const int S0=4; // TCS230 or TCS3200 RGB sensor
const int S1=5;
const int S2=6;
const int S3=7;
const int sensorOut=8;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0,HIGH);// Setting frequency scaling to 20%
  //based on states scaling can be set to 2% and 100%
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  
  digitalWrite(S2,LOW);// For reading red frequency
  digitalWrite(S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);
  
  Serial.print("R = ");
  Serial.println(redFrequency);
  delay(100);
  
  digitalWrite(S2,HIGH);// For reading green frequency
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
   
  Serial.print("G = ");
  Serial.println(greenFrequency);
  delay(100);
 
  digitalWrite(S2,LOW);// For reading blue frequency
  digitalWrite(S3,HIGH);
  
  blueFrequency = pulseIn(sensorOut, LOW);
   
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(100);

  // Detect the color of the material
  if(redFrequency > greenFrequency && redFrequency > blueFrequency){
      Serial.println("RED detected!");
  }
  else if(greenFrequency > redFrequency && greenFrequency > blueFrequency){
    Serial.println("GREEN detected!");
  }
  else if(blueFrequency > redFrequency && blueFrequency > greenFrequency){
    Serial.println("BLUE detected!");
  }
}
