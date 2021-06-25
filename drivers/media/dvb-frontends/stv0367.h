<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stv0367.h
 *
 * Driver क्रम ST STV0367 DVB-T & DVB-C demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2010,2011 NetUP Inc.
 * Copyright (C) 2010,2011 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित STV0367_H
#घोषणा STV0367_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

#घोषणा STV0367_ICSPEED_53125	53125000
#घोषणा STV0367_ICSPEED_58000	58000000

काष्ठा stv0367_config अणु
	u8 demod_address;
	u32 xtal;
	u32 अगर_khz;/*4500*/
	पूर्णांक अगर_iq_mode;
	पूर्णांक ts_mode;
	पूर्णांक clk_pol;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV0367)
बाह्य काष्ठा
dvb_frontend *stv0367ter_attach(स्थिर काष्ठा stv0367_config *config,
					काष्ठा i2c_adapter *i2c);
बाह्य काष्ठा
dvb_frontend *stv0367cab_attach(स्थिर काष्ठा stv0367_config *config,
					काष्ठा i2c_adapter *i2c);
बाह्य काष्ठा
dvb_frontend *stv0367ddb_attach(स्थिर काष्ठा stv0367_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा
dvb_frontend *stv0367ter_attach(स्थिर काष्ठा stv0367_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा
dvb_frontend *stv0367cab_attach(स्थिर काष्ठा stv0367_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा
dvb_frontend *stv0367ddb_attach(स्थिर काष्ठा stv0367_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
