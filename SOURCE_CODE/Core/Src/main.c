#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN 0 */
// Hàm tắt tất cả LED
void clearAllClock(void) {
    HAL_GPIO_WritePin(GPIOA,
                      CLOCK_1_Pin | CLOCK_2_Pin | CLOCK_3_Pin | CLOCK_4_Pin |
                      CLOCK_5_Pin | CLOCK_6_Pin | CLOCK_7_Pin | CLOCK_8_Pin |
                      CLOCK_9_Pin | CLOCK_10_Pin | CLOCK_11_Pin | CLOCK_12_Pin,
                      GPIO_PIN_RESET);
}

// Hàm bật LED theo số num (0-11)
void setNumberOnClock(int num) {
    if (num < 0 || num > 11) return;

    int leds[12] = {
        CLOCK_1_Pin, CLOCK_2_Pin, CLOCK_3_Pin, CLOCK_4_Pin,
        CLOCK_5_Pin, CLOCK_6_Pin, CLOCK_7_Pin, CLOCK_8_Pin,
        CLOCK_9_Pin, CLOCK_10_Pin, CLOCK_11_Pin, CLOCK_12_Pin
    };

    clearAllClock(); // tắt hết
    HAL_GPIO_WritePin(GPIOA, leds[num], GPIO_PIN_SET); // bật LED chỉ định
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN 3 */
    for (int i = 0; i < 12; i++) {
        setNumberOnClock(i);   // bật LED theo số i
        HAL_Delay(500);        // giữ sáng 0.5 giây
    }
    /* USER CODE END 3 */
  }
}

/* ====================== System & GPIO ====================== */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    Error_Handler();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    Error_Handler();
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = CLOCK_1_Pin|CLOCK_2_Pin|CLOCK_3_Pin|CLOCK_4_Pin|
                        CLOCK_5_Pin|CLOCK_6_Pin|CLOCK_7_Pin|CLOCK_8_Pin|
                        CLOCK_9_Pin|CLOCK_10_Pin|CLOCK_11_Pin|CLOCK_12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_InitStruct.Pin, GPIO_PIN_RESET);
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
