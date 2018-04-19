# SpaceWeatherLamp
Basic code for 3-LED lamp that reads in live data from the ACE Satellite and outputs it to the three LEDs. 
LEDs can subsequently be manipulated to produce a more visually appealing lamp.

This project reads in three basic pieces of information from the NOAA live feed of the ACE satellite:
- Bulk speed
- Temperature
- Proton density

Bulk speed and temperature are represented by an RGB color range from blue to red in rainbow order.
Proton density is represented by the speed of rainbow cycling. 
However, the proton density multiplier is included in the code in case the user would prefer to avoid the rainbow cycling. 
In that case, just implement the proton density calls similarly to how the bulk speed and temperature calls are implemented.

This project uses:
1. An Adafruit Feather HUZZAH ESP8266. (Should be able to work with any ESP8266 with the right drivers.)
2. Three diffused 10mm RGB LEDs. (Again, any RGB LEDs should work.)
3. All the necessary wires and 9 resistors. 
