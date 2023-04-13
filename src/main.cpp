#include <Arduino.h>

float tidakBocor;
float bocor;
float bocorParah;

float valueTriMf(float inputFuzz, float val1, float val2, float val3)
{
    float outputFuzz;
    if (inputFuzz <= val1){outputFuzz = 0; return outputFuzz;}
    else if(inputFuzz > val1 && inputFuzz <= val2){outputFuzz = (inputFuzz - val1)/(val2 - val1); return outputFuzz;}
    else if(inputFuzz > val2 && inputFuzz <= val3){outputFuzz=(val3 - inputFuzz)/(val3 - val2); return outputFuzz;}
    else{outputFuzz = 0; return outputFuzz;}    
}

float valueTraMf(float inputFuzz, float val1, float val2, float val3, float val4)
{
    float outputFuzz;
    if (inputFuzz <= val1){outputFuzz = 0; return outputFuzz;}
    else if(inputFuzz > val1 && inputFuzz <= val2){outputFuzz = (inputFuzz - val1)/(val2 - val1); return outputFuzz;}
    else if(inputFuzz > val2 && inputFuzz <= val3){outputFuzz= 1; return outputFuzz;}
    else if(inputFuzz > val3 && inputFuzz <= val4){outputFuzz=(val4 - inputFuzz)/(val4 - val3); return outputFuzz;}
    else{outputFuzz = 0; return outputFuzz;}    
}

void ruleBase(float inputA1, float inputA2, float inputA3, float inputB1, float inputB2, float inputB3)
{
    float rules0 = min(inputA1, inputB1);
    float rules1 = min(inputA1, inputB2);
    float rules2 = min(inputA1, inputB3);
    float rules3 = min(inputA2, inputB1);
    float rules4 = min(inputA2, inputB2);
    float rules5 = min(inputA2, inputB3);
    float rules6 = min(inputA3, inputB1);
    float rules7 = min(inputA3, inputB2);
    float rules8 = min(inputA3, inputB3);
    tidakBocor = max(max(rules0, rules1), rules2);
    bocor = max(max(rules3, rules4), rules5);
    bocorParah = max(max(rules6, rules7), rules8);
}

float defuzz(float x1, float x2, float x3)
{
    float defuzzificationA = (tidakBocor*x1) + (bocor*x2) + (bocorParah);
    float defuzzificationB = tidakBocor + bocor + bocorParah;
    float defuzzifiaction = defuzzificationA / defuzzificationB;
    return defuzzifiaction;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ranNum = random(10);
  int ranNum2 = random(5);
  float A1 = valueTraMf(ranNum, -6, -2, 0, 2);
  float A2 = valueTriMf(ranNum, 0, 2, 4);
  float A3 = valueTraMf(ranNum, 2, 4, 6, 8);
  float B2 = valueTraMf(ranNum2, -6, -6, 0.5, 1);
  float B3 = valueTriMf(ranNum2, 0.5, 1, 1.5);
  float B4 = valueTraMf(ranNum2, 1, 1.5, 2, 2.5);
  ruleBase(A1, A2, A3, B2, B3, B4);
  float result = defuzz(2, 3, 4);
  Serial.print("hasilnya adalah: ");
  Serial.println(result);
}