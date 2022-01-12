#define RCC_AHB1ENR *((int *)0X40023830)
#define GPIOC_MODER *((int *)0X40020800)
#define GPIOC_ODR *((int *)0X40020814)
#define STK_LOAD *((int *)0XE000E014)
#define STK_VAL *((int *)0XE000E018)
#define STK_CTRL *((int *)0XE000E010)

void RED_LED_Init()
{
	RCC_AHB1ENR |= 0X4;	//Enable Port C clock, set 2nd bit in RCC_AHB1ENR Reg.
	while(!(RCC_AHB1ENR & 0X4));	//wait until 2nd bit of RCC_AHB1ENR is set
	
	GPIOC_MODER |= (0X1<<10);	//put "01" in 11-10 pos. in GPIOC_MODER Reg. to configure PC5 as output
}
void SysTick_Timer_Init()
{
	STK_LOAD = 1600000;	//Put 1600000 (100msec) in STK_LOAD Reg.
	STK_VAL = 10;	//clear STK_VAL Reg., Put garbage value
	STK_CTRL |= 0X7;	//set 2nd(AHB clock source), 1st (Interrupt handler enable) and 0th(Enable timer) bit of STK_CTRL Reg.
}
int main()
{
	//RED LED PC5 Initialization
	RED_LED_Init();
	//Sytem Tick Timer Initialization
	SysTick_Timer_Init();
	
	while(1)
	{
		;
	}
	
	return 0;
}
void SysTick_Handler()
{
	if(GPIOC_ODR & (0X1<<5))
		GPIOC_ODR &= ~(0X1<<5);
	else
		GPIOC_ODR |= (0X1<<5);
	while(!(STK_CTRL & (0X1<<16)))
	{
		;
	}
}