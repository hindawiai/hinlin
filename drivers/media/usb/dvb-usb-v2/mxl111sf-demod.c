<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  mxl111sf-demod.c - driver क्रम the MaxLinear MXL111SF DVB-T demodulator
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश "mxl111sf-demod.h"
#समावेश "mxl111sf-reg.h"

/* debug */
अटल पूर्णांक mxl111sf_demod_debug;
module_param_named(debug, mxl111sf_demod_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info (or-able)).");

#घोषणा mxl_dbg(fmt, arg...) \
	अगर (mxl111sf_demod_debug) \
		mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg)

/* ------------------------------------------------------------------------ */

काष्ठा mxl111sf_demod_state अणु
	काष्ठा mxl111sf_state *mxl_state;

	स्थिर काष्ठा mxl111sf_demod_config *cfg;

	काष्ठा dvb_frontend fe;
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl111sf_demod_पढ़ो_reg(काष्ठा mxl111sf_demod_state *state,
				   u8 addr, u8 *data)
अणु
	वापस (state->cfg->पढ़ो_reg) ?
		state->cfg->पढ़ो_reg(state->mxl_state, addr, data) :
		-EINVAL;
पूर्ण

अटल पूर्णांक mxl111sf_demod_ग_लिखो_reg(काष्ठा mxl111sf_demod_state *state,
				    u8 addr, u8 data)
अणु
	वापस (state->cfg->ग_लिखो_reg) ?
		state->cfg->ग_लिखो_reg(state->mxl_state, addr, data) :
		-EINVAL;
पूर्ण

अटल
पूर्णांक mxl111sf_demod_program_regs(काष्ठा mxl111sf_demod_state *state,
				काष्ठा mxl111sf_reg_ctrl_info *ctrl_reg_info)
अणु
	वापस (state->cfg->program_regs) ?
		state->cfg->program_regs(state->mxl_state, ctrl_reg_info) :
		-EINVAL;
पूर्ण

/* ------------------------------------------------------------------------ */
/* TPS */

अटल
पूर्णांक mxl1x1sf_demod_get_tps_code_rate(काष्ठा mxl111sf_demod_state *state,
				     क्रमागत fe_code_rate *code_rate)
अणु
	u8 val;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_CODE_RATE_TPS_REG, &val);
	/* bit<2:0> - 000:1/2, 001:2/3, 010:3/4, 011:5/6, 100:7/8 */
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन (val & V6_CODE_RATE_TPS_MASK) अणु
	हाल 0:
		*code_rate = FEC_1_2;
		अवरोध;
	हाल 1:
		*code_rate = FEC_2_3;
		अवरोध;
	हाल 2:
		*code_rate = FEC_3_4;
		अवरोध;
	हाल 3:
		*code_rate = FEC_5_6;
		अवरोध;
	हाल 4:
		*code_rate = FEC_7_8;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_tps_modulation(काष्ठा mxl111sf_demod_state *state,
				      क्रमागत fe_modulation *modulation)
अणु
	u8 val;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_MODORDER_TPS_REG, &val);
	/* Constellation, 00 : QPSK, 01 : 16QAM, 10:64QAM */
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन ((val & V6_PARAM_CONSTELLATION_MASK) >> 4) अणु
	हाल 0:
		*modulation = QPSK;
		अवरोध;
	हाल 1:
		*modulation = QAM_16;
		अवरोध;
	हाल 2:
		*modulation = QAM_64;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_tps_guard_fft_mode(काष्ठा mxl111sf_demod_state *state,
					  क्रमागत fe_transmit_mode *fft_mode)
अणु
	u8 val;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_MODE_TPS_REG, &val);
	/* FFT Mode, 00:2K, 01:8K, 10:4K */
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन ((val & V6_PARAM_FFT_MODE_MASK) >> 2) अणु
	हाल 0:
		*fft_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		*fft_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	हाल 2:
		*fft_mode = TRANSMISSION_MODE_4K;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_tps_guard_पूर्णांकerval(काष्ठा mxl111sf_demod_state *state,
					  क्रमागत fe_guard_पूर्णांकerval *guard)
अणु
	u8 val;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_CP_TPS_REG, &val);
	/* 00:1/32, 01:1/16, 10:1/8, 11:1/4 */
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन ((val & V6_PARAM_GI_MASK) >> 4) अणु
	हाल 0:
		*guard = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		*guard = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		*guard = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		*guard = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_tps_hierarchy(काष्ठा mxl111sf_demod_state *state,
				     क्रमागत fe_hierarchy *hierarchy)
अणु
	u8 val;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_TPS_HIERACHY_REG, &val);
	/* bit<6:4> - 000:Non hierarchy, 001:1, 010:2, 011:4 */
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन ((val & V6_TPS_HIERARCHY_INFO_MASK) >> 6) अणु
	हाल 0:
		*hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		*hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		*hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		*hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */
/* LOCKS */

अटल
पूर्णांक mxl1x1sf_demod_get_sync_lock_status(काष्ठा mxl111sf_demod_state *state,
					पूर्णांक *sync_lock)
अणु
	u8 val = 0;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_SYNC_LOCK_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;
	*sync_lock = (val & SYNC_LOCK_MASK) >> 4;
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_rs_lock_status(काष्ठा mxl111sf_demod_state *state,
				      पूर्णांक *rs_lock)
अणु
	u8 val = 0;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_RS_LOCK_DET_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;
	*rs_lock = (val & RS_LOCK_DET_MASK) >> 3;
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_tps_lock_status(काष्ठा mxl111sf_demod_state *state,
				       पूर्णांक *tps_lock)
अणु
	u8 val = 0;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_TPS_LOCK_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;
	*tps_lock = (val & V6_PARAM_TPS_LOCK_MASK) >> 6;
fail:
	वापस ret;
पूर्ण

अटल
पूर्णांक mxl1x1sf_demod_get_fec_lock_status(काष्ठा mxl111sf_demod_state *state,
				       पूर्णांक *fec_lock)
अणु
	u8 val = 0;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_IRQ_STATUS_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;
	*fec_lock = (val & IRQ_MASK_FEC_LOCK) >> 4;
fail:
	वापस ret;
पूर्ण

#अगर 0
अटल
पूर्णांक mxl1x1sf_demod_get_cp_lock_status(काष्ठा mxl111sf_demod_state *state,
				      पूर्णांक *cp_lock)
अणु
	u8 val = 0;
	पूर्णांक ret = mxl111sf_demod_पढ़ो_reg(state, V6_CP_LOCK_DET_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;
	*cp_lock = (val & V6_CP_LOCK_DET_MASK) >> 2;
fail:
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mxl1x1sf_demod_reset_irq_status(काष्ठा mxl111sf_demod_state *state)
अणु
	वापस mxl111sf_demod_ग_लिखो_reg(state, 0x0e, 0xff);
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक mxl111sf_demod_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;
	पूर्णांक ret = 0;

	काष्ठा mxl111sf_reg_ctrl_info phy_pll_patch[] = अणु
		अणु0x00, 0xff, 0x01पूर्ण, /* change page to 1 */
		अणु0x40, 0xff, 0x05पूर्ण,
		अणु0x40, 0xff, 0x01पूर्ण,
		अणु0x41, 0xff, 0xcaपूर्ण,
		अणु0x41, 0xff, 0xc0पूर्ण,
		अणु0x00, 0xff, 0x00पूर्ण, /* change page to 0 */
		अणु0,    0,    0पूर्ण
	पूर्ण;

	mxl_dbg("()");

	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (mxl_fail(ret))
			जाओ fail;
		msleep(50);
	पूर्ण
	ret = mxl111sf_demod_program_regs(state, phy_pll_patch);
	mxl_fail(ret);
	msleep(50);
	ret = mxl1x1sf_demod_reset_irq_status(state);
	mxl_fail(ret);
	msleep(100);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

#अगर 0
/* resets TS Packet error count */
/* After setting 7th bit of V5_PER_COUNT_RESET_REG, it should be reset to 0. */
अटल
पूर्णांक mxl1x1sf_demod_reset_packet_error_count(काष्ठा mxl111sf_demod_state *state)
अणु
	काष्ठा mxl111sf_reg_ctrl_info reset_per_count[] = अणु
		अणु0x20, 0x01, 0x01पूर्ण,
		अणु0x20, 0x01, 0x00पूर्ण,
		अणु0,    0,    0पूर्ण
	पूर्ण;
	वापस mxl111sf_demod_program_regs(state, reset_per_count);
पूर्ण
#पूर्ण_अगर

/* वापसs TS Packet error count */
/* PER Count = FEC_PER_COUNT * (2 ** (FEC_PER_SCALE * 4)) */
अटल पूर्णांक mxl111sf_demod_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;
	u32 fec_per_count, fec_per_scale;
	u8 val;
	पूर्णांक ret;

	*ucblocks = 0;

	/* FEC_PER_COUNT Register */
	ret = mxl111sf_demod_पढ़ो_reg(state, V6_FEC_PER_COUNT_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;

	fec_per_count = val;

	/* FEC_PER_SCALE Register */
	ret = mxl111sf_demod_पढ़ो_reg(state, V6_FEC_PER_SCALE_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;

	val &= V6_FEC_PER_SCALE_MASK;
	val *= 4;

	fec_per_scale = 1 << val;

	fec_per_count *= fec_per_scale;

	*ucblocks = fec_per_count;
fail:
	वापस ret;
पूर्ण

#अगर_घोषित MXL111SF_DEMOD_ENABLE_CALCULATIONS
/* FIXME: leaving this enabled अवरोधs the build on some architectures,
 * and we shouldn't have any भग्नing poपूर्णांक math in the kernel, anyway.
 *
 * These macros need to be re-written, but it's harmless to simply
 * वापस zero क्रम now. */
#घोषणा CALCULATE_BER(avg_errors, count) \
	((u32)(avg_errors * 4)/(count*64*188*8))
#घोषणा CALCULATE_SNR(data) \
	((u32)((10 * (u32)data / 64) - 2.5))
#अन्यथा
#घोषणा CALCULATE_BER(avg_errors, count) 0
#घोषणा CALCULATE_SNR(data) 0
#पूर्ण_अगर

अटल पूर्णांक mxl111sf_demod_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;
	u8 val1, val2, val3;
	पूर्णांक ret;

	*ber = 0;

	ret = mxl111sf_demod_पढ़ो_reg(state, V6_RS_AVG_ERRORS_LSB_REG, &val1);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_demod_पढ़ो_reg(state, V6_RS_AVG_ERRORS_MSB_REG, &val2);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_demod_पढ़ो_reg(state, V6_N_ACCUMULATE_REG, &val3);
	अगर (mxl_fail(ret))
		जाओ fail;

	*ber = CALCULATE_BER((val1 | (val2 << 8)), val3);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_demod_calc_snr(काष्ठा mxl111sf_demod_state *state,
				   u16 *snr)
अणु
	u8 val1, val2;
	पूर्णांक ret;

	*snr = 0;

	ret = mxl111sf_demod_पढ़ो_reg(state, V6_SNR_RB_LSB_REG, &val1);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_demod_पढ़ो_reg(state, V6_SNR_RB_MSB_REG, &val2);
	अगर (mxl_fail(ret))
		जाओ fail;

	*snr = CALCULATE_SNR(val1 | ((val2 & 0x03) << 8));
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_demod_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;

	पूर्णांक ret = mxl111sf_demod_calc_snr(state, snr);
	अगर (mxl_fail(ret))
		जाओ fail;

	*snr /= 10; /* 0.1 dB */
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_demod_पढ़ो_status(काष्ठा dvb_frontend *fe,
				      क्रमागत fe_status *status)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;
	पूर्णांक ret, locked, cr_lock, sync_lock, fec_lock;

	*status = 0;

	ret = mxl1x1sf_demod_get_rs_lock_status(state, &locked);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_demod_get_tps_lock_status(state, &cr_lock);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_demod_get_sync_lock_status(state, &sync_lock);
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl1x1sf_demod_get_fec_lock_status(state, &fec_lock);
	अगर (mxl_fail(ret))
		जाओ fail;

	अगर (locked)
		*status |= FE_HAS_SIGNAL;
	अगर (cr_lock)
		*status |= FE_HAS_CARRIER;
	अगर (sync_lock)
		*status |= FE_HAS_SYNC;
	अगर (fec_lock) /* false positives? */
		*status |= FE_HAS_VITERBI;

	अगर ((locked) && (cr_lock) && (sync_lock))
		*status |= FE_HAS_LOCK;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl111sf_demod_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					       u16 *संकेत_strength)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;
	क्रमागत fe_modulation modulation;
	पूर्णांक ret;
	u16 snr;

	ret = mxl111sf_demod_calc_snr(state, &snr);
	अगर (ret < 0)
		वापस ret;
	ret = mxl1x1sf_demod_get_tps_modulation(state, &modulation);
	अगर (ret < 0)
		वापस ret;

	चयन (modulation) अणु
	हाल QPSK:
		*संकेत_strength = (snr >= 1300) ?
			min(65535, snr * 44) : snr * 38;
		अवरोध;
	हाल QAM_16:
		*संकेत_strength = (snr >= 1500) ?
			min(65535, snr * 38) : snr * 33;
		अवरोध;
	हाल QAM_64:
		*संकेत_strength = (snr >= 2000) ?
			min(65535, snr * 29) : snr * 25;
		अवरोध;
	शेष:
		*संकेत_strength = 0;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxl111sf_demod_get_frontend(काष्ठा dvb_frontend *fe,
				       काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;

	mxl_dbg("()");
#अगर 0
	p->inversion = /* FIXME */ ? INVERSION_ON : INVERSION_OFF;
#पूर्ण_अगर
	अगर (fe->ops.tuner_ops.get_bandwidth)
		fe->ops.tuner_ops.get_bandwidth(fe, &p->bandwidth_hz);
	अगर (fe->ops.tuner_ops.get_frequency)
		fe->ops.tuner_ops.get_frequency(fe, &p->frequency);
	mxl1x1sf_demod_get_tps_code_rate(state, &p->code_rate_HP);
	mxl1x1sf_demod_get_tps_code_rate(state, &p->code_rate_LP);
	mxl1x1sf_demod_get_tps_modulation(state, &p->modulation);
	mxl1x1sf_demod_get_tps_guard_fft_mode(state,
					      &p->transmission_mode);
	mxl1x1sf_demod_get_tps_guard_पूर्णांकerval(state,
					      &p->guard_पूर्णांकerval);
	mxl1x1sf_demod_get_tps_hierarchy(state,
					 &p->hierarchy);

	वापस 0;
पूर्ण

अटल
पूर्णांक mxl111sf_demod_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम mxl111sf_demod_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl111sf_demod_state *state = fe->demodulator_priv;
	mxl_dbg("()");
	kमुक्त(state);
	fe->demodulator_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mxl111sf_demod_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name               = "MaxLinear MxL111SF DVB-T demodulator",
		.frequency_min_hz      = 177 * MHz,
		.frequency_max_hz      = 858 * MHz,
		.frequency_stepsize_hz = 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_HIERARCHY_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_RECOVER
	पूर्ण,
	.release              = mxl111sf_demod_release,
#अगर 0
	.init                 = mxl111sf_init,
	.i2c_gate_ctrl        = mxl111sf_i2c_gate_ctrl,
#पूर्ण_अगर
	.set_frontend         = mxl111sf_demod_set_frontend,
	.get_frontend         = mxl111sf_demod_get_frontend,
	.get_tune_settings    = mxl111sf_demod_get_tune_settings,
	.पढ़ो_status          = mxl111sf_demod_पढ़ो_status,
	.पढ़ो_संकेत_strength = mxl111sf_demod_पढ़ो_संकेत_strength,
	.पढ़ो_ber             = mxl111sf_demod_पढ़ो_ber,
	.पढ़ो_snr             = mxl111sf_demod_पढ़ो_snr,
	.पढ़ो_ucblocks        = mxl111sf_demod_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *mxl111sf_demod_attach(काष्ठा mxl111sf_state *mxl_state,
				   स्थिर काष्ठा mxl111sf_demod_config *cfg)
अणु
	काष्ठा mxl111sf_demod_state *state = शून्य;

	mxl_dbg("()");

	state = kzalloc(माप(काष्ठा mxl111sf_demod_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->mxl_state = mxl_state;
	state->cfg = cfg;

	स_नकल(&state->fe.ops, &mxl111sf_demod_ops,
	       माप(काष्ठा dvb_frontend_ops));

	state->fe.demodulator_priv = state;
	वापस &state->fe;
पूर्ण
EXPORT_SYMBOL_GPL(mxl111sf_demod_attach);

MODULE_DESCRIPTION("MaxLinear MxL111SF DVB-T demodulator driver");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
