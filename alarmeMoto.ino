// Alarme moto v1.0 20/02/2017
// felipefiel@yahoo.com.br

unsigned long tempoRetardo = 60000 * 3; // 3min
////////////////////////////////////////////////
#define start 12
#define led 13
#define desarme 10
#define sirene 19
#define rele 9
boolean flag = 0x00;
unsigned long tempo = 0;
void setup() {
  pinMode(start, INPUT_PULLUP);
  pinMode(desarme, INPUT_PULLUP);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(sirene, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(rele, OUTPUT);
  Serial.begin(9600);
  Serial.println("##############################################");
  Serial.println("#                                            #");
  Serial.println("#   Sistema de Alarme para motos e carros.   #");
  Serial.println("#      Desenvolvido por: Felipe Tavares      #");
  Serial.println("#     Para: Claudio Araujo   Versao: 1.0     #");
  Serial.println("#                                            #");
  Serial.println("##############################################\n");
  Serial.println("Sistema em espera..");
}
void loop() {
  if (!digitalRead(start)) {
    flag = 0x01;
    tempo = millis();
    Serial.println(F("Start pressionado, contando tempo pra desarme."));
  }
  while (flag) {
    digitalWrite(led, 0);
    //Serial.println(tempo + tempoRetardo - millis());
    if (tempo + tempoRetardo < millis()) {
      digitalWrite(rele, 1);
      Serial.println(F("Rele de corte acionado, moto desligada"));
      digitalWrite(sirene, 1);
      delay(5000);
    }
    if (!digitalRead(desarme)) {
      flag = 0x00;
      Serial.println(F("Desarme acionado, moto funcionara normalmente"));
      digitalWrite(led, 1);
      digitalWrite(rele, 0);
      digitalWrite(sirene, 0);
    }
  }
}
