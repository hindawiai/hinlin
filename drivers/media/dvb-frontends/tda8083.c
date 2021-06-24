<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम Philips TDA8083 based QPSK Demodulator

    Copyright (C) 2001 Convergence Integrated Media GmbH

    written by Ralph Metzler <ralph@convergence.de>

    aकरोption to the new DVB frontend API and diagnostic ioctl's
    by Holger Waechtler <holger@convergence.de>


*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <media/dvb_frontend.h>
#समावेश "tda8083.h"


काष्ठा tda8083_state अणु
	काष्ठा i2c_adapter* i2c;
	/* configuration settings */
	स्थिर काष्ठा tda8083_config* config;
	काष्ठा dvb_frontend frontend;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "tda8083: " args); \
	पूर्ण जबतक (0)


अटल u8 tda8083_init_tab [] = अणु
	0x04, 0x00, 0x4a, 0x79, 0x04, 0x00, 0xff, 0xea,
	0x48, 0x42, 0x79, 0x60, 0x70, 0x52, 0x9a, 0x10,
	0x0e, 0x10, 0xf2, 0xa7, 0x93, 0x0b, 0x05, 0xc8,
	0x9d, 0x00, 0x42, 0x80, 0x00, 0x60, 0x40, 0x00,
	0x00, 0x75, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
पूर्ण;


अटल पूर्णांक tda8083_ग_लिखोreg (काष्ठा tda8083_state* state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf [] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk ("%s: writereg error (reg %02x, ret == %i)\n",
			__func__, reg, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल पूर्णांक tda8083_पढ़ोregs (काष्ठा tda8083_state* state, u8 reg1, u8 *b, u8 len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = &reg1, .len = 1 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b, .len = len पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		dprपूर्णांकk ("%s: readreg error (reg %02x, ret == %i)\n",
			__func__, reg1, ret);

	वापस ret == 2 ? 0 : -1;
पूर्ण

अटल अंतरभूत u8 tda8083_पढ़ोreg (काष्ठा tda8083_state* state, u8 reg)
अणु
	u8 val;

	tda8083_पढ़ोregs (state, reg, &val, 1);

	वापस val;
पूर्ण

अटल पूर्णांक tda8083_set_inversion(काष्ठा tda8083_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
	/*  XXX FIXME: implement other modes than FEC_AUTO */
	अगर (inversion == INVERSION_AUTO)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tda8083_set_fec(काष्ठा tda8083_state *state, क्रमागत fe_code_rate fec)
अणु
	अगर (fec == FEC_AUTO)
		वापस tda8083_ग_लिखोreg (state, 0x07, 0xff);

	अगर (fec >= FEC_1_2 && fec <= FEC_8_9)
		वापस tda8083_ग_लिखोreg (state, 0x07, 1 << (FEC_8_9 - fec));

	वापस -EINVAL;
पूर्ण

अटल क्रमागत fe_code_rate tda8083_get_fec(काष्ठा tda8083_state *state)
अणु
	u8 index;
	अटल क्रमागत fe_code_rate fec_tab[] = अणु
		FEC_8_9, FEC_1_2, FEC_2_3, FEC_3_4,
		FEC_4_5, FEC_5_6, FEC_6_7, FEC_7_8
	पूर्ण;

	index = tda8083_पढ़ोreg(state, 0x0e) & 0x07;

	वापस fec_tab [index];
पूर्ण

अटल पूर्णांक tda8083_set_symbolrate (काष्ठा tda8083_state* state, u32 srate)
अणु
	u32 ratio;
	u32 पंचांगp;
	u8 filter;

	अगर (srate > 32000000)
		srate = 32000000;
	अगर (srate < 500000)
		srate = 500000;

	filter = 0;
	अगर (srate < 24000000)
		filter = 2;
	अगर (srate < 16000000)
		filter = 3;

	पंचांगp = 31250 << 16;
	ratio = पंचांगp / srate;

	पंचांगp = (पंचांगp % srate) << 8;
	ratio = (ratio << 8) + पंचांगp / srate;

	पंचांगp = (पंचांगp % srate) << 8;
	ratio = (ratio << 8) + पंचांगp / srate;

	dprपूर्णांकk("tda8083: ratio == %08x\n", (अचिन्हित पूर्णांक) ratio);

	tda8083_ग_लिखोreg (state, 0x05, filter);
	tda8083_ग_लिखोreg (state, 0x02, (ratio >> 16) & 0xff);
	tda8083_ग_लिखोreg (state, 0x03, (ratio >>  8) & 0xff);
	tda8083_ग_लिखोreg (state, 0x04, (ratio      ) & 0xff);

	tda8083_ग_लिखोreg (state, 0x00, 0x3c);
	tda8083_ग_लिखोreg (state, 0x00, 0x04);

	वापस 1;
पूर्ण

अटल व्योम tda8083_रुको_diseqc_fअगरo (काष्ठा tda8083_state* state, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक (jअगरfies - start < समयout &&
	       !(tda8083_पढ़ोreg(state, 0x02) & 0x80))
	अणु
		msleep(50);
	पूर्ण
पूर्ण

अटल पूर्णांक tda8083_set_tone(काष्ठा tda8083_state *state,
			    क्रमागत fe_sec_tone_mode tone)
अणु
	tda8083_ग_लिखोreg (state, 0x26, 0xf1);

	चयन (tone) अणु
	हाल SEC_TONE_OFF:
		वापस tda8083_ग_लिखोreg (state, 0x29, 0x00);
	हाल SEC_TONE_ON:
		वापस tda8083_ग_लिखोreg (state, 0x29, 0x80);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tda8083_set_voltage(काष्ठा tda8083_state *state,
			       क्रमागत fe_sec_voltage voltage)
अणु
	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		वापस tda8083_ग_लिखोreg (state, 0x20, 0x00);
	हाल SEC_VOLTAGE_18:
		वापस tda8083_ग_लिखोreg (state, 0x20, 0x11);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tda8083_send_diseqc_burst(काष्ठा tda8083_state *state,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	चयन (burst) अणु
	हाल SEC_MINI_A:
		tda8083_ग_लिखोreg (state, 0x29, (5 << 2));  /* send burst A */
		अवरोध;
	हाल SEC_MINI_B:
		tda8083_ग_लिखोreg (state, 0x29, (7 << 2));  /* send B */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	tda8083_रुको_diseqc_fअगरo (state, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				   काष्ठा dvb_diseqc_master_cmd *m)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;
	पूर्णांक i;

	tda8083_ग_लिखोreg (state, 0x29, (m->msg_len - 3) | (1 << 2)); /* enable */

	क्रम (i=0; i<m->msg_len; i++)
		tda8083_ग_लिखोreg (state, 0x23 + i, m->msg[i]);

	tda8083_ग_लिखोreg (state, 0x29, (m->msg_len - 3) | (3 << 2)); /* send!! */

	tda8083_रुको_diseqc_fअगरo (state, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_पढ़ो_status(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_status *status)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	u8 संकेत = ~tda8083_पढ़ोreg (state, 0x01);
	u8 sync = tda8083_पढ़ोreg (state, 0x02);

	*status = 0;

	अगर (संकेत > 10)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 0x01)
		*status |= FE_HAS_CARRIER;

	अगर (sync & 0x02)
		*status |= FE_HAS_VITERBI;

	अगर (sync & 0x10)
		*status |= FE_HAS_SYNC;

	अगर (sync & 0x20) /* frontend can not lock */
		*status |= FE_TIMEDOUT;

	अगर ((sync & 0x1f) == 0x1f)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[3];

	अगर ((ret = tda8083_पढ़ोregs(state, 0x0b, buf, माप(buf))))
		वापस ret;

	*ber = ((buf[0] & 0x1f) << 16) | (buf[1] << 8) | buf[2];

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	u8 संकेत = ~tda8083_पढ़ोreg (state, 0x01);
	*strength = (संकेत << 8) | संकेत;

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	u8 _snr = tda8083_पढ़ोreg (state, 0x08);
	*snr = (_snr << 8) | _snr;

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	*ucblocks = tda8083_पढ़ोreg(state, 0x0f);
	अगर (*ucblocks == 0xff)
		*ucblocks = 0xffffffff;

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	tda8083_set_inversion (state, p->inversion);
	tda8083_set_fec(state, p->fec_inner);
	tda8083_set_symbolrate(state, p->symbol_rate);

	tda8083_ग_लिखोreg (state, 0x00, 0x3c);
	tda8083_ग_लिखोreg (state, 0x00, 0x04);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	/*  FIXME: get symbolrate & frequency offset...*/
	/*p->frequency = ???;*/
	p->inversion = (tda8083_पढ़ोreg (state, 0x0e) & 0x80) ?
			INVERSION_ON : INVERSION_OFF;
	p->fec_inner = tda8083_get_fec(state);
	/*p->symbol_rate = tda8083_get_symbolrate (state);*/

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	tda8083_ग_लिखोreg (state, 0x00, 0x02);
	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;
	पूर्णांक i;

	क्रम (i=0; i<44; i++)
		tda8083_ग_लिखोreg (state, i, tda8083_init_tab[i]);

	tda8083_ग_लिखोreg (state, 0x00, 0x3c);
	tda8083_ग_लिखोreg (state, 0x00, 0x04);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	tda8083_send_diseqc_burst (state, burst);
	tda8083_ग_लिखोreg (state, 0x00, 0x3c);
	tda8083_ग_लिखोreg (state, 0x00, 0x04);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_diseqc_set_tone(काष्ठा dvb_frontend *fe,
				   क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	tda8083_set_tone (state, tone);
	tda8083_ग_लिखोreg (state, 0x00, 0x3c);
	tda8083_ग_लिखोreg (state, 0x00, 0x04);

	वापस 0;
पूर्ण

अटल पूर्णांक tda8083_diseqc_set_voltage(काष्ठा dvb_frontend *fe,
				      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;

	tda8083_set_voltage (state, voltage);
	tda8083_ग_लिखोreg (state, 0x00, 0x3c);
	tda8083_ग_लिखोreg (state, 0x00, 0x04);

	वापस 0;
पूर्ण

अटल व्योम tda8083_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda8083_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda8083_ops;

काष्ठा dvb_frontend* tda8083_attach(स्थिर काष्ठा tda8083_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा tda8083_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda8083_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	अगर ((tda8083_पढ़ोreg(state, 0x00)) != 0x05) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda8083_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda8083_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "Philips TDA8083 DVB-S",
		.frequency_min_hz	=  920 * MHz,     /* TDA8060 */
		.frequency_max_hz	= 2200 * MHz,    /* TDA8060 */
		.frequency_stepsize_hz	=  125 * kHz,
		.symbol_rate_min	= 12000000,
		.symbol_rate_max	= 30000000,
	/*      .symbol_rate_tolerance	= ???,*/
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_8_9 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_MUTE_TS
	पूर्ण,

	.release = tda8083_release,

	.init = tda8083_init,
	.sleep = tda8083_sleep,

	.set_frontend = tda8083_set_frontend,
	.get_frontend = tda8083_get_frontend,

	.पढ़ो_status = tda8083_पढ़ो_status,
	.पढ़ो_संकेत_strength = tda8083_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda8083_पढ़ो_snr,
	.पढ़ो_ber = tda8083_पढ़ो_ber,
	.पढ़ो_ucblocks = tda8083_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = tda8083_send_diseqc_msg,
	.diseqc_send_burst = tda8083_diseqc_send_burst,
	.set_tone = tda8083_diseqc_set_tone,
	.set_voltage = tda8083_diseqc_set_voltage,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Philips TDA8083 DVB-S Demodulator");
MODULE_AUTHOR("Ralph Metzler, Holger Waechtler");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(tda8083_attach);
