<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Sharp s921 driver
 *
 *   Copyright (C) 2009 Mauro Carvalho Chehab
 *   Copyright (C) 2009 Douglas Landgraf <करोugsland@redhat.com>
 */

#अगर_अघोषित S921_H
#घोषणा S921_H

#समावेश <linux/dvb/frontend.h>

काष्ठा s921_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_S921)
बाह्य काष्ठा dvb_frontend *s921_attach(स्थिर काष्ठा s921_config *config,
					   काष्ठा i2c_adapter *i2c);
बाह्य काष्ठा i2c_adapter *s921_get_tuner_i2c_adapter(काष्ठा dvb_frontend *);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *s921_attach(
	स्थिर काष्ठा s921_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा i2c_adapter *
	s921_get_tuner_i2c_adapter(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* S921_H */
