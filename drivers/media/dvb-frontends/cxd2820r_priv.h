<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Sony CXD2820R demodulator driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */


#अगर_अघोषित CXD2820R_PRIV_H
#घोषणा CXD2820R_PRIV_H

#समावेश <linux/dvb/version.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "cxd2820r.h"
#समावेश <linux/gpपन.स>
#समावेश <linux/math64.h>
#समावेश <linux/regmap.h>

काष्ठा reg_val_mask अणु
	u32 reg;
	u8  val;
	u8  mask;
पूर्ण;

#घोषणा CXD2820R_CLK 41000000

काष्ठा cxd2820r_priv अणु
	काष्ठा i2c_client *client[2];
	काष्ठा regmap *regmap[2];
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend fe;
	u8 ts_mode;
	bool ts_clk_inv;
	bool अगर_agc_polarity;
	bool spec_inv;

	u64 post_bit_error_prev_dvbv3;
	u64 post_bit_error;

	bool ber_running;

#घोषणा GPIO_COUNT 3
	u8 gpio[GPIO_COUNT];
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर

	क्रमागत fe_delivery_प्रणाली delivery_प्रणाली;
	bool last_tune_failed; /* क्रम चयन between T and T2 tune */
पूर्ण;

/* cxd2820r_core.c */

बाह्य पूर्णांक cxd2820r_debug;

पूर्णांक cxd2820r_gpio(काष्ठा dvb_frontend *fe, u8 *gpio);

पूर्णांक cxd2820r_wr_reg_val_mask_tab(काष्ठा cxd2820r_priv *priv,
				 स्थिर काष्ठा reg_val_mask *tab, पूर्णांक tab_len);

पूर्णांक cxd2820r_wr_reg_mask(काष्ठा cxd2820r_priv *priv, u32 reg, u8 val,
	u8 mask);

पूर्णांक cxd2820r_wr_regs(काष्ठा cxd2820r_priv *priv, u32 reginfo, u8 *val,
	पूर्णांक len);

पूर्णांक cxd2820r_wr_regs(काष्ठा cxd2820r_priv *priv, u32 reginfo, u8 *val,
	पूर्णांक len);

पूर्णांक cxd2820r_rd_regs(काष्ठा cxd2820r_priv *priv, u32 reginfo, u8 *val,
	पूर्णांक len);

पूर्णांक cxd2820r_wr_reg(काष्ठा cxd2820r_priv *priv, u32 reg, u8 val);

पूर्णांक cxd2820r_rd_reg(काष्ठा cxd2820r_priv *priv, u32 reg, u8 *val);

/* cxd2820r_c.c */

पूर्णांक cxd2820r_get_frontend_c(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *p);

पूर्णांक cxd2820r_set_frontend_c(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_पढ़ो_status_c(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);

पूर्णांक cxd2820r_init_c(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_sleep_c(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_get_tune_settings_c(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s);

/* cxd2820r_t.c */

पूर्णांक cxd2820r_get_frontend_t(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *p);

पूर्णांक cxd2820r_set_frontend_t(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_पढ़ो_status_t(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);

पूर्णांक cxd2820r_init_t(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_sleep_t(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_get_tune_settings_t(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s);

/* cxd2820r_t2.c */

पूर्णांक cxd2820r_get_frontend_t2(काष्ठा dvb_frontend *fe,
			     काष्ठा dtv_frontend_properties *p);

पूर्णांक cxd2820r_set_frontend_t2(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_पढ़ो_status_t2(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status);

पूर्णांक cxd2820r_init_t2(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_sleep_t2(काष्ठा dvb_frontend *fe);

पूर्णांक cxd2820r_get_tune_settings_t2(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s);

#पूर्ण_अगर /* CXD2820R_PRIV_H */
