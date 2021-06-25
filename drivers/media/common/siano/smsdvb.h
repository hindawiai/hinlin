<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***********************************************************************
 *
 ***********************************************************************/

काष्ठा smsdvb_debugfs;
काष्ठा smsdvb_client_t;

प्रकार व्योम (*sms_prt_dvb_stats_t)(काष्ठा smsdvb_debugfs *debug_data,
				    काष्ठा sms_stats *p);

प्रकार व्योम (*sms_prt_isdb_stats_t)(काष्ठा smsdvb_debugfs *debug_data,
				     काष्ठा sms_isdbt_stats *p);

प्रकार व्योम (*sms_prt_isdb_stats_ex_t)
			(काष्ठा smsdvb_debugfs *debug_data,
			 काष्ठा sms_isdbt_stats_ex *p);


काष्ठा smsdvb_client_t अणु
	काष्ठा list_head entry;

	काष्ठा smscore_device_t *coredev;
	काष्ठा smscore_client_t *smsclient;

	काष्ठा dvb_adapter      adapter;
	काष्ठा dvb_demux        demux;
	काष्ठा dmxdev           dmxdev;
	काष्ठा dvb_frontend     frontend;

	क्रमागत fe_status          fe_status;

	काष्ठा completion       tune_करोne;
	काष्ठा completion       stats_करोne;

	पूर्णांक last_per;

	पूर्णांक legacy_ber, legacy_per;

	पूर्णांक event_fe_state;
	पूर्णांक event_unc_state;

	अचिन्हित दीर्घ		get_stats_jअगरfies;

	पूर्णांक			feed_users;
	bool			has_tuned;

	/* stats debugfs data */
	काष्ठा dentry		*debugfs;

	काष्ठा smsdvb_debugfs	*debug_data;

	sms_prt_dvb_stats_t	prt_dvb_stats;
	sms_prt_isdb_stats_t	prt_isdb_stats;
	sms_prt_isdb_stats_ex_t	prt_isdb_stats_ex;
पूर्ण;

/*
 * This काष्ठा is a mix of काष्ठा sms_rx_stats_ex and
 * काष्ठा sms_srvm_संकेत_status.
 * It was obtained by comparing the way it was filled by the original code
 */
काष्ठा RECEPTION_STATISTICS_PER_SLICES_S अणु
	u32 result;
	u32 snr;
	s32 in_band_घातer;
	u32 ts_packets;
	u32 ets_packets;
	u32 स्थिरellation;
	u32 hp_code;
	u32 tps_srv_ind_lp;
	u32 tps_srv_ind_hp;
	u32 cell_id;
	u32 reason;
	u32 request_id;
	u32 modem_state;		/* from SMSHOSTLIB_DVB_MODEM_STATE_ET */

	u32 ber;		/* Post Viterbi BER [1E-5] */
	s32 RSSI;		/* dBm */
	s32 carrier_offset;	/* Carrier Offset in bin/1024 */

	u32 is_rf_locked;		/* 0 - not locked, 1 - locked */
	u32 is_demod_locked;	/* 0 - not locked, 1 - locked */

	u32 ber_bit_count;	/* Total number of SYNC bits. */
	u32 ber_error_count;	/* Number of erroneous SYNC bits. */

	s32 MRC_SNR;		/* dB */
	s32 mrc_in_band_pwr;	/* In band घातer in dBM */
	s32 MRC_RSSI;		/* dBm */
पूर्ण;

/* From smsdvb-debugfs.c */
#अगर_घोषित CONFIG_SMS_SIANO_DEBUGFS

पूर्णांक smsdvb_debugfs_create(काष्ठा smsdvb_client_t *client);
व्योम smsdvb_debugfs_release(काष्ठा smsdvb_client_t *client);
व्योम smsdvb_debugfs_रेजिस्टर(व्योम);
व्योम smsdvb_debugfs_unरेजिस्टर(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक smsdvb_debugfs_create(काष्ठा smsdvb_client_t *client)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम smsdvb_debugfs_release(काष्ठा smsdvb_client_t *client) अणुपूर्ण

अटल अंतरभूत व्योम smsdvb_debugfs_रेजिस्टर(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम smsdvb_debugfs_unरेजिस्टर(व्योम) अणुपूर्ण;

#पूर्ण_अगर

