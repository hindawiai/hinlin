<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Legend Silicon LGS-8GL5 DMB-TH OFDM demodulator driver

    Copyright (C) 2008 Sirius International (Hong Kong) Limited
	Timothy Lee <timothy.lee@siriushk.com>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <media/dvb_frontend.h>
#समावेश "lgs8gl5.h"


#घोषणा REG_RESET		0x02
#घोषणा REG_RESET_OFF			0x01
#घोषणा REG_03			0x03
#घोषणा REG_04			0x04
#घोषणा REG_07			0x07
#घोषणा REG_09			0x09
#घोषणा REG_0A			0x0a
#घोषणा REG_0B			0x0b
#घोषणा REG_0C			0x0c
#घोषणा REG_37			0x37
#घोषणा REG_STRENGTH		0x4b
#घोषणा REG_STRENGTH_MASK		0x7f
#घोषणा REG_STRENGTH_CARRIER		0x80
#घोषणा REG_INVERSION		0x7c
#घोषणा REG_INVERSION_ON		0x80
#घोषणा REG_7D			0x7d
#घोषणा REG_7E			0x7e
#घोषणा REG_A2			0xa2
#घोषणा REG_STATUS		0xa4
#घोषणा REG_STATUS_SYNC		0x04
#घोषणा REG_STATUS_LOCK		0x01


काष्ठा lgs8gl5_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा lgs8gl5_config *config;
	काष्ठा dvb_frontend frontend;
पूर्ण;


अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "lgs8gl5: " args); \
	पूर्ण जबतक (0)


/* Writes पूर्णांकo demod's रेजिस्टर */
अटल पूर्णांक
lgs8gl5_ग_लिखो_reg(काष्ठा lgs8gl5_state *state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणुreg, dataपूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr  = state->config->demod_address,
		.flags = 0,
		.buf   = buf,
		.len   = 2
	पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);
	अगर (ret != 1)
		dprपूर्णांकk("%s: error (reg=0x%02x, val=0x%02x, ret=%i)\n",
			__func__, reg, data, ret);
	वापस (ret != 1) ? -1 : 0;
पूर्ण


/* Reads from demod's रेजिस्टर */
अटल पूर्णांक
lgs8gl5_पढ़ो_reg(काष्ठा lgs8gl5_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणुregपूर्ण;
	u8 b1[] = अणु0पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr  = state->config->demod_address,
			.flags = 0,
			.buf   = b0,
			.len   = 1
		पूर्ण,
		अणु
			.addr  = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf   = b1,
			.len   = 1
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);
	अगर (ret != 2)
		वापस -EIO;

	वापस b1[0];
पूर्ण


अटल पूर्णांक
lgs8gl5_update_reg(काष्ठा lgs8gl5_state *state, u8 reg, u8 data)
अणु
	lgs8gl5_पढ़ो_reg(state, reg);
	lgs8gl5_ग_लिखो_reg(state, reg, data);
	वापस 0;
पूर्ण


/* Writes पूर्णांकo alternate device's रेजिस्टर */
/* TODO:  Find out what that device is क्रम! */
अटल पूर्णांक
lgs8gl5_update_alt_reg(काष्ठा lgs8gl5_state *state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 b0[] = अणुregपूर्ण;
	u8 b1[] = अणु0पूर्ण;
	u8 b2[] = अणुreg, dataपूर्ण;
	काष्ठा i2c_msg msg[3] = अणु
		अणु
			.addr  = state->config->demod_address + 2,
			.flags = 0,
			.buf   = b0,
			.len   = 1
		पूर्ण,
		अणु
			.addr  = state->config->demod_address + 2,
			.flags = I2C_M_RD,
			.buf   = b1,
			.len   = 1
		पूर्ण,
		अणु
			.addr  = state->config->demod_address + 2,
			.flags = 0,
			.buf   = b2,
			.len   = 2
		पूर्ण,
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 3);
	वापस (ret != 3) ? -1 : 0;
पूर्ण


अटल व्योम
lgs8gl5_soft_reset(काष्ठा lgs8gl5_state *state)
अणु
	u8 val;

	dprपूर्णांकk("%s\n", __func__);

	val = lgs8gl5_पढ़ो_reg(state, REG_RESET);
	lgs8gl5_ग_लिखो_reg(state, REG_RESET, val & ~REG_RESET_OFF);
	lgs8gl5_ग_लिखो_reg(state, REG_RESET, val | REG_RESET_OFF);
	msleep(5);
पूर्ण


/* Starts demodulation */
अटल व्योम
lgs8gl5_start_demod(काष्ठा lgs8gl5_state *state)
अणु
	u8  val;
	पूर्णांक n;

	dprपूर्णांकk("%s\n", __func__);

	lgs8gl5_update_alt_reg(state, 0xc2, 0x28);
	lgs8gl5_soft_reset(state);
	lgs8gl5_update_reg(state, REG_07, 0x10);
	lgs8gl5_update_reg(state, REG_07, 0x10);
	lgs8gl5_ग_लिखो_reg(state, REG_09, 0x0e);
	lgs8gl5_ग_लिखो_reg(state, REG_0A, 0xe5);
	lgs8gl5_ग_लिखो_reg(state, REG_0B, 0x35);
	lgs8gl5_ग_लिखो_reg(state, REG_0C, 0x30);

	lgs8gl5_update_reg(state, REG_03, 0x00);
	lgs8gl5_update_reg(state, REG_7E, 0x01);
	lgs8gl5_update_alt_reg(state, 0xc5, 0x00);
	lgs8gl5_update_reg(state, REG_04, 0x02);
	lgs8gl5_update_reg(state, REG_37, 0x01);
	lgs8gl5_soft_reset(state);

	/* Wait क्रम carrier */
	क्रम (n = 0;  n < 10;  n++) अणु
		val = lgs8gl5_पढ़ो_reg(state, REG_STRENGTH);
		dprपूर्णांकk("Wait for carrier[%d] 0x%02X\n", n, val);
		अगर (val & REG_STRENGTH_CARRIER)
			अवरोध;
		msleep(4);
	पूर्ण
	अगर (!(val & REG_STRENGTH_CARRIER))
		वापस;

	/* Wait क्रम lock */
	क्रम (n = 0;  n < 20;  n++) अणु
		val = lgs8gl5_पढ़ो_reg(state, REG_STATUS);
		dprपूर्णांकk("Wait for lock[%d] 0x%02X\n", n, val);
		अगर (val & REG_STATUS_LOCK)
			अवरोध;
		msleep(12);
	पूर्ण
	अगर (!(val & REG_STATUS_LOCK))
		वापस;

	lgs8gl5_ग_लिखो_reg(state, REG_7D, lgs8gl5_पढ़ो_reg(state, REG_A2));
	lgs8gl5_soft_reset(state);
पूर्ण


अटल पूर्णांक
lgs8gl5_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	lgs8gl5_update_alt_reg(state, 0xc2, 0x28);
	lgs8gl5_soft_reset(state);
	lgs8gl5_update_reg(state, REG_07, 0x10);
	lgs8gl5_update_reg(state, REG_07, 0x10);
	lgs8gl5_ग_लिखो_reg(state, REG_09, 0x0e);
	lgs8gl5_ग_लिखो_reg(state, REG_0A, 0xe5);
	lgs8gl5_ग_लिखो_reg(state, REG_0B, 0x35);
	lgs8gl5_ग_लिखो_reg(state, REG_0C, 0x30);

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;
	u8 level = lgs8gl5_पढ़ो_reg(state, REG_STRENGTH);
	u8 flags = lgs8gl5_पढ़ो_reg(state, REG_STATUS);

	*status = 0;

	अगर ((level & REG_STRENGTH_MASK) > 0)
		*status |= FE_HAS_SIGNAL;
	अगर (level & REG_STRENGTH_CARRIER)
		*status |= FE_HAS_CARRIER;
	अगर (flags & REG_STATUS_SYNC)
		*status |= FE_HAS_SYNC;
	अगर (flags & REG_STATUS_LOCK)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	*ber = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *संकेत_strength)
अणु
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;
	u8 level = lgs8gl5_पढ़ो_reg(state, REG_STRENGTH);
	*संकेत_strength = (level & REG_STRENGTH_MASK) << 8;

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;
	u8 level = lgs8gl5_पढ़ो_reg(state, REG_STRENGTH);
	*snr = (level & REG_STRENGTH_MASK) << 8;

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	*ucblocks = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (p->bandwidth_hz != 8000000)
		वापस -EINVAL;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* lgs8gl5_set_inversion(state, p->inversion); */

	lgs8gl5_start_demod(state);

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_get_frontend(काष्ठा dvb_frontend *fe,
		     काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;

	u8 inv = lgs8gl5_पढ़ो_reg(state, REG_INVERSION);

	p->inversion = (inv & REG_INVERSION_ON) ? INVERSION_ON : INVERSION_OFF;

	p->code_rate_HP = FEC_1_2;
	p->code_rate_LP = FEC_7_8;
	p->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
	p->transmission_mode = TRANSMISSION_MODE_2K;
	p->modulation = QAM_64;
	p->hierarchy = HIERARCHY_NONE;
	p->bandwidth_hz = 8000000;

	वापस 0;
पूर्ण


अटल पूर्णांक
lgs8gl5_get_tune_settings(काष्ठा dvb_frontend *fe,
		काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	fesettings->min_delay_ms = 240;
	fesettings->step_size    = 0;
	fesettings->max_drअगरt    = 0;
	वापस 0;
पूर्ण


अटल व्योम
lgs8gl5_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgs8gl5_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण


अटल स्थिर काष्ठा dvb_frontend_ops lgs8gl5_ops;


काष्ठा dvb_frontend*
lgs8gl5_attach(स्थिर काष्ठा lgs8gl5_config *config, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा lgs8gl5_state *state = शून्य;

	dprपूर्णांकk("%s\n", __func__);

	/* Allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा lgs8gl5_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* Setup the state */
	state->config = config;
	state->i2c    = i2c;

	/* Check अगर the demod is there */
	अगर (lgs8gl5_पढ़ो_reg(state, REG_RESET) < 0)
		जाओ error;

	/* Create dvb_frontend */
	स_नकल(&state->frontend.ops, &lgs8gl5_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(lgs8gl5_attach);


अटल स्थिर काष्ठा dvb_frontend_ops lgs8gl5_ops = अणु
	.delsys = अणु SYS_DTMB पूर्ण,
	.info = अणु
		.name			= "Legend Silicon LGS-8GL5 DMB-TH",
		.frequency_min_hz	= 474 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	=  10 * kHz,
		.caps = FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_32 |
			FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_BANDWIDTH_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_RECOVER
	पूर्ण,

	.release = lgs8gl5_release,

	.init = lgs8gl5_init,

	.set_frontend = lgs8gl5_set_frontend,
	.get_frontend = lgs8gl5_get_frontend,
	.get_tune_settings = lgs8gl5_get_tune_settings,

	.पढ़ो_status = lgs8gl5_पढ़ो_status,
	.पढ़ो_ber = lgs8gl5_पढ़ो_ber,
	.पढ़ो_संकेत_strength = lgs8gl5_पढ़ो_संकेत_strength,
	.पढ़ो_snr = lgs8gl5_पढ़ो_snr,
	.पढ़ो_ucblocks = lgs8gl5_पढ़ो_ucblocks,
पूर्ण;


module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Legend Silicon LGS-8GL5 DMB-TH Demodulator driver");
MODULE_AUTHOR("Timothy Lee");
MODULE_LICENSE("GPL");
