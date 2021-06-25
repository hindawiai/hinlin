<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* DVB compliant Linux driver क्रम the DVB-S si2109/2110 demodulator
*
* Copyright (C) 2008 Igor M. Liplianin (liplianin@me.by)
*/
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "si21xx.h"

#घोषणा	REVISION_REG			0x00
#घोषणा	SYSTEM_MODE_REG			0x01
#घोषणा	TS_CTRL_REG_1			0x02
#घोषणा	TS_CTRL_REG_2			0x03
#घोषणा	PIN_CTRL_REG_1			0x04
#घोषणा	PIN_CTRL_REG_2			0x05
#घोषणा	LOCK_STATUS_REG_1		0x0f
#घोषणा	LOCK_STATUS_REG_2		0x10
#घोषणा	ACQ_STATUS_REG			0x11
#घोषणा	ACQ_CTRL_REG_1			0x13
#घोषणा	ACQ_CTRL_REG_2			0x14
#घोषणा	PLL_DIVISOR_REG			0x15
#घोषणा	COARSE_TUNE_REG			0x16
#घोषणा	FINE_TUNE_REG_L			0x17
#घोषणा	FINE_TUNE_REG_H			0x18

#घोषणा	ANALOG_AGC_POWER_LEVEL_REG	0x28
#घोषणा	CFO_ESTIMATOR_CTRL_REG_1	0x29
#घोषणा	CFO_ESTIMATOR_CTRL_REG_2	0x2a
#घोषणा	CFO_ESTIMATOR_CTRL_REG_3	0x2b

#घोषणा	SYM_RATE_ESTIMATE_REG_L		0x31
#घोषणा	SYM_RATE_ESTIMATE_REG_M		0x32
#घोषणा	SYM_RATE_ESTIMATE_REG_H		0x33

#घोषणा	CFO_ESTIMATOR_OFFSET_REG_L	0x36
#घोषणा	CFO_ESTIMATOR_OFFSET_REG_H	0x37
#घोषणा	CFO_ERROR_REG_L			0x38
#घोषणा	CFO_ERROR_REG_H			0x39
#घोषणा	SYM_RATE_ESTIMATOR_CTRL_REG	0x3a

#घोषणा	SYM_RATE_REG_L			0x3f
#घोषणा	SYM_RATE_REG_M			0x40
#घोषणा	SYM_RATE_REG_H			0x41
#घोषणा	SYM_RATE_ESTIMATOR_MAXIMUM_REG	0x42
#घोषणा	SYM_RATE_ESTIMATOR_MINIMUM_REG	0x43

#घोषणा	C_N_ESTIMATOR_CTRL_REG		0x7c
#घोषणा	C_N_ESTIMATOR_THRSHLD_REG	0x7d
#घोषणा	C_N_ESTIMATOR_LEVEL_REG_L	0x7e
#घोषणा	C_N_ESTIMATOR_LEVEL_REG_H	0x7f

#घोषणा	BLIND_SCAN_CTRL_REG		0x80

#घोषणा	LSA_CTRL_REG_1			0x8D
#घोषणा	SPCTRM_TILT_CORR_THRSHLD_REG	0x8f
#घोषणा	ONE_DB_BNDWDTH_THRSHLD_REG	0x90
#घोषणा	TWO_DB_BNDWDTH_THRSHLD_REG	0x91
#घोषणा	THREE_DB_BNDWDTH_THRSHLD_REG	0x92
#घोषणा	INBAND_POWER_THRSHLD_REG	0x93
#घोषणा	REF_NOISE_LVL_MRGN_THRSHLD_REG	0x94

#घोषणा	VIT_SRCH_CTRL_REG_1		0xa0
#घोषणा	VIT_SRCH_CTRL_REG_2		0xa1
#घोषणा	VIT_SRCH_CTRL_REG_3		0xa2
#घोषणा	VIT_SRCH_STATUS_REG		0xa3
#घोषणा	VITERBI_BER_COUNT_REG_L		0xab
#घोषणा	REED_SOLOMON_CTRL_REG		0xb0
#घोषणा	REED_SOLOMON_ERROR_COUNT_REG_L	0xb1
#घोषणा	PRBS_CTRL_REG			0xb5

#घोषणा	LNB_CTRL_REG_1			0xc0
#घोषणा	LNB_CTRL_REG_2			0xc1
#घोषणा	LNB_CTRL_REG_3			0xc2
#घोषणा	LNB_CTRL_REG_4			0xc3
#घोषणा	LNB_CTRL_STATUS_REG		0xc4
#घोषणा	LNB_FIFO_REGS_0			0xc5
#घोषणा	LNB_FIFO_REGS_1			0xc6
#घोषणा	LNB_FIFO_REGS_2			0xc7
#घोषणा	LNB_FIFO_REGS_3			0xc8
#घोषणा	LNB_FIFO_REGS_4			0xc9
#घोषणा	LNB_FIFO_REGS_5			0xca
#घोषणा	LNB_SUPPLY_CTRL_REG_1		0xcb
#घोषणा	LNB_SUPPLY_CTRL_REG_2		0xcc
#घोषणा	LNB_SUPPLY_CTRL_REG_3		0xcd
#घोषणा	LNB_SUPPLY_CTRL_REG_4		0xce
#घोषणा	LNB_SUPPLY_STATUS_REG		0xcf

#घोषणा FAIL	-1
#घोषणा PASS	0

#घोषणा ALLOWABLE_FS_COUNT	10
#घोषणा STATUS_BER		0
#घोषणा STATUS_UCBLOCKS		1

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "si21xx: " args); \
	पूर्ण जबतक (0)

क्रमागत अणु
	ACTIVE_HIGH,
	ACTIVE_LOW
पूर्ण;
क्रमागत अणु
	BYTE_WIDE,
	BIT_WIDE
पूर्ण;
क्रमागत अणु
	CLK_GAPPED_MODE,
	CLK_CONTINUOUS_MODE
पूर्ण;
क्रमागत अणु
	RISING_EDGE,
	FALLING_EDGE
पूर्ण;
क्रमागत अणु
	MSB_FIRST,
	LSB_FIRST
पूर्ण;
क्रमागत अणु
	SERIAL,
	PARALLEL
पूर्ण;

काष्ठा si21xx_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा si21xx_config *config;
	काष्ठा dvb_frontend frontend;
	u8 initialised:1;
	पूर्णांक errmode;
	पूर्णांक fs;			/*Sampling rate of the ADC in MHz*/
पूर्ण;

/*	रेजिस्टर शेष initialization */
अटल u8 serit_sp1511lhb_inittab[] = अणु
	0x01, 0x28,	/* set i2c_inc_disable */
	0x20, 0x03,
	0x27, 0x20,
	0xe0, 0x45,
	0xe1, 0x08,
	0xfe, 0x01,
	0x01, 0x28,
	0x89, 0x09,
	0x04, 0x80,
	0x05, 0x01,
	0x06, 0x00,
	0x20, 0x03,
	0x24, 0x88,
	0x29, 0x09,
	0x2a, 0x0f,
	0x2c, 0x10,
	0x2d, 0x19,
	0x2e, 0x08,
	0x2f, 0x10,
	0x30, 0x19,
	0x34, 0x20,
	0x35, 0x03,
	0x45, 0x02,
	0x46, 0x45,
	0x47, 0xd0,
	0x48, 0x00,
	0x49, 0x40,
	0x4a, 0x03,
	0x4c, 0xfd,
	0x4f, 0x2e,
	0x50, 0x2e,
	0x51, 0x10,
	0x52, 0x10,
	0x56, 0x92,
	0x59, 0x00,
	0x5a, 0x2d,
	0x5b, 0x33,
	0x5c, 0x1f,
	0x5f, 0x76,
	0x62, 0xc0,
	0x63, 0xc0,
	0x64, 0xf3,
	0x65, 0xf3,
	0x79, 0x40,
	0x6a, 0x40,
	0x6b, 0x0a,
	0x6c, 0x80,
	0x6d, 0x27,
	0x71, 0x06,
	0x75, 0x60,
	0x78, 0x00,
	0x79, 0xb5,
	0x7c, 0x05,
	0x7d, 0x1a,
	0x87, 0x55,
	0x88, 0x72,
	0x8f, 0x08,
	0x90, 0xe0,
	0x94, 0x40,
	0xa0, 0x3f,
	0xa1, 0xc0,
	0xa4, 0xcc,
	0xa5, 0x66,
	0xa6, 0x66,
	0xa7, 0x7b,
	0xa8, 0x7b,
	0xa9, 0x7b,
	0xaa, 0x9a,
	0xed, 0x04,
	0xad, 0x00,
	0xae, 0x03,
	0xcc, 0xab,
	0x01, 0x08,
	0xff, 0xff
पूर्ण;

/*	low level पढ़ो/ग_लिखोs */
अटल पूर्णांक si21_ग_लिखोregs(काष्ठा si21xx_state *state, u8 reg1,
							u8 *data, पूर्णांक len)
अणु
	पूर्णांक ret;
	u8 buf[60];/* = अणु reg1, data पूर्ण;*/
	काष्ठा i2c_msg msg = अणु
				.addr = state->config->demod_address,
				.flags = 0,
				.buf = buf,
				.len = len + 1
	पूर्ण;

	अगर (len > माप(buf) - 1)
		वापस -EINVAL;

	msg.buf[0] =  reg1;
	स_नकल(msg.buf + 1, data, len);

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: writereg error (reg1 == 0x%02x, data == 0x%02x, ret == %i)\n",
			__func__, reg1, data[0], ret);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक si21_ग_लिखोreg(काष्ठा si21xx_state *state, u8 reg, u8 data)
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
		dprपूर्णांकk("%s: writereg error (reg == 0x%02x, data == 0x%02x, ret == %i)\n",
			__func__, reg, data, ret);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक si21_ग_लिखो(काष्ठा dvb_frontend *fe, स्थिर u8 buf[], पूर्णांक len)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	अगर (len != 2)
		वापस -EINVAL;

	वापस si21_ग_लिखोreg(state, buf[0], buf[1]);
पूर्ण

अटल u8 si21_पढ़ोreg(काष्ठा si21xx_state *state, u8 reg)
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

अटल पूर्णांक si21_पढ़ोregs(काष्ठा si21xx_state *state, u8 reg1, u8 *b, u8 len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->demod_address,
			.flags = 0,
			.buf = &reg1,
			.len = 1
		पूर्ण, अणु
			.addr = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf = b,
			.len = len
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		dprपूर्णांकk("%s: readreg error (ret == %i)\n", __func__, ret);

	वापस ret == 2 ? 0 : -1;
पूर्ण

अटल पूर्णांक si21xx_रुको_diseqc_idle(काष्ठा si21xx_state *state, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	dprपूर्णांकk("%s\n", __func__);

	जबतक ((si21_पढ़ोreg(state, LNB_CTRL_REG_1) & 0x8) == 8) अणु
		अगर (jअगरfies - start > समयout) अणु
			dprपूर्णांकk("%s: timeout!!\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si21xx_set_symbolrate(काष्ठा dvb_frontend *fe, u32 srate)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u32 sym_rate, data_rate;
	पूर्णांक i;
	u8 sym_rate_bytes[3];

	dprपूर्णांकk("%s : srate = %i\n", __func__ , srate);

	अगर ((srate < 1000000) || (srate > 45000000))
		वापस -EINVAL;

	data_rate = srate;
	sym_rate = 0;

	क्रम (i = 0; i < 4; ++i) अणु
		sym_rate /= 100;
		sym_rate = sym_rate + ((data_rate % 100) * 0x800000) /
								state->fs;
		data_rate /= 100;
	पूर्ण
	क्रम (i = 0; i < 3; ++i)
		sym_rate_bytes[i] = (u8)((sym_rate >> (i * 8)) & 0xff);

	si21_ग_लिखोregs(state, SYM_RATE_REG_L, sym_rate_bytes, 0x03);

	वापस 0;
पूर्ण

अटल पूर्णांक si21xx_send_diseqc_msg(काष्ठा dvb_frontend *fe,
					काष्ठा dvb_diseqc_master_cmd *m)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u8 lnb_status;
	u8 LNB_CTRL_1;
	पूर्णांक status;

	dprपूर्णांकk("%s\n", __func__);

	status = PASS;
	LNB_CTRL_1 = 0;

	status |= si21_पढ़ोregs(state, LNB_CTRL_STATUS_REG, &lnb_status, 0x01);
	status |= si21_पढ़ोregs(state, LNB_CTRL_REG_1, &lnb_status, 0x01);

	/*fill the FIFO*/
	status |= si21_ग_लिखोregs(state, LNB_FIFO_REGS_0, m->msg, m->msg_len);

	LNB_CTRL_1 = (lnb_status & 0x70);
	LNB_CTRL_1 |= m->msg_len;

	LNB_CTRL_1 |= 0x80;	/* begin LNB संकेतing */

	status |= si21_ग_लिखोregs(state, LNB_CTRL_REG_1, &LNB_CTRL_1, 0x01);

	वापस status;
पूर्ण

अटल पूर्णांक si21xx_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk("%s\n", __func__);

	अगर (si21xx_रुको_diseqc_idle(state, 100) < 0)
		वापस -ETIMEDOUT;

	val = (0x80 | si21_पढ़ोreg(state, 0xc1));
	अगर (si21_ग_लिखोreg(state, LNB_CTRL_REG_1,
			burst == SEC_MINI_A ? (val & ~0x10) : (val | 0x10)))
		वापस -EREMOTEIO;

	अगर (si21xx_रुको_diseqc_idle(state, 100) < 0)
		वापस -ETIMEDOUT;

	अगर (si21_ग_लिखोreg(state, LNB_CTRL_REG_1, val))
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण
/*	30.06.2008 */
अटल पूर्णांक si21xx_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk("%s\n", __func__);
	val = (0x80 | si21_पढ़ोreg(state, LNB_CTRL_REG_1));

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		वापस si21_ग_लिखोreg(state, LNB_CTRL_REG_1, val | 0x20);

	हाल SEC_TONE_OFF:
		वापस si21_ग_लिखोreg(state, LNB_CTRL_REG_1, (val & ~0x20));

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si21xx_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage volt)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	u8 val;
	dprपूर्णांकk("%s: %s\n", __func__,
		volt == SEC_VOLTAGE_13 ? "SEC_VOLTAGE_13" :
		volt == SEC_VOLTAGE_18 ? "SEC_VOLTAGE_18" : "??");


	val = (0x80 | si21_पढ़ोreg(state, LNB_CTRL_REG_1));

	चयन (volt) अणु
	हाल SEC_VOLTAGE_18:
		वापस si21_ग_लिखोreg(state, LNB_CTRL_REG_1, val | 0x40);
	हाल SEC_VOLTAGE_13:
		वापस si21_ग_लिखोreg(state, LNB_CTRL_REG_1, (val & ~0x40));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si21xx_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	पूर्णांक i;
	पूर्णांक status = 0;
	u8 reg1;
	u8 val;
	u8 reg2[2];

	dprपूर्णांकk("%s\n", __func__);

	क्रम (i = 0; ; i += 2) अणु
		reg1 = serit_sp1511lhb_inittab[i];
		val = serit_sp1511lhb_inittab[i+1];
		अगर (reg1 == 0xff && val == 0xff)
			अवरोध;
		si21_ग_लिखोregs(state, reg1, &val, 1);
	पूर्ण

	/*DVB QPSK SYSTEM MODE REG*/
	reg1 = 0x08;
	si21_ग_लिखोregs(state, SYSTEM_MODE_REG, &reg1, 0x01);

	/*transport stream config*/
	/*
	mode = PARALLEL;
	sdata_क्रमm = LSB_FIRST;
	clk_edge = FALLING_EDGE;
	clk_mode = CLK_GAPPED_MODE;
	strt_len = BYTE_WIDE;
	sync_pol = ACTIVE_HIGH;
	val_pol = ACTIVE_HIGH;
	err_pol = ACTIVE_HIGH;
	sclk_rate = 0x00;
	parity = 0x00 ;
	data_delay = 0x00;
	clk_delay = 0x00;
	pclk_smooth = 0x00;
	*/
	reg2[0] =
		PARALLEL + (LSB_FIRST << 1)
		+ (FALLING_EDGE << 2) + (CLK_GAPPED_MODE << 3)
		+ (BYTE_WIDE << 4) + (ACTIVE_HIGH << 5)
		+ (ACTIVE_HIGH << 6) + (ACTIVE_HIGH << 7);

	reg2[1] = 0;
	/*	sclk_rate + (parity << 2)
		+ (data_delay << 3) + (clk_delay << 4)
		+ (pclk_smooth << 5);
	*/
	status |= si21_ग_लिखोregs(state, TS_CTRL_REG_1, reg2, 0x02);
	अगर (status != 0)
		dprपूर्णांकk(" %s : TS Set Error\n", __func__);

	वापस 0;

पूर्ण

अटल पूर्णांक si21_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u8 regs_पढ़ो[2];
	u8 reg_पढ़ो;
	u8 i;
	u8 lock;
	u8 संकेत = si21_पढ़ोreg(state, ANALOG_AGC_POWER_LEVEL_REG);

	si21_पढ़ोregs(state, LOCK_STATUS_REG_1, regs_पढ़ो, 0x02);
	reg_पढ़ो = 0;

	क्रम (i = 0; i < 7; ++i)
		reg_पढ़ो |= ((regs_पढ़ो[0] >> i) & 0x01) << (6 - i);

	lock = ((reg_पढ़ो & 0x7f) | (regs_पढ़ो[1] & 0x80));

	dprपूर्णांकk("%s : FE_READ_STATUS : VSTATUS: 0x%02x\n", __func__, lock);
	*status = 0;

	अगर (संकेत > 10)
		*status |= FE_HAS_SIGNAL;

	अगर (lock & 0x2)
		*status |= FE_HAS_CARRIER;

	अगर (lock & 0x20)
		*status |= FE_HAS_VITERBI;

	अगर (lock & 0x40)
		*status |= FE_HAS_SYNC;

	अगर ((lock & 0x7b) == 0x7b)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक si21_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	/*status = si21_पढ़ोreg(state, ANALOG_AGC_POWER_LEVEL_REG,
						(u8*)agclevel, 0x01);*/

	u16 संकेत = (3 * si21_पढ़ोreg(state, 0x27) *
					si21_पढ़ोreg(state, 0x28));

	dprपूर्णांकk("%s : AGCPWR: 0x%02x%02x, signal=0x%04x\n", __func__,
		si21_पढ़ोreg(state, 0x27),
		si21_पढ़ोreg(state, 0x28), (पूर्णांक) संकेत);

	संकेत  <<= 4;
	*strength = संकेत;

	वापस 0;
पूर्ण

अटल पूर्णांक si21_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (state->errmode != STATUS_BER)
		वापस 0;

	*ber = (si21_पढ़ोreg(state, 0x1d) << 8) |
				si21_पढ़ोreg(state, 0x1e);

	वापस 0;
पूर्ण

अटल पूर्णांक si21_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	s32 xsnr = 0xffff - ((si21_पढ़ोreg(state, 0x24) << 8) |
					si21_पढ़ोreg(state, 0x25));
	xsnr = 3 * (xsnr - 0xa100);
	*snr = (xsnr > 0xffff) ? 0xffff : (xsnr < 0) ? 0 : xsnr;

	dprपूर्णांकk("%s\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक si21_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (state->errmode != STATUS_UCBLOCKS)
		*ucblocks = 0;
	अन्यथा
		*ucblocks = (si21_पढ़ोreg(state, 0x1d) << 8) |
					si21_पढ़ोreg(state, 0x1e);

	वापस 0;
पूर्ण

/*	initiates a channel acquisition sequence
	using the specअगरied symbol rate and code rate */
अटल पूर्णांक si21xx_setacquire(काष्ठा dvb_frontend *fe, पूर्णांक symbrate,
			     क्रमागत fe_code_rate crate)
अणु

	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u8 coderates[] = अणु
				0x0, 0x01, 0x02, 0x04, 0x00,
				0x8, 0x10, 0x20, 0x00, 0x3f
	पूर्ण;

	u8 coderate_ptr;
	पूर्णांक status;
	u8 start_acq = 0x80;
	u8 reg, regs[3];

	dprपूर्णांकk("%s\n", __func__);

	status = PASS;
	coderate_ptr = coderates[crate];

	si21xx_set_symbolrate(fe, symbrate);

	/* ग_लिखो code rates to use in the Viterbi search */
	status |= si21_ग_लिखोregs(state,
				VIT_SRCH_CTRL_REG_1,
				&coderate_ptr, 0x01);

	/* clear acq_start bit */
	status |= si21_पढ़ोregs(state, ACQ_CTRL_REG_2, &reg, 0x01);
	reg &= ~start_acq;
	status |= si21_ग_लिखोregs(state, ACQ_CTRL_REG_2, &reg, 0x01);

	/* use new Carrier Frequency Offset Estimator (QuickLock) */
	regs[0] = 0xCB;
	regs[1] = 0x40;
	regs[2] = 0xCB;

	status |= si21_ग_लिखोregs(state,
				TWO_DB_BNDWDTH_THRSHLD_REG,
				&regs[0], 0x03);
	reg = 0x56;
	status |= si21_ग_लिखोregs(state,
				LSA_CTRL_REG_1, &reg, 1);
	reg = 0x05;
	status |= si21_ग_लिखोregs(state,
				BLIND_SCAN_CTRL_REG, &reg, 1);
	/* start स्वतःmatic acq */
	status |= si21_ग_लिखोregs(state,
				ACQ_CTRL_REG_2, &start_acq, 0x01);

	वापस status;
पूर्ण

अटल पूर्णांक si21xx_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	/* freq		Channel carrier frequency in KHz (i.e. 1550000 KHz)
	 datarate	Channel symbol rate in Sps (i.e. 22500000 Sps)*/

	/* in MHz */
	अचिन्हित अक्षर coarse_tune_freq;
	पूर्णांक fine_tune_freq;
	अचिन्हित अक्षर sample_rate = 0;
	/* boolean */
	bool inband_पूर्णांकerferer_ind;

	/* INTERMEDIATE VALUES */
	पूर्णांक icoarse_tune_freq; /* MHz */
	पूर्णांक अगरine_tune_freq; /* MHz */
	अचिन्हित पूर्णांक band_high;
	अचिन्हित पूर्णांक band_low;
	अचिन्हित पूर्णांक x1;
	अचिन्हित पूर्णांक x2;
	पूर्णांक i;
	bool inband_पूर्णांकerferer_भाग2[ALLOWABLE_FS_COUNT];
	bool inband_पूर्णांकerferer_भाग4[ALLOWABLE_FS_COUNT];
	पूर्णांक status;

	/* allowable sample rates क्रम ADC in MHz */
	पूर्णांक afs[ALLOWABLE_FS_COUNT] = अणु 200, 192, 193, 194, 195,
					196, 204, 205, 206, 207
	पूर्ण;
	/* in MHz */
	पूर्णांक अगर_limit_high;
	पूर्णांक अगर_limit_low;
	पूर्णांक lnb_lo;
	पूर्णांक lnb_uncertanity;

	पूर्णांक rf_freq;
	पूर्णांक data_rate;
	अचिन्हित अक्षर regs[4];

	dprपूर्णांकk("%s : FE_SET_FRONTEND\n", __func__);

	अगर (c->delivery_प्रणाली != SYS_DVBS) अणु
			dprपूर्णांकk("%s: unsupported delivery system selected (%d)\n",
				__func__, c->delivery_प्रणाली);
			वापस -EOPNOTSUPP;
	पूर्ण

	क्रम (i = 0; i < ALLOWABLE_FS_COUNT; ++i)
		inband_पूर्णांकerferer_भाग2[i] = inband_पूर्णांकerferer_भाग4[i] = false;

	अगर_limit_high = -700000;
	अगर_limit_low = -100000;
	/* in MHz */
	lnb_lo = 0;
	lnb_uncertanity = 0;

	rf_freq = 10 * c->frequency ;
	data_rate = c->symbol_rate / 100;

	status = PASS;

	band_low = (rf_freq - lnb_lo) - ((lnb_uncertanity * 200)
					+ (data_rate * 135)) / 200;

	band_high = (rf_freq - lnb_lo) + ((lnb_uncertanity * 200)
					+ (data_rate * 135)) / 200;


	icoarse_tune_freq = 100000 *
				(((rf_freq - lnb_lo) -
					(अगर_limit_low + अगर_limit_high) / 2)
								/ 100000);

	अगरine_tune_freq = (rf_freq - lnb_lo) - icoarse_tune_freq ;

	क्रम (i = 0; i < ALLOWABLE_FS_COUNT; ++i) अणु
		x1 = ((rf_freq - lnb_lo) / (afs[i] * 2500)) *
					(afs[i] * 2500) + afs[i] * 2500;

		x2 = ((rf_freq - lnb_lo) / (afs[i] * 2500)) *
							(afs[i] * 2500);

		अगर (((band_low < x1) && (x1 < band_high)) ||
					((band_low < x2) && (x2 < band_high)))
					inband_पूर्णांकerferer_भाग4[i] = true;

	पूर्ण

	क्रम (i = 0; i < ALLOWABLE_FS_COUNT; ++i) अणु
		x1 = ((rf_freq - lnb_lo) / (afs[i] * 5000)) *
					(afs[i] * 5000) + afs[i] * 5000;

		x2 = ((rf_freq - lnb_lo) / (afs[i] * 5000)) *
					(afs[i] * 5000);

		अगर (((band_low < x1) && (x1 < band_high)) ||
					((band_low < x2) && (x2 < band_high)))
					inband_पूर्णांकerferer_भाग2[i] = true;
	पूर्ण

	inband_पूर्णांकerferer_ind = true;
	क्रम (i = 0; i < ALLOWABLE_FS_COUNT; ++i) अणु
		अगर (inband_पूर्णांकerferer_भाग2[i] || inband_पूर्णांकerferer_भाग4[i]) अणु
			inband_पूर्णांकerferer_ind = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (inband_पूर्णांकerferer_ind) अणु
		क्रम (i = 0; i < ALLOWABLE_FS_COUNT; ++i) अणु
			अगर (!inband_पूर्णांकerferer_भाग2[i]) अणु
				sample_rate = (u8) afs[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ALLOWABLE_FS_COUNT; ++i) अणु
			अगर ((inband_पूर्णांकerferer_भाग2[i] ||
			     !inband_पूर्णांकerferer_भाग4[i])) अणु
				sample_rate = (u8) afs[i];
				अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (sample_rate > 207 || sample_rate < 192)
		sample_rate = 200;

	fine_tune_freq = ((0x4000 * (अगरine_tune_freq / 10)) /
					((sample_rate) * 1000));

	coarse_tune_freq = (u8)(icoarse_tune_freq / 100000);

	regs[0] = sample_rate;
	regs[1] = coarse_tune_freq;
	regs[2] = fine_tune_freq & 0xFF;
	regs[3] = fine_tune_freq >> 8 & 0xFF;

	status |= si21_ग_लिखोregs(state, PLL_DIVISOR_REG, &regs[0], 0x04);

	state->fs = sample_rate;/*ADC MHz*/
	si21xx_setacquire(fe, c->symbol_rate, c->fec_inner);

	वापस 0;
पूर्ण

अटल पूर्णांक si21xx_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;
	u8 regdata;

	dprपूर्णांकk("%s\n", __func__);

	si21_पढ़ोregs(state, SYSTEM_MODE_REG, &regdata, 0x01);
	regdata |= 1 << 6;
	si21_ग_लिखोregs(state, SYSTEM_MODE_REG, &regdata, 0x01);
	state->initialised = 0;

	वापस 0;
पूर्ण

अटल व्योम si21xx_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा si21xx_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops si21xx_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "SL SI21XX DVB-S",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	=  125 * kHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.symbol_rate_tolerance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		FE_CAN_QPSK |
		FE_CAN_FEC_AUTO
	पूर्ण,

	.release = si21xx_release,
	.init = si21xx_init,
	.sleep = si21xx_sleep,
	.ग_लिखो = si21_ग_लिखो,
	.पढ़ो_status = si21_पढ़ो_status,
	.पढ़ो_ber = si21_पढ़ो_ber,
	.पढ़ो_संकेत_strength = si21_पढ़ो_संकेत_strength,
	.पढ़ो_snr = si21_पढ़ो_snr,
	.पढ़ो_ucblocks = si21_पढ़ो_ucblocks,
	.diseqc_send_master_cmd = si21xx_send_diseqc_msg,
	.diseqc_send_burst = si21xx_send_diseqc_burst,
	.set_tone = si21xx_set_tone,
	.set_voltage = si21xx_set_voltage,

	.set_frontend = si21xx_set_frontend,
पूर्ण;

काष्ठा dvb_frontend *si21xx_attach(स्थिर काष्ठा si21xx_config *config,
						काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा si21xx_state *state = शून्य;
	पूर्णांक id;

	dprपूर्णांकk("%s\n", __func__);

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा si21xx_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;
	state->errmode = STATUS_BER;

	/* check अगर the demod is there */
	id = si21_पढ़ोreg(state, SYSTEM_MODE_REG);
	si21_ग_लिखोreg(state, SYSTEM_MODE_REG, id | 0x40); /* standby off */
	msleep(200);
	id = si21_पढ़ोreg(state, 0x00);

	/* रेजिस्टर 0x00 contains:
		0x34 क्रम SI2107
		0x24 क्रम SI2108
		0x14 क्रम SI2109
		0x04 क्रम SI2110
	*/
	अगर (id != 0x04 && id != 0x14)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &si21xx_ops,
					माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(si21xx_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("SL SI21XX DVB Demodulator driver");
MODULE_AUTHOR("Igor M. Liplianin");
MODULE_LICENSE("GPL");
