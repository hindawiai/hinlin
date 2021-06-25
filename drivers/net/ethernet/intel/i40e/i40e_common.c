<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#समावेश "i40e.h"
#समावेश "i40e_type.h"
#समावेश "i40e_adminq.h"
#समावेश "i40e_prototype.h"
#समावेश <linux/avf/virtchnl.h>

/**
 * i40e_set_mac_type - Sets MAC type
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function sets the mac type of the adapter based on the
 * venकरोr ID and device ID stored in the hw काष्ठाure.
 **/
i40e_status i40e_set_mac_type(काष्ठा i40e_hw *hw)
अणु
	i40e_status status = 0;

	अगर (hw->venकरोr_id == PCI_VENDOR_ID_INTEL) अणु
		चयन (hw->device_id) अणु
		हाल I40E_DEV_ID_SFP_XL710:
		हाल I40E_DEV_ID_QEMU:
		हाल I40E_DEV_ID_KX_B:
		हाल I40E_DEV_ID_KX_C:
		हाल I40E_DEV_ID_QSFP_A:
		हाल I40E_DEV_ID_QSFP_B:
		हाल I40E_DEV_ID_QSFP_C:
		हाल I40E_DEV_ID_5G_BASE_T_BC:
		हाल I40E_DEV_ID_10G_BASE_T:
		हाल I40E_DEV_ID_10G_BASE_T4:
		हाल I40E_DEV_ID_10G_BASE_T_BC:
		हाल I40E_DEV_ID_10G_B:
		हाल I40E_DEV_ID_10G_SFP:
		हाल I40E_DEV_ID_20G_KR2:
		हाल I40E_DEV_ID_20G_KR2_A:
		हाल I40E_DEV_ID_25G_B:
		हाल I40E_DEV_ID_25G_SFP28:
		हाल I40E_DEV_ID_X710_N3000:
		हाल I40E_DEV_ID_XXV710_N3000:
			hw->mac.type = I40E_MAC_XL710;
			अवरोध;
		हाल I40E_DEV_ID_KX_X722:
		हाल I40E_DEV_ID_QSFP_X722:
		हाल I40E_DEV_ID_SFP_X722:
		हाल I40E_DEV_ID_1G_BASE_T_X722:
		हाल I40E_DEV_ID_10G_BASE_T_X722:
		हाल I40E_DEV_ID_SFP_I_X722:
			hw->mac.type = I40E_MAC_X722;
			अवरोध;
		शेष:
			hw->mac.type = I40E_MAC_GENERIC;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = I40E_ERR_DEVICE_NOT_SUPPORTED;
	पूर्ण

	hw_dbg(hw, "i40e_set_mac_type found mac: %d, returns: %d\n",
		  hw->mac.type, status);
	वापस status;
पूर्ण

/**
 * i40e_aq_str - convert AQ err code to a string
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @aq_err: the AQ error code to convert
 **/
स्थिर अक्षर *i40e_aq_str(काष्ठा i40e_hw *hw, क्रमागत i40e_admin_queue_err aq_err)
अणु
	चयन (aq_err) अणु
	हाल I40E_AQ_RC_OK:
		वापस "OK";
	हाल I40E_AQ_RC_EPERM:
		वापस "I40E_AQ_RC_EPERM";
	हाल I40E_AQ_RC_ENOENT:
		वापस "I40E_AQ_RC_ENOENT";
	हाल I40E_AQ_RC_ESRCH:
		वापस "I40E_AQ_RC_ESRCH";
	हाल I40E_AQ_RC_EINTR:
		वापस "I40E_AQ_RC_EINTR";
	हाल I40E_AQ_RC_EIO:
		वापस "I40E_AQ_RC_EIO";
	हाल I40E_AQ_RC_ENXIO:
		वापस "I40E_AQ_RC_ENXIO";
	हाल I40E_AQ_RC_E2BIG:
		वापस "I40E_AQ_RC_E2BIG";
	हाल I40E_AQ_RC_EAGAIN:
		वापस "I40E_AQ_RC_EAGAIN";
	हाल I40E_AQ_RC_ENOMEM:
		वापस "I40E_AQ_RC_ENOMEM";
	हाल I40E_AQ_RC_EACCES:
		वापस "I40E_AQ_RC_EACCES";
	हाल I40E_AQ_RC_EFAULT:
		वापस "I40E_AQ_RC_EFAULT";
	हाल I40E_AQ_RC_EBUSY:
		वापस "I40E_AQ_RC_EBUSY";
	हाल I40E_AQ_RC_EEXIST:
		वापस "I40E_AQ_RC_EEXIST";
	हाल I40E_AQ_RC_EINVAL:
		वापस "I40E_AQ_RC_EINVAL";
	हाल I40E_AQ_RC_ENOTTY:
		वापस "I40E_AQ_RC_ENOTTY";
	हाल I40E_AQ_RC_ENOSPC:
		वापस "I40E_AQ_RC_ENOSPC";
	हाल I40E_AQ_RC_ENOSYS:
		वापस "I40E_AQ_RC_ENOSYS";
	हाल I40E_AQ_RC_दुस्फल:
		वापस "I40E_AQ_RC_ERANGE";
	हाल I40E_AQ_RC_EFLUSHED:
		वापस "I40E_AQ_RC_EFLUSHED";
	हाल I40E_AQ_RC_BAD_ADDR:
		वापस "I40E_AQ_RC_BAD_ADDR";
	हाल I40E_AQ_RC_EMODE:
		वापस "I40E_AQ_RC_EMODE";
	हाल I40E_AQ_RC_EFBIG:
		वापस "I40E_AQ_RC_EFBIG";
	पूर्ण

	snम_लिखो(hw->err_str, माप(hw->err_str), "%d", aq_err);
	वापस hw->err_str;
पूर्ण

/**
 * i40e_stat_str - convert status err code to a string
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @stat_err: the status error code to convert
 **/
स्थिर अक्षर *i40e_stat_str(काष्ठा i40e_hw *hw, i40e_status stat_err)
अणु
	चयन (stat_err) अणु
	हाल 0:
		वापस "OK";
	हाल I40E_ERR_NVM:
		वापस "I40E_ERR_NVM";
	हाल I40E_ERR_NVM_CHECKSUM:
		वापस "I40E_ERR_NVM_CHECKSUM";
	हाल I40E_ERR_PHY:
		वापस "I40E_ERR_PHY";
	हाल I40E_ERR_CONFIG:
		वापस "I40E_ERR_CONFIG";
	हाल I40E_ERR_PARAM:
		वापस "I40E_ERR_PARAM";
	हाल I40E_ERR_MAC_TYPE:
		वापस "I40E_ERR_MAC_TYPE";
	हाल I40E_ERR_UNKNOWN_PHY:
		वापस "I40E_ERR_UNKNOWN_PHY";
	हाल I40E_ERR_LINK_SETUP:
		वापस "I40E_ERR_LINK_SETUP";
	हाल I40E_ERR_ADAPTER_STOPPED:
		वापस "I40E_ERR_ADAPTER_STOPPED";
	हाल I40E_ERR_INVALID_MAC_ADDR:
		वापस "I40E_ERR_INVALID_MAC_ADDR";
	हाल I40E_ERR_DEVICE_NOT_SUPPORTED:
		वापस "I40E_ERR_DEVICE_NOT_SUPPORTED";
	हाल I40E_ERR_MASTER_REQUESTS_PENDING:
		वापस "I40E_ERR_MASTER_REQUESTS_PENDING";
	हाल I40E_ERR_INVALID_LINK_SETTINGS:
		वापस "I40E_ERR_INVALID_LINK_SETTINGS";
	हाल I40E_ERR_AUTONEG_NOT_COMPLETE:
		वापस "I40E_ERR_AUTONEG_NOT_COMPLETE";
	हाल I40E_ERR_RESET_FAILED:
		वापस "I40E_ERR_RESET_FAILED";
	हाल I40E_ERR_SWFW_SYNC:
		वापस "I40E_ERR_SWFW_SYNC";
	हाल I40E_ERR_NO_AVAILABLE_VSI:
		वापस "I40E_ERR_NO_AVAILABLE_VSI";
	हाल I40E_ERR_NO_MEMORY:
		वापस "I40E_ERR_NO_MEMORY";
	हाल I40E_ERR_BAD_PTR:
		वापस "I40E_ERR_BAD_PTR";
	हाल I40E_ERR_RING_FULL:
		वापस "I40E_ERR_RING_FULL";
	हाल I40E_ERR_INVALID_PD_ID:
		वापस "I40E_ERR_INVALID_PD_ID";
	हाल I40E_ERR_INVALID_QP_ID:
		वापस "I40E_ERR_INVALID_QP_ID";
	हाल I40E_ERR_INVALID_CQ_ID:
		वापस "I40E_ERR_INVALID_CQ_ID";
	हाल I40E_ERR_INVALID_CEQ_ID:
		वापस "I40E_ERR_INVALID_CEQ_ID";
	हाल I40E_ERR_INVALID_AEQ_ID:
		वापस "I40E_ERR_INVALID_AEQ_ID";
	हाल I40E_ERR_INVALID_SIZE:
		वापस "I40E_ERR_INVALID_SIZE";
	हाल I40E_ERR_INVALID_ARP_INDEX:
		वापस "I40E_ERR_INVALID_ARP_INDEX";
	हाल I40E_ERR_INVALID_FPM_FUNC_ID:
		वापस "I40E_ERR_INVALID_FPM_FUNC_ID";
	हाल I40E_ERR_QP_INVALID_MSG_SIZE:
		वापस "I40E_ERR_QP_INVALID_MSG_SIZE";
	हाल I40E_ERR_QP_TOOMANY_WRS_POSTED:
		वापस "I40E_ERR_QP_TOOMANY_WRS_POSTED";
	हाल I40E_ERR_INVALID_FRAG_COUNT:
		वापस "I40E_ERR_INVALID_FRAG_COUNT";
	हाल I40E_ERR_QUEUE_EMPTY:
		वापस "I40E_ERR_QUEUE_EMPTY";
	हाल I40E_ERR_INVALID_ALIGNMENT:
		वापस "I40E_ERR_INVALID_ALIGNMENT";
	हाल I40E_ERR_FLUSHED_QUEUE:
		वापस "I40E_ERR_FLUSHED_QUEUE";
	हाल I40E_ERR_INVALID_PUSH_PAGE_INDEX:
		वापस "I40E_ERR_INVALID_PUSH_PAGE_INDEX";
	हाल I40E_ERR_INVALID_IMM_DATA_SIZE:
		वापस "I40E_ERR_INVALID_IMM_DATA_SIZE";
	हाल I40E_ERR_TIMEOUT:
		वापस "I40E_ERR_TIMEOUT";
	हाल I40E_ERR_OPCODE_MISMATCH:
		वापस "I40E_ERR_OPCODE_MISMATCH";
	हाल I40E_ERR_CQP_COMPL_ERROR:
		वापस "I40E_ERR_CQP_COMPL_ERROR";
	हाल I40E_ERR_INVALID_VF_ID:
		वापस "I40E_ERR_INVALID_VF_ID";
	हाल I40E_ERR_INVALID_HMCFN_ID:
		वापस "I40E_ERR_INVALID_HMCFN_ID";
	हाल I40E_ERR_BACKING_PAGE_ERROR:
		वापस "I40E_ERR_BACKING_PAGE_ERROR";
	हाल I40E_ERR_NO_PBLCHUNKS_AVAILABLE:
		वापस "I40E_ERR_NO_PBLCHUNKS_AVAILABLE";
	हाल I40E_ERR_INVALID_PBLE_INDEX:
		वापस "I40E_ERR_INVALID_PBLE_INDEX";
	हाल I40E_ERR_INVALID_SD_INDEX:
		वापस "I40E_ERR_INVALID_SD_INDEX";
	हाल I40E_ERR_INVALID_PAGE_DESC_INDEX:
		वापस "I40E_ERR_INVALID_PAGE_DESC_INDEX";
	हाल I40E_ERR_INVALID_SD_TYPE:
		वापस "I40E_ERR_INVALID_SD_TYPE";
	हाल I40E_ERR_MEMCPY_FAILED:
		वापस "I40E_ERR_MEMCPY_FAILED";
	हाल I40E_ERR_INVALID_HMC_OBJ_INDEX:
		वापस "I40E_ERR_INVALID_HMC_OBJ_INDEX";
	हाल I40E_ERR_INVALID_HMC_OBJ_COUNT:
		वापस "I40E_ERR_INVALID_HMC_OBJ_COUNT";
	हाल I40E_ERR_INVALID_SRQ_ARM_LIMIT:
		वापस "I40E_ERR_INVALID_SRQ_ARM_LIMIT";
	हाल I40E_ERR_SRQ_ENABLED:
		वापस "I40E_ERR_SRQ_ENABLED";
	हाल I40E_ERR_ADMIN_QUEUE_ERROR:
		वापस "I40E_ERR_ADMIN_QUEUE_ERROR";
	हाल I40E_ERR_ADMIN_QUEUE_TIMEOUT:
		वापस "I40E_ERR_ADMIN_QUEUE_TIMEOUT";
	हाल I40E_ERR_BUF_TOO_SHORT:
		वापस "I40E_ERR_BUF_TOO_SHORT";
	हाल I40E_ERR_ADMIN_QUEUE_FULL:
		वापस "I40E_ERR_ADMIN_QUEUE_FULL";
	हाल I40E_ERR_ADMIN_QUEUE_NO_WORK:
		वापस "I40E_ERR_ADMIN_QUEUE_NO_WORK";
	हाल I40E_ERR_BAD_IWARP_CQE:
		वापस "I40E_ERR_BAD_IWARP_CQE";
	हाल I40E_ERR_NVM_BLANK_MODE:
		वापस "I40E_ERR_NVM_BLANK_MODE";
	हाल I40E_ERR_NOT_IMPLEMENTED:
		वापस "I40E_ERR_NOT_IMPLEMENTED";
	हाल I40E_ERR_PE_DOORBELL_NOT_ENABLED:
		वापस "I40E_ERR_PE_DOORBELL_NOT_ENABLED";
	हाल I40E_ERR_DIAG_TEST_FAILED:
		वापस "I40E_ERR_DIAG_TEST_FAILED";
	हाल I40E_ERR_NOT_READY:
		वापस "I40E_ERR_NOT_READY";
	हाल I40E_NOT_SUPPORTED:
		वापस "I40E_NOT_SUPPORTED";
	हाल I40E_ERR_FIRMWARE_API_VERSION:
		वापस "I40E_ERR_FIRMWARE_API_VERSION";
	हाल I40E_ERR_ADMIN_QUEUE_CRITICAL_ERROR:
		वापस "I40E_ERR_ADMIN_QUEUE_CRITICAL_ERROR";
	पूर्ण

	snम_लिखो(hw->err_str, माप(hw->err_str), "%d", stat_err);
	वापस hw->err_str;
पूर्ण

/**
 * i40e_debug_aq
 * @hw: debug mask related to admin queue
 * @mask: debug mask
 * @desc: poपूर्णांकer to admin queue descriptor
 * @buffer: poपूर्णांकer to command buffer
 * @buf_len: max length of buffer
 *
 * Dumps debug log about adminq command with descriptor contents.
 **/
व्योम i40e_debug_aq(काष्ठा i40e_hw *hw, क्रमागत i40e_debug_mask mask, व्योम *desc,
		   व्योम *buffer, u16 buf_len)
अणु
	काष्ठा i40e_aq_desc *aq_desc = (काष्ठा i40e_aq_desc *)desc;
	u32 effective_mask = hw->debug_mask & mask;
	अक्षर prefix[27];
	u16 len;
	u8 *buf = (u8 *)buffer;

	अगर (!effective_mask || !desc)
		वापस;

	len = le16_to_cpu(aq_desc->datalen);

	i40e_debug(hw, mask & I40E_DEBUG_AQ_DESCRIPTOR,
		   "AQ CMD: opcode 0x%04X, flags 0x%04X, datalen 0x%04X, retval 0x%04X\n",
		   le16_to_cpu(aq_desc->opcode),
		   le16_to_cpu(aq_desc->flags),
		   le16_to_cpu(aq_desc->datalen),
		   le16_to_cpu(aq_desc->retval));
	i40e_debug(hw, mask & I40E_DEBUG_AQ_DESCRIPTOR,
		   "\tcookie (h,l) 0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->cookie_high),
		   le32_to_cpu(aq_desc->cookie_low));
	i40e_debug(hw, mask & I40E_DEBUG_AQ_DESCRIPTOR,
		   "\tparam (0,1)  0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.पूर्णांकernal.param0),
		   le32_to_cpu(aq_desc->params.पूर्णांकernal.param1));
	i40e_debug(hw, mask & I40E_DEBUG_AQ_DESCRIPTOR,
		   "\taddr (h,l)   0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.बाह्यal.addr_high),
		   le32_to_cpu(aq_desc->params.बाह्यal.addr_low));

	अगर (buffer && buf_len != 0 && len != 0 &&
	    (effective_mask & I40E_DEBUG_AQ_DESC_BUFFER)) अणु
		i40e_debug(hw, mask, "AQ CMD Buffer:\n");
		अगर (buf_len < len)
			len = buf_len;

		snम_लिखो(prefix, माप(prefix),
			 "i40e %02x:%02x.%x: \t0x",
			 hw->bus.bus_id,
			 hw->bus.device,
			 hw->bus.func);

		prपूर्णांक_hex_dump(KERN_INFO, prefix, DUMP_PREFIX_OFFSET,
			       16, 1, buf, len, false);
	पूर्ण
पूर्ण

/**
 * i40e_check_asq_alive
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Returns true अगर Queue is enabled अन्यथा false.
 **/
bool i40e_check_asq_alive(काष्ठा i40e_hw *hw)
अणु
	अगर (hw->aq.asq.len)
		वापस !!(rd32(hw, hw->aq.asq.len) &
			  I40E_PF_ATQLEN_ATQENABLE_MASK);
	अन्यथा
		वापस false;
पूर्ण

/**
 * i40e_aq_queue_shutकरोwn
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @unloading: is the driver unloading itself
 *
 * Tell the Firmware that we're shutting करोwn the AdminQ and whether
 * or not the driver is unloading as well.
 **/
i40e_status i40e_aq_queue_shutकरोwn(काष्ठा i40e_hw *hw,
					     bool unloading)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_queue_shutकरोwn *cmd =
		(काष्ठा i40e_aqc_queue_shutकरोwn *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_queue_shutकरोwn);

	अगर (unloading)
		cmd->driver_unloading = cpu_to_le32(I40E_AQ_DRIVER_UNLOADING);
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_set_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_id: vsi fw index
 * @pf_lut: क्रम PF table set true, क्रम VSI table set false
 * @lut: poपूर्णांकer to the lut buffer provided by the caller
 * @lut_size: size of the lut buffer
 * @set: set true to set the table, false to get the table
 *
 * Internal function to get or set RSS look up table
 **/
अटल i40e_status i40e_aq_get_set_rss_lut(काष्ठा i40e_hw *hw,
					   u16 vsi_id, bool pf_lut,
					   u8 *lut, u16 lut_size,
					   bool set)
अणु
	i40e_status status;
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_get_set_rss_lut *cmd_resp =
		   (काष्ठा i40e_aqc_get_set_rss_lut *)&desc.params.raw;

	अगर (set)
		i40e_fill_शेष_direct_cmd_desc(&desc,
						  i40e_aqc_opc_set_rss_lut);
	अन्यथा
		i40e_fill_शेष_direct_cmd_desc(&desc,
						  i40e_aqc_opc_get_rss_lut);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_RD);

	cmd_resp->vsi_id =
			cpu_to_le16((u16)((vsi_id <<
					  I40E_AQC_SET_RSS_LUT_VSI_ID_SHIFT) &
					  I40E_AQC_SET_RSS_LUT_VSI_ID_MASK));
	cmd_resp->vsi_id |= cpu_to_le16((u16)I40E_AQC_SET_RSS_LUT_VSI_VALID);

	अगर (pf_lut)
		cmd_resp->flags |= cpu_to_le16((u16)
					((I40E_AQC_SET_RSS_LUT_TABLE_TYPE_PF <<
					I40E_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT) &
					I40E_AQC_SET_RSS_LUT_TABLE_TYPE_MASK));
	अन्यथा
		cmd_resp->flags |= cpu_to_le16((u16)
					((I40E_AQC_SET_RSS_LUT_TABLE_TYPE_VSI <<
					I40E_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT) &
					I40E_AQC_SET_RSS_LUT_TABLE_TYPE_MASK));

	status = i40e_asq_send_command(hw, &desc, lut, lut_size, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_id: vsi fw index
 * @pf_lut: क्रम PF table set true, क्रम VSI table set false
 * @lut: poपूर्णांकer to the lut buffer provided by the caller
 * @lut_size: size of the lut buffer
 *
 * get the RSS lookup table, PF or VSI type
 **/
i40e_status i40e_aq_get_rss_lut(काष्ठा i40e_hw *hw, u16 vsi_id,
				bool pf_lut, u8 *lut, u16 lut_size)
अणु
	वापस i40e_aq_get_set_rss_lut(hw, vsi_id, pf_lut, lut, lut_size,
				       false);
पूर्ण

/**
 * i40e_aq_set_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_id: vsi fw index
 * @pf_lut: क्रम PF table set true, क्रम VSI table set false
 * @lut: poपूर्णांकer to the lut buffer provided by the caller
 * @lut_size: size of the lut buffer
 *
 * set the RSS lookup table, PF or VSI type
 **/
i40e_status i40e_aq_set_rss_lut(काष्ठा i40e_hw *hw, u16 vsi_id,
				bool pf_lut, u8 *lut, u16 lut_size)
अणु
	वापस i40e_aq_get_set_rss_lut(hw, vsi_id, pf_lut, lut, lut_size, true);
पूर्ण

/**
 * i40e_aq_get_set_rss_key
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_id: vsi fw index
 * @key: poपूर्णांकer to key info काष्ठा
 * @set: set true to set the key, false to get the key
 *
 * get the RSS key per VSI
 **/
अटल i40e_status i40e_aq_get_set_rss_key(काष्ठा i40e_hw *hw,
				      u16 vsi_id,
				      काष्ठा i40e_aqc_get_set_rss_key_data *key,
				      bool set)
अणु
	i40e_status status;
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_get_set_rss_key *cmd_resp =
			(काष्ठा i40e_aqc_get_set_rss_key *)&desc.params.raw;
	u16 key_size = माप(काष्ठा i40e_aqc_get_set_rss_key_data);

	अगर (set)
		i40e_fill_शेष_direct_cmd_desc(&desc,
						  i40e_aqc_opc_set_rss_key);
	अन्यथा
		i40e_fill_शेष_direct_cmd_desc(&desc,
						  i40e_aqc_opc_get_rss_key);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_RD);

	cmd_resp->vsi_id =
			cpu_to_le16((u16)((vsi_id <<
					  I40E_AQC_SET_RSS_KEY_VSI_ID_SHIFT) &
					  I40E_AQC_SET_RSS_KEY_VSI_ID_MASK));
	cmd_resp->vsi_id |= cpu_to_le16((u16)I40E_AQC_SET_RSS_KEY_VSI_VALID);

	status = i40e_asq_send_command(hw, &desc, key, key_size, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_rss_key
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_id: vsi fw index
 * @key: poपूर्णांकer to key info काष्ठा
 *
 **/
i40e_status i40e_aq_get_rss_key(काष्ठा i40e_hw *hw,
				u16 vsi_id,
				काष्ठा i40e_aqc_get_set_rss_key_data *key)
अणु
	वापस i40e_aq_get_set_rss_key(hw, vsi_id, key, false);
पूर्ण

/**
 * i40e_aq_set_rss_key
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_id: vsi fw index
 * @key: poपूर्णांकer to key info काष्ठा
 *
 * set the RSS key per VSI
 **/
i40e_status i40e_aq_set_rss_key(काष्ठा i40e_hw *hw,
				u16 vsi_id,
				काष्ठा i40e_aqc_get_set_rss_key_data *key)
अणु
	वापस i40e_aq_get_set_rss_key(hw, vsi_id, key, true);
पूर्ण

/* The i40e_ptype_lookup table is used to convert from the 8-bit ptype in the
 * hardware to a bit-field that can be used by SW to more easily determine the
 * packet type.
 *
 * Macros are used to लघुen the table lines and make this table human
 * पढ़ोable.
 *
 * We store the PTYPE in the top byte of the bit field - this is just so that
 * we can check that the table करोesn't have a row missing, as the index पूर्णांकo
 * the table should be the PTYPE.
 *
 * Typical work flow:
 *
 * IF NOT i40e_ptype_lookup[ptype].known
 * THEN
 *      Packet is unknown
 * ELSE IF i40e_ptype_lookup[ptype].outer_ip == I40E_RX_PTYPE_OUTER_IP
 *      Use the rest of the fields to look at the tunnels, inner protocols, etc
 * ELSE
 *      Use the क्रमागत i40e_rx_l2_ptype to decode the packet type
 * ENDIF
 */

/* macro to make the table lines लघु */
#घोषणा I40E_PTT(PTYPE, OUTER_IP, OUTER_IP_VER, OUTER_FRAG, T, TE, TEF, I, PL)\
	अणु	PTYPE, \
		1, \
		I40E_RX_PTYPE_OUTER_##OUTER_IP, \
		I40E_RX_PTYPE_OUTER_##OUTER_IP_VER, \
		I40E_RX_PTYPE_##OUTER_FRAG, \
		I40E_RX_PTYPE_TUNNEL_##T, \
		I40E_RX_PTYPE_TUNNEL_END_##TE, \
		I40E_RX_PTYPE_##TEF, \
		I40E_RX_PTYPE_INNER_PROT_##I, \
		I40E_RX_PTYPE_PAYLOAD_LAYER_##PL पूर्ण

#घोषणा I40E_PTT_UNUSED_ENTRY(PTYPE) \
		अणु PTYPE, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण

/* लघुer macros makes the table fit but are terse */
#घोषणा I40E_RX_PTYPE_NOF		I40E_RX_PTYPE_NOT_FRAG
#घोषणा I40E_RX_PTYPE_FRG		I40E_RX_PTYPE_FRAG
#घोषणा I40E_RX_PTYPE_INNER_PROT_TS	I40E_RX_PTYPE_INNER_PROT_TIMESYNC

/* Lookup table mapping the HW PTYPE to the bit field क्रम decoding */
काष्ठा i40e_rx_ptype_decoded i40e_ptype_lookup[] = अणु
	/* L2 Packet types */
	I40E_PTT_UNUSED_ENTRY(0),
	I40E_PTT(1,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	I40E_PTT(2,  L2, NONE, NOF, NONE, NONE, NOF, TS,   PAY2),
	I40E_PTT(3,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	I40E_PTT_UNUSED_ENTRY(4),
	I40E_PTT_UNUSED_ENTRY(5),
	I40E_PTT(6,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	I40E_PTT(7,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	I40E_PTT_UNUSED_ENTRY(8),
	I40E_PTT_UNUSED_ENTRY(9),
	I40E_PTT(10, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	I40E_PTT(11, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	I40E_PTT(12, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(13, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(14, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(15, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(16, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(17, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(18, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(19, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(20, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(21, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),

	/* Non Tunneled IPv4 */
	I40E_PTT(22, IP, IPV4, FRG, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(23, IP, IPV4, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(24, IP, IPV4, NOF, NONE, NONE, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(25),
	I40E_PTT(26, IP, IPV4, NOF, NONE, NONE, NOF, TCP,  PAY4),
	I40E_PTT(27, IP, IPV4, NOF, NONE, NONE, NOF, SCTP, PAY4),
	I40E_PTT(28, IP, IPV4, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv4 --> IPv4 */
	I40E_PTT(29, IP, IPV4, NOF, IP_IP, IPV4, FRG, NONE, PAY3),
	I40E_PTT(30, IP, IPV4, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	I40E_PTT(31, IP, IPV4, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(32),
	I40E_PTT(33, IP, IPV4, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(34, IP, IPV4, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(35, IP, IPV4, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> IPv6 */
	I40E_PTT(36, IP, IPV4, NOF, IP_IP, IPV6, FRG, NONE, PAY3),
	I40E_PTT(37, IP, IPV4, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	I40E_PTT(38, IP, IPV4, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(39),
	I40E_PTT(40, IP, IPV4, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(41, IP, IPV4, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(42, IP, IPV4, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT */
	I40E_PTT(43, IP, IPV4, NOF, IP_GRENAT, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GRE/NAT --> IPv4 */
	I40E_PTT(44, IP, IPV4, NOF, IP_GRENAT, IPV4, FRG, NONE, PAY3),
	I40E_PTT(45, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, NONE, PAY3),
	I40E_PTT(46, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(47),
	I40E_PTT(48, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(49, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(50, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> IPv6 */
	I40E_PTT(51, IP, IPV4, NOF, IP_GRENAT, IPV6, FRG, NONE, PAY3),
	I40E_PTT(52, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, NONE, PAY3),
	I40E_PTT(53, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(54),
	I40E_PTT(55, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(56, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(57, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> MAC */
	I40E_PTT(58, IP, IPV4, NOF, IP_GRENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GRE/NAT --> MAC --> IPv4 */
	I40E_PTT(59, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, FRG, NONE, PAY3),
	I40E_PTT(60, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, NONE, PAY3),
	I40E_PTT(61, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(62),
	I40E_PTT(63, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(64, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(65, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT -> MAC --> IPv6 */
	I40E_PTT(66, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, FRG, NONE, PAY3),
	I40E_PTT(67, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, NONE, PAY3),
	I40E_PTT(68, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(69),
	I40E_PTT(70, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(71, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(72, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> MAC/VLAN */
	I40E_PTT(73, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, NONE, NOF, NONE, PAY3),

	/* IPv4 ---> GRE/NAT -> MAC/VLAN --> IPv4 */
	I40E_PTT(74, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, FRG, NONE, PAY3),
	I40E_PTT(75, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, NONE, PAY3),
	I40E_PTT(76, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(77),
	I40E_PTT(78, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(79, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(80, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, ICMP, PAY4),

	/* IPv4 -> GRE/NAT -> MAC/VLAN --> IPv6 */
	I40E_PTT(81, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, FRG, NONE, PAY3),
	I40E_PTT(82, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, NONE, PAY3),
	I40E_PTT(83, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(84),
	I40E_PTT(85, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(86, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(87, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, ICMP, PAY4),

	/* Non Tunneled IPv6 */
	I40E_PTT(88, IP, IPV6, FRG, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(89, IP, IPV6, NOF, NONE, NONE, NOF, NONE, PAY3),
	I40E_PTT(90, IP, IPV6, NOF, NONE, NONE, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(91),
	I40E_PTT(92, IP, IPV6, NOF, NONE, NONE, NOF, TCP,  PAY4),
	I40E_PTT(93, IP, IPV6, NOF, NONE, NONE, NOF, SCTP, PAY4),
	I40E_PTT(94, IP, IPV6, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv6 --> IPv4 */
	I40E_PTT(95,  IP, IPV6, NOF, IP_IP, IPV4, FRG, NONE, PAY3),
	I40E_PTT(96,  IP, IPV6, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	I40E_PTT(97,  IP, IPV6, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(98),
	I40E_PTT(99,  IP, IPV6, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(100, IP, IPV6, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(101, IP, IPV6, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> IPv6 */
	I40E_PTT(102, IP, IPV6, NOF, IP_IP, IPV6, FRG, NONE, PAY3),
	I40E_PTT(103, IP, IPV6, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	I40E_PTT(104, IP, IPV6, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(105),
	I40E_PTT(106, IP, IPV6, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(107, IP, IPV6, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(108, IP, IPV6, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT */
	I40E_PTT(109, IP, IPV6, NOF, IP_GRENAT, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> IPv4 */
	I40E_PTT(110, IP, IPV6, NOF, IP_GRENAT, IPV4, FRG, NONE, PAY3),
	I40E_PTT(111, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, NONE, PAY3),
	I40E_PTT(112, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(113),
	I40E_PTT(114, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(115, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(116, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> IPv6 */
	I40E_PTT(117, IP, IPV6, NOF, IP_GRENAT, IPV6, FRG, NONE, PAY3),
	I40E_PTT(118, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, NONE, PAY3),
	I40E_PTT(119, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(120),
	I40E_PTT(121, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(122, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(123, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC */
	I40E_PTT(124, IP, IPV6, NOF, IP_GRENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> MAC -> IPv4 */
	I40E_PTT(125, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, FRG, NONE, PAY3),
	I40E_PTT(126, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, NONE, PAY3),
	I40E_PTT(127, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(128),
	I40E_PTT(129, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(130, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(131, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC -> IPv6 */
	I40E_PTT(132, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, FRG, NONE, PAY3),
	I40E_PTT(133, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, NONE, PAY3),
	I40E_PTT(134, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(135),
	I40E_PTT(136, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(137, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(138, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC/VLAN */
	I40E_PTT(139, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> MAC/VLAN --> IPv4 */
	I40E_PTT(140, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, FRG, NONE, PAY3),
	I40E_PTT(141, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, NONE, PAY3),
	I40E_PTT(142, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(143),
	I40E_PTT(144, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, TCP,  PAY4),
	I40E_PTT(145, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, SCTP, PAY4),
	I40E_PTT(146, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC/VLAN --> IPv6 */
	I40E_PTT(147, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, FRG, NONE, PAY3),
	I40E_PTT(148, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, NONE, PAY3),
	I40E_PTT(149, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, UDP,  PAY4),
	I40E_PTT_UNUSED_ENTRY(150),
	I40E_PTT(151, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, TCP,  PAY4),
	I40E_PTT(152, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, SCTP, PAY4),
	I40E_PTT(153, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, ICMP, PAY4),

	/* unused entries */
	I40E_PTT_UNUSED_ENTRY(154),
	I40E_PTT_UNUSED_ENTRY(155),
	I40E_PTT_UNUSED_ENTRY(156),
	I40E_PTT_UNUSED_ENTRY(157),
	I40E_PTT_UNUSED_ENTRY(158),
	I40E_PTT_UNUSED_ENTRY(159),

	I40E_PTT_UNUSED_ENTRY(160),
	I40E_PTT_UNUSED_ENTRY(161),
	I40E_PTT_UNUSED_ENTRY(162),
	I40E_PTT_UNUSED_ENTRY(163),
	I40E_PTT_UNUSED_ENTRY(164),
	I40E_PTT_UNUSED_ENTRY(165),
	I40E_PTT_UNUSED_ENTRY(166),
	I40E_PTT_UNUSED_ENTRY(167),
	I40E_PTT_UNUSED_ENTRY(168),
	I40E_PTT_UNUSED_ENTRY(169),

	I40E_PTT_UNUSED_ENTRY(170),
	I40E_PTT_UNUSED_ENTRY(171),
	I40E_PTT_UNUSED_ENTRY(172),
	I40E_PTT_UNUSED_ENTRY(173),
	I40E_PTT_UNUSED_ENTRY(174),
	I40E_PTT_UNUSED_ENTRY(175),
	I40E_PTT_UNUSED_ENTRY(176),
	I40E_PTT_UNUSED_ENTRY(177),
	I40E_PTT_UNUSED_ENTRY(178),
	I40E_PTT_UNUSED_ENTRY(179),

	I40E_PTT_UNUSED_ENTRY(180),
	I40E_PTT_UNUSED_ENTRY(181),
	I40E_PTT_UNUSED_ENTRY(182),
	I40E_PTT_UNUSED_ENTRY(183),
	I40E_PTT_UNUSED_ENTRY(184),
	I40E_PTT_UNUSED_ENTRY(185),
	I40E_PTT_UNUSED_ENTRY(186),
	I40E_PTT_UNUSED_ENTRY(187),
	I40E_PTT_UNUSED_ENTRY(188),
	I40E_PTT_UNUSED_ENTRY(189),

	I40E_PTT_UNUSED_ENTRY(190),
	I40E_PTT_UNUSED_ENTRY(191),
	I40E_PTT_UNUSED_ENTRY(192),
	I40E_PTT_UNUSED_ENTRY(193),
	I40E_PTT_UNUSED_ENTRY(194),
	I40E_PTT_UNUSED_ENTRY(195),
	I40E_PTT_UNUSED_ENTRY(196),
	I40E_PTT_UNUSED_ENTRY(197),
	I40E_PTT_UNUSED_ENTRY(198),
	I40E_PTT_UNUSED_ENTRY(199),

	I40E_PTT_UNUSED_ENTRY(200),
	I40E_PTT_UNUSED_ENTRY(201),
	I40E_PTT_UNUSED_ENTRY(202),
	I40E_PTT_UNUSED_ENTRY(203),
	I40E_PTT_UNUSED_ENTRY(204),
	I40E_PTT_UNUSED_ENTRY(205),
	I40E_PTT_UNUSED_ENTRY(206),
	I40E_PTT_UNUSED_ENTRY(207),
	I40E_PTT_UNUSED_ENTRY(208),
	I40E_PTT_UNUSED_ENTRY(209),

	I40E_PTT_UNUSED_ENTRY(210),
	I40E_PTT_UNUSED_ENTRY(211),
	I40E_PTT_UNUSED_ENTRY(212),
	I40E_PTT_UNUSED_ENTRY(213),
	I40E_PTT_UNUSED_ENTRY(214),
	I40E_PTT_UNUSED_ENTRY(215),
	I40E_PTT_UNUSED_ENTRY(216),
	I40E_PTT_UNUSED_ENTRY(217),
	I40E_PTT_UNUSED_ENTRY(218),
	I40E_PTT_UNUSED_ENTRY(219),

	I40E_PTT_UNUSED_ENTRY(220),
	I40E_PTT_UNUSED_ENTRY(221),
	I40E_PTT_UNUSED_ENTRY(222),
	I40E_PTT_UNUSED_ENTRY(223),
	I40E_PTT_UNUSED_ENTRY(224),
	I40E_PTT_UNUSED_ENTRY(225),
	I40E_PTT_UNUSED_ENTRY(226),
	I40E_PTT_UNUSED_ENTRY(227),
	I40E_PTT_UNUSED_ENTRY(228),
	I40E_PTT_UNUSED_ENTRY(229),

	I40E_PTT_UNUSED_ENTRY(230),
	I40E_PTT_UNUSED_ENTRY(231),
	I40E_PTT_UNUSED_ENTRY(232),
	I40E_PTT_UNUSED_ENTRY(233),
	I40E_PTT_UNUSED_ENTRY(234),
	I40E_PTT_UNUSED_ENTRY(235),
	I40E_PTT_UNUSED_ENTRY(236),
	I40E_PTT_UNUSED_ENTRY(237),
	I40E_PTT_UNUSED_ENTRY(238),
	I40E_PTT_UNUSED_ENTRY(239),

	I40E_PTT_UNUSED_ENTRY(240),
	I40E_PTT_UNUSED_ENTRY(241),
	I40E_PTT_UNUSED_ENTRY(242),
	I40E_PTT_UNUSED_ENTRY(243),
	I40E_PTT_UNUSED_ENTRY(244),
	I40E_PTT_UNUSED_ENTRY(245),
	I40E_PTT_UNUSED_ENTRY(246),
	I40E_PTT_UNUSED_ENTRY(247),
	I40E_PTT_UNUSED_ENTRY(248),
	I40E_PTT_UNUSED_ENTRY(249),

	I40E_PTT_UNUSED_ENTRY(250),
	I40E_PTT_UNUSED_ENTRY(251),
	I40E_PTT_UNUSED_ENTRY(252),
	I40E_PTT_UNUSED_ENTRY(253),
	I40E_PTT_UNUSED_ENTRY(254),
	I40E_PTT_UNUSED_ENTRY(255)
पूर्ण;

/**
 * i40e_init_shared_code - Initialize the shared code
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * This assigns the MAC type and PHY code and inits the NVM.
 * Does not touch the hardware. This function must be called prior to any
 * other function in the shared code. The i40e_hw काष्ठाure should be
 * स_रखो to 0 prior to calling this function.  The following fields in
 * hw काष्ठाure should be filled in prior to calling this function:
 * hw_addr, back, device_id, venकरोr_id, subप्रणाली_device_id,
 * subप्रणाली_venकरोr_id, and revision_id
 **/
i40e_status i40e_init_shared_code(काष्ठा i40e_hw *hw)
अणु
	i40e_status status = 0;
	u32 port, ari, func_rid;

	i40e_set_mac_type(hw);

	चयन (hw->mac.type) अणु
	हाल I40E_MAC_XL710:
	हाल I40E_MAC_X722:
		अवरोध;
	शेष:
		वापस I40E_ERR_DEVICE_NOT_SUPPORTED;
	पूर्ण

	hw->phy.get_link_info = true;

	/* Determine port number and PF number*/
	port = (rd32(hw, I40E_PFGEN_PORTNUM) & I40E_PFGEN_PORTNUM_PORT_NUM_MASK)
					   >> I40E_PFGEN_PORTNUM_PORT_NUM_SHIFT;
	hw->port = (u8)port;
	ari = (rd32(hw, I40E_GLPCI_CAPSUP) & I40E_GLPCI_CAPSUP_ARI_EN_MASK) >>
						 I40E_GLPCI_CAPSUP_ARI_EN_SHIFT;
	func_rid = rd32(hw, I40E_PF_FUNC_RID);
	अगर (ari)
		hw->pf_id = (u8)(func_rid & 0xff);
	अन्यथा
		hw->pf_id = (u8)(func_rid & 0x7);

	status = i40e_init_nvm(hw);
	वापस status;
पूर्ण

/**
 * i40e_aq_mac_address_पढ़ो - Retrieve the MAC addresses
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @flags: a वापस indicator of what addresses were added to the addr store
 * @addrs: the requestor's mac addr store
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
अटल i40e_status i40e_aq_mac_address_पढ़ो(काष्ठा i40e_hw *hw,
				   u16 *flags,
				   काष्ठा i40e_aqc_mac_address_पढ़ो_data *addrs,
				   काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_mac_address_पढ़ो *cmd_data =
		(काष्ठा i40e_aqc_mac_address_पढ़ो *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_mac_address_पढ़ो);
	desc.flags |= cpu_to_le16(I40E_AQ_FLAG_BUF);

	status = i40e_asq_send_command(hw, &desc, addrs,
				       माप(*addrs), cmd_details);
	*flags = le16_to_cpu(cmd_data->command_flags);

	वापस status;
पूर्ण

/**
 * i40e_aq_mac_address_ग_लिखो - Change the MAC addresses
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @flags: indicates which MAC to be written
 * @mac_addr: address to ग_लिखो
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_mac_address_ग_लिखो(काष्ठा i40e_hw *hw,
				    u16 flags, u8 *mac_addr,
				    काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_mac_address_ग_लिखो *cmd_data =
		(काष्ठा i40e_aqc_mac_address_ग_लिखो *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_mac_address_ग_लिखो);
	cmd_data->command_flags = cpu_to_le16(flags);
	cmd_data->mac_sah = cpu_to_le16((u16)mac_addr[0] << 8 | mac_addr[1]);
	cmd_data->mac_sal = cpu_to_le32(((u32)mac_addr[2] << 24) |
					((u32)mac_addr[3] << 16) |
					((u32)mac_addr[4] << 8) |
					mac_addr[5]);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_get_mac_addr - get MAC address
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @mac_addr: poपूर्णांकer to MAC address
 *
 * Reads the adapter's MAC address from रेजिस्टर
 **/
i40e_status i40e_get_mac_addr(काष्ठा i40e_hw *hw, u8 *mac_addr)
अणु
	काष्ठा i40e_aqc_mac_address_पढ़ो_data addrs;
	i40e_status status;
	u16 flags = 0;

	status = i40e_aq_mac_address_पढ़ो(hw, &flags, &addrs, शून्य);

	अगर (flags & I40E_AQC_LAN_ADDR_VALID)
		ether_addr_copy(mac_addr, addrs.pf_lan_mac);

	वापस status;
पूर्ण

/**
 * i40e_get_port_mac_addr - get Port MAC address
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @mac_addr: poपूर्णांकer to Port MAC address
 *
 * Reads the adapter's Port MAC address
 **/
i40e_status i40e_get_port_mac_addr(काष्ठा i40e_hw *hw, u8 *mac_addr)
अणु
	काष्ठा i40e_aqc_mac_address_पढ़ो_data addrs;
	i40e_status status;
	u16 flags = 0;

	status = i40e_aq_mac_address_पढ़ो(hw, &flags, &addrs, शून्य);
	अगर (status)
		वापस status;

	अगर (flags & I40E_AQC_PORT_ADDR_VALID)
		ether_addr_copy(mac_addr, addrs.port_mac);
	अन्यथा
		status = I40E_ERR_INVALID_MAC_ADDR;

	वापस status;
पूर्ण

/**
 * i40e_pre_tx_queue_cfg - pre tx queue configure
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @queue: target PF queue index
 * @enable: state change request
 *
 * Handles hw requirement to indicate पूर्णांकention to enable
 * or disable target queue.
 **/
व्योम i40e_pre_tx_queue_cfg(काष्ठा i40e_hw *hw, u32 queue, bool enable)
अणु
	u32 असल_queue_idx = hw->func_caps.base_queue + queue;
	u32 reg_block = 0;
	u32 reg_val;

	अगर (असल_queue_idx >= 128) अणु
		reg_block = असल_queue_idx / 128;
		असल_queue_idx %= 128;
	पूर्ण

	reg_val = rd32(hw, I40E_GLLAN_TXPRE_QDIS(reg_block));
	reg_val &= ~I40E_GLLAN_TXPRE_QDIS_QINDX_MASK;
	reg_val |= (असल_queue_idx << I40E_GLLAN_TXPRE_QDIS_QINDX_SHIFT);

	अगर (enable)
		reg_val |= I40E_GLLAN_TXPRE_QDIS_CLEAR_QDIS_MASK;
	अन्यथा
		reg_val |= I40E_GLLAN_TXPRE_QDIS_SET_QDIS_MASK;

	wr32(hw, I40E_GLLAN_TXPRE_QDIS(reg_block), reg_val);
पूर्ण

/**
 *  i40e_पढ़ो_pba_string - Reads part number string from EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @pba_num: stores the part number string from the EEPROM
 *  @pba_num_size: part number string buffer length
 *
 *  Reads the part number string from the EEPROM.
 **/
i40e_status i40e_पढ़ो_pba_string(काष्ठा i40e_hw *hw, u8 *pba_num,
				 u32 pba_num_size)
अणु
	i40e_status status = 0;
	u16 pba_word = 0;
	u16 pba_size = 0;
	u16 pba_ptr = 0;
	u16 i = 0;

	status = i40e_पढ़ो_nvm_word(hw, I40E_SR_PBA_FLAGS, &pba_word);
	अगर (status || (pba_word != 0xFAFA)) अणु
		hw_dbg(hw, "Failed to read PBA flags or flag is invalid.\n");
		वापस status;
	पूर्ण

	status = i40e_पढ़ो_nvm_word(hw, I40E_SR_PBA_BLOCK_PTR, &pba_ptr);
	अगर (status) अणु
		hw_dbg(hw, "Failed to read PBA Block pointer.\n");
		वापस status;
	पूर्ण

	status = i40e_पढ़ो_nvm_word(hw, pba_ptr, &pba_size);
	अगर (status) अणु
		hw_dbg(hw, "Failed to read PBA Block size.\n");
		वापस status;
	पूर्ण

	/* Subtract one to get PBA word count (PBA Size word is included in
	 * total size)
	 */
	pba_size--;
	अगर (pba_num_size < (((u32)pba_size * 2) + 1)) अणु
		hw_dbg(hw, "Buffer too small for PBA data.\n");
		वापस I40E_ERR_PARAM;
	पूर्ण

	क्रम (i = 0; i < pba_size; i++) अणु
		status = i40e_पढ़ो_nvm_word(hw, (pba_ptr + 1) + i, &pba_word);
		अगर (status) अणु
			hw_dbg(hw, "Failed to read PBA Block word %d.\n", i);
			वापस status;
		पूर्ण

		pba_num[(i * 2)] = (pba_word >> 8) & 0xFF;
		pba_num[(i * 2) + 1] = pba_word & 0xFF;
	पूर्ण
	pba_num[(pba_size * 2)] = '\0';

	वापस status;
पूर्ण

/**
 * i40e_get_media_type - Gets media type
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल क्रमागत i40e_media_type i40e_get_media_type(काष्ठा i40e_hw *hw)
अणु
	क्रमागत i40e_media_type media;

	चयन (hw->phy.link_info.phy_type) अणु
	हाल I40E_PHY_TYPE_10GBASE_SR:
	हाल I40E_PHY_TYPE_10GBASE_LR:
	हाल I40E_PHY_TYPE_1000BASE_SX:
	हाल I40E_PHY_TYPE_1000BASE_LX:
	हाल I40E_PHY_TYPE_40GBASE_SR4:
	हाल I40E_PHY_TYPE_40GBASE_LR4:
	हाल I40E_PHY_TYPE_25GBASE_LR:
	हाल I40E_PHY_TYPE_25GBASE_SR:
		media = I40E_MEDIA_TYPE_FIBER;
		अवरोध;
	हाल I40E_PHY_TYPE_100BASE_TX:
	हाल I40E_PHY_TYPE_1000BASE_T:
	हाल I40E_PHY_TYPE_2_5GBASE_T_LINK_STATUS:
	हाल I40E_PHY_TYPE_5GBASE_T_LINK_STATUS:
	हाल I40E_PHY_TYPE_10GBASE_T:
		media = I40E_MEDIA_TYPE_BASET;
		अवरोध;
	हाल I40E_PHY_TYPE_10GBASE_CR1_CU:
	हाल I40E_PHY_TYPE_40GBASE_CR4_CU:
	हाल I40E_PHY_TYPE_10GBASE_CR1:
	हाल I40E_PHY_TYPE_40GBASE_CR4:
	हाल I40E_PHY_TYPE_10GBASE_SFPP_CU:
	हाल I40E_PHY_TYPE_40GBASE_AOC:
	हाल I40E_PHY_TYPE_10GBASE_AOC:
	हाल I40E_PHY_TYPE_25GBASE_CR:
	हाल I40E_PHY_TYPE_25GBASE_AOC:
	हाल I40E_PHY_TYPE_25GBASE_ACC:
		media = I40E_MEDIA_TYPE_DA;
		अवरोध;
	हाल I40E_PHY_TYPE_1000BASE_KX:
	हाल I40E_PHY_TYPE_10GBASE_KX4:
	हाल I40E_PHY_TYPE_10GBASE_KR:
	हाल I40E_PHY_TYPE_40GBASE_KR4:
	हाल I40E_PHY_TYPE_20GBASE_KR2:
	हाल I40E_PHY_TYPE_25GBASE_KR:
		media = I40E_MEDIA_TYPE_BACKPLANE;
		अवरोध;
	हाल I40E_PHY_TYPE_SGMII:
	हाल I40E_PHY_TYPE_XAUI:
	हाल I40E_PHY_TYPE_XFI:
	हाल I40E_PHY_TYPE_XLAUI:
	हाल I40E_PHY_TYPE_XLPPI:
	शेष:
		media = I40E_MEDIA_TYPE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस media;
पूर्ण

/**
 * i40e_poll_globr - Poll क्रम Global Reset completion
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @retry_limit: how many बार to retry beक्रमe failure
 **/
अटल i40e_status i40e_poll_globr(काष्ठा i40e_hw *hw,
				   u32 retry_limit)
अणु
	u32 cnt, reg = 0;

	क्रम (cnt = 0; cnt < retry_limit; cnt++) अणु
		reg = rd32(hw, I40E_GLGEN_RSTAT);
		अगर (!(reg & I40E_GLGEN_RSTAT_DEVSTATE_MASK))
			वापस 0;
		msleep(100);
	पूर्ण

	hw_dbg(hw, "Global reset failed.\n");
	hw_dbg(hw, "I40E_GLGEN_RSTAT = 0x%x\n", reg);

	वापस I40E_ERR_RESET_FAILED;
पूर्ण

#घोषणा I40E_PF_RESET_WAIT_COUNT_A0	200
#घोषणा I40E_PF_RESET_WAIT_COUNT	200
/**
 * i40e_pf_reset - Reset the PF
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Assuming someone अन्यथा has triggered a global reset,
 * assure the global reset is complete and then reset the PF
 **/
i40e_status i40e_pf_reset(काष्ठा i40e_hw *hw)
अणु
	u32 cnt = 0;
	u32 cnt1 = 0;
	u32 reg = 0;
	u32 grst_del;

	/* Poll क्रम Global Reset steady state in हाल of recent GRST.
	 * The grst delay value is in 100ms units, and we'll रुको a
	 * couple counts दीर्घer to be sure we करोn't just miss the end.
	 */
	grst_del = (rd32(hw, I40E_GLGEN_RSTCTL) &
		    I40E_GLGEN_RSTCTL_GRSTDEL_MASK) >>
		    I40E_GLGEN_RSTCTL_GRSTDEL_SHIFT;

	/* It can take upto 15 secs क्रम GRST steady state.
	 * Bump it to 16 secs max to be safe.
	 */
	grst_del = grst_del * 20;

	क्रम (cnt = 0; cnt < grst_del; cnt++) अणु
		reg = rd32(hw, I40E_GLGEN_RSTAT);
		अगर (!(reg & I40E_GLGEN_RSTAT_DEVSTATE_MASK))
			अवरोध;
		msleep(100);
	पूर्ण
	अगर (reg & I40E_GLGEN_RSTAT_DEVSTATE_MASK) अणु
		hw_dbg(hw, "Global reset polling failed to complete.\n");
		वापस I40E_ERR_RESET_FAILED;
	पूर्ण

	/* Now Wait क्रम the FW to be पढ़ोy */
	क्रम (cnt1 = 0; cnt1 < I40E_PF_RESET_WAIT_COUNT; cnt1++) अणु
		reg = rd32(hw, I40E_GLNVM_ULD);
		reg &= (I40E_GLNVM_ULD_CONF_CORE_DONE_MASK |
			I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK);
		अगर (reg == (I40E_GLNVM_ULD_CONF_CORE_DONE_MASK |
			    I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK)) अणु
			hw_dbg(hw, "Core and Global modules ready %d\n", cnt1);
			अवरोध;
		पूर्ण
		usleep_range(10000, 20000);
	पूर्ण
	अगर (!(reg & (I40E_GLNVM_ULD_CONF_CORE_DONE_MASK |
		     I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK))) अणु
		hw_dbg(hw, "wait for FW Reset complete timedout\n");
		hw_dbg(hw, "I40E_GLNVM_ULD = 0x%x\n", reg);
		वापस I40E_ERR_RESET_FAILED;
	पूर्ण

	/* If there was a Global Reset in progress when we got here,
	 * we करोn't need to करो the PF Reset
	 */
	अगर (!cnt) अणु
		u32 reg2 = 0;
		अगर (hw->revision_id == 0)
			cnt = I40E_PF_RESET_WAIT_COUNT_A0;
		अन्यथा
			cnt = I40E_PF_RESET_WAIT_COUNT;
		reg = rd32(hw, I40E_PFGEN_CTRL);
		wr32(hw, I40E_PFGEN_CTRL,
		     (reg | I40E_PFGEN_CTRL_PFSWR_MASK));
		क्रम (; cnt; cnt--) अणु
			reg = rd32(hw, I40E_PFGEN_CTRL);
			अगर (!(reg & I40E_PFGEN_CTRL_PFSWR_MASK))
				अवरोध;
			reg2 = rd32(hw, I40E_GLGEN_RSTAT);
			अगर (reg2 & I40E_GLGEN_RSTAT_DEVSTATE_MASK)
				अवरोध;
			usleep_range(1000, 2000);
		पूर्ण
		अगर (reg2 & I40E_GLGEN_RSTAT_DEVSTATE_MASK) अणु
			अगर (i40e_poll_globr(hw, grst_del))
				वापस I40E_ERR_RESET_FAILED;
		पूर्ण अन्यथा अगर (reg & I40E_PFGEN_CTRL_PFSWR_MASK) अणु
			hw_dbg(hw, "PF reset polling failed to complete.\n");
			वापस I40E_ERR_RESET_FAILED;
		पूर्ण
	पूर्ण

	i40e_clear_pxe_mode(hw);

	वापस 0;
पूर्ण

/**
 * i40e_clear_hw - clear out any left over hw state
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Clear queues and पूर्णांकerrupts, typically called at init समय,
 * but after the capabilities have been found so we know how many
 * queues and msix vectors have been allocated.
 **/
व्योम i40e_clear_hw(काष्ठा i40e_hw *hw)
अणु
	u32 num_queues, base_queue;
	u32 num_pf_पूर्णांक;
	u32 num_vf_पूर्णांक;
	u32 num_vfs;
	u32 i, j;
	u32 val;
	u32 eol = 0x7ff;

	/* get number of पूर्णांकerrupts, queues, and VFs */
	val = rd32(hw, I40E_GLPCI_CNF2);
	num_pf_पूर्णांक = (val & I40E_GLPCI_CNF2_MSI_X_PF_N_MASK) >>
		     I40E_GLPCI_CNF2_MSI_X_PF_N_SHIFT;
	num_vf_पूर्णांक = (val & I40E_GLPCI_CNF2_MSI_X_VF_N_MASK) >>
		     I40E_GLPCI_CNF2_MSI_X_VF_N_SHIFT;

	val = rd32(hw, I40E_PFLAN_QALLOC);
	base_queue = (val & I40E_PFLAN_QALLOC_FIRSTQ_MASK) >>
		     I40E_PFLAN_QALLOC_FIRSTQ_SHIFT;
	j = (val & I40E_PFLAN_QALLOC_LASTQ_MASK) >>
	    I40E_PFLAN_QALLOC_LASTQ_SHIFT;
	अगर (val & I40E_PFLAN_QALLOC_VALID_MASK)
		num_queues = (j - base_queue) + 1;
	अन्यथा
		num_queues = 0;

	val = rd32(hw, I40E_PF_VT_PFALLOC);
	i = (val & I40E_PF_VT_PFALLOC_FIRSTVF_MASK) >>
	    I40E_PF_VT_PFALLOC_FIRSTVF_SHIFT;
	j = (val & I40E_PF_VT_PFALLOC_LASTVF_MASK) >>
	    I40E_PF_VT_PFALLOC_LASTVF_SHIFT;
	अगर (val & I40E_PF_VT_PFALLOC_VALID_MASK)
		num_vfs = (j - i) + 1;
	अन्यथा
		num_vfs = 0;

	/* stop all the पूर्णांकerrupts */
	wr32(hw, I40E_PFINT_ICR0_ENA, 0);
	val = 0x3 << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT;
	क्रम (i = 0; i < num_pf_पूर्णांक - 2; i++)
		wr32(hw, I40E_PFINT_DYN_CTLN(i), val);

	/* Set the FIRSTQ_INDX field to 0x7FF in PFINT_LNKLSTx */
	val = eol << I40E_PFINT_LNKLST0_FIRSTQ_INDX_SHIFT;
	wr32(hw, I40E_PFINT_LNKLST0, val);
	क्रम (i = 0; i < num_pf_पूर्णांक - 2; i++)
		wr32(hw, I40E_PFINT_LNKLSTN(i), val);
	val = eol << I40E_VPINT_LNKLST0_FIRSTQ_INDX_SHIFT;
	क्रम (i = 0; i < num_vfs; i++)
		wr32(hw, I40E_VPINT_LNKLST0(i), val);
	क्रम (i = 0; i < num_vf_पूर्णांक - 2; i++)
		wr32(hw, I40E_VPINT_LNKLSTN(i), val);

	/* warn the HW of the coming Tx disables */
	क्रम (i = 0; i < num_queues; i++) अणु
		u32 असल_queue_idx = base_queue + i;
		u32 reg_block = 0;

		अगर (असल_queue_idx >= 128) अणु
			reg_block = असल_queue_idx / 128;
			असल_queue_idx %= 128;
		पूर्ण

		val = rd32(hw, I40E_GLLAN_TXPRE_QDIS(reg_block));
		val &= ~I40E_GLLAN_TXPRE_QDIS_QINDX_MASK;
		val |= (असल_queue_idx << I40E_GLLAN_TXPRE_QDIS_QINDX_SHIFT);
		val |= I40E_GLLAN_TXPRE_QDIS_SET_QDIS_MASK;

		wr32(hw, I40E_GLLAN_TXPRE_QDIS(reg_block), val);
	पूर्ण
	udelay(400);

	/* stop all the queues */
	क्रम (i = 0; i < num_queues; i++) अणु
		wr32(hw, I40E_QINT_TQCTL(i), 0);
		wr32(hw, I40E_QTX_ENA(i), 0);
		wr32(hw, I40E_QINT_RQCTL(i), 0);
		wr32(hw, I40E_QRX_ENA(i), 0);
	पूर्ण

	/* लघु रुको क्रम all queue disables to settle */
	udelay(50);
पूर्ण

/**
 * i40e_clear_pxe_mode - clear pxe operations mode
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Make sure all PXE mode settings are cleared, including things
 * like descriptor fetch/ग_लिखो-back mode.
 **/
व्योम i40e_clear_pxe_mode(काष्ठा i40e_hw *hw)
अणु
	u32 reg;

	अगर (i40e_check_asq_alive(hw))
		i40e_aq_clear_pxe_mode(hw, शून्य);

	/* Clear single descriptor fetch/ग_लिखो-back mode */
	reg = rd32(hw, I40E_GLLAN_RCTL_0);

	अगर (hw->revision_id == 0) अणु
		/* As a work around clear PXE_MODE instead of setting it */
		wr32(hw, I40E_GLLAN_RCTL_0, (reg & (~I40E_GLLAN_RCTL_0_PXE_MODE_MASK)));
	पूर्ण अन्यथा अणु
		wr32(hw, I40E_GLLAN_RCTL_0, (reg | I40E_GLLAN_RCTL_0_PXE_MODE_MASK));
	पूर्ण
पूर्ण

/**
 * i40e_led_is_mine - helper to find matching led
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @idx: index पूर्णांकo GPIO रेजिस्टरs
 *
 * वापसs: 0 अगर no match, otherwise the value of the GPIO_CTL रेजिस्टर
 */
अटल u32 i40e_led_is_mine(काष्ठा i40e_hw *hw, पूर्णांक idx)
अणु
	u32 gpio_val = 0;
	u32 port;

	अगर (!I40E_IS_X710TL_DEVICE(hw->device_id) &&
	    !hw->func_caps.led[idx])
		वापस 0;
	gpio_val = rd32(hw, I40E_GLGEN_GPIO_CTL(idx));
	port = (gpio_val & I40E_GLGEN_GPIO_CTL_PRT_NUM_MASK) >>
		I40E_GLGEN_GPIO_CTL_PRT_NUM_SHIFT;

	/* अगर PRT_NUM_NA is 1 then this LED is not port specअगरic, OR
	 * अगर it is not our port then ignore
	 */
	अगर ((gpio_val & I40E_GLGEN_GPIO_CTL_PRT_NUM_NA_MASK) ||
	    (port != hw->port))
		वापस 0;

	वापस gpio_val;
पूर्ण

#घोषणा I40E_FW_LED BIT(4)
#घोषणा I40E_LED_MODE_VALID (I40E_GLGEN_GPIO_CTL_LED_MODE_MASK >> \
			     I40E_GLGEN_GPIO_CTL_LED_MODE_SHIFT)

#घोषणा I40E_LED0 22

#घोषणा I40E_PIN_FUNC_SDP 0x0
#घोषणा I40E_PIN_FUNC_LED 0x1

/**
 * i40e_led_get - वापस current on/off mode
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * The value वापसed is the 'mode' field as defined in the
 * GPIO रेजिस्टर definitions: 0x0 = off, 0xf = on, and other
 * values are variations of possible behaviors relating to
 * blink, link, and wire.
 **/
u32 i40e_led_get(काष्ठा i40e_hw *hw)
अणु
	u32 mode = 0;
	पूर्णांक i;

	/* as per the करोcumentation GPIO 22-29 are the LED
	 * GPIO pins named LED0..LED7
	 */
	क्रम (i = I40E_LED0; i <= I40E_GLGEN_GPIO_CTL_MAX_INDEX; i++) अणु
		u32 gpio_val = i40e_led_is_mine(hw, i);

		अगर (!gpio_val)
			जारी;

		mode = (gpio_val & I40E_GLGEN_GPIO_CTL_LED_MODE_MASK) >>
			I40E_GLGEN_GPIO_CTL_LED_MODE_SHIFT;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

/**
 * i40e_led_set - set new on/off mode
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @mode: 0=off, 0xf=on (अन्यथा see manual क्रम mode details)
 * @blink: true अगर the LED should blink when on, false अगर steady
 *
 * अगर this function is used to turn on the blink it should
 * be used to disable the blink when restoring the original state.
 **/
व्योम i40e_led_set(काष्ठा i40e_hw *hw, u32 mode, bool blink)
अणु
	पूर्णांक i;

	अगर (mode & ~I40E_LED_MODE_VALID) अणु
		hw_dbg(hw, "invalid mode passed in %X\n", mode);
		वापस;
	पूर्ण

	/* as per the करोcumentation GPIO 22-29 are the LED
	 * GPIO pins named LED0..LED7
	 */
	क्रम (i = I40E_LED0; i <= I40E_GLGEN_GPIO_CTL_MAX_INDEX; i++) अणु
		u32 gpio_val = i40e_led_is_mine(hw, i);

		अगर (!gpio_val)
			जारी;

		अगर (I40E_IS_X710TL_DEVICE(hw->device_id)) अणु
			u32 pin_func = 0;

			अगर (mode & I40E_FW_LED)
				pin_func = I40E_PIN_FUNC_SDP;
			अन्यथा
				pin_func = I40E_PIN_FUNC_LED;

			gpio_val &= ~I40E_GLGEN_GPIO_CTL_PIN_FUNC_MASK;
			gpio_val |= ((pin_func <<
				     I40E_GLGEN_GPIO_CTL_PIN_FUNC_SHIFT) &
				     I40E_GLGEN_GPIO_CTL_PIN_FUNC_MASK);
		पूर्ण
		gpio_val &= ~I40E_GLGEN_GPIO_CTL_LED_MODE_MASK;
		/* this & is a bit of paranoia, but serves as a range check */
		gpio_val |= ((mode << I40E_GLGEN_GPIO_CTL_LED_MODE_SHIFT) &
			     I40E_GLGEN_GPIO_CTL_LED_MODE_MASK);

		अगर (blink)
			gpio_val |= BIT(I40E_GLGEN_GPIO_CTL_LED_BLINK_SHIFT);
		अन्यथा
			gpio_val &= ~BIT(I40E_GLGEN_GPIO_CTL_LED_BLINK_SHIFT);

		wr32(hw, I40E_GLGEN_GPIO_CTL(i), gpio_val);
		अवरोध;
	पूर्ण
पूर्ण

/* Admin command wrappers */

/**
 * i40e_aq_get_phy_capabilities
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @abilities: काष्ठाure क्रम PHY capabilities to be filled
 * @qualअगरied_modules: report Qualअगरied Modules
 * @report_init: report init capabilities (active are शेष)
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Returns the various PHY abilities supported on the Port.
 **/
i40e_status i40e_aq_get_phy_capabilities(काष्ठा i40e_hw *hw,
			bool qualअगरied_modules, bool report_init,
			काष्ठा i40e_aq_get_phy_abilities_resp *abilities,
			काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	i40e_status status;
	u16 abilities_size = माप(काष्ठा i40e_aq_get_phy_abilities_resp);
	u16 max_delay = I40E_MAX_PHY_TIMEOUT, total_delay = 0;

	अगर (!abilities)
		वापस I40E_ERR_PARAM;

	करो अणु
		i40e_fill_शेष_direct_cmd_desc(&desc,
					       i40e_aqc_opc_get_phy_abilities);

		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
		अगर (abilities_size > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

		अगर (qualअगरied_modules)
			desc.params.बाह्यal.param0 |=
			cpu_to_le32(I40E_AQ_PHY_REPORT_QUALIFIED_MODULES);

		अगर (report_init)
			desc.params.बाह्यal.param0 |=
			cpu_to_le32(I40E_AQ_PHY_REPORT_INITIAL_VALUES);

		status = i40e_asq_send_command(hw, &desc, abilities,
					       abilities_size, cmd_details);

		चयन (hw->aq.asq_last_status) अणु
		हाल I40E_AQ_RC_EIO:
			status = I40E_ERR_UNKNOWN_PHY;
			अवरोध;
		हाल I40E_AQ_RC_EAGAIN:
			usleep_range(1000, 2000);
			total_delay++;
			status = I40E_ERR_TIMEOUT;
			अवरोध;
		/* also covers I40E_AQ_RC_OK */
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण जबतक ((hw->aq.asq_last_status == I40E_AQ_RC_EAGAIN) &&
		(total_delay < max_delay));

	अगर (status)
		वापस status;

	अगर (report_init) अणु
		अगर (hw->mac.type ==  I40E_MAC_XL710 &&
		    hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
		    hw->aq.api_min_ver >= I40E_MINOR_VER_GET_LINK_INFO_XL710) अणु
			status = i40e_aq_get_link_info(hw, true, शून्य, शून्य);
		पूर्ण अन्यथा अणु
			hw->phy.phy_types = le32_to_cpu(abilities->phy_type);
			hw->phy.phy_types |=
					((u64)abilities->phy_type_ext << 32);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_set_phy_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @config: काष्ठाure with PHY configuration to be set
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set the various PHY configuration parameters
 * supported on the Port.One or more of the Set PHY config parameters may be
 * ignored in an MFP mode as the PF may not have the privilege to set some
 * of the PHY Config parameters. This status will be indicated by the
 * command response.
 **/
क्रमागत i40e_status_code i40e_aq_set_phy_config(काष्ठा i40e_hw *hw,
				काष्ठा i40e_aq_set_phy_config *config,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aq_set_phy_config *cmd =
			(काष्ठा i40e_aq_set_phy_config *)&desc.params.raw;
	क्रमागत i40e_status_code status;

	अगर (!config)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_phy_config);

	*cmd = *config;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

अटल noअंतरभूत_क्रम_stack क्रमागत i40e_status_code
i40e_set_fc_status(काष्ठा i40e_hw *hw,
		   काष्ठा i40e_aq_get_phy_abilities_resp *abilities,
		   bool atomic_restart)
अणु
	काष्ठा i40e_aq_set_phy_config config;
	क्रमागत i40e_fc_mode fc_mode = hw->fc.requested_mode;
	u8 छोड़ो_mask = 0x0;

	चयन (fc_mode) अणु
	हाल I40E_FC_FULL:
		छोड़ो_mask |= I40E_AQ_PHY_FLAG_PAUSE_TX;
		छोड़ो_mask |= I40E_AQ_PHY_FLAG_PAUSE_RX;
		अवरोध;
	हाल I40E_FC_RX_PAUSE:
		छोड़ो_mask |= I40E_AQ_PHY_FLAG_PAUSE_RX;
		अवरोध;
	हाल I40E_FC_TX_PAUSE:
		छोड़ो_mask |= I40E_AQ_PHY_FLAG_PAUSE_TX;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	स_रखो(&config, 0, माप(काष्ठा i40e_aq_set_phy_config));
	/* clear the old छोड़ो settings */
	config.abilities = abilities->abilities & ~(I40E_AQ_PHY_FLAG_PAUSE_TX) &
			   ~(I40E_AQ_PHY_FLAG_PAUSE_RX);
	/* set the new abilities */
	config.abilities |= छोड़ो_mask;
	/* If the abilities have changed, then set the new config */
	अगर (config.abilities == abilities->abilities)
		वापस 0;

	/* Auto restart link so settings take effect */
	अगर (atomic_restart)
		config.abilities |= I40E_AQ_PHY_ENABLE_ATOMIC_LINK;
	/* Copy over all the old settings */
	config.phy_type = abilities->phy_type;
	config.phy_type_ext = abilities->phy_type_ext;
	config.link_speed = abilities->link_speed;
	config.eee_capability = abilities->eee_capability;
	config.eeer = abilities->eeer_val;
	config.low_घातer_ctrl = abilities->d3_lpan;
	config.fec_config = abilities->fec_cfg_curr_mod_ext_info &
			    I40E_AQ_PHY_FEC_CONFIG_MASK;

	वापस i40e_aq_set_phy_config(hw, &config, शून्य);
पूर्ण

/**
 * i40e_set_fc
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @aq_failures: buffer to वापस AdminQ failure inक्रमmation
 * @atomic_restart: whether to enable atomic link restart
 *
 * Set the requested flow control mode using set_phy_config.
 **/
क्रमागत i40e_status_code i40e_set_fc(काष्ठा i40e_hw *hw, u8 *aq_failures,
				  bool atomic_restart)
अणु
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	क्रमागत i40e_status_code status;

	*aq_failures = 0x0;

	/* Get the current phy config */
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      शून्य);
	अगर (status) अणु
		*aq_failures |= I40E_SET_FC_AQ_FAIL_GET;
		वापस status;
	पूर्ण

	status = i40e_set_fc_status(hw, &abilities, atomic_restart);
	अगर (status)
		*aq_failures |= I40E_SET_FC_AQ_FAIL_SET;

	/* Update the link info */
	status = i40e_update_link_info(hw);
	अगर (status) अणु
		/* Wait a little bit (on 40G cards it someबार takes a really
		 * दीर्घ समय क्रम link to come back from the atomic reset)
		 * and try once more
		 */
		msleep(1000);
		status = i40e_update_link_info(hw);
	पूर्ण
	अगर (status)
		*aq_failures |= I40E_SET_FC_AQ_FAIL_UPDATE;

	वापस status;
पूर्ण

/**
 * i40e_aq_clear_pxe_mode
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Tell the firmware that the driver is taking over from PXE
 **/
i40e_status i40e_aq_clear_pxe_mode(काष्ठा i40e_hw *hw,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	i40e_status status;
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_clear_pxe *cmd =
		(काष्ठा i40e_aqc_clear_pxe *)&desc.params.raw;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_clear_pxe_mode);

	cmd->rx_cnt = 0x2;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	wr32(hw, I40E_GLLAN_RCTL_0, 0x1);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_link_restart_an
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @enable_link: अगर true: enable link, अगर false: disable link
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Sets up the link and restarts the Auto-Negotiation over the link.
 **/
i40e_status i40e_aq_set_link_restart_an(काष्ठा i40e_hw *hw,
					bool enable_link,
					काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_link_restart_an *cmd =
		(काष्ठा i40e_aqc_set_link_restart_an *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_link_restart_an);

	cmd->command = I40E_AQ_PHY_RESTART_AN;
	अगर (enable_link)
		cmd->command |= I40E_AQ_PHY_LINK_ENABLE;
	अन्यथा
		cmd->command &= ~I40E_AQ_PHY_LINK_ENABLE;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_link_info
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @enable_lse: enable/disable LinkStatusEvent reporting
 * @link: poपूर्णांकer to link status काष्ठाure - optional
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Returns the link status of the adapter.
 **/
i40e_status i40e_aq_get_link_info(काष्ठा i40e_hw *hw,
				bool enable_lse, काष्ठा i40e_link_status *link,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_get_link_status *resp =
		(काष्ठा i40e_aqc_get_link_status *)&desc.params.raw;
	काष्ठा i40e_link_status *hw_link_info = &hw->phy.link_info;
	i40e_status status;
	bool tx_छोड़ो, rx_छोड़ो;
	u16 command_flags;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_get_link_status);

	अगर (enable_lse)
		command_flags = I40E_AQ_LSE_ENABLE;
	अन्यथा
		command_flags = I40E_AQ_LSE_DISABLE;
	resp->command_flags = cpu_to_le16(command_flags);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (status)
		जाओ aq_get_link_info_निकास;

	/* save off old link status inक्रमmation */
	hw->phy.link_info_old = *hw_link_info;

	/* update link status */
	hw_link_info->phy_type = (क्रमागत i40e_aq_phy_type)resp->phy_type;
	hw->phy.media_type = i40e_get_media_type(hw);
	hw_link_info->link_speed = (क्रमागत i40e_aq_link_speed)resp->link_speed;
	hw_link_info->link_info = resp->link_info;
	hw_link_info->an_info = resp->an_info;
	hw_link_info->fec_info = resp->config & (I40E_AQ_CONFIG_FEC_KR_ENA |
						 I40E_AQ_CONFIG_FEC_RS_ENA);
	hw_link_info->ext_info = resp->ext_info;
	hw_link_info->loopback = resp->loopback & I40E_AQ_LOOPBACK_MASK;
	hw_link_info->max_frame_size = le16_to_cpu(resp->max_frame_size);
	hw_link_info->pacing = resp->config & I40E_AQ_CONFIG_PACING_MASK;

	/* update fc info */
	tx_छोड़ो = !!(resp->an_info & I40E_AQ_LINK_PAUSE_TX);
	rx_छोड़ो = !!(resp->an_info & I40E_AQ_LINK_PAUSE_RX);
	अगर (tx_छोड़ो & rx_छोड़ो)
		hw->fc.current_mode = I40E_FC_FULL;
	अन्यथा अगर (tx_छोड़ो)
		hw->fc.current_mode = I40E_FC_TX_PAUSE;
	अन्यथा अगर (rx_छोड़ो)
		hw->fc.current_mode = I40E_FC_RX_PAUSE;
	अन्यथा
		hw->fc.current_mode = I40E_FC_NONE;

	अगर (resp->config & I40E_AQ_CONFIG_CRC_ENA)
		hw_link_info->crc_enable = true;
	अन्यथा
		hw_link_info->crc_enable = false;

	अगर (resp->command_flags & cpu_to_le16(I40E_AQ_LSE_IS_ENABLED))
		hw_link_info->lse_enable = true;
	अन्यथा
		hw_link_info->lse_enable = false;

	अगर ((hw->mac.type == I40E_MAC_XL710) &&
	    (hw->aq.fw_maj_ver < 4 || (hw->aq.fw_maj_ver == 4 &&
	     hw->aq.fw_min_ver < 40)) && hw_link_info->phy_type == 0xE)
		hw_link_info->phy_type = I40E_PHY_TYPE_10GBASE_SFPP_CU;

	अगर (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE &&
	    hw->mac.type != I40E_MAC_X722) अणु
		__le32 पंचांगp;

		स_नकल(&पंचांगp, resp->link_type, माप(पंचांगp));
		hw->phy.phy_types = le32_to_cpu(पंचांगp);
		hw->phy.phy_types |= ((u64)resp->link_type_ext << 32);
	पूर्ण

	/* save link status inक्रमmation */
	अगर (link)
		*link = *hw_link_info;

	/* flag cleared so helper functions करोn't call AQ again */
	hw->phy.get_link_info = false;

aq_get_link_info_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_set_phy_पूर्णांक_mask
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @mask: पूर्णांकerrupt mask to be set
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set link पूर्णांकerrupt mask.
 **/
i40e_status i40e_aq_set_phy_पूर्णांक_mask(काष्ठा i40e_hw *hw,
				     u16 mask,
				     काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_phy_पूर्णांक_mask *cmd =
		(काष्ठा i40e_aqc_set_phy_पूर्णांक_mask *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_phy_पूर्णांक_mask);

	cmd->event_mask = cpu_to_le16(mask);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_phy_debug
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @cmd_flags: debug command flags
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Reset the बाह्यal PHY.
 **/
i40e_status i40e_aq_set_phy_debug(काष्ठा i40e_hw *hw, u8 cmd_flags,
				  काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_phy_debug *cmd =
		(काष्ठा i40e_aqc_set_phy_debug *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_phy_debug);

	cmd->command_flags = cmd_flags;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_is_aq_api_ver_ge
 * @aq: poपूर्णांकer to AdminQ info containing HW API version to compare
 * @maj: API major value
 * @min: API minor value
 *
 * Assert whether current HW API version is greater/equal than provided.
 **/
अटल bool i40e_is_aq_api_ver_ge(काष्ठा i40e_adminq_info *aq, u16 maj,
				  u16 min)
अणु
	वापस (aq->api_maj_ver > maj ||
		(aq->api_maj_ver == maj && aq->api_min_ver >= min));
पूर्ण

/**
 * i40e_aq_add_vsi
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_ctx: poपूर्णांकer to a vsi context काष्ठा
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add a VSI context to the hardware.
**/
i40e_status i40e_aq_add_vsi(काष्ठा i40e_hw *hw,
				काष्ठा i40e_vsi_context *vsi_ctx,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_get_update_vsi *cmd =
		(काष्ठा i40e_aqc_add_get_update_vsi *)&desc.params.raw;
	काष्ठा i40e_aqc_add_get_update_vsi_completion *resp =
		(काष्ठा i40e_aqc_add_get_update_vsi_completion *)
		&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_add_vsi);

	cmd->uplink_seid = cpu_to_le16(vsi_ctx->uplink_seid);
	cmd->connection_type = vsi_ctx->connection_type;
	cmd->vf_id = vsi_ctx->vf_num;
	cmd->vsi_flags = cpu_to_le16(vsi_ctx->flags);

	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));

	status = i40e_asq_send_command(hw, &desc, &vsi_ctx->info,
				    माप(vsi_ctx->info), cmd_details);

	अगर (status)
		जाओ aq_add_vsi_निकास;

	vsi_ctx->seid = le16_to_cpu(resp->seid);
	vsi_ctx->vsi_number = le16_to_cpu(resp->vsi_number);
	vsi_ctx->vsis_allocated = le16_to_cpu(resp->vsi_used);
	vsi_ctx->vsis_unallocated = le16_to_cpu(resp->vsi_मुक्त);

aq_add_vsi_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_set_शेष_vsi
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_set_शेष_vsi(काष्ठा i40e_hw *hw,
				    u16 seid,
				    काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)
		&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_vsi_promiscuous_modes);

	cmd->promiscuous_flags = cpu_to_le16(I40E_AQC_SET_VSI_DEFAULT);
	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_DEFAULT);
	cmd->seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_clear_शेष_vsi
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_clear_शेष_vsi(काष्ठा i40e_hw *hw,
				      u16 seid,
				      काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)
		&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_vsi_promiscuous_modes);

	cmd->promiscuous_flags = cpu_to_le16(0);
	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_DEFAULT);
	cmd->seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_unicast_promiscuous
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @set: set unicast promiscuous enable/disable
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 * @rx_only_promisc: flag to decide अगर egress traffic माला_लो mirrored in promisc
 **/
i40e_status i40e_aq_set_vsi_unicast_promiscuous(काष्ठा i40e_hw *hw,
				u16 seid, bool set,
				काष्ठा i40e_asq_cmd_details *cmd_details,
				bool rx_only_promisc)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	i40e_status status;
	u16 flags = 0;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					i40e_aqc_opc_set_vsi_promiscuous_modes);

	अगर (set) अणु
		flags |= I40E_AQC_SET_VSI_PROMISC_UNICAST;
		अगर (rx_only_promisc && i40e_is_aq_api_ver_ge(&hw->aq, 1, 5))
			flags |= I40E_AQC_SET_VSI_PROMISC_RX_ONLY;
	पूर्ण

	cmd->promiscuous_flags = cpu_to_le16(flags);

	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_UNICAST);
	अगर (i40e_is_aq_api_ver_ge(&hw->aq, 1, 5))
		cmd->valid_flags |=
			cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_RX_ONLY);

	cmd->seid = cpu_to_le16(seid);
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_multicast_promiscuous
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @set: set multicast promiscuous enable/disable
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_set_vsi_multicast_promiscuous(काष्ठा i40e_hw *hw,
				u16 seid, bool set, काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	i40e_status status;
	u16 flags = 0;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					i40e_aqc_opc_set_vsi_promiscuous_modes);

	अगर (set)
		flags |= I40E_AQC_SET_VSI_PROMISC_MULTICAST;

	cmd->promiscuous_flags = cpu_to_le16(flags);

	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_MULTICAST);

	cmd->seid = cpu_to_le16(seid);
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_mc_promisc_on_vlan
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @enable: set MAC L2 layer unicast promiscuous enable/disable क्रम a given VLAN
 * @vid: The VLAN tag filter - capture any multicast packet with this VLAN tag
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
क्रमागत i40e_status_code i40e_aq_set_vsi_mc_promisc_on_vlan(काष्ठा i40e_hw *hw,
							 u16 seid, bool enable,
							 u16 vid,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	क्रमागत i40e_status_code status;
	u16 flags = 0;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_vsi_promiscuous_modes);

	अगर (enable)
		flags |= I40E_AQC_SET_VSI_PROMISC_MULTICAST;

	cmd->promiscuous_flags = cpu_to_le16(flags);
	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_MULTICAST);
	cmd->seid = cpu_to_le16(seid);
	cmd->vlan_tag = cpu_to_le16(vid | I40E_AQC_SET_VSI_VLAN_VALID);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_uc_promisc_on_vlan
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @enable: set MAC L2 layer unicast promiscuous enable/disable क्रम a given VLAN
 * @vid: The VLAN tag filter - capture any unicast packet with this VLAN tag
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
क्रमागत i40e_status_code i40e_aq_set_vsi_uc_promisc_on_vlan(काष्ठा i40e_hw *hw,
							 u16 seid, bool enable,
							 u16 vid,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	क्रमागत i40e_status_code status;
	u16 flags = 0;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_vsi_promiscuous_modes);

	अगर (enable) अणु
		flags |= I40E_AQC_SET_VSI_PROMISC_UNICAST;
		अगर (i40e_is_aq_api_ver_ge(&hw->aq, 1, 5))
			flags |= I40E_AQC_SET_VSI_PROMISC_RX_ONLY;
	पूर्ण

	cmd->promiscuous_flags = cpu_to_le16(flags);
	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_UNICAST);
	अगर (i40e_is_aq_api_ver_ge(&hw->aq, 1, 5))
		cmd->valid_flags |=
			cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_RX_ONLY);
	cmd->seid = cpu_to_le16(seid);
	cmd->vlan_tag = cpu_to_le16(vid | I40E_AQC_SET_VSI_VLAN_VALID);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_bc_promisc_on_vlan
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @enable: set broadcast promiscuous enable/disable क्रम a given VLAN
 * @vid: The VLAN tag filter - capture any broadcast packet with this VLAN tag
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_set_vsi_bc_promisc_on_vlan(काष्ठा i40e_hw *hw,
				u16 seid, bool enable, u16 vid,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	i40e_status status;
	u16 flags = 0;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					i40e_aqc_opc_set_vsi_promiscuous_modes);

	अगर (enable)
		flags |= I40E_AQC_SET_VSI_PROMISC_BROADCAST;

	cmd->promiscuous_flags = cpu_to_le16(flags);
	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_BROADCAST);
	cmd->seid = cpu_to_le16(seid);
	cmd->vlan_tag = cpu_to_le16(vid | I40E_AQC_SET_VSI_VLAN_VALID);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_broadcast
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @set_filter: true to set filter, false to clear filter
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set or clear the broadcast promiscuous flag (filter) क्रम a given VSI.
 **/
i40e_status i40e_aq_set_vsi_broadcast(काष्ठा i40e_hw *hw,
				u16 seid, bool set_filter,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					i40e_aqc_opc_set_vsi_promiscuous_modes);

	अगर (set_filter)
		cmd->promiscuous_flags
			    |= cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_BROADCAST);
	अन्यथा
		cmd->promiscuous_flags
			    &= cpu_to_le16(~I40E_AQC_SET_VSI_PROMISC_BROADCAST);

	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_BROADCAST);
	cmd->seid = cpu_to_le16(seid);
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_vsi_vlan_promisc - control the VLAN promiscuous setting
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: vsi number
 * @enable: set MAC L2 layer unicast promiscuous enable/disable क्रम a given VLAN
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_set_vsi_vlan_promisc(काष्ठा i40e_hw *hw,
				       u16 seid, bool enable,
				       काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(काष्ठा i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	i40e_status status;
	u16 flags = 0;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					i40e_aqc_opc_set_vsi_promiscuous_modes);
	अगर (enable)
		flags |= I40E_AQC_SET_VSI_PROMISC_VLAN;

	cmd->promiscuous_flags = cpu_to_le16(flags);
	cmd->valid_flags = cpu_to_le16(I40E_AQC_SET_VSI_PROMISC_VLAN);
	cmd->seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_vsi_params - get VSI configuration info
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_ctx: poपूर्णांकer to a vsi context काष्ठा
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_get_vsi_params(काष्ठा i40e_hw *hw,
				काष्ठा i40e_vsi_context *vsi_ctx,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_get_update_vsi *cmd =
		(काष्ठा i40e_aqc_add_get_update_vsi *)&desc.params.raw;
	काष्ठा i40e_aqc_add_get_update_vsi_completion *resp =
		(काष्ठा i40e_aqc_add_get_update_vsi_completion *)
		&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_vsi_parameters);

	cmd->uplink_seid = cpu_to_le16(vsi_ctx->seid);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);

	status = i40e_asq_send_command(hw, &desc, &vsi_ctx->info,
				    माप(vsi_ctx->info), शून्य);

	अगर (status)
		जाओ aq_get_vsi_params_निकास;

	vsi_ctx->seid = le16_to_cpu(resp->seid);
	vsi_ctx->vsi_number = le16_to_cpu(resp->vsi_number);
	vsi_ctx->vsis_allocated = le16_to_cpu(resp->vsi_used);
	vsi_ctx->vsis_unallocated = le16_to_cpu(resp->vsi_मुक्त);

aq_get_vsi_params_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_update_vsi_params
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_ctx: poपूर्णांकer to a vsi context काष्ठा
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Update a VSI context.
 **/
i40e_status i40e_aq_update_vsi_params(काष्ठा i40e_hw *hw,
				काष्ठा i40e_vsi_context *vsi_ctx,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_get_update_vsi *cmd =
		(काष्ठा i40e_aqc_add_get_update_vsi *)&desc.params.raw;
	काष्ठा i40e_aqc_add_get_update_vsi_completion *resp =
		(काष्ठा i40e_aqc_add_get_update_vsi_completion *)
		&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_update_vsi_parameters);
	cmd->uplink_seid = cpu_to_le16(vsi_ctx->seid);

	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));

	status = i40e_asq_send_command(hw, &desc, &vsi_ctx->info,
				    माप(vsi_ctx->info), cmd_details);

	vsi_ctx->vsis_allocated = le16_to_cpu(resp->vsi_used);
	vsi_ctx->vsis_unallocated = le16_to_cpu(resp->vsi_मुक्त);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_चयन_config
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @buf: poपूर्णांकer to the result buffer
 * @buf_size: length of input buffer
 * @start_seid: seid to start क्रम the report, 0 == beginning
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Fill the buf with चयन configuration वापसed from AdminQ command
 **/
i40e_status i40e_aq_get_चयन_config(काष्ठा i40e_hw *hw,
				काष्ठा i40e_aqc_get_चयन_config_resp *buf,
				u16 buf_size, u16 *start_seid,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_चयन_seid *scfg =
		(काष्ठा i40e_aqc_चयन_seid *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_चयन_config);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (buf_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
	scfg->seid = cpu_to_le16(*start_seid);

	status = i40e_asq_send_command(hw, &desc, buf, buf_size, cmd_details);
	*start_seid = le16_to_cpu(scfg->seid);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_चयन_config
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @flags: bit flag values to set
 * @mode: cloud filter mode
 * @valid_flags: which bit flags to set
 * @mode: cloud filter mode
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set चयन configuration bits
 **/
क्रमागत i40e_status_code i40e_aq_set_चयन_config(काष्ठा i40e_hw *hw,
						u16 flags,
						u16 valid_flags, u8 mode,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_चयन_config *scfg =
		(काष्ठा i40e_aqc_set_चयन_config *)&desc.params.raw;
	क्रमागत i40e_status_code status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_चयन_config);
	scfg->flags = cpu_to_le16(flags);
	scfg->valid_flags = cpu_to_le16(valid_flags);
	scfg->mode = mode;
	अगर (hw->flags & I40E_HW_FLAG_802_1AD_CAPABLE) अणु
		scfg->चयन_tag = cpu_to_le16(hw->चयन_tag);
		scfg->first_tag = cpu_to_le16(hw->first_tag);
		scfg->second_tag = cpu_to_le16(hw->second_tag);
	पूर्ण
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_firmware_version
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @fw_major_version: firmware major version
 * @fw_minor_version: firmware minor version
 * @fw_build: firmware build number
 * @api_major_version: major queue version
 * @api_minor_version: minor queue version
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get the firmware version from the admin queue commands
 **/
i40e_status i40e_aq_get_firmware_version(काष्ठा i40e_hw *hw,
				u16 *fw_major_version, u16 *fw_minor_version,
				u32 *fw_build,
				u16 *api_major_version, u16 *api_minor_version,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_get_version *resp =
		(काष्ठा i40e_aqc_get_version *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_get_version);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (!status) अणु
		अगर (fw_major_version)
			*fw_major_version = le16_to_cpu(resp->fw_major);
		अगर (fw_minor_version)
			*fw_minor_version = le16_to_cpu(resp->fw_minor);
		अगर (fw_build)
			*fw_build = le32_to_cpu(resp->fw_build);
		अगर (api_major_version)
			*api_major_version = le16_to_cpu(resp->api_major);
		अगर (api_minor_version)
			*api_minor_version = le16_to_cpu(resp->api_minor);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_send_driver_version
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @dv: driver's major, minor version
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Send the driver version to the firmware
 **/
i40e_status i40e_aq_send_driver_version(काष्ठा i40e_hw *hw,
				काष्ठा i40e_driver_version *dv,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_driver_version *cmd =
		(काष्ठा i40e_aqc_driver_version *)&desc.params.raw;
	i40e_status status;
	u16 len;

	अगर (dv == शून्य)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_driver_version);

	desc.flags |= cpu_to_le16(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD);
	cmd->driver_major_ver = dv->major_version;
	cmd->driver_minor_ver = dv->minor_version;
	cmd->driver_build_ver = dv->build_version;
	cmd->driver_subbuild_ver = dv->subbuild_version;

	len = 0;
	जबतक (len < माप(dv->driver_string) &&
	       (dv->driver_string[len] < 0x80) &&
	       dv->driver_string[len])
		len++;
	status = i40e_asq_send_command(hw, &desc, dv->driver_string,
				       len, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_get_link_status - get status of the HW network link
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @link_up: poपूर्णांकer to bool (true/false = linkup/linkकरोwn)
 *
 * Variable link_up true अगर link is up, false अगर link is करोwn.
 * The variable link_up is invalid अगर वापसed value of status != 0
 *
 * Side effect: LinkStatusEvent reporting becomes enabled
 **/
i40e_status i40e_get_link_status(काष्ठा i40e_hw *hw, bool *link_up)
अणु
	i40e_status status = 0;

	अगर (hw->phy.get_link_info) अणु
		status = i40e_update_link_info(hw);

		अगर (status)
			i40e_debug(hw, I40E_DEBUG_LINK, "get link failed: status %d\n",
				   status);
	पूर्ण

	*link_up = hw->phy.link_info.link_info & I40E_AQ_LINK_UP;

	वापस status;
पूर्ण

/**
 * i40e_update_link_info - update status of the HW network link
 * @hw: poपूर्णांकer to the hw काष्ठा
 **/
noअंतरभूत_क्रम_stack i40e_status i40e_update_link_info(काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	i40e_status status = 0;

	status = i40e_aq_get_link_info(hw, true, शून्य, शून्य);
	अगर (status)
		वापस status;

	/* extra checking needed to ensure link info to user is समयly */
	अगर ((hw->phy.link_info.link_info & I40E_AQ_MEDIA_AVAILABLE) &&
	    ((hw->phy.link_info.link_info & I40E_AQ_LINK_UP) ||
	     !(hw->phy.link_info_old.link_info & I40E_AQ_LINK_UP))) अणु
		status = i40e_aq_get_phy_capabilities(hw, false, false,
						      &abilities, शून्य);
		अगर (status)
			वापस status;

		अगर (abilities.fec_cfg_curr_mod_ext_info &
		    I40E_AQ_ENABLE_FEC_AUTO)
			hw->phy.link_info.req_fec_info =
				(I40E_AQ_REQUEST_FEC_KR |
				 I40E_AQ_REQUEST_FEC_RS);
		अन्यथा
			hw->phy.link_info.req_fec_info =
				abilities.fec_cfg_curr_mod_ext_info &
				(I40E_AQ_REQUEST_FEC_KR |
				 I40E_AQ_REQUEST_FEC_RS);

		स_नकल(hw->phy.link_info.module_type, &abilities.module_type,
		       माप(hw->phy.link_info.module_type));
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_add_veb - Insert a VEB between the VSI and the MAC
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @uplink_seid: the MAC or other gizmo SEID
 * @करोwnlink_seid: the VSI SEID
 * @enabled_tc: biपंचांगap of TCs to be enabled
 * @शेष_port: true क्रम शेष port VSI, false क्रम control port
 * @veb_seid: poपूर्णांकer to where to put the resulting VEB SEID
 * @enable_stats: true to turn on VEB stats
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This asks the FW to add a VEB between the uplink and करोwnlink
 * elements.  If the uplink SEID is 0, this will be a भग्नing VEB.
 **/
i40e_status i40e_aq_add_veb(काष्ठा i40e_hw *hw, u16 uplink_seid,
				u16 करोwnlink_seid, u8 enabled_tc,
				bool शेष_port, u16 *veb_seid,
				bool enable_stats,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_veb *cmd =
		(काष्ठा i40e_aqc_add_veb *)&desc.params.raw;
	काष्ठा i40e_aqc_add_veb_completion *resp =
		(काष्ठा i40e_aqc_add_veb_completion *)&desc.params.raw;
	i40e_status status;
	u16 veb_flags = 0;

	/* SEIDs need to either both be set or both be 0 क्रम भग्नing VEB */
	अगर (!!uplink_seid != !!करोwnlink_seid)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_add_veb);

	cmd->uplink_seid = cpu_to_le16(uplink_seid);
	cmd->करोwnlink_seid = cpu_to_le16(करोwnlink_seid);
	cmd->enable_tcs = enabled_tc;
	अगर (!uplink_seid)
		veb_flags |= I40E_AQC_ADD_VEB_FLOATING;
	अगर (शेष_port)
		veb_flags |= I40E_AQC_ADD_VEB_PORT_TYPE_DEFAULT;
	अन्यथा
		veb_flags |= I40E_AQC_ADD_VEB_PORT_TYPE_DATA;

	/* reverse logic here: set the bitflag to disable the stats */
	अगर (!enable_stats)
		veb_flags |= I40E_AQC_ADD_VEB_ENABLE_DISABLE_STATS;

	cmd->veb_flags = cpu_to_le16(veb_flags);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (!status && veb_seid)
		*veb_seid = le16_to_cpu(resp->veb_seid);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_veb_parameters - Retrieve VEB parameters
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @veb_seid: the SEID of the VEB to query
 * @चयन_id: the uplink चयन id
 * @भग्नing: set to true अगर the VEB is भग्नing
 * @statistic_index: index of the stats counter block क्रम this VEB
 * @vebs_used: number of VEB's used by function
 * @vebs_मुक्त: total VEB's not reserved by any function
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This retrieves the parameters क्रम a particular VEB, specअगरied by
 * uplink_seid, and वापसs them to the caller.
 **/
i40e_status i40e_aq_get_veb_parameters(काष्ठा i40e_hw *hw,
				u16 veb_seid, u16 *चयन_id,
				bool *भग्नing, u16 *statistic_index,
				u16 *vebs_used, u16 *vebs_मुक्त,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_get_veb_parameters_completion *cmd_resp =
		(काष्ठा i40e_aqc_get_veb_parameters_completion *)
		&desc.params.raw;
	i40e_status status;

	अगर (veb_seid == 0)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_veb_parameters);
	cmd_resp->seid = cpu_to_le16(veb_seid);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);
	अगर (status)
		जाओ get_veb_निकास;

	अगर (चयन_id)
		*चयन_id = le16_to_cpu(cmd_resp->चयन_id);
	अगर (statistic_index)
		*statistic_index = le16_to_cpu(cmd_resp->statistic_index);
	अगर (vebs_used)
		*vebs_used = le16_to_cpu(cmd_resp->vebs_used);
	अगर (vebs_मुक्त)
		*vebs_मुक्त = le16_to_cpu(cmd_resp->vebs_मुक्त);
	अगर (भग्नing) अणु
		u16 flags = le16_to_cpu(cmd_resp->veb_flags);

		अगर (flags & I40E_AQC_ADD_VEB_FLOATING)
			*भग्नing = true;
		अन्यथा
			*भग्नing = false;
	पूर्ण

get_veb_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_add_macvlan
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: VSI क्रम the mac address
 * @mv_list: list of macvlans to be added
 * @count: length of the list
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add MAC/VLAN addresses to the HW filtering
 **/
i40e_status i40e_aq_add_macvlan(काष्ठा i40e_hw *hw, u16 seid,
			काष्ठा i40e_aqc_add_macvlan_element_data *mv_list,
			u16 count, काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_macvlan *cmd =
		(काष्ठा i40e_aqc_macvlan *)&desc.params.raw;
	i40e_status status;
	u16 buf_size;
	पूर्णांक i;

	अगर (count == 0 || !mv_list || !hw)
		वापस I40E_ERR_PARAM;

	buf_size = count * माप(*mv_list);

	/* prep the rest of the request */
	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_add_macvlan);
	cmd->num_addresses = cpu_to_le16(count);
	cmd->seid[0] = cpu_to_le16(I40E_AQC_MACVLAN_CMD_SEID_VALID | seid);
	cmd->seid[1] = 0;
	cmd->seid[2] = 0;

	क्रम (i = 0; i < count; i++)
		अगर (is_multicast_ether_addr(mv_list[i].mac_addr))
			mv_list[i].flags |=
			       cpu_to_le16(I40E_AQC_MACVLAN_ADD_USE_SHARED_MAC);

	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	अगर (buf_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, mv_list, buf_size,
				       cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_हटाओ_macvlan
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: VSI क्रम the mac address
 * @mv_list: list of macvlans to be हटाओd
 * @count: length of the list
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Remove MAC/VLAN addresses from the HW filtering
 **/
i40e_status i40e_aq_हटाओ_macvlan(काष्ठा i40e_hw *hw, u16 seid,
			काष्ठा i40e_aqc_हटाओ_macvlan_element_data *mv_list,
			u16 count, काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_macvlan *cmd =
		(काष्ठा i40e_aqc_macvlan *)&desc.params.raw;
	i40e_status status;
	u16 buf_size;

	अगर (count == 0 || !mv_list || !hw)
		वापस I40E_ERR_PARAM;

	buf_size = count * माप(*mv_list);

	/* prep the rest of the request */
	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_हटाओ_macvlan);
	cmd->num_addresses = cpu_to_le16(count);
	cmd->seid[0] = cpu_to_le16(I40E_AQC_MACVLAN_CMD_SEID_VALID | seid);
	cmd->seid[1] = 0;
	cmd->seid[2] = 0;

	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	अगर (buf_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, mv_list, buf_size,
				       cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_mirrorrule_op - Internal helper function to add/delete mirror rule
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @opcode: AQ opcode क्रम add or delete mirror rule
 * @sw_seid: Switch SEID (to which rule refers)
 * @rule_type: Rule Type (ingress/egress/VLAN)
 * @id: Destination VSI SEID or Rule ID
 * @count: length of the list
 * @mr_list: list of mirrored VSI SEIDs or VLAN IDs
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 * @rule_id: Rule ID वापसed from FW
 * @rules_used: Number of rules used in पूर्णांकernal चयन
 * @rules_मुक्त: Number of rules मुक्त in पूर्णांकernal चयन
 *
 * Add/Delete a mirror rule to a specअगरic चयन. Mirror rules are supported क्रम
 * VEBs/VEPA elements only
 **/
अटल i40e_status i40e_mirrorrule_op(काष्ठा i40e_hw *hw,
				u16 opcode, u16 sw_seid, u16 rule_type, u16 id,
				u16 count, __le16 *mr_list,
				काष्ठा i40e_asq_cmd_details *cmd_details,
				u16 *rule_id, u16 *rules_used, u16 *rules_मुक्त)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_delete_mirror_rule *cmd =
		(काष्ठा i40e_aqc_add_delete_mirror_rule *)&desc.params.raw;
	काष्ठा i40e_aqc_add_delete_mirror_rule_completion *resp =
	(काष्ठा i40e_aqc_add_delete_mirror_rule_completion *)&desc.params.raw;
	i40e_status status;
	u16 buf_size;

	buf_size = count * माप(*mr_list);

	/* prep the rest of the request */
	i40e_fill_शेष_direct_cmd_desc(&desc, opcode);
	cmd->seid = cpu_to_le16(sw_seid);
	cmd->rule_type = cpu_to_le16(rule_type &
				     I40E_AQC_MIRROR_RULE_TYPE_MASK);
	cmd->num_entries = cpu_to_le16(count);
	/* Dest VSI क्रम add, rule_id क्रम delete */
	cmd->destination = cpu_to_le16(id);
	अगर (mr_list) अणु
		desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF |
						I40E_AQ_FLAG_RD));
		अगर (buf_size > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
	पूर्ण

	status = i40e_asq_send_command(hw, &desc, mr_list, buf_size,
				       cmd_details);
	अगर (!status ||
	    hw->aq.asq_last_status == I40E_AQ_RC_ENOSPC) अणु
		अगर (rule_id)
			*rule_id = le16_to_cpu(resp->rule_id);
		अगर (rules_used)
			*rules_used = le16_to_cpu(resp->mirror_rules_used);
		अगर (rules_मुक्त)
			*rules_मुक्त = le16_to_cpu(resp->mirror_rules_मुक्त);
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_aq_add_mirrorrule - add a mirror rule
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @sw_seid: Switch SEID (to which rule refers)
 * @rule_type: Rule Type (ingress/egress/VLAN)
 * @dest_vsi: SEID of VSI to which packets will be mirrored
 * @count: length of the list
 * @mr_list: list of mirrored VSI SEIDs or VLAN IDs
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 * @rule_id: Rule ID वापसed from FW
 * @rules_used: Number of rules used in पूर्णांकernal चयन
 * @rules_मुक्त: Number of rules मुक्त in पूर्णांकernal चयन
 *
 * Add mirror rule. Mirror rules are supported क्रम VEBs or VEPA elements only
 **/
i40e_status i40e_aq_add_mirrorrule(काष्ठा i40e_hw *hw, u16 sw_seid,
			u16 rule_type, u16 dest_vsi, u16 count, __le16 *mr_list,
			काष्ठा i40e_asq_cmd_details *cmd_details,
			u16 *rule_id, u16 *rules_used, u16 *rules_मुक्त)
अणु
	अगर (!(rule_type == I40E_AQC_MIRROR_RULE_TYPE_ALL_INGRESS ||
	    rule_type == I40E_AQC_MIRROR_RULE_TYPE_ALL_EGRESS)) अणु
		अगर (count == 0 || !mr_list)
			वापस I40E_ERR_PARAM;
	पूर्ण

	वापस i40e_mirrorrule_op(hw, i40e_aqc_opc_add_mirror_rule, sw_seid,
				  rule_type, dest_vsi, count, mr_list,
				  cmd_details, rule_id, rules_used, rules_मुक्त);
पूर्ण

/**
 * i40e_aq_delete_mirrorrule - delete a mirror rule
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @sw_seid: Switch SEID (to which rule refers)
 * @rule_type: Rule Type (ingress/egress/VLAN)
 * @count: length of the list
 * @rule_id: Rule ID that is वापसed in the receive desc as part of
 *		add_mirrorrule.
 * @mr_list: list of mirrored VLAN IDs to be हटाओd
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 * @rules_used: Number of rules used in पूर्णांकernal चयन
 * @rules_मुक्त: Number of rules मुक्त in पूर्णांकernal चयन
 *
 * Delete a mirror rule. Mirror rules are supported क्रम VEBs/VEPA elements only
 **/
i40e_status i40e_aq_delete_mirrorrule(काष्ठा i40e_hw *hw, u16 sw_seid,
			u16 rule_type, u16 rule_id, u16 count, __le16 *mr_list,
			काष्ठा i40e_asq_cmd_details *cmd_details,
			u16 *rules_used, u16 *rules_मुक्त)
अणु
	/* Rule ID has to be valid except rule_type: INGRESS VLAN mirroring */
	अगर (rule_type == I40E_AQC_MIRROR_RULE_TYPE_VLAN) अणु
		/* count and mr_list shall be valid क्रम rule_type INGRESS VLAN
		 * mirroring. For other rule_type, count and rule_type should
		 * not matter.
		 */
		अगर (count == 0 || !mr_list)
			वापस I40E_ERR_PARAM;
	पूर्ण

	वापस i40e_mirrorrule_op(hw, i40e_aqc_opc_delete_mirror_rule, sw_seid,
				  rule_type, rule_id, count, mr_list,
				  cmd_details, शून्य, rules_used, rules_मुक्त);
पूर्ण

/**
 * i40e_aq_send_msg_to_vf
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vfid: VF id to send msg
 * @v_opcode: opcodes क्रम VF-PF communication
 * @v_retval: वापस error code
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 * @cmd_details: poपूर्णांकer to command details
 *
 * send msg to vf
 **/
i40e_status i40e_aq_send_msg_to_vf(काष्ठा i40e_hw *hw, u16 vfid,
				u32 v_opcode, u32 v_retval, u8 *msg, u16 msglen,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_pf_vf_message *cmd =
		(काष्ठा i40e_aqc_pf_vf_message *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_send_msg_to_vf);
	cmd->id = cpu_to_le32(vfid);
	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_SI);
	अगर (msglen) अणु
		desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF |
						I40E_AQ_FLAG_RD));
		अगर (msglen > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
		desc.datalen = cpu_to_le16(msglen);
	पूर्ण
	status = i40e_asq_send_command(hw, &desc, msg, msglen, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_debug_पढ़ो_रेजिस्टर
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg_addr: रेजिस्टर address
 * @reg_val: रेजिस्टर value
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Read the रेजिस्टर using the admin queue commands
 **/
i40e_status i40e_aq_debug_पढ़ो_रेजिस्टर(काष्ठा i40e_hw *hw,
				u32 reg_addr, u64 *reg_val,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_debug_reg_पढ़ो_ग_लिखो *cmd_resp =
		(काष्ठा i40e_aqc_debug_reg_पढ़ो_ग_लिखो *)&desc.params.raw;
	i40e_status status;

	अगर (reg_val == शून्य)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_debug_पढ़ो_reg);

	cmd_resp->address = cpu_to_le32(reg_addr);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (!status) अणु
		*reg_val = ((u64)le32_to_cpu(cmd_resp->value_high) << 32) |
			   (u64)le32_to_cpu(cmd_resp->value_low);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_debug_ग_लिखो_रेजिस्टर
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg_addr: रेजिस्टर address
 * @reg_val: रेजिस्टर value
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Write to a रेजिस्टर using the admin queue commands
 **/
i40e_status i40e_aq_debug_ग_लिखो_रेजिस्टर(काष्ठा i40e_hw *hw,
					u32 reg_addr, u64 reg_val,
					काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_debug_reg_पढ़ो_ग_लिखो *cmd =
		(काष्ठा i40e_aqc_debug_reg_पढ़ो_ग_लिखो *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_debug_ग_लिखो_reg);

	cmd->address = cpu_to_le32(reg_addr);
	cmd->value_high = cpu_to_le32((u32)(reg_val >> 32));
	cmd->value_low = cpu_to_le32((u32)(reg_val & 0xFFFFFFFF));

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_request_resource
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @resource: resource id
 * @access: access type
 * @sdp_number: resource number
 * @समयout: the maximum समय in ms that the driver may hold the resource
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * requests common resource using the admin queue commands
 **/
i40e_status i40e_aq_request_resource(काष्ठा i40e_hw *hw,
				क्रमागत i40e_aq_resources_ids resource,
				क्रमागत i40e_aq_resource_access_type access,
				u8 sdp_number, u64 *समयout,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_request_resource *cmd_resp =
		(काष्ठा i40e_aqc_request_resource *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_request_resource);

	cmd_resp->resource_id = cpu_to_le16(resource);
	cmd_resp->access_type = cpu_to_le16(access);
	cmd_resp->resource_number = cpu_to_le32(sdp_number);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);
	/* The completion specअगरies the maximum समय in ms that the driver
	 * may hold the resource in the Timeout field.
	 * If the resource is held by someone अन्यथा, the command completes with
	 * busy वापस value and the समयout field indicates the maximum समय
	 * the current owner of the resource has to मुक्त it.
	 */
	अगर (!status || hw->aq.asq_last_status == I40E_AQ_RC_EBUSY)
		*समयout = le32_to_cpu(cmd_resp->समयout);

	वापस status;
पूर्ण

/**
 * i40e_aq_release_resource
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @resource: resource id
 * @sdp_number: resource number
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * release common resource using the admin queue commands
 **/
i40e_status i40e_aq_release_resource(काष्ठा i40e_hw *hw,
				क्रमागत i40e_aq_resources_ids resource,
				u8 sdp_number,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_request_resource *cmd =
		(काष्ठा i40e_aqc_request_resource *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_release_resource);

	cmd->resource_id = cpu_to_le16(resource);
	cmd->resource_number = cpu_to_le32(sdp_number);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_पढ़ो_nvm
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @module_poपूर्णांकer: module poपूर्णांकer location in words from the NVM beginning
 * @offset: byte offset from the module beginning
 * @length: length of the section to be पढ़ो (in bytes from the offset)
 * @data: command buffer (size [bytes] = length)
 * @last_command: tells अगर this is the last command in a series
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Read the NVM using the admin queue commands
 **/
i40e_status i40e_aq_पढ़ो_nvm(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
				u32 offset, u16 length, व्योम *data,
				bool last_command,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_nvm_update *cmd =
		(काष्ठा i40e_aqc_nvm_update *)&desc.params.raw;
	i40e_status status;

	/* In offset the highest byte must be zeroed. */
	अगर (offset & 0xFF000000) अणु
		status = I40E_ERR_PARAM;
		जाओ i40e_aq_पढ़ो_nvm_निकास;
	पूर्ण

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_nvm_पढ़ो);

	/* If this is the last command in a series, set the proper flag. */
	अगर (last_command)
		cmd->command_flags |= I40E_AQ_NVM_LAST_CMD;
	cmd->module_poपूर्णांकer = module_poपूर्णांकer;
	cmd->offset = cpu_to_le32(offset);
	cmd->length = cpu_to_le16(length);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (length > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, data, length, cmd_details);

i40e_aq_पढ़ो_nvm_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_erase_nvm
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @module_poपूर्णांकer: module poपूर्णांकer location in words from the NVM beginning
 * @offset: offset in the module (expressed in 4 KB from module's beginning)
 * @length: length of the section to be erased (expressed in 4 KB)
 * @last_command: tells अगर this is the last command in a series
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Erase the NVM sector using the admin queue commands
 **/
i40e_status i40e_aq_erase_nvm(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
			      u32 offset, u16 length, bool last_command,
			      काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_nvm_update *cmd =
		(काष्ठा i40e_aqc_nvm_update *)&desc.params.raw;
	i40e_status status;

	/* In offset the highest byte must be zeroed. */
	अगर (offset & 0xFF000000) अणु
		status = I40E_ERR_PARAM;
		जाओ i40e_aq_erase_nvm_निकास;
	पूर्ण

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_nvm_erase);

	/* If this is the last command in a series, set the proper flag. */
	अगर (last_command)
		cmd->command_flags |= I40E_AQ_NVM_LAST_CMD;
	cmd->module_poपूर्णांकer = module_poपूर्णांकer;
	cmd->offset = cpu_to_le32(offset);
	cmd->length = cpu_to_le16(length);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

i40e_aq_erase_nvm_निकास:
	वापस status;
पूर्ण

/**
 * i40e_parse_discover_capabilities
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @buff: poपूर्णांकer to a buffer containing device/function capability records
 * @cap_count: number of capability records in the list
 * @list_type_opc: type of capabilities list to parse
 *
 * Parse the device/function capabilities list.
 **/
अटल व्योम i40e_parse_discover_capabilities(काष्ठा i40e_hw *hw, व्योम *buff,
				     u32 cap_count,
				     क्रमागत i40e_admin_queue_opc list_type_opc)
अणु
	काष्ठा i40e_aqc_list_capabilities_element_resp *cap;
	u32 valid_functions, num_functions;
	u32 number, logical_id, phys_id;
	काष्ठा i40e_hw_capabilities *p;
	u16 id, ocp_cfg_word0;
	i40e_status status;
	u8 major_rev;
	u32 i = 0;

	cap = (काष्ठा i40e_aqc_list_capabilities_element_resp *) buff;

	अगर (list_type_opc == i40e_aqc_opc_list_dev_capabilities)
		p = &hw->dev_caps;
	अन्यथा अगर (list_type_opc == i40e_aqc_opc_list_func_capabilities)
		p = &hw->func_caps;
	अन्यथा
		वापस;

	क्रम (i = 0; i < cap_count; i++, cap++) अणु
		id = le16_to_cpu(cap->id);
		number = le32_to_cpu(cap->number);
		logical_id = le32_to_cpu(cap->logical_id);
		phys_id = le32_to_cpu(cap->phys_id);
		major_rev = cap->major_rev;

		चयन (id) अणु
		हाल I40E_AQ_CAP_ID_SWITCH_MODE:
			p->चयन_mode = number;
			अवरोध;
		हाल I40E_AQ_CAP_ID_MNG_MODE:
			p->management_mode = number;
			अगर (major_rev > 1) अणु
				p->mng_protocols_over_mctp = logical_id;
				i40e_debug(hw, I40E_DEBUG_INIT,
					   "HW Capability: Protocols over MCTP = %d\n",
					   p->mng_protocols_over_mctp);
			पूर्ण अन्यथा अणु
				p->mng_protocols_over_mctp = 0;
			पूर्ण
			अवरोध;
		हाल I40E_AQ_CAP_ID_NPAR_ACTIVE:
			p->npar_enable = number;
			अवरोध;
		हाल I40E_AQ_CAP_ID_OS2BMC_CAP:
			p->os2bmc = number;
			अवरोध;
		हाल I40E_AQ_CAP_ID_FUNCTIONS_VALID:
			p->valid_functions = number;
			अवरोध;
		हाल I40E_AQ_CAP_ID_SRIOV:
			अगर (number == 1)
				p->sr_iov_1_1 = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_VF:
			p->num_vfs = number;
			p->vf_base_id = logical_id;
			अवरोध;
		हाल I40E_AQ_CAP_ID_VMDQ:
			अगर (number == 1)
				p->vmdq = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_8021QBG:
			अगर (number == 1)
				p->evb_802_1_qbg = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_8021QBR:
			अगर (number == 1)
				p->evb_802_1_qbh = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_VSI:
			p->num_vsis = number;
			अवरोध;
		हाल I40E_AQ_CAP_ID_DCB:
			अगर (number == 1) अणु
				p->dcb = true;
				p->enabled_tcmap = logical_id;
				p->maxtc = phys_id;
			पूर्ण
			अवरोध;
		हाल I40E_AQ_CAP_ID_FCOE:
			अगर (number == 1)
				p->fcoe = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_ISCSI:
			अगर (number == 1)
				p->iscsi = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_RSS:
			p->rss = true;
			p->rss_table_size = number;
			p->rss_table_entry_width = logical_id;
			अवरोध;
		हाल I40E_AQ_CAP_ID_RXQ:
			p->num_rx_qp = number;
			p->base_queue = phys_id;
			अवरोध;
		हाल I40E_AQ_CAP_ID_TXQ:
			p->num_tx_qp = number;
			p->base_queue = phys_id;
			अवरोध;
		हाल I40E_AQ_CAP_ID_MSIX:
			p->num_msix_vectors = number;
			i40e_debug(hw, I40E_DEBUG_INIT,
				   "HW Capability: MSIX vector count = %d\n",
				   p->num_msix_vectors);
			अवरोध;
		हाल I40E_AQ_CAP_ID_VF_MSIX:
			p->num_msix_vectors_vf = number;
			अवरोध;
		हाल I40E_AQ_CAP_ID_FLEX10:
			अगर (major_rev == 1) अणु
				अगर (number == 1) अणु
					p->flex10_enable = true;
					p->flex10_capable = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Capability revision >= 2 */
				अगर (number & 1)
					p->flex10_enable = true;
				अगर (number & 2)
					p->flex10_capable = true;
			पूर्ण
			p->flex10_mode = logical_id;
			p->flex10_status = phys_id;
			अवरोध;
		हाल I40E_AQ_CAP_ID_CEM:
			अगर (number == 1)
				p->mgmt_cem = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_IWARP:
			अगर (number == 1)
				p->iwarp = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_LED:
			अगर (phys_id < I40E_HW_CAP_MAX_GPIO)
				p->led[phys_id] = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_SDP:
			अगर (phys_id < I40E_HW_CAP_MAX_GPIO)
				p->sdp[phys_id] = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_MDIO:
			अगर (number == 1) अणु
				p->mdio_port_num = phys_id;
				p->mdio_port_mode = logical_id;
			पूर्ण
			अवरोध;
		हाल I40E_AQ_CAP_ID_1588:
			अगर (number == 1)
				p->ieee_1588 = true;
			अवरोध;
		हाल I40E_AQ_CAP_ID_FLOW_सूचीECTOR:
			p->fd = true;
			p->fd_filters_guaranteed = number;
			p->fd_filters_best_efक्रमt = logical_id;
			अवरोध;
		हाल I40E_AQ_CAP_ID_WSR_PROT:
			p->wr_csr_prot = (u64)number;
			p->wr_csr_prot |= (u64)logical_id << 32;
			अवरोध;
		हाल I40E_AQ_CAP_ID_NVM_MGMT:
			अगर (number & I40E_NVM_MGMT_SEC_REV_DISABLED)
				p->sec_rev_disabled = true;
			अगर (number & I40E_NVM_MGMT_UPDATE_DISABLED)
				p->update_disabled = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (p->fcoe)
		i40e_debug(hw, I40E_DEBUG_ALL, "device is FCoE capable\n");

	/* Software override ensuring FCoE is disabled अगर npar or mfp
	 * mode because it is not supported in these modes.
	 */
	अगर (p->npar_enable || p->flex10_enable)
		p->fcoe = false;

	/* count the enabled ports (aka the "not disabled" ports) */
	hw->num_ports = 0;
	क्रम (i = 0; i < 4; i++) अणु
		u32 port_cfg_reg = I40E_PRTGEN_CNF + (4 * i);
		u64 port_cfg = 0;

		/* use AQ पढ़ो to get the physical रेजिस्टर offset instead
		 * of the port relative offset
		 */
		i40e_aq_debug_पढ़ो_रेजिस्टर(hw, port_cfg_reg, &port_cfg, शून्य);
		अगर (!(port_cfg & I40E_PRTGEN_CNF_PORT_DIS_MASK))
			hw->num_ports++;
	पूर्ण

	/* OCP cards हाल: अगर a mezz is हटाओd the Ethernet port is at
	 * disabled state in PRTGEN_CNF रेजिस्टर. Additional NVM पढ़ो is
	 * needed in order to check अगर we are dealing with OCP card.
	 * Those cards have 4 PFs at minimum, so using PRTGEN_CNF क्रम counting
	 * physical ports results in wrong partition id calculation and thus
	 * not supporting WoL.
	 */
	अगर (hw->mac.type == I40E_MAC_X722) अणु
		अगर (!i40e_acquire_nvm(hw, I40E_RESOURCE_READ)) अणु
			status = i40e_aq_पढ़ो_nvm(hw, I40E_SR_EMP_MODULE_PTR,
						  2 * I40E_SR_OCP_CFG_WORD0,
						  माप(ocp_cfg_word0),
						  &ocp_cfg_word0, true, शून्य);
			अगर (!status &&
			    (ocp_cfg_word0 & I40E_SR_OCP_ENABLED))
				hw->num_ports = 4;
			i40e_release_nvm(hw);
		पूर्ण
	पूर्ण

	valid_functions = p->valid_functions;
	num_functions = 0;
	जबतक (valid_functions) अणु
		अगर (valid_functions & 1)
			num_functions++;
		valid_functions >>= 1;
	पूर्ण

	/* partition id is 1-based, and functions are evenly spपढ़ो
	 * across the ports as partitions
	 */
	अगर (hw->num_ports != 0) अणु
		hw->partition_id = (hw->pf_id / hw->num_ports) + 1;
		hw->num_partitions = num_functions / hw->num_ports;
	पूर्ण

	/* additional HW specअगरic goodies that might
	 * someday be HW version specअगरic
	 */
	p->rx_buf_chain_len = I40E_MAX_CHAINED_RX_BUFFERS;
पूर्ण

/**
 * i40e_aq_discover_capabilities
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @buff: a भव buffer to hold the capabilities
 * @buff_size: Size of the भव buffer
 * @data_size: Size of the वापसed data, or buff size needed अगर AQ err==ENOMEM
 * @list_type_opc: capabilities type to discover - pass in the command opcode
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get the device capabilities descriptions from the firmware
 **/
i40e_status i40e_aq_discover_capabilities(काष्ठा i40e_hw *hw,
				व्योम *buff, u16 buff_size, u16 *data_size,
				क्रमागत i40e_admin_queue_opc list_type_opc,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aqc_list_capabilites *cmd;
	काष्ठा i40e_aq_desc desc;
	i40e_status status = 0;

	cmd = (काष्ठा i40e_aqc_list_capabilites *)&desc.params.raw;

	अगर (list_type_opc != i40e_aqc_opc_list_func_capabilities &&
		list_type_opc != i40e_aqc_opc_list_dev_capabilities) अणु
		status = I40E_ERR_PARAM;
		जाओ निकास;
	पूर्ण

	i40e_fill_शेष_direct_cmd_desc(&desc, list_type_opc);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);
	*data_size = le16_to_cpu(desc.datalen);

	अगर (status)
		जाओ निकास;

	i40e_parse_discover_capabilities(hw, buff, le32_to_cpu(cmd->count),
					 list_type_opc);

निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_update_nvm
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @module_poपूर्णांकer: module poपूर्णांकer location in words from the NVM beginning
 * @offset: byte offset from the module beginning
 * @length: length of the section to be written (in bytes from the offset)
 * @data: command buffer (size [bytes] = length)
 * @last_command: tells अगर this is the last command in a series
 * @preservation_flags: Preservation mode flags
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Update the NVM using the admin queue commands
 **/
i40e_status i40e_aq_update_nvm(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
			       u32 offset, u16 length, व्योम *data,
				bool last_command, u8 preservation_flags,
			       काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_nvm_update *cmd =
		(काष्ठा i40e_aqc_nvm_update *)&desc.params.raw;
	i40e_status status;

	/* In offset the highest byte must be zeroed. */
	अगर (offset & 0xFF000000) अणु
		status = I40E_ERR_PARAM;
		जाओ i40e_aq_update_nvm_निकास;
	पूर्ण

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_nvm_update);

	/* If this is the last command in a series, set the proper flag. */
	अगर (last_command)
		cmd->command_flags |= I40E_AQ_NVM_LAST_CMD;
	अगर (hw->mac.type == I40E_MAC_X722) अणु
		अगर (preservation_flags == I40E_NVM_PRESERVATION_FLAGS_SELECTED)
			cmd->command_flags |=
				(I40E_AQ_NVM_PRESERVATION_FLAGS_SELECTED <<
				 I40E_AQ_NVM_PRESERVATION_FLAGS_SHIFT);
		अन्यथा अगर (preservation_flags == I40E_NVM_PRESERVATION_FLAGS_ALL)
			cmd->command_flags |=
				(I40E_AQ_NVM_PRESERVATION_FLAGS_ALL <<
				 I40E_AQ_NVM_PRESERVATION_FLAGS_SHIFT);
	पूर्ण
	cmd->module_poपूर्णांकer = module_poपूर्णांकer;
	cmd->offset = cpu_to_le32(offset);
	cmd->length = cpu_to_le16(length);

	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	अगर (length > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, data, length, cmd_details);

i40e_aq_update_nvm_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_rearrange_nvm
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @rearrange_nvm: defines direction of rearrangement
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Rearrange NVM काष्ठाure, available only क्रम transition FW
 **/
i40e_status i40e_aq_rearrange_nvm(काष्ठा i40e_hw *hw,
				  u8 rearrange_nvm,
				  काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aqc_nvm_update *cmd;
	i40e_status status;
	काष्ठा i40e_aq_desc desc;

	cmd = (काष्ठा i40e_aqc_nvm_update *)&desc.params.raw;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_nvm_update);

	rearrange_nvm &= (I40E_AQ_NVM_REARRANGE_TO_FLAT |
			 I40E_AQ_NVM_REARRANGE_TO_STRUCT);

	अगर (!rearrange_nvm) अणु
		status = I40E_ERR_PARAM;
		जाओ i40e_aq_rearrange_nvm_निकास;
	पूर्ण

	cmd->command_flags |= rearrange_nvm;
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

i40e_aq_rearrange_nvm_निकास:
	वापस status;
पूर्ण

/**
 * i40e_aq_get_lldp_mib
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @bridge_type: type of bridge requested
 * @mib_type: Local, Remote or both Local and Remote MIBs
 * @buff: poपूर्णांकer to a user supplied buffer to store the MIB block
 * @buff_size: size of the buffer (in bytes)
 * @local_len : length of the वापसed Local LLDP MIB
 * @remote_len: length of the वापसed Remote LLDP MIB
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Requests the complete LLDP MIB (entire packet).
 **/
i40e_status i40e_aq_get_lldp_mib(काष्ठा i40e_hw *hw, u8 bridge_type,
				u8 mib_type, व्योम *buff, u16 buff_size,
				u16 *local_len, u16 *remote_len,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_lldp_get_mib *cmd =
		(काष्ठा i40e_aqc_lldp_get_mib *)&desc.params.raw;
	काष्ठा i40e_aqc_lldp_get_mib *resp =
		(काष्ठा i40e_aqc_lldp_get_mib *)&desc.params.raw;
	i40e_status status;

	अगर (buff_size == 0 || !buff)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_lldp_get_mib);
	/* Indirect Command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);

	cmd->type = mib_type & I40E_AQ_LLDP_MIB_TYPE_MASK;
	cmd->type |= ((bridge_type << I40E_AQ_LLDP_BRIDGE_TYPE_SHIFT) &
		       I40E_AQ_LLDP_BRIDGE_TYPE_MASK);

	desc.datalen = cpu_to_le16(buff_size);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);
	अगर (!status) अणु
		अगर (local_len != शून्य)
			*local_len = le16_to_cpu(resp->local_len);
		अगर (remote_len != शून्य)
			*remote_len = le16_to_cpu(resp->remote_len);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_set_lldp_mib - Set the LLDP MIB
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @mib_type: Local, Remote or both Local and Remote MIBs
 * @buff: poपूर्णांकer to a user supplied buffer to store the MIB block
 * @buff_size: size of the buffer (in bytes)
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set the LLDP MIB.
 **/
क्रमागत i40e_status_code
i40e_aq_set_lldp_mib(काष्ठा i40e_hw *hw,
		     u8 mib_type, व्योम *buff, u16 buff_size,
		     काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aqc_lldp_set_local_mib *cmd;
	क्रमागत i40e_status_code status;
	काष्ठा i40e_aq_desc desc;

	cmd = (काष्ठा i40e_aqc_lldp_set_local_mib *)&desc.params.raw;
	अगर (buff_size == 0 || !buff)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_lldp_set_local_mib);
	/* Indirect Command */
	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
	desc.datalen = cpu_to_le16(buff_size);

	cmd->type = mib_type;
	cmd->length = cpu_to_le16(buff_size);
	cmd->address_high = cpu_to_le32(upper_32_bits((uपूर्णांकptr_t)buff));
	cmd->address_low = cpu_to_le32(lower_32_bits((uपूर्णांकptr_t)buff));

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);
	वापस status;
पूर्ण

/**
 * i40e_aq_cfg_lldp_mib_change_event
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @enable_update: Enable or Disable event posting
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Enable or Disable posting of an event on ARQ when LLDP MIB
 * associated with the पूर्णांकerface changes
 **/
i40e_status i40e_aq_cfg_lldp_mib_change_event(काष्ठा i40e_hw *hw,
				bool enable_update,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_lldp_update_mib *cmd =
		(काष्ठा i40e_aqc_lldp_update_mib *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_lldp_update_mib);

	अगर (!enable_update)
		cmd->command |= I40E_AQ_LLDP_MIB_UPDATE_DISABLE;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_restore_lldp
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @setting: poपूर्णांकer to factory setting variable or शून्य
 * @restore: True अगर factory settings should be restored
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Restore LLDP Agent factory settings अगर @restore set to True. In other हाल
 * only वापसs factory setting in AQ response.
 **/
क्रमागत i40e_status_code
i40e_aq_restore_lldp(काष्ठा i40e_hw *hw, u8 *setting, bool restore,
		     काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_lldp_restore *cmd =
		(काष्ठा i40e_aqc_lldp_restore *)&desc.params.raw;
	i40e_status status;

	अगर (!(hw->flags & I40E_HW_FLAG_FW_LLDP_PERSISTENT)) अणु
		i40e_debug(hw, I40E_DEBUG_ALL,
			   "Restore LLDP not supported by current FW version.\n");
		वापस I40E_ERR_DEVICE_NOT_SUPPORTED;
	पूर्ण

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_lldp_restore);

	अगर (restore)
		cmd->command |= I40E_AQ_LLDP_AGENT_RESTORE;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (setting)
		*setting = cmd->command & 1;

	वापस status;
पूर्ण

/**
 * i40e_aq_stop_lldp
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @shutकरोwn_agent: True अगर LLDP Agent needs to be Shutकरोwn
 * @persist: True अगर stop of LLDP should be persistent across घातer cycles
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Stop or Shutकरोwn the embedded LLDP Agent
 **/
i40e_status i40e_aq_stop_lldp(काष्ठा i40e_hw *hw, bool shutकरोwn_agent,
				bool persist,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_lldp_stop *cmd =
		(काष्ठा i40e_aqc_lldp_stop *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_lldp_stop);

	अगर (shutकरोwn_agent)
		cmd->command |= I40E_AQ_LLDP_AGENT_SHUTDOWN;

	अगर (persist) अणु
		अगर (hw->flags & I40E_HW_FLAG_FW_LLDP_PERSISTENT)
			cmd->command |= I40E_AQ_LLDP_AGENT_STOP_PERSIST;
		अन्यथा
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Persistent Stop LLDP not supported by current FW version.\n");
	पूर्ण

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_start_lldp
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @persist: True अगर start of LLDP should be persistent across घातer cycles
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Start the embedded LLDP Agent on all ports.
 **/
i40e_status i40e_aq_start_lldp(काष्ठा i40e_hw *hw, bool persist,
			       काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_lldp_start *cmd =
		(काष्ठा i40e_aqc_lldp_start *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_lldp_start);

	cmd->command = I40E_AQ_LLDP_AGENT_START;

	अगर (persist) अणु
		अगर (hw->flags & I40E_HW_FLAG_FW_LLDP_PERSISTENT)
			cmd->command |= I40E_AQ_LLDP_AGENT_START_PERSIST;
		अन्यथा
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Persistent Start LLDP not supported by current FW version.\n");
	पूर्ण

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_set_dcb_parameters
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 * @dcb_enable: True अगर DCB configuration needs to be applied
 *
 **/
क्रमागत i40e_status_code
i40e_aq_set_dcb_parameters(काष्ठा i40e_hw *hw, bool dcb_enable,
			   काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_set_dcb_parameters *cmd =
		(काष्ठा i40e_aqc_set_dcb_parameters *)&desc.params.raw;
	i40e_status status;

	अगर (!(hw->flags & I40E_HW_FLAG_FW_LLDP_STOPPABLE))
		वापस I40E_ERR_DEVICE_NOT_SUPPORTED;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_dcb_parameters);

	अगर (dcb_enable) अणु
		cmd->valid_flags = I40E_DCB_VALID;
		cmd->command = I40E_AQ_DCB_SET_AGENT;
	पूर्ण
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_cee_dcb_config
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @buff: response buffer that stores CEE operational configuration
 * @buff_size: size of the buffer passed
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get CEE DCBX mode operational configuration from firmware
 **/
i40e_status i40e_aq_get_cee_dcb_config(काष्ठा i40e_hw *hw,
				       व्योम *buff, u16 buff_size,
				       काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	i40e_status status;

	अगर (buff_size == 0 || !buff)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_get_cee_dcb_cfg);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	status = i40e_asq_send_command(hw, &desc, (व्योम *)buff, buff_size,
				       cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_add_udp_tunnel
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @udp_port: the UDP port to add in Host byte order
 * @protocol_index: protocol index type
 * @filter_index: poपूर्णांकer to filter index
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Note: Firmware expects the udp_port value to be in Little Endian क्रमmat,
 * and this function will call cpu_to_le16 to convert from Host byte order to
 * Little Endian order.
 **/
i40e_status i40e_aq_add_udp_tunnel(काष्ठा i40e_hw *hw,
				u16 udp_port, u8 protocol_index,
				u8 *filter_index,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_udp_tunnel *cmd =
		(काष्ठा i40e_aqc_add_udp_tunnel *)&desc.params.raw;
	काष्ठा i40e_aqc_del_udp_tunnel_completion *resp =
		(काष्ठा i40e_aqc_del_udp_tunnel_completion *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_add_udp_tunnel);

	cmd->udp_port = cpu_to_le16(udp_port);
	cmd->protocol_type = protocol_index;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (!status && filter_index)
		*filter_index = resp->index;

	वापस status;
पूर्ण

/**
 * i40e_aq_del_udp_tunnel
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @index: filter index
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_del_udp_tunnel(काष्ठा i40e_hw *hw, u8 index,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_हटाओ_udp_tunnel *cmd =
		(काष्ठा i40e_aqc_हटाओ_udp_tunnel *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_del_udp_tunnel);

	cmd->index = index;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_delete_element - Delete चयन element
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: the SEID to delete from the चयन
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This deletes a चयन element from the चयन.
 **/
i40e_status i40e_aq_delete_element(काष्ठा i40e_hw *hw, u16 seid,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_चयन_seid *cmd =
		(काष्ठा i40e_aqc_चयन_seid *)&desc.params.raw;
	i40e_status status;

	अगर (seid == 0)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_delete_element);

	cmd->seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_dcb_updated - DCB Updated Command
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * EMP will वापस when the shared RPB settings have been
 * recomputed and modअगरied. The retval field in the descriptor
 * will be set to 0 when RPB is modअगरied.
 **/
i40e_status i40e_aq_dcb_updated(काष्ठा i40e_hw *hw,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_dcb_updated);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_tx_sched_cmd - generic Tx scheduler AQ command handler
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid क्रम the physical port/चयनing component/vsi
 * @buff: Indirect buffer to hold data parameters and response
 * @buff_size: Indirect buffer size
 * @opcode: Tx scheduler AQ command opcode
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Generic command handler क्रम Tx scheduler AQ commands
 **/
अटल i40e_status i40e_aq_tx_sched_cmd(काष्ठा i40e_hw *hw, u16 seid,
				व्योम *buff, u16 buff_size,
				 क्रमागत i40e_admin_queue_opc opcode,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_tx_sched_ind *cmd =
		(काष्ठा i40e_aqc_tx_sched_ind *)&desc.params.raw;
	i40e_status status;
	bool cmd_param_flag = false;

	चयन (opcode) अणु
	हाल i40e_aqc_opc_configure_vsi_ets_sla_bw_limit:
	हाल i40e_aqc_opc_configure_vsi_tc_bw:
	हाल i40e_aqc_opc_enable_चयनing_comp_ets:
	हाल i40e_aqc_opc_modअगरy_चयनing_comp_ets:
	हाल i40e_aqc_opc_disable_चयनing_comp_ets:
	हाल i40e_aqc_opc_configure_चयनing_comp_ets_bw_limit:
	हाल i40e_aqc_opc_configure_चयनing_comp_bw_config:
		cmd_param_flag = true;
		अवरोध;
	हाल i40e_aqc_opc_query_vsi_bw_config:
	हाल i40e_aqc_opc_query_vsi_ets_sla_config:
	हाल i40e_aqc_opc_query_चयनing_comp_ets_config:
	हाल i40e_aqc_opc_query_port_ets_config:
	हाल i40e_aqc_opc_query_चयनing_comp_bw_config:
		cmd_param_flag = false;
		अवरोध;
	शेष:
		वापस I40E_ERR_PARAM;
	पूर्ण

	i40e_fill_शेष_direct_cmd_desc(&desc, opcode);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (cmd_param_flag)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_RD);
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	desc.datalen = cpu_to_le16(buff_size);

	cmd->vsi_seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_config_vsi_bw_limit - Configure VSI BW Limit
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: VSI seid
 * @credit: BW limit credits (0 = disabled)
 * @max_credit: Max BW limit credits
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_config_vsi_bw_limit(काष्ठा i40e_hw *hw,
				u16 seid, u16 credit, u8 max_credit,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_configure_vsi_bw_limit *cmd =
		(काष्ठा i40e_aqc_configure_vsi_bw_limit *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_configure_vsi_bw_limit);

	cmd->vsi_seid = cpu_to_le16(seid);
	cmd->credit = cpu_to_le16(credit);
	cmd->max_credit = max_credit;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_config_vsi_tc_bw - Config VSI BW Allocation per TC
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: VSI seid
 * @bw_data: Buffer holding enabled TCs, relative TC BW limit/credits
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_config_vsi_tc_bw(काष्ठा i40e_hw *hw,
			u16 seid,
			काष्ठा i40e_aqc_configure_vsi_tc_bw_data *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
				    i40e_aqc_opc_configure_vsi_tc_bw,
				    cmd_details);
पूर्ण

/**
 * i40e_aq_config_चयन_comp_ets - Enable/Disable/Modअगरy ETS on the port
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the चयनing component connected to Physical Port
 * @ets_data: Buffer holding ETS parameters
 * @opcode: Tx scheduler AQ command opcode
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_config_चयन_comp_ets(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_configure_चयनing_comp_ets_data *ets_data,
		क्रमागत i40e_admin_queue_opc opcode,
		काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)ets_data,
				    माप(*ets_data), opcode, cmd_details);
पूर्ण

/**
 * i40e_aq_config_चयन_comp_bw_config - Config Switch comp BW Alloc per TC
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the चयनing component
 * @bw_data: Buffer holding enabled TCs, relative/असलolute TC BW limit/credits
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_config_चयन_comp_bw_config(काष्ठा i40e_hw *hw,
	u16 seid,
	काष्ठा i40e_aqc_configure_चयनing_comp_bw_config_data *bw_data,
	काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
			    i40e_aqc_opc_configure_चयनing_comp_bw_config,
			    cmd_details);
पूर्ण

/**
 * i40e_aq_query_vsi_bw_config - Query VSI BW configuration
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the VSI
 * @bw_data: Buffer to hold VSI BW configuration
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_query_vsi_bw_config(काष्ठा i40e_hw *hw,
			u16 seid,
			काष्ठा i40e_aqc_query_vsi_bw_config_resp *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
				    i40e_aqc_opc_query_vsi_bw_config,
				    cmd_details);
पूर्ण

/**
 * i40e_aq_query_vsi_ets_sla_config - Query VSI BW configuration per TC
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the VSI
 * @bw_data: Buffer to hold VSI BW configuration per TC
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_query_vsi_ets_sla_config(काष्ठा i40e_hw *hw,
			u16 seid,
			काष्ठा i40e_aqc_query_vsi_ets_sla_config_resp *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
				    i40e_aqc_opc_query_vsi_ets_sla_config,
				    cmd_details);
पूर्ण

/**
 * i40e_aq_query_चयन_comp_ets_config - Query Switch comp BW config per TC
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the चयनing component
 * @bw_data: Buffer to hold चयनing component's per TC BW config
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_query_चयन_comp_ets_config(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_query_चयनing_comp_ets_config_resp *bw_data,
		काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
				   i40e_aqc_opc_query_चयनing_comp_ets_config,
				   cmd_details);
पूर्ण

/**
 * i40e_aq_query_port_ets_config - Query Physical Port ETS configuration
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the VSI or चयनing component connected to Physical Port
 * @bw_data: Buffer to hold current ETS configuration क्रम the Physical Port
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_query_port_ets_config(काष्ठा i40e_hw *hw,
			u16 seid,
			काष्ठा i40e_aqc_query_port_ets_config_resp *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
				    i40e_aqc_opc_query_port_ets_config,
				    cmd_details);
पूर्ण

/**
 * i40e_aq_query_चयन_comp_bw_config - Query Switch comp BW configuration
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: seid of the चयनing component
 * @bw_data: Buffer to hold चयनing component's BW configuration
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
i40e_status i40e_aq_query_चयन_comp_bw_config(काष्ठा i40e_hw *hw,
		u16 seid,
		काष्ठा i40e_aqc_query_चयनing_comp_bw_config_resp *bw_data,
		काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	वापस i40e_aq_tx_sched_cmd(hw, seid, (व्योम *)bw_data, माप(*bw_data),
				    i40e_aqc_opc_query_चयनing_comp_bw_config,
				    cmd_details);
पूर्ण

/**
 * i40e_validate_filter_settings
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @settings: Filter control settings
 *
 * Check and validate the filter control settings passed.
 * The function checks क्रम the valid filter/context sizes being
 * passed क्रम FCoE and PE.
 *
 * Returns 0 अगर the values passed are valid and within
 * range अन्यथा वापसs an error.
 **/
अटल i40e_status i40e_validate_filter_settings(काष्ठा i40e_hw *hw,
				काष्ठा i40e_filter_control_settings *settings)
अणु
	u32 fcoe_cntx_size, fcoe_filt_size;
	u32 pe_cntx_size, pe_filt_size;
	u32 fcoe_fmax;
	u32 val;

	/* Validate FCoE settings passed */
	चयन (settings->fcoe_filt_num) अणु
	हाल I40E_HASH_FILTER_SIZE_1K:
	हाल I40E_HASH_FILTER_SIZE_2K:
	हाल I40E_HASH_FILTER_SIZE_4K:
	हाल I40E_HASH_FILTER_SIZE_8K:
	हाल I40E_HASH_FILTER_SIZE_16K:
	हाल I40E_HASH_FILTER_SIZE_32K:
		fcoe_filt_size = I40E_HASH_FILTER_BASE_SIZE;
		fcoe_filt_size <<= (u32)settings->fcoe_filt_num;
		अवरोध;
	शेष:
		वापस I40E_ERR_PARAM;
	पूर्ण

	चयन (settings->fcoe_cntx_num) अणु
	हाल I40E_DMA_CNTX_SIZE_512:
	हाल I40E_DMA_CNTX_SIZE_1K:
	हाल I40E_DMA_CNTX_SIZE_2K:
	हाल I40E_DMA_CNTX_SIZE_4K:
		fcoe_cntx_size = I40E_DMA_CNTX_BASE_SIZE;
		fcoe_cntx_size <<= (u32)settings->fcoe_cntx_num;
		अवरोध;
	शेष:
		वापस I40E_ERR_PARAM;
	पूर्ण

	/* Validate PE settings passed */
	चयन (settings->pe_filt_num) अणु
	हाल I40E_HASH_FILTER_SIZE_1K:
	हाल I40E_HASH_FILTER_SIZE_2K:
	हाल I40E_HASH_FILTER_SIZE_4K:
	हाल I40E_HASH_FILTER_SIZE_8K:
	हाल I40E_HASH_FILTER_SIZE_16K:
	हाल I40E_HASH_FILTER_SIZE_32K:
	हाल I40E_HASH_FILTER_SIZE_64K:
	हाल I40E_HASH_FILTER_SIZE_128K:
	हाल I40E_HASH_FILTER_SIZE_256K:
	हाल I40E_HASH_FILTER_SIZE_512K:
	हाल I40E_HASH_FILTER_SIZE_1M:
		pe_filt_size = I40E_HASH_FILTER_BASE_SIZE;
		pe_filt_size <<= (u32)settings->pe_filt_num;
		अवरोध;
	शेष:
		वापस I40E_ERR_PARAM;
	पूर्ण

	चयन (settings->pe_cntx_num) अणु
	हाल I40E_DMA_CNTX_SIZE_512:
	हाल I40E_DMA_CNTX_SIZE_1K:
	हाल I40E_DMA_CNTX_SIZE_2K:
	हाल I40E_DMA_CNTX_SIZE_4K:
	हाल I40E_DMA_CNTX_SIZE_8K:
	हाल I40E_DMA_CNTX_SIZE_16K:
	हाल I40E_DMA_CNTX_SIZE_32K:
	हाल I40E_DMA_CNTX_SIZE_64K:
	हाल I40E_DMA_CNTX_SIZE_128K:
	हाल I40E_DMA_CNTX_SIZE_256K:
		pe_cntx_size = I40E_DMA_CNTX_BASE_SIZE;
		pe_cntx_size <<= (u32)settings->pe_cntx_num;
		अवरोध;
	शेष:
		वापस I40E_ERR_PARAM;
	पूर्ण

	/* FCHSIZE + FCDSIZE should not be greater than PMFCOEFMAX */
	val = rd32(hw, I40E_GLHMC_FCOEFMAX);
	fcoe_fmax = (val & I40E_GLHMC_FCOEFMAX_PMFCOEFMAX_MASK)
		     >> I40E_GLHMC_FCOEFMAX_PMFCOEFMAX_SHIFT;
	अगर (fcoe_filt_size + fcoe_cntx_size >  fcoe_fmax)
		वापस I40E_ERR_INVALID_SIZE;

	वापस 0;
पूर्ण

/**
 * i40e_set_filter_control
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @settings: Filter control settings
 *
 * Set the Queue Filters क्रम PE/FCoE and enable filters required
 * क्रम a single PF. It is expected that these settings are programmed
 * at the driver initialization समय.
 **/
i40e_status i40e_set_filter_control(काष्ठा i40e_hw *hw,
				काष्ठा i40e_filter_control_settings *settings)
अणु
	i40e_status ret = 0;
	u32 hash_lut_size = 0;
	u32 val;

	अगर (!settings)
		वापस I40E_ERR_PARAM;

	/* Validate the input settings */
	ret = i40e_validate_filter_settings(hw, settings);
	अगर (ret)
		वापस ret;

	/* Read the PF Queue Filter control रेजिस्टर */
	val = i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_CTL_0);

	/* Program required PE hash buckets क्रम the PF */
	val &= ~I40E_PFQF_CTL_0_PEHSIZE_MASK;
	val |= ((u32)settings->pe_filt_num << I40E_PFQF_CTL_0_PEHSIZE_SHIFT) &
		I40E_PFQF_CTL_0_PEHSIZE_MASK;
	/* Program required PE contexts क्रम the PF */
	val &= ~I40E_PFQF_CTL_0_PEDSIZE_MASK;
	val |= ((u32)settings->pe_cntx_num << I40E_PFQF_CTL_0_PEDSIZE_SHIFT) &
		I40E_PFQF_CTL_0_PEDSIZE_MASK;

	/* Program required FCoE hash buckets क्रम the PF */
	val &= ~I40E_PFQF_CTL_0_PFFCHSIZE_MASK;
	val |= ((u32)settings->fcoe_filt_num <<
			I40E_PFQF_CTL_0_PFFCHSIZE_SHIFT) &
		I40E_PFQF_CTL_0_PFFCHSIZE_MASK;
	/* Program required FCoE DDP contexts क्रम the PF */
	val &= ~I40E_PFQF_CTL_0_PFFCDSIZE_MASK;
	val |= ((u32)settings->fcoe_cntx_num <<
			I40E_PFQF_CTL_0_PFFCDSIZE_SHIFT) &
		I40E_PFQF_CTL_0_PFFCDSIZE_MASK;

	/* Program Hash LUT size क्रम the PF */
	val &= ~I40E_PFQF_CTL_0_HASHLUTSIZE_MASK;
	अगर (settings->hash_lut_size == I40E_HASH_LUT_SIZE_512)
		hash_lut_size = 1;
	val |= (hash_lut_size << I40E_PFQF_CTL_0_HASHLUTSIZE_SHIFT) &
		I40E_PFQF_CTL_0_HASHLUTSIZE_MASK;

	/* Enable Fसूची, Ethertype and MACVLAN filters क्रम PF and VFs */
	अगर (settings->enable_fdir)
		val |= I40E_PFQF_CTL_0_FD_ENA_MASK;
	अगर (settings->enable_ethtype)
		val |= I40E_PFQF_CTL_0_ETYPE_ENA_MASK;
	अगर (settings->enable_macvlan)
		val |= I40E_PFQF_CTL_0_MACVLAN_ENA_MASK;

	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_CTL_0, val);

	वापस 0;
पूर्ण

/**
 * i40e_aq_add_rem_control_packet_filter - Add or Remove Control Packet Filter
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @mac_addr: MAC address to use in the filter
 * @ethtype: Ethertype to use in the filter
 * @flags: Flags that needs to be applied to the filter
 * @vsi_seid: seid of the control VSI
 * @queue: VSI queue number to send the packet to
 * @is_add: Add control packet filter अगर True अन्यथा हटाओ
 * @stats: Structure to hold inक्रमmation on control filter counts
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This command will Add or Remove control packet filter क्रम a control VSI.
 * In वापस it will update the total number of perfect filter count in
 * the stats member.
 **/
i40e_status i40e_aq_add_rem_control_packet_filter(काष्ठा i40e_hw *hw,
				u8 *mac_addr, u16 ethtype, u16 flags,
				u16 vsi_seid, u16 queue, bool is_add,
				काष्ठा i40e_control_filter_stats *stats,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_हटाओ_control_packet_filter *cmd =
		(काष्ठा i40e_aqc_add_हटाओ_control_packet_filter *)
		&desc.params.raw;
	काष्ठा i40e_aqc_add_हटाओ_control_packet_filter_completion *resp =
		(काष्ठा i40e_aqc_add_हटाओ_control_packet_filter_completion *)
		&desc.params.raw;
	i40e_status status;

	अगर (vsi_seid == 0)
		वापस I40E_ERR_PARAM;

	अगर (is_add) अणु
		i40e_fill_शेष_direct_cmd_desc(&desc,
				i40e_aqc_opc_add_control_packet_filter);
		cmd->queue = cpu_to_le16(queue);
	पूर्ण अन्यथा अणु
		i40e_fill_शेष_direct_cmd_desc(&desc,
				i40e_aqc_opc_हटाओ_control_packet_filter);
	पूर्ण

	अगर (mac_addr)
		ether_addr_copy(cmd->mac, mac_addr);

	cmd->etype = cpu_to_le16(ethtype);
	cmd->flags = cpu_to_le16(flags);
	cmd->seid = cpu_to_le16(vsi_seid);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (!status && stats) अणु
		stats->mac_etype_used = le16_to_cpu(resp->mac_etype_used);
		stats->etype_used = le16_to_cpu(resp->etype_used);
		stats->mac_etype_मुक्त = le16_to_cpu(resp->mac_etype_मुक्त);
		stats->etype_मुक्त = le16_to_cpu(resp->etype_मुक्त);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_add_filter_to_drop_tx_flow_control_frames- filter to drop flow control
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @seid: VSI seid to add ethertype filter from
 **/
व्योम i40e_add_filter_to_drop_tx_flow_control_frames(काष्ठा i40e_hw *hw,
						    u16 seid)
अणु
#घोषणा I40E_FLOW_CONTROL_ETHTYPE 0x8808
	u16 flag = I40E_AQC_ADD_CONTROL_PACKET_FLAGS_IGNORE_MAC |
		   I40E_AQC_ADD_CONTROL_PACKET_FLAGS_DROP |
		   I40E_AQC_ADD_CONTROL_PACKET_FLAGS_TX;
	u16 ethtype = I40E_FLOW_CONTROL_ETHTYPE;
	i40e_status status;

	status = i40e_aq_add_rem_control_packet_filter(hw, शून्य, ethtype, flag,
						       seid, 0, true, शून्य,
						       शून्य);
	अगर (status)
		hw_dbg(hw, "Ethtype Filter Add failed: Error pruning Tx flow control frames\n");
पूर्ण

/**
 * i40e_aq_alternate_पढ़ो
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @reg_addr0: address of first dword to be पढ़ो
 * @reg_val0: poपूर्णांकer क्रम data पढ़ो from 'reg_addr0'
 * @reg_addr1: address of second dword to be पढ़ो
 * @reg_val1: poपूर्णांकer क्रम data पढ़ो from 'reg_addr1'
 *
 * Read one or two dwords from alternate काष्ठाure. Fields are indicated
 * by 'reg_addr0' and 'reg_addr1' register numbers. If 'reg_val1' poपूर्णांकer
 * is not passed then only रेजिस्टर at 'reg_addr0' is पढ़ो.
 *
 **/
अटल i40e_status i40e_aq_alternate_पढ़ो(काष्ठा i40e_hw *hw,
					  u32 reg_addr0, u32 *reg_val0,
					  u32 reg_addr1, u32 *reg_val1)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_alternate_ग_लिखो *cmd_resp =
		(काष्ठा i40e_aqc_alternate_ग_लिखो *)&desc.params.raw;
	i40e_status status;

	अगर (!reg_val0)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_alternate_पढ़ो);
	cmd_resp->address0 = cpu_to_le32(reg_addr0);
	cmd_resp->address1 = cpu_to_le32(reg_addr1);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, शून्य);

	अगर (!status) अणु
		*reg_val0 = le32_to_cpu(cmd_resp->data0);

		अगर (reg_val1)
			*reg_val1 = le32_to_cpu(cmd_resp->data1);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_suspend_port_tx
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @seid: port seid
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Suspend port's Tx traffic
 **/
i40e_status i40e_aq_suspend_port_tx(काष्ठा i40e_hw *hw, u16 seid,
				    काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aqc_tx_sched_ind *cmd;
	काष्ठा i40e_aq_desc desc;
	i40e_status status;

	cmd = (काष्ठा i40e_aqc_tx_sched_ind *)&desc.params.raw;
	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_suspend_port_tx);
	cmd->vsi_seid = cpu_to_le16(seid);
	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_resume_port_tx
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Resume port's Tx traffic
 **/
i40e_status i40e_aq_resume_port_tx(काष्ठा i40e_hw *hw,
				   काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_resume_port_tx);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_set_pci_config_data - store PCI bus info
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @link_status: the link status word from PCI config space
 *
 * Stores the PCI bus info (speed, width, type) within the i40e_hw काष्ठाure
 **/
व्योम i40e_set_pci_config_data(काष्ठा i40e_hw *hw, u16 link_status)
अणु
	hw->bus.type = i40e_bus_type_pci_express;

	चयन (link_status & PCI_EXP_LNKSTA_NLW) अणु
	हाल PCI_EXP_LNKSTA_NLW_X1:
		hw->bus.width = i40e_bus_width_pcie_x1;
		अवरोध;
	हाल PCI_EXP_LNKSTA_NLW_X2:
		hw->bus.width = i40e_bus_width_pcie_x2;
		अवरोध;
	हाल PCI_EXP_LNKSTA_NLW_X4:
		hw->bus.width = i40e_bus_width_pcie_x4;
		अवरोध;
	हाल PCI_EXP_LNKSTA_NLW_X8:
		hw->bus.width = i40e_bus_width_pcie_x8;
		अवरोध;
	शेष:
		hw->bus.width = i40e_bus_width_unknown;
		अवरोध;
	पूर्ण

	चयन (link_status & PCI_EXP_LNKSTA_CLS) अणु
	हाल PCI_EXP_LNKSTA_CLS_2_5GB:
		hw->bus.speed = i40e_bus_speed_2500;
		अवरोध;
	हाल PCI_EXP_LNKSTA_CLS_5_0GB:
		hw->bus.speed = i40e_bus_speed_5000;
		अवरोध;
	हाल PCI_EXP_LNKSTA_CLS_8_0GB:
		hw->bus.speed = i40e_bus_speed_8000;
		अवरोध;
	शेष:
		hw->bus.speed = i40e_bus_speed_unknown;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_aq_debug_dump
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cluster_id: specअगरic cluster to dump
 * @table_id: table id within cluster
 * @start_index: index of line in the block to पढ़ो
 * @buff_size: dump buffer size
 * @buff: dump buffer
 * @ret_buff_size: actual buffer size वापसed
 * @ret_next_table: next block to पढ़ो
 * @ret_next_index: next index to पढ़ो
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Dump पूर्णांकernal FW/HW data क्रम debug purposes.
 *
 **/
i40e_status i40e_aq_debug_dump(काष्ठा i40e_hw *hw, u8 cluster_id,
			       u8 table_id, u32 start_index, u16 buff_size,
			       व्योम *buff, u16 *ret_buff_size,
			       u8 *ret_next_table, u32 *ret_next_index,
			       काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_debug_dump_पूर्णांकernals *cmd =
		(काष्ठा i40e_aqc_debug_dump_पूर्णांकernals *)&desc.params.raw;
	काष्ठा i40e_aqc_debug_dump_पूर्णांकernals *resp =
		(काष्ठा i40e_aqc_debug_dump_पूर्णांकernals *)&desc.params.raw;
	i40e_status status;

	अगर (buff_size == 0 || !buff)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_debug_dump_पूर्णांकernals);
	/* Indirect Command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	cmd->cluster_id = cluster_id;
	cmd->table_id = table_id;
	cmd->idx = cpu_to_le32(start_index);

	desc.datalen = cpu_to_le16(buff_size);

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);
	अगर (!status) अणु
		अगर (ret_buff_size)
			*ret_buff_size = le16_to_cpu(desc.datalen);
		अगर (ret_next_table)
			*ret_next_table = resp->table_id;
		अगर (ret_next_index)
			*ret_next_index = le32_to_cpu(resp->idx);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_पढ़ो_bw_from_alt_ram
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @max_bw: poपूर्णांकer क्रम max_bw पढ़ो
 * @min_bw: poपूर्णांकer क्रम min_bw पढ़ो
 * @min_valid: poपूर्णांकer क्रम bool that is true अगर min_bw is a valid value
 * @max_valid: poपूर्णांकer क्रम bool that is true अगर max_bw is a valid value
 *
 * Read bw from the alternate ram क्रम the given pf
 **/
i40e_status i40e_पढ़ो_bw_from_alt_ram(काष्ठा i40e_hw *hw,
				      u32 *max_bw, u32 *min_bw,
				      bool *min_valid, bool *max_valid)
अणु
	i40e_status status;
	u32 max_bw_addr, min_bw_addr;

	/* Calculate the address of the min/max bw रेजिस्टरs */
	max_bw_addr = I40E_ALT_STRUCT_FIRST_PF_OFFSET +
		      I40E_ALT_STRUCT_MAX_BW_OFFSET +
		      (I40E_ALT_STRUCT_DWORDS_PER_PF * hw->pf_id);
	min_bw_addr = I40E_ALT_STRUCT_FIRST_PF_OFFSET +
		      I40E_ALT_STRUCT_MIN_BW_OFFSET +
		      (I40E_ALT_STRUCT_DWORDS_PER_PF * hw->pf_id);

	/* Read the bandwidths from alt ram */
	status = i40e_aq_alternate_पढ़ो(hw, max_bw_addr, max_bw,
					min_bw_addr, min_bw);

	अगर (*min_bw & I40E_ALT_BW_VALID_MASK)
		*min_valid = true;
	अन्यथा
		*min_valid = false;

	अगर (*max_bw & I40E_ALT_BW_VALID_MASK)
		*max_valid = true;
	अन्यथा
		*max_valid = false;

	वापस status;
पूर्ण

/**
 * i40e_aq_configure_partition_bw
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @bw_data: Buffer holding valid pfs and bw limits
 * @cmd_details: poपूर्णांकer to command details
 *
 * Configure partitions guaranteed/max bw
 **/
i40e_status i40e_aq_configure_partition_bw(काष्ठा i40e_hw *hw,
			काष्ठा i40e_aqc_configure_partition_bw_data *bw_data,
			काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	i40e_status status;
	काष्ठा i40e_aq_desc desc;
	u16 bwd_size = माप(*bw_data);

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_configure_partition_bw);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_RD);

	अगर (bwd_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	desc.datalen = cpu_to_le16(bwd_size);

	status = i40e_asq_send_command(hw, &desc, bw_data, bwd_size,
				       cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_पढ़ो_phy_रेजिस्टर_clause22
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @reg: रेजिस्टर address in the page
 * @phy_addr: PHY address on MDIO पूर्णांकerface
 * @value: PHY रेजिस्टर value
 *
 * Reads specअगरied PHY रेजिस्टर value
 **/
i40e_status i40e_पढ़ो_phy_रेजिस्टर_clause22(काष्ठा i40e_hw *hw,
					    u16 reg, u8 phy_addr, u16 *value)
अणु
	i40e_status status = I40E_ERR_TIMEOUT;
	u8 port_num = (u8)hw->func_caps.mdio_port_num;
	u32 command = 0;
	u16 retry = 1000;

	command = (reg << I40E_GLGEN_MSCA_DEVADD_SHIFT) |
		  (phy_addr << I40E_GLGEN_MSCA_PHYADD_SHIFT) |
		  (I40E_MDIO_CLAUSE22_OPCODE_READ_MASK) |
		  (I40E_MDIO_CLAUSE22_STCODE_MASK) |
		  (I40E_GLGEN_MSCA_MDICMD_MASK);
	wr32(hw, I40E_GLGEN_MSCA(port_num), command);
	करो अणु
		command = rd32(hw, I40E_GLGEN_MSCA(port_num));
		अगर (!(command & I40E_GLGEN_MSCA_MDICMD_MASK)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		udelay(10);
		retry--;
	पूर्ण जबतक (retry);

	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_PHY,
			   "PHY: Can't write command to external PHY.\n");
	पूर्ण अन्यथा अणु
		command = rd32(hw, I40E_GLGEN_MSRWD(port_num));
		*value = (command & I40E_GLGEN_MSRWD_MसूचीDDATA_MASK) >>
			 I40E_GLGEN_MSRWD_MसूचीDDATA_SHIFT;
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_ग_लिखो_phy_रेजिस्टर_clause22
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @reg: रेजिस्टर address in the page
 * @phy_addr: PHY address on MDIO पूर्णांकerface
 * @value: PHY रेजिस्टर value
 *
 * Writes specअगरied PHY रेजिस्टर value
 **/
i40e_status i40e_ग_लिखो_phy_रेजिस्टर_clause22(काष्ठा i40e_hw *hw,
					     u16 reg, u8 phy_addr, u16 value)
अणु
	i40e_status status = I40E_ERR_TIMEOUT;
	u8 port_num = (u8)hw->func_caps.mdio_port_num;
	u32 command  = 0;
	u16 retry = 1000;

	command = value << I40E_GLGEN_MSRWD_MDIWRDATA_SHIFT;
	wr32(hw, I40E_GLGEN_MSRWD(port_num), command);

	command = (reg << I40E_GLGEN_MSCA_DEVADD_SHIFT) |
		  (phy_addr << I40E_GLGEN_MSCA_PHYADD_SHIFT) |
		  (I40E_MDIO_CLAUSE22_OPCODE_WRITE_MASK) |
		  (I40E_MDIO_CLAUSE22_STCODE_MASK) |
		  (I40E_GLGEN_MSCA_MDICMD_MASK);

	wr32(hw, I40E_GLGEN_MSCA(port_num), command);
	करो अणु
		command = rd32(hw, I40E_GLGEN_MSCA(port_num));
		अगर (!(command & I40E_GLGEN_MSCA_MDICMD_MASK)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		udelay(10);
		retry--;
	पूर्ण जबतक (retry);

	वापस status;
पूर्ण

/**
 * i40e_पढ़ो_phy_रेजिस्टर_clause45
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @page: रेजिस्टरs page number
 * @reg: रेजिस्टर address in the page
 * @phy_addr: PHY address on MDIO पूर्णांकerface
 * @value: PHY रेजिस्टर value
 *
 * Reads specअगरied PHY रेजिस्टर value
 **/
i40e_status i40e_पढ़ो_phy_रेजिस्टर_clause45(काष्ठा i40e_hw *hw,
				u8 page, u16 reg, u8 phy_addr, u16 *value)
अणु
	i40e_status status = I40E_ERR_TIMEOUT;
	u32 command = 0;
	u16 retry = 1000;
	u8 port_num = hw->func_caps.mdio_port_num;

	command = (reg << I40E_GLGEN_MSCA_MDIADD_SHIFT) |
		  (page << I40E_GLGEN_MSCA_DEVADD_SHIFT) |
		  (phy_addr << I40E_GLGEN_MSCA_PHYADD_SHIFT) |
		  (I40E_MDIO_CLAUSE45_OPCODE_ADDRESS_MASK) |
		  (I40E_MDIO_CLAUSE45_STCODE_MASK) |
		  (I40E_GLGEN_MSCA_MDICMD_MASK) |
		  (I40E_GLGEN_MSCA_MDIINPROGEN_MASK);
	wr32(hw, I40E_GLGEN_MSCA(port_num), command);
	करो अणु
		command = rd32(hw, I40E_GLGEN_MSCA(port_num));
		अगर (!(command & I40E_GLGEN_MSCA_MDICMD_MASK)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
		retry--;
	पूर्ण जबतक (retry);

	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_PHY,
			   "PHY: Can't write command to external PHY.\n");
		जाओ phy_पढ़ो_end;
	पूर्ण

	command = (page << I40E_GLGEN_MSCA_DEVADD_SHIFT) |
		  (phy_addr << I40E_GLGEN_MSCA_PHYADD_SHIFT) |
		  (I40E_MDIO_CLAUSE45_OPCODE_READ_MASK) |
		  (I40E_MDIO_CLAUSE45_STCODE_MASK) |
		  (I40E_GLGEN_MSCA_MDICMD_MASK) |
		  (I40E_GLGEN_MSCA_MDIINPROGEN_MASK);
	status = I40E_ERR_TIMEOUT;
	retry = 1000;
	wr32(hw, I40E_GLGEN_MSCA(port_num), command);
	करो अणु
		command = rd32(hw, I40E_GLGEN_MSCA(port_num));
		अगर (!(command & I40E_GLGEN_MSCA_MDICMD_MASK)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
		retry--;
	पूर्ण जबतक (retry);

	अगर (!status) अणु
		command = rd32(hw, I40E_GLGEN_MSRWD(port_num));
		*value = (command & I40E_GLGEN_MSRWD_MसूचीDDATA_MASK) >>
			 I40E_GLGEN_MSRWD_MसूचीDDATA_SHIFT;
	पूर्ण अन्यथा अणु
		i40e_debug(hw, I40E_DEBUG_PHY,
			   "PHY: Can't read register value from external PHY.\n");
	पूर्ण

phy_पढ़ो_end:
	वापस status;
पूर्ण

/**
 * i40e_ग_लिखो_phy_रेजिस्टर_clause45
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @page: रेजिस्टरs page number
 * @reg: रेजिस्टर address in the page
 * @phy_addr: PHY address on MDIO पूर्णांकerface
 * @value: PHY रेजिस्टर value
 *
 * Writes value to specअगरied PHY रेजिस्टर
 **/
i40e_status i40e_ग_लिखो_phy_रेजिस्टर_clause45(काष्ठा i40e_hw *hw,
				u8 page, u16 reg, u8 phy_addr, u16 value)
अणु
	i40e_status status = I40E_ERR_TIMEOUT;
	u32 command = 0;
	u16 retry = 1000;
	u8 port_num = hw->func_caps.mdio_port_num;

	command = (reg << I40E_GLGEN_MSCA_MDIADD_SHIFT) |
		  (page << I40E_GLGEN_MSCA_DEVADD_SHIFT) |
		  (phy_addr << I40E_GLGEN_MSCA_PHYADD_SHIFT) |
		  (I40E_MDIO_CLAUSE45_OPCODE_ADDRESS_MASK) |
		  (I40E_MDIO_CLAUSE45_STCODE_MASK) |
		  (I40E_GLGEN_MSCA_MDICMD_MASK) |
		  (I40E_GLGEN_MSCA_MDIINPROGEN_MASK);
	wr32(hw, I40E_GLGEN_MSCA(port_num), command);
	करो अणु
		command = rd32(hw, I40E_GLGEN_MSCA(port_num));
		अगर (!(command & I40E_GLGEN_MSCA_MDICMD_MASK)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
		retry--;
	पूर्ण जबतक (retry);
	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_PHY,
			   "PHY: Can't write command to external PHY.\n");
		जाओ phy_ग_लिखो_end;
	पूर्ण

	command = value << I40E_GLGEN_MSRWD_MDIWRDATA_SHIFT;
	wr32(hw, I40E_GLGEN_MSRWD(port_num), command);

	command = (page << I40E_GLGEN_MSCA_DEVADD_SHIFT) |
		  (phy_addr << I40E_GLGEN_MSCA_PHYADD_SHIFT) |
		  (I40E_MDIO_CLAUSE45_OPCODE_WRITE_MASK) |
		  (I40E_MDIO_CLAUSE45_STCODE_MASK) |
		  (I40E_GLGEN_MSCA_MDICMD_MASK) |
		  (I40E_GLGEN_MSCA_MDIINPROGEN_MASK);
	status = I40E_ERR_TIMEOUT;
	retry = 1000;
	wr32(hw, I40E_GLGEN_MSCA(port_num), command);
	करो अणु
		command = rd32(hw, I40E_GLGEN_MSCA(port_num));
		अगर (!(command & I40E_GLGEN_MSCA_MDICMD_MASK)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
		retry--;
	पूर्ण जबतक (retry);

phy_ग_लिखो_end:
	वापस status;
पूर्ण

/**
 * i40e_ग_लिखो_phy_रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @page: रेजिस्टरs page number
 * @reg: रेजिस्टर address in the page
 * @phy_addr: PHY address on MDIO पूर्णांकerface
 * @value: PHY रेजिस्टर value
 *
 * Writes value to specअगरied PHY रेजिस्टर
 **/
i40e_status i40e_ग_लिखो_phy_रेजिस्टर(काष्ठा i40e_hw *hw,
				    u8 page, u16 reg, u8 phy_addr, u16 value)
अणु
	i40e_status status;

	चयन (hw->device_id) अणु
	हाल I40E_DEV_ID_1G_BASE_T_X722:
		status = i40e_ग_लिखो_phy_रेजिस्टर_clause22(hw, reg, phy_addr,
							  value);
		अवरोध;
	हाल I40E_DEV_ID_5G_BASE_T_BC:
	हाल I40E_DEV_ID_10G_BASE_T:
	हाल I40E_DEV_ID_10G_BASE_T4:
	हाल I40E_DEV_ID_10G_BASE_T_BC:
	हाल I40E_DEV_ID_10G_BASE_T_X722:
	हाल I40E_DEV_ID_25G_B:
	हाल I40E_DEV_ID_25G_SFP28:
		status = i40e_ग_लिखो_phy_रेजिस्टर_clause45(hw, page, reg,
							  phy_addr, value);
		अवरोध;
	शेष:
		status = I40E_ERR_UNKNOWN_PHY;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_पढ़ो_phy_रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @page: रेजिस्टरs page number
 * @reg: रेजिस्टर address in the page
 * @phy_addr: PHY address on MDIO पूर्णांकerface
 * @value: PHY रेजिस्टर value
 *
 * Reads specअगरied PHY रेजिस्टर value
 **/
i40e_status i40e_पढ़ो_phy_रेजिस्टर(काष्ठा i40e_hw *hw,
				   u8 page, u16 reg, u8 phy_addr, u16 *value)
अणु
	i40e_status status;

	चयन (hw->device_id) अणु
	हाल I40E_DEV_ID_1G_BASE_T_X722:
		status = i40e_पढ़ो_phy_रेजिस्टर_clause22(hw, reg, phy_addr,
							 value);
		अवरोध;
	हाल I40E_DEV_ID_5G_BASE_T_BC:
	हाल I40E_DEV_ID_10G_BASE_T:
	हाल I40E_DEV_ID_10G_BASE_T4:
	हाल I40E_DEV_ID_10G_BASE_T_BC:
	हाल I40E_DEV_ID_10G_BASE_T_X722:
	हाल I40E_DEV_ID_25G_B:
	हाल I40E_DEV_ID_25G_SFP28:
		status = i40e_पढ़ो_phy_रेजिस्टर_clause45(hw, page, reg,
							 phy_addr, value);
		अवरोध;
	शेष:
		status = I40E_ERR_UNKNOWN_PHY;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_get_phy_address
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @dev_num: PHY port num that address we want
 *
 * Gets PHY address क्रम current port
 **/
u8 i40e_get_phy_address(काष्ठा i40e_hw *hw, u8 dev_num)
अणु
	u8 port_num = hw->func_caps.mdio_port_num;
	u32 reg_val = rd32(hw, I40E_GLGEN_MDIO_I2C_SEL(port_num));

	वापस (u8)(reg_val >> ((dev_num + 1) * 5)) & 0x1f;
पूर्ण

/**
 * i40e_blink_phy_link_led
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @समय: समय how दीर्घ led will blinks in secs
 * @पूर्णांकerval: gap between LED on and off in msecs
 *
 * Blinks PHY link LED
 **/
i40e_status i40e_blink_phy_link_led(काष्ठा i40e_hw *hw,
				    u32 समय, u32 पूर्णांकerval)
अणु
	i40e_status status = 0;
	u32 i;
	u16 led_ctl;
	u16 gpio_led_port;
	u16 led_reg;
	u16 led_addr = I40E_PHY_LED_PROV_REG_1;
	u8 phy_addr = 0;
	u8 port_num;

	i = rd32(hw, I40E_PFGEN_PORTNUM);
	port_num = (u8)(i & I40E_PFGEN_PORTNUM_PORT_NUM_MASK);
	phy_addr = i40e_get_phy_address(hw, port_num);

	क्रम (gpio_led_port = 0; gpio_led_port < 3; gpio_led_port++,
	     led_addr++) अणु
		status = i40e_पढ़ो_phy_रेजिस्टर_clause45(hw,
							 I40E_PHY_COM_REG_PAGE,
							 led_addr, phy_addr,
							 &led_reg);
		अगर (status)
			जाओ phy_blinking_end;
		led_ctl = led_reg;
		अगर (led_reg & I40E_PHY_LED_LINK_MODE_MASK) अणु
			led_reg = 0;
			status = i40e_ग_लिखो_phy_रेजिस्टर_clause45(hw,
							 I40E_PHY_COM_REG_PAGE,
							 led_addr, phy_addr,
							 led_reg);
			अगर (status)
				जाओ phy_blinking_end;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (समय > 0 && पूर्णांकerval > 0) अणु
		क्रम (i = 0; i < समय * 1000; i += पूर्णांकerval) अणु
			status = i40e_पढ़ो_phy_रेजिस्टर_clause45(hw,
						I40E_PHY_COM_REG_PAGE,
						led_addr, phy_addr, &led_reg);
			अगर (status)
				जाओ restore_config;
			अगर (led_reg & I40E_PHY_LED_MANUAL_ON)
				led_reg = 0;
			अन्यथा
				led_reg = I40E_PHY_LED_MANUAL_ON;
			status = i40e_ग_लिखो_phy_रेजिस्टर_clause45(hw,
						I40E_PHY_COM_REG_PAGE,
						led_addr, phy_addr, led_reg);
			अगर (status)
				जाओ restore_config;
			msleep(पूर्णांकerval);
		पूर्ण
	पूर्ण

restore_config:
	status = i40e_ग_लिखो_phy_रेजिस्टर_clause45(hw,
						  I40E_PHY_COM_REG_PAGE,
						  led_addr, phy_addr, led_ctl);

phy_blinking_end:
	वापस status;
पूर्ण

/**
 * i40e_led_get_reg - पढ़ो LED रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @led_addr: LED रेजिस्टर address
 * @reg_val: पढ़ो रेजिस्टर value
 **/
अटल क्रमागत i40e_status_code i40e_led_get_reg(काष्ठा i40e_hw *hw, u16 led_addr,
					      u32 *reg_val)
अणु
	क्रमागत i40e_status_code status;
	u8 phy_addr = 0;
	u8 port_num;
	u32 i;

	*reg_val = 0;
	अगर (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE) अणु
		status =
		       i40e_aq_get_phy_रेजिस्टर(hw,
						I40E_AQ_PHY_REG_ACCESS_EXTERNAL,
						I40E_PHY_COM_REG_PAGE, true,
						I40E_PHY_LED_PROV_REG_1,
						reg_val, शून्य);
	पूर्ण अन्यथा अणु
		i = rd32(hw, I40E_PFGEN_PORTNUM);
		port_num = (u8)(i & I40E_PFGEN_PORTNUM_PORT_NUM_MASK);
		phy_addr = i40e_get_phy_address(hw, port_num);
		status = i40e_पढ़ो_phy_रेजिस्टर_clause45(hw,
							 I40E_PHY_COM_REG_PAGE,
							 led_addr, phy_addr,
							 (u16 *)reg_val);
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_led_set_reg - ग_लिखो LED रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @led_addr: LED रेजिस्टर address
 * @reg_val: रेजिस्टर value to ग_लिखो
 **/
अटल क्रमागत i40e_status_code i40e_led_set_reg(काष्ठा i40e_hw *hw, u16 led_addr,
					      u32 reg_val)
अणु
	क्रमागत i40e_status_code status;
	u8 phy_addr = 0;
	u8 port_num;
	u32 i;

	अगर (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE) अणु
		status =
		       i40e_aq_set_phy_रेजिस्टर(hw,
						I40E_AQ_PHY_REG_ACCESS_EXTERNAL,
						I40E_PHY_COM_REG_PAGE, true,
						I40E_PHY_LED_PROV_REG_1,
						reg_val, शून्य);
	पूर्ण अन्यथा अणु
		i = rd32(hw, I40E_PFGEN_PORTNUM);
		port_num = (u8)(i & I40E_PFGEN_PORTNUM_PORT_NUM_MASK);
		phy_addr = i40e_get_phy_address(hw, port_num);
		status = i40e_ग_लिखो_phy_रेजिस्टर_clause45(hw,
							  I40E_PHY_COM_REG_PAGE,
							  led_addr, phy_addr,
							  (u16)reg_val);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_led_get_phy - वापस current on/off mode
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @led_addr: address of led रेजिस्टर to use
 * @val: original value of रेजिस्टर to use
 *
 **/
i40e_status i40e_led_get_phy(काष्ठा i40e_hw *hw, u16 *led_addr,
			     u16 *val)
अणु
	i40e_status status = 0;
	u16 gpio_led_port;
	u8 phy_addr = 0;
	u16 reg_val;
	u16 temp_addr;
	u8 port_num;
	u32 i;
	u32 reg_val_aq;

	अगर (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE) अणु
		status =
		      i40e_aq_get_phy_रेजिस्टर(hw,
					       I40E_AQ_PHY_REG_ACCESS_EXTERNAL,
					       I40E_PHY_COM_REG_PAGE, true,
					       I40E_PHY_LED_PROV_REG_1,
					       &reg_val_aq, शून्य);
		अगर (status == I40E_SUCCESS)
			*val = (u16)reg_val_aq;
		वापस status;
	पूर्ण
	temp_addr = I40E_PHY_LED_PROV_REG_1;
	i = rd32(hw, I40E_PFGEN_PORTNUM);
	port_num = (u8)(i & I40E_PFGEN_PORTNUM_PORT_NUM_MASK);
	phy_addr = i40e_get_phy_address(hw, port_num);

	क्रम (gpio_led_port = 0; gpio_led_port < 3; gpio_led_port++,
	     temp_addr++) अणु
		status = i40e_पढ़ो_phy_रेजिस्टर_clause45(hw,
							 I40E_PHY_COM_REG_PAGE,
							 temp_addr, phy_addr,
							 &reg_val);
		अगर (status)
			वापस status;
		*val = reg_val;
		अगर (reg_val & I40E_PHY_LED_LINK_MODE_MASK) अणु
			*led_addr = temp_addr;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_led_set_phy
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @on: true or false
 * @led_addr: address of led रेजिस्टर to use
 * @mode: original val plus bit क्रम set or ignore
 *
 * Set led's on or off when controlled by the PHY
 *
 **/
i40e_status i40e_led_set_phy(काष्ठा i40e_hw *hw, bool on,
			     u16 led_addr, u32 mode)
अणु
	i40e_status status = 0;
	u32 led_ctl = 0;
	u32 led_reg = 0;

	status = i40e_led_get_reg(hw, led_addr, &led_reg);
	अगर (status)
		वापस status;
	led_ctl = led_reg;
	अगर (led_reg & I40E_PHY_LED_LINK_MODE_MASK) अणु
		led_reg = 0;
		status = i40e_led_set_reg(hw, led_addr, led_reg);
		अगर (status)
			वापस status;
	पूर्ण
	status = i40e_led_get_reg(hw, led_addr, &led_reg);
	अगर (status)
		जाओ restore_config;
	अगर (on)
		led_reg = I40E_PHY_LED_MANUAL_ON;
	अन्यथा
		led_reg = 0;

	status = i40e_led_set_reg(hw, led_addr, led_reg);
	अगर (status)
		जाओ restore_config;
	अगर (mode & I40E_PHY_LED_MODE_ORIG) अणु
		led_ctl = (mode & I40E_PHY_LED_MODE_MASK);
		status = i40e_led_set_reg(hw, led_addr, led_ctl);
	पूर्ण
	वापस status;

restore_config:
	status = i40e_led_set_reg(hw, led_addr, led_ctl);
	वापस status;
पूर्ण

/**
 * i40e_aq_rx_ctl_पढ़ो_रेजिस्टर - use FW to पढ़ो from an Rx control रेजिस्टर
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg_addr: रेजिस्टर address
 * @reg_val: ptr to रेजिस्टर value
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Use the firmware to पढ़ो the Rx control रेजिस्टर,
 * especially useful अगर the Rx unit is under heavy pressure
 **/
i40e_status i40e_aq_rx_ctl_पढ़ो_रेजिस्टर(काष्ठा i40e_hw *hw,
				u32 reg_addr, u32 *reg_val,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_rx_ctl_reg_पढ़ो_ग_लिखो *cmd_resp =
		(काष्ठा i40e_aqc_rx_ctl_reg_पढ़ो_ग_लिखो *)&desc.params.raw;
	i40e_status status;

	अगर (!reg_val)
		वापस I40E_ERR_PARAM;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_rx_ctl_reg_पढ़ो);

	cmd_resp->address = cpu_to_le32(reg_addr);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	अगर (status == 0)
		*reg_val = le32_to_cpu(cmd_resp->value);

	वापस status;
पूर्ण

/**
 * i40e_पढ़ो_rx_ctl - पढ़ो from an Rx control रेजिस्टर
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg_addr: रेजिस्टर address
 **/
u32 i40e_पढ़ो_rx_ctl(काष्ठा i40e_hw *hw, u32 reg_addr)
अणु
	i40e_status status = 0;
	bool use_रेजिस्टर;
	पूर्णांक retry = 5;
	u32 val = 0;

	use_रेजिस्टर = (((hw->aq.api_maj_ver == 1) &&
			(hw->aq.api_min_ver < 5)) ||
			(hw->mac.type == I40E_MAC_X722));
	अगर (!use_रेजिस्टर) अणु
करो_retry:
		status = i40e_aq_rx_ctl_पढ़ो_रेजिस्टर(hw, reg_addr, &val, शून्य);
		अगर (hw->aq.asq_last_status == I40E_AQ_RC_EAGAIN && retry) अणु
			usleep_range(1000, 2000);
			retry--;
			जाओ करो_retry;
		पूर्ण
	पूर्ण

	/* अगर the AQ access failed, try the old-fashioned way */
	अगर (status || use_रेजिस्टर)
		val = rd32(hw, reg_addr);

	वापस val;
पूर्ण

/**
 * i40e_aq_rx_ctl_ग_लिखो_रेजिस्टर
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg_addr: रेजिस्टर address
 * @reg_val: रेजिस्टर value
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Use the firmware to ग_लिखो to an Rx control रेजिस्टर,
 * especially useful अगर the Rx unit is under heavy pressure
 **/
i40e_status i40e_aq_rx_ctl_ग_लिखो_रेजिस्टर(काष्ठा i40e_hw *hw,
				u32 reg_addr, u32 reg_val,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_rx_ctl_reg_पढ़ो_ग_लिखो *cmd =
		(काष्ठा i40e_aqc_rx_ctl_reg_पढ़ो_ग_लिखो *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc, i40e_aqc_opc_rx_ctl_reg_ग_लिखो);

	cmd->address = cpu_to_le32(reg_addr);
	cmd->value = cpu_to_le32(reg_val);

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_ग_लिखो_rx_ctl - ग_लिखो to an Rx control रेजिस्टर
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg_addr: रेजिस्टर address
 * @reg_val: रेजिस्टर value
 **/
व्योम i40e_ग_लिखो_rx_ctl(काष्ठा i40e_hw *hw, u32 reg_addr, u32 reg_val)
अणु
	i40e_status status = 0;
	bool use_रेजिस्टर;
	पूर्णांक retry = 5;

	use_रेजिस्टर = (((hw->aq.api_maj_ver == 1) &&
			(hw->aq.api_min_ver < 5)) ||
			(hw->mac.type == I40E_MAC_X722));
	अगर (!use_रेजिस्टर) अणु
करो_retry:
		status = i40e_aq_rx_ctl_ग_लिखो_रेजिस्टर(hw, reg_addr,
						       reg_val, शून्य);
		अगर (hw->aq.asq_last_status == I40E_AQ_RC_EAGAIN && retry) अणु
			usleep_range(1000, 2000);
			retry--;
			जाओ करो_retry;
		पूर्ण
	पूर्ण

	/* अगर the AQ access failed, try the old-fashioned way */
	अगर (status || use_रेजिस्टर)
		wr32(hw, reg_addr, reg_val);
पूर्ण

/**
 * i40e_mdio_अगर_number_selection - MDIO I/F number selection
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @set_mdio: use MDIO I/F number specअगरied by mdio_num
 * @mdio_num: MDIO I/F number
 * @cmd: poपूर्णांकer to PHY Register command काष्ठाure
 **/
अटल व्योम i40e_mdio_अगर_number_selection(काष्ठा i40e_hw *hw, bool set_mdio,
					  u8 mdio_num,
					  काष्ठा i40e_aqc_phy_रेजिस्टर_access *cmd)
अणु
	अगर (set_mdio && cmd->phy_पूर्णांकerface == I40E_AQ_PHY_REG_ACCESS_EXTERNAL) अणु
		अगर (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_EXTENDED)
			cmd->cmd_flags |=
				I40E_AQ_PHY_REG_ACCESS_SET_MDIO_IF_NUMBER |
				((mdio_num <<
				I40E_AQ_PHY_REG_ACCESS_MDIO_IF_NUMBER_SHIFT) &
				I40E_AQ_PHY_REG_ACCESS_MDIO_IF_NUMBER_MASK);
		अन्यथा
			i40e_debug(hw, I40E_DEBUG_PHY,
				   "MDIO I/F number selection not supported by current FW version.\n");
	पूर्ण
पूर्ण

/**
 * i40e_aq_set_phy_रेजिस्टर_ext
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @phy_select: select which phy should be accessed
 * @dev_addr: PHY device address
 * @page_change: flag to indicate अगर phy page should be updated
 * @set_mdio: use MDIO I/F number specअगरied by mdio_num
 * @mdio_num: MDIO I/F number
 * @reg_addr: PHY रेजिस्टर address
 * @reg_val: new रेजिस्टर value
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Write the बाह्यal PHY रेजिस्टर.
 * NOTE: In common हालs MDIO I/F number should not be changed, thats why you
 * may use simple wrapper i40e_aq_set_phy_रेजिस्टर.
 **/
क्रमागत i40e_status_code i40e_aq_set_phy_रेजिस्टर_ext(काष्ठा i40e_hw *hw,
			     u8 phy_select, u8 dev_addr, bool page_change,
			     bool set_mdio, u8 mdio_num,
			     u32 reg_addr, u32 reg_val,
			     काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_phy_रेजिस्टर_access *cmd =
		(काष्ठा i40e_aqc_phy_रेजिस्टर_access *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_phy_रेजिस्टर);

	cmd->phy_पूर्णांकerface = phy_select;
	cmd->dev_address = dev_addr;
	cmd->reg_address = cpu_to_le32(reg_addr);
	cmd->reg_value = cpu_to_le32(reg_val);

	i40e_mdio_अगर_number_selection(hw, set_mdio, mdio_num, cmd);

	अगर (!page_change)
		cmd->cmd_flags = I40E_AQ_PHY_REG_ACCESS_DONT_CHANGE_QSFP_PAGE;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_aq_get_phy_रेजिस्टर_ext
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @phy_select: select which phy should be accessed
 * @dev_addr: PHY device address
 * @page_change: flag to indicate अगर phy page should be updated
 * @set_mdio: use MDIO I/F number specअगरied by mdio_num
 * @mdio_num: MDIO I/F number
 * @reg_addr: PHY रेजिस्टर address
 * @reg_val: पढ़ो रेजिस्टर value
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Read the बाह्यal PHY रेजिस्टर.
 * NOTE: In common हालs MDIO I/F number should not be changed, thats why you
 * may use simple wrapper i40e_aq_get_phy_रेजिस्टर.
 **/
क्रमागत i40e_status_code i40e_aq_get_phy_रेजिस्टर_ext(काष्ठा i40e_hw *hw,
			     u8 phy_select, u8 dev_addr, bool page_change,
			     bool set_mdio, u8 mdio_num,
			     u32 reg_addr, u32 *reg_val,
			     काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_phy_रेजिस्टर_access *cmd =
		(काष्ठा i40e_aqc_phy_रेजिस्टर_access *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_phy_रेजिस्टर);

	cmd->phy_पूर्णांकerface = phy_select;
	cmd->dev_address = dev_addr;
	cmd->reg_address = cpu_to_le32(reg_addr);

	i40e_mdio_अगर_number_selection(hw, set_mdio, mdio_num, cmd);

	अगर (!page_change)
		cmd->cmd_flags = I40E_AQ_PHY_REG_ACCESS_DONT_CHANGE_QSFP_PAGE;

	status = i40e_asq_send_command(hw, &desc, शून्य, 0, cmd_details);
	अगर (!status)
		*reg_val = le32_to_cpu(cmd->reg_value);

	वापस status;
पूर्ण

/**
 * i40e_aq_ग_लिखो_ddp - Write dynamic device personalization (ddp)
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @buff: command buffer (size in bytes = buff_size)
 * @buff_size: buffer size in bytes
 * @track_id: package tracking id
 * @error_offset: वापसs error offset
 * @error_info: वापसs error inक्रमmation
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
क्रमागत
i40e_status_code i40e_aq_ग_लिखो_ddp(काष्ठा i40e_hw *hw, व्योम *buff,
				   u16 buff_size, u32 track_id,
				   u32 *error_offset, u32 *error_info,
				   काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_ग_लिखो_personalization_profile *cmd =
		(काष्ठा i40e_aqc_ग_लिखो_personalization_profile *)
		&desc.params.raw;
	काष्ठा i40e_aqc_ग_लिखो_ddp_resp *resp;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_ग_लिखो_personalization_profile);

	desc.flags |= cpu_to_le16(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD);
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	desc.datalen = cpu_to_le16(buff_size);

	cmd->profile_track_id = cpu_to_le32(track_id);

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);
	अगर (!status) अणु
		resp = (काष्ठा i40e_aqc_ग_लिखो_ddp_resp *)&desc.params.raw;
		अगर (error_offset)
			*error_offset = le32_to_cpu(resp->error_offset);
		अगर (error_info)
			*error_info = le32_to_cpu(resp->error_info);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_aq_get_ddp_list - Read dynamic device personalization (ddp)
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @buff: command buffer (size in bytes = buff_size)
 * @buff_size: buffer size in bytes
 * @flags: AdminQ command flags
 * @cmd_details: poपूर्णांकer to command details काष्ठाure or शून्य
 **/
क्रमागत
i40e_status_code i40e_aq_get_ddp_list(काष्ठा i40e_hw *hw, व्योम *buff,
				      u16 buff_size, u8 flags,
				      काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_get_applied_profiles *cmd =
		(काष्ठा i40e_aqc_get_applied_profiles *)&desc.params.raw;
	i40e_status status;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_personalization_profile_list);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	अगर (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
	desc.datalen = cpu_to_le16(buff_size);

	cmd->flags = flags;

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);

	वापस status;
पूर्ण

/**
 * i40e_find_segment_in_package
 * @segment_type: the segment type to search क्रम (i.e., SEGMENT_TYPE_I40E)
 * @pkg_hdr: poपूर्णांकer to the package header to be searched
 *
 * This function searches a package file क्रम a particular segment type. On
 * success it वापसs a poपूर्णांकer to the segment header, otherwise it will
 * वापस शून्य.
 **/
काष्ठा i40e_generic_seg_header *
i40e_find_segment_in_package(u32 segment_type,
			     काष्ठा i40e_package_header *pkg_hdr)
अणु
	काष्ठा i40e_generic_seg_header *segment;
	u32 i;

	/* Search all package segments क्रम the requested segment type */
	क्रम (i = 0; i < pkg_hdr->segment_count; i++) अणु
		segment =
			(काष्ठा i40e_generic_seg_header *)((u8 *)pkg_hdr +
			 pkg_hdr->segment_offset[i]);

		अगर (segment->type == segment_type)
			वापस segment;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Get section table in profile */
#घोषणा I40E_SECTION_TABLE(profile, sec_tbl)				\
	करो अणु								\
		काष्ठा i40e_profile_segment *p = (profile);		\
		u32 count;						\
		u32 *nvm;						\
		count = p->device_table_count;				\
		nvm = (u32 *)&p->device_table[count];			\
		sec_tbl = (काष्ठा i40e_section_table *)&nvm[nvm[0] + 1]; \
	पूर्ण जबतक (0)

/* Get section header in profile */
#घोषणा I40E_SECTION_HEADER(profile, offset)				\
	(काष्ठा i40e_profile_section_header *)((u8 *)(profile) + (offset))

/**
 * i40e_find_section_in_profile
 * @section_type: the section type to search क्रम (i.e., SECTION_TYPE_NOTE)
 * @profile: poपूर्णांकer to the i40e segment header to be searched
 *
 * This function searches i40e segment क्रम a particular section type. On
 * success it वापसs a poपूर्णांकer to the section header, otherwise it will
 * वापस शून्य.
 **/
काष्ठा i40e_profile_section_header *
i40e_find_section_in_profile(u32 section_type,
			     काष्ठा i40e_profile_segment *profile)
अणु
	काष्ठा i40e_profile_section_header *sec;
	काष्ठा i40e_section_table *sec_tbl;
	u32 sec_off;
	u32 i;

	अगर (profile->header.type != SEGMENT_TYPE_I40E)
		वापस शून्य;

	I40E_SECTION_TABLE(profile, sec_tbl);

	क्रम (i = 0; i < sec_tbl->section_count; i++) अणु
		sec_off = sec_tbl->section_offset[i];
		sec = I40E_SECTION_HEADER(profile, sec_off);
		अगर (sec->section.type == section_type)
			वापस sec;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * i40e_ddp_exec_aq_section - Execute generic AQ क्रम DDP
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @aq: command buffer containing all data to execute AQ
 **/
अटल क्रमागत
i40e_status_code i40e_ddp_exec_aq_section(काष्ठा i40e_hw *hw,
					  काष्ठा i40e_profile_aq_section *aq)
अणु
	i40e_status status;
	काष्ठा i40e_aq_desc desc;
	u8 *msg = शून्य;
	u16 msglen;

	i40e_fill_शेष_direct_cmd_desc(&desc, aq->opcode);
	desc.flags |= cpu_to_le16(aq->flags);
	स_नकल(desc.params.raw, aq->param, माप(desc.params.raw));

	msglen = aq->datalen;
	अगर (msglen) अणु
		desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF |
						I40E_AQ_FLAG_RD));
		अगर (msglen > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
		desc.datalen = cpu_to_le16(msglen);
		msg = &aq->data[0];
	पूर्ण

	status = i40e_asq_send_command(hw, &desc, msg, msglen, शून्य);

	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_PACKAGE,
			   "unable to exec DDP AQ opcode %u, error %d\n",
			   aq->opcode, status);
		वापस status;
	पूर्ण

	/* copy वापसed desc to aq_buf */
	स_नकल(aq->param, desc.params.raw, माप(desc.params.raw));

	वापस 0;
पूर्ण

/**
 * i40e_validate_profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @profile: poपूर्णांकer to the profile segment of the package to be validated
 * @track_id: package tracking id
 * @rollback: flag अगर the profile is क्रम rollback.
 *
 * Validates supported devices and profile's sections.
 */
अटल क्रमागत i40e_status_code
i40e_validate_profile(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *profile,
		      u32 track_id, bool rollback)
अणु
	काष्ठा i40e_profile_section_header *sec = शून्य;
	i40e_status status = 0;
	काष्ठा i40e_section_table *sec_tbl;
	u32 venकरोr_dev_id;
	u32 dev_cnt;
	u32 sec_off;
	u32 i;

	अगर (track_id == I40E_DDP_TRACKID_INVALID) अणु
		i40e_debug(hw, I40E_DEBUG_PACKAGE, "Invalid track_id\n");
		वापस I40E_NOT_SUPPORTED;
	पूर्ण

	dev_cnt = profile->device_table_count;
	क्रम (i = 0; i < dev_cnt; i++) अणु
		venकरोr_dev_id = profile->device_table[i].venकरोr_dev_id;
		अगर ((venकरोr_dev_id >> 16) == PCI_VENDOR_ID_INTEL &&
		    hw->device_id == (venकरोr_dev_id & 0xFFFF))
			अवरोध;
	पूर्ण
	अगर (dev_cnt && i == dev_cnt) अणु
		i40e_debug(hw, I40E_DEBUG_PACKAGE,
			   "Device doesn't support DDP\n");
		वापस I40E_ERR_DEVICE_NOT_SUPPORTED;
	पूर्ण

	I40E_SECTION_TABLE(profile, sec_tbl);

	/* Validate sections types */
	क्रम (i = 0; i < sec_tbl->section_count; i++) अणु
		sec_off = sec_tbl->section_offset[i];
		sec = I40E_SECTION_HEADER(profile, sec_off);
		अगर (rollback) अणु
			अगर (sec->section.type == SECTION_TYPE_MMIO ||
			    sec->section.type == SECTION_TYPE_AQ ||
			    sec->section.type == SECTION_TYPE_RB_AQ) अणु
				i40e_debug(hw, I40E_DEBUG_PACKAGE,
					   "Not a roll-back package\n");
				वापस I40E_NOT_SUPPORTED;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sec->section.type == SECTION_TYPE_RB_AQ ||
			    sec->section.type == SECTION_TYPE_RB_MMIO) अणु
				i40e_debug(hw, I40E_DEBUG_PACKAGE,
					   "Not an original package\n");
				वापस I40E_NOT_SUPPORTED;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_ग_लिखो_profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @profile: poपूर्णांकer to the profile segment of the package to be करोwnloaded
 * @track_id: package tracking id
 *
 * Handles the करोwnload of a complete package.
 */
क्रमागत i40e_status_code
i40e_ग_लिखो_profile(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *profile,
		   u32 track_id)
अणु
	i40e_status status = 0;
	काष्ठा i40e_section_table *sec_tbl;
	काष्ठा i40e_profile_section_header *sec = शून्य;
	काष्ठा i40e_profile_aq_section *ddp_aq;
	u32 section_size = 0;
	u32 offset = 0, info = 0;
	u32 sec_off;
	u32 i;

	status = i40e_validate_profile(hw, profile, track_id, false);
	अगर (status)
		वापस status;

	I40E_SECTION_TABLE(profile, sec_tbl);

	क्रम (i = 0; i < sec_tbl->section_count; i++) अणु
		sec_off = sec_tbl->section_offset[i];
		sec = I40E_SECTION_HEADER(profile, sec_off);
		/* Process generic admin command */
		अगर (sec->section.type == SECTION_TYPE_AQ) अणु
			ddp_aq = (काष्ठा i40e_profile_aq_section *)&sec[1];
			status = i40e_ddp_exec_aq_section(hw, ddp_aq);
			अगर (status) अणु
				i40e_debug(hw, I40E_DEBUG_PACKAGE,
					   "Failed to execute aq: section %d, opcode %u\n",
					   i, ddp_aq->opcode);
				अवरोध;
			पूर्ण
			sec->section.type = SECTION_TYPE_RB_AQ;
		पूर्ण

		/* Skip any non-mmio sections */
		अगर (sec->section.type != SECTION_TYPE_MMIO)
			जारी;

		section_size = sec->section.size +
			माप(काष्ठा i40e_profile_section_header);

		/* Write MMIO section */
		status = i40e_aq_ग_लिखो_ddp(hw, (व्योम *)sec, (u16)section_size,
					   track_id, &offset, &info, शून्य);
		अगर (status) अणु
			i40e_debug(hw, I40E_DEBUG_PACKAGE,
				   "Failed to write profile: section %d, offset %d, info %d\n",
				   i, offset, info);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_rollback_profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @profile: poपूर्णांकer to the profile segment of the package to be हटाओd
 * @track_id: package tracking id
 *
 * Rolls back previously loaded package.
 */
क्रमागत i40e_status_code
i40e_rollback_profile(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *profile,
		      u32 track_id)
अणु
	काष्ठा i40e_profile_section_header *sec = शून्य;
	i40e_status status = 0;
	काष्ठा i40e_section_table *sec_tbl;
	u32 offset = 0, info = 0;
	u32 section_size = 0;
	u32 sec_off;
	पूर्णांक i;

	status = i40e_validate_profile(hw, profile, track_id, true);
	अगर (status)
		वापस status;

	I40E_SECTION_TABLE(profile, sec_tbl);

	/* For rollback ग_लिखो sections in reverse */
	क्रम (i = sec_tbl->section_count - 1; i >= 0; i--) अणु
		sec_off = sec_tbl->section_offset[i];
		sec = I40E_SECTION_HEADER(profile, sec_off);

		/* Skip any non-rollback sections */
		अगर (sec->section.type != SECTION_TYPE_RB_MMIO)
			जारी;

		section_size = sec->section.size +
			माप(काष्ठा i40e_profile_section_header);

		/* Write roll-back MMIO section */
		status = i40e_aq_ग_लिखो_ddp(hw, (व्योम *)sec, (u16)section_size,
					   track_id, &offset, &info, शून्य);
		अगर (status) अणु
			i40e_debug(hw, I40E_DEBUG_PACKAGE,
				   "Failed to write profile: section %d, offset %d, info %d\n",
				   i, offset, info);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_add_pinfo_to_list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @profile: poपूर्णांकer to the profile segment of the package
 * @profile_info_sec: buffer क्रम inक्रमmation section
 * @track_id: package tracking id
 *
 * Register a profile to the list of loaded profiles.
 */
क्रमागत i40e_status_code
i40e_add_pinfo_to_list(काष्ठा i40e_hw *hw,
		       काष्ठा i40e_profile_segment *profile,
		       u8 *profile_info_sec, u32 track_id)
अणु
	i40e_status status = 0;
	काष्ठा i40e_profile_section_header *sec = शून्य;
	काष्ठा i40e_profile_info *pinfo;
	u32 offset = 0, info = 0;

	sec = (काष्ठा i40e_profile_section_header *)profile_info_sec;
	sec->tbl_size = 1;
	sec->data_end = माप(काष्ठा i40e_profile_section_header) +
			माप(काष्ठा i40e_profile_info);
	sec->section.type = SECTION_TYPE_INFO;
	sec->section.offset = माप(काष्ठा i40e_profile_section_header);
	sec->section.size = माप(काष्ठा i40e_profile_info);
	pinfo = (काष्ठा i40e_profile_info *)(profile_info_sec +
					     sec->section.offset);
	pinfo->track_id = track_id;
	pinfo->version = profile->version;
	pinfo->op = I40E_DDP_ADD_TRACKID;
	स_नकल(pinfo->name, profile->name, I40E_DDP_NAME_SIZE);

	status = i40e_aq_ग_लिखो_ddp(hw, (व्योम *)sec, sec->data_end,
				   track_id, &offset, &info, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_add_cloud_filters
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @seid: VSI seid to add cloud filters from
 * @filters: Buffer which contains the filters to be added
 * @filter_count: number of filters contained in the buffer
 *
 * Set the cloud filters क्रम a given VSI.  The contents of the
 * i40e_aqc_cloud_filters_element_data are filled in by the caller
 * of the function.
 *
 **/
क्रमागत i40e_status_code
i40e_aq_add_cloud_filters(काष्ठा i40e_hw *hw, u16 seid,
			  काष्ठा i40e_aqc_cloud_filters_element_data *filters,
			  u8 filter_count)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_हटाओ_cloud_filters *cmd =
	(काष्ठा i40e_aqc_add_हटाओ_cloud_filters *)&desc.params.raw;
	क्रमागत i40e_status_code status;
	u16 buff_len;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_add_cloud_filters);

	buff_len = filter_count * माप(*filters);
	desc.datalen = cpu_to_le16(buff_len);
	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	cmd->num_filters = filter_count;
	cmd->seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, filters, buff_len, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_add_cloud_filters_bb
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @seid: VSI seid to add cloud filters from
 * @filters: Buffer which contains the filters in big buffer to be added
 * @filter_count: number of filters contained in the buffer
 *
 * Set the big buffer cloud filters क्रम a given VSI.  The contents of the
 * i40e_aqc_cloud_filters_element_bb are filled in by the caller of the
 * function.
 *
 **/
क्रमागत i40e_status_code
i40e_aq_add_cloud_filters_bb(काष्ठा i40e_hw *hw, u16 seid,
			     काष्ठा i40e_aqc_cloud_filters_element_bb *filters,
			     u8 filter_count)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_हटाओ_cloud_filters *cmd =
	(काष्ठा i40e_aqc_add_हटाओ_cloud_filters *)&desc.params.raw;
	i40e_status status;
	u16 buff_len;
	पूर्णांक i;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_add_cloud_filters);

	buff_len = filter_count * माप(*filters);
	desc.datalen = cpu_to_le16(buff_len);
	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	cmd->num_filters = filter_count;
	cmd->seid = cpu_to_le16(seid);
	cmd->big_buffer_flag = I40E_AQC_ADD_CLOUD_CMD_BB;

	क्रम (i = 0; i < filter_count; i++) अणु
		u16 tnl_type;
		u32 ti;

		tnl_type = (le16_to_cpu(filters[i].element.flags) &
			   I40E_AQC_ADD_CLOUD_TNL_TYPE_MASK) >>
			   I40E_AQC_ADD_CLOUD_TNL_TYPE_SHIFT;

		/* Due to hardware eccentricities, the VNI क्रम Geneve is shअगरted
		 * one more byte further than normally used क्रम Tenant ID in
		 * other tunnel types.
		 */
		अगर (tnl_type == I40E_AQC_ADD_CLOUD_TNL_TYPE_GENEVE) अणु
			ti = le32_to_cpu(filters[i].element.tenant_id);
			filters[i].element.tenant_id = cpu_to_le32(ti << 8);
		पूर्ण
	पूर्ण

	status = i40e_asq_send_command(hw, &desc, filters, buff_len, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_rem_cloud_filters
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @seid: VSI seid to हटाओ cloud filters from
 * @filters: Buffer which contains the filters to be हटाओd
 * @filter_count: number of filters contained in the buffer
 *
 * Remove the cloud filters क्रम a given VSI.  The contents of the
 * i40e_aqc_cloud_filters_element_data are filled in by the caller
 * of the function.
 *
 **/
क्रमागत i40e_status_code
i40e_aq_rem_cloud_filters(काष्ठा i40e_hw *hw, u16 seid,
			  काष्ठा i40e_aqc_cloud_filters_element_data *filters,
			  u8 filter_count)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_हटाओ_cloud_filters *cmd =
	(काष्ठा i40e_aqc_add_हटाओ_cloud_filters *)&desc.params.raw;
	क्रमागत i40e_status_code status;
	u16 buff_len;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_हटाओ_cloud_filters);

	buff_len = filter_count * माप(*filters);
	desc.datalen = cpu_to_le16(buff_len);
	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	cmd->num_filters = filter_count;
	cmd->seid = cpu_to_le16(seid);

	status = i40e_asq_send_command(hw, &desc, filters, buff_len, शून्य);

	वापस status;
पूर्ण

/**
 * i40e_aq_rem_cloud_filters_bb
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @seid: VSI seid to हटाओ cloud filters from
 * @filters: Buffer which contains the filters in big buffer to be हटाओd
 * @filter_count: number of filters contained in the buffer
 *
 * Remove the big buffer cloud filters क्रम a given VSI.  The contents of the
 * i40e_aqc_cloud_filters_element_bb are filled in by the caller of the
 * function.
 *
 **/
क्रमागत i40e_status_code
i40e_aq_rem_cloud_filters_bb(काष्ठा i40e_hw *hw, u16 seid,
			     काष्ठा i40e_aqc_cloud_filters_element_bb *filters,
			     u8 filter_count)
अणु
	काष्ठा i40e_aq_desc desc;
	काष्ठा i40e_aqc_add_हटाओ_cloud_filters *cmd =
	(काष्ठा i40e_aqc_add_हटाओ_cloud_filters *)&desc.params.raw;
	i40e_status status;
	u16 buff_len;
	पूर्णांक i;

	i40e_fill_शेष_direct_cmd_desc(&desc,
					  i40e_aqc_opc_हटाओ_cloud_filters);

	buff_len = filter_count * माप(*filters);
	desc.datalen = cpu_to_le16(buff_len);
	desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD));
	cmd->num_filters = filter_count;
	cmd->seid = cpu_to_le16(seid);
	cmd->big_buffer_flag = I40E_AQC_ADD_CLOUD_CMD_BB;

	क्रम (i = 0; i < filter_count; i++) अणु
		u16 tnl_type;
		u32 ti;

		tnl_type = (le16_to_cpu(filters[i].element.flags) &
			   I40E_AQC_ADD_CLOUD_TNL_TYPE_MASK) >>
			   I40E_AQC_ADD_CLOUD_TNL_TYPE_SHIFT;

		/* Due to hardware eccentricities, the VNI क्रम Geneve is shअगरted
		 * one more byte further than normally used क्रम Tenant ID in
		 * other tunnel types.
		 */
		अगर (tnl_type == I40E_AQC_ADD_CLOUD_TNL_TYPE_GENEVE) अणु
			ti = le32_to_cpu(filters[i].element.tenant_id);
			filters[i].element.tenant_id = cpu_to_le32(ti << 8);
		पूर्ण
	पूर्ण

	status = i40e_asq_send_command(hw, &desc, filters, buff_len, शून्य);

	वापस status;
पूर्ण
