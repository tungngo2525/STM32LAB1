/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void display7SEG(int num);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  void display7SEG(int num);
  // Function to control the 4-way traffic light with countdown display
      // Countdown time in seconds
  int countdown;
  while (1)
  {
    /* USER CODE END WHILE */
      /* USER CODE END WHILE */
      // Step 1: East-West Red, North-South Green
      // North-South Traffic Lights
      HAL_GPIO_WritePin(GPIO_PIN_12_GPIO_Port, GPIO_PIN_12_Pin, GPIO_PIN_RESET);  // NS Green ON
      HAL_GPIO_WritePin(GPIO_PIN_11_GPIO_Port, GPIO_PIN_11_Pin, GPIO_PIN_SET);  // NS Yellow OFF
      HAL_GPIO_WritePin(GPIO_PIN_10_GPIO_Port, GPIO_PIN_10_Pin, GPIO_PIN_SET);        // NS Red OFF

      // East-West Traffic Lights
      HAL_GPIO_WritePin(GPIO_PIN_7_GPIO_Port, GPIO_PIN_7_Pin, GPIO_PIN_RESET);  // EW Red ON
      HAL_GPIO_WritePin(GPIO_PIN_8_GPIO_Port, GPIO_PIN_8_Pin, GPIO_PIN_SET);  // EW Yellow OFF
      HAL_GPIO_WritePin(GPIO_PIN_9_GPIO_Port, GPIO_PIN_9_Pin, GPIO_PIN_SET);  // EW Green OFF

      // Countdown for East-West Red Light (5 seconds)
      for (countdown = 5; countdown > 0; countdown--)
      {
          display7SEG(countdown);  // Display countdown on 7-segment
          // When the countdown reaches 3, switch North-South to Yellow
          if (countdown == 3)
          {
              HAL_GPIO_WritePin(GPIO_PIN_12_GPIO_Port, GPIO_PIN_12_Pin, GPIO_PIN_SET);    // NS Green OFF
              HAL_GPIO_WritePin(GPIO_PIN_11_GPIO_Port, GPIO_PIN_11_Pin, GPIO_PIN_RESET); // NS Yellow ON
          }
          HAL_Delay(1000);  // Delay 1 second
      }
      // North-South Traffic Lights turn Red after 2 seconds of Yellow
      HAL_GPIO_WritePin(GPIO_PIN_11_GPIO_Port, GPIO_PIN_11_Pin, GPIO_PIN_SET);   // NS Yellow OFF
      HAL_GPIO_WritePin(GPIO_PIN_10_GPIO_Port, GPIO_PIN_10_Pin, GPIO_PIN_RESET);       // NS Red ON
      // Step 2: East-West Green, North-South Red
      HAL_GPIO_WritePin(GPIO_PIN_7_GPIO_Port, GPIO_PIN_7_Pin, GPIO_PIN_SET);     // EW Red OFF
      HAL_GPIO_WritePin(GPIO_PIN_9_GPIO_Port, GPIO_PIN_9_Pin, GPIO_PIN_RESET); // EW Green ON
      // Countdown for East-West Green Light (3 seconds)
      for (countdown = 3; countdown > 0; countdown--)
      {
          display7SEG(countdown);  // Display countdown on 7-segment
          HAL_Delay(1000);         // Delay 1 second
      }
      // Step 3: East-West Yellow, North-South Red
      HAL_GPIO_WritePin(GPIO_PIN_8_GPIO_Port, GPIO_PIN_8_Pin, GPIO_PIN_RESET);   // EW Green OFF
      HAL_GPIO_WritePin(GPIO_PIN_9_GPIO_Port, GPIO_PIN_9_Pin, GPIO_PIN_SET); // EW Yellow ON
      // Countdown for East-West Yellow Light (2 seconds)
      for (countdown = 2; countdown > 0; countdown--)
      {
          display7SEG(countdown);  // Display countdown on 7-segment
          HAL_Delay(1000);         // Delay 1 second
      }
      // Reset the traffic lights for the next cycle
      HAL_GPIO_WritePin(GPIO_PIN_8_GPIO_Port, GPIO_PIN_8_Pin, GPIO_PIN_SET);   // EW Yellow OFF
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin|LED_YELLOW_Pin|GPIO_PIN8_Pin
                          |GPIO_PIN9_Pin|GPIO_PIN10_Pin|GPIO_PIN11_Pin|GPIO_PIN12_Pin
                          |GPIO_PIN13_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0_Pin|GPIO_PIN_1_Pin|GPIO_PIN_2_Pin|GPIO_PIN_10_Pin
                          |GPIO_PIN_11_Pin|GPIO_PIN_12_Pin|GPIO_PIN_3_Pin|GPIO_PIN_4_Pin
                          |GPIO_PIN_5_Pin|GPIO_PIN_6_Pin|GPIO_PIN_7_Pin|GPIO_PIN_8_Pin
                          |GPIO_PIN_9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_Pin LED_GREEN_Pin LED_YELLOW_Pin PAPin
                           PAPin PAPin PAPin PAPin
                           PAPin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_GREEN_Pin|LED_YELLOW_Pin|GPIO_PIN8_Pin
                          |GPIO_PIN9_Pin|GPIO_PIN10_Pin|GPIO_PIN11_Pin|GPIO_PIN12_Pin
                          |GPIO_PIN13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = GPIO_PIN_0_Pin|GPIO_PIN_1_Pin|GPIO_PIN_2_Pin|GPIO_PIN_10_Pin
                          |GPIO_PIN_11_Pin|GPIO_PIN_12_Pin|GPIO_PIN_3_Pin|GPIO_PIN_4_Pin
                          |GPIO_PIN_5_Pin|GPIO_PIN_6_Pin|GPIO_PIN_7_Pin|GPIO_PIN_8_Pin
                          |GPIO_PIN_9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG(int num)
{
    // Segment values for digits 0-9 (active-low: 0 turns ON the segment)
    uint8_t segment_map[10] = {
        0b11000000, // 0: a, b, c, d, e, f
        0b11111001, // 1: b, c
        0b10100100, // 2: a, b, d, e, g
        0b10110000, // 3: a, b, c, d, g
        0b10011001, // 4: b, c, f, g
        0b10010010, // 5: a, c, d, f, g
        0b10000010, // 6: a, c, d, e, f, g
        0b11111000, // 7: a, b, c
        0b10000000, // 8: a, b, c, d, e, f, g
        0b10010000  // 9: a, b, c, d, f, g
    };

    // Clear the current output on PB0-PB6
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);

    // Write the segments to the 7-segment display
    for (int i = 0; i < 7; i++)
    {
        // Check if the segment should be ON or OFF
        GPIO_PinState pin_state = (segment_map[num] & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET;

        // Set the corresponding pin
        HAL_GPIO_WritePin(GPIOB, (1 << i), pin_state);
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
