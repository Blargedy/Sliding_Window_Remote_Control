# Sliding Window Remote Control
WIP

### BoM
* linear actuator x1
* L298N H-bridge motor driver x1 [Amazon](https://www.amazon.ca/gp/product/B07D1HP3SJ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* 12v power supply with 5.5mm barrel jack x1 [Amazon](https://www.amazon.ca/gp/product/B085ZZ86ZJ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* limit switch x1 [Amazon](https://www.amazon.ca/gp/product/B07YKH3TDR/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* SPST-mom button x1 [Amazon](https://www.amazon.ca/gp/product/B07Q6C3NSN/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* Panic cutoff button x1 [Amazon](https://www.amazon.ca/gp/product/B07WTL3KPB/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* SPDT-mom switch x1 [Amazon](https://www.amazon.ca/gp/product/B01LYGWWHA/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* SPDT-latching switch x1 [Amazon](https://www.amazon.ca/gp/product/B01BTTOEQ6/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* 5.5mm x 2.1mm barrel jack connector [Amazon](https://www.amazon.ca/gp/product/B092Z6ZG3V/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* power button x1 [Amazon](https://www.amazon.ca/gp/product/B08225LGRT/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* 12v A4x20 fan x1 [Amazon](https://www.amazon.ca/gp/product/B071W93333/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* panic button x1 [Amazon](https://www.amazon.ca/gp/product/B07WTL3KPB/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* Arduino Wemos D1 Mini x1 [Amazon](https://www.amazon.ca/gp/product/B07WWFND3B/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* 2 port wago x1
* 3 port wago x1
* 5 port wago x2
* 2 port microfit-3 connectors and crimps x2
* Dupont headers and crimps
* ferrule crimps
* M3 hardware
* M3 heat inserts (4mmH x 5mmD) x4
* wires

## Part printing
Clearances were designed for ABS/ASA shrinkages, but the parts can be made of basically any filament

## Electronics
1. solder and crimp electric box
2. Crimp linear actuator

![20230130_030009](https://user-images.githubusercontent.com/25805271/215446989-5598ee22-ec45-40d6-be63-3765f77d34f4.jpg)


## Software Configuration
1. Edit wifi_passwords.h to fill in your wifi name and password, then move the wifi_passwords folder into your arduino library folder.
2. Upload Actuator_Control_Module.ino to the D1 Mini via USB
3. Adjust pin numbers if you made changes

## Hardware
1. Mount linear actuator
