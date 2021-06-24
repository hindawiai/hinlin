<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Afatech AF9013 demodulator driver
 *
 * Copyright (C) 2007 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 */

#समावेश "af9013_priv.h"

काष्ठा af9013_state अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा dvb_frontend fe;
	u32 clk;
	u8 tuner;
	u32 अगर_frequency;
	u8 ts_mode;
	u8 ts_output_pin;
	bool spec_inv;
	u8 api_version[4];
	u8 gpio[4];

	u32 bandwidth_hz;
	क्रमागत fe_status fe_status;
	/* RF and IF AGC limits used क्रम संकेत strength calc */
	u8 strength_en, rf_agc_50, rf_agc_80, अगर_agc_50, अगर_agc_80;
	अचिन्हित दीर्घ set_frontend_jअगरfies;
	अचिन्हित दीर्घ पढ़ो_status_jअगरfies;
	अचिन्हित दीर्घ strength_jअगरfies;
	अचिन्हित दीर्घ cnr_jअगरfies;
	अचिन्हित दीर्घ ber_ucb_jअगरfies;
	u16 dvbv3_snr;
	u16 dvbv3_strength;
	u32 dvbv3_ber;
	u32 dvbv3_ucblocks;
	bool first_tune;
पूर्ण;

अटल पूर्णांक af9013_set_gpio(काष्ठा af9013_state *state, u8 gpio, u8 gpioval)
अणु
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;
	u8 pos;
	u16 addr;

	dev_dbg(&client->dev, "gpio %u, gpioval %02x\n", gpio, gpioval);

	/*
	 * GPIO0 & GPIO1 0xd735
	 * GPIO2 & GPIO3 0xd736
	 */

	चयन (gpio) अणु
	हाल 0:
	हाल 1:
		addr = 0xd735;
		अवरोध;
	हाल 2:
	हाल 3:
		addr = 0xd736;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	चयन (gpio) अणु
	हाल 0:
	हाल 2:
		pos = 0;
		अवरोध;
	हाल 1:
	हाल 3:
	शेष:
		pos = 4;
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(state->regmap, addr, 0x0f << pos,
				 gpioval << pos);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	fesettings->min_delay_ms = 800;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक af9013_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i, sampling_freq;
	bool स्वतः_mode, spec_inv;
	u8 buf[6];
	u32 अगर_frequency, freq_cw;

	dev_dbg(&client->dev, "frequency %u, bandwidth_hz %u\n",
		c->frequency, c->bandwidth_hz);

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* program CFOE coefficients */
	अगर (c->bandwidth_hz != state->bandwidth_hz) अणु
		क्रम (i = 0; i < ARRAY_SIZE(coeff_lut); i++) अणु
			अगर (coeff_lut[i].घड़ी == state->clk &&
				coeff_lut[i].bandwidth_hz == c->bandwidth_hz) अणु
				अवरोध;
			पूर्ण
		पूर्ण

		/* Return an error अगर can't find bandwidth or the right घड़ी */
		अगर (i == ARRAY_SIZE(coeff_lut)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = regmap_bulk_ग_लिखो(state->regmap, 0xae00, coeff_lut[i].val,
					माप(coeff_lut[i].val));
		अगर (ret)
			जाओ err;
	पूर्ण

	/* program frequency control */
	अगर (c->bandwidth_hz != state->bandwidth_hz || state->first_tune) अणु
		/* get used IF frequency */
		अगर (fe->ops.tuner_ops.get_अगर_frequency) अणु
			ret = fe->ops.tuner_ops.get_अगर_frequency(fe,
								 &अगर_frequency);
			अगर (ret)
				जाओ err;
		पूर्ण अन्यथा अणु
			अगर_frequency = state->अगर_frequency;
		पूर्ण

		dev_dbg(&client->dev, "if_frequency %u\n", अगर_frequency);

		sampling_freq = अगर_frequency;

		जबतक (sampling_freq > (state->clk / 2))
			sampling_freq -= state->clk;

		अगर (sampling_freq < 0) अणु
			sampling_freq *= -1;
			spec_inv = state->spec_inv;
		पूर्ण अन्यथा अणु
			spec_inv = !state->spec_inv;
		पूर्ण

		freq_cw = DIV_ROUND_CLOSEST_ULL((u64)sampling_freq * 0x800000,
						state->clk);

		अगर (spec_inv)
			freq_cw = 0x800000 - freq_cw;

		buf[0] = (freq_cw >>  0) & 0xff;
		buf[1] = (freq_cw >>  8) & 0xff;
		buf[2] = (freq_cw >> 16) & 0x7f;

		freq_cw = 0x800000 - freq_cw;

		buf[3] = (freq_cw >>  0) & 0xff;
		buf[4] = (freq_cw >>  8) & 0xff;
		buf[5] = (freq_cw >> 16) & 0x7f;

		ret = regmap_bulk_ग_लिखो(state->regmap, 0xd140, buf, 3);
		अगर (ret)
			जाओ err;

		ret = regmap_bulk_ग_लिखो(state->regmap, 0x9be7, buf, 6);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* clear TPS lock flag */
	ret = regmap_update_bits(state->regmap, 0xd330, 0x08, 0x08);
	अगर (ret)
		जाओ err;

	/* clear MPEG2 lock flag */
	ret = regmap_update_bits(state->regmap, 0xd507, 0x40, 0x00);
	अगर (ret)
		जाओ err;

	/* empty channel function */
	ret = regmap_update_bits(state->regmap, 0x9bfe, 0x01, 0x00);
	अगर (ret)
		जाओ err;

	/* empty DVB-T channel function */
	ret = regmap_update_bits(state->regmap, 0x9bc2, 0x01, 0x00);
	अगर (ret)
		जाओ err;

	/* transmission parameters */
	स्वतः_mode = false;
	स_रखो(buf, 0, 3);

	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_AUTO:
		स्वतः_mode = true;
		अवरोध;
	हाल TRANSMISSION_MODE_2K:
		अवरोध;
	हाल TRANSMISSION_MODE_8K:
		buf[0] |= (1 << 0);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid transmission_mode\n");
		स्वतः_mode = true;
	पूर्ण

	चयन (c->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_AUTO:
		स्वतः_mode = true;
		अवरोध;
	हाल GUARD_INTERVAL_1_32:
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		buf[0] |= (1 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		buf[0] |= (2 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		buf[0] |= (3 << 2);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid guard_interval\n");
		स्वतः_mode = true;
	पूर्ण

	चयन (c->hierarchy) अणु
	हाल HIERARCHY_AUTO:
		स्वतः_mode = true;
		अवरोध;
	हाल HIERARCHY_NONE:
		अवरोध;
	हाल HIERARCHY_1:
		buf[0] |= (1 << 4);
		अवरोध;
	हाल HIERARCHY_2:
		buf[0] |= (2 << 4);
		अवरोध;
	हाल HIERARCHY_4:
		buf[0] |= (3 << 4);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid hierarchy\n");
		स्वतः_mode = true;
	पूर्ण

	चयन (c->modulation) अणु
	हाल QAM_AUTO:
		स्वतः_mode = true;
		अवरोध;
	हाल QPSK:
		अवरोध;
	हाल QAM_16:
		buf[1] |= (1 << 6);
		अवरोध;
	हाल QAM_64:
		buf[1] |= (2 << 6);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid modulation\n");
		स्वतः_mode = true;
	पूर्ण

	/* Use HP. How and which हाल we can चयन to LP? */
	buf[1] |= (1 << 4);

	चयन (c->code_rate_HP) अणु
	हाल FEC_AUTO:
		स्वतः_mode = true;
		अवरोध;
	हाल FEC_1_2:
		अवरोध;
	हाल FEC_2_3:
		buf[2] |= (1 << 0);
		अवरोध;
	हाल FEC_3_4:
		buf[2] |= (2 << 0);
		अवरोध;
	हाल FEC_5_6:
		buf[2] |= (3 << 0);
		अवरोध;
	हाल FEC_7_8:
		buf[2] |= (4 << 0);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid code_rate_HP\n");
		स्वतः_mode = true;
	पूर्ण

	चयन (c->code_rate_LP) अणु
	हाल FEC_AUTO:
		स्वतः_mode = true;
		अवरोध;
	हाल FEC_1_2:
		अवरोध;
	हाल FEC_2_3:
		buf[2] |= (1 << 3);
		अवरोध;
	हाल FEC_3_4:
		buf[2] |= (2 << 3);
		अवरोध;
	हाल FEC_5_6:
		buf[2] |= (3 << 3);
		अवरोध;
	हाल FEC_7_8:
		buf[2] |= (4 << 3);
		अवरोध;
	हाल FEC_NONE:
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid code_rate_LP\n");
		स्वतः_mode = true;
	पूर्ण

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		अवरोध;
	हाल 7000000:
		buf[1] |= (1 << 2);
		अवरोध;
	हाल 8000000:
		buf[1] |= (2 << 2);
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid bandwidth_hz\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(state->regmap, 0xd3c0, buf, 3);
	अगर (ret)
		जाओ err;

	अगर (स्वतः_mode) अणु
		/* clear easy mode flag */
		ret = regmap_ग_लिखो(state->regmap, 0xaefd, 0x00);
		अगर (ret)
			जाओ err;

		dev_dbg(&client->dev, "auto params\n");
	पूर्ण अन्यथा अणु
		/* set easy mode flag */
		ret = regmap_ग_लिखो(state->regmap, 0xaefd, 0x01);
		अगर (ret)
			जाओ err;

		ret = regmap_ग_लिखो(state->regmap, 0xaefe, 0x00);
		अगर (ret)
			जाओ err;

		dev_dbg(&client->dev, "manual params\n");
	पूर्ण

	/* Reset FSM */
	ret = regmap_ग_लिखो(state->regmap, 0xffff, 0x00);
	अगर (ret)
		जाओ err;

	state->bandwidth_hz = c->bandwidth_hz;
	state->set_frontend_jअगरfies = jअगरfies;
	state->first_tune = false;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_get_frontend(काष्ठा dvb_frontend *fe,
			       काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;
	u8 buf[3];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_पढ़ो(state->regmap, 0xd3c0, buf, 3);
	अगर (ret)
		जाओ err;

	चयन ((buf[1] >> 6) & 3) अणु
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

	चयन ((buf[0] >> 0) & 3) अणु
	हाल 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
	पूर्ण

	चयन ((buf[0] >> 2) & 3) अणु
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

	चयन ((buf[2] >> 0) & 7) अणु
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

	चयन ((buf[2] >> 3) & 7) अणु
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

	चयन ((buf[1] >> 2) & 3) अणु
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

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, sपंचांगp1;
	अचिन्हित पूर्णांक uपंचांगp, uपंचांगp1, uपंचांगp2, uपंचांगp3, uपंचांगp4;
	u8 buf[7];

	dev_dbg(&client->dev, "\n");

	/*
	 * Return status from the cache अगर it is younger than 2000ms with the
	 * exception of last tune is करोne during 4000ms.
	 */
	अगर (समय_is_after_jअगरfies(state->पढ़ो_status_jअगरfies + msecs_to_jअगरfies(2000)) &&
	    समय_is_beक्रमe_jअगरfies(state->set_frontend_jअगरfies + msecs_to_jअगरfies(4000))) अणु
		*status = state->fe_status;
	पूर्ण अन्यथा अणु
		/* MPEG2 lock */
		ret = regmap_पढ़ो(state->regmap, 0xd507, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर ((uपंचांगp >> 6) & 0x01) अणु
			uपंचांगp1 = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		पूर्ण अन्यथा अणु
			/* TPS lock */
			ret = regmap_पढ़ो(state->regmap, 0xd330, &uपंचांगp);
			अगर (ret)
				जाओ err;

			अगर ((uपंचांगp >> 3) & 0x01)
				uपंचांगp1 = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI;
			अन्यथा
				uपंचांगp1 = 0;
		पूर्ण

		dev_dbg(&client->dev, "fe_status %02x\n", uपंचांगp1);

		state->पढ़ो_status_jअगरfies = jअगरfies;

		state->fe_status = uपंचांगp1;
		*status = uपंचांगp1;
	पूर्ण

	/* Signal strength */
	चयन (state->strength_en) अणु
	हाल 0:
		/* Check अगर we support संकेत strength */
		ret = regmap_पढ़ो(state->regmap, 0x9bee, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर ((uपंचांगp >> 0) & 0x01) अणु
			/* Read agc values क्रम संकेत strength estimation */
			ret = regmap_पढ़ो(state->regmap, 0x9bbd, &uपंचांगp1);
			अगर (ret)
				जाओ err;
			ret = regmap_पढ़ो(state->regmap, 0x9bd0, &uपंचांगp2);
			अगर (ret)
				जाओ err;
			ret = regmap_पढ़ो(state->regmap, 0x9be2, &uपंचांगp3);
			अगर (ret)
				जाओ err;
			ret = regmap_पढ़ो(state->regmap, 0x9be4, &uपंचांगp4);
			अगर (ret)
				जाओ err;

			state->rf_agc_50 = uपंचांगp1;
			state->rf_agc_80 = uपंचांगp2;
			state->अगर_agc_50 = uपंचांगp3;
			state->अगर_agc_80 = uपंचांगp4;
			dev_dbg(&client->dev,
				"rf_agc_50 %u, rf_agc_80 %u, if_agc_50 %u, if_agc_80 %u\n",
				uपंचांगp1, uपंचांगp2, uपंचांगp3, uपंचांगp4);

			state->strength_en = 1;
		पूर्ण अन्यथा अणु
			/* Signal strength is not supported */
			state->strength_en = 2;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 1:
		अगर (समय_is_after_jअगरfies(state->strength_jअगरfies + msecs_to_jअगरfies(2000)))
			अवरोध;

		/* Read value */
		ret = regmap_bulk_पढ़ो(state->regmap, 0xd07c, buf, 2);
		अगर (ret)
			जाओ err;

		/*
		 * Conकाष्ठा line equation from tuner dependent -80/-50 dBm agc
		 * limits and use it to map current agc value to dBm estimate
		 */
		#घोषणा agc_gain (buf[0] + buf[1])
		#घोषणा agc_gain_50dbm (state->rf_agc_50 + state->अगर_agc_50)
		#घोषणा agc_gain_80dbm (state->rf_agc_80 + state->अगर_agc_80)
		sपंचांगp1 = 30000 * (agc_gain - agc_gain_80dbm) /
			(agc_gain_50dbm - agc_gain_80dbm) - 80000;

		dev_dbg(&client->dev,
			"strength %d, agc_gain %d, agc_gain_50dbm %d, agc_gain_80dbm %d\n",
			sपंचांगp1, agc_gain, agc_gain_50dbm, agc_gain_80dbm);

		state->strength_jअगरfies = jअगरfies;
		/* Convert [-90, -30] dBm to [0x0000, 0xffff] क्रम dvbv3 */
		uपंचांगp1 = clamp(sपंचांगp1 + 90000, 0, 60000);
		state->dvbv3_strength = भाग_u64((u64)uपंचांगp1 * 0xffff, 60000);

		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = sपंचांगp1;
		अवरोध;
	शेष:
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		अवरोध;
	पूर्ण

	/* CNR */
	चयन (state->fe_status & FE_HAS_VITERBI) अणु
	हाल FE_HAS_VITERBI:
		अगर (समय_is_after_jअगरfies(state->cnr_jअगरfies + msecs_to_jअगरfies(2000)))
			अवरोध;

		/* Check अगर cnr पढ़ोy */
		ret = regmap_पढ़ो(state->regmap, 0xd2e1, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर (!((uपंचांगp >> 3) & 0x01)) अणु
			dev_dbg(&client->dev, "cnr not ready\n");
			अवरोध;
		पूर्ण

		/* Read value */
		ret = regmap_bulk_पढ़ो(state->regmap, 0xd2e3, buf, 3);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

		/* Read current modulation */
		ret = regmap_पढ़ो(state->regmap, 0xd3c1, &uपंचांगp);
		अगर (ret)
			जाओ err;

		चयन ((uपंचांगp >> 6) & 3) अणु
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
			dev_dbg(&client->dev, "invalid modulation %u\n",
				(uपंचांगp >> 6) & 3);
			uपंचांगp1 = 0;
			अवरोध;
		पूर्ण

		dev_dbg(&client->dev, "cnr %u\n", uपंचांगp1);

		state->cnr_jअगरfies = jअगरfies;
		state->dvbv3_snr = uपंचांगp1 / 100;

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = uपंचांगp1;
		अवरोध;
	शेष:
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		अवरोध;
	पूर्ण

	/* BER / PER */
	चयन (state->fe_status & FE_HAS_SYNC) अणु
	हाल FE_HAS_SYNC:
		अगर (समय_is_after_jअगरfies(state->ber_ucb_jअगरfies + msecs_to_jअगरfies(2000)))
			अवरोध;

		/* Check अगर ber / ucb is पढ़ोy */
		ret = regmap_पढ़ो(state->regmap, 0xd391, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर (!((uपंचांगp >> 4) & 0x01)) अणु
			dev_dbg(&client->dev, "ber not ready\n");
			अवरोध;
		पूर्ण

		/* Read value */
		ret = regmap_bulk_पढ़ो(state->regmap, 0xd385, buf, 7);
		अगर (ret)
			जाओ err;

		uपंचांगp1 = buf[4] << 16 | buf[3] << 8 | buf[2] << 0;
		uपंचांगp2 = (buf[1] << 8 | buf[0] << 0) * 204 * 8;
		uपंचांगp3 = buf[6] << 8 | buf[5] << 0;
		uपंचांगp4 = buf[1] << 8 | buf[0] << 0;

		/* Use 10000 TS packets क्रम measure */
		अगर (uपंचांगp4 != 10000) अणु
			buf[0] = (10000 >> 0) & 0xff;
			buf[1] = (10000 >> 8) & 0xff;
			ret = regmap_bulk_ग_लिखो(state->regmap, 0xd385, buf, 2);
			अगर (ret)
				जाओ err;
		पूर्ण

		/* Reset ber / ucb counter */
		ret = regmap_update_bits(state->regmap, 0xd391, 0x20, 0x20);
		अगर (ret)
			जाओ err;

		dev_dbg(&client->dev, "post_bit_error %u, post_bit_count %u\n",
			uपंचांगp1, uपंचांगp2);
		dev_dbg(&client->dev, "block_error %u, block_count %u\n",
			uपंचांगp3, uपंचांगp4);

		state->ber_ucb_jअगरfies = jअगरfies;
		state->dvbv3_ber = uपंचांगp1;
		state->dvbv3_ucblocks += uपंचांगp3;

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += uपंचांगp1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += uपंचांगp2;

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue += uपंचांगp3;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue += uपंचांगp4;
		अवरोध;
	शेष:
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		अवरोध;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;

	*snr = state->dvbv3_snr;

	वापस 0;
पूर्ण

अटल पूर्णांक af9013_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;

	*strength = state->dvbv3_strength;

	वापस 0;
पूर्ण

अटल पूर्णांक af9013_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;

	*ber = state->dvbv3_ber;

	वापस 0;
पूर्ण

अटल पूर्णांक af9013_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;

	*ucblocks = state->dvbv3_ucblocks;

	वापस 0;
पूर्ण

अटल पूर्णांक af9013_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret, i, len;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[3];
	स्थिर काष्ठा af9013_reg_mask_val *tab;

	dev_dbg(&client->dev, "\n");

	/* ADC on */
	ret = regmap_update_bits(state->regmap, 0xd73a, 0x08, 0x00);
	अगर (ret)
		जाओ err;

	/* Clear reset */
	ret = regmap_update_bits(state->regmap, 0xd417, 0x02, 0x00);
	अगर (ret)
		जाओ err;

	/* Disable reset */
	ret = regmap_update_bits(state->regmap, 0xd417, 0x10, 0x00);
	अगर (ret)
		जाओ err;

	/* ग_लिखो API version to firmware */
	ret = regmap_bulk_ग_लिखो(state->regmap, 0x9bf2, state->api_version, 4);
	अगर (ret)
		जाओ err;

	/* program ADC control */
	चयन (state->clk) अणु
	हाल 28800000: /* 28.800 MHz */
		uपंचांगp = 0;
		अवरोध;
	हाल 20480000: /* 20.480 MHz */
		uपंचांगp = 1;
		अवरोध;
	हाल 28000000: /* 28.000 MHz */
		uपंचांगp = 2;
		अवरोध;
	हाल 25000000: /* 25.000 MHz */
		uपंचांगp = 3;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_update_bits(state->regmap, 0x9bd2, 0x0f, uपंचांगp);
	अगर (ret)
		जाओ err;

	uपंचांगp = भाग_u64((u64)state->clk * 0x80000, 1000000);
	buf[0] = (uपंचांगp >>  0) & 0xff;
	buf[1] = (uपंचांगp >>  8) & 0xff;
	buf[2] = (uपंचांगp >> 16) & 0xff;
	ret = regmap_bulk_ग_लिखो(state->regmap, 0xd180, buf, 3);
	अगर (ret)
		जाओ err;

	/* Demod core settings */
	dev_dbg(&client->dev, "load demod core settings\n");
	len = ARRAY_SIZE(demod_init_tab);
	tab = demod_init_tab;
	क्रम (i = 0; i < len; i++) अणु
		ret = regmap_update_bits(state->regmap, tab[i].reg, tab[i].mask,
					 tab[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Demod tuner specअगरic settings */
	dev_dbg(&client->dev, "load tuner specific settings\n");
	चयन (state->tuner) अणु
	हाल AF9013_TUNER_MXL5003D:
		len = ARRAY_SIZE(tuner_init_tab_mxl5003d);
		tab = tuner_init_tab_mxl5003d;
		अवरोध;
	हाल AF9013_TUNER_MXL5005D:
	हाल AF9013_TUNER_MXL5005R:
	हाल AF9013_TUNER_MXL5007T:
		len = ARRAY_SIZE(tuner_init_tab_mxl5005);
		tab = tuner_init_tab_mxl5005;
		अवरोध;
	हाल AF9013_TUNER_ENV77H11D5:
		len = ARRAY_SIZE(tuner_init_tab_env77h11d5);
		tab = tuner_init_tab_env77h11d5;
		अवरोध;
	हाल AF9013_TUNER_MT2060:
		len = ARRAY_SIZE(tuner_init_tab_mt2060);
		tab = tuner_init_tab_mt2060;
		अवरोध;
	हाल AF9013_TUNER_MC44S803:
		len = ARRAY_SIZE(tuner_init_tab_mc44s803);
		tab = tuner_init_tab_mc44s803;
		अवरोध;
	हाल AF9013_TUNER_QT1010:
	हाल AF9013_TUNER_QT1010A:
		len = ARRAY_SIZE(tuner_init_tab_qt1010);
		tab = tuner_init_tab_qt1010;
		अवरोध;
	हाल AF9013_TUNER_MT2060_2:
		len = ARRAY_SIZE(tuner_init_tab_mt2060_2);
		tab = tuner_init_tab_mt2060_2;
		अवरोध;
	हाल AF9013_TUNER_TDA18271:
	हाल AF9013_TUNER_TDA18218:
		len = ARRAY_SIZE(tuner_init_tab_tda18271);
		tab = tuner_init_tab_tda18271;
		अवरोध;
	हाल AF9013_TUNER_UNKNOWN:
	शेष:
		len = ARRAY_SIZE(tuner_init_tab_unknown);
		tab = tuner_init_tab_unknown;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		ret = regmap_update_bits(state->regmap, tab[i].reg, tab[i].mask,
					 tab[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* TS पूर्णांकerface */
	अगर (state->ts_output_pin == 7)
		uपंचांगp = 1 << 3 | state->ts_mode << 1;
	अन्यथा
		uपंचांगp = 0 << 3 | state->ts_mode << 1;
	ret = regmap_update_bits(state->regmap, 0xd500, 0x0e, uपंचांगp);
	अगर (ret)
		जाओ err;

	/* enable lock led */
	ret = regmap_update_bits(state->regmap, 0xd730, 0x01, 0x01);
	अगर (ret)
		जाओ err;

	state->first_tune = true;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	dev_dbg(&client->dev, "\n");

	/* disable lock led */
	ret = regmap_update_bits(state->regmap, 0xd730, 0x01, 0x00);
	अगर (ret)
		जाओ err;

	/* Enable reset */
	ret = regmap_update_bits(state->regmap, 0xd417, 0x10, 0x10);
	अगर (ret)
		जाओ err;

	/* Start reset execution */
	ret = regmap_ग_लिखो(state->regmap, 0xaeff, 0x01);
	अगर (ret)
		जाओ err;

	/* Wait reset perक्रमms */
	ret = regmap_पढ़ो_poll_समयout(state->regmap, 0xd417, uपंचांगp,
				       (uपंचांगp >> 1) & 0x01, 5000, 1000000);
	अगर (ret)
		जाओ err;

	अगर (!((uपंचांगp >> 1) & 0x01)) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	/* ADC off */
	ret = regmap_update_bits(state->regmap, 0xd73a, 0x08, 0x08);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops af9013_ops;

अटल पूर्णांक af9013_करोwnload_firmware(काष्ठा af9013_state *state)
अणु
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret, i, len, rem;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[4];
	u16 checksum = 0;
	स्थिर काष्ठा firmware *firmware;
	स्थिर अक्षर *name = AF9013_FIRMWARE;

	dev_dbg(&client->dev, "\n");

	/* Check whether firmware is alपढ़ोy running */
	ret = regmap_पढ़ो(state->regmap, 0x98be, &uपंचांगp);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "firmware status %02x\n", uपंचांगp);

	अगर (uपंचांगp == 0x0c)
		वापस 0;

	dev_info(&client->dev, "found a '%s' in cold state, will try to load a firmware\n",
		 af9013_ops.info.name);

	/* Request the firmware, will block and समयout */
	ret = request_firmware(&firmware, name, &client->dev);
	अगर (ret) अणु
		dev_info(&client->dev, "firmware file '%s' not found %d\n",
			 name, ret);
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
		 name);

	/* Write firmware checksum & size */
	क्रम (i = 0; i < firmware->size; i++)
		checksum += firmware->data[i];

	buf[0] = (checksum >> 8) & 0xff;
	buf[1] = (checksum >> 0) & 0xff;
	buf[2] = (firmware->size >> 8) & 0xff;
	buf[3] = (firmware->size >> 0) & 0xff;
	ret = regmap_bulk_ग_लिखो(state->regmap, 0x50fc, buf, 4);
	अगर (ret)
		जाओ err_release_firmware;

	/* Download firmware */
	#घोषणा LEN_MAX 16
	क्रम (rem = firmware->size; rem > 0; rem -= LEN_MAX) अणु
		len = min(LEN_MAX, rem);
		ret = regmap_bulk_ग_लिखो(state->regmap,
					0x5100 + firmware->size - rem,
					&firmware->data[firmware->size - rem],
					len);
		अगर (ret) अणु
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			जाओ err_release_firmware;
		पूर्ण
	पूर्ण

	release_firmware(firmware);

	/* Boot firmware */
	ret = regmap_ग_लिखो(state->regmap, 0xe205, 0x01);
	अगर (ret)
		जाओ err;

	/* Check firmware status. 0c=OK, 04=fail */
	ret = regmap_पढ़ो_poll_समयout(state->regmap, 0x98be, uपंचांगp,
				       (uपंचांगp == 0x0c || uपंचांगp == 0x04),
				       5000, 1000000);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "firmware status %02x\n", uपंचांगp);

	अगर (uपंचांगp == 0x04) अणु
		ret = -ENODEV;
		dev_err(&client->dev, "firmware did not run\n");
		जाओ err;
	पूर्ण अन्यथा अगर (uपंचांगp != 0x0c) अणु
		ret = -ENODEV;
		dev_err(&client->dev, "firmware boot timeout\n");
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "found a '%s' in warm state\n",
		 af9013_ops.info.name);

	वापस 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops af9013_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "Afatech AF9013",
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

	.init = af9013_init,
	.sleep = af9013_sleep,

	.get_tune_settings = af9013_get_tune_settings,
	.set_frontend = af9013_set_frontend,
	.get_frontend = af9013_get_frontend,

	.पढ़ो_status = af9013_पढ़ो_status,
	.पढ़ो_snr = af9013_पढ़ो_snr,
	.पढ़ो_संकेत_strength = af9013_पढ़ो_संकेत_strength,
	.पढ़ो_ber = af9013_पढ़ो_ber,
	.पढ़ो_ucblocks = af9013_पढ़ो_ucblocks,
पूर्ण;

अटल पूर्णांक af9013_pid_filter_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "onoff %d\n", onoff);

	ret = regmap_update_bits(state->regmap, 0xd503, 0x01, onoff);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_pid_filter(काष्ठा dvb_frontend *fe, u8 index, u16 pid,
			     पूर्णांक onoff)
अणु
	काष्ठा af9013_state *state = fe->demodulator_priv;
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;
	u8 buf[2];

	dev_dbg(&client->dev, "index %d, pid %04x, onoff %d\n",
		index, pid, onoff);

	अगर (pid > 0x1fff) अणु
		/* 0x2000 is kernel भव pid क्रम whole ts (all pids) */
		ret = 0;
		जाओ err;
	पूर्ण

	buf[0] = (pid >> 0) & 0xff;
	buf[1] = (pid >> 8) & 0xff;
	ret = regmap_bulk_ग_लिखो(state->regmap, 0xd505, buf, 2);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(state->regmap, 0xd504, onoff << 5 | index << 0);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल काष्ठा dvb_frontend *af9013_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा af9013_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &state->fe;
पूर्ण

अटल काष्ठा i2c_adapter *af9013_get_i2c_adapter(काष्ठा i2c_client *client)
अणु
	काष्ठा af9013_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस state->muxc->adapter[0];
पूर्ण

/*
 * XXX: Hackish solution. We use भव रेजिस्टर, reg bit 16, to carry info
 * about i2c adapter locking. Own locking is needed because i2c mux call has
 * alपढ़ोy locked i2c adapter.
 */
अटल पूर्णांक af9013_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा af9013_state *state = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	अगर (state->ts_mode == AF9013_TS_MODE_USB)
		ret = regmap_update_bits(state->regmap, 0x1d417, 0x08, 0x08);
	अन्यथा
		ret = regmap_update_bits(state->regmap, 0x1d607, 0x04, 0x04);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा af9013_state *state = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = state->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	अगर (state->ts_mode == AF9013_TS_MODE_USB)
		ret = regmap_update_bits(state->regmap, 0x1d417, 0x08, 0x00);
	अन्यथा
		ret = regmap_update_bits(state->regmap, 0x1d607, 0x04, 0x00);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

/* Own I2C access routines needed क्रम regmap as chip uses extra command byte */
अटल पूर्णांक af9013_wregs(काष्ठा i2c_client *client, u8 cmd, u16 reg,
			स्थिर u8 *val, पूर्णांक len, u8 lock)
अणु
	पूर्णांक ret;
	u8 buf[21];
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 3 + len,
			.buf = buf,
		पूर्ण
	पूर्ण;

	अगर (3 + len > माप(buf)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	buf[0] = (reg >> 8) & 0xff;
	buf[1] = (reg >> 0) & 0xff;
	buf[2] = cmd;
	स_नकल(&buf[3], val, len);

	अगर (lock)
		i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = __i2c_transfer(client->adapter, msg, 1);
	अगर (lock)
		i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	अगर (ret < 0) अणु
		जाओ err;
	पूर्ण अन्यथा अगर (ret != 1) अणु
		ret = -EREMOTEIO;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_rregs(काष्ठा i2c_client *client, u8 cmd, u16 reg,
			u8 *val, पूर्णांक len, u8 lock)
अणु
	पूर्णांक ret;
	u8 buf[3];
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 3,
			.buf = buf,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = val,
		पूर्ण
	पूर्ण;

	buf[0] = (reg >> 8) & 0xff;
	buf[1] = (reg >> 0) & 0xff;
	buf[2] = cmd;

	अगर (lock)
		i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = __i2c_transfer(client->adapter, msg, 2);
	अगर (lock)
		i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	अगर (ret < 0) अणु
		जाओ err;
	पूर्ण अन्यथा अगर (ret != 2) अणु
		ret = -EREMOTEIO;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_regmap_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा af9013_state *state = i2c_get_clientdata(client);
	पूर्णांक ret, i;
	u8 cmd;
	u8 lock = !((u8 *)data)[0];
	u16 reg = ((u8 *)data)[1] << 8 | ((u8 *)data)[2] << 0;
	u8 *val = &((u8 *)data)[3];
	स्थिर अचिन्हित पूर्णांक len = count - 3;

	अगर (state->ts_mode == AF9013_TS_MODE_USB && (reg & 0xff00) != 0xae00) अणु
		cmd = 0 << 7|0 << 6|(len - 1) << 2|1 << 1|1 << 0;
		ret = af9013_wregs(client, cmd, reg, val, len, lock);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (reg >= 0x5100 && reg < 0x8fff) अणु
		/* Firmware करोwnload */
		cmd = 1 << 7|1 << 6|(len - 1) << 2|1 << 1|1 << 0;
		ret = af9013_wregs(client, cmd, reg, val, len, lock);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		cmd = 0 << 7|0 << 6|(1 - 1) << 2|1 << 1|1 << 0;
		क्रम (i = 0; i < len; i++) अणु
			ret = af9013_wregs(client, cmd, reg + i, val + i, 1,
					   lock);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_regmap_पढ़ो(व्योम *context, स्थिर व्योम *reg_buf,
			      माप_प्रकार reg_size, व्योम *val_buf, माप_प्रकार val_size)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा af9013_state *state = i2c_get_clientdata(client);
	पूर्णांक ret, i;
	u8 cmd;
	u8 lock = !((u8 *)reg_buf)[0];
	u16 reg = ((u8 *)reg_buf)[1] << 8 | ((u8 *)reg_buf)[2] << 0;
	u8 *val = &((u8 *)val_buf)[0];
	स्थिर अचिन्हित पूर्णांक len = val_size;

	अगर (state->ts_mode == AF9013_TS_MODE_USB && (reg & 0xff00) != 0xae00) अणु
		cmd = 0 << 7|0 << 6|(len - 1) << 2|1 << 1|0 << 0;
		ret = af9013_rregs(client, cmd, reg, val_buf, len, lock);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		cmd = 0 << 7|0 << 6|(1 - 1) << 2|1 << 1|0 << 0;
		क्रम (i = 0; i < len; i++) अणु
			ret = af9013_rregs(client, cmd, reg + i, val + i, 1,
					   lock);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा af9013_state *state;
	काष्ठा af9013_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा dtv_frontend_properties *c;
	पूर्णांक ret, i;
	u8 firmware_version[4];
	अटल स्थिर काष्ठा regmap_bus regmap_bus = अणु
		.पढ़ो = af9013_regmap_पढ़ो,
		.ग_लिखो = af9013_regmap_ग_लिखो,
	पूर्ण;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		/* Actual reg is 16 bits, see i2c adapter lock */
		.reg_bits = 24,
		.val_bits = 8,
	पूर्ण;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev_dbg(&client->dev, "\n");

	/* Setup the state */
	state->client = client;
	i2c_set_clientdata(client, state);
	state->clk = pdata->clk;
	state->tuner = pdata->tuner;
	state->अगर_frequency = pdata->अगर_frequency;
	state->ts_mode = pdata->ts_mode;
	state->ts_output_pin = pdata->ts_output_pin;
	state->spec_inv = pdata->spec_inv;
	स_नकल(&state->api_version, pdata->api_version, माप(state->api_version));
	स_नकल(&state->gpio, pdata->gpio, माप(state->gpio));
	state->regmap = regmap_init(&client->dev, &regmap_bus, client,
				  &regmap_config);
	अगर (IS_ERR(state->regmap)) अणु
		ret = PTR_ERR(state->regmap);
		जाओ err_kमुक्त;
	पूर्ण
	/* Create mux i2c adapter */
	state->muxc = i2c_mux_alloc(client->adapter, &client->dev, 1, 0, 0,
				    af9013_select, af9013_deselect);
	अगर (!state->muxc) अणु
		ret = -ENOMEM;
		जाओ err_regmap_निकास;
	पूर्ण
	state->muxc->priv = state;
	ret = i2c_mux_add_adapter(state->muxc, 0, 0, 0);
	अगर (ret)
		जाओ err_regmap_निकास;

	/* Download firmware */
	अगर (state->ts_mode != AF9013_TS_MODE_USB) अणु
		ret = af9013_करोwnload_firmware(state);
		अगर (ret)
			जाओ err_i2c_mux_del_adapters;
	पूर्ण

	/* Firmware version */
	ret = regmap_bulk_पढ़ो(state->regmap, 0x5103, firmware_version,
			       माप(firmware_version));
	अगर (ret)
		जाओ err_i2c_mux_del_adapters;

	/* Set GPIOs */
	क्रम (i = 0; i < माप(state->gpio); i++) अणु
		ret = af9013_set_gpio(state, i, state->gpio[i]);
		अगर (ret)
			जाओ err_i2c_mux_del_adapters;
	पूर्ण

	/* Create dvb frontend */
	स_नकल(&state->fe.ops, &af9013_ops, माप(state->fe.ops));
	state->fe.demodulator_priv = state;

	/* Setup callbacks */
	pdata->get_dvb_frontend = af9013_get_dvb_frontend;
	pdata->get_i2c_adapter = af9013_get_i2c_adapter;
	pdata->pid_filter = af9013_pid_filter;
	pdata->pid_filter_ctrl = af9013_pid_filter_ctrl;

	/* Init stats to indicate which stats are supported */
	c = &state->fe.dtv_property_cache;
	c->strength.len = 1;
	c->cnr.len = 1;
	c->post_bit_error.len = 1;
	c->post_bit_count.len = 1;
	c->block_error.len = 1;
	c->block_count.len = 1;

	dev_info(&client->dev, "Afatech AF9013 successfully attached\n");
	dev_info(&client->dev, "firmware version: %d.%d.%d.%d\n",
		 firmware_version[0], firmware_version[1],
		 firmware_version[2], firmware_version[3]);
	वापस 0;
err_i2c_mux_del_adapters:
	i2c_mux_del_adapters(state->muxc);
err_regmap_निकास:
	regmap_निकास(state->regmap);
err_kमुक्त:
	kमुक्त(state);
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक af9013_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा af9013_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	i2c_mux_del_adapters(state->muxc);

	regmap_निकास(state->regmap);

	kमुक्त(state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id af9013_id_table[] = अणु
	अणु"af9013", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, af9013_id_table);

अटल काष्ठा i2c_driver af9013_driver = अणु
	.driver = अणु
		.name	= "af9013",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= af9013_probe,
	.हटाओ		= af9013_हटाओ,
	.id_table	= af9013_id_table,
पूर्ण;

module_i2c_driver(af9013_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Afatech AF9013 DVB-T demodulator driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(AF9013_FIRMWARE);
