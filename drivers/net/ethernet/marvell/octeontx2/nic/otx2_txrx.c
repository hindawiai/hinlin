<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/etherdevice.h>
#समावेश <net/ip.h>
#समावेश <net/tso.h>

#समावेश "otx2_reg.h"
#समावेश "otx2_common.h"
#समावेश "otx2_struct.h"
#समावेश "otx2_txrx.h"
#समावेश "otx2_ptp.h"
#समावेश "cn10k.h"

#घोषणा CQE_ADDR(CQ, idx) ((CQ)->cqe_base + ((CQ)->cqe_size * (idx)))

अटल काष्ठा nix_cqe_hdr_s *otx2_get_next_cqe(काष्ठा otx2_cq_queue *cq)
अणु
	काष्ठा nix_cqe_hdr_s *cqe_hdr;

	cqe_hdr = (काष्ठा nix_cqe_hdr_s *)CQE_ADDR(cq, cq->cq_head);
	अगर (cqe_hdr->cqe_type == NIX_XQE_TYPE_INVALID)
		वापस शून्य;

	cq->cq_head++;
	cq->cq_head &= (cq->cqe_cnt - 1);

	वापस cqe_hdr;
पूर्ण

अटल अचिन्हित पूर्णांक frag_num(अचिन्हित पूर्णांक i)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस (i & ~3) + 3 - (i & 3);
#अन्यथा
	वापस i;
#पूर्ण_अगर
पूर्ण

अटल dma_addr_t otx2_dma_map_skb_frag(काष्ठा otx2_nic *pfvf,
					काष्ठा sk_buff *skb, पूर्णांक seg, पूर्णांक *len)
अणु
	स्थिर skb_frag_t *frag;
	काष्ठा page *page;
	पूर्णांक offset;

	/* First segment is always skb->data */
	अगर (!seg) अणु
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		*len = skb_headlen(skb);
	पूर्ण अन्यथा अणु
		frag = &skb_shinfo(skb)->frags[seg - 1];
		page = skb_frag_page(frag);
		offset = skb_frag_off(frag);
		*len = skb_frag_size(frag);
	पूर्ण
	वापस otx2_dma_map_page(pfvf, page, offset, *len, DMA_TO_DEVICE);
पूर्ण

अटल व्योम otx2_dma_unmap_skb_frags(काष्ठा otx2_nic *pfvf, काष्ठा sg_list *sg)
अणु
	पूर्णांक seg;

	क्रम (seg = 0; seg < sg->num_segs; seg++) अणु
		otx2_dma_unmap_page(pfvf, sg->dma_addr[seg],
				    sg->size[seg], DMA_TO_DEVICE);
	पूर्ण
	sg->num_segs = 0;
पूर्ण

अटल व्योम otx2_snd_pkt_handler(काष्ठा otx2_nic *pfvf,
				 काष्ठा otx2_cq_queue *cq,
				 काष्ठा otx2_snd_queue *sq,
				 काष्ठा nix_cqe_tx_s *cqe,
				 पूर्णांक budget, पूर्णांक *tx_pkts, पूर्णांक *tx_bytes)
अणु
	काष्ठा nix_send_comp_s *snd_comp = &cqe->comp;
	काष्ठा skb_shared_hwtstamps ts;
	काष्ठा sk_buff *skb = शून्य;
	u64 बारtamp, tsns;
	काष्ठा sg_list *sg;
	पूर्णांक err;

	अगर (unlikely(snd_comp->status) && netअगर_msg_tx_err(pfvf))
		net_err_ratelimited("%s: TX%d: Error in send CQ status:%x\n",
				    pfvf->netdev->name, cq->cपूर्णांक_idx,
				    snd_comp->status);

	sg = &sq->sg[snd_comp->sqe_id];
	skb = (काष्ठा sk_buff *)sg->skb;
	अगर (unlikely(!skb))
		वापस;

	अगर (skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS) अणु
		बारtamp = ((u64 *)sq->बारtamps->base)[snd_comp->sqe_id];
		अगर (बारtamp != 1) अणु
			err = otx2_ptp_tstamp2समय(pfvf, बारtamp, &tsns);
			अगर (!err) अणु
				स_रखो(&ts, 0, माप(ts));
				ts.hwtstamp = ns_to_kसमय(tsns);
				skb_tstamp_tx(skb, &ts);
			पूर्ण
		पूर्ण
	पूर्ण

	*tx_bytes += skb->len;
	(*tx_pkts)++;
	otx2_dma_unmap_skb_frags(pfvf, sg);
	napi_consume_skb(skb, budget);
	sg->skb = (u64)शून्य;
पूर्ण

अटल व्योम otx2_set_rxtstamp(काष्ठा otx2_nic *pfvf,
			      काष्ठा sk_buff *skb, व्योम *data)
अणु
	u64 tsns;
	पूर्णांक err;

	अगर (!(pfvf->flags & OTX2_FLAG_RX_TSTAMP_ENABLED))
		वापस;

	/* The first 8 bytes is the बारtamp */
	err = otx2_ptp_tstamp2समय(pfvf, be64_to_cpu(*(__be64 *)data), &tsns);
	अगर (err)
		वापस;

	skb_hwtstamps(skb)->hwtstamp = ns_to_kसमय(tsns);
पूर्ण

अटल व्योम otx2_skb_add_frag(काष्ठा otx2_nic *pfvf, काष्ठा sk_buff *skb,
			      u64 iova, पूर्णांक len, काष्ठा nix_rx_parse_s *parse)
अणु
	काष्ठा page *page;
	पूर्णांक off = 0;
	व्योम *va;

	va = phys_to_virt(otx2_iova_to_phys(pfvf->iommu_करोमुख्य, iova));

	अगर (likely(!skb_shinfo(skb)->nr_frags)) अणु
		/* Check अगर data starts at some nonzero offset
		 * from the start of the buffer.  For now the
		 * only possible offset is 8 bytes in the हाल
		 * where packet is prepended by a बारtamp.
		 */
		अगर (parse->laptr) अणु
			otx2_set_rxtstamp(pfvf, skb, va);
			off = OTX2_HW_TIMESTAMP_LEN;
		पूर्ण
	पूर्ण

	page = virt_to_page(va);
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
			va - page_address(page) + off, len - off, pfvf->rbsize);

	otx2_dma_unmap_page(pfvf, iova - OTX2_HEAD_ROOM,
			    pfvf->rbsize, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम otx2_set_rxhash(काष्ठा otx2_nic *pfvf,
			    काष्ठा nix_cqe_rx_s *cqe, काष्ठा sk_buff *skb)
अणु
	क्रमागत pkt_hash_types hash_type = PKT_HASH_TYPE_NONE;
	काष्ठा otx2_rss_info *rss;
	u32 hash = 0;

	अगर (!(pfvf->netdev->features & NETIF_F_RXHASH))
		वापस;

	rss = &pfvf->hw.rss_info;
	अगर (rss->flowkey_cfg) अणु
		अगर (rss->flowkey_cfg &
		    ~(NIX_FLOW_KEY_TYPE_IPV4 | NIX_FLOW_KEY_TYPE_IPV6))
			hash_type = PKT_HASH_TYPE_L4;
		अन्यथा
			hash_type = PKT_HASH_TYPE_L3;
		hash = cqe->hdr.flow_tag;
	पूर्ण
	skb_set_hash(skb, hash, hash_type);
पूर्ण

अटल व्योम otx2_मुक्त_rcv_seg(काष्ठा otx2_nic *pfvf, काष्ठा nix_cqe_rx_s *cqe,
			      पूर्णांक qidx)
अणु
	काष्ठा nix_rx_sg_s *sg = &cqe->sg;
	व्योम *end, *start;
	u64 *seg_addr;
	पूर्णांक seg;

	start = (व्योम *)sg;
	end = start + ((cqe->parse.desc_sizem1 + 1) * 16);
	जबतक (start < end) अणु
		sg = (काष्ठा nix_rx_sg_s *)start;
		seg_addr = &sg->seg_addr;
		क्रम (seg = 0; seg < sg->segs; seg++, seg_addr++)
			pfvf->hw_ops->aura_मुक्तptr(pfvf, qidx,
						   *seg_addr & ~0x07ULL);
		start += माप(*sg);
	पूर्ण
पूर्ण

अटल bool otx2_check_rcv_errors(काष्ठा otx2_nic *pfvf,
				  काष्ठा nix_cqe_rx_s *cqe, पूर्णांक qidx)
अणु
	काष्ठा otx2_drv_stats *stats = &pfvf->hw.drv_stats;
	काष्ठा nix_rx_parse_s *parse = &cqe->parse;

	अगर (netअगर_msg_rx_err(pfvf))
		netdev_err(pfvf->netdev,
			   "RQ%d: Error pkt with errlev:0x%x errcode:0x%x\n",
			   qidx, parse->errlev, parse->errcode);

	अगर (parse->errlev == NPC_ERRLVL_RE) अणु
		चयन (parse->errcode) अणु
		हाल ERRCODE_FCS:
		हाल ERRCODE_FCS_RCV:
			atomic_inc(&stats->rx_fcs_errs);
			अवरोध;
		हाल ERRCODE_UNDERSIZE:
			atomic_inc(&stats->rx_undersize_errs);
			अवरोध;
		हाल ERRCODE_OVERSIZE:
			atomic_inc(&stats->rx_oversize_errs);
			अवरोध;
		हाल ERRCODE_OL2_LEN_MISMATCH:
			atomic_inc(&stats->rx_len_errs);
			अवरोध;
		शेष:
			atomic_inc(&stats->rx_other_errs);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (parse->errlev == NPC_ERRLVL_NIX) अणु
		चयन (parse->errcode) अणु
		हाल ERRCODE_OL3_LEN:
		हाल ERRCODE_OL4_LEN:
		हाल ERRCODE_IL3_LEN:
		हाल ERRCODE_IL4_LEN:
			atomic_inc(&stats->rx_len_errs);
			अवरोध;
		हाल ERRCODE_OL4_CSUM:
		हाल ERRCODE_IL4_CSUM:
			atomic_inc(&stats->rx_csum_errs);
			अवरोध;
		शेष:
			atomic_inc(&stats->rx_other_errs);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		atomic_inc(&stats->rx_other_errs);
		/* For now ignore all the NPC parser errors and
		 * pass the packets to stack.
		 */
		वापस false;
	पूर्ण

	/* If RXALL is enabled pass on packets to stack. */
	अगर (pfvf->netdev->features & NETIF_F_RXALL)
		वापस false;

	/* Free buffer back to pool */
	अगर (cqe->sg.segs)
		otx2_मुक्त_rcv_seg(pfvf, cqe, qidx);
	वापस true;
पूर्ण

अटल व्योम otx2_rcv_pkt_handler(काष्ठा otx2_nic *pfvf,
				 काष्ठा napi_काष्ठा *napi,
				 काष्ठा otx2_cq_queue *cq,
				 काष्ठा nix_cqe_rx_s *cqe)
अणु
	काष्ठा nix_rx_parse_s *parse = &cqe->parse;
	काष्ठा nix_rx_sg_s *sg = &cqe->sg;
	काष्ठा sk_buff *skb = शून्य;
	व्योम *end, *start;
	u64 *seg_addr;
	u16 *seg_size;
	पूर्णांक seg;

	अगर (unlikely(parse->errlev || parse->errcode)) अणु
		अगर (otx2_check_rcv_errors(pfvf, cqe, cq->cq_idx))
			वापस;
	पूर्ण

	skb = napi_get_frags(napi);
	अगर (unlikely(!skb))
		वापस;

	start = (व्योम *)sg;
	end = start + ((cqe->parse.desc_sizem1 + 1) * 16);
	जबतक (start < end) अणु
		sg = (काष्ठा nix_rx_sg_s *)start;
		seg_addr = &sg->seg_addr;
		seg_size = (व्योम *)sg;
		क्रम (seg = 0; seg < sg->segs; seg++, seg_addr++) अणु
			otx2_skb_add_frag(pfvf, skb, *seg_addr, seg_size[seg],
					  parse);
			cq->pool_ptrs++;
		पूर्ण
		start += माप(*sg);
	पूर्ण
	otx2_set_rxhash(pfvf, cqe, skb);

	skb_record_rx_queue(skb, cq->cq_idx);
	अगर (pfvf->netdev->features & NETIF_F_RXCSUM)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	napi_gro_frags(napi);
पूर्ण

अटल पूर्णांक otx2_rx_napi_handler(काष्ठा otx2_nic *pfvf,
				काष्ठा napi_काष्ठा *napi,
				काष्ठा otx2_cq_queue *cq, पूर्णांक budget)
अणु
	काष्ठा nix_cqe_rx_s *cqe;
	पूर्णांक processed_cqe = 0;

	जबतक (likely(processed_cqe < budget)) अणु
		cqe = (काष्ठा nix_cqe_rx_s *)CQE_ADDR(cq, cq->cq_head);
		अगर (cqe->hdr.cqe_type == NIX_XQE_TYPE_INVALID ||
		    !cqe->sg.seg_addr) अणु
			अगर (!processed_cqe)
				वापस 0;
			अवरोध;
		पूर्ण
		cq->cq_head++;
		cq->cq_head &= (cq->cqe_cnt - 1);

		otx2_rcv_pkt_handler(pfvf, napi, cq, cqe);

		cqe->hdr.cqe_type = NIX_XQE_TYPE_INVALID;
		cqe->sg.seg_addr = 0x00;
		processed_cqe++;
	पूर्ण

	/* Free CQEs to HW */
	otx2_ग_लिखो64(pfvf, NIX_LF_CQ_OP_DOOR,
		     ((u64)cq->cq_idx << 32) | processed_cqe);

	अगर (unlikely(!cq->pool_ptrs))
		वापस 0;
	/* Refill pool with new buffers */
	pfvf->hw_ops->refill_pool_ptrs(pfvf, cq);

	वापस processed_cqe;
पूर्ण

व्योम otx2_refill_pool_ptrs(व्योम *dev, काष्ठा otx2_cq_queue *cq)
अणु
	काष्ठा otx2_nic *pfvf = dev;
	dma_addr_t bufptr;

	जबतक (cq->pool_ptrs) अणु
		अगर (otx2_alloc_buffer(pfvf, cq, &bufptr))
			अवरोध;
		otx2_aura_मुक्तptr(pfvf, cq->cq_idx, bufptr + OTX2_HEAD_ROOM);
		cq->pool_ptrs--;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_tx_napi_handler(काष्ठा otx2_nic *pfvf,
				काष्ठा otx2_cq_queue *cq, पूर्णांक budget)
अणु
	पूर्णांक tx_pkts = 0, tx_bytes = 0;
	काष्ठा nix_cqe_tx_s *cqe;
	पूर्णांक processed_cqe = 0;

	जबतक (likely(processed_cqe < budget)) अणु
		cqe = (काष्ठा nix_cqe_tx_s *)otx2_get_next_cqe(cq);
		अगर (unlikely(!cqe)) अणु
			अगर (!processed_cqe)
				वापस 0;
			अवरोध;
		पूर्ण
		otx2_snd_pkt_handler(pfvf, cq, &pfvf->qset.sq[cq->cपूर्णांक_idx],
				     cqe, budget, &tx_pkts, &tx_bytes);

		cqe->hdr.cqe_type = NIX_XQE_TYPE_INVALID;
		processed_cqe++;
	पूर्ण

	/* Free CQEs to HW */
	otx2_ग_लिखो64(pfvf, NIX_LF_CQ_OP_DOOR,
		     ((u64)cq->cq_idx << 32) | processed_cqe);

	अगर (likely(tx_pkts)) अणु
		काष्ठा netdev_queue *txq;

		txq = netdev_get_tx_queue(pfvf->netdev, cq->cपूर्णांक_idx);
		netdev_tx_completed_queue(txq, tx_pkts, tx_bytes);
		/* Check अगर queue was stopped earlier due to ring full */
		smp_mb();
		अगर (netअगर_tx_queue_stopped(txq) &&
		    netअगर_carrier_ok(pfvf->netdev))
			netअगर_tx_wake_queue(txq);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक otx2_napi_handler(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा otx2_cq_poll *cq_poll;
	पूर्णांक workकरोne = 0, cq_idx, i;
	काष्ठा otx2_cq_queue *cq;
	काष्ठा otx2_qset *qset;
	काष्ठा otx2_nic *pfvf;

	cq_poll = container_of(napi, काष्ठा otx2_cq_poll, napi);
	pfvf = (काष्ठा otx2_nic *)cq_poll->dev;
	qset = &pfvf->qset;

	क्रम (i = CQS_PER_CINT - 1; i >= 0; i--) अणु
		cq_idx = cq_poll->cq_ids[i];
		अगर (unlikely(cq_idx == CINT_INVALID_CQ))
			जारी;
		cq = &qset->cq[cq_idx];
		अगर (cq->cq_type == CQ_RX) अणु
			/* If the RQ refill WQ task is running, skip napi
			 * scheduler क्रम this queue.
			 */
			अगर (cq->refill_task_sched)
				जारी;
			workकरोne += otx2_rx_napi_handler(pfvf, napi,
							 cq, budget);
		पूर्ण अन्यथा अणु
			workकरोne += otx2_tx_napi_handler(pfvf, cq, budget);
		पूर्ण
	पूर्ण

	/* Clear the IRQ */
	otx2_ग_लिखो64(pfvf, NIX_LF_CINTX_INT(cq_poll->cपूर्णांक_idx), BIT_ULL(0));

	अगर (workकरोne < budget && napi_complete_करोne(napi, workकरोne)) अणु
		/* If पूर्णांकerface is going करोwn, करोn't re-enable IRQ */
		अगर (pfvf->flags & OTX2_FLAG_INTF_DOWN)
			वापस workकरोne;

		/* Re-enable पूर्णांकerrupts */
		otx2_ग_लिखो64(pfvf, NIX_LF_CINTX_ENA_W1S(cq_poll->cपूर्णांक_idx),
			     BIT_ULL(0));
	पूर्ण
	वापस workकरोne;
पूर्ण

व्योम otx2_sqe_flush(व्योम *dev, काष्ठा otx2_snd_queue *sq,
		    पूर्णांक size, पूर्णांक qidx)
अणु
	u64 status;

	/* Packet data stores should finish beक्रमe SQE is flushed to HW */
	dma_wmb();

	करो अणु
		स_नकल(sq->lmt_addr, sq->sqe_base, size);
		status = otx2_lmt_flush(sq->io_addr);
	पूर्ण जबतक (status == 0);

	sq->head++;
	sq->head &= (sq->sqe_cnt - 1);
पूर्ण

#घोषणा MAX_SEGS_PER_SG	3
/* Add SQE scatter/gather subdescriptor काष्ठाure */
अटल bool otx2_sqe_add_sg(काष्ठा otx2_nic *pfvf, काष्ठा otx2_snd_queue *sq,
			    काष्ठा sk_buff *skb, पूर्णांक num_segs, पूर्णांक *offset)
अणु
	काष्ठा nix_sqe_sg_s *sg = शून्य;
	u64 dma_addr, *iova = शून्य;
	u16 *sg_lens = शून्य;
	पूर्णांक seg, len;

	sq->sg[sq->head].num_segs = 0;

	क्रम (seg = 0; seg < num_segs; seg++) अणु
		अगर ((seg % MAX_SEGS_PER_SG) == 0) अणु
			sg = (काष्ठा nix_sqe_sg_s *)(sq->sqe_base + *offset);
			sg->ld_type = NIX_SEND_LDTYPE_LDD;
			sg->subdc = NIX_SUBDC_SG;
			sg->segs = 0;
			sg_lens = (व्योम *)sg;
			iova = (व्योम *)sg + माप(*sg);
			/* Next subdc always starts at a 16byte boundary.
			 * So अगर sg->segs is whether 2 or 3, offset += 16bytes.
			 */
			अगर ((num_segs - seg) >= (MAX_SEGS_PER_SG - 1))
				*offset += माप(*sg) + (3 * माप(u64));
			अन्यथा
				*offset += माप(*sg) + माप(u64);
		पूर्ण
		dma_addr = otx2_dma_map_skb_frag(pfvf, skb, seg, &len);
		अगर (dma_mapping_error(pfvf->dev, dma_addr))
			वापस false;

		sg_lens[frag_num(seg % MAX_SEGS_PER_SG)] = len;
		sg->segs++;
		*iova++ = dma_addr;

		/* Save DMA mapping info क्रम later unmapping */
		sq->sg[sq->head].dma_addr[seg] = dma_addr;
		sq->sg[sq->head].size[seg] = len;
		sq->sg[sq->head].num_segs++;
	पूर्ण

	sq->sg[sq->head].skb = (u64)skb;
	वापस true;
पूर्ण

/* Add SQE extended header subdescriptor */
अटल व्योम otx2_sqe_add_ext(काष्ठा otx2_nic *pfvf, काष्ठा otx2_snd_queue *sq,
			     काष्ठा sk_buff *skb, पूर्णांक *offset)
अणु
	काष्ठा nix_sqe_ext_s *ext;

	ext = (काष्ठा nix_sqe_ext_s *)(sq->sqe_base + *offset);
	ext->subdc = NIX_SUBDC_EXT;
	अगर (skb_shinfo(skb)->gso_size) अणु
		ext->lso = 1;
		ext->lso_sb = skb_transport_offset(skb) + tcp_hdrlen(skb);
		ext->lso_mps = skb_shinfo(skb)->gso_size;

		/* Only TSOv4 and TSOv6 GSO offloads are supported */
		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4) अणु
			ext->lso_क्रमmat = pfvf->hw.lso_tsov4_idx;

			/* HW adds payload size to 'ip_hdr->tot_len' जबतक
			 * sending TSO segment, hence set payload length
			 * in IP header of the packet to just header length.
			 */
			ip_hdr(skb)->tot_len =
				htons(ext->lso_sb - skb_network_offset(skb));
		पूर्ण अन्यथा अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) अणु
			ext->lso_क्रमmat = pfvf->hw.lso_tsov6_idx;

			ipv6_hdr(skb)->payload_len =
				htons(ext->lso_sb - skb_network_offset(skb));
		पूर्ण अन्यथा अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
			__be16 l3_proto = vlan_get_protocol(skb);
			काष्ठा udphdr *udph = udp_hdr(skb);
			u16 iplen;

			ext->lso_sb = skb_transport_offset(skb) +
					माप(काष्ठा udphdr);

			/* HW adds payload size to length fields in IP and
			 * UDP headers जबतक segmentation, hence adjust the
			 * lengths to just header sizes.
			 */
			iplen = htons(ext->lso_sb - skb_network_offset(skb));
			अगर (l3_proto == htons(ETH_P_IP)) अणु
				ip_hdr(skb)->tot_len = iplen;
				ext->lso_क्रमmat = pfvf->hw.lso_udpv4_idx;
			पूर्ण अन्यथा अणु
				ipv6_hdr(skb)->payload_len = iplen;
				ext->lso_क्रमmat = pfvf->hw.lso_udpv6_idx;
			पूर्ण

			udph->len = htons(माप(काष्ठा udphdr));
		पूर्ण
	पूर्ण अन्यथा अगर (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) अणु
		ext->tsपंचांगp = 1;
	पूर्ण

#घोषणा OTX2_VLAN_PTR_OFFSET     (ETH_HLEN - ETH_TLEN)
	अगर (skb_vlan_tag_present(skb)) अणु
		अगर (skb->vlan_proto == htons(ETH_P_8021Q)) अणु
			ext->vlan1_ins_ena = 1;
			ext->vlan1_ins_ptr = OTX2_VLAN_PTR_OFFSET;
			ext->vlan1_ins_tci = skb_vlan_tag_get(skb);
		पूर्ण अन्यथा अगर (skb->vlan_proto == htons(ETH_P_8021AD)) अणु
			ext->vlan0_ins_ena = 1;
			ext->vlan0_ins_ptr = OTX2_VLAN_PTR_OFFSET;
			ext->vlan0_ins_tci = skb_vlan_tag_get(skb);
		पूर्ण
	पूर्ण

	*offset += माप(*ext);
पूर्ण

अटल व्योम otx2_sqe_add_mem(काष्ठा otx2_snd_queue *sq, पूर्णांक *offset,
			     पूर्णांक alg, u64 iova)
अणु
	काष्ठा nix_sqe_mem_s *mem;

	mem = (काष्ठा nix_sqe_mem_s *)(sq->sqe_base + *offset);
	mem->subdc = NIX_SUBDC_MEM;
	mem->alg = alg;
	mem->wmem = 1; /* रुको क्रम the memory operation */
	mem->addr = iova;

	*offset += माप(*mem);
पूर्ण

/* Add SQE header subdescriptor काष्ठाure */
अटल व्योम otx2_sqe_add_hdr(काष्ठा otx2_nic *pfvf, काष्ठा otx2_snd_queue *sq,
			     काष्ठा nix_sqe_hdr_s *sqe_hdr,
			     काष्ठा sk_buff *skb, u16 qidx)
अणु
	पूर्णांक proto = 0;

	/* Check अगर SQE was framed beक्रमe, अगर yes then no need to
	 * set these स्थिरants again and again.
	 */
	अगर (!sqe_hdr->total) अणु
		/* Don't मुक्त Tx buffers to Aura */
		sqe_hdr->df = 1;
		sqe_hdr->aura = sq->aura_id;
		/* Post a CQE Tx after pkt transmission */
		sqe_hdr->pnc = 1;
		sqe_hdr->sq = qidx;
	पूर्ण
	sqe_hdr->total = skb->len;
	/* Set SQE identअगरier which will be used later क्रम मुक्तing SKB */
	sqe_hdr->sqe_id = sq->head;

	/* Offload TCP/UDP checksum to HW */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		sqe_hdr->ol3ptr = skb_network_offset(skb);
		sqe_hdr->ol4ptr = skb_transport_offset(skb);
		/* get vlan protocol Ethertype */
		अगर (eth_type_vlan(skb->protocol))
			skb->protocol = vlan_get_protocol(skb);

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			proto = ip_hdr(skb)->protocol;
			/* In हाल of TSO, HW needs this to be explicitly set.
			 * So set this always, instead of adding a check.
			 */
			sqe_hdr->ol3type = NIX_SENDL3TYPE_IP4_CKSUM;
		पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			proto = ipv6_hdr(skb)->nexthdr;
			sqe_hdr->ol3type = NIX_SENDL3TYPE_IP6;
		पूर्ण

		अगर (proto == IPPROTO_TCP)
			sqe_hdr->ol4type = NIX_SENDL4TYPE_TCP_CKSUM;
		अन्यथा अगर (proto == IPPROTO_UDP)
			sqe_hdr->ol4type = NIX_SENDL4TYPE_UDP_CKSUM;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_dma_map_tso_skb(काष्ठा otx2_nic *pfvf,
				काष्ठा otx2_snd_queue *sq,
				काष्ठा sk_buff *skb, पूर्णांक sqe, पूर्णांक hdr_len)
अणु
	पूर्णांक num_segs = skb_shinfo(skb)->nr_frags + 1;
	काष्ठा sg_list *sg = &sq->sg[sqe];
	u64 dma_addr;
	पूर्णांक seg, len;

	sg->num_segs = 0;

	/* Get payload length at skb->data */
	len = skb_headlen(skb) - hdr_len;

	क्रम (seg = 0; seg < num_segs; seg++) अणु
		/* Skip skb->data, अगर there is no payload */
		अगर (!seg && !len)
			जारी;
		dma_addr = otx2_dma_map_skb_frag(pfvf, skb, seg, &len);
		अगर (dma_mapping_error(pfvf->dev, dma_addr))
			जाओ unmap;

		/* Save DMA mapping info क्रम later unmapping */
		sg->dma_addr[sg->num_segs] = dma_addr;
		sg->size[sg->num_segs] = len;
		sg->num_segs++;
	पूर्ण
	वापस 0;
unmap:
	otx2_dma_unmap_skb_frags(pfvf, sg);
	वापस -EINVAL;
पूर्ण

अटल u64 otx2_tso_frag_dma_addr(काष्ठा otx2_snd_queue *sq,
				  काष्ठा sk_buff *skb, पूर्णांक seg,
				  u64 seg_addr, पूर्णांक hdr_len, पूर्णांक sqe)
अणु
	काष्ठा sg_list *sg = &sq->sg[sqe];
	स्थिर skb_frag_t *frag;
	पूर्णांक offset;

	अगर (seg < 0)
		वापस sg->dma_addr[0] + (seg_addr - (u64)skb->data);

	frag = &skb_shinfo(skb)->frags[seg];
	offset = seg_addr - (u64)skb_frag_address(frag);
	अगर (skb_headlen(skb) - hdr_len)
		seg++;
	वापस sg->dma_addr[seg] + offset;
पूर्ण

अटल व्योम otx2_sqe_tso_add_sg(काष्ठा otx2_snd_queue *sq,
				काष्ठा sg_list *list, पूर्णांक *offset)
अणु
	काष्ठा nix_sqe_sg_s *sg = शून्य;
	u16 *sg_lens = शून्य;
	u64 *iova = शून्य;
	पूर्णांक seg;

	/* Add SG descriptors with buffer addresses */
	क्रम (seg = 0; seg < list->num_segs; seg++) अणु
		अगर ((seg % MAX_SEGS_PER_SG) == 0) अणु
			sg = (काष्ठा nix_sqe_sg_s *)(sq->sqe_base + *offset);
			sg->ld_type = NIX_SEND_LDTYPE_LDD;
			sg->subdc = NIX_SUBDC_SG;
			sg->segs = 0;
			sg_lens = (व्योम *)sg;
			iova = (व्योम *)sg + माप(*sg);
			/* Next subdc always starts at a 16byte boundary.
			 * So अगर sg->segs is whether 2 or 3, offset += 16bytes.
			 */
			अगर ((list->num_segs - seg) >= (MAX_SEGS_PER_SG - 1))
				*offset += माप(*sg) + (3 * माप(u64));
			अन्यथा
				*offset += माप(*sg) + माप(u64);
		पूर्ण
		sg_lens[frag_num(seg % MAX_SEGS_PER_SG)] = list->size[seg];
		*iova++ = list->dma_addr[seg];
		sg->segs++;
	पूर्ण
पूर्ण

अटल व्योम otx2_sq_append_tso(काष्ठा otx2_nic *pfvf, काष्ठा otx2_snd_queue *sq,
			       काष्ठा sk_buff *skb, u16 qidx)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(pfvf->netdev, qidx);
	पूर्णांक hdr_len, tcp_data, seg_len, pkt_len, offset;
	काष्ठा nix_sqe_hdr_s *sqe_hdr;
	पूर्णांक first_sqe = sq->head;
	काष्ठा sg_list list;
	काष्ठा tso_t tso;

	hdr_len = tso_start(skb, &tso);

	/* Map SKB's fragments to DMA.
	 * It's done here to avoid mapping for every TSO segment's packet.
	 */
	अगर (otx2_dma_map_tso_skb(pfvf, sq, skb, first_sqe, hdr_len)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	netdev_tx_sent_queue(txq, skb->len);

	tcp_data = skb->len - hdr_len;
	जबतक (tcp_data > 0) अणु
		अक्षर *hdr;

		seg_len = min_t(पूर्णांक, skb_shinfo(skb)->gso_size, tcp_data);
		tcp_data -= seg_len;

		/* Set SQE's SEND_HDR */
		स_रखो(sq->sqe_base, 0, sq->sqe_size);
		sqe_hdr = (काष्ठा nix_sqe_hdr_s *)(sq->sqe_base);
		otx2_sqe_add_hdr(pfvf, sq, sqe_hdr, skb, qidx);
		offset = माप(*sqe_hdr);

		/* Add TSO segment's pkt header */
		hdr = sq->tso_hdrs->base + (sq->head * TSO_HEADER_SIZE);
		tso_build_hdr(skb, hdr, &tso, seg_len, tcp_data == 0);
		list.dma_addr[0] =
			sq->tso_hdrs->iova + (sq->head * TSO_HEADER_SIZE);
		list.size[0] = hdr_len;
		list.num_segs = 1;

		/* Add TSO segment's payload data fragments */
		pkt_len = hdr_len;
		जबतक (seg_len > 0) अणु
			पूर्णांक size;

			size = min_t(पूर्णांक, tso.size, seg_len);

			list.size[list.num_segs] = size;
			list.dma_addr[list.num_segs] =
				otx2_tso_frag_dma_addr(sq, skb,
						       tso.next_frag_idx - 1,
						       (u64)tso.data, hdr_len,
						       first_sqe);
			list.num_segs++;
			pkt_len += size;
			seg_len -= size;
			tso_build_data(skb, &tso, size);
		पूर्ण
		sqe_hdr->total = pkt_len;
		otx2_sqe_tso_add_sg(sq, &list, &offset);

		/* DMA mappings and skb needs to be मुक्तd only after last
		 * TSO segment is transmitted out. So set 'PNC' only क्रम
		 * last segment. Also poपूर्णांक last segment's sqe_id to first
		 * segment's SQE index where skb address and DMA mappings
		 * are saved.
		 */
		अगर (!tcp_data) अणु
			sqe_hdr->pnc = 1;
			sqe_hdr->sqe_id = first_sqe;
			sq->sg[first_sqe].skb = (u64)skb;
		पूर्ण अन्यथा अणु
			sqe_hdr->pnc = 0;
		पूर्ण

		sqe_hdr->sizem1 = (offset / 16) - 1;

		/* Flush SQE to HW */
		pfvf->hw_ops->sqe_flush(pfvf, sq, offset, qidx);
	पूर्ण
पूर्ण

अटल bool is_hw_tso_supported(काष्ठा otx2_nic *pfvf,
				काष्ठा sk_buff *skb)
अणु
	पूर्णांक payload_len, last_seg_size;

	अगर (test_bit(HW_TSO, &pfvf->hw.cap_flag))
		वापस true;

	/* On 96xx A0, HW TSO not supported */
	अगर (!is_96xx_B0(pfvf->pdev))
		वापस false;

	/* HW has an issue due to which when the payload of the last LSO
	 * segment is लघुer than 16 bytes, some header fields may not
	 * be correctly modअगरied, hence करोn't offload such TSO segments.
	 */

	payload_len = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	last_seg_size = payload_len % skb_shinfo(skb)->gso_size;
	अगर (last_seg_size && last_seg_size < 16)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक otx2_get_sqe_count(काष्ठा otx2_nic *pfvf, काष्ठा sk_buff *skb)
अणु
	अगर (!skb_shinfo(skb)->gso_size)
		वापस 1;

	/* HW TSO */
	अगर (is_hw_tso_supported(pfvf, skb))
		वापस 1;

	/* SW TSO */
	वापस skb_shinfo(skb)->gso_segs;
पूर्ण

अटल व्योम otx2_set_txtstamp(काष्ठा otx2_nic *pfvf, काष्ठा sk_buff *skb,
			      काष्ठा otx2_snd_queue *sq, पूर्णांक *offset)
अणु
	u64 iova;

	अगर (!skb_shinfo(skb)->gso_size &&
	    skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) अणु
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		iova = sq->बारtamps->iova + (sq->head * माप(u64));
		otx2_sqe_add_mem(sq, offset, NIX_SENDMEMALG_E_SETTSTMP, iova);
	पूर्ण अन्यथा अणु
		skb_tx_बारtamp(skb);
	पूर्ण
पूर्ण

bool otx2_sq_append_skb(काष्ठा net_device *netdev, काष्ठा otx2_snd_queue *sq,
			काष्ठा sk_buff *skb, u16 qidx)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(netdev, qidx);
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	पूर्णांक offset, num_segs, मुक्त_sqe;
	काष्ठा nix_sqe_hdr_s *sqe_hdr;

	/* Check अगर there is room क्रम new SQE.
	 * 'Num of SQBs freed to SQ's pool - SQ's Aura count'
	 * will give मुक्त SQE count.
	 */
	मुक्त_sqe = (sq->num_sqbs - *sq->aura_fc_addr) * sq->sqe_per_sqb;

	अगर (मुक्त_sqe < sq->sqe_thresh ||
	    मुक्त_sqe < otx2_get_sqe_count(pfvf, skb))
		वापस false;

	num_segs = skb_shinfo(skb)->nr_frags + 1;

	/* If SKB करोesn't fit in a single SQE, linearize it.
	 * TODO: Consider adding JUMP descriptor instead.
	 */
	अगर (unlikely(num_segs > OTX2_MAX_FRAGS_IN_SQE)) अणु
		अगर (__skb_linearize(skb)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस true;
		पूर्ण
		num_segs = skb_shinfo(skb)->nr_frags + 1;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_size && !is_hw_tso_supported(pfvf, skb)) अणु
		/* Insert vlan tag beक्रमe giving pkt to tso */
		अगर (skb_vlan_tag_present(skb))
			skb = __vlan_hwaccel_push_inside(skb);
		otx2_sq_append_tso(pfvf, sq, skb, qidx);
		वापस true;
	पूर्ण

	/* Set SQE's SEND_HDR.
	 * Do not clear the first 64bit as it contains स्थिरant info.
	 */
	स_रखो(sq->sqe_base + 8, 0, sq->sqe_size - 8);
	sqe_hdr = (काष्ठा nix_sqe_hdr_s *)(sq->sqe_base);
	otx2_sqe_add_hdr(pfvf, sq, sqe_hdr, skb, qidx);
	offset = माप(*sqe_hdr);

	/* Add extended header अगर needed */
	otx2_sqe_add_ext(pfvf, sq, skb, &offset);

	/* Add SG subdesc with data frags */
	अगर (!otx2_sqe_add_sg(pfvf, sq, skb, num_segs, &offset)) अणु
		otx2_dma_unmap_skb_frags(pfvf, &sq->sg[sq->head]);
		वापस false;
	पूर्ण

	otx2_set_txtstamp(pfvf, skb, sq, &offset);

	sqe_hdr->sizem1 = (offset / 16) - 1;

	netdev_tx_sent_queue(txq, skb->len);

	/* Flush SQE to HW */
	pfvf->hw_ops->sqe_flush(pfvf, sq, offset, qidx);

	वापस true;
पूर्ण
EXPORT_SYMBOL(otx2_sq_append_skb);

व्योम otx2_cleanup_rx_cqes(काष्ठा otx2_nic *pfvf, काष्ठा otx2_cq_queue *cq)
अणु
	काष्ठा nix_cqe_rx_s *cqe;
	पूर्णांक processed_cqe = 0;
	u64 iova, pa;

	जबतक ((cqe = (काष्ठा nix_cqe_rx_s *)otx2_get_next_cqe(cq))) अणु
		अगर (!cqe->sg.subdc)
			जारी;
		processed_cqe++;
		अगर (cqe->sg.segs > 1) अणु
			otx2_मुक्त_rcv_seg(pfvf, cqe, cq->cq_idx);
			जारी;
		पूर्ण
		iova = cqe->sg.seg_addr - OTX2_HEAD_ROOM;
		pa = otx2_iova_to_phys(pfvf->iommu_करोमुख्य, iova);
		otx2_dma_unmap_page(pfvf, iova, pfvf->rbsize, DMA_FROM_DEVICE);
		put_page(virt_to_page(phys_to_virt(pa)));
	पूर्ण

	/* Free CQEs to HW */
	otx2_ग_लिखो64(pfvf, NIX_LF_CQ_OP_DOOR,
		     ((u64)cq->cq_idx << 32) | processed_cqe);
पूर्ण

व्योम otx2_cleanup_tx_cqes(काष्ठा otx2_nic *pfvf, काष्ठा otx2_cq_queue *cq)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा otx2_snd_queue *sq;
	काष्ठा nix_cqe_tx_s *cqe;
	पूर्णांक processed_cqe = 0;
	काष्ठा sg_list *sg;

	sq = &pfvf->qset.sq[cq->cपूर्णांक_idx];

	जबतक ((cqe = (काष्ठा nix_cqe_tx_s *)otx2_get_next_cqe(cq))) अणु
		sg = &sq->sg[cqe->comp.sqe_id];
		skb = (काष्ठा sk_buff *)sg->skb;
		अगर (skb) अणु
			otx2_dma_unmap_skb_frags(pfvf, sg);
			dev_kमुक्त_skb_any(skb);
			sg->skb = (u64)शून्य;
		पूर्ण
		processed_cqe++;
	पूर्ण

	/* Free CQEs to HW */
	otx2_ग_लिखो64(pfvf, NIX_LF_CQ_OP_DOOR,
		     ((u64)cq->cq_idx << 32) | processed_cqe);
पूर्ण

पूर्णांक otx2_rxtx_enable(काष्ठा otx2_nic *pfvf, bool enable)
अणु
	काष्ठा msg_req *msg;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	अगर (enable)
		msg = otx2_mbox_alloc_msg_nix_lf_start_rx(&pfvf->mbox);
	अन्यथा
		msg = otx2_mbox_alloc_msg_nix_lf_stop_rx(&pfvf->mbox);

	अगर (!msg) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण
