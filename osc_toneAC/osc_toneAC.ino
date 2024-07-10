#include <toneAC.h>
#include <DFRobot_AD9837.h>

float octPerVolt = 1.0;
float baseFrequency = 55;

float LAST_FREQ1 = 0.0;
float LAST_FREQ2 = 0.0;

DFRobot_AD9837 DAC1(5, &SPI);
DFRobot_AD9837 DAC2(6, &SPI);

void setup() {
    DAC1.begin(10000000);
    DAC2.begin(10000000);
}

void loop() {
  float ADC1 = analogRead(A2);
  float VOLT1 = (ADC1 - fmod(ADC1, 17.05)) * (5.0 / 1023.0);
  float FREQ1 = baseFrequency * pow(2.0, (VOLT1 * octPerVolt));

  float ADC2 = analogRead(A3);
  float VOLT2 = (ADC2 - fmod(ADC2, 17.05)) * (5.0 / 1023.0);
  float FREQ2 = baseFrequency * pow(2.0, (VOLT2 * octPerVolt));

  int phase = 0;

  if (LAST_FREQ1 != FREQ1) {
    DAC1.outputSin(phase, FREQ1);
    //DAC1.outputTriangle(phase, FREQ1);
    //DAC1.outputSquare(DAC1.eDIV2_1, phase, FREQ1);

    LAST_FREQ1 = FREQ1;
  }

  if (LAST_FREQ2 != FREQ2) {
    //DAC2.outputSin(phase, FREQ1);
    DAC2.outputTriangle(phase, FREQ2);
    //DAC2.outputSquare(DAC2.eDIV2_1, phase, FREQ2);
    LAST_FREQ2 != FREQ2;
  }
}

