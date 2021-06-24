<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP TDA18218HN silicon tuner driver
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश "tda18218_priv.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

/* ग_लिखो multiple रेजिस्टरs */
अटल पूर्णांक tda18218_wr_regs(काष्ठा tda18218_priv *priv, u8 reg, u8 *val, u8 len)
अणु
	पूर्णांक ret = 0, len2, reमुख्यing;
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = priv->cfg->i2c_address,
			.flags = 0,
			.buf = buf,
		पूर्ण
	पूर्ण;

	अगर (1 + len > माप(buf)) अणु
		dev_warn(&priv->i2c->dev,
			 "%s: i2c wr reg=%04x: len=%d is too big!\n",
			 KBUILD_MODNAME, reg, len);
		वापस -EINVAL;
	पूर्ण

	क्रम (reमुख्यing = len; reमुख्यing > 0;
			reमुख्यing -= (priv->cfg->i2c_wr_max - 1)) अणु
		len2 = reमुख्यing;
		अगर (len2 > (priv->cfg->i2c_wr_max - 1))
			len2 = (priv->cfg->i2c_wr_max - 1);

		msg[0].len = 1 + len2;
		buf[0] = reg + len - reमुख्यing;
		स_नकल(&buf[1], &val[len - reमुख्यing], len2);

		ret = i2c_transfer(priv->i2c, msg, 1);
		अगर (ret != 1)
			अवरोध;
	पूर्ण

	अगर (ret == 1) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		dev_warn(&priv->i2c->dev, "%s: i2c wr failed=%d reg=%02x " \
				"len=%d\n", KBUILD_MODNAME, ret, reg, len);
		ret = -EREMOTEIO;
	पूर्ण

	वापस ret;
पूर्ण

/* पढ़ो multiple रेजिस्टरs */
अटल पूर्णांक tda18218_rd_regs(काष्ठा tda18218_priv *priv, u8 reg, u8 *val, u8 len)
अणु
	पूर्णांक ret;
	u8 buf[MAX_XFER_SIZE]; /* we must start पढ़ो always from reg 0x00 */
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = priv->cfg->i2c_address,
			.flags = 0,
			.len = 1,
			.buf = "\x00",
		पूर्ण, अणु
			.addr = priv->cfg->i2c_address,
			.flags = I2C_M_RD,
			.len = reg + len,
			.buf = buf,
		पूर्ण
	पूर्ण;

	अगर (reg + len > माप(buf)) अणु
		dev_warn(&priv->i2c->dev,
			 "%s: i2c wr reg=%04x: len=%d is too big!\n",
			 KBUILD_MODNAME, reg, len);
		वापस -EINVAL;
	पूर्ण

	ret = i2c_transfer(priv->i2c, msg, 2);
	अगर (ret == 2) अणु
		स_नकल(val, &buf[reg], len);
		ret = 0;
	पूर्ण अन्यथा अणु
		dev_warn(&priv->i2c->dev, "%s: i2c rd failed=%d reg=%02x " \
				"len=%d\n", KBUILD_MODNAME, ret, reg, len);
		ret = -EREMOTEIO;
	पूर्ण

	वापस ret;
पूर्ण

/* ग_लिखो single रेजिस्टर */
अटल पूर्णांक tda18218_wr_reg(काष्ठा tda18218_priv *priv, u8 reg, u8 val)
अणु
	वापस tda18218_wr_regs(priv, reg, &val, 1);
पूर्ण

/* पढ़ो single रेजिस्टर */

अटल पूर्णांक tda18218_rd_reg(काष्ठा tda18218_priv *priv, u8 reg, u8 *val)
अणु
	वापस tda18218_rd_regs(priv, reg, val, 1);
पूर्ण

अटल पूर्णांक tda18218_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18218_priv *priv = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 bw = c->bandwidth_hz;
	पूर्णांक ret;
	u8 buf[3], i, BP_Filter, LP_Fc;
	u32 LO_Frac;
	/* TODO: find out correct AGC algorithm */
	u8 agc[][2] = अणु
		अणु R20_AGC11, 0x60 पूर्ण,
		अणु R23_AGC21, 0x02 पूर्ण,
		अणु R20_AGC11, 0xa0 पूर्ण,
		अणु R23_AGC21, 0x09 पूर्ण,
		अणु R20_AGC11, 0xe0 पूर्ण,
		अणु R23_AGC21, 0x0c पूर्ण,
		अणु R20_AGC11, 0x40 पूर्ण,
		अणु R23_AGC21, 0x01 पूर्ण,
		अणु R20_AGC11, 0x80 पूर्ण,
		अणु R23_AGC21, 0x08 पूर्ण,
		अणु R20_AGC11, 0xc0 पूर्ण,
		अणु R23_AGC21, 0x0b पूर्ण,
		अणु R24_AGC22, 0x1c पूर्ण,
		अणु R24_AGC22, 0x0c पूर्ण,
	पूर्ण;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	/* low-pass filter cut-off frequency */
	अगर (bw <= 6000000) अणु
		LP_Fc = 0;
		priv->अगर_frequency = 3000000;
	पूर्ण अन्यथा अगर (bw <= 7000000) अणु
		LP_Fc = 1;
		priv->अगर_frequency = 3500000;
	पूर्ण अन्यथा अणु
		LP_Fc = 2;
		priv->अगर_frequency = 4000000;
	पूर्ण

	LO_Frac = c->frequency + priv->अगर_frequency;

	/* band-pass filter */
	अगर (LO_Frac < 188000000)
		BP_Filter = 3;
	अन्यथा अगर (LO_Frac < 253000000)
		BP_Filter = 4;
	अन्यथा अगर (LO_Frac < 343000000)
		BP_Filter = 5;
	अन्यथा
		BP_Filter = 6;

	buf[0] = (priv->regs[R1A_IF1] & ~7) | BP_Filter; /* BP_Filter */
	buf[1] = (priv->regs[R1B_IF2] & ~3) | LP_Fc; /* LP_Fc */
	buf[2] = priv->regs[R1C_AGC2B];
	ret = tda18218_wr_regs(priv, R1A_IF1, buf, 3);
	अगर (ret)
		जाओ error;

	buf[0] = (LO_Frac / 1000) >> 12; /* LO_Frac_0 */
	buf[1] = (LO_Frac / 1000) >> 4; /* LO_Frac_1 */
	buf[2] = (LO_Frac / 1000) << 4 |
		(priv->regs[R0C_MD5] & 0x0f); /* LO_Frac_2 */
	ret = tda18218_wr_regs(priv, R0A_MD3, buf, 3);
	अगर (ret)
		जाओ error;

	buf[0] = priv->regs[R0F_MD8] | (1 << 6); /* Freq_prog_Start */
	ret = tda18218_wr_regs(priv, R0F_MD8, buf, 1);
	अगर (ret)
		जाओ error;

	buf[0] = priv->regs[R0F_MD8] & ~(1 << 6); /* Freq_prog_Start */
	ret = tda18218_wr_regs(priv, R0F_MD8, buf, 1);
	अगर (ret)
		जाओ error;

	/* trigger AGC */
	क्रम (i = 0; i < ARRAY_SIZE(agc); i++) अणु
		ret = tda18218_wr_reg(priv, agc[i][0], agc[i][1]);
		अगर (ret)
			जाओ error;
	पूर्ण

error:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (ret)
		dev_dbg(&priv->i2c->dev, "%s: failed=%d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tda18218_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda18218_priv *priv = fe->tuner_priv;
	*frequency = priv->अगर_frequency;
	dev_dbg(&priv->i2c->dev, "%s: if_frequency=%d\n", __func__, *frequency);
	वापस 0;
पूर्ण

अटल पूर्णांक tda18218_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18218_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	/* standby */
	ret = tda18218_wr_reg(priv, R17_PD1, priv->regs[R17_PD1] | (1 << 0));

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (ret)
		dev_dbg(&priv->i2c->dev, "%s: failed=%d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tda18218_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda18218_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	/* TODO: calibrations */

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	ret = tda18218_wr_regs(priv, R00_ID, priv->regs, TDA18218_NUM_REGS);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	अगर (ret)
		dev_dbg(&priv->i2c->dev, "%s: failed=%d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल व्योम tda18218_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tda18218_tuner_ops = अणु
	.info = अणु
		.name              = "NXP TDA18218",

		.frequency_min_hz  = 174 * MHz,
		.frequency_max_hz  = 864 * MHz,
		.frequency_step_hz =   1 * kHz,
	पूर्ण,

	.release       = tda18218_release,
	.init          = tda18218_init,
	.sleep         = tda18218_sleep,

	.set_params    = tda18218_set_params,

	.get_अगर_frequency = tda18218_get_अगर_frequency,
पूर्ण;

काष्ठा dvb_frontend *tda18218_attach(काष्ठा dvb_frontend *fe,
	काष्ठा i2c_adapter *i2c, काष्ठा tda18218_config *cfg)
अणु
	काष्ठा tda18218_priv *priv = शून्य;
	u8 val;
	पूर्णांक ret;
	/* chip शेष रेजिस्टरs values */
	अटल u8 def_regs[] = अणु
		0xc0, 0x88, 0x00, 0x8e, 0x03, 0x00, 0x00, 0xd0, 0x00, 0x40,
		0x00, 0x00, 0x07, 0xff, 0x84, 0x09, 0x00, 0x13, 0x00, 0x00,
		0x01, 0x84, 0x09, 0xf0, 0x19, 0x0a, 0x8e, 0x69, 0x98, 0x01,
		0x00, 0x58, 0x10, 0x40, 0x8c, 0x00, 0x0c, 0x48, 0x85, 0xc9,
		0xa7, 0x00, 0x00, 0x00, 0x30, 0x81, 0x80, 0x00, 0x39, 0x00,
		0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0xf6
	पूर्ण;

	priv = kzalloc(माप(काष्ठा tda18218_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->cfg = cfg;
	priv->i2c = i2c;
	fe->tuner_priv = priv;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो I2C-gate */

	/* check अगर the tuner is there */
	ret = tda18218_rd_reg(priv, R00_ID, &val);
	अगर (!ret)
		dev_dbg(&priv->i2c->dev, "%s: chip id=%02x\n", __func__, val);
	अगर (ret || val != def_regs[R00_ID]) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	dev_info(&priv->i2c->dev,
			"%s: NXP TDA18218HN successfully identified\n",
			KBUILD_MODNAME);

	स_नकल(&fe->ops.tuner_ops, &tda18218_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));
	स_नकल(priv->regs, def_regs, माप(def_regs));

	/* loop-through enabled chip शेष रेजिस्टर values */
	अगर (priv->cfg->loop_through) अणु
		priv->regs[R17_PD1] = 0xb0;
		priv->regs[R18_PD2] = 0x59;
	पूर्ण

	/* standby */
	ret = tda18218_wr_reg(priv, R17_PD1, priv->regs[R17_PD1] | (1 << 0));
	अगर (ret)
		dev_dbg(&priv->i2c->dev, "%s: failed=%d\n", __func__, ret);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद I2C-gate */

	वापस fe;
पूर्ण
EXPORT_SYMBOL(tda18218_attach);

MODULE_DESCRIPTION("NXP TDA18218HN silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_LICENSE("GPL");
