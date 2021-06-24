<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	TDA8261 8PSK/QPSK tuner driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __TDA8261_H
#घोषणा __TDA8261_H

क्रमागत tda8261_step अणु
	TDA8261_STEP_2000 = 0,	/* 2000 kHz */
	TDA8261_STEP_1000,	/* 1000 kHz */
	TDA8261_STEP_500,	/*  500 kHz */
	TDA8261_STEP_250,	/*  250 kHz */
	TDA8261_STEP_125	/*  125 kHz */
पूर्ण;

काष्ठा tda8261_config अणु
//	u8			buf[16];
	u8			addr;
	क्रमागत tda8261_step	step_size;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA8261)

बाह्य काष्ठा dvb_frontend *tda8261_attach(काष्ठा dvb_frontend *fe,
					   स्थिर काष्ठा tda8261_config *config,
					   काष्ठा i2c_adapter *i2c);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *tda8261_attach(काष्ठा dvb_frontend *fe,
						  स्थिर काष्ठा tda8261_config *config,
						  काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर //CONFIG_DVB_TDA8261

#पूर्ण_अगर// __TDA8261_H
