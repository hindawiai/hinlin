<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * horus3a.h
 *
 * Sony Horus3A DVB-S/S2 tuner driver
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#अगर_अघोषित __DVB_HORUS3A_H__
#घोषणा __DVB_HORUS3A_H__

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>

/**
 * काष्ठा horus3a_config - the configuration of Horus3A tuner driver
 * @i2c_address:    I2C address of the tuner
 * @xtal_freq_mhz:  Oscillator frequency, MHz
 * @set_tuner_priv: Callback function निजी context
 * @set_tuner_callback: Callback function that notअगरies the parent driver
 *          which tuner is active now
 */
काष्ठा horus3a_config अणु
	u8	i2c_address;
	u8	xtal_freq_mhz;
	व्योम	*set_tuner_priv;
	पूर्णांक	(*set_tuner_callback)(व्योम *, पूर्णांक);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_HORUS3A)
/**
 * horus3a_attach - Attach a horus3a tuner
 *
 * @fe: frontend to be attached
 * @config: poपूर्णांकer to &काष्ठा helene_config with tuner configuration.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *horus3a_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा horus3a_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *horus3a_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा horus3a_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
