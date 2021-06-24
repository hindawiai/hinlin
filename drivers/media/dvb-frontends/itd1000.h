<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Integrant ITD1000 "Zero-IF Tuner IC for Direct Broadcast Satellite"
 *
 *  Copyright (c) 2007 Patrick Boettcher <pb@linuxtv.org>
 */

#अगर_अघोषित ITD1000_H
#घोषणा ITD1000_H

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

काष्ठा itd1000_config अणु
	u8 i2c_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TUNER_ITD1000)
बाह्य काष्ठा dvb_frontend *itd1000_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा itd1000_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *itd1000_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा itd1000_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
