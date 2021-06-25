<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम Legend Silicon GB20600 (a.k.a DMB-TH) demodulator
 *    LGS8913, LGS8GL5, LGS8G75
 *    experimental support LGS8G42, LGS8G52
 *
 *    Copyright (C) 2007-2009 David T.L. Wong <davidtlwong@gmail.com>
 *    Copyright (C) 2008 Sirius International (Hong Kong) Limited
 *    Timothy Lee <timothy.lee@siriushk.com> (क्रम initial work on LGS8GL5)
 */

#अगर_अघोषित __LGS8GXX_H__
#घोषणा __LGS8GXX_H__

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>

#घोषणा LGS8GXX_PROD_LGS8913 0
#घोषणा LGS8GXX_PROD_LGS8GL5 1
#घोषणा LGS8GXX_PROD_LGS8G42 3
#घोषणा LGS8GXX_PROD_LGS8G52 4
#घोषणा LGS8GXX_PROD_LGS8G54 5
#घोषणा LGS8GXX_PROD_LGS8G75 6

काष्ठा lgs8gxx_config अणु

	/* product type */
	u8 prod;

	/* the demodulator's i2c address */
	u8 demod_address;

	/* parallel or serial transport stream */
	u8 serial_ts;

	/* transport stream polarity*/
	u8 ts_clk_pol;

	/* transport stream घड़ी gated by ts_valid */
	u8 ts_clk_gated;

	/* A/D Clock frequency */
	u32 अगर_clk_freq; /* in kHz */

	/* IF frequency */
	u32 अगर_freq; /* in kHz */

	/*Use External ADC*/
	u8 ext_adc;

	/*External ADC output two's complement*/
	u8 adc_चिन्हित;

	/*Sample IF data at falling edge of IF_CLK*/
	u8 अगर_neg_edge;

	/*IF use Negative center frequency*/
	u8 अगर_neg_center;

	/*8G75 पूर्णांकernal ADC input range selection*/
	/*0: 0.8Vpp, 1: 1.0Vpp, 2: 1.6Vpp, 3: 2.0Vpp*/
	u8 adc_vpp;

	/* slave address and configuration of the tuner */
	u8 tuner_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LGS8GXX)
बाह्य काष्ठा dvb_frontend *lgs8gxx_attach(स्थिर काष्ठा lgs8gxx_config *config,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *lgs8gxx_attach(स्थिर काष्ठा lgs8gxx_config *config,
				    काष्ठा i2c_adapter *i2c) अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_LGS8GXX */

#पूर्ण_अगर /* __LGS8GXX_H__ */
