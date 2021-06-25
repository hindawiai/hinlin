<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "iavf_type.h"
#समावेश "iavf_adminq.h"
#समावेश "iavf_prototype.h"
#समावेश <linux/avf/virtchnl.h>

/**
 * iavf_set_mac_type - Sets MAC type
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function sets the mac type of the adapter based on the
 * venकरोr ID and device ID stored in the hw काष्ठाure.
 **/
क्रमागत iavf_status iavf_set_mac_type(काष्ठा iavf_hw *hw)
अणु
	क्रमागत iavf_status status = 0;

	अगर (hw->venकरोr_id == PCI_VENDOR_ID_INTEL) अणु
		चयन (hw->device_id) अणु
		हाल IAVF_DEV_ID_X722_VF:
			hw->mac.type = IAVF_MAC_X722_VF;
			अवरोध;
		हाल IAVF_DEV_ID_VF:
		हाल IAVF_DEV_ID_VF_HV:
		हाल IAVF_DEV_ID_ADAPTIVE_VF:
			hw->mac.type = IAVF_MAC_VF;
			अवरोध;
		शेष:
			hw->mac.type = IAVF_MAC_GENERIC;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = IAVF_ERR_DEVICE_NOT_SUPPORTED;
	पूर्ण

	hw_dbg(hw, "found mac: %d, returns: %d\n", hw->mac.type, status);
	वापस status;
पूर्ण

/**
 * iavf_aq_str - convert AQ err code to a string
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @aq_err: the AQ error code to convert
 **/
स्थिर अक्षर *iavf_aq_str(काष्ठा iavf_hw *hw, क्रमागत iavf_admin_queue_err aq_err)
अणु
	चयन (aq_err) अणु
	हाल IAVF_AQ_RC_OK:
		वापस "OK";
	हाल IAVF_AQ_RC_EPERM:
		वापस "IAVF_AQ_RC_EPERM";
	हाल IAVF_AQ_RC_ENOENT:
		वापस "IAVF_AQ_RC_ENOENT";
	हाल IAVF_AQ_RC_ESRCH:
		वापस "IAVF_AQ_RC_ESRCH";
	हाल IAVF_AQ_RC_EINTR:
		वापस "IAVF_AQ_RC_EINTR";
	हाल IAVF_AQ_RC_EIO:
		वापस "IAVF_AQ_RC_EIO";
	हाल IAVF_AQ_RC_ENXIO:
		वापस "IAVF_AQ_RC_ENXIO";
	हाल IAVF_AQ_RC_E2BIG:
		वापस "IAVF_AQ_RC_E2BIG";
	हाल IAVF_AQ_RC_EAGAIN:
		वापस "IAVF_AQ_RC_EAGAIN";
	हाल IAVF_AQ_RC_ENOMEM:
		वापस "IAVF_AQ_RC_ENOMEM";
	हाल IAVF_AQ_RC_EACCES:
		वापस "IAVF_AQ_RC_EACCES";
	हाल IAVF_AQ_RC_EFAULT:
		वापस "IAVF_AQ_RC_EFAULT";
	हाल IAVF_AQ_RC_EBUSY:
		वापस "IAVF_AQ_RC_EBUSY";
	हाल IAVF_AQ_RC_EEXIST:
		वापस "IAVF_AQ_RC_EEXIST";
	हाल IAVF_AQ_RC_EINVAL:
		वापस "IAVF_AQ_RC_EINVAL";
	हाल IAVF_AQ_RC_ENOTTY:
		वापस "IAVF_AQ_RC_ENOTTY";
	हाल IAVF_AQ_RC_ENOSPC:
		वापस "IAVF_AQ_RC_ENOSPC";
	हाल IAVF_AQ_RC_ENOSYS:
		वापस "IAVF_AQ_RC_ENOSYS";
	हाल IAVF_AQ_RC_दुस्फल:
		वापस "IAVF_AQ_RC_ERANGE";
	हाल IAVF_AQ_RC_EFLUSHED:
		वापस "IAVF_AQ_RC_EFLUSHED";
	हाल IAVF_AQ_RC_BAD_ADDR:
		वापस "IAVF_AQ_RC_BAD_ADDR";
	हाल IAVF_AQ_RC_EMODE:
		वापस "IAVF_AQ_RC_EMODE";
	हाल IAVF_AQ_RC_EFBIG:
		वापस "IAVF_AQ_RC_EFBIG";
	पूर्ण

	snम_लिखो(hw->err_str, माप(hw->err_str), "%d", aq_err);
	वापस hw->err_str;
पूर्ण

/**
 * iavf_stat_str - convert status err code to a string
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @stat_err: the status error code to convert
 **/
स्थिर अक्षर *iavf_stat_str(काष्ठा iavf_hw *hw, क्रमागत iavf_status stat_err)
अणु
	चयन (stat_err) अणु
	हाल 0:
		वापस "OK";
	हाल IAVF_ERR_NVM:
		वापस "IAVF_ERR_NVM";
	हाल IAVF_ERR_NVM_CHECKSUM:
		वापस "IAVF_ERR_NVM_CHECKSUM";
	हाल IAVF_ERR_PHY:
		वापस "IAVF_ERR_PHY";
	हाल IAVF_ERR_CONFIG:
		वापस "IAVF_ERR_CONFIG";
	हाल IAVF_ERR_PARAM:
		वापस "IAVF_ERR_PARAM";
	हाल IAVF_ERR_MAC_TYPE:
		वापस "IAVF_ERR_MAC_TYPE";
	हाल IAVF_ERR_UNKNOWN_PHY:
		वापस "IAVF_ERR_UNKNOWN_PHY";
	हाल IAVF_ERR_LINK_SETUP:
		वापस "IAVF_ERR_LINK_SETUP";
	हाल IAVF_ERR_ADAPTER_STOPPED:
		वापस "IAVF_ERR_ADAPTER_STOPPED";
	हाल IAVF_ERR_INVALID_MAC_ADDR:
		वापस "IAVF_ERR_INVALID_MAC_ADDR";
	हाल IAVF_ERR_DEVICE_NOT_SUPPORTED:
		वापस "IAVF_ERR_DEVICE_NOT_SUPPORTED";
	हाल IAVF_ERR_MASTER_REQUESTS_PENDING:
		वापस "IAVF_ERR_MASTER_REQUESTS_PENDING";
	हाल IAVF_ERR_INVALID_LINK_SETTINGS:
		वापस "IAVF_ERR_INVALID_LINK_SETTINGS";
	हाल IAVF_ERR_AUTONEG_NOT_COMPLETE:
		वापस "IAVF_ERR_AUTONEG_NOT_COMPLETE";
	हाल IAVF_ERR_RESET_FAILED:
		वापस "IAVF_ERR_RESET_FAILED";
	हाल IAVF_ERR_SWFW_SYNC:
		वापस "IAVF_ERR_SWFW_SYNC";
	हाल IAVF_ERR_NO_AVAILABLE_VSI:
		वापस "IAVF_ERR_NO_AVAILABLE_VSI";
	हाल IAVF_ERR_NO_MEMORY:
		वापस "IAVF_ERR_NO_MEMORY";
	हाल IAVF_ERR_BAD_PTR:
		वापस "IAVF_ERR_BAD_PTR";
	हाल IAVF_ERR_RING_FULL:
		वापस "IAVF_ERR_RING_FULL";
	हाल IAVF_ERR_INVALID_PD_ID:
		वापस "IAVF_ERR_INVALID_PD_ID";
	हाल IAVF_ERR_INVALID_QP_ID:
		वापस "IAVF_ERR_INVALID_QP_ID";
	हाल IAVF_ERR_INVALID_CQ_ID:
		वापस "IAVF_ERR_INVALID_CQ_ID";
	हाल IAVF_ERR_INVALID_CEQ_ID:
		वापस "IAVF_ERR_INVALID_CEQ_ID";
	हाल IAVF_ERR_INVALID_AEQ_ID:
		वापस "IAVF_ERR_INVALID_AEQ_ID";
	हाल IAVF_ERR_INVALID_SIZE:
		वापस "IAVF_ERR_INVALID_SIZE";
	हाल IAVF_ERR_INVALID_ARP_INDEX:
		वापस "IAVF_ERR_INVALID_ARP_INDEX";
	हाल IAVF_ERR_INVALID_FPM_FUNC_ID:
		वापस "IAVF_ERR_INVALID_FPM_FUNC_ID";
	हाल IAVF_ERR_QP_INVALID_MSG_SIZE:
		वापस "IAVF_ERR_QP_INVALID_MSG_SIZE";
	हाल IAVF_ERR_QP_TOOMANY_WRS_POSTED:
		वापस "IAVF_ERR_QP_TOOMANY_WRS_POSTED";
	हाल IAVF_ERR_INVALID_FRAG_COUNT:
		वापस "IAVF_ERR_INVALID_FRAG_COUNT";
	हाल IAVF_ERR_QUEUE_EMPTY:
		वापस "IAVF_ERR_QUEUE_EMPTY";
	हाल IAVF_ERR_INVALID_ALIGNMENT:
		वापस "IAVF_ERR_INVALID_ALIGNMENT";
	हाल IAVF_ERR_FLUSHED_QUEUE:
		वापस "IAVF_ERR_FLUSHED_QUEUE";
	हाल IAVF_ERR_INVALID_PUSH_PAGE_INDEX:
		वापस "IAVF_ERR_INVALID_PUSH_PAGE_INDEX";
	हाल IAVF_ERR_INVALID_IMM_DATA_SIZE:
		वापस "IAVF_ERR_INVALID_IMM_DATA_SIZE";
	हाल IAVF_ERR_TIMEOUT:
		वापस "IAVF_ERR_TIMEOUT";
	हाल IAVF_ERR_OPCODE_MISMATCH:
		वापस "IAVF_ERR_OPCODE_MISMATCH";
	हाल IAVF_ERR_CQP_COMPL_ERROR:
		वापस "IAVF_ERR_CQP_COMPL_ERROR";
	हाल IAVF_ERR_INVALID_VF_ID:
		वापस "IAVF_ERR_INVALID_VF_ID";
	हाल IAVF_ERR_INVALID_HMCFN_ID:
		वापस "IAVF_ERR_INVALID_HMCFN_ID";
	हाल IAVF_ERR_BACKING_PAGE_ERROR:
		वापस "IAVF_ERR_BACKING_PAGE_ERROR";
	हाल IAVF_ERR_NO_PBLCHUNKS_AVAILABLE:
		वापस "IAVF_ERR_NO_PBLCHUNKS_AVAILABLE";
	हाल IAVF_ERR_INVALID_PBLE_INDEX:
		वापस "IAVF_ERR_INVALID_PBLE_INDEX";
	हाल IAVF_ERR_INVALID_SD_INDEX:
		वापस "IAVF_ERR_INVALID_SD_INDEX";
	हाल IAVF_ERR_INVALID_PAGE_DESC_INDEX:
		वापस "IAVF_ERR_INVALID_PAGE_DESC_INDEX";
	हाल IAVF_ERR_INVALID_SD_TYPE:
		वापस "IAVF_ERR_INVALID_SD_TYPE";
	हाल IAVF_ERR_MEMCPY_FAILED:
		वापस "IAVF_ERR_MEMCPY_FAILED";
	हाल IAVF_ERR_INVALID_HMC_OBJ_INDEX:
		वापस "IAVF_ERR_INVALID_HMC_OBJ_INDEX";
	हाल IAVF_ERR_INVALID_HMC_OBJ_COUNT:
		वापस "IAVF_ERR_INVALID_HMC_OBJ_COUNT";
	हाल IAVF_ERR_INVALID_SRQ_ARM_LIMIT:
		वापस "IAVF_ERR_INVALID_SRQ_ARM_LIMIT";
	हाल IAVF_ERR_SRQ_ENABLED:
		वापस "IAVF_ERR_SRQ_ENABLED";
	हाल IAVF_ERR_ADMIN_QUEUE_ERROR:
		वापस "IAVF_ERR_ADMIN_QUEUE_ERROR";
	हाल IAVF_ERR_ADMIN_QUEUE_TIMEOUT:
		वापस "IAVF_ERR_ADMIN_QUEUE_TIMEOUT";
	हाल IAVF_ERR_BUF_TOO_SHORT:
		वापस "IAVF_ERR_BUF_TOO_SHORT";
	हाल IAVF_ERR_ADMIN_QUEUE_FULL:
		वापस "IAVF_ERR_ADMIN_QUEUE_FULL";
	हाल IAVF_ERR_ADMIN_QUEUE_NO_WORK:
		वापस "IAVF_ERR_ADMIN_QUEUE_NO_WORK";
	हाल IAVF_ERR_BAD_IWARP_CQE:
		वापस "IAVF_ERR_BAD_IWARP_CQE";
	हाल IAVF_ERR_NVM_BLANK_MODE:
		वापस "IAVF_ERR_NVM_BLANK_MODE";
	हाल IAVF_ERR_NOT_IMPLEMENTED:
		वापस "IAVF_ERR_NOT_IMPLEMENTED";
	हाल IAVF_ERR_PE_DOORBELL_NOT_ENABLED:
		वापस "IAVF_ERR_PE_DOORBELL_NOT_ENABLED";
	हाल IAVF_ERR_DIAG_TEST_FAILED:
		वापस "IAVF_ERR_DIAG_TEST_FAILED";
	हाल IAVF_ERR_NOT_READY:
		वापस "IAVF_ERR_NOT_READY";
	हाल IAVF_NOT_SUPPORTED:
		वापस "IAVF_NOT_SUPPORTED";
	हाल IAVF_ERR_FIRMWARE_API_VERSION:
		वापस "IAVF_ERR_FIRMWARE_API_VERSION";
	हाल IAVF_ERR_ADMIN_QUEUE_CRITICAL_ERROR:
		वापस "IAVF_ERR_ADMIN_QUEUE_CRITICAL_ERROR";
	पूर्ण

	snम_लिखो(hw->err_str, माप(hw->err_str), "%d", stat_err);
	वापस hw->err_str;
पूर्ण

/**
 * iavf_debug_aq
 * @hw: debug mask related to admin queue
 * @mask: debug mask
 * @desc: poपूर्णांकer to admin queue descriptor
 * @buffer: poपूर्णांकer to command buffer
 * @buf_len: max length of buffer
 *
 * Dumps debug log about adminq command with descriptor contents.
 **/
व्योम iavf_debug_aq(काष्ठा iavf_hw *hw, क्रमागत iavf_debug_mask mask, व्योम *desc,
		   व्योम *buffer, u16 buf_len)
अणु
	काष्ठा iavf_aq_desc *aq_desc = (काष्ठा iavf_aq_desc *)desc;
	u8 *buf = (u8 *)buffer;

	अगर ((!(mask & hw->debug_mask)) || !desc)
		वापस;

	iavf_debug(hw, mask,
		   "AQ CMD: opcode 0x%04X, flags 0x%04X, datalen 0x%04X, retval 0x%04X\n",
		   le16_to_cpu(aq_desc->opcode),
		   le16_to_cpu(aq_desc->flags),
		   le16_to_cpu(aq_desc->datalen),
		   le16_to_cpu(aq_desc->retval));
	iavf_debug(hw, mask, "\tcookie (h,l) 0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->cookie_high),
		   le32_to_cpu(aq_desc->cookie_low));
	iavf_debug(hw, mask, "\tparam (0,1)  0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.पूर्णांकernal.param0),
		   le32_to_cpu(aq_desc->params.पूर्णांकernal.param1));
	iavf_debug(hw, mask, "\taddr (h,l)   0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.बाह्यal.addr_high),
		   le32_to_cpu(aq_desc->params.बाह्यal.addr_low));

	अगर (buffer && aq_desc->datalen) अणु
		u16 len = le16_to_cpu(aq_desc->datalen);

		iavf_debug(hw, mask, "AQ CMD Buffer:\n");
		अगर (buf_len < len)
			len = buf_len;
		/* ग_लिखो the full 16-byte chunks */
		अगर (hw->debug_mask & mask) अणु
			अक्षर prefix[27];

			snम_लिखो(prefix, माप(prefix),
				 "iavf %02x:%02x.%x: \t0x",
				 hw->bus.bus_id,
				 hw->bus.device,
				 hw->bus.func);

			prपूर्णांक_hex_dump(KERN_INFO, prefix, DUMP_PREFIX_OFFSET,
				       16, 1, buf, len, false);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * iavf_check_asq_alive
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Returns true अगर Queue is enabled अन्यथा false.
 **/
bool iavf_check_asq_alive(काष्ठा iavf_hw *hw)
अणु
	अगर (hw->aq.asq.len)
		वापस !!(rd32(hw, hw->aq.asq.len) &
			  IAVF_VF_ATQLEN1_ATQENABLE_MASK);
	अन्यथा
		वापस false;
पूर्ण

/**
 * iavf_aq_queue_shutकरोwn
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @unloading: is the driver unloading itself
 *
 * Tell the Firmware that we're shutting करोwn the AdminQ and whether
 * or not the driver is unloading as well.
 **/
क्रमागत iavf_status iavf_aq_queue_shutकरोwn(काष्ठा iavf_hw *hw, bool unloading)
अणु
	काष्ठा iavf_aq_desc desc;
	काष्ठा iavf_aqc_queue_shutकरोwn *cmd =
		(काष्ठा iavf_aqc_queue_shutकरोwn *)&desc.params.raw;
	क्रमागत iavf_status status;

	iavf_fill_शेष_direct_cmd_desc(&desc, iavf_aqc_opc_queue_shutकरोwn);

	अगर (unloading)
		cmd->driver_unloading = cpu_to_le32(IAVF_AQ_DRIVER_UNLOADING);
	status = iavf_asq_send_command(hw, &desc, शून्य, 0, शून्य);

	वापस status;
पूर्ण

/**
 * iavf_aq_get_set_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_id: vsi fw index
 * @pf_lut: क्रम PF table set true, क्रम VSI table set false
 * @lut: poपूर्णांकer to the lut buffer provided by the caller
 * @lut_size: size of the lut buffer
 * @set: set true to set the table, false to get the table
 *
 * Internal function to get or set RSS look up table
 **/
अटल क्रमागत iavf_status iavf_aq_get_set_rss_lut(काष्ठा iavf_hw *hw,
						u16 vsi_id, bool pf_lut,
						u8 *lut, u16 lut_size,
						bool set)
अणु
	क्रमागत iavf_status status;
	काष्ठा iavf_aq_desc desc;
	काष्ठा iavf_aqc_get_set_rss_lut *cmd_resp =
		   (काष्ठा iavf_aqc_get_set_rss_lut *)&desc.params.raw;

	अगर (set)
		iavf_fill_शेष_direct_cmd_desc(&desc,
						  iavf_aqc_opc_set_rss_lut);
	अन्यथा
		iavf_fill_शेष_direct_cmd_desc(&desc,
						  iavf_aqc_opc_get_rss_lut);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_RD);

	cmd_resp->vsi_id =
			cpu_to_le16((u16)((vsi_id <<
					  IAVF_AQC_SET_RSS_LUT_VSI_ID_SHIFT) &
					  IAVF_AQC_SET_RSS_LUT_VSI_ID_MASK));
	cmd_resp->vsi_id |= cpu_to_le16((u16)IAVF_AQC_SET_RSS_LUT_VSI_VALID);

	अगर (pf_lut)
		cmd_resp->flags |= cpu_to_le16((u16)
					((IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_PF <<
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT) &
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_MASK));
	अन्यथा
		cmd_resp->flags |= cpu_to_le16((u16)
					((IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_VSI <<
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT) &
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_MASK));

	status = iavf_asq_send_command(hw, &desc, lut, lut_size, शून्य);

	वापस status;
पूर्ण

/**
 * iavf_aq_get_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_id: vsi fw index
 * @pf_lut: क्रम PF table set true, क्रम VSI table set false
 * @lut: poपूर्णांकer to the lut buffer provided by the caller
 * @lut_size: size of the lut buffer
 *
 * get the RSS lookup table, PF or VSI type
 **/
क्रमागत iavf_status iavf_aq_get_rss_lut(काष्ठा iavf_hw *hw, u16 vsi_id,
				     bool pf_lut, u8 *lut, u16 lut_size)
अणु
	वापस iavf_aq_get_set_rss_lut(hw, vsi_id, pf_lut, lut, lut_size,
				       false);
पूर्ण

/**
 * iavf_aq_set_rss_lut
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_id: vsi fw index
 * @pf_lut: क्रम PF table set true, क्रम VSI table set false
 * @lut: poपूर्णांकer to the lut buffer provided by the caller
 * @lut_size: size of the lut buffer
 *
 * set the RSS lookup table, PF or VSI type
 **/
क्रमागत iavf_status iavf_aq_set_rss_lut(काष्ठा iavf_hw *hw, u16 vsi_id,
				     bool pf_lut, u8 *lut, u16 lut_size)
अणु
	वापस iavf_aq_get_set_rss_lut(hw, vsi_id, pf_lut, lut, lut_size, true);
पूर्ण

/**
 * iavf_aq_get_set_rss_key
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_id: vsi fw index
 * @key: poपूर्णांकer to key info काष्ठा
 * @set: set true to set the key, false to get the key
 *
 * get the RSS key per VSI
 **/
अटल क्रमागत
iavf_status iavf_aq_get_set_rss_key(काष्ठा iavf_hw *hw, u16 vsi_id,
				    काष्ठा iavf_aqc_get_set_rss_key_data *key,
				    bool set)
अणु
	क्रमागत iavf_status status;
	काष्ठा iavf_aq_desc desc;
	काष्ठा iavf_aqc_get_set_rss_key *cmd_resp =
			(काष्ठा iavf_aqc_get_set_rss_key *)&desc.params.raw;
	u16 key_size = माप(काष्ठा iavf_aqc_get_set_rss_key_data);

	अगर (set)
		iavf_fill_शेष_direct_cmd_desc(&desc,
						  iavf_aqc_opc_set_rss_key);
	अन्यथा
		iavf_fill_शेष_direct_cmd_desc(&desc,
						  iavf_aqc_opc_get_rss_key);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_RD);

	cmd_resp->vsi_id =
			cpu_to_le16((u16)((vsi_id <<
					  IAVF_AQC_SET_RSS_KEY_VSI_ID_SHIFT) &
					  IAVF_AQC_SET_RSS_KEY_VSI_ID_MASK));
	cmd_resp->vsi_id |= cpu_to_le16((u16)IAVF_AQC_SET_RSS_KEY_VSI_VALID);

	status = iavf_asq_send_command(hw, &desc, key, key_size, शून्य);

	वापस status;
पूर्ण

/**
 * iavf_aq_get_rss_key
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_id: vsi fw index
 * @key: poपूर्णांकer to key info काष्ठा
 *
 **/
क्रमागत iavf_status iavf_aq_get_rss_key(काष्ठा iavf_hw *hw, u16 vsi_id,
				     काष्ठा iavf_aqc_get_set_rss_key_data *key)
अणु
	वापस iavf_aq_get_set_rss_key(hw, vsi_id, key, false);
पूर्ण

/**
 * iavf_aq_set_rss_key
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @vsi_id: vsi fw index
 * @key: poपूर्णांकer to key info काष्ठा
 *
 * set the RSS key per VSI
 **/
क्रमागत iavf_status iavf_aq_set_rss_key(काष्ठा iavf_hw *hw, u16 vsi_id,
				     काष्ठा iavf_aqc_get_set_rss_key_data *key)
अणु
	वापस iavf_aq_get_set_rss_key(hw, vsi_id, key, true);
पूर्ण

/* The iavf_ptype_lookup table is used to convert from the 8-bit ptype in the
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
 * IF NOT iavf_ptype_lookup[ptype].known
 * THEN
 *      Packet is unknown
 * ELSE IF iavf_ptype_lookup[ptype].outer_ip == IAVF_RX_PTYPE_OUTER_IP
 *      Use the rest of the fields to look at the tunnels, inner protocols, etc
 * ELSE
 *      Use the क्रमागत iavf_rx_l2_ptype to decode the packet type
 * ENDIF
 */

/* macro to make the table lines लघु */
#घोषणा IAVF_PTT(PTYPE, OUTER_IP, OUTER_IP_VER, OUTER_FRAG, T, TE, TEF, I, PL)\
	अणु	PTYPE, \
		1, \
		IAVF_RX_PTYPE_OUTER_##OUTER_IP, \
		IAVF_RX_PTYPE_OUTER_##OUTER_IP_VER, \
		IAVF_RX_PTYPE_##OUTER_FRAG, \
		IAVF_RX_PTYPE_TUNNEL_##T, \
		IAVF_RX_PTYPE_TUNNEL_END_##TE, \
		IAVF_RX_PTYPE_##TEF, \
		IAVF_RX_PTYPE_INNER_PROT_##I, \
		IAVF_RX_PTYPE_PAYLOAD_LAYER_##PL पूर्ण

#घोषणा IAVF_PTT_UNUSED_ENTRY(PTYPE) \
		अणु PTYPE, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण

/* लघुer macros makes the table fit but are terse */
#घोषणा IAVF_RX_PTYPE_NOF		IAVF_RX_PTYPE_NOT_FRAG
#घोषणा IAVF_RX_PTYPE_FRG		IAVF_RX_PTYPE_FRAG
#घोषणा IAVF_RX_PTYPE_INNER_PROT_TS	IAVF_RX_PTYPE_INNER_PROT_TIMESYNC

/* Lookup table mapping the HW PTYPE to the bit field क्रम decoding */
काष्ठा iavf_rx_ptype_decoded iavf_ptype_lookup[] = अणु
	/* L2 Packet types */
	IAVF_PTT_UNUSED_ENTRY(0),
	IAVF_PTT(1,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT(2,  L2, NONE, NOF, NONE, NONE, NOF, TS,   PAY2),
	IAVF_PTT(3,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT_UNUSED_ENTRY(4),
	IAVF_PTT_UNUSED_ENTRY(5),
	IAVF_PTT(6,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT(7,  L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT_UNUSED_ENTRY(8),
	IAVF_PTT_UNUSED_ENTRY(9),
	IAVF_PTT(10, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY2),
	IAVF_PTT(11, L2, NONE, NOF, NONE, NONE, NOF, NONE, NONE),
	IAVF_PTT(12, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(13, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(14, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(15, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(16, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(17, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(18, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(19, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(20, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(21, L2, NONE, NOF, NONE, NONE, NOF, NONE, PAY3),

	/* Non Tunneled IPv4 */
	IAVF_PTT(22, IP, IPV4, FRG, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(23, IP, IPV4, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(24, IP, IPV4, NOF, NONE, NONE, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(25),
	IAVF_PTT(26, IP, IPV4, NOF, NONE, NONE, NOF, TCP,  PAY4),
	IAVF_PTT(27, IP, IPV4, NOF, NONE, NONE, NOF, SCTP, PAY4),
	IAVF_PTT(28, IP, IPV4, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv4 --> IPv4 */
	IAVF_PTT(29, IP, IPV4, NOF, IP_IP, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(30, IP, IPV4, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(31, IP, IPV4, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(32),
	IAVF_PTT(33, IP, IPV4, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(34, IP, IPV4, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(35, IP, IPV4, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> IPv6 */
	IAVF_PTT(36, IP, IPV4, NOF, IP_IP, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(37, IP, IPV4, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(38, IP, IPV4, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(39),
	IAVF_PTT(40, IP, IPV4, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(41, IP, IPV4, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(42, IP, IPV4, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT */
	IAVF_PTT(43, IP, IPV4, NOF, IP_GRENAT, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GRE/NAT --> IPv4 */
	IAVF_PTT(44, IP, IPV4, NOF, IP_GRENAT, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(45, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(46, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(47),
	IAVF_PTT(48, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(49, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(50, IP, IPV4, NOF, IP_GRENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> IPv6 */
	IAVF_PTT(51, IP, IPV4, NOF, IP_GRENAT, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(52, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(53, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(54),
	IAVF_PTT(55, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(56, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(57, IP, IPV4, NOF, IP_GRENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> MAC */
	IAVF_PTT(58, IP, IPV4, NOF, IP_GRENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv4 --> GRE/NAT --> MAC --> IPv4 */
	IAVF_PTT(59, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(60, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(61, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(62),
	IAVF_PTT(63, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(64, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(65, IP, IPV4, NOF, IP_GRENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT -> MAC --> IPv6 */
	IAVF_PTT(66, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(67, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(68, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(69),
	IAVF_PTT(70, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(71, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(72, IP, IPV4, NOF, IP_GRENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv4 --> GRE/NAT --> MAC/VLAN */
	IAVF_PTT(73, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, NONE, NOF, NONE, PAY3),

	/* IPv4 ---> GRE/NAT -> MAC/VLAN --> IPv4 */
	IAVF_PTT(74, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(75, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(76, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(77),
	IAVF_PTT(78, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(79, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(80, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, ICMP, PAY4),

	/* IPv4 -> GRE/NAT -> MAC/VLAN --> IPv6 */
	IAVF_PTT(81, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(82, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(83, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(84),
	IAVF_PTT(85, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(86, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(87, IP, IPV4, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, ICMP, PAY4),

	/* Non Tunneled IPv6 */
	IAVF_PTT(88, IP, IPV6, FRG, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(89, IP, IPV6, NOF, NONE, NONE, NOF, NONE, PAY3),
	IAVF_PTT(90, IP, IPV6, NOF, NONE, NONE, NOF, UDP,  PAY3),
	IAVF_PTT_UNUSED_ENTRY(91),
	IAVF_PTT(92, IP, IPV6, NOF, NONE, NONE, NOF, TCP,  PAY4),
	IAVF_PTT(93, IP, IPV6, NOF, NONE, NONE, NOF, SCTP, PAY4),
	IAVF_PTT(94, IP, IPV6, NOF, NONE, NONE, NOF, ICMP, PAY4),

	/* IPv6 --> IPv4 */
	IAVF_PTT(95,  IP, IPV6, NOF, IP_IP, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(96,  IP, IPV6, NOF, IP_IP, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(97,  IP, IPV6, NOF, IP_IP, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(98),
	IAVF_PTT(99,  IP, IPV6, NOF, IP_IP, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(100, IP, IPV6, NOF, IP_IP, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(101, IP, IPV6, NOF, IP_IP, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> IPv6 */
	IAVF_PTT(102, IP, IPV6, NOF, IP_IP, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(103, IP, IPV6, NOF, IP_IP, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(104, IP, IPV6, NOF, IP_IP, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(105),
	IAVF_PTT(106, IP, IPV6, NOF, IP_IP, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(107, IP, IPV6, NOF, IP_IP, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(108, IP, IPV6, NOF, IP_IP, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT */
	IAVF_PTT(109, IP, IPV6, NOF, IP_GRENAT, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> IPv4 */
	IAVF_PTT(110, IP, IPV6, NOF, IP_GRENAT, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(111, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(112, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(113),
	IAVF_PTT(114, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(115, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(116, IP, IPV6, NOF, IP_GRENAT, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> IPv6 */
	IAVF_PTT(117, IP, IPV6, NOF, IP_GRENAT, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(118, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(119, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(120),
	IAVF_PTT(121, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(122, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(123, IP, IPV6, NOF, IP_GRENAT, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC */
	IAVF_PTT(124, IP, IPV6, NOF, IP_GRENAT_MAC, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> MAC -> IPv4 */
	IAVF_PTT(125, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(126, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(127, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(128),
	IAVF_PTT(129, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(130, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(131, IP, IPV6, NOF, IP_GRENAT_MAC, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC -> IPv6 */
	IAVF_PTT(132, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(133, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(134, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(135),
	IAVF_PTT(136, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(137, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(138, IP, IPV6, NOF, IP_GRENAT_MAC, IPV6, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC/VLAN */
	IAVF_PTT(139, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, NONE, NOF, NONE, PAY3),

	/* IPv6 --> GRE/NAT -> MAC/VLAN --> IPv4 */
	IAVF_PTT(140, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, FRG, NONE, PAY3),
	IAVF_PTT(141, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, NONE, PAY3),
	IAVF_PTT(142, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(143),
	IAVF_PTT(144, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, TCP,  PAY4),
	IAVF_PTT(145, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, SCTP, PAY4),
	IAVF_PTT(146, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV4, NOF, ICMP, PAY4),

	/* IPv6 --> GRE/NAT -> MAC/VLAN --> IPv6 */
	IAVF_PTT(147, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, FRG, NONE, PAY3),
	IAVF_PTT(148, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, NONE, PAY3),
	IAVF_PTT(149, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, UDP,  PAY4),
	IAVF_PTT_UNUSED_ENTRY(150),
	IAVF_PTT(151, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, TCP,  PAY4),
	IAVF_PTT(152, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, SCTP, PAY4),
	IAVF_PTT(153, IP, IPV6, NOF, IP_GRENAT_MAC_VLAN, IPV6, NOF, ICMP, PAY4),

	/* unused entries */
	IAVF_PTT_UNUSED_ENTRY(154),
	IAVF_PTT_UNUSED_ENTRY(155),
	IAVF_PTT_UNUSED_ENTRY(156),
	IAVF_PTT_UNUSED_ENTRY(157),
	IAVF_PTT_UNUSED_ENTRY(158),
	IAVF_PTT_UNUSED_ENTRY(159),

	IAVF_PTT_UNUSED_ENTRY(160),
	IAVF_PTT_UNUSED_ENTRY(161),
	IAVF_PTT_UNUSED_ENTRY(162),
	IAVF_PTT_UNUSED_ENTRY(163),
	IAVF_PTT_UNUSED_ENTRY(164),
	IAVF_PTT_UNUSED_ENTRY(165),
	IAVF_PTT_UNUSED_ENTRY(166),
	IAVF_PTT_UNUSED_ENTRY(167),
	IAVF_PTT_UNUSED_ENTRY(168),
	IAVF_PTT_UNUSED_ENTRY(169),

	IAVF_PTT_UNUSED_ENTRY(170),
	IAVF_PTT_UNUSED_ENTRY(171),
	IAVF_PTT_UNUSED_ENTRY(172),
	IAVF_PTT_UNUSED_ENTRY(173),
	IAVF_PTT_UNUSED_ENTRY(174),
	IAVF_PTT_UNUSED_ENTRY(175),
	IAVF_PTT_UNUSED_ENTRY(176),
	IAVF_PTT_UNUSED_ENTRY(177),
	IAVF_PTT_UNUSED_ENTRY(178),
	IAVF_PTT_UNUSED_ENTRY(179),

	IAVF_PTT_UNUSED_ENTRY(180),
	IAVF_PTT_UNUSED_ENTRY(181),
	IAVF_PTT_UNUSED_ENTRY(182),
	IAVF_PTT_UNUSED_ENTRY(183),
	IAVF_PTT_UNUSED_ENTRY(184),
	IAVF_PTT_UNUSED_ENTRY(185),
	IAVF_PTT_UNUSED_ENTRY(186),
	IAVF_PTT_UNUSED_ENTRY(187),
	IAVF_PTT_UNUSED_ENTRY(188),
	IAVF_PTT_UNUSED_ENTRY(189),

	IAVF_PTT_UNUSED_ENTRY(190),
	IAVF_PTT_UNUSED_ENTRY(191),
	IAVF_PTT_UNUSED_ENTRY(192),
	IAVF_PTT_UNUSED_ENTRY(193),
	IAVF_PTT_UNUSED_ENTRY(194),
	IAVF_PTT_UNUSED_ENTRY(195),
	IAVF_PTT_UNUSED_ENTRY(196),
	IAVF_PTT_UNUSED_ENTRY(197),
	IAVF_PTT_UNUSED_ENTRY(198),
	IAVF_PTT_UNUSED_ENTRY(199),

	IAVF_PTT_UNUSED_ENTRY(200),
	IAVF_PTT_UNUSED_ENTRY(201),
	IAVF_PTT_UNUSED_ENTRY(202),
	IAVF_PTT_UNUSED_ENTRY(203),
	IAVF_PTT_UNUSED_ENTRY(204),
	IAVF_PTT_UNUSED_ENTRY(205),
	IAVF_PTT_UNUSED_ENTRY(206),
	IAVF_PTT_UNUSED_ENTRY(207),
	IAVF_PTT_UNUSED_ENTRY(208),
	IAVF_PTT_UNUSED_ENTRY(209),

	IAVF_PTT_UNUSED_ENTRY(210),
	IAVF_PTT_UNUSED_ENTRY(211),
	IAVF_PTT_UNUSED_ENTRY(212),
	IAVF_PTT_UNUSED_ENTRY(213),
	IAVF_PTT_UNUSED_ENTRY(214),
	IAVF_PTT_UNUSED_ENTRY(215),
	IAVF_PTT_UNUSED_ENTRY(216),
	IAVF_PTT_UNUSED_ENTRY(217),
	IAVF_PTT_UNUSED_ENTRY(218),
	IAVF_PTT_UNUSED_ENTRY(219),

	IAVF_PTT_UNUSED_ENTRY(220),
	IAVF_PTT_UNUSED_ENTRY(221),
	IAVF_PTT_UNUSED_ENTRY(222),
	IAVF_PTT_UNUSED_ENTRY(223),
	IAVF_PTT_UNUSED_ENTRY(224),
	IAVF_PTT_UNUSED_ENTRY(225),
	IAVF_PTT_UNUSED_ENTRY(226),
	IAVF_PTT_UNUSED_ENTRY(227),
	IAVF_PTT_UNUSED_ENTRY(228),
	IAVF_PTT_UNUSED_ENTRY(229),

	IAVF_PTT_UNUSED_ENTRY(230),
	IAVF_PTT_UNUSED_ENTRY(231),
	IAVF_PTT_UNUSED_ENTRY(232),
	IAVF_PTT_UNUSED_ENTRY(233),
	IAVF_PTT_UNUSED_ENTRY(234),
	IAVF_PTT_UNUSED_ENTRY(235),
	IAVF_PTT_UNUSED_ENTRY(236),
	IAVF_PTT_UNUSED_ENTRY(237),
	IAVF_PTT_UNUSED_ENTRY(238),
	IAVF_PTT_UNUSED_ENTRY(239),

	IAVF_PTT_UNUSED_ENTRY(240),
	IAVF_PTT_UNUSED_ENTRY(241),
	IAVF_PTT_UNUSED_ENTRY(242),
	IAVF_PTT_UNUSED_ENTRY(243),
	IAVF_PTT_UNUSED_ENTRY(244),
	IAVF_PTT_UNUSED_ENTRY(245),
	IAVF_PTT_UNUSED_ENTRY(246),
	IAVF_PTT_UNUSED_ENTRY(247),
	IAVF_PTT_UNUSED_ENTRY(248),
	IAVF_PTT_UNUSED_ENTRY(249),

	IAVF_PTT_UNUSED_ENTRY(250),
	IAVF_PTT_UNUSED_ENTRY(251),
	IAVF_PTT_UNUSED_ENTRY(252),
	IAVF_PTT_UNUSED_ENTRY(253),
	IAVF_PTT_UNUSED_ENTRY(254),
	IAVF_PTT_UNUSED_ENTRY(255)
पूर्ण;

/**
 * iavf_aq_send_msg_to_pf
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @v_opcode: opcodes क्रम VF-PF communication
 * @v_retval: वापस error code
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 * @cmd_details: poपूर्णांकer to command details
 *
 * Send message to PF driver using admin queue. By शेष, this message
 * is sent asynchronously, i.e. iavf_asq_send_command() करोes not रुको क्रम
 * completion beक्रमe वापसing.
 **/
क्रमागत iavf_status iavf_aq_send_msg_to_pf(काष्ठा iavf_hw *hw,
					क्रमागत virtchnl_ops v_opcode,
					क्रमागत iavf_status v_retval,
					u8 *msg, u16 msglen,
					काष्ठा iavf_asq_cmd_details *cmd_details)
अणु
	काष्ठा iavf_asq_cmd_details details;
	काष्ठा iavf_aq_desc desc;
	क्रमागत iavf_status status;

	iavf_fill_शेष_direct_cmd_desc(&desc, iavf_aqc_opc_send_msg_to_pf);
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_SI);
	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);
	अगर (msglen) अणु
		desc.flags |= cpu_to_le16((u16)(IAVF_AQ_FLAG_BUF
						| IAVF_AQ_FLAG_RD));
		अगर (msglen > IAVF_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_LB);
		desc.datalen = cpu_to_le16(msglen);
	पूर्ण
	अगर (!cmd_details) अणु
		स_रखो(&details, 0, माप(details));
		details.async = true;
		cmd_details = &details;
	पूर्ण
	status = iavf_asq_send_command(hw, &desc, msg, msglen, cmd_details);
	वापस status;
पूर्ण

/**
 * iavf_vf_parse_hw_config
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @msg: poपूर्णांकer to the भव channel VF resource काष्ठाure
 *
 * Given a VF resource message from the PF, populate the hw काष्ठा
 * with appropriate inक्रमmation.
 **/
व्योम iavf_vf_parse_hw_config(काष्ठा iavf_hw *hw,
			     काष्ठा virtchnl_vf_resource *msg)
अणु
	काष्ठा virtchnl_vsi_resource *vsi_res;
	पूर्णांक i;

	vsi_res = &msg->vsi_res[0];

	hw->dev_caps.num_vsis = msg->num_vsis;
	hw->dev_caps.num_rx_qp = msg->num_queue_pairs;
	hw->dev_caps.num_tx_qp = msg->num_queue_pairs;
	hw->dev_caps.num_msix_vectors_vf = msg->max_vectors;
	hw->dev_caps.dcb = msg->vf_cap_flags &
			   VIRTCHNL_VF_OFFLOAD_L2;
	hw->dev_caps.fcoe = 0;
	क्रम (i = 0; i < msg->num_vsis; i++) अणु
		अगर (vsi_res->vsi_type == VIRTCHNL_VSI_SRIOV) अणु
			ether_addr_copy(hw->mac.perm_addr,
					vsi_res->शेष_mac_addr);
			ether_addr_copy(hw->mac.addr,
					vsi_res->शेष_mac_addr);
		पूर्ण
		vsi_res++;
	पूर्ण
पूर्ण

/**
 * iavf_vf_reset
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Send a VF_RESET message to the PF. Does not रुको क्रम response from PF
 * as none will be क्रमthcoming. Immediately after calling this function,
 * the admin queue should be shut करोwn and (optionally) reinitialized.
 **/
क्रमागत iavf_status iavf_vf_reset(काष्ठा iavf_hw *hw)
अणु
	वापस iavf_aq_send_msg_to_pf(hw, VIRTCHNL_OP_RESET_VF,
				      0, शून्य, 0, शून्य);
पूर्ण
