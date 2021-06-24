<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Conexant CX24113/CX24128 Tuner (Satellite)
 *
 *  Copyright (C) 2007-8 Patrick Boettcher <pb@linuxtv.org>
 *
 *  Developed क्रम BBTI / Technisat
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <media/dvb_frontend.h>
#समावेश "cx24113.h"

अटल पूर्णांक debug;

#घोषणा cx_info(args...) करो अणु prपूर्णांकk(KERN_INFO "CX24113: " args); पूर्ण जबतक (0)
#घोषणा cx_err(args...)  करो अणु prपूर्णांकk(KERN_ERR  "CX24113: " args); पूर्ण जबतक (0)

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) अणु \
			prपूर्णांकk(KERN_DEBUG "CX24113: %s: ", __func__); \
			prपूर्णांकk(args); \
		पूर्ण \
	पूर्ण जबतक (0)

काष्ठा cx24113_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा cx24113_config *config;

#घोषणा REV_CX24113 0x23
	u8 rev;
	u8 ver;

	u8 icp_mode:1;

#घोषणा ICP_LEVEL1 0
#घोषणा ICP_LEVEL2 1
#घोषणा ICP_LEVEL3 2
#घोषणा ICP_LEVEL4 3
	u8 icp_man:2;
	u8 icp_स्वतः_low:2;
	u8 icp_स्वतः_mlow:2;
	u8 icp_स्वतः_mhi:2;
	u8 icp_स्वतः_hi:2;
	u8 icp_dig;

#घोषणा LNA_MIN_GAIN 0
#घोषणा LNA_MID_GAIN 1
#घोषणा LNA_MAX_GAIN 2
	u8 lna_gain:2;

	u8 acp_on:1;

	u8 vco_mode:2;
	u8 vco_shअगरt:1;
#घोषणा VCOBANDSEL_6 0x80
#घोषणा VCOBANDSEL_5 0x01
#घोषणा VCOBANDSEL_4 0x02
#घोषणा VCOBANDSEL_3 0x04
#घोषणा VCOBANDSEL_2 0x08
#घोषणा VCOBANDSEL_1 0x10
	u8 vco_band;

#घोषणा VCODIV4 4
#घोषणा VCODIV2 2
	u8 vcoभाग;

	u8 bs_delay:4;
	u16 bs_freqcnt:13;
	u16 bs_rभाग;
	u8 prescaler_mode:1;

	u8 rfvga_bias_ctrl;

	s16 tuner_gain_thres;
	u8  gain_level;

	u32 frequency;

	u8 refभाग;

	u8 Fwinकरोw_enabled;
पूर्ण;

अटल पूर्णांक cx24113_ग_लिखोreg(काष्ठा cx24113_state *state, पूर्णांक reg, पूर्णांक data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->i2c_addr,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		prपूर्णांकk(KERN_DEBUG "%s: writereg error(err == %i, reg == 0x%02x, data == 0x%02x)\n",
		       __func__, err, reg, data);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24113_पढ़ोreg(काष्ठा cx24113_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config->i2c_addr,
			.flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->config->i2c_addr,
			.flags = I2C_M_RD, .buf = &b, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		prपूर्णांकk(KERN_DEBUG "%s: reg=0x%x (error=%d)\n",
			__func__, reg, ret);
		वापस ret;
	पूर्ण

	वापस b;
पूर्ण

अटल व्योम cx24113_set_parameters(काष्ठा cx24113_state *state)
अणु
	u8 r;

	r = cx24113_पढ़ोreg(state, 0x10) & 0x82;
	r |= state->icp_mode;
	r |= state->icp_man << 4;
	r |= state->icp_dig << 2;
	r |= state->prescaler_mode << 5;
	cx24113_ग_लिखोreg(state, 0x10, r);

	r = (state->icp_स्वतः_low  << 0) | (state->icp_स्वतः_mlow << 2)
		| (state->icp_स्वतः_mhi << 4) | (state->icp_स्वतः_hi << 6);
	cx24113_ग_लिखोreg(state, 0x11, r);

	अगर (state->rev == REV_CX24113) अणु
		r = cx24113_पढ़ोreg(state, 0x20) & 0xec;
		r |= state->lna_gain;
		r |= state->rfvga_bias_ctrl << 4;
		cx24113_ग_लिखोreg(state, 0x20, r);
	पूर्ण

	r = cx24113_पढ़ोreg(state, 0x12) & 0x03;
	r |= state->acp_on << 2;
	r |= state->bs_delay << 4;
	cx24113_ग_लिखोreg(state, 0x12, r);

	r = cx24113_पढ़ोreg(state, 0x18) & 0x40;
	r |= state->vco_shअगरt;
	अगर (state->vco_band == VCOBANDSEL_6)
		r |= (1 << 7);
	अन्यथा
		r |= (state->vco_band << 1);
	cx24113_ग_लिखोreg(state, 0x18, r);

	r  = cx24113_पढ़ोreg(state, 0x14) & 0x20;
	r |= (state->vco_mode << 6) | ((state->bs_freqcnt >> 8) & 0x1f);
	cx24113_ग_लिखोreg(state, 0x14, r);
	cx24113_ग_लिखोreg(state, 0x15, (state->bs_freqcnt        & 0xff));

	cx24113_ग_लिखोreg(state, 0x16, (state->bs_rभाग >> 4) & 0xff);
	r = (cx24113_पढ़ोreg(state, 0x17) & 0x0f) |
		((state->bs_rभाग & 0x0f) << 4);
	cx24113_ग_लिखोreg(state, 0x17, r);
पूर्ण

#घोषणा VGA_0 0x00
#घोषणा VGA_1 0x04
#घोषणा VGA_2 0x02
#घोषणा VGA_3 0x06
#घोषणा VGA_4 0x01
#घोषणा VGA_5 0x05
#घोषणा VGA_6 0x03
#घोषणा VGA_7 0x07

#घोषणा RFVGA_0 0x00
#घोषणा RFVGA_1 0x01
#घोषणा RFVGA_2 0x02
#घोषणा RFVGA_3 0x03

अटल पूर्णांक cx24113_set_gain_settings(काष्ठा cx24113_state *state,
		s16 घातer_estimation)
अणु
	u8 ampout = cx24113_पढ़ोreg(state, 0x1d) & 0xf0,
	   vga    = cx24113_पढ़ोreg(state, 0x1f) & 0x3f,
	   rfvga  = cx24113_पढ़ोreg(state, 0x20) & 0xf3;
	u8 gain_level = घातer_estimation >= state->tuner_gain_thres;

	dprपूर्णांकk("power estimation: %d, thres: %d, gain_level: %d/%d\n",
			घातer_estimation, state->tuner_gain_thres,
			state->gain_level, gain_level);

	अगर (gain_level == state->gain_level)
		वापस 0; /* nothing to be करोne */

	ampout |= 0xf;

	अगर (gain_level) अणु
		rfvga |= RFVGA_0 << 2;
		vga   |= (VGA_7 << 3) | VGA_7;
	पूर्ण अन्यथा अणु
		rfvga |= RFVGA_2 << 2;
		vga  |= (VGA_6 << 3) | VGA_2;
	पूर्ण
	state->gain_level = gain_level;

	cx24113_ग_लिखोreg(state, 0x1d, ampout);
	cx24113_ग_लिखोreg(state, 0x1f, vga);
	cx24113_ग_लिखोreg(state, 0x20, rfvga);

	वापस 1; /* did something */
पूर्ण

अटल पूर्णांक cx24113_set_Fref(काष्ठा cx24113_state *state, u8 high)
अणु
	u8 xtal = cx24113_पढ़ोreg(state, 0x02);
	अगर (state->rev == 0x43 && state->vcoभाग == VCODIV4)
		high = 1;

	xtal &= ~0x2;
	अगर (high)
		xtal |= high << 1;
	वापस cx24113_ग_लिखोreg(state, 0x02, xtal);
पूर्ण

अटल पूर्णांक cx24113_enable(काष्ठा cx24113_state *state, u8 enable)
अणु
	u8 r21 = (cx24113_पढ़ोreg(state, 0x21) & 0xc0) | enable;
	अगर (state->rev == REV_CX24113)
		r21 |= (1 << 1);
	वापस cx24113_ग_लिखोreg(state, 0x21, r21);
पूर्ण

अटल पूर्णांक cx24113_set_bandwidth(काष्ठा cx24113_state *state, u32 bandwidth_khz)
अणु
	u8 r;

	अगर (bandwidth_khz <= 19000)
		r = 0x03 << 6;
	अन्यथा अगर (bandwidth_khz <= 25000)
		r = 0x02 << 6;
	अन्यथा
		r = 0x01 << 6;

	dprपूर्णांकk("bandwidth to be set: %d\n", bandwidth_khz);
	bandwidth_khz *= 10;
	bandwidth_khz -= 10000;
	bandwidth_khz /= 1000;
	bandwidth_khz += 5;
	bandwidth_khz /= 10;

	dprपूर्णांकk("bandwidth: %d %d\n", r >> 6, bandwidth_khz);

	r |= bandwidth_khz & 0x3f;

	वापस cx24113_ग_लिखोreg(state, 0x1e, r);
पूर्ण

अटल पूर्णांक cx24113_set_clk_inversion(काष्ठा cx24113_state *state, u8 on)
अणु
	u8 r = (cx24113_पढ़ोreg(state, 0x10) & 0x7f) | ((on & 0x1) << 7);
	वापस cx24113_ग_लिखोreg(state, 0x10, r);
पूर्ण

अटल पूर्णांक cx24113_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा cx24113_state *state = fe->tuner_priv;
	u8 r = (cx24113_पढ़ोreg(state, 0x10) & 0x02) >> 1;
	अगर (r)
		*status |= TUNER_STATUS_LOCKED;
	dprपूर्णांकk("PLL locked: %d\n", r);
	वापस 0;
पूर्ण

अटल u8 cx24113_set_ref_भाग(काष्ठा cx24113_state *state, u8 refभाग)
अणु
	अगर (state->rev == 0x43 && state->vcoभाग == VCODIV4)
		refभाग = 2;
	वापस state->refभाग = refभाग;
पूर्ण

अटल व्योम cx24113_calc_pll_nf(काष्ठा cx24113_state *state, u16 *n, s32 *f)
अणु
	s32 N;
	s64 F;
	u64 भागidend;
	u8 R, r;
	u8 vcoभाग;
	u8 factor;
	s32 freq_hz = state->frequency * 1000;

	अगर (state->config->xtal_khz < 20000)
		factor = 1;
	अन्यथा
		factor = 2;

	अगर (state->rev == REV_CX24113) अणु
		अगर (state->frequency >= 1100000)
			vcoभाग = VCODIV2;
		अन्यथा
			vcoभाग = VCODIV4;
	पूर्ण अन्यथा अणु
		अगर (state->frequency >= 1165000)
			vcoभाग = VCODIV2;
		अन्यथा
			vcoभाग = VCODIV4;
	पूर्ण
	state->vcoभाग = vcoभाग;

	dprपूर्णांकk("calculating N/F for %dHz with vcodiv %d\n", freq_hz, vcoभाग);
	R = 0;
	करो अणु
		R = cx24113_set_ref_भाग(state, R + 1);

		/* calculate tuner PLL settings: */
		N =  (freq_hz / 100 * vcoभाग) * R;
		N /= (state->config->xtal_khz) * factor * 2;
		N += 5;     /* For round up. */
		N /= 10;
		N -= 32;
	पूर्ण जबतक (N < 6 && R < 3);

	अगर (N < 6) अणु
		cx_err("strange frequency: N < 6\n");
		वापस;
	पूर्ण
	F = freq_hz;
	F *= (u64) (R * vcoभाग * 262144);
	dprपूर्णांकk("1 N: %d, F: %lld, R: %d\n", N, (दीर्घ दीर्घ)F, R);
	/* करो_भाग needs an u64 as first argument */
	भागidend = F;
	करो_भाग(भागidend, state->config->xtal_khz * 1000 * factor * 2);
	F = भागidend;
	dprपूर्णांकk("2 N: %d, F: %lld, R: %d\n", N, (दीर्घ दीर्घ)F, R);
	F -= (N + 32) * 262144;

	dprपूर्णांकk("3 N: %d, F: %lld, R: %d\n", N, (दीर्घ दीर्घ)F, R);

	अगर (state->Fwinकरोw_enabled) अणु
		अगर (F > (262144 / 2 - 1638))
			F = 262144 / 2 - 1638;
		अगर (F < (-262144 / 2 + 1638))
			F = -262144 / 2 + 1638;
		अगर ((F < 3277 && F > 0) || (F > -3277 && F < 0)) अणु
			F = 0;
			r = cx24113_पढ़ोreg(state, 0x10);
			cx24113_ग_लिखोreg(state, 0x10, r | (1 << 6));
		पूर्ण
	पूर्ण
	dprपूर्णांकk("4 N: %d, F: %lld, R: %d\n", N, (दीर्घ दीर्घ)F, R);

	*n = (u16) N;
	*f = (s32) F;
पूर्ण


अटल व्योम cx24113_set_nfr(काष्ठा cx24113_state *state, u16 n, s32 f, u8 r)
अणु
	u8 reg;
	cx24113_ग_लिखोreg(state, 0x19, (n >> 1) & 0xff);

	reg = ((n & 0x1) << 7) | ((f >> 11) & 0x7f);
	cx24113_ग_लिखोreg(state, 0x1a, reg);

	cx24113_ग_लिखोreg(state, 0x1b, (f >> 3) & 0xff);

	reg = cx24113_पढ़ोreg(state, 0x1c) & 0x1f;
	cx24113_ग_लिखोreg(state, 0x1c, reg | ((f & 0x7) << 5));

	cx24113_set_Fref(state, r - 1);
पूर्ण

अटल पूर्णांक cx24113_set_frequency(काष्ठा cx24113_state *state, u32 frequency)
अणु
	u8 r = 1; /* or 2 */
	u16 n = 6;
	s32 f = 0;

	r = cx24113_पढ़ोreg(state, 0x14);
	cx24113_ग_लिखोreg(state, 0x14, r & 0x3f);

	r = cx24113_पढ़ोreg(state, 0x10);
	cx24113_ग_लिखोreg(state, 0x10, r & 0xbf);

	state->frequency = frequency;

	dprपूर्णांकk("tuning to frequency: %d\n", frequency);

	cx24113_calc_pll_nf(state, &n, &f);
	cx24113_set_nfr(state, n, f, state->refभाग);

	r = cx24113_पढ़ोreg(state, 0x18) & 0xbf;
	अगर (state->vcoभाग != VCODIV2)
		r |= 1 << 6;
	cx24113_ग_लिखोreg(state, 0x18, r);

	/* The need क्रम this sleep is not clear. But helps in some हालs */
	msleep(5);

	r = cx24113_पढ़ोreg(state, 0x1c) & 0xef;
	cx24113_ग_लिखोreg(state, 0x1c, r | (1 << 4));
	वापस 0;
पूर्ण

अटल पूर्णांक cx24113_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24113_state *state = fe->tuner_priv;
	पूर्णांक ret;

	state->tuner_gain_thres = -50;
	state->gain_level = 255; /* to क्रमce a gain-setting initialization */
	state->icp_mode = 0;

	अगर (state->config->xtal_khz < 11000) अणु
		state->icp_स्वतः_hi  = ICP_LEVEL4;
		state->icp_स्वतः_mhi  = ICP_LEVEL4;
		state->icp_स्वतः_mlow = ICP_LEVEL3;
		state->icp_स्वतः_low = ICP_LEVEL3;
	पूर्ण अन्यथा अणु
		state->icp_स्वतः_hi  = ICP_LEVEL4;
		state->icp_स्वतः_mhi  = ICP_LEVEL4;
		state->icp_स्वतः_mlow = ICP_LEVEL3;
		state->icp_स्वतः_low = ICP_LEVEL2;
	पूर्ण

	state->icp_dig = ICP_LEVEL3;
	state->icp_man = ICP_LEVEL1;
	state->acp_on  = 1;
	state->vco_mode = 0;
	state->vco_shअगरt = 0;
	state->vco_band = VCOBANDSEL_1;
	state->bs_delay = 8;
	state->bs_freqcnt = 0x0fff;
	state->bs_rभाग = 0x0fff;
	state->prescaler_mode = 0;
	state->lna_gain = LNA_MAX_GAIN;
	state->rfvga_bias_ctrl = 1;
	state->Fwinकरोw_enabled = 1;

	cx24113_set_Fref(state, 0);
	cx24113_enable(state, 0x3d);
	cx24113_set_parameters(state);

	cx24113_set_gain_settings(state, -30);

	cx24113_set_bandwidth(state, 18025);
	cx24113_set_clk_inversion(state, 1);

	अगर (state->config->xtal_khz >= 40000)
		ret = cx24113_ग_लिखोreg(state, 0x02,
			(cx24113_पढ़ोreg(state, 0x02) & 0xfb) | (1 << 2));
	अन्यथा
		ret = cx24113_ग_लिखोreg(state, 0x02,
			(cx24113_पढ़ोreg(state, 0x02) & 0xfb) | (0 << 2));

	वापस ret;
पूर्ण

अटल पूर्णांक cx24113_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24113_state *state = fe->tuner_priv;
	/* क्रम a ROLL-OFF factor of 0.35, 0.2: 600, 0.25: 625 */
	u32 roll_off = 675;
	u32 bw;

	bw  = ((c->symbol_rate/100) * roll_off) / 1000;
	bw += (10000000/100) + 5;
	bw /= 10;
	bw += 1000;
	cx24113_set_bandwidth(state, bw);

	cx24113_set_frequency(state, c->frequency);
	msleep(5);
	वापस cx24113_get_status(fe, &bw);
पूर्ण

अटल s8 cx24113_agc_table[2][10] = अणु
	अणु-54, -41, -35, -30, -25, -21, -16, -10,  -6,  -2पूर्ण,
	अणु-39, -35, -30, -25, -19, -15, -11,  -5,   1,   9पूर्ण,
पूर्ण;

व्योम cx24113_agc_callback(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24113_state *state = fe->tuner_priv;
	s16 s, i;
	अगर (!fe->ops.पढ़ो_संकेत_strength)
		वापस;

	करो अणु
		/* this only works with the current CX24123 implementation */
		fe->ops.पढ़ो_संकेत_strength(fe, (u16 *) &s);
		s >>= 8;
		dprपूर्णांकk("signal strength: %d\n", s);
		क्रम (i = 0; i < माप(cx24113_agc_table[0]); i++)
			अगर (cx24113_agc_table[state->gain_level][i] > s)
				अवरोध;
		s = -25 - i*5;
	पूर्ण जबतक (cx24113_set_gain_settings(state, s));
पूर्ण
EXPORT_SYMBOL(cx24113_agc_callback);

अटल पूर्णांक cx24113_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा cx24113_state *state = fe->tuner_priv;
	*frequency = state->frequency;
	वापस 0;
पूर्ण

अटल व्योम cx24113_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24113_state *state = fe->tuner_priv;
	dprपूर्णांकk("\n");
	fe->tuner_priv = शून्य;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops cx24113_tuner_ops = अणु
	.info = अणु
		.name              = "Conexant CX24113",
		.frequency_min_hz  =  950 * MHz,
		.frequency_max_hz  = 2150 * MHz,
		.frequency_step_hz =  125 * kHz,
	पूर्ण,

	.release       = cx24113_release,

	.init          = cx24113_init,

	.set_params    = cx24113_set_params,
	.get_frequency = cx24113_get_frequency,
	.get_status    = cx24113_get_status,
पूर्ण;

काष्ठा dvb_frontend *cx24113_attach(काष्ठा dvb_frontend *fe,
		स्थिर काष्ठा cx24113_config *config, काष्ठा i2c_adapter *i2c)
अणु
	/* allocate memory क्रम the पूर्णांकernal state */
	काष्ठा cx24113_state *state = kzalloc(माप(*state), GFP_KERNEL);
	पूर्णांक rc;

	अगर (!state)
		वापस शून्य;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	cx_info("trying to detect myself\n");

	/* making a dummy पढ़ो, because of some expected troubles
	 * after घातer on */
	cx24113_पढ़ोreg(state, 0x00);

	rc = cx24113_पढ़ोreg(state, 0x00);
	अगर (rc < 0) अणु
		cx_info("CX24113 not found.\n");
		जाओ error;
	पूर्ण
	state->rev = rc;

	चयन (rc) अणु
	हाल 0x43:
		cx_info("detected CX24113 variant\n");
		अवरोध;
	हाल REV_CX24113:
		cx_info("successfully detected\n");
		अवरोध;
	शेष:
		cx_err("unsupported device id: %x\n", state->rev);
		जाओ error;
	पूर्ण
	state->ver = cx24113_पढ़ोreg(state, 0x01);
	cx_info("version: %x\n", state->ver);

	/* create dvb_frontend */
	स_नकल(&fe->ops.tuner_ops, &cx24113_tuner_ops,
			माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = state;
	वापस fe;

error:
	kमुक्त(state);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(cx24113_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activates frontend debugging (default:0)");

MODULE_AUTHOR("Patrick Boettcher <pb@linuxtv.org>");
MODULE_DESCRIPTION("DVB Frontend module for Conexant CX24113/CX24128hardware");
MODULE_LICENSE("GPL");

