<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/mac80211.h>

#समावेश "fw/notif-wait.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-op-mode.h"
#समावेश "fw/img.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-drv.h"
#समावेश "iwl-modparams.h"
#समावेश "mvm.h"
#समावेश "iwl-phy-db.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "rs.h"
#समावेश "fw/api/scan.h"
#समावेश "time-event.h"
#समावेश "fw-api.h"
#समावेश "fw/acpi.h"

#घोषणा DRV_DESCRIPTION	"The new Intel(R) wireless AGN driver for Linux"
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा iwl_op_mode_ops iwl_mvm_ops;
अटल स्थिर काष्ठा iwl_op_mode_ops iwl_mvm_ops_mq;

काष्ठा iwl_mvm_mod_params iwlmvm_mod_params = अणु
	.घातer_scheme = IWL_POWER_SCHEME_BPS,
	/* rest of fields are 0 by शेष */
पूर्ण;

module_param_named(init_dbg, iwlmvm_mod_params.init_dbg, bool, 0444);
MODULE_PARM_DESC(init_dbg,
		 "set to true to debug an ASSERT in INIT fw (default: false");
module_param_named(घातer_scheme, iwlmvm_mod_params.घातer_scheme, पूर्णांक, 0444);
MODULE_PARM_DESC(घातer_scheme,
		 "power management scheme: 1-active, 2-balanced, 3-low power, default: 2");

/*
 * module init and निकास functions
 */
अटल पूर्णांक __init iwl_mvm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = iwl_mvm_rate_control_रेजिस्टर();
	अगर (ret) अणु
		pr_err("Unable to register rate control algorithm: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iwl_opmode_रेजिस्टर("iwlmvm", &iwl_mvm_ops);
	अगर (ret)
		pr_err("Unable to register MVM op_mode: %d\n", ret);

	वापस ret;
पूर्ण
module_init(iwl_mvm_init);

अटल व्योम __निकास iwl_mvm_निकास(व्योम)
अणु
	iwl_opmode_deरेजिस्टर("iwlmvm");
	iwl_mvm_rate_control_unरेजिस्टर();
पूर्ण
module_निकास(iwl_mvm_निकास);

अटल व्योम iwl_mvm_nic_config(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा iwl_trans_debug *dbg = &mvm->trans->dbg;
	u8 radio_cfg_type, radio_cfg_step, radio_cfg_dash;
	u32 reg_val = 0;
	u32 phy_config = iwl_mvm_get_phy_config(mvm);

	radio_cfg_type = (phy_config & FW_PHY_CFG_RADIO_TYPE) >>
			 FW_PHY_CFG_RADIO_TYPE_POS;
	radio_cfg_step = (phy_config & FW_PHY_CFG_RADIO_STEP) >>
			 FW_PHY_CFG_RADIO_STEP_POS;
	radio_cfg_dash = (phy_config & FW_PHY_CFG_RADIO_DASH) >>
			 FW_PHY_CFG_RADIO_DASH_POS;

	/* SKU control */
	reg_val |= CSR_HW_REV_STEP(mvm->trans->hw_rev) <<
				CSR_HW_IF_CONFIG_REG_POS_MAC_STEP;
	reg_val |= CSR_HW_REV_DASH(mvm->trans->hw_rev) <<
				CSR_HW_IF_CONFIG_REG_POS_MAC_DASH;

	/* radio configuration */
	reg_val |= radio_cfg_type << CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE;
	reg_val |= radio_cfg_step << CSR_HW_IF_CONFIG_REG_POS_PHY_STEP;
	reg_val |= radio_cfg_dash << CSR_HW_IF_CONFIG_REG_POS_PHY_DASH;

	WARN_ON((radio_cfg_type << CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE) &
		 ~CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE);

	/*
	 * TODO: Bits 7-8 of CSR in 8000 HW family and higher set the ADC
	 * sampling, and shouldn't be set to any non-zero value.
	 * The same is supposed to be true of the other HW, but unsetting
	 * them (such as the 7260) causes स्वतःmatic tests to fail on seemingly
	 * unrelated errors. Need to further investigate this, but क्रम now
	 * we'll separate हालs.
	 */
	अगर (mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000)
		reg_val |= CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI;

	अगर (iwl_fw_dbg_is_d3_debug_enabled(&mvm->fwrt) ||
	    (iwl_trans_dbg_ini_valid(mvm->trans) &&
	     dbg->fw_mon_cfg[IWL_FW_INI_ALLOCATION_ID_INTERNAL].buf_location)
	    )
		reg_val |= CSR_HW_IF_CONFIG_REG_D3_DEBUG;

	iwl_trans_set_bits_mask(mvm->trans, CSR_HW_IF_CONFIG_REG,
				CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH |
				CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP |
				CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE |
				CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP |
				CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH |
				CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI |
				CSR_HW_IF_CONFIG_REG_BIT_MAC_SI   |
				CSR_HW_IF_CONFIG_REG_D3_DEBUG,
				reg_val);

	IWL_DEBUG_INFO(mvm, "Radio type=0x%x-0x%x-0x%x\n", radio_cfg_type,
		       radio_cfg_step, radio_cfg_dash);

	/*
	 * W/A : NIC is stuck in a reset state after Early PCIe घातer off
	 * (PCIe घातer is lost beक्रमe PERST# is निश्चितed), causing ME FW
	 * to lose ownership and not being able to obtain it back.
	 */
	अगर (!mvm->trans->cfg->apmg_not_supported)
		iwl_set_bits_mask_prph(mvm->trans, APMG_PS_CTRL_REG,
				       APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS,
				       ~APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS);
पूर्ण

अटल व्योम iwl_mvm_rx_monitor_notअगर(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_datapath_monitor_notअगर *notअगर = (व्योम *)pkt->data;
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	काष्ठा ieee80211_vअगर *vअगर;

	अगर (notअगर->type != cpu_to_le32(IWL_DP_MON_NOTIF_TYPE_EXT_CCA))
		वापस;

	vअगर = iwl_mvm_get_vअगर_by_macid(mvm, notअगर->mac_id);
	अगर (!vअगर || vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!vअगर->bss_conf.chandef.chan ||
	    vअगर->bss_conf.chandef.chan->band != NL80211_BAND_2GHZ ||
	    vअगर->bss_conf.chandef.width < NL80211_CHAN_WIDTH_40)
		वापस;

	अगर (!vअगर->bss_conf.assoc)
		वापस;

	/* this shouldn't happen *again*, ignore it */
	अगर (mvm->cca_40mhz_workaround)
		वापस;

	/*
	 * We'll decrement this on disconnect - so set to 2 since we'll
	 * still have to disconnect from the current AP first.
	 */
	mvm->cca_40mhz_workaround = 2;

	/*
	 * This capability manipulation isn't really ideal, but it's the
	 * easiest choice - otherwise we'd have to करो some major changes
	 * in mac80211 to support this, which isn't worth it. This करोes
	 * mean that userspace may have outdated inक्रमmation, but that's
	 * actually not an issue at all.
	 */
	sband = mvm->hw->wiphy->bands[NL80211_BAND_2GHZ];

	WARN_ON(!sband->ht_cap.ht_supported);
	WARN_ON(!(sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40));
	sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	he_cap = ieee80211_get_he_अगरtype_cap(sband,
					     ieee80211_vअगर_type_p2p(vअगर));

	अगर (he_cap) अणु
		/* we know that ours is writable */
		काष्ठा ieee80211_sta_he_cap *he = (व्योम *)he_cap;

		WARN_ON(!he->has_he);
		WARN_ON(!(he->he_cap_elem.phy_cap_info[0] &
				IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G));
		he->he_cap_elem.phy_cap_info[0] &=
			~IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G;
	पूर्ण

	ieee80211_disconnect(vअगर, true);
पूर्ण

/**
 * क्रमागत iwl_rx_handler_context context क्रम Rx handler
 * @RX_HANDLER_SYNC : this means that it will be called in the Rx path
 *	which can't acquire mvm->mutex.
 * @RX_HANDLER_ASYNC_LOCKED : If the handler needs to hold mvm->mutex
 *	(and only in this हाल!), it should be set as ASYNC. In that हाल,
 *	it will be called from a worker with mvm->mutex held.
 * @RX_HANDLER_ASYNC_UNLOCKED : in हाल the handler needs to lock the
 *	mutex itself, it will be called from a worker without mvm->mutex held.
 */
क्रमागत iwl_rx_handler_context अणु
	RX_HANDLER_SYNC,
	RX_HANDLER_ASYNC_LOCKED,
	RX_HANDLER_ASYNC_UNLOCKED,
पूर्ण;

/**
 * काष्ठा iwl_rx_handlers handler क्रम FW notअगरication
 * @cmd_id: command id
 * @context: see &iwl_rx_handler_context
 * @fn: the function is called when notअगरication is received
 */
काष्ठा iwl_rx_handlers अणु
	u16 cmd_id, min_size;
	क्रमागत iwl_rx_handler_context context;
	व्योम (*fn)(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्ण;

#घोषणा RX_HANDLER_NO_SIZE(_cmd_id, _fn, _context)		\
	अणु .cmd_id = _cmd_id, .fn = _fn, .context = _context, पूर्ण
#घोषणा RX_HANDLER_GRP_NO_SIZE(_grp, _cmd, _fn, _context)	\
	अणु .cmd_id = WIDE_ID(_grp, _cmd), .fn = _fn, .context = _context, पूर्ण
#घोषणा RX_HANDLER(_cmd_id, _fn, _context, _काष्ठा)		\
	अणु .cmd_id = _cmd_id, .fn = _fn,				\
	  .context = _context, .min_size = माप(_काष्ठा), पूर्ण
#घोषणा RX_HANDLER_GRP(_grp, _cmd, _fn, _context, _काष्ठा)	\
	अणु .cmd_id = WIDE_ID(_grp, _cmd), .fn = _fn,		\
	  .context = _context, .min_size = माप(_काष्ठा), पूर्ण

/*
 * Handlers क्रम fw notअगरications
 * Convention: RX_HANDLER(CMD_NAME, iwl_mvm_rx_CMD_NAME
 * This list should be in order of frequency क्रम perक्रमmance purposes.
 *
 * The handler can be one from three contexts, see &iwl_rx_handler_context
 */
अटल स्थिर काष्ठा iwl_rx_handlers iwl_mvm_rx_handlers[] = अणु
	RX_HANDLER(TX_CMD, iwl_mvm_rx_tx_cmd, RX_HANDLER_SYNC,
		   काष्ठा iwl_mvm_tx_resp),
	RX_HANDLER(BA_NOTIF, iwl_mvm_rx_ba_notअगर, RX_HANDLER_SYNC,
		   काष्ठा iwl_mvm_ba_notअगर),

	RX_HANDLER_GRP(DATA_PATH_GROUP, TLC_MNG_UPDATE_NOTIF,
		       iwl_mvm_tlc_update_notअगर, RX_HANDLER_SYNC,
		       काष्ठा iwl_tlc_update_notअगर),

	RX_HANDLER(BT_PROखाता_NOTIFICATION, iwl_mvm_rx_bt_coex_notअगर,
		   RX_HANDLER_ASYNC_LOCKED, काष्ठा iwl_bt_coex_profile_notअगर),
	RX_HANDLER_NO_SIZE(BEACON_NOTIFICATION, iwl_mvm_rx_beacon_notअगर,
			   RX_HANDLER_ASYNC_LOCKED),
	RX_HANDLER_NO_SIZE(STATISTICS_NOTIFICATION, iwl_mvm_rx_statistics,
			   RX_HANDLER_ASYNC_LOCKED),

	RX_HANDLER(BA_WINDOW_STATUS_NOTIFICATION_ID,
		   iwl_mvm_winकरोw_status_notअगर, RX_HANDLER_SYNC,
		   काष्ठा iwl_ba_winकरोw_status_notअगर),

	RX_HANDLER(TIME_EVENT_NOTIFICATION, iwl_mvm_rx_समय_event_notअगर,
		   RX_HANDLER_SYNC, काष्ठा iwl_समय_event_notअगर),
	RX_HANDLER_GRP(MAC_CONF_GROUP, SESSION_PROTECTION_NOTIF,
		       iwl_mvm_rx_session_protect_notअगर, RX_HANDLER_SYNC,
		       काष्ठा iwl_mvm_session_prot_notअगर),
	RX_HANDLER(MCC_CHUB_UPDATE_CMD, iwl_mvm_rx_chub_update_mcc,
		   RX_HANDLER_ASYNC_LOCKED, काष्ठा iwl_mcc_chub_notअगर),

	RX_HANDLER(EOSP_NOTIFICATION, iwl_mvm_rx_eosp_notअगर, RX_HANDLER_SYNC,
		   काष्ठा iwl_mvm_eosp_notअगरication),

	RX_HANDLER(SCAN_ITERATION_COMPLETE,
		   iwl_mvm_rx_lmac_scan_iter_complete_notअगर, RX_HANDLER_SYNC,
		   काष्ठा iwl_lmac_scan_complete_notअगर),
	RX_HANDLER(SCAN_OFFLOAD_COMPLETE,
		   iwl_mvm_rx_lmac_scan_complete_notअगर,
		   RX_HANDLER_ASYNC_LOCKED, काष्ठा iwl_periodic_scan_complete),
	RX_HANDLER_NO_SIZE(MATCH_FOUND_NOTIFICATION,
			   iwl_mvm_rx_scan_match_found,
			   RX_HANDLER_SYNC),
	RX_HANDLER(SCAN_COMPLETE_UMAC, iwl_mvm_rx_umac_scan_complete_notअगर,
		   RX_HANDLER_ASYNC_LOCKED, काष्ठा iwl_umac_scan_complete),
	RX_HANDLER(SCAN_ITERATION_COMPLETE_UMAC,
		   iwl_mvm_rx_umac_scan_iter_complete_notअगर, RX_HANDLER_SYNC,
		   काष्ठा iwl_umac_scan_iter_complete_notअगर),

	RX_HANDLER(CARD_STATE_NOTIFICATION, iwl_mvm_rx_card_state_notअगर,
		   RX_HANDLER_SYNC, काष्ठा iwl_card_state_notअगर),

	RX_HANDLER(MISSED_BEACONS_NOTIFICATION, iwl_mvm_rx_missed_beacons_notअगर,
		   RX_HANDLER_SYNC, काष्ठा iwl_missed_beacons_notअगर),

	RX_HANDLER(REPLY_ERROR, iwl_mvm_rx_fw_error, RX_HANDLER_SYNC,
		   काष्ठा iwl_error_resp),
	RX_HANDLER(PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION,
		   iwl_mvm_घातer_uapsd_misbehaving_ap_notअगर, RX_HANDLER_SYNC,
		   काष्ठा iwl_uapsd_misbehaving_ap_notअगर),
	RX_HANDLER_NO_SIZE(DTS_MEASUREMENT_NOTIFICATION, iwl_mvm_temp_notअगर,
			   RX_HANDLER_ASYNC_LOCKED),
	RX_HANDLER_GRP_NO_SIZE(PHY_OPS_GROUP, DTS_MEASUREMENT_NOTIF_WIDE,
			       iwl_mvm_temp_notअगर, RX_HANDLER_ASYNC_UNLOCKED),
	RX_HANDLER_GRP(PHY_OPS_GROUP, CT_KILL_NOTIFICATION,
		       iwl_mvm_ct_समाप्त_notअगर, RX_HANDLER_SYNC,
		       काष्ठा ct_समाप्त_notअगर),

	RX_HANDLER(TDLS_CHANNEL_SWITCH_NOTIFICATION, iwl_mvm_rx_tdls_notअगर,
		   RX_HANDLER_ASYNC_LOCKED,
		   काष्ठा iwl_tdls_channel_चयन_notअगर),
	RX_HANDLER(MFUART_LOAD_NOTIFICATION, iwl_mvm_rx_mfuart_notअगर,
		   RX_HANDLER_SYNC, काष्ठा iwl_mfuart_load_notअगर_v1),
	RX_HANDLER_GRP(LOCATION_GROUP, TOF_RESPONDER_STATS,
		       iwl_mvm_fपंचांग_responder_stats, RX_HANDLER_ASYNC_LOCKED,
		       काष्ठा iwl_fपंचांग_responder_stats),

	RX_HANDLER_GRP_NO_SIZE(LOCATION_GROUP, TOF_RANGE_RESPONSE_NOTIF,
			       iwl_mvm_fपंचांग_range_resp, RX_HANDLER_ASYNC_LOCKED),
	RX_HANDLER_GRP_NO_SIZE(LOCATION_GROUP, TOF_LC_NOTIF,
			       iwl_mvm_fपंचांग_lc_notअगर, RX_HANDLER_ASYNC_LOCKED),

	RX_HANDLER_GRP(DEBUG_GROUP, MFU_ASSERT_DUMP_NTF,
		       iwl_mvm_mfu_निश्चित_dump_notअगर, RX_HANDLER_SYNC,
		       काष्ठा iwl_mfu_निश्चित_dump_notअगर),
	RX_HANDLER_GRP(PROT_OFFLOAD_GROUP, STORED_BEACON_NTF,
		       iwl_mvm_rx_stored_beacon_notअगर, RX_HANDLER_SYNC,
		       काष्ठा iwl_stored_beacon_notअगर),
	RX_HANDLER_GRP(DATA_PATH_GROUP, MU_GROUP_MGMT_NOTIF,
		       iwl_mvm_mu_mimo_grp_notअगर, RX_HANDLER_SYNC,
		       काष्ठा iwl_mu_group_mgmt_notअगर),
	RX_HANDLER_GRP(DATA_PATH_GROUP, STA_PM_NOTIF,
		       iwl_mvm_sta_pm_notअगर, RX_HANDLER_SYNC,
		       काष्ठा iwl_mvm_pm_state_notअगरication),
	RX_HANDLER_GRP(MAC_CONF_GROUP, PROBE_RESPONSE_DATA_NOTIF,
		       iwl_mvm_probe_resp_data_notअगर,
		       RX_HANDLER_ASYNC_LOCKED,
		       काष्ठा iwl_probe_resp_data_notअगर),
	RX_HANDLER_GRP(MAC_CONF_GROUP, CHANNEL_SWITCH_NOA_NOTIF,
		       iwl_mvm_channel_चयन_noa_notअगर,
		       RX_HANDLER_SYNC, काष्ठा iwl_channel_चयन_noa_notअगर),
	RX_HANDLER_GRP(DATA_PATH_GROUP, MONITOR_NOTIF,
		       iwl_mvm_rx_monitor_notअगर, RX_HANDLER_ASYNC_LOCKED,
		       काष्ठा iwl_datapath_monitor_notअगर),
पूर्ण;
#अघोषित RX_HANDLER
#अघोषित RX_HANDLER_GRP

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_legacy_names[] = अणु
	HCMD_NAME(UCODE_ALIVE_NTFY),
	HCMD_NAME(REPLY_ERROR),
	HCMD_NAME(ECHO_CMD),
	HCMD_NAME(INIT_COMPLETE_NOTIF),
	HCMD_NAME(PHY_CONTEXT_CMD),
	HCMD_NAME(DBG_CFG),
	HCMD_NAME(SCAN_CFG_CMD),
	HCMD_NAME(SCAN_REQ_UMAC),
	HCMD_NAME(SCAN_ABORT_UMAC),
	HCMD_NAME(SCAN_COMPLETE_UMAC),
	HCMD_NAME(BA_WINDOW_STATUS_NOTIFICATION_ID),
	HCMD_NAME(ADD_STA_KEY),
	HCMD_NAME(ADD_STA),
	HCMD_NAME(REMOVE_STA),
	HCMD_NAME(FW_GET_ITEM_CMD),
	HCMD_NAME(TX_CMD),
	HCMD_NAME(SCD_QUEUE_CFG),
	HCMD_NAME(TXPATH_FLUSH),
	HCMD_NAME(MGMT_MCAST_KEY),
	HCMD_NAME(WEP_KEY),
	HCMD_NAME(SHARED_MEM_CFG),
	HCMD_NAME(TDLS_CHANNEL_SWITCH_CMD),
	HCMD_NAME(MAC_CONTEXT_CMD),
	HCMD_NAME(TIME_EVENT_CMD),
	HCMD_NAME(TIME_EVENT_NOTIFICATION),
	HCMD_NAME(BINDING_CONTEXT_CMD),
	HCMD_NAME(TIME_QUOTA_CMD),
	HCMD_NAME(NON_QOS_TX_COUNTER_CMD),
	HCMD_NAME(LEDS_CMD),
	HCMD_NAME(LQ_CMD),
	HCMD_NAME(FW_PAGING_BLOCK_CMD),
	HCMD_NAME(SCAN_OFFLOAD_REQUEST_CMD),
	HCMD_NAME(SCAN_OFFLOAD_ABORT_CMD),
	HCMD_NAME(HOT_SPOT_CMD),
	HCMD_NAME(SCAN_OFFLOAD_PROखाताS_QUERY_CMD),
	HCMD_NAME(BT_COEX_UPDATE_REDUCED_TXP),
	HCMD_NAME(BT_COEX_CI),
	HCMD_NAME(PHY_CONFIGURATION_CMD),
	HCMD_NAME(CALIB_RES_NOTIF_PHY_DB),
	HCMD_NAME(PHY_DB_CMD),
	HCMD_NAME(SCAN_OFFLOAD_COMPLETE),
	HCMD_NAME(SCAN_OFFLOAD_UPDATE_PROखाताS_CMD),
	HCMD_NAME(POWER_TABLE_CMD),
	HCMD_NAME(PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION),
	HCMD_NAME(REPLY_THERMAL_MNG_BACKOFF),
	HCMD_NAME(DC2DC_CONFIG_CMD),
	HCMD_NAME(NVM_ACCESS_CMD),
	HCMD_NAME(BEACON_NOTIFICATION),
	HCMD_NAME(BEACON_TEMPLATE_CMD),
	HCMD_NAME(TX_ANT_CONFIGURATION_CMD),
	HCMD_NAME(BT_CONFIG),
	HCMD_NAME(STATISTICS_CMD),
	HCMD_NAME(STATISTICS_NOTIFICATION),
	HCMD_NAME(EOSP_NOTIFICATION),
	HCMD_NAME(REDUCE_TX_POWER_CMD),
	HCMD_NAME(CARD_STATE_NOTIFICATION),
	HCMD_NAME(MISSED_BEACONS_NOTIFICATION),
	HCMD_NAME(TDLS_CONFIG_CMD),
	HCMD_NAME(MAC_PM_POWER_TABLE),
	HCMD_NAME(TDLS_CHANNEL_SWITCH_NOTIFICATION),
	HCMD_NAME(MFUART_LOAD_NOTIFICATION),
	HCMD_NAME(RSS_CONFIG_CMD),
	HCMD_NAME(SCAN_ITERATION_COMPLETE_UMAC),
	HCMD_NAME(REPLY_RX_PHY_CMD),
	HCMD_NAME(REPLY_RX_MPDU_CMD),
	HCMD_NAME(BAR_FRAME_RELEASE),
	HCMD_NAME(FRAME_RELEASE),
	HCMD_NAME(BA_NOTIF),
	HCMD_NAME(MCC_UPDATE_CMD),
	HCMD_NAME(MCC_CHUB_UPDATE_CMD),
	HCMD_NAME(MARKER_CMD),
	HCMD_NAME(BT_PROखाता_NOTIFICATION),
	HCMD_NAME(BCAST_FILTER_CMD),
	HCMD_NAME(MCAST_FILTER_CMD),
	HCMD_NAME(REPLY_SF_CFG_CMD),
	HCMD_NAME(REPLY_BEACON_FILTERING_CMD),
	HCMD_NAME(D3_CONFIG_CMD),
	HCMD_NAME(PROT_OFFLOAD_CONFIG_CMD),
	HCMD_NAME(OFFLOADS_QUERY_CMD),
	HCMD_NAME(REMOTE_WAKE_CONFIG_CMD),
	HCMD_NAME(MATCH_FOUND_NOTIFICATION),
	HCMD_NAME(DTS_MEASUREMENT_NOTIFICATION),
	HCMD_NAME(WOWLAN_PATTERNS),
	HCMD_NAME(WOWLAN_CONFIGURATION),
	HCMD_NAME(WOWLAN_TSC_RSC_PARAM),
	HCMD_NAME(WOWLAN_TKIP_PARAM),
	HCMD_NAME(WOWLAN_KEK_KCK_MATERIAL),
	HCMD_NAME(WOWLAN_GET_STATUSES),
	HCMD_NAME(SCAN_ITERATION_COMPLETE),
	HCMD_NAME(D0I3_END_CMD),
	HCMD_NAME(LTR_CONFIG),
	HCMD_NAME(LDBG_CONFIG_CMD),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_प्रणाली_names[] = अणु
	HCMD_NAME(SHARED_MEM_CFG_CMD),
	HCMD_NAME(INIT_EXTENDED_CFG_CMD),
	HCMD_NAME(FW_ERROR_RECOVERY_CMD),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_mac_conf_names[] = अणु
	HCMD_NAME(CHANNEL_SWITCH_TIME_EVENT_CMD),
	HCMD_NAME(SESSION_PROTECTION_CMD),
	HCMD_NAME(SESSION_PROTECTION_NOTIF),
	HCMD_NAME(CHANNEL_SWITCH_NOA_NOTIF),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_phy_names[] = अणु
	HCMD_NAME(CMD_DTS_MEASUREMENT_TRIGGER_WIDE),
	HCMD_NAME(CTDP_CONFIG_CMD),
	HCMD_NAME(TEMP_REPORTING_THRESHOLDS_CMD),
	HCMD_NAME(GEO_TX_POWER_LIMIT),
	HCMD_NAME(CT_KILL_NOTIFICATION),
	HCMD_NAME(DTS_MEASUREMENT_NOTIF_WIDE),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_data_path_names[] = अणु
	HCMD_NAME(DQA_ENABLE_CMD),
	HCMD_NAME(UPDATE_MU_GROUPS_CMD),
	HCMD_NAME(TRIGGER_RX_QUEUES_NOTIF_CMD),
	HCMD_NAME(STA_HE_CTXT_CMD),
	HCMD_NAME(RFH_QUEUE_CONFIG_CMD),
	HCMD_NAME(TLC_MNG_CONFIG_CMD),
	HCMD_NAME(CHEST_COLLECTOR_FILTER_CONFIG_CMD),
	HCMD_NAME(MONITOR_NOTIF),
	HCMD_NAME(STA_PM_NOTIF),
	HCMD_NAME(MU_GROUP_MGMT_NOTIF),
	HCMD_NAME(RX_QUEUES_NOTIFICATION),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_location_names[] = अणु
	HCMD_NAME(TOF_RANGE_REQ_CMD),
	HCMD_NAME(TOF_CONFIG_CMD),
	HCMD_NAME(TOF_RANGE_ABORT_CMD),
	HCMD_NAME(TOF_RANGE_REQ_EXT_CMD),
	HCMD_NAME(TOF_RESPONDER_CONFIG_CMD),
	HCMD_NAME(TOF_RESPONDER_DYN_CONFIG_CMD),
	HCMD_NAME(TOF_LC_NOTIF),
	HCMD_NAME(TOF_RESPONDER_STATS),
	HCMD_NAME(TOF_MCSI_DEBUG_NOTIF),
	HCMD_NAME(TOF_RANGE_RESPONSE_NOTIF),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_prot_offload_names[] = अणु
	HCMD_NAME(STORED_BEACON_NTF),
पूर्ण;

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_mvm_regulatory_and_nvm_names[] = अणु
	HCMD_NAME(NVM_ACCESS_COMPLETE),
	HCMD_NAME(NVM_GET_INFO),
	HCMD_NAME(TAS_CONFIG),
पूर्ण;

अटल स्थिर काष्ठा iwl_hcmd_arr iwl_mvm_groups[] = अणु
	[LEGACY_GROUP] = HCMD_ARR(iwl_mvm_legacy_names),
	[LONG_GROUP] = HCMD_ARR(iwl_mvm_legacy_names),
	[SYSTEM_GROUP] = HCMD_ARR(iwl_mvm_प्रणाली_names),
	[MAC_CONF_GROUP] = HCMD_ARR(iwl_mvm_mac_conf_names),
	[PHY_OPS_GROUP] = HCMD_ARR(iwl_mvm_phy_names),
	[DATA_PATH_GROUP] = HCMD_ARR(iwl_mvm_data_path_names),
	[LOCATION_GROUP] = HCMD_ARR(iwl_mvm_location_names),
	[PROT_OFFLOAD_GROUP] = HCMD_ARR(iwl_mvm_prot_offload_names),
	[REGULATORY_AND_NVM_GROUP] =
		HCMD_ARR(iwl_mvm_regulatory_and_nvm_names),
पूर्ण;

/* this क्रमward declaration can aव्योम to export the function */
अटल व्योम iwl_mvm_async_handlers_wk(काष्ठा work_काष्ठा *wk);

अटल u32 iwl_mvm_min_backoff(काष्ठा iwl_mvm *mvm)
अणु
	स्थिर काष्ठा iwl_pwr_tx_backoff *backoff = mvm->cfg->pwr_tx_backoffs;
	u64 dflt_pwr_limit;

	अगर (!backoff)
		वापस 0;

	dflt_pwr_limit = iwl_acpi_get_pwr_limit(mvm->dev);

	जबतक (backoff->pwr) अणु
		अगर (dflt_pwr_limit >= backoff->pwr)
			वापस backoff->backoff;

		backoff++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_tx_unblock_dwork(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(work, काष्ठा iwl_mvm, cs_tx_unblock_dwork.work);
	काष्ठा ieee80211_vअगर *tx_blocked_vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;

	mutex_lock(&mvm->mutex);

	tx_blocked_vअगर =
		rcu_dereference_रक्षित(mvm->csa_tx_blocked_vअगर,
					  lockdep_is_held(&mvm->mutex));

	अगर (!tx_blocked_vअगर)
		जाओ unlock;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(tx_blocked_vअगर);
	iwl_mvm_modअगरy_all_sta_disable_tx(mvm, mvmvअगर, false);
	RCU_INIT_POINTER(mvm->csa_tx_blocked_vअगर, शून्य);
unlock:
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक iwl_mvm_fwrt_dump_start(व्योम *ctx)
अणु
	काष्ठा iwl_mvm *mvm = ctx;

	mutex_lock(&mvm->mutex);

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_fwrt_dump_end(व्योम *ctx)
अणु
	काष्ठा iwl_mvm *mvm = ctx;

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल bool iwl_mvm_fwrt_fw_running(व्योम *ctx)
अणु
	वापस iwl_mvm_firmware_running(ctx);
पूर्ण

अटल पूर्णांक iwl_mvm_fwrt_send_hcmd(व्योम *ctx, काष्ठा iwl_host_cmd *host_cmd)
अणु
	काष्ठा iwl_mvm *mvm = (काष्ठा iwl_mvm *)ctx;
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd(mvm, host_cmd);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल bool iwl_mvm_d3_debug_enable(व्योम *ctx)
अणु
	वापस IWL_MVM_D3_DEBUG;
पूर्ण

अटल स्थिर काष्ठा iwl_fw_runसमय_ops iwl_mvm_fwrt_ops = अणु
	.dump_start = iwl_mvm_fwrt_dump_start,
	.dump_end = iwl_mvm_fwrt_dump_end,
	.fw_running = iwl_mvm_fwrt_fw_running,
	.send_hcmd = iwl_mvm_fwrt_send_hcmd,
	.d3_debug_enable = iwl_mvm_d3_debug_enable,
पूर्ण;

अटल पूर्णांक iwl_mvm_start_get_nvm(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	ret = iwl_run_init_mvm_ucode(mvm);

	अगर (ret && ret != -ERFKILL)
		iwl_fw_dbg_error_collect(&mvm->fwrt, FW_DBG_TRIGGER_DRIVER);

	अगर (!iwlmvm_mod_params.init_dbg || !ret)
		iwl_mvm_stop_device(mvm);

	mutex_unlock(&mvm->mutex);

	अगर (ret < 0)
		IWL_ERR(mvm, "Failed to run INIT ucode: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_start_post_nvm(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	iwl_mvm_toggle_tx_ant(mvm, &mvm->mgmt_last_antenna_idx);

	ret = iwl_mvm_mac_setup_रेजिस्टर(mvm);
	अगर (ret)
		वापस ret;
	mvm->hw_रेजिस्टरed = true;

	iwl_mvm_dbgfs_रेजिस्टर(mvm);

	वापस 0;
पूर्ण

अटल काष्ठा iwl_op_mode *
iwl_op_mode_mvm_start(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
		      स्थिर काष्ठा iwl_fw *fw, काष्ठा dentry *dbgfs_dir)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा iwl_op_mode *op_mode;
	काष्ठा iwl_mvm *mvm;
	काष्ठा iwl_trans_config trans_cfg = अणुपूर्ण;
	अटल स्थिर u8 no_reclaim_cmds[] = अणु
		TX_CMD,
	पूर्ण;
	पूर्णांक err, scan_size;
	u32 min_backoff;
	क्रमागत iwl_amsdu_size rb_size_शेष;

	/*
	 * We use IWL_MVM_STATION_COUNT_MAX to check the validity of the station
	 * index all over the driver - check that its value corresponds to the
	 * array size.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(mvm->fw_id_to_mac_id) !=
		     IWL_MVM_STATION_COUNT_MAX);

	/********************************
	 * 1. Allocating and configuring HW data
	 ********************************/
	hw = ieee80211_alloc_hw(माप(काष्ठा iwl_op_mode) +
				माप(काष्ठा iwl_mvm),
				&iwl_mvm_hw_ops);
	अगर (!hw)
		वापस शून्य;

	hw->max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;

	अगर (cfg->max_tx_agg_size)
		hw->max_tx_aggregation_subframes = cfg->max_tx_agg_size;
	अन्यथा
		hw->max_tx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;

	op_mode = hw->priv;

	mvm = IWL_OP_MODE_GET_MVM(op_mode);
	mvm->dev = trans->dev;
	mvm->trans = trans;
	mvm->cfg = cfg;
	mvm->fw = fw;
	mvm->hw = hw;

	iwl_fw_runसमय_init(&mvm->fwrt, trans, fw, &iwl_mvm_fwrt_ops, mvm,
			    dbgfs_dir);

	mvm->init_status = 0;

	अगर (iwl_mvm_has_new_rx_api(mvm)) अणु
		op_mode->ops = &iwl_mvm_ops_mq;
		trans->rx_mpdu_cmd_hdr_size =
			(trans->trans_cfg->device_family >=
			 IWL_DEVICE_FAMILY_AX210) ?
			माप(काष्ठा iwl_rx_mpdu_desc) :
			IWL_RX_DESC_SIZE_V1;
	पूर्ण अन्यथा अणु
		op_mode->ops = &iwl_mvm_ops;
		trans->rx_mpdu_cmd_hdr_size =
			माप(काष्ठा iwl_rx_mpdu_res_start);

		अगर (WARN_ON(trans->num_rx_queues > 1))
			जाओ out_मुक्त;
	पूर्ण

	mvm->fw_restart = iwlwअगरi_mod_params.fw_restart ? -1 : 0;

	mvm->aux_queue = IWL_MVM_DQA_AUX_QUEUE;
	mvm->snअगर_queue = IWL_MVM_DQA_INJECT_MONITOR_QUEUE;
	mvm->probe_queue = IWL_MVM_DQA_AP_PROBE_RESP_QUEUE;
	mvm->p2p_dev_queue = IWL_MVM_DQA_P2P_DEVICE_QUEUE;

	mvm->sf_state = SF_UNINIT;
	अगर (iwl_mvm_has_unअगरied_ucode(mvm))
		iwl_fw_set_current_image(&mvm->fwrt, IWL_UCODE_REGULAR);
	अन्यथा
		iwl_fw_set_current_image(&mvm->fwrt, IWL_UCODE_INIT);
	mvm->drop_bcn_ap_mode = true;

	mutex_init(&mvm->mutex);
	spin_lock_init(&mvm->async_handlers_lock);
	INIT_LIST_HEAD(&mvm->समय_event_list);
	INIT_LIST_HEAD(&mvm->aux_roc_te_list);
	INIT_LIST_HEAD(&mvm->async_handlers_list);
	spin_lock_init(&mvm->समय_event_lock);
	INIT_LIST_HEAD(&mvm->fपंचांग_initiator.loc_list);
	INIT_LIST_HEAD(&mvm->fपंचांग_initiator.pasn_list);
	INIT_LIST_HEAD(&mvm->resp_pasn_list);

	INIT_WORK(&mvm->async_handlers_wk, iwl_mvm_async_handlers_wk);
	INIT_WORK(&mvm->roc_करोne_wk, iwl_mvm_roc_करोne_wk);
	INIT_DELAYED_WORK(&mvm->tdls_cs.dwork, iwl_mvm_tdls_ch_चयन_work);
	INIT_DELAYED_WORK(&mvm->scan_समयout_dwork, iwl_mvm_scan_समयout_wk);
	INIT_WORK(&mvm->add_stream_wk, iwl_mvm_add_new_dqa_stream_wk);
	INIT_LIST_HEAD(&mvm->add_stream_txqs);

	init_रुकोqueue_head(&mvm->rx_sync_रुकोq);

	mvm->queue_sync_state = 0;

	SET_IEEE80211_DEV(mvm->hw, mvm->trans->dev);

	spin_lock_init(&mvm->tcm.lock);
	INIT_DELAYED_WORK(&mvm->tcm.work, iwl_mvm_tcm_work);
	mvm->tcm.ts = jअगरfies;
	mvm->tcm.ll_ts = jअगरfies;
	mvm->tcm.uapsd_nonagg_ts = jअगरfies;

	INIT_DELAYED_WORK(&mvm->cs_tx_unblock_dwork, iwl_mvm_tx_unblock_dwork);

	mvm->cmd_ver.d0i3_resp =
		iwl_fw_lookup_notअगर_ver(mvm->fw, LEGACY_GROUP, D0I3_END_CMD,
					0);
	/* we only support version 1 */
	अगर (WARN_ON_ONCE(mvm->cmd_ver.d0i3_resp > 1))
		जाओ out_मुक्त;

	mvm->cmd_ver.range_resp =
		iwl_fw_lookup_notअगर_ver(mvm->fw, LOCATION_GROUP,
					TOF_RANGE_RESPONSE_NOTIF, 5);
	/* we only support up to version 8 */
	अगर (WARN_ON_ONCE(mvm->cmd_ver.range_resp > 8))
		जाओ out_मुक्त;

	/*
	 * Populate the state variables that the transport layer needs
	 * to know about.
	 */
	trans_cfg.op_mode = op_mode;
	trans_cfg.no_reclaim_cmds = no_reclaim_cmds;
	trans_cfg.n_no_reclaim_cmds = ARRAY_SIZE(no_reclaim_cmds);

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		rb_size_शेष = IWL_AMSDU_2K;
	अन्यथा
		rb_size_शेष = IWL_AMSDU_4K;

	चयन (iwlwअगरi_mod_params.amsdu_size) अणु
	हाल IWL_AMSDU_DEF:
		trans_cfg.rx_buf_size = rb_size_शेष;
		अवरोध;
	हाल IWL_AMSDU_4K:
		trans_cfg.rx_buf_size = IWL_AMSDU_4K;
		अवरोध;
	हाल IWL_AMSDU_8K:
		trans_cfg.rx_buf_size = IWL_AMSDU_8K;
		अवरोध;
	हाल IWL_AMSDU_12K:
		trans_cfg.rx_buf_size = IWL_AMSDU_12K;
		अवरोध;
	शेष:
		pr_err("%s: Unsupported amsdu_size: %d\n", KBUILD_MODNAME,
		       iwlwअगरi_mod_params.amsdu_size);
		trans_cfg.rx_buf_size = rb_size_शेष;
	पूर्ण

	trans->wide_cmd_header = true;
	trans_cfg.bc_table_dword =
		mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210;

	trans_cfg.command_groups = iwl_mvm_groups;
	trans_cfg.command_groups_size = ARRAY_SIZE(iwl_mvm_groups);

	trans_cfg.cmd_queue = IWL_MVM_DQA_CMD_QUEUE;
	trans_cfg.cmd_fअगरo = IWL_MVM_TX_FIFO_CMD;
	trans_cfg.scd_set_active = true;

	trans_cfg.cb_data_offs = दुरत्व(काष्ठा ieee80211_tx_info,
					  driver_data[2]);

	/* Set a लघु watchकरोg क्रम the command queue */
	trans_cfg.cmd_q_wdg_समयout =
		iwl_mvm_get_wd_समयout(mvm, शून्य, false, true);

	snम_लिखो(mvm->hw->wiphy->fw_version,
		 माप(mvm->hw->wiphy->fw_version),
		 "%s", fw->fw_version);

	trans_cfg.fw_reset_handshake = fw_has_capa(&mvm->fw->ucode_capa,
						   IWL_UCODE_TLV_CAPA_FW_RESET_HANDSHAKE);

	/* Configure transport layer */
	iwl_trans_configure(mvm->trans, &trans_cfg);

	trans->rx_mpdu_cmd = REPLY_RX_MPDU_CMD;
	trans->dbg.dest_tlv = mvm->fw->dbg.dest_tlv;
	trans->dbg.n_dest_reg = mvm->fw->dbg.n_dest_reg;
	स_नकल(trans->dbg.conf_tlv, mvm->fw->dbg.conf_tlv,
	       माप(trans->dbg.conf_tlv));
	trans->dbg.trigger_tlv = mvm->fw->dbg.trigger_tlv;

	trans->iml = mvm->fw->iml;
	trans->iml_len = mvm->fw->iml_len;

	/* set up notअगरication रुको support */
	iwl_notअगरication_रुको_init(&mvm->notअगर_रुको);

	/* Init phy db */
	mvm->phy_db = iwl_phy_db_init(trans);
	अगर (!mvm->phy_db) अणु
		IWL_ERR(mvm, "Cannot init phy_db\n");
		जाओ out_मुक्त;
	पूर्ण

	IWL_INFO(mvm, "Detected %s, REV=0x%X\n",
		 mvm->trans->name, mvm->trans->hw_rev);

	अगर (iwlwअगरi_mod_params.nvm_file)
		mvm->nvm_file_name = iwlwअगरi_mod_params.nvm_file;
	अन्यथा
		IWL_DEBUG_EEPROM(mvm->trans->dev,
				 "working without external nvm file\n");

	err = iwl_trans_start_hw(mvm->trans);
	अगर (err)
		जाओ out_मुक्त;

	scan_size = iwl_mvm_scan_size(mvm);

	mvm->scan_cmd = kदो_स्मृति(scan_size, GFP_KERNEL);
	अगर (!mvm->scan_cmd)
		जाओ out_मुक्त;

	/* invalidate ids to prevent accidental removal of sta_id 0 */
	mvm->aux_sta.sta_id = IWL_MVM_INVALID_STA;
	mvm->snअगर_sta.sta_id = IWL_MVM_INVALID_STA;

	/* Set EBS as successful as दीर्घ as not stated otherwise by the FW. */
	mvm->last_ebs_successful = true;

	min_backoff = iwl_mvm_min_backoff(mvm);
	iwl_mvm_thermal_initialize(mvm, min_backoff);

	अगर (!iwl_mvm_has_new_rx_stats_api(mvm))
		स_रखो(&mvm->rx_stats_v3, 0,
		       माप(काष्ठा mvm_statistics_rx_v3));
	अन्यथा
		स_रखो(&mvm->rx_stats, 0, माप(काष्ठा mvm_statistics_rx));

	mvm->debugfs_dir = dbgfs_dir;

	अगर (iwl_mvm_start_get_nvm(mvm))
		जाओ out_thermal_निकास;

	अगर (iwl_mvm_start_post_nvm(mvm))
		जाओ out_thermal_निकास;

	वापस op_mode;

 out_thermal_निकास:
	iwl_mvm_thermal_निकास(mvm);
 out_मुक्त:
	iwl_fw_flush_dumps(&mvm->fwrt);
	iwl_fw_runसमय_मुक्त(&mvm->fwrt);

	अगर (iwlmvm_mod_params.init_dbg)
		वापस op_mode;
	iwl_phy_db_मुक्त(mvm->phy_db);
	kमुक्त(mvm->scan_cmd);
	iwl_trans_op_mode_leave(trans);

	ieee80211_मुक्त_hw(mvm->hw);
	वापस शून्य;
पूर्ण

व्योम iwl_mvm_stop_device(काष्ठा iwl_mvm *mvm)
अणु
	lockdep_निश्चित_held(&mvm->mutex);

	iwl_fw_cancel_बारtamp(&mvm->fwrt);

	clear_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);

	iwl_fw_dbg_stop_sync(&mvm->fwrt);
	iwl_trans_stop_device(mvm->trans);
	iwl_मुक्त_fw_paging(&mvm->fwrt);
	iwl_fw_dump_conf_clear(&mvm->fwrt);
पूर्ण

अटल व्योम iwl_op_mode_mvm_stop(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	पूर्णांक i;

	iwl_mvm_leds_निकास(mvm);

	iwl_mvm_thermal_निकास(mvm);

	ieee80211_unरेजिस्टर_hw(mvm->hw);

	kमुक्त(mvm->scan_cmd);
	kमुक्त(mvm->mcast_filter_cmd);
	mvm->mcast_filter_cmd = शून्य;

	kमुक्त(mvm->error_recovery_buf);
	mvm->error_recovery_buf = शून्य;

	iwl_trans_op_mode_leave(mvm->trans);

	iwl_phy_db_मुक्त(mvm->phy_db);
	mvm->phy_db = शून्य;

	kमुक्त(mvm->nvm_data);
	क्रम (i = 0; i < NVM_MAX_NUM_SECTIONS; i++)
		kमुक्त(mvm->nvm_sections[i].data);

	cancel_delayed_work_sync(&mvm->tcm.work);

	iwl_fw_runसमय_मुक्त(&mvm->fwrt);
	mutex_destroy(&mvm->mutex);

	ieee80211_मुक्त_hw(mvm->hw);
पूर्ण

काष्ठा iwl_async_handler_entry अणु
	काष्ठा list_head list;
	काष्ठा iwl_rx_cmd_buffer rxb;
	क्रमागत iwl_rx_handler_context context;
	व्योम (*fn)(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्ण;

व्योम iwl_mvm_async_handlers_purge(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_async_handler_entry *entry, *पंचांगp;

	spin_lock_bh(&mvm->async_handlers_lock);
	list_क्रम_each_entry_safe(entry, पंचांगp, &mvm->async_handlers_list, list) अणु
		iwl_मुक्त_rxb(&entry->rxb);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	spin_unlock_bh(&mvm->async_handlers_lock);
पूर्ण

अटल व्योम iwl_mvm_async_handlers_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(wk, काष्ठा iwl_mvm, async_handlers_wk);
	काष्ठा iwl_async_handler_entry *entry, *पंचांगp;
	LIST_HEAD(local_list);

	/* Ensure that we are not in stop flow (check iwl_mvm_mac_stop) */

	/*
	 * Sync with Rx path with a lock. Remove all the entries from this list,
	 * add them to a local one (lock मुक्त), and then handle them.
	 */
	spin_lock_bh(&mvm->async_handlers_lock);
	list_splice_init(&mvm->async_handlers_list, &local_list);
	spin_unlock_bh(&mvm->async_handlers_lock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &local_list, list) अणु
		अगर (entry->context == RX_HANDLER_ASYNC_LOCKED)
			mutex_lock(&mvm->mutex);
		entry->fn(mvm, &entry->rxb);
		iwl_मुक्त_rxb(&entry->rxb);
		list_del(&entry->list);
		अगर (entry->context == RX_HANDLER_ASYNC_LOCKED)
			mutex_unlock(&mvm->mutex);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iwl_mvm_rx_check_trigger(काष्ठा iwl_mvm *mvm,
					    काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_cmd *cmds_trig;
	पूर्णांक i;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, शून्य,
				     FW_DBG_TRIGGER_FW_NOTIF);
	अगर (!trig)
		वापस;

	cmds_trig = (व्योम *)trig->data;

	क्रम (i = 0; i < ARRAY_SIZE(cmds_trig->cmds); i++) अणु
		/* करोn't collect on CMD 0 */
		अगर (!cmds_trig->cmds[i].cmd_id)
			अवरोध;

		अगर (cmds_trig->cmds[i].cmd_id != pkt->hdr.cmd ||
		    cmds_trig->cmds[i].group_id != pkt->hdr.group_id)
			जारी;

		iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
					"CMD 0x%02x.%02x received",
					pkt->hdr.group_id, pkt->hdr.cmd);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_rx_common(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_rx_cmd_buffer *rxb,
			      काष्ठा iwl_rx_packet *pkt)
अणु
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	पूर्णांक i;
	जोड़ iwl_dbg_tlv_tp_data tp_data = अणु .fw_pkt = pkt पूर्ण;

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
			       IWL_FW_INI_TIME_POINT_FW_RSP_OR_NOTIF, &tp_data);
	iwl_mvm_rx_check_trigger(mvm, pkt);

	/*
	 * Do the notअगरication रुको beक्रमe RX handlers so
	 * even अगर the RX handler consumes the RXB we have
	 * access to it in the notअगरication रुको entry.
	 */
	iwl_notअगरication_रुको_notअगरy(&mvm->notअगर_रुको, pkt);

	क्रम (i = 0; i < ARRAY_SIZE(iwl_mvm_rx_handlers); i++) अणु
		स्थिर काष्ठा iwl_rx_handlers *rx_h = &iwl_mvm_rx_handlers[i];
		काष्ठा iwl_async_handler_entry *entry;

		अगर (rx_h->cmd_id != WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd))
			जारी;

		अगर (unlikely(pkt_len < rx_h->min_size))
			वापस;

		अगर (rx_h->context == RX_HANDLER_SYNC) अणु
			rx_h->fn(mvm, rxb);
			वापस;
		पूर्ण

		entry = kzalloc(माप(*entry), GFP_ATOMIC);
		/* we can't करो much... */
		अगर (!entry)
			वापस;

		entry->rxb._page = rxb_steal_page(rxb);
		entry->rxb._offset = rxb->_offset;
		entry->rxb._rx_page_order = rxb->_rx_page_order;
		entry->fn = rx_h->fn;
		entry->context = rx_h->context;
		spin_lock(&mvm->async_handlers_lock);
		list_add_tail(&entry->list, &mvm->async_handlers_list);
		spin_unlock(&mvm->async_handlers_lock);
		schedule_work(&mvm->async_handlers_wk);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_rx(काष्ठा iwl_op_mode *op_mode,
		       काष्ठा napi_काष्ठा *napi,
		       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	u16 cmd = WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd);

	अगर (likely(cmd == WIDE_ID(LEGACY_GROUP, REPLY_RX_MPDU_CMD)))
		iwl_mvm_rx_rx_mpdu(mvm, napi, rxb);
	अन्यथा अगर (cmd == WIDE_ID(LEGACY_GROUP, REPLY_RX_PHY_CMD))
		iwl_mvm_rx_rx_phy_cmd(mvm, rxb);
	अन्यथा
		iwl_mvm_rx_common(mvm, rxb, pkt);
पूर्ण

व्योम iwl_mvm_rx_mq(काष्ठा iwl_op_mode *op_mode,
		   काष्ठा napi_काष्ठा *napi,
		   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	u16 cmd = WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd);

	अगर (likely(cmd == WIDE_ID(LEGACY_GROUP, REPLY_RX_MPDU_CMD)))
		iwl_mvm_rx_mpdu_mq(mvm, napi, rxb, 0);
	अन्यथा अगर (unlikely(cmd == WIDE_ID(DATA_PATH_GROUP,
					 RX_QUEUES_NOTIFICATION)))
		iwl_mvm_rx_queue_notअगर(mvm, napi, rxb, 0);
	अन्यथा अगर (cmd == WIDE_ID(LEGACY_GROUP, FRAME_RELEASE))
		iwl_mvm_rx_frame_release(mvm, napi, rxb, 0);
	अन्यथा अगर (cmd == WIDE_ID(LEGACY_GROUP, BAR_FRAME_RELEASE))
		iwl_mvm_rx_bar_frame_release(mvm, napi, rxb, 0);
	अन्यथा अगर (cmd == WIDE_ID(DATA_PATH_GROUP, RX_NO_DATA_NOTIF))
		iwl_mvm_rx_monitor_no_data(mvm, napi, rxb, 0);
	अन्यथा
		iwl_mvm_rx_common(mvm, rxb, pkt);
पूर्ण

अटल व्योम iwl_mvm_async_cb(काष्ठा iwl_op_mode *op_mode,
			     स्थिर काष्ठा iwl_device_cmd *cmd)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);

	/*
	 * For now, we only set the CMD_WANT_ASYNC_CALLBACK क्रम ADD_STA
	 * commands that need to block the Tx queues.
	 */
	iwl_trans_block_txq_ptrs(mvm->trans, false);
पूर्ण

अटल पूर्णांक iwl_mvm_is_अटल_queue(काष्ठा iwl_mvm *mvm, पूर्णांक queue)
अणु
	वापस queue == mvm->aux_queue || queue == mvm->probe_queue ||
		queue == mvm->p2p_dev_queue || queue == mvm->snअगर_queue;
पूर्ण

अटल व्योम iwl_mvm_queue_state_change(काष्ठा iwl_op_mode *op_mode,
				       पूर्णांक hw_queue, bool start)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_txq *txq;
	काष्ठा iwl_mvm_txq *mvmtxq;
	पूर्णांक i;
	अचिन्हित दीर्घ tid_biपंचांगap;
	काष्ठा iwl_mvm_sta *mvmsta;
	u8 sta_id;

	sta_id = iwl_mvm_has_new_tx_api(mvm) ?
		mvm->tvqm_info[hw_queue].sta_id :
		mvm->queue_info[hw_queue].ra_sta_id;

	अगर (WARN_ON_ONCE(sta_id >= mvm->fw->ucode_capa.num_stations))
		वापस;

	rcu_पढ़ो_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
	अगर (IS_ERR_OR_शून्य(sta))
		जाओ out;
	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अगर (iwl_mvm_is_अटल_queue(mvm, hw_queue)) अणु
		अगर (!start)
			ieee80211_stop_queues(mvm->hw);
		अन्यथा अगर (mvmsta->sta_state != IEEE80211_STA_NOTEXIST)
			ieee80211_wake_queues(mvm->hw);

		जाओ out;
	पूर्ण

	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		पूर्णांक tid = mvm->tvqm_info[hw_queue].txq_tid;

		tid_biपंचांगap = BIT(tid);
	पूर्ण अन्यथा अणु
		tid_biपंचांगap = mvm->queue_info[hw_queue].tid_biपंचांगap;
	पूर्ण

	क्रम_each_set_bit(i, &tid_biपंचांगap, IWL_MAX_TID_COUNT + 1) अणु
		पूर्णांक tid = i;

		अगर (tid == IWL_MAX_TID_COUNT)
			tid = IEEE80211_NUM_TIDS;

		txq = sta->txq[tid];
		mvmtxq = iwl_mvm_txq_from_mac80211(txq);
		mvmtxq->stopped = !start;

		अगर (start && mvmsta->sta_state != IEEE80211_STA_NOTEXIST)
			iwl_mvm_mac_itxq_xmit(mvm->hw, txq);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_stop_sw_queue(काष्ठा iwl_op_mode *op_mode, पूर्णांक hw_queue)
अणु
	iwl_mvm_queue_state_change(op_mode, hw_queue, false);
पूर्ण

अटल व्योम iwl_mvm_wake_sw_queue(काष्ठा iwl_op_mode *op_mode, पूर्णांक hw_queue)
अणु
	iwl_mvm_queue_state_change(op_mode, hw_queue, true);
पूर्ण

अटल व्योम iwl_mvm_set_rfसमाप्त_state(काष्ठा iwl_mvm *mvm)
अणु
	bool state = iwl_mvm_is_radio_समाप्तed(mvm);

	अगर (state)
		wake_up(&mvm->rx_sync_रुकोq);

	wiphy_rfसमाप्त_set_hw_state(mvm->hw->wiphy, state);
पूर्ण

व्योम iwl_mvm_set_hw_ctसमाप्त_state(काष्ठा iwl_mvm *mvm, bool state)
अणु
	अगर (state)
		set_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status);
	अन्यथा
		clear_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status);

	iwl_mvm_set_rfसमाप्त_state(mvm);
पूर्ण

अटल bool iwl_mvm_set_hw_rfसमाप्त_state(काष्ठा iwl_op_mode *op_mode, bool state)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	bool rfसमाप्त_safe_init_करोne = READ_ONCE(mvm->rfसमाप्त_safe_init_करोne);
	bool unअगरied = iwl_mvm_has_unअगरied_ucode(mvm);

	अगर (state)
		set_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);
	अन्यथा
		clear_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);

	iwl_mvm_set_rfसमाप्त_state(mvm);

	 /* iwl_run_init_mvm_ucode is रुकोing क्रम results, पात it. */
	अगर (rfसमाप्त_safe_init_करोne)
		iwl_पात_notअगरication_रुकोs(&mvm->notअगर_रुको);

	/*
	 * Don't ask the transport to stop the firmware. We'll करो it
	 * after cfg80211 takes us करोwn.
	 */
	अगर (unअगरied)
		वापस false;

	/*
	 * Stop the device अगर we run OPERATIONAL firmware or अगर we are in the
	 * middle of the calibrations.
	 */
	वापस state && rfसमाप्त_safe_init_करोne;
पूर्ण

अटल व्योम iwl_mvm_मुक्त_skb(काष्ठा iwl_op_mode *op_mode, काष्ठा sk_buff *skb)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा ieee80211_tx_info *info;

	info = IEEE80211_SKB_CB(skb);
	iwl_trans_मुक्त_tx_cmd(mvm->trans, info->driver_data[1]);
	ieee80211_मुक्त_txskb(mvm->hw, skb);
पूर्ण

काष्ठा iwl_mvm_reprobe अणु
	काष्ठा device *dev;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम iwl_mvm_reprobe_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_mvm_reprobe *reprobe;

	reprobe = container_of(wk, काष्ठा iwl_mvm_reprobe, work);
	अगर (device_reprobe(reprobe->dev))
		dev_err(reprobe->dev, "reprobe failed!\n");
	put_device(reprobe->dev);
	kमुक्त(reprobe);
	module_put(THIS_MODULE);
पूर्ण

व्योम iwl_mvm_nic_restart(काष्ठा iwl_mvm *mvm, bool fw_error)
अणु
	iwl_पात_notअगरication_रुकोs(&mvm->notअगर_रुको);
	iwl_dbg_tlv_del_समयrs(mvm->trans);

	/*
	 * This is a bit racy, but worst हाल we tell mac80211 about
	 * a stopped/पातed scan when that was alपढ़ोy करोne which
	 * is not a problem. It is necessary to पात any os scan
	 * here because mac80211 requires having the scan cleared
	 * beक्रमe restarting.
	 * We'll reset the scan_status to NONE in restart cleanup in
	 * the next start() call from mac80211. If restart isn't called
	 * (no fw restart) scan status will stay busy.
	 */
	iwl_mvm_report_scan_पातed(mvm);

	/*
	 * If we're restarting already, don't cycle restarts.
	 * If INIT fw निश्चितed, it will likely fail again.
	 * If WoWLAN fw निश्चितed, करोn't restart either, mac80211
	 * can't recover this since we're alपढ़ोy half suspended.
	 */
	अगर (!mvm->fw_restart && fw_error) अणु
		iwl_fw_error_collect(&mvm->fwrt);
	पूर्ण अन्यथा अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) अणु
		काष्ठा iwl_mvm_reprobe *reprobe;

		IWL_ERR(mvm,
			"Firmware error during reconfiguration - reprobe!\n");

		/*
		 * get a module reference to aव्योम करोing this जबतक unloading
		 * anyway and to aव्योम scheduling a work with code that's
		 * being हटाओd.
		 */
		अगर (!try_module_get(THIS_MODULE)) अणु
			IWL_ERR(mvm, "Module is being unloaded - abort\n");
			वापस;
		पूर्ण

		reprobe = kzalloc(माप(*reprobe), GFP_ATOMIC);
		अगर (!reprobe) अणु
			module_put(THIS_MODULE);
			वापस;
		पूर्ण
		reprobe->dev = get_device(mvm->trans->dev);
		INIT_WORK(&reprobe->work, iwl_mvm_reprobe_wk);
		schedule_work(&reprobe->work);
	पूर्ण अन्यथा अगर (test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
			    &mvm->status)) अणु
		IWL_ERR(mvm, "HW restart already requested, but not started\n");
	पूर्ण अन्यथा अगर (mvm->fwrt.cur_fw_img == IWL_UCODE_REGULAR &&
		   mvm->hw_रेजिस्टरed &&
		   !test_bit(STATUS_TRANS_DEAD, &mvm->trans->status)) अणु
		/* This should be first thing beक्रमe trying to collect any
		 * data to aव्योम endless loops अगर any HW error happens जबतक
		 * collecting debug data.
		 */
		set_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);

		अगर (mvm->fw->ucode_capa.error_log_size) अणु
			u32 src_size = mvm->fw->ucode_capa.error_log_size;
			u32 src_addr = mvm->fw->ucode_capa.error_log_addr;
			u8 *recover_buf = kzalloc(src_size, GFP_ATOMIC);

			अगर (recover_buf) अणु
				mvm->error_recovery_buf = recover_buf;
				iwl_trans_पढ़ो_mem_bytes(mvm->trans,
							 src_addr,
							 recover_buf,
							 src_size);
			पूर्ण
		पूर्ण

		iwl_fw_error_collect(&mvm->fwrt);

		अगर (fw_error && mvm->fw_restart > 0)
			mvm->fw_restart--;
		ieee80211_restart_hw(mvm->hw);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_nic_error(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);

	अगर (!test_bit(STATUS_TRANS_DEAD, &mvm->trans->status))
		iwl_mvm_dump_nic_error_log(mvm);

	iwl_mvm_nic_restart(mvm, true);
पूर्ण

अटल व्योम iwl_mvm_cmd_queue_full(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);

	WARN_ON(1);
	iwl_mvm_nic_restart(mvm, true);
पूर्ण

अटल व्योम iwl_op_mode_mvm_समय_poपूर्णांक(काष्ठा iwl_op_mode *op_mode,
				       क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id,
				       जोड़ iwl_dbg_tlv_tp_data *tp_data)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, tp_id, tp_data);
पूर्ण

#घोषणा IWL_MVM_COMMON_OPS					\
	/* these could be dअगरferentiated */			\
	.async_cb = iwl_mvm_async_cb,				\
	.queue_full = iwl_mvm_stop_sw_queue,			\
	.queue_not_full = iwl_mvm_wake_sw_queue,		\
	.hw_rf_समाप्त = iwl_mvm_set_hw_rfसमाप्त_state,		\
	.मुक्त_skb = iwl_mvm_मुक्त_skb,				\
	.nic_error = iwl_mvm_nic_error,				\
	.cmd_queue_full = iwl_mvm_cmd_queue_full,		\
	.nic_config = iwl_mvm_nic_config,			\
	/* as we only रेजिस्टर one, these MUST be common! */	\
	.start = iwl_op_mode_mvm_start,				\
	.stop = iwl_op_mode_mvm_stop,				\
	.समय_poपूर्णांक = iwl_op_mode_mvm_समय_poपूर्णांक

अटल स्थिर काष्ठा iwl_op_mode_ops iwl_mvm_ops = अणु
	IWL_MVM_COMMON_OPS,
	.rx = iwl_mvm_rx,
पूर्ण;

अटल व्योम iwl_mvm_rx_mq_rss(काष्ठा iwl_op_mode *op_mode,
			      काष्ठा napi_काष्ठा *napi,
			      काष्ठा iwl_rx_cmd_buffer *rxb,
			      अचिन्हित पूर्णांक queue)
अणु
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	u16 cmd = WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd);

	अगर (unlikely(cmd == WIDE_ID(LEGACY_GROUP, FRAME_RELEASE)))
		iwl_mvm_rx_frame_release(mvm, napi, rxb, queue);
	अन्यथा अगर (unlikely(cmd == WIDE_ID(DATA_PATH_GROUP,
					 RX_QUEUES_NOTIFICATION)))
		iwl_mvm_rx_queue_notअगर(mvm, napi, rxb, queue);
	अन्यथा अगर (likely(cmd == WIDE_ID(LEGACY_GROUP, REPLY_RX_MPDU_CMD)))
		iwl_mvm_rx_mpdu_mq(mvm, napi, rxb, queue);
पूर्ण

अटल स्थिर काष्ठा iwl_op_mode_ops iwl_mvm_ops_mq = अणु
	IWL_MVM_COMMON_OPS,
	.rx = iwl_mvm_rx_mq,
	.rx_rss = iwl_mvm_rx_mq_rss,
पूर्ण;
