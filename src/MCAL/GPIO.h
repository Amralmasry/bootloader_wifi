#ifndef gpio
#define gpio

#include "stm32f4xx.h"


typedef enum  mode {
	INPUT_,
	GPO,
	ALT_FUNC,
	ANALOG
} gpio_mode_t;

typedef enum pull {
	NO_PULL,
	PULLUP,
	PULLDOWN
} gpio_pullup_t;

typedef enum speed {
	LOW_,
	MED,
	HIGH_gp,
	VERYHIGH
}gpio_speed_t;

void gpio_output_data_low (GPIO_TypeDef *GPIOx , uint8_t pin_no);
void gpio_output_data_high (GPIO_TypeDef *GPIOx , uint8_t pin_no);

void gpio_init(GPIO_TypeDef *GPIOx);
void gpio_altrenate_func (GPIO_TypeDef *GPIOx,uint8_t pin_no,uint8_t alt_num);


void gpio_pin_conf_mode(GPIO_TypeDef *GPIOx , uint8_t pin_no,gpio_mode_t mode);
void gpio_pin_output_conf (GPIO_TypeDef *GPIOx , uint8_t pin_no);
void gpio_output_speed (GPIO_TypeDef *GPIOx , uint8_t pin_no,gpio_speed_t SPEED);
void gpio_pull_up_down  (GPIO_TypeDef *GPIOx , uint8_t pin_no,gpio_pullup_t conf);

void uart1_pin_conf(void);





#endif
