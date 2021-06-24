<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Zarlink zl10036 DVB-S silicon tuner
 *
 * Copyright (C) 2006 Tino Reiअक्षरdt
 * Copyright (C) 2007-2009 Matthias Schwarzott <zzam@gentoo.de>
 *
 **
 * The data sheet क्रम this tuner can be found at:
 *    http://www.mcmilk.de/projects/dvb-card/datasheets/ZL10036.pdf
 *
 * This one is working: (at my Avermedia DVB-S Pro)
 * - zl10036 (40pin, FTA)
 *
 * A driver क्रम zl10038 should be very similar.
 */

#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "zl10036.h"

अटल पूर्णांक zl10036_debug;
#घोषणा dprपूर्णांकk(level, args...) \
	करो अणु अगर (zl10036_debug & level) prपूर्णांकk(KERN_DEBUG "zl10036: " args); \
	पूर्ण जबतक (0)

#घोषणा deb_info(args...)  dprपूर्णांकk(0x01, args)
#घोषणा deb_i2c(args...)  dprपूर्णांकk(0x02, args)

काष्ठा zl10036_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा zl10036_config *config;
	u32 frequency;
	u8 br, bf;
पूर्ण;


/* This driver assumes the tuner is driven by a 10.111MHz Cristal */
#घोषणा _XTAL 10111

/* Some of the possible भागiders:
 *   64, (ग_लिखो 0x05 to reg), freq step size   158kHz
 *   10, (ग_लिखो 0x0a to reg), freq step size 1.011kHz (used here)
 *    5, (ग_लिखो 0x09 to reg), freq step size 2.022kHz
 */

#घोषणा _RDIV 10
#घोषणा _RDIV_REG 0x0a
#घोषणा _FR   (_XTAL/_RDIV)

#घोषणा STATUS_POR 0x80 /* Power on Reset */
#घोषणा STATUS_FL  0x40 /* Frequency & Phase Lock */

/* पढ़ो/ग_लिखो क्रम zl10036 and zl10038 */

अटल पूर्णांक zl10036_पढ़ो_status_reg(काष्ठा zl10036_state *state)
अणु
	u8 status;
	काष्ठा i2c_msg msg[1] = अणु
		अणु .addr = state->config->tuner_address, .flags = I2C_M_RD,
		  .buf = &status, .len = माप(status) पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(state->i2c, msg, 1) != 1) अणु
		prपूर्णांकk(KERN_ERR "%s: i2c read failed at addr=%02x\n",
			__func__, state->config->tuner_address);
		वापस -EIO;
	पूर्ण

	deb_i2c("R(status): %02x  [FL=%d]\n", status,
		(status & STATUS_FL) ? 1 : 0);
	अगर (status & STATUS_POR)
		deb_info("%s: Power-On-Reset bit enabled - need to initialize the tuner\n",
			 __func__);

	वापस status;
पूर्ण

अटल पूर्णांक zl10036_ग_लिखो(काष्ठा zl10036_state *state, u8 buf[], u8 count)
अणु
	काष्ठा i2c_msg msg[1] = अणु
		अणु .addr = state->config->tuner_address, .flags = 0,
		  .buf = buf, .len = count पूर्ण,
	पूर्ण;
	u8 reg = 0;
	पूर्णांक ret;

	अगर (zl10036_debug & 0x02) अणु
		/* every 8bit-value satisअगरes this!
		 * so only check क्रम debug log */
		अगर ((buf[0] & 0x80) == 0x00)
			reg = 2;
		अन्यथा अगर ((buf[0] & 0xc0) == 0x80)
			reg = 4;
		अन्यथा अगर ((buf[0] & 0xf0) == 0xc0)
			reg = 6;
		अन्यथा अगर ((buf[0] & 0xf0) == 0xd0)
			reg = 8;
		अन्यथा अगर ((buf[0] & 0xf0) == 0xe0)
			reg = 10;
		अन्यथा अगर ((buf[0] & 0xf0) == 0xf0)
			reg = 12;

		deb_i2c("W(%d):", reg);
		अणु
			पूर्णांक i;
			क्रम (i = 0; i < count; i++)
				prपूर्णांकk(KERN_CONT " %02x", buf[i]);
			prपूर्णांकk(KERN_CONT "\n");
		पूर्ण
	पूर्ण

	ret = i2c_transfer(state->i2c, msg, 1);
	अगर (ret != 1) अणु
		prपूर्णांकk(KERN_ERR "%s: i2c error, ret=%d\n", __func__, ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम zl10036_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10036_state *state = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(state);
पूर्ण

अटल पूर्णांक zl10036_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10036_state *state = fe->tuner_priv;
	u8 buf[] = अणु 0xf0, 0x80 पूर्ण; /* regs 12/13 */
	पूर्णांक ret;

	deb_info("%s\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	ret = zl10036_ग_लिखो(state, buf, माप(buf));

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस ret;
पूर्ण

/*
 * रेजिस्टर map of the ZL10036/ZL10038
 *
 * reg[शेष] content
 *  2[0x00]:   0 | N14 | N13 | N12 | N11 | N10 |  N9 |  N8
 *  3[0x00]:  N7 |  N6 |  N5 |  N4 |  N3 |  N2 |  N1 |  N0
 *  4[0x80]:   1 |   0 | RFG | BA1 | BA0 | BG1 | BG0 | LEN
 *  5[0x00]:  P0 |  C1 |  C0 |  R4 |  R3 |  R2 |  R1 |  R0
 *  6[0xc0]:   1 |   1 |   0 |   0 | RSD |   0 |   0 |   0
 *  7[0x20]:  P1 | BF6 | BF5 | BF4 | BF3 | BF2 | BF1 |   0
 *  8[0xdb]:   1 |   1 |   0 |   1 |   0 |  CC |   1 |   1
 *  9[0x30]: VSD |  V2 |  V1 |  V0 |  S3 |  S2 |  S1 |  S0
 * 10[0xe1]:   1 |   1 |   1 |   0 |   0 | LS2 | LS1 | LS0
 * 11[0xf5]:  WS | WH2 | WH1 | WH0 | WL2 | WL1 | WL0 | WRE
 * 12[0xf0]:   1 |   1 |   1 |   1 |   0 |   0 |   0 |   0
 * 13[0x28]:  PD | BR4 | BR3 | BR2 | BR1 | BR0 | CLR |  TL
 */

अटल पूर्णांक zl10036_set_frequency(काष्ठा zl10036_state *state, u32 frequency)
अणु
	u8 buf[2];
	u32 भाग, foffset;

	भाग = (frequency + _FR/2) / _FR;
	state->frequency = भाग * _FR;

	foffset = frequency - state->frequency;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = (भाग >> 0) & 0xff;

	deb_info("%s: ftodo=%u fpriv=%u ferr=%d div=%u\n", __func__,
		frequency, state->frequency, foffset, भाग);

	वापस zl10036_ग_लिखो(state, buf, माप(buf));
पूर्ण

अटल पूर्णांक zl10036_set_bandwidth(काष्ठा zl10036_state *state, u32 fbw)
अणु
	/* fbw is measured in kHz */
	u8 br, bf;
	पूर्णांक ret;
	u8 buf_bf[] = अणु
		0xc0, 0x00, /*   6/7: rsd=0 bf=0 */
	पूर्ण;
	u8 buf_br[] = अणु
		0xf0, 0x00, /* 12/13: br=0xa clr=0 tl=0*/
	पूर्ण;
	u8 zl10036_rsd_off[] = अणु 0xc8 पूर्ण; /* set RSD=1 */

	/* ensure correct values */
	अगर (fbw > 35000)
		fbw = 35000;
	अगर (fbw <  8000)
		fbw =  8000;

#घोषणा _BR_MAXIMUM (_XTAL/575) /* _XTAL / 575kHz = 17 */

	/* <= 28,82 MHz */
	अगर (fbw <= 28820) अणु
		br = _BR_MAXIMUM;
	पूर्ण अन्यथा अणु
		/*
		 *  f(bw)=34,6MHz f(xtal)=10.111MHz
		 *  br = (10111/34600) * 63 * 1/K = 14;
		 */
		br = ((_XTAL * 21 * 1000) / (fbw * 419));
	पूर्ण

	/* ensure correct values */
	अगर (br < 4)
		br = 4;
	अगर (br > _BR_MAXIMUM)
		br = _BR_MAXIMUM;

	/*
	 * k = 1.257
	 * bf = fbw/_XTAL * br * k - 1 */

	bf = (fbw * br * 1257) / (_XTAL * 1000) - 1;

	/* ensure correct values */
	अगर (bf > 62)
		bf = 62;

	buf_bf[1] = (bf << 1) & 0x7e;
	buf_br[1] = (br << 2) & 0x7c;
	deb_info("%s: BW=%d br=%u bf=%u\n", __func__, fbw, br, bf);

	अगर (br != state->br) अणु
		ret = zl10036_ग_लिखो(state, buf_br, माप(buf_br));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (bf != state->bf) अणु
		ret = zl10036_ग_लिखो(state, buf_bf, माप(buf_bf));
		अगर (ret < 0)
			वापस ret;

		/* समय = br/(32* fxtal) */
		/* minimal sleep समय to be calculated
		 * maximum br is 63 -> max समय = 2 /10 MHz = 2e-7 */
		msleep(1);

		ret = zl10036_ग_लिखो(state, zl10036_rsd_off,
			माप(zl10036_rsd_off));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	state->br = br;
	state->bf = bf;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10036_set_gain_params(काष्ठा zl10036_state *state,
	पूर्णांक c)
अणु
	u8 buf[2];
	u8 rfg, ba, bg;

	/* शेष values */
	rfg = 0; /* enable when using an lna */
	ba = 1;
	bg = 1;

	/* reg 4 */
	buf[0] = 0x80 | ((rfg << 5) & 0x20)
		| ((ba  << 3) & 0x18) | ((bg  << 1) & 0x06);

	अगर (!state->config->rf_loop_enable)
		buf[0] |= 0x01;

	/* P0=0 */
	buf[1] = _RDIV_REG | ((c << 5) & 0x60);

	deb_info("%s: c=%u rfg=%u ba=%u bg=%u\n", __func__, c, rfg, ba, bg);
	वापस zl10036_ग_लिखो(state, buf, माप(buf));
पूर्ण

अटल पूर्णांक zl10036_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा zl10036_state *state = fe->tuner_priv;
	पूर्णांक ret = 0;
	u32 frequency = p->frequency;
	u32 fbw;
	पूर्णांक i;
	u8 c;

	/* ensure correct values
	 * maybe redundant as core alपढ़ोy checks this */
	अगर ((frequency < fe->ops.info.frequency_min_hz / kHz)
	||  (frequency > fe->ops.info.frequency_max_hz / kHz))
		वापस -EINVAL;

	/*
	 * alpha = 1.35 क्रम dvb-s
	 * fBW = (alpha*symbolrate)/(2*0.8)
	 * 1.35 / (2*0.8) = 27 / 32
	 */
	fbw = (27 * p->symbol_rate) / 32;

	/* scale to kHz */
	fbw /= 1000;

	/* Add safe margin of 3MHz */
	fbw += 3000;

	/* setting the अक्षरge pump - guessed values */
	अगर (frequency < 950000)
		वापस -EINVAL;
	अन्यथा अगर (frequency < 1250000)
		c = 0;
	अन्यथा अगर (frequency < 1750000)
		c = 1;
	अन्यथा अगर (frequency < 2175000)
		c = 2;
	अन्यथा
		वापस -EINVAL;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	ret = zl10036_set_gain_params(state, c);
	अगर (ret < 0)
		जाओ error;

	ret = zl10036_set_frequency(state, p->frequency);
	अगर (ret < 0)
		जाओ error;

	ret = zl10036_set_bandwidth(state, fbw);
	अगर (ret < 0)
		जाओ error;

	/* रुको क्रम tuner lock - no idea अगर this is really needed */
	क्रम (i = 0; i < 20; i++) अणु
		ret = zl10036_पढ़ो_status_reg(state);
		अगर (ret < 0)
			जाओ error;

		/* check Frequency & Phase Lock Bit */
		अगर (ret & STATUS_FL)
			अवरोध;

		msleep(10);
	पूर्ण

error:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस ret;
पूर्ण

अटल पूर्णांक zl10036_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा zl10036_state *state = fe->tuner_priv;

	*frequency = state->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10036_init_regs(काष्ठा zl10036_state *state)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	/* could also be one block from reg 2 to 13 and additional 10/11 */
	u8 zl10036_init_tab[][2] = अणु
		अणु 0x04, 0x00 पूर्ण,		/*   2/3: भाग=0x400 - arbitrary value */
		अणु 0x8b, _RDIV_REG पूर्ण,	/*   4/5: rfg=0 ba=1 bg=1 len=? */
					/*        p0=0 c=0 r=_RDIV_REG */
		अणु 0xc0, 0x20 पूर्ण,		/*   6/7: rsd=0 bf=0x10 */
		अणु 0xd3, 0x40 पूर्ण,		/*   8/9: from datasheet */
		अणु 0xe3, 0x5b पूर्ण,		/* 10/11: lock winकरोw level */
		अणु 0xf0, 0x28 पूर्ण,		/* 12/13: br=0xa clr=0 tl=0*/
		अणु 0xe3, 0xf9 पूर्ण,		/* 10/11: unlock winकरोw level */
	पूर्ण;

	/* invalid values to trigger writing */
	state->br = 0xff;
	state->bf = 0xff;

	अगर (!state->config->rf_loop_enable)
		zl10036_init_tab[1][0] |= 0x01;

	deb_info("%s\n", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(zl10036_init_tab); i++) अणु
		ret = zl10036_ग_लिखो(state, zl10036_init_tab[i], 2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zl10036_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10036_state *state = fe->tuner_priv;
	पूर्णांक ret = 0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	ret = zl10036_पढ़ो_status_reg(state);
	अगर (ret < 0)
		वापस ret;

	/* Only init अगर Power-on-Reset bit is set? */
	ret = zl10036_init_regs(state);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops zl10036_tuner_ops = अणु
	.info = अणु
		.name = "Zarlink ZL10036",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2175 * MHz
	पूर्ण,
	.init = zl10036_init,
	.release = zl10036_release,
	.sleep = zl10036_sleep,
	.set_params = zl10036_set_params,
	.get_frequency = zl10036_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *zl10036_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा zl10036_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा zl10036_state *state;
	पूर्णांक ret;

	अगर (!config) अणु
		prपूर्णांकk(KERN_ERR "%s: no config specified", __func__);
		वापस शून्य;
	पूर्ण

	state = kzalloc(माप(काष्ठा zl10036_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->config = config;
	state->i2c = i2c;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* खोलो i2c_gate */

	ret = zl10036_पढ़ो_status_reg(state);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: No zl10036 found\n", __func__);
		जाओ error;
	पूर्ण

	ret = zl10036_init_regs(state);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: tuner initialization failed\n",
			__func__);
		जाओ error;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* बंद i2c_gate */

	fe->tuner_priv = state;

	स_नकल(&fe->ops.tuner_ops, &zl10036_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));
	prपूर्णांकk(KERN_INFO "%s: tuner initialization (%s addr=0x%02x) ok\n",
		__func__, fe->ops.tuner_ops.info.name, config->tuner_address);

	वापस fe;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(zl10036_attach);

module_param_named(debug, zl10036_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");
MODULE_DESCRIPTION("DVB ZL10036 driver");
MODULE_AUTHOR("Tino Reichardt");
MODULE_AUTHOR("Matthias Schwarzott");
MODULE_LICENSE("GPL");
