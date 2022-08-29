/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: 18 ago 2022
 *      Author: Philli
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"

typedef struct{
	uint8_t GPIO_PinNumber; /*GPIO pin possible modes from @GPIO_PIN_NUMBERS*/
	uint8_t GPIO_PinMode; /*GPIO pin possible modes from @GPIO_PINMODE*/
	uint8_t GPIO_PinSpeed; /*GPIO pin possible speed from @GPIO_PINSPEED*/
	uint8_t GPIO_PinPuPdControl; /*GPIO pin possible pull-up / pull-down controls from @GPIO_PINPUPDCTRL*/
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

/*
 * This is a handle structure for a GPIO Pin
 */

typedef struct {
	// pointer to hold the base address of the GPIO peripheral
	GPIO_RegDef_t *pGPIOxr; //This holds the base address of the 	GPIO port to which the pin belong//
	GPIO_PinConfig_t GPIO_PinConfig; //This holds GPIO configuration settings

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15


/* @GPIO_PINMODE
 * GPIO pin possible modes
 */
#define GPIO_MODE_INPUT 	0
#define GPIO_MODE_OUTPUT 	1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG 	3
#define GPIO_MODE_IT_FT		4
#define GPIO_MODE_IT_RT		5
#define GPIO_MODE_IT_RFT	6

/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1

/*
 * @GPIO_PINSPEED
 * GPIO pin possible output speed
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

/*@GPIO_PINPUPDCTRL
 *GPIO PULL UP and PULL DOWN configuration macros
 */

#define GPIO_NO_PUPD		0
#define GPIO_PU				1
#define GPIO_PD				2


/*****************************************************************************************************
 * 								APIs supported by this driver
 * 		For more information about the APIs check the function definitions
 ****************************************************************************************************/
/*
 * Peripheral clock setup
 */
void GPIO_PeriClkCtrl(GPIO_RegDef_t *pGPIOxr, uint8_t EnorDi);
/*
 * Init and De-Init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOxr);
/*
 * Data Read / Write
 *
 */
uint8_t GPIO_ReadFromInPin(GPIO_RegDef_t *pGPIOxr, uint8_t PinNumber);
uint16_t GPIO_ReadFromInPort(GPIO_RegDef_t *pGPIOxr);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOxr, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOxr, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOxr, uint8_t PinNumber);
/*
 * IRQ Configuration and ISR handling p
 */
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);













#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
