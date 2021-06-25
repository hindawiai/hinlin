<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Panasonic MN88473 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित MN88473_PRIV_H
#घोषणा MN88473_PRIV_H

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "mn88473.h"
#समावेश <linux/math64.h>
#समावेश <linux/firmware.h>
#समावेश <linux/regmap.h>

#घोषणा MN88473_FIRMWARE "dvb-demod-mn88473-01.fw"

काष्ठा mn88473_dev अणु
	काष्ठा i2c_client *client[3];
	काष्ठा regmap *regmap[3];
	काष्ठा dvb_frontend frontend;
	u16 i2c_wr_max;
	bool active;
	u32 clk;
पूर्ण;

#पूर्ण_अगर
