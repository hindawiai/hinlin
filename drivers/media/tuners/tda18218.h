<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA18218HN silicon tuner driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TDA18218_H
#घोषणा TDA18218_H

#समावेश <media/dvb_frontend.h>

काष्ठा tda18218_config अणु
	u8 i2c_address;
	u8 i2c_wr_max;
	u8 loop_through:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_TDA18218)
बाह्य काष्ठा dvb_frontend *tda18218_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c, काष्ठा tda18218_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *tda18218_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c, काष्ठा tda18218_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
