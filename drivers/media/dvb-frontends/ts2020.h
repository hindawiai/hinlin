<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Montage Technology TS2020 - Silicon Tuner driver
    Copyright (C) 2009-2012 Konstantin Dimitrov <kosio.dimitrov@gmail.com>

    Copyright (C) 2009-2012 TurboSight.com

 */

#अगर_अघोषित TS2020_H
#घोषणा TS2020_H

#समावेश <linux/dvb/frontend.h>

काष्ठा ts2020_config अणु
	u8 tuner_address;
	u32 frequency_भाग;

	/*
	 * RF loop-through
	 */
	bool loop_through:1;

	/*
	 * घड़ी output
	 */
#घोषणा TS2020_CLK_OUT_DISABLED        0
#घोषणा TS2020_CLK_OUT_ENABLED         1
#घोषणा TS2020_CLK_OUT_ENABLED_XTALOUT 2
	u8 clk_out:2;

	/*
	 * घड़ी output भागider
	 * 1 - 31
	 */
	u8 clk_out_भाग:5;

	/* Set to true to suppress stat polling */
	bool करोnt_poll:1;

	/*
	 * poपूर्णांकer to DVB frontend
	 */
	काष्ठा dvb_frontend *fe;

	/*
	 * driver निजी, करो not set value
	 */
	u8 attach_in_use:1;

	/* Operation to be called by the ts2020 driver to get the value of the
	 * AGC PWM tuner input as theoretically output by the demodulator.
	 */
	पूर्णांक (*get_agc_pwm)(काष्ठा dvb_frontend *fe, u8 *_agc_pwm);
पूर्ण;

/* Do not add new ts2020_attach() users! Use I2C bindings instead. */
#अगर IS_REACHABLE(CONFIG_DVB_TS2020)
बाह्य काष्ठा dvb_frontend *ts2020_attach(
	काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा ts2020_config *config,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *ts2020_attach(
	काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा ts2020_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* TS2020_H */
