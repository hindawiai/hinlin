<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chelsio Communications, Inc.
 */

#घोषणा DRV_NAME "cxgbit"
#घोषणा DRV_VERSION "1.0.0-ko"
#घोषणा pr_fmt(fmt) DRV_NAME ": " fmt

#समावेश "cxgbit.h"

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
#समावेश <net/dcbevent.h>
#समावेश "cxgb4_dcb.h"
#पूर्ण_अगर

LIST_HEAD(cdev_list_head);
/* cdev list lock */
DEFINE_MUTEX(cdev_list_lock);

व्योम _cxgbit_मुक्त_cdev(काष्ठा kref *kref)
अणु
	काष्ठा cxgbit_device *cdev;

	cdev = container_of(kref, काष्ठा cxgbit_device, kref);

	cxgbi_ppm_release(cdev2ppm(cdev));
	kमुक्त(cdev);
पूर्ण

अटल व्योम cxgbit_set_mdsl(काष्ठा cxgbit_device *cdev)
अणु
	काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;
	u32 mdsl;

#घोषणा ULP2_MAX_PKT_LEN 16224
#घोषणा ISCSI_PDU_NONPAYLOAD_LEN 312
	mdsl = min_t(u32, lldi->iscsi_iolen - ISCSI_PDU_NONPAYLOAD_LEN,
		     ULP2_MAX_PKT_LEN - ISCSI_PDU_NONPAYLOAD_LEN);
	mdsl = min_t(u32, mdsl, 8192);
	mdsl = min_t(u32, mdsl, (MAX_SKB_FRAGS - 1) * PAGE_SIZE);

	cdev->mdsl = mdsl;
पूर्ण

अटल व्योम *cxgbit_uld_add(स्थिर काष्ठा cxgb4_lld_info *lldi)
अणु
	काष्ठा cxgbit_device *cdev;

	अगर (is_t4(lldi->adapter_type))
		वापस ERR_PTR(-ENODEV);

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&cdev->kref);
	spin_lock_init(&cdev->np_lock);

	cdev->lldi = *lldi;

	cxgbit_set_mdsl(cdev);

	अगर (cxgbit_ddp_init(cdev) < 0) अणु
		kमुक्त(cdev);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!test_bit(CDEV_DDP_ENABLE, &cdev->flags))
		pr_info("cdev %s ddp init failed\n",
			pci_name(lldi->pdev));

	अगर (lldi->fw_vers >= 0x10d2b00)
		set_bit(CDEV_ISO_ENABLE, &cdev->flags);

	spin_lock_init(&cdev->cskq.lock);
	INIT_LIST_HEAD(&cdev->cskq.list);

	mutex_lock(&cdev_list_lock);
	list_add_tail(&cdev->list, &cdev_list_head);
	mutex_unlock(&cdev_list_lock);

	pr_info("cdev %s added for iSCSI target transport\n",
		pci_name(lldi->pdev));

	वापस cdev;
पूर्ण

अटल व्योम cxgbit_बंद_conn(काष्ठा cxgbit_device *cdev)
अणु
	काष्ठा cxgbit_sock *csk;
	काष्ठा sk_buff *skb;
	bool wakeup_thपढ़ो = false;

	spin_lock_bh(&cdev->cskq.lock);
	list_क्रम_each_entry(csk, &cdev->cskq.list, list) अणु
		skb = alloc_skb(0, GFP_ATOMIC);
		अगर (!skb)
			जारी;

		spin_lock_bh(&csk->rxq.lock);
		__skb_queue_tail(&csk->rxq, skb);
		अगर (skb_queue_len(&csk->rxq) == 1)
			wakeup_thपढ़ो = true;
		spin_unlock_bh(&csk->rxq.lock);

		अगर (wakeup_thपढ़ो) अणु
			wake_up(&csk->रुकोq);
			wakeup_thपढ़ो = false;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cdev->cskq.lock);
पूर्ण

अटल व्योम cxgbit_detach_cdev(काष्ठा cxgbit_device *cdev)
अणु
	bool मुक्त_cdev = false;

	spin_lock_bh(&cdev->cskq.lock);
	अगर (list_empty(&cdev->cskq.list))
		मुक्त_cdev = true;
	spin_unlock_bh(&cdev->cskq.lock);

	अगर (मुक्त_cdev) अणु
		mutex_lock(&cdev_list_lock);
		list_del(&cdev->list);
		mutex_unlock(&cdev_list_lock);

		cxgbit_put_cdev(cdev);
	पूर्ण अन्यथा अणु
		cxgbit_बंद_conn(cdev);
	पूर्ण
पूर्ण

अटल पूर्णांक cxgbit_uld_state_change(व्योम *handle, क्रमागत cxgb4_state state)
अणु
	काष्ठा cxgbit_device *cdev = handle;

	चयन (state) अणु
	हाल CXGB4_STATE_UP:
		set_bit(CDEV_STATE_UP, &cdev->flags);
		pr_info("cdev %s state UP.\n", pci_name(cdev->lldi.pdev));
		अवरोध;
	हाल CXGB4_STATE_START_RECOVERY:
		clear_bit(CDEV_STATE_UP, &cdev->flags);
		cxgbit_बंद_conn(cdev);
		pr_info("cdev %s state RECOVERY.\n", pci_name(cdev->lldi.pdev));
		अवरोध;
	हाल CXGB4_STATE_DOWN:
		pr_info("cdev %s state DOWN.\n", pci_name(cdev->lldi.pdev));
		अवरोध;
	हाल CXGB4_STATE_DETACH:
		clear_bit(CDEV_STATE_UP, &cdev->flags);
		pr_info("cdev %s state DETACH.\n", pci_name(cdev->lldi.pdev));
		cxgbit_detach_cdev(cdev);
		अवरोध;
	शेष:
		pr_info("cdev %s unknown state %d.\n",
			pci_name(cdev->lldi.pdev), state);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
cxgbit_process_ddpvld(काष्ठा cxgbit_sock *csk, काष्ठा cxgbit_lro_pdu_cb *pdu_cb,
		      u32 ddpvld)
अणु

	अगर (ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_HCRC_SHIFT)) अणु
		pr_info("tid 0x%x, status 0x%x, hcrc bad.\n", csk->tid, ddpvld);
		pdu_cb->flags |= PDUCBF_RX_HCRC_ERR;
	पूर्ण

	अगर (ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_DCRC_SHIFT)) अणु
		pr_info("tid 0x%x, status 0x%x, dcrc bad.\n", csk->tid, ddpvld);
		pdu_cb->flags |= PDUCBF_RX_DCRC_ERR;
	पूर्ण

	अगर (ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_PAD_SHIFT))
		pr_info("tid 0x%x, status 0x%x, pad bad.\n", csk->tid, ddpvld);

	अगर ((ddpvld & (1 << CPL_RX_ISCSI_DDP_STATUS_DDP_SHIFT)) &&
	    (!(pdu_cb->flags & PDUCBF_RX_DATA))) अणु
		pdu_cb->flags |= PDUCBF_RX_DATA_DDPD;
	पूर्ण
पूर्ण

अटल व्योम
cxgbit_lro_add_packet_rsp(काष्ठा sk_buff *skb, u8 op, स्थिर __be64 *rsp)
अणु
	काष्ठा cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb,
						lro_cb->pdu_idx);
	काष्ठा cpl_rx_iscsi_ddp *cpl = (काष्ठा cpl_rx_iscsi_ddp *)(rsp + 1);

	cxgbit_process_ddpvld(lro_cb->csk, pdu_cb, be32_to_cpu(cpl->ddpvld));

	pdu_cb->flags |= PDUCBF_RX_STATUS;
	pdu_cb->ddigest = ntohl(cpl->ulp_crc);
	pdu_cb->pdulen = ntohs(cpl->len);

	अगर (pdu_cb->flags & PDUCBF_RX_HDR)
		pdu_cb->complete = true;

	lro_cb->pdu_totallen += pdu_cb->pdulen;
	lro_cb->complete = true;
	lro_cb->pdu_idx++;
पूर्ण

अटल व्योम
cxgbit_copy_frags(काष्ठा sk_buff *skb, स्थिर काष्ठा pkt_gl *gl,
		  अचिन्हित पूर्णांक offset)
अणु
	u8 skb_frag_idx = skb_shinfo(skb)->nr_frags;
	u8 i;

	/* usually there's just one frag */
	__skb_fill_page_desc(skb, skb_frag_idx, gl->frags[0].page,
			     gl->frags[0].offset + offset,
			     gl->frags[0].size - offset);
	क्रम (i = 1; i < gl->nfrags; i++)
		__skb_fill_page_desc(skb, skb_frag_idx + i,
				     gl->frags[i].page,
				     gl->frags[i].offset,
				     gl->frags[i].size);

	skb_shinfo(skb)->nr_frags += gl->nfrags;

	/* get a reference to the last page, we करोn't own it */
	get_page(gl->frags[gl->nfrags - 1].page);
पूर्ण

अटल व्योम
cxgbit_lro_add_packet_gl(काष्ठा sk_buff *skb, u8 op, स्थिर काष्ठा pkt_gl *gl)
अणु
	काष्ठा cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb,
						lro_cb->pdu_idx);
	u32 len, offset;

	अगर (op == CPL_ISCSI_HDR) अणु
		काष्ठा cpl_iscsi_hdr *cpl = (काष्ठा cpl_iscsi_hdr *)gl->va;

		offset = माप(काष्ठा cpl_iscsi_hdr);
		pdu_cb->flags |= PDUCBF_RX_HDR;
		pdu_cb->seq = ntohl(cpl->seq);
		len = ntohs(cpl->len);
		pdu_cb->hdr = gl->va + offset;
		pdu_cb->hlen = len;
		pdu_cb->hfrag_idx = skb_shinfo(skb)->nr_frags;

		अगर (unlikely(gl->nfrags > 1))
			cxgbit_skcb_flags(skb) = 0;

		lro_cb->complete = false;
	पूर्ण अन्यथा अगर (op == CPL_ISCSI_DATA) अणु
		काष्ठा cpl_iscsi_data *cpl = (काष्ठा cpl_iscsi_data *)gl->va;

		offset = माप(काष्ठा cpl_iscsi_data);
		pdu_cb->flags |= PDUCBF_RX_DATA;
		len = ntohs(cpl->len);
		pdu_cb->dlen = len;
		pdu_cb->करोffset = lro_cb->offset;
		pdu_cb->nr_dfrags = gl->nfrags;
		pdu_cb->dfrag_idx = skb_shinfo(skb)->nr_frags;
		lro_cb->complete = false;
	पूर्ण अन्यथा अणु
		काष्ठा cpl_rx_iscsi_cmp *cpl;

		cpl = (काष्ठा cpl_rx_iscsi_cmp *)gl->va;
		offset = माप(काष्ठा cpl_rx_iscsi_cmp);
		pdu_cb->flags |= (PDUCBF_RX_HDR | PDUCBF_RX_STATUS);
		len = be16_to_cpu(cpl->len);
		pdu_cb->hdr = gl->va + offset;
		pdu_cb->hlen = len;
		pdu_cb->hfrag_idx = skb_shinfo(skb)->nr_frags;
		pdu_cb->ddigest = be32_to_cpu(cpl->ulp_crc);
		pdu_cb->pdulen = ntohs(cpl->len);

		अगर (unlikely(gl->nfrags > 1))
			cxgbit_skcb_flags(skb) = 0;

		cxgbit_process_ddpvld(lro_cb->csk, pdu_cb,
				      be32_to_cpu(cpl->ddpvld));

		अगर (pdu_cb->flags & PDUCBF_RX_DATA_DDPD) अणु
			pdu_cb->flags |= PDUCBF_RX_DDP_CMP;
			pdu_cb->complete = true;
		पूर्ण अन्यथा अगर (pdu_cb->flags & PDUCBF_RX_DATA) अणु
			pdu_cb->complete = true;
		पूर्ण

		lro_cb->pdu_totallen += pdu_cb->hlen + pdu_cb->dlen;
		lro_cb->complete = true;
		lro_cb->pdu_idx++;
	पूर्ण

	cxgbit_copy_frags(skb, gl, offset);

	pdu_cb->frags += gl->nfrags;
	lro_cb->offset += len;
	skb->len += len;
	skb->data_len += len;
	skb->truesize += len;
पूर्ण

अटल काष्ठा sk_buff *
cxgbit_lro_init_skb(काष्ठा cxgbit_sock *csk, u8 op, स्थिर काष्ठा pkt_gl *gl,
		    स्थिर __be64 *rsp, काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cxgbit_lro_cb *lro_cb;

	skb = napi_alloc_skb(napi, LRO_SKB_MAX_HEADROOM);

	अगर (unlikely(!skb))
		वापस शून्य;

	स_रखो(skb->data, 0, LRO_SKB_MAX_HEADROOM);

	cxgbit_skcb_flags(skb) |= SKCBF_RX_LRO;

	lro_cb = cxgbit_skb_lro_cb(skb);

	cxgbit_get_csk(csk);

	lro_cb->csk = csk;

	वापस skb;
पूर्ण

अटल व्योम cxgbit_queue_lro_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	bool wakeup_thपढ़ो = false;

	spin_lock(&csk->rxq.lock);
	__skb_queue_tail(&csk->rxq, skb);
	अगर (skb_queue_len(&csk->rxq) == 1)
		wakeup_thपढ़ो = true;
	spin_unlock(&csk->rxq.lock);

	अगर (wakeup_thपढ़ो)
		wake_up(&csk->रुकोq);
पूर्ण

अटल व्योम cxgbit_lro_flush(काष्ठा t4_lro_mgr *lro_mgr, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	काष्ठा cxgbit_sock *csk = lro_cb->csk;

	csk->lro_skb = शून्य;

	__skb_unlink(skb, &lro_mgr->lroq);
	cxgbit_queue_lro_skb(csk, skb);

	cxgbit_put_csk(csk);

	lro_mgr->lro_pkts++;
	lro_mgr->lro_session_cnt--;
पूर्ण

अटल व्योम cxgbit_uld_lro_flush(काष्ठा t4_lro_mgr *lro_mgr)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_peek(&lro_mgr->lroq)))
		cxgbit_lro_flush(lro_mgr, skb);
पूर्ण

अटल पूर्णांक
cxgbit_lro_receive(काष्ठा cxgbit_sock *csk, u8 op, स्थिर __be64 *rsp,
		   स्थिर काष्ठा pkt_gl *gl, काष्ठा t4_lro_mgr *lro_mgr,
		   काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cxgbit_lro_cb *lro_cb;

	अगर (!csk) अणु
		pr_err("%s: csk NULL, op 0x%x.\n", __func__, op);
		जाओ out;
	पूर्ण

	अगर (csk->lro_skb)
		जाओ add_packet;

start_lro:
	अगर (lro_mgr->lro_session_cnt >= MAX_LRO_SESSIONS) अणु
		cxgbit_uld_lro_flush(lro_mgr);
		जाओ start_lro;
	पूर्ण

	skb = cxgbit_lro_init_skb(csk, op, gl, rsp, napi);
	अगर (unlikely(!skb))
		जाओ out;

	csk->lro_skb = skb;

	__skb_queue_tail(&lro_mgr->lroq, skb);
	lro_mgr->lro_session_cnt++;

add_packet:
	skb = csk->lro_skb;
	lro_cb = cxgbit_skb_lro_cb(skb);

	अगर ((gl && (((skb_shinfo(skb)->nr_frags + gl->nfrags) >
	    MAX_SKB_FRAGS) || (lro_cb->pdu_totallen >= LRO_FLUSH_LEN_MAX))) ||
	    (lro_cb->pdu_idx >= MAX_SKB_FRAGS)) अणु
		cxgbit_lro_flush(lro_mgr, skb);
		जाओ start_lro;
	पूर्ण

	अगर (gl)
		cxgbit_lro_add_packet_gl(skb, op, gl);
	अन्यथा
		cxgbit_lro_add_packet_rsp(skb, op, rsp);

	lro_mgr->lro_merged++;

	वापस 0;

out:
	वापस -1;
पूर्ण

अटल पूर्णांक
cxgbit_uld_lro_rx_handler(व्योम *hndl, स्थिर __be64 *rsp,
			  स्थिर काष्ठा pkt_gl *gl, काष्ठा t4_lro_mgr *lro_mgr,
			  काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा cxgbit_device *cdev = hndl;
	काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;
	काष्ठा cpl_tx_data *rpl = शून्य;
	काष्ठा cxgbit_sock *csk = शून्य;
	अचिन्हित पूर्णांक tid = 0;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक op = *(u8 *)rsp;
	bool lro_flush = true;

	चयन (op) अणु
	हाल CPL_ISCSI_HDR:
	हाल CPL_ISCSI_DATA:
	हाल CPL_RX_ISCSI_CMP:
	हाल CPL_RX_ISCSI_DDP:
	हाल CPL_FW4_ACK:
		lro_flush = false;
		fallthrough;
	हाल CPL_ABORT_RPL_RSS:
	हाल CPL_PASS_ESTABLISH:
	हाल CPL_PEER_CLOSE:
	हाल CPL_CLOSE_CON_RPL:
	हाल CPL_ABORT_REQ_RSS:
	हाल CPL_SET_TCB_RPL:
	हाल CPL_RX_DATA:
		rpl = gl ? (काष्ठा cpl_tx_data *)gl->va :
			   (काष्ठा cpl_tx_data *)(rsp + 1);
		tid = GET_TID(rpl);
		csk = lookup_tid(lldi->tids, tid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (csk && csk->lro_skb && lro_flush)
		cxgbit_lro_flush(lro_mgr, csk->lro_skb);

	अगर (!gl) अणु
		अचिन्हित पूर्णांक len;

		अगर (op == CPL_RX_ISCSI_DDP) अणु
			अगर (!cxgbit_lro_receive(csk, op, rsp, शून्य, lro_mgr,
						napi))
				वापस 0;
		पूर्ण

		len = 64 - माप(काष्ठा rsp_ctrl) - 8;
		skb = napi_alloc_skb(napi, len);
		अगर (!skb)
			जाओ nomem;
		__skb_put(skb, len);
		skb_copy_to_linear_data(skb, &rsp[1], len);
	पूर्ण अन्यथा अणु
		अगर (unlikely(op != *(u8 *)gl->va)) अणु
			pr_info("? FL 0x%p,RSS%#llx,FL %#llx,len %u.\n",
				gl->va, be64_to_cpu(*rsp),
				get_unaligned_be64(gl->va),
				gl->tot_len);
			वापस 0;
		पूर्ण

		अगर ((op == CPL_ISCSI_HDR) || (op == CPL_ISCSI_DATA) ||
		    (op == CPL_RX_ISCSI_CMP)) अणु
			अगर (!cxgbit_lro_receive(csk, op, rsp, gl, lro_mgr,
						napi))
				वापस 0;
		पूर्ण

#घोषणा RX_PULL_LEN 128
		skb = cxgb4_pktgl_to_skb(gl, RX_PULL_LEN, RX_PULL_LEN);
		अगर (unlikely(!skb))
			जाओ nomem;
	पूर्ण

	rpl = (काष्ठा cpl_tx_data *)skb->data;
	op = rpl->ot.opcode;
	cxgbit_skcb_rx_opcode(skb) = op;

	pr_debug("cdev %p, opcode 0x%x(0x%x,0x%x), skb %p.\n",
		 cdev, op, rpl->ot.opcode_tid,
		 ntohl(rpl->ot.opcode_tid), skb);

	अगर (op < NUM_CPL_CMDS && cxgbit_cplhandlers[op]) अणु
		cxgbit_cplhandlers[op](cdev, skb);
	पूर्ण अन्यथा अणु
		pr_err("No handler for opcode 0x%x.\n", op);
		__kमुक्त_skb(skb);
	पूर्ण
	वापस 0;
nomem:
	pr_err("%s OOM bailing out.\n", __func__);
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
काष्ठा cxgbit_dcb_work अणु
	काष्ठा dcb_app_type dcb_app;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम
cxgbit_update_dcb_priority(काष्ठा cxgbit_device *cdev, u8 port_id,
			   u8 dcb_priority, u16 port_num)
अणु
	काष्ठा cxgbit_sock *csk;
	काष्ठा sk_buff *skb;
	u16 local_port;
	bool wakeup_thपढ़ो = false;

	spin_lock_bh(&cdev->cskq.lock);
	list_क्रम_each_entry(csk, &cdev->cskq.list, list) अणु
		अगर (csk->port_id != port_id)
			जारी;

		अगर (csk->com.local_addr.ss_family == AF_INET6) अणु
			काष्ठा sockaddr_in6 *sock_in6;

			sock_in6 = (काष्ठा sockaddr_in6 *)&csk->com.local_addr;
			local_port = ntohs(sock_in6->sin6_port);
		पूर्ण अन्यथा अणु
			काष्ठा sockaddr_in *sock_in;

			sock_in = (काष्ठा sockaddr_in *)&csk->com.local_addr;
			local_port = ntohs(sock_in->sin_port);
		पूर्ण

		अगर (local_port != port_num)
			जारी;

		अगर (csk->dcb_priority == dcb_priority)
			जारी;

		skb = alloc_skb(0, GFP_ATOMIC);
		अगर (!skb)
			जारी;

		spin_lock(&csk->rxq.lock);
		__skb_queue_tail(&csk->rxq, skb);
		अगर (skb_queue_len(&csk->rxq) == 1)
			wakeup_thपढ़ो = true;
		spin_unlock(&csk->rxq.lock);

		अगर (wakeup_thपढ़ो) अणु
			wake_up(&csk->रुकोq);
			wakeup_thपढ़ो = false;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cdev->cskq.lock);
पूर्ण

अटल व्योम cxgbit_dcb_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cxgbit_dcb_work *dcb_work;
	काष्ठा net_device *ndev;
	काष्ठा cxgbit_device *cdev = शून्य;
	काष्ठा dcb_app_type *iscsi_app;
	u8 priority, port_id = 0xff;

	dcb_work = container_of(work, काष्ठा cxgbit_dcb_work, work);
	iscsi_app = &dcb_work->dcb_app;

	अगर (iscsi_app->dcbx & DCB_CAP_DCBX_VER_IEEE) अणु
		अगर ((iscsi_app->app.selector != IEEE_8021QAZ_APP_SEL_STREAM) &&
		    (iscsi_app->app.selector != IEEE_8021QAZ_APP_SEL_ANY))
			जाओ out;

		priority = iscsi_app->app.priority;

	पूर्ण अन्यथा अगर (iscsi_app->dcbx & DCB_CAP_DCBX_VER_CEE) अणु
		अगर (iscsi_app->app.selector != DCB_APP_IDTYPE_PORTNUM)
			जाओ out;

		अगर (!iscsi_app->app.priority)
			जाओ out;

		priority = ffs(iscsi_app->app.priority) - 1;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	pr_debug("priority for ifid %d is %u\n",
		 iscsi_app->अगरindex, priority);

	ndev = dev_get_by_index(&init_net, iscsi_app->अगरindex);

	अगर (!ndev)
		जाओ out;

	mutex_lock(&cdev_list_lock);
	cdev = cxgbit_find_device(ndev, &port_id);

	dev_put(ndev);

	अगर (!cdev) अणु
		mutex_unlock(&cdev_list_lock);
		जाओ out;
	पूर्ण

	cxgbit_update_dcb_priority(cdev, port_id, priority,
				   iscsi_app->app.protocol);
	mutex_unlock(&cdev_list_lock);
out:
	kमुक्त(dcb_work);
पूर्ण

अटल पूर्णांक
cxgbit_dcbevent_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
		       व्योम *data)
अणु
	काष्ठा cxgbit_dcb_work *dcb_work;
	काष्ठा dcb_app_type *dcb_app = data;

	dcb_work = kzalloc(माप(*dcb_work), GFP_ATOMIC);
	अगर (!dcb_work)
		वापस NOTIFY_DONE;

	dcb_work->dcb_app = *dcb_app;
	INIT_WORK(&dcb_work->work, cxgbit_dcb_workfn);
	schedule_work(&dcb_work->work);
	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

अटल क्रमागत target_prot_op cxgbit_get_sup_prot_ops(काष्ठा iscsi_conn *conn)
अणु
	वापस TARGET_PROT_NORMAL;
पूर्ण

अटल काष्ठा iscsit_transport cxgbit_transport = अणु
	.name			= DRV_NAME,
	.transport_type		= ISCSI_CXGBIT,
	.rdma_shutकरोwn		= false,
	.priv_size		= माप(काष्ठा cxgbit_cmd),
	.owner			= THIS_MODULE,
	.iscsit_setup_np	= cxgbit_setup_np,
	.iscsit_accept_np	= cxgbit_accept_np,
	.iscsit_मुक्त_np		= cxgbit_मुक्त_np,
	.iscsit_मुक्त_conn	= cxgbit_मुक्त_conn,
	.iscsit_get_login_rx	= cxgbit_get_login_rx,
	.iscsit_put_login_tx	= cxgbit_put_login_tx,
	.iscsit_immediate_queue	= iscsit_immediate_queue,
	.iscsit_response_queue	= iscsit_response_queue,
	.iscsit_get_dataout	= iscsit_build_r2ts_क्रम_cmd,
	.iscsit_queue_data_in	= iscsit_queue_rsp,
	.iscsit_queue_status	= iscsit_queue_rsp,
	.iscsit_xmit_pdu	= cxgbit_xmit_pdu,
	.iscsit_get_r2t_ttt	= cxgbit_get_r2t_ttt,
	.iscsit_get_rx_pdu	= cxgbit_get_rx_pdu,
	.iscsit_validate_params	= cxgbit_validate_params,
	.iscsit_unmap_cmd	= cxgbit_unmap_cmd,
	.iscsit_पातed_task	= iscsit_पातed_task,
	.iscsit_get_sup_prot_ops = cxgbit_get_sup_prot_ops,
पूर्ण;

अटल काष्ठा cxgb4_uld_info cxgbit_uld_info = अणु
	.name		= DRV_NAME,
	.nrxq		= MAX_ULD_QSETS,
	.ntxq		= MAX_ULD_QSETS,
	.rxq_size	= 1024,
	.lro		= true,
	.add		= cxgbit_uld_add,
	.state_change	= cxgbit_uld_state_change,
	.lro_rx_handler = cxgbit_uld_lro_rx_handler,
	.lro_flush	= cxgbit_uld_lro_flush,
पूर्ण;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
अटल काष्ठा notअगरier_block cxgbit_dcbevent_nb = अणु
	.notअगरier_call = cxgbit_dcbevent_notअगरy,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init cxgbit_init(व्योम)
अणु
	cxgb4_रेजिस्टर_uld(CXGB4_ULD_ISCSIT, &cxgbit_uld_info);
	iscsit_रेजिस्टर_transport(&cxgbit_transport);

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	pr_info("%s dcb enabled.\n", DRV_NAME);
	रेजिस्टर_dcbevent_notअगरier(&cxgbit_dcbevent_nb);
#पूर्ण_अगर
	BUILD_BUG_ON(माप_field(काष्ठा sk_buff, cb) <
		     माप(जोड़ cxgbit_skb_cb));
	वापस 0;
पूर्ण

अटल व्योम __निकास cxgbit_निकास(व्योम)
अणु
	काष्ठा cxgbit_device *cdev, *पंचांगp;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB
	unरेजिस्टर_dcbevent_notअगरier(&cxgbit_dcbevent_nb);
#पूर्ण_अगर
	mutex_lock(&cdev_list_lock);
	list_क्रम_each_entry_safe(cdev, पंचांगp, &cdev_list_head, list) अणु
		list_del(&cdev->list);
		cxgbit_put_cdev(cdev);
	पूर्ण
	mutex_unlock(&cdev_list_lock);
	iscsit_unरेजिस्टर_transport(&cxgbit_transport);
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_ISCSIT);
पूर्ण

module_init(cxgbit_init);
module_निकास(cxgbit_निकास);

MODULE_DESCRIPTION("Chelsio iSCSI target offload driver");
MODULE_AUTHOR("Chelsio Communications");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
