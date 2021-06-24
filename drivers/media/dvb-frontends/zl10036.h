<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम Zarlink ZL10036 DVB-S silicon tuner
 *
 * Copyright (C) 2006 Tino Reiअक्षरdt
 * Copyright (C) 2007-2009 Matthias Schwarzott <zzam@gentoo.de>
 */

#अगर_अघोषित DVB_ZL10036_H
#घोषणा DVB_ZL10036_H

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

काष्ठा zl10036_config अणु
	u8 tuner_address;
	पूर्णांक rf_loop_enable;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_ZL10036)
/**
 * zl10036_attach - Attach a zl10036 tuner to the supplied frontend काष्ठाure.
 *
 * @fe: Frontend to attach to.
 * @config: zl10036_config काष्ठाure.
 * @i2c: poपूर्णांकer to काष्ठा i2c_adapter.
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *zl10036_attach(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा zl10036_config *config, काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *zl10036_attach(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा zl10036_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* DVB_ZL10036_H */
