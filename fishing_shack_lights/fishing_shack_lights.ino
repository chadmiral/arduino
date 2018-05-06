/*
Adafruit Arduino - Lesson 3. RGB LED
// Red : > 120 ohm resistor
// Green: > 82 ohm resistor
// Blue: > 82 ohm resistor
*/

class Color
{
  public:
    Color()
    {
      r = 0.0f;
      g = 0.0f;
      b = 0.0f;
    }
    Color(float red, float green, float blue)
    {
      r = red;
      g = green;
      b = blue;
    }

    void randomize() {
      r = random(0.0f, 255.0f);
      g = random(0.0f, 255.0f);
      b = random(0.0f, 255.0f);
    }
    
    float r;
    float g;
    float b;
};

Color COLOR_BLACK(0.0f, 0.0f, 0.0f);
Color COLOR_WHITE(255.0f, 255.0f, 255.0f);
Color COLOR_RED(255.0f, 0.0f, 0.0f);
Color COLOR_GREEN(0.0f, 255.0f, 0.0f);
Color COLOR_BLUE(0.0f, 0.0f, 255.0f);
Color COLOR_INCANDESCENT(255.0f, 140.0f, 30.0f);
Color COLOR_HALOGEN(200.0f, 255.0f, 200.0f);

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

  Serial.begin(9600);
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
  delay(random(5000.0f, 50000.0f));
  setColor(COLOR_BLACK);
  delay(random(5000.0f, 50000.0f));
}

void fireplaceLight()
{
  Color flame[3];
  flame[0].r = 255.0f;
  flame[0].g = 130.0f;
  flame[0].b = 20.0f;

  flame[1].r = 0.8f * 200.0f;
  flame[1].g = 0.8f * 60.0f;
  flame[1].b = 0.8f * 0.0f;

  //darker red
  flame[2].r = 120.0f;
  flame[2].g = 30.0f;
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

void danceParty()
{
  //strobe light
  int mode = random(0, 2);
  int loops = pow(4, (int)random(1, 3));
  int pow4;
  int num_loops;

  Color rc;
  rc.randomize();
  for(int i = 0; i < loops; i++) {
    switch(mode) {
      case 0:
        setColor(rc);
        delay(10);
        setColor(COLOR_BLACK);
        delay(300);
        break;
  
       case 1:
          pow4 = (int)pow(4.0f, (int)random(1, 3));
          for(int j = 0; j < pow4; j++)
          {
            rc.randomize();
            int freq = pow(10, (int)random(1, 3));
            setColor(rc);
            delay(freq);
            setColor(COLOR_BLACK);
            delay(0);
          }
          break;
       case 2:
       num_loops = 500;
       rc = Color(random(0.0f, 255.0f),random(0.0f, 255.0f), random(0.0f, 255.0f));
       for(int j = 0; j < num_loops; j++) {
        float brightness = 0.5f * (sin(360.0f * (float)j / (float)num_loops) + 1.0f);

        Color out_c(brightness * rc.r, brightness * rc.g, brightness * rc.b);
        setColor(out_c);
        delay(50);
       }
       break;
       default:
        break;
    }
  } 
}

void loop()
{
  //televisionLight();
  //flickerLight(COLOR_HALOGEN);
  //periodicLight(COLOR_INCANDESCENT);
  //fireplaceLight();
  danceParty();
}
