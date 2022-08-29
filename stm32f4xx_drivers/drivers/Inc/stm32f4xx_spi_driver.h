/*
 * stm32f4xx_spi_driver.h
 *
 *  Created on: 27 ago 2022
 *      Author: Philli
 */

#ifndef INC_STM32F4XX_SPI_DRIVER_H_
#define INC_STM32F4XX_SPI_DRIVER_H_

#include "stm32f446xx.h"

/*
 * config structure for SPIx peripherals
 */
typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig; // this config decide whether the bus is full duplex/ half duplex / simplex
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

/*
 * Handle structure for SPIx peripheral
 */
typedef struct {
	// pointer to hold the base address of the GPIO peripheral
	SPI_RegDef_t *pSPIx; //This holds the base address of the SPI Peripherals {1, 2, 3, 4}//
	SPI_Config_t SPIConfig; //This holds SPIx configuration settings

}SPI_Handle_t;

/*
 *@SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0
/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3
/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2					0
#define SPI_SCLK_SPEED_DIV4					1
#define SPI_SCLK_SPEED_DIV8					2
#define SPI_SCLK_SPEED_DIV16				3
#define SPI_SCLK_SPEED_DIV32				4
#define SPI_SCLK_SPEED_DIV64				5
#define SPI_SCLK_SPEED_DIV128				6
#define SPI_SCLK_SPEED_DIV256				7
/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS	0
#define SPI_DFF_16BITS	1
/*
 * @SPI_CPOL
 */
#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0
/*
 * @SPI_CPHA
 */
#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0
/*
 * @SPI_SSM
 */
#define SPI_SSM_EN		1
#define SPI_SSM_DIS		0
/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1 << SPI_SR_BSY)

/*****************************************************************************************************
 * 								APIs supported by this driver
 * 		For more information about the APIs check the function definitions
 ****************************************************************************************************/
/*
 * Peripheral clock setup
 */
void SPI_PeriClkCtrl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
/*
 * Init and De-Init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
/*
 * Data Send / Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/*
 * Other peripheral control APIs
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
uint8_t SPI_getFlagStatus(SPI_RegDef_t *pSPIx, uint32_t flagName);


#endif /* INC_STM32F4XX_SPI_DRIVER_H_ */
