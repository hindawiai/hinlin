<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sharp QM1D1C0042 8PSK tuner driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

/*
 * NOTICE:
 * As the disबंदd inक्रमmation on the chip is very limited,
 * this driver lacks some features, including chip config like IF freq.
 * It assumes that users of this driver (such as a PCI bridge of
 * DTV receiver cards) know the relevant info and
 * configure the chip via I2C अगर necessary.
 *
 * Currently, PT3 driver is the only one that uses this driver,
 * and contains init/config code in its firmware.
 * Thus some part of the code might be dependent on PT3 specअगरic config.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश "qm1d1c0042.h"

#घोषणा QM1D1C0042_NUM_REGS 0x20
#घोषणा QM1D1C0042_NUM_REG_ROWS 2

अटल स्थिर u8
reg_initval[QM1D1C0042_NUM_REG_ROWS][QM1D1C0042_NUM_REGS] = अणु अणु
		0x48, 0x1c, 0xa0, 0x10, 0xbc, 0xc5, 0x20, 0x33,
		0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x00, 0xff, 0xf3, 0x00, 0x2a, 0x64, 0xa6, 0x86,
		0x8c, 0xcf, 0xb8, 0xf1, 0xa8, 0xf2, 0x89, 0x00
	पूर्ण, अणु
		0x68, 0x1c, 0xc0, 0x10, 0xbc, 0xc1, 0x11, 0x33,
		0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x00, 0xff, 0xf3, 0x00, 0x3f, 0x25, 0x5c, 0xd6,
		0x55, 0xcf, 0x95, 0xf6, 0x36, 0xf2, 0x09, 0x00
	पूर्ण
पूर्ण;

अटल पूर्णांक reg_index;

अटल स्थिर काष्ठा qm1d1c0042_config शेष_cfg = अणु
	.xtal_freq = 16000,
	.lpf = 1,
	.fast_srch = 0,
	.lpf_रुको = 20,
	.fast_srch_रुको = 4,
	.normal_srch_रुको = 15,
पूर्ण;

काष्ठा qm1d1c0042_state अणु
	काष्ठा qm1d1c0042_config cfg;
	काष्ठा i2c_client *i2c;
	u8 regs[QM1D1C0042_NUM_REGS];
पूर्ण;

अटल काष्ठा qm1d1c0042_state *cfg_to_state(काष्ठा qm1d1c0042_config *c)
अणु
	वापस container_of(c, काष्ठा qm1d1c0042_state, cfg);
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा qm1d1c0042_state *state, u8 reg, u8 val)
अणु
	u8 wbuf[2] = अणु reg, val पूर्ण;
	पूर्णांक ret;

	ret = i2c_master_send(state->i2c, wbuf, माप(wbuf));
	अगर (ret >= 0 && ret < माप(wbuf))
		ret = -EIO;
	वापस (ret == माप(wbuf)) ? 0 : ret;
पूर्ण

अटल पूर्णांक reg_पढ़ो(काष्ठा qm1d1c0042_state *state, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = state->i2c->addr,
			.flags = 0,
			.buf = &reg,
			.len = 1,
		पूर्ण,
		अणु
			.addr = state->i2c->addr,
			.flags = I2C_M_RD,
			.buf = val,
			.len = 1,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret >= 0 && ret < ARRAY_SIZE(msgs))
		ret = -EIO;
	वापस (ret == ARRAY_SIZE(msgs)) ? 0 : ret;
पूर्ण


अटल पूर्णांक qm1d1c0042_set_srch_mode(काष्ठा qm1d1c0042_state *state, bool fast)
अणु
	अगर (fast)
		state->regs[0x03] |= 0x01; /* set fast search mode */
	अन्यथा
		state->regs[0x03] &= ~0x01 & 0xff;

	वापस reg_ग_लिखो(state, 0x03, state->regs[0x03]);
पूर्ण

अटल पूर्णांक qm1d1c0042_wakeup(काष्ठा qm1d1c0042_state *state)
अणु
	पूर्णांक ret;

	state->regs[0x01] |= 1 << 3;             /* BB_Reg_enable */
	state->regs[0x01] &= (~(1 << 0)) & 0xff; /* NORMAL (wake-up) */
	state->regs[0x05] &= (~(1 << 3)) & 0xff; /* pfd_rst NORMAL */
	ret = reg_ग_लिखो(state, 0x01, state->regs[0x01]);
	अगर (ret == 0)
		ret = reg_ग_लिखो(state, 0x05, state->regs[0x05]);

	अगर (ret < 0)
		dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
			__func__, state->cfg.fe->dvb->num, state->cfg.fe->id);
	वापस ret;
पूर्ण

/* tuner_ops */

अटल पूर्णांक qm1d1c0042_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा qm1d1c0042_state *state;
	काष्ठा qm1d1c0042_config *cfg;

	state = fe->tuner_priv;
	cfg = priv_cfg;

	अगर (cfg->fe)
		state->cfg.fe = cfg->fe;

	अगर (cfg->xtal_freq != QM1D1C0042_CFG_XTAL_DFLT)
		dev_warn(&state->i2c->dev,
			"(%s) changing xtal_freq not supported. ", __func__);
	state->cfg.xtal_freq = शेष_cfg.xtal_freq;

	state->cfg.lpf = cfg->lpf;
	state->cfg.fast_srch = cfg->fast_srch;

	अगर (cfg->lpf_रुको != QM1D1C0042_CFG_WAIT_DFLT)
		state->cfg.lpf_रुको = cfg->lpf_रुको;
	अन्यथा
		state->cfg.lpf_रुको = शेष_cfg.lpf_रुको;

	अगर (cfg->fast_srch_रुको != QM1D1C0042_CFG_WAIT_DFLT)
		state->cfg.fast_srch_रुको = cfg->fast_srch_रुको;
	अन्यथा
		state->cfg.fast_srch_रुको = शेष_cfg.fast_srch_रुको;

	अगर (cfg->normal_srch_रुको != QM1D1C0042_CFG_WAIT_DFLT)
		state->cfg.normal_srch_रुको = cfg->normal_srch_रुको;
	अन्यथा
		state->cfg.normal_srch_रुको = शेष_cfg.normal_srch_रुको;
	वापस 0;
पूर्ण

/* भागisor, vco_band parameters */
/*  अणुmaxfreq,  param1(band?), param2(भाग?) */
अटल स्थिर u32 conv_table[9][3] = अणु
	अणु 2151000, 1, 7 पूर्ण,
	अणु 1950000, 1, 6 पूर्ण,
	अणु 1800000, 1, 5 पूर्ण,
	अणु 1600000, 1, 4 पूर्ण,
	अणु 1450000, 1, 3 पूर्ण,
	अणु 1250000, 1, 2 पूर्ण,
	अणु 1200000, 0, 7 पूर्ण,
	अणु  975000, 0, 6 पूर्ण,
	अणु  950000, 0, 0 पूर्ण
पूर्ण;

अटल पूर्णांक qm1d1c0042_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा qm1d1c0042_state *state;
	u32 freq;
	पूर्णांक i, ret;
	u8 val, mask;
	u32 a, sd;
	s32 b;

	state = fe->tuner_priv;
	freq = fe->dtv_property_cache.frequency;

	state->regs[0x08] &= 0xf0;
	state->regs[0x08] |= 0x09;

	state->regs[0x13] &= 0x9f;
	state->regs[0x13] |= 0x20;

	/* भाग2/vco_band */
	val = state->regs[0x02] & 0x0f;
	क्रम (i = 0; i < 8; i++)
		अगर (freq < conv_table[i][0] && freq >= conv_table[i + 1][0]) अणु
			val |= conv_table[i][1] << 7;
			val |= conv_table[i][2] << 4;
			अवरोध;
		पूर्ण
	ret = reg_ग_लिखो(state, 0x02, val);
	अगर (ret < 0)
		वापस ret;

	a = DIV_ROUND_CLOSEST(freq, state->cfg.xtal_freq);

	state->regs[0x06] &= 0x40;
	state->regs[0x06] |= (a - 12) / 4;
	ret = reg_ग_लिखो(state, 0x06, state->regs[0x06]);
	अगर (ret < 0)
		वापस ret;

	state->regs[0x07] &= 0xf0;
	state->regs[0x07] |= (a - 4 * ((a - 12) / 4 + 1) - 5) & 0x0f;
	ret = reg_ग_लिखो(state, 0x07, state->regs[0x07]);
	अगर (ret < 0)
		वापस ret;

	/* LPF */
	val = state->regs[0x08];
	अगर (state->cfg.lpf) अणु
		/* LPF_CLK, LPF_FC */
		val &= 0xf0;
		val |= 0x02;
	पूर्ण
	ret = reg_ग_लिखो(state, 0x08, val);
	अगर (ret < 0)
		वापस ret;

	/*
	 * b = (freq / state->cfg.xtal_freq - a) << 20;
	 * sd = b          (b >= 0)
	 *      1<<22 + b  (b < 0)
	 */
	b = (s32)भाग64_s64(((s64) freq) << 20, state->cfg.xtal_freq)
			   - (((s64) a) << 20);

	अगर (b >= 0)
		sd = b;
	अन्यथा
		sd = (1 << 22) + b;

	state->regs[0x09] &= 0xc0;
	state->regs[0x09] |= (sd >> 16) & 0x3f;
	state->regs[0x0a] = (sd >> 8) & 0xff;
	state->regs[0x0b] = sd & 0xff;
	ret = reg_ग_लिखो(state, 0x09, state->regs[0x09]);
	अगर (ret == 0)
		ret = reg_ग_लिखो(state, 0x0a, state->regs[0x0a]);
	अगर (ret == 0)
		ret = reg_ग_लिखो(state, 0x0b, state->regs[0x0b]);
	अगर (ret != 0)
		वापस ret;

	अगर (!state->cfg.lpf) अणु
		/* CSEL_Offset */
		ret = reg_ग_लिखो(state, 0x13, state->regs[0x13]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* VCO_TM, LPF_TM */
	mask = state->cfg.lpf ? 0x3f : 0x7f;
	val = state->regs[0x0c] & mask;
	ret = reg_ग_लिखो(state, 0x0c, val);
	अगर (ret < 0)
		वापस ret;
	usleep_range(2000, 3000);
	val = state->regs[0x0c] | ~mask;
	ret = reg_ग_लिखो(state, 0x0c, val);
	अगर (ret < 0)
		वापस ret;

	अगर (state->cfg.lpf)
		msleep(state->cfg.lpf_रुको);
	अन्यथा अगर (state->regs[0x03] & 0x01)
		msleep(state->cfg.fast_srch_रुको);
	अन्यथा
		msleep(state->cfg.normal_srch_रुको);

	अगर (state->cfg.lpf) अणु
		/* LPF_FC */
		ret = reg_ग_लिखो(state, 0x08, 0x09);
		अगर (ret < 0)
			वापस ret;

		/* CSEL_Offset */
		ret = reg_ग_लिखो(state, 0x13, state->regs[0x13]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qm1d1c0042_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा qm1d1c0042_state *state;
	पूर्णांक ret;

	state = fe->tuner_priv;
	state->regs[0x01] &= (~(1 << 3)) & 0xff; /* BB_Reg_disable */
	state->regs[0x01] |= 1 << 0;             /* STDBY */
	state->regs[0x05] |= 1 << 3;             /* pfd_rst STANDBY */
	ret = reg_ग_लिखो(state, 0x05, state->regs[0x05]);
	अगर (ret == 0)
		ret = reg_ग_लिखो(state, 0x01, state->regs[0x01]);
	अगर (ret < 0)
		dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
			__func__, fe->dvb->num, fe->id);
	वापस ret;
पूर्ण

अटल पूर्णांक qm1d1c0042_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा qm1d1c0042_state *state;
	u8 val;
	पूर्णांक i, ret;

	state = fe->tuner_priv;

	reg_ग_लिखो(state, 0x01, 0x0c);
	reg_ग_लिखो(state, 0x01, 0x0c);

	ret = reg_ग_लिखो(state, 0x01, 0x0c); /* soft reset on */
	अगर (ret < 0)
		जाओ failed;
	usleep_range(2000, 3000);

	ret = reg_ग_लिखो(state, 0x01, 0x1c); /* soft reset off */
	अगर (ret < 0)
		जाओ failed;

	/* check ID and choose initial रेजिस्टरs corresponding ID */
	ret = reg_पढ़ो(state, 0x00, &val);
	अगर (ret < 0)
		जाओ failed;
	क्रम (reg_index = 0; reg_index < QM1D1C0042_NUM_REG_ROWS;
	     reg_index++) अणु
		अगर (val == reg_initval[reg_index][0x00])
			अवरोध;
	पूर्ण
	अगर (reg_index >= QM1D1C0042_NUM_REG_ROWS) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण
	स_नकल(state->regs, reg_initval[reg_index], QM1D1C0042_NUM_REGS);
	usleep_range(2000, 3000);

	state->regs[0x0c] |= 0x40;
	ret = reg_ग_लिखो(state, 0x0c, state->regs[0x0c]);
	अगर (ret < 0)
		जाओ failed;
	msleep(state->cfg.lpf_रुको);

	/* set all writable रेजिस्टरs */
	क्रम (i = 1; i <= 0x0c ; i++) अणु
		ret = reg_ग_लिखो(state, i, state->regs[i]);
		अगर (ret < 0)
			जाओ failed;
	पूर्ण
	क्रम (i = 0x11; i < QM1D1C0042_NUM_REGS; i++) अणु
		ret = reg_ग_लिखो(state, i, state->regs[i]);
		अगर (ret < 0)
			जाओ failed;
	पूर्ण

	ret = qm1d1c0042_wakeup(state);
	अगर (ret < 0)
		जाओ failed;

	ret = qm1d1c0042_set_srch_mode(state, state->cfg.fast_srch);
	अगर (ret < 0)
		जाओ failed;

	वापस ret;

failed:
	dev_warn(&state->i2c->dev, "(%s) failed. [adap%d-fe%d]\n",
		__func__, fe->dvb->num, fe->id);
	वापस ret;
पूर्ण

/* I2C driver functions */

अटल स्थिर काष्ठा dvb_tuner_ops qm1d1c0042_ops = अणु
	.info = अणु
		.name = "Sharp QM1D1C0042",

		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
	पूर्ण,

	.init = qm1d1c0042_init,
	.sleep = qm1d1c0042_sleep,
	.set_config = qm1d1c0042_set_config,
	.set_params = qm1d1c0042_set_params,
पूर्ण;


अटल पूर्णांक qm1d1c0042_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा qm1d1c0042_state *state;
	काष्ठा qm1d1c0042_config *cfg;
	काष्ठा dvb_frontend *fe;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;
	state->i2c = client;

	cfg = client->dev.platक्रमm_data;
	fe = cfg->fe;
	fe->tuner_priv = state;
	qm1d1c0042_set_config(fe, cfg);
	स_नकल(&fe->ops.tuner_ops, &qm1d1c0042_ops, माप(qm1d1c0042_ops));

	i2c_set_clientdata(client, &state->cfg);
	dev_info(&client->dev, "Sharp QM1D1C0042 attached.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक qm1d1c0042_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा qm1d1c0042_state *state;

	state = cfg_to_state(i2c_get_clientdata(client));
	state->cfg.fe->tuner_priv = शून्य;
	kमुक्त(state);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id qm1d1c0042_id[] = अणु
	अणु"qm1d1c0042", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, qm1d1c0042_id);

अटल काष्ठा i2c_driver qm1d1c0042_driver = अणु
	.driver = अणु
		.name	= "qm1d1c0042",
	पूर्ण,
	.probe		= qm1d1c0042_probe,
	.हटाओ		= qm1d1c0042_हटाओ,
	.id_table	= qm1d1c0042_id,
पूर्ण;

module_i2c_driver(qm1d1c0042_driver);

MODULE_DESCRIPTION("Sharp QM1D1C0042 tuner");
MODULE_AUTHOR("Akihiro TSUKADA");
MODULE_LICENSE("GPL");
