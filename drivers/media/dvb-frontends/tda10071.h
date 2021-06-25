<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA10071 + Conexant CX24118A DVB-S/S2 demodulator + tuner driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TDA10071_H
#घोषणा TDA10071_H

#समावेश <linux/dvb/frontend.h>

/*
 * I2C address
 * 0x05, 0x55,
 */

/**
 * काष्ठा tda10071_platक्रमm_data - Platक्रमm data क्रम the tda10071 driver
 * @clk: Clock frequency.
 * @i2c_wr_max: Max bytes I2C adapter can ग_लिखो at once.
 * @ts_mode: TS mode.
 * @spec_inv: Input spectrum inversion.
 * @pll_multiplier: PLL multiplier.
 * @tuner_i2c_addr: CX24118A tuner I2C address (0x14, 0x54, ...).
 * @get_dvb_frontend: Get DVB frontend.
 */
काष्ठा tda10071_platक्रमm_data अणु
	u32 clk;
	u16 i2c_wr_max;
#घोषणा TDA10071_TS_SERIAL        0
#घोषणा TDA10071_TS_PARALLEL      1
	u8 ts_mode;
	bool spec_inv;
	u8 pll_multiplier;
	u8 tuner_i2c_addr;

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
पूर्ण;

#पूर्ण_अगर /* TDA10071_H */
