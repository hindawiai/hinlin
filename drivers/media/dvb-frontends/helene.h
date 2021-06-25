<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * helene.h
 *
 * Sony HELENE DVB-S/S2/T/T2/C/C2/ISDB-T/S tuner driver (CXD2858ER)
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#अगर_अघोषित __DVB_HELENE_H__
#घोषणा __DVB_HELENE_H__

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>

क्रमागत helene_xtal अणु
	SONY_HELENE_XTAL_16000, /* 16 MHz */
	SONY_HELENE_XTAL_20500, /* 20.5 MHz */
	SONY_HELENE_XTAL_24000, /* 24 MHz */
	SONY_HELENE_XTAL_41000 /* 41 MHz */
पूर्ण;

/**
 * काष्ठा helene_config - the configuration of 'Helene' tuner driver
 * @i2c_address:	I2C address of the tuner
 * @xtal_freq_mhz:	Oscillator frequency, MHz
 * @set_tuner_priv:	Callback function निजी context
 * @set_tuner_callback:	Callback function that notअगरies the parent driver
 *			which tuner is active now
 * @xtal: Cristal frequency as described by &क्रमागत helene_xtal
 * @fe: Frontend क्रम which connects this tuner
 */
काष्ठा helene_config अणु
	u8	i2c_address;
	u8	xtal_freq_mhz;
	व्योम	*set_tuner_priv;
	पूर्णांक	(*set_tuner_callback)(व्योम *, पूर्णांक);
	क्रमागत helene_xtal xtal;

	काष्ठा dvb_frontend *fe;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_HELENE)
/**
 * helene_attach - Attach a helene tuner (terrestrial and cable standards)
 *
 * @fe: frontend to be attached
 * @config: poपूर्णांकer to &काष्ठा helene_config with tuner configuration.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *helene_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा helene_config *config,
					काष्ठा i2c_adapter *i2c);

/**
 * helene_attach_s - Attach a helene tuner (satellite standards)
 *
 * @fe: frontend to be attached
 * @config: poपूर्णांकer to &काष्ठा helene_config with tuner configuration.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *helene_attach_s(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा helene_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *helene_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा helene_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dvb_frontend *helene_attach_s(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा helene_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
