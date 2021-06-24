<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stv0900.h
 *
 * Driver क्रम ST STV0900 satellite demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित STV0900_H
#घोषणा STV0900_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

काष्ठा stv0900_reg अणु
	u16 addr;
	u8  val;
पूर्ण;

काष्ठा stv0900_config अणु
	u8 demod_address;
	u8 demod_mode;
	u32 xtal;
	u8 clkmode;/* 0 क्रम CLKI,  2 क्रम XTALI */

	u8 diseqc_mode;

	u8 path1_mode;
	u8 path2_mode;
	काष्ठा stv0900_reg *ts_config_regs;
	u8 tun1_maddress;/* 0, 1, 2, 3 क्रम 0xc0, 0xc2, 0xc4, 0xc6 */
	u8 tun2_maddress;
	u8 tun1_adc;/* 1 क्रम stv6110, 2 क्रम stb6100 */
	u8 tun2_adc;
	u8 tun1_type;/* क्रम now 3 क्रम stb6100 स्वतः, अन्यथा - software */
	u8 tun2_type;
	/* Set device param to start dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured);
	/* Hook क्रम Lock LED */
	व्योम (*set_lock_led)(काष्ठा dvb_frontend *fe, पूर्णांक offon);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV0900)
बाह्य काष्ठा dvb_frontend *stv0900_attach(स्थिर काष्ठा stv0900_config *config,
					काष्ठा i2c_adapter *i2c, पूर्णांक demod);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *stv0900_attach(स्थिर काष्ठा stv0900_config *config,
					काष्ठा i2c_adapter *i2c, पूर्णांक demod)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

