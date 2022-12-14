


#include <MQUnifiedsensor.h>

/* Definições da MQ135 */
#define RatioMQ135CleanAir 3.6 
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0
#define type "MQ-135"
#define ADC_Bit_Resolution 10
#define RatioMQ135CleanAir 3.6

#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP085.h> //INCLUSÃO DE BIBLIOTECA
#include<Wire.h>
 
//Endereco I2C do MPU6050
const int MPU=0x68;  //pino aberto 0X68 , pino ligado em 3,3V 0x69

//Variaveis globais
int acelX,acelY,acelZ,temperatura,giroX,giroY,giroZ;
 
Adafruit_BMP085 bmp; //OBJETO DO TIPO Adafruit_BMP085 (I2C)

/* Declarando bmp e MQ135 */
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup()
{
  Serial.begin(9600); /* Na velocidade 9600 no Monitor Serial */
  MQ135.setRegressionMethod(1); /* Inicia o MQ135 */
  MQ135.init(); 

  float calcR0 = 0; /* Formula de calibração do MQ135 */
    for(int i = 1; i<=10; i ++)
    {
      MQ135.update(); 
      calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    }
  MQ135.setR0(calcR0/10);
   Serial.begin(9600); //INICIALIZA A SERIAL
  if (!bmp.begin()){ //SE O SENSOR NÃO FOR INICIALIZADO, FAZ
  Serial.println("Sensor BMP180 não foi identificado! Verifique as conexões."); //IMPRIME O TEXTO NO MONITOR SERIAL
  while(1){} //SEMPRE ENTRE NO LOOP
    Serial.begin(9600);     //inicia a comunicação serial
  Wire.begin();                 //inicia I2C
  Wire.beginTransmission(MPU);  //Inicia transmissão para o endereço do MPU
  Wire.write(0x6B);             
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
  }
}

void loop(void)
{ 
  double CO = MQ135.readSensor(); MQ135.setA(605.18); MQ135.setB(-3.937);
  double Alcohol = MQ135.readSensor(); MQ135.setA(77.255); MQ135.setB(-3.18);
  double NH4 = MQ135.readSensor(); MQ135.setA(102.2 ); MQ135.setB(-2.473);
  double Acetona = MQ135.readSensor(); MQ135.setA(34.668); MQ135.setB(-3.369);
  double CO2 = MQ135.readSensor(); MQ135.setA(110.47); MQ135.setB(-2.862);

  Serial.print("CO :");
  Serial.println(CO);
  Serial.print("Alcohol :");
  Serial.println(Alcohol);
  Serial.print("NH4 :");
  Serial.println(NH4);
  Serial.print("Acetona :");
  Serial.println(Acetona);
  Serial.print("CO2 :");
  Serial.println(CO2);

    
    Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(bmp.readTemperature()); //IMPRIME NO MONITOR SERIAL A TEMPERATURA
    Serial.println(" *C (Grau Celsius)"); //IMPRIME O TEXTO NO MONITOR SERIAL
        
    Serial.print("Pressão: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(bmp.readPressure()); //IMPRIME NO MONITOR SERIAL A PRESSÃO
    Serial.println(" Pa (Pascal)"); //IMPRIME O TEXTO NO MONITOR SERIAL
     
    Serial.print("Altitude: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(bmp.readAltitude()); //IMPRIME NO MONITOR SERIAL A ALTITUDE APROXIMADA
    Serial.println(" m (Metros)"); //IMPRIME O TEXTO NO MONITOR SERIAL
    
    Serial.print("Pressão a nível do mar (calculada): "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(bmp.readSealevelPressure()); //IMPRIME NO MONITOR SERIAL A PRESSÃO A NÍVEL DO MAR
    Serial.println(" Pa (Pascal)"); //IMPRIME O TEXTO NO MONITOR SERIAL

    Serial.print("Altitude real: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(bmp.readAltitude(101500)); //IMPRIME NO MONITOR SERIAL A ALTITUDE REAL
    Serial.println(" m (Metros)"); //IMPRIME O TEXTO NO MONITOR SERIAL
     
    Serial.println("-----------------------------------"); //IMPRIME UMA LINHA NO MONITOR SERIAL
    delay(2000); //INTERVALO DE 2 SEGUNDOS
  
  MQ135.update(); /* Atualiza os dados do MQ135 */
  delay(2000);
    Wire.beginTransmission(MPU);      //transmite
  Wire.write(0x3B);                 // Endereço 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);     //Finaliza transmissão
  
  Wire.requestFrom(MPU,14,true);   //requisita bytes
   
  //Armazena o valor dos sensores nas variaveis correspondentes
  acelX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  acelY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acelZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  temperatura=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  giroX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  giroY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  giroZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   
  
   
  //Aguarda 500 ms
  delay(500);
}




// RADIO


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  char text[32] = "";

  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    Serial.println(transData);
  }
}



  exporter.add("Temperatura", Temperatura);
  exporter.add("Altitude", Altitude);
  exporter.add("Pressao", Pressao);
  exporter.add("CO", CO);
  exporter.add("CO2", CO2);
  exporter.add("Alcohol", Alcohol);
  exporter.add("NH4", NH4);
  exporter.add("Acetona", Acetona);
  exporter.add("AcelX", acelX);
  exporter.add("AcelY", acelY);
  exporter.add("AcelZ", acelZ);
  exporter.add("GiroX", giroX);
  exporter.add("GiroY", giroY);
  exporter.add("GiroZ", giroZ);
  exporter.exportJSON();