<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	NxtWave Communications - NXT6000 demodulator driver

    Copyright (C) 2002-2003 Florian Schirmer <jolt@tuxbox.org>
    Copyright (C) 2003 Paul Andreassen <paul@andreassen.com.au>

*/

#अगर_अघोषित NXT6000_H
#घोषणा NXT6000_H

#समावेश <linux/dvb/frontend.h>

काष्ठा nxt6000_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* should घड़ी inversion be used? */
	u8 घड़ी_inversion:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_NXT6000)
बाह्य काष्ठा dvb_frontend* nxt6000_attach(स्थिर काष्ठा nxt6000_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* nxt6000_attach(स्थिर काष्ठा nxt6000_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_NXT6000

#पूर्ण_अगर // NXT6000_H
