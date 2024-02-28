#include <AccelStepper.h>
#include <MultiStepper.h>
#define MotorInterfaceType 4

AccelStepper X(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper Y(MotorInterfaceType, 2, 4, 3, 5);
MultiStepper XY;

long pos_xy[2] = {0,0};
long pos_xya[5][2] = {{0,0}, {4000, 0}, {0, 4000}, {4000, 4000}, {0, 0}};


void abc() {
  int i = 0;
  for(i = 0; i < 5; i++) {
    while (X.distanceToGo() != 0) { delay(10); }
    XY.moveTo(pos_xya[i]);
    XY.runSpeedToPosition();
  }
}


void setup() {
	X.setMaxSpeed(500.0);
	Y.setMaxSpeed(500.0);

  XY.addStepper(X);
  XY.addStepper(Y);

  Serial.begin(9600);
}




void loop() {
  delay(2000);
  abc();
}


/*
void loop() {

  if (X.distanceToGo() == 0) {
     while (Serial.available() == 0) {}

     String s;
     pos_xy[0] = Serial.parseInt();
     pos_xy[1] = Serial.parseInt();
     s = Serial.readString();
     Serial.print("x = ");
     Serial.print(pos_xy[0]);
     Serial.print("  y = ");
     Serial.print(pos_xy[1]);
     Serial.println(s);
     XY.moveTo(pos_xy);
  }

  XY.runSpeedToPosition();
}
*/


