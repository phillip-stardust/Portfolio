#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h>
#include  <DallasTemperature.h>

//variables WiFi
const char *ssid = "Madoka";
const char *pwd = "ChingueSuMadreMami1979?";
//variables sensor de temperatura
const byte pinDatosDQ= 5;
const byte relaycalentador = 18;
//variables sensor de luz
const byte pinLuz = 33;
int LuzLvl = 0; 
const byte relaylampara1 = 19;
const byte relaylampara2 = 21;
//variables sensor de nl.agua
const int PinTrig =13;
const int PinEcho = 35;
const float VelSon = 34000.0; 
float distancia;
int litros;
//variables sensor de pH
const byte pinPH = 32;
float calibracion_ref = 21.34;
int phval = 0;
unsigned long int promedio;
int buffer_arr[10], temp;
//variables de nvl.humedad
const byte pinHumedad = 34;
int HumedadLvl = 0;
 
OneWire onewireobjeto (pinDatosDQ);
DallasTemperature sensorDS18B20(&onewireobjeto);
//variable de sensores

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250]; 

// Web server conectado al port 8888
WebServer server(8888);

//funcion para conectarse a la red wifi
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pwd);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
   
  }
 
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}


///////funciones de sensores//////
//sensor de temperatura
void Sensordetemperatura(){
  Serial.println("Mandando comandos a los sensores");
  sensorDS18B20.requestTemperatures();

  Serial.print("Temperatura sensor: ");
  Serial.println(sensorDS18B20.getTempCByIndex(0));

  if(sensorDS18B20.getTempCByIndex(0)){
    digitalWrite(relaycalentador, HIGH);
    }
  //delay(3000);
}

//sensor de luz
void Sensordeluz(){
  int LuzLvl = analogRead(pinLuz);
  Serial.print("Nivel de luminosidad: ");
  Serial.println(LuzLvl);

  if(LuzLvl > 3830){
     digitalWrite(relaylampara1, HIGH);
    }
  else
  digitalWrite(relaylampara1, LOW);
  
  //delay(3000);
}
 
 //sensor de humedad
void Sensordehumedad(){
  HumedadLvl = analogRead(pinHumedad);
  Serial.print("Nivel de humedad: ");
  Serial.println(HumedadLvl);
  //delay(3000);
}
 
//sensor de nl.de agua
void Sensornvlagua(){
  iniciarTrigger();
  unsigned long tiempo = pulseIn(PinEcho, HIGH);
 
  distancia = tiempo * 0.000001 * VelSon / 2.0;
  Serial.print("distancia: ");
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  litros = -0.5806*distancia + 20.067;
  Serial.print(litros);
  Serial.print(" litros ");
  Serial.println();
  //delay(3000);
}

//Trigger para sensor de nl.de agua
void iniciarTrigger()
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
}

  
  //sensor de pH
void Sensordeph(){
  for (int i = 0; i < 10; i++)
  {
    buffer_arr[i] = analogRead(pinPH);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  promedio = 0;
  for (int i = 2; i < 8; i++)
    promedio += buffer_arr[i];
  float volt = (float)promedio * 3.3 / 4096 / 6;
  float ph_act = -5.70 * volt + calibracion_ref;
  Serial.print("pH Val:");
  Serial.println(ph_act);
  delay(3000);
}

//setup inicial
void setup() {
  Serial.begin(9600);
  pinMode(PinTrig, OUTPUT);
  pinMode(PinEcho, INPUT);
  sensorDS18B20.begin();
  pinMode(relaylampara1, OUTPUT);
  //connectToWiFi(); 
}

void loop() {
  //Sensordetemperatura(); 
  Sensordeluz();
  //Sensordeph();
  //Sensornvlagua();
  delay(2000);
}
