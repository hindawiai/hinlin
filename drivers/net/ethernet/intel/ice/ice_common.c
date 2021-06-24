<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice_common.h"
#समावेश "ice_sched.h"
#समावेश "ice_adminq_cmd.h"
#समावेश "ice_flow.h"

#घोषणा ICE_PF_RESET_WAIT_COUNT	300

/**
 * ice_set_mac_type - Sets MAC type
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function sets the MAC type of the adapter based on the
 * venकरोr ID and device ID stored in the HW काष्ठाure.
 */
अटल क्रमागत ice_status ice_set_mac_type(काष्ठा ice_hw *hw)
अणु
	अगर (hw->venकरोr_id != PCI_VENDOR_ID_INTEL)
		वापस ICE_ERR_DEVICE_NOT_SUPPORTED;

	चयन (hw->device_id) अणु
	हाल ICE_DEV_ID_E810C_BACKPLANE:
	हाल ICE_DEV_ID_E810C_QSFP:
	हाल ICE_DEV_ID_E810C_SFP:
	हाल ICE_DEV_ID_E810_XXV_SFP:
		hw->mac_type = ICE_MAC_E810;
		अवरोध;
	हाल ICE_DEV_ID_E823C_10G_BASE_T:
	हाल ICE_DEV_ID_E823C_BACKPLANE:
	हाल ICE_DEV_ID_E823C_QSFP:
	हाल ICE_DEV_ID_E823C_SFP:
	हाल ICE_DEV_ID_E823C_SGMII:
	हाल ICE_DEV_ID_E822C_10G_BASE_T:
	हाल ICE_DEV_ID_E822C_BACKPLANE:
	हाल ICE_DEV_ID_E822C_QSFP:
	हाल ICE_DEV_ID_E822C_SFP:
	हाल ICE_DEV_ID_E822C_SGMII:
	हाल ICE_DEV_ID_E822L_10G_BASE_T:
	हाल ICE_DEV_ID_E822L_BACKPLANE:
	हाल ICE_DEV_ID_E822L_SFP:
	हाल ICE_DEV_ID_E822L_SGMII:
	हाल ICE_DEV_ID_E823L_10G_BASE_T:
	हाल ICE_DEV_ID_E823L_1GBE:
	हाल ICE_DEV_ID_E823L_BACKPLANE:
	हाल ICE_DEV_ID_E823L_QSFP:
	हाल ICE_DEV_ID_E823L_SFP:
		hw->mac_type = ICE_MAC_GENERIC;
		अवरोध;
	शेष:
		hw->mac_type = ICE_MAC_UNKNOWN;
		अवरोध;
	पूर्ण

	ice_debug(hw, ICE_DBG_INIT, "mac_type: %d\n", hw->mac_type);
	वापस 0;
पूर्ण

/**
 * ice_clear_pf_cfg - Clear PF configuration
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Clears any existing PF configuration (VSIs, VSI lists, चयन rules, port
 * configuration, flow director filters, etc.).
 */
क्रमागत ice_status ice_clear_pf_cfg(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_clear_pf_cfg);

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
पूर्ण

/**
 * ice_aq_manage_mac_पढ़ो - manage MAC address पढ़ो command
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @buf: a भव buffer to hold the manage MAC पढ़ो response
 * @buf_size: Size of the भव buffer
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This function is used to वापस per PF station MAC address (0x0107).
 * NOTE: Upon successful completion of this command, MAC address inक्रमmation
 * is वापसed in user specअगरied buffer. Please पूर्णांकerpret user specअगरied
 * buffer as "manage_mac_read" response.
 * Response such as various MAC addresses are stored in HW काष्ठा (port.mac)
 * ice_discover_dev_caps is expected to be called beक्रमe this function is
 * called.
 */
अटल क्रमागत ice_status
ice_aq_manage_mac_पढ़ो(काष्ठा ice_hw *hw, व्योम *buf, u16 buf_size,
		       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_manage_mac_पढ़ो_resp *resp;
	काष्ठा ice_aqc_manage_mac_पढ़ो *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;
	u16 flags;
	u8 i;

	cmd = &desc.params.mac_पढ़ो;

	अगर (buf_size < माप(*resp))
		वापस ICE_ERR_BUF_TOO_SHORT;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_manage_mac_पढ़ो);

	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	अगर (status)
		वापस status;

	resp = buf;
	flags = le16_to_cpu(cmd->flags) & ICE_AQC_MAN_MAC_READ_M;

	अगर (!(flags & ICE_AQC_MAN_MAC_LAN_ADDR_VALID)) अणु
		ice_debug(hw, ICE_DBG_LAN, "got invalid MAC address\n");
		वापस ICE_ERR_CFG;
	पूर्ण

	/* A single port can report up to two (LAN and WoL) addresses */
	क्रम (i = 0; i < cmd->num_addr; i++)
		अगर (resp[i].addr_type == ICE_AQC_MAN_MAC_ADDR_TYPE_LAN) अणु
			ether_addr_copy(hw->port_info->mac.lan_addr,
					resp[i].mac_addr);
			ether_addr_copy(hw->port_info->mac.perm_addr,
					resp[i].mac_addr);
			अवरोध;
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_aq_get_phy_caps - वापसs PHY capabilities
 * @pi: port inक्रमmation काष्ठाure
 * @qual_mods: report qualअगरied modules
 * @report_mode: report mode capabilities
 * @pcaps: काष्ठाure क्रम PHY capabilities to be filled
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Returns the various PHY capabilities supported on the Port (0x0600)
 */
क्रमागत ice_status
ice_aq_get_phy_caps(काष्ठा ice_port_info *pi, bool qual_mods, u8 report_mode,
		    काष्ठा ice_aqc_get_phy_caps_data *pcaps,
		    काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_get_phy_caps *cmd;
	u16 pcaps_size = माप(*pcaps);
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;

	cmd = &desc.params.get_phy;

	अगर (!pcaps || (report_mode & ~ICE_AQC_REPORT_MODE_M) || !pi)
		वापस ICE_ERR_PARAM;
	hw = pi->hw;

	अगर (report_mode == ICE_AQC_REPORT_DFLT_CFG &&
	    !ice_fw_supports_report_dflt_cfg(hw))
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_phy_caps);

	अगर (qual_mods)
		cmd->param0 |= cpu_to_le16(ICE_AQC_GET_PHY_RQM);

	cmd->param0 |= cpu_to_le16(report_mode);
	status = ice_aq_send_cmd(hw, &desc, pcaps, pcaps_size, cd);

	ice_debug(hw, ICE_DBG_LINK, "get phy caps - report_mode = 0x%x\n",
		  report_mode);
	ice_debug(hw, ICE_DBG_LINK, "	phy_type_low = 0x%llx\n",
		  (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pcaps->phy_type_low));
	ice_debug(hw, ICE_DBG_LINK, "	phy_type_high = 0x%llx\n",
		  (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(pcaps->phy_type_high));
	ice_debug(hw, ICE_DBG_LINK, "	caps = 0x%x\n", pcaps->caps);
	ice_debug(hw, ICE_DBG_LINK, "	low_power_ctrl_an = 0x%x\n",
		  pcaps->low_घातer_ctrl_an);
	ice_debug(hw, ICE_DBG_LINK, "	eee_cap = 0x%x\n", pcaps->eee_cap);
	ice_debug(hw, ICE_DBG_LINK, "	eeer_value = 0x%x\n",
		  pcaps->eeer_value);
	ice_debug(hw, ICE_DBG_LINK, "	link_fec_options = 0x%x\n",
		  pcaps->link_fec_options);
	ice_debug(hw, ICE_DBG_LINK, "	module_compliance_enforcement = 0x%x\n",
		  pcaps->module_compliance_enक्रमcement);
	ice_debug(hw, ICE_DBG_LINK, "   extended_compliance_code = 0x%x\n",
		  pcaps->extended_compliance_code);
	ice_debug(hw, ICE_DBG_LINK, "   module_type[0] = 0x%x\n",
		  pcaps->module_type[0]);
	ice_debug(hw, ICE_DBG_LINK, "   module_type[1] = 0x%x\n",
		  pcaps->module_type[1]);
	ice_debug(hw, ICE_DBG_LINK, "   module_type[2] = 0x%x\n",
		  pcaps->module_type[2]);

	अगर (!status && report_mode == ICE_AQC_REPORT_TOPO_CAP_MEDIA) अणु
		pi->phy.phy_type_low = le64_to_cpu(pcaps->phy_type_low);
		pi->phy.phy_type_high = le64_to_cpu(pcaps->phy_type_high);
		स_नकल(pi->phy.link_info.module_type, &pcaps->module_type,
		       माप(pi->phy.link_info.module_type));
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_get_link_topo_handle - get link topology node वापस status
 * @pi: port inक्रमmation काष्ठाure
 * @node_type: requested node type
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get link topology node वापस status क्रम specअगरied node type (0x06E0)
 *
 * Node type cage can be used to determine अगर cage is present. If AQC
 * वापसs error (ENOENT), then no cage present. If no cage present, then
 * connection type is backplane or BASE-T.
 */
अटल क्रमागत ice_status
ice_aq_get_link_topo_handle(काष्ठा ice_port_info *pi, u8 node_type,
			    काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_get_link_topo *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.get_link_topo;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_link_topo);

	cmd->addr.node_type_ctx = (ICE_AQC_LINK_TOPO_NODE_CTX_PORT <<
				   ICE_AQC_LINK_TOPO_NODE_CTX_S);

	/* set node type */
	cmd->addr.node_type_ctx |= (ICE_AQC_LINK_TOPO_NODE_TYPE_M & node_type);

	वापस ice_aq_send_cmd(pi->hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_is_media_cage_present
 * @pi: port inक्रमmation काष्ठाure
 *
 * Returns true अगर media cage is present, अन्यथा false. If no cage, then
 * media type is backplane or BASE-T.
 */
अटल bool ice_is_media_cage_present(काष्ठा ice_port_info *pi)
अणु
	/* Node type cage can be used to determine अगर cage is present. If AQC
	 * वापसs error (ENOENT), then no cage present. If no cage present then
	 * connection type is backplane or BASE-T.
	 */
	वापस !ice_aq_get_link_topo_handle(pi,
					    ICE_AQC_LINK_TOPO_NODE_TYPE_CAGE,
					    शून्य);
पूर्ण

/**
 * ice_get_media_type - Gets media type
 * @pi: port inक्रमmation काष्ठाure
 */
अटल क्रमागत ice_media_type ice_get_media_type(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_link_status *hw_link_info;

	अगर (!pi)
		वापस ICE_MEDIA_UNKNOWN;

	hw_link_info = &pi->phy.link_info;
	अगर (hw_link_info->phy_type_low && hw_link_info->phy_type_high)
		/* If more than one media type is selected, report unknown */
		वापस ICE_MEDIA_UNKNOWN;

	अगर (hw_link_info->phy_type_low) अणु
		/* 1G SGMII is a special हाल where some DA cable PHYs
		 * may show this as an option when it really shouldn't
		 * be since SGMII is meant to be between a MAC and a PHY
		 * in a backplane. Try to detect this हाल and handle it
		 */
		अगर (hw_link_info->phy_type_low == ICE_PHY_TYPE_LOW_1G_SGMII &&
		    (hw_link_info->module_type[ICE_AQC_MOD_TYPE_IDENT] ==
		    ICE_AQC_MOD_TYPE_BYTE1_SFP_PLUS_CU_ACTIVE ||
		    hw_link_info->module_type[ICE_AQC_MOD_TYPE_IDENT] ==
		    ICE_AQC_MOD_TYPE_BYTE1_SFP_PLUS_CU_PASSIVE))
			वापस ICE_MEDIA_DA;

		चयन (hw_link_info->phy_type_low) अणु
		हाल ICE_PHY_TYPE_LOW_1000BASE_SX:
		हाल ICE_PHY_TYPE_LOW_1000BASE_LX:
		हाल ICE_PHY_TYPE_LOW_10GBASE_SR:
		हाल ICE_PHY_TYPE_LOW_10GBASE_LR:
		हाल ICE_PHY_TYPE_LOW_10G_SFI_C2C:
		हाल ICE_PHY_TYPE_LOW_25GBASE_SR:
		हाल ICE_PHY_TYPE_LOW_25GBASE_LR:
		हाल ICE_PHY_TYPE_LOW_40GBASE_SR4:
		हाल ICE_PHY_TYPE_LOW_40GBASE_LR4:
		हाल ICE_PHY_TYPE_LOW_50GBASE_SR2:
		हाल ICE_PHY_TYPE_LOW_50GBASE_LR2:
		हाल ICE_PHY_TYPE_LOW_50GBASE_SR:
		हाल ICE_PHY_TYPE_LOW_50GBASE_FR:
		हाल ICE_PHY_TYPE_LOW_50GBASE_LR:
		हाल ICE_PHY_TYPE_LOW_100GBASE_SR4:
		हाल ICE_PHY_TYPE_LOW_100GBASE_LR4:
		हाल ICE_PHY_TYPE_LOW_100GBASE_SR2:
		हाल ICE_PHY_TYPE_LOW_100GBASE_DR:
		हाल ICE_PHY_TYPE_LOW_10G_SFI_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_25G_AUI_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_40G_XLAUI_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_50G_LAUI2_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_50G_AUI2_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_50G_AUI1_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_100G_CAUI4_AOC_ACC:
		हाल ICE_PHY_TYPE_LOW_100G_AUI4_AOC_ACC:
			वापस ICE_MEDIA_FIBER;
		हाल ICE_PHY_TYPE_LOW_100BASE_TX:
		हाल ICE_PHY_TYPE_LOW_1000BASE_T:
		हाल ICE_PHY_TYPE_LOW_2500BASE_T:
		हाल ICE_PHY_TYPE_LOW_5GBASE_T:
		हाल ICE_PHY_TYPE_LOW_10GBASE_T:
		हाल ICE_PHY_TYPE_LOW_25GBASE_T:
			वापस ICE_MEDIA_BASET;
		हाल ICE_PHY_TYPE_LOW_10G_SFI_DA:
		हाल ICE_PHY_TYPE_LOW_25GBASE_CR:
		हाल ICE_PHY_TYPE_LOW_25GBASE_CR_S:
		हाल ICE_PHY_TYPE_LOW_25GBASE_CR1:
		हाल ICE_PHY_TYPE_LOW_40GBASE_CR4:
		हाल ICE_PHY_TYPE_LOW_50GBASE_CR2:
		हाल ICE_PHY_TYPE_LOW_50GBASE_CP:
		हाल ICE_PHY_TYPE_LOW_100GBASE_CR4:
		हाल ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4:
		हाल ICE_PHY_TYPE_LOW_100GBASE_CP2:
			वापस ICE_MEDIA_DA;
		हाल ICE_PHY_TYPE_LOW_25G_AUI_C2C:
		हाल ICE_PHY_TYPE_LOW_40G_XLAUI:
		हाल ICE_PHY_TYPE_LOW_50G_LAUI2:
		हाल ICE_PHY_TYPE_LOW_50G_AUI2:
		हाल ICE_PHY_TYPE_LOW_50G_AUI1:
		हाल ICE_PHY_TYPE_LOW_100G_AUI4:
		हाल ICE_PHY_TYPE_LOW_100G_CAUI4:
			अगर (ice_is_media_cage_present(pi))
				वापस ICE_MEDIA_DA;
			fallthrough;
		हाल ICE_PHY_TYPE_LOW_1000BASE_KX:
		हाल ICE_PHY_TYPE_LOW_2500BASE_KX:
		हाल ICE_PHY_TYPE_LOW_2500BASE_X:
		हाल ICE_PHY_TYPE_LOW_5GBASE_KR:
		हाल ICE_PHY_TYPE_LOW_10GBASE_KR_CR1:
		हाल ICE_PHY_TYPE_LOW_25GBASE_KR:
		हाल ICE_PHY_TYPE_LOW_25GBASE_KR1:
		हाल ICE_PHY_TYPE_LOW_25GBASE_KR_S:
		हाल ICE_PHY_TYPE_LOW_40GBASE_KR4:
		हाल ICE_PHY_TYPE_LOW_50GBASE_KR_PAM4:
		हाल ICE_PHY_TYPE_LOW_50GBASE_KR2:
		हाल ICE_PHY_TYPE_LOW_100GBASE_KR4:
		हाल ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4:
			वापस ICE_MEDIA_BACKPLANE;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (hw_link_info->phy_type_high) अणु
		हाल ICE_PHY_TYPE_HIGH_100G_AUI2:
		हाल ICE_PHY_TYPE_HIGH_100G_CAUI2:
			अगर (ice_is_media_cage_present(pi))
				वापस ICE_MEDIA_DA;
			fallthrough;
		हाल ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4:
			वापस ICE_MEDIA_BACKPLANE;
		हाल ICE_PHY_TYPE_HIGH_100G_CAUI2_AOC_ACC:
		हाल ICE_PHY_TYPE_HIGH_100G_AUI2_AOC_ACC:
			वापस ICE_MEDIA_FIBER;
		पूर्ण
	पूर्ण
	वापस ICE_MEDIA_UNKNOWN;
पूर्ण

/**
 * ice_aq_get_link_info
 * @pi: port inक्रमmation काष्ठाure
 * @ena_lse: enable/disable LinkStatusEvent reporting
 * @link: poपूर्णांकer to link status काष्ठाure - optional
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get Link Status (0x607). Returns the link status of the adapter.
 */
क्रमागत ice_status
ice_aq_get_link_info(काष्ठा ice_port_info *pi, bool ena_lse,
		     काष्ठा ice_link_status *link, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_get_link_status_data link_data = अणु 0 पूर्ण;
	काष्ठा ice_aqc_get_link_status *resp;
	काष्ठा ice_link_status *li_old, *li;
	क्रमागत ice_media_type *hw_media_type;
	काष्ठा ice_fc_info *hw_fc_info;
	bool tx_छोड़ो, rx_छोड़ो;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;
	u16 cmd_flags;

	अगर (!pi)
		वापस ICE_ERR_PARAM;
	hw = pi->hw;
	li_old = &pi->phy.link_info_old;
	hw_media_type = &pi->phy.media_type;
	li = &pi->phy.link_info;
	hw_fc_info = &pi->fc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_link_status);
	cmd_flags = (ena_lse) ? ICE_AQ_LSE_ENA : ICE_AQ_LSE_DIS;
	resp = &desc.params.get_link_status;
	resp->cmd_flags = cpu_to_le16(cmd_flags);
	resp->lport_num = pi->lport;

	status = ice_aq_send_cmd(hw, &desc, &link_data, माप(link_data), cd);

	अगर (status)
		वापस status;

	/* save off old link status inक्रमmation */
	*li_old = *li;

	/* update current link status inक्रमmation */
	li->link_speed = le16_to_cpu(link_data.link_speed);
	li->phy_type_low = le64_to_cpu(link_data.phy_type_low);
	li->phy_type_high = le64_to_cpu(link_data.phy_type_high);
	*hw_media_type = ice_get_media_type(pi);
	li->link_info = link_data.link_info;
	li->an_info = link_data.an_info;
	li->ext_info = link_data.ext_info;
	li->max_frame_size = le16_to_cpu(link_data.max_frame_size);
	li->fec_info = link_data.cfg & ICE_AQ_FEC_MASK;
	li->topo_media_conflict = link_data.topo_media_conflict;
	li->pacing = link_data.cfg & (ICE_AQ_CFG_PACING_M |
				      ICE_AQ_CFG_PACING_TYPE_M);

	/* update fc info */
	tx_छोड़ो = !!(link_data.an_info & ICE_AQ_LINK_PAUSE_TX);
	rx_छोड़ो = !!(link_data.an_info & ICE_AQ_LINK_PAUSE_RX);
	अगर (tx_छोड़ो && rx_छोड़ो)
		hw_fc_info->current_mode = ICE_FC_FULL;
	अन्यथा अगर (tx_छोड़ो)
		hw_fc_info->current_mode = ICE_FC_TX_PAUSE;
	अन्यथा अगर (rx_छोड़ो)
		hw_fc_info->current_mode = ICE_FC_RX_PAUSE;
	अन्यथा
		hw_fc_info->current_mode = ICE_FC_NONE;

	li->lse_ena = !!(resp->cmd_flags & cpu_to_le16(ICE_AQ_LSE_IS_ENABLED));

	ice_debug(hw, ICE_DBG_LINK, "get link info\n");
	ice_debug(hw, ICE_DBG_LINK, "	link_speed = 0x%x\n", li->link_speed);
	ice_debug(hw, ICE_DBG_LINK, "	phy_type_low = 0x%llx\n",
		  (अचिन्हित दीर्घ दीर्घ)li->phy_type_low);
	ice_debug(hw, ICE_DBG_LINK, "	phy_type_high = 0x%llx\n",
		  (अचिन्हित दीर्घ दीर्घ)li->phy_type_high);
	ice_debug(hw, ICE_DBG_LINK, "	media_type = 0x%x\n", *hw_media_type);
	ice_debug(hw, ICE_DBG_LINK, "	link_info = 0x%x\n", li->link_info);
	ice_debug(hw, ICE_DBG_LINK, "	an_info = 0x%x\n", li->an_info);
	ice_debug(hw, ICE_DBG_LINK, "	ext_info = 0x%x\n", li->ext_info);
	ice_debug(hw, ICE_DBG_LINK, "	fec_info = 0x%x\n", li->fec_info);
	ice_debug(hw, ICE_DBG_LINK, "	lse_ena = 0x%x\n", li->lse_ena);
	ice_debug(hw, ICE_DBG_LINK, "	max_frame = 0x%x\n",
		  li->max_frame_size);
	ice_debug(hw, ICE_DBG_LINK, "	pacing = 0x%x\n", li->pacing);

	/* save link status inक्रमmation */
	अगर (link)
		*link = *li;

	/* flag cleared so calling functions करोn't call AQ again */
	pi->phy.get_link_info = false;

	वापस 0;
पूर्ण

/**
 * ice_fill_tx_समयr_and_fc_thresh
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cmd: poपूर्णांकer to MAC cfg काष्ठाure
 *
 * Add Tx समयr and FC refresh threshold info to Set MAC Config AQ command
 * descriptor
 */
अटल व्योम
ice_fill_tx_समयr_and_fc_thresh(काष्ठा ice_hw *hw,
				काष्ठा ice_aqc_set_mac_cfg *cmd)
अणु
	u16 fc_thres_val, tx_समयr_val;
	u32 val;

	/* We पढ़ो back the transmit समयr and FC threshold value of
	 * LFC. Thus, we will use index =
	 * PRTMAC_HSEC_CTL_TX_PAUSE_QUANTA_MAX_INDEX.
	 *
	 * Also, because we are operating on transmit समयr and FC
	 * threshold of LFC, we करोn't turn on any bit in tx_पंचांगr_priority
	 */
#घोषणा IDX_OF_LFC PRTMAC_HSEC_CTL_TX_PAUSE_QUANTA_MAX_INDEX

	/* Retrieve the transmit समयr */
	val = rd32(hw, PRTMAC_HSEC_CTL_TX_PAUSE_QUANTA(IDX_OF_LFC));
	tx_समयr_val = val &
		PRTMAC_HSEC_CTL_TX_PAUSE_QUANTA_HSEC_CTL_TX_PAUSE_QUANTA_M;
	cmd->tx_पंचांगr_value = cpu_to_le16(tx_समयr_val);

	/* Retrieve the FC threshold */
	val = rd32(hw, PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER(IDX_OF_LFC));
	fc_thres_val = val & PRTMAC_HSEC_CTL_TX_PAUSE_REFRESH_TIMER_M;

	cmd->fc_refresh_threshold = cpu_to_le16(fc_thres_val);
पूर्ण

/**
 * ice_aq_set_mac_cfg
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @max_frame_size: Maximum Frame Size to be supported
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set MAC configuration (0x0603)
 */
क्रमागत ice_status
ice_aq_set_mac_cfg(काष्ठा ice_hw *hw, u16 max_frame_size, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_set_mac_cfg *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.set_mac_cfg;

	अगर (max_frame_size == 0)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_mac_cfg);

	cmd->max_frame_size = cpu_to_le16(max_frame_size);

	ice_fill_tx_समयr_and_fc_thresh(hw, cmd);

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_init_fltr_mgmt_काष्ठा - initializes filter management list and locks
 * @hw: poपूर्णांकer to the HW काष्ठा
 */
अटल क्रमागत ice_status ice_init_fltr_mgmt_काष्ठा(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_चयन_info *sw;
	क्रमागत ice_status status;

	hw->चयन_info = devm_kzalloc(ice_hw_to_dev(hw),
				       माप(*hw->चयन_info), GFP_KERNEL);
	sw = hw->चयन_info;

	अगर (!sw)
		वापस ICE_ERR_NO_MEMORY;

	INIT_LIST_HEAD(&sw->vsi_list_map_head);

	status = ice_init_def_sw_recp(hw);
	अगर (status) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), hw->चयन_info);
		वापस status;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_cleanup_fltr_mgmt_काष्ठा - cleanup filter management list and locks
 * @hw: poपूर्णांकer to the HW काष्ठा
 */
अटल व्योम ice_cleanup_fltr_mgmt_काष्ठा(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	काष्ठा ice_vsi_list_map_info *v_pos_map;
	काष्ठा ice_vsi_list_map_info *v_पंचांगp_map;
	काष्ठा ice_sw_recipe *recps;
	u8 i;

	list_क्रम_each_entry_safe(v_pos_map, v_पंचांगp_map, &sw->vsi_list_map_head,
				 list_entry) अणु
		list_del(&v_pos_map->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), v_pos_map);
	पूर्ण
	recps = hw->चयन_info->recp_list;
	क्रम (i = 0; i < ICE_SW_LKUP_LAST; i++) अणु
		काष्ठा ice_fltr_mgmt_list_entry *lst_itr, *पंचांगp_entry;

		recps[i].root_rid = i;
		mutex_destroy(&recps[i].filt_rule_lock);
		list_क्रम_each_entry_safe(lst_itr, पंचांगp_entry,
					 &recps[i].filt_rules, list_entry) अणु
			list_del(&lst_itr->list_entry);
			devm_kमुक्त(ice_hw_to_dev(hw), lst_itr);
		पूर्ण
	पूर्ण
	ice_rm_all_sw_replay_rule_info(hw);
	devm_kमुक्त(ice_hw_to_dev(hw), sw->recp_list);
	devm_kमुक्त(ice_hw_to_dev(hw), sw);
पूर्ण

/**
 * ice_get_fw_log_cfg - get FW logging configuration
 * @hw: poपूर्णांकer to the HW काष्ठा
 */
अटल क्रमागत ice_status ice_get_fw_log_cfg(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;
	__le16 *config;
	u16 size;

	size = माप(*config) * ICE_AQC_FW_LOG_ID_MAX;
	config = devm_kzalloc(ice_hw_to_dev(hw), size, GFP_KERNEL);
	अगर (!config)
		वापस ICE_ERR_NO_MEMORY;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_fw_logging_info);

	status = ice_aq_send_cmd(hw, &desc, config, size, शून्य);
	अगर (!status) अणु
		u16 i;

		/* Save FW logging inक्रमmation पूर्णांकo the HW काष्ठाure */
		क्रम (i = 0; i < ICE_AQC_FW_LOG_ID_MAX; i++) अणु
			u16 v, m, flgs;

			v = le16_to_cpu(config[i]);
			m = (v & ICE_AQC_FW_LOG_ID_M) >> ICE_AQC_FW_LOG_ID_S;
			flgs = (v & ICE_AQC_FW_LOG_EN_M) >> ICE_AQC_FW_LOG_EN_S;

			अगर (m < ICE_AQC_FW_LOG_ID_MAX)
				hw->fw_log.evnts[m].cur = flgs;
		पूर्ण
	पूर्ण

	devm_kमुक्त(ice_hw_to_dev(hw), config);

	वापस status;
पूर्ण

/**
 * ice_cfg_fw_log - configure FW logging
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @enable: enable certain FW logging events अगर true, disable all अगर false
 *
 * This function enables/disables the FW logging via Rx CQ events and a UART
 * port based on predetermined configurations. FW logging via the Rx CQ can be
 * enabled/disabled क्रम inभागidual PF's. However, FW logging via the UART can
 * only be enabled/disabled क्रम all PFs on the same device.
 *
 * To enable overall FW logging, the "cq_en" and "uart_en" enable bits in
 * hw->fw_log need to be set accordingly, e.g. based on user-provided input,
 * beक्रमe initializing the device.
 *
 * When re/configuring FW logging, callers need to update the "cfg" elements of
 * the hw->fw_log.evnts array with the desired logging event configurations क्रम
 * modules of पूर्णांकerest. When disabling FW logging completely, the callers can
 * just pass false in the "enable" parameter. On completion, the function will
 * update the "cur" element of the hw->fw_log.evnts array with the resulting
 * logging event configurations of the modules that are being re/configured. FW
 * logging modules that are not part of a reconfiguration operation retain their
 * previous states.
 *
 * Beक्रमe resetting the device, it is recommended that the driver disables FW
 * logging beक्रमe shutting करोwn the control queue. When disabling FW logging
 * ("enable" = false), the latest configurations of FW logging events stored in
 * hw->fw_log.evnts[] are not overridden to allow them to be reconfigured after
 * a device reset.
 *
 * When enabling FW logging to emit log messages via the Rx CQ during the
 * device's initialization phase, a mechanism alternative to पूर्णांकerrupt handlers
 * needs to be used to extract FW log messages from the Rx CQ periodically and
 * to prevent the Rx CQ from being full and stalling other types of control
 * messages from FW to SW. Interrupts are typically disabled during the device's
 * initialization phase.
 */
अटल क्रमागत ice_status ice_cfg_fw_log(काष्ठा ice_hw *hw, bool enable)
अणु
	काष्ठा ice_aqc_fw_logging *cmd;
	क्रमागत ice_status status = 0;
	u16 i, chgs = 0, len = 0;
	काष्ठा ice_aq_desc desc;
	__le16 *data = शून्य;
	u8 actv_evnts = 0;
	व्योम *buf = शून्य;

	अगर (!hw->fw_log.cq_en && !hw->fw_log.uart_en)
		वापस 0;

	/* Disable FW logging only when the control queue is still responsive */
	अगर (!enable &&
	    (!hw->fw_log.actv_evnts || !ice_check_sq_alive(hw, &hw->adminq)))
		वापस 0;

	/* Get current FW log settings */
	status = ice_get_fw_log_cfg(hw);
	अगर (status)
		वापस status;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_fw_logging);
	cmd = &desc.params.fw_logging;

	/* Indicate which controls are valid */
	अगर (hw->fw_log.cq_en)
		cmd->log_ctrl_valid |= ICE_AQC_FW_LOG_AQ_VALID;

	अगर (hw->fw_log.uart_en)
		cmd->log_ctrl_valid |= ICE_AQC_FW_LOG_UART_VALID;

	अगर (enable) अणु
		/* Fill in an array of entries with FW logging modules and
		 * logging events being reconfigured.
		 */
		क्रम (i = 0; i < ICE_AQC_FW_LOG_ID_MAX; i++) अणु
			u16 val;

			/* Keep track of enabled event types */
			actv_evnts |= hw->fw_log.evnts[i].cfg;

			अगर (hw->fw_log.evnts[i].cfg == hw->fw_log.evnts[i].cur)
				जारी;

			अगर (!data) अणु
				data = devm_kसुस्मृति(ice_hw_to_dev(hw),
						    ICE_AQC_FW_LOG_ID_MAX,
						    माप(*data),
						    GFP_KERNEL);
				अगर (!data)
					वापस ICE_ERR_NO_MEMORY;
			पूर्ण

			val = i << ICE_AQC_FW_LOG_ID_S;
			val |= hw->fw_log.evnts[i].cfg << ICE_AQC_FW_LOG_EN_S;
			data[chgs++] = cpu_to_le16(val);
		पूर्ण

		/* Only enable FW logging अगर at least one module is specअगरied.
		 * If FW logging is currently enabled but all modules are not
		 * enabled to emit log messages, disable FW logging altogether.
		 */
		अगर (actv_evnts) अणु
			/* Leave अगर there is effectively no change */
			अगर (!chgs)
				जाओ out;

			अगर (hw->fw_log.cq_en)
				cmd->log_ctrl |= ICE_AQC_FW_LOG_AQ_EN;

			अगर (hw->fw_log.uart_en)
				cmd->log_ctrl |= ICE_AQC_FW_LOG_UART_EN;

			buf = data;
			len = माप(*data) * chgs;
			desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
		पूर्ण
	पूर्ण

	status = ice_aq_send_cmd(hw, &desc, buf, len, शून्य);
	अगर (!status) अणु
		/* Update the current configuration to reflect events enabled.
		 * hw->fw_log.cq_en and hw->fw_log.uart_en indicate अगर the FW
		 * logging mode is enabled क्रम the device. They करो not reflect
		 * actual modules being enabled to emit log messages. So, their
		 * values reमुख्य unchanged even when all modules are disabled.
		 */
		u16 cnt = enable ? chgs : (u16)ICE_AQC_FW_LOG_ID_MAX;

		hw->fw_log.actv_evnts = actv_evnts;
		क्रम (i = 0; i < cnt; i++) अणु
			u16 v, m;

			अगर (!enable) अणु
				/* When disabling all FW logging events as part
				 * of device's de-initialization, the original
				 * configurations are retained, and can be used
				 * to reconfigure FW logging later अगर the device
				 * is re-initialized.
				 */
				hw->fw_log.evnts[i].cur = 0;
				जारी;
			पूर्ण

			v = le16_to_cpu(data[i]);
			m = (v & ICE_AQC_FW_LOG_ID_M) >> ICE_AQC_FW_LOG_ID_S;
			hw->fw_log.evnts[m].cur = hw->fw_log.evnts[m].cfg;
		पूर्ण
	पूर्ण

out:
	अगर (data)
		devm_kमुक्त(ice_hw_to_dev(hw), data);

	वापस status;
पूर्ण

/**
 * ice_output_fw_log
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @desc: poपूर्णांकer to the AQ message descriptor
 * @buf: poपूर्णांकer to the buffer accompanying the AQ message
 *
 * Formats a FW Log message and outमाला_दो it via the standard driver logs.
 */
व्योम ice_output_fw_log(काष्ठा ice_hw *hw, काष्ठा ice_aq_desc *desc, व्योम *buf)
अणु
	ice_debug(hw, ICE_DBG_FW_LOG, "[ FW Log Msg Start ]\n");
	ice_debug_array(hw, ICE_DBG_FW_LOG, 16, 1, (u8 *)buf,
			le16_to_cpu(desc->datalen));
	ice_debug(hw, ICE_DBG_FW_LOG, "[ FW Log Msg End ]\n");
पूर्ण

/**
 * ice_get_itr_पूर्णांकrl_gran
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Determines the ITR/INTRL granularities based on the maximum aggregate
 * bandwidth according to the device's configuration during घातer-on.
 */
अटल व्योम ice_get_itr_पूर्णांकrl_gran(काष्ठा ice_hw *hw)
अणु
	u8 max_agg_bw = (rd32(hw, GL_PWR_MODE_CTL) &
			 GL_PWR_MODE_CTL_CAR_MAX_BW_M) >>
			GL_PWR_MODE_CTL_CAR_MAX_BW_S;

	चयन (max_agg_bw) अणु
	हाल ICE_MAX_AGG_BW_200G:
	हाल ICE_MAX_AGG_BW_100G:
	हाल ICE_MAX_AGG_BW_50G:
		hw->itr_gran = ICE_ITR_GRAN_ABOVE_25;
		hw->पूर्णांकrl_gran = ICE_INTRL_GRAN_ABOVE_25;
		अवरोध;
	हाल ICE_MAX_AGG_BW_25G:
		hw->itr_gran = ICE_ITR_GRAN_MAX_25;
		hw->पूर्णांकrl_gran = ICE_INTRL_GRAN_MAX_25;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_init_hw - मुख्य hardware initialization routine
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
क्रमागत ice_status ice_init_hw(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	क्रमागत ice_status status;
	u16 mac_buf_len;
	व्योम *mac_buf;

	/* Set MAC type based on DeviceID */
	status = ice_set_mac_type(hw);
	अगर (status)
		वापस status;

	hw->pf_id = (u8)(rd32(hw, PF_FUNC_RID) &
			 PF_FUNC_RID_FUNC_NUM_M) >>
		PF_FUNC_RID_FUNC_NUM_S;

	status = ice_reset(hw, ICE_RESET_PFR);
	अगर (status)
		वापस status;

	ice_get_itr_पूर्णांकrl_gran(hw);

	status = ice_create_all_ctrlq(hw);
	अगर (status)
		जाओ err_unroll_cqinit;

	/* Enable FW logging. Not fatal अगर this fails. */
	status = ice_cfg_fw_log(hw, true);
	अगर (status)
		ice_debug(hw, ICE_DBG_INIT, "Failed to enable FW logging.\n");

	status = ice_clear_pf_cfg(hw);
	अगर (status)
		जाओ err_unroll_cqinit;

	/* Set bit to enable Flow Director filters */
	wr32(hw, PFQF_FD_ENA, PFQF_FD_ENA_FD_ENA_M);
	INIT_LIST_HEAD(&hw->fdir_list_head);

	ice_clear_pxe_mode(hw);

	status = ice_init_nvm(hw);
	अगर (status)
		जाओ err_unroll_cqinit;

	status = ice_get_caps(hw);
	अगर (status)
		जाओ err_unroll_cqinit;

	hw->port_info = devm_kzalloc(ice_hw_to_dev(hw),
				     माप(*hw->port_info), GFP_KERNEL);
	अगर (!hw->port_info) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ err_unroll_cqinit;
	पूर्ण

	/* set the back poपूर्णांकer to HW */
	hw->port_info->hw = hw;

	/* Initialize port_info काष्ठा with चयन configuration data */
	status = ice_get_initial_sw_cfg(hw);
	अगर (status)
		जाओ err_unroll_alloc;

	hw->evb_veb = true;

	/* Query the allocated resources क्रम Tx scheduler */
	status = ice_sched_query_res_alloc(hw);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_SCHED, "Failed to get scheduler allocated resources\n");
		जाओ err_unroll_alloc;
	पूर्ण
	ice_sched_get_psm_clk_freq(hw);

	/* Initialize port_info काष्ठा with scheduler data */
	status = ice_sched_init_port(hw->port_info);
	अगर (status)
		जाओ err_unroll_sched;

	pcaps = devm_kzalloc(ice_hw_to_dev(hw), माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ err_unroll_sched;
	पूर्ण

	/* Initialize port_info काष्ठा with PHY capabilities */
	status = ice_aq_get_phy_caps(hw->port_info, false,
				     ICE_AQC_REPORT_TOPO_CAP_MEDIA, pcaps,
				     शून्य);
	devm_kमुक्त(ice_hw_to_dev(hw), pcaps);
	अगर (status)
		dev_warn(ice_hw_to_dev(hw), "Get PHY capabilities failed status = %d, continuing anyway\n",
			 status);

	/* Initialize port_info काष्ठा with link inक्रमmation */
	status = ice_aq_get_link_info(hw->port_info, false, शून्य, शून्य);
	अगर (status)
		जाओ err_unroll_sched;

	/* need a valid SW entry poपूर्णांक to build a Tx tree */
	अगर (!hw->sw_entry_poपूर्णांक_layer) अणु
		ice_debug(hw, ICE_DBG_SCHED, "invalid sw entry point\n");
		status = ICE_ERR_CFG;
		जाओ err_unroll_sched;
	पूर्ण
	INIT_LIST_HEAD(&hw->agg_list);
	/* Initialize max burst size */
	अगर (!hw->max_burst_size)
		ice_cfg_rl_burst_size(hw, ICE_SCHED_DFLT_BURST_SIZE);

	status = ice_init_fltr_mgmt_काष्ठा(hw);
	अगर (status)
		जाओ err_unroll_sched;

	/* Get MAC inक्रमmation */
	/* A single port can report up to two (LAN and WoL) addresses */
	mac_buf = devm_kसुस्मृति(ice_hw_to_dev(hw), 2,
			       माप(काष्ठा ice_aqc_manage_mac_पढ़ो_resp),
			       GFP_KERNEL);
	mac_buf_len = 2 * माप(काष्ठा ice_aqc_manage_mac_पढ़ो_resp);

	अगर (!mac_buf) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ err_unroll_fltr_mgmt_काष्ठा;
	पूर्ण

	status = ice_aq_manage_mac_पढ़ो(hw, mac_buf, mac_buf_len, शून्य);
	devm_kमुक्त(ice_hw_to_dev(hw), mac_buf);

	अगर (status)
		जाओ err_unroll_fltr_mgmt_काष्ठा;
	/* enable jumbo frame support at MAC level */
	status = ice_aq_set_mac_cfg(hw, ICE_AQ_SET_MAC_FRAME_SIZE_MAX, शून्य);
	अगर (status)
		जाओ err_unroll_fltr_mgmt_काष्ठा;
	/* Obtain counter base index which would be used by flow director */
	status = ice_alloc_fd_res_cntr(hw, &hw->fd_ctr_base);
	अगर (status)
		जाओ err_unroll_fltr_mgmt_काष्ठा;
	status = ice_init_hw_tbls(hw);
	अगर (status)
		जाओ err_unroll_fltr_mgmt_काष्ठा;
	mutex_init(&hw->tnl_lock);
	वापस 0;

err_unroll_fltr_mgmt_काष्ठा:
	ice_cleanup_fltr_mgmt_काष्ठा(hw);
err_unroll_sched:
	ice_sched_cleanup_all(hw);
err_unroll_alloc:
	devm_kमुक्त(ice_hw_to_dev(hw), hw->port_info);
err_unroll_cqinit:
	ice_destroy_all_ctrlq(hw);
	वापस status;
पूर्ण

/**
 * ice_deinit_hw - unroll initialization operations करोne by ice_init_hw
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * This should be called only during nominal operation, not as a result of
 * ice_init_hw() failing since ice_init_hw() will take care of unrolling
 * applicable initializations अगर it fails क्रम any reason.
 */
व्योम ice_deinit_hw(काष्ठा ice_hw *hw)
अणु
	ice_मुक्त_fd_res_cntr(hw, hw->fd_ctr_base);
	ice_cleanup_fltr_mgmt_काष्ठा(hw);

	ice_sched_cleanup_all(hw);
	ice_sched_clear_agg(hw);
	ice_मुक्त_seg(hw);
	ice_मुक्त_hw_tbls(hw);
	mutex_destroy(&hw->tnl_lock);

	अगर (hw->port_info) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), hw->port_info);
		hw->port_info = शून्य;
	पूर्ण

	/* Attempt to disable FW logging beक्रमe shutting करोwn control queues */
	ice_cfg_fw_log(hw, false);
	ice_destroy_all_ctrlq(hw);

	/* Clear VSI contexts अगर not alपढ़ोy cleared */
	ice_clear_all_vsi_ctx(hw);
पूर्ण

/**
 * ice_check_reset - Check to see अगर a global reset is complete
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
क्रमागत ice_status ice_check_reset(काष्ठा ice_hw *hw)
अणु
	u32 cnt, reg = 0, grst_समयout, uld_mask;

	/* Poll क्रम Device Active state in हाल a recent CORER, GLOBR,
	 * or EMPR has occurred. The grst delay value is in 100ms units.
	 * Add 1sec क्रम outstanding AQ commands that can take a दीर्घ समय.
	 */
	grst_समयout = ((rd32(hw, GLGEN_RSTCTL) & GLGEN_RSTCTL_GRSTDEL_M) >>
			GLGEN_RSTCTL_GRSTDEL_S) + 10;

	क्रम (cnt = 0; cnt < grst_समयout; cnt++) अणु
		mdelay(100);
		reg = rd32(hw, GLGEN_RSTAT);
		अगर (!(reg & GLGEN_RSTAT_DEVSTATE_M))
			अवरोध;
	पूर्ण

	अगर (cnt == grst_समयout) अणु
		ice_debug(hw, ICE_DBG_INIT, "Global reset polling failed to complete.\n");
		वापस ICE_ERR_RESET_FAILED;
	पूर्ण

#घोषणा ICE_RESET_DONE_MASK	(GLNVM_ULD_PCIER_DONE_M |\
				 GLNVM_ULD_PCIER_DONE_1_M |\
				 GLNVM_ULD_CORER_DONE_M |\
				 GLNVM_ULD_GLOBR_DONE_M |\
				 GLNVM_ULD_POR_DONE_M |\
				 GLNVM_ULD_POR_DONE_1_M |\
				 GLNVM_ULD_PCIER_DONE_2_M)

	uld_mask = ICE_RESET_DONE_MASK;

	/* Device is Active; check Global Reset processes are करोne */
	क्रम (cnt = 0; cnt < ICE_PF_RESET_WAIT_COUNT; cnt++) अणु
		reg = rd32(hw, GLNVM_ULD) & uld_mask;
		अगर (reg == uld_mask) अणु
			ice_debug(hw, ICE_DBG_INIT, "Global reset processes done. %d\n", cnt);
			अवरोध;
		पूर्ण
		mdelay(10);
	पूर्ण

	अगर (cnt == ICE_PF_RESET_WAIT_COUNT) अणु
		ice_debug(hw, ICE_DBG_INIT, "Wait for Reset Done timed out. GLNVM_ULD = 0x%x\n",
			  reg);
		वापस ICE_ERR_RESET_FAILED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_pf_reset - Reset the PF
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * If a global reset has been triggered, this function checks
 * क्रम its completion and then issues the PF reset
 */
अटल क्रमागत ice_status ice_pf_reset(काष्ठा ice_hw *hw)
अणु
	u32 cnt, reg;

	/* If at function entry a global reset was alपढ़ोy in progress, i.e.
	 * state is not 'device active' or any of the reset करोne bits are not
	 * set in GLNVM_ULD, there is no need क्रम a PF Reset; poll until the
	 * global reset is करोne.
	 */
	अगर ((rd32(hw, GLGEN_RSTAT) & GLGEN_RSTAT_DEVSTATE_M) ||
	    (rd32(hw, GLNVM_ULD) & ICE_RESET_DONE_MASK) ^ ICE_RESET_DONE_MASK) अणु
		/* poll on global reset currently in progress until करोne */
		अगर (ice_check_reset(hw))
			वापस ICE_ERR_RESET_FAILED;

		वापस 0;
	पूर्ण

	/* Reset the PF */
	reg = rd32(hw, PFGEN_CTRL);

	wr32(hw, PFGEN_CTRL, (reg | PFGEN_CTRL_PFSWR_M));

	/* Wait क्रम the PFR to complete. The रुको समय is the global config lock
	 * समयout plus the PFR समयout which will account क्रम a possible reset
	 * that is occurring during a करोwnload package operation.
	 */
	क्रम (cnt = 0; cnt < ICE_GLOBAL_CFG_LOCK_TIMEOUT +
	     ICE_PF_RESET_WAIT_COUNT; cnt++) अणु
		reg = rd32(hw, PFGEN_CTRL);
		अगर (!(reg & PFGEN_CTRL_PFSWR_M))
			अवरोध;

		mdelay(1);
	पूर्ण

	अगर (cnt == ICE_PF_RESET_WAIT_COUNT) अणु
		ice_debug(hw, ICE_DBG_INIT, "PF reset polling failed to complete.\n");
		वापस ICE_ERR_RESET_FAILED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_reset - Perक्रमm dअगरferent types of reset
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @req: reset request
 *
 * This function triggers a reset as specअगरied by the req parameter.
 *
 * Note:
 * If anything other than a PF reset is triggered, PXE mode is restored.
 * This has to be cleared using ice_clear_pxe_mode again, once the AQ
 * पूर्णांकerface has been restored in the rebuild flow.
 */
क्रमागत ice_status ice_reset(काष्ठा ice_hw *hw, क्रमागत ice_reset_req req)
अणु
	u32 val = 0;

	चयन (req) अणु
	हाल ICE_RESET_PFR:
		वापस ice_pf_reset(hw);
	हाल ICE_RESET_CORER:
		ice_debug(hw, ICE_DBG_INIT, "CoreR requested\n");
		val = GLGEN_RTRIG_CORER_M;
		अवरोध;
	हाल ICE_RESET_GLOBR:
		ice_debug(hw, ICE_DBG_INIT, "GlobalR requested\n");
		val = GLGEN_RTRIG_GLOBR_M;
		अवरोध;
	शेष:
		वापस ICE_ERR_PARAM;
	पूर्ण

	val |= rd32(hw, GLGEN_RTRIG);
	wr32(hw, GLGEN_RTRIG, val);
	ice_flush(hw);

	/* रुको क्रम the FW to be पढ़ोy */
	वापस ice_check_reset(hw);
पूर्ण

/**
 * ice_copy_rxq_ctx_to_hw
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @ice_rxq_ctx: poपूर्णांकer to the rxq context
 * @rxq_index: the index of the Rx queue
 *
 * Copies rxq context from dense काष्ठाure to HW रेजिस्टर space
 */
अटल क्रमागत ice_status
ice_copy_rxq_ctx_to_hw(काष्ठा ice_hw *hw, u8 *ice_rxq_ctx, u32 rxq_index)
अणु
	u8 i;

	अगर (!ice_rxq_ctx)
		वापस ICE_ERR_BAD_PTR;

	अगर (rxq_index > QRX_CTRL_MAX_INDEX)
		वापस ICE_ERR_PARAM;

	/* Copy each dword separately to HW */
	क्रम (i = 0; i < ICE_RXQ_CTX_SIZE_DWORDS; i++) अणु
		wr32(hw, QRX_CONTEXT(i, rxq_index),
		     *((u32 *)(ice_rxq_ctx + (i * माप(u32)))));

		ice_debug(hw, ICE_DBG_QCTX, "qrxdata[%d]: %08X\n", i,
			  *((u32 *)(ice_rxq_ctx + (i * माप(u32)))));
	पूर्ण

	वापस 0;
पूर्ण

/* LAN Rx Queue Context */
अटल स्थिर काष्ठा ice_ctx_ele ice_rlan_ctx_info[] = अणु
	/* Field		Width	LSB */
	ICE_CTX_STORE(ice_rlan_ctx, head,		13,	0),
	ICE_CTX_STORE(ice_rlan_ctx, cpuid,		8,	13),
	ICE_CTX_STORE(ice_rlan_ctx, base,		57,	32),
	ICE_CTX_STORE(ice_rlan_ctx, qlen,		13,	89),
	ICE_CTX_STORE(ice_rlan_ctx, dbuf,		7,	102),
	ICE_CTX_STORE(ice_rlan_ctx, hbuf,		5,	109),
	ICE_CTX_STORE(ice_rlan_ctx, dtype,		2,	114),
	ICE_CTX_STORE(ice_rlan_ctx, dsize,		1,	116),
	ICE_CTX_STORE(ice_rlan_ctx, crcstrip,		1,	117),
	ICE_CTX_STORE(ice_rlan_ctx, l2tsel,		1,	119),
	ICE_CTX_STORE(ice_rlan_ctx, hsplit_0,		4,	120),
	ICE_CTX_STORE(ice_rlan_ctx, hsplit_1,		2,	124),
	ICE_CTX_STORE(ice_rlan_ctx, showiv,		1,	127),
	ICE_CTX_STORE(ice_rlan_ctx, rxmax,		14,	174),
	ICE_CTX_STORE(ice_rlan_ctx, tphrdesc_ena,	1,	193),
	ICE_CTX_STORE(ice_rlan_ctx, tphwdesc_ena,	1,	194),
	ICE_CTX_STORE(ice_rlan_ctx, tphdata_ena,	1,	195),
	ICE_CTX_STORE(ice_rlan_ctx, tphhead_ena,	1,	196),
	ICE_CTX_STORE(ice_rlan_ctx, lrxqthresh,		3,	198),
	ICE_CTX_STORE(ice_rlan_ctx, prefena,		1,	201),
	अणु 0 पूर्ण
पूर्ण;

/**
 * ice_ग_लिखो_rxq_ctx
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @rlan_ctx: poपूर्णांकer to the rxq context
 * @rxq_index: the index of the Rx queue
 *
 * Converts rxq context from sparse to dense काष्ठाure and then ग_लिखोs
 * it to HW रेजिस्टर space and enables the hardware to prefetch descriptors
 * instead of only fetching them on demand
 */
क्रमागत ice_status
ice_ग_लिखो_rxq_ctx(काष्ठा ice_hw *hw, काष्ठा ice_rlan_ctx *rlan_ctx,
		  u32 rxq_index)
अणु
	u8 ctx_buf[ICE_RXQ_CTX_SZ] = अणु 0 पूर्ण;

	अगर (!rlan_ctx)
		वापस ICE_ERR_BAD_PTR;

	rlan_ctx->prefena = 1;

	ice_set_ctx(hw, (u8 *)rlan_ctx, ctx_buf, ice_rlan_ctx_info);
	वापस ice_copy_rxq_ctx_to_hw(hw, ctx_buf, rxq_index);
पूर्ण

/* LAN Tx Queue Context */
स्थिर काष्ठा ice_ctx_ele ice_tlan_ctx_info[] = अणु
				    /* Field			Width	LSB */
	ICE_CTX_STORE(ice_tlan_ctx, base,			57,	0),
	ICE_CTX_STORE(ice_tlan_ctx, port_num,			3,	57),
	ICE_CTX_STORE(ice_tlan_ctx, cgd_num,			5,	60),
	ICE_CTX_STORE(ice_tlan_ctx, pf_num,			3,	65),
	ICE_CTX_STORE(ice_tlan_ctx, vmvf_num,			10,	68),
	ICE_CTX_STORE(ice_tlan_ctx, vmvf_type,			2,	78),
	ICE_CTX_STORE(ice_tlan_ctx, src_vsi,			10,	80),
	ICE_CTX_STORE(ice_tlan_ctx, tsyn_ena,			1,	90),
	ICE_CTX_STORE(ice_tlan_ctx, पूर्णांकernal_usage_flag,	1,	91),
	ICE_CTX_STORE(ice_tlan_ctx, alt_vlan,			1,	92),
	ICE_CTX_STORE(ice_tlan_ctx, cpuid,			8,	93),
	ICE_CTX_STORE(ice_tlan_ctx, wb_mode,			1,	101),
	ICE_CTX_STORE(ice_tlan_ctx, tphrd_desc,			1,	102),
	ICE_CTX_STORE(ice_tlan_ctx, tphrd,			1,	103),
	ICE_CTX_STORE(ice_tlan_ctx, tphwr_desc,			1,	104),
	ICE_CTX_STORE(ice_tlan_ctx, cmpq_id,			9,	105),
	ICE_CTX_STORE(ice_tlan_ctx, qnum_in_func,		14,	114),
	ICE_CTX_STORE(ice_tlan_ctx, itr_notअगरication_mode,	1,	128),
	ICE_CTX_STORE(ice_tlan_ctx, adjust_prof_id,		6,	129),
	ICE_CTX_STORE(ice_tlan_ctx, qlen,			13,	135),
	ICE_CTX_STORE(ice_tlan_ctx, quanta_prof_idx,		4,	148),
	ICE_CTX_STORE(ice_tlan_ctx, tso_ena,			1,	152),
	ICE_CTX_STORE(ice_tlan_ctx, tso_qnum,			11,	153),
	ICE_CTX_STORE(ice_tlan_ctx, legacy_पूर्णांक,			1,	164),
	ICE_CTX_STORE(ice_tlan_ctx, drop_ena,			1,	165),
	ICE_CTX_STORE(ice_tlan_ctx, cache_prof_idx,		2,	166),
	ICE_CTX_STORE(ice_tlan_ctx, pkt_shaper_prof_idx,	3,	168),
	ICE_CTX_STORE(ice_tlan_ctx, पूर्णांक_q_state,		122,	171),
	अणु 0 पूर्ण
पूर्ण;

/* FW Admin Queue command wrappers */

/* Software lock/mutex that is meant to be held जबतक the Global Config Lock
 * in firmware is acquired by the software to prevent most (but not all) types
 * of AQ commands from being sent to FW
 */
DEFINE_MUTEX(ice_global_cfg_lock_sw);

/**
 * ice_should_retry_sq_send_cmd
 * @opcode: AQ opcode
 *
 * Decide अगर we should retry the send command routine क्रम the ATQ, depending
 * on the opcode.
 */
अटल bool ice_should_retry_sq_send_cmd(u16 opcode)
अणु
	चयन (opcode) अणु
	हाल ice_aqc_opc_get_link_topo:
	हाल ice_aqc_opc_lldp_stop:
	हाल ice_aqc_opc_lldp_start:
	हाल ice_aqc_opc_lldp_filter_ctrl:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_sq_send_cmd_retry - send command to Control Queue (ATQ)
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cq: poपूर्णांकer to the specअगरic Control queue
 * @desc: prefilled descriptor describing the command
 * @buf: buffer to use क्रम indirect commands (or शून्य क्रम direct commands)
 * @buf_size: size of buffer क्रम indirect commands (or 0 क्रम direct commands)
 * @cd: poपूर्णांकer to command details काष्ठाure
 *
 * Retry sending the FW Admin Queue command, multiple बार, to the FW Admin
 * Queue अगर the EBUSY AQ error is वापसed.
 */
अटल क्रमागत ice_status
ice_sq_send_cmd_retry(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq,
		      काष्ठा ice_aq_desc *desc, व्योम *buf, u16 buf_size,
		      काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc_cpy;
	क्रमागत ice_status status;
	bool is_cmd_क्रम_retry;
	u8 *buf_cpy = शून्य;
	u8 idx = 0;
	u16 opcode;

	opcode = le16_to_cpu(desc->opcode);
	is_cmd_क्रम_retry = ice_should_retry_sq_send_cmd(opcode);
	स_रखो(&desc_cpy, 0, माप(desc_cpy));

	अगर (is_cmd_क्रम_retry) अणु
		अगर (buf) अणु
			buf_cpy = kzalloc(buf_size, GFP_KERNEL);
			अगर (!buf_cpy)
				वापस ICE_ERR_NO_MEMORY;
		पूर्ण

		स_नकल(&desc_cpy, desc, माप(desc_cpy));
	पूर्ण

	करो अणु
		status = ice_sq_send_cmd(hw, cq, desc, buf, buf_size, cd);

		अगर (!is_cmd_क्रम_retry || !status ||
		    hw->adminq.sq_last_status != ICE_AQ_RC_EBUSY)
			अवरोध;

		अगर (buf_cpy)
			स_नकल(buf, buf_cpy, buf_size);

		स_नकल(desc, &desc_cpy, माप(desc_cpy));

		mdelay(ICE_SQ_SEND_DELAY_TIME_MS);

	पूर्ण जबतक (++idx < ICE_SQ_SEND_MAX_EXECUTE);

	kमुक्त(buf_cpy);

	वापस status;
पूर्ण

/**
 * ice_aq_send_cmd - send FW Admin Queue command to FW Admin Queue
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @desc: descriptor describing the command
 * @buf: buffer to use क्रम indirect commands (शून्य क्रम direct commands)
 * @buf_size: size of buffer क्रम indirect commands (0 क्रम direct commands)
 * @cd: poपूर्णांकer to command details काष्ठाure
 *
 * Helper function to send FW Admin Queue commands to the FW Admin Queue.
 */
क्रमागत ice_status
ice_aq_send_cmd(काष्ठा ice_hw *hw, काष्ठा ice_aq_desc *desc, व्योम *buf,
		u16 buf_size, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_req_res *cmd = &desc->params.res_owner;
	bool lock_acquired = false;
	क्रमागत ice_status status;

	/* When a package करोwnload is in process (i.e. when the firmware's
	 * Global Configuration Lock resource is held), only the Download
	 * Package, Get Version, Get Package Info List and Release Resource
	 * (with resource ID set to Global Config Lock) AdminQ commands are
	 * allowed; all others must block until the package करोwnload completes
	 * and the Global Config Lock is released.  See also
	 * ice_acquire_global_cfg_lock().
	 */
	चयन (le16_to_cpu(desc->opcode)) अणु
	हाल ice_aqc_opc_करोwnload_pkg:
	हाल ice_aqc_opc_get_pkg_info_list:
	हाल ice_aqc_opc_get_ver:
		अवरोध;
	हाल ice_aqc_opc_release_res:
		अगर (le16_to_cpu(cmd->res_id) == ICE_AQC_RES_ID_GLBL_LOCK)
			अवरोध;
		fallthrough;
	शेष:
		mutex_lock(&ice_global_cfg_lock_sw);
		lock_acquired = true;
		अवरोध;
	पूर्ण

	status = ice_sq_send_cmd_retry(hw, &hw->adminq, desc, buf, buf_size, cd);
	अगर (lock_acquired)
		mutex_unlock(&ice_global_cfg_lock_sw);

	वापस status;
पूर्ण

/**
 * ice_aq_get_fw_ver
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get the firmware version (0x0001) from the admin queue commands
 */
क्रमागत ice_status ice_aq_get_fw_ver(काष्ठा ice_hw *hw, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_get_ver *resp;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	resp = &desc.params.get_ver;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_ver);

	status = ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);

	अगर (!status) अणु
		hw->fw_branch = resp->fw_branch;
		hw->fw_maj_ver = resp->fw_major;
		hw->fw_min_ver = resp->fw_minor;
		hw->fw_patch = resp->fw_patch;
		hw->fw_build = le32_to_cpu(resp->fw_build);
		hw->api_branch = resp->api_branch;
		hw->api_maj_ver = resp->api_major;
		hw->api_min_ver = resp->api_minor;
		hw->api_patch = resp->api_patch;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_send_driver_ver
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @dv: driver's major, minor version
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Send the driver version (0x0002) to the firmware
 */
क्रमागत ice_status
ice_aq_send_driver_ver(काष्ठा ice_hw *hw, काष्ठा ice_driver_ver *dv,
		       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_driver_ver *cmd;
	काष्ठा ice_aq_desc desc;
	u16 len;

	cmd = &desc.params.driver_ver;

	अगर (!dv)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_driver_ver);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	cmd->major_ver = dv->major_ver;
	cmd->minor_ver = dv->minor_ver;
	cmd->build_ver = dv->build_ver;
	cmd->subbuild_ver = dv->subbuild_ver;

	len = 0;
	जबतक (len < माप(dv->driver_string) &&
	       isascii(dv->driver_string[len]) && dv->driver_string[len])
		len++;

	वापस ice_aq_send_cmd(hw, &desc, dv->driver_string, len, cd);
पूर्ण

/**
 * ice_aq_q_shutकरोwn
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @unloading: is the driver unloading itself
 *
 * Tell the Firmware that we're shutting करोwn the AdminQ and whether
 * or not the driver is unloading as well (0x0003).
 */
क्रमागत ice_status ice_aq_q_shutकरोwn(काष्ठा ice_hw *hw, bool unloading)
अणु
	काष्ठा ice_aqc_q_shutकरोwn *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.q_shutकरोwn;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_q_shutकरोwn);

	अगर (unloading)
		cmd->driver_unloading = ICE_AQC_DRIVER_UNLOADING;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
पूर्ण

/**
 * ice_aq_req_res
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @res: resource ID
 * @access: access type
 * @sdp_number: resource number
 * @समयout: the maximum समय in ms that the driver may hold the resource
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Requests common resource using the admin queue commands (0x0008).
 * When attempting to acquire the Global Config Lock, the driver can
 * learn of three states:
 *  1) ICE_SUCCESS -        acquired lock, and can perक्रमm करोwnload package
 *  2) ICE_ERR_AQ_ERROR -   did not get lock, driver should fail to load
 *  3) ICE_ERR_AQ_NO_WORK - did not get lock, but another driver has
 *                          successfully करोwnloaded the package; the driver करोes
 *                          not have to करोwnload the package and can जारी
 *                          loading
 *
 * Note that अगर the caller is in an acquire lock, perक्रमm action, release lock
 * phase of operation, it is possible that the FW may detect a समयout and issue
 * a CORER. In this हाल, the driver will receive a CORER पूर्णांकerrupt and will
 * have to determine its cause. The calling thपढ़ो that is handling this flow
 * will likely get an error propagated back to it indicating the Download
 * Package, Update Package or the Release Resource AQ commands समयd out.
 */
अटल क्रमागत ice_status
ice_aq_req_res(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_ids res,
	       क्रमागत ice_aq_res_access_type access, u8 sdp_number, u32 *समयout,
	       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_req_res *cmd_resp;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd_resp = &desc.params.res_owner;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_req_res);

	cmd_resp->res_id = cpu_to_le16(res);
	cmd_resp->access_type = cpu_to_le16(access);
	cmd_resp->res_number = cpu_to_le32(sdp_number);
	cmd_resp->समयout = cpu_to_le32(*समयout);
	*समयout = 0;

	status = ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);

	/* The completion specअगरies the maximum समय in ms that the driver
	 * may hold the resource in the Timeout field.
	 */

	/* Global config lock response utilizes an additional status field.
	 *
	 * If the Global config lock resource is held by some other driver, the
	 * command completes with ICE_AQ_RES_GLBL_IN_PROG in the status field
	 * and the समयout field indicates the maximum समय the current owner
	 * of the resource has to मुक्त it.
	 */
	अगर (res == ICE_GLOBAL_CFG_LOCK_RES_ID) अणु
		अगर (le16_to_cpu(cmd_resp->status) == ICE_AQ_RES_GLBL_SUCCESS) अणु
			*समयout = le32_to_cpu(cmd_resp->समयout);
			वापस 0;
		पूर्ण अन्यथा अगर (le16_to_cpu(cmd_resp->status) ==
			   ICE_AQ_RES_GLBL_IN_PROG) अणु
			*समयout = le32_to_cpu(cmd_resp->समयout);
			वापस ICE_ERR_AQ_ERROR;
		पूर्ण अन्यथा अगर (le16_to_cpu(cmd_resp->status) ==
			   ICE_AQ_RES_GLBL_DONE) अणु
			वापस ICE_ERR_AQ_NO_WORK;
		पूर्ण

		/* invalid FW response, क्रमce a समयout immediately */
		*समयout = 0;
		वापस ICE_ERR_AQ_ERROR;
	पूर्ण

	/* If the resource is held by some other driver, the command completes
	 * with a busy वापस value and the समयout field indicates the maximum
	 * समय the current owner of the resource has to मुक्त it.
	 */
	अगर (!status || hw->adminq.sq_last_status == ICE_AQ_RC_EBUSY)
		*समयout = le32_to_cpu(cmd_resp->समयout);

	वापस status;
पूर्ण

/**
 * ice_aq_release_res
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @res: resource ID
 * @sdp_number: resource number
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * release common resource using the admin queue commands (0x0009)
 */
अटल क्रमागत ice_status
ice_aq_release_res(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_ids res, u8 sdp_number,
		   काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_req_res *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.res_owner;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_release_res);

	cmd->res_id = cpu_to_le16(res);
	cmd->res_number = cpu_to_le32(sdp_number);

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_acquire_res
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @res: resource ID
 * @access: access type (पढ़ो or ग_लिखो)
 * @समयout: समयout in milliseconds
 *
 * This function will attempt to acquire the ownership of a resource.
 */
क्रमागत ice_status
ice_acquire_res(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_ids res,
		क्रमागत ice_aq_res_access_type access, u32 समयout)
अणु
#घोषणा ICE_RES_POLLING_DELAY_MS	10
	u32 delay = ICE_RES_POLLING_DELAY_MS;
	u32 समय_left = समयout;
	क्रमागत ice_status status;

	status = ice_aq_req_res(hw, res, access, 0, &समय_left, शून्य);

	/* A वापस code of ICE_ERR_AQ_NO_WORK means that another driver has
	 * previously acquired the resource and perक्रमmed any necessary updates;
	 * in this हाल the caller करोes not obtain the resource and has no
	 * further work to करो.
	 */
	अगर (status == ICE_ERR_AQ_NO_WORK)
		जाओ ice_acquire_res_निकास;

	अगर (status)
		ice_debug(hw, ICE_DBG_RES, "resource %d acquire type %d failed.\n", res, access);

	/* If necessary, poll until the current lock owner समयouts */
	समयout = समय_left;
	जबतक (status && समयout && समय_left) अणु
		mdelay(delay);
		समयout = (समयout > delay) ? समयout - delay : 0;
		status = ice_aq_req_res(hw, res, access, 0, &समय_left, शून्य);

		अगर (status == ICE_ERR_AQ_NO_WORK)
			/* lock मुक्त, but no work to करो */
			अवरोध;

		अगर (!status)
			/* lock acquired */
			अवरोध;
	पूर्ण
	अगर (status && status != ICE_ERR_AQ_NO_WORK)
		ice_debug(hw, ICE_DBG_RES, "resource acquire timed out.\n");

ice_acquire_res_निकास:
	अगर (status == ICE_ERR_AQ_NO_WORK) अणु
		अगर (access == ICE_RES_WRITE)
			ice_debug(hw, ICE_DBG_RES, "resource indicates no work to do.\n");
		अन्यथा
			ice_debug(hw, ICE_DBG_RES, "Warning: ICE_ERR_AQ_NO_WORK not expected\n");
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_release_res
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @res: resource ID
 *
 * This function will release a resource using the proper Admin Command.
 */
व्योम ice_release_res(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_ids res)
अणु
	क्रमागत ice_status status;
	u32 total_delay = 0;

	status = ice_aq_release_res(hw, res, 0, शून्य);

	/* there are some rare हालs when trying to release the resource
	 * results in an admin queue समयout, so handle them correctly
	 */
	जबतक ((status == ICE_ERR_AQ_TIMEOUT) &&
	       (total_delay < hw->adminq.sq_cmd_समयout)) अणु
		mdelay(1);
		status = ice_aq_release_res(hw, res, 0, शून्य);
		total_delay++;
	पूर्ण
पूर्ण

/**
 * ice_aq_alloc_मुक्त_res - command to allocate/मुक्त resources
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @num_entries: number of resource entries in buffer
 * @buf: Indirect buffer to hold data parameters and response
 * @buf_size: size of buffer क्रम indirect commands
 * @opc: pass in the command opcode
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Helper function to allocate/मुक्त resources using the admin queue commands
 */
क्रमागत ice_status
ice_aq_alloc_मुक्त_res(काष्ठा ice_hw *hw, u16 num_entries,
		      काष्ठा ice_aqc_alloc_मुक्त_res_elem *buf, u16 buf_size,
		      क्रमागत ice_adminq_opc opc, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_alloc_मुक्त_res_cmd *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.sw_res_ctrl;

	अगर (!buf)
		वापस ICE_ERR_PARAM;

	अगर (buf_size < flex_array_size(buf, elem, num_entries))
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, opc);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	cmd->num_entries = cpu_to_le16(num_entries);

	वापस ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
पूर्ण

/**
 * ice_alloc_hw_res - allocate resource
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @type: type of resource
 * @num: number of resources to allocate
 * @bपंचांग: allocate from bottom
 * @res: poपूर्णांकer to array that will receive the resources
 */
क्रमागत ice_status
ice_alloc_hw_res(काष्ठा ice_hw *hw, u16 type, u16 num, bool bपंचांग, u16 *res)
अणु
	काष्ठा ice_aqc_alloc_मुक्त_res_elem *buf;
	क्रमागत ice_status status;
	u16 buf_len;

	buf_len = काष्ठा_size(buf, elem, num);
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	/* Prepare buffer to allocate resource. */
	buf->num_elems = cpu_to_le16(num);
	buf->res_type = cpu_to_le16(type | ICE_AQC_RES_TYPE_FLAG_DEDICATED |
				    ICE_AQC_RES_TYPE_FLAG_IGNORE_INDEX);
	अगर (bपंचांग)
		buf->res_type |= cpu_to_le16(ICE_AQC_RES_TYPE_FLAG_SCAN_BOTTOM);

	status = ice_aq_alloc_मुक्त_res(hw, 1, buf, buf_len,
				       ice_aqc_opc_alloc_res, शून्य);
	अगर (status)
		जाओ ice_alloc_res_निकास;

	स_नकल(res, buf->elem, माप(*buf->elem) * num);

ice_alloc_res_निकास:
	kमुक्त(buf);
	वापस status;
पूर्ण

/**
 * ice_मुक्त_hw_res - मुक्त allocated HW resource
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @type: type of resource to मुक्त
 * @num: number of resources
 * @res: poपूर्णांकer to array that contains the resources to मुक्त
 */
क्रमागत ice_status ice_मुक्त_hw_res(काष्ठा ice_hw *hw, u16 type, u16 num, u16 *res)
अणु
	काष्ठा ice_aqc_alloc_मुक्त_res_elem *buf;
	क्रमागत ice_status status;
	u16 buf_len;

	buf_len = काष्ठा_size(buf, elem, num);
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	/* Prepare buffer to मुक्त resource. */
	buf->num_elems = cpu_to_le16(num);
	buf->res_type = cpu_to_le16(type);
	स_नकल(buf->elem, res, माप(*buf->elem) * num);

	status = ice_aq_alloc_मुक्त_res(hw, num, buf, buf_len,
				       ice_aqc_opc_मुक्त_res, शून्य);
	अगर (status)
		ice_debug(hw, ICE_DBG_SW, "CQ CMD Buffer:\n");

	kमुक्त(buf);
	वापस status;
पूर्ण

/**
 * ice_get_num_per_func - determine number of resources per PF
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @max: value to be evenly split between each PF
 *
 * Determine the number of valid functions by going through the biपंचांगap वापसed
 * from parsing capabilities and use this to calculate the number of resources
 * per PF based on the max value passed in.
 */
अटल u32 ice_get_num_per_func(काष्ठा ice_hw *hw, u32 max)
अणु
	u8 funcs;

#घोषणा ICE_CAPS_VALID_FUNCS_M	0xFF
	funcs = hweight8(hw->dev_caps.common_cap.valid_functions &
			 ICE_CAPS_VALID_FUNCS_M);

	अगर (!funcs)
		वापस 0;

	वापस max / funcs;
पूर्ण

/**
 * ice_parse_common_caps - parse common device/function capabilities
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @caps: poपूर्णांकer to common capabilities काष्ठाure
 * @elem: the capability element to parse
 * @prefix: message prefix क्रम tracing capabilities
 *
 * Given a capability element, extract relevant details पूर्णांकo the common
 * capability काष्ठाure.
 *
 * Returns: true अगर the capability matches one of the common capability ids,
 * false otherwise.
 */
अटल bool
ice_parse_common_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_common_caps *caps,
		      काष्ठा ice_aqc_list_caps_elem *elem, स्थिर अक्षर *prefix)
अणु
	u32 logical_id = le32_to_cpu(elem->logical_id);
	u32 phys_id = le32_to_cpu(elem->phys_id);
	u32 number = le32_to_cpu(elem->number);
	u16 cap = le16_to_cpu(elem->cap);
	bool found = true;

	चयन (cap) अणु
	हाल ICE_AQC_CAPS_VALID_FUNCTIONS:
		caps->valid_functions = number;
		ice_debug(hw, ICE_DBG_INIT, "%s: valid_functions (bitmap) = %d\n", prefix,
			  caps->valid_functions);
		अवरोध;
	हाल ICE_AQC_CAPS_SRIOV:
		caps->sr_iov_1_1 = (number == 1);
		ice_debug(hw, ICE_DBG_INIT, "%s: sr_iov_1_1 = %d\n", prefix,
			  caps->sr_iov_1_1);
		अवरोध;
	हाल ICE_AQC_CAPS_DCB:
		caps->dcb = (number == 1);
		caps->active_tc_biपंचांगap = logical_id;
		caps->maxtc = phys_id;
		ice_debug(hw, ICE_DBG_INIT, "%s: dcb = %d\n", prefix, caps->dcb);
		ice_debug(hw, ICE_DBG_INIT, "%s: active_tc_bitmap = %d\n", prefix,
			  caps->active_tc_biपंचांगap);
		ice_debug(hw, ICE_DBG_INIT, "%s: maxtc = %d\n", prefix, caps->maxtc);
		अवरोध;
	हाल ICE_AQC_CAPS_RSS:
		caps->rss_table_size = number;
		caps->rss_table_entry_width = logical_id;
		ice_debug(hw, ICE_DBG_INIT, "%s: rss_table_size = %d\n", prefix,
			  caps->rss_table_size);
		ice_debug(hw, ICE_DBG_INIT, "%s: rss_table_entry_width = %d\n", prefix,
			  caps->rss_table_entry_width);
		अवरोध;
	हाल ICE_AQC_CAPS_RXQS:
		caps->num_rxq = number;
		caps->rxq_first_id = phys_id;
		ice_debug(hw, ICE_DBG_INIT, "%s: num_rxq = %d\n", prefix,
			  caps->num_rxq);
		ice_debug(hw, ICE_DBG_INIT, "%s: rxq_first_id = %d\n", prefix,
			  caps->rxq_first_id);
		अवरोध;
	हाल ICE_AQC_CAPS_TXQS:
		caps->num_txq = number;
		caps->txq_first_id = phys_id;
		ice_debug(hw, ICE_DBG_INIT, "%s: num_txq = %d\n", prefix,
			  caps->num_txq);
		ice_debug(hw, ICE_DBG_INIT, "%s: txq_first_id = %d\n", prefix,
			  caps->txq_first_id);
		अवरोध;
	हाल ICE_AQC_CAPS_MSIX:
		caps->num_msix_vectors = number;
		caps->msix_vector_first_id = phys_id;
		ice_debug(hw, ICE_DBG_INIT, "%s: num_msix_vectors = %d\n", prefix,
			  caps->num_msix_vectors);
		ice_debug(hw, ICE_DBG_INIT, "%s: msix_vector_first_id = %d\n", prefix,
			  caps->msix_vector_first_id);
		अवरोध;
	हाल ICE_AQC_CAPS_PENDING_NVM_VER:
		caps->nvm_update_pending_nvm = true;
		ice_debug(hw, ICE_DBG_INIT, "%s: update_pending_nvm\n", prefix);
		अवरोध;
	हाल ICE_AQC_CAPS_PENDING_OROM_VER:
		caps->nvm_update_pending_orom = true;
		ice_debug(hw, ICE_DBG_INIT, "%s: update_pending_orom\n", prefix);
		अवरोध;
	हाल ICE_AQC_CAPS_PENDING_NET_VER:
		caps->nvm_update_pending_netlist = true;
		ice_debug(hw, ICE_DBG_INIT, "%s: update_pending_netlist\n", prefix);
		अवरोध;
	हाल ICE_AQC_CAPS_NVM_MGMT:
		caps->nvm_unअगरied_update =
			(number & ICE_NVM_MGMT_UNIFIED_UPD_SUPPORT) ?
			true : false;
		ice_debug(hw, ICE_DBG_INIT, "%s: nvm_unified_update = %d\n", prefix,
			  caps->nvm_unअगरied_update);
		अवरोध;
	हाल ICE_AQC_CAPS_MAX_MTU:
		caps->max_mtu = number;
		ice_debug(hw, ICE_DBG_INIT, "%s: max_mtu = %d\n",
			  prefix, caps->max_mtu);
		अवरोध;
	शेष:
		/* Not one of the recognized common capabilities */
		found = false;
	पूर्ण

	वापस found;
पूर्ण

/**
 * ice_recalc_port_limited_caps - Recalculate port limited capabilities
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @caps: poपूर्णांकer to capabilities काष्ठाure to fix
 *
 * Re-calculate the capabilities that are dependent on the number of physical
 * ports; i.e. some features are not supported or function dअगरferently on
 * devices with more than 4 ports.
 */
अटल व्योम
ice_recalc_port_limited_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_common_caps *caps)
अणु
	/* This assumes device capabilities are always scanned beक्रमe function
	 * capabilities during the initialization flow.
	 */
	अगर (hw->dev_caps.num_funcs > 4) अणु
		/* Max 4 TCs per port */
		caps->maxtc = 4;
		ice_debug(hw, ICE_DBG_INIT, "reducing maxtc to %d (based on #ports)\n",
			  caps->maxtc);
	पूर्ण
पूर्ण

/**
 * ice_parse_vf_func_caps - Parse ICE_AQC_CAPS_VF function caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @func_p: poपूर्णांकer to function capabilities काष्ठाure
 * @cap: poपूर्णांकer to the capability element to parse
 *
 * Extract function capabilities क्रम ICE_AQC_CAPS_VF.
 */
अटल व्योम
ice_parse_vf_func_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_func_caps *func_p,
		       काष्ठा ice_aqc_list_caps_elem *cap)
अणु
	u32 logical_id = le32_to_cpu(cap->logical_id);
	u32 number = le32_to_cpu(cap->number);

	func_p->num_allocd_vfs = number;
	func_p->vf_base_id = logical_id;
	ice_debug(hw, ICE_DBG_INIT, "func caps: num_allocd_vfs = %d\n",
		  func_p->num_allocd_vfs);
	ice_debug(hw, ICE_DBG_INIT, "func caps: vf_base_id = %d\n",
		  func_p->vf_base_id);
पूर्ण

/**
 * ice_parse_vsi_func_caps - Parse ICE_AQC_CAPS_VSI function caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @func_p: poपूर्णांकer to function capabilities काष्ठाure
 * @cap: poपूर्णांकer to the capability element to parse
 *
 * Extract function capabilities क्रम ICE_AQC_CAPS_VSI.
 */
अटल व्योम
ice_parse_vsi_func_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_func_caps *func_p,
			काष्ठा ice_aqc_list_caps_elem *cap)
अणु
	func_p->guar_num_vsi = ice_get_num_per_func(hw, ICE_MAX_VSI);
	ice_debug(hw, ICE_DBG_INIT, "func caps: guar_num_vsi (fw) = %d\n",
		  le32_to_cpu(cap->number));
	ice_debug(hw, ICE_DBG_INIT, "func caps: guar_num_vsi = %d\n",
		  func_p->guar_num_vsi);
पूर्ण

/**
 * ice_parse_fdir_func_caps - Parse ICE_AQC_CAPS_FD function caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @func_p: poपूर्णांकer to function capabilities काष्ठाure
 *
 * Extract function capabilities क्रम ICE_AQC_CAPS_FD.
 */
अटल व्योम
ice_parse_fdir_func_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_func_caps *func_p)
अणु
	u32 reg_val, val;

	reg_val = rd32(hw, GLQF_FD_SIZE);
	val = (reg_val & GLQF_FD_SIZE_FD_GSIZE_M) >>
		GLQF_FD_SIZE_FD_GSIZE_S;
	func_p->fd_fltr_guar =
		ice_get_num_per_func(hw, val);
	val = (reg_val & GLQF_FD_SIZE_FD_BSIZE_M) >>
		GLQF_FD_SIZE_FD_BSIZE_S;
	func_p->fd_fltr_best_efक्रमt = val;

	ice_debug(hw, ICE_DBG_INIT, "func caps: fd_fltr_guar = %d\n",
		  func_p->fd_fltr_guar);
	ice_debug(hw, ICE_DBG_INIT, "func caps: fd_fltr_best_effort = %d\n",
		  func_p->fd_fltr_best_efक्रमt);
पूर्ण

/**
 * ice_parse_func_caps - Parse function capabilities
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @func_p: poपूर्णांकer to function capabilities काष्ठाure
 * @buf: buffer containing the function capability records
 * @cap_count: the number of capabilities
 *
 * Helper function to parse function (0x000A) capabilities list. For
 * capabilities shared between device and function, this relies on
 * ice_parse_common_caps.
 *
 * Loop through the list of provided capabilities and extract the relevant
 * data पूर्णांकo the function capabilities काष्ठाured.
 */
अटल व्योम
ice_parse_func_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_func_caps *func_p,
		    व्योम *buf, u32 cap_count)
अणु
	काष्ठा ice_aqc_list_caps_elem *cap_resp;
	u32 i;

	cap_resp = buf;

	स_रखो(func_p, 0, माप(*func_p));

	क्रम (i = 0; i < cap_count; i++) अणु
		u16 cap = le16_to_cpu(cap_resp[i].cap);
		bool found;

		found = ice_parse_common_caps(hw, &func_p->common_cap,
					      &cap_resp[i], "func caps");

		चयन (cap) अणु
		हाल ICE_AQC_CAPS_VF:
			ice_parse_vf_func_caps(hw, func_p, &cap_resp[i]);
			अवरोध;
		हाल ICE_AQC_CAPS_VSI:
			ice_parse_vsi_func_caps(hw, func_p, &cap_resp[i]);
			अवरोध;
		हाल ICE_AQC_CAPS_FD:
			ice_parse_fdir_func_caps(hw, func_p);
			अवरोध;
		शेष:
			/* Don't list common capabilities as unknown */
			अगर (!found)
				ice_debug(hw, ICE_DBG_INIT, "func caps: unknown capability[%d]: 0x%x\n",
					  i, cap);
			अवरोध;
		पूर्ण
	पूर्ण

	ice_recalc_port_limited_caps(hw, &func_p->common_cap);
पूर्ण

/**
 * ice_parse_valid_functions_cap - Parse ICE_AQC_CAPS_VALID_FUNCTIONS caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @dev_p: poपूर्णांकer to device capabilities काष्ठाure
 * @cap: capability element to parse
 *
 * Parse ICE_AQC_CAPS_VALID_FUNCTIONS क्रम device capabilities.
 */
अटल व्योम
ice_parse_valid_functions_cap(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_p,
			      काष्ठा ice_aqc_list_caps_elem *cap)
अणु
	u32 number = le32_to_cpu(cap->number);

	dev_p->num_funcs = hweight32(number);
	ice_debug(hw, ICE_DBG_INIT, "dev caps: num_funcs = %d\n",
		  dev_p->num_funcs);
पूर्ण

/**
 * ice_parse_vf_dev_caps - Parse ICE_AQC_CAPS_VF device caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @dev_p: poपूर्णांकer to device capabilities काष्ठाure
 * @cap: capability element to parse
 *
 * Parse ICE_AQC_CAPS_VF क्रम device capabilities.
 */
अटल व्योम
ice_parse_vf_dev_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_p,
		      काष्ठा ice_aqc_list_caps_elem *cap)
अणु
	u32 number = le32_to_cpu(cap->number);

	dev_p->num_vfs_exposed = number;
	ice_debug(hw, ICE_DBG_INIT, "dev_caps: num_vfs_exposed = %d\n",
		  dev_p->num_vfs_exposed);
पूर्ण

/**
 * ice_parse_vsi_dev_caps - Parse ICE_AQC_CAPS_VSI device caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @dev_p: poपूर्णांकer to device capabilities काष्ठाure
 * @cap: capability element to parse
 *
 * Parse ICE_AQC_CAPS_VSI क्रम device capabilities.
 */
अटल व्योम
ice_parse_vsi_dev_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_p,
		       काष्ठा ice_aqc_list_caps_elem *cap)
अणु
	u32 number = le32_to_cpu(cap->number);

	dev_p->num_vsi_allocd_to_host = number;
	ice_debug(hw, ICE_DBG_INIT, "dev caps: num_vsi_allocd_to_host = %d\n",
		  dev_p->num_vsi_allocd_to_host);
पूर्ण

/**
 * ice_parse_fdir_dev_caps - Parse ICE_AQC_CAPS_FD device caps
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @dev_p: poपूर्णांकer to device capabilities काष्ठाure
 * @cap: capability element to parse
 *
 * Parse ICE_AQC_CAPS_FD क्रम device capabilities.
 */
अटल व्योम
ice_parse_fdir_dev_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_p,
			काष्ठा ice_aqc_list_caps_elem *cap)
अणु
	u32 number = le32_to_cpu(cap->number);

	dev_p->num_flow_director_fltr = number;
	ice_debug(hw, ICE_DBG_INIT, "dev caps: num_flow_director_fltr = %d\n",
		  dev_p->num_flow_director_fltr);
पूर्ण

/**
 * ice_parse_dev_caps - Parse device capabilities
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @dev_p: poपूर्णांकer to device capabilities काष्ठाure
 * @buf: buffer containing the device capability records
 * @cap_count: the number of capabilities
 *
 * Helper device to parse device (0x000B) capabilities list. For
 * capabilities shared between device and function, this relies on
 * ice_parse_common_caps.
 *
 * Loop through the list of provided capabilities and extract the relevant
 * data पूर्णांकo the device capabilities काष्ठाured.
 */
अटल व्योम
ice_parse_dev_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_p,
		   व्योम *buf, u32 cap_count)
अणु
	काष्ठा ice_aqc_list_caps_elem *cap_resp;
	u32 i;

	cap_resp = buf;

	स_रखो(dev_p, 0, माप(*dev_p));

	क्रम (i = 0; i < cap_count; i++) अणु
		u16 cap = le16_to_cpu(cap_resp[i].cap);
		bool found;

		found = ice_parse_common_caps(hw, &dev_p->common_cap,
					      &cap_resp[i], "dev caps");

		चयन (cap) अणु
		हाल ICE_AQC_CAPS_VALID_FUNCTIONS:
			ice_parse_valid_functions_cap(hw, dev_p, &cap_resp[i]);
			अवरोध;
		हाल ICE_AQC_CAPS_VF:
			ice_parse_vf_dev_caps(hw, dev_p, &cap_resp[i]);
			अवरोध;
		हाल ICE_AQC_CAPS_VSI:
			ice_parse_vsi_dev_caps(hw, dev_p, &cap_resp[i]);
			अवरोध;
		हाल  ICE_AQC_CAPS_FD:
			ice_parse_fdir_dev_caps(hw, dev_p, &cap_resp[i]);
			अवरोध;
		शेष:
			/* Don't list common capabilities as unknown */
			अगर (!found)
				ice_debug(hw, ICE_DBG_INIT, "dev caps: unknown capability[%d]: 0x%x\n",
					  i, cap);
			अवरोध;
		पूर्ण
	पूर्ण

	ice_recalc_port_limited_caps(hw, &dev_p->common_cap);
पूर्ण

/**
 * ice_aq_list_caps - query function/device capabilities
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @buf: a buffer to hold the capabilities
 * @buf_size: size of the buffer
 * @cap_count: अगर not शून्य, set to the number of capabilities reported
 * @opc: capabilities type to discover, device or function
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get the function (0x000A) or device (0x000B) capabilities description from
 * firmware and store it in the buffer.
 *
 * If the cap_count poपूर्णांकer is not शून्य, then it is set to the number of
 * capabilities firmware will report. Note that अगर the buffer size is too
 * small, it is possible the command will वापस ICE_AQ_ERR_ENOMEM. The
 * cap_count will still be updated in this हाल. It is recommended that the
 * buffer size be set to ICE_AQ_MAX_BUF_LEN (the largest possible buffer that
 * firmware could वापस) to aव्योम this.
 */
क्रमागत ice_status
ice_aq_list_caps(काष्ठा ice_hw *hw, व्योम *buf, u16 buf_size, u32 *cap_count,
		 क्रमागत ice_adminq_opc opc, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_list_caps *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.get_cap;

	अगर (opc != ice_aqc_opc_list_func_caps &&
	    opc != ice_aqc_opc_list_dev_caps)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, opc);
	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);

	अगर (cap_count)
		*cap_count = le32_to_cpu(cmd->count);

	वापस status;
पूर्ण

/**
 * ice_discover_dev_caps - Read and extract device capabilities
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @dev_caps: poपूर्णांकer to device capabilities काष्ठाure
 *
 * Read the device capabilities and extract them पूर्णांकo the dev_caps काष्ठाure
 * क्रम later use.
 */
क्रमागत ice_status
ice_discover_dev_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_dev_caps *dev_caps)
अणु
	क्रमागत ice_status status;
	u32 cap_count = 0;
	व्योम *cbuf;

	cbuf = kzalloc(ICE_AQ_MAX_BUF_LEN, GFP_KERNEL);
	अगर (!cbuf)
		वापस ICE_ERR_NO_MEMORY;

	/* Although the driver करोesn't know the number of capabilities the
	 * device will वापस, we can simply send a 4KB buffer, the maximum
	 * possible size that firmware can वापस.
	 */
	cap_count = ICE_AQ_MAX_BUF_LEN / माप(काष्ठा ice_aqc_list_caps_elem);

	status = ice_aq_list_caps(hw, cbuf, ICE_AQ_MAX_BUF_LEN, &cap_count,
				  ice_aqc_opc_list_dev_caps, शून्य);
	अगर (!status)
		ice_parse_dev_caps(hw, dev_caps, cbuf, cap_count);
	kमुक्त(cbuf);

	वापस status;
पूर्ण

/**
 * ice_discover_func_caps - Read and extract function capabilities
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @func_caps: poपूर्णांकer to function capabilities काष्ठाure
 *
 * Read the function capabilities and extract them पूर्णांकo the func_caps काष्ठाure
 * क्रम later use.
 */
अटल क्रमागत ice_status
ice_discover_func_caps(काष्ठा ice_hw *hw, काष्ठा ice_hw_func_caps *func_caps)
अणु
	क्रमागत ice_status status;
	u32 cap_count = 0;
	व्योम *cbuf;

	cbuf = kzalloc(ICE_AQ_MAX_BUF_LEN, GFP_KERNEL);
	अगर (!cbuf)
		वापस ICE_ERR_NO_MEMORY;

	/* Although the driver करोesn't know the number of capabilities the
	 * device will वापस, we can simply send a 4KB buffer, the maximum
	 * possible size that firmware can वापस.
	 */
	cap_count = ICE_AQ_MAX_BUF_LEN / माप(काष्ठा ice_aqc_list_caps_elem);

	status = ice_aq_list_caps(hw, cbuf, ICE_AQ_MAX_BUF_LEN, &cap_count,
				  ice_aqc_opc_list_func_caps, शून्य);
	अगर (!status)
		ice_parse_func_caps(hw, func_caps, cbuf, cap_count);
	kमुक्त(cbuf);

	वापस status;
पूर्ण

/**
 * ice_set_safe_mode_caps - Override dev/func capabilities when in safe mode
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
व्योम ice_set_safe_mode_caps(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_hw_func_caps *func_caps = &hw->func_caps;
	काष्ठा ice_hw_dev_caps *dev_caps = &hw->dev_caps;
	काष्ठा ice_hw_common_caps cached_caps;
	u32 num_funcs;

	/* cache some func_caps values that should be restored after स_रखो */
	cached_caps = func_caps->common_cap;

	/* unset func capabilities */
	स_रखो(func_caps, 0, माप(*func_caps));

#घोषणा ICE_RESTORE_FUNC_CAP(name) \
	func_caps->common_cap.name = cached_caps.name

	/* restore cached values */
	ICE_RESTORE_FUNC_CAP(valid_functions);
	ICE_RESTORE_FUNC_CAP(txq_first_id);
	ICE_RESTORE_FUNC_CAP(rxq_first_id);
	ICE_RESTORE_FUNC_CAP(msix_vector_first_id);
	ICE_RESTORE_FUNC_CAP(max_mtu);
	ICE_RESTORE_FUNC_CAP(nvm_unअगरied_update);
	ICE_RESTORE_FUNC_CAP(nvm_update_pending_nvm);
	ICE_RESTORE_FUNC_CAP(nvm_update_pending_orom);
	ICE_RESTORE_FUNC_CAP(nvm_update_pending_netlist);

	/* one Tx and one Rx queue in safe mode */
	func_caps->common_cap.num_rxq = 1;
	func_caps->common_cap.num_txq = 1;

	/* two MSIX vectors, one क्रम traffic and one क्रम misc causes */
	func_caps->common_cap.num_msix_vectors = 2;
	func_caps->guar_num_vsi = 1;

	/* cache some dev_caps values that should be restored after स_रखो */
	cached_caps = dev_caps->common_cap;
	num_funcs = dev_caps->num_funcs;

	/* unset dev capabilities */
	स_रखो(dev_caps, 0, माप(*dev_caps));

#घोषणा ICE_RESTORE_DEV_CAP(name) \
	dev_caps->common_cap.name = cached_caps.name

	/* restore cached values */
	ICE_RESTORE_DEV_CAP(valid_functions);
	ICE_RESTORE_DEV_CAP(txq_first_id);
	ICE_RESTORE_DEV_CAP(rxq_first_id);
	ICE_RESTORE_DEV_CAP(msix_vector_first_id);
	ICE_RESTORE_DEV_CAP(max_mtu);
	ICE_RESTORE_DEV_CAP(nvm_unअगरied_update);
	ICE_RESTORE_DEV_CAP(nvm_update_pending_nvm);
	ICE_RESTORE_DEV_CAP(nvm_update_pending_orom);
	ICE_RESTORE_DEV_CAP(nvm_update_pending_netlist);
	dev_caps->num_funcs = num_funcs;

	/* one Tx and one Rx queue per function in safe mode */
	dev_caps->common_cap.num_rxq = num_funcs;
	dev_caps->common_cap.num_txq = num_funcs;

	/* two MSIX vectors per function */
	dev_caps->common_cap.num_msix_vectors = 2 * num_funcs;
पूर्ण

/**
 * ice_get_caps - get info about the HW
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
क्रमागत ice_status ice_get_caps(काष्ठा ice_hw *hw)
अणु
	क्रमागत ice_status status;

	status = ice_discover_dev_caps(hw, &hw->dev_caps);
	अगर (status)
		वापस status;

	वापस ice_discover_func_caps(hw, &hw->func_caps);
पूर्ण

/**
 * ice_aq_manage_mac_ग_लिखो - manage MAC address ग_लिखो command
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @mac_addr: MAC address to be written as LAA/LAA+WoL/Port address
 * @flags: flags to control ग_लिखो behavior
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This function is used to ग_लिखो MAC address to the NVM (0x0108).
 */
क्रमागत ice_status
ice_aq_manage_mac_ग_लिखो(काष्ठा ice_hw *hw, स्थिर u8 *mac_addr, u8 flags,
			काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_manage_mac_ग_लिखो *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.mac_ग_लिखो;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_manage_mac_ग_लिखो);

	cmd->flags = flags;
	ether_addr_copy(cmd->mac_addr, mac_addr);

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_clear_pxe_mode
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Tell the firmware that the driver is taking over from PXE (0x0110).
 */
अटल क्रमागत ice_status ice_aq_clear_pxe_mode(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_clear_pxe_mode);
	desc.params.clear_pxe.rx_cnt = ICE_AQC_CLEAR_PXE_RX_CNT;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
पूर्ण

/**
 * ice_clear_pxe_mode - clear pxe operations mode
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Make sure all PXE mode settings are cleared, including things
 * like descriptor fetch/ग_लिखो-back mode.
 */
व्योम ice_clear_pxe_mode(काष्ठा ice_hw *hw)
अणु
	अगर (ice_check_sq_alive(hw, &hw->adminq))
		ice_aq_clear_pxe_mode(hw);
पूर्ण

/**
 * ice_get_link_speed_based_on_phy_type - वापसs link speed
 * @phy_type_low: lower part of phy_type
 * @phy_type_high: higher part of phy_type
 *
 * This helper function will convert an entry in PHY type काष्ठाure
 * [phy_type_low, phy_type_high] to its corresponding link speed.
 * Note: In the काष्ठाure of [phy_type_low, phy_type_high], there should
 * be one bit set, as this function will convert one PHY type to its
 * speed.
 * If no bit माला_लो set, ICE_LINK_SPEED_UNKNOWN will be वापसed
 * If more than one bit माला_लो set, ICE_LINK_SPEED_UNKNOWN will be वापसed
 */
अटल u16
ice_get_link_speed_based_on_phy_type(u64 phy_type_low, u64 phy_type_high)
अणु
	u16 speed_phy_type_high = ICE_AQ_LINK_SPEED_UNKNOWN;
	u16 speed_phy_type_low = ICE_AQ_LINK_SPEED_UNKNOWN;

	चयन (phy_type_low) अणु
	हाल ICE_PHY_TYPE_LOW_100BASE_TX:
	हाल ICE_PHY_TYPE_LOW_100M_SGMII:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_100MB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_1000BASE_T:
	हाल ICE_PHY_TYPE_LOW_1000BASE_SX:
	हाल ICE_PHY_TYPE_LOW_1000BASE_LX:
	हाल ICE_PHY_TYPE_LOW_1000BASE_KX:
	हाल ICE_PHY_TYPE_LOW_1G_SGMII:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_1000MB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_2500BASE_T:
	हाल ICE_PHY_TYPE_LOW_2500BASE_X:
	हाल ICE_PHY_TYPE_LOW_2500BASE_KX:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_2500MB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_5GBASE_T:
	हाल ICE_PHY_TYPE_LOW_5GBASE_KR:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_5GB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_10GBASE_T:
	हाल ICE_PHY_TYPE_LOW_10G_SFI_DA:
	हाल ICE_PHY_TYPE_LOW_10GBASE_SR:
	हाल ICE_PHY_TYPE_LOW_10GBASE_LR:
	हाल ICE_PHY_TYPE_LOW_10GBASE_KR_CR1:
	हाल ICE_PHY_TYPE_LOW_10G_SFI_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_10G_SFI_C2C:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_10GB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_25GBASE_T:
	हाल ICE_PHY_TYPE_LOW_25GBASE_CR:
	हाल ICE_PHY_TYPE_LOW_25GBASE_CR_S:
	हाल ICE_PHY_TYPE_LOW_25GBASE_CR1:
	हाल ICE_PHY_TYPE_LOW_25GBASE_SR:
	हाल ICE_PHY_TYPE_LOW_25GBASE_LR:
	हाल ICE_PHY_TYPE_LOW_25GBASE_KR:
	हाल ICE_PHY_TYPE_LOW_25GBASE_KR_S:
	हाल ICE_PHY_TYPE_LOW_25GBASE_KR1:
	हाल ICE_PHY_TYPE_LOW_25G_AUI_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_25G_AUI_C2C:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_25GB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_40GBASE_CR4:
	हाल ICE_PHY_TYPE_LOW_40GBASE_SR4:
	हाल ICE_PHY_TYPE_LOW_40GBASE_LR4:
	हाल ICE_PHY_TYPE_LOW_40GBASE_KR4:
	हाल ICE_PHY_TYPE_LOW_40G_XLAUI_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_40G_XLAUI:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_40GB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_50GBASE_CR2:
	हाल ICE_PHY_TYPE_LOW_50GBASE_SR2:
	हाल ICE_PHY_TYPE_LOW_50GBASE_LR2:
	हाल ICE_PHY_TYPE_LOW_50GBASE_KR2:
	हाल ICE_PHY_TYPE_LOW_50G_LAUI2_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_50G_LAUI2:
	हाल ICE_PHY_TYPE_LOW_50G_AUI2_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_50G_AUI2:
	हाल ICE_PHY_TYPE_LOW_50GBASE_CP:
	हाल ICE_PHY_TYPE_LOW_50GBASE_SR:
	हाल ICE_PHY_TYPE_LOW_50GBASE_FR:
	हाल ICE_PHY_TYPE_LOW_50GBASE_LR:
	हाल ICE_PHY_TYPE_LOW_50GBASE_KR_PAM4:
	हाल ICE_PHY_TYPE_LOW_50G_AUI1_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_50G_AUI1:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_50GB;
		अवरोध;
	हाल ICE_PHY_TYPE_LOW_100GBASE_CR4:
	हाल ICE_PHY_TYPE_LOW_100GBASE_SR4:
	हाल ICE_PHY_TYPE_LOW_100GBASE_LR4:
	हाल ICE_PHY_TYPE_LOW_100GBASE_KR4:
	हाल ICE_PHY_TYPE_LOW_100G_CAUI4_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_100G_CAUI4:
	हाल ICE_PHY_TYPE_LOW_100G_AUI4_AOC_ACC:
	हाल ICE_PHY_TYPE_LOW_100G_AUI4:
	हाल ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4:
	हाल ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4:
	हाल ICE_PHY_TYPE_LOW_100GBASE_CP2:
	हाल ICE_PHY_TYPE_LOW_100GBASE_SR2:
	हाल ICE_PHY_TYPE_LOW_100GBASE_DR:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_100GB;
		अवरोध;
	शेष:
		speed_phy_type_low = ICE_AQ_LINK_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	चयन (phy_type_high) अणु
	हाल ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4:
	हाल ICE_PHY_TYPE_HIGH_100G_CAUI2_AOC_ACC:
	हाल ICE_PHY_TYPE_HIGH_100G_CAUI2:
	हाल ICE_PHY_TYPE_HIGH_100G_AUI2_AOC_ACC:
	हाल ICE_PHY_TYPE_HIGH_100G_AUI2:
		speed_phy_type_high = ICE_AQ_LINK_SPEED_100GB;
		अवरोध;
	शेष:
		speed_phy_type_high = ICE_AQ_LINK_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	अगर (speed_phy_type_low == ICE_AQ_LINK_SPEED_UNKNOWN &&
	    speed_phy_type_high == ICE_AQ_LINK_SPEED_UNKNOWN)
		वापस ICE_AQ_LINK_SPEED_UNKNOWN;
	अन्यथा अगर (speed_phy_type_low != ICE_AQ_LINK_SPEED_UNKNOWN &&
		 speed_phy_type_high != ICE_AQ_LINK_SPEED_UNKNOWN)
		वापस ICE_AQ_LINK_SPEED_UNKNOWN;
	अन्यथा अगर (speed_phy_type_low != ICE_AQ_LINK_SPEED_UNKNOWN &&
		 speed_phy_type_high == ICE_AQ_LINK_SPEED_UNKNOWN)
		वापस speed_phy_type_low;
	अन्यथा
		वापस speed_phy_type_high;
पूर्ण

/**
 * ice_update_phy_type
 * @phy_type_low: poपूर्णांकer to the lower part of phy_type
 * @phy_type_high: poपूर्णांकer to the higher part of phy_type
 * @link_speeds_biपंचांगap: targeted link speeds biपंचांगap
 *
 * Note: For the link_speeds_biपंचांगap काष्ठाure, you can check it at
 * [ice_aqc_get_link_status->link_speed]. Caller can pass in
 * link_speeds_biपंचांगap include multiple speeds.
 *
 * Each entry in this [phy_type_low, phy_type_high] काष्ठाure will
 * present a certain link speed. This helper function will turn on bits
 * in [phy_type_low, phy_type_high] काष्ठाure based on the value of
 * link_speeds_biपंचांगap input parameter.
 */
व्योम
ice_update_phy_type(u64 *phy_type_low, u64 *phy_type_high,
		    u16 link_speeds_biपंचांगap)
अणु
	u64 pt_high;
	u64 pt_low;
	पूर्णांक index;
	u16 speed;

	/* We first check with low part of phy_type */
	क्रम (index = 0; index <= ICE_PHY_TYPE_LOW_MAX_INDEX; index++) अणु
		pt_low = BIT_ULL(index);
		speed = ice_get_link_speed_based_on_phy_type(pt_low, 0);

		अगर (link_speeds_biपंचांगap & speed)
			*phy_type_low |= BIT_ULL(index);
	पूर्ण

	/* We then check with high part of phy_type */
	क्रम (index = 0; index <= ICE_PHY_TYPE_HIGH_MAX_INDEX; index++) अणु
		pt_high = BIT_ULL(index);
		speed = ice_get_link_speed_based_on_phy_type(0, pt_high);

		अगर (link_speeds_biपंचांगap & speed)
			*phy_type_high |= BIT_ULL(index);
	पूर्ण
पूर्ण

/**
 * ice_aq_set_phy_cfg
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @pi: port info काष्ठाure of the पूर्णांकerested logical port
 * @cfg: काष्ठाure with PHY configuration data to be set
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set the various PHY configuration parameters supported on the Port.
 * One or more of the Set PHY config parameters may be ignored in an MFP
 * mode as the PF may not have the privilege to set some of the PHY Config
 * parameters. This status will be indicated by the command response (0x0601).
 */
क्रमागत ice_status
ice_aq_set_phy_cfg(काष्ठा ice_hw *hw, काष्ठा ice_port_info *pi,
		   काष्ठा ice_aqc_set_phy_cfg_data *cfg, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (!cfg)
		वापस ICE_ERR_PARAM;

	/* Ensure that only valid bits of cfg->caps can be turned on. */
	अगर (cfg->caps & ~ICE_AQ_PHY_ENA_VALID_MASK) अणु
		ice_debug(hw, ICE_DBG_PHY, "Invalid bit is set in ice_aqc_set_phy_cfg_data->caps : 0x%x\n",
			  cfg->caps);

		cfg->caps &= ICE_AQ_PHY_ENA_VALID_MASK;
	पूर्ण

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_phy_cfg);
	desc.params.set_phy.lport_num = pi->lport;
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	ice_debug(hw, ICE_DBG_LINK, "set phy cfg\n");
	ice_debug(hw, ICE_DBG_LINK, "	phy_type_low = 0x%llx\n",
		  (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(cfg->phy_type_low));
	ice_debug(hw, ICE_DBG_LINK, "	phy_type_high = 0x%llx\n",
		  (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(cfg->phy_type_high));
	ice_debug(hw, ICE_DBG_LINK, "	caps = 0x%x\n", cfg->caps);
	ice_debug(hw, ICE_DBG_LINK, "	low_power_ctrl_an = 0x%x\n",
		  cfg->low_घातer_ctrl_an);
	ice_debug(hw, ICE_DBG_LINK, "	eee_cap = 0x%x\n", cfg->eee_cap);
	ice_debug(hw, ICE_DBG_LINK, "	eeer_value = 0x%x\n", cfg->eeer_value);
	ice_debug(hw, ICE_DBG_LINK, "	link_fec_opt = 0x%x\n",
		  cfg->link_fec_opt);

	status = ice_aq_send_cmd(hw, &desc, cfg, माप(*cfg), cd);
	अगर (hw->adminq.sq_last_status == ICE_AQ_RC_EMODE)
		status = 0;

	अगर (!status)
		pi->phy.curr_user_phy_cfg = *cfg;

	वापस status;
पूर्ण

/**
 * ice_update_link_info - update status of the HW network link
 * @pi: port info काष्ठाure of the पूर्णांकerested logical port
 */
क्रमागत ice_status ice_update_link_info(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_link_status *li;
	क्रमागत ice_status status;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	li = &pi->phy.link_info;

	status = ice_aq_get_link_info(pi, true, शून्य, शून्य);
	अगर (status)
		वापस status;

	अगर (li->link_info & ICE_AQ_MEDIA_AVAILABLE) अणु
		काष्ठा ice_aqc_get_phy_caps_data *pcaps;
		काष्ठा ice_hw *hw;

		hw = pi->hw;
		pcaps = devm_kzalloc(ice_hw_to_dev(hw), माप(*pcaps),
				     GFP_KERNEL);
		अगर (!pcaps)
			वापस ICE_ERR_NO_MEMORY;

		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP_MEDIA,
					     pcaps, शून्य);

		devm_kमुक्त(ice_hw_to_dev(hw), pcaps);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_cache_phy_user_req
 * @pi: port inक्रमmation काष्ठाure
 * @cache_data: PHY logging data
 * @cache_mode: PHY logging mode
 *
 * Log the user request on (FC, FEC, SPEED) क्रम later use.
 */
अटल व्योम
ice_cache_phy_user_req(काष्ठा ice_port_info *pi,
		       काष्ठा ice_phy_cache_mode_data cache_data,
		       क्रमागत ice_phy_cache_mode cache_mode)
अणु
	अगर (!pi)
		वापस;

	चयन (cache_mode) अणु
	हाल ICE_FC_MODE:
		pi->phy.curr_user_fc_req = cache_data.data.curr_user_fc_req;
		अवरोध;
	हाल ICE_SPEED_MODE:
		pi->phy.curr_user_speed_req =
			cache_data.data.curr_user_speed_req;
		अवरोध;
	हाल ICE_FEC_MODE:
		pi->phy.curr_user_fec_req = cache_data.data.curr_user_fec_req;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_caps_to_fc_mode
 * @caps: PHY capabilities
 *
 * Convert PHY FC capabilities to ice FC mode
 */
क्रमागत ice_fc_mode ice_caps_to_fc_mode(u8 caps)
अणु
	अगर (caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE &&
	    caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE)
		वापस ICE_FC_FULL;

	अगर (caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE)
		वापस ICE_FC_TX_PAUSE;

	अगर (caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE)
		वापस ICE_FC_RX_PAUSE;

	वापस ICE_FC_NONE;
पूर्ण

/**
 * ice_caps_to_fec_mode
 * @caps: PHY capabilities
 * @fec_options: Link FEC options
 *
 * Convert PHY FEC capabilities to ice FEC mode
 */
क्रमागत ice_fec_mode ice_caps_to_fec_mode(u8 caps, u8 fec_options)
अणु
	अगर (caps & ICE_AQC_PHY_EN_AUTO_FEC)
		वापस ICE_FEC_AUTO;

	अगर (fec_options & (ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN |
			   ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ |
			   ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN |
			   ICE_AQC_PHY_FEC_25G_KR_REQ))
		वापस ICE_FEC_BASER;

	अगर (fec_options & (ICE_AQC_PHY_FEC_25G_RS_528_REQ |
			   ICE_AQC_PHY_FEC_25G_RS_544_REQ |
			   ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN))
		वापस ICE_FEC_RS;

	वापस ICE_FEC_NONE;
पूर्ण

/**
 * ice_cfg_phy_fc - Configure PHY FC data based on FC mode
 * @pi: port inक्रमmation काष्ठाure
 * @cfg: PHY configuration data to set FC mode
 * @req_mode: FC mode to configure
 */
क्रमागत ice_status
ice_cfg_phy_fc(काष्ठा ice_port_info *pi, काष्ठा ice_aqc_set_phy_cfg_data *cfg,
	       क्रमागत ice_fc_mode req_mode)
अणु
	काष्ठा ice_phy_cache_mode_data cache_data;
	u8 छोड़ो_mask = 0x0;

	अगर (!pi || !cfg)
		वापस ICE_ERR_BAD_PTR;

	चयन (req_mode) अणु
	हाल ICE_FC_FULL:
		छोड़ो_mask |= ICE_AQC_PHY_EN_TX_LINK_PAUSE;
		छोड़ो_mask |= ICE_AQC_PHY_EN_RX_LINK_PAUSE;
		अवरोध;
	हाल ICE_FC_RX_PAUSE:
		छोड़ो_mask |= ICE_AQC_PHY_EN_RX_LINK_PAUSE;
		अवरोध;
	हाल ICE_FC_TX_PAUSE:
		छोड़ो_mask |= ICE_AQC_PHY_EN_TX_LINK_PAUSE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* clear the old छोड़ो settings */
	cfg->caps &= ~(ICE_AQC_PHY_EN_TX_LINK_PAUSE |
		ICE_AQC_PHY_EN_RX_LINK_PAUSE);

	/* set the new capabilities */
	cfg->caps |= छोड़ो_mask;

	/* Cache user FC request */
	cache_data.data.curr_user_fc_req = req_mode;
	ice_cache_phy_user_req(pi, cache_data, ICE_FC_MODE);

	वापस 0;
पूर्ण

/**
 * ice_set_fc
 * @pi: port inक्रमmation काष्ठाure
 * @aq_failures: poपूर्णांकer to status code, specअगरic to ice_set_fc routine
 * @ena_स्वतः_link_update: enable स्वतःmatic link update
 *
 * Set the requested flow control mode.
 */
क्रमागत ice_status
ice_set_fc(काष्ठा ice_port_info *pi, u8 *aq_failures, bool ena_स्वतः_link_update)
अणु
	काष्ठा ice_aqc_set_phy_cfg_data cfg = अणु 0 पूर्ण;
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;

	अगर (!pi || !aq_failures)
		वापस ICE_ERR_BAD_PTR;

	*aq_failures = 0;
	hw = pi->hw;

	pcaps = devm_kzalloc(ice_hw_to_dev(hw), माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस ICE_ERR_NO_MEMORY;

	/* Get the current PHY config */
	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_ACTIVE_CFG,
				     pcaps, शून्य);
	अगर (status) अणु
		*aq_failures = ICE_SET_FC_AQ_FAIL_GET;
		जाओ out;
	पूर्ण

	ice_copy_phy_caps_to_cfg(pi, pcaps, &cfg);

	/* Configure the set PHY data */
	status = ice_cfg_phy_fc(pi, &cfg, pi->fc.req_mode);
	अगर (status)
		जाओ out;

	/* If the capabilities have changed, then set the new config */
	अगर (cfg.caps != pcaps->caps) अणु
		पूर्णांक retry_count, retry_max = 10;

		/* Auto restart link so settings take effect */
		अगर (ena_स्वतः_link_update)
			cfg.caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;

		status = ice_aq_set_phy_cfg(hw, pi, &cfg, शून्य);
		अगर (status) अणु
			*aq_failures = ICE_SET_FC_AQ_FAIL_SET;
			जाओ out;
		पूर्ण

		/* Update the link info
		 * It someबार takes a really दीर्घ समय क्रम link to
		 * come back from the atomic reset. Thus, we रुको a
		 * little bit.
		 */
		क्रम (retry_count = 0; retry_count < retry_max; retry_count++) अणु
			status = ice_update_link_info(pi);

			अगर (!status)
				अवरोध;

			mdelay(100);
		पूर्ण

		अगर (status)
			*aq_failures = ICE_SET_FC_AQ_FAIL_UPDATE;
	पूर्ण

out:
	devm_kमुक्त(ice_hw_to_dev(hw), pcaps);
	वापस status;
पूर्ण

/**
 * ice_phy_caps_equals_cfg
 * @phy_caps: PHY capabilities
 * @phy_cfg: PHY configuration
 *
 * Helper function to determine अगर PHY capabilities matches PHY
 * configuration
 */
bool
ice_phy_caps_equals_cfg(काष्ठा ice_aqc_get_phy_caps_data *phy_caps,
			काष्ठा ice_aqc_set_phy_cfg_data *phy_cfg)
अणु
	u8 caps_mask, cfg_mask;

	अगर (!phy_caps || !phy_cfg)
		वापस false;

	/* These bits are not common between capabilities and configuration.
	 * Do not use them to determine equality.
	 */
	caps_mask = ICE_AQC_PHY_CAPS_MASK & ~(ICE_AQC_PHY_AN_MODE |
					      ICE_AQC_GET_PHY_EN_MOD_QUAL);
	cfg_mask = ICE_AQ_PHY_ENA_VALID_MASK & ~ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;

	अगर (phy_caps->phy_type_low != phy_cfg->phy_type_low ||
	    phy_caps->phy_type_high != phy_cfg->phy_type_high ||
	    ((phy_caps->caps & caps_mask) != (phy_cfg->caps & cfg_mask)) ||
	    phy_caps->low_घातer_ctrl_an != phy_cfg->low_घातer_ctrl_an ||
	    phy_caps->eee_cap != phy_cfg->eee_cap ||
	    phy_caps->eeer_value != phy_cfg->eeer_value ||
	    phy_caps->link_fec_options != phy_cfg->link_fec_opt)
		वापस false;

	वापस true;
पूर्ण

/**
 * ice_copy_phy_caps_to_cfg - Copy PHY ability data to configuration data
 * @pi: port inक्रमmation काष्ठाure
 * @caps: PHY ability काष्ठाure to copy date from
 * @cfg: PHY configuration काष्ठाure to copy data to
 *
 * Helper function to copy AQC PHY get ability data to PHY set configuration
 * data काष्ठाure
 */
व्योम
ice_copy_phy_caps_to_cfg(काष्ठा ice_port_info *pi,
			 काष्ठा ice_aqc_get_phy_caps_data *caps,
			 काष्ठा ice_aqc_set_phy_cfg_data *cfg)
अणु
	अगर (!pi || !caps || !cfg)
		वापस;

	स_रखो(cfg, 0, माप(*cfg));
	cfg->phy_type_low = caps->phy_type_low;
	cfg->phy_type_high = caps->phy_type_high;
	cfg->caps = caps->caps;
	cfg->low_घातer_ctrl_an = caps->low_घातer_ctrl_an;
	cfg->eee_cap = caps->eee_cap;
	cfg->eeer_value = caps->eeer_value;
	cfg->link_fec_opt = caps->link_fec_options;
	cfg->module_compliance_enक्रमcement =
		caps->module_compliance_enक्रमcement;
पूर्ण

/**
 * ice_cfg_phy_fec - Configure PHY FEC data based on FEC mode
 * @pi: port inक्रमmation काष्ठाure
 * @cfg: PHY configuration data to set FEC mode
 * @fec: FEC mode to configure
 */
क्रमागत ice_status
ice_cfg_phy_fec(काष्ठा ice_port_info *pi, काष्ठा ice_aqc_set_phy_cfg_data *cfg,
		क्रमागत ice_fec_mode fec)
अणु
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;

	अगर (!pi || !cfg)
		वापस ICE_ERR_BAD_PTR;

	hw = pi->hw;

	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_aq_get_phy_caps(pi, false,
				     (ice_fw_supports_report_dflt_cfg(hw) ?
				      ICE_AQC_REPORT_DFLT_CFG :
				      ICE_AQC_REPORT_TOPO_CAP_MEDIA), pcaps, शून्य);
	अगर (status)
		जाओ out;

	cfg->caps |= pcaps->caps & ICE_AQC_PHY_EN_AUTO_FEC;
	cfg->link_fec_opt = pcaps->link_fec_options;

	चयन (fec) अणु
	हाल ICE_FEC_BASER:
		/* Clear RS bits, and AND BASE-R ability
		 * bits and OR request bits.
		 */
		cfg->link_fec_opt &= ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN |
			ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN;
		cfg->link_fec_opt |= ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ |
			ICE_AQC_PHY_FEC_25G_KR_REQ;
		अवरोध;
	हाल ICE_FEC_RS:
		/* Clear BASE-R bits, and AND RS ability
		 * bits and OR request bits.
		 */
		cfg->link_fec_opt &= ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN;
		cfg->link_fec_opt |= ICE_AQC_PHY_FEC_25G_RS_528_REQ |
			ICE_AQC_PHY_FEC_25G_RS_544_REQ;
		अवरोध;
	हाल ICE_FEC_NONE:
		/* Clear all FEC option bits. */
		cfg->link_fec_opt &= ~ICE_AQC_PHY_FEC_MASK;
		अवरोध;
	हाल ICE_FEC_AUTO:
		/* AND स्वतः FEC bit, and all caps bits. */
		cfg->caps &= ICE_AQC_PHY_CAPS_MASK;
		cfg->link_fec_opt |= pcaps->link_fec_options;
		अवरोध;
	शेष:
		status = ICE_ERR_PARAM;
		अवरोध;
	पूर्ण

	अगर (fec == ICE_FEC_AUTO && ice_fw_supports_link_override(hw) &&
	    !ice_fw_supports_report_dflt_cfg(hw)) अणु
		काष्ठा ice_link_शेष_override_tlv tlv;

		अगर (ice_get_link_शेष_override(&tlv, pi))
			जाओ out;

		अगर (!(tlv.options & ICE_LINK_OVERRIDE_STRICT_MODE) &&
		    (tlv.options & ICE_LINK_OVERRIDE_EN))
			cfg->link_fec_opt = tlv.fec_options;
	पूर्ण

out:
	kमुक्त(pcaps);

	वापस status;
पूर्ण

/**
 * ice_get_link_status - get status of the HW network link
 * @pi: port inक्रमmation काष्ठाure
 * @link_up: poपूर्णांकer to bool (true/false = linkup/linkकरोwn)
 *
 * Variable link_up is true अगर link is up, false अगर link is करोwn.
 * The variable link_up is invalid अगर status is non zero. As a
 * result of this call, link status reporting becomes enabled
 */
क्रमागत ice_status ice_get_link_status(काष्ठा ice_port_info *pi, bool *link_up)
अणु
	काष्ठा ice_phy_info *phy_info;
	क्रमागत ice_status status = 0;

	अगर (!pi || !link_up)
		वापस ICE_ERR_PARAM;

	phy_info = &pi->phy;

	अगर (phy_info->get_link_info) अणु
		status = ice_update_link_info(pi);

		अगर (status)
			ice_debug(pi->hw, ICE_DBG_LINK, "get link status error, status = %d\n",
				  status);
	पूर्ण

	*link_up = phy_info->link_info.link_info & ICE_AQ_LINK_UP;

	वापस status;
पूर्ण

/**
 * ice_aq_set_link_restart_an
 * @pi: poपूर्णांकer to the port inक्रमmation काष्ठाure
 * @ena_link: अगर true: enable link, अगर false: disable link
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Sets up the link and restarts the Auto-Negotiation over the link.
 */
क्रमागत ice_status
ice_aq_set_link_restart_an(काष्ठा ice_port_info *pi, bool ena_link,
			   काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_restart_an *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.restart_an;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_restart_an);

	cmd->cmd_flags = ICE_AQC_RESTART_AN_LINK_RESTART;
	cmd->lport_num = pi->lport;
	अगर (ena_link)
		cmd->cmd_flags |= ICE_AQC_RESTART_AN_LINK_ENABLE;
	अन्यथा
		cmd->cmd_flags &= ~ICE_AQC_RESTART_AN_LINK_ENABLE;

	वापस ice_aq_send_cmd(pi->hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_set_event_mask
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @port_num: port number of the physical function
 * @mask: event mask to be set
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set event mask (0x0613)
 */
क्रमागत ice_status
ice_aq_set_event_mask(काष्ठा ice_hw *hw, u8 port_num, u16 mask,
		      काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_set_event_mask *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.set_event_mask;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_event_mask);

	cmd->lport_num = port_num;

	cmd->event_mask = cpu_to_le16(mask);
	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_set_mac_loopback
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @ena_lpbk: Enable or Disable loopback
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Enable/disable loopback on a given port
 */
क्रमागत ice_status
ice_aq_set_mac_loopback(काष्ठा ice_hw *hw, bool ena_lpbk, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_set_mac_lb *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.set_mac_lb;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_mac_lb);
	अगर (ena_lpbk)
		cmd->lb_mode = ICE_AQ_MAC_LB_EN;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_set_port_id_led
 * @pi: poपूर्णांकer to the port inक्रमmation
 * @is_orig_mode: is this LED set to original mode (by the net-list)
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set LED value क्रम the given port (0x06e9)
 */
क्रमागत ice_status
ice_aq_set_port_id_led(काष्ठा ice_port_info *pi, bool is_orig_mode,
		       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_set_port_id_led *cmd;
	काष्ठा ice_hw *hw = pi->hw;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.set_port_id_led;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_port_id_led);

	अगर (is_orig_mode)
		cmd->ident_mode = ICE_AQC_PORT_IDENT_LED_ORIG;
	अन्यथा
		cmd->ident_mode = ICE_AQC_PORT_IDENT_LED_BLINK;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_aq_sff_eeprom
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @lport: bits [7:0] = logical port, bit [8] = logical port valid
 * @bus_addr: I2C bus address of the eeprom (typically 0xA0, 0=topo शेष)
 * @mem_addr: I2C offset. lower 8 bits क्रम address, 8 upper bits zero padding.
 * @page: QSFP page
 * @set_page: set or ignore the page
 * @data: poपूर्णांकer to data buffer to be पढ़ो/written to the I2C device.
 * @length: 1-16 क्रम पढ़ो, 1 क्रम ग_लिखो.
 * @ग_लिखो: 0 पढ़ो, 1 क्रम ग_लिखो.
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Read/Write SFF EEPROM (0x06EE)
 */
क्रमागत ice_status
ice_aq_sff_eeprom(काष्ठा ice_hw *hw, u16 lport, u8 bus_addr,
		  u16 mem_addr, u8 page, u8 set_page, u8 *data, u8 length,
		  bool ग_लिखो, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_sff_eeprom *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (!data || (mem_addr & 0xff00))
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_sff_eeprom);
	cmd = &desc.params.पढ़ो_ग_लिखो_sff_param;
	desc.flags = cpu_to_le16(ICE_AQ_FLAG_RD);
	cmd->lport_num = (u8)(lport & 0xff);
	cmd->lport_num_valid = (u8)((lport >> 8) & 0x01);
	cmd->i2c_bus_addr = cpu_to_le16(((bus_addr >> 1) &
					 ICE_AQC_SFF_I2CBUS_7BIT_M) |
					((set_page <<
					  ICE_AQC_SFF_SET_EEPROM_PAGE_S) &
					 ICE_AQC_SFF_SET_EEPROM_PAGE_M));
	cmd->i2c_mem_addr = cpu_to_le16(mem_addr & 0xff);
	cmd->eeprom_page = cpu_to_le16((u16)page << ICE_AQC_SFF_EEPROM_PAGE_S);
	अगर (ग_लिखो)
		cmd->i2c_bus_addr |= cpu_to_le16(ICE_AQC_SFF_IS_WRITE);

	status = ice_aq_send_cmd(hw, &desc, data, length, cd);
	वापस status;
पूर्ण

/**
 * __ice_aq_get_set_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @params: RSS LUT parameters
 * @set: set true to set the table, false to get the table
 *
 * Internal function to get (0x0B05) or set (0x0B03) RSS look up table
 */
अटल क्रमागत ice_status
__ice_aq_get_set_rss_lut(काष्ठा ice_hw *hw, काष्ठा ice_aq_get_set_rss_lut_params *params, bool set)
अणु
	u16 flags = 0, vsi_id, lut_type, lut_size, glob_lut_idx, vsi_handle;
	काष्ठा ice_aqc_get_set_rss_lut *cmd_resp;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;
	u8 *lut;

	अगर (!params)
		वापस ICE_ERR_PARAM;

	vsi_handle = params->vsi_handle;
	lut = params->lut;

	अगर (!ice_is_vsi_valid(hw, vsi_handle) || !lut)
		वापस ICE_ERR_PARAM;

	lut_size = params->lut_size;
	lut_type = params->lut_type;
	glob_lut_idx = params->global_lut_id;
	vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	cmd_resp = &desc.params.get_set_rss_lut;

	अगर (set) अणु
		ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_rss_lut);
		desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	पूर्ण अन्यथा अणु
		ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_rss_lut);
	पूर्ण

	cmd_resp->vsi_id = cpu_to_le16(((vsi_id <<
					 ICE_AQC_GSET_RSS_LUT_VSI_ID_S) &
					ICE_AQC_GSET_RSS_LUT_VSI_ID_M) |
				       ICE_AQC_GSET_RSS_LUT_VSI_VALID);

	चयन (lut_type) अणु
	हाल ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_VSI:
	हाल ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_PF:
	हाल ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_GLOBAL:
		flags |= ((lut_type << ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_S) &
			  ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_M);
		अवरोध;
	शेष:
		status = ICE_ERR_PARAM;
		जाओ ice_aq_get_set_rss_lut_निकास;
	पूर्ण

	अगर (lut_type == ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_GLOBAL) अणु
		flags |= ((glob_lut_idx << ICE_AQC_GSET_RSS_LUT_GLOBAL_IDX_S) &
			  ICE_AQC_GSET_RSS_LUT_GLOBAL_IDX_M);

		अगर (!set)
			जाओ ice_aq_get_set_rss_lut_send;
	पूर्ण अन्यथा अगर (lut_type == ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_PF) अणु
		अगर (!set)
			जाओ ice_aq_get_set_rss_lut_send;
	पूर्ण अन्यथा अणु
		जाओ ice_aq_get_set_rss_lut_send;
	पूर्ण

	/* LUT size is only valid क्रम Global and PF table types */
	चयन (lut_size) अणु
	हाल ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_128:
		अवरोध;
	हाल ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_512:
		flags |= (ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_512_FLAG <<
			  ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_S) &
			 ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_M;
		अवरोध;
	हाल ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_2K:
		अगर (lut_type == ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_PF) अणु
			flags |= (ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_2K_FLAG <<
				  ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_S) &
				 ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_M;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		status = ICE_ERR_PARAM;
		जाओ ice_aq_get_set_rss_lut_निकास;
	पूर्ण

ice_aq_get_set_rss_lut_send:
	cmd_resp->flags = cpu_to_le16(flags);
	status = ice_aq_send_cmd(hw, &desc, lut, lut_size, शून्य);

ice_aq_get_set_rss_lut_निकास:
	वापस status;
पूर्ण

/**
 * ice_aq_get_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @get_params: RSS LUT parameters used to specअगरy which RSS LUT to get
 *
 * get the RSS lookup table, PF or VSI type
 */
क्रमागत ice_status
ice_aq_get_rss_lut(काष्ठा ice_hw *hw, काष्ठा ice_aq_get_set_rss_lut_params *get_params)
अणु
	वापस __ice_aq_get_set_rss_lut(hw, get_params, false);
पूर्ण

/**
 * ice_aq_set_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @set_params: RSS LUT parameters used to specअगरy how to set the RSS LUT
 *
 * set the RSS lookup table, PF or VSI type
 */
क्रमागत ice_status
ice_aq_set_rss_lut(काष्ठा ice_hw *hw, काष्ठा ice_aq_get_set_rss_lut_params *set_params)
अणु
	वापस __ice_aq_get_set_rss_lut(hw, set_params, true);
पूर्ण

/**
 * __ice_aq_get_set_rss_key
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_id: VSI FW index
 * @key: poपूर्णांकer to key info काष्ठा
 * @set: set true to set the key, false to get the key
 *
 * get (0x0B04) or set (0x0B02) the RSS key per VSI
 */
अटल क्रमागत
ice_status __ice_aq_get_set_rss_key(काष्ठा ice_hw *hw, u16 vsi_id,
				    काष्ठा ice_aqc_get_set_rss_keys *key,
				    bool set)
अणु
	काष्ठा ice_aqc_get_set_rss_key *cmd_resp;
	u16 key_size = माप(*key);
	काष्ठा ice_aq_desc desc;

	cmd_resp = &desc.params.get_set_rss_key;

	अगर (set) अणु
		ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_rss_key);
		desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	पूर्ण अन्यथा अणु
		ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_rss_key);
	पूर्ण

	cmd_resp->vsi_id = cpu_to_le16(((vsi_id <<
					 ICE_AQC_GSET_RSS_KEY_VSI_ID_S) &
					ICE_AQC_GSET_RSS_KEY_VSI_ID_M) |
				       ICE_AQC_GSET_RSS_KEY_VSI_VALID);

	वापस ice_aq_send_cmd(hw, &desc, key, key_size, शून्य);
पूर्ण

/**
 * ice_aq_get_rss_key
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: software VSI handle
 * @key: poपूर्णांकer to key info काष्ठा
 *
 * get the RSS key per VSI
 */
क्रमागत ice_status
ice_aq_get_rss_key(काष्ठा ice_hw *hw, u16 vsi_handle,
		   काष्ठा ice_aqc_get_set_rss_keys *key)
अणु
	अगर (!ice_is_vsi_valid(hw, vsi_handle) || !key)
		वापस ICE_ERR_PARAM;

	वापस __ice_aq_get_set_rss_key(hw, ice_get_hw_vsi_num(hw, vsi_handle),
					key, false);
पूर्ण

/**
 * ice_aq_set_rss_key
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: software VSI handle
 * @keys: poपूर्णांकer to key info काष्ठा
 *
 * set the RSS key per VSI
 */
क्रमागत ice_status
ice_aq_set_rss_key(काष्ठा ice_hw *hw, u16 vsi_handle,
		   काष्ठा ice_aqc_get_set_rss_keys *keys)
अणु
	अगर (!ice_is_vsi_valid(hw, vsi_handle) || !keys)
		वापस ICE_ERR_PARAM;

	वापस __ice_aq_get_set_rss_key(hw, ice_get_hw_vsi_num(hw, vsi_handle),
					keys, true);
पूर्ण

/**
 * ice_aq_add_lan_txq
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @num_qgrps: Number of added queue groups
 * @qg_list: list of queue groups to be added
 * @buf_size: size of buffer क्रम indirect command
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add Tx LAN queue (0x0C30)
 *
 * NOTE:
 * Prior to calling add Tx LAN queue:
 * Initialize the following as part of the Tx queue context:
 * Completion queue ID अगर the queue uses Completion queue, Quanta profile,
 * Cache profile and Packet shaper profile.
 *
 * After add Tx LAN queue AQ command is completed:
 * Interrupts should be associated with specअगरic queues,
 * Association of Tx queue to Doorbell queue is not part of Add LAN Tx queue
 * flow.
 */
अटल क्रमागत ice_status
ice_aq_add_lan_txq(काष्ठा ice_hw *hw, u8 num_qgrps,
		   काष्ठा ice_aqc_add_tx_qgrp *qg_list, u16 buf_size,
		   काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_add_tx_qgrp *list;
	काष्ठा ice_aqc_add_txqs *cmd;
	काष्ठा ice_aq_desc desc;
	u16 i, sum_size = 0;

	cmd = &desc.params.add_txqs;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_add_txqs);

	अगर (!qg_list)
		वापस ICE_ERR_PARAM;

	अगर (num_qgrps > ICE_LAN_TXQ_MAX_QGRPS)
		वापस ICE_ERR_PARAM;

	क्रम (i = 0, list = qg_list; i < num_qgrps; i++) अणु
		sum_size += काष्ठा_size(list, txqs, list->num_txqs);
		list = (काष्ठा ice_aqc_add_tx_qgrp *)(list->txqs +
						      list->num_txqs);
	पूर्ण

	अगर (buf_size != sum_size)
		वापस ICE_ERR_PARAM;

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	cmd->num_qgrps = num_qgrps;

	वापस ice_aq_send_cmd(hw, &desc, qg_list, buf_size, cd);
पूर्ण

/**
 * ice_aq_dis_lan_txq
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @num_qgrps: number of groups in the list
 * @qg_list: the list of groups to disable
 * @buf_size: the total size of the qg_list buffer in bytes
 * @rst_src: अगर called due to reset, specअगरies the reset source
 * @vmvf_num: the relative VM or VF number that is undergoing the reset
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Disable LAN Tx queue (0x0C31)
 */
अटल क्रमागत ice_status
ice_aq_dis_lan_txq(काष्ठा ice_hw *hw, u8 num_qgrps,
		   काष्ठा ice_aqc_dis_txq_item *qg_list, u16 buf_size,
		   क्रमागत ice_disq_rst_src rst_src, u16 vmvf_num,
		   काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_dis_txq_item *item;
	काष्ठा ice_aqc_dis_txqs *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;
	u16 i, sz = 0;

	cmd = &desc.params.dis_txqs;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_dis_txqs);

	/* qg_list can be शून्य only in VM/VF reset flow */
	अगर (!qg_list && !rst_src)
		वापस ICE_ERR_PARAM;

	अगर (num_qgrps > ICE_LAN_TXQ_MAX_QGRPS)
		वापस ICE_ERR_PARAM;

	cmd->num_entries = num_qgrps;

	cmd->vmvf_and_समयout = cpu_to_le16((5 << ICE_AQC_Q_DIS_TIMEOUT_S) &
					    ICE_AQC_Q_DIS_TIMEOUT_M);

	चयन (rst_src) अणु
	हाल ICE_VM_RESET:
		cmd->cmd_type = ICE_AQC_Q_DIS_CMD_VM_RESET;
		cmd->vmvf_and_समयout |=
			cpu_to_le16(vmvf_num & ICE_AQC_Q_DIS_VMVF_NUM_M);
		अवरोध;
	हाल ICE_VF_RESET:
		cmd->cmd_type = ICE_AQC_Q_DIS_CMD_VF_RESET;
		/* In this हाल, FW expects vmvf_num to be असलolute VF ID */
		cmd->vmvf_and_समयout |=
			cpu_to_le16((vmvf_num + hw->func_caps.vf_base_id) &
				    ICE_AQC_Q_DIS_VMVF_NUM_M);
		अवरोध;
	हाल ICE_NO_RESET:
	शेष:
		अवरोध;
	पूर्ण

	/* flush pipe on समय out */
	cmd->cmd_type |= ICE_AQC_Q_DIS_CMD_FLUSH_PIPE;
	/* If no queue group info, we are in a reset flow. Issue the AQ */
	अगर (!qg_list)
		जाओ करो_aq;

	/* set RD bit to indicate that command buffer is provided by the driver
	 * and it needs to be पढ़ो by the firmware
	 */
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	क्रम (i = 0, item = qg_list; i < num_qgrps; i++) अणु
		u16 item_size = काष्ठा_size(item, q_id, item->num_qs);

		/* If the num of queues is even, add 2 bytes of padding */
		अगर ((item->num_qs % 2) == 0)
			item_size += 2;

		sz += item_size;

		item = (काष्ठा ice_aqc_dis_txq_item *)((u8 *)item + item_size);
	पूर्ण

	अगर (buf_size != sz)
		वापस ICE_ERR_PARAM;

करो_aq:
	status = ice_aq_send_cmd(hw, &desc, qg_list, buf_size, cd);
	अगर (status) अणु
		अगर (!qg_list)
			ice_debug(hw, ICE_DBG_SCHED, "VM%d disable failed %d\n",
				  vmvf_num, hw->adminq.sq_last_status);
		अन्यथा
			ice_debug(hw, ICE_DBG_SCHED, "disable queue %d failed %d\n",
				  le16_to_cpu(qg_list[0].q_id[0]),
				  hw->adminq.sq_last_status);
	पूर्ण
	वापस status;
पूर्ण

/* End of FW Admin Queue command wrappers */

/**
 * ice_ग_लिखो_byte - ग_लिखो a byte to a packed context काष्ठाure
 * @src_ctx:  the context काष्ठाure to पढ़ो from
 * @dest_ctx: the context to be written to
 * @ce_info:  a description of the काष्ठा to be filled
 */
अटल व्योम
ice_ग_लिखो_byte(u8 *src_ctx, u8 *dest_ctx, स्थिर काष्ठा ice_ctx_ele *ce_info)
अणु
	u8 src_byte, dest_byte, mask;
	u8 *from, *dest;
	u16 shअगरt_width;

	/* copy from the next काष्ठा field */
	from = src_ctx + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;
	mask = (u8)(BIT(ce_info->width) - 1);

	src_byte = *from;
	src_byte &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_byte <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = dest_ctx + (ce_info->lsb / 8);

	स_नकल(&dest_byte, dest, माप(dest_byte));

	dest_byte &= ~mask;	/* get the bits not changing */
	dest_byte |= src_byte;	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_byte, माप(dest_byte));
पूर्ण

/**
 * ice_ग_लिखो_word - ग_लिखो a word to a packed context काष्ठाure
 * @src_ctx:  the context काष्ठाure to पढ़ो from
 * @dest_ctx: the context to be written to
 * @ce_info:  a description of the काष्ठा to be filled
 */
अटल व्योम
ice_ग_लिखो_word(u8 *src_ctx, u8 *dest_ctx, स्थिर काष्ठा ice_ctx_ele *ce_info)
अणु
	u16 src_word, mask;
	__le16 dest_word;
	u8 *from, *dest;
	u16 shअगरt_width;

	/* copy from the next काष्ठा field */
	from = src_ctx + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;
	mask = BIT(ce_info->width) - 1;

	/* करोn't swizzle the bits until after the mask because the mask bits
	 * will be in a dअगरferent bit position on big endian machines
	 */
	src_word = *(u16 *)from;
	src_word &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_word <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = dest_ctx + (ce_info->lsb / 8);

	स_नकल(&dest_word, dest, माप(dest_word));

	dest_word &= ~(cpu_to_le16(mask));	/* get the bits not changing */
	dest_word |= cpu_to_le16(src_word);	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_word, माप(dest_word));
पूर्ण

/**
 * ice_ग_लिखो_dword - ग_लिखो a dword to a packed context काष्ठाure
 * @src_ctx:  the context काष्ठाure to पढ़ो from
 * @dest_ctx: the context to be written to
 * @ce_info:  a description of the काष्ठा to be filled
 */
अटल व्योम
ice_ग_लिखो_dword(u8 *src_ctx, u8 *dest_ctx, स्थिर काष्ठा ice_ctx_ele *ce_info)
अणु
	u32 src_dword, mask;
	__le32 dest_dword;
	u8 *from, *dest;
	u16 shअगरt_width;

	/* copy from the next काष्ठा field */
	from = src_ctx + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;

	/* अगर the field width is exactly 32 on an x86 machine, then the shअगरt
	 * operation will not work because the SHL inकाष्ठाions count is masked
	 * to 5 bits so the shअगरt will करो nothing
	 */
	अगर (ce_info->width < 32)
		mask = BIT(ce_info->width) - 1;
	अन्यथा
		mask = (u32)~0;

	/* करोn't swizzle the bits until after the mask because the mask bits
	 * will be in a dअगरferent bit position on big endian machines
	 */
	src_dword = *(u32 *)from;
	src_dword &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_dword <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = dest_ctx + (ce_info->lsb / 8);

	स_नकल(&dest_dword, dest, माप(dest_dword));

	dest_dword &= ~(cpu_to_le32(mask));	/* get the bits not changing */
	dest_dword |= cpu_to_le32(src_dword);	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_dword, माप(dest_dword));
पूर्ण

/**
 * ice_ग_लिखो_qword - ग_लिखो a qword to a packed context काष्ठाure
 * @src_ctx:  the context काष्ठाure to पढ़ो from
 * @dest_ctx: the context to be written to
 * @ce_info:  a description of the काष्ठा to be filled
 */
अटल व्योम
ice_ग_लिखो_qword(u8 *src_ctx, u8 *dest_ctx, स्थिर काष्ठा ice_ctx_ele *ce_info)
अणु
	u64 src_qword, mask;
	__le64 dest_qword;
	u8 *from, *dest;
	u16 shअगरt_width;

	/* copy from the next काष्ठा field */
	from = src_ctx + ce_info->offset;

	/* prepare the bits and mask */
	shअगरt_width = ce_info->lsb % 8;

	/* अगर the field width is exactly 64 on an x86 machine, then the shअगरt
	 * operation will not work because the SHL inकाष्ठाions count is masked
	 * to 6 bits so the shअगरt will करो nothing
	 */
	अगर (ce_info->width < 64)
		mask = BIT_ULL(ce_info->width) - 1;
	अन्यथा
		mask = (u64)~0;

	/* करोn't swizzle the bits until after the mask because the mask bits
	 * will be in a dअगरferent bit position on big endian machines
	 */
	src_qword = *(u64 *)from;
	src_qword &= mask;

	/* shअगरt to correct alignment */
	mask <<= shअगरt_width;
	src_qword <<= shअगरt_width;

	/* get the current bits from the target bit string */
	dest = dest_ctx + (ce_info->lsb / 8);

	स_नकल(&dest_qword, dest, माप(dest_qword));

	dest_qword &= ~(cpu_to_le64(mask));	/* get the bits not changing */
	dest_qword |= cpu_to_le64(src_qword);	/* add in the new bits */

	/* put it all back */
	स_नकल(dest, &dest_qword, माप(dest_qword));
पूर्ण

/**
 * ice_set_ctx - set context bits in packed काष्ठाure
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @src_ctx:  poपूर्णांकer to a generic non-packed context काष्ठाure
 * @dest_ctx: poपूर्णांकer to memory क्रम the packed काष्ठाure
 * @ce_info:  a description of the काष्ठाure to be transक्रमmed
 */
क्रमागत ice_status
ice_set_ctx(काष्ठा ice_hw *hw, u8 *src_ctx, u8 *dest_ctx,
	    स्थिर काष्ठा ice_ctx_ele *ce_info)
अणु
	पूर्णांक f;

	क्रम (f = 0; ce_info[f].width; f++) अणु
		/* We have to deal with each element of the FW response
		 * using the correct size so that we are correct regardless
		 * of the endianness of the machine.
		 */
		अगर (ce_info[f].width > (ce_info[f].size_of * BITS_PER_BYTE)) अणु
			ice_debug(hw, ICE_DBG_QCTX, "Field %d width of %d bits larger than size of %d byte(s) ... skipping write\n",
				  f, ce_info[f].width, ce_info[f].size_of);
			जारी;
		पूर्ण
		चयन (ce_info[f].size_of) अणु
		हाल माप(u8):
			ice_ग_लिखो_byte(src_ctx, dest_ctx, &ce_info[f]);
			अवरोध;
		हाल माप(u16):
			ice_ग_लिखो_word(src_ctx, dest_ctx, &ce_info[f]);
			अवरोध;
		हाल माप(u32):
			ice_ग_लिखो_dword(src_ctx, dest_ctx, &ce_info[f]);
			अवरोध;
		हाल माप(u64):
			ice_ग_लिखो_qword(src_ctx, dest_ctx, &ce_info[f]);
			अवरोध;
		शेष:
			वापस ICE_ERR_INVAL_SIZE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_get_lan_q_ctx - get the LAN queue context क्रम the given VSI and TC
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: software VSI handle
 * @tc: TC number
 * @q_handle: software queue handle
 */
काष्ठा ice_q_ctx *
ice_get_lan_q_ctx(काष्ठा ice_hw *hw, u16 vsi_handle, u8 tc, u16 q_handle)
अणु
	काष्ठा ice_vsi_ctx *vsi;
	काष्ठा ice_q_ctx *q_ctx;

	vsi = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (!vsi)
		वापस शून्य;
	अगर (q_handle >= vsi->num_lan_q_entries[tc])
		वापस शून्य;
	अगर (!vsi->lan_q_ctx[tc])
		वापस शून्य;
	q_ctx = vsi->lan_q_ctx[tc];
	वापस &q_ctx[q_handle];
पूर्ण

/**
 * ice_ena_vsi_txq
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc: TC number
 * @q_handle: software queue handle
 * @num_qgrps: Number of added queue groups
 * @buf: list of queue groups to be added
 * @buf_size: size of buffer क्रम indirect command
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This function adds one LAN queue
 */
क्रमागत ice_status
ice_ena_vsi_txq(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc, u16 q_handle,
		u8 num_qgrps, काष्ठा ice_aqc_add_tx_qgrp *buf, u16 buf_size,
		काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_txsched_elem_data node = अणु 0 पूर्ण;
	काष्ठा ice_sched_node *parent;
	काष्ठा ice_q_ctx *q_ctx;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;

	अगर (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		वापस ICE_ERR_CFG;

	अगर (num_qgrps > 1 || buf->num_txqs > 1)
		वापस ICE_ERR_MAX_LIMIT;

	hw = pi->hw;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	mutex_lock(&pi->sched_lock);

	q_ctx = ice_get_lan_q_ctx(hw, vsi_handle, tc, q_handle);
	अगर (!q_ctx) अणु
		ice_debug(hw, ICE_DBG_SCHED, "Enaq: invalid queue handle %d\n",
			  q_handle);
		status = ICE_ERR_PARAM;
		जाओ ena_txq_निकास;
	पूर्ण

	/* find a parent node */
	parent = ice_sched_get_मुक्त_qparent(pi, vsi_handle, tc,
					    ICE_SCHED_NODE_OWNER_LAN);
	अगर (!parent) अणु
		status = ICE_ERR_PARAM;
		जाओ ena_txq_निकास;
	पूर्ण

	buf->parent_teid = parent->info.node_teid;
	node.parent_teid = parent->info.node_teid;
	/* Mark that the values in the "generic" section as valid. The शेष
	 * value in the "generic" section is zero. This means that :
	 * - Scheduling mode is Bytes Per Second (BPS), indicated by Bit 0.
	 * - 0 priority among siblings, indicated by Bit 1-3.
	 * - WFQ, indicated by Bit 4.
	 * - 0 Adjusपंचांगent value is used in PSM credit update flow, indicated by
	 * Bit 5-6.
	 * - Bit 7 is reserved.
	 * Without setting the generic section as valid in valid_sections, the
	 * Admin queue command will fail with error code ICE_AQ_RC_EINVAL.
	 */
	buf->txqs[0].info.valid_sections =
		ICE_AQC_ELEM_VALID_GENERIC | ICE_AQC_ELEM_VALID_CIR |
		ICE_AQC_ELEM_VALID_EIR;
	buf->txqs[0].info.generic = 0;
	buf->txqs[0].info.cir_bw.bw_profile_idx =
		cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
	buf->txqs[0].info.cir_bw.bw_alloc =
		cpu_to_le16(ICE_SCHED_DFLT_BW_WT);
	buf->txqs[0].info.eir_bw.bw_profile_idx =
		cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
	buf->txqs[0].info.eir_bw.bw_alloc =
		cpu_to_le16(ICE_SCHED_DFLT_BW_WT);

	/* add the LAN queue */
	status = ice_aq_add_lan_txq(hw, num_qgrps, buf, buf_size, cd);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_SCHED, "enable queue %d failed %d\n",
			  le16_to_cpu(buf->txqs[0].txq_id),
			  hw->adminq.sq_last_status);
		जाओ ena_txq_निकास;
	पूर्ण

	node.node_teid = buf->txqs[0].q_teid;
	node.data.elem_type = ICE_AQC_ELEM_TYPE_LEAF;
	q_ctx->q_handle = q_handle;
	q_ctx->q_teid = le32_to_cpu(node.node_teid);

	/* add a leaf node पूर्णांकo scheduler tree queue layer */
	status = ice_sched_add_node(pi, hw->num_tx_sched_layers - 1, &node);
	अगर (!status)
		status = ice_sched_replay_q_bw(pi, q_ctx);

ena_txq_निकास:
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_dis_vsi_txq
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc: TC number
 * @num_queues: number of queues
 * @q_handles: poपूर्णांकer to software queue handle array
 * @q_ids: poपूर्णांकer to the q_id array
 * @q_teids: poपूर्णांकer to queue node teids
 * @rst_src: अगर called due to reset, specअगरies the reset source
 * @vmvf_num: the relative VM or VF number that is undergoing the reset
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This function हटाओs queues and their corresponding nodes in SW DB
 */
क्रमागत ice_status
ice_dis_vsi_txq(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc, u8 num_queues,
		u16 *q_handles, u16 *q_ids, u32 *q_teids,
		क्रमागत ice_disq_rst_src rst_src, u16 vmvf_num,
		काष्ठा ice_sq_cd *cd)
अणु
	क्रमागत ice_status status = ICE_ERR_DOES_NOT_EXIST;
	काष्ठा ice_aqc_dis_txq_item *qg_list;
	काष्ठा ice_q_ctx *q_ctx;
	काष्ठा ice_hw *hw;
	u16 i, buf_size;

	अगर (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		वापस ICE_ERR_CFG;

	hw = pi->hw;

	अगर (!num_queues) अणु
		/* अगर queue is disabled alपढ़ोy yet the disable queue command
		 * has to be sent to complete the VF reset, then call
		 * ice_aq_dis_lan_txq without any queue inक्रमmation
		 */
		अगर (rst_src)
			वापस ice_aq_dis_lan_txq(hw, 0, शून्य, 0, rst_src,
						  vmvf_num, शून्य);
		वापस ICE_ERR_CFG;
	पूर्ण

	buf_size = काष्ठा_size(qg_list, q_id, 1);
	qg_list = kzalloc(buf_size, GFP_KERNEL);
	अगर (!qg_list)
		वापस ICE_ERR_NO_MEMORY;

	mutex_lock(&pi->sched_lock);

	क्रम (i = 0; i < num_queues; i++) अणु
		काष्ठा ice_sched_node *node;

		node = ice_sched_find_node_by_teid(pi->root, q_teids[i]);
		अगर (!node)
			जारी;
		q_ctx = ice_get_lan_q_ctx(hw, vsi_handle, tc, q_handles[i]);
		अगर (!q_ctx) अणु
			ice_debug(hw, ICE_DBG_SCHED, "invalid queue handle%d\n",
				  q_handles[i]);
			जारी;
		पूर्ण
		अगर (q_ctx->q_handle != q_handles[i]) अणु
			ice_debug(hw, ICE_DBG_SCHED, "Err:handles %d %d\n",
				  q_ctx->q_handle, q_handles[i]);
			जारी;
		पूर्ण
		qg_list->parent_teid = node->info.parent_teid;
		qg_list->num_qs = 1;
		qg_list->q_id[0] = cpu_to_le16(q_ids[i]);
		status = ice_aq_dis_lan_txq(hw, 1, qg_list, buf_size, rst_src,
					    vmvf_num, cd);

		अगर (status)
			अवरोध;
		ice_मुक्त_sched_node(pi, node);
		q_ctx->q_handle = ICE_INVAL_Q_HANDLE;
	पूर्ण
	mutex_unlock(&pi->sched_lock);
	kमुक्त(qg_list);
	वापस status;
पूर्ण

/**
 * ice_cfg_vsi_qs - configure the new/existing VSI queues
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc_biपंचांगap: TC biपंचांगap
 * @maxqs: max queues array per TC
 * @owner: LAN or RDMA
 *
 * This function adds/updates the VSI queues per TC.
 */
अटल क्रमागत ice_status
ice_cfg_vsi_qs(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc_biपंचांगap,
	       u16 *maxqs, u8 owner)
अणु
	क्रमागत ice_status status = 0;
	u8 i;

	अगर (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		वापस ICE_ERR_CFG;

	अगर (!ice_is_vsi_valid(pi->hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	mutex_lock(&pi->sched_lock);

	ice_क्रम_each_traffic_class(i) अणु
		/* configuration is possible only अगर TC node is present */
		अगर (!ice_sched_get_tc_node(pi, i))
			जारी;

		status = ice_sched_cfg_vsi(pi, vsi_handle, i, maxqs[i], owner,
					   ice_is_tc_ena(tc_biपंचांगap, i));
		अगर (status)
			अवरोध;
	पूर्ण

	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_cfg_vsi_lan - configure VSI LAN queues
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc_biपंचांगap: TC biपंचांगap
 * @max_lanqs: max LAN queues array per TC
 *
 * This function adds/updates the VSI LAN queues per TC.
 */
क्रमागत ice_status
ice_cfg_vsi_lan(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc_biपंचांगap,
		u16 *max_lanqs)
अणु
	वापस ice_cfg_vsi_qs(pi, vsi_handle, tc_biपंचांगap, max_lanqs,
			      ICE_SCHED_NODE_OWNER_LAN);
पूर्ण

/**
 * ice_replay_pre_init - replay pre initialization
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Initializes required config data क्रम VSI, FD, ACL, and RSS beक्रमe replay.
 */
अटल क्रमागत ice_status ice_replay_pre_init(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_चयन_info *sw = hw->चयन_info;
	u8 i;

	/* Delete old entries from replay filter list head अगर there is any */
	ice_rm_all_sw_replay_rule_info(hw);
	/* In start of replay, move entries पूर्णांकo replay_rules list, it
	 * will allow adding rules entries back to filt_rules list,
	 * which is operational list.
	 */
	क्रम (i = 0; i < ICE_SW_LKUP_LAST; i++)
		list_replace_init(&sw->recp_list[i].filt_rules,
				  &sw->recp_list[i].filt_replay_rules);
	ice_sched_replay_agg_vsi_preinit(hw);

	वापस 0;
पूर्ण

/**
 * ice_replay_vsi - replay VSI configuration
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: driver VSI handle
 *
 * Restore all VSI configuration after reset. It is required to call this
 * function with मुख्य VSI first.
 */
क्रमागत ice_status ice_replay_vsi(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	क्रमागत ice_status status;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	/* Replay pre-initialization अगर there is any */
	अगर (vsi_handle == ICE_MAIN_VSI_HANDLE) अणु
		status = ice_replay_pre_init(hw);
		अगर (status)
			वापस status;
	पूर्ण
	/* Replay per VSI all RSS configurations */
	status = ice_replay_rss_cfg(hw, vsi_handle);
	अगर (status)
		वापस status;
	/* Replay per VSI all filters */
	status = ice_replay_vsi_all_fltr(hw, vsi_handle);
	अगर (!status)
		status = ice_replay_vsi_agg(hw, vsi_handle);
	वापस status;
पूर्ण

/**
 * ice_replay_post - post replay configuration cleanup
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Post replay cleanup.
 */
व्योम ice_replay_post(काष्ठा ice_hw *hw)
अणु
	/* Delete old entries from replay filter list head */
	ice_rm_all_sw_replay_rule_info(hw);
	ice_sched_replay_agg(hw);
पूर्ण

/**
 * ice_stat_update40 - पढ़ो 40 bit stat from the chip and update stat values
 * @hw: ptr to the hardware info
 * @reg: offset of 64 bit HW रेजिस्टर to पढ़ो from
 * @prev_stat_loaded: bool to specअगरy अगर previous stats are loaded
 * @prev_stat: ptr to previous loaded stat value
 * @cur_stat: ptr to current stat value
 */
व्योम
ice_stat_update40(काष्ठा ice_hw *hw, u32 reg, bool prev_stat_loaded,
		  u64 *prev_stat, u64 *cur_stat)
अणु
	u64 new_data = rd64(hw, reg) & (BIT_ULL(40) - 1);

	/* device stats are not reset at PFR, they likely will not be zeroed
	 * when the driver starts. Thus, save the value from the first पढ़ो
	 * without adding to the statistic value so that we report stats which
	 * count up from zero.
	 */
	अगर (!prev_stat_loaded) अणु
		*prev_stat = new_data;
		वापस;
	पूर्ण

	/* Calculate the dअगरference between the new and old values, and then
	 * add it to the software stat value.
	 */
	अगर (new_data >= *prev_stat)
		*cur_stat += new_data - *prev_stat;
	अन्यथा
		/* to manage the potential roll-over */
		*cur_stat += (new_data + BIT_ULL(40)) - *prev_stat;

	/* Update the previously stored value to prepare क्रम next पढ़ो */
	*prev_stat = new_data;
पूर्ण

/**
 * ice_stat_update32 - पढ़ो 32 bit stat from the chip and update stat values
 * @hw: ptr to the hardware info
 * @reg: offset of HW रेजिस्टर to पढ़ो from
 * @prev_stat_loaded: bool to specअगरy अगर previous stats are loaded
 * @prev_stat: ptr to previous loaded stat value
 * @cur_stat: ptr to current stat value
 */
व्योम
ice_stat_update32(काष्ठा ice_hw *hw, u32 reg, bool prev_stat_loaded,
		  u64 *prev_stat, u64 *cur_stat)
अणु
	u32 new_data;

	new_data = rd32(hw, reg);

	/* device stats are not reset at PFR, they likely will not be zeroed
	 * when the driver starts. Thus, save the value from the first पढ़ो
	 * without adding to the statistic value so that we report stats which
	 * count up from zero.
	 */
	अगर (!prev_stat_loaded) अणु
		*prev_stat = new_data;
		वापस;
	पूर्ण

	/* Calculate the dअगरference between the new and old values, and then
	 * add it to the software stat value.
	 */
	अगर (new_data >= *prev_stat)
		*cur_stat += new_data - *prev_stat;
	अन्यथा
		/* to manage the potential roll-over */
		*cur_stat += (new_data + BIT_ULL(32)) - *prev_stat;

	/* Update the previously stored value to prepare क्रम next पढ़ो */
	*prev_stat = new_data;
पूर्ण

/**
 * ice_sched_query_elem - query element inक्रमmation from HW
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node_teid: node TEID to be queried
 * @buf: buffer to element inक्रमmation
 *
 * This function queries HW element inक्रमmation
 */
क्रमागत ice_status
ice_sched_query_elem(काष्ठा ice_hw *hw, u32 node_teid,
		     काष्ठा ice_aqc_txsched_elem_data *buf)
अणु
	u16 buf_size, num_elem_ret = 0;
	क्रमागत ice_status status;

	buf_size = माप(*buf);
	स_रखो(buf, 0, buf_size);
	buf->node_teid = cpu_to_le32(node_teid);
	status = ice_aq_query_sched_elems(hw, 1, buf, buf_size, &num_elem_ret,
					  शून्य);
	अगर (status || num_elem_ret != 1)
		ice_debug(hw, ICE_DBG_SCHED, "query element failed\n");
	वापस status;
पूर्ण

/**
 * ice_fw_supports_link_override
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Checks अगर the firmware supports link override
 */
bool ice_fw_supports_link_override(काष्ठा ice_hw *hw)
अणु
	अगर (hw->api_maj_ver == ICE_FW_API_LINK_OVERRIDE_MAJ) अणु
		अगर (hw->api_min_ver > ICE_FW_API_LINK_OVERRIDE_MIN)
			वापस true;
		अगर (hw->api_min_ver == ICE_FW_API_LINK_OVERRIDE_MIN &&
		    hw->api_patch >= ICE_FW_API_LINK_OVERRIDE_PATCH)
			वापस true;
	पूर्ण अन्यथा अगर (hw->api_maj_ver > ICE_FW_API_LINK_OVERRIDE_MAJ) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_get_link_शेष_override
 * @lकरो: poपूर्णांकer to the link शेष override काष्ठा
 * @pi: poपूर्णांकer to the port info काष्ठा
 *
 * Gets the link शेष override क्रम a port
 */
क्रमागत ice_status
ice_get_link_शेष_override(काष्ठा ice_link_शेष_override_tlv *lकरो,
			      काष्ठा ice_port_info *pi)
अणु
	u16 i, tlv, tlv_len, tlv_start, buf, offset;
	काष्ठा ice_hw *hw = pi->hw;
	क्रमागत ice_status status;

	status = ice_get_pfa_module_tlv(hw, &tlv, &tlv_len,
					ICE_SR_LINK_DEFAULT_OVERRIDE_PTR);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read link override TLV.\n");
		वापस status;
	पूर्ण

	/* Each port has its own config; calculate क्रम our port */
	tlv_start = tlv + pi->lport * ICE_SR_PFA_LINK_OVERRIDE_WORDS +
		ICE_SR_PFA_LINK_OVERRIDE_OFFSET;

	/* link options first */
	status = ice_पढ़ो_sr_word(hw, tlv_start, &buf);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read override link options.\n");
		वापस status;
	पूर्ण
	lकरो->options = buf & ICE_LINK_OVERRIDE_OPT_M;
	lकरो->phy_config = (buf & ICE_LINK_OVERRIDE_PHY_CFG_M) >>
		ICE_LINK_OVERRIDE_PHY_CFG_S;

	/* link PHY config */
	offset = tlv_start + ICE_SR_PFA_LINK_OVERRIDE_FEC_OFFSET;
	status = ice_पढ़ो_sr_word(hw, offset, &buf);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read override phy config.\n");
		वापस status;
	पूर्ण
	lकरो->fec_options = buf & ICE_LINK_OVERRIDE_FEC_OPT_M;

	/* PHY types low */
	offset = tlv_start + ICE_SR_PFA_LINK_OVERRIDE_PHY_OFFSET;
	क्रम (i = 0; i < ICE_SR_PFA_LINK_OVERRIDE_PHY_WORDS; i++) अणु
		status = ice_पढ़ो_sr_word(hw, (offset + i), &buf);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_INIT, "Failed to read override link options.\n");
			वापस status;
		पूर्ण
		/* shअगरt 16 bits at a समय to fill 64 bits */
		lकरो->phy_type_low |= ((u64)buf << (i * 16));
	पूर्ण

	/* PHY types high */
	offset = tlv_start + ICE_SR_PFA_LINK_OVERRIDE_PHY_OFFSET +
		ICE_SR_PFA_LINK_OVERRIDE_PHY_WORDS;
	क्रम (i = 0; i < ICE_SR_PFA_LINK_OVERRIDE_PHY_WORDS; i++) अणु
		status = ice_पढ़ो_sr_word(hw, (offset + i), &buf);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_INIT, "Failed to read override link options.\n");
			वापस status;
		पूर्ण
		/* shअगरt 16 bits at a समय to fill 64 bits */
		lकरो->phy_type_high |= ((u64)buf << (i * 16));
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_is_phy_caps_an_enabled - check अगर PHY capabilities स्वतःneg is enabled
 * @caps: get PHY capability data
 */
bool ice_is_phy_caps_an_enabled(काष्ठा ice_aqc_get_phy_caps_data *caps)
अणु
	अगर (caps->caps & ICE_AQC_PHY_AN_MODE ||
	    caps->low_घातer_ctrl_an & (ICE_AQC_PHY_AN_EN_CLAUSE28 |
				       ICE_AQC_PHY_AN_EN_CLAUSE73 |
				       ICE_AQC_PHY_AN_EN_CLAUSE37))
		वापस true;

	वापस false;
पूर्ण

/**
 * ice_aq_set_lldp_mib - Set the LLDP MIB
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @mib_type: Local, Remote or both Local and Remote MIBs
 * @buf: poपूर्णांकer to the caller-supplied buffer to store the MIB block
 * @buf_size: size of the buffer (in bytes)
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set the LLDP MIB. (0x0A08)
 */
क्रमागत ice_status
ice_aq_set_lldp_mib(काष्ठा ice_hw *hw, u8 mib_type, व्योम *buf, u16 buf_size,
		    काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_lldp_set_local_mib *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.lldp_set_mib;

	अगर (buf_size == 0 || !buf)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_set_local_mib);

	desc.flags |= cpu_to_le16((u16)ICE_AQ_FLAG_RD);
	desc.datalen = cpu_to_le16(buf_size);

	cmd->type = mib_type;
	cmd->length = cpu_to_le16(buf_size);

	वापस ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
पूर्ण

/**
 * ice_fw_supports_lldp_fltr_ctrl - check NVM version supports lldp_fltr_ctrl
 * @hw: poपूर्णांकer to HW काष्ठा
 */
bool ice_fw_supports_lldp_fltr_ctrl(काष्ठा ice_hw *hw)
अणु
	अगर (hw->mac_type != ICE_MAC_E810)
		वापस false;

	अगर (hw->api_maj_ver == ICE_FW_API_LLDP_FLTR_MAJ) अणु
		अगर (hw->api_min_ver > ICE_FW_API_LLDP_FLTR_MIN)
			वापस true;
		अगर (hw->api_min_ver == ICE_FW_API_LLDP_FLTR_MIN &&
		    hw->api_patch >= ICE_FW_API_LLDP_FLTR_PATCH)
			वापस true;
	पूर्ण अन्यथा अगर (hw->api_maj_ver > ICE_FW_API_LLDP_FLTR_MAJ) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * ice_lldp_fltr_add_हटाओ - add or हटाओ a LLDP Rx चयन filter
 * @hw: poपूर्णांकer to HW काष्ठा
 * @vsi_num: असलolute HW index क्रम VSI
 * @add: boolean क्रम अगर adding or removing a filter
 */
क्रमागत ice_status
ice_lldp_fltr_add_हटाओ(काष्ठा ice_hw *hw, u16 vsi_num, bool add)
अणु
	काष्ठा ice_aqc_lldp_filter_ctrl *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.lldp_filter_ctrl;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_filter_ctrl);

	अगर (add)
		cmd->cmd_flags = ICE_AQC_LLDP_FILTER_ACTION_ADD;
	अन्यथा
		cmd->cmd_flags = ICE_AQC_LLDP_FILTER_ACTION_DELETE;

	cmd->vsi_num = cpu_to_le16(vsi_num);

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
पूर्ण

/**
 * ice_fw_supports_report_dflt_cfg
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Checks अगर the firmware supports report शेष configuration
 */
bool ice_fw_supports_report_dflt_cfg(काष्ठा ice_hw *hw)
अणु
	अगर (hw->api_maj_ver == ICE_FW_API_REPORT_DFLT_CFG_MAJ) अणु
		अगर (hw->api_min_ver > ICE_FW_API_REPORT_DFLT_CFG_MIN)
			वापस true;
		अगर (hw->api_min_ver == ICE_FW_API_REPORT_DFLT_CFG_MIN &&
		    hw->api_patch >= ICE_FW_API_REPORT_DFLT_CFG_PATCH)
			वापस true;
	पूर्ण अन्यथा अगर (hw->api_maj_ver > ICE_FW_API_REPORT_DFLT_CFG_MAJ) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
