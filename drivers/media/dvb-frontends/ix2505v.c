<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Sharp IX2505V (marked B0017) DVB-S silicon tuner
 *
 * Copyright (C) 2010 Malcolm Priestley
 */

#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "ix2505v.h"

अटल पूर्णांक ix2505v_debug;
#घोषणा dprपूर्णांकk(level, args...) करो अणु \
	अगर (ix2505v_debug & level) \
		prपूर्णांकk(KERN_DEBUG "ix2505v: " args); \
पूर्ण जबतक (0)

#घोषणा deb_info(args...)  dprपूर्णांकk(0x01, args)
#घोषणा deb_i2c(args...)  dprपूर्णांकk(0x02, args)

काष्ठा ix2505v_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा ix2505v_config *config;
	u32 frequency;
पूर्ण;

/*
 *  Data पढ़ो क्रमmat of the Sharp IX2505V B0017
 *
 *  byte1:   1   |   1   |   0   |   0   |   0   |  MA1  |  MA0  |  1
 *  byte2:  POR  |   FL  |  RD2  |  RD1  |  RD0  |   X   |   X   |  X
 *
 *  byte1 = address
 *  byte2;
 *	POR = Power on Reset (VCC H=<2.2v L=>2.2v)
 *	FL  = Phase Lock (H=lock L=unlock)
 *	RD0-2 = Reserved पूर्णांकernal operations
 *
 * Only POR can be used to check the tuner is present
 *
 * Caution: after byte2 the I2C reverts to ग_लिखो mode continuing to पढ़ो
 *          may corrupt tuning data.
 *
 */

अटल पूर्णांक ix2505v_पढ़ो_status_reg(काष्ठा ix2505v_state *state)
अणु
	u8 addr = state->config->tuner_address;
	u8 b2[] = अणु0पूर्ण;
	पूर्णांक ret;

	काष्ठा i2c_msg msg[1] = अणु
		अणु .addr = addr, .flags = I2C_M_RD, .buf = b2, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 1);
	deb_i2c("Read %s ", __func__);

	वापस (ret == 1) ? (पूर्णांक) b2[0] : -1;
पूर्ण

अटल पूर्णांक ix2505v_ग_लिखो(काष्ठा ix2505v_state *state, u8 buf[], u8 count)
अणु
	काष्ठा i2c_msg msg[1] = अणु
		अणु .addr = state->config->tuner_address, .flags = 0,
		  .buf = buf, .len = count पूर्ण,
	पूर्ण;

	पूर्णांक ret;

	ret = i2c_transfer(state->i2c, msg, 1);

	अगर (ret != 1) अणु
		deb_i2c("%s: i2c error, ret=%d\n", __func__, ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ix2505v_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ix2505v_state *state = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(state);

पूर्ण

/*
 *  Data ग_लिखो क्रमmat of the Sharp IX2505V B0017
 *
 *  byte1:   1   |   1   |   0   |   0   |   0   | 0(MA1)| 0(MA0)|  0
 *  byte2:   0   |  BG1  |  BG2  |   N8  |   N7  |   N6  |  N5   |  N4
 *  byte3:   N3  |   N2  |   N1  |   A5  |   A4  |   A3  |   A2  |  A1
 *  byte4:   1   | 1(C1) | 1(C0) |  PD5  |  PD4  |   TM  | 0(RTS)| 1(REF)
 *  byte5:   BA2 |   BA1 |  BA0  |  PSC  |  PD3  |PD2/TS2|DIV/TS1|PD0/TS0
 *
 *  byte1 = address
 *
 *  Write order
 *  1) byte1 -> byte2 -> byte3 -> byte4 -> byte5
 *  2) byte1 -> byte4 -> byte5 -> byte2 -> byte3
 *  3) byte1 -> byte2 -> byte3 -> byte4
 *  4) byte1 -> byte4 -> byte5 -> byte2
 *  5) byte1 -> byte2 -> byte3
 *  6) byte1 -> byte4 -> byte5
 *  7) byte1 -> byte2
 *  8) byte1 -> byte4
 *
 *  Recommended Setup
 *  1 -> 8 -> 6
 */

अटल पूर्णांक ix2505v_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा ix2505v_state *state = fe->tuner_priv;
	u32 frequency = c->frequency;
	u32 b_w  = (c->symbol_rate * 27) / 32000;
	u32 भाग_factor, N , A, x;
	पूर्णांक ret = 0, len;
	u8 gain, cc, ref, psc, local_osc, lpf;
	u8 data[4] = अणु0पूर्ण;

	अगर ((frequency < fe->ops.info.frequency_min_hz / kHz)
	||  (frequency > fe->ops.info.frequency_max_hz / kHz))
		वापस -EINVAL;

	अगर (state->config->tuner_gain)
		gain = (state->config->tuner_gain < 4)
			? state->config->tuner_gain : 0;
	अन्यथा
		gain = 0x0;

	अगर (state->config->tuner_अक्षरgepump)
		cc = state->config->tuner_अक्षरgepump;
	अन्यथा
		cc = 0x3;

	ref = 8; /* REF =1 */
	psc = 32; /* PSC = 0 */

	भाग_factor = (frequency * ref) / 40; /* local osc = 4Mhz */
	x = भाग_factor / psc;
	N = x/100;
	A = ((x - (N * 100)) * psc) / 100;

	data[0] = ((gain & 0x3) << 5) | (N >> 3);
	data[1] = (N << 5) | (A & 0x1f);
	data[2] = 0x81 | ((cc & 0x3) << 5) ; /*PD5,PD4 & TM = 0|C1,C0|REF=1*/

	deb_info("Frq=%d x=%d N=%d A=%d\n", frequency, x, N, A);

	अगर (frequency <= 1065000)
		local_osc = (6 << 5) | 2;
	अन्यथा अगर (frequency <= 1170000)
		local_osc = (7 << 5) | 2;
	अन्यथा अगर (frequency <= 1300000)
		local_osc = (1 << 5);
	अन्यथा अगर (frequency <= 1445000)
		local_osc = (2 << 5);
	अन्यथा अगर (frequency <= 1607000)
		local_osc = (3 << 5);
	अन्यथा अगर (frequency <= 1778000)
		local_osc = (4 << 5);
	अन्यथा अगर (frequency <= 1942000)
		local_osc = (5 << 5);
	अन्यथा		/*frequency up to 2150000*/
		local_osc = (6 << 5);

	data[3] = local_osc; /* all other bits set 0 */

	अगर (b_w <= 10000)
		lpf = 0xc;
	अन्यथा अगर (b_w <= 12000)
		lpf = 0x2;
	अन्यथा अगर (b_w <= 14000)
		lpf = 0xa;
	अन्यथा अगर (b_w <= 16000)
		lpf = 0x6;
	अन्यथा अगर (b_w <= 18000)
		lpf = 0xe;
	अन्यथा अगर (b_w <= 20000)
		lpf = 0x1;
	अन्यथा अगर (b_w <= 22000)
		lpf = 0x9;
	अन्यथा अगर (b_w <= 24000)
		lpf = 0x5;
	अन्यथा अगर (b_w <= 26000)
		lpf = 0xd;
	अन्यथा अगर (b_w <= 28000)
		lpf = 0x3;
		अन्यथा
		lpf = 0xb;

	deb_info("Osc=%x b_w=%x lpf=%x\n", local_osc, b_w, lpf);
	deb_info("Data 0=[%4phN]\n", data);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	len = माप(data);
	ret |= ix2505v_ग_लिखो(state, data, len);

	data[2] |= 0x4; /* set TM = 1 other bits same */

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	len = 1;
	ret |= ix2505v_ग_लिखो(state, &data[2], len); /* ग_लिखो byte 4 only */

	msleep(10);

	data[2] |= ((lpf >> 2) & 0x3) << 3; /* lpf */
	data[3] |= (lpf & 0x3) << 2;

	deb_info("Data 2=[%x%x]\n", data[2], data[3]);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	len = 2;
	ret |= ix2505v_ग_लिखो(state, &data[2], len); /* ग_लिखो byte 4 & 5 */

	अगर (state->config->min_delay_ms)
		msleep(state->config->min_delay_ms);

	state->frequency = frequency;

	वापस ret;
पूर्ण

अटल पूर्णांक ix2505v_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा ix2505v_state *state = fe->tuner_priv;

	*frequency = state->frequency;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops ix2505v_tuner_ops = अणु
	.info = अणु
		.name = "Sharp IX2505V (B0017)",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2175 * MHz
	पूर्ण,
	.release = ix2505v_release,
	.set_params = ix2505v_set_params,
	.get_frequency = ix2505v_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *ix2505v_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा ix2505v_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा ix2505v_state *state = शून्य;
	पूर्णांक ret;

	अगर (शून्य == config) अणु
		deb_i2c("%s: no config ", __func__);
		जाओ error;
	पूर्ण

	state = kzalloc(माप(काष्ठा ix2505v_state), GFP_KERNEL);
	अगर (शून्य == state)
		वापस शून्य;

	state->config = config;
	state->i2c = i2c;

	अगर (state->config->tuner_ग_लिखो_only) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = ix2505v_पढ़ो_status_reg(state);

		अगर (ret & 0x80) अणु
			deb_i2c("%s: No IX2505V found\n", __func__);
			जाओ error;
		पूर्ण

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	fe->tuner_priv = state;

	स_नकल(&fe->ops.tuner_ops, &ix2505v_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));
	deb_i2c("%s: initialization (%s addr=0x%02x) ok\n",
		__func__, fe->ops.tuner_ops.info.name, config->tuner_address);

	वापस fe;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ix2505v_attach);

module_param_named(debug, ix2505v_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");
MODULE_DESCRIPTION("DVB IX2505V tuner driver");
MODULE_AUTHOR("Malcolm Priestley");
MODULE_LICENSE("GPL");
