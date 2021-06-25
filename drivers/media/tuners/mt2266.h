<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Microtune MT2266 "Direct conversion low power broadband tuner"
 *
 *  Copyright (c) 2007 Olivier DANET <odanet@caramail.com>
 */

#अगर_अघोषित MT2266_H
#घोषणा MT2266_H

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

काष्ठा mt2266_config अणु
	u8 i2c_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MT2266)
बाह्य काष्ठा dvb_frontend * mt2266_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा mt2266_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend * mt2266_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा mt2266_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_MEDIA_TUNER_MT2266

#पूर्ण_अगर
