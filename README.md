# Sliding Window Remote Control
WIP

![20230130_030828](https://user-images.githubusercontent.com/25805271/215448381-5c63a3d0-f2b8-4b14-948e-479a7cd36ecd.jpg)


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
1. Install arduino ide
2. Download  Wemos drivers from https://www.wemos.cc/en/latest/ch340_driver.html
3. Create a new folder somewhere and extract the contents of the driver zip into this new folder
4. run `SETUP.EXE`
5. Click on `INSTALL`

![image](https://user-images.githubusercontent.com/25805271/215886179-a9582b4a-5cfe-4f45-8f0e-83b2530a9946.png)

6. In arduino IDE click on `File` then `Prefereces...`

![image](https://user-images.githubusercontent.com/25805271/215887396-64f2fc23-8c67-49f5-9c80-0de3da4ef14f.png)

7. under `Additional Boards Manager URLs:` paste ```http://arduino.esp8266.com/stable/package_esp8266com_index.json```

![image](https://user-images.githubusercontent.com/25805271/215887636-b4c58f7d-9bc9-4413-918a-bbcce9718cf3.png)

8. Click on `Sketch`, then `Include Library` then `Manage Libraries`, or press the key combination `Ctr+Shift+I`.

![image](https://user-images.githubusercontent.com/25805271/215888631-48ed80e5-b5ed-4ff4-8316-0b54e8809504.png)

9. Search for a library called `ESP8266 microgear` and click `INSTALL`.

![image](https://user-images.githubusercontent.com/25805271/215889096-7229ebf6-a2e9-4927-bee7-4cbb482b37f6.png)

10. Click on `Tools`, then `Board` then `Board Manager` or press the key combination `Ctr+Shift+B`.

![image](https://user-images.githubusercontent.com/25805271/215889488-aa1a84ed-05a4-4808-8d0c-ca89f6e0da3e.png)

11. Search for `ESP8266` and install the board

![image](https://user-images.githubusercontent.com/25805271/215889716-cde856a1-789d-443a-b18e-0f3d8cea981c.png)

12. Make sure the switch that controls the motor driver 5v supply is shut off and/or you unplug the unit, or you'll damage the driver or your pc or both

13. Plug in the D1 mini with a micro-usb cable

14. Click on `Select Board` and select the `Unknown COMx`.

![image](https://user-images.githubusercontent.com/25805271/215890013-8736d73d-9cc3-4650-bce1-e54d1d2c9db6.png)

15. Search for `d1` and select `LOLIN(WEMOS) D1 R2 & mini`

![image](https://user-images.githubusercontent.com/25805271/215890358-87216288-ffab-4c58-adf7-1f4989d8c059.png)

16. Copy the folder `wifi_passwords` to your arduino library folder (under `Documents > Arduino > libraries` by default)

![image](https://user-images.githubusercontent.com/25805271/215891138-b6d8e9e7-ac1d-453c-a86b-2797787050ee.png)

17. Edit wifi_passwords.h to fill in your wifi name and password, replacing the text and the <> but leaving the " ".

18. Upload Actuator_Control_Module.ino to the D1 Mini via USB

![image](https://user-images.githubusercontent.com/25805271/215891711-b0bcb784-3c1d-4e01-a69e-24805f02641f.png)

19. Adjust the pin number definitions if you made any changes to the default. 

20. Unplug the D1 from your computer, plug in the 12v PSU to the unit, and flip the internal power connection switch.

21. Go to `https://www.python.org/downloads/` and click `Download Python 3.5.1`. 

![image](https://user-images.githubusercontent.com/25805271/215895270-fc627207-14a5-41df-b08d-ab29467ded09.png)

22. Run the python installer

23. Checkmark `Use admin priveleges when installing py.exe` and `Add python.exe to PATH` options, then click `Install Now`

![image](https://user-images.githubusercontent.com/25805271/215895805-d114e87a-9dd6-42ef-b22a-4f79a896796b.png)

24. Restart Arduino IDE.

25. Check your firewall settings to make sure the OTA connection isn't being blocked. I had to set my network to private for OTA to work. 

26. If all went well you should see the OTA connection come up as an upload target option.

27. Once you upload the sketch you will have to restart the IDE to be able to upload again. This bug should be fixed soon<sup>TM</sup>

## Hardware
1. Mount linear actuator
