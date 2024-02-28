void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop() {
  int i = digitalRead(13); 
  Serial.println(i);
  delay(100);                   
 }

