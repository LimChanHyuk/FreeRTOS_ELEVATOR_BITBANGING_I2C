#include "fnd.h"
#include "extern.h"
#include "elevator.h"

extern enum CURRENT_DOOR_STATE current_door_state;

 void fnd_elevator(void);
 void fnd_display(uint8_t fnd, uint8_t location);

 void fnd_elevator(void)
 {
     fnd_display((current_door_state == open) ? 0x3F : 0x39, 1);    // thousands
     fnd_display((current_door_state == open) ? 0x73 : 0x38, 2);    // hundreds
     fnd_display((current_door_state == open) ? 0x79 : 0x3F, 3);    // tens
     fnd_display((current_door_state == open) ? 0x54 : 0x6D, 4);    // ones
 }


 void fnd_display(uint8_t fnd, uint8_t location)
 {
 	uint16_t data = 0;
 	data = fnd << 8;
 	data |= ~(1 << (location - 1)) & 0x0F;

 	for(int i=0 ; i<16; i++){

 		if(data >> (15-i) & 1)
 		{	
 			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 1);	
 		}
 		else
 		{
 			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0);	
 		}

 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 1);	
 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 0);	
 	}
 	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, 0);
 	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, 1);
 }
