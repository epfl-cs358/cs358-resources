void setup() {}

// Connect input pins 1 to 4 of the ULN2003 stepper driver to pins 8-11 of
// your Arduino Uno.
int stepper_pins[4] = {8,9,10,11};

int phase_pattern[][4] = {
  {1,0,0,0},
  {0,1,0,0},
  {0,0,1,0},
  {0,0,0,1}
};

// Make one step either forward or backward.
// You need to wait a little before doing the next step.
void step(bool forward){
  static unsigned current_step = 0;
    
  if(forward) current_step = (current_step + 1) % 4;
  else current_step = (current_step - 1) % 4;

  for(int i=0; i<4; i++)
    digitalWrite(stepper_pins[i], phase_pattern[current_step][i]);
}

void loop() {
  // Tune this. 1800 is the smallest delay that worked for me.
  // Lower numbers make the stepper faster, but if you go to low, movement
  // may become erratic/unreliable.
  delayMicroseconds(3000);

  step(true);
}

