<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
*/

#अगर_अघोषित __TDA8290_H__
#घोषणा __TDA8290_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>
#समावेश "tda18271.h"

क्रमागत tda8290_lna अणु
	TDA8290_LNA_OFF = 0,
	TDA8290_LNA_GP0_HIGH_ON = 1,
	TDA8290_LNA_GP0_HIGH_OFF = 2,
	TDA8290_LNA_ON_BRIDGE = 3,
पूर्ण;

काष्ठा tda829x_config अणु
	क्रमागत tda8290_lna lna_cfg;

	अचिन्हित पूर्णांक probe_tuner:1;
#घोषणा TDA829X_PROBE_TUNER 0
#घोषणा TDA829X_DONT_PROBE  1
	अचिन्हित पूर्णांक no_i2c_gate:1;
	काष्ठा tda18271_std_map *tda18271_std_map;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_TDA8290)
बाह्य पूर्णांक tda829x_probe(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr);

बाह्य काष्ठा dvb_frontend *tda829x_attach(काष्ठा dvb_frontend *fe,
					   काष्ठा i2c_adapter *i2c_adap,
					   u8 i2c_addr,
					   काष्ठा tda829x_config *cfg);
#अन्यथा
अटल अंतरभूत पूर्णांक tda829x_probe(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा dvb_frontend *tda829x_attach(काष्ठा dvb_frontend *fe,
						  काष्ठा i2c_adapter *i2c_adap,
						  u8 i2c_addr,
						  काष्ठा tda829x_config *cfg)
अणु
	prपूर्णांकk(KERN_INFO "%s: not probed - driver disabled by Kconfig\n",
	       __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __TDA8290_H__ */
