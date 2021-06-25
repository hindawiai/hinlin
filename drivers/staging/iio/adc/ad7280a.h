<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AD7280A Lithium Ion Battery Monitoring System
 *
 * Copyright 2011 Analog Devices Inc.
 */

#अगर_अघोषित IIO_ADC_AD7280_H_
#घोषणा IIO_ADC_AD7280_H_

/*
 * TODO: काष्ठा ad7280_platक्रमm_data needs to go पूर्णांकo include/linux/iio
 */

#घोषणा AD7280A_ACQ_TIME_400ns			0
#घोषणा AD7280A_ACQ_TIME_800ns			1
#घोषणा AD7280A_ACQ_TIME_1200ns			2
#घोषणा AD7280A_ACQ_TIME_1600ns			3

#घोषणा AD7280A_CONV_AVG_DIS			0
#घोषणा AD7280A_CONV_AVG_2			1
#घोषणा AD7280A_CONV_AVG_4			2
#घोषणा AD7280A_CONV_AVG_8			3

#घोषणा AD7280A_ALERT_REMOVE_VIN5		BIT(2)
#घोषणा AD7280A_ALERT_REMOVE_VIN4_VIN5		BIT(3)
#घोषणा AD7280A_ALERT_REMOVE_AUX5		BIT(0)
#घोषणा AD7280A_ALERT_REMOVE_AUX4_AUX5		BIT(1)

काष्ठा ad7280_platक्रमm_data अणु
	अचिन्हित पूर्णांक		acquisition_समय;
	अचिन्हित पूर्णांक		conversion_averaging;
	अचिन्हित पूर्णांक		chain_last_alert_ignore;
	bool			thermistor_term_en;
पूर्ण;

#पूर्ण_अगर /* IIO_ADC_AD7280_H_ */
