<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Realtek RTL2832 DVB-T demodulator driver
 *
 * Copyright (C) 2012 Thomas Mair <thomas.mair86@gmail.com>
 * Copyright (C) 2012-2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित RTL2832_H
#घोषणा RTL2832_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c-mux.h>

/**
 * काष्ठा rtl2832_platक्रमm_data - Platक्रमm data क्रम the rtl2832 driver
 * @clk: Clock frequency (4000000, 16000000, 25000000, 28800000).
 * @tuner: Used tuner model.
 * @get_dvb_frontend: Get DVB frontend.
 * @get_i2c_adapter: Get I2C adapter.
 * @slave_ts_ctrl: Control slave TS पूर्णांकerface.
 * @pid_filter: Set PID to PID filter.
 * @pid_filter_ctrl: Control PID filter.
 */
काष्ठा rtl2832_platक्रमm_data अणु
	u32 clk;
	/*
	 * XXX: This list must be kept sync with dvb_usb_rtl28xxu USB IF driver.
	 */
#घोषणा RTL2832_TUNER_FC2580    0x21
#घोषणा RTL2832_TUNER_TUA9001   0x24
#घोषणा RTL2832_TUNER_FC0012    0x26
#घोषणा RTL2832_TUNER_E4000     0x27
#घोषणा RTL2832_TUNER_FC0013    0x29
#घोषणा RTL2832_TUNER_R820T     0x2a
#घोषणा RTL2832_TUNER_R828D     0x2b
#घोषणा RTL2832_TUNER_SI2157    0x2c
	u8 tuner;

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
	काष्ठा i2c_adapter* (*get_i2c_adapter)(काष्ठा i2c_client *);
	पूर्णांक (*slave_ts_ctrl)(काष्ठा i2c_client *, bool);
	पूर्णांक (*pid_filter)(काष्ठा dvb_frontend *, u8, u16, पूर्णांक);
	पूर्णांक (*pid_filter_ctrl)(काष्ठा dvb_frontend *, पूर्णांक);
/* निजी: Register access क्रम SDR module use only */
	काष्ठा regmap *regmap;
पूर्ण;

#पूर्ण_अगर /* RTL2832_H */
