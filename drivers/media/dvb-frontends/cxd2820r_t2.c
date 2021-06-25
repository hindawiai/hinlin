<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sony CXD2820R demodulator driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */


#समावेश "cxd2820r_priv.h"

पूर्णांक cxd2820r_set_frontend_t2(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, bw_i;
	अचिन्हित पूर्णांक uपंचांगp;
	u32 अगर_frequency;
	u8 buf[3], bw_param;
	u8 bw_params1[][5] = अणु
		अणु 0x1c, 0xb3, 0x33, 0x33, 0x33 पूर्ण, /* 5 MHz */
		अणु 0x17, 0xea, 0xaa, 0xaa, 0xaa पूर्ण, /* 6 MHz */
		अणु 0x14, 0x80, 0x00, 0x00, 0x00 पूर्ण, /* 7 MHz */
		अणु 0x11, 0xf0, 0x00, 0x00, 0x00 पूर्ण, /* 8 MHz */
	पूर्ण;
	काष्ठा reg_val_mask tab[] = अणु
		अणु 0x00080, 0x02, 0xff पूर्ण,
		अणु 0x00081, 0x20, 0xff पूर्ण,
		अणु 0x00085, 0x07, 0xff पूर्ण,
		अणु 0x00088, 0x01, 0xff पूर्ण,
		अणु 0x02069, 0x01, 0xff पूर्ण,

		अणु 0x0207f, 0x2a, 0xff पूर्ण,
		अणु 0x02082, 0x0a, 0xff पूर्ण,
		अणु 0x02083, 0x0a, 0xff पूर्ण,
		अणु 0x020cb, priv->अगर_agc_polarity << 6, 0x40 पूर्ण,
		अणु 0x02070, priv->ts_mode, 0xff पूर्ण,
		अणु 0x02071, !priv->ts_clk_inv << 6, 0x40 पूर्ण,
		अणु 0x020b5, priv->spec_inv << 4, 0x10 पूर्ण,
		अणु 0x02567, 0x07, 0x0f पूर्ण,
		अणु 0x02569, 0x03, 0x03 पूर्ण,
		अणु 0x02595, 0x1a, 0xff पूर्ण,
		अणु 0x02596, 0x50, 0xff पूर्ण,
		अणु 0x02a8c, 0x00, 0xff पूर्ण,
		अणु 0x02a8d, 0x34, 0xff पूर्ण,
		अणु 0x02a45, 0x06, 0x07 पूर्ण,
		अणु 0x03f10, 0x0d, 0xff पूर्ण,
		अणु 0x03f11, 0x02, 0xff पूर्ण,
		अणु 0x03f12, 0x01, 0xff पूर्ण,
		अणु 0x03f23, 0x2c, 0xff पूर्ण,
		अणु 0x03f51, 0x13, 0xff पूर्ण,
		अणु 0x03f52, 0x01, 0xff पूर्ण,
		अणु 0x03f53, 0x00, 0xff पूर्ण,
		अणु 0x027e6, 0x14, 0xff पूर्ण,
		अणु 0x02786, 0x02, 0x07 पूर्ण,
		अणु 0x02787, 0x40, 0xe0 पूर्ण,
		अणु 0x027ef, 0x10, 0x18 पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev,
		"delivery_system=%d modulation=%d frequency=%u bandwidth_hz=%u inversion=%d stream_id=%u\n",
		c->delivery_प्रणाली, c->modulation, c->frequency,
		c->bandwidth_hz, c->inversion, c->stream_id);

	चयन (c->bandwidth_hz) अणु
	हाल 5000000:
		bw_i = 0;
		bw_param = 3;
		अवरोध;
	हाल 6000000:
		bw_i = 1;
		bw_param = 2;
		अवरोध;
	हाल 7000000:
		bw_i = 2;
		bw_param = 1;
		अवरोध;
	हाल 8000000:
		bw_i = 3;
		bw_param = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	अगर (priv->delivery_प्रणाली != SYS_DVBT2) अणु
		ret = cxd2820r_wr_reg_val_mask_tab(priv, tab, ARRAY_SIZE(tab));
		अगर (ret)
			जाओ error;
	पूर्ण

	priv->delivery_प्रणाली = SYS_DVBT2;

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
	ret = regmap_bulk_ग_लिखो(priv->regmap[0], 0x20b6, buf, 3);
	अगर (ret)
		जाओ error;

	/* PLP filtering */
	अगर (c->stream_id > 255) अणु
		dev_dbg(&client->dev, "disable PLP filtering\n");
		ret = regmap_ग_लिखो(priv->regmap[0], 0x23ad, 0x00);
		अगर (ret)
			जाओ error;
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "enable PLP filtering\n");
		ret = regmap_ग_लिखो(priv->regmap[0], 0x23af, c->stream_id & 0xff);
		अगर (ret)
			जाओ error;
		ret = regmap_ग_लिखो(priv->regmap[0], 0x23ad, 0x01);
		अगर (ret)
			जाओ error;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(priv->regmap[0], 0x209f, bw_params1[bw_i], 5);
	अगर (ret)
		जाओ error;

	ret = regmap_update_bits(priv->regmap[0], 0x20d7, 0xc0, bw_param << 6);
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

पूर्णांक cxd2820r_get_frontend_t2(काष्ठा dvb_frontend *fe,
			     काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[2];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x205c, buf, 2);
	अगर (ret)
		जाओ error;

	चयन ((buf[0] >> 0) & 0x07) अणु
	हाल 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	हाल 2:
		c->transmission_mode = TRANSMISSION_MODE_4K;
		अवरोध;
	हाल 3:
		c->transmission_mode = TRANSMISSION_MODE_1K;
		अवरोध;
	हाल 4:
		c->transmission_mode = TRANSMISSION_MODE_16K;
		अवरोध;
	हाल 5:
		c->transmission_mode = TRANSMISSION_MODE_32K;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 4) & 0x07) अणु
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
	हाल 4:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_128;
		अवरोध;
	हाल 5:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_19_128;
		अवरोध;
	हाल 6:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_19_256;
		अवरोध;
	पूर्ण

	ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x225b, buf, 2);
	अगर (ret)
		जाओ error;

	चयन ((buf[0] >> 0) & 0x07) अणु
	हाल 0:
		c->fec_inner = FEC_1_2;
		अवरोध;
	हाल 1:
		c->fec_inner = FEC_3_5;
		अवरोध;
	हाल 2:
		c->fec_inner = FEC_2_3;
		अवरोध;
	हाल 3:
		c->fec_inner = FEC_3_4;
		अवरोध;
	हाल 4:
		c->fec_inner = FEC_4_5;
		अवरोध;
	हाल 5:
		c->fec_inner = FEC_5_6;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 0) & 0x07) अणु
	हाल 0:
		c->modulation = QPSK;
		अवरोध;
	हाल 1:
		c->modulation = QAM_16;
		अवरोध;
	हाल 2:
		c->modulation = QAM_64;
		अवरोध;
	हाल 3:
		c->modulation = QAM_256;
		अवरोध;
	पूर्ण

	ret = regmap_पढ़ो(priv->regmap[0], 0x20b5, &uपंचांगp);
	अगर (ret)
		जाओ error;

	चयन ((uपंचांगp >> 4) & 0x01) अणु
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

पूर्णांक cxd2820r_पढ़ो_status_t2(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2;
	u8 buf[4];

	/* Lock detection */
	ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x2010, &buf[0], 1);
	अगर (ret)
		जाओ error;

	uपंचांगp1 = (buf[0] >> 0) & 0x07;
	uपंचांगp2 = (buf[0] >> 5) & 0x01;

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
		*status, 1, buf, uपंचांगp1, uपंचांगp2);

	/* Signal strength */
	अगर (*status & FE_HAS_SIGNAL) अणु
		अचिन्हित पूर्णांक strength;

		ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x2026, buf, 2);
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

		ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x2028, buf, 2);
		अगर (ret)
			जाओ error;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		uपंचांगp = uपंचांगp & 0x0fff;
		#घोषणा CXD2820R_LOG10_8_24 15151336 /* log10(8) << 24 */
		अगर (uपंचांगp)
			cnr = भाग_u64((u64)(पूर्णांकlog10(uपंचांगp)
				      - CXD2820R_LOG10_8_24) * 10000,
				      (1 << 24));
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

		ret = regmap_bulk_पढ़ो(priv->regmap[0], 0x2039, buf, 4);
		अगर (ret)
			जाओ error;

		अगर ((buf[0] >> 4) & 0x01) अणु
			post_bit_error = buf[0] << 24 | buf[1] << 16 |
					 buf[2] << 8 | buf[3] << 0;
			post_bit_error &= 0x0fffffff;
		पूर्ण अन्यथा अणु
			post_bit_error = 0;
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

पूर्णांक cxd2820r_sleep_t2(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cxd2820r_priv *priv = fe->demodulator_priv;
	काष्ठा i2c_client *client = priv->client[0];
	पूर्णांक ret;
	अटल स्थिर काष्ठा reg_val_mask tab[] = अणु
		अणु 0x000ff, 0x1f, 0xff पूर्ण,
		अणु 0x00085, 0x00, 0xff पूर्ण,
		अणु 0x00088, 0x01, 0xff पूर्ण,
		अणु 0x02069, 0x00, 0xff पूर्ण,
		अणु 0x00081, 0x00, 0xff पूर्ण,
		अणु 0x00080, 0x00, 0xff पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	ret = cxd2820r_wr_reg_val_mask_tab(priv, tab, ARRAY_SIZE(tab));
	अगर (ret)
		जाओ error;

	priv->delivery_प्रणाली = SYS_UNDEFINED;

	वापस ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cxd2820r_get_tune_settings_t2(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 1500;
	s->step_size = fe->ops.info.frequency_stepsize_hz * 2;
	s->max_drअगरt = (fe->ops.info.frequency_stepsize_hz * 2) + 1;

	वापस 0;
पूर्ण
