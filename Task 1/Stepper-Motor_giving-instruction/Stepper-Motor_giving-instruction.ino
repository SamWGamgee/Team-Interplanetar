String instr;
const int stepPin = 5; //this pin makes the rotation at one step at a time
const int dirPin = 2;  //this pin is responsible for the direction of rotation
const int enPin = 8;  //if low, this pin enables the driver
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
}

void loop() {
  digitalWrite(dirPin,HIGH);//this makes the rotation at a definite direction.
  //change the state if you wanna change the direction
  while (Serial.available() == 0)   
    { //Wait for user input  
    }
  instr=Serial.readString();
  if(instr == 'C') {
    for(int i=0;i<25;i++){ //For 200 steps/rev, 25 steps goes only 45 degree
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);  
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500);
    }
  }
  else if (instr == 'S') {
    while (Serial.available() == 0 && Serial.readString()!='F') {//rotates continously if 'F' is not inputted
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500);
    }
  }
  
}
