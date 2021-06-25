<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 */
#अगर_अघोषित __iwl_agn_h__
#घोषणा __iwl_agn_h__

#समावेश "iwl-config.h"

#समावेश "dev.h"

/* The first 11 queues (0-10) are used otherwise */
#घोषणा IWLAGN_FIRST_AMPDU_QUEUE	11

/* AUX (TX during scan dwell) queue */
#घोषणा IWL_AUX_QUEUE		10

#घोषणा IWL_INVALID_STATION	255

/* device operations */
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_1000_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_2000_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_105_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_2030_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_5000_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_5150_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6000_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6005_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6050_cfg;
बाह्य स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6030_cfg;


#घोषणा TIME_UNIT		1024

/*****************************************************
* DRIVER STATUS FUNCTIONS
******************************************************/
#घोषणा STATUS_RF_KILL_HW	0
#घोषणा STATUS_CT_KILL		1
#घोषणा STATUS_ALIVE		2
#घोषणा STATUS_READY		3
#घोषणा STATUS_EXIT_PENDING	5
#घोषणा STATUS_STATISTICS	6
#घोषणा STATUS_SCANNING		7
#घोषणा STATUS_SCAN_ABORTING	8
#घोषणा STATUS_SCAN_HW		9
#घोषणा STATUS_FW_ERROR		10
#घोषणा STATUS_CHANNEL_SWITCH_PENDING 11
#घोषणा STATUS_SCAN_COMPLETE	12
#घोषणा STATUS_POWER_PMI	13

काष्ठा iwl_ucode_capabilities;

बाह्य स्थिर काष्ठा ieee80211_ops iwlagn_hw_ops;

अटल अंतरभूत व्योम iwl_set_calib_hdr(काष्ठा iwl_calib_hdr *hdr, u8 cmd)
अणु
	hdr->op_code = cmd;
	hdr->first_group = 0;
	hdr->groups_num = 1;
	hdr->data_valid = 1;
पूर्ण

व्योम iwl_करोwn(काष्ठा iwl_priv *priv);
व्योम iwl_cancel_deferred_work(काष्ठा iwl_priv *priv);
व्योम iwlagn_prepare_restart(काष्ठा iwl_priv *priv);
व्योम iwl_rx_dispatch(काष्ठा iwl_op_mode *op_mode, काष्ठा napi_काष्ठा *napi,
		     काष्ठा iwl_rx_cmd_buffer *rxb);

bool iwl_check_क्रम_ct_समाप्त(काष्ठा iwl_priv *priv);

व्योम iwlagn_lअगरt_passive_no_rx(काष्ठा iwl_priv *priv);

/* MAC80211 */
काष्ठा ieee80211_hw *iwl_alloc_all(व्योम);
पूर्णांक iwlagn_mac_setup_रेजिस्टर(काष्ठा iwl_priv *priv,
			      स्थिर काष्ठा iwl_ucode_capabilities *capa);
व्योम iwlagn_mac_unरेजिस्टर(काष्ठा iwl_priv *priv);

/* commands */
पूर्णांक iwl_dvm_send_cmd(काष्ठा iwl_priv *priv, काष्ठा iwl_host_cmd *cmd);
पूर्णांक iwl_dvm_send_cmd_pdu(काष्ठा iwl_priv *priv, u8 id,
			 u32 flags, u16 len, स्थिर व्योम *data);

/* RXON */
व्योम iwl_connection_init_rx_config(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_rxon_context *ctx);
पूर्णांक iwlagn_set_pan_params(काष्ठा iwl_priv *priv);
पूर्णांक iwlagn_commit_rxon(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx);
व्योम iwlagn_set_rxon_chain(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx);
पूर्णांक iwlagn_mac_config(काष्ठा ieee80211_hw *hw, u32 changed);
व्योम iwlagn_bss_info_changed(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *bss_conf,
			     u32 changes);
व्योम iwlagn_config_ht40(काष्ठा ieee80211_conf *conf,
			काष्ठा iwl_rxon_context *ctx);
व्योम iwl_set_rxon_ht(काष्ठा iwl_priv *priv, काष्ठा iwl_ht_config *ht_conf);
व्योम iwl_set_rxon_channel(काष्ठा iwl_priv *priv, काष्ठा ieee80211_channel *ch,
			 काष्ठा iwl_rxon_context *ctx);
व्योम iwl_set_flags_क्रम_band(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_rxon_context *ctx,
			    क्रमागत nl80211_band band,
			    काष्ठा ieee80211_vअगर *vअगर);

/* uCode */
पूर्णांक iwl_send_bt_env(काष्ठा iwl_priv *priv, u8 action, u8 type);
व्योम iwl_send_prio_tbl(काष्ठा iwl_priv *priv);
पूर्णांक iwl_init_alive_start(काष्ठा iwl_priv *priv);
पूर्णांक iwl_run_init_ucode(काष्ठा iwl_priv *priv);
पूर्णांक iwl_load_ucode_रुको_alive(काष्ठा iwl_priv *priv,
			      क्रमागत iwl_ucode_type ucode_type);
पूर्णांक iwl_send_calib_results(काष्ठा iwl_priv *priv);
पूर्णांक iwl_calib_set(काष्ठा iwl_priv *priv,
		  स्थिर काष्ठा iwl_calib_hdr *cmd, पूर्णांक len);
व्योम iwl_calib_मुक्त_results(काष्ठा iwl_priv *priv);
पूर्णांक iwl_dump_nic_event_log(काष्ठा iwl_priv *priv, bool full_log,
			    अक्षर **buf);
पूर्णांक iwlagn_hw_valid_rtc_data_addr(u32 addr);

/* lib */
पूर्णांक iwlagn_send_tx_घातer(काष्ठा iwl_priv *priv);
व्योम iwlagn_temperature(काष्ठा iwl_priv *priv);
पूर्णांक iwlagn_txfअगरo_flush(काष्ठा iwl_priv *priv, u32 scd_q_msk);
व्योम iwlagn_dev_txfअगरo_flush(काष्ठा iwl_priv *priv);
पूर्णांक iwlagn_send_beacon_cmd(काष्ठा iwl_priv *priv);
पूर्णांक iwl_send_statistics_request(काष्ठा iwl_priv *priv,
				u8 flags, bool clear);

अटल अंतरभूत स्थिर काष्ठा ieee80211_supported_band *iwl_get_hw_mode(
			काष्ठा iwl_priv *priv, क्रमागत nl80211_band band)
अणु
	वापस priv->hw->wiphy->bands[band];
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक iwlagn_send_patterns(काष्ठा iwl_priv *priv,
			 काष्ठा cfg80211_wowlan *wowlan);
पूर्णांक iwlagn_suspend(काष्ठा iwl_priv *priv, काष्ठा cfg80211_wowlan *wowlan);
#पूर्ण_अगर

/* rx */
पूर्णांक iwlagn_hwrate_to_mac80211_idx(u32 rate_n_flags, क्रमागत nl80211_band band);
व्योम iwl_setup_rx_handlers(काष्ठा iwl_priv *priv);
व्योम iwl_chचयन_करोne(काष्ठा iwl_priv *priv, bool is_success);


/* tx */
पूर्णांक iwlagn_tx_skb(काष्ठा iwl_priv *priv,
		  काष्ठा ieee80211_sta *sta,
		  काष्ठा sk_buff *skb);
पूर्णांक iwlagn_tx_agg_start(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid, u16 *ssn);
पूर्णांक iwlagn_tx_agg_oper(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid, u8 buf_size);
पूर्णांक iwlagn_tx_agg_stop(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, u16 tid);
पूर्णांक iwlagn_tx_agg_flush(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid);
व्योम iwlagn_rx_reply_compressed_ba(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwlagn_rx_reply_tx(काष्ठा iwl_priv *priv, काष्ठा iwl_rx_cmd_buffer *rxb);

अटल अंतरभूत u32 iwl_tx_status_to_mac80211(u32 status)
अणु
	status &= TX_STATUS_MSK;

	चयन (status) अणु
	हाल TX_STATUS_SUCCESS:
	हाल TX_STATUS_सूचीECT_DONE:
		वापस IEEE80211_TX_STAT_ACK;
	हाल TX_STATUS_FAIL_DEST_PS:
	हाल TX_STATUS_FAIL_PASSIVE_NO_RX:
		वापस IEEE80211_TX_STAT_TX_FILTERED;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत bool iwl_is_tx_success(u32 status)
अणु
	status &= TX_STATUS_MSK;
	वापस (status == TX_STATUS_SUCCESS) ||
	       (status == TX_STATUS_सूचीECT_DONE);
पूर्ण

u8 iwl_toggle_tx_ant(काष्ठा iwl_priv *priv, u8 ant_idx, u8 valid);

/* scan */
व्योम iwlagn_post_scan(काष्ठा iwl_priv *priv);
पूर्णांक iwl_क्रमce_rf_reset(काष्ठा iwl_priv *priv, bool बाह्यal);
व्योम iwl_init_scan_params(काष्ठा iwl_priv *priv);
पूर्णांक iwl_scan_cancel(काष्ठा iwl_priv *priv);
व्योम iwl_scan_cancel_समयout(काष्ठा iwl_priv *priv, अचिन्हित दीर्घ ms);
व्योम iwl_क्रमce_scan_end(काष्ठा iwl_priv *priv);
व्योम iwl_पूर्णांकernal_लघु_hw_scan(काष्ठा iwl_priv *priv);
व्योम iwl_setup_rx_scan_handlers(काष्ठा iwl_priv *priv);
व्योम iwl_setup_scan_deferred_work(काष्ठा iwl_priv *priv);
व्योम iwl_cancel_scan_deferred_work(काष्ठा iwl_priv *priv);
पूर्णांक __must_check iwl_scan_initiate(काष्ठा iwl_priv *priv,
				   काष्ठा ieee80211_vअगर *vअगर,
				   क्रमागत iwl_scan_type scan_type,
				   क्रमागत nl80211_band band);

/* For faster active scanning, scan will move to the next channel अगर fewer than
 * PLCP_QUIET_THRESH packets are heard on this channel within
 * ACTIVE_QUIET_TIME after sending probe request.  This लघुens the dwell
 * समय अगर it's a quiet channel (nothing responded to our probe, and there's
 * no other traffic).
 * Disable "quiet" feature by setting PLCP_QUIET_THRESH to 0. */
#घोषणा IWL_ACTIVE_QUIET_TIME       cpu_to_le16(10)  /* msec */
#घोषणा IWL_PLCP_QUIET_THRESH       cpu_to_le16(1)  /* packets */

#घोषणा IWL_SCAN_CHECK_WATCHDOG		(HZ * 15)


/* bt coex */
व्योम iwlagn_send_advance_bt_config(काष्ठा iwl_priv *priv);
व्योम iwlagn_bt_rx_handler_setup(काष्ठा iwl_priv *priv);
व्योम iwlagn_bt_setup_deferred_work(काष्ठा iwl_priv *priv);
व्योम iwlagn_bt_cancel_deferred_work(काष्ठा iwl_priv *priv);
व्योम iwlagn_bt_coex_rssi_monitor(काष्ठा iwl_priv *priv);
व्योम iwlagn_bt_adjust_rssi_monitor(काष्ठा iwl_priv *priv, bool rssi_ena);

अटल अंतरभूत bool iwl_advanced_bt_coexist(काष्ठा iwl_priv *priv)
अणु
	वापस priv->lib->bt_params &&
	       priv->lib->bt_params->advanced_bt_coexist;
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
स्थिर अक्षर *iwl_get_tx_fail_reason(u32 status);
स्थिर अक्षर *iwl_get_agg_tx_fail_reason(u16 status);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *iwl_get_tx_fail_reason(u32 status) अणु वापस ""; पूर्ण
अटल अंतरभूत स्थिर अक्षर *iwl_get_agg_tx_fail_reason(u16 status) अणु वापस ""; पूर्ण
#पूर्ण_अगर


/* station management */
पूर्णांक iwlagn_manage_ibss_station(काष्ठा iwl_priv *priv,
			       काष्ठा ieee80211_vअगर *vअगर, bool add);
#घोषणा IWL_STA_DRIVER_ACTIVE BIT(0) /* driver entry is active */
#घोषणा IWL_STA_UCODE_ACTIVE  BIT(1) /* ucode entry is active */
#घोषणा IWL_STA_UCODE_INPROGRESS  BIT(2) /* ucode entry is in process of
					    being activated */
#घोषणा IWL_STA_LOCAL BIT(3) /* station state not directed by mac80211;
				(this is क्रम the IBSS BSSID stations) */
#घोषणा IWL_STA_BCAST BIT(4) /* this station is the special bcast station */


व्योम iwl_restore_stations(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx);
व्योम iwl_clear_ucode_stations(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx);
व्योम iwl_dealloc_bcast_stations(काष्ठा iwl_priv *priv);
पूर्णांक iwl_get_मुक्त_ucode_key_offset(काष्ठा iwl_priv *priv);
पूर्णांक iwl_send_add_sta(काष्ठा iwl_priv *priv,
		     काष्ठा iwl_addsta_cmd *sta, u8 flags);
पूर्णांक iwl_add_station_common(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			   स्थिर u8 *addr, bool is_ap,
			   काष्ठा ieee80211_sta *sta, u8 *sta_id_r);
पूर्णांक iwl_हटाओ_station(काष्ठा iwl_priv *priv, स्थिर u8 sta_id,
		       स्थिर u8 *addr);
व्योम iwl_deactivate_station(काष्ठा iwl_priv *priv, स्थिर u8 sta_id,
			    स्थिर u8 *addr);
u8 iwl_prep_station(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		    स्थिर u8 *addr, bool is_ap, काष्ठा ieee80211_sta *sta);

पूर्णांक iwl_send_lq_cmd(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		    काष्ठा iwl_link_quality_cmd *lq, u8 flags, bool init);
व्योम iwl_add_sta_callback(काष्ठा iwl_priv *priv, काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्णांक iwl_sta_update_ht(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		      काष्ठा ieee80211_sta *sta);

bool iwl_is_ht40_tx_allowed(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_rxon_context *ctx,
			    काष्ठा ieee80211_sta *sta);

अटल अंतरभूत पूर्णांक iwl_sta_id(काष्ठा ieee80211_sta *sta)
अणु
	अगर (WARN_ON(!sta))
		वापस IWL_INVALID_STATION;

	वापस ((काष्ठा iwl_station_priv *)sta->drv_priv)->sta_id;
पूर्ण

पूर्णांक iwlagn_alloc_bcast_station(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx);
पूर्णांक iwlagn_add_bssid_station(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			     स्थिर u8 *addr, u8 *sta_id_r);
पूर्णांक iwl_हटाओ_शेष_wep_key(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx,
			       काष्ठा ieee80211_key_conf *key);
पूर्णांक iwl_set_शेष_wep_key(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_rxon_context *ctx,
			    काष्ठा ieee80211_key_conf *key);
पूर्णांक iwl_restore_शेष_wep_keys(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_rxon_context *ctx);
पूर्णांक iwl_set_dynamic_key(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			काष्ठा ieee80211_key_conf *key,
			काष्ठा ieee80211_sta *sta);
पूर्णांक iwl_हटाओ_dynamic_key(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			   काष्ठा ieee80211_key_conf *key,
			   काष्ठा ieee80211_sta *sta);
व्योम iwl_update_tkip_key(काष्ठा iwl_priv *priv,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_key_conf *keyconf,
			 काष्ठा ieee80211_sta *sta, u32 iv32, u16 *phase1key);
पूर्णांक iwl_sta_tx_modअगरy_enable_tid(काष्ठा iwl_priv *priv, पूर्णांक sta_id, पूर्णांक tid);
पूर्णांक iwl_sta_rx_agg_start(काष्ठा iwl_priv *priv, काष्ठा ieee80211_sta *sta,
			 पूर्णांक tid, u16 ssn);
पूर्णांक iwl_sta_rx_agg_stop(काष्ठा iwl_priv *priv, काष्ठा ieee80211_sta *sta,
			पूर्णांक tid);
व्योम iwl_sta_modअगरy_sleep_tx_count(काष्ठा iwl_priv *priv, पूर्णांक sta_id, पूर्णांक cnt);
पूर्णांक iwl_update_bcast_station(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_rxon_context *ctx);
पूर्णांक iwl_update_bcast_stations(काष्ठा iwl_priv *priv);

/* rate */
अटल अंतरभूत u32 iwl_ant_idx_to_flags(u8 ant_idx)
अणु
	वापस BIT(ant_idx) << RATE_MCS_ANT_POS;
पूर्ण

अटल अंतरभूत u8 iwl_hw_get_rate(__le32 rate_n_flags)
अणु
	वापस le32_to_cpu(rate_n_flags) & RATE_MCS_RATE_MSK;
पूर्ण

अटल अंतरभूत __le32 iwl_hw_set_rate_n_flags(u8 rate, u32 flags)
अणु
	वापस cpu_to_le32(flags|(u32)rate);
पूर्ण

पूर्णांक iwl_alive_start(काष्ठा iwl_priv *priv);

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
व्योम iwl_prपूर्णांक_rx_config_cmd(काष्ठा iwl_priv *priv,
			     क्रमागत iwl_rxon_context_id ctxid);
#अन्यथा
अटल अंतरभूत व्योम iwl_prपूर्णांक_rx_config_cmd(काष्ठा iwl_priv *priv,
					   क्रमागत iwl_rxon_context_id ctxid)
अणु
पूर्ण
#पूर्ण_अगर

/* status checks */

अटल अंतरभूत पूर्णांक iwl_is_पढ़ोy(काष्ठा iwl_priv *priv)
अणु
	/* The adapter is 'ready' अगर READY EXIT_PENDING is not set */
	वापस test_bit(STATUS_READY, &priv->status) &&
	       !test_bit(STATUS_EXIT_PENDING, &priv->status);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_is_alive(काष्ठा iwl_priv *priv)
अणु
	वापस test_bit(STATUS_ALIVE, &priv->status);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_is_rfसमाप्त(काष्ठा iwl_priv *priv)
अणु
	वापस test_bit(STATUS_RF_KILL_HW, &priv->status);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_is_ctसमाप्त(काष्ठा iwl_priv *priv)
अणु
	वापस test_bit(STATUS_CT_KILL, &priv->status);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_is_पढ़ोy_rf(काष्ठा iwl_priv *priv)
अणु
	अगर (iwl_is_rfसमाप्त(priv))
		वापस 0;

	वापस iwl_is_पढ़ोy(priv);
पूर्ण

अटल अंतरभूत व्योम iwl_dvm_set_pmi(काष्ठा iwl_priv *priv, bool state)
अणु
	अगर (state)
		set_bit(STATUS_POWER_PMI, &priv->status);
	अन्यथा
		clear_bit(STATUS_POWER_PMI, &priv->status);
	iwl_trans_set_pmi(priv->trans, state);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_dbgfs_रेजिस्टर(काष्ठा iwl_priv *priv, काष्ठा dentry *dbgfs_dir);
#अन्यथा
अटल अंतरभूत व्योम iwl_dbgfs_रेजिस्टर(काष्ठा iwl_priv *priv,
				      काष्ठा dentry *dbgfs_dir) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
#घोषणा IWL_DEBUG_QUIET_RFKILL(m, fmt, args...)	\
करो अणु									\
	अगर (!iwl_is_rfसमाप्त((m)))					\
		IWL_ERR(m, fmt, ##args);				\
	अन्यथा								\
		__iwl_err((m)->dev, true,				\
			  !iwl_have_debug_level(IWL_DL_RADIO),		\
			  fmt, ##args);					\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा IWL_DEBUG_QUIET_RFKILL(m, fmt, args...)	\
करो अणु									\
	अगर (!iwl_is_rfसमाप्त((m)))					\
		IWL_ERR(m, fmt, ##args);				\
	अन्यथा								\
		__iwl_err((m)->dev, true, true, fmt, ##args);	\
पूर्ण जबतक (0)
#पूर्ण_अगर				/* CONFIG_IWLWIFI_DEBUG */

#पूर्ण_अगर /* __iwl_agn_h__ */
