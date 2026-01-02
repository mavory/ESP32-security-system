# My Journal

This is a diary where I describe everything about how I created this project.

## So how much time did I spend on that?

I think I spent about 25 hours on this project.

## My worst hangups

- Unfortunately, I designed the bottom part of the case incorrectly, so I had to redo it completely.
- My RFID module hasn't been working for a while, so I had to solve this error as well.
- The website also didn't work for me because I broke it completely while coding.

## Timeline

### The beginning of my project!
I wanted to create an Arduino RFID system first, but later I decided to remake it and make it on my new ESP32!
I had to start from scratch, so I thought about how everything would work. I thought I could put a motor as a door and everything would be controlled via the web. When I had everything ready, I started taking things apart.
So it took me about 1.5 hours, because I had to dismantle the old project and think about the new one.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjUyNjEsInB1ciI6ImJsb2JfaWQifX0=--d6d16b95d1471c3a3df862dfe2b0ca53cf7bf386/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/1000022503.jpg)

### Oh no! Breadboard problem
When my brain was ready, I started taking things apart and adjusting things on the breadboard!
I thought it would be fun, but it wasn't at all...
The ESP32 didn't fit on my breadboard and unfortunately I don't have another one, so I spent some time thinking about how to solve this problem.
Unfortunately, I struggled with this problem for quite a long time, because I was looking for other solutions, such as trying to solder it, but I backed away from that.
I came up with a solution, which is to put the ESP32 aside and thus have to use 2x more jumpers.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjUzMTUsInB1ciI6ImJsb2JfaWQifX0=--ece9f20fcf3af1e8901eb665fdeaa5ca023218b1/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/1000022849.jpg)

### Connecting things is my passion..
So when I solved this problem, I started wiring all the components, I have to say it was terrible.
I had to redo the whole layout a few times just to make sure everything fit on the breadboard.
I managed it and then I moved on to the next part!

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjUzOTQsInB1ciI6ImJsb2JfaWQifX0=--d376c975d3a905b49fcb4de09a8a111605fcd14c/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/1000022854.jpg)

### First steps to working code
Then I started coding. At first I tested if everything worked and I had to read some articles about how ESP32 works, because that was my first project with this microcontroller.
It took me about half an hour, but then I found out that it is very similar to Arduino!
So then everything went like clockwork (that's what I thought...) - Unfortunately, I had a lot of problems with the micro SD card reader, then with RFID,... but I managed it

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjUzOTksInB1ciI6ImJsb2JfaWQifX0=--6ed10eac33307a39af299ed8c208b5a426f23e20/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/1000022942_720.png)

### Big mistake for me
I thought everything would be fine, but after redoing the wiring, everything fell apart, the SD card reader and RFID reader didn't work, the RGB diode didn't light up properly, so I had to disconnect everything again and slowly start over.
I connected some pins and suddenly everything started working - for now...
( I didn't know I would have to do it again 💀 )

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU0MTUsInB1ciI6ImJsb2JfaWQifX0=--bca6d469827a2e1fe7bf02ca551b7ba37134773b/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260101_132817.jpg)

### A new beginning - for now
Well... I started coding again. Everything went pretty well, except for one thing. The SD card reader suddenly stopped working, so I tried to make a code for it to see if it would work now, and unfortunately, it didn't.
But I researched this bug for a long time because I couldn't figure it out.
This way, I was forced to remove the micro SD reader and live without it. I rewrote the entire code to make it work without the reader.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU0MjQsInB1ciI6ImJsb2JfaWQifX0=--98bf996d0e0eebc6ad9b6fa9949dc4bd0798fee1/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/1000022941.jpg)

### Coding a script for ESP32
After this bug, I finally started coding and I have to say that it was terrible, my server crashed several times, it wouldn't load (as you can see in the photo) and I didn't know what to do.
Well, I tried different methods, but after a while I still ended up with the IP address.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU0MjYsInB1ciI6ImJsb2JfaWQifX0=--9991fab0cc8b178f2f0d70bb76fb4f6c3a595c8c/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

### 1. Web interface
Coding was probably the hardest part for me, even though I made a lot of mistakes elsewhere. Coming up with a nice, but functional web interface was beyond my skills.
I tried to make just an admin panel without security, but that seemed strange to me, so I also tried to make a page for the public where they can see statistics and then I tried to make an admin page, which I didn't succeed at all. Either it wouldn't load at all or I couldn't connect the website to the ESP32.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU0NTIsInB1ciI6ImJsb2JfaWQifX0=--632441993bfe41a039765181dfa0a2ca5e25ea1f/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260101_200147.jpg)

### My dream look
I wasn't at all satisfied with how the temporary web interface looked, so I started reworking the code to get my dream look.
It took me a lot of effort, I tried a lot of options, but again I encountered an error that I had been solving for a long time, but after about half an hour it was solved and I could continue!
After some time, I decided that a modern and minimalist look with just a black and white theme would be best.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU0OTAsInB1ciI6ImJsb2JfaWQifX0=--facc379a4e2ce9a67a03bf4ede201a33abf9f7f1/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/20260101_195634_720.png)

### Case design for everything
I took a break from programming for now and started thinking about how I would put everything in the case to make it look good!
My favorite and easy program to learn is Tinkercad. I normally use Fusion, but this is faster for me. When I started making some designs, I didn't notice that I was supposed to add a little space, so I fixed that. I had the sketch ready and suddenly I remembered that I was out of filament, so I ordered some new ones and hopefully they will arrive in the morning!

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU1MjYsInB1ciI6ImJsb2JfaWQifX0=--fe58421b2b95880b816a8252024989ec3dce68ef/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/Screenshot_20260101_235141_Alza.jpg)

### A moment for quick coding
I had nothing else to do, so I started redesigning the web interface. It took me a while, but I still wasn't satisfied... At least it was a black and white look and minimalist.
Some buttons just didn't work properly, so I had to redesign it again later, but at least I knew where it was going.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjU1NTgsInB1ciI6ImJsb2JfaWQifX0=--2e8b5630a352e7c19eb1aa863c2e3f069820569f/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260101_204503.jpg)

### How to hide an RFID module?
I got my filament today, so I can start modeling the case! But first I have to measure everything so that everything fits in the case.
I had to measure mainly the RFID module so that they could make a smaller space for it to fit in there.
I thought for a while about how I would do it and came up with a solution: I would make a holder for the top part to hold it so it wouldn't be visible, but it should work.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjY5NzcsInB1ciI6ImJsb2JfaWQifX0=--a3c247993ec897ce80dd5d586d153b5124a1ca0a/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

### Making all parts of the case
It took me a while, but I've finished both parts of the case. There's a hole on the top for the RGB diode that signals the status, and there's also a marked hole for the RFID!

- Here is the top view:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjcwNjEsInB1ciI6ImJsb2JfaWQifX0=--8f7e75b1db44054d0c2107994800246e23992534/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/Sn%C3%ADmek%20obrazovky%202026-01-02%20130054.png)

- Here is the bottom view:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjcwNjMsInB1ciI6ImJsb2JfaWQifX0=--1fd581dff0793a2330d2db823aeda0ebb6dc2bc4/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/Sn%C3%ADmek%20obrazovky%202026-01-02%20130113.png)

### 2. Web interface
Once I had the models ready, I went back to coding the website. There were some errors there, so I had to fix them. Sometimes the button wouldn't work for me or sometimes "Host mode" wouldn't work for me, so I fixed all that.
Unfortunately, I still have to redo the code, probably one more time, because I want to add some very interesting things!

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjcxMTMsInB1ciI6ImJsb2JfaWQifX0=--11f6117564eace38d0d58d106a9961d9d62d9814/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/20260101_204510_720.png)

### Circuit diagram!
I remembered that I still need to finish the Circuit diagram to show how it's connected. So I opened my favorite program - KICAD!
I started creating, but for example, for ESP32 I didn't know which model to use, I did some research and had to download some libraries to make it as similar as possible, but I managed it quite quickly, in my experience, in about an hour and a half.
The hardest part for me was probably finding what symbols to use, for example, I didn't know what symbol to use for the motor, but I guess I got the hang of it.

- Circuit diagram:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjcyODIsInB1ciI6ImJsb2JfaWQifX0=--48d36750d952fdea397c03e27d3585ef0f5074a3/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/ESP32.jpg)

### Printing 3D models
I'm already printing the first part! Hopefully it will work and everything will fit.
Unfortunately, I've found a problem that when I want to scan the UID, the reader doesn't work at all, so I have to try to find the problem and solve it as quickly as possible!

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc0MzYsInB1ciI6ImJsb2JfaWQifX0=--9738a606b2e05d62e542bd8f36b5a547e13d7b31/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260102_155329%20(1).jpg)

### Final code for the website
I have to say it with joy, but I already have a finished web interface, which looks very good to me! There are buttons to turn off the buzzer, RGB diodes, readers,...
It all took me a lot of time and I have to say that it was worth it. The code is about 330 lines, so it's not that long. I also modified the homepage to match the new design.

- Home page:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc1MzYsInB1ciI6ImJsb2JfaWQifX0=--2b2fe2daf3ade8f26e785c72293dd960093ab23b/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

- Admin page:

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc1MjAsInB1ciI6ImJsb2JfaWQifX0=--e5566524fd4fefe3dde6587cce4e9fbfe601d757/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

### Exporting files
I'm very close to the end, just need to finish a few wiring things and I think it'll be ready! I already have the last part printed, but the supports were harder to remove, so I had to spend 30 minutes cutting the plastic to make it fit properly!
I've also started exporting the files, which I'll later upload to GitHub, where everything is! I still have to finish the information and connections, so I still have a long way to go.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc1NTksInB1ciI6ImJsb2JfaWQifX0=--dcebc5b2c0c4ad5ba9072431bf0c0bf0efb11e72/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260102_175536%20(1).jpg)

### Remaking a 3D model
How to say it.... I started putting all the things in the box, everything fit except for one SMALL THING... CABLES
I made the box too short, so I can't close the cables and so on with it anymore. So I had to redo the case again and hopefully it will be good.

![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc1NzEsInB1ciI6ImJsb2JfaWQifX0=--6c037f3198fba3491a45f5db2b1e85ca828acec9/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJqcGciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--15ca3815f01a5683e19ea0585d2eef9af9e441d7/20260102_182307.jpg)


