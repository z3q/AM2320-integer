#include "AM2320-int.h"
#include <Wire.h>
// 
// AM2320 Temperature & Humidity Sensor library for Arduino
// Сделана Тимофеевым Е.Н., доработана на целочисленную математику Воронцовым К.А.

unsigned int CRC16(byte *ptr, byte length) 
{ 
      unsigned int crc = 0xFFFF; 
      uint8_t s = 0x00; 

      while(length--) {
        crc ^= *ptr++; 
        for(s = 0; s < 8; s++) {
          if((crc & 0x01) != 0) {
            crc >>= 1; 
            crc ^= 0xA001; 
          } else crc >>= 1; 
        } 
      } 
      return crc; 
} 

AM2320::AM2320()
{
	Wire.begin();
}

byte AM2320::Read()
{
  byte buf[8];
  for (byte s = 0; s < 8; s++) buf[s] = 0x00;
  // Пробуждаем датчик AM2320
  Wire.beginTransmission(AM2320_address);
  Wire.endTransmission();
  // запрос 4 байт (температуры и влажности)
  Wire.beginTransmission(AM2320_address);
  Wire.write(0x03);// запрос
  Wire.write(0x00); // с 0-го адреса
  Wire.write(0x04); // 4 байта
  if (Wire.endTransmission(1) != 0) return 1;
  delayMicroseconds(1600); //>1.5ms
  // считываем результаты запроса
  Wire.requestFrom(AM2320_address, 0x08);
  for (byte i = 0; i < 0x08; i++) buf[i] = Wire.read();

  // CRC check
  unsigned int Rcrc = buf[7] << 8;
  Rcrc += buf[6];
  if (Rcrc == CRC16(buf, 6)) {
    t = ((buf[4] & 0x7F) << 8) + buf[5]; // x10, don't forget to divide by 10!
    //t = ((buf[4] & 0x80) >> 7) == 1 ? t * (-1) : t;
    if (((buf[4] & 0x80) >> 7) == 1) t = t * (-1);

    unsigned int humidity = (buf[2] << 8) + buf[3];
    h = byte (humidity / 10);
    return 0;
  }
  return 2;
}
