# Sliding Window Remote Control
WIP

### BoM
* linear actuator x1
* H-bridge motor driver x1
* 12v power supply
* limit switch x1
* SPST-mom button x1
* Panic cutoff button x1
* SPDT-mom switch x1
* SPDT-latching switch x1
* barrel jack connector
* power button
* 12v 3030 fan x1
* panic button x1
* Arduino wemos D1 Mini x1
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

## Software Configuration
1. Edit wifi_passwords.h to fill in your wifi name and password, then move the wifi_passwords folder into your arduino library folder.
2. Upload Actuator_Control_Module.ino to the D1 Mini via USB
3. Adjust pin numbers if you made changes

## Hardware
1. Mount linear actuator
