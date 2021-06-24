<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	TDA665x tuner driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __TDA665x_H
#घोषणा __TDA665x_H

काष्ठा tda665x_config अणु
	अक्षर name[128];

	u8	addr;
	u32	frequency_min;
	u32	frequency_max;
	u32	frequency_offst;
	u32	ref_multiplier;
	u32	ref_भागider;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA665x)

बाह्य काष्ठा dvb_frontend *tda665x_attach(काष्ठा dvb_frontend *fe,
					   स्थिर काष्ठा tda665x_config *config,
					   काष्ठा i2c_adapter *i2c);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *tda665x_attach(काष्ठा dvb_frontend *fe,
						  स्थिर काष्ठा tda665x_config *config,
						  काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_TDA665x */

#पूर्ण_अगर /* __TDA665x_H */
