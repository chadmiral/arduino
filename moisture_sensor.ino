int moisture_sensor_pin = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(moisture_sensor_pin, INPUT);
}

void loop()
{
  delay(500);
  float value = analogRead(moisture_sensor_pin);

  Serial.print("soil moisture: ");
  Serial.println(value);
}

