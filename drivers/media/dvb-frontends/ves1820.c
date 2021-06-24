<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    VES1820  - Single Chip Cable Channel Receiver driver module

    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>

*/

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "ves1820.h"



काष्ठा ves1820_state अणु
	काष्ठा i2c_adapter* i2c;
	/* configuration settings */
	स्थिर काष्ठा ves1820_config* config;
	काष्ठा dvb_frontend frontend;

	/* निजी demodulator data */
	u8 reg0;
	u8 pwm;
पूर्ण;


अटल पूर्णांक verbose;

अटल u8 ves1820_inittab[] = अणु
	0x69, 0x6A, 0x93, 0x1A, 0x12, 0x46, 0x26, 0x1A,
	0x43, 0x6A, 0xAA, 0xAA, 0x1E, 0x85, 0x43, 0x20,
	0xE0, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x40
पूर्ण;

अटल पूर्णांक ves1820_ग_लिखोreg(काष्ठा ves1820_state *state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु 0x00, reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = state->config->demod_address,.flags = 0,.buf = buf,.len = 3 पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk("ves1820: %s(): writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
		       __func__, reg, data, ret);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल u8 ves1820_पढ़ोreg(काष्ठा ves1820_state *state, u8 reg)
अणु
	u8 b0[] = अणु 0x00, reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु.addr = state->config->demod_address,.flags = 0,.buf = b0,.len = 2पूर्ण,
		अणु.addr = state->config->demod_address,.flags = I2C_M_RD,.buf = b1,.len = 1पूर्ण
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		prपूर्णांकk("ves1820: %s(): readreg error (reg == 0x%02x, ret == %i)\n",
		       __func__, reg, ret);

	वापस b1[0];
पूर्ण

अटल पूर्णांक ves1820_setup_reg0(काष्ठा ves1820_state *state,
			      u8 reg0, क्रमागत fe_spectral_inversion inversion)
अणु
	reg0 |= state->reg0 & 0x62;

	अगर (INVERSION_ON == inversion) अणु
		अगर (!state->config->invert) reg0 |= 0x20;
		अन्यथा reg0 &= ~0x20;
	पूर्ण अन्यथा अगर (INVERSION_OFF == inversion) अणु
		अगर (!state->config->invert) reg0 &= ~0x20;
		अन्यथा reg0 |= 0x20;
	पूर्ण

	ves1820_ग_लिखोreg(state, 0x00, reg0 & 0xfe);
	ves1820_ग_लिखोreg(state, 0x00, reg0 | 0x01);

	state->reg0 = reg0;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_set_symbolrate(काष्ठा ves1820_state *state, u32 symbolrate)
अणु
	s32 BDR;
	s32 BDRI;
	s16 SFIL = 0;
	u16 NDEC = 0;
	u32 ratio;
	u32 fin;
	u32 पंचांगp;
	u64 fpपंचांगp;
	u64 fpxin;

	अगर (symbolrate > state->config->xin / 2)
		symbolrate = state->config->xin / 2;

	अगर (symbolrate < 500000)
		symbolrate = 500000;

	अगर (symbolrate < state->config->xin / 16)
		NDEC = 1;
	अगर (symbolrate < state->config->xin / 32)
		NDEC = 2;
	अगर (symbolrate < state->config->xin / 64)
		NDEC = 3;

	/* yeuch! */
	fpxin = state->config->xin * 10ULL;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 123);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 1;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 160);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 0;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 246);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 1;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 320);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 0;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 492);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 1;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 640);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 0;
	fpपंचांगp = fpxin; करो_भाग(fpपंचांगp, 984);
	अगर (symbolrate < fpपंचांगp)
		SFIL = 1;

	fin = state->config->xin >> 4;
	symbolrate <<= NDEC;
	ratio = (symbolrate << 4) / fin;
	पंचांगp = ((symbolrate << 4) % fin) << 8;
	ratio = (ratio << 8) + पंचांगp / fin;
	पंचांगp = (पंचांगp % fin) << 8;
	ratio = (ratio << 8) + DIV_ROUND_CLOSEST(पंचांगp, fin);

	BDR = ratio;
	BDRI = (((state->config->xin << 5) / symbolrate) + 1) / 2;

	अगर (BDRI > 0xFF)
		BDRI = 0xFF;

	SFIL = (SFIL << 4) | ves1820_inittab[0x0E];

	NDEC = (NDEC << 6) | ves1820_inittab[0x03];

	ves1820_ग_लिखोreg(state, 0x03, NDEC);
	ves1820_ग_लिखोreg(state, 0x0a, BDR & 0xff);
	ves1820_ग_लिखोreg(state, 0x0b, (BDR >> 8) & 0xff);
	ves1820_ग_लिखोreg(state, 0x0c, (BDR >> 16) & 0x3f);

	ves1820_ग_लिखोreg(state, 0x0d, BDRI);
	ves1820_ग_लिखोreg(state, 0x0e, SFIL);

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;
	पूर्णांक i;

	ves1820_ग_लिखोreg(state, 0, 0);

	क्रम (i = 0; i < माप(ves1820_inittab); i++)
		ves1820_ग_लिखोreg(state, i, ves1820_inittab[i]);
	अगर (state->config->selagc)
		ves1820_ग_लिखोreg(state, 2, ves1820_inittab[2] | 0x08);

	ves1820_ग_लिखोreg(state, 0x34, state->pwm);

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ves1820_state* state = fe->demodulator_priv;
	अटल स्थिर u8 reg0x00[] = अणु 0x00, 0x04, 0x08, 0x0c, 0x10 पूर्ण;
	अटल स्थिर u8 reg0x01[] = अणु 140, 140, 106, 100, 92 पूर्ण;
	अटल स्थिर u8 reg0x05[] = अणु 135, 100, 70, 54, 38 पूर्ण;
	अटल स्थिर u8 reg0x08[] = अणु 162, 116, 67, 52, 35 पूर्ण;
	अटल स्थिर u8 reg0x09[] = अणु 145, 150, 106, 126, 107 पूर्ण;
	पूर्णांक real_qam = p->modulation - QAM_16;

	अगर (real_qam < 0 || real_qam > 4)
		वापस -EINVAL;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	ves1820_set_symbolrate(state, p->symbol_rate);
	ves1820_ग_लिखोreg(state, 0x34, state->pwm);

	ves1820_ग_लिखोreg(state, 0x01, reg0x01[real_qam]);
	ves1820_ग_लिखोreg(state, 0x05, reg0x05[real_qam]);
	ves1820_ग_लिखोreg(state, 0x08, reg0x08[real_qam]);
	ves1820_ग_लिखोreg(state, 0x09, reg0x09[real_qam]);

	ves1820_setup_reg0(state, reg0x00[real_qam], p->inversion);
	ves1820_ग_लिखोreg(state, 2, ves1820_inittab[2] | (state->config->selagc ? 0x08 : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;
	पूर्णांक sync;

	*status = 0;
	sync = ves1820_पढ़ोreg(state, 0x11);

	अगर (sync & 1)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 2)
		*status |= FE_HAS_CARRIER;

	अगर (sync & 2)	/* XXX FIXME! */
		*status |= FE_HAS_VITERBI;

	अगर (sync & 4)
		*status |= FE_HAS_SYNC;

	अगर (sync & 8)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;

	u32 _ber = ves1820_पढ़ोreg(state, 0x14) |
			(ves1820_पढ़ोreg(state, 0x15) << 8) |
			((ves1820_पढ़ोreg(state, 0x16) & 0x0f) << 16);
	*ber = 10 * _ber;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;

	u8 gain = ves1820_पढ़ोreg(state, 0x17);
	*strength = (gain << 8) | gain;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;

	u8 quality = ~ves1820_पढ़ोreg(state, 0x18);
	*snr = (quality << 8) | quality;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;

	*ucblocks = ves1820_पढ़ोreg(state, 0x13) & 0x7f;
	अगर (*ucblocks == 0x7f)
		*ucblocks = 0xffffffff;

	/* reset uncorrected block counter */
	ves1820_ग_लिखोreg(state, 0x10, ves1820_inittab[0x10] & 0xdf);
	ves1820_ग_लिखोreg(state, 0x10, ves1820_inittab[0x10]);

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;
	पूर्णांक sync;
	s8 afc = 0;

	sync = ves1820_पढ़ोreg(state, 0x11);
	afc = ves1820_पढ़ोreg(state, 0x19);
	अगर (verbose) अणु
		/* AFC only valid when carrier has been recovered */
		prपूर्णांकk(sync & 2 ? "ves1820: AFC (%d) %dHz\n" :
			"ves1820: [AFC (%d) %dHz]\n", afc, -((s32) p->symbol_rate * afc) >> 10);
	पूर्ण

	अगर (!state->config->invert) अणु
		p->inversion = (state->reg0 & 0x20) ? INVERSION_ON : INVERSION_OFF;
	पूर्ण अन्यथा अणु
		p->inversion = (!(state->reg0 & 0x20)) ? INVERSION_ON : INVERSION_OFF;
	पूर्ण

	p->modulation = ((state->reg0 >> 2) & 7) + QAM_16;

	p->fec_inner = FEC_NONE;

	p->frequency = ((p->frequency + 31250) / 62500) * 62500;
	अगर (sync & 2)
		p->frequency -= ((s32) p->symbol_rate * afc) >> 10;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;

	ves1820_ग_लिखोreg(state, 0x1b, 0x02);	/* pकरोwn ADC */
	ves1820_ग_लिखोreg(state, 0x00, 0x80);	/* standby */

	वापस 0;
पूर्ण

अटल पूर्णांक ves1820_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु

	fesettings->min_delay_ms = 200;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम ves1820_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ves1820_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ves1820_ops;

काष्ठा dvb_frontend* ves1820_attach(स्थिर काष्ठा ves1820_config* config,
				    काष्ठा i2c_adapter* i2c,
				    u8 pwm)
अणु
	काष्ठा ves1820_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा ves1820_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->reg0 = ves1820_inittab[0];
	state->config = config;
	state->i2c = i2c;
	state->pwm = pwm;

	/* check अगर the demod is there */
	अगर ((ves1820_पढ़ोreg(state, 0x1a) & 0xf0) != 0x70)
		जाओ error;

	अगर (verbose)
		prपूर्णांकk("ves1820: pwm=0x%02x\n", state->pwm);

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &ves1820_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.ops.info.symbol_rate_min = (state->config->xin / 2) / 64;      /* SACLK/64 == (XIN/2)/64 */
	state->frontend.ops.info.symbol_rate_max = (state->config->xin / 2) / 4;       /* SACLK/4 */
	state->frontend.demodulator_priv = state;

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ves1820_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A पूर्ण,
	.info = अणु
		.name = "VLSI VES1820 DVB-C",
		.frequency_min_hz =  47 * MHz,
		.frequency_max_hz = 862 * MHz,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO
	पूर्ण,

	.release = ves1820_release,

	.init = ves1820_init,
	.sleep = ves1820_sleep,

	.set_frontend = ves1820_set_parameters,
	.get_frontend = ves1820_get_frontend,
	.get_tune_settings = ves1820_get_tune_settings,

	.पढ़ो_status = ves1820_पढ़ो_status,
	.पढ़ो_ber = ves1820_पढ़ो_ber,
	.पढ़ो_संकेत_strength = ves1820_पढ़ो_संकेत_strength,
	.पढ़ो_snr = ves1820_पढ़ो_snr,
	.पढ़ो_ucblocks = ves1820_पढ़ो_ucblocks,
पूर्ण;

module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "print AFC offset after tuning for debugging the PWM setting");

MODULE_DESCRIPTION("VLSI VES1820 DVB-C Demodulator driver");
MODULE_AUTHOR("Ralph Metzler, Holger Waechtler");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(ves1820_attach);
