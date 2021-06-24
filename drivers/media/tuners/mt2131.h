<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Microtune MT2131 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#अगर_अघोषित __MT2131_H__
#घोषणा __MT2131_H__

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

काष्ठा mt2131_config अणु
	u8 i2c_address;
	u8 घड़ी_out; /* 0 = off, 1 = CLK/4, 2 = CLK/2, 3 = CLK/1 */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MT2131)
बाह्य काष्ठा dvb_frontend* mt2131_attach(काष्ठा dvb_frontend *fe,
					  काष्ठा i2c_adapter *i2c,
					  काष्ठा mt2131_config *cfg,
					  u16 अगर1);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* mt2131_attach(काष्ठा dvb_frontend *fe,
						 काष्ठा i2c_adapter *i2c,
						 काष्ठा mt2131_config *cfg,
						 u16 अगर1)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEDIA_TUNER_MT2131 */

#पूर्ण_अगर /* __MT2131_H__ */
