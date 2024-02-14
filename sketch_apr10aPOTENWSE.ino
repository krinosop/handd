#include <Servo.h>
//результат нашей тяжелой работы((
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

bool zn1, zn2;
int p = 1;
int porog1 = 10, porog2 = 10;//изменение потенцометром
int emg1 = 0, emg2 = 0;
int amp1 = 0, amp2 = 0;
int poten=0, plus=0,plus1=0;
int min1 = 255, min2 = 255, max1 = 0, max2 = 0;

void funr3(Servo servo, int angle, int sp, int Min, int Max) {
  angle = map(angle, 0, 100, Min, Max);
  if (servo.read() < angle){
    servo.write(servo.read() + min(sp, angle - servo.read()));
  }
  else if (servo.read() > angle){
    servo.write(servo.read() - min(sp, servo.read() - angle));
  }
}

void amp_emg(){
  for (int k = 0; k < 32; k++){
    emg1 = analogRead(A0);
    emg2 = analogRead(A1);
    emg1 = map(emg1, 0, 1023, 0, 255);
    emg2 = map(emg2, 0, 1023, 0, 255);

    if (emg1 > max1){
      max1 = emg1;
    }
    if (emg1 < min1){
      min1 = emg1;
    }
    if (emg2 > max2){
      max2 = emg2;
    }
    if (emg2 < min2){
      min2 = emg2;
    }
  }
  amp1 = 0.3*amp1 + 0.7*(max1 - min1);
  amp2 = 0.3*amp2 + 0.7*(max2 - min2);
 // Serial.print(amp1);
  //Serial.print(" ");
  //Serial.println(amp2);
  min1 = 255;
  min2 = 255;
  max1 = 0;
  max2 = 0;
}

void setup() {
  // put your setup code here, to run once:
  myservo1.write(180); // большой сгиб
  myservo1.attach(3);
  myservo2.write(160); //поворот 180
  myservo2.attach(5);
  myservo3.write(0); // указательный. больше 90, почти сжался там
  myservo3.attach(6);
  myservo4.write(0); // средний чуть больше 100(прибизтельно) относительно третьего, чтобы сжалился
  myservo4.attach(9);
  myservo5.write(180); // мизинец и без имени, чтобы разжалось
  myservo5.attach(10);
}
void loop() {
 amp_emg(); 
 poten=analogRead(3);
 plus=map(poten, 0, 1023, 0, 20);
 plus1=map(poten, 0, 1023, 20, 0);
 constrain(plus, 0, 20);
 
  if (amp1 > porog1+plus1 && amp2 > porog2+plus1) { //кулак
    funr3(myservo1, 100, 2, 180, 80);
    funr3(myservo2, 100, 2, 160, 80);
    funr3(myservo3, 100, 3.5, 0, 160);
    funr3(myservo4, 100, 3.75, 0, 170);
    funr3(myservo5, 100, 3, 180, 30);
  }
  else if(amp1>porog1){ //виктори
  funr3(myservo1, 100, 2, 180, 80);
  funr3(myservo2, 100, 2, 160, 80);
  funr3(myservo3, 0, 3.5, 0, 160);
  funr3(myservo4, 0, 3.75, 0, 170);
  funr3(myservo5, 100, 3, 180, 30);
   }
    else if(amp2>porog2){// окей
  funr3(myservo1, 100, 2, 180, 80);
  funr3(myservo2, 100, 2, 160, 80);
  funr3(myservo3, 100, 3.5, 0, 160);
  funr3(myservo4, 0, 3.75, 0, 170);
  funr3(myservo5, 0, 3, 180, 30);
     }
    else { //ладонь
   funr3(myservo1, 0, 2, 180, 80);
   funr3(myservo2, 0, 2, 160, 80);
   funr3(myservo3, 0, 3.5, 0, 160); //90-30
   funr3(myservo4, 0, 3.75, 0, 170); //75-50
   funr3(myservo5, 0, 3, 180, 30);
  }
  delay(30);
}
