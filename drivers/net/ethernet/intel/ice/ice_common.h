<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_COMMON_H_
#घोषणा _ICE_COMMON_H_

#समावेश "ice.h"
#समावेश "ice_type.h"
#समावेश "ice_nvm.h"
#समावेश "ice_flex_pipe.h"
#समावेश "ice_switch.h"
#समावेश <linux/avf/virtchnl.h>

#घोषणा ICE_SQ_SEND_DELAY_TIME_MS	10
#घोषणा ICE_SQ_SEND_MAX_EXECUTE		3

क्रमागत ice_status ice_init_hw(काष्ठा ice_hw *hw);
व्योम ice_deinit_hw(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_check_reset(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_reset(काष्ठा ice_hw *hw, क्रमागत ice_reset_req req);
क्रमागत ice_status ice_create_all_ctrlq(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_init_all_ctrlq(काष्ठा ice_hw *hw);
व्योम ice_shutकरोwn_all_ctrlq(काष्ठा ice_hw *hw);
व्योम ice_destroy_all_ctrlq(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_clean_rq_elem(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq,
		  काष्ठा ice_rq_event_info *e, u16 *pending);
क्रमागत ice_status
ice_get_link_status(काष्ठा ice_port_info *pi, bool *link_up);
क्रमागत ice_status ice_update_link_info(काष्ठा ice_port_info *pi);
क्रमागत ice_status
ice_acquire_res(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_ids res,
		क्रमागत ice_aq_res_access_type access, u32 समयout);
व्योम ice_release_res(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_ids res);
क्रमागत ice_status
ice_alloc_hw_res(काष्ठा ice_hw *hw, u16 type, u16 num, bool bपंचांग, u16 *res);
क्रमागत ice_status
ice_मुक्त_hw_res(काष्ठा ice_hw *hw, u16 type, u16 num, u16 *res);
क्रमागत ice_status
ice_aq_alloc_मुक्त_res(काष्ठा ice_hw *hw, u16 num_entries,
		      काष्ठा ice_aqc_alloc_मुक्त_res_elem *buf, u16 buf_size,
		      क्रमागत ice_adminq_opc opc, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_sq_send_cmd(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq,
		काष्ठा ice_aq_desc *desc, व्योम *buf, u16 buf_size,
		काष्ठा ice_sq_cd *cd);
व्योम ice_clear_pxe_mode(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_get_caps(काष्ठा ice_hw *hw);

व्योम ice_set_safe_mode_caps(काष्ठा ice_hw *hw);

क्रमागत ice_status
ice_ग_लिखो_rxq_ctx(काष्ठा ice_hw *hw, काष्ठा ice_rlan_ctx *rlan_ctx,
		  u32 rxq_index);

क्रमागत ice_status
ice_aq_get_rss_lut(काष्ठा ice_hw *hw, काष्ठा ice_aq_get_set_rss_lut_params *get_params);
क्रमागत ice_status
ice_aq_set_rss_lut(काष्ठा ice_hw *hw, काष्ठा ice_aq_get_set_rss_lut_params *set_params);
क्रमागत ice_status
ice_aq_get_rss_key(काष्ठा ice_hw *hw, u16 vsi_handle,
		   काष्ठा ice_aqc_get_set_rss_keys *keys);
क्रमागत ice_status
ice_aq_set_rss_key(काष्ठा ice_hw *hw, u16 vsi_handle,
		   काष्ठा ice_aqc_get_set_rss_keys *keys);

bool ice_check_sq_alive(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq);
क्रमागत ice_status ice_aq_q_shutकरोwn(काष्ठा ice_hw *hw, bool unloading);
व्योम ice_fill_dflt_direct_cmd_desc(काष्ठा ice_aq_desc *desc, u16 opcode);
बाह्य स्थिर काष्ठा ice_ctx_ele ice_tlan_ctx_info[];
क्रमागत ice_status
ice_set_ctx(काष्ठा ice_hw *hw, u8 *src_ctx, u8 *dest_ctx,
	    स्थिर काष्ठा ice_ctx_ele *ce_info);

बाह्य काष्ठा mutex ice_global_cfg_lock_sw;

क्रमागत ice_status
ice_aq_send_cmd(काष्ठा ice_hw *hw, काष्ठा ice_aq_desc *desc,
		व्योम *buf, u16 buf_size, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status ice_aq_get_fw_ver(काष्ठा ice_hw *hw, काष्ठा ice_sq_cd *cd);

क्रमागत ice_status
ice_aq_send_driver_ver(काष्ठा ice_hw *hw, काष्ठा ice_driver_ver *dv,
		       काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_get_phy_caps(काष्ठा ice_port_info *pi, bool qual_mods, u8 report_mode,
		    काष्ठा ice_aqc_get_phy_caps_data *caps,
		    काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_list_caps(काष्ठा ice_hw *hw, व्योम *buf, u16 buf_size, u32 *cap_count,
		 क्रमागत ice_adminq_opc opc, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_discover_dev_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_caps);
व्योम
ice_update_phy_type(u64 *phy_type_low, u64 *phy_type_high,
		    u16 link_speeds_biपंचांगap);
क्रमागत ice_status
ice_aq_manage_mac_ग_लिखो(काष्ठा ice_hw *hw, स्थिर u8 *mac_addr, u8 flags,
			काष्ठा ice_sq_cd *cd);
क्रमागत ice_status ice_clear_pf_cfg(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_aq_set_phy_cfg(काष्ठा ice_hw *hw, काष्ठा ice_port_info *pi,
		   काष्ठा ice_aqc_set_phy_cfg_data *cfg, काष्ठा ice_sq_cd *cd);
bool ice_fw_supports_link_override(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_get_link_शेष_override(काष्ठा ice_link_शेष_override_tlv *lकरो,
			      काष्ठा ice_port_info *pi);
bool ice_is_phy_caps_an_enabled(काष्ठा ice_aqc_get_phy_caps_data *caps);

क्रमागत ice_fc_mode ice_caps_to_fc_mode(u8 caps);
क्रमागत ice_fec_mode ice_caps_to_fec_mode(u8 caps, u8 fec_options);
क्रमागत ice_status
ice_set_fc(काष्ठा ice_port_info *pi, u8 *aq_failures,
	   bool ena_स्वतः_link_update);
क्रमागत ice_status
ice_cfg_phy_fc(काष्ठा ice_port_info *pi, काष्ठा ice_aqc_set_phy_cfg_data *cfg,
	       क्रमागत ice_fc_mode fc);
bool
ice_phy_caps_equals_cfg(काष्ठा ice_aqc_get_phy_caps_data *caps,
			काष्ठा ice_aqc_set_phy_cfg_data *cfg);
व्योम
ice_copy_phy_caps_to_cfg(काष्ठा ice_port_info *pi,
			 काष्ठा ice_aqc_get_phy_caps_data *caps,
			 काष्ठा ice_aqc_set_phy_cfg_data *cfg);
क्रमागत ice_status
ice_cfg_phy_fec(काष्ठा ice_port_info *pi, काष्ठा ice_aqc_set_phy_cfg_data *cfg,
		क्रमागत ice_fec_mode fec);
क्रमागत ice_status
ice_aq_set_link_restart_an(काष्ठा ice_port_info *pi, bool ena_link,
			   काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_set_mac_cfg(काष्ठा ice_hw *hw, u16 max_frame_size, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_get_link_info(काष्ठा ice_port_info *pi, bool ena_lse,
		     काष्ठा ice_link_status *link, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_set_event_mask(काष्ठा ice_hw *hw, u8 port_num, u16 mask,
		      काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_set_mac_loopback(काष्ठा ice_hw *hw, bool ena_lpbk, काष्ठा ice_sq_cd *cd);

क्रमागत ice_status
ice_aq_set_port_id_led(काष्ठा ice_port_info *pi, bool is_orig_mode,
		       काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_sff_eeprom(काष्ठा ice_hw *hw, u16 lport, u8 bus_addr,
		  u16 mem_addr, u8 page, u8 set_page, u8 *data, u8 length,
		  bool ग_लिखो, काष्ठा ice_sq_cd *cd);

क्रमागत ice_status
ice_dis_vsi_txq(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc, u8 num_queues,
		u16 *q_handle, u16 *q_ids, u32 *q_teids,
		क्रमागत ice_disq_rst_src rst_src, u16 vmvf_num,
		काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_cfg_vsi_lan(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc_biपंचांगap,
		u16 *max_lanqs);
क्रमागत ice_status
ice_ena_vsi_txq(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc, u16 q_handle,
		u8 num_qgrps, काष्ठा ice_aqc_add_tx_qgrp *buf, u16 buf_size,
		काष्ठा ice_sq_cd *cd);
क्रमागत ice_status ice_replay_vsi(काष्ठा ice_hw *hw, u16 vsi_handle);
व्योम ice_replay_post(काष्ठा ice_hw *hw);
व्योम ice_output_fw_log(काष्ठा ice_hw *hw, काष्ठा ice_aq_desc *desc, व्योम *buf);
काष्ठा ice_q_ctx *
ice_get_lan_q_ctx(काष्ठा ice_hw *hw, u16 vsi_handle, u8 tc, u16 q_handle);
व्योम
ice_stat_update40(काष्ठा ice_hw *hw, u32 reg, bool prev_stat_loaded,
		  u64 *prev_stat, u64 *cur_stat);
व्योम
ice_stat_update32(काष्ठा ice_hw *hw, u32 reg, bool prev_stat_loaded,
		  u64 *prev_stat, u64 *cur_stat);
क्रमागत ice_status
ice_sched_query_elem(काष्ठा ice_hw *hw, u32 node_teid,
		     काष्ठा ice_aqc_txsched_elem_data *buf);
क्रमागत ice_status
ice_aq_set_lldp_mib(काष्ठा ice_hw *hw, u8 mib_type, व्योम *buf, u16 buf_size,
		    काष्ठा ice_sq_cd *cd);
bool ice_fw_supports_lldp_fltr_ctrl(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_lldp_fltr_add_हटाओ(काष्ठा ice_hw *hw, u16 vsi_num, bool add);
bool ice_fw_supports_report_dflt_cfg(काष्ठा ice_hw *hw);
#पूर्ण_अगर /* _ICE_COMMON_H_ */
