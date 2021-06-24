<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AD7887 SPI ADC driver
 *
 * Copyright 2010 Analog Devices Inc.
 */
#अगर_अघोषित IIO_ADC_AD7887_H_
#घोषणा IIO_ADC_AD7887_H_

/**
 * काष्ठा ad7887_platक्रमm_data - AD7887 ADC driver platक्रमm data
 * @en_dual: Whether to use dual channel mode. If set to true AIN1 becomes the
 *	second input channel, and Vref is पूर्णांकernally connected to Vdd. If set to
 *	false the device is used in single channel mode and AIN1/Vref is used as
 *	VREF input.
 */
काष्ठा ad7887_platक्रमm_data अणु
	bool en_dual;
पूर्ण;

#पूर्ण_अगर /* IIO_ADC_AD7887_H_ */
