<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Fitiघातer FC0012 tuner driver
 *
 * Copyright (C) 2012 Hans-Frieder Vogt <hfvogt@gmx.net>
 */

#समावेश "fc0012.h"
#समावेश "fc0012-priv.h"

अटल पूर्णांक fc0012_ग_लिखोreg(काष्ठा fc0012_priv *priv, u8 reg, u8 val)
अणु
	u8 buf[2] = अणुreg, valपूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cfg->i2c_address, .flags = 0, .buf = buf, .len = 2
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		dev_err(&priv->i2c->dev,
			"%s: I2C write reg failed, reg: %02x, val: %02x\n",
			KBUILD_MODNAME, reg, val);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fc0012_पढ़ोreg(काष्ठा fc0012_priv *priv, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->cfg->i2c_address, .flags = 0,
			.buf = &reg, .len = 1 पूर्ण,
		अणु .addr = priv->cfg->i2c_address, .flags = I2C_M_RD,
			.buf = val, .len = 1 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		dev_err(&priv->i2c->dev,
			"%s: I2C read reg failed, reg: %02x\n",
			KBUILD_MODNAME, reg);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fc0012_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक fc0012_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc0012_priv *priv = fe->tuner_priv;
	पूर्णांक i, ret = 0;
	अचिन्हित अक्षर reg[] = अणु
		0x00,	/* dummy reg. 0 */
		0x05,	/* reg. 0x01 */
		0x10,	/* reg. 0x02 */
		0x00,	/* reg. 0x03 */
		0x00,	/* reg. 0x04 */
		0x0f,	/* reg. 0x05: may also be 0x0a */
		0x00,	/* reg. 0x06: भागider 2, VCO slow */
		0x00,	/* reg. 0x07: may also be 0x0f */
		0xff,	/* reg. 0x08: AGC Clock भागide by 256, AGC gain 1/256,
			   Loop Bw 1/8 */
		0x6e,	/* reg. 0x09: Disable LoopThrough, Enable LoopThrough: 0x6f */
		0xb8,	/* reg. 0x0a: Disable LO Test Buffer */
		0x82,	/* reg. 0x0b: Output Clock is same as घड़ी frequency,
			   may also be 0x83 */
		0xfc,	/* reg. 0x0c: depending on AGC Up-Down mode, may need 0xf8 */
		0x02,	/* reg. 0x0d: AGC Not Forcing & LNA Forcing, 0x02 क्रम DVB-T */
		0x00,	/* reg. 0x0e */
		0x00,	/* reg. 0x0f */
		0x00,	/* reg. 0x10: may also be 0x0d */
		0x00,	/* reg. 0x11 */
		0x1f,	/* reg. 0x12: Set to maximum gain */
		0x08,	/* reg. 0x13: Set to Middle Gain: 0x08,
			   Low Gain: 0x00, High Gain: 0x10, enable IX2: 0x80 */
		0x00,	/* reg. 0x14 */
		0x04,	/* reg. 0x15: Enable LNA COMPS */
	पूर्ण;

	चयन (priv->cfg->xtal_freq) अणु
	हाल FC_XTAL_27_MHZ:
	हाल FC_XTAL_28_8_MHZ:
		reg[0x07] |= 0x20;
		अवरोध;
	हाल FC_XTAL_36_MHZ:
	शेष:
		अवरोध;
	पूर्ण

	अगर (priv->cfg->dual_master)
		reg[0x0c] |= 0x02;

	अगर (priv->cfg->loop_through)
		reg[0x09] |= 0x01;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	क्रम (i = 1; i < माप(reg); i++) अणु
		ret = fc0012_ग_लिखोreg(priv, i, reg[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (ret)
		dev_err(&priv->i2c->dev, "%s: fc0012_writereg failed: %d\n",
				KBUILD_MODNAME, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fc0012_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc0012_priv *priv = fe->tuner_priv;
	पूर्णांक i, ret = 0;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 freq = p->frequency / 1000;
	u32 delsys = p->delivery_प्रणाली;
	अचिन्हित अक्षर reg[7], am, pm, multi, पंचांगp;
	अचिन्हित दीर्घ f_vco;
	अचिन्हित लघु xtal_freq_khz_2, xin, xभाग;
	bool vco_select = false;

	अगर (fe->callback) अणु
		ret = fe->callback(priv->i2c, DVB_FRONTEND_COMPONENT_TUNER,
			FC_FE_CALLBACK_VHF_ENABLE, (freq > 300000 ? 0 : 1));
		अगर (ret)
			जाओ निकास;
	पूर्ण

	चयन (priv->cfg->xtal_freq) अणु
	हाल FC_XTAL_27_MHZ:
		xtal_freq_khz_2 = 27000 / 2;
		अवरोध;
	हाल FC_XTAL_36_MHZ:
		xtal_freq_khz_2 = 36000 / 2;
		अवरोध;
	हाल FC_XTAL_28_8_MHZ:
	शेष:
		xtal_freq_khz_2 = 28800 / 2;
		अवरोध;
	पूर्ण

	/* select frequency भागider and the frequency of VCO */
	अगर (freq < 37084) अणु		/* freq * 96 < 3560000 */
		multi = 96;
		reg[5] = 0x82;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 55625) अणु	/* freq * 64 < 3560000 */
		multi = 64;
		reg[5] = 0x82;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 74167) अणु	/* freq * 48 < 3560000 */
		multi = 48;
		reg[5] = 0x42;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 111250) अणु	/* freq * 32 < 3560000 */
		multi = 32;
		reg[5] = 0x42;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 148334) अणु	/* freq * 24 < 3560000 */
		multi = 24;
		reg[5] = 0x22;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 222500) अणु	/* freq * 16 < 3560000 */
		multi = 16;
		reg[5] = 0x22;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 296667) अणु	/* freq * 12 < 3560000 */
		multi = 12;
		reg[5] = 0x12;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 445000) अणु	/* freq * 8 < 3560000 */
		multi = 8;
		reg[5] = 0x12;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 593334) अणु	/* freq * 6 < 3560000 */
		multi = 6;
		reg[5] = 0x0a;
		reg[6] = 0x00;
	पूर्ण अन्यथा अणु
		multi = 4;
		reg[5] = 0x0a;
		reg[6] = 0x02;
	पूर्ण

	f_vco = freq * multi;

	अगर (f_vco >= 3060000) अणु
		reg[6] |= 0x08;
		vco_select = true;
	पूर्ण

	अगर (freq >= 45000) अणु
		/* From भागided value (XDIV) determined the FA and FP value */
		xभाग = (अचिन्हित लघु)(f_vco / xtal_freq_khz_2);
		अगर ((f_vco - xभाग * xtal_freq_khz_2) >= (xtal_freq_khz_2 / 2))
			xभाग++;

		pm = (अचिन्हित अक्षर)(xभाग / 8);
		am = (अचिन्हित अक्षर)(xभाग - (8 * pm));

		अगर (am < 2) अणु
			reg[1] = am + 8;
			reg[2] = pm - 1;
		पूर्ण अन्यथा अणु
			reg[1] = am;
			reg[2] = pm;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* fix क्रम frequency less than 45 MHz */
		reg[1] = 0x06;
		reg[2] = 0x11;
	पूर्ण

	/* fix घड़ी out */
	reg[6] |= 0x20;

	/* From VCO frequency determines the XIN ( fractional part of Delta
	   Sigma PLL) and भागided value (XDIV) */
	xin = (अचिन्हित लघु)(f_vco - (f_vco / xtal_freq_khz_2) * xtal_freq_khz_2);
	xin = (xin << 15) / xtal_freq_khz_2;
	अगर (xin >= 16384)
		xin += 32768;

	reg[3] = xin >> 8;	/* xin with 9 bit resolution */
	reg[4] = xin & 0xff;

	अगर (delsys == SYS_DVBT) अणु
		reg[6] &= 0x3f;	/* bits 6 and 7 describe the bandwidth */
		चयन (p->bandwidth_hz) अणु
		हाल 6000000:
			reg[6] |= 0x80;
			अवरोध;
		हाल 7000000:
			reg[6] |= 0x40;
			अवरोध;
		हाल 8000000:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&priv->i2c->dev, "%s: modulation type not supported!\n",
				KBUILD_MODNAME);
		वापस -EINVAL;
	पूर्ण

	/* modअगरied क्रम Realtek demod */
	reg[5] |= 0x07;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	क्रम (i = 1; i <= 6; i++) अणु
		ret = fc0012_ग_लिखोreg(priv, i, reg[i]);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	/* VCO Calibration */
	ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x80);
	अगर (!ret)
		ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x00);

	/* VCO Re-Calibration अगर needed */
	अगर (!ret)
		ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x00);

	अगर (!ret) अणु
		msleep(10);
		ret = fc0012_पढ़ोreg(priv, 0x0e, &पंचांगp);
	पूर्ण
	अगर (ret)
		जाओ निकास;

	/* vco selection */
	पंचांगp &= 0x3f;

	अगर (vco_select) अणु
		अगर (पंचांगp > 0x3c) अणु
			reg[6] &= ~0x08;
			ret = fc0012_ग_लिखोreg(priv, 0x06, reg[6]);
			अगर (!ret)
				ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x80);
			अगर (!ret)
				ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x00);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (पंचांगp < 0x02) अणु
			reg[6] |= 0x08;
			ret = fc0012_ग_लिखोreg(priv, 0x06, reg[6]);
			अगर (!ret)
				ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x80);
			अगर (!ret)
				ret = fc0012_ग_लिखोreg(priv, 0x0e, 0x00);
		पूर्ण
	पूर्ण

	priv->frequency = p->frequency;
	priv->bandwidth = p->bandwidth_hz;

निकास:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */
	अगर (ret)
		dev_warn(&priv->i2c->dev, "%s: %s failed: %d\n",
				KBUILD_MODNAME, __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fc0012_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा fc0012_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक fc0012_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = 0; /* Zero-IF */
	वापस 0;
पूर्ण

अटल पूर्णांक fc0012_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा fc0012_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

#घोषणा INPUT_ADC_LEVEL	-8

अटल पूर्णांक fc0012_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा fc0012_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक पूर्णांक_temp, lna_gain, पूर्णांक_lna, tot_agc_gain, घातer;
	अटल स्थिर पूर्णांक fc0012_lna_gain_table[] = अणु
		/* low gain */
		-63, -58, -99, -73,
		-63, -65, -54, -60,
		/* middle gain */
		 71,  70,  68,  67,
		 65,  63,  61,  58,
		/* high gain */
		197, 191, 188, 186,
		184, 182, 181, 179,
	पूर्ण;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	ret = fc0012_ग_लिखोreg(priv, 0x12, 0x00);
	अगर (ret)
		जाओ err;

	ret = fc0012_पढ़ोreg(priv, 0x12, &पंचांगp);
	अगर (ret)
		जाओ err;
	पूर्णांक_temp = पंचांगp;

	ret = fc0012_पढ़ोreg(priv, 0x13, &पंचांगp);
	अगर (ret)
		जाओ err;
	lna_gain = पंचांगp & 0x1f;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (lna_gain < ARRAY_SIZE(fc0012_lna_gain_table)) अणु
		पूर्णांक_lna = fc0012_lna_gain_table[lna_gain];
		tot_agc_gain = (असल((पूर्णांक_temp >> 5) - 7) - 2 +
				(पूर्णांक_temp & 0x1f)) * 2;
		घातer = INPUT_ADC_LEVEL - tot_agc_gain - पूर्णांक_lna / 10;

		अगर (घातer >= 45)
			*strength = 255;	/* 100% */
		अन्यथा अगर (घातer < -95)
			*strength = 0;
		अन्यथा
			*strength = (घातer + 95) * 255 / 140;

		*strength |= *strength << 8;
	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण

	जाओ निकास;

err:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */
निकास:
	अगर (ret)
		dev_warn(&priv->i2c->dev, "%s: %s failed: %d\n",
				KBUILD_MODNAME, __func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops fc0012_tuner_ops = अणु
	.info = अणु
		.name              = "Fitipower FC0012",

		.frequency_min_hz  =  37 * MHz,	/* estimate */
		.frequency_max_hz  = 862 * MHz,	/* estimate */
	पूर्ण,

	.release	= fc0012_release,

	.init		= fc0012_init,

	.set_params	= fc0012_set_params,

	.get_frequency	= fc0012_get_frequency,
	.get_अगर_frequency = fc0012_get_अगर_frequency,
	.get_bandwidth	= fc0012_get_bandwidth,

	.get_rf_strength = fc0012_get_rf_strength,
पूर्ण;

काष्ठा dvb_frontend *fc0012_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c, स्थिर काष्ठा fc0012_config *cfg)
अणु
	काष्ठा fc0012_priv *priv;
	पूर्णांक ret;
	u8 chip_id;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	priv = kzalloc(माप(काष्ठा fc0012_priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		dev_err(&i2c->dev, "%s: kzalloc() failed\n", KBUILD_MODNAME);
		जाओ err;
	पूर्ण

	priv->cfg = cfg;
	priv->i2c = i2c;

	/* check अगर the tuner is there */
	ret = fc0012_पढ़ोreg(priv, 0x00, &chip_id);
	अगर (ret < 0)
		जाओ err;

	dev_dbg(&i2c->dev, "%s: chip_id=%02x\n", __func__, chip_id);

	चयन (chip_id) अणु
	हाल 0xa1:
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	dev_info(&i2c->dev, "%s: Fitipower FC0012 successfully identified\n",
			KBUILD_MODNAME);

	अगर (priv->cfg->loop_through) अणु
		ret = fc0012_ग_लिखोreg(priv, 0x09, 0x6f);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	/*
	 * TODO: Clock out en or भाग?
	 * For dual tuner configuration clearing bit [0] is required.
	 */
	अगर (priv->cfg->घड़ी_out) अणु
		ret =  fc0012_ग_लिखोreg(priv, 0x0b, 0x82);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	fe->tuner_priv = priv;
	स_नकल(&fe->ops.tuner_ops, &fc0012_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));

err:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret) अणु
		dev_dbg(&i2c->dev, "%s: failed: %d\n", __func__, ret);
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	वापस fe;
पूर्ण
EXPORT_SYMBOL(fc0012_attach);

MODULE_DESCRIPTION("Fitipower FC0012 silicon tuner driver");
MODULE_AUTHOR("Hans-Frieder Vogt <hfvogt@gmx.net>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.6");
