/*
 * stm32f446xx.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Philli
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>
#define __vo volatile
/************************************PROCESSOR SPECIFIC DETAILS*****************************************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0			( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1			( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2			( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3			( (__vo uint32_t*)0xE000E10C )
/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0			( (__vo uint32_t*)0XE000E180 )
#define NVIC_ICER1			( (__vo uint32_t*)0XE000E184 )
#define NVIC_ICER2			( (__vo uint32_t*)0XE000E188 )
#define NVIC_ICER3			( (__vo uint32_t*)0XE000E18C )
/*
 * ARM Cortex Mx Processor Priority register Address calculation
 */
#define NVIC_PR_BASE_ADDR	( (__vo uint32_t*)0xE000E400 )

#define NO_PR_BITS_IMPLEMENTED		4

/*
 * Base of addresses of flash and SRAM memories
 */
#define FLASH_BASEADDR		0x08000000U //Addres of flash memory
#define SRAM1_BASEADDR		0x20000000U //Addres of SRAM1
#define SRAM2_BASEADDR		0x2001C000U //Addres of SRAM2
#define ROM					0x1FFF0000U //Addres of ROM = System Memory addres
#define SRAM 				SRAM1_BASEADDR //Same addres of SRAM1

/*
 *AHBx and APBx Bus Peripheral base addresses
 */
#define PERIPH_BASEADDR			0x40000000U //address of the peripheral base
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR //APB1 base address is the peripheral base address
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U

/*
 * Base address of peripherals wich are hanging on AHB1 bus
 * TO DO: Complete for all other peripheral
 */
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0X0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0X0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0X0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0X1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0X1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0X1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0X1C00)
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

/*
 * Base address of peripherals wich are hanging on APB1 bus
 * TO DO: Complete for all other peripheral
 */
#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000)

/*
 * Base address of peripherals wich are hanging on APB2 bus
 * TO DO: Complete for all other peripheral
 */
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR			(APB2PERIPH_BASEADDR + 0x3400)
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800)


/*******************************peripheral register definition structures********************************/
typedef struct{
	__vo uint32_t MODER;                   //GPIO port mode register 										offset:0x00
	__vo uint32_t OTYPER;				  //GPIO port output type register									offset:0x04
	__vo uint32_t OSPEEDER;				  //GPIO port output speed register									offset:0x08
	__vo uint32_t PUPDR;					  //GPIO port pull-up/pull-down register							offset:0x0C
	__vo uint32_t IDR;					  //GPIO port input data register									offset:0x10
	__vo uint32_t ODR;					  //GPIO port output data register									offset:0x14
	__vo uint32_t BSRR;					  //GPIO port bit set/reset register								offset:0x18
	__vo uint32_t LCKR;					  //GPIO port configuration lock register							offset:0x1C
	__vo uint32_t AFR[2];				  //GPIO alternate function low[1]/high[2] register					offset:0x20/0x24
}GPIO_RegDef_t;

/*
 * peripheral definitions (peripheral base addresses typecasted to xxx_RegDef_t)
 */
#define GPIOA ( (GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB ( (GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC ( (GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD ( (GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE ( (GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF ( (GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG ( (GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH ( (GPIO_RegDef_t*) GPIOH_BASEADDR)

#define EXTI  ( (EXTI_RegDef_t*) EXTI_BASEADDR)

/*******************************RCC register definition structures********************************/
typedef struct{
	__vo uint32_t CR;                   	//RCC clock control register												offset:0x00
	__vo uint32_t PLLCFGR;			  		//RCC PLL configuration register 											offset:0x04
	__vo uint32_t CFGR;				  		//RCC clock configuration register											offset:0x08
	__vo uint32_t CIR;					  	//RCC clock interrupt register												offset:0x0C
	__vo uint32_t AHB1RSTR;					//RCC AHB1 peripheral reset register										offset:0x10
	__vo uint32_t AHB2RSTR;					//RCC AHB2 peripheral reset register										offset:0x14
	__vo uint32_t AHB3RSTR;					//RCC AHB3 peripheral reset register										offset:0x18
	__vo uint32_t Reserved0;				//RESERVED
	__vo uint32_t APB1RSTR;					//RCC APB1 peripheral reset register										offset:0x20
	__vo uint32_t APB2RSTR;					//RCC APB2 peripheral reset register										offset:0x24
	__vo uint32_t Reserved1[2];				//RESERVED
	__vo uint32_t AHB1ENR;					//RCC AHB1 peripheral clock enable register									offset:0x30
	__vo uint32_t AHB2ENR;					//RCC AHB2 peripheral clock enable register									offset:0x34
	__vo uint32_t AHB3ENR;					//RCC AHB3 peripheral clock enable register									offset:0x38
	__vo uint32_t Reserved2;				//RESERVED
	__vo uint32_t APB1ENR;					//RCC APB1 peripheral clock enable register									offset:0x40
	__vo uint32_t APB2ENR;					//RCC APB2 peripheral clock enable register									offset:0x44
	__vo uint32_t Reserved3[2];				//RESERVED
	__vo uint32_t AHB1LPENR;				//RCC AHB1 peripheral clock enable in low power mode register				offset:0x50
	__vo uint32_t AHB2LPENR;				//RCC AHB2 peripheral clock enable in low power mode register				offset:0x54
	__vo uint32_t AHB3LPENR;				//RCC AHB3 peripheral clock enable in low power mode register				offset:0x58
	__vo uint32_t Reserved4;				//RESERVED
	__vo uint32_t APB1LPENR;				//RCC APB1 peripheral clock enable in low power mode register				offset:0x60
	__vo uint32_t APB2LPENR;				//RCC APB2 peripheral clock enabled in low power mode register				offset:0x64
	__vo uint32_t Reserved5[2];				//RESERVED
	__vo uint32_t BDCR;						//RCC Backup domain control register										offset:0x70
	__vo uint32_t CSR;						//RCC clock control & status register 										offset:0x74
	__vo uint32_t Reserved6[2];				//RESERVED
	__vo uint32_t SSCGR;					//RCC spread spectrum clock generation register								offset:0x80
	__vo uint32_t PLLI2SCFGR;				//RCC PLLI2S configuration register											offset:0x84
	__vo uint32_t PLLSAICFGR;				//RCC PLL configuration register											offset:0x88
	__vo uint32_t DCKCFGR;					//RCC dedicated clock configuration register								offset:0x8C
	__vo uint32_t CKGATENR;					//RCC clocks gated enable register 											offset:0x90
	__vo uint32_t DCKCFGR2;					//RCC dedicated clocks configuration register 2 							offset:0x94

}RCC_RegDef_t;

/*
 * peripheral definitions structure for EXTI
 */
typedef struct{
	__vo uint32_t IMR;                    //offset:0x00
	__vo uint32_t EMR;				  	  //offset:0x04
	__vo uint32_t RTSR;				 	  //offset:0x08
	__vo uint32_t FTSR;					  //offset:0x0C
	__vo uint32_t SWIER;				  //offset:0x10
	__vo uint32_t PR;					  //offset:0x14
}EXTI_RegDef_t;

/*
 * RCC definitions (RCC base addresses typecasted to RCC_RegDef_t)
 */
#define RCC		( (RCC_RegDef_t*)RCC_BASEADDR)

/*
 * Clock Enable Macros for GPIOx Peripherals
 */
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 << 7))

/*
 * Clock Enable Macros for I2Cx Peripherals
 */
#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))
/*
 * Clock Enable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()		(RCC->APB2ENR |= (1 << 13))
/*
 * Clock Enable Macros for USARTx Peripherals
 */
#define USART1_PCCK_EN()	(RCC->APB2ENR |= (1 << 4))
#define USART2_PCCK_EN()	(RCC->APB1ENR |= (1 << 17))
#define USART3_PCCK_EN()	(RCC->APB1ENR |= (1 << 18))
#define UART4_PCCK_EN()		(RCC->APB1ENR |= (1 << 19))
#define UART5_PCCK_EN()		(RCC->APB1ENR |= (1 << 20))
#define USART6_PCCK_EN()	(RCC->APB2ENR |= (1 << 5))
/*
 *Clock Enable Macros for SYSCFG Peripherals
*/
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1 << 14))
/*
 *Structure for SYSCFG Peripherals
*/
typedef struct{
	__vo uint32_t MEMRMP;                   //offset:0x00
	__vo uint32_t PMC;				  	  	//offset:0x04
	__vo uint32_t EXTICR[4];				//offset:0x08 - 0x14
	__vo uint32_t CMPCR;					//offset:0x20
	__vo uint32_t CFGR;					  	//offset:0x2C

}SYSCFG_RegDef_t;
#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Clock Disable Macros for GPIOx Peripherals
 */
#define GPIOA_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DIS()		(RCC->AHB1ENR &= ~(1 << 7))
/*
 * Clock Disable Macros for I2Cx Peripherals
 */
#define I2C1_PCLK_DIS()		(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DIS()		(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DIS()		(RCC->APB1ENR &= ~(1 << 23))
/*
 * Clock Disable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_DIS()		(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DIS()		(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DIS()		(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DIS()		(RCC->APB2ENR &= ~(1 << 13))
/*
 * Clock Disable Macros for USARTx Peripherals
 */
#define USART1_PCCK_DIS()	(RCC->RCC &= ~(1 << 4))
#define USART2_PCCK_DIS()	(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCCK_DIS()	(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCCK_DIS()		(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCCK_DIS()		(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCCK_DIS()	(RCC->APB2ENR &= ~(1 << 5))
/*
 *Clock Disable Macros for SYSCFG Peripherals
*/
#define SYSCFG_PCLK_DIS()	(RCC->APB2ENR &= ~(1 << 14))

/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 0)); 			(RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 1)); 			(RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 2)); 			(RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 3)); 			(RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 4)); 			(RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 5)); 			(RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 6)); 			(RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()		do {(RCC->AHB1RSTR|= (1 << 7)); 			(RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

#define GPIO_BASE_TO_MACRO(x)		((x == GPIOA) ? 0:\
									(x == GPIOB) ? 1:\
									(x == GPIOC) ? 2:\
									(x == GPIOD) ? 3:\
									(x == GPIOE) ? 4:\
									(x == GPIOF) ? 5:\
									(x == GPIOG) ? 6:\
									(x == GPIOH) ? 7:0)

//some generic macros
#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET 		SET
#define GPIO_PIN_RESET 		RESET
#define FLAG_RESET			RESET
#define FLAG_SET			SET
/*
 * IRQ(Interrupt request) numbers of SRM32F4xx MCU
 */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

/*
 *Macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0				0
#define NVIC_IRQ_PRI15				15

/*
 * peripheral register definition structure for SPI
 */
typedef struct{
	__vo uint32_t CR1;                   		//offset:0x00
	__vo uint32_t CR2;				  	  		//offset:0x04
	__vo uint32_t SR;							//offset:0x08
	__vo uint32_t DR;							//offset:0x0C
	__vo uint32_t CRCPR;					 	//offset:0x10
	__vo uint32_t RXCRCR;					  	//offset:0x14
	__vo uint32_t TXCRCR;					  	//offset:0x18
	__vo uint32_t I2SCFGR;					  	//offset:0x1C
	__vo uint32_t I2SPR;					  	//offset:0x20
}SPI_RegDef_t;

/*
 *SPI Peripheral Definitions
 */

#define SPI1		( (SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2		( (SPI_RegDef_t*) SPI2_BASEADDR)
#define SPI3		( (SPI_RegDef_t*) SPI3_BASEADDR)
#define SPI4		( (SPI_RegDef_t*) SPI4_BASEADDR)
/*
* Bit position definitions for SPI control register 1 (SPI_CR1)
*/
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15
/*
* Bit position definitions for SPI control register 2 (SPI_CR2)
*/
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7
/*
* Bit position definitions for SPI status registers
*/
#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8


#include "stm32f446xx_gpio_driver.h"
#include "stm32f4xx_spi_driver.h"


#endif /* INC_STM32F446XX_H_ */
