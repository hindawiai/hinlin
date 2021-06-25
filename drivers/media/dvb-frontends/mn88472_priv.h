<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Panasonic MN88472 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित MN88472_PRIV_H
#घोषणा MN88472_PRIV_H

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "mn88472.h"
#समावेश <linux/firmware.h>
#समावेश <linux/regmap.h>

#घोषणा MN88472_FIRMWARE "dvb-demod-mn88472-02.fw"

काष्ठा mn88472_dev अणु
	काष्ठा i2c_client *client[3];
	काष्ठा regmap *regmap[3];
	काष्ठा dvb_frontend fe;
	u16 i2c_ग_लिखो_max;
	अचिन्हित पूर्णांक clk;
	अचिन्हित पूर्णांक active:1;
	अचिन्हित पूर्णांक ts_mode:1;
	अचिन्हित पूर्णांक ts_clk:1;
पूर्ण;

#पूर्ण_अगर
