<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Conexant cx24120/cx24118 - DVBS/S2 Satellite demod/tuner driver

    Copyright (C) 2008 Patrick Boettcher <pb@linuxtv.org>
    Copyright (C) 2009 Sergey Tyurin <क्रमum.मुक्त-x.de>
    Updated 2012 by Jannis Achstetter <jannis_achstetter@web.de>
    Copyright (C) 2015 Jemma Denson <jdenson@gmail.com>
	April 2015
	    Refactored & simplअगरied driver
	    Updated to work with delivery प्रणाली supplied by DVBv5
	    Add frequency, fec & pilot to get_frontend

	Cards supported: Technisat Skystar S2

*/

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/firmware.h>
#समावेश <media/dvb_frontend.h>
#समावेश "cx24120.h"

#घोषणा CX24120_SEARCH_RANGE_KHZ 5000
#घोषणा CX24120_FIRMWARE "dvb-fe-cx24120-1.20.58.2.fw"

/* cx24120 i2c रेजिस्टरs  */
#घोषणा CX24120_REG_CMD_START	0x00		/* ग_लिखो cmd_id */
#घोषणा CX24120_REG_CMD_ARGS	0x01		/* ग_लिखो command arguments */
#घोषणा CX24120_REG_CMD_END	0x1f		/* ग_लिखो 0x01 क्रम end */

#घोषणा CX24120_REG_MAILBOX	0x33
#घोषणा CX24120_REG_FREQ3	0x34		/* frequency */
#घोषणा CX24120_REG_FREQ2	0x35
#घोषणा CX24120_REG_FREQ1	0x36

#घोषणा CX24120_REG_FECMODE	0x39		/* FEC status */
#घोषणा CX24120_REG_STATUS	0x3a		/* Tuner status */
#घोषणा CX24120_REG_SIGSTR_H	0x3a		/* Signal strength high */
#घोषणा CX24120_REG_SIGSTR_L	0x3b		/* Signal strength low byte */
#घोषणा CX24120_REG_QUALITY_H	0x40		/* SNR high byte */
#घोषणा CX24120_REG_QUALITY_L	0x41		/* SNR low byte */

#घोषणा CX24120_REG_BER_HH	0x47		/* BER high byte of high word */
#घोषणा CX24120_REG_BER_HL	0x48		/* BER low byte of high word */
#घोषणा CX24120_REG_BER_LH	0x49		/* BER high byte of low word */
#घोषणा CX24120_REG_BER_LL	0x4a		/* BER low byte of low word */

#घोषणा CX24120_REG_UCB_H	0x50		/* UCB high byte */
#घोषणा CX24120_REG_UCB_L	0x51		/* UCB low byte  */

#घोषणा CX24120_REG_CLKDIV	0xe6
#घोषणा CX24120_REG_RATEDIV	0xf0

#घोषणा CX24120_REG_REVISION	0xff		/* Chip revision (ro) */

/* Command messages */
क्रमागत command_message_id अणु
	CMD_VCO_SET		= 0x10,		/* cmd.len = 12; */
	CMD_TUNEREQUEST		= 0x11,		/* cmd.len = 15; */

	CMD_MPEG_ONOFF		= 0x13,		/* cmd.len = 4; */
	CMD_MPEG_INIT		= 0x14,		/* cmd.len = 7; */
	CMD_BANDWIDTH		= 0x15,		/* cmd.len = 12; */
	CMD_CLOCK_READ		= 0x16,		/* पढ़ो घड़ी */
	CMD_CLOCK_SET		= 0x17,		/* cmd.len = 10; */

	CMD_DISEQC_MSG1		= 0x20,		/* cmd.len = 11; */
	CMD_DISEQC_MSG2		= 0x21,		/* cmd.len = d->msg_len + 6; */
	CMD_SETVOLTAGE		= 0x22,		/* cmd.len = 2; */
	CMD_SETTONE		= 0x23,		/* cmd.len = 4; */
	CMD_DISEQC_BURST	= 0x24,		/* cmd.len not used !!! */

	CMD_READ_SNR		= 0x1a,		/* Read संकेत strength */
	CMD_START_TUNER		= 0x1b,		/* ??? */

	CMD_FWVERSION		= 0x35,

	CMD_BER_CTRL		= 0x3c,		/* cmd.len = 0x03; */
पूर्ण;

#घोषणा CX24120_MAX_CMD_LEN	30

/* pilot mask */
#घोषणा CX24120_PILOT_OFF	0x00
#घोषणा CX24120_PILOT_ON	0x40
#घोषणा CX24120_PILOT_AUTO	0x80

/* संकेत status */
#घोषणा CX24120_HAS_SIGNAL	0x01
#घोषणा CX24120_HAS_CARRIER	0x02
#घोषणा CX24120_HAS_VITERBI	0x04
#घोषणा CX24120_HAS_LOCK	0x08
#घोषणा CX24120_HAS_UNK1	0x10
#घोषणा CX24120_HAS_UNK2	0x20
#घोषणा CX24120_STATUS_MASK	0x0f
#घोषणा CX24120_SIGNAL_MASK	0xc0

/* ber winकरोw */
#घोषणा CX24120_BER_WINDOW	16
#घोषणा CX24120_BER_WSIZE	((1 << CX24120_BER_WINDOW) * 208 * 8)

#घोषणा info(args...) pr_info("cx24120: " args)
#घोषणा err(args...)  pr_err("cx24120: ### ERROR: " args)

/* The Demod/Tuner can't easily provide these, we cache them */
काष्ठा cx24120_tuning अणु
	u32 frequency;
	u32 symbol_rate;
	क्रमागत fe_spectral_inversion inversion;
	क्रमागत fe_code_rate fec;

	क्रमागत fe_delivery_प्रणाली delsys;
	क्रमागत fe_modulation modulation;
	क्रमागत fe_pilot pilot;

	/* Demod values */
	u8 fec_val;
	u8 fec_mask;
	u8 clkभाग;
	u8 rateभाग;
	u8 inversion_val;
	u8 pilot_val;
पूर्ण;

/* Private state */
काष्ठा cx24120_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा cx24120_config *config;
	काष्ठा dvb_frontend frontend;

	u8 cold_init;
	u8 mpeg_enabled;
	u8 need_घड़ी_set;

	/* current and next tuning parameters */
	काष्ठा cx24120_tuning dcur;
	काष्ठा cx24120_tuning dnxt;

	क्रमागत fe_status fe_status;

	/* dvbv5 stats calculations */
	u32 bitrate;
	u32 berw_usecs;
	u32 ber_prev;
	u32 ucb_offset;
	अचिन्हित दीर्घ ber_jअगरfies_stats;
	अचिन्हित दीर्घ per_jअगरfies_stats;
पूर्ण;

/* Command message to firmware */
काष्ठा cx24120_cmd अणु
	u8 id;
	u8 len;
	u8 arg[CX24120_MAX_CMD_LEN];
पूर्ण;

/* Read single रेजिस्टर */
अटल पूर्णांक cx24120_पढ़ोreg(काष्ठा cx24120_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 buf = 0;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->i2c_addr,
			.flags = 0,
			.len = 1,
			.buf = &reg
		पूर्ण, अणु
			.addr = state->config->i2c_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &buf
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);
	अगर (ret != 2) अणु
		err("Read error: reg=0x%02x, ret=%i)\n", reg, ret);
		वापस ret;
	पूर्ण

	dev_dbg(&state->i2c->dev, "reg=0x%02x; data=0x%02x\n", reg, buf);

	वापस buf;
पूर्ण

/* Write single रेजिस्टर */
अटल पूर्णांक cx24120_ग_लिखोreg(काष्ठा cx24120_state *state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->i2c_addr,
		.flags = 0,
		.buf = buf,
		.len = 2
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c, &msg, 1);
	अगर (ret != 1) अणु
		err("Write error: i2c_write error(err == %i, 0x%02x: 0x%02x)\n",
		    ret, reg, data);
		वापस ret;
	पूर्ण

	dev_dbg(&state->i2c->dev, "reg=0x%02x; data=0x%02x\n", reg, data);

	वापस 0;
पूर्ण

/* Write multiple रेजिस्टरs in chunks of i2c_wr_max-sized buffers */
अटल पूर्णांक cx24120_ग_लिखोregs(काष्ठा cx24120_state *state,
			     u8 reg, स्थिर u8 *values, u16 len, u8 incr)
अणु
	पूर्णांक ret;
	u16 max = state->config->i2c_wr_max > 0 ?
				state->config->i2c_wr_max :
				len;

	काष्ठा i2c_msg msg = अणु
		.addr = state->config->i2c_addr,
		.flags = 0,
	पूर्ण;

	msg.buf = kदो_स्मृति(max + 1, GFP_KERNEL);
	अगर (!msg.buf)
		वापस -ENOMEM;

	जबतक (len) अणु
		msg.buf[0] = reg;
		msg.len = len > max ? max : len;
		स_नकल(&msg.buf[1], values, msg.len);

		len    -= msg.len;      /* data length revers counter */
		values += msg.len;      /* incr data poपूर्णांकer */

		अगर (incr)
			reg += msg.len;
		msg.len++;              /* करोn't क्रमget the addr byte */

		ret = i2c_transfer(state->i2c, &msg, 1);
		अगर (ret != 1) अणु
			err("i2c_write error(err == %i, 0x%02x)\n", ret, reg);
			जाओ out;
		पूर्ण

		dev_dbg(&state->i2c->dev, "reg=0x%02x; data=%*ph\n",
			reg, msg.len - 1, msg.buf + 1);
	पूर्ण

	ret = 0;

out:
	kमुक्त(msg.buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24120_ops;

काष्ठा dvb_frontend *cx24120_attach(स्थिर काष्ठा cx24120_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा cx24120_state *state;
	पूर्णांक demod_rev;

	info("Conexant cx24120/cx24118 - DVBS/S2 Satellite demod/tuner\n");
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state) अणु
		err("Unable to allocate memory for cx24120_state\n");
		जाओ error;
	पूर्ण

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is present and has proper type */
	demod_rev = cx24120_पढ़ोreg(state, CX24120_REG_REVISION);
	चयन (demod_rev) अणु
	हाल 0x07:
		info("Demod cx24120 rev. 0x07 detected.\n");
		अवरोध;
	हाल 0x05:
		info("Demod cx24120 rev. 0x05 detected.\n");
		अवरोध;
	शेष:
		err("Unsupported demod revision: 0x%x detected.\n", demod_rev);
		जाओ error;
	पूर्ण

	/* create dvb_frontend */
	state->cold_init = 0;
	स_नकल(&state->frontend.ops, &cx24120_ops,
	       माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	info("Conexant cx24120/cx24118 attached.\n");
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(cx24120_attach);

अटल पूर्णांक cx24120_test_rom(काष्ठा cx24120_state *state)
अणु
	पूर्णांक err, ret;

	err = cx24120_पढ़ोreg(state, 0xfd);
	अगर (err & 4) अणु
		ret = cx24120_पढ़ोreg(state, 0xdf) & 0xfe;
		err = cx24120_ग_लिखोreg(state, 0xdf, ret);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cx24120_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->cnr.stat[0].scale != FE_SCALE_DECIBEL)
		*snr = 0;
	अन्यथा
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->post_bit_error.stat[0].scale != FE_SCALE_COUNTER) अणु
		*ber = 0;
		वापस 0;
	पूर्ण

	*ber = c->post_bit_error.stat[0].uvalue - state->ber_prev;
	state->ber_prev = c->post_bit_error.stat[0].uvalue;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_msg_mpeg_output_global_config(काष्ठा cx24120_state *state,
						 u8 flag);

/* Check अगर we're running a command that needs to disable mpeg out */
अटल व्योम cx24120_check_cmd(काष्ठा cx24120_state *state, u8 id)
अणु
	चयन (id) अणु
	हाल CMD_TUNEREQUEST:
	हाल CMD_CLOCK_READ:
	हाल CMD_DISEQC_MSG1:
	हाल CMD_DISEQC_MSG2:
	हाल CMD_SETVOLTAGE:
	हाल CMD_SETTONE:
	हाल CMD_DISEQC_BURST:
		cx24120_msg_mpeg_output_global_config(state, 0);
		/* Old driver would करो a msleep(100) here */
		वापस;
	शेष:
		वापस;
	पूर्ण
पूर्ण

/* Send a message to the firmware */
अटल पूर्णांक cx24120_message_send(काष्ठा cx24120_state *state,
				काष्ठा cx24120_cmd *cmd)
अणु
	पूर्णांक ficus;

	अगर (state->mpeg_enabled) अणु
		/* Disable mpeg out on certain commands */
		cx24120_check_cmd(state, cmd->id);
	पूर्ण

	cx24120_ग_लिखोreg(state, CX24120_REG_CMD_START, cmd->id);
	cx24120_ग_लिखोregs(state, CX24120_REG_CMD_ARGS, &cmd->arg[0],
			  cmd->len, 1);
	cx24120_ग_लिखोreg(state, CX24120_REG_CMD_END, 0x01);

	ficus = 1000;
	जबतक (cx24120_पढ़ोreg(state, CX24120_REG_CMD_END)) अणु
		msleep(20);
		ficus -= 20;
		अगर (ficus == 0) अणु
			err("Error sending message to firmware\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	dev_dbg(&state->i2c->dev, "sent message 0x%02x\n", cmd->id);

	वापस 0;
पूर्ण

/* Send a message and fill arg[] with the results */
अटल पूर्णांक cx24120_message_sendrcv(काष्ठा cx24120_state *state,
				   काष्ठा cx24120_cmd *cmd, u8 numreg)
अणु
	पूर्णांक ret, i;

	अगर (numreg > CX24120_MAX_CMD_LEN) अणु
		err("Too many registers to read. cmd->reg = %d", numreg);
		वापस -EREMOTEIO;
	पूर्ण

	ret = cx24120_message_send(state, cmd);
	अगर (ret != 0)
		वापस ret;

	अगर (!numreg)
		वापस 0;

	/* Read numreg रेजिस्टरs starting from रेजिस्टर cmd->len */
	क्रम (i = 0; i < numreg; i++)
		cmd->arg[i] = cx24120_पढ़ोreg(state, (cmd->len + i + 1));

	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					u16 *संकेत_strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->strength.stat[0].scale != FE_SCALE_RELATIVE)
		*संकेत_strength = 0;
	अन्यथा
		*संकेत_strength = c->strength.stat[0].uvalue;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_msg_mpeg_output_global_config(काष्ठा cx24120_state *state,
						 u8 enable)
अणु
	काष्ठा cx24120_cmd cmd;
	पूर्णांक ret;

	cmd.id = CMD_MPEG_ONOFF;
	cmd.len = 4;
	cmd.arg[0] = 0x01;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = enable ? 0 : (u8)(-1);
	cmd.arg[3] = 0x01;

	ret = cx24120_message_send(state, &cmd);
	अगर (ret != 0) अणु
		dev_dbg(&state->i2c->dev, "failed to %s MPEG output\n",
			enable ? "enable" : "disable");
		वापस ret;
	पूर्ण

	state->mpeg_enabled = enable;
	dev_dbg(&state->i2c->dev, "MPEG output %s\n",
		enable ? "enabled" : "disabled");

	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_msg_mpeg_output_config(काष्ठा cx24120_state *state, u8 seq)
अणु
	काष्ठा cx24120_cmd cmd;
	काष्ठा cx24120_initial_mpeg_config i =
			state->config->initial_mpeg_config;

	cmd.id = CMD_MPEG_INIT;
	cmd.len = 7;
	cmd.arg[0] = seq; /* sequental number - can be 0,1,2 */
	cmd.arg[1] = ((i.x1 & 0x01) << 1) | ((i.x1 >> 1) & 0x01);
	cmd.arg[2] = 0x05;
	cmd.arg[3] = 0x02;
	cmd.arg[4] = ((i.x2 >> 1) & 0x01);
	cmd.arg[5] = (i.x2 & 0xf0) | (i.x3 & 0x0f);
	cmd.arg[6] = 0x10;

	वापस cx24120_message_send(state, &cmd);
पूर्ण

अटल पूर्णांक cx24120_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "\n");

	/*
	 * Yes, cmd.len is set to zero. The old driver
	 * didn't specअगरy any len, but also had a
	 * स_रखो 0 beक्रमe every use of the cmd काष्ठा
	 * which would have set it to zero.
	 * This quite probably needs looking पूर्णांकo.
	 */
	cmd.id = CMD_DISEQC_BURST;
	cmd.len = 0;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = (burst == SEC_MINI_B) ? 0x01 : 0x00;

	वापस cx24120_message_send(state, &cmd);
पूर्ण

अटल पूर्णांक cx24120_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "(%d)\n", tone);

	अगर ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) अणु
		err("Invalid tone=%d\n", tone);
		वापस -EINVAL;
	पूर्ण

	cmd.id = CMD_SETTONE;
	cmd.len = 4;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x00;
	cmd.arg[3] = (tone == SEC_TONE_ON) ? 0x01 : 0x00;

	वापस cx24120_message_send(state, &cmd);
पूर्ण

अटल पूर्णांक cx24120_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "(%d)\n", voltage);

	cmd.id = CMD_SETVOLTAGE;
	cmd.len = 2;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = (voltage == SEC_VOLTAGE_18) ? 0x01 : 0x00;

	वापस cx24120_message_send(state, &cmd);
पूर्ण

अटल पूर्णांक cx24120_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				   काष्ठा dvb_diseqc_master_cmd *d)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;
	पूर्णांक back_count;

	dev_dbg(&state->i2c->dev, "\n");

	cmd.id = CMD_DISEQC_MSG1;
	cmd.len = 11;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x03;
	cmd.arg[3] = 0x16;
	cmd.arg[4] = 0x28;
	cmd.arg[5] = 0x01;
	cmd.arg[6] = 0x01;
	cmd.arg[7] = 0x14;
	cmd.arg[8] = 0x19;
	cmd.arg[9] = 0x14;
	cmd.arg[10] = 0x1e;

	अगर (cx24120_message_send(state, &cmd)) अणु
		err("send 1st message(0x%x) failed\n", cmd.id);
		वापस -EREMOTEIO;
	पूर्ण

	cmd.id = CMD_DISEQC_MSG2;
	cmd.len = d->msg_len + 6;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x01;
	cmd.arg[2] = 0x02;
	cmd.arg[3] = 0x00;
	cmd.arg[4] = 0x00;
	cmd.arg[5] = d->msg_len;

	स_नकल(&cmd.arg[6], &d->msg, d->msg_len);

	अगर (cx24120_message_send(state, &cmd)) अणु
		err("send 2nd message(0x%x) failed\n", cmd.id);
		वापस -EREMOTEIO;
	पूर्ण

	back_count = 500;
	करो अणु
		अगर (!(cx24120_पढ़ोreg(state, 0x93) & 0x01)) अणु
			dev_dbg(&state->i2c->dev, "diseqc sequence sent\n");
			वापस 0;
		पूर्ण
		msleep(20);
		back_count -= 20;
	पूर्ण जबतक (back_count);

	err("Too long waiting for diseqc.\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम cx24120_get_stats(काष्ठा cx24120_state *state)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24120_cmd cmd;
	पूर्णांक ret, cnr, msecs;
	u16 sig, ucb;
	u32 ber;

	dev_dbg(&state->i2c->dev, "\n");

	/* संकेत strength */
	अगर (state->fe_status & FE_HAS_SIGNAL) अणु
		cmd.id = CMD_READ_SNR;
		cmd.len = 1;
		cmd.arg[0] = 0x00;

		ret = cx24120_message_send(state, &cmd);
		अगर (ret != 0) अणु
			err("error reading signal strength\n");
			वापस;
		पूर्ण

		/* raw */
		sig = cx24120_पढ़ोreg(state, CX24120_REG_SIGSTR_H) >> 6;
		sig = sig << 8;
		sig |= cx24120_पढ़ोreg(state, CX24120_REG_SIGSTR_L);
		dev_dbg(&state->i2c->dev,
			"signal strength from firmware = 0x%x\n", sig);

		/* cooked */
		sig = -100 * sig + 94324;

		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = sig;
	पूर्ण अन्यथा अणु
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (state->fe_status & FE_HAS_VITERBI) अणु
		cnr = cx24120_पढ़ोreg(state, CX24120_REG_QUALITY_H) << 8;
		cnr |= cx24120_पढ़ोreg(state, CX24120_REG_QUALITY_L);
		dev_dbg(&state->i2c->dev, "read SNR index = %d\n", cnr);

		/* guessed - seems about right */
		cnr = cnr * 100;

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = cnr;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* BER & UCB require lock */
	अगर (!(state->fe_status & FE_HAS_LOCK)) अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	/* BER */
	अगर (समय_after(jअगरfies, state->ber_jअगरfies_stats)) अणु
		msecs = (state->berw_usecs + 500) / 1000;
		state->ber_jअगरfies_stats = jअगरfies + msecs_to_jअगरfies(msecs);

		ber = cx24120_पढ़ोreg(state, CX24120_REG_BER_HH) << 24;
		ber |= cx24120_पढ़ोreg(state, CX24120_REG_BER_HL) << 16;
		ber |= cx24120_पढ़ोreg(state, CX24120_REG_BER_LH) << 8;
		ber |= cx24120_पढ़ोreg(state, CX24120_REG_BER_LL);
		dev_dbg(&state->i2c->dev, "read BER index = %d\n", ber);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += ber;

		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += CX24120_BER_WSIZE;
	पूर्ण

	/* UCB */
	अगर (समय_after(jअगरfies, state->per_jअगरfies_stats)) अणु
		state->per_jअगरfies_stats = jअगरfies + msecs_to_jअगरfies(1000);

		ucb = cx24120_पढ़ोreg(state, CX24120_REG_UCB_H) << 8;
		ucb |= cx24120_पढ़ोreg(state, CX24120_REG_UCB_L);
		dev_dbg(&state->i2c->dev, "ucblocks = %d\n", ucb);

		/* handle reset */
		अगर (ucb < state->ucb_offset)
			state->ucb_offset = c->block_error.stat[0].uvalue;

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue = ucb + state->ucb_offset;

		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue += state->bitrate / 8 / 208;
	पूर्ण
पूर्ण

अटल व्योम cx24120_set_घड़ी_ratios(काष्ठा dvb_frontend *fe);

/* Read current tuning status */
अटल पूर्णांक cx24120_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	पूर्णांक lock;

	lock = cx24120_पढ़ोreg(state, CX24120_REG_STATUS);

	dev_dbg(&state->i2c->dev, "status = 0x%02x\n", lock);

	*status = 0;

	अगर (lock & CX24120_HAS_SIGNAL)
		*status = FE_HAS_SIGNAL;
	अगर (lock & CX24120_HAS_CARRIER)
		*status |= FE_HAS_CARRIER;
	अगर (lock & CX24120_HAS_VITERBI)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
	अगर (lock & CX24120_HAS_LOCK)
		*status |= FE_HAS_LOCK;

	/*
	 * TODO: is FE_HAS_SYNC in the right place?
	 * Other cx241xx drivers have this slightly
	 * dअगरferent
	 */

	state->fe_status = *status;
	cx24120_get_stats(state);

	/* Set the घड़ी once tuned in */
	अगर (state->need_घड़ी_set && *status & FE_HAS_LOCK) अणु
		/* Set घड़ी ratios */
		cx24120_set_घड़ी_ratios(fe);

		/* Old driver would करो a msleep(200) here */

		/* Renable mpeg output */
		अगर (!state->mpeg_enabled)
			cx24120_msg_mpeg_output_global_config(state, 1);

		state->need_घड़ी_set = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * FEC & modulation lookup table
 * Used क्रम decoding the REG_FECMODE रेजिस्टर
 * once tuned in.
 */
काष्ठा cx24120_modfec अणु
	क्रमागत fe_delivery_प्रणाली delsys;
	क्रमागत fe_modulation mod;
	क्रमागत fe_code_rate fec;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा cx24120_modfec modfec_lookup_table[] = अणु
	/*delsys     mod    fec       val */
	अणु SYS_DVBS,  QPSK,  FEC_1_2,  0x01 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_2_3,  0x02 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_3_4,  0x03 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_4_5,  0x04 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_5_6,  0x05 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_6_7,  0x06 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_7_8,  0x07 पूर्ण,

	अणु SYS_DVBS2, QPSK,  FEC_1_2,  0x04 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_3_5,  0x05 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_2_3,  0x06 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_3_4,  0x07 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_4_5,  0x08 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_5_6,  0x09 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_8_9,  0x0a पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_9_10, 0x0b पूर्ण,

	अणु SYS_DVBS2, PSK_8, FEC_3_5,  0x0c पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_2_3,  0x0d पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_3_4,  0x0e पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_5_6,  0x0f पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_8_9,  0x10 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_9_10, 0x11 पूर्ण,
पूर्ण;

/* Retrieve current fec, modulation & pilot values */
अटल पूर्णांक cx24120_get_fec(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	पूर्णांक idx;
	पूर्णांक ret;
	पूर्णांक fec;

	ret = cx24120_पढ़ोreg(state, CX24120_REG_FECMODE);
	fec = ret & 0x3f; /* Lower 6 bits */

	dev_dbg(&state->i2c->dev, "raw fec = %d\n", fec);

	क्रम (idx = 0; idx < ARRAY_SIZE(modfec_lookup_table); idx++) अणु
		अगर (modfec_lookup_table[idx].delsys != state->dcur.delsys)
			जारी;
		अगर (modfec_lookup_table[idx].val != fec)
			जारी;

		अवरोध; /* found */
	पूर्ण

	अगर (idx >= ARRAY_SIZE(modfec_lookup_table)) अणु
		dev_dbg(&state->i2c->dev, "couldn't find fec!\n");
		वापस -EINVAL;
	पूर्ण

	/* save values back to cache */
	c->modulation = modfec_lookup_table[idx].mod;
	c->fec_inner = modfec_lookup_table[idx].fec;
	c->pilot = (ret & 0x80) ? PILOT_ON : PILOT_OFF;

	dev_dbg(&state->i2c->dev, "mod(%d), fec(%d), pilot(%d)\n",
		c->modulation, c->fec_inner, c->pilot);

	वापस 0;
पूर्ण

/* Calculate ber winकरोw समय */
अटल व्योम cx24120_calculate_ber_winकरोw(काष्ठा cx24120_state *state, u32 rate)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u64 पंचांगp;

	/*
	 * Calculate bitrate from rate in the घड़ी ratios table.
	 * This isn't *exactly* right but बंद enough.
	 */
	पंचांगp = (u64)c->symbol_rate * rate;
	करो_भाग(पंचांगp, 256);
	state->bitrate = पंचांगp;

	/* usecs per ber winकरोw */
	पंचांगp = 1000000ULL * CX24120_BER_WSIZE;
	करो_भाग(पंचांगp, state->bitrate);
	state->berw_usecs = पंचांगp;

	dev_dbg(&state->i2c->dev, "bitrate: %u, berw_usecs: %u\n",
		state->bitrate, state->berw_usecs);
पूर्ण

/*
 * Clock ratios lookup table
 *
 * Values obtained from much larger table in old driver
 * which had numerous entries which would never match.
 *
 * There's probably some way of calculating these but I
 * can't determine the pattern
 */
काष्ठा cx24120_घड़ी_ratios_table अणु
	क्रमागत fe_delivery_प्रणाली delsys;
	क्रमागत fe_pilot pilot;
	क्रमागत fe_modulation mod;
	क्रमागत fe_code_rate fec;
	u32 m_rat;
	u32 n_rat;
	u32 rate;
पूर्ण;

अटल स्थिर काष्ठा cx24120_घड़ी_ratios_table घड़ी_ratios_table[] = अणु
	/*delsys     pilot      mod    fec       m_rat    n_rat   rate */
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_1_2,  273088,  254505, 274 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_3_5,  17272,   13395,  330 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_2_3,  24344,   16967,  367 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_3_4,  410788,  254505, 413 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_4_5,  438328,  254505, 440 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_5_6,  30464,   16967,  459 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_8_9,  487832,  254505, 490 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, QPSK,  FEC_9_10, 493952,  254505, 496 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, PSK_8, FEC_3_5,  328168,  169905, 494 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, PSK_8, FEC_2_3,  24344,   11327,  550 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, PSK_8, FEC_3_4,  410788,  169905, 618 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, PSK_8, FEC_5_6,  30464,   11327,  688 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, PSK_8, FEC_8_9,  487832,  169905, 735 पूर्ण,
	अणु SYS_DVBS2, PILOT_OFF, PSK_8, FEC_9_10, 493952,  169905, 744 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_1_2,  273088,  260709, 268 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_3_5,  328168,  260709, 322 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_2_3,  121720,  86903,  358 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_3_4,  410788,  260709, 403 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_4_5,  438328,  260709, 430 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_5_6,  152320,  86903,  448 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_8_9,  487832,  260709, 479 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  QPSK,  FEC_9_10, 493952,  260709, 485 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  PSK_8, FEC_3_5,  328168,  173853, 483 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  PSK_8, FEC_2_3,  121720,  57951,  537 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  PSK_8, FEC_3_4,  410788,  173853, 604 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  PSK_8, FEC_5_6,  152320,  57951,  672 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  PSK_8, FEC_8_9,  487832,  173853, 718 पूर्ण,
	अणु SYS_DVBS2, PILOT_ON,  PSK_8, FEC_9_10, 493952,  173853, 727 पूर्ण,
	अणु SYS_DVBS,  PILOT_OFF, QPSK,  FEC_1_2,  152592,  152592, 256 पूर्ण,
	अणु SYS_DVBS,  PILOT_OFF, QPSK,  FEC_2_3,  305184,  228888, 341 पूर्ण,
	अणु SYS_DVBS,  PILOT_OFF, QPSK,  FEC_3_4,  457776,  305184, 384 पूर्ण,
	अणु SYS_DVBS,  PILOT_OFF, QPSK,  FEC_5_6,  762960,  457776, 427 पूर्ण,
	अणु SYS_DVBS,  PILOT_OFF, QPSK,  FEC_7_8,  1068144, 610368, 448 पूर्ण,
पूर्ण;

/* Set घड़ी ratio from lookup table */
अटल व्योम cx24120_set_घड़ी_ratios(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;
	पूर्णांक ret, idx;

	/* Find fec, modulation, pilot */
	ret = cx24120_get_fec(fe);
	अगर (ret != 0)
		वापस;

	/* Find the घड़ी ratios in the lookup table */
	क्रम (idx = 0; idx < ARRAY_SIZE(घड़ी_ratios_table); idx++) अणु
		अगर (घड़ी_ratios_table[idx].delsys != state->dcur.delsys)
			जारी;
		अगर (घड़ी_ratios_table[idx].mod != c->modulation)
			जारी;
		अगर (घड़ी_ratios_table[idx].fec != c->fec_inner)
			जारी;
		अगर (घड़ी_ratios_table[idx].pilot != c->pilot)
			जारी;

		अवरोध;		/* found */
	पूर्ण

	अगर (idx >= ARRAY_SIZE(घड़ी_ratios_table)) अणु
		info("Clock ratio not found - data reception in danger\n");
		वापस;
	पूर्ण

	/* Read current values? */
	cmd.id = CMD_CLOCK_READ;
	cmd.len = 1;
	cmd.arg[0] = 0x00;
	ret = cx24120_message_sendrcv(state, &cmd, 6);
	अगर (ret != 0)
		वापस;
	/* in cmd[0]-[5] - result */

	dev_dbg(&state->i2c->dev, "m=%d, n=%d; idx: %d m=%d, n=%d, rate=%d\n",
		cmd.arg[2] | (cmd.arg[1] << 8) | (cmd.arg[0] << 16),
		cmd.arg[5] | (cmd.arg[4] << 8) | (cmd.arg[3] << 16),
		idx,
		घड़ी_ratios_table[idx].m_rat,
		घड़ी_ratios_table[idx].n_rat,
		घड़ी_ratios_table[idx].rate);

	/* Set the घड़ी */
	cmd.id = CMD_CLOCK_SET;
	cmd.len = 10;
	cmd.arg[0] = 0;
	cmd.arg[1] = 0x10;
	cmd.arg[2] = (घड़ी_ratios_table[idx].m_rat >> 16) & 0xff;
	cmd.arg[3] = (घड़ी_ratios_table[idx].m_rat >>  8) & 0xff;
	cmd.arg[4] = (घड़ी_ratios_table[idx].m_rat >>  0) & 0xff;
	cmd.arg[5] = (घड़ी_ratios_table[idx].n_rat >> 16) & 0xff;
	cmd.arg[6] = (घड़ी_ratios_table[idx].n_rat >>  8) & 0xff;
	cmd.arg[7] = (घड़ी_ratios_table[idx].n_rat >>  0) & 0xff;
	cmd.arg[8] = (घड़ी_ratios_table[idx].rate >> 8) & 0xff;
	cmd.arg[9] = (घड़ी_ratios_table[idx].rate >> 0) & 0xff;

	cx24120_message_send(state, &cmd);

	/* Calculate ber winकरोw rates क्रम stat work */
	cx24120_calculate_ber_winकरोw(state, घड़ी_ratios_table[idx].rate);
पूर्ण

/* Set inversion value */
अटल पूर्णांक cx24120_set_inversion(काष्ठा cx24120_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
	dev_dbg(&state->i2c->dev, "(%d)\n", inversion);

	चयन (inversion) अणु
	हाल INVERSION_OFF:
		state->dnxt.inversion_val = 0x00;
		अवरोध;
	हाल INVERSION_ON:
		state->dnxt.inversion_val = 0x04;
		अवरोध;
	हाल INVERSION_AUTO:
		state->dnxt.inversion_val = 0x0c;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	state->dnxt.inversion = inversion;

	वापस 0;
पूर्ण

/* FEC lookup table क्रम tuning */
काष्ठा cx24120_modfec_table अणु
	क्रमागत fe_delivery_प्रणाली delsys;
	क्रमागत fe_modulation mod;
	क्रमागत fe_code_rate fec;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा cx24120_modfec_table modfec_table[] = अणु
	/*delsys     mod    fec       val */
	अणु SYS_DVBS,  QPSK,  FEC_1_2,  0x2e पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_2_3,  0x2f पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_3_4,  0x30 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_5_6,  0x31 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_6_7,  0x32 पूर्ण,
	अणु SYS_DVBS,  QPSK,  FEC_7_8,  0x33 पूर्ण,

	अणु SYS_DVBS2, QPSK,  FEC_1_2,  0x04 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_3_5,  0x05 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_2_3,  0x06 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_3_4,  0x07 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_4_5,  0x08 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_5_6,  0x09 पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_8_9,  0x0a पूर्ण,
	अणु SYS_DVBS2, QPSK,  FEC_9_10, 0x0b पूर्ण,

	अणु SYS_DVBS2, PSK_8, FEC_3_5,  0x0c पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_2_3,  0x0d पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_3_4,  0x0e पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_5_6,  0x0f पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_8_9,  0x10 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_9_10, 0x11 पूर्ण,
पूर्ण;

/* Set fec_val & fec_mask values from delsys, modulation & fec */
अटल पूर्णांक cx24120_set_fec(काष्ठा cx24120_state *state, क्रमागत fe_modulation mod,
			   क्रमागत fe_code_rate fec)
अणु
	पूर्णांक idx;

	dev_dbg(&state->i2c->dev, "(0x%02x,0x%02x)\n", mod, fec);

	state->dnxt.fec = fec;

	/* Lookup fec_val from modfec table */
	क्रम (idx = 0; idx < ARRAY_SIZE(modfec_table); idx++) अणु
		अगर (modfec_table[idx].delsys != state->dnxt.delsys)
			जारी;
		अगर (modfec_table[idx].mod != mod)
			जारी;
		अगर (modfec_table[idx].fec != fec)
			जारी;

		/* found */
		state->dnxt.fec_mask = 0x00;
		state->dnxt.fec_val = modfec_table[idx].val;
		वापस 0;
	पूर्ण

	अगर (state->dnxt.delsys == SYS_DVBS2) अणु
		/* DVBS2 स्वतः is 0x00/0x00 */
		state->dnxt.fec_mask = 0x00;
		state->dnxt.fec_val  = 0x00;
	पूर्ण अन्यथा अणु
		/* Set DVB-S to स्वतः */
		state->dnxt.fec_val  = 0x2e;
		state->dnxt.fec_mask = 0xac;
	पूर्ण

	वापस 0;
पूर्ण

/* Set pilot */
अटल पूर्णांक cx24120_set_pilot(काष्ठा cx24120_state *state, क्रमागत fe_pilot pilot)
अणु
	dev_dbg(&state->i2c->dev, "(%d)\n", pilot);

	/* Pilot only valid in DVBS2 */
	अगर (state->dnxt.delsys != SYS_DVBS2) अणु
		state->dnxt.pilot_val = CX24120_PILOT_OFF;
		वापस 0;
	पूर्ण

	चयन (pilot) अणु
	हाल PILOT_OFF:
		state->dnxt.pilot_val = CX24120_PILOT_OFF;
		अवरोध;
	हाल PILOT_ON:
		state->dnxt.pilot_val = CX24120_PILOT_ON;
		अवरोध;
	हाल PILOT_AUTO:
	शेष:
		state->dnxt.pilot_val = CX24120_PILOT_AUTO;
	पूर्ण

	वापस 0;
पूर्ण

/* Set symbol rate */
अटल पूर्णांक cx24120_set_symbolrate(काष्ठा cx24120_state *state, u32 rate)
अणु
	dev_dbg(&state->i2c->dev, "(%d)\n", rate);

	state->dnxt.symbol_rate = rate;

	/* Check symbol rate */
	अगर (rate  > 31000000) अणु
		state->dnxt.clkभाग  = (-(rate < 31000001) & 3) + 2;
		state->dnxt.rateभाग = (-(rate < 31000001) & 6) + 4;
	पूर्ण अन्यथा अणु
		state->dnxt.clkभाग  = 3;
		state->dnxt.rateभाग = 6;
	पूर्ण

	वापस 0;
पूर्ण

/* Overग_लिखो the current tuning params, we are about to tune */
अटल व्योम cx24120_clone_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;

	state->dcur = state->dnxt;
पूर्ण

अटल पूर्णांक cx24120_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;
	पूर्णांक ret;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS2:
		dev_dbg(&state->i2c->dev, "DVB-S2\n");
		अवरोध;
	हाल SYS_DVBS:
		dev_dbg(&state->i2c->dev, "DVB-S\n");
		अवरोध;
	शेष:
		dev_dbg(&state->i2c->dev,
			"delivery system(%d) not supported\n",
			c->delivery_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	state->dnxt.delsys = c->delivery_प्रणाली;
	state->dnxt.modulation = c->modulation;
	state->dnxt.frequency = c->frequency;
	state->dnxt.pilot = c->pilot;

	ret = cx24120_set_inversion(state, c->inversion);
	अगर (ret !=  0)
		वापस ret;

	ret = cx24120_set_fec(state, c->modulation, c->fec_inner);
	अगर (ret !=  0)
		वापस ret;

	ret = cx24120_set_pilot(state, c->pilot);
	अगर (ret != 0)
		वापस ret;

	ret = cx24120_set_symbolrate(state, c->symbol_rate);
	अगर (ret !=  0)
		वापस ret;

	/* discard the 'current' tuning parameters and prepare to tune */
	cx24120_clone_params(fe);

	dev_dbg(&state->i2c->dev,
		"delsys      = %d\n", state->dcur.delsys);
	dev_dbg(&state->i2c->dev,
		"modulation  = %d\n", state->dcur.modulation);
	dev_dbg(&state->i2c->dev,
		"frequency   = %d\n", state->dcur.frequency);
	dev_dbg(&state->i2c->dev,
		"pilot       = %d (val = 0x%02x)\n",
		state->dcur.pilot, state->dcur.pilot_val);
	dev_dbg(&state->i2c->dev,
		"symbol_rate = %d (clkdiv/ratediv = 0x%02x/0x%02x)\n",
		 state->dcur.symbol_rate,
		 state->dcur.clkभाग, state->dcur.rateभाग);
	dev_dbg(&state->i2c->dev,
		"FEC         = %d (mask/val = 0x%02x/0x%02x)\n",
		state->dcur.fec, state->dcur.fec_mask, state->dcur.fec_val);
	dev_dbg(&state->i2c->dev,
		"Inversion   = %d (val = 0x%02x)\n",
		state->dcur.inversion, state->dcur.inversion_val);

	/* Flag that घड़ी needs to be set after tune */
	state->need_घड़ी_set = 1;

	/* Tune in */
	cmd.id = CMD_TUNEREQUEST;
	cmd.len = 15;
	cmd.arg[0] = 0;
	cmd.arg[1]  = (state->dcur.frequency & 0xff0000) >> 16;
	cmd.arg[2]  = (state->dcur.frequency & 0x00ff00) >> 8;
	cmd.arg[3]  = (state->dcur.frequency & 0x0000ff);
	cmd.arg[4]  = ((state->dcur.symbol_rate / 1000) & 0xff00) >> 8;
	cmd.arg[5]  = ((state->dcur.symbol_rate / 1000) & 0x00ff);
	cmd.arg[6]  = state->dcur.inversion;
	cmd.arg[7]  = state->dcur.fec_val | state->dcur.pilot_val;
	cmd.arg[8]  = CX24120_SEARCH_RANGE_KHZ >> 8;
	cmd.arg[9]  = CX24120_SEARCH_RANGE_KHZ & 0xff;
	cmd.arg[10] = 0;		/* maybe rolloff? */
	cmd.arg[11] = state->dcur.fec_mask;
	cmd.arg[12] = state->dcur.rateभाग;
	cmd.arg[13] = state->dcur.clkभाग;
	cmd.arg[14] = 0;

	/* Send tune command */
	ret = cx24120_message_send(state, &cmd);
	अगर (ret != 0)
		वापस ret;

	/* Write symbol rate values */
	ret = cx24120_ग_लिखोreg(state, CX24120_REG_CLKDIV, state->dcur.clkभाग);
	ret = cx24120_पढ़ोreg(state, CX24120_REG_RATEDIV);
	ret &= 0xfffffff0;
	ret |= state->dcur.rateभाग;
	ret = cx24120_ग_लिखोreg(state, CX24120_REG_RATEDIV, ret);

	वापस 0;
पूर्ण

/* Set vco from config */
अटल पूर्णांक cx24120_set_vco(काष्ठा cx24120_state *state)
अणु
	काष्ठा cx24120_cmd cmd;
	u32 nxtal_khz, vco;
	u64 inv_vco;
	u32 xtal_khz = state->config->xtal_khz;

	nxtal_khz = xtal_khz * 4;
	vco = nxtal_khz * 10;
	inv_vco = DIV_ROUND_CLOSEST_ULL(0x400000000ULL, vco);

	dev_dbg(&state->i2c->dev, "xtal=%d, vco=%d, inv_vco=%lld\n",
		xtal_khz, vco, inv_vco);

	cmd.id = CMD_VCO_SET;
	cmd.len = 12;
	cmd.arg[0] = (vco >> 16) & 0xff;
	cmd.arg[1] = (vco >> 8) & 0xff;
	cmd.arg[2] = vco & 0xff;
	cmd.arg[3] = (inv_vco >> 8) & 0xff;
	cmd.arg[4] = (inv_vco) & 0xff;
	cmd.arg[5] = 0x03;
	cmd.arg[6] = (nxtal_khz >> 8) & 0xff;
	cmd.arg[7] = nxtal_khz & 0xff;
	cmd.arg[8] = 0x06;
	cmd.arg[9] = 0x03;
	cmd.arg[10] = (xtal_khz >> 16) & 0xff;
	cmd.arg[11] = xtal_khz & 0xff;

	वापस cx24120_message_send(state, &cmd);
पूर्ण

अटल पूर्णांक cx24120_init(काष्ठा dvb_frontend *fe)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा cx24120_cmd cmd;
	u8 reg;
	पूर्णांक ret, i;
	अचिन्हित अक्षर vers[4];

	अगर (state->cold_init)
		वापस 0;

	/* ???? */
	cx24120_ग_लिखोreg(state, 0xea, 0x00);
	cx24120_test_rom(state);
	reg = cx24120_पढ़ोreg(state, 0xfb) & 0xfe;
	cx24120_ग_लिखोreg(state, 0xfb, reg);
	reg = cx24120_पढ़ोreg(state, 0xfc) & 0xfe;
	cx24120_ग_लिखोreg(state, 0xfc, reg);
	cx24120_ग_लिखोreg(state, 0xc3, 0x04);
	cx24120_ग_लिखोreg(state, 0xc4, 0x04);
	cx24120_ग_लिखोreg(state, 0xce, 0x00);
	cx24120_ग_लिखोreg(state, 0xcf, 0x00);
	reg = cx24120_पढ़ोreg(state, 0xea) & 0xfe;
	cx24120_ग_लिखोreg(state, 0xea, reg);
	cx24120_ग_लिखोreg(state, 0xeb, 0x0c);
	cx24120_ग_लिखोreg(state, 0xec, 0x06);
	cx24120_ग_लिखोreg(state, 0xed, 0x05);
	cx24120_ग_लिखोreg(state, 0xee, 0x03);
	cx24120_ग_लिखोreg(state, 0xef, 0x05);
	cx24120_ग_लिखोreg(state, 0xf3, 0x03);
	cx24120_ग_लिखोreg(state, 0xf4, 0x44);

	क्रम (i = 0; i < 3; i++) अणु
		cx24120_ग_लिखोreg(state, 0xf0 + i, 0x04);
		cx24120_ग_लिखोreg(state, 0xe6 + i, 0x02);
	पूर्ण

	cx24120_ग_लिखोreg(state, 0xea, (reg | 0x01));
	क्रम (i = 0; i < 6; i += 2) अणु
		cx24120_ग_लिखोreg(state, 0xc5 + i, 0x00);
		cx24120_ग_लिखोreg(state, 0xc6 + i, 0x00);
	पूर्ण

	cx24120_ग_लिखोreg(state, 0xe4, 0x03);
	cx24120_ग_लिखोreg(state, 0xeb, 0x0a);

	dev_dbg(&state->i2c->dev, "requesting firmware (%s) to download...\n",
		CX24120_FIRMWARE);

	ret = state->config->request_firmware(fe, &fw, CX24120_FIRMWARE);
	अगर (ret) अणु
		err("Could not load firmware (%s): %d\n", CX24120_FIRMWARE,
		    ret);
		वापस ret;
	पूर्ण

	dev_dbg(&state->i2c->dev,
		"Firmware found, size %d bytes (%02x %02x .. %02x %02x)\n",
		(पूर्णांक)fw->size,			/* firmware_size in bytes */
		fw->data[0],			/* fw 1st byte */
		fw->data[1],			/* fw 2d byte */
		fw->data[fw->size - 2],		/* fw beक्रमe last byte */
		fw->data[fw->size - 1]);	/* fw last byte */

	cx24120_test_rom(state);
	reg = cx24120_पढ़ोreg(state, 0xfb) & 0xfe;
	cx24120_ग_लिखोreg(state, 0xfb, reg);
	cx24120_ग_लिखोreg(state, 0xe0, 0x76);
	cx24120_ग_लिखोreg(state, 0xf7, 0x81);
	cx24120_ग_लिखोreg(state, 0xf8, 0x00);
	cx24120_ग_लिखोreg(state, 0xf9, 0x00);
	cx24120_ग_लिखोregs(state, 0xfa, fw->data, (fw->size - 1), 0x00);
	cx24120_ग_लिखोreg(state, 0xf7, 0xc0);
	cx24120_ग_लिखोreg(state, 0xe0, 0x00);
	reg = (fw->size - 2) & 0x00ff;
	cx24120_ग_लिखोreg(state, 0xf8, reg);
	reg = ((fw->size - 2) >> 8) & 0x00ff;
	cx24120_ग_लिखोreg(state, 0xf9, reg);
	cx24120_ग_लिखोreg(state, 0xf7, 0x00);
	cx24120_ग_लिखोreg(state, 0xdc, 0x00);
	cx24120_ग_लिखोreg(state, 0xdc, 0x07);
	msleep(500);

	/* Check final byte matches final byte of firmware */
	reg = cx24120_पढ़ोreg(state, 0xe1);
	अगर (reg == fw->data[fw->size - 1]) अणु
		dev_dbg(&state->i2c->dev, "Firmware uploaded successfully\n");
		ret = 0;
	पूर्ण अन्यथा अणु
		err("Firmware upload failed. Last byte returned=0x%x\n", ret);
		ret = -EREMOTEIO;
	पूर्ण
	cx24120_ग_लिखोreg(state, 0xdc, 0x00);
	release_firmware(fw);
	अगर (ret != 0)
		वापस ret;

	/* Start tuner */
	cmd.id = CMD_START_TUNER;
	cmd.len = 3;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x00;

	अगर (cx24120_message_send(state, &cmd) != 0) अणु
		err("Error tuner start! :(\n");
		वापस -EREMOTEIO;
	पूर्ण

	/* Set VCO */
	ret = cx24120_set_vco(state);
	अगर (ret != 0) अणु
		err("Error set VCO! :(\n");
		वापस ret;
	पूर्ण

	/* set bandwidth */
	cmd.id = CMD_BANDWIDTH;
	cmd.len = 12;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = 0x00;
	cmd.arg[2] = 0x00;
	cmd.arg[3] = 0x00;
	cmd.arg[4] = 0x05;
	cmd.arg[5] = 0x02;
	cmd.arg[6] = 0x02;
	cmd.arg[7] = 0x00;
	cmd.arg[8] = 0x05;
	cmd.arg[9] = 0x02;
	cmd.arg[10] = 0x02;
	cmd.arg[11] = 0x00;

	अगर (cx24120_message_send(state, &cmd)) अणु
		err("Error set bandwidth!\n");
		वापस -EREMOTEIO;
	पूर्ण

	reg = cx24120_पढ़ोreg(state, 0xba);
	अगर (reg > 3) अणु
		dev_dbg(&state->i2c->dev, "Reset-readreg 0xba: %x\n", ret);
		err("Error initialising tuner!\n");
		वापस -EREMOTEIO;
	पूर्ण

	dev_dbg(&state->i2c->dev, "Tuner initialised correctly.\n");

	/* Initialise mpeg outमाला_दो */
	cx24120_ग_लिखोreg(state, 0xeb, 0x0a);
	अगर (cx24120_msg_mpeg_output_global_config(state, 0) ||
	    cx24120_msg_mpeg_output_config(state, 0) ||
	    cx24120_msg_mpeg_output_config(state, 1) ||
	    cx24120_msg_mpeg_output_config(state, 2)) अणु
		err("Error initialising mpeg output. :(\n");
		वापस -EREMOTEIO;
	पूर्ण

	/* Set size of BER winकरोw */
	cmd.id = CMD_BER_CTRL;
	cmd.len = 3;
	cmd.arg[0] = 0x00;
	cmd.arg[1] = CX24120_BER_WINDOW;
	cmd.arg[2] = CX24120_BER_WINDOW;
	अगर (cx24120_message_send(state, &cmd)) अणु
		err("Error setting ber window\n");
		वापस -EREMOTEIO;
	पूर्ण

	/* Firmware CMD 35: Get firmware version */
	cmd.id = CMD_FWVERSION;
	cmd.len = 1;
	क्रम (i = 0; i < 4; i++) अणु
		cmd.arg[0] = i;
		ret = cx24120_message_send(state, &cmd);
		अगर (ret != 0)
			वापस ret;
		vers[i] = cx24120_पढ़ोreg(state, CX24120_REG_MAILBOX);
	पूर्ण
	info("FW version %i.%i.%i.%i\n", vers[0], vers[1], vers[2], vers[3]);

	/* init stats here in order संकेत app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	state->cold_init = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_tune(काष्ठा dvb_frontend *fe, bool re_tune,
			अचिन्हित पूर्णांक mode_flags, अचिन्हित पूर्णांक *delay,
			क्रमागत fe_status *status)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	dev_dbg(&state->i2c->dev, "(%d)\n", re_tune);

	/* TODO: Do we need to set delay? */

	अगर (re_tune) अणु
		ret = cx24120_set_frontend(fe);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस cx24120_पढ़ो_status(fe, status);
पूर्ण

अटल क्रमागत dvbfe_algo cx24120_get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल पूर्णांक cx24120_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cx24120_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	u8 freq1, freq2, freq3;
	पूर्णांक status;

	dev_dbg(&state->i2c->dev, "\n");

	/* करोn't return empty data if we're not tuned in */
	status = cx24120_पढ़ोreg(state, CX24120_REG_STATUS);
	अगर (!(status & CX24120_HAS_LOCK))
		वापस 0;

	/* Get frequency */
	freq1 = cx24120_पढ़ोreg(state, CX24120_REG_FREQ1);
	freq2 = cx24120_पढ़ोreg(state, CX24120_REG_FREQ2);
	freq3 = cx24120_पढ़ोreg(state, CX24120_REG_FREQ3);
	c->frequency = (freq3 << 16) | (freq2 << 8) | freq1;
	dev_dbg(&state->i2c->dev, "frequency = %d\n", c->frequency);

	/* Get modulation, fec, pilot */
	cx24120_get_fec(fe);

	वापस 0;
पूर्ण

अटल व्योम cx24120_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;

	dev_dbg(&state->i2c->dev, "Clear state structure\n");
	kमुक्त(state);
पूर्ण

अटल पूर्णांक cx24120_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा cx24120_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->block_error.stat[0].scale != FE_SCALE_COUNTER) अणु
		*ucblocks = 0;
		वापस 0;
	पूर्ण

	*ucblocks = c->block_error.stat[0].uvalue - state->ucb_offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24120_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name = "Conexant CX24120/CX24118",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.frequency_stepsize_hz = 1011 * kHz,
		.frequency_tolerance_hz = 5 * MHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps =	FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_2G_MODULATION |
			FE_CAN_QPSK | FE_CAN_RECOVER
	पूर्ण,
	.release =			cx24120_release,

	.init =				cx24120_init,
	.sleep =			cx24120_sleep,

	.tune =				cx24120_tune,
	.get_frontend_algo =		cx24120_get_algo,
	.set_frontend =			cx24120_set_frontend,

	.get_frontend =			cx24120_get_frontend,
	.पढ़ो_status =			cx24120_पढ़ो_status,
	.पढ़ो_ber =			cx24120_पढ़ो_ber,
	.पढ़ो_संकेत_strength =		cx24120_पढ़ो_संकेत_strength,
	.पढ़ो_snr =			cx24120_पढ़ो_snr,
	.पढ़ो_ucblocks =		cx24120_पढ़ो_ucblocks,

	.diseqc_send_master_cmd =	cx24120_send_diseqc_msg,

	.diseqc_send_burst =		cx24120_diseqc_send_burst,
	.set_tone =			cx24120_set_tone,
	.set_voltage =			cx24120_set_voltage,
पूर्ण;

MODULE_DESCRIPTION("DVB Frontend module for Conexant CX24120/CX24118 hardware");
MODULE_AUTHOR("Jemma Denson");
MODULE_LICENSE("GPL");
