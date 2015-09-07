#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void ADC_init(void);

/*
 * Convert analog values. 10 bit precision. Results between 0x0000 and 0x03FF. Returns 0xFC00 in case of an error
 */
uint16_t ADC_readValue(uint8_t channel);

#endif
