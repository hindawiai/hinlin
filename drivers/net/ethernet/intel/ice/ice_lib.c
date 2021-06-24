<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice.h"
#समावेश "ice_base.h"
#समावेश "ice_flow.h"
#समावेश "ice_lib.h"
#समावेश "ice_fltr.h"
#समावेश "ice_dcb_lib.h"
#समावेश "ice_devlink.h"

/**
 * ice_vsi_type_str - maps VSI type क्रमागत to string equivalents
 * @vsi_type: VSI type क्रमागत
 */
स्थिर अक्षर *ice_vsi_type_str(क्रमागत ice_vsi_type vsi_type)
अणु
	चयन (vsi_type) अणु
	हाल ICE_VSI_PF:
		वापस "ICE_VSI_PF";
	हाल ICE_VSI_VF:
		वापस "ICE_VSI_VF";
	हाल ICE_VSI_CTRL:
		वापस "ICE_VSI_CTRL";
	हाल ICE_VSI_LB:
		वापस "ICE_VSI_LB";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/**
 * ice_vsi_ctrl_all_rx_rings - Start or stop a VSI's Rx rings
 * @vsi: the VSI being configured
 * @ena: start or stop the Rx rings
 *
 * First enable/disable all of the Rx rings, flush any reमुख्यing ग_लिखोs, and
 * then verअगरy that they have all been enabled/disabled successfully. This will
 * let all of the रेजिस्टर ग_लिखोs complete when enabling/disabling the Rx rings
 * beक्रमe रुकोing क्रम the change in hardware to complete.
 */
अटल पूर्णांक ice_vsi_ctrl_all_rx_rings(काष्ठा ice_vsi *vsi, bool ena)
अणु
	पूर्णांक ret = 0;
	u16 i;

	क्रम (i = 0; i < vsi->num_rxq; i++)
		ice_vsi_ctrl_one_rx_ring(vsi, ena, i, false);

	ice_flush(&vsi->back->hw);

	क्रम (i = 0; i < vsi->num_rxq; i++) अणु
		ret = ice_vsi_रुको_one_rx_ring(vsi, ena, i);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ice_vsi_alloc_arrays - Allocate queue and vector poपूर्णांकer arrays क्रम the VSI
 * @vsi: VSI poपूर्णांकer
 *
 * On error: वापसs error code (negative)
 * On success: वापसs 0
 */
अटल पूर्णांक ice_vsi_alloc_arrays(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);

	/* allocate memory क्रम both Tx and Rx ring poपूर्णांकers */
	vsi->tx_rings = devm_kसुस्मृति(dev, vsi->alloc_txq,
				     माप(*vsi->tx_rings), GFP_KERNEL);
	अगर (!vsi->tx_rings)
		वापस -ENOMEM;

	vsi->rx_rings = devm_kसुस्मृति(dev, vsi->alloc_rxq,
				     माप(*vsi->rx_rings), GFP_KERNEL);
	अगर (!vsi->rx_rings)
		जाओ err_rings;

	/* XDP will have vsi->alloc_txq Tx queues as well, so द्विगुन the size */
	vsi->txq_map = devm_kसुस्मृति(dev, (2 * vsi->alloc_txq),
				    माप(*vsi->txq_map), GFP_KERNEL);

	अगर (!vsi->txq_map)
		जाओ err_txq_map;

	vsi->rxq_map = devm_kसुस्मृति(dev, vsi->alloc_rxq,
				    माप(*vsi->rxq_map), GFP_KERNEL);
	अगर (!vsi->rxq_map)
		जाओ err_rxq_map;

	/* There is no need to allocate q_vectors क्रम a loopback VSI. */
	अगर (vsi->type == ICE_VSI_LB)
		वापस 0;

	/* allocate memory क्रम q_vector poपूर्णांकers */
	vsi->q_vectors = devm_kसुस्मृति(dev, vsi->num_q_vectors,
				      माप(*vsi->q_vectors), GFP_KERNEL);
	अगर (!vsi->q_vectors)
		जाओ err_vectors;

	vsi->af_xdp_zc_qps = biपंचांगap_zalloc(max_t(पूर्णांक, vsi->alloc_txq, vsi->alloc_rxq), GFP_KERNEL);
	अगर (!vsi->af_xdp_zc_qps)
		जाओ err_zc_qps;

	वापस 0;

err_zc_qps:
	devm_kमुक्त(dev, vsi->q_vectors);
err_vectors:
	devm_kमुक्त(dev, vsi->rxq_map);
err_rxq_map:
	devm_kमुक्त(dev, vsi->txq_map);
err_txq_map:
	devm_kमुक्त(dev, vsi->rx_rings);
err_rings:
	devm_kमुक्त(dev, vsi->tx_rings);
	वापस -ENOMEM;
पूर्ण

/**
 * ice_vsi_set_num_desc - Set number of descriptors क्रम queues on this VSI
 * @vsi: the VSI being configured
 */
अटल व्योम ice_vsi_set_num_desc(काष्ठा ice_vsi *vsi)
अणु
	चयन (vsi->type) अणु
	हाल ICE_VSI_PF:
	हाल ICE_VSI_CTRL:
	हाल ICE_VSI_LB:
		/* a user could change the values of num_[tr]x_desc using
		 * ethtool -G so we should keep those values instead of
		 * overwriting them with the शेषs.
		 */
		अगर (!vsi->num_rx_desc)
			vsi->num_rx_desc = ICE_DFLT_NUM_RX_DESC;
		अगर (!vsi->num_tx_desc)
			vsi->num_tx_desc = ICE_DFLT_NUM_TX_DESC;
		अवरोध;
	शेष:
		dev_dbg(ice_pf_to_dev(vsi->back), "Not setting number of Tx/Rx descriptors for VSI type %d\n",
			vsi->type);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_vsi_set_num_qs - Set number of queues, descriptors and vectors क्रम a VSI
 * @vsi: the VSI being configured
 * @vf_id: ID of the VF being configured
 *
 * Return 0 on success and a negative value on error
 */
अटल व्योम ice_vsi_set_num_qs(काष्ठा ice_vsi *vsi, u16 vf_id)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_vf *vf = शून्य;

	अगर (vsi->type == ICE_VSI_VF)
		vsi->vf_id = vf_id;
	अन्यथा
		vsi->vf_id = ICE_INVAL_VFID;

	चयन (vsi->type) अणु
	हाल ICE_VSI_PF:
		vsi->alloc_txq = min3(pf->num_lan_msix,
				      ice_get_avail_txq_count(pf),
				      (u16)num_online_cpus());
		अगर (vsi->req_txq) अणु
			vsi->alloc_txq = vsi->req_txq;
			vsi->num_txq = vsi->req_txq;
		पूर्ण

		pf->num_lan_tx = vsi->alloc_txq;

		/* only 1 Rx queue unless RSS is enabled */
		अगर (!test_bit(ICE_FLAG_RSS_ENA, pf->flags)) अणु
			vsi->alloc_rxq = 1;
		पूर्ण अन्यथा अणु
			vsi->alloc_rxq = min3(pf->num_lan_msix,
					      ice_get_avail_rxq_count(pf),
					      (u16)num_online_cpus());
			अगर (vsi->req_rxq) अणु
				vsi->alloc_rxq = vsi->req_rxq;
				vsi->num_rxq = vsi->req_rxq;
			पूर्ण
		पूर्ण

		pf->num_lan_rx = vsi->alloc_rxq;

		vsi->num_q_vectors = min_t(पूर्णांक, pf->num_lan_msix,
					   max_t(पूर्णांक, vsi->alloc_rxq,
						 vsi->alloc_txq));
		अवरोध;
	हाल ICE_VSI_VF:
		vf = &pf->vf[vsi->vf_id];
		अगर (vf->num_req_qs)
			vf->num_vf_qs = vf->num_req_qs;
		vsi->alloc_txq = vf->num_vf_qs;
		vsi->alloc_rxq = vf->num_vf_qs;
		/* pf->num_msix_per_vf includes (VF miscellaneous vector +
		 * data queue पूर्णांकerrupts). Since vsi->num_q_vectors is number
		 * of queues vectors, subtract 1 (ICE_NONQ_VECS_VF) from the
		 * original vector count
		 */
		vsi->num_q_vectors = pf->num_msix_per_vf - ICE_NONQ_VECS_VF;
		अवरोध;
	हाल ICE_VSI_CTRL:
		vsi->alloc_txq = 1;
		vsi->alloc_rxq = 1;
		vsi->num_q_vectors = 1;
		अवरोध;
	हाल ICE_VSI_LB:
		vsi->alloc_txq = 1;
		vsi->alloc_rxq = 1;
		अवरोध;
	शेष:
		dev_warn(ice_pf_to_dev(pf), "Unknown VSI type %d\n", vsi->type);
		अवरोध;
	पूर्ण

	ice_vsi_set_num_desc(vsi);
पूर्ण

/**
 * ice_get_मुक्त_slot - get the next non-शून्य location index in array
 * @array: array to search
 * @size: size of the array
 * @curr: last known occupied index to be used as a search hपूर्णांक
 *
 * व्योम * is being used to keep the functionality generic. This lets us use this
 * function on any array of poपूर्णांकers.
 */
अटल पूर्णांक ice_get_मुक्त_slot(व्योम *array, पूर्णांक size, पूर्णांक curr)
अणु
	पूर्णांक **पंचांगp_array = (पूर्णांक **)array;
	पूर्णांक next;

	अगर (curr < (size - 1) && !पंचांगp_array[curr + 1]) अणु
		next = curr + 1;
	पूर्ण अन्यथा अणु
		पूर्णांक i = 0;

		जबतक ((i < size) && (पंचांगp_array[i]))
			i++;
		अगर (i == size)
			next = ICE_NO_VSI;
		अन्यथा
			next = i;
	पूर्ण
	वापस next;
पूर्ण

/**
 * ice_vsi_delete - delete a VSI from the चयन
 * @vsi: poपूर्णांकer to VSI being हटाओd
 */
अटल व्योम ice_vsi_delete(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_vsi_ctx *ctxt;
	क्रमागत ice_status status;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस;

	अगर (vsi->type == ICE_VSI_VF)
		ctxt->vf_num = vsi->vf_id;
	ctxt->vsi_num = vsi->vsi_num;

	स_नकल(&ctxt->info, &vsi->info, माप(ctxt->info));

	status = ice_मुक्त_vsi(&pf->hw, vsi->idx, ctxt, false, शून्य);
	अगर (status)
		dev_err(ice_pf_to_dev(pf), "Failed to delete VSI %i in FW - error: %s\n",
			vsi->vsi_num, ice_stat_str(status));

	kमुक्त(ctxt);
पूर्ण

/**
 * ice_vsi_मुक्त_arrays - De-allocate queue and vector poपूर्णांकer arrays क्रम the VSI
 * @vsi: poपूर्णांकer to VSI being cleared
 */
अटल व्योम ice_vsi_मुक्त_arrays(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);

	अगर (vsi->af_xdp_zc_qps) अणु
		biपंचांगap_मुक्त(vsi->af_xdp_zc_qps);
		vsi->af_xdp_zc_qps = शून्य;
	पूर्ण
	/* मुक्त the ring and vector containers */
	अगर (vsi->q_vectors) अणु
		devm_kमुक्त(dev, vsi->q_vectors);
		vsi->q_vectors = शून्य;
	पूर्ण
	अगर (vsi->tx_rings) अणु
		devm_kमुक्त(dev, vsi->tx_rings);
		vsi->tx_rings = शून्य;
	पूर्ण
	अगर (vsi->rx_rings) अणु
		devm_kमुक्त(dev, vsi->rx_rings);
		vsi->rx_rings = शून्य;
	पूर्ण
	अगर (vsi->txq_map) अणु
		devm_kमुक्त(dev, vsi->txq_map);
		vsi->txq_map = शून्य;
	पूर्ण
	अगर (vsi->rxq_map) अणु
		devm_kमुक्त(dev, vsi->rxq_map);
		vsi->rxq_map = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_vsi_clear - clean up and deallocate the provided VSI
 * @vsi: poपूर्णांकer to VSI being cleared
 *
 * This deallocates the VSI's queue resources, removes it from the PF's
 * VSI array अगर necessary, and deallocates the VSI
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_vsi_clear(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = शून्य;
	काष्ठा device *dev;

	अगर (!vsi)
		वापस 0;

	अगर (!vsi->back)
		वापस -EINVAL;

	pf = vsi->back;
	dev = ice_pf_to_dev(pf);

	अगर (!pf->vsi[vsi->idx] || pf->vsi[vsi->idx] != vsi) अणु
		dev_dbg(dev, "vsi does not exist at pf->vsi[%d]\n", vsi->idx);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&pf->sw_mutex);
	/* updates the PF क्रम this cleared VSI */

	pf->vsi[vsi->idx] = शून्य;
	अगर (vsi->idx < pf->next_vsi && vsi->type != ICE_VSI_CTRL)
		pf->next_vsi = vsi->idx;
	अगर (vsi->idx < pf->next_vsi && vsi->type == ICE_VSI_CTRL &&
	    vsi->vf_id != ICE_INVAL_VFID)
		pf->next_vsi = vsi->idx;

	ice_vsi_मुक्त_arrays(vsi);
	mutex_unlock(&pf->sw_mutex);
	devm_kमुक्त(dev, vsi);

	वापस 0;
पूर्ण

/**
 * ice_msix_clean_ctrl_vsi - MSIX mode पूर्णांकerrupt handler क्रम ctrl VSI
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 */
अटल irqवापस_t ice_msix_clean_ctrl_vsi(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा ice_q_vector *q_vector = (काष्ठा ice_q_vector *)data;

	अगर (!q_vector->tx.ring)
		वापस IRQ_HANDLED;

#घोषणा Fसूची_RX_DESC_CLEAN_BUDGET 64
	ice_clean_rx_irq(q_vector->rx.ring, Fसूची_RX_DESC_CLEAN_BUDGET);
	ice_clean_ctrl_tx_irq(q_vector->tx.ring);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ice_msix_clean_rings - MSIX mode Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 */
अटल irqवापस_t ice_msix_clean_rings(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा ice_q_vector *q_vector = (काष्ठा ice_q_vector *)data;

	अगर (!q_vector->tx.ring && !q_vector->rx.ring)
		वापस IRQ_HANDLED;

	q_vector->total_events++;

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ice_vsi_alloc - Allocates the next available काष्ठा VSI in the PF
 * @pf: board निजी काष्ठाure
 * @vsi_type: type of VSI
 * @vf_id: ID of the VF being configured
 *
 * वापसs a poपूर्णांकer to a VSI on success, शून्य on failure.
 */
अटल काष्ठा ice_vsi *
ice_vsi_alloc(काष्ठा ice_pf *pf, क्रमागत ice_vsi_type vsi_type, u16 vf_id)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_vsi *vsi = शून्य;

	/* Need to protect the allocation of the VSIs at the PF level */
	mutex_lock(&pf->sw_mutex);

	/* If we have alपढ़ोy allocated our maximum number of VSIs,
	 * pf->next_vsi will be ICE_NO_VSI. If not, pf->next_vsi index
	 * is available to be populated
	 */
	अगर (pf->next_vsi == ICE_NO_VSI) अणु
		dev_dbg(dev, "out of VSI slots!\n");
		जाओ unlock_pf;
	पूर्ण

	vsi = devm_kzalloc(dev, माप(*vsi), GFP_KERNEL);
	अगर (!vsi)
		जाओ unlock_pf;

	vsi->type = vsi_type;
	vsi->back = pf;
	set_bit(ICE_VSI_DOWN, vsi->state);

	अगर (vsi_type == ICE_VSI_VF)
		ice_vsi_set_num_qs(vsi, vf_id);
	अन्यथा
		ice_vsi_set_num_qs(vsi, ICE_INVAL_VFID);

	चयन (vsi->type) अणु
	हाल ICE_VSI_PF:
		अगर (ice_vsi_alloc_arrays(vsi))
			जाओ err_rings;

		/* Setup शेष MSIX irq handler क्रम VSI */
		vsi->irq_handler = ice_msix_clean_rings;
		अवरोध;
	हाल ICE_VSI_CTRL:
		अगर (ice_vsi_alloc_arrays(vsi))
			जाओ err_rings;

		/* Setup ctrl VSI MSIX irq handler */
		vsi->irq_handler = ice_msix_clean_ctrl_vsi;
		अवरोध;
	हाल ICE_VSI_VF:
		अगर (ice_vsi_alloc_arrays(vsi))
			जाओ err_rings;
		अवरोध;
	हाल ICE_VSI_LB:
		अगर (ice_vsi_alloc_arrays(vsi))
			जाओ err_rings;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown VSI type %d\n", vsi->type);
		जाओ unlock_pf;
	पूर्ण

	अगर (vsi->type == ICE_VSI_CTRL && vf_id == ICE_INVAL_VFID) अणु
		/* Use the last VSI slot as the index क्रम PF control VSI */
		vsi->idx = pf->num_alloc_vsi - 1;
		pf->ctrl_vsi_idx = vsi->idx;
		pf->vsi[vsi->idx] = vsi;
	पूर्ण अन्यथा अणु
		/* fill slot and make note of the index */
		vsi->idx = pf->next_vsi;
		pf->vsi[pf->next_vsi] = vsi;

		/* prepare pf->next_vsi क्रम next use */
		pf->next_vsi = ice_get_मुक्त_slot(pf->vsi, pf->num_alloc_vsi,
						 pf->next_vsi);
	पूर्ण

	अगर (vsi->type == ICE_VSI_CTRL && vf_id != ICE_INVAL_VFID)
		pf->vf[vf_id].ctrl_vsi_idx = vsi->idx;
	जाओ unlock_pf;

err_rings:
	devm_kमुक्त(dev, vsi);
	vsi = शून्य;
unlock_pf:
	mutex_unlock(&pf->sw_mutex);
	वापस vsi;
पूर्ण

/**
 * ice_alloc_fd_res - Allocate FD resource क्रम a VSI
 * @vsi: poपूर्णांकer to the ice_vsi
 *
 * This allocates the FD resources
 *
 * Returns 0 on success, -EPERM on no-op or -EIO on failure
 */
अटल पूर्णांक ice_alloc_fd_res(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	u32 g_val, b_val;

	/* Flow Director filters are only allocated/asचिन्हित to the PF VSI which
	 * passes the traffic. The CTRL VSI is only used to add/delete filters
	 * so we करोn't allocate resources to it
	 */

	/* FD filters from guaranteed pool per VSI */
	g_val = pf->hw.func_caps.fd_fltr_guar;
	अगर (!g_val)
		वापस -EPERM;

	/* FD filters from best efक्रमt pool */
	b_val = pf->hw.func_caps.fd_fltr_best_efक्रमt;
	अगर (!b_val)
		वापस -EPERM;

	अगर (!(vsi->type == ICE_VSI_PF || vsi->type == ICE_VSI_VF))
		वापस -EPERM;

	अगर (!test_bit(ICE_FLAG_FD_ENA, pf->flags))
		वापस -EPERM;

	vsi->num_gfltr = g_val / pf->num_alloc_vsi;

	/* each VSI माला_लो same "best_effort" quota */
	vsi->num_bfltr = b_val;

	अगर (vsi->type == ICE_VSI_VF) अणु
		vsi->num_gfltr = 0;

		/* each VSI माला_लो same "best_effort" quota */
		vsi->num_bfltr = b_val;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vsi_get_qs - Assign queues from PF to VSI
 * @vsi: the VSI to assign queues to
 *
 * Returns 0 on success and a negative value on error
 */
अटल पूर्णांक ice_vsi_get_qs(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_qs_cfg tx_qs_cfg = अणु
		.qs_mutex = &pf->avail_q_mutex,
		.pf_map = pf->avail_txqs,
		.pf_map_size = pf->max_pf_txqs,
		.q_count = vsi->alloc_txq,
		.scatter_count = ICE_MAX_SCATTER_TXQS,
		.vsi_map = vsi->txq_map,
		.vsi_map_offset = 0,
		.mapping_mode = ICE_VSI_MAP_CONTIG
	पूर्ण;
	काष्ठा ice_qs_cfg rx_qs_cfg = अणु
		.qs_mutex = &pf->avail_q_mutex,
		.pf_map = pf->avail_rxqs,
		.pf_map_size = pf->max_pf_rxqs,
		.q_count = vsi->alloc_rxq,
		.scatter_count = ICE_MAX_SCATTER_RXQS,
		.vsi_map = vsi->rxq_map,
		.vsi_map_offset = 0,
		.mapping_mode = ICE_VSI_MAP_CONTIG
	पूर्ण;
	पूर्णांक ret;

	ret = __ice_vsi_get_qs(&tx_qs_cfg);
	अगर (ret)
		वापस ret;
	vsi->tx_mapping_mode = tx_qs_cfg.mapping_mode;

	ret = __ice_vsi_get_qs(&rx_qs_cfg);
	अगर (ret)
		वापस ret;
	vsi->rx_mapping_mode = rx_qs_cfg.mapping_mode;

	वापस 0;
पूर्ण

/**
 * ice_vsi_put_qs - Release queues from VSI to PF
 * @vsi: the VSI that is going to release queues
 */
अटल व्योम ice_vsi_put_qs(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक i;

	mutex_lock(&pf->avail_q_mutex);

	क्रम (i = 0; i < vsi->alloc_txq; i++) अणु
		clear_bit(vsi->txq_map[i], pf->avail_txqs);
		vsi->txq_map[i] = ICE_INVAL_Q_INDEX;
	पूर्ण

	क्रम (i = 0; i < vsi->alloc_rxq; i++) अणु
		clear_bit(vsi->rxq_map[i], pf->avail_rxqs);
		vsi->rxq_map[i] = ICE_INVAL_Q_INDEX;
	पूर्ण

	mutex_unlock(&pf->avail_q_mutex);
पूर्ण

/**
 * ice_is_safe_mode
 * @pf: poपूर्णांकer to the PF काष्ठा
 *
 * वापसs true अगर driver is in safe mode, false otherwise
 */
bool ice_is_safe_mode(काष्ठा ice_pf *pf)
अणु
	वापस !test_bit(ICE_FLAG_ADV_FEATURES, pf->flags);
पूर्ण

/**
 * ice_vsi_clean_rss_flow_fld - Delete RSS configuration
 * @vsi: the VSI being cleaned up
 *
 * This function deletes RSS input set क्रम all flows that were configured
 * क्रम this VSI
 */
अटल व्योम ice_vsi_clean_rss_flow_fld(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;

	अगर (ice_is_safe_mode(pf))
		वापस;

	status = ice_rem_vsi_rss_cfg(&pf->hw, vsi->idx);
	अगर (status)
		dev_dbg(ice_pf_to_dev(pf), "ice_rem_vsi_rss_cfg failed for vsi = %d, error = %s\n",
			vsi->vsi_num, ice_stat_str(status));
पूर्ण

/**
 * ice_rss_clean - Delete RSS related VSI काष्ठाures and configuration
 * @vsi: the VSI being हटाओd
 */
अटल व्योम ice_rss_clean(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);

	अगर (vsi->rss_hkey_user)
		devm_kमुक्त(dev, vsi->rss_hkey_user);
	अगर (vsi->rss_lut_user)
		devm_kमुक्त(dev, vsi->rss_lut_user);

	ice_vsi_clean_rss_flow_fld(vsi);
	/* हटाओ RSS replay list */
	अगर (!ice_is_safe_mode(pf))
		ice_rem_vsi_rss_list(&pf->hw, vsi->idx);
पूर्ण

/**
 * ice_vsi_set_rss_params - Setup RSS capabilities per VSI type
 * @vsi: the VSI being configured
 */
अटल व्योम ice_vsi_set_rss_params(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_hw_common_caps *cap;
	काष्ठा ice_pf *pf = vsi->back;

	अगर (!test_bit(ICE_FLAG_RSS_ENA, pf->flags)) अणु
		vsi->rss_size = 1;
		वापस;
	पूर्ण

	cap = &pf->hw.func_caps.common_cap;
	चयन (vsi->type) अणु
	हाल ICE_VSI_PF:
		/* PF VSI will inherit RSS instance of PF */
		vsi->rss_table_size = (u16)cap->rss_table_size;
		vsi->rss_size = min_t(u16, num_online_cpus(),
				      BIT(cap->rss_table_entry_width));
		vsi->rss_lut_type = ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_PF;
		अवरोध;
	हाल ICE_VSI_VF:
		/* VF VSI will get a small RSS table.
		 * For VSI_LUT, LUT size should be set to 64 bytes.
		 */
		vsi->rss_table_size = ICE_VSIQF_HLUT_ARRAY_SIZE;
		vsi->rss_size = ICE_MAX_RSS_QS_PER_VF;
		vsi->rss_lut_type = ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_VSI;
		अवरोध;
	हाल ICE_VSI_LB:
		अवरोध;
	शेष:
		dev_dbg(ice_pf_to_dev(pf), "Unsupported VSI type %s\n",
			ice_vsi_type_str(vsi->type));
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_set_dflt_vsi_ctx - Set शेष VSI context beक्रमe adding a VSI
 * @ctxt: the VSI context being set
 *
 * This initializes a शेष VSI context क्रम all sections except the Queues.
 */
अटल व्योम ice_set_dflt_vsi_ctx(काष्ठा ice_vsi_ctx *ctxt)
अणु
	u32 table = 0;

	स_रखो(&ctxt->info, 0, माप(ctxt->info));
	/* VSI's should be allocated from shared pool */
	ctxt->alloc_from_pool = true;
	/* Src pruning enabled by शेष */
	ctxt->info.sw_flags = ICE_AQ_VSI_SW_FLAG_SRC_PRUNE;
	/* Traffic from VSI can be sent to LAN */
	ctxt->info.sw_flags2 = ICE_AQ_VSI_SW_FLAG_LAN_ENA;
	/* By शेष bits 3 and 4 in vlan_flags are 0's which results in legacy
	 * behavior (show VLAN, DEI, and UP) in descriptor. Also, allow all
	 * packets untagged/tagged.
	 */
	ctxt->info.vlan_flags = ((ICE_AQ_VSI_VLAN_MODE_ALL &
				  ICE_AQ_VSI_VLAN_MODE_M) >>
				 ICE_AQ_VSI_VLAN_MODE_S);
	/* Have 1:1 UP mapping क्रम both ingress/egress tables */
	table |= ICE_UP_TABLE_TRANSLATE(0, 0);
	table |= ICE_UP_TABLE_TRANSLATE(1, 1);
	table |= ICE_UP_TABLE_TRANSLATE(2, 2);
	table |= ICE_UP_TABLE_TRANSLATE(3, 3);
	table |= ICE_UP_TABLE_TRANSLATE(4, 4);
	table |= ICE_UP_TABLE_TRANSLATE(5, 5);
	table |= ICE_UP_TABLE_TRANSLATE(6, 6);
	table |= ICE_UP_TABLE_TRANSLATE(7, 7);
	ctxt->info.ingress_table = cpu_to_le32(table);
	ctxt->info.egress_table = cpu_to_le32(table);
	/* Have 1:1 UP mapping क्रम outer to inner UP table */
	ctxt->info.outer_up_table = cpu_to_le32(table);
	/* No Outer tag support outer_tag_flags reमुख्यs to zero */
पूर्ण

/**
 * ice_vsi_setup_q_map - Setup a VSI queue map
 * @vsi: the VSI being configured
 * @ctxt: VSI context काष्ठाure
 */
अटल व्योम ice_vsi_setup_q_map(काष्ठा ice_vsi *vsi, काष्ठा ice_vsi_ctx *ctxt)
अणु
	u16 offset = 0, qmap = 0, tx_count = 0, घात = 0;
	u16 num_txq_per_tc, num_rxq_per_tc;
	u16 qcount_tx = vsi->alloc_txq;
	u16 qcount_rx = vsi->alloc_rxq;
	bool ena_tc0 = false;
	u8 netdev_tc = 0;
	पूर्णांक i;

	/* at least TC0 should be enabled by शेष */
	अगर (vsi->tc_cfg.numtc) अणु
		अगर (!(vsi->tc_cfg.ena_tc & BIT(0)))
			ena_tc0 = true;
	पूर्ण अन्यथा अणु
		ena_tc0 = true;
	पूर्ण

	अगर (ena_tc0) अणु
		vsi->tc_cfg.numtc++;
		vsi->tc_cfg.ena_tc |= 1;
	पूर्ण

	num_rxq_per_tc = min_t(u16, qcount_rx / vsi->tc_cfg.numtc, ICE_MAX_RXQS_PER_TC);
	अगर (!num_rxq_per_tc)
		num_rxq_per_tc = 1;
	num_txq_per_tc = qcount_tx / vsi->tc_cfg.numtc;
	अगर (!num_txq_per_tc)
		num_txq_per_tc = 1;

	/* find the (rounded up) घातer-of-2 of qcount */
	घात = (u16)order_base_2(num_rxq_per_tc);

	/* TC mapping is a function of the number of Rx queues asचिन्हित to the
	 * VSI क्रम each traffic class and the offset of these queues.
	 * The first 10 bits are क्रम queue offset क्रम TC0, next 4 bits क्रम no:of
	 * queues allocated to TC0. No:of queues is a घातer-of-2.
	 *
	 * If TC is not enabled, the queue offset is set to 0, and allocate one
	 * queue, this way, traffic क्रम the given TC will be sent to the शेष
	 * queue.
	 *
	 * Setup number and offset of Rx queues क्रम all TCs क्रम the VSI
	 */
	ice_क्रम_each_traffic_class(i) अणु
		अगर (!(vsi->tc_cfg.ena_tc & BIT(i))) अणु
			/* TC is not enabled */
			vsi->tc_cfg.tc_info[i].qoffset = 0;
			vsi->tc_cfg.tc_info[i].qcount_rx = 1;
			vsi->tc_cfg.tc_info[i].qcount_tx = 1;
			vsi->tc_cfg.tc_info[i].netdev_tc = 0;
			ctxt->info.tc_mapping[i] = 0;
			जारी;
		पूर्ण

		/* TC is enabled */
		vsi->tc_cfg.tc_info[i].qoffset = offset;
		vsi->tc_cfg.tc_info[i].qcount_rx = num_rxq_per_tc;
		vsi->tc_cfg.tc_info[i].qcount_tx = num_txq_per_tc;
		vsi->tc_cfg.tc_info[i].netdev_tc = netdev_tc++;

		qmap = ((offset << ICE_AQ_VSI_TC_Q_OFFSET_S) &
			ICE_AQ_VSI_TC_Q_OFFSET_M) |
			((घात << ICE_AQ_VSI_TC_Q_NUM_S) &
			 ICE_AQ_VSI_TC_Q_NUM_M);
		offset += num_rxq_per_tc;
		tx_count += num_txq_per_tc;
		ctxt->info.tc_mapping[i] = cpu_to_le16(qmap);
	पूर्ण

	/* अगर offset is non-zero, means it is calculated correctly based on
	 * enabled TCs क्रम a given VSI otherwise qcount_rx will always
	 * be correct and non-zero because it is based off - VSI's
	 * allocated Rx queues which is at least 1 (hence qcount_tx will be
	 * at least 1)
	 */
	अगर (offset)
		vsi->num_rxq = offset;
	अन्यथा
		vsi->num_rxq = num_rxq_per_tc;

	vsi->num_txq = tx_count;

	अगर (vsi->type == ICE_VSI_VF && vsi->num_txq != vsi->num_rxq) अणु
		dev_dbg(ice_pf_to_dev(vsi->back), "VF VSI should have same number of Tx and Rx queues. Hence making them equal\n");
		/* since there is a chance that num_rxq could have been changed
		 * in the above क्रम loop, make num_txq equal to num_rxq.
		 */
		vsi->num_txq = vsi->num_rxq;
	पूर्ण

	/* Rx queue mapping */
	ctxt->info.mapping_flags |= cpu_to_le16(ICE_AQ_VSI_Q_MAP_CONTIG);
	/* q_mapping buffer holds the info क्रम the first queue allocated क्रम
	 * this VSI in the PF space and also the number of queues associated
	 * with this VSI.
	 */
	ctxt->info.q_mapping[0] = cpu_to_le16(vsi->rxq_map[0]);
	ctxt->info.q_mapping[1] = cpu_to_le16(vsi->num_rxq);
पूर्ण

/**
 * ice_set_fd_vsi_ctx - Set FD VSI context beक्रमe adding a VSI
 * @ctxt: the VSI context being set
 * @vsi: the VSI being configured
 */
अटल व्योम ice_set_fd_vsi_ctx(काष्ठा ice_vsi_ctx *ctxt, काष्ठा ice_vsi *vsi)
अणु
	u8 dflt_q_group, dflt_q_prio;
	u16 dflt_q, report_q, val;

	अगर (vsi->type != ICE_VSI_PF && vsi->type != ICE_VSI_CTRL &&
	    vsi->type != ICE_VSI_VF)
		वापस;

	val = ICE_AQ_VSI_PROP_FLOW_सूची_VALID;
	ctxt->info.valid_sections |= cpu_to_le16(val);
	dflt_q = 0;
	dflt_q_group = 0;
	report_q = 0;
	dflt_q_prio = 0;

	/* enable flow director filtering/programming */
	val = ICE_AQ_VSI_FD_ENABLE | ICE_AQ_VSI_FD_PROG_ENABLE;
	ctxt->info.fd_options = cpu_to_le16(val);
	/* max of allocated flow director filters */
	ctxt->info.max_fd_fltr_dedicated =
			cpu_to_le16(vsi->num_gfltr);
	/* max of shared flow director filters any VSI may program */
	ctxt->info.max_fd_fltr_shared =
			cpu_to_le16(vsi->num_bfltr);
	/* शेष queue index within the VSI of the शेष FD */
	val = ((dflt_q << ICE_AQ_VSI_FD_DEF_Q_S) &
	       ICE_AQ_VSI_FD_DEF_Q_M);
	/* target queue or queue group to the FD filter */
	val |= ((dflt_q_group << ICE_AQ_VSI_FD_DEF_GRP_S) &
		ICE_AQ_VSI_FD_DEF_GRP_M);
	ctxt->info.fd_def_q = cpu_to_le16(val);
	/* queue index on which FD filter completion is reported */
	val = ((report_q << ICE_AQ_VSI_FD_REPORT_Q_S) &
	       ICE_AQ_VSI_FD_REPORT_Q_M);
	/* priority of the शेष qindex action */
	val |= ((dflt_q_prio << ICE_AQ_VSI_FD_DEF_PRIORITY_S) &
		ICE_AQ_VSI_FD_DEF_PRIORITY_M);
	ctxt->info.fd_report_opt = cpu_to_le16(val);
पूर्ण

/**
 * ice_set_rss_vsi_ctx - Set RSS VSI context beक्रमe adding a VSI
 * @ctxt: the VSI context being set
 * @vsi: the VSI being configured
 */
अटल व्योम ice_set_rss_vsi_ctx(काष्ठा ice_vsi_ctx *ctxt, काष्ठा ice_vsi *vsi)
अणु
	u8 lut_type, hash_type;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;

	pf = vsi->back;
	dev = ice_pf_to_dev(pf);

	चयन (vsi->type) अणु
	हाल ICE_VSI_PF:
		/* PF VSI will inherit RSS instance of PF */
		lut_type = ICE_AQ_VSI_Q_OPT_RSS_LUT_PF;
		hash_type = ICE_AQ_VSI_Q_OPT_RSS_TPLZ;
		अवरोध;
	हाल ICE_VSI_VF:
		/* VF VSI will माला_लो a small RSS table which is a VSI LUT type */
		lut_type = ICE_AQ_VSI_Q_OPT_RSS_LUT_VSI;
		hash_type = ICE_AQ_VSI_Q_OPT_RSS_TPLZ;
		अवरोध;
	शेष:
		dev_dbg(dev, "Unsupported VSI type %s\n",
			ice_vsi_type_str(vsi->type));
		वापस;
	पूर्ण

	ctxt->info.q_opt_rss = ((lut_type << ICE_AQ_VSI_Q_OPT_RSS_LUT_S) &
				ICE_AQ_VSI_Q_OPT_RSS_LUT_M) |
				((hash_type << ICE_AQ_VSI_Q_OPT_RSS_HASH_S) &
				 ICE_AQ_VSI_Q_OPT_RSS_HASH_M);
पूर्ण

/**
 * ice_vsi_init - Create and initialize a VSI
 * @vsi: the VSI being configured
 * @init_vsi: is this call creating a VSI
 *
 * This initializes a VSI context depending on the VSI type to be added and
 * passes it करोwn to the add_vsi aq command to create a new VSI.
 */
अटल पूर्णांक ice_vsi_init(काष्ठा ice_vsi *vsi, bool init_vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_vsi_ctx *ctxt;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	dev = ice_pf_to_dev(pf);
	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस -ENOMEM;

	चयन (vsi->type) अणु
	हाल ICE_VSI_CTRL:
	हाल ICE_VSI_LB:
	हाल ICE_VSI_PF:
		ctxt->flags = ICE_AQ_VSI_TYPE_PF;
		अवरोध;
	हाल ICE_VSI_VF:
		ctxt->flags = ICE_AQ_VSI_TYPE_VF;
		/* VF number here is the असलolute VF number (0-255) */
		ctxt->vf_num = vsi->vf_id + hw->func_caps.vf_base_id;
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ice_set_dflt_vsi_ctx(ctxt);
	अगर (test_bit(ICE_FLAG_FD_ENA, pf->flags))
		ice_set_fd_vsi_ctx(ctxt, vsi);
	/* अगर the चयन is in VEB mode, allow VSI loopback */
	अगर (vsi->vsw->bridge_mode == BRIDGE_MODE_VEB)
		ctxt->info.sw_flags |= ICE_AQ_VSI_SW_FLAG_ALLOW_LB;

	/* Set LUT type and HASH type अगर RSS is enabled */
	अगर (test_bit(ICE_FLAG_RSS_ENA, pf->flags) &&
	    vsi->type != ICE_VSI_CTRL) अणु
		ice_set_rss_vsi_ctx(ctxt, vsi);
		/* अगर updating VSI context, make sure to set valid_section:
		 * to indicate which section of VSI context being updated
		 */
		अगर (!init_vsi)
			ctxt->info.valid_sections |=
				cpu_to_le16(ICE_AQ_VSI_PROP_Q_OPT_VALID);
	पूर्ण

	ctxt->info.sw_id = vsi->port_info->sw_id;
	ice_vsi_setup_q_map(vsi, ctxt);
	अगर (!init_vsi) /* means VSI being updated */
		/* must to indicate which section of VSI context are
		 * being modअगरied
		 */
		ctxt->info.valid_sections |=
			cpu_to_le16(ICE_AQ_VSI_PROP_RXQ_MAP_VALID);

	/* enable/disable MAC and VLAN anti-spoof when spoofchk is on/off
	 * respectively
	 */
	अगर (vsi->type == ICE_VSI_VF) अणु
		ctxt->info.valid_sections |=
			cpu_to_le16(ICE_AQ_VSI_PROP_SECURITY_VALID);
		अगर (pf->vf[vsi->vf_id].spoofchk) अणु
			ctxt->info.sec_flags |=
				ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF |
				(ICE_AQ_VSI_SEC_TX_VLAN_PRUNE_ENA <<
				 ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S);
		पूर्ण अन्यथा अणु
			ctxt->info.sec_flags &=
				~(ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF |
				  (ICE_AQ_VSI_SEC_TX_VLAN_PRUNE_ENA <<
				   ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S));
		पूर्ण
	पूर्ण

	/* Allow control frames out of मुख्य VSI */
	अगर (vsi->type == ICE_VSI_PF) अणु
		ctxt->info.sec_flags |= ICE_AQ_VSI_SEC_FLAG_ALLOW_DEST_OVRD;
		ctxt->info.valid_sections |=
			cpu_to_le16(ICE_AQ_VSI_PROP_SECURITY_VALID);
	पूर्ण

	अगर (init_vsi) अणु
		ret = ice_add_vsi(hw, vsi->idx, ctxt, शून्य);
		अगर (ret) अणु
			dev_err(dev, "Add VSI failed, err %d\n", ret);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ice_update_vsi(hw, vsi->idx, ctxt, शून्य);
		अगर (ret) अणु
			dev_err(dev, "Update VSI failed, err %d\n", ret);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	/* keep context क्रम update VSI operations */
	vsi->info = ctxt->info;

	/* record VSI number वापसed */
	vsi->vsi_num = ctxt->vsi_num;

out:
	kमुक्त(ctxt);
	वापस ret;
पूर्ण

/**
 * ice_मुक्त_res - मुक्त a block of resources
 * @res: poपूर्णांकer to the resource
 * @index: starting index previously वापसed by ice_get_res
 * @id: identअगरier to track owner
 *
 * Returns number of resources मुक्तd
 */
पूर्णांक ice_मुक्त_res(काष्ठा ice_res_tracker *res, u16 index, u16 id)
अणु
	पूर्णांक count = 0;
	पूर्णांक i;

	अगर (!res || index >= res->end)
		वापस -EINVAL;

	id |= ICE_RES_VALID_BIT;
	क्रम (i = index; i < res->end && res->list[i] == id; i++) अणु
		res->list[i] = 0;
		count++;
	पूर्ण

	वापस count;
पूर्ण

/**
 * ice_search_res - Search the tracker क्रम a block of resources
 * @res: poपूर्णांकer to the resource
 * @needed: size of the block needed
 * @id: identअगरier to track owner
 *
 * Returns the base item index of the block, or -ENOMEM क्रम error
 */
अटल पूर्णांक ice_search_res(काष्ठा ice_res_tracker *res, u16 needed, u16 id)
अणु
	u16 start = 0, end = 0;

	अगर (needed > res->end)
		वापस -ENOMEM;

	id |= ICE_RES_VALID_BIT;

	करो अणु
		/* skip alपढ़ोy allocated entries */
		अगर (res->list[end++] & ICE_RES_VALID_BIT) अणु
			start = end;
			अगर ((start + needed) > res->end)
				अवरोध;
		पूर्ण

		अगर (end == (start + needed)) अणु
			पूर्णांक i = start;

			/* there was enough, so assign it to the requestor */
			जबतक (i != end)
				res->list[i++] = id;

			वापस start;
		पूर्ण
	पूर्ण जबतक (end < res->end);

	वापस -ENOMEM;
पूर्ण

/**
 * ice_get_मुक्त_res_count - Get मुक्त count from a resource tracker
 * @res: Resource tracker instance
 */
अटल u16 ice_get_मुक्त_res_count(काष्ठा ice_res_tracker *res)
अणु
	u16 i, count = 0;

	क्रम (i = 0; i < res->end; i++)
		अगर (!(res->list[i] & ICE_RES_VALID_BIT))
			count++;

	वापस count;
पूर्ण

/**
 * ice_get_res - get a block of resources
 * @pf: board निजी काष्ठाure
 * @res: poपूर्णांकer to the resource
 * @needed: size of the block needed
 * @id: identअगरier to track owner
 *
 * Returns the base item index of the block, or negative क्रम error
 */
पूर्णांक
ice_get_res(काष्ठा ice_pf *pf, काष्ठा ice_res_tracker *res, u16 needed, u16 id)
अणु
	अगर (!res || !pf)
		वापस -EINVAL;

	अगर (!needed || needed > res->num_entries || id >= ICE_RES_VALID_BIT) अणु
		dev_err(ice_pf_to_dev(pf), "param err: needed=%d, num_entries = %d id=0x%04x\n",
			needed, res->num_entries, id);
		वापस -EINVAL;
	पूर्ण

	वापस ice_search_res(res, needed, id);
पूर्ण

/**
 * ice_vsi_setup_vector_base - Set up the base vector क्रम the given VSI
 * @vsi: ptr to the VSI
 *
 * This should only be called after ice_vsi_alloc() which allocates the
 * corresponding SW VSI काष्ठाure and initializes num_queue_pairs क्रम the
 * newly allocated VSI.
 *
 * Returns 0 on success or negative on failure
 */
अटल पूर्णांक ice_vsi_setup_vector_base(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	u16 num_q_vectors;
	पूर्णांक base;

	dev = ice_pf_to_dev(pf);
	/* SRIOV करोesn't grab irq_tracker entries क्रम each VSI */
	अगर (vsi->type == ICE_VSI_VF)
		वापस 0;

	अगर (vsi->base_vector) अणु
		dev_dbg(dev, "VSI %d has non-zero base vector %d\n",
			vsi->vsi_num, vsi->base_vector);
		वापस -EEXIST;
	पूर्ण

	num_q_vectors = vsi->num_q_vectors;
	/* reserve slots from OS requested IRQs */
	अगर (vsi->type == ICE_VSI_CTRL && vsi->vf_id != ICE_INVAL_VFID) अणु
		काष्ठा ice_vf *vf;
		पूर्णांक i;

		ice_क्रम_each_vf(pf, i) अणु
			vf = &pf->vf[i];
			अगर (i != vsi->vf_id && vf->ctrl_vsi_idx != ICE_NO_VSI) अणु
				base = pf->vsi[vf->ctrl_vsi_idx]->base_vector;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == pf->num_alloc_vfs)
			base = ice_get_res(pf, pf->irq_tracker, num_q_vectors,
					   ICE_RES_VF_CTRL_VEC_ID);
	पूर्ण अन्यथा अणु
		base = ice_get_res(pf, pf->irq_tracker, num_q_vectors,
				   vsi->idx);
	पूर्ण

	अगर (base < 0) अणु
		dev_err(dev, "%d MSI-X interrupts available. %s %d failed to get %d MSI-X vectors\n",
			ice_get_मुक्त_res_count(pf->irq_tracker),
			ice_vsi_type_str(vsi->type), vsi->idx, num_q_vectors);
		वापस -ENOENT;
	पूर्ण
	vsi->base_vector = (u16)base;
	pf->num_avail_sw_msix -= num_q_vectors;

	वापस 0;
पूर्ण

/**
 * ice_vsi_clear_rings - Deallocates the Tx and Rx rings क्रम VSI
 * @vsi: the VSI having rings deallocated
 */
अटल व्योम ice_vsi_clear_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i;

	/* Aव्योम stale references by clearing map from vector to ring */
	अगर (vsi->q_vectors) अणु
		ice_क्रम_each_q_vector(vsi, i) अणु
			काष्ठा ice_q_vector *q_vector = vsi->q_vectors[i];

			अगर (q_vector) अणु
				q_vector->tx.ring = शून्य;
				q_vector->rx.ring = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vsi->tx_rings) अणु
		क्रम (i = 0; i < vsi->alloc_txq; i++) अणु
			अगर (vsi->tx_rings[i]) अणु
				kमुक्त_rcu(vsi->tx_rings[i], rcu);
				WRITE_ONCE(vsi->tx_rings[i], शून्य);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (vsi->rx_rings) अणु
		क्रम (i = 0; i < vsi->alloc_rxq; i++) अणु
			अगर (vsi->rx_rings[i]) अणु
				kमुक्त_rcu(vsi->rx_rings[i], rcu);
				WRITE_ONCE(vsi->rx_rings[i], शून्य);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_vsi_alloc_rings - Allocates Tx and Rx rings क्रम the VSI
 * @vsi: VSI which is having rings allocated
 */
अटल पूर्णांक ice_vsi_alloc_rings(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	u16 i;

	dev = ice_pf_to_dev(pf);
	/* Allocate Tx rings */
	क्रम (i = 0; i < vsi->alloc_txq; i++) अणु
		काष्ठा ice_ring *ring;

		/* allocate with kzalloc(), मुक्त with kमुक्त_rcu() */
		ring = kzalloc(माप(*ring), GFP_KERNEL);

		अगर (!ring)
			जाओ err_out;

		ring->q_index = i;
		ring->reg_idx = vsi->txq_map[i];
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->dev = dev;
		ring->count = vsi->num_tx_desc;
		WRITE_ONCE(vsi->tx_rings[i], ring);
	पूर्ण

	/* Allocate Rx rings */
	क्रम (i = 0; i < vsi->alloc_rxq; i++) अणु
		काष्ठा ice_ring *ring;

		/* allocate with kzalloc(), मुक्त with kमुक्त_rcu() */
		ring = kzalloc(माप(*ring), GFP_KERNEL);
		अगर (!ring)
			जाओ err_out;

		ring->q_index = i;
		ring->reg_idx = vsi->rxq_map[i];
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->netdev = vsi->netdev;
		ring->dev = dev;
		ring->count = vsi->num_rx_desc;
		WRITE_ONCE(vsi->rx_rings[i], ring);
	पूर्ण

	वापस 0;

err_out:
	ice_vsi_clear_rings(vsi);
	वापस -ENOMEM;
पूर्ण

/**
 * ice_vsi_manage_rss_lut - disable/enable RSS
 * @vsi: the VSI being changed
 * @ena: boolean value indicating अगर this is an enable or disable request
 *
 * In the event of disable request क्रम RSS, this function will zero out RSS
 * LUT, जबतक in the event of enable request क्रम RSS, it will reconfigure RSS
 * LUT.
 */
व्योम ice_vsi_manage_rss_lut(काष्ठा ice_vsi *vsi, bool ena)
अणु
	u8 *lut;

	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस;

	अगर (ena) अणु
		अगर (vsi->rss_lut_user)
			स_नकल(lut, vsi->rss_lut_user, vsi->rss_table_size);
		अन्यथा
			ice_fill_rss_lut(lut, vsi->rss_table_size,
					 vsi->rss_size);
	पूर्ण

	ice_set_rss_lut(vsi, lut, vsi->rss_table_size);
	kमुक्त(lut);
पूर्ण

/**
 * ice_vsi_cfg_rss_lut_key - Configure RSS params क्रम a VSI
 * @vsi: VSI to be configured
 */
अटल पूर्णांक ice_vsi_cfg_rss_lut_key(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	u8 *lut, *key;
	पूर्णांक err;

	dev = ice_pf_to_dev(pf);
	vsi->rss_size = min_t(u16, vsi->rss_size, vsi->num_rxq);

	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;

	अगर (vsi->rss_lut_user)
		स_नकल(lut, vsi->rss_lut_user, vsi->rss_table_size);
	अन्यथा
		ice_fill_rss_lut(lut, vsi->rss_table_size, vsi->rss_size);

	err = ice_set_rss_lut(vsi, lut, vsi->rss_table_size);
	अगर (err) अणु
		dev_err(dev, "set_rss_lut failed, error %d\n", err);
		जाओ ice_vsi_cfg_rss_निकास;
	पूर्ण

	key = kzalloc(ICE_GET_SET_RSS_KEY_EXTEND_KEY_SIZE, GFP_KERNEL);
	अगर (!key) अणु
		err = -ENOMEM;
		जाओ ice_vsi_cfg_rss_निकास;
	पूर्ण

	अगर (vsi->rss_hkey_user)
		स_नकल(key, vsi->rss_hkey_user, ICE_GET_SET_RSS_KEY_EXTEND_KEY_SIZE);
	अन्यथा
		netdev_rss_key_fill((व्योम *)key, ICE_GET_SET_RSS_KEY_EXTEND_KEY_SIZE);

	err = ice_set_rss_key(vsi, key);
	अगर (err)
		dev_err(dev, "set_rss_key failed, error %d\n", err);

	kमुक्त(key);
ice_vsi_cfg_rss_निकास:
	kमुक्त(lut);
	वापस err;
पूर्ण

/**
 * ice_vsi_set_vf_rss_flow_fld - Sets VF VSI RSS input set क्रम dअगरferent flows
 * @vsi: VSI to be configured
 *
 * This function will only be called during the VF VSI setup. Upon successful
 * completion of package करोwnload, this function will configure शेष RSS
 * input sets क्रम VF VSI.
 */
अटल व्योम ice_vsi_set_vf_rss_flow_fld(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);
	अगर (ice_is_safe_mode(pf)) अणु
		dev_dbg(dev, "Advanced RSS disabled. Package download failed, vsi num = %d\n",
			vsi->vsi_num);
		वापस;
	पूर्ण

	status = ice_add_avf_rss_cfg(&pf->hw, vsi->idx, ICE_DEFAULT_RSS_HENA);
	अगर (status)
		dev_dbg(dev, "ice_add_avf_rss_cfg failed for vsi = %d, error = %s\n",
			vsi->vsi_num, ice_stat_str(status));
पूर्ण

/**
 * ice_vsi_set_rss_flow_fld - Sets RSS input set क्रम dअगरferent flows
 * @vsi: VSI to be configured
 *
 * This function will only be called after successful करोwnload package call
 * during initialization of PF. Since the करोwnloaded package will erase the
 * RSS section, this function will configure RSS input sets क्रम dअगरferent
 * flow types. The last profile added has the highest priority, thereक्रमe 2
 * tuple profiles (i.e. IPv4 src/dst) are added beक्रमe 4 tuple profiles
 * (i.e. IPv4 src/dst TCP src/dst port).
 */
अटल व्योम ice_vsi_set_rss_flow_fld(काष्ठा ice_vsi *vsi)
अणु
	u16 vsi_handle = vsi->idx, vsi_num = vsi->vsi_num;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);
	अगर (ice_is_safe_mode(pf)) अणु
		dev_dbg(dev, "Advanced RSS disabled. Package download failed, vsi num = %d\n",
			vsi_num);
		वापस;
	पूर्ण
	/* configure RSS क्रम IPv4 with input set IP src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_FLOW_HASH_IPV4,
				 ICE_FLOW_SEG_HDR_IPV4);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for ipv4 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम IPv6 with input set IPv6 src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_FLOW_HASH_IPV6,
				 ICE_FLOW_SEG_HDR_IPV6);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for ipv6 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम tcp4 with input set IP src/dst, TCP src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_HASH_TCP_IPV4,
				 ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_IPV4);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for tcp4 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम udp4 with input set IP src/dst, UDP src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_HASH_UDP_IPV4,
				 ICE_FLOW_SEG_HDR_UDP | ICE_FLOW_SEG_HDR_IPV4);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for udp4 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम sctp4 with input set IP src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_FLOW_HASH_IPV4,
				 ICE_FLOW_SEG_HDR_SCTP | ICE_FLOW_SEG_HDR_IPV4);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for sctp4 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम tcp6 with input set IPv6 src/dst, TCP src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_HASH_TCP_IPV6,
				 ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_IPV6);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for tcp6 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम udp6 with input set IPv6 src/dst, UDP src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_HASH_UDP_IPV6,
				 ICE_FLOW_SEG_HDR_UDP | ICE_FLOW_SEG_HDR_IPV6);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for udp6 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));

	/* configure RSS क्रम sctp6 with input set IPv6 src/dst */
	status = ice_add_rss_cfg(hw, vsi_handle, ICE_FLOW_HASH_IPV6,
				 ICE_FLOW_SEG_HDR_SCTP | ICE_FLOW_SEG_HDR_IPV6);
	अगर (status)
		dev_dbg(dev, "ice_add_rss_cfg failed for sctp6 flow, vsi = %d, error = %s\n",
			vsi_num, ice_stat_str(status));
पूर्ण

/**
 * ice_pf_state_is_nominal - checks the PF क्रम nominal state
 * @pf: poपूर्णांकer to PF to check
 *
 * Check the PF's state क्रम a collection of bits that would indicate
 * the PF is in a state that would inhibit normal operation क्रम
 * driver functionality.
 *
 * Returns true अगर PF is in a nominal state, false otherwise
 */
bool ice_pf_state_is_nominal(काष्ठा ice_pf *pf)
अणु
	DECLARE_BITMAP(check_bits, ICE_STATE_NBITS) = अणु 0 पूर्ण;

	अगर (!pf)
		वापस false;

	biपंचांगap_set(check_bits, 0, ICE_STATE_NOMINAL_CHECK_BITS);
	अगर (biपंचांगap_पूर्णांकersects(pf->state, check_bits, ICE_STATE_NBITS))
		वापस false;

	वापस true;
पूर्ण

/**
 * ice_update_eth_stats - Update VSI-specअगरic ethernet statistics counters
 * @vsi: the VSI to be updated
 */
व्योम ice_update_eth_stats(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_eth_stats *prev_es, *cur_es;
	काष्ठा ice_hw *hw = &vsi->back->hw;
	u16 vsi_num = vsi->vsi_num;    /* HW असलolute index of a VSI */

	prev_es = &vsi->eth_stats_prev;
	cur_es = &vsi->eth_stats;

	ice_stat_update40(hw, GLV_GORCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_bytes, &cur_es->rx_bytes);

	ice_stat_update40(hw, GLV_UPRCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_unicast, &cur_es->rx_unicast);

	ice_stat_update40(hw, GLV_MPRCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_multicast, &cur_es->rx_multicast);

	ice_stat_update40(hw, GLV_BPRCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_broadcast, &cur_es->rx_broadcast);

	ice_stat_update32(hw, GLV_RDPC(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_discards, &cur_es->rx_discards);

	ice_stat_update40(hw, GLV_GOTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_bytes, &cur_es->tx_bytes);

	ice_stat_update40(hw, GLV_UPTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_unicast, &cur_es->tx_unicast);

	ice_stat_update40(hw, GLV_MPTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_multicast, &cur_es->tx_multicast);

	ice_stat_update40(hw, GLV_BPTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_broadcast, &cur_es->tx_broadcast);

	ice_stat_update32(hw, GLV_TEPC(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_errors, &cur_es->tx_errors);

	vsi->stat_offsets_loaded = true;
पूर्ण

/**
 * ice_vsi_add_vlan - Add VSI membership क्रम given VLAN
 * @vsi: the VSI being configured
 * @vid: VLAN ID to be added
 * @action: filter action to be perक्रमmed on match
 */
पूर्णांक
ice_vsi_add_vlan(काष्ठा ice_vsi *vsi, u16 vid, क्रमागत ice_sw_fwd_act_type action)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	पूर्णांक err = 0;

	dev = ice_pf_to_dev(pf);

	अगर (!ice_fltr_add_vlan(vsi, vid, action)) अणु
		vsi->num_vlan++;
	पूर्ण अन्यथा अणु
		err = -ENODEV;
		dev_err(dev, "Failure Adding VLAN %d on VSI %i\n", vid,
			vsi->vsi_num);
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_vsi_समाप्त_vlan - Remove VSI membership क्रम a given VLAN
 * @vsi: the VSI being configured
 * @vid: VLAN ID to be हटाओd
 *
 * Returns 0 on success and negative on failure
 */
पूर्णांक ice_vsi_समाप्त_vlan(काष्ठा ice_vsi *vsi, u16 vid)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	पूर्णांक err = 0;

	dev = ice_pf_to_dev(pf);

	status = ice_fltr_हटाओ_vlan(vsi, vid, ICE_FWD_TO_VSI);
	अगर (!status) अणु
		vsi->num_vlan--;
	पूर्ण अन्यथा अगर (status == ICE_ERR_DOES_NOT_EXIST) अणु
		dev_dbg(dev, "Failed to remove VLAN %d on VSI %i, it does not exist, status: %s\n",
			vid, vsi->vsi_num, ice_stat_str(status));
	पूर्ण अन्यथा अणु
		dev_err(dev, "Error removing VLAN %d on vsi %i error: %s\n",
			vid, vsi->vsi_num, ice_stat_str(status));
		err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_vsi_cfg_frame_size - setup max frame size and Rx buffer length
 * @vsi: VSI
 */
व्योम ice_vsi_cfg_frame_size(काष्ठा ice_vsi *vsi)
अणु
	अगर (!vsi->netdev || test_bit(ICE_FLAG_LEGACY_RX, vsi->back->flags)) अणु
		vsi->max_frame = ICE_AQ_SET_MAC_FRAME_SIZE_MAX;
		vsi->rx_buf_len = ICE_RXBUF_2048;
#अगर (PAGE_SIZE < 8192)
	पूर्ण अन्यथा अगर (!ICE_2K_TOO_SMALL_WITH_PADDING &&
		   (vsi->netdev->mtu <= ETH_DATA_LEN)) अणु
		vsi->max_frame = ICE_RXBUF_1536 - NET_IP_ALIGN;
		vsi->rx_buf_len = ICE_RXBUF_1536 - NET_IP_ALIGN;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		vsi->max_frame = ICE_AQ_SET_MAC_FRAME_SIZE_MAX;
#अगर (PAGE_SIZE < 8192)
		vsi->rx_buf_len = ICE_RXBUF_3072;
#अन्यथा
		vsi->rx_buf_len = ICE_RXBUF_2048;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/**
 * ice_ग_लिखो_qrxflxp_cntxt - ग_लिखो/configure QRXFLXP_CNTXT रेजिस्टर
 * @hw: HW poपूर्णांकer
 * @pf_q: index of the Rx queue in the PF's queue space
 * @rxdid: flexible descriptor RXDID
 * @prio: priority क्रम the RXDID क्रम this queue
 */
व्योम
ice_ग_लिखो_qrxflxp_cntxt(काष्ठा ice_hw *hw, u16 pf_q, u32 rxdid, u32 prio)
अणु
	पूर्णांक regval = rd32(hw, QRXFLXP_CNTXT(pf_q));

	/* clear any previous values */
	regval &= ~(QRXFLXP_CNTXT_RXDID_IDX_M |
		    QRXFLXP_CNTXT_RXDID_PRIO_M |
		    QRXFLXP_CNTXT_TS_M);

	regval |= (rxdid << QRXFLXP_CNTXT_RXDID_IDX_S) &
		QRXFLXP_CNTXT_RXDID_IDX_M;

	regval |= (prio << QRXFLXP_CNTXT_RXDID_PRIO_S) &
		QRXFLXP_CNTXT_RXDID_PRIO_M;

	wr32(hw, QRXFLXP_CNTXT(pf_q), regval);
पूर्ण

/**
 * ice_vsi_cfg_rxqs - Configure the VSI क्रम Rx
 * @vsi: the VSI being configured
 *
 * Return 0 on success and a negative value on error
 * Configure the Rx VSI क्रम operation.
 */
पूर्णांक ice_vsi_cfg_rxqs(काष्ठा ice_vsi *vsi)
अणु
	u16 i;

	अगर (vsi->type == ICE_VSI_VF)
		जाओ setup_rings;

	ice_vsi_cfg_frame_size(vsi);
setup_rings:
	/* set up inभागidual rings */
	क्रम (i = 0; i < vsi->num_rxq; i++) अणु
		पूर्णांक err;

		err = ice_setup_rx_ctx(vsi->rx_rings[i]);
		अगर (err) अणु
			dev_err(ice_pf_to_dev(vsi->back), "ice_setup_rx_ctx failed for RxQ %d, err %d\n",
				i, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vsi_cfg_txqs - Configure the VSI क्रम Tx
 * @vsi: the VSI being configured
 * @rings: Tx ring array to be configured
 * @count: number of Tx ring array elements
 *
 * Return 0 on success and a negative value on error
 * Configure the Tx VSI क्रम operation.
 */
अटल पूर्णांक
ice_vsi_cfg_txqs(काष्ठा ice_vsi *vsi, काष्ठा ice_ring **rings, u16 count)
अणु
	काष्ठा ice_aqc_add_tx_qgrp *qg_buf;
	u16 q_idx = 0;
	पूर्णांक err = 0;

	qg_buf = kzalloc(काष्ठा_size(qg_buf, txqs, 1), GFP_KERNEL);
	अगर (!qg_buf)
		वापस -ENOMEM;

	qg_buf->num_txqs = 1;

	क्रम (q_idx = 0; q_idx < count; q_idx++) अणु
		err = ice_vsi_cfg_txq(vsi, rings[q_idx], qg_buf);
		अगर (err)
			जाओ err_cfg_txqs;
	पूर्ण

err_cfg_txqs:
	kमुक्त(qg_buf);
	वापस err;
पूर्ण

/**
 * ice_vsi_cfg_lan_txqs - Configure the VSI क्रम Tx
 * @vsi: the VSI being configured
 *
 * Return 0 on success and a negative value on error
 * Configure the Tx VSI क्रम operation.
 */
पूर्णांक ice_vsi_cfg_lan_txqs(काष्ठा ice_vsi *vsi)
अणु
	वापस ice_vsi_cfg_txqs(vsi, vsi->tx_rings, vsi->num_txq);
पूर्ण

/**
 * ice_vsi_cfg_xdp_txqs - Configure Tx queues dedicated क्रम XDP in given VSI
 * @vsi: the VSI being configured
 *
 * Return 0 on success and a negative value on error
 * Configure the Tx queues dedicated क्रम XDP in given VSI क्रम operation.
 */
पूर्णांक ice_vsi_cfg_xdp_txqs(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = ice_vsi_cfg_txqs(vsi, vsi->xdp_rings, vsi->num_xdp_txq);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < vsi->num_xdp_txq; i++)
		vsi->xdp_rings[i]->xsk_pool = ice_xsk_pool(vsi->xdp_rings[i]);

	वापस ret;
पूर्ण

/**
 * ice_पूर्णांकrl_usec_to_reg - convert पूर्णांकerrupt rate limit to रेजिस्टर value
 * @पूर्णांकrl: पूर्णांकerrupt rate limit in usecs
 * @gran: पूर्णांकerrupt rate limit granularity in usecs
 *
 * This function converts a decimal पूर्णांकerrupt rate limit in usecs to the क्रमmat
 * expected by firmware.
 */
अटल u32 ice_पूर्णांकrl_usec_to_reg(u8 पूर्णांकrl, u8 gran)
अणु
	u32 val = पूर्णांकrl / gran;

	अगर (val)
		वापस val | GLINT_RATE_INTRL_ENA_M;
	वापस 0;
पूर्ण

/**
 * ice_ग_लिखो_पूर्णांकrl - ग_लिखो throttle rate limit to पूर्णांकerrupt specअगरic रेजिस्टर
 * @q_vector: poपूर्णांकer to पूर्णांकerrupt specअगरic काष्ठाure
 * @पूर्णांकrl: throttle rate limit in microseconds to ग_लिखो
 */
व्योम ice_ग_लिखो_पूर्णांकrl(काष्ठा ice_q_vector *q_vector, u8 पूर्णांकrl)
अणु
	काष्ठा ice_hw *hw = &q_vector->vsi->back->hw;

	wr32(hw, GLINT_RATE(q_vector->reg_idx),
	     ice_पूर्णांकrl_usec_to_reg(पूर्णांकrl, ICE_INTRL_GRAN_ABOVE_25));
पूर्ण

/**
 * __ice_ग_लिखो_itr - ग_लिखो throttle rate to रेजिस्टर
 * @q_vector: poपूर्णांकer to पूर्णांकerrupt data काष्ठाure
 * @rc: poपूर्णांकer to ring container
 * @itr: throttle rate in microseconds to ग_लिखो
 */
अटल व्योम __ice_ग_लिखो_itr(काष्ठा ice_q_vector *q_vector,
			    काष्ठा ice_ring_container *rc, u16 itr)
अणु
	काष्ठा ice_hw *hw = &q_vector->vsi->back->hw;

	wr32(hw, GLINT_ITR(rc->itr_idx, q_vector->reg_idx),
	     ITR_REG_ALIGN(itr) >> ICE_ITR_GRAN_S);
पूर्ण

/**
 * ice_ग_लिखो_itr - ग_लिखो throttle rate to queue specअगरic रेजिस्टर
 * @rc: poपूर्णांकer to ring container
 * @itr: throttle rate in microseconds to ग_लिखो
 */
व्योम ice_ग_लिखो_itr(काष्ठा ice_ring_container *rc, u16 itr)
अणु
	काष्ठा ice_q_vector *q_vector;

	अगर (!rc->ring)
		वापस;

	q_vector = rc->ring->q_vector;

	__ice_ग_लिखो_itr(q_vector, rc, itr);
पूर्ण

/**
 * ice_vsi_cfg_msix - MSIX mode Interrupt Config in the HW
 * @vsi: the VSI being configured
 *
 * This configures MSIX mode पूर्णांकerrupts क्रम the PF VSI, and should not be used
 * क्रम the VF VSI.
 */
व्योम ice_vsi_cfg_msix(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u16 txq = 0, rxq = 0;
	पूर्णांक i, q;

	क्रम (i = 0; i < vsi->num_q_vectors; i++) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[i];
		u16 reg_idx = q_vector->reg_idx;

		ice_cfg_itr(hw, q_vector);

		/* Both Transmit Queue Interrupt Cause Control रेजिस्टर
		 * and Receive Queue Interrupt Cause control रेजिस्टर
		 * expects MSIX_INDX field to be the vector index
		 * within the function space and not the असलolute
		 * vector index across PF or across device.
		 * For SR-IOV VF VSIs queue vector index always starts
		 * with 1 since first vector index(0) is used क्रम OICR
		 * in VF space. Since VMDq and other PF VSIs are within
		 * the PF function space, use the vector index that is
		 * tracked क्रम this PF.
		 */
		क्रम (q = 0; q < q_vector->num_ring_tx; q++) अणु
			ice_cfg_txq_पूर्णांकerrupt(vsi, txq, reg_idx,
					      q_vector->tx.itr_idx);
			txq++;
		पूर्ण

		क्रम (q = 0; q < q_vector->num_ring_rx; q++) अणु
			ice_cfg_rxq_पूर्णांकerrupt(vsi, rxq, reg_idx,
					      q_vector->rx.itr_idx);
			rxq++;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_vsi_manage_vlan_insertion - Manage VLAN insertion क्रम the VSI क्रम Tx
 * @vsi: the VSI being changed
 */
पूर्णांक ice_vsi_manage_vlan_insertion(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	काष्ठा ice_vsi_ctx *ctxt;
	क्रमागत ice_status status;
	पूर्णांक ret = 0;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस -ENOMEM;

	/* Here we are configuring the VSI to let the driver add VLAN tags by
	 * setting vlan_flags to ICE_AQ_VSI_VLAN_MODE_ALL. The actual VLAN tag
	 * insertion happens in the Tx hot path, in ice_tx_map.
	 */
	ctxt->info.vlan_flags = ICE_AQ_VSI_VLAN_MODE_ALL;

	/* Preserve existing VLAN strip setting */
	ctxt->info.vlan_flags |= (vsi->info.vlan_flags &
				  ICE_AQ_VSI_VLAN_EMOD_M);

	ctxt->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_VLAN_VALID);

	status = ice_update_vsi(hw, vsi->idx, ctxt, शून्य);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "update VSI for VLAN insert failed, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		ret = -EIO;
		जाओ out;
	पूर्ण

	vsi->info.vlan_flags = ctxt->info.vlan_flags;
out:
	kमुक्त(ctxt);
	वापस ret;
पूर्ण

/**
 * ice_vsi_manage_vlan_stripping - Manage VLAN stripping क्रम the VSI क्रम Rx
 * @vsi: the VSI being changed
 * @ena: boolean value indicating अगर this is a enable or disable request
 */
पूर्णांक ice_vsi_manage_vlan_stripping(काष्ठा ice_vsi *vsi, bool ena)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	काष्ठा ice_vsi_ctx *ctxt;
	क्रमागत ice_status status;
	पूर्णांक ret = 0;

	/* करो not allow modअगरying VLAN stripping when a port VLAN is configured
	 * on this VSI
	 */
	अगर (vsi->info.pvid)
		वापस 0;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस -ENOMEM;

	/* Here we are configuring what the VSI should करो with the VLAN tag in
	 * the Rx packet. We can either leave the tag in the packet or put it in
	 * the Rx descriptor.
	 */
	अगर (ena)
		/* Strip VLAN tag from Rx packet and put it in the desc */
		ctxt->info.vlan_flags = ICE_AQ_VSI_VLAN_EMOD_STR_BOTH;
	अन्यथा
		/* Disable stripping. Leave tag in packet */
		ctxt->info.vlan_flags = ICE_AQ_VSI_VLAN_EMOD_NOTHING;

	/* Allow all packets untagged/tagged */
	ctxt->info.vlan_flags |= ICE_AQ_VSI_VLAN_MODE_ALL;

	ctxt->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_VLAN_VALID);

	status = ice_update_vsi(hw, vsi->idx, ctxt, शून्य);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "update VSI for VLAN strip failed, ena = %d err %s aq_err %s\n",
			ena, ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		ret = -EIO;
		जाओ out;
	पूर्ण

	vsi->info.vlan_flags = ctxt->info.vlan_flags;
out:
	kमुक्त(ctxt);
	वापस ret;
पूर्ण

/**
 * ice_vsi_start_all_rx_rings - start/enable all of a VSI's Rx rings
 * @vsi: the VSI whose rings are to be enabled
 *
 * Returns 0 on success and a negative value on error
 */
पूर्णांक ice_vsi_start_all_rx_rings(काष्ठा ice_vsi *vsi)
अणु
	वापस ice_vsi_ctrl_all_rx_rings(vsi, true);
पूर्ण

/**
 * ice_vsi_stop_all_rx_rings - stop/disable all of a VSI's Rx rings
 * @vsi: the VSI whose rings are to be disabled
 *
 * Returns 0 on success and a negative value on error
 */
पूर्णांक ice_vsi_stop_all_rx_rings(काष्ठा ice_vsi *vsi)
अणु
	वापस ice_vsi_ctrl_all_rx_rings(vsi, false);
पूर्ण

/**
 * ice_vsi_stop_tx_rings - Disable Tx rings
 * @vsi: the VSI being configured
 * @rst_src: reset source
 * @rel_vmvf_num: Relative ID of VF/VM
 * @rings: Tx ring array to be stopped
 * @count: number of Tx ring array elements
 */
अटल पूर्णांक
ice_vsi_stop_tx_rings(काष्ठा ice_vsi *vsi, क्रमागत ice_disq_rst_src rst_src,
		      u16 rel_vmvf_num, काष्ठा ice_ring **rings, u16 count)
अणु
	u16 q_idx;

	अगर (vsi->num_txq > ICE_LAN_TXQ_MAX_QDIS)
		वापस -EINVAL;

	क्रम (q_idx = 0; q_idx < count; q_idx++) अणु
		काष्ठा ice_txq_meta txq_meta = अणु पूर्ण;
		पूर्णांक status;

		अगर (!rings || !rings[q_idx])
			वापस -EINVAL;

		ice_fill_txq_meta(vsi, rings[q_idx], &txq_meta);
		status = ice_vsi_stop_tx_ring(vsi, rst_src, rel_vmvf_num,
					      rings[q_idx], &txq_meta);

		अगर (status)
			वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vsi_stop_lan_tx_rings - Disable LAN Tx rings
 * @vsi: the VSI being configured
 * @rst_src: reset source
 * @rel_vmvf_num: Relative ID of VF/VM
 */
पूर्णांक
ice_vsi_stop_lan_tx_rings(काष्ठा ice_vsi *vsi, क्रमागत ice_disq_rst_src rst_src,
			  u16 rel_vmvf_num)
अणु
	वापस ice_vsi_stop_tx_rings(vsi, rst_src, rel_vmvf_num, vsi->tx_rings, vsi->num_txq);
पूर्ण

/**
 * ice_vsi_stop_xdp_tx_rings - Disable XDP Tx rings
 * @vsi: the VSI being configured
 */
पूर्णांक ice_vsi_stop_xdp_tx_rings(काष्ठा ice_vsi *vsi)
अणु
	वापस ice_vsi_stop_tx_rings(vsi, ICE_NO_RESET, 0, vsi->xdp_rings, vsi->num_xdp_txq);
पूर्ण

/**
 * ice_vsi_is_vlan_pruning_ena - check अगर VLAN pruning is enabled or not
 * @vsi: VSI to check whether or not VLAN pruning is enabled.
 *
 * वापसs true अगर Rx VLAN pruning is enabled and false otherwise.
 */
bool ice_vsi_is_vlan_pruning_ena(काष्ठा ice_vsi *vsi)
अणु
	अगर (!vsi)
		वापस false;

	वापस (vsi->info.sw_flags2 & ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA);
पूर्ण

/**
 * ice_cfg_vlan_pruning - enable or disable VLAN pruning on the VSI
 * @vsi: VSI to enable or disable VLAN pruning on
 * @ena: set to true to enable VLAN pruning and false to disable it
 * @vlan_promisc: enable valid security flags अगर not in VLAN promiscuous mode
 *
 * वापसs 0 अगर VSI is updated, negative otherwise
 */
पूर्णांक ice_cfg_vlan_pruning(काष्ठा ice_vsi *vsi, bool ena, bool vlan_promisc)
अणु
	काष्ठा ice_vsi_ctx *ctxt;
	काष्ठा ice_pf *pf;
	पूर्णांक status;

	अगर (!vsi)
		वापस -EINVAL;

	/* Don't enable VLAN pruning अगर the netdev is currently in promiscuous
	 * mode. VLAN pruning will be enabled when the पूर्णांकerface निकासs
	 * promiscuous mode अगर any VLAN filters are active.
	 */
	अगर (vsi->netdev && vsi->netdev->flags & IFF_PROMISC && ena)
		वापस 0;

	pf = vsi->back;
	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस -ENOMEM;

	ctxt->info = vsi->info;

	अगर (ena)
		ctxt->info.sw_flags2 |= ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA;
	अन्यथा
		ctxt->info.sw_flags2 &= ~ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA;

	अगर (!vlan_promisc)
		ctxt->info.valid_sections =
			cpu_to_le16(ICE_AQ_VSI_PROP_SW_VALID);

	status = ice_update_vsi(&pf->hw, vsi->idx, ctxt, शून्य);
	अगर (status) अणु
		netdev_err(vsi->netdev, "%sabling VLAN pruning on VSI handle: %d, VSI HW ID: %d failed, err = %s, aq_err = %s\n",
			   ena ? "En" : "Dis", vsi->idx, vsi->vsi_num,
			   ice_stat_str(status),
			   ice_aq_str(pf->hw.adminq.sq_last_status));
		जाओ err_out;
	पूर्ण

	vsi->info.sw_flags2 = ctxt->info.sw_flags2;

	kमुक्त(ctxt);
	वापस 0;

err_out:
	kमुक्त(ctxt);
	वापस -EIO;
पूर्ण

अटल व्योम ice_vsi_set_tc_cfg(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_dcbx_cfg *cfg = &vsi->port_info->qos_cfg.local_dcbx_cfg;

	vsi->tc_cfg.ena_tc = ice_dcb_get_ena_tc(cfg);
	vsi->tc_cfg.numtc = ice_dcb_get_num_tc(cfg);
पूर्ण

/**
 * ice_vsi_set_q_vectors_reg_idx - set the HW रेजिस्टर index क्रम all q_vectors
 * @vsi: VSI to set the q_vectors रेजिस्टर index on
 */
अटल पूर्णांक
ice_vsi_set_q_vectors_reg_idx(काष्ठा ice_vsi *vsi)
अणु
	u16 i;

	अगर (!vsi || !vsi->q_vectors)
		वापस -EINVAL;

	ice_क्रम_each_q_vector(vsi, i) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[i];

		अगर (!q_vector) अणु
			dev_err(ice_pf_to_dev(vsi->back), "Failed to set reg_idx on q_vector %d VSI %d\n",
				i, vsi->vsi_num);
			जाओ clear_reg_idx;
		पूर्ण

		अगर (vsi->type == ICE_VSI_VF) अणु
			काष्ठा ice_vf *vf = &vsi->back->vf[vsi->vf_id];

			q_vector->reg_idx = ice_calc_vf_reg_idx(vf, q_vector);
		पूर्ण अन्यथा अणु
			q_vector->reg_idx =
				q_vector->v_idx + vsi->base_vector;
		पूर्ण
	पूर्ण

	वापस 0;

clear_reg_idx:
	ice_क्रम_each_q_vector(vsi, i) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[i];

		अगर (q_vector)
			q_vector->reg_idx = 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * ice_cfg_sw_lldp - Config चयन rules क्रम LLDP packet handling
 * @vsi: the VSI being configured
 * @tx: bool to determine Tx or Rx rule
 * @create: bool to determine create or हटाओ Rule
 */
व्योम ice_cfg_sw_lldp(काष्ठा ice_vsi *vsi, bool tx, bool create)
अणु
	क्रमागत ice_status (*eth_fltr)(काष्ठा ice_vsi *v, u16 type, u16 flag,
				    क्रमागत ice_sw_fwd_act_type act);
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);
	eth_fltr = create ? ice_fltr_add_eth : ice_fltr_हटाओ_eth;

	अगर (tx) अणु
		status = eth_fltr(vsi, ETH_P_LLDP, ICE_FLTR_TX,
				  ICE_DROP_PACKET);
	पूर्ण अन्यथा अणु
		अगर (ice_fw_supports_lldp_fltr_ctrl(&pf->hw)) अणु
			status = ice_lldp_fltr_add_हटाओ(&pf->hw, vsi->vsi_num,
							  create);
		पूर्ण अन्यथा अणु
			status = eth_fltr(vsi, ETH_P_LLDP, ICE_FLTR_RX,
					  ICE_FWD_TO_VSI);
		पूर्ण
	पूर्ण

	अगर (status)
		dev_err(dev, "Fail %s %s LLDP rule on VSI %i error: %s\n",
			create ? "adding" : "removing", tx ? "TX" : "RX",
			vsi->vsi_num, ice_stat_str(status));
पूर्ण

/**
 * ice_set_agg_vsi - sets up scheduler aggregator node and move VSI पूर्णांकo it
 * @vsi: poपूर्णांकer to the VSI
 *
 * This function will allocate new scheduler aggregator now अगर needed and will
 * move specअगरied VSI पूर्णांकo it.
 */
अटल व्योम ice_set_agg_vsi(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vsi->back);
	काष्ठा ice_agg_node *agg_node_iter = शून्य;
	u32 agg_id = ICE_INVALID_AGG_NODE_ID;
	काष्ठा ice_agg_node *agg_node = शून्य;
	पूर्णांक node_offset, max_agg_nodes = 0;
	काष्ठा ice_port_info *port_info;
	काष्ठा ice_pf *pf = vsi->back;
	u32 agg_node_id_start = 0;
	क्रमागत ice_status status;

	/* create (as needed) scheduler aggregator node and move VSI पूर्णांकo
	 * corresponding aggregator node
	 * - PF aggregator node to contains VSIs of type _PF and _CTRL
	 * - VF aggregator nodes will contain VF VSI
	 */
	port_info = pf->hw.port_info;
	अगर (!port_info)
		वापस;

	चयन (vsi->type) अणु
	हाल ICE_VSI_CTRL:
	हाल ICE_VSI_LB:
	हाल ICE_VSI_PF:
		max_agg_nodes = ICE_MAX_PF_AGG_NODES;
		agg_node_id_start = ICE_PF_AGG_NODE_ID_START;
		agg_node_iter = &pf->pf_agg_node[0];
		अवरोध;
	हाल ICE_VSI_VF:
		/* user can create 'n' VFs on a given PF, but since max children
		 * per aggregator node can be only 64. Following code handles
		 * aggregator(s) क्रम VF VSIs, either selects a agg_node which
		 * was alपढ़ोy created provided num_vsis < 64, otherwise
		 * select next available node, which will be created
		 */
		max_agg_nodes = ICE_MAX_VF_AGG_NODES;
		agg_node_id_start = ICE_VF_AGG_NODE_ID_START;
		agg_node_iter = &pf->vf_agg_node[0];
		अवरोध;
	शेष:
		/* other VSI type, handle later अगर needed */
		dev_dbg(dev, "unexpected VSI type %s\n",
			ice_vsi_type_str(vsi->type));
		वापस;
	पूर्ण

	/* find the appropriate aggregator node */
	क्रम (node_offset = 0; node_offset < max_agg_nodes; node_offset++) अणु
		/* see अगर we can find space in previously created
		 * node अगर num_vsis < 64, otherwise skip
		 */
		अगर (agg_node_iter->num_vsis &&
		    agg_node_iter->num_vsis == ICE_MAX_VSIS_IN_AGG_NODE) अणु
			agg_node_iter++;
			जारी;
		पूर्ण

		अगर (agg_node_iter->valid &&
		    agg_node_iter->agg_id != ICE_INVALID_AGG_NODE_ID) अणु
			agg_id = agg_node_iter->agg_id;
			agg_node = agg_node_iter;
			अवरोध;
		पूर्ण

		/* find unclaimed agg_id */
		अगर (agg_node_iter->agg_id == ICE_INVALID_AGG_NODE_ID) अणु
			agg_id = node_offset + agg_node_id_start;
			agg_node = agg_node_iter;
			अवरोध;
		पूर्ण
		/* move to next agg_node */
		agg_node_iter++;
	पूर्ण

	अगर (!agg_node)
		वापस;

	/* अगर selected aggregator node was not created, create it */
	अगर (!agg_node->valid) अणु
		status = ice_cfg_agg(port_info, agg_id, ICE_AGG_TYPE_AGG,
				     (u8)vsi->tc_cfg.ena_tc);
		अगर (status) अणु
			dev_err(dev, "unable to create aggregator node with agg_id %u\n",
				agg_id);
			वापस;
		पूर्ण
		/* aggregator node is created, store the neeeded info */
		agg_node->valid = true;
		agg_node->agg_id = agg_id;
	पूर्ण

	/* move VSI to corresponding aggregator node */
	status = ice_move_vsi_to_agg(port_info, agg_id, vsi->idx,
				     (u8)vsi->tc_cfg.ena_tc);
	अगर (status) अणु
		dev_err(dev, "unable to move VSI idx %u into aggregator %u node",
			vsi->idx, agg_id);
		वापस;
	पूर्ण

	/* keep active children count क्रम aggregator node */
	agg_node->num_vsis++;

	/* cache the 'agg_id' in VSI, so that after reset - VSI will be moved
	 * to aggregator node
	 */
	vsi->agg_node = agg_node;
	dev_dbg(dev, "successfully moved VSI idx %u tc_bitmap 0x%x) into aggregator node %d which has num_vsis %u\n",
		vsi->idx, vsi->tc_cfg.ena_tc, vsi->agg_node->agg_id,
		vsi->agg_node->num_vsis);
पूर्ण

/**
 * ice_vsi_setup - Set up a VSI by a given type
 * @pf: board निजी काष्ठाure
 * @pi: poपूर्णांकer to the port_info instance
 * @vsi_type: VSI type
 * @vf_id: defines VF ID to which this VSI connects. This field is meant to be
 *         used only क्रम ICE_VSI_VF VSI type. For other VSI types, should
 *         fill-in ICE_INVAL_VFID as input.
 *
 * This allocates the sw VSI काष्ठाure and its queue resources.
 *
 * Returns poपूर्णांकer to the successfully allocated and configured VSI sw काष्ठा on
 * success, शून्य on failure.
 */
काष्ठा ice_vsi *
ice_vsi_setup(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi,
	      क्रमागत ice_vsi_type vsi_type, u16 vf_id)
अणु
	u16 max_txqs[ICE_MAX_TRAFFIC_CLASS] = अणु 0 पूर्ण;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	क्रमागत ice_status status;
	काष्ठा ice_vsi *vsi;
	पूर्णांक ret, i;

	अगर (vsi_type == ICE_VSI_VF || vsi_type == ICE_VSI_CTRL)
		vsi = ice_vsi_alloc(pf, vsi_type, vf_id);
	अन्यथा
		vsi = ice_vsi_alloc(pf, vsi_type, ICE_INVAL_VFID);

	अगर (!vsi) अणु
		dev_err(dev, "could not allocate VSI\n");
		वापस शून्य;
	पूर्ण

	vsi->port_info = pi;
	vsi->vsw = pf->first_sw;
	अगर (vsi->type == ICE_VSI_PF)
		vsi->ethtype = ETH_P_PAUSE;

	अगर (vsi->type == ICE_VSI_VF || vsi->type == ICE_VSI_CTRL)
		vsi->vf_id = vf_id;

	ice_alloc_fd_res(vsi);

	अगर (ice_vsi_get_qs(vsi)) अणु
		dev_err(dev, "Failed to allocate queues. vsi->idx = %d\n",
			vsi->idx);
		जाओ unroll_vsi_alloc;
	पूर्ण

	/* set RSS capabilities */
	ice_vsi_set_rss_params(vsi);

	/* set TC configuration */
	ice_vsi_set_tc_cfg(vsi);

	/* create the VSI */
	ret = ice_vsi_init(vsi, true);
	अगर (ret)
		जाओ unroll_get_qs;

	चयन (vsi->type) अणु
	हाल ICE_VSI_CTRL:
	हाल ICE_VSI_PF:
		ret = ice_vsi_alloc_q_vectors(vsi);
		अगर (ret)
			जाओ unroll_vsi_init;

		ret = ice_vsi_setup_vector_base(vsi);
		अगर (ret)
			जाओ unroll_alloc_q_vector;

		ret = ice_vsi_set_q_vectors_reg_idx(vsi);
		अगर (ret)
			जाओ unroll_vector_base;

		ret = ice_vsi_alloc_rings(vsi);
		अगर (ret)
			जाओ unroll_vector_base;

		/* Always add VLAN ID 0 चयन rule by शेष. This is needed
		 * in order to allow all untagged and 0 tagged priority traffic
		 * अगर Rx VLAN pruning is enabled. Also there are हालs where we
		 * करोn't get the call to add VLAN 0 via ice_vlan_rx_add_vid()
		 * so this handles those हालs (i.e. adding the PF to a bridge
		 * without the 8021q module loaded).
		 */
		ret = ice_vsi_add_vlan(vsi, 0, ICE_FWD_TO_VSI);
		अगर (ret)
			जाओ unroll_clear_rings;

		ice_vsi_map_rings_to_vectors(vsi);

		/* ICE_VSI_CTRL करोes not need RSS so skip RSS processing */
		अगर (vsi->type != ICE_VSI_CTRL)
			/* Do not निकास अगर configuring RSS had an issue, at
			 * least receive traffic on first queue. Hence no
			 * need to capture वापस value
			 */
			अगर (test_bit(ICE_FLAG_RSS_ENA, pf->flags)) अणु
				ice_vsi_cfg_rss_lut_key(vsi);
				ice_vsi_set_rss_flow_fld(vsi);
			पूर्ण
		ice_init_arfs(vsi);
		अवरोध;
	हाल ICE_VSI_VF:
		/* VF driver will take care of creating netdev क्रम this type and
		 * map queues to vectors through Virtchnl, PF driver only
		 * creates a VSI and corresponding काष्ठाures क्रम bookkeeping
		 * purpose
		 */
		ret = ice_vsi_alloc_q_vectors(vsi);
		अगर (ret)
			जाओ unroll_vsi_init;

		ret = ice_vsi_alloc_rings(vsi);
		अगर (ret)
			जाओ unroll_alloc_q_vector;

		ret = ice_vsi_set_q_vectors_reg_idx(vsi);
		अगर (ret)
			जाओ unroll_vector_base;

		/* Do not निकास अगर configuring RSS had an issue, at least
		 * receive traffic on first queue. Hence no need to capture
		 * वापस value
		 */
		अगर (test_bit(ICE_FLAG_RSS_ENA, pf->flags)) अणु
			ice_vsi_cfg_rss_lut_key(vsi);
			ice_vsi_set_vf_rss_flow_fld(vsi);
		पूर्ण
		अवरोध;
	हाल ICE_VSI_LB:
		ret = ice_vsi_alloc_rings(vsi);
		अगर (ret)
			जाओ unroll_vsi_init;
		अवरोध;
	शेष:
		/* clean up the resources and निकास */
		जाओ unroll_vsi_init;
	पूर्ण

	/* configure VSI nodes based on number of queues and TC's */
	क्रम (i = 0; i < vsi->tc_cfg.numtc; i++)
		max_txqs[i] = vsi->alloc_txq;

	status = ice_cfg_vsi_lan(vsi->port_info, vsi->idx, vsi->tc_cfg.ena_tc,
				 max_txqs);
	अगर (status) अणु
		dev_err(dev, "VSI %d failed lan queue config, error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		जाओ unroll_clear_rings;
	पूर्ण

	/* Add चयन rule to drop all Tx Flow Control Frames, of look up
	 * type ETHERTYPE from VSIs, and restrict malicious VF from sending
	 * out PAUSE or PFC frames. If enabled, FW can still send FC frames.
	 * The rule is added once क्रम PF VSI in order to create appropriate
	 * recipe, since VSI/VSI list is ignored with drop action...
	 * Also add rules to handle LLDP Tx packets.  Tx LLDP packets need to
	 * be dropped so that VFs cannot send LLDP packets to reconfig DCB
	 * settings in the HW.
	 */
	अगर (!ice_is_safe_mode(pf))
		अगर (vsi->type == ICE_VSI_PF) अणु
			ice_fltr_add_eth(vsi, ETH_P_PAUSE, ICE_FLTR_TX,
					 ICE_DROP_PACKET);
			ice_cfg_sw_lldp(vsi, true, true);
		पूर्ण

	अगर (!vsi->agg_node)
		ice_set_agg_vsi(vsi);
	वापस vsi;

unroll_clear_rings:
	ice_vsi_clear_rings(vsi);
unroll_vector_base:
	/* reclaim SW पूर्णांकerrupts back to the common pool */
	ice_मुक्त_res(pf->irq_tracker, vsi->base_vector, vsi->idx);
	pf->num_avail_sw_msix += vsi->num_q_vectors;
unroll_alloc_q_vector:
	ice_vsi_मुक्त_q_vectors(vsi);
unroll_vsi_init:
	ice_vsi_delete(vsi);
unroll_get_qs:
	ice_vsi_put_qs(vsi);
unroll_vsi_alloc:
	अगर (vsi_type == ICE_VSI_VF)
		ice_enable_lag(pf->lag);
	ice_vsi_clear(vsi);

	वापस शून्य;
पूर्ण

/**
 * ice_vsi_release_msix - Clear the queue to Interrupt mapping in HW
 * @vsi: the VSI being cleaned up
 */
अटल व्योम ice_vsi_release_msix(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 txq = 0;
	u32 rxq = 0;
	पूर्णांक i, q;

	क्रम (i = 0; i < vsi->num_q_vectors; i++) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[i];

		ice_ग_लिखो_पूर्णांकrl(q_vector, 0);
		क्रम (q = 0; q < q_vector->num_ring_tx; q++) अणु
			ice_ग_लिखो_itr(&q_vector->tx, 0);
			wr32(hw, QINT_TQCTL(vsi->txq_map[txq]), 0);
			अगर (ice_is_xdp_ena_vsi(vsi)) अणु
				u32 xdp_txq = txq + vsi->num_xdp_txq;

				wr32(hw, QINT_TQCTL(vsi->txq_map[xdp_txq]), 0);
			पूर्ण
			txq++;
		पूर्ण

		क्रम (q = 0; q < q_vector->num_ring_rx; q++) अणु
			ice_ग_लिखो_itr(&q_vector->rx, 0);
			wr32(hw, QINT_RQCTL(vsi->rxq_map[rxq]), 0);
			rxq++;
		पूर्ण
	पूर्ण

	ice_flush(hw);
पूर्ण

/**
 * ice_vsi_मुक्त_irq - Free the IRQ association with the OS
 * @vsi: the VSI being configured
 */
व्योम ice_vsi_मुक्त_irq(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक base = vsi->base_vector;
	पूर्णांक i;

	अगर (!vsi->q_vectors || !vsi->irqs_पढ़ोy)
		वापस;

	ice_vsi_release_msix(vsi);
	अगर (vsi->type == ICE_VSI_VF)
		वापस;

	vsi->irqs_पढ़ोy = false;
	ice_क्रम_each_q_vector(vsi, i) अणु
		u16 vector = i + base;
		पूर्णांक irq_num;

		irq_num = pf->msix_entries[vector].vector;

		/* मुक्त only the irqs that were actually requested */
		अगर (!vsi->q_vectors[i] ||
		    !(vsi->q_vectors[i]->num_ring_tx ||
		      vsi->q_vectors[i]->num_ring_rx))
			जारी;

		/* clear the affinity notअगरier in the IRQ descriptor */
		irq_set_affinity_notअगरier(irq_num, शून्य);

		/* clear the affinity_mask in the IRQ descriptor */
		irq_set_affinity_hपूर्णांक(irq_num, शून्य);
		synchronize_irq(irq_num);
		devm_मुक्त_irq(ice_pf_to_dev(pf), irq_num, vsi->q_vectors[i]);
	पूर्ण
पूर्ण

/**
 * ice_vsi_मुक्त_tx_rings - Free Tx resources क्रम VSI queues
 * @vsi: the VSI having resources मुक्तd
 */
व्योम ice_vsi_मुक्त_tx_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i;

	अगर (!vsi->tx_rings)
		वापस;

	ice_क्रम_each_txq(vsi, i)
		अगर (vsi->tx_rings[i] && vsi->tx_rings[i]->desc)
			ice_मुक्त_tx_ring(vsi->tx_rings[i]);
पूर्ण

/**
 * ice_vsi_मुक्त_rx_rings - Free Rx resources क्रम VSI queues
 * @vsi: the VSI having resources मुक्तd
 */
व्योम ice_vsi_मुक्त_rx_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i;

	अगर (!vsi->rx_rings)
		वापस;

	ice_क्रम_each_rxq(vsi, i)
		अगर (vsi->rx_rings[i] && vsi->rx_rings[i]->desc)
			ice_मुक्त_rx_ring(vsi->rx_rings[i]);
पूर्ण

/**
 * ice_vsi_बंद - Shut करोwn a VSI
 * @vsi: the VSI being shut करोwn
 */
व्योम ice_vsi_बंद(काष्ठा ice_vsi *vsi)
अणु
	अगर (!test_and_set_bit(ICE_VSI_DOWN, vsi->state))
		ice_करोwn(vsi);

	ice_vsi_मुक्त_irq(vsi);
	ice_vsi_मुक्त_tx_rings(vsi);
	ice_vsi_मुक्त_rx_rings(vsi);
पूर्ण

/**
 * ice_ena_vsi - resume a VSI
 * @vsi: the VSI being resume
 * @locked: is the rtnl_lock alपढ़ोy held
 */
पूर्णांक ice_ena_vsi(काष्ठा ice_vsi *vsi, bool locked)
अणु
	पूर्णांक err = 0;

	अगर (!test_bit(ICE_VSI_NEEDS_RESTART, vsi->state))
		वापस 0;

	clear_bit(ICE_VSI_NEEDS_RESTART, vsi->state);

	अगर (vsi->netdev && vsi->type == ICE_VSI_PF) अणु
		अगर (netअगर_running(vsi->netdev)) अणु
			अगर (!locked)
				rtnl_lock();

			err = ice_खोलो_पूर्णांकernal(vsi->netdev);

			अगर (!locked)
				rtnl_unlock();
		पूर्ण
	पूर्ण अन्यथा अगर (vsi->type == ICE_VSI_CTRL) अणु
		err = ice_vsi_खोलो_ctrl(vsi);
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_dis_vsi - छोड़ो a VSI
 * @vsi: the VSI being छोड़ोd
 * @locked: is the rtnl_lock alपढ़ोy held
 */
व्योम ice_dis_vsi(काष्ठा ice_vsi *vsi, bool locked)
अणु
	अगर (test_bit(ICE_VSI_DOWN, vsi->state))
		वापस;

	set_bit(ICE_VSI_NEEDS_RESTART, vsi->state);

	अगर (vsi->type == ICE_VSI_PF && vsi->netdev) अणु
		अगर (netअगर_running(vsi->netdev)) अणु
			अगर (!locked)
				rtnl_lock();

			ice_vsi_बंद(vsi);

			अगर (!locked)
				rtnl_unlock();
		पूर्ण अन्यथा अणु
			ice_vsi_बंद(vsi);
		पूर्ण
	पूर्ण अन्यथा अगर (vsi->type == ICE_VSI_CTRL) अणु
		ice_vsi_बंद(vsi);
	पूर्ण
पूर्ण

/**
 * ice_vsi_dis_irq - Mask off queue पूर्णांकerrupt generation on the VSI
 * @vsi: the VSI being un-configured
 */
व्योम ice_vsi_dis_irq(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक base = vsi->base_vector;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 val;
	पूर्णांक i;

	/* disable पूर्णांकerrupt causation from each queue */
	अगर (vsi->tx_rings) अणु
		ice_क्रम_each_txq(vsi, i) अणु
			अगर (vsi->tx_rings[i]) अणु
				u16 reg;

				reg = vsi->tx_rings[i]->reg_idx;
				val = rd32(hw, QINT_TQCTL(reg));
				val &= ~QINT_TQCTL_CAUSE_ENA_M;
				wr32(hw, QINT_TQCTL(reg), val);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (vsi->rx_rings) अणु
		ice_क्रम_each_rxq(vsi, i) अणु
			अगर (vsi->rx_rings[i]) अणु
				u16 reg;

				reg = vsi->rx_rings[i]->reg_idx;
				val = rd32(hw, QINT_RQCTL(reg));
				val &= ~QINT_RQCTL_CAUSE_ENA_M;
				wr32(hw, QINT_RQCTL(reg), val);
			पूर्ण
		पूर्ण
	पूर्ण

	/* disable each पूर्णांकerrupt */
	ice_क्रम_each_q_vector(vsi, i) अणु
		अगर (!vsi->q_vectors[i])
			जारी;
		wr32(hw, GLINT_DYN_CTL(vsi->q_vectors[i]->reg_idx), 0);
	पूर्ण

	ice_flush(hw);

	/* करोn't call synchronize_irq() for VF's from the host */
	अगर (vsi->type == ICE_VSI_VF)
		वापस;

	ice_क्रम_each_q_vector(vsi, i)
		synchronize_irq(pf->msix_entries[i + base].vector);
पूर्ण

/**
 * ice_napi_del - Remove NAPI handler क्रम the VSI
 * @vsi: VSI क्रम which NAPI handler is to be हटाओd
 */
व्योम ice_napi_del(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक v_idx;

	अगर (!vsi->netdev)
		वापस;

	ice_क्रम_each_q_vector(vsi, v_idx)
		netअगर_napi_del(&vsi->q_vectors[v_idx]->napi);
पूर्ण

/**
 * ice_vsi_release - Delete a VSI and मुक्त its resources
 * @vsi: the VSI being हटाओd
 *
 * Returns 0 on success or < 0 on error
 */
पूर्णांक ice_vsi_release(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf;

	अगर (!vsi->back)
		वापस -ENODEV;
	pf = vsi->back;

	/* करो not unरेजिस्टर जबतक driver is in the reset recovery pending
	 * state. Since reset/rebuild happens through PF service task workqueue,
	 * it's not a good idea to unरेजिस्टर netdev that is associated to the
	 * PF that is running the work queue items currently. This is करोne to
	 * aव्योम check_flush_dependency() warning on this wq
	 */
	अगर (vsi->netdev && !ice_is_reset_in_progress(pf->state) &&
	    (test_bit(ICE_VSI_NETDEV_REGISTERED, vsi->state))) अणु
		unरेजिस्टर_netdev(vsi->netdev);
		clear_bit(ICE_VSI_NETDEV_REGISTERED, vsi->state);
	पूर्ण

	ice_devlink_destroy_port(vsi);

	अगर (test_bit(ICE_FLAG_RSS_ENA, pf->flags))
		ice_rss_clean(vsi);

	/* Disable VSI and मुक्त resources */
	अगर (vsi->type != ICE_VSI_LB)
		ice_vsi_dis_irq(vsi);
	ice_vsi_बंद(vsi);

	/* SR-IOV determines needed MSIX resources all at once instead of per
	 * VSI since when VFs are spawned we know how many VFs there are and how
	 * many पूर्णांकerrupts each VF needs. SR-IOV MSIX resources are also
	 * cleared in the same manner.
	 */
	अगर (vsi->type == ICE_VSI_CTRL && vsi->vf_id != ICE_INVAL_VFID) अणु
		काष्ठा ice_vf *vf;
		पूर्णांक i;

		ice_क्रम_each_vf(pf, i) अणु
			vf = &pf->vf[i];
			अगर (i != vsi->vf_id && vf->ctrl_vsi_idx != ICE_NO_VSI)
				अवरोध;
		पूर्ण
		अगर (i == pf->num_alloc_vfs) अणु
			/* No other VFs left that have control VSI, reclaim SW
			 * पूर्णांकerrupts back to the common pool
			 */
			ice_मुक्त_res(pf->irq_tracker, vsi->base_vector,
				     ICE_RES_VF_CTRL_VEC_ID);
			pf->num_avail_sw_msix += vsi->num_q_vectors;
		पूर्ण
	पूर्ण अन्यथा अगर (vsi->type != ICE_VSI_VF) अणु
		/* reclaim SW पूर्णांकerrupts back to the common pool */
		ice_मुक्त_res(pf->irq_tracker, vsi->base_vector, vsi->idx);
		pf->num_avail_sw_msix += vsi->num_q_vectors;
	पूर्ण

	अगर (!ice_is_safe_mode(pf)) अणु
		अगर (vsi->type == ICE_VSI_PF) अणु
			ice_fltr_हटाओ_eth(vsi, ETH_P_PAUSE, ICE_FLTR_TX,
					    ICE_DROP_PACKET);
			ice_cfg_sw_lldp(vsi, true, false);
			/* The Rx rule will only exist to हटाओ अगर the LLDP FW
			 * engine is currently stopped
			 */
			अगर (!test_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags))
				ice_cfg_sw_lldp(vsi, false, false);
		पूर्ण
	पूर्ण

	ice_fltr_हटाओ_all(vsi);
	ice_rm_vsi_lan_cfg(vsi->port_info, vsi->idx);
	ice_vsi_delete(vsi);
	ice_vsi_मुक्त_q_vectors(vsi);

	अगर (vsi->netdev) अणु
		अगर (test_bit(ICE_VSI_NETDEV_REGISTERED, vsi->state)) अणु
			unरेजिस्टर_netdev(vsi->netdev);
			clear_bit(ICE_VSI_NETDEV_REGISTERED, vsi->state);
		पूर्ण
		अगर (test_bit(ICE_VSI_NETDEV_ALLOCD, vsi->state)) अणु
			मुक्त_netdev(vsi->netdev);
			vsi->netdev = शून्य;
			clear_bit(ICE_VSI_NETDEV_ALLOCD, vsi->state);
		पूर्ण
	पूर्ण

	अगर (vsi->type == ICE_VSI_VF &&
	    vsi->agg_node && vsi->agg_node->valid)
		vsi->agg_node->num_vsis--;
	ice_vsi_clear_rings(vsi);

	ice_vsi_put_qs(vsi);

	/* retain SW VSI data काष्ठाure since it is needed to unरेजिस्टर and
	 * मुक्त VSI netdev when PF is not in reset recovery pending state,\
	 * क्रम ex: during rmmod.
	 */
	अगर (!ice_is_reset_in_progress(pf->state))
		ice_vsi_clear(vsi);

	वापस 0;
पूर्ण

/**
 * ice_vsi_rebuild_get_coalesce - get coalesce from all q_vectors
 * @vsi: VSI connected with q_vectors
 * @coalesce: array of काष्ठा with stored coalesce
 *
 * Returns array size.
 */
अटल पूर्णांक
ice_vsi_rebuild_get_coalesce(काष्ठा ice_vsi *vsi,
			     काष्ठा ice_coalesce_stored *coalesce)
अणु
	पूर्णांक i;

	ice_क्रम_each_q_vector(vsi, i) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[i];

		coalesce[i].itr_tx = q_vector->tx.itr_setting;
		coalesce[i].itr_rx = q_vector->rx.itr_setting;
		coalesce[i].पूर्णांकrl = q_vector->पूर्णांकrl;

		अगर (i < vsi->num_txq)
			coalesce[i].tx_valid = true;
		अगर (i < vsi->num_rxq)
			coalesce[i].rx_valid = true;
	पूर्ण

	वापस vsi->num_q_vectors;
पूर्ण

/**
 * ice_vsi_rebuild_set_coalesce - set coalesce from earlier saved arrays
 * @vsi: VSI connected with q_vectors
 * @coalesce: poपूर्णांकer to array of काष्ठा with stored coalesce
 * @size: size of coalesce array
 *
 * Beक्रमe this function, ice_vsi_rebuild_get_coalesce should be called to save
 * ITR params in arrays. If size is 0 or coalesce wasn't stored set coalesce
 * to शेष value.
 */
अटल व्योम
ice_vsi_rebuild_set_coalesce(काष्ठा ice_vsi *vsi,
			     काष्ठा ice_coalesce_stored *coalesce, पूर्णांक size)
अणु
	काष्ठा ice_ring_container *rc;
	पूर्णांक i;

	अगर ((size && !coalesce) || !vsi)
		वापस;

	/* There are a couple of हालs that have to be handled here:
	 *   1. The हाल where the number of queue vectors stays the same, but
	 *      the number of Tx or Rx rings changes (the first क्रम loop)
	 *   2. The हाल where the number of queue vectors increased (the
	 *      second क्रम loop)
	 */
	क्रम (i = 0; i < size && i < vsi->num_q_vectors; i++) अणु
		/* There are 2 हालs to handle here and they are the same क्रम
		 * both Tx and Rx:
		 *   अगर the entry was valid previously (coalesce[i].[tr]x_valid
		 *   and the loop variable is less than the number of rings
		 *   allocated, then ग_लिखो the previous values
		 *
		 *   अगर the entry was not valid previously, but the number of
		 *   rings is less than are allocated (this means the number of
		 *   rings increased from previously), then ग_लिखो out the
		 *   values in the first element
		 *
		 *   Also, always ग_लिखो the ITR, even अगर in ITR_IS_DYNAMIC
		 *   as there is no harm because the dynamic algorithm
		 *   will just overग_लिखो.
		 */
		अगर (i < vsi->alloc_rxq && coalesce[i].rx_valid) अणु
			rc = &vsi->q_vectors[i]->rx;
			rc->itr_setting = coalesce[i].itr_rx;
			ice_ग_लिखो_itr(rc, rc->itr_setting);
		पूर्ण अन्यथा अगर (i < vsi->alloc_rxq) अणु
			rc = &vsi->q_vectors[i]->rx;
			rc->itr_setting = coalesce[0].itr_rx;
			ice_ग_लिखो_itr(rc, rc->itr_setting);
		पूर्ण

		अगर (i < vsi->alloc_txq && coalesce[i].tx_valid) अणु
			rc = &vsi->q_vectors[i]->tx;
			rc->itr_setting = coalesce[i].itr_tx;
			ice_ग_लिखो_itr(rc, rc->itr_setting);
		पूर्ण अन्यथा अगर (i < vsi->alloc_txq) अणु
			rc = &vsi->q_vectors[i]->tx;
			rc->itr_setting = coalesce[0].itr_tx;
			ice_ग_लिखो_itr(rc, rc->itr_setting);
		पूर्ण

		vsi->q_vectors[i]->पूर्णांकrl = coalesce[i].पूर्णांकrl;
		ice_ग_लिखो_पूर्णांकrl(vsi->q_vectors[i], coalesce[i].पूर्णांकrl);
	पूर्ण

	/* the number of queue vectors increased so ग_लिखो whatever is in
	 * the first element
	 */
	क्रम (; i < vsi->num_q_vectors; i++) अणु
		/* transmit */
		rc = &vsi->q_vectors[i]->tx;
		rc->itr_setting = coalesce[0].itr_tx;
		ice_ग_लिखो_itr(rc, rc->itr_setting);

		/* receive */
		rc = &vsi->q_vectors[i]->rx;
		rc->itr_setting = coalesce[0].itr_rx;
		ice_ग_लिखो_itr(rc, rc->itr_setting);

		vsi->q_vectors[i]->पूर्णांकrl = coalesce[0].पूर्णांकrl;
		ice_ग_लिखो_पूर्णांकrl(vsi->q_vectors[i], coalesce[0].पूर्णांकrl);
	पूर्ण
पूर्ण

/**
 * ice_vsi_rebuild - Rebuild VSI after reset
 * @vsi: VSI to be rebuild
 * @init_vsi: is this an initialization or a reconfigure of the VSI
 *
 * Returns 0 on success and negative value on failure
 */
पूर्णांक ice_vsi_rebuild(काष्ठा ice_vsi *vsi, bool init_vsi)
अणु
	u16 max_txqs[ICE_MAX_TRAFFIC_CLASS] = अणु 0 पूर्ण;
	काष्ठा ice_coalesce_stored *coalesce;
	पूर्णांक prev_num_q_vectors = 0;
	काष्ठा ice_vf *vf = शून्य;
	क्रमागत ice_vsi_type vtype;
	क्रमागत ice_status status;
	काष्ठा ice_pf *pf;
	पूर्णांक ret, i;

	अगर (!vsi)
		वापस -EINVAL;

	pf = vsi->back;
	vtype = vsi->type;
	अगर (vtype == ICE_VSI_VF)
		vf = &pf->vf[vsi->vf_id];

	coalesce = kसुस्मृति(vsi->num_q_vectors,
			   माप(काष्ठा ice_coalesce_stored), GFP_KERNEL);
	अगर (!coalesce)
		वापस -ENOMEM;

	prev_num_q_vectors = ice_vsi_rebuild_get_coalesce(vsi, coalesce);

	ice_rm_vsi_lan_cfg(vsi->port_info, vsi->idx);
	ice_vsi_मुक्त_q_vectors(vsi);

	/* SR-IOV determines needed MSIX resources all at once instead of per
	 * VSI since when VFs are spawned we know how many VFs there are and how
	 * many पूर्णांकerrupts each VF needs. SR-IOV MSIX resources are also
	 * cleared in the same manner.
	 */
	अगर (vtype != ICE_VSI_VF) अणु
		/* reclaim SW पूर्णांकerrupts back to the common pool */
		ice_मुक्त_res(pf->irq_tracker, vsi->base_vector, vsi->idx);
		pf->num_avail_sw_msix += vsi->num_q_vectors;
		vsi->base_vector = 0;
	पूर्ण

	अगर (ice_is_xdp_ena_vsi(vsi))
		/* वापस value check can be skipped here, it always वापसs
		 * 0 अगर reset is in progress
		 */
		ice_destroy_xdp_rings(vsi);
	ice_vsi_put_qs(vsi);
	ice_vsi_clear_rings(vsi);
	ice_vsi_मुक्त_arrays(vsi);
	अगर (vtype == ICE_VSI_VF)
		ice_vsi_set_num_qs(vsi, vf->vf_id);
	अन्यथा
		ice_vsi_set_num_qs(vsi, ICE_INVAL_VFID);

	ret = ice_vsi_alloc_arrays(vsi);
	अगर (ret < 0)
		जाओ err_vsi;

	ice_vsi_get_qs(vsi);

	ice_alloc_fd_res(vsi);
	ice_vsi_set_tc_cfg(vsi);

	/* Initialize VSI काष्ठा elements and create VSI in FW */
	ret = ice_vsi_init(vsi, init_vsi);
	अगर (ret < 0)
		जाओ err_vsi;

	चयन (vtype) अणु
	हाल ICE_VSI_CTRL:
	हाल ICE_VSI_PF:
		ret = ice_vsi_alloc_q_vectors(vsi);
		अगर (ret)
			जाओ err_rings;

		ret = ice_vsi_setup_vector_base(vsi);
		अगर (ret)
			जाओ err_vectors;

		ret = ice_vsi_set_q_vectors_reg_idx(vsi);
		अगर (ret)
			जाओ err_vectors;

		ret = ice_vsi_alloc_rings(vsi);
		अगर (ret)
			जाओ err_vectors;

		ice_vsi_map_rings_to_vectors(vsi);
		अगर (ice_is_xdp_ena_vsi(vsi)) अणु
			vsi->num_xdp_txq = vsi->alloc_rxq;
			ret = ice_prepare_xdp_rings(vsi, vsi->xdp_prog);
			अगर (ret)
				जाओ err_vectors;
		पूर्ण
		/* ICE_VSI_CTRL करोes not need RSS so skip RSS processing */
		अगर (vtype != ICE_VSI_CTRL)
			/* Do not निकास अगर configuring RSS had an issue, at
			 * least receive traffic on first queue. Hence no
			 * need to capture वापस value
			 */
			अगर (test_bit(ICE_FLAG_RSS_ENA, pf->flags))
				ice_vsi_cfg_rss_lut_key(vsi);
		अवरोध;
	हाल ICE_VSI_VF:
		ret = ice_vsi_alloc_q_vectors(vsi);
		अगर (ret)
			जाओ err_rings;

		ret = ice_vsi_set_q_vectors_reg_idx(vsi);
		अगर (ret)
			जाओ err_vectors;

		ret = ice_vsi_alloc_rings(vsi);
		अगर (ret)
			जाओ err_vectors;

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* configure VSI nodes based on number of queues and TC's */
	क्रम (i = 0; i < vsi->tc_cfg.numtc; i++) अणु
		max_txqs[i] = vsi->alloc_txq;

		अगर (ice_is_xdp_ena_vsi(vsi))
			max_txqs[i] += vsi->num_xdp_txq;
	पूर्ण

	status = ice_cfg_vsi_lan(vsi->port_info, vsi->idx, vsi->tc_cfg.ena_tc,
				 max_txqs);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(pf), "VSI %d failed lan queue config, error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		अगर (init_vsi) अणु
			ret = -EIO;
			जाओ err_vectors;
		पूर्ण अन्यथा अणु
			वापस ice_schedule_reset(pf, ICE_RESET_PFR);
		पूर्ण
	पूर्ण
	ice_vsi_rebuild_set_coalesce(vsi, coalesce, prev_num_q_vectors);
	kमुक्त(coalesce);

	वापस 0;

err_vectors:
	ice_vsi_मुक्त_q_vectors(vsi);
err_rings:
	अगर (vsi->netdev) अणु
		vsi->current_netdev_flags = 0;
		unरेजिस्टर_netdev(vsi->netdev);
		मुक्त_netdev(vsi->netdev);
		vsi->netdev = शून्य;
	पूर्ण
err_vsi:
	ice_vsi_clear(vsi);
	set_bit(ICE_RESET_FAILED, pf->state);
	kमुक्त(coalesce);
	वापस ret;
पूर्ण

/**
 * ice_is_reset_in_progress - check क्रम a reset in progress
 * @state: PF state field
 */
bool ice_is_reset_in_progress(अचिन्हित दीर्घ *state)
अणु
	वापस test_bit(ICE_RESET_OICR_RECV, state) ||
	       test_bit(ICE_PFR_REQ, state) ||
	       test_bit(ICE_CORER_REQ, state) ||
	       test_bit(ICE_GLOBR_REQ, state);
पूर्ण

#अगर_घोषित CONFIG_DCB
/**
 * ice_vsi_update_q_map - update our copy of the VSI info with new queue map
 * @vsi: VSI being configured
 * @ctx: the context buffer वापसed from AQ VSI update command
 */
अटल व्योम ice_vsi_update_q_map(काष्ठा ice_vsi *vsi, काष्ठा ice_vsi_ctx *ctx)
अणु
	vsi->info.mapping_flags = ctx->info.mapping_flags;
	स_नकल(&vsi->info.q_mapping, &ctx->info.q_mapping,
	       माप(vsi->info.q_mapping));
	स_नकल(&vsi->info.tc_mapping, ctx->info.tc_mapping,
	       माप(vsi->info.tc_mapping));
पूर्ण

/**
 * ice_vsi_cfg_tc - Configure VSI Tx Sched क्रम given TC map
 * @vsi: VSI to be configured
 * @ena_tc: TC biपंचांगap
 *
 * VSI queues expected to be quiesced beक्रमe calling this function
 */
पूर्णांक ice_vsi_cfg_tc(काष्ठा ice_vsi *vsi, u8 ena_tc)
अणु
	u16 max_txqs[ICE_MAX_TRAFFIC_CLASS] = अणु 0 पूर्ण;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_vsi_ctx *ctx;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	पूर्णांक i, ret = 0;
	u8 num_tc = 0;

	dev = ice_pf_to_dev(pf);

	ice_क्रम_each_traffic_class(i) अणु
		/* build biपंचांगap of enabled TCs */
		अगर (ena_tc & BIT(i))
			num_tc++;
		/* populate max_txqs per TC */
		max_txqs[i] = vsi->alloc_txq;
	पूर्ण

	vsi->tc_cfg.ena_tc = ena_tc;
	vsi->tc_cfg.numtc = num_tc;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->vf_num = 0;
	ctx->info = vsi->info;

	ice_vsi_setup_q_map(vsi, ctx);

	/* must to indicate which section of VSI context are being modअगरied */
	ctx->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_RXQ_MAP_VALID);
	status = ice_update_vsi(&pf->hw, vsi->idx, ctx, शून्य);
	अगर (status) अणु
		dev_info(dev, "Failed VSI Update\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	status = ice_cfg_vsi_lan(vsi->port_info, vsi->idx, vsi->tc_cfg.ena_tc,
				 max_txqs);

	अगर (status) अणु
		dev_err(dev, "VSI %d failed TC config, error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		ret = -EIO;
		जाओ out;
	पूर्ण
	ice_vsi_update_q_map(vsi, ctx);
	vsi->info.valid_sections = 0;

	ice_vsi_cfg_netdev_tc(vsi, ena_tc);
out:
	kमुक्त(ctx);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_DCB */

/**
 * ice_update_ring_stats - Update ring statistics
 * @ring: ring to update
 * @pkts: number of processed packets
 * @bytes: number of processed bytes
 *
 * This function assumes that caller has acquired a u64_stats_sync lock.
 */
अटल व्योम ice_update_ring_stats(काष्ठा ice_ring *ring, u64 pkts, u64 bytes)
अणु
	ring->stats.bytes += bytes;
	ring->stats.pkts += pkts;
पूर्ण

/**
 * ice_update_tx_ring_stats - Update Tx ring specअगरic counters
 * @tx_ring: ring to update
 * @pkts: number of processed packets
 * @bytes: number of processed bytes
 */
व्योम ice_update_tx_ring_stats(काष्ठा ice_ring *tx_ring, u64 pkts, u64 bytes)
अणु
	u64_stats_update_begin(&tx_ring->syncp);
	ice_update_ring_stats(tx_ring, pkts, bytes);
	u64_stats_update_end(&tx_ring->syncp);
पूर्ण

/**
 * ice_update_rx_ring_stats - Update Rx ring specअगरic counters
 * @rx_ring: ring to update
 * @pkts: number of processed packets
 * @bytes: number of processed bytes
 */
व्योम ice_update_rx_ring_stats(काष्ठा ice_ring *rx_ring, u64 pkts, u64 bytes)
अणु
	u64_stats_update_begin(&rx_ring->syncp);
	ice_update_ring_stats(rx_ring, pkts, bytes);
	u64_stats_update_end(&rx_ring->syncp);
पूर्ण

/**
 * ice_status_to_त्रुटि_सं - convert from क्रमागत ice_status to Linux त्रुटि_सं
 * @err: ice_status value to convert
 */
पूर्णांक ice_status_to_त्रुटि_सं(क्रमागत ice_status err)
अणु
	चयन (err) अणु
	हाल ICE_SUCCESS:
		वापस 0;
	हाल ICE_ERR_DOES_NOT_EXIST:
		वापस -ENOENT;
	हाल ICE_ERR_OUT_OF_RANGE:
		वापस -ENOTTY;
	हाल ICE_ERR_PARAM:
		वापस -EINVAL;
	हाल ICE_ERR_NO_MEMORY:
		वापस -ENOMEM;
	हाल ICE_ERR_MAX_LIMIT:
		वापस -EAGAIN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * ice_is_dflt_vsi_in_use - check अगर the शेष क्रमwarding VSI is being used
 * @sw: चयन to check अगर its शेष क्रमwarding VSI is मुक्त
 *
 * Return true अगर the शेष क्रमwarding VSI is alपढ़ोy being used, अन्यथा वापसs
 * false संकेतling that it's available to use.
 */
bool ice_is_dflt_vsi_in_use(काष्ठा ice_sw *sw)
अणु
	वापस (sw->dflt_vsi && sw->dflt_vsi_ena);
पूर्ण

/**
 * ice_is_vsi_dflt_vsi - check अगर the VSI passed in is the शेष VSI
 * @sw: चयन क्रम the शेष क्रमwarding VSI to compare against
 * @vsi: VSI to compare against शेष क्रमwarding VSI
 *
 * If this VSI passed in is the शेष क्रमwarding VSI then वापस true, अन्यथा
 * वापस false
 */
bool ice_is_vsi_dflt_vsi(काष्ठा ice_sw *sw, काष्ठा ice_vsi *vsi)
अणु
	वापस (sw->dflt_vsi == vsi && sw->dflt_vsi_ena);
पूर्ण

/**
 * ice_set_dflt_vsi - set the शेष क्रमwarding VSI
 * @sw: चयन used to assign the शेष क्रमwarding VSI
 * @vsi: VSI getting set as the शेष क्रमwarding VSI on the चयन
 *
 * If the VSI passed in is alपढ़ोy the शेष VSI and it's enabled just वापस
 * success.
 *
 * If there is alपढ़ोy a शेष VSI on the चयन and it's enabled then वापस
 * -EEXIST since there can only be one शेष VSI per चयन.
 *
 *  Otherwise try to set the VSI passed in as the चयन's शेष VSI and
 *  वापस the result.
 */
पूर्णांक ice_set_dflt_vsi(काष्ठा ice_sw *sw, काष्ठा ice_vsi *vsi)
अणु
	क्रमागत ice_status status;
	काष्ठा device *dev;

	अगर (!sw || !vsi)
		वापस -EINVAL;

	dev = ice_pf_to_dev(vsi->back);

	/* the VSI passed in is alपढ़ोy the शेष VSI */
	अगर (ice_is_vsi_dflt_vsi(sw, vsi)) अणु
		dev_dbg(dev, "VSI %d passed in is already the default forwarding VSI, nothing to do\n",
			vsi->vsi_num);
		वापस 0;
	पूर्ण

	/* another VSI is alपढ़ोy the शेष VSI क्रम this चयन */
	अगर (ice_is_dflt_vsi_in_use(sw)) अणु
		dev_err(dev, "Default forwarding VSI %d already in use, disable it and try again\n",
			sw->dflt_vsi->vsi_num);
		वापस -EEXIST;
	पूर्ण

	status = ice_cfg_dflt_vsi(&vsi->back->hw, vsi->idx, true, ICE_FLTR_RX);
	अगर (status) अणु
		dev_err(dev, "Failed to set VSI %d as the default forwarding VSI, error %s\n",
			vsi->vsi_num, ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	sw->dflt_vsi = vsi;
	sw->dflt_vsi_ena = true;

	वापस 0;
पूर्ण

/**
 * ice_clear_dflt_vsi - clear the शेष क्रमwarding VSI
 * @sw: चयन used to clear the शेष VSI
 *
 * If the चयन has no शेष VSI or it's not enabled then वापस error.
 *
 * Otherwise try to clear the शेष VSI and वापस the result.
 */
पूर्णांक ice_clear_dflt_vsi(काष्ठा ice_sw *sw)
अणु
	काष्ठा ice_vsi *dflt_vsi;
	क्रमागत ice_status status;
	काष्ठा device *dev;

	अगर (!sw)
		वापस -EINVAL;

	dev = ice_pf_to_dev(sw->pf);

	dflt_vsi = sw->dflt_vsi;

	/* there is no शेष VSI configured */
	अगर (!ice_is_dflt_vsi_in_use(sw))
		वापस -ENODEV;

	status = ice_cfg_dflt_vsi(&dflt_vsi->back->hw, dflt_vsi->idx, false,
				  ICE_FLTR_RX);
	अगर (status) अणु
		dev_err(dev, "Failed to clear the default forwarding VSI %d, error %s\n",
			dflt_vsi->vsi_num, ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	sw->dflt_vsi = शून्य;
	sw->dflt_vsi_ena = false;

	वापस 0;
पूर्ण

/**
 * ice_set_link - turn on/off physical link
 * @vsi: VSI to modअगरy physical link on
 * @ena: turn on/off physical link
 */
पूर्णांक ice_set_link(काष्ठा ice_vsi *vsi, bool ena)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vsi->back);
	काष्ठा ice_port_info *pi = vsi->port_info;
	काष्ठा ice_hw *hw = pi->hw;
	क्रमागत ice_status status;

	अगर (vsi->type != ICE_VSI_PF)
		वापस -EINVAL;

	status = ice_aq_set_link_restart_an(pi, ena, शून्य);

	/* अगर link is owned by manageability, FW will वापस ICE_AQ_RC_EMODE.
	 * this is not a fatal error, so prपूर्णांक a warning message and वापस
	 * a success code. Return an error अगर FW वापसs an error code other
	 * than ICE_AQ_RC_EMODE
	 */
	अगर (status == ICE_ERR_AQ_ERROR) अणु
		अगर (hw->adminq.sq_last_status == ICE_AQ_RC_EMODE)
			dev_warn(dev, "can't set link to %s, err %s aq_err %s. not fatal, continuing\n",
				 (ena ? "ON" : "OFF"), ice_stat_str(status),
				 ice_aq_str(hw->adminq.sq_last_status));
	पूर्ण अन्यथा अगर (status) अणु
		dev_err(dev, "can't set link to %s, err %s aq_err %s\n",
			(ena ? "ON" : "OFF"), ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
