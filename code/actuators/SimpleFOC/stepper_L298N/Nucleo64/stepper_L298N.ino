// Use a Nucleo 64 board: compatible to Arduino Uno but faster.
// MCU speed matters for FOC.

#include <SimpleFOC.h>

StepperMotor motor = StepperMotor(50); // always 50 pole pairs

// The pins on the Nucleo64 board are as for the Arduino Uno
StepperDriver4PWM driver = StepperDriver4PWM(5, 6, 9, 10,  8, 7);

// CUI AMT 102V/103V output pins A,B to Arduino Uno pins D2, D3
Encoder encoder = Encoder(2, 3, 2048);

void doA(){encoder.handleA();}
void doB(){encoder.handleB();}
Commander command = Commander(Serial);
void onMotor(char* cmd){ command.motor(&motor, cmd); }


void setup() {
  encoder.quadrature = Quadrature::ON; // this is the default
  encoder.pullup = Pullup::USE_EXTERN;
  encoder.init();
  encoder.enableInterrupts(doA, doB); 
  motor.linkSensor(&encoder);

  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;

  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);

  // set control loop type to be used
  motor.controller = MotionControlType::angle;

  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor.PID_velocity.D = 0;
  motor.LPF_velocity.Tf = 0.01;

  motor.voltage_limit = 12;
  motor.current_limit = 18;
  motor.P_angle.P = 20;
  motor.velocity_limit = 50;
  
  Serial.begin(115200);
  motor.useMonitoring(Serial);

  motor.init();
  motor.initFOC();
  motor.target = 0;
  command.add('M', onMotor, "motor");
  _delay(1000);
}


void loop() {
  motor.loopFOC();
  motor.move();
  command.run();
}
