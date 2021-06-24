<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Fujitsu MB86A16 DVB-S/DSS DC Receiver driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MB86A16_H
#घोषणा __MB86A16_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>


काष्ठा mb86a16_config अणु
	u8 demod_address;

	पूर्णांक (*set_voltage)(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_voltage voltage);
पूर्ण;



#अगर IS_REACHABLE(CONFIG_DVB_MB86A16)

बाह्य काष्ठा dvb_frontend *mb86a16_attach(स्थिर काष्ठा mb86a16_config *config,
					   काष्ठा i2c_adapter *i2c_adap);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *mb86a16_attach(स्थिर काष्ठा mb86a16_config *config,
					   काष्ठा i2c_adapter *i2c_adap)
अणु
	prपूर्णांकk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_MB86A16 */

#पूर्ण_अगर /* __MB86A16_H */
