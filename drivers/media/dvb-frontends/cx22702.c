<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Conexant 22702 DVB OFDM demodulator driver

    based on:
	Alps TDMB7 DVB OFDM demodulator driver

    Copyright (C) 2001-2002 Convergence Integrated Media GmbH
	  Holger Waechtler <holger@convergence.de>

    Copyright (C) 2004 Steven Toth <stoth@linuxtv.org>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <media/dvb_frontend.h>
#समावेश "cx22702.h"

काष्ठा cx22702_state अणु

	काष्ठा i2c_adapter *i2c;

	/* configuration settings */
	स्थिर काष्ठा cx22702_config *config;

	काष्ठा dvb_frontend frontend;

	/* previous uncorrected block counter */
	u8 prevUCBlocks;
पूर्ण;

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

#घोषणा dprपूर्णांकk	अगर (debug) prपूर्णांकk

/* Register values to initialise the demod */
अटल स्थिर u8 init_tab[] = अणु
	0x00, 0x00, /* Stop acquisition */
	0x0B, 0x06,
	0x09, 0x01,
	0x0D, 0x41,
	0x16, 0x32,
	0x20, 0x0A,
	0x21, 0x17,
	0x24, 0x3e,
	0x26, 0xff,
	0x27, 0x10,
	0x28, 0x00,
	0x29, 0x00,
	0x2a, 0x10,
	0x2b, 0x00,
	0x2c, 0x10,
	0x2d, 0x00,
	0x48, 0xd4,
	0x49, 0x56,
	0x6b, 0x1e,
	0xc8, 0x02,
	0xf9, 0x00,
	0xfa, 0x00,
	0xfb, 0x00,
	0xfc, 0x00,
	0xfd, 0x00,
पूर्ण;

अटल पूर्णांक cx22702_ग_लिखोreg(काष्ठा cx22702_state *state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_address, .flags = 0,
			.buf = buf, .len = 2 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (unlikely(ret != 1)) अणु
		prपूर्णांकk(KERN_ERR
			"%s: error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 cx22702_पढ़ोreg(काष्ठा cx22702_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 data;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config->demod_address, .flags = 0,
			.buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->config->demod_address, .flags = I2C_M_RD,
			.buf = &data, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (unlikely(ret != 2)) अणु
		prपूर्णांकk(KERN_ERR "%s: error (reg == 0x%02x, ret == %i)\n",
			__func__, reg, ret);
		वापस 0;
	पूर्ण

	वापस data;
पूर्ण

अटल पूर्णांक cx22702_set_inversion(काष्ठा cx22702_state *state, पूर्णांक inversion)
अणु
	u8 val;

	val = cx22702_पढ़ोreg(state, 0x0C);
	चयन (inversion) अणु
	हाल INVERSION_AUTO:
		वापस -EOPNOTSUPP;
	हाल INVERSION_ON:
		val |= 0x01;
		अवरोध;
	हाल INVERSION_OFF:
		val &= 0xfe;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस cx22702_ग_लिखोreg(state, 0x0C, val);
पूर्ण

/* Retrieve the demod settings */
अटल पूर्णांक cx22702_get_tps(काष्ठा cx22702_state *state,
			   काष्ठा dtv_frontend_properties *p)
अणु
	u8 val;

	/* Make sure the TPS regs are valid */
	अगर (!(cx22702_पढ़ोreg(state, 0x0A) & 0x20))
		वापस -EAGAIN;

	val = cx22702_पढ़ोreg(state, 0x01);
	चयन ((val & 0x18) >> 3) अणु
	हाल 0:
		p->modulation = QPSK;
		अवरोध;
	हाल 1:
		p->modulation = QAM_16;
		अवरोध;
	हाल 2:
		p->modulation = QAM_64;
		अवरोध;
	पूर्ण
	चयन (val & 0x07) अणु
	हाल 0:
		p->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		p->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		p->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		p->hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण


	val = cx22702_पढ़ोreg(state, 0x02);
	चयन ((val & 0x38) >> 3) अणु
	हाल 0:
		p->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 1:
		p->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 2:
		p->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 3:
		p->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 4:
		p->code_rate_HP = FEC_7_8;
		अवरोध;
	पूर्ण
	चयन (val & 0x07) अणु
	हाल 0:
		p->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 1:
		p->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 2:
		p->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 3:
		p->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 4:
		p->code_rate_LP = FEC_7_8;
		अवरोध;
	पूर्ण

	val = cx22702_पढ़ोreg(state, 0x03);
	चयन ((val & 0x0c) >> 2) अणु
	हाल 0:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण
	चयन (val & 0x03) अणु
	हाल 0:
		p->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		p->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);
	val = cx22702_पढ़ोreg(state, 0x0D);
	अगर (enable)
		val &= 0xfe;
	अन्यथा
		val |= 0x01;
	वापस cx22702_ग_लिखोreg(state, 0x0D, val);
पूर्ण

/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
अटल पूर्णांक cx22702_set_tps(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u8 val;
	काष्ठा cx22702_state *state = fe->demodulator_priv;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* set inversion */
	cx22702_set_inversion(state, p->inversion);

	/* set bandwidth */
	val = cx22702_पढ़ोreg(state, 0x0C) & 0xcf;
	चयन (p->bandwidth_hz) अणु
	हाल 6000000:
		val |= 0x20;
		अवरोध;
	हाल 7000000:
		val |= 0x10;
		अवरोध;
	हाल 8000000:
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid bandwidth\n", __func__);
		वापस -EINVAL;
	पूर्ण
	cx22702_ग_लिखोreg(state, 0x0C, val);

	p->code_rate_LP = FEC_AUTO; /* temp hack as manual not working */

	/* use स्वतः configuration? */
	अगर ((p->hierarchy == HIERARCHY_AUTO) ||
	   (p->modulation == QAM_AUTO) ||
	   (p->code_rate_HP == FEC_AUTO) ||
	   (p->code_rate_LP == FEC_AUTO) ||
	   (p->guard_पूर्णांकerval == GUARD_INTERVAL_AUTO) ||
	   (p->transmission_mode == TRANSMISSION_MODE_AUTO)) अणु

		/* TPS Source - use hardware driven values */
		cx22702_ग_लिखोreg(state, 0x06, 0x10);
		cx22702_ग_लिखोreg(state, 0x07, 0x9);
		cx22702_ग_लिखोreg(state, 0x08, 0xC1);
		cx22702_ग_लिखोreg(state, 0x0B, cx22702_पढ़ोreg(state, 0x0B)
			& 0xfc);
		cx22702_ग_लिखोreg(state, 0x0C,
			(cx22702_पढ़ोreg(state, 0x0C) & 0xBF) | 0x40);
		cx22702_ग_लिखोreg(state, 0x00, 0x01); /* Begin acquisition */
		dprपूर्णांकk("%s: Autodetecting\n", __func__);
		वापस 0;
	पूर्ण

	/* manually programmed values */
	चयन (p->modulation) अणु		/* mask 0x18 */
	हाल QPSK:
		val = 0x00;
		अवरोध;
	हाल QAM_16:
		val = 0x08;
		अवरोध;
	हाल QAM_64:
		val = 0x10;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid modulation\n", __func__);
		वापस -EINVAL;
	पूर्ण
	चयन (p->hierarchy) अणु	/* mask 0x07 */
	हाल HIERARCHY_NONE:
		अवरोध;
	हाल HIERARCHY_1:
		val |= 0x01;
		अवरोध;
	हाल HIERARCHY_2:
		val |= 0x02;
		अवरोध;
	हाल HIERARCHY_4:
		val |= 0x03;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid hierarchy\n", __func__);
		वापस -EINVAL;
	पूर्ण
	cx22702_ग_लिखोreg(state, 0x06, val);

	चयन (p->code_rate_HP) अणु		/* mask 0x38 */
	हाल FEC_NONE:
	हाल FEC_1_2:
		val = 0x00;
		अवरोध;
	हाल FEC_2_3:
		val = 0x08;
		अवरोध;
	हाल FEC_3_4:
		val = 0x10;
		अवरोध;
	हाल FEC_5_6:
		val = 0x18;
		अवरोध;
	हाल FEC_7_8:
		val = 0x20;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid code_rate_HP\n", __func__);
		वापस -EINVAL;
	पूर्ण
	चयन (p->code_rate_LP) अणु		/* mask 0x07 */
	हाल FEC_NONE:
	हाल FEC_1_2:
		अवरोध;
	हाल FEC_2_3:
		val |= 0x01;
		अवरोध;
	हाल FEC_3_4:
		val |= 0x02;
		अवरोध;
	हाल FEC_5_6:
		val |= 0x03;
		अवरोध;
	हाल FEC_7_8:
		val |= 0x04;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid code_rate_LP\n", __func__);
		वापस -EINVAL;
	पूर्ण
	cx22702_ग_लिखोreg(state, 0x07, val);

	चयन (p->guard_पूर्णांकerval) अणु		/* mask 0x0c */
	हाल GUARD_INTERVAL_1_32:
		val = 0x00;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		val = 0x04;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		val = 0x08;
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		val = 0x0c;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid guard_interval\n", __func__);
		वापस -EINVAL;
	पूर्ण
	चयन (p->transmission_mode) अणु		/* mask 0x03 */
	हाल TRANSMISSION_MODE_2K:
		अवरोध;
	हाल TRANSMISSION_MODE_8K:
		val |= 0x1;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid transmission_mode\n", __func__);
		वापस -EINVAL;
	पूर्ण
	cx22702_ग_लिखोreg(state, 0x08, val);
	cx22702_ग_लिखोreg(state, 0x0B,
		(cx22702_पढ़ोreg(state, 0x0B) & 0xfc) | 0x02);
	cx22702_ग_लिखोreg(state, 0x0C,
		(cx22702_पढ़ोreg(state, 0x0C) & 0xBF) | 0x40);

	/* Begin channel acquisition */
	cx22702_ग_लिखोreg(state, 0x00, 0x01);

	वापस 0;
पूर्ण

/* Reset the demod hardware and reset all of the configuration रेजिस्टरs
   to a शेष state. */
अटल पूर्णांक cx22702_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक i;
	काष्ठा cx22702_state *state = fe->demodulator_priv;

	cx22702_ग_लिखोreg(state, 0x00, 0x02);

	msleep(10);

	क्रम (i = 0; i < ARRAY_SIZE(init_tab); i += 2)
		cx22702_ग_लिखोreg(state, init_tab[i], init_tab[i + 1]);

	cx22702_ग_लिखोreg(state, 0xf8, (state->config->output_mode << 1)
		& 0x02);

	cx22702_i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;
	u8 reg0A;
	u8 reg23;

	*status = 0;

	reg0A = cx22702_पढ़ोreg(state, 0x0A);
	reg23 = cx22702_पढ़ोreg(state, 0x23);

	dprपूर्णांकk("%s: status demod=0x%02x agc=0x%02x\n"
		, __func__, reg0A, reg23);

	अगर (reg0A & 0x10) अणु
		*status |= FE_HAS_LOCK;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
	पूर्ण

	अगर (reg0A & 0x20)
		*status |= FE_HAS_CARRIER;

	अगर (reg23 < 0xf0)
		*status |= FE_HAS_SIGNAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;

	अगर (cx22702_पढ़ोreg(state, 0xE4) & 0x02) अणु
		/* Realसमय statistics */
		*ber = (cx22702_पढ़ोreg(state, 0xDE) & 0x7F) << 7
			| (cx22702_पढ़ोreg(state, 0xDF) & 0x7F);
	पूर्ण अन्यथा अणु
		/* Averagtine statistics */
		*ber = (cx22702_पढ़ोreg(state, 0xDE) & 0x7F) << 7
			| cx22702_पढ़ोreg(state, 0xDF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *संकेत_strength)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;
	u8 reg23;

	/*
	 * Experience suggests that the strength संकेत रेजिस्टर works as
	 * follows:
	 * - In the असलence of संकेत, value is 0xff.
	 * - In the presence of a weak संकेत, bit 7 is set, not sure what
	 *   the lower 7 bits mean.
	 * - In the presence of a strong संकेत, the रेजिस्टर holds a 7-bit
	 *   value (bit 7 is cleared), with greater values standing क्रम
	 *   weaker संकेतs.
	 */
	reg23 = cx22702_पढ़ोreg(state, 0x23);
	अगर (reg23 & 0x80) अणु
		*संकेत_strength = 0;
	पूर्ण अन्यथा अणु
		reg23 = ~reg23 & 0x7f;
		/* Scale to 16 bit */
		*संकेत_strength = (reg23 << 9) | (reg23 << 2) | (reg23 >> 5);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;

	u16 rs_ber;
	अगर (cx22702_पढ़ोreg(state, 0xE4) & 0x02) अणु
		/* Realसमय statistics */
		rs_ber = (cx22702_पढ़ोreg(state, 0xDE) & 0x7F) << 7
			| (cx22702_पढ़ोreg(state, 0xDF) & 0x7F);
	पूर्ण अन्यथा अणु
		/* Averagine statistics */
		rs_ber = (cx22702_पढ़ोreg(state, 0xDE) & 0x7F) << 8
			| cx22702_पढ़ोreg(state, 0xDF);
	पूर्ण
	*snr = ~rs_ber;

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;

	u8 _ucblocks;

	/* RS Uncorrectable Packet Count then reset */
	_ucblocks = cx22702_पढ़ोreg(state, 0xE3);
	अगर (state->prevUCBlocks < _ucblocks)
		*ucblocks = (_ucblocks - state->prevUCBlocks);
	अन्यथा
		*ucblocks = state->prevUCBlocks - _ucblocks;
	state->prevUCBlocks = _ucblocks;

	वापस 0;
पूर्ण

अटल पूर्णांक cx22702_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;

	u8 reg0C = cx22702_पढ़ोreg(state, 0x0C);

	c->inversion = reg0C & 0x1 ? INVERSION_ON : INVERSION_OFF;
	वापस cx22702_get_tps(state, c);
पूर्ण

अटल पूर्णांक cx22702_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम cx22702_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx22702_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx22702_ops;

काष्ठा dvb_frontend *cx22702_attach(स्थिर काष्ठा cx22702_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा cx22702_state *state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा cx22702_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	अगर (cx22702_पढ़ोreg(state, 0x1f) != 0x3)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &cx22702_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(cx22702_attach);

अटल स्थिर काष्ठा dvb_frontend_ops cx22702_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Conexant CX22702 DVB-T",
		.frequency_min_hz	= 177 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		FE_CAN_HIERARCHY_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
		FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_RECOVER
	पूर्ण,

	.release = cx22702_release,

	.init = cx22702_init,
	.i2c_gate_ctrl = cx22702_i2c_gate_ctrl,

	.set_frontend = cx22702_set_tps,
	.get_frontend = cx22702_get_frontend,
	.get_tune_settings = cx22702_get_tune_settings,

	.पढ़ो_status = cx22702_पढ़ो_status,
	.पढ़ो_ber = cx22702_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cx22702_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cx22702_पढ़ो_snr,
	.पढ़ो_ucblocks = cx22702_पढ़ो_ucblocks,
पूर्ण;

MODULE_DESCRIPTION("Conexant CX22702 DVB-T Demodulator driver");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");
