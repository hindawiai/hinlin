<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sony CXD2820R demodulator driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */


#समावेश "cxd2820r_priv.h"

पूर्णांक cxd2820r_set_frontend_c(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[2];
	u32 अगर_frequency;
	काष्ठा reg_val_mask tab[] = अणु
		अणु 0x00080, 0x01, 0xff पूर्ण,
		अणु 0x00081, 0x05, 0xff पूर्ण,
		अणु 0x00085, 0x07, 0xff पूर्ण,
		अणु 0x00088, 0x01, 0xff पूर्ण,

		अणु 0x00082, 0x20, 0x60 पूर्ण,
		अणु 0x1016a, 0x48, 0xff पूर्ण,
		अणु 0x100a5, 0x00, 0x01 पूर्ण,
		अणु 0x10020, 0x06, 0x07 पूर्ण,
		अणु 0x10059, 0x50, 0xff पूर्ण,
		अणु 0x10087, 0x0c, 0x3c पूर्ण,
		अणु 0x1008b, 0x07, 0xff पूर्ण,
		अणु 0x1001f, priv->अगर_agc_polarity << 7, 0x80 पूर्ण,
		अणु 0x10070, priv->ts_mode, 0xff पूर्ण,
		अणु 0x10071, !priv->ts_clk_inv << 4, 0x10 पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev,
		"delivery_system=%d modulation=%d frequency=%u symbol_rate=%u inversion=%d\n",
		c->delivery_प्रणाली, c->modulation, c->frequency,
		c->symbol_rate, c->inversion);

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	अगर (priv->delivery_प्रणाली !=  SYS_DVBC_ANNEX_A) अणु
		ret = cxd2820r_wr_reg_val_mask_tab(priv, tab, ARRAY_SIZE(tab));
		अगर (ret)
			जाओ error;
	पूर्ण

	priv->delivery_प्रणाली = SYS_DVBC_ANNEX_A;
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

	uपंचांगp = 0x4000 - DIV_ROUND_CLOSEST_ULL((u64)अगर_frequency * 0x4000, CXD2820R_CLK);
	buf[0] = (uपंचांगp >> 8) & 0xff;
	buf[1] = (uपंचांगp >> 0) & 0xff;
	ret = regmap_bulk_ग_लिखो(priv->regmap[1], 0x0042, buf, 2);
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

पूर्णांक cxd2820r_get_frontend_c(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[2];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_पढ़ो(priv->regmap[1], 0x001a, buf, 2);
	अगर (ret)
		जाओ error;

	c->symbol_rate = 2500 * ((buf[0] & 0x0f) << 8 | buf[1]);

	ret = regmap_पढ़ो(priv->regmap[1], 0x0019, &uपंचांगp);
	अगर (ret)
		जाओ error;

	चयन ((uपंचांगp >> 0) & 0x07) अणु
	हाल 0:
		c->modulation = QAM_16;
		अवरोध;
	हाल 1:
		c->modulation = QAM_32;
		अवरोध;
	हाल 2:
		c->modulation = QAM_64;
		अवरोध;
	हाल 3:
		c->modulation = QAM_128;
		अवरोध;
	हाल 4:
		c->modulation = QAM_256;
		अवरोध;
	पूर्ण

	चयन ((uपंचांगp >> 7) & 0x01) अणु
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

पूर्णांक cxd2820r_पढ़ो_status_c(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2;
	u8 buf[3];

	/* Lock detection */
	ret = regmap_bulk_पढ़ो(priv->regmap[1], 0x0088, &buf[0], 1);
	अगर (ret)
		जाओ error;
	ret = regmap_bulk_पढ़ो(priv->regmap[1], 0x0073, &buf[1], 1);
	अगर (ret)
		जाओ error;

	uपंचांगp1 = (buf[0] >> 0) & 0x01;
	uपंचांगp2 = (buf[1] >> 3) & 0x01;

	अगर (uपंचांगp1 == 1 && uपंचांगp2 == 1) अणु
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
			  FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण अन्यथा अगर (uपंचांगp1 == 1 || uपंचांगp2 == 1) अणु
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

		ret = regmap_bulk_पढ़ो(priv->regmap[1], 0x0049, buf, 2);
		अगर (ret)
			जाओ error;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		uपंचांगp = 511 - sign_extend32(uपंचांगp, 9);
		/* Scale value to 0x0000-0xffff */
		strength = uपंचांगp << 6 | uपंचांगp >> 4;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = strength;
	पूर्ण अन्यथा अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (*status & FE_HAS_VITERBI) अणु
		अचिन्हित पूर्णांक cnr, स्थिर_a, स्थिर_b;

		ret = regmap_पढ़ो(priv->regmap[1], 0x0019, &uपंचांगp);
		अगर (ret)
			जाओ error;

		अगर (((uपंचांगp >> 0) & 0x03) % 2) अणु
			स्थिर_a = 8750;
			स्थिर_b = 650;
		पूर्ण अन्यथा अणु
			स्थिर_a = 9500;
			स्थिर_b = 760;
		पूर्ण

		ret = regmap_पढ़ो(priv->regmap[1], 0x004d, &uपंचांगp);
		अगर (ret)
			जाओ error;

		#घोषणा CXD2820R_LOG2_E_24 24204406 /* log2(e) << 24 */
		अगर (uपंचांगp)
			cnr = भाग_u64((u64)(पूर्णांकlog2(स्थिर_b) - पूर्णांकlog2(uपंचांगp))
				      * स्थिर_a, CXD2820R_LOG2_E_24);
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
			ret = regmap_bulk_पढ़ो(priv->regmap[1], 0x0076, buf, 3);
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
			ret = regmap_ग_लिखो(priv->regmap[1], 0x0079, 0x01);
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

पूर्णांक cxd2820r_init_c(काष्ठा dvb_frontend *fe)
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

पूर्णांक cxd2820r_sleep_c(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अटल स्थिर काष्ठा reg_val_mask tab[] = अणु
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

पूर्णांक cxd2820r_get_tune_settings_c(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 500;
	s->step_size = 0; /* no zigzag */
	s->max_drअगरt = 0;

	वापस 0;
पूर्ण
