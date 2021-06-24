<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice_switch.h"

#घोषणा ICE_ETH_DA_OFFSET		0
#घोषणा ICE_ETH_ETHTYPE_OFFSET		12
#घोषणा ICE_ETH_VLAN_TCI_OFFSET		14
#घोषणा ICE_MAX_VLAN_ID			0xFFF

/* Dummy ethernet header needed in the ice_aqc_sw_rules_elem
 * काष्ठा to configure any चयन filter rules.
 * अणुDA (6 bytes), SA(6 bytes),
 * Ether type (2 bytes क्रम header without VLAN tag) OR
 * VLAN tag (4 bytes क्रम header with VLAN tag) पूर्ण
 *
 * Word on Hardcoded values
 * byte 0 = 0x2: to identअगरy it as locally administered DA MAC
 * byte 6 = 0x2: to identअगरy it as locally administered SA MAC
 * byte 12 = 0x81 & byte 13 = 0x00:
 *	In हाल of VLAN filter first two bytes defines ether type (0x8100)
 *	and reमुख्यing two bytes are placeholder क्रम programming a given VLAN ID
 *	In हाल of Ether type filter it is treated as header without VLAN tag
 *	and byte 12 and 13 is used to program a given Ether type instead
 */
#घोषणा DUMMY_ETH_HDR_LEN		16
अटल स्थिर u8 dummy_eth_header[DUMMY_ETH_HDR_LEN] = अणु 0x2, 0, 0, 0, 0, 0,
							0x2, 0, 0, 0, 0, 0,
							0x81, 0, 0, 0पूर्ण;

#घोषणा ICE_SW_RULE_RX_TX_ETH_HDR_SIZE \
	(दुरत्व(काष्ठा ice_aqc_sw_rules_elem, pdata.lkup_tx_rx.hdr) + \
	 (DUMMY_ETH_HDR_LEN * \
	  माप(((काष्ठा ice_sw_rule_lkup_rx_tx *)0)->hdr[0])))
#घोषणा ICE_SW_RULE_RX_TX_NO_HDR_SIZE \
	(दुरत्व(काष्ठा ice_aqc_sw_rules_elem, pdata.lkup_tx_rx.hdr))
#घोषणा ICE_SW_RULE_LG_ACT_SIZE(n) \
	(दुरत्व(काष्ठा ice_aqc_sw_rules_elem, pdata.lg_act.act) + \
	 ((n) * माप(((काष्ठा ice_sw_rule_lg_act *)0)->act[0])))
#घोषणा ICE_SW_RULE_VSI_LIST_SIZE(n) \
	(दुरत्व(काष्ठा ice_aqc_sw_rules_elem, pdata.vsi_list.vsi) + \
	 ((n) * माप(((काष्ठा ice_sw_rule_vsi_list *)0)->vsi[0])))

/**
 * ice_init_def_sw_recp - initialize the recipe book keeping tables
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Allocate memory क्रम the entire recipe table and initialize the काष्ठाures/
 * entries corresponding to basic recipes.
 */
क्रमागत ice_status ice_init_def_sw_recp(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_sw_recipe *recps;
	u8 i;

	recps = devm_kसुस्मृति(ice_hw_to_dev(hw), ICE_MAX_NUM_RECIPES,
			     माप(*recps), GFP_KERNEL);
	अगर (!recps)
		वापस ICE_ERR_NO_MEMORY;

	क्रम (i = 0; i < ICE_SW_LKUP_LAST; i++) अणु
		recps[i].root_rid = i;
		INIT_LIST_HEAD(&recps[i].filt_rules);
		INIT_LIST_HEAD(&recps[i].filt_replay_rules);
		mutex_init(&recps[i].filt_rule_lock);
	पूर्ण

	hw->चयन_info->recp_list = recps;

	वापस 0;
पूर्ण

/**
 * ice_aq_get_sw_cfg - get चयन configuration
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @buf: poपूर्णांकer to the result buffer
 * @buf_size: length of the buffer available क्रम response
 * @req_desc: poपूर्णांकer to requested descriptor
 * @num_elems: poपूर्णांकer to number of elements
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get चयन configuration (0x0200) to be placed in buf.
 * This admin command वापसs inक्रमmation such as initial VSI/port number
 * and चयन ID it beदीर्घs to.
 *
 * NOTE: *req_desc is both an input/output parameter.
 * The caller of this function first calls this function with *request_desc set
 * to 0. If the response from f/w has *req_desc set to 0, all the चयन
 * configuration inक्रमmation has been वापसed; अगर non-zero (meaning not all
 * the inक्रमmation was वापसed), the caller should call this function again
 * with *req_desc set to the previous value वापसed by f/w to get the
 * next block of चयन configuration inक्रमmation.
 *
 * *num_elems is output only parameter. This reflects the number of elements
 * in response buffer. The caller of this function to use *num_elems जबतक
 * parsing the response buffer.
 */
अटल क्रमागत ice_status
ice_aq_get_sw_cfg(काष्ठा ice_hw *hw, काष्ठा ice_aqc_get_sw_cfg_resp_elem *buf,
		  u16 buf_size, u16 *req_desc, u16 *num_elems,
		  काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_get_sw_cfg *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_sw_cfg);
	cmd = &desc.params.get_sw_conf;
	cmd->element = cpu_to_le16(*req_desc);

	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	अगर (!status) अणु
		*req_desc = le16_to_cpu(cmd->element);
		*num_elems = le16_to_cpu(cmd->num_elems);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_add_vsi
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_ctx: poपूर्णांकer to a VSI context काष्ठा
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add a VSI context to the hardware (0x0210)
 */
अटल क्रमागत ice_status
ice_aq_add_vsi(काष्ठा ice_hw *hw, काष्ठा ice_vsi_ctx *vsi_ctx,
	       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_add_update_मुक्त_vsi_resp *res;
	काष्ठा ice_aqc_add_get_update_मुक्त_vsi *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.vsi_cmd;
	res = &desc.params.add_update_मुक्त_vsi_res;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_add_vsi);

	अगर (!vsi_ctx->alloc_from_pool)
		cmd->vsi_num = cpu_to_le16(vsi_ctx->vsi_num |
					   ICE_AQ_VSI_IS_VALID);
	cmd->vf_id = vsi_ctx->vf_num;

	cmd->vsi_flags = cpu_to_le16(vsi_ctx->flags);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	status = ice_aq_send_cmd(hw, &desc, &vsi_ctx->info,
				 माप(vsi_ctx->info), cd);

	अगर (!status) अणु
		vsi_ctx->vsi_num = le16_to_cpu(res->vsi_num) & ICE_AQ_VSI_NUM_M;
		vsi_ctx->vsis_allocd = le16_to_cpu(res->vsi_used);
		vsi_ctx->vsis_unallocated = le16_to_cpu(res->vsi_मुक्त);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_मुक्त_vsi
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_ctx: poपूर्णांकer to a VSI context काष्ठा
 * @keep_vsi_alloc: keep VSI allocation as part of this PF's resources
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Free VSI context info from hardware (0x0213)
 */
अटल क्रमागत ice_status
ice_aq_मुक्त_vsi(काष्ठा ice_hw *hw, काष्ठा ice_vsi_ctx *vsi_ctx,
		bool keep_vsi_alloc, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_add_update_मुक्त_vsi_resp *resp;
	काष्ठा ice_aqc_add_get_update_मुक्त_vsi *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.vsi_cmd;
	resp = &desc.params.add_update_मुक्त_vsi_res;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_मुक्त_vsi);

	cmd->vsi_num = cpu_to_le16(vsi_ctx->vsi_num | ICE_AQ_VSI_IS_VALID);
	अगर (keep_vsi_alloc)
		cmd->cmd_flags = cpu_to_le16(ICE_AQ_VSI_KEEP_ALLOC);

	status = ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
	अगर (!status) अणु
		vsi_ctx->vsis_allocd = le16_to_cpu(resp->vsi_used);
		vsi_ctx->vsis_unallocated = le16_to_cpu(resp->vsi_मुक्त);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_update_vsi
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_ctx: poपूर्णांकer to a VSI context काष्ठा
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Update VSI context in the hardware (0x0211)
 */
अटल क्रमागत ice_status
ice_aq_update_vsi(काष्ठा ice_hw *hw, काष्ठा ice_vsi_ctx *vsi_ctx,
		  काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_add_update_मुक्त_vsi_resp *resp;
	काष्ठा ice_aqc_add_get_update_मुक्त_vsi *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.vsi_cmd;
	resp = &desc.params.add_update_मुक्त_vsi_res;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_update_vsi);

	cmd->vsi_num = cpu_to_le16(vsi_ctx->vsi_num | ICE_AQ_VSI_IS_VALID);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	status = ice_aq_send_cmd(hw, &desc, &vsi_ctx->info,
				 माप(vsi_ctx->info), cd);

	अगर (!status) अणु
		vsi_ctx->vsis_allocd = le16_to_cpu(resp->vsi_used);
		vsi_ctx->vsis_unallocated = le16_to_cpu(resp->vsi_मुक्त);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_is_vsi_valid - check whether the VSI is valid or not
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 *
 * check whether the VSI is valid or not
 */
bool ice_is_vsi_valid(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	वापस vsi_handle < ICE_MAX_VSI && hw->vsi_ctx[vsi_handle];
पूर्ण

/**
 * ice_get_hw_vsi_num - वापस the HW VSI number
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 *
 * वापस the HW VSI number
 * Caution: call this function only अगर VSI is valid (ice_is_vsi_valid)
 */
u16 ice_get_hw_vsi_num(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	वापस hw->vsi_ctx[vsi_handle]->vsi_num;
पूर्ण

/**
 * ice_get_vsi_ctx - वापस the VSI context entry क्रम a given VSI handle
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 *
 * वापस the VSI context entry क्रम a given VSI handle
 */
काष्ठा ice_vsi_ctx *ice_get_vsi_ctx(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	वापस (vsi_handle >= ICE_MAX_VSI) ? शून्य : hw->vsi_ctx[vsi_handle];
पूर्ण

/**
 * ice_save_vsi_ctx - save the VSI context क्रम a given VSI handle
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 * @vsi: VSI context poपूर्णांकer
 *
 * save the VSI context entry क्रम a given VSI handle
 */
अटल व्योम
ice_save_vsi_ctx(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi)
अणु
	hw->vsi_ctx[vsi_handle] = vsi;
पूर्ण

/**
 * ice_clear_vsi_q_ctx - clear VSI queue contexts क्रम all TCs
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 */
अटल व्योम ice_clear_vsi_q_ctx(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	काष्ठा ice_vsi_ctx *vsi;
	u8 i;

	vsi = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (!vsi)
		वापस;
	ice_क्रम_each_traffic_class(i) अणु
		अगर (vsi->lan_q_ctx[i]) अणु
			devm_kमुक्त(ice_hw_to_dev(hw), vsi->lan_q_ctx[i]);
			vsi->lan_q_ctx[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_clear_vsi_ctx - clear the VSI context entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 *
 * clear the VSI context entry
 */
अटल व्योम ice_clear_vsi_ctx(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	काष्ठा ice_vsi_ctx *vsi;

	vsi = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (vsi) अणु
		ice_clear_vsi_q_ctx(hw, vsi_handle);
		devm_kमुक्त(ice_hw_to_dev(hw), vsi);
		hw->vsi_ctx[vsi_handle] = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_clear_all_vsi_ctx - clear all the VSI context entries
 * @hw: poपूर्णांकer to the HW काष्ठा
 */
व्योम ice_clear_all_vsi_ctx(काष्ठा ice_hw *hw)
अणु
	u16 i;

	क्रम (i = 0; i < ICE_MAX_VSI; i++)
		ice_clear_vsi_ctx(hw, i);
पूर्ण

/**
 * ice_add_vsi - add VSI context to the hardware and VSI handle list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: unique VSI handle provided by drivers
 * @vsi_ctx: poपूर्णांकer to a VSI context काष्ठा
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add a VSI context to the hardware also add it पूर्णांकo the VSI handle list.
 * If this function माला_लो called after reset क्रम existing VSIs then update
 * with the new HW VSI number in the corresponding VSI handle list entry.
 */
क्रमागत ice_status
ice_add_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi_ctx,
	    काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_vsi_ctx *पंचांगp_vsi_ctx;
	क्रमागत ice_status status;

	अगर (vsi_handle >= ICE_MAX_VSI)
		वापस ICE_ERR_PARAM;
	status = ice_aq_add_vsi(hw, vsi_ctx, cd);
	अगर (status)
		वापस status;
	पंचांगp_vsi_ctx = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (!पंचांगp_vsi_ctx) अणु
		/* Create a new VSI context */
		पंचांगp_vsi_ctx = devm_kzalloc(ice_hw_to_dev(hw),
					   माप(*पंचांगp_vsi_ctx), GFP_KERNEL);
		अगर (!पंचांगp_vsi_ctx) अणु
			ice_aq_मुक्त_vsi(hw, vsi_ctx, false, cd);
			वापस ICE_ERR_NO_MEMORY;
		पूर्ण
		*पंचांगp_vsi_ctx = *vsi_ctx;
		ice_save_vsi_ctx(hw, vsi_handle, पंचांगp_vsi_ctx);
	पूर्ण अन्यथा अणु
		/* update with new HW VSI num */
		पंचांगp_vsi_ctx->vsi_num = vsi_ctx->vsi_num;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_मुक्त_vsi- मुक्त VSI context from hardware and VSI handle list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: unique VSI handle
 * @vsi_ctx: poपूर्णांकer to a VSI context काष्ठा
 * @keep_vsi_alloc: keep VSI allocation as part of this PF's resources
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Free VSI context info from hardware as well as from VSI handle list
 */
क्रमागत ice_status
ice_मुक्त_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi_ctx,
	     bool keep_vsi_alloc, काष्ठा ice_sq_cd *cd)
अणु
	क्रमागत ice_status status;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	vsi_ctx->vsi_num = ice_get_hw_vsi_num(hw, vsi_handle);
	status = ice_aq_मुक्त_vsi(hw, vsi_ctx, keep_vsi_alloc, cd);
	अगर (!status)
		ice_clear_vsi_ctx(hw, vsi_handle);
	वापस status;
पूर्ण

/**
 * ice_update_vsi
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: unique VSI handle
 * @vsi_ctx: poपूर्णांकer to a VSI context काष्ठा
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Update VSI context in the hardware
 */
क्रमागत ice_status
ice_update_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi_ctx,
	       काष्ठा ice_sq_cd *cd)
अणु
	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	vsi_ctx->vsi_num = ice_get_hw_vsi_num(hw, vsi_handle);
	वापस ice_aq_update_vsi(hw, vsi_ctx, cd);
पूर्ण

/**
 * ice_aq_alloc_मुक्त_vsi_list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_list_id: VSI list ID वापसed or used क्रम lookup
 * @lkup_type: चयन rule filter lookup type
 * @opc: चयन rules population command type - pass in the command opcode
 *
 * allocates or मुक्त a VSI list resource
 */
अटल क्रमागत ice_status
ice_aq_alloc_मुक्त_vsi_list(काष्ठा ice_hw *hw, u16 *vsi_list_id,
			   क्रमागत ice_sw_lkup_type lkup_type,
			   क्रमागत ice_adminq_opc opc)
अणु
	काष्ठा ice_aqc_alloc_मुक्त_res_elem *sw_buf;
	काष्ठा ice_aqc_res_elem *vsi_ele;
	क्रमागत ice_status status;
	u16 buf_len;

	buf_len = काष्ठा_size(sw_buf, elem, 1);
	sw_buf = devm_kzalloc(ice_hw_to_dev(hw), buf_len, GFP_KERNEL);
	अगर (!sw_buf)
		वापस ICE_ERR_NO_MEMORY;
	sw_buf->num_elems = cpu_to_le16(1);

	अगर (lkup_type == ICE_SW_LKUP_MAC ||
	    lkup_type == ICE_SW_LKUP_MAC_VLAN ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE_MAC ||
	    lkup_type == ICE_SW_LKUP_PROMISC ||
	    lkup_type == ICE_SW_LKUP_PROMISC_VLAN) अणु
		sw_buf->res_type = cpu_to_le16(ICE_AQC_RES_TYPE_VSI_LIST_REP);
	पूर्ण अन्यथा अगर (lkup_type == ICE_SW_LKUP_VLAN) अणु
		sw_buf->res_type =
			cpu_to_le16(ICE_AQC_RES_TYPE_VSI_LIST_PRUNE);
	पूर्ण अन्यथा अणु
		status = ICE_ERR_PARAM;
		जाओ ice_aq_alloc_मुक्त_vsi_list_निकास;
	पूर्ण

	अगर (opc == ice_aqc_opc_मुक्त_res)
		sw_buf->elem[0].e.sw_resp = cpu_to_le16(*vsi_list_id);

	status = ice_aq_alloc_मुक्त_res(hw, 1, sw_buf, buf_len, opc, शून्य);
	अगर (status)
		जाओ ice_aq_alloc_मुक्त_vsi_list_निकास;

	अगर (opc == ice_aqc_opc_alloc_res) अणु
		vsi_ele = &sw_buf->elem[0];
		*vsi_list_id = le16_to_cpu(vsi_ele->e.sw_resp);
	पूर्ण

ice_aq_alloc_मुक्त_vsi_list_निकास:
	devm_kमुक्त(ice_hw_to_dev(hw), sw_buf);
	वापस status;
पूर्ण

/**
 * ice_aq_sw_rules - add/update/हटाओ चयन rules
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @rule_list: poपूर्णांकer to चयन rule population list
 * @rule_list_sz: total size of the rule list in bytes
 * @num_rules: number of चयन rules in the rule_list
 * @opc: चयन rules population command type - pass in the command opcode
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add(0x02a0)/Update(0x02a1)/Remove(0x02a2) चयन rules commands to firmware
 */
अटल क्रमागत ice_status
ice_aq_sw_rules(काष्ठा ice_hw *hw, व्योम *rule_list, u16 rule_list_sz,
		u8 num_rules, क्रमागत ice_adminq_opc opc, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (opc != ice_aqc_opc_add_sw_rules &&
	    opc != ice_aqc_opc_update_sw_rules &&
	    opc != ice_aqc_opc_हटाओ_sw_rules)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, opc);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	desc.params.sw_rules.num_rules_fltr_entry_index =
		cpu_to_le16(num_rules);
	status = ice_aq_send_cmd(hw, &desc, rule_list, rule_list_sz, cd);
	अगर (opc != ice_aqc_opc_add_sw_rules &&
	    hw->adminq.sq_last_status == ICE_AQ_RC_ENOENT)
		status = ICE_ERR_DOES_NOT_EXIST;

	वापस status;
पूर्ण

/* ice_init_port_info - Initialize port_info with चयन configuration data
 * @pi: poपूर्णांकer to port_info
 * @vsi_port_num: VSI number or port number
 * @type: Type of चयन element (port or VSI)
 * @swid: चयन ID of the चयन the element is attached to
 * @pf_vf_num: PF or VF number
 * @is_vf: true अगर the element is a VF, false otherwise
 */
अटल व्योम
ice_init_port_info(काष्ठा ice_port_info *pi, u16 vsi_port_num, u8 type,
		   u16 swid, u16 pf_vf_num, bool is_vf)
अणु
	चयन (type) अणु
	हाल ICE_AQC_GET_SW_CONF_RESP_PHYS_PORT:
		pi->lport = (u8)(vsi_port_num & ICE_LPORT_MASK);
		pi->sw_id = swid;
		pi->pf_vf_num = pf_vf_num;
		pi->is_vf = is_vf;
		pi->dflt_tx_vsi_num = ICE_DFLT_VSI_INVAL;
		pi->dflt_rx_vsi_num = ICE_DFLT_VSI_INVAL;
		अवरोध;
	शेष:
		ice_debug(pi->hw, ICE_DBG_SW, "incorrect VSI/port type received\n");
		अवरोध;
	पूर्ण
पूर्ण

/* ice_get_initial_sw_cfg - Get initial port and शेष VSI data
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
क्रमागत ice_status ice_get_initial_sw_cfg(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aqc_get_sw_cfg_resp_elem *rbuf;
	क्रमागत ice_status status;
	u16 req_desc = 0;
	u16 num_elems;
	u16 i;

	rbuf = devm_kzalloc(ice_hw_to_dev(hw), ICE_SW_CFG_MAX_BUF_LEN,
			    GFP_KERNEL);

	अगर (!rbuf)
		वापस ICE_ERR_NO_MEMORY;

	/* Multiple calls to ice_aq_get_sw_cfg may be required
	 * to get all the चयन configuration inक्रमmation. The need
	 * क्रम additional calls is indicated by ice_aq_get_sw_cfg
	 * writing a non-zero value in req_desc
	 */
	करो अणु
		काष्ठा ice_aqc_get_sw_cfg_resp_elem *ele;

		status = ice_aq_get_sw_cfg(hw, rbuf, ICE_SW_CFG_MAX_BUF_LEN,
					   &req_desc, &num_elems, शून्य);

		अगर (status)
			अवरोध;

		क्रम (i = 0, ele = rbuf; i < num_elems; i++, ele++) अणु
			u16 pf_vf_num, swid, vsi_port_num;
			bool is_vf = false;
			u8 res_type;

			vsi_port_num = le16_to_cpu(ele->vsi_port_num) &
				ICE_AQC_GET_SW_CONF_RESP_VSI_PORT_NUM_M;

			pf_vf_num = le16_to_cpu(ele->pf_vf_num) &
				ICE_AQC_GET_SW_CONF_RESP_FUNC_NUM_M;

			swid = le16_to_cpu(ele->swid);

			अगर (le16_to_cpu(ele->pf_vf_num) &
			    ICE_AQC_GET_SW_CONF_RESP_IS_VF)
				is_vf = true;

			res_type = (u8)(le16_to_cpu(ele->vsi_port_num) >>
					ICE_AQC_GET_SW_CONF_RESP_TYPE_S);

			अगर (res_type == ICE_AQC_GET_SW_CONF_RESP_VSI) अणु
				/* FW VSI is not needed. Just जारी. */
				जारी;
			पूर्ण

			ice_init_port_info(hw->port_info, vsi_port_num,
					   res_type, swid, pf_vf_num, is_vf);
		पूर्ण
	पूर्ण जबतक (req_desc && !status);

	devm_kमुक्त(ice_hw_to_dev(hw), rbuf);
	वापस status;
पूर्ण

/**
 * ice_fill_sw_info - Helper function to populate lb_en and lan_en
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @fi: filter info काष्ठाure to fill/update
 *
 * This helper function populates the lb_en and lan_en elements of the provided
 * ice_fltr_info काष्ठा using the चयन's type and अक्षरacteristics of the
 * चयन rule being configured.
 */
अटल व्योम ice_fill_sw_info(काष्ठा ice_hw *hw, काष्ठा ice_fltr_info *fi)
अणु
	fi->lb_en = false;
	fi->lan_en = false;
	अगर ((fi->flag & ICE_FLTR_TX) &&
	    (fi->fltr_act == ICE_FWD_TO_VSI ||
	     fi->fltr_act == ICE_FWD_TO_VSI_LIST ||
	     fi->fltr_act == ICE_FWD_TO_Q ||
	     fi->fltr_act == ICE_FWD_TO_QGRP)) अणु
		/* Setting LB क्रम prune actions will result in replicated
		 * packets to the पूर्णांकernal चयन that will be dropped.
		 */
		अगर (fi->lkup_type != ICE_SW_LKUP_VLAN)
			fi->lb_en = true;

		/* Set lan_en to TRUE अगर
		 * 1. The चयन is a VEB AND
		 * 2
		 * 2.1 The lookup is a directional lookup like ethertype,
		 * promiscuous, ethertype-MAC, promiscuous-VLAN
		 * and शेष-port OR
		 * 2.2 The lookup is VLAN, OR
		 * 2.3 The lookup is MAC with mcast or bcast addr क्रम MAC, OR
		 * 2.4 The lookup is MAC_VLAN with mcast or bcast addr क्रम MAC.
		 *
		 * OR
		 *
		 * The चयन is a VEPA.
		 *
		 * In all other हालs, the LAN enable has to be set to false.
		 */
		अगर (hw->evb_veb) अणु
			अगर (fi->lkup_type == ICE_SW_LKUP_ETHERTYPE ||
			    fi->lkup_type == ICE_SW_LKUP_PROMISC ||
			    fi->lkup_type == ICE_SW_LKUP_ETHERTYPE_MAC ||
			    fi->lkup_type == ICE_SW_LKUP_PROMISC_VLAN ||
			    fi->lkup_type == ICE_SW_LKUP_DFLT ||
			    fi->lkup_type == ICE_SW_LKUP_VLAN ||
			    (fi->lkup_type == ICE_SW_LKUP_MAC &&
			     !is_unicast_ether_addr(fi->l_data.mac.mac_addr)) ||
			    (fi->lkup_type == ICE_SW_LKUP_MAC_VLAN &&
			     !is_unicast_ether_addr(fi->l_data.mac.mac_addr)))
				fi->lan_en = true;
		पूर्ण अन्यथा अणु
			fi->lan_en = true;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_fill_sw_rule - Helper function to fill चयन rule काष्ठाure
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @f_info: entry containing packet क्रमwarding inक्रमmation
 * @s_rule: चयन rule काष्ठाure to be filled in based on mac_entry
 * @opc: चयन rules population command type - pass in the command opcode
 */
अटल व्योम
ice_fill_sw_rule(काष्ठा ice_hw *hw, काष्ठा ice_fltr_info *f_info,
		 काष्ठा ice_aqc_sw_rules_elem *s_rule, क्रमागत ice_adminq_opc opc)
अणु
	u16 vlan_id = ICE_MAX_VLAN_ID + 1;
	व्योम *daddr = शून्य;
	u16 eth_hdr_sz;
	u8 *eth_hdr;
	u32 act = 0;
	__be16 *off;
	u8 q_rgn;

	अगर (opc == ice_aqc_opc_हटाओ_sw_rules) अणु
		s_rule->pdata.lkup_tx_rx.act = 0;
		s_rule->pdata.lkup_tx_rx.index =
			cpu_to_le16(f_info->fltr_rule_id);
		s_rule->pdata.lkup_tx_rx.hdr_len = 0;
		वापस;
	पूर्ण

	eth_hdr_sz = माप(dummy_eth_header);
	eth_hdr = s_rule->pdata.lkup_tx_rx.hdr;

	/* initialize the ether header with a dummy header */
	स_नकल(eth_hdr, dummy_eth_header, eth_hdr_sz);
	ice_fill_sw_info(hw, f_info);

	चयन (f_info->fltr_act) अणु
	हाल ICE_FWD_TO_VSI:
		act |= (f_info->fwd_id.hw_vsi_id << ICE_SINGLE_ACT_VSI_ID_S) &
			ICE_SINGLE_ACT_VSI_ID_M;
		अगर (f_info->lkup_type != ICE_SW_LKUP_VLAN)
			act |= ICE_SINGLE_ACT_VSI_FORWARDING |
				ICE_SINGLE_ACT_VALID_BIT;
		अवरोध;
	हाल ICE_FWD_TO_VSI_LIST:
		act |= ICE_SINGLE_ACT_VSI_LIST;
		act |= (f_info->fwd_id.vsi_list_id <<
			ICE_SINGLE_ACT_VSI_LIST_ID_S) &
			ICE_SINGLE_ACT_VSI_LIST_ID_M;
		अगर (f_info->lkup_type != ICE_SW_LKUP_VLAN)
			act |= ICE_SINGLE_ACT_VSI_FORWARDING |
				ICE_SINGLE_ACT_VALID_BIT;
		अवरोध;
	हाल ICE_FWD_TO_Q:
		act |= ICE_SINGLE_ACT_TO_Q;
		act |= (f_info->fwd_id.q_id << ICE_SINGLE_ACT_Q_INDEX_S) &
			ICE_SINGLE_ACT_Q_INDEX_M;
		अवरोध;
	हाल ICE_DROP_PACKET:
		act |= ICE_SINGLE_ACT_VSI_FORWARDING | ICE_SINGLE_ACT_DROP |
			ICE_SINGLE_ACT_VALID_BIT;
		अवरोध;
	हाल ICE_FWD_TO_QGRP:
		q_rgn = f_info->qgrp_size > 0 ?
			(u8)ilog2(f_info->qgrp_size) : 0;
		act |= ICE_SINGLE_ACT_TO_Q;
		act |= (f_info->fwd_id.q_id << ICE_SINGLE_ACT_Q_INDEX_S) &
			ICE_SINGLE_ACT_Q_INDEX_M;
		act |= (q_rgn << ICE_SINGLE_ACT_Q_REGION_S) &
			ICE_SINGLE_ACT_Q_REGION_M;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (f_info->lb_en)
		act |= ICE_SINGLE_ACT_LB_ENABLE;
	अगर (f_info->lan_en)
		act |= ICE_SINGLE_ACT_LAN_ENABLE;

	चयन (f_info->lkup_type) अणु
	हाल ICE_SW_LKUP_MAC:
		daddr = f_info->l_data.mac.mac_addr;
		अवरोध;
	हाल ICE_SW_LKUP_VLAN:
		vlan_id = f_info->l_data.vlan.vlan_id;
		अगर (f_info->fltr_act == ICE_FWD_TO_VSI ||
		    f_info->fltr_act == ICE_FWD_TO_VSI_LIST) अणु
			act |= ICE_SINGLE_ACT_PRUNE;
			act |= ICE_SINGLE_ACT_EGRESS | ICE_SINGLE_ACT_INGRESS;
		पूर्ण
		अवरोध;
	हाल ICE_SW_LKUP_ETHERTYPE_MAC:
		daddr = f_info->l_data.ethertype_mac.mac_addr;
		fallthrough;
	हाल ICE_SW_LKUP_ETHERTYPE:
		off = (__क्रमce __be16 *)(eth_hdr + ICE_ETH_ETHTYPE_OFFSET);
		*off = cpu_to_be16(f_info->l_data.ethertype_mac.ethertype);
		अवरोध;
	हाल ICE_SW_LKUP_MAC_VLAN:
		daddr = f_info->l_data.mac_vlan.mac_addr;
		vlan_id = f_info->l_data.mac_vlan.vlan_id;
		अवरोध;
	हाल ICE_SW_LKUP_PROMISC_VLAN:
		vlan_id = f_info->l_data.mac_vlan.vlan_id;
		fallthrough;
	हाल ICE_SW_LKUP_PROMISC:
		daddr = f_info->l_data.mac_vlan.mac_addr;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	s_rule->type = (f_info->flag & ICE_FLTR_RX) ?
		cpu_to_le16(ICE_AQC_SW_RULES_T_LKUP_RX) :
		cpu_to_le16(ICE_AQC_SW_RULES_T_LKUP_TX);

	/* Recipe set depending on lookup type */
	s_rule->pdata.lkup_tx_rx.recipe_id = cpu_to_le16(f_info->lkup_type);
	s_rule->pdata.lkup_tx_rx.src = cpu_to_le16(f_info->src);
	s_rule->pdata.lkup_tx_rx.act = cpu_to_le32(act);

	अगर (daddr)
		ether_addr_copy(eth_hdr + ICE_ETH_DA_OFFSET, daddr);

	अगर (!(vlan_id > ICE_MAX_VLAN_ID)) अणु
		off = (__क्रमce __be16 *)(eth_hdr + ICE_ETH_VLAN_TCI_OFFSET);
		*off = cpu_to_be16(vlan_id);
	पूर्ण

	/* Create the चयन rule with the final dummy Ethernet header */
	अगर (opc != ice_aqc_opc_update_sw_rules)
		s_rule->pdata.lkup_tx_rx.hdr_len = cpu_to_le16(eth_hdr_sz);
पूर्ण

/**
 * ice_add_marker_act
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @m_ent: the management entry क्रम which sw marker needs to be added
 * @sw_marker: sw marker to tag the Rx descriptor with
 * @l_id: large action resource ID
 *
 * Create a large action to hold software marker and update the चयन rule
 * entry poपूर्णांकed by m_ent with newly created large action
 */
अटल क्रमागत ice_status
ice_add_marker_act(काष्ठा ice_hw *hw, काष्ठा ice_fltr_mgmt_list_entry *m_ent,
		   u16 sw_marker, u16 l_id)
अणु
	काष्ठा ice_aqc_sw_rules_elem *lg_act, *rx_tx;
	/* For software marker we need 3 large actions
	 * 1. FWD action: FWD TO VSI or VSI LIST
	 * 2. GENERIC VALUE action to hold the profile ID
	 * 3. GENERIC VALUE action to hold the software marker ID
	 */
	स्थिर u16 num_lg_acts = 3;
	क्रमागत ice_status status;
	u16 lg_act_size;
	u16 rules_size;
	u32 act;
	u16 id;

	अगर (m_ent->fltr_info.lkup_type != ICE_SW_LKUP_MAC)
		वापस ICE_ERR_PARAM;

	/* Create two back-to-back चयन rules and submit them to the HW using
	 * one memory buffer:
	 *    1. Large Action
	 *    2. Look up Tx Rx
	 */
	lg_act_size = (u16)ICE_SW_RULE_LG_ACT_SIZE(num_lg_acts);
	rules_size = lg_act_size + ICE_SW_RULE_RX_TX_ETH_HDR_SIZE;
	lg_act = devm_kzalloc(ice_hw_to_dev(hw), rules_size, GFP_KERNEL);
	अगर (!lg_act)
		वापस ICE_ERR_NO_MEMORY;

	rx_tx = (काष्ठा ice_aqc_sw_rules_elem *)((u8 *)lg_act + lg_act_size);

	/* Fill in the first चयन rule i.e. large action */
	lg_act->type = cpu_to_le16(ICE_AQC_SW_RULES_T_LG_ACT);
	lg_act->pdata.lg_act.index = cpu_to_le16(l_id);
	lg_act->pdata.lg_act.size = cpu_to_le16(num_lg_acts);

	/* First action VSI क्रमwarding or VSI list क्रमwarding depending on how
	 * many VSIs
	 */
	id = (m_ent->vsi_count > 1) ? m_ent->fltr_info.fwd_id.vsi_list_id :
		m_ent->fltr_info.fwd_id.hw_vsi_id;

	act = ICE_LG_ACT_VSI_FORWARDING | ICE_LG_ACT_VALID_BIT;
	act |= (id << ICE_LG_ACT_VSI_LIST_ID_S) & ICE_LG_ACT_VSI_LIST_ID_M;
	अगर (m_ent->vsi_count > 1)
		act |= ICE_LG_ACT_VSI_LIST;
	lg_act->pdata.lg_act.act[0] = cpu_to_le32(act);

	/* Second action descriptor type */
	act = ICE_LG_ACT_GENERIC;

	act |= (1 << ICE_LG_ACT_GENERIC_VALUE_S) & ICE_LG_ACT_GENERIC_VALUE_M;
	lg_act->pdata.lg_act.act[1] = cpu_to_le32(act);

	act = (ICE_LG_ACT_GENERIC_OFF_RX_DESC_PROF_IDX <<
	       ICE_LG_ACT_GENERIC_OFFSET_S) & ICE_LG_ACT_GENERIC_OFFSET_M;

	/* Third action Marker value */
	act |= ICE_LG_ACT_GENERIC;
	act |= (sw_marker << ICE_LG_ACT_GENERIC_VALUE_S) &
		ICE_LG_ACT_GENERIC_VALUE_M;

	lg_act->pdata.lg_act.act[2] = cpu_to_le32(act);

	/* call the fill चयन rule to fill the lookup Tx Rx काष्ठाure */
	ice_fill_sw_rule(hw, &m_ent->fltr_info, rx_tx,
			 ice_aqc_opc_update_sw_rules);

	/* Update the action to poपूर्णांक to the large action ID */
	rx_tx->pdata.lkup_tx_rx.act =
		cpu_to_le32(ICE_SINGLE_ACT_PTR |
			    ((l_id << ICE_SINGLE_ACT_PTR_VAL_S) &
			     ICE_SINGLE_ACT_PTR_VAL_M));

	/* Use the filter rule ID of the previously created rule with single
	 * act. Once the update happens, hardware will treat this as large
	 * action
	 */
	rx_tx->pdata.lkup_tx_rx.index =
		cpu_to_le16(m_ent->fltr_info.fltr_rule_id);

	status = ice_aq_sw_rules(hw, lg_act, rules_size, 2,
				 ice_aqc_opc_update_sw_rules, शून्य);
	अगर (!status) अणु
		m_ent->lg_act_idx = l_id;
		m_ent->sw_marker_id = sw_marker;
	पूर्ण

	devm_kमुक्त(ice_hw_to_dev(hw), lg_act);
	वापस status;
पूर्ण

/**
 * ice_create_vsi_list_map
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle_arr: array of VSI handles to set in the VSI mapping
 * @num_vsi: number of VSI handles in the array
 * @vsi_list_id: VSI list ID generated as part of allocate resource
 *
 * Helper function to create a new entry of VSI list ID to VSI mapping
 * using the given VSI list ID
 */
अटल काष्ठा ice_vsi_list_map_info *
ice_create_vsi_list_map(काष्ठा ice_hw *hw, u16 *vsi_handle_arr, u16 num_vsi,
			u16 vsi_list_id)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_vsi_list_map_info *v_map;
	पूर्णांक i;

	v_map = devm_kzalloc(ice_hw_to_dev(hw), माप(*v_map), GFP_KERNEL);
	अगर (!v_map)
		वापस शून्य;

	v_map->vsi_list_id = vsi_list_id;
	v_map->ref_cnt = 1;
	क्रम (i = 0; i < num_vsi; i++)
		set_bit(vsi_handle_arr[i], v_map->vsi_map);

	list_add(&v_map->list_entry, &sw->vsi_list_map_head);
	वापस v_map;
पूर्ण

/**
 * ice_update_vsi_list_rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle_arr: array of VSI handles to क्रमm a VSI list
 * @num_vsi: number of VSI handles in the array
 * @vsi_list_id: VSI list ID generated as part of allocate resource
 * @हटाओ: Boolean value to indicate अगर this is a हटाओ action
 * @opc: चयन rules population command type - pass in the command opcode
 * @lkup_type: lookup type of the filter
 *
 * Call AQ command to add a new चयन rule or update existing चयन rule
 * using the given VSI list ID
 */
अटल क्रमागत ice_status
ice_update_vsi_list_rule(काष्ठा ice_hw *hw, u16 *vsi_handle_arr, u16 num_vsi,
			 u16 vsi_list_id, bool हटाओ, क्रमागत ice_adminq_opc opc,
			 क्रमागत ice_sw_lkup_type lkup_type)
अणु
	काष्ठा ice_aqc_sw_rules_elem *s_rule;
	क्रमागत ice_status status;
	u16 s_rule_size;
	u16 rule_type;
	पूर्णांक i;

	अगर (!num_vsi)
		वापस ICE_ERR_PARAM;

	अगर (lkup_type == ICE_SW_LKUP_MAC ||
	    lkup_type == ICE_SW_LKUP_MAC_VLAN ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE ||
	    lkup_type == ICE_SW_LKUP_ETHERTYPE_MAC ||
	    lkup_type == ICE_SW_LKUP_PROMISC ||
	    lkup_type == ICE_SW_LKUP_PROMISC_VLAN)
		rule_type = हटाओ ? ICE_AQC_SW_RULES_T_VSI_LIST_CLEAR :
			ICE_AQC_SW_RULES_T_VSI_LIST_SET;
	अन्यथा अगर (lkup_type == ICE_SW_LKUP_VLAN)
		rule_type = हटाओ ? ICE_AQC_SW_RULES_T_PRUNE_LIST_CLEAR :
			ICE_AQC_SW_RULES_T_PRUNE_LIST_SET;
	अन्यथा
		वापस ICE_ERR_PARAM;

	s_rule_size = (u16)ICE_SW_RULE_VSI_LIST_SIZE(num_vsi);
	s_rule = devm_kzalloc(ice_hw_to_dev(hw), s_rule_size, GFP_KERNEL);
	अगर (!s_rule)
		वापस ICE_ERR_NO_MEMORY;
	क्रम (i = 0; i < num_vsi; i++) अणु
		अगर (!ice_is_vsi_valid(hw, vsi_handle_arr[i])) अणु
			status = ICE_ERR_PARAM;
			जाओ निकास;
		पूर्ण
		/* AQ call requires hw_vsi_id(s) */
		s_rule->pdata.vsi_list.vsi[i] =
			cpu_to_le16(ice_get_hw_vsi_num(hw, vsi_handle_arr[i]));
	पूर्ण

	s_rule->type = cpu_to_le16(rule_type);
	s_rule->pdata.vsi_list.number_vsi = cpu_to_le16(num_vsi);
	s_rule->pdata.vsi_list.index = cpu_to_le16(vsi_list_id);

	status = ice_aq_sw_rules(hw, s_rule, s_rule_size, 1, opc, शून्य);

निकास:
	devm_kमुक्त(ice_hw_to_dev(hw), s_rule);
	वापस status;
पूर्ण

/**
 * ice_create_vsi_list_rule - Creates and populates a VSI list rule
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle_arr: array of VSI handles to क्रमm a VSI list
 * @num_vsi: number of VSI handles in the array
 * @vsi_list_id: stores the ID of the VSI list to be created
 * @lkup_type: चयन rule filter's lookup type
 */
अटल क्रमागत ice_status
ice_create_vsi_list_rule(काष्ठा ice_hw *hw, u16 *vsi_handle_arr, u16 num_vsi,
			 u16 *vsi_list_id, क्रमागत ice_sw_lkup_type lkup_type)
अणु
	क्रमागत ice_status status;

	status = ice_aq_alloc_मुक्त_vsi_list(hw, vsi_list_id, lkup_type,
					    ice_aqc_opc_alloc_res);
	अगर (status)
		वापस status;

	/* Update the newly created VSI list to include the specअगरied VSIs */
	वापस ice_update_vsi_list_rule(hw, vsi_handle_arr, num_vsi,
					*vsi_list_id, false,
					ice_aqc_opc_add_sw_rules, lkup_type);
पूर्ण

/**
 * ice_create_pkt_fwd_rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @f_entry: entry containing packet क्रमwarding inक्रमmation
 *
 * Create चयन rule with given filter inक्रमmation and add an entry
 * to the corresponding filter management list to track this चयन rule
 * and VSI mapping
 */
अटल क्रमागत ice_status
ice_create_pkt_fwd_rule(काष्ठा ice_hw *hw,
			काष्ठा ice_fltr_list_entry *f_entry)
अणु
	काष्ठा ice_fltr_mgmt_list_entry *fm_entry;
	काष्ठा ice_aqc_sw_rules_elem *s_rule;
	क्रमागत ice_sw_lkup_type l_type;
	काष्ठा ice_sw_recipe *recp;
	क्रमागत ice_status status;

	s_rule = devm_kzalloc(ice_hw_to_dev(hw),
			      ICE_SW_RULE_RX_TX_ETH_HDR_SIZE, GFP_KERNEL);
	अगर (!s_rule)
		वापस ICE_ERR_NO_MEMORY;
	fm_entry = devm_kzalloc(ice_hw_to_dev(hw), माप(*fm_entry),
				GFP_KERNEL);
	अगर (!fm_entry) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ ice_create_pkt_fwd_rule_निकास;
	पूर्ण

	fm_entry->fltr_info = f_entry->fltr_info;

	/* Initialize all the fields क्रम the management entry */
	fm_entry->vsi_count = 1;
	fm_entry->lg_act_idx = ICE_INVAL_LG_ACT_INDEX;
	fm_entry->sw_marker_id = ICE_INVAL_SW_MARKER_ID;
	fm_entry->counter_index = ICE_INVAL_COUNTER_ID;

	ice_fill_sw_rule(hw, &fm_entry->fltr_info, s_rule,
			 ice_aqc_opc_add_sw_rules);

	status = ice_aq_sw_rules(hw, s_rule, ICE_SW_RULE_RX_TX_ETH_HDR_SIZE, 1,
				 ice_aqc_opc_add_sw_rules, शून्य);
	अगर (status) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), fm_entry);
		जाओ ice_create_pkt_fwd_rule_निकास;
	पूर्ण

	f_entry->fltr_info.fltr_rule_id =
		le16_to_cpu(s_rule->pdata.lkup_tx_rx.index);
	fm_entry->fltr_info.fltr_rule_id =
		le16_to_cpu(s_rule->pdata.lkup_tx_rx.index);

	/* The book keeping entries will get हटाओd when base driver
	 * calls हटाओ filter AQ command
	 */
	l_type = fm_entry->fltr_info.lkup_type;
	recp = &hw->चयन_info->recp_list[l_type];
	list_add(&fm_entry->list_entry, &recp->filt_rules);

ice_create_pkt_fwd_rule_निकास:
	devm_kमुक्त(ice_hw_to_dev(hw), s_rule);
	वापस status;
पूर्ण

/**
 * ice_update_pkt_fwd_rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @f_info: filter inक्रमmation क्रम चयन rule
 *
 * Call AQ command to update a previously created चयन rule with a
 * VSI list ID
 */
अटल क्रमागत ice_status
ice_update_pkt_fwd_rule(काष्ठा ice_hw *hw, काष्ठा ice_fltr_info *f_info)
अणु
	काष्ठा ice_aqc_sw_rules_elem *s_rule;
	क्रमागत ice_status status;

	s_rule = devm_kzalloc(ice_hw_to_dev(hw),
			      ICE_SW_RULE_RX_TX_ETH_HDR_SIZE, GFP_KERNEL);
	अगर (!s_rule)
		वापस ICE_ERR_NO_MEMORY;

	ice_fill_sw_rule(hw, f_info, s_rule, ice_aqc_opc_update_sw_rules);

	s_rule->pdata.lkup_tx_rx.index = cpu_to_le16(f_info->fltr_rule_id);

	/* Update चयन rule with new rule set to क्रमward VSI list */
	status = ice_aq_sw_rules(hw, s_rule, ICE_SW_RULE_RX_TX_ETH_HDR_SIZE, 1,
				 ice_aqc_opc_update_sw_rules, शून्य);

	devm_kमुक्त(ice_hw_to_dev(hw), s_rule);
	वापस status;
पूर्ण

/**
 * ice_update_sw_rule_bridge_mode
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Updates unicast चयन filter rules based on VEB/VEPA mode
 */
क्रमागत ice_status ice_update_sw_rule_bridge_mode(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_mgmt_list_entry *fm_entry;
	क्रमागत ice_status status = 0;
	काष्ठा list_head *rule_head;
	काष्ठा mutex *rule_lock; /* Lock to protect filter rule list */

	rule_lock = &sw->recp_list[ICE_SW_LKUP_MAC].filt_rule_lock;
	rule_head = &sw->recp_list[ICE_SW_LKUP_MAC].filt_rules;

	mutex_lock(rule_lock);
	list_क्रम_each_entry(fm_entry, rule_head, list_entry) अणु
		काष्ठा ice_fltr_info *fi = &fm_entry->fltr_info;
		u8 *addr = fi->l_data.mac.mac_addr;

		/* Update unicast Tx rules to reflect the selected
		 * VEB/VEPA mode
		 */
		अगर ((fi->flag & ICE_FLTR_TX) && is_unicast_ether_addr(addr) &&
		    (fi->fltr_act == ICE_FWD_TO_VSI ||
		     fi->fltr_act == ICE_FWD_TO_VSI_LIST ||
		     fi->fltr_act == ICE_FWD_TO_Q ||
		     fi->fltr_act == ICE_FWD_TO_QGRP)) अणु
			status = ice_update_pkt_fwd_rule(hw, fi);
			अगर (status)
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(rule_lock);

	वापस status;
पूर्ण

/**
 * ice_add_update_vsi_list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @m_entry: poपूर्णांकer to current filter management list entry
 * @cur_fltr: filter inक्रमmation from the book keeping entry
 * @new_fltr: filter inक्रमmation with the new VSI to be added
 *
 * Call AQ command to add or update previously created VSI list with new VSI.
 *
 * Helper function to करो book keeping associated with adding filter inक्रमmation
 * The algorithm to करो the book keeping is described below :
 * When a VSI needs to subscribe to a given filter (MAC/VLAN/Ethtype etc.)
 *	अगर only one VSI has been added till now
 *		Allocate a new VSI list and add two VSIs
 *		to this list using चयन rule command
 *		Update the previously created चयन rule with the
 *		newly created VSI list ID
 *	अगर a VSI list was previously created
 *		Add the new VSI to the previously created VSI list set
 *		using the update चयन rule command
 */
अटल क्रमागत ice_status
ice_add_update_vsi_list(काष्ठा ice_hw *hw,
			काष्ठा ice_fltr_mgmt_list_entry *m_entry,
			काष्ठा ice_fltr_info *cur_fltr,
			काष्ठा ice_fltr_info *new_fltr)
अणु
	क्रमागत ice_status status = 0;
	u16 vsi_list_id = 0;

	अगर ((cur_fltr->fltr_act == ICE_FWD_TO_Q ||
	     cur_fltr->fltr_act == ICE_FWD_TO_QGRP))
		वापस ICE_ERR_NOT_IMPL;

	अगर ((new_fltr->fltr_act == ICE_FWD_TO_Q ||
	     new_fltr->fltr_act == ICE_FWD_TO_QGRP) &&
	    (cur_fltr->fltr_act == ICE_FWD_TO_VSI ||
	     cur_fltr->fltr_act == ICE_FWD_TO_VSI_LIST))
		वापस ICE_ERR_NOT_IMPL;

	अगर (m_entry->vsi_count < 2 && !m_entry->vsi_list_info) अणु
		/* Only one entry existed in the mapping and it was not alपढ़ोy
		 * a part of a VSI list. So, create a VSI list with the old and
		 * new VSIs.
		 */
		काष्ठा ice_fltr_info पंचांगp_fltr;
		u16 vsi_handle_arr[2];

		/* A rule alपढ़ोy exists with the new VSI being added */
		अगर (cur_fltr->fwd_id.hw_vsi_id == new_fltr->fwd_id.hw_vsi_id)
			वापस ICE_ERR_ALREADY_EXISTS;

		vsi_handle_arr[0] = cur_fltr->vsi_handle;
		vsi_handle_arr[1] = new_fltr->vsi_handle;
		status = ice_create_vsi_list_rule(hw, &vsi_handle_arr[0], 2,
						  &vsi_list_id,
						  new_fltr->lkup_type);
		अगर (status)
			वापस status;

		पंचांगp_fltr = *new_fltr;
		पंचांगp_fltr.fltr_rule_id = cur_fltr->fltr_rule_id;
		पंचांगp_fltr.fltr_act = ICE_FWD_TO_VSI_LIST;
		पंचांगp_fltr.fwd_id.vsi_list_id = vsi_list_id;
		/* Update the previous चयन rule of "MAC forward to VSI" to
		 * "MAC fwd to VSI list"
		 */
		status = ice_update_pkt_fwd_rule(hw, &पंचांगp_fltr);
		अगर (status)
			वापस status;

		cur_fltr->fwd_id.vsi_list_id = vsi_list_id;
		cur_fltr->fltr_act = ICE_FWD_TO_VSI_LIST;
		m_entry->vsi_list_info =
			ice_create_vsi_list_map(hw, &vsi_handle_arr[0], 2,
						vsi_list_id);

		अगर (!m_entry->vsi_list_info)
			वापस ICE_ERR_NO_MEMORY;

		/* If this entry was large action then the large action needs
		 * to be updated to poपूर्णांक to FWD to VSI list
		 */
		अगर (m_entry->sw_marker_id != ICE_INVAL_SW_MARKER_ID)
			status =
			    ice_add_marker_act(hw, m_entry,
					       m_entry->sw_marker_id,
					       m_entry->lg_act_idx);
	पूर्ण अन्यथा अणु
		u16 vsi_handle = new_fltr->vsi_handle;
		क्रमागत ice_adminq_opc opcode;

		अगर (!m_entry->vsi_list_info)
			वापस ICE_ERR_CFG;

		/* A rule alपढ़ोy exists with the new VSI being added */
		अगर (test_bit(vsi_handle, m_entry->vsi_list_info->vsi_map))
			वापस 0;

		/* Update the previously created VSI list set with
		 * the new VSI ID passed in
		 */
		vsi_list_id = cur_fltr->fwd_id.vsi_list_id;
		opcode = ice_aqc_opc_update_sw_rules;

		status = ice_update_vsi_list_rule(hw, &vsi_handle, 1,
						  vsi_list_id, false, opcode,
						  new_fltr->lkup_type);
		/* update VSI list mapping info with new VSI ID */
		अगर (!status)
			set_bit(vsi_handle, m_entry->vsi_list_info->vsi_map);
	पूर्ण
	अगर (!status)
		m_entry->vsi_count++;
	वापस status;
पूर्ण

/**
 * ice_find_rule_entry - Search a rule entry
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @recp_id: lookup type क्रम which the specअगरied rule needs to be searched
 * @f_info: rule inक्रमmation
 *
 * Helper function to search क्रम a given rule entry
 * Returns poपूर्णांकer to entry storing the rule अगर found
 */
अटल काष्ठा ice_fltr_mgmt_list_entry *
ice_find_rule_entry(काष्ठा ice_hw *hw, u8 recp_id, काष्ठा ice_fltr_info *f_info)
अणु
	काष्ठा ice_fltr_mgmt_list_entry *list_itr, *ret = शून्य;
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा list_head *list_head;

	list_head = &sw->recp_list[recp_id].filt_rules;
	list_क्रम_each_entry(list_itr, list_head, list_entry) अणु
		अगर (!स_भेद(&f_info->l_data, &list_itr->fltr_info.l_data,
			    माप(f_info->l_data)) &&
		    f_info->flag == list_itr->fltr_info.flag) अणु
			ret = list_itr;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ice_find_vsi_list_entry - Search VSI list map with VSI count 1
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @recp_id: lookup type क्रम which VSI lists needs to be searched
 * @vsi_handle: VSI handle to be found in VSI list
 * @vsi_list_id: VSI list ID found containing vsi_handle
 *
 * Helper function to search a VSI list with single entry containing given VSI
 * handle element. This can be extended further to search VSI list with more
 * than 1 vsi_count. Returns poपूर्णांकer to VSI list entry अगर found.
 */
अटल काष्ठा ice_vsi_list_map_info *
ice_find_vsi_list_entry(काष्ठा ice_hw *hw, u8 recp_id, u16 vsi_handle,
			u16 *vsi_list_id)
अणु
	काष्ठा ice_vsi_list_map_info *map_info = शून्य;
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_mgmt_list_entry *list_itr;
	काष्ठा list_head *list_head;

	list_head = &sw->recp_list[recp_id].filt_rules;
	list_क्रम_each_entry(list_itr, list_head, list_entry) अणु
		अगर (list_itr->vsi_count == 1 && list_itr->vsi_list_info) अणु
			map_info = list_itr->vsi_list_info;
			अगर (test_bit(vsi_handle, map_info->vsi_map)) अणु
				*vsi_list_id = map_info->vsi_list_id;
				वापस map_info;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * ice_add_rule_पूर्णांकernal - add rule क्रम a given lookup type
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @recp_id: lookup type (recipe ID) क्रम which rule has to be added
 * @f_entry: काष्ठाure containing MAC क्रमwarding inक्रमmation
 *
 * Adds or updates the rule lists क्रम a given recipe
 */
अटल क्रमागत ice_status
ice_add_rule_पूर्णांकernal(काष्ठा ice_hw *hw, u8 recp_id,
		      काष्ठा ice_fltr_list_entry *f_entry)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_info *new_fltr, *cur_fltr;
	काष्ठा ice_fltr_mgmt_list_entry *m_entry;
	काष्ठा mutex *rule_lock; /* Lock to protect filter rule list */
	क्रमागत ice_status status = 0;

	अगर (!ice_is_vsi_valid(hw, f_entry->fltr_info.vsi_handle))
		वापस ICE_ERR_PARAM;
	f_entry->fltr_info.fwd_id.hw_vsi_id =
		ice_get_hw_vsi_num(hw, f_entry->fltr_info.vsi_handle);

	rule_lock = &sw->recp_list[recp_id].filt_rule_lock;

	mutex_lock(rule_lock);
	new_fltr = &f_entry->fltr_info;
	अगर (new_fltr->flag & ICE_FLTR_RX)
		new_fltr->src = hw->port_info->lport;
	अन्यथा अगर (new_fltr->flag & ICE_FLTR_TX)
		new_fltr->src = f_entry->fltr_info.fwd_id.hw_vsi_id;

	m_entry = ice_find_rule_entry(hw, recp_id, new_fltr);
	अगर (!m_entry) अणु
		mutex_unlock(rule_lock);
		वापस ice_create_pkt_fwd_rule(hw, f_entry);
	पूर्ण

	cur_fltr = &m_entry->fltr_info;
	status = ice_add_update_vsi_list(hw, m_entry, cur_fltr, new_fltr);
	mutex_unlock(rule_lock);

	वापस status;
पूर्ण

/**
 * ice_हटाओ_vsi_list_rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_list_id: VSI list ID generated as part of allocate resource
 * @lkup_type: चयन rule filter lookup type
 *
 * The VSI list should be emptied beक्रमe this function is called to हटाओ the
 * VSI list.
 */
अटल क्रमागत ice_status
ice_हटाओ_vsi_list_rule(काष्ठा ice_hw *hw, u16 vsi_list_id,
			 क्रमागत ice_sw_lkup_type lkup_type)
अणु
	काष्ठा ice_aqc_sw_rules_elem *s_rule;
	क्रमागत ice_status status;
	u16 s_rule_size;

	s_rule_size = (u16)ICE_SW_RULE_VSI_LIST_SIZE(0);
	s_rule = devm_kzalloc(ice_hw_to_dev(hw), s_rule_size, GFP_KERNEL);
	अगर (!s_rule)
		वापस ICE_ERR_NO_MEMORY;

	s_rule->type = cpu_to_le16(ICE_AQC_SW_RULES_T_VSI_LIST_CLEAR);
	s_rule->pdata.vsi_list.index = cpu_to_le16(vsi_list_id);

	/* Free the vsi_list resource that we allocated. It is assumed that the
	 * list is empty at this poपूर्णांक.
	 */
	status = ice_aq_alloc_मुक्त_vsi_list(hw, &vsi_list_id, lkup_type,
					    ice_aqc_opc_मुक्त_res);

	devm_kमुक्त(ice_hw_to_dev(hw), s_rule);
	वापस status;
पूर्ण

/**
 * ice_rem_update_vsi_list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle of the VSI to हटाओ
 * @fm_list: filter management entry क्रम which the VSI list management needs to
 *           be करोne
 */
अटल क्रमागत ice_status
ice_rem_update_vsi_list(काष्ठा ice_hw *hw, u16 vsi_handle,
			काष्ठा ice_fltr_mgmt_list_entry *fm_list)
अणु
	क्रमागत ice_sw_lkup_type lkup_type;
	क्रमागत ice_status status = 0;
	u16 vsi_list_id;

	अगर (fm_list->fltr_info.fltr_act != ICE_FWD_TO_VSI_LIST ||
	    fm_list->vsi_count == 0)
		वापस ICE_ERR_PARAM;

	/* A rule with the VSI being हटाओd करोes not exist */
	अगर (!test_bit(vsi_handle, fm_list->vsi_list_info->vsi_map))
		वापस ICE_ERR_DOES_NOT_EXIST;

	lkup_type = fm_list->fltr_info.lkup_type;
	vsi_list_id = fm_list->fltr_info.fwd_id.vsi_list_id;
	status = ice_update_vsi_list_rule(hw, &vsi_handle, 1, vsi_list_id, true,
					  ice_aqc_opc_update_sw_rules,
					  lkup_type);
	अगर (status)
		वापस status;

	fm_list->vsi_count--;
	clear_bit(vsi_handle, fm_list->vsi_list_info->vsi_map);

	अगर (fm_list->vsi_count == 1 && lkup_type != ICE_SW_LKUP_VLAN) अणु
		काष्ठा ice_fltr_info पंचांगp_fltr_info = fm_list->fltr_info;
		काष्ठा ice_vsi_list_map_info *vsi_list_info =
			fm_list->vsi_list_info;
		u16 rem_vsi_handle;

		rem_vsi_handle = find_first_bit(vsi_list_info->vsi_map,
						ICE_MAX_VSI);
		अगर (!ice_is_vsi_valid(hw, rem_vsi_handle))
			वापस ICE_ERR_OUT_OF_RANGE;

		/* Make sure VSI list is empty beक्रमe removing it below */
		status = ice_update_vsi_list_rule(hw, &rem_vsi_handle, 1,
						  vsi_list_id, true,
						  ice_aqc_opc_update_sw_rules,
						  lkup_type);
		अगर (status)
			वापस status;

		पंचांगp_fltr_info.fltr_act = ICE_FWD_TO_VSI;
		पंचांगp_fltr_info.fwd_id.hw_vsi_id =
			ice_get_hw_vsi_num(hw, rem_vsi_handle);
		पंचांगp_fltr_info.vsi_handle = rem_vsi_handle;
		status = ice_update_pkt_fwd_rule(hw, &पंचांगp_fltr_info);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_SW, "Failed to update pkt fwd rule to FWD_TO_VSI on HW VSI %d, error %d\n",
				  पंचांगp_fltr_info.fwd_id.hw_vsi_id, status);
			वापस status;
		पूर्ण

		fm_list->fltr_info = पंचांगp_fltr_info;
	पूर्ण

	अगर ((fm_list->vsi_count == 1 && lkup_type != ICE_SW_LKUP_VLAN) ||
	    (fm_list->vsi_count == 0 && lkup_type == ICE_SW_LKUP_VLAN)) अणु
		काष्ठा ice_vsi_list_map_info *vsi_list_info =
			fm_list->vsi_list_info;

		/* Remove the VSI list since it is no दीर्घer used */
		status = ice_हटाओ_vsi_list_rule(hw, vsi_list_id, lkup_type);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_SW, "Failed to remove VSI list %d, error %d\n",
				  vsi_list_id, status);
			वापस status;
		पूर्ण

		list_del(&vsi_list_info->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), vsi_list_info);
		fm_list->vsi_list_info = शून्य;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_हटाओ_rule_पूर्णांकernal - Remove a filter rule of a given type
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @recp_id: recipe ID क्रम which the rule needs to हटाओd
 * @f_entry: rule entry containing filter inक्रमmation
 */
अटल क्रमागत ice_status
ice_हटाओ_rule_पूर्णांकernal(काष्ठा ice_hw *hw, u8 recp_id,
			 काष्ठा ice_fltr_list_entry *f_entry)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_mgmt_list_entry *list_elem;
	काष्ठा mutex *rule_lock; /* Lock to protect filter rule list */
	क्रमागत ice_status status = 0;
	bool हटाओ_rule = false;
	u16 vsi_handle;

	अगर (!ice_is_vsi_valid(hw, f_entry->fltr_info.vsi_handle))
		वापस ICE_ERR_PARAM;
	f_entry->fltr_info.fwd_id.hw_vsi_id =
		ice_get_hw_vsi_num(hw, f_entry->fltr_info.vsi_handle);

	rule_lock = &sw->recp_list[recp_id].filt_rule_lock;
	mutex_lock(rule_lock);
	list_elem = ice_find_rule_entry(hw, recp_id, &f_entry->fltr_info);
	अगर (!list_elem) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ निकास;
	पूर्ण

	अगर (list_elem->fltr_info.fltr_act != ICE_FWD_TO_VSI_LIST) अणु
		हटाओ_rule = true;
	पूर्ण अन्यथा अगर (!list_elem->vsi_list_info) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ निकास;
	पूर्ण अन्यथा अगर (list_elem->vsi_list_info->ref_cnt > 1) अणु
		/* a ref_cnt > 1 indicates that the vsi_list is being
		 * shared by multiple rules. Decrement the ref_cnt and
		 * हटाओ this rule, but करो not modअगरy the list, as it
		 * is in-use by other rules.
		 */
		list_elem->vsi_list_info->ref_cnt--;
		हटाओ_rule = true;
	पूर्ण अन्यथा अणु
		/* a ref_cnt of 1 indicates the vsi_list is only used
		 * by one rule. However, the original removal request is only
		 * क्रम a single VSI. Update the vsi_list first, and only
		 * हटाओ the rule अगर there are no further VSIs in this list.
		 */
		vsi_handle = f_entry->fltr_info.vsi_handle;
		status = ice_rem_update_vsi_list(hw, vsi_handle, list_elem);
		अगर (status)
			जाओ निकास;
		/* अगर VSI count goes to zero after updating the VSI list */
		अगर (list_elem->vsi_count == 0)
			हटाओ_rule = true;
	पूर्ण

	अगर (हटाओ_rule) अणु
		/* Remove the lookup rule */
		काष्ठा ice_aqc_sw_rules_elem *s_rule;

		s_rule = devm_kzalloc(ice_hw_to_dev(hw),
				      ICE_SW_RULE_RX_TX_NO_HDR_SIZE,
				      GFP_KERNEL);
		अगर (!s_rule) अणु
			status = ICE_ERR_NO_MEMORY;
			जाओ निकास;
		पूर्ण

		ice_fill_sw_rule(hw, &list_elem->fltr_info, s_rule,
				 ice_aqc_opc_हटाओ_sw_rules);

		status = ice_aq_sw_rules(hw, s_rule,
					 ICE_SW_RULE_RX_TX_NO_HDR_SIZE, 1,
					 ice_aqc_opc_हटाओ_sw_rules, शून्य);

		/* Remove a book keeping from the list */
		devm_kमुक्त(ice_hw_to_dev(hw), s_rule);

		अगर (status)
			जाओ निकास;

		list_del(&list_elem->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), list_elem);
	पूर्ण
निकास:
	mutex_unlock(rule_lock);
	वापस status;
पूर्ण

/**
 * ice_add_mac - Add a MAC address based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @m_list: list of MAC addresses and क्रमwarding inक्रमmation
 *
 * IMPORTANT: When the ucast_shared flag is set to false and m_list has
 * multiple unicast addresses, the function assumes that all the
 * addresses are unique in a given add_mac call. It करोesn't
 * check क्रम duplicates in this हाल, removing duplicates from a given
 * list should be taken care of in the caller of this function.
 */
क्रमागत ice_status ice_add_mac(काष्ठा ice_hw *hw, काष्ठा list_head *m_list)
अणु
	काष्ठा ice_aqc_sw_rules_elem *s_rule, *r_iter;
	काष्ठा ice_fltr_list_entry *m_list_itr;
	काष्ठा list_head *rule_head;
	u16 total_elem_left, s_rule_size;
	काष्ठा ice_चयन_info *sw;
	काष्ठा mutex *rule_lock; /* Lock to protect filter rule list */
	क्रमागत ice_status status = 0;
	u16 num_unicast = 0;
	u8 elem_sent;

	अगर (!m_list || !hw)
		वापस ICE_ERR_PARAM;

	s_rule = शून्य;
	sw = hw->चयन_info;
	rule_lock = &sw->recp_list[ICE_SW_LKUP_MAC].filt_rule_lock;
	list_क्रम_each_entry(m_list_itr, m_list, list_entry) अणु
		u8 *add = &m_list_itr->fltr_info.l_data.mac.mac_addr[0];
		u16 vsi_handle;
		u16 hw_vsi_id;

		m_list_itr->fltr_info.flag = ICE_FLTR_TX;
		vsi_handle = m_list_itr->fltr_info.vsi_handle;
		अगर (!ice_is_vsi_valid(hw, vsi_handle))
			वापस ICE_ERR_PARAM;
		hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);
		m_list_itr->fltr_info.fwd_id.hw_vsi_id = hw_vsi_id;
		/* update the src in हाल it is VSI num */
		अगर (m_list_itr->fltr_info.src_id != ICE_SRC_ID_VSI)
			वापस ICE_ERR_PARAM;
		m_list_itr->fltr_info.src = hw_vsi_id;
		अगर (m_list_itr->fltr_info.lkup_type != ICE_SW_LKUP_MAC ||
		    is_zero_ether_addr(add))
			वापस ICE_ERR_PARAM;
		अगर (is_unicast_ether_addr(add) && !hw->ucast_shared) अणु
			/* Don't overग_लिखो the unicast address */
			mutex_lock(rule_lock);
			अगर (ice_find_rule_entry(hw, ICE_SW_LKUP_MAC,
						&m_list_itr->fltr_info)) अणु
				mutex_unlock(rule_lock);
				वापस ICE_ERR_ALREADY_EXISTS;
			पूर्ण
			mutex_unlock(rule_lock);
			num_unicast++;
		पूर्ण अन्यथा अगर (is_multicast_ether_addr(add) ||
			   (is_unicast_ether_addr(add) && hw->ucast_shared)) अणु
			m_list_itr->status =
				ice_add_rule_पूर्णांकernal(hw, ICE_SW_LKUP_MAC,
						      m_list_itr);
			अगर (m_list_itr->status)
				वापस m_list_itr->status;
		पूर्ण
	पूर्ण

	mutex_lock(rule_lock);
	/* Exit अगर no suitable entries were found क्रम adding bulk चयन rule */
	अगर (!num_unicast) अणु
		status = 0;
		जाओ ice_add_mac_निकास;
	पूर्ण

	rule_head = &sw->recp_list[ICE_SW_LKUP_MAC].filt_rules;

	/* Allocate चयन rule buffer क्रम the bulk update क्रम unicast */
	s_rule_size = ICE_SW_RULE_RX_TX_ETH_HDR_SIZE;
	s_rule = devm_kसुस्मृति(ice_hw_to_dev(hw), num_unicast, s_rule_size,
			      GFP_KERNEL);
	अगर (!s_rule) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ ice_add_mac_निकास;
	पूर्ण

	r_iter = s_rule;
	list_क्रम_each_entry(m_list_itr, m_list, list_entry) अणु
		काष्ठा ice_fltr_info *f_info = &m_list_itr->fltr_info;
		u8 *mac_addr = &f_info->l_data.mac.mac_addr[0];

		अगर (is_unicast_ether_addr(mac_addr)) अणु
			ice_fill_sw_rule(hw, &m_list_itr->fltr_info, r_iter,
					 ice_aqc_opc_add_sw_rules);
			r_iter = (काष्ठा ice_aqc_sw_rules_elem *)
				((u8 *)r_iter + s_rule_size);
		पूर्ण
	पूर्ण

	/* Call AQ bulk चयन rule update क्रम all unicast addresses */
	r_iter = s_rule;
	/* Call AQ चयन rule in AQ_MAX chunk */
	क्रम (total_elem_left = num_unicast; total_elem_left > 0;
	     total_elem_left -= elem_sent) अणु
		काष्ठा ice_aqc_sw_rules_elem *entry = r_iter;

		elem_sent = min_t(u8, total_elem_left,
				  (ICE_AQ_MAX_BUF_LEN / s_rule_size));
		status = ice_aq_sw_rules(hw, entry, elem_sent * s_rule_size,
					 elem_sent, ice_aqc_opc_add_sw_rules,
					 शून्य);
		अगर (status)
			जाओ ice_add_mac_निकास;
		r_iter = (काष्ठा ice_aqc_sw_rules_elem *)
			((u8 *)r_iter + (elem_sent * s_rule_size));
	पूर्ण

	/* Fill up rule ID based on the value वापसed from FW */
	r_iter = s_rule;
	list_क्रम_each_entry(m_list_itr, m_list, list_entry) अणु
		काष्ठा ice_fltr_info *f_info = &m_list_itr->fltr_info;
		u8 *mac_addr = &f_info->l_data.mac.mac_addr[0];
		काष्ठा ice_fltr_mgmt_list_entry *fm_entry;

		अगर (is_unicast_ether_addr(mac_addr)) अणु
			f_info->fltr_rule_id =
				le16_to_cpu(r_iter->pdata.lkup_tx_rx.index);
			f_info->fltr_act = ICE_FWD_TO_VSI;
			/* Create an entry to track this MAC address */
			fm_entry = devm_kzalloc(ice_hw_to_dev(hw),
						माप(*fm_entry), GFP_KERNEL);
			अगर (!fm_entry) अणु
				status = ICE_ERR_NO_MEMORY;
				जाओ ice_add_mac_निकास;
			पूर्ण
			fm_entry->fltr_info = *f_info;
			fm_entry->vsi_count = 1;
			/* The book keeping entries will get हटाओd when
			 * base driver calls हटाओ filter AQ command
			 */

			list_add(&fm_entry->list_entry, rule_head);
			r_iter = (काष्ठा ice_aqc_sw_rules_elem *)
				((u8 *)r_iter + s_rule_size);
		पूर्ण
	पूर्ण

ice_add_mac_निकास:
	mutex_unlock(rule_lock);
	अगर (s_rule)
		devm_kमुक्त(ice_hw_to_dev(hw), s_rule);
	वापस status;
पूर्ण

/**
 * ice_add_vlan_पूर्णांकernal - Add one VLAN based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @f_entry: filter entry containing one VLAN inक्रमmation
 */
अटल क्रमागत ice_status
ice_add_vlan_पूर्णांकernal(काष्ठा ice_hw *hw, काष्ठा ice_fltr_list_entry *f_entry)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_mgmt_list_entry *v_list_itr;
	काष्ठा ice_fltr_info *new_fltr, *cur_fltr;
	क्रमागत ice_sw_lkup_type lkup_type;
	u16 vsi_list_id = 0, vsi_handle;
	काष्ठा mutex *rule_lock; /* Lock to protect filter rule list */
	क्रमागत ice_status status = 0;

	अगर (!ice_is_vsi_valid(hw, f_entry->fltr_info.vsi_handle))
		वापस ICE_ERR_PARAM;

	f_entry->fltr_info.fwd_id.hw_vsi_id =
		ice_get_hw_vsi_num(hw, f_entry->fltr_info.vsi_handle);
	new_fltr = &f_entry->fltr_info;

	/* VLAN ID should only be 12 bits */
	अगर (new_fltr->l_data.vlan.vlan_id > ICE_MAX_VLAN_ID)
		वापस ICE_ERR_PARAM;

	अगर (new_fltr->src_id != ICE_SRC_ID_VSI)
		वापस ICE_ERR_PARAM;

	new_fltr->src = new_fltr->fwd_id.hw_vsi_id;
	lkup_type = new_fltr->lkup_type;
	vsi_handle = new_fltr->vsi_handle;
	rule_lock = &sw->recp_list[ICE_SW_LKUP_VLAN].filt_rule_lock;
	mutex_lock(rule_lock);
	v_list_itr = ice_find_rule_entry(hw, ICE_SW_LKUP_VLAN, new_fltr);
	अगर (!v_list_itr) अणु
		काष्ठा ice_vsi_list_map_info *map_info = शून्य;

		अगर (new_fltr->fltr_act == ICE_FWD_TO_VSI) अणु
			/* All VLAN pruning rules use a VSI list. Check अगर
			 * there is alपढ़ोy a VSI list containing VSI that we
			 * want to add. If found, use the same vsi_list_id क्रम
			 * this new VLAN rule or अन्यथा create a new list.
			 */
			map_info = ice_find_vsi_list_entry(hw, ICE_SW_LKUP_VLAN,
							   vsi_handle,
							   &vsi_list_id);
			अगर (!map_info) अणु
				status = ice_create_vsi_list_rule(hw,
								  &vsi_handle,
								  1,
								  &vsi_list_id,
								  lkup_type);
				अगर (status)
					जाओ निकास;
			पूर्ण
			/* Convert the action to क्रमwarding to a VSI list. */
			new_fltr->fltr_act = ICE_FWD_TO_VSI_LIST;
			new_fltr->fwd_id.vsi_list_id = vsi_list_id;
		पूर्ण

		status = ice_create_pkt_fwd_rule(hw, f_entry);
		अगर (!status) अणु
			v_list_itr = ice_find_rule_entry(hw, ICE_SW_LKUP_VLAN,
							 new_fltr);
			अगर (!v_list_itr) अणु
				status = ICE_ERR_DOES_NOT_EXIST;
				जाओ निकास;
			पूर्ण
			/* reuse VSI list क्रम new rule and increment ref_cnt */
			अगर (map_info) अणु
				v_list_itr->vsi_list_info = map_info;
				map_info->ref_cnt++;
			पूर्ण अन्यथा अणु
				v_list_itr->vsi_list_info =
					ice_create_vsi_list_map(hw, &vsi_handle,
								1, vsi_list_id);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (v_list_itr->vsi_list_info->ref_cnt == 1) अणु
		/* Update existing VSI list to add new VSI ID only अगर it used
		 * by one VLAN rule.
		 */
		cur_fltr = &v_list_itr->fltr_info;
		status = ice_add_update_vsi_list(hw, v_list_itr, cur_fltr,
						 new_fltr);
	पूर्ण अन्यथा अणु
		/* If VLAN rule exists and VSI list being used by this rule is
		 * referenced by more than 1 VLAN rule. Then create a new VSI
		 * list appending previous VSI with new VSI and update existing
		 * VLAN rule to poपूर्णांक to new VSI list ID
		 */
		काष्ठा ice_fltr_info पंचांगp_fltr;
		u16 vsi_handle_arr[2];
		u16 cur_handle;

		/* Current implementation only supports reusing VSI list with
		 * one VSI count. We should never hit below condition
		 */
		अगर (v_list_itr->vsi_count > 1 &&
		    v_list_itr->vsi_list_info->ref_cnt > 1) अणु
			ice_debug(hw, ICE_DBG_SW, "Invalid configuration: Optimization to reuse VSI list with more than one VSI is not being done yet\n");
			status = ICE_ERR_CFG;
			जाओ निकास;
		पूर्ण

		cur_handle =
			find_first_bit(v_list_itr->vsi_list_info->vsi_map,
				       ICE_MAX_VSI);

		/* A rule alपढ़ोy exists with the new VSI being added */
		अगर (cur_handle == vsi_handle) अणु
			status = ICE_ERR_ALREADY_EXISTS;
			जाओ निकास;
		पूर्ण

		vsi_handle_arr[0] = cur_handle;
		vsi_handle_arr[1] = vsi_handle;
		status = ice_create_vsi_list_rule(hw, &vsi_handle_arr[0], 2,
						  &vsi_list_id, lkup_type);
		अगर (status)
			जाओ निकास;

		पंचांगp_fltr = v_list_itr->fltr_info;
		पंचांगp_fltr.fltr_rule_id = v_list_itr->fltr_info.fltr_rule_id;
		पंचांगp_fltr.fwd_id.vsi_list_id = vsi_list_id;
		पंचांगp_fltr.fltr_act = ICE_FWD_TO_VSI_LIST;
		/* Update the previous चयन rule to a new VSI list which
		 * includes current VSI that is requested
		 */
		status = ice_update_pkt_fwd_rule(hw, &पंचांगp_fltr);
		अगर (status)
			जाओ निकास;

		/* beक्रमe overriding VSI list map info. decrement ref_cnt of
		 * previous VSI list
		 */
		v_list_itr->vsi_list_info->ref_cnt--;

		/* now update to newly created list */
		v_list_itr->fltr_info.fwd_id.vsi_list_id = vsi_list_id;
		v_list_itr->vsi_list_info =
			ice_create_vsi_list_map(hw, &vsi_handle_arr[0], 2,
						vsi_list_id);
		v_list_itr->vsi_count++;
	पूर्ण

निकास:
	mutex_unlock(rule_lock);
	वापस status;
पूर्ण

/**
 * ice_add_vlan - Add VLAN based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @v_list: list of VLAN entries and क्रमwarding inक्रमmation
 */
क्रमागत ice_status ice_add_vlan(काष्ठा ice_hw *hw, काष्ठा list_head *v_list)
अणु
	काष्ठा ice_fltr_list_entry *v_list_itr;

	अगर (!v_list || !hw)
		वापस ICE_ERR_PARAM;

	list_क्रम_each_entry(v_list_itr, v_list, list_entry) अणु
		अगर (v_list_itr->fltr_info.lkup_type != ICE_SW_LKUP_VLAN)
			वापस ICE_ERR_PARAM;
		v_list_itr->fltr_info.flag = ICE_FLTR_TX;
		v_list_itr->status = ice_add_vlan_पूर्णांकernal(hw, v_list_itr);
		अगर (v_list_itr->status)
			वापस v_list_itr->status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_add_eth_mac - Add ethertype and MAC based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @em_list: list of ether type MAC filter, MAC is optional
 *
 * This function requires the caller to populate the entries in
 * the filter list with the necessary fields (including flags to
 * indicate Tx or Rx rules).
 */
क्रमागत ice_status
ice_add_eth_mac(काष्ठा ice_hw *hw, काष्ठा list_head *em_list)
अणु
	काष्ठा ice_fltr_list_entry *em_list_itr;

	अगर (!em_list || !hw)
		वापस ICE_ERR_PARAM;

	list_क्रम_each_entry(em_list_itr, em_list, list_entry) अणु
		क्रमागत ice_sw_lkup_type l_type =
			em_list_itr->fltr_info.lkup_type;

		अगर (l_type != ICE_SW_LKUP_ETHERTYPE_MAC &&
		    l_type != ICE_SW_LKUP_ETHERTYPE)
			वापस ICE_ERR_PARAM;

		em_list_itr->status = ice_add_rule_पूर्णांकernal(hw, l_type,
							    em_list_itr);
		अगर (em_list_itr->status)
			वापस em_list_itr->status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_हटाओ_eth_mac - Remove an ethertype (or MAC) based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @em_list: list of ethertype or ethertype MAC entries
 */
क्रमागत ice_status
ice_हटाओ_eth_mac(काष्ठा ice_hw *hw, काष्ठा list_head *em_list)
अणु
	काष्ठा ice_fltr_list_entry *em_list_itr, *पंचांगp;

	अगर (!em_list || !hw)
		वापस ICE_ERR_PARAM;

	list_क्रम_each_entry_safe(em_list_itr, पंचांगp, em_list, list_entry) अणु
		क्रमागत ice_sw_lkup_type l_type =
			em_list_itr->fltr_info.lkup_type;

		अगर (l_type != ICE_SW_LKUP_ETHERTYPE_MAC &&
		    l_type != ICE_SW_LKUP_ETHERTYPE)
			वापस ICE_ERR_PARAM;

		em_list_itr->status = ice_हटाओ_rule_पूर्णांकernal(hw, l_type,
							       em_list_itr);
		अगर (em_list_itr->status)
			वापस em_list_itr->status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_rem_sw_rule_info
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @rule_head: poपूर्णांकer to the चयन list काष्ठाure that we want to delete
 */
अटल व्योम
ice_rem_sw_rule_info(काष्ठा ice_hw *hw, काष्ठा list_head *rule_head)
अणु
	अगर (!list_empty(rule_head)) अणु
		काष्ठा ice_fltr_mgmt_list_entry *entry;
		काष्ठा ice_fltr_mgmt_list_entry *पंचांगp;

		list_क्रम_each_entry_safe(entry, पंचांगp, rule_head, list_entry) अणु
			list_del(&entry->list_entry);
			devm_kमुक्त(ice_hw_to_dev(hw), entry);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_cfg_dflt_vsi - change state of VSI to set/clear शेष
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to set as शेष
 * @set: true to add the above mentioned चयन rule, false to हटाओ it
 * @direction: ICE_FLTR_RX or ICE_FLTR_TX
 *
 * add filter rule to set/unset given VSI as शेष VSI क्रम the चयन
 * (represented by swid)
 */
क्रमागत ice_status
ice_cfg_dflt_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, bool set, u8 direction)
अणु
	काष्ठा ice_aqc_sw_rules_elem *s_rule;
	काष्ठा ice_fltr_info f_info;
	क्रमागत ice_adminq_opc opcode;
	क्रमागत ice_status status;
	u16 s_rule_size;
	u16 hw_vsi_id;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	s_rule_size = set ? ICE_SW_RULE_RX_TX_ETH_HDR_SIZE :
		ICE_SW_RULE_RX_TX_NO_HDR_SIZE;

	s_rule = devm_kzalloc(ice_hw_to_dev(hw), s_rule_size, GFP_KERNEL);
	अगर (!s_rule)
		वापस ICE_ERR_NO_MEMORY;

	स_रखो(&f_info, 0, माप(f_info));

	f_info.lkup_type = ICE_SW_LKUP_DFLT;
	f_info.flag = direction;
	f_info.fltr_act = ICE_FWD_TO_VSI;
	f_info.fwd_id.hw_vsi_id = hw_vsi_id;

	अगर (f_info.flag & ICE_FLTR_RX) अणु
		f_info.src = hw->port_info->lport;
		f_info.src_id = ICE_SRC_ID_LPORT;
		अगर (!set)
			f_info.fltr_rule_id =
				hw->port_info->dflt_rx_vsi_rule_id;
	पूर्ण अन्यथा अगर (f_info.flag & ICE_FLTR_TX) अणु
		f_info.src_id = ICE_SRC_ID_VSI;
		f_info.src = hw_vsi_id;
		अगर (!set)
			f_info.fltr_rule_id =
				hw->port_info->dflt_tx_vsi_rule_id;
	पूर्ण

	अगर (set)
		opcode = ice_aqc_opc_add_sw_rules;
	अन्यथा
		opcode = ice_aqc_opc_हटाओ_sw_rules;

	ice_fill_sw_rule(hw, &f_info, s_rule, opcode);

	status = ice_aq_sw_rules(hw, s_rule, s_rule_size, 1, opcode, शून्य);
	अगर (status || !(f_info.flag & ICE_FLTR_TX_RX))
		जाओ out;
	अगर (set) अणु
		u16 index = le16_to_cpu(s_rule->pdata.lkup_tx_rx.index);

		अगर (f_info.flag & ICE_FLTR_TX) अणु
			hw->port_info->dflt_tx_vsi_num = hw_vsi_id;
			hw->port_info->dflt_tx_vsi_rule_id = index;
		पूर्ण अन्यथा अगर (f_info.flag & ICE_FLTR_RX) अणु
			hw->port_info->dflt_rx_vsi_num = hw_vsi_id;
			hw->port_info->dflt_rx_vsi_rule_id = index;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (f_info.flag & ICE_FLTR_TX) अणु
			hw->port_info->dflt_tx_vsi_num = ICE_DFLT_VSI_INVAL;
			hw->port_info->dflt_tx_vsi_rule_id = ICE_INVAL_ACT;
		पूर्ण अन्यथा अगर (f_info.flag & ICE_FLTR_RX) अणु
			hw->port_info->dflt_rx_vsi_num = ICE_DFLT_VSI_INVAL;
			hw->port_info->dflt_rx_vsi_rule_id = ICE_INVAL_ACT;
		पूर्ण
	पूर्ण

out:
	devm_kमुक्त(ice_hw_to_dev(hw), s_rule);
	वापस status;
पूर्ण

/**
 * ice_find_ucast_rule_entry - Search क्रम a unicast MAC filter rule entry
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @recp_id: lookup type क्रम which the specअगरied rule needs to be searched
 * @f_info: rule inक्रमmation
 *
 * Helper function to search क्रम a unicast rule entry - this is to be used
 * to हटाओ unicast MAC filter that is not shared with other VSIs on the
 * PF चयन.
 *
 * Returns poपूर्णांकer to entry storing the rule अगर found
 */
अटल काष्ठा ice_fltr_mgmt_list_entry *
ice_find_ucast_rule_entry(काष्ठा ice_hw *hw, u8 recp_id,
			  काष्ठा ice_fltr_info *f_info)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_mgmt_list_entry *list_itr;
	काष्ठा list_head *list_head;

	list_head = &sw->recp_list[recp_id].filt_rules;
	list_क्रम_each_entry(list_itr, list_head, list_entry) अणु
		अगर (!स_भेद(&f_info->l_data, &list_itr->fltr_info.l_data,
			    माप(f_info->l_data)) &&
		    f_info->fwd_id.hw_vsi_id ==
		    list_itr->fltr_info.fwd_id.hw_vsi_id &&
		    f_info->flag == list_itr->fltr_info.flag)
			वापस list_itr;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * ice_हटाओ_mac - हटाओ a MAC address based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @m_list: list of MAC addresses and क्रमwarding inक्रमmation
 *
 * This function हटाओs either a MAC filter rule or a specअगरic VSI from a
 * VSI list क्रम a multicast MAC address.
 *
 * Returns ICE_ERR_DOES_NOT_EXIST अगर a given entry was not added by
 * ice_add_mac. Caller should be aware that this call will only work अगर all
 * the entries passed पूर्णांकo m_list were added previously. It will not attempt to
 * करो a partial हटाओ of entries that were found.
 */
क्रमागत ice_status ice_हटाओ_mac(काष्ठा ice_hw *hw, काष्ठा list_head *m_list)
अणु
	काष्ठा ice_fltr_list_entry *list_itr, *पंचांगp;
	काष्ठा mutex *rule_lock; /* Lock to protect filter rule list */

	अगर (!m_list)
		वापस ICE_ERR_PARAM;

	rule_lock = &hw->चयन_info->recp_list[ICE_SW_LKUP_MAC].filt_rule_lock;
	list_क्रम_each_entry_safe(list_itr, पंचांगp, m_list, list_entry) अणु
		क्रमागत ice_sw_lkup_type l_type = list_itr->fltr_info.lkup_type;
		u8 *add = &list_itr->fltr_info.l_data.mac.mac_addr[0];
		u16 vsi_handle;

		अगर (l_type != ICE_SW_LKUP_MAC)
			वापस ICE_ERR_PARAM;

		vsi_handle = list_itr->fltr_info.vsi_handle;
		अगर (!ice_is_vsi_valid(hw, vsi_handle))
			वापस ICE_ERR_PARAM;

		list_itr->fltr_info.fwd_id.hw_vsi_id =
					ice_get_hw_vsi_num(hw, vsi_handle);
		अगर (is_unicast_ether_addr(add) && !hw->ucast_shared) अणु
			/* Don't हटाओ the unicast address that beदीर्घs to
			 * another VSI on the चयन, since it is not being
			 * shared...
			 */
			mutex_lock(rule_lock);
			अगर (!ice_find_ucast_rule_entry(hw, ICE_SW_LKUP_MAC,
						       &list_itr->fltr_info)) अणु
				mutex_unlock(rule_lock);
				वापस ICE_ERR_DOES_NOT_EXIST;
			पूर्ण
			mutex_unlock(rule_lock);
		पूर्ण
		list_itr->status = ice_हटाओ_rule_पूर्णांकernal(hw,
							    ICE_SW_LKUP_MAC,
							    list_itr);
		अगर (list_itr->status)
			वापस list_itr->status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_हटाओ_vlan - Remove VLAN based filter rule
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @v_list: list of VLAN entries and क्रमwarding inक्रमmation
 */
क्रमागत ice_status
ice_हटाओ_vlan(काष्ठा ice_hw *hw, काष्ठा list_head *v_list)
अणु
	काष्ठा ice_fltr_list_entry *v_list_itr, *पंचांगp;

	अगर (!v_list || !hw)
		वापस ICE_ERR_PARAM;

	list_क्रम_each_entry_safe(v_list_itr, पंचांगp, v_list, list_entry) अणु
		क्रमागत ice_sw_lkup_type l_type = v_list_itr->fltr_info.lkup_type;

		अगर (l_type != ICE_SW_LKUP_VLAN)
			वापस ICE_ERR_PARAM;
		v_list_itr->status = ice_हटाओ_rule_पूर्णांकernal(hw,
							      ICE_SW_LKUP_VLAN,
							      v_list_itr);
		अगर (v_list_itr->status)
			वापस v_list_itr->status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_vsi_uses_fltr - Determine अगर given VSI uses specअगरied filter
 * @fm_entry: filter entry to inspect
 * @vsi_handle: VSI handle to compare with filter info
 */
अटल bool
ice_vsi_uses_fltr(काष्ठा ice_fltr_mgmt_list_entry *fm_entry, u16 vsi_handle)
अणु
	वापस ((fm_entry->fltr_info.fltr_act == ICE_FWD_TO_VSI &&
		 fm_entry->fltr_info.vsi_handle == vsi_handle) ||
		(fm_entry->fltr_info.fltr_act == ICE_FWD_TO_VSI_LIST &&
		 fm_entry->vsi_list_info &&
		 (test_bit(vsi_handle, fm_entry->vsi_list_info->vsi_map))));
पूर्ण

/**
 * ice_add_entry_to_vsi_fltr_list - Add copy of fltr_list_entry to हटाओ list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to हटाओ filters from
 * @vsi_list_head: poपूर्णांकer to the list to add entry to
 * @fi: poपूर्णांकer to fltr_info of filter entry to copy & add
 *
 * Helper function, used when creating a list of filters to हटाओ from
 * a specअगरic VSI. The entry added to vsi_list_head is a COPY of the
 * original filter entry, with the exception of fltr_info.fltr_act and
 * fltr_info.fwd_id fields. These are set such that later logic can
 * extract which VSI to हटाओ the fltr from, and pass on that inक्रमmation.
 */
अटल क्रमागत ice_status
ice_add_entry_to_vsi_fltr_list(काष्ठा ice_hw *hw, u16 vsi_handle,
			       काष्ठा list_head *vsi_list_head,
			       काष्ठा ice_fltr_info *fi)
अणु
	काष्ठा ice_fltr_list_entry *पंचांगp;

	/* this memory is मुक्तd up in the caller function
	 * once filters क्रम this VSI are हटाओd
	 */
	पंचांगp = devm_kzalloc(ice_hw_to_dev(hw), माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस ICE_ERR_NO_MEMORY;

	पंचांगp->fltr_info = *fi;

	/* Overग_लिखो these fields to indicate which VSI to हटाओ filter from,
	 * so find and हटाओ logic can extract the inक्रमmation from the
	 * list entries. Note that original entries will still have proper
	 * values.
	 */
	पंचांगp->fltr_info.fltr_act = ICE_FWD_TO_VSI;
	पंचांगp->fltr_info.vsi_handle = vsi_handle;
	पंचांगp->fltr_info.fwd_id.hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	list_add(&पंचांगp->list_entry, vsi_list_head);

	वापस 0;
पूर्ण

/**
 * ice_add_to_vsi_fltr_list - Add VSI filters to the list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to हटाओ filters from
 * @lkup_list_head: poपूर्णांकer to the list that has certain lookup type filters
 * @vsi_list_head: poपूर्णांकer to the list pertaining to VSI with vsi_handle
 *
 * Locates all filters in lkup_list_head that are used by the given VSI,
 * and adds COPIES of those entries to vsi_list_head (पूर्णांकended to be used
 * to हटाओ the listed filters).
 * Note that this means all entries in vsi_list_head must be explicitly
 * deallocated by the caller when करोne with list.
 */
अटल क्रमागत ice_status
ice_add_to_vsi_fltr_list(काष्ठा ice_hw *hw, u16 vsi_handle,
			 काष्ठा list_head *lkup_list_head,
			 काष्ठा list_head *vsi_list_head)
अणु
	काष्ठा ice_fltr_mgmt_list_entry *fm_entry;
	क्रमागत ice_status status = 0;

	/* check to make sure VSI ID is valid and within boundary */
	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	list_क्रम_each_entry(fm_entry, lkup_list_head, list_entry) अणु
		अगर (!ice_vsi_uses_fltr(fm_entry, vsi_handle))
			जारी;

		status = ice_add_entry_to_vsi_fltr_list(hw, vsi_handle,
							vsi_list_head,
							&fm_entry->fltr_info);
		अगर (status)
			वापस status;
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_determine_promisc_mask
 * @fi: filter info to parse
 *
 * Helper function to determine which ICE_PROMISC_ mask corresponds
 * to given filter पूर्णांकo.
 */
अटल u8 ice_determine_promisc_mask(काष्ठा ice_fltr_info *fi)
अणु
	u16 vid = fi->l_data.mac_vlan.vlan_id;
	u8 *macaddr = fi->l_data.mac.mac_addr;
	bool is_tx_fltr = false;
	u8 promisc_mask = 0;

	अगर (fi->flag == ICE_FLTR_TX)
		is_tx_fltr = true;

	अगर (is_broadcast_ether_addr(macaddr))
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_BCAST_TX : ICE_PROMISC_BCAST_RX;
	अन्यथा अगर (is_multicast_ether_addr(macaddr))
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_MCAST_TX : ICE_PROMISC_MCAST_RX;
	अन्यथा अगर (is_unicast_ether_addr(macaddr))
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_UCAST_TX : ICE_PROMISC_UCAST_RX;
	अगर (vid)
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_VLAN_TX : ICE_PROMISC_VLAN_RX;

	वापस promisc_mask;
पूर्ण

/**
 * ice_हटाओ_promisc - Remove promisc based filter rules
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @recp_id: recipe ID क्रम which the rule needs to हटाओd
 * @v_list: list of promisc entries
 */
अटल क्रमागत ice_status
ice_हटाओ_promisc(काष्ठा ice_hw *hw, u8 recp_id,
		   काष्ठा list_head *v_list)
अणु
	काष्ठा ice_fltr_list_entry *v_list_itr, *पंचांगp;

	list_क्रम_each_entry_safe(v_list_itr, पंचांगp, v_list, list_entry) अणु
		v_list_itr->status =
			ice_हटाओ_rule_पूर्णांकernal(hw, recp_id, v_list_itr);
		अगर (v_list_itr->status)
			वापस v_list_itr->status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_clear_vsi_promisc - clear specअगरied promiscuous mode(s) क्रम given VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to clear mode
 * @promisc_mask: mask of promiscuous config bits to clear
 * @vid: VLAN ID to clear VLAN promiscuous
 */
क्रमागत ice_status
ice_clear_vsi_promisc(काष्ठा ice_hw *hw, u16 vsi_handle, u8 promisc_mask,
		      u16 vid)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_list_entry *fm_entry, *पंचांगp;
	काष्ठा list_head हटाओ_list_head;
	काष्ठा ice_fltr_mgmt_list_entry *itr;
	काष्ठा list_head *rule_head;
	काष्ठा mutex *rule_lock;	/* Lock to protect filter rule list */
	क्रमागत ice_status status = 0;
	u8 recipe_id;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	अगर (promisc_mask & (ICE_PROMISC_VLAN_RX | ICE_PROMISC_VLAN_TX))
		recipe_id = ICE_SW_LKUP_PROMISC_VLAN;
	अन्यथा
		recipe_id = ICE_SW_LKUP_PROMISC;

	rule_head = &sw->recp_list[recipe_id].filt_rules;
	rule_lock = &sw->recp_list[recipe_id].filt_rule_lock;

	INIT_LIST_HEAD(&हटाओ_list_head);

	mutex_lock(rule_lock);
	list_क्रम_each_entry(itr, rule_head, list_entry) अणु
		काष्ठा ice_fltr_info *fltr_info;
		u8 fltr_promisc_mask = 0;

		अगर (!ice_vsi_uses_fltr(itr, vsi_handle))
			जारी;
		fltr_info = &itr->fltr_info;

		अगर (recipe_id == ICE_SW_LKUP_PROMISC_VLAN &&
		    vid != fltr_info->l_data.mac_vlan.vlan_id)
			जारी;

		fltr_promisc_mask |= ice_determine_promisc_mask(fltr_info);

		/* Skip अगर filter is not completely specअगरied by given mask */
		अगर (fltr_promisc_mask & ~promisc_mask)
			जारी;

		status = ice_add_entry_to_vsi_fltr_list(hw, vsi_handle,
							&हटाओ_list_head,
							fltr_info);
		अगर (status) अणु
			mutex_unlock(rule_lock);
			जाओ मुक्त_fltr_list;
		पूर्ण
	पूर्ण
	mutex_unlock(rule_lock);

	status = ice_हटाओ_promisc(hw, recipe_id, &हटाओ_list_head);

मुक्त_fltr_list:
	list_क्रम_each_entry_safe(fm_entry, पंचांगp, &हटाओ_list_head, list_entry) अणु
		list_del(&fm_entry->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), fm_entry);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_set_vsi_promisc - set given VSI to given promiscuous mode(s)
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to configure
 * @promisc_mask: mask of promiscuous config bits
 * @vid: VLAN ID to set VLAN promiscuous
 */
क्रमागत ice_status
ice_set_vsi_promisc(काष्ठा ice_hw *hw, u16 vsi_handle, u8 promisc_mask, u16 vid)
अणु
	क्रमागत अणु UCAST_FLTR = 1, MCAST_FLTR, BCAST_FLTR पूर्ण;
	काष्ठा ice_fltr_list_entry f_list_entry;
	काष्ठा ice_fltr_info new_fltr;
	क्रमागत ice_status status = 0;
	bool is_tx_fltr;
	u16 hw_vsi_id;
	पूर्णांक pkt_type;
	u8 recipe_id;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	स_रखो(&new_fltr, 0, माप(new_fltr));

	अगर (promisc_mask & (ICE_PROMISC_VLAN_RX | ICE_PROMISC_VLAN_TX)) अणु
		new_fltr.lkup_type = ICE_SW_LKUP_PROMISC_VLAN;
		new_fltr.l_data.mac_vlan.vlan_id = vid;
		recipe_id = ICE_SW_LKUP_PROMISC_VLAN;
	पूर्ण अन्यथा अणु
		new_fltr.lkup_type = ICE_SW_LKUP_PROMISC;
		recipe_id = ICE_SW_LKUP_PROMISC;
	पूर्ण

	/* Separate filters must be set क्रम each direction/packet type
	 * combination, so we will loop over the mask value, store the
	 * inभागidual type, and clear it out in the input mask as it
	 * is found.
	 */
	जबतक (promisc_mask) अणु
		u8 *mac_addr;

		pkt_type = 0;
		is_tx_fltr = false;

		अगर (promisc_mask & ICE_PROMISC_UCAST_RX) अणु
			promisc_mask &= ~ICE_PROMISC_UCAST_RX;
			pkt_type = UCAST_FLTR;
		पूर्ण अन्यथा अगर (promisc_mask & ICE_PROMISC_UCAST_TX) अणु
			promisc_mask &= ~ICE_PROMISC_UCAST_TX;
			pkt_type = UCAST_FLTR;
			is_tx_fltr = true;
		पूर्ण अन्यथा अगर (promisc_mask & ICE_PROMISC_MCAST_RX) अणु
			promisc_mask &= ~ICE_PROMISC_MCAST_RX;
			pkt_type = MCAST_FLTR;
		पूर्ण अन्यथा अगर (promisc_mask & ICE_PROMISC_MCAST_TX) अणु
			promisc_mask &= ~ICE_PROMISC_MCAST_TX;
			pkt_type = MCAST_FLTR;
			is_tx_fltr = true;
		पूर्ण अन्यथा अगर (promisc_mask & ICE_PROMISC_BCAST_RX) अणु
			promisc_mask &= ~ICE_PROMISC_BCAST_RX;
			pkt_type = BCAST_FLTR;
		पूर्ण अन्यथा अगर (promisc_mask & ICE_PROMISC_BCAST_TX) अणु
			promisc_mask &= ~ICE_PROMISC_BCAST_TX;
			pkt_type = BCAST_FLTR;
			is_tx_fltr = true;
		पूर्ण

		/* Check क्रम VLAN promiscuous flag */
		अगर (promisc_mask & ICE_PROMISC_VLAN_RX) अणु
			promisc_mask &= ~ICE_PROMISC_VLAN_RX;
		पूर्ण अन्यथा अगर (promisc_mask & ICE_PROMISC_VLAN_TX) अणु
			promisc_mask &= ~ICE_PROMISC_VLAN_TX;
			is_tx_fltr = true;
		पूर्ण

		/* Set filter DA based on packet type */
		mac_addr = new_fltr.l_data.mac.mac_addr;
		अगर (pkt_type == BCAST_FLTR) अणु
			eth_broadcast_addr(mac_addr);
		पूर्ण अन्यथा अगर (pkt_type == MCAST_FLTR ||
			   pkt_type == UCAST_FLTR) अणु
			/* Use the dummy ether header DA */
			ether_addr_copy(mac_addr, dummy_eth_header);
			अगर (pkt_type == MCAST_FLTR)
				mac_addr[0] |= 0x1;	/* Set multicast bit */
		पूर्ण

		/* Need to reset this to zero क्रम all iterations */
		new_fltr.flag = 0;
		अगर (is_tx_fltr) अणु
			new_fltr.flag |= ICE_FLTR_TX;
			new_fltr.src = hw_vsi_id;
		पूर्ण अन्यथा अणु
			new_fltr.flag |= ICE_FLTR_RX;
			new_fltr.src = hw->port_info->lport;
		पूर्ण

		new_fltr.fltr_act = ICE_FWD_TO_VSI;
		new_fltr.vsi_handle = vsi_handle;
		new_fltr.fwd_id.hw_vsi_id = hw_vsi_id;
		f_list_entry.fltr_info = new_fltr;

		status = ice_add_rule_पूर्णांकernal(hw, recipe_id, &f_list_entry);
		अगर (status)
			जाओ set_promisc_निकास;
	पूर्ण

set_promisc_निकास:
	वापस status;
पूर्ण

/**
 * ice_set_vlan_vsi_promisc
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to configure
 * @promisc_mask: mask of promiscuous config bits
 * @rm_vlan_promisc: Clear VLANs VSI promisc mode
 *
 * Configure VSI with all associated VLANs to given promiscuous mode(s)
 */
क्रमागत ice_status
ice_set_vlan_vsi_promisc(काष्ठा ice_hw *hw, u16 vsi_handle, u8 promisc_mask,
			 bool rm_vlan_promisc)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_list_entry *list_itr, *पंचांगp;
	काष्ठा list_head vsi_list_head;
	काष्ठा list_head *vlan_head;
	काष्ठा mutex *vlan_lock; /* Lock to protect filter rule list */
	क्रमागत ice_status status;
	u16 vlan_id;

	INIT_LIST_HEAD(&vsi_list_head);
	vlan_lock = &sw->recp_list[ICE_SW_LKUP_VLAN].filt_rule_lock;
	vlan_head = &sw->recp_list[ICE_SW_LKUP_VLAN].filt_rules;
	mutex_lock(vlan_lock);
	status = ice_add_to_vsi_fltr_list(hw, vsi_handle, vlan_head,
					  &vsi_list_head);
	mutex_unlock(vlan_lock);
	अगर (status)
		जाओ मुक्त_fltr_list;

	list_क्रम_each_entry(list_itr, &vsi_list_head, list_entry) अणु
		vlan_id = list_itr->fltr_info.l_data.vlan.vlan_id;
		अगर (rm_vlan_promisc)
			status = ice_clear_vsi_promisc(hw, vsi_handle,
						       promisc_mask, vlan_id);
		अन्यथा
			status = ice_set_vsi_promisc(hw, vsi_handle,
						     promisc_mask, vlan_id);
		अगर (status)
			अवरोध;
	पूर्ण

मुक्त_fltr_list:
	list_क्रम_each_entry_safe(list_itr, पंचांगp, &vsi_list_head, list_entry) अणु
		list_del(&list_itr->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), list_itr);
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_हटाओ_vsi_lkup_fltr - Remove lookup type filters क्रम a VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to हटाओ filters from
 * @lkup: चयन rule filter lookup type
 */
अटल व्योम
ice_हटाओ_vsi_lkup_fltr(काष्ठा ice_hw *hw, u16 vsi_handle,
			 क्रमागत ice_sw_lkup_type lkup)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_fltr_list_entry *fm_entry;
	काष्ठा list_head हटाओ_list_head;
	काष्ठा list_head *rule_head;
	काष्ठा ice_fltr_list_entry *पंचांगp;
	काष्ठा mutex *rule_lock;	/* Lock to protect filter rule list */
	क्रमागत ice_status status;

	INIT_LIST_HEAD(&हटाओ_list_head);
	rule_lock = &sw->recp_list[lkup].filt_rule_lock;
	rule_head = &sw->recp_list[lkup].filt_rules;
	mutex_lock(rule_lock);
	status = ice_add_to_vsi_fltr_list(hw, vsi_handle, rule_head,
					  &हटाओ_list_head);
	mutex_unlock(rule_lock);
	अगर (status)
		जाओ मुक्त_fltr_list;

	चयन (lkup) अणु
	हाल ICE_SW_LKUP_MAC:
		ice_हटाओ_mac(hw, &हटाओ_list_head);
		अवरोध;
	हाल ICE_SW_LKUP_VLAN:
		ice_हटाओ_vlan(hw, &हटाओ_list_head);
		अवरोध;
	हाल ICE_SW_LKUP_PROMISC:
	हाल ICE_SW_LKUP_PROMISC_VLAN:
		ice_हटाओ_promisc(hw, lkup, &हटाओ_list_head);
		अवरोध;
	हाल ICE_SW_LKUP_MAC_VLAN:
	हाल ICE_SW_LKUP_ETHERTYPE:
	हाल ICE_SW_LKUP_ETHERTYPE_MAC:
	हाल ICE_SW_LKUP_DFLT:
	हाल ICE_SW_LKUP_LAST:
	शेष:
		ice_debug(hw, ICE_DBG_SW, "Unsupported lookup type %d\n", lkup);
		अवरोध;
	पूर्ण

मुक्त_fltr_list:
	list_क्रम_each_entry_safe(fm_entry, पंचांगp, &हटाओ_list_head, list_entry) अणु
		list_del(&fm_entry->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), fm_entry);
	पूर्ण
पूर्ण

/**
 * ice_हटाओ_vsi_fltr - Remove all filters क्रम a VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: VSI handle to हटाओ filters from
 */
व्योम ice_हटाओ_vsi_fltr(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_MAC);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_MAC_VLAN);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_PROMISC);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_VLAN);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_DFLT);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_ETHERTYPE);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_ETHERTYPE_MAC);
	ice_हटाओ_vsi_lkup_fltr(hw, vsi_handle, ICE_SW_LKUP_PROMISC_VLAN);
पूर्ण

/**
 * ice_alloc_res_cntr - allocating resource counter
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @type: type of resource
 * @alloc_shared: अगर set it is shared अन्यथा dedicated
 * @num_items: number of entries requested क्रम FD resource type
 * @counter_id: counter index वापसed by AQ call
 */
क्रमागत ice_status
ice_alloc_res_cntr(काष्ठा ice_hw *hw, u8 type, u8 alloc_shared, u16 num_items,
		   u16 *counter_id)
अणु
	काष्ठा ice_aqc_alloc_मुक्त_res_elem *buf;
	क्रमागत ice_status status;
	u16 buf_len;

	/* Allocate resource */
	buf_len = काष्ठा_size(buf, elem, 1);
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	buf->num_elems = cpu_to_le16(num_items);
	buf->res_type = cpu_to_le16(((type << ICE_AQC_RES_TYPE_S) &
				      ICE_AQC_RES_TYPE_M) | alloc_shared);

	status = ice_aq_alloc_मुक्त_res(hw, 1, buf, buf_len,
				       ice_aqc_opc_alloc_res, शून्य);
	अगर (status)
		जाओ निकास;

	*counter_id = le16_to_cpu(buf->elem[0].e.sw_resp);

निकास:
	kमुक्त(buf);
	वापस status;
पूर्ण

/**
 * ice_मुक्त_res_cntr - मुक्त resource counter
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @type: type of resource
 * @alloc_shared: अगर set it is shared अन्यथा dedicated
 * @num_items: number of entries to be मुक्तd क्रम FD resource type
 * @counter_id: counter ID resource which needs to be मुक्तd
 */
क्रमागत ice_status
ice_मुक्त_res_cntr(काष्ठा ice_hw *hw, u8 type, u8 alloc_shared, u16 num_items,
		  u16 counter_id)
अणु
	काष्ठा ice_aqc_alloc_मुक्त_res_elem *buf;
	क्रमागत ice_status status;
	u16 buf_len;

	/* Free resource */
	buf_len = काष्ठा_size(buf, elem, 1);
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	buf->num_elems = cpu_to_le16(num_items);
	buf->res_type = cpu_to_le16(((type << ICE_AQC_RES_TYPE_S) &
				      ICE_AQC_RES_TYPE_M) | alloc_shared);
	buf->elem[0].e.sw_resp = cpu_to_le16(counter_id);

	status = ice_aq_alloc_मुक्त_res(hw, 1, buf, buf_len,
				       ice_aqc_opc_मुक्त_res, शून्य);
	अगर (status)
		ice_debug(hw, ICE_DBG_SW, "counter resource could not be freed\n");

	kमुक्त(buf);
	वापस status;
पूर्ण

/**
 * ice_replay_vsi_fltr - Replay filters क्रम requested VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: driver VSI handle
 * @recp_id: Recipe ID क्रम which rules need to be replayed
 * @list_head: list क्रम which filters need to be replayed
 *
 * Replays the filter of recipe recp_id क्रम a VSI represented via vsi_handle.
 * It is required to pass valid VSI handle.
 */
अटल क्रमागत ice_status
ice_replay_vsi_fltr(काष्ठा ice_hw *hw, u16 vsi_handle, u8 recp_id,
		    काष्ठा list_head *list_head)
अणु
	काष्ठा ice_fltr_mgmt_list_entry *itr;
	क्रमागत ice_status status = 0;
	u16 hw_vsi_id;

	अगर (list_empty(list_head))
		वापस status;
	hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	list_क्रम_each_entry(itr, list_head, list_entry) अणु
		काष्ठा ice_fltr_list_entry f_entry;

		f_entry.fltr_info = itr->fltr_info;
		अगर (itr->vsi_count < 2 && recp_id != ICE_SW_LKUP_VLAN &&
		    itr->fltr_info.vsi_handle == vsi_handle) अणु
			/* update the src in हाल it is VSI num */
			अगर (f_entry.fltr_info.src_id == ICE_SRC_ID_VSI)
				f_entry.fltr_info.src = hw_vsi_id;
			status = ice_add_rule_पूर्णांकernal(hw, recp_id, &f_entry);
			अगर (status)
				जाओ end;
			जारी;
		पूर्ण
		अगर (!itr->vsi_list_info ||
		    !test_bit(vsi_handle, itr->vsi_list_info->vsi_map))
			जारी;
		/* Clearing it so that the logic can add it back */
		clear_bit(vsi_handle, itr->vsi_list_info->vsi_map);
		f_entry.fltr_info.vsi_handle = vsi_handle;
		f_entry.fltr_info.fltr_act = ICE_FWD_TO_VSI;
		/* update the src in हाल it is VSI num */
		अगर (f_entry.fltr_info.src_id == ICE_SRC_ID_VSI)
			f_entry.fltr_info.src = hw_vsi_id;
		अगर (recp_id == ICE_SW_LKUP_VLAN)
			status = ice_add_vlan_पूर्णांकernal(hw, &f_entry);
		अन्यथा
			status = ice_add_rule_पूर्णांकernal(hw, recp_id, &f_entry);
		अगर (status)
			जाओ end;
	पूर्ण
end:
	वापस status;
पूर्ण

/**
 * ice_replay_vsi_all_fltr - replay all filters stored in bookkeeping lists
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: driver VSI handle
 *
 * Replays filters क्रम requested VSI via vsi_handle.
 */
क्रमागत ice_status ice_replay_vsi_all_fltr(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	क्रमागत ice_status status = 0;
	u8 i;

	क्रम (i = 0; i < ICE_SW_LKUP_LAST; i++) अणु
		काष्ठा list_head *head;

		head = &sw->recp_list[i].filt_replay_rules;
		status = ice_replay_vsi_fltr(hw, vsi_handle, i, head);
		अगर (status)
			वापस status;
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_rm_all_sw_replay_rule_info - deletes filter replay rules
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Deletes the filter replay rules.
 */
व्योम ice_rm_all_sw_replay_rule_info(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	u8 i;

	अगर (!sw)
		वापस;

	क्रम (i = 0; i < ICE_SW_LKUP_LAST; i++) अणु
		अगर (!list_empty(&sw->recp_list[i].filt_replay_rules)) अणु
			काष्ठा list_head *l_head;

			l_head = &sw->recp_list[i].filt_replay_rules;
			ice_rem_sw_rule_info(hw, l_head);
		पूर्ण
	पूर्ण
पूर्ण
