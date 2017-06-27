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
  pressao = getPressao();
  p2 = pressao;
  temperatura = getTemperatura();
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Pressão: ");
  Serial.println(pressao);
  
}

void loop() {
  pressao = getPressao();
  bip();
  p2 = pressao;
}

void bip(){
  double result, T;// T = tempo do sinal sonoro
  result =  pressao - p2;
  
  T = (1000 * (result * 2)) - 1000;
  if(T < 0) T = T * (-1);

  if(result > 0.07){
    tone(10, 1700, (0.75 * T));  
  }else if(result < (-0.07)){
    tone(10, 2900, (0.50 * T));
  }else {
    /*
     * Aqui eu tinha colocado o 'zerinho', mas notei que o buzzer consome muita bateria e resolvi tirar.
     */
//    for(int i = 1900; i < 2200; i++){
//      tone(10, i);
//      delay(1);
//    }
//    noTone(10);
  }
  
  
  Serial.println(T);
  delay(T);
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
