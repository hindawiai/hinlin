<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Conexant cx24117/cx24132 - Dual DVBS/S2 Satellite demod/tuner driver

    Copyright (C) 2013 Luis Alves <ljalvs@gmail.com>
	July, 6th 2013
	    First release based on cx24116 driver by:
	    Steven Toth and Georg Acher, Darron Broad, Igor Liplianin
	    Cards currently supported:
		TBS6980 - Dual DVBS/S2 PCIe card
		TBS6981 - Dual DVBS/S2 PCIe card

*/

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/firmware.h>

#समावेश "tuner-i2c.h"
#समावेश <media/dvb_frontend.h>
#समावेश "cx24117.h"


#घोषणा CX24117_DEFAULT_FIRMWARE "dvb-fe-cx24117.fw"
#घोषणा CX24117_SEARCH_RANGE_KHZ 5000

/* known रेजिस्टरs */
#घोषणा CX24117_REG_COMMAND      (0x00)      /* command buffer */
#घोषणा CX24117_REG_EXECUTE      (0x1f)      /* execute command */

#घोषणा CX24117_REG_FREQ3_0      (0x34)      /* frequency */
#घोषणा CX24117_REG_FREQ2_0      (0x35)
#घोषणा CX24117_REG_FREQ1_0      (0x36)
#घोषणा CX24117_REG_STATE0       (0x39)
#घोषणा CX24117_REG_SSTATUS0     (0x3a)      /* demod0 संकेत high / status */
#घोषणा CX24117_REG_SIGNAL0      (0x3b)
#घोषणा CX24117_REG_FREQ5_0      (0x3c)      /* +-freq */
#घोषणा CX24117_REG_FREQ6_0      (0x3d)
#घोषणा CX24117_REG_SRATE2_0     (0x3e)      /* +- 1000 * srate */
#घोषणा CX24117_REG_SRATE1_0     (0x3f)
#घोषणा CX24117_REG_QUALITY2_0   (0x40)
#घोषणा CX24117_REG_QUALITY1_0   (0x41)

#घोषणा CX24117_REG_BER4_0       (0x47)
#घोषणा CX24117_REG_BER3_0       (0x48)
#घोषणा CX24117_REG_BER2_0       (0x49)
#घोषणा CX24117_REG_BER1_0       (0x4a)
#घोषणा CX24117_REG_DVBS_UCB2_0  (0x4b)
#घोषणा CX24117_REG_DVBS_UCB1_0  (0x4c)
#घोषणा CX24117_REG_DVBS2_UCB2_0 (0x50)
#घोषणा CX24117_REG_DVBS2_UCB1_0 (0x51)
#घोषणा CX24117_REG_QSTATUS0     (0x93)
#घोषणा CX24117_REG_CLKDIV0      (0xe6)
#घोषणा CX24117_REG_RATEDIV0     (0xf0)


#घोषणा CX24117_REG_FREQ3_1      (0x55)      /* frequency */
#घोषणा CX24117_REG_FREQ2_1      (0x56)
#घोषणा CX24117_REG_FREQ1_1      (0x57)
#घोषणा CX24117_REG_STATE1       (0x5a)
#घोषणा CX24117_REG_SSTATUS1     (0x5b)      /* demod1 संकेत high / status */
#घोषणा CX24117_REG_SIGNAL1      (0x5c)
#घोषणा CX24117_REG_FREQ5_1      (0x5d)      /* +- freq */
#घोषणा CX24117_REG_FREQ4_1      (0x5e)
#घोषणा CX24117_REG_SRATE2_1     (0x5f)
#घोषणा CX24117_REG_SRATE1_1     (0x60)
#घोषणा CX24117_REG_QUALITY2_1   (0x61)
#घोषणा CX24117_REG_QUALITY1_1   (0x62)
#घोषणा CX24117_REG_BER4_1       (0x68)
#घोषणा CX24117_REG_BER3_1       (0x69)
#घोषणा CX24117_REG_BER2_1       (0x6a)
#घोषणा CX24117_REG_BER1_1       (0x6b)
#घोषणा CX24117_REG_DVBS_UCB2_1  (0x6c)
#घोषणा CX24117_REG_DVBS_UCB1_1  (0x6d)
#घोषणा CX24117_REG_DVBS2_UCB2_1 (0x71)
#घोषणा CX24117_REG_DVBS2_UCB1_1 (0x72)
#घोषणा CX24117_REG_QSTATUS1     (0x9f)
#घोषणा CX24117_REG_CLKDIV1      (0xe7)
#घोषणा CX24117_REG_RATEDIV1     (0xf1)


/* arg buffer size */
#घोषणा CX24117_ARGLEN       (0x1e)

/* rolloff */
#घोषणा CX24117_ROLLOFF_020  (0x00)
#घोषणा CX24117_ROLLOFF_025  (0x01)
#घोषणा CX24117_ROLLOFF_035  (0x02)

/* pilot bit */
#घोषणा CX24117_PILOT_OFF    (0x00)
#घोषणा CX24117_PILOT_ON     (0x40)
#घोषणा CX24117_PILOT_AUTO   (0x80)

/* संकेत status */
#घोषणा CX24117_HAS_SIGNAL   (0x01)
#घोषणा CX24117_HAS_CARRIER  (0x02)
#घोषणा CX24117_HAS_VITERBI  (0x04)
#घोषणा CX24117_HAS_SYNCLOCK (0x08)
#घोषणा CX24117_STATUS_MASK  (0x0f)
#घोषणा CX24117_SIGNAL_MASK  (0xc0)


/* arg offset क्रम DiSEqC */
#घोषणा CX24117_DISEQC_DEMOD  (1)
#घोषणा CX24117_DISEQC_BURST  (2)
#घोषणा CX24117_DISEQC_ARG3_2 (3)   /* unknown value=2 */
#घोषणा CX24117_DISEQC_ARG4_0 (4)   /* unknown value=0 */
#घोषणा CX24117_DISEQC_ARG5_0 (5)   /* unknown value=0 */
#घोषणा CX24117_DISEQC_MSGLEN (6)
#घोषणा CX24117_DISEQC_MSGOFS (7)

/* DiSEqC burst */
#घोषणा CX24117_DISEQC_MINI_A (0)
#घोषणा CX24117_DISEQC_MINI_B (1)


#घोषणा CX24117_PNE	(0) /* 0 disabled / 2 enabled */
#घोषणा CX24117_OCC	(1) /* 0 disabled / 1 enabled */


क्रमागत cmds अणु
	CMD_SET_VCOFREQ    = 0x10,
	CMD_TUNEREQUEST    = 0x11,
	CMD_GLOBAL_MPEGCFG = 0x13,
	CMD_MPEGCFG        = 0x14,
	CMD_TUNERINIT      = 0x15,
	CMD_GET_SRATE      = 0x18,
	CMD_SET_GOLDCODE   = 0x19,
	CMD_GET_AGCACC     = 0x1a,
	CMD_DEMODINIT      = 0x1b,
	CMD_GETCTLACC      = 0x1c,

	CMD_LNBCONFIG      = 0x20,
	CMD_LNBSEND        = 0x21,
	CMD_LNBDCLEVEL     = 0x22,
	CMD_LNBPCBCONFIG   = 0x23,
	CMD_LNBSENDTONEBST = 0x24,
	CMD_LNBUPDREPLY    = 0x25,

	CMD_SET_GPIOMODE   = 0x30,
	CMD_SET_GPIOEN     = 0x31,
	CMD_SET_GPIOसूची    = 0x32,
	CMD_SET_GPIOOUT    = 0x33,
	CMD_ENABLERSCORR   = 0x34,
	CMD_FWVERSION      = 0x35,
	CMD_SET_SLEEPMODE  = 0x36,
	CMD_BERCTRL        = 0x3c,
	CMD_EVENTCTRL      = 0x3d,
पूर्ण;

अटल LIST_HEAD(hybrid_tuner_instance_list);
अटल DEFINE_MUTEX(cx24117_list_mutex);

/* The Demod/Tuner can't easily provide these, we cache them */
काष्ठा cx24117_tuning अणु
	u32 frequency;
	u32 symbol_rate;
	क्रमागत fe_spectral_inversion inversion;
	क्रमागत fe_code_rate fec;

	क्रमागत fe_delivery_प्रणाली delsys;
	क्रमागत fe_modulation modulation;
	क्रमागत fe_pilot pilot;
	क्रमागत fe_rolloff rolloff;

	/* Demod values */
	u8 fec_val;
	u8 fec_mask;
	u8 inversion_val;
	u8 pilot_val;
	u8 rolloff_val;
पूर्ण;

/* Basic commands that are sent to the firmware */
काष्ठा cx24117_cmd अणु
	u8 len;
	u8 args[CX24117_ARGLEN];
पूर्ण;

/* common to both fe's */
काष्ठा cx24117_priv अणु
	u8 demod_address;
	काष्ठा i2c_adapter *i2c;
	u8 skip_fw_load;
	काष्ठा mutex fe_lock;

	/* Used क्रम sharing this काष्ठा between demods */
	काष्ठा tuner_i2c_props i2c_props;
	काष्ठा list_head hybrid_tuner_instance_list;
पूर्ण;

/* one per each fe */
काष्ठा cx24117_state अणु
	काष्ठा cx24117_priv *priv;
	काष्ठा dvb_frontend frontend;

	काष्ठा cx24117_tuning dcur;
	काष्ठा cx24117_tuning dnxt;
	काष्ठा cx24117_cmd dsec_cmd;

	पूर्णांक demod;
पूर्ण;

/* modfec (modulation and FEC) lookup table */
/* Check cx24116.c क्रम a detailed description of each field */
अटल काष्ठा cx24117_modfec अणु
	क्रमागत fe_delivery_प्रणाली delivery_प्रणाली;
	क्रमागत fe_modulation modulation;
	क्रमागत fe_code_rate fec;
	u8 mask;	/* In DVBS mode this is used to स्वतःdetect */
	u8 val;		/* Passed to the firmware to indicate mode selection */
पूर्ण cx24117_modfec_modes[] = अणु
	/* QPSK. For unknown rates we set hardware to स्वतः detect 0xfe 0x30 */

	/*mod   fec       mask  val */
	अणु SYS_DVBS, QPSK, FEC_NONE, 0xfe, 0x30 पूर्ण,
	अणु SYS_DVBS, QPSK, FEC_1_2,  0x02, 0x2e पूर्ण, /* 00000010 00101110 */
	अणु SYS_DVBS, QPSK, FEC_2_3,  0x04, 0x2f पूर्ण, /* 00000100 00101111 */
	अणु SYS_DVBS, QPSK, FEC_3_4,  0x08, 0x30 पूर्ण, /* 00001000 00110000 */
	अणु SYS_DVBS, QPSK, FEC_4_5,  0xfe, 0x30 पूर्ण, /* 000?0000 ?        */
	अणु SYS_DVBS, QPSK, FEC_5_6,  0x20, 0x31 पूर्ण, /* 00100000 00110001 */
	अणु SYS_DVBS, QPSK, FEC_6_7,  0xfe, 0x30 पूर्ण, /* 0?000000 ?        */
	अणु SYS_DVBS, QPSK, FEC_7_8,  0x80, 0x32 पूर्ण, /* 10000000 00110010 */
	अणु SYS_DVBS, QPSK, FEC_8_9,  0xfe, 0x30 पूर्ण, /* 0000000? ?        */
	अणु SYS_DVBS, QPSK, FEC_AUTO, 0xfe, 0x30 पूर्ण,
	/* NBC-QPSK */
	अणु SYS_DVBS2, QPSK, FEC_NONE, 0x00, 0x00 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_1_2,  0x00, 0x04 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_3_5,  0x00, 0x05 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_2_3,  0x00, 0x06 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_3_4,  0x00, 0x07 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_4_5,  0x00, 0x08 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_5_6,  0x00, 0x09 पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_8_9,  0x00, 0x0a पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_9_10, 0x00, 0x0b पूर्ण,
	अणु SYS_DVBS2, QPSK, FEC_AUTO, 0x00, 0x00 पूर्ण,
	/* 8PSK */
	अणु SYS_DVBS2, PSK_8, FEC_NONE, 0x00, 0x00 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_3_5,  0x00, 0x0c पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_2_3,  0x00, 0x0d पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_3_4,  0x00, 0x0e पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_5_6,  0x00, 0x0f पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_8_9,  0x00, 0x10 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_9_10, 0x00, 0x11 पूर्ण,
	अणु SYS_DVBS2, PSK_8, FEC_AUTO, 0x00, 0x00 पूर्ण,
	/*
	 * 'val' can be found in the FECSTATUS रेजिस्टर when tuning.
	 * FECSTATUS will give the actual FEC in use अगर tuning was successful.
	 */
पूर्ण;


अटल पूर्णांक cx24117_ग_लिखोreg(काष्ठा cx24117_state *state, u8 reg, u8 data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->priv->demod_address,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक ret;

	dev_dbg(&state->priv->i2c->dev,
			"%s() demod%d i2c wr @0x%02x=0x%02x\n",
			__func__, state->demod, reg, data);

	ret = i2c_transfer(state->priv->i2c, &msg, 1);
	अगर (ret < 0) अणु
		dev_warn(&state->priv->i2c->dev,
			"%s: demod%d i2c wr err(%i) @0x%02x=0x%02x\n",
			KBUILD_MODNAME, state->demod, ret, reg, data);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_ग_लिखोcmd(काष्ठा cx24117_state *state,
	काष्ठा cx24117_cmd *cmd)
अणु
	काष्ठा i2c_msg msg;
	u8 buf[CX24117_ARGLEN+1];
	पूर्णांक ret;

	dev_dbg(&state->priv->i2c->dev,
			"%s() demod%d i2c wr cmd len=%d\n",
			__func__, state->demod, cmd->len);

	buf[0] = CX24117_REG_COMMAND;
	स_नकल(&buf[1], cmd->args, cmd->len);

	msg.addr = state->priv->demod_address;
	msg.flags = 0;
	msg.len = cmd->len+1;
	msg.buf = buf;
	ret = i2c_transfer(state->priv->i2c, &msg, 1);
	अगर (ret < 0) अणु
		dev_warn(&state->priv->i2c->dev,
			"%s: demod%d i2c wr cmd err(%i) len=%d\n",
			KBUILD_MODNAME, state->demod, ret, cmd->len);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_पढ़ोreg(काष्ठा cx24117_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 recv = 0;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->priv->demod_address, .flags = 0,
			.buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->priv->demod_address, .flags = I2C_M_RD,
			.buf = &recv, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->priv->i2c, msg, 2);
	अगर (ret < 0) अणु
		dev_warn(&state->priv->i2c->dev,
			"%s: demod%d i2c rd err(%d) @0x%x\n",
			KBUILD_MODNAME, state->demod, ret, reg);
		वापस ret;
	पूर्ण

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d i2c rd @0x%02x=0x%02x\n",
		__func__, state->demod, reg, recv);

	वापस recv;
पूर्ण

अटल पूर्णांक cx24117_पढ़ोregN(काष्ठा cx24117_state *state,
	u8 reg, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->priv->demod_address, .flags = 0,
			.buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->priv->demod_address, .flags = I2C_M_RD,
			.buf = buf, .len = len पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->priv->i2c, msg, 2);
	अगर (ret < 0) अणु
		dev_warn(&state->priv->i2c->dev,
			"%s: demod%d i2c rd err(%d) @0x%x\n",
			KBUILD_MODNAME, state->demod, ret, reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_set_inversion(काष्ठा cx24117_state *state,
	क्रमागत fe_spectral_inversion inversion)
अणु
	dev_dbg(&state->priv->i2c->dev, "%s(%d) demod%d\n",
		__func__, inversion, state->demod);

	चयन (inversion) अणु
	हाल INVERSION_OFF:
		state->dnxt.inversion_val = 0x00;
		अवरोध;
	हाल INVERSION_ON:
		state->dnxt.inversion_val = 0x04;
		अवरोध;
	हाल INVERSION_AUTO:
		state->dnxt.inversion_val = 0x0C;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	state->dnxt.inversion = inversion;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_lookup_fecmod(काष्ठा cx24117_state *state,
	क्रमागत fe_delivery_प्रणाली d, क्रमागत fe_modulation m, क्रमागत fe_code_rate f)
अणु
	पूर्णांक i, ret = -EINVAL;

	dev_dbg(&state->priv->i2c->dev,
		"%s(demod(0x%02x,0x%02x) demod%d\n",
		__func__, m, f, state->demod);

	क्रम (i = 0; i < ARRAY_SIZE(cx24117_modfec_modes); i++) अणु
		अगर ((d == cx24117_modfec_modes[i].delivery_प्रणाली) &&
			(m == cx24117_modfec_modes[i].modulation) &&
			(f == cx24117_modfec_modes[i].fec)) अणु
				ret = i;
				अवरोध;
			पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cx24117_set_fec(काष्ठा cx24117_state *state,
			   क्रमागत fe_delivery_प्रणाली delsys,
			   क्रमागत fe_modulation mod,
			   क्रमागत fe_code_rate fec)
अणु
	पूर्णांक ret;

	dev_dbg(&state->priv->i2c->dev,
		"%s(0x%02x,0x%02x) demod%d\n",
		__func__, mod, fec, state->demod);

	ret = cx24117_lookup_fecmod(state, delsys, mod, fec);
	अगर (ret < 0)
		वापस ret;

	state->dnxt.fec = fec;
	state->dnxt.fec_val = cx24117_modfec_modes[ret].val;
	state->dnxt.fec_mask = cx24117_modfec_modes[ret].mask;
	dev_dbg(&state->priv->i2c->dev,
		"%s() demod%d mask/val = 0x%02x/0x%02x\n", __func__,
		state->demod, state->dnxt.fec_mask, state->dnxt.fec_val);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_set_symbolrate(काष्ठा cx24117_state *state, u32 rate)
अणु
	dev_dbg(&state->priv->i2c->dev, "%s(%d) demod%d\n",
		__func__, rate, state->demod);

	state->dnxt.symbol_rate = rate;

	dev_dbg(&state->priv->i2c->dev,
		"%s() demod%d symbol_rate = %d\n",
		__func__, state->demod, rate);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_load_firmware(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा firmware *fw);

अटल पूर्णांक cx24117_firmware_ondemand(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 0;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d skip_fw_load=%d\n",
		__func__, state->demod, state->priv->skip_fw_load);

	अगर (state->priv->skip_fw_load)
		वापस 0;

	/* check अगर firmware is alपढ़ोy running */
	अगर (cx24117_पढ़ोreg(state, 0xeb) != 0xa) अणु
		/* Load firmware */
		/* request the firmware, this will block until loaded */
		dev_dbg(&state->priv->i2c->dev,
			"%s: Waiting for firmware upload (%s)...\n",
			__func__, CX24117_DEFAULT_FIRMWARE);
		ret = request_firmware(&fw, CX24117_DEFAULT_FIRMWARE,
			state->priv->i2c->dev.parent);
		dev_dbg(&state->priv->i2c->dev,
			"%s: Waiting for firmware upload(2)...\n", __func__);
		अगर (ret) अणु
			dev_err(&state->priv->i2c->dev,
				"%s: No firmware uploaded (timeout or file not found?)\n",
__func__);
			वापस ret;
		पूर्ण

		/* Make sure we करोn't recurse back through here
		 * during loading */
		state->priv->skip_fw_load = 1;

		ret = cx24117_load_firmware(fe, fw);
		अगर (ret)
			dev_err(&state->priv->i2c->dev,
				"%s: Writing firmware failed\n", __func__);
		release_firmware(fw);

		dev_info(&state->priv->i2c->dev,
			"%s: Firmware upload %s\n", __func__,
			ret == 0 ? "complete" : "failed");

		/* Ensure firmware is always loaded अगर required */
		state->priv->skip_fw_load = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Take a basic firmware command काष्ठाure, क्रमmat it
 * and क्रमward it क्रम processing
 */
अटल पूर्णांक cx24117_cmd_execute_nolock(काष्ठा dvb_frontend *fe,
	काष्ठा cx24117_cmd *cmd)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक i, ret;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	/* Load the firmware अगर required */
	ret = cx24117_firmware_ondemand(fe);
	अगर (ret != 0)
		वापस ret;

	/* Write the command */
	cx24117_ग_लिखोcmd(state, cmd);

	/* Start execution and रुको क्रम cmd to terminate */
	cx24117_ग_लिखोreg(state, CX24117_REG_EXECUTE, 0x01);
	i = 0;
	जबतक (cx24117_पढ़ोreg(state, CX24117_REG_EXECUTE)) अणु
		msleep(20);
		अगर (i++ > 40) अणु
			/* Aव्योम looping क्रमever अगर the firmware करोes
				not respond */
			dev_warn(&state->priv->i2c->dev,
				"%s() Firmware not responding\n", __func__);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_cmd_execute(काष्ठा dvb_frontend *fe, काष्ठा cx24117_cmd *cmd)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->priv->fe_lock);
	ret = cx24117_cmd_execute_nolock(fe, cmd);
	mutex_unlock(&state->priv->fe_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cx24117_load_firmware(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;
	पूर्णांक i, ret;
	अचिन्हित अक्षर vers[4];

	काष्ठा i2c_msg msg;
	u8 *buf;

	dev_dbg(&state->priv->i2c->dev,
		"%s() demod%d FW is %zu bytes (%02x %02x .. %02x %02x)\n",
		__func__, state->demod, fw->size, fw->data[0], fw->data[1],
		fw->data[fw->size - 2], fw->data[fw->size - 1]);

	cx24117_ग_लिखोreg(state, 0xea, 0x00);
	cx24117_ग_लिखोreg(state, 0xea, 0x01);
	cx24117_ग_लिखोreg(state, 0xea, 0x00);

	cx24117_ग_लिखोreg(state, 0xce, 0x92);

	cx24117_ग_लिखोreg(state, 0xfb, 0x00);
	cx24117_ग_लिखोreg(state, 0xfc, 0x00);

	cx24117_ग_लिखोreg(state, 0xc3, 0x04);
	cx24117_ग_लिखोreg(state, 0xc4, 0x04);

	cx24117_ग_लिखोreg(state, 0xce, 0x00);
	cx24117_ग_लिखोreg(state, 0xcf, 0x00);

	cx24117_ग_लिखोreg(state, 0xea, 0x00);
	cx24117_ग_लिखोreg(state, 0xeb, 0x0c);
	cx24117_ग_लिखोreg(state, 0xec, 0x06);
	cx24117_ग_लिखोreg(state, 0xed, 0x05);
	cx24117_ग_लिखोreg(state, 0xee, 0x03);
	cx24117_ग_लिखोreg(state, 0xef, 0x05);

	cx24117_ग_लिखोreg(state, 0xf3, 0x03);
	cx24117_ग_लिखोreg(state, 0xf4, 0x44);

	cx24117_ग_लिखोreg(state, CX24117_REG_RATEDIV0, 0x04);
	cx24117_ग_लिखोreg(state, CX24117_REG_CLKDIV0, 0x02);

	cx24117_ग_लिखोreg(state, CX24117_REG_RATEDIV1, 0x04);
	cx24117_ग_लिखोreg(state, CX24117_REG_CLKDIV1, 0x02);

	cx24117_ग_लिखोreg(state, 0xf2, 0x04);
	cx24117_ग_लिखोreg(state, 0xe8, 0x02);
	cx24117_ग_लिखोreg(state, 0xea, 0x01);
	cx24117_ग_लिखोreg(state, 0xc8, 0x00);
	cx24117_ग_लिखोreg(state, 0xc9, 0x00);
	cx24117_ग_लिखोreg(state, 0xca, 0x00);
	cx24117_ग_लिखोreg(state, 0xcb, 0x00);
	cx24117_ग_लिखोreg(state, 0xcc, 0x00);
	cx24117_ग_लिखोreg(state, 0xcd, 0x00);
	cx24117_ग_लिखोreg(state, 0xe4, 0x03);
	cx24117_ग_लिखोreg(state, 0xeb, 0x0a);

	cx24117_ग_लिखोreg(state, 0xfb, 0x00);
	cx24117_ग_लिखोreg(state, 0xe0, 0x76);
	cx24117_ग_लिखोreg(state, 0xf7, 0x81);
	cx24117_ग_लिखोreg(state, 0xf8, 0x00);
	cx24117_ग_लिखोreg(state, 0xf9, 0x00);

	buf = kदो_स्मृति(fw->size + 1, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		state->priv->skip_fw_load = 0;
		वापस -ENOMEM;
	पूर्ण

	/* fw upload reg */
	buf[0] = 0xfa;
	स_नकल(&buf[1], fw->data, fw->size);

	/* prepare i2c message to send */
	msg.addr = state->priv->demod_address;
	msg.flags = 0;
	msg.len = fw->size + 1;
	msg.buf = buf;

	/* send fw */
	ret = i2c_transfer(state->priv->i2c, &msg, 1);
	अगर (ret < 0) अणु
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	kमुक्त(buf);

	cx24117_ग_लिखोreg(state, 0xf7, 0x0c);
	cx24117_ग_लिखोreg(state, 0xe0, 0x00);

	/* Init demodulator */
	cmd.args[0] = CMD_DEMODINIT;
	cmd.args[1] = 0x00;
	cmd.args[2] = 0x01;
	cmd.args[3] = 0x00;
	cmd.len = 4;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ error;

	/* Set VCO frequency */
	cmd.args[0] = CMD_SET_VCOFREQ;
	cmd.args[1] = 0x06;
	cmd.args[2] = 0x2b;
	cmd.args[3] = 0xd8;
	cmd.args[4] = 0xa5;
	cmd.args[5] = 0xee;
	cmd.args[6] = 0x03;
	cmd.args[7] = 0x9d;
	cmd.args[8] = 0xfc;
	cmd.args[9] = 0x06;
	cmd.args[10] = 0x02;
	cmd.args[11] = 0x9d;
	cmd.args[12] = 0xfc;
	cmd.len = 13;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ error;

	/* Tuner init */
	cmd.args[0] = CMD_TUNERINIT;
	cmd.args[1] = 0x00;
	cmd.args[2] = 0x01;
	cmd.args[3] = 0x00;
	cmd.args[4] = 0x00;
	cmd.args[5] = 0x01;
	cmd.args[6] = 0x01;
	cmd.args[7] = 0x01;
	cmd.args[8] = 0x00;
	cmd.args[9] = 0x05;
	cmd.args[10] = 0x02;
	cmd.args[11] = 0x02;
	cmd.args[12] = 0x00;
	cmd.len = 13;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ error;

	/* Global MPEG config */
	cmd.args[0] = CMD_GLOBAL_MPEGCFG;
	cmd.args[1] = 0x00;
	cmd.args[2] = 0x00;
	cmd.args[3] = 0x00;
	cmd.args[4] = 0x01;
	cmd.args[5] = 0x00;
	cmd.len = 6;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ error;

	/* MPEG config क्रम each demod */
	क्रम (i = 0; i < 2; i++) अणु
		cmd.args[0] = CMD_MPEGCFG;
		cmd.args[1] = (u8) i;
		cmd.args[2] = 0x00;
		cmd.args[3] = 0x05;
		cmd.args[4] = 0x00;
		cmd.args[5] = 0x00;
		cmd.args[6] = 0x55;
		cmd.args[7] = 0x00;
		cmd.len = 8;
		ret = cx24117_cmd_execute_nolock(fe, &cmd);
		अगर (ret != 0)
			जाओ error;
	पूर्ण

	cx24117_ग_लिखोreg(state, 0xce, 0xc0);
	cx24117_ग_लिखोreg(state, 0xcf, 0x00);
	cx24117_ग_लिखोreg(state, 0xe5, 0x04);

	/* Get firmware version */
	cmd.args[0] = CMD_FWVERSION;
	cmd.len = 2;
	क्रम (i = 0; i < 4; i++) अणु
		cmd.args[1] = i;
		ret = cx24117_cmd_execute_nolock(fe, &cmd);
		अगर (ret != 0)
			जाओ error;
		vers[i] = cx24117_पढ़ोreg(state, 0x33);
	पूर्ण
	dev_info(&state->priv->i2c->dev,
		"%s: FW version %i.%i.%i.%i\n", __func__,
		vers[0], vers[1], vers[2], vers[3]);
	वापस 0;
error:
	state->priv->skip_fw_load = 0;
	dev_err(&state->priv->i2c->dev, "%s() Error running FW.\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक cx24117_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक lock;

	lock = cx24117_पढ़ोreg(state,
		(state->demod == 0) ? CX24117_REG_SSTATUS0 :
				      CX24117_REG_SSTATUS1) &
		CX24117_STATUS_MASK;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d status = 0x%02x\n",
		__func__, state->demod, lock);

	*status = 0;

	अगर (lock & CX24117_HAS_SIGNAL)
		*status |= FE_HAS_SIGNAL;
	अगर (lock & CX24117_HAS_CARRIER)
		*status |= FE_HAS_CARRIER;
	अगर (lock & CX24117_HAS_VITERBI)
		*status |= FE_HAS_VITERBI;
	अगर (lock & CX24117_HAS_SYNCLOCK)
		*status |= FE_HAS_SYNC | FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[4];
	u8 base_reg = (state->demod == 0) ?
			CX24117_REG_BER4_0 :
			CX24117_REG_BER4_1;

	ret = cx24117_पढ़ोregN(state, base_reg, buf, 4);
	अगर (ret != 0)
		वापस ret;

	*ber = (buf[0] << 24) | (buf[1] << 16) |
		(buf[1] << 8) | buf[0];

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d ber=0x%04x\n",
		__func__, state->demod, *ber);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *संकेत_strength)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;
	पूर्णांक ret;
	u16 sig_पढ़ोing;
	u8 buf[2];
	u8 reg = (state->demod == 0) ?
		CX24117_REG_SSTATUS0 : CX24117_REG_SSTATUS1;

	/* Read AGC accumulator रेजिस्टर */
	cmd.args[0] = CMD_GET_AGCACC;
	cmd.args[1] = (u8) state->demod;
	cmd.len = 2;
	ret = cx24117_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	ret = cx24117_पढ़ोregN(state, reg, buf, 2);
	अगर (ret != 0)
		वापस ret;
	sig_पढ़ोing = ((buf[0] & CX24117_SIGNAL_MASK) << 2) | buf[1];

	*संकेत_strength = -100 * sig_पढ़ोing + 94324;

	dev_dbg(&state->priv->i2c->dev,
		"%s() demod%d raw / cooked = 0x%04x / 0x%04x\n",
		__func__, state->demod, sig_पढ़ोing, *संकेत_strength);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[2];
	u8 reg = (state->demod == 0) ?
		CX24117_REG_QUALITY2_0 : CX24117_REG_QUALITY2_1;

	ret = cx24117_पढ़ोregN(state, reg, buf, 2);
	अगर (ret != 0)
		वापस ret;

	*snr = (buf[0] << 8) | buf[1];

	dev_dbg(&state->priv->i2c->dev,
		"%s() demod%d snr = 0x%04x\n",
		__func__, state->demod, *snr);

	वापस ret;
पूर्ण

अटल पूर्णांक cx24117_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	क्रमागत fe_delivery_प्रणाली delsys = fe->dtv_property_cache.delivery_प्रणाली;
	पूर्णांक ret;
	u8 buf[2];
	u8 reg = (state->demod == 0) ?
		CX24117_REG_DVBS_UCB2_0 :
		CX24117_REG_DVBS_UCB2_1;

	चयन (delsys) अणु
	हाल SYS_DVBS:
		अवरोध;
	हाल SYS_DVBS2:
		reg += (CX24117_REG_DVBS2_UCB2_0 - CX24117_REG_DVBS_UCB2_0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = cx24117_पढ़ोregN(state, reg, buf, 2);
	अगर (ret != 0)
		वापस ret;
	*ucblocks = (buf[0] << 8) | buf[1];

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d ucb=0x%04x\n",
		__func__, state->demod, *ucblocks);

	वापस 0;
पूर्ण

/* Overग_लिखो the current tuning params, we are about to tune */
अटल व्योम cx24117_clone_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	state->dcur = state->dnxt;
पूर्ण

/* Wait क्रम LNB */
अटल पूर्णांक cx24117_रुको_क्रम_lnb(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक i;
	u8 val, reg = (state->demod == 0) ? CX24117_REG_QSTATUS0 :
					    CX24117_REG_QSTATUS1;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d qstatus = 0x%02x\n",
		__func__, state->demod, cx24117_पढ़ोreg(state, reg));

	/* Wait क्रम up to 300 ms */
	क्रम (i = 0; i < 10; i++) अणु
		val = cx24117_पढ़ोreg(state, reg) & 0x01;
		अगर (val != 0)
			वापस 0;
		msleep(30);
	पूर्ण

	dev_warn(&state->priv->i2c->dev, "%s: demod%d LNB not ready\n",
		KBUILD_MODNAME, state->demod);

	वापस -ETIMEDOUT; /* -EBUSY ? */
पूर्ण

अटल पूर्णांक cx24117_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;
	पूर्णांक ret;
	u8 reg = (state->demod == 0) ? 0x10 : 0x20;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d %s\n",
		__func__, state->demod,
		voltage == SEC_VOLTAGE_13 ? "SEC_VOLTAGE_13" :
		voltage == SEC_VOLTAGE_18 ? "SEC_VOLTAGE_18" :
		"SEC_VOLTAGE_OFF");

	/* Prepare a set GPIO logic level CMD */
	cmd.args[0] = CMD_SET_GPIOOUT;
	cmd.args[2] = reg; /* mask */
	cmd.len = 3;

	अगर ((voltage == SEC_VOLTAGE_13) ||
	    (voltage == SEC_VOLTAGE_18)) अणु
		/* घातer on LNB */
		cmd.args[1] = reg;
		ret = cx24117_cmd_execute(fe, &cmd);
		अगर (ret != 0)
			वापस ret;

		ret = cx24117_रुको_क्रम_lnb(fe);
		अगर (ret != 0)
			वापस ret;

		/* Wait क्रम voltage/min repeat delay */
		msleep(100);

		/* Set 13V/18V select pin */
		cmd.args[0] = CMD_LNBDCLEVEL;
		cmd.args[1] = state->demod ? 0 : 1;
		cmd.args[2] = (voltage == SEC_VOLTAGE_18 ? 0x01 : 0x00);
		cmd.len = 3;
		ret = cx24117_cmd_execute(fe, &cmd);

		/* Min delay समय beक्रमe DiSEqC send */
		msleep(20);
	पूर्ण अन्यथा अणु
		/* घातer off LNB */
		cmd.args[1] = 0x00;
		ret = cx24117_cmd_execute(fe, &cmd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cx24117_set_tone(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;
	पूर्णांक ret;

	dev_dbg(&state->priv->i2c->dev, "%s(%d) demod%d\n",
		__func__, state->demod, tone);
	अगर ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) अणु
		dev_warn(&state->priv->i2c->dev, "%s: demod%d invalid tone=%d\n",
			KBUILD_MODNAME, state->demod, tone);
		वापस -EINVAL;
	पूर्ण

	/* Wait क्रम LNB पढ़ोy */
	ret = cx24117_रुको_क्रम_lnb(fe);
	अगर (ret != 0)
		वापस ret;

	/* Min delay समय after DiSEqC send */
	msleep(20);

	/* Set the tone */
	cmd.args[0] = CMD_LNBPCBCONFIG;
	cmd.args[1] = (state->demod ? 0 : 1);
	cmd.args[2] = 0x00;
	cmd.args[3] = 0x00;
	cmd.len = 5;
	चयन (tone) अणु
	हाल SEC_TONE_ON:
		cmd.args[4] = 0x01;
		अवरोध;
	हाल SEC_TONE_OFF:
		cmd.args[4] = 0x00;
		अवरोध;
	पूर्ण

	msleep(20);

	वापस cx24117_cmd_execute(fe, &cmd);
पूर्ण

/* Initialise DiSEqC */
अटल पूर्णांक cx24117_diseqc_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;

	/* Prepare a DiSEqC command */
	state->dsec_cmd.args[0] = CMD_LNBSEND;

	/* demod */
	state->dsec_cmd.args[CX24117_DISEQC_DEMOD] = state->demod ? 0 : 1;

	/* DiSEqC burst */
	state->dsec_cmd.args[CX24117_DISEQC_BURST] = CX24117_DISEQC_MINI_A;

	/* Unknown */
	state->dsec_cmd.args[CX24117_DISEQC_ARG3_2] = 0x02;
	state->dsec_cmd.args[CX24117_DISEQC_ARG4_0] = 0x00;

	/* Continuation flag? */
	state->dsec_cmd.args[CX24117_DISEQC_ARG5_0] = 0x00;

	/* DiSEqC message length */
	state->dsec_cmd.args[CX24117_DISEQC_MSGLEN] = 0x00;

	/* Command length */
	state->dsec_cmd.len = 7;

	वापस 0;
पूर्ण

/* Send DiSEqC message */
अटल पूर्णांक cx24117_send_diseqc_msg(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_diseqc_master_cmd *d)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	पूर्णांक i, ret;

	/* Dump DiSEqC message */
	dev_dbg(&state->priv->i2c->dev, "%s: demod %d (",
		__func__, state->demod);
	क्रम (i = 0; i < d->msg_len; i++)
		dev_dbg(&state->priv->i2c->dev, "0x%02x ", d->msg[i]);
	dev_dbg(&state->priv->i2c->dev, ")\n");

	/* Validate length */
	अगर (d->msg_len > माप(d->msg))
		वापस -EINVAL;

	/* DiSEqC message */
	क्रम (i = 0; i < d->msg_len; i++)
		state->dsec_cmd.args[CX24117_DISEQC_MSGOFS + i] = d->msg[i];

	/* DiSEqC message length */
	state->dsec_cmd.args[CX24117_DISEQC_MSGLEN] = d->msg_len;

	/* Command length */
	state->dsec_cmd.len = CX24117_DISEQC_MSGOFS +
		state->dsec_cmd.args[CX24117_DISEQC_MSGLEN];

	/*
	 * Message is sent with derived अन्यथा cached burst
	 *
	 * WRITE PORT GROUP COMMAND 38
	 *
	 * 0/A/A: E0 10 38 F0..F3
	 * 1/B/B: E0 10 38 F4..F7
	 * 2/C/A: E0 10 38 F8..FB
	 * 3/D/B: E0 10 38 FC..FF
	 *
	 * databyte[3]= 8421:8421
	 *              ABCD:WXYZ
	 *              CLR :SET
	 *
	 *              WX= PORT SELECT 0..3    (X=TONEBURST)
	 *              Y = VOLTAGE             (0=13V, 1=18V)
	 *              Z = BAND                (0=LOW, 1=HIGH(22K))
	 */
	अगर (d->msg_len >= 4 && d->msg[2] == 0x38)
		state->dsec_cmd.args[CX24117_DISEQC_BURST] =
			((d->msg[3] & 4) >> 2);

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d burst=%d\n",
		__func__, state->demod,
		state->dsec_cmd.args[CX24117_DISEQC_BURST]);

	/* Wait क्रम LNB पढ़ोy */
	ret = cx24117_रुको_क्रम_lnb(fe);
	अगर (ret != 0)
		वापस ret;

	/* Wait क्रम voltage/min repeat delay */
	msleep(100);

	/* Command */
	ret = cx24117_cmd_execute(fe, &state->dsec_cmd);
	अगर (ret != 0)
		वापस ret;
	/*
	 * Wait क्रम send
	 *
	 * Eutelsat spec:
	 * >15ms delay          + (XXX determine अगर FW करोes this, see set_tone)
	 *  13.5ms per byte     +
	 * >15ms delay          +
	 *  12.5ms burst        +
	 * >15ms delay            (XXX determine अगर FW करोes this, see set_tone)
	 */
	msleep((state->dsec_cmd.args[CX24117_DISEQC_MSGLEN] << 4) + 60);

	वापस 0;
पूर्ण

/* Send DiSEqC burst */
अटल पूर्णांक cx24117_diseqc_send_burst(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;

	dev_dbg(&state->priv->i2c->dev, "%s(%d) demod=%d\n",
		__func__, burst, state->demod);

	/* DiSEqC burst */
	अगर (burst == SEC_MINI_A)
		state->dsec_cmd.args[CX24117_DISEQC_BURST] =
			CX24117_DISEQC_MINI_A;
	अन्यथा अगर (burst == SEC_MINI_B)
		state->dsec_cmd.args[CX24117_DISEQC_BURST] =
			CX24117_DISEQC_MINI_B;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24117_get_priv(काष्ठा cx24117_priv **priv,
	काष्ठा i2c_adapter *i2c, u8 client_address)
अणु
	पूर्णांक ret;

	mutex_lock(&cx24117_list_mutex);
	ret = hybrid_tuner_request_state(काष्ठा cx24117_priv, (*priv),
		hybrid_tuner_instance_list, i2c, client_address, "cx24117");
	mutex_unlock(&cx24117_list_mutex);

	वापस ret;
पूर्ण

अटल व्योम cx24117_release_priv(काष्ठा cx24117_priv *priv)
अणु
	mutex_lock(&cx24117_list_mutex);
	अगर (priv != शून्य)
		hybrid_tuner_release_state(priv);
	mutex_unlock(&cx24117_list_mutex);
पूर्ण

अटल व्योम cx24117_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	dev_dbg(&state->priv->i2c->dev, "%s demod%d\n",
		__func__, state->demod);
	cx24117_release_priv(state->priv);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24117_ops;

काष्ठा dvb_frontend *cx24117_attach(स्थिर काष्ठा cx24117_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा cx24117_state *state = शून्य;
	काष्ठा cx24117_priv *priv = शून्य;
	पूर्णांक demod = 0;

	/* get the common data काष्ठा क्रम both demods */
	demod = cx24117_get_priv(&priv, i2c, config->demod_address);

	चयन (demod) अणु
	हाल 0:
		dev_err(&i2c->dev,
			"%s: Error attaching frontend %d\n",
			KBUILD_MODNAME, demod);
		जाओ error1;
		अवरोध;
	हाल 1:
		/* new priv instance */
		priv->i2c = i2c;
		priv->demod_address = config->demod_address;
		mutex_init(&priv->fe_lock);
		अवरोध;
	शेष:
		/* existing priv instance */
		अवरोध;
	पूर्ण

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा cx24117_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error2;

	state->demod = demod - 1;
	state->priv = priv;

	dev_info(&state->priv->i2c->dev,
		"%s: Attaching frontend %d\n",
		KBUILD_MODNAME, state->demod);

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &cx24117_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error2:
	cx24117_release_priv(priv);
error1:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cx24117_attach);

/*
 * Initialise or wake up device
 *
 * Power config will reset and load initial firmware अगर required
 */
अटल पूर्णांक cx24117_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;
	पूर्णांक ret;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	mutex_lock(&state->priv->fe_lock);

	/* Set sleep mode off */
	cmd.args[0] = CMD_SET_SLEEPMODE;
	cmd.args[1] = (state->demod ? 1 : 0);
	cmd.args[2] = 0;
	cmd.len = 3;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ निकास;

	ret = cx24117_diseqc_init(fe);
	अगर (ret != 0)
		जाओ निकास;

	/* Set BER control */
	cmd.args[0] = CMD_BERCTRL;
	cmd.args[1] = (state->demod ? 1 : 0);
	cmd.args[2] = 0x10;
	cmd.args[3] = 0x10;
	cmd.len = 4;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ निकास;

	/* Set RS correction (enable/disable) */
	cmd.args[0] = CMD_ENABLERSCORR;
	cmd.args[1] = (state->demod ? 1 : 0);
	cmd.args[2] = CX24117_OCC;
	cmd.len = 3;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);
	अगर (ret != 0)
		जाओ निकास;

	/* Set GPIO direction */
	/* Set as output - controls LNB घातer on/off */
	cmd.args[0] = CMD_SET_GPIOसूची;
	cmd.args[1] = 0x30;
	cmd.args[2] = 0x30;
	cmd.len = 3;
	ret = cx24117_cmd_execute_nolock(fe, &cmd);

निकास:
	mutex_unlock(&state->priv->fe_lock);

	वापस ret;
पूर्ण

/*
 * Put device to sleep
 */
अटल पूर्णांक cx24117_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	/* Set sleep mode on */
	cmd.args[0] = CMD_SET_SLEEPMODE;
	cmd.args[1] = (state->demod ? 1 : 0);
	cmd.args[2] = 1;
	cmd.len = 3;
	वापस cx24117_cmd_execute(fe, &cmd);
पूर्ण

/* dvb-core told us to tune, the tv property cache will be complete,
 * it's safe क्रम is to pull values and use them क्रम tuning purposes.
 */
अटल पूर्णांक cx24117_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24117_cmd cmd;
	क्रमागत fe_status tunerstat;
	पूर्णांक i, status, ret, retune = 1;
	u8 reg_clkभाग, reg_rateभाग;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		dev_dbg(&state->priv->i2c->dev, "%s() demod%d DVB-S\n",
			__func__, state->demod);

		/* Only QPSK is supported क्रम DVB-S */
		अगर (c->modulation != QPSK) अणु
			dev_dbg(&state->priv->i2c->dev,
				"%s() demod%d unsupported modulation (%d)\n",
				__func__, state->demod, c->modulation);
			वापस -EINVAL;
		पूर्ण

		/* Pilot करोesn't exist in DVB-S, turn bit off */
		state->dnxt.pilot_val = CX24117_PILOT_OFF;

		/* DVB-S only supports 0.35 */
		state->dnxt.rolloff_val = CX24117_ROLLOFF_035;
		अवरोध;

	हाल SYS_DVBS2:
		dev_dbg(&state->priv->i2c->dev, "%s() demod%d DVB-S2\n",
			__func__, state->demod);

		/*
		 * NBC 8PSK/QPSK with DVB-S is supported क्रम DVB-S2,
		 * but not hardware स्वतः detection
		 */
		अगर (c->modulation != PSK_8 && c->modulation != QPSK) अणु
			dev_dbg(&state->priv->i2c->dev,
				"%s() demod%d unsupported modulation (%d)\n",
				__func__, state->demod, c->modulation);
			वापस -EOPNOTSUPP;
		पूर्ण

		चयन (c->pilot) अणु
		हाल PILOT_AUTO:
			state->dnxt.pilot_val = CX24117_PILOT_AUTO;
			अवरोध;
		हाल PILOT_OFF:
			state->dnxt.pilot_val = CX24117_PILOT_OFF;
			अवरोध;
		हाल PILOT_ON:
			state->dnxt.pilot_val = CX24117_PILOT_ON;
			अवरोध;
		शेष:
			dev_dbg(&state->priv->i2c->dev,
				"%s() demod%d unsupported pilot mode (%d)\n",
				__func__, state->demod, c->pilot);
			वापस -EOPNOTSUPP;
		पूर्ण

		चयन (c->rolloff) अणु
		हाल ROLLOFF_20:
			state->dnxt.rolloff_val = CX24117_ROLLOFF_020;
			अवरोध;
		हाल ROLLOFF_25:
			state->dnxt.rolloff_val = CX24117_ROLLOFF_025;
			अवरोध;
		हाल ROLLOFF_35:
			state->dnxt.rolloff_val = CX24117_ROLLOFF_035;
			अवरोध;
		हाल ROLLOFF_AUTO:
			state->dnxt.rolloff_val = CX24117_ROLLOFF_035;
			/* soft-स्वतः rolloff */
			retune = 3;
			अवरोध;
		शेष:
			dev_warn(&state->priv->i2c->dev,
				"%s: demod%d unsupported rolloff (%d)\n",
				KBUILD_MODNAME, state->demod, c->rolloff);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(&state->priv->i2c->dev,
			"%s: demod %d unsupported delivery system (%d)\n",
			KBUILD_MODNAME, state->demod, c->delivery_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	state->dnxt.delsys = c->delivery_प्रणाली;
	state->dnxt.modulation = c->modulation;
	state->dnxt.frequency = c->frequency;
	state->dnxt.pilot = c->pilot;
	state->dnxt.rolloff = c->rolloff;

	ret = cx24117_set_inversion(state, c->inversion);
	अगर (ret !=  0)
		वापस ret;

	ret = cx24117_set_fec(state,
		c->delivery_प्रणाली, c->modulation, c->fec_inner);
	अगर (ret !=  0)
		वापस ret;

	ret = cx24117_set_symbolrate(state, c->symbol_rate);
	अगर (ret !=  0)
		वापस ret;

	/* discard the 'current' tuning parameters and prepare to tune */
	cx24117_clone_params(fe);

	dev_dbg(&state->priv->i2c->dev,
		"%s: delsys      = %d\n", __func__, state->dcur.delsys);
	dev_dbg(&state->priv->i2c->dev,
		"%s: modulation  = %d\n", __func__, state->dcur.modulation);
	dev_dbg(&state->priv->i2c->dev,
		"%s: frequency   = %d\n", __func__, state->dcur.frequency);
	dev_dbg(&state->priv->i2c->dev,
		"%s: pilot       = %d (val = 0x%02x)\n", __func__,
		state->dcur.pilot, state->dcur.pilot_val);
	dev_dbg(&state->priv->i2c->dev,
		"%s: retune      = %d\n", __func__, retune);
	dev_dbg(&state->priv->i2c->dev,
		"%s: rolloff     = %d (val = 0x%02x)\n", __func__,
		state->dcur.rolloff, state->dcur.rolloff_val);
	dev_dbg(&state->priv->i2c->dev,
		"%s: symbol_rate = %d\n", __func__, state->dcur.symbol_rate);
	dev_dbg(&state->priv->i2c->dev,
		"%s: FEC         = %d (mask/val = 0x%02x/0x%02x)\n", __func__,
		state->dcur.fec, state->dcur.fec_mask, state->dcur.fec_val);
	dev_dbg(&state->priv->i2c->dev,
		"%s: Inversion   = %d (val = 0x%02x)\n", __func__,
		state->dcur.inversion, state->dcur.inversion_val);

	/* Prepare a tune request */
	cmd.args[0] = CMD_TUNEREQUEST;

	/* demod */
	cmd.args[1] = state->demod;

	/* Frequency */
	cmd.args[2] = (state->dcur.frequency & 0xff0000) >> 16;
	cmd.args[3] = (state->dcur.frequency & 0x00ff00) >> 8;
	cmd.args[4] = (state->dcur.frequency & 0x0000ff);

	/* Symbol Rate */
	cmd.args[5] = ((state->dcur.symbol_rate / 1000) & 0xff00) >> 8;
	cmd.args[6] = ((state->dcur.symbol_rate / 1000) & 0x00ff);

	/* Automatic Inversion */
	cmd.args[7] = state->dcur.inversion_val;

	/* Modulation / FEC / Pilot */
	cmd.args[8] = state->dcur.fec_val | state->dcur.pilot_val;

	cmd.args[9] = CX24117_SEARCH_RANGE_KHZ >> 8;
	cmd.args[10] = CX24117_SEARCH_RANGE_KHZ & 0xff;

	cmd.args[11] = state->dcur.rolloff_val;
	cmd.args[12] = state->dcur.fec_mask;

	अगर (state->dcur.symbol_rate > 30000000) अणु
		reg_rateभाग = 0x04;
		reg_clkभाग = 0x02;
	पूर्ण अन्यथा अगर (state->dcur.symbol_rate > 10000000) अणु
		reg_rateभाग = 0x06;
		reg_clkभाग = 0x03;
	पूर्ण अन्यथा अणु
		reg_rateभाग = 0x0a;
		reg_clkभाग = 0x05;
	पूर्ण

	cmd.args[13] = reg_rateभाग;
	cmd.args[14] = reg_clkभाग;

	cx24117_ग_लिखोreg(state, (state->demod == 0) ?
		CX24117_REG_CLKDIV0 : CX24117_REG_CLKDIV1, reg_clkभाग);
	cx24117_ग_लिखोreg(state, (state->demod == 0) ?
		CX24117_REG_RATEDIV0 : CX24117_REG_RATEDIV1, reg_rateभाग);

	cmd.args[15] = CX24117_PNE;
	cmd.len = 16;

	करो अणु
		/* Reset status रेजिस्टर */
		status = cx24117_पढ़ोreg(state, (state->demod == 0) ?
			CX24117_REG_SSTATUS0 : CX24117_REG_SSTATUS1) &
			CX24117_SIGNAL_MASK;

		dev_dbg(&state->priv->i2c->dev,
			"%s() demod%d status_setfe = %02x\n",
			__func__, state->demod, status);

		cx24117_ग_लिखोreg(state, (state->demod == 0) ?
			CX24117_REG_SSTATUS0 : CX24117_REG_SSTATUS1, status);

		/* Tune */
		ret = cx24117_cmd_execute(fe, &cmd);
		अगर (ret != 0)
			अवरोध;

		/*
		 * Wait क्रम up to 500 ms beक्रमe retrying
		 *
		 * If we are able to tune then generally it occurs within 100ms.
		 * If it takes दीर्घer, try a dअगरferent rolloff setting.
		 */
		क्रम (i = 0; i < 50; i++) अणु
			cx24117_पढ़ो_status(fe, &tunerstat);
			status = tunerstat & (FE_HAS_SIGNAL | FE_HAS_SYNC);
			अगर (status == (FE_HAS_SIGNAL | FE_HAS_SYNC)) अणु
				dev_dbg(&state->priv->i2c->dev,
					"%s() demod%d tuned\n",
					__func__, state->demod);
				वापस 0;
			पूर्ण
			msleep(20);
		पूर्ण

		dev_dbg(&state->priv->i2c->dev, "%s() demod%d not tuned\n",
			__func__, state->demod);

		/* try next rolloff value */
		अगर (state->dcur.rolloff == 3)
			cmd.args[11]--;

	पूर्ण जबतक (--retune);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cx24117_tune(काष्ठा dvb_frontend *fe, bool re_tune,
	अचिन्हित पूर्णांक mode_flags, अचिन्हित पूर्णांक *delay, क्रमागत fe_status *status)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;

	dev_dbg(&state->priv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	*delay = HZ / 5;
	अगर (re_tune) अणु
		पूर्णांक ret = cx24117_set_frontend(fe);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cx24117_पढ़ो_status(fe, status);
पूर्ण

अटल क्रमागत dvbfe_algo cx24117_get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल पूर्णांक cx24117_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा cx24117_state *state = fe->demodulator_priv;
	काष्ठा cx24117_cmd cmd;
	u8 reg, st, inv;
	पूर्णांक ret, idx;
	अचिन्हित पूर्णांक freq;
	लघु srate_os, freq_os;

	u8 buf[0x1f-4];

	/* Read current tune parameters */
	cmd.args[0] = CMD_GETCTLACC;
	cmd.args[1] = (u8) state->demod;
	cmd.len = 2;
	ret = cx24117_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	/* पढ़ो all required regs at once */
	reg = (state->demod == 0) ? CX24117_REG_FREQ3_0 : CX24117_REG_FREQ3_1;
	ret = cx24117_पढ़ोregN(state, reg, buf, 0x1f-4);
	अगर (ret != 0)
		वापस ret;

	st = buf[5];

	/* get spectral inversion */
	inv = (((state->demod == 0) ? ~st : st) >> 6) & 1;
	अगर (inv == 0)
		c->inversion = INVERSION_OFF;
	अन्यथा
		c->inversion = INVERSION_ON;

	/* modulation and fec */
	idx = st & 0x3f;
	अगर (c->delivery_प्रणाली == SYS_DVBS2) अणु
		अगर (idx > 11)
			idx += 9;
		अन्यथा
			idx += 7;
	पूर्ण

	c->modulation = cx24117_modfec_modes[idx].modulation;
	c->fec_inner = cx24117_modfec_modes[idx].fec;

	/* frequency */
	freq = (buf[0] << 16) | (buf[1] << 8) | buf[2];
	freq_os = (buf[8] << 8) | buf[9];
	c->frequency = freq + freq_os;

	/* symbol rate */
	srate_os = (buf[10] << 8) | buf[11];
	c->symbol_rate = -1000 * srate_os + state->dcur.symbol_rate;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24117_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name = "Conexant CX24117/CX24132",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.frequency_stepsize_hz = 1011 * kHz,
		.frequency_tolerance_hz = 5 * MHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_2G_MODULATION |
			FE_CAN_QPSK | FE_CAN_RECOVER
	पूर्ण,

	.release = cx24117_release,

	.init = cx24117_initfe,
	.sleep = cx24117_sleep,
	.पढ़ो_status = cx24117_पढ़ो_status,
	.पढ़ो_ber = cx24117_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cx24117_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cx24117_पढ़ो_snr,
	.पढ़ो_ucblocks = cx24117_पढ़ो_ucblocks,
	.set_tone = cx24117_set_tone,
	.set_voltage = cx24117_set_voltage,
	.diseqc_send_master_cmd = cx24117_send_diseqc_msg,
	.diseqc_send_burst = cx24117_diseqc_send_burst,
	.get_frontend_algo = cx24117_get_algo,
	.tune = cx24117_tune,

	.set_frontend = cx24117_set_frontend,
	.get_frontend = cx24117_get_frontend,
पूर्ण;


MODULE_DESCRIPTION("DVB Frontend module for Conexant cx24117/cx24132 hardware");
MODULE_AUTHOR("Luis Alves (ljalvs@gmail.com)");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");
MODULE_FIRMWARE(CX24117_DEFAULT_FIRMWARE);

