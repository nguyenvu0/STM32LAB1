/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - Exercise 5: Traffic Light + 7SEG
  ******************************************************************************
  * @attention
  *
  * Author: YourName
  * Date: 2025
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
void display7SEG(int num);
/* USER CODE END PFP */

/* USER CODE BEGIN PV */
// Bảng mã số 0–9 cho LED 7 đoạn (Common Cathode)
// bit0=A, bit1=B, ..., bit6=G
const uint8_t seven_seg_digits[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};
/* USER CODE END PV */

/* USER CODE BEGIN 0 */

// Hàm hiển thị số trên LED 7 đoạn
void display7SEG(int num) {
    if(num < 0 || num > 9) return;
    uint8_t pattern = seven_seg_digits[num];

    HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, (pattern & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, (pattern & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, (pattern & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, (pattern & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, (pattern & 0x10) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, (pattern & 0x20) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, (pattern & 0x40) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

// Hàm điều khiển đèn giao thông
// direction: 0=North, 1=East, 2=South, 3=West
// state: 0=RED, 1=YELLOW, 2=GREEN
void controlTrafficLight(int direction, int state) {
    if(direction == 0) { // North
        HAL_GPIO_WritePin(GPIOA, LED_RED_Pin,    (state==0)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin, (state==1)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin,  (state==2)?GPIO_PIN_SET:GPIO_PIN_RESET);
    }
    else if(direction == 1) { // East
        HAL_GPIO_WritePin(GPIOA, LED_REDA7_Pin,     (state==0)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_YELLOWA8_Pin,  (state==1)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_GREENA9_Pin,   (state==2)?GPIO_PIN_SET:GPIO_PIN_RESET);
    }
    else if(direction == 2) { // South
        HAL_GPIO_WritePin(GPIOA, LED_REDA10_Pin,    (state==0)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_YELLOWA11_Pin, (state==1)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_GREENA12_Pin,  (state==2)?GPIO_PIN_SET:GPIO_PIN_RESET);
    }
    else if(direction == 3) { // West
        HAL_GPIO_WritePin(GPIOA, LED_REDA13_Pin,    (state==0)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_YELLOWA14_Pin, (state==1)?GPIO_PIN_SET:GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, LED_GREENA15_Pin,  (state==2)?GPIO_PIN_SET:GPIO_PIN_RESET);
    }
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
    // Phase 1: North-South Green (5s), East-West Red
    for(int t=5; t>0; t--){
        display7SEG(t);
        controlTrafficLight(0,2); // North GREEN
        controlTrafficLight(2,2); // South GREEN
        controlTrafficLight(1,0); // East RED
        controlTrafficLight(3,0); // West RED
        HAL_Delay(1000);
    }

    // Phase 2: North-South Yellow (2s), East-West Red
    for(int t=2; t>0; t--){
        display7SEG(t);
        controlTrafficLight(0,1); // North YELLOW
        controlTrafficLight(2,1); // South YELLOW
        controlTrafficLight(1,0);
        controlTrafficLight(3,0);
        HAL_Delay(1000);
    }

    // Phase 3: East-West Green (5s), North-South Red
    for(int t=5; t>0; t--){
        display7SEG(t);
        controlTrafficLight(0,0);
        controlTrafficLight(2,0);
        controlTrafficLight(1,2);
        controlTrafficLight(3,2);
        HAL_Delay(1000);
    }

    // Phase 4: East-West Yellow (2s), North-South Red
    for(int t=2; t>0; t--){
        display7SEG(t);
        controlTrafficLight(0,0);
        controlTrafficLight(2,0);
        controlTrafficLight(1,1);
        controlTrafficLight(3,1);
        HAL_Delay(1000);
    }
  }
}

/* Clock config & GPIO init giữ nguyên CubeMX sinh */
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

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // Init all LEDs = OFF
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin
                          |LED_REDA7_Pin|LED_YELLOWA8_Pin|LED_GREENA9_Pin
                          |LED_REDA10_Pin|LED_YELLOWA11_Pin|LED_GREENA12_Pin
                          |LED_REDA13_Pin|LED_YELLOWA14_Pin|LED_GREENA15_Pin, GPIO_PIN_RESET);

  // Init 7SEG = OFF
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin, GPIO_PIN_RESET);

  // Configure traffic LEDs (PA4–PA15)
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_YELLOW_Pin|LED_GREEN_Pin
                       |LED_REDA7_Pin|LED_YELLOWA8_Pin|LED_GREENA9_Pin
                       |LED_REDA10_Pin|LED_YELLOWA11_Pin|LED_GREENA12_Pin
                       |LED_REDA13_Pin|LED_YELLOWA14_Pin|LED_GREENA15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure 7SEG (PB0–PB6)
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
