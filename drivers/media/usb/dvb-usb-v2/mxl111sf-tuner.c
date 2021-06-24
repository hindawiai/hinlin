<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  mxl111sf-tuner.c - driver क्रम the MaxLinear MXL111SF CMOS tuner
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश "mxl111sf-tuner.h"
#समावेश "mxl111sf-phy.h"
#समावेश "mxl111sf-reg.h"

/* debug */
अटल पूर्णांक mxl111sf_tuner_debug;
module_param_named(debug, mxl111sf_tuner_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info (or-able)).");

#घोषणा mxl_dbg(fmt, arg...) \
	अगर (mxl111sf_tuner_debug) \
		mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg)

/* ------------------------------------------------------------------------ */

काष्ठा mxl111sf_tuner_state अणु
	काष्ठा mxl111sf_state *mxl_state;

	स्थिर काष्ठा mxl111sf_tuner_config *cfg;

	क्रमागत mxl_अगर_freq अगर_freq;

	u32 frequency;
	u32 bandwidth;
पूर्ण;

अटल पूर्णांक mxl111sf_tuner_पढ़ो_reg(काष्ठा mxl111sf_tuner_state *state,
				   u8 addr, u8 *data)
अणु
	वापस (state->cfg->पढ़ो_reg) ?
		state->cfg->पढ़ो_reg(state->mxl_state, addr, data) :
		-EINVAL;
पूर्ण

अटल पूर्णांक mxl111sf_tuner_ग_लिखो_reg(काष्ठा mxl111sf_tuner_state *state,
				    u8 addr, u8 data)
अणु
	वापस (state->cfg->ग_लिखो_reg) ?
		state->cfg->ग_लिखो_reg(state->mxl_state, addr, data) :
		-EINVAL;
पूर्ण

अटल पूर्णांक mxl111sf_tuner_program_regs(काष्ठा mxl111sf_tuner_state *state,
			       काष्ठा mxl111sf_reg_ctrl_info *ctrl_reg_info)
अणु
	वापस (state->cfg->program_regs) ?
		state->cfg->program_regs(state->mxl_state, ctrl_reg_info) :
		-EINVAL;
पूर्ण

अटल पूर्णांक mxl1x1sf_tuner_top_master_ctrl(काष्ठा mxl111sf_tuner_state *state,
					  पूर्णांक onoff)
अणु
	वापस (state->cfg->top_master_ctrl) ?
		state->cfg->top_master_ctrl(state->mxl_state, onoff) :
		-EINVAL;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल काष्ठा mxl111sf_reg_ctrl_info mxl_phy_tune_rf[] = अणु
	अणु0x1d, 0x7f, 0x00पूर्ण, /* channel bandwidth section 1/2/3,
			       DIG_MODEINDEX, _A, _CSF, */
	अणु0x1e, 0xff, 0x00पूर्ण, /* channel frequency (lo and fractional) */
	अणु0x1f, 0xff, 0x00पूर्ण, /* channel frequency (hi क्रम पूर्णांकeger portion) */
	अणु0,    0,    0पूर्ण
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल काष्ठा mxl111sf_reg_ctrl_info *mxl111sf_calc_phy_tune_regs(u32 freq,
								  u8 bw)
अणु
	u8 filt_bw;

	/* set channel bandwidth */
	चयन (bw) अणु
	हाल 0: /* ATSC */
		filt_bw = 25;
		अवरोध;
	हाल 1: /* QAM */
		filt_bw = 69;
		अवरोध;
	हाल 6:
		filt_bw = 21;
		अवरोध;
	हाल 7:
		filt_bw = 42;
		अवरोध;
	हाल 8:
		filt_bw = 63;
		अवरोध;
	शेष:
		pr_err("%s: invalid bandwidth setting!", __func__);
		वापस शून्य;
	पूर्ण

	/* calculate RF channel */
	freq /= 1000000;

	freq *= 64;
#अगर 0
	/* करो round */
	freq += 0.5;
#पूर्ण_अगर
	/* set bandwidth */
	mxl_phy_tune_rf[0].data = filt_bw;

	/* set RF */
	mxl_phy_tune_rf[1].data = (freq & 0xff);
	mxl_phy_tune_rf[2].data = (freq >> 8) & 0xff;

	/* start tune */
	वापस mxl_phy_tune_rf;
पूर्ण

अटल पूर्णांक mxl1x1sf_tuner_set_अगर_output_freq(काष्ठा mxl111sf_tuner_state *state)
अणु
	पूर्णांक ret;
	u8 ctrl;
#अगर 0
	u16 अगरfcw;
	u32 अगर_freq;
#पूर्ण_अगर
	mxl_dbg("(IF polarity = %d, IF freq = 0x%02x)",
		state->cfg->invert_spectrum, state->cfg->अगर_freq);

	/* set IF polarity */
	ctrl = state->cfg->invert_spectrum;

	ctrl |= state->cfg->अगर_freq;

	ret = mxl111sf_tuner_ग_लिखो_reg(state, V6_TUNER_IF_SEL_REG, ctrl);
	अगर (mxl_fail(ret))
		जाओ fail;

#अगर 0
	अगर_freq /= 1000000;

	/* करो round */
	अगर_freq += 0.5;

	अगर (MXL_IF_LO == state->cfg->अगर_freq) अणु
		ctrl = 0x08;
		अगरfcw = (u16)(अगर_freq / (108 * 4096));
	पूर्ण अन्यथा अगर (MXL_IF_HI == state->cfg->अगर_freq) अणु
		ctrl = 0x08;
		अगरfcw = (u16)(अगर_freq / (216 * 4096));
	पूर्ण अन्यथा अणु
		ctrl = 0;
		अगरfcw = 0;
	पूर्ण

	ctrl |= (अगरfcw >> 8);
#पूर्ण_अगर
	ret = mxl111sf_tuner_पढ़ो_reg(state, V6_TUNER_IF_FCW_BYP_REG, &ctrl);
	अगर (mxl_fail(ret))
		जाओ fail;

	ctrl &= 0xf0;
	ctrl |= 0x90;

	ret = mxl111sf_tuner_ग_लिखो_reg(state, V6_TUNER_IF_FCW_BYP_REG, ctrl);
	अगर (mxl_fail(ret))
		जाओ fail;

#अगर 0
	ctrl = अगरfcw & 0x00ff;
#पूर्ण_अगर
	ret = mxl111sf_tuner_ग_लिखो_reg(state, V6_TUNER_IF_FCW_REG, ctrl);
	अगर (mxl_fail(ret))
		जाओ fail;

	state->अगर_freq = state->cfg->अगर_freq;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl1x1sf_tune_rf(काष्ठा dvb_frontend *fe, u32 freq, u8 bw)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	अटल काष्ठा mxl111sf_reg_ctrl_info *reg_ctrl_array;
	पूर्णांक ret;
	u8 mxl_mode;

	mxl_dbg("(freq = %d, bw = 0x%x)", freq, bw);

	/* stop tune */
	ret = mxl111sf_tuner_ग_लिखो_reg(state, START_TUNE_REG, 0);
	अगर (mxl_fail(ret))
		जाओ fail;

	/* check device mode */
	ret = mxl111sf_tuner_पढ़ो_reg(state, MXL_MODE_REG, &mxl_mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	/* Fill out रेजिस्टरs क्रम channel tune */
	reg_ctrl_array = mxl111sf_calc_phy_tune_regs(freq, bw);
	अगर (!reg_ctrl_array)
		वापस -EINVAL;

	ret = mxl111sf_tuner_program_regs(state, reg_ctrl_array);
	अगर (mxl_fail(ret))
		जाओ fail;

	अगर ((mxl_mode & MXL_DEV_MODE_MASK) == MXL_TUNER_MODE) अणु
		/* IF tuner mode only */
		mxl1x1sf_tuner_top_master_ctrl(state, 0);
		mxl1x1sf_tuner_top_master_ctrl(state, 1);
		mxl1x1sf_tuner_set_अगर_output_freq(state);
	पूर्ण

	ret = mxl111sf_tuner_ग_लिखो_reg(state, START_TUNE_REG, 1);
	अगर (mxl_fail(ret))
		जाओ fail;

	अगर (state->cfg->ant_hunt)
		state->cfg->ant_hunt(fe);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl1x1sf_tuner_get_lock_status(काष्ठा mxl111sf_tuner_state *state,
					  पूर्णांक *rf_synth_lock,
					  पूर्णांक *ref_synth_lock)
अणु
	पूर्णांक ret;
	u8 data;

	*rf_synth_lock = 0;
	*ref_synth_lock = 0;

	ret = mxl111sf_tuner_पढ़ो_reg(state, V6_RF_LOCK_STATUS_REG, &data);
	अगर (mxl_fail(ret))
		जाओ fail;

	*ref_synth_lock = ((data & 0x03) == 0x03) ? 1 : 0;
	*rf_synth_lock  = ((data & 0x0c) == 0x0c) ? 1 : 0;
fail:
	वापस ret;
पूर्ण

#अगर 0
अटल पूर्णांक mxl1x1sf_tuner_loop_thru_ctrl(काष्ठा mxl111sf_tuner_state *state,
					 पूर्णांक onoff)
अणु
	वापस mxl111sf_tuner_ग_लिखो_reg(state, V6_TUNER_LOOP_THRU_CTRL_REG,
					onoff ? 1 : 0);
पूर्ण
#पूर्ण_अगर

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl111sf_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys  = c->delivery_प्रणाली;
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	पूर्णांक ret;
	u8 bw;

	mxl_dbg("()");

	चयन (delsys) अणु
	हाल SYS_ATSC:
	हाल SYS_ATSCMH:
		bw = 0; /* ATSC */
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		bw = 1; /* US CABLE */
		अवरोध;
	हाल SYS_DVBT:
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			bw = 6;
			अवरोध;
		हाल 7000000:
			bw = 7;
			अवरोध;
		हाल 8000000:
			bw = 8;
			अवरोध;
		शेष:
			pr_err("%s: bandwidth not set!", __func__);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s: modulation type not supported!", __func__);
		वापस -EINVAL;
	पूर्ण
	ret = mxl1x1sf_tune_rf(fe, c->frequency, bw);
	अगर (mxl_fail(ret))
		जाओ fail;

	state->frequency = c->frequency;
	state->bandwidth = c->bandwidth_hz;
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

#अगर 0
अटल पूर्णांक mxl111sf_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	पूर्णांक ret;

	/* wake from standby handled by usb driver */

	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	पूर्णांक ret;

	/* enter standby mode handled by usb driver */

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl111sf_tuner_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	पूर्णांक rf_locked, ref_locked, ret;

	*status = 0;

	ret = mxl1x1sf_tuner_get_lock_status(state, &rf_locked, &ref_locked);
	अगर (mxl_fail(ret))
		जाओ fail;
	mxl_info("%s%s", rf_locked ? "rf locked " : "",
		 ref_locked ? "ref locked" : "");

	अगर ((rf_locked) || (ref_locked))
		*status |= TUNER_STATUS_LOCKED;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_get_rf_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	u8 val1, val2;
	पूर्णांक ret;

	*strength = 0;

	ret = mxl111sf_tuner_ग_लिखो_reg(state, 0x00, 0x02);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_tuner_पढ़ो_reg(state, V6_DIG_RF_PWR_LSB_REG, &val1);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_tuner_पढ़ो_reg(state, V6_DIG_RF_PWR_MSB_REG, &val2);
	अगर (mxl_fail(ret))
		जाओ fail;

	*strength = val1 | ((val2 & 0x07) << 8);
fail:
	ret = mxl111sf_tuner_ग_लिखो_reg(state, 0x00, 0x00);
	mxl_fail(ret);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl111sf_tuner_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	*frequency = state->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_tuner_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	*bandwidth = state->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_tuner_get_अगर_frequency(काष्ठा dvb_frontend *fe,
					   u32 *frequency)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;

	*frequency = 0;

	चयन (state->अगर_freq) अणु
	हाल MXL_IF_4_0:   /* 4.0   MHz */
		*frequency = 4000000;
		अवरोध;
	हाल MXL_IF_4_5:   /* 4.5   MHz */
		*frequency = 4500000;
		अवरोध;
	हाल MXL_IF_4_57:  /* 4.57  MHz */
		*frequency = 4570000;
		अवरोध;
	हाल MXL_IF_5_0:   /* 5.0   MHz */
		*frequency = 5000000;
		अवरोध;
	हाल MXL_IF_5_38:  /* 5.38  MHz */
		*frequency = 5380000;
		अवरोध;
	हाल MXL_IF_6_0:   /* 6.0   MHz */
		*frequency = 6000000;
		अवरोध;
	हाल MXL_IF_6_28:  /* 6.28  MHz */
		*frequency = 6280000;
		अवरोध;
	हाल MXL_IF_7_2:   /* 7.2   MHz */
		*frequency = 7200000;
		अवरोध;
	हाल MXL_IF_35_25: /* 35.25 MHz */
		*frequency = 35250000;
		अवरोध;
	हाल MXL_IF_36:    /* 36    MHz */
		*frequency = 36000000;
		अवरोध;
	हाल MXL_IF_36_15: /* 36.15 MHz */
		*frequency = 36150000;
		अवरोध;
	हाल MXL_IF_44:    /* 44    MHz */
		*frequency = 44000000;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mxl111sf_tuner_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_tuner_state *state = fe->tuner_priv;
	mxl_dbg("()");
	kमुक्त(state);
	fe->tuner_priv = शून्य;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल स्थिर काष्ठा dvb_tuner_ops mxl111sf_tuner_tuner_ops = अणु
	.info = अणु
		.name = "MaxLinear MxL111SF",
#अगर 0
		.frequency_min_hz  = ,
		.frequency_max_hz  = ,
		.frequency_step_hz = ,
#पूर्ण_अगर
	पूर्ण,
#अगर 0
	.init              = mxl111sf_tuner_init,
	.sleep             = mxl111sf_tuner_sleep,
#पूर्ण_अगर
	.set_params        = mxl111sf_tuner_set_params,
	.get_status        = mxl111sf_tuner_get_status,
	.get_rf_strength   = mxl111sf_get_rf_strength,
	.get_frequency     = mxl111sf_tuner_get_frequency,
	.get_bandwidth     = mxl111sf_tuner_get_bandwidth,
	.get_अगर_frequency  = mxl111sf_tuner_get_अगर_frequency,
	.release           = mxl111sf_tuner_release,
पूर्ण;

काष्ठा dvb_frontend *mxl111sf_tuner_attach(काष्ठा dvb_frontend *fe,
				काष्ठा mxl111sf_state *mxl_state,
				स्थिर काष्ठा mxl111sf_tuner_config *cfg)
अणु
	काष्ठा mxl111sf_tuner_state *state = शून्य;

	mxl_dbg("()");

	state = kzalloc(माप(काष्ठा mxl111sf_tuner_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->mxl_state = mxl_state;
	state->cfg = cfg;

	स_नकल(&fe->ops.tuner_ops, &mxl111sf_tuner_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = state;
	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(mxl111sf_tuner_attach);

MODULE_DESCRIPTION("MaxLinear MxL111SF CMOS tuner driver");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
