<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Fitiघातer FC0013 tuner driver
 *
 * Copyright (C) 2012 Hans-Frieder Vogt <hfvogt@gmx.net>
 */

#अगर_अघोषित _FC0013_H_
#घोषणा _FC0013_H_

#समावेश <media/dvb_frontend.h>
#समावेश "fc001x-common.h"

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_FC0013)
बाह्य काष्ठा dvb_frontend *fc0013_attach(काष्ठा dvb_frontend *fe,
					काष्ठा i2c_adapter *i2c,
					u8 i2c_address, पूर्णांक dual_master,
					क्रमागत fc001x_xtal_freq xtal_freq);
बाह्य पूर्णांक fc0013_rc_cal_add(काष्ठा dvb_frontend *fe, पूर्णांक rc_val);
बाह्य पूर्णांक fc0013_rc_cal_reset(काष्ठा dvb_frontend *fe);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *fc0013_attach(काष्ठा dvb_frontend *fe,
					काष्ठा i2c_adapter *i2c,
					u8 i2c_address, पूर्णांक dual_master,
					क्रमागत fc001x_xtal_freq xtal_freq)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक fc0013_rc_cal_add(काष्ठा dvb_frontend *fe, पूर्णांक rc_val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fc0013_rc_cal_reset(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
