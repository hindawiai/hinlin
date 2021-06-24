<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम VES1893 and VES1993 QPSK Demodulators

    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>
    Copyright (C) 2001 Ronny Strutz <3des@elitedvb.de>
    Copyright (C) 2002 Dennis Noermann <dennis.noermann@noernet.de>
    Copyright (C) 2002-2003 Andreas Oberritter <obi@linuxtv.org>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <media/dvb_frontend.h>
#समावेश "ves1x93.h"


काष्ठा ves1x93_state अणु
	काष्ठा i2c_adapter* i2c;
	/* configuration settings */
	स्थिर काष्ठा ves1x93_config* config;
	काष्ठा dvb_frontend frontend;

	/* previous uncorrected block counter */
	क्रमागत fe_spectral_inversion inversion;
	u8 *init_1x93_tab;
	u8 *init_1x93_wtab;
	u8 tab_size;
	u8 demod_type;
	u32 frequency;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk	अगर (debug) prपूर्णांकk

#घोषणा DEMOD_VES1893		0
#घोषणा DEMOD_VES1993		1

अटल u8 init_1893_tab [] = अणु
	0x01, 0xa4, 0x35, 0x80, 0x2a, 0x0b, 0x55, 0xc4,
	0x09, 0x69, 0x00, 0x86, 0x4c, 0x28, 0x7f, 0x00,
	0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x21, 0xb0, 0x14, 0x00, 0xdc, 0x00,
	0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x55, 0x00, 0x00, 0x7f, 0x00
पूर्ण;

अटल u8 init_1993_tab [] = अणु
	0x00, 0x9c, 0x35, 0x80, 0x6a, 0x09, 0x72, 0x8c,
	0x09, 0x6b, 0x00, 0x00, 0x4c, 0x08, 0x00, 0x00,
	0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x40, 0x21, 0xb0, 0x00, 0x00, 0x00, 0x10,
	0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x55, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x00, 0x0e, 0x80, 0x00
पूर्ण;

अटल u8 init_1893_wtab[] =
अणु
	1,1,1,1,1,1,1,1, 1,1,0,0,1,1,0,0,
	0,1,0,0,0,0,0,0, 1,0,1,1,0,0,0,1,
	1,1,1,0,0,0,0,0, 0,0,1,1,0,0,0,0,
	1,1,1,0,1,1
पूर्ण;

अटल u8 init_1993_wtab[] =
अणु
	1,1,1,1,1,1,1,1, 1,1,0,0,1,1,0,0,
	0,1,0,0,0,0,0,0, 1,1,1,1,0,0,0,1,
	1,1,1,0,0,0,0,0, 0,0,1,1,0,0,0,0,
	1,1,1,0,1,1,1,1, 1,1,1,1,1
पूर्ण;

अटल पूर्णांक ves1x93_ग_लिखोreg (काष्ठा ves1x93_state* state, u8 reg, u8 data)
अणु
	u8 buf [] = अणु 0x00, reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 3 पूर्ण;
	पूर्णांक err;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		dprपूर्णांकk ("%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)\n", __func__, err, reg, data);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 ves1x93_पढ़ोreg (काष्ठा ves1x93_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु 0x00, reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 2 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer (state->i2c, msg, 2);

	अगर (ret != 2) वापस ret;

	वापस b1[0];
पूर्ण

अटल पूर्णांक ves1x93_clr_bit (काष्ठा ves1x93_state* state)
अणु
	msleep(10);
	ves1x93_ग_लिखोreg (state, 0, state->init_1x93_tab[0] & 0xfe);
	ves1x93_ग_लिखोreg (state, 0, state->init_1x93_tab[0]);
	msleep(50);
	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_set_inversion(काष्ठा ves1x93_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
	u8 val;

	/*
	 * inversion on/off are पूर्णांकerchanged because i and q seem to
	 * be swapped on the hardware
	 */

	चयन (inversion) अणु
	हाल INVERSION_OFF:
		val = 0xc0;
		अवरोध;
	हाल INVERSION_ON:
		val = 0x80;
		अवरोध;
	हाल INVERSION_AUTO:
		val = 0x00;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ves1x93_ग_लिखोreg (state, 0x0c, (state->init_1x93_tab[0x0c] & 0x3f) | val);
पूर्ण

अटल पूर्णांक ves1x93_set_fec(काष्ठा ves1x93_state *state, क्रमागत fe_code_rate fec)
अणु
	अगर (fec == FEC_AUTO)
		वापस ves1x93_ग_लिखोreg (state, 0x0d, 0x08);
	अन्यथा अगर (fec < FEC_1_2 || fec > FEC_8_9)
		वापस -EINVAL;
	अन्यथा
		वापस ves1x93_ग_लिखोreg (state, 0x0d, fec - FEC_1_2);
पूर्ण

अटल क्रमागत fe_code_rate ves1x93_get_fec(काष्ठा ves1x93_state *state)
अणु
	वापस FEC_1_2 + ((ves1x93_पढ़ोreg (state, 0x0d) >> 4) & 0x7);
पूर्ण

अटल पूर्णांक ves1x93_set_symbolrate (काष्ठा ves1x93_state* state, u32 srate)
अणु
	u32 BDR;
	u32 ratio;
	u8  ADCONF, FCONF, FNR, AGCR;
	u32 BDRI;
	u32 पंचांगp;
	u32 FIN;

	dprपूर्णांकk("%s: srate == %d\n", __func__, (अचिन्हित पूर्णांक) srate);

	अगर (srate > state->config->xin/2)
		srate = state->config->xin/2;

	अगर (srate < 500000)
		srate = 500000;

#घोषणा MUL (1UL<<26)

	FIN = (state->config->xin + 6000) >> 4;

	पंचांगp = srate << 6;
	ratio = पंचांगp / FIN;

	पंचांगp = (पंचांगp % FIN) << 8;
	ratio = (ratio << 8) + पंचांगp / FIN;

	पंचांगp = (पंचांगp % FIN) << 8;
	ratio = (ratio << 8) + पंचांगp / FIN;

	FNR = 0xff;

	अगर (ratio < MUL/3)	     FNR = 0;
	अगर (ratio < (MUL*11)/50)     FNR = 1;
	अगर (ratio < MUL/6)	     FNR = 2;
	अगर (ratio < MUL/9)	     FNR = 3;
	अगर (ratio < MUL/12)	     FNR = 4;
	अगर (ratio < (MUL*11)/200)    FNR = 5;
	अगर (ratio < MUL/24)	     FNR = 6;
	अगर (ratio < (MUL*27)/1000)   FNR = 7;
	अगर (ratio < MUL/48)	     FNR = 8;
	अगर (ratio < (MUL*137)/10000) FNR = 9;

	अगर (FNR == 0xff) अणु
		ADCONF = 0x89;
		FCONF  = 0x80;
		FNR	= 0;
	पूर्ण अन्यथा अणु
		ADCONF = 0x81;
		FCONF  = 0x88 | (FNR >> 1) | ((FNR & 0x01) << 5);
		/*FCONF	 = 0x80 | ((FNR & 0x01) << 5) | (((FNR > 1) & 0x03) << 3) | ((FNR >> 1) & 0x07);*/
	पूर्ण

	BDR = (( (ratio << (FNR >> 1)) >> 4) + 1) >> 1;
	BDRI = ( ((FIN << 8) / ((srate << (FNR >> 1)) >> 2)) + 1) >> 1;

	dprपूर्णांकk("FNR= %d\n", FNR);
	dprपूर्णांकk("ratio= %08x\n", (अचिन्हित पूर्णांक) ratio);
	dprपूर्णांकk("BDR= %08x\n", (अचिन्हित पूर्णांक) BDR);
	dprपूर्णांकk("BDRI= %02x\n", (अचिन्हित पूर्णांक) BDRI);

	अगर (BDRI > 0xff)
		BDRI = 0xff;

	ves1x93_ग_लिखोreg (state, 0x06, 0xff & BDR);
	ves1x93_ग_लिखोreg (state, 0x07, 0xff & (BDR >> 8));
	ves1x93_ग_लिखोreg (state, 0x08, 0x0f & (BDR >> 16));

	ves1x93_ग_लिखोreg (state, 0x09, BDRI);
	ves1x93_ग_लिखोreg (state, 0x20, ADCONF);
	ves1x93_ग_लिखोreg (state, 0x21, FCONF);

	AGCR = state->init_1x93_tab[0x05];
	अगर (state->config->invert_pwm)
		AGCR |= 0x20;

	अगर (srate < 6000000)
		AGCR |= 0x80;
	अन्यथा
		AGCR &= ~0x80;

	ves1x93_ग_लिखोreg (state, 0x05, AGCR);

	/* ves1993 hates this, will lose lock */
	अगर (state->demod_type != DEMOD_VES1993)
		ves1x93_clr_bit (state);

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_init (काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;
	पूर्णांक i;
	पूर्णांक val;

	dprपूर्णांकk("%s: init chip\n", __func__);

	क्रम (i = 0; i < state->tab_size; i++) अणु
		अगर (state->init_1x93_wtab[i]) अणु
			val = state->init_1x93_tab[i];

			अगर (state->config->invert_pwm && (i == 0x05)) val |= 0x20; /* invert PWM */
			ves1x93_ग_लिखोreg (state, i, val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		वापस ves1x93_ग_लिखोreg (state, 0x1f, 0x20);
	हाल SEC_VOLTAGE_18:
		वापस ves1x93_ग_लिखोreg (state, 0x1f, 0x30);
	हाल SEC_VOLTAGE_OFF:
		वापस ves1x93_ग_लिखोreg (state, 0x1f, 0x00);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ves1x93_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	u8 sync = ves1x93_पढ़ोreg (state, 0x0e);

	/*
	 * The ves1893 someबार वापसs sync values that make no sense,
	 * because, e.g., the SIGNAL bit is 0, जबतक some of the higher
	 * bits are 1 (and how can there be a CARRIER w/o a SIGNAL?).
	 * Tests showed that the VITERBI and SYNC bits are वापसed
	 * reliably, जबतक the SIGNAL and CARRIER bits ar someबार wrong.
	 * If such a हाल occurs, we पढ़ो the value again, until we get a
	 * valid value.
	 */
	पूर्णांक maxtry = 10; /* just क्रम safety - let's not get stuck here */
	जबतक ((sync & 0x03) != 0x03 && (sync & 0x0c) && maxtry--) अणु
		msleep(10);
		sync = ves1x93_पढ़ोreg (state, 0x0e);
	पूर्ण

	*status = 0;

	अगर (sync & 1)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 2)
		*status |= FE_HAS_CARRIER;

	अगर (sync & 4)
		*status |= FE_HAS_VITERBI;

	अगर (sync & 8)
		*status |= FE_HAS_SYNC;

	अगर ((sync & 0x1f) == 0x1f)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	*ber = ves1x93_पढ़ोreg (state, 0x15);
	*ber |= (ves1x93_पढ़ोreg (state, 0x16) << 8);
	*ber |= ((ves1x93_पढ़ोreg (state, 0x17) & 0x0F) << 16);
	*ber *= 10;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	u8 संकेत = ~ves1x93_पढ़ोreg (state, 0x0b);
	*strength = (संकेत << 8) | संकेत;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	u8 _snr = ~ves1x93_पढ़ोreg (state, 0x1c);
	*snr = (_snr << 8) | _snr;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	*ucblocks = ves1x93_पढ़ोreg (state, 0x18) & 0x7f;

	अगर (*ucblocks == 0x7f)
		*ucblocks = 0xffffffff;   /* counter overflow... */

	ves1x93_ग_लिखोreg (state, 0x18, 0x00);  /* reset the counter */
	ves1x93_ग_लिखोreg (state, 0x18, 0x80);  /* dto. */

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण
	ves1x93_set_inversion (state, p->inversion);
	ves1x93_set_fec(state, p->fec_inner);
	ves1x93_set_symbolrate(state, p->symbol_rate);
	state->inversion = p->inversion;
	state->frequency = p->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;
	पूर्णांक afc;

	afc = ((पूर्णांक)((अक्षर)(ves1x93_पढ़ोreg (state, 0x0a) << 1)))/2;
	afc = (afc * (पूर्णांक)(p->symbol_rate/1000/8))/16;

	p->frequency = state->frequency - afc;

	/*
	 * inversion indicator is only valid
	 * अगर स्वतः inversion was used
	 */
	अगर (state->inversion == INVERSION_AUTO)
		p->inversion = (ves1x93_पढ़ोreg (state, 0x0f) & 2) ?
				INVERSION_OFF : INVERSION_ON;
	p->fec_inner = ves1x93_get_fec(state);
	/*  XXX FIXME: timing offset !! */

	वापस 0;
पूर्ण

अटल पूर्णांक ves1x93_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	वापस ves1x93_ग_लिखोreg (state, 0x00, 0x08);
पूर्ण

अटल व्योम ves1x93_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल पूर्णांक ves1x93_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा ves1x93_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		वापस ves1x93_ग_लिखोreg(state, 0x00, 0x11);
	पूर्ण अन्यथा अणु
		वापस ves1x93_ग_लिखोreg(state, 0x00, 0x01);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ves1x93_ops;

काष्ठा dvb_frontend* ves1x93_attach(स्थिर काष्ठा ves1x93_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा ves1x93_state* state = शून्य;
	u8 identity;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा ves1x93_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->inversion = INVERSION_OFF;

	/* check अगर the demod is there + identअगरy it */
	identity = ves1x93_पढ़ोreg(state, 0x1e);
	चयन (identity) अणु
	हाल 0xdc: /* VES1893A rev1 */
		prपूर्णांकk("ves1x93: Detected ves1893a rev1\n");
		state->demod_type = DEMOD_VES1893;
		state->init_1x93_tab = init_1893_tab;
		state->init_1x93_wtab = init_1893_wtab;
		state->tab_size = माप(init_1893_tab);
		अवरोध;

	हाल 0xdd: /* VES1893A rev2 */
		prपूर्णांकk("ves1x93: Detected ves1893a rev2\n");
		state->demod_type = DEMOD_VES1893;
		state->init_1x93_tab = init_1893_tab;
		state->init_1x93_wtab = init_1893_wtab;
		state->tab_size = माप(init_1893_tab);
		अवरोध;

	हाल 0xde: /* VES1993 */
		prपूर्णांकk("ves1x93: Detected ves1993\n");
		state->demod_type = DEMOD_VES1993;
		state->init_1x93_tab = init_1993_tab;
		state->init_1x93_wtab = init_1993_wtab;
		state->tab_size = माप(init_1993_tab);
		अवरोध;

	शेष:
		जाओ error;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &ves1x93_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ves1x93_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "VLSI VES1x93 DVB-S",
		.frequency_min_hz	=   950 * MHz,
		.frequency_max_hz	=  2150 * MHz,
		.frequency_stepsize_hz	=   125 * kHz,
		.frequency_tolerance_hz	= 29500 * kHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
	/*	.symbol_rate_tolerance	=	???,*/
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK
	पूर्ण,

	.release = ves1x93_release,

	.init = ves1x93_init,
	.sleep = ves1x93_sleep,
	.i2c_gate_ctrl = ves1x93_i2c_gate_ctrl,

	.set_frontend = ves1x93_set_frontend,
	.get_frontend = ves1x93_get_frontend,

	.पढ़ो_status = ves1x93_पढ़ो_status,
	.पढ़ो_ber = ves1x93_पढ़ो_ber,
	.पढ़ो_संकेत_strength = ves1x93_पढ़ो_संकेत_strength,
	.पढ़ो_snr = ves1x93_पढ़ो_snr,
	.पढ़ो_ucblocks = ves1x93_पढ़ो_ucblocks,

	.set_voltage = ves1x93_set_voltage,
पूर्ण;

module_param(debug, पूर्णांक, 0644);

MODULE_DESCRIPTION("VLSI VES1x93 DVB-S Demodulator driver");
MODULE_AUTHOR("Ralph Metzler");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(ves1x93_attach);
