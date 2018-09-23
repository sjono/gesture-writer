
/*
 Stepper Motor Test
 Date: 09/20, 8:30pm
 Updates:
    9:30pm - adding joystick analog input
 
 This code spins a stepper motor, using inputs from a joystick
 Original Code from Colin
 */
 
#include <Stepper.h>

/* REF
 * Step C0 C1 C2 C3
 *  1 1 0 1 0
 *  2 0 1 1 0
 *  3 0 1 0 1
 *  4 1 0 0 1
 */
#define P1 5
#define P2 6
#define P3 7
#define P4 8


const int stepsPerRevolution = 200; // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, P1, P2, P3, P4);
int speed = 200; // In Hz
int Mot_en = 10; // pin 10 is a PWM pin on Teensy LC
int sensorPin = 1; // read in Teensy LC A1 (pin 15)
int input = 1;
int step2angle = 0;
int step2max = 3;
int step2min = -3;
int sensorValue = 0;

void setup() {
 
 pinMode(P1, OUTPUT);
 pinMode(P2, OUTPUT);
 pinMode(P3, OUTPUT);
 pinMode(P4, OUTPUT);
 
 pinMode(Mot_en, OUTPUT);
 analogWrite(Mot_en, 255); // 192 is a 75% duty cycle {0 to 255}, 225 works good

 
 // set the speed at 60 rpm:
// myStepper.setSpeed(30);
 // initialize the serial port:
 Serial.begin(9600);
  Serial.println("Serial Initialized");
  // This line sets one side of the H-bridge high and should hold the stepper stationary
 digitalWrite(P1, HIGH);    // sets the digital pin 13 on
 digitalWrite(P2, LOW);    // sets the digital pin 13 off
 digitalWrite(P3, LOW);    // sets the digital pin 13 off
 digitalWrite(P4, LOW);    // sets the digital pin 13 off
 for (int i =0; i<5; i++)
 {
  Serial.print("Starting in ");
  Serial.println(5-i);
  delay(1000);
 }
 
}

void loop() { 
  sensorValue = analogRead(sensorPin);

  // ~~  NEW JOYSTICK STUFF ~~~~~~~ 
        // Listen to joystick
  if (sensorValue > 850){ // check values, if high, turn CW
    input = 1;
  }
  else if (sensorValue < 200){ // if low value, turn opposite
      input = -1;
  }
  else { input = 0;}

  
  if (input){
    Serial.println("Turning motor");
    
    if (step2angle >= step2max){
      step2angle = step2max;
      input = -1;
    }
    else if (step2angle <= step2min){
      step2angle = step2min;
      input = 1;
    }
    stepAngle(); // turns the motor only if input is + or -
      Serial.print("Angle is: ");
  Serial.println(step2angle);
      delay(10);                       // waits 15ms for the servo to reach the position
    }

  // ~~ end NEW STUFF ~~~~~~~ 
    
 // ~~ OLD BORING STUFF ~~~~~~~ 
//    //myStepper.setSpeed(120);
//     Serial.println("clockwise");
//     stepForward(3);
//  //   myStepper.step(1);​
//  delay(1000);
//  
//  Serial.println("counterclockwise");
//  stepBackward(6);
//  delay(1000);
//
//  Serial.println("clockwise");
//     stepForward(3);
//  //   myStepper.step(1);​
//  delay(1000);
  // ~~ end BORING STUFF ~~~~~~~ 
}

void stepAngle() {
  Serial.println(input);
  if (input > 0)
  {
    stepForward(1);
    step2angle = step2angle+1;
    Serial.println("Spins CW");
  }
  else if (input < 0)
  {
    stepBackward(1);
    step2angle = step2angle-1;
    Serial.println("Spins CCW");
  }
  input = 0;
}

void stepForward(int n) {
 int i;
 for (i=0; i < n; i++) {
  step1();
  delay(50);
  step2();
  delay(50);
  step3();
  delay(50);
  step4();
  delay(50);
  }
  holdAngle();
}

void stepBackward(int n) {
 int i;
 for (i=0; i < n; i++) {
  step4();
  delay(50);
  step3();
  delay(50);
  step2();
  delay(50);
  step1();
  delay(50);
 }
 holdAngle();
}

void step1(){ // 1 0 1 0
 digitalWrite(P1, HIGH);    // sets the digital pin 13 on
 digitalWrite(P2, LOW);    // sets the digital pin 13 off
 digitalWrite(P3, HIGH);    // sets the digital pin 13 off
 digitalWrite(P4, LOW);    // sets the digital pin 13 off
}
void step2(){ // 0 1 1 0
 digitalWrite(P1, LOW);    // sets the digital pin 13 on
 digitalWrite(P2, HIGH);    // sets the digital pin 13 off
 digitalWrite(P3, HIGH);    // sets the digital pin 13 off
 digitalWrite(P4, LOW);    // sets the digital pin 13 off
}
void step3(){ // 0 1 0 1
 digitalWrite(P1, LOW);    // sets the digital pin 13 on
 digitalWrite(P2, HIGH);    // sets the digital pin 13 off
 digitalWrite(P3, LOW);    // sets the digital pin 13 off
 digitalWrite(P4, HIGH);    // sets the digital pin 13 off
}
void step4(){ // 1 0 0 1
 digitalWrite(P1, HIGH);    // sets the digital pin 13 on
 digitalWrite(P2, LOW);    // sets the digital pin 13 off
 digitalWrite(P3, LOW);    // sets the digital pin 13 off
 digitalWrite(P4, HIGH);    // sets the digital pin 13 off
}
void holdAngle(){ // 1 0 0 0
 digitalWrite(P1, HIGH);    // sets the digital pin 13 on
 digitalWrite(P2, LOW);    // sets the digital pin 13 off
 digitalWrite(P3, LOW);    // sets the digital pin 13 off
 digitalWrite(P4, LOW);    // sets the digital pin 13 off
}
