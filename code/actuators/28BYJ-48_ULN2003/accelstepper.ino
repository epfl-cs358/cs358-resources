#include <AccelStepper.h>
#include <MultiStepper.h>
#define MotorInterfaceType 4

// Connect pins 1-4 of two ULN2003 stepper drivers, the first to pins 8-11 and
// the second to pins 2-5 of the Arduino Uno, respectively. (The permutations
// of the pin orders below are idiosyncrasies of the software library; ignore
// these permuted orders and wire pins in ascending order.)
AccelStepper X(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper Y(MotorInterfaceType, 2, 4, 3, 5);
MultiStepper XY;

long pos_xy[2] = {0,0};
long pos_xya[5][2] = {{0,0}, {4000, 0}, {0, 4000}, {4000, 4000}, {0, 0}};


void setup() {
  X.setMaxSpeed(500.0);
  Y.setMaxSpeed(500.0);

  XY.addStepper(X);
  XY.addStepper(Y);

  Serial.begin(9600);
}


/*
// execute a drawing by moving through the sequence of positions stored in
// the array pos_xya[][].
void loop() {
  int i = 0;
  delay(2000);

  for(i = 0; i < 5; i++) {
    XY.moveTo(pos_xya[i]);
    while (X.distanceToGo() != 0) {
      XY.runSpeedToPosition();
    }
  }
}
*/


// Enter coordinates through the serial interface, e.g. "1000 5000" followed by
// hitting the enter button.
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


