<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम VES1893 and VES1993 QPSK Demodulators

    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>
    Copyright (C) 2001 Ronny Strutz <3des@elitedvb.de>
    Copyright (C) 2002 Dennis Noermann <dennis.noermann@noernet.de>
    Copyright (C) 2002-2003 Andreas Oberritter <obi@linuxtv.org>


*/

#अगर_अघोषित VES1X93_H
#घोषणा VES1X93_H

#समावेश <linux/dvb/frontend.h>

काष्ठा ves1x93_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* value of XIN to use */
	u32 xin;

	/* should PWM be inverted? */
	u8 invert_pwm:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_VES1X93)
बाह्य काष्ठा dvb_frontend* ves1x93_attach(स्थिर काष्ठा ves1x93_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* ves1x93_attach(स्थिर काष्ठा ves1x93_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_VES1X93

#पूर्ण_अगर // VES1X93_H
