<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Driver क्रम ST STV0288 demodulator
	Copyright (C) 2006 Georg Acher, BayCom GmbH, acher (at) baycom (करोt) de
		क्रम Reel Mulसमयdia
	Copyright (C) 2008 TurboSight.com, Bob Liu <bob@turbosight.com>
	Copyright (C) 2008 Igor M. Liplianin <liplianin@me.by>
		Removed stb6000 specअगरic tuner code and revised some
		procedures.
	2010-09-01 Josef Pavlik <josef@pavlik.it>
		Fixed diseqc_msg, diseqc_burst and set_tone problems


*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "stv0288.h"

काष्ठा stv0288_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा stv0288_config *config;
	काष्ठा dvb_frontend frontend;

	u8 initialised:1;
	u32 tuner_frequency;
	u32 symbol_rate;
	क्रमागत fe_code_rate fec_inner;
	पूर्णांक errmode;
पूर्ण;

#घोषणा STATUS_BER 0
#घोषणा STATUS_UCBLOCKS 1

अटल पूर्णांक debug;
अटल पूर्णांक debug_legacy_dish_चयन;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "stv0288: " args); \
	पूर्ण जबतक (0)


अटल पूर्णांक stv0288_ग_लिखोregI(काष्ठा stv0288_state *state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_address,
		.flags = 0,
		.buf = buf,
		.len = 2
	पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक stv0288_ग_लिखो(काष्ठा dvb_frontend *fe, स्थिर u8 buf[], पूर्णांक len)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	अगर (len != 2)
		वापस -EINVAL;

	वापस stv0288_ग_लिखोregI(state, buf[0], buf[1]);
पूर्ण

अटल u8 stv0288_पढ़ोreg(काष्ठा stv0288_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->demod_address,
			.flags = 0,
			.buf = b0,
			.len = 1
		पूर्ण, अणु
			.addr = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		dprपूर्णांकk("%s: readreg error (reg == 0x%02x, ret == %i)\n",
				__func__, reg, ret);

	वापस b1[0];
पूर्ण

अटल पूर्णांक stv0288_set_symbolrate(काष्ठा dvb_frontend *fe, u32 srate)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;
	अचिन्हित पूर्णांक temp;
	अचिन्हित अक्षर b[3];

	अगर ((srate < 1000000) || (srate > 45000000))
		वापस -EINVAL;

	stv0288_ग_लिखोregI(state, 0x22, 0);
	stv0288_ग_लिखोregI(state, 0x23, 0);
	stv0288_ग_लिखोregI(state, 0x2b, 0xff);
	stv0288_ग_लिखोregI(state, 0x2c, 0xf7);

	temp = (अचिन्हित पूर्णांक)srate / 1000;

	temp = temp * 32768;
	temp = temp / 25;
	temp = temp / 125;
	b[0] = (अचिन्हित अक्षर)((temp >> 12) & 0xff);
	b[1] = (अचिन्हित अक्षर)((temp >> 4) & 0xff);
	b[2] = (अचिन्हित अक्षर)((temp << 4) & 0xf0);
	stv0288_ग_लिखोregI(state, 0x28, 0x80); /* SFRH */
	stv0288_ग_लिखोregI(state, 0x29, 0); /* SFRM */
	stv0288_ग_लिखोregI(state, 0x2a, 0); /* SFRL */

	stv0288_ग_लिखोregI(state, 0x28, b[0]);
	stv0288_ग_लिखोregI(state, 0x29, b[1]);
	stv0288_ग_लिखोregI(state, 0x2a, b[2]);
	dprपूर्णांकk("stv0288: stv0288_set_symbolrate\n");

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_diseqc_master_cmd *m)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	stv0288_ग_लिखोregI(state, 0x09, 0);
	msleep(30);
	stv0288_ग_लिखोregI(state, 0x05, 0x12);/* modulated mode, single shot */

	क्रम (i = 0; i < m->msg_len; i++) अणु
		अगर (stv0288_ग_लिखोregI(state, 0x06, m->msg[i]))
			वापस -EREMOTEIO;
	पूर्ण
	msleep(m->msg_len*12);
	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (stv0288_ग_लिखोregI(state, 0x05, 0x03))/* burst mode, single shot */
		वापस -EREMOTEIO;

	अगर (stv0288_ग_लिखोregI(state, 0x06, burst == SEC_MINI_A ? 0x00 : 0xff))
		वापस -EREMOTEIO;

	msleep(15);
	अगर (stv0288_ग_लिखोregI(state, 0x05, 0x12))
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		अगर (stv0288_ग_लिखोregI(state, 0x05, 0x10))/* cont carrier */
			वापस -EREMOTEIO;
	अवरोध;

	हाल SEC_TONE_OFF:
		अगर (stv0288_ग_लिखोregI(state, 0x05, 0x12))/* burst mode off*/
			वापस -EREMOTEIO;
	अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 stv0288_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x20,
	0x09, 0x0,
	0x0a, 0x4,
	0x0b, 0x0,
	0x0c, 0x0,
	0x0d, 0x0,
	0x0e, 0xd4,
	0x0f, 0x30,
	0x11, 0x80,
	0x12, 0x03,
	0x13, 0x48,
	0x14, 0x84,
	0x15, 0x45,
	0x16, 0xb7,
	0x17, 0x9c,
	0x18, 0x0,
	0x19, 0xa6,
	0x1a, 0x88,
	0x1b, 0x8f,
	0x1c, 0xf0,
	0x20, 0x0b,
	0x21, 0x54,
	0x22, 0x0,
	0x23, 0x0,
	0x2b, 0xff,
	0x2c, 0xf7,
	0x30, 0x0,
	0x31, 0x1e,
	0x32, 0x14,
	0x33, 0x0f,
	0x34, 0x09,
	0x35, 0x0c,
	0x36, 0x05,
	0x37, 0x2f,
	0x38, 0x16,
	0x39, 0xbe,
	0x3a, 0x0,
	0x3b, 0x13,
	0x3c, 0x11,
	0x3d, 0x30,
	0x40, 0x63,
	0x41, 0x04,
	0x42, 0x20,
	0x43, 0x00,
	0x44, 0x00,
	0x45, 0x00,
	0x46, 0x00,
	0x47, 0x00,
	0x4a, 0x00,
	0x50, 0x10,
	0x51, 0x38,
	0x52, 0x21,
	0x58, 0x54,
	0x59, 0x86,
	0x5a, 0x0,
	0x5b, 0x9b,
	0x5c, 0x08,
	0x5d, 0x7f,
	0x5e, 0x0,
	0x5f, 0xff,
	0x70, 0x0,
	0x71, 0x0,
	0x72, 0x0,
	0x74, 0x0,
	0x75, 0x0,
	0x76, 0x0,
	0x81, 0x0,
	0x82, 0x3f,
	0x83, 0x3f,
	0x84, 0x0,
	0x85, 0x0,
	0x88, 0x0,
	0x89, 0x0,
	0x8a, 0x0,
	0x8b, 0x0,
	0x8c, 0x0,
	0x90, 0x0,
	0x91, 0x0,
	0x92, 0x0,
	0x93, 0x0,
	0x94, 0x1c,
	0x97, 0x0,
	0xa0, 0x48,
	0xa1, 0x0,
	0xb0, 0xb8,
	0xb1, 0x3a,
	0xb2, 0x10,
	0xb3, 0x82,
	0xb4, 0x80,
	0xb5, 0x82,
	0xb6, 0x82,
	0xb7, 0x82,
	0xb8, 0x20,
	0xb9, 0x0,
	0xf0, 0x0,
	0xf1, 0x0,
	0xf2, 0xc0,
	0x51, 0x36,
	0x52, 0x09,
	0x53, 0x94,
	0x54, 0x62,
	0x55, 0x29,
	0x56, 0x64,
	0x57, 0x2b,
	0xff, 0xff,
पूर्ण;

अटल पूर्णांक stv0288_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage volt)
अणु
	dprपूर्णांकk("%s: %s\n", __func__,
		volt == SEC_VOLTAGE_13 ? "SEC_VOLTAGE_13" :
		volt == SEC_VOLTAGE_18 ? "SEC_VOLTAGE_18" : "??");

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;
	पूर्णांक i;
	u8 reg;
	u8 val;

	dprपूर्णांकk("stv0288: init chip\n");
	stv0288_ग_लिखोregI(state, 0x41, 0x04);
	msleep(50);

	/* we have शेष inittab */
	अगर (state->config->inittab == शून्य) अणु
		क्रम (i = 0; !(stv0288_inittab[i] == 0xff &&
				stv0288_inittab[i + 1] == 0xff); i += 2)
			stv0288_ग_लिखोregI(state, stv0288_inittab[i],
					stv0288_inittab[i + 1]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; ; i += 2)  अणु
			reg = state->config->inittab[i];
			val = state->config->inittab[i+1];
			अगर (reg == 0xff && val == 0xff)
				अवरोध;
			stv0288_ग_लिखोregI(state, reg, val);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	u8 sync = stv0288_पढ़ोreg(state, 0x24);
	अगर (sync == 255)
		sync = 0;

	dprपूर्णांकk("%s : FE_READ_STATUS : VSTATUS: 0x%02x\n", __func__, sync);

	*status = 0;
	अगर (sync & 0x80)
		*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
	अगर (sync & 0x10)
		*status |= FE_HAS_VITERBI;
	अगर (sync & 0x08) अणु
		*status |= FE_HAS_LOCK;
		dprपूर्णांकk("stv0288 has locked\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	अगर (state->errmode != STATUS_BER)
		वापस 0;
	*ber = (stv0288_पढ़ोreg(state, 0x26) << 8) |
					stv0288_पढ़ोreg(state, 0x27);
	dprपूर्णांकk("stv0288_read_ber %d\n", *ber);

	वापस 0;
पूर्ण


अटल पूर्णांक stv0288_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	s32 संकेत =  0xffff - ((stv0288_पढ़ोreg(state, 0x10) << 8));


	संकेत = संकेत * 5 / 4;
	*strength = (संकेत > 0xffff) ? 0xffff : (संकेत < 0) ? 0 : संकेत;
	dprपूर्णांकk("stv0288_read_signal_strength %d\n", *strength);

	वापस 0;
पूर्ण
अटल पूर्णांक stv0288_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	stv0288_ग_लिखोregI(state, 0x41, 0x84);
	state->initialised = 0;

	वापस 0;
पूर्ण
अटल पूर्णांक stv0288_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	s32 xsnr = 0xffff - ((stv0288_पढ़ोreg(state, 0x2d) << 8)
			   | stv0288_पढ़ोreg(state, 0x2e));
	xsnr = 3 * (xsnr - 0xa100);
	*snr = (xsnr > 0xffff) ? 0xffff : (xsnr < 0) ? 0 : xsnr;
	dprपूर्णांकk("stv0288_read_snr %d\n", *snr);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	अगर (state->errmode != STATUS_BER)
		वापस 0;
	*ucblocks = (stv0288_पढ़ोreg(state, 0x26) << 8) |
					stv0288_पढ़ोreg(state, 0x27);
	dprपूर्णांकk("stv0288_read_ber %d\n", *ucblocks);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अक्षर पंचांग;
	अचिन्हित अक्षर tda[3];
	u8 reg, समय_out = 0;

	dprपूर्णांकk("%s : FE_SET_FRONTEND\n", __func__);

	अगर (c->delivery_प्रणाली != SYS_DVBS) अणु
		dprपूर्णांकk("%s: unsupported delivery system selected (%d)\n",
			__func__, c->delivery_प्रणाली);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);

	/* only frequency & symbol_rate are used क्रम tuner*/
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	udelay(10);
	stv0288_set_symbolrate(fe, c->symbol_rate);
	/* Carrier lock control रेजिस्टर */
	stv0288_ग_लिखोregI(state, 0x15, 0xc5);

	tda[2] = 0x0; /* CFRL */
	क्रम (पंचांग = -9; पंचांग < 7;) अणु
		/* Viterbi status */
		reg = stv0288_पढ़ोreg(state, 0x24);
		अगर (reg & 0x8)
				अवरोध;
		अगर (reg & 0x80) अणु
			समय_out++;
			अगर (समय_out > 10)
				अवरोध;
			tda[2] += 40;
			अगर (tda[2] < 40)
				पंचांग++;
		पूर्ण अन्यथा अणु
			पंचांग++;
			tda[2] = 0;
			समय_out = 0;
		पूर्ण
		tda[1] = (अचिन्हित अक्षर)पंचांग;
		stv0288_ग_लिखोregI(state, 0x2b, tda[1]);
		stv0288_ग_लिखोregI(state, 0x2c, tda[2]);
		msleep(30);
	पूर्ण
	state->tuner_frequency = c->frequency;
	state->fec_inner = FEC_AUTO;
	state->symbol_rate = c->symbol_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0288_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;

	अगर (enable)
		stv0288_ग_लिखोregI(state, 0x01, 0xb5);
	अन्यथा
		stv0288_ग_लिखोregI(state, 0x01, 0x35);

	udelay(1);

	वापस 0;
पूर्ण

अटल व्योम stv0288_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0288_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0288_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "ST STV0288 DVB-S",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	=    1 * MHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.symbol_rate_tolerance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK |
		      FE_CAN_FEC_AUTO
	पूर्ण,

	.release = stv0288_release,
	.init = stv0288_init,
	.sleep = stv0288_sleep,
	.ग_लिखो = stv0288_ग_लिखो,
	.i2c_gate_ctrl = stv0288_i2c_gate_ctrl,
	.पढ़ो_status = stv0288_पढ़ो_status,
	.पढ़ो_ber = stv0288_पढ़ो_ber,
	.पढ़ो_संकेत_strength = stv0288_पढ़ो_संकेत_strength,
	.पढ़ो_snr = stv0288_पढ़ो_snr,
	.पढ़ो_ucblocks = stv0288_पढ़ो_ucblocks,
	.diseqc_send_master_cmd = stv0288_send_diseqc_msg,
	.diseqc_send_burst = stv0288_send_diseqc_burst,
	.set_tone = stv0288_set_tone,
	.set_voltage = stv0288_set_voltage,

	.set_frontend = stv0288_set_frontend,
पूर्ण;

काष्ठा dvb_frontend *stv0288_attach(स्थिर काष्ठा stv0288_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv0288_state *state = शून्य;
	पूर्णांक id;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा stv0288_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;
	state->tuner_frequency = 0;
	state->symbol_rate = 0;
	state->fec_inner = 0;
	state->errmode = STATUS_BER;

	stv0288_ग_लिखोregI(state, 0x41, 0x04);
	msleep(200);
	id = stv0288_पढ़ोreg(state, 0x00);
	dprपूर्णांकk("stv0288 id %x\n", id);

	/* रेजिस्टर 0x00 contains 0x11 क्रम STV0288  */
	अगर (id != 0x11)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &stv0288_ops,
			माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stv0288_attach);

module_param(debug_legacy_dish_चयन, पूर्णांक, 0444);
MODULE_PARM_DESC(debug_legacy_dish_चयन,
		"Enable timing analysis for Dish Network legacy switches");

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("ST STV0288 DVB Demodulator driver");
MODULE_AUTHOR("Georg Acher, Bob Liu, Igor liplianin");
MODULE_LICENSE("GPL");

