<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Zarlink DVB-T ZL10353 demodulator
 *
 * Copyright (C) 2006, 2007 Christopher Pascoe <c.pascoe@itee.uq.edu.au>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "zl10353_priv.h"
#समावेश "zl10353.h"

काष्ठा zl10353_state अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend frontend;

	काष्ठा zl10353_config config;

	u32 bandwidth;
	u32 ucblocks;
	u32 frequency;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "zl10353: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक debug_regs;

अटल पूर्णांक zl10353_single_ग_लिखो(काष्ठा dvb_frontend *fe, u8 reg, u8 val)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config.demod_address, .flags = 0,
			       .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		prपूर्णांकk("zl10353: write to reg %x failed (err = %d)!\n", reg, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_ग_लिखो(काष्ठा dvb_frontend *fe, स्थिर u8 ibuf[], पूर्णांक ilen)
अणु
	पूर्णांक err, i;
	क्रम (i = 0; i < ilen - 1; i++)
		अगर ((err = zl10353_single_ग_लिखो(fe, ibuf[0] + i, ibuf[i + 1])))
			वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_पढ़ो_रेजिस्टर(काष्ठा zl10353_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[1] = अणु reg पूर्ण;
	u8 b1[1] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु अणु .addr = state->config.demod_address,
				    .flags = 0,
				    .buf = b0, .len = 1 पूर्ण,
				  अणु .addr = state->config.demod_address,
				    .flags = I2C_M_RD,
				    .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		prपूर्णांकk("%s: readreg error (reg=%d, ret==%i)\n",
		       __func__, reg, ret);
		वापस ret;
	पूर्ण

	वापस b1[0];
पूर्ण

अटल व्योम zl10353_dump_regs(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 reg;

	/* Dump all रेजिस्टरs. */
	क्रम (reg = 0; ; reg++) अणु
		अगर (reg % 16 == 0) अणु
			अगर (reg)
				prपूर्णांकk(KERN_CONT "\n");
			prपूर्णांकk(KERN_DEBUG "%02x:", reg);
		पूर्ण
		ret = zl10353_पढ़ो_रेजिस्टर(state, reg);
		अगर (ret >= 0)
			prपूर्णांकk(KERN_CONT " %02x", (u8)ret);
		अन्यथा
			prपूर्णांकk(KERN_CONT " --");
		अगर (reg == 0xff)
			अवरोध;
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम zl10353_calc_nominal_rate(काष्ठा dvb_frontend *fe,
				      u32 bandwidth,
				      u16 *nominal_rate)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u32 adc_घड़ी = 450560; /* 45.056 MHz */
	u64 value;
	u8 bw = bandwidth / 1000000;

	अगर (state->config.adc_घड़ी)
		adc_घड़ी = state->config.adc_घड़ी;

	value = (u64)10 * (1 << 23) / 7 * 125;
	value = (bw * value) + adc_घड़ी / 2;
	*nominal_rate = भाग_u64(value, adc_घड़ी);

	dprपूर्णांकk("%s: bw %d, adc_clock %d => 0x%x\n",
		__func__, bw, adc_घड़ी, *nominal_rate);
पूर्ण

अटल व्योम zl10353_calc_input_freq(काष्ठा dvb_frontend *fe,
				    u16 *input_freq)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u32 adc_घड़ी = 450560;	/* 45.056  MHz */
	पूर्णांक अगर2 = 361667;	/* 36.1667 MHz */
	पूर्णांक अगरe;
	u64 value;

	अगर (state->config.adc_घड़ी)
		adc_घड़ी = state->config.adc_घड़ी;
	अगर (state->config.अगर2)
		अगर2 = state->config.अगर2;

	अगर (adc_घड़ी >= अगर2 * 2)
		अगरe = अगर2;
	अन्यथा अणु
		अगरe = adc_घड़ी - (अगर2 % adc_घड़ी);
		अगर (अगरe > adc_घड़ी / 2)
			अगरe = adc_घड़ी - अगरe;
	पूर्ण
	value = भाग_u64((u64)65536 * अगरe + adc_घड़ी / 2, adc_घड़ी);
	*input_freq = -value;

	dprपूर्णांकk("%s: if2 %d, ife %d, adc_clock %d => %d / 0x%x\n",
		__func__, अगर2, अगरe, adc_घड़ी, -(पूर्णांक)value, *input_freq);
पूर्ण

अटल पूर्णांक zl10353_sleep(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 zl10353_softकरोwn[] = अणु 0x50, 0x0C, 0x44 पूर्ण;

	zl10353_ग_लिखो(fe, zl10353_softकरोwn, माप(zl10353_softकरोwn));
	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u16 nominal_rate, input_freq;
	u8 pllbuf[6] = अणु 0x67 पूर्ण, acq_ctl = 0;
	u16 tps = 0;

	state->frequency = c->frequency;

	zl10353_single_ग_लिखो(fe, RESET, 0x80);
	udelay(200);
	zl10353_single_ग_लिखो(fe, 0xEA, 0x01);
	udelay(200);
	zl10353_single_ग_लिखो(fe, 0xEA, 0x00);

	zl10353_single_ग_लिखो(fe, AGC_TARGET, 0x28);

	अगर (c->transmission_mode != TRANSMISSION_MODE_AUTO)
		acq_ctl |= (1 << 0);
	अगर (c->guard_पूर्णांकerval != GUARD_INTERVAL_AUTO)
		acq_ctl |= (1 << 1);
	zl10353_single_ग_लिखो(fe, ACQ_CTL, acq_ctl);

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		/* These are extrapolated from the 7 and 8MHz values */
		zl10353_single_ग_लिखो(fe, MCLK_RATIO, 0x97);
		zl10353_single_ग_लिखो(fe, 0x64, 0x34);
		zl10353_single_ग_लिखो(fe, 0xcc, 0xdd);
		अवरोध;
	हाल 7000000:
		zl10353_single_ग_लिखो(fe, MCLK_RATIO, 0x86);
		zl10353_single_ग_लिखो(fe, 0x64, 0x35);
		zl10353_single_ग_लिखो(fe, 0xcc, 0x73);
		अवरोध;
	शेष:
		c->bandwidth_hz = 8000000;
		fallthrough;
	हाल 8000000:
		zl10353_single_ग_लिखो(fe, MCLK_RATIO, 0x75);
		zl10353_single_ग_लिखो(fe, 0x64, 0x36);
		zl10353_single_ग_लिखो(fe, 0xcc, 0x73);
	पूर्ण

	zl10353_calc_nominal_rate(fe, c->bandwidth_hz, &nominal_rate);
	zl10353_single_ग_लिखो(fe, TRL_NOMINAL_RATE_1, msb(nominal_rate));
	zl10353_single_ग_लिखो(fe, TRL_NOMINAL_RATE_0, lsb(nominal_rate));
	state->bandwidth = c->bandwidth_hz;

	zl10353_calc_input_freq(fe, &input_freq);
	zl10353_single_ग_लिखो(fe, INPUT_FREQ_1, msb(input_freq));
	zl10353_single_ग_लिखो(fe, INPUT_FREQ_0, lsb(input_freq));

	/* Hपूर्णांक at TPS settings */
	चयन (c->code_rate_HP) अणु
	हाल FEC_2_3:
		tps |= (1 << 7);
		अवरोध;
	हाल FEC_3_4:
		tps |= (2 << 7);
		अवरोध;
	हाल FEC_5_6:
		tps |= (3 << 7);
		अवरोध;
	हाल FEC_7_8:
		tps |= (4 << 7);
		अवरोध;
	हाल FEC_1_2:
	हाल FEC_AUTO:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (c->code_rate_LP) अणु
	हाल FEC_2_3:
		tps |= (1 << 4);
		अवरोध;
	हाल FEC_3_4:
		tps |= (2 << 4);
		अवरोध;
	हाल FEC_5_6:
		tps |= (3 << 4);
		अवरोध;
	हाल FEC_7_8:
		tps |= (4 << 4);
		अवरोध;
	हाल FEC_1_2:
	हाल FEC_AUTO:
		अवरोध;
	हाल FEC_NONE:
		अगर (c->hierarchy == HIERARCHY_AUTO ||
		    c->hierarchy == HIERARCHY_NONE)
			अवरोध;
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (c->modulation) अणु
	हाल QPSK:
		अवरोध;
	हाल QAM_AUTO:
	हाल QAM_16:
		tps |= (1 << 13);
		अवरोध;
	हाल QAM_64:
		tps |= (2 << 13);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
	हाल TRANSMISSION_MODE_AUTO:
		अवरोध;
	हाल TRANSMISSION_MODE_8K:
		tps |= (1 << 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (c->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_32:
	हाल GUARD_INTERVAL_AUTO:
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		tps |= (1 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		tps |= (2 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		tps |= (3 << 2);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (c->hierarchy) अणु
	हाल HIERARCHY_AUTO:
	हाल HIERARCHY_NONE:
		अवरोध;
	हाल HIERARCHY_1:
		tps |= (1 << 10);
		अवरोध;
	हाल HIERARCHY_2:
		tps |= (2 << 10);
		अवरोध;
	हाल HIERARCHY_4:
		tps |= (3 << 10);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	zl10353_single_ग_लिखो(fe, TPS_GIVEN_1, msb(tps));
	zl10353_single_ग_लिखो(fe, TPS_GIVEN_0, lsb(tps));

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	/*
	 * If there is no tuner attached to the secondary I2C bus, we call
	 * set_params to program a potential tuner attached somewhere अन्यथा.
	 * Otherwise, we update the PLL रेजिस्टरs via calc_regs.
	 */
	अगर (state->config.no_tuner) अणु
		अगर (fe->ops.tuner_ops.set_params) अणु
			fe->ops.tuner_ops.set_params(fe);
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (fe->ops.tuner_ops.calc_regs) अणु
		fe->ops.tuner_ops.calc_regs(fe, pllbuf + 1, 5);
		pllbuf[1] <<= 1;
		zl10353_ग_लिखो(fe, pllbuf, माप(pllbuf));
	पूर्ण

	zl10353_single_ग_लिखो(fe, 0x5F, 0x13);

	/* If no attached tuner or invalid PLL रेजिस्टरs, just start the FSM. */
	अगर (state->config.no_tuner || fe->ops.tuner_ops.calc_regs == शून्य)
		zl10353_single_ग_लिखो(fe, FSM_GO, 0x01);
	अन्यथा
		zl10353_single_ग_लिखो(fe, TUNER_GO, 0x01);

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_get_parameters(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	पूर्णांक s6, s9;
	u16 tps;
	अटल स्थिर u8 tps_fec_to_api[8] = अणु
		FEC_1_2,
		FEC_2_3,
		FEC_3_4,
		FEC_5_6,
		FEC_7_8,
		FEC_AUTO,
		FEC_AUTO,
		FEC_AUTO
	पूर्ण;

	s6 = zl10353_पढ़ो_रेजिस्टर(state, STATUS_6);
	s9 = zl10353_पढ़ो_रेजिस्टर(state, STATUS_9);
	अगर (s6 < 0 || s9 < 0)
		वापस -EREMOTEIO;
	अगर ((s6 & (1 << 5)) == 0 || (s9 & (1 << 4)) == 0)
		वापस -EINVAL;	/* no FE or TPS lock */

	tps = zl10353_पढ़ो_रेजिस्टर(state, TPS_RECEIVED_1) << 8 |
	      zl10353_पढ़ो_रेजिस्टर(state, TPS_RECEIVED_0);

	c->code_rate_HP = tps_fec_to_api[(tps >> 7) & 7];
	c->code_rate_LP = tps_fec_to_api[(tps >> 4) & 7];

	चयन ((tps >> 13) & 3) अणु
	हाल 0:
		c->modulation = QPSK;
		अवरोध;
	हाल 1:
		c->modulation = QAM_16;
		अवरोध;
	हाल 2:
		c->modulation = QAM_64;
		अवरोध;
	शेष:
		c->modulation = QAM_AUTO;
		अवरोध;
	पूर्ण

	c->transmission_mode = (tps & 0x01) ? TRANSMISSION_MODE_8K :
					       TRANSMISSION_MODE_2K;

	चयन ((tps >> 2) & 3) अणु
	हाल 0:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	शेष:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
		अवरोध;
	पूर्ण

	चयन ((tps >> 10) & 7) अणु
	हाल 0:
		c->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		c->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		c->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		c->hierarchy = HIERARCHY_4;
		अवरोध;
	शेष:
		c->hierarchy = HIERARCHY_AUTO;
		अवरोध;
	पूर्ण

	c->frequency = state->frequency;
	c->bandwidth_hz = state->bandwidth;
	c->inversion = INVERSION_AUTO;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	पूर्णांक s6, s7, s8;

	अगर ((s6 = zl10353_पढ़ो_रेजिस्टर(state, STATUS_6)) < 0)
		वापस -EREMOTEIO;
	अगर ((s7 = zl10353_पढ़ो_रेजिस्टर(state, STATUS_7)) < 0)
		वापस -EREMOTEIO;
	अगर ((s8 = zl10353_पढ़ो_रेजिस्टर(state, STATUS_8)) < 0)
		वापस -EREMOTEIO;

	*status = 0;
	अगर (s6 & (1 << 2))
		*status |= FE_HAS_CARRIER;
	अगर (s6 & (1 << 1))
		*status |= FE_HAS_VITERBI;
	अगर (s6 & (1 << 5))
		*status |= FE_HAS_LOCK;
	अगर (s7 & (1 << 4))
		*status |= FE_HAS_SYNC;
	अगर (s8 & (1 << 6))
		*status |= FE_HAS_SIGNAL;

	अगर ((*status & (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)) !=
	    (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;

	*ber = zl10353_पढ़ो_रेजिस्टर(state, RS_ERR_CNT_2) << 16 |
	       zl10353_पढ़ो_रेजिस्टर(state, RS_ERR_CNT_1) << 8 |
	       zl10353_पढ़ो_रेजिस्टर(state, RS_ERR_CNT_0);

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;

	u16 संकेत = zl10353_पढ़ो_रेजिस्टर(state, AGC_GAIN_1) << 10 |
		     zl10353_पढ़ो_रेजिस्टर(state, AGC_GAIN_0) << 2 | 3;

	*strength = ~संकेत;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u8 _snr;

	अगर (debug_regs)
		zl10353_dump_regs(fe);

	_snr = zl10353_पढ़ो_रेजिस्टर(state, SNR);
	*snr = 10 * _snr / 8;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u32 ubl = 0;

	ubl = zl10353_पढ़ो_रेजिस्टर(state, RS_UBC_1) << 8 |
	      zl10353_पढ़ो_रेजिस्टर(state, RS_UBC_0);

	state->ucblocks += ubl;
	*ucblocks = state->ucblocks;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings
					 *fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 1000;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u8 zl10353_reset_attach[6] = अणु 0x50, 0x03, 0x64, 0x46, 0x15, 0x0F पूर्ण;

	अगर (debug_regs)
		zl10353_dump_regs(fe);
	अगर (state->config.parallel_ts)
		zl10353_reset_attach[2] &= ~0x20;
	अगर (state->config.घड़ी_ctl_1)
		zl10353_reset_attach[3] = state->config.घड़ी_ctl_1;
	अगर (state->config.pll_0)
		zl10353_reset_attach[4] = state->config.pll_0;

	/* Do a "hard" reset अगर not alपढ़ोy करोne */
	अगर (zl10353_पढ़ो_रेजिस्टर(state, 0x50) != zl10353_reset_attach[1] ||
	    zl10353_पढ़ो_रेजिस्टर(state, 0x51) != zl10353_reset_attach[2]) अणु
		zl10353_ग_लिखो(fe, zl10353_reset_attach,
				   माप(zl10353_reset_attach));
		अगर (debug_regs)
			zl10353_dump_regs(fe);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zl10353_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	u8 val = 0x0a;

	अगर (state->config.disable_i2c_gate_ctrl) अणु
		/* No tuner attached to the पूर्णांकernal I2C bus */
		/* If set enable I2C bridge, the मुख्य I2C bus stopped hardly */
		वापस 0;
	पूर्ण

	अगर (enable)
		val |= 0x10;

	वापस zl10353_single_ग_लिखो(fe, 0x62, val);
पूर्ण

अटल व्योम zl10353_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा zl10353_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops zl10353_ops;

काष्ठा dvb_frontend *zl10353_attach(स्थिर काष्ठा zl10353_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा zl10353_state *state = शून्य;
	पूर्णांक id;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा zl10353_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	स_नकल(&state->config, config, माप(काष्ठा zl10353_config));

	/* check अगर the demod is there */
	id = zl10353_पढ़ो_रेजिस्टर(state, CHIP_ID);
	अगर ((id != ID_ZL10353) && (id != ID_CE6230) && (id != ID_CE6231))
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &zl10353_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	वापस &state->frontend;
error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops zl10353_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Zarlink ZL10353 DVB-T",
		.frequency_min_hz	= 174 * MHz,
		.frequency_max_hz	= 862 * MHz,
		.frequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO | FE_CAN_RECOVER |
			FE_CAN_MUTE_TS
	पूर्ण,

	.release = zl10353_release,

	.init = zl10353_init,
	.sleep = zl10353_sleep,
	.i2c_gate_ctrl = zl10353_i2c_gate_ctrl,
	.ग_लिखो = zl10353_ग_लिखो,

	.set_frontend = zl10353_set_parameters,
	.get_frontend = zl10353_get_parameters,
	.get_tune_settings = zl10353_get_tune_settings,

	.पढ़ो_status = zl10353_पढ़ो_status,
	.पढ़ो_ber = zl10353_पढ़ो_ber,
	.पढ़ो_संकेत_strength = zl10353_पढ़ो_संकेत_strength,
	.पढ़ो_snr = zl10353_पढ़ो_snr,
	.पढ़ो_ucblocks = zl10353_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

module_param(debug_regs, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_regs, "Turn on/off frontend register dumps (default:off).");

MODULE_DESCRIPTION("Zarlink ZL10353 DVB-T demodulator driver");
MODULE_AUTHOR("Chris Pascoe");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(zl10353_attach);
