<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    TDA10021  - Single Chip Cable Channel Receiver driver module
	       used on the Siemens DVB-C cards

    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>
    Copyright (C) 2004 Markus Schulz <msc@antzप्रणाली.de>
		   Support क्रम TDA10021

*/

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda1002x.h"


काष्ठा tda10021_state अणु
	काष्ठा i2c_adapter* i2c;
	/* configuration settings */
	स्थिर काष्ठा tda1002x_config* config;
	काष्ठा dvb_frontend frontend;

	u8 pwm;
	u8 reg0;
पूर्ण;


#अगर 0
#घोषणा dprपूर्णांकk(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा dprपूर्णांकk(x...)
#पूर्ण_अगर

अटल पूर्णांक verbose;

#घोषणा XIN 57840000UL

#घोषणा FIN (XIN >> 4)

अटल पूर्णांक tda10021_inittab_size = 0x40;
अटल u8 tda10021_inittab[0x40]=
अणु
	0x73, 0x6a, 0x23, 0x0a, 0x02, 0x37, 0x77, 0x1a,
	0x37, 0x6a, 0x17, 0x8a, 0x1e, 0x86, 0x43, 0x40,
	0xb8, 0x3f, 0xa1, 0x00, 0xcd, 0x01, 0x00, 0xff,
	0x11, 0x00, 0x7c, 0x31, 0x30, 0x20, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x33, 0x11, 0x0d, 0x95, 0x08, 0x58,
	0x00, 0x00, 0x80, 0x00, 0x80, 0xff, 0x00, 0x00,
	0x04, 0x2d, 0x2f, 0xff, 0x00, 0x00, 0x00, 0x00,
पूर्ण;

अटल पूर्णांक _tda10021_ग_लिखोreg (काष्ठा tda10021_state* state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer (state->i2c, &msg, 1);
	अगर (ret != 1)
		prपूर्णांकk("DVB: TDA10021(%d): %s, writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			state->frontend.dvb->num, __func__, reg, data, ret);

	msleep(10);
	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल u8 tda10021_पढ़ोreg (काष्ठा tda10021_state* state, u8 reg)
अणु
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
				  अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer (state->i2c, msg, 2);
	// Don't prपूर्णांक an error message अगर the id is पढ़ो.
	अगर (ret != 2 && reg != 0x1a)
		prपूर्णांकk("DVB: TDA10021: %s: readreg error (ret == %i)\n",
				__func__, ret);
	वापस b1[0];
पूर्ण

//get access to tuner
अटल पूर्णांक lock_tuner(काष्ठा tda10021_state* state)
अणु
	u8 buf[2] = अणु 0x0f, tda10021_inittab[0x0f] | 0x80 पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr=state->config->demod_address, .flags=0, .buf=buf, .len=2पूर्ण;

	अगर(i2c_transfer(state->i2c, &msg, 1) != 1)
	अणु
		prपूर्णांकk("tda10021: lock tuner fails\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

//release access from tuner
अटल पूर्णांक unlock_tuner(काष्ठा tda10021_state* state)
अणु
	u8 buf[2] = अणु 0x0f, tda10021_inittab[0x0f] & 0x7f पूर्ण;
	काष्ठा i2c_msg msg_post=अणु.addr=state->config->demod_address, .flags=0, .buf=buf, .len=2पूर्ण;

	अगर(i2c_transfer(state->i2c, &msg_post, 1) != 1)
	अणु
		prपूर्णांकk("tda10021: unlock tuner fails\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_setup_reg0(काष्ठा tda10021_state *state, u8 reg0,
			       क्रमागत fe_spectral_inversion inversion)
अणु
	reg0 |= state->reg0 & 0x63;

	अगर ((INVERSION_ON == inversion) ^ (state->config->invert == 0))
		reg0 &= ~0x20;
	अन्यथा
		reg0 |= 0x20;

	_tda10021_ग_लिखोreg (state, 0x00, reg0 & 0xfe);
	_tda10021_ग_लिखोreg (state, 0x00, reg0 | 0x01);

	state->reg0 = reg0;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_set_symbolrate (काष्ठा tda10021_state* state, u32 symbolrate)
अणु
	s32 BDR;
	s32 BDRI;
	s16 SFIL = 0;
	u16 NDEC = 0;
	u32 पंचांगp, ratio;

	अगर (symbolrate > XIN / 2)
		symbolrate = XIN / 2;
	अन्यथा अगर (symbolrate < 500000)
		symbolrate = 500000;

	अगर (symbolrate < XIN / 16)
		NDEC = 1;
	अगर (symbolrate < XIN / 32)
		NDEC = 2;
	अगर (symbolrate < XIN / 64)
		NDEC = 3;

	अगर (symbolrate < XIN * 10 / 123)
		SFIL = 1;
	अगर (symbolrate < XIN * 10 / 160)
		SFIL = 0;
	अगर (symbolrate < XIN * 10 / 246)
		SFIL = 1;
	अगर (symbolrate < XIN * 10 / 320)
		SFIL = 0;
	अगर (symbolrate < XIN * 10 / 492)
		SFIL = 1;
	अगर (symbolrate < XIN * 10 / 640)
		SFIL = 0;
	अगर (symbolrate < XIN * 10 / 984)
		SFIL = 1;

	symbolrate <<= NDEC;
	ratio = (symbolrate << 4) / FIN;
	पंचांगp =  ((symbolrate << 4) % FIN) << 8;
	ratio = (ratio << 8) + पंचांगp / FIN;
	पंचांगp = (पंचांगp % FIN) << 8;
	ratio = (ratio << 8) + DIV_ROUND_CLOSEST(पंचांगp, FIN);

	BDR = ratio;
	BDRI = (((XIN << 5) / symbolrate) + 1) / 2;

	अगर (BDRI > 0xFF)
		BDRI = 0xFF;

	SFIL = (SFIL << 4) | tda10021_inittab[0x0E];

	NDEC = (NDEC << 6) | tda10021_inittab[0x03];

	_tda10021_ग_लिखोreg (state, 0x03, NDEC);
	_tda10021_ग_लिखोreg (state, 0x0a, BDR&0xff);
	_tda10021_ग_लिखोreg (state, 0x0b, (BDR>> 8)&0xff);
	_tda10021_ग_लिखोreg (state, 0x0c, (BDR>>16)&0x3f);

	_tda10021_ग_लिखोreg (state, 0x0d, BDRI);
	_tda10021_ग_लिखोreg (state, 0x0e, SFIL);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_init (काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;
	पूर्णांक i;

	dprपूर्णांकk("DVB: TDA10021(%d): init chip\n", fe->adapter->num);

	//_tda10021_ग_लिखोreg (fe, 0, 0);

	क्रम (i=0; i<tda10021_inittab_size; i++)
		_tda10021_ग_लिखोreg (state, i, tda10021_inittab[i]);

	_tda10021_ग_लिखोreg (state, 0x34, state->pwm);

	//Comment by markus
	//0x2A[3-0] == PDIV -> P multiplaying factor (P=PDIV+1)(शेष 0)
	//0x2A[4] == BYPPLL -> Power करोwn mode (शेष 1)
	//0x2A[5] == LCK -> PLL Lock Flag
	//0x2A[6] == POLAXIN -> Polarity of the input reference घड़ी (शेष 0)

	//Activate PLL
	_tda10021_ग_लिखोreg(state, 0x2a, tda10021_inittab[0x2a] & 0xef);
	वापस 0;
पूर्ण

काष्ठा qam_params अणु
	u8 conf, agcref, lthr, mseth, aref;
पूर्ण;

अटल पूर्णांक tda10021_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys  = c->delivery_प्रणाली;
	अचिन्हित qam = c->modulation;
	bool is_annex_c;
	u32 reg0x3d;
	काष्ठा tda10021_state* state = fe->demodulator_priv;
	अटल स्थिर काष्ठा qam_params qam_params[] = अणु
		/* Modulation  Conf  AGCref  LTHR  MSETH  AREF */
		[QPSK]	   = अणु 0x14, 0x78,   0x78, 0x8c,  0x96 पूर्ण,
		[QAM_16]   = अणु 0x00, 0x8c,   0x87, 0xa2,  0x91 पूर्ण,
		[QAM_32]   = अणु 0x04, 0x8c,   0x64, 0x74,  0x96 पूर्ण,
		[QAM_64]   = अणु 0x08, 0x6a,   0x46, 0x43,  0x6a पूर्ण,
		[QAM_128]  = अणु 0x0c, 0x78,   0x36, 0x34,  0x7e पूर्ण,
		[QAM_256]  = अणु 0x10, 0x5c,   0x26, 0x23,  0x6b पूर्ण,
	पूर्ण;

	चयन (delsys) अणु
	हाल SYS_DVBC_ANNEX_A:
		is_annex_c = false;
		अवरोध;
	हाल SYS_DVBC_ANNEX_C:
		is_annex_c = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * gcc optimizes the code below the same way as it would code:
	 *           "if (qam > 5) return -EINVAL;"
	 * Yet, the code is clearer, as it shows what QAM standards are
	 * supported by the driver, and aव्योमs the usage of magic numbers on
	 * it.
	 */
	चयन (qam) अणु
	हाल QPSK:
	हाल QAM_16:
	हाल QAM_32:
	हाल QAM_64:
	हाल QAM_128:
	हाल QAM_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (c->inversion != INVERSION_ON && c->inversion != INVERSION_OFF)
		वापस -EINVAL;

	/*prपूर्णांकk("tda10021: set frequency to %d qam=%d symrate=%d\n", p->frequency,qam,p->symbol_rate);*/

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	tda10021_set_symbolrate(state, c->symbol_rate);
	_tda10021_ग_लिखोreg(state, 0x34, state->pwm);

	_tda10021_ग_लिखोreg(state, 0x01, qam_params[qam].agcref);
	_tda10021_ग_लिखोreg(state, 0x05, qam_params[qam].lthr);
	_tda10021_ग_लिखोreg(state, 0x08, qam_params[qam].mseth);
	_tda10021_ग_लिखोreg(state, 0x09, qam_params[qam].aref);

	/*
	 * Bit 0 == 0 means roll-off = 0.15 (Annex A)
	 *	 == 1 means roll-off = 0.13 (Annex C)
	 */
	reg0x3d = tda10021_पढ़ोreg (state, 0x3d);
	अगर (is_annex_c)
		_tda10021_ग_लिखोreg (state, 0x3d, 0x01 | reg0x3d);
	अन्यथा
		_tda10021_ग_लिखोreg (state, 0x3d, 0xfe & reg0x3d);
	tda10021_setup_reg0(state, qam_params[qam].conf, c->inversion);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *status)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;
	पूर्णांक sync;

	*status = 0;
	//0x11[0] == EQALGO -> Equalizer algorithms state
	//0x11[1] == CARLOCK -> Carrier locked
	//0x11[2] == FSYNC -> Frame synchronisation
	//0x11[3] == FEL -> Front End locked
	//0x11[6] == NODVB -> DVB Mode Inक्रमmation
	sync = tda10021_पढ़ोreg (state, 0x11);

	अगर (sync & 2)
		*status |= FE_HAS_SIGNAL|FE_HAS_CARRIER;

	अगर (sync & 4)
		*status |= FE_HAS_SYNC|FE_HAS_VITERBI;

	अगर (sync & 8)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;

	u32 _ber = tda10021_पढ़ोreg(state, 0x14) |
		(tda10021_पढ़ोreg(state, 0x15) << 8) |
		((tda10021_पढ़ोreg(state, 0x16) & 0x0f) << 16);
	_tda10021_ग_लिखोreg(state, 0x10, (tda10021_पढ़ोreg(state, 0x10) & ~0xc0)
					| (tda10021_inittab[0x10] & 0xc0));
	*ber = 10 * _ber;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;

	u8 config = tda10021_पढ़ोreg(state, 0x02);
	u8 gain = tda10021_पढ़ोreg(state, 0x17);
	अगर (config & 0x02)
		/* the agc value is inverted */
		gain = ~gain;
	*strength = (gain << 8) | gain;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;

	u8 quality = ~tda10021_पढ़ोreg(state, 0x18);
	*snr = (quality << 8) | quality;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;

	*ucblocks = tda10021_पढ़ोreg (state, 0x13) & 0x7f;
	अगर (*ucblocks == 0x7f)
		*ucblocks = 0xffffffff;

	/* reset uncorrected block counter */
	_tda10021_ग_लिखोreg (state, 0x10, tda10021_inittab[0x10] & 0xdf);
	_tda10021_ग_लिखोreg (state, 0x10, tda10021_inittab[0x10]);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;
	पूर्णांक sync;
	s8 afc = 0;

	sync = tda10021_पढ़ोreg(state, 0x11);
	afc = tda10021_पढ़ोreg(state, 0x19);
	अगर (verbose) अणु
		/* AFC only valid when carrier has been recovered */
		prपूर्णांकk(sync & 2 ? "DVB: TDA10021(%d): AFC (%d) %dHz\n" :
				  "DVB: TDA10021(%d): [AFC (%d) %dHz]\n",
			state->frontend.dvb->num, afc,
		       -((s32)p->symbol_rate * afc) >> 10);
	पूर्ण

	p->inversion = ((state->reg0 & 0x20) == 0x20) ^ (state->config->invert != 0) ? INVERSION_ON : INVERSION_OFF;
	p->modulation = ((state->reg0 >> 2) & 7) + QAM_16;

	p->fec_inner = FEC_NONE;
	p->frequency = ((p->frequency + 31250) / 62500) * 62500;

	अगर (sync & 2)
		p->frequency -= ((s32)p->symbol_rate * afc) >> 10;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		lock_tuner(state);
	पूर्ण अन्यथा अणु
		unlock_tuner(state);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda10021_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;

	_tda10021_ग_लिखोreg (state, 0x1b, 0x02);  /* pकरोwn ADC */
	_tda10021_ग_लिखोreg (state, 0x00, 0x80);  /* standby */

	वापस 0;
पूर्ण

अटल व्योम tda10021_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10021_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10021_ops;

काष्ठा dvb_frontend* tda10021_attach(स्थिर काष्ठा tda1002x_config* config,
				     काष्ठा i2c_adapter* i2c,
				     u8 pwm)
अणु
	काष्ठा tda10021_state* state = शून्य;
	u8 id;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda10021_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->pwm = pwm;
	state->reg0 = tda10021_inittab[0];

	/* check अगर the demod is there */
	id = tda10021_पढ़ोreg(state, 0x1a);
	अगर ((id & 0xf0) != 0x70) जाओ error;

	/* Don't claim TDA10023 */
	अगर (id == 0x7d)
		जाओ error;

	prपूर्णांकk("TDA10021: i2c-addr = 0x%02x, id = 0x%02x\n",
	       state->config->demod_address, id);

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda10021_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10021_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A, SYS_DVBC_ANNEX_C पूर्ण,
	.info = अणु
		.name = "Philips TDA10021 DVB-C",
		.frequency_min_hz =  47 * MHz,
		.frequency_max_hz = 862 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min = (XIN / 2) / 64,     /* SACLK/64 == (XIN/2)/64 */
		.symbol_rate_max = (XIN / 2) / 4,      /* SACLK/4 */
	#अगर 0
		.frequency_tolerance = ???,
		.symbol_rate_tolerance = ???,  /* ppm */  /* == 8% (spec p. 5) */
	#पूर्ण_अगर
		.caps = 0x400 | //FE_CAN_QAM_4
			FE_CAN_QAM_16 | FE_CAN_QAM_32 | FE_CAN_QAM_64 |
			FE_CAN_QAM_128 | FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO
	पूर्ण,

	.release = tda10021_release,

	.init = tda10021_init,
	.sleep = tda10021_sleep,
	.i2c_gate_ctrl = tda10021_i2c_gate_ctrl,

	.set_frontend = tda10021_set_parameters,
	.get_frontend = tda10021_get_frontend,

	.पढ़ो_status = tda10021_पढ़ो_status,
	.पढ़ो_ber = tda10021_पढ़ो_ber,
	.पढ़ो_संकेत_strength = tda10021_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda10021_पढ़ो_snr,
	.पढ़ो_ucblocks = tda10021_पढ़ो_ucblocks,
पूर्ण;

module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "print AFC offset after tuning for debugging the PWM setting");

MODULE_DESCRIPTION("Philips TDA10021 DVB-C demodulator driver");
MODULE_AUTHOR("Ralph Metzler, Holger Waechtler, Markus Schulz");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(tda10021_attach);
