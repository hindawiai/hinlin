<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Conexant cx24117/cx24132 - Dual DVBS/S2 Satellite demod/tuner driver

    Copyright (C) 2013 Luis Alves <ljalvs@gmail.com>
	(based on cx24116.h by Steven Toth)

*/

#अगर_अघोषित CX24117_H
#घोषणा CX24117_H

#समावेश <linux/dvb/frontend.h>

काष्ठा cx24117_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CX24117)
बाह्य काष्ठा dvb_frontend *cx24117_attach(
	स्थिर काष्ठा cx24117_config *config,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cx24117_attach(
	स्थिर काष्ठा cx24117_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	dev_warn(&i2c->dev, "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CX24117_H */
