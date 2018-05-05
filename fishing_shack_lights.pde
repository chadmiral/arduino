/*
Adafruit Arduino - Lesson 3. RGB LED
// Red : > 120 ohm resistor
// Green: > 82 ohm resistor
// Blue: > 82 ohm resistor
*/

class Color
{
  public:
    float r;
    float g;
    float b;
};

Color Incandescent;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

float tv_r = 0.0f;
float tv_g = 0.0f;
float tv_b = 0.0f;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Incandescent.r = 255.0f;
  Incandescent.g = 140.0f;
  Incandescent.b = 30.0f;
}

void setColor(int red, int green, int blue)
{

  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

float mix(float x, float y, float m)
{
  return (x * (1.0f - m) + y * m);
}

void televisionLight()
{
  float brightness = 2.0f;
  int steps = random(5, 80);

  float r_next = brightness * random(150.0f, 255.0f);
  float g_next = brightness * random(150.0f, 255.0f);
  float b_next = brightness * random(150.0f, 255.0f);

  for(int i = 0; i < steps; i++)
  {
    float mix_val = (float)i / (float)steps;
    float r = mix(tv_r, r_next, mix_val);
    float g = mix(tv_g, g_next, mix_val);
    float b = mix(tv_b, b_next, mix_val);

    setColor(r, g, b);
    delay(10.0);
  }

  tv_r = r_next;
  tv_g = g_next;
  tv_b = b_next;
}

// as if someone keeps going in a room and turning on / off a light
void periodicLight(Color c)
{
  setColor(c.r, c.g, c.b);
  delay(random(2000.0f, 10000.0f));
  setColor(0.0f, 0.0f, 0.0f);
  delay(random(2000.0f, 10000.0f));
}

void flickerLight(float r, float g, float b)
{
  setColor(r, g, b);
  delay(random(200.0f, 1200.0f));
  setColor(0.0f, 0.0f, 0.0f);
  delay(random(20.0f, 100.0f));
}

void loop()
{
  //televisionLight();
  //flickerLight(255.0f, 255.0f, 255.0f);
  periodicLight(Incandescent);
}
