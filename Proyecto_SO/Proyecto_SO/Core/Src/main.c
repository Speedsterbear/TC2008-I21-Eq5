/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

osThreadId produceTaskHandle;
osThreadId consumeTaskHandle;
osSemaphoreId myBinarySem01Handle;
osSemaphoreId Sem_disponiblesHandle;
osSemaphoreId Sem_ocupadosHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
void produce(void const * argument);
void consume(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch){
	HAL_UART_Transmit(&huart1, &ch, 1, 10);
	return 1;
}
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* definition and creation of Sem_disponibles */
  osSemaphoreDef(Sem_disponibles);
  Sem_disponiblesHandle = osSemaphoreCreate(osSemaphore(Sem_disponibles), 2);

  /* definition and creation of Sem_ocupados */
  osSemaphoreDef(Sem_ocupados);
  Sem_ocupadosHandle = osSemaphoreCreate(osSemaphore(Sem_ocupados), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of produceTask */
  osThreadDef(produceTask, produce, osPriorityNormal, 0, 128);
  produceTaskHandle = osThreadCreate(osThread(produceTask), NULL);

  /* definition and creation of consumeTask */
  osThreadDef(consumeTask, consume, osPriorityNormal, 0, 128);
  consumeTaskHandle = osThreadCreate(osThread(consumeTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_EXT6_Pin|LED_EXT5_Pin|LED_EXT4_Pin|LED_EXT3_Pin
                          |LED_EXT1_Pin|LED_EXT0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_EXT2_GPIO_Port, LED_EXT2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_BUILTIN_Pin */
  GPIO_InitStruct.Pin = LED_BUILTIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_BUILTIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_EXT0_Pin BTN_EXT1_Pin BTN_EXT2_Pin BTN_EXT3_Pin
                           BTN_EXT4_Pin */
  GPIO_InitStruct.Pin = BTN_EXT0_Pin|BTN_EXT1_Pin|BTN_EXT2_Pin|BTN_EXT3_Pin
                          |BTN_EXT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_EXT6_Pin LED_EXT5_Pin LED_EXT4_Pin LED_EXT3_Pin
                           LED_EXT1_Pin LED_EXT0_Pin */
  GPIO_InitStruct.Pin = LED_EXT6_Pin|LED_EXT5_Pin|LED_EXT4_Pin|LED_EXT3_Pin
                          |LED_EXT1_Pin|LED_EXT0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_EXT2_Pin */
  GPIO_InitStruct.Pin = LED_EXT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_EXT2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_produce */
/**
  * @brief  Function implementing the produceTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_produce */
void produce(void const * argument)
{
  /* USER CODE BEGIN 5 */
	char msg[32];
	uint8_t msg_size, cnt=0;
  /* Infinite loop */
  for(;;)
  {
	  msg_size = sprintf(msg, "Hello from produce, Count: %d\r\n", cnt);
	  HAL_GPIO_TogglePin(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin);
	  osSemaphoreWait(myBinarySem01Handle, osWaitForever);
	  HAL_UART_Transmit(&huart1, &msg, msg_size, 1000);
	  osSemaphoreRelease(myBinarySem01Handle);
	  cnt++;
	  osDelay(500);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_consume */
/**
* @brief Function implementing the consumeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_consume */
void consume(void const * argument)
{
  /* USER CODE BEGIN consume */
	char msg[32];
	uint8_t msg_size, cnt=0;
  /* Infinite loop */
	  for(;;)
	  {
		  msg_size = sprintf(msg, "Hello from consume, Count: %d\r\n", cnt);
		  osSemaphoreWait(myBinarySem01Handle, osWaitForever);
		  HAL_UART_Transmit(&huart1, &msg, msg_size, 1000);
		  osSemaphoreRelease(myBinarySem01Handle);
		  cnt++;
		  if(!HAL_GPIO_ReadPin(BTN_EXT0_GPIO_Port, BTN_EXT0_Pin)){
			  HAL_GPIO_TogglePin(LED_EXT0_GPIO_Port, LED_EXT0_Pin);
		  }
		  if(!HAL_GPIO_ReadPin(BTN_EXT1_GPIO_Port, BTN_EXT1_Pin)){
			  HAL_GPIO_TogglePin(LED_EXT1_GPIO_Port, LED_EXT1_Pin);
		  }
		  if(!HAL_GPIO_ReadPin(BTN_EXT2_GPIO_Port, BTN_EXT2_Pin)){
			  HAL_GPIO_TogglePin(LED_EXT2_GPIO_Port, LED_EXT2_Pin);
		  }
		  if(!HAL_GPIO_ReadPin(BTN_EXT3_GPIO_Port, BTN_EXT3_Pin)){
			  HAL_GPIO_TogglePin(LED_EXT3_GPIO_Port, LED_EXT3_Pin);
			  HAL_GPIO_TogglePin(LED_EXT5_GPIO_Port, LED_EXT5_Pin);
		  }
		  if(!HAL_GPIO_ReadPin(BTN_EXT4_GPIO_Port, BTN_EXT4_Pin)){
			  HAL_GPIO_TogglePin(LED_EXT4_GPIO_Port, LED_EXT4_Pin);
			  HAL_GPIO_TogglePin(LED_EXT6_GPIO_Port, LED_EXT6_Pin);
		  }
		  osDelay(250);
	  }
  /* USER CODE END consume */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
