# Wrist Controlled RC Car

This was a fun early project I made that let me consolidate my knowledge of C, Arduino electronics, and 3D modelling. I've included the Arduino code, prototype board schematics, and 3D models for the car and wrist controller.

<br>

<p align="center"> 
  <img src="https://i.imgur.com/FT4axC1.jpg" width="400">
</p>

<p align="center"> 
  <img src="https://i.imgur.com/OK8XMAc.jpg" width="400">
</p>

<p align="center"> 
  <img src="https://i.imgur.com/VeCXkbs.jpg" width="400">
</p>

## Overview

The RC car uses two 12V geared DC motors, connected to a 2S Li-ion pack via a L293D dual H bridge. The H bridge is controlled by an Arduino Nano, which receives wireless commands from an NRF24L01 radio transceiver. 

The wrist controller consists of a GY-521 three-axis gyroscope module and an NRF24L01 radio transceiver controlled by an Arduino Nano. The controller is powered by a 9V battery.

<p align="center"> 
  <img src="https://i.imgur.com/3fIx6e9.png" width="600">
</p>

## Features

Once the car and wrist controller are powered on, the front lights will blink. When a connection is established (usually instant), the front lights will stay illuminated and the car will respond to the wrist controller. 

Holding the hand out parallel to the ground stops the car. Tilting the hand forward, back, left, and right drives the car in that respective direction. The car is capable of driving at a max forward speed of ~2 m/s, and can turn on a dime.

The car has a battery life of around 20 h of continuous heavy use.

## Code

All C code is original, except for the excellent TMRh20 library by Stefan Engelke for the NRF24L01 radio transceivers. 

## Schematics

The car and controller circuits were prototyped on breadboards before being built on two prototype boards. Fritzing was used to create digital schematics during this process.

## Models

The car shell and wheels were designed using SolidWorks and 3D printed using PLA filament. However, store bought wheels were used in the final design due to the need to superglue the 3D printed wheels (I might need to salvage the motors for later projects!)

## Photos

### Car Underside

<p align="center"> 
  <img src="https://i.imgur.com/iLLLVcL.jpg" width="300">
</p>

### Car and Controller Schematic Preview

<p align="center"> 
  <img src="https://i.imgur.com/Dah2qRM.png" width="600">
</p>

</br>

<p align="center"> 
  <img src="https://i.imgur.com/P8LcoUK.png" width="600">
</p>

### Prototypes

<p align="center"> 
  <img src="https://i.imgur.com/7XJsonO.jpg" width="300">
</p>

</br>

<p align="center"> 
  <img src="https://i.imgur.com/bo12gwc.png?1" width="300">
</p>




