<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Afatech AF9033 demodulator driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#समावेश "af9033_priv.h"

काष्ठा af9033_dev अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा dvb_frontend fe;
	काष्ठा af9033_config cfg;
	bool is_af9035;
	bool is_it9135;

	u32 bandwidth_hz;
	bool ts_mode_parallel;
	bool ts_mode_serial;

	क्रमागत fe_status fe_status;
	u64 post_bit_error_prev; /* क्रम old पढ़ो_ber we वापस (curr - prev) */
	u64 post_bit_error;
	u64 post_bit_count;
	u64 error_block_count;
	u64 total_block_count;
पूर्ण;

/* Write reg val table using reg addr स्वतः increment */
अटल पूर्णांक af9033_wr_reg_val_tab(काष्ठा af9033_dev *dev,
				 स्थिर काष्ठा reg_val *tab, पूर्णांक tab_len)
अणु
	काष्ठा i2c_client *client = dev->client;
#घोषणा MAX_TAB_LEN 212
	पूर्णांक ret, i, j;
	u8 buf[1 + MAX_TAB_LEN];

	dev_dbg(&client->dev, "tab_len=%d\n", tab_len);

	अगर (tab_len > माप(buf)) अणु
		dev_warn(&client->dev, "tab len %d is too big\n", tab_len);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0, j = 0; i < tab_len; i++) अणु
		buf[j] = tab[i].val;

		अगर (i == tab_len - 1 || tab[i].reg != tab[i + 1].reg - 1) अणु
			ret = regmap_bulk_ग_लिखो(dev->regmap, tab[i].reg - j,
						buf, j + 1);
			अगर (ret)
				जाओ err;

			j = 0;
		पूर्ण अन्यथा अणु
			j++;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i, len;
	अचिन्हित पूर्णांक uपंचांगp;
	स्थिर काष्ठा reg_val *init;
	u8 buf[4];
	काष्ठा reg_val_mask tab[] = अणु
		अणु 0x80fb24, 0x00, 0x08 पूर्ण,
		अणु 0x80004c, 0x00, 0xff पूर्ण,
		अणु 0x00f641, dev->cfg.tuner, 0xff पूर्ण,
		अणु 0x80f5ca, 0x01, 0x01 पूर्ण,
		अणु 0x80f715, 0x01, 0x01 पूर्ण,
		अणु 0x00f41f, 0x04, 0x04 पूर्ण,
		अणु 0x00f41a, 0x01, 0x01 पूर्ण,
		अणु 0x80f731, 0x00, 0x01 पूर्ण,
		अणु 0x00d91e, 0x00, 0x01 पूर्ण,
		अणु 0x00d919, 0x00, 0x01 पूर्ण,
		अणु 0x80f732, 0x00, 0x01 पूर्ण,
		अणु 0x00d91f, 0x00, 0x01 पूर्ण,
		अणु 0x00d91a, 0x00, 0x01 पूर्ण,
		अणु 0x80f730, 0x00, 0x01 पूर्ण,
		अणु 0x80f778, 0x00, 0xff पूर्ण,
		अणु 0x80f73c, 0x01, 0x01 पूर्ण,
		अणु 0x80f776, 0x00, 0x01 पूर्ण,
		अणु 0x00d8fd, 0x01, 0xff पूर्ण,
		अणु 0x00d830, 0x01, 0xff पूर्ण,
		अणु 0x00d831, 0x00, 0xff पूर्ण,
		अणु 0x00d832, 0x00, 0xff पूर्ण,
		अणु 0x80f985, dev->ts_mode_serial, 0x01 पूर्ण,
		अणु 0x80f986, dev->ts_mode_parallel, 0x01 पूर्ण,
		अणु 0x00d827, 0x00, 0xff पूर्ण,
		अणु 0x00d829, 0x00, 0xff पूर्ण,
		अणु 0x800045, dev->cfg.adc_multiplier, 0xff पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	/* Main clk control */
	uपंचांगp = भाग_u64((u64)dev->cfg.घड़ी * 0x80000, 1000000);
	buf[0] = (uपंचांगp >>  0) & 0xff;
	buf[1] = (uपंचांगp >>  8) & 0xff;
	buf[2] = (uपंचांगp >> 16) & 0xff;
	buf[3] = (uपंचांगp >> 24) & 0xff;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x800025, buf, 4);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "clk=%u clk_cw=%08x\n", dev->cfg.घड़ी, uपंचांगp);

	/* ADC clk control */
	क्रम (i = 0; i < ARRAY_SIZE(घड़ी_adc_lut); i++) अणु
		अगर (घड़ी_adc_lut[i].घड़ी == dev->cfg.घड़ी)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(घड़ी_adc_lut)) अणु
		dev_err(&client->dev, "Couldn't find ADC config for clock %d\n",
			dev->cfg.घड़ी);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	uपंचांगp = भाग_u64((u64)घड़ी_adc_lut[i].adc * 0x80000, 1000000);
	buf[0] = (uपंचांगp >>  0) & 0xff;
	buf[1] = (uपंचांगp >>  8) & 0xff;
	buf[2] = (uपंचांगp >> 16) & 0xff;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80f1cd, buf, 3);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "adc=%u adc_cw=%06x\n",
		घड़ी_adc_lut[i].adc, uपंचांगp);

	/* Config रेजिस्टर table */
	क्रम (i = 0; i < ARRAY_SIZE(tab); i++) अणु
		ret = regmap_update_bits(dev->regmap, tab[i].reg, tab[i].mask,
					 tab[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Demod clk output */
	अगर (dev->cfg.dyn0_clk) अणु
		ret = regmap_ग_लिखो(dev->regmap, 0x80fba8, 0x00);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* TS पूर्णांकerface */
	अगर (dev->cfg.ts_mode == AF9033_TS_MODE_USB) अणु
		ret = regmap_update_bits(dev->regmap, 0x80f9a5, 0x01, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(dev->regmap, 0x80f9b5, 0x01, 0x01);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(dev->regmap, 0x80f990, 0x01, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(dev->regmap, 0x80f9b5, 0x01, 0x00);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Demod core settings */
	dev_dbg(&client->dev, "load ofsm settings\n");
	चयन (dev->cfg.tuner) अणु
	हाल AF9033_TUNER_IT9135_38:
	हाल AF9033_TUNER_IT9135_51:
	हाल AF9033_TUNER_IT9135_52:
		len = ARRAY_SIZE(ofsm_init_it9135_v1);
		init = ofsm_init_it9135_v1;
		अवरोध;
	हाल AF9033_TUNER_IT9135_60:
	हाल AF9033_TUNER_IT9135_61:
	हाल AF9033_TUNER_IT9135_62:
		len = ARRAY_SIZE(ofsm_init_it9135_v2);
		init = ofsm_init_it9135_v2;
		अवरोध;
	शेष:
		len = ARRAY_SIZE(ofsm_init);
		init = ofsm_init;
		अवरोध;
	पूर्ण

	ret = af9033_wr_reg_val_tab(dev, init, len);
	अगर (ret)
		जाओ err;

	/* Demod tuner specअगरic settings */
	dev_dbg(&client->dev, "load tuner specific settings\n");
	चयन (dev->cfg.tuner) अणु
	हाल AF9033_TUNER_TUA9001:
		len = ARRAY_SIZE(tuner_init_tua9001);
		init = tuner_init_tua9001;
		अवरोध;
	हाल AF9033_TUNER_FC0011:
		len = ARRAY_SIZE(tuner_init_fc0011);
		init = tuner_init_fc0011;
		अवरोध;
	हाल AF9033_TUNER_MXL5007T:
		len = ARRAY_SIZE(tuner_init_mxl5007t);
		init = tuner_init_mxl5007t;
		अवरोध;
	हाल AF9033_TUNER_TDA18218:
		len = ARRAY_SIZE(tuner_init_tda18218);
		init = tuner_init_tda18218;
		अवरोध;
	हाल AF9033_TUNER_FC2580:
		len = ARRAY_SIZE(tuner_init_fc2580);
		init = tuner_init_fc2580;
		अवरोध;
	हाल AF9033_TUNER_FC0012:
		len = ARRAY_SIZE(tuner_init_fc0012);
		init = tuner_init_fc0012;
		अवरोध;
	हाल AF9033_TUNER_IT9135_38:
		len = ARRAY_SIZE(tuner_init_it9135_38);
		init = tuner_init_it9135_38;
		अवरोध;
	हाल AF9033_TUNER_IT9135_51:
		len = ARRAY_SIZE(tuner_init_it9135_51);
		init = tuner_init_it9135_51;
		अवरोध;
	हाल AF9033_TUNER_IT9135_52:
		len = ARRAY_SIZE(tuner_init_it9135_52);
		init = tuner_init_it9135_52;
		अवरोध;
	हाल AF9033_TUNER_IT9135_60:
		len = ARRAY_SIZE(tuner_init_it9135_60);
		init = tuner_init_it9135_60;
		अवरोध;
	हाल AF9033_TUNER_IT9135_61:
		len = ARRAY_SIZE(tuner_init_it9135_61);
		init = tuner_init_it9135_61;
		अवरोध;
	हाल AF9033_TUNER_IT9135_62:
		len = ARRAY_SIZE(tuner_init_it9135_62);
		init = tuner_init_it9135_62;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "unsupported tuner ID=%d\n",
			dev->cfg.tuner);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = af9033_wr_reg_val_tab(dev, init, len);
	अगर (ret)
		जाओ err;

	अगर (dev->cfg.ts_mode == AF9033_TS_MODE_SERIAL) अणु
		ret = regmap_update_bits(dev->regmap, 0x00d91c, 0x01, 0x01);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(dev->regmap, 0x00d917, 0x01, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(dev->regmap, 0x00d916, 0x01, 0x00);
		अगर (ret)
			जाओ err;
	पूर्ण

	चयन (dev->cfg.tuner) अणु
	हाल AF9033_TUNER_IT9135_60:
	हाल AF9033_TUNER_IT9135_61:
	हाल AF9033_TUNER_IT9135_62:
		ret = regmap_ग_लिखो(dev->regmap, 0x800000, 0x01);
		अगर (ret)
			जाओ err;
	पूर्ण

	dev->bandwidth_hz = 0; /* Force to program all parameters */
	/* Init stats here in order संकेत app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	dev_dbg(&client->dev, "\n");

	ret = regmap_ग_लिखो(dev->regmap, 0x80004c, 0x01);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x800000, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_पढ़ो_poll_समयout(dev->regmap, 0x80004c, uपंचांगp, uपंचांगp == 0,
				       5000, 1000000);
	अगर (ret)
		जाओ err;
	ret = regmap_update_bits(dev->regmap, 0x80fb24, 0x08, 0x08);
	अगर (ret)
		जाओ err;

	/* Prevent current leak by setting TS पूर्णांकerface to parallel mode */
	अगर (dev->cfg.ts_mode == AF9033_TS_MODE_SERIAL) अणु
		/* Enable parallel TS */
		ret = regmap_update_bits(dev->regmap, 0x00d917, 0x01, 0x00);
		अगर (ret)
			जाओ err;
		ret = regmap_update_bits(dev->regmap, 0x00d916, 0x01, 0x01);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_get_tune_settings(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	/* 800 => 2000 because IT9135 v2 is slow to gain lock */
	fesettings->min_delay_ms = 2000;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक af9033_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uपंचांगp, adc_freq;
	u8 पंचांगp, buf[3], bandwidth_reg_val;
	u32 अगर_frequency;

	dev_dbg(&client->dev, "frequency=%u bandwidth_hz=%u\n",
		c->frequency, c->bandwidth_hz);

	/* Check bandwidth */
	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		bandwidth_reg_val = 0x00;
		अवरोध;
	हाल 7000000:
		bandwidth_reg_val = 0x01;
		अवरोध;
	हाल 8000000:
		bandwidth_reg_val = 0x02;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid bandwidth_hz\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* Coefficients */
	अगर (c->bandwidth_hz != dev->bandwidth_hz) अणु
		क्रम (i = 0; i < ARRAY_SIZE(coeff_lut); i++) अणु
			अगर (coeff_lut[i].घड़ी == dev->cfg.घड़ी &&
			    coeff_lut[i].bandwidth_hz == c->bandwidth_hz) अणु
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(coeff_lut)) अणु
			dev_err(&client->dev,
				"Couldn't find config for clock %u\n",
				dev->cfg.घड़ी);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x800001, coeff_lut[i].val,
					माप(coeff_lut[i].val));
		अगर (ret)
			जाओ err;
	पूर्ण

	/* IF frequency control */
	अगर (c->bandwidth_hz != dev->bandwidth_hz) अणु
		क्रम (i = 0; i < ARRAY_SIZE(घड़ी_adc_lut); i++) अणु
			अगर (घड़ी_adc_lut[i].घड़ी == dev->cfg.घड़ी)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(घड़ी_adc_lut)) अणु
			dev_err(&client->dev,
				"Couldn't find ADC clock for clock %u\n",
				dev->cfg.घड़ी);
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		adc_freq = घड़ी_adc_lut[i].adc;

		अगर (dev->cfg.adc_multiplier == AF9033_ADC_MULTIPLIER_2X)
			adc_freq = 2 * adc_freq;

		/* Get used IF frequency */
		अगर (fe->ops.tuner_ops.get_अगर_frequency)
			fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_frequency);
		अन्यथा
			अगर_frequency = 0;

		uपंचांगp = DIV_ROUND_CLOSEST_ULL((u64)अगर_frequency * 0x800000,
					     adc_freq);

		अगर (!dev->cfg.spec_inv && अगर_frequency)
			uपंचांगp = 0x800000 - uपंचांगp;

		buf[0] = (uपंचांगp >>  0) & 0xff;
		buf[1] = (uपंचांगp >>  8) & 0xff;
		buf[2] = (uपंचांगp >> 16) & 0xff;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x800029, buf, 3);
		अगर (ret)
			जाओ err;

		dev_dbg(&client->dev, "if_frequency_cw=%06x\n", uपंचांगp);

		dev->bandwidth_hz = c->bandwidth_hz;
	पूर्ण

	ret = regmap_update_bits(dev->regmap, 0x80f904, 0x03,
				 bandwidth_reg_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x800040, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x800047, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_update_bits(dev->regmap, 0x80f999, 0x01, 0x00);
	अगर (ret)
		जाओ err;

	अगर (c->frequency <= 230000000)
		पंचांगp = 0x00; /* VHF */
	अन्यथा
		पंचांगp = 0x01; /* UHF */

	ret = regmap_ग_लिखो(dev->regmap, 0x80004b, पंचांगp);
	अगर (ret)
		जाओ err;
	/* Reset FSM */
	ret = regmap_ग_लिखो(dev->regmap, 0x800000, 0x00);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_get_frontend(काष्ठा dvb_frontend *fe,
			       काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 buf[8];

	dev_dbg(&client->dev, "\n");

	/* Read all needed TPS रेजिस्टरs */
	ret = regmap_bulk_पढ़ो(dev->regmap, 0x80f900, buf, 8);
	अगर (ret)
		जाओ err;

	चयन ((buf[0] >> 0) & 3) अणु
	हाल 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 0) & 3) अणु
	हाल 0:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण

	चयन ((buf[2] >> 0) & 7) अणु
	हाल 0:
		c->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		c->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		c->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		c->hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण

	चयन ((buf[3] >> 0) & 3) अणु
	हाल 0:
		c->modulation = QPSK;
		अवरोध;
	हाल 1:
		c->modulation = QAM_16;
		अवरोध;
	हाल 2:
		c->modulation = QAM_64;
		अवरोध;
	पूर्ण

	चयन ((buf[4] >> 0) & 3) अणु
	हाल 0:
		c->bandwidth_hz = 6000000;
		अवरोध;
	हाल 1:
		c->bandwidth_hz = 7000000;
		अवरोध;
	हाल 2:
		c->bandwidth_hz = 8000000;
		अवरोध;
	पूर्ण

	चयन ((buf[6] >> 0) & 7) अणु
	हाल 0:
		c->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 1:
		c->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 2:
		c->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 3:
		c->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 4:
		c->code_rate_HP = FEC_7_8;
		अवरोध;
	हाल 5:
		c->code_rate_HP = FEC_NONE;
		अवरोध;
	पूर्ण

	चयन ((buf[7] >> 0) & 7) अणु
	हाल 0:
		c->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 1:
		c->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 2:
		c->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 3:
		c->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 4:
		c->code_rate_LP = FEC_7_8;
		अवरोध;
	हाल 5:
		c->code_rate_LP = FEC_NONE;
		अवरोध;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, पंचांगp = 0;
	u8 buf[7];
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1;

	dev_dbg(&client->dev, "\n");

	*status = 0;

	/* Radio channel status: 0=no result, 1=has संकेत, 2=no संकेत */
	ret = regmap_पढ़ो(dev->regmap, 0x800047, &uपंचांगp);
	अगर (ret)
		जाओ err;

	/* Has संकेत */
	अगर (uपंचांगp == 0x01)
		*status |= FE_HAS_SIGNAL;

	अगर (uपंचांगp != 0x02) अणु
		/* TPS lock */
		ret = regmap_पढ़ो(dev->regmap, 0x80f5a9, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर ((uपंचांगp >> 0) & 0x01)
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI;

		/* Full lock */
		ret = regmap_पढ़ो(dev->regmap, 0x80f999, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर ((uपंचांगp >> 0) & 0x01)
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI | FE_HAS_SYNC |
					FE_HAS_LOCK;
	पूर्ण

	dev->fe_status = *status;

	/* Signal strength */
	अगर (dev->fe_status & FE_HAS_SIGNAL) अणु
		अगर (dev->is_af9035) अणु
			ret = regmap_पढ़ो(dev->regmap, 0x80004a, &uपंचांगp);
			अगर (ret)
				जाओ err;
			पंचांगp = -uपंचांगp * 1000;
		पूर्ण अन्यथा अणु
			ret = regmap_पढ़ो(dev->regmap, 0x8000f7, &uपंचांगp);
			अगर (ret)
				जाओ err;
			पंचांगp = (uपंचांगp - 100) * 1000;
		पूर्ण

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = पंचांगp;
	पूर्ण अन्यथा अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (dev->fe_status & FE_HAS_VITERBI) अणु
		/* Read raw SNR value */
		ret = regmap_bulk_पढ़ो(dev->regmap, 0x80002c, buf, 3);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

		/* Read superframe number */
		ret = regmap_पढ़ो(dev->regmap, 0x80f78b, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर (uपंचांगp)
			uपंचांगp1 /= uपंचांगp;

		/* Read current transmission mode */
		ret = regmap_पढ़ो(dev->regmap, 0x80f900, &uपंचांगp);
		अगर (ret)
			जाओ err;

		चयन ((uपंचांगp >> 0) & 3) अणु
		हाल 0:
			/* 2k */
			uपंचांगp1 *= 4;
			अवरोध;
		हाल 1:
			/* 8k */
			uपंचांगp1 *= 1;
			अवरोध;
		हाल 2:
			/* 4k */
			uपंचांगp1 *= 2;
			अवरोध;
		शेष:
			uपंचांगp1 *= 0;
			अवरोध;
		पूर्ण

		/* Read current modulation */
		ret = regmap_पढ़ो(dev->regmap, 0x80f903, &uपंचांगp);
		अगर (ret)
			जाओ err;

		चयन ((uपंचांगp >> 0) & 3) अणु
		हाल 0:
			/*
			 * QPSK
			 * CNR[dB] 13 * -log10((1690000 - value) / value) + 2.6
			 * value [653799, 1689999], 2.6 / 13 = 3355443
			 */
			uपंचांगp1 = clamp(uपंचांगp1, 653799U, 1689999U);
			uपंचांगp1 = ((u64)(पूर्णांकlog10(uपंचांगp1)
				 - पूर्णांकlog10(1690000 - uपंचांगp1)
				 + 3355443) * 13 * 1000) >> 24;
			अवरोध;
		हाल 1:
			/*
			 * QAM-16
			 * CNR[dB] 6 * log10((value - 370000) / (828000 - value)) + 15.7
			 * value [371105, 827999], 15.7 / 6 = 43900382
			 */
			uपंचांगp1 = clamp(uपंचांगp1, 371105U, 827999U);
			uपंचांगp1 = ((u64)(पूर्णांकlog10(uपंचांगp1 - 370000)
				 - पूर्णांकlog10(828000 - uपंचांगp1)
				 + 43900382) * 6 * 1000) >> 24;
			अवरोध;
		हाल 2:
			/*
			 * QAM-64
			 * CNR[dB] 8 * log10((value - 193000) / (425000 - value)) + 23.8
			 * value [193246, 424999], 23.8 / 8 = 49912218
			 */
			uपंचांगp1 = clamp(uपंचांगp1, 193246U, 424999U);
			uपंचांगp1 = ((u64)(पूर्णांकlog10(uपंचांगp1 - 193000)
				 - पूर्णांकlog10(425000 - uपंचांगp1)
				 + 49912218) * 8 * 1000) >> 24;
			अवरोध;
		शेष:
			uपंचांगp1 = 0;
			अवरोध;
		पूर्ण

		dev_dbg(&client->dev, "cnr=%u\n", uपंचांगp1);

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = uपंचांगp1;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* UCB/PER/BER */
	अगर (dev->fe_status & FE_HAS_LOCK) अणु
		/* Outer FEC, 204 byte packets */
		u16 पात_packet_count, rsd_packet_count;
		/* Inner FEC, bits */
		u32 rsd_bit_err_count;

		/*
		 * Packet count used क्रम measurement is 10000
		 * (rsd_packet_count). Maybe it should be increased?
		 */

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x800032, buf, 7);
		अगर (ret)
			जाओ err;

		पात_packet_count = (buf[1] << 8) | (buf[0] << 0);
		rsd_bit_err_count = (buf[4] << 16) | (buf[3] << 8) | buf[2];
		rsd_packet_count = (buf[6] << 8) | (buf[5] << 0);

		dev->error_block_count += पात_packet_count;
		dev->total_block_count += rsd_packet_count;
		dev->post_bit_error += rsd_bit_err_count;
		dev->post_bit_count += rsd_packet_count * 204 * 8;

		c->block_count.len = 1;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue = dev->total_block_count;

		c->block_error.len = 1;
		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue = dev->error_block_count;

		c->post_bit_count.len = 1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;

		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	dev_dbg(&client->dev, "\n");

	/* Use DVBv5 CNR */
	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL) अणु
		/* Return 0.1 dB क्रम AF9030 and 0-0xffff क्रम IT9130. */
		अगर (dev->is_af9035) अणु
			/* 1000x => 10x (0.1 dB) */
			*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
		पूर्ण अन्यथा अणु
			/* 1000x => 1x (1 dB) */
			*snr = भाग_s64(c->cnr.stat[0].svalue, 1000);

			/* Read current modulation */
			ret = regmap_पढ़ो(dev->regmap, 0x80f903, &uपंचांगp);
			अगर (ret)
				जाओ err;

			/* scale value to 0x0000-0xffff */
			चयन ((uपंचांगp >> 0) & 3) अणु
			हाल 0:
				*snr = *snr * 0xffff / 23;
				अवरोध;
			हाल 1:
				*snr = *snr * 0xffff / 26;
				अवरोध;
			हाल 2:
				*snr = *snr * 0xffff / 32;
				अवरोध;
			शेष:
				ret = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		*snr = 0;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	पूर्णांक ret, पंचांगp, घातer_real;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 gain_offset, buf[7];

	dev_dbg(&client->dev, "\n");

	अगर (dev->is_af9035) अणु
		/* Read संकेत strength of 0-100 scale */
		ret = regmap_पढ़ो(dev->regmap, 0x800048, &uपंचांगp);
		अगर (ret)
			जाओ err;

		/* Scale value to 0x0000-0xffff */
		*strength = uपंचांगp * 0xffff / 100;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(dev->regmap, 0x8000f7, &uपंचांगp);
		अगर (ret)
			जाओ err;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x80f900, buf, 7);
		अगर (ret)
			जाओ err;

		अगर (c->frequency <= 300000000)
			gain_offset = 7; /* VHF */
		अन्यथा
			gain_offset = 4; /* UHF */

		घातer_real = (uपंचांगp - 100 - gain_offset) -
			घातer_reference[((buf[3] >> 0) & 3)][((buf[6] >> 0) & 7)];

		अगर (घातer_real < -15)
			पंचांगp = 0;
		अन्यथा अगर ((घातer_real >= -15) && (घातer_real < 0))
			पंचांगp = (2 * (घातer_real + 15)) / 3;
		अन्यथा अगर ((घातer_real >= 0) && (घातer_real < 20))
			पंचांगp = 4 * घातer_real + 10;
		अन्यथा अगर ((घातer_real >= 20) && (घातer_real < 35))
			पंचांगp = (2 * (घातer_real - 20)) / 3 + 90;
		अन्यथा
			पंचांगp = 100;

		/* Scale value to 0x0000-0xffff */
		*strength = पंचांगp * 0xffff / 100;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;

	*ber = (dev->post_bit_error - dev->post_bit_error_prev);
	dev->post_bit_error_prev = dev->post_bit_error;

	वापस 0;
पूर्ण

अटल पूर्णांक af9033_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;

	*ucblocks = dev->error_block_count;

	वापस 0;
पूर्ण

अटल पूर्णांक af9033_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "enable=%d\n", enable);

	ret = regmap_update_bits(dev->regmap, 0x00fa04, 0x01, enable);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_pid_filter_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "onoff=%d\n", onoff);

	ret = regmap_update_bits(dev->regmap, 0x80f993, 0x01, onoff);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_pid_filter(काष्ठा dvb_frontend *fe, पूर्णांक index, u16 pid,
			     पूर्णांक onoff)
अणु
	काष्ठा af9033_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 wbuf[2] = अणु(pid >> 0) & 0xff, (pid >> 8) & 0xffपूर्ण;

	dev_dbg(&client->dev, "index=%d pid=%04x onoff=%d\n",
		index, pid, onoff);

	अगर (pid > 0x1fff)
		वापस 0;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x80f996, wbuf, 2);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x80f994, onoff);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x80f995, index);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops af9033_ops = अणु
	.delsys = अणुSYS_DVBTपूर्ण,
	.info = अणु
		.name = "Afatech AF9033 (DVB-T)",
		.frequency_min_hz = 174 * MHz,
		.frequency_max_hz = 862 * MHz,
		.frequency_stepsize_hz = 250 * kHz,
		.caps =	FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_RECOVER |
			FE_CAN_MUTE_TS
	पूर्ण,

	.init = af9033_init,
	.sleep = af9033_sleep,

	.get_tune_settings = af9033_get_tune_settings,
	.set_frontend = af9033_set_frontend,
	.get_frontend = af9033_get_frontend,

	.पढ़ो_status = af9033_पढ़ो_status,
	.पढ़ो_snr = af9033_पढ़ो_snr,
	.पढ़ो_संकेत_strength = af9033_पढ़ो_संकेत_strength,
	.पढ़ो_ber = af9033_पढ़ो_ber,
	.पढ़ो_ucblocks = af9033_पढ़ो_ucblocks,

	.i2c_gate_ctrl = af9033_i2c_gate_ctrl,
पूर्ण;

अटल पूर्णांक af9033_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा af9033_config *cfg = client->dev.platक्रमm_data;
	काष्ठा af9033_dev *dev;
	पूर्णांक ret;
	u8 buf[8];
	u32 reg;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits    =  24,
		.val_bits    =  8,
	पूर्ण;

	/* Allocate memory क्रम the पूर्णांकernal state */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Setup the state */
	dev->client = client;
	स_नकल(&dev->cfg, cfg, माप(dev->cfg));
	चयन (dev->cfg.ts_mode) अणु
	हाल AF9033_TS_MODE_PARALLEL:
		dev->ts_mode_parallel = true;
		अवरोध;
	हाल AF9033_TS_MODE_SERIAL:
		dev->ts_mode_serial = true;
		अवरोध;
	हाल AF9033_TS_MODE_USB:
		/* USB mode क्रम AF9035 */
	शेष:
		अवरोध;
	पूर्ण

	अगर (dev->cfg.घड़ी != 12000000) अणु
		ret = -ENODEV;
		dev_err(&client->dev,
			"Unsupported clock %u Hz. Only 12000000 Hz is supported currently\n",
			dev->cfg.घड़ी);
		जाओ err_kमुक्त;
	पूर्ण

	/* Create regmap */
	dev->regmap = regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* Firmware version */
	चयन (dev->cfg.tuner) अणु
	हाल AF9033_TUNER_IT9135_38:
	हाल AF9033_TUNER_IT9135_51:
	हाल AF9033_TUNER_IT9135_52:
	हाल AF9033_TUNER_IT9135_60:
	हाल AF9033_TUNER_IT9135_61:
	हाल AF9033_TUNER_IT9135_62:
		dev->is_it9135 = true;
		reg = 0x004bfc;
		अवरोध;
	शेष:
		dev->is_af9035 = true;
		reg = 0x0083e9;
		अवरोध;
	पूर्ण

	ret = regmap_bulk_पढ़ो(dev->regmap, reg, &buf[0], 4);
	अगर (ret)
		जाओ err_regmap_निकास;
	ret = regmap_bulk_पढ़ो(dev->regmap, 0x804191, &buf[4], 4);
	अगर (ret)
		जाओ err_regmap_निकास;

	dev_info(&client->dev,
		 "firmware version: LINK %d.%d.%d.%d - OFDM %d.%d.%d.%d\n",
		 buf[0], buf[1], buf[2], buf[3],
		 buf[4], buf[5], buf[6], buf[7]);

	/* Sleep as chip seems to be partly active by शेष */
	/* IT9135 did not like to sleep at that early */
	अगर (dev->is_af9035) अणु
		ret = regmap_ग_लिखो(dev->regmap, 0x80004c, 0x01);
		अगर (ret)
			जाओ err_regmap_निकास;
		ret = regmap_ग_लिखो(dev->regmap, 0x800000, 0x00);
		अगर (ret)
			जाओ err_regmap_निकास;
	पूर्ण

	/* Create dvb frontend */
	स_नकल(&dev->fe.ops, &af9033_ops, माप(dev->fe.ops));
	dev->fe.demodulator_priv = dev;
	*cfg->fe = &dev->fe;
	अगर (cfg->ops) अणु
		cfg->ops->pid_filter = af9033_pid_filter;
		cfg->ops->pid_filter_ctrl = af9033_pid_filter_ctrl;
	पूर्ण
	cfg->regmap = dev->regmap;
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "Afatech AF9033 successfully attached\n");

	वापस 0;
err_regmap_निकास:
	regmap_निकास(dev->regmap);
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9033_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा af9033_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	regmap_निकास(dev->regmap);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id af9033_id_table[] = अणु
	अणु"af9033", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, af9033_id_table);

अटल काष्ठा i2c_driver af9033_driver = अणु
	.driver = अणु
		.name	= "af9033",
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= af9033_probe,
	.हटाओ		= af9033_हटाओ,
	.id_table	= af9033_id_table,
पूर्ण;

module_i2c_driver(af9033_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Afatech AF9033 DVB-T demodulator driver");
MODULE_LICENSE("GPL");
