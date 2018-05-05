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

Color COLOR_BLACK;
Color Incandescent;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

float tv_r = 0.0f;
float tv_g = 0.0f;
float tv_b = 0.0f;

Color fireplace;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Incandescent.r = 255.0f;
  Incandescent.g = 140.0f;
  Incandescent.b = 30.0f;

  COLOR_BLACK.r = 0.0f;
  COLOR_BLACK.g = 0.0f;
  COLOR_BLACK.b = 0.0f;
}

void setColor(Color c)
{
  analogWrite(redPin, 255 - c.r);
  analogWrite(greenPin, 255 - c.g);
  analogWrite(bluePin, 255 - c.b);
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
    Color c;
    c.r = mix(tv_r, r_next, mix_val);
    c.g = mix(tv_g, g_next, mix_val);
    c.b = mix(tv_b, b_next, mix_val);

    setColor(c);
    delay(10.0);
  }

  tv_r = r_next;
  tv_g = g_next;
  tv_b = b_next;
}

// as if someone keeps going in a room and turning on / off a light
void periodicLight(Color c)
{
  setColor(c);
  delay(random(2000.0f, 10000.0f));
  setColor(COLOR_BLACK);
  delay(random(2000.0f, 10000.0f));
}

void fireplaceLight()
{
  Color flame[3];
  flame[0].r = 255.0f;
  flame[0].g = 180.0f;
  flame[0].b = 40.0f;

  flame[1].r = 200.0f;
  flame[1].g = 100.0f;
  flame[1].b = 0.0f;

  flame[2].r = 255.0f;
  flame[2].g = 60.0f;
  flame[2].b = 0.0f;

  Color prev = fireplace;
  Color next = flame[(int)random(0, 3)];

  float brightness = 1.0f;//random(0.7f, 1.0f);

  next.r = next.r * brightness;
  next.g = next.g * brightness;
  next.b = next.b * brightness;

  int steps = random(20, 100);
  for(int i = 0; i < steps; i++) {
    Color c;
    float mix_val = (float)i / (float)steps;
    c.r = mix(prev.r, next.r, mix_val);
    c.g = mix(prev.g, next.g, mix_val);
    c.b = mix(prev.b, next.b, mix_val);
    setColor(c);
    delay(4.0f);
  }
  fireplace = next;
}

void flickerLight(Color c)
{
  setColor(c);
  delay(random(200.0f, 1200.0f));
  setColor(COLOR_BLACK);
  delay(random(20.0f, 100.0f));
}

void loop()
{
  //televisionLight();
  //flickerLight(255.0f, 255.0f, 255.0f);
  //periodicLight(Incandescent);
  fireplaceLight();
}
