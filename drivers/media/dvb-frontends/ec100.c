<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * E3C EC100 demodulator driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/dvb_frontend.h>
#समावेश "ec100.h"

काष्ठा ec100_state अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend frontend;
	काष्ठा ec100_config config;

	u16 ber;
पूर्ण;

/* ग_लिखो single रेजिस्टर */
अटल पूर्णांक ec100_ग_लिखो_reg(काष्ठा ec100_state *state, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	u8 buf[2] = अणुreg, valपूर्ण;
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = state->config.demod_address,
			.flags = 0,
			.len = माप(buf),
			.buf = buf,
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 1);
	अगर (ret == 1) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		dev_warn(&state->i2c->dev, "%s: i2c wr failed=%d reg=%02x\n",
				KBUILD_MODNAME, ret, reg);
		ret = -EREMOTEIO;
	पूर्ण

	वापस ret;
पूर्ण

/* पढ़ो single रेजिस्टर */
अटल पूर्णांक ec100_पढ़ो_reg(काष्ठा ec100_state *state, u8 reg, u8 *val)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = state->config.demod_address,
			.flags = 0,
			.len = 1,
			.buf = &reg
		पूर्ण, अणु
			.addr = state->config.demod_address,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = val
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);
	अगर (ret == 2) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		dev_warn(&state->i2c->dev, "%s: i2c rd failed=%d reg=%02x\n",
				KBUILD_MODNAME, ret, reg);
		ret = -EREMOTEIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ec100_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा ec100_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 पंचांगp, पंचांगp2;

	dev_dbg(&state->i2c->dev, "%s: frequency=%d bandwidth_hz=%d\n",
			__func__, c->frequency, c->bandwidth_hz);

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	ret = ec100_ग_लिखो_reg(state, 0x04, 0x06);
	अगर (ret)
		जाओ error;
	ret = ec100_ग_लिखो_reg(state, 0x67, 0x58);
	अगर (ret)
		जाओ error;
	ret = ec100_ग_लिखो_reg(state, 0x05, 0x18);
	अगर (ret)
		जाओ error;

	/* reg/bw |   6  |   7  |   8
	   -------+------+------+------
	   A 0x1b | 0xa1 | 0xe7 | 0x2c
	   A 0x1c | 0x55 | 0x63 | 0x72
	   -------+------+------+------
	   B 0x1b | 0xb7 | 0x00 | 0x49
	   B 0x1c | 0x55 | 0x64 | 0x72 */

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		पंचांगp = 0xb7;
		पंचांगp2 = 0x55;
		अवरोध;
	हाल 7000000:
		पंचांगp = 0x00;
		पंचांगp2 = 0x64;
		अवरोध;
	हाल 8000000:
	शेष:
		पंचांगp = 0x49;
		पंचांगp2 = 0x72;
	पूर्ण

	ret = ec100_ग_लिखो_reg(state, 0x1b, पंचांगp);
	अगर (ret)
		जाओ error;
	ret = ec100_ग_लिखो_reg(state, 0x1c, पंचांगp2);
	अगर (ret)
		जाओ error;

	ret = ec100_ग_लिखो_reg(state, 0x0c, 0xbb); /* अगर freq */
	अगर (ret)
		जाओ error;
	ret = ec100_ग_लिखो_reg(state, 0x0d, 0x31); /* अगर freq */
	अगर (ret)
		जाओ error;

	ret = ec100_ग_लिखो_reg(state, 0x08, 0x24);
	अगर (ret)
		जाओ error;

	ret = ec100_ग_लिखो_reg(state, 0x00, 0x00); /* go */
	अगर (ret)
		जाओ error;
	ret = ec100_ग_लिखो_reg(state, 0x00, 0x20); /* go */
	अगर (ret)
		जाओ error;

	वापस ret;
error:
	dev_dbg(&state->i2c->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ec100_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	fesettings->min_delay_ms = 300;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ec100_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा ec100_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 पंचांगp;
	*status = 0;

	ret = ec100_पढ़ो_reg(state, 0x42, &पंचांगp);
	अगर (ret)
		जाओ error;

	अगर (पंचांगp & 0x80) अणु
		/* bit7 set - have lock */
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI |
			FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण अन्यथा अणु
		ret = ec100_पढ़ो_reg(state, 0x01, &पंचांगp);
		अगर (ret)
			जाओ error;

		अगर (पंचांगp & 0x10) अणु
			/* bit4 set - have संकेत */
			*status |= FE_HAS_SIGNAL;
			अगर (!(पंचांगp & 0x01)) अणु
				/* bit0 clear - have ~valid संकेत */
				*status |= FE_HAS_CARRIER |  FE_HAS_VITERBI;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
error:
	dev_dbg(&state->i2c->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ec100_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा ec100_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 पंचांगp, पंचांगp2;
	u16 ber2;

	*ber = 0;

	ret = ec100_पढ़ो_reg(state, 0x65, &पंचांगp);
	अगर (ret)
		जाओ error;
	ret = ec100_पढ़ो_reg(state, 0x66, &पंचांगp2);
	अगर (ret)
		जाओ error;

	ber2 = (पंचांगp2 << 8) | पंचांगp;

	/* अगर counter overflow or clear */
	अगर (ber2 < state->ber)
		*ber = ber2;
	अन्यथा
		*ber = ber2 - state->ber;

	state->ber = ber2;

	वापस ret;
error:
	dev_dbg(&state->i2c->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ec100_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा ec100_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 पंचांगp;

	ret = ec100_पढ़ो_reg(state, 0x24, &पंचांगp);
	अगर (ret) अणु
		*strength = 0;
		जाओ error;
	पूर्ण

	*strength = ((पंचांगp << 8) | पंचांगp);

	वापस ret;
error:
	dev_dbg(&state->i2c->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ec100_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	*snr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ec100_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	*ucblocks = 0;
	वापस 0;
पूर्ण

अटल व्योम ec100_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ec100_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops ec100_ops;

काष्ठा dvb_frontend *ec100_attach(स्थिर काष्ठा ec100_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	पूर्णांक ret;
	काष्ठा ec100_state *state = शून्य;
	u8 पंचांगp;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा ec100_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	स_नकल(&state->config, config, माप(काष्ठा ec100_config));

	/* check अगर the demod is there */
	ret = ec100_पढ़ो_reg(state, 0x33, &पंचांगp);
	अगर (ret || पंचांगp != 0x0b)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &ec100_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	वापस &state->frontend;
error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ec100_attach);

अटल स्थिर काष्ठा dvb_frontend_ops ec100_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "E3C EC100 DVB-T",
		.caps =
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 |
			FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_MUTE_TS
	पूर्ण,

	.release = ec100_release,
	.set_frontend = ec100_set_frontend,
	.get_tune_settings = ec100_get_tune_settings,
	.पढ़ो_status = ec100_पढ़ो_status,
	.पढ़ो_ber = ec100_पढ़ो_ber,
	.पढ़ो_संकेत_strength = ec100_पढ़ो_संकेत_strength,
	.पढ़ो_snr = ec100_पढ़ो_snr,
	.पढ़ो_ucblocks = ec100_पढ़ो_ucblocks,
पूर्ण;

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("E3C EC100 DVB-T demodulator driver");
MODULE_LICENSE("GPL");
