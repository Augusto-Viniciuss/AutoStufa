//Biblioteca usada para programar o LCD
#include <LiquidCrystal.h>

//Pinos da Tela LCD 16x2
LiquidCrystal lcd(12, 11, A0, A1, A2, A3);

//Pino sensor de umidade
#define sensor_umidade A5

//Pino sensor de temperatura
#define sensor_temperatura A4

//Pinos LED RGB de indicação de umidade
#define vermelho 7
#define azul 8
#define verde 9

//Pino válvula solenoide
#define valvula 13

//Pino do exaustor
#define exaustor 10

void setup() {
  	
    //Instruções de Setup do lcd
    lcd.begin(16, 2);
    
    //Instruções de apresentação inicial no lcd
    lcd.setCursor(0, 0);
    lcd.print("Iniciando...");
    delay (2000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Tudo pronto.");
    delay (1000);
    lcd.clear();
   
    //Definição dos pinos.
    pinMode(sensor_umidade, INPUT);
    pinMode(sensor_temperatura, INPUT);
    pinMode(vermelho, OUTPUT);
    pinMode(azul, OUTPUT);
    pinMode(verde, OUTPUT);
    pinMode(valvula, OUTPUT);
    pinMode(exaustor, OUTPUT);
    
    //Fecha a válvula.
    digitalWrite(valvula, HIGH);
  
}

void loop() {
    
    //Ler do sinal do sensor
    float sinal_umd = analogRead(sensor_umidade);
    float sinal_temp = analogRead(sensor_temperatura);  
      
    //Limpa a memoria do LCD
    lcd.clear();
  
    //Chamada dos voids
    monitorar_umd(sinal_umd);
    monitorar_temp(sinal_temp);
      
  delay(600000);
}

//Função para a verificação de umidade no solo
void monitorar_umd(float umd) {
  	
    //Transformar o valor analógico recebido em porcentagem
    int umidade = map(umd, 0, 1023, 0, 100);
 
    if (umidade > 60) {
    	
      //Verde - Umidade registrada maior que 60%
      digitalWrite(vermelho,LOW);
      digitalWrite(azul, LOW);
      digitalWrite(verde, HIGH);
    
      //Desligar sistema de irrigação
      digitalWrite(valvula, HIGH);
 
    } else if ((umidade > 40) && (umidade <= 60)) {
      
      //Amarelo - Umidade registrada entre 40% e 60%
      digitalWrite(vermelho, HIGH);
      digitalWrite(azul, LOW);
      digitalWrite(verde, HIGH);
  
      //Manter sistema de irrigação desligado
      digitalWrite(valvula, HIGH); 
      
    } else {
      
      //Vermelho - Umidade registrada menor ou igual a 40%
      digitalWrite(vermelho, HIGH);
      digitalWrite(azul, LOW);
      digitalWrite(verde, LOW);
    	
      //Acionar sistema de irrigação
      digitalWrite(valvula, LOW);
      
  	}
  
   //Instruções do LCD
   lcd.setCursor(1, 0);
   lcd.print("UMID");
   lcd.setCursor(2, 1);
   lcd.print(umidade);

}

//Função para a verificação da temperatura
void monitorar_temp(float temp) {
  
      //Conversão dos valores do sensor em graus celsius
      float temperatura = temp / 1024;
      temperatura = temperatura * 5;
      temperatura = temperatura - 0.5;
      int temperaturaCelsius = temperatura * 100;

      if(temperaturaCelsius > 16) {
        
        //Acionar o sistema de ventilação
        digitalWrite(exaustor, HIGH);
        
      }else {
        
        //Desligar o sistema de ventilação
        digitalWrite(exaustor, LOW);
        
      }
      
      //Instruções do LCD
      lcd.setCursor(11, 0);
      lcd.print("TEMP");
      lcd.setCursor(12, 1);
      lcd.print(temperaturaCelsius);
      
}
