# ESP32--IoT-meteo-and-air-quality-station-with-oled

--ENG

IoT weather station - Project by Diego Pellacani -
Detects temperature, humidity, atmospheric pressure and air quality, detects the presence of ammonia (NH3), nitrogen oxides (NOx), alcohol, benzene vapors, smoke, carbon dioxide (CO2)
This program is based on the work of:
Rui Santos & Sara Santos - Random Nerd Tutorials https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
and information for the MQ135 sensor taken from here: https://wokwi.com/projects/388604029799563265
I used the two projects to take inspiration and make just one.

--IT

Stazione meteo IoT - Progetto by Diego Pellacani -
Rileva temperatura, umidità, pressione atmosferica e qualità dell'aria, rileva la presenza di ammoniaca (NH3), ossidi di azoto (NOx), alcool, vapori di benzene, fumo, anidride carbonica (CO2)
Questo programma si basa sul lavoro di:
Rui Santos & Sara Santos - Random Nerd Tutorials https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
e sulle informazioni per il sensore MQ135 prese da qui: https://wokwi.com/projects/388604029799563265
Ho usato i due progetti per prenderne spunto e farne uno solo.

/*
  Adapted from Example from ThingSpeak Library (Mathworks) 
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

Resistor is 1K ohm. in the future it will be replaced with a 5 to 3.3 volt analog converter module, for greater precision and ratio in the measurement scale.
If you don't have the converter you can leave the resistor.


In this figure the ESP32 is without OLED, in my project I used the one with the integrated OLED. If you don't have the display you must remove the part of the code related to it. However, you can connect an external 128x64 display
![Meteo_1_bb](https://github.com/user-attachments/assets/cd7a263d-9f15-4e99-91a5-272223d560f5)

![Immagine WhatsApp 2024-08-30 ore 06 36 44_6c2b3d7d](https://github.com/user-attachments/assets/ab3287ae-b45b-4a66-b486-8295059612ae)

![Immagine WhatsApp 2024-08-30 ore 06 38 34_58df9bad](https://github.com/user-attachments/assets/4bbac203-a231-46f9-9ec6-6414ece2131b)

![Immagine WhatsApp 2024-08-30 ore 06 36 44_b2f6ad6b](https://github.com/user-attachments/assets/2de5d8eb-24e3-4d00-8eae-f7b3cca46781)

![Immagine WhatsApp 2024-08-30 ore 06 36 44_5c07c74b](https://github.com/user-attachments/assets/91117cb6-a710-4648-8f6e-97134d441c0f)
