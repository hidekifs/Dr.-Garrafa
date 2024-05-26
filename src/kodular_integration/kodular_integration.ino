#include "BluetoothSerial.h" // Inclui a biblioteca para comunicação Bluetooth

BluetoothSerial SerialBT; // Cria um objeto para a comunicação Bluetooth

bool dispositivoConectado = false; // Variável para rastrear o estado de conexão

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial com a taxa de transmissão de 115200
  SerialBT.begin("DR.Garrafa"); // Inicializa a comunicação Bluetooth com o nome "DR.Garrafa"
  Serial.println("ESP32 Bluetooth Serial Iniciado"); // Imprime uma mensagem indicando que o Bluetooth foi iniciado
}

void loop() {
  if (SerialBT.hasClient() && !dispositivoConectado) { // Verifica se um dispositivo foi conectado
    dispositivoConectado = true; // Atualiza o estado de conexão
    Serial.println("Dispositivo conectado"); // Imprime uma mensagem indicando que o dispositivo foi conectado
  } else if (!SerialBT.hasClient() && dispositivoConectado) { // Verifica se o dispositivo foi desconectado
    dispositivoConectado = false; // Atualiza o estado de conexão
    Serial.println("Dispositivo desconectado"); // Imprime uma mensagem indicando que o dispositivo foi desconectado
  }

  if (SerialBT.available()) { // Verifica se há dados disponíveis na comunicação Bluetooth
    String dadosRecebidos = SerialBT.readStringUntil('\n'); // Lê os dados até encontrar um caractere de nova linha ('\n')
    Serial.println("Recebido: " + dadosRecebidos); // Imprime os dados recebidos no monitor serial

    //extrai hora
    int hora = extrairNumero(dadosRecebidos, "\"hora\":");
    int minuto = extrairNumero(dadosRecebidos, "\"minuto\":");
    if (hora != -1) {
      Serial.print("Hora extraída: ");
      Serial.print("Minuto extraído: ");
      Serial.println(hora);
      Serial.println(minuto);
    } else {
      Serial.println("Nenhuma hora encontrada.");
    }

    //extrai minuto
  //  int minuto = extrairNumero(dadosRecebidos, "\"minuto\":");
  //  if (minuto != -1) {
  //    Serial.print("Minuto extraído: ");
  //    Serial.println(minuto);
  //  } else {
  //    Serial.println("Nenhum minuto encontrado.");
  //  }

    //extrai medicamento
    int medicamento = extrairNumero(dadosRecebidos, "\"medicamento\":");
    if (medicamento != -1) {
      Serial.print("Medicamento extraído: ");
      Serial.println(medicamento);
    } else {
      Serial.println("Nenhum medicamento encontrado.");
    }

    //extrai dispenser
    int dispenser = extrairNumero(dadosRecebidos, "\"dispenser\":");
    if (dispenser != -1) {
      Serial.print("Dispenser extraído: ");
      Serial.println(dispenser);
    } else {
      Serial.println("Nenhum dispenser encontrado.");
    }
  }
}

int extrairNumero(String dados, String parametro) {
  int startIndex = dados.indexOf(parametro);
  if (startIndex == -1) {
    return -1; // Indica que o parâmetro não foi encontrado
  }
  
  startIndex += parametro.length(); // Move para o próximo caractere após o parâmetro
  // Pular qualquer espaço em branco
  while (startIndex < dados.length() && !isDigit(dados[startIndex])) {
    startIndex++;
  }
  
  String numeroString = "";
  
  while (startIndex < dados.length() && isDigit(dados[startIndex])) {
    numeroString += dados[startIndex];
    startIndex++;
  }
  
  if (numeroString.length() > 0) {
    return numeroString.toInt(); // Converte a string de dígitos em um número inteiro e retorna
  } else {
    return -1; // Indica que nenhum número foi encontrado
  }
}
