 #include <SimpleFOC.h>

BLDCMotor motor = BLDCMotor(7, 0.025); // br3536 1200kv
//BLDCMotor motor = BLDCMotor(7, 0.033); // br3536 950kv
BLDCDriver6PWM driver = BLDCDriver6PWM(A_PHASE_UH, A_PHASE_UL, A_PHASE_VH, A_PHASE_VL, A_PHASE_WH, A_PHASE_WL);

float target_position = 0;

Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_position, cmd); }
void doLimit(char* cmd) { command.scalar(&motor.voltage_limit, cmd); }
void doVelocity(char* cmd) { command.scalar(&motor.velocity_limit, cmd); }

void setup() {
  driver.voltage_power_supply = 12;
  driver.voltage_limit = 12;
  driver.init();
  motor.linkDriver(&driver);

  motor.voltage_limit = 12;   // [V]
  motor.velocity_limit = 30; // [rad/s] cca 50rpm
  motor.current_limit = 15;
  motor.controller = MotionControlType::angle_openloop;

  motor.init();

  command.add('T', doTarget, "target angle");
  command.add('L', doLimit, "voltage limit");
  command.add('V', doLimit, "movement velocity");

  Serial.begin(115200);
  Serial.println("Motor ready!");
  Serial.println("Set target position [rad]");
  _delay(1000);
}

void loop() {
  motor.move(target_position);
  command.run();
}