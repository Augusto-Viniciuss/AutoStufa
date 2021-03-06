//Pino do sensor de luminosidade
#define sensor A5

//Pino do potenciometro para mudar as cores
#define muda_cor A4

//Pinos dos LEDs RGBs 
#define azul 2
#define vermelho 3
#define verde 4

void setup() {
 
  //Definição dos pinos
  pinMode(muda_cor, INPUT);
  pinMode(sensor, INPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  
}

void loop() {
 
  //Ler os valores do potenciometro e do sensor
  float escolheCor = analogRead(muda_cor);
  float luz = analogRead(sensor);
  
  if (luz > 800) {   
    
    //Chama o void para decidir qual cor acenderá
    muda_cores(escolheCor);
    
  } else {
    
    //Desliga a iluminação
    digitalWrite(vermelho, LOW);
    digitalWrite(azul, LOW);
    digitalWrite(verde, LOW);
    
  } 
}

void muda_cores(float valor) {
  
  //Mapear os valores do potenciometro de 0 a 100
  int cores = map(valor, 0, 1024, 0, 100);
 
  if ((cores > 33) && (cores <= 66)) {
    
    //Definir cor amarela
    digitalWrite(verde, HIGH);
    digitalWrite(vermelho, HIGH);
    digitalWrite(azul, LOW);
    
   } else if (cores > 66) {
    
    //Definir cor azul
    digitalWrite(azul, HIGH);
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
    
  } else {
    
    //Definir cor vermelha
    digitalWrite(vermelho, HIGH);
    digitalWrite(azul, LOW);
    digitalWrite(verde, LOW);
    
  }
}
