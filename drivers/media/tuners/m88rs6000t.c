<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the पूर्णांकernal tuner of Montage M88RS6000
 *
 * Copyright (C) 2014 Max nibble <nibble.max@gmail.com>
 */

#समावेश "m88rs6000t.h"
#समावेश <linux/regmap.h>

काष्ठा m88rs6000t_dev अणु
	काष्ठा m88rs6000t_config cfg;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	u32 frequency_khz;
पूर्ण;

काष्ठा m88rs6000t_reg_val अणु
	u8 reg;
	u8 val;
पूर्ण;

/* set demod मुख्य mclk and ts mclk */
अटल पूर्णांक m88rs6000t_set_demod_mclk(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 reg11, reg15, reg16, reg1D, reg1E, reg1F;
	u8 N, f0 = 0, f1 = 0, f2 = 0, f3 = 0;
	u16 pll_भाग_fb;
	u32 भाग, ts_mclk;
	अचिन्हित पूर्णांक uपंचांगp;
	पूर्णांक ret;

	/* select demod मुख्य mclk */
	ret = regmap_पढ़ो(dev->regmap, 0x15, &uपंचांगp);
	अगर (ret)
		जाओ err;
	reg15 = uपंचांगp;
	अगर (c->symbol_rate > 45010000) अणु
		reg11 = 0x0E;
		reg15 |= 0x02;
		reg16 = 115; /* mclk = 110.25MHz */
	पूर्ण अन्यथा अणु
		reg11 = 0x0A;
		reg15 &= ~0x02;
		reg16 = 96; /* mclk = 96MHz */
	पूर्ण

	/* set ts mclk */
	अगर (c->delivery_प्रणाली == SYS_DVBS)
		ts_mclk = 96000;
	अन्यथा
		ts_mclk = 144000;

	pll_भाग_fb = (reg15 & 0x01) << 8;
	pll_भाग_fb += reg16;
	pll_भाग_fb += 32;

	भाग = 36000 * pll_भाग_fb;
	भाग /= ts_mclk;

	अगर (भाग <= 32) अणु
		N = 2;
		f0 = 0;
		f1 = भाग / 2;
		f2 = भाग - f1;
		f3 = 0;
	पूर्ण अन्यथा अगर (भाग <= 48) अणु
		N = 3;
		f0 = भाग / 3;
		f1 = (भाग - f0) / 2;
		f2 = भाग - f0 - f1;
		f3 = 0;
	पूर्ण अन्यथा अगर (भाग <= 64) अणु
		N = 4;
		f0 = भाग / 4;
		f1 = (भाग - f0) / 3;
		f2 = (भाग - f0 - f1) / 2;
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
	अगर (f1 == 16)
		f1 = 0;
	अगर (f2 == 16)
		f2 = 0;
	अगर (f3 == 16)
		f3 = 0;

	ret = regmap_पढ़ो(dev->regmap, 0x1D, &uपंचांगp);
	अगर (ret)
		जाओ err;
	reg1D = uपंचांगp;
	reg1D &= ~0x03;
	reg1D |= N - 1;
	reg1E = ((f3 << 4) + f2) & 0xFF;
	reg1F = ((f1 << 4) + f0) & 0xFF;

	/* program and recalibrate demod PLL */
	ret = regmap_ग_लिखो(dev->regmap, 0x05, 0x40);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x11, 0x08);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x15, reg15);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x16, reg16);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x1D, reg1D);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x1E, reg1E);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x1F, reg1F);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x17, 0xc1);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x17, 0x81);
	अगर (ret)
		जाओ err;
	usleep_range(5000, 50000);
	ret = regmap_ग_लिखो(dev->regmap, 0x05, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x11, reg11);
	अगर (ret)
		जाओ err;
	usleep_range(5000, 50000);
err:
	अगर (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs6000t_set_pll_freq(काष्ठा m88rs6000t_dev *dev,
			u32 tuner_freq_MHz)
अणु
	u32 fcry_KHz, ulNDiv1, ulNDiv2, ulNDiv;
	u8 refDiv, ucLoDiv1, ucLomod1, ucLoDiv2, ucLomod2, ucLoDiv, ucLomod;
	u8 reg27, reg29, reg42, reg42buf;
	अचिन्हित पूर्णांक uपंचांगp;
	पूर्णांक ret;

	fcry_KHz = 27000; /* in kHz */
	refDiv = 27;

	ret = regmap_ग_लिखो(dev->regmap, 0x36, (refDiv - 8));
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x31, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x2c, 0x02);
	अगर (ret)
		जाओ err;

	अगर (tuner_freq_MHz >= 1550) अणु
		ucLoDiv1 = 2;
		ucLomod1 = 0;
		ucLoDiv2 = 2;
		ucLomod2 = 0;
	पूर्ण अन्यथा अगर (tuner_freq_MHz >= 1380) अणु
		ucLoDiv1 = 3;
		ucLomod1 = 16;
		ucLoDiv2 = 2;
		ucLomod2 = 0;
	पूर्ण अन्यथा अगर (tuner_freq_MHz >= 1070) अणु
		ucLoDiv1 = 3;
		ucLomod1 = 16;
		ucLoDiv2 = 3;
		ucLomod2 = 16;
	पूर्ण अन्यथा अगर (tuner_freq_MHz >= 1000) अणु
		ucLoDiv1 = 3;
		ucLomod1 = 16;
		ucLoDiv2 = 4;
		ucLomod2 = 64;
	पूर्ण अन्यथा अगर (tuner_freq_MHz >= 775) अणु
		ucLoDiv1 = 4;
		ucLomod1 = 64;
		ucLoDiv2 = 4;
		ucLomod2 = 64;
	पूर्ण अन्यथा अगर (tuner_freq_MHz >= 700) अणु
		ucLoDiv1 = 6;
		ucLomod1 = 48;
		ucLoDiv2 = 4;
		ucLomod2 = 64;
	पूर्ण अन्यथा अगर (tuner_freq_MHz >= 520) अणु
		ucLoDiv1 = 6;
		ucLomod1 = 48;
		ucLoDiv2 = 6;
		ucLomod2 = 48;
	पूर्ण अन्यथा अणु
		ucLoDiv1 = 8;
		ucLomod1 = 96;
		ucLoDiv2 = 8;
		ucLomod2 = 96;
	पूर्ण

	ulNDiv1 = ((tuner_freq_MHz * ucLoDiv1 * 1000) * refDiv
			/ fcry_KHz - 1024) / 2;
	ulNDiv2 = ((tuner_freq_MHz * ucLoDiv2 * 1000) * refDiv
			/ fcry_KHz - 1024) / 2;

	reg27 = (((ulNDiv1 >> 8) & 0x0F) + ucLomod1) & 0x7F;
	ret = regmap_ग_लिखो(dev->regmap, 0x27, reg27);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x28, (u8)(ulNDiv1 & 0xFF));
	अगर (ret)
		जाओ err;
	reg29 = (((ulNDiv2 >> 8) & 0x0F) + ucLomod2) & 0x7f;
	ret = regmap_ग_लिखो(dev->regmap, 0x29, reg29);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x2a, (u8)(ulNDiv2 & 0xFF));
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x2F, 0xf5);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x30, 0x05);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x08, 0x1f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x08, 0x3f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x09, 0x20);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x09, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x3e, 0x11);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x08, 0x2f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x08, 0x3f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x09, 0x10);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x09, 0x00);
	अगर (ret)
		जाओ err;
	usleep_range(2000, 50000);

	ret = regmap_पढ़ो(dev->regmap, 0x42, &uपंचांगp);
	अगर (ret)
		जाओ err;
	reg42 = uपंचांगp;

	ret = regmap_ग_लिखो(dev->regmap, 0x3e, 0x10);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x08, 0x2f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x08, 0x3f);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x09, 0x10);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x09, 0x00);
	अगर (ret)
		जाओ err;
	usleep_range(2000, 50000);

	ret = regmap_पढ़ो(dev->regmap, 0x42, &uपंचांगp);
	अगर (ret)
		जाओ err;
	reg42buf = uपंचांगp;
	अगर (reg42buf < reg42) अणु
		ret = regmap_ग_लिखो(dev->regmap, 0x3e, 0x11);
		अगर (ret)
			जाओ err;
	पूर्ण
	usleep_range(5000, 50000);

	ret = regmap_पढ़ो(dev->regmap, 0x2d, &uपंचांगp);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x2d, uपंचांगp);
	अगर (ret)
		जाओ err;
	ret = regmap_पढ़ो(dev->regmap, 0x2e, &uपंचांगp);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x2e, uपंचांगp);
	अगर (ret)
		जाओ err;

	ret = regmap_पढ़ो(dev->regmap, 0x27, &uपंचांगp);
	अगर (ret)
		जाओ err;
	reg27 = uपंचांगp & 0x70;
	ret = regmap_पढ़ो(dev->regmap, 0x83, &uपंचांगp);
	अगर (ret)
		जाओ err;
	अगर (reg27 == (uपंचांगp & 0x70)) अणु
		ucLoDiv	= ucLoDiv1;
		ulNDiv = ulNDiv1;
		ucLomod = ucLomod1 / 16;
	पूर्ण अन्यथा अणु
		ucLoDiv	= ucLoDiv2;
		ulNDiv = ulNDiv2;
		ucLomod = ucLomod2 / 16;
	पूर्ण

	अगर ((ucLoDiv == 3) || (ucLoDiv == 6)) अणु
		refDiv = 18;
		ret = regmap_ग_लिखो(dev->regmap, 0x36, (refDiv - 8));
		अगर (ret)
			जाओ err;
		ulNDiv = ((tuner_freq_MHz * ucLoDiv * 1000) * refDiv
				/ fcry_KHz - 1024) / 2;
	पूर्ण

	reg27 = (0x80 + ((ucLomod << 4) & 0x70)
			+ ((ulNDiv >> 8) & 0x0F)) & 0xFF;
	ret = regmap_ग_लिखो(dev->regmap, 0x27, reg27);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x28, (u8)(ulNDiv & 0xFF));
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x29, 0x80);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x31, 0x03);
	अगर (ret)
		जाओ err;

	अगर (ucLoDiv == 3)
		uपंचांगp = 0xCE;
	अन्यथा
		uपंचांगp = 0x8A;
	ret = regmap_ग_लिखो(dev->regmap, 0x3b, uपंचांगp);
	अगर (ret)
		जाओ err;

	dev->frequency_khz = fcry_KHz * (ulNDiv * 2 + 1024) / refDiv / ucLoDiv;

	dev_dbg(&dev->client->dev,
		"actual tune frequency=%d\n", dev->frequency_khz);
err:
	अगर (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs6000t_set_bb(काष्ठा m88rs6000t_dev *dev,
		u32 symbol_rate_KSs, s32 lpf_offset_KHz)
अणु
	u32 f3dB;
	u8  reg40;

	f3dB = symbol_rate_KSs * 9 / 14 + 2000;
	f3dB += lpf_offset_KHz;
	f3dB = clamp_val(f3dB, 6000U, 43000U);
	reg40 = f3dB / 1000;
	वापस regmap_ग_लिखो(dev->regmap, 0x40, reg40);
पूर्ण

अटल पूर्णांक m88rs6000t_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	s32 lpf_offset_KHz;
	u32 realFreq, freq_MHz;

	dev_dbg(&dev->client->dev,
			"frequency=%d symbol_rate=%d\n",
			c->frequency, c->symbol_rate);

	अगर (c->symbol_rate < 5000000)
		lpf_offset_KHz = 3000;
	अन्यथा
		lpf_offset_KHz = 0;

	realFreq = c->frequency + lpf_offset_KHz;
	/* set tuner pll.*/
	freq_MHz = (realFreq + 500) / 1000;
	ret = m88rs6000t_set_pll_freq(dev, freq_MHz);
	अगर (ret)
		जाओ err;
	ret = m88rs6000t_set_bb(dev, c->symbol_rate / 1000, lpf_offset_KHz);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x01);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x00);
	अगर (ret)
		जाओ err;
	/* set demod mlck */
	ret = m88rs6000t_set_demod_mclk(fe);
err:
	अगर (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs6000t_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;
	पूर्णांक ret;

	dev_dbg(&dev->client->dev, "%s:\n", __func__);

	ret = regmap_update_bits(dev->regmap, 0x11, 0x08, 0x08);
	अगर (ret)
		जाओ err;
	usleep_range(5000, 50000);
	ret = regmap_update_bits(dev->regmap, 0x10, 0x01, 0x01);
	अगर (ret)
		जाओ err;
	usleep_range(10000, 50000);
	ret = regmap_ग_लिखो(dev->regmap, 0x07, 0x7d);
err:
	अगर (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs6000t_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;
	पूर्णांक ret;

	dev_dbg(&dev->client->dev, "%s:\n", __func__);

	ret = regmap_ग_लिखो(dev->regmap, 0x07, 0x6d);
	अगर (ret) अणु
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(5000, 10000);
	वापस 0;
पूर्ण

अटल पूर्णांक m88rs6000t_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;

	dev_dbg(&dev->client->dev, "\n");

	*frequency = dev->frequency_khz;
	वापस 0;
पूर्ण

अटल पूर्णांक m88rs6000t_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;

	dev_dbg(&dev->client->dev, "\n");

	*frequency = 0; /* Zero-IF */
	वापस 0;
पूर्ण


अटल पूर्णांक m88rs6000t_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा m88rs6000t_dev *dev = fe->tuner_priv;
	अचिन्हित पूर्णांक val, i;
	पूर्णांक ret;
	u16 gain;
	u32 PGA2_cri_GS = 46, PGA2_crf_GS = 290, TIA_GS = 290;
	u32 RF_GC = 1200, IF_GC = 1100, BB_GC = 300;
	u32 PGA2_GC = 300, TIA_GC = 300, PGA2_cri = 0, PGA2_crf = 0;
	u32 RFG = 0, IFG = 0, BBG = 0, PGA2G = 0, TIAG = 0;
	u32 RFGS[13] = अणु0, 245, 266, 268, 270, 285,
			298, 295, 283, 285, 285, 300, 300पूर्ण;
	u32 IFGS[12] = अणु0, 300, 230, 270, 270, 285,
			295, 285, 290, 295, 295, 310पूर्ण;
	u32 BBGS[14] = अणु0, 286, 275, 290, 294, 300, 290,
			290, 285, 283, 260, 295, 290, 260पूर्ण;

	ret = regmap_पढ़ो(dev->regmap, 0x5A, &val);
	अगर (ret)
		जाओ err;
	RF_GC = val & 0x0f;

	ret = regmap_पढ़ो(dev->regmap, 0x5F, &val);
	अगर (ret)
		जाओ err;
	IF_GC = val & 0x0f;

	ret = regmap_पढ़ो(dev->regmap, 0x3F, &val);
	अगर (ret)
		जाओ err;
	TIA_GC = (val >> 4) & 0x07;

	ret = regmap_पढ़ो(dev->regmap, 0x77, &val);
	अगर (ret)
		जाओ err;
	BB_GC = (val >> 4) & 0x0f;

	ret = regmap_पढ़ो(dev->regmap, 0x76, &val);
	अगर (ret)
		जाओ err;
	PGA2_GC = val & 0x3f;
	PGA2_cri = PGA2_GC >> 2;
	PGA2_crf = PGA2_GC & 0x03;

	क्रम (i = 0; i <= RF_GC && i < ARRAY_SIZE(RFGS); i++)
		RFG += RFGS[i];

	अगर (RF_GC == 0)
		RFG += 400;
	अगर (RF_GC == 1)
		RFG += 300;
	अगर (RF_GC == 2)
		RFG += 200;
	अगर (RF_GC == 3)
		RFG += 100;

	क्रम (i = 0; i <= IF_GC && i < ARRAY_SIZE(IFGS); i++)
		IFG += IFGS[i];

	TIAG = TIA_GC * TIA_GS;

	क्रम (i = 0; i <= BB_GC && i < ARRAY_SIZE(BBGS); i++)
		BBG += BBGS[i];

	PGA2G = PGA2_cri * PGA2_cri_GS + PGA2_crf * PGA2_crf_GS;

	gain = RFG + IFG - TIAG + BBG + PGA2G;

	/* scale value to 0x0000-0xffff */
	gain = clamp_val(gain, 1000U, 10500U);
	*strength = (10500 - gain) * 0xffff / (10500 - 1000);
err:
	अगर (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops m88rs6000t_tuner_ops = अणु
	.info = अणु
		.name             = "Montage M88RS6000 Internal Tuner",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
	पूर्ण,

	.init = m88rs6000t_init,
	.sleep = m88rs6000t_sleep,
	.set_params = m88rs6000t_set_params,
	.get_frequency = m88rs6000t_get_frequency,
	.get_अगर_frequency = m88rs6000t_get_अगर_frequency,
	.get_rf_strength = m88rs6000t_get_rf_strength,
पूर्ण;

अटल पूर्णांक m88rs6000t_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा m88rs6000t_config *cfg = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = cfg->fe;
	काष्ठा m88rs6000t_dev *dev;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक uपंचांगp;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;
	अटल स्थिर काष्ठा m88rs6000t_reg_val reg_vals[] = अणु
		अणु0x10, 0xfbपूर्ण,
		अणु0x24, 0x38पूर्ण,
		अणु0x11, 0x0aपूर्ण,
		अणु0x12, 0x00पूर्ण,
		अणु0x2b, 0x1cपूर्ण,
		अणु0x44, 0x48पूर्ण,
		अणु0x54, 0x24पूर्ण,
		अणु0x55, 0x06पूर्ण,
		अणु0x59, 0x00पूर्ण,
		अणु0x5b, 0x4cपूर्ण,
		अणु0x60, 0x8bपूर्ण,
		अणु0x61, 0xf4पूर्ण,
		अणु0x65, 0x07पूर्ण,
		अणु0x6d, 0x6fपूर्ण,
		अणु0x6e, 0x31पूर्ण,
		अणु0x3c, 0xf3पूर्ण,
		अणु0x37, 0x0fपूर्ण,
		अणु0x48, 0x28पूर्ण,
		अणु0x49, 0xd8पूर्ण,
		अणु0x70, 0x66पूर्ण,
		अणु0x71, 0xCFपूर्ण,
		अणु0x72, 0x81पूर्ण,
		अणु0x73, 0xA7पूर्ण,
		अणु0x74, 0x4Fपूर्ण,
		अणु0x75, 0xFCपूर्ण,
	पूर्ण;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		जाओ err;
	पूर्ण

	स_नकल(&dev->cfg, cfg, माप(काष्ठा m88rs6000t_config));
	dev->client = client;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err;
	पूर्ण

	ret = regmap_update_bits(dev->regmap, 0x11, 0x08, 0x08);
	अगर (ret)
		जाओ err;
	usleep_range(5000, 50000);
	ret = regmap_update_bits(dev->regmap, 0x10, 0x01, 0x01);
	अगर (ret)
		जाओ err;
	usleep_range(10000, 50000);
	ret = regmap_ग_लिखो(dev->regmap, 0x07, 0x7d);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x04, 0x01);
	अगर (ret)
		जाओ err;

	/* check tuner chip id */
	ret = regmap_पढ़ो(dev->regmap, 0x01, &uपंचांगp);
	अगर (ret)
		जाओ err;
	dev_info(&dev->client->dev, "chip_id=%02x\n", uपंचांगp);
	अगर (uपंचांगp != 0x64) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* tuner init. */
	ret = regmap_ग_लिखो(dev->regmap, 0x05, 0x40);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x11, 0x08);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x15, 0x6c);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x17, 0xc1);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x17, 0x81);
	अगर (ret)
		जाओ err;
	usleep_range(10000, 50000);
	ret = regmap_ग_लिखो(dev->regmap, 0x05, 0x00);
	अगर (ret)
		जाओ err;
	ret = regmap_ग_लिखो(dev->regmap, 0x11, 0x0a);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(reg_vals); i++) अणु
		ret = regmap_ग_लिखो(dev->regmap,
				reg_vals[i].reg, reg_vals[i].val);
		अगर (ret)
			जाओ err;
	पूर्ण

	dev_info(&dev->client->dev, "Montage M88RS6000 internal tuner successfully identified\n");

	fe->tuner_priv = dev;
	स_नकल(&fe->ops.tuner_ops, &m88rs6000t_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
	i2c_set_clientdata(client, dev);
	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक m88rs6000t_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा m88rs6000t_dev *dev = i2c_get_clientdata(client);
	काष्ठा dvb_frontend *fe = dev->cfg.fe;

	dev_dbg(&client->dev, "\n");

	स_रखो(&fe->ops.tuner_ops, 0, माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = शून्य;
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id m88rs6000t_id[] = अणु
	अणु"m88rs6000t", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, m88rs6000t_id);

अटल काष्ठा i2c_driver m88rs6000t_driver = अणु
	.driver = अणु
		.name	= "m88rs6000t",
	पूर्ण,
	.probe		= m88rs6000t_probe,
	.हटाओ		= m88rs6000t_हटाओ,
	.id_table	= m88rs6000t_id,
पूर्ण;

module_i2c_driver(m88rs6000t_driver);

MODULE_AUTHOR("Max nibble <nibble.max@gmail.com>");
MODULE_DESCRIPTION("Montage M88RS6000 internal tuner driver");
MODULE_LICENSE("GPL");
