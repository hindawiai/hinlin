<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
  */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#समावेश "bna.h"
#समावेश "bfi.h"

/* IB */
अटल व्योम
bna_ib_coalescing_समयo_set(काष्ठा bna_ib *ib, u8 coalescing_समयo)
अणु
	ib->coalescing_समयo = coalescing_समयo;
	ib->करोor_bell.करोorbell_ack = BNA_DOORBELL_IB_INT_ACK(
				(u32)ib->coalescing_समयo, 0);
पूर्ण

/* RXF */

#घोषणा bna_rxf_vlan_cfg_soft_reset(rxf)				\
करो अणु									\
	(rxf)->vlan_pending_biपंचांगask = (u8)BFI_VLAN_BMASK_ALL;		\
	(rxf)->vlan_strip_pending = true;				\
पूर्ण जबतक (0)

#घोषणा bna_rxf_rss_cfg_soft_reset(rxf)					\
करो अणु									\
	अगर ((rxf)->rss_status == BNA_STATUS_T_ENABLED)			\
		(rxf)->rss_pending = (BNA_RSS_F_RIT_PENDING |		\
				BNA_RSS_F_CFG_PENDING |			\
				BNA_RSS_F_STATUS_PENDING);		\
पूर्ण जबतक (0)

अटल पूर्णांक bna_rxf_cfg_apply(काष्ठा bna_rxf *rxf);
अटल व्योम bna_rxf_cfg_reset(काष्ठा bna_rxf *rxf);
अटल पूर्णांक bna_rxf_ucast_cfg_apply(काष्ठा bna_rxf *rxf);
अटल पूर्णांक bna_rxf_promisc_cfg_apply(काष्ठा bna_rxf *rxf);
अटल पूर्णांक bna_rxf_allmulti_cfg_apply(काष्ठा bna_rxf *rxf);
अटल पूर्णांक bna_rxf_vlan_strip_cfg_apply(काष्ठा bna_rxf *rxf);
अटल पूर्णांक bna_rxf_ucast_cfg_reset(काष्ठा bna_rxf *rxf,
					क्रमागत bna_cleanup_type cleanup);
अटल पूर्णांक bna_rxf_promisc_cfg_reset(काष्ठा bna_rxf *rxf,
					क्रमागत bna_cleanup_type cleanup);
अटल पूर्णांक bna_rxf_allmulti_cfg_reset(काष्ठा bna_rxf *rxf,
					क्रमागत bna_cleanup_type cleanup);

bfa_fsm_state_decl(bna_rxf, stopped, काष्ठा bna_rxf,
			क्रमागत bna_rxf_event);
bfa_fsm_state_decl(bna_rxf, cfg_रुको, काष्ठा bna_rxf,
			क्रमागत bna_rxf_event);
bfa_fsm_state_decl(bna_rxf, started, काष्ठा bna_rxf,
			क्रमागत bna_rxf_event);
bfa_fsm_state_decl(bna_rxf, last_resp_रुको, काष्ठा bna_rxf,
			क्रमागत bna_rxf_event);

अटल व्योम
bna_rxf_sm_stopped_entry(काष्ठा bna_rxf *rxf)
अणु
	call_rxf_stop_cbfn(rxf);
पूर्ण

अटल व्योम
bna_rxf_sm_stopped(काष्ठा bna_rxf *rxf, क्रमागत bna_rxf_event event)
अणु
	चयन (event) अणु
	हाल RXF_E_START:
		bfa_fsm_set_state(rxf, bna_rxf_sm_cfg_रुको);
		अवरोध;

	हाल RXF_E_STOP:
		call_rxf_stop_cbfn(rxf);
		अवरोध;

	हाल RXF_E_FAIL:
		/* No-op */
		अवरोध;

	हाल RXF_E_CONFIG:
		call_rxf_cam_fltr_cbfn(rxf);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_rxf_sm_cfg_रुको_entry(काष्ठा bna_rxf *rxf)
अणु
	अगर (!bna_rxf_cfg_apply(rxf)) अणु
		/* No more pending config updates */
		bfa_fsm_set_state(rxf, bna_rxf_sm_started);
	पूर्ण
पूर्ण

अटल व्योम
bna_rxf_sm_cfg_रुको(काष्ठा bna_rxf *rxf, क्रमागत bna_rxf_event event)
अणु
	चयन (event) अणु
	हाल RXF_E_STOP:
		bfa_fsm_set_state(rxf, bna_rxf_sm_last_resp_रुको);
		अवरोध;

	हाल RXF_E_FAIL:
		bna_rxf_cfg_reset(rxf);
		call_rxf_start_cbfn(rxf);
		call_rxf_cam_fltr_cbfn(rxf);
		bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
		अवरोध;

	हाल RXF_E_CONFIG:
		/* No-op */
		अवरोध;

	हाल RXF_E_FW_RESP:
		अगर (!bna_rxf_cfg_apply(rxf)) अणु
			/* No more pending config updates */
			bfa_fsm_set_state(rxf, bna_rxf_sm_started);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_rxf_sm_started_entry(काष्ठा bna_rxf *rxf)
अणु
	call_rxf_start_cbfn(rxf);
	call_rxf_cam_fltr_cbfn(rxf);
पूर्ण

अटल व्योम
bna_rxf_sm_started(काष्ठा bna_rxf *rxf, क्रमागत bna_rxf_event event)
अणु
	चयन (event) अणु
	हाल RXF_E_STOP:
	हाल RXF_E_FAIL:
		bna_rxf_cfg_reset(rxf);
		bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
		अवरोध;

	हाल RXF_E_CONFIG:
		bfa_fsm_set_state(rxf, bna_rxf_sm_cfg_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_rxf_sm_last_resp_रुको_entry(काष्ठा bna_rxf *rxf)
अणु
पूर्ण

अटल व्योम
bna_rxf_sm_last_resp_रुको(काष्ठा bna_rxf *rxf, क्रमागत bna_rxf_event event)
अणु
	चयन (event) अणु
	हाल RXF_E_FAIL:
	हाल RXF_E_FW_RESP:
		bna_rxf_cfg_reset(rxf);
		bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_ucast_req(काष्ठा bna_rxf *rxf, काष्ठा bna_mac *mac,
		क्रमागत bfi_enet_h2i_msgs req_type)
अणु
	काष्ठा bfi_enet_ucast_req *req = &rxf->bfi_enet_cmd.ucast_req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET, req_type, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
	bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_ucast_req)));
	ether_addr_copy(req->mac_addr, mac->addr);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_ucast_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_mcast_add_req(काष्ठा bna_rxf *rxf, काष्ठा bna_mac *mac)
अणु
	काष्ठा bfi_enet_mcast_add_req *req =
		&rxf->bfi_enet_cmd.mcast_add_req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET, BFI_ENET_H2I_MAC_MCAST_ADD_REQ,
		0, rxf->rx->rid);
	req->mh.num_entries = htons(
	bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_mcast_add_req)));
	ether_addr_copy(req->mac_addr, mac->addr);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_mcast_add_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_mcast_del_req(काष्ठा bna_rxf *rxf, u16 handle)
अणु
	काष्ठा bfi_enet_mcast_del_req *req =
		&rxf->bfi_enet_cmd.mcast_del_req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET, BFI_ENET_H2I_MAC_MCAST_DEL_REQ,
		0, rxf->rx->rid);
	req->mh.num_entries = htons(
	bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_mcast_del_req)));
	req->handle = htons(handle);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_mcast_del_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_mcast_filter_req(काष्ठा bna_rxf *rxf, क्रमागत bna_status status)
अणु
	काष्ठा bfi_enet_enable_req *req = &rxf->bfi_enet_cmd.req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_MAC_MCAST_FILTER_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_enable_req)));
	req->enable = status;
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_enable_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_rx_promisc_req(काष्ठा bna_rxf *rxf, क्रमागत bna_status status)
अणु
	काष्ठा bfi_enet_enable_req *req = &rxf->bfi_enet_cmd.req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RX_PROMISCUOUS_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_enable_req)));
	req->enable = status;
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_enable_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_rx_vlan_filter_set(काष्ठा bna_rxf *rxf, u8 block_idx)
अणु
	काष्ठा bfi_enet_rx_vlan_req *req = &rxf->bfi_enet_cmd.vlan_req;
	पूर्णांक i;
	पूर्णांक j;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RX_VLAN_SET_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_rx_vlan_req)));
	req->block_idx = block_idx;
	क्रम (i = 0; i < (BFI_ENET_VLAN_BLOCK_SIZE / 32); i++) अणु
		j = (block_idx * (BFI_ENET_VLAN_BLOCK_SIZE / 32)) + i;
		अगर (rxf->vlan_filter_status == BNA_STATUS_T_ENABLED)
			req->bit_mask[i] =
				htonl(rxf->vlan_filter_table[j]);
		अन्यथा
			req->bit_mask[i] = 0xFFFFFFFF;
	पूर्ण
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_rx_vlan_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_vlan_strip_enable(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bfi_enet_enable_req *req = &rxf->bfi_enet_cmd.req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RX_VLAN_STRIP_ENABLE_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_enable_req)));
	req->enable = rxf->vlan_strip_status;
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_enable_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_rit_cfg(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bfi_enet_rit_req *req = &rxf->bfi_enet_cmd.rit_req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RIT_CFG_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_rit_req)));
	req->size = htons(rxf->rit_size);
	स_नकल(&req->table[0], rxf->rit, rxf->rit_size);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_rit_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_rss_cfg(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bfi_enet_rss_cfg_req *req = &rxf->bfi_enet_cmd.rss_req;
	पूर्णांक i;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RSS_CFG_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_rss_cfg_req)));
	req->cfg.type = rxf->rss_cfg.hash_type;
	req->cfg.mask = rxf->rss_cfg.hash_mask;
	क्रम (i = 0; i < BFI_ENET_RSS_KEY_LEN; i++)
		req->cfg.key[i] =
			htonl(rxf->rss_cfg.toeplitz_hash_key[i]);
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_rss_cfg_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_rss_enable(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bfi_enet_enable_req *req = &rxf->bfi_enet_cmd.req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RSS_ENABLE_REQ, 0, rxf->rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_enable_req)));
	req->enable = rxf->rss_status;
	bfa_msgq_cmd_set(&rxf->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_enable_req), &req->mh);
	bfa_msgq_cmd_post(&rxf->rx->bna->msgq, &rxf->msgq_cmd);
पूर्ण

/* This function माला_लो the multicast MAC that has alपढ़ोy been added to CAM */
अटल काष्ठा bna_mac *
bna_rxf_mcmac_get(काष्ठा bna_rxf *rxf, स्थिर u8 *mac_addr)
अणु
	काष्ठा bna_mac *mac;

	list_क्रम_each_entry(mac, &rxf->mcast_active_q, qe)
		अगर (ether_addr_equal(mac->addr, mac_addr))
			वापस mac;

	list_क्रम_each_entry(mac, &rxf->mcast_pending_del_q, qe)
		अगर (ether_addr_equal(mac->addr, mac_addr))
			वापस mac;

	वापस शून्य;
पूर्ण

अटल काष्ठा bna_mcam_handle *
bna_rxf_mchandle_get(काष्ठा bna_rxf *rxf, पूर्णांक handle)
अणु
	काष्ठा bna_mcam_handle *mchandle;

	list_क्रम_each_entry(mchandle, &rxf->mcast_handle_q, qe)
		अगर (mchandle->handle == handle)
			वापस mchandle;

	वापस शून्य;
पूर्ण

अटल व्योम
bna_rxf_mchandle_attach(काष्ठा bna_rxf *rxf, u8 *mac_addr, पूर्णांक handle)
अणु
	काष्ठा bna_mac *mcmac;
	काष्ठा bna_mcam_handle *mchandle;

	mcmac = bna_rxf_mcmac_get(rxf, mac_addr);
	mchandle = bna_rxf_mchandle_get(rxf, handle);
	अगर (mchandle == शून्य) अणु
		mchandle = bna_mcam_mod_handle_get(&rxf->rx->bna->mcam_mod);
		mchandle->handle = handle;
		mchandle->refcnt = 0;
		list_add_tail(&mchandle->qe, &rxf->mcast_handle_q);
	पूर्ण
	mchandle->refcnt++;
	mcmac->handle = mchandle;
पूर्ण

अटल पूर्णांक
bna_rxf_mcast_del(काष्ठा bna_rxf *rxf, काष्ठा bna_mac *mac,
		क्रमागत bna_cleanup_type cleanup)
अणु
	काष्ठा bna_mcam_handle *mchandle;
	पूर्णांक ret = 0;

	mchandle = mac->handle;
	अगर (mchandle == शून्य)
		वापस ret;

	mchandle->refcnt--;
	अगर (mchandle->refcnt == 0) अणु
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_mcast_del_req(rxf, mchandle->handle);
			ret = 1;
		पूर्ण
		list_del(&mchandle->qe);
		bna_mcam_mod_handle_put(&rxf->rx->bna->mcam_mod, mchandle);
	पूर्ण
	mac->handle = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक
bna_rxf_mcast_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bna_mac *mac = शून्य;
	पूर्णांक ret;

	/* First delete multicast entries to मुख्यtain the count */
	जबतक (!list_empty(&rxf->mcast_pending_del_q)) अणु
		mac = list_first_entry(&rxf->mcast_pending_del_q,
				       काष्ठा bna_mac, qe);
		ret = bna_rxf_mcast_del(rxf, mac, BNA_HARD_CLEANUP);
		list_move_tail(&mac->qe, bna_mcam_mod_del_q(rxf->rx->bna));
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Add multicast entries */
	अगर (!list_empty(&rxf->mcast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->mcast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &rxf->mcast_active_q);
		bna_bfi_mcast_add_req(rxf, mac);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_vlan_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	u8 vlan_pending_biपंचांगask;
	पूर्णांक block_idx = 0;

	अगर (rxf->vlan_pending_biपंचांगask) अणु
		vlan_pending_biपंचांगask = rxf->vlan_pending_biपंचांगask;
		जबतक (!(vlan_pending_biपंचांगask & 0x1)) अणु
			block_idx++;
			vlan_pending_biपंचांगask >>= 1;
		पूर्ण
		rxf->vlan_pending_biपंचांगask &= ~BIT(block_idx);
		bna_bfi_rx_vlan_filter_set(rxf, block_idx);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_mcast_cfg_reset(काष्ठा bna_rxf *rxf, क्रमागत bna_cleanup_type cleanup)
अणु
	काष्ठा bna_mac *mac;
	पूर्णांक ret;

	/* Throw away delete pending mcast entries */
	जबतक (!list_empty(&rxf->mcast_pending_del_q)) अणु
		mac = list_first_entry(&rxf->mcast_pending_del_q,
				       काष्ठा bna_mac, qe);
		ret = bna_rxf_mcast_del(rxf, mac, cleanup);
		list_move_tail(&mac->qe, bna_mcam_mod_del_q(rxf->rx->bna));
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Move active mcast entries to pending_add_q */
	जबतक (!list_empty(&rxf->mcast_active_q)) अणु
		mac = list_first_entry(&rxf->mcast_active_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &rxf->mcast_pending_add_q);
		अगर (bna_rxf_mcast_del(rxf, mac, cleanup))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_rss_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	अगर (rxf->rss_pending) अणु
		अगर (rxf->rss_pending & BNA_RSS_F_RIT_PENDING) अणु
			rxf->rss_pending &= ~BNA_RSS_F_RIT_PENDING;
			bna_bfi_rit_cfg(rxf);
			वापस 1;
		पूर्ण

		अगर (rxf->rss_pending & BNA_RSS_F_CFG_PENDING) अणु
			rxf->rss_pending &= ~BNA_RSS_F_CFG_PENDING;
			bna_bfi_rss_cfg(rxf);
			वापस 1;
		पूर्ण

		अगर (rxf->rss_pending & BNA_RSS_F_STATUS_PENDING) अणु
			rxf->rss_pending &= ~BNA_RSS_F_STATUS_PENDING;
			bna_bfi_rss_enable(rxf);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	अगर (bna_rxf_ucast_cfg_apply(rxf))
		वापस 1;

	अगर (bna_rxf_mcast_cfg_apply(rxf))
		वापस 1;

	अगर (bna_rxf_promisc_cfg_apply(rxf))
		वापस 1;

	अगर (bna_rxf_allmulti_cfg_apply(rxf))
		वापस 1;

	अगर (bna_rxf_vlan_cfg_apply(rxf))
		वापस 1;

	अगर (bna_rxf_vlan_strip_cfg_apply(rxf))
		वापस 1;

	अगर (bna_rxf_rss_cfg_apply(rxf))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम
bna_rxf_cfg_reset(काष्ठा bna_rxf *rxf)
अणु
	bna_rxf_ucast_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_mcast_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_promisc_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_allmulti_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_vlan_cfg_soft_reset(rxf);
	bna_rxf_rss_cfg_soft_reset(rxf);
पूर्ण

अटल व्योम
bna_rit_init(काष्ठा bna_rxf *rxf, पूर्णांक rit_size)
अणु
	काष्ठा bna_rx *rx = rxf->rx;
	काष्ठा bna_rxp *rxp;
	पूर्णांक offset = 0;

	rxf->rit_size = rit_size;
	list_क्रम_each_entry(rxp, &rx->rxp_q, qe) अणु
		rxf->rit[offset] = rxp->cq.ccb->id;
		offset++;
	पूर्ण
पूर्ण

व्योम
bna_bfi_rxf_cfg_rsp(काष्ठा bna_rxf *rxf, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	bfa_fsm_send_event(rxf, RXF_E_FW_RESP);
पूर्ण

व्योम
bna_bfi_rxf_ucast_set_rsp(काष्ठा bna_rxf *rxf,
			काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_rsp *rsp =
		container_of(msghdr, काष्ठा bfi_enet_rsp, mh);

	अगर (rsp->error) अणु
		/* Clear ucast from cache */
		rxf->ucast_active_set = 0;
	पूर्ण

	bfa_fsm_send_event(rxf, RXF_E_FW_RESP);
पूर्ण

व्योम
bna_bfi_rxf_mcast_add_rsp(काष्ठा bna_rxf *rxf,
			काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_mcast_add_req *req =
		&rxf->bfi_enet_cmd.mcast_add_req;
	काष्ठा bfi_enet_mcast_add_rsp *rsp =
		container_of(msghdr, काष्ठा bfi_enet_mcast_add_rsp, mh);

	bna_rxf_mchandle_attach(rxf, (u8 *)&req->mac_addr,
		ntohs(rsp->handle));
	bfa_fsm_send_event(rxf, RXF_E_FW_RESP);
पूर्ण

अटल व्योम
bna_rxf_init(काष्ठा bna_rxf *rxf,
		काष्ठा bna_rx *rx,
		काष्ठा bna_rx_config *q_config,
		काष्ठा bna_res_info *res_info)
अणु
	rxf->rx = rx;

	INIT_LIST_HEAD(&rxf->ucast_pending_add_q);
	INIT_LIST_HEAD(&rxf->ucast_pending_del_q);
	rxf->ucast_pending_set = 0;
	rxf->ucast_active_set = 0;
	INIT_LIST_HEAD(&rxf->ucast_active_q);
	rxf->ucast_pending_mac = शून्य;

	INIT_LIST_HEAD(&rxf->mcast_pending_add_q);
	INIT_LIST_HEAD(&rxf->mcast_pending_del_q);
	INIT_LIST_HEAD(&rxf->mcast_active_q);
	INIT_LIST_HEAD(&rxf->mcast_handle_q);

	rxf->rit = (u8 *)
		res_info[BNA_RX_RES_MEM_T_RIT].res_u.mem_info.mdl[0].kva;
	bna_rit_init(rxf, q_config->num_paths);

	rxf->rss_status = q_config->rss_status;
	अगर (rxf->rss_status == BNA_STATUS_T_ENABLED) अणु
		rxf->rss_cfg = q_config->rss_config;
		rxf->rss_pending |= BNA_RSS_F_CFG_PENDING;
		rxf->rss_pending |= BNA_RSS_F_RIT_PENDING;
		rxf->rss_pending |= BNA_RSS_F_STATUS_PENDING;
	पूर्ण

	rxf->vlan_filter_status = BNA_STATUS_T_DISABLED;
	स_रखो(rxf->vlan_filter_table, 0,
			(माप(u32) * (BFI_ENET_VLAN_ID_MAX / 32)));
	rxf->vlan_filter_table[0] |= 1; /* क्रम pure priority tagged frames */
	rxf->vlan_pending_biपंचांगask = (u8)BFI_VLAN_BMASK_ALL;

	rxf->vlan_strip_status = q_config->vlan_strip_status;

	bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
पूर्ण

अटल व्योम
bna_rxf_uninit(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bna_mac *mac;

	rxf->ucast_pending_set = 0;
	rxf->ucast_active_set = 0;

	जबतक (!list_empty(&rxf->ucast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->ucast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, bna_ucam_mod_मुक्त_q(rxf->rx->bna));
	पूर्ण

	अगर (rxf->ucast_pending_mac) अणु
		list_add_tail(&rxf->ucast_pending_mac->qe,
			      bna_ucam_mod_मुक्त_q(rxf->rx->bna));
		rxf->ucast_pending_mac = शून्य;
	पूर्ण

	जबतक (!list_empty(&rxf->mcast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->mcast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, bna_mcam_mod_मुक्त_q(rxf->rx->bna));
	पूर्ण

	rxf->rxmode_pending = 0;
	rxf->rxmode_pending_biपंचांगask = 0;
	अगर (rxf->rx->bna->promisc_rid == rxf->rx->rid)
		rxf->rx->bna->promisc_rid = BFI_INVALID_RID;
	अगर (rxf->rx->bna->शेष_mode_rid == rxf->rx->rid)
		rxf->rx->bna->शेष_mode_rid = BFI_INVALID_RID;

	rxf->rss_pending = 0;
	rxf->vlan_strip_pending = false;

	rxf->rx = शून्य;
पूर्ण

अटल व्योम
bna_rx_cb_rxf_started(काष्ठा bna_rx *rx)
अणु
	bfa_fsm_send_event(rx, RX_E_RXF_STARTED);
पूर्ण

अटल व्योम
bna_rxf_start(काष्ठा bna_rxf *rxf)
अणु
	rxf->start_cbfn = bna_rx_cb_rxf_started;
	rxf->start_cbarg = rxf->rx;
	bfa_fsm_send_event(rxf, RXF_E_START);
पूर्ण

अटल व्योम
bna_rx_cb_rxf_stopped(काष्ठा bna_rx *rx)
अणु
	bfa_fsm_send_event(rx, RX_E_RXF_STOPPED);
पूर्ण

अटल व्योम
bna_rxf_stop(काष्ठा bna_rxf *rxf)
अणु
	rxf->stop_cbfn = bna_rx_cb_rxf_stopped;
	rxf->stop_cbarg = rxf->rx;
	bfa_fsm_send_event(rxf, RXF_E_STOP);
पूर्ण

अटल व्योम
bna_rxf_fail(काष्ठा bna_rxf *rxf)
अणु
	bfa_fsm_send_event(rxf, RXF_E_FAIL);
पूर्ण

क्रमागत bna_cb_status
bna_rx_ucast_set(काष्ठा bna_rx *rx, स्थिर u8 *ucmac)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;

	अगर (rxf->ucast_pending_mac == शून्य) अणु
		rxf->ucast_pending_mac =
			bna_cam_mod_mac_get(bna_ucam_mod_मुक्त_q(rxf->rx->bna));
		अगर (rxf->ucast_pending_mac == शून्य)
			वापस BNA_CB_UCAST_CAM_FULL;
	पूर्ण

	ether_addr_copy(rxf->ucast_pending_mac->addr, ucmac);
	rxf->ucast_pending_set = 1;
	rxf->cam_fltr_cbfn = शून्य;
	rxf->cam_fltr_cbarg = rx->bna->bnad;

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	वापस BNA_CB_SUCCESS;
पूर्ण

क्रमागत bna_cb_status
bna_rx_mcast_add(काष्ठा bna_rx *rx, स्थिर u8 *addr,
		 व्योम (*cbfn)(काष्ठा bnad *, काष्ठा bna_rx *))
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;
	काष्ठा bna_mac *mac;

	/* Check अगर alपढ़ोy added or pending addition */
	अगर (bna_mac_find(&rxf->mcast_active_q, addr) ||
		bna_mac_find(&rxf->mcast_pending_add_q, addr)) अणु
		अगर (cbfn)
			cbfn(rx->bna->bnad, rx);
		वापस BNA_CB_SUCCESS;
	पूर्ण

	mac = bna_cam_mod_mac_get(bna_mcam_mod_मुक्त_q(rxf->rx->bna));
	अगर (mac == शून्य)
		वापस BNA_CB_MCAST_LIST_FULL;
	ether_addr_copy(mac->addr, addr);
	list_add_tail(&mac->qe, &rxf->mcast_pending_add_q);

	rxf->cam_fltr_cbfn = cbfn;
	rxf->cam_fltr_cbarg = rx->bna->bnad;

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	वापस BNA_CB_SUCCESS;
पूर्ण

क्रमागत bna_cb_status
bna_rx_ucast_listset(काष्ठा bna_rx *rx, पूर्णांक count, स्थिर u8 *uclist)
अणु
	काष्ठा bna_ucam_mod *ucam_mod = &rx->bna->ucam_mod;
	काष्ठा bna_rxf *rxf = &rx->rxf;
	काष्ठा list_head list_head;
	स्थिर u8 *mcaddr;
	काष्ठा bna_mac *mac, *del_mac;
	पूर्णांक i;

	/* Purge the pending_add_q */
	जबतक (!list_empty(&rxf->ucast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->ucast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &ucam_mod->मुक्त_q);
	पूर्ण

	/* Schedule active_q entries क्रम deletion */
	जबतक (!list_empty(&rxf->ucast_active_q)) अणु
		mac = list_first_entry(&rxf->ucast_active_q,
				       काष्ठा bna_mac, qe);
		del_mac = bna_cam_mod_mac_get(&ucam_mod->del_q);
		ether_addr_copy(del_mac->addr, mac->addr);
		del_mac->handle = mac->handle;
		list_add_tail(&del_mac->qe, &rxf->ucast_pending_del_q);
		list_move_tail(&mac->qe, &ucam_mod->मुक्त_q);
	पूर्ण

	/* Allocate nodes */
	INIT_LIST_HEAD(&list_head);
	क्रम (i = 0, mcaddr = uclist; i < count; i++) अणु
		mac = bna_cam_mod_mac_get(&ucam_mod->मुक्त_q);
		अगर (mac == शून्य)
			जाओ err_वापस;
		ether_addr_copy(mac->addr, mcaddr);
		list_add_tail(&mac->qe, &list_head);
		mcaddr += ETH_ALEN;
	पूर्ण

	/* Add the new entries */
	जबतक (!list_empty(&list_head)) अणु
		mac = list_first_entry(&list_head, काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &rxf->ucast_pending_add_q);
	पूर्ण

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	वापस BNA_CB_SUCCESS;

err_वापस:
	जबतक (!list_empty(&list_head)) अणु
		mac = list_first_entry(&list_head, काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &ucam_mod->मुक्त_q);
	पूर्ण

	वापस BNA_CB_UCAST_CAM_FULL;
पूर्ण

क्रमागत bna_cb_status
bna_rx_mcast_listset(काष्ठा bna_rx *rx, पूर्णांक count, स्थिर u8 *mclist)
अणु
	काष्ठा bna_mcam_mod *mcam_mod = &rx->bna->mcam_mod;
	काष्ठा bna_rxf *rxf = &rx->rxf;
	काष्ठा list_head list_head;
	स्थिर u8 *mcaddr;
	काष्ठा bna_mac *mac, *del_mac;
	पूर्णांक i;

	/* Purge the pending_add_q */
	जबतक (!list_empty(&rxf->mcast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->mcast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &mcam_mod->मुक्त_q);
	पूर्ण

	/* Schedule active_q entries क्रम deletion */
	जबतक (!list_empty(&rxf->mcast_active_q)) अणु
		mac = list_first_entry(&rxf->mcast_active_q,
				       काष्ठा bna_mac, qe);
		del_mac = bna_cam_mod_mac_get(&mcam_mod->del_q);
		ether_addr_copy(del_mac->addr, mac->addr);
		del_mac->handle = mac->handle;
		list_add_tail(&del_mac->qe, &rxf->mcast_pending_del_q);
		mac->handle = शून्य;
		list_move_tail(&mac->qe, &mcam_mod->मुक्त_q);
	पूर्ण

	/* Allocate nodes */
	INIT_LIST_HEAD(&list_head);
	क्रम (i = 0, mcaddr = mclist; i < count; i++) अणु
		mac = bna_cam_mod_mac_get(&mcam_mod->मुक्त_q);
		अगर (mac == शून्य)
			जाओ err_वापस;
		ether_addr_copy(mac->addr, mcaddr);
		list_add_tail(&mac->qe, &list_head);

		mcaddr += ETH_ALEN;
	पूर्ण

	/* Add the new entries */
	जबतक (!list_empty(&list_head)) अणु
		mac = list_first_entry(&list_head, काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &rxf->mcast_pending_add_q);
	पूर्ण

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	वापस BNA_CB_SUCCESS;

err_वापस:
	जबतक (!list_empty(&list_head)) अणु
		mac = list_first_entry(&list_head, काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &mcam_mod->मुक्त_q);
	पूर्ण

	वापस BNA_CB_MCAST_LIST_FULL;
पूर्ण

व्योम
bna_rx_mcast_delall(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;
	काष्ठा bna_mac *mac, *del_mac;
	पूर्णांक need_hw_config = 0;

	/* Purge all entries from pending_add_q */
	जबतक (!list_empty(&rxf->mcast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->mcast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, bna_mcam_mod_मुक्त_q(rxf->rx->bna));
	पूर्ण

	/* Schedule all entries in active_q क्रम deletion */
	जबतक (!list_empty(&rxf->mcast_active_q)) अणु
		mac = list_first_entry(&rxf->mcast_active_q,
				       काष्ठा bna_mac, qe);
		list_del(&mac->qe);
		del_mac = bna_cam_mod_mac_get(bna_mcam_mod_del_q(rxf->rx->bna));
		स_नकल(del_mac, mac, माप(*del_mac));
		list_add_tail(&del_mac->qe, &rxf->mcast_pending_del_q);
		mac->handle = शून्य;
		list_add_tail(&mac->qe, bna_mcam_mod_मुक्त_q(rxf->rx->bna));
		need_hw_config = 1;
	पूर्ण

	अगर (need_hw_config)
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
पूर्ण

व्योम
bna_rx_vlan_add(काष्ठा bna_rx *rx, पूर्णांक vlan_id)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;
	पूर्णांक index = (vlan_id >> BFI_VLAN_WORD_SHIFT);
	पूर्णांक bit = BIT(vlan_id & BFI_VLAN_WORD_MASK);
	पूर्णांक group_id = (vlan_id >> BFI_VLAN_BLOCK_SHIFT);

	rxf->vlan_filter_table[index] |= bit;
	अगर (rxf->vlan_filter_status == BNA_STATUS_T_ENABLED) अणु
		rxf->vlan_pending_biपंचांगask |= BIT(group_id);
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	पूर्ण
पूर्ण

व्योम
bna_rx_vlan_del(काष्ठा bna_rx *rx, पूर्णांक vlan_id)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;
	पूर्णांक index = (vlan_id >> BFI_VLAN_WORD_SHIFT);
	पूर्णांक bit = BIT(vlan_id & BFI_VLAN_WORD_MASK);
	पूर्णांक group_id = (vlan_id >> BFI_VLAN_BLOCK_SHIFT);

	rxf->vlan_filter_table[index] &= ~bit;
	अगर (rxf->vlan_filter_status == BNA_STATUS_T_ENABLED) अणु
		rxf->vlan_pending_biपंचांगask |= BIT(group_id);
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	पूर्ण
पूर्ण

अटल पूर्णांक
bna_rxf_ucast_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bna_mac *mac = शून्य;

	/* Delete MAC addresses previousely added */
	अगर (!list_empty(&rxf->ucast_pending_del_q)) अणु
		mac = list_first_entry(&rxf->ucast_pending_del_q,
				       काष्ठा bna_mac, qe);
		bna_bfi_ucast_req(rxf, mac, BFI_ENET_H2I_MAC_UCAST_DEL_REQ);
		list_move_tail(&mac->qe, bna_ucam_mod_del_q(rxf->rx->bna));
		वापस 1;
	पूर्ण

	/* Set शेष unicast MAC */
	अगर (rxf->ucast_pending_set) अणु
		rxf->ucast_pending_set = 0;
		ether_addr_copy(rxf->ucast_active_mac.addr,
				rxf->ucast_pending_mac->addr);
		rxf->ucast_active_set = 1;
		bna_bfi_ucast_req(rxf, &rxf->ucast_active_mac,
			BFI_ENET_H2I_MAC_UCAST_SET_REQ);
		वापस 1;
	पूर्ण

	/* Add additional MAC entries */
	अगर (!list_empty(&rxf->ucast_pending_add_q)) अणु
		mac = list_first_entry(&rxf->ucast_pending_add_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &rxf->ucast_active_q);
		bna_bfi_ucast_req(rxf, mac, BFI_ENET_H2I_MAC_UCAST_ADD_REQ);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_ucast_cfg_reset(काष्ठा bna_rxf *rxf, क्रमागत bna_cleanup_type cleanup)
अणु
	काष्ठा bna_mac *mac;

	/* Throw away delete pending ucast entries */
	जबतक (!list_empty(&rxf->ucast_pending_del_q)) अणु
		mac = list_first_entry(&rxf->ucast_pending_del_q,
				       काष्ठा bna_mac, qe);
		अगर (cleanup == BNA_SOFT_CLEANUP)
			list_move_tail(&mac->qe,
				       bna_ucam_mod_del_q(rxf->rx->bna));
		अन्यथा अणु
			bna_bfi_ucast_req(rxf, mac,
					  BFI_ENET_H2I_MAC_UCAST_DEL_REQ);
			list_move_tail(&mac->qe,
				       bna_ucam_mod_del_q(rxf->rx->bna));
			वापस 1;
		पूर्ण
	पूर्ण

	/* Move active ucast entries to pending_add_q */
	जबतक (!list_empty(&rxf->ucast_active_q)) अणु
		mac = list_first_entry(&rxf->ucast_active_q,
				       काष्ठा bna_mac, qe);
		list_move_tail(&mac->qe, &rxf->ucast_pending_add_q);
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_ucast_req(rxf, mac,
				BFI_ENET_H2I_MAC_UCAST_DEL_REQ);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (rxf->ucast_active_set) अणु
		rxf->ucast_pending_set = 1;
		rxf->ucast_active_set = 0;
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_ucast_req(rxf, &rxf->ucast_active_mac,
				BFI_ENET_H2I_MAC_UCAST_CLR_REQ);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_promisc_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bna *bna = rxf->rx->bna;

	/* Enable/disable promiscuous mode */
	अगर (is_promisc_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask)) अणु
		/* move promisc configuration from pending -> active */
		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active |= BNA_RXMODE_PROMISC;
		bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_ENABLED);
		वापस 1;
	पूर्ण अन्यथा अगर (is_promisc_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask)) अणु
		/* move promisc configuration from pending -> active */
		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active &= ~BNA_RXMODE_PROMISC;
		bna->promisc_rid = BFI_INVALID_RID;
		bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_DISABLED);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_promisc_cfg_reset(काष्ठा bna_rxf *rxf, क्रमागत bna_cleanup_type cleanup)
अणु
	काष्ठा bna *bna = rxf->rx->bna;

	/* Clear pending promisc mode disable */
	अगर (is_promisc_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask)) अणु
		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active &= ~BNA_RXMODE_PROMISC;
		bna->promisc_rid = BFI_INVALID_RID;
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_DISABLED);
			वापस 1;
		पूर्ण
	पूर्ण

	/* Move promisc mode config from active -> pending */
	अगर (rxf->rxmode_active & BNA_RXMODE_PROMISC) अणु
		promisc_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active &= ~BNA_RXMODE_PROMISC;
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_rx_promisc_req(rxf, BNA_STATUS_T_DISABLED);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_allmulti_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	/* Enable/disable allmulti mode */
	अगर (is_allmulti_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask)) अणु
		/* move allmulti configuration from pending -> active */
		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active |= BNA_RXMODE_ALLMULTI;
		bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_DISABLED);
		वापस 1;
	पूर्ण अन्यथा अगर (is_allmulti_disable(rxf->rxmode_pending,
					rxf->rxmode_pending_biपंचांगask)) अणु
		/* move allmulti configuration from pending -> active */
		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active &= ~BNA_RXMODE_ALLMULTI;
		bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_ENABLED);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_allmulti_cfg_reset(काष्ठा bna_rxf *rxf, क्रमागत bna_cleanup_type cleanup)
अणु
	/* Clear pending allmulti mode disable */
	अगर (is_allmulti_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask)) अणु
		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active &= ~BNA_RXMODE_ALLMULTI;
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_ENABLED);
			वापस 1;
		पूर्ण
	पूर्ण

	/* Move allmulti mode config from active -> pending */
	अगर (rxf->rxmode_active & BNA_RXMODE_ALLMULTI) अणु
		allmulti_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		rxf->rxmode_active &= ~BNA_RXMODE_ALLMULTI;
		अगर (cleanup == BNA_HARD_CLEANUP) अणु
			bna_bfi_mcast_filter_req(rxf, BNA_STATUS_T_ENABLED);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bna_rxf_promisc_enable(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bna *bna = rxf->rx->bna;
	पूर्णांक ret = 0;

	अगर (is_promisc_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask) ||
		(rxf->rxmode_active & BNA_RXMODE_PROMISC)) अणु
		/* Do nothing अगर pending enable or alपढ़ोy enabled */
	पूर्ण अन्यथा अगर (is_promisc_disable(rxf->rxmode_pending,
					rxf->rxmode_pending_biपंचांगask)) अणु
		/* Turn off pending disable command */
		promisc_inactive(rxf->rxmode_pending,
			rxf->rxmode_pending_biपंचांगask);
	पूर्ण अन्यथा अणु
		/* Schedule enable */
		promisc_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		bna->promisc_rid = rxf->rx->rid;
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
bna_rxf_promisc_disable(काष्ठा bna_rxf *rxf)
अणु
	काष्ठा bna *bna = rxf->rx->bna;
	पूर्णांक ret = 0;

	अगर (is_promisc_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask) ||
		(!(rxf->rxmode_active & BNA_RXMODE_PROMISC))) अणु
		/* Do nothing अगर pending disable or alपढ़ोy disabled */
	पूर्ण अन्यथा अगर (is_promisc_enable(rxf->rxmode_pending,
					rxf->rxmode_pending_biपंचांगask)) अणु
		/* Turn off pending enable command */
		promisc_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		bna->promisc_rid = BFI_INVALID_RID;
	पूर्ण अन्यथा अगर (rxf->rxmode_active & BNA_RXMODE_PROMISC) अणु
		/* Schedule disable */
		promisc_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
bna_rxf_allmulti_enable(काष्ठा bna_rxf *rxf)
अणु
	पूर्णांक ret = 0;

	अगर (is_allmulti_enable(rxf->rxmode_pending,
			rxf->rxmode_pending_biपंचांगask) ||
			(rxf->rxmode_active & BNA_RXMODE_ALLMULTI)) अणु
		/* Do nothing अगर pending enable or alपढ़ोy enabled */
	पूर्ण अन्यथा अगर (is_allmulti_disable(rxf->rxmode_pending,
					rxf->rxmode_pending_biपंचांगask)) अणु
		/* Turn off pending disable command */
		allmulti_inactive(rxf->rxmode_pending,
			rxf->rxmode_pending_biपंचांगask);
	पूर्ण अन्यथा अणु
		/* Schedule enable */
		allmulti_enable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
bna_rxf_allmulti_disable(काष्ठा bna_rxf *rxf)
अणु
	पूर्णांक ret = 0;

	अगर (is_allmulti_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask) ||
		(!(rxf->rxmode_active & BNA_RXMODE_ALLMULTI))) अणु
		/* Do nothing अगर pending disable or alपढ़ोy disabled */
	पूर्ण अन्यथा अगर (is_allmulti_enable(rxf->rxmode_pending,
					rxf->rxmode_pending_biपंचांगask)) अणु
		/* Turn off pending enable command */
		allmulti_inactive(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
	पूर्ण अन्यथा अगर (rxf->rxmode_active & BNA_RXMODE_ALLMULTI) अणु
		/* Schedule disable */
		allmulti_disable(rxf->rxmode_pending,
				rxf->rxmode_pending_biपंचांगask);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
bna_rxf_vlan_strip_cfg_apply(काष्ठा bna_rxf *rxf)
अणु
	अगर (rxf->vlan_strip_pending) अणु
			rxf->vlan_strip_pending = false;
			bna_bfi_vlan_strip_enable(rxf);
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* RX */

#घोषणा	BNA_GET_RXQS(qcfg)	(((qcfg)->rxp_type == BNA_RXP_SINGLE) ?	\
	(qcfg)->num_paths : ((qcfg)->num_paths * 2))

#घोषणा	SIZE_TO_PAGES(size)	(((size) >> PAGE_SHIFT) + ((((size) &\
	(PAGE_SIZE - 1)) + (PAGE_SIZE - 1)) >> PAGE_SHIFT))

#घोषणा	call_rx_stop_cbfn(rx)						\
करो अणु								    \
	अगर ((rx)->stop_cbfn) अणु						\
		व्योम (*cbfn)(व्योम *, काष्ठा bna_rx *);	  \
		व्योम *cbarg;					    \
		cbfn = (rx)->stop_cbfn;				 \
		cbarg = (rx)->stop_cbarg;			       \
		(rx)->stop_cbfn = शून्य;					\
		(rx)->stop_cbarg = शून्य;				\
		cbfn(cbarg, rx);					\
	पूर्ण							       \
पूर्ण जबतक (0)

#घोषणा call_rx_stall_cbfn(rx)						\
करो अणु									\
	अगर ((rx)->rx_stall_cbfn)					\
		(rx)->rx_stall_cbfn((rx)->bna->bnad, (rx));		\
पूर्ण जबतक (0)

#घोषणा bfi_enet_datapath_q_init(bfi_q, bna_qpt)			\
करो अणु									\
	काष्ठा bna_dma_addr cur_q_addr =				\
		*((काष्ठा bna_dma_addr *)((bna_qpt)->kv_qpt_ptr));	\
	(bfi_q)->pg_tbl.a32.addr_lo = (bna_qpt)->hw_qpt_ptr.lsb;	\
	(bfi_q)->pg_tbl.a32.addr_hi = (bna_qpt)->hw_qpt_ptr.msb;	\
	(bfi_q)->first_entry.a32.addr_lo = cur_q_addr.lsb;		\
	(bfi_q)->first_entry.a32.addr_hi = cur_q_addr.msb;		\
	(bfi_q)->pages = htons((u16)(bna_qpt)->page_count);	\
	(bfi_q)->page_sz = htons((u16)(bna_qpt)->page_size);\
पूर्ण जबतक (0)

अटल व्योम bna_bfi_rx_enet_start(काष्ठा bna_rx *rx);
अटल व्योम bna_rx_enet_stop(काष्ठा bna_rx *rx);
अटल व्योम bna_rx_mod_cb_rx_stopped(व्योम *arg, काष्ठा bna_rx *rx);

bfa_fsm_state_decl(bna_rx, stopped,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, start_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, start_stop_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, rxf_start_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, started,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, rxf_stop_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, stop_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, cleanup_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, failed,
	काष्ठा bna_rx, क्रमागत bna_rx_event);
bfa_fsm_state_decl(bna_rx, quiesce_रुको,
	काष्ठा bna_rx, क्रमागत bna_rx_event);

अटल व्योम bna_rx_sm_stopped_entry(काष्ठा bna_rx *rx)
अणु
	call_rx_stop_cbfn(rx);
पूर्ण

अटल व्योम bna_rx_sm_stopped(काष्ठा bna_rx *rx,
				क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_START:
		bfa_fsm_set_state(rx, bna_rx_sm_start_रुको);
		अवरोध;

	हाल RX_E_STOP:
		call_rx_stop_cbfn(rx);
		अवरोध;

	हाल RX_E_FAIL:
		/* no-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bna_rx_sm_start_रुको_entry(काष्ठा bna_rx *rx)
अणु
	bna_bfi_rx_enet_start(rx);
पूर्ण

अटल व्योम
bna_rx_sm_stop_रुको_entry(काष्ठा bna_rx *rx)
अणु
पूर्ण

अटल व्योम
bna_rx_sm_stop_रुको(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_FAIL:
	हाल RX_E_STOPPED:
		bfa_fsm_set_state(rx, bna_rx_sm_cleanup_रुको);
		rx->rx_cleanup_cbfn(rx->bna->bnad, rx);
		अवरोध;

	हाल RX_E_STARTED:
		bna_rx_enet_stop(rx);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bna_rx_sm_start_रुको(काष्ठा bna_rx *rx,
				क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_start_stop_रुको);
		अवरोध;

	हाल RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_stopped);
		अवरोध;

	हाल RX_E_STARTED:
		bfa_fsm_set_state(rx, bna_rx_sm_rxf_start_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bna_rx_sm_rxf_start_रुको_entry(काष्ठा bna_rx *rx)
अणु
	rx->rx_post_cbfn(rx->bna->bnad, rx);
	bna_rxf_start(&rx->rxf);
पूर्ण

अटल व्योम
bna_rx_sm_rxf_stop_रुको_entry(काष्ठा bna_rx *rx)
अणु
पूर्ण

अटल व्योम
bna_rx_sm_rxf_stop_रुको(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_cleanup_रुको);
		bna_rxf_fail(&rx->rxf);
		call_rx_stall_cbfn(rx);
		rx->rx_cleanup_cbfn(rx->bna->bnad, rx);
		अवरोध;

	हाल RX_E_RXF_STARTED:
		bna_rxf_stop(&rx->rxf);
		अवरोध;

	हाल RX_E_RXF_STOPPED:
		bfa_fsm_set_state(rx, bna_rx_sm_stop_रुको);
		call_rx_stall_cbfn(rx);
		bna_rx_enet_stop(rx);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम
bna_rx_sm_start_stop_रुको_entry(काष्ठा bna_rx *rx)
अणु
पूर्ण

अटल व्योम
bna_rx_sm_start_stop_रुको(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_FAIL:
	हाल RX_E_STOPPED:
		bfa_fsm_set_state(rx, bna_rx_sm_stopped);
		अवरोध;

	हाल RX_E_STARTED:
		bna_rx_enet_stop(rx);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_rx_sm_started_entry(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rxp *rxp;
	पूर्णांक is_regular = (rx->type == BNA_RX_T_REGULAR);

	/* Start IB */
	list_क्रम_each_entry(rxp, &rx->rxp_q, qe)
		bna_ib_start(rx->bna, &rxp->cq.ib, is_regular);

	bna_ethport_cb_rx_started(&rx->bna->ethport);
पूर्ण

अटल व्योम
bna_rx_sm_started(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_rxf_stop_रुको);
		bna_ethport_cb_rx_stopped(&rx->bna->ethport);
		bna_rxf_stop(&rx->rxf);
		अवरोध;

	हाल RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_failed);
		bna_ethport_cb_rx_stopped(&rx->bna->ethport);
		bna_rxf_fail(&rx->rxf);
		call_rx_stall_cbfn(rx);
		rx->rx_cleanup_cbfn(rx->bna->bnad, rx);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bna_rx_sm_rxf_start_रुको(काष्ठा bna_rx *rx,
				क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_rxf_stop_रुको);
		अवरोध;

	हाल RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_failed);
		bna_rxf_fail(&rx->rxf);
		call_rx_stall_cbfn(rx);
		rx->rx_cleanup_cbfn(rx->bna->bnad, rx);
		अवरोध;

	हाल RX_E_RXF_STARTED:
		bfa_fsm_set_state(rx, bna_rx_sm_started);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bna_rx_sm_cleanup_रुको_entry(काष्ठा bna_rx *rx)
अणु
पूर्ण

अटल व्योम
bna_rx_sm_cleanup_रुको(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_FAIL:
	हाल RX_E_RXF_STOPPED:
		/* No-op */
		अवरोध;

	हाल RX_E_CLEANUP_DONE:
		bfa_fsm_set_state(rx, bna_rx_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bna_rx_sm_failed_entry(काष्ठा bna_rx *rx)
अणु
पूर्ण

अटल व्योम
bna_rx_sm_failed(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_START:
		bfa_fsm_set_state(rx, bna_rx_sm_quiesce_रुको);
		अवरोध;

	हाल RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_cleanup_रुको);
		अवरोध;

	हाल RX_E_FAIL:
	हाल RX_E_RXF_STARTED:
	हाल RX_E_RXF_STOPPED:
		/* No-op */
		अवरोध;

	हाल RX_E_CLEANUP_DONE:
		bfa_fsm_set_state(rx, bna_rx_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
पूर्ण	पूर्ण

अटल व्योम
bna_rx_sm_quiesce_रुको_entry(काष्ठा bna_rx *rx)
अणु
पूर्ण

अटल व्योम
bna_rx_sm_quiesce_रुको(काष्ठा bna_rx *rx, क्रमागत bna_rx_event event)
अणु
	चयन (event) अणु
	हाल RX_E_STOP:
		bfa_fsm_set_state(rx, bna_rx_sm_cleanup_रुको);
		अवरोध;

	हाल RX_E_FAIL:
		bfa_fsm_set_state(rx, bna_rx_sm_failed);
		अवरोध;

	हाल RX_E_CLEANUP_DONE:
		bfa_fsm_set_state(rx, bna_rx_sm_start_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_rx_enet_start(काष्ठा bna_rx *rx)
अणु
	काष्ठा bfi_enet_rx_cfg_req *cfg_req = &rx->bfi_enet_cmd.cfg_req;
	काष्ठा bna_rxp *rxp = शून्य;
	काष्ठा bna_rxq *q0 = शून्य, *q1 = शून्य;
	पूर्णांक i;

	bfi_msgq_mhdr_set(cfg_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RX_CFG_SET_REQ, 0, rx->rid);
	cfg_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_rx_cfg_req)));

	cfg_req->rx_cfg.frame_size = bna_enet_mtu_get(&rx->bna->enet);
	cfg_req->num_queue_sets = rx->num_paths;
	क्रम (i = 0; i < rx->num_paths; i++) अणु
		rxp = rxp ? list_next_entry(rxp, qe)
			: list_first_entry(&rx->rxp_q, काष्ठा bna_rxp, qe);
		GET_RXQS(rxp, q0, q1);
		चयन (rxp->type) अणु
		हाल BNA_RXP_SLR:
		हाल BNA_RXP_HDS:
			/* Small RxQ */
			bfi_enet_datapath_q_init(&cfg_req->q_cfg[i].qs.q,
						&q1->qpt);
			cfg_req->q_cfg[i].qs.rx_buffer_size =
				htons((u16)q1->buffer_size);
			fallthrough;

		हाल BNA_RXP_SINGLE:
			/* Large/Single RxQ */
			bfi_enet_datapath_q_init(&cfg_req->q_cfg[i].ql.q,
						&q0->qpt);
			अगर (q0->multi_buffer)
				/* multi-buffer is enabled by allocating
				 * a new rx with new set of resources.
				 * q0->buffer_size should be initialized to
				 * fragment size.
				 */
				cfg_req->rx_cfg.multi_buffer =
					BNA_STATUS_T_ENABLED;
			अन्यथा
				q0->buffer_size =
					bna_enet_mtu_get(&rx->bna->enet);
			cfg_req->q_cfg[i].ql.rx_buffer_size =
				htons((u16)q0->buffer_size);
			अवरोध;

		शेष:
			BUG_ON(1);
		पूर्ण

		bfi_enet_datapath_q_init(&cfg_req->q_cfg[i].cq.q,
					&rxp->cq.qpt);

		cfg_req->q_cfg[i].ib.index_addr.a32.addr_lo =
			rxp->cq.ib.ib_seg_host_addr.lsb;
		cfg_req->q_cfg[i].ib.index_addr.a32.addr_hi =
			rxp->cq.ib.ib_seg_host_addr.msb;
		cfg_req->q_cfg[i].ib.पूर्णांकr.msix_index =
			htons((u16)rxp->cq.ib.पूर्णांकr_vector);
	पूर्ण

	cfg_req->ib_cfg.पूर्णांक_pkt_dma = BNA_STATUS_T_DISABLED;
	cfg_req->ib_cfg.पूर्णांक_enabled = BNA_STATUS_T_ENABLED;
	cfg_req->ib_cfg.पूर्णांक_pkt_enabled = BNA_STATUS_T_DISABLED;
	cfg_req->ib_cfg.continuous_coalescing = BNA_STATUS_T_DISABLED;
	cfg_req->ib_cfg.msix = (rxp->cq.ib.पूर्णांकr_type == BNA_INTR_T_MSIX)
				? BNA_STATUS_T_ENABLED :
				BNA_STATUS_T_DISABLED;
	cfg_req->ib_cfg.coalescing_समयout =
			htonl((u32)rxp->cq.ib.coalescing_समयo);
	cfg_req->ib_cfg.पूर्णांकer_pkt_समयout =
			htonl((u32)rxp->cq.ib.पूर्णांकerpkt_समयo);
	cfg_req->ib_cfg.पूर्णांकer_pkt_count = (u8)rxp->cq.ib.पूर्णांकerpkt_count;

	चयन (rxp->type) अणु
	हाल BNA_RXP_SLR:
		cfg_req->rx_cfg.rxq_type = BFI_ENET_RXQ_LARGE_SMALL;
		अवरोध;

	हाल BNA_RXP_HDS:
		cfg_req->rx_cfg.rxq_type = BFI_ENET_RXQ_HDS;
		cfg_req->rx_cfg.hds.type = rx->hds_cfg.hdr_type;
		cfg_req->rx_cfg.hds.क्रमce_offset = rx->hds_cfg.क्रमced_offset;
		cfg_req->rx_cfg.hds.max_header_size = rx->hds_cfg.क्रमced_offset;
		अवरोध;

	हाल BNA_RXP_SINGLE:
		cfg_req->rx_cfg.rxq_type = BFI_ENET_RXQ_SINGLE;
		अवरोध;

	शेष:
		BUG_ON(1);
	पूर्ण
	cfg_req->rx_cfg.strip_vlan = rx->rxf.vlan_strip_status;

	bfa_msgq_cmd_set(&rx->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_rx_cfg_req), &cfg_req->mh);
	bfa_msgq_cmd_post(&rx->bna->msgq, &rx->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_rx_enet_stop(काष्ठा bna_rx *rx)
अणु
	काष्ठा bfi_enet_req *req = &rx->bfi_enet_cmd.req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_RX_CFG_CLR_REQ, 0, rx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_req)));
	bfa_msgq_cmd_set(&rx->msgq_cmd, शून्य, शून्य, माप(काष्ठा bfi_enet_req),
		&req->mh);
	bfa_msgq_cmd_post(&rx->bna->msgq, &rx->msgq_cmd);
पूर्ण

अटल व्योम
bna_rx_enet_stop(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rxp *rxp;

	/* Stop IB */
	list_क्रम_each_entry(rxp, &rx->rxp_q, qe)
		bna_ib_stop(rx->bna, &rxp->cq.ib);

	bna_bfi_rx_enet_stop(rx);
पूर्ण

अटल पूर्णांक
bna_rx_res_check(काष्ठा bna_rx_mod *rx_mod, काष्ठा bna_rx_config *rx_cfg)
अणु
	अगर ((rx_mod->rx_मुक्त_count == 0) ||
		(rx_mod->rxp_मुक्त_count == 0) ||
		(rx_mod->rxq_मुक्त_count == 0))
		वापस 0;

	अगर (rx_cfg->rxp_type == BNA_RXP_SINGLE) अणु
		अगर ((rx_mod->rxp_मुक्त_count < rx_cfg->num_paths) ||
			(rx_mod->rxq_मुक्त_count < rx_cfg->num_paths))
				वापस 0;
	पूर्ण अन्यथा अणु
		अगर ((rx_mod->rxp_मुक्त_count < rx_cfg->num_paths) ||
			(rx_mod->rxq_मुक्त_count < (2 * rx_cfg->num_paths)))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा bna_rxq *
bna_rxq_get(काष्ठा bna_rx_mod *rx_mod)
अणु
	काष्ठा bna_rxq *rxq = शून्य;

	rxq = list_first_entry(&rx_mod->rxq_मुक्त_q, काष्ठा bna_rxq, qe);
	list_del(&rxq->qe);
	rx_mod->rxq_मुक्त_count--;

	वापस rxq;
पूर्ण

अटल व्योम
bna_rxq_put(काष्ठा bna_rx_mod *rx_mod, काष्ठा bna_rxq *rxq)
अणु
	list_add_tail(&rxq->qe, &rx_mod->rxq_मुक्त_q);
	rx_mod->rxq_मुक्त_count++;
पूर्ण

अटल काष्ठा bna_rxp *
bna_rxp_get(काष्ठा bna_rx_mod *rx_mod)
अणु
	काष्ठा bna_rxp *rxp = शून्य;

	rxp = list_first_entry(&rx_mod->rxp_मुक्त_q, काष्ठा bna_rxp, qe);
	list_del(&rxp->qe);
	rx_mod->rxp_मुक्त_count--;

	वापस rxp;
पूर्ण

अटल व्योम
bna_rxp_put(काष्ठा bna_rx_mod *rx_mod, काष्ठा bna_rxp *rxp)
अणु
	list_add_tail(&rxp->qe, &rx_mod->rxp_मुक्त_q);
	rx_mod->rxp_मुक्त_count++;
पूर्ण

अटल काष्ठा bna_rx *
bna_rx_get(काष्ठा bna_rx_mod *rx_mod, क्रमागत bna_rx_type type)
अणु
	काष्ठा bna_rx *rx = शून्य;

	BUG_ON(list_empty(&rx_mod->rx_मुक्त_q));
	अगर (type == BNA_RX_T_REGULAR)
		rx = list_first_entry(&rx_mod->rx_मुक्त_q, काष्ठा bna_rx, qe);
	अन्यथा
		rx = list_last_entry(&rx_mod->rx_मुक्त_q, काष्ठा bna_rx, qe);

	rx_mod->rx_मुक्त_count--;
	list_move_tail(&rx->qe, &rx_mod->rx_active_q);
	rx->type = type;

	वापस rx;
पूर्ण

अटल व्योम
bna_rx_put(काष्ठा bna_rx_mod *rx_mod, काष्ठा bna_rx *rx)
अणु
	काष्ठा list_head *qe;

	list_क्रम_each_prev(qe, &rx_mod->rx_मुक्त_q)
		अगर (((काष्ठा bna_rx *)qe)->rid < rx->rid)
			अवरोध;

	list_add(&rx->qe, qe);
	rx_mod->rx_मुक्त_count++;
पूर्ण

अटल व्योम
bna_rxp_add_rxqs(काष्ठा bna_rxp *rxp, काष्ठा bna_rxq *q0,
		काष्ठा bna_rxq *q1)
अणु
	चयन (rxp->type) अणु
	हाल BNA_RXP_SINGLE:
		rxp->rxq.single.only = q0;
		rxp->rxq.single.reserved = शून्य;
		अवरोध;
	हाल BNA_RXP_SLR:
		rxp->rxq.slr.large = q0;
		rxp->rxq.slr.small = q1;
		अवरोध;
	हाल BNA_RXP_HDS:
		rxp->rxq.hds.data = q0;
		rxp->rxq.hds.hdr = q1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bna_rxq_qpt_setup(काष्ठा bna_rxq *rxq,
		काष्ठा bna_rxp *rxp,
		u32 page_count,
		u32 page_size,
		काष्ठा bna_mem_descr *qpt_mem,
		काष्ठा bna_mem_descr *swqpt_mem,
		काष्ठा bna_mem_descr *page_mem)
अणु
	u8 *kva;
	u64 dma;
	काष्ठा bna_dma_addr bna_dma;
	पूर्णांक	i;

	rxq->qpt.hw_qpt_ptr.lsb = qpt_mem->dma.lsb;
	rxq->qpt.hw_qpt_ptr.msb = qpt_mem->dma.msb;
	rxq->qpt.kv_qpt_ptr = qpt_mem->kva;
	rxq->qpt.page_count = page_count;
	rxq->qpt.page_size = page_size;

	rxq->rcb->sw_qpt = (व्योम **) swqpt_mem->kva;
	rxq->rcb->sw_q = page_mem->kva;

	kva = page_mem->kva;
	BNA_GET_DMA_ADDR(&page_mem->dma, dma);

	क्रम (i = 0; i < rxq->qpt.page_count; i++) अणु
		rxq->rcb->sw_qpt[i] = kva;
		kva += PAGE_SIZE;

		BNA_SET_DMA_ADDR(dma, &bna_dma);
		((काष्ठा bna_dma_addr *)rxq->qpt.kv_qpt_ptr)[i].lsb =
			bna_dma.lsb;
		((काष्ठा bna_dma_addr *)rxq->qpt.kv_qpt_ptr)[i].msb =
			bna_dma.msb;
		dma += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम
bna_rxp_cqpt_setup(काष्ठा bna_rxp *rxp,
		u32 page_count,
		u32 page_size,
		काष्ठा bna_mem_descr *qpt_mem,
		काष्ठा bna_mem_descr *swqpt_mem,
		काष्ठा bna_mem_descr *page_mem)
अणु
	u8 *kva;
	u64 dma;
	काष्ठा bna_dma_addr bna_dma;
	पूर्णांक	i;

	rxp->cq.qpt.hw_qpt_ptr.lsb = qpt_mem->dma.lsb;
	rxp->cq.qpt.hw_qpt_ptr.msb = qpt_mem->dma.msb;
	rxp->cq.qpt.kv_qpt_ptr = qpt_mem->kva;
	rxp->cq.qpt.page_count = page_count;
	rxp->cq.qpt.page_size = page_size;

	rxp->cq.ccb->sw_qpt = (व्योम **) swqpt_mem->kva;
	rxp->cq.ccb->sw_q = page_mem->kva;

	kva = page_mem->kva;
	BNA_GET_DMA_ADDR(&page_mem->dma, dma);

	क्रम (i = 0; i < rxp->cq.qpt.page_count; i++) अणु
		rxp->cq.ccb->sw_qpt[i] = kva;
		kva += PAGE_SIZE;

		BNA_SET_DMA_ADDR(dma, &bna_dma);
		((काष्ठा bna_dma_addr *)rxp->cq.qpt.kv_qpt_ptr)[i].lsb =
			bna_dma.lsb;
		((काष्ठा bna_dma_addr *)rxp->cq.qpt.kv_qpt_ptr)[i].msb =
			bna_dma.msb;
		dma += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम
bna_rx_mod_cb_rx_stopped(व्योम *arg, काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rx_mod *rx_mod = (काष्ठा bna_rx_mod *)arg;

	bfa_wc_करोwn(&rx_mod->rx_stop_wc);
पूर्ण

अटल व्योम
bna_rx_mod_cb_rx_stopped_all(व्योम *arg)
अणु
	काष्ठा bna_rx_mod *rx_mod = (काष्ठा bna_rx_mod *)arg;

	अगर (rx_mod->stop_cbfn)
		rx_mod->stop_cbfn(&rx_mod->bna->enet);
	rx_mod->stop_cbfn = शून्य;
पूर्ण

अटल व्योम
bna_rx_start(काष्ठा bna_rx *rx)
अणु
	rx->rx_flags |= BNA_RX_F_ENET_STARTED;
	अगर (rx->rx_flags & BNA_RX_F_ENABLED)
		bfa_fsm_send_event(rx, RX_E_START);
पूर्ण

अटल व्योम
bna_rx_stop(काष्ठा bna_rx *rx)
अणु
	rx->rx_flags &= ~BNA_RX_F_ENET_STARTED;
	अगर (rx->fsm == (bfa_fsm_t) bna_rx_sm_stopped)
		bna_rx_mod_cb_rx_stopped(&rx->bna->rx_mod, rx);
	अन्यथा अणु
		rx->stop_cbfn = bna_rx_mod_cb_rx_stopped;
		rx->stop_cbarg = &rx->bna->rx_mod;
		bfa_fsm_send_event(rx, RX_E_STOP);
	पूर्ण
पूर्ण

अटल व्योम
bna_rx_fail(काष्ठा bna_rx *rx)
अणु
	/* Indicate Enet is not enabled, and failed */
	rx->rx_flags &= ~BNA_RX_F_ENET_STARTED;
	bfa_fsm_send_event(rx, RX_E_FAIL);
पूर्ण

व्योम
bna_rx_mod_start(काष्ठा bna_rx_mod *rx_mod, क्रमागत bna_rx_type type)
अणु
	काष्ठा bna_rx *rx;

	rx_mod->flags |= BNA_RX_MOD_F_ENET_STARTED;
	अगर (type == BNA_RX_T_LOOPBACK)
		rx_mod->flags |= BNA_RX_MOD_F_ENET_LOOPBACK;

	list_क्रम_each_entry(rx, &rx_mod->rx_active_q, qe)
		अगर (rx->type == type)
			bna_rx_start(rx);
पूर्ण

व्योम
bna_rx_mod_stop(काष्ठा bna_rx_mod *rx_mod, क्रमागत bna_rx_type type)
अणु
	काष्ठा bna_rx *rx;

	rx_mod->flags &= ~BNA_RX_MOD_F_ENET_STARTED;
	rx_mod->flags &= ~BNA_RX_MOD_F_ENET_LOOPBACK;

	rx_mod->stop_cbfn = bna_enet_cb_rx_stopped;

	bfa_wc_init(&rx_mod->rx_stop_wc, bna_rx_mod_cb_rx_stopped_all, rx_mod);

	list_क्रम_each_entry(rx, &rx_mod->rx_active_q, qe)
		अगर (rx->type == type) अणु
			bfa_wc_up(&rx_mod->rx_stop_wc);
			bna_rx_stop(rx);
		पूर्ण

	bfa_wc_रुको(&rx_mod->rx_stop_wc);
पूर्ण

व्योम
bna_rx_mod_fail(काष्ठा bna_rx_mod *rx_mod)
अणु
	काष्ठा bna_rx *rx;

	rx_mod->flags &= ~BNA_RX_MOD_F_ENET_STARTED;
	rx_mod->flags &= ~BNA_RX_MOD_F_ENET_LOOPBACK;

	list_क्रम_each_entry(rx, &rx_mod->rx_active_q, qe)
		bna_rx_fail(rx);
पूर्ण

व्योम bna_rx_mod_init(काष्ठा bna_rx_mod *rx_mod, काष्ठा bna *bna,
			काष्ठा bna_res_info *res_info)
अणु
	पूर्णांक	index;
	काष्ठा bna_rx *rx_ptr;
	काष्ठा bna_rxp *rxp_ptr;
	काष्ठा bna_rxq *rxq_ptr;

	rx_mod->bna = bna;
	rx_mod->flags = 0;

	rx_mod->rx = (काष्ठा bna_rx *)
		res_info[BNA_MOD_RES_MEM_T_RX_ARRAY].res_u.mem_info.mdl[0].kva;
	rx_mod->rxp = (काष्ठा bna_rxp *)
		res_info[BNA_MOD_RES_MEM_T_RXP_ARRAY].res_u.mem_info.mdl[0].kva;
	rx_mod->rxq = (काष्ठा bna_rxq *)
		res_info[BNA_MOD_RES_MEM_T_RXQ_ARRAY].res_u.mem_info.mdl[0].kva;

	/* Initialize the queues */
	INIT_LIST_HEAD(&rx_mod->rx_मुक्त_q);
	rx_mod->rx_मुक्त_count = 0;
	INIT_LIST_HEAD(&rx_mod->rxq_मुक्त_q);
	rx_mod->rxq_मुक्त_count = 0;
	INIT_LIST_HEAD(&rx_mod->rxp_मुक्त_q);
	rx_mod->rxp_मुक्त_count = 0;
	INIT_LIST_HEAD(&rx_mod->rx_active_q);

	/* Build RX queues */
	क्रम (index = 0; index < bna->ioceth.attr.num_rxp; index++) अणु
		rx_ptr = &rx_mod->rx[index];

		INIT_LIST_HEAD(&rx_ptr->rxp_q);
		rx_ptr->bna = शून्य;
		rx_ptr->rid = index;
		rx_ptr->stop_cbfn = शून्य;
		rx_ptr->stop_cbarg = शून्य;

		list_add_tail(&rx_ptr->qe, &rx_mod->rx_मुक्त_q);
		rx_mod->rx_मुक्त_count++;
	पूर्ण

	/* build RX-path queue */
	क्रम (index = 0; index < bna->ioceth.attr.num_rxp; index++) अणु
		rxp_ptr = &rx_mod->rxp[index];
		list_add_tail(&rxp_ptr->qe, &rx_mod->rxp_मुक्त_q);
		rx_mod->rxp_मुक्त_count++;
	पूर्ण

	/* build RXQ queue */
	क्रम (index = 0; index < (bna->ioceth.attr.num_rxp * 2); index++) अणु
		rxq_ptr = &rx_mod->rxq[index];
		list_add_tail(&rxq_ptr->qe, &rx_mod->rxq_मुक्त_q);
		rx_mod->rxq_मुक्त_count++;
	पूर्ण
पूर्ण

व्योम
bna_rx_mod_uninit(काष्ठा bna_rx_mod *rx_mod)
अणु
	rx_mod->bna = शून्य;
पूर्ण

व्योम
bna_bfi_rx_enet_start_rsp(काष्ठा bna_rx *rx, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_rx_cfg_rsp *cfg_rsp = &rx->bfi_enet_cmd.cfg_rsp;
	काष्ठा bna_rxp *rxp = शून्य;
	काष्ठा bna_rxq *q0 = शून्य, *q1 = शून्य;
	पूर्णांक i;

	bfa_msgq_rsp_copy(&rx->bna->msgq, (u8 *)cfg_rsp,
		माप(काष्ठा bfi_enet_rx_cfg_rsp));

	rx->hw_id = cfg_rsp->hw_id;

	क्रम (i = 0, rxp = list_first_entry(&rx->rxp_q, काष्ठा bna_rxp, qe);
	     i < rx->num_paths; i++, rxp = list_next_entry(rxp, qe)) अणु
		GET_RXQS(rxp, q0, q1);

		/* Setup करोorbells */
		rxp->cq.ccb->i_dbell->करोorbell_addr =
			rx->bna->pcidev.pci_bar_kva
			+ ntohl(cfg_rsp->q_handles[i].i_dbell);
		rxp->hw_id = cfg_rsp->q_handles[i].hw_cqid;
		q0->rcb->q_dbell =
			rx->bna->pcidev.pci_bar_kva
			+ ntohl(cfg_rsp->q_handles[i].ql_dbell);
		q0->hw_id = cfg_rsp->q_handles[i].hw_lqid;
		अगर (q1) अणु
			q1->rcb->q_dbell =
			rx->bna->pcidev.pci_bar_kva
			+ ntohl(cfg_rsp->q_handles[i].qs_dbell);
			q1->hw_id = cfg_rsp->q_handles[i].hw_sqid;
		पूर्ण

		/* Initialize producer/consumer indexes */
		(*rxp->cq.ccb->hw_producer_index) = 0;
		rxp->cq.ccb->producer_index = 0;
		q0->rcb->producer_index = q0->rcb->consumer_index = 0;
		अगर (q1)
			q1->rcb->producer_index = q1->rcb->consumer_index = 0;
	पूर्ण

	bfa_fsm_send_event(rx, RX_E_STARTED);
पूर्ण

व्योम
bna_bfi_rx_enet_stop_rsp(काष्ठा bna_rx *rx, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	bfa_fsm_send_event(rx, RX_E_STOPPED);
पूर्ण

व्योम
bna_rx_res_req(काष्ठा bna_rx_config *q_cfg, काष्ठा bna_res_info *res_info)
अणु
	u32 cq_size, hq_size, dq_size;
	u32 cpage_count, hpage_count, dpage_count;
	काष्ठा bna_mem_info *mem_info;
	u32 cq_depth;
	u32 hq_depth;
	u32 dq_depth;

	dq_depth = q_cfg->q0_depth;
	hq_depth = ((q_cfg->rxp_type == BNA_RXP_SINGLE) ? 0 : q_cfg->q1_depth);
	cq_depth = roundup_घात_of_two(dq_depth + hq_depth);

	cq_size = cq_depth * BFI_CQ_WI_SIZE;
	cq_size = ALIGN(cq_size, PAGE_SIZE);
	cpage_count = SIZE_TO_PAGES(cq_size);

	dq_depth = roundup_घात_of_two(dq_depth);
	dq_size = dq_depth * BFI_RXQ_WI_SIZE;
	dq_size = ALIGN(dq_size, PAGE_SIZE);
	dpage_count = SIZE_TO_PAGES(dq_size);

	अगर (BNA_RXP_SINGLE != q_cfg->rxp_type) अणु
		hq_depth = roundup_घात_of_two(hq_depth);
		hq_size = hq_depth * BFI_RXQ_WI_SIZE;
		hq_size = ALIGN(hq_size, PAGE_SIZE);
		hpage_count = SIZE_TO_PAGES(hq_size);
	पूर्ण अन्यथा
		hpage_count = 0;

	res_info[BNA_RX_RES_MEM_T_CCB].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CCB].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = माप(काष्ठा bna_ccb);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_RCB].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_RCB].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = माप(काष्ठा bna_rcb);
	mem_info->num = BNA_GET_RXQS(q_cfg);

	res_info[BNA_RX_RES_MEM_T_CQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = cpage_count * माप(काष्ठा bna_dma_addr);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_CSWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CSWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = cpage_count * माप(व्योम *);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * cpage_count;
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_DQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_DQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = dpage_count * माप(काष्ठा bna_dma_addr);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_DSWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_DSWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = dpage_count * माप(व्योम *);
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_DPAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_DPAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * dpage_count;
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_HQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_HQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = hpage_count * माप(काष्ठा bna_dma_addr);
	mem_info->num = (hpage_count ? q_cfg->num_paths : 0);

	res_info[BNA_RX_RES_MEM_T_HSWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_HSWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = hpage_count * माप(व्योम *);
	mem_info->num = (hpage_count ? q_cfg->num_paths : 0);

	res_info[BNA_RX_RES_MEM_T_HPAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_HPAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * hpage_count;
	mem_info->num = (hpage_count ? q_cfg->num_paths : 0);

	res_info[BNA_RX_RES_MEM_T_IBIDX].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = BFI_IBIDX_SIZE;
	mem_info->num = q_cfg->num_paths;

	res_info[BNA_RX_RES_MEM_T_RIT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_RX_RES_MEM_T_RIT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = BFI_ENET_RSS_RIT_MAX;
	mem_info->num = 1;

	res_info[BNA_RX_RES_T_INTR].res_type = BNA_RES_T_INTR;
	res_info[BNA_RX_RES_T_INTR].res_u.पूर्णांकr_info.पूर्णांकr_type = BNA_INTR_T_MSIX;
	res_info[BNA_RX_RES_T_INTR].res_u.पूर्णांकr_info.num = q_cfg->num_paths;
पूर्ण

काष्ठा bna_rx *
bna_rx_create(काष्ठा bna *bna, काष्ठा bnad *bnad,
		काष्ठा bna_rx_config *rx_cfg,
		स्थिर काष्ठा bna_rx_event_cbfn *rx_cbfn,
		काष्ठा bna_res_info *res_info,
		व्योम *priv)
अणु
	काष्ठा bna_rx_mod *rx_mod = &bna->rx_mod;
	काष्ठा bna_rx *rx;
	काष्ठा bna_rxp *rxp;
	काष्ठा bna_rxq *q0;
	काष्ठा bna_rxq *q1;
	काष्ठा bna_पूर्णांकr_info *पूर्णांकr_info;
	काष्ठा bna_mem_descr *hqunmap_mem;
	काष्ठा bna_mem_descr *dqunmap_mem;
	काष्ठा bna_mem_descr *ccb_mem;
	काष्ठा bna_mem_descr *rcb_mem;
	काष्ठा bna_mem_descr *cqpt_mem;
	काष्ठा bna_mem_descr *cswqpt_mem;
	काष्ठा bna_mem_descr *cpage_mem;
	काष्ठा bna_mem_descr *hqpt_mem;
	काष्ठा bna_mem_descr *dqpt_mem;
	काष्ठा bna_mem_descr *hsqpt_mem;
	काष्ठा bna_mem_descr *dsqpt_mem;
	काष्ठा bna_mem_descr *hpage_mem;
	काष्ठा bna_mem_descr *dpage_mem;
	u32 dpage_count, hpage_count;
	u32 hq_idx, dq_idx, rcb_idx;
	u32 cq_depth, i;
	u32 page_count;

	अगर (!bna_rx_res_check(rx_mod, rx_cfg))
		वापस शून्य;

	पूर्णांकr_info = &res_info[BNA_RX_RES_T_INTR].res_u.पूर्णांकr_info;
	ccb_mem = &res_info[BNA_RX_RES_MEM_T_CCB].res_u.mem_info.mdl[0];
	rcb_mem = &res_info[BNA_RX_RES_MEM_T_RCB].res_u.mem_info.mdl[0];
	dqunmap_mem = &res_info[BNA_RX_RES_MEM_T_UNMAPDQ].res_u.mem_info.mdl[0];
	hqunmap_mem = &res_info[BNA_RX_RES_MEM_T_UNMAPHQ].res_u.mem_info.mdl[0];
	cqpt_mem = &res_info[BNA_RX_RES_MEM_T_CQPT].res_u.mem_info.mdl[0];
	cswqpt_mem = &res_info[BNA_RX_RES_MEM_T_CSWQPT].res_u.mem_info.mdl[0];
	cpage_mem = &res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_u.mem_info.mdl[0];
	hqpt_mem = &res_info[BNA_RX_RES_MEM_T_HQPT].res_u.mem_info.mdl[0];
	dqpt_mem = &res_info[BNA_RX_RES_MEM_T_DQPT].res_u.mem_info.mdl[0];
	hsqpt_mem = &res_info[BNA_RX_RES_MEM_T_HSWQPT].res_u.mem_info.mdl[0];
	dsqpt_mem = &res_info[BNA_RX_RES_MEM_T_DSWQPT].res_u.mem_info.mdl[0];
	hpage_mem = &res_info[BNA_RX_RES_MEM_T_HPAGE].res_u.mem_info.mdl[0];
	dpage_mem = &res_info[BNA_RX_RES_MEM_T_DPAGE].res_u.mem_info.mdl[0];

	page_count = res_info[BNA_RX_RES_MEM_T_CQPT_PAGE].res_u.mem_info.len /
			PAGE_SIZE;

	dpage_count = res_info[BNA_RX_RES_MEM_T_DPAGE].res_u.mem_info.len /
			PAGE_SIZE;

	hpage_count = res_info[BNA_RX_RES_MEM_T_HPAGE].res_u.mem_info.len /
			PAGE_SIZE;

	rx = bna_rx_get(rx_mod, rx_cfg->rx_type);
	rx->bna = bna;
	rx->rx_flags = 0;
	INIT_LIST_HEAD(&rx->rxp_q);
	rx->stop_cbfn = शून्य;
	rx->stop_cbarg = शून्य;
	rx->priv = priv;

	rx->rcb_setup_cbfn = rx_cbfn->rcb_setup_cbfn;
	rx->rcb_destroy_cbfn = rx_cbfn->rcb_destroy_cbfn;
	rx->ccb_setup_cbfn = rx_cbfn->ccb_setup_cbfn;
	rx->ccb_destroy_cbfn = rx_cbfn->ccb_destroy_cbfn;
	rx->rx_stall_cbfn = rx_cbfn->rx_stall_cbfn;
	/* Following callbacks are mandatory */
	rx->rx_cleanup_cbfn = rx_cbfn->rx_cleanup_cbfn;
	rx->rx_post_cbfn = rx_cbfn->rx_post_cbfn;

	अगर (rx->bna->rx_mod.flags & BNA_RX_MOD_F_ENET_STARTED) अणु
		चयन (rx->type) अणु
		हाल BNA_RX_T_REGULAR:
			अगर (!(rx->bna->rx_mod.flags &
				BNA_RX_MOD_F_ENET_LOOPBACK))
				rx->rx_flags |= BNA_RX_F_ENET_STARTED;
			अवरोध;
		हाल BNA_RX_T_LOOPBACK:
			अगर (rx->bna->rx_mod.flags & BNA_RX_MOD_F_ENET_LOOPBACK)
				rx->rx_flags |= BNA_RX_F_ENET_STARTED;
			अवरोध;
		पूर्ण
	पूर्ण

	rx->num_paths = rx_cfg->num_paths;
	क्रम (i = 0, hq_idx = 0, dq_idx = 0, rcb_idx = 0;
			i < rx->num_paths; i++) अणु
		rxp = bna_rxp_get(rx_mod);
		list_add_tail(&rxp->qe, &rx->rxp_q);
		rxp->type = rx_cfg->rxp_type;
		rxp->rx = rx;
		rxp->cq.rx = rx;

		q0 = bna_rxq_get(rx_mod);
		अगर (BNA_RXP_SINGLE == rx_cfg->rxp_type)
			q1 = शून्य;
		अन्यथा
			q1 = bna_rxq_get(rx_mod);

		अगर (1 == पूर्णांकr_info->num)
			rxp->vector = पूर्णांकr_info->idl[0].vector;
		अन्यथा
			rxp->vector = पूर्णांकr_info->idl[i].vector;

		/* Setup IB */

		rxp->cq.ib.ib_seg_host_addr.lsb =
		res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].dma.lsb;
		rxp->cq.ib.ib_seg_host_addr.msb =
		res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].dma.msb;
		rxp->cq.ib.ib_seg_host_addr_kva =
		res_info[BNA_RX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].kva;
		rxp->cq.ib.पूर्णांकr_type = पूर्णांकr_info->पूर्णांकr_type;
		अगर (पूर्णांकr_info->पूर्णांकr_type == BNA_INTR_T_MSIX)
			rxp->cq.ib.पूर्णांकr_vector = rxp->vector;
		अन्यथा
			rxp->cq.ib.पूर्णांकr_vector = BIT(rxp->vector);
		rxp->cq.ib.coalescing_समयo = rx_cfg->coalescing_समयo;
		rxp->cq.ib.पूर्णांकerpkt_count = BFI_RX_INTERPKT_COUNT;
		rxp->cq.ib.पूर्णांकerpkt_समयo = BFI_RX_INTERPKT_TIMEO;

		bna_rxp_add_rxqs(rxp, q0, q1);

		/* Setup large Q */

		q0->rx = rx;
		q0->rxp = rxp;

		q0->rcb = (काष्ठा bna_rcb *) rcb_mem[rcb_idx].kva;
		q0->rcb->unmap_q = (व्योम *)dqunmap_mem[dq_idx].kva;
		rcb_idx++; dq_idx++;
		q0->rcb->q_depth = rx_cfg->q0_depth;
		q0->q_depth = rx_cfg->q0_depth;
		q0->multi_buffer = rx_cfg->q0_multi_buf;
		q0->buffer_size = rx_cfg->q0_buf_size;
		q0->num_vecs = rx_cfg->q0_num_vecs;
		q0->rcb->rxq = q0;
		q0->rcb->bnad = bna->bnad;
		q0->rcb->id = 0;
		q0->rx_packets = q0->rx_bytes = 0;
		q0->rx_packets_with_error = q0->rxbuf_alloc_failed = 0;
		q0->rxbuf_map_failed = 0;

		bna_rxq_qpt_setup(q0, rxp, dpage_count, PAGE_SIZE,
			&dqpt_mem[i], &dsqpt_mem[i], &dpage_mem[i]);

		अगर (rx->rcb_setup_cbfn)
			rx->rcb_setup_cbfn(bnad, q0->rcb);

		/* Setup small Q */

		अगर (q1) अणु
			q1->rx = rx;
			q1->rxp = rxp;

			q1->rcb = (काष्ठा bna_rcb *) rcb_mem[rcb_idx].kva;
			q1->rcb->unmap_q = (व्योम *)hqunmap_mem[hq_idx].kva;
			rcb_idx++; hq_idx++;
			q1->rcb->q_depth = rx_cfg->q1_depth;
			q1->q_depth = rx_cfg->q1_depth;
			q1->multi_buffer = BNA_STATUS_T_DISABLED;
			q1->num_vecs = 1;
			q1->rcb->rxq = q1;
			q1->rcb->bnad = bna->bnad;
			q1->rcb->id = 1;
			q1->buffer_size = (rx_cfg->rxp_type == BNA_RXP_HDS) ?
					rx_cfg->hds_config.क्रमced_offset
					: rx_cfg->q1_buf_size;
			q1->rx_packets = q1->rx_bytes = 0;
			q1->rx_packets_with_error = q1->rxbuf_alloc_failed = 0;
			q1->rxbuf_map_failed = 0;

			bna_rxq_qpt_setup(q1, rxp, hpage_count, PAGE_SIZE,
				&hqpt_mem[i], &hsqpt_mem[i],
				&hpage_mem[i]);

			अगर (rx->rcb_setup_cbfn)
				rx->rcb_setup_cbfn(bnad, q1->rcb);
		पूर्ण

		/* Setup CQ */

		rxp->cq.ccb = (काष्ठा bna_ccb *) ccb_mem[i].kva;
		cq_depth = rx_cfg->q0_depth +
			((rx_cfg->rxp_type == BNA_RXP_SINGLE) ?
			 0 : rx_cfg->q1_depth);
		/* अगर multi-buffer is enabled sum of q0_depth
		 * and q1_depth need not be a घातer of 2
		 */
		cq_depth = roundup_घात_of_two(cq_depth);
		rxp->cq.ccb->q_depth = cq_depth;
		rxp->cq.ccb->cq = &rxp->cq;
		rxp->cq.ccb->rcb[0] = q0->rcb;
		q0->rcb->ccb = rxp->cq.ccb;
		अगर (q1) अणु
			rxp->cq.ccb->rcb[1] = q1->rcb;
			q1->rcb->ccb = rxp->cq.ccb;
		पूर्ण
		rxp->cq.ccb->hw_producer_index =
			(u32 *)rxp->cq.ib.ib_seg_host_addr_kva;
		rxp->cq.ccb->i_dbell = &rxp->cq.ib.करोor_bell;
		rxp->cq.ccb->पूर्णांकr_type = rxp->cq.ib.पूर्णांकr_type;
		rxp->cq.ccb->पूर्णांकr_vector = rxp->cq.ib.पूर्णांकr_vector;
		rxp->cq.ccb->rx_coalescing_समयo =
			rxp->cq.ib.coalescing_समयo;
		rxp->cq.ccb->pkt_rate.small_pkt_cnt = 0;
		rxp->cq.ccb->pkt_rate.large_pkt_cnt = 0;
		rxp->cq.ccb->bnad = bna->bnad;
		rxp->cq.ccb->id = i;

		bna_rxp_cqpt_setup(rxp, page_count, PAGE_SIZE,
			&cqpt_mem[i], &cswqpt_mem[i], &cpage_mem[i]);

		अगर (rx->ccb_setup_cbfn)
			rx->ccb_setup_cbfn(bnad, rxp->cq.ccb);
	पूर्ण

	rx->hds_cfg = rx_cfg->hds_config;

	bna_rxf_init(&rx->rxf, rx, rx_cfg, res_info);

	bfa_fsm_set_state(rx, bna_rx_sm_stopped);

	rx_mod->rid_mask |= BIT(rx->rid);

	वापस rx;
पूर्ण

व्योम
bna_rx_destroy(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rx_mod *rx_mod = &rx->bna->rx_mod;
	काष्ठा bna_rxq *q0 = शून्य;
	काष्ठा bna_rxq *q1 = शून्य;
	काष्ठा bna_rxp *rxp;
	काष्ठा list_head *qe;

	bna_rxf_uninit(&rx->rxf);

	जबतक (!list_empty(&rx->rxp_q)) अणु
		rxp = list_first_entry(&rx->rxp_q, काष्ठा bna_rxp, qe);
		list_del(&rxp->qe);
		GET_RXQS(rxp, q0, q1);
		अगर (rx->rcb_destroy_cbfn)
			rx->rcb_destroy_cbfn(rx->bna->bnad, q0->rcb);
		q0->rcb = शून्य;
		q0->rxp = शून्य;
		q0->rx = शून्य;
		bna_rxq_put(rx_mod, q0);

		अगर (q1) अणु
			अगर (rx->rcb_destroy_cbfn)
				rx->rcb_destroy_cbfn(rx->bna->bnad, q1->rcb);
			q1->rcb = शून्य;
			q1->rxp = शून्य;
			q1->rx = शून्य;
			bna_rxq_put(rx_mod, q1);
		पूर्ण
		rxp->rxq.slr.large = शून्य;
		rxp->rxq.slr.small = शून्य;

		अगर (rx->ccb_destroy_cbfn)
			rx->ccb_destroy_cbfn(rx->bna->bnad, rxp->cq.ccb);
		rxp->cq.ccb = शून्य;
		rxp->rx = शून्य;
		bna_rxp_put(rx_mod, rxp);
	पूर्ण

	list_क्रम_each(qe, &rx_mod->rx_active_q)
		अगर (qe == &rx->qe) अणु
			list_del(&rx->qe);
			अवरोध;
		पूर्ण

	rx_mod->rid_mask &= ~BIT(rx->rid);

	rx->bna = शून्य;
	rx->priv = शून्य;
	bna_rx_put(rx_mod, rx);
पूर्ण

व्योम
bna_rx_enable(काष्ठा bna_rx *rx)
अणु
	अगर (rx->fsm != (bfa_sm_t)bna_rx_sm_stopped)
		वापस;

	rx->rx_flags |= BNA_RX_F_ENABLED;
	अगर (rx->rx_flags & BNA_RX_F_ENET_STARTED)
		bfa_fsm_send_event(rx, RX_E_START);
पूर्ण

व्योम
bna_rx_disable(काष्ठा bna_rx *rx, क्रमागत bna_cleanup_type type,
		व्योम (*cbfn)(व्योम *, काष्ठा bna_rx *))
अणु
	अगर (type == BNA_SOFT_CLEANUP) अणु
		/* h/w should not be accessed. Treat we're stopped */
		(*cbfn)(rx->bna->bnad, rx);
	पूर्ण अन्यथा अणु
		rx->stop_cbfn = cbfn;
		rx->stop_cbarg = rx->bna->bnad;

		rx->rx_flags &= ~BNA_RX_F_ENABLED;

		bfa_fsm_send_event(rx, RX_E_STOP);
	पूर्ण
पूर्ण

व्योम
bna_rx_cleanup_complete(काष्ठा bna_rx *rx)
अणु
	bfa_fsm_send_event(rx, RX_E_CLEANUP_DONE);
पूर्ण

व्योम
bna_rx_vlan_strip_enable(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;

	अगर (rxf->vlan_strip_status == BNA_STATUS_T_DISABLED) अणु
		rxf->vlan_strip_status = BNA_STATUS_T_ENABLED;
		rxf->vlan_strip_pending = true;
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	पूर्ण
पूर्ण

व्योम
bna_rx_vlan_strip_disable(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;

	अगर (rxf->vlan_strip_status != BNA_STATUS_T_DISABLED) अणु
		rxf->vlan_strip_status = BNA_STATUS_T_DISABLED;
		rxf->vlan_strip_pending = true;
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	पूर्ण
पूर्ण

क्रमागत bna_cb_status
bna_rx_mode_set(काष्ठा bna_rx *rx, क्रमागत bna_rxmode new_mode,
		क्रमागत bna_rxmode biपंचांगask)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;
	पूर्णांक need_hw_config = 0;

	/* Error checks */

	अगर (is_promisc_enable(new_mode, biपंचांगask)) अणु
		/* If promisc mode is alपढ़ोy enabled अन्यथाwhere in the प्रणाली */
		अगर ((rx->bna->promisc_rid != BFI_INVALID_RID) &&
			(rx->bna->promisc_rid != rxf->rx->rid))
			जाओ err_वापस;

		/* If शेष mode is alपढ़ोy enabled in the प्रणाली */
		अगर (rx->bna->शेष_mode_rid != BFI_INVALID_RID)
			जाओ err_वापस;

		/* Trying to enable promiscuous and शेष mode together */
		अगर (is_शेष_enable(new_mode, biपंचांगask))
			जाओ err_वापस;
	पूर्ण

	अगर (is_शेष_enable(new_mode, biपंचांगask)) अणु
		/* If शेष mode is alपढ़ोy enabled अन्यथाwhere in the प्रणाली */
		अगर ((rx->bna->शेष_mode_rid != BFI_INVALID_RID) &&
			(rx->bna->शेष_mode_rid != rxf->rx->rid)) अणु
				जाओ err_वापस;
		पूर्ण

		/* If promiscuous mode is alपढ़ोy enabled in the प्रणाली */
		अगर (rx->bna->promisc_rid != BFI_INVALID_RID)
			जाओ err_वापस;
	पूर्ण

	/* Process the commands */

	अगर (is_promisc_enable(new_mode, biपंचांगask)) अणु
		अगर (bna_rxf_promisc_enable(rxf))
			need_hw_config = 1;
	पूर्ण अन्यथा अगर (is_promisc_disable(new_mode, biपंचांगask)) अणु
		अगर (bna_rxf_promisc_disable(rxf))
			need_hw_config = 1;
	पूर्ण

	अगर (is_allmulti_enable(new_mode, biपंचांगask)) अणु
		अगर (bna_rxf_allmulti_enable(rxf))
			need_hw_config = 1;
	पूर्ण अन्यथा अगर (is_allmulti_disable(new_mode, biपंचांगask)) अणु
		अगर (bna_rxf_allmulti_disable(rxf))
			need_hw_config = 1;
	पूर्ण

	/* Trigger h/w अगर needed */

	अगर (need_hw_config) अणु
		rxf->cam_fltr_cbfn = शून्य;
		rxf->cam_fltr_cbarg = rx->bna->bnad;
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	पूर्ण

	वापस BNA_CB_SUCCESS;

err_वापस:
	वापस BNA_CB_FAIL;
पूर्ण

व्योम
bna_rx_vlanfilter_enable(काष्ठा bna_rx *rx)
अणु
	काष्ठा bna_rxf *rxf = &rx->rxf;

	अगर (rxf->vlan_filter_status == BNA_STATUS_T_DISABLED) अणु
		rxf->vlan_filter_status = BNA_STATUS_T_ENABLED;
		rxf->vlan_pending_biपंचांगask = (u8)BFI_VLAN_BMASK_ALL;
		bfa_fsm_send_event(rxf, RXF_E_CONFIG);
	पूर्ण
पूर्ण

व्योम
bna_rx_coalescing_समयo_set(काष्ठा bna_rx *rx, पूर्णांक coalescing_समयo)
अणु
	काष्ठा bna_rxp *rxp;

	list_क्रम_each_entry(rxp, &rx->rxp_q, qe) अणु
		rxp->cq.ccb->rx_coalescing_समयo = coalescing_समयo;
		bna_ib_coalescing_समयo_set(&rxp->cq.ib, coalescing_समयo);
	पूर्ण
पूर्ण

व्योम
bna_rx_dim_reconfig(काष्ठा bna *bna, स्थिर u32 vector[][BNA_BIAS_T_MAX])
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < BNA_LOAD_T_MAX; i++)
		क्रम (j = 0; j < BNA_BIAS_T_MAX; j++)
			bna->rx_mod.dim_vector[i][j] = vector[i][j];
पूर्ण

व्योम
bna_rx_dim_update(काष्ठा bna_ccb *ccb)
अणु
	काष्ठा bna *bna = ccb->cq->rx->bna;
	u32 load, bias;
	u32 pkt_rt, small_rt, large_rt;
	u8 coalescing_समयo;

	अगर ((ccb->pkt_rate.small_pkt_cnt == 0) &&
		(ccb->pkt_rate.large_pkt_cnt == 0))
		वापस;

	/* Arrive at preconfigured coalescing समयo value based on pkt rate */

	small_rt = ccb->pkt_rate.small_pkt_cnt;
	large_rt = ccb->pkt_rate.large_pkt_cnt;

	pkt_rt = small_rt + large_rt;

	अगर (pkt_rt < BNA_PKT_RATE_10K)
		load = BNA_LOAD_T_LOW_4;
	अन्यथा अगर (pkt_rt < BNA_PKT_RATE_20K)
		load = BNA_LOAD_T_LOW_3;
	अन्यथा अगर (pkt_rt < BNA_PKT_RATE_30K)
		load = BNA_LOAD_T_LOW_2;
	अन्यथा अगर (pkt_rt < BNA_PKT_RATE_40K)
		load = BNA_LOAD_T_LOW_1;
	अन्यथा अगर (pkt_rt < BNA_PKT_RATE_50K)
		load = BNA_LOAD_T_HIGH_1;
	अन्यथा अगर (pkt_rt < BNA_PKT_RATE_60K)
		load = BNA_LOAD_T_HIGH_2;
	अन्यथा अगर (pkt_rt < BNA_PKT_RATE_80K)
		load = BNA_LOAD_T_HIGH_3;
	अन्यथा
		load = BNA_LOAD_T_HIGH_4;

	अगर (small_rt > (large_rt << 1))
		bias = 0;
	अन्यथा
		bias = 1;

	ccb->pkt_rate.small_pkt_cnt = 0;
	ccb->pkt_rate.large_pkt_cnt = 0;

	coalescing_समयo = bna->rx_mod.dim_vector[load][bias];
	ccb->rx_coalescing_समयo = coalescing_समयo;

	/* Set it to IB */
	bna_ib_coalescing_समयo_set(&ccb->cq->ib, coalescing_समयo);
पूर्ण

स्थिर u32 bna_napi_dim_vector[BNA_LOAD_T_MAX][BNA_BIAS_T_MAX] = अणु
	अणु12, 12पूर्ण,
	अणु6, 10पूर्ण,
	अणु5, 10पूर्ण,
	अणु4, 8पूर्ण,
	अणु3, 6पूर्ण,
	अणु3, 6पूर्ण,
	अणु2, 4पूर्ण,
	अणु1, 2पूर्ण,
पूर्ण;

/* TX */

#घोषणा call_tx_stop_cbfn(tx)						\
करो अणु									\
	अगर ((tx)->stop_cbfn) अणु						\
		व्योम (*cbfn)(व्योम *, काष्ठा bna_tx *);		\
		व्योम *cbarg;						\
		cbfn = (tx)->stop_cbfn;					\
		cbarg = (tx)->stop_cbarg;				\
		(tx)->stop_cbfn = शून्य;					\
		(tx)->stop_cbarg = शून्य;				\
		cbfn(cbarg, (tx));					\
	पूर्ण								\
पूर्ण जबतक (0)

अटल व्योम bna_tx_mod_cb_tx_stopped(व्योम *tx_mod, काष्ठा bna_tx *tx);
अटल व्योम bna_bfi_tx_enet_start(काष्ठा bna_tx *tx);
अटल व्योम bna_tx_enet_stop(काष्ठा bna_tx *tx);

क्रमागत bna_tx_event अणु
	TX_E_START			= 1,
	TX_E_STOP			= 2,
	TX_E_FAIL			= 3,
	TX_E_STARTED			= 4,
	TX_E_STOPPED			= 5,
	TX_E_CLEANUP_DONE		= 7,
	TX_E_BW_UPDATE			= 8,
पूर्ण;

bfa_fsm_state_decl(bna_tx, stopped, काष्ठा bna_tx, क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, start_रुको, काष्ठा bna_tx, क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, started, काष्ठा bna_tx, क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, stop_रुको, काष्ठा bna_tx, क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, cleanup_रुको, काष्ठा bna_tx,
			क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, prio_stop_रुको, काष्ठा bna_tx,
			क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, prio_cleanup_रुको, काष्ठा bna_tx,
			क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, failed, काष्ठा bna_tx, क्रमागत bna_tx_event);
bfa_fsm_state_decl(bna_tx, quiesce_रुको, काष्ठा bna_tx,
			क्रमागत bna_tx_event);

अटल व्योम
bna_tx_sm_stopped_entry(काष्ठा bna_tx *tx)
अणु
	call_tx_stop_cbfn(tx);
पूर्ण

अटल व्योम
bna_tx_sm_stopped(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_START:
		bfa_fsm_set_state(tx, bna_tx_sm_start_रुको);
		अवरोध;

	हाल TX_E_STOP:
		call_tx_stop_cbfn(tx);
		अवरोध;

	हाल TX_E_FAIL:
		/* No-op */
		अवरोध;

	हाल TX_E_BW_UPDATE:
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_start_रुको_entry(काष्ठा bna_tx *tx)
अणु
	bna_bfi_tx_enet_start(tx);
पूर्ण

अटल व्योम
bna_tx_sm_start_रुको(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_STOP:
		tx->flags &= ~BNA_TX_F_BW_UPDATED;
		bfa_fsm_set_state(tx, bna_tx_sm_stop_रुको);
		अवरोध;

	हाल TX_E_FAIL:
		tx->flags &= ~BNA_TX_F_BW_UPDATED;
		bfa_fsm_set_state(tx, bna_tx_sm_stopped);
		अवरोध;

	हाल TX_E_STARTED:
		अगर (tx->flags & BNA_TX_F_BW_UPDATED) अणु
			tx->flags &= ~BNA_TX_F_BW_UPDATED;
			bfa_fsm_set_state(tx, bna_tx_sm_prio_stop_रुको);
		पूर्ण अन्यथा
			bfa_fsm_set_state(tx, bna_tx_sm_started);
		अवरोध;

	हाल TX_E_BW_UPDATE:
		tx->flags |= BNA_TX_F_BW_UPDATED;
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_started_entry(काष्ठा bna_tx *tx)
अणु
	काष्ठा bna_txq *txq;
	पूर्णांक is_regular = (tx->type == BNA_TX_T_REGULAR);

	list_क्रम_each_entry(txq, &tx->txq_q, qe) अणु
		txq->tcb->priority = txq->priority;
		/* Start IB */
		bna_ib_start(tx->bna, &txq->ib, is_regular);
	पूर्ण
	tx->tx_resume_cbfn(tx->bna->bnad, tx);
पूर्ण

अटल व्योम
bna_tx_sm_started(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_stop_रुको);
		tx->tx_stall_cbfn(tx->bna->bnad, tx);
		bna_tx_enet_stop(tx);
		अवरोध;

	हाल TX_E_FAIL:
		bfa_fsm_set_state(tx, bna_tx_sm_failed);
		tx->tx_stall_cbfn(tx->bna->bnad, tx);
		tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
		अवरोध;

	हाल TX_E_BW_UPDATE:
		bfa_fsm_set_state(tx, bna_tx_sm_prio_stop_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_stop_रुको_entry(काष्ठा bna_tx *tx)
अणु
पूर्ण

अटल व्योम
bna_tx_sm_stop_रुको(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_FAIL:
	हाल TX_E_STOPPED:
		bfa_fsm_set_state(tx, bna_tx_sm_cleanup_रुको);
		tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
		अवरोध;

	हाल TX_E_STARTED:
		/**
		 * We are here due to start_रुको -> stop_रुको transition on
		 * TX_E_STOP event
		 */
		bna_tx_enet_stop(tx);
		अवरोध;

	हाल TX_E_BW_UPDATE:
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_cleanup_रुको_entry(काष्ठा bna_tx *tx)
अणु
पूर्ण

अटल व्योम
bna_tx_sm_cleanup_रुको(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_FAIL:
	हाल TX_E_BW_UPDATE:
		/* No-op */
		अवरोध;

	हाल TX_E_CLEANUP_DONE:
		bfa_fsm_set_state(tx, bna_tx_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_prio_stop_रुको_entry(काष्ठा bna_tx *tx)
अणु
	tx->tx_stall_cbfn(tx->bna->bnad, tx);
	bna_tx_enet_stop(tx);
पूर्ण

अटल व्योम
bna_tx_sm_prio_stop_रुको(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_stop_रुको);
		अवरोध;

	हाल TX_E_FAIL:
		bfa_fsm_set_state(tx, bna_tx_sm_failed);
		tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
		अवरोध;

	हाल TX_E_STOPPED:
		bfa_fsm_set_state(tx, bna_tx_sm_prio_cleanup_रुको);
		अवरोध;

	हाल TX_E_BW_UPDATE:
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_prio_cleanup_रुको_entry(काष्ठा bna_tx *tx)
अणु
	tx->tx_cleanup_cbfn(tx->bna->bnad, tx);
पूर्ण

अटल व्योम
bna_tx_sm_prio_cleanup_रुको(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_cleanup_रुको);
		अवरोध;

	हाल TX_E_FAIL:
		bfa_fsm_set_state(tx, bna_tx_sm_failed);
		अवरोध;

	हाल TX_E_BW_UPDATE:
		/* No-op */
		अवरोध;

	हाल TX_E_CLEANUP_DONE:
		bfa_fsm_set_state(tx, bna_tx_sm_start_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_failed_entry(काष्ठा bna_tx *tx)
अणु
पूर्ण

अटल व्योम
bna_tx_sm_failed(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_START:
		bfa_fsm_set_state(tx, bna_tx_sm_quiesce_रुको);
		अवरोध;

	हाल TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_cleanup_रुको);
		अवरोध;

	हाल TX_E_FAIL:
		/* No-op */
		अवरोध;

	हाल TX_E_CLEANUP_DONE:
		bfa_fsm_set_state(tx, bna_tx_sm_stopped);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_tx_sm_quiesce_रुको_entry(काष्ठा bna_tx *tx)
अणु
पूर्ण

अटल व्योम
bna_tx_sm_quiesce_रुको(काष्ठा bna_tx *tx, क्रमागत bna_tx_event event)
अणु
	चयन (event) अणु
	हाल TX_E_STOP:
		bfa_fsm_set_state(tx, bna_tx_sm_cleanup_रुको);
		अवरोध;

	हाल TX_E_FAIL:
		bfa_fsm_set_state(tx, bna_tx_sm_failed);
		अवरोध;

	हाल TX_E_CLEANUP_DONE:
		bfa_fsm_set_state(tx, bna_tx_sm_start_रुको);
		अवरोध;

	हाल TX_E_BW_UPDATE:
		/* No-op */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bna_bfi_tx_enet_start(काष्ठा bna_tx *tx)
अणु
	काष्ठा bfi_enet_tx_cfg_req *cfg_req = &tx->bfi_enet_cmd.cfg_req;
	काष्ठा bna_txq *txq = शून्य;
	पूर्णांक i;

	bfi_msgq_mhdr_set(cfg_req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_TX_CFG_SET_REQ, 0, tx->rid);
	cfg_req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_tx_cfg_req)));

	cfg_req->num_queues = tx->num_txq;
	क्रम (i = 0; i < tx->num_txq; i++) अणु
		txq = txq ? list_next_entry(txq, qe)
			: list_first_entry(&tx->txq_q, काष्ठा bna_txq, qe);
		bfi_enet_datapath_q_init(&cfg_req->q_cfg[i].q.q, &txq->qpt);
		cfg_req->q_cfg[i].q.priority = txq->priority;

		cfg_req->q_cfg[i].ib.index_addr.a32.addr_lo =
			txq->ib.ib_seg_host_addr.lsb;
		cfg_req->q_cfg[i].ib.index_addr.a32.addr_hi =
			txq->ib.ib_seg_host_addr.msb;
		cfg_req->q_cfg[i].ib.पूर्णांकr.msix_index =
			htons((u16)txq->ib.पूर्णांकr_vector);
	पूर्ण

	cfg_req->ib_cfg.पूर्णांक_pkt_dma = BNA_STATUS_T_ENABLED;
	cfg_req->ib_cfg.पूर्णांक_enabled = BNA_STATUS_T_ENABLED;
	cfg_req->ib_cfg.पूर्णांक_pkt_enabled = BNA_STATUS_T_DISABLED;
	cfg_req->ib_cfg.continuous_coalescing = BNA_STATUS_T_ENABLED;
	cfg_req->ib_cfg.msix = (txq->ib.पूर्णांकr_type == BNA_INTR_T_MSIX)
				? BNA_STATUS_T_ENABLED : BNA_STATUS_T_DISABLED;
	cfg_req->ib_cfg.coalescing_समयout =
			htonl((u32)txq->ib.coalescing_समयo);
	cfg_req->ib_cfg.पूर्णांकer_pkt_समयout =
			htonl((u32)txq->ib.पूर्णांकerpkt_समयo);
	cfg_req->ib_cfg.पूर्णांकer_pkt_count = (u8)txq->ib.पूर्णांकerpkt_count;

	cfg_req->tx_cfg.vlan_mode = BFI_ENET_TX_VLAN_WI;
	cfg_req->tx_cfg.vlan_id = htons((u16)tx->txf_vlan_id);
	cfg_req->tx_cfg.admit_tagged_frame = BNA_STATUS_T_ENABLED;
	cfg_req->tx_cfg.apply_vlan_filter = BNA_STATUS_T_DISABLED;

	bfa_msgq_cmd_set(&tx->msgq_cmd, शून्य, शून्य,
		माप(काष्ठा bfi_enet_tx_cfg_req), &cfg_req->mh);
	bfa_msgq_cmd_post(&tx->bna->msgq, &tx->msgq_cmd);
पूर्ण

अटल व्योम
bna_bfi_tx_enet_stop(काष्ठा bna_tx *tx)
अणु
	काष्ठा bfi_enet_req *req = &tx->bfi_enet_cmd.req;

	bfi_msgq_mhdr_set(req->mh, BFI_MC_ENET,
		BFI_ENET_H2I_TX_CFG_CLR_REQ, 0, tx->rid);
	req->mh.num_entries = htons(
		bfi_msgq_num_cmd_entries(माप(काष्ठा bfi_enet_req)));
	bfa_msgq_cmd_set(&tx->msgq_cmd, शून्य, शून्य, माप(काष्ठा bfi_enet_req),
		&req->mh);
	bfa_msgq_cmd_post(&tx->bna->msgq, &tx->msgq_cmd);
पूर्ण

अटल व्योम
bna_tx_enet_stop(काष्ठा bna_tx *tx)
अणु
	काष्ठा bna_txq *txq;

	/* Stop IB */
	list_क्रम_each_entry(txq, &tx->txq_q, qe)
		bna_ib_stop(tx->bna, &txq->ib);

	bna_bfi_tx_enet_stop(tx);
पूर्ण

अटल व्योम
bna_txq_qpt_setup(काष्ठा bna_txq *txq, पूर्णांक page_count, पूर्णांक page_size,
		काष्ठा bna_mem_descr *qpt_mem,
		काष्ठा bna_mem_descr *swqpt_mem,
		काष्ठा bna_mem_descr *page_mem)
अणु
	u8 *kva;
	u64 dma;
	काष्ठा bna_dma_addr bna_dma;
	पूर्णांक i;

	txq->qpt.hw_qpt_ptr.lsb = qpt_mem->dma.lsb;
	txq->qpt.hw_qpt_ptr.msb = qpt_mem->dma.msb;
	txq->qpt.kv_qpt_ptr = qpt_mem->kva;
	txq->qpt.page_count = page_count;
	txq->qpt.page_size = page_size;

	txq->tcb->sw_qpt = (व्योम **) swqpt_mem->kva;
	txq->tcb->sw_q = page_mem->kva;

	kva = page_mem->kva;
	BNA_GET_DMA_ADDR(&page_mem->dma, dma);

	क्रम (i = 0; i < page_count; i++) अणु
		txq->tcb->sw_qpt[i] = kva;
		kva += PAGE_SIZE;

		BNA_SET_DMA_ADDR(dma, &bna_dma);
		((काष्ठा bna_dma_addr *)txq->qpt.kv_qpt_ptr)[i].lsb =
			bna_dma.lsb;
		((काष्ठा bna_dma_addr *)txq->qpt.kv_qpt_ptr)[i].msb =
			bna_dma.msb;
		dma += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल काष्ठा bna_tx *
bna_tx_get(काष्ठा bna_tx_mod *tx_mod, क्रमागत bna_tx_type type)
अणु
	काष्ठा bna_tx *tx = शून्य;

	अगर (list_empty(&tx_mod->tx_मुक्त_q))
		वापस शून्य;
	अगर (type == BNA_TX_T_REGULAR)
		tx = list_first_entry(&tx_mod->tx_मुक्त_q, काष्ठा bna_tx, qe);
	अन्यथा
		tx = list_last_entry(&tx_mod->tx_मुक्त_q, काष्ठा bna_tx, qe);
	list_del(&tx->qe);
	tx->type = type;

	वापस tx;
पूर्ण

अटल व्योम
bna_tx_मुक्त(काष्ठा bna_tx *tx)
अणु
	काष्ठा bna_tx_mod *tx_mod = &tx->bna->tx_mod;
	काष्ठा bna_txq *txq;
	काष्ठा list_head *qe;

	जबतक (!list_empty(&tx->txq_q)) अणु
		txq = list_first_entry(&tx->txq_q, काष्ठा bna_txq, qe);
		txq->tcb = शून्य;
		txq->tx = शून्य;
		list_move_tail(&txq->qe, &tx_mod->txq_मुक्त_q);
	पूर्ण

	list_क्रम_each(qe, &tx_mod->tx_active_q) अणु
		अगर (qe == &tx->qe) अणु
			list_del(&tx->qe);
			अवरोध;
		पूर्ण
	पूर्ण

	tx->bna = शून्य;
	tx->priv = शून्य;

	list_क्रम_each_prev(qe, &tx_mod->tx_मुक्त_q)
		अगर (((काष्ठा bna_tx *)qe)->rid < tx->rid)
			अवरोध;

	list_add(&tx->qe, qe);
पूर्ण

अटल व्योम
bna_tx_start(काष्ठा bna_tx *tx)
अणु
	tx->flags |= BNA_TX_F_ENET_STARTED;
	अगर (tx->flags & BNA_TX_F_ENABLED)
		bfa_fsm_send_event(tx, TX_E_START);
पूर्ण

अटल व्योम
bna_tx_stop(काष्ठा bna_tx *tx)
अणु
	tx->stop_cbfn = bna_tx_mod_cb_tx_stopped;
	tx->stop_cbarg = &tx->bna->tx_mod;

	tx->flags &= ~BNA_TX_F_ENET_STARTED;
	bfa_fsm_send_event(tx, TX_E_STOP);
पूर्ण

अटल व्योम
bna_tx_fail(काष्ठा bna_tx *tx)
अणु
	tx->flags &= ~BNA_TX_F_ENET_STARTED;
	bfa_fsm_send_event(tx, TX_E_FAIL);
पूर्ण

व्योम
bna_bfi_tx_enet_start_rsp(काष्ठा bna_tx *tx, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	काष्ठा bfi_enet_tx_cfg_rsp *cfg_rsp = &tx->bfi_enet_cmd.cfg_rsp;
	काष्ठा bna_txq *txq = शून्य;
	पूर्णांक i;

	bfa_msgq_rsp_copy(&tx->bna->msgq, (u8 *)cfg_rsp,
		माप(काष्ठा bfi_enet_tx_cfg_rsp));

	tx->hw_id = cfg_rsp->hw_id;

	क्रम (i = 0, txq = list_first_entry(&tx->txq_q, काष्ठा bna_txq, qe);
	     i < tx->num_txq; i++, txq = list_next_entry(txq, qe)) अणु
		/* Setup करोorbells */
		txq->tcb->i_dbell->करोorbell_addr =
			tx->bna->pcidev.pci_bar_kva
			+ ntohl(cfg_rsp->q_handles[i].i_dbell);
		txq->tcb->q_dbell =
			tx->bna->pcidev.pci_bar_kva
			+ ntohl(cfg_rsp->q_handles[i].q_dbell);
		txq->hw_id = cfg_rsp->q_handles[i].hw_qid;

		/* Initialize producer/consumer indexes */
		(*txq->tcb->hw_consumer_index) = 0;
		txq->tcb->producer_index = txq->tcb->consumer_index = 0;
	पूर्ण

	bfa_fsm_send_event(tx, TX_E_STARTED);
पूर्ण

व्योम
bna_bfi_tx_enet_stop_rsp(काष्ठा bna_tx *tx, काष्ठा bfi_msgq_mhdr *msghdr)
अणु
	bfa_fsm_send_event(tx, TX_E_STOPPED);
पूर्ण

व्योम
bna_bfi_bw_update_aen(काष्ठा bna_tx_mod *tx_mod)
अणु
	काष्ठा bna_tx *tx;

	list_क्रम_each_entry(tx, &tx_mod->tx_active_q, qe)
		bfa_fsm_send_event(tx, TX_E_BW_UPDATE);
पूर्ण

व्योम
bna_tx_res_req(पूर्णांक num_txq, पूर्णांक txq_depth, काष्ठा bna_res_info *res_info)
अणु
	u32 q_size;
	u32 page_count;
	काष्ठा bna_mem_info *mem_info;

	res_info[BNA_TX_RES_MEM_T_TCB].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_TCB].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = माप(काष्ठा bna_tcb);
	mem_info->num = num_txq;

	q_size = txq_depth * BFI_TXQ_WI_SIZE;
	q_size = ALIGN(q_size, PAGE_SIZE);
	page_count = q_size >> PAGE_SHIFT;

	res_info[BNA_TX_RES_MEM_T_QPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_QPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = page_count * माप(काष्ठा bna_dma_addr);
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_MEM_T_SWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_SWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = page_count * माप(व्योम *);
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_MEM_T_PAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_PAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * page_count;
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_MEM_T_IBIDX].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_IBIDX].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = BFI_IBIDX_SIZE;
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_INTR_T_TXCMPL].res_type = BNA_RES_T_INTR;
	res_info[BNA_TX_RES_INTR_T_TXCMPL].res_u.पूर्णांकr_info.पूर्णांकr_type =
			BNA_INTR_T_MSIX;
	res_info[BNA_TX_RES_INTR_T_TXCMPL].res_u.पूर्णांकr_info.num = num_txq;
पूर्ण

काष्ठा bna_tx *
bna_tx_create(काष्ठा bna *bna, काष्ठा bnad *bnad,
		काष्ठा bna_tx_config *tx_cfg,
		स्थिर काष्ठा bna_tx_event_cbfn *tx_cbfn,
		काष्ठा bna_res_info *res_info, व्योम *priv)
अणु
	काष्ठा bna_पूर्णांकr_info *पूर्णांकr_info;
	काष्ठा bna_tx_mod *tx_mod = &bna->tx_mod;
	काष्ठा bna_tx *tx;
	काष्ठा bna_txq *txq;
	पूर्णांक page_count;
	पूर्णांक i;

	पूर्णांकr_info = &res_info[BNA_TX_RES_INTR_T_TXCMPL].res_u.पूर्णांकr_info;
	page_count = (res_info[BNA_TX_RES_MEM_T_PAGE].res_u.mem_info.len) /
					PAGE_SIZE;

	/**
	 * Get resources
	 */

	अगर ((पूर्णांकr_info->num != 1) && (पूर्णांकr_info->num != tx_cfg->num_txq))
		वापस शून्य;

	/* Tx */

	tx = bna_tx_get(tx_mod, tx_cfg->tx_type);
	अगर (!tx)
		वापस शून्य;
	tx->bna = bna;
	tx->priv = priv;

	/* TxQs */

	INIT_LIST_HEAD(&tx->txq_q);
	क्रम (i = 0; i < tx_cfg->num_txq; i++) अणु
		अगर (list_empty(&tx_mod->txq_मुक्त_q))
			जाओ err_वापस;

		txq = list_first_entry(&tx_mod->txq_मुक्त_q, काष्ठा bna_txq, qe);
		list_move_tail(&txq->qe, &tx->txq_q);
		txq->tx = tx;
	पूर्ण

	/*
	 * Initialize
	 */

	/* Tx */

	tx->tcb_setup_cbfn = tx_cbfn->tcb_setup_cbfn;
	tx->tcb_destroy_cbfn = tx_cbfn->tcb_destroy_cbfn;
	/* Following callbacks are mandatory */
	tx->tx_stall_cbfn = tx_cbfn->tx_stall_cbfn;
	tx->tx_resume_cbfn = tx_cbfn->tx_resume_cbfn;
	tx->tx_cleanup_cbfn = tx_cbfn->tx_cleanup_cbfn;

	list_add_tail(&tx->qe, &tx_mod->tx_active_q);

	tx->num_txq = tx_cfg->num_txq;

	tx->flags = 0;
	अगर (tx->bna->tx_mod.flags & BNA_TX_MOD_F_ENET_STARTED) अणु
		चयन (tx->type) अणु
		हाल BNA_TX_T_REGULAR:
			अगर (!(tx->bna->tx_mod.flags &
				BNA_TX_MOD_F_ENET_LOOPBACK))
				tx->flags |= BNA_TX_F_ENET_STARTED;
			अवरोध;
		हाल BNA_TX_T_LOOPBACK:
			अगर (tx->bna->tx_mod.flags & BNA_TX_MOD_F_ENET_LOOPBACK)
				tx->flags |= BNA_TX_F_ENET_STARTED;
			अवरोध;
		पूर्ण
	पूर्ण

	/* TxQ */

	i = 0;
	list_क्रम_each_entry(txq, &tx->txq_q, qe) अणु
		txq->tcb = (काष्ठा bna_tcb *)
		res_info[BNA_TX_RES_MEM_T_TCB].res_u.mem_info.mdl[i].kva;
		txq->tx_packets = 0;
		txq->tx_bytes = 0;

		/* IB */
		txq->ib.ib_seg_host_addr.lsb =
		res_info[BNA_TX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].dma.lsb;
		txq->ib.ib_seg_host_addr.msb =
		res_info[BNA_TX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].dma.msb;
		txq->ib.ib_seg_host_addr_kva =
		res_info[BNA_TX_RES_MEM_T_IBIDX].res_u.mem_info.mdl[i].kva;
		txq->ib.पूर्णांकr_type = पूर्णांकr_info->पूर्णांकr_type;
		txq->ib.पूर्णांकr_vector = (पूर्णांकr_info->num == 1) ?
					पूर्णांकr_info->idl[0].vector :
					पूर्णांकr_info->idl[i].vector;
		अगर (पूर्णांकr_info->पूर्णांकr_type == BNA_INTR_T_INTX)
			txq->ib.पूर्णांकr_vector = BIT(txq->ib.पूर्णांकr_vector);
		txq->ib.coalescing_समयo = tx_cfg->coalescing_समयo;
		txq->ib.पूर्णांकerpkt_समयo = BFI_TX_INTERPKT_TIMEO;
		txq->ib.पूर्णांकerpkt_count = BFI_TX_INTERPKT_COUNT;

		/* TCB */

		txq->tcb->q_depth = tx_cfg->txq_depth;
		txq->tcb->unmap_q = (व्योम *)
		res_info[BNA_TX_RES_MEM_T_UNMAPQ].res_u.mem_info.mdl[i].kva;
		txq->tcb->hw_consumer_index =
			(u32 *)txq->ib.ib_seg_host_addr_kva;
		txq->tcb->i_dbell = &txq->ib.करोor_bell;
		txq->tcb->पूर्णांकr_type = txq->ib.पूर्णांकr_type;
		txq->tcb->पूर्णांकr_vector = txq->ib.पूर्णांकr_vector;
		txq->tcb->txq = txq;
		txq->tcb->bnad = bnad;
		txq->tcb->id = i;

		/* QPT, SWQPT, Pages */
		bna_txq_qpt_setup(txq, page_count, PAGE_SIZE,
			&res_info[BNA_TX_RES_MEM_T_QPT].res_u.mem_info.mdl[i],
			&res_info[BNA_TX_RES_MEM_T_SWQPT].res_u.mem_info.mdl[i],
			&res_info[BNA_TX_RES_MEM_T_PAGE].
				  res_u.mem_info.mdl[i]);

		/* Callback to bnad क्रम setting up TCB */
		अगर (tx->tcb_setup_cbfn)
			(tx->tcb_setup_cbfn)(bna->bnad, txq->tcb);

		अगर (tx_cfg->num_txq == BFI_TX_MAX_PRIO)
			txq->priority = txq->tcb->id;
		अन्यथा
			txq->priority = tx_mod->शेष_prio;

		i++;
	पूर्ण

	tx->txf_vlan_id = 0;

	bfa_fsm_set_state(tx, bna_tx_sm_stopped);

	tx_mod->rid_mask |= BIT(tx->rid);

	वापस tx;

err_वापस:
	bna_tx_मुक्त(tx);
	वापस शून्य;
पूर्ण

व्योम
bna_tx_destroy(काष्ठा bna_tx *tx)
अणु
	काष्ठा bna_txq *txq;

	list_क्रम_each_entry(txq, &tx->txq_q, qe)
		अगर (tx->tcb_destroy_cbfn)
			(tx->tcb_destroy_cbfn)(tx->bna->bnad, txq->tcb);

	tx->bna->tx_mod.rid_mask &= ~BIT(tx->rid);
	bna_tx_मुक्त(tx);
पूर्ण

व्योम
bna_tx_enable(काष्ठा bna_tx *tx)
अणु
	अगर (tx->fsm != (bfa_sm_t)bna_tx_sm_stopped)
		वापस;

	tx->flags |= BNA_TX_F_ENABLED;

	अगर (tx->flags & BNA_TX_F_ENET_STARTED)
		bfa_fsm_send_event(tx, TX_E_START);
पूर्ण

व्योम
bna_tx_disable(काष्ठा bna_tx *tx, क्रमागत bna_cleanup_type type,
		व्योम (*cbfn)(व्योम *, काष्ठा bna_tx *))
अणु
	अगर (type == BNA_SOFT_CLEANUP) अणु
		(*cbfn)(tx->bna->bnad, tx);
		वापस;
	पूर्ण

	tx->stop_cbfn = cbfn;
	tx->stop_cbarg = tx->bna->bnad;

	tx->flags &= ~BNA_TX_F_ENABLED;

	bfa_fsm_send_event(tx, TX_E_STOP);
पूर्ण

व्योम
bna_tx_cleanup_complete(काष्ठा bna_tx *tx)
अणु
	bfa_fsm_send_event(tx, TX_E_CLEANUP_DONE);
पूर्ण

अटल व्योम
bna_tx_mod_cb_tx_stopped(व्योम *arg, काष्ठा bna_tx *tx)
अणु
	काष्ठा bna_tx_mod *tx_mod = (काष्ठा bna_tx_mod *)arg;

	bfa_wc_करोwn(&tx_mod->tx_stop_wc);
पूर्ण

अटल व्योम
bna_tx_mod_cb_tx_stopped_all(व्योम *arg)
अणु
	काष्ठा bna_tx_mod *tx_mod = (काष्ठा bna_tx_mod *)arg;

	अगर (tx_mod->stop_cbfn)
		tx_mod->stop_cbfn(&tx_mod->bna->enet);
	tx_mod->stop_cbfn = शून्य;
पूर्ण

व्योम
bna_tx_mod_init(काष्ठा bna_tx_mod *tx_mod, काष्ठा bna *bna,
		काष्ठा bna_res_info *res_info)
अणु
	पूर्णांक i;

	tx_mod->bna = bna;
	tx_mod->flags = 0;

	tx_mod->tx = (काष्ठा bna_tx *)
		res_info[BNA_MOD_RES_MEM_T_TX_ARRAY].res_u.mem_info.mdl[0].kva;
	tx_mod->txq = (काष्ठा bna_txq *)
		res_info[BNA_MOD_RES_MEM_T_TXQ_ARRAY].res_u.mem_info.mdl[0].kva;

	INIT_LIST_HEAD(&tx_mod->tx_मुक्त_q);
	INIT_LIST_HEAD(&tx_mod->tx_active_q);

	INIT_LIST_HEAD(&tx_mod->txq_मुक्त_q);

	क्रम (i = 0; i < bna->ioceth.attr.num_txq; i++) अणु
		tx_mod->tx[i].rid = i;
		list_add_tail(&tx_mod->tx[i].qe, &tx_mod->tx_मुक्त_q);
		list_add_tail(&tx_mod->txq[i].qe, &tx_mod->txq_मुक्त_q);
	पूर्ण

	tx_mod->prio_map = BFI_TX_PRIO_MAP_ALL;
	tx_mod->शेष_prio = 0;
	tx_mod->iscsi_over_cee = BNA_STATUS_T_DISABLED;
	tx_mod->iscsi_prio = -1;
पूर्ण

व्योम
bna_tx_mod_uninit(काष्ठा bna_tx_mod *tx_mod)
अणु
	tx_mod->bna = शून्य;
पूर्ण

व्योम
bna_tx_mod_start(काष्ठा bna_tx_mod *tx_mod, क्रमागत bna_tx_type type)
अणु
	काष्ठा bna_tx *tx;

	tx_mod->flags |= BNA_TX_MOD_F_ENET_STARTED;
	अगर (type == BNA_TX_T_LOOPBACK)
		tx_mod->flags |= BNA_TX_MOD_F_ENET_LOOPBACK;

	list_क्रम_each_entry(tx, &tx_mod->tx_active_q, qe)
		अगर (tx->type == type)
			bna_tx_start(tx);
पूर्ण

व्योम
bna_tx_mod_stop(काष्ठा bna_tx_mod *tx_mod, क्रमागत bna_tx_type type)
अणु
	काष्ठा bna_tx *tx;

	tx_mod->flags &= ~BNA_TX_MOD_F_ENET_STARTED;
	tx_mod->flags &= ~BNA_TX_MOD_F_ENET_LOOPBACK;

	tx_mod->stop_cbfn = bna_enet_cb_tx_stopped;

	bfa_wc_init(&tx_mod->tx_stop_wc, bna_tx_mod_cb_tx_stopped_all, tx_mod);

	list_क्रम_each_entry(tx, &tx_mod->tx_active_q, qe)
		अगर (tx->type == type) अणु
			bfa_wc_up(&tx_mod->tx_stop_wc);
			bna_tx_stop(tx);
		पूर्ण

	bfa_wc_रुको(&tx_mod->tx_stop_wc);
पूर्ण

व्योम
bna_tx_mod_fail(काष्ठा bna_tx_mod *tx_mod)
अणु
	काष्ठा bna_tx *tx;

	tx_mod->flags &= ~BNA_TX_MOD_F_ENET_STARTED;
	tx_mod->flags &= ~BNA_TX_MOD_F_ENET_LOOPBACK;

	list_क्रम_each_entry(tx, &tx_mod->tx_active_q, qe)
		bna_tx_fail(tx);
पूर्ण

व्योम
bna_tx_coalescing_समयo_set(काष्ठा bna_tx *tx, पूर्णांक coalescing_समयo)
अणु
	काष्ठा bna_txq *txq;

	list_क्रम_each_entry(txq, &tx->txq_q, qe)
		bna_ib_coalescing_समयo_set(&txq->ib, coalescing_समयo);
पूर्ण
