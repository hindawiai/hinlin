<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम ADAU1361/ADAU1461/ADAU1761/ADAU1961/ADAU1381/ADAU1781 codecs
 *
 * Copyright 2011-2014 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_ADAU17X1_H__
#घोषणा __LINUX_PLATFORM_DATA_ADAU17X1_H__

/**
 * क्रमागत adau17x1_micbias_voltage - Microphone bias voltage
 * @ADAU17X1_MICBIAS_0_90_AVDD: 0.9 * AVDD
 * @ADAU17X1_MICBIAS_0_65_AVDD: 0.65 * AVDD
 */
क्रमागत adau17x1_micbias_voltage अणु
	ADAU17X1_MICBIAS_0_90_AVDD = 0,
	ADAU17X1_MICBIAS_0_65_AVDD = 1,
पूर्ण;

/**
 * क्रमागत adau1761_digmic_jackdet_pin_mode - Configuration of the JACKDET/MICIN pin
 * @ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE: Disable the pin
 * @ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC: Configure the pin क्रम usage as
 *   digital microphone input.
 * @ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT: Configure the pin क्रम jack
 *  insertion detection.
 */
क्रमागत adau1761_digmic_jackdet_pin_mode अणु
	ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE,
	ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC,
	ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT,
पूर्ण;

/**
 * adau1761_jackdetect_debounce_समय - Jack insertion detection debounce समय
 * @ADAU1761_JACKDETECT_DEBOUNCE_5MS: 5 milliseconds
 * @ADAU1761_JACKDETECT_DEBOUNCE_10MS: 10 milliseconds
 * @ADAU1761_JACKDETECT_DEBOUNCE_20MS: 20 milliseconds
 * @ADAU1761_JACKDETECT_DEBOUNCE_40MS: 40 milliseconds
 */
क्रमागत adau1761_jackdetect_debounce_समय अणु
	ADAU1761_JACKDETECT_DEBOUNCE_5MS = 0,
	ADAU1761_JACKDETECT_DEBOUNCE_10MS = 1,
	ADAU1761_JACKDETECT_DEBOUNCE_20MS = 2,
	ADAU1761_JACKDETECT_DEBOUNCE_40MS = 3,
पूर्ण;

/**
 * क्रमागत adau1761_output_mode - Output mode configuration
 * @ADAU1761_OUTPUT_MODE_HEADPHONE: Headphone output
 * @ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS: Capless headphone output
 * @ADAU1761_OUTPUT_MODE_LINE: Line output
 */
क्रमागत adau1761_output_mode अणु
	ADAU1761_OUTPUT_MODE_HEADPHONE,
	ADAU1761_OUTPUT_MODE_HEADPHONE_CAPLESS,
	ADAU1761_OUTPUT_MODE_LINE,
पूर्ण;

/**
 * काष्ठा adau1761_platक्रमm_data - ADAU1761 Codec driver platक्रमm data
 * @input_dअगरferential: If true the input pins will be configured in
 *  dअगरferential mode.
 * @lineout_mode: Output mode क्रम the LOUT/ROUT pins
 * @headphone_mode: Output mode क्रम the LHP/RHP pins
 * @digmic_jackdetect_pin_mode: JACKDET/MICIN pin configuration
 * @jackdetect_debounce_समय: Jack insertion detection debounce समय.
 *  Note: This value will only be used, अगर the JACKDET/MICIN pin is configured
 *  क्रम jack insertion detection.
 * @jackdetect_active_low: If true the jack insertion detection is active low.
 *  Othwise it will be active high.
 * @micbias_voltage: Microphone voltage bias
 */
काष्ठा adau1761_platक्रमm_data अणु
	bool input_dअगरferential;
	क्रमागत adau1761_output_mode lineout_mode;
	क्रमागत adau1761_output_mode headphone_mode;

	क्रमागत adau1761_digmic_jackdet_pin_mode digmic_jackdetect_pin_mode;

	क्रमागत adau1761_jackdetect_debounce_समय jackdetect_debounce_समय;
	bool jackdetect_active_low;

	क्रमागत adau17x1_micbias_voltage micbias_voltage;
पूर्ण;

/**
 * काष्ठा adau1781_platक्रमm_data - ADAU1781 Codec driver platक्रमm data
 * @left_input_dअगरferential: If true configure the left input as
 * dअगरferential input.
 * @right_input_dअगरferential: If true configure the right input as dअगरferntial
 *  input.
 * @use_dmic: If true configure the MIC pins as digital microphone pins instead
 *  of analog microphone pins.
 * @micbias_voltage: Microphone voltage bias
 */
काष्ठा adau1781_platक्रमm_data अणु
	bool left_input_dअगरferential;
	bool right_input_dअगरferential;

	bool use_dmic;

	क्रमागत adau17x1_micbias_voltage micbias_voltage;
पूर्ण;

#पूर्ण_अगर
