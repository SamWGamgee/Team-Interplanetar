/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

// Use the following line if you have a Leonardo or MKR1000
//#define USE_USBCON

#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std_msgs::String str_msg; 
ros::Publisher pub("rover_to_base", &str_msg);//initialize rostopic "rover_to_base" under publisher 'pub'

const int S0=4; // TCS230 or TCS3200 RGB sensor
const int S1=5;
const int S2=6;
const int S3=7;
const int sensorOut=8;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup()
{
  nh.initNode();
  nh.advertise(pub);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);// Setting frequency scaling to 20%
  //based on states scaling can be set to 2% and 100%
  digitalWrite(S1,LOW);
}

void loop()
{
  digitalWrite(S2,LOW);// For reading red frequency
  digitalWrite(S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);
  
  delay(100);
  
  digitalWrite(S2,HIGH);// For reading green frequency
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
   
  delay(100);
 
  digitalWrite(S2,LOW);// For reading blue frequency
  digitalWrite(S3,HIGH);
  
  blueFrequency = pulseIn(sensorOut, LOW);
   
  delay(100);

  // Detect the color of the material
  if(redFrequency > greenFrequency && redFrequency > blueFrequency){
    str_msg.data="RED detected!";
  }
  else if(greenFrequency > redFrequency && greenFrequency > blueFrequency){
    str_msg.data="GREEN detected!";
  }
  else if(blueFrequency > redFrequency && blueFrequency > greenFrequency){
    str_msg.data="BLUE detected!";
  }
  
  pub.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
