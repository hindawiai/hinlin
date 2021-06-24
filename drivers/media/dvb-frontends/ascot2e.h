<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ascot2e.h
 *
 * Sony Ascot3E DVB-T/T2/C/C2 tuner driver
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#अगर_अघोषित __DVB_ASCOT2E_H__
#घोषणा __DVB_ASCOT2E_H__

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>

/**
 * काष्ठा ascot2e_config - the configuration of Ascot2E tuner driver
 * @i2c_address:	I2C address of the tuner
 * @xtal_freq_mhz:	Oscillator frequency, MHz
 * @set_tuner_priv:	Callback function निजी context
 * @set_tuner_callback:	Callback function that notअगरies the parent driver
 *			which tuner is active now
 */
काष्ठा ascot2e_config अणु
	u8	i2c_address;
	u8	xtal_freq_mhz;
	व्योम	*set_tuner_priv;
	पूर्णांक	(*set_tuner_callback)(व्योम *, पूर्णांक);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_ASCOT2E)
/**
 * ascot2e_attach - Attach an ascot2e tuner
 *
 * @fe: frontend to be attached
 * @config: poपूर्णांकer to &काष्ठा ascot2e_config with tuner configuration.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *ascot2e_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा ascot2e_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *ascot2e_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा ascot2e_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
