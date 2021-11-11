

/*********************************INCLUDES******************************************/
#include "BSP/BMP280_I2C.h"
#include "i2c.h"
	

/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/
static int t_fine = 0;
static uint16_t dig_T1 = 0, dig_P1 = 0;
static int16_t dig_T2 = 0, dig_T3 = 0;
static int16_t dig_P2 = 0, dig_P3 = 0, dig_P4 = 0, dig_P5 = 0, dig_P6 = 0, dig_P7 = 0, dig_P8 = 0, dig_P9 = 0;

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

int my_16bit_two_complement_to_decimal(uint16_t data_in) 
{
	uint16_t negative_bit = 0;
  int new_value = 0;
	
	negative_bit = (data_in & 0x8000) >> 15;	// Extract valoe of 15th bit
																						// Since we have 16 bit variable, last bit is 15th
	
	// If bit is negative
	if (negative_bit == 1) 										
	{
		// Invert data
		data_in = ~data_in;
		// Add 1
		data_in = data_in + 1;
		
		// Make negative 
		new_value = data_in * (-1);
		return new_value;
	}
	
	// If positive
	else 
	{
		// Return the same value
		return data_in;
	}
}


// Read calibration registers
void bmp280_I2C_read_all_conf_reg(void) 
{
	uint8_t i2c_addr = 0x76;
	uint16_t priv = 0;
	
	uint8_t rx_data[2] = {0};
	uint8_t reg_T1_1 = 0x88;
	uint8_t reg_T1_2 = 0x89;

	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_T1_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_T1_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_T1 = my_16bit_two_complement_to_decimal(priv);
	
		
	uint8_t reg_T2_1 = 0x8A;
	uint8_t reg_T2_2 = 0x8B;

	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_T2_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_T2_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_T2 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
	
	
	uint8_t reg_T3_1 = 0x8C;
	uint8_t reg_T3_2 = 0x8D;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_T3_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_T3_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_T3 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
	
	
	uint8_t reg_P1_1 = 0x8E;
	uint8_t reg_P1_2 = 0x8F;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P1_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P1_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P1 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
	
	
	uint8_t reg_P2_1 = 0x90;
	uint8_t reg_P2_2 = 0x91;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P2_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P2_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P2 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);


	uint8_t reg_P3_1 = 0x92;
	uint8_t reg_P3_2 = 0x93;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P3_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P3_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P3 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
	
		
	uint8_t reg_P4_1 = 0x94;
	uint8_t reg_P4_2 = 0x95;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P4_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P4_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P4 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
		
	
	uint8_t reg_P5_1 = 0x96;
	uint8_t reg_P5_2 = 0x97;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P5_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P5_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P5 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
		
		
	uint8_t reg_P6_1 = 0x98;
	uint8_t reg_P6_2 = 0x99;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P6_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P6_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P6 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
		
		
	uint8_t reg_P7_1 = 0x9A;
	uint8_t reg_P7_2 = 0x9B;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P7_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P7_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P7 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
		
		
	uint8_t reg_P8_1 = 0x9C;
	uint8_t reg_P8_2 = 0x9D;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P8_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P8_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P8 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
	
	
	uint8_t reg_P9_1 = 0x9E;
	uint8_t reg_P9_2 = 0x9F;
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P9_2, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[1], 1, 20);
	
	HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, &reg_P9_1, 1, 20);
	HAL_I2C_Master_Receive(&hi2c1, i2c_addr << 1, &rx_data[0], 1, 20);
	priv = (rx_data[1] << 8) | rx_data[0];
	dig_P9 = my_16bit_two_complement_to_decimal((rx_data[1] << 8) | rx_data[0]);
}


// Temperature compensation
float bmp280_I2C_temp_calculation(int adc_T)
{
	bmp280_I2C_read_all_conf_reg();
	volatile double var1, var2, T;
	var1 = (((double)adc_T)/(double)16384.0 - ((double)dig_T1)/(double)1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T)/(double)131072.0 - ((double)dig_T1)/(double)8192.0) * (((double)adc_T)/(double)131072.0 - ((double) dig_T1)/(double)8192.0)) * ((double)dig_T3);
	t_fine = (int)(var1 + var2);
	T = (var1 + var2);
	T = T / (double)5120.0;
	return T;
}

// Pressure compensation
float bmp280_I2C_pressure_calculation(int adc_P)
{
	bmp280_I2C_read_all_conf_reg();
	volatile double var1, var2, p;
	var1 = ((double)t_fine/(double)2.0) - (double)64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / (double)32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * (double)2.0;
	var2 = (var2/4.0)+(((double)dig_P4) * (double)65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / (double)524288.0 + ((double)dig_P2) * var1) / (double)524288.0;
	var1 = (1.0 + var1 / (double)32768.0)*((double)dig_P1);
	if (var1 == 0.0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 - (double)adc_P;
	p = (p - (var2 / (double)4096.0)) * (double)6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / (double)2147483648.0;
	var2 = p * ((double)dig_P8) / (double)32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / (double)16.0;
	return p;
}

// Function allows setting power modes
void set_power_mode(uint8_t mode)
{
	uint8_t ctrl_meas_addr = 0xF4;
	uint8_t reg_value = 0;
	
	// Read CTRL_MEAS register
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR << 1, &ctrl_meas_addr, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR << 1, &reg_value, 1, 10);
	
	// Reset bits for mode
	reg_value &= POWER_MODE_MASK;
	// Set new register value - new mode bits
	reg_value |= mode;
	
	// Write this value to CTRL_MEAS register
	HAL_I2C_Mem_Write(&hi2c1, BMP280_ADDR << 1, ctrl_meas_addr, 1, &reg_value, 1, 10);	
}

// Function sets time btween measurements
void set_stdby_time(uint8_t time)
{
	uint8_t config = 0xF5;
	uint8_t reg_value = 0;
	
	// Read CONFIG register
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR << 1, &config, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR << 1, &reg_value, 1, 10);
	
	// Reset bits that determine time between measurements 
	reg_value &= STDBY_TIME_MASK;
	// Set new time between measurement
	reg_value |= (time << 5);
	
	// And write it to CONFIG register
	HAL_I2C_Mem_Write(&hi2c1, BMP280_ADDR << 1, config, 1, &reg_value, 1, 10);	
	
}

// Function sets temperature resolution
void set_temp_resolution(uint8_t t_samp)
{
	uint8_t ctrl_meas_addr = 0xF4;
	uint8_t reg_value = 0;
	
	// Read CTRL_MEAS register
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR << 1, &ctrl_meas_addr, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR << 1, &reg_value, 1, 10);
	
	// Reset temperature resolution bits 
	reg_value &= TEMP_MASK;
	// Set new temperature resolution
	reg_value |= (t_samp << 5);
	
	// And write it to CTRL_MEAS register
	HAL_I2C_Mem_Write(&hi2c1, BMP280_ADDR << 1, ctrl_meas_addr, 1, &reg_value, 1, 10);	
}

// Function sets pressure resolution
void set_pressure_resolution(uint8_t p_samp)
{
	uint8_t ctrl_meas_addr = 0xF4;
	uint8_t reg_value = 0;
	
	// Read CONFIG register
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR << 1, &ctrl_meas_addr, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR << 1, &reg_value, 1, 10);
	
	//  Reset pressure resolution bits 
	reg_value &= PRESS_MASK;
	// Set new pressure resolution 
	reg_value |= (p_samp << 2);
	
	// And write it to CTRL_MEAS register
	HAL_I2C_Mem_Write(&hi2c1, BMP280_ADDR << 1, ctrl_meas_addr, 1, &reg_value, 1, 10);	
}

// Function returns raw temperature data
uint32_t get_raw_temp()
{
	uint8_t temp_msb = 0xFA;
	uint8_t reg_value[3] = {0};
	uint32_t temp = 0;
	
	// Read  temp_msb, temp_lsb and temp_xlsb registers
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR << 1, &temp_msb, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR << 1, reg_value, 3, 10);
	
	// Form the data
	temp = (uint32_t)reg_value[0] << 12;    
	temp |= (uint32_t)reg_value[1] << 4;
	temp |= (uint32_t)reg_value[2] >> 4;
	
	return temp;
}

// Function return raw pressure data
uint32_t get_raw_press()
{
	uint8_t press_msb = 0xF7;
	uint8_t reg_value[3] = {0};
	uint32_t press = 0;
	
	// Read press_msb, press_lsb and press_xlsb registers
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR << 1, &press_msb, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR << 1, reg_value, 3, 10);
	
	// Form the data
	press = (uint32_t)reg_value[0] << 12;    
	press |= (uint32_t)reg_value[1] << 4;
	press |= (uint32_t)reg_value[2] >> 4;
	
	return press;
}

