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
    if (hora != -1) {
      Serial.print("Hora extraída: ");
      Serial.println(hora);
    } else {
      Serial.println("Nenhuma hora encontrada.");
    }

    //extrai minuto
    int minuto = extrairNumero(dadosRecebidos, "\"minuto\":");
    if (minuto != -1) {
      Serial.print("minuto extraída: ");
      Serial.println(minuto);
    } else {
      Serial.println("Nenhuma minuto encontrada.");
    }

    //extrai dispenser
    int dispenser = extrairNumero(dadosRecebidos, "\"dispenser\":");
    if (dispenser != -1) {
      Serial.print("Dispenser extraído: ");
      Serial.println(dispenser);
    } else {
      Serial.println("Nenhum dispenser encontrado.");
    }

    //extrai somente no dia
    int uma_vez = extrairNumero(dadosRecebidos, "\"uma_vez\":");
    if (uma_vez != -1) {
      Serial.print("Uma vez extraído: ");
      Serial.println(uma_vez);
    }

    //extrai repeticao
    String repeticao = extrairString(dadosRecebidos, "\"repeticao\":");
    if (repeticao != "") {
      Serial.print("repeticao extraida: ");
      Serial.println(repeticao);
    }

    //extrai dias de semana
    String semana = extrairString(dadosRecebidos, "\"semana\":");
    if (semana != "") {
      Serial.print("Semana extraído: ");
      Serial.println(semana);
    }

    //extrai segunda
    int segunda = extrairNumero(dadosRecebidos, "\"segunda\":");
    if (segunda != -1) {
      Serial.print("Segunda extraído: ");
      Serial.println(segunda);
    }

        //extrai terca
    int terca = extrairNumero(dadosRecebidos, "\"terça\":");
    if (terca != -1) {
      Serial.print("Terça extraído: ");
      Serial.println(terca);
    }

        //extrai quarta
    int quarta = extrairNumero(dadosRecebidos, "\"quarta\":");
    if (quarta != -1) {
      Serial.print("quarta extraído: ");
      Serial.println(quarta);
    }

            //extrai quinta
    int quinta = extrairNumero(dadosRecebidos, "\"quinta\":");
    if (quinta != -1) {
      Serial.print("quinta extraído: ");
      Serial.println(quinta);
    }

        //extrai sexta
    int sexta = extrairNumero(dadosRecebidos, "\"sexta\":");
    if (sexta != -1) {
      Serial.print("sexta extraído: ");
      Serial.println(sexta);
    }

            //extrai sabado
    int sabado = extrairNumero(dadosRecebidos, "\"sabado\":");
    if (sabado != -1) {
      Serial.print("sabado extraído: ");
      Serial.println(sabado);
    }

            //extrai domingo
    int domingo = extrairNumero(dadosRecebidos, "\"domingo\":");
    if (domingo != -1) {
      Serial.print("domingo extraído: ");
      Serial.println(domingo);
    }
  }
}

// Declaração da função extrairString
String extrairString(String dados, String parametro) {
  int startIndex = dados.indexOf(parametro);
  if (startIndex == -1) {
    return ""; // Retorna uma string vazia se o parâmetro não for encontrado
  }
  
  startIndex += parametro.length(); // Move para o próximo caractere após o parâmetro
  
  // Pular qualquer espaço em branco
  while (startIndex < dados.length() && dados[startIndex] != '\"') {
    startIndex++;
  }
  
  startIndex++; // Avança para o próximo caractere após a primeira aspas
  
  // Encontra o índice do próximo caractere de aspas
  int endIndex = dados.indexOf('\"', startIndex);
  
  if (endIndex != -1) {
    return dados.substring(startIndex, endIndex); // Retorna a substring entre as aspas
  } else {
    return ""; // Retorna uma string vazia se o segundo conjunto de aspas não for encontrado
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
