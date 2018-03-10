#include <IRremote.h>

int RECV_PIN = 5;
int motorOFF = 4;

int timepause = 200; //mikro
int holdTime = 1000; //milli
long numberWhole = 110000;
long numberHalf = 61000;
long currentStep = 0;


IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;
 

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(motorOFF, OUTPUT);
  digitalWrite(motorOFF, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}


void motorRull(decode_results *results) {
long MOTOR_UP =  1587632295; //volum opp
long MOTOR_DOWN = 1587664935; //volum ned
long MOTOR_HALF = 1587673350;  // pil venstre
long MOTOR_ON = 1587640710;  //pil høyre

  if (results->value == REPEAT) {
    //Serial.println("Jeg vil ikke repetere");
    return;
  }
  if (results->value == MOTOR_UP){
    if (currentStep == numberHalf){
      //Serial.println("motoren gar opp, Halv");
      digitalWrite(8, HIGH);
      digitalWrite(motorOFF, LOW);
      delay(holdTime);
      for (long i=0; i < (numberWhole - numberHalf); i++){
        digitalWrite(9, HIGH);
        delayMicroseconds(timepause);          
        digitalWrite(9, LOW); 
        delayMicroseconds(timepause);
      }
      delay(holdTime);
      //Serial.println(currentStep);
      currentStep = numberWhole;
      //Serial.println(currentStep);
      digitalWrite(motorOFF, HIGH);
    }
    if (currentStep == 0){
      //Serial.println("motoren gar opp, Hel");
      digitalWrite(8, HIGH);
      digitalWrite(motorOFF, LOW);
      delay(holdTime);
      for (long i=0; i < numberWhole; i++){
        digitalWrite(9, HIGH);
        delayMicroseconds(timepause);          
        digitalWrite(9, LOW); 
        delayMicroseconds(timepause);
      }
      delay(holdTime);
      //Serial.println(currentStep);
      currentStep = numberWhole;
      //Serial.println(currentStep);
      digitalWrite(motorOFF, HIGH);
    }
    else {
      return;
    }
  }

  
  if (results->value == MOTOR_DOWN){
    if (currentStep == numberHalf){
      //Serial.println("motoren gar ned, halv");
      digitalWrite(8, LOW);
      digitalWrite(motorOFF, LOW);
      delay(holdTime);
      for (long i=0; i < numberHalf; i++){
        digitalWrite(9, HIGH);
        delayMicroseconds(timepause);          
        digitalWrite(9, LOW); 
        delayMicroseconds(timepause);
      }
      delay(holdTime);
      //Serial.println(currentStep);
      currentStep = 0;
      //Serial.println(currentStep);
      digitalWrite(motorOFF, HIGH);
    }
    else if (currentStep == numberWhole){
      //Serial.println("motoren gar ned, Hel");
      digitalWrite(8, LOW);
      digitalWrite(motorOFF, LOW);
      delay(holdTime);
      for (long i=0; i < numberWhole; i++){
        digitalWrite(9, HIGH);
        delayMicroseconds(timepause);          
        digitalWrite(9, LOW); 
        delayMicroseconds(timepause);
      }
      delay(holdTime);                  
      //Serial.println(currentStep);
      currentStep = 0;
      //Serial.println(currentStep);
      digitalWrite(motorOFF, HIGH);
    }
    else{
      return;
    }
  }

  
  if (results->value == MOTOR_HALF){
    if (currentStep == 0){
      //Serial.println("motoren gar halv, opp");
      digitalWrite(8, HIGH);
      digitalWrite(motorOFF, LOW);
      delay(holdTime);
      for (long i=0; i < numberHalf; i++){
        digitalWrite(9, HIGH);
        delayMicroseconds(timepause);          
        digitalWrite(9, LOW); 
        delayMicroseconds(timepause);
      }
      delay(holdTime);
      //Serial.println(currentStep);
      currentStep = numberHalf;
      //Serial.println(currentStep);
      digitalWrite(motorOFF, HIGH);
      
    }
    else if (currentStep == numberWhole){
      //Serial.println("motoren gar halv, ned");
      digitalWrite(8, LOW);
      digitalWrite(motorOFF, LOW);
      delay(holdTime);
      for (long i=0; i < (numberWhole - numberHalf); i++){
        digitalWrite(9, HIGH);
        delayMicroseconds(timepause);          
        digitalWrite(9, LOW); 
        delayMicroseconds(timepause);
      }
      delay(holdTime);
      //Serial.println(currentStep);
      currentStep = numberHalf;
      //Serial.println(currentStep);
      digitalWrite(motorOFF, HIGH);
    }
    else{
      return;
    }

  }
  if (results->value == MOTOR_ON){
  //Serial.println("motoren paa");
  digitalWrite(motorOFF, LOW);
  }
}



void loop() {
  if (irrecv.decode(&results)) {
    motorRull(&results);
    irrecv.resume(); // resume receiver
  }
}
