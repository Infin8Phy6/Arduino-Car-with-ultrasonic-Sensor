#include <Servo.h>
//construct variables
const int trigfront = 7;
const int echofront  = 8;
const int trigback = 9;
const int echoback = 10;
const int Forwardpin= 3;
const int Reversepin= 4;
const int DISTANCE_THRESHOLD = 37;
int frontobstate=0; 
int backobstate=0;
int frontobstate2=0; 
int backobstate2=0;
Servo servo;
long durationfront;
int  distancefront;
long durationback;
int  distanceback;
void fwrd(){
  digitalWrite(Forwardpin, HIGH);
  }
void rvrse(){
  digitalWrite(Reversepin, HIGH);
  }
void Stopdv(){
   Serial.println("STOP");
   dclear();
   checkobstacle();
   digitalWrite(Forwardpin, LOW);//STOP
   delay(100);
}

void dclear(){
frontobstate=0; 
backobstate=0;
frontobstate2=0; 
backobstate2=0;
}
void setup() {
  pinMode(Forwardpin,    OUTPUT);// Forward
  pinMode(Reversepin,  OUTPUT);// REVERSE
  pinMode(trigfront,     OUTPUT); // Sets the trigPin as an Output
  pinMode(echofront ,    INPUT); // Sets the echoPin as an Input
  pinMode(trigback,      OUTPUT); // Sets the trigPin as an Output
  pinMode(echoback ,     INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  Stopdv();
  
}
void eyesense(){
digitalWrite(trigfront, LOW); // Clears the trigfront this sensor is for front then right
delayMicroseconds(7);
digitalWrite(trigfront, HIGH);// Sets the trigfront on HIGH state for 7 micro seconds
delayMicroseconds(7);
digitalWrite(trigfront, LOW);
delayMicroseconds(3);// Sets the trigfront on LOW state for 7 micro seconds
durationfront = pulseIn(echofront, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
distancefront = durationfront * 0.034 / 2; // Calculating the distancefront or distance right
digitalWrite(trigback, LOW); // Clears the trigback this sensor or for  left
delayMicroseconds(7);
digitalWrite(trigback, HIGH);// Sets the trigback on HIGH state for 7 micro seconds
delayMicroseconds(7);
digitalWrite(trigback, LOW);
delayMicroseconds(3);// Sets the trigback on LOW state for 7 micro seconds
durationback = pulseIn(echoback, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
distanceback = durationback * 0.034 / 2; // Calculating the distanceback or left
}
void drivelogics(){
  //analysis
  //front or right
  if (distancefront <= DISTANCE_THRESHOLD){
    frontobstate=1;
  }
  else{
    frontobstate=0;
    }
  //front or right
  //back or left
  if (distanceback <= DISTANCE_THRESHOLD){
    backobstate=1;
 }
 else{
  backobstate=0;
  }
//back or left
}


void checkobstacle(){
  Serial.println("FINDWAY");
eyesense();
drivelogics();
}
void loop() {
    digitalWrite(Forwardpin, LOW);
  digitalWrite(Reversepin, LOW);
  
  checkobstacle();
 
if(((frontobstate==0) &&  (backobstate==0)) || ((frontobstate==0) &&  (backobstate==1))){
  //checks if there is obstacle in front if no obstacle move forward
  Serial.println("Forward No obstacle");
  fwrd();
  //digitalWrite(Forwardpin, HIGH); // FORWARD
  eyesense();
drivelogics();
  
  
}else if(((frontobstate==1) &&  (backobstate==0)))
{
  digitalWrite(Forwardpin, LOW);
  digitalWrite(Reversepin, HIGH);
  delay(750);
  Serial.println("Forward  obstacle");
  eyesense();
drivelogics();
  
  
}else if (((frontobstate==1) &&  (backobstate==1)))
{
 Serial.println("front and back are blocked");
   digitalWrite(Forwardpin, LOW);
  digitalWrite(Reversepin, LOW);
  eyesense();
  drivelogics();
}else 
{
  digitalWrite(Forwardpin, LOW);
  digitalWrite(Reversepin, LOW);
  eyesense();
  drivelogics();
}

}
    
    






  


  
