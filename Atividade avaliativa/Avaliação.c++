#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

//Declarando as variáveis.
int BotVerde = 34;
int EstBotVer;

int BotRed = 35;
int EstBotRed;

int BotAmare = 32;
int EstBotAma;

int BotAzul = 33; 
int EstBotAzul;

int contadorAzul;

//Mostrando a mensagem de bem-vindo, pedindo para o usuário escolher uma opção e definindo os pinos de entradas.
void setup(){
    
    for(int i = 32; i <= 35; i++){
        pinMode(i, INPUT);
    }
    lcd.init();
    lcd.backlight();
    Serial.begin(115200);
    lcd.setCursor(3,0);
    lcd.println("Bem-Vindo!");
    Serial.println("Bem-Vindo!");
    delay(1500);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.println("Escolha uma");
    lcd.setCursor(5,1);
    lcd.println("opcao:");  
    Serial.println("Escolha uma opção: ");
    delay(2000);
    lcd.clear();
    Serial.println("Opção 1 - Verde");
    Serial.println("Opção 2 - Azul");
    Serial.println("Opção 3 - Amarelo");
    
}

//Mostra as opções para serem selecionadas.
void loop(){
  lcd.setCursor(0,0);
  lcd.println("Opc. 1");
  lcd.setCursor(10,0);
  lcd.println("Opc. 2");
  lcd.setCursor(0,1);
  lcd.println("Opc. 3");

  
}

//Função do botão verde.
void EstadoVer(){

  EstBotVer = digitalRead(BotVerde);

  while (EstBotVer == HIGH){
    delay(500);
    lcd.clear();
    Serial.println("Contar ao Clicar");
    lcd.setCursor(0,0);
    lcd.println("Contar ao Clicar");
    delay(1500);
    lcd.clear();

  }
}   

void Contador(){

  EstBotAzul = digitalRead(BotAzul);

  while(true){
    if(BotAzul==HIGH){
      lcd.setCursor(0,0);
      lcd.println("Contador: ");
      Serial.println("Botão Azul para incrementar");
      Serial.println("Botão Amarelo para resetar");
      Serial.println("Botão Vermelho para voltar ao menu");
      lcd.setCursor(0,1);
      for(int i = 0; i >= 0; i++){
        lcd.println(i);

      }
    }

  }

}

/* Código do site caso de errado o save.
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int BotVerde = 34;
int EstBotVer;
bool EstVer = false;

int BotRed = 35;
int EstBotRed;
bool EstRed = false;

int BotAmare = 32;
int EstBotAma;
bool EstAma = false;

int BotAzul = 33; 
int EstBotAzul;
bool EstAzul = false;

void setup(){
  for(int i = 32; i <= 35; i++){
    pinMode(i, INPUT);
  }
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  lcd.setCursor(3,0);
  lcd.println("Bem-Vindo!");
  Serial.println("Bem-Vindo!");
  delay(1500);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.println("Escolha uma");
  lcd.setCursor(5,1);
  lcd.println("opcao:");  
  Serial.println("Escolha uma opção: "); 
  delay(2000);
  lcd.clear();
  Serial.println("Opção 1 - Verde");
  Serial.println("Opção 2 - Azul");
  Serial.println("Opção 3 - Amarelo");
  
}

void loop(){
  lcd.setCursor(0,0);
  lcd.println("Opc. 1");
  lcd.setCursor(10,0);
  lcd.println("Opc. 2");
  lcd.setCursor(0,1);
  lcd.println("Opc. 3");

  EstadoVer();
      
}

void EstadoVer(){

  EstBotVer = digitalRead(BotVerde);

  if (EstBotVer == HIGH){
    EstVer = !EstBotVer;
    delay(500);
    lcd.clear();
    Serial.println("Contar ao Clicar");
    lcd.setCursor(0,0);
    lcd.println("Contar ao Clicar");
    delay(1500);
    lcd.clear();
    lcd.println("Contador:");
    Serial.println("Botão Azul para incrementar");
    Serial.println("Botão Amarelo para resetar");
    Serial.println("Botão Vermelho para voltar ao menu");

  }
}   
*/