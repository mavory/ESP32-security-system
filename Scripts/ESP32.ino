#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Stepper.h>
#include <deque>
#include "time.h"

// PINOUT!!
const char* ssid = "Vory_EXT";
const char* password = "Pazout2604";
const char* adminUser = "admin";
const char* adminPass = "admin123";

#define SCK_PIN 18
#define MISO_PIN 19
#define MOSI_PIN 23
#define SS_PIN 21
#define RST_PIN 22
#define STEP1 32
#define STEP2 33
#define STEP3 27
#define STEP4 14
#define L_R 25
#define L_G 26
#define L_B 4
#define BUZZ 2

//udání
MFRC522 rfid(SS_PIN, RST_PIN);
AsyncWebServer server(80);
Stepper door(2048, STEP1, STEP3, STEP2, STEP4);

bool lockdownManual = false;
bool readerOn = true;
bool ledsOn = true;
bool buzzOn = true;
bool scanMode = false;
int okC = 0, failC = 0, strikes = 0;
unsigned long blockStart = 0;

bool hostModeWaiting = false;
String hostCardUID = "";
unsigned long hostEndTime = 0; // Změněno z hostStartTime jen kvůli odpočtu

String schedDate = "";
int sH = -1, sM = -1, eH = -1, eM = -1;

unsigned long motorStartTime = 0;
int motorPhase = 0; 
bool greenFeedback = false;
unsigned long redFeedbackEnd = 0;

struct User { String id; String name; String last; };
std::vector<User> users;
struct Log { String t; String n; String res; };
std::deque<Log> logs;

void setLED(int r, int g, int b) { 
  // Pokud jsou LED vypnuté v nastavení, ale probíhá feedback nebo motor, stejně se rozsvítí
  bool override = (motorPhase > 0 || greenFeedback || redFeedbackEnd > millis() || strikes >= 10);
  if (!ledsOn && !override) {
    digitalWrite(L_R, LOW); digitalWrite(L_G, LOW); digitalWrite(L_B, LOW);
    return;
  }
  digitalWrite(L_R, r > 0 ? HIGH : LOW);
  digitalWrite(L_G, g > 0 ? HIGH : LOW);
  digitalWrite(L_B, b > 0 ? HIGH : LOW);
}

// Vyšší frekvence pro pocitově vyšší hlasitost
void sound(int f, int d) { if(buzzOn) tone(BUZZ, f, d); }
void actionBeep() { sound(2500, 50); } // Pronikavější pípnutí

void loadUsers() {
  users.clear();
  if(!LittleFS.exists("/u.dat")) return;
  File f = LittleFS.open("/u.dat", "r");
  while(f.available()){
    String i = f.readStringUntil(':'); String n = f.readStringUntil('|'); String l = f.readStringUntil('\n');
    i.trim(); n.trim(); l.trim();
    if(i.length()>0) users.push_back({i, n, l});
  }
  f.close();
}

void saveUsers() {
  File f = LittleFS.open("/u.dat", "w");
  if(!f) return;
  for(auto const& u : users) f.printf("%s:%s|%s\n", u.id.c_str(), u.name.c_str(), u.last.c_str());
  f.close();
}

void addLog(String name, String res) {
  struct tm ti; getLocalTime(&ti); char ts[10]; strftime(ts, 10, "%H:%M", &ti);
  if(logs.size() >= 15) logs.pop_back();
  logs.push_front({String(ts), name, res});
}

bool isLockdownActive() {
  struct tm ti; if(!getLocalTime(&ti)) return lockdownManual;
  char buf[11]; strftime(buf,11,"%Y-%m-%d",&ti);
  if (schedDate != "" && String(buf) == schedDate) {
    int nowMin = ti.tm_hour * 60 + ti.tm_min;
    int startMin = sH * 60 + sM;
    int endMin = eH * 60 + eM;
    if (nowMin >= startMin && nowMin < endMin) return true;
  }
  return lockdownManual;
}

//začátek toho nechutnýho kódu (Ale je uspornej)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><style>
body{background:#000;color:#fff;font-family:sans-serif;display:flex;justify-content:center;align-items:center;height:100vh;margin:0;}
.card{width:420px;text-align:center;padding:40px;border:1px solid #111;border-radius:24px;background:#050505;}
h1{font-size:0.7rem;letter-spacing:4px;color:#444;text-transform:uppercase;margin-bottom:40px;}
#st{font-size:2.8rem;font-weight:200;margin-bottom:10px;}
#scInfo{font-size:0.8rem;color:#ff9500;margin-bottom:30px;height:20px;}
table{width:100%;font-size:0.75rem;color:#666;border-collapse:collapse;} td{padding:12px;border-bottom:1px solid #111;text-align:left;}
.admin-link{display:block;margin-top:40px;color:#222;text-decoration:none;font-size:0.65rem;}
</style></head><body><div class="card"><h1>SECURITY SYSTEM</h1><div id="st">...</div><div id="scInfo"></div><table id="lb"></table><a href="/admin" class="admin-link">SYSTEM ADMINISTRATION</a></div>
<script>async function up(){const r=await fetch('/api/st');const d=await r.json();
document.getElementById('st').innerText=d.isL?'LOCKDOWN':(d.isB?'BLOCKED':'ONLINE');
document.getElementById('st').style.color=d.isL?'#ff3b30':'#ffffff'; 
document.getElementById('scInfo').innerText=d.scD?`Planned Lockdown: ${d.scD} ${d.scS}-${d.scE}`:'';
let h='';d.logs.slice(0,5).forEach(l=>h+=`<tr><td>${l.t}</td><td>${l.n}</td><td>${l.r}</td></tr>`);document.getElementById('lb').innerHTML=h;}setInterval(up,2000);up();</script></body></html>
)rawliteral";

const char admin_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><style>
body{background:#000;color:#fff;font-family:sans-serif;margin:0;overflow:hidden;height:100vh;}
.main{display:grid;grid-template-columns:320px 1fr 350px;height:100vh;background:#1a1a1a;gap:1px;}
.col{background:#0a0a0a;padding:28px;overflow-y:auto;display:flex;flex-direction:column;}
h2{font-size:0.7rem;color:#555;text-transform:uppercase;letter-spacing:2px;margin-bottom:24px;}
.btn{background:#111;border:1px solid #222;color:#fff;padding:16px;cursor:pointer;margin-bottom:12px;width:100%;text-align:left;border-radius:12px;}
.btn:disabled{opacity:0.1;cursor:not-allowed;}
.btn-status{display:block;font-size:0.6rem;color:#444;margin-top:4px;font-weight:800;text-transform:uppercase;}
.h-box{background:#001a33;padding:15px;border-radius:12px;margin-bottom:15px;border:1px solid #003366;}
input{background:#111;border:1px solid #222;color:#fff;padding:12px;width:calc(100% - 28px);margin-bottom:12px;border-radius:10px;outline:none;}
table{width:100%;font-size:0.8rem;border-collapse:collapse;} td,th{padding:12px 10px;border-bottom:1px solid #111;}
th{text-align:left;color:#333;font-size:0.6rem;}
</style></head><body>
<div class="main">
  <div class="col">
    <h2>SYSTEM CONTROL</h2>
    <button class="btn" onclick="f('/api/open')">RELEASE LATCH<span class="btn-status">READY</span></button>
    <button class="btn" id="btnS" onclick="f('/api/scan')">SCAN NEW TAG<span id="statScan" class="btn-status">IDLE</span></button>
    <div id="hArea"></div>
    <button class="btn" id="btnH" onclick="f('/api/host')">HOST ACCESS<span id="statHost" class="btn-status">INACTIVE</span></button>
    <button class="btn" onclick="f('/api/t-l')">LOCKDOWN MODE<span id="statLock" class="btn-status">OFF</span></button>
    <button class="btn" onclick="f('/api/t-r')">RFID READER<span id="statRead" class="btn-status">ON</span></button>
    <button class="btn" onclick="f('/api/t-b')">BUZZER FEEDBACK<span id="statBuzz" class="btn-status">ON</span></button>
    <button class="btn" onclick="f('/api/t-led')">STATUS LIGHTS<span id="statLed" class="btn-status">ON</span></button>
  </div>
  <div class="col">
    <h2>USER DIRECTORY</h2><div id="uList"></div>
    <h2 style="margin-top:40px">SCHEDULER</h2>
    <div id="scActive" style="font-size:0.7rem;color:#555;margin-bottom:10px"></div>
    <input type="date" id="sd"><div style="display:flex;gap:10px"><input type="time" id="ss"><input type="time" id="se"></div>
    <button class="btn" onclick="setS()">APPLY SCHEDULE</button><button class="btn" onclick="f('/api/s-clr')">CLEAR SCHEDULE</button>
  </div>
  <div class="col">
    <h2>ACTIVITY LOG</h2><table id="lb"></table>
    <button class="btn" style="margin-top:auto" onclick="f('/api/clear')">PURGE ALL LOGS</button>
    <button class="btn" style="color:#ff453a;border-color:#331111;" onclick="location.href='/logout'">EXIT SESSION</button>
  </div>
</div>
<script>
function f(u){fetch(u);setTimeout(load,200);}
function setS(){fetch(`/api/sched?d=${document.getElementById('sd').value}&s=${document.getElementById('ss').value}&e=${document.getElementById('se').value}`);setTimeout(load,200);}
async function load(){
  const r=await fetch('/api/st');const d=await r.json();
  document.getElementById('btnS').disabled = d.isL;
  document.getElementById('btnH').disabled = d.isL;
  document.getElementById('statLock').innerText='STATUS: '+(d.isL?'ACTIVE':'OFF');
  document.getElementById('statRead').innerText='STATUS: '+(d.rO?'ON':'OFF');
  document.getElementById('statBuzz').innerText='STATUS: '+(d.bO?'ON':'OFF');
  document.getElementById('statLed').innerText='STATUS: '+(d.lO?'ON':'OFF');
  document.getElementById('statHost').innerText='STATUS: '+(d.hW?'WAITING':'INACTIVE');
  document.getElementById('scActive').innerText = d.scD ? `Scheduled: ${d.scD} (${d.scS}-${d.scE})` : 'No schedule set';
  if(d.hRem > 0) {
    document.getElementById('hArea').innerHTML = `<div class="h-box"><div style="font-size:0.7rem;color:#00aaff">HOST 1 ACTIVE</div><div style="font-size:1.1rem;margin:5px 0">${d.hRem}s remaining</div><button onclick="f('/api/h-plus')" style="background:#003366;border:none;color:white;padding:5px 8px;border-radius:4px;cursor:pointer">+2m</button><button onclick="f('/api/h-del')" style="background:#330000;border:none;color:white;padding:5px 8px;border-radius:4px;cursor:pointer;margin-left:5px">Revoke</button></div>`;
  } else document.getElementById('hArea').innerHTML = '';
  let lh='<tr><th>TIME</th><th>ENTITY</th><th>RESULT</th></tr>';
  d.logs.forEach(l=>lh+=`<tr><td>${l.t}</td><td>${l.n}</td><td>${l.r}</td></tr>`);
  document.getElementById('lb').innerHTML=lh;
  const ur=await fetch('/api/ulist');const ud=await ur.json();
  let uh='<table><tr><th>NAME</th><th>UID</th><th></th></tr>';
  ud.forEach(u=>uh+=`<tr><td><input style="margin:0;padding:4px;width:100px" value="${u.n}" onchange="ren('${u.i}',this.value)"></td><td><span style="color:#444">${u.i}</span></td><td><button style="background:none;border:none;color:#ff453a;cursor:pointer" onclick="del('${u.i}')">DEL</button></td></tr>`);
  document.getElementById('uList').innerHTML=uh+'</table>';
}
function ren(i,n){fetch(`/api/rename?id=${i}&n=${n}`);}
function del(i){if(confirm('Delete?')){fetch(`/api/del?id=${i}`);setTimeout(load,200);}}
load(); setInterval(load, 2000);
</script></body></html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  if(!LittleFS.begin(true)){ LittleFS.format(); LittleFS.begin(); }
  loadUsers();
  pinMode(L_R, OUTPUT); pinMode(L_G, OUTPUT); pinMode(L_B, OUTPUT); 
  pinMode(BUZZ, OUTPUT); pinMode(RST_PIN, OUTPUT);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  Serial.println("INITIALIZING RFID...");
  while(true) {
    digitalWrite(RST_PIN, LOW); delay(50); digitalWrite(RST_PIN, HIGH); delay(50);
    rfid.PCD_Init();
    rfid.PCD_SetAntennaGain(rfid.RxGain_max);
    byte v = rfid.PCD_ReadRegister(rfid.VersionReg);
    Serial.print("RFID Check: 0x"); Serial.println(v, HEX);
    if(v != 0x00 && v != 0xFF) {
      Serial.println(">> RFID SUCCESSS! Module connected. <<");
      sound(3000, 100); delay(150); sound(4000, 100); 
      break; 
    }
    delay(1000);
  }

  WiFi.begin(ssid, password);
  configTime(3600, 3600, "pool.ntp.org"); 

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *r){ r->send_P(200, "text/html", index_html); });
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest *r){
    if(!r->authenticate(adminUser, adminPass)) return r->requestAuthentication();
    r->send_P(200, "text/html", admin_html);
  });
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *r){
    r->send(401, "text/html", "<html><script>window.location.href='/';</script></html>");
  });

  server.on("/api/st", HTTP_GET, [](AsyncWebServerRequest *r){
    long hRem = (hostEndTime > millis()) ? (hostEndTime - millis()) / 1000 : 0;
    String j = "{ \"isL\":" + String(isLockdownActive()?"true":"false") + ",\"isB\":" + String(strikes>=10?"true":"false");
    j += ",\"rO\":" + String(readerOn?"true":"false") + ",\"bO\":" + String(buzzOn?"true":"false") + ",\"lO\":" + String(ledsOn?"true":"false") + ",\"hW\":" + String(hostModeWaiting?"true":"false");
    j += ",\"scD\":\"" + schedDate + "\",\"scS\":\"" + (sH<10?"0":"")+String(sH)+":"+(sM<10?"0":"")+String(sM) + "\",\"scE\":\"" + (eH<10?"0":"")+String(eH)+":"+(eM<10?"0":"")+String(eM) + "\"";
    j += ",\"hRem\":" + String(hRem);
    j += ",\"logs\":[";
    for(int i=0; i<logs.size(); i++) j += "{\"t\":\""+logs[i].t+"\",\"n\":\""+logs[i].n+"\",\"r\":\""+logs[i].res+"\"}" + (i<logs.size()-1?",":"");
    j += "]}"; r->send(200, "application/json", j);
  });

  server.on("/api/ulist", HTTP_GET, [](AsyncWebServerRequest *r){
    String j = "[";
    for(int i=0; i<users.size(); i++) j += "{\"i\":\""+users[i].id+"\",\"n\":\""+users[i].name+"\"}" + (i<users.size()-1?",":"");
    j += "]"; r->send(200, "application/json", j);
  });

  server.on("/api/scan", [](AsyncWebServerRequest *r){ if(!isLockdownActive()) scanMode = true; actionBeep(); r->send(200); });
  server.on("/api/host", [](AsyncWebServerRequest *r){ if(!isLockdownActive()) hostModeWaiting = true; actionBeep(); r->send(200); });
  server.on("/api/h-plus", [](AsyncWebServerRequest *r){ if(hostEndTime > millis()) hostEndTime += 120000; actionBeep(); r->send(200); });
  server.on("/api/h-del", [](AsyncWebServerRequest *r){ hostEndTime = 0; hostCardUID = ""; actionBeep(); r->send(200); });
  server.on("/api/t-l", [](AsyncWebServerRequest *r){ lockdownManual = !lockdownManual; actionBeep(); r->send(200); });
  server.on("/api/t-r", [](AsyncWebServerRequest *r){ readerOn = !readerOn; actionBeep(); r->send(200); });
  server.on("/api/t-b", [](AsyncWebServerRequest *r){ buzzOn = !buzzOn; actionBeep(); r->send(200); });
  server.on("/api/t-led", [](AsyncWebServerRequest *r){ ledsOn = !ledsOn; actionBeep(); r->send(200); });
  server.on("/api/s-clr", [](AsyncWebServerRequest *r){ schedDate = ""; actionBeep(); r->send(200); });
  server.on("/api/clear", [](AsyncWebServerRequest *r){ logs.clear(); actionBeep(); r->send(200); });
  server.on("/api/rename", [](AsyncWebServerRequest *r){ String id = r->arg("id"), n = r->arg("n"); for(auto &u : users) if(u.id == id) u.name = n; saveUsers(); r->send(200); });
  server.on("/api/del", [](AsyncWebServerRequest *r){ String id = r->arg("id"); users.erase(std::remove_if(users.begin(), users.end(), [&](User u){return u.id == id;}), users.end()); saveUsers(); r->send(200); });
  server.on("/api/open", [](AsyncWebServerRequest *r){ if(motorPhase==0){ greenFeedback=true; motorPhase=1; actionBeep(); } r->send(200); });
  server.on("/api/sched", [](AsyncWebServerRequest *r){ schedDate = r->arg("d"); sH = r->arg("s").substring(0,2).toInt(); sM = r->arg("s").substring(3,5).toInt(); eH = r->arg("e").substring(0,2).toInt(); eM = r->arg("e").substring(3,5).toInt(); actionBeep(); r->send(200); });

  server.begin();
}

void loop() {
  unsigned long now = millis();
  if (now % 5000 == 0) rfid.PCD_SetAntennaGain(rfid.RxGain_max);
  if(strikes >= 10 && (now - blockStart > 120000)) strikes = 0;

  door.setSpeed(12);
  if (motorPhase == 1) { 
    setLED(0, 255, 0); // VYNUCENÍ ZELENÉ PŘED POHYBEM
    delay(100); 
    door.step(1024); 
    motorStartTime = now; 
    motorPhase = 2; 
  }
  else if (motorPhase == 2 && (now - motorStartTime > 3000)) { motorPhase = 3; }
  else if (motorPhase == 3) { 
    setLED(0, 255, 0); // DRŽET ZELENOU PŘI NÁVRATU
    door.step(-1024); 
    motorPhase = 0; 
    greenFeedback = false; 
  }

  // LOGIKA STAVOVÉ DIODY
  if (strikes >= 10) setLED(255, 0, 0);
  else if (motorPhase > 0 || greenFeedback) setLED(0, 255, 0);
  else if (now < redFeedbackEnd) setLED(255, 0, 0);
  else if (scanMode) setLED(255, 255, 0);
  else if (hostModeWaiting) setLED(0, 0, 255);
  else if (isLockdownActive()) setLED(255, 0, 0);
  else setLED(10, 10, 20); // Standby modrá

  if (readerOn && !isLockdownActive() && strikes < 10 && motorPhase == 0) {
    rfid.PCD_Init(); 
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      String id = "";
      for(byte i=0; i<rfid.uid.size; i++) id += (rfid.uid.uidByte[i]<0x10?"0":"")+String(rfid.uid.uidByte[i], HEX);
      id.toUpperCase();

      if(scanMode) {
        bool exists = false; for(auto &u : users) if(u.id == id) exists = true;
        if(!exists) { users.push_back({id, "NEW USER", "NEVER"}); saveUsers(); }
        scanMode = false; sound(2000, 100);
      } 
      else if(hostModeWaiting) {
        hostCardUID = id; hostEndTime = now + 300000;
        hostModeWaiting = false; sound(2000, 200); addLog("HOST 1 SET", id);
      } 
      else {
        bool allowed = (id == hostCardUID && now < hostEndTime); 
        String name = (id == hostCardUID) ? "HOST 1" : "UNKNOWN";
        for(auto &u : users) if(u.id == id){ 
          allowed = true; name = u.name; 
          struct tm ti; getLocalTime(&ti); char ts[20]; strftime(ts, 20, "%d.%m %H:%M", &ti);
          u.last = String(ts); break; 
        }
        if(allowed) {
          addLog(name, "APPROVED"); strikes = 0; greenFeedback = true; 
          setLED(0, 255, 0); // OKAMŽITÝ FEEDBACK
          sound(1500, 100); sound(2000, 150); 
          motorPhase = 1; 
          saveUsers();
        } else {
          strikes++; addLog(id, "DENIED"); 
          redFeedbackEnd = now + 2000; 
          setLED(255, 0, 0); // OKAMŽITÝ FEEDBACK
          if(strikes >= 10) blockStart = now; 
          sound(400, 500); // HLASITÉ DLOUHÉ "ERROR" BZUČENÍ
        }
      }
      rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();
      delay(1500); 
    }
  }
}

//miluju když je to hotove - @MAVORY
