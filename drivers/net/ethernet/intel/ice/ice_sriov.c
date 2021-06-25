<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice_common.h"
#समावेश "ice_sriov.h"

/**
 * ice_aq_send_msg_to_vf
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vfid: VF ID to send msg
 * @v_opcode: opcodes क्रम VF-PF communication
 * @v_retval: वापस error code
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 * @cd: poपूर्णांकer to command details
 *
 * Send message to VF driver (0x0802) using mailbox
 * queue and asynchronously sending message via
 * ice_sq_send_cmd() function
 */
क्रमागत ice_status
ice_aq_send_msg_to_vf(काष्ठा ice_hw *hw, u16 vfid, u32 v_opcode, u32 v_retval,
		      u8 *msg, u16 msglen, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_pf_vf_msg *cmd;
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_mbx_opc_send_msg_to_vf);

	cmd = &desc.params.virt;
	cmd->id = cpu_to_le32(vfid);

	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);

	अगर (msglen)
		desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	वापस ice_sq_send_cmd(hw, &hw->mailboxq, &desc, msg, msglen, cd);
पूर्ण

/**
 * ice_conv_link_speed_to_virtchnl
 * @adv_link_support: determines the क्रमmat of the वापसed link speed
 * @link_speed: variable containing the link_speed to be converted
 *
 * Convert link speed supported by HW to link speed supported by virtchnl.
 * If adv_link_support is true, then वापस link speed in Mbps. Else वापस
 * link speed as a VIRTCHNL_LINK_SPEED_* casted to a u32. Note that the caller
 * needs to cast back to an क्रमागत virtchnl_link_speed in the हाल where
 * adv_link_support is false, but when adv_link_support is true the caller can
 * expect the speed in Mbps.
 */
u32 ice_conv_link_speed_to_virtchnl(bool adv_link_support, u16 link_speed)
अणु
	u32 speed;

	अगर (adv_link_support)
		चयन (link_speed) अणु
		हाल ICE_AQ_LINK_SPEED_10MB:
			speed = ICE_LINK_SPEED_10MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_100MB:
			speed = ICE_LINK_SPEED_100MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_1000MB:
			speed = ICE_LINK_SPEED_1000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_2500MB:
			speed = ICE_LINK_SPEED_2500MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_5GB:
			speed = ICE_LINK_SPEED_5000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_10GB:
			speed = ICE_LINK_SPEED_10000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_20GB:
			speed = ICE_LINK_SPEED_20000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_25GB:
			speed = ICE_LINK_SPEED_25000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_40GB:
			speed = ICE_LINK_SPEED_40000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_50GB:
			speed = ICE_LINK_SPEED_50000MBPS;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_100GB:
			speed = ICE_LINK_SPEED_100000MBPS;
			अवरोध;
		शेष:
			speed = ICE_LINK_SPEED_UNKNOWN;
			अवरोध;
		पूर्ण
	अन्यथा
		/* Virtchnl speeds are not defined क्रम every speed supported in
		 * the hardware. To मुख्यtain compatibility with older AVF
		 * drivers, जबतक reporting the speed the new speed values are
		 * resolved to the बंदst known virtchnl speeds
		 */
		चयन (link_speed) अणु
		हाल ICE_AQ_LINK_SPEED_10MB:
		हाल ICE_AQ_LINK_SPEED_100MB:
			speed = (u32)VIRTCHNL_LINK_SPEED_100MB;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_1000MB:
		हाल ICE_AQ_LINK_SPEED_2500MB:
		हाल ICE_AQ_LINK_SPEED_5GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_1GB;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_10GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_10GB;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_20GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_20GB;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_25GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_25GB;
			अवरोध;
		हाल ICE_AQ_LINK_SPEED_40GB:
		हाल ICE_AQ_LINK_SPEED_50GB:
		हाल ICE_AQ_LINK_SPEED_100GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_40GB;
			अवरोध;
		शेष:
			speed = (u32)VIRTCHNL_LINK_SPEED_UNKNOWN;
			अवरोध;
		पूर्ण

	वापस speed;
पूर्ण

/* The mailbox overflow detection algorithm helps to check अगर there
 * is a possibility of a malicious VF transmitting too many MBX messages to the
 * PF.
 * 1. The mailbox snapshot काष्ठाure, ice_mbx_snapshot, is initialized during
 * driver initialization in ice_init_hw() using ice_mbx_init_snapshot().
 * The काष्ठा ice_mbx_snapshot helps to track and traverse a अटल winकरोw of
 * messages within the mailbox queue जबतक looking क्रम a malicious VF.
 *
 * 2. When the caller starts processing its mailbox queue in response to an
 * पूर्णांकerrupt, the काष्ठाure ice_mbx_snapshot is expected to be cleared beक्रमe
 * the algorithm can be run क्रम the first समय क्रम that पूर्णांकerrupt. This can be
 * करोne via ice_mbx_reset_snapshot().
 *
 * 3. For every message पढ़ो by the caller from the MBX Queue, the caller must
 * call the detection algorithm's entry function ice_mbx_vf_state_handler().
 * Beक्रमe every call to ice_mbx_vf_state_handler() the काष्ठा ice_mbx_data is
 * filled as it is required to be passed to the algorithm.
 *
 * 4. Every समय a message is पढ़ो from the MBX queue, a VFId is received which
 * is passed to the state handler. The boolean output is_malvf of the state
 * handler ice_mbx_vf_state_handler() serves as an indicator to the caller
 * whether this VF is malicious or not.
 *
 * 5. When a VF is identअगरied to be malicious, the caller can send a message
 * to the प्रणाली administrator. The caller can invoke ice_mbx_report_malvf()
 * to help determine अगर a malicious VF is to be reported or not. This function
 * requires the caller to मुख्यtain a global biपंचांगap to track all malicious VFs
 * and pass that to ice_mbx_report_malvf() aदीर्घ with the VFID which was identअगरied
 * to be malicious by ice_mbx_vf_state_handler().
 *
 * 6. The global biपंचांगap मुख्यtained by PF can be cleared completely अगर PF is in
 * reset or the bit corresponding to a VF can be cleared अगर that VF is in reset.
 * When a VF is shut करोwn and brought back up, we assume that the new VF
 * brought up is not malicious and hence report it अगर found malicious.
 *
 * 7. The function ice_mbx_reset_snapshot() is called to reset the inक्रमmation
 * in ice_mbx_snapshot क्रम every new mailbox पूर्णांकerrupt handled.
 *
 * 8. The memory allocated क्रम variables in ice_mbx_snapshot is de-allocated
 * when driver is unloaded.
 */
#घोषणा ICE_RQ_DATA_MASK(rq_data) ((rq_data) & PF_MBX_ARQH_ARQH_M)
/* Using the highest value क्रम an अचिन्हित 16-bit value 0xFFFF to indicate that
 * the max messages check must be ignored in the algorithm
 */
#घोषणा ICE_IGNORE_MAX_MSG_CNT	0xFFFF

/**
 * ice_mbx_traverse - Pass through mailbox snapshot
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @new_state: new algorithm state
 *
 * Traversing the mailbox अटल snapshot without checking
 * क्रम malicious VFs.
 */
अटल व्योम
ice_mbx_traverse(काष्ठा ice_hw *hw,
		 क्रमागत ice_mbx_snapshot_state *new_state)
अणु
	काष्ठा ice_mbx_snap_buffer_data *snap_buf;
	u32 num_iterations;

	snap_buf = &hw->mbx_snapshot.mbx_buf;

	/* As mailbox buffer is circular, applying a mask
	 * on the incremented iteration count.
	 */
	num_iterations = ICE_RQ_DATA_MASK(++snap_buf->num_iterations);

	/* Checking either of the below conditions to निकास snapshot traversal:
	 * Condition-1: If the number of iterations in the mailbox is equal to
	 * the mailbox head which would indicate that we have reached the end
	 * of the अटल snapshot.
	 * Condition-2: If the maximum messages serviced in the mailbox क्रम a
	 * given पूर्णांकerrupt is the highest possible value then there is no need
	 * to check अगर the number of messages processed is equal to it. If not
	 * check अगर the number of messages processed is greater than or equal
	 * to the maximum number of mailbox entries serviced in current work item.
	 */
	अगर (num_iterations == snap_buf->head ||
	    (snap_buf->max_num_msgs_mbx < ICE_IGNORE_MAX_MSG_CNT &&
	     ++snap_buf->num_msg_proc >= snap_buf->max_num_msgs_mbx))
		*new_state = ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT;
पूर्ण

/**
 * ice_mbx_detect_malvf - Detect malicious VF in snapshot
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vf_id: relative भव function ID
 * @new_state: new algorithm state
 * @is_malvf: boolean output to indicate अगर VF is malicious
 *
 * This function tracks the number of asynchronous messages
 * sent per VF and marks the VF as malicious अगर it exceeds
 * the permissible number of messages to send.
 */
अटल क्रमागत ice_status
ice_mbx_detect_malvf(काष्ठा ice_hw *hw, u16 vf_id,
		     क्रमागत ice_mbx_snapshot_state *new_state,
		     bool *is_malvf)
अणु
	काष्ठा ice_mbx_snapshot *snap = &hw->mbx_snapshot;

	अगर (vf_id >= snap->mbx_vf.vfcntr_len)
		वापस ICE_ERR_OUT_OF_RANGE;

	/* increment the message count in the VF array */
	snap->mbx_vf.vf_cntr[vf_id]++;

	अगर (snap->mbx_vf.vf_cntr[vf_id] >= ICE_ASYNC_VF_MSG_THRESHOLD)
		*is_malvf = true;

	/* जारी to iterate through the mailbox snapshot */
	ice_mbx_traverse(hw, new_state);

	वापस 0;
पूर्ण

/**
 * ice_mbx_reset_snapshot - Reset mailbox snapshot काष्ठाure
 * @snap: poपूर्णांकer to mailbox snapshot काष्ठाure in the ice_hw काष्ठा
 *
 * Reset the mailbox snapshot काष्ठाure and clear VF counter array.
 */
अटल व्योम ice_mbx_reset_snapshot(काष्ठा ice_mbx_snapshot *snap)
अणु
	u32 vfcntr_len;

	अगर (!snap || !snap->mbx_vf.vf_cntr)
		वापस;

	/* Clear VF counters. */
	vfcntr_len = snap->mbx_vf.vfcntr_len;
	अगर (vfcntr_len)
		स_रखो(snap->mbx_vf.vf_cntr, 0,
		       (vfcntr_len * माप(*snap->mbx_vf.vf_cntr)));

	/* Reset mailbox snapshot क्रम a new capture. */
	स_रखो(&snap->mbx_buf, 0, माप(snap->mbx_buf));
	snap->mbx_buf.state = ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT;
पूर्ण

/**
 * ice_mbx_vf_state_handler - Handle states of the overflow algorithm
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @mbx_data: poपूर्णांकer to काष्ठाure containing mailbox data
 * @vf_id: relative भव function (VF) ID
 * @is_malvf: boolean output to indicate अगर VF is malicious
 *
 * The function serves as an entry poपूर्णांक क्रम the malicious VF
 * detection algorithm by handling the dअगरferent states and state
 * transitions of the algorithm:
 * New snapshot: This state is entered when creating a new अटल
 * snapshot. The data from any previous mailbox snapshot is
 * cleared and a new capture of the mailbox head and tail is
 * logged. This will be the new अटल snapshot to detect
 * asynchronous messages sent by VFs. On capturing the snapshot
 * and depending on whether the number of pending messages in that
 * snapshot exceed the watermark value, the state machine enters
 * traverse or detect states.
 * Traverse: If pending message count is below watermark then iterate
 * through the snapshot without any action on VF.
 * Detect: If pending message count exceeds watermark traverse
 * the अटल snapshot and look क्रम a malicious VF.
 */
क्रमागत ice_status
ice_mbx_vf_state_handler(काष्ठा ice_hw *hw,
			 काष्ठा ice_mbx_data *mbx_data, u16 vf_id,
			 bool *is_malvf)
अणु
	काष्ठा ice_mbx_snapshot *snap = &hw->mbx_snapshot;
	काष्ठा ice_mbx_snap_buffer_data *snap_buf;
	काष्ठा ice_ctl_q_info *cq = &hw->mailboxq;
	क्रमागत ice_mbx_snapshot_state new_state;
	क्रमागत ice_status status = 0;

	अगर (!is_malvf || !mbx_data)
		वापस ICE_ERR_BAD_PTR;

	/* When entering the mailbox state machine assume that the VF
	 * is not malicious until detected.
	 */
	*is_malvf = false;

	 /* Checking अगर max messages allowed to be processed जबतक servicing current
	  * पूर्णांकerrupt is not less than the defined AVF message threshold.
	  */
	अगर (mbx_data->max_num_msgs_mbx <= ICE_ASYNC_VF_MSG_THRESHOLD)
		वापस ICE_ERR_INVAL_SIZE;

	/* The watermark value should not be lesser than the threshold limit
	 * set क्रम the number of asynchronous messages a VF can send to mailbox
	 * nor should it be greater than the maximum number of messages in the
	 * mailbox serviced in current पूर्णांकerrupt.
	 */
	अगर (mbx_data->async_watermark_val < ICE_ASYNC_VF_MSG_THRESHOLD ||
	    mbx_data->async_watermark_val > mbx_data->max_num_msgs_mbx)
		वापस ICE_ERR_PARAM;

	new_state = ICE_MAL_VF_DETECT_STATE_INVALID;
	snap_buf = &snap->mbx_buf;

	चयन (snap_buf->state) अणु
	हाल ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT:
		/* Clear any previously held data in mailbox snapshot काष्ठाure. */
		ice_mbx_reset_snapshot(snap);

		/* Collect the pending ARQ count, number of messages processed and
		 * the maximum number of messages allowed to be processed from the
		 * Mailbox क्रम current पूर्णांकerrupt.
		 */
		snap_buf->num_pending_arq = mbx_data->num_pending_arq;
		snap_buf->num_msg_proc = mbx_data->num_msg_proc;
		snap_buf->max_num_msgs_mbx = mbx_data->max_num_msgs_mbx;

		/* Capture a new अटल snapshot of the mailbox by logging the
		 * head and tail of snapshot and set num_iterations to the tail
		 * value to mark the start of the iteration through the snapshot.
		 */
		snap_buf->head = ICE_RQ_DATA_MASK(cq->rq.next_to_clean +
						  mbx_data->num_pending_arq);
		snap_buf->tail = ICE_RQ_DATA_MASK(cq->rq.next_to_clean - 1);
		snap_buf->num_iterations = snap_buf->tail;

		/* Pending ARQ messages वापसed by ice_clean_rq_elem
		 * is the dअगरference between the head and tail of the
		 * mailbox queue. Comparing this value against the watermark
		 * helps to check अगर we potentially have malicious VFs.
		 */
		अगर (snap_buf->num_pending_arq >=
		    mbx_data->async_watermark_val) अणु
			new_state = ICE_MAL_VF_DETECT_STATE_DETECT;
			status = ice_mbx_detect_malvf(hw, vf_id, &new_state, is_malvf);
		पूर्ण अन्यथा अणु
			new_state = ICE_MAL_VF_DETECT_STATE_TRAVERSE;
			ice_mbx_traverse(hw, &new_state);
		पूर्ण
		अवरोध;

	हाल ICE_MAL_VF_DETECT_STATE_TRAVERSE:
		new_state = ICE_MAL_VF_DETECT_STATE_TRAVERSE;
		ice_mbx_traverse(hw, &new_state);
		अवरोध;

	हाल ICE_MAL_VF_DETECT_STATE_DETECT:
		new_state = ICE_MAL_VF_DETECT_STATE_DETECT;
		status = ice_mbx_detect_malvf(hw, vf_id, &new_state, is_malvf);
		अवरोध;

	शेष:
		new_state = ICE_MAL_VF_DETECT_STATE_INVALID;
		status = ICE_ERR_CFG;
	पूर्ण

	snap_buf->state = new_state;

	वापस status;
पूर्ण

/**
 * ice_mbx_report_malvf - Track and note malicious VF
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @all_malvfs: all malicious VFs tracked by PF
 * @biपंचांगap_len: length of biपंचांगap in bits
 * @vf_id: relative भव function ID of the malicious VF
 * @report_malvf: boolean to indicate अगर malicious VF must be reported
 *
 * This function will update a biपंचांगap that keeps track of the malicious
 * VFs attached to the PF. A malicious VF must be reported only once अगर
 * discovered between VF resets or loading so the function checks
 * the input vf_id against the biपंचांगap to verअगरy अगर the VF has been
 * detected in any previous mailbox iterations.
 */
क्रमागत ice_status
ice_mbx_report_malvf(काष्ठा ice_hw *hw, अचिन्हित दीर्घ *all_malvfs,
		     u16 biपंचांगap_len, u16 vf_id, bool *report_malvf)
अणु
	अगर (!all_malvfs || !report_malvf)
		वापस ICE_ERR_PARAM;

	*report_malvf = false;

	अगर (biपंचांगap_len < hw->mbx_snapshot.mbx_vf.vfcntr_len)
		वापस ICE_ERR_INVAL_SIZE;

	अगर (vf_id >= biपंचांगap_len)
		वापस ICE_ERR_OUT_OF_RANGE;

	/* If the vf_id is found in the biपंचांगap set bit and boolean to true */
	अगर (!test_and_set_bit(vf_id, all_malvfs))
		*report_malvf = true;

	वापस 0;
पूर्ण

/**
 * ice_mbx_clear_malvf - Clear VF biपंचांगap and counter क्रम VF ID
 * @snap: poपूर्णांकer to the mailbox snapshot काष्ठाure
 * @all_malvfs: all malicious VFs tracked by PF
 * @biपंचांगap_len: length of biपंचांगap in bits
 * @vf_id: relative भव function ID of the malicious VF
 *
 * In हाल of a VF reset, this function can be called to clear
 * the bit corresponding to the VF ID in the biपंचांगap tracking all
 * malicious VFs attached to the PF. The function also clears the
 * VF counter array at the index of the VF ID. This is to ensure
 * that the new VF loaded is not considered malicious beक्रमe going
 * through the overflow detection algorithm.
 */
क्रमागत ice_status
ice_mbx_clear_malvf(काष्ठा ice_mbx_snapshot *snap, अचिन्हित दीर्घ *all_malvfs,
		    u16 biपंचांगap_len, u16 vf_id)
अणु
	अगर (!snap || !all_malvfs)
		वापस ICE_ERR_PARAM;

	अगर (biपंचांगap_len < snap->mbx_vf.vfcntr_len)
		वापस ICE_ERR_INVAL_SIZE;

	/* Ensure VF ID value is not larger than biपंचांगap or VF counter length */
	अगर (vf_id >= biपंचांगap_len || vf_id >= snap->mbx_vf.vfcntr_len)
		वापस ICE_ERR_OUT_OF_RANGE;

	/* Clear VF ID bit in the biपंचांगap tracking malicious VFs attached to PF */
	clear_bit(vf_id, all_malvfs);

	/* Clear the VF counter in the mailbox snapshot काष्ठाure क्रम that VF ID.
	 * This is to ensure that अगर a VF is unloaded and a new one brought back
	 * up with the same VF ID क्रम a snapshot currently in traversal or detect
	 * state the counter क्रम that VF ID करोes not increment on top of existing
	 * values in the mailbox overflow detection algorithm.
	 */
	snap->mbx_vf.vf_cntr[vf_id] = 0;

	वापस 0;
पूर्ण

/**
 * ice_mbx_init_snapshot - Initialize mailbox snapshot काष्ठाure
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vf_count: number of VFs allocated on a PF
 *
 * Clear the mailbox snapshot काष्ठाure and allocate memory
 * क्रम the VF counter array based on the number of VFs allocated
 * on that PF.
 *
 * Assumption: This function will assume ice_get_caps() has alपढ़ोy been
 * called to ensure that the vf_count can be compared against the number
 * of VFs supported as defined in the functional capabilities of the device.
 */
क्रमागत ice_status ice_mbx_init_snapshot(काष्ठा ice_hw *hw, u16 vf_count)
अणु
	काष्ठा ice_mbx_snapshot *snap = &hw->mbx_snapshot;

	/* Ensure that the number of VFs allocated is non-zero and
	 * is not greater than the number of supported VFs defined in
	 * the functional capabilities of the PF.
	 */
	अगर (!vf_count || vf_count > hw->func_caps.num_allocd_vfs)
		वापस ICE_ERR_INVAL_SIZE;

	snap->mbx_vf.vf_cntr = devm_kसुस्मृति(ice_hw_to_dev(hw), vf_count,
					    माप(*snap->mbx_vf.vf_cntr),
					    GFP_KERNEL);
	अगर (!snap->mbx_vf.vf_cntr)
		वापस ICE_ERR_NO_MEMORY;

	/* Setting the VF counter length to the number of allocated
	 * VFs क्रम given PF's functional capabilities.
	 */
	snap->mbx_vf.vfcntr_len = vf_count;

	/* Clear mbx_buf in the mailbox snaphot काष्ठाure and setting the
	 * mailbox snapshot state to a new capture.
	 */
	स_रखो(&snap->mbx_buf, 0, माप(snap->mbx_buf));
	snap->mbx_buf.state = ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT;

	वापस 0;
पूर्ण

/**
 * ice_mbx_deinit_snapshot - Free mailbox snapshot काष्ठाure
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Clear the mailbox snapshot काष्ठाure and मुक्त the VF counter array.
 */
व्योम ice_mbx_deinit_snapshot(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_mbx_snapshot *snap = &hw->mbx_snapshot;

	/* Free VF counter array and reset VF counter length */
	devm_kमुक्त(ice_hw_to_dev(hw), snap->mbx_vf.vf_cntr);
	snap->mbx_vf.vfcntr_len = 0;

	/* Clear mbx_buf in the mailbox snaphot काष्ठाure */
	स_रखो(&snap->mbx_buf, 0, माप(snap->mbx_buf));
पूर्ण
