<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Montage Technology TS2020 - Silicon Tuner driver
    Copyright (C) 2009-2012 Konstantin Dimitrov <kosio.dimitrov@gmail.com>

    Copyright (C) 2009-2012 TurboSight.com

 */

#समावेश <media/dvb_frontend.h>
#समावेश "ts2020.h"
#समावेश <linux/regmap.h>
#समावेश <linux/math64.h>

#घोषणा TS2020_XTAL_FREQ   27000 /* in kHz */
#घोषणा FREQ_OFFSET_LOW_SYM_RATE 3000

काष्ठा ts2020_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex regmap_mutex;
	काष्ठा regmap_config regmap_config;
	काष्ठा regmap *regmap;
	काष्ठा dvb_frontend *fe;
	काष्ठा delayed_work stat_work;
	पूर्णांक (*get_agc_pwm)(काष्ठा dvb_frontend *fe, u8 *_agc_pwm);
	/* i2c details */
	काष्ठा i2c_adapter *i2c;
	पूर्णांक i2c_address;
	bool loop_through:1;
	u8 clk_out:2;
	u8 clk_out_भाग:5;
	bool करोnt_poll:1;
	u32 frequency_भाग; /* LO output भागider चयन frequency */
	u32 frequency_khz; /* actual used LO frequency */
#घोषणा TS2020_M88TS2020 0
#घोषणा TS2020_M88TS2022 1
	u8 tuner;
पूर्ण;

काष्ठा ts2020_reg_val अणु
	u8 reg;
	u8 val;
पूर्ण;

अटल व्योम ts2020_stat_work(काष्ठा work_काष्ठा *work);

अटल व्योम ts2020_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	काष्ठा i2c_client *client = priv->client;

	dev_dbg(&client->dev, "\n");

	i2c_unरेजिस्टर_device(client);
पूर्ण

अटल पूर्णांक ts2020_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u8 u8पंचांगp;

	अगर (priv->tuner == TS2020_M88TS2020)
		u8पंचांगp = 0x0a; /* XXX: probably wrong */
	अन्यथा
		u8पंचांगp = 0x00;

	ret = regmap_ग_लिखो(priv->regmap, u8पंचांगp, 0x00);
	अगर (ret < 0)
		वापस ret;

	/* stop statistics polling */
	अगर (!priv->करोnt_poll)
		cancel_delayed_work_sync(&priv->stat_work);
	वापस 0;
पूर्ण

अटल पूर्णांक ts2020_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	पूर्णांक i;
	u8 u8पंचांगp;

	अगर (priv->tuner == TS2020_M88TS2020) अणु
		regmap_ग_लिखो(priv->regmap, 0x42, 0x73);
		regmap_ग_लिखो(priv->regmap, 0x05, priv->clk_out_भाग);
		regmap_ग_लिखो(priv->regmap, 0x20, 0x27);
		regmap_ग_लिखो(priv->regmap, 0x07, 0x02);
		regmap_ग_लिखो(priv->regmap, 0x11, 0xff);
		regmap_ग_लिखो(priv->regmap, 0x60, 0xf9);
		regmap_ग_लिखो(priv->regmap, 0x08, 0x01);
		regmap_ग_लिखो(priv->regmap, 0x00, 0x41);
	पूर्ण अन्यथा अणु
		अटल स्थिर काष्ठा ts2020_reg_val reg_vals[] = अणु
			अणु0x7d, 0x9dपूर्ण,
			अणु0x7c, 0x9aपूर्ण,
			अणु0x7a, 0x76पूर्ण,
			अणु0x3b, 0x01पूर्ण,
			अणु0x63, 0x88पूर्ण,
			अणु0x61, 0x85पूर्ण,
			अणु0x22, 0x30पूर्ण,
			अणु0x30, 0x40पूर्ण,
			अणु0x20, 0x23पूर्ण,
			अणु0x24, 0x02पूर्ण,
			अणु0x12, 0xa0पूर्ण,
		पूर्ण;

		regmap_ग_लिखो(priv->regmap, 0x00, 0x01);
		regmap_ग_लिखो(priv->regmap, 0x00, 0x03);

		चयन (priv->clk_out) अणु
		हाल TS2020_CLK_OUT_DISABLED:
			u8पंचांगp = 0x60;
			अवरोध;
		हाल TS2020_CLK_OUT_ENABLED:
			u8पंचांगp = 0x70;
			regmap_ग_लिखो(priv->regmap, 0x05, priv->clk_out_भाग);
			अवरोध;
		हाल TS2020_CLK_OUT_ENABLED_XTALOUT:
			u8पंचांगp = 0x6c;
			अवरोध;
		शेष:
			u8पंचांगp = 0x60;
			अवरोध;
		पूर्ण

		regmap_ग_लिखो(priv->regmap, 0x42, u8पंचांगp);

		अगर (priv->loop_through)
			u8पंचांगp = 0xec;
		अन्यथा
			u8पंचांगp = 0x6c;

		regmap_ग_लिखो(priv->regmap, 0x62, u8पंचांगp);

		क्रम (i = 0; i < ARRAY_SIZE(reg_vals); i++)
			regmap_ग_लिखो(priv->regmap, reg_vals[i].reg,
				     reg_vals[i].val);
	पूर्ण

	/* Initialise v5 stats here */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].uvalue = 0;

	/* Start statistics polling by invoking the work function */
	ts2020_stat_work(&priv->stat_work.work);
	वापस 0;
पूर्ण

अटल पूर्णांक ts2020_tuner_gate_ctrl(काष्ठा dvb_frontend *fe, u8 offset)
अणु
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	ret = regmap_ग_लिखो(priv->regmap, 0x51, 0x1f - offset);
	ret |= regmap_ग_लिखो(priv->regmap, 0x51, 0x1f);
	ret |= regmap_ग_लिखो(priv->regmap, 0x50, offset);
	ret |= regmap_ग_लिखो(priv->regmap, 0x50, 0x00);
	msleep(20);
	वापस ret;
पूर्ण

अटल पूर्णांक ts2020_set_tuner_rf(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ts2020_priv *dev = fe->tuner_priv;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;

	ret = regmap_पढ़ो(dev->regmap, 0x3d, &uपंचांगp);
	अगर (ret)
		वापस ret;

	uपंचांगp &= 0x7f;
	अगर (uपंचांगp < 0x16)
		uपंचांगp = 0xa1;
	अन्यथा अगर (uपंचांगp == 0x16)
		uपंचांगp = 0x99;
	अन्यथा
		uपंचांगp = 0xf9;

	regmap_ग_लिखो(dev->regmap, 0x60, uपंचांगp);
	ret = ts2020_tuner_gate_ctrl(fe, 0x08);

	वापस ret;
पूर्ण

अटल पूर्णांक ts2020_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	अचिन्हित पूर्णांक uपंचांगp;
	u32 f3db, gभाग28;
	u16 u16पंचांगp, value, lpf_coeff;
	u8 buf[3], reg10, lpf_mxभाग, mlpf_max, mlpf_min, nlpf;
	अचिन्हित पूर्णांक f_ref_khz, f_vco_khz, भाग_ref, भाग_out, pll_n;
	अचिन्हित पूर्णांक frequency_khz = c->frequency;

	/*
	 * Integer-N PLL synthesizer
	 * kHz is used क्रम all calculations to keep calculations within 32-bit
	 */
	f_ref_khz = TS2020_XTAL_FREQ;
	भाग_ref = DIV_ROUND_CLOSEST(f_ref_khz, 2000);

	/* select LO output भागider */
	अगर (frequency_khz < priv->frequency_भाग) अणु
		भाग_out = 4;
		reg10 = 0x10;
	पूर्ण अन्यथा अणु
		भाग_out = 2;
		reg10 = 0x00;
	पूर्ण

	f_vco_khz = frequency_khz * भाग_out;
	pll_n = f_vco_khz * भाग_ref / f_ref_khz;
	pll_n += pll_n % 2;
	priv->frequency_khz = pll_n * f_ref_khz / भाग_ref / भाग_out;

	pr_debug("frequency=%u offset=%d f_vco_khz=%u pll_n=%u div_ref=%u div_out=%u\n",
		 priv->frequency_khz, priv->frequency_khz - c->frequency,
		 f_vco_khz, pll_n, भाग_ref, भाग_out);

	अगर (priv->tuner == TS2020_M88TS2020) अणु
		lpf_coeff = 2766;
		reg10 |= 0x01;
		ret = regmap_ग_लिखो(priv->regmap, 0x10, reg10);
	पूर्ण अन्यथा अणु
		lpf_coeff = 3200;
		reg10 |= 0x0b;
		ret = regmap_ग_लिखो(priv->regmap, 0x10, reg10);
		ret |= regmap_ग_लिखो(priv->regmap, 0x11, 0x40);
	पूर्ण

	u16पंचांगp = pll_n - 1024;
	buf[0] = (u16पंचांगp >> 8) & 0xff;
	buf[1] = (u16पंचांगp >> 0) & 0xff;
	buf[2] = भाग_ref - 8;

	ret |= regmap_ग_लिखो(priv->regmap, 0x01, buf[0]);
	ret |= regmap_ग_लिखो(priv->regmap, 0x02, buf[1]);
	ret |= regmap_ग_लिखो(priv->regmap, 0x03, buf[2]);

	ret |= ts2020_tuner_gate_ctrl(fe, 0x10);
	अगर (ret < 0)
		वापस -ENODEV;

	ret |= ts2020_tuner_gate_ctrl(fe, 0x08);

	/* Tuner RF */
	अगर (priv->tuner == TS2020_M88TS2020)
		ret |= ts2020_set_tuner_rf(fe);

	gभाग28 = (TS2020_XTAL_FREQ / 1000 * 1694 + 500) / 1000;
	ret |= regmap_ग_लिखो(priv->regmap, 0x04, gभाग28 & 0xff);
	ret |= ts2020_tuner_gate_ctrl(fe, 0x04);
	अगर (ret < 0)
		वापस -ENODEV;

	अगर (priv->tuner == TS2020_M88TS2022) अणु
		ret = regmap_ग_लिखो(priv->regmap, 0x25, 0x00);
		ret |= regmap_ग_लिखो(priv->regmap, 0x27, 0x70);
		ret |= regmap_ग_लिखो(priv->regmap, 0x41, 0x09);
		ret |= regmap_ग_लिखो(priv->regmap, 0x08, 0x0b);
		अगर (ret < 0)
			वापस -ENODEV;
	पूर्ण

	regmap_पढ़ो(priv->regmap, 0x26, &uपंचांगp);
	value = uपंचांगp;

	f3db = (c->bandwidth_hz / 1000 / 2) + 2000;
	f3db += FREQ_OFFSET_LOW_SYM_RATE; /* FIXME: ~always too wide filter */
	f3db = clamp(f3db, 7000U, 40000U);

	gभाग28 = gभाग28 * 207 / (value * 2 + 151);
	mlpf_max = gभाग28 * 135 / 100;
	mlpf_min = gभाग28 * 78 / 100;
	अगर (mlpf_max > 63)
		mlpf_max = 63;

	nlpf = (f3db * gभाग28 * 2 / lpf_coeff /
		(TS2020_XTAL_FREQ / 1000)  + 1) / 2;
	अगर (nlpf > 23)
		nlpf = 23;
	अगर (nlpf < 1)
		nlpf = 1;

	lpf_mxभाग = (nlpf * (TS2020_XTAL_FREQ / 1000)
		* lpf_coeff * 2  / f3db + 1) / 2;

	अगर (lpf_mxभाग < mlpf_min) अणु
		nlpf++;
		lpf_mxभाग = (nlpf * (TS2020_XTAL_FREQ / 1000)
			* lpf_coeff * 2  / f3db + 1) / 2;
	पूर्ण

	अगर (lpf_mxभाग > mlpf_max)
		lpf_mxभाग = mlpf_max;

	ret = regmap_ग_लिखो(priv->regmap, 0x04, lpf_mxभाग);
	ret |= regmap_ग_लिखो(priv->regmap, 0x06, nlpf);

	ret |= ts2020_tuner_gate_ctrl(fe, 0x04);

	ret |= ts2020_tuner_gate_ctrl(fe, 0x01);

	msleep(80);

	वापस (ret < 0) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक ts2020_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा ts2020_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency_khz;
	वापस 0;
पूर्ण

अटल पूर्णांक ts2020_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = 0; /* Zero-IF */
	वापस 0;
पूर्ण

/*
 * Get the tuner gain.
 * @fe: The front end क्रम which we're determining the gain
 * @v_agc: The voltage of the AGC from the demodulator (0-2600mV)
 * @_gain: Where to store the gain (in 0.001dB units)
 *
 * Returns 0 or a negative error code.
 */
अटल पूर्णांक ts2020_पढ़ो_tuner_gain(काष्ठा dvb_frontend *fe, अचिन्हित v_agc,
				  __s64 *_gain)
अणु
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	अचिन्हित दीर्घ gain1, gain2, gain3;
	अचिन्हित uपंचांगp;
	पूर्णांक ret;

	/* Read the RF gain */
	ret = regmap_पढ़ो(priv->regmap, 0x3d, &uपंचांगp);
	अगर (ret < 0)
		वापस ret;
	gain1 = uपंचांगp & 0x1f;

	/* Read the baseband gain */
	ret = regmap_पढ़ो(priv->regmap, 0x21, &uपंचांगp);
	अगर (ret < 0)
		वापस ret;
	gain2 = uपंचांगp & 0x1f;

	चयन (priv->tuner) अणु
	हाल TS2020_M88TS2020:
		gain1 = clamp_t(दीर्घ, gain1, 0, 15);
		gain2 = clamp_t(दीर्घ, gain2, 0, 13);
		v_agc = clamp_t(दीर्घ, v_agc, 400, 1100);

		*_gain = -((__s64)gain1 * 2330 +
			   gain2 * 3500 +
			   v_agc * 24 / 10 * 10 +
			   10000);
		/* gain in range -19600 to -116850 in units of 0.001dB */
		अवरोध;

	हाल TS2020_M88TS2022:
		ret = regmap_पढ़ो(priv->regmap, 0x66, &uपंचांगp);
		अगर (ret < 0)
			वापस ret;
		gain3 = (uपंचांगp >> 3) & 0x07;

		gain1 = clamp_t(दीर्घ, gain1, 0, 15);
		gain2 = clamp_t(दीर्घ, gain2, 2, 16);
		gain3 = clamp_t(दीर्घ, gain3, 0, 6);
		v_agc = clamp_t(दीर्घ, v_agc, 600, 1600);

		*_gain = -((__s64)gain1 * 2650 +
			   gain2 * 3380 +
			   gain3 * 2850 +
			   v_agc * 176 / 100 * 10 -
			   30000);
		/* gain in range -47320 to -158950 in units of 0.001dB */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get the AGC inक्रमmation from the demodulator and use that to calculate the
 * tuner gain.
 */
अटल पूर्णांक ts2020_get_tuner_gain(काष्ठा dvb_frontend *fe, __s64 *_gain)
अणु
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	पूर्णांक v_agc = 0, ret;
	u8 agc_pwm;

	/* Read the AGC PWM rate from the demodulator */
	अगर (priv->get_agc_pwm) अणु
		ret = priv->get_agc_pwm(fe, &agc_pwm);
		अगर (ret < 0)
			वापस ret;

		चयन (priv->tuner) अणु
		हाल TS2020_M88TS2020:
			v_agc = (पूर्णांक)agc_pwm * 20 - 1166;
			अवरोध;
		हाल TS2020_M88TS2022:
			v_agc = (पूर्णांक)agc_pwm * 16 - 670;
			अवरोध;
		पूर्ण

		अगर (v_agc < 0)
			v_agc = 0;
	पूर्ण

	वापस ts2020_पढ़ो_tuner_gain(fe, v_agc, _gain);
पूर्ण

/*
 * Gather statistics on a regular basis
 */
अटल व्योम ts2020_stat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ts2020_priv *priv = container_of(work, काष्ठा ts2020_priv,
					       stat_work.work);
	काष्ठा i2c_client *client = priv->client;
	काष्ठा dtv_frontend_properties *c = &priv->fe->dtv_property_cache;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	ret = ts2020_get_tuner_gain(priv->fe, &c->strength.stat[0].svalue);
	अगर (ret < 0)
		जाओ err;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;

	अगर (!priv->करोnt_poll)
		schedule_delayed_work(&priv->stat_work, msecs_to_jअगरfies(2000));
	वापस;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
पूर्ण

/*
 * Read TS2020 संकेत strength in v3 क्रमmat.
 */
अटल पूर्णांक ts2020_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
				       u16 *_संकेत_strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा ts2020_priv *priv = fe->tuner_priv;
	अचिन्हित strength;
	__s64 gain;

	अगर (priv->करोnt_poll)
		ts2020_stat_work(&priv->stat_work.work);

	अगर (c->strength.stat[0].scale == FE_SCALE_NOT_AVAILABLE) अणु
		*_संकेत_strength = 0;
		वापस 0;
	पूर्ण

	gain = c->strength.stat[0].svalue;

	/* Calculate the संकेत strength based on the total gain of the tuner */
	अगर (gain < -85000)
		/* 0%: no संकेत or weak संकेत */
		strength = 0;
	अन्यथा अगर (gain < -65000)
		/* 0% - 60%: weak संकेत */
		strength = 0 + भाग64_s64((85000 + gain) * 3, 1000);
	अन्यथा अगर (gain < -45000)
		/* 60% - 90%: normal संकेत */
		strength = 60 + भाग64_s64((65000 + gain) * 3, 2000);
	अन्यथा
		/* 90% - 99%: strong संकेत */
		strength = 90 + भाग64_s64((45000 + gain), 5000);

	*_संकेत_strength = strength * 65535 / 100;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops ts2020_tuner_ops = अणु
	.info = अणु
		.name = "TS2020",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz
	पूर्ण,
	.init = ts2020_init,
	.release = ts2020_release,
	.sleep = ts2020_sleep,
	.set_params = ts2020_set_params,
	.get_frequency = ts2020_get_frequency,
	.get_अगर_frequency = ts2020_get_अगर_frequency,
	.get_rf_strength = ts2020_पढ़ो_संकेत_strength,
पूर्ण;

काष्ठा dvb_frontend *ts2020_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा ts2020_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info;

	/* This is only used by ts2020_probe() so can be on the stack */
	काष्ठा ts2020_config pdata;

	स_नकल(&pdata, config, माप(pdata));
	pdata.fe = fe;
	pdata.attach_in_use = true;

	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "ts2020", I2C_NAME_SIZE);
	board_info.addr = config->tuner_address;
	board_info.platक्रमm_data = &pdata;
	client = i2c_new_client_device(i2c, &board_info);
	अगर (!i2c_client_has_driver(client))
		वापस शून्य;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(ts2020_attach);

/*
 * We implement own regmap locking due to legacy DVB attach which uses frontend
 * gate control callback to control I2C bus access. We can खोलो / बंद gate and
 * serialize whole खोलो / I2C-operation / बंद sequence at the same.
 */
अटल व्योम ts2020_regmap_lock(व्योम *__dev)
अणु
	काष्ठा ts2020_priv *dev = __dev;

	mutex_lock(&dev->regmap_mutex);
	अगर (dev->fe->ops.i2c_gate_ctrl)
		dev->fe->ops.i2c_gate_ctrl(dev->fe, 1);
पूर्ण

अटल व्योम ts2020_regmap_unlock(व्योम *__dev)
अणु
	काष्ठा ts2020_priv *dev = __dev;

	अगर (dev->fe->ops.i2c_gate_ctrl)
		dev->fe->ops.i2c_gate_ctrl(dev->fe, 0);
	mutex_unlock(&dev->regmap_mutex);
पूर्ण

अटल पूर्णांक ts2020_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ts2020_config *pdata = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = pdata->fe;
	काष्ठा ts2020_priv *dev;
	पूर्णांक ret;
	u8 u8पंचांगp;
	अचिन्हित पूर्णांक uपंचांगp;
	अक्षर *chip_str;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* create regmap */
	mutex_init(&dev->regmap_mutex);
	dev->regmap_config.reg_bits = 8;
	dev->regmap_config.val_bits = 8;
	dev->regmap_config.lock = ts2020_regmap_lock;
	dev->regmap_config.unlock = ts2020_regmap_unlock;
	dev->regmap_config.lock_arg = dev;
	dev->regmap = regmap_init_i2c(client, &dev->regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	dev->i2c = client->adapter;
	dev->i2c_address = client->addr;
	dev->loop_through = pdata->loop_through;
	dev->clk_out = pdata->clk_out;
	dev->clk_out_भाग = pdata->clk_out_भाग;
	dev->करोnt_poll = pdata->करोnt_poll;
	dev->frequency_भाग = pdata->frequency_भाग;
	dev->fe = fe;
	dev->get_agc_pwm = pdata->get_agc_pwm;
	fe->tuner_priv = dev;
	dev->client = client;
	INIT_DELAYED_WORK(&dev->stat_work, ts2020_stat_work);

	/* check अगर the tuner is there */
	ret = regmap_पढ़ो(dev->regmap, 0x00, &uपंचांगp);
	अगर (ret)
		जाओ err_regmap_निकास;

	अगर ((uपंचांगp & 0x03) == 0x00) अणु
		ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x01);
		अगर (ret)
			जाओ err_regmap_निकास;

		usleep_range(2000, 50000);
	पूर्ण

	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x03);
	अगर (ret)
		जाओ err_regmap_निकास;

	usleep_range(2000, 50000);

	ret = regmap_पढ़ो(dev->regmap, 0x00, &uपंचांगp);
	अगर (ret)
		जाओ err_regmap_निकास;

	dev_dbg(&client->dev, "chip_id=%02x\n", uपंचांगp);

	चयन (uपंचांगp) अणु
	हाल 0x01:
	हाल 0x41:
	हाल 0x81:
		dev->tuner = TS2020_M88TS2020;
		chip_str = "TS2020";
		अगर (!dev->frequency_भाग)
			dev->frequency_भाग = 1060000;
		अवरोध;
	हाल 0xc3:
	हाल 0x83:
		dev->tuner = TS2020_M88TS2022;
		chip_str = "TS2022";
		अगर (!dev->frequency_भाग)
			dev->frequency_भाग = 1103000;
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err_regmap_निकास;
	पूर्ण

	अगर (dev->tuner == TS2020_M88TS2022) अणु
		चयन (dev->clk_out) अणु
		हाल TS2020_CLK_OUT_DISABLED:
			u8पंचांगp = 0x60;
			अवरोध;
		हाल TS2020_CLK_OUT_ENABLED:
			u8पंचांगp = 0x70;
			ret = regmap_ग_लिखो(dev->regmap, 0x05, dev->clk_out_भाग);
			अगर (ret)
				जाओ err_regmap_निकास;
			अवरोध;
		हाल TS2020_CLK_OUT_ENABLED_XTALOUT:
			u8पंचांगp = 0x6c;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ err_regmap_निकास;
		पूर्ण

		ret = regmap_ग_लिखो(dev->regmap, 0x42, u8पंचांगp);
		अगर (ret)
			जाओ err_regmap_निकास;

		अगर (dev->loop_through)
			u8पंचांगp = 0xec;
		अन्यथा
			u8पंचांगp = 0x6c;

		ret = regmap_ग_लिखो(dev->regmap, 0x62, u8पंचांगp);
		अगर (ret)
			जाओ err_regmap_निकास;
	पूर्ण

	/* sleep */
	ret = regmap_ग_लिखो(dev->regmap, 0x00, 0x00);
	अगर (ret)
		जाओ err_regmap_निकास;

	dev_info(&client->dev,
		 "Montage Technology %s successfully identified\n", chip_str);

	स_नकल(&fe->ops.tuner_ops, &ts2020_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
	अगर (!pdata->attach_in_use)
		fe->ops.tuner_ops.release = शून्य;

	i2c_set_clientdata(client, dev);
	वापस 0;
err_regmap_निकास:
	regmap_निकास(dev->regmap);
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ts2020_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ts2020_priv *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	/* stop statistics polling */
	अगर (!dev->करोnt_poll)
		cancel_delayed_work_sync(&dev->stat_work);

	regmap_निकास(dev->regmap);
	kमुक्त(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ts2020_id_table[] = अणु
	अणु"ts2020", 0पूर्ण,
	अणु"ts2022", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ts2020_id_table);

अटल काष्ठा i2c_driver ts2020_driver = अणु
	.driver = अणु
		.name	= "ts2020",
	पूर्ण,
	.probe		= ts2020_probe,
	.हटाओ		= ts2020_हटाओ,
	.id_table	= ts2020_id_table,
पूर्ण;

module_i2c_driver(ts2020_driver);

MODULE_AUTHOR("Konstantin Dimitrov <kosio.dimitrov@gmail.com>");
MODULE_DESCRIPTION("Montage Technology TS2020 - Silicon tuner driver module");
MODULE_LICENSE("GPL");
