<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Fujitsu mb86a20s driver
 *
 *   Copyright (C) 2010 Mauro Carvalho Chehab
 */

#अगर_अघोषित MB86A20S_H
#घोषणा MB86A20S_H

#समावेश <linux/dvb/frontend.h>

/**
 * काष्ठा mb86a20s_config - Define the per-device attributes of the frontend
 *
 * @fclk:		Clock frequency. If zero, assumes the शेष
 *			(32.57142 Mhz)
 * @demod_address:	the demodulator's i2c address
 * @is_serial:		अगर true, TS is serial. Otherwise, TS is parallel
 */
काष्ठा mb86a20s_config अणु
	u32	fclk;
	u8	demod_address;
	bool	is_serial;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_MB86A20S)
/**
 * mb86a20s_attach - Attach a mb86a20s demod
 *
 * @config: poपूर्णांकer to &काष्ठा mb86a20s_config with demod configuration.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *mb86a20s_attach(स्थिर काष्ठा mb86a20s_config *config,
					   काष्ठा i2c_adapter *i2c);

#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *mb86a20s_attach(
	स्थिर काष्ठा mb86a20s_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* MB86A20S */
