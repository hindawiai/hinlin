<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Legend Silicon LGS-8GL5 DMB-TH OFDM demodulator driver

    Copyright (C) 2008 Sirius International (Hong Kong) Limited
	Timothy Lee <timothy.lee@siriushk.com>


*/

#अगर_अघोषित LGS8GL5_H
#घोषणा LGS8GL5_H

#समावेश <linux/dvb/frontend.h>

काष्ठा lgs8gl5_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LGS8GL5)
बाह्य काष्ठा dvb_frontend *lgs8gl5_attach(
	स्थिर काष्ठा lgs8gl5_config *config, काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *lgs8gl5_attach(
	स्थिर काष्ठा lgs8gl5_config *config, काष्ठा i2c_adapter *i2c) अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_LGS8GL5 */

#पूर्ण_अगर /* LGS8GL5_H */
