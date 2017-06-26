#include <SFE_BMP180.h>
#include <Wire.h>

double pressao, temperatura;
double p2;

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
  //pressao = getPressao();
  pressao = 1013.25;
  p2 = pressao;
  temperatura = getTemperatura();
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Pressão: ");
  Serial.println(pressao);
  
}

void loop() {
  //pressao = getPressao();
  pressao -= 0.25;
  bip();
  p2 = pressao;
  delay(5000);
}

void bip(){
  double result, T;// T = tempo do sinal sonoro
  result =  pressao - p2;
  Serial.print("resultado ");
  Serial.println(result);
  
  T = result * 5000;
  Serial.print("tempo ");
  Serial.println(T);
  
  //T = constrain(T, 0, 1000);
  //Serial.println(result);
  if(result < 0){
    tone(10, 1800, T);
    //delay(T + 100);
  }else {
    noTone(10);
  }
  
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
