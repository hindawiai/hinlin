<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम OR51211 (pcHDTV HD-2000) - VSB
 *
 *    Copyright (C) 2005 Kirk Lapray <kirk_lapray@bigfoot.com>
*/

#अगर_अघोषित OR51211_H
#घोषणा OR51211_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

काष्ठा or51211_config
अणु
	/* The demodulator's i2c address */
	u8 demod_address;

	/* Request firmware क्रम device */
	पूर्णांक (*request_firmware)(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name);
	व्योम (*seपंचांगode)(काष्ठा dvb_frontend * fe, पूर्णांक mode);
	व्योम (*reset)(काष्ठा dvb_frontend * fe);
	व्योम (*sleep)(काष्ठा dvb_frontend * fe);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_OR51211)
बाह्य काष्ठा dvb_frontend* or51211_attach(स्थिर काष्ठा or51211_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* or51211_attach(स्थिर काष्ठा or51211_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_OR51211

#पूर्ण_अगर // OR51211_H

