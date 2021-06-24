<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tuner-xc2028
 *
 * Copyright (c) 2007-2008 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#अगर_अघोषित __TUNER_XC2028_H__
#घोषणा __TUNER_XC2028_H__

#समावेश <media/dvb_frontend.h>

#घोषणा XC2028_DEFAULT_FIRMWARE "xc3028-v27.fw"
#घोषणा XC3028L_DEFAULT_FIRMWARE "xc3028L-v36.fw"

/*      Dmoduler		IF (kHz) */
#घोषणा	XC3028_FE_DEFAULT	0		/* Don't load SCODE */
#घोषणा XC3028_FE_LG60		6000
#घोषणा	XC3028_FE_ATI638	6380
#घोषणा	XC3028_FE_OREN538	5380
#घोषणा	XC3028_FE_OREN36	3600
#घोषणा	XC3028_FE_TOYOTA388	3880
#घोषणा	XC3028_FE_TOYOTA794	7940
#घोषणा	XC3028_FE_DIBCOM52	5200
#घोषणा	XC3028_FE_ZARLINK456	4560
#घोषणा	XC3028_FE_CHINA		5200

क्रमागत firmware_type अणु
	XC2028_AUTO = 0,        /* By शेष, स्वतः-detects */
	XC2028_D2633,
	XC2028_D2620,
पूर्ण;

काष्ठा xc2028_ctrl अणु
	अक्षर			*fname;
	पूर्णांक			max_len;
	पूर्णांक			msleep;
	अचिन्हित पूर्णांक		scode_table;
	अचिन्हित पूर्णांक		mts   :1;
	अचिन्हित पूर्णांक		input1:1;
	अचिन्हित पूर्णांक		vhfbw7:1;
	अचिन्हित पूर्णांक		uhfbw8:1;
	अचिन्हित पूर्णांक		disable_घातer_mgmt:1;
	अचिन्हित पूर्णांक            पढ़ो_not_reliable:1;
	अचिन्हित पूर्णांक		demod;
	क्रमागत firmware_type	type:2;
पूर्ण;

काष्ठा xc2028_config अणु
	काष्ठा i2c_adapter *i2c_adap;
	u8		   i2c_addr;
	काष्ठा xc2028_ctrl *ctrl;
पूर्ण;

/* xc2028 commands क्रम callback */
#घोषणा XC2028_TUNER_RESET	0
#घोषणा XC2028_RESET_CLK	1
#घोषणा XC2028_I2C_FLUSH	2

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_XC2028)
बाह्य काष्ठा dvb_frontend *xc2028_attach(काष्ठा dvb_frontend *fe,
					  काष्ठा xc2028_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *xc2028_attach(काष्ठा dvb_frontend *fe,
						 काष्ठा xc2028_config *cfg)
अणु
	prपूर्णांकk(KERN_INFO "%s: not probed - driver disabled by Kconfig\n",
	       __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __TUNER_XC2028_H__ */
