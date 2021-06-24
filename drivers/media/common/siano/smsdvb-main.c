<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************

Siano Mobile Silicon, Inc.
MDTV receiver kernel modules.
Copyright (C) 2006-2008, Uri Shkolnik


****************************************************************/

#समावेश "smscoreapi.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>

#समावेश "sms-cards.h"

#समावेश "smsdvb.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल काष्ठा list_head g_smsdvb_clients;
अटल काष्ठा mutex g_smsdvb_clientslock;

अटल u32 sms_to_guard_पूर्णांकerval_table[] = अणु
	[0] = GUARD_INTERVAL_1_32,
	[1] = GUARD_INTERVAL_1_16,
	[2] = GUARD_INTERVAL_1_8,
	[3] = GUARD_INTERVAL_1_4,
पूर्ण;

अटल u32 sms_to_code_rate_table[] = अणु
	[0] = FEC_1_2,
	[1] = FEC_2_3,
	[2] = FEC_3_4,
	[3] = FEC_5_6,
	[4] = FEC_7_8,
पूर्ण;


अटल u32 sms_to_hierarchy_table[] = अणु
	[0] = HIERARCHY_NONE,
	[1] = HIERARCHY_1,
	[2] = HIERARCHY_2,
	[3] = HIERARCHY_4,
पूर्ण;

अटल u32 sms_to_modulation_table[] = अणु
	[0] = QPSK,
	[1] = QAM_16,
	[2] = QAM_64,
	[3] = DQPSK,
पूर्ण;


/* Events that may come from DVB v3 adapter */
अटल व्योम sms_board_dvb3_event(काष्ठा smsdvb_client_t *client,
		क्रमागत SMS_DVB3_EVENTS event) अणु

	काष्ठा smscore_device_t *coredev = client->coredev;
	चयन (event) अणु
	हाल DVB3_EVENT_INIT:
		pr_debug("DVB3_EVENT_INIT\n");
		sms_board_event(coredev, BOARD_EVENT_BIND);
		अवरोध;
	हाल DVB3_EVENT_SLEEP:
		pr_debug("DVB3_EVENT_SLEEP\n");
		sms_board_event(coredev, BOARD_EVENT_POWER_SUSPEND);
		अवरोध;
	हाल DVB3_EVENT_HOTPLUG:
		pr_debug("DVB3_EVENT_HOTPLUG\n");
		sms_board_event(coredev, BOARD_EVENT_POWER_INIT);
		अवरोध;
	हाल DVB3_EVENT_FE_LOCK:
		अगर (client->event_fe_state != DVB3_EVENT_FE_LOCK) अणु
			client->event_fe_state = DVB3_EVENT_FE_LOCK;
			pr_debug("DVB3_EVENT_FE_LOCK\n");
			sms_board_event(coredev, BOARD_EVENT_FE_LOCK);
		पूर्ण
		अवरोध;
	हाल DVB3_EVENT_FE_UNLOCK:
		अगर (client->event_fe_state != DVB3_EVENT_FE_UNLOCK) अणु
			client->event_fe_state = DVB3_EVENT_FE_UNLOCK;
			pr_debug("DVB3_EVENT_FE_UNLOCK\n");
			sms_board_event(coredev, BOARD_EVENT_FE_UNLOCK);
		पूर्ण
		अवरोध;
	हाल DVB3_EVENT_UNC_OK:
		अगर (client->event_unc_state != DVB3_EVENT_UNC_OK) अणु
			client->event_unc_state = DVB3_EVENT_UNC_OK;
			pr_debug("DVB3_EVENT_UNC_OK\n");
			sms_board_event(coredev, BOARD_EVENT_MULTIPLEX_OK);
		पूर्ण
		अवरोध;
	हाल DVB3_EVENT_UNC_ERR:
		अगर (client->event_unc_state != DVB3_EVENT_UNC_ERR) अणु
			client->event_unc_state = DVB3_EVENT_UNC_ERR;
			pr_debug("DVB3_EVENT_UNC_ERR\n");
			sms_board_event(coredev, BOARD_EVENT_MULTIPLEX_ERRORS);
		पूर्ण
		अवरोध;

	शेष:
		pr_err("Unknown dvb3 api event\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम smsdvb_stats_not_पढ़ोy(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा smsdvb_client_t *client =
		container_of(fe, काष्ठा smsdvb_client_t, frontend);
	काष्ठा smscore_device_t *coredev = client->coredev;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक i, n_layers;

	चयन (smscore_get_device_mode(coredev)) अणु
	हाल DEVICE_MODE_ISDBT:
	हाल DEVICE_MODE_ISDBT_BDA:
		n_layers = 4;
		अवरोध;
	शेष:
		n_layers = 1;
	पूर्ण

	/* Global stats */
	c->strength.len = 1;
	c->cnr.len = 1;
	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->cnr.stat[0].scale = FE_SCALE_DECIBEL;

	/* Per-layer stats */
	c->post_bit_error.len = n_layers;
	c->post_bit_count.len = n_layers;
	c->block_error.len = n_layers;
	c->block_count.len = n_layers;

	/*
	 * Put all of them at FE_SCALE_NOT_AVAILABLE. They're dynamically
	 * changed when the stats become available.
	 */
	क्रम (i = 0; i < n_layers; i++) अणु
		c->post_bit_error.stat[i].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[i].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[i].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[i].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक sms_to_mode(u32 mode)
अणु
	चयन (mode) अणु
	हाल 2:
		वापस TRANSMISSION_MODE_2K;
	हाल 4:
		वापस TRANSMISSION_MODE_4K;
	हाल 8:
		वापस TRANSMISSION_MODE_8K;
	पूर्ण
	वापस TRANSMISSION_MODE_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक sms_to_isdbt_mode(u32 mode)
अणु
	चयन (mode) अणु
	हाल 1:
		वापस TRANSMISSION_MODE_2K;
	हाल 2:
		वापस TRANSMISSION_MODE_4K;
	हाल 3:
		वापस TRANSMISSION_MODE_8K;
	पूर्ण
	वापस TRANSMISSION_MODE_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक sms_to_isdbt_guard_पूर्णांकerval(u32 पूर्णांकerval)
अणु
	चयन (पूर्णांकerval) अणु
	हाल 4:
		वापस GUARD_INTERVAL_1_4;
	हाल 8:
		वापस GUARD_INTERVAL_1_8;
	हाल 16:
		वापस GUARD_INTERVAL_1_16;
	हाल 32:
		वापस GUARD_INTERVAL_1_32;
	पूर्ण
	वापस GUARD_INTERVAL_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक sms_to_status(u32 is_demod_locked, u32 is_rf_locked)
अणु
	अगर (is_demod_locked)
		वापस FE_HAS_SIGNAL  | FE_HAS_CARRIER | FE_HAS_VITERBI |
		       FE_HAS_SYNC    | FE_HAS_LOCK;

	अगर (is_rf_locked)
		वापस FE_HAS_SIGNAL | FE_HAS_CARRIER;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 sms_to_bw(u32 value)
अणु
	वापस value * 1000000;
पूर्ण

#घोषणा convert_from_table(value, table, defval) (अणु			\
	u32 __ret;							\
	अगर (value < ARRAY_SIZE(table))					\
		__ret = table[value];					\
	अन्यथा								\
		__ret = defval;						\
	__ret;								\
पूर्ण)

#घोषणा sms_to_guard_पूर्णांकerval(value)					\
	convert_from_table(value, sms_to_guard_पूर्णांकerval_table,		\
			   GUARD_INTERVAL_AUTO);

#घोषणा sms_to_code_rate(value)						\
	convert_from_table(value, sms_to_code_rate_table,		\
			   FEC_NONE);

#घोषणा sms_to_hierarchy(value)						\
	convert_from_table(value, sms_to_hierarchy_table,		\
			   FEC_NONE);

#घोषणा sms_to_modulation(value)					\
	convert_from_table(value, sms_to_modulation_table,		\
			   FEC_NONE);

अटल व्योम smsdvb_update_tx_params(काष्ठा smsdvb_client_t *client,
				    काष्ठा sms_tx_stats *p)
अणु
	काष्ठा dvb_frontend *fe = &client->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	c->frequency = p->frequency;
	client->fe_status = sms_to_status(p->is_demod_locked, 0);
	c->bandwidth_hz = sms_to_bw(p->bandwidth);
	c->transmission_mode = sms_to_mode(p->transmission_mode);
	c->guard_पूर्णांकerval = sms_to_guard_पूर्णांकerval(p->guard_पूर्णांकerval);
	c->code_rate_HP = sms_to_code_rate(p->code_rate);
	c->code_rate_LP = sms_to_code_rate(p->lp_code_rate);
	c->hierarchy = sms_to_hierarchy(p->hierarchy);
	c->modulation = sms_to_modulation(p->स्थिरellation);
पूर्ण

अटल व्योम smsdvb_update_per_slices(काष्ठा smsdvb_client_t *client,
				     काष्ठा RECEPTION_STATISTICS_PER_SLICES_S *p)
अणु
	काष्ठा dvb_frontend *fe = &client->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u64 पंचांगp;

	client->fe_status = sms_to_status(p->is_demod_locked, p->is_rf_locked);
	c->modulation = sms_to_modulation(p->स्थिरellation);

	/* संकेत Strength, in DBm */
	c->strength.stat[0].uvalue = p->in_band_घातer * 1000;

	/* Carrier to noise ratio, in DB */
	c->cnr.stat[0].svalue = p->snr * 1000;

	/* PER/BER requires demod lock */
	अगर (!p->is_demod_locked)
		वापस;

	/* TS PER */
	client->last_per = c->block_error.stat[0].uvalue;
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->block_error.stat[0].uvalue += p->ets_packets;
	c->block_count.stat[0].uvalue += p->ets_packets + p->ts_packets;

	/* ber */
	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue += p->ber_error_count;
	c->post_bit_count.stat[0].uvalue += p->ber_bit_count;

	/* Legacy PER/BER */
	पंचांगp = p->ets_packets * 65535ULL;
	अगर (p->ts_packets + p->ets_packets)
		करो_भाग(पंचांगp, p->ts_packets + p->ets_packets);
	client->legacy_per = पंचांगp;
पूर्ण

अटल व्योम smsdvb_update_dvb_stats(काष्ठा smsdvb_client_t *client,
				    काष्ठा sms_stats *p)
अणु
	काष्ठा dvb_frontend *fe = &client->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (client->prt_dvb_stats)
		client->prt_dvb_stats(client->debug_data, p);

	client->fe_status = sms_to_status(p->is_demod_locked, p->is_rf_locked);

	/* Update DVB modulation parameters */
	c->frequency = p->frequency;
	client->fe_status = sms_to_status(p->is_demod_locked, 0);
	c->bandwidth_hz = sms_to_bw(p->bandwidth);
	c->transmission_mode = sms_to_mode(p->transmission_mode);
	c->guard_पूर्णांकerval = sms_to_guard_पूर्णांकerval(p->guard_पूर्णांकerval);
	c->code_rate_HP = sms_to_code_rate(p->code_rate);
	c->code_rate_LP = sms_to_code_rate(p->lp_code_rate);
	c->hierarchy = sms_to_hierarchy(p->hierarchy);
	c->modulation = sms_to_modulation(p->स्थिरellation);

	/* update reception data */
	c->lna = p->is_बाह्यal_lna_on ? 1 : 0;

	/* Carrier to noise ratio, in DB */
	c->cnr.stat[0].svalue = p->SNR * 1000;

	/* संकेत Strength, in DBm */
	c->strength.stat[0].uvalue = p->in_band_pwr * 1000;

	/* PER/BER requires demod lock */
	अगर (!p->is_demod_locked)
		वापस;

	/* TS PER */
	client->last_per = c->block_error.stat[0].uvalue;
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->block_error.stat[0].uvalue += p->error_ts_packets;
	c->block_count.stat[0].uvalue += p->total_ts_packets;

	/* ber */
	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue += p->ber_error_count;
	c->post_bit_count.stat[0].uvalue += p->ber_bit_count;

	/* Legacy PER/BER */
	client->legacy_ber = p->ber;
पूर्ण;

अटल व्योम smsdvb_update_isdbt_stats(काष्ठा smsdvb_client_t *client,
				      काष्ठा sms_isdbt_stats *p)
अणु
	काष्ठा dvb_frontend *fe = &client->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा sms_isdbt_layer_stats *lr;
	पूर्णांक i, n_layers;

	अगर (client->prt_isdb_stats)
		client->prt_isdb_stats(client->debug_data, p);

	client->fe_status = sms_to_status(p->is_demod_locked, p->is_rf_locked);

	/*
	 * Firmware 2.1 seems to report only lock status and
	 * संकेत strength. The संकेत strength indicator is at the
	 * wrong field.
	 */
	अगर (p->statistics_type == 0) अणु
		c->strength.stat[0].uvalue = ((s32)p->transmission_mode) * 1000;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	/* Update ISDB-T transmission parameters */
	c->frequency = p->frequency;
	c->bandwidth_hz = sms_to_bw(p->bandwidth);
	c->transmission_mode = sms_to_isdbt_mode(p->transmission_mode);
	c->guard_पूर्णांकerval = sms_to_isdbt_guard_पूर्णांकerval(p->guard_पूर्णांकerval);
	c->isdbt_partial_reception = p->partial_reception ? 1 : 0;
	n_layers = p->num_of_layers;
	अगर (n_layers < 1)
		n_layers = 1;
	अगर (n_layers > 3)
		n_layers = 3;
	c->isdbt_layer_enabled = 0;

	/* update reception data */
	c->lna = p->is_बाह्यal_lna_on ? 1 : 0;

	/* Carrier to noise ratio, in DB */
	c->cnr.stat[0].svalue = p->SNR * 1000;

	/* संकेत Strength, in DBm */
	c->strength.stat[0].uvalue = p->in_band_pwr * 1000;

	/* PER/BER and per-layer stats require demod lock */
	अगर (!p->is_demod_locked)
		वापस;

	client->last_per = c->block_error.stat[0].uvalue;

	/* Clears global counters, as the code below will sum it again */
	c->block_error.stat[0].uvalue = 0;
	c->block_count.stat[0].uvalue = 0;
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue = 0;
	c->post_bit_count.stat[0].uvalue = 0;
	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;

	क्रम (i = 0; i < n_layers; i++) अणु
		lr = &p->layer_info[i];

		/* Update per-layer transmission parameters */
		अगर (lr->number_of_segments > 0 && lr->number_of_segments < 13) अणु
			c->isdbt_layer_enabled |= 1 << i;
			c->layer[i].segment_count = lr->number_of_segments;
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण
		c->layer[i].modulation = sms_to_modulation(lr->स्थिरellation);
		c->layer[i].fec = sms_to_code_rate(lr->code_rate);

		/* Time पूर्णांकerleaving */
		c->layer[i].पूर्णांकerleaving = (u8)lr->ti_ldepth_i;

		/* TS PER */
		c->block_error.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->block_count.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->block_error.stat[i + 1].uvalue += lr->error_ts_packets;
		c->block_count.stat[i + 1].uvalue += lr->total_ts_packets;

		/* Update global PER counter */
		c->block_error.stat[0].uvalue += lr->error_ts_packets;
		c->block_count.stat[0].uvalue += lr->total_ts_packets;

		/* BER */
		c->post_bit_error.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[i + 1].uvalue += lr->ber_error_count;
		c->post_bit_count.stat[i + 1].uvalue += lr->ber_bit_count;

		/* Update global BER counter */
		c->post_bit_error.stat[0].uvalue += lr->ber_error_count;
		c->post_bit_count.stat[0].uvalue += lr->ber_bit_count;
	पूर्ण
पूर्ण

अटल व्योम smsdvb_update_isdbt_stats_ex(काष्ठा smsdvb_client_t *client,
					 काष्ठा sms_isdbt_stats_ex *p)
अणु
	काष्ठा dvb_frontend *fe = &client->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा sms_isdbt_layer_stats *lr;
	पूर्णांक i, n_layers;

	अगर (client->prt_isdb_stats_ex)
		client->prt_isdb_stats_ex(client->debug_data, p);

	/* Update ISDB-T transmission parameters */
	c->frequency = p->frequency;
	client->fe_status = sms_to_status(p->is_demod_locked, 0);
	c->bandwidth_hz = sms_to_bw(p->bandwidth);
	c->transmission_mode = sms_to_isdbt_mode(p->transmission_mode);
	c->guard_पूर्णांकerval = sms_to_isdbt_guard_पूर्णांकerval(p->guard_पूर्णांकerval);
	c->isdbt_partial_reception = p->partial_reception ? 1 : 0;
	n_layers = p->num_of_layers;
	अगर (n_layers < 1)
		n_layers = 1;
	अगर (n_layers > 3)
		n_layers = 3;
	c->isdbt_layer_enabled = 0;

	/* update reception data */
	c->lna = p->is_बाह्यal_lna_on ? 1 : 0;

	/* Carrier to noise ratio, in DB */
	c->cnr.stat[0].svalue = p->SNR * 1000;

	/* संकेत Strength, in DBm */
	c->strength.stat[0].uvalue = p->in_band_pwr * 1000;

	/* PER/BER and per-layer stats require demod lock */
	अगर (!p->is_demod_locked)
		वापस;

	client->last_per = c->block_error.stat[0].uvalue;

	/* Clears global counters, as the code below will sum it again */
	c->block_error.stat[0].uvalue = 0;
	c->block_count.stat[0].uvalue = 0;
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue = 0;
	c->post_bit_count.stat[0].uvalue = 0;
	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;

	c->post_bit_error.len = n_layers + 1;
	c->post_bit_count.len = n_layers + 1;
	c->block_error.len = n_layers + 1;
	c->block_count.len = n_layers + 1;
	क्रम (i = 0; i < n_layers; i++) अणु
		lr = &p->layer_info[i];

		/* Update per-layer transmission parameters */
		अगर (lr->number_of_segments > 0 && lr->number_of_segments < 13) अणु
			c->isdbt_layer_enabled |= 1 << i;
			c->layer[i].segment_count = lr->number_of_segments;
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण
		c->layer[i].modulation = sms_to_modulation(lr->स्थिरellation);
		c->layer[i].fec = sms_to_code_rate(lr->code_rate);

		/* Time पूर्णांकerleaving */
		c->layer[i].पूर्णांकerleaving = (u8)lr->ti_ldepth_i;

		/* TS PER */
		c->block_error.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->block_count.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->block_error.stat[i + 1].uvalue += lr->error_ts_packets;
		c->block_count.stat[i + 1].uvalue += lr->total_ts_packets;

		/* Update global PER counter */
		c->block_error.stat[0].uvalue += lr->error_ts_packets;
		c->block_count.stat[0].uvalue += lr->total_ts_packets;

		/* ber */
		c->post_bit_error.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[i + 1].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[i + 1].uvalue += lr->ber_error_count;
		c->post_bit_count.stat[i + 1].uvalue += lr->ber_bit_count;

		/* Update global ber counter */
		c->post_bit_error.stat[0].uvalue += lr->ber_error_count;
		c->post_bit_count.stat[0].uvalue += lr->ber_bit_count;
	पूर्ण
पूर्ण

अटल पूर्णांक smsdvb_onresponse(व्योम *context, काष्ठा smscore_buffer_t *cb)
अणु
	काष्ठा smsdvb_client_t *client = (काष्ठा smsdvb_client_t *) context;
	काष्ठा sms_msg_hdr *phdr = (काष्ठा sms_msg_hdr *) (((u8 *) cb->p)
			+ cb->offset);
	व्योम *p = phdr + 1;
	काष्ठा dvb_frontend *fe = &client->frontend;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	bool is_status_update = false;

	चयन (phdr->msg_type) अणु
	हाल MSG_SMS_DVBT_BDA_DATA:
		/*
		 * Only feed data to dvb demux अगर are there any feed listening
		 * to it and अगर the device has tuned
		 */
		अगर (client->feed_users && client->has_tuned)
			dvb_dmx_swfilter(&client->demux, p,
					 cb->size - माप(काष्ठा sms_msg_hdr));
		अवरोध;

	हाल MSG_SMS_RF_TUNE_RES:
	हाल MSG_SMS_ISDBT_TUNE_RES:
		complete(&client->tune_करोne);
		अवरोध;

	हाल MSG_SMS_SIGNAL_DETECTED_IND:
		client->fe_status = FE_HAS_SIGNAL  | FE_HAS_CARRIER |
				    FE_HAS_VITERBI | FE_HAS_SYNC    |
				    FE_HAS_LOCK;

		is_status_update = true;
		अवरोध;

	हाल MSG_SMS_NO_SIGNAL_IND:
		client->fe_status = 0;

		is_status_update = true;
		अवरोध;

	हाल MSG_SMS_TRANSMISSION_IND:
		smsdvb_update_tx_params(client, p);

		is_status_update = true;
		अवरोध;

	हाल MSG_SMS_HO_PER_SLICES_IND:
		smsdvb_update_per_slices(client, p);

		is_status_update = true;
		अवरोध;

	हाल MSG_SMS_GET_STATISTICS_RES:
		चयन (smscore_get_device_mode(client->coredev)) अणु
		हाल DEVICE_MODE_ISDBT:
		हाल DEVICE_MODE_ISDBT_BDA:
			smsdvb_update_isdbt_stats(client, p);
			अवरोध;
		शेष:
			/* Skip sms_msg_statistics_info:request_result field */
			smsdvb_update_dvb_stats(client, p + माप(u32));
		पूर्ण

		is_status_update = true;
		अवरोध;

	/* Only क्रम ISDB-T */
	हाल MSG_SMS_GET_STATISTICS_EX_RES:
		/* Skip sms_msg_statistics_info:request_result field? */
		smsdvb_update_isdbt_stats_ex(client, p + माप(u32));
		is_status_update = true;
		अवरोध;
	शेष:
		pr_debug("message not handled\n");
	पूर्ण
	smscore_putbuffer(client->coredev, cb);

	अगर (is_status_update) अणु
		अगर (client->fe_status & FE_HAS_LOCK) अणु
			sms_board_dvb3_event(client, DVB3_EVENT_FE_LOCK);
			अगर (client->last_per == c->block_error.stat[0].uvalue)
				sms_board_dvb3_event(client, DVB3_EVENT_UNC_OK);
			अन्यथा
				sms_board_dvb3_event(client, DVB3_EVENT_UNC_ERR);
			client->has_tuned = true;
		पूर्ण अन्यथा अणु
			smsdvb_stats_not_पढ़ोy(fe);
			client->has_tuned = false;
			sms_board_dvb3_event(client, DVB3_EVENT_FE_UNLOCK);
		पूर्ण
		complete(&client->stats_करोne);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम smsdvb_media_device_unरेजिस्टर(काष्ठा smsdvb_client_t *client)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा smscore_device_t *coredev = client->coredev;

	अगर (!coredev->media_dev)
		वापस;
	media_device_unरेजिस्टर(coredev->media_dev);
	media_device_cleanup(coredev->media_dev);
	kमुक्त(coredev->media_dev);
	coredev->media_dev = शून्य;
#पूर्ण_अगर
पूर्ण

अटल व्योम smsdvb_unरेजिस्टर_client(काष्ठा smsdvb_client_t *client)
अणु
	/* must be called under clientslock */

	list_del(&client->entry);

	smsdvb_debugfs_release(client);
	smscore_unरेजिस्टर_client(client->smsclient);
	dvb_unरेजिस्टर_frontend(&client->frontend);
	dvb_dmxdev_release(&client->dmxdev);
	dvb_dmx_release(&client->demux);
	smsdvb_media_device_unरेजिस्टर(client);
	dvb_unरेजिस्टर_adapter(&client->adapter);
	kमुक्त(client);
पूर्ण

अटल व्योम smsdvb_onहटाओ(व्योम *context)
अणु
	mutex_lock(&g_smsdvb_clientslock);

	smsdvb_unरेजिस्टर_client((काष्ठा smsdvb_client_t *) context);

	mutex_unlock(&g_smsdvb_clientslock);
पूर्ण

अटल पूर्णांक smsdvb_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा smsdvb_client_t *client =
		container_of(feed->demux, काष्ठा smsdvb_client_t, demux);
	काष्ठा sms_msg_data pid_msg;

	pr_debug("add pid %d(%x)\n",
		  feed->pid, feed->pid);

	client->feed_users++;

	pid_msg.x_msg_header.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	pid_msg.x_msg_header.msg_dst_id = HIF_TASK;
	pid_msg.x_msg_header.msg_flags = 0;
	pid_msg.x_msg_header.msg_type  = MSG_SMS_ADD_PID_FILTER_REQ;
	pid_msg.x_msg_header.msg_length = माप(pid_msg);
	pid_msg.msg_data[0] = feed->pid;

	वापस smsclient_sendrequest(client->smsclient,
				     &pid_msg, माप(pid_msg));
पूर्ण

अटल पूर्णांक smsdvb_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा smsdvb_client_t *client =
		container_of(feed->demux, काष्ठा smsdvb_client_t, demux);
	काष्ठा sms_msg_data pid_msg;

	pr_debug("remove pid %d(%x)\n",
		  feed->pid, feed->pid);

	client->feed_users--;

	pid_msg.x_msg_header.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	pid_msg.x_msg_header.msg_dst_id = HIF_TASK;
	pid_msg.x_msg_header.msg_flags = 0;
	pid_msg.x_msg_header.msg_type  = MSG_SMS_REMOVE_PID_FILTER_REQ;
	pid_msg.x_msg_header.msg_length = माप(pid_msg);
	pid_msg.msg_data[0] = feed->pid;

	वापस smsclient_sendrequest(client->smsclient,
				     &pid_msg, माप(pid_msg));
पूर्ण

अटल पूर्णांक smsdvb_sendrequest_and_रुको(काष्ठा smsdvb_client_t *client,
					व्योम *buffer, माप_प्रकार size,
					काष्ठा completion *completion)
अणु
	पूर्णांक rc;

	rc = smsclient_sendrequest(client->smsclient, buffer, size);
	अगर (rc < 0)
		वापस rc;

	वापस रुको_क्रम_completion_समयout(completion,
					   msecs_to_jअगरfies(2000)) ?
						0 : -ETIME;
पूर्ण

अटल पूर्णांक smsdvb_send_statistics_request(काष्ठा smsdvb_client_t *client)
अणु
	पूर्णांक rc;
	काष्ठा sms_msg_hdr msg;

	/* Don't request stats too fast */
	अगर (client->get_stats_jअगरfies &&
	   (!समय_after(jअगरfies, client->get_stats_jअगरfies)))
		वापस 0;
	client->get_stats_jअगरfies = jअगरfies + msecs_to_jअगरfies(100);

	msg.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	msg.msg_dst_id = HIF_TASK;
	msg.msg_flags = 0;
	msg.msg_length = माप(msg);

	चयन (smscore_get_device_mode(client->coredev)) अणु
	हाल DEVICE_MODE_ISDBT:
	हाल DEVICE_MODE_ISDBT_BDA:
		/*
		* Check क्रम firmware version, to aव्योम अवरोधing क्रम old cards
		*/
		अगर (client->coredev->fw_version >= 0x800)
			msg.msg_type = MSG_SMS_GET_STATISTICS_EX_REQ;
		अन्यथा
			msg.msg_type = MSG_SMS_GET_STATISTICS_REQ;
		अवरोध;
	शेष:
		msg.msg_type = MSG_SMS_GET_STATISTICS_REQ;
	पूर्ण

	rc = smsdvb_sendrequest_and_रुको(client, &msg, माप(msg),
					 &client->stats_करोne);

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक led_feedback(काष्ठा smsdvb_client_t *client)
अणु
	अगर (!(client->fe_status & FE_HAS_LOCK))
		वापस sms_board_led_feedback(client->coredev, SMS_LED_OFF);

	वापस sms_board_led_feedback(client->coredev,
				     (client->legacy_ber == 0) ?
				     SMS_LED_HI : SMS_LED_LO);
पूर्ण

अटल पूर्णांक smsdvb_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat)
अणु
	पूर्णांक rc;
	काष्ठा smsdvb_client_t *client;
	client = container_of(fe, काष्ठा smsdvb_client_t, frontend);

	rc = smsdvb_send_statistics_request(client);

	*stat = client->fe_status;

	led_feedback(client);

	वापस rc;
पूर्ण

अटल पूर्णांक smsdvb_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	पूर्णांक rc;
	काष्ठा smsdvb_client_t *client;

	client = container_of(fe, काष्ठा smsdvb_client_t, frontend);

	rc = smsdvb_send_statistics_request(client);

	*ber = client->legacy_ber;

	led_feedback(client);

	वापस rc;
पूर्ण

अटल पूर्णांक smsdvb_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc;
	s32 घातer = (s32) c->strength.stat[0].uvalue;
	काष्ठा smsdvb_client_t *client;

	client = container_of(fe, काष्ठा smsdvb_client_t, frontend);

	rc = smsdvb_send_statistics_request(client);

	अगर (घातer < -95)
		*strength = 0;
		अन्यथा अगर (घातer > -29)
			*strength = 65535;
		अन्यथा
			*strength = (घातer + 95) * 65535 / 66;

	led_feedback(client);

	वापस rc;
पूर्ण

अटल पूर्णांक smsdvb_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक rc;
	काष्ठा smsdvb_client_t *client;

	client = container_of(fe, काष्ठा smsdvb_client_t, frontend);

	rc = smsdvb_send_statistics_request(client);

	/* Preferred scale क्रम SNR with legacy API: 0.1 dB */
	*snr = ((u32)c->cnr.stat[0].svalue) / 100;

	led_feedback(client);

	वापस rc;
पूर्ण

अटल पूर्णांक smsdvb_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	पूर्णांक rc;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा smsdvb_client_t *client;

	client = container_of(fe, काष्ठा smsdvb_client_t, frontend);

	rc = smsdvb_send_statistics_request(client);

	*ucblocks = c->block_error.stat[0].uvalue;

	led_feedback(client);

	वापस rc;
पूर्ण

अटल पूर्णांक smsdvb_get_tune_settings(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_frontend_tune_settings *tune)
अणु
	pr_debug("\n");

	tune->min_delay_ms = 400;
	tune->step_size = 250000;
	tune->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक smsdvb_dvbt_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा smsdvb_client_t *client =
		container_of(fe, काष्ठा smsdvb_client_t, frontend);

	काष्ठा अणु
		काष्ठा sms_msg_hdr	msg;
		u32		Data[3];
	पूर्ण msg;

	पूर्णांक ret;

	client->fe_status = 0;
	client->event_fe_state = -1;
	client->event_unc_state = -1;
	fe->dtv_property_cache.delivery_प्रणाली = SYS_DVBT;

	msg.msg.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	msg.msg.msg_dst_id = HIF_TASK;
	msg.msg.msg_flags = 0;
	msg.msg.msg_type = MSG_SMS_RF_TUNE_REQ;
	msg.msg.msg_length = माप(msg);
	msg.Data[0] = c->frequency;
	msg.Data[2] = 12000000;

	pr_debug("%s: freq %d band %d\n", __func__, c->frequency,
		 c->bandwidth_hz);

	चयन (c->bandwidth_hz / 1000000) अणु
	हाल 8:
		msg.Data[1] = BW_8_MHZ;
		अवरोध;
	हाल 7:
		msg.Data[1] = BW_7_MHZ;
		अवरोध;
	हाल 6:
		msg.Data[1] = BW_6_MHZ;
		अवरोध;
	हाल 0:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Disable LNA, अगर any. An error is वापसed अगर no LNA is present */
	ret = sms_board_lna_control(client->coredev, 0);
	अगर (ret == 0) अणु
		क्रमागत fe_status status;

		/* tune with LNA off at first */
		ret = smsdvb_sendrequest_and_रुको(client, &msg, माप(msg),
						  &client->tune_करोne);

		smsdvb_पढ़ो_status(fe, &status);

		अगर (status & FE_HAS_LOCK)
			वापस ret;

		/* previous tune didn't lock - enable LNA and tune again */
		sms_board_lna_control(client->coredev, 1);
	पूर्ण

	वापस smsdvb_sendrequest_and_रुको(client, &msg, माप(msg),
					   &client->tune_करोne);
पूर्ण

अटल पूर्णांक smsdvb_isdbt_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा smsdvb_client_t *client =
		container_of(fe, काष्ठा smsdvb_client_t, frontend);
	पूर्णांक board_id = smscore_get_board_id(client->coredev);
	काष्ठा sms_board *board = sms_get_board(board_id);
	क्रमागत sms_device_type_st type = board->type;
	पूर्णांक ret;

	काष्ठा अणु
		काष्ठा sms_msg_hdr	msg;
		u32		Data[4];
	पूर्ण msg;

	fe->dtv_property_cache.delivery_प्रणाली = SYS_ISDBT;

	msg.msg.msg_src_id  = DVBT_BDA_CONTROL_MSG_ID;
	msg.msg.msg_dst_id  = HIF_TASK;
	msg.msg.msg_flags  = 0;
	msg.msg.msg_type   = MSG_SMS_ISDBT_TUNE_REQ;
	msg.msg.msg_length = माप(msg);

	अगर (c->isdbt_sb_segment_idx == -1)
		c->isdbt_sb_segment_idx = 0;

	अगर (!c->isdbt_layer_enabled)
		c->isdbt_layer_enabled = 7;

	msg.Data[0] = c->frequency;
	msg.Data[1] = BW_ISDBT_1SEG;
	msg.Data[2] = 12000000;
	msg.Data[3] = c->isdbt_sb_segment_idx;

	अगर (c->isdbt_partial_reception) अणु
		अगर ((type == SMS_PELE || type == SMS_RIO) &&
		    c->isdbt_sb_segment_count > 3)
			msg.Data[1] = BW_ISDBT_13SEG;
		अन्यथा अगर (c->isdbt_sb_segment_count > 1)
			msg.Data[1] = BW_ISDBT_3SEG;
	पूर्ण अन्यथा अगर (type == SMS_PELE || type == SMS_RIO)
		msg.Data[1] = BW_ISDBT_13SEG;

	c->bandwidth_hz = 6000000;

	pr_debug("freq %d segwidth %d segindex %d\n",
		 c->frequency, c->isdbt_sb_segment_count,
		 c->isdbt_sb_segment_idx);

	/* Disable LNA, अगर any. An error is वापसed अगर no LNA is present */
	ret = sms_board_lna_control(client->coredev, 0);
	अगर (ret == 0) अणु
		क्रमागत fe_status status;

		/* tune with LNA off at first */
		ret = smsdvb_sendrequest_and_रुको(client, &msg, माप(msg),
						  &client->tune_करोne);

		smsdvb_पढ़ो_status(fe, &status);

		अगर (status & FE_HAS_LOCK)
			वापस ret;

		/* previous tune didn't lock - enable LNA and tune again */
		sms_board_lna_control(client->coredev, 1);
	पूर्ण
	वापस smsdvb_sendrequest_and_रुको(client, &msg, माप(msg),
					   &client->tune_करोne);
पूर्ण

अटल पूर्णांक smsdvb_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा smsdvb_client_t *client =
		container_of(fe, काष्ठा smsdvb_client_t, frontend);
	काष्ठा smscore_device_t *coredev = client->coredev;

	smsdvb_stats_not_पढ़ोy(fe);
	c->strength.stat[0].uvalue = 0;
	c->cnr.stat[0].uvalue = 0;

	client->has_tuned = false;

	चयन (smscore_get_device_mode(coredev)) अणु
	हाल DEVICE_MODE_DVBT:
	हाल DEVICE_MODE_DVBT_BDA:
		वापस smsdvb_dvbt_set_frontend(fe);
	हाल DEVICE_MODE_ISDBT:
	हाल DEVICE_MODE_ISDBT_BDA:
		वापस smsdvb_isdbt_set_frontend(fe);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक smsdvb_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा smsdvb_client_t *client =
		container_of(fe, काष्ठा smsdvb_client_t, frontend);

	sms_board_घातer(client->coredev, 1);

	sms_board_dvb3_event(client, DVB3_EVENT_INIT);
	वापस 0;
पूर्ण

अटल पूर्णांक smsdvb_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा smsdvb_client_t *client =
		container_of(fe, काष्ठा smsdvb_client_t, frontend);

	sms_board_led_feedback(client->coredev, SMS_LED_OFF);
	sms_board_घातer(client->coredev, 0);

	sms_board_dvb3_event(client, DVB3_EVENT_SLEEP);

	वापस 0;
पूर्ण

अटल व्योम smsdvb_release(काष्ठा dvb_frontend *fe)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops smsdvb_fe_ops = अणु
	.info = अणु
		.name			= "Siano Mobile Digital MDTV Receiver",
		.frequency_min_hz	=  44250 * kHz,
		.frequency_max_hz	= 867250 * kHz,
		.frequency_stepsize_hz	=    250 * kHz,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO | FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_RECOVER |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = smsdvb_release,

	.set_frontend = smsdvb_set_frontend,
	.get_tune_settings = smsdvb_get_tune_settings,

	.पढ़ो_status = smsdvb_पढ़ो_status,
	.पढ़ो_ber = smsdvb_पढ़ो_ber,
	.पढ़ो_संकेत_strength = smsdvb_पढ़ो_संकेत_strength,
	.पढ़ो_snr = smsdvb_पढ़ो_snr,
	.पढ़ो_ucblocks = smsdvb_पढ़ो_ucblocks,

	.init = smsdvb_init,
	.sleep = smsdvb_sleep,
पूर्ण;

अटल पूर्णांक smsdvb_hotplug(काष्ठा smscore_device_t *coredev,
			  काष्ठा device *device, पूर्णांक arrival)
अणु
	काष्ठा smsclient_params_t params;
	काष्ठा smsdvb_client_t *client;
	पूर्णांक rc;

	/* device removal handled by onहटाओ callback */
	अगर (!arrival)
		वापस 0;
	client = kzalloc(माप(काष्ठा smsdvb_client_t), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;

	/* रेजिस्टर dvb adapter */
	rc = dvb_रेजिस्टर_adapter(&client->adapter,
				  sms_get_board(
					smscore_get_board_id(coredev))->name,
				  THIS_MODULE, device, adapter_nr);
	अगर (rc < 0) अणु
		pr_err("dvb_register_adapter() failed %d\n", rc);
		जाओ adapter_error;
	पूर्ण
	dvb_रेजिस्टर_media_controller(&client->adapter, coredev->media_dev);

	/* init dvb demux */
	client->demux.dmx.capabilities = DMX_TS_FILTERING;
	client->demux.filternum = 32; /* toकरो: nova ??? */
	client->demux.feednum = 32;
	client->demux.start_feed = smsdvb_start_feed;
	client->demux.stop_feed = smsdvb_stop_feed;

	rc = dvb_dmx_init(&client->demux);
	अगर (rc < 0) अणु
		pr_err("dvb_dmx_init failed %d\n", rc);
		जाओ dvbdmx_error;
	पूर्ण

	/* init dmxdev */
	client->dmxdev.filternum = 32;
	client->dmxdev.demux = &client->demux.dmx;
	client->dmxdev.capabilities = 0;

	rc = dvb_dmxdev_init(&client->dmxdev, &client->adapter);
	अगर (rc < 0) अणु
		pr_err("dvb_dmxdev_init failed %d\n", rc);
		जाओ dmxdev_error;
	पूर्ण

	/* init and रेजिस्टर frontend */
	स_नकल(&client->frontend.ops, &smsdvb_fe_ops,
	       माप(काष्ठा dvb_frontend_ops));

	चयन (smscore_get_device_mode(coredev)) अणु
	हाल DEVICE_MODE_DVBT:
	हाल DEVICE_MODE_DVBT_BDA:
		client->frontend.ops.delsys[0] = SYS_DVBT;
		अवरोध;
	हाल DEVICE_MODE_ISDBT:
	हाल DEVICE_MODE_ISDBT_BDA:
		client->frontend.ops.delsys[0] = SYS_ISDBT;
		अवरोध;
	पूर्ण

	rc = dvb_रेजिस्टर_frontend(&client->adapter, &client->frontend);
	अगर (rc < 0) अणु
		pr_err("frontend registration failed %d\n", rc);
		जाओ frontend_error;
	पूर्ण

	params.initial_id = 1;
	params.data_type = MSG_SMS_DVBT_BDA_DATA;
	params.onresponse_handler = smsdvb_onresponse;
	params.onहटाओ_handler = smsdvb_onहटाओ;
	params.context = client;

	rc = smscore_रेजिस्टर_client(coredev, &params, &client->smsclient);
	अगर (rc < 0) अणु
		pr_err("smscore_register_client() failed %d\n", rc);
		जाओ client_error;
	पूर्ण

	client->coredev = coredev;

	init_completion(&client->tune_करोne);
	init_completion(&client->stats_करोne);

	mutex_lock(&g_smsdvb_clientslock);

	list_add(&client->entry, &g_smsdvb_clients);

	mutex_unlock(&g_smsdvb_clientslock);

	client->event_fe_state = -1;
	client->event_unc_state = -1;
	sms_board_dvb3_event(client, DVB3_EVENT_HOTPLUG);

	sms_board_setup(coredev);

	अगर (smsdvb_debugfs_create(client) < 0)
		pr_info("failed to create debugfs node\n");

	rc = dvb_create_media_graph(&client->adapter, true);
	अगर (rc < 0) अणु
		pr_err("dvb_create_media_graph failed %d\n", rc);
		जाओ media_graph_error;
	पूर्ण

	pr_info("DVB interface registered.\n");
	वापस 0;

media_graph_error:
	smsdvb_debugfs_release(client);

client_error:
	dvb_unरेजिस्टर_frontend(&client->frontend);

frontend_error:
	dvb_dmxdev_release(&client->dmxdev);

dmxdev_error:
	dvb_dmx_release(&client->demux);

dvbdmx_error:
	smsdvb_media_device_unरेजिस्टर(client);
	dvb_unरेजिस्टर_adapter(&client->adapter);

adapter_error:
	kमुक्त(client);
	वापस rc;
पूर्ण

अटल पूर्णांक __init smsdvb_module_init(व्योम)
अणु
	पूर्णांक rc;

	INIT_LIST_HEAD(&g_smsdvb_clients);
	mutex_init(&g_smsdvb_clientslock);

	smsdvb_debugfs_रेजिस्टर();

	rc = smscore_रेजिस्टर_hotplug(smsdvb_hotplug);

	pr_debug("\n");

	वापस rc;
पूर्ण

अटल व्योम __निकास smsdvb_module_निकास(व्योम)
अणु
	smscore_unरेजिस्टर_hotplug(smsdvb_hotplug);

	mutex_lock(&g_smsdvb_clientslock);

	जबतक (!list_empty(&g_smsdvb_clients))
		smsdvb_unरेजिस्टर_client((काष्ठा smsdvb_client_t *)g_smsdvb_clients.next);

	smsdvb_debugfs_unरेजिस्टर();

	mutex_unlock(&g_smsdvb_clientslock);
पूर्ण

module_init(smsdvb_module_init);
module_निकास(smsdvb_module_निकास);

MODULE_DESCRIPTION("SMS DVB subsystem adaptation module");
MODULE_AUTHOR("Siano Mobile Silicon, Inc. (uris@siano-ms.com)");
MODULE_LICENSE("GPL");
