<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STV6110(A) Silicon tuner driver

	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STV6110x_H
#घोषणा __STV6110x_H

काष्ठा stv6110x_config अणु
	u8	addr;
	u32	refclk;
	u8	clk_भाग; /* भागisor value क्रम the output घड़ी */
	काष्ठा dvb_frontend		*frontend;

	काष्ठा stv6110x_devctl* (*get_devctl)(काष्ठा i2c_client *i2c);
पूर्ण;

क्रमागत tuner_mode अणु
	TUNER_SLEEP = 1,
	TUNER_WAKE,
पूर्ण;

क्रमागत tuner_status अणु
	TUNER_PHASELOCKED = 1,
पूर्ण;

काष्ठा stv6110x_devctl अणु
	पूर्णांक (*tuner_init) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_sleep) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_set_mode) (काष्ठा dvb_frontend *fe, क्रमागत tuner_mode mode);
	पूर्णांक (*tuner_set_frequency) (काष्ठा dvb_frontend *fe, u32 frequency);
	पूर्णांक (*tuner_get_frequency) (काष्ठा dvb_frontend *fe, u32 *frequency);
	पूर्णांक (*tuner_set_bandwidth) (काष्ठा dvb_frontend *fe, u32 bandwidth);
	पूर्णांक (*tuner_get_bandwidth) (काष्ठा dvb_frontend *fe, u32 *bandwidth);
	पूर्णांक (*tuner_set_bbgain) (काष्ठा dvb_frontend *fe, u32 gain);
	पूर्णांक (*tuner_get_bbgain) (काष्ठा dvb_frontend *fe, u32 *gain);
	पूर्णांक (*tuner_set_refclk)  (काष्ठा dvb_frontend *fe, u32 refclk);
	पूर्णांक (*tuner_get_status) (काष्ठा dvb_frontend *fe, u32 *status);
पूर्ण;


#अगर IS_REACHABLE(CONFIG_DVB_STV6110x)

बाह्य स्थिर काष्ठा stv6110x_devctl *stv6110x_attach(काष्ठा dvb_frontend *fe,
					       स्थिर काष्ठा stv6110x_config *config,
					       काष्ठा i2c_adapter *i2c);

#अन्यथा
अटल अंतरभूत स्थिर काष्ठा stv6110x_devctl *stv6110x_attach(काष्ठा dvb_frontend *fe,
						      स्थिर काष्ठा stv6110x_config *config,
						      काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_STV6110x */

#पूर्ण_अगर /* __STV6110x_H */
