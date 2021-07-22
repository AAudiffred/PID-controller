#include <Arduino.h>
#include <HBridge.h>
#include <QuadratureEncoder.h>
#include <ESP32_PWM.h>
#include <PID.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
HBridge driver;
PID pid;
QuadratureEncoder encoder;
uint8_t i=0;
uint8_t c=0;
ulong current_time, prev_time;
uint16_t dt_ms = 10;

void setup()
{
  SerialBT.begin("Audiffred");
  Serial.begin(9600);
  driver.setup(19,18,0,1,16.0f);
  encoder.setup(5,21, 1632.67f);
  pid.setup(1.0f, 0, 0, 100.0f);
  prev_time = millis();
}

void loop()
{
  current_time = millis();
  if (current_time - prev_time > dt_ms)
  {
    prev_time = current_time;
    driver.setSpeed(pid.calculate(encoder.getAngle(), dt_ms/1000.0));
    Serial.printf("%f \n",encoder.getAngle());
  }
  if (Serial.available())
  {
    pid.reference = Serial.readStringUntil('\n').toFloat();
  }
}
