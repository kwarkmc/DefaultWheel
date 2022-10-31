//NURI ROBOT
//Arduino Uno
//PWM, Direction, Brake
//V3.0

#include <TimerOne.h>
#include <MsTimer2.h>

int PWM = 9; //PWM, Pin 9
int Direction = 4; //Direction, Pin 4
int Brake = 2; //Brake, Pin 2
int Slope = 5; //Slope step 1~10
volatile int DutyRef = 0; //PWM duty reference -1024~1024(-100%~100%)
volatile int Duty = 0;

void flash() {
  if(Duty < DutyRef) Duty++;
  else if(Duty > DutyRef) Duty--;

  if(Duty > 0) {
    Timer1.setPwmDuty(PWM, Duty); //PWM, Duty
    digitalWrite(Direction, LOW); //Direction, '0'
  }
  else if(Duty < 0) {
    Timer1.setPwmDuty(PWM, -1*Duty); //PWM, Duty
    digitalWrite(Direction, HIGH); //Direction, '1'
  }
}

void setup() {
  //PWM
  Timer1.initialize(); //Timer1
  Timer1.pwm(PWM, 0); //PWM, Duty 0%
  Timer1.setPeriod(50); //PWM period 20kHz
  Timer1.setPwmDuty(PWM, 0); //PWM, Duty 0%

  //Direction
  pinMode(Direction, OUTPUT); //Direction, Output
  digitalWrite(Direction, LOW); //Direction, '0'

  //Brake
  pinMode(Brake, OUTPUT); //Brake, Output
  digitalWrite(Brake, LOW); //Brake, '0'

  //Timer interrupt
  MsTimer2::set(10/Slope, flash); //Timer interrupt period
  MsTimer2::start(); //Timer interrupt start
}

void loop() {
  DutyRef = 1000; //PWM duty reference -1024~1024(-100%~100%)
  delay(5000); //Delay 5s
  
  DutyRef = -1000; //PWM duty reference -1024~1024(-100%~100%)
  delay(5000); //Delay 5s
}
