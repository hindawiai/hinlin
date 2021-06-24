<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sony CXD2820R demodulator driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */


#समावेश "cxd2820r_priv.h"

/* Write रेजिस्टर table */
पूर्णांक cxd2820r_wr_reg_val_mask_tab(काष्ठा cxd2820r_priv *priv,
				 स्थिर काष्ठा reg_val_mask *tab, पूर्णांक tab_len)
अणु
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, reg, mask, val;
	काष्ठा regmap *regmap;

	dev_dbg(&client->dev, "tab_len=%d\n", tab_len);

	क्रम (i = 0; i < tab_len; i++) अणु
		अगर ((tab[i].reg >> 16) & 0x1)
			regmap = priv->regmap[1];
		अन्यथा
			regmap = priv->regmap[0];

		reg = (tab[i].reg >> 0) & 0xffff;
		val = tab[i].val;
		mask = tab[i].mask;

		अगर (mask == 0xff)
			ret = regmap_ग_लिखो(regmap, reg, val);
		अन्यथा
			ret = regmap_ग_लिखो_bits(regmap, reg, mask, val);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_gpio(काष्ठा dvb_frontend *fe, u8 *gpio)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	u8 पंचांगp0, पंचांगp1;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	/* update GPIOs only when needed */
	अगर (!स_भेद(gpio, priv->gpio, माप(priv->gpio)))
		वापस 0;

	पंचांगp0 = 0x00;
	पंचांगp1 = 0x00;
	क्रम (i = 0; i < माप(priv->gpio); i++) अणु
		/* enable / disable */
		अगर (gpio[i] & CXD2820R_GPIO_E)
			पंचांगp0 |= (2 << 6) >> (2 * i);
		अन्यथा
			पंचांगp0 |= (1 << 6) >> (2 * i);

		/* input / output */
		अगर (gpio[i] & CXD2820R_GPIO_I)
			पंचांगp1 |= (1 << (3 + i));
		अन्यथा
			पंचांगp1 |= (0 << (3 + i));

		/* high / low */
		अगर (gpio[i] & CXD2820R_GPIO_H)
			पंचांगp1 |= (1 << (0 + i));
		अन्यथा
			पंचांगp1 |= (0 << (0 + i));

		dev_dbg(&client->dev, "gpio i=%d %02x %02x\n", i, पंचांगp0, पंचांगp1);
	पूर्ण

	dev_dbg(&client->dev, "wr gpio=%02x %02x\n", पंचांगp0, पंचांगp1);

	/* ग_लिखो bits [7:2] */
	ret = regmap_update_bits(priv->regmap[0], 0x0089, 0xfc, पंचांगp0);
	अगर (ret)
		जाओ error;

	/* ग_लिखो bits [5:0] */
	ret = regmap_update_bits(priv->regmap[0], 0x008e, 0x3f, पंचांगp1);
	अगर (ret)
		जाओ error;

	स_नकल(priv->gpio, gpio, माप(priv->gpio));

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2820r_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = cxd2820r_init_t(fe);
		अगर (ret < 0)
			जाओ err;
		ret = cxd2820r_set_frontend_t(fe);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2820r_init_t(fe);
		अगर (ret < 0)
			जाओ err;
		ret = cxd2820r_set_frontend_t2(fe);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = cxd2820r_init_c(fe);
		अगर (ret < 0)
			जाओ err;
		ret = cxd2820r_set_frontend_c(fe);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid delivery_system\n");
		ret = -EINVAL;
		अवरोध;
	पूर्ण
err:
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2820r_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = cxd2820r_पढ़ो_status_t(fe, status);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2820r_पढ़ो_status_t2(fe, status);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = cxd2820r_पढ़ो_status_c(fe, status);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2820r_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	अगर (priv->delivery_प्रणाली == SYS_UNDEFINED)
		वापस 0;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = cxd2820r_get_frontend_t(fe, p);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2820r_get_frontend_t2(fe, p);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = cxd2820r_get_frontend_c(fe, p);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2820r_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	*ber = (priv->post_bit_error - priv->post_bit_error_prev_dvbv3);
	priv->post_bit_error_prev_dvbv3 = priv->post_bit_error;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2820r_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	अगर (c->strength.stat[0].scale == FE_SCALE_RELATIVE)
		*strength = c->strength.stat[0].uvalue;
	अन्यथा
		*strength = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2820r_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
	अन्यथा
		*snr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2820r_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	*ucblocks = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cxd2820r_init(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cxd2820r_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = cxd2820r_sleep_t(fe);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2820r_sleep_t2(fe);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = cxd2820r_sleep_c(fe);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2820r_get_tune_settings(काष्ठा dvb_frontend *fe,
				      काष्ठा dvb_frontend_tune_settings *s)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = cxd2820r_get_tune_settings_t(fe, s);
		अवरोध;
	हाल SYS_DVBT2:
		ret = cxd2820r_get_tune_settings_t2(fe, s);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = cxd2820r_get_tune_settings_c(fe, s);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत dvbfe_search cxd2820r_search(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	क्रमागत fe_status status = 0;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_प्रणाली);

	/* चयन between DVB-T and DVB-T2 when tune fails */
	अगर (priv->last_tune_failed) अणु
		अगर (priv->delivery_प्रणाली == SYS_DVBT) अणु
			ret = cxd2820r_sleep_t(fe);
			अगर (ret)
				जाओ error;

			c->delivery_प्रणाली = SYS_DVBT2;
		पूर्ण अन्यथा अगर (priv->delivery_प्रणाली == SYS_DVBT2) अणु
			ret = cxd2820r_sleep_t2(fe);
			अगर (ret)
				जाओ error;

			c->delivery_प्रणाली = SYS_DVBT;
		पूर्ण
	पूर्ण

	/* set frontend */
	ret = cxd2820r_set_frontend(fe);
	अगर (ret)
		जाओ error;

	/* frontend lock रुको loop count */
	चयन (priv->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBC_ANNEX_A:
		i = 20;
		अवरोध;
	हाल SYS_DVBT2:
		i = 40;
		अवरोध;
	हाल SYS_UNDEFINED:
	शेष:
		i = 0;
		अवरोध;
	पूर्ण

	/* रुको frontend lock */
	क्रम (; i > 0; i--) अणु
		dev_dbg(&client->dev, "loop=%d\n", i);
		msleep(50);
		ret = cxd2820r_पढ़ो_status(fe, &status);
		अगर (ret)
			जाओ error;

		अगर (status & FE_HAS_LOCK)
			अवरोध;
	पूर्ण

	/* check अगर we have a valid संकेत */
	अगर (status & FE_HAS_LOCK) अणु
		priv->last_tune_failed = false;
		वापस DVBFE_ALGO_SEARCH_SUCCESS;
	पूर्ण अन्यथा अणु
		priv->last_tune_failed = true;
		वापस DVBFE_ALGO_SEARCH_AGAIN;
	पूर्ण

error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस DVBFE_ALGO_SEARCH_ERROR;
पूर्ण

अटल क्रमागत dvbfe_algo cxd2820r_get_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_CUSTOM;
पूर्ण

अटल व्योम cxd2820r_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];

	dev_dbg(&client->dev, "\n");

	i2c_unरेजिस्टर_device(client);

	वापस;
पूर्ण

अटल पूर्णांक cxd2820r_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];

	dev_dbg_ratelimited(&client->dev, "enable=%d\n", enable);

	वापस regmap_update_bits(priv->regmap[0], 0x00db, 0x01, enable ? 1 : 0);
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक cxd2820r_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित nr,
		पूर्णांक val)
अणु
	काष्ठा cxd2820r_priv *priv = gpiochip_get_data(chip);
	काष्ठा i2c_client *client = priv->client[0];
	u8 gpio[GPIO_COUNT];

	dev_dbg(&client->dev, "nr=%u val=%d\n", nr, val);

	स_नकल(gpio, priv->gpio, माप(gpio));
	gpio[nr] = CXD2820R_GPIO_E | CXD2820R_GPIO_O | (val << 2);

	वापस cxd2820r_gpio(&priv->fe, gpio);
पूर्ण

अटल व्योम cxd2820r_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित nr, पूर्णांक val)
अणु
	काष्ठा cxd2820r_priv *priv = gpiochip_get_data(chip);
	काष्ठा i2c_client *client = priv->client[0];
	u8 gpio[GPIO_COUNT];

	dev_dbg(&client->dev, "nr=%u val=%d\n", nr, val);

	स_नकल(gpio, priv->gpio, माप(gpio));
	gpio[nr] = CXD2820R_GPIO_E | CXD2820R_GPIO_O | (val << 2);

	(व्योम) cxd2820r_gpio(&priv->fe, gpio);

	वापस;
पूर्ण

अटल पूर्णांक cxd2820r_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित nr)
अणु
	काष्ठा cxd2820r_priv *priv = gpiochip_get_data(chip);
	काष्ठा i2c_client *client = priv->client[0];

	dev_dbg(&client->dev, "nr=%u\n", nr);

	वापस (priv->gpio[nr] >> 2) & 0x01;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dvb_frontend_ops cxd2820r_ops = अणु
	.delsys = अणु SYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_A पूर्ण,
	/* शेष: DVB-T/T2 */
	.info = अणु
		.name = "Sony CXD2820R",

		.caps =	FE_CAN_FEC_1_2			|
			FE_CAN_FEC_2_3			|
			FE_CAN_FEC_3_4			|
			FE_CAN_FEC_5_6			|
			FE_CAN_FEC_7_8			|
			FE_CAN_FEC_AUTO			|
			FE_CAN_QPSK			|
			FE_CAN_QAM_16			|
			FE_CAN_QAM_32			|
			FE_CAN_QAM_64			|
			FE_CAN_QAM_128			|
			FE_CAN_QAM_256			|
			FE_CAN_QAM_AUTO			|
			FE_CAN_TRANSMISSION_MODE_AUTO	|
			FE_CAN_GUARD_INTERVAL_AUTO	|
			FE_CAN_HIERARCHY_AUTO		|
			FE_CAN_MUTE_TS			|
			FE_CAN_2G_MODULATION		|
			FE_CAN_MULTISTREAM
		पूर्ण,

	.release		= cxd2820r_release,
	.init			= cxd2820r_init,
	.sleep			= cxd2820r_sleep,

	.get_tune_settings	= cxd2820r_get_tune_settings,
	.i2c_gate_ctrl		= cxd2820r_i2c_gate_ctrl,

	.get_frontend		= cxd2820r_get_frontend,

	.get_frontend_algo	= cxd2820r_get_frontend_algo,
	.search			= cxd2820r_search,

	.पढ़ो_status		= cxd2820r_पढ़ो_status,
	.पढ़ो_snr		= cxd2820r_पढ़ो_snr,
	.पढ़ो_ber		= cxd2820r_पढ़ो_ber,
	.पढ़ो_ucblocks		= cxd2820r_पढ़ो_ucblocks,
	.पढ़ो_संकेत_strength	= cxd2820r_पढ़ो_संकेत_strength,
पूर्ण;

/*
 * XXX: That is wrapper to cxd2820r_probe() via driver core in order to provide
 * proper I2C client क्रम legacy media attach binding.
 * New users must use I2C client binding directly!
 */
काष्ठा dvb_frontend *cxd2820r_attach(स्थिर काष्ठा cxd2820r_config *config,
				     काष्ठा i2c_adapter *adapter,
				     पूर्णांक *gpio_chip_base)
अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info;
	काष्ठा cxd2820r_platक्रमm_data pdata;

	pdata.ts_mode = config->ts_mode;
	pdata.ts_clk_inv = config->ts_घड़ी_inv;
	pdata.अगर_agc_polarity = config->अगर_agc_polarity;
	pdata.spec_inv = config->spec_inv;
	pdata.gpio_chip_base = &gpio_chip_base;
	pdata.attach_in_use = true;

	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "cxd2820r", I2C_NAME_SIZE);
	board_info.addr = config->i2c_address;
	board_info.platक्रमm_data = &pdata;
	client = i2c_new_client_device(adapter, &board_info);
	अगर (!i2c_client_has_driver(client))
		वापस शून्य;

	वापस pdata.get_dvb_frontend(client);
पूर्ण
EXPORT_SYMBOL(cxd2820r_attach);

अटल काष्ठा dvb_frontend *cxd2820r_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा cxd2820r_priv *priv = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &priv->fe;
पूर्ण

अटल पूर्णांक cxd2820r_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cxd2820r_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा cxd2820r_priv *priv;
	पूर्णांक ret, *gpio_chip_base;
	अचिन्हित पूर्णांक uपंचांगp;
	अटल स्थिर काष्ठा regmap_range_cfg regmap_range_cfg0[] = अणु
		अणु
			.range_min        = 0x0000,
			.range_max        = 0x3fff,
			.selector_reg     = 0x00,
			.selector_mask    = 0xff,
			.selector_shअगरt   = 0,
			.winकरोw_start     = 0x00,
			.winकरोw_len       = 0x100,
		पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_range_cfg regmap_range_cfg1[] = अणु
		अणु
			.range_min        = 0x0000,
			.range_max        = 0x01ff,
			.selector_reg     = 0x00,
			.selector_mask    = 0xff,
			.selector_shअगरt   = 0,
			.winकरोw_start     = 0x00,
			.winकरोw_len       = 0x100,
		पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_config regmap_config0 = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x3fff,
		.ranges = regmap_range_cfg0,
		.num_ranges = ARRAY_SIZE(regmap_range_cfg0),
		.cache_type = REGCACHE_NONE,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_config regmap_config1 = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x01ff,
		.ranges = regmap_range_cfg1,
		.num_ranges = ARRAY_SIZE(regmap_range_cfg1),
		.cache_type = REGCACHE_NONE,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	priv->client[0] = client;
	priv->fe.demodulator_priv = priv;
	priv->i2c = client->adapter;
	priv->ts_mode = pdata->ts_mode;
	priv->ts_clk_inv = pdata->ts_clk_inv;
	priv->अगर_agc_polarity = pdata->अगर_agc_polarity;
	priv->spec_inv = pdata->spec_inv;
	gpio_chip_base = *pdata->gpio_chip_base;
	priv->regmap[0] = regmap_init_i2c(priv->client[0], &regmap_config0);
	अगर (IS_ERR(priv->regmap[0])) अणु
		ret = PTR_ERR(priv->regmap[0]);
		जाओ err_kमुक्त;
	पूर्ण

	/* Check demod answers with correct chip id */
	ret = regmap_पढ़ो(priv->regmap[0], 0x00fd, &uपंचांगp);
	अगर (ret)
		जाओ err_regmap_0_regmap_निकास;

	dev_dbg(&client->dev, "chip_id=%02x\n", uपंचांगp);

	अगर (uपंचांगp != 0xe1) अणु
		ret = -ENODEV;
		जाओ err_regmap_0_regmap_निकास;
	पूर्ण

	/*
	 * Chip has two I2C addresses क्रम dअगरferent रेजिस्टर banks. We रेजिस्टर
	 * one dummy I2C client in in order to get own I2C client क्रम each
	 * रेजिस्टर bank.
	 */
	priv->client[1] = i2c_new_dummy_device(client->adapter, client->addr | (1 << 1));
	अगर (IS_ERR(priv->client[1])) अणु
		ret = PTR_ERR(priv->client[1]);
		dev_err(&client->dev, "I2C registration failed\n");
		जाओ err_regmap_0_regmap_निकास;
	पूर्ण

	priv->regmap[1] = regmap_init_i2c(priv->client[1], &regmap_config1);
	अगर (IS_ERR(priv->regmap[1])) अणु
		ret = PTR_ERR(priv->regmap[1]);
		जाओ err_client_1_i2c_unरेजिस्टर_device;
	पूर्ण

	अगर (gpio_chip_base) अणु
#अगर_घोषित CONFIG_GPIOLIB
		/* Add GPIOs */
		priv->gpio_chip.label = KBUILD_MODNAME;
		priv->gpio_chip.parent = &client->dev;
		priv->gpio_chip.owner = THIS_MODULE;
		priv->gpio_chip.direction_output = cxd2820r_gpio_direction_output;
		priv->gpio_chip.set = cxd2820r_gpio_set;
		priv->gpio_chip.get = cxd2820r_gpio_get;
		priv->gpio_chip.base = -1; /* Dynamic allocation */
		priv->gpio_chip.ngpio = GPIO_COUNT;
		priv->gpio_chip.can_sleep = 1;
		ret = gpiochip_add_data(&priv->gpio_chip, priv);
		अगर (ret)
			जाओ err_regmap_1_regmap_निकास;

		dev_dbg(&client->dev, "gpio_chip.base=%d\n",
			priv->gpio_chip.base);

		*gpio_chip_base = priv->gpio_chip.base;
#अन्यथा
		/*
		 * Use अटल GPIO configuration अगर GPIOLIB is undefined.
		 * This is fallback condition.
		 */
		u8 gpio[GPIO_COUNT];
		gpio[0] = (*gpio_chip_base >> 0) & 0x07;
		gpio[1] = (*gpio_chip_base >> 3) & 0x07;
		gpio[2] = 0;
		ret = cxd2820r_gpio(&priv->fe, gpio);
		अगर (ret)
			जाओ err_regmap_1_regmap_निकास;
#पूर्ण_अगर
	पूर्ण

	/* Create dvb frontend */
	स_नकल(&priv->fe.ops, &cxd2820r_ops, माप(priv->fe.ops));
	अगर (!pdata->attach_in_use)
		priv->fe.ops.release = शून्य;
	i2c_set_clientdata(client, priv);

	/* Setup callbacks */
	pdata->get_dvb_frontend = cxd2820r_get_dvb_frontend;

	dev_info(&client->dev, "Sony CXD2820R successfully identified\n");

	वापस 0;
err_regmap_1_regmap_निकास:
	regmap_निकास(priv->regmap[1]);
err_client_1_i2c_unरेजिस्टर_device:
	i2c_unरेजिस्टर_device(priv->client[1]);
err_regmap_0_regmap_निकास:
	regmap_निकास(priv->regmap[0]);
err_kमुक्त:
	kमुक्त(priv);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cxd2820r_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cxd2820r_priv *priv = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

#अगर_घोषित CONFIG_GPIOLIB
	अगर (priv->gpio_chip.label)
		gpiochip_हटाओ(&priv->gpio_chip);
#पूर्ण_अगर
	regmap_निकास(priv->regmap[1]);
	i2c_unरेजिस्टर_device(priv->client[1]);

	regmap_निकास(priv->regmap[0]);

	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cxd2820r_id_table[] = अणु
	अणु"cxd2820r", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cxd2820r_id_table);

अटल काष्ठा i2c_driver cxd2820r_driver = अणु
	.driver = अणु
		.name                = "cxd2820r",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe    = cxd2820r_probe,
	.हटाओ   = cxd2820r_हटाओ,
	.id_table = cxd2820r_id_table,
पूर्ण;

module_i2c_driver(cxd2820r_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Sony CXD2820R demodulator driver");
MODULE_LICENSE("GPL");
