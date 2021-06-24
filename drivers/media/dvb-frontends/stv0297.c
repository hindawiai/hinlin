<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम STV0297 demodulator

    Copyright (C) 2004 Andrew de Quincey <adq_dvb@lidskialf.net>
    Copyright (C) 2003-2004 Dennis Noermann <dennis.noermann@noernet.de>

*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "stv0297.h"

काष्ठा stv0297_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा stv0297_config *config;
	काष्ठा dvb_frontend frontend;

	अचिन्हित दीर्घ last_ber;
	अचिन्हित दीर्घ base_freq;
पूर्ण;

#अगर 1
#घोषणा dprपूर्णांकk(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा dprपूर्णांकk(x...)
#पूर्ण_अगर

#घोषणा STV0297_CLOCK_KHZ   28900


अटल पूर्णांक stv0297_ग_लिखोreg(काष्ठा stv0297_state *state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = state->config->demod_address,.flags = 0,.buf = buf,.len = 2 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल पूर्णांक stv0297_पढ़ोreg(काष्ठा stv0297_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु अणु.addr = state->config->demod_address,.flags = 0,.buf = b0,.len = 1पूर्ण,
				 अणु.addr = state->config->demod_address,.flags = I2C_M_RD,.buf = b1,.len = 1पूर्ण
			       पूर्ण;

	// this device needs a STOP between the रेजिस्टर and data
	अगर (state->config->stop_during_पढ़ो) अणु
		अगर ((ret = i2c_transfer(state->i2c, &msg[0], 1)) != 1) अणु
			dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n", __func__, reg, ret);
			वापस -1;
		पूर्ण
		अगर ((ret = i2c_transfer(state->i2c, &msg[1], 1)) != 1) अणु
			dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n", __func__, reg, ret);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((ret = i2c_transfer(state->i2c, msg, 2)) != 2) अणु
			dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n", __func__, reg, ret);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस b1[0];
पूर्ण

अटल पूर्णांक stv0297_ग_लिखोreg_mask(काष्ठा stv0297_state *state, u8 reg, u8 mask, u8 data)
अणु
	पूर्णांक val;

	val = stv0297_पढ़ोreg(state, reg);
	val &= ~mask;
	val |= (data & mask);
	stv0297_ग_लिखोreg(state, reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_पढ़ोregs(काष्ठा stv0297_state *state, u8 reg1, u8 * b, u8 len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु अणु.addr = state->config->demod_address,.flags = 0,.buf =
				  &reg1,.len = 1पूर्ण,
	अणु.addr = state->config->demod_address,.flags = I2C_M_RD,.buf = b,.len = lenपूर्ण
	पूर्ण;

	// this device needs a STOP between the रेजिस्टर and data
	अगर (state->config->stop_during_पढ़ो) अणु
		अगर ((ret = i2c_transfer(state->i2c, &msg[0], 1)) != 1) अणु
			dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n", __func__, reg1, ret);
			वापस -1;
		पूर्ण
		अगर ((ret = i2c_transfer(state->i2c, &msg[1], 1)) != 1) अणु
			dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n", __func__, reg1, ret);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((ret = i2c_transfer(state->i2c, msg, 2)) != 2) अणु
			dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n", __func__, reg1, ret);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 stv0297_get_symbolrate(काष्ठा stv0297_state *state)
अणु
	u64 पंचांगp;

	पंचांगp = (u64)(stv0297_पढ़ोreg(state, 0x55)
		    | (stv0297_पढ़ोreg(state, 0x56) << 8)
		    | (stv0297_पढ़ोreg(state, 0x57) << 16)
		    | (stv0297_पढ़ोreg(state, 0x58) << 24));

	पंचांगp *= STV0297_CLOCK_KHZ;
	पंचांगp >>= 32;

	वापस (u32) पंचांगp;
पूर्ण

अटल व्योम stv0297_set_symbolrate(काष्ठा stv0297_state *state, u32 srate)
अणु
	दीर्घ पंचांगp;

	पंचांगp = 131072L * srate;	/* 131072 = 2^17  */
	पंचांगp = पंचांगp / (STV0297_CLOCK_KHZ / 4);	/* 1/4 = 2^-2 */
	पंचांगp = पंचांगp * 8192L;	/* 8192 = 2^13 */

	stv0297_ग_लिखोreg(state, 0x55, (अचिन्हित अक्षर) (पंचांगp & 0xFF));
	stv0297_ग_लिखोreg(state, 0x56, (अचिन्हित अक्षर) (पंचांगp >> 8));
	stv0297_ग_लिखोreg(state, 0x57, (अचिन्हित अक्षर) (पंचांगp >> 16));
	stv0297_ग_लिखोreg(state, 0x58, (अचिन्हित अक्षर) (पंचांगp >> 24));
पूर्ण

अटल व्योम stv0297_set_sweeprate(काष्ठा stv0297_state *state, लघु fshअगरt, दीर्घ symrate)
अणु
	दीर्घ पंचांगp;

	पंचांगp = (दीर्घ) fshअगरt *262144L;	/* 262144 = 2*18 */
	पंचांगp /= symrate;
	पंचांगp *= 1024;		/* 1024 = 2*10   */

	// adjust
	अगर (पंचांगp >= 0) अणु
		पंचांगp += 500000;
	पूर्ण अन्यथा अणु
		पंचांगp -= 500000;
	पूर्ण
	पंचांगp /= 1000000;

	stv0297_ग_लिखोreg(state, 0x60, पंचांगp & 0xFF);
	stv0297_ग_लिखोreg_mask(state, 0x69, 0xF0, (पंचांगp >> 4) & 0xf0);
पूर्ण

अटल व्योम stv0297_set_carrieroffset(काष्ठा stv0297_state *state, दीर्घ offset)
अणु
	दीर्घ पंचांगp;

	/* symrate is hardcoded to 10000 */
	पंचांगp = offset * 26844L;	/* (2**28)/10000 */
	अगर (पंचांगp < 0)
		पंचांगp += 0x10000000;
	पंचांगp &= 0x0FFFFFFF;

	stv0297_ग_लिखोreg(state, 0x66, (अचिन्हित अक्षर) (पंचांगp & 0xFF));
	stv0297_ग_लिखोreg(state, 0x67, (अचिन्हित अक्षर) (पंचांगp >> 8));
	stv0297_ग_लिखोreg(state, 0x68, (अचिन्हित अक्षर) (पंचांगp >> 16));
	stv0297_ग_लिखोreg_mask(state, 0x69, 0x0F, (पंचांगp >> 24) & 0x0f);
पूर्ण

/*
अटल दीर्घ stv0297_get_carrieroffset(काष्ठा stv0297_state *state)
अणु
	s64 पंचांगp;

	stv0297_ग_लिखोreg(state, 0x6B, 0x00);

	पंचांगp = stv0297_पढ़ोreg(state, 0x66);
	पंचांगp |= (stv0297_पढ़ोreg(state, 0x67) << 8);
	पंचांगp |= (stv0297_पढ़ोreg(state, 0x68) << 16);
	पंचांगp |= (stv0297_पढ़ोreg(state, 0x69) & 0x0F) << 24;

	पंचांगp *= stv0297_get_symbolrate(state);
	पंचांगp >>= 28;

	वापस (s32) पंचांगp;
पूर्ण
*/

अटल व्योम stv0297_set_initialdemodfreq(काष्ठा stv0297_state *state, दीर्घ freq)
अणु
	s32 पंचांगp;

	अगर (freq > 10000)
		freq -= STV0297_CLOCK_KHZ;

	पंचांगp = (STV0297_CLOCK_KHZ * 1000) / (1 << 16);
	पंचांगp = (freq * 1000) / पंचांगp;
	अगर (पंचांगp > 0xffff)
		पंचांगp = 0xffff;

	stv0297_ग_लिखोreg_mask(state, 0x25, 0x80, 0x80);
	stv0297_ग_लिखोreg(state, 0x21, पंचांगp >> 8);
	stv0297_ग_लिखोreg(state, 0x20, पंचांगp);
पूर्ण

अटल पूर्णांक stv0297_set_qam(काष्ठा stv0297_state *state,
			   क्रमागत fe_modulation modulation)
अणु
	पूर्णांक val = 0;

	चयन (modulation) अणु
	हाल QAM_16:
		val = 0;
		अवरोध;

	हाल QAM_32:
		val = 1;
		अवरोध;

	हाल QAM_64:
		val = 4;
		अवरोध;

	हाल QAM_128:
		val = 2;
		अवरोध;

	हाल QAM_256:
		val = 3;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	stv0297_ग_लिखोreg_mask(state, 0x00, 0x70, val << 4);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_set_inversion(काष्ठा stv0297_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
	पूर्णांक val = 0;

	चयन (inversion) अणु
	हाल INVERSION_OFF:
		val = 0;
		अवरोध;

	हाल INVERSION_ON:
		val = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	stv0297_ग_लिखोreg_mask(state, 0x83, 0x08, val << 3);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;

	अगर (enable) अणु
		stv0297_ग_लिखोreg(state, 0x87, 0x78);
		stv0297_ग_लिखोreg(state, 0x86, 0xc8);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	पूर्णांक i;

	/* load init table */
	क्रम (i=0; !(state->config->inittab[i] == 0xff && state->config->inittab[i+1] == 0xff); i+=2)
		stv0297_ग_लिखोreg(state, state->config->inittab[i], state->config->inittab[i+1]);
	msleep(200);

	state->last_ber = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;

	stv0297_ग_लिखोreg_mask(state, 0x80, 1, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;

	u8 sync = stv0297_पढ़ोreg(state, 0xDF);

	*status = 0;
	अगर (sync & 0x80)
		*status |=
			FE_HAS_SYNC | FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_LOCK;
	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 * ber)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	u8 BER[3];

	stv0297_पढ़ोregs(state, 0xA0, BER, 3);
	अगर (!(BER[0] & 0x80)) अणु
		state->last_ber = BER[2] << 8 | BER[1];
		stv0297_ग_लिखोreg_mask(state, 0xA0, 0x80, 0x80);
	पूर्ण

	*ber = state->last_ber;

	वापस 0;
पूर्ण


अटल पूर्णांक stv0297_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 * strength)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	u8 STRENGTH[3];
	u16 पंचांगp;

	stv0297_पढ़ोregs(state, 0x41, STRENGTH, 3);
	पंचांगp = (STRENGTH[1] & 0x03) << 8 | STRENGTH[0];
	अगर (STRENGTH[2] & 0x20) अणु
		अगर (पंचांगp < 0x200)
			पंचांगp = 0;
		अन्यथा
			पंचांगp = पंचांगp - 0x200;
	पूर्ण अन्यथा अणु
		अगर (पंचांगp > 0x1ff)
			पंचांगp = 0;
		अन्यथा
			पंचांगp = 0x1ff - पंचांगp;
	पूर्ण
	*strength = (पंचांगp << 7) | (पंचांगp >> 2);
	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 * snr)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	u8 SNR[2];

	stv0297_पढ़ोregs(state, 0x07, SNR, 2);
	*snr = SNR[1] << 8 | SNR[0];

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 * ucblocks)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;

	stv0297_ग_लिखोreg_mask(state, 0xDF, 0x03, 0x03); /* मुक्तze the counters */

	*ucblocks = (stv0297_पढ़ोreg(state, 0xD5) << 8)
		| stv0297_पढ़ोreg(state, 0xD4);

	stv0297_ग_लिखोreg_mask(state, 0xDF, 0x03, 0x02); /* clear the counters */
	stv0297_ग_लिखोreg_mask(state, 0xDF, 0x03, 0x01); /* re-enable the counters */

	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	पूर्णांक u_threshold;
	पूर्णांक initial_u;
	पूर्णांक blind_u;
	पूर्णांक delay;
	पूर्णांक sweeprate;
	पूर्णांक carrieroffset;
	अचिन्हित दीर्घ समयout;
	क्रमागत fe_spectral_inversion inversion;

	चयन (p->modulation) अणु
	हाल QAM_16:
	हाल QAM_32:
	हाल QAM_64:
		delay = 100;
		sweeprate = 1000;
		अवरोध;

	हाल QAM_128:
	हाल QAM_256:
		delay = 200;
		sweeprate = 500;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// determine inversion dependent parameters
	inversion = p->inversion;
	अगर (state->config->invert)
		inversion = (inversion == INVERSION_ON) ? INVERSION_OFF : INVERSION_ON;
	carrieroffset = -330;
	चयन (inversion) अणु
	हाल INVERSION_OFF:
		अवरोध;

	हाल INVERSION_ON:
		sweeprate = -sweeprate;
		carrieroffset = -carrieroffset;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	stv0297_init(fe);
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* clear software पूर्णांकerrupts */
	stv0297_ग_लिखोreg(state, 0x82, 0x0);

	/* set initial demodulation frequency */
	stv0297_set_initialdemodfreq(state, 7250);

	/* setup AGC */
	stv0297_ग_लिखोreg_mask(state, 0x43, 0x10, 0x00);
	stv0297_ग_लिखोreg(state, 0x41, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x42, 0x03, 0x01);
	stv0297_ग_लिखोreg_mask(state, 0x36, 0x60, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x36, 0x18, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x71, 0x80, 0x80);
	stv0297_ग_लिखोreg(state, 0x72, 0x00);
	stv0297_ग_लिखोreg(state, 0x73, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x74, 0x0F, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x43, 0x08, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x71, 0x80, 0x00);

	/* setup STL */
	stv0297_ग_लिखोreg_mask(state, 0x5a, 0x20, 0x20);
	stv0297_ग_लिखोreg_mask(state, 0x5b, 0x02, 0x02);
	stv0297_ग_लिखोreg_mask(state, 0x5b, 0x02, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x5b, 0x01, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x5a, 0x40, 0x40);

	/* disable frequency sweep */
	stv0297_ग_लिखोreg_mask(state, 0x6a, 0x01, 0x00);

	/* reset deपूर्णांकerleaver */
	stv0297_ग_लिखोreg_mask(state, 0x81, 0x01, 0x01);
	stv0297_ग_लिखोreg_mask(state, 0x81, 0x01, 0x00);

	/* ??? */
	stv0297_ग_लिखोreg_mask(state, 0x83, 0x20, 0x20);
	stv0297_ग_लिखोreg_mask(state, 0x83, 0x20, 0x00);

	/* reset equaliser */
	u_threshold = stv0297_पढ़ोreg(state, 0x00) & 0xf;
	initial_u = stv0297_पढ़ोreg(state, 0x01) >> 4;
	blind_u = stv0297_पढ़ोreg(state, 0x01) & 0xf;
	stv0297_ग_लिखोreg_mask(state, 0x84, 0x01, 0x01);
	stv0297_ग_लिखोreg_mask(state, 0x84, 0x01, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x00, 0x0f, u_threshold);
	stv0297_ग_लिखोreg_mask(state, 0x01, 0xf0, initial_u << 4);
	stv0297_ग_लिखोreg_mask(state, 0x01, 0x0f, blind_u);

	/* data comes from पूर्णांकernal A/D */
	stv0297_ग_लिखोreg_mask(state, 0x87, 0x80, 0x00);

	/* clear phase रेजिस्टरs */
	stv0297_ग_लिखोreg(state, 0x63, 0x00);
	stv0297_ग_लिखोreg(state, 0x64, 0x00);
	stv0297_ग_लिखोreg(state, 0x65, 0x00);
	stv0297_ग_लिखोreg(state, 0x66, 0x00);
	stv0297_ग_लिखोreg(state, 0x67, 0x00);
	stv0297_ग_लिखोreg(state, 0x68, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x69, 0x0f, 0x00);

	/* set parameters */
	stv0297_set_qam(state, p->modulation);
	stv0297_set_symbolrate(state, p->symbol_rate / 1000);
	stv0297_set_sweeprate(state, sweeprate, p->symbol_rate / 1000);
	stv0297_set_carrieroffset(state, carrieroffset);
	stv0297_set_inversion(state, inversion);

	/* kick off lock */
	/* Disable corner detection क्रम higher QAMs */
	अगर (p->modulation == QAM_128 ||
		p->modulation == QAM_256)
		stv0297_ग_लिखोreg_mask(state, 0x88, 0x08, 0x00);
	अन्यथा
		stv0297_ग_लिखोreg_mask(state, 0x88, 0x08, 0x08);

	stv0297_ग_लिखोreg_mask(state, 0x5a, 0x20, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x6a, 0x01, 0x01);
	stv0297_ग_लिखोreg_mask(state, 0x43, 0x40, 0x40);
	stv0297_ग_लिखोreg_mask(state, 0x5b, 0x30, 0x00);
	stv0297_ग_लिखोreg_mask(state, 0x03, 0x0c, 0x0c);
	stv0297_ग_लिखोreg_mask(state, 0x03, 0x03, 0x03);
	stv0297_ग_लिखोreg_mask(state, 0x43, 0x10, 0x10);

	/* रुको क्रम WGAGC lock */
	समयout = jअगरfies + msecs_to_jअगरfies(2000);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		msleep(10);
		अगर (stv0297_पढ़ोreg(state, 0x43) & 0x08)
			अवरोध;
	पूर्ण
	अगर (समय_after(jअगरfies, समयout)) अणु
		जाओ समयout;
	पूर्ण
	msleep(20);

	/* रुको क्रम equaliser partial convergence */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		msleep(10);

		अगर (stv0297_पढ़ोreg(state, 0x82) & 0x04) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (समय_after(jअगरfies, समयout)) अणु
		जाओ समयout;
	पूर्ण

	/* रुको क्रम equaliser full convergence */
	समयout = jअगरfies + msecs_to_jअगरfies(delay);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		msleep(10);

		अगर (stv0297_पढ़ोreg(state, 0x82) & 0x08) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (समय_after(jअगरfies, समयout)) अणु
		जाओ समयout;
	पूर्ण

	/* disable sweep */
	stv0297_ग_लिखोreg_mask(state, 0x6a, 1, 0);
	stv0297_ग_लिखोreg_mask(state, 0x88, 8, 0);

	/* रुको क्रम मुख्य lock */
	समयout = jअगरfies + msecs_to_jअगरfies(20);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		msleep(10);

		अगर (stv0297_पढ़ोreg(state, 0xDF) & 0x80) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (समय_after(jअगरfies, समयout)) अणु
		जाओ समयout;
	पूर्ण
	msleep(100);

	/* is it still locked after that delay? */
	अगर (!(stv0297_पढ़ोreg(state, 0xDF) & 0x80)) अणु
		जाओ समयout;
	पूर्ण

	/* success!! */
	stv0297_ग_लिखोreg_mask(state, 0x5a, 0x40, 0x00);
	state->base_freq = p->frequency;
	वापस 0;

समयout:
	stv0297_ग_लिखोreg_mask(state, 0x6a, 0x01, 0x00);
	वापस 0;
पूर्ण

अटल पूर्णांक stv0297_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	पूर्णांक reg_00, reg_83;

	reg_00 = stv0297_पढ़ोreg(state, 0x00);
	reg_83 = stv0297_पढ़ोreg(state, 0x83);

	p->frequency = state->base_freq;
	p->inversion = (reg_83 & 0x08) ? INVERSION_ON : INVERSION_OFF;
	अगर (state->config->invert)
		p->inversion = (p->inversion == INVERSION_ON) ? INVERSION_OFF : INVERSION_ON;
	p->symbol_rate = stv0297_get_symbolrate(state) * 1000;
	p->fec_inner = FEC_NONE;

	चयन ((reg_00 >> 4) & 0x7) अणु
	हाल 0:
		p->modulation = QAM_16;
		अवरोध;
	हाल 1:
		p->modulation = QAM_32;
		अवरोध;
	हाल 2:
		p->modulation = QAM_128;
		अवरोध;
	हाल 3:
		p->modulation = QAM_256;
		अवरोध;
	हाल 4:
		p->modulation = QAM_64;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stv0297_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0297_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0297_ops;

काष्ठा dvb_frontend *stv0297_attach(स्थिर काष्ठा stv0297_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv0297_state *state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा stv0297_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->last_ber = 0;
	state->base_freq = 0;

	/* check अगर the demod is there */
	अगर ((stv0297_पढ़ोreg(state, 0x80) & 0x70) != 0x20)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &stv0297_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0297_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A पूर्ण,
	.info = अणु
		 .name = "ST STV0297 DVB-C",
		 .frequency_min_hz = 47 * MHz,
		 .frequency_max_hz = 862 * MHz,
		 .frequency_stepsize_hz = 62500,
		 .symbol_rate_min = 870000,
		 .symbol_rate_max = 11700000,
		 .caps = FE_CAN_QAM_16 | FE_CAN_QAM_32 | FE_CAN_QAM_64 |
		 FE_CAN_QAM_128 | FE_CAN_QAM_256 | FE_CAN_FEC_AUTOपूर्ण,

	.release = stv0297_release,

	.init = stv0297_init,
	.sleep = stv0297_sleep,
	.i2c_gate_ctrl = stv0297_i2c_gate_ctrl,

	.set_frontend = stv0297_set_frontend,
	.get_frontend = stv0297_get_frontend,

	.पढ़ो_status = stv0297_पढ़ो_status,
	.पढ़ो_ber = stv0297_पढ़ो_ber,
	.पढ़ो_संकेत_strength = stv0297_पढ़ो_संकेत_strength,
	.पढ़ो_snr = stv0297_पढ़ो_snr,
	.पढ़ो_ucblocks = stv0297_पढ़ो_ucblocks,
पूर्ण;

MODULE_DESCRIPTION("ST STV0297 DVB-C Demodulator driver");
MODULE_AUTHOR("Dennis Noermann and Andrew de Quincey");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(stv0297_attach);
