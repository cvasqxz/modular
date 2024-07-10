int interruptPin = 2;

int pwmPin = 9;
int pwmValue = 0;

int pwmAttackChange = 3;
int pwmDecayChange = 10;
int pwmReleaseChange = 1;

int pwmSustainValue = 200;

int envelopeStatus = 0;

void setup() {
  TCCR1B = TCCR1B & B11111000 | B00000001;
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin), detectPulse, CHANGE);
}

void loop() {  
  if (envelopeStatus != 0) {
    analogWrite(pwmPin, pwmValue);
  }

  switch (envelopeStatus) {
    // ATTACK
    case 1:
      if (pwmValue + pwmAttackChange <= 255) {
        pwmValue = pwmValue + pwmAttackChange;
      } else {
        envelopeStatus = 2;
      }
      break;
  
  // DECAY
  case 2:
    if (pwmValue > pwmSustainValue) {
      pwmValue = pwmValue - pwmDecayChange;
    } else {
      envelopeStatus = 3;
    } 
    break;

  // SUSTAIN
  case 3:
    pwmValue = pwmSustainValue;
    break;

  // RELEASE
  case 4:
    if (pwmValue > 0) {
      pwmValue = pwmValue - pwmReleaseChange;
    } else {
      envelopeStatus = 0;
      pwmValue = 0;
    }
    break;

  }

  delay(10);
}

void detectPulse() {
  if (digitalRead(interruptPin) == LOW) {
    envelopeStatus = 1;
  } else {
    envelopeStatus = 4;
  }
}
