#include <RTClib.h> // Biblioteca para o RTC DS1307
#include "BluetoothSerial.h"
#include <ArduinoJson.h>

BluetoothSerial SerialBT;
char valorRecebido;
char recebeBluetooth;
int variavel = 1830;
char caracter;
String palavra;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("DR.Garrafa");
  Serial.println("ESP32 Bluetooth Serial Started");
}

void loop() {

  if(SerialBT.available()>0) {
  caracter = SerialBT.read();
  palavra = palavra + caracter;
  String receivedData;

  if(caracter == '*') {    
     palavra = palavra.substring(0, palavra.length() - 1); // Quita último caracter * 
     Serial.println(palavra);
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
  }
}