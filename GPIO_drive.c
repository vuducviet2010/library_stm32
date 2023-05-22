
#include "stm32f10x.h"     // Device header
#include "GPIO_drive.h"


void init_GP(unsigned short PORT,unsigned short PIN,unsigned short DIR,unsigned short OPT)
{
	volatile unsigned long * CR;
	unsigned short tPin = PIN;
	unsigned short offset = 0x00;			//GPIOx_CRL
	
		if(PIN > 7)
		{
			tPin -=8;
			offset = 0x01;								// GPIOx_CRH
		}
		

	if(PORT == 1)											// #define PORT_A 1
		{
			RCC_APB2ENR |= 0x4;						// ENABLING PORT A

			CR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)								// #define PORT_B 2
		{
		RCC_APB2ENR |= 0x8;							// ENABLING PORT B
		CR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)								// #define PORT_C 3
		{
		RCC_APB2ENR |= 0x10;						// ENABLING PORT C
		CR = (volatile unsigned long *)(&GPIO_C + offset);
		}
/*
1.Generates a 4-bit mask with all bits equal to 1 using the hexadecimal value 0xf.
2.Shift this mask to the left a number of bits equal to 4*(tPIN), corresponding to the position of the GPIO pin to be cleared in the register.
3.Invert the mask
*/
	// RESET THE PORT
	*CR &= ~(0xf<<(tPin)*4);// Reset the taget pin
		//bit 1111
	*CR |= ((DIR<<(tPin*4)) | (OPT<<(tPin*4+2)));//// Set up the direction and the option of the PIN
}

int Read_GP(unsigned short PORT,unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(PORT == 1)
		{
			IDR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		IDR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		IDR = (volatile unsigned long *)(&GPIO_C+ offset);
		}
		/*
		For example, if pin has a value of 5, then (1<<pin) will produce the value 0b100000, 
		i.e. only the 6th bit (counting from 0) is set to 1, and all other bits are 0
		After performing the right shift >>pin, this value will become 0b000001 only the 0th bit is set to 1, and all other bits are zero. 
		This value is the bit value of the pin. 
		GPIO in the start into, and will be used to read the status of the foot GPIO that.
		*/
		state =  ((*IDR & (1<<pin))>>pin)  ;
		
		return state;
}

void Write_GP(unsigned short PORT,unsigned short pin, unsigned short STATUS)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;
	if(PORT == 1)
		{
			ODR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		ODR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		ODR = (volatile unsigned long *)(&GPIO_C+ offset);
		}
	STATUS ? (*ODR |= (STATUS<<pin)) : (*ODR &= ~(1<<pin));
					// different 0 => true       equal 0 =>false
}

void toggle_GP(unsigned short Port,unsigned short pin)
{
	if(Read_GP(Port,pin))
		{
			Write_GP(Port,pin,0);
		}
	else
		{
			Write_GP(Port,pin,1);
		}
}





void PINc(unsigned short pin, unsigned short STATUS)
{
	STATUS ? (GPIOC->ODR |= (STATUS<<pin)) : (GPIOC->ODR &= ~(1<<pin));
}

void B_init(void)
{
	init_GP(PortC,13,OUT50,OUT_GP_PP);
}

void BLED(unsigned short state)
{
	Write_GP(PortC,13,state);
}
