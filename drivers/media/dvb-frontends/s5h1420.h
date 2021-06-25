<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम
 *    Samsung S5H1420 and
 *    PnpNetwork PN1010 QPSK Demodulator
 *
 * Copyright (C) 2005 Andrew de Quincey <adq_dvb@lidskialf.net>
 * Copyright (C) 2005-8 Patrick Boettcher <pb@linuxtv.org>
 */
#अगर_अघोषित S5H1420_H
#घोषणा S5H1420_H

#समावेश <linux/dvb/frontend.h>

काष्ठा s5h1420_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* करोes the inversion require inversion? */
	u8 invert:1;

	u8 repeated_start_workaround:1;
	u8 cdclk_polarity:1; /* 1 == falling edge, 0 == raising edge */

	u8 serial_mpeg:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_S5H1420)
बाह्य काष्ठा dvb_frontend *s5h1420_attach(स्थिर काष्ठा s5h1420_config *config,
	     काष्ठा i2c_adapter *i2c);
बाह्य काष्ठा i2c_adapter *s5h1420_get_tuner_i2c_adapter(काष्ठा dvb_frontend *fe);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *s5h1420_attach(स्थिर काष्ठा s5h1420_config *config,
					   काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *s5h1420_get_tuner_i2c_adapter(काष्ठा dvb_frontend *fe)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_S5H1420

#पूर्ण_अगर // S5H1420_H
