<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * horus3a.h
 *
 * Sony Horus3A DVB-S/S2 tuner driver
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/types.h>
#समावेश "horus3a.h"
#समावेश <media/dvb_frontend.h>

#घोषणा MAX_WRITE_REGSIZE      5

क्रमागत horus3a_state अणु
	STATE_UNKNOWN,
	STATE_SLEEP,
	STATE_ACTIVE
पूर्ण;

काष्ठा horus3a_priv अणु
	u32			frequency;
	u8			i2c_address;
	काष्ठा i2c_adapter	*i2c;
	क्रमागत horus3a_state	state;
	व्योम			*set_tuner_data;
	पूर्णांक			(*set_tuner)(व्योम *, पूर्णांक);
पूर्ण;

अटल व्योम horus3a_i2c_debug(काष्ठा horus3a_priv *priv,
			      u8 reg, u8 ग_लिखो, स्थिर u8 *data, u32 len)
अणु
	dev_dbg(&priv->i2c->dev, "horus3a: I2C %s reg 0x%02x size %d\n",
		(ग_लिखो == 0 ? "read" : "write"), reg, len);
	prपूर्णांक_hex_dump_bytes("horus3a: I2C data: ",
		DUMP_PREFIX_OFFSET, data, len);
पूर्ण

अटल पूर्णांक horus3a_ग_लिखो_regs(काष्ठा horus3a_priv *priv,
			      u8 reg, स्थिर u8 *data, u32 len)
अणु
	पूर्णांक ret;
	u8 buf[MAX_WRITE_REGSIZE + 1];
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = priv->i2c_address,
			.flags = 0,
			.len = len + 1,
			.buf = buf,
		पूर्ण
	पूर्ण;

	अगर (len + 1 > माप(buf)) अणु
		dev_warn(&priv->i2c->dev,"wr reg=%04x: len=%d is too big!\n",
			 reg, len + 1);
		वापस -E2BIG;
	पूर्ण

	horus3a_i2c_debug(priv, reg, 1, data, len);
	buf[0] = reg;
	स_नकल(&buf[1], data, len);
	ret = i2c_transfer(priv->i2c, msg, 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	अगर (ret < 0) अणु
		dev_warn(&priv->i2c->dev,
			"%s: i2c wr failed=%d reg=%02x len=%d\n",
			KBUILD_MODNAME, ret, reg, len);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक horus3a_ग_लिखो_reg(काष्ठा horus3a_priv *priv, u8 reg, u8 val)
अणु
	u8 पंचांगp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस horus3a_ग_लिखो_regs(priv, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक horus3a_enter_घातer_save(काष्ठा horus3a_priv *priv)
अणु
	u8 data[2];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_SLEEP)
		वापस 0;
	/* IQ Generator disable */
	horus3a_ग_लिखो_reg(priv, 0x2a, 0x79);
	/* MDIV_EN = 0 */
	horus3a_ग_लिखो_reg(priv, 0x29, 0x70);
	/* VCO disable preparation */
	horus3a_ग_लिखो_reg(priv, 0x28, 0x3e);
	/* VCO buffer disable */
	horus3a_ग_लिखो_reg(priv, 0x2a, 0x19);
	/* VCO calibration disable */
	horus3a_ग_लिखो_reg(priv, 0x1c, 0x00);
	/* Power save setting (xtal is not stopped) */
	data[0] = 0xC0;
	/* LNA is Disabled */
	data[1] = 0xA7;
	/* 0x11 - 0x12 */
	horus3a_ग_लिखो_regs(priv, 0x11, data, माप(data));
	priv->state = STATE_SLEEP;
	वापस 0;
पूर्ण

अटल पूर्णांक horus3a_leave_घातer_save(काष्ठा horus3a_priv *priv)
अणु
	u8 data[2];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_ACTIVE)
		वापस 0;
	/* Leave घातer save */
	data[0] = 0x00;
	/* LNA is Disabled */
	data[1] = 0xa7;
	/* 0x11 - 0x12 */
	horus3a_ग_लिखो_regs(priv, 0x11, data, माप(data));
	/* VCO buffer enable */
	horus3a_ग_लिखो_reg(priv, 0x2a, 0x79);
	/* VCO calibration enable */
	horus3a_ग_लिखो_reg(priv, 0x1c, 0xc0);
	/* MDIV_EN = 1 */
	horus3a_ग_लिखो_reg(priv, 0x29, 0x71);
	usleep_range(5000, 7000);
	priv->state = STATE_ACTIVE;
	वापस 0;
पूर्ण

अटल पूर्णांक horus3a_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा horus3a_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम horus3a_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा horus3a_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक horus3a_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा horus3a_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	horus3a_enter_घातer_save(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक horus3a_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा horus3a_priv *priv = fe->tuner_priv;
	u32 frequency = p->frequency;
	u32 symbol_rate = p->symbol_rate/1000;
	u8 mixभाग = 0;
	u8 mभाग = 0;
	u32 ms = 0;
	u8 f_ctl = 0;
	u8 g_ctl = 0;
	u8 fc_lpf = 0;
	u8 data[5];

	dev_dbg(&priv->i2c->dev, "%s(): frequency %dkHz symbol_rate %dksps\n",
		__func__, frequency, symbol_rate);
	अगर (priv->set_tuner)
		priv->set_tuner(priv->set_tuner_data, 0);
	अगर (priv->state == STATE_SLEEP)
		horus3a_leave_घातer_save(priv);

	/* frequency should be X MHz (X : पूर्णांकeger) */
	frequency = DIV_ROUND_CLOSEST(frequency, 1000) * 1000;
	अगर (frequency <= 1155000) अणु
		mixभाग = 4;
		mभाग = 1;
	पूर्ण अन्यथा अणु
		mixभाग = 2;
		mभाग = 0;
	पूर्ण
	/* Assumed that fREF == 1MHz (1000kHz) */
	ms = DIV_ROUND_CLOSEST((frequency * mixभाग) / 2, 1000);
	अगर (ms > 0x7FFF) अणु /* 15 bit */
		dev_err(&priv->i2c->dev, "horus3a: invalid frequency %d\n",
			frequency);
		वापस -EINVAL;
	पूर्ण
	अगर (frequency < 975000) अणु
		/* F_CTL=11100 G_CTL=001 */
		f_ctl = 0x1C;
		g_ctl = 0x01;
	पूर्ण अन्यथा अगर (frequency < 1050000) अणु
		/* F_CTL=11000 G_CTL=010 */
		f_ctl = 0x18;
		g_ctl = 0x02;
	पूर्ण अन्यथा अगर (frequency < 1150000) अणु
		/* F_CTL=10100 G_CTL=010 */
		f_ctl = 0x14;
		g_ctl = 0x02;
	पूर्ण अन्यथा अगर (frequency < 1250000) अणु
		/* F_CTL=10000 G_CTL=011 */
		f_ctl = 0x10;
		g_ctl = 0x03;
	पूर्ण अन्यथा अगर (frequency < 1350000) अणु
		/* F_CTL=01100 G_CTL=100 */
		f_ctl = 0x0C;
		g_ctl = 0x04;
	पूर्ण अन्यथा अगर (frequency < 1450000) अणु
		/* F_CTL=01010 G_CTL=100 */
		f_ctl = 0x0A;
		g_ctl = 0x04;
	पूर्ण अन्यथा अगर (frequency < 1600000) अणु
		/* F_CTL=00111 G_CTL=101 */
		f_ctl = 0x07;
		g_ctl = 0x05;
	पूर्ण अन्यथा अगर (frequency < 1800000) अणु
		/* F_CTL=00100 G_CTL=010 */
		f_ctl = 0x04;
		g_ctl = 0x02;
	पूर्ण अन्यथा अगर (frequency < 2000000) अणु
		/* F_CTL=00010 G_CTL=001 */
		f_ctl = 0x02;
		g_ctl = 0x01;
	पूर्ण अन्यथा अणु
		/* F_CTL=00000 G_CTL=000 */
		f_ctl = 0x00;
		g_ctl = 0x00;
	पूर्ण
	/* LPF cutoff frequency setting */
	अगर (p->delivery_प्रणाली == SYS_DVBS) अणु
		/*
		 * rolloff = 0.35
		 * SR <= 4.3
		 * fc_lpf = 5
		 * 4.3 < SR <= 10
		 * fc_lpf = SR * (1 + rolloff) / 2 + SR / 2 =
		 *	SR * 1.175 = SR * (47/40)
		 * 10 < SR
		 * fc_lpf = SR * (1 + rolloff) / 2 + 5 =
		 *	SR * 0.675 + 5 = SR * (27/40) + 5
		 * NOTE: The result should be round up.
		 */
		अगर (symbol_rate <= 4300)
			fc_lpf = 5;
		अन्यथा अगर (symbol_rate <= 10000)
			fc_lpf = (u8)DIV_ROUND_UP(symbol_rate * 47, 40000);
		अन्यथा
			fc_lpf = (u8)DIV_ROUND_UP(symbol_rate * 27, 40000) + 5;
		/* 5 <= fc_lpf <= 36 */
		अगर (fc_lpf > 36)
			fc_lpf = 36;
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBS2) अणु
		/*
		 * SR <= 4.5:
		 * fc_lpf = 5
		 * 4.5 < SR <= 10:
		 * fc_lpf = SR * (1 + rolloff) / 2 + SR / 2
		 * 10 < SR:
		 * fc_lpf = SR * (1 + rolloff) / 2 + 5
		 * NOTE: The result should be round up.
		 */
		अगर (symbol_rate <= 4500)
			fc_lpf = 5;
		अन्यथा अगर (symbol_rate <= 10000)
			fc_lpf = (u8)((symbol_rate * 11 + (10000-1)) / 10000);
		अन्यथा
			fc_lpf = (u8)((symbol_rate * 3 + (5000-1)) / 5000 + 5);
		/* 5 <= fc_lpf <= 36 is valid */
		अगर (fc_lpf > 36)
			fc_lpf = 36;
	पूर्ण अन्यथा अणु
		dev_err(&priv->i2c->dev,
			"horus3a: invalid delivery system %d\n",
			p->delivery_प्रणाली);
		वापस -EINVAL;
	पूर्ण
	/* 0x00 - 0x04 */
	data[0] = (u8)((ms >> 7) & 0xFF);
	data[1] = (u8)((ms << 1) & 0xFF);
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = (u8)(mभाग << 7);
	horus3a_ग_लिखो_regs(priv, 0x00, data, माप(data));
	/* Write G_CTL, F_CTL */
	horus3a_ग_लिखो_reg(priv, 0x09, (u8)((g_ctl << 5) | f_ctl));
	/* Write LPF cutoff frequency */
	horus3a_ग_लिखो_reg(priv, 0x37, (u8)(0x80 | (fc_lpf << 1)));
	/* Start Calibration */
	horus3a_ग_लिखो_reg(priv, 0x05, 0x80);
	/* IQ Generator enable */
	horus3a_ग_लिखो_reg(priv, 0x2a, 0x7b);
	/* tuner stabilization समय */
	msleep(60);
	/* Store tuned frequency to the काष्ठा */
	priv->frequency = ms * 2 * 1000 / mixभाग;
	वापस 0;
पूर्ण

अटल पूर्णांक horus3a_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा horus3a_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops horus3a_tuner_ops = अणु
	.info = अणु
		.name = "Sony Horus3a",
		.frequency_min_hz  =  950 * MHz,
		.frequency_max_hz  = 2150 * MHz,
		.frequency_step_hz =    1 * MHz,
	पूर्ण,
	.init = horus3a_init,
	.release = horus3a_release,
	.sleep = horus3a_sleep,
	.set_params = horus3a_set_params,
	.get_frequency = horus3a_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *horus3a_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा horus3a_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	u8 buf[3], val;
	काष्ठा horus3a_priv *priv = शून्य;

	priv = kzalloc(माप(काष्ठा horus3a_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* रुको 4ms after घातer on */
	usleep_range(4000, 6000);
	/* IQ Generator disable */
	horus3a_ग_लिखो_reg(priv, 0x2a, 0x79);
	/* REF_R = Xtal Frequency */
	buf[0] = config->xtal_freq_mhz;
	buf[1] = config->xtal_freq_mhz;
	buf[2] = 0;
	/* 0x6 - 0x8 */
	horus3a_ग_लिखो_regs(priv, 0x6, buf, 3);
	/* IQ Out = Single Ended */
	horus3a_ग_लिखो_reg(priv, 0x0a, 0x40);
	चयन (config->xtal_freq_mhz) अणु
	हाल 27:
		val = 0x1f;
		अवरोध;
	हाल 24:
		val = 0x10;
		अवरोध;
	हाल 16:
		val = 0xc;
		अवरोध;
	शेष:
		val = 0;
		dev_warn(&priv->i2c->dev,
			"horus3a: invalid xtal frequency %dMHz\n",
			config->xtal_freq_mhz);
		अवरोध;
	पूर्ण
	val <<= 2;
	horus3a_ग_लिखो_reg(priv, 0x0e, val);
	horus3a_enter_घातer_save(priv);
	usleep_range(3000, 5000);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	स_नकल(&fe->ops.tuner_ops, &horus3a_tuner_ops,
				माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
		"Sony HORUS3A attached on addr=%x at I2C adapter %p\n",
		priv->i2c_address, priv->i2c);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(horus3a_attach);

MODULE_DESCRIPTION("Sony HORUS3A satellite tuner driver");
MODULE_AUTHOR("Sergey Kozlov <serjk@netup.ru>");
MODULE_LICENSE("GPL");
