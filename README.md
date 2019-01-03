# Leap Motion Redbot Hands Free Controller

## **Introduction**

Ever since I first saw the Leap Motion Hand Tracking Controller, I've been fascinated by the potential of what can be done with this fantastic device.  Leap Motion has not only developed a device that can track your hands, but through their software, they can tell you every aspect about your hands.  With great accuracy, they can tell you if you every aspect of your left, right, or both hands; they can tell you the pitch, roll, and yaw of the palm of your hand; they can tell you how many fingers you have extended along with the length and direction of each segment of each finger on each hand (including your thumb).  With this device and its accompanying software, you can use your hands as input devices to control any aspect that is controllable through your computer.  The potential of this device is limitless!

With this in mind, I wanted to start with a simple device that I can control with just hand gestures.  This, I'm doing to become familiar with the use of the Leap Motion Controller along with its software and to just have some fun.  What I came up with is the software that allows you to control a SparkFun Redbot robot with just your hands in free space.

The Redbot robot is a basic robot platform that has two wheels where each one is driven independently along with a third pivot point.  So in order to control this robot, I'll need throttle control for forward and reverse along with directional control for straight, left or right.  I decided to use a single hand to control the device with the pitch of the palm to control the throttle and roll for directional control.

And now, how am I communicating with the Redbot?  Good thing that you asked.  I just happened to have several Digi XBee modules left over from an early project that just happen to fit the bill.  And the best part is that the controller board on the Redbot is already fitted with the proper connector to support the XBee module.  I just love it when things work out for the better!  In addition to the one XBee module for the Redbot, I have two others.  Both of these modules are mounted on SparkFun Explorer boards that includes an FTDI to USB chip, so all I have to do is plug in the module onto the project board and then plug the project board into an open USB port on by computer and I'm all set.  Now you may ask, why do I have two modules connected to the computer?  Again, good question.  I'm using one as a transceiver to communicate with the XBee module on the Redbot and the second one is being used to monitor all communications between the computer and the Redbot through the use of a terminal window such as Tetra Term or HyperTerminal.

This Github repository contains the software that I've developed that provides the ability to control a SparkFun Redbot using the Leap Motion Controller.  It contains the firmware that gets loaded onto the SparkFun Redbot along with the application that you run on your computer that allows you to control the robot without any contact to any device.

## **Hardware Requirements**

The hardware requirements consist of the Leap Motion Controller, the SparkFun Redbot robot, and a verity of Digi XBee modules and supporting hardware.  This is documented in the following sections.

### **Leap Motion Controller**

The heart of this project is the Leap Motion Controller.  You can purchase one either directly from Leap Motion or from various online vendors. 

![alt text](./images/leapmotion_controller.jpeg?raw=true "Leap Motion Controller")

The Leap Motion Controller comes with a USB3 cable.  Simply plug the cable into the controller and the other end into an open USB port of your computer.

### **SparkFun Redbot**

Next, we have the SparkFun Redbot robot development platform.  This kit comes with everything shown (along with a few items not shown).

![alt text](./images/sparkfun_redbot.jpeg?raw=true "SparkFun Redbot Robot Development Platform")

Please be aware that this version of the Redbot is no longer in production.  But the good news is that the differences between this Redbot and the one currently being sold by SparkFun have no relevance to what we will be doing in this demonstration.

The best part of this platform is the SparkFun Redbot Mainboard.  This is an Arduino compatible development board that includes everything that is needed to control this robot including the motor drivers.  It also includes multiple io ports that can be used to drive servos or other devices along with monitoring sensors.  But the best part is that it comes with the proper connector for the Digi XBee modules that we will be using to remotely control the robot.  In this project, we will only be using the Digi XBee connector along with the motor drivers.

The first thing that you will need to do is to build the Redbot according to the instructions provided by SparkFun.  This is an easy and fun process and shouldn't take more than an hour or so to complete.

### **Digi XBee Modules**

This last pieces of hardware that we will need are the Digi XBee RF Modules as shown below.

![alt text](./images/digi_xbee_modules.jpeg?raw=true "Digi XBee Pro 900 Modules")

What's shown above are three Digi XBee Pro 900 Modules along with a SparkFun XBee Explorer USB and a SparkFun XBee Explorer Dongle.  I have one XBee module that is using a wire antenna and two that are using the RPSMA connector with a 900MHz antenna attached to each.

For this project, I've chosen to us the Digi Pro 900 Modules, primarily because I had these left over from an earlier project.  These modules work on the 900MHz frequency band as apposed to the Digi modules that you'll normally find that work on the 2.4GHz frequency band.

For this project, you'll need to attach one of the XBee modules to the Redbot's XBee connector and mound one each on the XBee Explorers as shown below.

![alt text](./images/redbot_xbee.jpeg?raw=true "Assembled Modules")

Please be aware that there is what I'll call a 'design oversight' with the Redbot Mainboard.  This has to do with the placement of switch S3.  During development, you'll need to change the setting on this switch in order to load the firmware onto this board and then change the setting back in order for the firmware to work properly.  That is why I'm shown the XBee Module with the wire antenna mounted on the Redbot.  With this XBee module, you'll have direct access to switch S3 without having to remove and then remount the module during firmware updates.

As a further note, I'm showing two XBee modules that will be used on the host side when in reality, you only NEED one.  The second module will be used to monitor the serial data between the Redbot and the host computer. This makes debugging the software much easier and is well worth the cost of the additional module when you consider the time that will be saved.

## **Software Requirements**

There are multiple pieces of software that will need to be downloaded and installed.  These include the following:

* The Arduino IDE along with the SparkFun plug-in for Arduino
* Visual Studio Community 2017
* git
* Leap Motion Services
* Leap Motion Software Development Kit (SDK)
* Leap Motion LeapC-Samples
* This repository

I guess that I should start with the basics and that is that all development was done using Windows 10.

### **Arduino IDE**

Let's start with the simple stuff first.  You will need to install the Arduino IDE.  At the time of this writing, I installed version 1.8.7.  Once you have this installed, you will need to install the SparkFun plug-in for Arduino.  This is a pretty straight forward process and is well documented on the SparkFun web site.  You can start by going to the following URL which will take you to the SparkFun web site:

[SparkFun Software Installation Guide](https://learn.sparkfun.com/tutorials/experiment-guide-for-redbot-with-shadow-chassis/experiment-1-software-install-and-basic-test)

Then, just follow the instructions on how to install the Arduino IDE along with the SparkFun plug-in.  Truthfully, they've explained the process better than I can.

### **Visual Studio Community 2017**

Visual Studio Community 2017 is a full featured and free version of Microsoft's Visual Studio IDE.  You can download the installer for either Windows or Mac at the following link:

[Visual Studio Community 2017](https://visualstudio.microsoft.com/vs/community/)

Once you've downloaded the installer, you will need to execute it to install Visual Studio on your system.

### **git**

Considering that you're looking at Github, I'm going to assume that you already have git installed and are familiar with its use. You will need git to clone various repositories in the process of requiring the various pieces of software.

### **Leap Motion Services**

Another piece of software that you will need to install is the Leap Motion Services.  Leap Motion does a great job at defining how to install their services at the following link:

[Leap Motion Service](https://www.leapmotion.com/setup/)

For this project, you will need to install the Leap Motion Services for the desktop.  Once installed, the service will run in the background and will only become active once the Leap Motion Controller is plugged into your host computer.  The application that we will be building that runs on the host computer will interact with this service to get the hand tracking data.  So it is quite important that it is installed and working properly.

### **Leap Motion Software Development Kit (SDK)**

From the same link above, you should be able to find the Leap Motion SDK.  You will need to download and install this as well.

### **Leap Motion LeapC-Samples**

Please bare with me, we're getting close to the end.  The next software package what needs to be downloaded is the Leap Motion LeapC example programs that I used as a starting point for this project.  You will first need to go the the Leap Motion Github LeapC-samples repository at the following link:

[LeapC-samples](https://github.com/leapmotion/LeapC-samples)

You can then clone the repository like this:

```
mkdir Development
cd Development
git clone https://github.com/leapmotion/LeapC-samples.git
```

### **redbot-touchless-control**

And last but not lest, you will need to clone this repository as well:

```
git clone https://github.com/JimInCA/redbot-touchless-control.git
```

I know that this was quite a bit, but this should be it for software installation.  Next we will need to configure the software by coping some code from LeapC to our project.  This is how I'm avoiding any copyright issues, which I strongly support.

## **Software Configuration**

Now that we have everything that we need to build both the firmware for the Redbot and for building the host application, we now need to copy some files from the Leap Motion LeapC samples directory to our application directory.  I've put together a script file that will automatically copy the files from the LeapC-samples directory and place them where Visual Studio expects them to me.  Assuming that you cloned the two directories as defined above, this is all you should need to do:

```
cd ./redbot-touchless-control
./auto_config.sh
```

Now you may say "Hey! We're using Windows! What gives with the script file?" and you would be right.  I worked for may years on Sun System machines and I feel very comfortable using the Unix Shell and the one that I prefer these days is the one that gets installed when you install GitExtensions on any machine running Windows.  So that's what I'm using these days.  But everything that you need to do is documented in this script, so if you don't have a Unix shell that you can use, you should be able to figure out what you need to do by simple reviewing auto_config.sh.  But someday, I my rewrite this script into a Windows compatible batch file...

##  **Building and Installing the Redbot Firmware**

Now that all the work is done, we can finally start to have some fun!  To start with, we will first build the firmware that we will load onto the SparkFun Redbot.  This should be a simple task if the Arduino IDE is set up as defined above.  So open the Arduino IDE and from the File menu, select open.  Once the file browser opens, make your way to `<path>/redbot-touchless-control/redbot-firmware` and select `redbot-firmware.ino' to open the the file that has the firmware source code.

Please feel free to scan through the code to become familiar with what it is doing.  The code is very simple in that the setup() function initializes the uart and timeout counter.  The main work is being done in the loop() function in that it waits for data to show up on the uart, reads the data, and then programs the left and right motor with the data that it receives.  If you look closely, you'll also notice that I have a timeout counter that is intended to prevent the robot from running wild if it stops receiving data by zeroing out the motor analog values.

So now what we need to do is connect the Redbot to the host computer through the USB cable connected to the Redbot Mainboard.  You should be familiar with this if you went through the SparkFun Software Initialization Guide as I had suggested earlier.  So once the Redbot Mainboard is connected to the host, you will need to open the Tools menu in the Arduino IDE and then scroll down to Boards:... From the pop-up listing, scroll down and select SparkFun Redbot.  You will then need to repeat the process of opening up the Tools menu, but this time, you will need to select Ports and then select the proper port that your Redbot is connected to on your computer.  From this point, it should be a simple mater of selecting Verify/Compile from the Sketch menu and once it completes, then select Upload frm the Sketch menu to load the firmware onto the Redbot Mainboard. 

Please be aware that as I've pointed out earlier, you will need to change the position on switch S3 to upload the firmware and then switch it back to its original position once the firmware is completed uploading.  

##  **Building The Redbot Host Application**

All that's left is to build the application that will run on your host computer that will send the wireless commands to the Redbot.  We'll start by bringing up Visual Studio Community IDE.  

## **Testing Leap Motion Control of Redbot**

Now it's time to start having some real fun!  
