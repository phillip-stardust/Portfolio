/*
 * stm32f4xx_spi_driver.c
 *
 *  Created on: 27 ago 2022
 *      Author: Philli
 */
#include "stm32f4xx_spi_driver.h"
#include "stm32f446xx.h"
/*************************************************************************
 * @fn						-SPI_PeriClkCtrl
 *
 * @brief                   - This function enables/disables peripheral clock for the given SPIx
 *
 * @param[in]               - base address of the SPI peripheral
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_PeriClkCtrl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		}
		else if(pSPIx == SPI4){
			SPI4_PCLK_EN();
		}
	}
	else{
		if(pSPIx == SPI1){
			SPI1_PCLK_DIS();
		}
		else if(pSPIx == SPI2){
			SPI2_PCLK_DIS();
		}
		else if(pSPIx == SPI3){
			SPI3_PCLK_DIS();
		}
		else if(pSPIx == SPI4){
			SPI4_PCLK_DIS();
		}
	}
}
uint8_t SPI_getFlagStatus(SPI_RegDef_t *pSPIx, uint32_t flagName){
	if(pSPIx->SR & flagName){
		return FLAG_SET;
	}
	else{
	return FLAG_RESET;
	}
}

/*************************************************************************
 * @fn						-SPI_Init
 *
 * @brief                   - This function initializes the SPI port
 *
 * @param[in]               - base addres of the spi peripheral
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_Init(SPI_Handle_t *pSPIHandle){
	uint32_t tempreg = 0;
	//peripheral clock enable
	SPI_PeriClkCtrl(pSPIHandle->pSPIx, ENABLE);

	//configure device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
	//configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		//for this mode "bidi"mode should be CLEAR
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		//for this mode "bidi"mode should be SET
		tempreg |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//for this mode "bidi"mode should be CLEAR
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
		//RXONLY must be SET
		tempreg |= (1 << SPI_CR1_RXONLY);
	}
	//configure spi serial clk speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed <<SPI_CR1_BR;
	//configure the DD
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF <<SPI_CR1_DFF;
	//configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL <<SPI_CR1_CPOL;
	//configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA <<SPI_CR1_CPHA;
	//configure the SSM
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 |= tempreg;
}
/*************************************************************************
 * @fn						-SPI_DeInit
 *
 * @brief                   - This function disable the SPI port
 *
 * @param[in]               - base addres of the SPI
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx){

}
/*************************************************************************
 * @fn						-SPI_SendData
 *
 * @brief                   - This function is for SPI Tx to send the data to Rx
 *
 * @param[in]               -
 * @param[in]               -
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - This is blocking call
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){
	while(Len > 0){
		//wait until TXE is set
		while(SPI_getFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);
		//check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF) ){
			//16 BIT DFF
			//loading data in CR1
			pSPIx->DR = *((uint16_t*) pTxBuffer);
			Len --;
			Len --;
			(uint16_t*)pTxBuffer++;
		}
		else{
			//8 BIT DFF
			pSPIx->DR = *pTxBuffer;
			Len --;
			pTxBuffer++;
		}
	}
}
/*************************************************************************
 * @fn						-SPI_ReceiveData
 *
 * @brief                   - This function enables/disables peripheral clock for the given GPIO port
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){
	while(Len > 0){
		//wait until RXNE is set
		while(SPI_getFlagStatus(pSPIx,SPI_RXNE_FLAG) == FLAG_RESET);
		//check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF) ){
			//16 BIT DFF
			//loading the data from
			*((uint16_t*) pRxBuffer) = pSPIx->DR;
			Len --;
			Len --;
			(uint16_t*)pRxBuffer++;
		}
		else{
			//8 BIT DFF
			*(pRxBuffer) =pSPIx->DR;
			Len --;
			pRxBuffer++;
		}
	}
}
/*************************************************************************
 * @fn						-SPI_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi){

 *
 * @brief                   - This function enables/disables peripheral clock for the given GPIO port
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi){

}
/*************************************************************************
 * @fn						-SPI_IRQPriorityConfi
 *
 * @brief                   - This function enables/disables peripheral clock for the given GPIO port
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){

}
/*************************************************************************
 * @fn						-SPI_IRQHandling
 *
 * @brief                   - This function enables/disables peripheral clock for the given GPIO port
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               - ENABLE or DISABLE macros
 * @param[in]               -
 *
 * @return					- none
 *
 * @Note                    - none
 */
void SPI_IRQHandling(SPI_Handle_t *pHandle){

}


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
	if(EnorDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
	if(EnorDi == ENABLE){
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}
	else{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}
