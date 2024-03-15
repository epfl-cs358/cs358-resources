void setup() {}

int stepper_pins[4] = {8,9,10,11};

int phase_pattern[][4] = {
  {1,0,0,0},
  {0,1,0,0},
  {0,0,1,0},
  {0,0,0,1}
};

void step(bool forward){
  static unsigned current_step = 0;
    
  if(forward) current_step = (current_step + 1) % 4;
  else current_step = (current_step - 1) % 4;

  for(int i=0; i<4; i++)
    digitalWrite(stepper_pins[i], phase_pattern[current_step][i]);
}

void loop() {
  delayMicroseconds(3000); // tune this. 1800 is the smallest delay that worked for me
  step(true);
}

