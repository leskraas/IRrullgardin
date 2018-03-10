#include <Stepper.h>
#include <IRremote.h>

int RECV_PIN = 5;

int in1Pin = 9;
int in2Pin = 8;
int motorEnable = 4;


#define STEPS 200
#define LENGDE 2000


IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

Stepper motor(STEPS, in1Pin, in2Pin); 

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(motorEnable, OUTPUT);


  while (!Serial);
  motor.setSpeed(600);
  //digitalWrite(motorEnable, HIGH);
}


void motorRull(decode_results *results) {
long MOTOR_UP =  1587632295;
long MOTOR_DOWN =1587664935; 
long MOTOR_OF = 1587631530;
  Serial.print("Received: ");
  Serial.println(results->value);
  if (results->value == REPEAT) {
    Serial.println("Jeg vil ikke repetere");
    return;
  }
  //Serial.println(results->value);
  //Serial.println(results->value, HEX);
  if (results->value == MOTOR_UP){
    Serial.println("motoren gar opp");
    motor.step(LENGDE);
  }
    if (results->value == MOTOR_OF){
    Serial.println("motoren av");
    digitalWrite(motorEnable, LOW);
  }
    if (results->value == MOTOR_DOWN){
    Serial.println("motoren gar ned");
    motor.step(-LENGDE);
  }
}



void loop() {
  if (irrecv.decode(&results)) {
    motorRull(&results);
    irrecv.resume(); // resume receiver
  }
}

