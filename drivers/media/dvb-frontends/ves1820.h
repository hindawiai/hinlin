<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    VES1820  - Single Chip Cable Channel Receiver driver module

    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>

*/

#अगर_अघोषित VES1820_H
#घोषणा VES1820_H

#समावेश <linux/dvb/frontend.h>

#घोषणा VES1820_SELAGC_PWM 0
#घोषणा VES1820_SELAGC_SIGNAMPERR 1

काष्ठा ves1820_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* value of XIN to use */
	u32 xin;

	/* करोes inversion need inverted? */
	u8 invert:1;

	/* SELAGC control */
	u8 selagc:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_VES1820)
बाह्य काष्ठा dvb_frontend* ves1820_attach(स्थिर काष्ठा ves1820_config* config,
					   काष्ठा i2c_adapter* i2c, u8 pwm);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* ves1820_attach(स्थिर काष्ठा ves1820_config* config,
					   काष्ठा i2c_adapter* i2c, u8 pwm)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_VES1820

#पूर्ण_अगर // VES1820_H
