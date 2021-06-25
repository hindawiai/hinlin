<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Fitiघातer FC0011 tuner driver
 *
 * Copyright (C) 2012 Michael Buesch <m@bues.ch>
 *
 * Derived from FC0012 tuner driver:
 * Copyright (C) 2012 Hans-Frieder Vogt <hfvogt@gmx.net>
 */

#समावेश "fc0011.h"


/* Tuner रेजिस्टरs */
क्रमागत अणु
	FC11_REG_0,
	FC11_REG_FA,		/* FA */
	FC11_REG_FP,		/* FP */
	FC11_REG_XINHI,		/* XIN high 8 bit */
	FC11_REG_XINLO,		/* XIN low 8 bit */
	FC11_REG_VCO,		/* VCO */
	FC11_REG_VCOSEL,	/* VCO select */
	FC11_REG_7,		/* Unknown tuner reg 7 */
	FC11_REG_8,		/* Unknown tuner reg 8 */
	FC11_REG_9,
	FC11_REG_10,		/* Unknown tuner reg 10 */
	FC11_REG_11,		/* Unknown tuner reg 11 */
	FC11_REG_12,
	FC11_REG_RCCAL,		/* RC calibrate */
	FC11_REG_VCOCAL,	/* VCO calibrate */
	FC11_REG_15,
	FC11_REG_16,		/* Unknown tuner reg 16 */
	FC11_REG_17,

	FC11_NR_REGS,		/* Number of रेजिस्टरs */
पूर्ण;

क्रमागत FC11_REG_VCOSEL_bits अणु
	FC11_VCOSEL_2		= 0x08, /* VCO select 2 */
	FC11_VCOSEL_1		= 0x10, /* VCO select 1 */
	FC11_VCOSEL_CLKOUT	= 0x20, /* Fix घड़ी out */
	FC11_VCOSEL_BW7M	= 0x40, /* 7MHz bw */
	FC11_VCOSEL_BW6M	= 0x80, /* 6MHz bw */
पूर्ण;

क्रमागत FC11_REG_RCCAL_bits अणु
	FC11_RCCAL_FORCE	= 0x10, /* क्रमce */
पूर्ण;

क्रमागत FC11_REG_VCOCAL_bits अणु
	FC11_VCOCAL_RUN		= 0,	/* VCO calibration run */
	FC11_VCOCAL_VALUEMASK	= 0x3F,	/* VCO calibration value mask */
	FC11_VCOCAL_OK		= 0x40,	/* VCO calibration Ok */
	FC11_VCOCAL_RESET	= 0x80, /* VCO calibration reset */
पूर्ण;


काष्ठा fc0011_priv अणु
	काष्ठा i2c_adapter *i2c;
	u8 addr;

	u32 frequency;
	u32 bandwidth;
पूर्ण;


अटल पूर्णांक fc0011_ग_लिखोreg(काष्ठा fc0011_priv *priv, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->addr,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		dev_err(&priv->i2c->dev,
			"I2C write reg failed, reg: %02x, val: %02x\n",
			reg, val);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fc0011_पढ़ोreg(काष्ठा fc0011_priv *priv, u8 reg, u8 *val)
अणु
	u8 dummy;
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->addr,
		  .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = priv->addr,
		  .flags = I2C_M_RD, .buf = val ? : &dummy, .len = 1 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		dev_err(&priv->i2c->dev,
			"I2C read failed, reg: %02x\n", reg);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fc0011_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक fc0011_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा fc0011_priv *priv = fe->tuner_priv;
	पूर्णांक err;

	अगर (WARN_ON(!fe->callback))
		वापस -EINVAL;

	err = fe->callback(priv->i2c, DVB_FRONTEND_COMPONENT_TUNER,
			   FC0011_FE_CALLBACK_POWER, priv->addr);
	अगर (err) अणु
		dev_err(&priv->i2c->dev, "Power-on callback failed\n");
		वापस err;
	पूर्ण
	err = fe->callback(priv->i2c, DVB_FRONTEND_COMPONENT_TUNER,
			   FC0011_FE_CALLBACK_RESET, priv->addr);
	अगर (err) अणु
		dev_err(&priv->i2c->dev, "Reset callback failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Initiate VCO calibration */
अटल पूर्णांक fc0011_vcocal_trigger(काष्ठा fc0011_priv *priv)
अणु
	पूर्णांक err;

	err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOCAL, FC11_VCOCAL_RESET);
	अगर (err)
		वापस err;
	err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOCAL, FC11_VCOCAL_RUN);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* Read VCO calibration value */
अटल पूर्णांक fc0011_vcocal_पढ़ो(काष्ठा fc0011_priv *priv, u8 *value)
अणु
	पूर्णांक err;

	err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOCAL, FC11_VCOCAL_RUN);
	अगर (err)
		वापस err;
	usleep_range(10000, 20000);
	err = fc0011_पढ़ोreg(priv, FC11_REG_VCOCAL, value);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक fc0011_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा fc0011_priv *priv = fe->tuner_priv;
	पूर्णांक err;
	अचिन्हित पूर्णांक i, vco_retries;
	u32 freq = p->frequency / 1000;
	u32 bandwidth = p->bandwidth_hz / 1000;
	u32 fvco, xin, frac, xभाग, xभागr;
	u8 fa, fp, vco_sel, vco_cal;
	u8 regs[FC11_NR_REGS] = अणु पूर्ण;

	regs[FC11_REG_7] = 0x0F;
	regs[FC11_REG_8] = 0x3E;
	regs[FC11_REG_10] = 0xB8;
	regs[FC11_REG_11] = 0x80;
	regs[FC11_REG_RCCAL] = 0x04;
	err = fc0011_ग_लिखोreg(priv, FC11_REG_7, regs[FC11_REG_7]);
	err |= fc0011_ग_लिखोreg(priv, FC11_REG_8, regs[FC11_REG_8]);
	err |= fc0011_ग_लिखोreg(priv, FC11_REG_10, regs[FC11_REG_10]);
	err |= fc0011_ग_लिखोreg(priv, FC11_REG_11, regs[FC11_REG_11]);
	err |= fc0011_ग_लिखोreg(priv, FC11_REG_RCCAL, regs[FC11_REG_RCCAL]);
	अगर (err)
		वापस -EIO;

	/* Set VCO freq and VCO भाग */
	अगर (freq < 54000) अणु
		fvco = freq * 64;
		regs[FC11_REG_VCO] = 0x82;
	पूर्ण अन्यथा अगर (freq < 108000) अणु
		fvco = freq * 32;
		regs[FC11_REG_VCO] = 0x42;
	पूर्ण अन्यथा अगर (freq < 216000) अणु
		fvco = freq * 16;
		regs[FC11_REG_VCO] = 0x22;
	पूर्ण अन्यथा अगर (freq < 432000) अणु
		fvco = freq * 8;
		regs[FC11_REG_VCO] = 0x12;
	पूर्ण अन्यथा अणु
		fvco = freq * 4;
		regs[FC11_REG_VCO] = 0x0A;
	पूर्ण

	/* Calc XIN. The PLL reference frequency is 18 MHz. */
	xभाग = fvco / 18000;
	WARN_ON(xभाग > 0xFF);
	frac = fvco - xभाग * 18000;
	frac = (frac << 15) / 18000;
	अगर (frac >= 16384)
		frac += 32786;
	अगर (!frac)
		xin = 0;
	अन्यथा
		xin = clamp_t(u32, frac, 512, 65024);
	regs[FC11_REG_XINHI] = xin >> 8;
	regs[FC11_REG_XINLO] = xin;

	/* Calc FP and FA */
	xभागr = xभाग;
	अगर (fvco - xभाग * 18000 >= 9000)
		xभागr += 1; /* round */
	fp = xभागr / 8;
	fa = xभागr - fp * 8;
	अगर (fa < 2) अणु
		fp -= 1;
		fa += 8;
	पूर्ण
	अगर (fp > 0x1F) अणु
		fp = 0x1F;
		fa = 0xF;
	पूर्ण
	अगर (fa >= fp) अणु
		dev_warn(&priv->i2c->dev,
			 "fa %02X >= fp %02X, but trying to continue\n",
			 (अचिन्हित पूर्णांक)(u8)fa, (अचिन्हित पूर्णांक)(u8)fp);
	पूर्ण
	regs[FC11_REG_FA] = fa;
	regs[FC11_REG_FP] = fp;

	/* Select bandwidth */
	चयन (bandwidth) अणु
	हाल 8000:
		अवरोध;
	हाल 7000:
		regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_BW7M;
		अवरोध;
	शेष:
		dev_warn(&priv->i2c->dev, "Unsupported bandwidth %u kHz. Using 6000 kHz.\n",
			 bandwidth);
		bandwidth = 6000;
		fallthrough;
	हाल 6000:
		regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_BW6M;
		अवरोध;
	पूर्ण

	/* Pre VCO select */
	अगर (fvco < 2320000) अणु
		vco_sel = 0;
		regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
	पूर्ण अन्यथा अगर (fvco < 3080000) अणु
		vco_sel = 1;
		regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
		regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_1;
	पूर्ण अन्यथा अणु
		vco_sel = 2;
		regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
		regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_2;
	पूर्ण

	/* Fix क्रम low freqs */
	अगर (freq < 45000) अणु
		regs[FC11_REG_FA] = 0x6;
		regs[FC11_REG_FP] = 0x11;
	पूर्ण

	/* Clock out fix */
	regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_CLKOUT;

	/* Write the cached रेजिस्टरs */
	क्रम (i = FC11_REG_FA; i <= FC11_REG_VCOSEL; i++) अणु
		err = fc0011_ग_लिखोreg(priv, i, regs[i]);
		अगर (err)
			वापस err;
	पूर्ण

	/* VCO calibration */
	err = fc0011_vcocal_trigger(priv);
	अगर (err)
		वापस err;
	err = fc0011_vcocal_पढ़ो(priv, &vco_cal);
	अगर (err)
		वापस err;
	vco_retries = 0;
	जबतक (!(vco_cal & FC11_VCOCAL_OK) && vco_retries < 3) अणु
		/* Reset the tuner and try again */
		err = fe->callback(priv->i2c, DVB_FRONTEND_COMPONENT_TUNER,
				   FC0011_FE_CALLBACK_RESET, priv->addr);
		अगर (err) अणु
			dev_err(&priv->i2c->dev, "Failed to reset tuner\n");
			वापस err;
		पूर्ण
		/* Reinit tuner config */
		err = 0;
		क्रम (i = FC11_REG_FA; i <= FC11_REG_VCOSEL; i++)
			err |= fc0011_ग_लिखोreg(priv, i, regs[i]);
		err |= fc0011_ग_लिखोreg(priv, FC11_REG_7, regs[FC11_REG_7]);
		err |= fc0011_ग_लिखोreg(priv, FC11_REG_8, regs[FC11_REG_8]);
		err |= fc0011_ग_लिखोreg(priv, FC11_REG_10, regs[FC11_REG_10]);
		err |= fc0011_ग_लिखोreg(priv, FC11_REG_11, regs[FC11_REG_11]);
		err |= fc0011_ग_लिखोreg(priv, FC11_REG_RCCAL, regs[FC11_REG_RCCAL]);
		अगर (err)
			वापस -EIO;
		/* VCO calibration */
		err = fc0011_vcocal_trigger(priv);
		अगर (err)
			वापस err;
		err = fc0011_vcocal_पढ़ो(priv, &vco_cal);
		अगर (err)
			वापस err;
		vco_retries++;
	पूर्ण
	अगर (!(vco_cal & FC11_VCOCAL_OK)) अणु
		dev_err(&priv->i2c->dev,
			"Failed to read VCO calibration value (got %02X)\n",
			(अचिन्हित पूर्णांक)vco_cal);
		वापस -EIO;
	पूर्ण
	vco_cal &= FC11_VCOCAL_VALUEMASK;

	चयन (vco_sel) अणु
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	हाल 0:
		अगर (vco_cal < 8) अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_1;
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
			err = fc0011_vcocal_trigger(priv);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	हाल 1:
		अगर (vco_cal < 5) अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_2;
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
			err = fc0011_vcocal_trigger(priv);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (vco_cal <= 48) अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_1;
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
			err = fc0011_vcocal_trigger(priv);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	हाल 2:
		अगर (vco_cal > 53) अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_1;
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
			err = fc0011_vcocal_trigger(priv);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			regs[FC11_REG_VCOSEL] &= ~(FC11_VCOSEL_1 | FC11_VCOSEL_2);
			regs[FC11_REG_VCOSEL] |= FC11_VCOSEL_2;
			err = fc0011_ग_लिखोreg(priv, FC11_REG_VCOSEL,
					      regs[FC11_REG_VCOSEL]);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण
	err = fc0011_vcocal_पढ़ो(priv, शून्य);
	अगर (err)
		वापस err;
	usleep_range(10000, 50000);

	err = fc0011_पढ़ोreg(priv, FC11_REG_RCCAL, &regs[FC11_REG_RCCAL]);
	अगर (err)
		वापस err;
	regs[FC11_REG_RCCAL] |= FC11_RCCAL_FORCE;
	err = fc0011_ग_लिखोreg(priv, FC11_REG_RCCAL, regs[FC11_REG_RCCAL]);
	अगर (err)
		वापस err;
	regs[FC11_REG_16] = 0xB;
	err = fc0011_ग_लिखोreg(priv, FC11_REG_16, regs[FC11_REG_16]);
	अगर (err)
		वापस err;

	dev_dbg(&priv->i2c->dev, "Tuned to fa=%02X fp=%02X xin=%02X%02X vco=%02X vcosel=%02X vcocal=%02X(%u) bw=%u\n",
		(अचिन्हित पूर्णांक)regs[FC11_REG_FA],
		(अचिन्हित पूर्णांक)regs[FC11_REG_FP],
		(अचिन्हित पूर्णांक)regs[FC11_REG_XINHI],
		(अचिन्हित पूर्णांक)regs[FC11_REG_XINLO],
		(अचिन्हित पूर्णांक)regs[FC11_REG_VCO],
		(अचिन्हित पूर्णांक)regs[FC11_REG_VCOSEL],
		(अचिन्हित पूर्णांक)vco_cal, vco_retries,
		(अचिन्हित पूर्णांक)bandwidth);

	priv->frequency = p->frequency;
	priv->bandwidth = p->bandwidth_hz;

	वापस 0;
पूर्ण

अटल पूर्णांक fc0011_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा fc0011_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक fc0011_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक fc0011_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा fc0011_priv *priv = fe->tuner_priv;

	*bandwidth = priv->bandwidth;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops fc0011_tuner_ops = अणु
	.info = अणु
		.name		  = "Fitipower FC0011",

		.frequency_min_hz =   45 * MHz,
		.frequency_max_hz = 1000 * MHz,
	पूर्ण,

	.release		= fc0011_release,
	.init			= fc0011_init,

	.set_params		= fc0011_set_params,

	.get_frequency		= fc0011_get_frequency,
	.get_अगर_frequency	= fc0011_get_अगर_frequency,
	.get_bandwidth		= fc0011_get_bandwidth,
पूर्ण;

काष्ठा dvb_frontend *fc0011_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा i2c_adapter *i2c,
				   स्थिर काष्ठा fc0011_config *config)
अणु
	काष्ठा fc0011_priv *priv;

	priv = kzalloc(माप(काष्ठा fc0011_priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	priv->i2c = i2c;
	priv->addr = config->i2c_address;

	fe->tuner_priv = priv;
	fe->ops.tuner_ops = fc0011_tuner_ops;

	dev_info(&priv->i2c->dev, "Fitipower FC0011 tuner attached\n");

	वापस fe;
पूर्ण
EXPORT_SYMBOL(fc0011_attach);

MODULE_DESCRIPTION("Fitipower FC0011 silicon tuner driver");
MODULE_AUTHOR("Michael Buesch <m@bues.ch>");
MODULE_LICENSE("GPL");
