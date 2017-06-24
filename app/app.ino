#include <SFE_BMP180.h>
#include <Wire.h>

double lowpassFast, lowpassSlow, pressao, toneFreq, toneFreqLowpass;
int ddsAcc;

SFE_BMP180 barometro;

void setup() {
  char status;
  Wire.begin();
  Serial.begin(9600);
  status = barometro.begin();
  if (!status) {
    Serial.println("Erro na inicialização do barômetro\n");
  }
  pressao = getPressao();
  lowpassFast = lowpassSlow = pressao;
}
int cont = 0;
void loop() {
  pressao = getPressao();

  Serial.print("Pressão: ");
  Serial.println(pressao);
  
  Serial.print("lowpassFast antes: ");
  Serial.println(lowpassFast);
  lowpassFast = lowpassFast + (pressao - lowpassFast) * 0.5;//era 0.1
  Serial.print("lowpassFast depois: ");
  Serial.println(lowpassFast);
  
  Serial.print("lowpassSlow antes: ");
  Serial.println(lowpassSlow);
  lowpassSlow = lowpassSlow + (pressao - lowpassSlow) * 0.25;//era 0.05
  Serial.print("lowpassSlow depois: ");
  Serial.println(lowpassSlow);
  
  Serial.print("toneFreq antes: ");
  Serial.println(toneFreq);
  toneFreq = (lowpassSlow - lowpassFast) * 50;
  Serial.print("toneFreq depois: ");
  Serial.println(toneFreq);

  Serial.print("toneFreqLowpass antes: ");
  Serial.println(toneFreqLowpass);
  toneFreqLowpass = toneFreqLowpass + (toneFreq - toneFreqLowpass) * 0.1;
  Serial.print("toneFreqLowpass depois: ");
  Serial.println(toneFreqLowpass);

  Serial.print("toneFreq antes constrain: ");
  Serial.println(toneFreq);
  toneFreq = constrain(toneFreqLowpass, -500, 500);
  Serial.print("toneFreq depois constrain: ");
  Serial.println(toneFreq);

  Serial.print("ddsAcc antes: ");
  Serial.println(ddsAcc);
  ddsAcc += toneFreq * 100 + 2000;
  Serial.print("ddsAcc depois: ");
  Serial.println(ddsAcc);

  if (toneFreq < 0 || ddsAcc > 0){
    tone(10, toneFreq + 2100);
    Serial.print("toneFreq: ");
    Serial.println(toneFreq + 2100);
  }else{
    noTone(10);
  }
  Serial.println("-----------------------------");
  //delay(10);
}

double getPressao() {
  double P, T;
  char status;
  status = barometro.begin();
  T = getTemperatura();
  status = barometro.startPressure(1);
  if (status) {
    delay(status);
    status = barometro.getPressure(P, T);
    if (status) {
      return P;
    }
  } else {
    Serial.println("Problema com a inicialização da pressão");
  }
}
double getTemperatura() {
  double T;//temperatura
  char status;
  status = barometro.begin();
  status = barometro.startTemperature();
  if (status != 0 ) {
    delay(status);
    status = barometro.getTemperature(T);
    if (status) {
      return T;
    }
  } else {
    Serial.println("Problema com a inicialização da temperatura");
  }

}
