<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Conexant cx24116/cx24118 - DVBS/S2 Satellite demod/tuner driver

    Copyright (C) 2006-2008 Steven Toth <stoth@hauppauge.com>
    Copyright (C) 2006-2007 Georg Acher
    Copyright (C) 2007-2008 Darron Broad
	March 2007
	    Fixed some bugs.
	    Added diseqc support.
	    Added corrected संकेत strength support.
	August 2007
	    Sync with legacy version.
	    Some clean ups.
    Copyright (C) 2008 Igor Liplianin
	September, 9th 2008
	    Fixed locking on high symbol rates (>30000).
	    Implement MPEG initialization parameter.
	January, 17th 2009
	    Fill set_voltage with actually control voltage code.
	    Correct set tone to not affect voltage.

*/

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/firmware.h>

#समावेश <media/dvb_frontend.h>
#समावेश "cx24116.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activates frontend debugging (default:0)");

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_INFO "cx24116: " args); \
	पूर्ण जबतक (0)

#घोषणा CX24116_DEFAULT_FIRMWARE "dvb-fe-cx24116.fw"
#घोषणा CX24116_SEARCH_RANGE_KHZ 5000

/* known रेजिस्टरs */
#घोषणा CX24116_REG_COMMAND (0x00)      /* command args 0x00..0x1e */
#घोषणा CX24116_REG_EXECUTE (0x1f)      /* execute command */
#घोषणा CX24116_REG_MAILBOX (0x96)      /* FW or multipurpose mailbox? */
#घोषणा CX24116_REG_RESET   (0x20)      /* reset status > 0     */
#घोषणा CX24116_REG_SIGNAL  (0x9e)      /* संकेत low           */
#घोषणा CX24116_REG_SSTATUS (0x9d)      /* संकेत high / status */
#घोषणा CX24116_REG_QUALITY8 (0xa3)
#घोषणा CX24116_REG_QSTATUS (0xbc)
#घोषणा CX24116_REG_QUALITY0 (0xd5)
#घोषणा CX24116_REG_BER0    (0xc9)
#घोषणा CX24116_REG_BER8    (0xc8)
#घोषणा CX24116_REG_BER16   (0xc7)
#घोषणा CX24116_REG_BER24   (0xc6)
#घोषणा CX24116_REG_UCB0    (0xcb)
#घोषणा CX24116_REG_UCB8    (0xca)
#घोषणा CX24116_REG_CLKDIV  (0xf3)
#घोषणा CX24116_REG_RATEDIV (0xf9)

/* configured fec (not tuned) or actual FEC (tuned) 1=1/2 2=2/3 etc */
#घोषणा CX24116_REG_FECSTATUS (0x9c)

/* FECSTATUS bits */
/* mask to determine configured fec (not tuned) or actual fec (tuned) */
#घोषणा CX24116_FEC_FECMASK   (0x1f)

/* Select DVB-S demodulator, अन्यथा DVB-S2 */
#घोषणा CX24116_FEC_DVBS      (0x20)
#घोषणा CX24116_FEC_UNKNOWN   (0x40)    /* Unknown/unused */

/* Pilot mode requested when tuning अन्यथा always reset when tuned */
#घोषणा CX24116_FEC_PILOT     (0x80)

/* arg buffer size */
#घोषणा CX24116_ARGLEN (0x1e)

/* rolloff */
#घोषणा CX24116_ROLLOFF_020 (0x00)
#घोषणा CX24116_ROLLOFF_025 (0x01)
#घोषणा CX24116_ROLLOFF_035 (0x02)

/* pilot bit */
#घोषणा CX24116_PILOT_OFF (0x00)
#घोषणा CX24116_PILOT_ON (0x40)

/* संकेत status */
#घोषणा CX24116_HAS_SIGNAL   (0x01)
#घोषणा CX24116_HAS_CARRIER  (0x02)
#घोषणा CX24116_HAS_VITERBI  (0x04)
#घोषणा CX24116_HAS_SYNCLOCK (0x08)
#घोषणा CX24116_HAS_UNKNOWN1 (0x10)
#घोषणा CX24116_HAS_UNKNOWN2 (0x20)
#घोषणा CX24116_STATUS_MASK  (0x0f)
#घोषणा CX24116_SIGNAL_MASK  (0xc0)

#घोषणा CX24116_DISEQC_TONखातापूर्णF   (0)    /* toneburst never sent */
#घोषणा CX24116_DISEQC_TONECACHE (1)    /* toneburst cached     */
#घोषणा CX24116_DISEQC_MESGCACHE (2)    /* message cached       */

/* arg offset क्रम DiSEqC */
#घोषणा CX24116_DISEQC_BURST  (1)
#घोषणा CX24116_DISEQC_ARG2_2 (2)   /* unknown value=2 */
#घोषणा CX24116_DISEQC_ARG3_0 (3)   /* unknown value=0 */
#घोषणा CX24116_DISEQC_ARG4_0 (4)   /* unknown value=0 */
#घोषणा CX24116_DISEQC_MSGLEN (5)
#घोषणा CX24116_DISEQC_MSGOFS (6)

/* DiSEqC burst */
#घोषणा CX24116_DISEQC_MINI_A (0)
#घोषणा CX24116_DISEQC_MINI_B (1)

/* DiSEqC tone burst */
अटल पूर्णांक toneburst = 1;
module_param(toneburst, पूर्णांक, 0644);
MODULE_PARM_DESC(toneburst, "DiSEqC toneburst 0=OFF, 1=TONE CACHE, "\
	"2=MESSAGE CACHE (default:1)");

/* SNR measurements */
अटल पूर्णांक esno_snr;
module_param(esno_snr, पूर्णांक, 0644);
MODULE_PARM_DESC(esno_snr, "SNR return units, 0=PERCENTAGE 0-100, "\
	"1=ESNO(db * 10) (default:0)");

क्रमागत cmds अणु
	CMD_SET_VCO     = 0x10,
	CMD_TUNEREQUEST = 0x11,
	CMD_MPEGCONFIG  = 0x13,
	CMD_TUNERINIT   = 0x14,
	CMD_BANDWIDTH   = 0x15,
	CMD_GETAGC      = 0x19,
	CMD_LNBCONFIG   = 0x20,
	CMD_LNBSEND     = 0x21, /* Formerly CMD_SEND_DISEQC */
	CMD_LNBDCLEVEL  = 0x22,
	CMD_SET_TONE    = 0x23,
	CMD_UPDFWVERS   = 0x35,
	CMD_TUNERSLEEP  = 0x36,
	CMD_AGCCONTROL  = 0x3b, /* Unknown */
पूर्ण;

/* The Demod/Tuner can't easily provide these, we cache them */
काष्ठा cx24116_tuning अणु
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
काष्ठा cx24116_cmd अणु
	u8 len;
	u8 args[CX24116_ARGLEN];
पूर्ण;

काष्ठा cx24116_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा cx24116_config *config;

	काष्ठा dvb_frontend frontend;

	काष्ठा cx24116_tuning dcur;
	काष्ठा cx24116_tuning dnxt;

	u8 skip_fw_load;
	u8 burst;
	काष्ठा cx24116_cmd dsec_cmd;
पूर्ण;

अटल पूर्णांक cx24116_ग_लिखोreg(काष्ठा cx24116_state *state, पूर्णांक reg, पूर्णांक data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;
	पूर्णांक err;

	अगर (debug > 1)
		prपूर्णांकk("cx24116: %s: write reg 0x%02x, value 0x%02x\n",
			__func__, reg, data);

	err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		prपूर्णांकk(KERN_ERR "%s: writereg error(err == %i, reg == 0x%02x, value == 0x%02x)\n",
		       __func__, err, reg, data);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Bulk byte ग_लिखोs to a single I2C address, क्रम 32k firmware load */
अटल पूर्णांक cx24116_ग_लिखोregN(काष्ठा cx24116_state *state, पूर्णांक reg,
			     स्थिर u8 *data, u16 len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg;
	u8 *buf;

	buf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	*(buf) = reg;
	स_नकल(buf + 1, data, len);

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = len + 1;

	अगर (debug > 1)
		prपूर्णांकk(KERN_INFO "cx24116: %s:  write regN 0x%02x, len = %d\n",
			__func__, reg, len);

	ret = i2c_transfer(state->i2c, &msg, 1);
	अगर (ret != 1) अणु
		prपूर्णांकk(KERN_ERR "%s: writereg error(err == %i, reg == 0x%02x\n",
			 __func__, ret, reg);
		ret = -EREMOTEIO;
	पूर्ण

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक cx24116_पढ़ोreg(काष्ठा cx24116_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config->demod_address, .flags = 0,
			.buf = b0, .len = 1 पूर्ण,
		अणु .addr = state->config->demod_address, .flags = I2C_M_RD,
			.buf = b1, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		prपूर्णांकk(KERN_ERR "%s: reg=0x%x (error=%d)\n",
			__func__, reg, ret);
		वापस ret;
	पूर्ण

	अगर (debug > 1)
		prपूर्णांकk(KERN_INFO "cx24116: read reg 0x%02x, value 0x%02x\n",
			reg, b1[0]);

	वापस b1[0];
पूर्ण

अटल पूर्णांक cx24116_set_inversion(काष्ठा cx24116_state *state,
	क्रमागत fe_spectral_inversion inversion)
अणु
	dprपूर्णांकk("%s(%d)\n", __func__, inversion);

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

/*
 * modfec (modulation and FEC)
 * ===========================
 *
 * MOD          FEC             mask/val    standard
 * ----         --------        ----------- --------
 * QPSK         FEC_1_2         0x02 0x02+X DVB-S
 * QPSK         FEC_2_3         0x04 0x02+X DVB-S
 * QPSK         FEC_3_4         0x08 0x02+X DVB-S
 * QPSK         FEC_4_5         0x10 0x02+X DVB-S (?)
 * QPSK         FEC_5_6         0x20 0x02+X DVB-S
 * QPSK         FEC_6_7         0x40 0x02+X DVB-S
 * QPSK         FEC_7_8         0x80 0x02+X DVB-S
 * QPSK         FEC_8_9         0x01 0x02+X DVB-S (?) (NOT SUPPORTED?)
 * QPSK         AUTO            0xff 0x02+X DVB-S
 *
 * For DVB-S high byte probably represents FEC
 * and low byte selects the modulator. The high
 * byte is search range mask. Bit 5 may turn
 * on DVB-S and reमुख्यing bits represent some
 * kind of calibration (how/what i करो not know).
 *
 * Eg.(2/3) szap "Zone Horror"
 *
 * mask/val = 0x04, 0x20
 * status 1f | संकेत c3c0 | snr a333 | ber 00000098 | unc 0 | FE_HAS_LOCK
 *
 * mask/val = 0x04, 0x30
 * status 1f | संकेत c3c0 | snr a333 | ber 00000000 | unc 0 | FE_HAS_LOCK
 *
 * After tuning FECSTATUS contains actual FEC
 * in use numbered 1 through to 8 क्रम 1/2 .. 2/3 etc
 *
 * NBC=NOT/NON BACKWARD COMPATIBLE WITH DVB-S (DVB-S2 only)
 *
 * NBC-QPSK     FEC_1_2         0x00, 0x04      DVB-S2
 * NBC-QPSK     FEC_3_5         0x00, 0x05      DVB-S2
 * NBC-QPSK     FEC_2_3         0x00, 0x06      DVB-S2
 * NBC-QPSK     FEC_3_4         0x00, 0x07      DVB-S2
 * NBC-QPSK     FEC_4_5         0x00, 0x08      DVB-S2
 * NBC-QPSK     FEC_5_6         0x00, 0x09      DVB-S2
 * NBC-QPSK     FEC_8_9         0x00, 0x0a      DVB-S2
 * NBC-QPSK     FEC_9_10        0x00, 0x0b      DVB-S2
 *
 * NBC-8PSK     FEC_3_5         0x00, 0x0c      DVB-S2
 * NBC-8PSK     FEC_2_3         0x00, 0x0d      DVB-S2
 * NBC-8PSK     FEC_3_4         0x00, 0x0e      DVB-S2
 * NBC-8PSK     FEC_5_6         0x00, 0x0f      DVB-S2
 * NBC-8PSK     FEC_8_9         0x00, 0x10      DVB-S2
 * NBC-8PSK     FEC_9_10        0x00, 0x11      DVB-S2
 *
 * For DVB-S2 low bytes selects both modulator
 * and FEC. High byte is meaningless here. To
 * set pilot, bit 6 (0x40) is set. When inspecting
 * FECSTATUS bit 7 (0x80) represents the pilot
 * selection whilst not tuned. When tuned, actual FEC
 * in use is found in FECSTATUS as per above. Pilot
 * value is reset.
 */

/* A table of modulation, fec and configuration bytes क्रम the demod.
 * Not all S2 mmodulation schemes are support and not all rates with
 * a scheme are support. Especially, no स्वतः detect when in S2 mode.
 */
अटल काष्ठा cx24116_modfec अणु
	क्रमागत fe_delivery_प्रणाली delivery_प्रणाली;
	क्रमागत fe_modulation modulation;
	क्रमागत fe_code_rate fec;
	u8 mask;	/* In DVBS mode this is used to स्वतःdetect */
	u8 val;		/* Passed to the firmware to indicate mode selection */
पूर्ण CX24116_MODFEC_MODES[] = अणु
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
 अणु SYS_DVBS2, QPSK, FEC_1_2,  0x00, 0x04 पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_3_5,  0x00, 0x05 पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_2_3,  0x00, 0x06 पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_3_4,  0x00, 0x07 पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_4_5,  0x00, 0x08 पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_5_6,  0x00, 0x09 पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_8_9,  0x00, 0x0a पूर्ण,
 अणु SYS_DVBS2, QPSK, FEC_9_10, 0x00, 0x0b पूर्ण,
 /* 8PSK */
 अणु SYS_DVBS2, PSK_8, FEC_3_5,  0x00, 0x0c पूर्ण,
 अणु SYS_DVBS2, PSK_8, FEC_2_3,  0x00, 0x0d पूर्ण,
 अणु SYS_DVBS2, PSK_8, FEC_3_4,  0x00, 0x0e पूर्ण,
 अणु SYS_DVBS2, PSK_8, FEC_5_6,  0x00, 0x0f पूर्ण,
 अणु SYS_DVBS2, PSK_8, FEC_8_9,  0x00, 0x10 पूर्ण,
 अणु SYS_DVBS2, PSK_8, FEC_9_10, 0x00, 0x11 पूर्ण,
 /*
  * `val' can be found in the FECSTATUS रेजिस्टर when tuning.
  * FECSTATUS will give the actual FEC in use अगर tuning was successful.
  */
पूर्ण;

अटल पूर्णांक cx24116_lookup_fecmod(काष्ठा cx24116_state *state,
	क्रमागत fe_delivery_प्रणाली d, क्रमागत fe_modulation m, क्रमागत fe_code_rate f)
अणु
	पूर्णांक i, ret = -EOPNOTSUPP;

	dprपूर्णांकk("%s(0x%02x,0x%02x)\n", __func__, m, f);

	क्रम (i = 0; i < ARRAY_SIZE(CX24116_MODFEC_MODES); i++) अणु
		अगर ((d == CX24116_MODFEC_MODES[i].delivery_प्रणाली) &&
			(m == CX24116_MODFEC_MODES[i].modulation) &&
			(f == CX24116_MODFEC_MODES[i].fec)) अणु
				ret = i;
				अवरोध;
			पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cx24116_set_fec(काष्ठा cx24116_state *state,
			   क्रमागत fe_delivery_प्रणाली delsys,
			   क्रमागत fe_modulation mod,
			   क्रमागत fe_code_rate fec)
अणु
	पूर्णांक ret = 0;

	dprपूर्णांकk("%s(0x%02x,0x%02x)\n", __func__, mod, fec);

	ret = cx24116_lookup_fecmod(state, delsys, mod, fec);

	अगर (ret < 0)
		वापस ret;

	state->dnxt.fec = fec;
	state->dnxt.fec_val = CX24116_MODFEC_MODES[ret].val;
	state->dnxt.fec_mask = CX24116_MODFEC_MODES[ret].mask;
	dprपूर्णांकk("%s() mask/val = 0x%02x/0x%02x\n", __func__,
		state->dnxt.fec_mask, state->dnxt.fec_val);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_set_symbolrate(काष्ठा cx24116_state *state, u32 rate)
अणु
	dprपूर्णांकk("%s(%d)\n", __func__, rate);

	/*  check अगर symbol rate is within limits */
	अगर ((rate > state->frontend.ops.info.symbol_rate_max) ||
	    (rate < state->frontend.ops.info.symbol_rate_min)) अणु
		dprपूर्णांकk("%s() unsupported symbol_rate = %d\n", __func__, rate);
		वापस -EOPNOTSUPP;
	पूर्ण

	state->dnxt.symbol_rate = rate;
	dprपूर्णांकk("%s() symbol_rate = %d\n", __func__, rate);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_load_firmware(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा firmware *fw);

अटल पूर्णांक cx24116_firmware_ondemand(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 0;

	dprपूर्णांकk("%s()\n", __func__);

	अगर (cx24116_पढ़ोreg(state, 0x20) > 0) अणु

		अगर (state->skip_fw_load)
			वापस 0;

		/* Load firmware */
		/* request the firmware, this will block until loaded */
		prपूर्णांकk(KERN_INFO "%s: Waiting for firmware upload (%s)...\n",
			__func__, CX24116_DEFAULT_FIRMWARE);
		ret = request_firmware(&fw, CX24116_DEFAULT_FIRMWARE,
			state->i2c->dev.parent);
		prपूर्णांकk(KERN_INFO "%s: Waiting for firmware upload(2)...\n",
			__func__);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: No firmware uploaded (timeout or file not found?)\n",
			       __func__);
			वापस ret;
		पूर्ण

		/* Make sure we करोn't recurse back through here
		 * during loading */
		state->skip_fw_load = 1;

		ret = cx24116_load_firmware(fe, fw);
		अगर (ret)
			prपूर्णांकk(KERN_ERR "%s: Writing firmware to device failed\n",
				__func__);

		release_firmware(fw);

		prपूर्णांकk(KERN_INFO "%s: Firmware upload %s\n", __func__,
			ret == 0 ? "complete" : "failed");

		/* Ensure firmware is always loaded अगर required */
		state->skip_fw_load = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Take a basic firmware command काष्ठाure, क्रमmat it
 * and क्रमward it क्रम processing
 */
अटल पूर्णांक cx24116_cmd_execute(काष्ठा dvb_frontend *fe, काष्ठा cx24116_cmd *cmd)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	पूर्णांक i, ret;

	dprपूर्णांकk("%s()\n", __func__);

	/* Load the firmware अगर required */
	ret = cx24116_firmware_ondemand(fe);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "%s(): Unable initialise the firmware\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Write the command */
	क्रम (i = 0; i < cmd->len ; i++) अणु
		dprपूर्णांकk("%s: 0x%02x == 0x%02x\n", __func__, i, cmd->args[i]);
		cx24116_ग_लिखोreg(state, i, cmd->args[i]);
	पूर्ण

	/* Start execution and रुको क्रम cmd to terminate */
	cx24116_ग_लिखोreg(state, CX24116_REG_EXECUTE, 0x01);
	जबतक (cx24116_पढ़ोreg(state, CX24116_REG_EXECUTE)) अणु
		msleep(10);
		अगर (i++ > 64) अणु
			/* Aव्योम looping क्रमever अगर the firmware करोes
				not respond */
			prपूर्णांकk(KERN_WARNING "%s() Firmware not responding\n",
				__func__);
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_load_firmware(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	काष्ठा cx24116_cmd cmd;
	पूर्णांक i, ret, len, max, reमुख्यing;
	अचिन्हित अक्षर vers[4];

	dprपूर्णांकk("%s\n", __func__);
	dprपूर्णांकk("Firmware is %zu bytes (%02x %02x .. %02x %02x)\n",
			fw->size,
			fw->data[0],
			fw->data[1],
			fw->data[fw->size-2],
			fw->data[fw->size-1]);

	/* Toggle 88x SRST pin to reset demod */
	अगर (state->config->reset_device)
		state->config->reset_device(fe);

	/* Begin the firmware load process */
	/* Prepare the demod, load the firmware, cleanup after load */

	/* Init PLL */
	cx24116_ग_लिखोreg(state, 0xE5, 0x00);
	cx24116_ग_लिखोreg(state, 0xF1, 0x08);
	cx24116_ग_लिखोreg(state, 0xF2, 0x13);

	/* Start PLL */
	cx24116_ग_लिखोreg(state, 0xe0, 0x03);
	cx24116_ग_लिखोreg(state, 0xe0, 0x00);

	/* Unknown */
	cx24116_ग_लिखोreg(state, CX24116_REG_CLKDIV, 0x46);
	cx24116_ग_लिखोreg(state, CX24116_REG_RATEDIV, 0x00);

	/* Unknown */
	cx24116_ग_लिखोreg(state, 0xF0, 0x03);
	cx24116_ग_लिखोreg(state, 0xF4, 0x81);
	cx24116_ग_लिखोreg(state, 0xF5, 0x00);
	cx24116_ग_लिखोreg(state, 0xF6, 0x00);

	/* Split firmware to the max I2C ग_लिखो len and ग_लिखो.
	 * Writes whole firmware as one ग_लिखो when i2c_wr_max is set to 0. */
	अगर (state->config->i2c_wr_max)
		max = state->config->i2c_wr_max;
	अन्यथा
		max = पूर्णांक_उच्च; /* enough क्रम 32k firmware */

	क्रम (reमुख्यing = fw->size; reमुख्यing > 0; reमुख्यing -= max - 1) अणु
		len = reमुख्यing;
		अगर (len > max - 1)
			len = max - 1;

		cx24116_ग_लिखोregN(state, 0xF7, &fw->data[fw->size - reमुख्यing],
			len);
	पूर्ण

	cx24116_ग_लिखोreg(state, 0xF4, 0x10);
	cx24116_ग_लिखोreg(state, 0xF0, 0x00);
	cx24116_ग_लिखोreg(state, 0xF8, 0x06);

	/* Firmware CMD 10: VCO config */
	cmd.args[0x00] = CMD_SET_VCO;
	cmd.args[0x01] = 0x05;
	cmd.args[0x02] = 0xdc;
	cmd.args[0x03] = 0xda;
	cmd.args[0x04] = 0xae;
	cmd.args[0x05] = 0xaa;
	cmd.args[0x06] = 0x04;
	cmd.args[0x07] = 0x9d;
	cmd.args[0x08] = 0xfc;
	cmd.args[0x09] = 0x06;
	cmd.len = 0x0a;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	cx24116_ग_लिखोreg(state, CX24116_REG_SSTATUS, 0x00);

	/* Firmware CMD 14: Tuner config */
	cmd.args[0x00] = CMD_TUNERINIT;
	cmd.args[0x01] = 0x00;
	cmd.args[0x02] = 0x00;
	cmd.len = 0x03;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	cx24116_ग_लिखोreg(state, 0xe5, 0x00);

	/* Firmware CMD 13: MPEG config */
	cmd.args[0x00] = CMD_MPEGCONFIG;
	cmd.args[0x01] = 0x01;
	cmd.args[0x02] = 0x75;
	cmd.args[0x03] = 0x00;
	अगर (state->config->mpg_clk_pos_pol)
		cmd.args[0x04] = state->config->mpg_clk_pos_pol;
	अन्यथा
		cmd.args[0x04] = 0x02;
	cmd.args[0x05] = 0x00;
	cmd.len = 0x06;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	/* Firmware CMD 35: Get firmware version */
	cmd.args[0x00] = CMD_UPDFWVERS;
	cmd.len = 0x02;
	क्रम (i = 0; i < 4; i++) अणु
		cmd.args[0x01] = i;
		ret = cx24116_cmd_execute(fe, &cmd);
		अगर (ret != 0)
			वापस ret;
		vers[i] = cx24116_पढ़ोreg(state, CX24116_REG_MAILBOX);
	पूर्ण
	prपूर्णांकk(KERN_INFO "%s: FW version %i.%i.%i.%i\n", __func__,
		vers[0], vers[1], vers[2], vers[3]);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;

	पूर्णांक lock = cx24116_पढ़ोreg(state, CX24116_REG_SSTATUS) &
		CX24116_STATUS_MASK;

	dprपूर्णांकk("%s: status = 0x%02x\n", __func__, lock);

	*status = 0;

	अगर (lock & CX24116_HAS_SIGNAL)
		*status |= FE_HAS_SIGNAL;
	अगर (lock & CX24116_HAS_CARRIER)
		*status |= FE_HAS_CARRIER;
	अगर (lock & CX24116_HAS_VITERBI)
		*status |= FE_HAS_VITERBI;
	अगर (lock & CX24116_HAS_SYNCLOCK)
		*status |= FE_HAS_SYNC | FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	*ber =  (cx24116_पढ़ोreg(state, CX24116_REG_BER24) << 24) |
		(cx24116_पढ़ोreg(state, CX24116_REG_BER16) << 16) |
		(cx24116_पढ़ोreg(state, CX24116_REG_BER8)  << 8)  |
		 cx24116_पढ़ोreg(state, CX24116_REG_BER0);

	वापस 0;
पूर्ण

/* TODO Determine function and scale appropriately */
अटल पूर्णांक cx24116_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *संकेत_strength)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	काष्ठा cx24116_cmd cmd;
	पूर्णांक ret;
	u16 sig_पढ़ोing;

	dprपूर्णांकk("%s()\n", __func__);

	/* Firmware CMD 19: Get AGC */
	cmd.args[0x00] = CMD_GETAGC;
	cmd.len = 0x01;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	sig_पढ़ोing =
		(cx24116_पढ़ोreg(state,
			CX24116_REG_SSTATUS) & CX24116_SIGNAL_MASK) |
		(cx24116_पढ़ोreg(state, CX24116_REG_SIGNAL) << 6);
	*संकेत_strength = 0 - sig_पढ़ोing;

	dprपूर्णांकk("%s: raw / cooked = 0x%04x / 0x%04x\n",
		__func__, sig_पढ़ोing, *संकेत_strength);

	वापस 0;
पूर्ण

/* SNR (0..100)% = (sig & 0xf0) * 10 + (sig & 0x0f) * 10 / 16 */
अटल पूर्णांक cx24116_पढ़ो_snr_pct(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	u8 snr_पढ़ोing;
	अटल स्थिर u32 snr_tab[] = अणु /* 10 x Table (rounded up) */
		0x00000, 0x0199A, 0x03333, 0x04ccD, 0x06667,
		0x08000, 0x0999A, 0x0b333, 0x0cccD, 0x0e667,
		0x10000, 0x1199A, 0x13333, 0x14ccD, 0x16667,
		0x18000 पूर्ण;

	dprपूर्णांकk("%s()\n", __func__);

	snr_पढ़ोing = cx24116_पढ़ोreg(state, CX24116_REG_QUALITY0);

	अगर (snr_पढ़ोing >= 0xa0 /* 100% */)
		*snr = 0xffff;
	अन्यथा
		*snr = snr_tab[(snr_पढ़ोing & 0xf0) >> 4] +
			(snr_tab[(snr_पढ़ोing & 0x0f)] >> 4);

	dprपूर्णांकk("%s: raw / cooked = 0x%02x / 0x%04x\n", __func__,
		snr_पढ़ोing, *snr);

	वापस 0;
पूर्ण

/* The reelbox patches show the value in the रेजिस्टरs represents
 * ESNO, from 0->30db (values 0->300). We provide this value by
 * शेष.
 */
अटल पूर्णांक cx24116_पढ़ो_snr_esno(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	*snr = cx24116_पढ़ोreg(state, CX24116_REG_QUALITY8) << 8 |
		cx24116_पढ़ोreg(state, CX24116_REG_QUALITY0);

	dprपूर्णांकk("%s: raw 0x%04x\n", __func__, *snr);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	अगर (esno_snr == 1)
		वापस cx24116_पढ़ो_snr_esno(fe, snr);
	अन्यथा
		वापस cx24116_पढ़ो_snr_pct(fe, snr);
पूर्ण

अटल पूर्णांक cx24116_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	*ucblocks = (cx24116_पढ़ोreg(state, CX24116_REG_UCB8) << 8) |
		cx24116_पढ़ोreg(state, CX24116_REG_UCB0);

	वापस 0;
पूर्ण

/* Overग_लिखो the current tuning params, we are about to tune */
अटल व्योम cx24116_clone_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	state->dcur = state->dnxt;
पूर्ण

/* Wait क्रम LNB */
अटल पूर्णांक cx24116_रुको_क्रम_lnb(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	पूर्णांक i;

	dprपूर्णांकk("%s() qstatus = 0x%02x\n", __func__,
		cx24116_पढ़ोreg(state, CX24116_REG_QSTATUS));

	/* Wait क्रम up to 300 ms */
	क्रम (i = 0; i < 30 ; i++) अणु
		अगर (cx24116_पढ़ोreg(state, CX24116_REG_QSTATUS) & 0x20)
			वापस 0;
		msleep(10);
	पूर्ण

	dprपूर्णांकk("%s(): LNB not ready\n", __func__);

	वापस -ETIMEDOUT; /* -EBUSY ? */
पूर्ण

अटल पूर्णांक cx24116_set_voltage(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx24116_cmd cmd;
	पूर्णांक ret;

	dprपूर्णांकk("%s: %s\n", __func__,
		voltage == SEC_VOLTAGE_13 ? "SEC_VOLTAGE_13" :
		voltage == SEC_VOLTAGE_18 ? "SEC_VOLTAGE_18" : "??");

	/* Wait क्रम LNB पढ़ोy */
	ret = cx24116_रुको_क्रम_lnb(fe);
	अगर (ret != 0)
		वापस ret;

	/* Wait क्रम voltage/min repeat delay */
	msleep(100);

	cmd.args[0x00] = CMD_LNBDCLEVEL;
	cmd.args[0x01] = (voltage == SEC_VOLTAGE_18 ? 0x01 : 0x00);
	cmd.len = 0x02;

	/* Min delay समय beक्रमe DiSEqC send */
	msleep(15);

	वापस cx24116_cmd_execute(fe, &cmd);
पूर्ण

अटल पूर्णांक cx24116_set_tone(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा cx24116_cmd cmd;
	पूर्णांक ret;

	dprपूर्णांकk("%s(%d)\n", __func__, tone);
	अगर ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) अणु
		prपूर्णांकk(KERN_ERR "%s: Invalid, tone=%d\n", __func__, tone);
		वापस -EINVAL;
	पूर्ण

	/* Wait क्रम LNB पढ़ोy */
	ret = cx24116_रुको_क्रम_lnb(fe);
	अगर (ret != 0)
		वापस ret;

	/* Min delay समय after DiSEqC send */
	msleep(15); /* XXX determine is FW करोes this, see send_diseqc/burst */

	/* Now we set the tone */
	cmd.args[0x00] = CMD_SET_TONE;
	cmd.args[0x01] = 0x00;
	cmd.args[0x02] = 0x00;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		dprपूर्णांकk("%s: setting tone on\n", __func__);
		cmd.args[0x03] = 0x01;
		अवरोध;
	हाल SEC_TONE_OFF:
		dprपूर्णांकk("%s: setting tone off\n", __func__);
		cmd.args[0x03] = 0x00;
		अवरोध;
	पूर्ण
	cmd.len = 0x04;

	/* Min delay समय beक्रमe DiSEqC send */
	msleep(15); /* XXX determine is FW करोes this, see send_diseqc/burst */

	वापस cx24116_cmd_execute(fe, &cmd);
पूर्ण

/* Initialise DiSEqC */
अटल पूर्णांक cx24116_diseqc_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	काष्ठा cx24116_cmd cmd;
	पूर्णांक ret;

	/* Firmware CMD 20: LNB/DiSEqC config */
	cmd.args[0x00] = CMD_LNBCONFIG;
	cmd.args[0x01] = 0x00;
	cmd.args[0x02] = 0x10;
	cmd.args[0x03] = 0x00;
	cmd.args[0x04] = 0x8f;
	cmd.args[0x05] = 0x28;
	cmd.args[0x06] = (toneburst == CX24116_DISEQC_TONखातापूर्णF) ? 0x00 : 0x01;
	cmd.args[0x07] = 0x01;
	cmd.len = 0x08;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	/* Prepare a DiSEqC command */
	state->dsec_cmd.args[0x00] = CMD_LNBSEND;

	/* DiSEqC burst */
	state->dsec_cmd.args[CX24116_DISEQC_BURST]  = CX24116_DISEQC_MINI_A;

	/* Unknown */
	state->dsec_cmd.args[CX24116_DISEQC_ARG2_2] = 0x02;
	state->dsec_cmd.args[CX24116_DISEQC_ARG3_0] = 0x00;
	/* Continuation flag? */
	state->dsec_cmd.args[CX24116_DISEQC_ARG4_0] = 0x00;

	/* DiSEqC message length */
	state->dsec_cmd.args[CX24116_DISEQC_MSGLEN] = 0x00;

	/* Command length */
	state->dsec_cmd.len = CX24116_DISEQC_MSGOFS;

	वापस 0;
पूर्ण

/* Send DiSEqC message with derived burst (hack) || previous burst */
अटल पूर्णांक cx24116_send_diseqc_msg(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_diseqc_master_cmd *d)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	पूर्णांक i, ret;

	/* Validate length */
	अगर (d->msg_len > माप(d->msg))
		वापस -EINVAL;

	/* Dump DiSEqC message */
	अगर (debug) अणु
		prपूर्णांकk(KERN_INFO "cx24116: %s(", __func__);
		क्रम (i = 0 ; i < d->msg_len ;) अणु
			prपूर्णांकk(KERN_INFO "0x%02x", d->msg[i]);
			अगर (++i < d->msg_len)
				prपूर्णांकk(KERN_INFO ", ");
		पूर्ण
		prपूर्णांकk(") toneburst=%d\n", toneburst);
	पूर्ण

	/* DiSEqC message */
	क्रम (i = 0; i < d->msg_len; i++)
		state->dsec_cmd.args[CX24116_DISEQC_MSGOFS + i] = d->msg[i];

	/* DiSEqC message length */
	state->dsec_cmd.args[CX24116_DISEQC_MSGLEN] = d->msg_len;

	/* Command length */
	state->dsec_cmd.len = CX24116_DISEQC_MSGOFS +
		state->dsec_cmd.args[CX24116_DISEQC_MSGLEN];

	/* DiSEqC toneburst */
	अगर (toneburst == CX24116_DISEQC_MESGCACHE)
		/* Message is cached */
		वापस 0;

	अन्यथा अगर (toneburst == CX24116_DISEQC_TONखातापूर्णF)
		/* Message is sent without burst */
		state->dsec_cmd.args[CX24116_DISEQC_BURST] = 0;

	अन्यथा अगर (toneburst == CX24116_DISEQC_TONECACHE) अणु
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
			state->dsec_cmd.args[CX24116_DISEQC_BURST] =
				((d->msg[3] & 4) >> 2);
		अगर (debug)
			dprपूर्णांकk("%s burst=%d\n", __func__,
				state->dsec_cmd.args[CX24116_DISEQC_BURST]);
	पूर्ण

	/* Wait क्रम LNB पढ़ोy */
	ret = cx24116_रुको_क्रम_lnb(fe);
	अगर (ret != 0)
		वापस ret;

	/* Wait क्रम voltage/min repeat delay */
	msleep(100);

	/* Command */
	ret = cx24116_cmd_execute(fe, &state->dsec_cmd);
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
	msleep((state->dsec_cmd.args[CX24116_DISEQC_MSGLEN] << 4) +
		((toneburst == CX24116_DISEQC_TONखातापूर्णF) ? 30 : 60));

	वापस 0;
पूर्ण

/* Send DiSEqC burst */
अटल पूर्णांक cx24116_diseqc_send_burst(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	dprपूर्णांकk("%s(%d) toneburst=%d\n", __func__, burst, toneburst);

	/* DiSEqC burst */
	अगर (burst == SEC_MINI_A)
		state->dsec_cmd.args[CX24116_DISEQC_BURST] =
			CX24116_DISEQC_MINI_A;
	अन्यथा अगर (burst == SEC_MINI_B)
		state->dsec_cmd.args[CX24116_DISEQC_BURST] =
			CX24116_DISEQC_MINI_B;
	अन्यथा
		वापस -EINVAL;

	/* DiSEqC toneburst */
	अगर (toneburst != CX24116_DISEQC_MESGCACHE)
		/* Burst is cached */
		वापस 0;

	/* Burst is to be sent with cached message */

	/* Wait क्रम LNB पढ़ोy */
	ret = cx24116_रुको_क्रम_lnb(fe);
	अगर (ret != 0)
		वापस ret;

	/* Wait क्रम voltage/min repeat delay */
	msleep(100);

	/* Command */
	ret = cx24116_cmd_execute(fe, &state->dsec_cmd);
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
	msleep((state->dsec_cmd.args[CX24116_DISEQC_MSGLEN] << 4) + 60);

	वापस 0;
पूर्ण

अटल व्योम cx24116_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	dprपूर्णांकk("%s\n", __func__);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24116_ops;

काष्ठा dvb_frontend *cx24116_attach(स्थिर काष्ठा cx24116_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा cx24116_state *state;
	पूर्णांक ret;

	dprपूर्णांकk("%s\n", __func__);

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is present */
	ret = (cx24116_पढ़ोreg(state, 0xFF) << 8) |
		cx24116_पढ़ोreg(state, 0xFE);
	अगर (ret != 0x0501) अणु
		kमुक्त(state);
		prपूर्णांकk(KERN_INFO "Invalid probe, probably not a CX24116 device\n");
		वापस शून्य;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &cx24116_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(cx24116_attach);

/*
 * Initialise or wake up device
 *
 * Power config will reset and load initial firmware अगर required
 */
अटल पूर्णांक cx24116_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	काष्ठा cx24116_cmd cmd;
	पूर्णांक ret;

	dprपूर्णांकk("%s()\n", __func__);

	/* Power on */
	cx24116_ग_लिखोreg(state, 0xe0, 0);
	cx24116_ग_लिखोreg(state, 0xe1, 0);
	cx24116_ग_लिखोreg(state, 0xea, 0);

	/* Firmware CMD 36: Power config */
	cmd.args[0x00] = CMD_TUNERSLEEP;
	cmd.args[0x01] = 0;
	cmd.len = 0x02;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	ret = cx24116_diseqc_init(fe);
	अगर (ret != 0)
		वापस ret;

	/* HVR-4000 needs this */
	वापस cx24116_set_voltage(fe, SEC_VOLTAGE_13);
पूर्ण

/*
 * Put device to sleep
 */
अटल पूर्णांक cx24116_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	काष्ठा cx24116_cmd cmd;
	पूर्णांक ret;

	dprपूर्णांकk("%s()\n", __func__);

	/* Firmware CMD 36: Power config */
	cmd.args[0x00] = CMD_TUNERSLEEP;
	cmd.args[0x01] = 1;
	cmd.len = 0x02;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	/* Power off (Shutकरोwn घड़ीs) */
	cx24116_ग_लिखोreg(state, 0xea, 0xff);
	cx24116_ग_लिखोreg(state, 0xe1, 1);
	cx24116_ग_लिखोreg(state, 0xe0, 1);

	वापस 0;
पूर्ण

/* dvb-core told us to tune, the tv property cache will be complete,
 * it's safe क्रम is to pull values and use them क्रम tuning purposes.
 */
अटल पूर्णांक cx24116_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24116_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx24116_cmd cmd;
	क्रमागत fe_status tunerstat;
	पूर्णांक i, status, ret, retune = 1;

	dprपूर्णांकk("%s()\n", __func__);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		dprपूर्णांकk("%s: DVB-S delivery system selected\n", __func__);

		/* Only QPSK is supported क्रम DVB-S */
		अगर (c->modulation != QPSK) अणु
			dprपूर्णांकk("%s: unsupported modulation selected (%d)\n",
				__func__, c->modulation);
			वापस -EOPNOTSUPP;
		पूर्ण

		/* Pilot करोesn't exist in DVB-S, turn bit off */
		state->dnxt.pilot_val = CX24116_PILOT_OFF;

		/* DVB-S only supports 0.35 */
		अगर (c->rolloff != ROLLOFF_35) अणु
			dprपूर्णांकk("%s: unsupported rolloff selected (%d)\n",
				__func__, c->rolloff);
			वापस -EOPNOTSUPP;
		पूर्ण
		state->dnxt.rolloff_val = CX24116_ROLLOFF_035;
		अवरोध;

	हाल SYS_DVBS2:
		dprपूर्णांकk("%s: DVB-S2 delivery system selected\n", __func__);

		/*
		 * NBC 8PSK/QPSK with DVB-S is supported क्रम DVB-S2,
		 * but not hardware स्वतः detection
		 */
		अगर (c->modulation != PSK_8 && c->modulation != QPSK) अणु
			dprपूर्णांकk("%s: unsupported modulation selected (%d)\n",
				__func__, c->modulation);
			वापस -EOPNOTSUPP;
		पूर्ण

		चयन (c->pilot) अणु
		हाल PILOT_AUTO:	/* Not supported but emulated */
			state->dnxt.pilot_val = (c->modulation == QPSK)
				? CX24116_PILOT_OFF : CX24116_PILOT_ON;
			retune++;
			अवरोध;
		हाल PILOT_OFF:
			state->dnxt.pilot_val = CX24116_PILOT_OFF;
			अवरोध;
		हाल PILOT_ON:
			state->dnxt.pilot_val = CX24116_PILOT_ON;
			अवरोध;
		शेष:
			dprपूर्णांकk("%s: unsupported pilot mode selected (%d)\n",
				__func__, c->pilot);
			वापस -EOPNOTSUPP;
		पूर्ण

		चयन (c->rolloff) अणु
		हाल ROLLOFF_20:
			state->dnxt.rolloff_val = CX24116_ROLLOFF_020;
			अवरोध;
		हाल ROLLOFF_25:
			state->dnxt.rolloff_val = CX24116_ROLLOFF_025;
			अवरोध;
		हाल ROLLOFF_35:
			state->dnxt.rolloff_val = CX24116_ROLLOFF_035;
			अवरोध;
		हाल ROLLOFF_AUTO:	/* Rolloff must be explicit */
		शेष:
			dprपूर्णांकk("%s: unsupported rolloff selected (%d)\n",
				__func__, c->rolloff);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		dprपूर्णांकk("%s: unsupported delivery system selected (%d)\n",
			__func__, c->delivery_प्रणाली);
		वापस -EOPNOTSUPP;
	पूर्ण
	state->dnxt.delsys = c->delivery_प्रणाली;
	state->dnxt.modulation = c->modulation;
	state->dnxt.frequency = c->frequency;
	state->dnxt.pilot = c->pilot;
	state->dnxt.rolloff = c->rolloff;

	ret = cx24116_set_inversion(state, c->inversion);
	अगर (ret !=  0)
		वापस ret;

	/* FEC_NONE/AUTO क्रम DVB-S2 is not supported and detected here */
	ret = cx24116_set_fec(state, c->delivery_प्रणाली, c->modulation, c->fec_inner);
	अगर (ret !=  0)
		वापस ret;

	ret = cx24116_set_symbolrate(state, c->symbol_rate);
	अगर (ret !=  0)
		वापस ret;

	/* discard the 'current' tuning parameters and prepare to tune */
	cx24116_clone_params(fe);

	dprपूर्णांकk("%s:   delsys      = %d\n", __func__, state->dcur.delsys);
	dprपूर्णांकk("%s:   modulation  = %d\n", __func__, state->dcur.modulation);
	dprपूर्णांकk("%s:   frequency   = %d\n", __func__, state->dcur.frequency);
	dprपूर्णांकk("%s:   pilot       = %d (val = 0x%02x)\n", __func__,
		state->dcur.pilot, state->dcur.pilot_val);
	dprपूर्णांकk("%s:   retune      = %d\n", __func__, retune);
	dprपूर्णांकk("%s:   rolloff     = %d (val = 0x%02x)\n", __func__,
		state->dcur.rolloff, state->dcur.rolloff_val);
	dprपूर्णांकk("%s:   symbol_rate = %d\n", __func__, state->dcur.symbol_rate);
	dprपूर्णांकk("%s:   FEC         = %d (mask/val = 0x%02x/0x%02x)\n", __func__,
		state->dcur.fec, state->dcur.fec_mask, state->dcur.fec_val);
	dprपूर्णांकk("%s:   Inversion   = %d (val = 0x%02x)\n", __func__,
		state->dcur.inversion, state->dcur.inversion_val);

	/* This is also करोne in advise/acquire on HVR4000 but not on LITE */
	अगर (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);

	/* Set/Reset B/W */
	cmd.args[0x00] = CMD_BANDWIDTH;
	cmd.args[0x01] = 0x01;
	cmd.len = 0x02;
	ret = cx24116_cmd_execute(fe, &cmd);
	अगर (ret != 0)
		वापस ret;

	/* Prepare a tune request */
	cmd.args[0x00] = CMD_TUNEREQUEST;

	/* Frequency */
	cmd.args[0x01] = (state->dcur.frequency & 0xff0000) >> 16;
	cmd.args[0x02] = (state->dcur.frequency & 0x00ff00) >> 8;
	cmd.args[0x03] = (state->dcur.frequency & 0x0000ff);

	/* Symbol Rate */
	cmd.args[0x04] = ((state->dcur.symbol_rate / 1000) & 0xff00) >> 8;
	cmd.args[0x05] = ((state->dcur.symbol_rate / 1000) & 0x00ff);

	/* Automatic Inversion */
	cmd.args[0x06] = state->dcur.inversion_val;

	/* Modulation / FEC / Pilot */
	cmd.args[0x07] = state->dcur.fec_val | state->dcur.pilot_val;

	cmd.args[0x08] = CX24116_SEARCH_RANGE_KHZ >> 8;
	cmd.args[0x09] = CX24116_SEARCH_RANGE_KHZ & 0xff;
	cmd.args[0x0a] = 0x00;
	cmd.args[0x0b] = 0x00;
	cmd.args[0x0c] = state->dcur.rolloff_val;
	cmd.args[0x0d] = state->dcur.fec_mask;

	अगर (state->dcur.symbol_rate > 30000000) अणु
		cmd.args[0x0e] = 0x04;
		cmd.args[0x0f] = 0x00;
		cmd.args[0x10] = 0x01;
		cmd.args[0x11] = 0x77;
		cmd.args[0x12] = 0x36;
		cx24116_ग_लिखोreg(state, CX24116_REG_CLKDIV, 0x44);
		cx24116_ग_लिखोreg(state, CX24116_REG_RATEDIV, 0x01);
	पूर्ण अन्यथा अणु
		cmd.args[0x0e] = 0x06;
		cmd.args[0x0f] = 0x00;
		cmd.args[0x10] = 0x00;
		cmd.args[0x11] = 0xFA;
		cmd.args[0x12] = 0x24;
		cx24116_ग_लिखोreg(state, CX24116_REG_CLKDIV, 0x46);
		cx24116_ग_लिखोreg(state, CX24116_REG_RATEDIV, 0x00);
	पूर्ण

	cmd.len = 0x13;

	/* We need to support pilot and non-pilot tuning in the
	 * driver स्वतःmatically. This is a workaround क्रम because
	 * the demod करोes not support स्वतःdetect.
	 */
	करो अणु
		/* Reset status रेजिस्टर */
		status = cx24116_पढ़ोreg(state, CX24116_REG_SSTATUS)
			& CX24116_SIGNAL_MASK;
		cx24116_ग_लिखोreg(state, CX24116_REG_SSTATUS, status);

		/* Tune */
		ret = cx24116_cmd_execute(fe, &cmd);
		अगर (ret != 0)
			अवरोध;

		/*
		 * Wait क्रम up to 500 ms beक्रमe retrying
		 *
		 * If we are able to tune then generally it occurs within 100ms.
		 * If it takes दीर्घer, try a dअगरferent toneburst setting.
		 */
		क्रम (i = 0; i < 50 ; i++) अणु
			cx24116_पढ़ो_status(fe, &tunerstat);
			status = tunerstat & (FE_HAS_SIGNAL | FE_HAS_SYNC);
			अगर (status == (FE_HAS_SIGNAL | FE_HAS_SYNC)) अणु
				dprपूर्णांकk("%s: Tuned\n", __func__);
				जाओ tuned;
			पूर्ण
			msleep(10);
		पूर्ण

		dprपूर्णांकk("%s: Not tuned\n", __func__);

		/* Toggle pilot bit when in स्वतः-pilot */
		अगर (state->dcur.pilot == PILOT_AUTO)
			cmd.args[0x07] ^= CX24116_PILOT_ON;
	पूर्ण जबतक (--retune);

tuned:  /* Set/Reset B/W */
	cmd.args[0x00] = CMD_BANDWIDTH;
	cmd.args[0x01] = 0x00;
	cmd.len = 0x02;
	वापस cx24116_cmd_execute(fe, &cmd);
पूर्ण

अटल पूर्णांक cx24116_tune(काष्ठा dvb_frontend *fe, bool re_tune,
	अचिन्हित पूर्णांक mode_flags, अचिन्हित पूर्णांक *delay, क्रमागत fe_status *status)
अणु
	/*
	 * It is safe to discard "params" here, as the DVB core will sync
	 * fe->dtv_property_cache with fepriv->parameters_in, where the
	 * DVBv3 params are stored. The only practical usage क्रम it indicate
	 * that re-tuning is needed, e. g. (fepriv->state & FESTATE_RETUNE) is
	 * true.
	 */

	*delay = HZ / 5;
	अगर (re_tune) अणु
		पूर्णांक ret = cx24116_set_frontend(fe);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cx24116_पढ़ो_status(fe, status);
पूर्ण

अटल क्रमागत dvbfe_algo cx24116_get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cx24116_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name = "Conexant CX24116/CX24118",
		.frequency_min_hz = 950 * MHz,
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

	.release = cx24116_release,

	.init = cx24116_initfe,
	.sleep = cx24116_sleep,
	.पढ़ो_status = cx24116_पढ़ो_status,
	.पढ़ो_ber = cx24116_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cx24116_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cx24116_पढ़ो_snr,
	.पढ़ो_ucblocks = cx24116_पढ़ो_ucblocks,
	.set_tone = cx24116_set_tone,
	.set_voltage = cx24116_set_voltage,
	.diseqc_send_master_cmd = cx24116_send_diseqc_msg,
	.diseqc_send_burst = cx24116_diseqc_send_burst,
	.get_frontend_algo = cx24116_get_algo,
	.tune = cx24116_tune,

	.set_frontend = cx24116_set_frontend,
पूर्ण;

MODULE_DESCRIPTION("DVB Frontend module for Conexant cx24116/cx24118 hardware");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");

