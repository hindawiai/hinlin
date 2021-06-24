<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Afatech AF9013 demodulator driver
 *
 * Copyright (C) 2007 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 */

#अगर_अघोषित AF9013_H
#घोषणा AF9013_H

#समावेश <linux/dvb/frontend.h>

/*
 * I2C address: 0x1c, 0x1d
 */

/**
 * काष्ठा af9013_platक्रमm_data - Platक्रमm data क्रम the af9013 driver
 * @clk: Clock frequency.
 * @tuner: Used tuner model.
 * @अगर_frequency: IF frequency.
 * @ts_mode: TS mode.
 * @ts_output_pin: TS output pin.
 * @spec_inv: Input spectrum inverted.
 * @api_version: Firmware API version.
 * @gpio: GPIOs.
 * @get_dvb_frontend: Get DVB frontend callback.
 * @get_i2c_adapter: Get I2C adapter.
 * @pid_filter_ctrl: Control PID filter.
 * @pid_filter: Set PID to PID filter.
 */
काष्ठा af9013_platक्रमm_data अणु
	/*
	 * 20480000, 25000000, 28000000, 28800000
	 */
	u32 clk;
#घोषणा AF9013_TUNER_MXL5003D      3 /* MaxLinear */
#घोषणा AF9013_TUNER_MXL5005D     13 /* MaxLinear */
#घोषणा AF9013_TUNER_MXL5005R     30 /* MaxLinear */
#घोषणा AF9013_TUNER_ENV77H11D5  129 /* Panasonic */
#घोषणा AF9013_TUNER_MT2060      130 /* Microtune */
#घोषणा AF9013_TUNER_MC44S803    133 /* Freescale */
#घोषणा AF9013_TUNER_QT1010      134 /* Quantek */
#घोषणा AF9013_TUNER_UNKNOWN     140 /* क्रम can tuners ? */
#घोषणा AF9013_TUNER_MT2060_2    147 /* Microtune */
#घोषणा AF9013_TUNER_TDA18271    156 /* NXP */
#घोषणा AF9013_TUNER_QT1010A     162 /* Quantek */
#घोषणा AF9013_TUNER_MXL5007T    177 /* MaxLinear */
#घोषणा AF9013_TUNER_TDA18218    179 /* NXP */
	u8 tuner;
	u32 अगर_frequency;
#घोषणा AF9013_TS_MODE_USB       0
#घोषणा AF9013_TS_MODE_PARALLEL  1
#घोषणा AF9013_TS_MODE_SERIAL    2
	u8 ts_mode;
	u8 ts_output_pin;
	bool spec_inv;
	u8 api_version[4];
#घोषणा AF9013_GPIO_ON (1 << 0)
#घोषणा AF9013_GPIO_EN (1 << 1)
#घोषणा AF9013_GPIO_O  (1 << 2)
#घोषणा AF9013_GPIO_I  (1 << 3)
#घोषणा AF9013_GPIO_LO (AF9013_GPIO_ON|AF9013_GPIO_EN)
#घोषणा AF9013_GPIO_HI (AF9013_GPIO_ON|AF9013_GPIO_EN|AF9013_GPIO_O)
#घोषणा AF9013_GPIO_TUNER_ON  (AF9013_GPIO_ON|AF9013_GPIO_EN)
#घोषणा AF9013_GPIO_TUNER_OFF (AF9013_GPIO_ON|AF9013_GPIO_EN|AF9013_GPIO_O)
	u8 gpio[4];

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
	काष्ठा i2c_adapter* (*get_i2c_adapter)(काष्ठा i2c_client *);
	पूर्णांक (*pid_filter_ctrl)(काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*pid_filter)(काष्ठा dvb_frontend *, u8, u16, पूर्णांक);
पूर्ण;

/*
 * AF9013/5 GPIOs (mostly guessed)
 * demod#1-gpio#0 - set demod#2 i2c-addr क्रम dual devices
 * demod#1-gpio#1 - xtal setting (?)
 * demod#1-gpio#3 - tuner#1
 * demod#2-gpio#0 - tuner#2
 * demod#2-gpio#1 - xtal setting (?)
 */

#पूर्ण_अगर /* AF9013_H */
