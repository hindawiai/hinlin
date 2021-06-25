<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TerraTec Cinergy T2/qanu USB2 DVB-T adapter.
 *
 * Copyright (C) 2007 Tomi Orava (tomimo@ncircle.nullnet.fi)
 *
 * Based on the dvb-usb-framework code and the
 * original Terratec Cinergy T2 driver by:
 *
 * Copyright (C) 2004 Daniel Mack <daniel@qanu.de> and
 *                  Holger Waechtler <holger@qanu.de>
 *
 *  Protocol Spec published on http://qanu.de/specs/terratec_cinergyT2.pdf
 */

#समावेश "cinergyT2.h"


/*
 *  convert linux-dvb frontend parameter set पूर्णांकo TPS.
 *  See ETSI ETS-300744, section 4.6.2, table 9 क्रम details.
 *
 *  This function is probably reusable and may better get placed in a support
 *  library.
 *
 *  We replace erroneous fields by शेष TPS fields (the ones with value 0).
 */

अटल uपूर्णांक16_t compute_tps(काष्ठा dtv_frontend_properties *op)
अणु
	uपूर्णांक16_t tps = 0;

	चयन (op->code_rate_HP) अणु
	हाल FEC_2_3:
		tps |= (1 << 7);
		अवरोध;
	हाल FEC_3_4:
		tps |= (2 << 7);
		अवरोध;
	हाल FEC_5_6:
		tps |= (3 << 7);
		अवरोध;
	हाल FEC_7_8:
		tps |= (4 << 7);
		अवरोध;
	हाल FEC_1_2:
	हाल FEC_AUTO:
	शेष:
		/* tps |= (0 << 7) */;
	पूर्ण

	चयन (op->code_rate_LP) अणु
	हाल FEC_2_3:
		tps |= (1 << 4);
		अवरोध;
	हाल FEC_3_4:
		tps |= (2 << 4);
		अवरोध;
	हाल FEC_5_6:
		tps |= (3 << 4);
		अवरोध;
	हाल FEC_7_8:
		tps |= (4 << 4);
		अवरोध;
	हाल FEC_1_2:
	हाल FEC_AUTO:
	शेष:
		/* tps |= (0 << 4) */;
	पूर्ण

	चयन (op->modulation) अणु
	हाल QAM_16:
		tps |= (1 << 13);
		अवरोध;
	हाल QAM_64:
		tps |= (2 << 13);
		अवरोध;
	हाल QPSK:
	शेष:
		/* tps |= (0 << 13) */;
	पूर्ण

	चयन (op->transmission_mode) अणु
	हाल TRANSMISSION_MODE_8K:
		tps |= (1 << 0);
		अवरोध;
	हाल TRANSMISSION_MODE_2K:
	शेष:
		/* tps |= (0 << 0) */;
	पूर्ण

	चयन (op->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_16:
		tps |= (1 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		tps |= (2 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		tps |= (3 << 2);
		अवरोध;
	हाल GUARD_INTERVAL_1_32:
	शेष:
		/* tps |= (0 << 2) */;
	पूर्ण

	चयन (op->hierarchy) अणु
	हाल HIERARCHY_1:
		tps |= (1 << 10);
		अवरोध;
	हाल HIERARCHY_2:
		tps |= (2 << 10);
		अवरोध;
	हाल HIERARCHY_4:
		tps |= (3 << 10);
		अवरोध;
	हाल HIERARCHY_NONE:
	शेष:
		/* tps |= (0 << 10) */;
	पूर्ण

	वापस tps;
पूर्ण

काष्ठा cinergyt2_fe_state अणु
	काष्ठा dvb_frontend fe;
	काष्ठा dvb_usb_device *d;

	अचिन्हित अक्षर data[64];
	काष्ठा mutex data_mutex;

	काष्ठा dvbt_get_status_msg status;
पूर्ण;

अटल पूर्णांक cinergyt2_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_status *status)
अणु
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	mutex_lock(&state->data_mutex);
	state->data[0] = CINERGYT2_EP1_GET_TUNER_STATUS;

	ret = dvb_usb_generic_rw(state->d, state->data, 1,
				 state->data, माप(state->status), 0);
	अगर (!ret)
		स_नकल(&state->status, state->data, माप(state->status));
	mutex_unlock(&state->data_mutex);

	अगर (ret < 0)
		वापस ret;

	*status = 0;

	अगर (0xffff - le16_to_cpu(state->status.gain) > 30)
		*status |= FE_HAS_SIGNAL;
	अगर (state->status.lock_bits & (1 << 6))
		*status |= FE_HAS_LOCK;
	अगर (state->status.lock_bits & (1 << 5))
		*status |= FE_HAS_SYNC;
	अगर (state->status.lock_bits & (1 << 4))
		*status |= FE_HAS_CARRIER;
	अगर (state->status.lock_bits & (1 << 1))
		*status |= FE_HAS_VITERBI;

	अगर ((*status & (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)) !=
			(FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;

	*ber = le32_to_cpu(state->status.viterbi_error_rate);
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 *unc)
अणु
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;

	*unc = le32_to_cpu(state->status.uncorrected_block_count);
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
						u16 *strength)
अणु
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;

	*strength = (0xffff - le16_to_cpu(state->status.gain));
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;

	*snr = (state->status.snr << 8) | state->status.snr;
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_init(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	deb_info("cinergyt2_fe_sleep() Called\n");
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_get_tune_settings(काष्ठा dvb_frontend *fe,
				काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 800;
	वापस 0;
पूर्ण

अटल पूर्णांक cinergyt2_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;
	काष्ठा dvbt_set_parameters_msg *param;
	पूर्णांक err;

	mutex_lock(&state->data_mutex);

	param = (व्योम *)state->data;
	param->cmd = CINERGYT2_EP1_SET_TUNER_PARAMETERS;
	param->tps = cpu_to_le16(compute_tps(fep));
	param->freq = cpu_to_le32(fep->frequency / 1000);
	param->flags = 0;

	चयन (fep->bandwidth_hz) अणु
	शेष:
	हाल 8000000:
		param->bandwidth = 8;
		अवरोध;
	हाल 7000000:
		param->bandwidth = 7;
		अवरोध;
	हाल 6000000:
		param->bandwidth = 6;
		अवरोध;
	पूर्ण

	err = dvb_usb_generic_rw(state->d, state->data, माप(*param),
				 state->data, 2, 0);
	अगर (err < 0)
		err("cinergyt2_fe_set_frontend() Failed! err=%d\n", err);

	mutex_unlock(&state->data_mutex);
	वापस (err < 0) ? err : 0;
पूर्ण

अटल व्योम cinergyt2_fe_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cinergyt2_fe_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops cinergyt2_fe_ops;

काष्ठा dvb_frontend *cinergyt2_fe_attach(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा cinergyt2_fe_state *s = kzalloc(माप(
					काष्ठा cinergyt2_fe_state), GFP_KERNEL);
	अगर (s == शून्य)
		वापस शून्य;

	s->d = d;
	स_नकल(&s->fe.ops, &cinergyt2_fe_ops, माप(काष्ठा dvb_frontend_ops));
	s->fe.demodulator_priv = s;
	mutex_init(&s->data_mutex);
	वापस &s->fe;
पूर्ण


अटल स्थिर काष्ठा dvb_frontend_ops cinergyt2_fe_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= DRIVER_NAME,
		.frequency_min_hz	= 174 * MHz,
		.frequency_max_hz	= 862 * MHz,
		.frequency_stepsize_hz	= 166667,
		.caps = FE_CAN_INVERSION_AUTO | FE_CAN_FEC_1_2
			| FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4
			| FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8
			| FE_CAN_FEC_AUTO | FE_CAN_QPSK
			| FE_CAN_QAM_16 | FE_CAN_QAM_64
			| FE_CAN_QAM_AUTO
			| FE_CAN_TRANSMISSION_MODE_AUTO
			| FE_CAN_GUARD_INTERVAL_AUTO
			| FE_CAN_HIERARCHY_AUTO
			| FE_CAN_RECOVER
			| FE_CAN_MUTE_TS
	पूर्ण,

	.release		= cinergyt2_fe_release,

	.init			= cinergyt2_fe_init,
	.sleep			= cinergyt2_fe_sleep,

	.set_frontend		= cinergyt2_fe_set_frontend,
	.get_tune_settings	= cinergyt2_fe_get_tune_settings,

	.पढ़ो_status		= cinergyt2_fe_पढ़ो_status,
	.पढ़ो_ber		= cinergyt2_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength	= cinergyt2_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr		= cinergyt2_fe_पढ़ो_snr,
	.पढ़ो_ucblocks		= cinergyt2_fe_पढ़ो_unc_blocks,
पूर्ण;
