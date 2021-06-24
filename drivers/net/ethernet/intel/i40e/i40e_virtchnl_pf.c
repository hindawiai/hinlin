<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e.h"

/*********************notअगरication routines***********************/

/**
 * i40e_vc_vf_broadcast
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @v_opcode: operation code
 * @v_retval: वापस value
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 *
 * send a message to all VFs on a given PF
 **/
अटल व्योम i40e_vc_vf_broadcast(काष्ठा i40e_pf *pf,
				 क्रमागत virtchnl_ops v_opcode,
				 i40e_status v_retval, u8 *msg,
				 u16 msglen)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vf *vf = pf->vf;
	पूर्णांक i;

	क्रम (i = 0; i < pf->num_alloc_vfs; i++, vf++) अणु
		पूर्णांक असल_vf_id = vf->vf_id + (पूर्णांक)hw->func_caps.vf_base_id;
		/* Not all vfs are enabled so skip the ones that are not */
		अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states) &&
		    !test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
			जारी;

		/* Ignore वापस value on purpose - a given VF may fail, but
		 * we need to keep going and send to all of them
		 */
		i40e_aq_send_msg_to_vf(hw, असल_vf_id, v_opcode, v_retval,
				       msg, msglen, शून्य);
	पूर्ण
पूर्ण

/**
 * i40e_vc_link_speed2mbps
 * converts i40e_aq_link_speed to पूर्णांकeger value of Mbps
 * @link_speed: the speed to convert
 *
 * वापस the speed as direct value of Mbps.
 **/
अटल u32
i40e_vc_link_speed2mbps(क्रमागत i40e_aq_link_speed link_speed)
अणु
	चयन (link_speed) अणु
	हाल I40E_LINK_SPEED_100MB:
		वापस SPEED_100;
	हाल I40E_LINK_SPEED_1GB:
		वापस SPEED_1000;
	हाल I40E_LINK_SPEED_2_5GB:
		वापस SPEED_2500;
	हाल I40E_LINK_SPEED_5GB:
		वापस SPEED_5000;
	हाल I40E_LINK_SPEED_10GB:
		वापस SPEED_10000;
	हाल I40E_LINK_SPEED_20GB:
		वापस SPEED_20000;
	हाल I40E_LINK_SPEED_25GB:
		वापस SPEED_25000;
	हाल I40E_LINK_SPEED_40GB:
		वापस SPEED_40000;
	हाल I40E_LINK_SPEED_UNKNOWN:
		वापस SPEED_UNKNOWN;
	पूर्ण
	वापस SPEED_UNKNOWN;
पूर्ण

/**
 * i40e_set_vf_link_state
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @pfe: poपूर्णांकer to PF event काष्ठाure
 * @ls: poपूर्णांकer to link status काष्ठाure
 *
 * set a link state on a single vf
 **/
अटल व्योम i40e_set_vf_link_state(काष्ठा i40e_vf *vf,
				   काष्ठा virtchnl_pf_event *pfe, काष्ठा i40e_link_status *ls)
अणु
	u8 link_status = ls->link_info & I40E_AQ_LINK_UP;

	अगर (vf->link_क्रमced)
		link_status = vf->link_up;

	अगर (vf->driver_caps & VIRTCHNL_VF_CAP_ADV_LINK_SPEED) अणु
		pfe->event_data.link_event_adv.link_speed = link_status ?
			i40e_vc_link_speed2mbps(ls->link_speed) : 0;
		pfe->event_data.link_event_adv.link_status = link_status;
	पूर्ण अन्यथा अणु
		pfe->event_data.link_event.link_speed = link_status ?
			i40e_virtchnl_link_speed(ls->link_speed) : 0;
		pfe->event_data.link_event.link_status = link_status;
	पूर्ण
पूर्ण

/**
 * i40e_vc_notअगरy_vf_link_state
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * send a link status message to a single VF
 **/
अटल व्योम i40e_vc_notअगरy_vf_link_state(काष्ठा i40e_vf *vf)
अणु
	काष्ठा virtchnl_pf_event pfe;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_link_status *ls = &pf->hw.phy.link_info;
	पूर्णांक असल_vf_id = vf->vf_id + (पूर्णांक)hw->func_caps.vf_base_id;

	pfe.event = VIRTCHNL_EVENT_LINK_CHANGE;
	pfe.severity = PF_EVENT_SEVERITY_INFO;

	i40e_set_vf_link_state(vf, &pfe, ls);

	i40e_aq_send_msg_to_vf(hw, असल_vf_id, VIRTCHNL_OP_EVENT,
			       0, (u8 *)&pfe, माप(pfe), शून्य);
पूर्ण

/**
 * i40e_vc_notअगरy_link_state
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * send a link status message to all VFs on a given PF
 **/
व्योम i40e_vc_notअगरy_link_state(काष्ठा i40e_pf *pf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pf->num_alloc_vfs; i++)
		i40e_vc_notअगरy_vf_link_state(&pf->vf[i]);
पूर्ण

/**
 * i40e_vc_notअगरy_reset
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * indicate a pending reset to all VFs on a given PF
 **/
व्योम i40e_vc_notअगरy_reset(काष्ठा i40e_pf *pf)
अणु
	काष्ठा virtchnl_pf_event pfe;

	pfe.event = VIRTCHNL_EVENT_RESET_IMPENDING;
	pfe.severity = PF_EVENT_SEVERITY_CERTAIN_DOOM;
	i40e_vc_vf_broadcast(pf, VIRTCHNL_OP_EVENT, 0,
			     (u8 *)&pfe, माप(काष्ठा virtchnl_pf_event));
पूर्ण

/**
 * i40e_vc_notअगरy_vf_reset
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * indicate a pending reset to the given VF
 **/
व्योम i40e_vc_notअगरy_vf_reset(काष्ठा i40e_vf *vf)
अणु
	काष्ठा virtchnl_pf_event pfe;
	पूर्णांक असल_vf_id;

	/* validate the request */
	अगर (!vf || vf->vf_id >= vf->pf->num_alloc_vfs)
		वापस;

	/* verअगरy अगर the VF is in either init or active beक्रमe proceeding */
	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states) &&
	    !test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
		वापस;

	असल_vf_id = vf->vf_id + (पूर्णांक)vf->pf->hw.func_caps.vf_base_id;

	pfe.event = VIRTCHNL_EVENT_RESET_IMPENDING;
	pfe.severity = PF_EVENT_SEVERITY_CERTAIN_DOOM;
	i40e_aq_send_msg_to_vf(&vf->pf->hw, असल_vf_id, VIRTCHNL_OP_EVENT,
			       0, (u8 *)&pfe,
			       माप(काष्ठा virtchnl_pf_event), शून्य);
पूर्ण
/***********************misc routines*****************************/

/**
 * i40e_vc_disable_vf
 * @vf: poपूर्णांकer to the VF info
 *
 * Disable the VF through a SW reset.
 **/
अटल अंतरभूत व्योम i40e_vc_disable_vf(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	पूर्णांक i;

	i40e_vc_notअगरy_vf_reset(vf);

	/* We want to ensure that an actual reset occurs initiated after this
	 * function was called. However, we करो not want to रुको क्रमever, so
	 * we'll give a reasonable समय and prपूर्णांक a message अगर we failed to
	 * ensure a reset.
	 */
	क्रम (i = 0; i < 20; i++) अणु
		/* If PF is in VFs releasing state reset VF is impossible,
		 * so leave it.
		 */
		अगर (test_bit(__I40E_VFS_RELEASING, pf->state))
			वापस;
		अगर (i40e_reset_vf(vf, false))
			वापस;
		usleep_range(10000, 20000);
	पूर्ण

	dev_warn(&vf->pf->pdev->dev,
		 "Failed to initiate reset for VF %d after 200 milliseconds\n",
		 vf->vf_id);
पूर्ण

/**
 * i40e_vc_isvalid_vsi_id
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: VF relative VSI id
 *
 * check क्रम the valid VSI id
 **/
अटल अंतरभूत bool i40e_vc_isvalid_vsi_id(काष्ठा i40e_vf *vf, u16 vsi_id)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = i40e_find_vsi_from_id(pf, vsi_id);

	वापस (vsi && (vsi->vf_id == vf->vf_id));
पूर्ण

/**
 * i40e_vc_isvalid_queue_id
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: vsi id
 * @qid: vsi relative queue id
 *
 * check क्रम the valid queue id
 **/
अटल अंतरभूत bool i40e_vc_isvalid_queue_id(काष्ठा i40e_vf *vf, u16 vsi_id,
					    u16 qid)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = i40e_find_vsi_from_id(pf, vsi_id);

	वापस (vsi && (qid < vsi->alloc_queue_pairs));
पूर्ण

/**
 * i40e_vc_isvalid_vector_id
 * @vf: poपूर्णांकer to the VF info
 * @vector_id: VF relative vector id
 *
 * check क्रम the valid vector id
 **/
अटल अंतरभूत bool i40e_vc_isvalid_vector_id(काष्ठा i40e_vf *vf, u32 vector_id)
अणु
	काष्ठा i40e_pf *pf = vf->pf;

	वापस vector_id < pf->hw.func_caps.num_msix_vectors_vf;
पूर्ण

/***********************vf resource mgmt routines*****************/

/**
 * i40e_vc_get_pf_queue_id
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: id of VSI as provided by the FW
 * @vsi_queue_id: vsi relative queue id
 *
 * वापस PF relative queue id
 **/
अटल u16 i40e_vc_get_pf_queue_id(काष्ठा i40e_vf *vf, u16 vsi_id,
				   u8 vsi_queue_id)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = i40e_find_vsi_from_id(pf, vsi_id);
	u16 pf_queue_id = I40E_QUEUE_END_OF_LIST;

	अगर (!vsi)
		वापस pf_queue_id;

	अगर (le16_to_cpu(vsi->info.mapping_flags) &
	    I40E_AQ_VSI_QUE_MAP_NONCONTIG)
		pf_queue_id =
			le16_to_cpu(vsi->info.queue_mapping[vsi_queue_id]);
	अन्यथा
		pf_queue_id = le16_to_cpu(vsi->info.queue_mapping[0]) +
			      vsi_queue_id;

	वापस pf_queue_id;
पूर्ण

/**
 * i40e_get_real_pf_qid
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: vsi id
 * @queue_id: queue number
 *
 * wrapper function to get pf_queue_id handling ADq code as well
 **/
अटल u16 i40e_get_real_pf_qid(काष्ठा i40e_vf *vf, u16 vsi_id, u16 queue_id)
अणु
	पूर्णांक i;

	अगर (vf->adq_enabled) अणु
		/* Although VF considers all the queues(can be 1 to 16) as its
		 * own but they may actually beदीर्घ to dअगरferent VSIs(up to 4).
		 * We need to find which queues beदीर्घs to which VSI.
		 */
		क्रम (i = 0; i < vf->num_tc; i++) अणु
			अगर (queue_id < vf->ch[i].num_qps) अणु
				vsi_id = vf->ch[i].vsi_id;
				अवरोध;
			पूर्ण
			/* find right queue id which is relative to a
			 * given VSI.
			 */
			queue_id -= vf->ch[i].num_qps;
			पूर्ण
		पूर्ण

	वापस i40e_vc_get_pf_queue_id(vf, vsi_id, queue_id);
पूर्ण

/**
 * i40e_config_irq_link_list
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: id of VSI as given by the FW
 * @vecmap: irq map info
 *
 * configure irq link list from the map
 **/
अटल व्योम i40e_config_irq_link_list(काष्ठा i40e_vf *vf, u16 vsi_id,
				      काष्ठा virtchnl_vector_map *vecmap)
अणु
	अचिन्हित दीर्घ linklisपंचांगap = 0, tempmap;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 vsi_queue_id, pf_queue_id;
	क्रमागत i40e_queue_type qtype;
	u16 next_q, vector_id, size;
	u32 reg, reg_idx;
	u16 itr_idx = 0;

	vector_id = vecmap->vector_id;
	/* setup the head */
	अगर (0 == vector_id)
		reg_idx = I40E_VPINT_LNKLST0(vf->vf_id);
	अन्यथा
		reg_idx = I40E_VPINT_LNKLSTN(
		     ((pf->hw.func_caps.num_msix_vectors_vf - 1) * vf->vf_id) +
		     (vector_id - 1));

	अगर (vecmap->rxq_map == 0 && vecmap->txq_map == 0) अणु
		/* Special हाल - No queues mapped on this vector */
		wr32(hw, reg_idx, I40E_VPINT_LNKLST0_FIRSTQ_INDX_MASK);
		जाओ irq_list_करोne;
	पूर्ण
	tempmap = vecmap->rxq_map;
	क्रम_each_set_bit(vsi_queue_id, &tempmap, I40E_MAX_VSI_QP) अणु
		linklisपंचांगap |= (BIT(I40E_VIRTCHNL_SUPPORTED_QTYPES *
				    vsi_queue_id));
	पूर्ण

	tempmap = vecmap->txq_map;
	क्रम_each_set_bit(vsi_queue_id, &tempmap, I40E_MAX_VSI_QP) अणु
		linklisपंचांगap |= (BIT(I40E_VIRTCHNL_SUPPORTED_QTYPES *
				     vsi_queue_id + 1));
	पूर्ण

	size = I40E_MAX_VSI_QP * I40E_VIRTCHNL_SUPPORTED_QTYPES;
	next_q = find_first_bit(&linklisपंचांगap, size);
	अगर (unlikely(next_q == size))
		जाओ irq_list_करोne;

	vsi_queue_id = next_q / I40E_VIRTCHNL_SUPPORTED_QTYPES;
	qtype = next_q % I40E_VIRTCHNL_SUPPORTED_QTYPES;
	pf_queue_id = i40e_get_real_pf_qid(vf, vsi_id, vsi_queue_id);
	reg = ((qtype << I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT) | pf_queue_id);

	wr32(hw, reg_idx, reg);

	जबतक (next_q < size) अणु
		चयन (qtype) अणु
		हाल I40E_QUEUE_TYPE_RX:
			reg_idx = I40E_QINT_RQCTL(pf_queue_id);
			itr_idx = vecmap->rxitr_idx;
			अवरोध;
		हाल I40E_QUEUE_TYPE_TX:
			reg_idx = I40E_QINT_TQCTL(pf_queue_id);
			itr_idx = vecmap->txitr_idx;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		next_q = find_next_bit(&linklisपंचांगap, size, next_q + 1);
		अगर (next_q < size) अणु
			vsi_queue_id = next_q / I40E_VIRTCHNL_SUPPORTED_QTYPES;
			qtype = next_q % I40E_VIRTCHNL_SUPPORTED_QTYPES;
			pf_queue_id = i40e_get_real_pf_qid(vf,
							   vsi_id,
							   vsi_queue_id);
		पूर्ण अन्यथा अणु
			pf_queue_id = I40E_QUEUE_END_OF_LIST;
			qtype = 0;
		पूर्ण

		/* क्रमmat क्रम the RQCTL & TQCTL regs is same */
		reg = (vector_id) |
		    (qtype << I40E_QINT_RQCTL_NEXTQ_TYPE_SHIFT) |
		    (pf_queue_id << I40E_QINT_RQCTL_NEXTQ_INDX_SHIFT) |
		    BIT(I40E_QINT_RQCTL_CAUSE_ENA_SHIFT) |
		    (itr_idx << I40E_QINT_RQCTL_ITR_INDX_SHIFT);
		wr32(hw, reg_idx, reg);
	पूर्ण

	/* अगर the vf is running in polling mode and using पूर्णांकerrupt zero,
	 * need to disable स्वतः-mask on enabling zero पूर्णांकerrupt क्रम VFs.
	 */
	अगर ((vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RX_POLLING) &&
	    (vector_id == 0)) अणु
		reg = rd32(hw, I40E_GLINT_CTL);
		अगर (!(reg & I40E_GLINT_CTL_DIS_AUTOMASK_VF0_MASK)) अणु
			reg |= I40E_GLINT_CTL_DIS_AUTOMASK_VF0_MASK;
			wr32(hw, I40E_GLINT_CTL, reg);
		पूर्ण
	पूर्ण

irq_list_करोne:
	i40e_flush(hw);
पूर्ण

/**
 * i40e_release_iwarp_qvlist
 * @vf: poपूर्णांकer to the VF.
 *
 **/
अटल व्योम i40e_release_iwarp_qvlist(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा virtchnl_iwarp_qvlist_info *qvlist_info = vf->qvlist_info;
	u32 msix_vf;
	u32 i;

	अगर (!vf->qvlist_info)
		वापस;

	msix_vf = pf->hw.func_caps.num_msix_vectors_vf;
	क्रम (i = 0; i < qvlist_info->num_vectors; i++) अणु
		काष्ठा virtchnl_iwarp_qv_info *qv_info;
		u32 next_q_index, next_q_type;
		काष्ठा i40e_hw *hw = &pf->hw;
		u32 v_idx, reg_idx, reg;

		qv_info = &qvlist_info->qv_info[i];
		अगर (!qv_info)
			जारी;
		v_idx = qv_info->v_idx;
		अगर (qv_info->ceq_idx != I40E_QUEUE_INVALID_IDX) अणु
			/* Figure out the queue after CEQ and make that the
			 * first queue.
			 */
			reg_idx = (msix_vf - 1) * vf->vf_id + qv_info->ceq_idx;
			reg = rd32(hw, I40E_VPINT_CEQCTL(reg_idx));
			next_q_index = (reg & I40E_VPINT_CEQCTL_NEXTQ_INDX_MASK)
					>> I40E_VPINT_CEQCTL_NEXTQ_INDX_SHIFT;
			next_q_type = (reg & I40E_VPINT_CEQCTL_NEXTQ_TYPE_MASK)
					>> I40E_VPINT_CEQCTL_NEXTQ_TYPE_SHIFT;

			reg_idx = ((msix_vf - 1) * vf->vf_id) + (v_idx - 1);
			reg = (next_q_index &
			       I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK) |
			       (next_q_type <<
			       I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);

			wr32(hw, I40E_VPINT_LNKLSTN(reg_idx), reg);
		पूर्ण
	पूर्ण
	kमुक्त(vf->qvlist_info);
	vf->qvlist_info = शून्य;
पूर्ण

/**
 * i40e_config_iwarp_qvlist
 * @vf: poपूर्णांकer to the VF info
 * @qvlist_info: queue and vector list
 *
 * Return 0 on success or < 0 on error
 **/
अटल पूर्णांक i40e_config_iwarp_qvlist(काष्ठा i40e_vf *vf,
				    काष्ठा virtchnl_iwarp_qvlist_info *qvlist_info)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा virtchnl_iwarp_qv_info *qv_info;
	u32 v_idx, i, reg_idx, reg;
	u32 next_q_idx, next_q_type;
	u32 msix_vf;
	पूर्णांक ret = 0;

	msix_vf = pf->hw.func_caps.num_msix_vectors_vf;

	अगर (qvlist_info->num_vectors > msix_vf) अणु
		dev_warn(&pf->pdev->dev,
			 "Incorrect number of iwarp vectors %u. Maximum %u allowed.\n",
			 qvlist_info->num_vectors,
			 msix_vf);
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	kमुक्त(vf->qvlist_info);
	vf->qvlist_info = kzalloc(काष्ठा_size(vf->qvlist_info, qv_info,
					      qvlist_info->num_vectors - 1),
				  GFP_KERNEL);
	अगर (!vf->qvlist_info) अणु
		ret = -ENOMEM;
		जाओ err_out;
	पूर्ण
	vf->qvlist_info->num_vectors = qvlist_info->num_vectors;

	msix_vf = pf->hw.func_caps.num_msix_vectors_vf;
	क्रम (i = 0; i < qvlist_info->num_vectors; i++) अणु
		qv_info = &qvlist_info->qv_info[i];
		अगर (!qv_info)
			जारी;

		/* Validate vector id beदीर्घs to this vf */
		अगर (!i40e_vc_isvalid_vector_id(vf, qv_info->v_idx)) अणु
			ret = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		v_idx = qv_info->v_idx;

		vf->qvlist_info->qv_info[i] = *qv_info;

		reg_idx = ((msix_vf - 1) * vf->vf_id) + (v_idx - 1);
		/* We might be sharing the पूर्णांकerrupt, so get the first queue
		 * index and type, push it करोwn the list by adding the new
		 * queue on top. Also link it with the new queue in CEQCTL.
		 */
		reg = rd32(hw, I40E_VPINT_LNKLSTN(reg_idx));
		next_q_idx = ((reg & I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK) >>
				I40E_VPINT_LNKLSTN_FIRSTQ_INDX_SHIFT);
		next_q_type = ((reg & I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_MASK) >>
				I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);

		अगर (qv_info->ceq_idx != I40E_QUEUE_INVALID_IDX) अणु
			reg_idx = (msix_vf - 1) * vf->vf_id + qv_info->ceq_idx;
			reg = (I40E_VPINT_CEQCTL_CAUSE_ENA_MASK |
			(v_idx << I40E_VPINT_CEQCTL_MSIX_INDX_SHIFT) |
			(qv_info->itr_idx << I40E_VPINT_CEQCTL_ITR_INDX_SHIFT) |
			(next_q_type << I40E_VPINT_CEQCTL_NEXTQ_TYPE_SHIFT) |
			(next_q_idx << I40E_VPINT_CEQCTL_NEXTQ_INDX_SHIFT));
			wr32(hw, I40E_VPINT_CEQCTL(reg_idx), reg);

			reg_idx = ((msix_vf - 1) * vf->vf_id) + (v_idx - 1);
			reg = (qv_info->ceq_idx &
			       I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK) |
			       (I40E_QUEUE_TYPE_PE_CEQ <<
			       I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_SHIFT);
			wr32(hw, I40E_VPINT_LNKLSTN(reg_idx), reg);
		पूर्ण

		अगर (qv_info->aeq_idx != I40E_QUEUE_INVALID_IDX) अणु
			reg = (I40E_VPINT_AEQCTL_CAUSE_ENA_MASK |
			(v_idx << I40E_VPINT_AEQCTL_MSIX_INDX_SHIFT) |
			(qv_info->itr_idx << I40E_VPINT_AEQCTL_ITR_INDX_SHIFT));

			wr32(hw, I40E_VPINT_AEQCTL(vf->vf_id), reg);
		पूर्ण
	पूर्ण

	वापस 0;
err_मुक्त:
	kमुक्त(vf->qvlist_info);
	vf->qvlist_info = शून्य;
err_out:
	वापस ret;
पूर्ण

/**
 * i40e_config_vsi_tx_queue
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: id of VSI as provided by the FW
 * @vsi_queue_id: vsi relative queue index
 * @info: config. info
 *
 * configure tx queue
 **/
अटल पूर्णांक i40e_config_vsi_tx_queue(काष्ठा i40e_vf *vf, u16 vsi_id,
				    u16 vsi_queue_id,
				    काष्ठा virtchnl_txq_info *info)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_hmc_obj_txq tx_ctx;
	काष्ठा i40e_vsi *vsi;
	u16 pf_queue_id;
	u32 qtx_ctl;
	पूर्णांक ret = 0;

	अगर (!i40e_vc_isvalid_vsi_id(vf, info->vsi_id)) अणु
		ret = -ENOENT;
		जाओ error_context;
	पूर्ण
	pf_queue_id = i40e_vc_get_pf_queue_id(vf, vsi_id, vsi_queue_id);
	vsi = i40e_find_vsi_from_id(pf, vsi_id);
	अगर (!vsi) अणु
		ret = -ENOENT;
		जाओ error_context;
	पूर्ण

	/* clear the context काष्ठाure first */
	स_रखो(&tx_ctx, 0, माप(काष्ठा i40e_hmc_obj_txq));

	/* only set the required fields */
	tx_ctx.base = info->dma_ring_addr / 128;
	tx_ctx.qlen = info->ring_len;
	tx_ctx.rdylist = le16_to_cpu(vsi->info.qs_handle[0]);
	tx_ctx.rdylist_act = 0;
	tx_ctx.head_wb_ena = info->headwb_enabled;
	tx_ctx.head_wb_addr = info->dma_headwb_addr;

	/* clear the context in the HMC */
	ret = i40e_clear_lan_tx_queue_context(hw, pf_queue_id);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"Failed to clear VF LAN Tx queue context %d, error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		जाओ error_context;
	पूर्ण

	/* set the context in the HMC */
	ret = i40e_set_lan_tx_queue_context(hw, pf_queue_id, &tx_ctx);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"Failed to set VF LAN Tx queue context %d error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		जाओ error_context;
	पूर्ण

	/* associate this queue with the PCI VF function */
	qtx_ctl = I40E_QTX_CTL_VF_QUEUE;
	qtx_ctl |= ((hw->pf_id << I40E_QTX_CTL_PF_INDX_SHIFT)
		    & I40E_QTX_CTL_PF_INDX_MASK);
	qtx_ctl |= (((vf->vf_id + hw->func_caps.vf_base_id)
		     << I40E_QTX_CTL_VFVM_INDX_SHIFT)
		    & I40E_QTX_CTL_VFVM_INDX_MASK);
	wr32(hw, I40E_QTX_CTL(pf_queue_id), qtx_ctl);
	i40e_flush(hw);

error_context:
	वापस ret;
पूर्ण

/**
 * i40e_config_vsi_rx_queue
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: id of VSI  as provided by the FW
 * @vsi_queue_id: vsi relative queue index
 * @info: config. info
 *
 * configure rx queue
 **/
अटल पूर्णांक i40e_config_vsi_rx_queue(काष्ठा i40e_vf *vf, u16 vsi_id,
				    u16 vsi_queue_id,
				    काष्ठा virtchnl_rxq_info *info)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_hmc_obj_rxq rx_ctx;
	u16 pf_queue_id;
	पूर्णांक ret = 0;

	pf_queue_id = i40e_vc_get_pf_queue_id(vf, vsi_id, vsi_queue_id);

	/* clear the context काष्ठाure first */
	स_रखो(&rx_ctx, 0, माप(काष्ठा i40e_hmc_obj_rxq));

	/* only set the required fields */
	rx_ctx.base = info->dma_ring_addr / 128;
	rx_ctx.qlen = info->ring_len;

	अगर (info->splithdr_enabled) अणु
		rx_ctx.hsplit_0 = I40E_RX_SPLIT_L2      |
				  I40E_RX_SPLIT_IP      |
				  I40E_RX_SPLIT_TCP_UDP |
				  I40E_RX_SPLIT_SCTP;
		/* header length validation */
		अगर (info->hdr_size > ((2 * 1024) - 64)) अणु
			ret = -EINVAL;
			जाओ error_param;
		पूर्ण
		rx_ctx.hbuff = info->hdr_size >> I40E_RXQ_CTX_HBUFF_SHIFT;

		/* set split mode 10b */
		rx_ctx.dtype = I40E_RX_DTYPE_HEADER_SPLIT;
	पूर्ण

	/* databuffer length validation */
	अगर (info->databuffer_size > ((16 * 1024) - 128)) अणु
		ret = -EINVAL;
		जाओ error_param;
	पूर्ण
	rx_ctx.dbuff = info->databuffer_size >> I40E_RXQ_CTX_DBUFF_SHIFT;

	/* max pkt. length validation */
	अगर (info->max_pkt_size >= (16 * 1024) || info->max_pkt_size < 64) अणु
		ret = -EINVAL;
		जाओ error_param;
	पूर्ण
	rx_ctx.rxmax = info->max_pkt_size;

	/* enable 32bytes desc always */
	rx_ctx.dsize = 1;

	/* शेष values */
	rx_ctx.lrxqthresh = 1;
	rx_ctx.crcstrip = 1;
	rx_ctx.prefena = 1;
	rx_ctx.l2tsel = 1;

	/* clear the context in the HMC */
	ret = i40e_clear_lan_rx_queue_context(hw, pf_queue_id);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"Failed to clear VF LAN Rx queue context %d, error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		जाओ error_param;
	पूर्ण

	/* set the context in the HMC */
	ret = i40e_set_lan_rx_queue_context(hw, pf_queue_id, &rx_ctx);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"Failed to set VF LAN Rx queue context %d error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		जाओ error_param;
	पूर्ण

error_param:
	वापस ret;
पूर्ण

/**
 * i40e_alloc_vsi_res
 * @vf: poपूर्णांकer to the VF info
 * @idx: VSI index, applies only क्रम ADq mode, zero otherwise
 *
 * alloc VF vsi context & resources
 **/
अटल पूर्णांक i40e_alloc_vsi_res(काष्ठा i40e_vf *vf, u8 idx)
अणु
	काष्ठा i40e_mac_filter *f = शून्य;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi;
	u64 max_tx_rate = 0;
	पूर्णांक ret = 0;

	vsi = i40e_vsi_setup(pf, I40E_VSI_SRIOV, pf->vsi[pf->lan_vsi]->seid,
			     vf->vf_id);

	अगर (!vsi) अणु
		dev_err(&pf->pdev->dev,
			"add vsi failed for VF %d, aq_err %d\n",
			vf->vf_id, pf->hw.aq.asq_last_status);
		ret = -ENOENT;
		जाओ error_alloc_vsi_res;
	पूर्ण

	अगर (!idx) अणु
		u64 hena = i40e_pf_get_शेष_rss_hena(pf);
		u8 broadcast[ETH_ALEN];

		vf->lan_vsi_idx = vsi->idx;
		vf->lan_vsi_id = vsi->id;
		/* If the port VLAN has been configured and then the
		 * VF driver was हटाओd then the VSI port VLAN
		 * configuration was destroyed.  Check अगर there is
		 * a port VLAN and restore the VSI configuration अगर
		 * needed.
		 */
		अगर (vf->port_vlan_id)
			i40e_vsi_add_pvid(vsi, vf->port_vlan_id);

		spin_lock_bh(&vsi->mac_filter_hash_lock);
		अगर (is_valid_ether_addr(vf->शेष_lan_addr.addr)) अणु
			f = i40e_add_mac_filter(vsi,
						vf->शेष_lan_addr.addr);
			अगर (!f)
				dev_info(&pf->pdev->dev,
					 "Could not add MAC filter %pM for VF %d\n",
					vf->शेष_lan_addr.addr, vf->vf_id);
		पूर्ण
		eth_broadcast_addr(broadcast);
		f = i40e_add_mac_filter(vsi, broadcast);
		अगर (!f)
			dev_info(&pf->pdev->dev,
				 "Could not allocate VF broadcast filter\n");
		spin_unlock_bh(&vsi->mac_filter_hash_lock);
		wr32(&pf->hw, I40E_VFQF_HENA1(0, vf->vf_id), (u32)hena);
		wr32(&pf->hw, I40E_VFQF_HENA1(1, vf->vf_id), (u32)(hena >> 32));
		/* program mac filter only क्रम VF VSI */
		ret = i40e_sync_vsi_filters(vsi);
		अगर (ret)
			dev_err(&pf->pdev->dev, "Unable to program ucast filters\n");
	पूर्ण

	/* storing VSI index and id क्रम ADq and करोn't apply the mac filter */
	अगर (vf->adq_enabled) अणु
		vf->ch[idx].vsi_idx = vsi->idx;
		vf->ch[idx].vsi_id = vsi->id;
	पूर्ण

	/* Set VF bandwidth अगर specअगरied */
	अगर (vf->tx_rate) अणु
		max_tx_rate = vf->tx_rate;
	पूर्ण अन्यथा अगर (vf->ch[idx].max_tx_rate) अणु
		max_tx_rate = vf->ch[idx].max_tx_rate;
	पूर्ण

	अगर (max_tx_rate) अणु
		max_tx_rate = भाग_u64(max_tx_rate, I40E_BW_CREDIT_DIVISOR);
		ret = i40e_aq_config_vsi_bw_limit(&pf->hw, vsi->seid,
						  max_tx_rate, 0, शून्य);
		अगर (ret)
			dev_err(&pf->pdev->dev, "Unable to set tx rate, VF %d, error code %d.\n",
				vf->vf_id, ret);
	पूर्ण

error_alloc_vsi_res:
	वापस ret;
पूर्ण

/**
 * i40e_map_pf_queues_to_vsi
 * @vf: poपूर्णांकer to the VF info
 *
 * PF maps LQPs to a VF by programming VSILAN_QTABLE & VPLAN_QTABLE. This
 * function takes care of first part VSILAN_QTABLE, mapping pf queues to VSI.
 **/
अटल व्योम i40e_map_pf_queues_to_vsi(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg, num_tc = 1; /* VF has at least one traffic class */
	u16 vsi_id, qps;
	पूर्णांक i, j;

	अगर (vf->adq_enabled)
		num_tc = vf->num_tc;

	क्रम (i = 0; i < num_tc; i++) अणु
		अगर (vf->adq_enabled) अणु
			qps = vf->ch[i].num_qps;
			vsi_id =  vf->ch[i].vsi_id;
		पूर्ण अन्यथा अणु
			qps = pf->vsi[vf->lan_vsi_idx]->alloc_queue_pairs;
			vsi_id = vf->lan_vsi_id;
		पूर्ण

		क्रम (j = 0; j < 7; j++) अणु
			अगर (j * 2 >= qps) अणु
				/* end of list */
				reg = 0x07FF07FF;
			पूर्ण अन्यथा अणु
				u16 qid = i40e_vc_get_pf_queue_id(vf,
								  vsi_id,
								  j * 2);
				reg = qid;
				qid = i40e_vc_get_pf_queue_id(vf, vsi_id,
							      (j * 2) + 1);
				reg |= qid << 16;
			पूर्ण
			i40e_ग_लिखो_rx_ctl(hw,
					  I40E_VSILAN_QTABLE(j, vsi_id),
					  reg);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_map_pf_to_vf_queues
 * @vf: poपूर्णांकer to the VF info
 *
 * PF maps LQPs to a VF by programming VSILAN_QTABLE & VPLAN_QTABLE. This
 * function takes care of the second part VPLAN_QTABLE & completes VF mappings.
 **/
अटल व्योम i40e_map_pf_to_vf_queues(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg, total_qps = 0;
	u32 qps, num_tc = 1; /* VF has at least one traffic class */
	u16 vsi_id, qid;
	पूर्णांक i, j;

	अगर (vf->adq_enabled)
		num_tc = vf->num_tc;

	क्रम (i = 0; i < num_tc; i++) अणु
		अगर (vf->adq_enabled) अणु
			qps = vf->ch[i].num_qps;
			vsi_id =  vf->ch[i].vsi_id;
		पूर्ण अन्यथा अणु
			qps = pf->vsi[vf->lan_vsi_idx]->alloc_queue_pairs;
			vsi_id = vf->lan_vsi_id;
		पूर्ण

		क्रम (j = 0; j < qps; j++) अणु
			qid = i40e_vc_get_pf_queue_id(vf, vsi_id, j);

			reg = (qid & I40E_VPLAN_QTABLE_QINDEX_MASK);
			wr32(hw, I40E_VPLAN_QTABLE(total_qps, vf->vf_id),
			     reg);
			total_qps++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_enable_vf_mappings
 * @vf: poपूर्णांकer to the VF info
 *
 * enable VF mappings
 **/
अटल व्योम i40e_enable_vf_mappings(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg;

	/* Tell the hardware we're using noncontiguous mapping. HW requires
	 * that VF queues be mapped using this method, even when they are
	 * contiguous in real lअगरe
	 */
	i40e_ग_लिखो_rx_ctl(hw, I40E_VSILAN_QBASE(vf->lan_vsi_id),
			  I40E_VSILAN_QBASE_VSIQTABLE_ENA_MASK);

	/* enable VF vplan_qtable mappings */
	reg = I40E_VPLAN_MAPENA_TXRX_ENA_MASK;
	wr32(hw, I40E_VPLAN_MAPENA(vf->vf_id), reg);

	i40e_map_pf_to_vf_queues(vf);
	i40e_map_pf_queues_to_vsi(vf);

	i40e_flush(hw);
पूर्ण

/**
 * i40e_disable_vf_mappings
 * @vf: poपूर्णांकer to the VF info
 *
 * disable VF mappings
 **/
अटल व्योम i40e_disable_vf_mappings(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक i;

	/* disable qp mappings */
	wr32(hw, I40E_VPLAN_MAPENA(vf->vf_id), 0);
	क्रम (i = 0; i < I40E_MAX_VSI_QP; i++)
		wr32(hw, I40E_VPLAN_QTABLE(i, vf->vf_id),
		     I40E_QUEUE_END_OF_LIST);
	i40e_flush(hw);
पूर्ण

/**
 * i40e_मुक्त_vf_res
 * @vf: poपूर्णांकer to the VF info
 *
 * मुक्त VF resources
 **/
अटल व्योम i40e_मुक्त_vf_res(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg_idx, reg;
	पूर्णांक i, j, msix_vf;

	/* Start by disabling VF's configuration API to prevent the OS from
	 * accessing the VF's VSI after it's मुक्तd / invalidated.
	 */
	clear_bit(I40E_VF_STATE_INIT, &vf->vf_states);

	/* It's possible the VF had requeuested more queues than the शेष so
	 * करो the accounting here when we're about to मुक्त them.
	 */
	अगर (vf->num_queue_pairs > I40E_DEFAULT_QUEUES_PER_VF) अणु
		pf->queues_left += vf->num_queue_pairs -
				   I40E_DEFAULT_QUEUES_PER_VF;
	पूर्ण

	/* मुक्त vsi & disconnect it from the parent uplink */
	अगर (vf->lan_vsi_idx) अणु
		i40e_vsi_release(pf->vsi[vf->lan_vsi_idx]);
		vf->lan_vsi_idx = 0;
		vf->lan_vsi_id = 0;
	पूर्ण

	/* करो the accounting and हटाओ additional ADq VSI's */
	अगर (vf->adq_enabled && vf->ch[0].vsi_idx) अणु
		क्रम (j = 0; j < vf->num_tc; j++) अणु
			/* At this poपूर्णांक VSI0 is alपढ़ोy released so करोn't
			 * release it again and only clear their values in
			 * काष्ठाure variables
			 */
			अगर (j)
				i40e_vsi_release(pf->vsi[vf->ch[j].vsi_idx]);
			vf->ch[j].vsi_idx = 0;
			vf->ch[j].vsi_id = 0;
		पूर्ण
	पूर्ण
	msix_vf = pf->hw.func_caps.num_msix_vectors_vf;

	/* disable पूर्णांकerrupts so the VF starts in a known state */
	क्रम (i = 0; i < msix_vf; i++) अणु
		/* क्रमmat is same क्रम both रेजिस्टरs */
		अगर (0 == i)
			reg_idx = I40E_VFINT_DYN_CTL0(vf->vf_id);
		अन्यथा
			reg_idx = I40E_VFINT_DYN_CTLN(((msix_vf - 1) *
						      (vf->vf_id))
						     + (i - 1));
		wr32(hw, reg_idx, I40E_VFINT_DYN_CTLN_CLEARPBA_MASK);
		i40e_flush(hw);
	पूर्ण

	/* clear the irq settings */
	क्रम (i = 0; i < msix_vf; i++) अणु
		/* क्रमmat is same क्रम both रेजिस्टरs */
		अगर (0 == i)
			reg_idx = I40E_VPINT_LNKLST0(vf->vf_id);
		अन्यथा
			reg_idx = I40E_VPINT_LNKLSTN(((msix_vf - 1) *
						      (vf->vf_id))
						     + (i - 1));
		reg = (I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_MASK |
		       I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK);
		wr32(hw, reg_idx, reg);
		i40e_flush(hw);
	पूर्ण
	/* reset some of the state variables keeping track of the resources */
	vf->num_queue_pairs = 0;
	clear_bit(I40E_VF_STATE_MC_PROMISC, &vf->vf_states);
	clear_bit(I40E_VF_STATE_UC_PROMISC, &vf->vf_states);
पूर्ण

/**
 * i40e_alloc_vf_res
 * @vf: poपूर्णांकer to the VF info
 *
 * allocate VF resources
 **/
अटल पूर्णांक i40e_alloc_vf_res(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	पूर्णांक total_queue_pairs = 0;
	पूर्णांक ret, idx;

	अगर (vf->num_req_queues &&
	    vf->num_req_queues <= pf->queues_left + I40E_DEFAULT_QUEUES_PER_VF)
		pf->num_vf_qps = vf->num_req_queues;
	अन्यथा
		pf->num_vf_qps = I40E_DEFAULT_QUEUES_PER_VF;

	/* allocate hw vsi context & associated resources */
	ret = i40e_alloc_vsi_res(vf, 0);
	अगर (ret)
		जाओ error_alloc;
	total_queue_pairs += pf->vsi[vf->lan_vsi_idx]->alloc_queue_pairs;

	/* allocate additional VSIs based on tc inक्रमmation क्रम ADq */
	अगर (vf->adq_enabled) अणु
		अगर (pf->queues_left >=
		    (I40E_MAX_VF_QUEUES - I40E_DEFAULT_QUEUES_PER_VF)) अणु
			/* TC 0 always beदीर्घs to VF VSI */
			क्रम (idx = 1; idx < vf->num_tc; idx++) अणु
				ret = i40e_alloc_vsi_res(vf, idx);
				अगर (ret)
					जाओ error_alloc;
			पूर्ण
			/* send correct number of queues */
			total_queue_pairs = I40E_MAX_VF_QUEUES;
		पूर्ण अन्यथा अणु
			dev_info(&pf->pdev->dev, "VF %d: Not enough queues to allocate, disabling ADq\n",
				 vf->vf_id);
			vf->adq_enabled = false;
		पूर्ण
	पूर्ण

	/* We account क्रम each VF to get a शेष number of queue pairs.  If
	 * the VF has now requested more, we need to account क्रम that to make
	 * certain we never request more queues than we actually have left in
	 * HW.
	 */
	अगर (total_queue_pairs > I40E_DEFAULT_QUEUES_PER_VF)
		pf->queues_left -=
			total_queue_pairs - I40E_DEFAULT_QUEUES_PER_VF;

	अगर (vf->trusted)
		set_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps);
	अन्यथा
		clear_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps);

	/* store the total qps number क्रम the runसमय
	 * VF req validation
	 */
	vf->num_queue_pairs = total_queue_pairs;

	/* VF is now completely initialized */
	set_bit(I40E_VF_STATE_INIT, &vf->vf_states);

error_alloc:
	अगर (ret)
		i40e_मुक्त_vf_res(vf);

	वापस ret;
पूर्ण

#घोषणा VF_DEVICE_STATUS 0xAA
#घोषणा VF_TRANS_PENDING_MASK 0x20
/**
 * i40e_quiesce_vf_pci
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * Wait क्रम VF PCI transactions to be cleared after reset. Returns -EIO
 * अगर the transactions never clear.
 **/
अटल पूर्णांक i40e_quiesce_vf_pci(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक vf_असल_id, i;
	u32 reg;

	vf_असल_id = vf->vf_id + hw->func_caps.vf_base_id;

	wr32(hw, I40E_PF_PCI_CIAA,
	     VF_DEVICE_STATUS | (vf_असल_id << I40E_PF_PCI_CIAA_VF_NUM_SHIFT));
	क्रम (i = 0; i < 100; i++) अणु
		reg = rd32(hw, I40E_PF_PCI_CIAD);
		अगर ((reg & VF_TRANS_PENDING_MASK) == 0)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -EIO;
पूर्ण

/**
 * i40e_getnum_vf_vsi_vlan_filters
 * @vsi: poपूर्णांकer to the vsi
 *
 * called to get the number of VLANs offloaded on this VF
 **/
अटल पूर्णांक i40e_getnum_vf_vsi_vlan_filters(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा i40e_mac_filter *f;
	u16 num_vlans = 0, bkt;

	hash_क्रम_each(vsi->mac_filter_hash, bkt, f, hlist) अणु
		अगर (f->vlan >= 0 && f->vlan <= I40E_MAX_VLANID)
			num_vlans++;
	पूर्ण

	वापस num_vlans;
पूर्ण

/**
 * i40e_get_vlan_list_sync
 * @vsi: poपूर्णांकer to the VSI
 * @num_vlans: number of VLANs in mac_filter_hash, वापसed to caller
 * @vlan_list: list of VLANs present in mac_filter_hash, वापसed to caller.
 *             This array is allocated here, but has to be मुक्तd in caller.
 *
 * Called to get number of VLANs and VLAN list present in mac_filter_hash.
 **/
अटल व्योम i40e_get_vlan_list_sync(काष्ठा i40e_vsi *vsi, u16 *num_vlans,
				    s16 **vlan_list)
अणु
	काष्ठा i40e_mac_filter *f;
	पूर्णांक i = 0;
	पूर्णांक bkt;

	spin_lock_bh(&vsi->mac_filter_hash_lock);
	*num_vlans = i40e_getnum_vf_vsi_vlan_filters(vsi);
	*vlan_list = kसुस्मृति(*num_vlans, माप(**vlan_list), GFP_ATOMIC);
	अगर (!(*vlan_list))
		जाओ err;

	hash_क्रम_each(vsi->mac_filter_hash, bkt, f, hlist) अणु
		अगर (f->vlan < 0 || f->vlan > I40E_MAX_VLANID)
			जारी;
		(*vlan_list)[i++] = f->vlan;
	पूर्ण
err:
	spin_unlock_bh(&vsi->mac_filter_hash_lock);
पूर्ण

/**
 * i40e_set_vsi_promisc
 * @vf: poपूर्णांकer to the VF काष्ठा
 * @seid: VSI number
 * @multi_enable: set MAC L2 layer multicast promiscuous enable/disable
 *                क्रम a given VLAN
 * @unicast_enable: set MAC L2 layer unicast promiscuous enable/disable
 *                  क्रम a given VLAN
 * @vl: List of VLANs - apply filter क्रम given VLANs
 * @num_vlans: Number of elements in @vl
 **/
अटल i40e_status
i40e_set_vsi_promisc(काष्ठा i40e_vf *vf, u16 seid, bool multi_enable,
		     bool unicast_enable, s16 *vl, u16 num_vlans)
अणु
	i40e_status aq_ret, aq_पंचांगp = 0;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक i;

	/* No VLAN to set promisc on, set on VSI */
	अगर (!num_vlans || !vl) अणु
		aq_ret = i40e_aq_set_vsi_multicast_promiscuous(hw, seid,
							       multi_enable,
							       शून्य);
		अगर (aq_ret) अणु
			पूर्णांक aq_err = pf->hw.aq.asq_last_status;

			dev_err(&pf->pdev->dev,
				"VF %d failed to set multicast promiscuous mode err %s aq_err %s\n",
				vf->vf_id,
				i40e_stat_str(&pf->hw, aq_ret),
				i40e_aq_str(&pf->hw, aq_err));

			वापस aq_ret;
		पूर्ण

		aq_ret = i40e_aq_set_vsi_unicast_promiscuous(hw, seid,
							     unicast_enable,
							     शून्य, true);

		अगर (aq_ret) अणु
			पूर्णांक aq_err = pf->hw.aq.asq_last_status;

			dev_err(&pf->pdev->dev,
				"VF %d failed to set unicast promiscuous mode err %s aq_err %s\n",
				vf->vf_id,
				i40e_stat_str(&pf->hw, aq_ret),
				i40e_aq_str(&pf->hw, aq_err));
		पूर्ण

		वापस aq_ret;
	पूर्ण

	क्रम (i = 0; i < num_vlans; i++) अणु
		aq_ret = i40e_aq_set_vsi_mc_promisc_on_vlan(hw, seid,
							    multi_enable,
							    vl[i], शून्य);
		अगर (aq_ret) अणु
			पूर्णांक aq_err = pf->hw.aq.asq_last_status;

			dev_err(&pf->pdev->dev,
				"VF %d failed to set multicast promiscuous mode err %s aq_err %s\n",
				vf->vf_id,
				i40e_stat_str(&pf->hw, aq_ret),
				i40e_aq_str(&pf->hw, aq_err));

			अगर (!aq_पंचांगp)
				aq_पंचांगp = aq_ret;
		पूर्ण

		aq_ret = i40e_aq_set_vsi_uc_promisc_on_vlan(hw, seid,
							    unicast_enable,
							    vl[i], शून्य);
		अगर (aq_ret) अणु
			पूर्णांक aq_err = pf->hw.aq.asq_last_status;

			dev_err(&pf->pdev->dev,
				"VF %d failed to set unicast promiscuous mode err %s aq_err %s\n",
				vf->vf_id,
				i40e_stat_str(&pf->hw, aq_ret),
				i40e_aq_str(&pf->hw, aq_err));

			अगर (!aq_पंचांगp)
				aq_पंचांगp = aq_ret;
		पूर्ण
	पूर्ण

	अगर (aq_पंचांगp)
		aq_ret = aq_पंचांगp;

	वापस aq_ret;
पूर्ण

/**
 * i40e_config_vf_promiscuous_mode
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: VSI id
 * @allmulti: set MAC L2 layer multicast promiscuous enable/disable
 * @alluni: set MAC L2 layer unicast promiscuous enable/disable
 *
 * Called from the VF to configure the promiscuous mode of
 * VF vsis and from the VF reset path to reset promiscuous mode.
 **/
अटल i40e_status i40e_config_vf_promiscuous_mode(काष्ठा i40e_vf *vf,
						   u16 vsi_id,
						   bool allmulti,
						   bool alluni)
अणु
	i40e_status aq_ret = I40E_SUCCESS;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi;
	u16 num_vlans;
	s16 *vl;

	vsi = i40e_find_vsi_from_id(pf, vsi_id);
	अगर (!i40e_vc_isvalid_vsi_id(vf, vsi_id) || !vsi)
		वापस I40E_ERR_PARAM;

	अगर (vf->port_vlan_id) अणु
		aq_ret = i40e_set_vsi_promisc(vf, vsi->seid, allmulti,
					      alluni, &vf->port_vlan_id, 1);
		वापस aq_ret;
	पूर्ण अन्यथा अगर (i40e_getnum_vf_vsi_vlan_filters(vsi)) अणु
		i40e_get_vlan_list_sync(vsi, &num_vlans, &vl);

		अगर (!vl)
			वापस I40E_ERR_NO_MEMORY;

		aq_ret = i40e_set_vsi_promisc(vf, vsi->seid, allmulti, alluni,
					      vl, num_vlans);
		kमुक्त(vl);
		वापस aq_ret;
	पूर्ण

	/* no VLANs to set on, set on VSI */
	aq_ret = i40e_set_vsi_promisc(vf, vsi->seid, allmulti, alluni,
				      शून्य, 0);
	वापस aq_ret;
पूर्ण

/**
 * i40e_trigger_vf_reset
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @flr: VFLR was issued or not
 *
 * Trigger hardware to start a reset क्रम a particular VF. Expects the caller
 * to रुको the proper amount of समय to allow hardware to reset the VF beक्रमe
 * it cleans up and restores VF functionality.
 **/
अटल व्योम i40e_trigger_vf_reset(काष्ठा i40e_vf *vf, bool flr)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg, reg_idx, bit_idx;

	/* warn the VF */
	clear_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states);

	/* Disable VF's configuration API during reset. The flag is re-enabled
	 * in i40e_alloc_vf_res(), when it's safe again to access VF's VSI.
	 * It's normally disabled in i40e_free_vf_res(), but it's safer
	 * to करो it earlier to give some समय to finish to any VF config
	 * functions that may still be running at this poपूर्णांक.
	 */
	clear_bit(I40E_VF_STATE_INIT, &vf->vf_states);

	/* In the हाल of a VFLR, the HW has alपढ़ोy reset the VF and we
	 * just need to clean up, so करोn't hit the VFRTRIG रेजिस्टर.
	 */
	अगर (!flr) अणु
		/* reset VF using VPGEN_VFRTRIG reg */
		reg = rd32(hw, I40E_VPGEN_VFRTRIG(vf->vf_id));
		reg |= I40E_VPGEN_VFRTRIG_VFSWR_MASK;
		wr32(hw, I40E_VPGEN_VFRTRIG(vf->vf_id), reg);
		i40e_flush(hw);
	पूर्ण
	/* clear the VFLR bit in GLGEN_VFLRSTAT */
	reg_idx = (hw->func_caps.vf_base_id + vf->vf_id) / 32;
	bit_idx = (hw->func_caps.vf_base_id + vf->vf_id) % 32;
	wr32(hw, I40E_GLGEN_VFLRSTAT(reg_idx), BIT(bit_idx));
	i40e_flush(hw);

	अगर (i40e_quiesce_vf_pci(vf))
		dev_err(&pf->pdev->dev, "VF %d PCI transactions stuck\n",
			vf->vf_id);
पूर्ण

/**
 * i40e_cleanup_reset_vf
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * Cleanup a VF after the hardware reset is finished. Expects the caller to
 * have verअगरied whether the reset is finished properly, and ensure the
 * minimum amount of रुको समय has passed.
 **/
अटल व्योम i40e_cleanup_reset_vf(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg;

	/* disable promisc modes in हाल they were enabled */
	i40e_config_vf_promiscuous_mode(vf, vf->lan_vsi_id, false, false);

	/* मुक्त VF resources to begin resetting the VSI state */
	i40e_मुक्त_vf_res(vf);

	/* Enable hardware by clearing the reset bit in the VPGEN_VFRTRIG reg.
	 * By करोing this we allow HW to access VF memory at any poपूर्णांक. If we
	 * did it any sooner, HW could access memory जबतक it was being मुक्तd
	 * in i40e_मुक्त_vf_res(), causing an IOMMU fault.
	 *
	 * On the other hand, this needs to be करोne ASAP, because the VF driver
	 * is रुकोing क्रम this to happen and may report a समयout. It's
	 * harmless, but it माला_लो logged पूर्णांकo Guest OS kernel log, so best aव्योम
	 * it.
	 */
	reg = rd32(hw, I40E_VPGEN_VFRTRIG(vf->vf_id));
	reg &= ~I40E_VPGEN_VFRTRIG_VFSWR_MASK;
	wr32(hw, I40E_VPGEN_VFRTRIG(vf->vf_id), reg);

	/* पुनः_स्मृतिate VF resources to finish resetting the VSI state */
	अगर (!i40e_alloc_vf_res(vf)) अणु
		पूर्णांक असल_vf_id = vf->vf_id + hw->func_caps.vf_base_id;
		i40e_enable_vf_mappings(vf);
		set_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states);
		clear_bit(I40E_VF_STATE_DISABLED, &vf->vf_states);
		/* Do not notअगरy the client during VF init */
		अगर (!test_and_clear_bit(I40E_VF_STATE_PRE_ENABLE,
					&vf->vf_states))
			i40e_notअगरy_client_of_vf_reset(pf, असल_vf_id);
		vf->num_vlan = 0;
	पूर्ण

	/* Tell the VF driver the reset is करोne. This needs to be करोne only
	 * after VF has been fully initialized, because the VF driver may
	 * request resources immediately after setting this flag.
	 */
	wr32(hw, I40E_VFGEN_RSTAT1(vf->vf_id), VIRTCHNL_VFR_VFACTIVE);
पूर्ण

/**
 * i40e_reset_vf
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @flr: VFLR was issued or not
 *
 * Returns true अगर the VF is in reset, resets successfully, or resets
 * are disabled and false otherwise.
 **/
bool i40e_reset_vf(काष्ठा i40e_vf *vf, bool flr)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	bool rsd = false;
	u32 reg;
	पूर्णांक i;

	अगर (test_bit(__I40E_VF_RESETS_DISABLED, pf->state))
		वापस true;

	/* If the VFs have been disabled, this means something अन्यथा is
	 * resetting the VF, so we shouldn't जारी.
	 */
	अगर (test_and_set_bit(__I40E_VF_DISABLE, pf->state))
		वापस true;

	i40e_trigger_vf_reset(vf, flr);

	/* poll VPGEN_VFRSTAT reg to make sure
	 * that reset is complete
	 */
	क्रम (i = 0; i < 10; i++) अणु
		/* VF reset requires driver to first reset the VF and then
		 * poll the status रेजिस्टर to make sure that the reset
		 * completed successfully. Due to पूर्णांकernal HW FIFO flushes,
		 * we must रुको 10ms beक्रमe the रेजिस्टर will be valid.
		 */
		usleep_range(10000, 20000);
		reg = rd32(hw, I40E_VPGEN_VFRSTAT(vf->vf_id));
		अगर (reg & I40E_VPGEN_VFRSTAT_VFRD_MASK) अणु
			rsd = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (flr)
		usleep_range(10000, 20000);

	अगर (!rsd)
		dev_err(&pf->pdev->dev, "VF reset check timeout on VF %d\n",
			vf->vf_id);
	usleep_range(10000, 20000);

	/* On initial reset, we करोn't have any queues to disable */
	अगर (vf->lan_vsi_idx != 0)
		i40e_vsi_stop_rings(pf->vsi[vf->lan_vsi_idx]);

	i40e_cleanup_reset_vf(vf);

	i40e_flush(hw);
	clear_bit(__I40E_VF_DISABLE, pf->state);

	वापस true;
पूर्ण

/**
 * i40e_reset_all_vfs
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @flr: VFLR was issued or not
 *
 * Reset all allocated VFs in one go. First, tell the hardware to reset each
 * VF, then करो all the रुकोing in one chunk, and finally finish restoring each
 * VF after the रुको. This is useful during PF routines which need to reset
 * all VFs, as otherwise it must perक्रमm these resets in a serialized fashion.
 *
 * Returns true अगर any VFs were reset, and false otherwise.
 **/
bool i40e_reset_all_vfs(काष्ठा i40e_pf *pf, bool flr)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vf *vf;
	पूर्णांक i, v;
	u32 reg;

	/* If we करोn't have any VFs, then there is nothing to reset */
	अगर (!pf->num_alloc_vfs)
		वापस false;

	/* If VFs have been disabled, there is no need to reset */
	अगर (test_and_set_bit(__I40E_VF_DISABLE, pf->state))
		वापस false;

	/* Begin reset on all VFs at once */
	क्रम (v = 0; v < pf->num_alloc_vfs; v++)
		i40e_trigger_vf_reset(&pf->vf[v], flr);

	/* HW requires some समय to make sure it can flush the FIFO क्रम a VF
	 * when it resets it. Poll the VPGEN_VFRSTAT रेजिस्टर क्रम each VF in
	 * sequence to make sure that it has completed. We'll keep track of
	 * the VFs using a simple iterator that increments once that VF has
	 * finished resetting.
	 */
	क्रम (i = 0, v = 0; i < 10 && v < pf->num_alloc_vfs; i++) अणु
		usleep_range(10000, 20000);

		/* Check each VF in sequence, beginning with the VF to fail
		 * the previous check.
		 */
		जबतक (v < pf->num_alloc_vfs) अणु
			vf = &pf->vf[v];
			reg = rd32(hw, I40E_VPGEN_VFRSTAT(vf->vf_id));
			अगर (!(reg & I40E_VPGEN_VFRSTAT_VFRD_MASK))
				अवरोध;

			/* If the current VF has finished resetting, move on
			 * to the next VF in sequence.
			 */
			v++;
		पूर्ण
	पूर्ण

	अगर (flr)
		usleep_range(10000, 20000);

	/* Display a warning अगर at least one VF didn't manage to reset in
	 * समय, but जारी on with the operation.
	 */
	अगर (v < pf->num_alloc_vfs)
		dev_err(&pf->pdev->dev, "VF reset check timeout on VF %d\n",
			pf->vf[v].vf_id);
	usleep_range(10000, 20000);

	/* Begin disabling all the rings associated with VFs, but करो not रुको
	 * between each VF.
	 */
	क्रम (v = 0; v < pf->num_alloc_vfs; v++) अणु
		/* On initial reset, we करोn't have any queues to disable */
		अगर (pf->vf[v].lan_vsi_idx == 0)
			जारी;

		i40e_vsi_stop_rings_no_रुको(pf->vsi[pf->vf[v].lan_vsi_idx]);
	पूर्ण

	/* Now that we've notअगरied HW to disable all of the VF rings, रुको
	 * until they finish.
	 */
	क्रम (v = 0; v < pf->num_alloc_vfs; v++) अणु
		/* On initial reset, we करोn't have any queues to disable */
		अगर (pf->vf[v].lan_vsi_idx == 0)
			जारी;

		i40e_vsi_रुको_queues_disabled(pf->vsi[pf->vf[v].lan_vsi_idx]);
	पूर्ण

	/* Hw may need up to 50ms to finish disabling the RX queues. We
	 * minimize the रुको by delaying only once क्रम all VFs.
	 */
	mdelay(50);

	/* Finish the reset on each VF */
	क्रम (v = 0; v < pf->num_alloc_vfs; v++)
		i40e_cleanup_reset_vf(&pf->vf[v]);

	i40e_flush(hw);
	clear_bit(__I40E_VF_DISABLE, pf->state);

	वापस true;
पूर्ण

/**
 * i40e_मुक्त_vfs
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * मुक्त VF resources
 **/
व्योम i40e_मुक्त_vfs(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg_idx, bit_idx;
	पूर्णांक i, पंचांगp, vf_id;

	अगर (!pf->vf)
		वापस;

	set_bit(__I40E_VFS_RELEASING, pf->state);
	जबतक (test_and_set_bit(__I40E_VF_DISABLE, pf->state))
		usleep_range(1000, 2000);

	i40e_notअगरy_client_of_vf_enable(pf, 0);

	/* Disable IOV beक्रमe मुक्तing resources. This lets any VF drivers
	 * running in the host get themselves cleaned up beक्रमe we yank
	 * the carpet out from underneath their feet.
	 */
	अगर (!pci_vfs_asचिन्हित(pf->pdev))
		pci_disable_sriov(pf->pdev);
	अन्यथा
		dev_warn(&pf->pdev->dev, "VFs are assigned - not disabling SR-IOV\n");

	/* Amortize रुको समय by stopping all VFs at the same समय */
	क्रम (i = 0; i < pf->num_alloc_vfs; i++) अणु
		अगर (test_bit(I40E_VF_STATE_INIT, &pf->vf[i].vf_states))
			जारी;

		i40e_vsi_stop_rings_no_रुको(pf->vsi[pf->vf[i].lan_vsi_idx]);
	पूर्ण

	क्रम (i = 0; i < pf->num_alloc_vfs; i++) अणु
		अगर (test_bit(I40E_VF_STATE_INIT, &pf->vf[i].vf_states))
			जारी;

		i40e_vsi_रुको_queues_disabled(pf->vsi[pf->vf[i].lan_vsi_idx]);
	पूर्ण

	/* मुक्त up VF resources */
	पंचांगp = pf->num_alloc_vfs;
	pf->num_alloc_vfs = 0;
	क्रम (i = 0; i < पंचांगp; i++) अणु
		अगर (test_bit(I40E_VF_STATE_INIT, &pf->vf[i].vf_states))
			i40e_मुक्त_vf_res(&pf->vf[i]);
		/* disable qp mappings */
		i40e_disable_vf_mappings(&pf->vf[i]);
	पूर्ण

	kमुक्त(pf->vf);
	pf->vf = शून्य;

	/* This check is क्रम when the driver is unloaded जबतक VFs are
	 * asचिन्हित. Setting the number of VFs to 0 through sysfs is caught
	 * beक्रमe this function ever माला_लो called.
	 */
	अगर (!pci_vfs_asचिन्हित(pf->pdev)) अणु
		/* Acknowledge VFLR क्रम all VFS. Without this, VFs will fail to
		 * work correctly when SR-IOV माला_लो re-enabled.
		 */
		क्रम (vf_id = 0; vf_id < पंचांगp; vf_id++) अणु
			reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
			bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
			wr32(hw, I40E_GLGEN_VFLRSTAT(reg_idx), BIT(bit_idx));
		पूर्ण
	पूर्ण
	clear_bit(__I40E_VF_DISABLE, pf->state);
	clear_bit(__I40E_VFS_RELEASING, pf->state);
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
/**
 * i40e_alloc_vfs
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @num_alloc_vfs: number of VFs to allocate
 *
 * allocate VF resources
 **/
पूर्णांक i40e_alloc_vfs(काष्ठा i40e_pf *pf, u16 num_alloc_vfs)
अणु
	काष्ठा i40e_vf *vfs;
	पूर्णांक i, ret = 0;

	/* Disable पूर्णांकerrupt 0 so we करोn't try to handle the VFLR. */
	i40e_irq_dynamic_disable_icr0(pf);

	/* Check to see अगर we're just allocating resources क्रम extant VFs */
	अगर (pci_num_vf(pf->pdev) != num_alloc_vfs) अणु
		ret = pci_enable_sriov(pf->pdev, num_alloc_vfs);
		अगर (ret) अणु
			pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
			pf->num_alloc_vfs = 0;
			जाओ err_iov;
		पूर्ण
	पूर्ण
	/* allocate memory */
	vfs = kसुस्मृति(num_alloc_vfs, माप(काष्ठा i40e_vf), GFP_KERNEL);
	अगर (!vfs) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण
	pf->vf = vfs;

	/* apply शेष profile */
	क्रम (i = 0; i < num_alloc_vfs; i++) अणु
		vfs[i].pf = pf;
		vfs[i].parent_type = I40E_SWITCH_ELEMENT_TYPE_VEB;
		vfs[i].vf_id = i;

		/* assign शेष capabilities */
		set_bit(I40E_VIRTCHNL_VF_CAP_L2, &vfs[i].vf_caps);
		vfs[i].spoofchk = true;

		set_bit(I40E_VF_STATE_PRE_ENABLE, &vfs[i].vf_states);

	पूर्ण
	pf->num_alloc_vfs = num_alloc_vfs;

	/* VF resources get allocated during reset */
	i40e_reset_all_vfs(pf, false);

	i40e_notअगरy_client_of_vf_enable(pf, num_alloc_vfs);

err_alloc:
	अगर (ret)
		i40e_मुक्त_vfs(pf);
err_iov:
	/* Re-enable पूर्णांकerrupt 0. */
	i40e_irq_dynamic_enable_icr0(pf);
	वापस ret;
पूर्ण

#पूर्ण_अगर
/**
 * i40e_pci_sriov_enable
 * @pdev: poपूर्णांकer to a pci_dev काष्ठाure
 * @num_vfs: number of VFs to allocate
 *
 * Enable or change the number of VFs
 **/
अटल पूर्णांक i40e_pci_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);
	पूर्णांक pre_existing_vfs = pci_num_vf(pdev);
	पूर्णांक err = 0;

	अगर (test_bit(__I40E_TESTING, pf->state)) अणु
		dev_warn(&pdev->dev,
			 "Cannot enable SR-IOV virtual functions while the device is undergoing diagnostic testing\n");
		err = -EPERM;
		जाओ err_out;
	पूर्ण

	अगर (pre_existing_vfs && pre_existing_vfs != num_vfs)
		i40e_मुक्त_vfs(pf);
	अन्यथा अगर (pre_existing_vfs && pre_existing_vfs == num_vfs)
		जाओ out;

	अगर (num_vfs > pf->num_req_vfs) अणु
		dev_warn(&pdev->dev, "Unable to enable %d VFs. Limited to %d VFs due to device resource constraints.\n",
			 num_vfs, pf->num_req_vfs);
		err = -EPERM;
		जाओ err_out;
	पूर्ण

	dev_info(&pdev->dev, "Allocating %d VFs.\n", num_vfs);
	err = i40e_alloc_vfs(pf, num_vfs);
	अगर (err) अणु
		dev_warn(&pdev->dev, "Failed to enable SR-IOV: %d\n", err);
		जाओ err_out;
	पूर्ण

out:
	वापस num_vfs;

err_out:
	वापस err;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * i40e_pci_sriov_configure
 * @pdev: poपूर्णांकer to a pci_dev काष्ठाure
 * @num_vfs: number of VFs to allocate
 *
 * Enable or change the number of VFs. Called when the user updates the number
 * of VFs in sysfs.
 **/
पूर्णांक i40e_pci_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा i40e_pf *pf = pci_get_drvdata(pdev);
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (num_vfs) अणु
		अगर (!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) अणु
			pf->flags |= I40E_FLAG_VEB_MODE_ENABLED;
			i40e_करो_reset_safe(pf, I40E_PF_RESET_AND_REBUILD_FLAG);
		पूर्ण
		ret = i40e_pci_sriov_enable(pdev, num_vfs);
		जाओ sriov_configure_out;
	पूर्ण

	अगर (!pci_vfs_asचिन्हित(pf->pdev)) अणु
		i40e_मुक्त_vfs(pf);
		pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
		i40e_करो_reset_safe(pf, I40E_PF_RESET_AND_REBUILD_FLAG);
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev, "Unable to free VFs because some are assigned to VMs.\n");
		ret = -EINVAL;
		जाओ sriov_configure_out;
	पूर्ण
sriov_configure_out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/***********************भव channel routines******************/

/**
 * i40e_vc_send_msg_to_vf
 * @vf: poपूर्णांकer to the VF info
 * @v_opcode: भव channel opcode
 * @v_retval: भव channel वापस value
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 *
 * send msg to VF
 **/
अटल पूर्णांक i40e_vc_send_msg_to_vf(काष्ठा i40e_vf *vf, u32 v_opcode,
				  u32 v_retval, u8 *msg, u16 msglen)
अणु
	काष्ठा i40e_pf *pf;
	काष्ठा i40e_hw *hw;
	पूर्णांक असल_vf_id;
	i40e_status aq_ret;

	/* validate the request */
	अगर (!vf || vf->vf_id >= vf->pf->num_alloc_vfs)
		वापस -EINVAL;

	pf = vf->pf;
	hw = &pf->hw;
	असल_vf_id = vf->vf_id + hw->func_caps.vf_base_id;

	/* single place to detect unsuccessful वापस values */
	अगर (v_retval) अणु
		vf->num_invalid_msgs++;
		dev_info(&pf->pdev->dev, "VF %d failed opcode %d, retval: %d\n",
			 vf->vf_id, v_opcode, v_retval);
		अगर (vf->num_invalid_msgs >
		    I40E_DEFAULT_NUM_INVALID_MSGS_ALLOWED) अणु
			dev_err(&pf->pdev->dev,
				"Number of invalid messages exceeded for VF %d\n",
				vf->vf_id);
			dev_err(&pf->pdev->dev, "Use PF Control I/F to enable the VF\n");
			set_bit(I40E_VF_STATE_DISABLED, &vf->vf_states);
		पूर्ण
	पूर्ण अन्यथा अणु
		vf->num_valid_msgs++;
		/* reset the invalid counter, अगर a valid message is received. */
		vf->num_invalid_msgs = 0;
	पूर्ण

	aq_ret = i40e_aq_send_msg_to_vf(hw, असल_vf_id,	v_opcode, v_retval,
					msg, msglen, शून्य);
	अगर (aq_ret) अणु
		dev_info(&pf->pdev->dev,
			 "Unable to send the message to VF %d aq_err %d\n",
			 vf->vf_id, pf->hw.aq.asq_last_status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vc_send_resp_to_vf
 * @vf: poपूर्णांकer to the VF info
 * @opcode: operation code
 * @retval: वापस value
 *
 * send resp msg to VF
 **/
अटल पूर्णांक i40e_vc_send_resp_to_vf(काष्ठा i40e_vf *vf,
				   क्रमागत virtchnl_ops opcode,
				   i40e_status retval)
अणु
	वापस i40e_vc_send_msg_to_vf(vf, opcode, retval, शून्य, 0);
पूर्ण

/**
 * i40e_vc_get_version_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to request the API version used by the PF
 **/
अटल पूर्णांक i40e_vc_get_version_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_version_info info = अणु
		VIRTCHNL_VERSION_MAJOR, VIRTCHNL_VERSION_MINOR
	पूर्ण;

	vf->vf_ver = *(काष्ठा virtchnl_version_info *)msg;
	/* VFs running the 1.0 API expect to get 1.0 back or they will cry. */
	अगर (VF_IS_V10(&vf->vf_ver))
		info.minor = VIRTCHNL_VERSION_MINOR_NO_VF_CAPS;
	वापस i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_VERSION,
				      I40E_SUCCESS, (u8 *)&info,
				      माप(काष्ठा virtchnl_version_info));
पूर्ण

/**
 * i40e_del_qch - delete all the additional VSIs created as a part of ADq
 * @vf: poपूर्णांकer to VF काष्ठाure
 **/
अटल व्योम i40e_del_qch(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	पूर्णांक i;

	/* first element in the array beदीर्घs to primary VF VSI and we shouldn't
	 * delete it. We should however delete the rest of the VSIs created
	 */
	क्रम (i = 1; i < vf->num_tc; i++) अणु
		अगर (vf->ch[i].vsi_idx) अणु
			i40e_vsi_release(pf->vsi[vf->ch[i].vsi_idx]);
			vf->ch[i].vsi_idx = 0;
			vf->ch[i].vsi_id = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_vc_get_vf_resources_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to request its resources
 **/
अटल पूर्णांक i40e_vc_get_vf_resources_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_vf_resource *vfres = शून्य;
	काष्ठा i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;
	काष्ठा i40e_vsi *vsi;
	पूर्णांक num_vsis = 1;
	माप_प्रकार len = 0;
	पूर्णांक ret;

	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	len = काष्ठा_size(vfres, vsi_res, num_vsis);
	vfres = kzalloc(len, GFP_KERNEL);
	अगर (!vfres) अणु
		aq_ret = I40E_ERR_NO_MEMORY;
		len = 0;
		जाओ err;
	पूर्ण
	अगर (VF_IS_V11(&vf->vf_ver))
		vf->driver_caps = *(u32 *)msg;
	अन्यथा
		vf->driver_caps = VIRTCHNL_VF_OFFLOAD_L2 |
				  VIRTCHNL_VF_OFFLOAD_RSS_REG |
				  VIRTCHNL_VF_OFFLOAD_VLAN;

	vfres->vf_cap_flags = VIRTCHNL_VF_OFFLOAD_L2;
	vfres->vf_cap_flags |= VIRTCHNL_VF_CAP_ADV_LINK_SPEED;
	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vsi->info.pvid)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_VLAN;

	अगर (i40e_vf_client_capable(pf, vf->vf_id) &&
	    (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_IWARP)) अणु
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_IWARP;
		set_bit(I40E_VF_STATE_IWARPENA, &vf->vf_states);
	पूर्ण अन्यथा अणु
		clear_bit(I40E_VF_STATE_IWARPENA, &vf->vf_states);
	पूर्ण

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RSS_PF) अणु
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_PF;
	पूर्ण अन्यथा अणु
		अगर ((pf->hw_features & I40E_HW_RSS_AQ_CAPABLE) &&
		    (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RSS_AQ))
			vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_AQ;
		अन्यथा
			vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_REG;
	पूर्ण

	अगर (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE) अणु
		अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2)
			vfres->vf_cap_flags |=
				VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2;
	पूर्ण

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ENCAP)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_ENCAP;

	अगर ((pf->hw_features & I40E_HW_OUTER_UDP_CSUM_CAPABLE) &&
	    (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM))
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RX_POLLING) अणु
		अगर (pf->flags & I40E_FLAG_MFP_ENABLED) अणु
			dev_err(&pf->pdev->dev,
				"VF %d requested polling mode: this feature is supported only when the device is running in single function per port (SFP) mode\n",
				 vf->vf_id);
			aq_ret = I40E_ERR_PARAM;
			जाओ err;
		पूर्ण
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RX_POLLING;
	पूर्ण

	अगर (pf->hw_features & I40E_HW_WB_ON_ITR_CAPABLE) अणु
		अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_WB_ON_ITR)
			vfres->vf_cap_flags |=
					VIRTCHNL_VF_OFFLOAD_WB_ON_ITR;
	पूर्ण

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_REQ_QUEUES)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_REQ_QUEUES;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ADQ)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_ADQ;

	vfres->num_vsis = num_vsis;
	vfres->num_queue_pairs = vf->num_queue_pairs;
	vfres->max_vectors = pf->hw.func_caps.num_msix_vectors_vf;
	vfres->rss_key_size = I40E_HKEY_ARRAY_SIZE;
	vfres->rss_lut_size = I40E_VF_HLUT_ARRAY_SIZE;

	अगर (vf->lan_vsi_idx) अणु
		vfres->vsi_res[0].vsi_id = vf->lan_vsi_id;
		vfres->vsi_res[0].vsi_type = VIRTCHNL_VSI_SRIOV;
		vfres->vsi_res[0].num_queue_pairs = vsi->alloc_queue_pairs;
		/* VFs only use TC 0 */
		vfres->vsi_res[0].qset_handle
					  = le16_to_cpu(vsi->info.qs_handle[0]);
		ether_addr_copy(vfres->vsi_res[0].शेष_mac_addr,
				vf->शेष_lan_addr.addr);
	पूर्ण
	set_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states);

err:
	/* send the response back to the VF */
	ret = i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_GET_VF_RESOURCES,
				     aq_ret, (u8 *)vfres, len);

	kमुक्त(vfres);
	वापस ret;
पूर्ण

/**
 * i40e_vc_reset_vf_msg
 * @vf: poपूर्णांकer to the VF info
 *
 * called from the VF to reset itself,
 * unlike other virtchnl messages, PF driver
 * करोesn't send the response back to the VF
 **/
अटल व्योम i40e_vc_reset_vf_msg(काष्ठा i40e_vf *vf)
अणु
	अगर (test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
		i40e_reset_vf(vf, false);
पूर्ण

/**
 * i40e_vc_config_promiscuous_mode_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to configure the promiscuous mode of
 * VF vsis
 **/
अटल पूर्णांक i40e_vc_config_promiscuous_mode_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_promisc_info *info =
	    (काष्ठा virtchnl_promisc_info *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;
	bool allmulti = false;
	bool alluni = false;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err_out;
	पूर्ण
	अगर (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps)) अणु
		dev_err(&pf->pdev->dev,
			"Unprivileged VF %d is attempting to configure promiscuous mode\n",
			vf->vf_id);

		/* Lie to the VF on purpose, because this is an error we can
		 * ignore. Unprivileged VF is not a भव channel error.
		 */
		aq_ret = 0;
		जाओ err_out;
	पूर्ण

	अगर (info->flags > I40E_MAX_VF_PROMISC_FLAGS) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err_out;
	पूर्ण

	अगर (!i40e_vc_isvalid_vsi_id(vf, info->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err_out;
	पूर्ण

	/* Multicast promiscuous handling*/
	अगर (info->flags & FLAG_VF_MULTICAST_PROMISC)
		allmulti = true;

	अगर (info->flags & FLAG_VF_UNICAST_PROMISC)
		alluni = true;
	aq_ret = i40e_config_vf_promiscuous_mode(vf, info->vsi_id, allmulti,
						 alluni);
	अगर (aq_ret)
		जाओ err_out;

	अगर (allmulti) अणु
		अगर (!test_and_set_bit(I40E_VF_STATE_MC_PROMISC,
				      &vf->vf_states))
			dev_info(&pf->pdev->dev,
				 "VF %d successfully set multicast promiscuous mode\n",
				 vf->vf_id);
	पूर्ण अन्यथा अगर (test_and_clear_bit(I40E_VF_STATE_MC_PROMISC,
				      &vf->vf_states))
		dev_info(&pf->pdev->dev,
			 "VF %d successfully unset multicast promiscuous mode\n",
			 vf->vf_id);

	अगर (alluni) अणु
		अगर (!test_and_set_bit(I40E_VF_STATE_UC_PROMISC,
				      &vf->vf_states))
			dev_info(&pf->pdev->dev,
				 "VF %d successfully set unicast promiscuous mode\n",
				 vf->vf_id);
	पूर्ण अन्यथा अगर (test_and_clear_bit(I40E_VF_STATE_UC_PROMISC,
				      &vf->vf_states))
		dev_info(&pf->pdev->dev,
			 "VF %d successfully unset unicast promiscuous mode\n",
			 vf->vf_id);

err_out:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf,
				       VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_config_queues_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to configure the rx/tx
 * queues
 **/
अटल पूर्णांक i40e_vc_config_queues_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_vsi_queue_config_info *qci =
	    (काष्ठा virtchnl_vsi_queue_config_info *)msg;
	काष्ठा virtchnl_queue_pair_info *qpi;
	काष्ठा i40e_pf *pf = vf->pf;
	u16 vsi_id, vsi_queue_id = 0;
	u16 num_qps_all = 0;
	i40e_status aq_ret = 0;
	पूर्णांक i, j = 0, idx = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!i40e_vc_isvalid_vsi_id(vf, qci->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (qci->num_queue_pairs > I40E_MAX_VF_QUEUES) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (vf->adq_enabled) अणु
		क्रम (i = 0; i < I40E_MAX_VF_VSI; i++)
			num_qps_all += vf->ch[i].num_qps;
		अगर (num_qps_all != qci->num_queue_pairs) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ error_param;
		पूर्ण
	पूर्ण

	vsi_id = qci->vsi_id;

	क्रम (i = 0; i < qci->num_queue_pairs; i++) अणु
		qpi = &qci->qpair[i];

		अगर (!vf->adq_enabled) अणु
			अगर (!i40e_vc_isvalid_queue_id(vf, vsi_id,
						      qpi->txq.queue_id)) अणु
				aq_ret = I40E_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			vsi_queue_id = qpi->txq.queue_id;

			अगर (qpi->txq.vsi_id != qci->vsi_id ||
			    qpi->rxq.vsi_id != qci->vsi_id ||
			    qpi->rxq.queue_id != vsi_queue_id) अणु
				aq_ret = I40E_ERR_PARAM;
				जाओ error_param;
			पूर्ण
		पूर्ण

		अगर (vf->adq_enabled) अणु
			अगर (idx >= ARRAY_SIZE(vf->ch)) अणु
				aq_ret = I40E_ERR_NO_AVAILABLE_VSI;
				जाओ error_param;
			पूर्ण
			vsi_id = vf->ch[idx].vsi_id;
		पूर्ण

		अगर (i40e_config_vsi_rx_queue(vf, vsi_id, vsi_queue_id,
					     &qpi->rxq) ||
		    i40e_config_vsi_tx_queue(vf, vsi_id, vsi_queue_id,
					     &qpi->txq)) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		/* For ADq there can be up to 4 VSIs with max 4 queues each.
		 * VF करोes not know about these additional VSIs and all
		 * it cares is about its own queues. PF configures these queues
		 * to its appropriate VSIs based on TC mapping
		 */
		अगर (vf->adq_enabled) अणु
			अगर (idx >= ARRAY_SIZE(vf->ch)) अणु
				aq_ret = I40E_ERR_NO_AVAILABLE_VSI;
				जाओ error_param;
			पूर्ण
			अगर (j == (vf->ch[idx].num_qps - 1)) अणु
				idx++;
				j = 0; /* resetting the queue count */
				vsi_queue_id = 0;
			पूर्ण अन्यथा अणु
				j++;
				vsi_queue_id++;
			पूर्ण
		पूर्ण
	पूर्ण
	/* set vsi num_queue_pairs in use to num configured by VF */
	अगर (!vf->adq_enabled) अणु
		pf->vsi[vf->lan_vsi_idx]->num_queue_pairs =
			qci->num_queue_pairs;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < vf->num_tc; i++)
			pf->vsi[vf->ch[i].vsi_idx]->num_queue_pairs =
			       vf->ch[i].num_qps;
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES,
				       aq_ret);
पूर्ण

/**
 * i40e_validate_queue_map - check queue map is valid
 * @vf: the VF काष्ठाure poपूर्णांकer
 * @vsi_id: vsi id
 * @queuemap: Tx or Rx queue map
 *
 * check अगर Tx or Rx queue map is valid
 **/
अटल पूर्णांक i40e_validate_queue_map(काष्ठा i40e_vf *vf, u16 vsi_id,
				   अचिन्हित दीर्घ queuemap)
अणु
	u16 vsi_queue_id, queue_id;

	क्रम_each_set_bit(vsi_queue_id, &queuemap, I40E_MAX_VSI_QP) अणु
		अगर (vf->adq_enabled) अणु
			vsi_id = vf->ch[vsi_queue_id / I40E_MAX_VF_VSI].vsi_id;
			queue_id = (vsi_queue_id % I40E_DEFAULT_QUEUES_PER_VF);
		पूर्ण अन्यथा अणु
			queue_id = vsi_queue_id;
		पूर्ण

		अगर (!i40e_vc_isvalid_queue_id(vf, vsi_id, queue_id))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_vc_config_irq_map_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to configure the irq to
 * queue map
 **/
अटल पूर्णांक i40e_vc_config_irq_map_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_irq_map_info *irqmap_info =
	    (काष्ठा virtchnl_irq_map_info *)msg;
	काष्ठा virtchnl_vector_map *map;
	u16 vsi_id;
	i40e_status aq_ret = 0;
	पूर्णांक i;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (irqmap_info->num_vectors >
	    vf->pf->hw.func_caps.num_msix_vectors_vf) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < irqmap_info->num_vectors; i++) अणु
		map = &irqmap_info->vecmap[i];
		/* validate msg params */
		अगर (!i40e_vc_isvalid_vector_id(vf, map->vector_id) ||
		    !i40e_vc_isvalid_vsi_id(vf, map->vsi_id)) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ error_param;
		पूर्ण
		vsi_id = map->vsi_id;

		अगर (i40e_validate_queue_map(vf, vsi_id, map->rxq_map)) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		अगर (i40e_validate_queue_map(vf, vsi_id, map->txq_map)) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		i40e_config_irq_link_list(vf, vsi_id, map);
	पूर्ण
error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_IRQ_MAP,
				       aq_ret);
पूर्ण

/**
 * i40e_ctrl_vf_tx_rings
 * @vsi: the SRIOV VSI being configured
 * @q_map: bit map of the queues to be enabled
 * @enable: start or stop the queue
 **/
अटल पूर्णांक i40e_ctrl_vf_tx_rings(काष्ठा i40e_vsi *vsi, अचिन्हित दीर्घ q_map,
				 bool enable)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret = 0;
	u16 q_id;

	क्रम_each_set_bit(q_id, &q_map, I40E_MAX_VF_QUEUES) अणु
		ret = i40e_control_रुको_tx_q(vsi->seid, pf,
					     vsi->base_queue + q_id,
					     false /*is xdp*/, enable);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40e_ctrl_vf_rx_rings
 * @vsi: the SRIOV VSI being configured
 * @q_map: bit map of the queues to be enabled
 * @enable: start or stop the queue
 **/
अटल पूर्णांक i40e_ctrl_vf_rx_rings(काष्ठा i40e_vsi *vsi, अचिन्हित दीर्घ q_map,
				 bool enable)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret = 0;
	u16 q_id;

	क्रम_each_set_bit(q_id, &q_map, I40E_MAX_VF_QUEUES) अणु
		ret = i40e_control_रुको_rx_q(pf, vsi->base_queue + q_id,
					     enable);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40e_vc_validate_vqs_biपंचांगaps - validate Rx/Tx queue biपंचांगaps from VIRTHCHNL
 * @vqs: virtchnl_queue_select काष्ठाure containing biपंचांगaps to validate
 *
 * Returns true अगर validation was successful, अन्यथा false.
 */
अटल bool i40e_vc_validate_vqs_biपंचांगaps(काष्ठा virtchnl_queue_select *vqs)
अणु
	अगर ((!vqs->rx_queues && !vqs->tx_queues) ||
	    vqs->rx_queues >= BIT(I40E_MAX_VF_QUEUES) ||
	    vqs->tx_queues >= BIT(I40E_MAX_VF_QUEUES))
		वापस false;

	वापस true;
पूर्ण

/**
 * i40e_vc_enable_queues_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to enable all or specअगरic queue(s)
 **/
अटल पूर्णांक i40e_vc_enable_queues_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_queue_select *vqs =
	    (काष्ठा virtchnl_queue_select *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;
	पूर्णांक i;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!i40e_vc_isvalid_vsi_id(vf, vqs->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!i40e_vc_validate_vqs_biपंचांगaps(vqs)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	/* Use the queue bit map sent by the VF */
	अगर (i40e_ctrl_vf_rx_rings(pf->vsi[vf->lan_vsi_idx], vqs->rx_queues,
				  true)) अणु
		aq_ret = I40E_ERR_TIMEOUT;
		जाओ error_param;
	पूर्ण
	अगर (i40e_ctrl_vf_tx_rings(pf->vsi[vf->lan_vsi_idx], vqs->tx_queues,
				  true)) अणु
		aq_ret = I40E_ERR_TIMEOUT;
		जाओ error_param;
	पूर्ण

	/* need to start the rings क्रम additional ADq VSI's as well */
	अगर (vf->adq_enabled) अणु
		/* zero beदीर्घs to LAN VSI */
		क्रम (i = 1; i < vf->num_tc; i++) अणु
			अगर (i40e_vsi_start_rings(pf->vsi[vf->ch[i].vsi_idx]))
				aq_ret = I40E_ERR_TIMEOUT;
		पूर्ण
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ENABLE_QUEUES,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_disable_queues_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to disable all or specअगरic
 * queue(s)
 **/
अटल पूर्णांक i40e_vc_disable_queues_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_queue_select *vqs =
	    (काष्ठा virtchnl_queue_select *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!i40e_vc_isvalid_vsi_id(vf, vqs->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!i40e_vc_validate_vqs_biपंचांगaps(vqs)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	/* Use the queue bit map sent by the VF */
	अगर (i40e_ctrl_vf_tx_rings(pf->vsi[vf->lan_vsi_idx], vqs->tx_queues,
				  false)) अणु
		aq_ret = I40E_ERR_TIMEOUT;
		जाओ error_param;
	पूर्ण
	अगर (i40e_ctrl_vf_rx_rings(pf->vsi[vf->lan_vsi_idx], vqs->rx_queues,
				  false)) अणु
		aq_ret = I40E_ERR_TIMEOUT;
		जाओ error_param;
	पूर्ण
error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DISABLE_QUEUES,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_request_queues_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * VFs get a शेष number of queues but can use this message to request a
 * dअगरferent number.  If the request is successful, PF will reset the VF and
 * वापस 0.  If unsuccessful, PF will send message inक्रमming VF of number of
 * available queues and वापस result of sending VF a message.
 **/
अटल पूर्णांक i40e_vc_request_queues_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_vf_res_request *vfres =
		(काष्ठा virtchnl_vf_res_request *)msg;
	u16 req_pairs = vfres->num_queue_pairs;
	u8 cur_pairs = vf->num_queue_pairs;
	काष्ठा i40e_pf *pf = vf->pf;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
		वापस -EINVAL;

	अगर (req_pairs > I40E_MAX_VF_QUEUES) अणु
		dev_err(&pf->pdev->dev,
			"VF %d tried to request more than %d queues.\n",
			vf->vf_id,
			I40E_MAX_VF_QUEUES);
		vfres->num_queue_pairs = I40E_MAX_VF_QUEUES;
	पूर्ण अन्यथा अगर (req_pairs - cur_pairs > pf->queues_left) अणु
		dev_warn(&pf->pdev->dev,
			 "VF %d requested %d more queues, but only %d left.\n",
			 vf->vf_id,
			 req_pairs - cur_pairs,
			 pf->queues_left);
		vfres->num_queue_pairs = pf->queues_left + cur_pairs;
	पूर्ण अन्यथा अणु
		/* successful request */
		vf->num_req_queues = req_pairs;
		i40e_vc_notअगरy_vf_reset(vf);
		i40e_reset_vf(vf, false);
		वापस 0;
	पूर्ण

	वापस i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_REQUEST_QUEUES, 0,
				      (u8 *)vfres, माप(*vfres));
पूर्ण

/**
 * i40e_vc_get_stats_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to get vsi stats
 **/
अटल पूर्णांक i40e_vc_get_stats_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_queue_select *vqs =
	    (काष्ठा virtchnl_queue_select *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_eth_stats stats;
	i40e_status aq_ret = 0;
	काष्ठा i40e_vsi *vsi;

	स_रखो(&stats, 0, माप(काष्ठा i40e_eth_stats));

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!i40e_vc_isvalid_vsi_id(vf, vqs->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vsi) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण
	i40e_update_eth_stats(vsi);
	stats = vsi->eth_stats;

error_param:
	/* send the response back to the VF */
	वापस i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_GET_STATS, aq_ret,
				      (u8 *)&stats, माप(stats));
पूर्ण

/* If the VF is not trusted restrict the number of MAC/VLAN it can program
 * MAC filters: 16 क्रम multicast, 1 क्रम MAC, 1 क्रम broadcast
 */
#घोषणा I40E_VC_MAX_MAC_ADDR_PER_VF (16 + 1 + 1)
#घोषणा I40E_VC_MAX_VLAN_PER_VF 16

/**
 * i40e_check_vf_permission
 * @vf: poपूर्णांकer to the VF info
 * @al: MAC address list from virtchnl
 *
 * Check that the given list of MAC addresses is allowed. Will वापस -EPERM
 * अगर any address in the list is not valid. Checks the following conditions:
 *
 * 1) broadcast and zero addresses are never valid
 * 2) unicast addresses are not allowed अगर the VMM has administratively set
 *    the VF MAC address, unless the VF is marked as privileged.
 * 3) There is enough space to add all the addresses.
 *
 * Note that to guarantee consistency, it is expected this function be called
 * जबतक holding the mac_filter_hash_lock, as otherwise the current number of
 * addresses might not be accurate.
 **/
अटल अंतरभूत पूर्णांक i40e_check_vf_permission(काष्ठा i40e_vf *vf,
					   काष्ठा virtchnl_ether_addr_list *al)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = pf->vsi[vf->lan_vsi_idx];
	पूर्णांक mac2add_cnt = 0;
	पूर्णांक i;

	क्रम (i = 0; i < al->num_elements; i++) अणु
		काष्ठा i40e_mac_filter *f;
		u8 *addr = al->list[i].addr;

		अगर (is_broadcast_ether_addr(addr) ||
		    is_zero_ether_addr(addr)) अणु
			dev_err(&pf->pdev->dev, "invalid VF MAC addr %pM\n",
				addr);
			वापस I40E_ERR_INVALID_MAC_ADDR;
		पूर्ण

		/* If the host VMM administrator has set the VF MAC address
		 * administratively via the nकरो_set_vf_mac command then deny
		 * permission to the VF to add or delete unicast MAC addresses.
		 * Unless the VF is privileged and then it can करो whatever.
		 * The VF may request to set the MAC address filter alपढ़ोy
		 * asचिन्हित to it so करो not वापस an error in that हाल.
		 */
		अगर (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps) &&
		    !is_multicast_ether_addr(addr) && vf->pf_set_mac &&
		    !ether_addr_equal(addr, vf->शेष_lan_addr.addr)) अणु
			dev_err(&pf->pdev->dev,
				"VF attempting to override administratively set MAC address, bring down and up the VF interface to resume normal operation\n");
			वापस -EPERM;
		पूर्ण

		/*count filters that really will be added*/
		f = i40e_find_mac(vsi, addr);
		अगर (!f)
			++mac2add_cnt;
	पूर्ण

	/* If this VF is not privileged, then we can't add more than a limited
	 * number of addresses. Check to make sure that the additions करो not
	 * push us over the limit.
	 */
	अगर (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps) &&
	    (i40e_count_filters(vsi) + mac2add_cnt) >
		    I40E_VC_MAX_MAC_ADDR_PER_VF) अणु
		dev_err(&pf->pdev->dev,
			"Cannot add more MAC addresses, VF is not trusted, switch the VF to trusted to add more functionality\n");
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_vc_add_mac_addr_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * add guest mac address filter
 **/
अटल पूर्णांक i40e_vc_add_mac_addr_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_ether_addr_list *al =
	    (काष्ठा virtchnl_ether_addr_list *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status ret = 0;
	पूर्णांक i;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, al->vsi_id)) अणु
		ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = pf->vsi[vf->lan_vsi_idx];

	/* Lock once, because all function inside क्रम loop accesses VSI's
	 * MAC filter list which needs to be रक्षित using same lock.
	 */
	spin_lock_bh(&vsi->mac_filter_hash_lock);

	ret = i40e_check_vf_permission(vf, al);
	अगर (ret) अणु
		spin_unlock_bh(&vsi->mac_filter_hash_lock);
		जाओ error_param;
	पूर्ण

	/* add new addresses to the list */
	क्रम (i = 0; i < al->num_elements; i++) अणु
		काष्ठा i40e_mac_filter *f;

		f = i40e_find_mac(vsi, al->list[i].addr);
		अगर (!f) अणु
			f = i40e_add_mac_filter(vsi, al->list[i].addr);

			अगर (!f) अणु
				dev_err(&pf->pdev->dev,
					"Unable to add MAC filter %pM for VF %d\n",
					al->list[i].addr, vf->vf_id);
				ret = I40E_ERR_PARAM;
				spin_unlock_bh(&vsi->mac_filter_hash_lock);
				जाओ error_param;
			पूर्ण
			अगर (is_valid_ether_addr(al->list[i].addr) &&
			    is_zero_ether_addr(vf->शेष_lan_addr.addr))
				ether_addr_copy(vf->शेष_lan_addr.addr,
						al->list[i].addr);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* program the updated filter list */
	ret = i40e_sync_vsi_filters(vsi);
	अगर (ret)
		dev_err(&pf->pdev->dev, "Unable to program VF %d MAC filters, error %d\n",
			vf->vf_id, ret);

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ADD_ETH_ADDR,
				       ret);
पूर्ण

/**
 * i40e_vc_del_mac_addr_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * हटाओ guest mac address filter
 **/
अटल पूर्णांक i40e_vc_del_mac_addr_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_ether_addr_list *al =
	    (काष्ठा virtchnl_ether_addr_list *)msg;
	bool was_unimac_deleted = false;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status ret = 0;
	पूर्णांक i;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, al->vsi_id)) अणु
		ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < al->num_elements; i++) अणु
		अगर (is_broadcast_ether_addr(al->list[i].addr) ||
		    is_zero_ether_addr(al->list[i].addr)) अणु
			dev_err(&pf->pdev->dev, "Invalid MAC addr %pM for VF %d\n",
				al->list[i].addr, vf->vf_id);
			ret = I40E_ERR_INVALID_MAC_ADDR;
			जाओ error_param;
		पूर्ण
		अगर (ether_addr_equal(al->list[i].addr, vf->शेष_lan_addr.addr))
			was_unimac_deleted = true;
	पूर्ण
	vsi = pf->vsi[vf->lan_vsi_idx];

	spin_lock_bh(&vsi->mac_filter_hash_lock);
	/* delete addresses from the list */
	क्रम (i = 0; i < al->num_elements; i++)
		अगर (i40e_del_mac_filter(vsi, al->list[i].addr)) अणु
			ret = I40E_ERR_INVALID_MAC_ADDR;
			spin_unlock_bh(&vsi->mac_filter_hash_lock);
			जाओ error_param;
		पूर्ण

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* program the updated filter list */
	ret = i40e_sync_vsi_filters(vsi);
	अगर (ret)
		dev_err(&pf->pdev->dev, "Unable to program VF %d MAC filters, error %d\n",
			vf->vf_id, ret);

	अगर (vf->trusted && was_unimac_deleted) अणु
		काष्ठा i40e_mac_filter *f;
		काष्ठा hlist_node *h;
		u8 *macaddr = शून्य;
		पूर्णांक bkt;

		/* set last unicast mac address as शेष */
		spin_lock_bh(&vsi->mac_filter_hash_lock);
		hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist) अणु
			अगर (is_valid_ether_addr(f->macaddr))
				macaddr = f->macaddr;
		पूर्ण
		अगर (macaddr)
			ether_addr_copy(vf->शेष_lan_addr.addr, macaddr);
		spin_unlock_bh(&vsi->mac_filter_hash_lock);
	पूर्ण
error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DEL_ETH_ADDR, ret);
पूर्ण

/**
 * i40e_vc_add_vlan_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * program guest vlan id
 **/
अटल पूर्णांक i40e_vc_add_vlan_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_vlan_filter_list *vfl =
	    (काष्ठा virtchnl_vlan_filter_list *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status aq_ret = 0;
	पूर्णांक i;

	अगर ((vf->num_vlan >= I40E_VC_MAX_VLAN_PER_VF) &&
	    !test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps)) अणु
		dev_err(&pf->pdev->dev,
			"VF is not trusted, switch the VF to trusted to add more VLAN addresses\n");
		जाओ error_param;
	पूर्ण
	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vfl->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < vfl->num_elements; i++) अणु
		अगर (vfl->vlan_id[i] > I40E_MAX_VLANID) अणु
			aq_ret = I40E_ERR_PARAM;
			dev_err(&pf->pdev->dev,
				"invalid VF VLAN id %d\n", vfl->vlan_id[i]);
			जाओ error_param;
		पूर्ण
	पूर्ण
	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (vsi->info.pvid) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	i40e_vlan_stripping_enable(vsi);
	क्रम (i = 0; i < vfl->num_elements; i++) अणु
		/* add new VLAN filter */
		पूर्णांक ret = i40e_vsi_add_vlan(vsi, vfl->vlan_id[i]);
		अगर (!ret)
			vf->num_vlan++;

		अगर (test_bit(I40E_VF_STATE_UC_PROMISC, &vf->vf_states))
			i40e_aq_set_vsi_uc_promisc_on_vlan(&pf->hw, vsi->seid,
							   true,
							   vfl->vlan_id[i],
							   शून्य);
		अगर (test_bit(I40E_VF_STATE_MC_PROMISC, &vf->vf_states))
			i40e_aq_set_vsi_mc_promisc_on_vlan(&pf->hw, vsi->seid,
							   true,
							   vfl->vlan_id[i],
							   शून्य);

		अगर (ret)
			dev_err(&pf->pdev->dev,
				"Unable to add VLAN filter %d for VF %d, error %d\n",
				vfl->vlan_id[i], vf->vf_id, ret);
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ADD_VLAN, aq_ret);
पूर्ण

/**
 * i40e_vc_हटाओ_vlan_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * हटाओ programmed guest vlan id
 **/
अटल पूर्णांक i40e_vc_हटाओ_vlan_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_vlan_filter_list *vfl =
	    (काष्ठा virtchnl_vlan_filter_list *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status aq_ret = 0;
	पूर्णांक i;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vfl->vsi_id)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < vfl->num_elements; i++) अणु
		अगर (vfl->vlan_id[i] > I40E_MAX_VLANID) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ error_param;
		पूर्ण
	पूर्ण

	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (vsi->info.pvid) अणु
		अगर (vfl->num_elements > 1 || vfl->vlan_id[0])
			aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < vfl->num_elements; i++) अणु
		i40e_vsi_समाप्त_vlan(vsi, vfl->vlan_id[i]);
		vf->num_vlan--;

		अगर (test_bit(I40E_VF_STATE_UC_PROMISC, &vf->vf_states))
			i40e_aq_set_vsi_uc_promisc_on_vlan(&pf->hw, vsi->seid,
							   false,
							   vfl->vlan_id[i],
							   शून्य);
		अगर (test_bit(I40E_VF_STATE_MC_PROMISC, &vf->vf_states))
			i40e_aq_set_vsi_mc_promisc_on_vlan(&pf->hw, vsi->seid,
							   false,
							   vfl->vlan_id[i],
							   शून्य);
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DEL_VLAN, aq_ret);
पूर्ण

/**
 * i40e_vc_iwarp_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 *
 * called from the VF क्रम the iwarp msgs
 **/
अटल पूर्णांक i40e_vc_iwarp_msg(काष्ठा i40e_vf *vf, u8 *msg, u16 msglen)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	पूर्णांक असल_vf_id = vf->vf_id + pf->hw.func_caps.vf_base_id;
	i40e_status aq_ret = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !test_bit(I40E_VF_STATE_IWARPENA, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	i40e_notअगरy_client_of_vf_msg(pf->vsi[pf->lan_vsi], असल_vf_id,
				     msg, msglen);

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_IWARP,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_iwarp_qvmap_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 * @config: config qvmap or release it
 *
 * called from the VF क्रम the iwarp msgs
 **/
अटल पूर्णांक i40e_vc_iwarp_qvmap_msg(काष्ठा i40e_vf *vf, u8 *msg, bool config)
अणु
	काष्ठा virtchnl_iwarp_qvlist_info *qvlist_info =
				(काष्ठा virtchnl_iwarp_qvlist_info *)msg;
	i40e_status aq_ret = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !test_bit(I40E_VF_STATE_IWARPENA, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (config) अणु
		अगर (i40e_config_iwarp_qvlist(vf, qvlist_info))
			aq_ret = I40E_ERR_PARAM;
	पूर्ण अन्यथा अणु
		i40e_release_iwarp_qvlist(vf);
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf,
			       config ? VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP :
			       VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP,
			       aq_ret);
पूर्ण

/**
 * i40e_vc_config_rss_key
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Configure the VF's RSS key
 **/
अटल पूर्णांक i40e_vc_config_rss_key(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_rss_key *vrk =
		(काष्ठा virtchnl_rss_key *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status aq_ret = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vrk->vsi_id) ||
	    (vrk->key_len != I40E_HKEY_ARRAY_SIZE)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	vsi = pf->vsi[vf->lan_vsi_idx];
	aq_ret = i40e_config_rss(vsi, vrk->key, शून्य, 0);
err:
	/* send the response to the VF */
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_RSS_KEY,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_config_rss_lut
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Configure the VF's RSS LUT
 **/
अटल पूर्णांक i40e_vc_config_rss_lut(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_rss_lut *vrl =
		(काष्ठा virtchnl_rss_lut *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status aq_ret = 0;
	u16 i;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states) ||
	    !i40e_vc_isvalid_vsi_id(vf, vrl->vsi_id) ||
	    (vrl->lut_entries != I40E_VF_HLUT_ARRAY_SIZE)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < vrl->lut_entries; i++)
		अगर (vrl->lut[i] >= vf->num_queue_pairs) अणु
			aq_ret = I40E_ERR_PARAM;
			जाओ err;
		पूर्ण

	vsi = pf->vsi[vf->lan_vsi_idx];
	aq_ret = i40e_config_rss(vsi, शून्य, vrl->lut, I40E_VF_HLUT_ARRAY_SIZE);
	/* send the response to the VF */
err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_CONFIG_RSS_LUT,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_get_rss_hena
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Return the RSS HENA bits allowed by the hardware
 **/
अटल पूर्णांक i40e_vc_get_rss_hena(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_rss_hena *vrh = शून्य;
	काष्ठा i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;
	पूर्णांक len = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण
	len = माप(काष्ठा virtchnl_rss_hena);

	vrh = kzalloc(len, GFP_KERNEL);
	अगर (!vrh) अणु
		aq_ret = I40E_ERR_NO_MEMORY;
		len = 0;
		जाओ err;
	पूर्ण
	vrh->hena = i40e_pf_get_शेष_rss_hena(pf);
err:
	/* send the response back to the VF */
	aq_ret = i40e_vc_send_msg_to_vf(vf, VIRTCHNL_OP_GET_RSS_HENA_CAPS,
					aq_ret, (u8 *)vrh, len);
	kमुक्त(vrh);
	वापस aq_ret;
पूर्ण

/**
 * i40e_vc_set_rss_hena
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Set the RSS HENA bits क्रम the VF
 **/
अटल पूर्णांक i40e_vc_set_rss_hena(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_rss_hena *vrh =
		(काष्ठा virtchnl_rss_hena *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status aq_ret = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण
	i40e_ग_लिखो_rx_ctl(hw, I40E_VFQF_HENA1(0, vf->vf_id), (u32)vrh->hena);
	i40e_ग_लिखो_rx_ctl(hw, I40E_VFQF_HENA1(1, vf->vf_id),
			  (u32)(vrh->hena >> 32));

	/* send the response to the VF */
err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_SET_RSS_HENA, aq_ret);
पूर्ण

/**
 * i40e_vc_enable_vlan_stripping
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Enable vlan header stripping क्रम the VF
 **/
अटल पूर्णांक i40e_vc_enable_vlan_stripping(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	i40e_status aq_ret = 0;
	काष्ठा i40e_vsi *vsi;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	vsi = vf->pf->vsi[vf->lan_vsi_idx];
	i40e_vlan_stripping_enable(vsi);

	/* send the response to the VF */
err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ENABLE_VLAN_STRIPPING,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_disable_vlan_stripping
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Disable vlan header stripping क्रम the VF
 **/
अटल पूर्णांक i40e_vc_disable_vlan_stripping(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	i40e_status aq_ret = 0;
	काष्ठा i40e_vsi *vsi;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	vsi = vf->pf->vsi[vf->lan_vsi_idx];
	i40e_vlan_stripping_disable(vsi);

	/* send the response to the VF */
err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DISABLE_VLAN_STRIPPING,
				       aq_ret);
पूर्ण

/**
 * i40e_validate_cloud_filter
 * @vf: poपूर्णांकer to VF काष्ठाure
 * @tc_filter: poपूर्णांकer to filter requested
 *
 * This function validates cloud filter programmed as TC filter क्रम ADq
 **/
अटल पूर्णांक i40e_validate_cloud_filter(काष्ठा i40e_vf *vf,
				      काष्ठा virtchnl_filter *tc_filter)
अणु
	काष्ठा virtchnl_l4_spec mask = tc_filter->mask.tcp_spec;
	काष्ठा virtchnl_l4_spec data = tc_filter->data.tcp_spec;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	काष्ठा i40e_mac_filter *f;
	काष्ठा hlist_node *h;
	bool found = false;
	पूर्णांक bkt;

	अगर (!tc_filter->action) अणु
		dev_info(&pf->pdev->dev,
			 "VF %d: Currently ADq doesn't support Drop Action\n",
			 vf->vf_id);
		जाओ err;
	पूर्ण

	/* action_meta is TC number here to which the filter is applied */
	अगर (!tc_filter->action_meta ||
	    tc_filter->action_meta > I40E_MAX_VF_VSI) अणु
		dev_info(&pf->pdev->dev, "VF %d: Invalid TC number %u\n",
			 vf->vf_id, tc_filter->action_meta);
		जाओ err;
	पूर्ण

	/* Check filter अगर it's programmed क्रम advanced mode or basic mode.
	 * There are two ADq modes (क्रम VF only),
	 * 1. Basic mode: पूर्णांकended to allow as many filter options as possible
	 *		  to be added to a VF in Non-trusted mode. Main goal is
	 *		  to add filters to its own MAC and VLAN id.
	 * 2. Advanced mode: is क्रम allowing filters to be applied other than
	 *		  its own MAC or VLAN. This mode requires the VF to be
	 *		  Trusted.
	 */
	अगर (mask.dst_mac[0] && !mask.dst_ip[0]) अणु
		vsi = pf->vsi[vf->lan_vsi_idx];
		f = i40e_find_mac(vsi, data.dst_mac);

		अगर (!f) अणु
			dev_info(&pf->pdev->dev,
				 "Destination MAC %pM doesn't belong to VF %d\n",
				 data.dst_mac, vf->vf_id);
			जाओ err;
		पूर्ण

		अगर (mask.vlan_id) अणु
			hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f,
					   hlist) अणु
				अगर (f->vlan == ntohs(data.vlan_id)) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!found) अणु
				dev_info(&pf->pdev->dev,
					 "VF %d doesn't have any VLAN id %u\n",
					 vf->vf_id, ntohs(data.vlan_id));
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Check अगर VF is trusted */
		अगर (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps)) अणु
			dev_err(&pf->pdev->dev,
				"VF %d not trusted, make VF trusted to add advanced mode ADq cloud filters\n",
				vf->vf_id);
			वापस I40E_ERR_CONFIG;
		पूर्ण
	पूर्ण

	अगर (mask.dst_mac[0] & data.dst_mac[0]) अणु
		अगर (is_broadcast_ether_addr(data.dst_mac) ||
		    is_zero_ether_addr(data.dst_mac)) अणु
			dev_info(&pf->pdev->dev, "VF %d: Invalid Dest MAC addr %pM\n",
				 vf->vf_id, data.dst_mac);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (mask.src_mac[0] & data.src_mac[0]) अणु
		अगर (is_broadcast_ether_addr(data.src_mac) ||
		    is_zero_ether_addr(data.src_mac)) अणु
			dev_info(&pf->pdev->dev, "VF %d: Invalid Source MAC addr %pM\n",
				 vf->vf_id, data.src_mac);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (mask.dst_port & data.dst_port) अणु
		अगर (!data.dst_port) अणु
			dev_info(&pf->pdev->dev, "VF %d: Invalid Dest port\n",
				 vf->vf_id);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (mask.src_port & data.src_port) अणु
		अगर (!data.src_port) अणु
			dev_info(&pf->pdev->dev, "VF %d: Invalid Source port\n",
				 vf->vf_id);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (tc_filter->flow_type != VIRTCHNL_TCP_V6_FLOW &&
	    tc_filter->flow_type != VIRTCHNL_TCP_V4_FLOW) अणु
		dev_info(&pf->pdev->dev, "VF %d: Invalid Flow type\n",
			 vf->vf_id);
		जाओ err;
	पूर्ण

	अगर (mask.vlan_id & data.vlan_id) अणु
		अगर (ntohs(data.vlan_id) > I40E_MAX_VLANID) अणु
			dev_info(&pf->pdev->dev, "VF %d: invalid VLAN ID\n",
				 vf->vf_id);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस I40E_SUCCESS;
err:
	वापस I40E_ERR_CONFIG;
पूर्ण

/**
 * i40e_find_vsi_from_seid - searches क्रम the vsi with the given seid
 * @vf: poपूर्णांकer to the VF info
 * @seid: seid of the vsi it is searching क्रम
 **/
अटल काष्ठा i40e_vsi *i40e_find_vsi_from_seid(काष्ठा i40e_vf *vf, u16 seid)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < vf->num_tc ; i++) अणु
		vsi = i40e_find_vsi_from_id(pf, vf->ch[i].vsi_id);
		अगर (vsi && vsi->seid == seid)
			वापस vsi;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * i40e_del_all_cloud_filters
 * @vf: poपूर्णांकer to the VF info
 *
 * This function deletes all cloud filters
 **/
अटल व्योम i40e_del_all_cloud_filters(काष्ठा i40e_vf *vf)
अणु
	काष्ठा i40e_cloud_filter *cfilter = शून्य;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	काष्ठा hlist_node *node;
	पूर्णांक ret;

	hlist_क्रम_each_entry_safe(cfilter, node,
				  &vf->cloud_filter_list, cloud_node) अणु
		vsi = i40e_find_vsi_from_seid(vf, cfilter->seid);

		अगर (!vsi) अणु
			dev_err(&pf->pdev->dev, "VF %d: no VSI found for matching %u seid, can't delete cloud filter\n",
				vf->vf_id, cfilter->seid);
			जारी;
		पूर्ण

		अगर (cfilter->dst_port)
			ret = i40e_add_del_cloud_filter_big_buf(vsi, cfilter,
								false);
		अन्यथा
			ret = i40e_add_del_cloud_filter(vsi, cfilter, false);
		अगर (ret)
			dev_err(&pf->pdev->dev,
				"VF %d: Failed to delete cloud filter, err %s aq_err %s\n",
				vf->vf_id, i40e_stat_str(&pf->hw, ret),
				i40e_aq_str(&pf->hw,
					    pf->hw.aq.asq_last_status));

		hlist_del(&cfilter->cloud_node);
		kमुक्त(cfilter);
		vf->num_cloud_filters--;
	पूर्ण
पूर्ण

/**
 * i40e_vc_del_cloud_filter
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * This function deletes a cloud filter programmed as TC filter क्रम ADq
 **/
अटल पूर्णांक i40e_vc_del_cloud_filter(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_filter *vcf = (काष्ठा virtchnl_filter *)msg;
	काष्ठा virtchnl_l4_spec mask = vcf->mask.tcp_spec;
	काष्ठा virtchnl_l4_spec tcf = vcf->data.tcp_spec;
	काष्ठा i40e_cloud_filter cfilter, *cf = शून्य;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	काष्ठा hlist_node *node;
	i40e_status aq_ret = 0;
	पूर्णांक i, ret;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	अगर (!vf->adq_enabled) अणु
		dev_info(&pf->pdev->dev,
			 "VF %d: ADq not enabled, can't apply cloud filter\n",
			 vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	अगर (i40e_validate_cloud_filter(vf, vcf)) अणु
		dev_info(&pf->pdev->dev,
			 "VF %d: Invalid input, can't apply cloud filter\n",
			 vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	स_रखो(&cfilter, 0, माप(cfilter));
	/* parse destination mac address */
	क्रम (i = 0; i < ETH_ALEN; i++)
		cfilter.dst_mac[i] = mask.dst_mac[i] & tcf.dst_mac[i];

	/* parse source mac address */
	क्रम (i = 0; i < ETH_ALEN; i++)
		cfilter.src_mac[i] = mask.src_mac[i] & tcf.src_mac[i];

	cfilter.vlan_id = mask.vlan_id & tcf.vlan_id;
	cfilter.dst_port = mask.dst_port & tcf.dst_port;
	cfilter.src_port = mask.src_port & tcf.src_port;

	चयन (vcf->flow_type) अणु
	हाल VIRTCHNL_TCP_V4_FLOW:
		cfilter.n_proto = ETH_P_IP;
		अगर (mask.dst_ip[0] & tcf.dst_ip[0])
			स_नकल(&cfilter.ip.v4.dst_ip, tcf.dst_ip,
			       ARRAY_SIZE(tcf.dst_ip));
		अन्यथा अगर (mask.src_ip[0] & tcf.dst_ip[0])
			स_नकल(&cfilter.ip.v4.src_ip, tcf.src_ip,
			       ARRAY_SIZE(tcf.dst_ip));
		अवरोध;
	हाल VIRTCHNL_TCP_V6_FLOW:
		cfilter.n_proto = ETH_P_IPV6;
		अगर (mask.dst_ip[3] & tcf.dst_ip[3])
			स_नकल(&cfilter.ip.v6.dst_ip6, tcf.dst_ip,
			       माप(cfilter.ip.v6.dst_ip6));
		अगर (mask.src_ip[3] & tcf.src_ip[3])
			स_नकल(&cfilter.ip.v6.src_ip6, tcf.src_ip,
			       माप(cfilter.ip.v6.src_ip6));
		अवरोध;
	शेष:
		/* TC filter can be configured based on dअगरferent combinations
		 * and in this हाल IP is not a part of filter config
		 */
		dev_info(&pf->pdev->dev, "VF %d: Flow type not configured\n",
			 vf->vf_id);
	पूर्ण

	/* get the vsi to which the tc beदीर्घs to */
	vsi = pf->vsi[vf->ch[vcf->action_meta].vsi_idx];
	cfilter.seid = vsi->seid;
	cfilter.flags = vcf->field_flags;

	/* Deleting TC filter */
	अगर (tcf.dst_port)
		ret = i40e_add_del_cloud_filter_big_buf(vsi, &cfilter, false);
	अन्यथा
		ret = i40e_add_del_cloud_filter(vsi, &cfilter, false);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"VF %d: Failed to delete cloud filter, err %s aq_err %s\n",
			vf->vf_id, i40e_stat_str(&pf->hw, ret),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ err;
	पूर्ण

	hlist_क्रम_each_entry_safe(cf, node,
				  &vf->cloud_filter_list, cloud_node) अणु
		अगर (cf->seid != cfilter.seid)
			जारी;
		अगर (mask.dst_port)
			अगर (cfilter.dst_port != cf->dst_port)
				जारी;
		अगर (mask.dst_mac[0])
			अगर (!ether_addr_equal(cf->src_mac, cfilter.src_mac))
				जारी;
		/* क्रम ipv4 data to be valid, only first byte of mask is set */
		अगर (cfilter.n_proto == ETH_P_IP && mask.dst_ip[0])
			अगर (स_भेद(&cfilter.ip.v4.dst_ip, &cf->ip.v4.dst_ip,
				   ARRAY_SIZE(tcf.dst_ip)))
				जारी;
		/* क्रम ipv6, mask is set क्रम all sixteen bytes (4 words) */
		अगर (cfilter.n_proto == ETH_P_IPV6 && mask.dst_ip[3])
			अगर (स_भेद(&cfilter.ip.v6.dst_ip6, &cf->ip.v6.dst_ip6,
				   माप(cfilter.ip.v6.src_ip6)))
				जारी;
		अगर (mask.vlan_id)
			अगर (cfilter.vlan_id != cf->vlan_id)
				जारी;

		hlist_del(&cf->cloud_node);
		kमुक्त(cf);
		vf->num_cloud_filters--;
	पूर्ण

err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DEL_CLOUD_FILTER,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_add_cloud_filter
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * This function adds a cloud filter programmed as TC filter क्रम ADq
 **/
अटल पूर्णांक i40e_vc_add_cloud_filter(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_filter *vcf = (काष्ठा virtchnl_filter *)msg;
	काष्ठा virtchnl_l4_spec mask = vcf->mask.tcp_spec;
	काष्ठा virtchnl_l4_spec tcf = vcf->data.tcp_spec;
	काष्ठा i40e_cloud_filter *cfilter = शून्य;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_vsi *vsi = शून्य;
	i40e_status aq_ret = 0;
	पूर्णांक i, ret;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err_out;
	पूर्ण

	अगर (!vf->adq_enabled) अणु
		dev_info(&pf->pdev->dev,
			 "VF %d: ADq is not enabled, can't apply cloud filter\n",
			 vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
		जाओ err_out;
	पूर्ण

	अगर (i40e_validate_cloud_filter(vf, vcf)) अणु
		dev_info(&pf->pdev->dev,
			 "VF %d: Invalid input/s, can't apply cloud filter\n",
			 vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
		जाओ err_out;
	पूर्ण

	cfilter = kzalloc(माप(*cfilter), GFP_KERNEL);
	अगर (!cfilter)
		वापस -ENOMEM;

	/* parse destination mac address */
	क्रम (i = 0; i < ETH_ALEN; i++)
		cfilter->dst_mac[i] = mask.dst_mac[i] & tcf.dst_mac[i];

	/* parse source mac address */
	क्रम (i = 0; i < ETH_ALEN; i++)
		cfilter->src_mac[i] = mask.src_mac[i] & tcf.src_mac[i];

	cfilter->vlan_id = mask.vlan_id & tcf.vlan_id;
	cfilter->dst_port = mask.dst_port & tcf.dst_port;
	cfilter->src_port = mask.src_port & tcf.src_port;

	चयन (vcf->flow_type) अणु
	हाल VIRTCHNL_TCP_V4_FLOW:
		cfilter->n_proto = ETH_P_IP;
		अगर (mask.dst_ip[0] & tcf.dst_ip[0])
			स_नकल(&cfilter->ip.v4.dst_ip, tcf.dst_ip,
			       ARRAY_SIZE(tcf.dst_ip));
		अन्यथा अगर (mask.src_ip[0] & tcf.dst_ip[0])
			स_नकल(&cfilter->ip.v4.src_ip, tcf.src_ip,
			       ARRAY_SIZE(tcf.dst_ip));
		अवरोध;
	हाल VIRTCHNL_TCP_V6_FLOW:
		cfilter->n_proto = ETH_P_IPV6;
		अगर (mask.dst_ip[3] & tcf.dst_ip[3])
			स_नकल(&cfilter->ip.v6.dst_ip6, tcf.dst_ip,
			       माप(cfilter->ip.v6.dst_ip6));
		अगर (mask.src_ip[3] & tcf.src_ip[3])
			स_नकल(&cfilter->ip.v6.src_ip6, tcf.src_ip,
			       माप(cfilter->ip.v6.src_ip6));
		अवरोध;
	शेष:
		/* TC filter can be configured based on dअगरferent combinations
		 * and in this हाल IP is not a part of filter config
		 */
		dev_info(&pf->pdev->dev, "VF %d: Flow type not configured\n",
			 vf->vf_id);
	पूर्ण

	/* get the VSI to which the TC beदीर्घs to */
	vsi = pf->vsi[vf->ch[vcf->action_meta].vsi_idx];
	cfilter->seid = vsi->seid;
	cfilter->flags = vcf->field_flags;

	/* Adding cloud filter programmed as TC filter */
	अगर (tcf.dst_port)
		ret = i40e_add_del_cloud_filter_big_buf(vsi, cfilter, true);
	अन्यथा
		ret = i40e_add_del_cloud_filter(vsi, cfilter, true);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev,
			"VF %d: Failed to add cloud filter, err %s aq_err %s\n",
			vf->vf_id, i40e_stat_str(&pf->hw, ret),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		जाओ err_मुक्त;
	पूर्ण

	INIT_HLIST_NODE(&cfilter->cloud_node);
	hlist_add_head(&cfilter->cloud_node, &vf->cloud_filter_list);
	/* release the poपूर्णांकer passing it to the collection */
	cfilter = शून्य;
	vf->num_cloud_filters++;
err_मुक्त:
	kमुक्त(cfilter);
err_out:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ADD_CLOUD_FILTER,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_add_qch_msg: Add queue channel and enable ADq
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 **/
अटल पूर्णांक i40e_vc_add_qch_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_tc_info *tci =
		(काष्ठा virtchnl_tc_info *)msg;
	काष्ठा i40e_pf *pf = vf->pf;
	काष्ठा i40e_link_status *ls = &pf->hw.phy.link_info;
	पूर्णांक i, adq_request_qps = 0;
	i40e_status aq_ret = 0;
	u64 speed = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	/* ADq cannot be applied अगर spoof check is ON */
	अगर (vf->spoofchk) अणु
		dev_err(&pf->pdev->dev,
			"Spoof check is ON, turn it OFF to enable ADq\n");
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	अगर (!(vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ADQ)) अणु
		dev_err(&pf->pdev->dev,
			"VF %d attempting to enable ADq, but hasn't properly negotiated that capability\n",
			vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	/* max number of traffic classes क्रम VF currently capped at 4 */
	अगर (!tci->num_tc || tci->num_tc > I40E_MAX_VF_VSI) अणु
		dev_err(&pf->pdev->dev,
			"VF %d trying to set %u TCs, valid range 1-%u TCs per VF\n",
			vf->vf_id, tci->num_tc, I40E_MAX_VF_VSI);
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	/* validate queues क्रम each TC */
	क्रम (i = 0; i < tci->num_tc; i++)
		अगर (!tci->list[i].count ||
		    tci->list[i].count > I40E_DEFAULT_QUEUES_PER_VF) अणु
			dev_err(&pf->pdev->dev,
				"VF %d: TC %d trying to set %u queues, valid range 1-%u queues per TC\n",
				vf->vf_id, i, tci->list[i].count,
				I40E_DEFAULT_QUEUES_PER_VF);
			aq_ret = I40E_ERR_PARAM;
			जाओ err;
		पूर्ण

	/* need Max VF queues but alपढ़ोy have शेष number of queues */
	adq_request_qps = I40E_MAX_VF_QUEUES - I40E_DEFAULT_QUEUES_PER_VF;

	अगर (pf->queues_left < adq_request_qps) अणु
		dev_err(&pf->pdev->dev,
			"No queues left to allocate to VF %d\n",
			vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण अन्यथा अणु
		/* we need to allocate max VF queues to enable ADq so as to
		 * make sure ADq enabled VF always माला_लो back queues when it
		 * goes through a reset.
		 */
		vf->num_queue_pairs = I40E_MAX_VF_QUEUES;
	पूर्ण

	/* get link speed in MB to validate rate limit */
	speed = i40e_vc_link_speed2mbps(ls->link_speed);
	अगर (speed == SPEED_UNKNOWN) अणु
		dev_err(&pf->pdev->dev,
			"Cannot detect link speed\n");
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	/* parse data from the queue channel info */
	vf->num_tc = tci->num_tc;
	क्रम (i = 0; i < vf->num_tc; i++) अणु
		अगर (tci->list[i].max_tx_rate) अणु
			अगर (tci->list[i].max_tx_rate > speed) अणु
				dev_err(&pf->pdev->dev,
					"Invalid max tx rate %llu specified for VF %d.",
					tci->list[i].max_tx_rate,
					vf->vf_id);
				aq_ret = I40E_ERR_PARAM;
				जाओ err;
			पूर्ण अन्यथा अणु
				vf->ch[i].max_tx_rate =
					tci->list[i].max_tx_rate;
			पूर्ण
		पूर्ण
		vf->ch[i].num_qps = tci->list[i].count;
	पूर्ण

	/* set this flag only after making sure all inमाला_दो are sane */
	vf->adq_enabled = true;
	/* num_req_queues is set when user changes number of queues via ethtool
	 * and this causes issue क्रम शेष VSI(which depends on this variable)
	 * when ADq is enabled, hence reset it.
	 */
	vf->num_req_queues = 0;

	/* reset the VF in order to allocate resources */
	i40e_vc_notअगरy_vf_reset(vf);
	i40e_reset_vf(vf, false);

	वापस I40E_SUCCESS;

	/* send the response to the VF */
err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_ENABLE_CHANNELS,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_del_qch_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 **/
अटल पूर्णांक i40e_vc_del_qch_msg(काष्ठा i40e_vf *vf, u8 *msg)
अणु
	काष्ठा i40e_pf *pf = vf->pf;
	i40e_status aq_ret = 0;

	अगर (!test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states)) अणु
		aq_ret = I40E_ERR_PARAM;
		जाओ err;
	पूर्ण

	अगर (vf->adq_enabled) अणु
		i40e_del_all_cloud_filters(vf);
		i40e_del_qch(vf);
		vf->adq_enabled = false;
		vf->num_tc = 0;
		dev_info(&pf->pdev->dev,
			 "Deleting Queue Channels and cloud filters for ADq on VF %d\n",
			 vf->vf_id);
	पूर्ण अन्यथा अणु
		dev_info(&pf->pdev->dev, "VF %d trying to delete queue channels but ADq isn't enabled\n",
			 vf->vf_id);
		aq_ret = I40E_ERR_PARAM;
	पूर्ण

	/* reset the VF in order to allocate resources */
	i40e_vc_notअगरy_vf_reset(vf);
	i40e_reset_vf(vf, false);

	वापस I40E_SUCCESS;

err:
	वापस i40e_vc_send_resp_to_vf(vf, VIRTCHNL_OP_DISABLE_CHANNELS,
				       aq_ret);
पूर्ण

/**
 * i40e_vc_process_vf_msg
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @vf_id: source VF id
 * @v_opcode: operation code
 * @v_retval: unused वापस value code
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 *
 * called from the common aeq/arq handler to
 * process request from VF
 **/
पूर्णांक i40e_vc_process_vf_msg(काष्ठा i40e_pf *pf, s16 vf_id, u32 v_opcode,
			   u32 __always_unused v_retval, u8 *msg, u16 msglen)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक local_vf_id = vf_id - (s16)hw->func_caps.vf_base_id;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret;

	pf->vf_aq_requests++;
	अगर (local_vf_id < 0 || local_vf_id >= pf->num_alloc_vfs)
		वापस -EINVAL;
	vf = &(pf->vf[local_vf_id]);

	/* Check अगर VF is disabled. */
	अगर (test_bit(I40E_VF_STATE_DISABLED, &vf->vf_states))
		वापस I40E_ERR_PARAM;

	/* perक्रमm basic checks on the msg */
	ret = virtchnl_vc_validate_vf_msg(&vf->vf_ver, v_opcode, msg, msglen);

	अगर (ret) अणु
		i40e_vc_send_resp_to_vf(vf, v_opcode, I40E_ERR_PARAM);
		dev_err(&pf->pdev->dev, "Invalid message from VF %d, opcode %d, len %d\n",
			local_vf_id, v_opcode, msglen);
		चयन (ret) अणु
		हाल VIRTCHNL_STATUS_ERR_PARAM:
			वापस -EPERM;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (v_opcode) अणु
	हाल VIRTCHNL_OP_VERSION:
		ret = i40e_vc_get_version_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_GET_VF_RESOURCES:
		ret = i40e_vc_get_vf_resources_msg(vf, msg);
		i40e_vc_notअगरy_vf_link_state(vf);
		अवरोध;
	हाल VIRTCHNL_OP_RESET_VF:
		i40e_vc_reset_vf_msg(vf);
		ret = 0;
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE:
		ret = i40e_vc_config_promiscuous_mode_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_VSI_QUEUES:
		ret = i40e_vc_config_queues_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_IRQ_MAP:
		ret = i40e_vc_config_irq_map_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_QUEUES:
		ret = i40e_vc_enable_queues_msg(vf, msg);
		i40e_vc_notअगरy_vf_link_state(vf);
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_QUEUES:
		ret = i40e_vc_disable_queues_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_ETH_ADDR:
		ret = i40e_vc_add_mac_addr_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_ETH_ADDR:
		ret = i40e_vc_del_mac_addr_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_VLAN:
		ret = i40e_vc_add_vlan_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_VLAN:
		ret = i40e_vc_हटाओ_vlan_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_GET_STATS:
		ret = i40e_vc_get_stats_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_IWARP:
		ret = i40e_vc_iwarp_msg(vf, msg, msglen);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP:
		ret = i40e_vc_iwarp_qvmap_msg(vf, msg, true);
		अवरोध;
	हाल VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP:
		ret = i40e_vc_iwarp_qvmap_msg(vf, msg, false);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RSS_KEY:
		ret = i40e_vc_config_rss_key(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RSS_LUT:
		ret = i40e_vc_config_rss_lut(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_GET_RSS_HENA_CAPS:
		ret = i40e_vc_get_rss_hena(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_SET_RSS_HENA:
		ret = i40e_vc_set_rss_hena(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_VLAN_STRIPPING:
		ret = i40e_vc_enable_vlan_stripping(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_VLAN_STRIPPING:
		ret = i40e_vc_disable_vlan_stripping(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_REQUEST_QUEUES:
		ret = i40e_vc_request_queues_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_CHANNELS:
		ret = i40e_vc_add_qch_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_CHANNELS:
		ret = i40e_vc_del_qch_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_CLOUD_FILTER:
		ret = i40e_vc_add_cloud_filter(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_CLOUD_FILTER:
		ret = i40e_vc_del_cloud_filter(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_UNKNOWN:
	शेष:
		dev_err(&pf->pdev->dev, "Unsupported opcode %d from VF %d\n",
			v_opcode, local_vf_id);
		ret = i40e_vc_send_resp_to_vf(vf, v_opcode,
					      I40E_ERR_NOT_IMPLEMENTED);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_vc_process_vflr_event
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * called from the vlfr irq handler to
 * मुक्त up VF resources and state variables
 **/
पूर्णांक i40e_vc_process_vflr_event(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 reg, reg_idx, bit_idx;
	काष्ठा i40e_vf *vf;
	पूर्णांक vf_id;

	अगर (!test_bit(__I40E_VFLR_EVENT_PENDING, pf->state))
		वापस 0;

	/* Re-enable the VFLR पूर्णांकerrupt cause here, beक्रमe looking क्रम which
	 * VF got reset. Otherwise, अगर another VF माला_लो a reset जबतक the
	 * first one is being processed, that पूर्णांकerrupt will be lost, and
	 * that VF will be stuck in reset क्रमever.
	 */
	reg = rd32(hw, I40E_PFINT_ICR0_ENA);
	reg |= I40E_PFINT_ICR0_ENA_VFLR_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, reg);
	i40e_flush(hw);

	clear_bit(__I40E_VFLR_EVENT_PENDING, pf->state);
	क्रम (vf_id = 0; vf_id < pf->num_alloc_vfs; vf_id++) अणु
		reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
		bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
		/* पढ़ो GLGEN_VFLRSTAT रेजिस्टर to find out the flr VFs */
		vf = &pf->vf[vf_id];
		reg = rd32(hw, I40E_GLGEN_VFLRSTAT(reg_idx));
		अगर (reg & BIT(bit_idx))
			/* i40e_reset_vf will clear the bit in GLGEN_VFLRSTAT */
			i40e_reset_vf(vf, true);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_validate_vf
 * @pf: the physical function
 * @vf_id: VF identअगरier
 *
 * Check that the VF is enabled and the VSI exists.
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक i40e_validate_vf(काष्ठा i40e_pf *pf, पूर्णांक vf_id)
अणु
	काष्ठा i40e_vsi *vsi;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;

	अगर (vf_id >= pf->num_alloc_vfs) अणु
		dev_err(&pf->pdev->dev,
			"Invalid VF Identifier %d\n", vf_id);
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण
	vf = &pf->vf[vf_id];
	vsi = i40e_find_vsi_from_id(pf, vf->lan_vsi_id);
	अगर (!vsi)
		ret = -EINVAL;
err_out:
	वापस ret;
पूर्ण

/**
 * i40e_nकरो_set_vf_mac
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @mac: mac address
 *
 * program VF mac address
 **/
पूर्णांक i40e_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_id, u8 *mac)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_mac_filter *f;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;
	काष्ठा hlist_node *h;
	पूर्णांक bkt;
	u8 i;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	ret = i40e_validate_vf(pf, vf_id);
	अगर (ret)
		जाओ error_param;

	vf = &pf->vf[vf_id];

	/* When the VF is resetting रुको until it is करोne.
	 * It can take up to 200 milliseconds,
	 * but रुको क्रम up to 300 milliseconds to be safe.
	 * Acquire the VSI poपूर्णांकer only after the VF has been
	 * properly initialized.
	 */
	क्रम (i = 0; i < 15; i++) अणु
		अगर (test_bit(I40E_VF_STATE_INIT, &vf->vf_states))
			अवरोध;
		msleep(20);
	पूर्ण
	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) अणु
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		जाओ error_param;
	पूर्ण
	vsi = pf->vsi[vf->lan_vsi_idx];

	अगर (is_multicast_ether_addr(mac)) अणु
		dev_err(&pf->pdev->dev,
			"Invalid Ethernet address %pM for VF %d\n", mac, vf_id);
		ret = -EINVAL;
		जाओ error_param;
	पूर्ण

	/* Lock once because below invoked function add/del_filter requires
	 * mac_filter_hash_lock to be held
	 */
	spin_lock_bh(&vsi->mac_filter_hash_lock);

	/* delete the temporary mac address */
	अगर (!is_zero_ether_addr(vf->शेष_lan_addr.addr))
		i40e_del_mac_filter(vsi, vf->शेष_lan_addr.addr);

	/* Delete all the filters क्रम this VSI - we're going to समाप्त it
	 * anyway.
	 */
	hash_क्रम_each_safe(vsi->mac_filter_hash, bkt, h, f, hlist)
		__i40e_del_filter(vsi, f);

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* program mac filter */
	अगर (i40e_sync_vsi_filters(vsi)) अणु
		dev_err(&pf->pdev->dev, "Unable to program ucast filters\n");
		ret = -EIO;
		जाओ error_param;
	पूर्ण
	ether_addr_copy(vf->शेष_lan_addr.addr, mac);

	अगर (is_zero_ether_addr(mac)) अणु
		vf->pf_set_mac = false;
		dev_info(&pf->pdev->dev, "Removing MAC on VF %d\n", vf_id);
	पूर्ण अन्यथा अणु
		vf->pf_set_mac = true;
		dev_info(&pf->pdev->dev, "Setting MAC %pM on VF %d\n",
			 mac, vf_id);
	पूर्ण

	/* Force the VF पूर्णांकerface करोwn so it has to bring up with new MAC
	 * address
	 */
	i40e_vc_disable_vf(vf);
	dev_info(&pf->pdev->dev, "Bring down and up the VF interface to make this change effective.\n");

error_param:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_vsi_has_vlans - True अगर VSI has configured VLANs
 * @vsi: poपूर्णांकer to the vsi
 *
 * Check अगर a VSI has configured any VLANs. False अगर we have a port VLAN or अगर
 * we have no configured VLANs. Do not call जबतक holding the
 * mac_filter_hash_lock.
 */
अटल bool i40e_vsi_has_vlans(काष्ठा i40e_vsi *vsi)
अणु
	bool have_vlans;

	/* If we have a port VLAN, then the VSI cannot have any VLANs
	 * configured, as all MAC/VLAN filters will be asचिन्हित to the PVID.
	 */
	अगर (vsi->info.pvid)
		वापस false;

	/* Since we करोn't have a PVID, we know that अगर the device is in VLAN
	 * mode it must be because of a VLAN filter configured on this VSI.
	 */
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	have_vlans = i40e_is_vsi_in_vlan(vsi);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	वापस have_vlans;
पूर्ण

/**
 * i40e_nकरो_set_vf_port_vlan
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @vlan_id: mac address
 * @qos: priority setting
 * @vlan_proto: vlan protocol
 *
 * program VF vlan id and/or qos
 **/
पूर्णांक i40e_nकरो_set_vf_port_vlan(काष्ठा net_device *netdev, पूर्णांक vf_id,
			      u16 vlan_id, u8 qos, __be16 vlan_proto)
अणु
	u16 vlanprio = vlan_id | (qos << I40E_VLAN_PRIORITY_SHIFT);
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	bool allmulti = false, alluni = false;
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vsi *vsi;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	ret = i40e_validate_vf(pf, vf_id);
	अगर (ret)
		जाओ error_pvid;

	अगर ((vlan_id > I40E_MAX_VLANID) || (qos > 7)) अणु
		dev_err(&pf->pdev->dev, "Invalid VF Parameters\n");
		ret = -EINVAL;
		जाओ error_pvid;
	पूर्ण

	अगर (vlan_proto != htons(ETH_P_8021Q)) अणु
		dev_err(&pf->pdev->dev, "VF VLAN protocol is not supported\n");
		ret = -EPROTONOSUPPORT;
		जाओ error_pvid;
	पूर्ण

	vf = &pf->vf[vf_id];
	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) अणु
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		जाओ error_pvid;
	पूर्ण

	अगर (le16_to_cpu(vsi->info.pvid) == vlanprio)
		/* duplicate request, so just वापस success */
		जाओ error_pvid;

	अगर (i40e_vsi_has_vlans(vsi)) अणु
		dev_err(&pf->pdev->dev,
			"VF %d has already configured VLAN filters and the administrator is requesting a port VLAN override.\nPlease unload and reload the VF driver for this change to take effect.\n",
			vf_id);
		/* Administrator Error - knock the VF offline until he करोes
		 * the right thing by reconfiguring his network correctly
		 * and then reloading the VF driver.
		 */
		i40e_vc_disable_vf(vf);
		/* During reset the VF got a new VSI, so refresh the poपूर्णांकer. */
		vsi = pf->vsi[vf->lan_vsi_idx];
	पूर्ण

	/* Locked once because multiple functions below iterate list */
	spin_lock_bh(&vsi->mac_filter_hash_lock);

	/* Check क्रम condition where there was alपढ़ोy a port VLAN ID
	 * filter set and now it is being deleted by setting it to zero.
	 * Additionally check क्रम the condition where there was a port
	 * VLAN but now there is a new and dअगरferent port VLAN being set.
	 * Beक्रमe deleting all the old VLAN filters we must add new ones
	 * with -1 (I40E_VLAN_ANY) or otherwise we're left with all our
	 * MAC addresses deleted.
	 */
	अगर ((!(vlan_id || qos) ||
	    vlanprio != le16_to_cpu(vsi->info.pvid)) &&
	    vsi->info.pvid) अणु
		ret = i40e_add_vlan_all_mac(vsi, I40E_VLAN_ANY);
		अगर (ret) अणु
			dev_info(&vsi->back->pdev->dev,
				 "add VF VLAN failed, ret=%d aq_err=%d\n", ret,
				 vsi->back->hw.aq.asq_last_status);
			spin_unlock_bh(&vsi->mac_filter_hash_lock);
			जाओ error_pvid;
		पूर्ण
	पूर्ण

	अगर (vsi->info.pvid) अणु
		/* हटाओ all filters on the old VLAN */
		i40e_rm_vlan_all_mac(vsi, (le16_to_cpu(vsi->info.pvid) &
					   VLAN_VID_MASK));
	पूर्ण

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* disable promisc modes in हाल they were enabled */
	ret = i40e_config_vf_promiscuous_mode(vf, vf->lan_vsi_id,
					      allmulti, alluni);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev, "Unable to config VF promiscuous mode\n");
		जाओ error_pvid;
	पूर्ण

	अगर (vlan_id || qos)
		ret = i40e_vsi_add_pvid(vsi, vlanprio);
	अन्यथा
		i40e_vsi_हटाओ_pvid(vsi);
	spin_lock_bh(&vsi->mac_filter_hash_lock);

	अगर (vlan_id) अणु
		dev_info(&pf->pdev->dev, "Setting VLAN %d, QOS 0x%x on VF %d\n",
			 vlan_id, qos, vf_id);

		/* add new VLAN filter क्रम each MAC */
		ret = i40e_add_vlan_all_mac(vsi, vlan_id);
		अगर (ret) अणु
			dev_info(&vsi->back->pdev->dev,
				 "add VF VLAN failed, ret=%d aq_err=%d\n", ret,
				 vsi->back->hw.aq.asq_last_status);
			spin_unlock_bh(&vsi->mac_filter_hash_lock);
			जाओ error_pvid;
		पूर्ण

		/* हटाओ the previously added non-VLAN MAC filters */
		i40e_rm_vlan_all_mac(vsi, I40E_VLAN_ANY);
	पूर्ण

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	अगर (test_bit(I40E_VF_STATE_UC_PROMISC, &vf->vf_states))
		alluni = true;

	अगर (test_bit(I40E_VF_STATE_MC_PROMISC, &vf->vf_states))
		allmulti = true;

	/* Schedule the worker thपढ़ो to take care of applying changes */
	i40e_service_event_schedule(vsi->back);

	अगर (ret) अणु
		dev_err(&pf->pdev->dev, "Unable to update VF vsi context\n");
		जाओ error_pvid;
	पूर्ण

	/* The Port VLAN needs to be saved across resets the same as the
	 * शेष LAN MAC address.
	 */
	vf->port_vlan_id = le16_to_cpu(vsi->info.pvid);

	ret = i40e_config_vf_promiscuous_mode(vf, vsi->id, allmulti, alluni);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev, "Unable to config vf promiscuous mode\n");
		जाओ error_pvid;
	पूर्ण

	ret = 0;

error_pvid:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_nकरो_set_vf_bw
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @min_tx_rate: Minimum Tx rate
 * @max_tx_rate: Maximum Tx rate
 *
 * configure VF Tx rate
 **/
पूर्णांक i40e_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक min_tx_rate,
		       पूर्णांक max_tx_rate)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vsi *vsi;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	ret = i40e_validate_vf(pf, vf_id);
	अगर (ret)
		जाओ error;

	अगर (min_tx_rate) अणु
		dev_err(&pf->pdev->dev, "Invalid min tx rate (%d) (greater than 0) specified for VF %d.\n",
			min_tx_rate, vf_id);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	vf = &pf->vf[vf_id];
	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) अणु
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		जाओ error;
	पूर्ण

	ret = i40e_set_bw_limit(vsi, vsi->seid, max_tx_rate);
	अगर (ret)
		जाओ error;

	vf->tx_rate = max_tx_rate;
error:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_nकरो_get_vf_config
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @ivi: VF configuration काष्ठाure
 *
 * वापस VF configuration
 **/
पूर्णांक i40e_nकरो_get_vf_config(काष्ठा net_device *netdev,
			   पूर्णांक vf_id, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	ret = i40e_validate_vf(pf, vf_id);
	अगर (ret)
		जाओ error_param;

	vf = &pf->vf[vf_id];
	/* first vsi is always the LAN vsi */
	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vsi) अणु
		ret = -ENOENT;
		जाओ error_param;
	पूर्ण

	ivi->vf = vf_id;

	ether_addr_copy(ivi->mac, vf->शेष_lan_addr.addr);

	ivi->max_tx_rate = vf->tx_rate;
	ivi->min_tx_rate = 0;
	ivi->vlan = le16_to_cpu(vsi->info.pvid) & I40E_VLAN_MASK;
	ivi->qos = (le16_to_cpu(vsi->info.pvid) & I40E_PRIORITY_MASK) >>
		   I40E_VLAN_PRIORITY_SHIFT;
	अगर (vf->link_क्रमced == false)
		ivi->linkstate = IFLA_VF_LINK_STATE_AUTO;
	अन्यथा अगर (vf->link_up == true)
		ivi->linkstate = IFLA_VF_LINK_STATE_ENABLE;
	अन्यथा
		ivi->linkstate = IFLA_VF_LINK_STATE_DISABLE;
	ivi->spoofchk = vf->spoofchk;
	ivi->trusted = vf->trusted;
	ret = 0;

error_param:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_nकरो_set_vf_link_state
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @link: required link state
 *
 * Set the link state of a specअगरied VF, regardless of physical link state
 **/
पूर्णांक i40e_nकरो_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक link)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_link_status *ls = &pf->hw.phy.link_info;
	काष्ठा virtchnl_pf_event pfe;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vf *vf;
	पूर्णांक असल_vf_id;
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	अगर (vf_id >= pf->num_alloc_vfs) अणु
		dev_err(&pf->pdev->dev, "Invalid VF Identifier %d\n", vf_id);
		ret = -EINVAL;
		जाओ error_out;
	पूर्ण

	vf = &pf->vf[vf_id];
	असल_vf_id = vf->vf_id + hw->func_caps.vf_base_id;

	pfe.event = VIRTCHNL_EVENT_LINK_CHANGE;
	pfe.severity = PF_EVENT_SEVERITY_INFO;

	चयन (link) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
		vf->link_क्रमced = false;
		i40e_set_vf_link_state(vf, &pfe, ls);
		अवरोध;
	हाल IFLA_VF_LINK_STATE_ENABLE:
		vf->link_क्रमced = true;
		vf->link_up = true;
		i40e_set_vf_link_state(vf, &pfe, ls);
		अवरोध;
	हाल IFLA_VF_LINK_STATE_DISABLE:
		vf->link_क्रमced = true;
		vf->link_up = false;
		i40e_set_vf_link_state(vf, &pfe, ls);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ error_out;
	पूर्ण
	/* Notअगरy the VF of its new link state */
	i40e_aq_send_msg_to_vf(hw, असल_vf_id, VIRTCHNL_OP_EVENT,
			       0, (u8 *)&pfe, माप(pfe), शून्य);

error_out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_nकरो_set_vf_spoofchk
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @enable: flag to enable or disable feature
 *
 * Enable or disable VF spoof checking
 **/
पूर्णांक i40e_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf_id, bool enable)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_vsi_context ctxt;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	अगर (vf_id >= pf->num_alloc_vfs) अणु
		dev_err(&pf->pdev->dev, "Invalid VF Identifier %d\n", vf_id);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	vf = &(pf->vf[vf_id]);
	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) अणु
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (enable == vf->spoofchk)
		जाओ out;

	vf->spoofchk = enable;
	स_रखो(&ctxt, 0, माप(ctxt));
	ctxt.seid = pf->vsi[vf->lan_vsi_idx]->seid;
	ctxt.pf_num = pf->hw.pf_id;
	ctxt.info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_SECURITY_VALID);
	अगर (enable)
		ctxt.info.sec_flags |= (I40E_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK |
					I40E_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK);
	ret = i40e_aq_update_vsi_params(hw, &ctxt, शून्य);
	अगर (ret) अणु
		dev_err(&pf->pdev->dev, "Error %d updating VSI parameters\n",
			ret);
		ret = -EIO;
	पूर्ण
out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_nकरो_set_vf_trust
 * @netdev: network पूर्णांकerface device काष्ठाure of the pf
 * @vf_id: VF identअगरier
 * @setting: trust setting
 *
 * Enable or disable VF trust setting
 **/
पूर्णांक i40e_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf_id, bool setting)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vf *vf;
	पूर्णांक ret = 0;

	अगर (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) अणु
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		वापस -EAGAIN;
	पूर्ण

	/* validate the request */
	अगर (vf_id >= pf->num_alloc_vfs) अणु
		dev_err(&pf->pdev->dev, "Invalid VF Identifier %d\n", vf_id);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (pf->flags & I40E_FLAG_MFP_ENABLED) अणु
		dev_err(&pf->pdev->dev, "Trusted VF not supported in MFP mode.\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	vf = &pf->vf[vf_id];

	अगर (setting == vf->trusted)
		जाओ out;

	vf->trusted = setting;
	i40e_vc_disable_vf(vf);
	dev_info(&pf->pdev->dev, "VF %u is now %strusted\n",
		 vf_id, setting ? "" : "un");

	अगर (vf->adq_enabled) अणु
		अगर (!vf->trusted) अणु
			dev_info(&pf->pdev->dev,
				 "VF %u no longer Trusted, deleting all cloud filters\n",
				 vf_id);
			i40e_del_all_cloud_filters(vf);
		पूर्ण
	पूर्ण

out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	वापस ret;
पूर्ण

/**
 * i40e_get_vf_stats - populate some stats क्रम the VF
 * @netdev: the netdev of the PF
 * @vf_id: the host OS identअगरier (0-127)
 * @vf_stats: poपूर्णांकer to the OS memory to be initialized
 */
पूर्णांक i40e_get_vf_stats(काष्ठा net_device *netdev, पूर्णांक vf_id,
		      काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_eth_stats *stats;
	काष्ठा i40e_vsi *vsi;
	काष्ठा i40e_vf *vf;

	/* validate the request */
	अगर (i40e_validate_vf(pf, vf_id))
		वापस -EINVAL;

	vf = &pf->vf[vf_id];
	अगर (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) अणु
		dev_err(&pf->pdev->dev, "VF %d in reset. Try again.\n", vf_id);
		वापस -EBUSY;
	पूर्ण

	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vsi)
		वापस -EINVAL;

	i40e_update_eth_stats(vsi);
	stats = &vsi->eth_stats;

	स_रखो(vf_stats, 0, माप(*vf_stats));

	vf_stats->rx_packets = stats->rx_unicast + stats->rx_broadcast +
		stats->rx_multicast;
	vf_stats->tx_packets = stats->tx_unicast + stats->tx_broadcast +
		stats->tx_multicast;
	vf_stats->rx_bytes   = stats->rx_bytes;
	vf_stats->tx_bytes   = stats->tx_bytes;
	vf_stats->broadcast  = stats->rx_broadcast;
	vf_stats->multicast  = stats->rx_multicast;
	vf_stats->rx_dropped = stats->rx_discards;
	vf_stats->tx_dropped = stats->tx_discards;

	वापस 0;
पूर्ण
