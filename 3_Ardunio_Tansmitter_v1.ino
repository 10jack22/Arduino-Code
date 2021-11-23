#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

int time_delay = 50;

int Mux_1 = 0;
int Mux_2 = 1;
int Mux_3 = 2;
int Mux_4 = 3;
int Mux_en = 4;
int Mux_Sig = A0;

int Sensor_value;
String str_out = "Str_start";
String str_Sensor_value = "place holder";

RH_ASK rf_driver;
void setup(){
  pinMode(Mux_1, OUTPUT); 
  pinMode(Mux_2, OUTPUT); 
  pinMode(Mux_3, OUTPUT); 
  pinMode(Mux_4, OUTPUT); 

  digitalWrite(Mux_1, LOW);
  digitalWrite(Mux_2, LOW);
  digitalWrite(Mux_3, LOW);
  digitalWrite(Mux_4, LOW);

  rf_driver.init();

  Serial.begin(9600);
}
void loop(){
  str_out = "Str_start";
  for(int i = 0; i < 15; i ++){
    Sensor_value =(readMux(i));
    str_Sensor_value = String(Sensor_value);
    str_out = str_out + "," + str_Sensor_value;
    delay(time_delay);
  }
  static char *msg = str_out.c_str();

  rf_driver.send((uint8_t*)msg,strlen(msg));
  rf_driver.waitPacketSent();

}


float readMux(int channel){
  int controlPin[] = {Mux_1, Mux_2, Mux_3, Mux_4};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(Mux_Sig);

  //return the value
  float voltage = (val * 5.0) / 1024.0;
  return voltage;
}
