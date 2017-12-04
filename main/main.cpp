#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "sdkconfig.h"

#include "epd1in54.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1

//unsigned char image[1024];
//Paint paint(image, 0, 0);    // width should be the multiple of 8 

extern "C" void app_main()
{    
    printf("ATAS Node 2 - Display Example!\n");
	
    Epd epd;
    if (epd.Init(lut_full_update) != 0) {
        printf("e-Paper init failed\n");
    }
	
    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED);

    paint.DrawStringAt(30, 14, "ATAS", &Font16, UNCOLORED);

    /* Display the frame_buffer */
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    epd.DelayMs(2000);
	
    epd.SetFrameMemory(IMAGE_DATA, 0, 0, epd.width, epd.height);
    epd.DisplayFrame();
    epd.SetFrameMemory(IMAGE_DATA, 0, 0, epd.width, epd.height);
    epd.DisplayFrame();
	
	/*
	paint.SetRotate(ROTATE_0);
	paint.SetWidth(200);
	paint.SetHeight(24);*/

	/* For simplicity, the arguments are explicit numerical coordinates */
	/*
	paint.Clear(COLORED);
	paint.DrawStringAt(30, 4, "Hello world!", &Font16, UNCOLORED);
	epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());
	epd.DisplayFrame();
	
	if (epd.Init(lut_partial_update) != 0) {
	  printf("e-Paper init failed");
	  return;
	} */   
}

