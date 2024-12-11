/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW_QH_Pin GPIO_PIN_0
#define SW_QH_GPIO_Port GPIOA
#define SW_SH_LD_Pin GPIO_PIN_1
#define SW_SH_LD_GPIO_Port GPIOA
#define SW_CLK_Pin GPIO_PIN_4
#define SW_CLK_GPIO_Port GPIOA
#define ENCODER_Z_Pin GPIO_PIN_5
#define ENCODER_Z_GPIO_Port GPIOA
#define ENCODER_B_Pin GPIO_PIN_6
#define ENCODER_B_GPIO_Port GPIOA
#define ENCODER_A_Pin GPIO_PIN_7
#define ENCODER_A_GPIO_Port GPIOA
#define SIG_N2_Pin GPIO_PIN_0
#define SIG_N2_GPIO_Port GPIOB
#define SIG_P2_Pin GPIO_PIN_1
#define SIG_P2_GPIO_Port GPIOB
#define LED_POWER_Pin GPIO_PIN_8
#define LED_POWER_GPIO_Port GPIOA
#define PC_UART_TXD_Pin GPIO_PIN_9
#define PC_UART_TXD_GPIO_Port GPIOA
#define PC_UART_RXD_Pin GPIO_PIN_10
#define PC_UART_RXD_GPIO_Port GPIOA
#define SIG_P1_Pin GPIO_PIN_15
#define SIG_P1_GPIO_Port GPIOA
#define SIG_N1_Pin GPIO_PIN_3
#define SIG_N1_GPIO_Port GPIOB
#define SCK_7SEG_Pin GPIO_PIN_4
#define SCK_7SEG_GPIO_Port GPIOB
#define RCK_7SEG_Pin GPIO_PIN_5
#define RCK_7SEG_GPIO_Port GPIOB
#define SI_7SEG_Pin GPIO_PIN_6
#define SI_7SEG_GPIO_Port GPIOB
#define LED_UART_Pin GPIO_PIN_7
#define LED_UART_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
