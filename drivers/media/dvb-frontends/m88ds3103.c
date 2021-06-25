<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Montage Technology M88DS3103/M88RS6000 demodulator driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 */

#समावेश "m88ds3103_priv.h"

अटल स्थिर काष्ठा dvb_frontend_ops m88ds3103_ops;

/* ग_लिखो single रेजिस्टर with mask */
अटल पूर्णांक m88ds3103_update_bits(काष्ठा m88ds3103_dev *dev,
				u8 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	/* no need क्रम पढ़ो अगर whole reg is written */
	अगर (mask != 0xff) अणु
		ret = regmap_bulk_पढ़ो(dev->regmap, reg, &पंचांगp, 1);
		अगर (ret)
			वापस ret;

		val &= mask;
		पंचांगp &= ~mask;
		val |= पंचांगp;
	पूर्ण

	वापस regmap_bulk_ग_लिखो(dev->regmap, reg, &val, 1);
पूर्ण

/* ग_लिखो reg val table using reg addr स्वतः increment */
अटल पूर्णांक m88ds3103_wr_reg_val_tab(काष्ठा m88ds3103_dev *dev,
		स्थिर काष्ठा m88ds3103_reg_val *tab, पूर्णांक tab_len)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i, j;
	u8 buf[83];

	dev_dbg(&client->dev, "tab_len=%d\n", tab_len);

	अगर (tab_len > 86) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (i = 0, j = 0; i < tab_len; i++, j++) अणु
		buf[j] = tab[i].val;

		अगर (i == tab_len - 1 || tab[i].reg != tab[i + 1].reg - 1 ||
				!((j + 1) % (dev->cfg->i2c_wr_max - 1))) अणु
			ret = regmap_bulk_ग_लिखो(dev->regmap, tab[i].reg - j, buf, j + 1);
			अगर (ret)
				जाओ err;

			j = -1;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

/*
 * m88ds3103b demod has an पूर्णांकernal device related to घड़ीing. First the i2c
 * gate must be खोलोed, क्रम one transaction, then ग_लिखोs will be allowed.
 */
अटल पूर्णांक m88ds3103b_dt_ग_लिखो(काष्ठा m88ds3103_dev *dev, पूर्णांक reg, पूर्णांक data)
अणु
	काष्ठा i2c_client *client = dev->client;
	u8 buf[] = अणुreg, dataपूर्ण;
	u8 val;
	पूर्णांक ret;
	काष्ठा i2c_msg msg = अणु
		.addr = dev->dt_addr, .flags = 0, .buf = buf, .len = 2
	पूर्ण;

	m88ds3103_update_bits(dev, 0x11, 0x01, 0x00);

	val = 0x11;
	ret = regmap_ग_लिखो(dev->regmap, 0x03, val);
	अगर (ret)
		dev_dbg(&client->dev, "fail=%d\n", ret);

	ret = i2c_transfer(dev->dt_client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_err(&client->dev, "0x%02x (ret=%i, reg=0x%02x, value=0x%02x)\n",
			dev->dt_addr, ret, reg, data);

		m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);
		वापस -EREMOTEIO;
	पूर्ण
	m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);

	dev_dbg(&client->dev, "0x%02x reg 0x%02x, value 0x%02x\n",
		dev->dt_addr, reg, data);

	वापस 0;
पूर्ण

/*
 * m88ds3103b demod has an पूर्णांकernal device related to घड़ीing. First the i2c
 * gate must be खोलोed, क्रम two transactions, then पढ़ोs will be allowed.
 */
अटल पूर्णांक m88ds3103b_dt_पढ़ो(काष्ठा m88ds3103_dev *dev, u8 reg)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 val;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = dev->dt_addr,
			.flags = 0,
			.buf = b0,
			.len = 1
		पूर्ण,
		अणु
			.addr = dev->dt_addr,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		पूर्ण
	पूर्ण;

	m88ds3103_update_bits(dev, 0x11, 0x01, 0x00);

	val = 0x12;
	ret = regmap_ग_लिखो(dev->regmap, 0x03, val);
	अगर (ret)
		dev_dbg(&client->dev, "fail=%d\n", ret);

	ret = i2c_transfer(dev->dt_client->adapter, msg, 2);
	अगर (ret != 2) अणु
		dev_err(&client->dev, "0x%02x (ret=%d, reg=0x%02x)\n",
			dev->dt_addr, ret, reg);

		m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);
		वापस -EREMOTEIO;
	पूर्ण
	m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);

	dev_dbg(&client->dev, "0x%02x reg 0x%02x, value 0x%02x\n",
		dev->dt_addr, reg, b1[0]);

	वापस b1[0];
पूर्ण

/*
 * Get the demodulator AGC PWM voltage setting supplied to the tuner.
 */
पूर्णांक m88ds3103_get_agc_pwm(काष्ठा dvb_frontend *fe, u8 *_agc_pwm)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	अचिन्हित पंचांगp;
	पूर्णांक ret;

	ret = regmap_पढ़ो(dev->regmap, 0x3f, &पंचांगp);
	अगर (ret == 0)
		*_agc_pwm = पंचांगp;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(m88ds3103_get_agc_pwm);

अटल पूर्णांक m88ds3103_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i, iपंचांगp;
	अचिन्हित पूर्णांक uपंचांगp;
	u8 buf[3];

	*status = 0;

	अगर (!dev->warm) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		ret = regmap_पढ़ो(dev->regmap, 0xd1, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर ((uपंचांगp & 0x07) == 0x07)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI | FE_HAS_SYNC |
					FE_HAS_LOCK;
		अवरोध;
	हाल SYS_DVBS2:
		ret = regmap_पढ़ो(dev->regmap, 0x0d, &uपंचांगp);
		अगर (ret)
			जाओ err;

		अगर ((uपंचांगp & 0x8f) == 0x8f)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI | FE_HAS_SYNC |
					FE_HAS_LOCK;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid delivery_system\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dev->fe_status = *status;
	dev_dbg(&client->dev, "lock=%02x status=%02x\n", uपंचांगp, *status);

	/* CNR */
	अगर (dev->fe_status & FE_HAS_VITERBI) अणु
		अचिन्हित पूर्णांक cnr, noise, संकेत, noise_tot, संकेत_tot;

		cnr = 0;
		/* more iterations क्रम more accurate estimation */
		#घोषणा M88DS3103_SNR_ITERATIONS 3

		चयन (c->delivery_प्रणाली) अणु
		हाल SYS_DVBS:
			iपंचांगp = 0;

			क्रम (i = 0; i < M88DS3103_SNR_ITERATIONS; i++) अणु
				ret = regmap_पढ़ो(dev->regmap, 0xff, &uपंचांगp);
				अगर (ret)
					जाओ err;

				iपंचांगp += uपंचांगp;
			पूर्ण

			/* use of single रेजिस्टर limits max value to 15 dB */
			/* SNR(X) dB = 10 * ln(X) / ln(10) dB */
			iपंचांगp = DIV_ROUND_CLOSEST(iपंचांगp, 8 * M88DS3103_SNR_ITERATIONS);
			अगर (iपंचांगp)
				cnr = भाग_u64((u64) 10000 * पूर्णांकlog2(iपंचांगp), पूर्णांकlog2(10));
			अवरोध;
		हाल SYS_DVBS2:
			noise_tot = 0;
			संकेत_tot = 0;

			क्रम (i = 0; i < M88DS3103_SNR_ITERATIONS; i++) अणु
				ret = regmap_bulk_पढ़ो(dev->regmap, 0x8c, buf, 3);
				अगर (ret)
					जाओ err;

				noise = buf[1] << 6;    /* [13:6] */
				noise |= buf[0] & 0x3f; /*  [5:0] */
				noise >>= 2;
				संकेत = buf[2] * buf[2];
				संकेत >>= 1;

				noise_tot += noise;
				संकेत_tot += संकेत;
			पूर्ण

			noise = noise_tot / M88DS3103_SNR_ITERATIONS;
			संकेत = संकेत_tot / M88DS3103_SNR_ITERATIONS;

			/* SNR(X) dB = 10 * log10(X) dB */
			अगर (संकेत > noise) अणु
				iपंचांगp = संकेत / noise;
				cnr = भाग_u64((u64) 10000 * पूर्णांकlog10(iपंचांगp), (1 << 24));
			पूर्ण
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid delivery_system\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (cnr) अणु
			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].svalue = cnr;
		पूर्ण अन्यथा अणु
			c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* BER */
	अगर (dev->fe_status & FE_HAS_LOCK) अणु
		अचिन्हित पूर्णांक uपंचांगp, post_bit_error, post_bit_count;

		चयन (c->delivery_प्रणाली) अणु
		हाल SYS_DVBS:
			ret = regmap_ग_लिखो(dev->regmap, 0xf9, 0x04);
			अगर (ret)
				जाओ err;

			ret = regmap_पढ़ो(dev->regmap, 0xf8, &uपंचांगp);
			अगर (ret)
				जाओ err;

			/* measurement पढ़ोy? */
			अगर (!(uपंचांगp & 0x10)) अणु
				ret = regmap_bulk_पढ़ो(dev->regmap, 0xf6, buf, 2);
				अगर (ret)
					जाओ err;

				post_bit_error = buf[1] << 8 | buf[0] << 0;
				post_bit_count = 0x800000;
				dev->post_bit_error += post_bit_error;
				dev->post_bit_count += post_bit_count;
				dev->dvbv3_ber = post_bit_error;

				/* restart measurement */
				uपंचांगp |= 0x10;
				ret = regmap_ग_लिखो(dev->regmap, 0xf8, uपंचांगp);
				अगर (ret)
					जाओ err;
			पूर्ण
			अवरोध;
		हाल SYS_DVBS2:
			ret = regmap_bulk_पढ़ो(dev->regmap, 0xd5, buf, 3);
			अगर (ret)
				जाओ err;

			uपंचांगp = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

			/* enough data? */
			अगर (uपंचांगp > 4000) अणु
				ret = regmap_bulk_पढ़ो(dev->regmap, 0xf7, buf, 2);
				अगर (ret)
					जाओ err;

				post_bit_error = buf[1] << 8 | buf[0] << 0;
				post_bit_count = 32 * uपंचांगp; /* TODO: FEC */
				dev->post_bit_error += post_bit_error;
				dev->post_bit_count += post_bit_count;
				dev->dvbv3_ber = post_bit_error;

				/* restart measurement */
				ret = regmap_ग_लिखो(dev->regmap, 0xd1, 0x01);
				अगर (ret)
					जाओ err;

				ret = regmap_ग_लिखो(dev->regmap, 0xf9, 0x01);
				अगर (ret)
					जाओ err;

				ret = regmap_ग_लिखो(dev->regmap, 0xf9, 0x00);
				अगर (ret)
					जाओ err;

				ret = regmap_ग_लिखो(dev->regmap, 0xd1, 0x00);
				अगर (ret)
					जाओ err;
			पूर्ण
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid delivery_system\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103b_select_mclk(काष्ठा m88ds3103_dev *dev)
अणु
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	u32 adc_Freq_MHz[3] = अणु96, 93, 99पूर्ण;
	u8  reg16_list[3] = अणु96, 92, 100पूर्ण, reg16, reg15;
	u32 offset_MHz[3];
	u32 max_offset = 0;
	u32 old_setting = dev->mclk;
	u32 tuner_freq_MHz = c->frequency / 1000;
	u8 i;
	अक्षर big_symbol = 0;

	big_symbol = (c->symbol_rate > 45010000) ? 1 : 0;

	अगर (big_symbol) अणु
		reg16 = 115;
	पूर्ण अन्यथा अणु
		reg16 = 96;

		/* TODO: IS THIS NECESSARY ? */
		क्रम (i = 0; i < 3; i++) अणु
			offset_MHz[i] = tuner_freq_MHz % adc_Freq_MHz[i];

			अगर (offset_MHz[i] > (adc_Freq_MHz[i] / 2))
				offset_MHz[i] = adc_Freq_MHz[i] - offset_MHz[i];

			अगर (offset_MHz[i] > max_offset) अणु
				max_offset = offset_MHz[i];
				reg16 = reg16_list[i];
				dev->mclk = adc_Freq_MHz[i] * 1000 * 1000;

				अगर (big_symbol)
					dev->mclk /= 2;

				dev_dbg(&client->dev, "modifying mclk %u -> %u\n",
					old_setting, dev->mclk);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dev->mclk == 93000000)
		regmap_ग_लिखो(dev->regmap, 0xA0, 0x42);
	अन्यथा अगर (dev->mclk == 96000000)
		regmap_ग_लिखो(dev->regmap, 0xA0, 0x44);
	अन्यथा अगर (dev->mclk == 99000000)
		regmap_ग_लिखो(dev->regmap, 0xA0, 0x46);
	अन्यथा अगर (dev->mclk == 110250000)
		regmap_ग_लिखो(dev->regmap, 0xA0, 0x4E);
	अन्यथा
		regmap_ग_लिखो(dev->regmap, 0xA0, 0x44);

	reg15 = m88ds3103b_dt_पढ़ो(dev, 0x15);

	m88ds3103b_dt_ग_लिखो(dev, 0x05, 0x40);
	m88ds3103b_dt_ग_लिखो(dev, 0x11, 0x08);

	अगर (big_symbol)
		reg15 |= 0x02;
	अन्यथा
		reg15 &= ~0x02;

	m88ds3103b_dt_ग_लिखो(dev, 0x15, reg15);
	m88ds3103b_dt_ग_लिखो(dev, 0x16, reg16);

	usleep_range(5000, 5500);

	m88ds3103b_dt_ग_लिखो(dev, 0x05, 0x00);
	m88ds3103b_dt_ग_लिखो(dev, 0x11, (u8)(big_symbol ? 0x0E : 0x0A));

	usleep_range(5000, 5500);

	वापस 0;
पूर्ण

अटल पूर्णांक m88ds3103b_set_mclk(काष्ठा m88ds3103_dev *dev, u32 mclk_khz)
अणु
	u8 reg11 = 0x0A, reg15, reg16, reg1D, reg1E, reg1F, पंचांगp;
	u8 sm, f0 = 0, f1 = 0, f2 = 0, f3 = 0;
	u16 pll_भाग_fb, N;
	u32 भाग;

	reg15 = m88ds3103b_dt_पढ़ो(dev, 0x15);
	reg16 = m88ds3103b_dt_पढ़ो(dev, 0x16);
	reg1D = m88ds3103b_dt_पढ़ो(dev, 0x1D);

	अगर (dev->cfg->ts_mode != M88DS3103_TS_SERIAL) अणु
		अगर (reg16 == 92)
			पंचांगp = 93;
		अन्यथा अगर (reg16 == 100)
			पंचांगp = 99;
		अन्यथा
			पंचांगp = 96;

		mclk_khz *= पंचांगp;
		mclk_khz /= 96;
	पूर्ण

	pll_भाग_fb = (reg15 & 0x01) << 8;
	pll_भाग_fb += reg16;
	pll_भाग_fb += 32;

	भाग = 9000 * pll_भाग_fb * 4;
	भाग /= mclk_khz;

	अगर (dev->cfg->ts_mode == M88DS3103_TS_SERIAL) अणु
		reg11 |= 0x02;

		अगर (भाग <= 32) अणु
			N = 2;

			f0 = 0;
			f1 = भाग / N;
			f2 = भाग - f1;
			f3 = 0;
		पूर्ण अन्यथा अगर (भाग <= 34) अणु
			N = 3;

			f0 = भाग / N;
			f1 = (भाग - f0) / (N - 1);
			f2 = भाग - f0 - f1;
			f3 = 0;
		पूर्ण अन्यथा अगर (भाग <= 64) अणु
			N = 4;

			f0 = भाग / N;
			f1 = (भाग - f0) / (N - 1);
			f2 = (भाग - f0 - f1) / (N - 2);
			f3 = भाग - f0 - f1 - f2;
		पूर्ण अन्यथा अणु
			N = 4;

			f0 = 16;
			f1 = 16;
			f2 = 16;
			f3 = 16;
		पूर्ण

		अगर (f0 == 16)
			f0 = 0;
		अन्यथा अगर ((f0 < 8) && (f0 != 0))
			f0 = 8;

		अगर (f1 == 16)
			f1 = 0;
		अन्यथा अगर ((f1 < 8) && (f1 != 0))
			f1 = 8;

		अगर (f2 == 16)
			f2 = 0;
		अन्यथा अगर ((f2 < 8) && (f2 != 0))
			f2 = 8;

		अगर (f3 == 16)
			f3 = 0;
		अन्यथा अगर ((f3 < 8) && (f3 != 0))
			f3 = 8;
	पूर्ण अन्यथा अणु
		reg11 &= ~0x02;

		अगर (भाग <= 32) अणु
			N = 2;

			f0 = 0;
			f1 = भाग / N;
			f2 = भाग - f1;
			f3 = 0;
		पूर्ण अन्यथा अगर (भाग <= 48) अणु
			N = 3;

			f0 = भाग / N;
			f1 = (भाग - f0) / (N - 1);
			f2 = भाग - f0 - f1;
			f3 = 0;
		पूर्ण अन्यथा अगर (भाग <= 64) अणु
			N = 4;

			f0 = भाग / N;
			f1 = (भाग - f0) / (N - 1);
			f2 = (भाग - f0 - f1) / (N - 2);
			f3 = भाग - f0 - f1 - f2;
		पूर्ण अन्यथा अणु
			N = 4;

			f0 = 16;
			f1 = 16;
			f2 = 16;
			f3 = 16;
		पूर्ण

		अगर (f0 == 16)
			f0 = 0;
		अन्यथा अगर ((f0 < 9) && (f0 != 0))
			f0 = 9;

		अगर (f1 == 16)
			f1 = 0;
		अन्यथा अगर ((f1 < 9) && (f1 != 0))
			f1 = 9;

		अगर (f2 == 16)
			f2 = 0;
		अन्यथा अगर ((f2 < 9) && (f2 != 0))
			f2 = 9;

		अगर (f3 == 16)
			f3 = 0;
		अन्यथा अगर ((f3 < 9) && (f3 != 0))
			f3 = 9;
	पूर्ण

	sm = N - 1;

	/* Write to रेजिस्टरs */
	//reg15 &= 0x01;
	//reg15 |= (pll_भाग_fb >> 8) & 0x01;

	//reg16 = pll_भाग_fb & 0xFF;

	reg1D &= ~0x03;
	reg1D |= sm;
	reg1D |= 0x80;

	reg1E = ((f3 << 4) + f2) & 0xFF;
	reg1F = ((f1 << 4) + f0) & 0xFF;

	m88ds3103b_dt_ग_लिखो(dev, 0x05, 0x40);
	m88ds3103b_dt_ग_लिखो(dev, 0x11, 0x08);
	m88ds3103b_dt_ग_लिखो(dev, 0x1D, reg1D);
	m88ds3103b_dt_ग_लिखो(dev, 0x1E, reg1E);
	m88ds3103b_dt_ग_लिखो(dev, 0x1F, reg1F);

	m88ds3103b_dt_ग_लिखो(dev, 0x17, 0xc1);
	m88ds3103b_dt_ग_लिखो(dev, 0x17, 0x81);

	usleep_range(5000, 5500);

	m88ds3103b_dt_ग_लिखो(dev, 0x05, 0x00);
	m88ds3103b_dt_ग_लिखो(dev, 0x11, 0x0A);

	usleep_range(5000, 5500);

	वापस 0;
पूर्ण

अटल पूर्णांक m88ds3103_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, len;
	स्थिर काष्ठा m88ds3103_reg_val *init;
	u8 u8पंचांगp, u8पंचांगp1 = 0, u8पंचांगp2 = 0; /* silence compiler warning */
	u8 buf[3];
	u16 u16पंचांगp;
	u32 tuner_frequency_khz, target_mclk, u32पंचांगp;
	s32 s32पंचांगp;
	अटल स्थिर काष्ठा reg_sequence reset_buf[] = अणु
		अणु0x07, 0x80पूर्ण, अणु0x07, 0x00पूर्ण
	पूर्ण;

	dev_dbg(&client->dev,
		"delivery_system=%d modulation=%d frequency=%u symbol_rate=%d inversion=%d pilot=%d rolloff=%d\n",
		c->delivery_प्रणाली, c->modulation, c->frequency, c->symbol_rate,
		c->inversion, c->pilot, c->rolloff);

	अगर (!dev->warm) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	/* reset */
	ret = regmap_multi_reg_ग_लिखो(dev->regmap, reset_buf, 2);
	अगर (ret)
		जाओ err;

	/* Disable demod घड़ी path */
	अगर (dev->chip_id == M88RS6000_CHIP_ID) अणु
		अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
			ret = regmap_पढ़ो(dev->regmap, 0xb2, &u32पंचांगp);
			अगर (ret)
				जाओ err;
			अगर (u32पंचांगp == 0x01) अणु
				ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x00);
				अगर (ret)
					जाओ err;
				ret = regmap_ग_लिखो(dev->regmap, 0xb2, 0x00);
				अगर (ret)
					जाओ err;
			पूर्ण
		पूर्ण

		ret = regmap_ग_लिखो(dev->regmap, 0x06, 0xe0);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (fe->ops.tuner_ops.get_frequency) अणु
		ret = fe->ops.tuner_ops.get_frequency(fe, &tuner_frequency_khz);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		/*
		 * Use nominal target frequency as tuner driver करोes not provide
		 * actual frequency used. Carrier offset calculation is not
		 * valid.
		 */
		tuner_frequency_khz = c->frequency;
	पूर्ण

	/* set M88RS6000/DS3103B demod मुख्य mclk and ts mclk from tuner die */
	अगर (dev->chip_id == M88RS6000_CHIP_ID) अणु
		अगर (c->symbol_rate > 45010000)
			dev->mclk = 110250000;
		अन्यथा
			dev->mclk = 96000000;

		अगर (c->delivery_प्रणाली == SYS_DVBS)
			target_mclk = 96000000;
		अन्यथा
			target_mclk = 144000000;

		अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
			m88ds3103b_select_mclk(dev);
			m88ds3103b_set_mclk(dev, target_mclk / 1000);
		पूर्ण

		/* Enable demod घड़ी path */
		ret = regmap_ग_लिखो(dev->regmap, 0x06, 0x00);
		अगर (ret)
			जाओ err;
		usleep_range(10000, 20000);
	पूर्ण अन्यथा अणु
	/* set M88DS3103 mclk and ts mclk. */
		dev->mclk = 96000000;

		चयन (dev->cfg->ts_mode) अणु
		हाल M88DS3103_TS_SERIAL:
		हाल M88DS3103_TS_SERIAL_D7:
			target_mclk = dev->cfg->ts_clk;
			अवरोध;
		हाल M88DS3103_TS_PARALLEL:
		हाल M88DS3103_TS_CI:
			अगर (c->delivery_प्रणाली == SYS_DVBS)
				target_mclk = 96000000;
			अन्यथा अणु
				अगर (c->symbol_rate < 18000000)
					target_mclk = 96000000;
				अन्यथा अगर (c->symbol_rate < 28000000)
					target_mclk = 144000000;
				अन्यथा
					target_mclk = 192000000;
			पूर्ण
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid ts_mode\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		चयन (target_mclk) अणु
		हाल 96000000:
			u8पंचांगp1 = 0x02; /* 0b10 */
			u8पंचांगp2 = 0x01; /* 0b01 */
			अवरोध;
		हाल 144000000:
			u8पंचांगp1 = 0x00; /* 0b00 */
			u8पंचांगp2 = 0x01; /* 0b01 */
			अवरोध;
		हाल 192000000:
			u8पंचांगp1 = 0x03; /* 0b11 */
			u8पंचांगp2 = 0x00; /* 0b00 */
			अवरोध;
		पूर्ण
		ret = m88ds3103_update_bits(dev, 0x22, 0xc0, u8पंचांगp1 << 6);
		अगर (ret)
			जाओ err;
		ret = m88ds3103_update_bits(dev, 0x24, 0xc0, u8पंचांगp2 << 6);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0xb2, 0x01);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x01);
	अगर (ret)
		जाओ err;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		अगर (dev->chip_id == M88RS6000_CHIP_ID) अणु
			len = ARRAY_SIZE(m88rs6000_dvbs_init_reg_vals);
			init = m88rs6000_dvbs_init_reg_vals;
		पूर्ण अन्यथा अणु
			len = ARRAY_SIZE(m88ds3103_dvbs_init_reg_vals);
			init = m88ds3103_dvbs_init_reg_vals;
		पूर्ण
		अवरोध;
	हाल SYS_DVBS2:
		अगर (dev->chip_id == M88RS6000_CHIP_ID) अणु
			len = ARRAY_SIZE(m88rs6000_dvbs2_init_reg_vals);
			init = m88rs6000_dvbs2_init_reg_vals;
		पूर्ण अन्यथा अणु
			len = ARRAY_SIZE(m88ds3103_dvbs2_init_reg_vals);
			init = m88ds3103_dvbs2_init_reg_vals;
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid delivery_system\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* program init table */
	अगर (c->delivery_प्रणाली != dev->delivery_प्रणाली) अणु
		ret = m88ds3103_wr_reg_val_tab(dev, init, len);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (dev->chip_id == M88RS6000_CHIP_ID) अणु
		अगर (c->delivery_प्रणाली == SYS_DVBS2 &&
		    c->symbol_rate <= 5000000) अणु
			ret = regmap_ग_लिखो(dev->regmap, 0xc0, 0x04);
			अगर (ret)
				जाओ err;
			buf[0] = 0x09;
			buf[1] = 0x22;
			buf[2] = 0x88;
			ret = regmap_bulk_ग_लिखो(dev->regmap, 0x8a, buf, 3);
			अगर (ret)
				जाओ err;
		पूर्ण
		ret = m88ds3103_update_bits(dev, 0x9d, 0x08, 0x08);
		अगर (ret)
			जाओ err;

		अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
			buf[0] = m88ds3103b_dt_पढ़ो(dev, 0x15);
			buf[1] = m88ds3103b_dt_पढ़ो(dev, 0x16);

			अगर (c->symbol_rate > 45010000) अणु
				buf[0] &= ~0x03;
				buf[0] |= 0x02;
				buf[0] |= ((147 - 32) >> 8) & 0x01;
				buf[1] = (147 - 32) & 0xFF;

				dev->mclk = 110250 * 1000;
			पूर्ण अन्यथा अणु
				buf[0] &= ~0x03;
				buf[0] |= ((128 - 32) >> 8) & 0x01;
				buf[1] = (128 - 32) & 0xFF;

				dev->mclk = 96000 * 1000;
			पूर्ण
			m88ds3103b_dt_ग_लिखो(dev, 0x15, buf[0]);
			m88ds3103b_dt_ग_लिखो(dev, 0x16, buf[1]);

			regmap_पढ़ो(dev->regmap, 0x30, &u32पंचांगp);
			u32पंचांगp &= ~0x80;
			regmap_ग_लिखो(dev->regmap, 0x30, u32पंचांगp & 0xff);
		पूर्ण

		ret = regmap_ग_लिखो(dev->regmap, 0xf1, 0x01);
		अगर (ret)
			जाओ err;

		अगर (dev->chiptype != M88DS3103_CHIPTYPE_3103B) अणु
			ret = m88ds3103_update_bits(dev, 0x30, 0x80, 0x80);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	चयन (dev->cfg->ts_mode) अणु
	हाल M88DS3103_TS_SERIAL:
		u8पंचांगp1 = 0x00;
		u8पंचांगp = 0x06;
		अवरोध;
	हाल M88DS3103_TS_SERIAL_D7:
		u8पंचांगp1 = 0x20;
		u8पंचांगp = 0x06;
		अवरोध;
	हाल M88DS3103_TS_PARALLEL:
		u8पंचांगp = 0x02;
		अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
			u8पंचांगp = 0x01;
			u8पंचांगp1 = 0x01;
		पूर्ण
		अवरोध;
	हाल M88DS3103_TS_CI:
		u8पंचांगp = 0x03;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid ts_mode\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (dev->cfg->ts_clk_pol)
		u8पंचांगp |= 0x40;

	/* TS mode */
	ret = regmap_ग_लिखो(dev->regmap, 0xfd, u8पंचांगp);
	अगर (ret)
		जाओ err;

	चयन (dev->cfg->ts_mode) अणु
	हाल M88DS3103_TS_SERIAL:
	हाल M88DS3103_TS_SERIAL_D7:
		ret = m88ds3103_update_bits(dev, 0x29, 0x20, u8पंचांगp1);
		अगर (ret)
			जाओ err;
		u16पंचांगp = 0;
		u8पंचांगp1 = 0x3f;
		u8पंचांगp2 = 0x3f;
		अवरोध;
	हाल M88DS3103_TS_PARALLEL:
		अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
			ret = m88ds3103_update_bits(dev, 0x29, 0x01, u8पंचांगp1);
			अगर (ret)
				जाओ err;
		पूर्ण
		fallthrough;
	शेष:
		u16पंचांगp = DIV_ROUND_UP(target_mclk, dev->cfg->ts_clk);
		u8पंचांगp1 = u16पंचांगp / 2 - 1;
		u8पंचांगp2 = DIV_ROUND_UP(u16पंचांगp, 2) - 1;
	पूर्ण

	dev_dbg(&client->dev, "target_mclk=%u ts_clk=%u ts_clk_divide_ratio=%u\n",
		target_mclk, dev->cfg->ts_clk, u16पंचांगp);

	/* u8पंचांगp1[5:2] => fe[3:0], u8पंचांगp1[1:0] => ea[7:6] */
	/* u8पंचांगp2[5:0] => ea[5:0] */
	u8पंचांगp = (u8पंचांगp1 >> 2) & 0x0f;
	ret = regmap_update_bits(dev->regmap, 0xfe, 0x0f, u8पंचांगp);
	अगर (ret)
		जाओ err;
	u8पंचांगp = ((u8पंचांगp1 & 0x03) << 6) | u8पंचांगp2 >> 0;
	ret = regmap_ग_लिखो(dev->regmap, 0xea, u8पंचांगp);
	अगर (ret)
		जाओ err;

	अगर (c->symbol_rate <= 3000000)
		u8पंचांगp = 0x20;
	अन्यथा अगर (c->symbol_rate <= 10000000)
		u8पंचांगp = 0x10;
	अन्यथा
		u8पंचांगp = 0x06;

	अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B)
		m88ds3103b_set_mclk(dev, target_mclk / 1000);

	ret = regmap_ग_लिखो(dev->regmap, 0xc3, 0x08);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0xc8, u8पंचांगp);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0xc4, 0x08);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0xc7, 0x00);
	अगर (ret)
		जाओ err;

	u16पंचांगp = DIV_ROUND_CLOSEST_ULL((u64)c->symbol_rate * 0x10000, dev->mclk);
	buf[0] = (u16पंचांगp >> 0) & 0xff;
	buf[1] = (u16पंचांगp >> 8) & 0xff;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x61, buf, 2);
	अगर (ret)
		जाओ err;

	ret = m88ds3103_update_bits(dev, 0x4d, 0x02, dev->cfg->spec_inv << 1);
	अगर (ret)
		जाओ err;

	ret = m88ds3103_update_bits(dev, 0x30, 0x10, dev->cfg->agc_inv << 4);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x33, dev->cfg->agc);
	अगर (ret)
		जाओ err;

	अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
		/* enable/disable 192M LDPC घड़ी */
		ret = m88ds3103_update_bits(dev, 0x29, 0x10,
				(c->delivery_प्रणाली == SYS_DVBS) ? 0x10 : 0x0);
		अगर (ret)
			जाओ err;

		ret = m88ds3103_update_bits(dev, 0xc9, 0x08, 0x08);
		अगर (ret)
			जाओ err;
	पूर्ण

	dev_dbg(&client->dev, "carrier offset=%d\n",
		(tuner_frequency_khz - c->frequency));

	/* Use 32-bit calc as there is no s64 version of DIV_ROUND_CLOSEST() */
	s32पंचांगp = 0x10000 * (tuner_frequency_khz - c->frequency);
	s32पंचांगp = DIV_ROUND_CLOSEST(s32पंचांगp, dev->mclk / 1000);
	buf[0] = (s32पंचांगp >> 0) & 0xff;
	buf[1] = (s32पंचांगp >> 8) & 0xff;
	ret = regmap_bulk_ग_लिखो(dev->regmap, 0x5e, buf, 2);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x00);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0xb2, 0x00);
	अगर (ret)
		जाओ err;

	dev->delivery_प्रणाली = c->delivery_प्रणाली;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, len, rem;
	अचिन्हित पूर्णांक uपंचांगp;
	स्थिर काष्ठा firmware *firmware;
	स्थिर अक्षर *name;

	dev_dbg(&client->dev, "\n");

	/* set cold state by शेष */
	dev->warm = false;

	/* wake up device from sleep */
	ret = m88ds3103_update_bits(dev, 0x08, 0x01, 0x01);
	अगर (ret)
		जाओ err;
	ret = m88ds3103_update_bits(dev, 0x04, 0x01, 0x00);
	अगर (ret)
		जाओ err;
	ret = m88ds3103_update_bits(dev, 0x23, 0x10, 0x00);
	अगर (ret)
		जाओ err;

	/* firmware status */
	ret = regmap_पढ़ो(dev->regmap, 0xb9, &uपंचांगp);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "firmware=%02x\n", uपंचांगp);

	अगर (uपंचांगp)
		जाओ warm;

	/* global reset, global diseqc reset, global fec reset */
	ret = regmap_ग_लिखो(dev->regmap, 0x07, 0xe0);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x07, 0x00);
	अगर (ret)
		जाओ err;

	/* cold state - try to करोwnload firmware */
	dev_info(&client->dev, "found a '%s' in cold state\n",
		 dev->fe.ops.info.name);

	अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B)
		name = M88DS3103B_FIRMWARE;
	अन्यथा अगर (dev->chip_id == M88RS6000_CHIP_ID)
		name = M88RS6000_FIRMWARE;
	अन्यथा
		name = M88DS3103_FIRMWARE;

	/* request the firmware, this will block and समयout */
	ret = request_firmware(&firmware, name, &client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "firmware file '%s' not found\n", name);
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "downloading firmware from file '%s'\n", name);

	ret = regmap_ग_लिखो(dev->regmap, 0xb2, 0x01);
	अगर (ret)
		जाओ err_release_firmware;

	क्रम (rem = firmware->size; rem > 0; rem -= (dev->cfg->i2c_wr_max - 1)) अणु
		len = min(dev->cfg->i2c_wr_max - 1, rem);
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0xb0,
					&firmware->data[firmware->size - rem],
					len);
		अगर (ret) अणु
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			जाओ err_release_firmware;
		पूर्ण
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0xb2, 0x00);
	अगर (ret)
		जाओ err_release_firmware;

	release_firmware(firmware);

	ret = regmap_पढ़ो(dev->regmap, 0xb9, &uपंचांगp);
	अगर (ret)
		जाओ err;

	अगर (!uपंचांगp) अणु
		ret = -EINVAL;
		dev_info(&client->dev, "firmware did not run\n");
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "found a '%s' in warm state\n",
		 dev->fe.ops.info.name);
	dev_info(&client->dev, "firmware version: %X.%X\n",
		 (uपंचांगp >> 4) & 0xf, (uपंचांगp >> 0 & 0xf));

	अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
		m88ds3103b_dt_ग_लिखो(dev, 0x21, 0x92);
		m88ds3103b_dt_ग_लिखो(dev, 0x15, 0x6C);
		m88ds3103b_dt_ग_लिखो(dev, 0x17, 0xC1);
		m88ds3103b_dt_ग_लिखो(dev, 0x17, 0x81);
	पूर्ण
warm:
	/* warm state */
	dev->warm = true;

	/* init stats here in order संकेत app which stats are supported */
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	dev_dbg(&client->dev, "\n");

	dev->fe_status = 0;
	dev->delivery_प्रणाली = SYS_UNDEFINED;

	/* TS Hi-Z */
	अगर (dev->chip_id == M88RS6000_CHIP_ID)
		uपंचांगp = 0x29;
	अन्यथा
		uपंचांगp = 0x27;
	ret = m88ds3103_update_bits(dev, uपंचांगp, 0x01, 0x00);
	अगर (ret)
		जाओ err;

	/* sleep */
	ret = m88ds3103_update_bits(dev, 0x08, 0x01, 0x00);
	अगर (ret)
		जाओ err;
	ret = m88ds3103_update_bits(dev, 0x04, 0x01, 0x01);
	अगर (ret)
		जाओ err;
	ret = m88ds3103_update_bits(dev, 0x23, 0x10, 0x10);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_get_frontend(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 buf[3];

	dev_dbg(&client->dev, "\n");

	अगर (!dev->warm || !(dev->fe_status & FE_HAS_LOCK)) अणु
		ret = 0;
		जाओ err;
	पूर्ण

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		ret = regmap_bulk_पढ़ो(dev->regmap, 0xe0, &buf[0], 1);
		अगर (ret)
			जाओ err;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0xe6, &buf[1], 1);
		अगर (ret)
			जाओ err;

		चयन ((buf[0] >> 2) & 0x01) अणु
		हाल 0:
			c->inversion = INVERSION_OFF;
			अवरोध;
		हाल 1:
			c->inversion = INVERSION_ON;
			अवरोध;
		पूर्ण

		चयन ((buf[1] >> 5) & 0x07) अणु
		हाल 0:
			c->fec_inner = FEC_7_8;
			अवरोध;
		हाल 1:
			c->fec_inner = FEC_5_6;
			अवरोध;
		हाल 2:
			c->fec_inner = FEC_3_4;
			अवरोध;
		हाल 3:
			c->fec_inner = FEC_2_3;
			अवरोध;
		हाल 4:
			c->fec_inner = FEC_1_2;
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid fec_inner\n");
		पूर्ण

		c->modulation = QPSK;

		अवरोध;
	हाल SYS_DVBS2:
		ret = regmap_bulk_पढ़ो(dev->regmap, 0x7e, &buf[0], 1);
		अगर (ret)
			जाओ err;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x89, &buf[1], 1);
		अगर (ret)
			जाओ err;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0xf2, &buf[2], 1);
		अगर (ret)
			जाओ err;

		चयन ((buf[0] >> 0) & 0x0f) अणु
		हाल 2:
			c->fec_inner = FEC_2_5;
			अवरोध;
		हाल 3:
			c->fec_inner = FEC_1_2;
			अवरोध;
		हाल 4:
			c->fec_inner = FEC_3_5;
			अवरोध;
		हाल 5:
			c->fec_inner = FEC_2_3;
			अवरोध;
		हाल 6:
			c->fec_inner = FEC_3_4;
			अवरोध;
		हाल 7:
			c->fec_inner = FEC_4_5;
			अवरोध;
		हाल 8:
			c->fec_inner = FEC_5_6;
			अवरोध;
		हाल 9:
			c->fec_inner = FEC_8_9;
			अवरोध;
		हाल 10:
			c->fec_inner = FEC_9_10;
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid fec_inner\n");
		पूर्ण

		चयन ((buf[0] >> 5) & 0x01) अणु
		हाल 0:
			c->pilot = PILOT_OFF;
			अवरोध;
		हाल 1:
			c->pilot = PILOT_ON;
			अवरोध;
		पूर्ण

		चयन ((buf[0] >> 6) & 0x07) अणु
		हाल 0:
			c->modulation = QPSK;
			अवरोध;
		हाल 1:
			c->modulation = PSK_8;
			अवरोध;
		हाल 2:
			c->modulation = APSK_16;
			अवरोध;
		हाल 3:
			c->modulation = APSK_32;
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid modulation\n");
		पूर्ण

		चयन ((buf[1] >> 7) & 0x01) अणु
		हाल 0:
			c->inversion = INVERSION_OFF;
			अवरोध;
		हाल 1:
			c->inversion = INVERSION_ON;
			अवरोध;
		पूर्ण

		चयन ((buf[2] >> 0) & 0x03) अणु
		हाल 0:
			c->rolloff = ROLLOFF_35;
			अवरोध;
		हाल 1:
			c->rolloff = ROLLOFF_25;
			अवरोध;
		हाल 2:
			c->rolloff = ROLLOFF_20;
			अवरोध;
		शेष:
			dev_dbg(&client->dev, "invalid rolloff\n");
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid delivery_system\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_bulk_पढ़ो(dev->regmap, 0x6d, buf, 2);
	अगर (ret)
		जाओ err;

	c->symbol_rate = DIV_ROUND_CLOSEST_ULL((u64)(buf[1] << 8 | buf[0] << 0) * dev->mclk, 0x10000);

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
	अन्यथा
		*snr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक m88ds3103_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;

	*ber = dev->dvbv3_ber;

	वापस 0;
पूर्ण

अटल पूर्णांक m88ds3103_set_tone(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_tone_mode fe_sec_tone_mode)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp, tone, reg_a1_mask;

	dev_dbg(&client->dev, "fe_sec_tone_mode=%d\n", fe_sec_tone_mode);

	अगर (!dev->warm) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (fe_sec_tone_mode) अणु
	हाल SEC_TONE_ON:
		tone = 0;
		reg_a1_mask = 0x47;
		अवरोध;
	हाल SEC_TONE_OFF:
		tone = 1;
		reg_a1_mask = 0x00;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid fe_sec_tone_mode\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	uपंचांगp = tone << 7 | dev->cfg->envelope_mode << 5;
	ret = m88ds3103_update_bits(dev, 0xa2, 0xe0, uपंचांगp);
	अगर (ret)
		जाओ err;

	uपंचांगp = 1 << 2;
	ret = m88ds3103_update_bits(dev, 0xa1, reg_a1_mask, uपंचांगp);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_set_voltage(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_voltage fe_sec_voltage)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	bool voltage_sel, voltage_dis;

	dev_dbg(&client->dev, "fe_sec_voltage=%d\n", fe_sec_voltage);

	अगर (!dev->warm) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	चयन (fe_sec_voltage) अणु
	हाल SEC_VOLTAGE_18:
		voltage_sel = true;
		voltage_dis = false;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		voltage_sel = false;
		voltage_dis = false;
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		voltage_sel = false;
		voltage_dis = true;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid fe_sec_voltage\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* output pin polarity */
	voltage_sel ^= dev->cfg->lnb_hv_pol;
	voltage_dis ^= dev->cfg->lnb_en_pol;

	uपंचांगp = voltage_dis << 1 | voltage_sel << 0;
	ret = m88ds3103_update_bits(dev, 0xa2, 0x03, uपंचांगp);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_diseqc_send_master_cmd(काष्ठा dvb_frontend *fe,
		काष्ठा dvb_diseqc_master_cmd *diseqc_cmd)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	अचिन्हित दीर्घ समयout;

	dev_dbg(&client->dev, "msg=%*ph\n",
		diseqc_cmd->msg_len, diseqc_cmd->msg);

	अगर (!dev->warm) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	अगर (diseqc_cmd->msg_len < 3 || diseqc_cmd->msg_len > 6) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	uपंचांगp = dev->cfg->envelope_mode << 5;
	ret = m88ds3103_update_bits(dev, 0xa2, 0xe0, uपंचांगp);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_ग_लिखो(dev->regmap, 0xa3, diseqc_cmd->msg,
			diseqc_cmd->msg_len);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(dev->regmap, 0xa1,
			(diseqc_cmd->msg_len - 1) << 3 | 0x07);
	अगर (ret)
		जाओ err;

	/* रुको DiSEqC TX पढ़ोy */
	#घोषणा SEND_MASTER_CMD_TIMEOUT 120
	समयout = jअगरfies + msecs_to_jअगरfies(SEND_MASTER_CMD_TIMEOUT);

	/* DiSEqC message period is 13.5 ms per byte */
	uपंचांगp = diseqc_cmd->msg_len * 13500;
	usleep_range(uपंचांगp - 4000, uपंचांगp);

	क्रम (uपंचांगp = 1; !समय_after(jअगरfies, समयout) && uपंचांगp;) अणु
		ret = regmap_पढ़ो(dev->regmap, 0xa1, &uपंचांगp);
		अगर (ret)
			जाओ err;
		uपंचांगp = (uपंचांगp >> 6) & 0x1;
	पूर्ण

	अगर (uपंचांगp == 0) अणु
		dev_dbg(&client->dev, "diseqc tx took %u ms\n",
			jअगरfies_to_msecs(jअगरfies) -
			(jअगरfies_to_msecs(समयout) - SEND_MASTER_CMD_TIMEOUT));
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "diseqc tx timeout\n");

		ret = m88ds3103_update_bits(dev, 0xa1, 0xc0, 0x40);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = m88ds3103_update_bits(dev, 0xa2, 0xc0, 0x80);
	अगर (ret)
		जाओ err;

	अगर (uपंचांगp == 1) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_diseqc_send_burst(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_mini_cmd fe_sec_mini_cmd)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp, burst;
	अचिन्हित दीर्घ समयout;

	dev_dbg(&client->dev, "fe_sec_mini_cmd=%d\n", fe_sec_mini_cmd);

	अगर (!dev->warm) अणु
		ret = -EAGAIN;
		जाओ err;
	पूर्ण

	uपंचांगp = dev->cfg->envelope_mode << 5;
	ret = m88ds3103_update_bits(dev, 0xa2, 0xe0, uपंचांगp);
	अगर (ret)
		जाओ err;

	चयन (fe_sec_mini_cmd) अणु
	हाल SEC_MINI_A:
		burst = 0x02;
		अवरोध;
	हाल SEC_MINI_B:
		burst = 0x01;
		अवरोध;
	शेष:
		dev_dbg(&client->dev, "invalid fe_sec_mini_cmd\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0xa1, burst);
	अगर (ret)
		जाओ err;

	/* रुको DiSEqC TX पढ़ोy */
	#घोषणा SEND_BURST_TIMEOUT 40
	समयout = jअगरfies + msecs_to_jअगरfies(SEND_BURST_TIMEOUT);

	/* DiSEqC ToneBurst period is 12.5 ms */
	usleep_range(8500, 12500);

	क्रम (uपंचांगp = 1; !समय_after(jअगरfies, समयout) && uपंचांगp;) अणु
		ret = regmap_पढ़ो(dev->regmap, 0xa1, &uपंचांगp);
		अगर (ret)
			जाओ err;
		uपंचांगp = (uपंचांगp >> 6) & 0x1;
	पूर्ण

	अगर (uपंचांगp == 0) अणु
		dev_dbg(&client->dev, "diseqc tx took %u ms\n",
			jअगरfies_to_msecs(jअगरfies) -
			(jअगरfies_to_msecs(समयout) - SEND_BURST_TIMEOUT));
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "diseqc tx timeout\n");

		ret = m88ds3103_update_bits(dev, 0xa1, 0xc0, 0x40);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = m88ds3103_update_bits(dev, 0xa2, 0xc0, 0x80);
	अगर (ret)
		जाओ err;

	अगर (uपंचांगp == 1) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 3000;

	वापस 0;
पूर्ण

अटल व्योम m88ds3103_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88ds3103_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;

	i2c_unरेजिस्टर_device(client);
पूर्ण

अटल पूर्णांक m88ds3103_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा m88ds3103_dev *dev = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.flags = 0,
		.len = 2,
		.buf = "\x03\x11",
	पूर्ण;

	/* Open tuner I2C repeater क्रम 1 xfer, बंदs स्वतःmatically */
	ret = __i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_warn(&client->dev, "i2c wr failed=%d\n", ret);
		अगर (ret >= 0)
			ret = -EREMOTEIO;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * XXX: That is wrapper to m88ds3103_probe() via driver core in order to provide
 * proper I2C client क्रम legacy media attach binding.
 * New users must use I2C client binding directly!
 */
काष्ठा dvb_frontend *m88ds3103_attach(स्थिर काष्ठा m88ds3103_config *cfg,
				      काष्ठा i2c_adapter *i2c,
				      काष्ठा i2c_adapter **tuner_i2c_adapter)
अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info;
	काष्ठा m88ds3103_platक्रमm_data pdata = अणुपूर्ण;

	pdata.clk = cfg->घड़ी;
	pdata.i2c_wr_max = cfg->i2c_wr_max;
	pdata.ts_mode = cfg->ts_mode;
	pdata.ts_clk = cfg->ts_clk;
	pdata.ts_clk_pol = cfg->ts_clk_pol;
	pdata.spec_inv = cfg->spec_inv;
	pdata.agc = cfg->agc;
	pdata.agc_inv = cfg->agc_inv;
	pdata.clk_out = cfg->घड़ी_out;
	pdata.envelope_mode = cfg->envelope_mode;
	pdata.lnb_hv_pol = cfg->lnb_hv_pol;
	pdata.lnb_en_pol = cfg->lnb_en_pol;
	pdata.attach_in_use = true;

	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "m88ds3103", I2C_NAME_SIZE);
	board_info.addr = cfg->i2c_addr;
	board_info.platक्रमm_data = &pdata;
	client = i2c_new_client_device(i2c, &board_info);
	अगर (!i2c_client_has_driver(client))
		वापस शून्य;

	*tuner_i2c_adapter = pdata.get_i2c_adapter(client);
	वापस pdata.get_dvb_frontend(client);
पूर्ण
EXPORT_SYMBOL(m88ds3103_attach);

अटल स्थिर काष्ठा dvb_frontend_ops m88ds3103_ops = अणु
	.delsys = अणुSYS_DVBS, SYS_DVBS2पूर्ण,
	.info = अणु
		.name = "Montage Technology M88DS3103",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.frequency_tolerance_hz = 5 * MHz,
		.symbol_rate_min =  1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_8_9 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_RECOVER |
			FE_CAN_2G_MODULATION
	पूर्ण,

	.release = m88ds3103_release,

	.get_tune_settings = m88ds3103_get_tune_settings,

	.init = m88ds3103_init,
	.sleep = m88ds3103_sleep,

	.set_frontend = m88ds3103_set_frontend,
	.get_frontend = m88ds3103_get_frontend,

	.पढ़ो_status = m88ds3103_पढ़ो_status,
	.पढ़ो_snr = m88ds3103_पढ़ो_snr,
	.पढ़ो_ber = m88ds3103_पढ़ो_ber,

	.diseqc_send_master_cmd = m88ds3103_diseqc_send_master_cmd,
	.diseqc_send_burst = m88ds3103_diseqc_send_burst,

	.set_tone = m88ds3103_set_tone,
	.set_voltage = m88ds3103_set_voltage,
पूर्ण;

अटल काष्ठा dvb_frontend *m88ds3103_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा m88ds3103_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &dev->fe;
पूर्ण

अटल काष्ठा i2c_adapter *m88ds3103_get_i2c_adapter(काष्ठा i2c_client *client)
अणु
	काष्ठा m88ds3103_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस dev->muxc->adapter[0];
पूर्ण

अटल पूर्णांक m88ds3103_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा m88ds3103_dev *dev;
	काष्ठा m88ds3103_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev->client = client;
	dev->config.घड़ी = pdata->clk;
	dev->config.i2c_wr_max = pdata->i2c_wr_max;
	dev->config.ts_mode = pdata->ts_mode;
	dev->config.ts_clk = pdata->ts_clk * 1000;
	dev->config.ts_clk_pol = pdata->ts_clk_pol;
	dev->config.spec_inv = pdata->spec_inv;
	dev->config.agc_inv = pdata->agc_inv;
	dev->config.घड़ी_out = pdata->clk_out;
	dev->config.envelope_mode = pdata->envelope_mode;
	dev->config.agc = pdata->agc;
	dev->config.lnb_hv_pol = pdata->lnb_hv_pol;
	dev->config.lnb_en_pol = pdata->lnb_en_pol;
	dev->cfg = &dev->config;
	/* create regmap */
	dev->regmap_config.reg_bits = 8;
	dev->regmap_config.val_bits = 8;
	dev->regmap_config.lock_arg = dev;
	dev->regmap = devm_regmap_init_i2c(client, &dev->regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* 0x00: chip id[6:0], 0x01: chip ver[7:0], 0x02: chip ver[15:8] */
	ret = regmap_पढ़ो(dev->regmap, 0x00, &uपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;

	dev->chip_id = uपंचांगp >> 1;
	dev->chiptype = (u8)id->driver_data;

	dev_dbg(&client->dev, "chip_id=%02x\n", dev->chip_id);

	चयन (dev->chip_id) अणु
	हाल M88RS6000_CHIP_ID:
	हाल M88DS3103_CHIP_ID:
		अवरोध;
	शेष:
		ret = -ENODEV;
		dev_err(&client->dev, "Unknown device. Chip_id=%02x\n", dev->chip_id);
		जाओ err_kमुक्त;
	पूर्ण

	चयन (dev->cfg->घड़ी_out) अणु
	हाल M88DS3103_CLOCK_OUT_DISABLED:
		uपंचांगp = 0x80;
		अवरोध;
	हाल M88DS3103_CLOCK_OUT_ENABLED:
		uपंचांगp = 0x00;
		अवरोध;
	हाल M88DS3103_CLOCK_OUT_ENABLED_DIV2:
		uपंचांगp = 0x10;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_kमुक्त;
	पूर्ण

	अगर (!pdata->ts_clk) अणु
		ret = -EINVAL;
		जाओ err_kमुक्त;
	पूर्ण

	/* 0x29 रेजिस्टर is defined dअगरferently क्रम m88rs6000. */
	/* set पूर्णांकernal tuner address to 0x21 */
	अगर (dev->chip_id == M88RS6000_CHIP_ID)
		uपंचांगp = 0x00;

	ret = regmap_ग_लिखो(dev->regmap, 0x29, uपंचांगp);
	अगर (ret)
		जाओ err_kमुक्त;

	/* sleep */
	ret = m88ds3103_update_bits(dev, 0x08, 0x01, 0x00);
	अगर (ret)
		जाओ err_kमुक्त;
	ret = m88ds3103_update_bits(dev, 0x04, 0x01, 0x01);
	अगर (ret)
		जाओ err_kमुक्त;
	ret = m88ds3103_update_bits(dev, 0x23, 0x10, 0x10);
	अगर (ret)
		जाओ err_kमुक्त;

	/* create mux i2c adapter क्रम tuner */
	dev->muxc = i2c_mux_alloc(client->adapter, &client->dev, 1, 0, 0,
				  m88ds3103_select, शून्य);
	अगर (!dev->muxc) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण
	dev->muxc->priv = dev;
	ret = i2c_mux_add_adapter(dev->muxc, 0, 0, 0);
	अगर (ret)
		जाओ err_kमुक्त;

	/* create dvb_frontend */
	स_नकल(&dev->fe.ops, &m88ds3103_ops, माप(काष्ठा dvb_frontend_ops));
	अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B)
		strscpy(dev->fe.ops.info.name, "Montage Technology M88DS3103B",
			माप(dev->fe.ops.info.name));
	अन्यथा अगर (dev->chip_id == M88RS6000_CHIP_ID)
		strscpy(dev->fe.ops.info.name, "Montage Technology M88RS6000",
			माप(dev->fe.ops.info.name));
	अगर (!pdata->attach_in_use)
		dev->fe.ops.release = शून्य;
	dev->fe.demodulator_priv = dev;
	i2c_set_clientdata(client, dev);

	/* setup callbacks */
	pdata->get_dvb_frontend = m88ds3103_get_dvb_frontend;
	pdata->get_i2c_adapter = m88ds3103_get_i2c_adapter;

	अगर (dev->chiptype == M88DS3103_CHIPTYPE_3103B) अणु
		/* enable i2c repeater क्रम tuner */
		m88ds3103_update_bits(dev, 0x11, 0x01, 0x01);

		/* get frontend address */
		ret = regmap_पढ़ो(dev->regmap, 0x29, &uपंचांगp);
		अगर (ret)
			जाओ err_kमुक्त;
		dev->dt_addr = ((uपंचांगp & 0x80) == 0) ? 0x42 >> 1 : 0x40 >> 1;
		dev_dbg(&client->dev, "dt addr is 0x%02x\n", dev->dt_addr);

		dev->dt_client = i2c_new_dummy_device(client->adapter,
						      dev->dt_addr);
		अगर (IS_ERR(dev->dt_client)) अणु
			ret = PTR_ERR(dev->dt_client);
			जाओ err_kमुक्त;
		पूर्ण
	पूर्ण

	वापस 0;
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88ds3103_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा m88ds3103_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	अगर (dev->dt_client)
		i2c_unरेजिस्टर_device(dev->dt_client);

	i2c_mux_del_adapters(dev->muxc);

	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id m88ds3103_id_table[] = अणु
	अणु"m88ds3103",  M88DS3103_CHIPTYPE_3103पूर्ण,
	अणु"m88rs6000",  M88DS3103_CHIPTYPE_RS6000पूर्ण,
	अणु"m88ds3103b", M88DS3103_CHIPTYPE_3103Bपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, m88ds3103_id_table);

अटल काष्ठा i2c_driver m88ds3103_driver = अणु
	.driver = अणु
		.name	= "m88ds3103",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= m88ds3103_probe,
	.हटाओ		= m88ds3103_हटाओ,
	.id_table	= m88ds3103_id_table,
पूर्ण;

module_i2c_driver(m88ds3103_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Montage Technology M88DS3103 DVB-S/S2 demodulator driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(M88DS3103_FIRMWARE);
MODULE_FIRMWARE(M88RS6000_FIRMWARE);
MODULE_FIRMWARE(M88DS3103B_FIRMWARE);
