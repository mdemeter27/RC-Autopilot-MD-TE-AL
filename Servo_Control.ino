#include <Servo.h>
//SEROVOS
#define deadStick 3 //How much jitter should be accounted for by 90;
boolean inp_chk;//Checks if there is any input
Servo ail;
#define ailIn_pin 13//Pin input in coming from
int ail_data;//Data PWM is stored in
int ail_out;//angle of servo
Servo ele;
int eleIn_pin = 12;
int ele_data;
int ele_out;
//Servo rud;
//int rudIn_pin = 11;
//int rud_data;
//

//PID
#define Target_Const 0
#define PW 1
#define IW .001
#define DW 1
float integral = 0;
float last = 0;
//

float k = 16.4; //rotation factor normal is 16.4. Determines how much roation when using full stick. The more the less travel
float k2;
void servoSetup() {
  ail.attach(9);//Attach servos
  ele.attach(8);
  //rud.attach(5);
  rotationFactor();

}

void servoLoop() {
  translate();
  //Serial.println();
  //Serial.print(ail_out);
  //Serial.println();
  //Serial.print(ele_out);
  //Serial.println();
  //Serial.print(rud_data);
  //Serial.println();
  output();
}


void rotationFactor() {
  float x, y;
  y = 1450 / k;
  k2 = 90 - y;
 // Serial.print(1450 / k);
  //Serial.println();
  //Serial.print(k2);
  //Serial.println();
  //Serial.print(1450 / k + k2);
}

void translate() {//Take input of pins translate to PWM(Rounded a few)
  // ail_data = (int(pulseIn(ailIn_pin, HIGH) / 1)) * 1;//Make sure no jitter
  // ele_data = (int(pulseIn(eleIn_pin, HIGH)) / 1) * 1;
  // rud_data = (int(pulseIn(rudIn_pin, HIGH)) / 60) * 60;
}

int delta() {
  ail_out = 90 - ((stableize(ele_out, 3)) - 90);
}

int stableize(int n, int _chn) {
  int d = n;
  int chn = _chn;
  if (chn == 2) {
    n = 90 - roll;
    if (n < 65)n = 65;
    if (n > 115)n = 115;
    return n / 1.5 + 30;
  }

  if (chn == 3) {
    n = 90 - pitch;
    if (n < 65)n = 65;
    if (n > 115)n = 115;
    return n / 1.5 + 30;
  }
}

float PID(float value){
  float sum = 0;
  integral+=value-Target_Const;
  sum += PW*(value-Target_Const);
  sum += IW*integral;
  sum += DW*(value-last);
  last = value;
  return sum;
}


void output() {
  ail_out = (ail_data / k) + k2;
  ele_out = (ele_data / k) + k2;
  ail_out = (int)ail_out;
  ele_out = (int)ele_out;
  if (ail_out > 90 - deadStick && ail_out < 90 + deadStick)ail_out = 90;
  if (ele_out > 90 - deadStick && ele_out < 90 + deadStick)ele_out = 90;
  if (ele_out > 90 - deadStick && ele_out < 90 + deadStick && ail_out > 90 - deadStick && ail_out < 90 + deadStick)inp_chk = true;
  //Serial.println(stableize(ail_out, 2)+"   ");
  ail_out=(90-(int)PID(roll));
    if(ail_out<65)ail_out=65;
  if(ail_out>115)ail_out=115;
   Serial.println(ail_out);
  if (inp_chk == true) {
   // ele_out = stableize(ele_out, 3);
    //delta();
    //ail_out=stableize(ail_out,2);
  }
  ail.write(ail_out);
  ele.write(ele_out);
  // rud.write((rud_data / k) + k2);
  inp_chk = false;
}

