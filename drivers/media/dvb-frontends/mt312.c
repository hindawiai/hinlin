<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम Zarlink VP310/MT312/ZL10313 Satellite Channel Decoder

    Copyright (C) 2003 Andreas Oberritter <obi@linuxtv.org>
    Copyright (C) 2008 Matthias Schwarzott <zzam@gentoo.org>


    References:
    http://products.zarlink.com/product_profiles/MT312.hपंचांग
    http://products.zarlink.com/product_profiles/SL1935.hपंचांग
*/

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "mt312_priv.h"
#समावेश "mt312.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

काष्ठा mt312_state अणु
	काष्ठा i2c_adapter *i2c;
	/* configuration settings */
	स्थिर काष्ठा mt312_config *config;
	काष्ठा dvb_frontend frontend;

	u8 id;
	अचिन्हित दीर्घ xtal;
	u8 freq_mult;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "mt312: " args); \
	पूर्ण जबतक (0)

#घोषणा MT312_PLL_CLK		10000000UL	/* 10 MHz */
#घोषणा MT312_PLL_CLK_10_111	10111000UL	/* 10.111 MHz */

अटल पूर्णांक mt312_पढ़ो(काष्ठा mt312_state *state, स्थिर क्रमागत mt312_reg_addr reg,
		      u8 *buf, स्थिर माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[2];
	u8 regbuf[1] = अणु reg पूर्ण;

	msg[0].addr = state->config->demod_address;
	msg[0].flags = 0;
	msg[0].buf = regbuf;
	msg[0].len = 1;
	msg[1].addr = state->config->demod_address;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = buf;
	msg[1].len = count;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		prपूर्णांकk(KERN_DEBUG "%s: ret == %d\n", __func__, ret);
		वापस -EREMOTEIO;
	पूर्ण

	अगर (debug) अणु
		पूर्णांक i;
		dprपूर्णांकk("R(%d):", reg & 0x7f);
		क्रम (i = 0; i < count; i++)
			prपूर्णांकk(KERN_CONT " %02x", buf[i]);
		prपूर्णांकk("\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_ग_लिखो(काष्ठा mt312_state *state, स्थिर क्रमागत mt312_reg_addr reg,
		       स्थिर u8 *src, स्थिर माप_प्रकार count)
अणु
	पूर्णांक ret;
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg;

	अगर (1 + count > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "mt312: write: len=%zu is too big!\n", count);
		वापस -EINVAL;
	पूर्ण

	अगर (debug) अणु
		पूर्णांक i;
		dprपूर्णांकk("W(%d):", reg & 0x7f);
		क्रम (i = 0; i < count; i++)
			prपूर्णांकk(KERN_CONT " %02x", src[i]);
		prपूर्णांकk("\n");
	पूर्ण

	buf[0] = reg;
	स_नकल(&buf[1], src, count);

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = count + 1;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1) अणु
		dprपूर्णांकk("%s: ret == %d\n", __func__, ret);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mt312_पढ़ोreg(काष्ठा mt312_state *state,
				स्थिर क्रमागत mt312_reg_addr reg, u8 *val)
अणु
	वापस mt312_पढ़ो(state, reg, val, 1);
पूर्ण

अटल अंतरभूत पूर्णांक mt312_ग_लिखोreg(काष्ठा mt312_state *state,
				 स्थिर क्रमागत mt312_reg_addr reg, स्थिर u8 val)
अणु
	u8 पंचांगp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */


	वापस mt312_ग_लिखो(state, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक mt312_reset(काष्ठा mt312_state *state, स्थिर u8 full)
अणु
	वापस mt312_ग_लिखोreg(state, RESET, full ? 0x80 : 0x40);
पूर्ण

अटल पूर्णांक mt312_get_inversion(काष्ठा mt312_state *state,
			       क्रमागत fe_spectral_inversion *i)
अणु
	पूर्णांक ret;
	u8 vit_mode;

	ret = mt312_पढ़ोreg(state, VIT_MODE, &vit_mode);
	अगर (ret < 0)
		वापस ret;

	अगर (vit_mode & 0x80)	/* स्वतः inversion was used */
		*i = (vit_mode & 0x40) ? INVERSION_ON : INVERSION_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_get_symbol_rate(काष्ठा mt312_state *state, u32 *sr)
अणु
	पूर्णांक ret;
	u8 sym_rate_h;
	u8 dec_ratio;
	u16 sym_rat_op;
	u16 monitor;
	u8 buf[2];

	ret = mt312_पढ़ोreg(state, SYM_RATE_H, &sym_rate_h);
	अगर (ret < 0)
		वापस ret;

	अगर (sym_rate_h & 0x80) अणु
		/* symbol rate search was used */
		ret = mt312_ग_लिखोreg(state, MON_CTRL, 0x03);
		अगर (ret < 0)
			वापस ret;

		ret = mt312_पढ़ो(state, MONITOR_H, buf, माप(buf));
		अगर (ret < 0)
			वापस ret;

		monitor = (buf[0] << 8) | buf[1];

		dprपूर्णांकk("sr(auto) = %u\n",
			DIV_ROUND_CLOSEST(monitor * 15625, 4));
	पूर्ण अन्यथा अणु
		ret = mt312_ग_लिखोreg(state, MON_CTRL, 0x05);
		अगर (ret < 0)
			वापस ret;

		ret = mt312_पढ़ो(state, MONITOR_H, buf, माप(buf));
		अगर (ret < 0)
			वापस ret;

		dec_ratio = ((buf[0] >> 5) & 0x07) * 32;

		ret = mt312_पढ़ो(state, SYM_RAT_OP_H, buf, माप(buf));
		अगर (ret < 0)
			वापस ret;

		sym_rat_op = (buf[0] << 8) | buf[1];

		dprपूर्णांकk("sym_rat_op=%d dec_ratio=%d\n",
		       sym_rat_op, dec_ratio);
		dprपूर्णांकk("*sr(manual) = %lu\n",
		       (((state->xtal * 8192) / (sym_rat_op + 8192)) *
			2) - dec_ratio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_get_code_rate(काष्ठा mt312_state *state, क्रमागत fe_code_rate *cr)
अणु
	स्थिर क्रमागत fe_code_rate fec_tab[8] =
	    अणु FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_6_7, FEC_7_8,
		FEC_AUTO, FEC_AUTO पूर्ण;

	पूर्णांक ret;
	u8 fec_status;

	ret = mt312_पढ़ोreg(state, FEC_STATUS, &fec_status);
	अगर (ret < 0)
		वापस ret;

	*cr = fec_tab[(fec_status >> 4) & 0x07];

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[2];

	/* wake up */
	ret = mt312_ग_लिखोreg(state, CONFIG,
			(state->freq_mult == 6 ? 0x88 : 0x8c));
	अगर (ret < 0)
		वापस ret;

	/* रुको at least 150 usec */
	udelay(150);

	/* full reset */
	ret = mt312_reset(state, 1);
	अगर (ret < 0)
		वापस ret;

/* Per datasheet, ग_लिखो correct values. 09/28/03 ACCJr.
 * If we करोn't do this, we won't get FE_HAS_VITERBI in the VP310. */
	अणु
		u8 buf_def[8] = अणु 0x14, 0x12, 0x03, 0x02,
				  0x01, 0x00, 0x00, 0x00 पूर्ण;

		ret = mt312_ग_लिखो(state, VIT_SETUP, buf_def, माप(buf_def));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	चयन (state->id) अणु
	हाल ID_ZL10313:
		/* enable ADC */
		ret = mt312_ग_लिखोreg(state, GPP_CTRL, 0x80);
		अगर (ret < 0)
			वापस ret;

		/* configure ZL10313 क्रम optimal ADC perक्रमmance */
		buf[0] = 0x80;
		buf[1] = 0xB0;
		ret = mt312_ग_लिखो(state, HW_CTRL, buf, 2);
		अगर (ret < 0)
			वापस ret;

		/* enable MPEG output and ADCs */
		ret = mt312_ग_लिखोreg(state, HW_CTRL, 0x00);
		अगर (ret < 0)
			वापस ret;

		ret = mt312_ग_लिखोreg(state, MPEG_CTRL, 0x00);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	पूर्ण

	/* SYS_CLK */
	buf[0] = DIV_ROUND_CLOSEST(state->xtal * state->freq_mult * 2, 1000000);

	/* DISEQC_RATIO */
	buf[1] = DIV_ROUND_CLOSEST(state->xtal, 22000 * 4);

	ret = mt312_ग_लिखो(state, SYS_CLK, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	ret = mt312_ग_लिखोreg(state, SNR_THS_HIGH, 0x32);
	अगर (ret < 0)
		वापस ret;

	/* dअगरferent MOCLK polarity */
	चयन (state->id) अणु
	हाल ID_ZL10313:
		buf[0] = 0x33;
		अवरोध;
	शेष:
		buf[0] = 0x53;
		अवरोध;
	पूर्ण

	ret = mt312_ग_लिखोreg(state, OP_CTRL, buf[0]);
	अगर (ret < 0)
		वापस ret;

	/* TS_SW_LIM */
	buf[0] = 0x8c;
	buf[1] = 0x98;

	ret = mt312_ग_लिखो(state, TS_SW_LIM_L, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	ret = mt312_ग_लिखोreg(state, CS_SW_LIM, 0x69);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_send_master_cmd(काष्ठा dvb_frontend *fe,
				 काष्ठा dvb_diseqc_master_cmd *c)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 diseqc_mode;

	अगर ((c->msg_len == 0) || (c->msg_len > माप(c->msg)))
		वापस -EINVAL;

	ret = mt312_पढ़ोreg(state, DISEQC_MODE, &diseqc_mode);
	अगर (ret < 0)
		वापस ret;

	ret = mt312_ग_लिखो(state, (0x80 | DISEQC_INSTR), c->msg, c->msg_len);
	अगर (ret < 0)
		वापस ret;

	ret = mt312_ग_लिखोreg(state, DISEQC_MODE,
			     (diseqc_mode & 0x40) | ((c->msg_len - 1) << 3)
			     | 0x04);
	अगर (ret < 0)
		वापस ret;

	/* is there a better way to रुको क्रम message to be transmitted */
	msleep(100);

	/* set DISEQC_MODE[2:0] to zero अगर a वापस message is expected */
	अगर (c->msg[0] & 0x02) अणु
		ret = mt312_ग_लिखोreg(state, DISEQC_MODE, (diseqc_mode & 0x40));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_send_burst(काष्ठा dvb_frontend *fe,
			    स्थिर क्रमागत fe_sec_mini_cmd c)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	स्थिर u8 mini_tab[2] = अणु 0x02, 0x03 पूर्ण;

	पूर्णांक ret;
	u8 diseqc_mode;

	अगर (c > SEC_MINI_B)
		वापस -EINVAL;

	ret = mt312_पढ़ोreg(state, DISEQC_MODE, &diseqc_mode);
	अगर (ret < 0)
		वापस ret;

	ret = mt312_ग_लिखोreg(state, DISEQC_MODE,
			     (diseqc_mode & 0x40) | mini_tab[c]);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_set_tone(काष्ठा dvb_frontend *fe,
			  स्थिर क्रमागत fe_sec_tone_mode t)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	स्थिर u8 tone_tab[2] = अणु 0x01, 0x00 पूर्ण;

	पूर्णांक ret;
	u8 diseqc_mode;

	अगर (t > SEC_TONE_OFF)
		वापस -EINVAL;

	ret = mt312_पढ़ोreg(state, DISEQC_MODE, &diseqc_mode);
	अगर (ret < 0)
		वापस ret;

	ret = mt312_ग_लिखोreg(state, DISEQC_MODE,
			     (diseqc_mode & 0x40) | tone_tab[t]);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_set_voltage(काष्ठा dvb_frontend *fe,
			     स्थिर क्रमागत fe_sec_voltage v)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	स्थिर u8 volt_tab[3] = अणु 0x00, 0x40, 0x00 पूर्ण;
	u8 val;

	अगर (v > SEC_VOLTAGE_OFF)
		वापस -EINVAL;

	val = volt_tab[v];
	अगर (state->config->voltage_inverted)
		val ^= 0x40;

	वापस mt312_ग_लिखोreg(state, DISEQC_MODE, val);
पूर्ण

अटल पूर्णांक mt312_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *s)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 status[3];

	*s = 0;

	ret = mt312_पढ़ो(state, QPSK_STAT_H, status, माप(status));
	अगर (ret < 0)
		वापस ret;

	dprपूर्णांकk("QPSK_STAT_H: 0x%02x, QPSK_STAT_L: 0x%02x, FEC_STATUS: 0x%02x\n",
		status[0], status[1], status[2]);

	अगर (status[0] & 0xc0)
		*s |= FE_HAS_SIGNAL;	/* संकेत noise ratio */
	अगर (status[0] & 0x04)
		*s |= FE_HAS_CARRIER;	/* qpsk carrier lock */
	अगर (status[2] & 0x02)
		*s |= FE_HAS_VITERBI;	/* viterbi lock */
	अगर (status[2] & 0x04)
		*s |= FE_HAS_SYNC;	/* byte align lock */
	अगर (status[0] & 0x01)
		*s |= FE_HAS_LOCK;	/* qpsk lock */

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[3];

	ret = mt312_पढ़ो(state, RS_BERCNT_H, buf, 3);
	अगर (ret < 0)
		वापस ret;

	*ber = ((buf[0] << 16) | (buf[1] << 8) | buf[2]) * 64;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
				      u16 *संकेत_strength)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[3];
	u16 agc;
	s16 err_db;

	ret = mt312_पढ़ो(state, AGC_H, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	agc = (buf[0] << 6) | (buf[1] >> 2);
	err_db = (s16) (((buf[1] & 0x03) << 14) | buf[2] << 6) >> 6;

	*संकेत_strength = agc;

	dprपूर्णांकk("agc=%08x err_db=%hd\n", agc, err_db);

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[2];

	ret = mt312_पढ़ो(state, M_SNR_H, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	*snr = 0xFFFF - ((((buf[0] & 0x7f) << 8) | buf[1]) << 1);

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ubc)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[2];

	ret = mt312_पढ़ो(state, RS_UBC_H, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	*ubc = (buf[0] << 8) | buf[1];

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 buf[5], config_val;
	u16 sr;

	स्थिर u8 fec_tab[10] =
	    अणु 0x00, 0x01, 0x02, 0x04, 0x3f, 0x08, 0x10, 0x20, 0x3f, 0x3f पूर्ण;
	स्थिर u8 inv_tab[3] = अणु 0x00, 0x40, 0x80 पूर्ण;

	dprपूर्णांकk("%s: Freq %d\n", __func__, p->frequency);

	अगर ((p->frequency < fe->ops.info.frequency_min_hz / kHz)
	    || (p->frequency > fe->ops.info.frequency_max_hz / kHz))
		वापस -EINVAL;

	अगर (((पूर्णांक)p->inversion < INVERSION_OFF)
	    || (p->inversion > INVERSION_ON))
		वापस -EINVAL;

	अगर ((p->symbol_rate < fe->ops.info.symbol_rate_min)
	    || (p->symbol_rate > fe->ops.info.symbol_rate_max))
		वापस -EINVAL;

	अगर (((पूर्णांक)p->fec_inner < FEC_NONE)
	    || (p->fec_inner > FEC_AUTO))
		वापस -EINVAL;

	अगर ((p->fec_inner == FEC_4_5)
	    || (p->fec_inner == FEC_8_9))
		वापस -EINVAL;

	चयन (state->id) अणु
	हाल ID_VP310:
	/* For now we will करो this only क्रम the VP310.
	 * It should be better क्रम the mt312 as well,
	 * but tuning will be slower. ACCJr 09/29/03
	 */
		ret = mt312_पढ़ोreg(state, CONFIG, &config_val);
		अगर (ret < 0)
			वापस ret;
		अगर (p->symbol_rate >= 30000000) अणु
			/* Note that 30MS/s should use 90MHz */
			अगर (state->freq_mult == 6) अणु
				/* We are running 60MHz */
				state->freq_mult = 9;
				ret = mt312_initfe(fe);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (state->freq_mult == 9) अणु
				/* We are running 90MHz */
				state->freq_mult = 6;
				ret = mt312_initfe(fe);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ID_MT312:
	हाल ID_ZL10313:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* sr = (u16)(sr * 256.0 / 1000000.0) */
	sr = DIV_ROUND_CLOSEST(p->symbol_rate * 4, 15625);

	/* SYM_RATE */
	buf[0] = (sr >> 8) & 0x3f;
	buf[1] = (sr >> 0) & 0xff;

	/* VIT_MODE */
	buf[2] = inv_tab[p->inversion] | fec_tab[p->fec_inner];

	/* QPSK_CTRL */
	buf[3] = 0x40;		/* swap I and Q beक्रमe QPSK demodulation */

	अगर (p->symbol_rate < 10000000)
		buf[3] |= 0x04;	/* use afc mode */

	/* GO */
	buf[4] = 0x01;

	ret = mt312_ग_लिखो(state, SYM_RATE_H, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	ret = mt312_reset(state, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_get_frontend(काष्ठा dvb_frontend *fe,
			      काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	ret = mt312_get_inversion(state, &p->inversion);
	अगर (ret < 0)
		वापस ret;

	ret = mt312_get_symbol_rate(state, &p->symbol_rate);
	अगर (ret < 0)
		वापस ret;

	ret = mt312_get_code_rate(state, &p->fec_inner);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;

	u8 val = 0x00;
	पूर्णांक ret;

	चयन (state->id) अणु
	हाल ID_ZL10313:
		ret = mt312_पढ़ोreg(state, GPP_CTRL, &val);
		अगर (ret < 0)
			जाओ error;

		/* preserve this bit to not accidentally shutकरोwn ADC */
		val &= 0x80;
		अवरोध;
	पूर्ण

	अगर (enable)
		val |= 0x40;
	अन्यथा
		val &= ~0x40;

	ret = mt312_ग_लिखोreg(state, GPP_CTRL, val);

error:
	वापस ret;
पूर्ण

अटल पूर्णांक mt312_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 config;

	/* reset all रेजिस्टरs to शेषs */
	ret = mt312_reset(state, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (state->id == ID_ZL10313) अणु
		/* reset ADC */
		ret = mt312_ग_लिखोreg(state, GPP_CTRL, 0x00);
		अगर (ret < 0)
			वापस ret;

		/* full shutकरोwn of ADCs, mpeg bus tristated */
		ret = mt312_ग_लिखोreg(state, HW_CTRL, 0x0d);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = mt312_पढ़ोreg(state, CONFIG, &config);
	अगर (ret < 0)
		वापस ret;

	/* enter standby */
	ret = mt312_ग_लिखोreg(state, CONFIG, config & 0x7f);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt312_get_tune_settings(काष्ठा dvb_frontend *fe,
		काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	fesettings->min_delay_ms = 50;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम mt312_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt312_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

#घोषणा MT312_SYS_CLK		90000000UL	/* 90 MHz */
अटल स्थिर काष्ठा dvb_frontend_ops mt312_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name = "Zarlink ???? DVB-S",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		/* FIXME: adjust freq to real used xtal */
		.frequency_stepsize_hz = MT312_PLL_CLK / 128,
		.symbol_rate_min = MT312_SYS_CLK / 128, /* FIXME as above */
		.symbol_rate_max = MT312_SYS_CLK / 2,
		.caps =
		    FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
		    FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		    FE_CAN_FEC_AUTO | FE_CAN_QPSK | FE_CAN_MUTE_TS |
		    FE_CAN_RECOVER
	पूर्ण,

	.release = mt312_release,

	.init = mt312_initfe,
	.sleep = mt312_sleep,
	.i2c_gate_ctrl = mt312_i2c_gate_ctrl,

	.set_frontend = mt312_set_frontend,
	.get_frontend = mt312_get_frontend,
	.get_tune_settings = mt312_get_tune_settings,

	.पढ़ो_status = mt312_पढ़ो_status,
	.पढ़ो_ber = mt312_पढ़ो_ber,
	.पढ़ो_संकेत_strength = mt312_पढ़ो_संकेत_strength,
	.पढ़ो_snr = mt312_पढ़ो_snr,
	.पढ़ो_ucblocks = mt312_पढ़ो_ucblocks,

	.diseqc_send_master_cmd = mt312_send_master_cmd,
	.diseqc_send_burst = mt312_send_burst,
	.set_tone = mt312_set_tone,
	.set_voltage = mt312_set_voltage,
पूर्ण;

काष्ठा dvb_frontend *mt312_attach(स्थिर काष्ठा mt312_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा mt312_state *state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा mt312_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	अगर (mt312_पढ़ोreg(state, ID, &state->id) < 0)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &mt312_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	चयन (state->id) अणु
	हाल ID_VP310:
		strscpy(state->frontend.ops.info.name, "Zarlink VP310 DVB-S",
			माप(state->frontend.ops.info.name));
		state->xtal = MT312_PLL_CLK;
		state->freq_mult = 9;
		अवरोध;
	हाल ID_MT312:
		strscpy(state->frontend.ops.info.name, "Zarlink MT312 DVB-S",
			माप(state->frontend.ops.info.name));
		state->xtal = MT312_PLL_CLK;
		state->freq_mult = 6;
		अवरोध;
	हाल ID_ZL10313:
		strscpy(state->frontend.ops.info.name, "Zarlink ZL10313 DVB-S",
			माप(state->frontend.ops.info.name));
		state->xtal = MT312_PLL_CLK_10_111;
		state->freq_mult = 9;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "Only Zarlink VP310/MT312/ZL10313 are supported chips.\n");
		जाओ error;
	पूर्ण

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mt312_attach);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Zarlink VP310/MT312/ZL10313 DVB-S Demodulator driver");
MODULE_AUTHOR("Andreas Oberritter <obi@linuxtv.org>");
MODULE_AUTHOR("Matthias Schwarzott <zzam@gentoo.org>");
MODULE_LICENSE("GPL");

