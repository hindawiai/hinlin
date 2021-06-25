<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम AltoBeam GB20600 (a.k.a DMB-TH) demodulator
 *    ATBM8830, ATBM8831
 *
 *    Copyright (C) 2009 David T.L. Wong <davidtlwong@gmail.com>
 */

#अगर_अघोषित __ATBM8830_H__
#घोषणा __ATBM8830_H__

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>

#घोषणा ATBM8830_PROD_8830 0
#घोषणा ATBM8830_PROD_8831 1

काष्ठा atbm8830_config अणु

	/* product type */
	u8 prod;

	/* the demodulator's i2c address */
	u8 demod_address;

	/* parallel or serial transport stream */
	u8 serial_ts;

	/* transport stream घड़ी output only when receiving valid stream */
	u8 ts_clk_gated;

	/* Decoder sample TS data at rising edge of घड़ी */
	u8 ts_sampling_edge;

	/* Oscillator घड़ी frequency */
	u32 osc_clk_freq; /* in kHz */

	/* IF frequency */
	u32 अगर_freq; /* in kHz */

	/* Swap I/Q क्रम zero IF */
	u8 zअगर_swap_iq;

	/* Tuner AGC settings */
	u8 agc_min;
	u8 agc_max;
	u8 agc_hold_loop;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_ATBM8830)
बाह्य काष्ठा dvb_frontend *atbm8830_attach(स्थिर काष्ठा atbm8830_config *config,
		काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *atbm8830_attach(स्थिर काष्ठा atbm8830_config *config,
		काष्ठा i2c_adapter *i2c) अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_ATBM8830 */

#पूर्ण_अगर /* __ATBM8830_H__ */
