<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
  /*
     Driver क्रम Philips tda10086 DVBS Demodulator

     (c) 2006 Andrew de Quincey


   */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda10086.h"

#घोषणा SACLK 96000000U

काष्ठा tda10086_state अणु
	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा tda10086_config* config;
	काष्ठा dvb_frontend frontend;

	/* निजी demod data */
	u32 frequency;
	u32 symbol_rate;
	bool has_lock;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "tda10086: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक tda10086_ग_लिखो_byte(काष्ठा tda10086_state *state, पूर्णांक reg, पूर्णांक data)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .flags = 0, .buf = b0, .len = 2 पूर्ण;

	msg.addr = state->config->demod_address;
	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: error reg=0x%x, data=0x%x, ret=%i\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? ret : 0;
पूर्ण

अटल पूर्णांक tda10086_पढ़ो_byte(काष्ठा tda10086_state *state, पूर्णांक reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणुअणु .flags = 0, .buf = b0, .len = 1 पूर्ण,
				अणु .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्णपूर्ण;

	msg[0].addr = state->config->demod_address;
	msg[1].addr = state->config->demod_address;
	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		dprपूर्णांकk("%s: error reg=0x%x, ret=%i\n", __func__, reg,
			ret);
		वापस ret;
	पूर्ण

	वापस b1[0];
पूर्ण

अटल पूर्णांक tda10086_ग_लिखो_mask(काष्ठा tda10086_state *state, पूर्णांक reg, पूर्णांक mask, पूर्णांक data)
अणु
	पूर्णांक val;

	/* पढ़ो a byte and check */
	val = tda10086_पढ़ो_byte(state, reg);
	अगर (val < 0)
		वापस val;

	/* mask अगर off */
	val = val & ~mask;
	val |= data & 0xff;

	/* ग_लिखो it out again */
	वापस tda10086_ग_लिखो_byte(state, reg, val);
पूर्ण

अटल पूर्णांक tda10086_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 t22k_off = 0x80;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (state->config->diseqc_tone)
		t22k_off = 0;
	/* reset */
	tda10086_ग_लिखो_byte(state, 0x00, 0x00);
	msleep(10);

	/* misc setup */
	tda10086_ग_लिखो_byte(state, 0x01, 0x94);
	tda10086_ग_लिखो_byte(state, 0x02, 0x35); /* NOTE: TT drivers appear to disable CSWP */
	tda10086_ग_लिखो_byte(state, 0x03, 0xe4);
	tda10086_ग_लिखो_byte(state, 0x04, 0x43);
	tda10086_ग_लिखो_byte(state, 0x0c, 0x0c);
	tda10086_ग_लिखो_byte(state, 0x1b, 0xb0); /* noise threshold */
	tda10086_ग_लिखो_byte(state, 0x20, 0x89); /* misc */
	tda10086_ग_लिखो_byte(state, 0x30, 0x04); /* acquisition period length */
	tda10086_ग_लिखो_byte(state, 0x32, 0x00); /* irq off */
	tda10086_ग_लिखो_byte(state, 0x31, 0x56); /* setup AFC */

	/* setup PLL (this assumes SACLK = 96MHz) */
	tda10086_ग_लिखो_byte(state, 0x55, 0x2c); /* misc PLL setup */
	अगर (state->config->xtal_freq == TDA10086_XTAL_16M) अणु
		tda10086_ग_लिखो_byte(state, 0x3a, 0x0b); /* M=12 */
		tda10086_ग_लिखो_byte(state, 0x3b, 0x01); /* P=2 */
	पूर्ण अन्यथा अणु
		tda10086_ग_लिखो_byte(state, 0x3a, 0x17); /* M=24 */
		tda10086_ग_लिखो_byte(state, 0x3b, 0x00); /* P=1 */
	पूर्ण
	tda10086_ग_लिखो_mask(state, 0x55, 0x20, 0x00); /* घातerup PLL */

	/* setup TS पूर्णांकerface */
	tda10086_ग_लिखो_byte(state, 0x11, 0x81);
	tda10086_ग_लिखो_byte(state, 0x12, 0x81);
	tda10086_ग_लिखो_byte(state, 0x19, 0x40); /* parallel mode A + MSBFIRST */
	tda10086_ग_लिखो_byte(state, 0x56, 0x80); /* घातerकरोwn WPLL - unused in the mode we use */
	tda10086_ग_लिखो_byte(state, 0x57, 0x08); /* bypass WPLL - unused in the mode we use */
	tda10086_ग_लिखो_byte(state, 0x10, 0x2a);

	/* setup ADC */
	tda10086_ग_लिखो_byte(state, 0x58, 0x61); /* ADC setup */
	tda10086_ग_लिखो_mask(state, 0x58, 0x01, 0x00); /* घातerup ADC */

	/* setup AGC */
	tda10086_ग_लिखो_byte(state, 0x05, 0x0B);
	tda10086_ग_लिखो_byte(state, 0x37, 0x63);
	tda10086_ग_लिखो_byte(state, 0x3f, 0x0a); /* NOTE: flydvb varies it */
	tda10086_ग_लिखो_byte(state, 0x40, 0x64);
	tda10086_ग_लिखो_byte(state, 0x41, 0x4f);
	tda10086_ग_लिखो_byte(state, 0x42, 0x43);

	/* setup viterbi */
	tda10086_ग_लिखो_byte(state, 0x1a, 0x11); /* VBER 10^6, DVB, QPSK */

	/* setup carrier recovery */
	tda10086_ग_लिखो_byte(state, 0x3d, 0x80);

	/* setup SEC */
	tda10086_ग_लिखो_byte(state, 0x36, t22k_off); /* all SEC off, 22k tone */
	tda10086_ग_लिखो_byte(state, 0x34, (((1<<19) * (22000/1000)) / (SACLK/1000)));
	tda10086_ग_लिखो_byte(state, 0x35, (((1<<19) * (22000/1000)) / (SACLK/1000)) >> 8);

	वापस 0;
पूर्ण

अटल व्योम tda10086_diseqc_रुको(काष्ठा tda10086_state *state)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(200);
	जबतक (!(tda10086_पढ़ो_byte(state, 0x50) & 0x01)) अणु
		अगर(समय_after(jअगरfies, समयout)) अणु
			prपूर्णांकk("%s: diseqc queue not ready, command may be lost.\n", __func__);
			अवरोध;
		पूर्ण
		msleep(10);
	पूर्ण
पूर्ण

अटल पूर्णांक tda10086_set_tone(काष्ठा dvb_frontend *fe,
			     क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 t22k_off = 0x80;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (state->config->diseqc_tone)
		t22k_off = 0;

	चयन (tone) अणु
	हाल SEC_TONE_OFF:
		tda10086_ग_लिखो_byte(state, 0x36, t22k_off);
		अवरोध;

	हाल SEC_TONE_ON:
		tda10086_ग_लिखो_byte(state, 0x36, 0x01 + t22k_off);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_send_master_cmd (काष्ठा dvb_frontend* fe,
				    काष्ठा dvb_diseqc_master_cmd* cmd)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	पूर्णांक i;
	u8 oldval;
	u8 t22k_off = 0x80;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (state->config->diseqc_tone)
		t22k_off = 0;

	अगर (cmd->msg_len > 6)
		वापस -EINVAL;
	oldval = tda10086_पढ़ो_byte(state, 0x36);

	क्रम(i=0; i< cmd->msg_len; i++) अणु
		tda10086_ग_लिखो_byte(state, 0x48+i, cmd->msg[i]);
	पूर्ण
	tda10086_ग_लिखो_byte(state, 0x36, (0x08 + t22k_off)
					| ((cmd->msg_len - 1) << 4));

	tda10086_diseqc_रुको(state);

	tda10086_ग_लिखो_byte(state, 0x36, oldval);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_send_burst(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_mini_cmd minicmd)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 oldval = tda10086_पढ़ो_byte(state, 0x36);
	u8 t22k_off = 0x80;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (state->config->diseqc_tone)
		t22k_off = 0;

	चयन(minicmd) अणु
	हाल SEC_MINI_A:
		tda10086_ग_लिखो_byte(state, 0x36, 0x04 + t22k_off);
		अवरोध;

	हाल SEC_MINI_B:
		tda10086_ग_लिखो_byte(state, 0x36, 0x06 + t22k_off);
		अवरोध;
	पूर्ण

	tda10086_diseqc_रुको(state);

	tda10086_ग_लिखो_byte(state, 0x36, oldval);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_set_inversion(काष्ठा tda10086_state *state,
				  काष्ठा dtv_frontend_properties *fe_params)
अणु
	u8 invval = 0x80;

	dprपूर्णांकk ("%s %i %i\n", __func__, fe_params->inversion, state->config->invert);

	चयन(fe_params->inversion) अणु
	हाल INVERSION_OFF:
		अगर (state->config->invert)
			invval = 0x40;
		अवरोध;
	हाल INVERSION_ON:
		अगर (!state->config->invert)
			invval = 0x40;
		अवरोध;
	हाल INVERSION_AUTO:
		invval = 0x00;
		अवरोध;
	पूर्ण
	tda10086_ग_लिखो_mask(state, 0x0c, 0xc0, invval);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_set_symbol_rate(काष्ठा tda10086_state *state,
				    काष्ठा dtv_frontend_properties *fe_params)
अणु
	u8 dfn = 0;
	u8 afs = 0;
	u8 byp = 0;
	u8 reg37 = 0x43;
	u8 reg42 = 0x43;
	u64 big;
	u32 पंचांगp;
	u32 bdr;
	u32 bdri;
	u32 symbol_rate = fe_params->symbol_rate;

	dprपूर्णांकk ("%s %i\n", __func__, symbol_rate);

	/* setup the decimation and anti-aliasing filters.. */
	अगर (symbol_rate < SACLK / 10000 * 137) अणु
		dfn=4;
		afs=1;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 208) अणु
		dfn=4;
		afs=0;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 270) अणु
		dfn=3;
		afs=1;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 416) अणु
		dfn=3;
		afs=0;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 550) अणु
		dfn=2;
		afs=1;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 833) अणु
		dfn=2;
		afs=0;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 1100) अणु
		dfn=1;
		afs=1;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 1666) अणु
		dfn=1;
		afs=0;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 2200) अणु
		dfn=0;
		afs=1;
	पूर्ण अन्यथा अगर (symbol_rate < SACLK / 10000 * 3333) अणु
		dfn=0;
		afs=0;
	पूर्ण अन्यथा अणु
		reg37 = 0x63;
		reg42 = 0x4f;
		byp=1;
	पूर्ण

	/* calculate BDR */
	big = (1ULL<<21) * ((u64) symbol_rate/1000ULL) * (1ULL<<dfn);
	big += ((SACLK/1000ULL)-1ULL);
	करो_भाग(big, (SACLK/1000ULL));
	bdr = big & 0xfffff;

	/* calculate BDRI */
	पंचांगp = (1<<dfn)*(symbol_rate/1000);
	bdri = ((32 * (SACLK/1000)) + (पंचांगp-1)) / पंचांगp;

	tda10086_ग_लिखो_byte(state, 0x21, (afs << 7) | dfn);
	tda10086_ग_लिखो_mask(state, 0x20, 0x08, byp << 3);
	tda10086_ग_लिखो_byte(state, 0x06, bdr);
	tda10086_ग_लिखो_byte(state, 0x07, bdr >> 8);
	tda10086_ग_लिखो_byte(state, 0x08, bdr >> 16);
	tda10086_ग_लिखो_byte(state, 0x09, bdri);
	tda10086_ग_लिखो_byte(state, 0x37, reg37);
	tda10086_ग_लिखो_byte(state, 0x42, reg42);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_set_fec(काष्ठा tda10086_state *state,
			    काष्ठा dtv_frontend_properties *fe_params)
अणु
	u8 fecval;

	dprपूर्णांकk("%s %i\n", __func__, fe_params->fec_inner);

	चयन (fe_params->fec_inner) अणु
	हाल FEC_1_2:
		fecval = 0x00;
		अवरोध;
	हाल FEC_2_3:
		fecval = 0x01;
		अवरोध;
	हाल FEC_3_4:
		fecval = 0x02;
		अवरोध;
	हाल FEC_4_5:
		fecval = 0x03;
		अवरोध;
	हाल FEC_5_6:
		fecval = 0x04;
		अवरोध;
	हाल FEC_6_7:
		fecval = 0x05;
		अवरोध;
	हाल FEC_7_8:
		fecval = 0x06;
		अवरोध;
	हाल FEC_8_9:
		fecval = 0x07;
		अवरोध;
	हाल FEC_AUTO:
		fecval = 0x08;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	tda10086_ग_लिखो_byte(state, 0x0d, fecval);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fe_params = &fe->dtv_property_cache;
	काष्ठा tda10086_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u32 freq = 0;
	पूर्णांक freqoff;

	dprपूर्णांकk ("%s\n", __func__);

	/* modअगरy parameters क्रम tuning */
	tda10086_ग_लिखो_byte(state, 0x02, 0x35);
	state->has_lock = false;

	/* set params */
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);

		अगर (fe->ops.tuner_ops.get_frequency)
			fe->ops.tuner_ops.get_frequency(fe, &freq);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* calculate the frequency offset (in *Hz* not kHz) */
	freqoff = fe_params->frequency - freq;
	freqoff = ((1<<16) * freqoff) / (SACLK/1000);
	tda10086_ग_लिखो_byte(state, 0x3d, 0x80 | ((freqoff >> 8) & 0x7f));
	tda10086_ग_लिखो_byte(state, 0x3e, freqoff);

	अगर ((ret = tda10086_set_inversion(state, fe_params)) < 0)
		वापस ret;
	अगर ((ret = tda10086_set_symbol_rate(state, fe_params)) < 0)
		वापस ret;
	अगर ((ret = tda10086_set_fec(state, fe_params)) < 0)
		वापस ret;

	/* soft reset + disable TS output until lock */
	tda10086_ग_लिखो_mask(state, 0x10, 0x40, 0x40);
	tda10086_ग_लिखो_mask(state, 0x00, 0x01, 0x00);

	state->symbol_rate = fe_params->symbol_rate;
	state->frequency = fe_params->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *fe_params)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 val;
	पूर्णांक पंचांगp;
	u64 पंचांगp64;

	dprपूर्णांकk ("%s\n", __func__);

	/* check क्रम invalid symbol rate */
	अगर (fe_params->symbol_rate < 500000)
		वापस -EINVAL;

	/* calculate the updated frequency (note: we convert from Hz->kHz) */
	पंचांगp64 = ((u64)tda10086_पढ़ो_byte(state, 0x52)
		| (tda10086_पढ़ो_byte(state, 0x51) << 8));
	अगर (पंचांगp64 & 0x8000)
		पंचांगp64 |= 0xffffffffffff0000ULL;
	पंचांगp64 = (पंचांगp64 * (SACLK/1000ULL));
	करो_भाग(पंचांगp64, (1ULL<<15) * (1ULL<<1));
	fe_params->frequency = (पूर्णांक) state->frequency + (पूर्णांक) पंचांगp64;

	/* the inversion */
	val = tda10086_पढ़ो_byte(state, 0x0c);
	अगर (val & 0x80) अणु
		चयन(val & 0x40) अणु
		हाल 0x00:
			fe_params->inversion = INVERSION_OFF;
			अगर (state->config->invert)
				fe_params->inversion = INVERSION_ON;
			अवरोध;
		शेष:
			fe_params->inversion = INVERSION_ON;
			अगर (state->config->invert)
				fe_params->inversion = INVERSION_OFF;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		tda10086_पढ़ो_byte(state, 0x0f);
		चयन(val & 0x02) अणु
		हाल 0x00:
			fe_params->inversion = INVERSION_OFF;
			अगर (state->config->invert)
				fe_params->inversion = INVERSION_ON;
			अवरोध;
		शेष:
			fe_params->inversion = INVERSION_ON;
			अगर (state->config->invert)
				fe_params->inversion = INVERSION_OFF;
			अवरोध;
		पूर्ण
	पूर्ण

	/* calculate the updated symbol rate */
	पंचांगp = tda10086_पढ़ो_byte(state, 0x1d);
	अगर (पंचांगp & 0x80)
		पंचांगp |= 0xffffff00;
	पंचांगp = (पंचांगp * 480 * (1<<1)) / 128;
	पंचांगp = ((state->symbol_rate/1000) * पंचांगp) / (1000000/1000);
	fe_params->symbol_rate = state->symbol_rate + पंचांगp;

	/* the FEC */
	val = (tda10086_पढ़ो_byte(state, 0x0d) & 0x70) >> 4;
	चयन(val) अणु
	हाल 0x00:
		fe_params->fec_inner = FEC_1_2;
		अवरोध;
	हाल 0x01:
		fe_params->fec_inner = FEC_2_3;
		अवरोध;
	हाल 0x02:
		fe_params->fec_inner = FEC_3_4;
		अवरोध;
	हाल 0x03:
		fe_params->fec_inner = FEC_4_5;
		अवरोध;
	हाल 0x04:
		fe_params->fec_inner = FEC_5_6;
		अवरोध;
	हाल 0x05:
		fe_params->fec_inner = FEC_6_7;
		अवरोध;
	हाल 0x06:
		fe_params->fec_inner = FEC_7_8;
		अवरोध;
	हाल 0x07:
		fe_params->fec_inner = FEC_8_9;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *fe_status)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk ("%s\n", __func__);

	val = tda10086_पढ़ो_byte(state, 0x0e);
	*fe_status = 0;
	अगर (val & 0x01)
		*fe_status |= FE_HAS_SIGNAL;
	अगर (val & 0x02)
		*fe_status |= FE_HAS_CARRIER;
	अगर (val & 0x04)
		*fe_status |= FE_HAS_VITERBI;
	अगर (val & 0x08)
		*fe_status |= FE_HAS_SYNC;
	अगर (val & 0x10) अणु
		*fe_status |= FE_HAS_LOCK;
		अगर (!state->has_lock) अणु
			state->has_lock = true;
			/* modअगरy parameters क्रम stable reception */
			tda10086_ग_लिखो_byte(state, 0x02, 0x00);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 * संकेत)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 _str;

	dprपूर्णांकk ("%s\n", __func__);

	_str = 0xff - tda10086_पढ़ो_byte(state, 0x43);
	*संकेत = (_str << 8) | _str;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 * snr)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;
	u8 _snr;

	dprपूर्णांकk ("%s\n", __func__);

	_snr = 0xff - tda10086_पढ़ो_byte(state, 0x1c);
	*snr = (_snr << 8) | _snr;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;

	dprपूर्णांकk ("%s\n", __func__);

	/* पढ़ो it */
	*ucblocks = tda10086_पढ़ो_byte(state, 0x18) & 0x7f;

	/* reset counter */
	tda10086_ग_लिखो_byte(state, 0x18, 0x00);
	tda10086_ग_लिखो_byte(state, 0x18, 0x80);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;

	dprपूर्णांकk ("%s\n", __func__);

	/* पढ़ो it */
	*ber = 0;
	*ber |= tda10086_पढ़ो_byte(state, 0x15);
	*ber |= tda10086_पढ़ो_byte(state, 0x16) << 8;
	*ber |= (tda10086_पढ़ो_byte(state, 0x17) & 0xf) << 16;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;

	dprपूर्णांकk ("%s\n", __func__);

	tda10086_ग_लिखो_mask(state, 0x00, 0x08, 0x08);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा tda10086_state* state = fe->demodulator_priv;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (enable) अणु
		tda10086_ग_लिखो_mask(state, 0x00, 0x10, 0x10);
	पूर्ण अन्यथा अणु
		tda10086_ग_लिखो_mask(state, 0x00, 0x10, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda10086_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (p->symbol_rate > 20000000) अणु
		fesettings->min_delay_ms = 50;
		fesettings->step_size = 2000;
		fesettings->max_drअगरt = 8000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 12000000) अणु
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 1500;
		fesettings->max_drअगरt = 9000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 8000000) अणु
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 1000;
		fesettings->max_drअगरt = 8000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 4000000) अणु
		fesettings->min_delay_ms = 100;
		fesettings->step_size = 500;
		fesettings->max_drअगरt = 7000;
	पूर्ण अन्यथा अगर (p->symbol_rate > 2000000) अणु
		fesettings->min_delay_ms = 200;
		fesettings->step_size = p->symbol_rate / 8000;
		fesettings->max_drअगरt = 14 * fesettings->step_size;
	पूर्ण अन्यथा अणु
		fesettings->min_delay_ms = 200;
		fesettings->step_size =  p->symbol_rate / 8000;
		fesettings->max_drअगरt = 18 * fesettings->step_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tda10086_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda10086_state *state = fe->demodulator_priv;
	tda10086_sleep(fe);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10086_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name     = "Philips TDA10086 DVB-S",
		.frequency_min_hz      =  950 * MHz,
		.frequency_max_hz      = 2150 * MHz,
		.frequency_stepsize_hz =  125 * kHz,
		.symbol_rate_min  = 1000000,
		.symbol_rate_max  = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK
	पूर्ण,

	.release = tda10086_release,

	.init = tda10086_init,
	.sleep = tda10086_sleep,
	.i2c_gate_ctrl = tda10086_i2c_gate_ctrl,

	.set_frontend = tda10086_set_frontend,
	.get_frontend = tda10086_get_frontend,
	.get_tune_settings = tda10086_get_tune_settings,

	.पढ़ो_status = tda10086_पढ़ो_status,
	.पढ़ो_ber = tda10086_पढ़ो_ber,
	.पढ़ो_संकेत_strength = tda10086_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda10086_पढ़ो_snr,
	.पढ़ो_ucblocks = tda10086_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = tda10086_send_master_cmd,
	.diseqc_send_burst = tda10086_send_burst,
	.set_tone = tda10086_set_tone,
पूर्ण;

काष्ठा dvb_frontend* tda10086_attach(स्थिर काष्ठा tda10086_config* config,
				     काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा tda10086_state *state;

	dprपूर्णांकk ("%s\n", __func__);

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda10086_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	अगर (tda10086_पढ़ो_byte(state, 0x1e) != 0xe1) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda10086_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Philips TDA10086 DVB-S Demodulator");
MODULE_AUTHOR("Andrew de Quincey");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(tda10086_attach);
