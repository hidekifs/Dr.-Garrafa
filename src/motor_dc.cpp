const int pinMotor = 9; // Pino conectado ao motor

void setup() {
  pinMode(pinMotor, OUTPUT); // Configura o pino do motor como saída
}

void loop() {
  // Gira o motor no sentido horário
  //digitalWrite(pinMotor, HIGH);
  analogWrite(pinMotor, 100); // Define a velocidade baixa (valor entre 0 e 255)


  // Para o motor
  //digitalWrite(pinMotor, LOW);
  //delay(1000); // Aguarda 1 segundo
}