/*
 * stm32f446xx_gpio_driver.c
 *
 *  Created on: 18 ago 2022
 *      Author: Philli
 */

#include "stm32f446xx_gpio_driver.h"

/*
 * Peripheral clock setup
 */
/*************************************************************************
 * @fn						-GPIO_PeriClkCtrl
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
void GPIO_PeriClkCtrl(GPIO_RegDef_t *pGPIOxr, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pGPIOxr == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if(pGPIOxr == GPIOB){
			GPIOB_PCLK_EN();
		}
		else if(pGPIOxr == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if(pGPIOxr == GPIOD){
			GPIOD_PCLK_EN();
		}
		else if(pGPIOxr == GPIOE){
			GPIOE_PCLK_EN();
		}
		else if(pGPIOxr == GPIOF){
			GPIOF_PCLK_EN();
		}
		else if(pGPIOxr == GPIOG){
			GPIOG_PCLK_EN();
		}
		else if(pGPIOxr == GPIOH){
			GPIOH_PCLK_EN();
		}

	}
	else{
		if(pGPIOxr == GPIOA){
			GPIOA_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOB){
			GPIOB_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOC){
			GPIOC_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOD){
			GPIOD_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOE){
			GPIOE_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOF){
			GPIOF_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOG){
			GPIOG_PCLK_DIS();
		}
		else if(pGPIOxr == GPIOH){
			GPIOH_PCLK_DIS();
		}
	}
}
/*
 * Init and De-Init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp = 0; //temp. register
	//enable the peripheral clock
	GPIO_PeriClkCtrl(pGPIOHandle->pGPIOxr, ENABLE);
	//1.Config the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		//non-interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOxr->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOxr->MODER |= temp;
	}
	else{
		//interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			//Configure the FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			//Configure the RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
			//Configure the RTSR & FTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		//Configure the GPIO port selection in SYSCFG_EXTICR

		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode  = GPIO_BASE_TO_MACRO(pGPIOHandle->pGPIOxr);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);
		//Enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	}
	temp = 0;
	//2.Config the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOxr->OSPEEDER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOxr->OSPEEDER |= temp;
	temp = 0;
	//3.Config the pu-pd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOxr->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOxr->PUPDR |= temp;
	temp = 0;
	//4.Config the optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOxr->OTYPER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOxr->OTYPER |= temp;

	//5.Config the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		//configure the alternate function registers
		uint32_t temp1, temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOxr->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOxr->AFR[temp1] |= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2);
	}
}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOxr){
	if(pGPIOxr == GPIOA){
		GPIOA_REG_RESET();
	}
	else if(pGPIOxr == GPIOB){
		GPIOB_REG_RESET();
	}
	else if(pGPIOxr == GPIOC){
		GPIOC_REG_RESET();
	}
	else if(pGPIOxr == GPIOD){
		GPIOD_REG_RESET();
	}
	else if(pGPIOxr == GPIOE){
		GPIOE_REG_RESET();
	}
	else if(pGPIOxr == GPIOF){
		GPIOF_REG_RESET();
	}
	else if(pGPIOxr == GPIOG){
		GPIOG_REG_RESET();
	}
	else if(pGPIOxr == GPIOH){
		GPIOH_REG_RESET();
	}
}
/*
 * Data Read / Write
 *
 */
/*************************************************************************
 * @fn						-GPIO_ReadFromInPin
 *
 * @brief                   - This function read the value from a given Pin
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               - Pin to read
 * @param[in]               -
 *
 * @return					- 0 or 1
 *
 * @Note                    - none
 */
uint8_t GPIO_ReadFromInPin(GPIO_RegDef_t *pGPIOxr, uint8_t PinNumber){
	uint8_t value;
	value = (pGPIOxr->IDR >> PinNumber) & 0x00000001;
	return value;
}
/*************************************************************************
 * @fn						-GPIO_ReadFromInPort
 *
 * @brief                   - This function read the value from a given Port
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               -
 * @param[in]               -
 *
 * @return					- port value
 *
 * @Note                    - none
 */
uint16_t GPIO_ReadFromInPort(GPIO_RegDef_t *pGPIOxr){
	uint16_t value;
	value = (uint16_t)pGPIOxr->IDR;
	return value;
}
/*************************************************************************
 * @fn						-GPIO_WriteToOutputPin
 *
 * @brief                   - This function write value from a given Port
 *
 * @param[in]               - base address of the gpio peripheral
 * @param[in]               - Pin to write
 * @param[in]               - value to assign to the port
 *
 * @return					-
 *
 * @Note                    - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOxr, uint8_t PinNumber, uint8_t value){
	if(value == GPIO_PIN_SET){
		//write 1 to the output data register at the bit field corresponding pin number
		pGPIOxr ->ODR |= (1 <<PinNumber);
	}
	else{
		pGPIOxr ->ODR &= ~(1 <<PinNumber);
	}
}
/*************************************************************************
 * @fn						-GPIO_WriteToOutputPort
 *
 * @brief                   - This function write value from a given Port
 *
 * @param[in]               - base addres of the gpio peripheral
 * @param[in]               - Port to write
 * @param[in]               - value to assign to the port
 *
 * @return					-
 *
 * @Note                    - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOxr, uint16_t value){
	pGPIOxr->ODR = value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOxr, uint8_t PinNumber){
	pGPIOxr->ODR ^= (1 << PinNumber);
}
/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(IRQNumber <= 31){
			//program ISER0 register
			*NVIC_ISER0 |= (1<< IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64){
			//program ISER1 register
			*NVIC_ISER1 |= (1<< IRQNumber % 32);
		}
		else if (IRQNumber >= 64 && IRQNumber < 96){
			//program ISER2 register
			*NVIC_ISER3 |= (1<< IRQNumber % 64);
		}

		}
	else{
		if(IRQNumber <= 31){
			*NVIC_ICER0 |= (1<< IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64){
			*NVIC_ICER1 |= (1<< IRQNumber % 32);
		}
		else if(IRQNumber >= 6 && IRQNumber < 96){
			*NVIC_ICER3 |= (1<< IRQNumber % 64);
		}
	}
}


void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){
	//find out the ipr register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx*4) |= IRQPriority << shift_amount ;

}

void GPIO_IRQHandling(uint8_t PinNumber){
	//cleat the EXTI pr register corresponding to the pin number
	if(EXTI->PR & (1 <<PinNumber)){
		//clear the register bit
		EXTI->PR |= (1 <<PinNumber);
	}
}
