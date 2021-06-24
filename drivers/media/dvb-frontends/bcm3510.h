<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Support क्रम the Broadcom BCM3510 ATSC demodulator (1st generation Air2PC)
 *
 *  Copyright (C) 2001-5, B2C2 inc.
 *
 *  GPL/Linux driver written by Patrick Boettcher <patrick.boettcher@posteo.de>
 */
#अगर_अघोषित BCM3510_H
#घोषणा BCM3510_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

काष्ठा bcm3510_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* request firmware क्रम device */
	पूर्णांक (*request_firmware)(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_BCM3510)
बाह्य काष्ठा dvb_frontend* bcm3510_attach(स्थिर काष्ठा bcm3510_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* bcm3510_attach(स्थिर काष्ठा bcm3510_config* config,
						  काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_BCM3510

#पूर्ण_अगर
