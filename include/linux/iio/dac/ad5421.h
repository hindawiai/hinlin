<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IIO_DAC_AD5421_H__
#घोषणा __IIO_DAC_AD5421_H__

/**
 * क्रमागत ad5421_current_range - Current range the AD5421 is configured क्रम.
 * @AD5421_CURRENT_RANGE_4mA_20mA: 4 mA to 20 mA (RANGE1,0 pins = 00)
 * @AD5421_CURRENT_RANGE_3mA8_21mA: 3.8 mA to 21 mA (RANGE1,0 pins = x1)
 * @AD5421_CURRENT_RANGE_3mA2_24mA: 3.2 mA to 24 mA (RANGE1,0 pins = 10)
 */

क्रमागत ad5421_current_range अणु
	AD5421_CURRENT_RANGE_4mA_20mA,
	AD5421_CURRENT_RANGE_3mA8_21mA,
	AD5421_CURRENT_RANGE_3mA2_24mA,
पूर्ण;

/**
 * काष्ठा ad5421_platक्रमm_data - AD5421 DAC driver platक्रमm data
 * @बाह्यal_vref: whether an बाह्यal reference voltage is used or not
 * @current_range: Current range the AD5421 is configured क्रम
 */

काष्ठा ad5421_platक्रमm_data अणु
	bool बाह्यal_vref;
	क्रमागत ad5421_current_range current_range;
पूर्ण;

#पूर्ण_अगर
