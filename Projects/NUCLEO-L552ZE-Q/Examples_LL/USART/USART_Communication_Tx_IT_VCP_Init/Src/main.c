/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Examples_LL/USART/USART_Communication_Tx_IT_VCP_Init/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to send bytes over LPUART IP using
  *          the STM32L5xx USART LL API.
  *          Peripheral initialization done using LL unitary services functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

__IO uint8_t ubButtonPress = 0;
__IO uint8_t ubSend = 0;
const uint8_t aStringToSend[] = "STM32L5xx USART LL API Example : TX in IT mode\r\nConfiguration UART 115200 bps, 8 data bit/1 stop bit/No parity/No HW flow control\r\n";
uint8_t ubSizeToSend = sizeof(aStringToSend);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ICACHE_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void     LED_On(void);
void     LED_Off(void);
void     LED_Blinking(uint32_t Period);

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
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  */
  LL_PWR_DisableUCPDDeadBattery();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ICACHE_Init();
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* Polling LPUART initialisation */
  while ((!(LL_LPUART_IsActiveFlag_TEACK(LPUART1))) || (!(LL_LPUART_IsActiveFlag_REACK(LPUART1))))
  {
  }

  /* Enable RXNE and Error interrupts */
  LL_LPUART_EnableIT_RXNE(LPUART1);
  LL_LPUART_EnableIT_ERROR(LPUART1);

  /* Set LED1 Off */
  LED_Off();

  /* USER CODE END 2 */

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
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_5)
  {
  }

  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE0);
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {
  }

  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
  LL_RCC_MSI_SetCalibTrimming(0);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 55, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

   /* Intermediate AHB prescaler 2 when target frequency clock is higher than 80 MHz */
   LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Insure 1�s transition state at intermediate medium speed clock*/
  for (__IO uint32_t i = (RCC_MAX_FREQUENCY_MHZ >> 1); i !=0; i--);

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  LL_Init1msTick(110000000);

  LL_SetSystemCoreClock(110000000);
}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  LL_ICACHE_SetMode(LL_ICACHE_1WAY);
  LL_ICACHE_Enable();
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  LL_LPUART_InitTypeDef LPUART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_PCLK1);

  /* Peripheral clock enable */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPUART1);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
  LL_PWR_EnableVddIO2();
  /**LPUART1 GPIO Configuration
  PG7   ------> LPUART1_TX
  PG8   ------> LPUART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7|LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_8;
  LL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* LPUART1 interrupt Init */
  NVIC_SetPriority(LPUART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(LPUART1_IRQn);

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  LPUART_InitStruct.PrescalerValue = LL_LPUART_PRESCALER_DIV1;
  LPUART_InitStruct.BaudRate = 115200;
  LPUART_InitStruct.DataWidth = LL_LPUART_DATAWIDTH_8B;
  LPUART_InitStruct.StopBits = LL_LPUART_STOPBITS_1;
  LPUART_InitStruct.Parity = LL_LPUART_PARITY_NONE;
  LPUART_InitStruct.TransferDirection = LL_LPUART_DIRECTION_TX_RX;
  LPUART_InitStruct.HardwareFlowControl = LL_LPUART_HWCONTROL_NONE;
  LL_LPUART_Init(LPUART1, &LPUART_InitStruct);
  LL_LPUART_SetTXFIFOThreshold(LPUART1, LL_LPUART_FIFOTHRESHOLD_1_8);
  LL_LPUART_SetRXFIFOThreshold(LPUART1, LL_LPUART_FIFOTHRESHOLD_1_8);
  LL_LPUART_DisableFIFO(LPUART1);
  LL_LPUART_Enable(LPUART1);
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
  LL_PWR_EnableVddIO2();

  /**/
  LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);

  /**/
  LL_EXTI_SetEXTISource(LL_EXTI_EXTI_PORTC, LL_EXTI_EXTI_LINE13);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_13, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_INPUT);

  /**/
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI13_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3, 0));
  NVIC_EnableIRQ(EXTI13_IRQn);

}

/* USER CODE BEGIN 4 */

/**
  * @brief  Turn-on LED1.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
  /* Turn LED1 on */
  LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
}

/**
  * @brief  Turn-off LED1.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
  /* Turn LED1 off */
  LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin);
}

/**
  * @brief  Set LED1 to Blinking mode for an infinite loop (toggle period based on value provided as input parameter).
  * @param  Period : Period of time (in ms) between each toggling of LED
  *   This parameter can be user defined values. Pre-defined values used in that example are :
  *     @arg LED_BLINK_FAST : Fast Blinking
  *     @arg LED_BLINK_SLOW : Slow Blinking
  *     @arg LED_BLINK_ERROR : Error specific Blinking
  * @retval None
  */
void LED_Blinking(uint32_t Period)
{
  /* Toggle LED1 in an infinite loop */
  while (1)
  {
    LL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    LL_mDelay(Period);
  }
}

/******************************************************************************/
/*   USER IRQ HANDLER TREATMENT Functions                                     */
/******************************************************************************/
/**
  * @brief  Function to manage User push-button
  * @param  None
  * @retval None
  */
void UserButton_Callback(void)
{
  /* Start transfer only if not already ongoing */
  if (ubSend == 0)
  {
    /* Start LPUART transmission : Will initiate TXE interrupt after TDR register is empty */
    LL_LPUART_TransmitData8(LPUART1, aStringToSend[ubSend++]);

    /* Enable TXE interrupt */
    LL_LPUART_EnableIT_TXE(LPUART1);
  }
}

/**
  * @brief  Function called for achieving next TX Byte sending
  * @param  None
  * @retval None
  */
void LPUART_TXEmpty_Callback(void)
{
  if (ubSend == (ubSizeToSend - 1))
  {
    /* Disable TXE interrupt */
    LL_LPUART_DisableIT_TXE(LPUART1);

    /* Enable TC interrupt */
    LL_LPUART_EnableIT_TC(LPUART1);
  }

  /* Fill TDR with a new char */
  LL_LPUART_TransmitData8(LPUART1, aStringToSend[ubSend++]);
}

/**
  * @brief  Function called at completion of last byte transmission
  * @param  None
  * @retval None
  */
void LPUART_CharTransmitComplete_Callback(void)
{
  if (ubSend == sizeof(aStringToSend))
  {
    ubSend = 0;

    /* Disable TC interrupt */
    LL_LPUART_DisableIT_TC(LPUART1);

    /* Turn LED1 On at end of transfer : Tx sequence completed successfully */
    LED_On();
  }
}

/**
  * @brief  Function called in case of error detected in LPUART IT Handler
  * @param  None
  * @retval None
  */
void Error_Callback(void)
{
  __IO uint32_t isr_reg;

  /* Disable LPUARTx_IRQn */
  NVIC_DisableIRQ(LPUART1_IRQn);

  /* Error handling example :
    - Read LPUART ISR register to identify flag that leads to IT raising
    - Perform corresponding error handling treatment according to flag
  */
  isr_reg = LL_LPUART_ReadReg(LPUART1, ISR);
  if (isr_reg & LL_LPUART_ISR_NE)
  {
    /* case Noise Error flag is raised : ... */
    LED_Blinking(LED_BLINK_FAST);
  }
  else
  {
    /* Unexpected IT source : Set LED to Blinking mode to indicate error occurs */
    LED_Blinking(LED_BLINK_ERROR);
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
  while(1) 
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
  /* Infinite loop */
  while (1)
  {}
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
