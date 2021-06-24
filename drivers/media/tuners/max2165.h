<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Maxim MAX2165 silicon tuner
 *
 *  Copyright (c) 2009 David T. L. Wong <davidtlwong@gmail.com>
 */

#अगर_अघोषित __MAX2165_H__
#घोषणा __MAX2165_H__

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

काष्ठा max2165_config अणु
	u8 i2c_address;
	u8 osc_clk; /* in MHz, selectable values: 4,16,18,20,22,24,26,28 */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MAX2165)
बाह्य काष्ठा dvb_frontend *max2165_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c,
	काष्ठा max2165_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *max2165_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c,
	काष्ठा max2165_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
