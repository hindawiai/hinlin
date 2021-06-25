<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>

#समावेश "core.h"
#समावेश "htc.h"
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "wmi-tlv.h"
#समावेश "mac.h"
#समावेश "testmode.h"
#समावेश "wmi-ops.h"
#समावेश "p2p.h"
#समावेश "hw.h"
#समावेश "hif.h"
#समावेश "txrx.h"

#घोषणा ATH10K_WMI_BARRIER_ECHO_ID 0xBA991E9
#घोषणा ATH10K_WMI_BARRIER_TIMEOUT_HZ (3 * HZ)
#घोषणा ATH10K_WMI_DFS_CONF_TIMEOUT_HZ (HZ / 6)

/* MAIN WMI cmd track */
अटल काष्ठा wmi_cmd_map wmi_cmd_map = अणु
	.init_cmdid = WMI_INIT_CMDID,
	.start_scan_cmdid = WMI_START_SCAN_CMDID,
	.stop_scan_cmdid = WMI_STOP_SCAN_CMDID,
	.scan_chan_list_cmdid = WMI_SCAN_CHAN_LIST_CMDID,
	.scan_sch_prio_tbl_cmdid = WMI_SCAN_SCH_PRIO_TBL_CMDID,
	.scan_prob_req_oui_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_regकरोमुख्य_cmdid = WMI_PDEV_SET_REGDOMAIN_CMDID,
	.pdev_set_channel_cmdid = WMI_PDEV_SET_CHANNEL_CMDID,
	.pdev_set_param_cmdid = WMI_PDEV_SET_PARAM_CMDID,
	.pdev_pktlog_enable_cmdid = WMI_PDEV_PKTLOG_ENABLE_CMDID,
	.pdev_pktlog_disable_cmdid = WMI_PDEV_PKTLOG_DISABLE_CMDID,
	.pdev_set_wmm_params_cmdid = WMI_PDEV_SET_WMM_PARAMS_CMDID,
	.pdev_set_ht_cap_ie_cmdid = WMI_PDEV_SET_HT_CAP_IE_CMDID,
	.pdev_set_vht_cap_ie_cmdid = WMI_PDEV_SET_VHT_CAP_IE_CMDID,
	.pdev_set_dscp_tid_map_cmdid = WMI_PDEV_SET_DSCP_TID_MAP_CMDID,
	.pdev_set_quiet_mode_cmdid = WMI_PDEV_SET_QUIET_MODE_CMDID,
	.pdev_green_ap_ps_enable_cmdid = WMI_PDEV_GREEN_AP_PS_ENABLE_CMDID,
	.pdev_get_tpc_config_cmdid = WMI_PDEV_GET_TPC_CONFIG_CMDID,
	.pdev_set_base_macaddr_cmdid = WMI_PDEV_SET_BASE_MACADDR_CMDID,
	.vdev_create_cmdid = WMI_VDEV_CREATE_CMDID,
	.vdev_delete_cmdid = WMI_VDEV_DELETE_CMDID,
	.vdev_start_request_cmdid = WMI_VDEV_START_REQUEST_CMDID,
	.vdev_restart_request_cmdid = WMI_VDEV_RESTART_REQUEST_CMDID,
	.vdev_up_cmdid = WMI_VDEV_UP_CMDID,
	.vdev_stop_cmdid = WMI_VDEV_STOP_CMDID,
	.vdev_करोwn_cmdid = WMI_VDEV_DOWN_CMDID,
	.vdev_set_param_cmdid = WMI_VDEV_SET_PARAM_CMDID,
	.vdev_install_key_cmdid = WMI_VDEV_INSTALL_KEY_CMDID,
	.peer_create_cmdid = WMI_PEER_CREATE_CMDID,
	.peer_delete_cmdid = WMI_PEER_DELETE_CMDID,
	.peer_flush_tids_cmdid = WMI_PEER_FLUSH_TIDS_CMDID,
	.peer_set_param_cmdid = WMI_PEER_SET_PARAM_CMDID,
	.peer_assoc_cmdid = WMI_PEER_ASSOC_CMDID,
	.peer_add_wds_entry_cmdid = WMI_PEER_ADD_WDS_ENTRY_CMDID,
	.peer_हटाओ_wds_entry_cmdid = WMI_PEER_REMOVE_WDS_ENTRY_CMDID,
	.peer_mcast_group_cmdid = WMI_PEER_MCAST_GROUP_CMDID,
	.bcn_tx_cmdid = WMI_BCN_TX_CMDID,
	.pdev_send_bcn_cmdid = WMI_PDEV_SEND_BCN_CMDID,
	.bcn_पंचांगpl_cmdid = WMI_BCN_TMPL_CMDID,
	.bcn_filter_rx_cmdid = WMI_BCN_FILTER_RX_CMDID,
	.prb_req_filter_rx_cmdid = WMI_PRB_REQ_FILTER_RX_CMDID,
	.mgmt_tx_cmdid = WMI_MGMT_TX_CMDID,
	.prb_पंचांगpl_cmdid = WMI_PRB_TMPL_CMDID,
	.addba_clear_resp_cmdid = WMI_ADDBA_CLEAR_RESP_CMDID,
	.addba_send_cmdid = WMI_ADDBA_SEND_CMDID,
	.addba_status_cmdid = WMI_ADDBA_STATUS_CMDID,
	.delba_send_cmdid = WMI_DELBA_SEND_CMDID,
	.addba_set_resp_cmdid = WMI_ADDBA_SET_RESP_CMDID,
	.send_singleamsdu_cmdid = WMI_SEND_SINGLEAMSDU_CMDID,
	.sta_घातersave_mode_cmdid = WMI_STA_POWERSAVE_MODE_CMDID,
	.sta_घातersave_param_cmdid = WMI_STA_POWERSAVE_PARAM_CMDID,
	.sta_mimo_ps_mode_cmdid = WMI_STA_MIMO_PS_MODE_CMDID,
	.pdev_dfs_enable_cmdid = WMI_PDEV_DFS_ENABLE_CMDID,
	.pdev_dfs_disable_cmdid = WMI_PDEV_DFS_DISABLE_CMDID,
	.roam_scan_mode = WMI_ROAM_SCAN_MODE,
	.roam_scan_rssi_threshold = WMI_ROAM_SCAN_RSSI_THRESHOLD,
	.roam_scan_period = WMI_ROAM_SCAN_PERIOD,
	.roam_scan_rssi_change_threshold = WMI_ROAM_SCAN_RSSI_CHANGE_THRESHOLD,
	.roam_ap_profile = WMI_ROAM_AP_PROखाता,
	.ofl_scan_add_ap_profile = WMI_ROAM_AP_PROखाता,
	.ofl_scan_हटाओ_ap_profile = WMI_OFL_SCAN_REMOVE_AP_PROखाता,
	.ofl_scan_period = WMI_OFL_SCAN_PERIOD,
	.p2p_dev_set_device_info = WMI_P2P_DEV_SET_DEVICE_INFO,
	.p2p_dev_set_discoverability = WMI_P2P_DEV_SET_DISCOVERABILITY,
	.p2p_go_set_beacon_ie = WMI_P2P_GO_SET_BEACON_IE,
	.p2p_go_set_probe_resp_ie = WMI_P2P_GO_SET_PROBE_RESP_IE,
	.p2p_set_venकरोr_ie_data_cmdid = WMI_P2P_SET_VENDOR_IE_DATA_CMDID,
	.ap_ps_peer_param_cmdid = WMI_AP_PS_PEER_PARAM_CMDID,
	.ap_ps_peer_uapsd_coex_cmdid = WMI_AP_PS_PEER_UAPSD_COEX_CMDID,
	.peer_rate_retry_sched_cmdid = WMI_PEER_RATE_RETRY_SCHED_CMDID,
	.wlan_profile_trigger_cmdid = WMI_WLAN_PROखाता_TRIGGER_CMDID,
	.wlan_profile_set_hist_पूर्णांकvl_cmdid =
				WMI_WLAN_PROखाता_SET_HIST_INTVL_CMDID,
	.wlan_profile_get_profile_data_cmdid =
				WMI_WLAN_PROखाता_GET_PROखाता_DATA_CMDID,
	.wlan_profile_enable_profile_id_cmdid =
				WMI_WLAN_PROखाता_ENABLE_PROखाता_ID_CMDID,
	.wlan_profile_list_profile_id_cmdid =
				WMI_WLAN_PROखाता_LIST_PROखाता_ID_CMDID,
	.pdev_suspend_cmdid = WMI_PDEV_SUSPEND_CMDID,
	.pdev_resume_cmdid = WMI_PDEV_RESUME_CMDID,
	.add_bcn_filter_cmdid = WMI_ADD_BCN_FILTER_CMDID,
	.rmv_bcn_filter_cmdid = WMI_RMV_BCN_FILTER_CMDID,
	.wow_add_wake_pattern_cmdid = WMI_WOW_ADD_WAKE_PATTERN_CMDID,
	.wow_del_wake_pattern_cmdid = WMI_WOW_DEL_WAKE_PATTERN_CMDID,
	.wow_enable_disable_wake_event_cmdid =
				WMI_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID,
	.wow_enable_cmdid = WMI_WOW_ENABLE_CMDID,
	.wow_hostwakeup_from_sleep_cmdid = WMI_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID,
	.rtt_measreq_cmdid = WMI_RTT_MEASREQ_CMDID,
	.rtt_tsf_cmdid = WMI_RTT_TSF_CMDID,
	.vdev_spectral_scan_configure_cmdid =
				WMI_VDEV_SPECTRAL_SCAN_CONFIGURE_CMDID,
	.vdev_spectral_scan_enable_cmdid = WMI_VDEV_SPECTRAL_SCAN_ENABLE_CMDID,
	.request_stats_cmdid = WMI_REQUEST_STATS_CMDID,
	.set_arp_ns_offload_cmdid = WMI_SET_ARP_NS_OFFLOAD_CMDID,
	.network_list_offload_config_cmdid =
				WMI_NETWORK_LIST_OFFLOAD_CONFIG_CMDID,
	.gtk_offload_cmdid = WMI_GTK_OFFLOAD_CMDID,
	.csa_offload_enable_cmdid = WMI_CSA_OFFLOAD_ENABLE_CMDID,
	.csa_offload_chanचयन_cmdid = WMI_CSA_OFFLOAD_CHANSWITCH_CMDID,
	.chatter_set_mode_cmdid = WMI_CHATTER_SET_MODE_CMDID,
	.peer_tid_addba_cmdid = WMI_PEER_TID_ADDBA_CMDID,
	.peer_tid_delba_cmdid = WMI_PEER_TID_DELBA_CMDID,
	.sta_dtim_ps_method_cmdid = WMI_STA_DTIM_PS_METHOD_CMDID,
	.sta_uapsd_स्वतः_trig_cmdid = WMI_STA_UAPSD_AUTO_TRIG_CMDID,
	.sta_keepalive_cmd = WMI_STA_KEEPALIVE_CMD,
	.echo_cmdid = WMI_ECHO_CMDID,
	.pdev_utf_cmdid = WMI_PDEV_UTF_CMDID,
	.dbglog_cfg_cmdid = WMI_DBGLOG_CFG_CMDID,
	.pdev_qvit_cmdid = WMI_PDEV_QVIT_CMDID,
	.pdev_fपंचांग_पूर्णांकg_cmdid = WMI_PDEV_FTM_INTG_CMDID,
	.vdev_set_keepalive_cmdid = WMI_VDEV_SET_KEEPALIVE_CMDID,
	.vdev_get_keepalive_cmdid = WMI_VDEV_GET_KEEPALIVE_CMDID,
	.क्रमce_fw_hang_cmdid = WMI_FORCE_FW_HANG_CMDID,
	.gpio_config_cmdid = WMI_GPIO_CONFIG_CMDID,
	.gpio_output_cmdid = WMI_GPIO_OUTPUT_CMDID,
	.pdev_get_temperature_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_enable_adaptive_cca_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_update_request_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_standby_response_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_resume_response_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_add_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_evict_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_restore_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_prपूर्णांक_all_peers_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_update_wds_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_add_proxy_sta_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.rtt_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.oem_req_cmdid = WMI_CMD_UNSUPPORTED,
	.nan_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_ratemask_cmdid = WMI_CMD_UNSUPPORTED,
	.qboost_cfg_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_set_rx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_tx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_train_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_node_config_ops_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_antenna_चयन_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_ctl_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_mimogain_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_chainmsk_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_fips_cmdid = WMI_CMD_UNSUPPORTED,
	.tt_set_conf_cmdid = WMI_CMD_UNSUPPORTED,
	.fwtest_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_cck_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_ofdm_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_reserve_ast_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_nfcal_घातer_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_tpc_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ast_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_dscp_tid_map_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_get_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_filter_neighbor_rx_packets_cmdid = WMI_CMD_UNSUPPORTED,
	.mu_cal_start_cmdid = WMI_CMD_UNSUPPORTED,
	.set_cca_params_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_bss_chan_info_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_tpc_table_cmdid = WMI_CMD_UNSUPPORTED,
	.radar_found_cmdid = WMI_CMD_UNSUPPORTED,
पूर्ण;

/* 10.X WMI cmd track */
अटल काष्ठा wmi_cmd_map wmi_10x_cmd_map = अणु
	.init_cmdid = WMI_10X_INIT_CMDID,
	.start_scan_cmdid = WMI_10X_START_SCAN_CMDID,
	.stop_scan_cmdid = WMI_10X_STOP_SCAN_CMDID,
	.scan_chan_list_cmdid = WMI_10X_SCAN_CHAN_LIST_CMDID,
	.scan_sch_prio_tbl_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_prob_req_oui_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_regकरोमुख्य_cmdid = WMI_10X_PDEV_SET_REGDOMAIN_CMDID,
	.pdev_set_channel_cmdid = WMI_10X_PDEV_SET_CHANNEL_CMDID,
	.pdev_set_param_cmdid = WMI_10X_PDEV_SET_PARAM_CMDID,
	.pdev_pktlog_enable_cmdid = WMI_10X_PDEV_PKTLOG_ENABLE_CMDID,
	.pdev_pktlog_disable_cmdid = WMI_10X_PDEV_PKTLOG_DISABLE_CMDID,
	.pdev_set_wmm_params_cmdid = WMI_10X_PDEV_SET_WMM_PARAMS_CMDID,
	.pdev_set_ht_cap_ie_cmdid = WMI_10X_PDEV_SET_HT_CAP_IE_CMDID,
	.pdev_set_vht_cap_ie_cmdid = WMI_10X_PDEV_SET_VHT_CAP_IE_CMDID,
	.pdev_set_dscp_tid_map_cmdid = WMI_10X_PDEV_SET_DSCP_TID_MAP_CMDID,
	.pdev_set_quiet_mode_cmdid = WMI_10X_PDEV_SET_QUIET_MODE_CMDID,
	.pdev_green_ap_ps_enable_cmdid = WMI_10X_PDEV_GREEN_AP_PS_ENABLE_CMDID,
	.pdev_get_tpc_config_cmdid = WMI_10X_PDEV_GET_TPC_CONFIG_CMDID,
	.pdev_set_base_macaddr_cmdid = WMI_10X_PDEV_SET_BASE_MACADDR_CMDID,
	.vdev_create_cmdid = WMI_10X_VDEV_CREATE_CMDID,
	.vdev_delete_cmdid = WMI_10X_VDEV_DELETE_CMDID,
	.vdev_start_request_cmdid = WMI_10X_VDEV_START_REQUEST_CMDID,
	.vdev_restart_request_cmdid = WMI_10X_VDEV_RESTART_REQUEST_CMDID,
	.vdev_up_cmdid = WMI_10X_VDEV_UP_CMDID,
	.vdev_stop_cmdid = WMI_10X_VDEV_STOP_CMDID,
	.vdev_करोwn_cmdid = WMI_10X_VDEV_DOWN_CMDID,
	.vdev_set_param_cmdid = WMI_10X_VDEV_SET_PARAM_CMDID,
	.vdev_install_key_cmdid = WMI_10X_VDEV_INSTALL_KEY_CMDID,
	.peer_create_cmdid = WMI_10X_PEER_CREATE_CMDID,
	.peer_delete_cmdid = WMI_10X_PEER_DELETE_CMDID,
	.peer_flush_tids_cmdid = WMI_10X_PEER_FLUSH_TIDS_CMDID,
	.peer_set_param_cmdid = WMI_10X_PEER_SET_PARAM_CMDID,
	.peer_assoc_cmdid = WMI_10X_PEER_ASSOC_CMDID,
	.peer_add_wds_entry_cmdid = WMI_10X_PEER_ADD_WDS_ENTRY_CMDID,
	.peer_हटाओ_wds_entry_cmdid = WMI_10X_PEER_REMOVE_WDS_ENTRY_CMDID,
	.peer_mcast_group_cmdid = WMI_10X_PEER_MCAST_GROUP_CMDID,
	.bcn_tx_cmdid = WMI_10X_BCN_TX_CMDID,
	.pdev_send_bcn_cmdid = WMI_10X_PDEV_SEND_BCN_CMDID,
	.bcn_पंचांगpl_cmdid = WMI_CMD_UNSUPPORTED,
	.bcn_filter_rx_cmdid = WMI_10X_BCN_FILTER_RX_CMDID,
	.prb_req_filter_rx_cmdid = WMI_10X_PRB_REQ_FILTER_RX_CMDID,
	.mgmt_tx_cmdid = WMI_10X_MGMT_TX_CMDID,
	.prb_पंचांगpl_cmdid = WMI_CMD_UNSUPPORTED,
	.addba_clear_resp_cmdid = WMI_10X_ADDBA_CLEAR_RESP_CMDID,
	.addba_send_cmdid = WMI_10X_ADDBA_SEND_CMDID,
	.addba_status_cmdid = WMI_10X_ADDBA_STATUS_CMDID,
	.delba_send_cmdid = WMI_10X_DELBA_SEND_CMDID,
	.addba_set_resp_cmdid = WMI_10X_ADDBA_SET_RESP_CMDID,
	.send_singleamsdu_cmdid = WMI_10X_SEND_SINGLEAMSDU_CMDID,
	.sta_घातersave_mode_cmdid = WMI_10X_STA_POWERSAVE_MODE_CMDID,
	.sta_घातersave_param_cmdid = WMI_10X_STA_POWERSAVE_PARAM_CMDID,
	.sta_mimo_ps_mode_cmdid = WMI_10X_STA_MIMO_PS_MODE_CMDID,
	.pdev_dfs_enable_cmdid = WMI_10X_PDEV_DFS_ENABLE_CMDID,
	.pdev_dfs_disable_cmdid = WMI_10X_PDEV_DFS_DISABLE_CMDID,
	.roam_scan_mode = WMI_10X_ROAM_SCAN_MODE,
	.roam_scan_rssi_threshold = WMI_10X_ROAM_SCAN_RSSI_THRESHOLD,
	.roam_scan_period = WMI_10X_ROAM_SCAN_PERIOD,
	.roam_scan_rssi_change_threshold =
				WMI_10X_ROAM_SCAN_RSSI_CHANGE_THRESHOLD,
	.roam_ap_profile = WMI_10X_ROAM_AP_PROखाता,
	.ofl_scan_add_ap_profile = WMI_10X_OFL_SCAN_ADD_AP_PROखाता,
	.ofl_scan_हटाओ_ap_profile = WMI_10X_OFL_SCAN_REMOVE_AP_PROखाता,
	.ofl_scan_period = WMI_10X_OFL_SCAN_PERIOD,
	.p2p_dev_set_device_info = WMI_10X_P2P_DEV_SET_DEVICE_INFO,
	.p2p_dev_set_discoverability = WMI_10X_P2P_DEV_SET_DISCOVERABILITY,
	.p2p_go_set_beacon_ie = WMI_10X_P2P_GO_SET_BEACON_IE,
	.p2p_go_set_probe_resp_ie = WMI_10X_P2P_GO_SET_PROBE_RESP_IE,
	.p2p_set_venकरोr_ie_data_cmdid = WMI_CMD_UNSUPPORTED,
	.ap_ps_peer_param_cmdid = WMI_10X_AP_PS_PEER_PARAM_CMDID,
	.ap_ps_peer_uapsd_coex_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_rate_retry_sched_cmdid = WMI_10X_PEER_RATE_RETRY_SCHED_CMDID,
	.wlan_profile_trigger_cmdid = WMI_10X_WLAN_PROखाता_TRIGGER_CMDID,
	.wlan_profile_set_hist_पूर्णांकvl_cmdid =
				WMI_10X_WLAN_PROखाता_SET_HIST_INTVL_CMDID,
	.wlan_profile_get_profile_data_cmdid =
				WMI_10X_WLAN_PROखाता_GET_PROखाता_DATA_CMDID,
	.wlan_profile_enable_profile_id_cmdid =
				WMI_10X_WLAN_PROखाता_ENABLE_PROखाता_ID_CMDID,
	.wlan_profile_list_profile_id_cmdid =
				WMI_10X_WLAN_PROखाता_LIST_PROखाता_ID_CMDID,
	.pdev_suspend_cmdid = WMI_10X_PDEV_SUSPEND_CMDID,
	.pdev_resume_cmdid = WMI_10X_PDEV_RESUME_CMDID,
	.add_bcn_filter_cmdid = WMI_10X_ADD_BCN_FILTER_CMDID,
	.rmv_bcn_filter_cmdid = WMI_10X_RMV_BCN_FILTER_CMDID,
	.wow_add_wake_pattern_cmdid = WMI_10X_WOW_ADD_WAKE_PATTERN_CMDID,
	.wow_del_wake_pattern_cmdid = WMI_10X_WOW_DEL_WAKE_PATTERN_CMDID,
	.wow_enable_disable_wake_event_cmdid =
				WMI_10X_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID,
	.wow_enable_cmdid = WMI_10X_WOW_ENABLE_CMDID,
	.wow_hostwakeup_from_sleep_cmdid =
				WMI_10X_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID,
	.rtt_measreq_cmdid = WMI_10X_RTT_MEASREQ_CMDID,
	.rtt_tsf_cmdid = WMI_10X_RTT_TSF_CMDID,
	.vdev_spectral_scan_configure_cmdid =
				WMI_10X_VDEV_SPECTRAL_SCAN_CONFIGURE_CMDID,
	.vdev_spectral_scan_enable_cmdid =
				WMI_10X_VDEV_SPECTRAL_SCAN_ENABLE_CMDID,
	.request_stats_cmdid = WMI_10X_REQUEST_STATS_CMDID,
	.set_arp_ns_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.network_list_offload_config_cmdid = WMI_CMD_UNSUPPORTED,
	.gtk_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.csa_offload_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.csa_offload_chanचयन_cmdid = WMI_CMD_UNSUPPORTED,
	.chatter_set_mode_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_addba_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_delba_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_dtim_ps_method_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_uapsd_स्वतः_trig_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_keepalive_cmd = WMI_CMD_UNSUPPORTED,
	.echo_cmdid = WMI_10X_ECHO_CMDID,
	.pdev_utf_cmdid = WMI_10X_PDEV_UTF_CMDID,
	.dbglog_cfg_cmdid = WMI_10X_DBGLOG_CFG_CMDID,
	.pdev_qvit_cmdid = WMI_10X_PDEV_QVIT_CMDID,
	.pdev_fपंचांग_पूर्णांकg_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_get_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.क्रमce_fw_hang_cmdid = WMI_CMD_UNSUPPORTED,
	.gpio_config_cmdid = WMI_10X_GPIO_CONFIG_CMDID,
	.gpio_output_cmdid = WMI_10X_GPIO_OUTPUT_CMDID,
	.pdev_get_temperature_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_enable_adaptive_cca_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_update_request_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_standby_response_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_resume_response_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_add_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_evict_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_restore_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_prपूर्णांक_all_peers_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_update_wds_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_add_proxy_sta_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.rtt_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.oem_req_cmdid = WMI_CMD_UNSUPPORTED,
	.nan_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_ratemask_cmdid = WMI_CMD_UNSUPPORTED,
	.qboost_cfg_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_set_rx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_tx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_train_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_node_config_ops_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_antenna_चयन_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_ctl_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_mimogain_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_chainmsk_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_fips_cmdid = WMI_CMD_UNSUPPORTED,
	.tt_set_conf_cmdid = WMI_CMD_UNSUPPORTED,
	.fwtest_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_cck_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_ofdm_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_reserve_ast_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_nfcal_घातer_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_tpc_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ast_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_dscp_tid_map_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_get_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_filter_neighbor_rx_packets_cmdid = WMI_CMD_UNSUPPORTED,
	.mu_cal_start_cmdid = WMI_CMD_UNSUPPORTED,
	.set_cca_params_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_bss_chan_info_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_tpc_table_cmdid = WMI_CMD_UNSUPPORTED,
	.radar_found_cmdid = WMI_CMD_UNSUPPORTED,
पूर्ण;

/* 10.2.4 WMI cmd track */
अटल काष्ठा wmi_cmd_map wmi_10_2_4_cmd_map = अणु
	.init_cmdid = WMI_10_2_INIT_CMDID,
	.start_scan_cmdid = WMI_10_2_START_SCAN_CMDID,
	.stop_scan_cmdid = WMI_10_2_STOP_SCAN_CMDID,
	.scan_chan_list_cmdid = WMI_10_2_SCAN_CHAN_LIST_CMDID,
	.scan_sch_prio_tbl_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_prob_req_oui_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_regकरोमुख्य_cmdid = WMI_10_2_PDEV_SET_REGDOMAIN_CMDID,
	.pdev_set_channel_cmdid = WMI_10_2_PDEV_SET_CHANNEL_CMDID,
	.pdev_set_param_cmdid = WMI_10_2_PDEV_SET_PARAM_CMDID,
	.pdev_pktlog_enable_cmdid = WMI_10_2_PDEV_PKTLOG_ENABLE_CMDID,
	.pdev_pktlog_disable_cmdid = WMI_10_2_PDEV_PKTLOG_DISABLE_CMDID,
	.pdev_set_wmm_params_cmdid = WMI_10_2_PDEV_SET_WMM_PARAMS_CMDID,
	.pdev_set_ht_cap_ie_cmdid = WMI_10_2_PDEV_SET_HT_CAP_IE_CMDID,
	.pdev_set_vht_cap_ie_cmdid = WMI_10_2_PDEV_SET_VHT_CAP_IE_CMDID,
	.pdev_set_quiet_mode_cmdid = WMI_10_2_PDEV_SET_QUIET_MODE_CMDID,
	.pdev_green_ap_ps_enable_cmdid = WMI_10_2_PDEV_GREEN_AP_PS_ENABLE_CMDID,
	.pdev_get_tpc_config_cmdid = WMI_10_2_PDEV_GET_TPC_CONFIG_CMDID,
	.pdev_set_base_macaddr_cmdid = WMI_10_2_PDEV_SET_BASE_MACADDR_CMDID,
	.vdev_create_cmdid = WMI_10_2_VDEV_CREATE_CMDID,
	.vdev_delete_cmdid = WMI_10_2_VDEV_DELETE_CMDID,
	.vdev_start_request_cmdid = WMI_10_2_VDEV_START_REQUEST_CMDID,
	.vdev_restart_request_cmdid = WMI_10_2_VDEV_RESTART_REQUEST_CMDID,
	.vdev_up_cmdid = WMI_10_2_VDEV_UP_CMDID,
	.vdev_stop_cmdid = WMI_10_2_VDEV_STOP_CMDID,
	.vdev_करोwn_cmdid = WMI_10_2_VDEV_DOWN_CMDID,
	.vdev_set_param_cmdid = WMI_10_2_VDEV_SET_PARAM_CMDID,
	.vdev_install_key_cmdid = WMI_10_2_VDEV_INSTALL_KEY_CMDID,
	.peer_create_cmdid = WMI_10_2_PEER_CREATE_CMDID,
	.peer_delete_cmdid = WMI_10_2_PEER_DELETE_CMDID,
	.peer_flush_tids_cmdid = WMI_10_2_PEER_FLUSH_TIDS_CMDID,
	.peer_set_param_cmdid = WMI_10_2_PEER_SET_PARAM_CMDID,
	.peer_assoc_cmdid = WMI_10_2_PEER_ASSOC_CMDID,
	.peer_add_wds_entry_cmdid = WMI_10_2_PEER_ADD_WDS_ENTRY_CMDID,
	.peer_हटाओ_wds_entry_cmdid = WMI_10_2_PEER_REMOVE_WDS_ENTRY_CMDID,
	.peer_mcast_group_cmdid = WMI_10_2_PEER_MCAST_GROUP_CMDID,
	.bcn_tx_cmdid = WMI_10_2_BCN_TX_CMDID,
	.pdev_send_bcn_cmdid = WMI_10_2_PDEV_SEND_BCN_CMDID,
	.bcn_पंचांगpl_cmdid = WMI_CMD_UNSUPPORTED,
	.bcn_filter_rx_cmdid = WMI_10_2_BCN_FILTER_RX_CMDID,
	.prb_req_filter_rx_cmdid = WMI_10_2_PRB_REQ_FILTER_RX_CMDID,
	.mgmt_tx_cmdid = WMI_10_2_MGMT_TX_CMDID,
	.prb_पंचांगpl_cmdid = WMI_CMD_UNSUPPORTED,
	.addba_clear_resp_cmdid = WMI_10_2_ADDBA_CLEAR_RESP_CMDID,
	.addba_send_cmdid = WMI_10_2_ADDBA_SEND_CMDID,
	.addba_status_cmdid = WMI_10_2_ADDBA_STATUS_CMDID,
	.delba_send_cmdid = WMI_10_2_DELBA_SEND_CMDID,
	.addba_set_resp_cmdid = WMI_10_2_ADDBA_SET_RESP_CMDID,
	.send_singleamsdu_cmdid = WMI_10_2_SEND_SINGLEAMSDU_CMDID,
	.sta_घातersave_mode_cmdid = WMI_10_2_STA_POWERSAVE_MODE_CMDID,
	.sta_घातersave_param_cmdid = WMI_10_2_STA_POWERSAVE_PARAM_CMDID,
	.sta_mimo_ps_mode_cmdid = WMI_10_2_STA_MIMO_PS_MODE_CMDID,
	.pdev_dfs_enable_cmdid = WMI_10_2_PDEV_DFS_ENABLE_CMDID,
	.pdev_dfs_disable_cmdid = WMI_10_2_PDEV_DFS_DISABLE_CMDID,
	.roam_scan_mode = WMI_10_2_ROAM_SCAN_MODE,
	.roam_scan_rssi_threshold = WMI_10_2_ROAM_SCAN_RSSI_THRESHOLD,
	.roam_scan_period = WMI_10_2_ROAM_SCAN_PERIOD,
	.roam_scan_rssi_change_threshold =
				WMI_10_2_ROAM_SCAN_RSSI_CHANGE_THRESHOLD,
	.roam_ap_profile = WMI_10_2_ROAM_AP_PROखाता,
	.ofl_scan_add_ap_profile = WMI_10_2_OFL_SCAN_ADD_AP_PROखाता,
	.ofl_scan_हटाओ_ap_profile = WMI_10_2_OFL_SCAN_REMOVE_AP_PROखाता,
	.ofl_scan_period = WMI_10_2_OFL_SCAN_PERIOD,
	.p2p_dev_set_device_info = WMI_10_2_P2P_DEV_SET_DEVICE_INFO,
	.p2p_dev_set_discoverability = WMI_10_2_P2P_DEV_SET_DISCOVERABILITY,
	.p2p_go_set_beacon_ie = WMI_10_2_P2P_GO_SET_BEACON_IE,
	.p2p_go_set_probe_resp_ie = WMI_10_2_P2P_GO_SET_PROBE_RESP_IE,
	.p2p_set_venकरोr_ie_data_cmdid = WMI_CMD_UNSUPPORTED,
	.ap_ps_peer_param_cmdid = WMI_10_2_AP_PS_PEER_PARAM_CMDID,
	.ap_ps_peer_uapsd_coex_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_rate_retry_sched_cmdid = WMI_10_2_PEER_RATE_RETRY_SCHED_CMDID,
	.wlan_profile_trigger_cmdid = WMI_10_2_WLAN_PROखाता_TRIGGER_CMDID,
	.wlan_profile_set_hist_पूर्णांकvl_cmdid =
				WMI_10_2_WLAN_PROखाता_SET_HIST_INTVL_CMDID,
	.wlan_profile_get_profile_data_cmdid =
				WMI_10_2_WLAN_PROखाता_GET_PROखाता_DATA_CMDID,
	.wlan_profile_enable_profile_id_cmdid =
				WMI_10_2_WLAN_PROखाता_ENABLE_PROखाता_ID_CMDID,
	.wlan_profile_list_profile_id_cmdid =
				WMI_10_2_WLAN_PROखाता_LIST_PROखाता_ID_CMDID,
	.pdev_suspend_cmdid = WMI_10_2_PDEV_SUSPEND_CMDID,
	.pdev_resume_cmdid = WMI_10_2_PDEV_RESUME_CMDID,
	.add_bcn_filter_cmdid = WMI_10_2_ADD_BCN_FILTER_CMDID,
	.rmv_bcn_filter_cmdid = WMI_10_2_RMV_BCN_FILTER_CMDID,
	.wow_add_wake_pattern_cmdid = WMI_10_2_WOW_ADD_WAKE_PATTERN_CMDID,
	.wow_del_wake_pattern_cmdid = WMI_10_2_WOW_DEL_WAKE_PATTERN_CMDID,
	.wow_enable_disable_wake_event_cmdid =
				WMI_10_2_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID,
	.wow_enable_cmdid = WMI_10_2_WOW_ENABLE_CMDID,
	.wow_hostwakeup_from_sleep_cmdid =
				WMI_10_2_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID,
	.rtt_measreq_cmdid = WMI_10_2_RTT_MEASREQ_CMDID,
	.rtt_tsf_cmdid = WMI_10_2_RTT_TSF_CMDID,
	.vdev_spectral_scan_configure_cmdid =
				WMI_10_2_VDEV_SPECTRAL_SCAN_CONFIGURE_CMDID,
	.vdev_spectral_scan_enable_cmdid =
				WMI_10_2_VDEV_SPECTRAL_SCAN_ENABLE_CMDID,
	.request_stats_cmdid = WMI_10_2_REQUEST_STATS_CMDID,
	.set_arp_ns_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.network_list_offload_config_cmdid = WMI_CMD_UNSUPPORTED,
	.gtk_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.csa_offload_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.csa_offload_chanचयन_cmdid = WMI_CMD_UNSUPPORTED,
	.chatter_set_mode_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_addba_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_delba_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_dtim_ps_method_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_uapsd_स्वतः_trig_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_keepalive_cmd = WMI_CMD_UNSUPPORTED,
	.echo_cmdid = WMI_10_2_ECHO_CMDID,
	.pdev_utf_cmdid = WMI_10_2_PDEV_UTF_CMDID,
	.dbglog_cfg_cmdid = WMI_10_2_DBGLOG_CFG_CMDID,
	.pdev_qvit_cmdid = WMI_10_2_PDEV_QVIT_CMDID,
	.pdev_fपंचांग_पूर्णांकg_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_get_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.क्रमce_fw_hang_cmdid = WMI_CMD_UNSUPPORTED,
	.gpio_config_cmdid = WMI_10_2_GPIO_CONFIG_CMDID,
	.gpio_output_cmdid = WMI_10_2_GPIO_OUTPUT_CMDID,
	.pdev_get_temperature_cmdid = WMI_10_2_PDEV_GET_TEMPERATURE_CMDID,
	.pdev_enable_adaptive_cca_cmdid = WMI_10_2_SET_CCA_PARAMS,
	.scan_update_request_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_standby_response_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_resume_response_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_add_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_evict_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_restore_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_prपूर्णांक_all_peers_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_update_wds_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_add_proxy_sta_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.rtt_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.oem_req_cmdid = WMI_CMD_UNSUPPORTED,
	.nan_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_ratemask_cmdid = WMI_CMD_UNSUPPORTED,
	.qboost_cfg_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_set_rx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_tx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_train_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_node_config_ops_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_antenna_चयन_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_ctl_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_mimogain_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_chainmsk_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_fips_cmdid = WMI_CMD_UNSUPPORTED,
	.tt_set_conf_cmdid = WMI_CMD_UNSUPPORTED,
	.fwtest_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_cck_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_ofdm_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_reserve_ast_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_nfcal_घातer_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_tpc_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ast_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_dscp_tid_map_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_get_info_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_filter_neighbor_rx_packets_cmdid = WMI_CMD_UNSUPPORTED,
	.mu_cal_start_cmdid = WMI_CMD_UNSUPPORTED,
	.set_cca_params_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_bss_chan_info_request_cmdid =
		WMI_10_2_PDEV_BSS_CHAN_INFO_REQUEST_CMDID,
	.pdev_get_tpc_table_cmdid = WMI_CMD_UNSUPPORTED,
	.radar_found_cmdid = WMI_CMD_UNSUPPORTED,
	.set_bb_timing_cmdid = WMI_10_2_PDEV_SET_BB_TIMING_CONFIG_CMDID,
पूर्ण;

/* 10.4 WMI cmd track */
अटल काष्ठा wmi_cmd_map wmi_10_4_cmd_map = अणु
	.init_cmdid = WMI_10_4_INIT_CMDID,
	.start_scan_cmdid = WMI_10_4_START_SCAN_CMDID,
	.stop_scan_cmdid = WMI_10_4_STOP_SCAN_CMDID,
	.scan_chan_list_cmdid = WMI_10_4_SCAN_CHAN_LIST_CMDID,
	.scan_sch_prio_tbl_cmdid = WMI_10_4_SCAN_SCH_PRIO_TBL_CMDID,
	.scan_prob_req_oui_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_regकरोमुख्य_cmdid = WMI_10_4_PDEV_SET_REGDOMAIN_CMDID,
	.pdev_set_channel_cmdid = WMI_10_4_PDEV_SET_CHANNEL_CMDID,
	.pdev_set_param_cmdid = WMI_10_4_PDEV_SET_PARAM_CMDID,
	.pdev_pktlog_enable_cmdid = WMI_10_4_PDEV_PKTLOG_ENABLE_CMDID,
	.pdev_pktlog_disable_cmdid = WMI_10_4_PDEV_PKTLOG_DISABLE_CMDID,
	.pdev_set_wmm_params_cmdid = WMI_10_4_PDEV_SET_WMM_PARAMS_CMDID,
	.pdev_set_ht_cap_ie_cmdid = WMI_10_4_PDEV_SET_HT_CAP_IE_CMDID,
	.pdev_set_vht_cap_ie_cmdid = WMI_10_4_PDEV_SET_VHT_CAP_IE_CMDID,
	.pdev_set_dscp_tid_map_cmdid = WMI_10_4_PDEV_SET_DSCP_TID_MAP_CMDID,
	.pdev_set_quiet_mode_cmdid = WMI_10_4_PDEV_SET_QUIET_MODE_CMDID,
	.pdev_green_ap_ps_enable_cmdid = WMI_10_4_PDEV_GREEN_AP_PS_ENABLE_CMDID,
	.pdev_get_tpc_config_cmdid = WMI_10_4_PDEV_GET_TPC_CONFIG_CMDID,
	.pdev_set_base_macaddr_cmdid = WMI_10_4_PDEV_SET_BASE_MACADDR_CMDID,
	.vdev_create_cmdid = WMI_10_4_VDEV_CREATE_CMDID,
	.vdev_delete_cmdid = WMI_10_4_VDEV_DELETE_CMDID,
	.vdev_start_request_cmdid = WMI_10_4_VDEV_START_REQUEST_CMDID,
	.vdev_restart_request_cmdid = WMI_10_4_VDEV_RESTART_REQUEST_CMDID,
	.vdev_up_cmdid = WMI_10_4_VDEV_UP_CMDID,
	.vdev_stop_cmdid = WMI_10_4_VDEV_STOP_CMDID,
	.vdev_करोwn_cmdid = WMI_10_4_VDEV_DOWN_CMDID,
	.vdev_set_param_cmdid = WMI_10_4_VDEV_SET_PARAM_CMDID,
	.vdev_install_key_cmdid = WMI_10_4_VDEV_INSTALL_KEY_CMDID,
	.peer_create_cmdid = WMI_10_4_PEER_CREATE_CMDID,
	.peer_delete_cmdid = WMI_10_4_PEER_DELETE_CMDID,
	.peer_flush_tids_cmdid = WMI_10_4_PEER_FLUSH_TIDS_CMDID,
	.peer_set_param_cmdid = WMI_10_4_PEER_SET_PARAM_CMDID,
	.peer_assoc_cmdid = WMI_10_4_PEER_ASSOC_CMDID,
	.peer_add_wds_entry_cmdid = WMI_10_4_PEER_ADD_WDS_ENTRY_CMDID,
	.peer_हटाओ_wds_entry_cmdid = WMI_10_4_PEER_REMOVE_WDS_ENTRY_CMDID,
	.peer_mcast_group_cmdid = WMI_10_4_PEER_MCAST_GROUP_CMDID,
	.bcn_tx_cmdid = WMI_10_4_BCN_TX_CMDID,
	.pdev_send_bcn_cmdid = WMI_10_4_PDEV_SEND_BCN_CMDID,
	.bcn_पंचांगpl_cmdid = WMI_10_4_BCN_PRB_TMPL_CMDID,
	.bcn_filter_rx_cmdid = WMI_10_4_BCN_FILTER_RX_CMDID,
	.prb_req_filter_rx_cmdid = WMI_10_4_PRB_REQ_FILTER_RX_CMDID,
	.mgmt_tx_cmdid = WMI_10_4_MGMT_TX_CMDID,
	.prb_पंचांगpl_cmdid = WMI_10_4_PRB_TMPL_CMDID,
	.addba_clear_resp_cmdid = WMI_10_4_ADDBA_CLEAR_RESP_CMDID,
	.addba_send_cmdid = WMI_10_4_ADDBA_SEND_CMDID,
	.addba_status_cmdid = WMI_10_4_ADDBA_STATUS_CMDID,
	.delba_send_cmdid = WMI_10_4_DELBA_SEND_CMDID,
	.addba_set_resp_cmdid = WMI_10_4_ADDBA_SET_RESP_CMDID,
	.send_singleamsdu_cmdid = WMI_10_4_SEND_SINGLEAMSDU_CMDID,
	.sta_घातersave_mode_cmdid = WMI_10_4_STA_POWERSAVE_MODE_CMDID,
	.sta_घातersave_param_cmdid = WMI_10_4_STA_POWERSAVE_PARAM_CMDID,
	.sta_mimo_ps_mode_cmdid = WMI_10_4_STA_MIMO_PS_MODE_CMDID,
	.pdev_dfs_enable_cmdid = WMI_10_4_PDEV_DFS_ENABLE_CMDID,
	.pdev_dfs_disable_cmdid = WMI_10_4_PDEV_DFS_DISABLE_CMDID,
	.roam_scan_mode = WMI_10_4_ROAM_SCAN_MODE,
	.roam_scan_rssi_threshold = WMI_10_4_ROAM_SCAN_RSSI_THRESHOLD,
	.roam_scan_period = WMI_10_4_ROAM_SCAN_PERIOD,
	.roam_scan_rssi_change_threshold =
				WMI_10_4_ROAM_SCAN_RSSI_CHANGE_THRESHOLD,
	.roam_ap_profile = WMI_10_4_ROAM_AP_PROखाता,
	.ofl_scan_add_ap_profile = WMI_10_4_OFL_SCAN_ADD_AP_PROखाता,
	.ofl_scan_हटाओ_ap_profile = WMI_10_4_OFL_SCAN_REMOVE_AP_PROखाता,
	.ofl_scan_period = WMI_10_4_OFL_SCAN_PERIOD,
	.p2p_dev_set_device_info = WMI_10_4_P2P_DEV_SET_DEVICE_INFO,
	.p2p_dev_set_discoverability = WMI_10_4_P2P_DEV_SET_DISCOVERABILITY,
	.p2p_go_set_beacon_ie = WMI_10_4_P2P_GO_SET_BEACON_IE,
	.p2p_go_set_probe_resp_ie = WMI_10_4_P2P_GO_SET_PROBE_RESP_IE,
	.p2p_set_venकरोr_ie_data_cmdid = WMI_10_4_P2P_SET_VENDOR_IE_DATA_CMDID,
	.ap_ps_peer_param_cmdid = WMI_10_4_AP_PS_PEER_PARAM_CMDID,
	.ap_ps_peer_uapsd_coex_cmdid = WMI_10_4_AP_PS_PEER_UAPSD_COEX_CMDID,
	.peer_rate_retry_sched_cmdid = WMI_10_4_PEER_RATE_RETRY_SCHED_CMDID,
	.wlan_profile_trigger_cmdid = WMI_10_4_WLAN_PROखाता_TRIGGER_CMDID,
	.wlan_profile_set_hist_पूर्णांकvl_cmdid =
				WMI_10_4_WLAN_PROखाता_SET_HIST_INTVL_CMDID,
	.wlan_profile_get_profile_data_cmdid =
				WMI_10_4_WLAN_PROखाता_GET_PROखाता_DATA_CMDID,
	.wlan_profile_enable_profile_id_cmdid =
				WMI_10_4_WLAN_PROखाता_ENABLE_PROखाता_ID_CMDID,
	.wlan_profile_list_profile_id_cmdid =
				WMI_10_4_WLAN_PROखाता_LIST_PROखाता_ID_CMDID,
	.pdev_suspend_cmdid = WMI_10_4_PDEV_SUSPEND_CMDID,
	.pdev_resume_cmdid = WMI_10_4_PDEV_RESUME_CMDID,
	.add_bcn_filter_cmdid = WMI_10_4_ADD_BCN_FILTER_CMDID,
	.rmv_bcn_filter_cmdid = WMI_10_4_RMV_BCN_FILTER_CMDID,
	.wow_add_wake_pattern_cmdid = WMI_10_4_WOW_ADD_WAKE_PATTERN_CMDID,
	.wow_del_wake_pattern_cmdid = WMI_10_4_WOW_DEL_WAKE_PATTERN_CMDID,
	.wow_enable_disable_wake_event_cmdid =
				WMI_10_4_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID,
	.wow_enable_cmdid = WMI_10_4_WOW_ENABLE_CMDID,
	.wow_hostwakeup_from_sleep_cmdid =
				WMI_10_4_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID,
	.rtt_measreq_cmdid = WMI_10_4_RTT_MEASREQ_CMDID,
	.rtt_tsf_cmdid = WMI_10_4_RTT_TSF_CMDID,
	.vdev_spectral_scan_configure_cmdid =
				WMI_10_4_VDEV_SPECTRAL_SCAN_CONFIGURE_CMDID,
	.vdev_spectral_scan_enable_cmdid =
				WMI_10_4_VDEV_SPECTRAL_SCAN_ENABLE_CMDID,
	.request_stats_cmdid = WMI_10_4_REQUEST_STATS_CMDID,
	.set_arp_ns_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.network_list_offload_config_cmdid = WMI_CMD_UNSUPPORTED,
	.gtk_offload_cmdid = WMI_10_4_GTK_OFFLOAD_CMDID,
	.csa_offload_enable_cmdid = WMI_10_4_CSA_OFFLOAD_ENABLE_CMDID,
	.csa_offload_chanचयन_cmdid = WMI_10_4_CSA_OFFLOAD_CHANSWITCH_CMDID,
	.chatter_set_mode_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_addba_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_delba_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_dtim_ps_method_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_uapsd_स्वतः_trig_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_keepalive_cmd = WMI_CMD_UNSUPPORTED,
	.echo_cmdid = WMI_10_4_ECHO_CMDID,
	.pdev_utf_cmdid = WMI_10_4_PDEV_UTF_CMDID,
	.dbglog_cfg_cmdid = WMI_10_4_DBGLOG_CFG_CMDID,
	.pdev_qvit_cmdid = WMI_10_4_PDEV_QVIT_CMDID,
	.pdev_fपंचांग_पूर्णांकg_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_keepalive_cmdid = WMI_10_4_VDEV_SET_KEEPALIVE_CMDID,
	.vdev_get_keepalive_cmdid = WMI_10_4_VDEV_GET_KEEPALIVE_CMDID,
	.क्रमce_fw_hang_cmdid = WMI_10_4_FORCE_FW_HANG_CMDID,
	.gpio_config_cmdid = WMI_10_4_GPIO_CONFIG_CMDID,
	.gpio_output_cmdid = WMI_10_4_GPIO_OUTPUT_CMDID,
	.pdev_get_temperature_cmdid = WMI_10_4_PDEV_GET_TEMPERATURE_CMDID,
	.vdev_set_wmm_params_cmdid = WMI_CMD_UNSUPPORTED,
	.adaptive_qcs_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_update_request_cmdid = WMI_10_4_SCAN_UPDATE_REQUEST_CMDID,
	.vdev_standby_response_cmdid = WMI_10_4_VDEV_STANDBY_RESPONSE_CMDID,
	.vdev_resume_response_cmdid = WMI_10_4_VDEV_RESUME_RESPONSE_CMDID,
	.wlan_peer_caching_add_peer_cmdid =
			WMI_10_4_WLAN_PEER_CACHING_ADD_PEER_CMDID,
	.wlan_peer_caching_evict_peer_cmdid =
			WMI_10_4_WLAN_PEER_CACHING_EVICT_PEER_CMDID,
	.wlan_peer_caching_restore_peer_cmdid =
			WMI_10_4_WLAN_PEER_CACHING_RESTORE_PEER_CMDID,
	.wlan_peer_caching_prपूर्णांक_all_peers_info_cmdid =
			WMI_10_4_WLAN_PEER_CACHING_PRINT_ALL_PEERS_INFO_CMDID,
	.peer_update_wds_entry_cmdid = WMI_10_4_PEER_UPDATE_WDS_ENTRY_CMDID,
	.peer_add_proxy_sta_entry_cmdid =
			WMI_10_4_PEER_ADD_PROXY_STA_ENTRY_CMDID,
	.rtt_keepalive_cmdid = WMI_10_4_RTT_KEEPALIVE_CMDID,
	.oem_req_cmdid = WMI_10_4_OEM_REQ_CMDID,
	.nan_cmdid = WMI_10_4_न_अंक_CMDID,
	.vdev_ratemask_cmdid = WMI_10_4_VDEV_RATEMASK_CMDID,
	.qboost_cfg_cmdid = WMI_10_4_QBOOST_CFG_CMDID,
	.pdev_smart_ant_enable_cmdid = WMI_10_4_PDEV_SMART_ANT_ENABLE_CMDID,
	.pdev_smart_ant_set_rx_antenna_cmdid =
			WMI_10_4_PDEV_SMART_ANT_SET_RX_ANTENNA_CMDID,
	.peer_smart_ant_set_tx_antenna_cmdid =
			WMI_10_4_PEER_SMART_ANT_SET_TX_ANTENNA_CMDID,
	.peer_smart_ant_set_train_info_cmdid =
			WMI_10_4_PEER_SMART_ANT_SET_TRAIN_INFO_CMDID,
	.peer_smart_ant_set_node_config_ops_cmdid =
			WMI_10_4_PEER_SMART_ANT_SET_NODE_CONFIG_OPS_CMDID,
	.pdev_set_antenna_चयन_table_cmdid =
			WMI_10_4_PDEV_SET_ANTENNA_SWITCH_TABLE_CMDID,
	.pdev_set_ctl_table_cmdid = WMI_10_4_PDEV_SET_CTL_TABLE_CMDID,
	.pdev_set_mimogain_table_cmdid = WMI_10_4_PDEV_SET_MIMOGAIN_TABLE_CMDID,
	.pdev_ratepwr_table_cmdid = WMI_10_4_PDEV_RATEPWR_TABLE_CMDID,
	.pdev_ratepwr_chainmsk_table_cmdid =
			WMI_10_4_PDEV_RATEPWR_CHAINMSK_TABLE_CMDID,
	.pdev_fips_cmdid = WMI_10_4_PDEV_FIPS_CMDID,
	.tt_set_conf_cmdid = WMI_10_4_TT_SET_CONF_CMDID,
	.fwtest_cmdid = WMI_10_4_FWTEST_CMDID,
	.vdev_atf_request_cmdid = WMI_10_4_VDEV_ATF_REQUEST_CMDID,
	.peer_atf_request_cmdid = WMI_10_4_PEER_ATF_REQUEST_CMDID,
	.pdev_get_ani_cck_config_cmdid = WMI_10_4_PDEV_GET_ANI_CCK_CONFIG_CMDID,
	.pdev_get_ani_ofdm_config_cmdid =
			WMI_10_4_PDEV_GET_ANI_OFDM_CONFIG_CMDID,
	.pdev_reserve_ast_entry_cmdid = WMI_10_4_PDEV_RESERVE_AST_ENTRY_CMDID,
	.pdev_get_nfcal_घातer_cmdid = WMI_10_4_PDEV_GET_NFCAL_POWER_CMDID,
	.pdev_get_tpc_cmdid = WMI_10_4_PDEV_GET_TPC_CMDID,
	.pdev_get_ast_info_cmdid = WMI_10_4_PDEV_GET_AST_INFO_CMDID,
	.vdev_set_dscp_tid_map_cmdid = WMI_10_4_VDEV_SET_DSCP_TID_MAP_CMDID,
	.pdev_get_info_cmdid = WMI_10_4_PDEV_GET_INFO_CMDID,
	.vdev_get_info_cmdid = WMI_10_4_VDEV_GET_INFO_CMDID,
	.vdev_filter_neighbor_rx_packets_cmdid =
			WMI_10_4_VDEV_FILTER_NEIGHBOR_RX_PACKETS_CMDID,
	.mu_cal_start_cmdid = WMI_10_4_MU_CAL_START_CMDID,
	.set_cca_params_cmdid = WMI_10_4_SET_CCA_PARAMS_CMDID,
	.pdev_bss_chan_info_request_cmdid =
			WMI_10_4_PDEV_BSS_CHAN_INFO_REQUEST_CMDID,
	.ext_resource_cfg_cmdid = WMI_10_4_EXT_RESOURCE_CFG_CMDID,
	.vdev_set_ie_cmdid = WMI_10_4_VDEV_SET_IE_CMDID,
	.set_lteu_config_cmdid = WMI_10_4_SET_LTEU_CONFIG_CMDID,
	.atf_ssid_grouping_request_cmdid =
			WMI_10_4_ATF_SSID_GROUPING_REQUEST_CMDID,
	.peer_atf_ext_request_cmdid = WMI_10_4_PEER_ATF_EXT_REQUEST_CMDID,
	.set_periodic_channel_stats_cfg_cmdid =
			WMI_10_4_SET_PERIODIC_CHANNEL_STATS_CONFIG,
	.peer_bwf_request_cmdid = WMI_10_4_PEER_BWF_REQUEST_CMDID,
	.btcoex_cfg_cmdid = WMI_10_4_BTCOEX_CFG_CMDID,
	.peer_tx_mu_txmit_count_cmdid = WMI_10_4_PEER_TX_MU_TXMIT_COUNT_CMDID,
	.peer_tx_mu_txmit_rstcnt_cmdid = WMI_10_4_PEER_TX_MU_TXMIT_RSTCNT_CMDID,
	.peer_gid_userpos_list_cmdid = WMI_10_4_PEER_GID_USERPOS_LIST_CMDID,
	.pdev_check_cal_version_cmdid = WMI_10_4_PDEV_CHECK_CAL_VERSION_CMDID,
	.coex_version_cfg_cmid = WMI_10_4_COEX_VERSION_CFG_CMID,
	.pdev_get_rx_filter_cmdid = WMI_10_4_PDEV_GET_RX_FILTER_CMDID,
	.pdev_extended_nss_cfg_cmdid = WMI_10_4_PDEV_EXTENDED_NSS_CFG_CMDID,
	.vdev_set_scan_nac_rssi_cmdid = WMI_10_4_VDEV_SET_SCAN_NAC_RSSI_CMDID,
	.prog_gpio_band_select_cmdid = WMI_10_4_PROG_GPIO_BAND_SELECT_CMDID,
	.config_smart_logging_cmdid = WMI_10_4_CONFIG_SMART_LOGGING_CMDID,
	.debug_fatal_condition_cmdid = WMI_10_4_DEBUG_FATAL_CONDITION_CMDID,
	.get_tsf_समयr_cmdid = WMI_10_4_GET_TSF_TIMER_CMDID,
	.pdev_get_tpc_table_cmdid = WMI_10_4_PDEV_GET_TPC_TABLE_CMDID,
	.vdev_sअगरs_trigger_समय_cmdid = WMI_10_4_VDEV_SIFS_TRIGGER_TIME_CMDID,
	.pdev_wds_entry_list_cmdid = WMI_10_4_PDEV_WDS_ENTRY_LIST_CMDID,
	.tdls_set_state_cmdid = WMI_10_4_TDLS_SET_STATE_CMDID,
	.tdls_peer_update_cmdid = WMI_10_4_TDLS_PEER_UPDATE_CMDID,
	.tdls_set_offchan_mode_cmdid = WMI_10_4_TDLS_SET_OFFCHAN_MODE_CMDID,
	.radar_found_cmdid = WMI_10_4_RADAR_FOUND_CMDID,
	.per_peer_per_tid_config_cmdid = WMI_10_4_PER_PEER_PER_TID_CONFIG_CMDID,
पूर्ण;

अटल काष्ठा wmi_peer_param_map wmi_peer_param_map = अणु
	.smps_state = WMI_PEER_SMPS_STATE,
	.ampdu = WMI_PEER_AMPDU,
	.authorize = WMI_PEER_AUTHORIZE,
	.chan_width = WMI_PEER_CHAN_WIDTH,
	.nss = WMI_PEER_NSS,
	.use_4addr = WMI_PEER_USE_4ADDR,
	.use_fixed_घातer = WMI_PEER_USE_FIXED_PWR,
	.debug = WMI_PEER_DEBUG,
	.phymode = WMI_PEER_PHYMODE,
	.dummy_var = WMI_PEER_DUMMY_VAR,
पूर्ण;

/* MAIN WMI VDEV param map */
अटल काष्ठा wmi_vdev_param_map wmi_vdev_param_map = अणु
	.rts_threshold = WMI_VDEV_PARAM_RTS_THRESHOLD,
	.fragmentation_threshold = WMI_VDEV_PARAM_FRAGMENTATION_THRESHOLD,
	.beacon_पूर्णांकerval = WMI_VDEV_PARAM_BEACON_INTERVAL,
	.listen_पूर्णांकerval = WMI_VDEV_PARAM_LISTEN_INTERVAL,
	.multicast_rate = WMI_VDEV_PARAM_MULTICAST_RATE,
	.mgmt_tx_rate = WMI_VDEV_PARAM_MGMT_TX_RATE,
	.slot_समय = WMI_VDEV_PARAM_SLOT_TIME,
	.preamble = WMI_VDEV_PARAM_PREAMBLE,
	.swba_समय = WMI_VDEV_PARAM_SWBA_TIME,
	.wmi_vdev_stats_update_period = WMI_VDEV_STATS_UPDATE_PERIOD,
	.wmi_vdev_pwrsave_ageout_समय = WMI_VDEV_PWRSAVE_AGEOUT_TIME,
	.wmi_vdev_host_swba_पूर्णांकerval = WMI_VDEV_HOST_SWBA_INTERVAL,
	.dtim_period = WMI_VDEV_PARAM_DTIM_PERIOD,
	.wmi_vdev_oc_scheduler_air_समय_limit =
					WMI_VDEV_OC_SCHEDULER_AIR_TIME_LIMIT,
	.wds = WMI_VDEV_PARAM_WDS,
	.atim_winकरोw = WMI_VDEV_PARAM_ATIM_WINDOW,
	.bmiss_count_max = WMI_VDEV_PARAM_BMISS_COUNT_MAX,
	.bmiss_first_bcnt = WMI_VDEV_PARAM_BMISS_FIRST_BCNT,
	.bmiss_final_bcnt = WMI_VDEV_PARAM_BMISS_FINAL_BCNT,
	.feature_wmm = WMI_VDEV_PARAM_FEATURE_WMM,
	.chwidth = WMI_VDEV_PARAM_CHWIDTH,
	.chextoffset = WMI_VDEV_PARAM_CHEXTOFFSET,
	.disable_htprotection =	WMI_VDEV_PARAM_DISABLE_HTPROTECTION,
	.sta_quickkickout = WMI_VDEV_PARAM_STA_QUICKKICKOUT,
	.mgmt_rate = WMI_VDEV_PARAM_MGMT_RATE,
	.protection_mode = WMI_VDEV_PARAM_PROTECTION_MODE,
	.fixed_rate = WMI_VDEV_PARAM_FIXED_RATE,
	.sgi = WMI_VDEV_PARAM_SGI,
	.ldpc = WMI_VDEV_PARAM_LDPC,
	.tx_stbc = WMI_VDEV_PARAM_TX_STBC,
	.rx_stbc = WMI_VDEV_PARAM_RX_STBC,
	.पूर्णांकra_bss_fwd = WMI_VDEV_PARAM_INTRA_BSS_FWD,
	.def_keyid = WMI_VDEV_PARAM_DEF_KEYID,
	.nss = WMI_VDEV_PARAM_NSS,
	.bcast_data_rate = WMI_VDEV_PARAM_BCAST_DATA_RATE,
	.mcast_data_rate = WMI_VDEV_PARAM_MCAST_DATA_RATE,
	.mcast_indicate = WMI_VDEV_PARAM_MCAST_INDICATE,
	.dhcp_indicate = WMI_VDEV_PARAM_DHCP_INDICATE,
	.unknown_dest_indicate = WMI_VDEV_PARAM_UNKNOWN_DEST_INDICATE,
	.ap_keepalive_min_idle_inactive_समय_secs =
			WMI_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_idle_inactive_समय_secs =
			WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_unresponsive_समय_secs =
			WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS,
	.ap_enable_nawds = WMI_VDEV_PARAM_AP_ENABLE_NAWDS,
	.mcast2ucast_set = WMI_VDEV_PARAM_UNSUPPORTED,
	.enable_rtscts = WMI_VDEV_PARAM_ENABLE_RTSCTS,
	.txbf = WMI_VDEV_PARAM_TXBF,
	.packet_घातersave = WMI_VDEV_PARAM_PACKET_POWERSAVE,
	.drop_unencry = WMI_VDEV_PARAM_DROP_UNENCRY,
	.tx_encap_type = WMI_VDEV_PARAM_TX_ENCAP_TYPE,
	.ap_detect_out_of_sync_sleeping_sta_समय_secs =
					WMI_VDEV_PARAM_UNSUPPORTED,
	.rc_num_retries = WMI_VDEV_PARAM_UNSUPPORTED,
	.cabq_maxdur = WMI_VDEV_PARAM_UNSUPPORTED,
	.mfptest_set = WMI_VDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht_sgimask = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht80_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_enable = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_tgt_bmiss_num = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_bmiss_sample_cycle = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_slop_step = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_init_slop = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_छोड़ो = WMI_VDEV_PARAM_UNSUPPORTED,
	.proxy_sta = WMI_VDEV_PARAM_UNSUPPORTED,
	.meru_vc = WMI_VDEV_PARAM_UNSUPPORTED,
	.rx_decap_type = WMI_VDEV_PARAM_UNSUPPORTED,
	.bw_nss_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.disable_4addr_src_lrn = WMI_VDEV_PARAM_UNSUPPORTED,
	.rtt_responder_role = WMI_VDEV_PARAM_UNSUPPORTED,
पूर्ण;

/* 10.X WMI VDEV param map */
अटल काष्ठा wmi_vdev_param_map wmi_10x_vdev_param_map = अणु
	.rts_threshold = WMI_10X_VDEV_PARAM_RTS_THRESHOLD,
	.fragmentation_threshold = WMI_10X_VDEV_PARAM_FRAGMENTATION_THRESHOLD,
	.beacon_पूर्णांकerval = WMI_10X_VDEV_PARAM_BEACON_INTERVAL,
	.listen_पूर्णांकerval = WMI_10X_VDEV_PARAM_LISTEN_INTERVAL,
	.multicast_rate = WMI_10X_VDEV_PARAM_MULTICAST_RATE,
	.mgmt_tx_rate = WMI_10X_VDEV_PARAM_MGMT_TX_RATE,
	.slot_समय = WMI_10X_VDEV_PARAM_SLOT_TIME,
	.preamble = WMI_10X_VDEV_PARAM_PREAMBLE,
	.swba_समय = WMI_10X_VDEV_PARAM_SWBA_TIME,
	.wmi_vdev_stats_update_period = WMI_10X_VDEV_STATS_UPDATE_PERIOD,
	.wmi_vdev_pwrsave_ageout_समय = WMI_10X_VDEV_PWRSAVE_AGEOUT_TIME,
	.wmi_vdev_host_swba_पूर्णांकerval = WMI_10X_VDEV_HOST_SWBA_INTERVAL,
	.dtim_period = WMI_10X_VDEV_PARAM_DTIM_PERIOD,
	.wmi_vdev_oc_scheduler_air_समय_limit =
				WMI_10X_VDEV_OC_SCHEDULER_AIR_TIME_LIMIT,
	.wds = WMI_10X_VDEV_PARAM_WDS,
	.atim_winकरोw = WMI_10X_VDEV_PARAM_ATIM_WINDOW,
	.bmiss_count_max = WMI_10X_VDEV_PARAM_BMISS_COUNT_MAX,
	.bmiss_first_bcnt = WMI_VDEV_PARAM_UNSUPPORTED,
	.bmiss_final_bcnt = WMI_VDEV_PARAM_UNSUPPORTED,
	.feature_wmm = WMI_10X_VDEV_PARAM_FEATURE_WMM,
	.chwidth = WMI_10X_VDEV_PARAM_CHWIDTH,
	.chextoffset = WMI_10X_VDEV_PARAM_CHEXTOFFSET,
	.disable_htprotection = WMI_10X_VDEV_PARAM_DISABLE_HTPROTECTION,
	.sta_quickkickout = WMI_10X_VDEV_PARAM_STA_QUICKKICKOUT,
	.mgmt_rate = WMI_10X_VDEV_PARAM_MGMT_RATE,
	.protection_mode = WMI_10X_VDEV_PARAM_PROTECTION_MODE,
	.fixed_rate = WMI_10X_VDEV_PARAM_FIXED_RATE,
	.sgi = WMI_10X_VDEV_PARAM_SGI,
	.ldpc = WMI_10X_VDEV_PARAM_LDPC,
	.tx_stbc = WMI_10X_VDEV_PARAM_TX_STBC,
	.rx_stbc = WMI_10X_VDEV_PARAM_RX_STBC,
	.पूर्णांकra_bss_fwd = WMI_10X_VDEV_PARAM_INTRA_BSS_FWD,
	.def_keyid = WMI_10X_VDEV_PARAM_DEF_KEYID,
	.nss = WMI_10X_VDEV_PARAM_NSS,
	.bcast_data_rate = WMI_10X_VDEV_PARAM_BCAST_DATA_RATE,
	.mcast_data_rate = WMI_10X_VDEV_PARAM_MCAST_DATA_RATE,
	.mcast_indicate = WMI_10X_VDEV_PARAM_MCAST_INDICATE,
	.dhcp_indicate = WMI_10X_VDEV_PARAM_DHCP_INDICATE,
	.unknown_dest_indicate = WMI_10X_VDEV_PARAM_UNKNOWN_DEST_INDICATE,
	.ap_keepalive_min_idle_inactive_समय_secs =
		WMI_10X_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_idle_inactive_समय_secs =
		WMI_10X_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_unresponsive_समय_secs =
		WMI_10X_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS,
	.ap_enable_nawds = WMI_10X_VDEV_PARAM_AP_ENABLE_NAWDS,
	.mcast2ucast_set = WMI_10X_VDEV_PARAM_MCAST2UCAST_SET,
	.enable_rtscts = WMI_10X_VDEV_PARAM_ENABLE_RTSCTS,
	.txbf = WMI_VDEV_PARAM_UNSUPPORTED,
	.packet_घातersave = WMI_VDEV_PARAM_UNSUPPORTED,
	.drop_unencry = WMI_VDEV_PARAM_UNSUPPORTED,
	.tx_encap_type = WMI_VDEV_PARAM_UNSUPPORTED,
	.ap_detect_out_of_sync_sleeping_sta_समय_secs =
		WMI_10X_VDEV_PARAM_AP_DETECT_OUT_OF_SYNC_SLEEPING_STA_TIME_SECS,
	.rc_num_retries = WMI_VDEV_PARAM_UNSUPPORTED,
	.cabq_maxdur = WMI_VDEV_PARAM_UNSUPPORTED,
	.mfptest_set = WMI_VDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht_sgimask = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht80_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_enable = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_tgt_bmiss_num = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_bmiss_sample_cycle = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_slop_step = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_init_slop = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_छोड़ो = WMI_VDEV_PARAM_UNSUPPORTED,
	.proxy_sta = WMI_VDEV_PARAM_UNSUPPORTED,
	.meru_vc = WMI_VDEV_PARAM_UNSUPPORTED,
	.rx_decap_type = WMI_VDEV_PARAM_UNSUPPORTED,
	.bw_nss_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.disable_4addr_src_lrn = WMI_VDEV_PARAM_UNSUPPORTED,
	.rtt_responder_role = WMI_VDEV_PARAM_UNSUPPORTED,
पूर्ण;

अटल काष्ठा wmi_vdev_param_map wmi_10_2_4_vdev_param_map = अणु
	.rts_threshold = WMI_10X_VDEV_PARAM_RTS_THRESHOLD,
	.fragmentation_threshold = WMI_10X_VDEV_PARAM_FRAGMENTATION_THRESHOLD,
	.beacon_पूर्णांकerval = WMI_10X_VDEV_PARAM_BEACON_INTERVAL,
	.listen_पूर्णांकerval = WMI_10X_VDEV_PARAM_LISTEN_INTERVAL,
	.multicast_rate = WMI_10X_VDEV_PARAM_MULTICAST_RATE,
	.mgmt_tx_rate = WMI_10X_VDEV_PARAM_MGMT_TX_RATE,
	.slot_समय = WMI_10X_VDEV_PARAM_SLOT_TIME,
	.preamble = WMI_10X_VDEV_PARAM_PREAMBLE,
	.swba_समय = WMI_10X_VDEV_PARAM_SWBA_TIME,
	.wmi_vdev_stats_update_period = WMI_10X_VDEV_STATS_UPDATE_PERIOD,
	.wmi_vdev_pwrsave_ageout_समय = WMI_10X_VDEV_PWRSAVE_AGEOUT_TIME,
	.wmi_vdev_host_swba_पूर्णांकerval = WMI_10X_VDEV_HOST_SWBA_INTERVAL,
	.dtim_period = WMI_10X_VDEV_PARAM_DTIM_PERIOD,
	.wmi_vdev_oc_scheduler_air_समय_limit =
				WMI_10X_VDEV_OC_SCHEDULER_AIR_TIME_LIMIT,
	.wds = WMI_10X_VDEV_PARAM_WDS,
	.atim_winकरोw = WMI_10X_VDEV_PARAM_ATIM_WINDOW,
	.bmiss_count_max = WMI_10X_VDEV_PARAM_BMISS_COUNT_MAX,
	.bmiss_first_bcnt = WMI_VDEV_PARAM_UNSUPPORTED,
	.bmiss_final_bcnt = WMI_VDEV_PARAM_UNSUPPORTED,
	.feature_wmm = WMI_10X_VDEV_PARAM_FEATURE_WMM,
	.chwidth = WMI_10X_VDEV_PARAM_CHWIDTH,
	.chextoffset = WMI_10X_VDEV_PARAM_CHEXTOFFSET,
	.disable_htprotection = WMI_10X_VDEV_PARAM_DISABLE_HTPROTECTION,
	.sta_quickkickout = WMI_10X_VDEV_PARAM_STA_QUICKKICKOUT,
	.mgmt_rate = WMI_10X_VDEV_PARAM_MGMT_RATE,
	.protection_mode = WMI_10X_VDEV_PARAM_PROTECTION_MODE,
	.fixed_rate = WMI_10X_VDEV_PARAM_FIXED_RATE,
	.sgi = WMI_10X_VDEV_PARAM_SGI,
	.ldpc = WMI_10X_VDEV_PARAM_LDPC,
	.tx_stbc = WMI_10X_VDEV_PARAM_TX_STBC,
	.rx_stbc = WMI_10X_VDEV_PARAM_RX_STBC,
	.पूर्णांकra_bss_fwd = WMI_10X_VDEV_PARAM_INTRA_BSS_FWD,
	.def_keyid = WMI_10X_VDEV_PARAM_DEF_KEYID,
	.nss = WMI_10X_VDEV_PARAM_NSS,
	.bcast_data_rate = WMI_10X_VDEV_PARAM_BCAST_DATA_RATE,
	.mcast_data_rate = WMI_10X_VDEV_PARAM_MCAST_DATA_RATE,
	.mcast_indicate = WMI_10X_VDEV_PARAM_MCAST_INDICATE,
	.dhcp_indicate = WMI_10X_VDEV_PARAM_DHCP_INDICATE,
	.unknown_dest_indicate = WMI_10X_VDEV_PARAM_UNKNOWN_DEST_INDICATE,
	.ap_keepalive_min_idle_inactive_समय_secs =
		WMI_10X_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_idle_inactive_समय_secs =
		WMI_10X_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_unresponsive_समय_secs =
		WMI_10X_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS,
	.ap_enable_nawds = WMI_10X_VDEV_PARAM_AP_ENABLE_NAWDS,
	.mcast2ucast_set = WMI_10X_VDEV_PARAM_MCAST2UCAST_SET,
	.enable_rtscts = WMI_10X_VDEV_PARAM_ENABLE_RTSCTS,
	.txbf = WMI_VDEV_PARAM_UNSUPPORTED,
	.packet_घातersave = WMI_VDEV_PARAM_UNSUPPORTED,
	.drop_unencry = WMI_VDEV_PARAM_UNSUPPORTED,
	.tx_encap_type = WMI_VDEV_PARAM_UNSUPPORTED,
	.ap_detect_out_of_sync_sleeping_sta_समय_secs =
		WMI_10X_VDEV_PARAM_AP_DETECT_OUT_OF_SYNC_SLEEPING_STA_TIME_SECS,
	.rc_num_retries = WMI_VDEV_PARAM_UNSUPPORTED,
	.cabq_maxdur = WMI_VDEV_PARAM_UNSUPPORTED,
	.mfptest_set = WMI_VDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht_sgimask = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht80_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_enable = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_tgt_bmiss_num = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_bmiss_sample_cycle = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_slop_step = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_init_slop = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_छोड़ो = WMI_VDEV_PARAM_UNSUPPORTED,
	.proxy_sta = WMI_VDEV_PARAM_UNSUPPORTED,
	.meru_vc = WMI_VDEV_PARAM_UNSUPPORTED,
	.rx_decap_type = WMI_VDEV_PARAM_UNSUPPORTED,
	.bw_nss_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.disable_4addr_src_lrn = WMI_VDEV_PARAM_UNSUPPORTED,
	.rtt_responder_role = WMI_VDEV_PARAM_UNSUPPORTED,
पूर्ण;

अटल काष्ठा wmi_vdev_param_map wmi_10_4_vdev_param_map = अणु
	.rts_threshold = WMI_10_4_VDEV_PARAM_RTS_THRESHOLD,
	.fragmentation_threshold = WMI_10_4_VDEV_PARAM_FRAGMENTATION_THRESHOLD,
	.beacon_पूर्णांकerval = WMI_10_4_VDEV_PARAM_BEACON_INTERVAL,
	.listen_पूर्णांकerval = WMI_10_4_VDEV_PARAM_LISTEN_INTERVAL,
	.multicast_rate = WMI_10_4_VDEV_PARAM_MULTICAST_RATE,
	.mgmt_tx_rate = WMI_10_4_VDEV_PARAM_MGMT_TX_RATE,
	.slot_समय = WMI_10_4_VDEV_PARAM_SLOT_TIME,
	.preamble = WMI_10_4_VDEV_PARAM_PREAMBLE,
	.swba_समय = WMI_10_4_VDEV_PARAM_SWBA_TIME,
	.wmi_vdev_stats_update_period = WMI_10_4_VDEV_STATS_UPDATE_PERIOD,
	.wmi_vdev_pwrsave_ageout_समय = WMI_10_4_VDEV_PWRSAVE_AGEOUT_TIME,
	.wmi_vdev_host_swba_पूर्णांकerval = WMI_10_4_VDEV_HOST_SWBA_INTERVAL,
	.dtim_period = WMI_10_4_VDEV_PARAM_DTIM_PERIOD,
	.wmi_vdev_oc_scheduler_air_समय_limit =
	       WMI_10_4_VDEV_OC_SCHEDULER_AIR_TIME_LIMIT,
	.wds = WMI_10_4_VDEV_PARAM_WDS,
	.atim_winकरोw = WMI_10_4_VDEV_PARAM_ATIM_WINDOW,
	.bmiss_count_max = WMI_10_4_VDEV_PARAM_BMISS_COUNT_MAX,
	.bmiss_first_bcnt = WMI_10_4_VDEV_PARAM_BMISS_FIRST_BCNT,
	.bmiss_final_bcnt = WMI_10_4_VDEV_PARAM_BMISS_FINAL_BCNT,
	.feature_wmm = WMI_10_4_VDEV_PARAM_FEATURE_WMM,
	.chwidth = WMI_10_4_VDEV_PARAM_CHWIDTH,
	.chextoffset = WMI_10_4_VDEV_PARAM_CHEXTOFFSET,
	.disable_htprotection = WMI_10_4_VDEV_PARAM_DISABLE_HTPROTECTION,
	.sta_quickkickout = WMI_10_4_VDEV_PARAM_STA_QUICKKICKOUT,
	.mgmt_rate = WMI_10_4_VDEV_PARAM_MGMT_RATE,
	.protection_mode = WMI_10_4_VDEV_PARAM_PROTECTION_MODE,
	.fixed_rate = WMI_10_4_VDEV_PARAM_FIXED_RATE,
	.sgi = WMI_10_4_VDEV_PARAM_SGI,
	.ldpc = WMI_10_4_VDEV_PARAM_LDPC,
	.tx_stbc = WMI_10_4_VDEV_PARAM_TX_STBC,
	.rx_stbc = WMI_10_4_VDEV_PARAM_RX_STBC,
	.पूर्णांकra_bss_fwd = WMI_10_4_VDEV_PARAM_INTRA_BSS_FWD,
	.def_keyid = WMI_10_4_VDEV_PARAM_DEF_KEYID,
	.nss = WMI_10_4_VDEV_PARAM_NSS,
	.bcast_data_rate = WMI_10_4_VDEV_PARAM_BCAST_DATA_RATE,
	.mcast_data_rate = WMI_10_4_VDEV_PARAM_MCAST_DATA_RATE,
	.mcast_indicate = WMI_10_4_VDEV_PARAM_MCAST_INDICATE,
	.dhcp_indicate = WMI_10_4_VDEV_PARAM_DHCP_INDICATE,
	.unknown_dest_indicate = WMI_10_4_VDEV_PARAM_UNKNOWN_DEST_INDICATE,
	.ap_keepalive_min_idle_inactive_समय_secs =
	       WMI_10_4_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_idle_inactive_समय_secs =
	       WMI_10_4_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_unresponsive_समय_secs =
	       WMI_10_4_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS,
	.ap_enable_nawds = WMI_10_4_VDEV_PARAM_AP_ENABLE_NAWDS,
	.mcast2ucast_set = WMI_10_4_VDEV_PARAM_MCAST2UCAST_SET,
	.enable_rtscts = WMI_10_4_VDEV_PARAM_ENABLE_RTSCTS,
	.txbf = WMI_10_4_VDEV_PARAM_TXBF,
	.packet_घातersave = WMI_10_4_VDEV_PARAM_PACKET_POWERSAVE,
	.drop_unencry = WMI_10_4_VDEV_PARAM_DROP_UNENCRY,
	.tx_encap_type = WMI_10_4_VDEV_PARAM_TX_ENCAP_TYPE,
	.ap_detect_out_of_sync_sleeping_sta_समय_secs =
	       WMI_10_4_VDEV_PARAM_AP_DETECT_OUT_OF_SYNC_SLEEPING_STA_TIME_SECS,
	.rc_num_retries = WMI_10_4_VDEV_PARAM_RC_NUM_RETRIES,
	.cabq_maxdur = WMI_10_4_VDEV_PARAM_CABQ_MAXDUR,
	.mfptest_set = WMI_10_4_VDEV_PARAM_MFPTEST_SET,
	.rts_fixed_rate = WMI_10_4_VDEV_PARAM_RTS_FIXED_RATE,
	.vht_sgimask = WMI_10_4_VDEV_PARAM_VHT_SGIMASK,
	.vht80_ratemask = WMI_10_4_VDEV_PARAM_VHT80_RATEMASK,
	.early_rx_adjust_enable = WMI_10_4_VDEV_PARAM_EARLY_RX_ADJUST_ENABLE,
	.early_rx_tgt_bmiss_num = WMI_10_4_VDEV_PARAM_EARLY_RX_TGT_BMISS_NUM,
	.early_rx_bmiss_sample_cycle =
	       WMI_10_4_VDEV_PARAM_EARLY_RX_BMISS_SAMPLE_CYCLE,
	.early_rx_slop_step = WMI_10_4_VDEV_PARAM_EARLY_RX_SLOP_STEP,
	.early_rx_init_slop = WMI_10_4_VDEV_PARAM_EARLY_RX_INIT_SLOP,
	.early_rx_adjust_छोड़ो = WMI_10_4_VDEV_PARAM_EARLY_RX_ADJUST_PAUSE,
	.proxy_sta = WMI_10_4_VDEV_PARAM_PROXY_STA,
	.meru_vc = WMI_10_4_VDEV_PARAM_MERU_VC,
	.rx_decap_type = WMI_10_4_VDEV_PARAM_RX_DECAP_TYPE,
	.bw_nss_ratemask = WMI_10_4_VDEV_PARAM_BW_NSS_RATEMASK,
	.inc_tsf = WMI_10_4_VDEV_PARAM_TSF_INCREMENT,
	.dec_tsf = WMI_10_4_VDEV_PARAM_TSF_DECREMENT,
	.disable_4addr_src_lrn = WMI_10_4_VDEV_PARAM_DISABLE_4_ADDR_SRC_LRN,
	.rtt_responder_role = WMI_10_4_VDEV_PARAM_ENABLE_DISABLE_RTT_RESPONDER_ROLE,
पूर्ण;

अटल काष्ठा wmi_pdev_param_map wmi_pdev_param_map = अणु
	.tx_chain_mask = WMI_PDEV_PARAM_TX_CHAIN_MASK,
	.rx_chain_mask = WMI_PDEV_PARAM_RX_CHAIN_MASK,
	.txघातer_limit2g = WMI_PDEV_PARAM_TXPOWER_LIMIT2G,
	.txघातer_limit5g = WMI_PDEV_PARAM_TXPOWER_LIMIT5G,
	.txघातer_scale = WMI_PDEV_PARAM_TXPOWER_SCALE,
	.beacon_gen_mode = WMI_PDEV_PARAM_BEACON_GEN_MODE,
	.beacon_tx_mode = WMI_PDEV_PARAM_BEACON_TX_MODE,
	.resmgr_offchan_mode = WMI_PDEV_PARAM_RESMGR_OFFCHAN_MODE,
	.protection_mode = WMI_PDEV_PARAM_PROTECTION_MODE,
	.dynamic_bw = WMI_PDEV_PARAM_DYNAMIC_BW,
	.non_agg_sw_retry_th = WMI_PDEV_PARAM_NON_AGG_SW_RETRY_TH,
	.agg_sw_retry_th = WMI_PDEV_PARAM_AGG_SW_RETRY_TH,
	.sta_kickout_th = WMI_PDEV_PARAM_STA_KICKOUT_TH,
	.ac_aggrsize_scaling = WMI_PDEV_PARAM_AC_AGGRSIZE_SCALING,
	.ltr_enable = WMI_PDEV_PARAM_LTR_ENABLE,
	.ltr_ac_latency_be = WMI_PDEV_PARAM_LTR_AC_LATENCY_BE,
	.ltr_ac_latency_bk = WMI_PDEV_PARAM_LTR_AC_LATENCY_BK,
	.ltr_ac_latency_vi = WMI_PDEV_PARAM_LTR_AC_LATENCY_VI,
	.ltr_ac_latency_vo = WMI_PDEV_PARAM_LTR_AC_LATENCY_VO,
	.ltr_ac_latency_समयout = WMI_PDEV_PARAM_LTR_AC_LATENCY_TIMEOUT,
	.ltr_sleep_override = WMI_PDEV_PARAM_LTR_SLEEP_OVERRIDE,
	.ltr_rx_override = WMI_PDEV_PARAM_LTR_RX_OVERRIDE,
	.ltr_tx_activity_समयout = WMI_PDEV_PARAM_LTR_TX_ACTIVITY_TIMEOUT,
	.l1ss_enable = WMI_PDEV_PARAM_L1SS_ENABLE,
	.dsleep_enable = WMI_PDEV_PARAM_DSLEEP_ENABLE,
	.pcielp_txbuf_flush = WMI_PDEV_PARAM_PCIELP_TXBUF_FLUSH,
	.pcielp_txbuf_watermark = WMI_PDEV_PARAM_PCIELP_TXBUF_TMO_EN,
	.pcielp_txbuf_पंचांगo_en = WMI_PDEV_PARAM_PCIELP_TXBUF_TMO_EN,
	.pcielp_txbuf_पंचांगo_value = WMI_PDEV_PARAM_PCIELP_TXBUF_TMO_VALUE,
	.pdev_stats_update_period = WMI_PDEV_PARAM_PDEV_STATS_UPDATE_PERIOD,
	.vdev_stats_update_period = WMI_PDEV_PARAM_VDEV_STATS_UPDATE_PERIOD,
	.peer_stats_update_period = WMI_PDEV_PARAM_PEER_STATS_UPDATE_PERIOD,
	.bcnflt_stats_update_period = WMI_PDEV_PARAM_BCNFLT_STATS_UPDATE_PERIOD,
	.pmf_qos = WMI_PDEV_PARAM_PMF_QOS,
	.arp_ac_override = WMI_PDEV_PARAM_ARP_AC_OVERRIDE,
	.dcs = WMI_PDEV_PARAM_DCS,
	.ani_enable = WMI_PDEV_PARAM_ANI_ENABLE,
	.ani_poll_period = WMI_PDEV_PARAM_ANI_POLL_PERIOD,
	.ani_listen_period = WMI_PDEV_PARAM_ANI_LISTEN_PERIOD,
	.ani_ofdm_level = WMI_PDEV_PARAM_ANI_OFDM_LEVEL,
	.ani_cck_level = WMI_PDEV_PARAM_ANI_CCK_LEVEL,
	.dyntxchain = WMI_PDEV_PARAM_DYNTXCHAIN,
	.proxy_sta = WMI_PDEV_PARAM_PROXY_STA,
	.idle_ps_config = WMI_PDEV_PARAM_IDLE_PS_CONFIG,
	.घातer_gating_sleep = WMI_PDEV_PARAM_POWER_GATING_SLEEP,
	.fast_channel_reset = WMI_PDEV_PARAM_UNSUPPORTED,
	.burst_dur = WMI_PDEV_PARAM_UNSUPPORTED,
	.burst_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.cal_period = WMI_PDEV_PARAM_UNSUPPORTED,
	.aggr_burst = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_decap_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.smart_antenna_शेष_antenna = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.antenna_gain = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_filter = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_to_ucast_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.proxy_sta_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.हटाओ_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.peer_sta_ps_statechg_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_ac_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.block_पूर्णांकerbss = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_disable_reset_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_msdu_ttl_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_ppdu_duration_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.txbf_sound_period_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_promisc_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_burst_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.en_stats = WMI_PDEV_PARAM_UNSUPPORTED,
	.mu_group_policy = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_detection = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.dpd_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_bcast_echo = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_strict_sch = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_sched_duration = WMI_PDEV_PARAM_UNSUPPORTED,
	.ant_plzn = WMI_PDEV_PARAM_UNSUPPORTED,
	.mgmt_retry_limit = WMI_PDEV_PARAM_UNSUPPORTED,
	.sensitivity_level = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_2g = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_5g = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_amsdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_ampdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.cca_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_PDEV_PARAM_UNSUPPORTED,
	.pdev_reset = WMI_PDEV_PARAM_UNSUPPORTED,
	.wapi_mbssid_offset = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_srcaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_dstaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_btcoex = WMI_PDEV_PARAM_UNSUPPORTED,
पूर्ण;

अटल काष्ठा wmi_pdev_param_map wmi_10x_pdev_param_map = अणु
	.tx_chain_mask = WMI_10X_PDEV_PARAM_TX_CHAIN_MASK,
	.rx_chain_mask = WMI_10X_PDEV_PARAM_RX_CHAIN_MASK,
	.txघातer_limit2g = WMI_10X_PDEV_PARAM_TXPOWER_LIMIT2G,
	.txघातer_limit5g = WMI_10X_PDEV_PARAM_TXPOWER_LIMIT5G,
	.txघातer_scale = WMI_10X_PDEV_PARAM_TXPOWER_SCALE,
	.beacon_gen_mode = WMI_10X_PDEV_PARAM_BEACON_GEN_MODE,
	.beacon_tx_mode = WMI_10X_PDEV_PARAM_BEACON_TX_MODE,
	.resmgr_offchan_mode = WMI_10X_PDEV_PARAM_RESMGR_OFFCHAN_MODE,
	.protection_mode = WMI_10X_PDEV_PARAM_PROTECTION_MODE,
	.dynamic_bw = WMI_10X_PDEV_PARAM_DYNAMIC_BW,
	.non_agg_sw_retry_th = WMI_10X_PDEV_PARAM_NON_AGG_SW_RETRY_TH,
	.agg_sw_retry_th = WMI_10X_PDEV_PARAM_AGG_SW_RETRY_TH,
	.sta_kickout_th = WMI_10X_PDEV_PARAM_STA_KICKOUT_TH,
	.ac_aggrsize_scaling = WMI_10X_PDEV_PARAM_AC_AGGRSIZE_SCALING,
	.ltr_enable = WMI_10X_PDEV_PARAM_LTR_ENABLE,
	.ltr_ac_latency_be = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_BE,
	.ltr_ac_latency_bk = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_BK,
	.ltr_ac_latency_vi = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_VI,
	.ltr_ac_latency_vo = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_VO,
	.ltr_ac_latency_समयout = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_TIMEOUT,
	.ltr_sleep_override = WMI_10X_PDEV_PARAM_LTR_SLEEP_OVERRIDE,
	.ltr_rx_override = WMI_10X_PDEV_PARAM_LTR_RX_OVERRIDE,
	.ltr_tx_activity_समयout = WMI_10X_PDEV_PARAM_LTR_TX_ACTIVITY_TIMEOUT,
	.l1ss_enable = WMI_10X_PDEV_PARAM_L1SS_ENABLE,
	.dsleep_enable = WMI_10X_PDEV_PARAM_DSLEEP_ENABLE,
	.pcielp_txbuf_flush = WMI_PDEV_PARAM_UNSUPPORTED,
	.pcielp_txbuf_watermark = WMI_PDEV_PARAM_UNSUPPORTED,
	.pcielp_txbuf_पंचांगo_en = WMI_PDEV_PARAM_UNSUPPORTED,
	.pcielp_txbuf_पंचांगo_value = WMI_PDEV_PARAM_UNSUPPORTED,
	.pdev_stats_update_period = WMI_10X_PDEV_PARAM_PDEV_STATS_UPDATE_PERIOD,
	.vdev_stats_update_period = WMI_10X_PDEV_PARAM_VDEV_STATS_UPDATE_PERIOD,
	.peer_stats_update_period = WMI_10X_PDEV_PARAM_PEER_STATS_UPDATE_PERIOD,
	.bcnflt_stats_update_period =
				WMI_10X_PDEV_PARAM_BCNFLT_STATS_UPDATE_PERIOD,
	.pmf_qos = WMI_10X_PDEV_PARAM_PMF_QOS,
	.arp_ac_override = WMI_10X_PDEV_PARAM_ARPDHCP_AC_OVERRIDE,
	.dcs = WMI_10X_PDEV_PARAM_DCS,
	.ani_enable = WMI_10X_PDEV_PARAM_ANI_ENABLE,
	.ani_poll_period = WMI_10X_PDEV_PARAM_ANI_POLL_PERIOD,
	.ani_listen_period = WMI_10X_PDEV_PARAM_ANI_LISTEN_PERIOD,
	.ani_ofdm_level = WMI_10X_PDEV_PARAM_ANI_OFDM_LEVEL,
	.ani_cck_level = WMI_10X_PDEV_PARAM_ANI_CCK_LEVEL,
	.dyntxchain = WMI_10X_PDEV_PARAM_DYNTXCHAIN,
	.proxy_sta = WMI_PDEV_PARAM_UNSUPPORTED,
	.idle_ps_config = WMI_PDEV_PARAM_UNSUPPORTED,
	.घातer_gating_sleep = WMI_PDEV_PARAM_UNSUPPORTED,
	.fast_channel_reset = WMI_10X_PDEV_PARAM_FAST_CHANNEL_RESET,
	.burst_dur = WMI_10X_PDEV_PARAM_BURST_DUR,
	.burst_enable = WMI_10X_PDEV_PARAM_BURST_ENABLE,
	.cal_period = WMI_10X_PDEV_PARAM_CAL_PERIOD,
	.aggr_burst = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_decap_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.smart_antenna_शेष_antenna = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.antenna_gain = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_filter = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_to_ucast_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.proxy_sta_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.हटाओ_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.peer_sta_ps_statechg_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_ac_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.block_पूर्णांकerbss = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_disable_reset_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_msdu_ttl_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_ppdu_duration_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.txbf_sound_period_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_promisc_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_burst_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.en_stats = WMI_PDEV_PARAM_UNSUPPORTED,
	.mu_group_policy = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_detection = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.dpd_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_bcast_echo = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_strict_sch = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_sched_duration = WMI_PDEV_PARAM_UNSUPPORTED,
	.ant_plzn = WMI_PDEV_PARAM_UNSUPPORTED,
	.mgmt_retry_limit = WMI_PDEV_PARAM_UNSUPPORTED,
	.sensitivity_level = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_2g = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_5g = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_amsdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_ampdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.cca_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_PDEV_PARAM_UNSUPPORTED,
	.pdev_reset = WMI_PDEV_PARAM_UNSUPPORTED,
	.wapi_mbssid_offset = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_srcaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_dstaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_btcoex = WMI_PDEV_PARAM_UNSUPPORTED,
पूर्ण;

अटल काष्ठा wmi_pdev_param_map wmi_10_2_4_pdev_param_map = अणु
	.tx_chain_mask = WMI_10X_PDEV_PARAM_TX_CHAIN_MASK,
	.rx_chain_mask = WMI_10X_PDEV_PARAM_RX_CHAIN_MASK,
	.txघातer_limit2g = WMI_10X_PDEV_PARAM_TXPOWER_LIMIT2G,
	.txघातer_limit5g = WMI_10X_PDEV_PARAM_TXPOWER_LIMIT5G,
	.txघातer_scale = WMI_10X_PDEV_PARAM_TXPOWER_SCALE,
	.beacon_gen_mode = WMI_10X_PDEV_PARAM_BEACON_GEN_MODE,
	.beacon_tx_mode = WMI_10X_PDEV_PARAM_BEACON_TX_MODE,
	.resmgr_offchan_mode = WMI_10X_PDEV_PARAM_RESMGR_OFFCHAN_MODE,
	.protection_mode = WMI_10X_PDEV_PARAM_PROTECTION_MODE,
	.dynamic_bw = WMI_10X_PDEV_PARAM_DYNAMIC_BW,
	.non_agg_sw_retry_th = WMI_10X_PDEV_PARAM_NON_AGG_SW_RETRY_TH,
	.agg_sw_retry_th = WMI_10X_PDEV_PARAM_AGG_SW_RETRY_TH,
	.sta_kickout_th = WMI_10X_PDEV_PARAM_STA_KICKOUT_TH,
	.ac_aggrsize_scaling = WMI_10X_PDEV_PARAM_AC_AGGRSIZE_SCALING,
	.ltr_enable = WMI_10X_PDEV_PARAM_LTR_ENABLE,
	.ltr_ac_latency_be = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_BE,
	.ltr_ac_latency_bk = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_BK,
	.ltr_ac_latency_vi = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_VI,
	.ltr_ac_latency_vo = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_VO,
	.ltr_ac_latency_समयout = WMI_10X_PDEV_PARAM_LTR_AC_LATENCY_TIMEOUT,
	.ltr_sleep_override = WMI_10X_PDEV_PARAM_LTR_SLEEP_OVERRIDE,
	.ltr_rx_override = WMI_10X_PDEV_PARAM_LTR_RX_OVERRIDE,
	.ltr_tx_activity_समयout = WMI_10X_PDEV_PARAM_LTR_TX_ACTIVITY_TIMEOUT,
	.l1ss_enable = WMI_10X_PDEV_PARAM_L1SS_ENABLE,
	.dsleep_enable = WMI_10X_PDEV_PARAM_DSLEEP_ENABLE,
	.pcielp_txbuf_flush = WMI_PDEV_PARAM_UNSUPPORTED,
	.pcielp_txbuf_watermark = WMI_PDEV_PARAM_UNSUPPORTED,
	.pcielp_txbuf_पंचांगo_en = WMI_PDEV_PARAM_UNSUPPORTED,
	.pcielp_txbuf_पंचांगo_value = WMI_PDEV_PARAM_UNSUPPORTED,
	.pdev_stats_update_period = WMI_10X_PDEV_PARAM_PDEV_STATS_UPDATE_PERIOD,
	.vdev_stats_update_period = WMI_10X_PDEV_PARAM_VDEV_STATS_UPDATE_PERIOD,
	.peer_stats_update_period = WMI_10X_PDEV_PARAM_PEER_STATS_UPDATE_PERIOD,
	.bcnflt_stats_update_period =
				WMI_10X_PDEV_PARAM_BCNFLT_STATS_UPDATE_PERIOD,
	.pmf_qos = WMI_10X_PDEV_PARAM_PMF_QOS,
	.arp_ac_override = WMI_10X_PDEV_PARAM_ARPDHCP_AC_OVERRIDE,
	.dcs = WMI_10X_PDEV_PARAM_DCS,
	.ani_enable = WMI_10X_PDEV_PARAM_ANI_ENABLE,
	.ani_poll_period = WMI_10X_PDEV_PARAM_ANI_POLL_PERIOD,
	.ani_listen_period = WMI_10X_PDEV_PARAM_ANI_LISTEN_PERIOD,
	.ani_ofdm_level = WMI_10X_PDEV_PARAM_ANI_OFDM_LEVEL,
	.ani_cck_level = WMI_10X_PDEV_PARAM_ANI_CCK_LEVEL,
	.dyntxchain = WMI_10X_PDEV_PARAM_DYNTXCHAIN,
	.proxy_sta = WMI_PDEV_PARAM_UNSUPPORTED,
	.idle_ps_config = WMI_PDEV_PARAM_UNSUPPORTED,
	.घातer_gating_sleep = WMI_PDEV_PARAM_UNSUPPORTED,
	.fast_channel_reset = WMI_10X_PDEV_PARAM_FAST_CHANNEL_RESET,
	.burst_dur = WMI_10X_PDEV_PARAM_BURST_DUR,
	.burst_enable = WMI_10X_PDEV_PARAM_BURST_ENABLE,
	.cal_period = WMI_10X_PDEV_PARAM_CAL_PERIOD,
	.aggr_burst = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_decap_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.smart_antenna_शेष_antenna = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.antenna_gain = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_filter = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_to_ucast_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.proxy_sta_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.हटाओ_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.peer_sta_ps_statechg_enable =
				WMI_10X_PDEV_PARAM_PEER_STA_PS_STATECHG_ENABLE,
	.igmpmld_ac_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.block_पूर्णांकerbss = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_disable_reset_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_msdu_ttl_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_ppdu_duration_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.txbf_sound_period_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_promisc_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_burst_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.en_stats = WMI_PDEV_PARAM_UNSUPPORTED,
	.mu_group_policy = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_detection = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.dpd_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_bcast_echo = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_strict_sch = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_sched_duration = WMI_PDEV_PARAM_UNSUPPORTED,
	.ant_plzn = WMI_PDEV_PARAM_UNSUPPORTED,
	.mgmt_retry_limit = WMI_PDEV_PARAM_UNSUPPORTED,
	.sensitivity_level = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_2g = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_5g = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_amsdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_ampdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.cca_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_PDEV_PARAM_UNSUPPORTED,
	.pdev_reset = WMI_10X_PDEV_PARAM_PDEV_RESET,
	.wapi_mbssid_offset = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_srcaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_dstaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_btcoex = WMI_PDEV_PARAM_UNSUPPORTED,
पूर्ण;

/* firmware 10.2 specअगरic mappings */
अटल काष्ठा wmi_cmd_map wmi_10_2_cmd_map = अणु
	.init_cmdid = WMI_10_2_INIT_CMDID,
	.start_scan_cmdid = WMI_10_2_START_SCAN_CMDID,
	.stop_scan_cmdid = WMI_10_2_STOP_SCAN_CMDID,
	.scan_chan_list_cmdid = WMI_10_2_SCAN_CHAN_LIST_CMDID,
	.scan_sch_prio_tbl_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_prob_req_oui_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_regकरोमुख्य_cmdid = WMI_10_2_PDEV_SET_REGDOMAIN_CMDID,
	.pdev_set_channel_cmdid = WMI_10_2_PDEV_SET_CHANNEL_CMDID,
	.pdev_set_param_cmdid = WMI_10_2_PDEV_SET_PARAM_CMDID,
	.pdev_pktlog_enable_cmdid = WMI_10_2_PDEV_PKTLOG_ENABLE_CMDID,
	.pdev_pktlog_disable_cmdid = WMI_10_2_PDEV_PKTLOG_DISABLE_CMDID,
	.pdev_set_wmm_params_cmdid = WMI_10_2_PDEV_SET_WMM_PARAMS_CMDID,
	.pdev_set_ht_cap_ie_cmdid = WMI_10_2_PDEV_SET_HT_CAP_IE_CMDID,
	.pdev_set_vht_cap_ie_cmdid = WMI_10_2_PDEV_SET_VHT_CAP_IE_CMDID,
	.pdev_set_quiet_mode_cmdid = WMI_10_2_PDEV_SET_QUIET_MODE_CMDID,
	.pdev_green_ap_ps_enable_cmdid = WMI_10_2_PDEV_GREEN_AP_PS_ENABLE_CMDID,
	.pdev_get_tpc_config_cmdid = WMI_10_2_PDEV_GET_TPC_CONFIG_CMDID,
	.pdev_set_base_macaddr_cmdid = WMI_10_2_PDEV_SET_BASE_MACADDR_CMDID,
	.vdev_create_cmdid = WMI_10_2_VDEV_CREATE_CMDID,
	.vdev_delete_cmdid = WMI_10_2_VDEV_DELETE_CMDID,
	.vdev_start_request_cmdid = WMI_10_2_VDEV_START_REQUEST_CMDID,
	.vdev_restart_request_cmdid = WMI_10_2_VDEV_RESTART_REQUEST_CMDID,
	.vdev_up_cmdid = WMI_10_2_VDEV_UP_CMDID,
	.vdev_stop_cmdid = WMI_10_2_VDEV_STOP_CMDID,
	.vdev_करोwn_cmdid = WMI_10_2_VDEV_DOWN_CMDID,
	.vdev_set_param_cmdid = WMI_10_2_VDEV_SET_PARAM_CMDID,
	.vdev_install_key_cmdid = WMI_10_2_VDEV_INSTALL_KEY_CMDID,
	.peer_create_cmdid = WMI_10_2_PEER_CREATE_CMDID,
	.peer_delete_cmdid = WMI_10_2_PEER_DELETE_CMDID,
	.peer_flush_tids_cmdid = WMI_10_2_PEER_FLUSH_TIDS_CMDID,
	.peer_set_param_cmdid = WMI_10_2_PEER_SET_PARAM_CMDID,
	.peer_assoc_cmdid = WMI_10_2_PEER_ASSOC_CMDID,
	.peer_add_wds_entry_cmdid = WMI_10_2_PEER_ADD_WDS_ENTRY_CMDID,
	.peer_हटाओ_wds_entry_cmdid = WMI_10_2_PEER_REMOVE_WDS_ENTRY_CMDID,
	.peer_mcast_group_cmdid = WMI_10_2_PEER_MCAST_GROUP_CMDID,
	.bcn_tx_cmdid = WMI_10_2_BCN_TX_CMDID,
	.pdev_send_bcn_cmdid = WMI_10_2_PDEV_SEND_BCN_CMDID,
	.bcn_पंचांगpl_cmdid = WMI_CMD_UNSUPPORTED,
	.bcn_filter_rx_cmdid = WMI_10_2_BCN_FILTER_RX_CMDID,
	.prb_req_filter_rx_cmdid = WMI_10_2_PRB_REQ_FILTER_RX_CMDID,
	.mgmt_tx_cmdid = WMI_10_2_MGMT_TX_CMDID,
	.prb_पंचांगpl_cmdid = WMI_CMD_UNSUPPORTED,
	.addba_clear_resp_cmdid = WMI_10_2_ADDBA_CLEAR_RESP_CMDID,
	.addba_send_cmdid = WMI_10_2_ADDBA_SEND_CMDID,
	.addba_status_cmdid = WMI_10_2_ADDBA_STATUS_CMDID,
	.delba_send_cmdid = WMI_10_2_DELBA_SEND_CMDID,
	.addba_set_resp_cmdid = WMI_10_2_ADDBA_SET_RESP_CMDID,
	.send_singleamsdu_cmdid = WMI_10_2_SEND_SINGLEAMSDU_CMDID,
	.sta_घातersave_mode_cmdid = WMI_10_2_STA_POWERSAVE_MODE_CMDID,
	.sta_घातersave_param_cmdid = WMI_10_2_STA_POWERSAVE_PARAM_CMDID,
	.sta_mimo_ps_mode_cmdid = WMI_10_2_STA_MIMO_PS_MODE_CMDID,
	.pdev_dfs_enable_cmdid = WMI_10_2_PDEV_DFS_ENABLE_CMDID,
	.pdev_dfs_disable_cmdid = WMI_10_2_PDEV_DFS_DISABLE_CMDID,
	.roam_scan_mode = WMI_10_2_ROAM_SCAN_MODE,
	.roam_scan_rssi_threshold = WMI_10_2_ROAM_SCAN_RSSI_THRESHOLD,
	.roam_scan_period = WMI_10_2_ROAM_SCAN_PERIOD,
	.roam_scan_rssi_change_threshold =
				WMI_10_2_ROAM_SCAN_RSSI_CHANGE_THRESHOLD,
	.roam_ap_profile = WMI_10_2_ROAM_AP_PROखाता,
	.ofl_scan_add_ap_profile = WMI_10_2_OFL_SCAN_ADD_AP_PROखाता,
	.ofl_scan_हटाओ_ap_profile = WMI_10_2_OFL_SCAN_REMOVE_AP_PROखाता,
	.ofl_scan_period = WMI_10_2_OFL_SCAN_PERIOD,
	.p2p_dev_set_device_info = WMI_10_2_P2P_DEV_SET_DEVICE_INFO,
	.p2p_dev_set_discoverability = WMI_10_2_P2P_DEV_SET_DISCOVERABILITY,
	.p2p_go_set_beacon_ie = WMI_10_2_P2P_GO_SET_BEACON_IE,
	.p2p_go_set_probe_resp_ie = WMI_10_2_P2P_GO_SET_PROBE_RESP_IE,
	.p2p_set_venकरोr_ie_data_cmdid = WMI_CMD_UNSUPPORTED,
	.ap_ps_peer_param_cmdid = WMI_10_2_AP_PS_PEER_PARAM_CMDID,
	.ap_ps_peer_uapsd_coex_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_rate_retry_sched_cmdid = WMI_10_2_PEER_RATE_RETRY_SCHED_CMDID,
	.wlan_profile_trigger_cmdid = WMI_10_2_WLAN_PROखाता_TRIGGER_CMDID,
	.wlan_profile_set_hist_पूर्णांकvl_cmdid =
				WMI_10_2_WLAN_PROखाता_SET_HIST_INTVL_CMDID,
	.wlan_profile_get_profile_data_cmdid =
				WMI_10_2_WLAN_PROखाता_GET_PROखाता_DATA_CMDID,
	.wlan_profile_enable_profile_id_cmdid =
				WMI_10_2_WLAN_PROखाता_ENABLE_PROखाता_ID_CMDID,
	.wlan_profile_list_profile_id_cmdid =
				WMI_10_2_WLAN_PROखाता_LIST_PROखाता_ID_CMDID,
	.pdev_suspend_cmdid = WMI_10_2_PDEV_SUSPEND_CMDID,
	.pdev_resume_cmdid = WMI_10_2_PDEV_RESUME_CMDID,
	.add_bcn_filter_cmdid = WMI_10_2_ADD_BCN_FILTER_CMDID,
	.rmv_bcn_filter_cmdid = WMI_10_2_RMV_BCN_FILTER_CMDID,
	.wow_add_wake_pattern_cmdid = WMI_10_2_WOW_ADD_WAKE_PATTERN_CMDID,
	.wow_del_wake_pattern_cmdid = WMI_10_2_WOW_DEL_WAKE_PATTERN_CMDID,
	.wow_enable_disable_wake_event_cmdid =
				WMI_10_2_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID,
	.wow_enable_cmdid = WMI_10_2_WOW_ENABLE_CMDID,
	.wow_hostwakeup_from_sleep_cmdid =
				WMI_10_2_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID,
	.rtt_measreq_cmdid = WMI_10_2_RTT_MEASREQ_CMDID,
	.rtt_tsf_cmdid = WMI_10_2_RTT_TSF_CMDID,
	.vdev_spectral_scan_configure_cmdid =
				WMI_10_2_VDEV_SPECTRAL_SCAN_CONFIGURE_CMDID,
	.vdev_spectral_scan_enable_cmdid =
				WMI_10_2_VDEV_SPECTRAL_SCAN_ENABLE_CMDID,
	.request_stats_cmdid = WMI_10_2_REQUEST_STATS_CMDID,
	.set_arp_ns_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.network_list_offload_config_cmdid = WMI_CMD_UNSUPPORTED,
	.gtk_offload_cmdid = WMI_CMD_UNSUPPORTED,
	.csa_offload_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.csa_offload_chanचयन_cmdid = WMI_CMD_UNSUPPORTED,
	.chatter_set_mode_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_addba_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_tid_delba_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_dtim_ps_method_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_uapsd_स्वतः_trig_cmdid = WMI_CMD_UNSUPPORTED,
	.sta_keepalive_cmd = WMI_CMD_UNSUPPORTED,
	.echo_cmdid = WMI_10_2_ECHO_CMDID,
	.pdev_utf_cmdid = WMI_10_2_PDEV_UTF_CMDID,
	.dbglog_cfg_cmdid = WMI_10_2_DBGLOG_CFG_CMDID,
	.pdev_qvit_cmdid = WMI_10_2_PDEV_QVIT_CMDID,
	.pdev_fपंचांग_पूर्णांकg_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_set_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_get_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.क्रमce_fw_hang_cmdid = WMI_CMD_UNSUPPORTED,
	.gpio_config_cmdid = WMI_10_2_GPIO_CONFIG_CMDID,
	.gpio_output_cmdid = WMI_10_2_GPIO_OUTPUT_CMDID,
	.pdev_get_temperature_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_enable_adaptive_cca_cmdid = WMI_CMD_UNSUPPORTED,
	.scan_update_request_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_standby_response_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_resume_response_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_add_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_evict_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_restore_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_prपूर्णांक_all_peers_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_update_wds_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_add_proxy_sta_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.rtt_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.oem_req_cmdid = WMI_CMD_UNSUPPORTED,
	.nan_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_ratemask_cmdid = WMI_CMD_UNSUPPORTED,
	.qboost_cfg_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_set_rx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_tx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_train_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_node_config_ops_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_antenna_चयन_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_ctl_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_mimogain_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_chainmsk_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_fips_cmdid = WMI_CMD_UNSUPPORTED,
	.tt_set_conf_cmdid = WMI_CMD_UNSUPPORTED,
	.fwtest_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_cck_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_ofdm_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_reserve_ast_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_tpc_table_cmdid = WMI_CMD_UNSUPPORTED,
	.radar_found_cmdid = WMI_CMD_UNSUPPORTED,
पूर्ण;

अटल काष्ठा wmi_pdev_param_map wmi_10_4_pdev_param_map = अणु
	.tx_chain_mask = WMI_10_4_PDEV_PARAM_TX_CHAIN_MASK,
	.rx_chain_mask = WMI_10_4_PDEV_PARAM_RX_CHAIN_MASK,
	.txघातer_limit2g = WMI_10_4_PDEV_PARAM_TXPOWER_LIMIT2G,
	.txघातer_limit5g = WMI_10_4_PDEV_PARAM_TXPOWER_LIMIT5G,
	.txघातer_scale = WMI_10_4_PDEV_PARAM_TXPOWER_SCALE,
	.beacon_gen_mode = WMI_10_4_PDEV_PARAM_BEACON_GEN_MODE,
	.beacon_tx_mode = WMI_10_4_PDEV_PARAM_BEACON_TX_MODE,
	.resmgr_offchan_mode = WMI_10_4_PDEV_PARAM_RESMGR_OFFCHAN_MODE,
	.protection_mode = WMI_10_4_PDEV_PARAM_PROTECTION_MODE,
	.dynamic_bw = WMI_10_4_PDEV_PARAM_DYNAMIC_BW,
	.non_agg_sw_retry_th = WMI_10_4_PDEV_PARAM_NON_AGG_SW_RETRY_TH,
	.agg_sw_retry_th = WMI_10_4_PDEV_PARAM_AGG_SW_RETRY_TH,
	.sta_kickout_th = WMI_10_4_PDEV_PARAM_STA_KICKOUT_TH,
	.ac_aggrsize_scaling = WMI_10_4_PDEV_PARAM_AC_AGGRSIZE_SCALING,
	.ltr_enable = WMI_10_4_PDEV_PARAM_LTR_ENABLE,
	.ltr_ac_latency_be = WMI_10_4_PDEV_PARAM_LTR_AC_LATENCY_BE,
	.ltr_ac_latency_bk = WMI_10_4_PDEV_PARAM_LTR_AC_LATENCY_BK,
	.ltr_ac_latency_vi = WMI_10_4_PDEV_PARAM_LTR_AC_LATENCY_VI,
	.ltr_ac_latency_vo = WMI_10_4_PDEV_PARAM_LTR_AC_LATENCY_VO,
	.ltr_ac_latency_समयout = WMI_10_4_PDEV_PARAM_LTR_AC_LATENCY_TIMEOUT,
	.ltr_sleep_override = WMI_10_4_PDEV_PARAM_LTR_SLEEP_OVERRIDE,
	.ltr_rx_override = WMI_10_4_PDEV_PARAM_LTR_RX_OVERRIDE,
	.ltr_tx_activity_समयout = WMI_10_4_PDEV_PARAM_LTR_TX_ACTIVITY_TIMEOUT,
	.l1ss_enable = WMI_10_4_PDEV_PARAM_L1SS_ENABLE,
	.dsleep_enable = WMI_10_4_PDEV_PARAM_DSLEEP_ENABLE,
	.pcielp_txbuf_flush = WMI_10_4_PDEV_PARAM_PCIELP_TXBUF_FLUSH,
	.pcielp_txbuf_watermark = WMI_10_4_PDEV_PARAM_PCIELP_TXBUF_WATERMARK,
	.pcielp_txbuf_पंचांगo_en = WMI_10_4_PDEV_PARAM_PCIELP_TXBUF_TMO_EN,
	.pcielp_txbuf_पंचांगo_value = WMI_10_4_PDEV_PARAM_PCIELP_TXBUF_TMO_VALUE,
	.pdev_stats_update_period =
			WMI_10_4_PDEV_PARAM_PDEV_STATS_UPDATE_PERIOD,
	.vdev_stats_update_period =
			WMI_10_4_PDEV_PARAM_VDEV_STATS_UPDATE_PERIOD,
	.peer_stats_update_period =
			WMI_10_4_PDEV_PARAM_PEER_STATS_UPDATE_PERIOD,
	.bcnflt_stats_update_period =
			WMI_10_4_PDEV_PARAM_BCNFLT_STATS_UPDATE_PERIOD,
	.pmf_qos = WMI_10_4_PDEV_PARAM_PMF_QOS,
	.arp_ac_override = WMI_10_4_PDEV_PARAM_ARP_AC_OVERRIDE,
	.dcs = WMI_10_4_PDEV_PARAM_DCS,
	.ani_enable = WMI_10_4_PDEV_PARAM_ANI_ENABLE,
	.ani_poll_period = WMI_10_4_PDEV_PARAM_ANI_POLL_PERIOD,
	.ani_listen_period = WMI_10_4_PDEV_PARAM_ANI_LISTEN_PERIOD,
	.ani_ofdm_level = WMI_10_4_PDEV_PARAM_ANI_OFDM_LEVEL,
	.ani_cck_level = WMI_10_4_PDEV_PARAM_ANI_CCK_LEVEL,
	.dyntxchain = WMI_10_4_PDEV_PARAM_DYNTXCHAIN,
	.proxy_sta = WMI_10_4_PDEV_PARAM_PROXY_STA,
	.idle_ps_config = WMI_10_4_PDEV_PARAM_IDLE_PS_CONFIG,
	.घातer_gating_sleep = WMI_10_4_PDEV_PARAM_POWER_GATING_SLEEP,
	.fast_channel_reset = WMI_10_4_PDEV_PARAM_FAST_CHANNEL_RESET,
	.burst_dur = WMI_10_4_PDEV_PARAM_BURST_DUR,
	.burst_enable = WMI_10_4_PDEV_PARAM_BURST_ENABLE,
	.cal_period = WMI_10_4_PDEV_PARAM_CAL_PERIOD,
	.aggr_burst = WMI_10_4_PDEV_PARAM_AGGR_BURST,
	.rx_decap_mode = WMI_10_4_PDEV_PARAM_RX_DECAP_MODE,
	.smart_antenna_शेष_antenna =
			WMI_10_4_PDEV_PARAM_SMART_ANTENNA_DEFAULT_ANTENNA,
	.igmpmld_override = WMI_10_4_PDEV_PARAM_IGMPMLD_OVERRIDE,
	.igmpmld_tid = WMI_10_4_PDEV_PARAM_IGMPMLD_TID,
	.antenna_gain = WMI_10_4_PDEV_PARAM_ANTENNA_GAIN,
	.rx_filter = WMI_10_4_PDEV_PARAM_RX_FILTER,
	.set_mcast_to_ucast_tid = WMI_10_4_PDEV_SET_MCAST_TO_UCAST_TID,
	.proxy_sta_mode = WMI_10_4_PDEV_PARAM_PROXY_STA_MODE,
	.set_mcast2ucast_mode = WMI_10_4_PDEV_PARAM_SET_MCAST2UCAST_MODE,
	.set_mcast2ucast_buffer = WMI_10_4_PDEV_PARAM_SET_MCAST2UCAST_BUFFER,
	.हटाओ_mcast2ucast_buffer =
			WMI_10_4_PDEV_PARAM_REMOVE_MCAST2UCAST_BUFFER,
	.peer_sta_ps_statechg_enable =
			WMI_10_4_PDEV_PEER_STA_PS_STATECHG_ENABLE,
	.igmpmld_ac_override = WMI_10_4_PDEV_PARAM_IGMPMLD_AC_OVERRIDE,
	.block_पूर्णांकerbss = WMI_10_4_PDEV_PARAM_BLOCK_INTERBSS,
	.set_disable_reset_cmdid = WMI_10_4_PDEV_PARAM_SET_DISABLE_RESET_CMDID,
	.set_msdu_ttl_cmdid = WMI_10_4_PDEV_PARAM_SET_MSDU_TTL_CMDID,
	.set_ppdu_duration_cmdid = WMI_10_4_PDEV_PARAM_SET_PPDU_DURATION_CMDID,
	.txbf_sound_period_cmdid = WMI_10_4_PDEV_PARAM_TXBF_SOUND_PERIOD_CMDID,
	.set_promisc_mode_cmdid = WMI_10_4_PDEV_PARAM_SET_PROMISC_MODE_CMDID,
	.set_burst_mode_cmdid = WMI_10_4_PDEV_PARAM_SET_BURST_MODE_CMDID,
	.en_stats = WMI_10_4_PDEV_PARAM_EN_STATS,
	.mu_group_policy = WMI_10_4_PDEV_PARAM_MU_GROUP_POLICY,
	.noise_detection = WMI_10_4_PDEV_PARAM_NOISE_DETECTION,
	.noise_threshold = WMI_10_4_PDEV_PARAM_NOISE_THRESHOLD,
	.dpd_enable = WMI_10_4_PDEV_PARAM_DPD_ENABLE,
	.set_mcast_bcast_echo = WMI_10_4_PDEV_PARAM_SET_MCAST_BCAST_ECHO,
	.atf_strict_sch = WMI_10_4_PDEV_PARAM_ATF_STRICT_SCH,
	.atf_sched_duration = WMI_10_4_PDEV_PARAM_ATF_SCHED_DURATION,
	.ant_plzn = WMI_10_4_PDEV_PARAM_ANT_PLZN,
	.mgmt_retry_limit = WMI_10_4_PDEV_PARAM_MGMT_RETRY_LIMIT,
	.sensitivity_level = WMI_10_4_PDEV_PARAM_SENSITIVITY_LEVEL,
	.चिन्हित_txघातer_2g = WMI_10_4_PDEV_PARAM_SIGNED_TXPOWER_2G,
	.चिन्हित_txघातer_5g = WMI_10_4_PDEV_PARAM_SIGNED_TXPOWER_5G,
	.enable_per_tid_amsdu = WMI_10_4_PDEV_PARAM_ENABLE_PER_TID_AMSDU,
	.enable_per_tid_ampdu = WMI_10_4_PDEV_PARAM_ENABLE_PER_TID_AMPDU,
	.cca_threshold = WMI_10_4_PDEV_PARAM_CCA_THRESHOLD,
	.rts_fixed_rate = WMI_10_4_PDEV_PARAM_RTS_FIXED_RATE,
	.pdev_reset = WMI_10_4_PDEV_PARAM_PDEV_RESET,
	.wapi_mbssid_offset = WMI_10_4_PDEV_PARAM_WAPI_MBSSID_OFFSET,
	.arp_srcaddr = WMI_10_4_PDEV_PARAM_ARP_SRCADDR,
	.arp_dstaddr = WMI_10_4_PDEV_PARAM_ARP_DSTADDR,
	.enable_btcoex = WMI_10_4_PDEV_PARAM_ENABLE_BTCOEX,
पूर्ण;

अटल स्थिर u8 wmi_key_cipher_suites[] = अणु
	[WMI_CIPHER_NONE] = WMI_CIPHER_NONE,
	[WMI_CIPHER_WEP] = WMI_CIPHER_WEP,
	[WMI_CIPHER_TKIP] = WMI_CIPHER_TKIP,
	[WMI_CIPHER_AES_OCB] = WMI_CIPHER_AES_OCB,
	[WMI_CIPHER_AES_CCM] = WMI_CIPHER_AES_CCM,
	[WMI_CIPHER_WAPI] = WMI_CIPHER_WAPI,
	[WMI_CIPHER_CKIP] = WMI_CIPHER_CKIP,
	[WMI_CIPHER_AES_CMAC] = WMI_CIPHER_AES_CMAC,
	[WMI_CIPHER_AES_GCM] = WMI_CIPHER_AES_GCM,
पूर्ण;

अटल स्थिर u8 wmi_tlv_key_cipher_suites[] = अणु
	[WMI_CIPHER_NONE] = WMI_TLV_CIPHER_NONE,
	[WMI_CIPHER_WEP] = WMI_TLV_CIPHER_WEP,
	[WMI_CIPHER_TKIP] = WMI_TLV_CIPHER_TKIP,
	[WMI_CIPHER_AES_OCB] = WMI_TLV_CIPHER_AES_OCB,
	[WMI_CIPHER_AES_CCM] = WMI_TLV_CIPHER_AES_CCM,
	[WMI_CIPHER_WAPI] = WMI_TLV_CIPHER_WAPI,
	[WMI_CIPHER_CKIP] = WMI_TLV_CIPHER_CKIP,
	[WMI_CIPHER_AES_CMAC] = WMI_TLV_CIPHER_AES_CMAC,
	[WMI_CIPHER_AES_GCM] = WMI_TLV_CIPHER_AES_GCM,
पूर्ण;

अटल स्थिर काष्ठा wmi_peer_flags_map wmi_peer_flags_map = अणु
	.auth = WMI_PEER_AUTH,
	.qos = WMI_PEER_QOS,
	.need_ptk_4_way = WMI_PEER_NEED_PTK_4_WAY,
	.need_gtk_2_way = WMI_PEER_NEED_GTK_2_WAY,
	.apsd = WMI_PEER_APSD,
	.ht = WMI_PEER_HT,
	.bw40 = WMI_PEER_40MHZ,
	.stbc = WMI_PEER_STBC,
	.ldbc = WMI_PEER_LDPC,
	.dyn_mimops = WMI_PEER_DYN_MIMOPS,
	.अटल_mimops = WMI_PEER_STATIC_MIMOPS,
	.spatial_mux = WMI_PEER_SPATIAL_MUX,
	.vht = WMI_PEER_VHT,
	.bw80 = WMI_PEER_80MHZ,
	.vht_2g = WMI_PEER_VHT_2G,
	.pmf = WMI_PEER_PMF,
	.bw160 = WMI_PEER_160MHZ,
पूर्ण;

अटल स्थिर काष्ठा wmi_peer_flags_map wmi_10x_peer_flags_map = अणु
	.auth = WMI_10X_PEER_AUTH,
	.qos = WMI_10X_PEER_QOS,
	.need_ptk_4_way = WMI_10X_PEER_NEED_PTK_4_WAY,
	.need_gtk_2_way = WMI_10X_PEER_NEED_GTK_2_WAY,
	.apsd = WMI_10X_PEER_APSD,
	.ht = WMI_10X_PEER_HT,
	.bw40 = WMI_10X_PEER_40MHZ,
	.stbc = WMI_10X_PEER_STBC,
	.ldbc = WMI_10X_PEER_LDPC,
	.dyn_mimops = WMI_10X_PEER_DYN_MIMOPS,
	.अटल_mimops = WMI_10X_PEER_STATIC_MIMOPS,
	.spatial_mux = WMI_10X_PEER_SPATIAL_MUX,
	.vht = WMI_10X_PEER_VHT,
	.bw80 = WMI_10X_PEER_80MHZ,
	.bw160 = WMI_10X_PEER_160MHZ,
पूर्ण;

अटल स्थिर काष्ठा wmi_peer_flags_map wmi_10_2_peer_flags_map = अणु
	.auth = WMI_10_2_PEER_AUTH,
	.qos = WMI_10_2_PEER_QOS,
	.need_ptk_4_way = WMI_10_2_PEER_NEED_PTK_4_WAY,
	.need_gtk_2_way = WMI_10_2_PEER_NEED_GTK_2_WAY,
	.apsd = WMI_10_2_PEER_APSD,
	.ht = WMI_10_2_PEER_HT,
	.bw40 = WMI_10_2_PEER_40MHZ,
	.stbc = WMI_10_2_PEER_STBC,
	.ldbc = WMI_10_2_PEER_LDPC,
	.dyn_mimops = WMI_10_2_PEER_DYN_MIMOPS,
	.अटल_mimops = WMI_10_2_PEER_STATIC_MIMOPS,
	.spatial_mux = WMI_10_2_PEER_SPATIAL_MUX,
	.vht = WMI_10_2_PEER_VHT,
	.bw80 = WMI_10_2_PEER_80MHZ,
	.vht_2g = WMI_10_2_PEER_VHT_2G,
	.pmf = WMI_10_2_PEER_PMF,
	.bw160 = WMI_10_2_PEER_160MHZ,
पूर्ण;

व्योम ath10k_wmi_put_wmi_channel(काष्ठा ath10k *ar, काष्ठा wmi_channel *ch,
				स्थिर काष्ठा wmi_channel_arg *arg)
अणु
	u32 flags = 0;
	काष्ठा ieee80211_channel *chan = शून्य;

	स_रखो(ch, 0, माप(*ch));

	अगर (arg->passive)
		flags |= WMI_CHAN_FLAG_PASSIVE;
	अगर (arg->allow_ibss)
		flags |= WMI_CHAN_FLAG_ADHOC_ALLOWED;
	अगर (arg->allow_ht)
		flags |= WMI_CHAN_FLAG_ALLOW_HT;
	अगर (arg->allow_vht)
		flags |= WMI_CHAN_FLAG_ALLOW_VHT;
	अगर (arg->ht40plus)
		flags |= WMI_CHAN_FLAG_HT40_PLUS;
	अगर (arg->chan_radar)
		flags |= WMI_CHAN_FLAG_DFS;

	ch->band_center_freq2 = 0;
	ch->mhz = __cpu_to_le32(arg->freq);
	ch->band_center_freq1 = __cpu_to_le32(arg->band_center_freq1);
	अगर (arg->mode == MODE_11AC_VHT80_80) अणु
		ch->band_center_freq2 = __cpu_to_le32(arg->band_center_freq2);
		chan = ieee80211_get_channel(ar->hw->wiphy,
					     arg->band_center_freq2 - 10);
	पूर्ण

	अगर (arg->mode == MODE_11AC_VHT160) अणु
		u32 band_center_freq1;
		u32 band_center_freq2;

		अगर (arg->freq > arg->band_center_freq1) अणु
			band_center_freq1 = arg->band_center_freq1 + 40;
			band_center_freq2 = arg->band_center_freq1 - 40;
		पूर्ण अन्यथा अणु
			band_center_freq1 = arg->band_center_freq1 - 40;
			band_center_freq2 = arg->band_center_freq1 + 40;
		पूर्ण

		ch->band_center_freq1 =
					__cpu_to_le32(band_center_freq1);
		/* Minus 10 to get a defined 5G channel frequency*/
		chan = ieee80211_get_channel(ar->hw->wiphy,
					     band_center_freq2 - 10);
		/* The center frequency of the entire VHT160 */
		ch->band_center_freq2 = __cpu_to_le32(arg->band_center_freq1);
	पूर्ण

	अगर (chan && chan->flags & IEEE80211_CHAN_RADAR)
		flags |= WMI_CHAN_FLAG_DFS_CFREQ2;

	ch->min_घातer = arg->min_घातer;
	ch->max_घातer = arg->max_घातer;
	ch->reg_घातer = arg->max_reg_घातer;
	ch->antenna_max = arg->max_antenna_gain;
	ch->max_tx_घातer = arg->max_घातer;

	/* mode & flags share storage */
	ch->mode = arg->mode;
	ch->flags |= __cpu_to_le32(flags);
पूर्ण

पूर्णांक ath10k_wmi_रुको_क्रम_service_पढ़ोy(काष्ठा ath10k *ar)
अणु
	अचिन्हित दीर्घ समय_left;

	समय_left = रुको_क्रम_completion_समयout(&ar->wmi.service_पढ़ोy,
						WMI_SERVICE_READY_TIMEOUT_HZ);
	अगर (!समय_left)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

पूर्णांक ath10k_wmi_रुको_क्रम_unअगरied_पढ़ोy(काष्ठा ath10k *ar)
अणु
	अचिन्हित दीर्घ समय_left;

	समय_left = रुको_क्रम_completion_समयout(&ar->wmi.unअगरied_पढ़ोy,
						WMI_UNIFIED_READY_TIMEOUT_HZ);
	अगर (!समय_left)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

काष्ठा sk_buff *ath10k_wmi_alloc_skb(काष्ठा ath10k *ar, u32 len)
अणु
	काष्ठा sk_buff *skb;
	u32 round_len = roundup(len, 4);

	skb = ath10k_htc_alloc_skb(ar, WMI_SKB_HEADROOM + round_len);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, WMI_SKB_HEADROOM);
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4))
		ath10k_warn(ar, "Unaligned WMI skb\n");

	skb_put(skb, round_len);
	स_रखो(skb->data, 0, round_len);

	वापस skb;
पूर्ण

अटल व्योम ath10k_wmi_htc_tx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb(skb);
पूर्ण

पूर्णांक ath10k_wmi_cmd_send_noरुको(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			       u32 cmd_id)
अणु
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	पूर्णांक ret;
	u32 cmd = 0;

	अगर (skb_push(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		वापस -ENOMEM;

	cmd |= SM(cmd_id, WMI_CMD_HDR_CMD_ID);

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	cmd_hdr->cmd_id = __cpu_to_le32(cmd);

	स_रखो(skb_cb, 0, माप(*skb_cb));
	trace_ath10k_wmi_cmd(ar, cmd_id, skb->data, skb->len);
	ret = ath10k_htc_send(&ar->htc, ar->wmi.eid, skb);

	अगर (ret)
		जाओ err_pull;

	वापस 0;

err_pull:
	skb_pull(skb, माप(काष्ठा wmi_cmd_hdr));
	वापस ret;
पूर्ण

अटल व्योम ath10k_wmi_tx_beacon_noरुको(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ath10k_skb_cb *cb;
	काष्ठा sk_buff *bcn;
	bool dtim_zero;
	bool deliver_cab;
	पूर्णांक ret;

	spin_lock_bh(&ar->data_lock);

	bcn = arvअगर->beacon;

	अगर (!bcn)
		जाओ unlock;

	cb = ATH10K_SKB_CB(bcn);

	चयन (arvअगर->beacon_state) अणु
	हाल ATH10K_BEACON_SENDING:
	हाल ATH10K_BEACON_SENT:
		अवरोध;
	हाल ATH10K_BEACON_SCHEDULED:
		arvअगर->beacon_state = ATH10K_BEACON_SENDING;
		spin_unlock_bh(&ar->data_lock);

		dtim_zero = !!(cb->flags & ATH10K_SKB_F_DTIM_ZERO);
		deliver_cab = !!(cb->flags & ATH10K_SKB_F_DELIVER_CAB);
		ret = ath10k_wmi_beacon_send_ref_noरुको(arvअगर->ar,
							arvअगर->vdev_id,
							bcn->data, bcn->len,
							cb->paddr,
							dtim_zero,
							deliver_cab);

		spin_lock_bh(&ar->data_lock);

		अगर (ret == 0)
			arvअगर->beacon_state = ATH10K_BEACON_SENT;
		अन्यथा
			arvअगर->beacon_state = ATH10K_BEACON_SCHEDULED;
	पूर्ण

unlock:
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल व्योम ath10k_wmi_tx_beacons_iter(व्योम *data, u8 *mac,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	ath10k_wmi_tx_beacon_noरुको(arvअगर);
पूर्ण

अटल व्योम ath10k_wmi_tx_beacons_noरुको(काष्ठा ath10k *ar)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_NORMAL_FLAGS,
						   ath10k_wmi_tx_beacons_iter,
						   शून्य);
पूर्ण

अटल व्योम ath10k_wmi_op_ep_tx_credits(काष्ठा ath10k *ar)
अणु
	/* try to send pending beacons first. they take priority */
	ath10k_wmi_tx_beacons_noरुको(ar);

	wake_up(&ar->wmi.tx_credits_wq);
पूर्ण

पूर्णांक ath10k_wmi_cmd_send(काष्ठा ath10k *ar, काष्ठा sk_buff *skb, u32 cmd_id)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	अगर (cmd_id == WMI_CMD_UNSUPPORTED) अणु
		ath10k_warn(ar, "wmi command %d is not supported by firmware\n",
			    cmd_id);
		वापस ret;
	पूर्ण

	रुको_event_समयout(ar->wmi.tx_credits_wq, (अणु
		/* try to send pending beacons first. they take priority */
		ath10k_wmi_tx_beacons_noरुको(ar);

		ret = ath10k_wmi_cmd_send_noरुको(ar, skb, cmd_id);

		अगर (ret && test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
			ret = -ESHUTDOWN;

		(ret != -EAGAIN);
	पूर्ण), 3 * HZ);

	अगर (ret)
		dev_kमुक्त_skb_any(skb);

	अगर (ret == -EAGAIN) अणु
		ath10k_warn(ar, "wmi command %d timeout, restarting hardware\n",
			    cmd_id);
		ath10k_core_start_recovery(ar);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_mgmt_tx(काष्ठा ath10k *ar, काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(msdu);
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा wmi_mgmt_tx_cmd *cmd;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक len;
	u32 vdev_id;
	u32 buf_len = msdu->len;
	u16 fc;
	स्थिर u8 *peer_addr;

	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	fc = le16_to_cpu(hdr->frame_control);

	अगर (cb->vअगर) अणु
		arvअगर = (व्योम *)cb->vअगर->drv_priv;
		vdev_id = arvअगर->vdev_id;
	पूर्ण अन्यथा अणु
		vdev_id = 0;
	पूर्ण

	अगर (WARN_ON_ONCE(!ieee80211_is_mgmt(hdr->frame_control)))
		वापस ERR_PTR(-EINVAL);

	len = माप(cmd->hdr) + msdu->len;

	अगर ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_रक्षित(hdr->frame_control)) अणु
		peer_addr = hdr->addr1;
		अगर (is_multicast_ether_addr(peer_addr)) अणु
			len += माप(काष्ठा ieee80211_mmie_16);
			buf_len += माप(काष्ठा ieee80211_mmie_16);
		पूर्ण अन्यथा अणु
			अगर (cb->ucast_cipher == WLAN_CIPHER_SUITE_GCMP ||
			    cb->ucast_cipher == WLAN_CIPHER_SUITE_GCMP_256) अणु
				len += IEEE80211_GCMP_MIC_LEN;
				buf_len += IEEE80211_GCMP_MIC_LEN;
			पूर्ण अन्यथा अणु
				len += IEEE80211_CCMP_MIC_LEN;
				buf_len += IEEE80211_CCMP_MIC_LEN;
			पूर्ण
		पूर्ण
	पूर्ण

	len = round_up(len, 4);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_mgmt_tx_cmd *)skb->data;

	cmd->hdr.vdev_id = __cpu_to_le32(vdev_id);
	cmd->hdr.tx_rate = 0;
	cmd->hdr.tx_घातer = 0;
	cmd->hdr.buf_len = __cpu_to_le32(buf_len);

	ether_addr_copy(cmd->hdr.peer_macaddr.addr, ieee80211_get_DA(hdr));
	स_नकल(cmd->buf, msdu->data, msdu->len);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi mgmt tx skb %pK len %d ftype %02x stype %02x\n",
		   msdu, skb->len, fc & IEEE80211_FCTL_FTYPE,
		   fc & IEEE80211_FCTL_STYPE);
	trace_ath10k_tx_hdr(ar, skb->data, skb->len);
	trace_ath10k_tx_payload(ar, skb->data, skb->len);

	वापस skb;
पूर्ण

अटल व्योम ath10k_wmi_event_scan_started(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		ath10k_warn(ar, "received scan started event in an invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH10K_SCAN_STARTING:
		ar->scan.state = ATH10K_SCAN_RUNNING;

		अगर (ar->scan.is_roc)
			ieee80211_पढ़ोy_on_channel(ar->hw);

		complete(&ar->scan.started);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath10k_wmi_event_scan_start_failed(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		ath10k_warn(ar, "received scan start failed event in an invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH10K_SCAN_STARTING:
		complete(&ar->scan.started);
		__ath10k_scan_finish(ar);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath10k_wmi_event_scan_completed(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
	हाल ATH10K_SCAN_STARTING:
		/* One suspected reason scan can be completed जबतक starting is
		 * अगर firmware fails to deliver all scan events to the host,
		 * e.g. when transport pipe is full. This has been observed
		 * with spectral scan phyerr events starving wmi transport
		 * pipe. In such हाल the "scan completed" event should be (and
		 * is) ignored by the host as it may be just firmware's scan
		 * state machine recovering.
		 */
		ath10k_warn(ar, "received scan completed event in an invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		__ath10k_scan_finish(ar);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath10k_wmi_event_scan_bss_chan(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
	हाल ATH10K_SCAN_STARTING:
		ath10k_warn(ar, "received scan bss chan event in an invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		ar->scan_channel = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath10k_wmi_event_scan_क्रमeign_chan(काष्ठा ath10k *ar, u32 freq)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
	हाल ATH10K_SCAN_STARTING:
		ath10k_warn(ar, "received scan foreign chan event in an invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		ar->scan_channel = ieee80211_get_channel(ar->hw->wiphy, freq);

		अगर (ar->scan.is_roc && ar->scan.roc_freq == freq)
			complete(&ar->scan.on_channel);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
ath10k_wmi_event_scan_type_str(क्रमागत wmi_scan_event_type type,
			       क्रमागत wmi_scan_completion_reason reason)
अणु
	चयन (type) अणु
	हाल WMI_SCAN_EVENT_STARTED:
		वापस "started";
	हाल WMI_SCAN_EVENT_COMPLETED:
		चयन (reason) अणु
		हाल WMI_SCAN_REASON_COMPLETED:
			वापस "completed";
		हाल WMI_SCAN_REASON_CANCELLED:
			वापस "completed [cancelled]";
		हाल WMI_SCAN_REASON_PREEMPTED:
			वापस "completed [preempted]";
		हाल WMI_SCAN_REASON_TIMEDOUT:
			वापस "completed [timedout]";
		हाल WMI_SCAN_REASON_INTERNAL_FAILURE:
			वापस "completed [internal err]";
		हाल WMI_SCAN_REASON_MAX:
			अवरोध;
		पूर्ण
		वापस "completed [unknown]";
	हाल WMI_SCAN_EVENT_BSS_CHANNEL:
		वापस "bss channel";
	हाल WMI_SCAN_EVENT_FOREIGN_CHANNEL:
		वापस "foreign channel";
	हाल WMI_SCAN_EVENT_DEQUEUED:
		वापस "dequeued";
	हाल WMI_SCAN_EVENT_PREEMPTED:
		वापस "preempted";
	हाल WMI_SCAN_EVENT_START_FAILED:
		वापस "start failed";
	हाल WMI_SCAN_EVENT_RESTARTED:
		वापस "restarted";
	हाल WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT:
		वापस "foreign channel exit";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_scan_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				      काष्ठा wmi_scan_ev_arg *arg)
अणु
	काष्ठा wmi_scan_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->event_type = ev->event_type;
	arg->reason = ev->reason;
	arg->channel_freq = ev->channel_freq;
	arg->scan_req_id = ev->scan_req_id;
	arg->scan_id = ev->scan_id;
	arg->vdev_id = ev->vdev_id;

	वापस 0;
पूर्ण

पूर्णांक ath10k_wmi_event_scan(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_scan_ev_arg arg = अणुपूर्ण;
	क्रमागत wmi_scan_event_type event_type;
	क्रमागत wmi_scan_completion_reason reason;
	u32 freq;
	u32 req_id;
	u32 scan_id;
	u32 vdev_id;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_scan(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse scan event: %d\n", ret);
		वापस ret;
	पूर्ण

	event_type = __le32_to_cpu(arg.event_type);
	reason = __le32_to_cpu(arg.reason);
	freq = __le32_to_cpu(arg.channel_freq);
	req_id = __le32_to_cpu(arg.scan_req_id);
	scan_id = __le32_to_cpu(arg.scan_id);
	vdev_id = __le32_to_cpu(arg.vdev_id);

	spin_lock_bh(&ar->data_lock);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "scan event %s type %d reason %d freq %d req_id %d scan_id %d vdev_id %d state %s (%d)\n",
		   ath10k_wmi_event_scan_type_str(event_type, reason),
		   event_type, reason, freq, req_id, scan_id, vdev_id,
		   ath10k_scan_state_str(ar->scan.state), ar->scan.state);

	चयन (event_type) अणु
	हाल WMI_SCAN_EVENT_STARTED:
		ath10k_wmi_event_scan_started(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_COMPLETED:
		ath10k_wmi_event_scan_completed(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_BSS_CHANNEL:
		ath10k_wmi_event_scan_bss_chan(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_FOREIGN_CHANNEL:
		ath10k_wmi_event_scan_क्रमeign_chan(ar, freq);
		अवरोध;
	हाल WMI_SCAN_EVENT_START_FAILED:
		ath10k_warn(ar, "received scan start failure event\n");
		ath10k_wmi_event_scan_start_failed(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_DEQUEUED:
	हाल WMI_SCAN_EVENT_PREEMPTED:
	हाल WMI_SCAN_EVENT_RESTARTED:
	हाल WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	spin_unlock_bh(&ar->data_lock);
	वापस 0;
पूर्ण

/* If keys are configured, HW decrypts all frames
 * with रक्षित bit set. Mark such frames as decrypted.
 */
अटल व्योम ath10k_wmi_handle_wep_reauth(काष्ठा ath10k *ar,
					 काष्ठा sk_buff *skb,
					 काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अचिन्हित पूर्णांक hdrlen;
	bool peer_key;
	u8 *addr, keyidx;

	अगर (!ieee80211_is_auth(hdr->frame_control) ||
	    !ieee80211_has_रक्षित(hdr->frame_control))
		वापस;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (skb->len < (hdrlen + IEEE80211_WEP_IV_LEN))
		वापस;

	keyidx = skb->data[hdrlen + (IEEE80211_WEP_IV_LEN - 1)] >> WEP_KEYID_SHIFT;
	addr = ieee80211_get_SA(hdr);

	spin_lock_bh(&ar->data_lock);
	peer_key = ath10k_mac_is_peer_wep_key_set(ar, addr, keyidx);
	spin_unlock_bh(&ar->data_lock);

	अगर (peer_key) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac wep key present for peer %pM\n", addr);
		status->flag |= RX_FLAG_DECRYPTED;
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_mgmt_rx_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
					 काष्ठा wmi_mgmt_rx_ev_arg *arg)
अणु
	काष्ठा wmi_mgmt_rx_event_v1 *ev_v1;
	काष्ठा wmi_mgmt_rx_event_v2 *ev_v2;
	काष्ठा wmi_mgmt_rx_hdr_v1 *ev_hdr;
	काष्ठा wmi_mgmt_rx_ext_info *ext_info;
	माप_प्रकार pull_len;
	u32 msdu_len;
	u32 len;

	अगर (test_bit(ATH10K_FW_FEATURE_EXT_WMI_MGMT_RX,
		     ar->running_fw->fw_file.fw_features)) अणु
		ev_v2 = (काष्ठा wmi_mgmt_rx_event_v2 *)skb->data;
		ev_hdr = &ev_v2->hdr.v1;
		pull_len = माप(*ev_v2);
	पूर्ण अन्यथा अणु
		ev_v1 = (काष्ठा wmi_mgmt_rx_event_v1 *)skb->data;
		ev_hdr = &ev_v1->hdr;
		pull_len = माप(*ev_v1);
	पूर्ण

	अगर (skb->len < pull_len)
		वापस -EPROTO;

	skb_pull(skb, pull_len);
	arg->channel = ev_hdr->channel;
	arg->buf_len = ev_hdr->buf_len;
	arg->status = ev_hdr->status;
	arg->snr = ev_hdr->snr;
	arg->phy_mode = ev_hdr->phy_mode;
	arg->rate = ev_hdr->rate;

	msdu_len = __le32_to_cpu(arg->buf_len);
	अगर (skb->len < msdu_len)
		वापस -EPROTO;

	अगर (le32_to_cpu(arg->status) & WMI_RX_STATUS_EXT_INFO) अणु
		len = ALIGN(le32_to_cpu(arg->buf_len), 4);
		ext_info = (काष्ठा wmi_mgmt_rx_ext_info *)(skb->data + len);
		स_नकल(&arg->ext_info, ext_info,
		       माप(काष्ठा wmi_mgmt_rx_ext_info));
	पूर्ण
	/* the WMI buffer might've ended up being padded to 4 bytes due to HTC
	 * trailer with credit update. Trim the excess garbage.
	 */
	skb_trim(skb, msdu_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_pull_mgmt_rx_ev(काष्ठा ath10k *ar,
					      काष्ठा sk_buff *skb,
					      काष्ठा wmi_mgmt_rx_ev_arg *arg)
अणु
	काष्ठा wmi_10_4_mgmt_rx_event *ev;
	काष्ठा wmi_10_4_mgmt_rx_hdr *ev_hdr;
	माप_प्रकार pull_len;
	u32 msdu_len;
	काष्ठा wmi_mgmt_rx_ext_info *ext_info;
	u32 len;

	ev = (काष्ठा wmi_10_4_mgmt_rx_event *)skb->data;
	ev_hdr = &ev->hdr;
	pull_len = माप(*ev);

	अगर (skb->len < pull_len)
		वापस -EPROTO;

	skb_pull(skb, pull_len);
	arg->channel = ev_hdr->channel;
	arg->buf_len = ev_hdr->buf_len;
	arg->status = ev_hdr->status;
	arg->snr = ev_hdr->snr;
	arg->phy_mode = ev_hdr->phy_mode;
	arg->rate = ev_hdr->rate;

	msdu_len = __le32_to_cpu(arg->buf_len);
	अगर (skb->len < msdu_len)
		वापस -EPROTO;

	अगर (le32_to_cpu(arg->status) & WMI_RX_STATUS_EXT_INFO) अणु
		len = ALIGN(le32_to_cpu(arg->buf_len), 4);
		ext_info = (काष्ठा wmi_mgmt_rx_ext_info *)(skb->data + len);
		स_नकल(&arg->ext_info, ext_info,
		       माप(काष्ठा wmi_mgmt_rx_ext_info));
	पूर्ण

	/* Make sure bytes added क्रम padding are हटाओd. */
	skb_trim(skb, msdu_len);

	वापस 0;
पूर्ण

अटल bool ath10k_wmi_rx_is_decrypted(काष्ठा ath10k *ar,
				       काष्ठा ieee80211_hdr *hdr)
अणु
	अगर (!ieee80211_has_रक्षित(hdr->frame_control))
		वापस false;

	/* FW delivers WEP Shared Auth frame with Protected Bit set and
	 * encrypted payload. However in हाल of PMF it delivers decrypted
	 * frames with Protected Bit set.
	 */
	अगर (ieee80211_is_auth(hdr->frame_control))
		वापस false;

	/* qca99x0 based FW delivers broadcast or multicast management frames
	 * (ex: group privacy action frames in mesh) as encrypted payload.
	 */
	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) &&
	    ar->hw_params.sw_decrypt_mcast_mgmt)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
wmi_process_mgmt_tx_comp(काष्ठा ath10k *ar, काष्ठा mgmt_tx_compl_params *param)
अणु
	काष्ठा ath10k_mgmt_tx_pkt_addr *pkt_addr;
	काष्ठा ath10k_wmi *wmi = &ar->wmi;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *msdu;
	पूर्णांक ret;

	spin_lock_bh(&ar->data_lock);

	pkt_addr = idr_find(&wmi->mgmt_pending_tx, param->desc_id);
	अगर (!pkt_addr) अणु
		ath10k_warn(ar, "received mgmt tx completion for invalid msdu_id: %d\n",
			    param->desc_id);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	msdu = pkt_addr->vaddr;
	dma_unmap_single(ar->dev, pkt_addr->paddr,
			 msdu->len, DMA_TO_DEVICE);
	info = IEEE80211_SKB_CB(msdu);

	अगर (param->status) अणु
		info->flags &= ~IEEE80211_TX_STAT_ACK;
	पूर्ण अन्यथा अणु
		info->flags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_संकेत = ATH10K_DEFAULT_NOISE_FLOOR +
					  param->ack_rssi;
		info->status.is_valid_ack_संकेत = true;
	पूर्ण

	ieee80211_tx_status_irqsafe(ar->hw, msdu);

	ret = 0;

out:
	idr_हटाओ(&wmi->mgmt_pending_tx, param->desc_id);
	spin_unlock_bh(&ar->data_lock);
	वापस ret;
पूर्ण

पूर्णांक ath10k_wmi_event_mgmt_tx_compl(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_mgmt_tx_compl_ev_arg arg;
	काष्ठा mgmt_tx_compl_params param;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_mgmt_tx_compl(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse mgmt comp event: %d\n", ret);
		वापस ret;
	पूर्ण

	स_रखो(&param, 0, माप(काष्ठा mgmt_tx_compl_params));
	param.desc_id = __le32_to_cpu(arg.desc_id);
	param.status = __le32_to_cpu(arg.status);

	अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map))
		param.ack_rssi = __le32_to_cpu(arg.ack_rssi);

	wmi_process_mgmt_tx_comp(ar, &param);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv evnt mgmt tx completion\n");

	वापस 0;
पूर्ण

पूर्णांक ath10k_wmi_event_mgmt_tx_bundle_compl(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_mgmt_tx_bundle_compl_ev_arg arg;
	काष्ठा mgmt_tx_compl_params param;
	u32 num_reports;
	पूर्णांक i, ret;

	ret = ath10k_wmi_pull_mgmt_tx_bundle_compl(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse bundle mgmt compl event: %d\n", ret);
		वापस ret;
	पूर्ण

	num_reports = __le32_to_cpu(arg.num_reports);

	क्रम (i = 0; i < num_reports; i++) अणु
		स_रखो(&param, 0, माप(काष्ठा mgmt_tx_compl_params));
		param.desc_id = __le32_to_cpu(arg.desc_ids[i]);
		param.status = __le32_to_cpu(arg.desc_ids[i]);

		अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map))
			param.ack_rssi = __le32_to_cpu(arg.ack_rssi[i]);
		wmi_process_mgmt_tx_comp(ar, &param);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv event bundle mgmt tx completion\n");

	वापस 0;
पूर्ण

पूर्णांक ath10k_wmi_event_mgmt_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_mgmt_rx_ev_arg arg = अणुपूर्ण;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_supported_band *sband;
	u32 rx_status;
	u32 channel;
	u32 phy_mode;
	u32 snr, rssi;
	u32 rate;
	u16 fc;
	पूर्णांक ret, i;

	ret = ath10k_wmi_pull_mgmt_rx(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse mgmt rx event: %d\n", ret);
		dev_kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	channel = __le32_to_cpu(arg.channel);
	rx_status = __le32_to_cpu(arg.status);
	snr = __le32_to_cpu(arg.snr);
	phy_mode = __le32_to_cpu(arg.phy_mode);
	rate = __le32_to_cpu(arg.rate);

	स_रखो(status, 0, माप(*status));

	ath10k_dbg(ar, ATH10K_DBG_MGMT,
		   "event mgmt rx status %08x\n", rx_status);

	अगर ((test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags)) ||
	    (rx_status & (WMI_RX_STATUS_ERR_DECRYPT |
	    WMI_RX_STATUS_ERR_KEY_CACHE_MISS | WMI_RX_STATUS_ERR_CRC))) अणु
		dev_kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (rx_status & WMI_RX_STATUS_ERR_MIC)
		status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (rx_status & WMI_RX_STATUS_EXT_INFO) अणु
		status->maस_समय =
			__le64_to_cpu(arg.ext_info.rx_mac_बारtamp);
		status->flag |= RX_FLAG_MACTIME_END;
	पूर्ण
	/* Hardware can Rx CCK rates on 5GHz. In that हाल phy_mode is set to
	 * MODE_11B. This means phy_mode is not a reliable source क्रम the band
	 * of mgmt rx.
	 */
	अगर (channel >= 1 && channel <= 14) अणु
		status->band = NL80211_BAND_2GHZ;
	पूर्ण अन्यथा अगर (channel >= 36 && channel <= ATH10K_MAX_5G_CHAN) अणु
		status->band = NL80211_BAND_5GHZ;
	पूर्ण अन्यथा अणु
		/* Shouldn't happen unless list of advertised channels to
		 * mac80211 has been changed.
		 */
		WARN_ON_ONCE(1);
		dev_kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (phy_mode == MODE_11B && status->band == NL80211_BAND_5GHZ)
		ath10k_dbg(ar, ATH10K_DBG_MGMT, "wmi mgmt rx 11b (CCK) on 5GHz\n");

	sband = &ar->mac.sbands[status->band];

	status->freq = ieee80211_channel_to_frequency(channel, status->band);
	status->संकेत = snr + ATH10K_DEFAULT_NOISE_FLOOR;

	BUILD_BUG_ON(ARRAY_SIZE(status->chain_संकेत) != ARRAY_SIZE(arg.rssi));

	क्रम (i = 0; i < ARRAY_SIZE(status->chain_संकेत); i++) अणु
		status->chains &= ~BIT(i);
		rssi = __le32_to_cpu(arg.rssi[i]);
		ath10k_dbg(ar, ATH10K_DBG_MGMT, "mgmt rssi[%d]:%d\n", i, arg.rssi[i]);

		अगर (rssi != ATH10K_INVALID_RSSI && rssi != 0) अणु
			status->chain_संकेत[i] = ATH10K_DEFAULT_NOISE_FLOOR + rssi;
			status->chains |= BIT(i);
		पूर्ण
	पूर्ण

	status->rate_idx = ath10k_mac_bitrate_to_idx(sband, rate / 100);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	fc = le16_to_cpu(hdr->frame_control);

	/* Firmware is guaranteed to report all essential management frames via
	 * WMI जबतक it can deliver some extra via HTT. Since there can be
	 * duplicates split the reporting wrt monitor/snअगरfing.
	 */
	status->flag |= RX_FLAG_SKIP_MONITOR;

	ath10k_wmi_handle_wep_reauth(ar, skb, status);

	अगर (ath10k_wmi_rx_is_decrypted(ar, hdr)) अणु
		status->flag |= RX_FLAG_DECRYPTED;

		अगर (!ieee80211_is_action(hdr->frame_control) &&
		    !ieee80211_is_deauth(hdr->frame_control) &&
		    !ieee80211_is_disassoc(hdr->frame_control)) अणु
			status->flag |= RX_FLAG_IV_STRIPPED |
					RX_FLAG_MMIC_STRIPPED;
			hdr->frame_control = __cpu_to_le16(fc &
					~IEEE80211_FCTL_PROTECTED);
		पूर्ण
	पूर्ण

	अगर (ieee80211_is_beacon(hdr->frame_control))
		ath10k_mac_handle_beacon(ar, skb);

	ath10k_dbg(ar, ATH10K_DBG_MGMT,
		   "event mgmt rx skb %pK len %d ftype %02x stype %02x\n",
		   skb, skb->len,
		   fc & IEEE80211_FCTL_FTYPE, fc & IEEE80211_FCTL_STYPE);

	ath10k_dbg(ar, ATH10K_DBG_MGMT,
		   "event mgmt rx freq %d band %d snr %d, rate_idx %d\n",
		   status->freq, status->band, status->संकेत,
		   status->rate_idx);

	ieee80211_rx_ni(ar->hw, skb);

	वापस 0;
पूर्ण

अटल पूर्णांक freq_to_idx(काष्ठा ath10k *ar, पूर्णांक freq)
अणु
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक band, ch, idx = 0;

	क्रम (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; band++) अणु
		sband = ar->hw->wiphy->bands[band];
		अगर (!sband)
			जारी;

		क्रम (ch = 0; ch < sband->n_channels; ch++, idx++)
			अगर (sband->channels[ch].center_freq == freq)
				जाओ निकास;
	पूर्ण

निकास:
	वापस idx;
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_ch_info_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
					 काष्ठा wmi_ch_info_ev_arg *arg)
अणु
	काष्ठा wmi_chan_info_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->err_code = ev->err_code;
	arg->freq = ev->freq;
	arg->cmd_flags = ev->cmd_flags;
	arg->noise_न्यूनमान = ev->noise_न्यूनमान;
	arg->rx_clear_count = ev->rx_clear_count;
	arg->cycle_count = ev->cycle_count;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_pull_ch_info_ev(काष्ठा ath10k *ar,
					      काष्ठा sk_buff *skb,
					      काष्ठा wmi_ch_info_ev_arg *arg)
अणु
	काष्ठा wmi_10_4_chan_info_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->err_code = ev->err_code;
	arg->freq = ev->freq;
	arg->cmd_flags = ev->cmd_flags;
	arg->noise_न्यूनमान = ev->noise_न्यूनमान;
	arg->rx_clear_count = ev->rx_clear_count;
	arg->cycle_count = ev->cycle_count;
	arg->chan_tx_pwr_range = ev->chan_tx_pwr_range;
	arg->chan_tx_pwr_tp = ev->chan_tx_pwr_tp;
	arg->rx_frame_count = ev->rx_frame_count;

	वापस 0;
पूर्ण

/*
 * Handle the channel info event क्रम firmware which only sends one
 * chan_info event per scanned channel.
 */
अटल व्योम ath10k_wmi_event_chan_info_unpaired(काष्ठा ath10k *ar,
						काष्ठा chan_info_params *params)
अणु
	काष्ठा survey_info *survey;
	पूर्णांक idx;

	अगर (params->cmd_flags & WMI_CHAN_INFO_FLAG_COMPLETE) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI, "chan info report completed\n");
		वापस;
	पूर्ण

	idx = freq_to_idx(ar, params->freq);
	अगर (idx >= ARRAY_SIZE(ar->survey)) अणु
		ath10k_warn(ar, "chan info: invalid frequency %d (idx %d out of bounds)\n",
			    params->freq, idx);
		वापस;
	पूर्ण

	survey = &ar->survey[idx];

	अगर (!params->mac_clk_mhz)
		वापस;

	स_रखो(survey, 0, माप(*survey));

	survey->noise = params->noise_न्यूनमान;
	survey->समय = (params->cycle_count / params->mac_clk_mhz) / 1000;
	survey->समय_busy = (params->rx_clear_count / params->mac_clk_mhz) / 1000;
	survey->filled |= SURVEY_INFO_NOISE_DBM | SURVEY_INFO_TIME |
			  SURVEY_INFO_TIME_BUSY;
पूर्ण

/*
 * Handle the channel info event क्रम firmware which sends chan_info
 * event in pairs(start and stop events) क्रम every scanned channel.
 */
अटल व्योम ath10k_wmi_event_chan_info_paired(काष्ठा ath10k *ar,
					      काष्ठा chan_info_params *params)
अणु
	काष्ठा survey_info *survey;
	पूर्णांक idx;

	idx = freq_to_idx(ar, params->freq);
	अगर (idx >= ARRAY_SIZE(ar->survey)) अणु
		ath10k_warn(ar, "chan info: invalid frequency %d (idx %d out of bounds)\n",
			    params->freq, idx);
		वापस;
	पूर्ण

	अगर (params->cmd_flags & WMI_CHAN_INFO_FLAG_COMPLETE) अणु
		अगर (ar->ch_info_can_report_survey) अणु
			survey = &ar->survey[idx];
			survey->noise = params->noise_न्यूनमान;
			survey->filled = SURVEY_INFO_NOISE_DBM;

			ath10k_hw_fill_survey_समय(ar,
						   survey,
						   params->cycle_count,
						   params->rx_clear_count,
						   ar->survey_last_cycle_count,
						   ar->survey_last_rx_clear_count);
		पूर्ण

		ar->ch_info_can_report_survey = false;
	पूर्ण अन्यथा अणु
		ar->ch_info_can_report_survey = true;
	पूर्ण

	अगर (!(params->cmd_flags & WMI_CHAN_INFO_FLAG_PRE_COMPLETE)) अणु
		ar->survey_last_rx_clear_count = params->rx_clear_count;
		ar->survey_last_cycle_count = params->cycle_count;
	पूर्ण
पूर्ण

व्योम ath10k_wmi_event_chan_info(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा chan_info_params ch_info_param;
	काष्ठा wmi_ch_info_ev_arg arg = अणुपूर्ण;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_ch_info(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse chan info event: %d\n", ret);
		वापस;
	पूर्ण

	ch_info_param.err_code = __le32_to_cpu(arg.err_code);
	ch_info_param.freq = __le32_to_cpu(arg.freq);
	ch_info_param.cmd_flags = __le32_to_cpu(arg.cmd_flags);
	ch_info_param.noise_न्यूनमान = __le32_to_cpu(arg.noise_न्यूनमान);
	ch_info_param.rx_clear_count = __le32_to_cpu(arg.rx_clear_count);
	ch_info_param.cycle_count = __le32_to_cpu(arg.cycle_count);
	ch_info_param.mac_clk_mhz = __le32_to_cpu(arg.mac_clk_mhz);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "chan info err_code %d freq %d cmd_flags %d noise_floor %d rx_clear_count %d cycle_count %d\n",
		   ch_info_param.err_code, ch_info_param.freq, ch_info_param.cmd_flags,
		   ch_info_param.noise_न्यूनमान, ch_info_param.rx_clear_count,
		   ch_info_param.cycle_count);

	spin_lock_bh(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
	हाल ATH10K_SCAN_STARTING:
		ath10k_warn(ar, "received chan info event without a scan request, ignoring\n");
		जाओ निकास;
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		अवरोध;
	पूर्ण

	अगर (test_bit(ATH10K_FW_FEATURE_SINGLE_CHAN_INFO_PER_CHANNEL,
		     ar->running_fw->fw_file.fw_features))
		ath10k_wmi_event_chan_info_unpaired(ar, &ch_info_param);
	अन्यथा
		ath10k_wmi_event_chan_info_paired(ar, &ch_info_param);

निकास:
	spin_unlock_bh(&ar->data_lock);
पूर्ण

व्योम ath10k_wmi_event_echo(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_echo_ev_arg arg = अणुपूर्ण;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_echo_ev(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse echo: %d\n", ret);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event echo value 0x%08x\n",
		   le32_to_cpu(arg.value));

	अगर (le32_to_cpu(arg.value) == ATH10K_WMI_BARRIER_ECHO_ID)
		complete(&ar->wmi.barrier);
पूर्ण

पूर्णांक ath10k_wmi_event_debug_mesg(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi event debug mesg len %d\n",
		   skb->len);

	trace_ath10k_wmi_dbglog(ar, skb->data, skb->len);

	वापस 0;
पूर्ण

व्योम ath10k_wmi_pull_pdev_stats_base(स्थिर काष्ठा wmi_pdev_stats_base *src,
				     काष्ठा ath10k_fw_stats_pdev *dst)
अणु
	dst->ch_noise_न्यूनमान = __le32_to_cpu(src->chan_nf);
	dst->tx_frame_count = __le32_to_cpu(src->tx_frame_count);
	dst->rx_frame_count = __le32_to_cpu(src->rx_frame_count);
	dst->rx_clear_count = __le32_to_cpu(src->rx_clear_count);
	dst->cycle_count = __le32_to_cpu(src->cycle_count);
	dst->phy_err_count = __le32_to_cpu(src->phy_err_count);
	dst->chan_tx_घातer = __le32_to_cpu(src->chan_tx_pwr);
पूर्ण

व्योम ath10k_wmi_pull_pdev_stats_tx(स्थिर काष्ठा wmi_pdev_stats_tx *src,
				   काष्ठा ath10k_fw_stats_pdev *dst)
अणु
	dst->comp_queued = __le32_to_cpu(src->comp_queued);
	dst->comp_delivered = __le32_to_cpu(src->comp_delivered);
	dst->msdu_enqued = __le32_to_cpu(src->msdu_enqued);
	dst->mpdu_enqued = __le32_to_cpu(src->mpdu_enqued);
	dst->wmm_drop = __le32_to_cpu(src->wmm_drop);
	dst->local_enqued = __le32_to_cpu(src->local_enqued);
	dst->local_मुक्तd = __le32_to_cpu(src->local_मुक्तd);
	dst->hw_queued = __le32_to_cpu(src->hw_queued);
	dst->hw_reaped = __le32_to_cpu(src->hw_reaped);
	dst->underrun = __le32_to_cpu(src->underrun);
	dst->tx_पात = __le32_to_cpu(src->tx_पात);
	dst->mpdus_requed = __le32_to_cpu(src->mpdus_requed);
	dst->tx_ko = __le32_to_cpu(src->tx_ko);
	dst->data_rc = __le32_to_cpu(src->data_rc);
	dst->self_triggers = __le32_to_cpu(src->self_triggers);
	dst->sw_retry_failure = __le32_to_cpu(src->sw_retry_failure);
	dst->illgl_rate_phy_err = __le32_to_cpu(src->illgl_rate_phy_err);
	dst->pdev_cont_xretry = __le32_to_cpu(src->pdev_cont_xretry);
	dst->pdev_tx_समयout = __le32_to_cpu(src->pdev_tx_समयout);
	dst->pdev_resets = __le32_to_cpu(src->pdev_resets);
	dst->phy_underrun = __le32_to_cpu(src->phy_underrun);
	dst->txop_ovf = __le32_to_cpu(src->txop_ovf);
पूर्ण

अटल व्योम
ath10k_wmi_10_4_pull_pdev_stats_tx(स्थिर काष्ठा wmi_10_4_pdev_stats_tx *src,
				   काष्ठा ath10k_fw_stats_pdev *dst)
अणु
	dst->comp_queued = __le32_to_cpu(src->comp_queued);
	dst->comp_delivered = __le32_to_cpu(src->comp_delivered);
	dst->msdu_enqued = __le32_to_cpu(src->msdu_enqued);
	dst->mpdu_enqued = __le32_to_cpu(src->mpdu_enqued);
	dst->wmm_drop = __le32_to_cpu(src->wmm_drop);
	dst->local_enqued = __le32_to_cpu(src->local_enqued);
	dst->local_मुक्तd = __le32_to_cpu(src->local_मुक्तd);
	dst->hw_queued = __le32_to_cpu(src->hw_queued);
	dst->hw_reaped = __le32_to_cpu(src->hw_reaped);
	dst->underrun = __le32_to_cpu(src->underrun);
	dst->tx_पात = __le32_to_cpu(src->tx_पात);
	dst->mpdus_requed = __le32_to_cpu(src->mpdus_requed);
	dst->tx_ko = __le32_to_cpu(src->tx_ko);
	dst->data_rc = __le32_to_cpu(src->data_rc);
	dst->self_triggers = __le32_to_cpu(src->self_triggers);
	dst->sw_retry_failure = __le32_to_cpu(src->sw_retry_failure);
	dst->illgl_rate_phy_err = __le32_to_cpu(src->illgl_rate_phy_err);
	dst->pdev_cont_xretry = __le32_to_cpu(src->pdev_cont_xretry);
	dst->pdev_tx_समयout = __le32_to_cpu(src->pdev_tx_समयout);
	dst->pdev_resets = __le32_to_cpu(src->pdev_resets);
	dst->phy_underrun = __le32_to_cpu(src->phy_underrun);
	dst->txop_ovf = __le32_to_cpu(src->txop_ovf);
	dst->hw_छोड़ोd = __le32_to_cpu(src->hw_छोड़ोd);
	dst->seq_posted = __le32_to_cpu(src->seq_posted);
	dst->seq_failed_queueing =
		__le32_to_cpu(src->seq_failed_queueing);
	dst->seq_completed = __le32_to_cpu(src->seq_completed);
	dst->seq_restarted = __le32_to_cpu(src->seq_restarted);
	dst->mu_seq_posted = __le32_to_cpu(src->mu_seq_posted);
	dst->mpdus_sw_flush = __le32_to_cpu(src->mpdus_sw_flush);
	dst->mpdus_hw_filter = __le32_to_cpu(src->mpdus_hw_filter);
	dst->mpdus_truncated = __le32_to_cpu(src->mpdus_truncated);
	dst->mpdus_ack_failed = __le32_to_cpu(src->mpdus_ack_failed);
	dst->mpdus_hw_filter = __le32_to_cpu(src->mpdus_hw_filter);
	dst->mpdus_expired = __le32_to_cpu(src->mpdus_expired);
पूर्ण

व्योम ath10k_wmi_pull_pdev_stats_rx(स्थिर काष्ठा wmi_pdev_stats_rx *src,
				   काष्ठा ath10k_fw_stats_pdev *dst)
अणु
	dst->mid_ppdu_route_change = __le32_to_cpu(src->mid_ppdu_route_change);
	dst->status_rcvd = __le32_to_cpu(src->status_rcvd);
	dst->r0_frags = __le32_to_cpu(src->r0_frags);
	dst->r1_frags = __le32_to_cpu(src->r1_frags);
	dst->r2_frags = __le32_to_cpu(src->r2_frags);
	dst->r3_frags = __le32_to_cpu(src->r3_frags);
	dst->htt_msdus = __le32_to_cpu(src->htt_msdus);
	dst->htt_mpdus = __le32_to_cpu(src->htt_mpdus);
	dst->loc_msdus = __le32_to_cpu(src->loc_msdus);
	dst->loc_mpdus = __le32_to_cpu(src->loc_mpdus);
	dst->oversize_amsdu = __le32_to_cpu(src->oversize_amsdu);
	dst->phy_errs = __le32_to_cpu(src->phy_errs);
	dst->phy_err_drop = __le32_to_cpu(src->phy_err_drop);
	dst->mpdu_errs = __le32_to_cpu(src->mpdu_errs);
पूर्ण

व्योम ath10k_wmi_pull_pdev_stats_extra(स्थिर काष्ठा wmi_pdev_stats_extra *src,
				      काष्ठा ath10k_fw_stats_pdev *dst)
अणु
	dst->ack_rx_bad = __le32_to_cpu(src->ack_rx_bad);
	dst->rts_bad = __le32_to_cpu(src->rts_bad);
	dst->rts_good = __le32_to_cpu(src->rts_good);
	dst->fcs_bad = __le32_to_cpu(src->fcs_bad);
	dst->no_beacons = __le32_to_cpu(src->no_beacons);
	dst->mib_पूर्णांक_count = __le32_to_cpu(src->mib_पूर्णांक_count);
पूर्ण

व्योम ath10k_wmi_pull_peer_stats(स्थिर काष्ठा wmi_peer_stats *src,
				काष्ठा ath10k_fw_stats_peer *dst)
अणु
	ether_addr_copy(dst->peer_macaddr, src->peer_macaddr.addr);
	dst->peer_rssi = __le32_to_cpu(src->peer_rssi);
	dst->peer_tx_rate = __le32_to_cpu(src->peer_tx_rate);
पूर्ण

अटल व्योम
ath10k_wmi_10_4_pull_peer_stats(स्थिर काष्ठा wmi_10_4_peer_stats *src,
				काष्ठा ath10k_fw_stats_peer *dst)
अणु
	ether_addr_copy(dst->peer_macaddr, src->peer_macaddr.addr);
	dst->peer_rssi = __le32_to_cpu(src->peer_rssi);
	dst->peer_tx_rate = __le32_to_cpu(src->peer_tx_rate);
	dst->peer_rx_rate = __le32_to_cpu(src->peer_rx_rate);
पूर्ण

अटल व्योम
ath10k_wmi_10_4_pull_vdev_stats(स्थिर काष्ठा wmi_vdev_stats_extd *src,
				काष्ठा ath10k_fw_stats_vdev_extd *dst)
अणु
	dst->vdev_id = __le32_to_cpu(src->vdev_id);
	dst->ppdu_aggr_cnt = __le32_to_cpu(src->ppdu_aggr_cnt);
	dst->ppdu_noack = __le32_to_cpu(src->ppdu_noack);
	dst->mpdu_queued = __le32_to_cpu(src->mpdu_queued);
	dst->ppdu_nonaggr_cnt = __le32_to_cpu(src->ppdu_nonaggr_cnt);
	dst->mpdu_sw_requeued = __le32_to_cpu(src->mpdu_sw_requeued);
	dst->mpdu_suc_retry = __le32_to_cpu(src->mpdu_suc_retry);
	dst->mpdu_suc_multitry = __le32_to_cpu(src->mpdu_suc_multitry);
	dst->mpdu_fail_retry = __le32_to_cpu(src->mpdu_fail_retry);
	dst->tx_fपंचांग_suc = __le32_to_cpu(src->tx_fपंचांग_suc);
	dst->tx_fपंचांग_suc_retry = __le32_to_cpu(src->tx_fपंचांग_suc_retry);
	dst->tx_fपंचांग_fail = __le32_to_cpu(src->tx_fपंचांग_fail);
	dst->rx_fपंचांगr_cnt = __le32_to_cpu(src->rx_fपंचांगr_cnt);
	dst->rx_fपंचांगr_dup_cnt = __le32_to_cpu(src->rx_fपंचांगr_dup_cnt);
	dst->rx_अगरपंचांगr_cnt = __le32_to_cpu(src->rx_अगरपंचांगr_cnt);
	dst->rx_अगरपंचांगr_dup_cnt = __le32_to_cpu(src->rx_अगरपंचांगr_dup_cnt);
पूर्ण

अटल पूर्णांक ath10k_wmi_मुख्य_op_pull_fw_stats(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb,
					    काष्ठा ath10k_fw_stats *stats)
अणु
	स्थिर काष्ठा wmi_stats_event *ev = (व्योम *)skb->data;
	u32 num_pdev_stats, num_peer_stats;
	पूर्णांक i;

	अगर (!skb_pull(skb, माप(*ev)))
		वापस -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);

	क्रम (i = 0; i < num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_pdev_stats *src;
		काष्ठा ath10k_fw_stats_pdev *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);

		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	/* fw करोesn't implement vdev stats */

	क्रम (i = 0; i < num_peer_stats; i++) अणु
		स्थिर काष्ठा wmi_peer_stats *src;
		काष्ठा ath10k_fw_stats_peer *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_peer_stats(src, dst);
		list_add_tail(&dst->list, &stats->peers);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10x_op_pull_fw_stats(काष्ठा ath10k *ar,
					   काष्ठा sk_buff *skb,
					   काष्ठा ath10k_fw_stats *stats)
अणु
	स्थिर काष्ठा wmi_stats_event *ev = (व्योम *)skb->data;
	u32 num_pdev_stats, num_peer_stats;
	पूर्णांक i;

	अगर (!skb_pull(skb, माप(*ev)))
		वापस -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);

	क्रम (i = 0; i < num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_10x_pdev_stats *src;
		काष्ठा ath10k_fw_stats_pdev *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		ath10k_wmi_pull_pdev_stats_extra(&src->extra, dst);

		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	/* fw करोesn't implement vdev stats */

	क्रम (i = 0; i < num_peer_stats; i++) अणु
		स्थिर काष्ठा wmi_10x_peer_stats *src;
		काष्ठा ath10k_fw_stats_peer *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_peer_stats(&src->old, dst);

		dst->peer_rx_rate = __le32_to_cpu(src->peer_rx_rate);

		list_add_tail(&dst->list, &stats->peers);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_2_op_pull_fw_stats(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb,
					    काष्ठा ath10k_fw_stats *stats)
अणु
	स्थिर काष्ठा wmi_10_2_stats_event *ev = (व्योम *)skb->data;
	u32 num_pdev_stats;
	u32 num_pdev_ext_stats;
	u32 num_peer_stats;
	पूर्णांक i;

	अगर (!skb_pull(skb, माप(*ev)))
		वापस -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_pdev_ext_stats = __le32_to_cpu(ev->num_pdev_ext_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);

	क्रम (i = 0; i < num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_pdev_stats *src;
		काष्ठा ath10k_fw_stats_pdev *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		ath10k_wmi_pull_pdev_stats_extra(&src->extra, dst);
		/* FIXME: expose 10.2 specअगरic values */

		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	क्रम (i = 0; i < num_pdev_ext_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_pdev_ext_stats *src;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		/* FIXME: expose values to userspace
		 *
		 * Note: Even though this loop seems to करो nothing it is
		 * required to parse following sub-काष्ठाures properly.
		 */
	पूर्ण

	/* fw करोesn't implement vdev stats */

	क्रम (i = 0; i < num_peer_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_peer_stats *src;
		काष्ठा ath10k_fw_stats_peer *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_peer_stats(&src->old, dst);

		dst->peer_rx_rate = __le32_to_cpu(src->peer_rx_rate);
		/* FIXME: expose 10.2 specअगरic values */

		list_add_tail(&dst->list, &stats->peers);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_2_4_op_pull_fw_stats(काष्ठा ath10k *ar,
					      काष्ठा sk_buff *skb,
					      काष्ठा ath10k_fw_stats *stats)
अणु
	स्थिर काष्ठा wmi_10_2_stats_event *ev = (व्योम *)skb->data;
	u32 num_pdev_stats;
	u32 num_pdev_ext_stats;
	u32 num_peer_stats;
	पूर्णांक i;

	अगर (!skb_pull(skb, माप(*ev)))
		वापस -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_pdev_ext_stats = __le32_to_cpu(ev->num_pdev_ext_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);

	क्रम (i = 0; i < num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_pdev_stats *src;
		काष्ठा ath10k_fw_stats_pdev *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		ath10k_wmi_pull_pdev_stats_extra(&src->extra, dst);
		/* FIXME: expose 10.2 specअगरic values */

		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	क्रम (i = 0; i < num_pdev_ext_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_pdev_ext_stats *src;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		/* FIXME: expose values to userspace
		 *
		 * Note: Even though this loop seems to करो nothing it is
		 * required to parse following sub-काष्ठाures properly.
		 */
	पूर्ण

	/* fw करोesn't implement vdev stats */

	क्रम (i = 0; i < num_peer_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_4_ext_peer_stats *src;
		काष्ठा ath10k_fw_stats_peer *dst;
		पूर्णांक stats_len;

		अगर (test_bit(WMI_SERVICE_PEER_STATS, ar->wmi.svc_map))
			stats_len = माप(काष्ठा wmi_10_2_4_ext_peer_stats);
		अन्यथा
			stats_len = माप(काष्ठा wmi_10_2_4_peer_stats);

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, stats_len))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_peer_stats(&src->common.old, dst);

		dst->peer_rx_rate = __le32_to_cpu(src->common.peer_rx_rate);

		अगर (ath10k_peer_stats_enabled(ar))
			dst->rx_duration = __le32_to_cpu(src->rx_duration);
		/* FIXME: expose 10.2 specअगरic values */

		list_add_tail(&dst->list, &stats->peers);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_pull_fw_stats(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb,
					    काष्ठा ath10k_fw_stats *stats)
अणु
	स्थिर काष्ठा wmi_10_2_stats_event *ev = (व्योम *)skb->data;
	u32 num_pdev_stats;
	u32 num_pdev_ext_stats;
	u32 num_vdev_stats;
	u32 num_peer_stats;
	u32 num_bcnflt_stats;
	u32 stats_id;
	पूर्णांक i;

	अगर (!skb_pull(skb, माप(*ev)))
		वापस -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_pdev_ext_stats = __le32_to_cpu(ev->num_pdev_ext_stats);
	num_vdev_stats = __le32_to_cpu(ev->num_vdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);
	num_bcnflt_stats = __le32_to_cpu(ev->num_bcnflt_stats);
	stats_id = __le32_to_cpu(ev->stats_id);

	क्रम (i = 0; i < num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_10_4_pdev_stats *src;
		काष्ठा ath10k_fw_stats_pdev *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_10_4_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		dst->rx_ovfl_errs = __le32_to_cpu(src->rx_ovfl_errs);
		ath10k_wmi_pull_pdev_stats_extra(&src->extra, dst);

		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	क्रम (i = 0; i < num_pdev_ext_stats; i++) अणु
		स्थिर काष्ठा wmi_10_2_pdev_ext_stats *src;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		/* FIXME: expose values to userspace
		 *
		 * Note: Even though this loop seems to करो nothing it is
		 * required to parse following sub-काष्ठाures properly.
		 */
	पूर्ण

	क्रम (i = 0; i < num_vdev_stats; i++) अणु
		स्थिर काष्ठा wmi_vdev_stats *src;

		/* Ignore vdev stats here as it has only vdev id. Actual vdev
		 * stats will be retrieved from vdev extended stats.
		 */
		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;
	पूर्ण

	क्रम (i = 0; i < num_peer_stats; i++) अणु
		स्थिर काष्ठा wmi_10_4_peer_stats *src;
		काष्ठा ath10k_fw_stats_peer *dst;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_10_4_pull_peer_stats(src, dst);
		list_add_tail(&dst->list, &stats->peers);
	पूर्ण

	क्रम (i = 0; i < num_bcnflt_stats; i++) अणु
		स्थिर काष्ठा wmi_10_4_bss_bcn_filter_stats *src;

		src = (व्योम *)skb->data;
		अगर (!skb_pull(skb, माप(*src)))
			वापस -EPROTO;

		/* FIXME: expose values to userspace
		 *
		 * Note: Even though this loop seems to करो nothing it is
		 * required to parse following sub-काष्ठाures properly.
		 */
	पूर्ण

	अगर (stats_id & WMI_10_4_STAT_PEER_EXTD) अणु
		stats->extended = true;

		क्रम (i = 0; i < num_peer_stats; i++) अणु
			स्थिर काष्ठा wmi_10_4_peer_extd_stats *src;
			काष्ठा ath10k_fw_extd_stats_peer *dst;

			src = (व्योम *)skb->data;
			अगर (!skb_pull(skb, माप(*src)))
				वापस -EPROTO;

			dst = kzalloc(माप(*dst), GFP_ATOMIC);
			अगर (!dst)
				जारी;

			ether_addr_copy(dst->peer_macaddr,
					src->peer_macaddr.addr);
			dst->rx_duration = __le32_to_cpu(src->rx_duration);
			list_add_tail(&dst->list, &stats->peers_extd);
		पूर्ण
	पूर्ण

	अगर (stats_id & WMI_10_4_STAT_VDEV_EXTD) अणु
		क्रम (i = 0; i < num_vdev_stats; i++) अणु
			स्थिर काष्ठा wmi_vdev_stats_extd *src;
			काष्ठा ath10k_fw_stats_vdev_extd *dst;

			src = (व्योम *)skb->data;
			अगर (!skb_pull(skb, माप(*src)))
				वापस -EPROTO;

			dst = kzalloc(माप(*dst), GFP_ATOMIC);
			अगर (!dst)
				जारी;
			ath10k_wmi_10_4_pull_vdev_stats(src, dst);
			list_add_tail(&dst->list, &stats->vdevs);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_wmi_event_update_stats(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_UPDATE_STATS_EVENTID\n");
	ath10k_debug_fw_stats_process(ar, skb);
पूर्ण

अटल पूर्णांक
ath10k_wmi_op_pull_vdev_start_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				 काष्ठा wmi_vdev_start_ev_arg *arg)
अणु
	काष्ठा wmi_vdev_start_response_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->vdev_id = ev->vdev_id;
	arg->req_id = ev->req_id;
	arg->resp_type = ev->resp_type;
	arg->status = ev->status;

	वापस 0;
पूर्ण

व्योम ath10k_wmi_event_vdev_start_resp(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_vdev_start_ev_arg arg = अणुपूर्ण;
	पूर्णांक ret;
	u32 status;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_START_RESP_EVENTID\n");

	ar->last_wmi_vdev_start_status = 0;

	ret = ath10k_wmi_pull_vdev_start(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse vdev start event: %d\n", ret);
		ar->last_wmi_vdev_start_status = ret;
		जाओ out;
	पूर्ण

	status = __le32_to_cpu(arg.status);
	अगर (WARN_ON_ONCE(status)) अणु
		ath10k_warn(ar, "vdev-start-response reports status error: %d (%s)\n",
			    status, (status == WMI_VDEV_START_CHAN_INVALID) ?
			    "chan-invalid" : "unknown");
		/* Setup is करोne one way or another though, so we should still
		 * करो the completion, so करोn't वापस here.
		 */
		ar->last_wmi_vdev_start_status = -EINVAL;
	पूर्ण

out:
	complete(&ar->vdev_setup_करोne);
पूर्ण

व्योम ath10k_wmi_event_vdev_stopped(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_STOPPED_EVENTID\n");
	complete(&ar->vdev_setup_करोne);
पूर्ण

अटल पूर्णांक
ath10k_wmi_op_pull_peer_kick_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				काष्ठा wmi_peer_kick_ev_arg *arg)
अणु
	काष्ठा wmi_peer_sta_kickout_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->mac_addr = ev->peer_macaddr.addr;

	वापस 0;
पूर्ण

व्योम ath10k_wmi_event_peer_sta_kickout(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_peer_kick_ev_arg arg = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_peer_kick(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse peer kickout event: %d\n",
			    ret);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_STA, "wmi event peer sta kickout %pM\n",
		   arg.mac_addr);

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta_by_अगरaddr(ar->hw, arg.mac_addr, शून्य);
	अगर (!sta) अणु
		ath10k_warn(ar, "Spurious quick kickout for STA %pM\n",
			    arg.mac_addr);
		जाओ निकास;
	पूर्ण

	ieee80211_report_low_ack(sta, 10);

निकास:
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * FIXME
 *
 * We करोn't report to mac80211 sleep state of connected
 * stations. Due to this mac80211 can't fill in TIM IE
 * correctly.
 *
 * I know of no way of getting nullfunc frames that contain
 * sleep transition from connected stations - these करो not
 * seem to be sent from the target to the host. There also
 * करोesn't seem to be a dedicated event क्रम that. So the
 * only way left to करो this would be to पढ़ो tim_biपंचांगap
 * during SWBA.
 *
 * We could probably try using tim_biपंचांगap from SWBA to tell
 * mac80211 which stations are asleep and which are not. The
 * problem here is calling mac80211 functions so many बार
 * could take too दीर्घ and make us miss the समय to submit
 * the beacon to the target.
 *
 * So as a workaround we try to extend the TIM IE अगर there
 * is unicast buffered क्रम stations with aid > 7 and fill it
 * in ourselves.
 */
अटल व्योम ath10k_wmi_update_tim(काष्ठा ath10k *ar,
				  काष्ठा ath10k_vअगर *arvअगर,
				  काष्ठा sk_buff *bcn,
				  स्थिर काष्ठा wmi_tim_info_arg *tim_info)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)bcn->data;
	काष्ठा ieee80211_tim_ie *tim;
	u8 *ies, *ie;
	u8 ie_len, pvm_len;
	__le32 t;
	u32 v, tim_len;

	/* When FW reports 0 in tim_len, ensure atleast first byte
	 * in tim_biपंचांगap is considered क्रम pvm calculation.
	 */
	tim_len = tim_info->tim_len ? __le32_to_cpu(tim_info->tim_len) : 1;

	/* अगर next SWBA has no tim_changed the tim_biपंचांगap is garbage.
	 * we must copy the biपंचांगap upon change and reuse it later
	 */
	अगर (__le32_to_cpu(tim_info->tim_changed)) अणु
		पूर्णांक i;

		अगर (माप(arvअगर->u.ap.tim_biपंचांगap) < tim_len) अणु
			ath10k_warn(ar, "SWBA TIM field is too big (%u), truncated it to %zu",
				    tim_len, माप(arvअगर->u.ap.tim_biपंचांगap));
			tim_len = माप(arvअगर->u.ap.tim_biपंचांगap);
		पूर्ण

		क्रम (i = 0; i < tim_len; i++) अणु
			t = tim_info->tim_biपंचांगap[i / 4];
			v = __le32_to_cpu(t);
			arvअगर->u.ap.tim_biपंचांगap[i] = (v >> ((i % 4) * 8)) & 0xFF;
		पूर्ण

		/* FW reports either length 0 or length based on max supported
		 * station. so we calculate this on our own
		 */
		arvअगर->u.ap.tim_len = 0;
		क्रम (i = 0; i < tim_len; i++)
			अगर (arvअगर->u.ap.tim_biपंचांगap[i])
				arvअगर->u.ap.tim_len = i;

		arvअगर->u.ap.tim_len++;
	पूर्ण

	ies = bcn->data;
	ies += ieee80211_hdrlen(hdr->frame_control);
	ies += 12; /* fixed parameters */

	ie = (u8 *)cfg80211_find_ie(WLAN_EID_TIM, ies,
				    (u8 *)skb_tail_poपूर्णांकer(bcn) - ies);
	अगर (!ie) अणु
		अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_IBSS)
			ath10k_warn(ar, "no tim ie found;\n");
		वापस;
	पूर्ण

	tim = (व्योम *)ie + 2;
	ie_len = ie[1];
	pvm_len = ie_len - 3; /* exclude dtim count, dtim period, bmap ctl */

	अगर (pvm_len < arvअगर->u.ap.tim_len) अणु
		पूर्णांक expand_size = tim_len - pvm_len;
		पूर्णांक move_size = skb_tail_poपूर्णांकer(bcn) - (ie + 2 + ie_len);
		व्योम *next_ie = ie + 2 + ie_len;

		अगर (skb_put(bcn, expand_size)) अणु
			स_हटाओ(next_ie + expand_size, next_ie, move_size);

			ie[1] += expand_size;
			ie_len += expand_size;
			pvm_len += expand_size;
		पूर्ण अन्यथा अणु
			ath10k_warn(ar, "tim expansion failed\n");
		पूर्ण
	पूर्ण

	अगर (pvm_len > tim_len) अणु
		ath10k_warn(ar, "tim pvm length is too great (%d)\n", pvm_len);
		वापस;
	पूर्ण

	tim->biपंचांगap_ctrl = !!__le32_to_cpu(tim_info->tim_mcast);
	स_नकल(tim->भव_map, arvअगर->u.ap.tim_biपंचांगap, pvm_len);

	अगर (tim->dtim_count == 0) अणु
		ATH10K_SKB_CB(bcn)->flags |= ATH10K_SKB_F_DTIM_ZERO;

		अगर (__le32_to_cpu(tim_info->tim_mcast) == 1)
			ATH10K_SKB_CB(bcn)->flags |= ATH10K_SKB_F_DELIVER_CAB;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MGMT, "dtim %d/%d mcast %d pvmlen %d\n",
		   tim->dtim_count, tim->dtim_period,
		   tim->biपंचांगap_ctrl, pvm_len);
पूर्ण

अटल व्योम ath10k_wmi_update_noa(काष्ठा ath10k *ar, काष्ठा ath10k_vअगर *arvअगर,
				  काष्ठा sk_buff *bcn,
				  स्थिर काष्ठा wmi_p2p_noa_info *noa)
अणु
	अगर (!arvअगर->vअगर->p2p)
		वापस;

	ath10k_dbg(ar, ATH10K_DBG_MGMT, "noa changed: %d\n", noa->changed);

	अगर (noa->changed & WMI_P2P_NOA_CHANGED_BIT)
		ath10k_p2p_noa_update(arvअगर, noa);

	अगर (arvअगर->u.ap.noa_data)
		अगर (!pskb_expand_head(bcn, 0, arvअगर->u.ap.noa_len, GFP_ATOMIC))
			skb_put_data(bcn, arvअगर->u.ap.noa_data,
				     arvअगर->u.ap.noa_len);
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_swba_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				      काष्ठा wmi_swba_ev_arg *arg)
अणु
	काष्ठा wmi_host_swba_event *ev = (व्योम *)skb->data;
	u32 map;
	माप_प्रकार i;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->vdev_map = ev->vdev_map;

	क्रम (i = 0, map = __le32_to_cpu(ev->vdev_map); map; map >>= 1) अणु
		अगर (!(map & BIT(0)))
			जारी;

		/* If this happens there were some changes in firmware and
		 * ath10k should update the max size of tim_info array.
		 */
		अगर (WARN_ON_ONCE(i == ARRAY_SIZE(arg->tim_info)))
			अवरोध;

		अगर (__le32_to_cpu(ev->bcn_info[i].tim_info.tim_len) >
		     माप(ev->bcn_info[i].tim_info.tim_biपंचांगap)) अणु
			ath10k_warn(ar, "refusing to parse invalid swba structure\n");
			वापस -EPROTO;
		पूर्ण

		arg->tim_info[i].tim_len = ev->bcn_info[i].tim_info.tim_len;
		arg->tim_info[i].tim_mcast = ev->bcn_info[i].tim_info.tim_mcast;
		arg->tim_info[i].tim_biपंचांगap =
				ev->bcn_info[i].tim_info.tim_biपंचांगap;
		arg->tim_info[i].tim_changed =
				ev->bcn_info[i].tim_info.tim_changed;
		arg->tim_info[i].tim_num_ps_pending =
				ev->bcn_info[i].tim_info.tim_num_ps_pending;

		arg->noa_info[i] = &ev->bcn_info[i].p2p_noa_info;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_2_4_op_pull_swba_ev(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb,
					     काष्ठा wmi_swba_ev_arg *arg)
अणु
	काष्ठा wmi_10_2_4_host_swba_event *ev = (व्योम *)skb->data;
	u32 map;
	माप_प्रकार i;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->vdev_map = ev->vdev_map;

	क्रम (i = 0, map = __le32_to_cpu(ev->vdev_map); map; map >>= 1) अणु
		अगर (!(map & BIT(0)))
			जारी;

		/* If this happens there were some changes in firmware and
		 * ath10k should update the max size of tim_info array.
		 */
		अगर (WARN_ON_ONCE(i == ARRAY_SIZE(arg->tim_info)))
			अवरोध;

		अगर (__le32_to_cpu(ev->bcn_info[i].tim_info.tim_len) >
		     माप(ev->bcn_info[i].tim_info.tim_biपंचांगap)) अणु
			ath10k_warn(ar, "refusing to parse invalid swba structure\n");
			वापस -EPROTO;
		पूर्ण

		arg->tim_info[i].tim_len = ev->bcn_info[i].tim_info.tim_len;
		arg->tim_info[i].tim_mcast = ev->bcn_info[i].tim_info.tim_mcast;
		arg->tim_info[i].tim_biपंचांगap =
				ev->bcn_info[i].tim_info.tim_biपंचांगap;
		arg->tim_info[i].tim_changed =
				ev->bcn_info[i].tim_info.tim_changed;
		arg->tim_info[i].tim_num_ps_pending =
				ev->bcn_info[i].tim_info.tim_num_ps_pending;
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_pull_swba_ev(काष्ठा ath10k *ar,
					   काष्ठा sk_buff *skb,
					   काष्ठा wmi_swba_ev_arg *arg)
अणु
	काष्ठा wmi_10_4_host_swba_event *ev = (व्योम *)skb->data;
	u32 map, tim_len;
	माप_प्रकार i;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->vdev_map = ev->vdev_map;

	क्रम (i = 0, map = __le32_to_cpu(ev->vdev_map); map; map >>= 1) अणु
		अगर (!(map & BIT(0)))
			जारी;

		/* If this happens there were some changes in firmware and
		 * ath10k should update the max size of tim_info array.
		 */
		अगर (WARN_ON_ONCE(i == ARRAY_SIZE(arg->tim_info)))
			अवरोध;

		अगर (__le32_to_cpu(ev->bcn_info[i].tim_info.tim_len) >
		      माप(ev->bcn_info[i].tim_info.tim_biपंचांगap)) अणु
			ath10k_warn(ar, "refusing to parse invalid swba structure\n");
			वापस -EPROTO;
		पूर्ण

		tim_len = __le32_to_cpu(ev->bcn_info[i].tim_info.tim_len);
		अगर (tim_len) अणु
			/* Exclude 4 byte guard length */
			tim_len -= 4;
			arg->tim_info[i].tim_len = __cpu_to_le32(tim_len);
		पूर्ण अन्यथा अणु
			arg->tim_info[i].tim_len = 0;
		पूर्ण

		arg->tim_info[i].tim_mcast = ev->bcn_info[i].tim_info.tim_mcast;
		arg->tim_info[i].tim_biपंचांगap =
				ev->bcn_info[i].tim_info.tim_biपंचांगap;
		arg->tim_info[i].tim_changed =
				ev->bcn_info[i].tim_info.tim_changed;
		arg->tim_info[i].tim_num_ps_pending =
				ev->bcn_info[i].tim_info.tim_num_ps_pending;

		/* 10.4 firmware करोesn't have p2p support. notice of असलence
		 * info can be ignored क्रम now.
		 */

		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत wmi_txbf_conf ath10k_wmi_10_4_txbf_conf_scheme(काष्ठा ath10k *ar)
अणु
	वापस WMI_TXBF_CONF_BEFORE_ASSOC;
पूर्ण

व्योम ath10k_wmi_event_host_swba(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_swba_ev_arg arg = अणुपूर्ण;
	u32 map;
	पूर्णांक i = -1;
	स्थिर काष्ठा wmi_tim_info_arg *tim_info;
	स्थिर काष्ठा wmi_p2p_noa_info *noa_info;
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा sk_buff *bcn;
	dma_addr_t paddr;
	पूर्णांक ret, vdev_id = 0;

	ret = ath10k_wmi_pull_swba(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse swba event: %d\n", ret);
		वापस;
	पूर्ण

	map = __le32_to_cpu(arg.vdev_map);

	ath10k_dbg(ar, ATH10K_DBG_MGMT, "mgmt swba vdev_map 0x%x\n",
		   map);

	क्रम (; map; map >>= 1, vdev_id++) अणु
		अगर (!(map & 0x1))
			जारी;

		i++;

		अगर (i >= WMI_MAX_AP_VDEV) अणु
			ath10k_warn(ar, "swba has corrupted vdev map\n");
			अवरोध;
		पूर्ण

		tim_info = &arg.tim_info[i];
		noa_info = arg.noa_info[i];

		ath10k_dbg(ar, ATH10K_DBG_MGMT,
			   "mgmt event bcn_info %d tim_len %d mcast %d changed %d num_ps_pending %d bitmap 0x%08x%08x%08x%08x\n",
			   i,
			   __le32_to_cpu(tim_info->tim_len),
			   __le32_to_cpu(tim_info->tim_mcast),
			   __le32_to_cpu(tim_info->tim_changed),
			   __le32_to_cpu(tim_info->tim_num_ps_pending),
			   __le32_to_cpu(tim_info->tim_biपंचांगap[3]),
			   __le32_to_cpu(tim_info->tim_biपंचांगap[2]),
			   __le32_to_cpu(tim_info->tim_biपंचांगap[1]),
			   __le32_to_cpu(tim_info->tim_biपंचांगap[0]));

		/* TODO: Only first 4 word from tim_biपंचांगap is dumped.
		 * Extend debug code to dump full tim_biपंचांगap.
		 */

		arvअगर = ath10k_get_arvअगर(ar, vdev_id);
		अगर (arvअगर == शून्य) अणु
			ath10k_warn(ar, "no vif for vdev_id %d found\n",
				    vdev_id);
			जारी;
		पूर्ण

		/* mac80211 would have alपढ़ोy asked us to stop beaconing and
		 * bring the vdev करोwn, so जारी in that हाल
		 */
		अगर (!arvअगर->is_up)
			जारी;

		/* There are no completions क्रम beacons so रुको क्रम next SWBA
		 * beक्रमe telling mac80211 to decrement CSA counter
		 *
		 * Once CSA counter is completed stop sending beacons until
		 * actual channel चयन is करोne
		 */
		अगर (arvअगर->vअगर->csa_active &&
		    ieee80211_beacon_cntdwn_is_complete(arvअगर->vअगर)) अणु
			ieee80211_csa_finish(arvअगर->vअगर);
			जारी;
		पूर्ण

		bcn = ieee80211_beacon_get(ar->hw, arvअगर->vअगर);
		अगर (!bcn) अणु
			ath10k_warn(ar, "could not get mac80211 beacon\n");
			जारी;
		पूर्ण

		ath10k_tx_h_seq_no(arvअगर->vअगर, bcn);
		ath10k_wmi_update_tim(ar, arvअगर, bcn, tim_info);
		ath10k_wmi_update_noa(ar, arvअगर, bcn, noa_info);

		spin_lock_bh(&ar->data_lock);

		अगर (arvअगर->beacon) अणु
			चयन (arvअगर->beacon_state) अणु
			हाल ATH10K_BEACON_SENT:
				अवरोध;
			हाल ATH10K_BEACON_SCHEDULED:
				ath10k_warn(ar, "SWBA overrun on vdev %d, skipped old beacon\n",
					    arvअगर->vdev_id);
				अवरोध;
			हाल ATH10K_BEACON_SENDING:
				ath10k_warn(ar, "SWBA overrun on vdev %d, skipped new beacon\n",
					    arvअगर->vdev_id);
				dev_kमुक्त_skb(bcn);
				जाओ skip;
			पूर्ण

			ath10k_mac_vअगर_beacon_मुक्त(arvअगर);
		पूर्ण

		अगर (!arvअगर->beacon_buf) अणु
			paddr = dma_map_single(arvअगर->ar->dev, bcn->data,
					       bcn->len, DMA_TO_DEVICE);
			ret = dma_mapping_error(arvअगर->ar->dev, paddr);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to map beacon: %d\n",
					    ret);
				dev_kमुक्त_skb_any(bcn);
				जाओ skip;
			पूर्ण

			ATH10K_SKB_CB(bcn)->paddr = paddr;
		पूर्ण अन्यथा अणु
			अगर (bcn->len > IEEE80211_MAX_FRAME_LEN) अणु
				ath10k_warn(ar, "trimming beacon %d -> %d bytes!\n",
					    bcn->len, IEEE80211_MAX_FRAME_LEN);
				skb_trim(bcn, IEEE80211_MAX_FRAME_LEN);
			पूर्ण
			स_नकल(arvअगर->beacon_buf, bcn->data, bcn->len);
			ATH10K_SKB_CB(bcn)->paddr = arvअगर->beacon_paddr;
		पूर्ण

		arvअगर->beacon = bcn;
		arvअगर->beacon_state = ATH10K_BEACON_SCHEDULED;

		trace_ath10k_tx_hdr(ar, bcn->data, bcn->len);
		trace_ath10k_tx_payload(ar, bcn->data, bcn->len);

skip:
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	ath10k_wmi_tx_beacons_noरुको(ar);
पूर्ण

व्योम ath10k_wmi_event_tbttoffset_update(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_TBTTOFFSET_UPDATE_EVENTID\n");
पूर्ण

अटल व्योम ath10k_radar_detected(काष्ठा ath10k *ar)
अणु
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs radar detected\n");
	ATH10K_DFS_STAT_INC(ar, radar_detected);

	/* Control radar events reporting in debugfs file
	 * dfs_block_radar_events
	 */
	अगर (ar->dfs_block_radar_events)
		ath10k_info(ar, "DFS Radar detected, but ignored as requested\n");
	अन्यथा
		ieee80211_radar_detected(ar->hw);
पूर्ण

अटल व्योम ath10k_radar_confirmation_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k,
					 radar_confirmation_work);
	काष्ठा ath10k_radar_found_info radar_info;
	पूर्णांक ret, समय_left;

	reinit_completion(&ar->wmi.radar_confirm);

	spin_lock_bh(&ar->data_lock);
	स_नकल(&radar_info, &ar->last_radar_info, माप(radar_info));
	spin_unlock_bh(&ar->data_lock);

	ret = ath10k_wmi_report_radar_found(ar, &radar_info);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send radar found %d\n", ret);
		जाओ रुको_complete;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->wmi.radar_confirm,
						ATH10K_WMI_DFS_CONF_TIMEOUT_HZ);
	अगर (समय_left) अणु
		/* DFS Confirmation status event received and
		 * necessary action completed.
		 */
		जाओ रुको_complete;
	पूर्ण अन्यथा अणु
		/* DFS Confirmation event not received from FW.Considering this
		 * as real radar.
		 */
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
			   "dfs confirmation not received from fw, considering as radar\n");
		जाओ radar_detected;
	पूर्ण

radar_detected:
	ath10k_radar_detected(ar);

	/* Reset state to allow sending confirmation on consecutive radar
	 * detections, unless radar confirmation is disabled/stopped.
	 */
रुको_complete:
	spin_lock_bh(&ar->data_lock);
	अगर (ar->radar_conf_state != ATH10K_RADAR_CONFIRMATION_STOPPED)
		ar->radar_conf_state = ATH10K_RADAR_CONFIRMATION_IDLE;
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल व्योम ath10k_dfs_radar_report(काष्ठा ath10k *ar,
				    काष्ठा wmi_phyerr_ev_arg *phyerr,
				    स्थिर काष्ठा phyerr_radar_report *rr,
				    u64 tsf)
अणु
	u32 reg0, reg1, tsf32l;
	काष्ठा ieee80211_channel *ch;
	काष्ठा pulse_event pe;
	काष्ठा radar_detector_specs rs;
	u64 tsf64;
	u8 rssi, width;
	काष्ठा ath10k_radar_found_info *radar_info;

	reg0 = __le32_to_cpu(rr->reg0);
	reg1 = __le32_to_cpu(rr->reg1);

	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr radar report chirp %d max_width %d agc_total_gain %d pulse_delta_diff %d\n",
		   MS(reg0, RADAR_REPORT_REG0_PULSE_IS_CHIRP),
		   MS(reg0, RADAR_REPORT_REG0_PULSE_IS_MAX_WIDTH),
		   MS(reg0, RADAR_REPORT_REG0_AGC_TOTAL_GAIN),
		   MS(reg0, RADAR_REPORT_REG0_PULSE_DELTA_DIFF));
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr radar report pulse_delta_pean %d pulse_sidx %d fft_valid %d agc_mb_gain %d subchan_mask %d\n",
		   MS(reg0, RADAR_REPORT_REG0_PULSE_DELTA_PEAK),
		   MS(reg0, RADAR_REPORT_REG0_PULSE_SIDX),
		   MS(reg1, RADAR_REPORT_REG1_PULSE_SRCH_FFT_VALID),
		   MS(reg1, RADAR_REPORT_REG1_PULSE_AGC_MB_GAIN),
		   MS(reg1, RADAR_REPORT_REG1_PULSE_SUBCHAN_MASK));
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr radar report pulse_tsf_offset 0x%X pulse_dur: %d\n",
		   MS(reg1, RADAR_REPORT_REG1_PULSE_TSF_OFFSET),
		   MS(reg1, RADAR_REPORT_REG1_PULSE_DUR));

	अगर (!ar->dfs_detector)
		वापस;

	spin_lock_bh(&ar->data_lock);
	ch = ar->rx_channel;

	/* fetch target operating channel during channel change */
	अगर (!ch)
		ch = ar->tgt_oper_chan;

	spin_unlock_bh(&ar->data_lock);

	अगर (!ch) अणु
		ath10k_warn(ar, "failed to derive channel for radar pulse, treating as radar\n");
		जाओ radar_detected;
	पूर्ण

	/* report event to DFS pattern detector */
	tsf32l = phyerr->tsf_बारtamp;
	tsf64 = tsf & (~0xFFFFFFFFULL);
	tsf64 |= tsf32l;

	width = MS(reg1, RADAR_REPORT_REG1_PULSE_DUR);
	rssi = phyerr->rssi_combined;

	/* hardware store this as 8 bit चिन्हित value,
	 * set to zero अगर negative number
	 */
	अगर (rssi & 0x80)
		rssi = 0;

	pe.ts = tsf64;
	pe.freq = ch->center_freq;
	pe.width = width;
	pe.rssi = rssi;
	pe.chirp = (MS(reg0, RADAR_REPORT_REG0_PULSE_IS_CHIRP) != 0);
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "dfs add pulse freq: %d, width: %d, rssi %d, tsf: %llX\n",
		   pe.freq, pe.width, pe.rssi, pe.ts);

	ATH10K_DFS_STAT_INC(ar, pulses_detected);

	अगर (!ar->dfs_detector->add_pulse(ar->dfs_detector, &pe, &rs)) अणु
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
			   "dfs no pulse pattern detected, yet\n");
		वापस;
	पूर्ण

	अगर ((test_bit(WMI_SERVICE_HOST_DFS_CHECK_SUPPORT, ar->wmi.svc_map)) &&
	    ar->dfs_detector->region == NL80211_DFS_FCC) अणु
		/* Consecutive radar indications need not be
		 * sent to the firmware until we get confirmation
		 * क्रम the previous detected radar.
		 */
		spin_lock_bh(&ar->data_lock);
		अगर (ar->radar_conf_state != ATH10K_RADAR_CONFIRMATION_IDLE) अणु
			spin_unlock_bh(&ar->data_lock);
			वापस;
		पूर्ण
		ar->radar_conf_state = ATH10K_RADAR_CONFIRMATION_INPROGRESS;
		radar_info = &ar->last_radar_info;

		radar_info->pri_min = rs.pri_min;
		radar_info->pri_max = rs.pri_max;
		radar_info->width_min = rs.width_min;
		radar_info->width_max = rs.width_max;
		/*TODO Find sidx_min and sidx_max */
		radar_info->sidx_min = MS(reg0, RADAR_REPORT_REG0_PULSE_SIDX);
		radar_info->sidx_max = MS(reg0, RADAR_REPORT_REG0_PULSE_SIDX);

		ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
			   "sending wmi radar found cmd pri_min %d pri_max %d width_min %d width_max %d sidx_min %d sidx_max %d\n",
			   radar_info->pri_min, radar_info->pri_max,
			   radar_info->width_min, radar_info->width_max,
			   radar_info->sidx_min, radar_info->sidx_max);
		ieee80211_queue_work(ar->hw, &ar->radar_confirmation_work);
		spin_unlock_bh(&ar->data_lock);
		वापस;
	पूर्ण

radar_detected:
	ath10k_radar_detected(ar);
पूर्ण

अटल पूर्णांक ath10k_dfs_fft_report(काष्ठा ath10k *ar,
				 काष्ठा wmi_phyerr_ev_arg *phyerr,
				 स्थिर काष्ठा phyerr_fft_report *fftr,
				 u64 tsf)
अणु
	u32 reg0, reg1;
	u8 rssi, peak_mag;

	reg0 = __le32_to_cpu(fftr->reg0);
	reg1 = __le32_to_cpu(fftr->reg1);
	rssi = phyerr->rssi_combined;

	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr fft report total_gain_db %d base_pwr_db %d fft_chn_idx %d peak_sidx %d\n",
		   MS(reg0, SEARCH_FFT_REPORT_REG0_TOTAL_GAIN_DB),
		   MS(reg0, SEARCH_FFT_REPORT_REG0_BASE_PWR_DB),
		   MS(reg0, SEARCH_FFT_REPORT_REG0_FFT_CHN_IDX),
		   MS(reg0, SEARCH_FFT_REPORT_REG0_PEAK_SIDX));
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi phyerr fft report rel_pwr_db %d avgpwr_db %d peak_mag %d num_store_bin %d\n",
		   MS(reg1, SEARCH_FFT_REPORT_REG1_RELPWR_DB),
		   MS(reg1, SEARCH_FFT_REPORT_REG1_AVGPWR_DB),
		   MS(reg1, SEARCH_FFT_REPORT_REG1_PEAK_MAG),
		   MS(reg1, SEARCH_FFT_REPORT_REG1_NUM_STR_BINS_IB));

	peak_mag = MS(reg1, SEARCH_FFT_REPORT_REG1_PEAK_MAG);

	/* false event detection */
	अगर (rssi == DFS_RSSI_POSSIBLY_FALSE &&
	    peak_mag < 2 * DFS_PEAK_MAG_THOLD_POSSIBLY_FALSE) अणु
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs false pulse detected\n");
		ATH10K_DFS_STAT_INC(ar, pulses_discarded);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_wmi_event_dfs(काष्ठा ath10k *ar,
			  काष्ठा wmi_phyerr_ev_arg *phyerr,
			  u64 tsf)
अणु
	पूर्णांक buf_len, tlv_len, res, i = 0;
	स्थिर काष्ठा phyerr_tlv *tlv;
	स्थिर काष्ठा phyerr_radar_report *rr;
	स्थिर काष्ठा phyerr_fft_report *fftr;
	स्थिर u8 *tlv_buf;

	buf_len = phyerr->buf_len;
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "wmi event dfs err_code %d rssi %d tsfl 0x%X tsf64 0x%llX len %d\n",
		   phyerr->phy_err_code, phyerr->rssi_combined,
		   phyerr->tsf_बारtamp, tsf, buf_len);

	/* Skip event अगर DFS disabled */
	अगर (!IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED))
		वापस;

	ATH10K_DFS_STAT_INC(ar, pulses_total);

	जबतक (i < buf_len) अणु
		अगर (i + माप(*tlv) > buf_len) अणु
			ath10k_warn(ar, "too short buf for tlv header (%d)\n",
				    i);
			वापस;
		पूर्ण

		tlv = (काष्ठा phyerr_tlv *)&phyerr->buf[i];
		tlv_len = __le16_to_cpu(tlv->len);
		tlv_buf = &phyerr->buf[i + माप(*tlv)];
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
			   "wmi event dfs tlv_len %d tlv_tag 0x%02X tlv_sig 0x%02X\n",
			   tlv_len, tlv->tag, tlv->sig);

		चयन (tlv->tag) अणु
		हाल PHYERR_TLV_TAG_RADAR_PULSE_SUMMARY:
			अगर (i + माप(*tlv) + माप(*rr) > buf_len) अणु
				ath10k_warn(ar, "too short radar pulse summary (%d)\n",
					    i);
				वापस;
			पूर्ण

			rr = (काष्ठा phyerr_radar_report *)tlv_buf;
			ath10k_dfs_radar_report(ar, phyerr, rr, tsf);
			अवरोध;
		हाल PHYERR_TLV_TAG_SEARCH_FFT_REPORT:
			अगर (i + माप(*tlv) + माप(*fftr) > buf_len) अणु
				ath10k_warn(ar, "too short fft report (%d)\n",
					    i);
				वापस;
			पूर्ण

			fftr = (काष्ठा phyerr_fft_report *)tlv_buf;
			res = ath10k_dfs_fft_report(ar, phyerr, fftr, tsf);
			अगर (res)
				वापस;
			अवरोध;
		पूर्ण

		i += माप(*tlv) + tlv_len;
	पूर्ण
पूर्ण

व्योम ath10k_wmi_event_spectral_scan(काष्ठा ath10k *ar,
				    काष्ठा wmi_phyerr_ev_arg *phyerr,
				    u64 tsf)
अणु
	पूर्णांक buf_len, tlv_len, res, i = 0;
	काष्ठा phyerr_tlv *tlv;
	स्थिर व्योम *tlv_buf;
	स्थिर काष्ठा phyerr_fft_report *fftr;
	माप_प्रकार fftr_len;

	buf_len = phyerr->buf_len;

	जबतक (i < buf_len) अणु
		अगर (i + माप(*tlv) > buf_len) अणु
			ath10k_warn(ar, "failed to parse phyerr tlv header at byte %d\n",
				    i);
			वापस;
		पूर्ण

		tlv = (काष्ठा phyerr_tlv *)&phyerr->buf[i];
		tlv_len = __le16_to_cpu(tlv->len);
		tlv_buf = &phyerr->buf[i + माप(*tlv)];

		अगर (i + माप(*tlv) + tlv_len > buf_len) अणु
			ath10k_warn(ar, "failed to parse phyerr tlv payload at byte %d\n",
				    i);
			वापस;
		पूर्ण

		चयन (tlv->tag) अणु
		हाल PHYERR_TLV_TAG_SEARCH_FFT_REPORT:
			अगर (माप(*fftr) > tlv_len) अणु
				ath10k_warn(ar, "failed to parse fft report at byte %d\n",
					    i);
				वापस;
			पूर्ण

			fftr_len = tlv_len - माप(*fftr);
			fftr = tlv_buf;
			res = ath10k_spectral_process_fft(ar, phyerr,
							  fftr, fftr_len,
							  tsf);
			अगर (res < 0) अणु
				ath10k_dbg(ar, ATH10K_DBG_WMI, "failed to process fft report: %d\n",
					   res);
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण

		i += माप(*tlv) + tlv_len;
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_phyerr_ev_hdr(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb,
					    काष्ठा wmi_phyerr_hdr_arg *arg)
अणु
	काष्ठा wmi_phyerr_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	arg->num_phyerrs = __le32_to_cpu(ev->num_phyerrs);
	arg->tsf_l32 = __le32_to_cpu(ev->tsf_l32);
	arg->tsf_u32 = __le32_to_cpu(ev->tsf_u32);
	arg->buf_len = skb->len - माप(*ev);
	arg->phyerrs = ev->phyerrs;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_pull_phyerr_ev_hdr(काष्ठा ath10k *ar,
						 काष्ठा sk_buff *skb,
						 काष्ठा wmi_phyerr_hdr_arg *arg)
अणु
	काष्ठा wmi_10_4_phyerr_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	/* 10.4 firmware always reports only one phyerr */
	arg->num_phyerrs = 1;

	arg->tsf_l32 = __le32_to_cpu(ev->tsf_l32);
	arg->tsf_u32 = __le32_to_cpu(ev->tsf_u32);
	arg->buf_len = skb->len;
	arg->phyerrs = skb->data;

	वापस 0;
पूर्ण

पूर्णांक ath10k_wmi_op_pull_phyerr_ev(काष्ठा ath10k *ar,
				 स्थिर व्योम *phyerr_buf,
				 पूर्णांक left_len,
				 काष्ठा wmi_phyerr_ev_arg *arg)
अणु
	स्थिर काष्ठा wmi_phyerr *phyerr = phyerr_buf;
	पूर्णांक i;

	अगर (left_len < माप(*phyerr)) अणु
		ath10k_warn(ar, "wrong phyerr event head len %d (need: >=%zd)\n",
			    left_len, माप(*phyerr));
		वापस -EINVAL;
	पूर्ण

	arg->tsf_बारtamp = __le32_to_cpu(phyerr->tsf_बारtamp);
	arg->freq1 = __le16_to_cpu(phyerr->freq1);
	arg->freq2 = __le16_to_cpu(phyerr->freq2);
	arg->rssi_combined = phyerr->rssi_combined;
	arg->chan_width_mhz = phyerr->chan_width_mhz;
	arg->buf_len = __le32_to_cpu(phyerr->buf_len);
	arg->buf = phyerr->buf;
	arg->hdr_len = माप(*phyerr);

	क्रम (i = 0; i < 4; i++)
		arg->nf_chains[i] = __le16_to_cpu(phyerr->nf_chains[i]);

	चयन (phyerr->phy_err_code) अणु
	हाल PHY_ERROR_GEN_SPECTRAL_SCAN:
		arg->phy_err_code = PHY_ERROR_SPECTRAL_SCAN;
		अवरोध;
	हाल PHY_ERROR_GEN_FALSE_RADAR_EXT:
		arg->phy_err_code = PHY_ERROR_FALSE_RADAR_EXT;
		अवरोध;
	हाल PHY_ERROR_GEN_RADAR:
		arg->phy_err_code = PHY_ERROR_RADAR;
		अवरोध;
	शेष:
		arg->phy_err_code = PHY_ERROR_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_pull_phyerr_ev(काष्ठा ath10k *ar,
					     स्थिर व्योम *phyerr_buf,
					     पूर्णांक left_len,
					     काष्ठा wmi_phyerr_ev_arg *arg)
अणु
	स्थिर काष्ठा wmi_10_4_phyerr_event *phyerr = phyerr_buf;
	u32 phy_err_mask;
	पूर्णांक i;

	अगर (left_len < माप(*phyerr)) अणु
		ath10k_warn(ar, "wrong phyerr event head len %d (need: >=%zd)\n",
			    left_len, माप(*phyerr));
		वापस -EINVAL;
	पूर्ण

	arg->tsf_बारtamp = __le32_to_cpu(phyerr->tsf_बारtamp);
	arg->freq1 = __le16_to_cpu(phyerr->freq1);
	arg->freq2 = __le16_to_cpu(phyerr->freq2);
	arg->rssi_combined = phyerr->rssi_combined;
	arg->chan_width_mhz = phyerr->chan_width_mhz;
	arg->buf_len = __le32_to_cpu(phyerr->buf_len);
	arg->buf = phyerr->buf;
	arg->hdr_len = माप(*phyerr);

	क्रम (i = 0; i < 4; i++)
		arg->nf_chains[i] = __le16_to_cpu(phyerr->nf_chains[i]);

	phy_err_mask = __le32_to_cpu(phyerr->phy_err_mask[0]);

	अगर (phy_err_mask & PHY_ERROR_10_4_SPECTRAL_SCAN_MASK)
		arg->phy_err_code = PHY_ERROR_SPECTRAL_SCAN;
	अन्यथा अगर (phy_err_mask & PHY_ERROR_10_4_RADAR_MASK)
		arg->phy_err_code = PHY_ERROR_RADAR;
	अन्यथा
		arg->phy_err_code = PHY_ERROR_UNKNOWN;

	वापस 0;
पूर्ण

व्योम ath10k_wmi_event_phyerr(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_phyerr_hdr_arg hdr_arg = अणुपूर्ण;
	काष्ठा wmi_phyerr_ev_arg phyerr_arg = अणुपूर्ण;
	स्थिर व्योम *phyerr;
	u32 count, i, buf_len, phy_err_code;
	u64 tsf;
	पूर्णांक left_len, ret;

	ATH10K_DFS_STAT_INC(ar, phy_errors);

	ret = ath10k_wmi_pull_phyerr_hdr(ar, skb, &hdr_arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse phyerr event hdr: %d\n", ret);
		वापस;
	पूर्ण

	/* Check number of included events */
	count = hdr_arg.num_phyerrs;

	left_len = hdr_arg.buf_len;

	tsf = hdr_arg.tsf_u32;
	tsf <<= 32;
	tsf |= hdr_arg.tsf_l32;

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event phyerr count %d tsf64 0x%llX\n",
		   count, tsf);

	phyerr = hdr_arg.phyerrs;
	क्रम (i = 0; i < count; i++) अणु
		ret = ath10k_wmi_pull_phyerr(ar, phyerr, left_len, &phyerr_arg);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to parse phyerr event (%d)\n",
				    i);
			वापस;
		पूर्ण

		left_len -= phyerr_arg.hdr_len;
		buf_len = phyerr_arg.buf_len;
		phy_err_code = phyerr_arg.phy_err_code;

		अगर (left_len < buf_len) अणु
			ath10k_warn(ar, "single event (%d) wrong buf len\n", i);
			वापस;
		पूर्ण

		left_len -= buf_len;

		चयन (phy_err_code) अणु
		हाल PHY_ERROR_RADAR:
			ath10k_wmi_event_dfs(ar, &phyerr_arg, tsf);
			अवरोध;
		हाल PHY_ERROR_SPECTRAL_SCAN:
			ath10k_wmi_event_spectral_scan(ar, &phyerr_arg, tsf);
			अवरोध;
		हाल PHY_ERROR_FALSE_RADAR_EXT:
			ath10k_wmi_event_dfs(ar, &phyerr_arg, tsf);
			ath10k_wmi_event_spectral_scan(ar, &phyerr_arg, tsf);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		phyerr = phyerr + phyerr_arg.hdr_len + buf_len;
	पूर्ण
पूर्ण

अटल पूर्णांक
ath10k_wmi_10_4_op_pull_dfs_status_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				      काष्ठा wmi_dfs_status_ev_arg *arg)
अणु
	काष्ठा wmi_dfs_status_ev_arg *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	arg->status = ev->status;

	वापस 0;
पूर्ण

अटल व्योम
ath10k_wmi_event_dfs_status_check(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_dfs_status_ev_arg status_arg = अणुपूर्ण;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_dfs_status(ar, skb, &status_arg);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse dfs status event: %d\n", ret);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_REGULATORY,
		   "dfs status event received from fw: %d\n",
		   status_arg.status);

	/* Even in हाल of radar detection failure we follow the same
	 * behaviour as अगर radar is detected i.e to चयन to a dअगरferent
	 * channel.
	 */
	अगर (status_arg.status == WMI_HW_RADAR_DETECTED ||
	    status_arg.status == WMI_RADAR_DETECTION_FAIL)
		ath10k_radar_detected(ar);
	complete(&ar->wmi.radar_confirm);
पूर्ण

व्योम ath10k_wmi_event_roam(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_roam_ev_arg arg = अणुपूर्ण;
	पूर्णांक ret;
	u32 vdev_id;
	u32 reason;
	s32 rssi;

	ret = ath10k_wmi_pull_roam_ev(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse roam event: %d\n", ret);
		वापस;
	पूर्ण

	vdev_id = __le32_to_cpu(arg.vdev_id);
	reason = __le32_to_cpu(arg.reason);
	rssi = __le32_to_cpu(arg.rssi);
	rssi += WMI_SPECTRAL_NOISE_FLOOR_REF_DEFAULT;

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi roam event vdev %u reason 0x%08x rssi %d\n",
		   vdev_id, reason, rssi);

	अगर (reason >= WMI_ROAM_REASON_MAX)
		ath10k_warn(ar, "ignoring unknown roam event reason %d on vdev %i\n",
			    reason, vdev_id);

	चयन (reason) अणु
	हाल WMI_ROAM_REASON_BEACON_MISS:
		ath10k_mac_handle_beacon_miss(ar, vdev_id);
		अवरोध;
	हाल WMI_ROAM_REASON_BETTER_AP:
	हाल WMI_ROAM_REASON_LOW_RSSI:
	हाल WMI_ROAM_REASON_SUITABLE_AP_FOUND:
	हाल WMI_ROAM_REASON_HO_FAILED:
		ath10k_warn(ar, "ignoring not implemented roam event reason %d on vdev %i\n",
			    reason, vdev_id);
		अवरोध;
	पूर्ण
पूर्ण

व्योम ath10k_wmi_event_profile_match(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_PROFILE_MATCH\n");
पूर्ण

व्योम ath10k_wmi_event_debug_prपूर्णांक(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	अक्षर buf[101], c;
	पूर्णांक i;

	क्रम (i = 0; i < माप(buf) - 1; i++) अणु
		अगर (i >= skb->len)
			अवरोध;

		c = skb->data[i];

		अगर (c == '\0')
			अवरोध;

		अगर (isascii(c) && है_छाप(c))
			buf[i] = c;
		अन्यथा
			buf[i] = '.';
	पूर्ण

	अगर (i == माप(buf) - 1)
		ath10k_warn(ar, "wmi debug print truncated: %d\n", skb->len);

	/* क्रम some reason the debug prपूर्णांकs end with \न, हटाओ that */
	अगर (skb->data[i - 1] == '\n')
		i--;

	/* the last byte is always reserved क्रम the null अक्षरacter */
	buf[i] = '\0';

	ath10k_dbg(ar, ATH10K_DBG_WMI_PRINT, "wmi print '%s'\n", buf);
पूर्ण

व्योम ath10k_wmi_event_pdev_qvit(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_PDEV_QVIT_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_wlan_profile_data(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_WLAN_PROFILE_DATA_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_rtt_measurement_report(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_RTT_MEASUREMENT_REPORT_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_tsf_measurement_report(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_TSF_MEASUREMENT_REPORT_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_rtt_error_report(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_RTT_ERROR_REPORT_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_wow_wakeup_host(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_wow_ev_arg ev = अणुपूर्ण;
	पूर्णांक ret;

	complete(&ar->wow.wakeup_completed);

	ret = ath10k_wmi_pull_wow_event(ar, skb, &ev);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse wow wakeup event: %d\n", ret);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wow wakeup host reason %s\n",
		   wow_reason(ev.wake_reason));
पूर्ण

व्योम ath10k_wmi_event_dcs_पूर्णांकerference(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_DCS_INTERFERENCE_EVENTID\n");
पूर्ण

अटल u8 ath10k_tpc_config_get_rate(काष्ठा ath10k *ar,
				     काष्ठा wmi_pdev_tpc_config_event *ev,
				     u32 rate_idx, u32 num_chains,
				     u32 rate_code, u8 type)
अणु
	u8 tpc, num_streams, preamble, ch, sपंचांग_idx;

	num_streams = ATH10K_HW_NSS(rate_code);
	preamble = ATH10K_HW_PREAMBLE(rate_code);
	ch = num_chains - 1;

	tpc = min_t(u8, ev->rates_array[rate_idx], ev->max_reg_allow_घात[ch]);

	अगर (__le32_to_cpu(ev->num_tx_chain) <= 1)
		जाओ out;

	अगर (preamble == WMI_RATE_PREAMBLE_CCK)
		जाओ out;

	sपंचांग_idx = num_streams - 1;
	अगर (num_chains <= num_streams)
		जाओ out;

	चयन (type) अणु
	हाल WMI_TPC_TABLE_TYPE_STBC:
		tpc = min_t(u8, tpc,
			    ev->max_reg_allow_घात_agstbc[ch - 1][sपंचांग_idx]);
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_TXBF:
		tpc = min_t(u8, tpc,
			    ev->max_reg_allow_घात_agtxbf[ch - 1][sपंचांग_idx]);
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_CDD:
		tpc = min_t(u8, tpc,
			    ev->max_reg_allow_घात_agcdd[ch - 1][sपंचांग_idx]);
		अवरोध;
	शेष:
		ath10k_warn(ar, "unknown wmi tpc table type: %d\n", type);
		tpc = 0;
		अवरोध;
	पूर्ण

out:
	वापस tpc;
पूर्ण

अटल व्योम ath10k_tpc_config_disp_tables(काष्ठा ath10k *ar,
					  काष्ठा wmi_pdev_tpc_config_event *ev,
					  काष्ठा ath10k_tpc_stats *tpc_stats,
					  u8 *rate_code, u16 *pream_table, u8 type)
अणु
	u32 i, j, pream_idx, flags;
	u8 tpc[WMI_TPC_TX_N_CHAIN];
	अक्षर tpc_value[WMI_TPC_TX_N_CHAIN * WMI_TPC_BUF_SIZE];
	अक्षर buff[WMI_TPC_BUF_SIZE];

	flags = __le32_to_cpu(ev->flags);

	चयन (type) अणु
	हाल WMI_TPC_TABLE_TYPE_CDD:
		अगर (!(flags & WMI_TPC_CONFIG_EVENT_FLAG_TABLE_CDD)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI, "CDD not supported\n");
			tpc_stats->flag[type] = ATH10K_TPC_TABLE_TYPE_FLAG;
			वापस;
		पूर्ण
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_STBC:
		अगर (!(flags & WMI_TPC_CONFIG_EVENT_FLAG_TABLE_STBC)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI, "STBC not supported\n");
			tpc_stats->flag[type] = ATH10K_TPC_TABLE_TYPE_FLAG;
			वापस;
		पूर्ण
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_TXBF:
		अगर (!(flags & WMI_TPC_CONFIG_EVENT_FLAG_TABLE_TXBF)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI, "TXBF not supported\n");
			tpc_stats->flag[type] = ATH10K_TPC_TABLE_TYPE_FLAG;
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "invalid table type in wmi tpc event: %d\n", type);
		वापस;
	पूर्ण

	pream_idx = 0;
	क्रम (i = 0; i < tpc_stats->rate_max; i++) अणु
		स_रखो(tpc_value, 0, माप(tpc_value));
		स_रखो(buff, 0, माप(buff));
		अगर (i == pream_table[pream_idx])
			pream_idx++;

		क्रम (j = 0; j < tpc_stats->num_tx_chain; j++) अणु
			tpc[j] = ath10k_tpc_config_get_rate(ar, ev, i, j + 1,
							    rate_code[i],
							    type);
			snम_लिखो(buff, माप(buff), "%8d ", tpc[j]);
			strlcat(tpc_value, buff, माप(tpc_value));
		पूर्ण
		tpc_stats->tpc_table[type].pream_idx[i] = pream_idx;
		tpc_stats->tpc_table[type].rate_code[i] = rate_code[i];
		स_नकल(tpc_stats->tpc_table[type].tpc_value[i],
		       tpc_value, माप(tpc_value));
	पूर्ण
पूर्ण

व्योम ath10k_wmi_tpc_config_get_rate_code(u8 *rate_code, u16 *pream_table,
					 u32 num_tx_chain)
अणु
	u32 i, j, pream_idx;
	u8 rate_idx;

	/* Create the rate code table based on the chains supported */
	rate_idx = 0;
	pream_idx = 0;

	/* Fill CCK rate code */
	क्रम (i = 0; i < 4; i++) अणु
		rate_code[rate_idx] =
			ATH10K_HW_RATECODE(i, 0, WMI_RATE_PREAMBLE_CCK);
		rate_idx++;
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	/* Fill OFDM rate code */
	क्रम (i = 0; i < 8; i++) अणु
		rate_code[rate_idx] =
			ATH10K_HW_RATECODE(i, 0, WMI_RATE_PREAMBLE_OFDM);
		rate_idx++;
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	/* Fill HT20 rate code */
	क्रम (i = 0; i < num_tx_chain; i++) अणु
		क्रम (j = 0; j < 8; j++) अणु
			rate_code[rate_idx] =
			ATH10K_HW_RATECODE(j, i, WMI_RATE_PREAMBLE_HT);
			rate_idx++;
		पूर्ण
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	/* Fill HT40 rate code */
	क्रम (i = 0; i < num_tx_chain; i++) अणु
		क्रम (j = 0; j < 8; j++) अणु
			rate_code[rate_idx] =
			ATH10K_HW_RATECODE(j, i, WMI_RATE_PREAMBLE_HT);
			rate_idx++;
		पूर्ण
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	/* Fill VHT20 rate code */
	क्रम (i = 0; i < num_tx_chain; i++) अणु
		क्रम (j = 0; j < 10; j++) अणु
			rate_code[rate_idx] =
			ATH10K_HW_RATECODE(j, i, WMI_RATE_PREAMBLE_VHT);
			rate_idx++;
		पूर्ण
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	/* Fill VHT40 rate code */
	क्रम (i = 0; i < num_tx_chain; i++) अणु
		क्रम (j = 0; j < 10; j++) अणु
			rate_code[rate_idx] =
			ATH10K_HW_RATECODE(j, i, WMI_RATE_PREAMBLE_VHT);
			rate_idx++;
		पूर्ण
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	/* Fill VHT80 rate code */
	क्रम (i = 0; i < num_tx_chain; i++) अणु
		क्रम (j = 0; j < 10; j++) अणु
			rate_code[rate_idx] =
			ATH10K_HW_RATECODE(j, i, WMI_RATE_PREAMBLE_VHT);
			rate_idx++;
		पूर्ण
	पूर्ण
	pream_table[pream_idx] = rate_idx;
	pream_idx++;

	rate_code[rate_idx++] =
		ATH10K_HW_RATECODE(0, 0, WMI_RATE_PREAMBLE_CCK);
	rate_code[rate_idx++] =
		ATH10K_HW_RATECODE(0, 0, WMI_RATE_PREAMBLE_OFDM);
	rate_code[rate_idx++] =
		ATH10K_HW_RATECODE(0, 0, WMI_RATE_PREAMBLE_CCK);
	rate_code[rate_idx++] =
		ATH10K_HW_RATECODE(0, 0, WMI_RATE_PREAMBLE_OFDM);
	rate_code[rate_idx++] =
		ATH10K_HW_RATECODE(0, 0, WMI_RATE_PREAMBLE_OFDM);

	pream_table[pream_idx] = ATH10K_TPC_PREAM_TABLE_END;
पूर्ण

व्योम ath10k_wmi_event_pdev_tpc_config(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	u32 num_tx_chain, rate_max;
	u8 rate_code[WMI_TPC_RATE_MAX];
	u16 pream_table[WMI_TPC_PREAM_TABLE_MAX];
	काष्ठा wmi_pdev_tpc_config_event *ev;
	काष्ठा ath10k_tpc_stats *tpc_stats;

	ev = (काष्ठा wmi_pdev_tpc_config_event *)skb->data;

	num_tx_chain = __le32_to_cpu(ev->num_tx_chain);

	अगर (num_tx_chain > WMI_TPC_TX_N_CHAIN) अणु
		ath10k_warn(ar, "number of tx chain is %d greater than TPC configured tx chain %d\n",
			    num_tx_chain, WMI_TPC_TX_N_CHAIN);
		वापस;
	पूर्ण

	rate_max = __le32_to_cpu(ev->rate_max);
	अगर (rate_max > WMI_TPC_RATE_MAX) अणु
		ath10k_warn(ar, "number of rate is %d greater than TPC configured rate %d\n",
			    rate_max, WMI_TPC_RATE_MAX);
		rate_max = WMI_TPC_RATE_MAX;
	पूर्ण

	tpc_stats = kzalloc(माप(*tpc_stats), GFP_ATOMIC);
	अगर (!tpc_stats)
		वापस;

	ath10k_wmi_tpc_config_get_rate_code(rate_code, pream_table,
					    num_tx_chain);

	tpc_stats->chan_freq = __le32_to_cpu(ev->chan_freq);
	tpc_stats->phy_mode = __le32_to_cpu(ev->phy_mode);
	tpc_stats->ctl = __le32_to_cpu(ev->ctl);
	tpc_stats->reg_करोमुख्य = __le32_to_cpu(ev->reg_करोमुख्य);
	tpc_stats->twice_antenna_gain = a_sle32_to_cpu(ev->twice_antenna_gain);
	tpc_stats->twice_antenna_reduction =
		__le32_to_cpu(ev->twice_antenna_reduction);
	tpc_stats->घातer_limit = __le32_to_cpu(ev->घातer_limit);
	tpc_stats->twice_max_rd_घातer = __le32_to_cpu(ev->twice_max_rd_घातer);
	tpc_stats->num_tx_chain = num_tx_chain;
	tpc_stats->rate_max = rate_max;

	ath10k_tpc_config_disp_tables(ar, ev, tpc_stats,
				      rate_code, pream_table,
				      WMI_TPC_TABLE_TYPE_CDD);
	ath10k_tpc_config_disp_tables(ar, ev,  tpc_stats,
				      rate_code, pream_table,
				      WMI_TPC_TABLE_TYPE_STBC);
	ath10k_tpc_config_disp_tables(ar, ev, tpc_stats,
				      rate_code, pream_table,
				      WMI_TPC_TABLE_TYPE_TXBF);

	ath10k_debug_tpc_stats_process(ar, tpc_stats);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event tpc config channel %d mode %d ctl %d regd %d gain %d %d limit %d max_power %d tx_chanins %d rates %d\n",
		   __le32_to_cpu(ev->chan_freq),
		   __le32_to_cpu(ev->phy_mode),
		   __le32_to_cpu(ev->ctl),
		   __le32_to_cpu(ev->reg_करोमुख्य),
		   a_sle32_to_cpu(ev->twice_antenna_gain),
		   __le32_to_cpu(ev->twice_antenna_reduction),
		   __le32_to_cpu(ev->घातer_limit),
		   __le32_to_cpu(ev->twice_max_rd_घातer) / 2,
		   __le32_to_cpu(ev->num_tx_chain),
		   __le32_to_cpu(ev->rate_max));
पूर्ण

अटल u8
ath10k_wmi_tpc_final_get_rate(काष्ठा ath10k *ar,
			      काष्ठा wmi_pdev_tpc_final_table_event *ev,
			      u32 rate_idx, u32 num_chains,
			      u32 rate_code, u8 type, u32 pream_idx)
अणु
	u8 tpc, num_streams, preamble, ch, sपंचांग_idx;
	s8 घात_agcdd, घात_agstbc, घात_agtxbf;
	पूर्णांक pream;

	num_streams = ATH10K_HW_NSS(rate_code);
	preamble = ATH10K_HW_PREAMBLE(rate_code);
	ch = num_chains - 1;
	sपंचांग_idx = num_streams - 1;
	pream = -1;

	अगर (__le32_to_cpu(ev->chan_freq) <= 2483) अणु
		चयन (pream_idx) अणु
		हाल WMI_TPC_PREAM_2GHZ_CCK:
			pream = 0;
			अवरोध;
		हाल WMI_TPC_PREAM_2GHZ_OFDM:
			pream = 1;
			अवरोध;
		हाल WMI_TPC_PREAM_2GHZ_HT20:
		हाल WMI_TPC_PREAM_2GHZ_VHT20:
			pream = 2;
			अवरोध;
		हाल WMI_TPC_PREAM_2GHZ_HT40:
		हाल WMI_TPC_PREAM_2GHZ_VHT40:
			pream = 3;
			अवरोध;
		हाल WMI_TPC_PREAM_2GHZ_VHT80:
			pream = 4;
			अवरोध;
		शेष:
			pream = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (__le32_to_cpu(ev->chan_freq) >= 5180) अणु
		चयन (pream_idx) अणु
		हाल WMI_TPC_PREAM_5GHZ_OFDM:
			pream = 0;
			अवरोध;
		हाल WMI_TPC_PREAM_5GHZ_HT20:
		हाल WMI_TPC_PREAM_5GHZ_VHT20:
			pream = 1;
			अवरोध;
		हाल WMI_TPC_PREAM_5GHZ_HT40:
		हाल WMI_TPC_PREAM_5GHZ_VHT40:
			pream = 2;
			अवरोध;
		हाल WMI_TPC_PREAM_5GHZ_VHT80:
			pream = 3;
			अवरोध;
		हाल WMI_TPC_PREAM_5GHZ_HTCUP:
			pream = 4;
			अवरोध;
		शेष:
			pream = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pream == -1) अणु
		ath10k_warn(ar, "unknown wmi tpc final index and frequency: %u, %u\n",
			    pream_idx, __le32_to_cpu(ev->chan_freq));
		tpc = 0;
		जाओ out;
	पूर्ण

	अगर (pream == 4)
		tpc = min_t(u8, ev->rates_array[rate_idx],
			    ev->max_reg_allow_घात[ch]);
	अन्यथा
		tpc = min_t(u8, min_t(u8, ev->rates_array[rate_idx],
				      ev->max_reg_allow_घात[ch]),
			    ev->ctl_घातer_table[0][pream][sपंचांग_idx]);

	अगर (__le32_to_cpu(ev->num_tx_chain) <= 1)
		जाओ out;

	अगर (preamble == WMI_RATE_PREAMBLE_CCK)
		जाओ out;

	अगर (num_chains <= num_streams)
		जाओ out;

	चयन (type) अणु
	हाल WMI_TPC_TABLE_TYPE_STBC:
		घात_agstbc = ev->max_reg_allow_घात_agstbc[ch - 1][sपंचांग_idx];
		अगर (pream == 4)
			tpc = min_t(u8, tpc, घात_agstbc);
		अन्यथा
			tpc = min_t(u8, min_t(u8, tpc, घात_agstbc),
				    ev->ctl_घातer_table[0][pream][sपंचांग_idx]);
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_TXBF:
		घात_agtxbf = ev->max_reg_allow_घात_agtxbf[ch - 1][sपंचांग_idx];
		अगर (pream == 4)
			tpc = min_t(u8, tpc, घात_agtxbf);
		अन्यथा
			tpc = min_t(u8, min_t(u8, tpc, घात_agtxbf),
				    ev->ctl_घातer_table[1][pream][sपंचांग_idx]);
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_CDD:
		घात_agcdd = ev->max_reg_allow_घात_agcdd[ch - 1][sपंचांग_idx];
		अगर (pream == 4)
			tpc = min_t(u8, tpc, घात_agcdd);
		अन्यथा
			tpc = min_t(u8, min_t(u8, tpc, घात_agcdd),
				    ev->ctl_घातer_table[0][pream][sपंचांग_idx]);
		अवरोध;
	शेष:
		ath10k_warn(ar, "unknown wmi tpc final table type: %d\n", type);
		tpc = 0;
		अवरोध;
	पूर्ण

out:
	वापस tpc;
पूर्ण

अटल व्योम
ath10k_wmi_tpc_stats_final_disp_tables(काष्ठा ath10k *ar,
				       काष्ठा wmi_pdev_tpc_final_table_event *ev,
				       काष्ठा ath10k_tpc_stats_final *tpc_stats,
				       u8 *rate_code, u16 *pream_table, u8 type)
अणु
	u32 i, j, pream_idx, flags;
	u8 tpc[WMI_TPC_TX_N_CHAIN];
	अक्षर tpc_value[WMI_TPC_TX_N_CHAIN * WMI_TPC_BUF_SIZE];
	अक्षर buff[WMI_TPC_BUF_SIZE];

	flags = __le32_to_cpu(ev->flags);

	चयन (type) अणु
	हाल WMI_TPC_TABLE_TYPE_CDD:
		अगर (!(flags & WMI_TPC_CONFIG_EVENT_FLAG_TABLE_CDD)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI, "CDD not supported\n");
			tpc_stats->flag[type] = ATH10K_TPC_TABLE_TYPE_FLAG;
			वापस;
		पूर्ण
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_STBC:
		अगर (!(flags & WMI_TPC_CONFIG_EVENT_FLAG_TABLE_STBC)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI, "STBC not supported\n");
			tpc_stats->flag[type] = ATH10K_TPC_TABLE_TYPE_FLAG;
			वापस;
		पूर्ण
		अवरोध;
	हाल WMI_TPC_TABLE_TYPE_TXBF:
		अगर (!(flags & WMI_TPC_CONFIG_EVENT_FLAG_TABLE_TXBF)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI, "TXBF not supported\n");
			tpc_stats->flag[type] = ATH10K_TPC_TABLE_TYPE_FLAG;
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "invalid table type in wmi tpc event: %d\n", type);
		वापस;
	पूर्ण

	pream_idx = 0;
	क्रम (i = 0; i < tpc_stats->rate_max; i++) अणु
		स_रखो(tpc_value, 0, माप(tpc_value));
		स_रखो(buff, 0, माप(buff));
		अगर (i == pream_table[pream_idx])
			pream_idx++;

		क्रम (j = 0; j < tpc_stats->num_tx_chain; j++) अणु
			tpc[j] = ath10k_wmi_tpc_final_get_rate(ar, ev, i, j + 1,
							       rate_code[i],
							       type, pream_idx);
			snम_लिखो(buff, माप(buff), "%8d ", tpc[j]);
			strlcat(tpc_value, buff, माप(tpc_value));
		पूर्ण
		tpc_stats->tpc_table_final[type].pream_idx[i] = pream_idx;
		tpc_stats->tpc_table_final[type].rate_code[i] = rate_code[i];
		स_नकल(tpc_stats->tpc_table_final[type].tpc_value[i],
		       tpc_value, माप(tpc_value));
	पूर्ण
पूर्ण

व्योम ath10k_wmi_event_tpc_final_table(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	u32 num_tx_chain, rate_max;
	u8 rate_code[WMI_TPC_FINAL_RATE_MAX];
	u16 pream_table[WMI_TPC_PREAM_TABLE_MAX];
	काष्ठा wmi_pdev_tpc_final_table_event *ev;
	काष्ठा ath10k_tpc_stats_final *tpc_stats;

	ev = (काष्ठा wmi_pdev_tpc_final_table_event *)skb->data;

	num_tx_chain = __le32_to_cpu(ev->num_tx_chain);
	अगर (num_tx_chain > WMI_TPC_TX_N_CHAIN) अणु
		ath10k_warn(ar, "number of tx chain is %d greater than TPC final configured tx chain %d\n",
			    num_tx_chain, WMI_TPC_TX_N_CHAIN);
		वापस;
	पूर्ण

	rate_max = __le32_to_cpu(ev->rate_max);
	अगर (rate_max > WMI_TPC_FINAL_RATE_MAX) अणु
		ath10k_warn(ar, "number of rate is %d greater than TPC final configured rate %d\n",
			    rate_max, WMI_TPC_FINAL_RATE_MAX);
		rate_max = WMI_TPC_FINAL_RATE_MAX;
	पूर्ण

	tpc_stats = kzalloc(माप(*tpc_stats), GFP_ATOMIC);
	अगर (!tpc_stats)
		वापस;

	ath10k_wmi_tpc_config_get_rate_code(rate_code, pream_table,
					    num_tx_chain);

	tpc_stats->chan_freq = __le32_to_cpu(ev->chan_freq);
	tpc_stats->phy_mode = __le32_to_cpu(ev->phy_mode);
	tpc_stats->ctl = __le32_to_cpu(ev->ctl);
	tpc_stats->reg_करोमुख्य = __le32_to_cpu(ev->reg_करोमुख्य);
	tpc_stats->twice_antenna_gain = a_sle32_to_cpu(ev->twice_antenna_gain);
	tpc_stats->twice_antenna_reduction =
		__le32_to_cpu(ev->twice_antenna_reduction);
	tpc_stats->घातer_limit = __le32_to_cpu(ev->घातer_limit);
	tpc_stats->twice_max_rd_घातer = __le32_to_cpu(ev->twice_max_rd_घातer);
	tpc_stats->num_tx_chain = num_tx_chain;
	tpc_stats->rate_max = rate_max;

	ath10k_wmi_tpc_stats_final_disp_tables(ar, ev, tpc_stats,
					       rate_code, pream_table,
					       WMI_TPC_TABLE_TYPE_CDD);
	ath10k_wmi_tpc_stats_final_disp_tables(ar, ev,  tpc_stats,
					       rate_code, pream_table,
					       WMI_TPC_TABLE_TYPE_STBC);
	ath10k_wmi_tpc_stats_final_disp_tables(ar, ev, tpc_stats,
					       rate_code, pream_table,
					       WMI_TPC_TABLE_TYPE_TXBF);

	ath10k_debug_tpc_stats_final_process(ar, tpc_stats);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event tpc final table channel %d mode %d ctl %d regd %d gain %d %d limit %d max_power %d tx_chanins %d rates %d\n",
		   __le32_to_cpu(ev->chan_freq),
		   __le32_to_cpu(ev->phy_mode),
		   __le32_to_cpu(ev->ctl),
		   __le32_to_cpu(ev->reg_करोमुख्य),
		   a_sle32_to_cpu(ev->twice_antenna_gain),
		   __le32_to_cpu(ev->twice_antenna_reduction),
		   __le32_to_cpu(ev->घातer_limit),
		   __le32_to_cpu(ev->twice_max_rd_घातer) / 2,
		   __le32_to_cpu(ev->num_tx_chain),
		   __le32_to_cpu(ev->rate_max));
पूर्ण

अटल व्योम
ath10k_wmi_handle_tdls_peer_event(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tdls_peer_event *ev;
	काष्ठा ath10k_peer *peer;
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक vdev_id;
	पूर्णांक peer_status;
	पूर्णांक peer_reason;
	u8 reason;

	अगर (skb->len < माप(*ev)) अणु
		ath10k_err(ar, "received tdls peer event with invalid size (%d bytes)\n",
			   skb->len);
		वापस;
	पूर्ण

	ev = (काष्ठा wmi_tdls_peer_event *)skb->data;
	vdev_id = __le32_to_cpu(ev->vdev_id);
	peer_status = __le32_to_cpu(ev->peer_status);
	peer_reason = __le32_to_cpu(ev->peer_reason);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, vdev_id, ev->peer_macaddr.addr);
	spin_unlock_bh(&ar->data_lock);

	अगर (!peer) अणु
		ath10k_warn(ar, "failed to find peer entry for %pM\n",
			    ev->peer_macaddr.addr);
		वापस;
	पूर्ण

	चयन (peer_status) अणु
	हाल WMI_TDLS_SHOULD_TEARDOWN:
		चयन (peer_reason) अणु
		हाल WMI_TDLS_TEARDOWN_REASON_PTR_TIMEOUT:
		हाल WMI_TDLS_TEARDOWN_REASON_NO_RESPONSE:
		हाल WMI_TDLS_TEARDOWN_REASON_RSSI:
			reason = WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE;
			अवरोध;
		शेष:
			reason = WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED;
			अवरोध;
		पूर्ण

		arvअगर = ath10k_get_arvअगर(ar, vdev_id);
		अगर (!arvअगर) अणु
			ath10k_warn(ar, "received tdls peer event for invalid vdev id %u\n",
				    vdev_id);
			वापस;
		पूर्ण

		ieee80211_tdls_oper_request(arvअगर->vअगर, ev->peer_macaddr.addr,
					    NL80211_TDLS_TEARDOWN, reason,
					    GFP_ATOMIC);

		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "received tdls teardown event for peer %pM reason %u\n",
			   ev->peer_macaddr.addr, peer_reason);
		अवरोध;
	शेष:
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "received unknown tdls peer event %u\n",
			   peer_status);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
ath10k_wmi_event_peer_sta_ps_state_chg(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_peer_sta_ps_state_chg_event *ev;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_sta *arsta;
	u8 peer_addr[ETH_ALEN];

	lockdep_निश्चित_held(&ar->data_lock);

	ev = (काष्ठा wmi_peer_sta_ps_state_chg_event *)skb->data;
	ether_addr_copy(peer_addr, ev->peer_macaddr.addr);

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta_by_अगरaddr(ar->hw, peer_addr, शून्य);

	अगर (!sta) अणु
		ath10k_warn(ar, "failed to find station entry %pM\n",
			    peer_addr);
		जाओ निकास;
	पूर्ण

	arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	arsta->peer_ps_state = __le32_to_cpu(ev->peer_ps_state);

निकास:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ath10k_wmi_event_pdev_fपंचांग_पूर्णांकg(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_PDEV_FTM_INTG_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_gtk_offload_status(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_GTK_OFFLOAD_STATUS_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_gtk_rekey_fail(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_GTK_REKEY_FAIL_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_delba_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_TX_DELBA_COMPLETE_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_addba_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_TX_ADDBA_COMPLETE_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_vdev_install_key_complete(काष्ठा ath10k *ar,
						काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_INSTALL_KEY_COMPLETE_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_inst_rssi_stats(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_INST_RSSI_STATS_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_vdev_standby_req(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_STANDBY_REQ_EVENTID\n");
पूर्ण

व्योम ath10k_wmi_event_vdev_resume_req(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_RESUME_REQ_EVENTID\n");
पूर्ण

अटल पूर्णांक ath10k_wmi_alloc_chunk(काष्ठा ath10k *ar, u32 req_id,
				  u32 num_units, u32 unit_len)
अणु
	dma_addr_t paddr;
	u32 pool_size;
	पूर्णांक idx = ar->wmi.num_mem_chunks;
	व्योम *vaddr;

	pool_size = num_units * round_up(unit_len, 4);
	vaddr = dma_alloc_coherent(ar->dev, pool_size, &paddr, GFP_KERNEL);

	अगर (!vaddr)
		वापस -ENOMEM;

	ar->wmi.mem_chunks[idx].vaddr = vaddr;
	ar->wmi.mem_chunks[idx].paddr = paddr;
	ar->wmi.mem_chunks[idx].len = pool_size;
	ar->wmi.mem_chunks[idx].req_id = req_id;
	ar->wmi.num_mem_chunks++;

	वापस num_units;
पूर्ण

अटल पूर्णांक ath10k_wmi_alloc_host_mem(काष्ठा ath10k *ar, u32 req_id,
				     u32 num_units, u32 unit_len)
अणु
	पूर्णांक ret;

	जबतक (num_units) अणु
		ret = ath10k_wmi_alloc_chunk(ar, req_id, num_units, unit_len);
		अगर (ret < 0)
			वापस ret;

		num_units -= ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
ath10k_wmi_is_host_mem_allocated(काष्ठा ath10k *ar,
				 स्थिर काष्ठा wlan_host_mem_req **mem_reqs,
				 u32 num_mem_reqs)
अणु
	u32 req_id, num_units, unit_size, num_unit_info;
	u32 pool_size;
	पूर्णांक i, j;
	bool found;

	अगर (ar->wmi.num_mem_chunks != num_mem_reqs)
		वापस false;

	क्रम (i = 0; i < num_mem_reqs; ++i) अणु
		req_id = __le32_to_cpu(mem_reqs[i]->req_id);
		num_units = __le32_to_cpu(mem_reqs[i]->num_units);
		unit_size = __le32_to_cpu(mem_reqs[i]->unit_size);
		num_unit_info = __le32_to_cpu(mem_reqs[i]->num_unit_info);

		अगर (num_unit_info & NUM_UNITS_IS_NUM_ACTIVE_PEERS) अणु
			अगर (ar->num_active_peers)
				num_units = ar->num_active_peers + 1;
			अन्यथा
				num_units = ar->max_num_peers + 1;
		पूर्ण अन्यथा अगर (num_unit_info & NUM_UNITS_IS_NUM_PEERS) अणु
			num_units = ar->max_num_peers + 1;
		पूर्ण अन्यथा अगर (num_unit_info & NUM_UNITS_IS_NUM_VDEVS) अणु
			num_units = ar->max_num_vdevs + 1;
		पूर्ण

		found = false;
		क्रम (j = 0; j < ar->wmi.num_mem_chunks; j++) अणु
			अगर (ar->wmi.mem_chunks[j].req_id == req_id) अणु
				pool_size = num_units * round_up(unit_size, 4);
				अगर (ar->wmi.mem_chunks[j].len == pool_size) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!found)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
ath10k_wmi_मुख्य_op_pull_svc_rdy_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				   काष्ठा wmi_svc_rdy_ev_arg *arg)
अणु
	काष्ठा wmi_service_पढ़ोy_event *ev;
	माप_प्रकार i, n;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	ev = (व्योम *)skb->data;
	skb_pull(skb, माप(*ev));
	arg->min_tx_घातer = ev->hw_min_tx_घातer;
	arg->max_tx_घातer = ev->hw_max_tx_घातer;
	arg->ht_cap = ev->ht_cap_info;
	arg->vht_cap = ev->vht_cap_info;
	arg->vht_supp_mcs = ev->vht_supp_mcs;
	arg->sw_ver0 = ev->sw_version;
	arg->sw_ver1 = ev->sw_version_1;
	arg->phy_capab = ev->phy_capability;
	arg->num_rf_chains = ev->num_rf_chains;
	arg->eeprom_rd = ev->hal_reg_capabilities.eeprom_rd;
	arg->low_2ghz_chan = ev->hal_reg_capabilities.low_2ghz_chan;
	arg->high_2ghz_chan = ev->hal_reg_capabilities.high_2ghz_chan;
	arg->low_5ghz_chan = ev->hal_reg_capabilities.low_5ghz_chan;
	arg->high_5ghz_chan = ev->hal_reg_capabilities.high_5ghz_chan;
	arg->num_mem_reqs = ev->num_mem_reqs;
	arg->service_map = ev->wmi_service_biपंचांगap;
	arg->service_map_len = माप(ev->wmi_service_biपंचांगap);

	n = min_t(माप_प्रकार, __le32_to_cpu(arg->num_mem_reqs),
		  ARRAY_SIZE(arg->mem_reqs));
	क्रम (i = 0; i < n; i++)
		arg->mem_reqs[i] = &ev->mem_reqs[i];

	अगर (skb->len <
	    __le32_to_cpu(arg->num_mem_reqs) * माप(arg->mem_reqs[0]))
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_wmi_10x_op_pull_svc_rdy_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				  काष्ठा wmi_svc_rdy_ev_arg *arg)
अणु
	काष्ठा wmi_10x_service_पढ़ोy_event *ev;
	पूर्णांक i, n;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	ev = (व्योम *)skb->data;
	skb_pull(skb, माप(*ev));
	arg->min_tx_घातer = ev->hw_min_tx_घातer;
	arg->max_tx_घातer = ev->hw_max_tx_घातer;
	arg->ht_cap = ev->ht_cap_info;
	arg->vht_cap = ev->vht_cap_info;
	arg->vht_supp_mcs = ev->vht_supp_mcs;
	arg->sw_ver0 = ev->sw_version;
	arg->phy_capab = ev->phy_capability;
	arg->num_rf_chains = ev->num_rf_chains;
	arg->eeprom_rd = ev->hal_reg_capabilities.eeprom_rd;
	arg->low_2ghz_chan = ev->hal_reg_capabilities.low_2ghz_chan;
	arg->high_2ghz_chan = ev->hal_reg_capabilities.high_2ghz_chan;
	arg->low_5ghz_chan = ev->hal_reg_capabilities.low_5ghz_chan;
	arg->high_5ghz_chan = ev->hal_reg_capabilities.high_5ghz_chan;
	arg->num_mem_reqs = ev->num_mem_reqs;
	arg->service_map = ev->wmi_service_biपंचांगap;
	arg->service_map_len = माप(ev->wmi_service_biपंचांगap);

	/* Deliberately skipping ev->sys_cap_info as WMI and WMI-TLV have
	 * dअगरferent values. We would need a translation to handle that,
	 * but as we करोn't currently need anything from sys_cap_info from
	 * WMI पूर्णांकerface (only from WMI-TLV) safest it to skip it.
	 */

	n = min_t(माप_प्रकार, __le32_to_cpu(arg->num_mem_reqs),
		  ARRAY_SIZE(arg->mem_reqs));
	क्रम (i = 0; i < n; i++)
		arg->mem_reqs[i] = &ev->mem_reqs[i];

	अगर (skb->len <
	    __le32_to_cpu(arg->num_mem_reqs) * माप(arg->mem_reqs[0]))
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल व्योम ath10k_wmi_event_service_पढ़ोy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, svc_rdy_work);
	काष्ठा sk_buff *skb = ar->svc_rdy_skb;
	काष्ठा wmi_svc_rdy_ev_arg arg = अणुपूर्ण;
	u32 num_units, req_id, unit_size, num_mem_reqs, num_unit_info, i;
	पूर्णांक ret;
	bool allocated;

	अगर (!skb) अणु
		ath10k_warn(ar, "invalid service ready event skb\n");
		वापस;
	पूर्ण

	ret = ath10k_wmi_pull_svc_rdy(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse service ready: %d\n", ret);
		वापस;
	पूर्ण

	ath10k_wmi_map_svc(ar, arg.service_map, ar->wmi.svc_map,
			   arg.service_map_len);

	ar->hw_min_tx_घातer = __le32_to_cpu(arg.min_tx_घातer);
	ar->hw_max_tx_घातer = __le32_to_cpu(arg.max_tx_घातer);
	ar->ht_cap_info = __le32_to_cpu(arg.ht_cap);
	ar->vht_cap_info = __le32_to_cpu(arg.vht_cap);
	ar->vht_supp_mcs = __le32_to_cpu(arg.vht_supp_mcs);
	ar->fw_version_major =
		(__le32_to_cpu(arg.sw_ver0) & 0xff000000) >> 24;
	ar->fw_version_minor = (__le32_to_cpu(arg.sw_ver0) & 0x00ffffff);
	ar->fw_version_release =
		(__le32_to_cpu(arg.sw_ver1) & 0xffff0000) >> 16;
	ar->fw_version_build = (__le32_to_cpu(arg.sw_ver1) & 0x0000ffff);
	ar->phy_capability = __le32_to_cpu(arg.phy_capab);
	ar->num_rf_chains = __le32_to_cpu(arg.num_rf_chains);
	ar->hw_eeprom_rd = __le32_to_cpu(arg.eeprom_rd);
	ar->low_2ghz_chan = __le32_to_cpu(arg.low_2ghz_chan);
	ar->high_2ghz_chan = __le32_to_cpu(arg.high_2ghz_chan);
	ar->low_5ghz_chan = __le32_to_cpu(arg.low_5ghz_chan);
	ar->high_5ghz_chan = __le32_to_cpu(arg.high_5ghz_chan);
	ar->sys_cap_info = __le32_to_cpu(arg.sys_cap_info);

	ath10k_dbg_dump(ar, ATH10K_DBG_WMI, शून्य, "wmi svc: ",
			arg.service_map, arg.service_map_len);
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi sys_cap_info 0x%x\n",
		   ar->sys_cap_info);

	अगर (ar->num_rf_chains > ar->max_spatial_stream) अणु
		ath10k_warn(ar, "hardware advertises support for more spatial streams than it should (%d > %d)\n",
			    ar->num_rf_chains, ar->max_spatial_stream);
		ar->num_rf_chains = ar->max_spatial_stream;
	पूर्ण

	अगर (!ar->cfg_tx_chainmask) अणु
		ar->cfg_tx_chainmask = (1 << ar->num_rf_chains) - 1;
		ar->cfg_rx_chainmask = (1 << ar->num_rf_chains) - 1;
	पूर्ण

	अगर (म_माप(ar->hw->wiphy->fw_version) == 0) अणु
		snम_लिखो(ar->hw->wiphy->fw_version,
			 माप(ar->hw->wiphy->fw_version),
			 "%u.%u.%u.%u",
			 ar->fw_version_major,
			 ar->fw_version_minor,
			 ar->fw_version_release,
			 ar->fw_version_build);
	पूर्ण

	num_mem_reqs = __le32_to_cpu(arg.num_mem_reqs);
	अगर (num_mem_reqs > WMI_MAX_MEM_REQS) अणु
		ath10k_warn(ar, "requested memory chunks number (%d) exceeds the limit\n",
			    num_mem_reqs);
		वापस;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_PEER_CACHING, ar->wmi.svc_map)) अणु
		अगर (test_bit(ATH10K_FW_FEATURE_PEER_FLOW_CONTROL,
			     ar->running_fw->fw_file.fw_features))
			ar->num_active_peers = TARGET_10_4_QCACHE_ACTIVE_PEERS_PFC +
					       ar->max_num_vdevs;
		अन्यथा
			ar->num_active_peers = TARGET_10_4_QCACHE_ACTIVE_PEERS +
					       ar->max_num_vdevs;

		ar->max_num_peers = TARGET_10_4_NUM_QCACHE_PEERS_MAX +
				    ar->max_num_vdevs;
		ar->num_tids = ar->num_active_peers * 2;
		ar->max_num_stations = TARGET_10_4_NUM_QCACHE_PEERS_MAX;
	पूर्ण

	/* TODO: Adjust max peer count क्रम हालs like WMI_SERVICE_RATECTRL_CACHE
	 * and WMI_SERVICE_IRAM_TIDS, etc.
	 */

	allocated = ath10k_wmi_is_host_mem_allocated(ar, arg.mem_reqs,
						     num_mem_reqs);
	अगर (allocated)
		जाओ skip_mem_alloc;

	/* Either this event is received during boot समय or there is a change
	 * in memory requirement from firmware when compared to last request.
	 * Free any old memory and करो a fresh allocation based on the current
	 * memory requirement.
	 */
	ath10k_wmi_मुक्त_host_mem(ar);

	क्रम (i = 0; i < num_mem_reqs; ++i) अणु
		req_id = __le32_to_cpu(arg.mem_reqs[i]->req_id);
		num_units = __le32_to_cpu(arg.mem_reqs[i]->num_units);
		unit_size = __le32_to_cpu(arg.mem_reqs[i]->unit_size);
		num_unit_info = __le32_to_cpu(arg.mem_reqs[i]->num_unit_info);

		अगर (num_unit_info & NUM_UNITS_IS_NUM_ACTIVE_PEERS) अणु
			अगर (ar->num_active_peers)
				num_units = ar->num_active_peers + 1;
			अन्यथा
				num_units = ar->max_num_peers + 1;
		पूर्ण अन्यथा अगर (num_unit_info & NUM_UNITS_IS_NUM_PEERS) अणु
			/* number of units to allocate is number of
			 * peers, 1 extra क्रम self peer on target
			 * this needs to be tied, host and target
			 * can get out of sync
			 */
			num_units = ar->max_num_peers + 1;
		पूर्ण अन्यथा अगर (num_unit_info & NUM_UNITS_IS_NUM_VDEVS) अणु
			num_units = ar->max_num_vdevs + 1;
		पूर्ण

		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi mem_req_id %d num_units %d num_unit_info %d unit size %d actual units %d\n",
			   req_id,
			   __le32_to_cpu(arg.mem_reqs[i]->num_units),
			   num_unit_info,
			   unit_size,
			   num_units);

		ret = ath10k_wmi_alloc_host_mem(ar, req_id, num_units,
						unit_size);
		अगर (ret)
			वापस;
	पूर्ण

skip_mem_alloc:
	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event service ready min_tx_power 0x%08x max_tx_power 0x%08x ht_cap 0x%08x vht_cap 0x%08x vht_supp_mcs 0x%08x sw_ver0 0x%08x sw_ver1 0x%08x fw_build 0x%08x phy_capab 0x%08x num_rf_chains 0x%08x eeprom_rd 0x%08x low_2ghz_chan %d high_2ghz_chan %d low_5ghz_chan %d high_5ghz_chan %d num_mem_reqs 0x%08x\n",
		   __le32_to_cpu(arg.min_tx_घातer),
		   __le32_to_cpu(arg.max_tx_घातer),
		   __le32_to_cpu(arg.ht_cap),
		   __le32_to_cpu(arg.vht_cap),
		   __le32_to_cpu(arg.vht_supp_mcs),
		   __le32_to_cpu(arg.sw_ver0),
		   __le32_to_cpu(arg.sw_ver1),
		   __le32_to_cpu(arg.fw_build),
		   __le32_to_cpu(arg.phy_capab),
		   __le32_to_cpu(arg.num_rf_chains),
		   __le32_to_cpu(arg.eeprom_rd),
		   __le32_to_cpu(arg.low_2ghz_chan),
		   __le32_to_cpu(arg.high_2ghz_chan),
		   __le32_to_cpu(arg.low_5ghz_chan),
		   __le32_to_cpu(arg.high_5ghz_chan),
		   __le32_to_cpu(arg.num_mem_reqs));

	dev_kमुक्त_skb(skb);
	ar->svc_rdy_skb = शून्य;
	complete(&ar->wmi.service_पढ़ोy);
पूर्ण

व्योम ath10k_wmi_event_service_पढ़ोy(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ar->svc_rdy_skb = skb;
	queue_work(ar->workqueue_aux, &ar->svc_rdy_work);
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_rdy_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				     काष्ठा wmi_rdy_ev_arg *arg)
अणु
	काष्ठा wmi_पढ़ोy_event *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->sw_version = ev->sw_version;
	arg->abi_version = ev->abi_version;
	arg->status = ev->status;
	arg->mac_addr = ev->mac_addr.addr;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_roam_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				      काष्ठा wmi_roam_ev_arg *arg)
अणु
	काष्ठा wmi_roam_ev *ev = (व्योम *)skb->data;

	अगर (skb->len < माप(*ev))
		वापस -EPROTO;

	skb_pull(skb, माप(*ev));
	arg->vdev_id = ev->vdev_id;
	arg->reason = ev->reason;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_op_pull_echo_ev(काष्ठा ath10k *ar,
				      काष्ठा sk_buff *skb,
				      काष्ठा wmi_echo_ev_arg *arg)
अणु
	काष्ठा wmi_echo_event *ev = (व्योम *)skb->data;

	arg->value = ev->value;

	वापस 0;
पूर्ण

पूर्णांक ath10k_wmi_event_पढ़ोy(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_rdy_ev_arg arg = अणुपूर्ण;
	पूर्णांक ret;

	ret = ath10k_wmi_pull_rdy(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse ready event: %d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event ready sw_version 0x%08x abi_version %u mac_addr %pM status %d\n",
		   __le32_to_cpu(arg.sw_version),
		   __le32_to_cpu(arg.abi_version),
		   arg.mac_addr,
		   __le32_to_cpu(arg.status));

	अगर (is_zero_ether_addr(ar->mac_addr))
		ether_addr_copy(ar->mac_addr, arg.mac_addr);
	complete(&ar->wmi.unअगरied_पढ़ोy);
	वापस 0;
पूर्ण

व्योम ath10k_wmi_event_service_available(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा wmi_svc_avail_ev_arg arg = अणुपूर्ण;

	ret = ath10k_wmi_pull_svc_avail(ar, skb, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse service available event: %d\n",
			    ret);
	पूर्ण

	/*
	 * Initialization of "arg.service_map_ext_valid" to ZERO is necessary
	 * क्रम the below logic to work.
	 */
	अगर (arg.service_map_ext_valid)
		ath10k_wmi_map_svc_ext(ar, arg.service_map_ext, ar->wmi.svc_map,
				       __le32_to_cpu(arg.service_map_ext_len));
पूर्ण

अटल पूर्णांक ath10k_wmi_event_temperature(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा wmi_pdev_temperature_event *ev;

	ev = (काष्ठा wmi_pdev_temperature_event *)skb->data;
	अगर (WARN_ON(skb->len < माप(*ev)))
		वापस -EPROTO;

	ath10k_thermal_event_temperature(ar, __le32_to_cpu(ev->temperature));
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_event_pdev_bss_chan_info(काष्ठा ath10k *ar,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_pdev_bss_chan_info_event *ev;
	काष्ठा survey_info *survey;
	u64 busy, total, tx, rx, rx_bss;
	u32 freq, noise_न्यूनमान;
	u32 cc_freq_hz = ar->hw_params.channel_counters_freq_hz;
	पूर्णांक idx;

	ev = (काष्ठा wmi_pdev_bss_chan_info_event *)skb->data;
	अगर (WARN_ON(skb->len < माप(*ev)))
		वापस -EPROTO;

	freq        = __le32_to_cpu(ev->freq);
	noise_न्यूनमान = __le32_to_cpu(ev->noise_न्यूनमान);
	busy        = __le64_to_cpu(ev->cycle_busy);
	total       = __le64_to_cpu(ev->cycle_total);
	tx          = __le64_to_cpu(ev->cycle_tx);
	rx          = __le64_to_cpu(ev->cycle_rx);
	rx_bss      = __le64_to_cpu(ev->cycle_rx_bss);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event pdev bss chan info:\n freq: %d noise: %d cycle: busy %llu total %llu tx %llu rx %llu rx_bss %llu\n",
		   freq, noise_न्यूनमान, busy, total, tx, rx, rx_bss);

	spin_lock_bh(&ar->data_lock);
	idx = freq_to_idx(ar, freq);
	अगर (idx >= ARRAY_SIZE(ar->survey)) अणु
		ath10k_warn(ar, "bss chan info: invalid frequency %d (idx %d out of bounds)\n",
			    freq, idx);
		जाओ निकास;
	पूर्ण

	survey = &ar->survey[idx];

	survey->noise     = noise_न्यूनमान;
	survey->समय      = भाग_u64(total, cc_freq_hz);
	survey->समय_busy = भाग_u64(busy, cc_freq_hz);
	survey->समय_rx   = भाग_u64(rx_bss, cc_freq_hz);
	survey->समय_प्रकारx   = भाग_u64(tx, cc_freq_hz);
	survey->filled   |= (SURVEY_INFO_NOISE_DBM |
			     SURVEY_INFO_TIME |
			     SURVEY_INFO_TIME_BUSY |
			     SURVEY_INFO_TIME_RX |
			     SURVEY_INFO_TIME_TX);
निकास:
	spin_unlock_bh(&ar->data_lock);
	complete(&ar->bss_survey_करोne);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_wmi_queue_set_coverage_class_work(काष्ठा ath10k *ar)
अणु
	अगर (ar->hw_params.hw_ops->set_coverage_class) अणु
		spin_lock_bh(&ar->data_lock);

		/* This call only ensures that the modअगरied coverage class
		 * persists in हाल the firmware sets the रेजिस्टरs back to
		 * their शेष value. So calling it is only necessary अगर the
		 * coverage class has a non-zero value.
		 */
		अगर (ar->fw_coverage.coverage_class)
			queue_work(ar->workqueue, &ar->set_coverage_class_work);

		spin_unlock_bh(&ar->data_lock);
	पूर्ण
पूर्ण

अटल व्योम ath10k_wmi_op_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत wmi_event_id id;

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	अगर (skb_pull(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		जाओ out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	चयन (id) अणु
	हाल WMI_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		वापस;
	हाल WMI_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		अवरोध;
	हाल WMI_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		अवरोध;
	हाल WMI_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		अवरोध;
	हाल WMI_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		अवरोध;
	हाल WMI_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		अवरोध;
	हाल WMI_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		अवरोध;
	हाल WMI_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		अवरोध;
	हाल WMI_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_PROखाता_MATCH:
		ath10k_wmi_event_profile_match(ar, skb);
		अवरोध;
	हाल WMI_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_prपूर्णांक(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_PDEV_QVIT_EVENTID:
		ath10k_wmi_event_pdev_qvit(ar, skb);
		अवरोध;
	हाल WMI_WLAN_PROखाता_DATA_EVENTID:
		ath10k_wmi_event_wlan_profile_data(ar, skb);
		अवरोध;
	हाल WMI_RTT_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_rtt_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_TSF_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_tsf_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_RTT_ERROR_REPORT_EVENTID:
		ath10k_wmi_event_rtt_error_report(ar, skb);
		अवरोध;
	हाल WMI_WOW_WAKEUP_HOST_EVENTID:
		ath10k_wmi_event_wow_wakeup_host(ar, skb);
		अवरोध;
	हाल WMI_DCS_INTERFERENCE_EVENTID:
		ath10k_wmi_event_dcs_पूर्णांकerference(ar, skb);
		अवरोध;
	हाल WMI_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		अवरोध;
	हाल WMI_PDEV_FTM_INTG_EVENTID:
		ath10k_wmi_event_pdev_fपंचांग_पूर्णांकg(ar, skb);
		अवरोध;
	हाल WMI_GTK_OFFLOAD_STATUS_EVENTID:
		ath10k_wmi_event_gtk_offload_status(ar, skb);
		अवरोध;
	हाल WMI_GTK_REKEY_FAIL_EVENTID:
		ath10k_wmi_event_gtk_rekey_fail(ar, skb);
		अवरोध;
	हाल WMI_TX_DELBA_COMPLETE_EVENTID:
		ath10k_wmi_event_delba_complete(ar, skb);
		अवरोध;
	हाल WMI_TX_ADDBA_COMPLETE_EVENTID:
		ath10k_wmi_event_addba_complete(ar, skb);
		अवरोध;
	हाल WMI_VDEV_INSTALL_KEY_COMPLETE_EVENTID:
		ath10k_wmi_event_vdev_install_key_complete(ar, skb);
		अवरोध;
	हाल WMI_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_पढ़ोy(ar, skb);
		वापस;
	हाल WMI_READY_EVENTID:
		ath10k_wmi_event_पढ़ोy(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_SERVICE_AVAILABLE_EVENTID:
		ath10k_wmi_event_service_available(ar, skb);
		अवरोध;
	शेष:
		ath10k_warn(ar, "Unknown eventid: %d\n", id);
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath10k_wmi_10_1_op_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत wmi_10x_event_id id;
	bool consumed;

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	अगर (skb_pull(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		जाओ out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	consumed = ath10k_पंचांग_event_wmi(ar, id, skb);

	/* Ready event must be handled normally also in UTF mode so that we
	 * know the UTF firmware has booted, others we are just bypass WMI
	 * events to tesपंचांगode.
	 */
	अगर (consumed && id != WMI_10X_READY_EVENTID) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi testmode consumed 0x%x\n", id);
		जाओ out;
	पूर्ण

	चयन (id) अणु
	हाल WMI_10X_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		वापस;
	हाल WMI_10X_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		अवरोध;
	हाल WMI_10X_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		अवरोध;
	हाल WMI_10X_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		अवरोध;
	हाल WMI_10X_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		अवरोध;
	हाल WMI_10X_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		अवरोध;
	हाल WMI_10X_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		अवरोध;
	हाल WMI_10X_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		अवरोध;
	हाल WMI_10X_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_PROखाता_MATCH:
		ath10k_wmi_event_profile_match(ar, skb);
		अवरोध;
	हाल WMI_10X_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_prपूर्णांक(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_PDEV_QVIT_EVENTID:
		ath10k_wmi_event_pdev_qvit(ar, skb);
		अवरोध;
	हाल WMI_10X_WLAN_PROखाता_DATA_EVENTID:
		ath10k_wmi_event_wlan_profile_data(ar, skb);
		अवरोध;
	हाल WMI_10X_RTT_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_rtt_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_10X_TSF_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_tsf_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_10X_RTT_ERROR_REPORT_EVENTID:
		ath10k_wmi_event_rtt_error_report(ar, skb);
		अवरोध;
	हाल WMI_10X_WOW_WAKEUP_HOST_EVENTID:
		ath10k_wmi_event_wow_wakeup_host(ar, skb);
		अवरोध;
	हाल WMI_10X_DCS_INTERFERENCE_EVENTID:
		ath10k_wmi_event_dcs_पूर्णांकerference(ar, skb);
		अवरोध;
	हाल WMI_10X_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		अवरोध;
	हाल WMI_10X_INST_RSSI_STATS_EVENTID:
		ath10k_wmi_event_inst_rssi_stats(ar, skb);
		अवरोध;
	हाल WMI_10X_VDEV_STANDBY_REQ_EVENTID:
		ath10k_wmi_event_vdev_standby_req(ar, skb);
		अवरोध;
	हाल WMI_10X_VDEV_RESUME_REQ_EVENTID:
		ath10k_wmi_event_vdev_resume_req(ar, skb);
		अवरोध;
	हाल WMI_10X_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_पढ़ोy(ar, skb);
		वापस;
	हाल WMI_10X_READY_EVENTID:
		ath10k_wmi_event_पढ़ोy(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10X_PDEV_UTF_EVENTID:
		/* ignore utf events */
		अवरोध;
	शेष:
		ath10k_warn(ar, "Unknown eventid: %d\n", id);
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath10k_wmi_10_2_op_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत wmi_10_2_event_id id;
	bool consumed;

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	अगर (skb_pull(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		जाओ out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	consumed = ath10k_पंचांग_event_wmi(ar, id, skb);

	/* Ready event must be handled normally also in UTF mode so that we
	 * know the UTF firmware has booted, others we are just bypass WMI
	 * events to tesपंचांगode.
	 */
	अगर (consumed && id != WMI_10_2_READY_EVENTID) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi testmode consumed 0x%x\n", id);
		जाओ out;
	पूर्ण

	चयन (id) अणु
	हाल WMI_10_2_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		वापस;
	हाल WMI_10_2_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		अवरोध;
	हाल WMI_10_2_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		अवरोध;
	हाल WMI_10_2_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		अवरोध;
	हाल WMI_10_2_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		अवरोध;
	हाल WMI_10_2_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		अवरोध;
	हाल WMI_10_2_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		अवरोध;
	हाल WMI_10_2_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		अवरोध;
	हाल WMI_10_2_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_PROखाता_MATCH:
		ath10k_wmi_event_profile_match(ar, skb);
		अवरोध;
	हाल WMI_10_2_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_prपूर्णांक(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_PDEV_QVIT_EVENTID:
		ath10k_wmi_event_pdev_qvit(ar, skb);
		अवरोध;
	हाल WMI_10_2_WLAN_PROखाता_DATA_EVENTID:
		ath10k_wmi_event_wlan_profile_data(ar, skb);
		अवरोध;
	हाल WMI_10_2_RTT_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_rtt_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_10_2_TSF_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_tsf_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_10_2_RTT_ERROR_REPORT_EVENTID:
		ath10k_wmi_event_rtt_error_report(ar, skb);
		अवरोध;
	हाल WMI_10_2_WOW_WAKEUP_HOST_EVENTID:
		ath10k_wmi_event_wow_wakeup_host(ar, skb);
		अवरोध;
	हाल WMI_10_2_DCS_INTERFERENCE_EVENTID:
		ath10k_wmi_event_dcs_पूर्णांकerference(ar, skb);
		अवरोध;
	हाल WMI_10_2_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		अवरोध;
	हाल WMI_10_2_INST_RSSI_STATS_EVENTID:
		ath10k_wmi_event_inst_rssi_stats(ar, skb);
		अवरोध;
	हाल WMI_10_2_VDEV_STANDBY_REQ_EVENTID:
		ath10k_wmi_event_vdev_standby_req(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_VDEV_RESUME_REQ_EVENTID:
		ath10k_wmi_event_vdev_resume_req(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_पढ़ोy(ar, skb);
		वापस;
	हाल WMI_10_2_READY_EVENTID:
		ath10k_wmi_event_पढ़ोy(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_2_PDEV_TEMPERATURE_EVENTID:
		ath10k_wmi_event_temperature(ar, skb);
		अवरोध;
	हाल WMI_10_2_PDEV_BSS_CHAN_INFO_EVENTID:
		ath10k_wmi_event_pdev_bss_chan_info(ar, skb);
		अवरोध;
	हाल WMI_10_2_RTT_KEEPALIVE_EVENTID:
	हाल WMI_10_2_GPIO_INPUT_EVENTID:
	हाल WMI_10_2_PEER_RATECODE_LIST_EVENTID:
	हाल WMI_10_2_GENERIC_BUFFER_EVENTID:
	हाल WMI_10_2_MCAST_BUF_RELEASE_EVENTID:
	हाल WMI_10_2_MCAST_LIST_AGEOUT_EVENTID:
	हाल WMI_10_2_WDS_PEER_EVENTID:
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "received event id %d not implemented\n", id);
		अवरोध;
	हाल WMI_10_2_PEER_STA_PS_STATECHG_EVENTID:
		ath10k_wmi_event_peer_sta_ps_state_chg(ar, skb);
		अवरोध;
	शेष:
		ath10k_warn(ar, "Unknown eventid: %d\n", id);
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath10k_wmi_10_4_op_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत wmi_10_4_event_id id;
	bool consumed;

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	अगर (!skb_pull(skb, माप(काष्ठा wmi_cmd_hdr)))
		जाओ out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	consumed = ath10k_पंचांग_event_wmi(ar, id, skb);

	/* Ready event must be handled normally also in UTF mode so that we
	 * know the UTF firmware has booted, others we are just bypass WMI
	 * events to tesपंचांगode.
	 */
	अगर (consumed && id != WMI_10_4_READY_EVENTID) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi testmode consumed 0x%x\n", id);
		जाओ out;
	पूर्ण

	चयन (id) अणु
	हाल WMI_10_4_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		वापस;
	हाल WMI_10_4_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		अवरोध;
	हाल WMI_10_4_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_पढ़ोy(ar, skb);
		वापस;
	हाल WMI_10_4_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		अवरोध;
	हाल WMI_10_4_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		अवरोध;
	हाल WMI_10_4_READY_EVENTID:
		ath10k_wmi_event_पढ़ोy(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		अवरोध;
	हाल WMI_10_4_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		अवरोध;
	हाल WMI_10_4_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		अवरोध;
	हाल WMI_10_4_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_prपूर्णांक(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		अवरोध;
	हाल WMI_10_4_WOW_WAKEUP_HOST_EVENTID:
	हाल WMI_10_4_PEER_RATECODE_LIST_EVENTID:
	हाल WMI_10_4_WDS_PEER_EVENTID:
	हाल WMI_10_4_DEBUG_FATAL_CONDITION_EVENTID:
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "received event id %d not implemented\n", id);
		अवरोध;
	हाल WMI_10_4_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		अवरोध;
	हाल WMI_10_4_PDEV_TEMPERATURE_EVENTID:
		ath10k_wmi_event_temperature(ar, skb);
		अवरोध;
	हाल WMI_10_4_PDEV_BSS_CHAN_INFO_EVENTID:
		ath10k_wmi_event_pdev_bss_chan_info(ar, skb);
		अवरोध;
	हाल WMI_10_4_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		अवरोध;
	हाल WMI_10_4_TDLS_PEER_EVENTID:
		ath10k_wmi_handle_tdls_peer_event(ar, skb);
		अवरोध;
	हाल WMI_10_4_PDEV_TPC_TABLE_EVENTID:
		ath10k_wmi_event_tpc_final_table(ar, skb);
		अवरोध;
	हाल WMI_10_4_DFS_STATUS_CHECK_EVENTID:
		ath10k_wmi_event_dfs_status_check(ar, skb);
		अवरोध;
	हाल WMI_10_4_PEER_STA_PS_STATECHG_EVENTID:
		ath10k_wmi_event_peer_sta_ps_state_chg(ar, skb);
		अवरोध;
	शेष:
		ath10k_warn(ar, "Unknown eventid: %d\n", id);
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath10k_wmi_process_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	ret = ath10k_wmi_rx(ar, skb);
	अगर (ret)
		ath10k_warn(ar, "failed to process wmi rx: %d\n", ret);
पूर्ण

पूर्णांक ath10k_wmi_connect(काष्ठा ath10k *ar)
अणु
	पूर्णांक status;
	काष्ठा ath10k_htc_svc_conn_req conn_req;
	काष्ठा ath10k_htc_svc_conn_resp conn_resp;

	स_रखो(&ar->wmi.svc_map, 0, माप(ar->wmi.svc_map));

	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));

	/* these fields are the same क्रम all service endpoपूर्णांकs */
	conn_req.ep_ops.ep_tx_complete = ath10k_wmi_htc_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath10k_wmi_process_rx;
	conn_req.ep_ops.ep_tx_credits = ath10k_wmi_op_ep_tx_credits;

	/* connect to control service */
	conn_req.service_id = ATH10K_HTC_SVC_ID_WMI_CONTROL;

	status = ath10k_htc_connect_service(&ar->htc, &conn_req, &conn_resp);
	अगर (status) अणु
		ath10k_warn(ar, "failed to connect to WMI CONTROL service status: %d\n",
			    status);
		वापस status;
	पूर्ण

	ar->wmi.eid = conn_resp.eid;
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_set_base_macaddr(काष्ठा ath10k *ar,
					स्थिर u8 macaddr[ETH_ALEN])
अणु
	काष्ठा wmi_pdev_set_base_macaddr_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_base_macaddr_cmd *)skb->data;
	ether_addr_copy(cmd->mac_addr.addr, macaddr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev basemac %pM\n", macaddr);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_set_rd(काष्ठा ath10k *ar, u16 rd, u16 rd2g, u16 rd5g,
			      u16 ctl2g, u16 ctl5g,
			      क्रमागत wmi_dfs_region dfs_reg)
अणु
	काष्ठा wmi_pdev_set_regकरोमुख्य_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_regकरोमुख्य_cmd *)skb->data;
	cmd->reg_करोमुख्य = __cpu_to_le32(rd);
	cmd->reg_करोमुख्य_2G = __cpu_to_le32(rd2g);
	cmd->reg_करोमुख्य_5G = __cpu_to_le32(rd5g);
	cmd->conक्रमmance_test_limit_2G = __cpu_to_le32(ctl2g);
	cmd->conक्रमmance_test_limit_5G = __cpu_to_le32(ctl5g);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev regdomain rd %x rd2g %x rd5g %x ctl2g %x ctl5g %x\n",
		   rd, rd2g, rd5g, ctl2g, ctl5g);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10x_op_gen_pdev_set_rd(काष्ठा ath10k *ar, u16 rd, u16 rd2g, u16
				  rd5g, u16 ctl2g, u16 ctl5g,
				  क्रमागत wmi_dfs_region dfs_reg)
अणु
	काष्ठा wmi_pdev_set_regकरोमुख्य_cmd_10x *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_regकरोमुख्य_cmd_10x *)skb->data;
	cmd->reg_करोमुख्य = __cpu_to_le32(rd);
	cmd->reg_करोमुख्य_2G = __cpu_to_le32(rd2g);
	cmd->reg_करोमुख्य_5G = __cpu_to_le32(rd5g);
	cmd->conक्रमmance_test_limit_2G = __cpu_to_le32(ctl2g);
	cmd->conक्रमmance_test_limit_5G = __cpu_to_le32(ctl5g);
	cmd->dfs_करोमुख्य = __cpu_to_le32(dfs_reg);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev regdomain rd %x rd2g %x rd5g %x ctl2g %x ctl5g %x dfs_region %x\n",
		   rd, rd2g, rd5g, ctl2g, ctl5g, dfs_reg);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_suspend(काष्ठा ath10k *ar, u32 suspend_opt)
अणु
	काष्ठा wmi_pdev_suspend_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_suspend_cmd *)skb->data;
	cmd->suspend_opt = __cpu_to_le32(suspend_opt);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_resume(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, 0);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_set_param(काष्ठा ath10k *ar, u32 id, u32 value)
अणु
	काष्ठा wmi_pdev_set_param_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (id == WMI_PDEV_PARAM_UNSUPPORTED) अणु
		ath10k_warn(ar, "pdev param %d not supported by firmware\n",
			    id);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_param_cmd *)skb->data;
	cmd->param_id    = __cpu_to_le32(id);
	cmd->param_value = __cpu_to_le32(value);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev set param %d value %d\n",
		   id, value);
	वापस skb;
पूर्ण

व्योम ath10k_wmi_put_host_mem_chunks(काष्ठा ath10k *ar,
				    काष्ठा wmi_host_mem_chunks *chunks)
अणु
	काष्ठा host_memory_chunk *chunk;
	पूर्णांक i;

	chunks->count = __cpu_to_le32(ar->wmi.num_mem_chunks);

	क्रम (i = 0; i < ar->wmi.num_mem_chunks; i++) अणु
		chunk = &chunks->items[i];
		chunk->ptr = __cpu_to_le32(ar->wmi.mem_chunks[i].paddr);
		chunk->size = __cpu_to_le32(ar->wmi.mem_chunks[i].len);
		chunk->req_id = __cpu_to_le32(ar->wmi.mem_chunks[i].req_id);

		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi chunk %d len %d requested, addr 0x%llx\n",
			   i,
			   ar->wmi.mem_chunks[i].len,
			   (अचिन्हित दीर्घ दीर्घ)ar->wmi.mem_chunks[i].paddr);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *ath10k_wmi_op_gen_init(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_init_cmd *cmd;
	काष्ठा sk_buff *buf;
	काष्ठा wmi_resource_config config = अणुपूर्ण;
	u32 val;

	config.num_vdevs = __cpu_to_le32(TARGET_NUM_VDEVS);
	config.num_peers = __cpu_to_le32(TARGET_NUM_PEERS);
	config.num_offload_peers = __cpu_to_le32(TARGET_NUM_OFFLOAD_PEERS);

	config.num_offload_reorder_bufs =
		__cpu_to_le32(TARGET_NUM_OFFLOAD_REORDER_BUFS);

	config.num_peer_keys = __cpu_to_le32(TARGET_NUM_PEER_KEYS);
	config.num_tids = __cpu_to_le32(TARGET_NUM_TIDS);
	config.ast_skid_limit = __cpu_to_le32(TARGET_AST_SKID_LIMIT);
	config.tx_chain_mask = __cpu_to_le32(TARGET_TX_CHAIN_MASK);
	config.rx_chain_mask = __cpu_to_le32(TARGET_RX_CHAIN_MASK);
	config.rx_समयout_pri_vo = __cpu_to_le32(TARGET_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_vi = __cpu_to_le32(TARGET_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_be = __cpu_to_le32(TARGET_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_bk = __cpu_to_le32(TARGET_RX_TIMEOUT_HI_PRI);
	config.rx_decap_mode = __cpu_to_le32(ar->wmi.rx_decap_mode);
	config.scan_max_pending_reqs =
		__cpu_to_le32(TARGET_SCAN_MAX_PENDING_REQS);

	config.bmiss_offload_max_vdev =
		__cpu_to_le32(TARGET_BMISS_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_vdev =
		__cpu_to_le32(TARGET_ROAM_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_ap_profiles =
		__cpu_to_le32(TARGET_ROAM_OFFLOAD_MAX_AP_PROखाताS);

	config.num_mcast_groups = __cpu_to_le32(TARGET_NUM_MCAST_GROUPS);
	config.num_mcast_table_elems =
		__cpu_to_le32(TARGET_NUM_MCAST_TABLE_ELEMS);

	config.mcast2ucast_mode = __cpu_to_le32(TARGET_MCAST2UCAST_MODE);
	config.tx_dbg_log_size = __cpu_to_le32(TARGET_TX_DBG_LOG_SIZE);
	config.num_wds_entries = __cpu_to_le32(TARGET_NUM_WDS_ENTRIES);
	config.dma_burst_size = __cpu_to_le32(TARGET_DMA_BURST_SIZE);
	config.mac_aggr_delim = __cpu_to_le32(TARGET_MAC_AGGR_DELIM);

	val = TARGET_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK;
	config.rx_skip_defrag_समयout_dup_detection_check = __cpu_to_le32(val);

	config.vow_config = __cpu_to_le32(TARGET_VOW_CONFIG);

	config.gtk_offload_max_vdev =
		__cpu_to_le32(TARGET_GTK_OFFLOAD_MAX_VDEV);

	config.num_msdu_desc = __cpu_to_le32(TARGET_NUM_MSDU_DESC);
	config.max_frag_entries = __cpu_to_le32(TARGET_MAX_FRAG_ENTRIES);

	buf = ath10k_wmi_alloc_skb(ar, काष्ठा_size(cmd, mem_chunks.items,
						   ar->wmi.num_mem_chunks));
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_init_cmd *)buf->data;

	स_नकल(&cmd->resource_config, &config, माप(config));
	ath10k_wmi_put_host_mem_chunks(ar, &cmd->mem_chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi init\n");
	वापस buf;
पूर्ण

अटल काष्ठा sk_buff *ath10k_wmi_10_1_op_gen_init(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_init_cmd_10x *cmd;
	काष्ठा sk_buff *buf;
	काष्ठा wmi_resource_config_10x config = अणुपूर्ण;
	u32 val;

	config.num_vdevs = __cpu_to_le32(TARGET_10X_NUM_VDEVS);
	config.num_peers = __cpu_to_le32(TARGET_10X_NUM_PEERS);
	config.num_peer_keys = __cpu_to_le32(TARGET_10X_NUM_PEER_KEYS);
	config.num_tids = __cpu_to_le32(TARGET_10X_NUM_TIDS);
	config.ast_skid_limit = __cpu_to_le32(TARGET_10X_AST_SKID_LIMIT);
	config.tx_chain_mask = __cpu_to_le32(TARGET_10X_TX_CHAIN_MASK);
	config.rx_chain_mask = __cpu_to_le32(TARGET_10X_RX_CHAIN_MASK);
	config.rx_समयout_pri_vo = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_vi = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_be = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_bk = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_HI_PRI);
	config.rx_decap_mode = __cpu_to_le32(ar->wmi.rx_decap_mode);
	config.scan_max_pending_reqs =
		__cpu_to_le32(TARGET_10X_SCAN_MAX_PENDING_REQS);

	config.bmiss_offload_max_vdev =
		__cpu_to_le32(TARGET_10X_BMISS_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_vdev =
		__cpu_to_le32(TARGET_10X_ROAM_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_ap_profiles =
		__cpu_to_le32(TARGET_10X_ROAM_OFFLOAD_MAX_AP_PROखाताS);

	config.num_mcast_groups = __cpu_to_le32(TARGET_10X_NUM_MCAST_GROUPS);
	config.num_mcast_table_elems =
		__cpu_to_le32(TARGET_10X_NUM_MCAST_TABLE_ELEMS);

	config.mcast2ucast_mode = __cpu_to_le32(TARGET_10X_MCAST2UCAST_MODE);
	config.tx_dbg_log_size = __cpu_to_le32(TARGET_10X_TX_DBG_LOG_SIZE);
	config.num_wds_entries = __cpu_to_le32(TARGET_10X_NUM_WDS_ENTRIES);
	config.dma_burst_size = __cpu_to_le32(TARGET_10X_DMA_BURST_SIZE);
	config.mac_aggr_delim = __cpu_to_le32(TARGET_10X_MAC_AGGR_DELIM);

	val = TARGET_10X_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK;
	config.rx_skip_defrag_समयout_dup_detection_check = __cpu_to_le32(val);

	config.vow_config = __cpu_to_le32(TARGET_10X_VOW_CONFIG);

	config.num_msdu_desc = __cpu_to_le32(TARGET_10X_NUM_MSDU_DESC);
	config.max_frag_entries = __cpu_to_le32(TARGET_10X_MAX_FRAG_ENTRIES);

	buf = ath10k_wmi_alloc_skb(ar, काष्ठा_size(cmd, mem_chunks.items,
						   ar->wmi.num_mem_chunks));
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_init_cmd_10x *)buf->data;

	स_नकल(&cmd->resource_config, &config, माप(config));
	ath10k_wmi_put_host_mem_chunks(ar, &cmd->mem_chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi init 10x\n");
	वापस buf;
पूर्ण

अटल काष्ठा sk_buff *ath10k_wmi_10_2_op_gen_init(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_init_cmd_10_2 *cmd;
	काष्ठा sk_buff *buf;
	काष्ठा wmi_resource_config_10x config = अणुपूर्ण;
	u32 val, features;

	config.num_vdevs = __cpu_to_le32(TARGET_10X_NUM_VDEVS);
	config.num_peer_keys = __cpu_to_le32(TARGET_10X_NUM_PEER_KEYS);

	अगर (ath10k_peer_stats_enabled(ar)) अणु
		config.num_peers = __cpu_to_le32(TARGET_10X_TX_STATS_NUM_PEERS);
		config.num_tids = __cpu_to_le32(TARGET_10X_TX_STATS_NUM_TIDS);
	पूर्ण अन्यथा अणु
		config.num_peers = __cpu_to_le32(TARGET_10X_NUM_PEERS);
		config.num_tids = __cpu_to_le32(TARGET_10X_NUM_TIDS);
	पूर्ण

	config.ast_skid_limit = __cpu_to_le32(TARGET_10X_AST_SKID_LIMIT);
	config.tx_chain_mask = __cpu_to_le32(TARGET_10X_TX_CHAIN_MASK);
	config.rx_chain_mask = __cpu_to_le32(TARGET_10X_RX_CHAIN_MASK);
	config.rx_समयout_pri_vo = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_vi = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_be = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri_bk = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_HI_PRI);
	config.rx_decap_mode = __cpu_to_le32(ar->wmi.rx_decap_mode);

	config.scan_max_pending_reqs =
		__cpu_to_le32(TARGET_10X_SCAN_MAX_PENDING_REQS);

	config.bmiss_offload_max_vdev =
		__cpu_to_le32(TARGET_10X_BMISS_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_vdev =
		__cpu_to_le32(TARGET_10X_ROAM_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_ap_profiles =
		__cpu_to_le32(TARGET_10X_ROAM_OFFLOAD_MAX_AP_PROखाताS);

	config.num_mcast_groups = __cpu_to_le32(TARGET_10X_NUM_MCAST_GROUPS);
	config.num_mcast_table_elems =
		__cpu_to_le32(TARGET_10X_NUM_MCAST_TABLE_ELEMS);

	config.mcast2ucast_mode = __cpu_to_le32(TARGET_10X_MCAST2UCAST_MODE);
	config.tx_dbg_log_size = __cpu_to_le32(TARGET_10X_TX_DBG_LOG_SIZE);
	config.num_wds_entries = __cpu_to_le32(TARGET_10X_NUM_WDS_ENTRIES);
	config.dma_burst_size = __cpu_to_le32(TARGET_10_2_DMA_BURST_SIZE);
	config.mac_aggr_delim = __cpu_to_le32(TARGET_10X_MAC_AGGR_DELIM);

	val = TARGET_10X_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK;
	config.rx_skip_defrag_समयout_dup_detection_check = __cpu_to_le32(val);

	config.vow_config = __cpu_to_le32(TARGET_10X_VOW_CONFIG);

	config.num_msdu_desc = __cpu_to_le32(TARGET_10X_NUM_MSDU_DESC);
	config.max_frag_entries = __cpu_to_le32(TARGET_10X_MAX_FRAG_ENTRIES);

	buf = ath10k_wmi_alloc_skb(ar, काष्ठा_size(cmd, mem_chunks.items,
						   ar->wmi.num_mem_chunks));
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_init_cmd_10_2 *)buf->data;

	features = WMI_10_2_RX_BATCH_MODE;

	अगर (test_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags) &&
	    test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map))
		features |= WMI_10_2_COEX_GPIO;

	अगर (ath10k_peer_stats_enabled(ar))
		features |= WMI_10_2_PEER_STATS;

	अगर (test_bit(WMI_SERVICE_BSS_CHANNEL_INFO_64, ar->wmi.svc_map))
		features |= WMI_10_2_BSS_CHAN_INFO;

	cmd->resource_config.feature_mask = __cpu_to_le32(features);

	स_नकल(&cmd->resource_config.common, &config, माप(config));
	ath10k_wmi_put_host_mem_chunks(ar, &cmd->mem_chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi init 10.2\n");
	वापस buf;
पूर्ण

अटल काष्ठा sk_buff *ath10k_wmi_10_4_op_gen_init(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_init_cmd_10_4 *cmd;
	काष्ठा sk_buff *buf;
	काष्ठा wmi_resource_config_10_4 config = अणुपूर्ण;

	config.num_vdevs = __cpu_to_le32(ar->max_num_vdevs);
	config.num_peers = __cpu_to_le32(ar->max_num_peers);
	config.num_active_peers = __cpu_to_le32(ar->num_active_peers);
	config.num_tids = __cpu_to_le32(ar->num_tids);

	config.num_offload_peers = __cpu_to_le32(TARGET_10_4_NUM_OFFLOAD_PEERS);
	config.num_offload_reorder_buffs =
			__cpu_to_le32(TARGET_10_4_NUM_OFFLOAD_REORDER_BUFFS);
	config.num_peer_keys  = __cpu_to_le32(TARGET_10_4_NUM_PEER_KEYS);
	config.ast_skid_limit = __cpu_to_le32(TARGET_10_4_AST_SKID_LIMIT);
	config.tx_chain_mask  = __cpu_to_le32(ar->hw_params.tx_chain_mask);
	config.rx_chain_mask  = __cpu_to_le32(ar->hw_params.rx_chain_mask);

	config.rx_समयout_pri[0] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri[1] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri[2] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_LO_PRI);
	config.rx_समयout_pri[3] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_HI_PRI);

	config.rx_decap_mode	    = __cpu_to_le32(ar->wmi.rx_decap_mode);
	config.scan_max_pending_req = __cpu_to_le32(TARGET_10_4_SCAN_MAX_REQS);
	config.bmiss_offload_max_vdev =
			__cpu_to_le32(TARGET_10_4_BMISS_OFFLOAD_MAX_VDEV);
	config.roam_offload_max_vdev  =
			__cpu_to_le32(TARGET_10_4_ROAM_OFFLOAD_MAX_VDEV);
	config.roam_offload_max_ap_profiles =
			__cpu_to_le32(TARGET_10_4_ROAM_OFFLOAD_MAX_PROखाताS);
	config.num_mcast_groups = __cpu_to_le32(TARGET_10_4_NUM_MCAST_GROUPS);
	config.num_mcast_table_elems =
			__cpu_to_le32(TARGET_10_4_NUM_MCAST_TABLE_ELEMS);

	config.mcast2ucast_mode = __cpu_to_le32(TARGET_10_4_MCAST2UCAST_MODE);
	config.tx_dbg_log_size  = __cpu_to_le32(TARGET_10_4_TX_DBG_LOG_SIZE);
	config.num_wds_entries  = __cpu_to_le32(TARGET_10_4_NUM_WDS_ENTRIES);
	config.dma_burst_size   = __cpu_to_le32(TARGET_10_4_DMA_BURST_SIZE);
	config.mac_aggr_delim   = __cpu_to_le32(TARGET_10_4_MAC_AGGR_DELIM);

	config.rx_skip_defrag_समयout_dup_detection_check =
	  __cpu_to_le32(TARGET_10_4_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK);

	config.vow_config = __cpu_to_le32(TARGET_10_4_VOW_CONFIG);
	config.gtk_offload_max_vdev =
			__cpu_to_le32(TARGET_10_4_GTK_OFFLOAD_MAX_VDEV);
	config.num_msdu_desc = __cpu_to_le32(ar->htt.max_num_pending_tx);
	config.max_frag_entries = __cpu_to_le32(TARGET_10_4_11AC_TX_MAX_FRAGS);
	config.max_peer_ext_stats =
			__cpu_to_le32(TARGET_10_4_MAX_PEER_EXT_STATS);
	config.smart_ant_cap = __cpu_to_le32(TARGET_10_4_SMART_ANT_CAP);

	config.bk_minमुक्त = __cpu_to_le32(TARGET_10_4_BK_MIN_FREE);
	config.be_minमुक्त = __cpu_to_le32(TARGET_10_4_BE_MIN_FREE);
	config.vi_minमुक्त = __cpu_to_le32(TARGET_10_4_VI_MIN_FREE);
	config.vo_minमुक्त = __cpu_to_le32(TARGET_10_4_VO_MIN_FREE);

	config.rx_batchmode = __cpu_to_le32(TARGET_10_4_RX_BATCH_MODE);
	config.tt_support =
			__cpu_to_le32(TARGET_10_4_THERMAL_THROTTLING_CONFIG);
	config.atf_config = __cpu_to_le32(TARGET_10_4_ATF_CONFIG);
	config.iphdr_pad_config = __cpu_to_le32(TARGET_10_4_IPHDR_PAD_CONFIG);
	config.qwrap_config = __cpu_to_le32(TARGET_10_4_QWRAP_CONFIG);

	buf = ath10k_wmi_alloc_skb(ar, काष्ठा_size(cmd, mem_chunks.items,
						   ar->wmi.num_mem_chunks));
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_init_cmd_10_4 *)buf->data;
	स_नकल(&cmd->resource_config, &config, माप(config));
	ath10k_wmi_put_host_mem_chunks(ar, &cmd->mem_chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi init 10.4\n");
	वापस buf;
पूर्ण

पूर्णांक ath10k_wmi_start_scan_verअगरy(स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	अगर (arg->ie_len > WLAN_SCAN_PARAMS_MAX_IE_LEN)
		वापस -EINVAL;
	अगर (arg->n_channels > ARRAY_SIZE(arg->channels))
		वापस -EINVAL;
	अगर (arg->n_ssids > WLAN_SCAN_PARAMS_MAX_SSID)
		वापस -EINVAL;
	अगर (arg->n_bssids > WLAN_SCAN_PARAMS_MAX_BSSID)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल माप_प्रकार
ath10k_wmi_start_scan_tlvs_len(स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	पूर्णांक len = 0;

	अगर (arg->ie_len) अणु
		len += माप(काष्ठा wmi_ie_data);
		len += roundup(arg->ie_len, 4);
	पूर्ण

	अगर (arg->n_channels) अणु
		len += माप(काष्ठा wmi_chan_list);
		len += माप(__le32) * arg->n_channels;
	पूर्ण

	अगर (arg->n_ssids) अणु
		len += माप(काष्ठा wmi_ssid_list);
		len += माप(काष्ठा wmi_ssid) * arg->n_ssids;
	पूर्ण

	अगर (arg->n_bssids) अणु
		len += माप(काष्ठा wmi_bssid_list);
		len += माप(काष्ठा wmi_mac_addr) * arg->n_bssids;
	पूर्ण

	वापस len;
पूर्ण

व्योम ath10k_wmi_put_start_scan_common(काष्ठा wmi_start_scan_common *cmn,
				      स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	u32 scan_id;
	u32 scan_req_id;

	scan_id  = WMI_HOST_SCAN_REQ_ID_PREFIX;
	scan_id |= arg->scan_id;

	scan_req_id  = WMI_HOST_SCAN_REQUESTOR_ID_PREFIX;
	scan_req_id |= arg->scan_req_id;

	cmn->scan_id            = __cpu_to_le32(scan_id);
	cmn->scan_req_id        = __cpu_to_le32(scan_req_id);
	cmn->vdev_id            = __cpu_to_le32(arg->vdev_id);
	cmn->scan_priority      = __cpu_to_le32(arg->scan_priority);
	cmn->notअगरy_scan_events = __cpu_to_le32(arg->notअगरy_scan_events);
	cmn->dwell_समय_active  = __cpu_to_le32(arg->dwell_समय_active);
	cmn->dwell_समय_passive = __cpu_to_le32(arg->dwell_समय_passive);
	cmn->min_rest_समय      = __cpu_to_le32(arg->min_rest_समय);
	cmn->max_rest_समय      = __cpu_to_le32(arg->max_rest_समय);
	cmn->repeat_probe_समय  = __cpu_to_le32(arg->repeat_probe_समय);
	cmn->probe_spacing_समय = __cpu_to_le32(arg->probe_spacing_समय);
	cmn->idle_समय          = __cpu_to_le32(arg->idle_समय);
	cmn->max_scan_समय      = __cpu_to_le32(arg->max_scan_समय);
	cmn->probe_delay        = __cpu_to_le32(arg->probe_delay);
	cmn->scan_ctrl_flags    = __cpu_to_le32(arg->scan_ctrl_flags);
पूर्ण

अटल व्योम
ath10k_wmi_put_start_scan_tlvs(काष्ठा wmi_start_scan_tlvs *tlvs,
			       स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	काष्ठा wmi_ie_data *ie;
	काष्ठा wmi_chan_list *channels;
	काष्ठा wmi_ssid_list *ssids;
	काष्ठा wmi_bssid_list *bssids;
	व्योम *ptr = tlvs->tlvs;
	पूर्णांक i;

	अगर (arg->n_channels) अणु
		channels = ptr;
		channels->tag = __cpu_to_le32(WMI_CHAN_LIST_TAG);
		channels->num_chan = __cpu_to_le32(arg->n_channels);

		क्रम (i = 0; i < arg->n_channels; i++)
			channels->channel_list[i].freq =
				__cpu_to_le16(arg->channels[i]);

		ptr += माप(*channels);
		ptr += माप(__le32) * arg->n_channels;
	पूर्ण

	अगर (arg->n_ssids) अणु
		ssids = ptr;
		ssids->tag = __cpu_to_le32(WMI_SSID_LIST_TAG);
		ssids->num_ssids = __cpu_to_le32(arg->n_ssids);

		क्रम (i = 0; i < arg->n_ssids; i++) अणु
			ssids->ssids[i].ssid_len =
				__cpu_to_le32(arg->ssids[i].len);
			स_नकल(&ssids->ssids[i].ssid,
			       arg->ssids[i].ssid,
			       arg->ssids[i].len);
		पूर्ण

		ptr += माप(*ssids);
		ptr += माप(काष्ठा wmi_ssid) * arg->n_ssids;
	पूर्ण

	अगर (arg->n_bssids) अणु
		bssids = ptr;
		bssids->tag = __cpu_to_le32(WMI_BSSID_LIST_TAG);
		bssids->num_bssid = __cpu_to_le32(arg->n_bssids);

		क्रम (i = 0; i < arg->n_bssids; i++)
			ether_addr_copy(bssids->bssid_list[i].addr,
					arg->bssids[i].bssid);

		ptr += माप(*bssids);
		ptr += माप(काष्ठा wmi_mac_addr) * arg->n_bssids;
	पूर्ण

	अगर (arg->ie_len) अणु
		ie = ptr;
		ie->tag = __cpu_to_le32(WMI_IE_TAG);
		ie->ie_len = __cpu_to_le32(arg->ie_len);
		स_नकल(ie->ie_data, arg->ie, arg->ie_len);

		ptr += माप(*ie);
		ptr += roundup(arg->ie_len, 4);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_start_scan(काष्ठा ath10k *ar,
			     स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	काष्ठा wmi_start_scan_cmd *cmd;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	पूर्णांक ret;

	ret = ath10k_wmi_start_scan_verअगरy(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	len = माप(*cmd) + ath10k_wmi_start_scan_tlvs_len(arg);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_start_scan_cmd *)skb->data;

	ath10k_wmi_put_start_scan_common(&cmd->common, arg);
	ath10k_wmi_put_start_scan_tlvs(&cmd->tlvs, arg);

	cmd->burst_duration_ms = __cpu_to_le32(0);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi start scan\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10x_op_gen_start_scan(काष्ठा ath10k *ar,
				 स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	काष्ठा wmi_10x_start_scan_cmd *cmd;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	पूर्णांक ret;

	ret = ath10k_wmi_start_scan_verअगरy(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	len = माप(*cmd) + ath10k_wmi_start_scan_tlvs_len(arg);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_10x_start_scan_cmd *)skb->data;

	ath10k_wmi_put_start_scan_common(&cmd->common, arg);
	ath10k_wmi_put_start_scan_tlvs(&cmd->tlvs, arg);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi 10x start scan\n");
	वापस skb;
पूर्ण

व्योम ath10k_wmi_start_scan_init(काष्ठा ath10k *ar,
				काष्ठा wmi_start_scan_arg *arg)
अणु
	/* setup commonly used values */
	arg->scan_req_id = 1;
	arg->scan_priority = WMI_SCAN_PRIORITY_LOW;
	arg->dwell_समय_active = 50;
	arg->dwell_समय_passive = 150;
	arg->min_rest_समय = 50;
	arg->max_rest_समय = 500;
	arg->repeat_probe_समय = 0;
	arg->probe_spacing_समय = 0;
	arg->idle_समय = 0;
	arg->max_scan_समय = 20000;
	arg->probe_delay = 5;
	arg->notअगरy_scan_events = WMI_SCAN_EVENT_STARTED
		| WMI_SCAN_EVENT_COMPLETED
		| WMI_SCAN_EVENT_BSS_CHANNEL
		| WMI_SCAN_EVENT_FOREIGN_CHANNEL
		| WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT
		| WMI_SCAN_EVENT_DEQUEUED;
	arg->scan_ctrl_flags |= WMI_SCAN_CHAN_STAT_EVENT;
	arg->n_bssids = 1;
	arg->bssids[0].bssid = "\xFF\xFF\xFF\xFF\xFF\xFF";
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_stop_scan(काष्ठा ath10k *ar,
			    स्थिर काष्ठा wmi_stop_scan_arg *arg)
अणु
	काष्ठा wmi_stop_scan_cmd *cmd;
	काष्ठा sk_buff *skb;
	u32 scan_id;
	u32 req_id;

	अगर (arg->req_id > 0xFFF)
		वापस ERR_PTR(-EINVAL);
	अगर (arg->req_type == WMI_SCAN_STOP_ONE && arg->u.scan_id > 0xFFF)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	scan_id = arg->u.scan_id;
	scan_id |= WMI_HOST_SCAN_REQ_ID_PREFIX;

	req_id = arg->req_id;
	req_id |= WMI_HOST_SCAN_REQUESTOR_ID_PREFIX;

	cmd = (काष्ठा wmi_stop_scan_cmd *)skb->data;
	cmd->req_type    = __cpu_to_le32(arg->req_type);
	cmd->vdev_id     = __cpu_to_le32(arg->u.vdev_id);
	cmd->scan_id     = __cpu_to_le32(scan_id);
	cmd->scan_req_id = __cpu_to_le32(req_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi stop scan reqid %d req_type %d vdev/scan_id %d\n",
		   arg->req_id, arg->req_type, arg->u.scan_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_create(काष्ठा ath10k *ar, u32 vdev_id,
			      क्रमागत wmi_vdev_type type,
			      क्रमागत wmi_vdev_subtype subtype,
			      स्थिर u8 macaddr[ETH_ALEN])
अणु
	काष्ठा wmi_vdev_create_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_create_cmd *)skb->data;
	cmd->vdev_id      = __cpu_to_le32(vdev_id);
	cmd->vdev_type    = __cpu_to_le32(type);
	cmd->vdev_subtype = __cpu_to_le32(subtype);
	ether_addr_copy(cmd->vdev_macaddr.addr, macaddr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "WMI vdev create: id %d type %d subtype %d macaddr %pM\n",
		   vdev_id, type, subtype, macaddr);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_delete(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा wmi_vdev_delete_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_delete_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "WMI vdev delete id %d\n", vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_start(काष्ठा ath10k *ar,
			     स्थिर काष्ठा wmi_vdev_start_request_arg *arg,
			     bool restart)
अणु
	काष्ठा wmi_vdev_start_request_cmd *cmd;
	काष्ठा sk_buff *skb;
	स्थिर अक्षर *cmdname;
	u32 flags = 0;

	अगर (WARN_ON(arg->hidden_ssid && !arg->ssid))
		वापस ERR_PTR(-EINVAL);
	अगर (WARN_ON(arg->ssid_len > माप(cmd->ssid.ssid)))
		वापस ERR_PTR(-EINVAL);

	अगर (restart)
		cmdname = "restart";
	अन्यथा
		cmdname = "start";

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	अगर (arg->hidden_ssid)
		flags |= WMI_VDEV_START_HIDDEN_SSID;
	अगर (arg->pmf_enabled)
		flags |= WMI_VDEV_START_PMF_ENABLED;

	cmd = (काष्ठा wmi_vdev_start_request_cmd *)skb->data;
	cmd->vdev_id         = __cpu_to_le32(arg->vdev_id);
	cmd->disable_hw_ack  = __cpu_to_le32(arg->disable_hw_ack);
	cmd->beacon_पूर्णांकerval = __cpu_to_le32(arg->bcn_पूर्णांकval);
	cmd->dtim_period     = __cpu_to_le32(arg->dtim_period);
	cmd->flags           = __cpu_to_le32(flags);
	cmd->bcn_tx_rate     = __cpu_to_le32(arg->bcn_tx_rate);
	cmd->bcn_tx_घातer    = __cpu_to_le32(arg->bcn_tx_घातer);

	अगर (arg->ssid) अणु
		cmd->ssid.ssid_len = __cpu_to_le32(arg->ssid_len);
		स_नकल(cmd->ssid.ssid, arg->ssid, arg->ssid_len);
	पूर्ण

	ath10k_wmi_put_wmi_channel(ar, &cmd->chan, &arg->channel);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi vdev %s id 0x%x flags: 0x%0X, freq %d, mode %d, ch_flags: 0x%0X, max_power: %d\n",
		   cmdname, arg->vdev_id,
		   flags, arg->channel.freq, arg->channel.mode,
		   cmd->chan.flags, arg->channel.max_घातer);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_stop(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा wmi_vdev_stop_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_stop_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi vdev stop id 0x%x\n", vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_up(काष्ठा ath10k *ar, u32 vdev_id, u32 aid,
			  स्थिर u8 *bssid)
अणु
	काष्ठा wmi_vdev_up_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_up_cmd *)skb->data;
	cmd->vdev_id       = __cpu_to_le32(vdev_id);
	cmd->vdev_assoc_id = __cpu_to_le32(aid);
	ether_addr_copy(cmd->vdev_bssid.addr, bssid);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi mgmt vdev up id 0x%x assoc id %d bssid %pM\n",
		   vdev_id, aid, bssid);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_करोwn(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा wmi_vdev_करोwn_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_करोwn_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi mgmt vdev down id 0x%x\n", vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_set_param(काष्ठा ath10k *ar, u32 vdev_id,
				 u32 param_id, u32 param_value)
अणु
	काष्ठा wmi_vdev_set_param_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (param_id == WMI_VDEV_PARAM_UNSUPPORTED) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "vdev param %d not supported by firmware\n",
			    param_id);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_set_param_cmd *)skb->data;
	cmd->vdev_id     = __cpu_to_le32(vdev_id);
	cmd->param_id    = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(param_value);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi vdev id 0x%x set param %d value %d\n",
		   vdev_id, param_id, param_value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_install_key(काष्ठा ath10k *ar,
				   स्थिर काष्ठा wmi_vdev_install_key_arg *arg)
अणु
	काष्ठा wmi_vdev_install_key_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (arg->key_cipher == WMI_CIPHER_NONE && arg->key_data != शून्य)
		वापस ERR_PTR(-EINVAL);
	अगर (arg->key_cipher != WMI_CIPHER_NONE && arg->key_data == शून्य)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd) + arg->key_len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_install_key_cmd *)skb->data;
	cmd->vdev_id       = __cpu_to_le32(arg->vdev_id);
	cmd->key_idx       = __cpu_to_le32(arg->key_idx);
	cmd->key_flags     = __cpu_to_le32(arg->key_flags);
	cmd->key_cipher    = __cpu_to_le32(arg->key_cipher);
	cmd->key_len       = __cpu_to_le32(arg->key_len);
	cmd->key_txmic_len = __cpu_to_le32(arg->key_txmic_len);
	cmd->key_rxmic_len = __cpu_to_le32(arg->key_rxmic_len);

	अगर (arg->macaddr)
		ether_addr_copy(cmd->peer_macaddr.addr, arg->macaddr);
	अगर (arg->key_data)
		स_नकल(cmd->key_data, arg->key_data, arg->key_len);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi vdev install key idx %d cipher %d len %d\n",
		   arg->key_idx, arg->key_cipher, arg->key_len);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_spectral_conf(काष्ठा ath10k *ar,
				     स्थिर काष्ठा wmi_vdev_spectral_conf_arg *arg)
अणु
	काष्ठा wmi_vdev_spectral_conf_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_spectral_conf_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->scan_count = __cpu_to_le32(arg->scan_count);
	cmd->scan_period = __cpu_to_le32(arg->scan_period);
	cmd->scan_priority = __cpu_to_le32(arg->scan_priority);
	cmd->scan_fft_size = __cpu_to_le32(arg->scan_fft_size);
	cmd->scan_gc_ena = __cpu_to_le32(arg->scan_gc_ena);
	cmd->scan_restart_ena = __cpu_to_le32(arg->scan_restart_ena);
	cmd->scan_noise_न्यूनमान_ref = __cpu_to_le32(arg->scan_noise_न्यूनमान_ref);
	cmd->scan_init_delay = __cpu_to_le32(arg->scan_init_delay);
	cmd->scan_nb_tone_thr = __cpu_to_le32(arg->scan_nb_tone_thr);
	cmd->scan_str_bin_thr = __cpu_to_le32(arg->scan_str_bin_thr);
	cmd->scan_wb_rpt_mode = __cpu_to_le32(arg->scan_wb_rpt_mode);
	cmd->scan_rssi_rpt_mode = __cpu_to_le32(arg->scan_rssi_rpt_mode);
	cmd->scan_rssi_thr = __cpu_to_le32(arg->scan_rssi_thr);
	cmd->scan_pwr_क्रमmat = __cpu_to_le32(arg->scan_pwr_क्रमmat);
	cmd->scan_rpt_mode = __cpu_to_le32(arg->scan_rpt_mode);
	cmd->scan_bin_scale = __cpu_to_le32(arg->scan_bin_scale);
	cmd->scan_dbm_adj = __cpu_to_le32(arg->scan_dbm_adj);
	cmd->scan_chn_mask = __cpu_to_le32(arg->scan_chn_mask);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_vdev_spectral_enable(काष्ठा ath10k *ar, u32 vdev_id,
				       u32 trigger, u32 enable)
अणु
	काष्ठा wmi_vdev_spectral_enable_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_vdev_spectral_enable_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->trigger_cmd = __cpu_to_le32(trigger);
	cmd->enable_cmd = __cpu_to_le32(enable);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_peer_create(काष्ठा ath10k *ar, u32 vdev_id,
			      स्थिर u8 peer_addr[ETH_ALEN],
			      क्रमागत wmi_peer_type peer_type)
अणु
	काष्ठा wmi_peer_create_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_peer_create_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);
	cmd->peer_type = __cpu_to_le32(peer_type);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer create vdev_id %d peer_addr %pM\n",
		   vdev_id, peer_addr);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_peer_delete(काष्ठा ath10k *ar, u32 vdev_id,
			      स्थिर u8 peer_addr[ETH_ALEN])
अणु
	काष्ठा wmi_peer_delete_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_peer_delete_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer delete vdev_id %d peer_addr %pM\n",
		   vdev_id, peer_addr);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_peer_flush(काष्ठा ath10k *ar, u32 vdev_id,
			     स्थिर u8 peer_addr[ETH_ALEN], u32 tid_biपंचांगap)
अणु
	काष्ठा wmi_peer_flush_tids_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_peer_flush_tids_cmd *)skb->data;
	cmd->vdev_id         = __cpu_to_le32(vdev_id);
	cmd->peer_tid_biपंचांगap = __cpu_to_le32(tid_biपंचांगap);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer flush vdev_id %d peer_addr %pM tids %08x\n",
		   vdev_id, peer_addr, tid_biपंचांगap);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_peer_set_param(काष्ठा ath10k *ar, u32 vdev_id,
				 स्थिर u8 *peer_addr,
				 क्रमागत wmi_peer_param param_id,
				 u32 param_value)
अणु
	काष्ठा wmi_peer_set_param_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_peer_set_param_cmd *)skb->data;
	cmd->vdev_id     = __cpu_to_le32(vdev_id);
	cmd->param_id    = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(param_value);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi vdev %d peer 0x%pM set param %d value %d\n",
		   vdev_id, peer_addr, param_id, param_value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_set_psmode(काष्ठा ath10k *ar, u32 vdev_id,
			     क्रमागत wmi_sta_ps_mode psmode)
अणु
	काष्ठा wmi_sta_घातersave_mode_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_sta_घातersave_mode_cmd *)skb->data;
	cmd->vdev_id     = __cpu_to_le32(vdev_id);
	cmd->sta_ps_mode = __cpu_to_le32(psmode);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi set powersave id 0x%x mode %d\n",
		   vdev_id, psmode);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_set_sta_ps(काष्ठा ath10k *ar, u32 vdev_id,
			     क्रमागत wmi_sta_घातersave_param param_id,
			     u32 value)
अणु
	काष्ठा wmi_sta_घातersave_param_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_sta_घातersave_param_cmd *)skb->data;
	cmd->vdev_id     = __cpu_to_le32(vdev_id);
	cmd->param_id    = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(value);

	ath10k_dbg(ar, ATH10K_DBG_STA,
		   "wmi sta ps param vdev_id 0x%x param %d value %d\n",
		   vdev_id, param_id, value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_set_ap_ps(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
			    क्रमागत wmi_ap_ps_peer_param param_id, u32 value)
अणु
	काष्ठा wmi_ap_ps_peer_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (!mac)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_ap_ps_peer_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->param_id = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(value);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi ap ps param vdev_id 0x%X param %d value %d mac_addr %pM\n",
		   vdev_id, param_id, value, mac);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_scan_chan_list(काष्ठा ath10k *ar,
				 स्थिर काष्ठा wmi_scan_chan_list_arg *arg)
अणु
	काष्ठा wmi_scan_chan_list_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_channel_arg *ch;
	काष्ठा wmi_channel *ci;
	पूर्णांक i;

	skb = ath10k_wmi_alloc_skb(ar, काष्ठा_size(cmd, chan_info, arg->n_channels));
	अगर (!skb)
		वापस ERR_PTR(-EINVAL);

	cmd = (काष्ठा wmi_scan_chan_list_cmd *)skb->data;
	cmd->num_scan_chans = __cpu_to_le32(arg->n_channels);

	क्रम (i = 0; i < arg->n_channels; i++) अणु
		ch = &arg->channels[i];
		ci = &cmd->chan_info[i];

		ath10k_wmi_put_wmi_channel(ar, ci, ch);
	पूर्ण

	वापस skb;
पूर्ण

अटल व्योम
ath10k_wmi_peer_assoc_fill(काष्ठा ath10k *ar, व्योम *buf,
			   स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा wmi_common_peer_assoc_complete_cmd *cmd = buf;

	cmd->vdev_id            = __cpu_to_le32(arg->vdev_id);
	cmd->peer_new_assoc     = __cpu_to_le32(arg->peer_reassoc ? 0 : 1);
	cmd->peer_associd       = __cpu_to_le32(arg->peer_aid);
	cmd->peer_flags         = __cpu_to_le32(arg->peer_flags);
	cmd->peer_caps          = __cpu_to_le32(arg->peer_caps);
	cmd->peer_listen_पूर्णांकval = __cpu_to_le32(arg->peer_listen_पूर्णांकval);
	cmd->peer_ht_caps       = __cpu_to_le32(arg->peer_ht_caps);
	cmd->peer_max_mpdu      = __cpu_to_le32(arg->peer_max_mpdu);
	cmd->peer_mpdu_density  = __cpu_to_le32(arg->peer_mpdu_density);
	cmd->peer_rate_caps     = __cpu_to_le32(arg->peer_rate_caps);
	cmd->peer_nss           = __cpu_to_le32(arg->peer_num_spatial_streams);
	cmd->peer_vht_caps      = __cpu_to_le32(arg->peer_vht_caps);
	cmd->peer_phymode       = __cpu_to_le32(arg->peer_phymode);

	ether_addr_copy(cmd->peer_macaddr.addr, arg->addr);

	cmd->peer_legacy_rates.num_rates =
		__cpu_to_le32(arg->peer_legacy_rates.num_rates);
	स_नकल(cmd->peer_legacy_rates.rates, arg->peer_legacy_rates.rates,
	       arg->peer_legacy_rates.num_rates);

	cmd->peer_ht_rates.num_rates =
		__cpu_to_le32(arg->peer_ht_rates.num_rates);
	स_नकल(cmd->peer_ht_rates.rates, arg->peer_ht_rates.rates,
	       arg->peer_ht_rates.num_rates);

	cmd->peer_vht_rates.rx_max_rate =
		__cpu_to_le32(arg->peer_vht_rates.rx_max_rate);
	cmd->peer_vht_rates.rx_mcs_set =
		__cpu_to_le32(arg->peer_vht_rates.rx_mcs_set);
	cmd->peer_vht_rates.tx_max_rate =
		__cpu_to_le32(arg->peer_vht_rates.tx_max_rate);
	cmd->peer_vht_rates.tx_mcs_set =
		__cpu_to_le32(arg->peer_vht_rates.tx_mcs_set);
पूर्ण

अटल व्योम
ath10k_wmi_peer_assoc_fill_मुख्य(काष्ठा ath10k *ar, व्योम *buf,
				स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा wmi_मुख्य_peer_assoc_complete_cmd *cmd = buf;

	ath10k_wmi_peer_assoc_fill(ar, buf, arg);
	स_रखो(cmd->peer_ht_info, 0, माप(cmd->peer_ht_info));
पूर्ण

अटल व्योम
ath10k_wmi_peer_assoc_fill_10_1(काष्ठा ath10k *ar, व्योम *buf,
				स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	ath10k_wmi_peer_assoc_fill(ar, buf, arg);
पूर्ण

अटल व्योम
ath10k_wmi_peer_assoc_fill_10_2(काष्ठा ath10k *ar, व्योम *buf,
				स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा wmi_10_2_peer_assoc_complete_cmd *cmd = buf;
	पूर्णांक max_mcs, max_nss;
	u32 info0;

	/* TODO: Is using max values okay with firmware? */
	max_mcs = 0xf;
	max_nss = 0xf;

	info0 = SM(max_mcs, WMI_PEER_ASSOC_INFO0_MAX_MCS_IDX) |
		SM(max_nss, WMI_PEER_ASSOC_INFO0_MAX_NSS);

	ath10k_wmi_peer_assoc_fill(ar, buf, arg);
	cmd->info0 = __cpu_to_le32(info0);
पूर्ण

अटल व्योम
ath10k_wmi_peer_assoc_fill_10_4(काष्ठा ath10k *ar, व्योम *buf,
				स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा wmi_10_4_peer_assoc_complete_cmd *cmd = buf;

	ath10k_wmi_peer_assoc_fill_10_2(ar, buf, arg);
	cmd->peer_bw_rxnss_override =
		__cpu_to_le32(arg->peer_bw_rxnss_override);
पूर्ण

अटल पूर्णांक
ath10k_wmi_peer_assoc_check_arg(स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	अगर (arg->peer_mpdu_density > 16)
		वापस -EINVAL;
	अगर (arg->peer_legacy_rates.num_rates > MAX_SUPPORTED_RATES)
		वापस -EINVAL;
	अगर (arg->peer_ht_rates.num_rates > MAX_SUPPORTED_RATES)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_peer_assoc(काष्ठा ath10k *ar,
			     स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	माप_प्रकार len = माप(काष्ठा wmi_मुख्य_peer_assoc_complete_cmd);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = ath10k_wmi_peer_assoc_check_arg(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ath10k_wmi_peer_assoc_fill_मुख्य(ar, skb->data, arg);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer assoc vdev %d addr %pM (%s)\n",
		   arg->vdev_id, arg->addr,
		   arg->peer_reassoc ? "reassociate" : "new");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_1_op_gen_peer_assoc(काष्ठा ath10k *ar,
				  स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	माप_प्रकार len = माप(काष्ठा wmi_10_1_peer_assoc_complete_cmd);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = ath10k_wmi_peer_assoc_check_arg(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ath10k_wmi_peer_assoc_fill_10_1(ar, skb->data, arg);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer assoc vdev %d addr %pM (%s)\n",
		   arg->vdev_id, arg->addr,
		   arg->peer_reassoc ? "reassociate" : "new");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_2_op_gen_peer_assoc(काष्ठा ath10k *ar,
				  स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	माप_प्रकार len = माप(काष्ठा wmi_10_2_peer_assoc_complete_cmd);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = ath10k_wmi_peer_assoc_check_arg(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ath10k_wmi_peer_assoc_fill_10_2(ar, skb->data, arg);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer assoc vdev %d addr %pM (%s)\n",
		   arg->vdev_id, arg->addr,
		   arg->peer_reassoc ? "reassociate" : "new");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_op_gen_peer_assoc(काष्ठा ath10k *ar,
				  स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	माप_प्रकार len = माप(काष्ठा wmi_10_4_peer_assoc_complete_cmd);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ret = ath10k_wmi_peer_assoc_check_arg(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ath10k_wmi_peer_assoc_fill_10_4(ar, skb->data, arg);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi peer assoc vdev %d addr %pM (%s)\n",
		   arg->vdev_id, arg->addr,
		   arg->peer_reassoc ? "reassociate" : "new");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_2_op_gen_pdev_get_temperature(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, 0);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev get temperature\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_2_op_gen_pdev_bss_chan_info(काष्ठा ath10k *ar,
					  क्रमागत wmi_bss_survey_req_type type)
अणु
	काष्ठा wmi_pdev_chan_info_req_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_chan_info_req_cmd *)skb->data;
	cmd->type = __cpu_to_le32(type);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev bss info request type %d\n", type);

	वापस skb;
पूर्ण

/* This function assumes the beacon is alपढ़ोy DMA mapped */
अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_beacon_dma(काष्ठा ath10k *ar, u32 vdev_id, स्थिर व्योम *bcn,
			     माप_प्रकार bcn_len, u32 bcn_paddr, bool dtim_zero,
			     bool deliver_cab)
अणु
	काष्ठा wmi_bcn_tx_ref_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	hdr = (काष्ठा ieee80211_hdr *)bcn;
	fc = le16_to_cpu(hdr->frame_control);

	cmd = (काष्ठा wmi_bcn_tx_ref_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->data_len = __cpu_to_le32(bcn_len);
	cmd->data_ptr = __cpu_to_le32(bcn_paddr);
	cmd->msdu_id = 0;
	cmd->frame_control = __cpu_to_le32(fc);
	cmd->flags = 0;
	cmd->antenna_mask = __cpu_to_le32(WMI_BCN_TX_REF_DEF_ANTENNA);

	अगर (dtim_zero)
		cmd->flags |= __cpu_to_le32(WMI_BCN_TX_REF_FLAG_DTIM_ZERO);

	अगर (deliver_cab)
		cmd->flags |= __cpu_to_le32(WMI_BCN_TX_REF_FLAG_DELIVER_CAB);

	वापस skb;
पूर्ण

व्योम ath10k_wmi_set_wmm_param(काष्ठा wmi_wmm_params *params,
			      स्थिर काष्ठा wmi_wmm_params_arg *arg)
अणु
	params->cwmin  = __cpu_to_le32(arg->cwmin);
	params->cwmax  = __cpu_to_le32(arg->cwmax);
	params->aअगरs   = __cpu_to_le32(arg->aअगरs);
	params->txop   = __cpu_to_le32(arg->txop);
	params->acm    = __cpu_to_le32(arg->acm);
	params->no_ack = __cpu_to_le32(arg->no_ack);
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_set_wmm(काष्ठा ath10k *ar,
			       स्थिर काष्ठा wmi_wmm_params_all_arg *arg)
अणु
	काष्ठा wmi_pdev_set_wmm_params *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_wmm_params *)skb->data;
	ath10k_wmi_set_wmm_param(&cmd->ac_be, &arg->ac_be);
	ath10k_wmi_set_wmm_param(&cmd->ac_bk, &arg->ac_bk);
	ath10k_wmi_set_wmm_param(&cmd->ac_vi, &arg->ac_vi);
	ath10k_wmi_set_wmm_param(&cmd->ac_vo, &arg->ac_vo);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev set wmm params\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_request_stats(काष्ठा ath10k *ar, u32 stats_mask)
अणु
	काष्ठा wmi_request_stats_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_request_stats_cmd *)skb->data;
	cmd->stats_id = __cpu_to_le32(stats_mask);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi request stats 0x%08x\n",
		   stats_mask);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_क्रमce_fw_hang(काष्ठा ath10k *ar,
				क्रमागत wmi_क्रमce_fw_hang_type type, u32 delay_ms)
अणु
	काष्ठा wmi_क्रमce_fw_hang_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_क्रमce_fw_hang_cmd *)skb->data;
	cmd->type = __cpu_to_le32(type);
	cmd->delay_ms = __cpu_to_le32(delay_ms);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi force fw hang %d delay %d\n",
		   type, delay_ms);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_dbglog_cfg(काष्ठा ath10k *ar, u64 module_enable,
			     u32 log_level)
अणु
	काष्ठा wmi_dbglog_cfg_cmd *cmd;
	काष्ठा sk_buff *skb;
	u32 cfg;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_dbglog_cfg_cmd *)skb->data;

	अगर (module_enable) अणु
		cfg = SM(log_level,
			 ATH10K_DBGLOG_CFG_LOG_LVL);
	पूर्ण अन्यथा अणु
		/* set back शेषs, all modules with WARN level */
		cfg = SM(ATH10K_DBGLOG_LEVEL_WARN,
			 ATH10K_DBGLOG_CFG_LOG_LVL);
		module_enable = ~0;
	पूर्ण

	cmd->module_enable = __cpu_to_le32(module_enable);
	cmd->module_valid = __cpu_to_le32(~0);
	cmd->config_enable = __cpu_to_le32(cfg);
	cmd->config_valid = __cpu_to_le32(ATH10K_DBGLOG_CFG_LOG_LVL_MASK);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi dbglog cfg modules %08x %08x config %08x %08x\n",
		   __le32_to_cpu(cmd->module_enable),
		   __le32_to_cpu(cmd->module_valid),
		   __le32_to_cpu(cmd->config_enable),
		   __le32_to_cpu(cmd->config_valid));
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_op_gen_dbglog_cfg(काष्ठा ath10k *ar, u64 module_enable,
				  u32 log_level)
अणु
	काष्ठा wmi_10_4_dbglog_cfg_cmd *cmd;
	काष्ठा sk_buff *skb;
	u32 cfg;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_10_4_dbglog_cfg_cmd *)skb->data;

	अगर (module_enable) अणु
		cfg = SM(log_level,
			 ATH10K_DBGLOG_CFG_LOG_LVL);
	पूर्ण अन्यथा अणु
		/* set back शेषs, all modules with WARN level */
		cfg = SM(ATH10K_DBGLOG_LEVEL_WARN,
			 ATH10K_DBGLOG_CFG_LOG_LVL);
		module_enable = ~0;
	पूर्ण

	cmd->module_enable = __cpu_to_le64(module_enable);
	cmd->module_valid = __cpu_to_le64(~0);
	cmd->config_enable = __cpu_to_le32(cfg);
	cmd->config_valid = __cpu_to_le32(ATH10K_DBGLOG_CFG_LOG_LVL_MASK);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi dbglog cfg modules 0x%016llx 0x%016llx config %08x %08x\n",
		   __le64_to_cpu(cmd->module_enable),
		   __le64_to_cpu(cmd->module_valid),
		   __le32_to_cpu(cmd->config_enable),
		   __le32_to_cpu(cmd->config_valid));
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pktlog_enable(काष्ठा ath10k *ar, u32 ev_biपंचांगap)
अणु
	काष्ठा wmi_pdev_pktlog_enable_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ev_biपंचांगap &= ATH10K_PKTLOG_ANY;

	cmd = (काष्ठा wmi_pdev_pktlog_enable_cmd *)skb->data;
	cmd->ev_biपंचांगap = __cpu_to_le32(ev_biपंचांगap);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi enable pktlog filter 0x%08x\n",
		   ev_biपंचांगap);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pktlog_disable(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, 0);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi disable pktlog\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_set_quiet_mode(काष्ठा ath10k *ar, u32 period,
				      u32 duration, u32 next_offset,
				      u32 enabled)
अणु
	काष्ठा wmi_pdev_set_quiet_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_quiet_cmd *)skb->data;
	cmd->period = __cpu_to_le32(period);
	cmd->duration = __cpu_to_le32(duration);
	cmd->next_start = __cpu_to_le32(next_offset);
	cmd->enabled = __cpu_to_le32(enabled);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi quiet param: period %u duration %u enabled %d\n",
		   period, duration, enabled);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_addba_clear_resp(काष्ठा ath10k *ar, u32 vdev_id,
				   स्थिर u8 *mac)
अणु
	काष्ठा wmi_addba_clear_resp_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (!mac)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_addba_clear_resp_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi addba clear resp vdev_id 0x%X mac_addr %pM\n",
		   vdev_id, mac);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_addba_send(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
			     u32 tid, u32 buf_size)
अणु
	काष्ठा wmi_addba_send_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (!mac)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_addba_send_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = __cpu_to_le32(tid);
	cmd->buffersize = __cpu_to_le32(buf_size);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi addba send vdev_id 0x%X mac_addr %pM tid %u bufsize %u\n",
		   vdev_id, mac, tid, buf_size);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_addba_set_resp(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
				 u32 tid, u32 status)
अणु
	काष्ठा wmi_addba_setresponse_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (!mac)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_addba_setresponse_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = __cpu_to_le32(tid);
	cmd->statuscode = __cpu_to_le32(status);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi addba set resp vdev_id 0x%X mac_addr %pM tid %u status %u\n",
		   vdev_id, mac, tid, status);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_delba_send(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
			     u32 tid, u32 initiator, u32 reason)
अणु
	काष्ठा wmi_delba_send_cmd *cmd;
	काष्ठा sk_buff *skb;

	अगर (!mac)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_delba_send_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = __cpu_to_le32(tid);
	cmd->initiator = __cpu_to_le32(initiator);
	cmd->reasoncode = __cpu_to_le32(reason);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi delba send vdev_id 0x%X mac_addr %pM tid %u initiator %u reason %u\n",
		   vdev_id, mac, tid, initiator, reason);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_2_4_op_gen_pdev_get_tpc_config(काष्ठा ath10k *ar, u32 param)
अणु
	काष्ठा wmi_pdev_get_tpc_config_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_get_tpc_config_cmd *)skb->data;
	cmd->param = __cpu_to_le32(param);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev get tpc config param %d\n", param);
	वापस skb;
पूर्ण

माप_प्रकार ath10k_wmi_fw_stats_num_peers(काष्ठा list_head *head)
अणु
	काष्ठा ath10k_fw_stats_peer *i;
	माप_प्रकार num = 0;

	list_क्रम_each_entry(i, head, list)
		++num;

	वापस num;
पूर्ण

माप_प्रकार ath10k_wmi_fw_stats_num_vdevs(काष्ठा list_head *head)
अणु
	काष्ठा ath10k_fw_stats_vdev *i;
	माप_प्रकार num = 0;

	list_क्रम_each_entry(i, head, list)
		++num;

	वापस num;
पूर्ण

अटल व्योम
ath10k_wmi_fw_pdev_base_stats_fill(स्थिर काष्ठा ath10k_fw_stats_pdev *pdev,
				   अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n",
			"ath10k PDEV stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
			"=================");

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Channel noise floor", pdev->ch_noise_न्यूनमान);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"Channel TX power", pdev->chan_tx_घातer);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"TX frame count", pdev->tx_frame_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"RX frame count", pdev->rx_frame_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"RX clear count", pdev->rx_clear_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"Cycle count", pdev->cycle_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"PHY error count", pdev->phy_err_count);

	*length = len;
पूर्ण

अटल व्योम
ath10k_wmi_fw_pdev_extra_stats_fill(स्थिर काष्ठा ath10k_fw_stats_pdev *pdev,
				    अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"RTS bad count", pdev->rts_bad);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"RTS good count", pdev->rts_good);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"FCS bad count", pdev->fcs_bad);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"No beacon count", pdev->no_beacons);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"MIB int count", pdev->mib_पूर्णांक_count);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	*length = len;
पूर्ण

अटल व्योम
ath10k_wmi_fw_pdev_tx_stats_fill(स्थिर काष्ठा ath10k_fw_stats_pdev *pdev,
				 अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "\n%30s\n",
			 "ath10k PDEV TX stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HTT cookies queued", pdev->comp_queued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HTT cookies disp.", pdev->comp_delivered);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDU queued", pdev->msdu_enqued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDU queued", pdev->mpdu_enqued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDUs dropped", pdev->wmm_drop);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Local enqued", pdev->local_enqued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Local freed", pdev->local_मुक्तd);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HW queued", pdev->hw_queued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PPDUs reaped", pdev->hw_reaped);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Num underruns", pdev->underrun);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PPDUs cleaned", pdev->tx_पात);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDUs requed", pdev->mpdus_requed);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Excessive retries", pdev->tx_ko);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HW rate", pdev->data_rc);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Sched self triggers", pdev->self_triggers);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Dropped due to SW retries",
			 pdev->sw_retry_failure);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Illegal rate phy errors",
			 pdev->illgl_rate_phy_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Pdev continuous xretry", pdev->pdev_cont_xretry);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "TX timeout", pdev->pdev_tx_समयout);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PDEV resets", pdev->pdev_resets);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PHY underrun", pdev->phy_underrun);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDU is more than txop limit", pdev->txop_ovf);
	*length = len;
पूर्ण

अटल व्योम
ath10k_wmi_fw_pdev_rx_stats_fill(स्थिर काष्ठा ath10k_fw_stats_pdev *pdev,
				 अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "\n%30s\n",
			 "ath10k PDEV RX stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Mid PPDU route change",
			 pdev->mid_ppdu_route_change);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Tot. number of statuses", pdev->status_rcvd);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 0", pdev->r0_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 1", pdev->r1_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 2", pdev->r2_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 3", pdev->r3_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDUs delivered to HTT", pdev->htt_msdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDUs delivered to HTT", pdev->htt_mpdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDUs delivered to stack", pdev->loc_msdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDUs delivered to stack", pdev->loc_mpdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Oversized AMSDUs", pdev->oversize_amsdu);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PHY errors", pdev->phy_errs);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PHY errors drops", pdev->phy_err_drop);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDU errors (FCS, MIC, ENC)", pdev->mpdu_errs);
	*length = len;
पूर्ण

अटल व्योम
ath10k_wmi_fw_vdev_stats_fill(स्थिर काष्ठा ath10k_fw_stats_vdev *vdev,
			      अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;
	पूर्णांक i;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"vdev id", vdev->vdev_id);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"beacon snr", vdev->beacon_snr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"data snr", vdev->data_snr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"num rx frames", vdev->num_rx_frames);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"num rts fail", vdev->num_rts_fail);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"num rts success", vdev->num_rts_success);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"num rx err", vdev->num_rx_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"num rx discard", vdev->num_rx_discard);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"num tx not acked", vdev->num_tx_not_acked);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames", i,
				vdev->num_tx_frames[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames_retries); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames retries", i,
				vdev->num_tx_frames_retries[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames_failures); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames failures", i,
				vdev->num_tx_frames_failures[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->tx_rate_history); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] 0x%08x\n",
				"tx rate history", i,
				vdev->tx_rate_history[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->beacon_rssi_history); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"beacon rssi history", i,
				vdev->beacon_rssi_history[i]);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	*length = len;
पूर्ण

अटल व्योम
ath10k_wmi_fw_peer_stats_fill(स्थिर काष्ठा ath10k_fw_stats_peer *peer,
			      अक्षर *buf, u32 *length, bool extended_peer)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %pM\n",
			"Peer MAC address", peer->peer_macaddr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"Peer RSSI", peer->peer_rssi);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"Peer TX rate", peer->peer_tx_rate);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			"Peer RX rate", peer->peer_rx_rate);
	अगर (!extended_peer)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %llu\n",
				"Peer RX duration", peer->rx_duration);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	*length = len;
पूर्ण

अटल व्योम
ath10k_wmi_fw_extd_peer_stats_fill(स्थिर काष्ठा ath10k_fw_extd_stats_peer *peer,
				   अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %pM\n",
			"Peer MAC address", peer->peer_macaddr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %llu\n",
			"Peer RX duration", peer->rx_duration);
पूर्ण

व्योम ath10k_wmi_मुख्य_op_fw_stats_fill(काष्ठा ath10k *ar,
				      काष्ठा ath10k_fw_stats *fw_stats,
				      अक्षर *buf)
अणु
	u32 len = 0;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;
	स्थिर काष्ठा ath10k_fw_stats_pdev *pdev;
	स्थिर काष्ठा ath10k_fw_stats_vdev *vdev;
	स्थिर काष्ठा ath10k_fw_stats_peer *peer;
	माप_प्रकार num_peers;
	माप_प्रकार num_vdevs;

	spin_lock_bh(&ar->data_lock);

	pdev = list_first_entry_or_null(&fw_stats->pdevs,
					काष्ठा ath10k_fw_stats_pdev, list);
	अगर (!pdev) अणु
		ath10k_warn(ar, "failed to get pdev stats\n");
		जाओ unlock;
	पूर्ण

	num_peers = ath10k_wmi_fw_stats_num_peers(&fw_stats->peers);
	num_vdevs = ath10k_wmi_fw_stats_num_vdevs(&fw_stats->vdevs);

	ath10k_wmi_fw_pdev_base_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_tx_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_rx_stats_fill(pdev, buf, &len);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
			 "ath10k VDEV stats", num_vdevs);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

	list_क्रम_each_entry(vdev, &fw_stats->vdevs, list) अणु
		ath10k_wmi_fw_vdev_stats_fill(vdev, buf, &len);
	पूर्ण

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
			 "ath10k PEER stats", num_peers);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

	list_क्रम_each_entry(peer, &fw_stats->peers, list) अणु
		ath10k_wmi_fw_peer_stats_fill(peer, buf, &len,
					      fw_stats->extended);
	पूर्ण

unlock:
	spin_unlock_bh(&ar->data_lock);

	अगर (len >= buf_len)
		buf[len - 1] = 0;
	अन्यथा
		buf[len] = 0;
पूर्ण

व्योम ath10k_wmi_10x_op_fw_stats_fill(काष्ठा ath10k *ar,
				     काष्ठा ath10k_fw_stats *fw_stats,
				     अक्षर *buf)
अणु
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक buf_len = ATH10K_FW_STATS_BUF_SIZE;
	स्थिर काष्ठा ath10k_fw_stats_pdev *pdev;
	स्थिर काष्ठा ath10k_fw_stats_vdev *vdev;
	स्थिर काष्ठा ath10k_fw_stats_peer *peer;
	माप_प्रकार num_peers;
	माप_प्रकार num_vdevs;

	spin_lock_bh(&ar->data_lock);

	pdev = list_first_entry_or_null(&fw_stats->pdevs,
					काष्ठा ath10k_fw_stats_pdev, list);
	अगर (!pdev) अणु
		ath10k_warn(ar, "failed to get pdev stats\n");
		जाओ unlock;
	पूर्ण

	num_peers = ath10k_wmi_fw_stats_num_peers(&fw_stats->peers);
	num_vdevs = ath10k_wmi_fw_stats_num_vdevs(&fw_stats->vdevs);

	ath10k_wmi_fw_pdev_base_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_extra_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_tx_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_rx_stats_fill(pdev, buf, &len);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
			 "ath10k VDEV stats", num_vdevs);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

	list_क्रम_each_entry(vdev, &fw_stats->vdevs, list) अणु
		ath10k_wmi_fw_vdev_stats_fill(vdev, buf, &len);
	पूर्ण

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
			 "ath10k PEER stats", num_peers);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

	list_क्रम_each_entry(peer, &fw_stats->peers, list) अणु
		ath10k_wmi_fw_peer_stats_fill(peer, buf, &len,
					      fw_stats->extended);
	पूर्ण

unlock:
	spin_unlock_bh(&ar->data_lock);

	अगर (len >= buf_len)
		buf[len - 1] = 0;
	अन्यथा
		buf[len] = 0;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_pdev_enable_adaptive_cca(काष्ठा ath10k *ar, u8 enable,
					   u32 detect_level, u32 detect_margin)
अणु
	काष्ठा wmi_pdev_set_adaptive_cca_params *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_set_adaptive_cca_params *)skb->data;
	cmd->enable = __cpu_to_le32(enable);
	cmd->cca_detect_level = __cpu_to_le32(detect_level);
	cmd->cca_detect_margin = __cpu_to_le32(detect_margin);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev set adaptive cca params enable:%d detection level:%d detection margin:%d\n",
		   enable, detect_level, detect_margin);
	वापस skb;
पूर्ण

अटल व्योम
ath10k_wmi_fw_vdev_stats_extd_fill(स्थिर काष्ठा ath10k_fw_stats_vdev_extd *vdev,
				   अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;
	u32 val;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "vdev id", vdev->vdev_id);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "ppdu aggr count", vdev->ppdu_aggr_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "ppdu noack", vdev->ppdu_noack);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "mpdu queued", vdev->mpdu_queued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "ppdu nonaggr count", vdev->ppdu_nonaggr_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "mpdu sw requeued", vdev->mpdu_sw_requeued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "mpdu success retry", vdev->mpdu_suc_retry);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "mpdu success multitry", vdev->mpdu_suc_multitry);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "mpdu fail retry", vdev->mpdu_fail_retry);
	val = vdev->tx_fपंचांग_suc;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "tx ftm success",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	val = vdev->tx_fपंचांग_suc_retry;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "tx ftm success retry",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	val = vdev->tx_fपंचांग_fail;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "tx ftm fail",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	val = vdev->rx_fपंचांगr_cnt;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "rx ftm request count",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	val = vdev->rx_fपंचांगr_dup_cnt;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "rx ftm request dup count",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	val = vdev->rx_अगरपंचांगr_cnt;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "rx initial ftm req count",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	val = vdev->rx_अगरपंचांगr_dup_cnt;
	अगर (val & WMI_VDEV_STATS_FTM_COUNT_VALID)
		len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
				 "rx initial ftm req dup cnt",
				 MS(val, WMI_VDEV_STATS_FTM_COUNT));
	len += scnम_लिखो(buf + len, buf_len - len, "\n");

	*length = len;
पूर्ण

व्योम ath10k_wmi_10_4_op_fw_stats_fill(काष्ठा ath10k *ar,
				      काष्ठा ath10k_fw_stats *fw_stats,
				      अक्षर *buf)
अणु
	u32 len = 0;
	u32 buf_len = ATH10K_FW_STATS_BUF_SIZE;
	स्थिर काष्ठा ath10k_fw_stats_pdev *pdev;
	स्थिर काष्ठा ath10k_fw_stats_vdev_extd *vdev;
	स्थिर काष्ठा ath10k_fw_stats_peer *peer;
	स्थिर काष्ठा ath10k_fw_extd_stats_peer *extd_peer;
	माप_प्रकार num_peers;
	माप_प्रकार num_vdevs;

	spin_lock_bh(&ar->data_lock);

	pdev = list_first_entry_or_null(&fw_stats->pdevs,
					काष्ठा ath10k_fw_stats_pdev, list);
	अगर (!pdev) अणु
		ath10k_warn(ar, "failed to get pdev stats\n");
		जाओ unlock;
	पूर्ण

	num_peers = ath10k_wmi_fw_stats_num_peers(&fw_stats->peers);
	num_vdevs = ath10k_wmi_fw_stats_num_vdevs(&fw_stats->vdevs);

	ath10k_wmi_fw_pdev_base_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_extra_stats_fill(pdev, buf, &len);
	ath10k_wmi_fw_pdev_tx_stats_fill(pdev, buf, &len);

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"HW paused", pdev->hw_छोड़ोd);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Seqs posted", pdev->seq_posted);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Seqs failed queueing", pdev->seq_failed_queueing);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Seqs completed", pdev->seq_completed);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Seqs restarted", pdev->seq_restarted);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"MU Seqs posted", pdev->mu_seq_posted);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"MPDUs SW flushed", pdev->mpdus_sw_flush);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"MPDUs HW filtered", pdev->mpdus_hw_filter);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"MPDUs truncated", pdev->mpdus_truncated);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"MPDUs receive no ACK", pdev->mpdus_ack_failed);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"MPDUs expired", pdev->mpdus_expired);

	ath10k_wmi_fw_pdev_rx_stats_fill(pdev, buf, &len);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Num Rx Overflow errors", pdev->rx_ovfl_errs);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
			"ath10k VDEV stats", num_vdevs);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				"=================");
	list_क्रम_each_entry(vdev, &fw_stats->vdevs, list) अणु
		ath10k_wmi_fw_vdev_stats_extd_fill(vdev, buf, &len);
	पूर्ण

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
			"ath10k PEER stats", num_peers);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				"=================");

	list_क्रम_each_entry(peer, &fw_stats->peers, list) अणु
		ath10k_wmi_fw_peer_stats_fill(peer, buf, &len,
					      fw_stats->extended);
	पूर्ण

	अगर (fw_stats->extended) अणु
		list_क्रम_each_entry(extd_peer, &fw_stats->peers_extd, list) अणु
			ath10k_wmi_fw_extd_peer_stats_fill(extd_peer, buf,
							   &len);
		पूर्ण
	पूर्ण

unlock:
	spin_unlock_bh(&ar->data_lock);

	अगर (len >= buf_len)
		buf[len - 1] = 0;
	अन्यथा
		buf[len] = 0;
पूर्ण

पूर्णांक ath10k_wmi_op_get_vdev_subtype(काष्ठा ath10k *ar,
				   क्रमागत wmi_vdev_subtype subtype)
अणु
	चयन (subtype) अणु
	हाल WMI_VDEV_SUBTYPE_NONE:
		वापस WMI_VDEV_SUBTYPE_LEGACY_NONE;
	हाल WMI_VDEV_SUBTYPE_P2P_DEVICE:
		वापस WMI_VDEV_SUBTYPE_LEGACY_P2P_DEV;
	हाल WMI_VDEV_SUBTYPE_P2P_CLIENT:
		वापस WMI_VDEV_SUBTYPE_LEGACY_P2P_CLI;
	हाल WMI_VDEV_SUBTYPE_P2P_GO:
		वापस WMI_VDEV_SUBTYPE_LEGACY_P2P_GO;
	हाल WMI_VDEV_SUBTYPE_PROXY_STA:
		वापस WMI_VDEV_SUBTYPE_LEGACY_PROXY_STA;
	हाल WMI_VDEV_SUBTYPE_MESH_11S:
	हाल WMI_VDEV_SUBTYPE_MESH_NON_11S:
		वापस -ENOTSUPP;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_2_4_op_get_vdev_subtype(काष्ठा ath10k *ar,
						 क्रमागत wmi_vdev_subtype subtype)
अणु
	चयन (subtype) अणु
	हाल WMI_VDEV_SUBTYPE_NONE:
		वापस WMI_VDEV_SUBTYPE_10_2_4_NONE;
	हाल WMI_VDEV_SUBTYPE_P2P_DEVICE:
		वापस WMI_VDEV_SUBTYPE_10_2_4_P2P_DEV;
	हाल WMI_VDEV_SUBTYPE_P2P_CLIENT:
		वापस WMI_VDEV_SUBTYPE_10_2_4_P2P_CLI;
	हाल WMI_VDEV_SUBTYPE_P2P_GO:
		वापस WMI_VDEV_SUBTYPE_10_2_4_P2P_GO;
	हाल WMI_VDEV_SUBTYPE_PROXY_STA:
		वापस WMI_VDEV_SUBTYPE_10_2_4_PROXY_STA;
	हाल WMI_VDEV_SUBTYPE_MESH_11S:
		वापस WMI_VDEV_SUBTYPE_10_2_4_MESH_11S;
	हाल WMI_VDEV_SUBTYPE_MESH_NON_11S:
		वापस -ENOTSUPP;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक ath10k_wmi_10_4_op_get_vdev_subtype(काष्ठा ath10k *ar,
					       क्रमागत wmi_vdev_subtype subtype)
अणु
	चयन (subtype) अणु
	हाल WMI_VDEV_SUBTYPE_NONE:
		वापस WMI_VDEV_SUBTYPE_10_4_NONE;
	हाल WMI_VDEV_SUBTYPE_P2P_DEVICE:
		वापस WMI_VDEV_SUBTYPE_10_4_P2P_DEV;
	हाल WMI_VDEV_SUBTYPE_P2P_CLIENT:
		वापस WMI_VDEV_SUBTYPE_10_4_P2P_CLI;
	हाल WMI_VDEV_SUBTYPE_P2P_GO:
		वापस WMI_VDEV_SUBTYPE_10_4_P2P_GO;
	हाल WMI_VDEV_SUBTYPE_PROXY_STA:
		वापस WMI_VDEV_SUBTYPE_10_4_PROXY_STA;
	हाल WMI_VDEV_SUBTYPE_MESH_11S:
		वापस WMI_VDEV_SUBTYPE_10_4_MESH_11S;
	हाल WMI_VDEV_SUBTYPE_MESH_NON_11S:
		वापस WMI_VDEV_SUBTYPE_10_4_MESH_NON_11S;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_ext_resource_config(काष्ठा ath10k *ar,
				    क्रमागत wmi_host_platक्रमm_type type,
				    u32 fw_feature_biपंचांगap)
अणु
	काष्ठा wmi_ext_resource_config_10_4_cmd *cmd;
	काष्ठा sk_buff *skb;
	u32 num_tdls_sleep_sta = 0;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	अगर (test_bit(WMI_SERVICE_TDLS_UAPSD_SLEEP_STA, ar->wmi.svc_map))
		num_tdls_sleep_sta = TARGET_10_4_NUM_TDLS_SLEEP_STA;

	cmd = (काष्ठा wmi_ext_resource_config_10_4_cmd *)skb->data;
	cmd->host_platक्रमm_config = __cpu_to_le32(type);
	cmd->fw_feature_biपंचांगap = __cpu_to_le32(fw_feature_biपंचांगap);
	cmd->wlan_gpio_priority = __cpu_to_le32(ar->coex_gpio_pin);
	cmd->coex_version = __cpu_to_le32(WMI_NO_COEX_VERSION_SUPPORT);
	cmd->coex_gpio_pin1 = __cpu_to_le32(-1);
	cmd->coex_gpio_pin2 = __cpu_to_le32(-1);
	cmd->coex_gpio_pin3 = __cpu_to_le32(-1);
	cmd->num_tdls_vdevs = __cpu_to_le32(TARGET_10_4_NUM_TDLS_VDEVS);
	cmd->num_tdls_conn_table_entries = __cpu_to_le32(20);
	cmd->max_tdls_concurrent_sleep_sta = __cpu_to_le32(num_tdls_sleep_sta);
	cmd->max_tdls_concurrent_buffer_sta =
			__cpu_to_le32(TARGET_10_4_NUM_TDLS_BUFFER_STA);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi ext resource config host type %d firmware feature bitmap %08x\n",
		   type, fw_feature_biपंचांगap);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_gen_update_fw_tdls_state(काष्ठा ath10k *ar, u32 vdev_id,
					 क्रमागत wmi_tdls_state state)
अणु
	काष्ठा wmi_10_4_tdls_set_state_cmd *cmd;
	काष्ठा sk_buff *skb;
	u32 options = 0;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	अगर (test_bit(WMI_SERVICE_TDLS_EXPLICIT_MODE_ONLY, ar->wmi.svc_map) &&
	    state == WMI_TDLS_ENABLE_ACTIVE)
		state = WMI_TDLS_ENABLE_PASSIVE;

	अगर (test_bit(WMI_SERVICE_TDLS_UAPSD_BUFFER_STA, ar->wmi.svc_map))
		options |= WMI_TDLS_BUFFER_STA_EN;

	cmd = (काष्ठा wmi_10_4_tdls_set_state_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->state = __cpu_to_le32(state);
	cmd->notअगरication_पूर्णांकerval_ms = __cpu_to_le32(5000);
	cmd->tx_discovery_threshold = __cpu_to_le32(100);
	cmd->tx_tearकरोwn_threshold = __cpu_to_le32(5);
	cmd->rssi_tearकरोwn_threshold = __cpu_to_le32(-75);
	cmd->rssi_delta = __cpu_to_le32(-20);
	cmd->tdls_options = __cpu_to_le32(options);
	cmd->tdls_peer_traffic_ind_winकरोw = __cpu_to_le32(2);
	cmd->tdls_peer_traffic_response_समयout_ms = __cpu_to_le32(5000);
	cmd->tdls_puapsd_mask = __cpu_to_le32(0xf);
	cmd->tdls_puapsd_inactivity_समय_ms = __cpu_to_le32(0);
	cmd->tdls_puapsd_rx_frame_threshold = __cpu_to_le32(10);
	cmd->tearकरोwn_notअगरication_ms = __cpu_to_le32(10);
	cmd->tdls_peer_kickout_threshold = __cpu_to_le32(96);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi update fw tdls state %d for vdev %i\n",
		   state, vdev_id);
	वापस skb;
पूर्ण

अटल u32 ath10k_wmi_prepare_peer_qos(u8 uapsd_queues, u8 sp)
अणु
	u32 peer_qos = 0;

	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
		peer_qos |= WMI_TDLS_PEER_QOS_AC_VO;
	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
		peer_qos |= WMI_TDLS_PEER_QOS_AC_VI;
	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
		peer_qos |= WMI_TDLS_PEER_QOS_AC_BK;
	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
		peer_qos |= WMI_TDLS_PEER_QOS_AC_BE;

	peer_qos |= SM(sp, WMI_TDLS_PEER_SP);

	वापस peer_qos;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_op_gen_pdev_get_tpc_table_cmdid(काष्ठा ath10k *ar, u32 param)
अणु
	काष्ठा wmi_pdev_get_tpc_table_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_get_tpc_table_cmd *)skb->data;
	cmd->param = __cpu_to_le32(param);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev get tpc table param:%d\n", param);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_gen_tdls_peer_update(काष्ठा ath10k *ar,
				     स्थिर काष्ठा wmi_tdls_peer_update_cmd_arg *arg,
				     स्थिर काष्ठा wmi_tdls_peer_capab_arg *cap,
				     स्थिर काष्ठा wmi_channel_arg *chan_arg)
अणु
	काष्ठा wmi_10_4_tdls_peer_update_cmd *cmd;
	काष्ठा wmi_tdls_peer_capabilities *peer_cap;
	काष्ठा wmi_channel *chan;
	काष्ठा sk_buff *skb;
	u32 peer_qos;
	पूर्णांक len, chan_len;
	पूर्णांक i;

	/* tdls peer update cmd has place holder क्रम one channel*/
	chan_len = cap->peer_chan_len ? (cap->peer_chan_len - 1) : 0;

	len = माप(*cmd) + chan_len * माप(*chan);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(skb->data, 0, माप(*cmd));

	cmd = (काष्ठा wmi_10_4_tdls_peer_update_cmd *)skb->data;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, arg->addr);
	cmd->peer_state = __cpu_to_le32(arg->peer_state);

	peer_qos = ath10k_wmi_prepare_peer_qos(cap->peer_uapsd_queues,
					       cap->peer_max_sp);

	peer_cap = &cmd->peer_capab;
	peer_cap->peer_qos = __cpu_to_le32(peer_qos);
	peer_cap->buff_sta_support = __cpu_to_le32(cap->buff_sta_support);
	peer_cap->off_chan_support = __cpu_to_le32(cap->off_chan_support);
	peer_cap->peer_curr_operclass = __cpu_to_le32(cap->peer_curr_operclass);
	peer_cap->self_curr_operclass = __cpu_to_le32(cap->self_curr_operclass);
	peer_cap->peer_chan_len = __cpu_to_le32(cap->peer_chan_len);
	peer_cap->peer_operclass_len = __cpu_to_le32(cap->peer_operclass_len);

	क्रम (i = 0; i < WMI_TDLS_MAX_SUPP_OPER_CLASSES; i++)
		peer_cap->peer_operclass[i] = cap->peer_operclass[i];

	peer_cap->is_peer_responder = __cpu_to_le32(cap->is_peer_responder);
	peer_cap->pref_offchan_num = __cpu_to_le32(cap->pref_offchan_num);
	peer_cap->pref_offchan_bw = __cpu_to_le32(cap->pref_offchan_bw);

	क्रम (i = 0; i < cap->peer_chan_len; i++) अणु
		chan = (काष्ठा wmi_channel *)&peer_cap->peer_chan_list[i];
		ath10k_wmi_put_wmi_channel(ar, chan, &chan_arg[i]);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tdls peer update vdev %i state %d n_chans %u\n",
		   arg->vdev_id, arg->peer_state, cap->peer_chan_len);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_gen_radar_found(काष्ठा ath10k *ar,
				स्थिर काष्ठा ath10k_radar_found_info *arg)
अणु
	काष्ठा wmi_radar_found_info *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_radar_found_info *)skb->data;
	cmd->pri_min   = __cpu_to_le32(arg->pri_min);
	cmd->pri_max   = __cpu_to_le32(arg->pri_max);
	cmd->width_min = __cpu_to_le32(arg->width_min);
	cmd->width_max = __cpu_to_le32(arg->width_max);
	cmd->sidx_min  = __cpu_to_le32(arg->sidx_min);
	cmd->sidx_max  = __cpu_to_le32(arg->sidx_max);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi radar found pri_min %d pri_max %d width_min %d width_max %d sidx_min %d sidx_max %d\n",
		   arg->pri_min, arg->pri_max, arg->width_min,
		   arg->width_max, arg->sidx_min, arg->sidx_max);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_4_gen_per_peer_per_tid_cfg(काष्ठा ath10k *ar,
					 स्थिर काष्ठा wmi_per_peer_per_tid_cfg_arg *arg)
अणु
	काष्ठा wmi_peer_per_tid_cfg_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(skb->data, 0, माप(*cmd));

	cmd = (काष्ठा wmi_peer_per_tid_cfg_cmd *)skb->data;
	cmd->vdev_id = cpu_to_le32(arg->vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, arg->peer_macaddr.addr);
	cmd->tid = cpu_to_le32(arg->tid);
	cmd->ack_policy = cpu_to_le32(arg->ack_policy);
	cmd->aggr_control = cpu_to_le32(arg->aggr_control);
	cmd->rate_control = cpu_to_le32(arg->rate_ctrl);
	cmd->retry_count = cpu_to_le32(arg->retry_count);
	cmd->rcode_flags = cpu_to_le32(arg->rcode_flags);
	cmd->ext_tid_cfg_biपंचांगap = cpu_to_le32(arg->ext_tid_cfg_biपंचांगap);
	cmd->rtscts_ctrl = cpu_to_le32(arg->rtscts_ctrl);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi noack tid %d vdev id %d ack_policy %d aggr %u rate_ctrl %u rcflag %u retry_count %d rtscts %d ext_tid_cfg_bitmap %d mac_addr %pM\n",
		   arg->tid, arg->vdev_id, arg->ack_policy, arg->aggr_control,
		   arg->rate_ctrl, arg->rcode_flags, arg->retry_count,
		   arg->rtscts_ctrl, arg->ext_tid_cfg_biपंचांगap, arg->peer_macaddr.addr);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_op_gen_echo(काष्ठा ath10k *ar, u32 value)
अणु
	काष्ठा wmi_echo_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_echo_cmd *)skb->data;
	cmd->value = cpu_to_le32(value);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi echo value 0x%08x\n", value);
	वापस skb;
पूर्ण

पूर्णांक
ath10k_wmi_barrier(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;
	पूर्णांक समय_left;

	spin_lock_bh(&ar->data_lock);
	reinit_completion(&ar->wmi.barrier);
	spin_unlock_bh(&ar->data_lock);

	ret = ath10k_wmi_echo(ar, ATH10K_WMI_BARRIER_ECHO_ID);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit wmi echo: %d\n", ret);
		वापस ret;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->wmi.barrier,
						ATH10K_WMI_BARRIER_TIMEOUT_HZ);
	अगर (!समय_left)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_10_2_4_op_gen_bb_timing(काष्ठा ath10k *ar,
				   स्थिर काष्ठा wmi_bb_timing_cfg_arg *arg)
अणु
	काष्ठा wmi_pdev_bb_timing_cfg_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	cmd = (काष्ठा wmi_pdev_bb_timing_cfg_cmd *)skb->data;
	cmd->bb_tx_timing = __cpu_to_le32(arg->bb_tx_timing);
	cmd->bb_xpa_timing = __cpu_to_le32(arg->bb_xpa_timing);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev bb_tx_timing 0x%x bb_xpa_timing 0x%x\n",
		   arg->bb_tx_timing, arg->bb_xpa_timing);
	वापस skb;
पूर्ण

अटल स्थिर काष्ठा wmi_ops wmi_ops = अणु
	.rx = ath10k_wmi_op_rx,
	.map_svc = wmi_मुख्य_svc_map,

	.pull_scan = ath10k_wmi_op_pull_scan_ev,
	.pull_mgmt_rx = ath10k_wmi_op_pull_mgmt_rx_ev,
	.pull_ch_info = ath10k_wmi_op_pull_ch_info_ev,
	.pull_vdev_start = ath10k_wmi_op_pull_vdev_start_ev,
	.pull_peer_kick = ath10k_wmi_op_pull_peer_kick_ev,
	.pull_swba = ath10k_wmi_op_pull_swba_ev,
	.pull_phyerr_hdr = ath10k_wmi_op_pull_phyerr_ev_hdr,
	.pull_phyerr = ath10k_wmi_op_pull_phyerr_ev,
	.pull_svc_rdy = ath10k_wmi_मुख्य_op_pull_svc_rdy_ev,
	.pull_rdy = ath10k_wmi_op_pull_rdy_ev,
	.pull_fw_stats = ath10k_wmi_मुख्य_op_pull_fw_stats,
	.pull_roam_ev = ath10k_wmi_op_pull_roam_ev,
	.pull_echo_ev = ath10k_wmi_op_pull_echo_ev,

	.gen_pdev_suspend = ath10k_wmi_op_gen_pdev_suspend,
	.gen_pdev_resume = ath10k_wmi_op_gen_pdev_resume,
	.gen_pdev_set_rd = ath10k_wmi_op_gen_pdev_set_rd,
	.gen_pdev_set_param = ath10k_wmi_op_gen_pdev_set_param,
	.gen_init = ath10k_wmi_op_gen_init,
	.gen_start_scan = ath10k_wmi_op_gen_start_scan,
	.gen_stop_scan = ath10k_wmi_op_gen_stop_scan,
	.gen_vdev_create = ath10k_wmi_op_gen_vdev_create,
	.gen_vdev_delete = ath10k_wmi_op_gen_vdev_delete,
	.gen_vdev_start = ath10k_wmi_op_gen_vdev_start,
	.gen_vdev_stop = ath10k_wmi_op_gen_vdev_stop,
	.gen_vdev_up = ath10k_wmi_op_gen_vdev_up,
	.gen_vdev_करोwn = ath10k_wmi_op_gen_vdev_करोwn,
	.gen_vdev_set_param = ath10k_wmi_op_gen_vdev_set_param,
	.gen_vdev_install_key = ath10k_wmi_op_gen_vdev_install_key,
	.gen_vdev_spectral_conf = ath10k_wmi_op_gen_vdev_spectral_conf,
	.gen_vdev_spectral_enable = ath10k_wmi_op_gen_vdev_spectral_enable,
	/* .gen_vdev_wmm_conf not implemented */
	.gen_peer_create = ath10k_wmi_op_gen_peer_create,
	.gen_peer_delete = ath10k_wmi_op_gen_peer_delete,
	.gen_peer_flush = ath10k_wmi_op_gen_peer_flush,
	.gen_peer_set_param = ath10k_wmi_op_gen_peer_set_param,
	.gen_peer_assoc = ath10k_wmi_op_gen_peer_assoc,
	.gen_set_psmode = ath10k_wmi_op_gen_set_psmode,
	.gen_set_sta_ps = ath10k_wmi_op_gen_set_sta_ps,
	.gen_set_ap_ps = ath10k_wmi_op_gen_set_ap_ps,
	.gen_scan_chan_list = ath10k_wmi_op_gen_scan_chan_list,
	.gen_beacon_dma = ath10k_wmi_op_gen_beacon_dma,
	.gen_pdev_set_wmm = ath10k_wmi_op_gen_pdev_set_wmm,
	.gen_request_stats = ath10k_wmi_op_gen_request_stats,
	.gen_क्रमce_fw_hang = ath10k_wmi_op_gen_क्रमce_fw_hang,
	.gen_mgmt_tx = ath10k_wmi_op_gen_mgmt_tx,
	.gen_dbglog_cfg = ath10k_wmi_op_gen_dbglog_cfg,
	.gen_pktlog_enable = ath10k_wmi_op_gen_pktlog_enable,
	.gen_pktlog_disable = ath10k_wmi_op_gen_pktlog_disable,
	.gen_pdev_set_quiet_mode = ath10k_wmi_op_gen_pdev_set_quiet_mode,
	/* .gen_pdev_get_temperature not implemented */
	.gen_addba_clear_resp = ath10k_wmi_op_gen_addba_clear_resp,
	.gen_addba_send = ath10k_wmi_op_gen_addba_send,
	.gen_addba_set_resp = ath10k_wmi_op_gen_addba_set_resp,
	.gen_delba_send = ath10k_wmi_op_gen_delba_send,
	.fw_stats_fill = ath10k_wmi_मुख्य_op_fw_stats_fill,
	.get_vdev_subtype = ath10k_wmi_op_get_vdev_subtype,
	.gen_echo = ath10k_wmi_op_gen_echo,
	/* .gen_bcn_पंचांगpl not implemented */
	/* .gen_prb_पंचांगpl not implemented */
	/* .gen_p2p_go_bcn_ie not implemented */
	/* .gen_adaptive_qcs not implemented */
	/* .gen_pdev_enable_adaptive_cca not implemented */
पूर्ण;

अटल स्थिर काष्ठा wmi_ops wmi_10_1_ops = अणु
	.rx = ath10k_wmi_10_1_op_rx,
	.map_svc = wmi_10x_svc_map,
	.pull_svc_rdy = ath10k_wmi_10x_op_pull_svc_rdy_ev,
	.pull_fw_stats = ath10k_wmi_10x_op_pull_fw_stats,
	.gen_init = ath10k_wmi_10_1_op_gen_init,
	.gen_pdev_set_rd = ath10k_wmi_10x_op_gen_pdev_set_rd,
	.gen_start_scan = ath10k_wmi_10x_op_gen_start_scan,
	.gen_peer_assoc = ath10k_wmi_10_1_op_gen_peer_assoc,
	/* .gen_pdev_get_temperature not implemented */

	/* shared with मुख्य branch */
	.pull_scan = ath10k_wmi_op_pull_scan_ev,
	.pull_mgmt_rx = ath10k_wmi_op_pull_mgmt_rx_ev,
	.pull_ch_info = ath10k_wmi_op_pull_ch_info_ev,
	.pull_vdev_start = ath10k_wmi_op_pull_vdev_start_ev,
	.pull_peer_kick = ath10k_wmi_op_pull_peer_kick_ev,
	.pull_swba = ath10k_wmi_op_pull_swba_ev,
	.pull_phyerr_hdr = ath10k_wmi_op_pull_phyerr_ev_hdr,
	.pull_phyerr = ath10k_wmi_op_pull_phyerr_ev,
	.pull_rdy = ath10k_wmi_op_pull_rdy_ev,
	.pull_roam_ev = ath10k_wmi_op_pull_roam_ev,
	.pull_echo_ev = ath10k_wmi_op_pull_echo_ev,

	.gen_pdev_suspend = ath10k_wmi_op_gen_pdev_suspend,
	.gen_pdev_resume = ath10k_wmi_op_gen_pdev_resume,
	.gen_pdev_set_param = ath10k_wmi_op_gen_pdev_set_param,
	.gen_stop_scan = ath10k_wmi_op_gen_stop_scan,
	.gen_vdev_create = ath10k_wmi_op_gen_vdev_create,
	.gen_vdev_delete = ath10k_wmi_op_gen_vdev_delete,
	.gen_vdev_start = ath10k_wmi_op_gen_vdev_start,
	.gen_vdev_stop = ath10k_wmi_op_gen_vdev_stop,
	.gen_vdev_up = ath10k_wmi_op_gen_vdev_up,
	.gen_vdev_करोwn = ath10k_wmi_op_gen_vdev_करोwn,
	.gen_vdev_set_param = ath10k_wmi_op_gen_vdev_set_param,
	.gen_vdev_install_key = ath10k_wmi_op_gen_vdev_install_key,
	.gen_vdev_spectral_conf = ath10k_wmi_op_gen_vdev_spectral_conf,
	.gen_vdev_spectral_enable = ath10k_wmi_op_gen_vdev_spectral_enable,
	/* .gen_vdev_wmm_conf not implemented */
	.gen_peer_create = ath10k_wmi_op_gen_peer_create,
	.gen_peer_delete = ath10k_wmi_op_gen_peer_delete,
	.gen_peer_flush = ath10k_wmi_op_gen_peer_flush,
	.gen_peer_set_param = ath10k_wmi_op_gen_peer_set_param,
	.gen_set_psmode = ath10k_wmi_op_gen_set_psmode,
	.gen_set_sta_ps = ath10k_wmi_op_gen_set_sta_ps,
	.gen_set_ap_ps = ath10k_wmi_op_gen_set_ap_ps,
	.gen_scan_chan_list = ath10k_wmi_op_gen_scan_chan_list,
	.gen_beacon_dma = ath10k_wmi_op_gen_beacon_dma,
	.gen_pdev_set_wmm = ath10k_wmi_op_gen_pdev_set_wmm,
	.gen_request_stats = ath10k_wmi_op_gen_request_stats,
	.gen_क्रमce_fw_hang = ath10k_wmi_op_gen_क्रमce_fw_hang,
	.gen_mgmt_tx = ath10k_wmi_op_gen_mgmt_tx,
	.gen_dbglog_cfg = ath10k_wmi_op_gen_dbglog_cfg,
	.gen_pktlog_enable = ath10k_wmi_op_gen_pktlog_enable,
	.gen_pktlog_disable = ath10k_wmi_op_gen_pktlog_disable,
	.gen_pdev_set_quiet_mode = ath10k_wmi_op_gen_pdev_set_quiet_mode,
	.gen_addba_clear_resp = ath10k_wmi_op_gen_addba_clear_resp,
	.gen_addba_send = ath10k_wmi_op_gen_addba_send,
	.gen_addba_set_resp = ath10k_wmi_op_gen_addba_set_resp,
	.gen_delba_send = ath10k_wmi_op_gen_delba_send,
	.fw_stats_fill = ath10k_wmi_10x_op_fw_stats_fill,
	.get_vdev_subtype = ath10k_wmi_op_get_vdev_subtype,
	.gen_echo = ath10k_wmi_op_gen_echo,
	/* .gen_bcn_पंचांगpl not implemented */
	/* .gen_prb_पंचांगpl not implemented */
	/* .gen_p2p_go_bcn_ie not implemented */
	/* .gen_adaptive_qcs not implemented */
	/* .gen_pdev_enable_adaptive_cca not implemented */
पूर्ण;

अटल स्थिर काष्ठा wmi_ops wmi_10_2_ops = अणु
	.rx = ath10k_wmi_10_2_op_rx,
	.pull_fw_stats = ath10k_wmi_10_2_op_pull_fw_stats,
	.gen_init = ath10k_wmi_10_2_op_gen_init,
	.gen_peer_assoc = ath10k_wmi_10_2_op_gen_peer_assoc,
	/* .gen_pdev_get_temperature not implemented */

	/* shared with 10.1 */
	.map_svc = wmi_10x_svc_map,
	.pull_svc_rdy = ath10k_wmi_10x_op_pull_svc_rdy_ev,
	.gen_pdev_set_rd = ath10k_wmi_10x_op_gen_pdev_set_rd,
	.gen_start_scan = ath10k_wmi_10x_op_gen_start_scan,
	.gen_echo = ath10k_wmi_op_gen_echo,

	.pull_scan = ath10k_wmi_op_pull_scan_ev,
	.pull_mgmt_rx = ath10k_wmi_op_pull_mgmt_rx_ev,
	.pull_ch_info = ath10k_wmi_op_pull_ch_info_ev,
	.pull_vdev_start = ath10k_wmi_op_pull_vdev_start_ev,
	.pull_peer_kick = ath10k_wmi_op_pull_peer_kick_ev,
	.pull_swba = ath10k_wmi_op_pull_swba_ev,
	.pull_phyerr_hdr = ath10k_wmi_op_pull_phyerr_ev_hdr,
	.pull_phyerr = ath10k_wmi_op_pull_phyerr_ev,
	.pull_rdy = ath10k_wmi_op_pull_rdy_ev,
	.pull_roam_ev = ath10k_wmi_op_pull_roam_ev,
	.pull_echo_ev = ath10k_wmi_op_pull_echo_ev,

	.gen_pdev_suspend = ath10k_wmi_op_gen_pdev_suspend,
	.gen_pdev_resume = ath10k_wmi_op_gen_pdev_resume,
	.gen_pdev_set_param = ath10k_wmi_op_gen_pdev_set_param,
	.gen_stop_scan = ath10k_wmi_op_gen_stop_scan,
	.gen_vdev_create = ath10k_wmi_op_gen_vdev_create,
	.gen_vdev_delete = ath10k_wmi_op_gen_vdev_delete,
	.gen_vdev_start = ath10k_wmi_op_gen_vdev_start,
	.gen_vdev_stop = ath10k_wmi_op_gen_vdev_stop,
	.gen_vdev_up = ath10k_wmi_op_gen_vdev_up,
	.gen_vdev_करोwn = ath10k_wmi_op_gen_vdev_करोwn,
	.gen_vdev_set_param = ath10k_wmi_op_gen_vdev_set_param,
	.gen_vdev_install_key = ath10k_wmi_op_gen_vdev_install_key,
	.gen_vdev_spectral_conf = ath10k_wmi_op_gen_vdev_spectral_conf,
	.gen_vdev_spectral_enable = ath10k_wmi_op_gen_vdev_spectral_enable,
	/* .gen_vdev_wmm_conf not implemented */
	.gen_peer_create = ath10k_wmi_op_gen_peer_create,
	.gen_peer_delete = ath10k_wmi_op_gen_peer_delete,
	.gen_peer_flush = ath10k_wmi_op_gen_peer_flush,
	.gen_pdev_set_base_macaddr = ath10k_wmi_op_gen_pdev_set_base_macaddr,
	.gen_peer_set_param = ath10k_wmi_op_gen_peer_set_param,
	.gen_set_psmode = ath10k_wmi_op_gen_set_psmode,
	.gen_set_sta_ps = ath10k_wmi_op_gen_set_sta_ps,
	.gen_set_ap_ps = ath10k_wmi_op_gen_set_ap_ps,
	.gen_scan_chan_list = ath10k_wmi_op_gen_scan_chan_list,
	.gen_beacon_dma = ath10k_wmi_op_gen_beacon_dma,
	.gen_pdev_set_wmm = ath10k_wmi_op_gen_pdev_set_wmm,
	.gen_request_stats = ath10k_wmi_op_gen_request_stats,
	.gen_क्रमce_fw_hang = ath10k_wmi_op_gen_क्रमce_fw_hang,
	.gen_mgmt_tx = ath10k_wmi_op_gen_mgmt_tx,
	.gen_dbglog_cfg = ath10k_wmi_op_gen_dbglog_cfg,
	.gen_pktlog_enable = ath10k_wmi_op_gen_pktlog_enable,
	.gen_pktlog_disable = ath10k_wmi_op_gen_pktlog_disable,
	.gen_pdev_set_quiet_mode = ath10k_wmi_op_gen_pdev_set_quiet_mode,
	.gen_addba_clear_resp = ath10k_wmi_op_gen_addba_clear_resp,
	.gen_addba_send = ath10k_wmi_op_gen_addba_send,
	.gen_addba_set_resp = ath10k_wmi_op_gen_addba_set_resp,
	.gen_delba_send = ath10k_wmi_op_gen_delba_send,
	.fw_stats_fill = ath10k_wmi_10x_op_fw_stats_fill,
	.get_vdev_subtype = ath10k_wmi_op_get_vdev_subtype,
	/* .gen_pdev_enable_adaptive_cca not implemented */
पूर्ण;

अटल स्थिर काष्ठा wmi_ops wmi_10_2_4_ops = अणु
	.rx = ath10k_wmi_10_2_op_rx,
	.pull_fw_stats = ath10k_wmi_10_2_4_op_pull_fw_stats,
	.gen_init = ath10k_wmi_10_2_op_gen_init,
	.gen_peer_assoc = ath10k_wmi_10_2_op_gen_peer_assoc,
	.gen_pdev_get_temperature = ath10k_wmi_10_2_op_gen_pdev_get_temperature,
	.gen_pdev_bss_chan_info_req = ath10k_wmi_10_2_op_gen_pdev_bss_chan_info,

	/* shared with 10.1 */
	.map_svc = wmi_10x_svc_map,
	.pull_svc_rdy = ath10k_wmi_10x_op_pull_svc_rdy_ev,
	.gen_pdev_set_rd = ath10k_wmi_10x_op_gen_pdev_set_rd,
	.gen_start_scan = ath10k_wmi_10x_op_gen_start_scan,
	.gen_echo = ath10k_wmi_op_gen_echo,

	.pull_scan = ath10k_wmi_op_pull_scan_ev,
	.pull_mgmt_rx = ath10k_wmi_op_pull_mgmt_rx_ev,
	.pull_ch_info = ath10k_wmi_op_pull_ch_info_ev,
	.pull_vdev_start = ath10k_wmi_op_pull_vdev_start_ev,
	.pull_peer_kick = ath10k_wmi_op_pull_peer_kick_ev,
	.pull_swba = ath10k_wmi_10_2_4_op_pull_swba_ev,
	.pull_phyerr_hdr = ath10k_wmi_op_pull_phyerr_ev_hdr,
	.pull_phyerr = ath10k_wmi_op_pull_phyerr_ev,
	.pull_rdy = ath10k_wmi_op_pull_rdy_ev,
	.pull_roam_ev = ath10k_wmi_op_pull_roam_ev,
	.pull_echo_ev = ath10k_wmi_op_pull_echo_ev,

	.gen_pdev_suspend = ath10k_wmi_op_gen_pdev_suspend,
	.gen_pdev_resume = ath10k_wmi_op_gen_pdev_resume,
	.gen_pdev_set_param = ath10k_wmi_op_gen_pdev_set_param,
	.gen_stop_scan = ath10k_wmi_op_gen_stop_scan,
	.gen_vdev_create = ath10k_wmi_op_gen_vdev_create,
	.gen_vdev_delete = ath10k_wmi_op_gen_vdev_delete,
	.gen_vdev_start = ath10k_wmi_op_gen_vdev_start,
	.gen_vdev_stop = ath10k_wmi_op_gen_vdev_stop,
	.gen_vdev_up = ath10k_wmi_op_gen_vdev_up,
	.gen_vdev_करोwn = ath10k_wmi_op_gen_vdev_करोwn,
	.gen_vdev_set_param = ath10k_wmi_op_gen_vdev_set_param,
	.gen_vdev_install_key = ath10k_wmi_op_gen_vdev_install_key,
	.gen_vdev_spectral_conf = ath10k_wmi_op_gen_vdev_spectral_conf,
	.gen_vdev_spectral_enable = ath10k_wmi_op_gen_vdev_spectral_enable,
	.gen_peer_create = ath10k_wmi_op_gen_peer_create,
	.gen_peer_delete = ath10k_wmi_op_gen_peer_delete,
	.gen_peer_flush = ath10k_wmi_op_gen_peer_flush,
	.gen_peer_set_param = ath10k_wmi_op_gen_peer_set_param,
	.gen_set_psmode = ath10k_wmi_op_gen_set_psmode,
	.gen_set_sta_ps = ath10k_wmi_op_gen_set_sta_ps,
	.gen_set_ap_ps = ath10k_wmi_op_gen_set_ap_ps,
	.gen_scan_chan_list = ath10k_wmi_op_gen_scan_chan_list,
	.gen_beacon_dma = ath10k_wmi_op_gen_beacon_dma,
	.gen_pdev_set_wmm = ath10k_wmi_op_gen_pdev_set_wmm,
	.gen_request_stats = ath10k_wmi_op_gen_request_stats,
	.gen_क्रमce_fw_hang = ath10k_wmi_op_gen_क्रमce_fw_hang,
	.gen_mgmt_tx = ath10k_wmi_op_gen_mgmt_tx,
	.gen_dbglog_cfg = ath10k_wmi_op_gen_dbglog_cfg,
	.gen_pktlog_enable = ath10k_wmi_op_gen_pktlog_enable,
	.gen_pktlog_disable = ath10k_wmi_op_gen_pktlog_disable,
	.gen_pdev_set_quiet_mode = ath10k_wmi_op_gen_pdev_set_quiet_mode,
	.gen_addba_clear_resp = ath10k_wmi_op_gen_addba_clear_resp,
	.gen_addba_send = ath10k_wmi_op_gen_addba_send,
	.gen_addba_set_resp = ath10k_wmi_op_gen_addba_set_resp,
	.gen_delba_send = ath10k_wmi_op_gen_delba_send,
	.gen_pdev_get_tpc_config = ath10k_wmi_10_2_4_op_gen_pdev_get_tpc_config,
	.fw_stats_fill = ath10k_wmi_10x_op_fw_stats_fill,
	.gen_pdev_enable_adaptive_cca =
		ath10k_wmi_op_gen_pdev_enable_adaptive_cca,
	.get_vdev_subtype = ath10k_wmi_10_2_4_op_get_vdev_subtype,
	.gen_bb_timing = ath10k_wmi_10_2_4_op_gen_bb_timing,
	/* .gen_bcn_पंचांगpl not implemented */
	/* .gen_prb_पंचांगpl not implemented */
	/* .gen_p2p_go_bcn_ie not implemented */
	/* .gen_adaptive_qcs not implemented */
पूर्ण;

अटल स्थिर काष्ठा wmi_ops wmi_10_4_ops = अणु
	.rx = ath10k_wmi_10_4_op_rx,
	.map_svc = wmi_10_4_svc_map,

	.pull_fw_stats = ath10k_wmi_10_4_op_pull_fw_stats,
	.pull_scan = ath10k_wmi_op_pull_scan_ev,
	.pull_mgmt_rx = ath10k_wmi_10_4_op_pull_mgmt_rx_ev,
	.pull_ch_info = ath10k_wmi_10_4_op_pull_ch_info_ev,
	.pull_vdev_start = ath10k_wmi_op_pull_vdev_start_ev,
	.pull_peer_kick = ath10k_wmi_op_pull_peer_kick_ev,
	.pull_swba = ath10k_wmi_10_4_op_pull_swba_ev,
	.pull_phyerr_hdr = ath10k_wmi_10_4_op_pull_phyerr_ev_hdr,
	.pull_phyerr = ath10k_wmi_10_4_op_pull_phyerr_ev,
	.pull_svc_rdy = ath10k_wmi_मुख्य_op_pull_svc_rdy_ev,
	.pull_rdy = ath10k_wmi_op_pull_rdy_ev,
	.pull_roam_ev = ath10k_wmi_op_pull_roam_ev,
	.pull_dfs_status_ev = ath10k_wmi_10_4_op_pull_dfs_status_ev,
	.get_txbf_conf_scheme = ath10k_wmi_10_4_txbf_conf_scheme,

	.gen_pdev_suspend = ath10k_wmi_op_gen_pdev_suspend,
	.gen_pdev_resume = ath10k_wmi_op_gen_pdev_resume,
	.gen_pdev_set_base_macaddr = ath10k_wmi_op_gen_pdev_set_base_macaddr,
	.gen_pdev_set_rd = ath10k_wmi_10x_op_gen_pdev_set_rd,
	.gen_pdev_set_param = ath10k_wmi_op_gen_pdev_set_param,
	.gen_init = ath10k_wmi_10_4_op_gen_init,
	.gen_start_scan = ath10k_wmi_op_gen_start_scan,
	.gen_stop_scan = ath10k_wmi_op_gen_stop_scan,
	.gen_vdev_create = ath10k_wmi_op_gen_vdev_create,
	.gen_vdev_delete = ath10k_wmi_op_gen_vdev_delete,
	.gen_vdev_start = ath10k_wmi_op_gen_vdev_start,
	.gen_vdev_stop = ath10k_wmi_op_gen_vdev_stop,
	.gen_vdev_up = ath10k_wmi_op_gen_vdev_up,
	.gen_vdev_करोwn = ath10k_wmi_op_gen_vdev_करोwn,
	.gen_vdev_set_param = ath10k_wmi_op_gen_vdev_set_param,
	.gen_vdev_install_key = ath10k_wmi_op_gen_vdev_install_key,
	.gen_vdev_spectral_conf = ath10k_wmi_op_gen_vdev_spectral_conf,
	.gen_vdev_spectral_enable = ath10k_wmi_op_gen_vdev_spectral_enable,
	.gen_peer_create = ath10k_wmi_op_gen_peer_create,
	.gen_peer_delete = ath10k_wmi_op_gen_peer_delete,
	.gen_peer_flush = ath10k_wmi_op_gen_peer_flush,
	.gen_peer_set_param = ath10k_wmi_op_gen_peer_set_param,
	.gen_peer_assoc = ath10k_wmi_10_4_op_gen_peer_assoc,
	.gen_set_psmode = ath10k_wmi_op_gen_set_psmode,
	.gen_set_sta_ps = ath10k_wmi_op_gen_set_sta_ps,
	.gen_set_ap_ps = ath10k_wmi_op_gen_set_ap_ps,
	.gen_scan_chan_list = ath10k_wmi_op_gen_scan_chan_list,
	.gen_beacon_dma = ath10k_wmi_op_gen_beacon_dma,
	.gen_pdev_set_wmm = ath10k_wmi_op_gen_pdev_set_wmm,
	.gen_क्रमce_fw_hang = ath10k_wmi_op_gen_क्रमce_fw_hang,
	.gen_mgmt_tx = ath10k_wmi_op_gen_mgmt_tx,
	.gen_dbglog_cfg = ath10k_wmi_10_4_op_gen_dbglog_cfg,
	.gen_pktlog_enable = ath10k_wmi_op_gen_pktlog_enable,
	.gen_pktlog_disable = ath10k_wmi_op_gen_pktlog_disable,
	.gen_pdev_set_quiet_mode = ath10k_wmi_op_gen_pdev_set_quiet_mode,
	.gen_addba_clear_resp = ath10k_wmi_op_gen_addba_clear_resp,
	.gen_addba_send = ath10k_wmi_op_gen_addba_send,
	.gen_addba_set_resp = ath10k_wmi_op_gen_addba_set_resp,
	.gen_delba_send = ath10k_wmi_op_gen_delba_send,
	.fw_stats_fill = ath10k_wmi_10_4_op_fw_stats_fill,
	.ext_resource_config = ath10k_wmi_10_4_ext_resource_config,
	.gen_update_fw_tdls_state = ath10k_wmi_10_4_gen_update_fw_tdls_state,
	.gen_tdls_peer_update = ath10k_wmi_10_4_gen_tdls_peer_update,
	.gen_pdev_get_tpc_table_cmdid =
			ath10k_wmi_10_4_op_gen_pdev_get_tpc_table_cmdid,
	.gen_radar_found = ath10k_wmi_10_4_gen_radar_found,
	.gen_per_peer_per_tid_cfg = ath10k_wmi_10_4_gen_per_peer_per_tid_cfg,

	/* shared with 10.2 */
	.pull_echo_ev = ath10k_wmi_op_pull_echo_ev,
	.gen_request_stats = ath10k_wmi_op_gen_request_stats,
	.gen_pdev_get_temperature = ath10k_wmi_10_2_op_gen_pdev_get_temperature,
	.get_vdev_subtype = ath10k_wmi_10_4_op_get_vdev_subtype,
	.gen_pdev_bss_chan_info_req = ath10k_wmi_10_2_op_gen_pdev_bss_chan_info,
	.gen_echo = ath10k_wmi_op_gen_echo,
	.gen_pdev_get_tpc_config = ath10k_wmi_10_2_4_op_gen_pdev_get_tpc_config,
पूर्ण;

पूर्णांक ath10k_wmi_attach(काष्ठा ath10k *ar)
अणु
	चयन (ar->running_fw->fw_file.wmi_op_version) अणु
	हाल ATH10K_FW_WMI_OP_VERSION_10_4:
		ar->wmi.ops = &wmi_10_4_ops;
		ar->wmi.cmd = &wmi_10_4_cmd_map;
		ar->wmi.vdev_param = &wmi_10_4_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10_4_pdev_param_map;
		ar->wmi.peer_param = &wmi_peer_param_map;
		ar->wmi.peer_flags = &wmi_10_2_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_2_4:
		ar->wmi.cmd = &wmi_10_2_4_cmd_map;
		ar->wmi.ops = &wmi_10_2_4_ops;
		ar->wmi.vdev_param = &wmi_10_2_4_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10_2_4_pdev_param_map;
		ar->wmi.peer_param = &wmi_peer_param_map;
		ar->wmi.peer_flags = &wmi_10_2_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_2:
		ar->wmi.cmd = &wmi_10_2_cmd_map;
		ar->wmi.ops = &wmi_10_2_ops;
		ar->wmi.vdev_param = &wmi_10x_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10x_pdev_param_map;
		ar->wmi.peer_param = &wmi_peer_param_map;
		ar->wmi.peer_flags = &wmi_10_2_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_1:
		ar->wmi.cmd = &wmi_10x_cmd_map;
		ar->wmi.ops = &wmi_10_1_ops;
		ar->wmi.vdev_param = &wmi_10x_vdev_param_map;
		ar->wmi.pdev_param = &wmi_10x_pdev_param_map;
		ar->wmi.peer_param = &wmi_peer_param_map;
		ar->wmi.peer_flags = &wmi_10x_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_MAIN:
		ar->wmi.cmd = &wmi_cmd_map;
		ar->wmi.ops = &wmi_ops;
		ar->wmi.vdev_param = &wmi_vdev_param_map;
		ar->wmi.pdev_param = &wmi_pdev_param_map;
		ar->wmi.peer_param = &wmi_peer_param_map;
		ar->wmi.peer_flags = &wmi_peer_flags_map;
		ar->wmi_key_cipher = wmi_key_cipher_suites;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_TLV:
		ath10k_wmi_tlv_attach(ar);
		ar->wmi_key_cipher = wmi_tlv_key_cipher_suites;
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_UNSET:
	हाल ATH10K_FW_WMI_OP_VERSION_MAX:
		ath10k_err(ar, "unsupported WMI op version: %d\n",
			   ar->running_fw->fw_file.wmi_op_version);
		वापस -EINVAL;
	पूर्ण

	init_completion(&ar->wmi.service_पढ़ोy);
	init_completion(&ar->wmi.unअगरied_पढ़ोy);
	init_completion(&ar->wmi.barrier);
	init_completion(&ar->wmi.radar_confirm);

	INIT_WORK(&ar->svc_rdy_work, ath10k_wmi_event_service_पढ़ोy_work);
	INIT_WORK(&ar->radar_confirmation_work,
		  ath10k_radar_confirmation_work);

	अगर (test_bit(ATH10K_FW_FEATURE_MGMT_TX_BY_REF,
		     ar->running_fw->fw_file.fw_features)) अणु
		idr_init(&ar->wmi.mgmt_pending_tx);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_wmi_मुक्त_host_mem(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;

	/* मुक्त the host memory chunks requested by firmware */
	क्रम (i = 0; i < ar->wmi.num_mem_chunks; i++) अणु
		dma_मुक्त_coherent(ar->dev,
				  ar->wmi.mem_chunks[i].len,
				  ar->wmi.mem_chunks[i].vaddr,
				  ar->wmi.mem_chunks[i].paddr);
	पूर्ण

	ar->wmi.num_mem_chunks = 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_mgmt_tx_clean_up_pending(पूर्णांक msdu_id, व्योम *ptr,
					       व्योम *ctx)
अणु
	काष्ठा ath10k_mgmt_tx_pkt_addr *pkt_addr = ptr;
	काष्ठा ath10k *ar = ctx;
	काष्ठा sk_buff *msdu;

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "force cleanup mgmt msdu_id %u\n", msdu_id);

	msdu = pkt_addr->vaddr;
	dma_unmap_single(ar->dev, pkt_addr->paddr,
			 msdu->len, DMA_TO_DEVICE);
	ieee80211_मुक्त_txskb(ar->hw, msdu);

	वापस 0;
पूर्ण

व्योम ath10k_wmi_detach(काष्ठा ath10k *ar)
अणु
	अगर (test_bit(ATH10K_FW_FEATURE_MGMT_TX_BY_REF,
		     ar->running_fw->fw_file.fw_features)) अणु
		spin_lock_bh(&ar->data_lock);
		idr_क्रम_each(&ar->wmi.mgmt_pending_tx,
			     ath10k_wmi_mgmt_tx_clean_up_pending, ar);
		idr_destroy(&ar->wmi.mgmt_pending_tx);
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	cancel_work_sync(&ar->svc_rdy_work);
	dev_kमुक्त_skb(ar->svc_rdy_skb);
पूर्ण
