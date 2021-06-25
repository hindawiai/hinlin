<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम Zarlink ZL10039 DVB-S tuner

    Copyright (C) 2007 Jan D. Louw <jd.louw@mweb.co.za>

*/

#अगर_अघोषित ZL10039_H
#घोषणा ZL10039_H

#अगर IS_REACHABLE(CONFIG_DVB_ZL10039)
काष्ठा dvb_frontend *zl10039_attach(काष्ठा dvb_frontend *fe,
					u8 i2c_addr,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *zl10039_attach(काष्ठा dvb_frontend *fe,
					u8 i2c_addr,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_ZL10039 */

#पूर्ण_अगर /* ZL10039_H */
