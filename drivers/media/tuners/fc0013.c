<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Fitiघातer FC0013 tuner driver
 *
 * Copyright (C) 2012 Hans-Frieder Vogt <hfvogt@gmx.net>
 * partially based on driver code from Fitiघातer
 * Copyright (C) 2010 Fitiघातer Integrated Technology Inc
 */

#समावेश "fc0013.h"
#समावेश "fc0013-priv.h"

अटल पूर्णांक fc0013_ग_लिखोreg(काष्ठा fc0013_priv *priv, u8 reg, u8 val)
अणु
	u8 buf[2] = अणुreg, valपूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->addr, .flags = 0, .buf = buf, .len = 2
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		err("I2C write reg failed, reg: %02x, val: %02x", reg, val);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fc0013_पढ़ोreg(काष्ठा fc0013_priv *priv, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->addr, .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = priv->addr, .flags = I2C_M_RD, .buf = val, .len = 1 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		err("I2C read reg failed, reg: %02x", reg);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fc0013_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक fc0013_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
	पूर्णांक i, ret = 0;
	अचिन्हित अक्षर reg[] = अणु
		0x00,	/* reg. 0x00: dummy */
		0x09,	/* reg. 0x01 */
		0x16,	/* reg. 0x02 */
		0x00,	/* reg. 0x03 */
		0x00,	/* reg. 0x04 */
		0x17,	/* reg. 0x05 */
		0x02,	/* reg. 0x06 */
		0x0a,	/* reg. 0x07: CHECK */
		0xff,	/* reg. 0x08: AGC Clock भागide by 256, AGC gain 1/256,
			   Loop Bw 1/8 */
		0x6f,	/* reg. 0x09: enable LoopThrough */
		0xb8,	/* reg. 0x0a: Disable LO Test Buffer */
		0x82,	/* reg. 0x0b: CHECK */
		0xfc,	/* reg. 0x0c: depending on AGC Up-Down mode, may need 0xf8 */
		0x01,	/* reg. 0x0d: AGC Not Forcing & LNA Forcing, may need 0x02 */
		0x00,	/* reg. 0x0e */
		0x00,	/* reg. 0x0f */
		0x00,	/* reg. 0x10 */
		0x00,	/* reg. 0x11 */
		0x00,	/* reg. 0x12 */
		0x00,	/* reg. 0x13 */
		0x50,	/* reg. 0x14: DVB-t High Gain, UHF.
			   Middle Gain: 0x48, Low Gain: 0x40 */
		0x01,	/* reg. 0x15 */
	पूर्ण;

	चयन (priv->xtal_freq) अणु
	हाल FC_XTAL_27_MHZ:
	हाल FC_XTAL_28_8_MHZ:
		reg[0x07] |= 0x20;
		अवरोध;
	हाल FC_XTAL_36_MHZ:
	शेष:
		अवरोध;
	पूर्ण

	अगर (priv->dual_master)
		reg[0x0c] |= 0x02;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	क्रम (i = 1; i < माप(reg); i++) अणु
		ret = fc0013_ग_लिखोreg(priv, i, reg[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (ret)
		err("fc0013_writereg failed: %d", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fc0013_sleep(काष्ठा dvb_frontend *fe)
अणु
	/* nothing to करो here */
	वापस 0;
पूर्ण

पूर्णांक fc0013_rc_cal_add(काष्ठा dvb_frontend *fe, पूर्णांक rc_val)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u8 rc_cal;
	पूर्णांक val;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	/* push rc_cal value, get rc_cal value */
	ret = fc0013_ग_लिखोreg(priv, 0x10, 0x00);
	अगर (ret)
		जाओ error_out;

	/* get rc_cal value */
	ret = fc0013_पढ़ोreg(priv, 0x10, &rc_cal);
	अगर (ret)
		जाओ error_out;

	rc_cal &= 0x0f;

	val = (पूर्णांक)rc_cal + rc_val;

	/* क्रमcing rc_cal */
	ret = fc0013_ग_लिखोreg(priv, 0x0d, 0x11);
	अगर (ret)
		जाओ error_out;

	/* modअगरy rc_cal value */
	अगर (val > 15)
		ret = fc0013_ग_लिखोreg(priv, 0x10, 0x0f);
	अन्यथा अगर (val < 0)
		ret = fc0013_ग_लिखोreg(priv, 0x10, 0x00);
	अन्यथा
		ret = fc0013_ग_लिखोreg(priv, 0x10, (u8)val);

error_out:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fc0013_rc_cal_add);

पूर्णांक fc0013_rc_cal_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	ret = fc0013_ग_लिखोreg(priv, 0x0d, 0x01);
	अगर (!ret)
		ret = fc0013_ग_लिखोreg(priv, 0x10, 0x00);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fc0013_rc_cal_reset);

अटल पूर्णांक fc0013_set_vhf_track(काष्ठा fc0013_priv *priv, u32 freq)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = fc0013_पढ़ोreg(priv, 0x1d, &पंचांगp);
	अगर (ret)
		जाओ error_out;
	पंचांगp &= 0xe3;
	अगर (freq <= 177500) अणु		/* VHF Track: 7 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x1c);
	पूर्ण अन्यथा अगर (freq <= 184500) अणु	/* VHF Track: 6 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x18);
	पूर्ण अन्यथा अगर (freq <= 191500) अणु	/* VHF Track: 5 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x14);
	पूर्ण अन्यथा अगर (freq <= 198500) अणु	/* VHF Track: 4 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x10);
	पूर्ण अन्यथा अगर (freq <= 205500) अणु	/* VHF Track: 3 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x0c);
	पूर्ण अन्यथा अगर (freq <= 219500) अणु	/* VHF Track: 2 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x08);
	पूर्ण अन्यथा अगर (freq < 300000) अणु	/* VHF Track: 1 */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x04);
	पूर्ण अन्यथा अणु			/* UHF and GPS */
		ret = fc0013_ग_लिखोreg(priv, 0x1d, पंचांगp | 0x1c);
	पूर्ण
error_out:
	वापस ret;
पूर्ण

अटल पूर्णांक fc0013_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
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

	चयन (priv->xtal_freq) अणु
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

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	/* set VHF track */
	ret = fc0013_set_vhf_track(priv, freq);
	अगर (ret)
		जाओ निकास;

	अगर (freq < 300000) अणु
		/* enable VHF filter */
		ret = fc0013_पढ़ोreg(priv, 0x07, &पंचांगp);
		अगर (ret)
			जाओ निकास;
		ret = fc0013_ग_लिखोreg(priv, 0x07, पंचांगp | 0x10);
		अगर (ret)
			जाओ निकास;

		/* disable UHF & disable GPS */
		ret = fc0013_पढ़ोreg(priv, 0x14, &पंचांगp);
		अगर (ret)
			जाओ निकास;
		ret = fc0013_ग_लिखोreg(priv, 0x14, पंचांगp & 0x1f);
		अगर (ret)
			जाओ निकास;
	पूर्ण अन्यथा अगर (freq <= 862000) अणु
		/* disable VHF filter */
		ret = fc0013_पढ़ोreg(priv, 0x07, &पंचांगp);
		अगर (ret)
			जाओ निकास;
		ret = fc0013_ग_लिखोreg(priv, 0x07, पंचांगp & 0xef);
		अगर (ret)
			जाओ निकास;

		/* enable UHF & disable GPS */
		ret = fc0013_पढ़ोreg(priv, 0x14, &पंचांगp);
		अगर (ret)
			जाओ निकास;
		ret = fc0013_ग_लिखोreg(priv, 0x14, (पंचांगp & 0x1f) | 0x40);
		अगर (ret)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		/* disable VHF filter */
		ret = fc0013_पढ़ोreg(priv, 0x07, &पंचांगp);
		अगर (ret)
			जाओ निकास;
		ret = fc0013_ग_लिखोreg(priv, 0x07, पंचांगp & 0xef);
		अगर (ret)
			जाओ निकास;

		/* disable UHF & enable GPS */
		ret = fc0013_पढ़ोreg(priv, 0x14, &पंचांगp);
		अगर (ret)
			जाओ निकास;
		ret = fc0013_ग_लिखोreg(priv, 0x14, (पंचांगp & 0x1f) | 0x20);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	/* select frequency भागider and the frequency of VCO */
	अगर (freq < 37084) अणु		/* freq * 96 < 3560000 */
		multi = 96;
		reg[5] = 0x82;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 55625) अणु	/* freq * 64 < 3560000 */
		multi = 64;
		reg[5] = 0x02;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 74167) अणु	/* freq * 48 < 3560000 */
		multi = 48;
		reg[5] = 0x42;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 111250) अणु	/* freq * 32 < 3560000 */
		multi = 32;
		reg[5] = 0x82;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 148334) अणु	/* freq * 24 < 3560000 */
		multi = 24;
		reg[5] = 0x22;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 222500) अणु	/* freq * 16 < 3560000 */
		multi = 16;
		reg[5] = 0x42;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 296667) अणु	/* freq * 12 < 3560000 */
		multi = 12;
		reg[5] = 0x12;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 445000) अणु	/* freq * 8 < 3560000 */
		multi = 8;
		reg[5] = 0x22;
		reg[6] = 0x02;
	पूर्ण अन्यथा अगर (freq < 593334) अणु	/* freq * 6 < 3560000 */
		multi = 6;
		reg[5] = 0x0a;
		reg[6] = 0x00;
	पूर्ण अन्यथा अगर (freq < 950000) अणु	/* freq * 4 < 3800000 */
		multi = 4;
		reg[5] = 0x12;
		reg[6] = 0x02;
	पूर्ण अन्यथा अणु
		multi = 2;
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

	reg[3] = xin >> 8;
	reg[4] = xin & 0xff;

	अगर (delsys == SYS_DVBT) अणु
		reg[6] &= 0x3f; /* bits 6 and 7 describe the bandwidth */
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
		err("%s: modulation type not supported!", __func__);
		वापस -EINVAL;
	पूर्ण

	/* modअगरied क्रम Realtek demod */
	reg[5] |= 0x07;

	क्रम (i = 1; i <= 6; i++) अणु
		ret = fc0013_ग_लिखोreg(priv, i, reg[i]);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	ret = fc0013_पढ़ोreg(priv, 0x11, &पंचांगp);
	अगर (ret)
		जाओ निकास;
	अगर (multi == 64)
		ret = fc0013_ग_लिखोreg(priv, 0x11, पंचांगp | 0x04);
	अन्यथा
		ret = fc0013_ग_लिखोreg(priv, 0x11, पंचांगp & 0xfb);
	अगर (ret)
		जाओ निकास;

	/* VCO Calibration */
	ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x80);
	अगर (!ret)
		ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x00);

	/* VCO Re-Calibration अगर needed */
	अगर (!ret)
		ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x00);

	अगर (!ret) अणु
		msleep(10);
		ret = fc0013_पढ़ोreg(priv, 0x0e, &पंचांगp);
	पूर्ण
	अगर (ret)
		जाओ निकास;

	/* vco selection */
	पंचांगp &= 0x3f;

	अगर (vco_select) अणु
		अगर (पंचांगp > 0x3c) अणु
			reg[6] &= ~0x08;
			ret = fc0013_ग_लिखोreg(priv, 0x06, reg[6]);
			अगर (!ret)
				ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x80);
			अगर (!ret)
				ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x00);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (पंचांगp < 0x02) अणु
			reg[6] |= 0x08;
			ret = fc0013_ग_लिखोreg(priv, 0x06, reg[6]);
			अगर (!ret)
				ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x80);
			अगर (!ret)
				ret = fc0013_ग_लिखोreg(priv, 0x0e, 0x00);
		पूर्ण
	पूर्ण

	priv->frequency = p->frequency;
	priv->bandwidth = p->bandwidth_hz;

निकास:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */
	अगर (ret)
		warn("%s: failed: %d", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fc0013_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक fc0013_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	/* always ? */
	*frequency = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक fc0013_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
	*bandwidth = priv->bandwidth;
	वापस 0;
पूर्ण

#घोषणा INPUT_ADC_LEVEL	-8

अटल पूर्णांक fc0013_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा fc0013_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक पूर्णांक_temp, lna_gain, पूर्णांक_lna, tot_agc_gain, घातer;
	अटल स्थिर पूर्णांक fc0013_lna_gain_table[] = अणु
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

	ret = fc0013_ग_लिखोreg(priv, 0x13, 0x00);
	अगर (ret)
		जाओ err;

	ret = fc0013_पढ़ोreg(priv, 0x13, &पंचांगp);
	अगर (ret)
		जाओ err;
	पूर्णांक_temp = पंचांगp;

	ret = fc0013_पढ़ोreg(priv, 0x14, &पंचांगp);
	अगर (ret)
		जाओ err;
	lna_gain = पंचांगp & 0x1f;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (lna_gain < ARRAY_SIZE(fc0013_lna_gain_table)) अणु
		पूर्णांक_lna = fc0013_lna_gain_table[lna_gain];
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
		warn("%s: failed: %d", __func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops fc0013_tuner_ops = अणु
	.info = अणु
		.name		  = "Fitipower FC0013",

		.frequency_min_hz =   37 * MHz,	/* estimate */
		.frequency_max_hz = 1680 * MHz,	/* CHECK */
	पूर्ण,

	.release	= fc0013_release,

	.init		= fc0013_init,
	.sleep		= fc0013_sleep,

	.set_params	= fc0013_set_params,

	.get_frequency	= fc0013_get_frequency,
	.get_अगर_frequency = fc0013_get_अगर_frequency,
	.get_bandwidth	= fc0013_get_bandwidth,

	.get_rf_strength = fc0013_get_rf_strength,
पूर्ण;

काष्ठा dvb_frontend *fc0013_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c, u8 i2c_address, पूर्णांक dual_master,
	क्रमागत fc001x_xtal_freq xtal_freq)
अणु
	काष्ठा fc0013_priv *priv = शून्य;

	priv = kzalloc(माप(काष्ठा fc0013_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->i2c = i2c;
	priv->dual_master = dual_master;
	priv->addr = i2c_address;
	priv->xtal_freq = xtal_freq;

	info("Fitipower FC0013 successfully attached.");

	fe->tuner_priv = priv;

	स_नकल(&fe->ops.tuner_ops, &fc0013_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));

	वापस fe;
पूर्ण
EXPORT_SYMBOL(fc0013_attach);

MODULE_DESCRIPTION("Fitipower FC0013 silicon tuner driver");
MODULE_AUTHOR("Hans-Frieder Vogt <hfvogt@gmx.net>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
