<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
*/

#अगर_अघोषित __TUNER_SIMPLE_H__
#घोषणा __TUNER_SIMPLE_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_SIMPLE)
बाह्य काष्ठा dvb_frontend *simple_tuner_attach(काष्ठा dvb_frontend *fe,
						काष्ठा i2c_adapter *i2c_adap,
						u8 i2c_addr,
						अचिन्हित पूर्णांक type);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *simple_tuner_attach(काष्ठा dvb_frontend *fe,
						       काष्ठा i2c_adapter *i2c_adap,
						       u8 i2c_addr,
						       अचिन्हित पूर्णांक type)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __TUNER_SIMPLE_H__ */
