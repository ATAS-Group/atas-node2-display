/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.cpp providing EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <driver/spi_master.h>
#include <driver/gpio.h>
#include "esp_log.h"


#ifndef EPDIF_H
#define EPDIF_H

// CLK - GPIO 18
#define PIN_CLK 18 // yellow

// MOSI - GPIO 23
#define PIN_MOSI 23 // blue

// RESET - GPIO 16
#define PIN_RESET 16 // white

// DC - GPIO 17
#define PIN_DC 17 // green

// CS - GPIO 5
#define PIN_CS 5 // orange

// Busy - GPIO 4
#define PIN_BUSY 4 // violett

// Pin level definition
#define LOW 0
#define HIGH 1

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransferCmd(unsigned char data);
	static void SpiTransferData(unsigned char data);
};
#endif
