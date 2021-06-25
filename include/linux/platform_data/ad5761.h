<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AD5721, AD5721R, AD5761, AD5761R, Voltage Output Digital to Analog Converter
 *
 * Copyright 2016 Qtechnology A/S
 * 2016 Ricarकरो Ribalda <ribalda@kernel.org>
 */
#अगर_अघोषित __LINUX_PLATFORM_DATA_AD5761_H__
#घोषणा __LINUX_PLATFORM_DATA_AD5761_H__

/**
 * क्रमागत ad5761_voltage_range - Voltage range the AD5761 is configured क्रम.
 * @AD5761_VOLTAGE_RANGE_M10V_10V:  -10V to  10V
 * @AD5761_VOLTAGE_RANGE_0V_10V:      0V to  10V
 * @AD5761_VOLTAGE_RANGE_M5V_5V:     -5V to   5V
 * @AD5761_VOLTAGE_RANGE_0V_5V:       0V to   5V
 * @AD5761_VOLTAGE_RANGE_M2V5_7V5: -2.5V to 7.5V
 * @AD5761_VOLTAGE_RANGE_M3V_3V:     -3V to   3V
 * @AD5761_VOLTAGE_RANGE_0V_16V:      0V to  16V
 * @AD5761_VOLTAGE_RANGE_0V_20V:      0V to  20V
 */

क्रमागत ad5761_voltage_range अणु
	AD5761_VOLTAGE_RANGE_M10V_10V,
	AD5761_VOLTAGE_RANGE_0V_10V,
	AD5761_VOLTAGE_RANGE_M5V_5V,
	AD5761_VOLTAGE_RANGE_0V_5V,
	AD5761_VOLTAGE_RANGE_M2V5_7V5,
	AD5761_VOLTAGE_RANGE_M3V_3V,
	AD5761_VOLTAGE_RANGE_0V_16V,
	AD5761_VOLTAGE_RANGE_0V_20V,
पूर्ण;

/**
 * काष्ठा ad5761_platक्रमm_data - AD5761 DAC driver platक्रमm data
 * @voltage_range: Voltage range the AD5761 is configured क्रम
 */

काष्ठा ad5761_platक्रमm_data अणु
	क्रमागत ad5761_voltage_range voltage_range;
पूर्ण;

#पूर्ण_अगर
