#include <SimpleFOC.h>

//BLDCMotor motor = BLDCMotor(7, 0.033);  // br3536 kv950
BLDCMotor motor = BLDCMotor(7, 0.025);  // br3536 kv1200
//BLDCMotor motor = BLDCMotor(14, 0.27);  // t-motor mn5008 kv170
//BLDCMotor motor = BLDCMotor(20, 0.055); // Eaglepower 8318 kv100


// STM32 B_G431B_ESC1
BLDCDriver6PWM driver = BLDCDriver6PWM(A_PHASE_UH, A_PHASE_UL, A_PHASE_VH, A_PHASE_VL, A_PHASE_WH, A_PHASE_WL);
LowsideCurrentSense currentSense = LowsideCurrentSense(0.003f, -64.0f/7.0f, A_OP1_OUT, A_OP2_OUT, A_OP3_OUT);

Encoder encoder = Encoder(A_HALL1, A_HALL2, 2048); // CUI AMT 102V/103V

void doA(){encoder.handleA();}
void doB(){encoder.handleB();}

Commander command = Commander(Serial);
void doTarget(char* cmd) { command.motion(&motor, cmd); }

void setup() {

  encoder.init();
  encoder.enableInterrupts(doA, doB); 
  motor.linkSensor(&encoder);
  
  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);
  currentSense.linkDriver(&driver);

  currentSense.init();
  currentSense.skip_align = true;
  motor.linkCurrentSense(&currentSense);

  motor.controller = MotionControlType::angle;

  motor.voltage_limit = 12;
  motor.current_limit = 35;
  motor.velocity_limit = 1000;

  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor.PID_velocity.output_ramp = 1000;
  motor.LPF_velocity.Tf = 0.01;
  motor.P_angle.P = 20;

  motor.target = 0;

  Serial.begin(115200);
  motor.useMonitoring(Serial);

  motor.init();
  motor.initFOC();

  command.add('T', doTarget, "target angle");

  Serial.println(F("Motor ready."));
  Serial.println(F("Set the target angle using serial terminal:"));
  _delay(1000);
}

void loop() {
  motor.loopFOC();
  motor.move();
  command.run();
}


