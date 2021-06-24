<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Intersil ISL6423 SEC and LNB Power supply controller

	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

*/

#अगर_अघोषित __ISL_6423_H
#घोषणा __ISL_6423_H

#समावेश <linux/dvb/frontend.h>

क्रमागत isl6423_current अणु
	SEC_CURRENT_275m = 0,
	SEC_CURRENT_515m,
	SEC_CURRENT_635m,
	SEC_CURRENT_800m,
पूर्ण;

क्रमागत isl6423_curlim अणु
	SEC_CURRENT_LIM_ON = 1,
	SEC_CURRENT_LIM_OFF
पूर्ण;

काष्ठा isl6423_config अणु
	क्रमागत isl6423_current current_max;
	क्रमागत isl6423_curlim curlim;
	u8 addr;
	u8 mod_बाह्य;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_ISL6423)


बाह्य काष्ठा dvb_frontend *isl6423_attach(काष्ठा dvb_frontend *fe,
					   काष्ठा i2c_adapter *i2c,
					   स्थिर काष्ठा isl6423_config *config);

#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *isl6423_attach(काष्ठा dvb_frontend *fe,
						  काष्ठा i2c_adapter *i2c,
						  स्थिर काष्ठा isl6423_config *config)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_ISL6423 */

#पूर्ण_अगर /* __ISL_6423_H */
