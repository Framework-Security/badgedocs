#include <Adafruit_NeoPixel.h>

#define LED_PIN 5
#define BUTTON_PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, LED_PIN, NEO_GRB + NEO_KHZ800);
bool buttonPressed = false;
int arr[] = { 9, 10, 8, 11, 7, 12, 6, 13, 5, 14, 4, 15, 3, 16, 2, 17, 1, 18, 0, 19 };
bool buttonState = LOW;
bool lastButtonState = LOW;
unsigned long buttonPressTime = 0;

void allon();
void alloff();
void phase1();
void phase2();
void phase3();
void phase4();
void phase5();
void cycleColors();
void endwipe();
void endwipe();

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 20; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));  // Red
      strip.show();
      delay(10);
      strip.setPixelColor(i, strip.Color(0, 255, 0));  // Green
      strip.show();
      delay(10);
      strip.setPixelColor(i, strip.Color(0, 0, 255));  // Blue
      strip.show();
      delay(10);
      strip.setPixelColor(i, strip.Color(0, 0, 0));  // Off
      strip.show();
    }
  }
}

void loop() {
  buttonPressed = digitalRead(BUTTON_PIN) == LOW;
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH && lastButtonState == LOW) {
    buttonPressTime = millis();
  }
  if (buttonState == HIGH && (millis() - buttonPressTime >= 2000)) {
    for (int i = 0; i < 250; i++) {
      fadeColors(strip.Color(255, 0, 0), strip.Color(127, 127, 0));
      fadeColors(strip.Color(127, 127, 0), strip.Color(255, 87, 51));
      fadeColors(strip.Color(255, 87, 51), strip.Color(0, 255, 0));
      fadeColors(strip.Color(0, 255, 0), strip.Color(0, 0, 255));
      fadeColors(strip.Color(0, 0, 255), strip.Color(128, 0, 128));
      fadeColors(strip.Color(128, 0, 128), strip.Color(127, 127, 0));
      fadeColors(strip.Color(255, 215, 0), strip.Color(255, 0, 0));
    }
  }
  lastButtonState = buttonState;

  if (!buttonPressed) {
    int num = random(100);
    //int num = 100;
    Serial.println(num);
    num = (num + 5 - 1) / 5;
    Serial.println(num);

    if (num == 20) {  //win
      phase1();
      phase2();
      phase3();
      phase4();
      phase5();
      delay(5000);

      endwipe();
      alloff();
    }  //end of win

    else {
      if (random(5) == 1) {
        for (int i = 0; i < num; i++) {
          if (i > 15) {
            strip.setPixelColor(arr[i], strip.Color(random(128), random(128), random(128)));
            strip.show();
            delay(600);
          } else if (i > 10) {
            strip.setPixelColor(arr[i], strip.Color(random(128), random(128), random(128)));
            strip.show();
            delay(300);
          } else {
            strip.setPixelColor(arr[i], strip.Color(random(128), random(128), random(128)));
            strip.show();
            delay(100);
          }
        }
      } else {
        for (int i = 0; i < num; i++) {
          if (i > 15) {
            strip.setPixelColor(arr[i], strip.Color(128, 128, 128));
            strip.show();
            delay(600);
          } else if (i > 10) {
            strip.setPixelColor(arr[i], strip.Color(128, 128, 128));
            strip.show();
            delay(300);
          } else {
            strip.setPixelColor(arr[i], strip.Color(128, 128, 128));
            strip.show();
            delay(100);
          }
        }
      }
      delay(1000);
      for (int i = num; i >= 0; i--) {
        strip.setPixelColor(arr[i], strip.Color(0, 0, 0));  // Off
        strip.show();
        delay(50);
      }
      strip.setPixelColor(arr[0], strip.Color(0, 0, 0));  // Off
      strip.show();
    }
  }
}

void allon() {
  for (int i = 0; i < 20; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
    strip.show();
  }
}

void alloff() {
  for (int i = 0; i < 20; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
  }
}

void phase1() {
  for (int i = 0; i < 20; i++) {
    if (i > 15) {
      strip.setPixelColor(arr[i], strip.Color(128, 128, 128));
      strip.show();
      delay(600);
    } else if (i > 10) {
      strip.setPixelColor(arr[i], strip.Color(128, 128, 128));
      strip.show();
      delay(300);
    } else {
      strip.setPixelColor(arr[i], strip.Color(128, 128, 128));
      strip.show();
      delay(100);
    }
  }
}

void phase2() {
  for (int i = 0; i < 3; i++) {
    alloff();
    delay(300);
    allon();
    delay(300);
  }
  for (int i = 0; i < 5; i++) {
    alloff();
    delay(150);
    allon();
    delay(150);
  }
  for (int i = 0; i < 10; i++) {
    alloff();
    delay(50);
    allon();
    delay(50);
  }
}
void phase3() {
  for (int j = 0; j < 15; j++) {
    for (int i = 0; i < 20; i++) {
      strip.setPixelColor(arr[i], strip.Color(255, 0, 0));
      strip.show();
    }
    delay(100);
    for (int i = 0; i < 20; i++) {
      strip.setPixelColor(arr[i], strip.Color(0, 255, 0));
      strip.show();
    }
    delay(100);
    for (int i = 0; i < 20; i++) {
      strip.setPixelColor(arr[i], strip.Color(0, 0, 255));
      strip.show();
    }
    delay(100);
  }
}
void phase4() {
  for (int j = 0; j < 3; j++) {
    for (int i = 20; i >= 0; i--) {
      if (i % 3 == 0) {
        strip.setPixelColor(arr[i], strip.Color(255, 0, 0));
        strip.show();
      }
      if (i % 3 == 2) {
        strip.setPixelColor(arr[i], strip.Color(0, 255, 0));
        strip.show();
      }
      if (i % 3 == 1) {
        strip.setPixelColor(arr[i], strip.Color(0, 0, 255));
        strip.show();
      }
      delay(100);
    }
    if (j % 2 == 1) {
      for (int i = 0; i < 20; i++) {
        strip.setPixelColor(i, strip.Color(255, 105, 180));
        strip.show();
        delay(25);
      }
    } else {
      for (int i = 20; i >= 0; i--) {
        strip.setPixelColor(i, strip.Color(255, 215, 0));
        strip.show();
        delay(25);
      }
    }
  }
}

void fadeColors(uint32_t color1, uint32_t color2) {

  int r1 = (color1 >> 16) & 0xFF;
  int g1 = (color1 >> 8) & 0xFF;
  int b1 = color1 & 0xFF;

  int r2 = (color2 >> 16) & 0xFF;
  int g2 = (color2 >> 8) & 0xFF;
  int b2 = color2 & 0xFF;

  for (int j = 0; j <= 255; j++) {
    int r = r1 + ((r2 - r1) * j / 255);
    int g = g1 + ((g2 - g1) * j / 255);
    int b = b1 + ((b2 - b1) * j / 255);

    for (int i = 0; i <= strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
    delay(10);  //this line is kinda cool, make it shorter for faster fades
  }
}
void phase5() {
  for (int j = 0; j <= 35; j++) {
    for (int i = 0; i <= 20; i++) {
      if (j % 2 == 0) {
        if (i % 2 == 0) {
          strip.setPixelColor(i, strip.Color(0, 128, 0));
        } else {
          strip.setPixelColor(i, strip.Color(128, 0, 128));
        }
      } else {
        if (i % 2 == 0) {
          strip.setPixelColor(i, strip.Color(128, 0, 128));
        } else {
          strip.setPixelColor(i, strip.Color(0, 128, 0));
        }
      }
    }
    strip.show();
    delay(200);
  }
}
void endwipe() {
  for (int i = 0; i <= 20; i++) {
    strip.setPixelColor(i, strip.Color(128, 0, 0));
    strip.show();
    delay(150);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}