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

static const uint8_t PIN_DC =  17; 	// green
static const uint8_t PIN_RESET = 16; 	// white
static const uint8_t PIN_BUSY = 4; 		// violett

GxIO_Class io(SPI, SS, PIN_DC, PIN_RESET); // arbitrary selection of 17, 16
GxEPD_Class display(io, PIN_RESET, PIN_BUSY); // arbitrary selection of (16), 4

const GFXfont* fontsans9 = &FreeSans9pt7b;
const GFXfont* fontsans12 = &FreeSans12pt7b;
  
void initDisplay(){
	display.init();
}

void displayAlarmOn(){
	display.setFont(fontsans12);
	display.setTextColor(GxEPD_BLACK);
	display.setCursor(48, 175);
	display.fillScreen(GxEPD_WHITE);
	display.println("Alarm ON");
	display.drawBitmap(alarmbell, 36, 16, 128, 128, GxEPD_BLACK);
	display.update();
}

extern "C" void app_main()
{    
	// init Arduino subsystem
	initArduino();
	 
	printf("ATAS Node 2 - Display Example!\n");
	
	initDisplay();
	displayAlarmOn();
		
	// IMAGE
	//display.drawBitmap(img, x , y, width, height, color);
	display.drawBitmap(avalanche, 36, 36, 128, 128, GxEPD_BLACK);
	
    // FONT Setup
	display.setTextColor(GxEPD_BLACK);
	display.setFont(fontsans9);
		
	// GPS Data
	display.setCursor(10, 190);
	display.println("Lng: 45.662101");
	display.setCursor(10, 165);
	display.println("Lat: 7.234189");
		
	display.update();
	

}



