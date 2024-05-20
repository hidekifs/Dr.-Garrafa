#include <RTClib.h> // Biblioteca para o RTC DS1307
#include "BluetoothSerial.h"
#include <ArduinoJson.h>

RTC_DS1307 rtc;
BluetoothSerial SerialBT;
char valorRecebido;
char recebeBluetooth;
int variavel = 1830;
char caracter;
String palavra;

int extrairNumero(const std::string& str, const std::string& chave) {
  // Encontra a posição da chave na string
  size_t posChave = str.find(chave);
  if (posChave == std::string::npos) {
    // Se a chave não for encontrada, retorna -1
    return -1;
  }

  // Encontra a posição do primeiro dígito após a chave
  size_t posInicioNumero = posChave + chave.length();
  while (posInicioNumero < str.length() && !isdigit(str[posInicioNumero])) {
    posInicioNumero++;
  }

  if (posInicioNumero == str.length()) {
    // Se não houver números após a chave, retorna -1
    return -1;
  }

  // Extrai o número da string e converte para inteiro
  return std::stoi(str.substr(posInicioNumero));
}

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

// Definindo os pinos dos motores
const int motor1Pin = 16; // Atribuir valor ao parâmetro
//const int motor2Pin = ; 
//const int motor3Pin = ; 
//const int motor4Pin = ; 

// Instanciando os motores
Motor motor1(motor1Pin);
//Motor motor2(motor2Pin);
//Motor motor3(motor3Pin);
//Motor motor4(motor4Pin);

// Definindo os botões
int botao1 = 19;
//int botao2 = ; 
//int botao3 = ; 
//int botao4 = ; 

void setup() {
  

  Serial.begin(115200);
  SerialBT.begin("DR.Garrafa");
  Serial.println("ESP32 Bluetooth Serial Started");

  Serial.begin(9600);  
  // Extrai o número associado à chave "temperature"

  Serial.begin(115200);
  Serial.println("Testing DC Motors...");

  pinMode(botao1, INPUT); // Configurando o botão como entrada
//  pinMode(botao2, INPUT); // Configurando o botão como entrada
//  pinMode(botao3, INPUT); // Configurando o botão como entrada
//  pinMode(botao4, INPUT); // Configurando o botão como entrada

  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Não foi possível encontrar o RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC não está funcionando. Corrija a hora e a data!");
    // Se o RTC não está funcionando, você pode definir a hora e a data manualmente aqui

    DateTime now = DateTime(2024, 4, 30, 0, 45, 0); // Ano, Mês, Dia, Hora, Minuto, Segundo
    rtc.adjust(now);

    Serial.println("Data e hora configuradas com sucesso.");
  }

}

void loop() {
  if(SerialBT.available()) {
  caracter = SerialBT.read();
  palavra = palavra + caracter;
  String receivedData;

  if(caracter == '*') {    
     palavra = palavra.substring(0, palavra.length() - 1); // Quita último caracter * 
     Serial.println(palavra);
       
      int temperatura = extrairNumero(palavra, "temperature");
      Serial.println(temperatura);
     palavra = "";
    delay(100); 
   }

  {
    if (SerialBT.available() > 0){
      recebeBluetooth = SerialBT.read();
      palavra = palavra + recebeBluetooth;
    //  Serial.println(recebeBluetooth);
      delay(100);

      if (recebeBluetooth == '*'){
        palavra = palavra.substring (0, palavra.length() - 1);
        Serial.println(palavra);
        palavra = "";
        SerialBT.println(variavel);
      }
      delay(100);

      if (recebeBluetooth == 'temperature'){
        
      }
    }
  }

  // Movendo cada motor para frente
  motor1.frente();
//  motor2.frente();
//  motor3.frente();
//  motor4.frente();

  // Verifica se o botão foi pressionado
  if (digitalRead(botao1) == HIGH) {
    motor1.parar();
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

DateTime now = rtc.now(); {

  now = now + TimeSpan(0, 0, 0, 60);

//  Serial.print(now.year(), DEC);
//  Serial.print('/');
//  Serial.print(now.month(), DEC);
//  Serial.print('/');
//  Serial.print(now.day(), DEC);
//  Serial.print(" ");
//  Serial.print(now.hour(), DEC);
//  Serial.print(':');
//  Serial.print(now.minute(), DEC);
//  Serial.print(':');
//  Serial.print(now.second(), DEC);
//  Serial.println();

 // delay(1000);
 }
  }
}
