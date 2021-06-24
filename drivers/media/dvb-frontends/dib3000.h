<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * खुला header file of the frontend drivers क्रम mobile DVB-T demodulators
 * DiBcom 3000M-B and DiBcom 3000P/M-C (http://www.dibcom.fr/)
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * based on GPL code from DibCom, which has
 *
 * Copyright (C) 2004 Amaury Demol क्रम DiBcom
 *
 * Acknowledgements
 *
 *  Amaury Demol from DiBcom क्रम providing specs and driver
 *  sources, on which this driver (and the dvb-dibusb) are based.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#अगर_अघोषित DIB3000_H
#घोषणा DIB3000_H

#समावेश <linux/dvb/frontend.h>

काष्ठा dib3000_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

काष्ठा dib_fe_xfer_ops
अणु
	/* pid and transfer handling is करोne in the demodulator */
	पूर्णांक (*pid_parse)(काष्ठा dvb_frontend *fe, पूर्णांक onoff);
	पूर्णांक (*fअगरo_ctrl)(काष्ठा dvb_frontend *fe, पूर्णांक onoff);
	पूर्णांक (*pid_ctrl)(काष्ठा dvb_frontend *fe, पूर्णांक index, पूर्णांक pid, पूर्णांक onoff);
	पूर्णांक (*tuner_pass_ctrl)(काष्ठा dvb_frontend *fe, पूर्णांक onoff, u8 pll_ctrl);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DIB3000MB)
बाह्य काष्ठा dvb_frontend* dib3000mb_attach(स्थिर काष्ठा dib3000_config* config,
					     काष्ठा i2c_adapter* i2c, काष्ठा dib_fe_xfer_ops *xfer_ops);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* dib3000mb_attach(स्थिर काष्ठा dib3000_config* config,
					     काष्ठा i2c_adapter* i2c, काष्ठा dib_fe_xfer_ops *xfer_ops)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_DIB3000MB

#पूर्ण_अगर // DIB3000_H
