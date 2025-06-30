#include "_NRF24L01_.h"

// Declarate the NRF_Init parameters 
static SPI_HandleTypeDef *nrf_spi;	// pointer to nrf_spi handle
static GPIO_TypeDef* ce_port;		// chip enable port
static unint16_t ce_pin;			// chip enable pin
static GPIO_TypeDef* csn_port;		// chip select not port
static unint16_t csn_pin;			// chip select not pin

// ----------------------- FUNCTIONS --------------------------------//
//Initial Configuration the NRF24L01
void NRF_init(SPI_HandleTypeDEF *hspi, GPIO_TypeDef* CE_port, unint16_t CE_pin, GPIO_TypeDef* CSN_port, unint16_t CSN_pin){
	
	// Atribuite the reference variables
	nrf_spi = hspi;
	ce_port = CE_port;
	ce_pin = CE_pin;
	csn_port = CSN_port;
	csn_pin = CSN_pin;
	
	//ON CSN and OFF CE
	HAL_GPIO_WritePin(csn_port, csn_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(ce_port, ce_pin, GPIO_PIN_RESET);
	
	HAL_Delay(100);

/*	
----------------------------------------------------------
					TABLE TO CONFIG REGISTER
----------------------------------------------------------			
	| Value | Binary	 | description                    |
	|-------|------------|--------------------------------|
=>  | 0x0A	| 00001010	 | Transceptor, CRC ON, Power ON  |
	| 0x0B	| 00001011	 | Receptor, CRC ON, Power ON     |
	| 0x08	| 00001000	 | Transceptor, CRC ON, Power OFF |
	| 0x00	| 00000000	 | Power OFF                      |
	 -----------------------------------------------------
*/
	// Write the config register: CRC ON, Power ON
	NRF_Write(NRF_Config, 0x0A);
	
	// Write the channel register: channel (0-125)
	NRF_Write(NRF_RadioCH, 22); // Bozo 22 xD
/*
	-------------------------------------------------------------------------------------------------------------
										TABLE TO CONFIG POTENCY AND BAUDRATE									 
	-------------------------------------------------------------------------------------------------------------	
	| Hex  | Binário   | Velocidade (Data Rate) | Potência de TX | Descrição                                     |
	| ---- | --------- | ---------------------- | -------------- | --------------------------------------------- |
	| 0x00 | 0000 0000 | 1 Mbps                 | -18 dBm        | Minimun velocity, minimum potency             |
	| 0x02 | 0000 0010 | 1 Mbps                 | -12 dBm        | Potency little bit fast                       |
	| 0x04 | 0000 0100 | 1 Mbps                 | -6 dBm         | Medium potency                                |
=>  | 0x06 | 0000 0110 | 1 Mbps                 | 0 dBm (max)    | Default velocity and Maximum potency (default)|
	| 0x0A | 0000 1010 | 2 Mbps                 | -6 dBm         | biggest velocity, Medium potency              |
	| 0x0E | 0000 1110 | 2 Mbps                 | 0 dBm (max)    | Maximum velocity and Maximum potency          |
	| 0x20 | 0010 0000 | 250 kbps               | -18 dBm        | Low velocity, minimum potency                 |
	| 0x22 | 0010 0010 | 250 kbps               | -12 dBm        | Low velocity, Medium-low potency              |
	| 0x24 | 0010 0100 | 250 kbps               | -6 dBm         | Low velocity, Medium potency                  |
	| 0x26 | 0010 0110 | 250 kbps               | 0 dBm (max)    | Low velocity, Maximum potency                 |
	 ------------------------------------------------------------------------------------------------------------
*/
	// Write the RF Setup register: Default velocity and Maximum potency (default)
	NRF_Write(NRF_RFSetup, 0x06);
	
	// Clean the buffers
	NRF_FlushTX();
	NRF_FlushRX();
	
}