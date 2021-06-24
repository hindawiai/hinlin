<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम ST STV0299 demodulator

    Copyright (C) 2001-2002 Convergence Integrated Media GmbH
	<ralph@convergence.de>,
	<holger@convergence.de>,
	<js@convergence.de>


    Philips SU1278/SH

    Copyright (C) 2002 by Peter Schildmann <peter.schildmann@web.de>


    LG TDQF-S001F

    Copyright (C) 2002 Felix Domke <पंचांगbinc@elitedvb.net>
		     & Andreas Oberritter <obi@linuxtv.org>


    Support क्रम Samsung TBMU24112IMB used on Technisat SkyStar2 rev. 2.6B

    Copyright (C) 2003 Vadim Catana <skystar@molकरोva.cc>:

    Support क्रम Philips SU1278 on Technotrend hardware

    Copyright (C) 2004 Andrew de Quincey <adq_dvb@lidskialf.net>


*/

#अगर_अघोषित STV0299_H
#घोषणा STV0299_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

#घोषणा STV0299_LOCKOUTPUT_0  0
#घोषणा STV0299_LOCKOUTPUT_1  1
#घोषणा STV0299_LOCKOUTPUT_CF 2
#घोषणा STV0299_LOCKOUTPUT_LK 3

#घोषणा STV0299_VOLT13_OP0 0
#घोषणा STV0299_VOLT13_OP1 1

काष्ठा stv0299_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* inittab - array of pairs of values.
	 * First of each pair is the रेजिस्टर, second is the value.
	 * List should be terminated with an 0xff, 0xff pair.
	 */
	स्थिर u8* inittab;

	/* master घड़ी to use */
	u32 mclk;

	/* करोes the inversion require inversion? */
	u8 invert:1;

	/* Skip reinitialisation? */
	u8 skip_reinit:1;

	/* LOCK OUTPUT setting */
	u8 lock_output:2;

	/* Is 13v controlled by OP0 or OP1? */
	u8 volt13_op0_op1:1;

	/* Turn-off OP0? */
	u8 op0_off:1;

	/* minimum delay beक्रमe retuning */
	पूर्णांक min_delay_ms;

	/* Set the symbol rate */
	पूर्णांक (*set_symbol_rate)(काष्ठा dvb_frontend *fe, u32 srate, u32 ratio);

	/* Set device param to start dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV0299)
बाह्य काष्ठा dvb_frontend *stv0299_attach(स्थिर काष्ठा stv0299_config *config,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *stv0299_attach(स्थिर काष्ठा stv0299_config *config,
					   काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_STV0299

अटल अंतरभूत पूर्णांक stv0299_ग_लिखोreg(काष्ठा dvb_frontend *fe, u8 reg, u8 val) अणु
	पूर्णांक r = 0;
	u8 buf[] = अणुreg, valपूर्ण;
	अगर (fe->ops.ग_लिखो)
		r = fe->ops.ग_लिखो(fe, buf, 2);
	वापस r;
पूर्ण

#पूर्ण_अगर // STV0299_H
