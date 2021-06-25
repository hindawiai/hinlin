<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
*/

#अगर_अघोषित __TDA9887_H__
#घोषणा __TDA9887_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

/* ------------------------------------------------------------------------ */
#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_TDA9887)
बाह्य काष्ठा dvb_frontend *tda9887_attach(काष्ठा dvb_frontend *fe,
					   काष्ठा i2c_adapter *i2c_adap,
					   u8 i2c_addr);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *tda9887_attach(काष्ठा dvb_frontend *fe,
						  काष्ठा i2c_adapter *i2c_adap,
						  u8 i2c_addr)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __TDA9887_H__ */
