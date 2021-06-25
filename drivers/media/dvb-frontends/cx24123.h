<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Conexant cx24123/cx24109 - DVB QPSK Satellite demod/tuner driver

    Copyright (C) 2005 Steven Toth <stoth@linuxtv.org>

*/

#अगर_अघोषित CX24123_H
#घोषणा CX24123_H

#समावेश <linux/dvb/frontend.h>

काष्ठा cx24123_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* Need to set device param क्रम start_dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured);

	/* 0 = LNB voltage normal, 1 = LNB voltage inverted */
	पूर्णांक lnb_polarity;

	/* this device has another tuner */
	u8 करोnt_use_pll;
	व्योम (*agc_callback) (काष्ठा dvb_frontend *);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CX24123)
बाह्य काष्ठा dvb_frontend *cx24123_attach(स्थिर काष्ठा cx24123_config *config,
					   काष्ठा i2c_adapter *i2c);
बाह्य काष्ठा i2c_adapter *cx24123_get_tuner_i2c_adapter(काष्ठा dvb_frontend *);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cx24123_attach(
	स्थिर काष्ठा cx24123_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा i2c_adapter *
	cx24123_get_tuner_i2c_adapter(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CX24123_H */
