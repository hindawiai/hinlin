<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *   Fujitu mb86a20s ISDB-T/ISDB-Tsb Module driver
 *
 *   Copyright (C) 2010-2013 Mauro Carvalho Chehab
 *   Copyright (C) 2009-2010 Douglas Landgraf <करोugsland@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "mb86a20s.h"

#घोषणा NUM_LAYERS 3

क्रमागत mb86a20s_bandwidth अणु
	MB86A20S_13SEG = 0,
	MB86A20S_13SEG_PARTIAL = 1,
	MB86A20S_1SEG = 2,
	MB86A20S_3SEG = 3,
पूर्ण;

अटल u8 mb86a20s_subchannel[] = अणु
	0xb0, 0xc0, 0xd0, 0xe0,
	0xf0, 0x00, 0x10, 0x20,
पूर्ण;

काष्ठा mb86a20s_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा mb86a20s_config *config;
	u32 last_frequency;

	काष्ठा dvb_frontend frontend;

	u32 अगर_freq;
	क्रमागत mb86a20s_bandwidth bw;
	bool inversion;
	u32 subchannel;

	u32 estimated_rate[NUM_LAYERS];
	अचिन्हित दीर्घ get_strength_समय;

	bool need_init;
पूर्ण;

काष्ठा regdata अणु
	u8 reg;
	u8 data;
पूर्ण;

#घोषणा BER_SAMPLING_RATE	1	/* Seconds */

/*
 * Initialization sequence: Use whatevere शेष values that PV SBTVD
 * करोes on its initialisation, obtained via USB snoop
 */
अटल काष्ठा regdata mb86a20s_init1[] = अणु
	अणु 0x70, 0x0f पूर्ण,
	अणु 0x70, 0xff पूर्ण,
	अणु 0x08, 0x01 पूर्ण,
	अणु 0x50, 0xd1 पूर्ण, अणु 0x51, 0x20 पूर्ण,
पूर्ण;

अटल काष्ठा regdata mb86a20s_init2[] = अणु
	अणु 0x50, 0xd1 पूर्ण, अणु 0x51, 0x22 पूर्ण,
	अणु 0x39, 0x01 पूर्ण,
	अणु 0x71, 0x00 पूर्ण,
	अणु 0x3b, 0x21 पूर्ण,
	अणु 0x3c, 0x3a पूर्ण,
	अणु 0x01, 0x0d पूर्ण,
	अणु 0x04, 0x08 पूर्ण, अणु 0x05, 0x05 पूर्ण,
	अणु 0x04, 0x0e पूर्ण, अणु 0x05, 0x00 पूर्ण,
	अणु 0x04, 0x0f पूर्ण, अणु 0x05, 0x14 पूर्ण,
	अणु 0x04, 0x0b पूर्ण, अणु 0x05, 0x8c पूर्ण,
	अणु 0x04, 0x00 पूर्ण, अणु 0x05, 0x00 पूर्ण,
	अणु 0x04, 0x01 पूर्ण, अणु 0x05, 0x07 पूर्ण,
	अणु 0x04, 0x02 पूर्ण, अणु 0x05, 0x0f पूर्ण,
	अणु 0x04, 0x03 पूर्ण, अणु 0x05, 0xa0 पूर्ण,
	अणु 0x04, 0x09 पूर्ण, अणु 0x05, 0x00 पूर्ण,
	अणु 0x04, 0x0a पूर्ण, अणु 0x05, 0xff पूर्ण,
	अणु 0x04, 0x27 पूर्ण, अणु 0x05, 0x64 पूर्ण,
	अणु 0x04, 0x28 पूर्ण, अणु 0x05, 0x00 पूर्ण,
	अणु 0x04, 0x1e पूर्ण, अणु 0x05, 0xff पूर्ण,
	अणु 0x04, 0x29 पूर्ण, अणु 0x05, 0x0a पूर्ण,
	अणु 0x04, 0x32 पूर्ण, अणु 0x05, 0x0a पूर्ण,
	अणु 0x04, 0x14 पूर्ण, अणु 0x05, 0x02 पूर्ण,
	अणु 0x04, 0x04 पूर्ण, अणु 0x05, 0x00 पूर्ण,
	अणु 0x04, 0x05 पूर्ण, अणु 0x05, 0x22 पूर्ण,
	अणु 0x04, 0x06 पूर्ण, अणु 0x05, 0x0e पूर्ण,
	अणु 0x04, 0x07 पूर्ण, अणु 0x05, 0xd8 पूर्ण,
	अणु 0x04, 0x12 पूर्ण, अणु 0x05, 0x00 पूर्ण,
	अणु 0x04, 0x13 पूर्ण, अणु 0x05, 0xff पूर्ण,

	/*
	 * On this demod, when the bit count reaches the count below,
	 * it collects the bit error count. The bit counters are initialized
	 * to 65535 here. This warrants that all of them will be quickly
	 * calculated when device माला_लो locked. As TMCC is parsed, the values
	 * will be adjusted later in the driver's code.
	 */
	अणु 0x52, 0x01 पूर्ण,				/* Turn on BER beक्रमe Viterbi */
	अणु 0x50, 0xa7 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xa8 पूर्ण, अणु 0x51, 0xff पूर्ण,
	अणु 0x50, 0xa9 पूर्ण, अणु 0x51, 0xff पूर्ण,
	अणु 0x50, 0xaa पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xab पूर्ण, अणु 0x51, 0xff पूर्ण,
	अणु 0x50, 0xac पूर्ण, अणु 0x51, 0xff पूर्ण,
	अणु 0x50, 0xad पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xae पूर्ण, अणु 0x51, 0xff पूर्ण,
	अणु 0x50, 0xaf पूर्ण, अणु 0x51, 0xff पूर्ण,

	/*
	 * On this demod, post BER counts blocks. When the count reaches the
	 * value below, it collects the block error count. The block counters
	 * are initialized to 127 here. This warrants that all of them will be
	 * quickly calculated when device माला_लो locked. As TMCC is parsed, the
	 * values will be adjusted later in the driver's code.
	 */
	अणु 0x5e, 0x07 पूर्ण,				/* Turn on BER after Viterbi */
	अणु 0x50, 0xdc पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xdd पूर्ण, अणु 0x51, 0x7f पूर्ण,
	अणु 0x50, 0xde पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xdf पूर्ण, अणु 0x51, 0x7f पूर्ण,
	अणु 0x50, 0xe0 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xe1 पूर्ण, अणु 0x51, 0x7f पूर्ण,

	/*
	 * On this demod, when the block count reaches the count below,
	 * it collects the block error count. The block counters are initialized
	 * to 127 here. This warrants that all of them will be quickly
	 * calculated when device माला_लो locked. As TMCC is parsed, the values
	 * will be adjusted later in the driver's code.
	 */
	अणु 0x50, 0xb0 पूर्ण, अणु 0x51, 0x07 पूर्ण,		/* Enable PER */
	अणु 0x50, 0xb2 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xb3 पूर्ण, अणु 0x51, 0x7f पूर्ण,
	अणु 0x50, 0xb4 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xb5 पूर्ण, अणु 0x51, 0x7f पूर्ण,
	अणु 0x50, 0xb6 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0xb7 पूर्ण, अणु 0x51, 0x7f पूर्ण,

	अणु 0x50, 0x50 पूर्ण, अणु 0x51, 0x02 पूर्ण,		/* MER manual mode */
	अणु 0x50, 0x51 पूर्ण, अणु 0x51, 0x04 पूर्ण,		/* MER symbol 4 */
	अणु 0x45, 0x04 पूर्ण,				/* CN symbol 4 */
	अणु 0x48, 0x04 पूर्ण,				/* CN manual mode */
	अणु 0x50, 0xd5 पूर्ण, अणु 0x51, 0x01 पूर्ण,
	अणु 0x50, 0xd6 पूर्ण, अणु 0x51, 0x1f पूर्ण,
	अणु 0x50, 0xd2 पूर्ण, अणु 0x51, 0x03 पूर्ण,
	अणु 0x50, 0xd7 पूर्ण, अणु 0x51, 0x3f पूर्ण,
	अणु 0x1c, 0x01 पूर्ण,
	अणु 0x28, 0x06 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x03 पूर्ण,
	अणु 0x28, 0x07 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x0d पूर्ण,
	अणु 0x28, 0x08 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x02 पूर्ण,
	अणु 0x28, 0x09 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x01 पूर्ण,
	अणु 0x28, 0x0a पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x21 पूर्ण,
	अणु 0x28, 0x0b पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x29 पूर्ण,
	अणु 0x28, 0x0c पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x16 पूर्ण,
	अणु 0x28, 0x0d पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x31 पूर्ण,
	अणु 0x28, 0x0e पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x0e पूर्ण,
	अणु 0x28, 0x0f पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x4e पूर्ण,
	अणु 0x28, 0x10 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x46 पूर्ण,
	अणु 0x28, 0x11 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x0f पूर्ण,
	अणु 0x28, 0x12 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x56 पूर्ण,
	अणु 0x28, 0x13 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x35 पूर्ण,
	अणु 0x28, 0x14 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x01 पूर्ण, अणु 0x2b, 0xbe पूर्ण,
	अणु 0x28, 0x15 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x01 पूर्ण, अणु 0x2b, 0x84 पूर्ण,
	अणु 0x28, 0x16 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x03 पूर्ण, अणु 0x2b, 0xee पूर्ण,
	अणु 0x28, 0x17 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x98 पूर्ण,
	अणु 0x28, 0x18 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x00 पूर्ण, अणु 0x2b, 0x9f पूर्ण,
	अणु 0x28, 0x19 पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x07 पूर्ण, अणु 0x2b, 0xb2 पूर्ण,
	अणु 0x28, 0x1a पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x06 पूर्ण, अणु 0x2b, 0xc2 पूर्ण,
	अणु 0x28, 0x1b पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x07 पूर्ण, अणु 0x2b, 0x4a पूर्ण,
	अणु 0x28, 0x1c पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x01 पूर्ण, अणु 0x2b, 0xbc पूर्ण,
	अणु 0x28, 0x1d पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x04 पूर्ण, अणु 0x2b, 0xba पूर्ण,
	अणु 0x28, 0x1e पूर्ण, अणु 0x29, 0x00 पूर्ण, अणु 0x2a, 0x06 पूर्ण, अणु 0x2b, 0x14 पूर्ण,
	अणु 0x50, 0x1e पूर्ण, अणु 0x51, 0x5d पूर्ण,
	अणु 0x50, 0x22 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0x23 पूर्ण, अणु 0x51, 0xc8 पूर्ण,
	अणु 0x50, 0x24 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0x25 पूर्ण, अणु 0x51, 0xf0 पूर्ण,
	अणु 0x50, 0x26 पूर्ण, अणु 0x51, 0x00 पूर्ण,
	अणु 0x50, 0x27 पूर्ण, अणु 0x51, 0xc3 पूर्ण,
	अणु 0x50, 0x39 पूर्ण, अणु 0x51, 0x02 पूर्ण,
	अणु 0x50, 0xd5 पूर्ण, अणु 0x51, 0x01 पूर्ण,
	अणु 0xd0, 0x00 पूर्ण,
पूर्ण;

अटल काष्ठा regdata mb86a20s_reset_reception[] = अणु
	अणु 0x70, 0xf0 पूर्ण,
	अणु 0x70, 0xff पूर्ण,
	अणु 0x08, 0x01 पूर्ण,
	अणु 0x08, 0x00 पूर्ण,
पूर्ण;

अटल काष्ठा regdata mb86a20s_per_ber_reset[] = अणु
	अणु 0x53, 0x00 पूर्ण,	/* pre BER Counter reset */
	अणु 0x53, 0x07 पूर्ण,

	अणु 0x5f, 0x00 पूर्ण,	/* post BER Counter reset */
	अणु 0x5f, 0x07 पूर्ण,

	अणु 0x50, 0xb1 पूर्ण,	/* PER Counter reset */
	अणु 0x51, 0x07 पूर्ण,
	अणु 0x51, 0x00 पूर्ण,
पूर्ण;

/*
 * I2C पढ़ो/ग_लिखो functions and macros
 */

अटल पूर्णांक mb86a20s_i2c_ग_लिखोreg(काष्ठा mb86a20s_state *state,
			     u8 i2c_addr, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = i2c_addr, .flags = 0, .buf = buf, .len = 2
	पूर्ण;
	पूर्णांक rc;

	rc = i2c_transfer(state->i2c, &msg, 1);
	अगर (rc != 1) अणु
		dev_err(&state->i2c->dev,
			"%s: writereg error (rc == %i, reg == 0x%02x, data == 0x%02x)\n",
			__func__, rc, reg, data);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mb86a20s_i2c_ग_लिखोregdata(काष्ठा mb86a20s_state *state,
				     u8 i2c_addr, काष्ठा regdata *rd, पूर्णांक size)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < size; i++) अणु
		rc = mb86a20s_i2c_ग_लिखोreg(state, i2c_addr, rd[i].reg,
					   rd[i].data);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mb86a20s_i2c_पढ़ोreg(काष्ठा mb86a20s_state *state,
				u8 i2c_addr, u8 reg)
अणु
	u8 val;
	पूर्णांक rc;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = i2c_addr, .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = i2c_addr, .flags = I2C_M_RD, .buf = &val, .len = 1 पूर्ण
	पूर्ण;

	rc = i2c_transfer(state->i2c, msg, 2);

	अगर (rc != 2) अणु
		dev_err(&state->i2c->dev, "%s: reg=0x%x (error=%d)\n",
			__func__, reg, rc);
		वापस (rc < 0) ? rc : -EIO;
	पूर्ण

	वापस val;
पूर्ण

#घोषणा mb86a20s_पढ़ोreg(state, reg) \
	mb86a20s_i2c_पढ़ोreg(state, state->config->demod_address, reg)
#घोषणा mb86a20s_ग_लिखोreg(state, reg, val) \
	mb86a20s_i2c_ग_लिखोreg(state, state->config->demod_address, reg, val)
#घोषणा mb86a20s_ग_लिखोregdata(state, regdata) \
	mb86a20s_i2c_ग_लिखोregdata(state, state->config->demod_address, \
	regdata, ARRAY_SIZE(regdata))

/*
 * Ancillary पूर्णांकernal routines (likely compiled अंतरभूतd)
 *
 * The functions below assume that gateway lock has alपढ़ोy obtained
 */

अटल पूर्णांक mb86a20s_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	पूर्णांक val;

	*status = 0;

	val = mb86a20s_पढ़ोreg(state, 0x0a);
	अगर (val < 0)
		वापस val;

	val &= 0xf;
	अगर (val >= 2)
		*status |= FE_HAS_SIGNAL;

	अगर (val >= 4)
		*status |= FE_HAS_CARRIER;

	अगर (val >= 5)
		*status |= FE_HAS_VITERBI;

	अगर (val >= 7)
		*status |= FE_HAS_SYNC;

	/*
	 * Actually, on state S8, it starts receiving TS, but the TS
	 * output is only on normal state after the transition to S9.
	 */
	अगर (val >= 9)
		*status |= FE_HAS_LOCK;

	dev_dbg(&state->i2c->dev, "%s: Status = 0x%02x (state = %d)\n",
		 __func__, *status, val);

	वापस val;
पूर्ण

अटल पूर्णांक mb86a20s_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc;
	अचिन्हित rf_max, rf_min, rf;

	अगर (state->get_strength_समय &&
	   (!समय_after(jअगरfies, state->get_strength_समय)))
		वापस c->strength.stat[0].uvalue;

	/* Reset its value अगर an error happen */
	c->strength.stat[0].uvalue = 0;

	/* Does a binary search to get RF strength */
	rf_max = 0xfff;
	rf_min = 0;
	करो अणु
		rf = (rf_max + rf_min) / 2;
		rc = mb86a20s_ग_लिखोreg(state, 0x04, 0x1f);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x05, rf >> 8);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x04, 0x20);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x05, rf);
		अगर (rc < 0)
			वापस rc;

		rc = mb86a20s_पढ़ोreg(state, 0x02);
		अगर (rc < 0)
			वापस rc;
		अगर (rc & 0x08)
			rf_min = (rf_max + rf_min) / 2;
		अन्यथा
			rf_max = (rf_max + rf_min) / 2;
		अगर (rf_max - rf_min < 4) अणु
			rf = (rf_max + rf_min) / 2;

			/* Rescale it from 2^12 (4096) to 2^16 */
			rf = rf << (16 - 12);
			अगर (rf)
				rf |= (1 << 12) - 1;

			dev_dbg(&state->i2c->dev,
				"%s: signal strength = %d (%d < RF=%d < %d)\n",
				__func__, rf, rf_min, rf >> 4, rf_max);
			c->strength.stat[0].uvalue = rf;
			state->get_strength_समय = jअगरfies +
						   msecs_to_jअगरfies(1000);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक mb86a20s_get_modulation(काष्ठा mb86a20s_state *state,
				   अचिन्हित layer)
अणु
	पूर्णांक rc;
	अटल अचिन्हित अक्षर reg[] = अणु
		[0] = 0x86,	/* Layer A */
		[1] = 0x8a,	/* Layer B */
		[2] = 0x8e,	/* Layer C */
	पूर्ण;

	अगर (layer >= ARRAY_SIZE(reg))
		वापस -EINVAL;
	rc = mb86a20s_ग_लिखोreg(state, 0x6d, reg[layer]);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x6e);
	अगर (rc < 0)
		वापस rc;
	चयन ((rc >> 4) & 0x07) अणु
	हाल 0:
		वापस DQPSK;
	हाल 1:
		वापस QPSK;
	हाल 2:
		वापस QAM_16;
	हाल 3:
		वापस QAM_64;
	शेष:
		वापस QAM_AUTO;
	पूर्ण
पूर्ण

अटल पूर्णांक mb86a20s_get_fec(काष्ठा mb86a20s_state *state,
			    अचिन्हित layer)
अणु
	पूर्णांक rc;

	अटल अचिन्हित अक्षर reg[] = अणु
		[0] = 0x87,	/* Layer A */
		[1] = 0x8b,	/* Layer B */
		[2] = 0x8f,	/* Layer C */
	पूर्ण;

	अगर (layer >= ARRAY_SIZE(reg))
		वापस -EINVAL;
	rc = mb86a20s_ग_लिखोreg(state, 0x6d, reg[layer]);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x6e);
	अगर (rc < 0)
		वापस rc;
	चयन ((rc >> 4) & 0x07) अणु
	हाल 0:
		वापस FEC_1_2;
	हाल 1:
		वापस FEC_2_3;
	हाल 2:
		वापस FEC_3_4;
	हाल 3:
		वापस FEC_5_6;
	हाल 4:
		वापस FEC_7_8;
	शेष:
		वापस FEC_AUTO;
	पूर्ण
पूर्ण

अटल पूर्णांक mb86a20s_get_पूर्णांकerleaving(काष्ठा mb86a20s_state *state,
				     अचिन्हित layer)
अणु
	पूर्णांक rc;
	पूर्णांक पूर्णांकerleaving[] = अणु
		0, 1, 2, 4, 8
	पूर्ण;

	अटल अचिन्हित अक्षर reg[] = अणु
		[0] = 0x88,	/* Layer A */
		[1] = 0x8c,	/* Layer B */
		[2] = 0x90,	/* Layer C */
	पूर्ण;

	अगर (layer >= ARRAY_SIZE(reg))
		वापस -EINVAL;
	rc = mb86a20s_ग_लिखोreg(state, 0x6d, reg[layer]);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x6e);
	अगर (rc < 0)
		वापस rc;

	वापस पूर्णांकerleaving[(rc >> 4) & 0x07];
पूर्ण

अटल पूर्णांक mb86a20s_get_segment_count(काष्ठा mb86a20s_state *state,
				      अचिन्हित layer)
अणु
	पूर्णांक rc, count;
	अटल अचिन्हित अक्षर reg[] = अणु
		[0] = 0x89,	/* Layer A */
		[1] = 0x8d,	/* Layer B */
		[2] = 0x91,	/* Layer C */
	पूर्ण;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (layer >= ARRAY_SIZE(reg))
		वापस -EINVAL;

	rc = mb86a20s_ग_लिखोreg(state, 0x6d, reg[layer]);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x6e);
	अगर (rc < 0)
		वापस rc;
	count = (rc >> 4) & 0x0f;

	dev_dbg(&state->i2c->dev, "%s: segments: %d.\n", __func__, count);

	वापस count;
पूर्ण

अटल व्योम mb86a20s_reset_frontend_cache(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	/* Fixed parameters */
	c->delivery_प्रणाली = SYS_ISDBT;
	c->bandwidth_hz = 6000000;

	/* Initialize values that will be later स्वतःdetected */
	c->isdbt_layer_enabled = 0;
	c->transmission_mode = TRANSMISSION_MODE_AUTO;
	c->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
	c->isdbt_sb_mode = 0;
	c->isdbt_sb_segment_count = 0;
पूर्ण

/*
 * Estimates the bit rate using the per-segment bit rate given by
 * ABNT/NBR 15601 spec (table 4).
 */
अटल स्थिर u32 isdbt_rate[3][5][4] = अणु
	अणु	/* DQPSK/QPSK */
		अणु  280850,  312060,  330420,  340430 पूर्ण,	/* 1/2 */
		अणु  374470,  416080,  440560,  453910 पूर्ण,	/* 2/3 */
		अणु  421280,  468090,  495630,  510650 पूर्ण,	/* 3/4 */
		अणु  468090,  520100,  550700,  567390 पूर्ण,	/* 5/6 */
		अणु  491500,  546110,  578230,  595760 पूर्ण,	/* 7/8 */
	पूर्ण, अणु	/* QAM16 */
		अणु  561710,  624130,  660840,  680870 पूर्ण,	/* 1/2 */
		अणु  748950,  832170,  881120,  907820 पूर्ण,	/* 2/3 */
		अणु  842570,  936190,  991260, 1021300 पूर्ण,	/* 3/4 */
		अणु  936190, 1040210, 1101400, 1134780 पूर्ण,	/* 5/6 */
		अणु  983000, 1092220, 1156470, 1191520 पूर्ण,	/* 7/8 */
	पूर्ण, अणु	/* QAM64 */
		अणु  842570,  936190,  991260, 1021300 पूर्ण,	/* 1/2 */
		अणु 1123430, 1248260, 1321680, 1361740 पूर्ण,	/* 2/3 */
		अणु 1263860, 1404290, 1486900, 1531950 पूर्ण,	/* 3/4 */
		अणु 1404290, 1560320, 1652110, 1702170 पूर्ण,	/* 5/6 */
		अणु 1474500, 1638340, 1734710, 1787280 पूर्ण,	/* 7/8 */
	पूर्ण
पूर्ण;

अटल u32 isdbt_layer_min_bitrate(काष्ठा dtv_frontend_properties *c,
				   u32 layer)
अणु
	पूर्णांक mod, fec, guard;

	/*
	 * If modulation/fec/guard is not detected, the शेष is
	 * to consider the lowest bit rate, to aव्योम taking too दीर्घ समय
	 * to get BER.
	 */
	चयन (c->layer[layer].modulation) अणु
	हाल DQPSK:
	हाल QPSK:
	शेष:
		mod = 0;
		अवरोध;
	हाल QAM_16:
		mod = 1;
		अवरोध;
	हाल QAM_64:
		mod = 2;
		अवरोध;
	पूर्ण

	चयन (c->layer[layer].fec) अणु
	शेष:
	हाल FEC_1_2:
	हाल FEC_AUTO:
		fec = 0;
		अवरोध;
	हाल FEC_2_3:
		fec = 1;
		अवरोध;
	हाल FEC_3_4:
		fec = 2;
		अवरोध;
	हाल FEC_5_6:
		fec = 3;
		अवरोध;
	हाल FEC_7_8:
		fec = 4;
		अवरोध;
	पूर्ण

	चयन (c->guard_पूर्णांकerval) अणु
	शेष:
	हाल GUARD_INTERVAL_1_4:
		guard = 0;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		guard = 1;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		guard = 2;
		अवरोध;
	हाल GUARD_INTERVAL_1_32:
		guard = 3;
		अवरोध;
	पूर्ण

	वापस isdbt_rate[mod][fec][guard] * c->layer[layer].segment_count;
पूर्ण

अटल पूर्णांक mb86a20s_get_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक layer, rc, rate, counter;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	/* Reset frontend cache to शेष values */
	mb86a20s_reset_frontend_cache(fe);

	/* Check क्रम partial reception */
	rc = mb86a20s_ग_लिखोreg(state, 0x6d, 0x85);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x6e);
	अगर (rc < 0)
		वापस rc;
	c->isdbt_partial_reception = (rc & 0x10) ? 1 : 0;

	/* Get per-layer data */

	क्रम (layer = 0; layer < NUM_LAYERS; layer++) अणु
		dev_dbg(&state->i2c->dev, "%s: getting data for layer %c.\n",
			__func__, 'A' + layer);

		rc = mb86a20s_get_segment_count(state, layer);
		अगर (rc < 0)
			जाओ noperlayer_error;
		अगर (rc >= 0 && rc < 14) अणु
			c->layer[layer].segment_count = rc;
		पूर्ण अन्यथा अणु
			c->layer[layer].segment_count = 0;
			state->estimated_rate[layer] = 0;
			जारी;
		पूर्ण
		c->isdbt_layer_enabled |= 1 << layer;
		rc = mb86a20s_get_modulation(state, layer);
		अगर (rc < 0)
			जाओ noperlayer_error;
		dev_dbg(&state->i2c->dev, "%s: modulation %d.\n",
			__func__, rc);
		c->layer[layer].modulation = rc;
		rc = mb86a20s_get_fec(state, layer);
		अगर (rc < 0)
			जाओ noperlayer_error;
		dev_dbg(&state->i2c->dev, "%s: FEC %d.\n",
			__func__, rc);
		c->layer[layer].fec = rc;
		rc = mb86a20s_get_पूर्णांकerleaving(state, layer);
		अगर (rc < 0)
			जाओ noperlayer_error;
		dev_dbg(&state->i2c->dev, "%s: interleaving %d.\n",
			__func__, rc);
		c->layer[layer].पूर्णांकerleaving = rc;

		rate = isdbt_layer_min_bitrate(c, layer);
		counter = rate * BER_SAMPLING_RATE;

		/* Aव्योमs sampling too quickly or to overflow the रेजिस्टर */
		अगर (counter < 256)
			counter = 256;
		अन्यथा अगर (counter > (1 << 24) - 1)
			counter = (1 << 24) - 1;

		dev_dbg(&state->i2c->dev,
			"%s: layer %c bitrate: %d kbps; counter = %d (0x%06x)\n",
			__func__, 'A' + layer, rate / 1000, counter, counter);

		state->estimated_rate[layer] = counter;
	पूर्ण

	rc = mb86a20s_ग_लिखोreg(state, 0x6d, 0x84);
	अगर (rc < 0)
		वापस rc;
	अगर ((rc & 0x60) == 0x20) अणु
		c->isdbt_sb_mode = 1;
		/* At least, one segment should exist */
		अगर (!c->isdbt_sb_segment_count)
			c->isdbt_sb_segment_count = 1;
	पूर्ण

	/* Get transmission mode and guard पूर्णांकerval */
	rc = mb86a20s_पढ़ोreg(state, 0x07);
	अगर (rc < 0)
		वापस rc;
	c->transmission_mode = TRANSMISSION_MODE_AUTO;
	अगर ((rc & 0x60) == 0x20) अणु
		/* Only modes 2 and 3 are supported */
		चयन ((rc >> 2) & 0x03) अणु
		हाल 1:
			c->transmission_mode = TRANSMISSION_MODE_4K;
			अवरोध;
		हाल 2:
			c->transmission_mode = TRANSMISSION_MODE_8K;
			अवरोध;
		पूर्ण
	पूर्ण
	c->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
	अगर (!(rc & 0x10)) अणु
		/* Guard पूर्णांकerval 1/32 is not supported */
		चयन (rc & 0x3) अणु
		हाल 0:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
			अवरोध;
		हाल 1:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
			अवरोध;
		हाल 2:
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;

noperlayer_error:

	/* per-layer info is incomplete; discard all per-layer */
	c->isdbt_layer_enabled = 0;

	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_reset_counters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc, val;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	/* Reset the counters, अगर the channel changed */
	अगर (state->last_frequency != c->frequency) अणु
		स_रखो(&c->cnr, 0, माप(c->cnr));
		स_रखो(&c->pre_bit_error, 0, माप(c->pre_bit_error));
		स_रखो(&c->pre_bit_count, 0, माप(c->pre_bit_count));
		स_रखो(&c->post_bit_error, 0, माप(c->post_bit_error));
		स_रखो(&c->post_bit_count, 0, माप(c->post_bit_count));
		स_रखो(&c->block_error, 0, माप(c->block_error));
		स_रखो(&c->block_count, 0, माप(c->block_count));

		state->last_frequency = c->frequency;
	पूर्ण

	/* Clear status क्रम most stats */

	/* BER/PER counter reset */
	rc = mb86a20s_ग_लिखोregdata(state, mb86a20s_per_ber_reset);
	अगर (rc < 0)
		जाओ err;

	/* CNR counter reset */
	rc = mb86a20s_पढ़ोreg(state, 0x45);
	अगर (rc < 0)
		जाओ err;
	val = rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x45, val | 0x10);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x45, val & 0x6f);
	अगर (rc < 0)
		जाओ err;

	/* MER counter reset */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0x50);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		जाओ err;
	val = rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x51, val | 0x01);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x51, val & 0x06);
	अगर (rc < 0)
		जाओ err;

	जाओ ok;
err:
	dev_err(&state->i2c->dev,
		"%s: Can't reset FE statistics (error %d).\n",
		__func__, rc);
ok:
	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_get_pre_ber(काष्ठा dvb_frontend *fe,
				अचिन्हित layer,
				u32 *error, u32 *count)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	पूर्णांक rc, val;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (layer >= NUM_LAYERS)
		वापस -EINVAL;

	/* Check अगर the BER measures are alपढ़ोy available */
	rc = mb86a20s_पढ़ोreg(state, 0x54);
	अगर (rc < 0)
		वापस rc;

	/* Check अगर data is available क्रम that layer */
	अगर (!(rc & (1 << layer))) अणु
		dev_dbg(&state->i2c->dev,
			"%s: preBER for layer %c is not available yet.\n",
			__func__, 'A' + layer);
		वापस -EBUSY;
	पूर्ण

	/* Read Bit Error Count */
	rc = mb86a20s_पढ़ोreg(state, 0x55 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	*error = rc << 16;
	rc = mb86a20s_पढ़ोreg(state, 0x56 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	*error |= rc << 8;
	rc = mb86a20s_पढ़ोreg(state, 0x57 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	*error |= rc;

	dev_dbg(&state->i2c->dev,
		"%s: bit error before Viterbi for layer %c: %d.\n",
		__func__, 'A' + layer, *error);

	/* Read Bit Count */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xa7 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*count = rc << 16;
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xa8 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*count |= rc << 8;
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xa9 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*count |= rc;

	dev_dbg(&state->i2c->dev,
		"%s: bit count before Viterbi for layer %c: %d.\n",
		__func__, 'A' + layer, *count);


	/*
	 * As we get TMCC data from the frontend, we can better estimate the
	 * BER bit counters, in order to करो the BER measure during a दीर्घer
	 * समय. Use those data, अगर available, to update the bit count
	 * measure.
	 */

	अगर (state->estimated_rate[layer]
	    && state->estimated_rate[layer] != *count) अणु
		dev_dbg(&state->i2c->dev,
			"%s: updating layer %c preBER counter to %d.\n",
			__func__, 'A' + layer, state->estimated_rate[layer]);

		/* Turn off BER beक्रमe Viterbi */
		rc = mb86a20s_ग_लिखोreg(state, 0x52, 0x00);

		/* Update counter क्रम this layer */
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xa7 + layer * 3);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51,
				       state->estimated_rate[layer] >> 16);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xa8 + layer * 3);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51,
				       state->estimated_rate[layer] >> 8);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xa9 + layer * 3);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51,
				       state->estimated_rate[layer]);
		अगर (rc < 0)
			वापस rc;

		/* Turn on BER beक्रमe Viterbi */
		rc = mb86a20s_ग_लिखोreg(state, 0x52, 0x01);

		/* Reset all preBER counters */
		rc = mb86a20s_ग_लिखोreg(state, 0x53, 0x00);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x53, 0x07);
	पूर्ण अन्यथा अणु
		/* Reset counter to collect new data */
		rc = mb86a20s_पढ़ोreg(state, 0x53);
		अगर (rc < 0)
			वापस rc;
		val = rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x53, val & ~(1 << layer));
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x53, val | (1 << layer));
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_get_post_ber(काष्ठा dvb_frontend *fe,
				 अचिन्हित layer,
				  u32 *error, u32 *count)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	u32 counter, collect_rate;
	पूर्णांक rc, val;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (layer >= NUM_LAYERS)
		वापस -EINVAL;

	/* Check अगर the BER measures are alपढ़ोy available */
	rc = mb86a20s_पढ़ोreg(state, 0x60);
	अगर (rc < 0)
		वापस rc;

	/* Check अगर data is available क्रम that layer */
	अगर (!(rc & (1 << layer))) अणु
		dev_dbg(&state->i2c->dev,
			"%s: post BER for layer %c is not available yet.\n",
			__func__, 'A' + layer);
		वापस -EBUSY;
	पूर्ण

	/* Read Bit Error Count */
	rc = mb86a20s_पढ़ोreg(state, 0x64 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	*error = rc << 16;
	rc = mb86a20s_पढ़ोreg(state, 0x65 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	*error |= rc << 8;
	rc = mb86a20s_पढ़ोreg(state, 0x66 + layer * 3);
	अगर (rc < 0)
		वापस rc;
	*error |= rc;

	dev_dbg(&state->i2c->dev,
		"%s: post bit error for layer %c: %d.\n",
		__func__, 'A' + layer, *error);

	/* Read Bit Count */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xdc + layer * 2);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	counter = rc << 8;
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xdd + layer * 2);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	counter |= rc;
	*count = counter * 204 * 8;

	dev_dbg(&state->i2c->dev,
		"%s: post bit count for layer %c: %d.\n",
		__func__, 'A' + layer, *count);

	/*
	 * As we get TMCC data from the frontend, we can better estimate the
	 * BER bit counters, in order to करो the BER measure during a दीर्घer
	 * समय. Use those data, अगर available, to update the bit count
	 * measure.
	 */

	अगर (!state->estimated_rate[layer])
		जाओ reset_measurement;

	collect_rate = state->estimated_rate[layer] / 204 / 8;
	अगर (collect_rate < 32)
		collect_rate = 32;
	अगर (collect_rate > 65535)
		collect_rate = 65535;
	अगर (collect_rate != counter) अणु
		dev_dbg(&state->i2c->dev,
			"%s: updating postBER counter on layer %c to %d.\n",
			__func__, 'A' + layer, collect_rate);

		/* Turn off BER after Viterbi */
		rc = mb86a20s_ग_लिखोreg(state, 0x5e, 0x00);

		/* Update counter क्रम this layer */
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xdc + layer * 2);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, collect_rate >> 8);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xdd + layer * 2);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, collect_rate & 0xff);
		अगर (rc < 0)
			वापस rc;

		/* Turn on BER after Viterbi */
		rc = mb86a20s_ग_लिखोreg(state, 0x5e, 0x07);

		/* Reset all preBER counters */
		rc = mb86a20s_ग_लिखोreg(state, 0x5f, 0x00);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x5f, 0x07);

		वापस rc;
	पूर्ण

reset_measurement:
	/* Reset counter to collect new data */
	rc = mb86a20s_पढ़ोreg(state, 0x5f);
	अगर (rc < 0)
		वापस rc;
	val = rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x5f, val & ~(1 << layer));
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x5f, val | (1 << layer));

	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_get_blk_error(काष्ठा dvb_frontend *fe,
			    अचिन्हित layer,
			    u32 *error, u32 *count)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	पूर्णांक rc, val;
	u32 collect_rate;
	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (layer >= NUM_LAYERS)
		वापस -EINVAL;

	/* Check अगर the PER measures are alपढ़ोy available */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb8);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;

	/* Check अगर data is available क्रम that layer */

	अगर (!(rc & (1 << layer))) अणु
		dev_dbg(&state->i2c->dev,
			"%s: block counts for layer %c aren't available yet.\n",
			__func__, 'A' + layer);
		वापस -EBUSY;
	पूर्ण

	/* Read Packet error Count */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb9 + layer * 2);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*error = rc << 8;
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xba + layer * 2);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*error |= rc;
	dev_dbg(&state->i2c->dev, "%s: block error for layer %c: %d.\n",
		__func__, 'A' + layer, *error);

	/* Read Bit Count */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb2 + layer * 2);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*count = rc << 8;
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb3 + layer * 2);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	*count |= rc;

	dev_dbg(&state->i2c->dev,
		"%s: block count for layer %c: %d.\n",
		__func__, 'A' + layer, *count);

	/*
	 * As we get TMCC data from the frontend, we can better estimate the
	 * BER bit counters, in order to करो the BER measure during a दीर्घer
	 * समय. Use those data, अगर available, to update the bit count
	 * measure.
	 */

	अगर (!state->estimated_rate[layer])
		जाओ reset_measurement;

	collect_rate = state->estimated_rate[layer] / 204 / 8;
	अगर (collect_rate < 32)
		collect_rate = 32;
	अगर (collect_rate > 65535)
		collect_rate = 65535;

	अगर (collect_rate != *count) अणु
		dev_dbg(&state->i2c->dev,
			"%s: updating PER counter on layer %c to %d.\n",
			__func__, 'A' + layer, collect_rate);

		/* Stop PER measurement */
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb0);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, 0x00);
		अगर (rc < 0)
			वापस rc;

		/* Update this layer's counter */
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb2 + layer * 2);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, collect_rate >> 8);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb3 + layer * 2);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, collect_rate & 0xff);
		अगर (rc < 0)
			वापस rc;

		/* start PER measurement */
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb0);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, 0x07);
		अगर (rc < 0)
			वापस rc;

		/* Reset all counters to collect new data */
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb1);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, 0x07);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_ग_लिखोreg(state, 0x51, 0x00);

		वापस rc;
	पूर्ण

reset_measurement:
	/* Reset counter to collect new data */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xb1);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	val = rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x51, val | (1 << layer));
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x51, val & ~(1 << layer));

	वापस rc;
पूर्ण

काष्ठा linear_segments अणु
	अचिन्हित x, y;
पूर्ण;

/*
 * All tables below वापस a dB/1000 measurement
 */

अटल स्थिर काष्ठा linear_segments cnr_to_db_table[] = अणु
	अणु 19648,     0पूर्ण,
	अणु 18187,  1000पूर्ण,
	अणु 16534,  2000पूर्ण,
	अणु 14823,  3000पूर्ण,
	अणु 13161,  4000पूर्ण,
	अणु 11622,  5000पूर्ण,
	अणु 10279,  6000पूर्ण,
	अणु  9089,  7000पूर्ण,
	अणु  8042,  8000पूर्ण,
	अणु  7137,  9000पूर्ण,
	अणु  6342, 10000पूर्ण,
	अणु  5641, 11000पूर्ण,
	अणु  5030, 12000पूर्ण,
	अणु  4474, 13000पूर्ण,
	अणु  3988, 14000पूर्ण,
	अणु  3556, 15000पूर्ण,
	अणु  3180, 16000पूर्ण,
	अणु  2841, 17000पूर्ण,
	अणु  2541, 18000पूर्ण,
	अणु  2276, 19000पूर्ण,
	अणु  2038, 20000पूर्ण,
	अणु  1800, 21000पूर्ण,
	अणु  1625, 22000पूर्ण,
	अणु  1462, 23000पूर्ण,
	अणु  1324, 24000पूर्ण,
	अणु  1175, 25000पूर्ण,
	अणु  1063, 26000पूर्ण,
	अणु   980, 27000पूर्ण,
	अणु   907, 28000पूर्ण,
	अणु   840, 29000पूर्ण,
	अणु   788, 30000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा linear_segments cnr_64qam_table[] = अणु
	अणु 3922688,     0पूर्ण,
	अणु 3920384,  1000पूर्ण,
	अणु 3902720,  2000पूर्ण,
	अणु 3894784,  3000पूर्ण,
	अणु 3882496,  4000पूर्ण,
	अणु 3872768,  5000पूर्ण,
	अणु 3858944,  6000पूर्ण,
	अणु 3851520,  7000पूर्ण,
	अणु 3838976,  8000पूर्ण,
	अणु 3829248,  9000पूर्ण,
	अणु 3818240, 10000पूर्ण,
	अणु 3806976, 11000पूर्ण,
	अणु 3791872, 12000पूर्ण,
	अणु 3767040, 13000पूर्ण,
	अणु 3720960, 14000पूर्ण,
	अणु 3637504, 15000पूर्ण,
	अणु 3498496, 16000पूर्ण,
	अणु 3296000, 17000पूर्ण,
	अणु 3031040, 18000पूर्ण,
	अणु 2715392, 19000पूर्ण,
	अणु 2362624, 20000पूर्ण,
	अणु 1963264, 21000पूर्ण,
	अणु 1649664, 22000पूर्ण,
	अणु 1366784, 23000पूर्ण,
	अणु 1120768, 24000पूर्ण,
	अणु  890880, 25000पूर्ण,
	अणु  723456, 26000पूर्ण,
	अणु  612096, 27000पूर्ण,
	अणु  518912, 28000पूर्ण,
	अणु  448256, 29000पूर्ण,
	अणु  388864, 30000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा linear_segments cnr_16qam_table[] = अणु
	अणु 5314816,     0पूर्ण,
	अणु 5219072,  1000पूर्ण,
	अणु 5118720,  2000पूर्ण,
	अणु 4998912,  3000पूर्ण,
	अणु 4875520,  4000पूर्ण,
	अणु 4736000,  5000पूर्ण,
	अणु 4604160,  6000पूर्ण,
	अणु 4458752,  7000पूर्ण,
	अणु 4300288,  8000पूर्ण,
	अणु 4092928,  9000पूर्ण,
	अणु 3836160, 10000पूर्ण,
	अणु 3521024, 11000पूर्ण,
	अणु 3155968, 12000पूर्ण,
	अणु 2756864, 13000पूर्ण,
	अणु 2347008, 14000पूर्ण,
	अणु 1955072, 15000पूर्ण,
	अणु 1593600, 16000पूर्ण,
	अणु 1297920, 17000पूर्ण,
	अणु 1043968, 18000पूर्ण,
	अणु  839680, 19000पूर्ण,
	अणु  672256, 20000पूर्ण,
	अणु  523008, 21000पूर्ण,
	अणु  424704, 22000पूर्ण,
	अणु  345088, 23000पूर्ण,
	अणु  280064, 24000पूर्ण,
	अणु  221440, 25000पूर्ण,
	अणु  179712, 26000पूर्ण,
	अणु  151040, 27000पूर्ण,
	अणु  128512, 28000पूर्ण,
	अणु  110080, 29000पूर्ण,
	अणु   95744, 30000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा linear_segments cnr_qpsk_table[] = अणु
	अणु 2834176,     0पूर्ण,
	अणु 2683648,  1000पूर्ण,
	अणु 2536960,  2000पूर्ण,
	अणु 2391808,  3000पूर्ण,
	अणु 2133248,  4000पूर्ण,
	अणु 1906176,  5000पूर्ण,
	अणु 1666560,  6000पूर्ण,
	अणु 1422080,  7000पूर्ण,
	अणु 1189632,  8000पूर्ण,
	अणु  976384,  9000पूर्ण,
	अणु  790272, 10000पूर्ण,
	अणु  633344, 11000पूर्ण,
	अणु  505600, 12000पूर्ण,
	अणु  402944, 13000पूर्ण,
	अणु  320768, 14000पूर्ण,
	अणु  255488, 15000पूर्ण,
	अणु  204032, 16000पूर्ण,
	अणु  163072, 17000पूर्ण,
	अणु  130304, 18000पूर्ण,
	अणु  105216, 19000पूर्ण,
	अणु   83456, 20000पूर्ण,
	अणु   65024, 21000पूर्ण,
	अणु   52480, 22000पूर्ण,
	अणु   42752, 23000पूर्ण,
	अणु   34560, 24000पूर्ण,
	अणु   27136, 25000पूर्ण,
	अणु   22016, 26000पूर्ण,
	अणु   18432, 27000पूर्ण,
	अणु   15616, 28000पूर्ण,
	अणु   13312, 29000पूर्ण,
	अणु   11520, 30000पूर्ण,
पूर्ण;

अटल u32 पूर्णांकerpolate_value(u32 value, स्थिर काष्ठा linear_segments *segments,
			     अचिन्हित len)
अणु
	u64 पंचांगp64;
	u32 dx, dy;
	पूर्णांक i, ret;

	अगर (value >= segments[0].x)
		वापस segments[0].y;
	अगर (value < segments[len-1].x)
		वापस segments[len-1].y;

	क्रम (i = 1; i < len - 1; i++) अणु
		/* If value is identical, no need to पूर्णांकerpolate */
		अगर (value == segments[i].x)
			वापस segments[i].y;
		अगर (value > segments[i].x)
			अवरोध;
	पूर्ण

	/* Linear पूर्णांकerpolation between the two (x,y) poपूर्णांकs */
	dy = segments[i].y - segments[i - 1].y;
	dx = segments[i - 1].x - segments[i].x;
	पंचांगp64 = value - segments[i].x;
	पंचांगp64 *= dy;
	करो_भाग(पंचांगp64, dx);
	ret = segments[i].y - पंचांगp64;

	वापस ret;
पूर्ण

अटल पूर्णांक mb86a20s_get_मुख्य_CNR(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 cnr_linear, cnr;
	पूर्णांक rc, val;

	/* Check अगर CNR is available */
	rc = mb86a20s_पढ़ोreg(state, 0x45);
	अगर (rc < 0)
		वापस rc;

	अगर (!(rc & 0x40)) अणु
		dev_dbg(&state->i2c->dev, "%s: CNR is not available yet.\n",
			 __func__);
		वापस -EBUSY;
	पूर्ण
	val = rc;

	rc = mb86a20s_पढ़ोreg(state, 0x46);
	अगर (rc < 0)
		वापस rc;
	cnr_linear = rc << 8;

	rc = mb86a20s_पढ़ोreg(state, 0x46);
	अगर (rc < 0)
		वापस rc;
	cnr_linear |= rc;

	cnr = पूर्णांकerpolate_value(cnr_linear,
				cnr_to_db_table, ARRAY_SIZE(cnr_to_db_table));

	c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	c->cnr.stat[0].svalue = cnr;

	dev_dbg(&state->i2c->dev, "%s: CNR is %d.%03d dB (%d)\n",
		__func__, cnr / 1000, cnr % 1000, cnr_linear);

	/* CNR counter reset */
	rc = mb86a20s_ग_लिखोreg(state, 0x45, val | 0x10);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x45, val & 0x6f);

	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_get_blk_error_layer_CNR(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 mer, cnr;
	पूर्णांक rc, val, layer;
	स्थिर काष्ठा linear_segments *segs;
	अचिन्हित segs_len;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	/* Check अगर the measures are alपढ़ोy available */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0x5b);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;

	/* Check अगर data is available */
	अगर (!(rc & 0x01)) अणु
		dev_dbg(&state->i2c->dev,
			"%s: MER measures aren't available yet.\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/* Read all layers */
	क्रम (layer = 0; layer < NUM_LAYERS; layer++) अणु
		अगर (!(c->isdbt_layer_enabled & (1 << layer))) अणु
			c->cnr.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
			जारी;
		पूर्ण

		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0x52 + layer * 3);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_पढ़ोreg(state, 0x51);
		अगर (rc < 0)
			वापस rc;
		mer = rc << 16;
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0x53 + layer * 3);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_पढ़ोreg(state, 0x51);
		अगर (rc < 0)
			वापस rc;
		mer |= rc << 8;
		rc = mb86a20s_ग_लिखोreg(state, 0x50, 0x54 + layer * 3);
		अगर (rc < 0)
			वापस rc;
		rc = mb86a20s_पढ़ोreg(state, 0x51);
		अगर (rc < 0)
			वापस rc;
		mer |= rc;

		चयन (c->layer[layer].modulation) अणु
		हाल DQPSK:
		हाल QPSK:
			segs = cnr_qpsk_table;
			segs_len = ARRAY_SIZE(cnr_qpsk_table);
			अवरोध;
		हाल QAM_16:
			segs = cnr_16qam_table;
			segs_len = ARRAY_SIZE(cnr_16qam_table);
			अवरोध;
		शेष:
		हाल QAM_64:
			segs = cnr_64qam_table;
			segs_len = ARRAY_SIZE(cnr_64qam_table);
			अवरोध;
		पूर्ण
		cnr = पूर्णांकerpolate_value(mer, segs, segs_len);

		c->cnr.stat[1 + layer].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[1 + layer].svalue = cnr;

		dev_dbg(&state->i2c->dev,
			"%s: CNR for layer %c is %d.%03d dB (MER = %d).\n",
			__func__, 'A' + layer, cnr / 1000, cnr % 1000, mer);

	पूर्ण

	/* Start a new MER measurement */
	/* MER counter reset */
	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0x50);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_पढ़ोreg(state, 0x51);
	अगर (rc < 0)
		वापस rc;
	val = rc;

	rc = mb86a20s_ग_लिखोreg(state, 0x51, val | 0x01);
	अगर (rc < 0)
		वापस rc;
	rc = mb86a20s_ग_लिखोreg(state, 0x51, val & 0x06);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम mb86a20s_stats_not_पढ़ोy(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक layer;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	/* Fill the length of each status counter */

	/* Only global stats */
	c->strength.len = 1;

	/* Per-layer stats - 3 layers + global */
	c->cnr.len = NUM_LAYERS + 1;
	c->pre_bit_error.len = NUM_LAYERS + 1;
	c->pre_bit_count.len = NUM_LAYERS + 1;
	c->post_bit_error.len = NUM_LAYERS + 1;
	c->post_bit_count.len = NUM_LAYERS + 1;
	c->block_error.len = NUM_LAYERS + 1;
	c->block_count.len = NUM_LAYERS + 1;

	/* Signal is always available */
	c->strength.stat[0].scale = FE_SCALE_RELATIVE;
	c->strength.stat[0].uvalue = 0;

	/* Put all of them at FE_SCALE_NOT_AVAILABLE */
	क्रम (layer = 0; layer < NUM_LAYERS + 1; layer++) अणु
		c->cnr.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
		c->pre_bit_error.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
		c->pre_bit_count.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_error.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[layer].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण
पूर्ण

अटल पूर्णांक mb86a20s_get_stats(काष्ठा dvb_frontend *fe, पूर्णांक status_nr)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc = 0, layer;
	u32 bit_error = 0, bit_count = 0;
	u32 t_pre_bit_error = 0, t_pre_bit_count = 0;
	u32 t_post_bit_error = 0, t_post_bit_count = 0;
	u32 block_error = 0, block_count = 0;
	u32 t_block_error = 0, t_block_count = 0;
	पूर्णांक active_layers = 0, pre_ber_layers = 0, post_ber_layers = 0;
	पूर्णांक per_layers = 0;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	mb86a20s_get_मुख्य_CNR(fe);

	/* Get per-layer stats */
	mb86a20s_get_blk_error_layer_CNR(fe);

	/*
	 * At state 7, only CNR is available
	 * For BER measures, state=9 is required
	 * FIXME: we may get MER measures with state=8
	 */
	अगर (status_nr < 9)
		वापस 0;

	क्रम (layer = 0; layer < NUM_LAYERS; layer++) अणु
		अगर (c->isdbt_layer_enabled & (1 << layer)) अणु
			/* Layer is active and has rc segments */
			active_layers++;

			/* Handle BER beक्रमe vterbi */
			rc = mb86a20s_get_pre_ber(fe, layer,
						  &bit_error, &bit_count);
			अगर (rc >= 0) अणु
				c->pre_bit_error.stat[1 + layer].scale = FE_SCALE_COUNTER;
				c->pre_bit_error.stat[1 + layer].uvalue += bit_error;
				c->pre_bit_count.stat[1 + layer].scale = FE_SCALE_COUNTER;
				c->pre_bit_count.stat[1 + layer].uvalue += bit_count;
			पूर्ण अन्यथा अगर (rc != -EBUSY) अणु
				/*
					* If an I/O error happened,
					* measures are now unavailable
					*/
				c->pre_bit_error.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
				c->pre_bit_count.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
				dev_err(&state->i2c->dev,
					"%s: Can't get BER for layer %c (error %d).\n",
					__func__, 'A' + layer, rc);
			पूर्ण
			अगर (c->block_error.stat[1 + layer].scale != FE_SCALE_NOT_AVAILABLE)
				pre_ber_layers++;

			/* Handle BER post vterbi */
			rc = mb86a20s_get_post_ber(fe, layer,
						   &bit_error, &bit_count);
			अगर (rc >= 0) अणु
				c->post_bit_error.stat[1 + layer].scale = FE_SCALE_COUNTER;
				c->post_bit_error.stat[1 + layer].uvalue += bit_error;
				c->post_bit_count.stat[1 + layer].scale = FE_SCALE_COUNTER;
				c->post_bit_count.stat[1 + layer].uvalue += bit_count;
			पूर्ण अन्यथा अगर (rc != -EBUSY) अणु
				/*
					* If an I/O error happened,
					* measures are now unavailable
					*/
				c->post_bit_error.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
				c->post_bit_count.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
				dev_err(&state->i2c->dev,
					"%s: Can't get BER for layer %c (error %d).\n",
					__func__, 'A' + layer, rc);
			पूर्ण
			अगर (c->block_error.stat[1 + layer].scale != FE_SCALE_NOT_AVAILABLE)
				post_ber_layers++;

			/* Handle Block errors क्रम PER/UCB reports */
			rc = mb86a20s_get_blk_error(fe, layer,
						&block_error,
						&block_count);
			अगर (rc >= 0) अणु
				c->block_error.stat[1 + layer].scale = FE_SCALE_COUNTER;
				c->block_error.stat[1 + layer].uvalue += block_error;
				c->block_count.stat[1 + layer].scale = FE_SCALE_COUNTER;
				c->block_count.stat[1 + layer].uvalue += block_count;
			पूर्ण अन्यथा अगर (rc != -EBUSY) अणु
				/*
					* If an I/O error happened,
					* measures are now unavailable
					*/
				c->block_error.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
				c->block_count.stat[1 + layer].scale = FE_SCALE_NOT_AVAILABLE;
				dev_err(&state->i2c->dev,
					"%s: Can't get PER for layer %c (error %d).\n",
					__func__, 'A' + layer, rc);

			पूर्ण
			अगर (c->block_error.stat[1 + layer].scale != FE_SCALE_NOT_AVAILABLE)
				per_layers++;

			/* Update total preBER */
			t_pre_bit_error += c->pre_bit_error.stat[1 + layer].uvalue;
			t_pre_bit_count += c->pre_bit_count.stat[1 + layer].uvalue;

			/* Update total postBER */
			t_post_bit_error += c->post_bit_error.stat[1 + layer].uvalue;
			t_post_bit_count += c->post_bit_count.stat[1 + layer].uvalue;

			/* Update total PER */
			t_block_error += c->block_error.stat[1 + layer].uvalue;
			t_block_count += c->block_count.stat[1 + layer].uvalue;
		पूर्ण
	पूर्ण

	/*
	 * Start showing global count अगर at least one error count is
	 * available.
	 */
	अगर (pre_ber_layers) अणु
		/*
		 * At least one per-layer BER measure was पढ़ो. We can now
		 * calculate the total BER
		 *
		 * Total Bit Error/Count is calculated as the sum of the
		 * bit errors on all active layers.
		 */
		c->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->pre_bit_error.stat[0].uvalue = t_pre_bit_error;
		c->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->pre_bit_count.stat[0].uvalue = t_pre_bit_count;
	पूर्ण अन्यथा अणु
		c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	पूर्ण

	/*
	 * Start showing global count अगर at least one error count is
	 * available.
	 */
	अगर (post_ber_layers) अणु
		/*
		 * At least one per-layer BER measure was पढ़ो. We can now
		 * calculate the total BER
		 *
		 * Total Bit Error/Count is calculated as the sum of the
		 * bit errors on all active layers.
		 */
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = t_post_bit_error;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = t_post_bit_count;
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	पूर्ण

	अगर (per_layers) अणु
		/*
		 * At least one per-layer UCB measure was पढ़ो. We can now
		 * calculate the total UCB
		 *
		 * Total block Error/Count is calculated as the sum of the
		 * block errors on all active layers.
		 */
		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue = t_block_error;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue = t_block_count;
	पूर्ण अन्यथा अणु
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * The functions below are called via DVB callbacks, so they need to
 * properly use the I2C gate control
 */

अटल पूर्णांक mb86a20s_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	u64 pll;
	u32 fclk;
	पूर्णांक rc;
	u8  regD5 = 1, reg71, reg09 = 0x3a;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	/* Initialize the frontend */
	rc = mb86a20s_ग_लिखोregdata(state, mb86a20s_init1);
	अगर (rc < 0)
		जाओ err;

	अगर (!state->inversion)
		reg09 |= 0x04;
	rc = mb86a20s_ग_लिखोreg(state, 0x09, reg09);
	अगर (rc < 0)
		जाओ err;
	अगर (!state->bw)
		reg71 = 1;
	अन्यथा
		reg71 = 0;
	rc = mb86a20s_ग_लिखोreg(state, 0x39, reg71);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x71, state->bw);
	अगर (rc < 0)
		जाओ err;
	अगर (state->subchannel) अणु
		rc = mb86a20s_ग_लिखोreg(state, 0x44, state->subchannel);
		अगर (rc < 0)
			जाओ err;
	पूर्ण

	fclk = state->config->fclk;
	अगर (!fclk)
		fclk = 32571428;

	/* Adjust IF frequency to match tuner */
	अगर (fe->ops.tuner_ops.get_अगर_frequency)
		fe->ops.tuner_ops.get_अगर_frequency(fe, &state->अगर_freq);

	अगर (!state->अगर_freq)
		state->अगर_freq = 3300000;

	pll = (((u64)1) << 34) * state->अगर_freq;
	करो_भाग(pll, 63 * fclk);
	pll = (1 << 25) - pll;
	rc = mb86a20s_ग_लिखोreg(state, 0x28, 0x2a);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x29, (pll >> 16) & 0xff);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x2a, (pll >> 8) & 0xff);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x2b, pll & 0xff);
	अगर (rc < 0)
		जाओ err;
	dev_dbg(&state->i2c->dev, "%s: fclk=%d, IF=%d, clock reg=0x%06llx\n",
		__func__, fclk, state->अगर_freq, (दीर्घ दीर्घ)pll);

	/* pll = freq[Hz] * 2^24/10^6 / 16.285714286 */
	pll = state->अगर_freq * 1677721600L;
	करो_भाग(pll, 1628571429L);
	rc = mb86a20s_ग_लिखोreg(state, 0x28, 0x20);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x29, (pll >> 16) & 0xff);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x2a, (pll >> 8) & 0xff);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x2b, pll & 0xff);
	अगर (rc < 0)
		जाओ err;
	dev_dbg(&state->i2c->dev, "%s: IF=%d, IF reg=0x%06llx\n",
		__func__, state->अगर_freq, (दीर्घ दीर्घ)pll);

	अगर (!state->config->is_serial)
		regD5 &= ~1;

	rc = mb86a20s_ग_लिखोreg(state, 0x50, 0xd5);
	अगर (rc < 0)
		जाओ err;
	rc = mb86a20s_ग_लिखोreg(state, 0x51, regD5);
	अगर (rc < 0)
		जाओ err;

	rc = mb86a20s_ग_लिखोregdata(state, mb86a20s_init2);
	अगर (rc < 0)
		जाओ err;


err:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (rc < 0) अणु
		state->need_init = true;
		dev_info(&state->i2c->dev,
			 "mb86a20s: Init failed. Will try again later\n");
	पूर्ण अन्यथा अणु
		state->need_init = false;
		dev_dbg(&state->i2c->dev, "Initialization succeeded.\n");
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc, अगर_freq;
	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (!c->isdbt_layer_enabled)
		c->isdbt_layer_enabled = 7;

	अगर (c->isdbt_layer_enabled == 1)
		state->bw = MB86A20S_1SEG;
	अन्यथा अगर (c->isdbt_partial_reception)
		state->bw = MB86A20S_13SEG_PARTIAL;
	अन्यथा
		state->bw = MB86A20S_13SEG;

	अगर (c->inversion == INVERSION_ON)
		state->inversion = true;
	अन्यथा
		state->inversion = false;

	अगर (!c->isdbt_sb_mode) अणु
		state->subchannel = 0;
	पूर्ण अन्यथा अणु
		अगर (c->isdbt_sb_subchannel >= ARRAY_SIZE(mb86a20s_subchannel))
			c->isdbt_sb_subchannel = 0;

		state->subchannel = mb86a20s_subchannel[c->isdbt_sb_subchannel];
	पूर्ण

	/*
	 * Gate should alपढ़ोy be खोलोed, but it करोesn't hurt to
	 * द्विगुन-check
	 */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	fe->ops.tuner_ops.set_params(fe);

	अगर (fe->ops.tuner_ops.get_अगर_frequency)
		fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_freq);

	/*
	 * Make it more reliable: अगर, क्रम some reason, the initial
	 * device initialization करोesn't happen, initialize it when
	 * a SBTVD parameters are adjusted.
	 *
	 * Unक्रमtunately, due to a hard to track bug at tda829x/tda18271,
	 * the agc callback logic is not called during DVB attach समय,
	 * causing mb86a20s to not be initialized with Kworld SBTVD.
	 * So, this hack is needed, in order to make Kworld SBTVD to work.
	 *
	 * It is also needed to change the IF after the initial init.
	 *
	 * HACK: Always init the frontend when set_frontend is called:
	 * it was noticed that, on some devices, it fails to lock on a
	 * dअगरferent channel. So, it is better to reset everything, even
	 * wasting some समय, than to loose channel lock.
	 */
	mb86a20s_initfe(fe);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	rc = mb86a20s_ग_लिखोregdata(state, mb86a20s_reset_reception);
	mb86a20s_reset_counters(fe);
	mb86a20s_stats_not_पढ़ोy(fe);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_पढ़ो_status_and_stats(काष्ठा dvb_frontend *fe,
					  क्रमागत fe_status *status)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	पूर्णांक rc, status_nr;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	/* Get lock */
	status_nr = mb86a20s_पढ़ो_status(fe, status);
	अगर (status_nr < 7) अणु
		mb86a20s_stats_not_पढ़ोy(fe);
		mb86a20s_reset_frontend_cache(fe);
	पूर्ण
	अगर (status_nr < 0) अणु
		dev_err(&state->i2c->dev,
			"%s: Can't read frontend lock status\n", __func__);
		rc = status_nr;
		जाओ error;
	पूर्ण

	/* Get संकेत strength */
	rc = mb86a20s_पढ़ो_संकेत_strength(fe);
	अगर (rc < 0) अणु
		dev_err(&state->i2c->dev,
			"%s: Can't reset VBER registers.\n", __func__);
		mb86a20s_stats_not_पढ़ोy(fe);
		mb86a20s_reset_frontend_cache(fe);

		rc = 0;		/* Status is OK */
		जाओ error;
	पूर्ण

	अगर (status_nr >= 7) अणु
		/* Get TMCC info*/
		rc = mb86a20s_get_frontend(fe);
		अगर (rc < 0) अणु
			dev_err(&state->i2c->dev,
				"%s: Can't get FE TMCC data.\n", __func__);
			rc = 0;		/* Status is OK */
			जाओ error;
		पूर्ण

		/* Get statistics */
		rc = mb86a20s_get_stats(fe, status_nr);
		अगर (rc < 0 && rc != -EBUSY) अणु
			dev_err(&state->i2c->dev,
				"%s: Can't get FE statistics.\n", __func__);
			rc = 0;
			जाओ error;
		पूर्ण
		rc = 0;	/* Don't वापस EBUSY to userspace */
	पूर्ण
	जाओ ok;

error:
	mb86a20s_stats_not_पढ़ोy(fe);

ok:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक mb86a20s_पढ़ो_संकेत_strength_from_cache(काष्ठा dvb_frontend *fe,
						    u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;


	*strength = c->strength.stat[0].uvalue;

	वापस 0;
पूर्ण

अटल पूर्णांक mb86a20s_tune(काष्ठा dvb_frontend *fe,
			bool re_tune,
			अचिन्हित पूर्णांक mode_flags,
			अचिन्हित पूर्णांक *delay,
			क्रमागत fe_status *status)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;
	पूर्णांक rc = 0;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	अगर (re_tune)
		rc = mb86a20s_set_frontend(fe);

	अगर (!(mode_flags & FE_TUNE_MODE_ONESHOT))
		mb86a20s_पढ़ो_status_and_stats(fe, status);

	वापस rc;
पूर्ण

अटल व्योम mb86a20s_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a20s_state *state = fe->demodulator_priv;

	dev_dbg(&state->i2c->dev, "%s called.\n", __func__);

	kमुक्त(state);
पूर्ण

अटल क्रमागत dvbfe_algo mb86a20s_get_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mb86a20s_ops;

काष्ठा dvb_frontend *mb86a20s_attach(स्थिर काष्ठा mb86a20s_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा mb86a20s_state *state;
	u8	rev;

	dev_dbg(&i2c->dev, "%s called.\n", __func__);

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &mb86a20s_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* Check अगर it is a mb86a20s frontend */
	rev = mb86a20s_पढ़ोreg(state, 0);
	अगर (rev != 0x13) अणु
		kमुक्त(state);
		dev_dbg(&i2c->dev,
			"Frontend revision %d is unknown - aborting.\n",
		       rev);
		वापस शून्य;
	पूर्ण

	dev_info(&i2c->dev, "Detected a Fujitsu mb86a20s frontend\n");
	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(mb86a20s_attach);

अटल स्थिर काष्ठा dvb_frontend_ops mb86a20s_ops = अणु
	.delsys = अणु SYS_ISDBT पूर्ण,
	/* Use dib8000 values per शेष */
	.info = अणु
		.name = "Fujitsu mb86A20s",
		.caps = FE_CAN_RECOVER  |
			FE_CAN_FEC_1_2  | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6  | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK     | FE_CAN_QAM_16  | FE_CAN_QAM_64 |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_QAM_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO    | FE_CAN_HIERARCHY_AUTO,
		/* Actually, those values depend on the used tuner */
		.frequency_min_hz =  45 * MHz,
		.frequency_max_hz = 864 * MHz,
		.frequency_stepsize_hz = 62500,
	पूर्ण,

	.release = mb86a20s_release,

	.init = mb86a20s_initfe,
	.set_frontend = mb86a20s_set_frontend,
	.पढ़ो_status = mb86a20s_पढ़ो_status_and_stats,
	.पढ़ो_संकेत_strength = mb86a20s_पढ़ो_संकेत_strength_from_cache,
	.tune = mb86a20s_tune,
	.get_frontend_algo = mb86a20s_get_frontend_algo,
पूर्ण;

MODULE_DESCRIPTION("DVB Frontend module for Fujitsu mb86A20s hardware");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL");
