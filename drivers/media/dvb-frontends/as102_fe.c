<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */

#समावेश <media/dvb_frontend.h>

#समावेश "as102_fe.h"

काष्ठा as102_state अणु
	काष्ठा dvb_frontend frontend;
	काष्ठा as10x_demod_stats demod_stats;

	स्थिर काष्ठा as102_fe_ops *ops;
	व्योम *priv;
	uपूर्णांक8_t elna_cfg;

	/* संकेत strength */
	uपूर्णांक16_t संकेत_strength;
	/* bit error rate */
	uपूर्णांक32_t ber;
पूर्ण;

अटल uपूर्णांक8_t as102_fe_get_code_rate(क्रमागत fe_code_rate arg)
अणु
	uपूर्णांक8_t c;

	चयन (arg) अणु
	हाल FEC_1_2:
		c = CODE_RATE_1_2;
		अवरोध;
	हाल FEC_2_3:
		c = CODE_RATE_2_3;
		अवरोध;
	हाल FEC_3_4:
		c = CODE_RATE_3_4;
		अवरोध;
	हाल FEC_5_6:
		c = CODE_RATE_5_6;
		अवरोध;
	हाल FEC_7_8:
		c = CODE_RATE_7_8;
		अवरोध;
	शेष:
		c = CODE_RATE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस c;
पूर्ण

अटल पूर्णांक as102_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा as10x_tune_args tune_args = अणु 0 पूर्ण;

	/* set frequency */
	tune_args.freq = c->frequency / 1000;

	/* fix पूर्णांकerleaving_mode */
	tune_args.पूर्णांकerleaving_mode = INTLV_NATIVE;

	चयन (c->bandwidth_hz) अणु
	हाल 8000000:
		tune_args.bandwidth = BW_8_MHZ;
		अवरोध;
	हाल 7000000:
		tune_args.bandwidth = BW_7_MHZ;
		अवरोध;
	हाल 6000000:
		tune_args.bandwidth = BW_6_MHZ;
		अवरोध;
	शेष:
		tune_args.bandwidth = BW_8_MHZ;
	पूर्ण

	चयन (c->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_32:
		tune_args.guard_पूर्णांकerval = GUARD_INT_1_32;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		tune_args.guard_पूर्णांकerval = GUARD_INT_1_16;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		tune_args.guard_पूर्णांकerval = GUARD_INT_1_8;
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		tune_args.guard_पूर्णांकerval = GUARD_INT_1_4;
		अवरोध;
	हाल GUARD_INTERVAL_AUTO:
	शेष:
		tune_args.guard_पूर्णांकerval = GUARD_UNKNOWN;
		अवरोध;
	पूर्ण

	चयन (c->modulation) अणु
	हाल QPSK:
		tune_args.modulation = CONST_QPSK;
		अवरोध;
	हाल QAM_16:
		tune_args.modulation = CONST_QAM16;
		अवरोध;
	हाल QAM_64:
		tune_args.modulation = CONST_QAM64;
		अवरोध;
	शेष:
		tune_args.modulation = CONST_UNKNOWN;
		अवरोध;
	पूर्ण

	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		tune_args.transmission_mode = TRANS_MODE_2K;
		अवरोध;
	हाल TRANSMISSION_MODE_8K:
		tune_args.transmission_mode = TRANS_MODE_8K;
		अवरोध;
	शेष:
		tune_args.transmission_mode = TRANS_MODE_UNKNOWN;
	पूर्ण

	चयन (c->hierarchy) अणु
	हाल HIERARCHY_NONE:
		tune_args.hierarchy = HIER_NONE;
		अवरोध;
	हाल HIERARCHY_1:
		tune_args.hierarchy = HIER_ALPHA_1;
		अवरोध;
	हाल HIERARCHY_2:
		tune_args.hierarchy = HIER_ALPHA_2;
		अवरोध;
	हाल HIERARCHY_4:
		tune_args.hierarchy = HIER_ALPHA_4;
		अवरोध;
	हाल HIERARCHY_AUTO:
		tune_args.hierarchy = HIER_UNKNOWN;
		अवरोध;
	पूर्ण

	pr_debug("as102: tuner parameters: freq: %d  bw: 0x%02x  gi: 0x%02x\n",
			c->frequency,
			tune_args.bandwidth,
			tune_args.guard_पूर्णांकerval);

	/*
	 * Detect a hierarchy selection
	 * अगर HP/LP are both set to FEC_NONE, HP will be selected.
	 */
	अगर ((tune_args.hierarchy != HIER_NONE) &&
		       ((c->code_rate_LP == FEC_NONE) ||
			(c->code_rate_HP == FEC_NONE))) अणु

		अगर (c->code_rate_LP == FEC_NONE) अणु
			tune_args.hier_select = HIER_HIGH_PRIORITY;
			tune_args.code_rate =
			   as102_fe_get_code_rate(c->code_rate_HP);
		पूर्ण

		अगर (c->code_rate_HP == FEC_NONE) अणु
			tune_args.hier_select = HIER_LOW_PRIORITY;
			tune_args.code_rate =
			   as102_fe_get_code_rate(c->code_rate_LP);
		पूर्ण

		pr_debug("as102: \thierarchy: 0x%02x  selected: %s  code_rate_%s: 0x%02x\n",
			tune_args.hierarchy,
			tune_args.hier_select == HIER_HIGH_PRIORITY ?
			"HP" : "LP",
			tune_args.hier_select == HIER_HIGH_PRIORITY ?
			"HP" : "LP",
			tune_args.code_rate);
	पूर्ण अन्यथा अणु
		tune_args.code_rate =
			as102_fe_get_code_rate(c->code_rate_HP);
	पूर्ण

	/* Set frontend arguments */
	वापस state->ops->set_tune(state->priv, &tune_args);
पूर्ण

अटल पूर्णांक as102_fe_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;
	पूर्णांक ret = 0;
	काष्ठा as10x_tps tps = अणु 0 पूर्ण;

	/* send abilis command: GET_TPS */
	ret = state->ops->get_tps(state->priv, &tps);
	अगर (ret < 0)
		वापस ret;

	/* extract स्थिरellation */
	चयन (tps.modulation) अणु
	हाल CONST_QPSK:
		c->modulation = QPSK;
		अवरोध;
	हाल CONST_QAM16:
		c->modulation = QAM_16;
		अवरोध;
	हाल CONST_QAM64:
		c->modulation = QAM_64;
		अवरोध;
	पूर्ण

	/* extract hierarchy */
	चयन (tps.hierarchy) अणु
	हाल HIER_NONE:
		c->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल HIER_ALPHA_1:
		c->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल HIER_ALPHA_2:
		c->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल HIER_ALPHA_4:
		c->hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण

	/* extract code rate HP */
	चयन (tps.code_rate_HP) अणु
	हाल CODE_RATE_1_2:
		c->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल CODE_RATE_2_3:
		c->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल CODE_RATE_3_4:
		c->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल CODE_RATE_5_6:
		c->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल CODE_RATE_7_8:
		c->code_rate_HP = FEC_7_8;
		अवरोध;
	पूर्ण

	/* extract code rate LP */
	चयन (tps.code_rate_LP) अणु
	हाल CODE_RATE_1_2:
		c->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल CODE_RATE_2_3:
		c->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल CODE_RATE_3_4:
		c->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल CODE_RATE_5_6:
		c->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल CODE_RATE_7_8:
		c->code_rate_LP = FEC_7_8;
		अवरोध;
	पूर्ण

	/* extract guard पूर्णांकerval */
	चयन (tps.guard_पूर्णांकerval) अणु
	हाल GUARD_INT_1_32:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल GUARD_INT_1_16:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल GUARD_INT_1_8:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल GUARD_INT_1_4:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण

	/* extract transmission mode */
	चयन (tps.transmission_mode) अणु
	हाल TRANS_MODE_2K:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल TRANS_MODE_8K:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक as102_fe_get_tune_settings(काष्ठा dvb_frontend *fe,
			काष्ठा dvb_frontend_tune_settings *settings)
अणु

	settings->min_delay_ms = 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक as102_fe_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	पूर्णांक ret = 0;
	काष्ठा as102_state *state = fe->demodulator_priv;
	काष्ठा as10x_tune_status tstate = अणु 0 पूर्ण;

	/* send abilis command: GET_TUNE_STATUS */
	ret = state->ops->get_status(state->priv, &tstate);
	अगर (ret < 0)
		वापस ret;

	state->संकेत_strength  = tstate.संकेत_strength;
	state->ber  = tstate.BER;

	चयन (tstate.tune_state) अणु
	हाल TUNE_STATUS_SIGNAL_DVB_OK:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		अवरोध;
	हाल TUNE_STATUS_STREAM_DETECTED:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_SYNC |
			  FE_HAS_VITERBI;
		अवरोध;
	हाल TUNE_STATUS_STREAM_TUNED:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_SYNC |
			  FE_HAS_LOCK | FE_HAS_VITERBI;
		अवरोध;
	शेष:
		*status = TUNE_STATUS_NOT_TUNED;
	पूर्ण

	pr_debug("as102: tuner status: 0x%02x, strength %d, per: %d, ber: %d\n",
		 tstate.tune_state, tstate.संकेत_strength,
		 tstate.PER, tstate.BER);

	अगर (!(*status & FE_HAS_LOCK)) अणु
		स_रखो(&state->demod_stats, 0, माप(state->demod_stats));
		वापस 0;
	पूर्ण

	ret = state->ops->get_stats(state->priv, &state->demod_stats);
	अगर (ret < 0)
		स_रखो(&state->demod_stats, 0, माप(state->demod_stats));

	वापस ret;
पूर्ण

/*
 * Note:
 * - in AS102 SNR=MER
 *   - the SNR will be वापसed in linear terms, i.e. not in dB
 *   - the accuracy equals तऔ2dB क्रम a SNR range from 4dB to 30dB
 *   - the accuracy is >2dB क्रम SNR values outside this range
 */
अटल पूर्णांक as102_fe_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;

	*snr = state->demod_stats.mer;

	वापस 0;
पूर्ण

अटल पूर्णांक as102_fe_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;

	*ber = state->ber;

	वापस 0;
पूर्ण

अटल पूर्णांक as102_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					 u16 *strength)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;

	*strength = (((0xffff * 400) * state->संकेत_strength + 41000) * 2);

	वापस 0;
पूर्ण

अटल पूर्णांक as102_fe_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;

	अगर (state->demod_stats.has_started)
		*ucblocks = state->demod_stats.bad_frame_count;
	अन्यथा
		*ucblocks = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक as102_fe_ts_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;

	वापस state->ops->stream_ctrl(state->priv, acquire,
				      state->elna_cfg);
पूर्ण

अटल व्योम as102_fe_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा as102_state *state = fe->demodulator_priv;

	kमुक्त(state);
पूर्ण


अटल स्थिर काष्ठा dvb_frontend_ops as102_fe_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Abilis AS102 DVB-T",
		.frequency_min_hz	= 174 * MHz,
		.frequency_max_hz	= 862 * MHz,
		.frequency_stepsize_hz	= 166667,
		.caps = FE_CAN_INVERSION_AUTO
			| FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4
			| FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO
			| FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QPSK
			| FE_CAN_QAM_AUTO
			| FE_CAN_TRANSMISSION_MODE_AUTO
			| FE_CAN_GUARD_INTERVAL_AUTO
			| FE_CAN_HIERARCHY_AUTO
			| FE_CAN_RECOVER
			| FE_CAN_MUTE_TS
	पूर्ण,

	.set_frontend		= as102_fe_set_frontend,
	.get_frontend		= as102_fe_get_frontend,
	.get_tune_settings	= as102_fe_get_tune_settings,

	.पढ़ो_status		= as102_fe_पढ़ो_status,
	.पढ़ो_snr		= as102_fe_पढ़ो_snr,
	.पढ़ो_ber		= as102_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength	= as102_fe_पढ़ो_संकेत_strength,
	.पढ़ो_ucblocks		= as102_fe_पढ़ो_ucblocks,
	.ts_bus_ctrl		= as102_fe_ts_bus_ctrl,
	.release		= as102_fe_release,
पूर्ण;

काष्ठा dvb_frontend *as102_attach(स्थिर अक्षर *name,
				  स्थिर काष्ठा as102_fe_ops *ops,
				  व्योम *priv,
				  uपूर्णांक8_t elna_cfg)
अणु
	काष्ठा as102_state *state;
	काष्ठा dvb_frontend *fe;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	fe = &state->frontend;
	fe->demodulator_priv = state;
	state->ops = ops;
	state->priv = priv;
	state->elna_cfg = elna_cfg;

	/* init frontend callback ops */
	स_नकल(&fe->ops, &as102_fe_ops, माप(काष्ठा dvb_frontend_ops));
	strscpy(fe->ops.info.name, name, माप(fe->ops.info.name));

	वापस fe;

पूर्ण
EXPORT_SYMBOL_GPL(as102_attach);

MODULE_DESCRIPTION("as102-fe");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pierrick Hascoet <pierrick.hascoet@abilis.com>");
