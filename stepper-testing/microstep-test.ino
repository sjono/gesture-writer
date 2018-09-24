/*
 Stepper Microstep Test
 Date: 09/24, 9:30am

 09/24 10:30 am -best performance when del = 25 and the delay in the loop is either <10 or > 50
 
 This code will test if we can spin the stepper motor using 2 microsteps per full step (meaning 400 steps = 1 rev)
 */

 #define P1 5
#define P2 6
#define P3 7
#define P4 8

int Mot_en = 10; // pin 10 is a PWM pin on Teensy LC
int del = 25; // delay for motor signals, best performance at 25 (less = no mvmt, more = fights itself)

void setup() {
 
 pinMode(P1, OUTPUT);
 pinMode(P2, OUTPUT);
 pinMode(P3, OUTPUT);
 pinMode(P4, OUTPUT);
 
 pinMode(Mot_en, OUTPUT);
 analogWrite(Mot_en, 255); // 192 is a 75% duty cycle {0 to 255}, 225 works good


}

void loop() {
  int n = 10;
  for (int i=0; i < n; i++) {
  step1();
  step2();
  step3();
  step4();
  delay(1); // this just changes the speed of the rotation, shouldn't effect lag, bad performance if this is '25'
  }
  delay(5000);

}


// !!!!!!!  OLD FUNCTIONS  !!!!!!!!!!
// ~~~~   maybe not useful for microstepping ?? ~~~~~

void Ahi(){
 digitalWrite(P1, HIGH);    
 digitalWrite(P2, LOW);
}

void Alo(){
 digitalWrite(P1, LOW);    
 digitalWrite(P2, HIGH);
}

void Aoff(){
   digitalWrite(P1, HIGH);    
 digitalWrite(P2, HIGH);
}

void Bhi(){
 digitalWrite(P3, HIGH);    
 digitalWrite(P4, LOW);  
}

void Blo(){
 digitalWrite(P3, LOW);   
 digitalWrite(P4, HIGH); 
}

void Boff(){
 digitalWrite(P3, HIGH);   
 digitalWrite(P4, HIGH); 
}

void step1(){ // 1 0 1 0
  Ahi(); 
  Bhi();
  delay(del);
}
void step2(){ // 0 1 1 0
  Alo(); 
  Bhi(); 
    delay(del);
}
void step3(){ // 0 1 0 1
  Alo(); 
  Blo();
    delay(del);
}
void step4(){ // 1 0 0 1
  Ahi(); 
  Blo();
    delay(del);
}
