<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sony CXD2820R demodulator driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */


#समावेश "cxd2820r_priv.h"

पूर्णांक cxd2820r_set_frontend_t(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, bw_i;
	अचिन्हित पूर्णांक uपंचांगp;
	u32 अगर_frequency;
	u8 buf[3], bw_param;
	u8 bw_params1[][5] = अणु
		अणु 0x17, 0xea, 0xaa, 0xaa, 0xaa पूर्ण, /* 6 MHz */
		अणु 0x14, 0x80, 0x00, 0x00, 0x00 पूर्ण, /* 7 MHz */
		अणु 0x11, 0xf0, 0x00, 0x00, 0x00 पूर्ण, /* 8 MHz */
	पूर्ण;
	u8 bw_params2[][2] = अणु
		अणु 0x1f, 0xdc पूर्ण, /* 6 MHz */
		अणु 0x12, 0xf8 पूर्ण, /* 7 MHz */
		अणु 0x01, 0xe0 पूर्ण, /* 8 MHz */
	पूर्ण;
	काष्ठा reg_val_mask tab[] = अणु
		अणु 0x00080, 0x00, 0xff पूर्ण,
		अणु 0x00081, 0x03, 0xff पूर्ण,
		अणु 0x00085, 0x07, 0xff पूर्ण,
		अणु 0x00088, 0x01, 0xff पूर्ण,

		अणु 0x00070, priv->ts_mode, 0xff पूर्ण,
		अणु 0x00071, !priv->ts_clk_inv << 4, 0x10 पूर्ण,
		अणु 0x000cb, priv->अगर_agc_polarity << 6, 0x40 पूर्ण,
		अणु 0x000a5, 0x00, 0x01 पूर्ण,
		अणु 0x00082, 0x20, 0x60 पूर्ण,
		अणु 0x000c2, 0xc3, 0xff पूर्ण,
		अणु 0x0016a, 0x50, 0xff पूर्ण,
		अणु 0x00427, 0x41, 0xff पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev,
		"delivery_system=%d modulation=%d frequency=%u bandwidth_hz=%u inversion=%d\n",
		c->delivery_प्रणाली, c->modulation, c->frequency,
		c->bandwidth_hz, c->inversion);

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		bw_i = 0;
		bw_param = 2;
		अवरोध;
	हाल 7000000:
		bw_i = 1;
		bw_param = 1;
		अवरोध;
	हाल 8000000:
		bw_i = 2;
		bw_param = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	अगर (priv->delivery_प्रणाली != SYS_DVBT) अणु
		ret = cxd2820r_wr_reg_val_mask_tab(priv, tab, ARRAY_SIZE(tab));
		अगर (ret)
			जाओ error;
	पूर्ण

	priv->delivery_प्रणाली = SYS_DVBT;
	priv->ber_running = false; /* tune stops BER counter */

	/* program IF frequency */
	अगर (fe->ops.tuner_ops.get_अगर_frequency) अणु
		ret = fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_frequency);
		अगर (ret)
			जाओ error;
		dev_dbg(&client->dev, "if_frequency=%u\n", अगर_frequency);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	uपंचांगp = DIV_ROUND_CLOSEST_ULL((u64)अगर_frequency * 0x1000000, CXD2820R_CLK);
	buf[0] = (uपंचांगp >> 16) & 0xff;
	buf[1] = (uपंचांगp >>  8) & 0xff;
	buf[2] = (uपंचांगp >>  0) & 0xff;
	ret = regmap_bulk_ग_लिखो(priv->regmap[0], 0x00b6, buf, 3);
	अगर (ret)
		जाओ error;

	ret = regmap_bulk_ग_लिखो(priv->regmap[0], 0x009f, bw_params1[bw_i], 5);
	अगर (ret)
		जाओ error;

	ret = regmap_update_bits(priv->regmap[0], 0x00d7, 0xc0, bw_param << 6);
	अगर (ret)
		जाओ error;

	ret = regmap_bulk_ग_लिखो(priv->regmap[0], 0x00d9, bw_params2[bw_i], 2);
	अगर (ret)
		जाओ error;

	ret = regmap_ग_लिखो(priv->regmap[0], 0x00ff, 0x08);
	अगर (ret)
		जाओ error;

	ret = regmap_ग_लिखो(priv->regmap[0], 0x00fe, 0x01);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_get_frontend_t(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[2];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x002f, buf, माप(buf));
	अगर (ret)
		जाओ error;

	चयन ((buf[0] >> 6) & 0x03) अणु
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

	चयन ((buf[1] >> 1) & 0x03) अणु
	हाल 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 3) & 0x03) अणु
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

	चयन ((buf[0] >> 3) & 0x07) अणु
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

	चयन ((buf[0] >> 0) & 0x07) अणु
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
	पूर्ण

	चयन ((buf[1] >> 5) & 0x07) अणु
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
	पूर्ण

	ret = regmap_पढ़ो(priv->regmap[0], 0x07c6, &uपंचांगp);
	अगर (ret)
		जाओ error;

	चयन ((uपंचांगp >> 0) & 0x01) अणु
	हाल 0:
		c->inversion = INVERSION_OFF;
		अवरोध;
	हाल 1:
		c->inversion = INVERSION_ON;
		अवरोध;
	पूर्ण

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_पढ़ो_status_t(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2;
	u8 buf[3];

	/* Lock detection */
	ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x0010, &buf[0], 1);
	अगर (ret)
		जाओ error;
	ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x0073, &buf[1], 1);
	अगर (ret)
		जाओ error;

	uपंचांगp1 = (buf[0] >> 0) & 0x07;
	uपंचांगp2 = (buf[1] >> 3) & 0x01;

	अगर (uपंचांगp1 == 6 && uपंचांगp2 == 1) अणु
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
			  FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण अन्यथा अगर (uपंचांगp1 == 6 || uपंचांगp2 == 1) अणु
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
			  FE_HAS_VITERBI | FE_HAS_SYNC;
	पूर्ण अन्यथा अणु
		*status = 0;
	पूर्ण

	dev_dbg(&client->dev, "status=%02x raw=%*ph sync=%u ts=%u\n",
		*status, 2, buf, uपंचांगp1, uपंचांगp2);

	/* Signal strength */
	अगर (*status & FE_HAS_SIGNAL) अणु
		अचिन्हित पूर्णांक strength;

		ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x0026, buf, 2);
		अगर (ret)
			जाओ error;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		uपंचांगp = ~uपंचांगp & 0x0fff;
		/* Scale value to 0x0000-0xffff */
		strength = uपंचांगp << 4 | uपंचांगp >> 8;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = strength;
	पूर्ण अन्यथा अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (*status & FE_HAS_VITERBI) अणु
		अचिन्हित पूर्णांक cnr;

		ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x002c, buf, 2);
		अगर (ret)
			जाओ error;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		अगर (uपंचांगp)
			cnr = भाग_u64((u64)(पूर्णांकlog10(uपंचांगp)
				      - पूर्णांकlog10(32000 - uपंचांगp) + 55532585)
				      * 10000, (1 << 24));
		अन्यथा
			cnr = 0;

		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = cnr;
	पूर्ण अन्यथा अणु
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* BER */
	अगर (*status & FE_HAS_SYNC) अणु
		अचिन्हित पूर्णांक post_bit_error;
		bool start_ber;

		अगर (priv->ber_running) अणु
			ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x0076, buf, 3);
			अगर (ret)
				जाओ error;

			अगर ((buf[2] >> 7) & 0x01) अणु
				post_bit_error = buf[2] << 16 | buf[1] << 8 |
						 buf[0] << 0;
				post_bit_error &= 0x0fffff;
				start_ber = true;
			पूर्ण अन्यथा अणु
				post_bit_error = 0;
				start_ber = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			post_bit_error = 0;
			start_ber = true;
		पूर्ण

		अगर (start_ber) अणु
			ret = regmap_ग_लिखो(priv->regmap[0], 0x0079, 0x01);
			अगर (ret)
				जाओ error;
			priv->ber_running = true;
		पूर्ण

		priv->post_bit_error += post_bit_error;

		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = priv->post_bit_error;
	पूर्ण अन्यथा अणु
		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_init_t(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	ret = regmap_ग_लिखो(priv->regmap[0], 0x0085, 0x07);
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_sleep_t(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अटल काष्ठा reg_val_mask tab[] = अणु
		अणु 0x000ff, 0x1f, 0xff पूर्ण,
		अणु 0x00085, 0x00, 0xff पूर्ण,
		अणु 0x00088, 0x01, 0xff पूर्ण,
		अणु 0x00081, 0x00, 0xff पूर्ण,
		अणु 0x00080, 0x00, 0xff पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	priv->delivery_प्रणाली = SYS_UNDEFINED;

	ret = cxd2820r_wr_reg_val_mask_tab(priv, tab, ARRAY_SIZE(tab));
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_get_tune_settings_t(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 500;
	s->step_size = fe->ops.info.frequency_stepsize_hz * 2;
	s->max_drअगरt = (fe->ops.info.frequency_stepsize_hz * 2) + 1;

	वापस 0;
पूर्ण
