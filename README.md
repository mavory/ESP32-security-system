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
Turning the buzzer on or off or the doorbell can be controlled via a website running on the IP address.
