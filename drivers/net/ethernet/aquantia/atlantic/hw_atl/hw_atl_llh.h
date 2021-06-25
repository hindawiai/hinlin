<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_llh.h: Declarations of bitfield and रेजिस्टर access functions क्रम
 * Atlantic रेजिस्टरs.
 */

#अगर_अघोषित HW_ATL_LLH_H
#घोषणा HW_ATL_LLH_H

#समावेश <linux/types.h>

काष्ठा aq_hw_s;

/* set temperature sense reset */
व्योम hw_atl_ts_reset_set(काष्ठा aq_hw_s *aq_hw, u32 val);

/* set temperature sense घातer करोwn */
व्योम hw_atl_ts_घातer_करोwn_set(काष्ठा aq_hw_s *aq_hw, u32 val);

/* get temperature sense घातer करोwn */
u32 hw_atl_ts_घातer_करोwn_get(काष्ठा aq_hw_s *aq_hw);

/* get temperature sense पढ़ोy */
u32 hw_atl_ts_पढ़ोy_get(काष्ठा aq_hw_s *aq_hw);

/* get temperature sense पढ़ोy latch high */
u32 hw_atl_ts_पढ़ोy_latch_high_get(काष्ठा aq_hw_s *aq_hw);

/* get temperature sense data */
u32 hw_atl_ts_data_get(काष्ठा aq_hw_s *aq_hw);

/* global */

/* set global microprocessor semaphore */
व्योम hw_atl_reg_glb_cpu_sem_set(काष्ठा aq_hw_s *aq_hw,	u32 glb_cpu_sem,
				u32 semaphore);

/* get global microprocessor semaphore */
u32 hw_atl_reg_glb_cpu_sem_get(काष्ठा aq_hw_s *aq_hw, u32 semaphore);

/* set global रेजिस्टर reset disable */
व्योम hw_atl_glb_glb_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 glb_reg_res_dis);

/* set soft reset */
व्योम hw_atl_glb_soft_res_set(काष्ठा aq_hw_s *aq_hw, u32 soft_res);

/* get soft reset */
u32 hw_atl_glb_soft_res_get(काष्ठा aq_hw_s *aq_hw);

/* stats */

u32 hw_atl_rpb_rx_dma_drop_pkt_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get rx dma good octet counter */
u64 hw_atl_stats_rx_dma_good_octet_counter_get(काष्ठा aq_hw_s *aq_hw);

/* get rx dma good packet counter */
u64 hw_atl_stats_rx_dma_good_pkt_counter_get(काष्ठा aq_hw_s *aq_hw);

/* get tx dma good octet counter */
u64 hw_atl_stats_tx_dma_good_octet_counter_get(काष्ठा aq_hw_s *aq_hw);

/* get tx dma good packet counter */
u64 hw_atl_stats_tx_dma_good_pkt_counter_get(काष्ठा aq_hw_s *aq_hw);

/* get msm rx errors counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_rx_errs_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm rx unicast frames counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_rx_ucst_frm_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm rx multicast frames counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_rx_mcst_frm_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm rx broadcast frames counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_rx_bcst_frm_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm rx broadcast octets counter रेजिस्टर 1 */
u32 hw_atl_reg_mac_msm_rx_bcst_octets_counter1get(काष्ठा aq_hw_s *aq_hw);

/* get msm rx unicast octets counter रेजिस्टर 0 */
u32 hw_atl_reg_mac_msm_rx_ucst_octets_counter0get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx errors counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_tx_errs_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx unicast frames counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_tx_ucst_frm_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx multicast frames counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_tx_mcst_frm_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx broadcast frames counter रेजिस्टर */
u32 hw_atl_reg_mac_msm_tx_bcst_frm_cnt_get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx multicast octets counter रेजिस्टर 1 */
u32 hw_atl_reg_mac_msm_tx_mcst_octets_counter1get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx broadcast octets counter रेजिस्टर 1 */
u32 hw_atl_reg_mac_msm_tx_bcst_octets_counter1get(काष्ठा aq_hw_s *aq_hw);

/* get msm tx unicast octets counter रेजिस्टर 0 */
u32 hw_atl_reg_mac_msm_tx_ucst_octets_counter0get(काष्ठा aq_hw_s *aq_hw);

/* get global mअगर identअगरication */
u32 hw_atl_reg_glb_mअगर_id_get(काष्ठा aq_hw_s *aq_hw);

/* पूर्णांकerrupt */

/* set पूर्णांकerrupt स्वतः mask lsw */
व्योम hw_atl_itr_irq_स्वतः_masklsw_set(काष्ठा aq_hw_s *aq_hw,
				     u32 irq_स्वतः_masklsw);

/* set पूर्णांकerrupt mapping enable rx */
व्योम hw_atl_itr_irq_map_en_rx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_en_rx,
				  u32 rx);

/* set पूर्णांकerrupt mapping enable tx */
व्योम hw_atl_itr_irq_map_en_tx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_en_tx,
				  u32 tx);

/* set पूर्णांकerrupt mapping rx */
व्योम hw_atl_itr_irq_map_rx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_rx, u32 rx);

/* set पूर्णांकerrupt mapping tx */
व्योम hw_atl_itr_irq_map_tx_set(काष्ठा aq_hw_s *aq_hw, u32 irq_map_tx, u32 tx);

/* set पूर्णांकerrupt mask clear lsw */
व्योम hw_atl_itr_irq_msk_clearlsw_set(काष्ठा aq_hw_s *aq_hw,
				     u32 irq_msk_clearlsw);

/* set पूर्णांकerrupt mask set lsw */
व्योम hw_atl_itr_irq_msk_setlsw_set(काष्ठा aq_hw_s *aq_hw, u32 irq_msk_setlsw);

/* set पूर्णांकerrupt रेजिस्टर reset disable */
व्योम hw_atl_itr_irq_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 irq_reg_res_dis);

/* set पूर्णांकerrupt status clear lsw */
व्योम hw_atl_itr_irq_status_clearlsw_set(काष्ठा aq_hw_s *aq_hw,
					u32 irq_status_clearlsw);

/* get पूर्णांकerrupt status lsw */
u32 hw_atl_itr_irq_statuslsw_get(काष्ठा aq_hw_s *aq_hw);

/* get reset पूर्णांकerrupt */
u32 hw_atl_itr_res_irq_get(काष्ठा aq_hw_s *aq_hw);

/* set reset पूर्णांकerrupt */
व्योम hw_atl_itr_res_irq_set(काष्ठा aq_hw_s *aq_hw, u32 res_irq);

/* set RSC पूर्णांकerrupt */
व्योम hw_atl_itr_rsc_en_set(काष्ठा aq_hw_s *aq_hw, u32 enable);

/* set RSC delay */
व्योम hw_atl_itr_rsc_delay_set(काष्ठा aq_hw_s *aq_hw, u32 delay);

/* rdm */

/* set cpu id */
व्योम hw_atl_rdm_cpu_id_set(काष्ठा aq_hw_s *aq_hw, u32 cpuid, u32 dca);

/* set rx dca enable */
व्योम hw_atl_rdm_rx_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_dca_en);

/* set rx dca mode */
व्योम hw_atl_rdm_rx_dca_mode_set(काष्ठा aq_hw_s *aq_hw, u32 rx_dca_mode);

/* set rx descriptor data buffer size */
व्योम hw_atl_rdm_rx_desc_data_buff_size_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_data_buff_size,
				    u32 descriptor);

/* set rx descriptor dca enable */
व्योम hw_atl_rdm_rx_desc_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_dca_en,
				   u32 dca);

/* set rx descriptor enable */
व्योम hw_atl_rdm_rx_desc_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_en,
			       u32 descriptor);

/* set rx descriptor header splitting */
व्योम hw_atl_rdm_rx_desc_head_splitting_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_head_splitting,
				    u32 descriptor);

/* get rx descriptor head poपूर्णांकer */
u32 hw_atl_rdm_rx_desc_head_ptr_get(काष्ठा aq_hw_s *aq_hw, u32 descriptor);

/* set rx descriptor length */
व्योम hw_atl_rdm_rx_desc_len_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_len,
				u32 descriptor);

/* set rx descriptor ग_लिखो-back पूर्णांकerrupt enable */
व्योम hw_atl_rdm_rx_desc_wr_wb_irq_en_set(काष्ठा aq_hw_s *aq_hw,
					 u32 rx_desc_wr_wb_irq_en);

/* set rx header dca enable */
व्योम hw_atl_rdm_rx_head_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_head_dca_en,
				   u32 dca);

/* set rx payload dca enable */
व्योम hw_atl_rdm_rx_pld_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_pld_dca_en,
				  u32 dca);

/* set rx descriptor header buffer size */
व्योम hw_atl_rdm_rx_desc_head_buff_size_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_head_buff_size,
					   u32 descriptor);

/* set rx descriptor reset */
व्योम hw_atl_rdm_rx_desc_res_set(काष्ठा aq_hw_s *aq_hw, u32 rx_desc_res,
				u32 descriptor);

/* Set RDM Interrupt Moderation Enable */
व्योम hw_atl_rdm_rdm_पूर्णांकr_moder_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 rdm_पूर्णांकr_moder_en);

/* reg */

/* set general पूर्णांकerrupt mapping रेजिस्टर */
व्योम hw_atl_reg_gen_irq_map_set(काष्ठा aq_hw_s *aq_hw, u32 gen_पूर्णांकr_map,
				u32 regidx);

/* get general पूर्णांकerrupt status रेजिस्टर */
u32 hw_atl_reg_gen_irq_status_get(काष्ठा aq_hw_s *aq_hw);

/* set पूर्णांकerrupt global control रेजिस्टर */
व्योम hw_atl_reg_irq_glb_ctl_set(काष्ठा aq_hw_s *aq_hw, u32 पूर्णांकr_glb_ctl);

/* set पूर्णांकerrupt throttle रेजिस्टर */
व्योम hw_atl_reg_irq_thr_set(काष्ठा aq_hw_s *aq_hw, u32 पूर्णांकr_thr, u32 throttle);

/* set rx dma descriptor base address lsw */
व्योम hw_atl_reg_rx_dma_desc_base_addresslswset(काष्ठा aq_hw_s *aq_hw,
					       u32 rx_dma_desc_base_addrlsw,
					u32 descriptor);

/* set rx dma descriptor base address msw */
व्योम hw_atl_reg_rx_dma_desc_base_addressmswset(काष्ठा aq_hw_s *aq_hw,
					       u32 rx_dma_desc_base_addrmsw,
					u32 descriptor);

/* get rx dma descriptor status रेजिस्टर */
u32 hw_atl_reg_rx_dma_desc_status_get(काष्ठा aq_hw_s *aq_hw, u32 descriptor);

/* set rx dma descriptor tail poपूर्णांकer रेजिस्टर */
व्योम hw_atl_reg_rx_dma_desc_tail_ptr_set(काष्ठा aq_hw_s *aq_hw,
					 u32 rx_dma_desc_tail_ptr,
				  u32 descriptor);

/* set rx filter multicast filter mask रेजिस्टर */
व्योम hw_atl_reg_rx_flr_mcst_flr_msk_set(काष्ठा aq_hw_s *aq_hw,
					u32 rx_flr_mcst_flr_msk);

/* set rx filter multicast filter रेजिस्टर */
व्योम hw_atl_reg_rx_flr_mcst_flr_set(काष्ठा aq_hw_s *aq_hw, u32 rx_flr_mcst_flr,
				    u32 filter);

/* set rx filter rss control रेजिस्टर 1 */
व्योम hw_atl_reg_rx_flr_rss_control1set(काष्ठा aq_hw_s *aq_hw,
				       u32 rx_flr_rss_control1);

/* Set RX Filter Control Register 2 */
व्योम hw_atl_reg_rx_flr_control2_set(काष्ठा aq_hw_s *aq_hw, u32 rx_flr_control2);

/* Set RX Interrupt Moderation Control Register */
व्योम hw_atl_reg_rx_पूर्णांकr_moder_ctrl_set(काष्ठा aq_hw_s *aq_hw,
				       u32 rx_पूर्णांकr_moderation_ctl,
				u32 queue);

/* set tx dma debug control */
व्योम hw_atl_reg_tx_dma_debug_ctl_set(काष्ठा aq_hw_s *aq_hw,
				     u32 tx_dma_debug_ctl);

/* set tx dma descriptor base address lsw */
व्योम hw_atl_reg_tx_dma_desc_base_addresslswset(काष्ठा aq_hw_s *aq_hw,
					       u32 tx_dma_desc_base_addrlsw,
					u32 descriptor);

/* set tx dma descriptor base address msw */
व्योम hw_atl_reg_tx_dma_desc_base_addressmswset(काष्ठा aq_hw_s *aq_hw,
					       u32 tx_dma_desc_base_addrmsw,
					u32 descriptor);

/* set tx dma descriptor tail poपूर्णांकer रेजिस्टर */
व्योम hw_atl_reg_tx_dma_desc_tail_ptr_set(काष्ठा aq_hw_s *aq_hw,
					 u32 tx_dma_desc_tail_ptr,
					 u32 descriptor);

/* Set TX Interrupt Moderation Control Register */
व्योम hw_atl_reg_tx_पूर्णांकr_moder_ctrl_set(काष्ठा aq_hw_s *aq_hw,
				       u32 tx_पूर्णांकr_moderation_ctl,
				       u32 queue);

/* set global microprocessor scratch pad */
व्योम hw_atl_reg_glb_cpu_scratch_scp_set(काष्ठा aq_hw_s *aq_hw,
					u32 glb_cpu_scratch_scp,
					u32 scratch_scp);

/* rpb */

/* set dma प्रणाली loopback */
व्योम hw_atl_rpb_dma_sys_lbk_set(काष्ठा aq_hw_s *aq_hw, u32 dma_sys_lbk);

/* set dma network loopback */
व्योम hw_atl_rpb_dma_net_lbk_set(काष्ठा aq_hw_s *aq_hw, u32 dma_net_lbk);

/* set rx traffic class mode */
व्योम hw_atl_rpb_rpf_rx_traf_class_mode_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_traf_class_mode);

/* get rx traffic class mode */
u32 hw_atl_rpb_rpf_rx_traf_class_mode_get(काष्ठा aq_hw_s *aq_hw);

/* set rx buffer enable */
व्योम hw_atl_rpb_rx_buff_en_set(काष्ठा aq_hw_s *aq_hw, u32 rx_buff_en);

/* set rx buffer high threshold (per tc) */
व्योम hw_atl_rpb_rx_buff_hi_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 rx_buff_hi_threshold_per_tc,
						u32 buffer);

/* set rx buffer low threshold (per tc) */
व्योम hw_atl_rpb_rx_buff_lo_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 rx_buff_lo_threshold_per_tc,
					 u32 buffer);

/* set rx flow control mode */
व्योम hw_atl_rpb_rx_flow_ctl_mode_set(काष्ठा aq_hw_s *aq_hw,
				     u32 rx_flow_ctl_mode);

/* set rx packet buffer size (per tc) */
व्योम hw_atl_rpb_rx_pkt_buff_size_per_tc_set(काष्ठा aq_hw_s *aq_hw,
					    u32 rx_pkt_buff_size_per_tc,
					    u32 buffer);

/* toggle rdm rx dma descriptor cache init */
व्योम hw_atl_rdm_rx_dma_desc_cache_init_tgl(काष्ठा aq_hw_s *aq_hw);

/* get rdm rx dma descriptor cache init करोne */
u32 hw_atl_rdm_rx_dma_desc_cache_init_करोne_get(काष्ठा aq_hw_s *aq_hw);

/* set rx xoff enable (per tc) */
व्योम hw_atl_rpb_rx_xoff_en_per_tc_set(काष्ठा aq_hw_s *aq_hw,
				      u32 rx_xoff_en_per_tc,
				      u32 buffer);

/* rpf */

/* set l2 broadcast count threshold */
व्योम hw_atl_rpfl2broadcast_count_threshold_set(काष्ठा aq_hw_s *aq_hw,
					       u32 l2broadcast_count_threshold);

/* set l2 broadcast enable */
व्योम hw_atl_rpfl2broadcast_en_set(काष्ठा aq_hw_s *aq_hw, u32 l2broadcast_en);

/* set l2 broadcast filter action */
व्योम hw_atl_rpfl2broadcast_flr_act_set(काष्ठा aq_hw_s *aq_hw,
				       u32 l2broadcast_flr_act);

/* set l2 multicast filter enable */
व्योम hw_atl_rpfl2multicast_flr_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 l2multicast_flr_en,
				      u32 filter);

/* get l2 promiscuous mode enable */
u32 hw_atl_rpfl2promiscuous_mode_en_get(काष्ठा aq_hw_s *aq_hw);

/* set l2 promiscuous mode enable */
व्योम hw_atl_rpfl2promiscuous_mode_en_set(काष्ठा aq_hw_s *aq_hw,
					 u32 l2promiscuous_mode_en);

/* set l2 unicast filter action */
व्योम hw_atl_rpfl2unicast_flr_act_set(काष्ठा aq_hw_s *aq_hw,
				     u32 l2unicast_flr_act,
				     u32 filter);

/* set l2 unicast filter enable */
व्योम hw_atl_rpfl2_uc_flr_en_set(काष्ठा aq_hw_s *aq_hw, u32 l2unicast_flr_en,
				u32 filter);

/* set l2 unicast destination address lsw */
व्योम hw_atl_rpfl2unicast_dest_addresslsw_set(काष्ठा aq_hw_s *aq_hw,
					     u32 l2unicast_dest_addresslsw,
				      u32 filter);

/* set l2 unicast destination address msw */
व्योम hw_atl_rpfl2unicast_dest_addressmsw_set(काष्ठा aq_hw_s *aq_hw,
					     u32 l2unicast_dest_addressmsw,
				      u32 filter);

/* Set L2 Accept all Multicast packets */
व्योम hw_atl_rpfl2_accept_all_mc_packets_set(काष्ठा aq_hw_s *aq_hw,
					    u32 l2_accept_all_mc_packets);

/* set user-priority tc mapping */
व्योम hw_atl_rpf_rpb_user_priority_tc_map_set(काष्ठा aq_hw_s *aq_hw,
					     u32 user_priority_tc_map, u32 tc);

/* set rss key address */
व्योम hw_atl_rpf_rss_key_addr_set(काष्ठा aq_hw_s *aq_hw, u32 rss_key_addr);

/* set rss key ग_लिखो data */
व्योम hw_atl_rpf_rss_key_wr_data_set(काष्ठा aq_hw_s *aq_hw, u32 rss_key_wr_data);

/* get rss key ग_लिखो enable */
u32 hw_atl_rpf_rss_key_wr_en_get(काष्ठा aq_hw_s *aq_hw);

/* set rss key ग_लिखो enable */
व्योम hw_atl_rpf_rss_key_wr_en_set(काष्ठा aq_hw_s *aq_hw, u32 rss_key_wr_en);

/* set rss redirection table address */
व्योम hw_atl_rpf_rss_redir_tbl_addr_set(काष्ठा aq_hw_s *aq_hw,
				       u32 rss_redir_tbl_addr);

/* set rss redirection table ग_लिखो data */
व्योम hw_atl_rpf_rss_redir_tbl_wr_data_set(काष्ठा aq_hw_s *aq_hw,
					  u32 rss_redir_tbl_wr_data);

/* get rss redirection ग_लिखो enable */
u32 hw_atl_rpf_rss_redir_wr_en_get(काष्ठा aq_hw_s *aq_hw);

/* set rss redirection ग_लिखो enable */
व्योम hw_atl_rpf_rss_redir_wr_en_set(काष्ठा aq_hw_s *aq_hw, u32 rss_redir_wr_en);

/* set tpo to rpf प्रणाली loopback */
व्योम hw_atl_rpf_tpo_to_rpf_sys_lbk_set(काष्ठा aq_hw_s *aq_hw,
				       u32 tpo_to_rpf_sys_lbk);

/* set vlan inner ethertype */
व्योम hw_atl_rpf_vlan_inner_etht_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_inner_etht);

/* set vlan outer ethertype */
व्योम hw_atl_rpf_vlan_outer_etht_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_outer_etht);

/* set vlan promiscuous mode enable */
व्योम hw_atl_rpf_vlan_prom_mode_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 vlan_prom_mode_en);

/* Get VLAN promiscuous mode enable */
u32 hw_atl_rpf_vlan_prom_mode_en_get(काष्ठा aq_hw_s *aq_hw);

/* Set VLAN untagged action */
व्योम hw_atl_rpf_vlan_untagged_act_set(काष्ठा aq_hw_s *aq_hw,
				      u32 vlan_untagged_act);

/* Set VLAN accept untagged packets */
व्योम hw_atl_rpf_vlan_accept_untagged_packets_set(काष्ठा aq_hw_s *aq_hw,
						 u32 vlan_acc_untagged_packets);

/* Set VLAN filter enable */
व्योम hw_atl_rpf_vlan_flr_en_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_flr_en,
				u32 filter);

/* Set VLAN Filter Action */
व्योम hw_atl_rpf_vlan_flr_act_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_filter_act,
				 u32 filter);

/* Set VLAN ID Filter */
व्योम hw_atl_rpf_vlan_id_flr_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_id_flr,
				u32 filter);

/* Set VLAN RX queue assignment enable */
व्योम hw_atl_rpf_vlan_rxq_en_flr_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_rxq_en,
				    u32 filter);

/* Set VLAN RX queue */
व्योम hw_atl_rpf_vlan_rxq_flr_set(काष्ठा aq_hw_s *aq_hw, u32 vlan_rxq,
				 u32 filter);

/* set ethertype filter enable */
व्योम hw_atl_rpf_etht_flr_en_set(काष्ठा aq_hw_s *aq_hw, u32 etht_flr_en,
				u32 filter);

/* set  ethertype user-priority enable */
व्योम hw_atl_rpf_etht_user_priority_en_set(काष्ठा aq_hw_s *aq_hw,
					  u32 etht_user_priority_en,
					  u32 filter);

/* set  ethertype rx queue enable */
व्योम hw_atl_rpf_etht_rx_queue_en_set(काष्ठा aq_hw_s *aq_hw,
				     u32 etht_rx_queue_en,
				     u32 filter);

/* set ethertype rx queue */
व्योम hw_atl_rpf_etht_rx_queue_set(काष्ठा aq_hw_s *aq_hw, u32 etht_rx_queue,
				  u32 filter);

/* set ethertype user-priority */
व्योम hw_atl_rpf_etht_user_priority_set(काष्ठा aq_hw_s *aq_hw,
				       u32 etht_user_priority,
				       u32 filter);

/* set ethertype management queue */
व्योम hw_atl_rpf_etht_mgt_queue_set(काष्ठा aq_hw_s *aq_hw, u32 etht_mgt_queue,
				   u32 filter);

/* set ethertype filter action */
व्योम hw_atl_rpf_etht_flr_act_set(काष्ठा aq_hw_s *aq_hw, u32 etht_flr_act,
				 u32 filter);

/* set ethertype filter */
व्योम hw_atl_rpf_etht_flr_set(काष्ठा aq_hw_s *aq_hw, u32 etht_flr, u32 filter);

/* set L4 source port */
व्योम hw_atl_rpf_l4_spd_set(काष्ठा aq_hw_s *aq_hw, u32 val, u32 filter);

/* set L4 destination port */
व्योम hw_atl_rpf_l4_dpd_set(काष्ठा aq_hw_s *aq_hw, u32 val, u32 filter);

/* rpo */

/* set ipv4 header checksum offload enable */
व्योम hw_atl_rpo_ipv4header_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					      u32 ipv4header_crc_offload_en);

/* set rx descriptor vlan stripping */
व्योम hw_atl_rpo_rx_desc_vlan_stripping_set(काष्ठा aq_hw_s *aq_hw,
					   u32 rx_desc_vlan_stripping,
					   u32 descriptor);

व्योम hw_atl_rpo_outer_vlan_tag_mode_set(व्योम *context,
					u32 outervlantagmode);

u32 hw_atl_rpo_outer_vlan_tag_mode_get(व्योम *context);

/* set tcp/udp checksum offload enable */
व्योम hw_atl_rpo_tcp_udp_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					   u32 tcp_udp_crc_offload_en);

/* Set LRO Patch Optimization Enable. */
व्योम hw_atl_rpo_lro_patch_optimization_en_set(काष्ठा aq_hw_s *aq_hw,
					      u32 lro_patch_optimization_en);

/* Set Large Receive Offload Enable */
व्योम hw_atl_rpo_lro_en_set(काष्ठा aq_hw_s *aq_hw, u32 lro_en);

/* Set LRO Q Sessions Limit */
व्योम hw_atl_rpo_lro_qsessions_lim_set(काष्ठा aq_hw_s *aq_hw,
				      u32 lro_qsessions_lim);

/* Set LRO Total Descriptor Limit */
व्योम hw_atl_rpo_lro_total_desc_lim_set(काष्ठा aq_hw_s *aq_hw,
				       u32 lro_total_desc_lim);

/* Set LRO Min Payload of First Packet */
व्योम hw_atl_rpo_lro_min_pay_of_first_pkt_set(काष्ठा aq_hw_s *aq_hw,
					     u32 lro_min_pld_of_first_pkt);

/* Set LRO Packet Limit */
व्योम hw_atl_rpo_lro_pkt_lim_set(काष्ठा aq_hw_s *aq_hw, u32 lro_packet_lim);

/* Set LRO Max Number of Descriptors */
व्योम hw_atl_rpo_lro_max_num_of_descriptors_set(काष्ठा aq_hw_s *aq_hw,
					       u32 lro_max_desc_num, u32 lro);

/* Set LRO Time Base Divider */
व्योम hw_atl_rpo_lro_समय_base_भागider_set(काष्ठा aq_hw_s *aq_hw,
					  u32 lro_समय_base_भागider);

/*Set LRO Inactive Interval */
व्योम hw_atl_rpo_lro_inactive_पूर्णांकerval_set(काष्ठा aq_hw_s *aq_hw,
					  u32 lro_inactive_पूर्णांकerval);

/*Set LRO Max Coalescing Interval */
व्योम hw_atl_rpo_lro_max_coalescing_पूर्णांकerval_set(काष्ठा aq_hw_s *aq_hw,
						u32 lro_max_coal_पूर्णांकerval);

/* rx */

/* set rx रेजिस्टर reset disable */
व्योम hw_atl_rx_rx_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 rx_reg_res_dis);

/* tdm */

/* set cpu id */
व्योम hw_atl_tdm_cpu_id_set(काष्ठा aq_hw_s *aq_hw, u32 cpuid, u32 dca);

/* set large send offload enable */
व्योम hw_atl_tdm_large_send_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					  u32 large_send_offload_en);

/* set tx descriptor enable */
व्योम hw_atl_tdm_tx_desc_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_desc_en,
			       u32 descriptor);

/* set tx dca enable */
व्योम hw_atl_tdm_tx_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_dca_en);

/* set tx dca mode */
व्योम hw_atl_tdm_tx_dca_mode_set(काष्ठा aq_hw_s *aq_hw, u32 tx_dca_mode);

/* set tx descriptor dca enable */
व्योम hw_atl_tdm_tx_desc_dca_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_desc_dca_en,
				   u32 dca);

/* get tx descriptor head poपूर्णांकer */
u32 hw_atl_tdm_tx_desc_head_ptr_get(काष्ठा aq_hw_s *aq_hw, u32 descriptor);

/* set tx descriptor length */
व्योम hw_atl_tdm_tx_desc_len_set(काष्ठा aq_hw_s *aq_hw, u32 tx_desc_len,
				u32 descriptor);

/* set tx descriptor ग_लिखो-back पूर्णांकerrupt enable */
व्योम hw_atl_tdm_tx_desc_wr_wb_irq_en_set(काष्ठा aq_hw_s *aq_hw,
					 u32 tx_desc_wr_wb_irq_en);

/* set tx descriptor ग_लिखो-back threshold */
व्योम hw_atl_tdm_tx_desc_wr_wb_threshold_set(काष्ठा aq_hw_s *aq_hw,
					    u32 tx_desc_wr_wb_threshold,
				     u32 descriptor);

/* Set TDM Interrupt Moderation Enable */
व्योम hw_atl_tdm_tdm_पूर्णांकr_moder_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tdm_irq_moderation_en);
/* thm */

/* set lso tcp flag of first packet */
व्योम hw_atl_thm_lso_tcp_flag_of_first_pkt_set(काष्ठा aq_hw_s *aq_hw,
					      u32 lso_tcp_flag_of_first_pkt);

/* set lso tcp flag of last packet */
व्योम hw_atl_thm_lso_tcp_flag_of_last_pkt_set(काष्ठा aq_hw_s *aq_hw,
					     u32 lso_tcp_flag_of_last_pkt);

/* set lso tcp flag of middle packet */
व्योम hw_atl_thm_lso_tcp_flag_of_middle_pkt_set(काष्ठा aq_hw_s *aq_hw,
					       u32 lso_tcp_flag_of_middle_pkt);

/* tpb */

/* set TX Traffic Class Mode */
व्योम hw_atl_tpb_tps_tx_tc_mode_set(काष्ठा aq_hw_s *aq_hw,
				   u32 tx_traf_class_mode);

/* get TX Traffic Class Mode */
u32 hw_atl_tpb_tps_tx_tc_mode_get(काष्ठा aq_hw_s *aq_hw);

/* set tx buffer enable */
व्योम hw_atl_tpb_tx_buff_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_buff_en);

/* set tx buffer high threshold (per tc) */
व्योम hw_atl_tpb_tx_buff_hi_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 tx_buff_hi_threshold_per_tc,
					 u32 buffer);

/* set tx buffer low threshold (per tc) */
व्योम hw_atl_tpb_tx_buff_lo_threshold_per_tc_set(काष्ठा aq_hw_s *aq_hw,
						u32 tx_buff_lo_threshold_per_tc,
					 u32 buffer);

/* set tx dma प्रणाली loopback enable */
व्योम hw_atl_tpb_tx_dma_sys_lbk_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_dma_sys_lbk_en);

/* set tx dma network loopback enable */
व्योम hw_atl_tpb_tx_dma_net_lbk_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tx_dma_net_lbk_en);

/* set tx घड़ी gating enable */
व्योम hw_atl_tpb_tx_tx_clk_gate_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tx_clk_gate_en);

/* set tx packet buffer size (per tc) */
व्योम hw_atl_tpb_tx_pkt_buff_size_per_tc_set(काष्ठा aq_hw_s *aq_hw,
					    u32 tx_pkt_buff_size_per_tc,
					    u32 buffer);

/* set tx path pad insert enable */
व्योम hw_atl_tpb_tx_path_scp_ins_en_set(काष्ठा aq_hw_s *aq_hw, u32 tx_path_scp_ins_en);

/* tpo */

/* set ipv4 header checksum offload enable */
व्योम hw_atl_tpo_ipv4header_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					      u32 ipv4header_crc_offload_en);

/* set tcp/udp checksum offload enable */
व्योम hw_atl_tpo_tcp_udp_crc_offload_en_set(काष्ठा aq_hw_s *aq_hw,
					   u32 tcp_udp_crc_offload_en);

/* set tx pkt प्रणाली loopback enable */
व्योम hw_atl_tpo_tx_pkt_sys_lbk_en_set(काष्ठा aq_hw_s *aq_hw,
				      u32 tx_pkt_sys_lbk_en);

/* tps */

/* set tx packet scheduler data arbitration mode */
व्योम hw_atl_tps_tx_pkt_shed_data_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
					      u32 tx_pkt_shed_data_arb_mode);

/* set tx packet scheduler descriptor rate current समय reset */
व्योम hw_atl_tps_tx_pkt_shed_desc_rate_curr_समय_res_set(काष्ठा aq_hw_s *aq_hw,
							u32 curr_समय_res);

/* set tx packet scheduler descriptor rate limit */
व्योम hw_atl_tps_tx_pkt_shed_desc_rate_lim_set(काष्ठा aq_hw_s *aq_hw,
					      u32 tx_pkt_shed_desc_rate_lim);

/* set tx packet scheduler descriptor tc arbitration mode */
व्योम hw_atl_tps_tx_pkt_shed_desc_tc_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
						 u32 arb_mode);

/* set tx packet scheduler descriptor tc max credit */
व्योम hw_atl_tps_tx_pkt_shed_desc_tc_max_credit_set(काष्ठा aq_hw_s *aq_hw,
						   स्थिर u32 tc,
						   स्थिर u32 max_credit);

/* set tx packet scheduler descriptor tc weight */
व्योम hw_atl_tps_tx_pkt_shed_desc_tc_weight_set(काष्ठा aq_hw_s *aq_hw,
					       स्थिर u32 tc,
					       स्थिर u32 weight);

/* set tx packet scheduler descriptor vm arbitration mode */
व्योम hw_atl_tps_tx_pkt_shed_desc_vm_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
						 u32 arb_mode);

/* set tx packet scheduler tc data max credit */
व्योम hw_atl_tps_tx_pkt_shed_tc_data_max_credit_set(काष्ठा aq_hw_s *aq_hw,
						   स्थिर u32 tc,
						   स्थिर u32 max_credit);

/* set tx packet scheduler tc data weight */
व्योम hw_atl_tps_tx_pkt_shed_tc_data_weight_set(काष्ठा aq_hw_s *aq_hw,
					       स्थिर u32 tc,
					       स्थिर u32 weight);

/* set tx descriptor rate mode */
व्योम hw_atl_tps_tx_desc_rate_mode_set(काष्ठा aq_hw_s *aq_hw,
				      स्थिर u32 rate_mode);

/* set tx packet scheduler descriptor rate enable */
व्योम hw_atl_tps_tx_desc_rate_en_set(काष्ठा aq_hw_s *aq_hw, स्थिर u32 desc,
				    स्थिर u32 enable);

/* set tx packet scheduler descriptor rate पूर्णांकegral value */
व्योम hw_atl_tps_tx_desc_rate_x_set(काष्ठा aq_hw_s *aq_hw, स्थिर u32 desc,
				   स्थिर u32 rate_पूर्णांक);

/* set tx packet scheduler descriptor rate fractional value */
व्योम hw_atl_tps_tx_desc_rate_y_set(काष्ठा aq_hw_s *aq_hw, स्थिर u32 desc,
				   स्थिर u32 rate_frac);

/* tx */

/* set tx रेजिस्टर reset disable */
व्योम hw_atl_tx_tx_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 tx_reg_res_dis);

/* msm */

/* get रेजिस्टर access status */
u32 hw_atl_msm_reg_access_status_get(काष्ठा aq_hw_s *aq_hw);

/* set  रेजिस्टर address क्रम indirect address */
व्योम hw_atl_msm_reg_addr_क्रम_indirect_addr_set(काष्ठा aq_hw_s *aq_hw,
					       u32 reg_addr_क्रम_indirect_addr);

/* set रेजिस्टर पढ़ो strobe */
व्योम hw_atl_msm_reg_rd_strobe_set(काष्ठा aq_hw_s *aq_hw, u32 reg_rd_strobe);

/* get  रेजिस्टर पढ़ो data */
u32 hw_atl_msm_reg_rd_data_get(काष्ठा aq_hw_s *aq_hw);

/* set  रेजिस्टर ग_लिखो data */
व्योम hw_atl_msm_reg_wr_data_set(काष्ठा aq_hw_s *aq_hw, u32 reg_wr_data);

/* set रेजिस्टर ग_लिखो strobe */
व्योम hw_atl_msm_reg_wr_strobe_set(काष्ठा aq_hw_s *aq_hw, u32 reg_wr_strobe);

/* pci */

/* set pci रेजिस्टर reset disable */
व्योम hw_atl_pci_pci_reg_res_dis_set(काष्ठा aq_hw_s *aq_hw, u32 pci_reg_res_dis);

/* pcs */
व्योम hw_atl_pcs_ptp_घड़ी_पढ़ो_enable(काष्ठा aq_hw_s *aq_hw,
				      u32 ptp_घड़ी_पढ़ो_enable);

u32 hw_atl_pcs_ptp_घड़ी_get(काष्ठा aq_hw_s *aq_hw, u32 index);

/* set uP Force Interrupt */
व्योम hw_atl_mcp_up_क्रमce_पूर्णांकr_set(काष्ठा aq_hw_s *aq_hw, u32 up_क्रमce_पूर्णांकr);

/* clear ipv4 filter destination address */
व्योम hw_atl_rpfl3l4_ipv4_dest_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location);

/* clear ipv4 filter source address */
व्योम hw_atl_rpfl3l4_ipv4_src_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location);

/* clear command क्रम filter l3-l4 */
व्योम hw_atl_rpfl3l4_cmd_clear(काष्ठा aq_hw_s *aq_hw, u8 location);

/* clear ipv6 filter destination address */
व्योम hw_atl_rpfl3l4_ipv6_dest_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location);

/* clear ipv6 filter source address */
व्योम hw_atl_rpfl3l4_ipv6_src_addr_clear(काष्ठा aq_hw_s *aq_hw, u8 location);

/* set ipv4 filter destination address */
व्योम hw_atl_rpfl3l4_ipv4_dest_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				       u32 ipv4_dest);

/* set ipv4 filter source address */
व्योम hw_atl_rpfl3l4_ipv4_src_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				      u32 ipv4_src);

/* set command क्रम filter l3-l4 */
व्योम hw_atl_rpfl3l4_cmd_set(काष्ठा aq_hw_s *aq_hw, u8 location, u32 cmd);

/* set ipv6 filter source address */
व्योम hw_atl_rpfl3l4_ipv6_src_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				      u32 *ipv6_src);

/* set ipv6 filter destination address */
व्योम hw_atl_rpfl3l4_ipv6_dest_addr_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				       u32 *ipv6_dest);

/* set Global MDIO Interface 1 */
व्योम hw_atl_glb_mdio_अगरace1_set(काष्ठा aq_hw_s *hw, u32 value);

/* get Global MDIO Interface 1 */
u32 hw_atl_glb_mdio_अगरace1_get(काष्ठा aq_hw_s *hw);

/* set Global MDIO Interface 2 */
व्योम hw_atl_glb_mdio_अगरace2_set(काष्ठा aq_hw_s *hw, u32 value);

/* get Global MDIO Interface 2 */
u32 hw_atl_glb_mdio_अगरace2_get(काष्ठा aq_hw_s *hw);

/* set Global MDIO Interface 3 */
व्योम hw_atl_glb_mdio_अगरace3_set(काष्ठा aq_hw_s *hw, u32 value);

/* get Global MDIO Interface 3 */
u32 hw_atl_glb_mdio_अगरace3_get(काष्ठा aq_hw_s *hw);

/* set Global MDIO Interface 4 */
व्योम hw_atl_glb_mdio_अगरace4_set(काष्ठा aq_hw_s *hw, u32 value);

/* get Global MDIO Interface 4 */
u32 hw_atl_glb_mdio_अगरace4_get(काष्ठा aq_hw_s *hw);

/* set Global MDIO Interface 5 */
व्योम hw_atl_glb_mdio_अगरace5_set(काष्ठा aq_hw_s *hw, u32 value);

/* get Global MDIO Interface 5 */
u32 hw_atl_glb_mdio_अगरace5_get(काष्ठा aq_hw_s *hw);

u32 hw_atl_mdio_busy_get(काष्ठा aq_hw_s *aq_hw);

/* get global microprocessor ram semaphore */
u32 hw_atl_sem_ram_get(काष्ठा aq_hw_s *self);

/* get global microprocessor mdio semaphore */
u32 hw_atl_sem_mdio_get(काष्ठा aq_hw_s *self);

u32 hw_atl_sem_reset1_get(काष्ठा aq_hw_s *self);
u32 hw_atl_sem_reset2_get(काष्ठा aq_hw_s *self);

/* get global microprocessor scratch pad रेजिस्टर */
u32 hw_atl_scrpad_get(काष्ठा aq_hw_s *aq_hw, u32 scratch_scp);

/* get global microprocessor scratch pad 12 रेजिस्टर */
u32 hw_atl_scrpad12_get(काष्ठा aq_hw_s *self);

/* get global microprocessor scratch pad 25 रेजिस्टर */
u32 hw_atl_scrpad25_get(काष्ठा aq_hw_s *self);

#पूर्ण_अगर /* HW_ATL_LLH_H */
