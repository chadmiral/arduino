
int light_sensor_output = 0;
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  
  // initialize the digital pin as an output.
  pinMode(light_sensor_output, INPUT);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  delay(100);
  
  float value = analogRead(light_sensor_output);
  Serial.println(value);
}
