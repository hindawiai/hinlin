<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम Spase SP8870 demodulator

    Copyright (C) 1999 Juergen Peitz


*/

#अगर_अघोषित SP8870_H
#घोषणा SP8870_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

काष्ठा sp8870_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* request firmware क्रम device */
	पूर्णांक (*request_firmware)(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_SP8870)
बाह्य काष्ठा dvb_frontend* sp8870_attach(स्थिर काष्ठा sp8870_config* config,
					  काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* sp8870_attach(स्थिर काष्ठा sp8870_config* config,
					  काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_SP8870

#पूर्ण_अगर // SP8870_H
