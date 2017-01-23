# MBEDNest
A state machine written in C++ simulating the functionality of a Nest Thermometer on an ARM MBED Microcontroller

Project for ECE 2036 - Engineering Software Design

Product: A replica nest thermometer that changes states based on real time temperature using a TMP36 Thermometer. 

Hardware Used:
+ ARM MBED Microcontroller 
+ 1 x Breadboard
+ 3 x Pushbuttons
+ 1 x TMP36 Thermometer
+ 1 x Speaker
+ 1 x MicroSD Card Reader
+ 1 x uLCD Screen

Software Used:
+ C++ on MBED Cloud Compiler

Features:
+ 5 States (Heat ON, Heat OFF, System OFF, Cool ON, Cool OFF)
+ Button for switching between 3 modes (Heat, Off, Cool)
+ Two buttons for adjusting desired temperature
+ The ON and OFF within a mode are autimatically chosen based on the actual temperature and the temprature set by the user
+ Audio feedback when switching between modes and raising/lowering desired temperature
