<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम STV0297 demodulator

    Copyright (C) 2003-2004 Dennis Noermann <dennis.noermann@noernet.de>

*/

#अगर_अघोषित STV0297_H
#घोषणा STV0297_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

काष्ठा stv0297_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* inittab - array of pairs of values.
	* First of each pair is the रेजिस्टर, second is the value.
	* List should be terminated with an 0xff, 0xff pair.
	*/
	u8* inittab;

	/* करोes the "inversion" need inverted? */
	u8 invert:1;

	/* set to 1 अगर the device requires an i2c STOP during पढ़ोing */
	u8 stop_during_पढ़ो:1;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV0297)
बाह्य काष्ठा dvb_frontend* stv0297_attach(स्थिर काष्ठा stv0297_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* stv0297_attach(स्थिर काष्ठा stv0297_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_STV0297

#पूर्ण_अगर // STV0297_H
