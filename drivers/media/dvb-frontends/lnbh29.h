<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम LNB supply and control IC STMicroelectronics LNBH29
 *
 * Copyright (c) 2018 Socionext Inc.
 */

#अगर_अघोषित LNBH29_H
#घोषणा LNBH29_H

#समावेश <linux/i2c.h>
#समावेश <linux/dvb/frontend.h>

/* Using very low E.S.R. capacitors or ceramic caps */
#घोषणा LNBH29_DATA_COMP    BIT(3)

काष्ठा lnbh29_config अणु
	u8 i2c_address;
	u8 data_config;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LNBH29)
काष्ठा dvb_frontend *lnbh29_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा lnbh29_config *cfg,
				   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *lnbh29_attach(काष्ठा dvb_frontend *fe,
						 काष्ठा lnbh29_config *cfg,
						 काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
