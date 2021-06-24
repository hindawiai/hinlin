<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AD7266/65 SPI ADC driver
 *
 * Copyright 2012 Analog Devices Inc.
 */

#अगर_अघोषित __IIO_ADC_AD7266_H__
#घोषणा __IIO_ADC_AD7266_H__

/**
 * क्रमागत ad7266_range - AD7266 reference voltage range
 * @AD7266_RANGE_VREF: Device is configured क्रम input range 0V - VREF
 *			(RANGE pin set to low)
 * @AD7266_RANGE_2VREF: Device is configured क्रम input range 0V - 2VREF
 *			(RANGE pin set to high)
 */
क्रमागत ad7266_range अणु
	AD7266_RANGE_VREF,
	AD7266_RANGE_2VREF,
पूर्ण;

/**
 * क्रमागत ad7266_mode - AD7266 sample mode
 * @AD7266_MODE_DIFF: Device is configured क्रम full dअगरferential mode
 *				(SGL/DIFF pin set to low, AD0 pin set to low)
 * @AD7266_MODE_PSEUDO_DIFF: Device is configured क्रम pseuकरो dअगरferential mode
 *				(SGL/DIFF pin set to low, AD0 pin set to high)
 * @AD7266_MODE_SINGLE_ENDED: Device is configured क्रम single-ended mode
 *				(SGL/DIFF pin set to high)
 */
क्रमागत ad7266_mode अणु
	AD7266_MODE_DIFF,
	AD7266_MODE_PSEUDO_DIFF,
	AD7266_MODE_SINGLE_ENDED,
पूर्ण;

/**
 * काष्ठा ad7266_platक्रमm_data - Platक्रमm data क्रम the AD7266 driver
 * @range: Reference voltage range the device is configured क्रम
 * @mode: Sample mode the device is configured क्रम
 * @fixed_addr: Whether the address pins are hard-wired
 */
काष्ठा ad7266_platक्रमm_data अणु
	क्रमागत ad7266_range range;
	क्रमागत ad7266_mode mode;
	bool fixed_addr;
पूर्ण;

#पूर्ण_अगर
