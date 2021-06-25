<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम ST STV0299 demodulator

    Copyright (C) 2001-2002 Convergence Integrated Media GmbH
	<ralph@convergence.de>,
	<holger@convergence.de>,
	<js@convergence.de>


    Philips SU1278/SH

    Copyright (C) 2002 by Peter Schildmann <peter.schildmann@web.de>


    LG TDQF-S001F

    Copyright (C) 2002 Felix Domke <पंचांगbinc@elitedvb.net>
		     & Andreas Oberritter <obi@linuxtv.org>


    Support क्रम Samsung TBMU24112IMB used on Technisat SkyStar2 rev. 2.6B

    Copyright (C) 2003 Vadim Catana <skystar@molकरोva.cc>:

    Support क्रम Philips SU1278 on Technotrend hardware

    Copyright (C) 2004 Andrew de Quincey <adq_dvb@lidskialf.net>


*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "stv0299.h"

काष्ठा stv0299_state अणु
	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा stv0299_config* config;
	काष्ठा dvb_frontend frontend;

	u8 initialised:1;
	u32 tuner_frequency;
	u32 symbol_rate;
	क्रमागत fe_code_rate fec_inner;
	पूर्णांक errmode;
	u32 ucblocks;
	u8 mcr_reg;
पूर्ण;

#घोषणा STATUS_BER 0
#घोषणा STATUS_UCBLOCKS 1

अटल पूर्णांक debug;
अटल पूर्णांक debug_legacy_dish_चयन;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "stv0299: " args); \
	पूर्ण जबतक (0)


अटल पूर्णांक stv0299_ग_लिखोregI (काष्ठा stv0299_state* state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf [] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;

	ret = i2c_transfer (state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक stv0299_ग_लिखो(काष्ठा dvb_frontend* fe, स्थिर u8 buf[], पूर्णांक len)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	अगर (len != 2)
		वापस -EINVAL;

	वापस stv0299_ग_लिखोregI(state, buf[0], buf[1]);
पूर्ण

अटल u8 stv0299_पढ़ोreg (काष्ठा stv0299_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer (state->i2c, msg, 2);

	अगर (ret != 2)
		dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n",
				__func__, reg, ret);

	वापस b1[0];
पूर्ण

अटल पूर्णांक stv0299_पढ़ोregs (काष्ठा stv0299_state* state, u8 reg1, u8 *b, u8 len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = &reg1, .len = 1 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b, .len = len पूर्ण पूर्ण;

	ret = i2c_transfer (state->i2c, msg, 2);

	अगर (ret != 2)
		dprपूर्णांकk("%s: readreg error (ret == %i)\n", __func__, ret);

	वापस ret == 2 ? 0 : ret;
पूर्ण

अटल पूर्णांक stv0299_set_FEC(काष्ठा stv0299_state *state, क्रमागत fe_code_rate fec)
अणु
	dprपूर्णांकk ("%s\n", __func__);

	चयन (fec) अणु
	हाल FEC_AUTO:
	अणु
		वापस stv0299_ग_लिखोregI (state, 0x31, 0x1f);
	पूर्ण
	हाल FEC_1_2:
	अणु
		वापस stv0299_ग_लिखोregI (state, 0x31, 0x01);
	पूर्ण
	हाल FEC_2_3:
	अणु
		वापस stv0299_ग_लिखोregI (state, 0x31, 0x02);
	पूर्ण
	हाल FEC_3_4:
	अणु
		वापस stv0299_ग_लिखोregI (state, 0x31, 0x04);
	पूर्ण
	हाल FEC_5_6:
	अणु
		वापस stv0299_ग_लिखोregI (state, 0x31, 0x08);
	पूर्ण
	हाल FEC_7_8:
	अणु
		वापस stv0299_ग_लिखोregI (state, 0x31, 0x10);
	पूर्ण
	शेष:
	अणु
		वापस -EINVAL;
	पूर्ण
    पूर्ण
पूर्ण

अटल क्रमागत fe_code_rate stv0299_get_fec(काष्ठा stv0299_state *state)
अणु
	अटल क्रमागत fe_code_rate fec_tab[] = अणु FEC_2_3, FEC_3_4, FEC_5_6,
					       FEC_7_8, FEC_1_2 पूर्ण;
	u8 index;

	dprपूर्णांकk ("%s\n", __func__);

	index = stv0299_पढ़ोreg (state, 0x1b);
	index &= 0x7;

	अगर (index > 4)
		वापस FEC_AUTO;

	वापस fec_tab [index];
पूर्ण

अटल पूर्णांक stv0299_रुको_diseqc_fअगरo (काष्ठा stv0299_state* state, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	dprपूर्णांकk ("%s\n", __func__);

	जबतक (stv0299_पढ़ोreg(state, 0x0a) & 1) अणु
		अगर (jअगरfies - start > समयout) अणु
			dprपूर्णांकk ("%s: timeout!!\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_रुको_diseqc_idle (काष्ठा stv0299_state* state, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	dprपूर्णांकk ("%s\n", __func__);

	जबतक ((stv0299_पढ़ोreg(state, 0x0a) & 3) != 2 ) अणु
		अगर (jअगरfies - start > समयout) अणु
			dprपूर्णांकk ("%s: timeout!!\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_set_symbolrate (काष्ठा dvb_frontend* fe, u32 srate)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	u64 big = srate;
	u32 ratio;

	// check rate is within limits
	अगर ((srate < 1000000) || (srate > 45000000)) वापस -EINVAL;

	// calculate value to program
	big = big << 20;
	big += (state->config->mclk-1); // round correctly
	करो_भाग(big, state->config->mclk);
	ratio = big << 4;

	वापस state->config->set_symbol_rate(fe, srate, ratio);
पूर्ण

अटल पूर्णांक stv0299_get_symbolrate (काष्ठा stv0299_state* state)
अणु
	u32 Mclk = state->config->mclk / 4096L;
	u32 srate;
	s32 offset;
	u8 sfr[3];
	s8 rtf;

	dprपूर्णांकk ("%s\n", __func__);

	stv0299_पढ़ोregs (state, 0x1f, sfr, 3);
	stv0299_पढ़ोregs (state, 0x1a, (u8 *)&rtf, 1);

	srate = (sfr[0] << 8) | sfr[1];
	srate *= Mclk;
	srate /= 16;
	srate += (sfr[2] >> 4) * Mclk / 256;
	offset = (s32) rtf * (srate / 4096L);
	offset /= 128;

	dprपूर्णांकk ("%s : srate = %i\n", __func__, srate);
	dprपूर्णांकk ("%s : ofset = %i\n", __func__, offset);

	srate += offset;

	srate += 1000;
	srate /= 2000;
	srate *= 2000;

	वापस srate;
पूर्ण

अटल पूर्णांक stv0299_send_diseqc_msg (काष्ठा dvb_frontend* fe,
				    काष्ठा dvb_diseqc_master_cmd *m)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	u8 val;
	पूर्णांक i;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (stv0299_रुको_diseqc_idle (state, 100) < 0)
		वापस -ETIMEDOUT;

	val = stv0299_पढ़ोreg (state, 0x08);

	अगर (stv0299_ग_लिखोregI (state, 0x08, (val & ~0x7) | 0x6))  /* DiSEqC mode */
		वापस -EREMOTEIO;

	क्रम (i=0; i<m->msg_len; i++) अणु
		अगर (stv0299_रुको_diseqc_fअगरo (state, 100) < 0)
			वापस -ETIMEDOUT;

		अगर (stv0299_ग_लिखोregI (state, 0x09, m->msg[i]))
			वापस -EREMOTEIO;
	पूर्ण

	अगर (stv0299_रुको_diseqc_idle (state, 100) < 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (stv0299_रुको_diseqc_idle (state, 100) < 0)
		वापस -ETIMEDOUT;

	val = stv0299_पढ़ोreg (state, 0x08);

	अगर (stv0299_ग_लिखोregI (state, 0x08, (val & ~0x7) | 0x2))	/* burst mode */
		वापस -EREMOTEIO;

	अगर (stv0299_ग_लिखोregI (state, 0x09, burst == SEC_MINI_A ? 0x00 : 0xff))
		वापस -EREMOTEIO;

	अगर (stv0299_रुको_diseqc_idle (state, 100) < 0)
		वापस -ETIMEDOUT;

	अगर (stv0299_ग_लिखोregI (state, 0x08, val))
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_set_tone(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	u8 val;

	अगर (stv0299_रुको_diseqc_idle (state, 100) < 0)
		वापस -ETIMEDOUT;

	val = stv0299_पढ़ोreg (state, 0x08);

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		वापस stv0299_ग_लिखोregI (state, 0x08, val | 0x3);

	हाल SEC_TONE_OFF:
		वापस stv0299_ग_लिखोregI (state, 0x08, (val & ~0x3) | 0x02);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक stv0299_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	u8 reg0x08;
	u8 reg0x0c;

	dprपूर्णांकk("%s: %s\n", __func__,
		voltage == SEC_VOLTAGE_13 ? "SEC_VOLTAGE_13" :
		voltage == SEC_VOLTAGE_18 ? "SEC_VOLTAGE_18" : "??");

	reg0x08 = stv0299_पढ़ोreg (state, 0x08);
	reg0x0c = stv0299_पढ़ोreg (state, 0x0c);

	/*
	 *  H/V चयनing over OP0, OP1 and OP2 are LNB घातer enable bits
	 */
	reg0x0c &= 0x0f;
	reg0x08 = (reg0x08 & 0x3f) | (state->config->lock_output << 6);

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		अगर (state->config->volt13_op0_op1 == STV0299_VOLT13_OP0)
			reg0x0c |= 0x10; /* OP1 off, OP0 on */
		अन्यथा
			reg0x0c |= 0x40; /* OP1 on, OP0 off */
		अवरोध;
	हाल SEC_VOLTAGE_18:
		reg0x0c |= 0x50; /* OP1 on, OP0 on */
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		/* LNB घातer off! */
		reg0x08 = 0x00;
		reg0x0c = 0x00;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (state->config->op0_off)
		reg0x0c &= ~0x10;

	stv0299_ग_लिखोregI(state, 0x08, reg0x08);
	वापस stv0299_ग_लिखोregI(state, 0x0c, reg0x0c);
पूर्ण

अटल पूर्णांक stv0299_send_legacy_dish_cmd (काष्ठा dvb_frontend* fe, अचिन्हित दीर्घ cmd)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	u8 reg0x08;
	u8 reg0x0c;
	u8 lv_mask = 0x40;
	u8 last = 1;
	पूर्णांक i;
	kसमय_प्रकार nextसमय;
	kसमय_प्रकार tv[10];

	reg0x08 = stv0299_पढ़ोreg (state, 0x08);
	reg0x0c = stv0299_पढ़ोreg (state, 0x0c);
	reg0x0c &= 0x0f;
	stv0299_ग_लिखोregI (state, 0x08, (reg0x08 & 0x3f) | (state->config->lock_output << 6));
	अगर (state->config->volt13_op0_op1 == STV0299_VOLT13_OP0)
		lv_mask = 0x10;

	cmd = cmd << 1;
	अगर (debug_legacy_dish_चयन)
		prपूर्णांकk ("%s switch command: 0x%04lx\n",__func__, cmd);

	nextसमय = kसमय_get_bootसमय();
	अगर (debug_legacy_dish_चयन)
		tv[0] = nextसमय;
	stv0299_ग_लिखोregI (state, 0x0c, reg0x0c | 0x50); /* set LNB to 18V */

	dvb_frontend_sleep_until(&nextसमय, 32000);

	क्रम (i=0; i<9; i++) अणु
		अगर (debug_legacy_dish_चयन)
			tv[i+1] = kसमय_get_bootसमय();
		अगर((cmd & 0x01) != last) अणु
			/* set voltage to (last ? 13V : 18V) */
			stv0299_ग_लिखोregI (state, 0x0c, reg0x0c | (last ? lv_mask : 0x50));
			last = (last) ? 0 : 1;
		पूर्ण

		cmd = cmd >> 1;

		अगर (i != 8)
			dvb_frontend_sleep_until(&nextसमय, 8000);
	पूर्ण
	अगर (debug_legacy_dish_चयन) अणु
		prपूर्णांकk ("%s(%d): switch delay (should be 32k followed by all 8k\n",
			__func__, fe->dvb->num);
		क्रम (i = 1; i < 10; i++)
			prपूर्णांकk("%d: %d\n", i,
			       (पूर्णांक) kसमय_us_delta(tv[i], tv[i-1]));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_init (काष्ठा dvb_frontend* fe)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	पूर्णांक i;
	u8 reg;
	u8 val;

	dprपूर्णांकk("stv0299: init chip\n");

	stv0299_ग_लिखोregI(state, 0x02, 0x30 | state->mcr_reg);
	msleep(50);

	क्रम (i = 0; ; i += 2)  अणु
		reg = state->config->inittab[i];
		val = state->config->inittab[i+1];
		अगर (reg == 0xff && val == 0xff)
			अवरोध;
		अगर (reg == 0x0c && state->config->op0_off)
			val &= ~0x10;
		अगर (reg == 0x2)
			state->mcr_reg = val & 0xf;
		stv0299_ग_लिखोregI(state, reg, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	u8 संकेत = 0xff - stv0299_पढ़ोreg (state, 0x18);
	u8 sync = stv0299_पढ़ोreg (state, 0x1b);

	dprपूर्णांकk ("%s : FE_READ_STATUS : VSTATUS: 0x%02x\n", __func__, sync);
	*status = 0;

	अगर (संकेत > 10)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 0x80)
		*status |= FE_HAS_CARRIER;

	अगर (sync & 0x10)
		*status |= FE_HAS_VITERBI;

	अगर (sync & 0x08)
		*status |= FE_HAS_SYNC;

	अगर ((sync & 0x98) == 0x98)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	अगर (state->errmode != STATUS_BER)
		वापस -ENOSYS;

	*ber = stv0299_पढ़ोreg(state, 0x1e) | (stv0299_पढ़ोreg(state, 0x1d) << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	s32 संकेत =  0xffff - ((stv0299_पढ़ोreg (state, 0x18) << 8)
			       | stv0299_पढ़ोreg (state, 0x19));

	dprपूर्णांकk ("%s : FE_READ_SIGNAL_STRENGTH : AGC2I: 0x%02x%02x, signal=0x%04x\n", __func__,
		 stv0299_पढ़ोreg (state, 0x18),
		 stv0299_पढ़ोreg (state, 0x19), (पूर्णांक) संकेत);

	संकेत = संकेत * 5 / 4;
	*strength = (संकेत > 0xffff) ? 0xffff : (संकेत < 0) ? 0 : संकेत;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	s32 xsnr = 0xffff - ((stv0299_पढ़ोreg (state, 0x24) << 8)
			   | stv0299_पढ़ोreg (state, 0x25));
	xsnr = 3 * (xsnr - 0xa100);
	*snr = (xsnr > 0xffff) ? 0xffff : (xsnr < 0) ? 0 : xsnr;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	अगर (state->errmode != STATUS_UCBLOCKS)
		वापस -ENOSYS;

	state->ucblocks += stv0299_पढ़ोreg(state, 0x1e);
	state->ucblocks += (stv0299_पढ़ोreg(state, 0x1d) << 8);
	*ucblocks = state->ucblocks;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	पूर्णांक invval = 0;

	dprपूर्णांकk ("%s : FE_SET_FRONTEND\n", __func__);
	अगर (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);

	// set the inversion
	अगर (p->inversion == INVERSION_OFF) invval = 0;
	अन्यथा अगर (p->inversion == INVERSION_ON) invval = 1;
	अन्यथा अणु
		prपूर्णांकk("stv0299 does not support auto-inversion\n");
		वापस -EINVAL;
	पूर्ण
	अगर (state->config->invert) invval = (~invval) & 1;
	stv0299_ग_लिखोregI(state, 0x0c, (stv0299_पढ़ोreg(state, 0x0c) & 0xfe) | invval);

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	stv0299_set_FEC(state, p->fec_inner);
	stv0299_set_symbolrate(fe, p->symbol_rate);
	stv0299_ग_लिखोregI(state, 0x22, 0x00);
	stv0299_ग_लिखोregI(state, 0x23, 0x00);

	state->tuner_frequency = p->frequency;
	state->fec_inner = p->fec_inner;
	state->symbol_rate = p->symbol_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	s32 derot_freq;
	पूर्णांक invval;

	derot_freq = (s32)(s16) ((stv0299_पढ़ोreg (state, 0x22) << 8)
				| stv0299_पढ़ोreg (state, 0x23));

	derot_freq *= (state->config->mclk >> 16);
	derot_freq += 500;
	derot_freq /= 1000;

	p->frequency += derot_freq;

	invval = stv0299_पढ़ोreg (state, 0x0c) & 1;
	अगर (state->config->invert) invval = (~invval) & 1;
	p->inversion = invval ? INVERSION_ON : INVERSION_OFF;

	p->fec_inner = stv0299_get_fec(state);
	p->symbol_rate = stv0299_get_symbolrate(state);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	stv0299_ग_लिखोregI(state, 0x02, 0xb0 | state->mcr_reg);
	state->initialised = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		stv0299_ग_लिखोregI(state, 0x05, 0xb5);
	पूर्ण अन्यथा अणु
		stv0299_ग_लिखोregI(state, 0x05, 0x35);
	पूर्ण
	udelay(1);
	वापस 0;
पूर्ण

अटल पूर्णांक stv0299_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	fesettings->min_delay_ms = state->config->min_delay_ms;
	अगर (p->symbol_rate < 10000000) अणु
		fesettings->step_size = p->symbol_rate / 32000;
		fesettings->max_drअगरt = 5000;
	पूर्ण अन्यथा अणु
		fesettings->step_size = p->symbol_rate / 16000;
		fesettings->max_drअगरt = p->symbol_rate / 2000;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम stv0299_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा stv0299_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0299_ops;

काष्ठा dvb_frontend* stv0299_attach(स्थिर काष्ठा stv0299_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा stv0299_state* state = शून्य;
	पूर्णांक id;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा stv0299_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;
	state->tuner_frequency = 0;
	state->symbol_rate = 0;
	state->fec_inner = 0;
	state->errmode = STATUS_BER;

	/* check अगर the demod is there */
	stv0299_ग_लिखोregI(state, 0x02, 0x30); /* standby off */
	msleep(200);
	id = stv0299_पढ़ोreg(state, 0x00);

	/* रेजिस्टर 0x00 contains 0xa1 क्रम STV0299 and STV0299B */
	/* रेजिस्टर 0x00 might contain 0x80 when वापसing from standby */
	अगर (id != 0xa1 && id != 0x80) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &stv0299_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0299_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "ST STV0299 DVB-S",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	=  125 * kHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.symbol_rate_tolerance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK |
		      FE_CAN_FEC_AUTO
	पूर्ण,

	.release = stv0299_release,

	.init = stv0299_init,
	.sleep = stv0299_sleep,
	.ग_लिखो = stv0299_ग_लिखो,
	.i2c_gate_ctrl = stv0299_i2c_gate_ctrl,

	.set_frontend = stv0299_set_frontend,
	.get_frontend = stv0299_get_frontend,
	.get_tune_settings = stv0299_get_tune_settings,

	.पढ़ो_status = stv0299_पढ़ो_status,
	.पढ़ो_ber = stv0299_पढ़ो_ber,
	.पढ़ो_संकेत_strength = stv0299_पढ़ो_संकेत_strength,
	.पढ़ो_snr = stv0299_पढ़ो_snr,
	.पढ़ो_ucblocks = stv0299_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = stv0299_send_diseqc_msg,
	.diseqc_send_burst = stv0299_send_diseqc_burst,
	.set_tone = stv0299_set_tone,
	.set_voltage = stv0299_set_voltage,
	.dishnetwork_send_legacy_command = stv0299_send_legacy_dish_cmd,
पूर्ण;

module_param(debug_legacy_dish_चयन, पूर्णांक, 0444);
MODULE_PARM_DESC(debug_legacy_dish_चयन, "Enable timing analysis for Dish Network legacy switches");

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("ST STV0299 DVB Demodulator driver");
MODULE_AUTHOR("Ralph Metzler, Holger Waechtler, Peter Schildmann, Felix Domke, Andreas Oberritter, Andrew de Quincey, Kenneth Aafly");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(stv0299_attach);
