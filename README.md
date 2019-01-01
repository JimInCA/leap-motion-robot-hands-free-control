# Leap Motion Redbot Hands Free Controller

## Introduction

Ever since I first saw the Leap Motion Hand Tracking Controller, I've been fascinated by the potential of what can be done with this fantastic device.  Leap Motion has not only developed a device that can track your hands, but through their software, they can tell you every aspect about your hands.  With great accuracy, they can tell you if you every aspect of your left, right, or both hands; they can tell you the pitch, roll, and yaw of the palm of your hand; they can tell you how many fingers you have extended along with the length and direction of each segment of each finger on each hand (including your thumb).  With this device and its accompanying software, you can use your hands as input devices to control any aspect that is controllable through your computer.  The potential of this device is limitless!

With this in mind, I wanted to start with a simple device that I can control with just hand gestures.  This, I'm doing to become familiar with the use of the Leap Motion Controller along with its software and to just have some fun.  What I came up with is the software that allows you to control a Sparkfun Redbot robot with just your hands in free space.  

The Redbot robot is a basic robot platform that has two wheels where each one is driven independently along with a third pivot point.  So in order to control this robot, I'll need throttle control for forward and reverse along with directional control for straight, left or right.  I decided to use a single hand to control the device with the pitch of the palm to control the throttle and roll for directional control.

And now, how am I communicating with the Redbot?  Good thing that you asked.  I just happened to have several Digi XBee modules left over from an early project that just happen to fit the bill.  And the best part is that the controller board on the Redbot is already fitted with the proper connector to support the XBee module.  I just love it when things work out for the better!  In addition to the one XBee module for the Redbot, I have two others.  Both of these modules are mounted on SparkFun Explorer boards that includes an FTDI to USB chip, so all I have to do is plug in the module onto the project board and then plug the project board into an open USB port on by computer and I'm all set.  Now you may ask, why do I have two modules connected to the computer?  Again, good question.  I'm using one as a transceiver to communicate with the XBee module on the Redbot and the second one is being used to monitor all communications between the computer and the Redbot through the use of a terminal window such as Tetra Term or HyperTerminal.

This Github repository contains the software that I've developed that provides the ability to control a SparkFun Redbot using the Leap Motion Controller.  It contains the firmware that gets loaded onto the Sparkfun Redbot along with the application that you run on your computer that allows you to control the robot without any contact to any device.

## Hardware Requirements

### Leap Motion Controller

The heart of this project is the Leap Motion Controller.  You can purchase one either directly from Leap Motion or from various online vendors. 

![alt text](./images/leapmotion_controller.jpeg?raw=true "Leap Motion Controller")

The Leap Motion Controller comes with a USB3 cable.  Simply plug the cable into the controller and the other end into an open USB port of your computer.  

### SparkFun Redbot

Next, we have the SparkFun Redbot robot development platform.  This kit comes with everything shown (along with a few items not shown).

![alt text](./images/sparkfun_redbot.jpeg?raw=true "SparkFun Redbot Robot Development Platform")

Please be aware that this version of the Redbot is no longer in production.  But the good news is that the differences between this Redbot and the one currently being sold by SparkFun have no relevance to what we will be doing in this demonstration.

The best part of this platform is the SparkFun Redbot Mainboard.  This is an Arduino compatible development board that includes everything that is needed to control this robot including the motor drivers.  It also includes multiple io ports that can be used to drive servos or other devices along with monitoring sensors.  But the best part is that it comes with the proper connector for the Digi XBee modules that we will be using to remotely control the robot.  In this project, we will only be using the Digi XBee connector along with the motor drivers.

The first thing that you will need to do is to build the Redbot according to the instructions provided by SparkFun.  This is an easy and fun process and shouldn't take more than an hour or so to complete.

### Digi XBee Modules

Ths last pieces of hardware that we will need are the Digi XBee RF Modules as shown below.

![alt text](./images/digi_xbee_modules.jpeg?raw=true "Digi XBee Pro 900 Modules")

What's shown above are three Digi XBee Pro 900 Modules along with a SparkFun XBee Explorer USB and a Sparkfun XBee Explorer Dongle.  I have one XBee module that is using a wire antenna and two that are using the RPSMA connector with a 900MHz antenna attached to each.

For this project, I've chosen to us the Digi Pro 900 Modules, primarily because I had these left over from an earily project.  These modules work on the 900MHz frequency band as apposed to the Digi modules that you'll normally find that work on the 2.4GHz frequency band.

For this project, you'll need to attach one of the XBee modules to the Redbot's XBee connector and mound one each on the XBee Explorers as shown below.

![alt text](./images/redbot_xbee.jpeg?raw=true "Assembled Modules")

Please be aware that there is what I'll call a 'design oversight' with the Redbot Mainboard.  This has to do with the placement of switch S3.  During development, you'll need to change the setting on this switch in order to load the firmware onto this board and then change the setting back in order to the firmware to work properly.  That is why I'm shown the XBee Module with the wire antenna mounted on the Redbot.  With this XBee module, you'll have direct access to switch S3 without having to remove and then remount the module during firmware updates.  

As a further note, I'm showing two XBee modules that will be used on the host side when in reality, you only NEED one.  The second module will be used to monitor the serial data between the Redbot and the host computer. This makes debugging the software much easier and is well worth the cost of the additional module when you consider the time that will be saved.

## Software Requirements

                    ...oooOooo...
