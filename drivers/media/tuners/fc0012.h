<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Fitiघातer FC0012 tuner driver - include
 *
 * Copyright (C) 2012 Hans-Frieder Vogt <hfvogt@gmx.net>
 */

#अगर_अघोषित _FC0012_H_
#घोषणा _FC0012_H_

#समावेश <media/dvb_frontend.h>
#समावेश "fc001x-common.h"

काष्ठा fc0012_config अणु
	/*
	 * I2C address
	 */
	u8 i2c_address;

	/*
	 * घड़ी
	 */
	क्रमागत fc001x_xtal_freq xtal_freq;

	bool dual_master;

	/*
	 * RF loop-through
	 */
	bool loop_through;

	/*
	 * घड़ी output
	 */
	bool घड़ी_out;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_FC0012)
बाह्य काष्ठा dvb_frontend *fc0012_attach(काष्ठा dvb_frontend *fe,
					काष्ठा i2c_adapter *i2c,
					स्थिर काष्ठा fc0012_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *fc0012_attach(काष्ठा dvb_frontend *fe,
					काष्ठा i2c_adapter *i2c,
					स्थिर काष्ठा fc0012_config *cfg)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
