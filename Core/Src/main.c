#include "main.h"
#define GPIOD_BASE_ADDR  0x40020C00
#define GPIOA_BASE_ADDR  0x40020000
void LedInit()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0xFF << 24); //clear PD12-PD15 ve 0
	*GPIOD_MODER |= (0x55 << 24); //PD12-PD15 output

}

void ButtonInit()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t* GPIOA_MODER = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*GPIOA_MODER &= ~(0b11 << 0);//thiet lap PA0 input
	uint32_t* GPIOA_PUPDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x0C);
	*GPIOA_PUPDR |= (0b01 << 0);//day len PA0
}

void LedCtrl(int on_off, int led_no)
{

	uint32_t*GPIOD_BSRR = (uint32_t*)(GPIOD_BASE_ADDR + 0x18);
	if(on_off)
		*GPIOD_BSRR |= (1<< (12 + led_no));//bat led
	else
		*GPIOD_BSRR |= (1<<(28 + led_no));//tat led
}
int read_status_button(){
	uint32_t*GPIOA_IDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x10);
	return (*GPIOA_IDR & 0x1);//tra ve trang thai nut nhan

}

int main()
{
	HAL_Init();
	LedInit();
	ButtonInit();
	while (1)
	{
		if (read_status_button())
		{
			for (int i = 0; i < 4; i++)
				LedCtrl( 1, i);  // Bat cac led
		}
		else
		{
			for (int i = 0; i < 4; i++)
				LedCtrl(0, i); //tat cac led
		}
	}
	return 0;
}
