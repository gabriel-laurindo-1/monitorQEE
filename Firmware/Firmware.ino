/**
 * @file: Firmware Energy Monitor
 * @autor: Gabriel Laurindo
 * @version: 0.0.3

  Mapeamento de Hardware
            DS3231    -> Arduino Uno
            -----------------------------------------
            VCC pin   -> Arduino 5V
            GND pin   -> Arduino GND
            SDA pin   -> Arduino Digital 18 (SDA)
            SCL pin   -> Arduino Digital 19 (SCL)
            -----------------------------------------
*/

// ===== Inclusao das bibliotecas =====
#include "EmonLib.h"
#include "RTClib.h"

// ===== Criacao dos objetos  =====
EnergyMonitor emon1; // Objeto para a leitura de corrente
RTC_DS3231 rtc;


// ===== Constantes e diretivas gerais =====
#define nAmostras 16
const unsigned char measureInterval = 1;

// ===== Pins Hardware =====
#define pinPF   3
#define pinFreq 4
#define pinVol  A0
#define pinCur  A1

// ===== Variaveis  =====
float frequency = 60;
float nano = 1 * pow (10, -6);

float angle_max = 0;

float frequency_meter = 0; // [Hz] - Retorna a frequencia do sinal
float powerFactor_meter = 0;
float voltageAC_meter = 0;
float currentAC_meter = 0;

// ===== Prototipos de funcao =====
float measureFrequency(unsigned char pinoSinal);
float measurePowerFactor(unsigned char pinoSinal, float frequency_value);
float measureVoltageAC(unsigned char pinoSinal);
float measureCurrentAC();
void RTC_print();
void dataRegister();

// ===== Configuracao inicial =====
void setup() {

  pinMode(pinPF, INPUT);
  pinMode(pinFreq, INPUT);

  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pinCur, 60);

  Serial.begin(115200);

  if (! rtc.begin()) {
    Serial.println("Modulo RTC nao foi encontrado");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
//    rtc.adjust(DateTime(2020, 10, 22, 13, 23, 0));
  }

}

// ===== Rotina principal =====
void loop()
{
  if ((rtc.now().second() % measureInterval) == 0)
  {
    dataRegister();
  }
}

// ===== Desenvolvimento das funcoes =====
float measureFrequency(unsigned char pinoSinal)
{
  float period = (pulseIn( pinoSinal, HIGH ) + pulseIn( pinoSinal, LOW )) * nano;
  if (period == 0)
    return 0;
  else
    return  1.0 / period ;
}

float measurePowerFactor(unsigned char pinoSinal, float frequency_value)
{
  float powerFactor = 0;
  float angle = 0.0;
  float phase = 0.0;
  float degree = 360.0;
  // put your main code here, to run repeatedly:
  for (int i = 0; i < nAmostras; i++)
  {
    angle = ( ( ( ( pulseIn( pinoSinal, HIGH ) ) * nano ) * degree ) * frequency_value );

    if (angle > angle_max)
    {
      angle_max = angle; 
      powerFactor = cos(angle_max * PI / 180.0 );
    }
  }
  if (angle_max > 360) 
  {
    angle_max = 0; 
    powerFactor = 1; 
  }
  
  angle = 0;
  angle_max = 0;
  return powerFactor;
}

float measureVoltageAC(unsigned char pinoSinal)
{
  long acc = 0;
  for (int i = 0; i < nAmostras; i++) acc += analogRead(pinoSinal);

  return ((acc / float(nAmostras)) * 230.0 / 1023.0);
}

float measureCurrentAC()
{
  return emon1.calcIrms(1480); //Calcula a corrente
}

void RTC_print()
{
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('-');
  Serial.print(now.month(), DEC);
  Serial.print('-');
  Serial.print(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(" \t ");
}

void dataRegister()
{
  currentAC_meter = measureCurrentAC();
  voltageAC_meter = measureVoltageAC(pinVol);
  frequency_meter = measureFrequency(pinFreq);  // --- Leitura da frequencia ---
  powerFactor_meter = measurePowerFactor(pinPF, frequency_meter);


  RTC_print();
  Serial.print("Freq: ");
  Serial.print(frequency_meter);
  Serial.print(" Hz \t ");
  Serial.print("PHASE: ");
  Serial.print(acos(powerFactor_meter) * 180 / PI);
  Serial.print(" \t ");
  Serial.print("PF: ");
  Serial.print(powerFactor_meter);
  Serial.print(" \t ");
  Serial.print("Cur: ");
  Serial.print(currentAC_meter);
  Serial.print(" A \t ");
  Serial.print("Vlt: ");
  Serial.print(voltageAC_meter);
  Serial.println(" V");

}
