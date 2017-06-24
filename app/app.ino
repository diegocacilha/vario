#include <SFE_BMP180.h>
#include <Wire.h>

double pressao, temperatura, temp;

SFE_BMP180 barometro;

void setup() {
  char status;
  Wire.begin();
  Serial.begin(9600);
  status = barometro.begin();
  if (!status) {
    Serial.println("Erro na inicialização do barômetro\n");
  }else {
    Serial.println("Barômetro inicializado com sucesso\n");
  }
  pressao = getPressao();
  temperatura = getTemperatura();
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Pressão: ");
  Serial.println(pressao);
  
}
int cont = 0;
int tempo;
void loop() {
  double i;
  pressao = getPressao();
  i = pressao - temp;

  if(i > 0.20){
    //Serial.println(i);
    tone(10, 2850, 100);
    tempo = 120;
  }else if(i < -0.20){
    //Serial.println(i);
    tone(10, 2400, 15);
    tempo = 20;
  }else {
    Serial.println(i);
    tone(10, 2000, 200);
    tempo = 210;
  }
  delay(tempo);
  Serial.println(i);
  temp = pressao;
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
