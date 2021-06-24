<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#अगर_अघोषित _I40E_PROTOTYPE_H_
#घोषणा _I40E_PROTOTYPE_H_

#समावेश "i40e_type.h"
#समावेश "i40e_alloc.h"
#समावेश <linux/avf/virtchnl.h>

/* Prototypes क्रम shared code functions that are not in
 * the standard function poपूर्णांकer काष्ठाures.  These are
 * mostly because they are needed even beक्रमe the init
 * has happened and will assist in the early SW and FW
 * setup.
 */

/* adminq functions */
i40e_status i40e_init_adminq(काष्ठा i40e_hw *hw);
व्योम i40e_shutकरोwn_adminq(काष्ठा i40e_hw *hw);
व्योम i40e_adminq_init_ring_data(काष्ठा i40e_hw *hw);
i40e_status i40e_clean_arq_element(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_arq_event_info *e,
					     u16 *events_pending);
i40e_status i40e_asq_send_command(काष्ठा i40e_hw *hw,
				काष्ठा i40e_aq_desc *desc,
				व्योम *buff, /* can be शून्य */
				u16  buff_size,
				काष्ठा i40e_asq_cmd_details *cmd_details);

/* debug function क्रम adminq */
व्योम i40e_debug_aq(काष्ठा i40e_hw *hw, क्रमागत i40e_debug_mask mask,
		   व्योम *desc, व्योम *buffer, u16 buf_len);

व्योम i40e_idle_aq(काष्ठा i40e_hw *hw);
bool i40e_check_asq_alive(काष्ठा i40e_hw *hw);
i40e_status i40e_aq_queue_shutकरोwn(काष्ठा i40e_hw *hw, bool unloading);
स्थिर अक्षर *i40e_aq_str(काष्ठा i40e_hw *hw, क्रमागत i40e_admin_queue_err aq_err);
स्थिर अक्षर *i40e_stat_str(काष्ठा i40e_hw *hw, i40e_status stat_err);

i40e_status i40e_aq_get_rss_lut(काष्ठा i40e_hw *hw, u16 seid,
				bool pf_lut, u8 *lut, u16 lut_size);
i40e_status i40e_aq_set_rss_lut(काष्ठा i40e_hw *hw, u16 seid,
				bool pf_lut, u8 *lut, u16 lut_size);
i40e_status i40e_aq_get_rss_key(काष्ठा i40e_hw *hw,
				u16 seid,
				काष्ठा i40e_aqc_get_set_rss_key_data *key);
i40e_status i40e_aq_set_rss_key(काष्ठा i40e_hw *hw,
				u16 seid,
				काष्ठा i40e_aqc_get_set_rss_key_data *key);

u32 i40e_led_get(काष्ठा i40e_hw *hw);
व्योम i40e_led_set(काष्ठा i40e_hw *hw, u32 mode, bool blink);
i40e_status i40e_led_set_phy(काष्ठा i40e_hw *hw, bool on,
			     u16 led_addr, u32 mode);
i40e_status i40e_led_get_phy(काष्ठा i40e_hw *hw, u16 *led_addr,
			     u16 *val);
i40e_status i40e_blink_phy_link_led(काष्ठा i40e_hw *hw,
				    u32 समय, u32 पूर्णांकerval);

/* admin send queue commands */

i40e_status i40e_aq_get_firmware_version(काष्ठा i40e_hw *hw,
				u16 *fw_major_version, u16 *fw_minor_version,
				u32 *fw_build,
				u16 *api_major_version, u16 *api_minor_version,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_debug_ग_लिखो_रेजिस्टर(काष्ठा i40e_hw *hw,
					u32 reg_addr, u64 reg_val,
					काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_debug_पढ़ो_रेजिस्टर(काष्ठा i40e_hw *hw,
				u32  reg_addr, u64 *reg_val,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_phy_debug(काष्ठा i40e_hw *hw, u8 cmd_flags,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_शेष_vsi(काष्ठा i40e_hw *hw, u16 vsi_id,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_clear_शेष_vsi(काष्ठा i40e_hw *hw, u16 vsi_id,
				      काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code i40e_aq_get_phy_capabilities(काष्ठा i40e_hw *hw,
			bool qualअगरied_modules, bool report_init,
			काष्ठा i40e_aq_get_phy_abilities_resp *abilities,
			काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code i40e_aq_set_phy_config(काष्ठा i40e_hw *hw,
				काष्ठा i40e_aq_set_phy_config *config,
				काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code i40e_set_fc(काष्ठा i40e_hw *hw, u8 *aq_failures,
				  bool atomic_reset);
i40e_status i40e_aq_set_phy_पूर्णांक_mask(काष्ठा i40e_hw *hw, u16 mask,
				     काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_clear_pxe_mode(काष्ठा i40e_hw *hw,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_link_restart_an(काष्ठा i40e_hw *hw,
					bool enable_link,
					काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_get_link_info(काष्ठा i40e_hw *hw,
				bool enable_lse, काष्ठा i40e_link_status *link,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_local_advt_reg(काष्ठा i40e_hw *hw,
				u64 advt_reg,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_send_driver_version(काष्ठा i40e_hw *hw,
				काष्ठा i40e_driver_version *dv,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_add_vsi(काष्ठा i40e_hw *hw,
				काष्ठा i40e_vsi_context *vsi_ctx,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_vsi_broadcast(काष्ठा i40e_hw *hw,
				u16 vsi_id, bool set_filter,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_vsi_unicast_promiscuous(काष्ठा i40e_hw *hw,
		u16 vsi_id, bool set, काष्ठा i40e_asq_cmd_details *cmd_details,
		bool rx_only_promisc);
i40e_status i40e_aq_set_vsi_multicast_promiscuous(काष्ठा i40e_hw *hw,
		u16 vsi_id, bool set, काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code i40e_aq_set_vsi_mc_promisc_on_vlan(काष्ठा i40e_hw *hw,
							 u16 seid, bool enable,
							 u16 vid,
				काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code i40e_aq_set_vsi_uc_promisc_on_vlan(काष्ठा i40e_hw *hw,
							 u16 seid, bool enable,
							 u16 vid,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_vsi_bc_promisc_on_vlan(काष्ठा i40e_hw *hw,
				u16 seid, bool enable, u16 vid,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_vsi_vlan_promisc(काष्ठा i40e_hw *hw,
				u16 seid, bool enable,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_get_vsi_params(काष्ठा i40e_hw *hw,
				काष्ठा i40e_vsi_context *vsi_ctx,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_update_vsi_params(काष्ठा i40e_hw *hw,
				काष्ठा i40e_vsi_context *vsi_ctx,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_add_veb(काष्ठा i40e_hw *hw, u16 uplink_seid,
				u16 करोwnlink_seid, u8 enabled_tc,
				bool शेष_port, u16 *pveb_seid,
				bool enable_stats,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_get_veb_parameters(काष्ठा i40e_hw *hw,
				u16 veb_seid, u16 *चयन_id, bool *भग्नing,
				u16 *statistic_index, u16 *vebs_used,
				u16 *vebs_मुक्त,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_add_macvlan(काष्ठा i40e_hw *hw, u16 vsi_id,
			काष्ठा i40e_aqc_add_macvlan_element_data *mv_list,
			u16 count, काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_हटाओ_macvlan(काष्ठा i40e_hw *hw, u16 vsi_id,
			काष्ठा i40e_aqc_हटाओ_macvlan_element_data *mv_list,
			u16 count, काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_add_mirrorrule(काष्ठा i40e_hw *hw, u16 sw_seid,
			u16 rule_type, u16 dest_vsi, u16 count, __le16 *mr_list,
			काष्ठा i40e_asq_cmd_details *cmd_details,
			u16 *rule_id, u16 *rules_used, u16 *rules_मुक्त);
i40e_status i40e_aq_delete_mirrorrule(काष्ठा i40e_hw *hw, u16 sw_seid,
			u16 rule_type, u16 rule_id, u16 count, __le16 *mr_list,
			काष्ठा i40e_asq_cmd_details *cmd_details,
			u16 *rules_used, u16 *rules_मुक्त);

i40e_status i40e_aq_send_msg_to_vf(काष्ठा i40e_hw *hw, u16 vfid,
				u32 v_opcode, u32 v_retval, u8 *msg, u16 msglen,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_get_चयन_config(काष्ठा i40e_hw *hw,
				काष्ठा i40e_aqc_get_चयन_config_resp *buf,
				u16 buf_size, u16 *start_seid,
				काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code i40e_aq_set_चयन_config(काष्ठा i40e_hw *hw,
						u16 flags,
						u16 valid_flags, u8 mode,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_request_resource(काष्ठा i40e_hw *hw,
				क्रमागत i40e_aq_resources_ids resource,
				क्रमागत i40e_aq_resource_access_type access,
				u8 sdp_number, u64 *समयout,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_release_resource(काष्ठा i40e_hw *hw,
				क्रमागत i40e_aq_resources_ids resource,
				u8 sdp_number,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_पढ़ो_nvm(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
				u32 offset, u16 length, व्योम *data,
				bool last_command,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_erase_nvm(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
			      u32 offset, u16 length, bool last_command,
			      काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_discover_capabilities(काष्ठा i40e_hw *hw,
				व्योम *buff, u16 buff_size, u16 *data_size,
				क्रमागत i40e_admin_queue_opc list_type_opc,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_update_nvm(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
				u32 offset, u16 length, व्योम *data,
				bool last_command, u8 preservation_flags,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_rearrange_nvm(काष्ठा i40e_hw *hw,
				  u8 rearrange_nvm,
				  काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_get_lldp_mib(काष्ठा i40e_hw *hw, u8 bridge_type,
				u8 mib_type, व्योम *buff, u16 buff_size,
				u16 *local_len, u16 *remote_len,
				काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code
i40e_aq_set_lldp_mib(काष्ठा i40e_hw *hw,
		     u8 mib_type, व्योम *buff, u16 buff_size,
		     काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_cfg_lldp_mib_change_event(काष्ठा i40e_hw *hw,
				bool enable_update,
				काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code
i40e_aq_restore_lldp(काष्ठा i40e_hw *hw, u8 *setting, bool restore,
		     काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_stop_lldp(काष्ठा i40e_hw *hw, bool shutकरोwn_agent,
			      bool persist,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_set_dcb_parameters(काष्ठा i40e_hw *hw,
				       bool dcb_enable,
				       काष्ठा i40e_asq_cmd_details
				       *cmd_details);
i40e_status i40e_aq_start_lldp(काष्ठा i40e_hw *hw, bool persist,
			       काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_get_cee_dcb_config(काष्ठा i40e_hw *hw,
				       व्योम *buff, u16 buff_size,
				       काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_add_udp_tunnel(काष्ठा i40e_hw *hw,
				u16 udp_port, u8 protocol_index,
				u8 *filter_index,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_del_udp_tunnel(काष्ठा i40e_hw *hw, u8 index,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_delete_element(काष्ठा i40e_hw *hw, u16 seid,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_mac_address_ग_लिखो(काष्ठा i40e_hw *hw,
				    u16 flags, u8 *mac_addr,
				    काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_config_vsi_bw_limit(काष्ठा i40e_hw *hw,
				u16 seid, u16 credit, u8 max_credit,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_dcb_updated(काष्ठा i40e_hw *hw,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_config_चयन_comp_bw_limit(काष्ठा i40e_hw *hw,
				u16 seid, u16 credit, u8 max_bw,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_config_vsi_tc_bw(काष्ठा i40e_hw *hw, u16 seid,
			काष्ठा i40e_aqc_configure_vsi_tc_bw_data *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_config_चयन_comp_ets(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_configure_चयनing_comp_ets_data *ets_data,
		क्रमागत i40e_admin_queue_opc opcode,
		काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_config_चयन_comp_bw_config(काष्ठा i40e_hw *hw,
	u16 seid,
	काष्ठा i40e_aqc_configure_चयनing_comp_bw_config_data *bw_data,
	काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_query_vsi_bw_config(काष्ठा i40e_hw *hw,
			u16 seid,
			काष्ठा i40e_aqc_query_vsi_bw_config_resp *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_query_vsi_ets_sla_config(काष्ठा i40e_hw *hw,
			u16 seid,
			काष्ठा i40e_aqc_query_vsi_ets_sla_config_resp *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_query_चयन_comp_ets_config(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_query_चयनing_comp_ets_config_resp *bw_data,
		काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_query_port_ets_config(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_query_port_ets_config_resp *bw_data,
		काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_query_चयन_comp_bw_config(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_query_चयनing_comp_bw_config_resp *bw_data,
		काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_resume_port_tx(काष्ठा i40e_hw *hw,
				   काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code
i40e_aq_add_cloud_filters_bb(काष्ठा i40e_hw *hw, u16 seid,
			     काष्ठा i40e_aqc_cloud_filters_element_bb *filters,
			     u8 filter_count);
क्रमागत i40e_status_code
i40e_aq_add_cloud_filters(काष्ठा i40e_hw *hw, u16 vsi,
			  काष्ठा i40e_aqc_cloud_filters_element_data *filters,
			  u8 filter_count);
क्रमागत i40e_status_code
i40e_aq_rem_cloud_filters(काष्ठा i40e_hw *hw, u16 vsi,
			  काष्ठा i40e_aqc_cloud_filters_element_data *filters,
			  u8 filter_count);
क्रमागत i40e_status_code
i40e_aq_rem_cloud_filters_bb(काष्ठा i40e_hw *hw, u16 seid,
			     काष्ठा i40e_aqc_cloud_filters_element_bb *filters,
			     u8 filter_count);
i40e_status i40e_पढ़ो_lldp_cfg(काष्ठा i40e_hw *hw,
			       काष्ठा i40e_lldp_variables *lldp_cfg);
क्रमागत i40e_status_code
i40e_aq_suspend_port_tx(काष्ठा i40e_hw *hw, u16 seid,
			काष्ठा i40e_asq_cmd_details *cmd_details);
/* i40e_common */
i40e_status i40e_init_shared_code(काष्ठा i40e_hw *hw);
i40e_status i40e_pf_reset(काष्ठा i40e_hw *hw);
व्योम i40e_clear_hw(काष्ठा i40e_hw *hw);
व्योम i40e_clear_pxe_mode(काष्ठा i40e_hw *hw);
i40e_status i40e_get_link_status(काष्ठा i40e_hw *hw, bool *link_up);
i40e_status i40e_update_link_info(काष्ठा i40e_hw *hw);
i40e_status i40e_get_mac_addr(काष्ठा i40e_hw *hw, u8 *mac_addr);
i40e_status i40e_पढ़ो_bw_from_alt_ram(काष्ठा i40e_hw *hw,
				      u32 *max_bw, u32 *min_bw, bool *min_valid,
				      bool *max_valid);
i40e_status i40e_aq_configure_partition_bw(काष्ठा i40e_hw *hw,
			काष्ठा i40e_aqc_configure_partition_bw_data *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_get_port_mac_addr(काष्ठा i40e_hw *hw, u8 *mac_addr);
i40e_status i40e_पढ़ो_pba_string(काष्ठा i40e_hw *hw, u8 *pba_num,
				 u32 pba_num_size);
i40e_status i40e_validate_mac_addr(u8 *mac_addr);
व्योम i40e_pre_tx_queue_cfg(काष्ठा i40e_hw *hw, u32 queue, bool enable);
/* prototype क्रम functions used क्रम NVM access */
i40e_status i40e_init_nvm(काष्ठा i40e_hw *hw);
i40e_status i40e_acquire_nvm(काष्ठा i40e_hw *hw,
				      क्रमागत i40e_aq_resource_access_type access);
व्योम i40e_release_nvm(काष्ठा i40e_hw *hw);
i40e_status i40e_पढ़ो_nvm_word(काष्ठा i40e_hw *hw, u16 offset,
					 u16 *data);
क्रमागत i40e_status_code i40e_पढ़ो_nvm_module_data(काष्ठा i40e_hw *hw,
						u8 module_ptr,
						u16 module_offset,
						u16 data_offset,
						u16 words_data_size,
						u16 *data_ptr);
i40e_status i40e_पढ़ो_nvm_buffer(काष्ठा i40e_hw *hw, u16 offset,
				 u16 *words, u16 *data);
i40e_status i40e_update_nvm_checksum(काष्ठा i40e_hw *hw);
i40e_status i40e_validate_nvm_checksum(काष्ठा i40e_hw *hw,
						 u16 *checksum);
i40e_status i40e_nvmupd_command(काष्ठा i40e_hw *hw,
				काष्ठा i40e_nvm_access *cmd,
				u8 *bytes, पूर्णांक *);
व्योम i40e_nvmupd_check_रुको_event(काष्ठा i40e_hw *hw, u16 opcode,
				  काष्ठा i40e_aq_desc *desc);
व्योम i40e_nvmupd_clear_रुको_state(काष्ठा i40e_hw *hw);
व्योम i40e_set_pci_config_data(काष्ठा i40e_hw *hw, u16 link_status);

i40e_status i40e_set_mac_type(काष्ठा i40e_hw *hw);

बाह्य काष्ठा i40e_rx_ptype_decoded i40e_ptype_lookup[];

अटल अंतरभूत काष्ठा i40e_rx_ptype_decoded decode_rx_desc_ptype(u8 ptype)
अणु
	वापस i40e_ptype_lookup[ptype];
पूर्ण

/**
 * i40e_virtchnl_link_speed - Convert AdminQ link_speed to virtchnl definition
 * @link_speed: the speed to convert
 *
 * Returns the link_speed in terms of the virtchnl पूर्णांकerface, क्रम use in
 * converting link_speed as reported by the AdminQ पूर्णांकo the क्रमmat used क्रम
 * talking to virtchnl devices. If we can't represent the link speed properly,
 * report LINK_SPEED_UNKNOWN.
 **/
अटल अंतरभूत क्रमागत virtchnl_link_speed
i40e_virtchnl_link_speed(क्रमागत i40e_aq_link_speed link_speed)
अणु
	चयन (link_speed) अणु
	हाल I40E_LINK_SPEED_100MB:
		वापस VIRTCHNL_LINK_SPEED_100MB;
	हाल I40E_LINK_SPEED_1GB:
		वापस VIRTCHNL_LINK_SPEED_1GB;
	हाल I40E_LINK_SPEED_2_5GB:
		वापस VIRTCHNL_LINK_SPEED_2_5GB;
	हाल I40E_LINK_SPEED_5GB:
		वापस VIRTCHNL_LINK_SPEED_5GB;
	हाल I40E_LINK_SPEED_10GB:
		वापस VIRTCHNL_LINK_SPEED_10GB;
	हाल I40E_LINK_SPEED_40GB:
		वापस VIRTCHNL_LINK_SPEED_40GB;
	हाल I40E_LINK_SPEED_20GB:
		वापस VIRTCHNL_LINK_SPEED_20GB;
	हाल I40E_LINK_SPEED_25GB:
		वापस VIRTCHNL_LINK_SPEED_25GB;
	हाल I40E_LINK_SPEED_UNKNOWN:
	शेष:
		वापस VIRTCHNL_LINK_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

/* prototype क्रम functions used क्रम SW locks */

/* i40e_common क्रम VF drivers*/
व्योम i40e_vf_parse_hw_config(काष्ठा i40e_hw *hw,
			     काष्ठा virtchnl_vf_resource *msg);
i40e_status i40e_vf_reset(काष्ठा i40e_hw *hw);
i40e_status i40e_aq_send_msg_to_pf(काष्ठा i40e_hw *hw,
				क्रमागत virtchnl_ops v_opcode,
				i40e_status v_retval,
				u8 *msg, u16 msglen,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_set_filter_control(काष्ठा i40e_hw *hw,
				काष्ठा i40e_filter_control_settings *settings);
i40e_status i40e_aq_add_rem_control_packet_filter(काष्ठा i40e_hw *hw,
				u8 *mac_addr, u16 ethtype, u16 flags,
				u16 vsi_seid, u16 queue, bool is_add,
				काष्ठा i40e_control_filter_stats *stats,
				काष्ठा i40e_asq_cmd_details *cmd_details);
i40e_status i40e_aq_debug_dump(काष्ठा i40e_hw *hw, u8 cluster_id,
			       u8 table_id, u32 start_index, u16 buff_size,
			       व्योम *buff, u16 *ret_buff_size,
			       u8 *ret_next_table, u32 *ret_next_index,
			       काष्ठा i40e_asq_cmd_details *cmd_details);
व्योम i40e_add_filter_to_drop_tx_flow_control_frames(काष्ठा i40e_hw *hw,
						    u16 vsi_seid);
i40e_status i40e_aq_rx_ctl_पढ़ो_रेजिस्टर(काष्ठा i40e_hw *hw,
				u32 reg_addr, u32 *reg_val,
				काष्ठा i40e_asq_cmd_details *cmd_details);
u32 i40e_पढ़ो_rx_ctl(काष्ठा i40e_hw *hw, u32 reg_addr);
i40e_status i40e_aq_rx_ctl_ग_लिखो_रेजिस्टर(काष्ठा i40e_hw *hw,
				u32 reg_addr, u32 reg_val,
				काष्ठा i40e_asq_cmd_details *cmd_details);
व्योम i40e_ग_लिखो_rx_ctl(काष्ठा i40e_hw *hw, u32 reg_addr, u32 reg_val);
क्रमागत i40e_status_code
i40e_aq_set_phy_रेजिस्टर_ext(काष्ठा i40e_hw *hw,
			     u8 phy_select, u8 dev_addr, bool page_change,
			     bool set_mdio, u8 mdio_num,
			     u32 reg_addr, u32 reg_val,
			     काष्ठा i40e_asq_cmd_details *cmd_details);
क्रमागत i40e_status_code
i40e_aq_get_phy_रेजिस्टर_ext(काष्ठा i40e_hw *hw,
			     u8 phy_select, u8 dev_addr, bool page_change,
			     bool set_mdio, u8 mdio_num,
			     u32 reg_addr, u32 *reg_val,
			     काष्ठा i40e_asq_cmd_details *cmd_details);

/* Convenience wrappers क्रम most common use हाल */
#घोषणा i40e_aq_set_phy_रेजिस्टर(hw, ps, da, pc, ra, rv, cd)		\
	i40e_aq_set_phy_रेजिस्टर_ext(hw, ps, da, pc, false, 0, ra, rv, cd)
#घोषणा i40e_aq_get_phy_रेजिस्टर(hw, ps, da, pc, ra, rv, cd)		\
	i40e_aq_get_phy_रेजिस्टर_ext(hw, ps, da, pc, false, 0, ra, rv, cd)

i40e_status i40e_पढ़ो_phy_रेजिस्टर_clause22(काष्ठा i40e_hw *hw,
					    u16 reg, u8 phy_addr, u16 *value);
i40e_status i40e_ग_लिखो_phy_रेजिस्टर_clause22(काष्ठा i40e_hw *hw,
					     u16 reg, u8 phy_addr, u16 value);
i40e_status i40e_पढ़ो_phy_रेजिस्टर_clause45(काष्ठा i40e_hw *hw,
				u8 page, u16 reg, u8 phy_addr, u16 *value);
i40e_status i40e_ग_लिखो_phy_रेजिस्टर_clause45(काष्ठा i40e_hw *hw,
				u8 page, u16 reg, u8 phy_addr, u16 value);
i40e_status i40e_पढ़ो_phy_रेजिस्टर(काष्ठा i40e_hw *hw, u8 page, u16 reg,
				   u8 phy_addr, u16 *value);
i40e_status i40e_ग_लिखो_phy_रेजिस्टर(काष्ठा i40e_hw *hw, u8 page, u16 reg,
				    u8 phy_addr, u16 value);
u8 i40e_get_phy_address(काष्ठा i40e_hw *hw, u8 dev_num);
i40e_status i40e_blink_phy_link_led(काष्ठा i40e_hw *hw,
				    u32 समय, u32 पूर्णांकerval);
i40e_status i40e_aq_ग_लिखो_ddp(काष्ठा i40e_hw *hw, व्योम *buff,
			      u16 buff_size, u32 track_id,
			      u32 *error_offset, u32 *error_info,
			      काष्ठा i40e_asq_cmd_details *
			      cmd_details);
i40e_status i40e_aq_get_ddp_list(काष्ठा i40e_hw *hw, व्योम *buff,
				 u16 buff_size, u8 flags,
				 काष्ठा i40e_asq_cmd_details *
				 cmd_details);
काष्ठा i40e_generic_seg_header *
i40e_find_segment_in_package(u32 segment_type,
			     काष्ठा i40e_package_header *pkg_header);
काष्ठा i40e_profile_section_header *
i40e_find_section_in_profile(u32 section_type,
			     काष्ठा i40e_profile_segment *profile);
क्रमागत i40e_status_code
i40e_ग_लिखो_profile(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *i40e_seg,
		   u32 track_id);
क्रमागत i40e_status_code
i40e_rollback_profile(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *i40e_seg,
		      u32 track_id);
क्रमागत i40e_status_code
i40e_add_pinfo_to_list(काष्ठा i40e_hw *hw,
		       काष्ठा i40e_profile_segment *profile,
		       u8 *profile_info_sec, u32 track_id);
#पूर्ण_अगर /* _I40E_PROTOTYPE_H_ */
