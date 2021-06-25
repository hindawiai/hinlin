<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम OR51132 (pcHDTV HD-3000) - VSB/QAM
 *
 *    Copyright (C) 2005 Kirk Lapray <kirk_lapray@bigfoot.com>
*/

#अगर_अघोषित OR51132_H
#घोषणा OR51132_H

#समावेश <linux/firmware.h>
#समावेश <linux/dvb/frontend.h>

काष्ठा or51132_config
अणु
	/* The demodulator's i2c address */
	u8 demod_address;

	/* Need to set device param क्रम start_dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend* fe, पूर्णांक is_punctured);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_OR51132)
बाह्य काष्ठा dvb_frontend* or51132_attach(स्थिर काष्ठा or51132_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* or51132_attach(स्थिर काष्ठा or51132_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_OR51132

#पूर्ण_अगर // OR51132_H
