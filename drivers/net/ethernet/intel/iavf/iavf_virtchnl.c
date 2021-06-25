<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "iavf.h"
#समावेश "iavf_prototype.h"
#समावेश "iavf_client.h"

/* busy रुको delay in msec */
#घोषणा IAVF_BUSY_WAIT_DELAY 10
#घोषणा IAVF_BUSY_WAIT_COUNT 50

/**
 * iavf_send_pf_msg
 * @adapter: adapter काष्ठाure
 * @op: भव channel opcode
 * @msg: poपूर्णांकer to message buffer
 * @len: message length
 *
 * Send message to PF and prपूर्णांक status अगर failure.
 **/
अटल पूर्णांक iavf_send_pf_msg(काष्ठा iavf_adapter *adapter,
			    क्रमागत virtchnl_ops op, u8 *msg, u16 len)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;
	क्रमागत iavf_status err;

	अगर (adapter->flags & IAVF_FLAG_PF_COMMS_FAILED)
		वापस 0; /* nothing to see here, move aदीर्घ */

	err = iavf_aq_send_msg_to_pf(hw, op, 0, msg, len, शून्य);
	अगर (err)
		dev_dbg(&adapter->pdev->dev, "Unable to send opcode %d to PF, err %s, aq_err %s\n",
			op, iavf_stat_str(hw, err),
			iavf_aq_str(hw, hw->aq.asq_last_status));
	वापस err;
पूर्ण

/**
 * iavf_send_api_ver
 * @adapter: adapter काष्ठाure
 *
 * Send API version admin queue message to the PF. The reply is not checked
 * in this function. Returns 0 अगर the message was successfully
 * sent, or one of the IAVF_ADMIN_QUEUE_ERROR_ statuses अगर not.
 **/
पूर्णांक iavf_send_api_ver(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_version_info vvi;

	vvi.major = VIRTCHNL_VERSION_MAJOR;
	vvi.minor = VIRTCHNL_VERSION_MINOR;

	वापस iavf_send_pf_msg(adapter, VIRTCHNL_OP_VERSION, (u8 *)&vvi,
				माप(vvi));
पूर्ण

/**
 * iavf_verअगरy_api_ver
 * @adapter: adapter काष्ठाure
 *
 * Compare API versions with the PF. Must be called after admin queue is
 * initialized. Returns 0 अगर API versions match, -EIO अगर they करो not,
 * IAVF_ERR_ADMIN_QUEUE_NO_WORK अगर the admin queue is empty, and any errors
 * from the firmware are propagated.
 **/
पूर्णांक iavf_verअगरy_api_ver(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_version_info *pf_vvi;
	काष्ठा iavf_hw *hw = &adapter->hw;
	काष्ठा iavf_arq_event_info event;
	क्रमागत virtchnl_ops op;
	क्रमागत iavf_status err;

	event.buf_len = IAVF_MAX_AQ_BUF_SIZE;
	event.msg_buf = kzalloc(event.buf_len, GFP_KERNEL);
	अगर (!event.msg_buf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	जबतक (1) अणु
		err = iavf_clean_arq_element(hw, &event, शून्य);
		/* When the AQ is empty, iavf_clean_arq_element will वापस
		 * nonzero and this loop will terminate.
		 */
		अगर (err)
			जाओ out_alloc;
		op =
		    (क्रमागत virtchnl_ops)le32_to_cpu(event.desc.cookie_high);
		अगर (op == VIRTCHNL_OP_VERSION)
			अवरोध;
	पूर्ण


	err = (क्रमागत iavf_status)le32_to_cpu(event.desc.cookie_low);
	अगर (err)
		जाओ out_alloc;

	अगर (op != VIRTCHNL_OP_VERSION) अणु
		dev_info(&adapter->pdev->dev, "Invalid reply type %d from PF\n",
			op);
		err = -EIO;
		जाओ out_alloc;
	पूर्ण

	pf_vvi = (काष्ठा virtchnl_version_info *)event.msg_buf;
	adapter->pf_version = *pf_vvi;

	अगर ((pf_vvi->major > VIRTCHNL_VERSION_MAJOR) ||
	    ((pf_vvi->major == VIRTCHNL_VERSION_MAJOR) &&
	     (pf_vvi->minor > VIRTCHNL_VERSION_MINOR)))
		err = -EIO;

out_alloc:
	kमुक्त(event.msg_buf);
out:
	वापस err;
पूर्ण

/**
 * iavf_send_vf_config_msg
 * @adapter: adapter काष्ठाure
 *
 * Send VF configuration request admin queue message to the PF. The reply
 * is not checked in this function. Returns 0 अगर the message was
 * successfully sent, or one of the IAVF_ADMIN_QUEUE_ERROR_ statuses अगर not.
 **/
पूर्णांक iavf_send_vf_config_msg(काष्ठा iavf_adapter *adapter)
अणु
	u32 caps;

	caps = VIRTCHNL_VF_OFFLOAD_L2 |
	       VIRTCHNL_VF_OFFLOAD_RSS_PF |
	       VIRTCHNL_VF_OFFLOAD_RSS_AQ |
	       VIRTCHNL_VF_OFFLOAD_RSS_REG |
	       VIRTCHNL_VF_OFFLOAD_VLAN |
	       VIRTCHNL_VF_OFFLOAD_WB_ON_ITR |
	       VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2 |
	       VIRTCHNL_VF_OFFLOAD_ENCAP |
	       VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM |
	       VIRTCHNL_VF_OFFLOAD_REQ_QUEUES |
	       VIRTCHNL_VF_OFFLOAD_ADQ |
	       VIRTCHNL_VF_OFFLOAD_USO |
	       VIRTCHNL_VF_OFFLOAD_Fसूची_PF |
	       VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF |
	       VIRTCHNL_VF_CAP_ADV_LINK_SPEED;

	adapter->current_op = VIRTCHNL_OP_GET_VF_RESOURCES;
	adapter->aq_required &= ~IAVF_FLAG_AQ_GET_CONFIG;
	अगर (PF_IS_V11(adapter))
		वापस iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_VF_RESOURCES,
					(u8 *)&caps, माप(caps));
	अन्यथा
		वापस iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_VF_RESOURCES,
					शून्य, 0);
पूर्ण

/**
 * iavf_validate_num_queues
 * @adapter: adapter काष्ठाure
 *
 * Validate that the number of queues the PF has sent in
 * VIRTCHNL_OP_GET_VF_RESOURCES is not larger than the VF can handle.
 **/
अटल व्योम iavf_validate_num_queues(काष्ठा iavf_adapter *adapter)
अणु
	अगर (adapter->vf_res->num_queue_pairs > IAVF_MAX_REQ_QUEUES) अणु
		काष्ठा virtchnl_vsi_resource *vsi_res;
		पूर्णांक i;

		dev_info(&adapter->pdev->dev, "Received %d queues, but can only have a max of %d\n",
			 adapter->vf_res->num_queue_pairs,
			 IAVF_MAX_REQ_QUEUES);
		dev_info(&adapter->pdev->dev, "Fixing by reducing queues to %d\n",
			 IAVF_MAX_REQ_QUEUES);
		adapter->vf_res->num_queue_pairs = IAVF_MAX_REQ_QUEUES;
		क्रम (i = 0; i < adapter->vf_res->num_vsis; i++) अणु
			vsi_res = &adapter->vf_res->vsi_res[i];
			vsi_res->num_queue_pairs = IAVF_MAX_REQ_QUEUES;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * iavf_get_vf_config
 * @adapter: निजी adapter काष्ठाure
 *
 * Get VF configuration from PF and populate hw काष्ठाure. Must be called after
 * admin queue is initialized. Busy रुकोs until response is received from PF,
 * with maximum समयout. Response from PF is वापसed in the buffer क्रम further
 * processing by the caller.
 **/
पूर्णांक iavf_get_vf_config(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_hw *hw = &adapter->hw;
	काष्ठा iavf_arq_event_info event;
	क्रमागत virtchnl_ops op;
	क्रमागत iavf_status err;
	u16 len;

	len =  माप(काष्ठा virtchnl_vf_resource) +
		IAVF_MAX_VF_VSI * माप(काष्ठा virtchnl_vsi_resource);
	event.buf_len = len;
	event.msg_buf = kzalloc(event.buf_len, GFP_KERNEL);
	अगर (!event.msg_buf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	जबतक (1) अणु
		/* When the AQ is empty, iavf_clean_arq_element will वापस
		 * nonzero and this loop will terminate.
		 */
		err = iavf_clean_arq_element(hw, &event, शून्य);
		अगर (err)
			जाओ out_alloc;
		op =
		    (क्रमागत virtchnl_ops)le32_to_cpu(event.desc.cookie_high);
		अगर (op == VIRTCHNL_OP_GET_VF_RESOURCES)
			अवरोध;
	पूर्ण

	err = (क्रमागत iavf_status)le32_to_cpu(event.desc.cookie_low);
	स_नकल(adapter->vf_res, event.msg_buf, min(event.msg_len, len));

	/* some PFs send more queues than we should have so validate that
	 * we aren't getting too many queues
	 */
	अगर (!err)
		iavf_validate_num_queues(adapter);
	iavf_vf_parse_hw_config(hw, adapter->vf_res);
out_alloc:
	kमुक्त(event.msg_buf);
out:
	वापस err;
पूर्ण

/**
 * iavf_configure_queues
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF set up our (previously allocated) queues.
 **/
व्योम iavf_configure_queues(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_vsi_queue_config_info *vqci;
	काष्ठा virtchnl_queue_pair_info *vqpi;
	पूर्णांक pairs = adapter->num_active_queues;
	पूर्णांक i, max_frame = IAVF_MAX_RXBUFFER;
	माप_प्रकार len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot configure queues, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_CONFIG_VSI_QUEUES;
	len = काष्ठा_size(vqci, qpair, pairs);
	vqci = kzalloc(len, GFP_KERNEL);
	अगर (!vqci)
		वापस;

	/* Limit maximum frame size when jumbo frames is not enabled */
	अगर (!(adapter->flags & IAVF_FLAG_LEGACY_RX) &&
	    (adapter->netdev->mtu <= ETH_DATA_LEN))
		max_frame = IAVF_RXBUFFER_1536 - NET_IP_ALIGN;

	vqci->vsi_id = adapter->vsi_res->vsi_id;
	vqci->num_queue_pairs = pairs;
	vqpi = vqci->qpair;
	/* Size check is not needed here - HW max is 16 queue pairs, and we
	 * can fit info क्रम 31 of them पूर्णांकo the AQ buffer beक्रमe it overflows.
	 */
	क्रम (i = 0; i < pairs; i++) अणु
		vqpi->txq.vsi_id = vqci->vsi_id;
		vqpi->txq.queue_id = i;
		vqpi->txq.ring_len = adapter->tx_rings[i].count;
		vqpi->txq.dma_ring_addr = adapter->tx_rings[i].dma;
		vqpi->rxq.vsi_id = vqci->vsi_id;
		vqpi->rxq.queue_id = i;
		vqpi->rxq.ring_len = adapter->rx_rings[i].count;
		vqpi->rxq.dma_ring_addr = adapter->rx_rings[i].dma;
		vqpi->rxq.max_pkt_size = max_frame;
		vqpi->rxq.databuffer_size =
			ALIGN(adapter->rx_rings[i].rx_buf_len,
			      BIT_ULL(IAVF_RXQ_CTX_DBUFF_SHIFT));
		vqpi++;
	पूर्ण

	adapter->aq_required &= ~IAVF_FLAG_AQ_CONFIGURE_QUEUES;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_VSI_QUEUES,
			 (u8 *)vqci, len);
	kमुक्त(vqci);
पूर्ण

/**
 * iavf_enable_queues
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF enable all of our queues.
 **/
व्योम iavf_enable_queues(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_queue_select vqs;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot enable queues, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_ENABLE_QUEUES;
	vqs.vsi_id = adapter->vsi_res->vsi_id;
	vqs.tx_queues = BIT(adapter->num_active_queues) - 1;
	vqs.rx_queues = vqs.tx_queues;
	adapter->aq_required &= ~IAVF_FLAG_AQ_ENABLE_QUEUES;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_ENABLE_QUEUES,
			 (u8 *)&vqs, माप(vqs));
पूर्ण

/**
 * iavf_disable_queues
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF disable all of our queues.
 **/
व्योम iavf_disable_queues(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_queue_select vqs;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot disable queues, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_DISABLE_QUEUES;
	vqs.vsi_id = adapter->vsi_res->vsi_id;
	vqs.tx_queues = BIT(adapter->num_active_queues) - 1;
	vqs.rx_queues = vqs.tx_queues;
	adapter->aq_required &= ~IAVF_FLAG_AQ_DISABLE_QUEUES;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DISABLE_QUEUES,
			 (u8 *)&vqs, माप(vqs));
पूर्ण

/**
 * iavf_map_queues
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF map queues to पूर्णांकerrupt vectors. Misc causes, including
 * admin queue, are always mapped to vector 0.
 **/
व्योम iavf_map_queues(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_irq_map_info *vimi;
	काष्ठा virtchnl_vector_map *vecmap;
	काष्ठा iavf_q_vector *q_vector;
	पूर्णांक v_idx, q_vectors;
	माप_प्रकार len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot map queues to vectors, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_CONFIG_IRQ_MAP;

	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	len = काष्ठा_size(vimi, vecmap, adapter->num_msix_vectors);
	vimi = kzalloc(len, GFP_KERNEL);
	अगर (!vimi)
		वापस;

	vimi->num_vectors = adapter->num_msix_vectors;
	/* Queue vectors first */
	क्रम (v_idx = 0; v_idx < q_vectors; v_idx++) अणु
		q_vector = &adapter->q_vectors[v_idx];
		vecmap = &vimi->vecmap[v_idx];

		vecmap->vsi_id = adapter->vsi_res->vsi_id;
		vecmap->vector_id = v_idx + NONQ_VECS;
		vecmap->txq_map = q_vector->ring_mask;
		vecmap->rxq_map = q_vector->ring_mask;
		vecmap->rxitr_idx = IAVF_RX_ITR;
		vecmap->txitr_idx = IAVF_TX_ITR;
	पूर्ण
	/* Misc vector last - this is only क्रम AdminQ messages */
	vecmap = &vimi->vecmap[v_idx];
	vecmap->vsi_id = adapter->vsi_res->vsi_id;
	vecmap->vector_id = 0;
	vecmap->txq_map = 0;
	vecmap->rxq_map = 0;

	adapter->aq_required &= ~IAVF_FLAG_AQ_MAP_VECTORS;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_IRQ_MAP,
			 (u8 *)vimi, len);
	kमुक्त(vimi);
पूर्ण

/**
 * iavf_add_ether_addrs
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF add one or more addresses to our filters.
 **/
व्योम iavf_add_ether_addrs(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_ether_addr_list *veal;
	काष्ठा iavf_mac_filter *f;
	पूर्णांक i = 0, count = 0;
	bool more = false;
	माप_प्रकार len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot add filters, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	list_क्रम_each_entry(f, &adapter->mac_filter_list, list) अणु
		अगर (f->add)
			count++;
	पूर्ण
	अगर (!count) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_MAC_FILTER;
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_ADD_ETH_ADDR;

	len = काष्ठा_size(veal, list, count);
	अगर (len > IAVF_MAX_AQ_BUF_SIZE) अणु
		dev_warn(&adapter->pdev->dev, "Too many add MAC changes in one request\n");
		count = (IAVF_MAX_AQ_BUF_SIZE -
			 माप(काष्ठा virtchnl_ether_addr_list)) /
			माप(काष्ठा virtchnl_ether_addr);
		len = काष्ठा_size(veal, list, count);
		more = true;
	पूर्ण

	veal = kzalloc(len, GFP_ATOMIC);
	अगर (!veal) अणु
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण

	veal->vsi_id = adapter->vsi_res->vsi_id;
	veal->num_elements = count;
	list_क्रम_each_entry(f, &adapter->mac_filter_list, list) अणु
		अगर (f->add) अणु
			ether_addr_copy(veal->list[i].addr, f->macaddr);
			i++;
			f->add = false;
			अगर (i == count)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!more)
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_MAC_FILTER;

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	iavf_send_pf_msg(adapter, VIRTCHNL_OP_ADD_ETH_ADDR, (u8 *)veal, len);
	kमुक्त(veal);
पूर्ण

/**
 * iavf_del_ether_addrs
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF हटाओ one or more addresses from our filters.
 **/
व्योम iavf_del_ether_addrs(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_ether_addr_list *veal;
	काष्ठा iavf_mac_filter *f, *fपंचांगp;
	पूर्णांक i = 0, count = 0;
	bool more = false;
	माप_प्रकार len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot remove filters, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	list_क्रम_each_entry(f, &adapter->mac_filter_list, list) अणु
		अगर (f->हटाओ)
			count++;
	पूर्ण
	अगर (!count) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_MAC_FILTER;
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_DEL_ETH_ADDR;

	len = काष्ठा_size(veal, list, count);
	अगर (len > IAVF_MAX_AQ_BUF_SIZE) अणु
		dev_warn(&adapter->pdev->dev, "Too many delete MAC changes in one request\n");
		count = (IAVF_MAX_AQ_BUF_SIZE -
			 माप(काष्ठा virtchnl_ether_addr_list)) /
			माप(काष्ठा virtchnl_ether_addr);
		len = काष्ठा_size(veal, list, count);
		more = true;
	पूर्ण
	veal = kzalloc(len, GFP_ATOMIC);
	अगर (!veal) अणु
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण

	veal->vsi_id = adapter->vsi_res->vsi_id;
	veal->num_elements = count;
	list_क्रम_each_entry_safe(f, fपंचांगp, &adapter->mac_filter_list, list) अणु
		अगर (f->हटाओ) अणु
			ether_addr_copy(veal->list[i].addr, f->macaddr);
			i++;
			list_del(&f->list);
			kमुक्त(f);
			अगर (i == count)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!more)
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_MAC_FILTER;

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DEL_ETH_ADDR, (u8 *)veal, len);
	kमुक्त(veal);
पूर्ण

/**
 * iavf_add_vlans
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF add one or more VLAN filters to our VSI.
 **/
व्योम iavf_add_vlans(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_vlan_filter_list *vvfl;
	पूर्णांक len, i = 0, count = 0;
	काष्ठा iavf_vlan_filter *f;
	bool more = false;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot add VLANs, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	list_क्रम_each_entry(f, &adapter->vlan_filter_list, list) अणु
		अगर (f->add)
			count++;
	पूर्ण
	अगर (!count) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_VLAN_FILTER;
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_ADD_VLAN;

	len = माप(काष्ठा virtchnl_vlan_filter_list) +
	      (count * माप(u16));
	अगर (len > IAVF_MAX_AQ_BUF_SIZE) अणु
		dev_warn(&adapter->pdev->dev, "Too many add VLAN changes in one request\n");
		count = (IAVF_MAX_AQ_BUF_SIZE -
			 माप(काष्ठा virtchnl_vlan_filter_list)) /
			माप(u16);
		len = माप(काष्ठा virtchnl_vlan_filter_list) +
		      (count * माप(u16));
		more = true;
	पूर्ण
	vvfl = kzalloc(len, GFP_ATOMIC);
	अगर (!vvfl) अणु
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण

	vvfl->vsi_id = adapter->vsi_res->vsi_id;
	vvfl->num_elements = count;
	list_क्रम_each_entry(f, &adapter->vlan_filter_list, list) अणु
		अगर (f->add) अणु
			vvfl->vlan_id[i] = f->vlan;
			i++;
			f->add = false;
			अगर (i == count)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!more)
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_VLAN_FILTER;

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	iavf_send_pf_msg(adapter, VIRTCHNL_OP_ADD_VLAN, (u8 *)vvfl, len);
	kमुक्त(vvfl);
पूर्ण

/**
 * iavf_del_vlans
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF हटाओ one or more VLAN filters from our VSI.
 **/
व्योम iavf_del_vlans(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_vlan_filter_list *vvfl;
	काष्ठा iavf_vlan_filter *f, *fपंचांगp;
	पूर्णांक len, i = 0, count = 0;
	bool more = false;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot remove VLANs, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	list_क्रम_each_entry(f, &adapter->vlan_filter_list, list) अणु
		अगर (f->हटाओ)
			count++;
	पूर्ण
	अगर (!count) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_VLAN_FILTER;
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_DEL_VLAN;

	len = माप(काष्ठा virtchnl_vlan_filter_list) +
	      (count * माप(u16));
	अगर (len > IAVF_MAX_AQ_BUF_SIZE) अणु
		dev_warn(&adapter->pdev->dev, "Too many delete VLAN changes in one request\n");
		count = (IAVF_MAX_AQ_BUF_SIZE -
			 माप(काष्ठा virtchnl_vlan_filter_list)) /
			माप(u16);
		len = माप(काष्ठा virtchnl_vlan_filter_list) +
		      (count * माप(u16));
		more = true;
	पूर्ण
	vvfl = kzalloc(len, GFP_ATOMIC);
	अगर (!vvfl) अणु
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		वापस;
	पूर्ण

	vvfl->vsi_id = adapter->vsi_res->vsi_id;
	vvfl->num_elements = count;
	list_क्रम_each_entry_safe(f, fपंचांगp, &adapter->vlan_filter_list, list) अणु
		अगर (f->हटाओ) अणु
			vvfl->vlan_id[i] = f->vlan;
			i++;
			list_del(&f->list);
			kमुक्त(f);
			अगर (i == count)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!more)
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_VLAN_FILTER;

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DEL_VLAN, (u8 *)vvfl, len);
	kमुक्त(vvfl);
पूर्ण

/**
 * iavf_set_promiscuous
 * @adapter: adapter काष्ठाure
 * @flags: biपंचांगask to control unicast/multicast promiscuous.
 *
 * Request that the PF enable promiscuous mode क्रम our VSI.
 **/
व्योम iavf_set_promiscuous(काष्ठा iavf_adapter *adapter, पूर्णांक flags)
अणु
	काष्ठा virtchnl_promisc_info vpi;
	पूर्णांक promisc_all;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot set promiscuous mode, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	promisc_all = FLAG_VF_UNICAST_PROMISC |
		      FLAG_VF_MULTICAST_PROMISC;
	अगर ((flags & promisc_all) == promisc_all) अणु
		adapter->flags |= IAVF_FLAG_PROMISC_ON;
		adapter->aq_required &= ~IAVF_FLAG_AQ_REQUEST_PROMISC;
		dev_info(&adapter->pdev->dev, "Entering promiscuous mode\n");
	पूर्ण

	अगर (flags & FLAG_VF_MULTICAST_PROMISC) अणु
		adapter->flags |= IAVF_FLAG_ALLMULTI_ON;
		adapter->aq_required &= ~IAVF_FLAG_AQ_REQUEST_ALLMULTI;
		dev_info(&adapter->pdev->dev, "Entering multicast promiscuous mode\n");
	पूर्ण

	अगर (!flags) अणु
		adapter->flags &= ~(IAVF_FLAG_PROMISC_ON |
				    IAVF_FLAG_ALLMULTI_ON);
		adapter->aq_required &= ~(IAVF_FLAG_AQ_RELEASE_PROMISC |
					  IAVF_FLAG_AQ_RELEASE_ALLMULTI);
		dev_info(&adapter->pdev->dev, "Leaving promiscuous mode\n");
	पूर्ण

	adapter->current_op = VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE;
	vpi.vsi_id = adapter->vsi_res->vsi_id;
	vpi.flags = flags;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE,
			 (u8 *)&vpi, माप(vpi));
पूर्ण

/**
 * iavf_request_stats
 * @adapter: adapter काष्ठाure
 *
 * Request VSI statistics from PF.
 **/
व्योम iavf_request_stats(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_queue_select vqs;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* no error message, this isn't crucial */
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_GET_STATS;
	vqs.vsi_id = adapter->vsi_res->vsi_id;
	/* queue maps are ignored क्रम this message - only the vsi is used */
	अगर (iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_STATS, (u8 *)&vqs,
			     माप(vqs)))
		/* अगर the request failed, करोn't lock out others */
		adapter->current_op = VIRTCHNL_OP_UNKNOWN;
पूर्ण

/**
 * iavf_get_hena
 * @adapter: adapter काष्ठाure
 *
 * Request hash enable capabilities from PF
 **/
व्योम iavf_get_hena(काष्ठा iavf_adapter *adapter)
अणु
	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot get RSS hash capabilities, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_GET_RSS_HENA_CAPS;
	adapter->aq_required &= ~IAVF_FLAG_AQ_GET_HENA;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_RSS_HENA_CAPS, शून्य, 0);
पूर्ण

/**
 * iavf_set_hena
 * @adapter: adapter काष्ठाure
 *
 * Request the PF to set our RSS hash capabilities
 **/
व्योम iavf_set_hena(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_rss_hena vrh;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot set RSS hash enable, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	vrh.hena = adapter->hena;
	adapter->current_op = VIRTCHNL_OP_SET_RSS_HENA;
	adapter->aq_required &= ~IAVF_FLAG_AQ_SET_HENA;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_SET_RSS_HENA, (u8 *)&vrh,
			 माप(vrh));
पूर्ण

/**
 * iavf_set_rss_key
 * @adapter: adapter काष्ठाure
 *
 * Request the PF to set our RSS hash key
 **/
व्योम iavf_set_rss_key(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_rss_key *vrk;
	पूर्णांक len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot set RSS key, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	len = माप(काष्ठा virtchnl_rss_key) +
	      (adapter->rss_key_size * माप(u8)) - 1;
	vrk = kzalloc(len, GFP_KERNEL);
	अगर (!vrk)
		वापस;
	vrk->vsi_id = adapter->vsi.id;
	vrk->key_len = adapter->rss_key_size;
	स_नकल(vrk->key, adapter->rss_key, adapter->rss_key_size);

	adapter->current_op = VIRTCHNL_OP_CONFIG_RSS_KEY;
	adapter->aq_required &= ~IAVF_FLAG_AQ_SET_RSS_KEY;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_RSS_KEY, (u8 *)vrk, len);
	kमुक्त(vrk);
पूर्ण

/**
 * iavf_set_rss_lut
 * @adapter: adapter काष्ठाure
 *
 * Request the PF to set our RSS lookup table
 **/
व्योम iavf_set_rss_lut(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_rss_lut *vrl;
	पूर्णांक len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot set RSS LUT, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	len = माप(काष्ठा virtchnl_rss_lut) +
	      (adapter->rss_lut_size * माप(u8)) - 1;
	vrl = kzalloc(len, GFP_KERNEL);
	अगर (!vrl)
		वापस;
	vrl->vsi_id = adapter->vsi.id;
	vrl->lut_entries = adapter->rss_lut_size;
	स_नकल(vrl->lut, adapter->rss_lut, adapter->rss_lut_size);
	adapter->current_op = VIRTCHNL_OP_CONFIG_RSS_LUT;
	adapter->aq_required &= ~IAVF_FLAG_AQ_SET_RSS_LUT;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_RSS_LUT, (u8 *)vrl, len);
	kमुक्त(vrl);
पूर्ण

/**
 * iavf_enable_vlan_stripping
 * @adapter: adapter काष्ठाure
 *
 * Request VLAN header stripping to be enabled
 **/
व्योम iavf_enable_vlan_stripping(काष्ठा iavf_adapter *adapter)
अणु
	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot enable stripping, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_ENABLE_VLAN_STRIPPING;
	adapter->aq_required &= ~IAVF_FLAG_AQ_ENABLE_VLAN_STRIPPING;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_ENABLE_VLAN_STRIPPING, शून्य, 0);
पूर्ण

/**
 * iavf_disable_vlan_stripping
 * @adapter: adapter काष्ठाure
 *
 * Request VLAN header stripping to be disabled
 **/
व्योम iavf_disable_vlan_stripping(काष्ठा iavf_adapter *adapter)
अणु
	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot disable stripping, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_DISABLE_VLAN_STRIPPING;
	adapter->aq_required &= ~IAVF_FLAG_AQ_DISABLE_VLAN_STRIPPING;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DISABLE_VLAN_STRIPPING, शून्य, 0);
पूर्ण

#घोषणा IAVF_MAX_SPEED_STRLEN	13

/**
 * iavf_prपूर्णांक_link_message - prपूर्णांक link up or करोwn
 * @adapter: adapter काष्ठाure
 *
 * Log a message telling the world of our wonderous link status
 */
अटल व्योम iavf_prपूर्णांक_link_message(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक link_speed_mbps;
	अक्षर *speed;

	अगर (!adapter->link_up) अणु
		netdev_info(netdev, "NIC Link is Down\n");
		वापस;
	पूर्ण

	speed = kzalloc(IAVF_MAX_SPEED_STRLEN, GFP_KERNEL);
	अगर (!speed)
		वापस;

	अगर (ADV_LINK_SUPPORT(adapter)) अणु
		link_speed_mbps = adapter->link_speed_mbps;
		जाओ prपूर्णांक_link_msg;
	पूर्ण

	चयन (adapter->link_speed) अणु
	हाल VIRTCHNL_LINK_SPEED_40GB:
		link_speed_mbps = SPEED_40000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_25GB:
		link_speed_mbps = SPEED_25000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_20GB:
		link_speed_mbps = SPEED_20000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_10GB:
		link_speed_mbps = SPEED_10000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_5GB:
		link_speed_mbps = SPEED_5000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_2_5GB:
		link_speed_mbps = SPEED_2500;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_1GB:
		link_speed_mbps = SPEED_1000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_100MB:
		link_speed_mbps = SPEED_100;
		अवरोध;
	शेष:
		link_speed_mbps = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

prपूर्णांक_link_msg:
	अगर (link_speed_mbps > SPEED_1000) अणु
		अगर (link_speed_mbps == SPEED_2500)
			snम_लिखो(speed, IAVF_MAX_SPEED_STRLEN, "2.5 Gbps");
		अन्यथा
			/* convert to Gbps अंतरभूत */
			snम_लिखो(speed, IAVF_MAX_SPEED_STRLEN, "%d %s",
				 link_speed_mbps / 1000, "Gbps");
	पूर्ण अन्यथा अगर (link_speed_mbps == SPEED_UNKNOWN) अणु
		snम_लिखो(speed, IAVF_MAX_SPEED_STRLEN, "%s", "Unknown Mbps");
	पूर्ण अन्यथा अणु
		snम_लिखो(speed, IAVF_MAX_SPEED_STRLEN, "%u %s",
			 link_speed_mbps, "Mbps");
	पूर्ण

	netdev_info(netdev, "NIC Link is Up Speed is %s Full Duplex\n", speed);
	kमुक्त(speed);
पूर्ण

/**
 * iavf_get_vpe_link_status
 * @adapter: adapter काष्ठाure
 * @vpe: virtchnl_pf_event काष्ठाure
 *
 * Helper function क्रम determining the link status
 **/
अटल bool
iavf_get_vpe_link_status(काष्ठा iavf_adapter *adapter,
			 काष्ठा virtchnl_pf_event *vpe)
अणु
	अगर (ADV_LINK_SUPPORT(adapter))
		वापस vpe->event_data.link_event_adv.link_status;
	अन्यथा
		वापस vpe->event_data.link_event.link_status;
पूर्ण

/**
 * iavf_set_adapter_link_speed_from_vpe
 * @adapter: adapter काष्ठाure क्रम which we are setting the link speed
 * @vpe: virtchnl_pf_event काष्ठाure that contains the link speed we are setting
 *
 * Helper function क्रम setting iavf_adapter link speed
 **/
अटल व्योम
iavf_set_adapter_link_speed_from_vpe(काष्ठा iavf_adapter *adapter,
				     काष्ठा virtchnl_pf_event *vpe)
अणु
	अगर (ADV_LINK_SUPPORT(adapter))
		adapter->link_speed_mbps =
			vpe->event_data.link_event_adv.link_speed;
	अन्यथा
		adapter->link_speed = vpe->event_data.link_event.link_speed;
पूर्ण

/**
 * iavf_enable_channels
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF enable channels as specअगरied by
 * the user via tc tool.
 **/
व्योम iavf_enable_channels(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_tc_info *vti = शून्य;
	माप_प्रकार len;
	पूर्णांक i;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot configure mqprio, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	len = काष्ठा_size(vti, list, adapter->num_tc - 1);
	vti = kzalloc(len, GFP_KERNEL);
	अगर (!vti)
		वापस;
	vti->num_tc = adapter->num_tc;
	क्रम (i = 0; i < vti->num_tc; i++) अणु
		vti->list[i].count = adapter->ch_config.ch_info[i].count;
		vti->list[i].offset = adapter->ch_config.ch_info[i].offset;
		vti->list[i].pad = 0;
		vti->list[i].max_tx_rate =
				adapter->ch_config.ch_info[i].max_tx_rate;
	पूर्ण

	adapter->ch_config.state = __IAVF_TC_RUNNING;
	adapter->flags |= IAVF_FLAG_REINIT_ITR_NEEDED;
	adapter->current_op = VIRTCHNL_OP_ENABLE_CHANNELS;
	adapter->aq_required &= ~IAVF_FLAG_AQ_ENABLE_CHANNELS;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_ENABLE_CHANNELS, (u8 *)vti, len);
	kमुक्त(vti);
पूर्ण

/**
 * iavf_disable_channels
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF disable channels that are configured
 **/
व्योम iavf_disable_channels(काष्ठा iavf_adapter *adapter)
अणु
	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot configure mqprio, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	adapter->ch_config.state = __IAVF_TC_INVALID;
	adapter->flags |= IAVF_FLAG_REINIT_ITR_NEEDED;
	adapter->current_op = VIRTCHNL_OP_DISABLE_CHANNELS;
	adapter->aq_required &= ~IAVF_FLAG_AQ_DISABLE_CHANNELS;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DISABLE_CHANNELS, शून्य, 0);
पूर्ण

/**
 * iavf_prपूर्णांक_cloud_filter
 * @adapter: adapter काष्ठाure
 * @f: cloud filter to prपूर्णांक
 *
 * Prपूर्णांक the cloud filter
 **/
अटल व्योम iavf_prपूर्णांक_cloud_filter(काष्ठा iavf_adapter *adapter,
				    काष्ठा virtchnl_filter *f)
अणु
	चयन (f->flow_type) अणु
	हाल VIRTCHNL_TCP_V4_FLOW:
		dev_info(&adapter->pdev->dev, "dst_mac: %pM src_mac: %pM vlan_id: %hu dst_ip: %pI4 src_ip %pI4 dst_port %hu src_port %hu\n",
			 &f->data.tcp_spec.dst_mac,
			 &f->data.tcp_spec.src_mac,
			 ntohs(f->data.tcp_spec.vlan_id),
			 &f->data.tcp_spec.dst_ip[0],
			 &f->data.tcp_spec.src_ip[0],
			 ntohs(f->data.tcp_spec.dst_port),
			 ntohs(f->data.tcp_spec.src_port));
		अवरोध;
	हाल VIRTCHNL_TCP_V6_FLOW:
		dev_info(&adapter->pdev->dev, "dst_mac: %pM src_mac: %pM vlan_id: %hu dst_ip: %pI6 src_ip %pI6 dst_port %hu src_port %hu\n",
			 &f->data.tcp_spec.dst_mac,
			 &f->data.tcp_spec.src_mac,
			 ntohs(f->data.tcp_spec.vlan_id),
			 &f->data.tcp_spec.dst_ip,
			 &f->data.tcp_spec.src_ip,
			 ntohs(f->data.tcp_spec.dst_port),
			 ntohs(f->data.tcp_spec.src_port));
		अवरोध;
	पूर्ण
पूर्ण

/**
 * iavf_add_cloud_filter
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF add cloud filters as specअगरied
 * by the user via tc tool.
 **/
व्योम iavf_add_cloud_filter(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_cloud_filter *cf;
	काष्ठा virtchnl_filter *f;
	पूर्णांक len = 0, count = 0;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot add cloud filter, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	list_क्रम_each_entry(cf, &adapter->cloud_filter_list, list) अणु
		अगर (cf->add) अणु
			count++;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!count) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_CLOUD_FILTER;
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_ADD_CLOUD_FILTER;

	len = माप(काष्ठा virtchnl_filter);
	f = kzalloc(len, GFP_KERNEL);
	अगर (!f)
		वापस;

	list_क्रम_each_entry(cf, &adapter->cloud_filter_list, list) अणु
		अगर (cf->add) अणु
			स_नकल(f, &cf->f, माप(काष्ठा virtchnl_filter));
			cf->add = false;
			cf->state = __IAVF_CF_ADD_PENDING;
			iavf_send_pf_msg(adapter, VIRTCHNL_OP_ADD_CLOUD_FILTER,
					 (u8 *)f, len);
		पूर्ण
	पूर्ण
	kमुक्त(f);
पूर्ण

/**
 * iavf_del_cloud_filter
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF delete cloud filters as specअगरied
 * by the user via tc tool.
 **/
व्योम iavf_del_cloud_filter(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_cloud_filter *cf, *cfपंचांगp;
	काष्ठा virtchnl_filter *f;
	पूर्णांक len = 0, count = 0;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot remove cloud filter, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण
	list_क्रम_each_entry(cf, &adapter->cloud_filter_list, list) अणु
		अगर (cf->del) अणु
			count++;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!count) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_CLOUD_FILTER;
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_DEL_CLOUD_FILTER;

	len = माप(काष्ठा virtchnl_filter);
	f = kzalloc(len, GFP_KERNEL);
	अगर (!f)
		वापस;

	list_क्रम_each_entry_safe(cf, cfपंचांगp, &adapter->cloud_filter_list, list) अणु
		अगर (cf->del) अणु
			स_नकल(f, &cf->f, माप(काष्ठा virtchnl_filter));
			cf->del = false;
			cf->state = __IAVF_CF_DEL_PENDING;
			iavf_send_pf_msg(adapter, VIRTCHNL_OP_DEL_CLOUD_FILTER,
					 (u8 *)f, len);
		पूर्ण
	पूर्ण
	kमुक्त(f);
पूर्ण

/**
 * iavf_add_fdir_filter
 * @adapter: the VF adapter काष्ठाure
 *
 * Request that the PF add Flow Director filters as specअगरied
 * by the user via ethtool.
 **/
व्योम iavf_add_fdir_filter(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_fdir_fltr *fdir;
	काष्ठा virtchnl_fdir_add *f;
	bool process_fltr = false;
	पूर्णांक len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot add Flow Director filter, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	len = माप(काष्ठा virtchnl_fdir_add);
	f = kzalloc(len, GFP_KERNEL);
	अगर (!f)
		वापस;

	spin_lock_bh(&adapter->fdir_fltr_lock);
	list_क्रम_each_entry(fdir, &adapter->fdir_list_head, list) अणु
		अगर (fdir->state == IAVF_Fसूची_FLTR_ADD_REQUEST) अणु
			process_fltr = true;
			fdir->state = IAVF_Fसूची_FLTR_ADD_PENDING;
			स_नकल(f, &fdir->vc_add_msg, len);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	अगर (!process_fltr) अणु
		/* prevent iavf_add_fdir_filter() from being called when there
		 * are no filters to add
		 */
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_Fसूची_FILTER;
		kमुक्त(f);
		वापस;
	पूर्ण
	adapter->current_op = VIRTCHNL_OP_ADD_Fसूची_FILTER;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_ADD_Fसूची_FILTER, (u8 *)f, len);
	kमुक्त(f);
पूर्ण

/**
 * iavf_del_fdir_filter
 * @adapter: the VF adapter काष्ठाure
 *
 * Request that the PF delete Flow Director filters as specअगरied
 * by the user via ethtool.
 **/
व्योम iavf_del_fdir_filter(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा iavf_fdir_fltr *fdir;
	काष्ठा virtchnl_fdir_del f;
	bool process_fltr = false;
	पूर्णांक len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot remove Flow Director filter, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	len = माप(काष्ठा virtchnl_fdir_del);

	spin_lock_bh(&adapter->fdir_fltr_lock);
	list_क्रम_each_entry(fdir, &adapter->fdir_list_head, list) अणु
		अगर (fdir->state == IAVF_Fसूची_FLTR_DEL_REQUEST) अणु
			process_fltr = true;
			स_रखो(&f, 0, len);
			f.vsi_id = fdir->vc_add_msg.vsi_id;
			f.flow_id = fdir->flow_id;
			fdir->state = IAVF_Fसूची_FLTR_DEL_PENDING;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	अगर (!process_fltr) अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_Fसूची_FILTER;
		वापस;
	पूर्ण

	adapter->current_op = VIRTCHNL_OP_DEL_Fसूची_FILTER;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DEL_Fसूची_FILTER, (u8 *)&f, len);
पूर्ण

/**
 * iavf_add_adv_rss_cfg
 * @adapter: the VF adapter काष्ठाure
 *
 * Request that the PF add RSS configuration as specअगरied
 * by the user via ethtool.
 **/
व्योम iavf_add_adv_rss_cfg(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_rss_cfg *rss_cfg;
	काष्ठा iavf_adv_rss *rss;
	bool process_rss = false;
	पूर्णांक len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot add RSS configuration, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	len = माप(काष्ठा virtchnl_rss_cfg);
	rss_cfg = kzalloc(len, GFP_KERNEL);
	अगर (!rss_cfg)
		वापस;

	spin_lock_bh(&adapter->adv_rss_lock);
	list_क्रम_each_entry(rss, &adapter->adv_rss_list_head, list) अणु
		अगर (rss->state == IAVF_ADV_RSS_ADD_REQUEST) अणु
			process_rss = true;
			rss->state = IAVF_ADV_RSS_ADD_PENDING;
			स_नकल(rss_cfg, &rss->cfg_msg, len);
			iavf_prपूर्णांक_adv_rss_cfg(adapter, rss,
					       "Input set change for",
					       "is pending");
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adapter->adv_rss_lock);

	अगर (process_rss) अणु
		adapter->current_op = VIRTCHNL_OP_ADD_RSS_CFG;
		iavf_send_pf_msg(adapter, VIRTCHNL_OP_ADD_RSS_CFG,
				 (u8 *)rss_cfg, len);
	पूर्ण अन्यथा अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_ADD_ADV_RSS_CFG;
	पूर्ण

	kमुक्त(rss_cfg);
पूर्ण

/**
 * iavf_del_adv_rss_cfg
 * @adapter: the VF adapter काष्ठाure
 *
 * Request that the PF delete RSS configuration as specअगरied
 * by the user via ethtool.
 **/
व्योम iavf_del_adv_rss_cfg(काष्ठा iavf_adapter *adapter)
अणु
	काष्ठा virtchnl_rss_cfg *rss_cfg;
	काष्ठा iavf_adv_rss *rss;
	bool process_rss = false;
	पूर्णांक len;

	अगर (adapter->current_op != VIRTCHNL_OP_UNKNOWN) अणु
		/* bail because we alपढ़ोy have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot remove RSS configuration, command %d pending\n",
			adapter->current_op);
		वापस;
	पूर्ण

	len = माप(काष्ठा virtchnl_rss_cfg);
	rss_cfg = kzalloc(len, GFP_KERNEL);
	अगर (!rss_cfg)
		वापस;

	spin_lock_bh(&adapter->adv_rss_lock);
	list_क्रम_each_entry(rss, &adapter->adv_rss_list_head, list) अणु
		अगर (rss->state == IAVF_ADV_RSS_DEL_REQUEST) अणु
			process_rss = true;
			rss->state = IAVF_ADV_RSS_DEL_PENDING;
			स_नकल(rss_cfg, &rss->cfg_msg, len);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adapter->adv_rss_lock);

	अगर (process_rss) अणु
		adapter->current_op = VIRTCHNL_OP_DEL_RSS_CFG;
		iavf_send_pf_msg(adapter, VIRTCHNL_OP_DEL_RSS_CFG,
				 (u8 *)rss_cfg, len);
	पूर्ण अन्यथा अणु
		adapter->aq_required &= ~IAVF_FLAG_AQ_DEL_ADV_RSS_CFG;
	पूर्ण

	kमुक्त(rss_cfg);
पूर्ण

/**
 * iavf_request_reset
 * @adapter: adapter काष्ठाure
 *
 * Request that the PF reset this VF. No response is expected.
 **/
व्योम iavf_request_reset(काष्ठा iavf_adapter *adapter)
अणु
	/* Don't check CURRENT_OP - this is always higher priority */
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_RESET_VF, शून्य, 0);
	adapter->current_op = VIRTCHNL_OP_UNKNOWN;
पूर्ण

/**
 * iavf_virtchnl_completion
 * @adapter: adapter काष्ठाure
 * @v_opcode: opcode sent by PF
 * @v_retval: retval sent by PF
 * @msg: message sent by PF
 * @msglen: message length
 *
 * Asynchronous completion function क्रम admin queue messages. Rather than busy
 * रुको, we fire off our requests and assume that no errors will be वापसed.
 * This function handles the reply messages.
 **/
व्योम iavf_virtchnl_completion(काष्ठा iavf_adapter *adapter,
			      क्रमागत virtchnl_ops v_opcode,
			      क्रमागत iavf_status v_retval, u8 *msg, u16 msglen)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (v_opcode == VIRTCHNL_OP_EVENT) अणु
		काष्ठा virtchnl_pf_event *vpe =
			(काष्ठा virtchnl_pf_event *)msg;
		bool link_up = iavf_get_vpe_link_status(adapter, vpe);

		चयन (vpe->event) अणु
		हाल VIRTCHNL_EVENT_LINK_CHANGE:
			iavf_set_adapter_link_speed_from_vpe(adapter, vpe);

			/* we've alपढ़ोy got the right link status, bail */
			अगर (adapter->link_up == link_up)
				अवरोध;

			अगर (link_up) अणु
				/* If we get link up message and start queues
				 * beक्रमe our queues are configured it will
				 * trigger a TX hang. In that हाल, just ignore
				 * the link status message,we'll get another one
				 * after we enable queues and actually prepared
				 * to send traffic.
				 */
				अगर (adapter->state != __IAVF_RUNNING)
					अवरोध;

				/* For ADq enabled VF, we reconfigure VSIs and
				 * re-allocate queues. Hence रुको till all
				 * queues are enabled.
				 */
				अगर (adapter->flags &
				    IAVF_FLAG_QUEUES_DISABLED)
					अवरोध;
			पूर्ण

			adapter->link_up = link_up;
			अगर (link_up) अणु
				netअगर_tx_start_all_queues(netdev);
				netअगर_carrier_on(netdev);
			पूर्ण अन्यथा अणु
				netअगर_tx_stop_all_queues(netdev);
				netअगर_carrier_off(netdev);
			पूर्ण
			iavf_prपूर्णांक_link_message(adapter);
			अवरोध;
		हाल VIRTCHNL_EVENT_RESET_IMPENDING:
			dev_info(&adapter->pdev->dev, "Reset warning received from the PF\n");
			अगर (!(adapter->flags & IAVF_FLAG_RESET_PENDING)) अणु
				adapter->flags |= IAVF_FLAG_RESET_PENDING;
				dev_info(&adapter->pdev->dev, "Scheduling reset task\n");
				queue_work(iavf_wq, &adapter->reset_task);
			पूर्ण
			अवरोध;
		शेष:
			dev_err(&adapter->pdev->dev, "Unknown event %d from PF\n",
				vpe->event);
			अवरोध;
		पूर्ण
		वापस;
	पूर्ण
	अगर (v_retval) अणु
		चयन (v_opcode) अणु
		हाल VIRTCHNL_OP_ADD_VLAN:
			dev_err(&adapter->pdev->dev, "Failed to add VLAN filter, error %s\n",
				iavf_stat_str(&adapter->hw, v_retval));
			अवरोध;
		हाल VIRTCHNL_OP_ADD_ETH_ADDR:
			dev_err(&adapter->pdev->dev, "Failed to add MAC filter, error %s\n",
				iavf_stat_str(&adapter->hw, v_retval));
			/* restore administratively set MAC address */
			ether_addr_copy(adapter->hw.mac.addr, netdev->dev_addr);
			अवरोध;
		हाल VIRTCHNL_OP_DEL_VLAN:
			dev_err(&adapter->pdev->dev, "Failed to delete VLAN filter, error %s\n",
				iavf_stat_str(&adapter->hw, v_retval));
			अवरोध;
		हाल VIRTCHNL_OP_DEL_ETH_ADDR:
			dev_err(&adapter->pdev->dev, "Failed to delete MAC filter, error %s\n",
				iavf_stat_str(&adapter->hw, v_retval));
			अवरोध;
		हाल VIRTCHNL_OP_ENABLE_CHANNELS:
			dev_err(&adapter->pdev->dev, "Failed to configure queue channels, error %s\n",
				iavf_stat_str(&adapter->hw, v_retval));
			adapter->flags &= ~IAVF_FLAG_REINIT_ITR_NEEDED;
			adapter->ch_config.state = __IAVF_TC_INVALID;
			netdev_reset_tc(netdev);
			netअगर_tx_start_all_queues(netdev);
			अवरोध;
		हाल VIRTCHNL_OP_DISABLE_CHANNELS:
			dev_err(&adapter->pdev->dev, "Failed to disable queue channels, error %s\n",
				iavf_stat_str(&adapter->hw, v_retval));
			adapter->flags &= ~IAVF_FLAG_REINIT_ITR_NEEDED;
			adapter->ch_config.state = __IAVF_TC_RUNNING;
			netअगर_tx_start_all_queues(netdev);
			अवरोध;
		हाल VIRTCHNL_OP_ADD_CLOUD_FILTER: अणु
			काष्ठा iavf_cloud_filter *cf, *cfपंचांगp;

			list_क्रम_each_entry_safe(cf, cfपंचांगp,
						 &adapter->cloud_filter_list,
						 list) अणु
				अगर (cf->state == __IAVF_CF_ADD_PENDING) अणु
					cf->state = __IAVF_CF_INVALID;
					dev_info(&adapter->pdev->dev, "Failed to add cloud filter, error %s\n",
						 iavf_stat_str(&adapter->hw,
							       v_retval));
					iavf_prपूर्णांक_cloud_filter(adapter,
								&cf->f);
					list_del(&cf->list);
					kमुक्त(cf);
					adapter->num_cloud_filters--;
				पूर्ण
			पूर्ण
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_OP_DEL_CLOUD_FILTER: अणु
			काष्ठा iavf_cloud_filter *cf;

			list_क्रम_each_entry(cf, &adapter->cloud_filter_list,
					    list) अणु
				अगर (cf->state == __IAVF_CF_DEL_PENDING) अणु
					cf->state = __IAVF_CF_ACTIVE;
					dev_info(&adapter->pdev->dev, "Failed to del cloud filter, error %s\n",
						 iavf_stat_str(&adapter->hw,
							       v_retval));
					iavf_prपूर्णांक_cloud_filter(adapter,
								&cf->f);
				पूर्ण
			पूर्ण
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_OP_ADD_Fसूची_FILTER: अणु
			काष्ठा iavf_fdir_fltr *fdir, *fdir_पंचांगp;

			spin_lock_bh(&adapter->fdir_fltr_lock);
			list_क्रम_each_entry_safe(fdir, fdir_पंचांगp,
						 &adapter->fdir_list_head,
						 list) अणु
				अगर (fdir->state == IAVF_Fसूची_FLTR_ADD_PENDING) अणु
					dev_info(&adapter->pdev->dev, "Failed to add Flow Director filter, error %s\n",
						 iavf_stat_str(&adapter->hw,
							       v_retval));
					iavf_prपूर्णांक_fdir_fltr(adapter, fdir);
					अगर (msglen)
						dev_err(&adapter->pdev->dev,
							"%s\n", msg);
					list_del(&fdir->list);
					kमुक्त(fdir);
					adapter->fdir_active_fltr--;
				पूर्ण
			पूर्ण
			spin_unlock_bh(&adapter->fdir_fltr_lock);
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_OP_DEL_Fसूची_FILTER: अणु
			काष्ठा iavf_fdir_fltr *fdir;

			spin_lock_bh(&adapter->fdir_fltr_lock);
			list_क्रम_each_entry(fdir, &adapter->fdir_list_head,
					    list) अणु
				अगर (fdir->state == IAVF_Fसूची_FLTR_DEL_PENDING) अणु
					fdir->state = IAVF_Fसूची_FLTR_ACTIVE;
					dev_info(&adapter->pdev->dev, "Failed to del Flow Director filter, error %s\n",
						 iavf_stat_str(&adapter->hw,
							       v_retval));
					iavf_prपूर्णांक_fdir_fltr(adapter, fdir);
				पूर्ण
			पूर्ण
			spin_unlock_bh(&adapter->fdir_fltr_lock);
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_OP_ADD_RSS_CFG: अणु
			काष्ठा iavf_adv_rss *rss, *rss_पंचांगp;

			spin_lock_bh(&adapter->adv_rss_lock);
			list_क्रम_each_entry_safe(rss, rss_पंचांगp,
						 &adapter->adv_rss_list_head,
						 list) अणु
				अगर (rss->state == IAVF_ADV_RSS_ADD_PENDING) अणु
					iavf_prपूर्णांक_adv_rss_cfg(adapter, rss,
							       "Failed to change the input set for",
							       शून्य);
					list_del(&rss->list);
					kमुक्त(rss);
				पूर्ण
			पूर्ण
			spin_unlock_bh(&adapter->adv_rss_lock);
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_OP_DEL_RSS_CFG: अणु
			काष्ठा iavf_adv_rss *rss;

			spin_lock_bh(&adapter->adv_rss_lock);
			list_क्रम_each_entry(rss, &adapter->adv_rss_list_head,
					    list) अणु
				अगर (rss->state == IAVF_ADV_RSS_DEL_PENDING) अणु
					rss->state = IAVF_ADV_RSS_ACTIVE;
					dev_err(&adapter->pdev->dev, "Failed to delete RSS configuration, error %s\n",
						iavf_stat_str(&adapter->hw,
							      v_retval));
				पूर्ण
			पूर्ण
			spin_unlock_bh(&adapter->adv_rss_lock);
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_OP_ENABLE_VLAN_STRIPPING:
		हाल VIRTCHNL_OP_DISABLE_VLAN_STRIPPING:
			dev_warn(&adapter->pdev->dev, "Changing VLAN Stripping is not allowed when Port VLAN is configured\n");
			अवरोध;
		शेष:
			dev_err(&adapter->pdev->dev, "PF returned error %d (%s) to our request %d\n",
				v_retval, iavf_stat_str(&adapter->hw, v_retval),
				v_opcode);
		पूर्ण
	पूर्ण
	चयन (v_opcode) अणु
	हाल VIRTCHNL_OP_ADD_ETH_ADDR: अणु
		अगर (!ether_addr_equal(netdev->dev_addr, adapter->hw.mac.addr))
			ether_addr_copy(netdev->dev_addr, adapter->hw.mac.addr);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_GET_STATS: अणु
		काष्ठा iavf_eth_stats *stats =
			(काष्ठा iavf_eth_stats *)msg;
		netdev->stats.rx_packets = stats->rx_unicast +
					   stats->rx_multicast +
					   stats->rx_broadcast;
		netdev->stats.tx_packets = stats->tx_unicast +
					   stats->tx_multicast +
					   stats->tx_broadcast;
		netdev->stats.rx_bytes = stats->rx_bytes;
		netdev->stats.tx_bytes = stats->tx_bytes;
		netdev->stats.tx_errors = stats->tx_errors;
		netdev->stats.rx_dropped = stats->rx_discards;
		netdev->stats.tx_dropped = stats->tx_discards;
		adapter->current_stats = *stats;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_GET_VF_RESOURCES: अणु
		u16 len = माप(काष्ठा virtchnl_vf_resource) +
			  IAVF_MAX_VF_VSI *
			  माप(काष्ठा virtchnl_vsi_resource);
		स_नकल(adapter->vf_res, msg, min(msglen, len));
		iavf_validate_num_queues(adapter);
		iavf_vf_parse_hw_config(&adapter->hw, adapter->vf_res);
		अगर (is_zero_ether_addr(adapter->hw.mac.addr)) अणु
			/* restore current mac address */
			ether_addr_copy(adapter->hw.mac.addr, netdev->dev_addr);
		पूर्ण अन्यथा अणु
			/* refresh current mac address अगर changed */
			ether_addr_copy(netdev->dev_addr, adapter->hw.mac.addr);
			ether_addr_copy(netdev->perm_addr,
					adapter->hw.mac.addr);
		पूर्ण
		spin_lock_bh(&adapter->mac_vlan_list_lock);
		iavf_add_filter(adapter, adapter->hw.mac.addr);
		spin_unlock_bh(&adapter->mac_vlan_list_lock);
		iavf_process_config(adapter);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_QUEUES:
		/* enable transmits */
		iavf_irq_enable(adapter, true);
		adapter->flags &= ~IAVF_FLAG_QUEUES_DISABLED;
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_QUEUES:
		iavf_मुक्त_all_tx_resources(adapter);
		iavf_मुक्त_all_rx_resources(adapter);
		अगर (adapter->state == __IAVF_DOWN_PENDING) अणु
			adapter->state = __IAVF_DOWN;
			wake_up(&adapter->करोwn_रुकोqueue);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_VERSION:
	हाल VIRTCHNL_OP_CONFIG_IRQ_MAP:
		/* Don't display an error अगर we get these out of sequence.
		 * If the firmware needed to get kicked, we'll get these and
		 * it's no problem.
		 */
		अगर (v_opcode != adapter->current_op)
			वापस;
		अवरोध;
	हाल VIRTCHNL_OP_IWARP:
		/* Gobble zero-length replies from the PF. They indicate that
		 * a previous message was received OK, and the client करोesn't
		 * care about that.
		 */
		अगर (msglen && CLIENT_ENABLED(adapter))
			iavf_notअगरy_client_message(&adapter->vsi, msg, msglen);
		अवरोध;

	हाल VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP:
		adapter->client_pending &=
				~(BIT(VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP));
		अवरोध;
	हाल VIRTCHNL_OP_GET_RSS_HENA_CAPS: अणु
		काष्ठा virtchnl_rss_hena *vrh = (काष्ठा virtchnl_rss_hena *)msg;

		अगर (msglen == माप(*vrh))
			adapter->hena = vrh->hena;
		अन्यथा
			dev_warn(&adapter->pdev->dev,
				 "Invalid message %d from PF\n", v_opcode);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_REQUEST_QUEUES: अणु
		काष्ठा virtchnl_vf_res_request *vfres =
			(काष्ठा virtchnl_vf_res_request *)msg;

		अगर (vfres->num_queue_pairs != adapter->num_req_queues) अणु
			dev_info(&adapter->pdev->dev,
				 "Requested %d queues, PF can support %d\n",
				 adapter->num_req_queues,
				 vfres->num_queue_pairs);
			adapter->num_req_queues = 0;
			adapter->flags &= ~IAVF_FLAG_REINIT_ITR_NEEDED;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_ADD_CLOUD_FILTER: अणु
		काष्ठा iavf_cloud_filter *cf;

		list_क्रम_each_entry(cf, &adapter->cloud_filter_list, list) अणु
			अगर (cf->state == __IAVF_CF_ADD_PENDING)
				cf->state = __IAVF_CF_ACTIVE;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_DEL_CLOUD_FILTER: अणु
		काष्ठा iavf_cloud_filter *cf, *cfपंचांगp;

		list_क्रम_each_entry_safe(cf, cfपंचांगp, &adapter->cloud_filter_list,
					 list) अणु
			अगर (cf->state == __IAVF_CF_DEL_PENDING) अणु
				cf->state = __IAVF_CF_INVALID;
				list_del(&cf->list);
				kमुक्त(cf);
				adapter->num_cloud_filters--;
			पूर्ण
		पूर्ण
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_ADD_Fसूची_FILTER: अणु
		काष्ठा virtchnl_fdir_add *add_fltr = (काष्ठा virtchnl_fdir_add *)msg;
		काष्ठा iavf_fdir_fltr *fdir, *fdir_पंचांगp;

		spin_lock_bh(&adapter->fdir_fltr_lock);
		list_क्रम_each_entry_safe(fdir, fdir_पंचांगp,
					 &adapter->fdir_list_head,
					 list) अणु
			अगर (fdir->state == IAVF_Fसूची_FLTR_ADD_PENDING) अणु
				अगर (add_fltr->status == VIRTCHNL_Fसूची_SUCCESS) अणु
					dev_info(&adapter->pdev->dev, "Flow Director filter with location %u is added\n",
						 fdir->loc);
					fdir->state = IAVF_Fसूची_FLTR_ACTIVE;
					fdir->flow_id = add_fltr->flow_id;
				पूर्ण अन्यथा अणु
					dev_info(&adapter->pdev->dev, "Failed to add Flow Director filter with status: %d\n",
						 add_fltr->status);
					iavf_prपूर्णांक_fdir_fltr(adapter, fdir);
					list_del(&fdir->list);
					kमुक्त(fdir);
					adapter->fdir_active_fltr--;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_bh(&adapter->fdir_fltr_lock);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_DEL_Fसूची_FILTER: अणु
		काष्ठा virtchnl_fdir_del *del_fltr = (काष्ठा virtchnl_fdir_del *)msg;
		काष्ठा iavf_fdir_fltr *fdir, *fdir_पंचांगp;

		spin_lock_bh(&adapter->fdir_fltr_lock);
		list_क्रम_each_entry_safe(fdir, fdir_पंचांगp, &adapter->fdir_list_head,
					 list) अणु
			अगर (fdir->state == IAVF_Fसूची_FLTR_DEL_PENDING) अणु
				अगर (del_fltr->status == VIRTCHNL_Fसूची_SUCCESS) अणु
					dev_info(&adapter->pdev->dev, "Flow Director filter with location %u is deleted\n",
						 fdir->loc);
					list_del(&fdir->list);
					kमुक्त(fdir);
					adapter->fdir_active_fltr--;
				पूर्ण अन्यथा अणु
					fdir->state = IAVF_Fसूची_FLTR_ACTIVE;
					dev_info(&adapter->pdev->dev, "Failed to delete Flow Director filter with status: %d\n",
						 del_fltr->status);
					iavf_prपूर्णांक_fdir_fltr(adapter, fdir);
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_bh(&adapter->fdir_fltr_lock);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_ADD_RSS_CFG: अणु
		काष्ठा iavf_adv_rss *rss;

		spin_lock_bh(&adapter->adv_rss_lock);
		list_क्रम_each_entry(rss, &adapter->adv_rss_list_head, list) अणु
			अगर (rss->state == IAVF_ADV_RSS_ADD_PENDING) अणु
				iavf_prपूर्णांक_adv_rss_cfg(adapter, rss,
						       "Input set change for",
						       "successful");
				rss->state = IAVF_ADV_RSS_ACTIVE;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&adapter->adv_rss_lock);
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_DEL_RSS_CFG: अणु
		काष्ठा iavf_adv_rss *rss, *rss_पंचांगp;

		spin_lock_bh(&adapter->adv_rss_lock);
		list_क्रम_each_entry_safe(rss, rss_पंचांगp,
					 &adapter->adv_rss_list_head, list) अणु
			अगर (rss->state == IAVF_ADV_RSS_DEL_PENDING) अणु
				list_del(&rss->list);
				kमुक्त(rss);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&adapter->adv_rss_lock);
		पूर्ण
		अवरोध;
	शेष:
		अगर (adapter->current_op && (v_opcode != adapter->current_op))
			dev_warn(&adapter->pdev->dev, "Expected response %d from PF, received %d\n",
				 adapter->current_op, v_opcode);
		अवरोध;
	पूर्ण /* चयन v_opcode */
	adapter->current_op = VIRTCHNL_OP_UNKNOWN;
पूर्ण
