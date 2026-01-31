/*
 * rotate.c
 *
 *  Created on: 2026. 1. 28.
 *      Author: junwoo
 */

#include"rotate.h"

volatile uint8_t Flag = 0;
volatile uint8_t curr = 20;
volatile uint8_t direction = 0;
volatile uint32_t last_tick = 0;

//  uint32_t lastDebounceTime = 0;	// 마지막 디바운스 확인 시간
//  GPIO_PinState lastButtonState = GPIO_PIN_SET;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_7)
    {
        uint32_t current_tick = HAL_GetTick();
        if (current_tick - last_tick > 250) // 250ms 이내의 떨림은 무시
        {
            Flag = !Flag; // 1(실행) <-> 0(정지) 토글
        }
        last_tick = current_tick;
    }
}

void rotate()
{
	  if(Flag)
	  {
//		  ledOn(8);

		  if(direction==0)
		  {
			for(uint16_t i=curr;i<130;i++)
			{
				if (!Flag)
				{
//					ledOff(8);// 누르는 순간 탈출!
					break;
				}
				curr=i;
				TIM3->CCR1=i;
				HAL_Delay(50);

				if(i==129) direction=1;
			}
		  }
		  if(direction==1)
		  {
			for(uint16_t i=curr;i>20;i--)
			{
				if (!Flag)
				{
//					ledOff(8);// 누르는 순간 탈출!
					break;
				}
				curr=i;
				TIM3->CCR1=i;
				HAL_Delay(50);

				if (i == 21) direction = 0;
			}
		  }
		}
}

