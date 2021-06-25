<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Panasonic MN88473 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश "mn88473_priv.h"

अटल पूर्णांक mn88473_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक mn88473_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88473_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uiपंचांगp;
	u32 अगर_frequency;
	u8 delivery_प्रणाली_val, अगर_val[3], *conf_val_ptr;
	u8 reg_bank2_2d_val, reg_bank0_d2_val;

	dev_dbg(&client->dev,
		"delivery_system=%u modulation=%u frequency=%u bandwidth_hz=%u symbol_rate=%u inversion=%d stream_id=%d\n",
		c->delivery_प्रणाली, c->modulation, c->frequency,
		c->bandwidth_hz, c->symbol_rate, c->inversion, c->stream_id);

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		delivery_प्रणाली_val = 0x02;
		reg_bank2_2d_val = 0x23;
		reg_bank0_d2_val = 0x2a;
		अवरोध;
	हाल SYS_DVBT2:
		delivery_प्रणाली_val = 0x03;
		reg_bank2_2d_val = 0x3b;
		reg_bank0_d2_val = 0x29;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		delivery_प्रणाली_val = 0x04;
		reg_bank2_2d_val = 0x3b;
		reg_bank0_d2_val = 0x29;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			conf_val_ptr = "\xe9\x55\x55\x1c\x29\x1c\x29";
			अवरोध;
		हाल 7000000:
			conf_val_ptr = "\xc8\x00\x00\x17\x0a\x17\x0a";
			अवरोध;
		हाल 8000000:
			conf_val_ptr = "\xaf\x00\x00\x11\xec\x11\xec";
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		conf_val_ptr = "\x10\xab\x0d\xae\x1d\x9d";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Program tuner */
	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (fe->ops.tuner_ops.get_अगर_frequency) अणु
		ret = fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_frequency);
		अगर (ret)
			जाओ err;

		dev_dbg(&client->dev, "get_if_frequency=%u\n", अगर_frequency);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Calculate IF रेजिस्टरs */
	uiपंचांगp = DIV_ROUND_CLOSEST_ULL((u64) अगर_frequency * 0x1000000, dev->clk);
	अगर_val[0] = (uiपंचांगp >> 16) & 0xff;
	अगर_val[1] = (uiपंचांगp >>  8) & 0xff;
	अगर_val[2] = (uiपंचांगp >>  0) & 0xff;

	ret = regmap_ग_लिखो(dev->regmap[2], 0x05, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0xfb, 0x13);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0xef, 0x13);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0xf9, 0x13);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x00, 0x18);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x01, 0x01);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x02, 0x21);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x03, delivery_प्रणाली_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x0b, 0x00);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < माप(अगर_val); i++) अणु
		ret = regmap_ग_लिखो(dev->regmap[2], 0x10 + i, अगर_val[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		क्रम (i = 0; i < 7; i++) अणु
			ret = regmap_ग_लिखो(dev->regmap[2], 0x13 + i,
					   conf_val_ptr[i]);
			अगर (ret)
				जाओ err;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = regmap_bulk_ग_लिखो(dev->regmap[1], 0x10, conf_val_ptr, 6);
		अगर (ret)
			जाओ err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap[2], 0x2d, reg_bank2_2d_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x2e, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x56, 0x0d);
	अगर (ret)
		जाओ err;
	ret = regmap_bulk_ग_लिखो(dev->regmap[0], 0x01,
				"\xba\x13\x80\xba\x91\xdd\xe7\x28", 8);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x0a, 0x1a);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x13, 0x1f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x19, 0x03);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x1d, 0xb0);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x2a, 0x72);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x2d, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x3c, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0x3f, 0xf8);
	अगर (ret)
		जाओ err;
	ret = regmap_bulk_ग_लिखो(dev->regmap[0], 0x40, "\xf4\x08", 2);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xd2, reg_bank0_d2_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xd4, 0x55);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[1], 0xbe, 0x08);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xb2, 0x37);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xd7, 0x04);
	अगर (ret)
		जाओ err;

	/* PLP */
	अगर (c->delivery_प्रणाली == SYS_DVBT2) अणु
		ret = regmap_ग_लिखो(dev->regmap[2], 0x36,
				(c->stream_id == NO_STREAM_ID_FILTER) ? 0 :
				c->stream_id );
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Reset FSM */
	ret = regmap_ग_लिखो(dev->regmap[2], 0xf8, 0x9f);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mn88473_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88473_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i, sपंचांगp;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2;
	u8 buf[5];

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	/* Lock detection */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = regmap_पढ़ो(dev->regmap[0], 0x62, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर (!(uपंचांगp & 0xa0)) अणु
			अगर ((uपंचांगp & 0x0f) >= 0x09)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					  FE_HAS_VITERBI | FE_HAS_SYNC |
					  FE_HAS_LOCK;
			अन्यथा अगर ((uपंचांगp & 0x0f) >= 0x03)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		पूर्ण अन्यथा अणु
			*status = 0;
		पूर्ण
		अवरोध;
	हाल SYS_DVBT2:
		ret = regmap_पढ़ो(dev->regmap[2], 0x8b, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर (!(uपंचांगp & 0x40)) अणु
			अगर ((uपंचांगp & 0x0f) >= 0x0d)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					  FE_HAS_VITERBI | FE_HAS_SYNC |
					  FE_HAS_LOCK;
			अन्यथा अगर ((uपंचांगp & 0x0f) >= 0x0a)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					  FE_HAS_VITERBI;
			अन्यथा अगर ((uपंचांगp & 0x0f) >= 0x07)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		पूर्ण अन्यथा अणु
			*status = 0;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = regmap_पढ़ो(dev->regmap[1], 0x85, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर (!(uपंचांगp & 0x40)) अणु
			ret = regmap_पढ़ो(dev->regmap[1], 0x89, &uपंचांगp);
			अगर (ret)
				जाओ err;

			अगर (uपंचांगp & 0x01)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
						FE_HAS_VITERBI | FE_HAS_SYNC |
						FE_HAS_LOCK;
		पूर्ण अन्यथा अणु
			*status = 0;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Signal strength */
	अगर (*status & FE_HAS_SIGNAL) अणु
		क्रम (i = 0; i < 2; i++) अणु
			ret = regmap_bulk_पढ़ो(dev->regmap[2], 0x86 + i,
					       &buf[i], 1);
			अगर (ret)
				जाओ err;
		पूर्ण

		/* AGCRD[15:6] gives us a 10bit value ([5:0] are always 0) */
		uपंचांगp1 = buf[0] << 8 | buf[1] << 0 | buf[0] >> 2;
		dev_dbg(&client->dev, "strength=%u\n", uपंचांगp1);

		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = uपंचांगp1;
	पूर्ण अन्यथा अणु
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (*status & FE_HAS_VITERBI && c->delivery_प्रणाली == SYS_DVBT) अणु
		/* DVB-T CNR */
		ret = regmap_bulk_पढ़ो(dev->regmap[0], 0x8f, buf, 2);
		अगर (ret)
			जाओ err;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		अगर (uपंचांगp) अणु
			/* CNR[dB]: 10 * (log10(65536 / value) + 0.2) */
			/* log10(65536) = 80807124, 0.2 = 3355443 */
			sपंचांगp = भाग_u64(((u64)80807124 - पूर्णांकlog10(uपंचांगp)
					+ 3355443) * 10000, 1 << 24);
			dev_dbg(&client->dev, "cnr=%d value=%u\n", sपंचांगp, uपंचांगp);
		पूर्ण अन्यथा अणु
			sपंचांगp = 0;
		पूर्ण

		c->cnr.stat[0].svalue = sपंचांगp;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण अन्यथा अगर (*status & FE_HAS_VITERBI &&
		   c->delivery_प्रणाली == SYS_DVBT2) अणु
		/* DVB-T2 CNR */
		क्रम (i = 0; i < 3; i++) अणु
			ret = regmap_bulk_पढ़ो(dev->regmap[2], 0xb7 + i,
					       &buf[i], 1);
			अगर (ret)
				जाओ err;
		पूर्ण

		uपंचांगp = buf[1] << 8 | buf[2] << 0;
		uपंचांगp1 = (buf[0] >> 2) & 0x01; /* 0=SISO, 1=MISO */
		अगर (uपंचांगp) अणु
			अगर (uपंचांगp1) अणु
				/* CNR[dB]: 10 * (log10(16384 / value) - 0.6) */
				/* log10(16384) = 70706234, 0.6 = 10066330 */
				sपंचांगp = भाग_u64(((u64)70706234 - पूर्णांकlog10(uपंचांगp)
						- 10066330) * 10000, 1 << 24);
				dev_dbg(&client->dev, "cnr=%d value=%u MISO\n",
					sपंचांगp, uपंचांगp);
			पूर्ण अन्यथा अणु
				/* CNR[dB]: 10 * (log10(65536 / value) + 0.2) */
				/* log10(65536) = 80807124, 0.2 = 3355443 */
				sपंचांगp = भाग_u64(((u64)80807124 - पूर्णांकlog10(uपंचांगp)
						+ 3355443) * 10000, 1 << 24);
				dev_dbg(&client->dev, "cnr=%d value=%u SISO\n",
					sपंचांगp, uपंचांगp);
			पूर्ण
		पूर्ण अन्यथा अणु
			sपंचांगp = 0;
		पूर्ण

		c->cnr.stat[0].svalue = sपंचांगp;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण अन्यथा अगर (*status & FE_HAS_VITERBI &&
		   c->delivery_प्रणाली == SYS_DVBC_ANNEX_A) अणु
		/* DVB-C CNR */
		ret = regmap_bulk_पढ़ो(dev->regmap[1], 0xa1, buf, 4);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = buf[0] << 8 | buf[1] << 0; /* संकेत */
		uपंचांगp2 = buf[2] << 8 | buf[3] << 0; /* noise */
		अगर (uपंचांगp1 && uपंचांगp2) अणु
			/* CNR[dB]: 10 * log10(8 * (संकेत / noise)) */
			/* log10(8) = 15151336 */
			sपंचांगp = भाग_u64(((u64)15151336 + पूर्णांकlog10(uपंचांगp1)
					- पूर्णांकlog10(uपंचांगp2)) * 10000, 1 << 24);
			dev_dbg(&client->dev, "cnr=%d signal=%u noise=%u\n",
				sपंचांगp, uपंचांगp1, uपंचांगp2);
		पूर्ण अन्यथा अणु
			sपंचांगp = 0;
		पूर्ण

		c->cnr.stat[0].svalue = sपंचांगp;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* BER */
	अगर (*status & FE_HAS_LOCK && (c->delivery_प्रणाली == SYS_DVBT ||
				      c->delivery_प्रणाली == SYS_DVBC_ANNEX_A)) अणु
		/* DVB-T & DVB-C BER */
		ret = regmap_bulk_पढ़ो(dev->regmap[0], 0x92, buf, 5);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = buf[0] << 16 | buf[1] << 8 | buf[2] << 0;
		uपंचांगp2 = buf[3] << 8 | buf[4] << 0;
		uपंचांगp2 = uपंचांगp2 * 8 * 204;
		dev_dbg(&client->dev, "post_bit_error=%u post_bit_count=%u\n",
			uपंचांगp1, uपंचांगp2);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += uपंचांगp1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += uपंचांगp2;
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* PER */
	अगर (*status & FE_HAS_LOCK) अणु
		ret = regmap_bulk_पढ़ो(dev->regmap[0], 0xdd, buf, 4);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = buf[0] << 8 | buf[1] << 0;
		uपंचांगp2 = buf[2] << 8 | buf[3] << 0;
		dev_dbg(&client->dev, "block_error=%u block_count=%u\n",
			uपंचांगp1, uपंचांगp2);

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue += uपंचांगp1;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue += uपंचांगp2;
	पूर्ण अन्यथा अणु
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mn88473_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88473_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, len, reमुख्य;
	अचिन्हित पूर्णांक uiपंचांगp;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *name = MN88473_FIRMWARE;

	dev_dbg(&client->dev, "\n");

	/* Check अगर firmware is alपढ़ोy running */
	ret = regmap_पढ़ो(dev->regmap[0], 0xf5, &uiपंचांगp);
	अगर (ret)
		जाओ err;

	अगर (!(uiपंचांगp & 0x01))
		जाओ warm;

	/* Request the firmware, this will block and समयout */
	ret = request_firmware(&fw, name, &client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "firmware file '%s' not found\n", name);
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "downloading firmware from file '%s'\n", name);

	ret = regmap_ग_लिखो(dev->regmap[0], 0xf5, 0x03);
	अगर (ret)
		जाओ err_release_firmware;

	क्रम (reमुख्य = fw->size; reमुख्य > 0; reमुख्य -= (dev->i2c_wr_max - 1)) अणु
		len = min(dev->i2c_wr_max - 1, reमुख्य);
		ret = regmap_bulk_ग_लिखो(dev->regmap[0], 0xf6,
					&fw->data[fw->size - reमुख्य], len);
		अगर (ret) अणु
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			जाओ err_release_firmware;
		पूर्ण
	पूर्ण

	release_firmware(fw);

	/* Parity check of firmware */
	ret = regmap_पढ़ो(dev->regmap[0], 0xf8, &uiपंचांगp);
	अगर (ret)
		जाओ err;

	अगर (uiपंचांगp & 0x10) अणु
		dev_err(&client->dev, "firmware parity check failed\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap[0], 0xf5, 0x00);
	अगर (ret)
		जाओ err;
warm:
	/* TS config */
	ret = regmap_ग_लिखो(dev->regmap[2], 0x09, 0x08);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x08, 0x1d);
	अगर (ret)
		जाओ err;

	dev->active = true;

	/* init stats here to indicate which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
err_release_firmware:
	release_firmware(fw);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mn88473_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88473_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	ret = regmap_ग_लिखो(dev->regmap[2], 0x05, 0x3e);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mn88473_ops = अणु
	.delsys = अणुSYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_Aपूर्ण,
	.info = अणु
		.name = "Panasonic MN88473",
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 7200000,
		.caps =	FE_CAN_FEC_1_2                 |
			FE_CAN_FEC_2_3                 |
			FE_CAN_FEC_3_4                 |
			FE_CAN_FEC_5_6                 |
			FE_CAN_FEC_7_8                 |
			FE_CAN_FEC_AUTO                |
			FE_CAN_QPSK                    |
			FE_CAN_QAM_16                  |
			FE_CAN_QAM_32                  |
			FE_CAN_QAM_64                  |
			FE_CAN_QAM_128                 |
			FE_CAN_QAM_256                 |
			FE_CAN_QAM_AUTO                |
			FE_CAN_TRANSMISSION_MODE_AUTO  |
			FE_CAN_GUARD_INTERVAL_AUTO     |
			FE_CAN_HIERARCHY_AUTO          |
			FE_CAN_MUTE_TS                 |
			FE_CAN_2G_MODULATION           |
			FE_CAN_MULTISTREAM
	पूर्ण,

	.get_tune_settings = mn88473_get_tune_settings,

	.init = mn88473_init,
	.sleep = mn88473_sleep,

	.set_frontend = mn88473_set_frontend,

	.पढ़ो_status = mn88473_पढ़ो_status,
पूर्ण;

अटल पूर्णांक mn88473_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mn88473_config *config = client->dev.platक्रमm_data;
	काष्ठा mn88473_dev *dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uiपंचांगp;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	/* Caller really need to provide poपूर्णांकer क्रम frontend we create */
	अगर (config->fe == शून्य) अणु
		dev_err(&client->dev, "frontend pointer not defined\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (config->i2c_wr_max)
		dev->i2c_wr_max = config->i2c_wr_max;
	अन्यथा
		dev->i2c_wr_max = ~0;

	अगर (config->xtal)
		dev->clk = config->xtal;
	अन्यथा
		dev->clk = 25000000;
	dev->client[0] = client;
	dev->regmap[0] = regmap_init_i2c(dev->client[0], &regmap_config);
	अगर (IS_ERR(dev->regmap[0])) अणु
		ret = PTR_ERR(dev->regmap[0]);
		जाओ err_kमुक्त;
	पूर्ण

	/*
	 * Chip has three I2C addresses क्रम dअगरferent रेजिस्टर banks. Used
	 * addresses are 0x18, 0x1a and 0x1c. We रेजिस्टर two dummy clients,
	 * 0x1a and 0x1c, in order to get own I2C client क्रम each रेजिस्टर bank.
	 *
	 * Also, रेजिस्टर bank 2 करो not support sequential I/O. Only single
	 * रेजिस्टर ग_लिखो or पढ़ो is allowed to that bank.
	 */
	dev->client[1] = i2c_new_dummy_device(client->adapter, 0x1a);
	अगर (IS_ERR(dev->client[1])) अणु
		ret = PTR_ERR(dev->client[1]);
		dev_err(&client->dev, "I2C registration failed\n");
		जाओ err_regmap_0_regmap_निकास;
	पूर्ण
	dev->regmap[1] = regmap_init_i2c(dev->client[1], &regmap_config);
	अगर (IS_ERR(dev->regmap[1])) अणु
		ret = PTR_ERR(dev->regmap[1]);
		जाओ err_client_1_i2c_unरेजिस्टर_device;
	पूर्ण
	i2c_set_clientdata(dev->client[1], dev);

	dev->client[2] = i2c_new_dummy_device(client->adapter, 0x1c);
	अगर (IS_ERR(dev->client[2])) अणु
		ret = PTR_ERR(dev->client[2]);
		dev_err(&client->dev, "2nd I2C registration failed\n");
		जाओ err_regmap_1_regmap_निकास;
	पूर्ण
	dev->regmap[2] = regmap_init_i2c(dev->client[2], &regmap_config);
	अगर (IS_ERR(dev->regmap[2])) अणु
		ret = PTR_ERR(dev->regmap[2]);
		जाओ err_client_2_i2c_unरेजिस्टर_device;
	पूर्ण
	i2c_set_clientdata(dev->client[2], dev);

	/* Check demod answers with correct chip id */
	ret = regmap_पढ़ो(dev->regmap[2], 0xff, &uiपंचांगp);
	अगर (ret)
		जाओ err_regmap_2_regmap_निकास;

	dev_dbg(&client->dev, "chip id=%02x\n", uiपंचांगp);

	अगर (uiपंचांगp != 0x03) अणु
		ret = -ENODEV;
		जाओ err_regmap_2_regmap_निकास;
	पूर्ण

	/* Sleep because chip is active by शेष */
	ret = regmap_ग_लिखो(dev->regmap[2], 0x05, 0x3e);
	अगर (ret)
		जाओ err_regmap_2_regmap_निकास;

	/* Create dvb frontend */
	स_नकल(&dev->frontend.ops, &mn88473_ops, माप(dev->frontend.ops));
	dev->frontend.demodulator_priv = client;
	*config->fe = &dev->frontend;
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "Panasonic MN88473 successfully identified\n");

	वापस 0;
err_regmap_2_regmap_निकास:
	regmap_निकास(dev->regmap[2]);
err_client_2_i2c_unरेजिस्टर_device:
	i2c_unरेजिस्टर_device(dev->client[2]);
err_regmap_1_regmap_निकास:
	regmap_निकास(dev->regmap[1]);
err_client_1_i2c_unरेजिस्टर_device:
	i2c_unरेजिस्टर_device(dev->client[1]);
err_regmap_0_regmap_निकास:
	regmap_निकास(dev->regmap[0]);
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mn88473_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mn88473_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	regmap_निकास(dev->regmap[2]);
	i2c_unरेजिस्टर_device(dev->client[2]);

	regmap_निकास(dev->regmap[1]);
	i2c_unरेजिस्टर_device(dev->client[1]);

	regmap_निकास(dev->regmap[0]);

	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mn88473_id_table[] = अणु
	अणु"mn88473", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mn88473_id_table);

अटल काष्ठा i2c_driver mn88473_driver = अणु
	.driver = अणु
		.name		     = "mn88473",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= mn88473_probe,
	.हटाओ		= mn88473_हटाओ,
	.id_table	= mn88473_id_table,
पूर्ण;

module_i2c_driver(mn88473_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Panasonic MN88473 DVB-T/T2/C demodulator driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(MN88473_FIRMWARE);
