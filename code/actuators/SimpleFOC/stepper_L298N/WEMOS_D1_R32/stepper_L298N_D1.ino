// Use a WEMOS D1 R32 board

#include <SimpleFOC.h>

StepperMotor motor = StepperMotor(50); // always 50 pole pairs

// WEMOS D1 pins 16, 27, 12, 13, 14, 5 to
// L298N in1, in2, in3, in4, enA, enB
StepperDriver4PWM driver = StepperDriver4PWM(16, 27, 12, 13, 14, 5);

// CUI AMT 102V/103V output pins A,B to WEMOS D1 pins 39, 36
Encoder encoder = Encoder(39, 36, 2048);

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

  motor.controller = MotionControlType::angle;
//  motor.controller = MotionControlType::angle_openloop;
//  motor.controller = MotionControlType::velocity_openloop;

  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor.PID_velocity.D = 0;
  motor.LPF_velocity.Tf = 0.01;

  motor.voltage_limit = 12;
  motor.current_limit = 18;
  motor.P_angle.P = 20;
  motor.velocity_limit = 100;

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
