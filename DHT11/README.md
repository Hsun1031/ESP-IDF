# DHT11 for ESP-IDF

This is ESP32 and DHT11 Module for ESP-IDF Project.

## DHT11 Datasheet

* [DHT11 Humidity & Temperature Sensor - Mouser Electronics](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)
* [Digital relative humidity & temperature sensor DHT11](https://www.electronicoscaldas.com/datasheet/DHT11_Aosong.pdf)

## PIN

* ![#FF00FF](https://via.placeholder.com/15/FF00FF/000000?text=+) DHT11

|Module PIN                                                              |ESP32 PIN|ESP32 PIN|Module PIN                                                           |
| ----------------------------------------------------------------------:|:-------:|:-------:|:------------------------------------------------------------------- |
|                                                                        |3V3      |VIN      |                                                                     |
|                                                                        |GND      |GND      |                                                                     |
|                                                                        |D15      |D13      |                                                                     |
|                                                                        |D2       |D12      |                                                                     |
|                                                                        |D4       |D14      |![#FF00FF](https://via.placeholder.com/15/FF00FF/000000?text=+) DHT11|
|                                                                        |RX2      |D27      |                                                                     |
|                                                                        |TX2      |D26      |                                                                     |
|                                                                        |D5       |D25      |                                                                     |
|                                                                        |D18      |D33      |                                                                     |
|                                                                        |D19      |D32      |                                                                     |
|                                                                        |D21      |D35      |                                                                     |
|                                                                        |RX0      |D34      |                                                                     |
|                                                                        |TX0      |VN       |                                                                     |
|                                                                        |D22      |VP       |                                                                     |
|                                                                        |D23      |EN       |                                                                     |

## DHT11

|Module|Signal|  +  |  -  |
|:----:|:----:|:---:|:---:|
|ESP32 |D14   |3V3  |GND  |
|DHT11 |S     |+    |-    |
