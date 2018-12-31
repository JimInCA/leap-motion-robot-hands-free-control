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

[alt text](./images/leapmotion_controller.jpeg)


