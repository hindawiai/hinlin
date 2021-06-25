<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Quantek QT1010 silicon tuner
 *
 *  Copyright (C) 2006 Antti Palosaari <crope@iki.fi>
 *                     Aapo Tahkola <aet@rasterburn.org>
 */

#अगर_अघोषित QT1010_H
#घोषणा QT1010_H

#समावेश <media/dvb_frontend.h>

काष्ठा qt1010_config अणु
	u8 i2c_address;
पूर्ण;

/**
 * qt1010_attach() - Attach a qt1010 tuner to the supplied frontend काष्ठाure
 *
 * @fe:   frontend to attach to
 * @i2c:  i2c adapter to use
 * @cfg:  tuner hw based configuration
 * @वापस fe  poपूर्णांकer on success, शून्य on failure
 */
#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_QT1010)
बाह्य काष्ठा dvb_frontend *qt1010_attach(काष्ठा dvb_frontend *fe,
					  काष्ठा i2c_adapter *i2c,
					  काष्ठा qt1010_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *qt1010_attach(काष्ठा dvb_frontend *fe,
						 काष्ठा i2c_adapter *i2c,
						 काष्ठा qt1010_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_MEDIA_TUNER_QT1010

#पूर्ण_अगर
