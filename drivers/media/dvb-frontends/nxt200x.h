<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम NXT2002 and NXT2004 - VSB/QAM
 *
 *    Copyright (C) 2005 Kirk Lapray (kirk.lapray@gmail.com)
 *    based on nxt2002 by Taylor Jacob <rtjacob@earthlink.net>
 *    and nxt2004 by Jean-Francois Thibert (jeanfrancois@sagetv.com)
*/

#अगर_अघोषित NXT200X_H
#घोषणा NXT200X_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

प्रकार क्रमागत nxt_chip_t अणु
		NXTUNDEFINED,
		NXT2002,
		NXT2004
पूर्णnxt_chip_type;

काष्ठा nxt200x_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* need to set device param क्रम start_dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend* fe, पूर्णांक is_punctured);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_NXT200X)
बाह्य काष्ठा dvb_frontend* nxt200x_attach(स्थिर काष्ठा nxt200x_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* nxt200x_attach(स्थिर काष्ठा nxt200x_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_NXT200X

#पूर्ण_अगर /* NXT200X_H */
