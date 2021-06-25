<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Montage Technology DS3000 - DVBS/S2 Demodulator driver
    Copyright (C) 2009-2012 Konstantin Dimitrov <kosio.dimitrov@gmail.com>

    Copyright (C) 2009-2012 TurboSight.com

 */

#अगर_अघोषित DS3000_H
#घोषणा DS3000_H

#समावेश <linux/dvb/frontend.h>

काष्ठा ds3000_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;
	u8 ci_mode;
	/* Set device param to start dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured);
	/* Hook क्रम Lock LED */
	व्योम (*set_lock_led)(काष्ठा dvb_frontend *fe, पूर्णांक offon);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DS3000)
बाह्य काष्ठा dvb_frontend *ds3000_attach(स्थिर काष्ठा ds3000_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *ds3000_attach(स्थिर काष्ठा ds3000_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_DS3000 */
#पूर्ण_अगर /* DS3000_H */
