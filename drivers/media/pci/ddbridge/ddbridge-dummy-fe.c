<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Dummy Frontend
 *
 *  Written by Emard <emard@softhome.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "ddbridge-dummy-fe.h"

काष्ठा ddbridge_dummy_fe_state अणु
	काष्ठा dvb_frontend frontend;
पूर्ण;

अटल पूर्णांक ddbridge_dummy_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_status *status)
अणु
	*status = FE_HAS_SIGNAL
		| FE_HAS_CARRIER
		| FE_HAS_VITERBI
		| FE_HAS_SYNC
		| FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	*ber = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					     u16 *strength)
अणु
	*strength = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	*snr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	*ucblocks = 0;
	वापस 0;
पूर्ण

/*
 * Should only be implemented अगर it actually पढ़ोs something from the hardware.
 * Also, it should check क्रम the locks, in order to aव्योम report wrong data
 * to userspace.
 */
अटल पूर्णांक ddbridge_dummy_fe_get_frontend(काष्ठा dvb_frontend *fe,
				     काष्ठा dtv_frontend_properties *p)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ddbridge_dummy_fe_init(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल व्योम ddbridge_dummy_fe_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ddbridge_dummy_fe_state *state = fe->demodulator_priv;

	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ddbridge_dummy_fe_qam_ops;

काष्ठा dvb_frontend *ddbridge_dummy_fe_qam_attach(व्योम)
अणु
	काष्ठा ddbridge_dummy_fe_state *state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा ddbridge_dummy_fe_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops,
	       &ddbridge_dummy_fe_qam_ops,
	       माप(काष्ठा dvb_frontend_ops));

	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(ddbridge_dummy_fe_qam_attach);

अटल स्थिर काष्ठा dvb_frontend_ops ddbridge_dummy_fe_qam_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A पूर्ण,
	.info = अणु
		.name			= "ddbridge dummy DVB-C",
		.frequency_min_hz	=  51 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 62500,
		/* symbol_rate_min: SACLK/64 == (XIN/2)/64 */
		.symbol_rate_min	= (57840000 / 2) / 64,
		.symbol_rate_max	= (57840000 / 2) / 4,   /* SACLK/4 */
		.caps = FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO |
			FE_CAN_INVERSION_AUTO
	पूर्ण,

	.release = ddbridge_dummy_fe_release,

	.init = ddbridge_dummy_fe_init,
	.sleep = ddbridge_dummy_fe_sleep,

	.set_frontend = ddbridge_dummy_fe_set_frontend,
	.get_frontend = ddbridge_dummy_fe_get_frontend,

	.पढ़ो_status = ddbridge_dummy_fe_पढ़ो_status,
	.पढ़ो_ber = ddbridge_dummy_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength = ddbridge_dummy_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr = ddbridge_dummy_fe_पढ़ो_snr,
	.पढ़ो_ucblocks = ddbridge_dummy_fe_पढ़ो_ucblocks,
पूर्ण;

MODULE_DESCRIPTION("ddbridge dummy Frontend");
MODULE_AUTHOR("Emard");
MODULE_LICENSE("GPL");
