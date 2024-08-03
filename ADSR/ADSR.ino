int gatePin = 2;

int pwmPin = 9;
int pwmValue = 0;

int pwmAttackSpeed = 100;
int pwmDecaySpeed = 10;
int pwmSustainValue = 215;
int pwmReleaseSpeed = 100;
bool triggered = false;

int envelopeStatus = 0;

void setup() {
  TCCR1B = TCCR1B & B11111000 | B00000001;
  pinMode(gatePin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  if (digitalRead(gatePin) == LOW && triggered == false) {
    envelopeStatus = 1;
    triggered = true;
  }

  if (digitalRead(gatePin) == HIGH && triggered == true) {
    envelopeStatus = 4;
    triggered = false;
  }

  analogWrite(pwmPin, pwmValue);

  pwmAttackSpeed  = analogRead(A0) > 980 ? 200 : 1 + analogRead(A0) / 40;
  pwmDecaySpeed   = analogRead(A1) > 980 ? 200 : 1 + analogRead(A1) / 40;
  pwmSustainValue = analogRead(A2) / 4;
  pwmReleaseSpeed = analogRead(A3) > 980 ? 200 : 1 + analogRead(A3) / 40;

  /*
  Serial.print("A=");
  Serial.print(pwmAttackSpeed);
  Serial.print(" D=");
  Serial.print(pwmDecaySpeed);
  Serial.print(" S=");
  Serial.print(pwmSustainValue);
  Serial.print(" R=");
  Serial.print(pwmReleaseSpeed);
  Serial.print(" Status=");
  Serial.println(envelopeStatus);
  Serial.print(" PWM Value=");
  Serial.println(pwmValue);
  */

  switch (envelopeStatus) {
    // ATTACK
    case 1:
      if (pwmValue + pwmAttackSpeed <= 255) {
        pwmValue = pwmValue + pwmAttackSpeed;
      } else {
        pwmValue = 255;
        envelopeStatus = 2;
      }
      break;
  
  // DECAY
  case 2:
    if (pwmValue - pwmDecaySpeed >= pwmSustainValue) {
      pwmValue = pwmValue - pwmDecaySpeed;
    } else {
      pwmValue = pwmSustainValue;
      envelopeStatus = 3;
    } 
    break;

  // SUSTAIN
  case 3:
    pwmValue = pwmSustainValue;
    break;

  // RELEASE
  case 4:
    if (pwmValue - pwmReleaseSpeed >= 0) {
      pwmValue = pwmValue - pwmReleaseSpeed;
    } else {
      pwmValue = 0;
      envelopeStatus = 0;
    }
    break;

  }

  delay(10);
}
