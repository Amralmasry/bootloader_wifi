#include "gpio.h"
#include "stm32f4xx.h"

void gpio_init(GPIO_TypeDef *GPIOx)
{
	RCC->AHB1ENR|=(1<<0);
	RCC->AHB1ENR|=(1<<1);
	RCC->AHB1ENR|=(1<<2);
	RCC->AHB1ENR|=(1<<3);
	RCC->AHB1ENR|=(1<<4);




}

void gpio_pin_conf_mode(GPIO_TypeDef *GPIOx , uint8_t pin_no,gpio_mode_t mode)
{
	GPIOx ->MODER |= (mode << (2*pin_no));

}


void gpio_pin_output_conf (GPIO_TypeDef *GPIOx , uint8_t pin_no)
{

	GPIOx ->OTYPER |= (1<<pin_no);

}


void gpio_output_speed (GPIO_TypeDef *GPIOx , uint8_t pin_no,gpio_speed_t SPEED)
{

GPIOx -> OSPEEDR |= (SPEED<<(2*pin_no));
}

void gpio_pull_up_down  (GPIO_TypeDef *GPIOx , uint8_t pin_no,gpio_pullup_t conf)
{
	GPIOx -> PUPDR |= (conf<<(2*pin_no));
}


uint8_t gpio_read_pin (GPIO_TypeDef *GPIOx , uint8_t pin_no)
{
	return (GPIOx -> IDR & (1<<pin_no));
}

void gpio_output_data_high (GPIO_TypeDef *GPIOx , uint8_t pin_no)
{
	GPIOx -> ODR |=(1<<pin_no);
}

void gpio_output_data_low (GPIO_TypeDef *GPIOx , uint8_t pin_no)
{
	GPIOx -> ODR &=~(1<<pin_no);
}


void gpio_altrenate_func (GPIO_TypeDef *GPIOx,uint8_t pin_no,uint8_t alt_num)
{
	if ((pin_no <=  7 ))
	{
		GPIOx ->AFR[0] |= (alt_num << (pin_no*4));
	}
	else if ((pin_no > 7))
	{
		pin_no = pin_no-8;
		GPIOx ->AFR[1] |= (alt_num << (pin_no*4));

	}
}
