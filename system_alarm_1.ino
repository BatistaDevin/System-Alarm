#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinos
const int chaveGeral = 5;
const int ldrPin = A0;
const int potPin = A1;
const int lampadaPWM = 11;

const int sensorJanela = 2;
const int sensorPorta = 3;
const int sensorGaragem = 4;

const int ledSistemaLigado = 10;
const int ledAlarme = 6;
const int buzzer = 9;

// Estados
bool lcdLigado = false;
unsigned long tempoAnteriorLed = 0;
long intervaloPiscar = 200;
bool estadoLed = false;

unsigned long tempoAnteriorSom = 0;
const long intervaloSom = 300;
bool tomAtual = false;

void setup() {
  lcd.init();
  lcd.noBacklight();

  pinMode(chaveGeral, INPUT);
  pinMode(sensorJanela, INPUT_PULLUP);
  pinMode(sensorPorta, INPUT_PULLUP);
  pinMode(sensorGaragem, INPUT_PULLUP);

  pinMode(ledSistemaLigado, OUTPUT);
  pinMode(ledAlarme, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(lampadaPWM, OUTPUT);

  digitalWrite(ledSistemaLigado, LOW);
  digitalWrite(ledAlarme, LOW);
  noTone(buzzer);
}

void loop() {
  bool ligado = digitalRead(chaveGeral) == HIGH;
  unsigned long agora = millis();

  if (ligado) {
    // Controle da lâmpada via potenciômetro (só quando ligado)
    int valorPot = analogRead(potPin);
    int brilho = map(valorPot, 1023, 0, 0, 255);  // Invertido
    analogWrite(lampadaPWM, brilho);

    int valorLDR = analogRead(ldrPin);
    bool modoNoite = valorLDR < valorPot;

    // Piscar LED do sistema
    if (agora - tempoAnteriorLed >= intervaloPiscar) {
      tempoAnteriorLed = agora;
      estadoLed = !estadoLed;
      digitalWrite(ledSistemaLigado, estadoLed);
    }

    if (!lcdLigado) {
      lcd.backlight();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sistema Ativo");
      delay(1500);
      lcd.clear();
      lcdLigado = true;
    }

    bool janelaAberta = digitalRead(sensorJanela) == LOW;
    bool portaAberta = digitalRead(sensorPorta) == LOW;
    bool garagemAberta = digitalRead(sensorGaragem) == LOW;

    bool alerta = janelaAberta || portaAberta || garagemAberta;

    // Exibe alertas
    if (janelaAberta) {
      lcd.setCursor(0, 0);
      lcd.print("JANELA ABERTA     ");
      lcd.setCursor(0, 1);
      lcd.print("ALERTA DE ABERTURA");
    } else if (portaAberta) {
      lcd.setCursor(0, 0);
      lcd.print("PORTA ABERTA      ");
      lcd.setCursor(0, 1);
      lcd.print("ALERTA DE ABERTURA");
    } else if (garagemAberta) {
      lcd.setCursor(0, 0);
      lcd.print("GARAGEM ABERTA    ");
      lcd.setCursor(0, 1);
      lcd.print("ALERTA DE ABERTURA");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Tudo fechado      ");
      lcd.setCursor(0, 1);
      lcd.print(modoNoite ? "Modo Noite ON     " : "Modo Dia OK       ");
    }

    // Alarme
    if (alerta && modoNoite) {
      digitalWrite(ledAlarme, HIGH);
      if (agora - tempoAnteriorSom >= intervaloSom) {
        tempoAnteriorSom = agora;
        tomAtual = !tomAtual;
        tone(buzzer, tomAtual ? 1000 : 1500);
      }
    } else {
      digitalWrite(ledAlarme, LOW);
      noTone(buzzer);
    }

  } else {
    // Sistema desligado
    digitalWrite(ledSistemaLigado, LOW);
    digitalWrite(ledAlarme, LOW);
    noTone(buzzer);
    estadoLed = false;
    analogWrite(lampadaPWM, 0); // apaga a lâmpada

    if (lcdLigado) {
      lcd.clear();
      lcd.noBacklight();
      lcdLigado = false;
    }
  }
}
