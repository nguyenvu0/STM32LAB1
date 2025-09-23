/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - Exercise 3: 4-way traffic light
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
void controlTrafficLight(int direction, int state);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/**
  * @brief  Control 4-way traffic light
  * @param  direction: 0=North, 1=East, 2=South, 3=West
  * @param  state: 0=RED, 1=YELLOW, 2=GREEN
  * @retval None
  */
void controlTrafficLight(int direction, int state) {
    if(direction == 0) { // North
        HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin,     (state == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin,(state == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, (state == 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if(direction == 1) { // East
        HAL_GPIO_WritePin(REDA7_GPIO_Port, REDA7_Pin,     (state == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(YELLOWA8_GPIO_Port, YELLOWA8_Pin,(state == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GREENA9_GPIO_Port, GREENA9_Pin, (state == 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if(direction == 2) { // South
        HAL_GPIO_WritePin(REDA10_GPIO_Port, REDA10_Pin,     (state == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(YELLOWA11_GPIO_Port, YELLOWA11_Pin,(state == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GREENA12_GPIO_Port, GREENA12_Pin, (state == 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if(direction == 3) { // West
        HAL_GPIO_WritePin(REDA13_GPIO_Port, REDA13_Pin,     (state == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(YELLOWA14_GPIO_Port, YELLOWA14_Pin,(state == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GREENA15_GPIO_Port, GREENA15_Pin, (state == 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  int state = 0;
  /* USER CODE END 2 */

  while (1)
  {
    switch(state) {
      case 0:
        // Bắc-Nam XANH (3s), Đông-Tây ĐỎ
        controlTrafficLight(0, 2);
        controlTrafficLight(2, 2);
        controlTrafficLight(1, 0);
        controlTrafficLight(3, 0);
        HAL_Delay(3000);
        state = 1;
        break;

      case 1:
        // Bắc-Nam VÀNG (2s), Đông-Tây ĐỎ
        controlTrafficLight(0, 1);
        controlTrafficLight(2, 1);
        controlTrafficLight(1, 0);
        controlTrafficLight(3, 0);
        HAL_Delay(2000);
        state = 2;
        break;

      case 2:
        // Bắc-Nam ĐỎ, Đông-Tây XANH (3s)
        controlTrafficLight(0, 0);
        controlTrafficLight(2, 0);
        controlTrafficLight(1, 2);
        controlTrafficLight(3, 2);
        HAL_Delay(3000);
        state = 3;
        break;

      case 3:
        // Bắc-Nam ĐỎ, Đông-Tây VÀNG (2s)
        controlTrafficLight(0, 0);
        controlTrafficLight(2, 0);
        controlTrafficLight(1, 1);
        controlTrafficLight(3, 1);
        HAL_Delay(2000);
        state = 0; // lặp lại
        break;
    }
  }
}

/**
  * @brief System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) { Error_Handler(); }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) { Error_Handler(); }
}

/**
  * @brief GPIO Initialization Function
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();

  // Tắt hết LED ban đầu
  HAL_GPIO_WritePin(GPIOA, RED_Pin|YELLOW_Pin|GREEN_Pin|REDA7_Pin
                          |YELLOWA8_Pin|GREENA9_Pin|REDA10_Pin|YELLOWA11_Pin
                          |GREENA12_Pin|REDA13_Pin|YELLOWA14_Pin|GREENA15_Pin,
                          GPIO_PIN_RESET);

  // Cấu hình tất cả pin LED là Output
  GPIO_InitStruct.Pin = RED_Pin|YELLOW_Pin|GREEN_Pin|REDA7_Pin
                      |YELLOWA8_Pin|GREENA9_Pin|REDA10_Pin|YELLOWA11_Pin
                      |GREENA12_Pin|REDA13_Pin|YELLOWA14_Pin|GREENA15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
