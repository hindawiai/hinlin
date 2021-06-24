<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Freescale MC44S803 Low Power CMOS Broadband Tuner
 *
 *  Copyright (c) 2009 Jochen Friedrich <jochen@scram.de>
 */

#अगर_अघोषित MC44S803_H
#घोषणा MC44S803_H

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

काष्ठा mc44s803_config अणु
	u8 i2c_address;
	u8 dig_out;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MC44S803)
बाह्य काष्ठा dvb_frontend *mc44s803_attach(काष्ठा dvb_frontend *fe,
	 काष्ठा i2c_adapter *i2c, काष्ठा mc44s803_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *mc44s803_attach(काष्ठा dvb_frontend *fe,
	 काष्ठा i2c_adapter *i2c, काष्ठा mc44s803_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEDIA_TUNER_MC44S803 */

#पूर्ण_अगर
