<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Conexant 22702 DVB OFDM demodulator driver

    based on:
	Alps TDMB7 DVB OFDM demodulator driver

    Copyright (C) 2001-2002 Convergence Integrated Media GmbH
	  Holger Waechtler <holger@convergence.de>

    Copyright (C) 2004 Steven Toth <stoth@linuxtv.org>


*/

#अगर_अघोषित CX22702_H
#घोषणा CX22702_H

#समावेश <linux/dvb/frontend.h>

काष्ठा cx22702_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* serial/parallel output */
#घोषणा CX22702_PARALLEL_OUTPUT 0
#घोषणा CX22702_SERIAL_OUTPUT   1
	u8 output_mode;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CX22702)
बाह्य काष्ठा dvb_frontend *cx22702_attach(
	स्थिर काष्ठा cx22702_config *config,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cx22702_attach(
	स्थिर काष्ठा cx22702_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
