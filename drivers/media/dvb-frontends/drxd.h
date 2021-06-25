<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drxd.h: DRXD DVB-T demodulator driver
 *
 * Copyright (C) 2005-2007 Micronas
 */

#अगर_अघोषित _DRXD_H_
#घोषणा _DRXD_H_

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

काष्ठा drxd_config अणु
	u8 index;

	u8 pll_address;
	u8 pll_type;
#घोषणा DRXD_PLL_NONE     0
#घोषणा DRXD_PLL_DTT7520X 1
#घोषणा DRXD_PLL_MT3X0823 2

	u32 घड़ी;
	u8 insert_rs_byte;

	u8 demod_address;
	u8 demoda_address;
	u8 demod_revision;

	/* If the tuner is not behind an i2c gate, be sure to flip this bit
	   or अन्यथा the i2c bus could get wedged */
	u8 disable_i2c_gate_ctrl;

	u32 IF;
	 s16(*osc_deviation) (व्योम *priv, s16 dev, पूर्णांक flag);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DRXD)
बाह्य
काष्ठा dvb_frontend *drxd_attach(स्थिर काष्ठा drxd_config *config,
				 व्योम *priv, काष्ठा i2c_adapter *i2c,
				 काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *drxd_attach(स्थिर काष्ठा drxd_config *config,
				 व्योम *priv, काष्ठा i2c_adapter *i2c,
				 काष्ठा device *dev)
अणु
	prपूर्णांकk(KERN_INFO "%s: not probed - driver disabled by Kconfig\n",
	       __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
