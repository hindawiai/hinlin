<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Quantek QT1010 silicon tuner
 *
 *  Copyright (C) 2006 Antti Palosaari <crope@iki.fi>
 *                     Aapo Tahkola <aet@rasterburn.org>
 */
#समावेश "qt1010.h"
#समावेश "qt1010_priv.h"

/* पढ़ो single रेजिस्टर */
अटल पूर्णांक qt1010_पढ़ोreg(काष्ठा qt1010_priv *priv, u8 reg, u8 *val)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->cfg->i2c_address,
		  .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = priv->cfg->i2c_address,
		  .flags = I2C_M_RD, .buf = val, .len = 1 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(priv->i2c, msg, 2) != 2) अणु
		dev_warn(&priv->i2c->dev, "%s: i2c rd failed reg=%02x\n",
				KBUILD_MODNAME, reg);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

/* ग_लिखो single रेजिस्टर */
अटल पूर्णांक qt1010_ग_लिखोreg(काष्ठा qt1010_priv *priv, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = priv->cfg->i2c_address,
			       .flags = 0, .buf = buf, .len = 2 पूर्ण;

	अगर (i2c_transfer(priv->i2c, &msg, 1) != 1) अणु
		dev_warn(&priv->i2c->dev, "%s: i2c wr failed reg=%02x\n",
				KBUILD_MODNAME, reg);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qt1010_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा qt1010_priv *priv;
	पूर्णांक err;
	u32 freq, भाग, mod1, mod2;
	u8 i, पंचांगpval, reg05;
	qt1010_i2c_oper_t rd[48] = अणु
		अणु QT1010_WR, 0x01, 0x80 पूर्ण,
		अणु QT1010_WR, 0x02, 0x3f पूर्ण,
		अणु QT1010_WR, 0x05, 0xff पूर्ण, /* 02 c ग_लिखो */
		अणु QT1010_WR, 0x06, 0x44 पूर्ण,
		अणु QT1010_WR, 0x07, 0xff पूर्ण, /* 04 c ग_लिखो */
		अणु QT1010_WR, 0x08, 0x08 पूर्ण,
		अणु QT1010_WR, 0x09, 0xff पूर्ण, /* 06 c ग_लिखो */
		अणु QT1010_WR, 0x0a, 0xff पूर्ण, /* 07 c ग_लिखो */
		अणु QT1010_WR, 0x0b, 0xff पूर्ण, /* 08 c ग_लिखो */
		अणु QT1010_WR, 0x0c, 0xe1 पूर्ण,
		अणु QT1010_WR, 0x1a, 0xff पूर्ण, /* 10 c ग_लिखो */
		अणु QT1010_WR, 0x1b, 0x00 पूर्ण,
		अणु QT1010_WR, 0x1c, 0x89 पूर्ण,
		अणु QT1010_WR, 0x11, 0xff पूर्ण, /* 13 c ग_लिखो */
		अणु QT1010_WR, 0x12, 0xff पूर्ण, /* 14 c ग_लिखो */
		अणु QT1010_WR, 0x22, 0xff पूर्ण, /* 15 c ग_लिखो */
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x1e, 0xd0 पूर्ण,
		अणु QT1010_RD, 0x22, 0xff पूर्ण, /* 16 c पढ़ो */
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_RD, 0x05, 0xff पूर्ण, /* 20 c पढ़ो */
		अणु QT1010_RD, 0x22, 0xff पूर्ण, /* 21 c पढ़ो */
		अणु QT1010_WR, 0x23, 0xd0 पूर्ण,
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x1e, 0xe0 पूर्ण,
		अणु QT1010_RD, 0x23, 0xff पूर्ण, /* 25 c पढ़ो */
		अणु QT1010_RD, 0x23, 0xff पूर्ण, /* 26 c पढ़ो */
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x24, 0xd0 पूर्ण,
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x1e, 0xf0 पूर्ण,
		अणु QT1010_RD, 0x24, 0xff पूर्ण, /* 31 c पढ़ो */
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x14, 0x7f पूर्ण,
		अणु QT1010_WR, 0x15, 0x7f पूर्ण,
		अणु QT1010_WR, 0x05, 0xff पूर्ण, /* 35 c ग_लिखो */
		अणु QT1010_WR, 0x06, 0x00 पूर्ण,
		अणु QT1010_WR, 0x15, 0x1f पूर्ण,
		अणु QT1010_WR, 0x16, 0xff पूर्ण,
		अणु QT1010_WR, 0x18, 0xff पूर्ण,
		अणु QT1010_WR, 0x1f, 0xff पूर्ण, /* 40 c ग_लिखो */
		अणु QT1010_WR, 0x20, 0xff पूर्ण, /* 41 c ग_लिखो */
		अणु QT1010_WR, 0x21, 0x53 पूर्ण,
		अणु QT1010_WR, 0x25, 0xff पूर्ण, /* 43 c ग_लिखो */
		अणु QT1010_WR, 0x26, 0x15 पूर्ण,
		अणु QT1010_WR, 0x00, 0xff पूर्ण, /* 45 c ग_लिखो */
		अणु QT1010_WR, 0x02, 0x00 पूर्ण,
		अणु QT1010_WR, 0x01, 0x00 पूर्ण
	पूर्ण;

#घोषणा FREQ1 32000000 /* 32 MHz */
#घोषणा FREQ2  4000000 /* 4 MHz Quartz oscillator in the stick? */

	priv = fe->tuner_priv;
	freq = c->frequency;
	भाग = (freq + QT1010_OFFSET) / QT1010_STEP;
	freq = (भाग * QT1010_STEP) - QT1010_OFFSET;
	mod1 = (freq + QT1010_OFFSET) % FREQ1;
	mod2 = (freq + QT1010_OFFSET) % FREQ2;
	priv->frequency = freq;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	/* reg 05 base value */
	अगर      (freq < 290000000) reg05 = 0x14; /* 290 MHz */
	अन्यथा अगर (freq < 610000000) reg05 = 0x34; /* 610 MHz */
	अन्यथा अगर (freq < 802000000) reg05 = 0x54; /* 802 MHz */
	अन्यथा                       reg05 = 0x74;

	/* 0x5 */
	rd[2].val = reg05;

	/* 07 - set frequency: 32 MHz scale */
	rd[4].val = (freq + QT1010_OFFSET) / FREQ1;

	/* 09 - changes every 8/24 MHz */
	अगर (mod1 < 8000000) rd[6].val = 0x1d;
	अन्यथा                rd[6].val = 0x1c;

	/* 0a - set frequency: 4 MHz scale (max 28 MHz) */
	अगर      (mod1 < 1*FREQ2) rd[7].val = 0x09; /*  +0 MHz */
	अन्यथा अगर (mod1 < 2*FREQ2) rd[7].val = 0x08; /*  +4 MHz */
	अन्यथा अगर (mod1 < 3*FREQ2) rd[7].val = 0x0f; /*  +8 MHz */
	अन्यथा अगर (mod1 < 4*FREQ2) rd[7].val = 0x0e; /* +12 MHz */
	अन्यथा अगर (mod1 < 5*FREQ2) rd[7].val = 0x0d; /* +16 MHz */
	अन्यथा अगर (mod1 < 6*FREQ2) rd[7].val = 0x0c; /* +20 MHz */
	अन्यथा अगर (mod1 < 7*FREQ2) rd[7].val = 0x0b; /* +24 MHz */
	अन्यथा                     rd[7].val = 0x0a; /* +28 MHz */

	/* 0b - changes every 2/2 MHz */
	अगर (mod2 < 2000000) rd[8].val = 0x45;
	अन्यथा                rd[8].val = 0x44;

	/* 1a - set frequency: 125 kHz scale (max 3875 kHz)*/
	पंचांगpval = 0x78; /* byte, overflows पूर्णांकentionally */
	rd[10].val = पंचांगpval-((mod2/QT1010_STEP)*0x08);

	/* 11 */
	rd[13].val = 0xfd; /* TODO: correct value calculation */

	/* 12 */
	rd[14].val = 0x91; /* TODO: correct value calculation */

	/* 22 */
	अगर      (freq < 450000000) rd[15].val = 0xd0; /* 450 MHz */
	अन्यथा अगर (freq < 482000000) rd[15].val = 0xd1; /* 482 MHz */
	अन्यथा अगर (freq < 514000000) rd[15].val = 0xd4; /* 514 MHz */
	अन्यथा अगर (freq < 546000000) rd[15].val = 0xd7; /* 546 MHz */
	अन्यथा अगर (freq < 610000000) rd[15].val = 0xda; /* 610 MHz */
	अन्यथा                       rd[15].val = 0xd0;

	/* 05 */
	rd[35].val = (reg05 & 0xf0);

	/* 1f */
	अगर      (mod1 <  8000000) पंचांगpval = 0x00;
	अन्यथा अगर (mod1 < 12000000) पंचांगpval = 0x01;
	अन्यथा अगर (mod1 < 16000000) पंचांगpval = 0x02;
	अन्यथा अगर (mod1 < 24000000) पंचांगpval = 0x03;
	अन्यथा अगर (mod1 < 28000000) पंचांगpval = 0x04;
	अन्यथा                      पंचांगpval = 0x05;
	rd[40].val = (priv->reg1f_init_val + 0x0e + पंचांगpval);

	/* 20 */
	अगर      (mod1 <  8000000) पंचांगpval = 0x00;
	अन्यथा अगर (mod1 < 12000000) पंचांगpval = 0x01;
	अन्यथा अगर (mod1 < 20000000) पंचांगpval = 0x02;
	अन्यथा अगर (mod1 < 24000000) पंचांगpval = 0x03;
	अन्यथा अगर (mod1 < 28000000) पंचांगpval = 0x04;
	अन्यथा                      पंचांगpval = 0x05;
	rd[41].val = (priv->reg20_init_val + 0x0d + पंचांगpval);

	/* 25 */
	rd[43].val = priv->reg25_init_val;

	/* 00 */
	rd[45].val = 0x92; /* TODO: correct value calculation */

	dev_dbg(&priv->i2c->dev,
			"%s: freq:%u 05:%02x 07:%02x 09:%02x 0a:%02x 0b:%02x " \
			"1a:%02x 11:%02x 12:%02x 22:%02x 05:%02x 1f:%02x " \
			"20:%02x 25:%02x 00:%02x\n", __func__, \
			freq, rd[2].val, rd[4].val, rd[6].val, rd[7].val, \
			rd[8].val, rd[10].val, rd[13].val, rd[14].val, \
			rd[15].val, rd[35].val, rd[40].val, rd[41].val, \
			rd[43].val, rd[45].val);

	क्रम (i = 0; i < ARRAY_SIZE(rd); i++) अणु
		अगर (rd[i].oper == QT1010_WR) अणु
			err = qt1010_ग_लिखोreg(priv, rd[i].reg, rd[i].val);
		पूर्ण अन्यथा अणु /* पढ़ो is required to proper locking */
			err = qt1010_पढ़ोreg(priv, rd[i].reg, &पंचांगpval);
		पूर्ण
		अगर (err) वापस err;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस 0;
पूर्ण

अटल पूर्णांक qt1010_init_meas1(काष्ठा qt1010_priv *priv,
			     u8 oper, u8 reg, u8 reg_init_val, u8 *retval)
अणु
	u8 i, val1, val2;
	पूर्णांक err;

	qt1010_i2c_oper_t i2c_data[] = अणु
		अणु QT1010_WR, reg, reg_init_val पूर्ण,
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x1e, oper पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_data); i++) अणु
		err = qt1010_ग_लिखोreg(priv, i2c_data[i].reg,
				      i2c_data[i].val);
		अगर (err)
			वापस err;
	पूर्ण

	err = qt1010_पढ़ोreg(priv, reg, &val2);
	अगर (err)
		वापस err;
	करो अणु
		val1 = val2;
		err = qt1010_पढ़ोreg(priv, reg, &val2);
		अगर (err)
			वापस err;

		dev_dbg(&priv->i2c->dev, "%s: compare reg:%02x %02x %02x\n",
				__func__, reg, val1, val2);
	पूर्ण जबतक (val1 != val2);
	*retval = val1;

	वापस qt1010_ग_लिखोreg(priv, 0x1e, 0x00);
पूर्ण

अटल पूर्णांक qt1010_init_meas2(काष्ठा qt1010_priv *priv,
			    u8 reg_init_val, u8 *retval)
अणु
	u8 i, val = 0xff;
	पूर्णांक err;
	qt1010_i2c_oper_t i2c_data[] = अणु
		अणु QT1010_WR, 0x07, reg_init_val पूर्ण,
		अणु QT1010_WR, 0x22, 0xd0 पूर्ण,
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x1e, 0xd0 पूर्ण,
		अणु QT1010_RD, 0x22, 0xff पूर्ण,
		अणु QT1010_WR, 0x1e, 0x00 पूर्ण,
		अणु QT1010_WR, 0x22, 0xff पूर्ण
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_data); i++) अणु
		अगर (i2c_data[i].oper == QT1010_WR) अणु
			err = qt1010_ग_लिखोreg(priv, i2c_data[i].reg,
					      i2c_data[i].val);
		पूर्ण अन्यथा अणु
			err = qt1010_पढ़ोreg(priv, i2c_data[i].reg, &val);
		पूर्ण
		अगर (err)
			वापस err;
	पूर्ण
	*retval = val;
	वापस 0;
पूर्ण

अटल पूर्णांक qt1010_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा qt1010_priv *priv = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक err = 0;
	u8 i, पंचांगpval, *valptr = शून्य;

	अटल स्थिर qt1010_i2c_oper_t i2c_data[] = अणु
		अणु QT1010_WR, 0x01, 0x80 पूर्ण,
		अणु QT1010_WR, 0x0d, 0x84 पूर्ण,
		अणु QT1010_WR, 0x0e, 0xb7 पूर्ण,
		अणु QT1010_WR, 0x2a, 0x23 पूर्ण,
		अणु QT1010_WR, 0x2c, 0xdc पूर्ण,
		अणु QT1010_M1, 0x25, 0x40 पूर्ण, /* get reg 25 init value */
		अणु QT1010_M1, 0x81, 0xff पूर्ण, /* get reg 25 init value */
		अणु QT1010_WR, 0x2b, 0x70 पूर्ण,
		अणु QT1010_WR, 0x2a, 0x23 पूर्ण,
		अणु QT1010_M1, 0x26, 0x08 पूर्ण,
		अणु QT1010_M1, 0x82, 0xff पूर्ण,
		अणु QT1010_WR, 0x05, 0x14 पूर्ण,
		अणु QT1010_WR, 0x06, 0x44 पूर्ण,
		अणु QT1010_WR, 0x07, 0x28 पूर्ण,
		अणु QT1010_WR, 0x08, 0x0b पूर्ण,
		अणु QT1010_WR, 0x11, 0xfd पूर्ण,
		अणु QT1010_M1, 0x22, 0x0d पूर्ण,
		अणु QT1010_M1, 0xd0, 0xff पूर्ण,
		अणु QT1010_WR, 0x06, 0x40 पूर्ण,
		अणु QT1010_WR, 0x16, 0xf0 पूर्ण,
		अणु QT1010_WR, 0x02, 0x38 पूर्ण,
		अणु QT1010_WR, 0x03, 0x18 पूर्ण,
		अणु QT1010_WR, 0x20, 0xe0 पूर्ण,
		अणु QT1010_M1, 0x1f, 0x20 पूर्ण, /* get reg 1f init value */
		अणु QT1010_M1, 0x84, 0xff पूर्ण, /* get reg 1f init value */
		अणु QT1010_RD, 0x20, 0x20 पूर्ण, /* get reg 20 init value */
		अणु QT1010_WR, 0x03, 0x19 पूर्ण,
		अणु QT1010_WR, 0x02, 0x3f पूर्ण,
		अणु QT1010_WR, 0x21, 0x53 पूर्ण,
		अणु QT1010_RD, 0x21, 0xff पूर्ण,
		अणु QT1010_WR, 0x11, 0xfd पूर्ण,
		अणु QT1010_WR, 0x05, 0x34 पूर्ण,
		अणु QT1010_WR, 0x06, 0x44 पूर्ण,
		अणु QT1010_WR, 0x08, 0x08 पूर्ण
	पूर्ण;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	क्रम (i = 0; i < ARRAY_SIZE(i2c_data); i++) अणु
		चयन (i2c_data[i].oper) अणु
		हाल QT1010_WR:
			err = qt1010_ग_लिखोreg(priv, i2c_data[i].reg,
					      i2c_data[i].val);
			अवरोध;
		हाल QT1010_RD:
			अगर (i2c_data[i].val == 0x20)
				valptr = &priv->reg20_init_val;
			अन्यथा
				valptr = &पंचांगpval;
			err = qt1010_पढ़ोreg(priv, i2c_data[i].reg, valptr);
			अवरोध;
		हाल QT1010_M1:
			अगर (i2c_data[i].val == 0x25)
				valptr = &priv->reg25_init_val;
			अन्यथा अगर (i2c_data[i].val == 0x1f)
				valptr = &priv->reg1f_init_val;
			अन्यथा
				valptr = &पंचांगpval;

			BUG_ON(i >= ARRAY_SIZE(i2c_data) - 1);

			err = qt1010_init_meas1(priv, i2c_data[i+1].reg,
						i2c_data[i].reg,
						i2c_data[i].val, valptr);
			i++;
			अवरोध;
		पूर्ण
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0x31; i < 0x3a; i++) /* 0x31 - 0x39 */
		अगर ((err = qt1010_init_meas2(priv, i, &पंचांगpval)))
			वापस err;

	अगर (!c->frequency)
		c->frequency = 545000000; /* Sigmatek DVB-110 545000000 */
				      /* MSI Megasky 580 GL861 533000000 */
	वापस qt1010_set_params(fe);
पूर्ण

अटल व्योम qt1010_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक qt1010_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा qt1010_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक qt1010_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	*frequency = 36125000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops qt1010_tuner_ops = अणु
	.info = अणु
		.name              = "Quantek QT1010",
		.frequency_min_hz  = QT1010_MIN_FREQ,
		.frequency_max_hz  = QT1010_MAX_FREQ,
		.frequency_step_hz = QT1010_STEP,
	पूर्ण,

	.release       = qt1010_release,
	.init          = qt1010_init,
	/* TODO: implement sleep */

	.set_params    = qt1010_set_params,
	.get_frequency = qt1010_get_frequency,
	.get_अगर_frequency = qt1010_get_अगर_frequency,
पूर्ण;

काष्ठा dvb_frontend * qt1010_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c,
				    काष्ठा qt1010_config *cfg)
अणु
	काष्ठा qt1010_priv *priv = शून्य;
	u8 id;

	priv = kzalloc(माप(काष्ठा qt1010_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;

	priv->cfg = cfg;
	priv->i2c = i2c;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */


	/* Try to detect tuner chip. Probably this is not correct रेजिस्टर. */
	अगर (qt1010_पढ़ोreg(priv, 0x29, &id) != 0 || (id != 0x39)) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	dev_info(&priv->i2c->dev,
			"%s: Quantek QT1010 successfully identified\n",
			KBUILD_MODNAME);

	स_नकल(&fe->ops.tuner_ops, &qt1010_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = priv;
	वापस fe;
पूर्ण
EXPORT_SYMBOL(qt1010_attach);

MODULE_DESCRIPTION("Quantek QT1010 silicon tuner driver");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_AUTHOR("Aapo Tahkola <aet@rasterburn.org>");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
