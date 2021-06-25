<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम LG Electronics LGDT3304 and LGDT3305 - VSB/QAM
 *
 *    Copyright (C) 2008, 2009, 2010 Michael Krufky <mkrufky@linuxtv.org>
 *
 *    LGDT3304 support by Jarod Wilson <jarod@redhat.com>
 */

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/slab.h>
#समावेश <media/dvb_गणित.स>
#समावेश "lgdt3305.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debug level (info=1, reg=2 (or-able))");

#घोषणा DBG_INFO 1
#घोषणा DBG_REG  2

#घोषणा lg_prपूर्णांकk(kern, fmt, arg...)					\
	prपूर्णांकk(kern "%s: " fmt, __func__, ##arg)

#घोषणा lg_info(fmt, arg...)	prपूर्णांकk(KERN_INFO "lgdt3305: " fmt, ##arg)
#घोषणा lg_warn(fmt, arg...)	lg_prपूर्णांकk(KERN_WARNING,       fmt, ##arg)
#घोषणा lg_err(fmt, arg...)	lg_prपूर्णांकk(KERN_ERR,           fmt, ##arg)
#घोषणा lg_dbg(fmt, arg...) अगर (debug & DBG_INFO)			\
				lg_prपूर्णांकk(KERN_DEBUG,         fmt, ##arg)
#घोषणा lg_reg(fmt, arg...) अगर (debug & DBG_REG)			\
				lg_prपूर्णांकk(KERN_DEBUG,         fmt, ##arg)

#घोषणा lg_fail(ret)							\
(अणु									\
	पूर्णांक __ret;							\
	__ret = (ret < 0);						\
	अगर (__ret)							\
		lg_err("error %d on line %d\n",	ret, __LINE__);		\
	__ret;								\
पूर्ण)

काष्ठा lgdt3305_state अणु
	काष्ठा i2c_adapter *i2c_adap;
	स्थिर काष्ठा lgdt3305_config *cfg;

	काष्ठा dvb_frontend frontend;

	क्रमागत fe_modulation current_modulation;
	u32 current_frequency;
	u32 snr;
पूर्ण;

/* ------------------------------------------------------------------------ */

/* FIXME: verअगरy & करोcument the LGDT3304 रेजिस्टरs */

#घोषणा LGDT3305_GEN_CTRL_1                   0x0000
#घोषणा LGDT3305_GEN_CTRL_2                   0x0001
#घोषणा LGDT3305_GEN_CTRL_3                   0x0002
#घोषणा LGDT3305_GEN_STATUS                   0x0003
#घोषणा LGDT3305_GEN_CONTROL                  0x0007
#घोषणा LGDT3305_GEN_CTRL_4                   0x000a
#घोषणा LGDT3305_DGTL_AGC_REF_1               0x0012
#घोषणा LGDT3305_DGTL_AGC_REF_2               0x0013
#घोषणा LGDT3305_CR_CTR_FREQ_1                0x0106
#घोषणा LGDT3305_CR_CTR_FREQ_2                0x0107
#घोषणा LGDT3305_CR_CTR_FREQ_3                0x0108
#घोषणा LGDT3305_CR_CTR_FREQ_4                0x0109
#घोषणा LGDT3305_CR_MSE_1                     0x011b
#घोषणा LGDT3305_CR_MSE_2                     0x011c
#घोषणा LGDT3305_CR_LOCK_STATUS               0x011d
#घोषणा LGDT3305_CR_CTRL_7                    0x0126
#घोषणा LGDT3305_AGC_POWER_REF_1              0x0300
#घोषणा LGDT3305_AGC_POWER_REF_2              0x0301
#घोषणा LGDT3305_AGC_DELAY_PT_1               0x0302
#घोषणा LGDT3305_AGC_DELAY_PT_2               0x0303
#घोषणा LGDT3305_RFAGC_LOOP_FLTR_BW_1         0x0306
#घोषणा LGDT3305_RFAGC_LOOP_FLTR_BW_2         0x0307
#घोषणा LGDT3305_IFBW_1                       0x0308
#घोषणा LGDT3305_IFBW_2                       0x0309
#घोषणा LGDT3305_AGC_CTRL_1                   0x030c
#घोषणा LGDT3305_AGC_CTRL_4                   0x0314
#घोषणा LGDT3305_EQ_MSE_1                     0x0413
#घोषणा LGDT3305_EQ_MSE_2                     0x0414
#घोषणा LGDT3305_EQ_MSE_3                     0x0415
#घोषणा LGDT3305_PT_MSE_1                     0x0417
#घोषणा LGDT3305_PT_MSE_2                     0x0418
#घोषणा LGDT3305_PT_MSE_3                     0x0419
#घोषणा LGDT3305_FEC_BLOCK_CTRL               0x0504
#घोषणा LGDT3305_FEC_LOCK_STATUS              0x050a
#घोषणा LGDT3305_FEC_PKT_ERR_1                0x050c
#घोषणा LGDT3305_FEC_PKT_ERR_2                0x050d
#घोषणा LGDT3305_TP_CTRL_1                    0x050e
#घोषणा LGDT3305_BERT_PERIOD                  0x0801
#घोषणा LGDT3305_BERT_ERROR_COUNT_1           0x080a
#घोषणा LGDT3305_BERT_ERROR_COUNT_2           0x080b
#घोषणा LGDT3305_BERT_ERROR_COUNT_3           0x080c
#घोषणा LGDT3305_BERT_ERROR_COUNT_4           0x080d

अटल पूर्णांक lgdt3305_ग_लिखो_reg(काष्ठा lgdt3305_state *state, u16 reg, u8 val)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg >> 8, reg & 0xff, val पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = state->cfg->i2c_addr, .flags = 0,
		.buf = buf, .len = 3,
	पूर्ण;

	lg_reg("reg: 0x%04x, val: 0x%02x\n", reg, val);

	ret = i2c_transfer(state->i2c_adap, &msg, 1);

	अगर (ret != 1) अणु
		lg_err("error (addr %02x %02x <- %02x, err = %i)\n",
		       msg.buf[0], msg.buf[1], msg.buf[2], ret);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_पढ़ो_reg(काष्ठा lgdt3305_state *state, u16 reg, u8 *val)
अणु
	पूर्णांक ret;
	u8 reg_buf[] = अणु reg >> 8, reg & 0xff पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->cfg->i2c_addr,
		  .flags = 0, .buf = reg_buf, .len = 2 पूर्ण,
		अणु .addr = state->cfg->i2c_addr,
		  .flags = I2C_M_RD, .buf = val, .len = 1 पूर्ण,
	पूर्ण;

	lg_reg("reg: 0x%04x\n", reg);

	ret = i2c_transfer(state->i2c_adap, msg, 2);

	अगर (ret != 2) अणु
		lg_err("error (addr %02x reg %04x error (ret == %i)\n",
		       state->cfg->i2c_addr, reg, ret);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा पढ़ो_reg(state, reg)						\
(अणु									\
	u8 __val;							\
	पूर्णांक ret = lgdt3305_पढ़ो_reg(state, reg, &__val);		\
	अगर (lg_fail(ret))						\
		__val = 0;						\
	__val;								\
पूर्ण)

अटल पूर्णांक lgdt3305_set_reg_bit(काष्ठा lgdt3305_state *state,
				u16 reg, पूर्णांक bit, पूर्णांक onoff)
अणु
	u8 val;
	पूर्णांक ret;

	lg_reg("reg: 0x%04x, bit: %d, level: %d\n", reg, bit, onoff);

	ret = lgdt3305_पढ़ो_reg(state, reg, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= ~(1 << bit);
	val |= (onoff & 1) << bit;

	ret = lgdt3305_ग_लिखो_reg(state, reg, val);
fail:
	वापस ret;
पूर्ण

काष्ठा lgdt3305_reg अणु
	u16 reg;
	u8 val;
पूर्ण;

अटल पूर्णांक lgdt3305_ग_लिखो_regs(काष्ठा lgdt3305_state *state,
			       काष्ठा lgdt3305_reg *regs, पूर्णांक len)
अणु
	पूर्णांक i, ret;

	lg_reg("writing %d registers...\n", len);

	क्रम (i = 0; i < len - 1; i++) अणु
		ret = lgdt3305_ग_लिखो_reg(state, regs[i].reg, regs[i].val);
		अगर (lg_fail(ret))
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3305_soft_reset(काष्ठा lgdt3305_state *state)
अणु
	पूर्णांक ret;

	lg_dbg("\n");

	ret = lgdt3305_set_reg_bit(state, LGDT3305_GEN_CTRL_3, 0, 0);
	अगर (lg_fail(ret))
		जाओ fail;

	msleep(20);
	ret = lgdt3305_set_reg_bit(state, LGDT3305_GEN_CTRL_3, 0, 1);
fail:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक lgdt3305_mpeg_mode(काष्ठा lgdt3305_state *state,
				     क्रमागत lgdt3305_mpeg_mode mode)
अणु
	lg_dbg("(%d)\n", mode);
	वापस lgdt3305_set_reg_bit(state, LGDT3305_TP_CTRL_1, 5, mode);
पूर्ण

अटल पूर्णांक lgdt3305_mpeg_mode_polarity(काष्ठा lgdt3305_state *state)
अणु
	u8 val;
	पूर्णांक ret;
	क्रमागत lgdt3305_tp_घड़ी_edge edge = state->cfg->tpclk_edge;
	क्रमागत lgdt3305_tp_घड़ी_mode mode = state->cfg->tpclk_mode;
	क्रमागत lgdt3305_tp_valid_polarity valid = state->cfg->tpvalid_polarity;

	lg_dbg("edge = %d, valid = %d\n", edge, valid);

	ret = lgdt3305_पढ़ो_reg(state, LGDT3305_TP_CTRL_1, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= ~0x09;

	अगर (edge)
		val |= 0x08;
	अगर (mode)
		val |= 0x40;
	अगर (valid)
		val |= 0x01;

	ret = lgdt3305_ग_लिखो_reg(state, LGDT3305_TP_CTRL_1, val);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_soft_reset(state);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_set_modulation(काष्ठा lgdt3305_state *state,
				   काष्ठा dtv_frontend_properties *p)
अणु
	u8 opermode;
	पूर्णांक ret;

	lg_dbg("\n");

	ret = lgdt3305_पढ़ो_reg(state, LGDT3305_GEN_CTRL_1, &opermode);
	अगर (lg_fail(ret))
		जाओ fail;

	opermode &= ~0x03;

	चयन (p->modulation) अणु
	हाल VSB_8:
		opermode |= 0x03;
		अवरोध;
	हाल QAM_64:
		opermode |= 0x00;
		अवरोध;
	हाल QAM_256:
		opermode |= 0x01;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ret = lgdt3305_ग_लिखो_reg(state, LGDT3305_GEN_CTRL_1, opermode);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_set_filter_extension(काष्ठा lgdt3305_state *state,
					 काष्ठा dtv_frontend_properties *p)
अणु
	पूर्णांक val;

	चयन (p->modulation) अणु
	हाल VSB_8:
		val = 0;
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	lg_dbg("val = %d\n", val);

	वापस lgdt3305_set_reg_bit(state, 0x043f, 2, val);
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3305_passband_digital_agc(काष्ठा lgdt3305_state *state,
					 काष्ठा dtv_frontend_properties *p)
अणु
	u16 agc_ref;

	चयन (p->modulation) अणु
	हाल VSB_8:
		agc_ref = 0x32c4;
		अवरोध;
	हाल QAM_64:
		agc_ref = 0x2a00;
		अवरोध;
	हाल QAM_256:
		agc_ref = 0x2a80;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lg_dbg("agc ref: 0x%04x\n", agc_ref);

	lgdt3305_ग_लिखो_reg(state, LGDT3305_DGTL_AGC_REF_1, agc_ref >> 8);
	lgdt3305_ग_लिखो_reg(state, LGDT3305_DGTL_AGC_REF_2, agc_ref & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_rfagc_loop(काष्ठा lgdt3305_state *state,
			       काष्ठा dtv_frontend_properties *p)
अणु
	u16 अगरbw, rfbw, agcdelay;

	चयन (p->modulation) अणु
	हाल VSB_8:
		agcdelay = 0x04c0;
		rfbw     = 0x8000;
		अगरbw     = 0x8000;
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		agcdelay = 0x046b;
		rfbw     = 0x8889;
		/* FIXME: investigate optimal अगरbw & rfbw values क्रम the
		 *        DT3304 and re-ग_लिखो this चयन..हाल block */
		अगर (state->cfg->demod_chip == LGDT3304)
			अगरbw = 0x6666;
		अन्यथा /* (state->cfg->demod_chip == LGDT3305) */
			अगरbw = 0x8888;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (state->cfg->rf_agc_loop) अणु
		lg_dbg("agcdelay: 0x%04x, rfbw: 0x%04x\n", agcdelay, rfbw);

		/* rf agc loop filter bandwidth */
		lgdt3305_ग_लिखो_reg(state, LGDT3305_AGC_DELAY_PT_1,
				   agcdelay >> 8);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_AGC_DELAY_PT_2,
				   agcdelay & 0xff);

		lgdt3305_ग_लिखो_reg(state, LGDT3305_RFAGC_LOOP_FLTR_BW_1,
				   rfbw >> 8);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_RFAGC_LOOP_FLTR_BW_2,
				   rfbw & 0xff);
	पूर्ण अन्यथा अणु
		lg_dbg("ifbw: 0x%04x\n", अगरbw);

		/* अगर agc loop filter bandwidth */
		lgdt3305_ग_लिखो_reg(state, LGDT3305_IFBW_1, अगरbw >> 8);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_IFBW_2, अगरbw & 0xff);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_agc_setup(काष्ठा lgdt3305_state *state,
			      काष्ठा dtv_frontend_properties *p)
अणु
	पूर्णांक lockdten, acqen;

	चयन (p->modulation) अणु
	हाल VSB_8:
		lockdten = 0;
		acqen = 0;
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		lockdten = 1;
		acqen = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lg_dbg("lockdten = %d, acqen = %d\n", lockdten, acqen);

	/* control agc function */
	चयन (state->cfg->demod_chip) अणु
	हाल LGDT3304:
		lgdt3305_ग_लिखो_reg(state, 0x0314, 0xe1 | lockdten << 1);
		lgdt3305_set_reg_bit(state, 0x030e, 2, acqen);
		अवरोध;
	हाल LGDT3305:
		lgdt3305_ग_लिखो_reg(state, LGDT3305_AGC_CTRL_4, 0xe1 | lockdten << 1);
		lgdt3305_set_reg_bit(state, LGDT3305_AGC_CTRL_1, 2, acqen);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस lgdt3305_rfagc_loop(state, p);
पूर्ण

अटल पूर्णांक lgdt3305_set_agc_घातer_ref(काष्ठा lgdt3305_state *state,
				      काष्ठा dtv_frontend_properties *p)
अणु
	u16 usref = 0;

	चयन (p->modulation) अणु
	हाल VSB_8:
		अगर (state->cfg->usref_8vsb)
			usref = state->cfg->usref_8vsb;
		अवरोध;
	हाल QAM_64:
		अगर (state->cfg->usref_qam64)
			usref = state->cfg->usref_qam64;
		अवरोध;
	हाल QAM_256:
		अगर (state->cfg->usref_qam256)
			usref = state->cfg->usref_qam256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (usref) अणु
		lg_dbg("set manual mode: 0x%04x\n", usref);

		lgdt3305_set_reg_bit(state, LGDT3305_AGC_CTRL_1, 3, 1);

		lgdt3305_ग_लिखो_reg(state, LGDT3305_AGC_POWER_REF_1,
				   0xff & (usref >> 8));
		lgdt3305_ग_लिखो_reg(state, LGDT3305_AGC_POWER_REF_2,
				   0xff & (usref >> 0));
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3305_spectral_inversion(काष्ठा lgdt3305_state *state,
				       काष्ठा dtv_frontend_properties *p,
				       पूर्णांक inversion)
अणु
	पूर्णांक ret;

	lg_dbg("(%d)\n", inversion);

	चयन (p->modulation) अणु
	हाल VSB_8:
		ret = lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTRL_7,
					 inversion ? 0xf9 : 0x79);
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		ret = lgdt3305_ग_लिखो_reg(state, LGDT3305_FEC_BLOCK_CTRL,
					 inversion ? 0xfd : 0xff);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_set_अगर(काष्ठा lgdt3305_state *state,
			   काष्ठा dtv_frontend_properties *p)
अणु
	u16 अगर_freq_khz;
	u8 nco1, nco2, nco3, nco4;
	u64 nco;

	चयन (p->modulation) अणु
	हाल VSB_8:
		अगर_freq_khz = state->cfg->vsb_अगर_khz;
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		अगर_freq_khz = state->cfg->qam_अगर_khz;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nco = अगर_freq_khz / 10;

	चयन (p->modulation) अणु
	हाल VSB_8:
		nco <<= 24;
		करो_भाग(nco, 625);
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		nco <<= 28;
		करो_भाग(nco, 625);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nco1 = (nco >> 24) & 0x3f;
	nco1 |= 0x40;
	nco2 = (nco >> 16) & 0xff;
	nco3 = (nco >> 8) & 0xff;
	nco4 = nco & 0xff;

	lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_1, nco1);
	lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_2, nco2);
	lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_3, nco3);
	lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_4, nco4);

	lg_dbg("%d KHz -> [%02x%02x%02x%02x]\n",
	       अगर_freq_khz, nco1, nco2, nco3, nco4);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3305_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;

	अगर (state->cfg->deny_i2c_rptr)
		वापस 0;

	lg_dbg("(%d)\n", enable);

	वापस lgdt3305_set_reg_bit(state, LGDT3305_GEN_CTRL_2, 5,
				    enable ? 0 : 1);
पूर्ण

अटल पूर्णांक lgdt3305_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	u8 gen_ctrl_3, gen_ctrl_4;

	lg_dbg("\n");

	gen_ctrl_3 = पढ़ो_reg(state, LGDT3305_GEN_CTRL_3);
	gen_ctrl_4 = पढ़ो_reg(state, LGDT3305_GEN_CTRL_4);

	/* hold in software reset जबतक sleeping */
	gen_ctrl_3 &= ~0x01;
	/* tristate the IF-AGC pin */
	gen_ctrl_3 |=  0x02;
	/* tristate the RF-AGC pin */
	gen_ctrl_3 |=  0x04;

	/* disable vsb/qam module */
	gen_ctrl_4 &= ~0x01;
	/* disable adc module */
	gen_ctrl_4 &= ~0x02;

	lgdt3305_ग_लिखो_reg(state, LGDT3305_GEN_CTRL_3, gen_ctrl_3);
	lgdt3305_ग_लिखो_reg(state, LGDT3305_GEN_CTRL_4, gen_ctrl_4);

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	अटल काष्ठा lgdt3305_reg lgdt3304_init_data[] = अणु
		अणु .reg = LGDT3305_GEN_CTRL_1,           .val = 0x03, पूर्ण,
		अणु .reg = 0x000d,                        .val = 0x02, पूर्ण,
		अणु .reg = 0x000e,                        .val = 0x02, पूर्ण,
		अणु .reg = LGDT3305_DGTL_AGC_REF_1,       .val = 0x32, पूर्ण,
		अणु .reg = LGDT3305_DGTL_AGC_REF_2,       .val = 0xc4, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_1,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_2,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_3,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_4,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTRL_7,            .val = 0xf9, पूर्ण,
		अणु .reg = 0x0112,                        .val = 0x17, पूर्ण,
		अणु .reg = 0x0113,                        .val = 0x15, पूर्ण,
		अणु .reg = 0x0114,                        .val = 0x18, पूर्ण,
		अणु .reg = 0x0115,                        .val = 0xff, पूर्ण,
		अणु .reg = 0x0116,                        .val = 0x3c, पूर्ण,
		अणु .reg = 0x0214,                        .val = 0x67, पूर्ण,
		अणु .reg = 0x0424,                        .val = 0x8d, पूर्ण,
		अणु .reg = 0x0427,                        .val = 0x12, पूर्ण,
		अणु .reg = 0x0428,                        .val = 0x4f, पूर्ण,
		अणु .reg = LGDT3305_IFBW_1,               .val = 0x80, पूर्ण,
		अणु .reg = LGDT3305_IFBW_2,               .val = 0x00, पूर्ण,
		अणु .reg = 0x030a,                        .val = 0x08, पूर्ण,
		अणु .reg = 0x030b,                        .val = 0x9b, पूर्ण,
		अणु .reg = 0x030d,                        .val = 0x00, पूर्ण,
		अणु .reg = 0x030e,                        .val = 0x1c, पूर्ण,
		अणु .reg = 0x0314,                        .val = 0xe1, पूर्ण,
		अणु .reg = 0x000d,                        .val = 0x82, पूर्ण,
		अणु .reg = LGDT3305_TP_CTRL_1,            .val = 0x5b, पूर्ण,
		अणु .reg = LGDT3305_TP_CTRL_1,            .val = 0x5b, पूर्ण,
	पूर्ण;

	अटल काष्ठा lgdt3305_reg lgdt3305_init_data[] = अणु
		अणु .reg = LGDT3305_GEN_CTRL_1,           .val = 0x03, पूर्ण,
		अणु .reg = LGDT3305_GEN_CTRL_2,           .val = 0xb0, पूर्ण,
		अणु .reg = LGDT3305_GEN_CTRL_3,           .val = 0x01, पूर्ण,
		अणु .reg = LGDT3305_GEN_CONTROL,          .val = 0x6f, पूर्ण,
		अणु .reg = LGDT3305_GEN_CTRL_4,           .val = 0x03, पूर्ण,
		अणु .reg = LGDT3305_DGTL_AGC_REF_1,       .val = 0x32, पूर्ण,
		अणु .reg = LGDT3305_DGTL_AGC_REF_2,       .val = 0xc4, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_1,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_2,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_3,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTR_FREQ_4,        .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_CR_CTRL_7,            .val = 0x79, पूर्ण,
		अणु .reg = LGDT3305_AGC_POWER_REF_1,      .val = 0x32, पूर्ण,
		अणु .reg = LGDT3305_AGC_POWER_REF_2,      .val = 0xc4, पूर्ण,
		अणु .reg = LGDT3305_AGC_DELAY_PT_1,       .val = 0x0d, पूर्ण,
		अणु .reg = LGDT3305_AGC_DELAY_PT_2,       .val = 0x30, पूर्ण,
		अणु .reg = LGDT3305_RFAGC_LOOP_FLTR_BW_1, .val = 0x80, पूर्ण,
		अणु .reg = LGDT3305_RFAGC_LOOP_FLTR_BW_2, .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_IFBW_1,               .val = 0x80, पूर्ण,
		अणु .reg = LGDT3305_IFBW_2,               .val = 0x00, पूर्ण,
		अणु .reg = LGDT3305_AGC_CTRL_1,           .val = 0x30, पूर्ण,
		अणु .reg = LGDT3305_AGC_CTRL_4,           .val = 0x61, पूर्ण,
		अणु .reg = LGDT3305_FEC_BLOCK_CTRL,       .val = 0xff, पूर्ण,
		अणु .reg = LGDT3305_TP_CTRL_1,            .val = 0x1b, पूर्ण,
	पूर्ण;

	lg_dbg("\n");

	चयन (state->cfg->demod_chip) अणु
	हाल LGDT3304:
		ret = lgdt3305_ग_लिखो_regs(state, lgdt3304_init_data,
					  ARRAY_SIZE(lgdt3304_init_data));
		अवरोध;
	हाल LGDT3305:
		ret = lgdt3305_ग_लिखो_regs(state, lgdt3305_init_data,
					  ARRAY_SIZE(lgdt3305_init_data));
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_soft_reset(state);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3304_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	lg_dbg("(%d, %d)\n", p->frequency, p->modulation);

	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
		अगर (lg_fail(ret))
			जाओ fail;
		state->current_frequency = p->frequency;
	पूर्ण

	ret = lgdt3305_set_modulation(state, p);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_passband_digital_agc(state, p);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_agc_setup(state, p);
	अगर (lg_fail(ret))
		जाओ fail;

	/* reg 0x030d is 3304-only... seen in vsb and qam usbsnoops... */
	चयन (p->modulation) अणु
	हाल VSB_8:
		lgdt3305_ग_लिखो_reg(state, 0x030d, 0x00);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_1, 0x4f);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_2, 0x0c);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_3, 0xac);
		lgdt3305_ग_लिखो_reg(state, LGDT3305_CR_CTR_FREQ_4, 0xba);
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		lgdt3305_ग_लिखो_reg(state, 0x030d, 0x14);
		ret = lgdt3305_set_अगर(state, p);
		अगर (lg_fail(ret))
			जाओ fail;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	ret = lgdt3305_spectral_inversion(state, p,
					  state->cfg->spectral_inversion
					  ? 1 : 0);
	अगर (lg_fail(ret))
		जाओ fail;

	state->current_modulation = p->modulation;

	ret = lgdt3305_mpeg_mode(state, state->cfg->mpeg_mode);
	अगर (lg_fail(ret))
		जाओ fail;

	/* lgdt3305_mpeg_mode_polarity calls lgdt3305_soft_reset */
	ret = lgdt3305_mpeg_mode_polarity(state);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	lg_dbg("(%d, %d)\n", p->frequency, p->modulation);

	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
		अगर (lg_fail(ret))
			जाओ fail;
		state->current_frequency = p->frequency;
	पूर्ण

	ret = lgdt3305_set_modulation(state, p);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_passband_digital_agc(state, p);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lgdt3305_set_agc_घातer_ref(state, p);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lgdt3305_agc_setup(state, p);
	अगर (lg_fail(ret))
		जाओ fail;

	/* low अगर */
	ret = lgdt3305_ग_लिखो_reg(state, LGDT3305_GEN_CONTROL, 0x2f);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lgdt3305_set_reg_bit(state, LGDT3305_CR_CTR_FREQ_1, 6, 1);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_set_अगर(state, p);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lgdt3305_spectral_inversion(state, p,
					  state->cfg->spectral_inversion
					  ? 1 : 0);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lgdt3305_set_filter_extension(state, p);
	अगर (lg_fail(ret))
		जाओ fail;

	state->current_modulation = p->modulation;

	ret = lgdt3305_mpeg_mode(state, state->cfg->mpeg_mode);
	अगर (lg_fail(ret))
		जाओ fail;

	/* lgdt3305_mpeg_mode_polarity calls lgdt3305_soft_reset */
	ret = lgdt3305_mpeg_mode_polarity(state);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;

	lg_dbg("\n");

	p->modulation = state->current_modulation;
	p->frequency = state->current_frequency;
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3305_पढ़ो_cr_lock_status(काष्ठा lgdt3305_state *state,
					पूर्णांक *locked)
अणु
	u8 val;
	पूर्णांक ret;
	अक्षर *cr_lock_state = "";

	*locked = 0;

	ret = lgdt3305_पढ़ो_reg(state, LGDT3305_CR_LOCK_STATUS, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	चयन (state->current_modulation) अणु
	हाल QAM_256:
	हाल QAM_64:
		अगर (val & (1 << 1))
			*locked = 1;

		चयन (val & 0x07) अणु
		हाल 0:
			cr_lock_state = "QAM UNLOCK";
			अवरोध;
		हाल 4:
			cr_lock_state = "QAM 1stLock";
			अवरोध;
		हाल 6:
			cr_lock_state = "QAM 2ndLock";
			अवरोध;
		हाल 7:
			cr_lock_state = "QAM FinalLock";
			अवरोध;
		शेष:
			cr_lock_state = "CLOCKQAM-INVALID!";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल VSB_8:
		अगर (val & (1 << 7)) अणु
			*locked = 1;
			cr_lock_state = "CLOCKVSB";
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	lg_dbg("(%d) %s\n", *locked, cr_lock_state);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_पढ़ो_fec_lock_status(काष्ठा lgdt3305_state *state,
					 पूर्णांक *locked)
अणु
	u8 val;
	पूर्णांक ret, mpeg_lock, fec_lock, viterbi_lock;

	*locked = 0;

	चयन (state->current_modulation) अणु
	हाल QAM_256:
	हाल QAM_64:
		ret = lgdt3305_पढ़ो_reg(state,
					LGDT3305_FEC_LOCK_STATUS, &val);
		अगर (lg_fail(ret))
			जाओ fail;

		mpeg_lock    = (val & (1 << 0)) ? 1 : 0;
		fec_lock     = (val & (1 << 2)) ? 1 : 0;
		viterbi_lock = (val & (1 << 3)) ? 1 : 0;

		*locked = mpeg_lock && fec_lock && viterbi_lock;

		lg_dbg("(%d) %s%s%s\n", *locked,
		       mpeg_lock    ? "mpeg lock  "  : "",
		       fec_lock     ? "fec lock  "   : "",
		       viterbi_lock ? "viterbi lock" : "");
		अवरोध;
	हाल VSB_8:
	शेष:
		ret = -EINVAL;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3305_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	u8 val;
	पूर्णांक ret, संकेत, inlock, nofecerr, snrgood,
		cr_lock, fec_lock, sync_lock;

	*status = 0;

	ret = lgdt3305_पढ़ो_reg(state, LGDT3305_GEN_STATUS, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	संकेत    = (val & (1 << 4)) ? 1 : 0;
	inlock    = (val & (1 << 3)) ? 0 : 1;
	sync_lock = (val & (1 << 2)) ? 1 : 0;
	nofecerr  = (val & (1 << 1)) ? 1 : 0;
	snrgood   = (val & (1 << 0)) ? 1 : 0;

	lg_dbg("%s%s%s%s%s\n",
	       संकेत    ? "SIGNALEXIST " : "",
	       inlock    ? "INLOCK "      : "",
	       sync_lock ? "SYNCLOCK "    : "",
	       nofecerr  ? "NOFECERR "    : "",
	       snrgood   ? "SNRGOOD "     : "");

	ret = lgdt3305_पढ़ो_cr_lock_status(state, &cr_lock);
	अगर (lg_fail(ret))
		जाओ fail;

	अगर (संकेत)
		*status |= FE_HAS_SIGNAL;
	अगर (cr_lock)
		*status |= FE_HAS_CARRIER;
	अगर (nofecerr)
		*status |= FE_HAS_VITERBI;
	अगर (sync_lock)
		*status |= FE_HAS_SYNC;

	चयन (state->current_modulation) अणु
	हाल QAM_256:
	हाल QAM_64:
		/* संकेत bit is unreliable on the DT3304 in QAM mode */
		अगर (((LGDT3304 == state->cfg->demod_chip)) && (cr_lock))
			*status |= FE_HAS_SIGNAL;

		ret = lgdt3305_पढ़ो_fec_lock_status(state, &fec_lock);
		अगर (lg_fail(ret))
			जाओ fail;

		अगर (fec_lock)
			*status |= FE_HAS_LOCK;
		अवरोध;
	हाल VSB_8:
		अगर (inlock)
			*status |= FE_HAS_LOCK;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

/* borrowed from lgdt330x.c */
अटल u32 calculate_snr(u32 mse, u32 c)
अणु
	अगर (mse == 0) /* no संकेत */
		वापस 0;

	mse = पूर्णांकlog10(mse);
	अगर (mse > c) अणु
		/* Negative SNR, which is possible, but realisticly the
		demod will lose lock beक्रमe the संकेत माला_लो this bad.  The
		API only allows क्रम अचिन्हित values, so just वापस 0 */
		वापस 0;
	पूर्ण
	वापस 10*(c - mse);
पूर्ण

अटल पूर्णांक lgdt3305_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	u32 noise;	/* noise value */
	u32 c;		/* per-modulation SNR calculation स्थिरant */

	चयन (state->current_modulation) अणु
	हाल VSB_8:
#अगर_घोषित USE_PTMSE
		/* Use Phase Tracker Mean-Square Error Register */
		/* SNR क्रम ranges from -13.11 to +44.08 */
		noise =	((पढ़ो_reg(state, LGDT3305_PT_MSE_1) & 0x07) << 16) |
			(पढ़ो_reg(state, LGDT3305_PT_MSE_2) << 8) |
			(पढ़ो_reg(state, LGDT3305_PT_MSE_3) & 0xff);
		c = 73957994; /* log10(25*32^2)*2^24 */
#अन्यथा
		/* Use Equalizer Mean-Square Error Register */
		/* SNR क्रम ranges from -16.12 to +44.08 */
		noise =	((पढ़ो_reg(state, LGDT3305_EQ_MSE_1) & 0x0f) << 16) |
			(पढ़ो_reg(state, LGDT3305_EQ_MSE_2) << 8) |
			(पढ़ो_reg(state, LGDT3305_EQ_MSE_3) & 0xff);
		c = 73957994; /* log10(25*32^2)*2^24 */
#पूर्ण_अगर
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
		noise = (पढ़ो_reg(state, LGDT3305_CR_MSE_1) << 8) |
			(पढ़ो_reg(state, LGDT3305_CR_MSE_2) & 0xff);

		c = (state->current_modulation == QAM_64) ?
			97939837 : 98026066;
		/* log10(688128)*2^24 and log10(696320)*2^24 */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	state->snr = calculate_snr(noise, c);
	/* report SNR in dB * 10 */
	*snr = (state->snr / ((1 << 24) / 10));
	lg_dbg("noise = 0x%08x, snr = %d.%02d dB\n", noise,
	       state->snr >> 24, (((state->snr >> 8) & 0xffff) * 100) >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					 u16 *strength)
अणु
	/* borrowed from lgdt330x.c
	 *
	 * Calculate strength from SNR up to 35dB
	 * Even though the SNR can go higher than 35dB,
	 * there is some comक्रमt factor in having a range of
	 * strong संकेतs that can show at 100%
	 */
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	u16 snr;
	पूर्णांक ret;

	*strength = 0;

	ret = fe->ops.पढ़ो_snr(fe, &snr);
	अगर (lg_fail(ret))
		जाओ fail;
	/* Rather than use the 8.8 value snr, use state->snr which is 8.24 */
	/* scale the range 0 - 35*2^24 पूर्णांकo 0 - 65535 */
	अगर (state->snr >= 8960 * 0x10000)
		*strength = 0xffff;
	अन्यथा
		*strength = state->snr / 8960;
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3305_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	*ber = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;

	*ucblocks =
		(पढ़ो_reg(state, LGDT3305_FEC_PKT_ERR_1) << 8) |
		(पढ़ो_reg(state, LGDT3305_FEC_PKT_ERR_2) & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3305_get_tune_settings(काष्ठा dvb_frontend *fe,
				      काष्ठा dvb_frontend_tune_settings
					*fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 500;
	lg_dbg("\n");
	वापस 0;
पूर्ण

अटल व्योम lgdt3305_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt3305_state *state = fe->demodulator_priv;
	lg_dbg("\n");
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3304_ops;
अटल स्थिर काष्ठा dvb_frontend_ops lgdt3305_ops;

काष्ठा dvb_frontend *lgdt3305_attach(स्थिर काष्ठा lgdt3305_config *config,
				     काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा lgdt3305_state *state = शून्य;
	पूर्णांक ret;
	u8 val;

	lg_dbg("(%d-%04x)\n",
	       i2c_adap ? i2c_adapter_id(i2c_adap) : 0,
	       config ? config->i2c_addr : 0);

	state = kzalloc(माप(काष्ठा lgdt3305_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ fail;

	state->cfg = config;
	state->i2c_adap = i2c_adap;

	चयन (config->demod_chip) अणु
	हाल LGDT3304:
		स_नकल(&state->frontend.ops, &lgdt3304_ops,
		       माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	हाल LGDT3305:
		स_नकल(&state->frontend.ops, &lgdt3305_ops,
		       माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण
	state->frontend.demodulator_priv = state;

	/* verअगरy that we're talking to a lg dt3304/5 */
	ret = lgdt3305_पढ़ो_reg(state, LGDT3305_GEN_CTRL_2, &val);
	अगर ((lg_fail(ret)) | (val == 0))
		जाओ fail;
	ret = lgdt3305_ग_लिखो_reg(state, 0x0808, 0x80);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lgdt3305_पढ़ो_reg(state, 0x0808, &val);
	अगर ((lg_fail(ret)) | (val != 0x80))
		जाओ fail;
	ret = lgdt3305_ग_लिखो_reg(state, 0x0808, 0x00);
	अगर (lg_fail(ret))
		जाओ fail;

	state->current_frequency = -1;
	state->current_modulation = -1;

	वापस &state->frontend;
fail:
	lg_warn("unable to detect %s hardware\n",
		config->demod_chip ? "LGDT3304" : "LGDT3305");
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(lgdt3305_attach);

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3304_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "LG Electronics LGDT3304 VSB/QAM Frontend",
		.frequency_min_hz      =  54 * MHz,
		.frequency_max_hz      = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,
	.i2c_gate_ctrl        = lgdt3305_i2c_gate_ctrl,
	.init                 = lgdt3305_init,
	.sleep                = lgdt3305_sleep,
	.set_frontend         = lgdt3304_set_parameters,
	.get_frontend         = lgdt3305_get_frontend,
	.get_tune_settings    = lgdt3305_get_tune_settings,
	.पढ़ो_status          = lgdt3305_पढ़ो_status,
	.पढ़ो_ber             = lgdt3305_पढ़ो_ber,
	.पढ़ो_संकेत_strength = lgdt3305_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lgdt3305_पढ़ो_snr,
	.पढ़ो_ucblocks        = lgdt3305_पढ़ो_ucblocks,
	.release              = lgdt3305_release,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3305_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "LG Electronics LGDT3305 VSB/QAM Frontend",
		.frequency_min_hz      =  54 * MHz,
		.frequency_max_hz      = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,
	.i2c_gate_ctrl        = lgdt3305_i2c_gate_ctrl,
	.init                 = lgdt3305_init,
	.sleep                = lgdt3305_sleep,
	.set_frontend         = lgdt3305_set_parameters,
	.get_frontend         = lgdt3305_get_frontend,
	.get_tune_settings    = lgdt3305_get_tune_settings,
	.पढ़ो_status          = lgdt3305_पढ़ो_status,
	.पढ़ो_ber             = lgdt3305_पढ़ो_ber,
	.पढ़ो_संकेत_strength = lgdt3305_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lgdt3305_पढ़ो_snr,
	.पढ़ो_ucblocks        = lgdt3305_पढ़ो_ucblocks,
	.release              = lgdt3305_release,
पूर्ण;

MODULE_DESCRIPTION("LG Electronics LGDT3304/5 ATSC/QAM-B Demodulator Driver");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
