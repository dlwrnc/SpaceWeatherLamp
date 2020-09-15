# SpaceWeatherLamp
Basic code for 3-LED lamp that reads in live data from the ACE Satellite and outputs it to the LEDs. 
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
3. All the necessary wires.
4. 9 resistors, three for each LED. 

IMPORTANT: When using this code, please be sure to change the wifi network name and password in order to correspond to your own wifi network and password. 

PLEASE DO NOT CHANGE THE REQUEST FREQUENCY. The .txt file only updates every 60 seconds anyways, and if you request too often the NOAA will get mad. 


# AQILamp (Added 2020)

I've added some extremely similar code for an AQI lamp. This reads exclusively AQI for your city.
This code works primarily for an AQI between 0 and 300. Anything beyond 300 will appear as a pure red light. The color ratios are determined by the AQI on a sliding scale blue (AQI 0) -> green -> yellow -> red (AQI 300). During the fires, my light has primarily been shades of orange and red. 

This project uses:
1. An Adafruit Feather HUZZAH ESP8266. (Should be able to work with any ESP8266 with the right drivers.)
2. One diffused 10mm RGB LED. (Again, any RGB LEDs should work.)
3. All the necessary wires.
4. 3 resistors, three for each LED. 

IMPORTANT: When using this code, please be sure to change the wifi network name and password in order to correspond to your own wifi network and password. 
You will also need to go here: https://aqicn.org/data-platform/token/ and request your own token. Then put your token in for the 'token' variable.

Finally, enter your city for the 'city' variable. Not all cities are available by name alone, so make sure to check the API.

Feel free to change the request frequency to anything up to 1000req/second. It currently queries once per minute. However, there isn't much of a point to changing it to more than once per minute-- the AQI doesn't change that quickly, and the AQI detection stations don't update that quickly either. 

