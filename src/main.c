/* Standard libraries */
#include <stdint.h>
#include <assert.h>

/* AVR related libraries */
#include <avr/eeprom.h>
#include <avr/io.h>
#include <util/delay.h>

/* FreeRTOS libraries */
#include <FreeRTOS.h>
#include <task.h>

/* Local driver */
#include <ADC.h>
#include <Serial.h>
#include <SPI.h>

#define STACK_SIZE_FOR_TASK (configMINIMAL_STACK_SIZE)

#define tskPRIORITY_LOW  (tskIDLE_PRIORITY + 1)
#define tskPRIORITY_MID  (tskIDLE_PRIORITY + 2)
#define tskPRIORITY_HIGH (tskIDLE_PRIORITY + 3)

/* Arduino fuse settings */
FUSES = { .low = 0xFF, .high = 0xDE, .extended = 0x05, };

/* Default charger settings for eeprom */
uint8_t foo EEMEM = 0;

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno,
		const char *__sexp) {
	// transmit diagnostic informations through serial link.
	Serial_printAndReturn(__func);
	Serial_printAndReturn(__file);
	Serial_printIntegerAndReturn(__lineno, DEC);
	Serial_printAndReturn(__sexp);
	//Serial.flush();
	// abort program execution.
	abort();
}

int VREF = 5;
int BITS = 10;

/* TODO: Calculation incorrect! */
float getVoltage(uint16_t adcValue) {
	return VREF * ((float) adcValue) / ((2 ^ BITS) - 1);
}

void testTask(void *pvParameters) {
	for (;;) {
		/*Serial_print("Voltage: ");
		Serial_printInteger(getVoltage(ADC_readValue(0)), 10);
		Serial_print("V\n");*/

		assert(false);

		vTaskDelay(1000);
	}

	vTaskDelete(NULL);
}

int main(void) {
	/* TODO: write boardInit somewhere */

	ADC_initializeHardware();
	Serial_initializeHardware();
	SPI_initializeHardware();

	xTaskCreate(testTask, "test", STACK_SIZE_FOR_TASK, NULL, tskPRIORITY_LOW,
			NULL);

	vTaskStartScheduler();

	return 1;
}
