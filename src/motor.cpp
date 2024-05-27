#include <Arduino.h>

class Motor {
  private:
    int pin;

  public:
    Motor(int pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
    }

    void frente() {
      digitalWrite(pin, HIGH);
    }

    void parar() {
      digitalWrite(pin, LOW);
    }
};

class Led {
  private:
    int pin;

  public:
    Led(int pin) {  // Corrigir o nome do construtor para corresponder ao nome da classe
      this->pin = pin;
      pinMode(pin, OUTPUT);
    }

    void acende() {
      digitalWrite(pin, HIGH);
    }

    void apaga() {
      digitalWrite(pin, LOW);
    }
};

// Definindo os pinos dos motores
const int motor1Pin = 9;
//const int motor2Pin = ; 
//const int motor3Pin = ; 
//const int motor4Pin = ; 
const int ledPin = 10;
const int buzzerPin = 7;

// Instanciando os motores
Motor motor1(motor1Pin);
//Motor motor2(motor2Pin);
//Motor motor3(motor3Pin);
//Motor motor4(motor4Pin);

Led led(ledPin);

// Definindo os botões
const int botao1 = 2;
//const int botao2 = ; 
//const int botao3 = ; 
//const int botao4 = ; 

void setup() {
  Serial.begin(115200);
  Serial.println("Testing DC Motors...");

  pinMode(botao1, INPUT); // Configurando o botão como entrada
//  pinMode(botao2, INPUT); // Configurando o botão como entrada
//  pinMode(botao3, INPUT); // Configurando o botão como entrada
//  pinMode(botao4, INPUT); // Configurando o botão como entrada

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Movendo cada motor para frente
  motor1.frente();
//  motor2.frente();
//  motor3.frente();
//  motor4.frente();
  led.acende();
  tone(buzzerPin, 5);

  // Verifica se o botão foi pressionado
  if (digitalRead(botao1) == HIGH) {
    motor1.parar();
    led.apaga();
    noTone(buzzerPin);
  }

//  if (digitalRead(botao2) == HIGH) {
//    motor2.parar();
//  }

//  if (digitalRead(botao3) == HIGH) {
//    motor3.parar();
//  }

//  if (digitalRead(botao4) == HIGH) {
//    motor4.parar();
//  }
}
