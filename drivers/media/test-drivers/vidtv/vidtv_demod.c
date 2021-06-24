<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The Virtual DVB test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 * Based on the example driver written by Emard <emard@softhome.net>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>

#समावेश <media/dvb_frontend.h>

#समावेश "vidtv_demod.h"

#घोषणा POLL_THRD_TIME 2000 /* ms */

अटल स्थिर काष्ठा vidtv_demod_cnr_to_qual_s vidtv_demod_c_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db */
	अणु QAM_256, FEC_NONE,  34000, 38000पूर्ण,
	अणु QAM_64,  FEC_NONE,  30000, 34000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_demod_cnr_to_qual_s vidtv_demod_s_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db */
	अणु QPSK, FEC_1_2,  7000, 10000पूर्ण,
	अणु QPSK, FEC_2_3,  9000, 12000पूर्ण,
	अणु QPSK, FEC_3_4, 10000, 13000पूर्ण,
	अणु QPSK, FEC_5_6, 11000, 14000पूर्ण,
	अणु QPSK, FEC_7_8, 12000, 15000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_demod_cnr_to_qual_s vidtv_demod_s2_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db */
	अणु QPSK,  FEC_1_2,   9000,  12000पूर्ण,
	अणु QPSK,  FEC_2_3,  11000,  14000पूर्ण,
	अणु QPSK,  FEC_3_4,  12000,  15000पूर्ण,
	अणु QPSK,  FEC_5_6,  12000,  15000पूर्ण,
	अणु QPSK,  FEC_8_9,  13000,  16000पूर्ण,
	अणु QPSK,  FEC_9_10, 13500,  16500पूर्ण,
	अणु PSK_8, FEC_2_3,  14500,  17500पूर्ण,
	अणु PSK_8, FEC_3_4,  16000,  19000पूर्ण,
	अणु PSK_8, FEC_5_6,  17500,  20500पूर्ण,
	अणु PSK_8, FEC_8_9,  19000,  22000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_demod_cnr_to_qual_s vidtv_demod_t_cnr_2_qual[] = अणु
	/* from libdvbv5 source code, in milli db*/
	अणु   QPSK, FEC_1_2,  4100,  5900पूर्ण,
	अणु   QPSK, FEC_2_3,  6100,  9600पूर्ण,
	अणु   QPSK, FEC_3_4,  7200, 12400पूर्ण,
	अणु   QPSK, FEC_5_6,  8500, 15600पूर्ण,
	अणु   QPSK, FEC_7_8,  9200, 17500पूर्ण,
	अणु QAM_16, FEC_1_2,  9800, 11800पूर्ण,
	अणु QAM_16, FEC_2_3, 12100, 15300पूर्ण,
	अणु QAM_16, FEC_3_4, 13400, 18100पूर्ण,
	अणु QAM_16, FEC_5_6, 14800, 21300पूर्ण,
	अणु QAM_16, FEC_7_8, 15700, 23600पूर्ण,
	अणु QAM_64, FEC_1_2, 14000, 16000पूर्ण,
	अणु QAM_64, FEC_2_3, 19900, 25400पूर्ण,
	अणु QAM_64, FEC_3_4, 24900, 27900पूर्ण,
	अणु QAM_64, FEC_5_6, 21300, 23300पूर्ण,
	अणु QAM_64, FEC_7_8, 22000, 24000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vidtv_demod_cnr_to_qual_s *vidtv_match_cnr_s(काष्ठा dvb_frontend *fe)
अणु
	स्थिर काष्ठा vidtv_demod_cnr_to_qual_s *cnr2qual = शून्य;
	काष्ठा device *dev = fe->dvb->device;
	काष्ठा dtv_frontend_properties *c;
	u32 array_size = 0;
	u32 i;

	c = &fe->dtv_property_cache;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		cnr2qual   = vidtv_demod_t_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_demod_t_cnr_2_qual);
		अवरोध;

	हाल SYS_DVBS:
		cnr2qual   = vidtv_demod_s_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_demod_s_cnr_2_qual);
		अवरोध;

	हाल SYS_DVBS2:
		cnr2qual   = vidtv_demod_s2_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_demod_s2_cnr_2_qual);
		अवरोध;

	हाल SYS_DVBC_ANNEX_A:
		cnr2qual   = vidtv_demod_c_cnr_2_qual;
		array_size = ARRAY_SIZE(vidtv_demod_c_cnr_2_qual);
		अवरोध;

	शेष:
		dev_warn_ratelimited(dev,
				     "%s: unsupported delivery system: %u\n",
				     __func__,
				     c->delivery_प्रणाली);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < array_size; i++)
		अगर (cnr2qual[i].modulation == c->modulation &&
		    cnr2qual[i].fec == c->fec_inner)
			वापस &cnr2qual[i];

	वापस शून्य; /* not found */
पूर्ण

अटल व्योम vidtv_clean_stats(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	/* Fill the length of each status counter */

	/* Signal is always available */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].svalue = 0;

	/* Usually available only after Viterbi lock */
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.stat[0].svalue = 0;
	c->cnr.len = 1;

	/* Those depends on full lock */
	c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->pre_bit_error.stat[0].uvalue = 0;
	c->pre_bit_error.len = 1;
	c->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->pre_bit_count.stat[0].uvalue = 0;
	c->pre_bit_count.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.stat[0].uvalue = 0;
	c->post_bit_error.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].uvalue = 0;
	c->post_bit_count.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.stat[0].uvalue = 0;
	c->block_error.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.stat[0].uvalue = 0;
	c->block_count.len = 1;
पूर्ण

अटल व्योम vidtv_demod_update_stats(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा vidtv_demod_state *state = fe->demodulator_priv;
	u32 scale;

	अगर (state->status & FE_HAS_LOCK) अणु
		scale = FE_SCALE_COUNTER;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण अन्यथा अणु
		scale = FE_SCALE_NOT_AVAILABLE;
		c->cnr.stat[0].scale = scale;
	पूर्ण

	c->pre_bit_error.stat[0].scale = scale;
	c->pre_bit_count.stat[0].scale = scale;
	c->post_bit_error.stat[0].scale = scale;
	c->post_bit_count.stat[0].scale = scale;
	c->block_error.stat[0].scale = scale;
	c->block_count.stat[0].scale = scale;

	/*
	 * Add a 0.5% of अक्रमomness at the संकेत strength and CNR,
	 * and make them dअगरferent, as we want to have something बंदr
	 * to a real हाल scenario.
	 *
	 * Also, usually, संकेत strength is a negative number in dBm.
	 */
	c->strength.stat[0].svalue = state->tuner_cnr;
	c->strength.stat[0].svalue -= pअक्रमom_u32_max(state->tuner_cnr / 50);
	c->strength.stat[0].svalue -= 68000; /* Adjust to a better range */

	c->cnr.stat[0].svalue = state->tuner_cnr;
	c->cnr.stat[0].svalue -= pअक्रमom_u32_max(state->tuner_cnr / 50);
पूर्ण

अटल पूर्णांक vidtv_demod_पढ़ो_status(काष्ठा dvb_frontend *fe,
				   क्रमागत fe_status *status)
अणु
	काष्ठा vidtv_demod_state *state = fe->demodulator_priv;
	स्थिर काष्ठा vidtv_demod_cnr_to_qual_s *cnr2qual = शून्य;
	काष्ठा vidtv_demod_config *config = &state->config;
	u16 snr = 0;

	/* Simulate अक्रमom lost of संकेत due to a bad-tuned channel */
	cnr2qual = vidtv_match_cnr_s(&state->frontend);

	अगर (cnr2qual && state->tuner_cnr < cnr2qual->cnr_good &&
	    state->frontend.ops.tuner_ops.get_rf_strength) अणु
		state->frontend.ops.tuner_ops.get_rf_strength(&state->frontend,
							      &snr);

		अगर (snr < cnr2qual->cnr_ok) अणु
			/* eventually lose the TS lock */
			अगर (pअक्रमom_u32_max(100) < config->drop_tslock_prob_on_low_snr)
				state->status = 0;
		पूर्ण अन्यथा अणु
			/* recover अगर the संकेत improves */
			अगर (pअक्रमom_u32_max(100) <
			    config->recover_tslock_prob_on_good_snr)
				state->status = FE_HAS_SIGNAL  |
						FE_HAS_CARRIER |
						FE_HAS_VITERBI |
						FE_HAS_SYNC    |
						FE_HAS_LOCK;
		पूर्ण
	पूर्ण

	vidtv_demod_update_stats(&state->frontend);

	*status = state->status;

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_demod_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					    u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	*strength = c->strength.stat[0].uvalue;

	वापस 0;
पूर्ण

/*
 * NOTE:
 * This is implemented here just to be used as an example क्रम real
 * demod drivers.
 *
 * Should only be implemented अगर it actually पढ़ोs something from the hardware.
 * Also, it should check क्रम the locks, in order to aव्योम report wrong data
 * to userspace.
 */
अटल पूर्णांक vidtv_demod_get_frontend(काष्ठा dvb_frontend *fe,
				    काष्ठा dtv_frontend_properties *p)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_demod_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_demod_state *state = fe->demodulator_priv;
	u32 tuner_status = 0;
	पूर्णांक ret;

	अगर (!fe->ops.tuner_ops.set_params)
		वापस 0;

	fe->ops.tuner_ops.set_params(fe);

	/* store the CNR वापसed by the tuner */
	ret = fe->ops.tuner_ops.get_rf_strength(fe, &state->tuner_cnr);
	अगर (ret < 0)
		वापस ret;

	fe->ops.tuner_ops.get_status(fe, &tuner_status);
	state->status = (state->tuner_cnr > 0) ?  FE_HAS_SIGNAL  |
						    FE_HAS_CARRIER |
						    FE_HAS_VITERBI |
						    FE_HAS_SYNC    |
						    FE_HAS_LOCK	 :
						    0;

	vidtv_demod_update_stats(fe);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

/*
 * NOTE:
 * This is implemented here just to be used as an example क्रम real
 * demod drivers.
 *
 * Should only be implemented अगर the demod has support क्रम DVB-S or DVB-S2
 */
अटल पूर्णांक vidtv_demod_set_tone(काष्ठा dvb_frontend *fe,
				क्रमागत fe_sec_tone_mode tone)
अणु
	वापस 0;
पूर्ण

/*
 * NOTE:
 * This is implemented here just to be used as an example क्रम real
 * demod drivers.
 *
 * Should only be implemented अगर the demod has support क्रम DVB-S or DVB-S2
 */
अटल पूर्णांक vidtv_demod_set_voltage(काष्ठा dvb_frontend *fe,
				   क्रमागत fe_sec_voltage voltage)
अणु
	वापस 0;
पूर्ण

/*
 * NOTE:
 * This is implemented here just to be used as an example क्रम real
 * demod drivers.
 *
 * Should only be implemented अगर the demod has support क्रम DVB-S or DVB-S2
 */
अटल पूर्णांक vidtv_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				 काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	वापस 0;
पूर्ण

/*
 * NOTE:
 * This is implemented here just to be used as an example क्रम real
 * demod drivers.
 *
 * Should only be implemented अगर the demod has support क्रम DVB-S or DVB-S2
 */
अटल पूर्णांक vidtv_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				   क्रमागत fe_sec_mini_cmd burst)
अणु
	वापस 0;
पूर्ण

अटल व्योम vidtv_demod_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vidtv_demod_state *state = fe->demodulator_priv;

	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops vidtv_demod_ops = अणु
	.delsys = अणु
		SYS_DVBT,
		SYS_DVBT2,
		SYS_DVBC_ANNEX_A,
		SYS_DVBS,
		SYS_DVBS2,
	पूर्ण,

	.info = अणु
		.name                   = "Dummy demod for DVB-T/T2/C/S/S2",
		.frequency_min_hz       = 51 * MHz,
		.frequency_max_hz       = 2150 * MHz,
		.frequency_stepsize_hz  = 62500,
		.frequency_tolerance_hz = 29500 * kHz,
		.symbol_rate_min        = 1000000,
		.symbol_rate_max        = 45000000,

		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_8_9 |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_QAM_AUTO |
			FE_CAN_QPSK |
			FE_CAN_FEC_AUTO |
			FE_CAN_INVERSION_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = vidtv_demod_release,

	.set_frontend = vidtv_demod_set_frontend,
	.get_frontend = vidtv_demod_get_frontend,

	.पढ़ो_status          = vidtv_demod_पढ़ो_status,
	.पढ़ो_संकेत_strength = vidtv_demod_पढ़ो_संकेत_strength,

	/* For DVB-S/S2 */
	.set_voltage		= vidtv_demod_set_voltage,
	.set_tone		= vidtv_demod_set_tone,
	.diseqc_send_master_cmd	= vidtv_send_diseqc_msg,
	.diseqc_send_burst	= vidtv_diseqc_send_burst,

पूर्ण;

अटल स्थिर काष्ठा i2c_device_id vidtv_demod_i2c_id_table[] = अणु
	अणु"dvb_vidtv_demod", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vidtv_demod_i2c_id_table);

अटल पूर्णांक vidtv_demod_i2c_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vidtv_tuner_config *config = client->dev.platक्रमm_data;
	काष्ठा vidtv_demod_state *state;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops,
	       &vidtv_demod_ops,
	       माप(काष्ठा dvb_frontend_ops));

	स_नकल(&state->config, config, माप(state->config));

	state->frontend.demodulator_priv = state;
	i2c_set_clientdata(client, state);

	vidtv_clean_stats(&state->frontend);

	वापस 0;
पूर्ण

अटल पूर्णांक vidtv_demod_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा vidtv_demod_state *state = i2c_get_clientdata(client);

	kमुक्त(state);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver vidtv_demod_i2c_driver = अणु
	.driver = अणु
		.name                = "dvb_vidtv_demod",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe    = vidtv_demod_i2c_probe,
	.हटाओ   = vidtv_demod_i2c_हटाओ,
	.id_table = vidtv_demod_i2c_id_table,
पूर्ण;

module_i2c_driver(vidtv_demod_i2c_driver);

MODULE_DESCRIPTION("Virtual DVB Demodulator Driver");
MODULE_AUTHOR("Daniel W. S. Almeida");
MODULE_LICENSE("GPL");
