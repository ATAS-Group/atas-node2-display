// Display, Waveshare 1.54 200x200
#include "GxEPD.h"
#include "GxGDEW0154Z04.h"
#include "GxIO.h"
#include "GxIO_SPI.h"
#include "images.h"

// font
#include "FreeSans12pt7b.h"
#include "FreeSans9pt7b.h"

#include <driver/gpio.h>
#include <esp_log.h>
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"

// Arduino, allowes GxEPD
#include "Arduino.h"

// already declared in pins_arduino.h
//static const uint8_t MOSI = 23; 	// blue
//static const uint8_t SCK = 18; 	// yellow
//static const uint8_t SS = 5; 		// orange

static const int PIN_DC =  17; 	// green
static const int PIN_RESET = 16; 	// white
static const int PIN_BUSY = 4; 		// violett

GxIO_Class io(SPI, SS, PIN_DC, PIN_RESET); // arbitrary selection of 17, 16
GxEPD_Class display(io, PIN_RESET, PIN_BUSY); // arbitrary selection of (16), 4

const GFXfont* fontsans9 = &FreeSans9pt7b;
const GFXfont* fontsans12 = &FreeSans12pt7b;
  
void initDisplay(){
	display.init();
}

void displayAlarmOn(){	
	display.setFont(fontsans12);
	display.setCursor(48, 175);
	display.fillScreen(GxEPD_WHITE);
	display.println("Alarm ON");
	display.drawBitmap(alarmbell, 36, 16, 128, 128, GxEPD_BLACK);
	display.update();
}

void displayDashboard(){
	display.setFont(fontsans9);	
	display.fillScreen(GxEPD_WHITE);
	display.drawBitmap(location, 10, 10, 40, 40, GxEPD_BLACK);
	display.setCursor(60, 20);
	display.println("Lat: 46.212134");
	display.setCursor(60, 45);
	display.println("Lng: 7.8932157");
	display.update();
}

void displayAlarm(int alarm){
	display.setFont(fontsans12);
	display.setCursor(48, 175);
	display.fillScreen(GxEPD_WHITE);
	
	switch(alarm) {
	    case 1 : 
			display.drawBitmap(avalanche, 36, 16, 128, 128, GxEPD_BLACK);
			display.println("Avalanche");
			printf("Triggered Alarm: Avalanche\n");
			break;
	    case 2 : 
			display.drawBitmap(landslide, 36, 16, 128, 128, GxEPD_BLACK);
			display.println("Landslide");
			printf("Triggered Alarm: Landslide\n");
	    	break;
		case 3:
			display.drawBitmap(snowflake, 36, 16, 128, 128, GxEPD_BLACK);
			display.setCursor(42, 175);
			display.println("Snowstorm");
			printf("Triggered Alarm: Snowstorm\n");
			break;
		default:
			display.println("Error");
			printf("displayAlarm: error, no alarm defined");
			break;
	}
	display.update();
}

extern "C" void app_main()
{    
	// init Arduino subsystem
	initArduino();
	 
	printf("ATAS Node 2 - Display Example!\n");
	
	initDisplay();
	display.setTextColor(GxEPD_BLACK);
	
	displayDashboard();
	displayAlarmOn();
	displayAlarm(1);
	displayAlarm(2);
	displayAlarm(3);
}



