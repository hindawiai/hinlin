<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
   Driver क्रम the Spase sp887x demodulator
*/

#अगर_अघोषित SP887X_H
#घोषणा SP887X_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

काष्ठा sp887x_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* request firmware क्रम device */
	पूर्णांक (*request_firmware)(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_SP887X)
बाह्य काष्ठा dvb_frontend* sp887x_attach(स्थिर काष्ठा sp887x_config* config,
					  काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* sp887x_attach(स्थिर काष्ठा sp887x_config* config,
					  काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_SP887X

#पूर्ण_अगर // SP887X_H
