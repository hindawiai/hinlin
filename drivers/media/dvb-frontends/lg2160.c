<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम LG2160 - ATSC/MH
 *
 *    Copyright (C) 2010 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/dvb/frontend.h>
#समावेश "lg2160.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debug level (info=1, reg=2 (or-able))");

#घोषणा DBG_INFO 1
#घोषणा DBG_REG  2

#घोषणा lg_prपूर्णांकk(kern, fmt, arg...)					\
	prपूर्णांकk(kern "%s: " fmt, __func__, ##arg)

#घोषणा lg_info(fmt, arg...)	prपूर्णांकk(KERN_INFO "lg2160: " fmt, ##arg)
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

काष्ठा lg216x_state अणु
	काष्ठा i2c_adapter *i2c_adap;
	स्थिर काष्ठा lg2160_config *cfg;

	काष्ठा dvb_frontend frontend;

	u32 current_frequency;
	u8 parade_id;
	u8 fic_ver;
	अचिन्हित पूर्णांक last_reset;
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_ग_लिखो_reg(काष्ठा lg216x_state *state, u16 reg, u8 val)
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

अटल पूर्णांक lg216x_पढ़ो_reg(काष्ठा lg216x_state *state, u16 reg, u8 *val)
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

काष्ठा lg216x_reg अणु
	u16 reg;
	u8 val;
पूर्ण;

अटल पूर्णांक lg216x_ग_लिखो_regs(काष्ठा lg216x_state *state,
			     काष्ठा lg216x_reg *regs, पूर्णांक len)
अणु
	पूर्णांक i, ret;

	lg_reg("writing %d registers...\n", len);

	क्रम (i = 0; i < len; i++) अणु
		ret = lg216x_ग_लिखो_reg(state, regs[i].reg, regs[i].val);
		अगर (lg_fail(ret))
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lg216x_set_reg_bit(काष्ठा lg216x_state *state,
			      u16 reg, पूर्णांक bit, पूर्णांक onoff)
अणु
	u8 val;
	पूर्णांक ret;

	lg_reg("reg: 0x%04x, bit: %d, level: %d\n", reg, bit, onoff);

	ret = lg216x_पढ़ो_reg(state, reg, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= ~(1 << bit);
	val |= (onoff & 1) << bit;

	ret = lg216x_ग_लिखो_reg(state, reg, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	अगर (state->cfg->deny_i2c_rptr)
		वापस 0;

	lg_dbg("(%d)\n", enable);

	ret = lg216x_set_reg_bit(state, 0x0000, 0, enable ? 0 : 1);

	msleep(1);

	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_soft_reset(काष्ठा lg216x_state *state)
अणु
	पूर्णांक ret;

	lg_dbg("\n");

	ret = lg216x_ग_लिखो_reg(state, 0x0002, 0x00);
	अगर (lg_fail(ret))
		जाओ fail;

	msleep(20);
	ret = lg216x_ग_लिखो_reg(state, 0x0002, 0x01);
	अगर (lg_fail(ret))
		जाओ fail;

	state->last_reset = jअगरfies_to_msecs(jअगरfies);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_initialize(काष्ठा lg216x_state *state)
अणु
	पूर्णांक ret;

	अटल काष्ठा lg216x_reg lg2160_init[] = अणु
#अगर 0
		अणु .reg = 0x0015, .val = 0xe6 पूर्ण,
#अन्यथा
		अणु .reg = 0x0015, .val = 0xf7 पूर्ण,
		अणु .reg = 0x001b, .val = 0x52 पूर्ण,
		अणु .reg = 0x0208, .val = 0x00 पूर्ण,
		अणु .reg = 0x0209, .val = 0x82 पूर्ण,
		अणु .reg = 0x0210, .val = 0xf9 पूर्ण,
		अणु .reg = 0x020a, .val = 0x00 पूर्ण,
		अणु .reg = 0x020b, .val = 0x82 पूर्ण,
		अणु .reg = 0x020d, .val = 0x28 पूर्ण,
		अणु .reg = 0x020f, .val = 0x14 पूर्ण,
#पूर्ण_अगर
	पूर्ण;

	अटल काष्ठा lg216x_reg lg2161_init[] = अणु
		अणु .reg = 0x0000, .val = 0x41 पूर्ण,
		अणु .reg = 0x0001, .val = 0xfb पूर्ण,
		अणु .reg = 0x0216, .val = 0x00 पूर्ण,
		अणु .reg = 0x0219, .val = 0x00 पूर्ण,
		अणु .reg = 0x021b, .val = 0x55 पूर्ण,
		अणु .reg = 0x0606, .val = 0x0a पूर्ण,
	पूर्ण;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_ग_लिखो_regs(state,
					lg2160_init, ARRAY_SIZE(lg2160_init));
		अवरोध;
	हाल LG2161:
		ret = lg216x_ग_लिखो_regs(state,
					lg2161_init, ARRAY_SIZE(lg2161_init));
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_soft_reset(state);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_set_अगर(काष्ठा lg216x_state *state)
अणु
	u8 val;
	पूर्णांक ret;

	lg_dbg("%d KHz\n", state->cfg->अगर_khz);

	ret = lg216x_पढ़ो_reg(state, 0x0132, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xfb;
	val |= (0 == state->cfg->अगर_khz) ? 0x04 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0132, val);
	lg_fail(ret);

	/* अगर NOT zero IF, 6 MHz is the शेष */
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg2160_agc_fix(काष्ठा lg216x_state *state,
			  पूर्णांक अगर_agc_fix, पूर्णांक rf_agc_fix)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0100, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xf3;
	val |= (अगर_agc_fix) ? 0x08 : 0x00;
	val |= (rf_agc_fix) ? 0x04 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0100, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

#अगर 0
अटल पूर्णांक lg2160_agc_मुक्तze(काष्ठा lg216x_state *state,
			     पूर्णांक अगर_agc_मुक्तze, पूर्णांक rf_agc_मुक्तze)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0100, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xcf;
	val |= (अगर_agc_मुक्तze) ? 0x20 : 0x00;
	val |= (rf_agc_मुक्तze) ? 0x10 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0100, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lg2160_agc_polarity(काष्ठा lg216x_state *state,
			       पूर्णांक अगर_agc_polarity, पूर्णांक rf_agc_polarity)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0100, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xfc;
	val |= (अगर_agc_polarity) ? 0x02 : 0x00;
	val |= (rf_agc_polarity) ? 0x01 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0100, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2160_tuner_pwr_save_polarity(काष्ठा lg216x_state *state,
					  पूर्णांक polarity)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0008, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xfe;
	val |= (polarity) ? 0x01 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0008, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2160_spectrum_polarity(काष्ठा lg216x_state *state,
				    पूर्णांक inverted)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0132, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xfd;
	val |= (inverted) ? 0x02 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0132, val);
	lg_fail(ret);
fail:
	वापस lg216x_soft_reset(state);
पूर्ण

अटल पूर्णांक lg2160_tuner_pwr_save(काष्ठा lg216x_state *state, पूर्णांक onoff)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0007, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xbf;
	val |= (onoff) ? 0x40 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, 0x0007, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_set_parade(काष्ठा lg216x_state *state, पूर्णांक id)
अणु
	पूर्णांक ret;

	ret = lg216x_ग_लिखो_reg(state, 0x013e, id & 0x7f);
	अगर (lg_fail(ret))
		जाओ fail;

	state->parade_id = id & 0x7f;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_set_ensemble(काष्ठा lg216x_state *state, पूर्णांक id)
अणु
	पूर्णांक ret;
	u16 reg;
	u8 val;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		reg = 0x0400;
		अवरोध;
	हाल LG2161:
	शेष:
		reg = 0x0500;
		अवरोध;
	पूर्ण

	ret = lg216x_पढ़ो_reg(state, reg, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xfe;
	val |= (id) ? 0x01 : 0x00;

	ret = lg216x_ग_लिखो_reg(state, reg, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2160_set_spi_घड़ी(काष्ठा lg216x_state *state)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0014, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0xf3;
	val |= (state->cfg->spi_घड़ी << 2);

	ret = lg216x_ग_लिखो_reg(state, 0x0014, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2161_set_output_पूर्णांकerface(काष्ठा lg216x_state *state)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_reg(state, 0x0014, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	val &= ~0x07;
	val |= state->cfg->output_अगर; /* FIXME: needs sanity check */

	ret = lg216x_ग_लिखो_reg(state, 0x0014, val);
	lg_fail(ret);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_enable_fic(काष्ठा lg216x_state *state, पूर्णांक onoff)
अणु
	पूर्णांक ret;

	ret = lg216x_ग_लिखो_reg(state, 0x0017, 0x23);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_ग_लिखो_reg(state, 0x0016, 0xfc);
	अगर (lg_fail(ret))
		जाओ fail;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_ग_लिखो_reg(state, 0x0016,
				       0xfc | ((onoff) ? 0x02 : 0x00));
		अवरोध;
	हाल LG2161:
		ret = lg216x_ग_लिखो_reg(state, 0x0016, (onoff) ? 0x10 : 0x00);
		अवरोध;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_initialize(state);
	अगर (lg_fail(ret))
		जाओ fail;

	अगर (onoff) अणु
		ret = lg216x_ग_लिखो_reg(state, 0x0017, 0x03);
		lg_fail(ret);
	पूर्ण
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_get_fic_version(काष्ठा lg216x_state *state, u8 *ficver)
अणु
	u8 val;
	पूर्णांक ret;

	*ficver = 0xff; /* invalid value */

	ret = lg216x_पढ़ो_reg(state, 0x0128, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*ficver = (val >> 3) & 0x1f;
fail:
	वापस ret;
पूर्ण

#अगर 0
अटल पूर्णांक lg2160_get_parade_id(काष्ठा lg216x_state *state, u8 *id)
अणु
	u8 val;
	पूर्णांक ret;

	*id = 0xff; /* invalid value */

	ret = lg216x_पढ़ो_reg(state, 0x0123, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*id = val & 0x7f;
fail:
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lg216x_get_nog(काष्ठा lg216x_state *state, u8 *nog)
अणु
	u8 val;
	पूर्णांक ret;

	*nog = 0xff; /* invalid value */

	ret = lg216x_पढ़ो_reg(state, 0x0124, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*nog = ((val >> 4) & 0x07) + 1;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_get_tnog(काष्ठा lg216x_state *state, u8 *tnog)
अणु
	u8 val;
	पूर्णांक ret;

	*tnog = 0xff; /* invalid value */

	ret = lg216x_पढ़ो_reg(state, 0x0125, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*tnog = val & 0x1f;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_get_sgn(काष्ठा lg216x_state *state, u8 *sgn)
अणु
	u8 val;
	पूर्णांक ret;

	*sgn = 0xff; /* invalid value */

	ret = lg216x_पढ़ो_reg(state, 0x0124, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*sgn = val & 0x0f;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_get_prc(काष्ठा lg216x_state *state, u8 *prc)
अणु
	u8 val;
	पूर्णांक ret;

	*prc = 0xff; /* invalid value */

	ret = lg216x_पढ़ो_reg(state, 0x0125, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*prc = ((val >> 5) & 0x07) + 1;
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_get_rs_frame_mode(काष्ठा lg216x_state *state,
				    क्रमागत atscmh_rs_frame_mode *rs_framemode)
अणु
	u8 val;
	पूर्णांक ret;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_पढ़ो_reg(state, 0x0410, &val);
		अवरोध;
	हाल LG2161:
		ret = lg216x_पढ़ो_reg(state, 0x0513, &val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	चयन ((val >> 4) & 0x03) अणु
#अगर 1
	शेष:
#पूर्ण_अगर
	हाल 0x00:
		*rs_framemode = ATSCMH_RSFRAME_PRI_ONLY;
		अवरोध;
	हाल 0x01:
		*rs_framemode = ATSCMH_RSFRAME_PRI_SEC;
		अवरोध;
#अगर 0
	शेष:
		*rs_framemode = ATSCMH_RSFRAME_RES;
		अवरोध;
#पूर्ण_अगर
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक lg216x_get_rs_frame_ensemble(काष्ठा lg216x_state *state,
				 क्रमागत atscmh_rs_frame_ensemble *rs_frame_ens)
अणु
	u8 val;
	पूर्णांक ret;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_पढ़ो_reg(state, 0x0400, &val);
		अवरोध;
	हाल LG2161:
		ret = lg216x_पढ़ो_reg(state, 0x0500, &val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	val &= 0x01;
	*rs_frame_ens = (क्रमागत atscmh_rs_frame_ensemble) val;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_get_rs_code_mode(काष्ठा lg216x_state *state,
				   क्रमागत atscmh_rs_code_mode *rs_code_pri,
				   क्रमागत atscmh_rs_code_mode *rs_code_sec)
अणु
	u8 val;
	पूर्णांक ret;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_पढ़ो_reg(state, 0x0410, &val);
		अवरोध;
	हाल LG2161:
		ret = lg216x_पढ़ो_reg(state, 0x0513, &val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	*rs_code_pri = (क्रमागत atscmh_rs_code_mode) ((val >> 2) & 0x03);
	*rs_code_sec = (क्रमागत atscmh_rs_code_mode) (val & 0x03);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_get_sccc_block_mode(काष्ठा lg216x_state *state,
				      क्रमागत atscmh_sccc_block_mode *sccc_block)
अणु
	u8 val;
	पूर्णांक ret;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_पढ़ो_reg(state, 0x0315, &val);
		अवरोध;
	हाल LG2161:
		ret = lg216x_पढ़ो_reg(state, 0x0511, &val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	चयन (val & 0x03) अणु
	हाल 0x00:
		*sccc_block = ATSCMH_SCCC_BLK_SEP;
		अवरोध;
	हाल 0x01:
		*sccc_block = ATSCMH_SCCC_BLK_COMB;
		अवरोध;
	शेष:
		*sccc_block = ATSCMH_SCCC_BLK_RES;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_get_sccc_code_mode(काष्ठा lg216x_state *state,
				     क्रमागत atscmh_sccc_code_mode *mode_a,
				     क्रमागत atscmh_sccc_code_mode *mode_b,
				     क्रमागत atscmh_sccc_code_mode *mode_c,
				     क्रमागत atscmh_sccc_code_mode *mode_d)
अणु
	u8 val;
	पूर्णांक ret;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_पढ़ो_reg(state, 0x0316, &val);
		अवरोध;
	हाल LG2161:
		ret = lg216x_पढ़ो_reg(state, 0x0512, &val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	चयन ((val >> 6) & 0x03) अणु
	हाल 0x00:
		*mode_a = ATSCMH_SCCC_CODE_HLF;
		अवरोध;
	हाल 0x01:
		*mode_a = ATSCMH_SCCC_CODE_QTR;
		अवरोध;
	शेष:
		*mode_a = ATSCMH_SCCC_CODE_RES;
		अवरोध;
	पूर्ण

	चयन ((val >> 4) & 0x03) अणु
	हाल 0x00:
		*mode_b = ATSCMH_SCCC_CODE_HLF;
		अवरोध;
	हाल 0x01:
		*mode_b = ATSCMH_SCCC_CODE_QTR;
		अवरोध;
	शेष:
		*mode_b = ATSCMH_SCCC_CODE_RES;
		अवरोध;
	पूर्ण

	चयन ((val >> 2) & 0x03) अणु
	हाल 0x00:
		*mode_c = ATSCMH_SCCC_CODE_HLF;
		अवरोध;
	हाल 0x01:
		*mode_c = ATSCMH_SCCC_CODE_QTR;
		अवरोध;
	शेष:
		*mode_c = ATSCMH_SCCC_CODE_RES;
		अवरोध;
	पूर्ण

	चयन (val & 0x03) अणु
	हाल 0x00:
		*mode_d = ATSCMH_SCCC_CODE_HLF;
		अवरोध;
	हाल 0x01:
		*mode_d = ATSCMH_SCCC_CODE_QTR;
		अवरोध;
	शेष:
		*mode_d = ATSCMH_SCCC_CODE_RES;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

#अगर 0
अटल पूर्णांक lg216x_पढ़ो_fic_err_count(काष्ठा lg216x_state *state, u8 *err)
अणु
	u8 fic_err;
	पूर्णांक ret;

	*err = 0;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg216x_पढ़ो_reg(state, 0x0012, &fic_err);
		अवरोध;
	हाल LG2161:
		ret = lg216x_पढ़ो_reg(state, 0x001e, &fic_err);
		अवरोध;
	पूर्ण
	अगर (lg_fail(ret))
		जाओ fail;

	*err = fic_err;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2160_पढ़ो_crc_err_count(काष्ठा lg216x_state *state, u16 *err)
अणु
	u8 crc_err1, crc_err2;
	पूर्णांक ret;

	*err = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0411, &crc_err1);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_पढ़ो_reg(state, 0x0412, &crc_err2);
	अगर (lg_fail(ret))
		जाओ fail;

	*err = (u16)(((crc_err2 & 0x0f) << 8) | crc_err1);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2161_पढ़ो_crc_err_count(काष्ठा lg216x_state *state, u16 *err)
अणु
	u8 crc_err;
	पूर्णांक ret;

	*err = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0612, &crc_err);
	अगर (lg_fail(ret))
		जाओ fail;

	*err = (u16)crc_err;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_पढ़ो_crc_err_count(काष्ठा lg216x_state *state, u16 *err)
अणु
	पूर्णांक ret;
	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg2160_पढ़ो_crc_err_count(state, err);
		अवरोध;
	हाल LG2161:
		ret = lg2161_पढ़ो_crc_err_count(state, err);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lg2160_पढ़ो_rs_err_count(काष्ठा lg216x_state *state, u16 *err)
अणु
	u8 rs_err1, rs_err2;
	पूर्णांक ret;

	*err = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0413, &rs_err1);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_पढ़ो_reg(state, 0x0414, &rs_err2);
	अगर (lg_fail(ret))
		जाओ fail;

	*err = (u16)(((rs_err2 & 0x0f) << 8) | rs_err1);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2161_पढ़ो_rs_err_count(काष्ठा lg216x_state *state, u16 *err)
अणु
	u8 rs_err1, rs_err2;
	पूर्णांक ret;

	*err = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0613, &rs_err1);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_पढ़ो_reg(state, 0x0614, &rs_err2);
	अगर (lg_fail(ret))
		जाओ fail;

	*err = (u16)((rs_err1 << 8) | rs_err2);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_पढ़ो_rs_err_count(काष्ठा lg216x_state *state, u16 *err)
अणु
	पूर्णांक ret;
	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg2160_पढ़ो_rs_err_count(state, err);
		अवरोध;
	हाल LG2161:
		ret = lg2161_पढ़ो_rs_err_count(state, err);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_get_frontend(काष्ठा dvb_frontend *fe,
			       काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	lg_dbg("\n");

	c->modulation = VSB_8;
	c->frequency = state->current_frequency;
	c->delivery_प्रणाली = SYS_ATSCMH;

	ret = lg216x_get_fic_version(state,
				     &c->atscmh_fic_ver);
	अगर (lg_fail(ret))
		जाओ fail;
	अगर (state->fic_ver != c->atscmh_fic_ver) अणु
		state->fic_ver = c->atscmh_fic_ver;

#अगर 0
		ret = lg2160_get_parade_id(state,
				&c->atscmh_parade_id);
		अगर (lg_fail(ret))
			जाओ fail;
/* #अन्यथा */
		c->atscmh_parade_id = state->parade_id;
#पूर्ण_अगर
		ret = lg216x_get_nog(state,
				     &c->atscmh_nog);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_tnog(state,
				      &c->atscmh_tnog);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_sgn(state,
				     &c->atscmh_sgn);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_prc(state,
				     &c->atscmh_prc);
		अगर (lg_fail(ret))
			जाओ fail;

		ret = lg216x_get_rs_frame_mode(state,
			(क्रमागत atscmh_rs_frame_mode *)
			&c->atscmh_rs_frame_mode);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_rs_frame_ensemble(state,
			(क्रमागत atscmh_rs_frame_ensemble *)
			&c->atscmh_rs_frame_ensemble);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_rs_code_mode(state,
			(क्रमागत atscmh_rs_code_mode *)
			&c->atscmh_rs_code_mode_pri,
			(क्रमागत atscmh_rs_code_mode *)
			&c->atscmh_rs_code_mode_sec);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_sccc_block_mode(state,
			(क्रमागत atscmh_sccc_block_mode *)
			&c->atscmh_sccc_block_mode);
		अगर (lg_fail(ret))
			जाओ fail;
		ret = lg216x_get_sccc_code_mode(state,
			(क्रमागत atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_a,
			(क्रमागत atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_b,
			(क्रमागत atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_c,
			(क्रमागत atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_d);
		अगर (lg_fail(ret))
			जाओ fail;
	पूर्ण
#अगर 0
	ret = lg216x_पढ़ो_fic_err_count(state,
				(u8 *)&c->atscmh_fic_err);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lg216x_पढ़ो_crc_err_count(state,
				&c->atscmh_crc_err);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lg216x_पढ़ो_rs_err_count(state,
				&c->atscmh_rs_err);
	अगर (lg_fail(ret))
		जाओ fail;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		अगर (((c->atscmh_rs_err >= 240) &&
		     (c->atscmh_crc_err >= 240)) &&
		    ((jअगरfies_to_msecs(jअगरfies) - state->last_reset) > 6000))
			ret = lg216x_soft_reset(state);
		अवरोध;
	हाल LG2161:
		/* no fix needed here (as far as we know) */
		ret = 0;
		अवरोध;
	पूर्ण
	lg_fail(ret);
#पूर्ण_अगर
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2160_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;

	lg_dbg("(%d)\n", fe->dtv_property_cache.frequency);

	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
		अगर (lg_fail(ret))
			जाओ fail;
		state->current_frequency = fe->dtv_property_cache.frequency;
	पूर्ण

	ret = lg2160_agc_fix(state, 0, 0);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lg2160_agc_polarity(state, 0, 0);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lg2160_tuner_pwr_save_polarity(state, 1);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lg216x_set_अगर(state);
	अगर (lg_fail(ret))
		जाओ fail;
	ret = lg2160_spectrum_polarity(state, state->cfg->spectral_inversion);
	अगर (lg_fail(ret))
		जाओ fail;

	/* be tuned beक्रमe this poपूर्णांक */
	ret = lg216x_soft_reset(state);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg2160_tuner_pwr_save(state, 0);
	अगर (lg_fail(ret))
		जाओ fail;

	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg2160_set_spi_घड़ी(state);
		अगर (lg_fail(ret))
			जाओ fail;
		अवरोध;
	हाल LG2161:
		ret = lg2161_set_output_पूर्णांकerface(state);
		अगर (lg_fail(ret))
			जाओ fail;
		अवरोध;
	पूर्ण

	ret = lg216x_set_parade(state, fe->dtv_property_cache.atscmh_parade_id);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_set_ensemble(state,
			fe->dtv_property_cache.atscmh_rs_frame_ensemble);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_initialize(state);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_enable_fic(state, 1);
	lg_fail(ret);

	lg216x_get_frontend(fe, c);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg2160_पढ़ो_lock_status(काष्ठा lg216x_state *state,
				   पूर्णांक *acq_lock, पूर्णांक *sync_lock)
अणु
	u8 val;
	पूर्णांक ret;

	*acq_lock = 0;
	*sync_lock = 0;

	ret = lg216x_पढ़ो_reg(state, 0x011b, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*sync_lock = (val & 0x20) ? 0 : 1;
	*acq_lock  = (val & 0x40) ? 0 : 1;
fail:
	वापस ret;
पूर्ण

#अगर_घोषित USE_LG2161_LOCK_BITS
अटल पूर्णांक lg2161_पढ़ो_lock_status(काष्ठा lg216x_state *state,
				   पूर्णांक *acq_lock, पूर्णांक *sync_lock)
अणु
	u8 val;
	पूर्णांक ret;

	*acq_lock = 0;
	*sync_lock = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0304, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*sync_lock = (val & 0x80) ? 0 : 1;

	ret = lg216x_पढ़ो_reg(state, 0x011b, &val);
	अगर (lg_fail(ret))
		जाओ fail;

	*acq_lock  = (val & 0x40) ? 0 : 1;
fail:
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lg216x_पढ़ो_lock_status(काष्ठा lg216x_state *state,
				   पूर्णांक *acq_lock, पूर्णांक *sync_lock)
अणु
#अगर_घोषित USE_LG2161_LOCK_BITS
	पूर्णांक ret;
	चयन (state->cfg->lg_chip) अणु
	हाल LG2160:
		ret = lg2160_पढ़ो_lock_status(state, acq_lock, sync_lock);
		अवरोध;
	हाल LG2161:
		ret = lg2161_पढ़ो_lock_status(state, acq_lock, sync_lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
#अन्यथा
	वापस lg2160_पढ़ो_lock_status(state, acq_lock, sync_lock);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक lg216x_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	पूर्णांक ret, acq_lock, sync_lock;

	*status = 0;

	ret = lg216x_पढ़ो_lock_status(state, &acq_lock, &sync_lock);
	अगर (lg_fail(ret))
		जाओ fail;

	lg_dbg("%s%s\n",
	       acq_lock  ? "SIGNALEXIST " : "",
	       sync_lock ? "SYNCLOCK"     : "");

	अगर (acq_lock)
		*status |= FE_HAS_SIGNAL;
	अगर (sync_lock)
		*status |= FE_HAS_SYNC;

	अगर (*status)
		*status |= FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_LOCK;

fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg2160_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	u8 snr1, snr2;
	पूर्णांक ret;

	*snr = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0202, &snr1);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_पढ़ो_reg(state, 0x0203, &snr2);
	अगर (lg_fail(ret))
		जाओ fail;

	अगर ((snr1 == 0xba) || (snr2 == 0xdf))
		*snr = 0;
	अन्यथा
#अगर 1
	*snr =  ((snr1 >> 4) * 100) + ((snr1 & 0x0f) * 10) + (snr2 >> 4);
#अन्यथा /* BCD */
	*snr =  (snr2 | (snr1 << 8));
#पूर्ण_अगर
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg2161_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	u8 snr1, snr2;
	पूर्णांक ret;

	*snr = 0;

	ret = lg216x_पढ़ो_reg(state, 0x0302, &snr1);
	अगर (lg_fail(ret))
		जाओ fail;

	ret = lg216x_पढ़ो_reg(state, 0x0303, &snr2);
	अगर (lg_fail(ret))
		जाओ fail;

	अगर ((snr1 == 0xba) || (snr2 == 0xfd))
		*snr = 0;
	अन्यथा

	*snr =  ((snr1 >> 4) * 100) + ((snr1 & 0x0f) * 10) + (snr2 & 0x0f);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lg216x_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
				       u16 *strength)
अणु
#अगर 0
	/* borrowed from lgdt330x.c
	 *
	 * Calculate strength from SNR up to 35dB
	 * Even though the SNR can go higher than 35dB,
	 * there is some comक्रमt factor in having a range of
	 * strong संकेतs that can show at 100%
	 */
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	u16 snr;
	पूर्णांक ret;
#पूर्ण_अगर
	*strength = 0;
#अगर 0
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
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lg216x_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
#अगर 0
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	ret = lg216x_पढ़ो_rs_err_count(state,
				       &fe->dtv_property_cache.atscmh_rs_err);
	अगर (lg_fail(ret))
		जाओ fail;

	*ucblocks = fe->dtv_property_cache.atscmh_rs_err;
fail:
#अन्यथा
	*ucblocks = 0;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक lg216x_get_tune_settings(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_frontend_tune_settings
				    *fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 500;
	lg_dbg("\n");
	वापस 0;
पूर्ण

अटल व्योम lg216x_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lg216x_state *state = fe->demodulator_priv;
	lg_dbg("\n");
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops lg2160_ops = अणु
	.delsys = अणु SYS_ATSCMH पूर्ण,
	.info = अणु
		.name = "LG Electronics LG2160 ATSC/MH Frontend",
		.frequency_min_hz      =  54 * MHz,
		.frequency_max_hz      = 858 * MHz,
		.frequency_stepsize_hz = 62500,
	पूर्ण,
	.i2c_gate_ctrl        = lg216x_i2c_gate_ctrl,
#अगर 0
	.init                 = lg216x_init,
	.sleep                = lg216x_sleep,
#पूर्ण_अगर
	.set_frontend         = lg2160_set_frontend,
	.get_frontend         = lg216x_get_frontend,
	.get_tune_settings    = lg216x_get_tune_settings,
	.पढ़ो_status          = lg216x_पढ़ो_status,
#अगर 0
	.पढ़ो_ber             = lg216x_पढ़ो_ber,
#पूर्ण_अगर
	.पढ़ो_संकेत_strength = lg216x_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lg2160_पढ़ो_snr,
	.पढ़ो_ucblocks        = lg216x_पढ़ो_ucblocks,
	.release              = lg216x_release,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops lg2161_ops = अणु
	.delsys = अणु SYS_ATSCMH पूर्ण,
	.info = अणु
		.name = "LG Electronics LG2161 ATSC/MH Frontend",
		.frequency_min_hz      =  54 * MHz,
		.frequency_max_hz      = 858 * MHz,
		.frequency_stepsize_hz = 62500,
	पूर्ण,
	.i2c_gate_ctrl        = lg216x_i2c_gate_ctrl,
#अगर 0
	.init                 = lg216x_init,
	.sleep                = lg216x_sleep,
#पूर्ण_अगर
	.set_frontend         = lg2160_set_frontend,
	.get_frontend         = lg216x_get_frontend,
	.get_tune_settings    = lg216x_get_tune_settings,
	.पढ़ो_status          = lg216x_पढ़ो_status,
#अगर 0
	.पढ़ो_ber             = lg216x_पढ़ो_ber,
#पूर्ण_अगर
	.पढ़ो_संकेत_strength = lg216x_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lg2161_पढ़ो_snr,
	.पढ़ो_ucblocks        = lg216x_पढ़ो_ucblocks,
	.release              = lg216x_release,
पूर्ण;

काष्ठा dvb_frontend *lg2160_attach(स्थिर काष्ठा lg2160_config *config,
				   काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा lg216x_state *state = शून्य;

	lg_dbg("(%d-%04x)\n",
	       i2c_adap ? i2c_adapter_id(i2c_adap) : 0,
	       config ? config->i2c_addr : 0);

	state = kzalloc(माप(काष्ठा lg216x_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->cfg = config;
	state->i2c_adap = i2c_adap;
	state->fic_ver = 0xff;
	state->parade_id = 0xff;

	चयन (config->lg_chip) अणु
	शेष:
		lg_warn("invalid chip requested, defaulting to LG2160");
		fallthrough;
	हाल LG2160:
		स_नकल(&state->frontend.ops, &lg2160_ops,
		       माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	हाल LG2161:
		स_नकल(&state->frontend.ops, &lg2161_ops,
		       माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	पूर्ण

	state->frontend.demodulator_priv = state;
	state->current_frequency = -1;
	/* parade 1 by शेष */
	state->frontend.dtv_property_cache.atscmh_parade_id = 1;

	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(lg2160_attach);

MODULE_DESCRIPTION("LG Electronics LG216x ATSC/MH Demodulator Driver");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.3");
