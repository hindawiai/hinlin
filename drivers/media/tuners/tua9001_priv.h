<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Infineon TUA9001 silicon tuner driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TUA9001_PRIV_H
#घोषणा TUA9001_PRIV_H

#समावेश "tua9001.h"
#समावेश <linux/math64.h>
#समावेश <linux/regmap.h>

काष्ठा tua9001_reg_val अणु
	u8 reg;
	u16 val;
पूर्ण;

काष्ठा tua9001_dev अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
पूर्ण;

#पूर्ण_अगर
