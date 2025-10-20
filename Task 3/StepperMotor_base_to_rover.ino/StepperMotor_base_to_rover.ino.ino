
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

String instr;
const int stepPin = 5; //this pin makes the rotation at one step at a time
const int dirPin = 2;  //this pin is responsible for the direction of rotation
const int enPin = 8;  //if low, this pin enables the driver

void messageCb(const std_msgs::UInt16& toggle_msg){
  if(toggle_msg.data == 1) { //if published '1' into topic the motor rotates 45 degree
    for(int i=0;i<25;i++){ //For 200 steps/rev, 25 steps goes only 45 degree
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);  
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500);
    }
  }
  else if (toggle_msg.data == 9) { //if published '9' into topic the motor rotates uninterrupted
    while (toggle_msg.data!=0) {//rotates continously if '0' is not published
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500);
    }
  }
}

ros::Subscriber<std_msgs::UInt16> sub("base_to_rover", &messageCb );

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);

  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
}

void loop()
{  
  digitalWrite(dirPin,HIGH);//this makes the rotation at a definite direction.
  //change the state if you wanna change the direction
  
  nh.spinOnce();
  delay(100);
}
