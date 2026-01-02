# ESP32 security system

It is a secure system that can use an RFID reader to let people into a building,...

## Why did I do this?

I don't even know... I previously did this project with an Arduino and so I decided to do it with my new ESP32!

## Features

- Web interface
- Can add new cards to the system (UID)
- It has a buzzer and an RGB LED for notification
- The motor acts like an automatic door

## Scripts

The entire script is only one and has about 300 lines, so just upload it via Arduino IDE and everything should work.

## How it works?

The RFID reader waits for the UID, if it is enabled in the system, the motor will turn, if not, it will not let you in. 
Turning the buzzer on or off can be controlled via a website running on the IP address.

### Home page:
![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc1MjAsInB1ciI6ImJsb2JfaWQifX0=--e5566524fd4fefe3dde6587cce4e9fbfe601d757/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)
### Admin page:
![image](https://blueprint.hackclub.com/user-attachments/representations/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Njc1MjAsInB1ciI6ImJsb2JfaWQifX0=--e5566524fd4fefe3dde6587cce4e9fbfe601d757/eyJfcmFpbHMiOnsiZGF0YSI6eyJmb3JtYXQiOiJwbmciLCJyZXNpemVfdG9fbGltaXQiOlsyMDAwLDIwMDBdLCJjb252ZXJ0Ijoid2VicCIsInNhdmVyIjp7InF1YWxpdHkiOjgwLCJzdHJpcCI6dHJ1ZX19LCJwdXIiOiJ2YXJpYXRpb24ifX0=--0f85faa91c373105a0f317054e965c1f47e93a37/image.png)

## 3D models

Here is a view of the top and bottom of the case:

![image](https://github.com/mavory/ESP32-security-system/blob/main/Photos/Sn%C3%ADmek%20obrazovky%202026-01-02%20130054.png?raw=true)

![image](https://github.com/mavory/ESP32-security-system/blob/main/Photos/Sn%C3%ADmek%20obrazovky%202026-01-02%20130113.png?raw=true)

## There is the final photo of how it works!

--------
