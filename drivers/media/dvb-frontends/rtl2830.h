<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Realtek RTL2830 DVB-T demodulator driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित RTL2830_H
#घोषणा RTL2830_H

#समावेश <linux/dvb/frontend.h>

/**
 * काष्ठा rtl2830_platक्रमm_data - Platक्रमm data क्रम the rtl2830 driver
 * @clk: Clock frequency (4000000, 16000000, 25000000, 28800000).
 * @spec_inv: Spectrum inversion.
 * @vtop: AGC take-over poपूर्णांक.
 * @krf: AGC ratio.
 * @agc_targ_val: AGC.
 * @get_dvb_frontend: Get DVB frontend.
 * @get_i2c_adapter: Get I2C adapter.
 * @pid_filter: Set PID to PID filter.
 * @pid_filter_ctrl: Control PID filter.
 */
काष्ठा rtl2830_platक्रमm_data अणु
	u32 clk;
	bool spec_inv;
	u8 vtop;
	u8 krf;
	u8 agc_targ_val;

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
	काष्ठा i2c_adapter* (*get_i2c_adapter)(काष्ठा i2c_client *);
	पूर्णांक (*pid_filter)(काष्ठा dvb_frontend *, u8, u16, पूर्णांक);
	पूर्णांक (*pid_filter_ctrl)(काष्ठा dvb_frontend *, पूर्णांक);
पूर्ण;

#पूर्ण_अगर /* RTL2830_H */
