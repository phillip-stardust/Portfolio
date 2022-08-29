/*
 * 006spi_tx_test_testing.c
 *
 *  Created on: 28 ago 2022
 *      Author: Philli
 */
#include "stm32f446xx.h"
#include <string.h>


/*
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 --> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode : 5
 */

//command codes
#define COMMAND_LED_CTRL			0x50
#define COMMAND_SENSOR_READ			0x51
#define COMMAND_LED_READ			0x52
#define	COMMAND_PRINT				0x53
#define COMMAND_ID_READ				0x54

#define	LED_ON						1
#define	LED_OFF						0

//Arduino analog pins
#define ANALOG_PIN0					0
#define ANALOG_PIN1					1
#define ANALOG_PIN2 				2
#define ANALOG_PIN3					3
#define ANALOG_PIN4					4

//Arduino led

#define	LED_PIN						9


void SPI2_GPIOInits(void){
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOxr = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);
}

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

uint8_t SPI_verifyResponse(uint8_t ackbyte){
	if(ackbyte == 0xF5){
		//ack
		return 1;
	}
	return 0;
}

void SPI2_Inits(void){
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;  //GENERATE SCLK OF 2 MHZ
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DIS; //Hardware management enabled for NSS pin

	SPI_Init(&SPI2Handle);
}

void GPIO_ButtonInit(void){
	//this is btn gpio configuration
	GPIO_Handle_t GPIOBtn;
	GPIOBtn.pGPIOxr = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);
}

int main (void){
	uint8_t dummy_write = 0xF5;
	uint8_t dummy_read;

	GPIO_ButtonInit();
	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();
	//this function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	/*
	 * Making SSOE 1 does NSS output enable
	 * The NSS pis is automatically managed by the hardware
	 * i.e when SPE = 1, NSS will be pulled to low
	 * and NSS pin will be high when SPE = 0
	 */
	SPI_SSOEConfig(SPI2, ENABLE);
	while(1){
		//wait till button is pressed
		while(! GPIO_ReadFromInPin(GPIOA, GPIO_PIN_NO_0) );
		delay();

		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		//1. CMD_LED_CTRL <pin no(1)>	<value(1)>
		uint8_t commandcode = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];
		//send command
		SPI_SendData(SPI2, &commandcode, 1);
		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		//send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		//read the ack received by the data
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if (SPI_verifyResponse(ackbyte)){
			//send arguments
			args[0] = LED_PIN;
			args[1] = LED_ON;
			SPI_SendData(SPI2, args, 2);
		}
		//END OF COMMAND CMD_LED_CTRL

		//2 CMD_SENSOR_READ <analog pin number (1)>
		while(! GPIO_ReadFromInPin(GPIOA, GPIO_PIN_NO_0) );
		delay();
		commandcode = COMMAND_SENSOR_READ;
		//send command
		SPI_SendData(SPI2, &commandcode, 1);
		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		//send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		//read the ack received by the data
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if (SPI_verifyResponse(ackbyte)){
			args[0] = ANALOG_PIN0;
			//send arguments
			SPI_SendData(SPI2, args, 2);
			//send dummy bits to clear off the RXNE
			SPI_ReceiveData(SPI2, &dummy_read, 1);

			//insert some delay so that slave can ready the data
			delay();

			SPI_SendData(SPI2, &dummy_write, 1);

			uint8_t analog_read;
			SPI_ReceiveData(SPI2, &analog_read, 1);
		}
		//end of CMD_SENSOR_READ

		//check if SPI is not busy
		while(SPI_getFlagStatus(SPI2, SPI_BUSY_FLAG));
		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
	}

	return 0;
}
