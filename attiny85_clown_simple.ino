#define LED_EYE_R 3 // HIGH => on
#define LED_EYE_L 4 // HIGH => on
#define LED_NOSE 1  // LOW => on

void setup() {
  pinMode(LED_EYE_R, OUTPUT);
  pinMode(LED_EYE_L, OUTPUT);
  pinMode(LED_NOSE, OUTPUT);
  digitalWrite(LED_EYE_R, LOW);
  digitalWrite(LED_EYE_L, LOW);
  digitalWrite(LED_NOSE, HIGH);

  digitalWrite(LED_NOSE, LOW); delay(500); digitalWrite(LED_NOSE, HIGH);
  digitalWrite(LED_EYE_L, HIGH); delay(500); digitalWrite(LED_EYE_L, LOW);
  digitalWrite(LED_EYE_R, HIGH); delay(500); digitalWrite(LED_EYE_R, LOW);
}

#define NOSE_FLASH_PERIOD 3000
#define NOSE_FADE_PERIOD 12000
#define NOSE_FADE_CYCLES 4

unsigned long p = 1500L;
void loop() {

  cycleIter();

  // Animate nose
  unsigned long now = millis() % (NOSE_FLASH_PERIOD + NOSE_FADE_PERIOD);
  if (now < NOSE_FLASH_PERIOD) {
    boolean on = (now % 150) < 75;
    analogWrite(LED_NOSE, 255 - (on * 128));
  } else {
    long range1000 = map(now, NOSE_FLASH_PERIOD, (NOSE_FLASH_PERIOD + NOSE_FADE_PERIOD) - 1, 0, 1000L * NOSE_FADE_CYCLES);
    double brightness = abs(cos(range1000 * 0.0031415)); // * PI / 1000
    analogWrite(LED_NOSE, 55 + brightness * 200);
  }

  delay(5);

}




#define CYCLE_STAGES 14
#define CYCLE_STAGE_LENGTH 10000L
void cycleIter() {
  unsigned long now = millis() % (CYCLE_STAGES * CYCLE_STAGE_LENGTH);
  int stage = map(now, 0, (CYCLE_STAGES * CYCLE_STAGE_LENGTH) - 1, 0, CYCLE_STAGES);
  if (stage == CYCLE_STAGES) stage = CYCLE_STAGES - 1; //map doesn't map evenly to the last option
  switch (stage) {
    case 0: blinkIter(p, p / 6); break;
    case 1: winkLeftIter(p, p / 6); break;
    case 2: winkRightIter(p, p / 6); break;
    case 3: doubleBlinkIter(p, p / 6); break;
    case 4: doubleBlinkIter(p, p / 10); break;
    case 5: winkEachIter(2000); break;
    case 6: winkEachIter(750); break;
    case 7: blinkIter(p / 2, p / 6); break;
    case 8: winkLeftIter(p / 2, p / 6); break;
    case 9: winkRightIter(p / 2, p / 6); break;
    case 10: doubleBlinkIter(p / 2, p / 8); break;
    case 11: doubleBlinkIter(p / 2, p / 12); break;
    case 12: winkEachIter(1000); break;
    case 13: winkEachIter(300); break;
  }
}
unsigned long startTs = 0L;
void winkIter(int ledPin, unsigned long period, unsigned long winkDuration, boolean winkCtrl) {
  //  unsigned long now = (millis() - startTs) % period;
  unsigned long now = millis() % period;
  if (now < winkDuration) {
    digitalWrite(ledPin, winkCtrl);
  } else digitalWrite(ledPin, !winkCtrl);
}

void doubleWinkIter(int ledPin, unsigned long period, unsigned long winkDuration, boolean winkCtrl) {
  //  unsigned long now = (millis() - startTs) % period;
  unsigned long now = millis() % period;
  if (now < winkDuration || now > 2 * winkDuration && now < 3 * winkDuration) {
    digitalWrite(ledPin, winkCtrl);
  } else digitalWrite(ledPin, !winkCtrl);
}

void winkLeftIter(unsigned long period, unsigned long winkDuration) {
  winkIter(LED_EYE_L, period, winkDuration, LOW);
  digitalWrite(LED_EYE_R, HIGH);
}

void winkRightIter(unsigned long period, unsigned long winkDuration) {
  winkIter(LED_EYE_R, period, winkDuration, LOW);
  digitalWrite(LED_EYE_L, HIGH);
}

void blinkIter(unsigned long period, unsigned long winkDuration) {
  winkIter(LED_EYE_R, period, winkDuration, LOW);
  winkIter(LED_EYE_L, period, winkDuration, LOW);
}

void doubleBlinkIter(unsigned long period, unsigned long winkDuration) {
  doubleWinkIter(LED_EYE_R, period, winkDuration, LOW);
  doubleWinkIter(LED_EYE_L, period, winkDuration, LOW);
}

void winkEachIter(unsigned long period) {
  unsigned long winkDuration = period / 2;
  unsigned long now = millis() % period;
  if (now < winkDuration) {
    digitalWrite(LED_EYE_R, HIGH);
    digitalWrite(LED_EYE_L, LOW);
  } else {
    digitalWrite(LED_EYE_R, LOW);
    digitalWrite(LED_EYE_L, HIGH);

  }
}

