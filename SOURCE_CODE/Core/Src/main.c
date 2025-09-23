/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - Exercise 4: 7-Segment Display
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
void display7SEG(int num);
/* USER CODE END PFP */

/* USER CODE BEGIN PV */
// 7-segment display patterns for digits 0-9
// bit0=A, bit1=B, ..., bit6=G
const uint8_t seven_seg_digits[10] = {
    0x3F, // 0: A,B,C,D,E,F
    0x06, // 1: B,C
    0x5B, // 2: A,B,G,E,D
    0x4F, // 3: A,B,G,C,D
    0x66, // 4: F,G,B,C
    0x6D, // 5: A,F,G,C,D
    0x7D, // 6: A,F,G,E,D,C
    0x07, // 7: A,B,C
    0x7F, // 8: A,B,C,D,E,F,G
    0x6F  // 9: A,B,C,D,F,G
};
/* USER CODE END PV */

/* USER CODE BEGIN 0 */

/**
  * @brief  Display number on 7-segment display
  * @param  num: Number to display (0-9)
  * @retval None
  */
void display7SEG(int num) {
    if(num < 0 || num > 9) return;

    uint8_t pattern = seven_seg_digits[num];

    // Set each segment (PB0-PB6) based on pattern
    for(int i = 0; i < 7; i++) {
        if(pattern & (1 << i)) {
            HAL_GPIO_WritePin(GPIOB, 1 << i, GPIO_PIN_RESET); // Common Anode: LOW = sáng
        } else {
            HAL_GPIO_WritePin(GPIOB, 1 << i, GPIO_PIN_SET);   // HIGH = tắt
        }
    }
}

/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  int counter = 0;
  /* USER CODE END 2 */

  while (1)
  {
    // Hiển thị số trên 7-seg
    display7SEG(counter);

    // LED PA5 nhấp nháy để test
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

    HAL_Delay(1000);

    counter++;
    if(counter > 9) counter = 0; // Reset về 0 sau khi tới 9
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

  // Enable GPIO Ports Clock
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // PA5: LED test
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  // PB0-PB6: segment output, ban đầu tắt (HIGH vì common anode)
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin, GPIO_PIN_SET);

  // Configure PA5 (LED)
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure PB0-PB6 (7-seg)
  GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                      |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add report if needed */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
