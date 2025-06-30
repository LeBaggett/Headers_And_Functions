#include "stm32f1xx_hal.h" // modify to your STM family

//-------------------- NRF24l01 registers --------------------------------//

// NRF24l01 comand definitions (according to NRF24l01 datasheet)
#define NRF_WriteReg				0x20  // Write in registers 
#define NRF_ReadReg					0x00  // Read the registers 
#define NRF_FlushTX					0xE1  // Clean the TX send pool
#define NRF_FlushRX					0xE2  // Clean the RX receive pool
#define NRF_Send					0xA0  // Send the payload
#define NRF_Receive					0x61  // Receive the payload

// NRF24l01 register definitions (according to NRF24l01 datasheet)
#define NRF_Config         			0x00  // Power control and mode
#define NRF_EnableAA          		0x01  // Auto Acknowledge
#define NRF_RadioCH           		0x05  // Radio channel
#define NRF_RFSetup           		0x06  // Potency and Baudrate
#define NRF_Status            		0x07  // State Flags
#define NRF_RXAddress_P0      		0x0A  // Pipe 0 address (to listening)
#define NRF_TX_Address        		0x10  // Send address
#define NRF_RX_PayloadSizeof_P0     0x11  // Size of payload what waiting receive

// -------------------- NRF24l01 functions -------------------------------//

// Initialize the NRF24l01, receive 5 parameters: (1)spi handle, Chip Enable (2)port and (3)pin, Chip Select Not (4)port and (5)pin
void NRF_init(SPI_HandleTypeDEF *hspi, GPIO_TypeDef* CE_port, unint16_t CE_pin, GPIO_TypeDef* CSN_port, unint16_t CSN_pin);

// Write in registers function, receive 2 parameters: (1) register , (2) value
unint8_t NRF_Write(unint8_t reg, unint8_t value);

// Read the registers function, receive 1 parameters: (1) register
unint8_t NRF_Read(unint8_t reg);

// Send wireless package message, receive 2 parameters: (1) pointer array - data to send, (2) sizeof the array (max = 32bytes)
void NRF_SendPayload(unint8_t* data, unint8_t size);

// Receive wireless package message, receive 1 parameters: (1) pointer array - local data receive to save. Return the size of package received (bytes)
unint8_t NRF_ReceivePayload(unint8_t* data)

// Set the module in TX Mode, receive 2 parameters: (1) pointer to receptor address, (2) channel (0-125)
void NRF_SetTXMode(unint8_t* addr, unint8_t channel);

// Set the module in RX Mode, receive 2 parameters: (1) pointer to transceptor address, (2) channel (0-125)
void NRF_SetRXMode(unint8_t* addr, unint8_t channel);

// Clean the send pool(TX)/receive pool(RX)
void NRF_FlushTX(void);		// TX
void NRF_FlushrRX(void);	// RX
