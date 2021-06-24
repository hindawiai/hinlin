<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Panasonic MN88472 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 */

#समावेश "mn88472_priv.h"

अटल पूर्णांक mn88472_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक mn88472_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88472_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i, sपंचांगp;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2;
	u8 buf[5];

	अगर (!dev->active) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = regmap_पढ़ो(dev->regmap[0], 0x7f, &uपंचांगp);
		अगर (ret)
			जाओ err;
		अगर ((uपंचांगp & 0x0f) >= 0x09)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				  FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		अन्यथा
			*status = 0;
		अवरोध;
	हाल SYS_DVBT2:
		ret = regmap_पढ़ो(dev->regmap[2], 0x92, &uपंचांगp);
		अगर (ret)
			जाओ err;
		अगर ((uपंचांगp & 0x0f) >= 0x0d)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				  FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		अन्यथा अगर ((uपंचांगp & 0x0f) >= 0x0a)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				  FE_HAS_VITERBI;
		अन्यथा अगर ((uपंचांगp & 0x0f) >= 0x07)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		अन्यथा
			*status = 0;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = regmap_पढ़ो(dev->regmap[1], 0x84, &uपंचांगp);
		अगर (ret)
			जाओ err;
		अगर ((uपंचांगp & 0x0f) >= 0x08)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				  FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		अन्यथा
			*status = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Signal strength */
	अगर (*status & FE_HAS_SIGNAL) अणु
		क्रम (i = 0; i < 2; i++) अणु
			ret = regmap_bulk_पढ़ो(dev->regmap[2], 0x8e + i,
					       &buf[i], 1);
			अगर (ret)
				जाओ err;
		पूर्ण

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
		ret = regmap_bulk_पढ़ो(dev->regmap[0], 0x9c, buf, 2);
		अगर (ret)
			जाओ err;

		uपंचांगp = buf[0] << 8 | buf[1] << 0;
		अगर (uपंचांगp) अणु
			/* CNR[dB]: 10 * log10(65536 / value) + 2 */
			/* log10(65536) = 80807124, 0.2 = 3355443 */
			sपंचांगp = ((u64)80807124 - पूर्णांकlog10(uपंचांगp) + 3355443)
			       * 10000 >> 24;

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
			ret = regmap_bulk_पढ़ो(dev->regmap[2], 0xbc + i,
					       &buf[i], 1);
			अगर (ret)
				जाओ err;
		पूर्ण

		uपंचांगp = buf[1] << 8 | buf[2] << 0;
		uपंचांगp1 = (buf[0] >> 2) & 0x01; /* 0=SISO, 1=MISO */
		अगर (uपंचांगp) अणु
			अगर (uपंचांगp1) अणु
				/* CNR[dB]: 10 * log10(16384 / value) - 6 */
				/* log10(16384) = 70706234, 0.6 = 10066330 */
				sपंचांगp = ((u64)70706234 - पूर्णांकlog10(uपंचांगp)
				       - 10066330) * 10000 >> 24;
				dev_dbg(&client->dev, "cnr=%d value=%u MISO\n",
					sपंचांगp, uपंचांगp);
			पूर्ण अन्यथा अणु
				/* CNR[dB]: 10 * log10(65536 / value) + 2 */
				/* log10(65536) = 80807124, 0.2 = 3355443 */
				sपंचांगp = ((u64)80807124 - पूर्णांकlog10(uपंचांगp)
				       + 3355443) * 10000 >> 24;

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
			sपंचांगp = ((u64)15151336 + पूर्णांकlog10(uपंचांगp1)
			       - पूर्णांकlog10(uपंचांगp2)) * 10000 >> 24;

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

	/* PER */
	अगर (*status & FE_HAS_SYNC) अणु
		ret = regmap_bulk_पढ़ो(dev->regmap[0], 0xe1, buf, 4);
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

अटल पूर्णांक mn88472_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88472_dev *dev = i2c_get_clientdata(client);
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uपंचांगp;
	u32 अगर_frequency;
	u8 buf[3], delivery_प्रणाली_val, bandwidth_val, *bandwidth_vals_ptr;
	u8 reg_bank0_b4_val, reg_bank0_cd_val, reg_bank0_d4_val;
	u8 reg_bank0_d6_val;

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
		reg_bank0_b4_val = 0x00;
		reg_bank0_cd_val = 0x1f;
		reg_bank0_d4_val = 0x0a;
		reg_bank0_d6_val = 0x48;
		अवरोध;
	हाल SYS_DVBT2:
		delivery_प्रणाली_val = 0x03;
		reg_bank0_b4_val = 0xf6;
		reg_bank0_cd_val = 0x01;
		reg_bank0_d4_val = 0x09;
		reg_bank0_d6_val = 0x46;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		delivery_प्रणाली_val = 0x04;
		reg_bank0_b4_val = 0x00;
		reg_bank0_cd_val = 0x17;
		reg_bank0_d4_val = 0x09;
		reg_bank0_d6_val = 0x48;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		चयन (c->bandwidth_hz) अणु
		हाल 5000000:
			bandwidth_vals_ptr = "\xe5\x99\x9a\x1b\xa9\x1b\xa9";
			bandwidth_val = 0x03;
			अवरोध;
		हाल 6000000:
			bandwidth_vals_ptr = "\xbf\x55\x55\x15\x6b\x15\x6b";
			bandwidth_val = 0x02;
			अवरोध;
		हाल 7000000:
			bandwidth_vals_ptr = "\xa4\x00\x00\x0f\x2c\x0f\x2c";
			bandwidth_val = 0x01;
			अवरोध;
		हाल 8000000:
			bandwidth_vals_ptr = "\x8f\x80\x00\x08\xee\x08\xee";
			bandwidth_val = 0x00;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		bandwidth_vals_ptr = शून्य;
		bandwidth_val = 0x00;
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

		dev_dbg(&client->dev, "get_if_frequency=%d\n", अगर_frequency);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap[2], 0x00, 0x66);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x01, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x02, 0x01);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x03, delivery_प्रणाली_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x04, bandwidth_val);
	अगर (ret)
		जाओ err;

	/* IF */
	uपंचांगp = DIV_ROUND_CLOSEST_ULL((u64)अगर_frequency * 0x1000000, dev->clk);
	buf[0] = (uपंचांगp >> 16) & 0xff;
	buf[1] = (uपंचांगp >>  8) & 0xff;
	buf[2] = (uपंचांगp >>  0) & 0xff;
	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_ग_लिखो(dev->regmap[2], 0x10 + i, buf[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Bandwidth */
	अगर (bandwidth_vals_ptr) अणु
		क्रम (i = 0; i < 7; i++) अणु
			ret = regmap_ग_लिखो(dev->regmap[2], 0x13 + i,
					   bandwidth_vals_ptr[i]);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap[0], 0xb4, reg_bank0_b4_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xcd, reg_bank0_cd_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xd4, reg_bank0_d4_val);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[0], 0xd6, reg_bank0_d6_val);
	अगर (ret)
		जाओ err;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		ret = regmap_ग_लिखो(dev->regmap[0], 0x07, 0x26);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो(dev->regmap[0], 0x00, 0xba);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो(dev->regmap[0], 0x01, 0x13);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल SYS_DVBT2:
		ret = regmap_ग_लिखो(dev->regmap[2], 0x2b, 0x13);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो(dev->regmap[2], 0x4f, 0x05);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो(dev->regmap[1], 0xf6, 0x05);
		अगर (ret)
			जाओ err;
		ret = regmap_ग_लिखो(dev->regmap[2], 0x32,
				(c->stream_id == NO_STREAM_ID_FILTER) ? 0 :
				c->stream_id );
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		अवरोध;
	शेष:
		अवरोध;
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

अटल पूर्णांक mn88472_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88472_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret, len, rem;
	अचिन्हित पूर्णांक uपंचांगp;
	स्थिर काष्ठा firmware *firmware;
	स्थिर अक्षर *name = MN88472_FIRMWARE;

	dev_dbg(&client->dev, "\n");

	/* Power up */
	ret = regmap_ग_लिखो(dev->regmap[2], 0x05, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x0b, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x0c, 0x00);
	अगर (ret)
		जाओ err;

	/* Check अगर firmware is alपढ़ोy running */
	ret = regmap_पढ़ो(dev->regmap[0], 0xf5, &uपंचांगp);
	अगर (ret)
		जाओ err;
	अगर (!(uपंचांगp & 0x01))
		जाओ warm;

	ret = request_firmware(&firmware, name, &client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "firmware file '%s' not found\n", name);
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "downloading firmware from file '%s'\n", name);

	ret = regmap_ग_लिखो(dev->regmap[0], 0xf5, 0x03);
	अगर (ret)
		जाओ err_release_firmware;

	क्रम (rem = firmware->size; rem > 0; rem -= (dev->i2c_ग_लिखो_max - 1)) अणु
		len = min(dev->i2c_ग_लिखो_max - 1, rem);
		ret = regmap_bulk_ग_लिखो(dev->regmap[0], 0xf6,
					&firmware->data[firmware->size - rem],
					len);
		अगर (ret) अणु
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			जाओ err_release_firmware;
		पूर्ण
	पूर्ण

	/* Parity check of firmware */
	ret = regmap_पढ़ो(dev->regmap[0], 0xf8, &uपंचांगp);
	अगर (ret)
		जाओ err_release_firmware;
	अगर (uपंचांगp & 0x10) अणु
		ret = -EINVAL;
		dev_err(&client->dev, "firmware did not run\n");
		जाओ err_release_firmware;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap[0], 0xf5, 0x00);
	अगर (ret)
		जाओ err_release_firmware;

	release_firmware(firmware);
warm:
	/* TS config */
	चयन (dev->ts_mode) अणु
	हाल SERIAL_TS_MODE:
		uपंचांगp = 0x1d;
		अवरोध;
	हाल PARALLEL_TS_MODE:
		uपंचांगp = 0x00;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	ret = regmap_ग_लिखो(dev->regmap[2], 0x08, uपंचांगp);
	अगर (ret)
		जाओ err;

	चयन (dev->ts_clk) अणु
	हाल VARIABLE_TS_CLOCK:
		uपंचांगp = 0xe3;
		अवरोध;
	हाल FIXED_TS_CLOCK:
		uपंचांगp = 0xe1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	ret = regmap_ग_लिखो(dev->regmap[0], 0xd9, uपंचांगp);
	अगर (ret)
		जाओ err;

	dev->active = true;

	वापस 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mn88472_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_client *client = fe->demodulator_priv;
	काष्ठा mn88472_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	/* Power करोwn */
	ret = regmap_ग_लिखो(dev->regmap[2], 0x0c, 0x30);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x0b, 0x30);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap[2], 0x05, 0x3e);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mn88472_ops = अणु
	.delsys = अणुSYS_DVBT, SYS_DVBT2, SYS_DVBC_ANNEX_Aपूर्ण,
	.info = अणु
		.name = "Panasonic MN88472",
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

	.get_tune_settings = mn88472_get_tune_settings,

	.init = mn88472_init,
	.sleep = mn88472_sleep,

	.set_frontend = mn88472_set_frontend,

	.पढ़ो_status = mn88472_पढ़ो_status,
पूर्ण;

अटल काष्ठा dvb_frontend *mn88472_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा mn88472_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &dev->fe;
पूर्ण

अटल पूर्णांक mn88472_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mn88472_config *pdata = client->dev.platक्रमm_data;
	काष्ठा mn88472_dev *dev;
	काष्ठा dtv_frontend_properties *c;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->i2c_ग_लिखो_max = pdata->i2c_wr_max ? pdata->i2c_wr_max : ~0;
	dev->clk = pdata->xtal;
	dev->ts_mode = pdata->ts_mode;
	dev->ts_clk = pdata->ts_घड़ी;
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
	ret = regmap_पढ़ो(dev->regmap[2], 0xff, &uपंचांगp);
	अगर (ret)
		जाओ err_regmap_2_regmap_निकास;

	dev_dbg(&client->dev, "chip id=%02x\n", uपंचांगp);

	अगर (uपंचांगp != 0x02) अणु
		ret = -ENODEV;
		जाओ err_regmap_2_regmap_निकास;
	पूर्ण

	/* Sleep because chip is active by शेष */
	ret = regmap_ग_लिखो(dev->regmap[2], 0x05, 0x3e);
	अगर (ret)
		जाओ err_regmap_2_regmap_निकास;

	/* Create dvb frontend */
	स_नकल(&dev->fe.ops, &mn88472_ops, माप(काष्ठा dvb_frontend_ops));
	dev->fe.demodulator_priv = client;
	*pdata->fe = &dev->fe;
	i2c_set_clientdata(client, dev);

	/* Init stats to indicate which stats are supported */
	c = &dev->fe.dtv_property_cache;
	c->strength.len = 1;
	c->cnr.len = 1;
	c->block_error.len = 1;
	c->block_count.len = 1;

	/* Setup callbacks */
	pdata->get_dvb_frontend = mn88472_get_dvb_frontend;

	dev_info(&client->dev, "Panasonic MN88472 successfully identified\n");

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

अटल पूर्णांक mn88472_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mn88472_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	regmap_निकास(dev->regmap[2]);
	i2c_unरेजिस्टर_device(dev->client[2]);

	regmap_निकास(dev->regmap[1]);
	i2c_unरेजिस्टर_device(dev->client[1]);

	regmap_निकास(dev->regmap[0]);

	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mn88472_id_table[] = अणु
	अणु"mn88472", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mn88472_id_table);

अटल काष्ठा i2c_driver mn88472_driver = अणु
	.driver = अणु
		.name = "mn88472",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe    = mn88472_probe,
	.हटाओ   = mn88472_हटाओ,
	.id_table = mn88472_id_table,
पूर्ण;

module_i2c_driver(mn88472_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Panasonic MN88472 DVB-T/T2/C demodulator driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(MN88472_FIRMWARE);
