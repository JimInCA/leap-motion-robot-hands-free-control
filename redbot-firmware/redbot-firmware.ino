#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

/***********************************************************************
 * RedBot Wireless Software Serial
 ***********************************************************************/

#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

RedBotMotors motors;
RedBotSoftwareSerial SSerial;

int leftPower;  // variable for setting the drive power
int rightPower;
int data;  // variable for holding incoming data from PC to Arduino
static unsigned long time_then;
static unsigned long time_now;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Enter in left and right motor power values and click [Send]."); 
  Serial.println("Separate values with a space or non-numeric character.");
  Serial.println("Positive values spin the motor CW, and negative values spin the motor CCW.");
  time_then = millis();
}

void loop(void)
{
  // if there is data coming in on the Serial monitor, do something with it.
  if(Serial.available() > 0)
  {
    leftPower = Serial.parseInt();  // read in the next numeric value
    leftPower = constrain(leftPower, -255, 255);  // constrain the data to -255 to +255
    
    rightPower = Serial.parseInt();   // read in the next numeric value
    rightPower = constrain(rightPower, -255, 255);  // constrain the data to -255 to +255

    motors.leftMotor(leftPower);
    motors.rightMotor(rightPower);
    time_then = millis();
  }
  else
  {
    time_now = millis();
    if (time_now > (time_then + 250UL))
    {
      // prevent run-away if controller stops transmitting
      motors.leftMotor(0);
      motors.rightMotor(0);
      Serial.println("Waiting...");
      Serial.flush();
      time_then = time_now;
    }
  }
}
