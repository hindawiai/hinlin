<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Zarlink DVB-T MT352 demodulator
 *
 *  Written by Holger Waechtler <holger@qanu.de>
 *	 and Daniel Mack <daniel@qanu.de>
 *
 *  AVerMedia AVerTV DVB-T 771 support by
 *       Wolfram Joost <dbox2@frokaschwei.de>
 *
 *  Support क्रम Samsung TDTC9251DH01C(M) tuner
 *  Copyright (C) 2004 Antonio Mancuso <antonio.mancuso@digitaltelevision.it>
 *                     Amauri  Celani  <acelani@essegi.net>
 *
 *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Lite support by
 *       Christopher Pascoe <c.pascoe@itee.uq.edu.au>
 */

#अगर_अघोषित MT352_H
#घोषणा MT352_H

#समावेश <linux/dvb/frontend.h>

काष्ठा mt352_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* frequencies in kHz */
	पूर्णांक adc_घड़ी;  // शेष: 20480
	पूर्णांक अगर2;        // शेष: 36166

	/* set अगर no pll is connected to the secondary i2c bus */
	पूर्णांक no_tuner;

	/* Initialise the demodulator and PLL. Cannot be शून्य */
	पूर्णांक (*demod_init)(काष्ठा dvb_frontend* fe);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_MT352)
बाह्य काष्ठा dvb_frontend* mt352_attach(स्थिर काष्ठा mt352_config* config,
					 काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* mt352_attach(स्थिर काष्ठा mt352_config* config,
					 काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_MT352

अटल अंतरभूत पूर्णांक mt352_ग_लिखो(काष्ठा dvb_frontend *fe, स्थिर u8 buf[], पूर्णांक len) अणु
	पूर्णांक r = 0;
	अगर (fe->ops.ग_लिखो)
		r = fe->ops.ग_लिखो(fe, buf, len);
	वापस r;
पूर्ण

#पूर्ण_अगर // MT352_H
