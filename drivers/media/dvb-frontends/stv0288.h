<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Driver क्रम ST STV0288 demodulator

	Copyright (C) 2006 Georg Acher, BayCom GmbH, acher (at) baycom (करोt) de
		क्रम Reel Mulसमयdia
	Copyright (C) 2008 TurboSight.com, <bob@turbosight.com>
	Copyright (C) 2008 Igor M. Liplianin <liplianin@me.by>
		Removed stb6000 specअगरic tuner code and revised some
		procedures.


*/

#अगर_अघोषित STV0288_H
#घोषणा STV0288_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

काष्ठा stv0288_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	u8* inittab;

	/* minimum delay beक्रमe retuning */
	पूर्णांक min_delay_ms;

	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV0288)
बाह्य काष्ठा dvb_frontend *stv0288_attach(स्थिर काष्ठा stv0288_config *config,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *stv0288_attach(स्थिर काष्ठा stv0288_config *config,
					   काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_STV0288 */

अटल अंतरभूत पूर्णांक stv0288_ग_लिखोreg(काष्ठा dvb_frontend *fe, u8 reg, u8 val)
अणु
	पूर्णांक r = 0;
	u8 buf[] = अणु reg, val पूर्ण;
	अगर (fe->ops.ग_लिखो)
		r = fe->ops.ग_लिखो(fe, buf, 2);
	वापस r;
पूर्ण

#पूर्ण_अगर /* STV0288_H */
