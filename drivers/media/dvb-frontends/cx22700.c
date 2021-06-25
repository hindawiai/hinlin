<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Conexant cx22700 DVB OFDM demodulator driver

    Copyright (C) 2001-2002 Convergence Integrated Media GmbH
	Holger Waechtler <holger@convergence.de>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <media/dvb_frontend.h>
#समावेश "cx22700.h"


काष्ठा cx22700_state अणु

	काष्ठा i2c_adapter* i2c;

	स्थिर काष्ठा cx22700_config* config;

	काष्ठा dvb_frontend frontend;
पूर्ण;


अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "cx22700: " args); \
	पूर्ण जबतक (0)

अटल u8 init_tab [] = अणु
	0x04, 0x10,
	0x05, 0x09,
	0x06, 0x00,
	0x08, 0x04,
	0x09, 0x00,
	0x0a, 0x01,
	0x15, 0x40,
	0x16, 0x10,
	0x17, 0x87,
	0x18, 0x17,
	0x1a, 0x10,
	0x25, 0x04,
	0x2e, 0x00,
	0x39, 0x00,
	0x3a, 0x04,
	0x45, 0x08,
	0x46, 0x02,
	0x47, 0x05,
पूर्ण;


अटल पूर्णांक cx22700_ग_लिखोreg (काष्ठा cx22700_state* state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf [] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;

	dprपूर्णांकk ("%s\n", __func__);

	ret = i2c_transfer (state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk("%s: writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल पूर्णांक cx22700_पढ़ोreg (काष्ठा cx22700_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	dprपूर्णांकk ("%s\n", __func__);

	ret = i2c_transfer (state->i2c, msg, 2);

	अगर (ret != 2) वापस -EIO;

	वापस b1[0];
पूर्ण

अटल पूर्णांक cx22700_set_inversion (काष्ठा cx22700_state* state, पूर्णांक inversion)
अणु
	u8 val;

	dprपूर्णांकk ("%s\n", __func__);

	चयन (inversion) अणु
	हाल INVERSION_AUTO:
		वापस -EOPNOTSUPP;
	हाल INVERSION_ON:
		val = cx22700_पढ़ोreg (state, 0x09);
		वापस cx22700_ग_लिखोreg (state, 0x09, val | 0x01);
	हाल INVERSION_OFF:
		val = cx22700_पढ़ोreg (state, 0x09);
		वापस cx22700_ग_लिखोreg (state, 0x09, val & 0xfe);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक cx22700_set_tps(काष्ठा cx22700_state *state,
			   काष्ठा dtv_frontend_properties *p)
अणु
	अटल स्थिर u8 qam_tab [4] = अणु 0, 1, 0, 2 पूर्ण;
	अटल स्थिर u8 fec_tab [6] = अणु 0, 1, 2, 0, 3, 4 पूर्ण;
	u8 val;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (p->code_rate_HP < FEC_1_2 || p->code_rate_HP > FEC_7_8)
		वापस -EINVAL;

	अगर (p->code_rate_LP < FEC_1_2 || p->code_rate_LP > FEC_7_8)
		वापस -EINVAL;

	अगर (p->code_rate_HP == FEC_4_5 || p->code_rate_LP == FEC_4_5)
		वापस -EINVAL;

	अगर ((पूर्णांक)p->guard_पूर्णांकerval < GUARD_INTERVAL_1_32 ||
	    p->guard_पूर्णांकerval > GUARD_INTERVAL_1_4)
		वापस -EINVAL;

	अगर (p->transmission_mode != TRANSMISSION_MODE_2K &&
	    p->transmission_mode != TRANSMISSION_MODE_8K)
		वापस -EINVAL;

	अगर (p->modulation != QPSK &&
	    p->modulation != QAM_16 &&
	    p->modulation != QAM_64)
		वापस -EINVAL;

	अगर ((पूर्णांक)p->hierarchy < HIERARCHY_NONE ||
	    p->hierarchy > HIERARCHY_4)
		वापस -EINVAL;

	अगर (p->bandwidth_hz > 8000000 || p->bandwidth_hz < 6000000)
		वापस -EINVAL;

	अगर (p->bandwidth_hz == 7000000)
		cx22700_ग_लिखोreg (state, 0x09, cx22700_पढ़ोreg (state, 0x09 | 0x10));
	अन्यथा
		cx22700_ग_लिखोreg (state, 0x09, cx22700_पढ़ोreg (state, 0x09 & ~0x10));

	val = qam_tab[p->modulation - QPSK];
	val |= p->hierarchy - HIERARCHY_NONE;

	cx22700_ग_लिखोreg (state, 0x04, val);

	अगर (p->code_rate_HP - FEC_1_2 >= माप(fec_tab) ||
	    p->code_rate_LP - FEC_1_2 >= माप(fec_tab))
		वापस -EINVAL;
	val = fec_tab[p->code_rate_HP - FEC_1_2] << 3;
	val |= fec_tab[p->code_rate_LP - FEC_1_2];

	cx22700_ग_लिखोreg (state, 0x05, val);

	val = (p->guard_पूर्णांकerval - GUARD_INTERVAL_1_32) << 2;
	val |= p->transmission_mode - TRANSMISSION_MODE_2K;

	cx22700_ग_लिखोreg (state, 0x06, val);

	cx22700_ग_लिखोreg (state, 0x08, 0x04 | 0x02);  /* use user tps parameters */
	cx22700_ग_लिखोreg (state, 0x08, 0x04);         /* restart acquisition */

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_get_tps(काष्ठा cx22700_state *state,
			   काष्ठा dtv_frontend_properties *p)
अणु
	अटल स्थिर क्रमागत fe_modulation qam_tab[3] = अणु QPSK, QAM_16, QAM_64 पूर्ण;
	अटल स्थिर क्रमागत fe_code_rate fec_tab[5] = अणु
		FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8
	पूर्ण;
	u8 val;

	dprपूर्णांकk ("%s\n", __func__);

	अगर (!(cx22700_पढ़ोreg(state, 0x07) & 0x20))  /*  tps valid? */
		वापस -EAGAIN;

	val = cx22700_पढ़ोreg (state, 0x01);

	अगर ((val & 0x7) > 4)
		p->hierarchy = HIERARCHY_AUTO;
	अन्यथा
		p->hierarchy = HIERARCHY_NONE + (val & 0x7);

	अगर (((val >> 3) & 0x3) > 2)
		p->modulation = QAM_AUTO;
	अन्यथा
		p->modulation = qam_tab[(val >> 3) & 0x3];

	val = cx22700_पढ़ोreg (state, 0x02);

	अगर (((val >> 3) & 0x07) > 4)
		p->code_rate_HP = FEC_AUTO;
	अन्यथा
		p->code_rate_HP = fec_tab[(val >> 3) & 0x07];

	अगर ((val & 0x07) > 4)
		p->code_rate_LP = FEC_AUTO;
	अन्यथा
		p->code_rate_LP = fec_tab[val & 0x07];

	val = cx22700_पढ़ोreg (state, 0x03);

	p->guard_पूर्णांकerval = GUARD_INTERVAL_1_32 + ((val >> 6) & 0x3);
	p->transmission_mode = TRANSMISSION_MODE_2K + ((val >> 5) & 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_init (काष्ठा dvb_frontend* fe)

अणु	काष्ठा cx22700_state* state = fe->demodulator_priv;
	पूर्णांक i;

	dprपूर्णांकk("cx22700_init: init chip\n");

	cx22700_ग_लिखोreg (state, 0x00, 0x02);   /*  soft reset */
	cx22700_ग_लिखोreg (state, 0x00, 0x00);

	msleep(10);

	क्रम (i=0; i<माप(init_tab); i+=2)
		cx22700_ग_लिखोreg (state, init_tab[i], init_tab[i+1]);

	cx22700_ग_लिखोreg (state, 0x00, 0x01);

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	u16 rs_ber = (cx22700_पढ़ोreg (state, 0x0d) << 9)
		   | (cx22700_पढ़ोreg (state, 0x0e) << 1);
	u8 sync = cx22700_पढ़ोreg (state, 0x07);

	*status = 0;

	अगर (rs_ber < 0xff00)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 0x20)
		*status |= FE_HAS_CARRIER;

	अगर (sync & 0x10)
		*status |= FE_HAS_VITERBI;

	अगर (sync & 0x10)
		*status |= FE_HAS_SYNC;

	अगर (*status == 0x0f)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	*ber = cx22700_पढ़ोreg (state, 0x0c) & 0x7f;
	cx22700_ग_लिखोreg (state, 0x0c, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* संकेत_strength)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	u16 rs_ber = (cx22700_पढ़ोreg (state, 0x0d) << 9)
		   | (cx22700_पढ़ोreg (state, 0x0e) << 1);
	*संकेत_strength = ~rs_ber;

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	u16 rs_ber = (cx22700_पढ़ोreg (state, 0x0d) << 9)
		   | (cx22700_पढ़ोreg (state, 0x0e) << 1);
	*snr = ~rs_ber;

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	*ucblocks = cx22700_पढ़ोreg (state, 0x0f);
	cx22700_ग_लिखोreg (state, 0x0f, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	cx22700_ग_लिखोreg (state, 0x00, 0x02); /* XXX CHECKME: soft reset*/
	cx22700_ग_लिखोreg (state, 0x00, 0x00);

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	cx22700_set_inversion(state, c->inversion);
	cx22700_set_tps(state, c);
	cx22700_ग_लिखोreg (state, 0x37, 0x01);  /* PAL loop filter off */
	cx22700_ग_लिखोreg (state, 0x00, 0x01);  /* restart acquire */

	वापस 0;
पूर्ण

अटल पूर्णांक cx22700_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;
	u8 reg09 = cx22700_पढ़ोreg (state, 0x09);

	c->inversion = reg09 & 0x1 ? INVERSION_ON : INVERSION_OFF;
	वापस cx22700_get_tps(state, c);
पूर्ण

अटल पूर्णांक cx22700_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		वापस cx22700_ग_लिखोreg(state, 0x0a, 0x00);
	पूर्ण अन्यथा अणु
		वापस cx22700_ग_लिखोreg(state, 0x0a, 0x01);
	पूर्ण
पूर्ण

अटल पूर्णांक cx22700_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 150;
	fesettings->step_size = 166667;
	fesettings->max_drअगरt = 166667*2;
	वापस 0;
पूर्ण

अटल व्योम cx22700_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा cx22700_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx22700_ops;

काष्ठा dvb_frontend* cx22700_attach(स्थिर काष्ठा cx22700_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा cx22700_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा cx22700_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	अगर (cx22700_पढ़ोreg(state, 0x07) < 0) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &cx22700_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx22700_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Conexant CX22700 DVB-T",
		.frequency_min_hz	= 470 * MHz,
		.frequency_max_hz	= 860 * MHz,
		.frequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		      FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		      FE_CAN_RECOVER
	पूर्ण,

	.release = cx22700_release,

	.init = cx22700_init,
	.i2c_gate_ctrl = cx22700_i2c_gate_ctrl,

	.set_frontend = cx22700_set_frontend,
	.get_frontend = cx22700_get_frontend,
	.get_tune_settings = cx22700_get_tune_settings,

	.पढ़ो_status = cx22700_पढ़ो_status,
	.पढ़ो_ber = cx22700_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cx22700_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cx22700_पढ़ो_snr,
	.पढ़ो_ucblocks = cx22700_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Conexant CX22700 DVB-T Demodulator driver");
MODULE_AUTHOR("Holger Waechtler");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(cx22700_attach);
