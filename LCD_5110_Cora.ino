#include <LCD5110_Graph.h>
#include "DHT.h"

#define DHTPIN 3     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


LCD5110 tela(8,9,10,12,11);
 
//O arranjo gerado pelo programa terá o mesmo nome da imagem
extern uint8_t Cora[]; //Obtendo o arranjo
extern uint8_t SmallFont[]; 

void MostraLogo(){
  for (int i=0; i<=36; i++){ //laço necessário para o carrinho percorrer a tela toda
 
    tela.clrScr(); //limpando a tela e o buffer
    tela.drawBitmap(i, 0, Cora, 48, 48); //desenhando a imagem na tela
    tela.update(); //atualizando a tela com as informações armazenadas no buffer
    delay(200); //Aumentando esse tempo a velocidade diminuirá,
             //diminuindo-o a velocidade aumentará
  }  
}

void Jaba(){
  
  tela.clrScr(); //Apaga o contéudo que estiver na tela
  tela.print("  Cora", LEFT, 0);
  tela.print("Hacker", CENTER, 20);
  tela.print("Club  ", RIGHT, 40);
  tela.update(); //atualizando a tela com as informações armazenadas no buffer
  delay(500);
  
}


void getDTH11(){
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  tela.clrScr();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    tela.print("Faile to read", CENTER, 8);
    tela.print("from DTH sensor", CENTER, 32);
    tela.update(); //atualizando a tela com as informações armazenadas no buffer
    delay(2500);
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  tela.print("Cora HC.", CENTER, 0);
  tela.print("Humid.: " + String(h) + "%", LEFT, 10);
  tela.print("Temp. : " + String(t) + "C", LEFT, 20);
  tela.print("Indice Calor", CENTER, 32);
  tela.print(String(hic)+"C " + String(hif)+"F", 4, 40);
  
  tela.update(); //atualizando a tela com as informações armazenadas no buffer
  delay(2500);
}
  
void setup()
{
  tela.InitLCD();
  dht.begin();
  tela.setFont(SmallFont); //Definindo a fonte
}

 
void loop()
{

 MostraLogo();
 Jaba();
 getDTH11();

}
