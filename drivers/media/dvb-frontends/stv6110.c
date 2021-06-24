<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * stv6110.c
 *
 * Driver क्रम ST STV6110 satellite tuner IC.
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>

#समावेश <linux/types.h>

#समावेश "stv6110.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल पूर्णांक debug;

काष्ठा stv6110_priv अणु
	पूर्णांक i2c_address;
	काष्ठा i2c_adapter *i2c;

	u32 mclk;
	u8 clk_भाग;
	u8 gain;
	u8 regs[8];
पूर्ण;

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG args); \
	पूर्ण जबतक (0)

अटल s32 असलsub(s32 a, s32 b)
अणु
	अगर (a > b)
		वापस a - b;
	अन्यथा
		वापस b - a;
पूर्ण;

अटल व्योम stv6110_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक stv6110_ग_लिखो_regs(काष्ठा dvb_frontend *fe, u8 buf[],
							पूर्णांक start, पूर्णांक len)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	पूर्णांक rc;
	u8 cmdbuf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg = अणु
		.addr	= priv->i2c_address,
		.flags	= 0,
		.buf	= cmdbuf,
		.len	= len + 1
	पूर्ण;

	dprपूर्णांकk("%s\n", __func__);

	अगर (1 + len > माप(cmdbuf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr: len=%d is too big!\n",
		       KBUILD_MODNAME, len);
		वापस -EINVAL;
	पूर्ण

	अगर (start + len > 8)
		वापस -EINVAL;

	स_नकल(&cmdbuf[1], buf, len);
	cmdbuf[0] = start;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	rc = i2c_transfer(priv->i2c, &msg, 1);
	अगर (rc != 1)
		dprपूर्णांकk("%s: i2c error\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_पढ़ो_regs(काष्ठा dvb_frontend *fe, u8 regs[],
							पूर्णांक start, पूर्णांक len)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	पूर्णांक rc;
	u8 reg[] = अणु start पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= priv->i2c_address,
			.flags	= 0,
			.buf	= reg,
			.len	= 1,
		पूर्ण, अणु
			.addr	= priv->i2c_address,
			.flags	= I2C_M_RD,
			.buf	= regs,
			.len	= len,
		पूर्ण,
	पूर्ण;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	rc = i2c_transfer(priv->i2c, msg, 2);
	अगर (rc != 2)
		dprपूर्णांकk("%s: i2c error\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	स_नकल(&priv->regs[start], regs, len);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_पढ़ो_reg(काष्ठा dvb_frontend *fe, पूर्णांक start)
अणु
	u8 buf[] = अणु 0 पूर्ण;
	stv6110_पढ़ो_regs(fe, buf, start, 1);

	वापस buf[0];
पूर्ण

अटल पूर्णांक stv6110_sleep(काष्ठा dvb_frontend *fe)
अणु
	u8 reg[] = अणु 0 पूर्ण;
	stv6110_ग_लिखो_regs(fe, reg, 0, 1);

	वापस 0;
पूर्ण

अटल u32 carrier_width(u32 symbol_rate, क्रमागत fe_rolloff rolloff)
अणु
	u32 rlf;

	चयन (rolloff) अणु
	हाल ROLLOFF_20:
		rlf = 20;
		अवरोध;
	हाल ROLLOFF_25:
		rlf = 25;
		अवरोध;
	शेष:
		rlf = 35;
		अवरोध;
	पूर्ण

	वापस symbol_rate  + ((symbol_rate * rlf) / 100);
पूर्ण

अटल पूर्णांक stv6110_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bandwidth)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	u8 r8, ret = 0x04;
	पूर्णांक i;

	अगर ((bandwidth / 2) > 36000000) /*BW/2 max=31+5=36 mhz क्रम r8=31*/
		r8 = 31;
	अन्यथा अगर ((bandwidth / 2) < 5000000) /* BW/2 min=5Mhz क्रम F=0 */
		r8 = 0;
	अन्यथा /*अगर 5 < BW/2 < 36*/
		r8 = (bandwidth / 2) / 1000000 - 5;

	/* ctrl3, RCCLKOFF = 0 Activate the calibration Clock */
	/* ctrl3, CF = r8 Set the LPF value */
	priv->regs[RSTV6110_CTRL3] &= ~((1 << 6) | 0x1f);
	priv->regs[RSTV6110_CTRL3] |= (r8 & 0x1f);
	stv6110_ग_लिखो_regs(fe, &priv->regs[RSTV6110_CTRL3], RSTV6110_CTRL3, 1);
	/* stat1, CALRCSTRT = 1 Start LPF स्वतः calibration*/
	priv->regs[RSTV6110_STAT1] |= 0x02;
	stv6110_ग_लिखो_regs(fe, &priv->regs[RSTV6110_STAT1], RSTV6110_STAT1, 1);

	i = 0;
	/* Wait क्रम CALRCSTRT == 0 */
	जबतक ((i < 10) && (ret != 0)) अणु
		ret = ((stv6110_पढ़ो_reg(fe, RSTV6110_STAT1)) & 0x02);
		mdelay(1);	/* रुको क्रम LPF स्वतः calibration */
		i++;
	पूर्ण

	/* RCCLKOFF = 1 calibration करोne, deactivate the calibration Clock */
	priv->regs[RSTV6110_CTRL3] |= (1 << 6);
	stv6110_ग_लिखो_regs(fe, &priv->regs[RSTV6110_CTRL3], RSTV6110_CTRL3, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	u8 buf0[] = अणु 0x07, 0x11, 0xdc, 0x85, 0x17, 0x01, 0xe6, 0x1e पूर्ण;

	स_नकल(priv->regs, buf0, 8);
	/* K = (Reference / 1000000) - 16 */
	priv->regs[RSTV6110_CTRL1] &= ~(0x1f << 3);
	priv->regs[RSTV6110_CTRL1] |=
				((((priv->mclk / 1000000) - 16) & 0x1f) << 3);

	/* भागisor value क्रम the output घड़ी */
	priv->regs[RSTV6110_CTRL2] &= ~0xc0;
	priv->regs[RSTV6110_CTRL2] |= (priv->clk_भाग << 6);

	stv6110_ग_लिखो_regs(fe, &priv->regs[RSTV6110_CTRL1], RSTV6110_CTRL1, 8);
	msleep(1);
	stv6110_set_bandwidth(fe, 72000000);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	u32 nbsteps, भागider, psd2, freq;
	u8 regs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	stv6110_पढ़ो_regs(fe, regs, 0, 8);
	/*N*/
	भागider = (priv->regs[RSTV6110_TUNING2] & 0x0f) << 8;
	भागider += priv->regs[RSTV6110_TUNING1];

	/*R*/
	nbsteps  = (priv->regs[RSTV6110_TUNING2] >> 6) & 3;
	/*p*/
	psd2  = (priv->regs[RSTV6110_TUNING2] >> 4) & 1;

	freq = भागider * (priv->mclk / 1000);
	freq /= (1 << (nbsteps + psd2));
	freq /= 4;

	*frequency = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_set_frequency(काष्ठा dvb_frontend *fe, u32 frequency)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	u8 ret = 0x04;
	u32 भागider, ref, p, presc, i, result_freq, vco_freq;
	s32 p_calc, p_calc_opt = 1000, r_भाग, r_भाग_opt = 0, p_val;

	dprपूर्णांकk("%s, freq=%d kHz, mclk=%d Hz\n", __func__,
						frequency, priv->mclk);

	/* K = (Reference / 1000000) - 16 */
	priv->regs[RSTV6110_CTRL1] &= ~(0x1f << 3);
	priv->regs[RSTV6110_CTRL1] |=
				((((priv->mclk / 1000000) - 16) & 0x1f) << 3);

	/* BB_GAIN = db/2 */
	priv->regs[RSTV6110_CTRL2] &= ~0x0f;
	priv->regs[RSTV6110_CTRL2] |= (priv->gain & 0x0f);

	अगर (frequency <= 1023000) अणु
		p = 1;
		presc = 0;
	पूर्ण अन्यथा अगर (frequency <= 1300000) अणु
		p = 1;
		presc = 1;
	पूर्ण अन्यथा अगर (frequency <= 2046000) अणु
		p = 0;
		presc = 0;
	पूर्ण अन्यथा अणु
		p = 0;
		presc = 1;
	पूर्ण
	/* DIV4SEL = p*/
	priv->regs[RSTV6110_TUNING2] &= ~(1 << 4);
	priv->regs[RSTV6110_TUNING2] |= (p << 4);

	/* PRESC32ON = presc */
	priv->regs[RSTV6110_TUNING2] &= ~(1 << 5);
	priv->regs[RSTV6110_TUNING2] |= (presc << 5);

	p_val = (पूर्णांक)(1 << (p + 1)) * 10;/* P = 2 or P = 4 */
	क्रम (r_भाग = 0; r_भाग <= 3; r_भाग++) अणु
		p_calc = (priv->mclk / 100000);
		p_calc /= (1 << (r_भाग + 1));
		अगर ((असलsub(p_calc, p_val)) < (असलsub(p_calc_opt, p_val)))
			r_भाग_opt = r_भाग;

		p_calc_opt = (priv->mclk / 100000);
		p_calc_opt /= (1 << (r_भाग_opt + 1));
	पूर्ण

	ref = priv->mclk / ((1 << (r_भाग_opt + 1))  * (1 << (p + 1)));
	भागider = (((frequency * 1000) + (ref >> 1)) / ref);

	/* RDIV = r_भाग_opt */
	priv->regs[RSTV6110_TUNING2] &= ~(3 << 6);
	priv->regs[RSTV6110_TUNING2] |= (((r_भाग_opt) & 3) << 6);

	/* NDIV_MSB = MSB(भागider) */
	priv->regs[RSTV6110_TUNING2] &= ~0x0f;
	priv->regs[RSTV6110_TUNING2] |= (((भागider) >> 8) & 0x0f);

	/* NDIV_LSB, LSB(भागider) */
	priv->regs[RSTV6110_TUNING1] = (भागider & 0xff);

	/* CALVCOSTRT = 1 VCO Auto Calibration */
	priv->regs[RSTV6110_STAT1] |= 0x04;
	stv6110_ग_लिखो_regs(fe, &priv->regs[RSTV6110_CTRL1],
						RSTV6110_CTRL1, 8);

	i = 0;
	/* Wait क्रम CALVCOSTRT == 0 */
	जबतक ((i < 10) && (ret != 0)) अणु
		ret = ((stv6110_पढ़ो_reg(fe, RSTV6110_STAT1)) & 0x04);
		msleep(1); /* रुको क्रम VCO स्वतः calibration */
		i++;
	पूर्ण

	ret = stv6110_पढ़ो_reg(fe, RSTV6110_STAT1);
	stv6110_get_frequency(fe, &result_freq);

	vco_freq = भागider * ((priv->mclk / 1000) / ((1 << (r_भाग_opt + 1))));
	dprपूर्णांकk("%s, stat1=%x, lo_freq=%d kHz, vco_frec=%d kHz\n", __func__,
						ret, result_freq, vco_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 bandwidth = carrier_width(c->symbol_rate, c->rolloff);

	stv6110_set_frequency(fe, c->frequency);
	stv6110_set_bandwidth(fe, bandwidth);

	वापस 0;
पूर्ण

अटल पूर्णांक stv6110_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा stv6110_priv *priv = fe->tuner_priv;
	u8 r8 = 0;
	u8 regs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
	stv6110_पढ़ो_regs(fe, regs, 0, 8);

	/* CF */
	r8 = priv->regs[RSTV6110_CTRL3] & 0x1f;
	*bandwidth = (r8 + 5) * 2000000;/* x2 क्रम ZIF tuner BW/2 = F+5 Mhz */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops stv6110_tuner_ops = अणु
	.info = अणु
		.name = "ST STV6110",
		.frequency_min_hz  =  950 * MHz,
		.frequency_max_hz  = 2150 * MHz,
		.frequency_step_hz =    1 * MHz,
	पूर्ण,
	.init = stv6110_init,
	.release = stv6110_release,
	.sleep = stv6110_sleep,
	.set_params = stv6110_set_params,
	.get_frequency = stv6110_get_frequency,
	.set_frequency = stv6110_set_frequency,
	.get_bandwidth = stv6110_get_bandwidth,
	.set_bandwidth = stv6110_set_bandwidth,

पूर्ण;

काष्ठा dvb_frontend *stv6110_attach(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा stv6110_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv6110_priv *priv = शून्य;
	u8 reg0[] = अणु 0x00, 0x07, 0x11, 0xdc, 0x85, 0x17, 0x01, 0xe6, 0x1e पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = config->i2c_address,
			.flags = 0,
			.buf = reg0,
			.len = 9
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	/* भागisor value क्रम the output घड़ी */
	reg0[2] &= ~0xc0;
	reg0[2] |= (config->clk_भाग << 6);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = i2c_transfer(i2c, msg, 1);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret != 1)
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा stv6110_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->i2c_address = config->i2c_address;
	priv->i2c = i2c;
	priv->mclk = config->mclk;
	priv->clk_भाग = config->clk_भाग;
	priv->gain = config->gain;

	स_नकल(&priv->regs, &reg0[1], 8);

	स_नकल(&fe->ops.tuner_ops, &stv6110_tuner_ops,
				माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	prपूर्णांकk(KERN_INFO "STV6110 attached on addr=%x!\n", priv->i2c_address);

	वापस fe;
पूर्ण
EXPORT_SYMBOL(stv6110_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("ST STV6110 driver");
MODULE_AUTHOR("Igor M. Liplianin");
MODULE_LICENSE("GPL");
