#include <RTClib.h> //biblioteca do RTC

RTC_DS3231 rtc; //define RTC

//char daysOfWeek[7][12] = {"domingo","segunda","terça","quarta","quinta","sexta","sabado"}; //define string dos dias da semana

#define motor1 15 //define motor do dispenser 1
#define switch1 13 //define switch do dispenser 1

void entrega_remedio(int motor, int fdc){ //Função que faz dispenser escolhido entregar 1 remédio
    digitalWrite(motor, HIGH);
    delay(100);
    while(digitalRead(fdc) == LOW) {
    digitalWrite(motor, HIGH);
    };
    digitalWrite(motor, LOW);
}

void verifica_data(int hora, int minuto, int diadasemana){ //Função que verifica se horário atual bate com hora programada
  DateTime now = rtc.now();
  if(int(now.minute()) == minuto){
    if(int(now.hour()) == hora){
      if(now.dayOfTheWeek() == diadasemana){
        if(now.second() == 0){
          Serial.println("liberando remedio...");
          entrega_remedio(motor1, switch1); //chama função que libera remedio
        }}}}}

void setup () {
  //SETUP SERIAL
  Serial.begin(115200);

  //SETUP DISPENSERs
  pinMode(motor1, OUTPUT);
  pinMode(switch1, INPUT);

  // SETUP RTC MODULE
  if (!rtc.begin()) {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Ajuste automatico da data com base no horario do PC
}

void loop () {
  DateTime now = rtc.now(); //Atualizada variavél now de data e hora
  //Serial.print("("); 
  //Serial.print(now.dayOfTheWeek()); 
  //Serial.print(") ");
  //Serial.print(now.hour(), DEC); 
  //Serial.print(':'); 
  //Serial.println(now.minute(), DEC);

  verifica_data(18,6, 6); // TESTE INSERIR (HORA, MINUTO, DIA DA SEMANA)
  delay(900); // delay 0.9 seconds
}