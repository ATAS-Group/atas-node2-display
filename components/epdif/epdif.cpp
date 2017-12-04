/**
 *  @filename   :   epdif.cpp
 *  @brief      :   Implements EPD interface functions
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
#include "epdif.h"

esp_err_t ret;
spi_device_handle_t spi;

EpdIf::EpdIf() {
};
EpdIf::~EpdIf() {
};

void EpdIf::DigitalWrite(int pin, int value) {
    gpio_set_level((gpio_num_t)pin, value);
}

int EpdIf::DigitalRead(int pin) {
    return gpio_get_level((gpio_num_t)pin);
}

void EpdIf::DelayMs(unsigned int delaytime) {
    vTaskDelay(delaytime / portTICK_PERIOD_MS);
}

void EpdIf::SpiTransferCmd(unsigned char data){
	// set to send cmd
	gpio_set_level((gpio_num_t)PIN_DC, LOW);
	
	gpio_set_level((gpio_num_t)PIN_CS, LOW);	
	
	// SPI Transfer
	spi_transaction_t t;
	    memset(&t, 0, sizeof(t));       //Zero out the transaction
	    t.length=8;                     //Command is 8 bits
	    t.tx_buffer=&data;               //The data is the cmd itself
	    ret=spi_device_transmit(spi, &t);  //Transmit!
	    assert(ret==ESP_OK);            //Should have had no issues
	
	gpio_set_level((gpio_num_t)PIN_CS, HIGH);
}

void EpdIf::SpiTransferData(unsigned char data){
	// set to send data
	gpio_set_level((gpio_num_t)PIN_DC, HIGH);
	
	gpio_set_level((gpio_num_t)PIN_CS, LOW);
	
	// SPI Transfer
	spi_transaction_t t;
	    memset(&t, 0, sizeof(t));       //Zero out the transaction
	    t.length=8;                 //Len is in bytes, transaction length is in bits.
	    t.tx_buffer=&data;               //Data
	    ret=spi_device_transmit(spi, &t);  //Transmit!
	    assert(ret==ESP_OK);            //Should have had no issues.
			
	gpio_set_level((gpio_num_t)PIN_CS, HIGH);
}

int EpdIf::IfInit(void) {
	gpio_set_direction((gpio_num_t)PIN_CS, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)PIN_RESET, GPIO_MODE_OUTPUT);
	gpio_set_direction((gpio_num_t)PIN_DC, GPIO_MODE_OUTPUT);
	gpio_set_direction((gpio_num_t)PIN_BUSY, GPIO_MODE_INPUT);
	
	spi_bus_config_t buscfg;
	buscfg.mosi_io_num = PIN_MOSI;
	buscfg.sclk_io_num = PIN_CLK;
	buscfg.miso_io_num = -1; // not used
	buscfg.quadwp_io_num = -1; // not used
	buscfg.quadhd_io_num = -1; // not used
	
	// MSB first by default
	spi_device_interface_config_t dev_config;
	dev_config.mode             = 0;
	dev_config.cs_ena_posttrans = 0;
	dev_config.cs_ena_pretrans  = 0;
	dev_config.clock_speed_hz   = 2000000;
	dev_config.spics_io_num     = PIN_CS;
	dev_config.queue_size       = 7;
	dev_config.pre_cb           = NULL;
	dev_config.post_cb          = NULL;
	dev_config.flags            = 0;
	
	//Initialize the SPI bus
	ret=spi_bus_initialize(VSPI_HOST, &buscfg, 1);
	printf("SPI: bus initialization done\r\n");
	assert(ret==ESP_OK);
	
	//Attach the display
	ret=spi_bus_add_device(VSPI_HOST, &dev_config, &spi);
	printf("SPI: display device added to spi bus (%d)\r\n", VSPI_HOST);
	assert(ret==ESP_OK);
		
	return 0;
}