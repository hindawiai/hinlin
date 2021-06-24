<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Realtek RTL2830 DVB-T demodulator driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#समावेश "rtl2830_priv.h"

/* Our regmap is bypassing I2C adapter lock, thus we करो it! */
अटल पूर्णांक rtl2830_bulk_ग_लिखो(काष्ठा i2c_client *client, अचिन्हित पूर्णांक reg,
			      स्थिर व्योम *val, माप_प्रकार val_count)
अणु
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = regmap_bulk_ग_लिखो(dev->regmap, reg, val, val_count);
	i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_update_bits(काष्ठा i2c_client *client, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = regmap_update_bits(dev->regmap, reg, mask, val);
	i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_bulk_पढ़ो(काष्ठा i2c_client *client, अचिन्हित पूर्णांक reg,
			     व्योम *val, माप_प्रकार val_count)
अणु
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = regmap_bulk_पढ़ो(dev->regmap, reg, val, val_count);
	i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	पूर्णांक ret, i;
	काष्ठा rtl2830_reg_val_mask tab[] = अणु
		अणु0x00d, 0x01, 0x03पूर्ण,
		अणु0x00d, 0x10, 0x10पूर्ण,
		अणु0x104, 0x00, 0x1eपूर्ण,
		अणु0x105, 0x80, 0x80पूर्ण,
		अणु0x110, 0x02, 0x03पूर्ण,
		अणु0x110, 0x08, 0x0cपूर्ण,
		अणु0x17b, 0x00, 0x40पूर्ण,
		अणु0x17d, 0x05, 0x0fपूर्ण,
		अणु0x17d, 0x50, 0xf0पूर्ण,
		अणु0x18c, 0x08, 0x0fपूर्ण,
		अणु0x18d, 0x00, 0xc0पूर्ण,
		अणु0x188, 0x05, 0x0fपूर्ण,
		अणु0x189, 0x00, 0xfcपूर्ण,
		अणु0x2d5, 0x02, 0x02पूर्ण,
		अणु0x2f1, 0x02, 0x06पूर्ण,
		अणु0x2f1, 0x20, 0xf8पूर्ण,
		अणु0x16d, 0x00, 0x01पूर्ण,
		अणु0x1a6, 0x00, 0x80पूर्ण,
		अणु0x106, dev->pdata->vtop, 0x3fपूर्ण,
		अणु0x107, dev->pdata->krf, 0x3fपूर्ण,
		अणु0x112, 0x28, 0xffपूर्ण,
		अणु0x103, dev->pdata->agc_targ_val, 0xffपूर्ण,
		अणु0x00a, 0x02, 0x07पूर्ण,
		अणु0x140, 0x0c, 0x3cपूर्ण,
		अणु0x140, 0x40, 0xc0पूर्ण,
		अणु0x15b, 0x05, 0x07पूर्ण,
		अणु0x15b, 0x28, 0x38पूर्ण,
		अणु0x15c, 0x05, 0x07पूर्ण,
		अणु0x15c, 0x28, 0x38पूर्ण,
		अणु0x115, dev->pdata->spec_inv, 0x01पूर्ण,
		अणु0x16f, 0x01, 0x07पूर्ण,
		अणु0x170, 0x18, 0x38पूर्ण,
		अणु0x172, 0x0f, 0x0fपूर्ण,
		अणु0x173, 0x08, 0x38पूर्ण,
		अणु0x175, 0x01, 0x07पूर्ण,
		अणु0x176, 0x00, 0xc0पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(tab); i++) अणु
		ret = rtl2830_update_bits(client, tab[i].reg, tab[i].mask,
					  tab[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = rtl2830_bulk_ग_लिखो(client, 0x18f, "\x28\x00", 2);
	अगर (ret)
		जाओ err;

	ret = rtl2830_bulk_ग_लिखो(client, 0x195,
				 "\x04\x06\x0a\x12\x0a\x12\x1e\x28", 8);
	अगर (ret)
		जाओ err;

	/* TODO: spec init */

	/* soft reset */
	ret = rtl2830_update_bits(client, 0x101, 0x04, 0x04);
	अगर (ret)
		जाओ err;

	ret = rtl2830_update_bits(client, 0x101, 0x04, 0x00);
	अगर (ret)
		जाओ err;

	/* init stats here in order संकेत app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dev->sleeping = false;

	वापस ret;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);

	dev->sleeping = true;
	dev->fe_status = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 500;
	s->step_size = fe->ops.info.frequency_stepsize_hz * 2;
	s->max_drअगरt = (fe->ops.info.frequency_stepsize_hz * 2) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	u64 num;
	u8 buf[3], u8पंचांगp;
	u32 अगर_ctl, अगर_frequency;
	अटल स्थिर u8 bw_params1[3][34] = अणु
		अणु
		0x1f, 0xf0, 0x1f, 0xf0, 0x1f, 0xfa, 0x00, 0x17, 0x00, 0x41,
		0x00, 0x64, 0x00, 0x67, 0x00, 0x38, 0x1f, 0xde, 0x1f, 0x7a,
		0x1f, 0x47, 0x1f, 0x7c, 0x00, 0x30, 0x01, 0x4b, 0x02, 0x82,
		0x03, 0x73, 0x03, 0xcf, /* 6 MHz */
		पूर्ण, अणु
		0x1f, 0xfa, 0x1f, 0xda, 0x1f, 0xc1, 0x1f, 0xb3, 0x1f, 0xca,
		0x00, 0x07, 0x00, 0x4d, 0x00, 0x6d, 0x00, 0x40, 0x1f, 0xca,
		0x1f, 0x4d, 0x1f, 0x2a, 0x1f, 0xb2, 0x00, 0xec, 0x02, 0x7e,
		0x03, 0xd0, 0x04, 0x53, /* 7 MHz */
		पूर्ण, अणु
		0x00, 0x10, 0x00, 0x0e, 0x1f, 0xf7, 0x1f, 0xc9, 0x1f, 0xa0,
		0x1f, 0xa6, 0x1f, 0xec, 0x00, 0x4e, 0x00, 0x7d, 0x00, 0x3a,
		0x1f, 0x98, 0x1f, 0x10, 0x1f, 0x40, 0x00, 0x75, 0x02, 0x5f,
		0x04, 0x24, 0x04, 0xdb, /* 8 MHz */
		पूर्ण,
	पूर्ण;
	अटल स्थिर u8 bw_params2[3][6] = अणु
		अणु0xc3, 0x0c, 0x44, 0x33, 0x33, 0x30पूर्ण, /* 6 MHz */
		अणु0xb8, 0xe3, 0x93, 0x99, 0x99, 0x98पूर्ण, /* 7 MHz */
		अणु0xae, 0xba, 0xf3, 0x26, 0x66, 0x64पूर्ण, /* 8 MHz */
	पूर्ण;

	dev_dbg(&client->dev, "frequency=%u bandwidth_hz=%u inversion=%u\n",
		c->frequency, c->bandwidth_hz, c->inversion);

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		i = 0;
		अवरोध;
	हाल 7000000:
		i = 1;
		अवरोध;
	हाल 8000000:
		i = 2;
		अवरोध;
	शेष:
		dev_err(&client->dev, "invalid bandwidth_hz %u\n",
			c->bandwidth_hz);
		वापस -EINVAL;
	पूर्ण

	ret = rtl2830_update_bits(client, 0x008, 0x06, i << 1);
	अगर (ret)
		जाओ err;

	/* program अगर frequency */
	अगर (fe->ops.tuner_ops.get_अगर_frequency)
		ret = fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_frequency);
	अन्यथा
		ret = -EINVAL;
	अगर (ret)
		जाओ err;

	num = अगर_frequency % dev->pdata->clk;
	num *= 0x400000;
	num = भाग_u64(num, dev->pdata->clk);
	num = -num;
	अगर_ctl = num & 0x3fffff;
	dev_dbg(&client->dev, "if_frequency=%d if_ctl=%08x\n",
		अगर_frequency, अगर_ctl);

	buf[0] = (अगर_ctl >> 16) & 0x3f;
	buf[1] = (अगर_ctl >>  8) & 0xff;
	buf[2] = (अगर_ctl >>  0) & 0xff;

	ret = rtl2830_bulk_पढ़ो(client, 0x119, &u8पंचांगp, 1);
	अगर (ret)
		जाओ err;

	buf[0] |= u8पंचांगp & 0xc0;  /* [7:6] */

	ret = rtl2830_bulk_ग_लिखो(client, 0x119, buf, 3);
	अगर (ret)
		जाओ err;

	/* 1/2 split I2C ग_लिखो */
	ret = rtl2830_bulk_ग_लिखो(client, 0x11c, &bw_params1[i][0], 17);
	अगर (ret)
		जाओ err;

	/* 2/2 split I2C ग_लिखो */
	ret = rtl2830_bulk_ग_लिखो(client, 0x12d, &bw_params1[i][17], 17);
	अगर (ret)
		जाओ err;

	ret = rtl2830_bulk_ग_लिखो(client, 0x19d, bw_params2[i], 6);
	अगर (ret)
		जाओ err;

	वापस ret;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	u8 buf[3];

	अगर (dev->sleeping)
		वापस 0;

	ret = rtl2830_bulk_पढ़ो(client, 0x33c, buf, 2);
	अगर (ret)
		जाओ err;

	ret = rtl2830_bulk_पढ़ो(client, 0x351, &buf[2], 1);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "TPS=%*ph\n", 3, buf);

	चयन ((buf[0] >> 2) & 3) अणु
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

	चयन ((buf[2] >> 2) & 1) अणु
	हाल 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
	पूर्ण

	चयन ((buf[2] >> 0) & 3) अणु
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

	चयन ((buf[0] >> 4) & 7) अणु
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

	चयन ((buf[1] >> 3) & 7) अणु
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

	चयन ((buf[1] >> 0) & 7) अणु
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

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	पूर्णांक ret, sपंचांगp;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 u8पंचांगp, buf[2];

	*status = 0;

	अगर (dev->sleeping)
		वापस 0;

	ret = rtl2830_bulk_पढ़ो(client, 0x351, &u8पंचांगp, 1);
	अगर (ret)
		जाओ err;

	u8पंचांगp = (u8पंचांगp >> 3) & 0x0f; /* [6:3] */
	अगर (u8पंचांगp == 11) अणु
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण अन्यथा अगर (u8पंचांगp == 10) अणु
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI;
	पूर्ण

	dev->fe_status = *status;

	/* Signal strength */
	अगर (dev->fe_status & FE_HAS_SIGNAL) अणु
		/* Read IF AGC */
		ret = rtl2830_bulk_पढ़ो(client, 0x359, buf, 2);
		अगर (ret)
			जाओ err;

		sपंचांगp = buf[0] << 8 | buf[1] << 0;
		sपंचांगp = sign_extend32(sपंचांगp, 13);
		uपंचांगp = clamp_val(-4 * sपंचांगp + 32767, 0x0000, 0xffff);

		dev_dbg(&client->dev, "IF AGC=%d\n", sपंचांगp);

		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = uपंचांगp;
	पूर्ण अन्यथा अणु
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (dev->fe_status & FE_HAS_VITERBI) अणु
		अचिन्हित पूर्णांक hierarchy, स्थिरellation;
		#घोषणा CONSTELLATION_NUM 3
		#घोषणा HIERARCHY_NUM 4
		अटल स्थिर u32 स्थिरant[CONSTELLATION_NUM][HIERARCHY_NUM] = अणु
			अणु70705899, 70705899, 70705899, 70705899पूर्ण,
			अणु82433173, 82433173, 87483115, 94445660पूर्ण,
			अणु92888734, 92888734, 95487525, 99770748पूर्ण,
		पूर्ण;

		ret = rtl2830_bulk_पढ़ो(client, 0x33c, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;

		स्थिरellation = (u8पंचांगp >> 2) & 0x03; /* [3:2] */
		अगर (स्थिरellation > CONSTELLATION_NUM - 1)
			जाओ err;

		hierarchy = (u8पंचांगp >> 4) & 0x07; /* [6:4] */
		अगर (hierarchy > HIERARCHY_NUM - 1)
			जाओ err;

		ret = rtl2830_bulk_पढ़ो(client, 0x40c, buf, 2);
		अगर (ret)
			जाओ err;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		अगर (uपंचांगp)
			sपंचांगp = (स्थिरant[स्थिरellation][hierarchy] -
			       पूर्णांकlog10(uपंचांगp)) / ((1 << 24) / 10000);
		अन्यथा
			sपंचांगp = 0;

		dev_dbg(&client->dev, "CNR raw=%u\n", uपंचांगp);

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = sपंचांगp;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* BER */
	अगर (dev->fe_status & FE_HAS_LOCK) अणु
		ret = rtl2830_bulk_पढ़ो(client, 0x34e, buf, 2);
		अगर (ret)
			जाओ err;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		dev->post_bit_error += uपंचांगp;
		dev->post_bit_count += 1000000;

		dev_dbg(&client->dev, "BER errors=%u total=1000000\n", uपंचांगp);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण


	वापस ret;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
	अन्यथा
		*snr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);

	*ber = (dev->post_bit_error - dev->post_bit_error_prev);
	dev->post_bit_error_prev = dev->post_bit_error;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	*ucblocks = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->strength.stat[0].scale == FE_SCALE_RELATIVE)
		*strength = c->strength.stat[0].uvalue;
	अन्यथा
		*strength = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops rtl2830_ops = अणु
	.delsys = अणुSYS_DVBTपूर्ण,
	.info = अणु
		.name = "Realtek RTL2830 (DVB-T)",
		.caps = FE_CAN_FEC_1_2 |
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

	.init = rtl2830_init,
	.sleep = rtl2830_sleep,

	.get_tune_settings = rtl2830_get_tune_settings,

	.set_frontend = rtl2830_set_frontend,
	.get_frontend = rtl2830_get_frontend,

	.पढ़ो_status = rtl2830_पढ़ो_status,
	.पढ़ो_snr = rtl2830_पढ़ो_snr,
	.पढ़ो_ber = rtl2830_पढ़ो_ber,
	.पढ़ो_ucblocks = rtl2830_पढ़ो_ucblocks,
	.पढ़ो_संकेत_strength = rtl2830_पढ़ो_संकेत_strength,
पूर्ण;

अटल पूर्णांक rtl2830_pid_filter_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(&client->dev, "onoff=%d\n", onoff);

	/* enable / disable PID filter */
	अगर (onoff)
		u8पंचांगp = 0x80;
	अन्यथा
		u8पंचांगp = 0x00;

	ret = rtl2830_update_bits(client, 0x061, 0x80, u8पंचांगp);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_pid_filter(काष्ठा dvb_frontend *fe, u8 index, u16 pid, पूर्णांक onoff)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;
	u8 buf[4];

	dev_dbg(&client->dev, "index=%d pid=%04x onoff=%d\n",
		index, pid, onoff);

	/* skip invalid PIDs (0x2000) */
	अगर (pid > 0x1fff || index > 32)
		वापस 0;

	अगर (onoff)
		set_bit(index, &dev->filters);
	अन्यथा
		clear_bit(index, &dev->filters);

	/* enable / disable PIDs */
	buf[0] = (dev->filters >>  0) & 0xff;
	buf[1] = (dev->filters >>  8) & 0xff;
	buf[2] = (dev->filters >> 16) & 0xff;
	buf[3] = (dev->filters >> 24) & 0xff;
	ret = rtl2830_bulk_ग_लिखो(client, 0x062, buf, 4);
	अगर (ret)
		जाओ err;

	/* add PID */
	buf[0] = (pid >> 8) & 0xff;
	buf[1] = (pid >> 0) & 0xff;
	ret = rtl2830_bulk_ग_लिखो(client, 0x066 + 2 * index, buf, 2);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

/*
 * I2C gate/mux/repeater logic
 * We must use unlocked __i2c_transfer() here (through regmap) because of I2C
 * adapter lock is alपढ़ोy taken by tuner driver.
 * Gate is बंदd स्वतःmatically after single I2C transfer.
 */
अटल पूर्णांक rtl2830_select(काष्ठा i2c_mux_core *muxc, u32 chan_id)
अणु
	काष्ठा i2c_client *client = i2c_mux_priv(muxc);
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	/* खोलो I2C repeater क्रम 1 transfer, बंदs स्वतःmatically */
	/* XXX: regmap_update_bits() करोes not lock I2C adapter */
	ret = regmap_update_bits(dev->regmap, 0x101, 0x08, 0x08);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल काष्ठा dvb_frontend *rtl2830_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &dev->fe;
पूर्ण

अटल काष्ठा i2c_adapter *rtl2830_get_i2c_adapter(काष्ठा i2c_client *client)
अणु
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस dev->muxc->adapter[0];
पूर्ण

/*
 * We implement own I2C access routines क्रम regmap in order to get manual access
 * to I2C adapter lock, which is needed क्रम I2C mux adapter.
 */
अटल पूर्णांक rtl2830_regmap_पढ़ो(व्योम *context, स्थिर व्योम *reg_buf,
			       माप_प्रकार reg_size, व्योम *val_buf, माप_प्रकार val_size)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक ret;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = reg_size,
			.buf = (u8 *)reg_buf,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = val_size,
			.buf = val_buf,
		पूर्ण
	पूर्ण;

	ret = __i2c_transfer(client->adapter, msg, 2);
	अगर (ret != 2) अणु
		dev_warn(&client->dev, "i2c reg read failed %d\n", ret);
		अगर (ret >= 0)
			ret = -EREMOTEIO;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_regmap_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक ret;
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = count,
			.buf = (u8 *)data,
		पूर्ण
	पूर्ण;

	ret = __i2c_transfer(client->adapter, msg, 1);
	अगर (ret != 1) अणु
		dev_warn(&client->dev, "i2c reg write failed %d\n", ret);
		अगर (ret >= 0)
			ret = -EREMOTEIO;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_regmap_gather_ग_लिखो(व्योम *context, स्थिर व्योम *reg,
				       माप_प्रकार reg_len, स्थिर व्योम *val,
				       माप_प्रकार val_len)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक ret;
	u8 buf[256];
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 1 + val_len,
			.buf = buf,
		पूर्ण
	पूर्ण;

	buf[0] = *(u8 स्थिर *)reg;
	स_नकल(&buf[1], val, val_len);

	ret = __i2c_transfer(client->adapter, msg, 1);
	अगर (ret != 1) अणु
		dev_warn(&client->dev, "i2c reg write failed %d\n", ret);
		अगर (ret >= 0)
			ret = -EREMOTEIO;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl2830_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rtl2830_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा rtl2830_dev *dev;
	पूर्णांक ret;
	u8 u8पंचांगp;
	अटल स्थिर काष्ठा regmap_bus regmap_bus = अणु
		.पढ़ो = rtl2830_regmap_पढ़ो,
		.ग_लिखो = rtl2830_regmap_ग_लिखो,
		.gather_ग_लिखो = rtl2830_regmap_gather_ग_लिखो,
		.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_range_cfg regmap_range_cfg[] = अणु
		अणु
			.selector_reg     = 0x00,
			.selector_mask    = 0xff,
			.selector_shअगरt   = 0,
			.winकरोw_start     = 0,
			.winकरोw_len       = 0x100,
			.range_min        = 0 * 0x100,
			.range_max        = 5 * 0x100,
		पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits    =  8,
		.val_bits    =  8,
		.max_रेजिस्टर = 5 * 0x100,
		.ranges = regmap_range_cfg,
		.num_ranges = ARRAY_SIZE(regmap_range_cfg),
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	अगर (pdata == शून्य) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* allocate memory क्रम the पूर्णांकernal state */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* setup the state */
	i2c_set_clientdata(client, dev);
	dev->client = client;
	dev->pdata = client->dev.platक्रमm_data;
	dev->sleeping = true;
	dev->regmap = regmap_init(&client->dev, &regmap_bus, client,
				  &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* check अगर the demod is there */
	ret = rtl2830_bulk_पढ़ो(client, 0x000, &u8पंचांगp, 1);
	अगर (ret)
		जाओ err_regmap_निकास;

	/* create muxed i2c adapter क्रम tuner */
	dev->muxc = i2c_mux_alloc(client->adapter, &client->dev, 1, 0, 0,
				  rtl2830_select, शून्य);
	अगर (!dev->muxc) अणु
		ret = -ENOMEM;
		जाओ err_regmap_निकास;
	पूर्ण
	dev->muxc->priv = client;
	ret = i2c_mux_add_adapter(dev->muxc, 0, 0, 0);
	अगर (ret)
		जाओ err_regmap_निकास;

	/* create dvb frontend */
	स_नकल(&dev->fe.ops, &rtl2830_ops, माप(dev->fe.ops));
	dev->fe.demodulator_priv = client;

	/* setup callbacks */
	pdata->get_dvb_frontend = rtl2830_get_dvb_frontend;
	pdata->get_i2c_adapter = rtl2830_get_i2c_adapter;
	pdata->pid_filter = rtl2830_pid_filter;
	pdata->pid_filter_ctrl = rtl2830_pid_filter_ctrl;

	dev_info(&client->dev, "Realtek RTL2830 successfully attached\n");

	वापस 0;
err_regmap_निकास:
	regmap_निकास(dev->regmap);
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2830_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rtl2830_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	i2c_mux_del_adapters(dev->muxc);
	regmap_निकास(dev->regmap);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rtl2830_id_table[] = अणु
	अणु"rtl2830", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rtl2830_id_table);

अटल काष्ठा i2c_driver rtl2830_driver = अणु
	.driver = अणु
		.name			= "rtl2830",
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= rtl2830_probe,
	.हटाओ		= rtl2830_हटाओ,
	.id_table	= rtl2830_id_table,
पूर्ण;

module_i2c_driver(rtl2830_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Realtek RTL2830 DVB-T demodulator driver");
MODULE_LICENSE("GPL");
