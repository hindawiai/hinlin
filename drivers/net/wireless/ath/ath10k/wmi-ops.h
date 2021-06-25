<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _WMI_OPS_H_
#घोषणा _WMI_OPS_H_

काष्ठा ath10k;
काष्ठा sk_buff;

काष्ठा wmi_ops अणु
	व्योम (*rx)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
	व्योम (*map_svc)(स्थिर __le32 *in, अचिन्हित दीर्घ *out, माप_प्रकार len);
	व्योम (*map_svc_ext)(स्थिर __le32 *in, अचिन्हित दीर्घ *out, माप_प्रकार len);

	पूर्णांक (*pull_scan)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			 काष्ठा wmi_scan_ev_arg *arg);
	पूर्णांक (*pull_mgmt_rx)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			    काष्ठा wmi_mgmt_rx_ev_arg *arg);
	पूर्णांक (*pull_mgmt_tx_compl)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				  काष्ठा wmi_tlv_mgmt_tx_compl_ev_arg *arg);
	पूर्णांक (*pull_mgmt_tx_bundle_compl)(
				काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				काष्ठा wmi_tlv_mgmt_tx_bundle_compl_ev_arg *arg);
	पूर्णांक (*pull_ch_info)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			    काष्ठा wmi_ch_info_ev_arg *arg);
	पूर्णांक (*pull_vdev_start)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			       काष्ठा wmi_vdev_start_ev_arg *arg);
	पूर्णांक (*pull_peer_kick)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			      काष्ठा wmi_peer_kick_ev_arg *arg);
	पूर्णांक (*pull_swba)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			 काष्ठा wmi_swba_ev_arg *arg);
	पूर्णांक (*pull_phyerr_hdr)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			       काष्ठा wmi_phyerr_hdr_arg *arg);
	पूर्णांक (*pull_phyerr)(काष्ठा ath10k *ar, स्थिर व्योम *phyerr_buf,
			   पूर्णांक left_len, काष्ठा wmi_phyerr_ev_arg *arg);
	पूर्णांक (*pull_svc_rdy)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			    काष्ठा wmi_svc_rdy_ev_arg *arg);
	पूर्णांक (*pull_rdy)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			काष्ठा wmi_rdy_ev_arg *arg);
	पूर्णांक (*pull_fw_stats)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			     काष्ठा ath10k_fw_stats *stats);
	पूर्णांक (*pull_roam_ev)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			    काष्ठा wmi_roam_ev_arg *arg);
	पूर्णांक (*pull_wow_event)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			      काष्ठा wmi_wow_ev_arg *arg);
	पूर्णांक (*pull_echo_ev)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			    काष्ठा wmi_echo_ev_arg *arg);
	पूर्णांक (*pull_dfs_status_ev)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				  काष्ठा wmi_dfs_status_ev_arg *arg);
	पूर्णांक (*pull_svc_avail)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			      काष्ठा wmi_svc_avail_ev_arg *arg);

	क्रमागत wmi_txbf_conf (*get_txbf_conf_scheme)(काष्ठा ath10k *ar);

	काष्ठा sk_buff *(*gen_pdev_suspend)(काष्ठा ath10k *ar, u32 suspend_opt);
	काष्ठा sk_buff *(*gen_pdev_resume)(काष्ठा ath10k *ar);
	काष्ठा sk_buff *(*gen_pdev_set_base_macaddr)(काष्ठा ath10k *ar,
						     स्थिर u8 macaddr[ETH_ALEN]);
	काष्ठा sk_buff *(*gen_pdev_set_rd)(काष्ठा ath10k *ar, u16 rd, u16 rd2g,
					   u16 rd5g, u16 ctl2g, u16 ctl5g,
					   क्रमागत wmi_dfs_region dfs_reg);
	काष्ठा sk_buff *(*gen_pdev_set_param)(काष्ठा ath10k *ar, u32 id,
					      u32 value);
	काष्ठा sk_buff *(*gen_init)(काष्ठा ath10k *ar);
	काष्ठा sk_buff *(*gen_start_scan)(काष्ठा ath10k *ar,
					  स्थिर काष्ठा wmi_start_scan_arg *arg);
	काष्ठा sk_buff *(*gen_stop_scan)(काष्ठा ath10k *ar,
					 स्थिर काष्ठा wmi_stop_scan_arg *arg);
	काष्ठा sk_buff *(*gen_vdev_create)(काष्ठा ath10k *ar, u32 vdev_id,
					   क्रमागत wmi_vdev_type type,
					   क्रमागत wmi_vdev_subtype subtype,
					   स्थिर u8 macaddr[ETH_ALEN]);
	काष्ठा sk_buff *(*gen_vdev_delete)(काष्ठा ath10k *ar, u32 vdev_id);
	काष्ठा sk_buff *(*gen_vdev_start)(काष्ठा ath10k *ar,
					  स्थिर काष्ठा wmi_vdev_start_request_arg *arg,
					  bool restart);
	काष्ठा sk_buff *(*gen_vdev_stop)(काष्ठा ath10k *ar, u32 vdev_id);
	काष्ठा sk_buff *(*gen_vdev_up)(काष्ठा ath10k *ar, u32 vdev_id, u32 aid,
				       स्थिर u8 *bssid);
	काष्ठा sk_buff *(*gen_vdev_करोwn)(काष्ठा ath10k *ar, u32 vdev_id);
	काष्ठा sk_buff *(*gen_vdev_set_param)(काष्ठा ath10k *ar, u32 vdev_id,
					      u32 param_id, u32 param_value);
	काष्ठा sk_buff *(*gen_vdev_install_key)(काष्ठा ath10k *ar,
						स्थिर काष्ठा wmi_vdev_install_key_arg *arg);
	काष्ठा sk_buff *(*gen_vdev_spectral_conf)(काष्ठा ath10k *ar,
						  स्थिर काष्ठा wmi_vdev_spectral_conf_arg *arg);
	काष्ठा sk_buff *(*gen_vdev_spectral_enable)(काष्ठा ath10k *ar, u32 vdev_id,
						    u32 trigger, u32 enable);
	काष्ठा sk_buff *(*gen_vdev_wmm_conf)(काष्ठा ath10k *ar, u32 vdev_id,
					     स्थिर काष्ठा wmi_wmm_params_all_arg *arg);
	काष्ठा sk_buff *(*gen_peer_create)(काष्ठा ath10k *ar, u32 vdev_id,
					   स्थिर u8 peer_addr[ETH_ALEN],
					   क्रमागत wmi_peer_type peer_type);
	काष्ठा sk_buff *(*gen_peer_delete)(काष्ठा ath10k *ar, u32 vdev_id,
					   स्थिर u8 peer_addr[ETH_ALEN]);
	काष्ठा sk_buff *(*gen_peer_flush)(काष्ठा ath10k *ar, u32 vdev_id,
					  स्थिर u8 peer_addr[ETH_ALEN],
					  u32 tid_biपंचांगap);
	काष्ठा sk_buff *(*gen_peer_set_param)(काष्ठा ath10k *ar, u32 vdev_id,
					      स्थिर u8 *peer_addr,
					      क्रमागत wmi_peer_param param_id,
					      u32 param_value);
	काष्ठा sk_buff *(*gen_peer_assoc)(काष्ठा ath10k *ar,
					  स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg);
	काष्ठा sk_buff *(*gen_set_psmode)(काष्ठा ath10k *ar, u32 vdev_id,
					  क्रमागत wmi_sta_ps_mode psmode);
	काष्ठा sk_buff *(*gen_set_sta_ps)(काष्ठा ath10k *ar, u32 vdev_id,
					  क्रमागत wmi_sta_घातersave_param param_id,
					  u32 value);
	काष्ठा sk_buff *(*gen_set_ap_ps)(काष्ठा ath10k *ar, u32 vdev_id,
					 स्थिर u8 *mac,
					 क्रमागत wmi_ap_ps_peer_param param_id,
					 u32 value);
	काष्ठा sk_buff *(*gen_scan_chan_list)(काष्ठा ath10k *ar,
					      स्थिर काष्ठा wmi_scan_chan_list_arg *arg);
	काष्ठा sk_buff *(*gen_scan_prob_req_oui)(काष्ठा ath10k *ar,
						 u32 prob_req_oui);
	काष्ठा sk_buff *(*gen_beacon_dma)(काष्ठा ath10k *ar, u32 vdev_id,
					  स्थिर व्योम *bcn, माप_प्रकार bcn_len,
					  u32 bcn_paddr, bool dtim_zero,
					  bool deliver_cab);
	काष्ठा sk_buff *(*gen_pdev_set_wmm)(काष्ठा ath10k *ar,
					    स्थिर काष्ठा wmi_wmm_params_all_arg *arg);
	काष्ठा sk_buff *(*gen_request_stats)(काष्ठा ath10k *ar, u32 stats_mask);
	काष्ठा sk_buff *(*gen_request_peer_stats_info)(काष्ठा ath10k *ar,
						       u32 vdev_id,
						       क्रमागत
						       wmi_peer_stats_info_request_type
						       type,
						       u8 *addr,
						       u32 reset);
	काष्ठा sk_buff *(*gen_क्रमce_fw_hang)(काष्ठा ath10k *ar,
					     क्रमागत wmi_क्रमce_fw_hang_type type,
					     u32 delay_ms);
	काष्ठा sk_buff *(*gen_mgmt_tx)(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
	काष्ठा sk_buff *(*gen_mgmt_tx_send)(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb,
					    dma_addr_t paddr);
	पूर्णांक (*cleanup_mgmt_tx_send)(काष्ठा ath10k *ar, काष्ठा sk_buff *msdu);
	काष्ठा sk_buff *(*gen_dbglog_cfg)(काष्ठा ath10k *ar, u64 module_enable,
					  u32 log_level);
	काष्ठा sk_buff *(*gen_pktlog_enable)(काष्ठा ath10k *ar, u32 filter);
	काष्ठा sk_buff *(*gen_pktlog_disable)(काष्ठा ath10k *ar);
	काष्ठा sk_buff *(*gen_pdev_set_quiet_mode)(काष्ठा ath10k *ar,
						   u32 period, u32 duration,
						   u32 next_offset,
						   u32 enabled);
	काष्ठा sk_buff *(*gen_pdev_get_temperature)(काष्ठा ath10k *ar);
	काष्ठा sk_buff *(*gen_addba_clear_resp)(काष्ठा ath10k *ar, u32 vdev_id,
						स्थिर u8 *mac);
	काष्ठा sk_buff *(*gen_addba_send)(काष्ठा ath10k *ar, u32 vdev_id,
					  स्थिर u8 *mac, u32 tid, u32 buf_size);
	काष्ठा sk_buff *(*gen_addba_set_resp)(काष्ठा ath10k *ar, u32 vdev_id,
					      स्थिर u8 *mac, u32 tid,
					      u32 status);
	काष्ठा sk_buff *(*gen_delba_send)(काष्ठा ath10k *ar, u32 vdev_id,
					  स्थिर u8 *mac, u32 tid, u32 initiator,
					  u32 reason);
	काष्ठा sk_buff *(*gen_bcn_पंचांगpl)(काष्ठा ath10k *ar, u32 vdev_id,
					u32 tim_ie_offset, काष्ठा sk_buff *bcn,
					u32 prb_caps, u32 prb_erp,
					व्योम *prb_ies, माप_प्रकार prb_ies_len);
	काष्ठा sk_buff *(*gen_prb_पंचांगpl)(काष्ठा ath10k *ar, u32 vdev_id,
					काष्ठा sk_buff *bcn);
	काष्ठा sk_buff *(*gen_p2p_go_bcn_ie)(काष्ठा ath10k *ar, u32 vdev_id,
					     स्थिर u8 *p2p_ie);
	काष्ठा sk_buff *(*gen_vdev_sta_uapsd)(काष्ठा ath10k *ar, u32 vdev_id,
					      स्थिर u8 peer_addr[ETH_ALEN],
					      स्थिर काष्ठा wmi_sta_uapsd_स्वतः_trig_arg *args,
					      u32 num_ac);
	काष्ठा sk_buff *(*gen_sta_keepalive)(काष्ठा ath10k *ar,
					     स्थिर काष्ठा wmi_sta_keepalive_arg *arg);
	काष्ठा sk_buff *(*gen_wow_enable)(काष्ठा ath10k *ar);
	काष्ठा sk_buff *(*gen_wow_add_wakeup_event)(काष्ठा ath10k *ar, u32 vdev_id,
						    क्रमागत wmi_wow_wakeup_event event,
						    u32 enable);
	काष्ठा sk_buff *(*gen_wow_host_wakeup_ind)(काष्ठा ath10k *ar);
	काष्ठा sk_buff *(*gen_wow_add_pattern)(काष्ठा ath10k *ar, u32 vdev_id,
					       u32 pattern_id,
					       स्थिर u8 *pattern,
					       स्थिर u8 *mask,
					       पूर्णांक pattern_len,
					       पूर्णांक pattern_offset);
	काष्ठा sk_buff *(*gen_wow_del_pattern)(काष्ठा ath10k *ar, u32 vdev_id,
					       u32 pattern_id);
	काष्ठा sk_buff *(*gen_update_fw_tdls_state)(काष्ठा ath10k *ar,
						    u32 vdev_id,
						    क्रमागत wmi_tdls_state state);
	काष्ठा sk_buff *(*gen_tdls_peer_update)(काष्ठा ath10k *ar,
						स्थिर काष्ठा wmi_tdls_peer_update_cmd_arg *arg,
						स्थिर काष्ठा wmi_tdls_peer_capab_arg *cap,
						स्थिर काष्ठा wmi_channel_arg *chan);
	काष्ठा sk_buff *(*gen_radar_found)
			(काष्ठा ath10k *ar,
			 स्थिर काष्ठा ath10k_radar_found_info *arg);
	काष्ठा sk_buff *(*gen_adaptive_qcs)(काष्ठा ath10k *ar, bool enable);
	काष्ठा sk_buff *(*gen_pdev_get_tpc_config)(काष्ठा ath10k *ar,
						   u32 param);
	व्योम (*fw_stats_fill)(काष्ठा ath10k *ar,
			      काष्ठा ath10k_fw_stats *fw_stats,
			      अक्षर *buf);
	काष्ठा sk_buff *(*gen_pdev_enable_adaptive_cca)(काष्ठा ath10k *ar,
							u8 enable,
							u32 detect_level,
							u32 detect_margin);
	काष्ठा sk_buff *(*ext_resource_config)(काष्ठा ath10k *ar,
					       क्रमागत wmi_host_platक्रमm_type type,
					       u32 fw_feature_biपंचांगap);
	पूर्णांक (*get_vdev_subtype)(काष्ठा ath10k *ar,
				क्रमागत wmi_vdev_subtype subtype);
	काष्ठा sk_buff *(*gen_wow_config_pno)(काष्ठा ath10k *ar,
					      u32 vdev_id,
					      काष्ठा wmi_pno_scan_req *pno_scan);
	काष्ठा sk_buff *(*gen_pdev_bss_chan_info_req)
					(काष्ठा ath10k *ar,
					 क्रमागत wmi_bss_survey_req_type type);
	काष्ठा sk_buff *(*gen_echo)(काष्ठा ath10k *ar, u32 value);
	काष्ठा sk_buff *(*gen_pdev_get_tpc_table_cmdid)(काष्ठा ath10k *ar,
							u32 param);
	काष्ठा sk_buff *(*gen_bb_timing)
			(काष्ठा ath10k *ar,
			 स्थिर काष्ठा wmi_bb_timing_cfg_arg *arg);
	काष्ठा sk_buff *(*gen_per_peer_per_tid_cfg)(काष्ठा ath10k *ar,
						    स्थिर काष्ठा wmi_per_peer_per_tid_cfg_arg *arg);

पूर्ण;

पूर्णांक ath10k_wmi_cmd_send(काष्ठा ath10k *ar, काष्ठा sk_buff *skb, u32 cmd_id);

अटल अंतरभूत पूर्णांक
ath10k_wmi_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	अगर (WARN_ON_ONCE(!ar->wmi.ops->rx))
		वापस -EOPNOTSUPP;

	ar->wmi.ops->rx(ar, skb);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_map_svc(काष्ठा ath10k *ar, स्थिर __le32 *in, अचिन्हित दीर्घ *out,
		   माप_प्रकार len)
अणु
	अगर (!ar->wmi.ops->map_svc)
		वापस -EOPNOTSUPP;

	ar->wmi.ops->map_svc(in, out, len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_map_svc_ext(काष्ठा ath10k *ar, स्थिर __le32 *in, अचिन्हित दीर्घ *out,
		       माप_प्रकार len)
अणु
	अगर (!ar->wmi.ops->map_svc_ext)
		वापस -EOPNOTSUPP;

	ar->wmi.ops->map_svc_ext(in, out, len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_scan(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
		     काष्ठा wmi_scan_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_scan)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_scan(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_mgmt_tx_compl(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			      काष्ठा wmi_tlv_mgmt_tx_compl_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_mgmt_tx_compl)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_mgmt_tx_compl(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_mgmt_tx_bundle_compl(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				     काष्ठा wmi_tlv_mgmt_tx_bundle_compl_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_mgmt_tx_bundle_compl)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_mgmt_tx_bundle_compl(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_mgmt_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			काष्ठा wmi_mgmt_rx_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_mgmt_rx)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_mgmt_rx(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_ch_info(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			काष्ठा wmi_ch_info_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_ch_info)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_ch_info(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_vdev_start(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			   काष्ठा wmi_vdev_start_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_vdev_start)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_vdev_start(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_peer_kick(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			  काष्ठा wmi_peer_kick_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_peer_kick)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_peer_kick(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_swba(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
		     काष्ठा wmi_swba_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_swba)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_swba(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_phyerr_hdr(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			   काष्ठा wmi_phyerr_hdr_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_phyerr_hdr)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_phyerr_hdr(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_phyerr(काष्ठा ath10k *ar, स्थिर व्योम *phyerr_buf,
		       पूर्णांक left_len, काष्ठा wmi_phyerr_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_phyerr)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_phyerr(ar, phyerr_buf, left_len, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_svc_rdy(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			काष्ठा wmi_svc_rdy_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_svc_rdy)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_svc_rdy(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_rdy(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
		    काष्ठा wmi_rdy_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_rdy)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_rdy(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_svc_avail(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			  काष्ठा wmi_svc_avail_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_svc_avail)
		वापस -EOPNOTSUPP;
	वापस ar->wmi.ops->pull_svc_avail(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_fw_stats(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			 काष्ठा ath10k_fw_stats *stats)
अणु
	अगर (!ar->wmi.ops->pull_fw_stats)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_fw_stats(ar, skb, stats);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_roam_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			काष्ठा wmi_roam_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_roam_ev)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_roam_ev(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_wow_event(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			  काष्ठा wmi_wow_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_wow_event)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_wow_event(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_echo_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			काष्ठा wmi_echo_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_echo_ev)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_echo_ev(ar, skb, arg);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pull_dfs_status(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			   काष्ठा wmi_dfs_status_ev_arg *arg)
अणु
	अगर (!ar->wmi.ops->pull_dfs_status_ev)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->pull_dfs_status_ev(ar, skb, arg);
पूर्ण

अटल अंतरभूत क्रमागत wmi_txbf_conf
ath10k_wmi_get_txbf_conf_scheme(काष्ठा ath10k *ar)
अणु
	अगर (!ar->wmi.ops->get_txbf_conf_scheme)
		वापस WMI_TXBF_CONF_UNSUPPORTED;

	वापस ar->wmi.ops->get_txbf_conf_scheme(ar);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_cleanup_mgmt_tx_send(काष्ठा ath10k *ar, काष्ठा sk_buff *msdu)
अणु
	अगर (!ar->wmi.ops->cleanup_mgmt_tx_send)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->cleanup_mgmt_tx_send(ar, msdu);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_mgmt_tx_send(काष्ठा ath10k *ar, काष्ठा sk_buff *msdu,
			dma_addr_t paddr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (!ar->wmi.ops->gen_mgmt_tx_send)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_mgmt_tx_send(ar, msdu, paddr);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	ret = ath10k_wmi_cmd_send(ar, skb,
				  ar->wmi.cmd->mgmt_tx_send_cmdid);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_mgmt_tx(काष्ठा ath10k *ar, काष्ठा sk_buff *msdu)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (!ar->wmi.ops->gen_mgmt_tx)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_mgmt_tx(ar, msdu);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	ret = ath10k_wmi_cmd_send(ar, skb,
				  ar->wmi.cmd->mgmt_tx_cmdid);
	अगर (ret)
		वापस ret;

	/* FIXME There's no ACK event क्रम Management Tx. This probably
	 * shouldn't be called here either.
	 */
	info->flags |= IEEE80211_TX_STAT_ACK;
	ieee80211_tx_status_irqsafe(ar->hw, msdu);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_set_regकरोमुख्य(काष्ठा ath10k *ar, u16 rd, u16 rd2g, u16 rd5g,
			      u16 ctl2g, u16 ctl5g,
			      क्रमागत wmi_dfs_region dfs_reg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_set_rd)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_set_rd(ar, rd, rd2g, rd5g, ctl2g, ctl5g,
					   dfs_reg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_set_regकरोमुख्य_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_set_base_macaddr(काष्ठा ath10k *ar, स्थिर u8 macaddr[ETH_ALEN])
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_set_base_macaddr)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_set_base_macaddr(ar, macaddr);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_set_base_macaddr_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_suspend_target(काष्ठा ath10k *ar, u32 suspend_opt)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_suspend)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_suspend(ar, suspend_opt);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->pdev_suspend_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_resume_target(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_resume)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_resume(ar);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->pdev_resume_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_set_param(काष्ठा ath10k *ar, u32 id, u32 value)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_set_param)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_set_param(ar, id, value);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->pdev_set_param_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_cmd_init(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_init)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_init(ar);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->init_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_start_scan(काष्ठा ath10k *ar,
		      स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_start_scan)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_start_scan(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->start_scan_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_stop_scan(काष्ठा ath10k *ar, स्थिर काष्ठा wmi_stop_scan_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_stop_scan)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_stop_scan(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->stop_scan_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_create(काष्ठा ath10k *ar, u32 vdev_id,
		       क्रमागत wmi_vdev_type type,
		       क्रमागत wmi_vdev_subtype subtype,
		       स्थिर u8 macaddr[ETH_ALEN])
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_create)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_create(ar, vdev_id, type, subtype, macaddr);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->vdev_create_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_delete(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_delete)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_delete(ar, vdev_id);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->vdev_delete_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_start(काष्ठा ath10k *ar,
		      स्थिर काष्ठा wmi_vdev_start_request_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_start)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_start(ar, arg, false);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->vdev_start_request_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_restart(काष्ठा ath10k *ar,
			स्थिर काष्ठा wmi_vdev_start_request_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_start)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_start(ar, arg, true);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->vdev_restart_request_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_stop(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_stop)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_stop(ar, vdev_id);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->vdev_stop_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_up(काष्ठा ath10k *ar, u32 vdev_id, u32 aid, स्थिर u8 *bssid)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_up)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_up(ar, vdev_id, aid, bssid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->vdev_up_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_करोwn(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_करोwn)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_करोwn(ar, vdev_id);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->vdev_करोwn_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_set_param(काष्ठा ath10k *ar, u32 vdev_id, u32 param_id,
			  u32 param_value)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_set_param)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_set_param(ar, vdev_id, param_id,
					      param_value);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->vdev_set_param_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_install_key(काष्ठा ath10k *ar,
			    स्थिर काष्ठा wmi_vdev_install_key_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_vdev_install_key)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_install_key(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->vdev_install_key_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_spectral_conf(काष्ठा ath10k *ar,
			      स्थिर काष्ठा wmi_vdev_spectral_conf_arg *arg)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_vdev_spectral_conf)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_spectral_conf(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->vdev_spectral_scan_configure_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_spectral_enable(काष्ठा ath10k *ar, u32 vdev_id, u32 trigger,
				u32 enable)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_vdev_spectral_enable)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_spectral_enable(ar, vdev_id, trigger,
						    enable);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->vdev_spectral_scan_enable_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_sta_uapsd(काष्ठा ath10k *ar, u32 vdev_id,
			  स्थिर u8 peer_addr[ETH_ALEN],
			  स्थिर काष्ठा wmi_sta_uapsd_स्वतः_trig_arg *args,
			  u32 num_ac)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_vdev_sta_uapsd)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_vdev_sta_uapsd(ar, vdev_id, peer_addr, args,
					      num_ac);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->sta_uapsd_स्वतः_trig_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_vdev_wmm_conf(काष्ठा ath10k *ar, u32 vdev_id,
			 स्थिर काष्ठा wmi_wmm_params_all_arg *arg)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	skb = ar->wmi.ops->gen_vdev_wmm_conf(ar, vdev_id, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->vdev_set_wmm_params_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_peer_create(काष्ठा ath10k *ar, u32 vdev_id,
		       स्थिर u8 peer_addr[ETH_ALEN],
		       क्रमागत wmi_peer_type peer_type)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_peer_create)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_peer_create(ar, vdev_id, peer_addr, peer_type);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->peer_create_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_peer_delete(काष्ठा ath10k *ar, u32 vdev_id,
		       स्थिर u8 peer_addr[ETH_ALEN])
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_peer_delete)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_peer_delete(ar, vdev_id, peer_addr);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->peer_delete_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_peer_flush(काष्ठा ath10k *ar, u32 vdev_id,
		      स्थिर u8 peer_addr[ETH_ALEN], u32 tid_biपंचांगap)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_peer_flush)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_peer_flush(ar, vdev_id, peer_addr, tid_biपंचांगap);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->peer_flush_tids_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_peer_set_param(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *peer_addr,
			  क्रमागत wmi_peer_param param_id, u32 param_value)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_peer_set_param)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_peer_set_param(ar, vdev_id, peer_addr, param_id,
					      param_value);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->peer_set_param_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_set_psmode(काष्ठा ath10k *ar, u32 vdev_id,
		      क्रमागत wmi_sta_ps_mode psmode)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_set_psmode)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_set_psmode(ar, vdev_id, psmode);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->sta_घातersave_mode_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_set_sta_ps_param(काष्ठा ath10k *ar, u32 vdev_id,
			    क्रमागत wmi_sta_घातersave_param param_id, u32 value)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_set_sta_ps)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_set_sta_ps(ar, vdev_id, param_id, value);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->sta_घातersave_param_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_set_ap_ps_param(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
			   क्रमागत wmi_ap_ps_peer_param param_id, u32 value)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_set_ap_ps)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_set_ap_ps(ar, vdev_id, mac, param_id, value);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->ap_ps_peer_param_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_scan_chan_list(काष्ठा ath10k *ar,
			  स्थिर काष्ठा wmi_scan_chan_list_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_scan_chan_list)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_scan_chan_list(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->scan_chan_list_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_scan_prob_req_oui(काष्ठा ath10k *ar, स्थिर u8 mac_addr[ETH_ALEN])
अणु
	काष्ठा sk_buff *skb;
	u32 prob_req_oui;

	prob_req_oui = (((u32)mac_addr[0]) << 16) |
		       (((u32)mac_addr[1]) << 8) | mac_addr[2];

	अगर (!ar->wmi.ops->gen_scan_prob_req_oui)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_scan_prob_req_oui(ar, prob_req_oui);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
			ar->wmi.cmd->scan_prob_req_oui_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_peer_assoc(काष्ठा ath10k *ar,
		      स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_peer_assoc)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_peer_assoc(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->peer_assoc_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_beacon_send_ref_noरुको(काष्ठा ath10k *ar, u32 vdev_id,
				  स्थिर व्योम *bcn, माप_प्रकार bcn_len,
				  u32 bcn_paddr, bool dtim_zero,
				  bool deliver_cab)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (!ar->wmi.ops->gen_beacon_dma)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_beacon_dma(ar, vdev_id, bcn, bcn_len, bcn_paddr,
					  dtim_zero, deliver_cab);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	ret = ath10k_wmi_cmd_send_noरुको(ar, skb,
					 ar->wmi.cmd->pdev_send_bcn_cmdid);
	अगर (ret) अणु
		dev_kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_set_wmm_params(काष्ठा ath10k *ar,
			       स्थिर काष्ठा wmi_wmm_params_all_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_set_wmm)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_set_wmm(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_set_wmm_params_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_request_stats(काष्ठा ath10k *ar, u32 stats_mask)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_request_stats)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_request_stats(ar, stats_mask);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->request_stats_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_request_peer_stats_info(काष्ठा ath10k *ar,
				   u32 vdev_id,
				   क्रमागत wmi_peer_stats_info_request_type type,
				   u8 *addr,
				   u32 reset)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_request_peer_stats_info)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_request_peer_stats_info(ar,
						       vdev_id,
						       type,
						       addr,
						       reset);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->request_peer_stats_info_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_क्रमce_fw_hang(काष्ठा ath10k *ar,
			 क्रमागत wmi_क्रमce_fw_hang_type type, u32 delay_ms)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_क्रमce_fw_hang)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_क्रमce_fw_hang(ar, type, delay_ms);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->क्रमce_fw_hang_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_dbglog_cfg(काष्ठा ath10k *ar, u64 module_enable, u32 log_level)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_dbglog_cfg)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_dbglog_cfg(ar, module_enable, log_level);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->dbglog_cfg_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_pktlog_enable(काष्ठा ath10k *ar, u32 filter)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pktlog_enable)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pktlog_enable(ar, filter);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->pdev_pktlog_enable_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_pktlog_disable(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pktlog_disable)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pktlog_disable(ar);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_pktlog_disable_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_set_quiet_mode(काष्ठा ath10k *ar, u32 period, u32 duration,
			       u32 next_offset, u32 enabled)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_set_quiet_mode)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_set_quiet_mode(ar, period, duration,
						   next_offset, enabled);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_set_quiet_mode_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_get_temperature(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_get_temperature)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_get_temperature(ar);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_get_temperature_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_addba_clear_resp(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_addba_clear_resp)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_addba_clear_resp(ar, vdev_id, mac);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->addba_clear_resp_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_addba_send(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
		      u32 tid, u32 buf_size)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_addba_send)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_addba_send(ar, vdev_id, mac, tid, buf_size);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->addba_send_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_addba_set_resp(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
			  u32 tid, u32 status)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_addba_set_resp)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_addba_set_resp(ar, vdev_id, mac, tid, status);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->addba_set_resp_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_delba_send(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
		      u32 tid, u32 initiator, u32 reason)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_delba_send)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_delba_send(ar, vdev_id, mac, tid, initiator,
					  reason);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->delba_send_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_bcn_पंचांगpl(काष्ठा ath10k *ar, u32 vdev_id, u32 tim_ie_offset,
		    काष्ठा sk_buff *bcn, u32 prb_caps, u32 prb_erp,
		    व्योम *prb_ies, माप_प्रकार prb_ies_len)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_bcn_पंचांगpl)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_bcn_पंचांगpl(ar, vdev_id, tim_ie_offset, bcn,
					prb_caps, prb_erp, prb_ies,
					prb_ies_len);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->bcn_पंचांगpl_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_prb_पंचांगpl(काष्ठा ath10k *ar, u32 vdev_id, काष्ठा sk_buff *prb)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_prb_पंचांगpl)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_prb_पंचांगpl(ar, vdev_id, prb);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->prb_पंचांगpl_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_p2p_go_bcn_ie(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *p2p_ie)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_p2p_go_bcn_ie)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_p2p_go_bcn_ie(ar, vdev_id, p2p_ie);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->p2p_go_set_beacon_ie);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_sta_keepalive(काष्ठा ath10k *ar,
			 स्थिर काष्ठा wmi_sta_keepalive_arg *arg)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_sta_keepalive)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_sta_keepalive(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->sta_keepalive_cmd;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_wow_enable(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_wow_enable)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_enable(ar);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->wow_enable_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_wow_add_wakeup_event(काष्ठा ath10k *ar, u32 vdev_id,
				क्रमागत wmi_wow_wakeup_event event,
				u32 enable)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_wow_add_wakeup_event)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_add_wakeup_event(ar, vdev_id, event, enable);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->wow_enable_disable_wake_event_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_wow_host_wakeup_ind(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_wow_host_wakeup_ind)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_host_wakeup_ind(ar);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->wow_hostwakeup_from_sleep_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_wow_add_pattern(काष्ठा ath10k *ar, u32 vdev_id, u32 pattern_id,
			   स्थिर u8 *pattern, स्थिर u8 *mask,
			   पूर्णांक pattern_len, पूर्णांक pattern_offset)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_wow_add_pattern)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_add_pattern(ar, vdev_id, pattern_id,
					       pattern, mask, pattern_len,
					       pattern_offset);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->wow_add_wake_pattern_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_wow_del_pattern(काष्ठा ath10k *ar, u32 vdev_id, u32 pattern_id)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_wow_del_pattern)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_del_pattern(ar, vdev_id, pattern_id);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->wow_del_wake_pattern_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_wow_config_pno(काष्ठा ath10k *ar, u32 vdev_id,
			  काष्ठा wmi_pno_scan_req  *pno_scan)
अणु
	काष्ठा sk_buff *skb;
	u32 cmd_id;

	अगर (!ar->wmi.ops->gen_wow_config_pno)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_config_pno(ar, vdev_id, pno_scan);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->network_list_offload_config_cmdid;
	वापस ath10k_wmi_cmd_send(ar, skb, cmd_id);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_update_fw_tdls_state(काष्ठा ath10k *ar, u32 vdev_id,
				क्रमागत wmi_tdls_state state)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_update_fw_tdls_state)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_update_fw_tdls_state(ar, vdev_id, state);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->tdls_set_state_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_tdls_peer_update(काष्ठा ath10k *ar,
			    स्थिर काष्ठा wmi_tdls_peer_update_cmd_arg *arg,
			    स्थिर काष्ठा wmi_tdls_peer_capab_arg *cap,
			    स्थिर काष्ठा wmi_channel_arg *chan)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_tdls_peer_update)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_tdls_peer_update(ar, arg, cap, chan);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->tdls_peer_update_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_adaptive_qcs(काष्ठा ath10k *ar, bool enable)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_adaptive_qcs)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_adaptive_qcs(ar, enable);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, ar->wmi.cmd->adaptive_qcs_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_get_tpc_config(काष्ठा ath10k *ar, u32 param)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_get_tpc_config)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_get_tpc_config(ar, param);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_get_tpc_config_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_fw_stats_fill(काष्ठा ath10k *ar, काष्ठा ath10k_fw_stats *fw_stats,
			 अक्षर *buf)
अणु
	अगर (!ar->wmi.ops->fw_stats_fill)
		वापस -EOPNOTSUPP;

	ar->wmi.ops->fw_stats_fill(ar, fw_stats, buf);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_enable_adaptive_cca(काष्ठा ath10k *ar, u8 enable,
				    u32 detect_level, u32 detect_margin)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_enable_adaptive_cca)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_enable_adaptive_cca(ar, enable,
							detect_level,
							detect_margin);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_enable_adaptive_cca_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_ext_resource_config(काष्ठा ath10k *ar,
			       क्रमागत wmi_host_platक्रमm_type type,
			       u32 fw_feature_biपंचांगap)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->ext_resource_config)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->ext_resource_config(ar, type,
					       fw_feature_biपंचांगap);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->ext_resource_cfg_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_get_vdev_subtype(काष्ठा ath10k *ar, क्रमागत wmi_vdev_subtype subtype)
अणु
	अगर (!ar->wmi.ops->get_vdev_subtype)
		वापस -EOPNOTSUPP;

	वापस ar->wmi.ops->get_vdev_subtype(ar, subtype);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_bss_chan_info_request(काष्ठा ath10k *ar,
				      क्रमागत wmi_bss_survey_req_type type)
अणु
	काष्ठा ath10k_wmi *wmi = &ar->wmi;
	काष्ठा sk_buff *skb;

	अगर (!wmi->ops->gen_pdev_bss_chan_info_req)
		वापस -EOPNOTSUPP;

	skb = wmi->ops->gen_pdev_bss_chan_info_req(ar, type);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   wmi->cmd->pdev_bss_chan_info_request_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_echo(काष्ठा ath10k *ar, u32 value)
अणु
	काष्ठा ath10k_wmi *wmi = &ar->wmi;
	काष्ठा sk_buff *skb;

	अगर (!wmi->ops->gen_echo)
		वापस -EOPNOTSUPP;

	skb = wmi->ops->gen_echo(ar, value);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb, wmi->cmd->echo_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_get_tpc_table_cmdid(काष्ठा ath10k *ar, u32 param)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_pdev_get_tpc_table_cmdid)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_get_tpc_table_cmdid(ar, param);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_get_tpc_table_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_report_radar_found(काष्ठा ath10k *ar,
			      स्थिर काष्ठा ath10k_radar_found_info *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_radar_found)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_radar_found(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->radar_found_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_pdev_bb_timing(काष्ठा ath10k *ar,
			  स्थिर काष्ठा wmi_bb_timing_cfg_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_bb_timing)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_bb_timing(ar, arg);

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->set_bb_timing_cmdid);
पूर्ण

अटल अंतरभूत पूर्णांक
ath10k_wmi_set_per_peer_per_tid_cfg(काष्ठा ath10k *ar,
				    स्थिर काष्ठा wmi_per_peer_per_tid_cfg_arg *arg)
अणु
	काष्ठा sk_buff *skb;

	अगर (!ar->wmi.ops->gen_per_peer_per_tid_cfg)
		वापस -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_per_peer_per_tid_cfg(ar, arg);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->per_peer_per_tid_config_cmdid);
पूर्ण
#पूर्ण_अगर
