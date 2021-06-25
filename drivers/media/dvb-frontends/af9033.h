<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Afatech AF9033 demodulator driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित AF9033_H
#घोषणा AF9033_H

/*
 * I2C address: 0x1c, 0x1d, 0x1e, 0x1f
 */
काष्ठा af9033_config अणु
	/*
	 * घड़ी Hz
	 * 12000000, 22000000, 24000000, 34000000, 32000000, 28000000, 26000000,
	 * 30000000, 36000000, 20480000, 16384000
	 */
	u32 घड़ी;

	/*
	 * ADC multiplier
	 */
#घोषणा AF9033_ADC_MULTIPLIER_1X   0
#घोषणा AF9033_ADC_MULTIPLIER_2X   1
	u8 adc_multiplier;

	/*
	 * tuner
	 */
#घोषणा AF9033_TUNER_TUA9001     0x27 /* Infineon TUA 9001 */
#घोषणा AF9033_TUNER_FC0011      0x28 /* Fitiघातer FC0011 */
#घोषणा AF9033_TUNER_FC0012      0x2e /* Fitiघातer FC0012 */
#घोषणा AF9033_TUNER_MXL5007T    0xa0 /* MaxLinear MxL5007T */
#घोषणा AF9033_TUNER_TDA18218    0xa1 /* NXP TDA 18218HN */
#घोषणा AF9033_TUNER_FC2580      0x32 /* FCI FC2580 */
/* 50-5f Omega */
#घोषणा AF9033_TUNER_IT9135_38   0x38 /* Omega */
#घोषणा AF9033_TUNER_IT9135_51   0x51 /* Omega LNA config 1 */
#घोषणा AF9033_TUNER_IT9135_52   0x52 /* Omega LNA config 2 */
/* 60-6f Omega v2 */
#घोषणा AF9033_TUNER_IT9135_60   0x60 /* Omega v2 */
#घोषणा AF9033_TUNER_IT9135_61   0x61 /* Omega v2 LNA config 1 */
#घोषणा AF9033_TUNER_IT9135_62   0x62 /* Omega v2 LNA config 2 */
	u8 tuner;

	/*
	 * TS settings
	 */
#घोषणा AF9033_TS_MODE_USB       0
#घोषणा AF9033_TS_MODE_PARALLEL  1
#घोषणा AF9033_TS_MODE_SERIAL    2
	u8 ts_mode:2;

	/*
	 * input spectrum inversion
	 */
	bool spec_inv;

	/*
	 *
	 */
	bool dyn0_clk;

	/*
	 * PID filter ops
	 */
	काष्ठा af9033_ops *ops;

	/*
	 * frontend
	 * वापसed by that driver
	 */
	काष्ठा dvb_frontend **fe;

	/*
	 * regmap क्रम IT913x पूर्णांकegrated tuner driver
	 * वापसed by that driver
	 */
	काष्ठा regmap *regmap;
पूर्ण;

काष्ठा af9033_ops अणु
	पूर्णांक (*pid_filter_ctrl)(काष्ठा dvb_frontend *fe, पूर्णांक onoff);
	पूर्णांक (*pid_filter)(काष्ठा dvb_frontend *fe, पूर्णांक index, u16 pid,
			  पूर्णांक onoff);
पूर्ण;

#पूर्ण_अगर /* AF9033_H */
