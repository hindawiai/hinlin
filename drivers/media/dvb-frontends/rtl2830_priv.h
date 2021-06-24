<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Realtek RTL2830 DVB-T demodulator driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित RTL2830_PRIV_H
#घोषणा RTL2830_PRIV_H

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "rtl2830.h"
#समावेश <linux/i2c-mux.h>
#समावेश <linux/math64.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>

काष्ठा rtl2830_dev अणु
	काष्ठा rtl2830_platक्रमm_data *pdata;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा dvb_frontend fe;
	bool sleeping;
	अचिन्हित दीर्घ filters;
	क्रमागत fe_status fe_status;
	u64 post_bit_error_prev; /* क्रम old DVBv3 पढ़ो_ber() calculation */
	u64 post_bit_error;
	u64 post_bit_count;
पूर्ण;

काष्ठा rtl2830_reg_val_mask अणु
	u16 reg;
	u8  val;
	u8  mask;
पूर्ण;

#पूर्ण_अगर /* RTL2830_PRIV_H */
