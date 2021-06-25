<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * E3C EC100 demodulator driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित EC100_H
#घोषणा EC100_H

#समावेश <linux/dvb/frontend.h>

काष्ठा ec100_config अणु
	/* demodulator's I2C address */
	u8 demod_address;
पूर्ण;


#अगर IS_REACHABLE(CONFIG_DVB_EC100)
बाह्य काष्ठा dvb_frontend *ec100_attach(स्थिर काष्ठा ec100_config *config,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *ec100_attach(
	स्थिर काष्ठा ec100_config *config, काष्ठा i2c_adapter *i2c)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* EC100_H */
