#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

int Sensor_value;
String str_out = "Str_start";
String str_Sensor_value = "place holder";
RH_ASK rf_driver;
void setup() {
  rf_driver.init();
}

void loop() {
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
