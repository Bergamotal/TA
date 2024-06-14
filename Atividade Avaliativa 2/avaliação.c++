/*
Título: Controle de Acesso com Arduino

Descrição:
Você foi contratado para desenvolver um sistema de controle 
de acesso simples usando Arduino. O sistema consiste em um 
teclado matricial de 4x4 e um display LCD 16x2. O objetivo é 
permitir que um usuário insira um código de acesso de 4 dígitos. 
Se o código estiver correto, uma mensagem de "Acesso Permitido" 
será exibida no LCD; caso contrário, será exibida uma mensagem de 
"Acesso Negado".

Requisitos:
- Caso não possua senhas cadastradas, permitir acesso sem senha
- Após cadastrar o usuário, permitir acesso somente com senha
- Use a tecla # para confirmar
- Use a tecla * para cancelar
- Utilize as letras para navegar entre as funcionalidades

Funcionalidades
1. Usuário Logado:
  - Cadastrar novas senhas
  - Excluir senhas
  - Mostrar senhas cadastradas
  - Logoff
2. Usuário deslogado
  - Login

Funcionalidade Adicional (Opcional):
Implemente um mecanismo de bloqueio temporário após um número definido de tentativas fracassadas.
Permita que o código de acesso seja alterado pelo usuário através de uma interface simples.
*/

#include <LiquidCrystal.h>

// conexão física nos pinos
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
const int rows[] = {6, 7, 8, 9};
const int cols[] = {10, 11, 12, 13};

// mapear o teclado
const char keys[4][4] = {{'1', '2', '3', 'A'},
                         {'4', '5', '6', 'B'},
                         {'7', '8', '9', 'C'},
                         {'*', '0', '#', 'D'}};

// variáveis
char inputC[5];       // armazena código digitado
char storedC[5] = ""; // armazena código correto
bool logged = false; // estado de login
int inputI = 0;      // índice para digitação

void setup()
{
  // inicialização do display lcd
  lcd.begin(16, 2);
  delay(1000);
  lcd.println("Bem-Vindo!");
  delay(1000);
  lcd.clear();

  // iniciazação o teclado matricial
  for (int i=0; i<4; i++) {
    pinMode(rows[i], INPUT_PULLUP);
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], HIGH);
  }
}

void loop() {
  // chama a função que verifica e retorna se alguma tecla for pressionada
  char key = keyboardScan();
  // se retornar 0 = nulo, não tem tecla pressionada
  if (key > 0) {
   press(key);
    delay(500); // evitar considerar acionamentos
  }
}

char keyboardScan() {
  // retorno da função - padrão retorna nulo
  char ret = 0;

  for (int i=0; i<4; i++) {
    // colocar o pino de saída (coluna) em nível lógico baixo
    digitalWrite(cols[i], LOW);
    // verificar em todas as entradas (linhas)
    // se tem algum sinal em nível lógico baixo (botão pressionado)
    for (int j=0; j<4; j++) {
      // verificar se tem sinal nos pinos de entrada (linhas) em nível lógico baixo
      if (digitalRead(rows[j]) == LOW) {
        ret = keys[j][i];
        // escreve a coluna e linha pressionada
        // lcd.print("Col: " + String(i) + " - Lin: " + String(j));
      }
    }
    // colocar o pino de saída (coluna) em nível lógico alto
    digitalWrite(cols[i], HIGH);
  }
  // retorno da função
  return ret;
}

void press(char key) {
  if (key == '*') {
    // cancelar entrada
    inputI = 0;
    lcd.clear();
  } 
  
  else if (key == '#') {
    // confirmar entrada
    inputC[inputI] = '\0'; // finaliza string
    if (logged) {
      if (strcmp(inputC, "A") == 0) {
        // cadastrar nova senha
        lcd.clear();
        lcd.println("Nova Senha:");
        inputI = 0;

        while (inputI < 4) {
          char newKey = keyboardScan();
          
          if (newKey > 0) {
            inputC[inputI++] = newKey;
            lcd.print(newKey);
            delay(500);
          }
        }

        inputC[4] = '\0';
        strcpy(storedC, inputC);
        lcd.clear();
        lcd.println("Senha Cadastrada");
      }
      
      else if (strcmp(inputC, "B") == 0) {
        // excluir senha
        strcpy(storedC, "");
        lcd.clear();
        lcd.println("Senha Excluida");
      } 
      
      else if (strcmp(inputC, "C") == 0) {
        // mostrar senha cadastrada
        lcd.clear();
        lcd.println("Senha:");
        lcd.println(storedC);
      } 
      
      else if (strcmp(inputC, "D") == 0) {
        // logoff
        logged = false;
        lcd.clear();
        lcd.println("Deslogado");
      } 
      
      else {
        lcd.clear();
        lcd.println("Opcao Invalida");
      }
    } 
    
    else {
      if (strcmp(storedC, "") == 0 || strcmp(inputC, storedC) == 0) {
        // acesso permitido
        logged = true;
        lcd.clear();
        lcd.println("Acesso Permitido");
      } 
      
      else {
        // acesso negado
        lcd.clear();
        lcd.println("Acesso Negado");
      }
    }

    inputI = 0;

  } 
  
  else {
    // armazenar dígito
    if (inputI < 4) {
      inputC[inputI++] = key;
      lcd.print(key);
    }
  }
}
