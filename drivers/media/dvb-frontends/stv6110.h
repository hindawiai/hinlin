<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stv6110.h
 *
 * Driver क्रम ST STV6110 satellite tuner IC.
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित __DVB_STV6110_H__
#घोषणा __DVB_STV6110_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

/* रेजिस्टरs */
#घोषणा RSTV6110_CTRL1		0
#घोषणा RSTV6110_CTRL2		1
#घोषणा RSTV6110_TUNING1	2
#घोषणा RSTV6110_TUNING2	3
#घोषणा RSTV6110_CTRL3		4
#घोषणा RSTV6110_STAT1		5
#घोषणा RSTV6110_STAT2		6
#घोषणा RSTV6110_STAT3		7

काष्ठा stv6110_config अणु
	u8 i2c_address;
	u32 mclk;
	u8 gain;
	u8 clk_भाग;	/* भागisor value क्रम the output घड़ी */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV6110)
बाह्य काष्ठा dvb_frontend *stv6110_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा stv6110_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *stv6110_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा stv6110_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
