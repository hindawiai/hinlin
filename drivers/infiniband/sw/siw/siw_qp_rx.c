<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "siw.h"
#समावेश "siw_verbs.h"
#समावेश "siw_mem.h"

/*
 * siw_rx_umem()
 *
 * Receive data of @len पूर्णांकo target referenced by @dest_addr.
 *
 * @srx:	Receive Context
 * @umem:	siw representation of target memory
 * @dest_addr:	user भव address
 * @len:	number of bytes to place
 */
अटल पूर्णांक siw_rx_umem(काष्ठा siw_rx_stream *srx, काष्ठा siw_umem *umem,
		       u64 dest_addr, पूर्णांक len)
अणु
	पूर्णांक copied = 0;

	जबतक (len) अणु
		काष्ठा page *p;
		पूर्णांक pg_off, bytes, rv;
		व्योम *dest;

		p = siw_get_upage(umem, dest_addr);
		अगर (unlikely(!p)) अणु
			pr_warn("siw: %s: [QP %u]: bogus addr: %pK, %pK\n",
				__func__, qp_id(rx_qp(srx)),
				(व्योम *)(uपूर्णांकptr_t)dest_addr,
				(व्योम *)(uपूर्णांकptr_t)umem->fp_addr);
			/* siw पूर्णांकernal error */
			srx->skb_copied += copied;
			srx->skb_new -= copied;

			वापस -EFAULT;
		पूर्ण
		pg_off = dest_addr & ~PAGE_MASK;
		bytes = min(len, (पूर्णांक)PAGE_SIZE - pg_off);

		siw_dbg_qp(rx_qp(srx), "page %pK, bytes=%u\n", p, bytes);

		dest = kmap_atomic(p);
		rv = skb_copy_bits(srx->skb, srx->skb_offset, dest + pg_off,
				   bytes);

		अगर (unlikely(rv)) अणु
			kunmap_atomic(dest);
			srx->skb_copied += copied;
			srx->skb_new -= copied;

			pr_warn("siw: [QP %u]: %s, len %d, page %p, rv %d\n",
				qp_id(rx_qp(srx)), __func__, len, p, rv);

			वापस -EFAULT;
		पूर्ण
		अगर (srx->mpa_crc_hd) अणु
			अगर (rdma_is_kernel_res(&rx_qp(srx)->base_qp.res)) अणु
				crypto_shash_update(srx->mpa_crc_hd,
					(u8 *)(dest + pg_off), bytes);
				kunmap_atomic(dest);
			पूर्ण अन्यथा अणु
				kunmap_atomic(dest);
				/*
				 * Do CRC on original, not target buffer.
				 * Some user land applications may
				 * concurrently ग_लिखो the target buffer,
				 * which would yield a broken CRC.
				 * Walking the skb twice is very ineffcient.
				 * Folding the CRC पूर्णांकo skb_copy_bits()
				 * would be much better, but is currently
				 * not supported.
				 */
				siw_crc_skb(srx, bytes);
			पूर्ण
		पूर्ण अन्यथा अणु
			kunmap_atomic(dest);
		पूर्ण
		srx->skb_offset += bytes;
		copied += bytes;
		len -= bytes;
		dest_addr += bytes;
		pg_off = 0;
	पूर्ण
	srx->skb_copied += copied;
	srx->skb_new -= copied;

	वापस copied;
पूर्ण

अटल पूर्णांक siw_rx_kva(काष्ठा siw_rx_stream *srx, व्योम *kva, पूर्णांक len)
अणु
	पूर्णांक rv;

	siw_dbg_qp(rx_qp(srx), "kva: 0x%pK, len: %u\n", kva, len);

	rv = skb_copy_bits(srx->skb, srx->skb_offset, kva, len);
	अगर (unlikely(rv)) अणु
		pr_warn("siw: [QP %u]: %s, len %d, kva 0x%pK, rv %d\n",
			qp_id(rx_qp(srx)), __func__, len, kva, rv);

		वापस rv;
	पूर्ण
	अगर (srx->mpa_crc_hd)
		crypto_shash_update(srx->mpa_crc_hd, (u8 *)kva, len);

	srx->skb_offset += len;
	srx->skb_copied += len;
	srx->skb_new -= len;

	वापस len;
पूर्ण

अटल पूर्णांक siw_rx_pbl(काष्ठा siw_rx_stream *srx, पूर्णांक *pbl_idx,
		      काष्ठा siw_mem *mem, u64 addr, पूर्णांक len)
अणु
	काष्ठा siw_pbl *pbl = mem->pbl;
	u64 offset = addr - mem->va;
	पूर्णांक copied = 0;

	जबतक (len) अणु
		पूर्णांक bytes;
		dma_addr_t buf_addr =
			siw_pbl_get_buffer(pbl, offset, &bytes, pbl_idx);
		अगर (!buf_addr)
			अवरोध;

		bytes = min(bytes, len);
		अगर (siw_rx_kva(srx, (व्योम *)(uपूर्णांकptr_t)buf_addr, bytes) ==
		    bytes) अणु
			copied += bytes;
			offset += bytes;
			len -= bytes;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस copied;
पूर्ण

/*
 * siw_rresp_check_ntoh()
 *
 * Check incoming RRESP fragment header against expected
 * header values and update expected values क्रम potential next
 * fragment.
 *
 * NOTE: This function must be called only अगर a RRESP DDP segment
 *       starts but not क्रम fragmented consecutive pieces of an
 *       alपढ़ोy started DDP segment.
 */
अटल पूर्णांक siw_rresp_check_ntoh(काष्ठा siw_rx_stream *srx,
				काष्ठा siw_rx_fpdu *frx)
अणु
	काष्ठा iwarp_rdma_rresp *rresp = &srx->hdr.rresp;
	काष्ठा siw_wqe *wqe = &frx->wqe_active;
	क्रमागत ddp_ecode ecode;

	u32 sink_stag = be32_to_cpu(rresp->sink_stag);
	u64 sink_to = be64_to_cpu(rresp->sink_to);

	अगर (frx->first_ddp_seg) अणु
		srx->ddp_stag = wqe->sqe.sge[0].lkey;
		srx->ddp_to = wqe->sqe.sge[0].laddr;
		frx->pbl_idx = 0;
	पूर्ण
	/* Below checks extend beyond the semantics of DDP, and
	 * पूर्णांकo RDMAP:
	 * We check अगर the पढ़ो response matches exactly the
	 * पढ़ो request which was send to the remote peer to
	 * trigger this पढ़ो response. RFC5040/5041 करो not
	 * always have a proper error code क्रम the detected
	 * error हालs. We choose 'base or bounds error' क्रम
	 * हालs where the inbound STag is valid, but offset
	 * or length करो not match our response receive state.
	 */
	अगर (unlikely(srx->ddp_stag != sink_stag)) अणु
		pr_warn("siw: [QP %u]: rresp stag: %08x != %08x\n",
			qp_id(rx_qp(srx)), sink_stag, srx->ddp_stag);
		ecode = DDP_ECODE_T_INVALID_STAG;
		जाओ error;
	पूर्ण
	अगर (unlikely(srx->ddp_to != sink_to)) अणु
		pr_warn("siw: [QP %u]: rresp off: %016llx != %016llx\n",
			qp_id(rx_qp(srx)), (अचिन्हित दीर्घ दीर्घ)sink_to,
			(अचिन्हित दीर्घ दीर्घ)srx->ddp_to);
		ecode = DDP_ECODE_T_BASE_BOUNDS;
		जाओ error;
	पूर्ण
	अगर (unlikely(!frx->more_ddp_segs &&
		     (wqe->processed + srx->fpdu_part_rem != wqe->bytes))) अणु
		pr_warn("siw: [QP %u]: rresp len: %d != %d\n",
			qp_id(rx_qp(srx)),
			wqe->processed + srx->fpdu_part_rem, wqe->bytes);
		ecode = DDP_ECODE_T_BASE_BOUNDS;
		जाओ error;
	पूर्ण
	वापस 0;
error:
	siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_DDP,
			   DDP_ETYPE_TAGGED_BUF, ecode, 0);
	वापस -EINVAL;
पूर्ण

/*
 * siw_ग_लिखो_check_ntoh()
 *
 * Check incoming WRITE fragment header against expected
 * header values and update expected values क्रम potential next
 * fragment
 *
 * NOTE: This function must be called only अगर a WRITE DDP segment
 *       starts but not क्रम fragmented consecutive pieces of an
 *       alपढ़ोy started DDP segment.
 */
अटल पूर्णांक siw_ग_लिखो_check_ntoh(काष्ठा siw_rx_stream *srx,
				काष्ठा siw_rx_fpdu *frx)
अणु
	काष्ठा iwarp_rdma_ग_लिखो *ग_लिखो = &srx->hdr.rग_लिखो;
	क्रमागत ddp_ecode ecode;

	u32 sink_stag = be32_to_cpu(ग_लिखो->sink_stag);
	u64 sink_to = be64_to_cpu(ग_लिखो->sink_to);

	अगर (frx->first_ddp_seg) अणु
		srx->ddp_stag = sink_stag;
		srx->ddp_to = sink_to;
		frx->pbl_idx = 0;
	पूर्ण अन्यथा अणु
		अगर (unlikely(srx->ddp_stag != sink_stag)) अणु
			pr_warn("siw: [QP %u]: write stag: %08x != %08x\n",
				qp_id(rx_qp(srx)), sink_stag,
				srx->ddp_stag);
			ecode = DDP_ECODE_T_INVALID_STAG;
			जाओ error;
		पूर्ण
		अगर (unlikely(srx->ddp_to != sink_to)) अणु
			pr_warn("siw: [QP %u]: write off: %016llx != %016llx\n",
				qp_id(rx_qp(srx)),
				(अचिन्हित दीर्घ दीर्घ)sink_to,
				(अचिन्हित दीर्घ दीर्घ)srx->ddp_to);
			ecode = DDP_ECODE_T_BASE_BOUNDS;
			जाओ error;
		पूर्ण
	पूर्ण
	वापस 0;
error:
	siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_DDP,
			   DDP_ETYPE_TAGGED_BUF, ecode, 0);
	वापस -EINVAL;
पूर्ण

/*
 * siw_send_check_ntoh()
 *
 * Check incoming SEND fragment header against expected
 * header values and update expected MSN अगर no next
 * fragment expected
 *
 * NOTE: This function must be called only अगर a SEND DDP segment
 *       starts but not क्रम fragmented consecutive pieces of an
 *       alपढ़ोy started DDP segment.
 */
अटल पूर्णांक siw_send_check_ntoh(काष्ठा siw_rx_stream *srx,
			       काष्ठा siw_rx_fpdu *frx)
अणु
	काष्ठा iwarp_send_inv *send = &srx->hdr.send_inv;
	काष्ठा siw_wqe *wqe = &frx->wqe_active;
	क्रमागत ddp_ecode ecode;

	u32 ddp_msn = be32_to_cpu(send->ddp_msn);
	u32 ddp_mo = be32_to_cpu(send->ddp_mo);
	u32 ddp_qn = be32_to_cpu(send->ddp_qn);

	अगर (unlikely(ddp_qn != RDMAP_UNTAGGED_QN_SEND)) अणु
		pr_warn("siw: [QP %u]: invalid ddp qn %d for send\n",
			qp_id(rx_qp(srx)), ddp_qn);
		ecode = DDP_ECODE_UT_INVALID_QN;
		जाओ error;
	पूर्ण
	अगर (unlikely(ddp_msn != srx->ddp_msn[RDMAP_UNTAGGED_QN_SEND])) अणु
		pr_warn("siw: [QP %u]: send msn: %u != %u\n",
			qp_id(rx_qp(srx)), ddp_msn,
			srx->ddp_msn[RDMAP_UNTAGGED_QN_SEND]);
		ecode = DDP_ECODE_UT_INVALID_MSN_RANGE;
		जाओ error;
	पूर्ण
	अगर (unlikely(ddp_mo != wqe->processed)) अणु
		pr_warn("siw: [QP %u], send mo: %u != %u\n",
			qp_id(rx_qp(srx)), ddp_mo, wqe->processed);
		ecode = DDP_ECODE_UT_INVALID_MO;
		जाओ error;
	पूर्ण
	अगर (frx->first_ddp_seg) अणु
		/* initialize user memory ग_लिखो position */
		frx->sge_idx = 0;
		frx->sge_off = 0;
		frx->pbl_idx = 0;

		/* only valid क्रम SEND_INV and SEND_SE_INV operations */
		srx->inval_stag = be32_to_cpu(send->inval_stag);
	पूर्ण
	अगर (unlikely(wqe->bytes < wqe->processed + srx->fpdu_part_rem)) अणु
		siw_dbg_qp(rx_qp(srx), "receive space short: %d - %d < %d\n",
			   wqe->bytes, wqe->processed, srx->fpdu_part_rem);
		wqe->wc_status = SIW_WC_LOC_LEN_ERR;
		ecode = DDP_ECODE_UT_INVALID_MSN_NOBUF;
		जाओ error;
	पूर्ण
	वापस 0;
error:
	siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_DDP,
			   DDP_ETYPE_UNTAGGED_BUF, ecode, 0);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा siw_wqe *siw_rqe_get(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rqe *rqe;
	काष्ठा siw_srq *srq;
	काष्ठा siw_wqe *wqe = शून्य;
	bool srq_event = false;
	अचिन्हित दीर्घ flags;

	srq = qp->srq;
	अगर (srq) अणु
		spin_lock_irqsave(&srq->lock, flags);
		अगर (unlikely(!srq->num_rqe))
			जाओ out;

		rqe = &srq->recvq[srq->rq_get % srq->num_rqe];
	पूर्ण अन्यथा अणु
		अगर (unlikely(!qp->recvq))
			जाओ out;

		rqe = &qp->recvq[qp->rq_get % qp->attrs.rq_size];
	पूर्ण
	अगर (likely(rqe->flags == SIW_WQE_VALID)) अणु
		पूर्णांक num_sge = rqe->num_sge;

		अगर (likely(num_sge <= SIW_MAX_SGE)) अणु
			पूर्णांक i = 0;

			wqe = rx_wqe(&qp->rx_untagged);
			rx_type(wqe) = SIW_OP_RECEIVE;
			wqe->wr_status = SIW_WR_INPROGRESS;
			wqe->bytes = 0;
			wqe->processed = 0;

			wqe->rqe.id = rqe->id;
			wqe->rqe.num_sge = num_sge;

			जबतक (i < num_sge) अणु
				wqe->rqe.sge[i].laddr = rqe->sge[i].laddr;
				wqe->rqe.sge[i].lkey = rqe->sge[i].lkey;
				wqe->rqe.sge[i].length = rqe->sge[i].length;
				wqe->bytes += wqe->rqe.sge[i].length;
				wqe->mem[i] = शून्य;
				i++;
			पूर्ण
			/* can be re-used by appl */
			smp_store_mb(rqe->flags, 0);
		पूर्ण अन्यथा अणु
			siw_dbg_qp(qp, "too many sge's: %d\n", rqe->num_sge);
			अगर (srq)
				spin_unlock_irqrestore(&srq->lock, flags);
			वापस शून्य;
		पूर्ण
		अगर (!srq) अणु
			qp->rq_get++;
		पूर्ण अन्यथा अणु
			अगर (srq->armed) अणु
				/* Test SRQ limit */
				u32 off = (srq->rq_get + srq->limit) %
					  srq->num_rqe;
				काष्ठा siw_rqe *rqe2 = &srq->recvq[off];

				अगर (!(rqe2->flags & SIW_WQE_VALID)) अणु
					srq->armed = false;
					srq_event = true;
				पूर्ण
			पूर्ण
			srq->rq_get++;
		पूर्ण
	पूर्ण
out:
	अगर (srq) अणु
		spin_unlock_irqrestore(&srq->lock, flags);
		अगर (srq_event)
			siw_srq_event(srq, IB_EVENT_SRQ_LIMIT_REACHED);
	पूर्ण
	वापस wqe;
पूर्ण

/*
 * siw_proc_send:
 *
 * Process one incoming SEND and place data पूर्णांकo memory referenced by
 * receive wqe.
 *
 * Function supports partially received sends (suspending/resuming
 * current receive wqe processing)
 *
 * वापस value:
 *	0:       reached the end of a DDP segment
 *	-EAGAIN: to be called again to finish the DDP segment
 */
पूर्णांक siw_proc_send(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	काष्ठा siw_rx_fpdu *frx = &qp->rx_untagged;
	काष्ठा siw_wqe *wqe;
	u32 data_bytes; /* all data bytes available */
	u32 rcvd_bytes; /* sum of data bytes rcvd */
	पूर्णांक rv = 0;

	अगर (frx->first_ddp_seg) अणु
		wqe = siw_rqe_get(qp);
		अगर (unlikely(!wqe)) अणु
			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_UNTAGGED_BUF,
					   DDP_ECODE_UT_INVALID_MSN_NOBUF, 0);
			वापस -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		wqe = rx_wqe(frx);
	पूर्ण
	अगर (srx->state == SIW_GET_DATA_START) अणु
		rv = siw_send_check_ntoh(srx, frx);
		अगर (unlikely(rv)) अणु
			siw_qp_event(qp, IB_EVENT_QP_FATAL);
			वापस rv;
		पूर्ण
		अगर (!srx->fpdu_part_rem) /* zero length SEND */
			वापस 0;
	पूर्ण
	data_bytes = min(srx->fpdu_part_rem, srx->skb_new);
	rcvd_bytes = 0;

	/* A zero length SEND will skip below loop */
	जबतक (data_bytes) अणु
		काष्ठा ib_pd *pd;
		काष्ठा siw_mem **mem, *mem_p;
		काष्ठा siw_sge *sge;
		u32 sge_bytes; /* data bytes avail क्रम SGE */

		sge = &wqe->rqe.sge[frx->sge_idx];

		अगर (!sge->length) अणु
			/* just skip empty sge's */
			frx->sge_idx++;
			frx->sge_off = 0;
			frx->pbl_idx = 0;
			जारी;
		पूर्ण
		sge_bytes = min(data_bytes, sge->length - frx->sge_off);
		mem = &wqe->mem[frx->sge_idx];

		/*
		 * check with QP's PD if no SRQ present, SRQ's PD otherwise
		 */
		pd = qp->srq == शून्य ? qp->pd : qp->srq->base_srq.pd;

		rv = siw_check_sge(pd, sge, mem, IB_ACCESS_LOCAL_WRITE,
				   frx->sge_off, sge_bytes);
		अगर (unlikely(rv)) अणु
			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_CATASTROPHIC,
					   DDP_ECODE_CATASTROPHIC, 0);

			siw_qp_event(qp, IB_EVENT_QP_ACCESS_ERR);
			अवरोध;
		पूर्ण
		mem_p = *mem;
		अगर (mem_p->mem_obj == शून्य)
			rv = siw_rx_kva(srx,
				(व्योम *)(uपूर्णांकptr_t)(sge->laddr + frx->sge_off),
				sge_bytes);
		अन्यथा अगर (!mem_p->is_pbl)
			rv = siw_rx_umem(srx, mem_p->umem,
					 sge->laddr + frx->sge_off, sge_bytes);
		अन्यथा
			rv = siw_rx_pbl(srx, &frx->pbl_idx, mem_p,
					sge->laddr + frx->sge_off, sge_bytes);

		अगर (unlikely(rv != sge_bytes)) अणु
			wqe->processed += rcvd_bytes;

			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_CATASTROPHIC,
					   DDP_ECODE_CATASTROPHIC, 0);
			वापस -EINVAL;
		पूर्ण
		frx->sge_off += rv;

		अगर (frx->sge_off == sge->length) अणु
			frx->sge_idx++;
			frx->sge_off = 0;
			frx->pbl_idx = 0;
		पूर्ण
		data_bytes -= rv;
		rcvd_bytes += rv;

		srx->fpdu_part_rem -= rv;
		srx->fpdu_part_rcvd += rv;
	पूर्ण
	wqe->processed += rcvd_bytes;

	अगर (!srx->fpdu_part_rem)
		वापस 0;

	वापस (rv < 0) ? rv : -EAGAIN;
पूर्ण

/*
 * siw_proc_ग_लिखो:
 *
 * Place incoming WRITE after referencing and checking target buffer

 * Function supports partially received WRITEs (suspending/resuming
 * current receive processing)
 *
 * वापस value:
 *	0:       reached the end of a DDP segment
 *	-EAGAIN: to be called again to finish the DDP segment
 */
पूर्णांक siw_proc_ग_लिखो(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	काष्ठा siw_rx_fpdu *frx = &qp->rx_tagged;
	काष्ठा siw_mem *mem;
	पूर्णांक bytes, rv;

	अगर (srx->state == SIW_GET_DATA_START) अणु
		अगर (!srx->fpdu_part_rem) /* zero length WRITE */
			वापस 0;

		rv = siw_ग_लिखो_check_ntoh(srx, frx);
		अगर (unlikely(rv)) अणु
			siw_qp_event(qp, IB_EVENT_QP_FATAL);
			वापस rv;
		पूर्ण
	पूर्ण
	bytes = min(srx->fpdu_part_rem, srx->skb_new);

	अगर (frx->first_ddp_seg) अणु
		काष्ठा siw_wqe *wqe = rx_wqe(frx);

		rx_mem(frx) = siw_mem_id2obj(qp->sdev, srx->ddp_stag >> 8);
		अगर (unlikely(!rx_mem(frx))) अणु
			siw_dbg_qp(qp,
				   "sink stag not found/invalid, stag 0x%08x\n",
				   srx->ddp_stag);

			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_TAGGED_BUF,
					   DDP_ECODE_T_INVALID_STAG, 0);
			वापस -EINVAL;
		पूर्ण
		wqe->rqe.num_sge = 1;
		rx_type(wqe) = SIW_OP_WRITE;
		wqe->wr_status = SIW_WR_INPROGRESS;
	पूर्ण
	mem = rx_mem(frx);

	/*
	 * Check अगर application re-रेजिस्टरed memory with dअगरferent
	 * key field of STag.
	 */
	अगर (unlikely(mem->stag != srx->ddp_stag)) अणु
		siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
				   DDP_ETYPE_TAGGED_BUF,
				   DDP_ECODE_T_INVALID_STAG, 0);
		वापस -EINVAL;
	पूर्ण
	rv = siw_check_mem(qp->pd, mem, srx->ddp_to + srx->fpdu_part_rcvd,
			   IB_ACCESS_REMOTE_WRITE, bytes);
	अगर (unlikely(rv)) अणु
		siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
				   DDP_ETYPE_TAGGED_BUF, siw_tagged_error(-rv),
				   0);

		siw_qp_event(qp, IB_EVENT_QP_ACCESS_ERR);

		वापस -EINVAL;
	पूर्ण

	अगर (mem->mem_obj == शून्य)
		rv = siw_rx_kva(srx,
			(व्योम *)(uपूर्णांकptr_t)(srx->ddp_to + srx->fpdu_part_rcvd),
			bytes);
	अन्यथा अगर (!mem->is_pbl)
		rv = siw_rx_umem(srx, mem->umem,
				 srx->ddp_to + srx->fpdu_part_rcvd, bytes);
	अन्यथा
		rv = siw_rx_pbl(srx, &frx->pbl_idx, mem,
				srx->ddp_to + srx->fpdu_part_rcvd, bytes);

	अगर (unlikely(rv != bytes)) अणु
		siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
				   DDP_ETYPE_CATASTROPHIC,
				   DDP_ECODE_CATASTROPHIC, 0);
		वापस -EINVAL;
	पूर्ण
	srx->fpdu_part_rem -= rv;
	srx->fpdu_part_rcvd += rv;

	अगर (!srx->fpdu_part_rem) अणु
		srx->ddp_to += srx->fpdu_part_rcvd;
		वापस 0;
	पूर्ण
	वापस -EAGAIN;
पूर्ण

/*
 * Inbound RREQ's cannot carry user data.
 */
पूर्णांक siw_proc_rreq(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;

	अगर (!srx->fpdu_part_rem)
		वापस 0;

	pr_warn("siw: [QP %u]: rreq with mpa len %d\n", qp_id(qp),
		be16_to_cpu(srx->hdr.ctrl.mpa_len));

	वापस -EPROTO;
पूर्ण

/*
 * siw_init_rresp:
 *
 * Process inbound RDMA READ REQ. Produce a pseuकरो READ RESPONSE WQE.
 * Put it at the tail of the IRQ, अगर there is another WQE currently in
 * transmit processing. If not, make it the current WQE to be processed
 * and schedule transmit processing.
 *
 * Can be called from softirq context and from process
 * context (RREAD socket loopback हाल!)
 *
 * वापस value:
 *	0:      success,
 *		failure code otherwise
 */

अटल पूर्णांक siw_init_rresp(काष्ठा siw_qp *qp, काष्ठा siw_rx_stream *srx)
अणु
	काष्ठा siw_wqe *tx_work = tx_wqe(qp);
	काष्ठा siw_sqe *resp;

	uपूर्णांक64_t raddr = be64_to_cpu(srx->hdr.rreq.sink_to),
		 laddr = be64_to_cpu(srx->hdr.rreq.source_to);
	uपूर्णांक32_t length = be32_to_cpu(srx->hdr.rreq.पढ़ो_size),
		 lkey = be32_to_cpu(srx->hdr.rreq.source_stag),
		 rkey = be32_to_cpu(srx->hdr.rreq.sink_stag),
		 msn = be32_to_cpu(srx->hdr.rreq.ddp_msn);

	पूर्णांक run_sq = 1, rv = 0;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(msn != srx->ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ])) अणु
		siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
				   DDP_ETYPE_UNTAGGED_BUF,
				   DDP_ECODE_UT_INVALID_MSN_RANGE, 0);
		वापस -EPROTO;
	पूर्ण
	spin_lock_irqsave(&qp->sq_lock, flags);

	अगर (unlikely(!qp->attrs.irq_size)) अणु
		run_sq = 0;
		जाओ error_irq;
	पूर्ण
	अगर (tx_work->wr_status == SIW_WR_IDLE) अणु
		/*
		 * immediately schedule READ response w/o
		 * consuming IRQ entry: IRQ must be empty.
		 */
		tx_work->processed = 0;
		tx_work->mem[0] = शून्य;
		tx_work->wr_status = SIW_WR_QUEUED;
		resp = &tx_work->sqe;
	पूर्ण अन्यथा अणु
		resp = irq_alloc_मुक्त(qp);
		run_sq = 0;
	पूर्ण
	अगर (likely(resp)) अणु
		resp->opcode = SIW_OP_READ_RESPONSE;

		resp->sge[0].length = length;
		resp->sge[0].laddr = laddr;
		resp->sge[0].lkey = lkey;

		/* Keep aside message sequence number क्रम potential
		 * error reporting during Read Response generation.
		 */
		resp->sge[1].length = msn;

		resp->raddr = raddr;
		resp->rkey = rkey;
		resp->num_sge = length ? 1 : 0;

		/* RRESP now valid as current TX wqe or placed पूर्णांकo IRQ */
		smp_store_mb(resp->flags, SIW_WQE_VALID);
	पूर्ण अन्यथा अणु
error_irq:
		pr_warn("siw: [QP %u]: IRQ exceeded or null, size %d\n",
			qp_id(qp), qp->attrs.irq_size);

		siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
				   RDMAP_ETYPE_REMOTE_OPERATION,
				   RDMAP_ECODE_CATASTROPHIC_STREAM, 0);
		rv = -EPROTO;
	पूर्ण

	spin_unlock_irqrestore(&qp->sq_lock, flags);

	अगर (run_sq)
		rv = siw_sq_start(qp);

	वापस rv;
पूर्ण

/*
 * Only called at start of Read.Resonse processing.
 * Transfer pending Read from tip of ORQ पूर्णांकo currrent rx wqe,
 * but keep ORQ entry valid until Read.Response processing करोne.
 * No Queue locking needed.
 */
अटल पूर्णांक siw_orqe_start_rx(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *orqe;
	काष्ठा siw_wqe *wqe = शून्य;

	अगर (unlikely(!qp->attrs.orq_size))
		वापस -EPROTO;

	/* make sure ORQ indices are current */
	smp_mb();

	orqe = orq_get_current(qp);
	अगर (READ_ONCE(orqe->flags) & SIW_WQE_VALID) अणु
		/* RRESP is a TAGGED RDMAP operation */
		wqe = rx_wqe(&qp->rx_tagged);
		wqe->sqe.id = orqe->id;
		wqe->sqe.opcode = orqe->opcode;
		wqe->sqe.sge[0].laddr = orqe->sge[0].laddr;
		wqe->sqe.sge[0].lkey = orqe->sge[0].lkey;
		wqe->sqe.sge[0].length = orqe->sge[0].length;
		wqe->sqe.flags = orqe->flags;
		wqe->sqe.num_sge = 1;
		wqe->bytes = orqe->sge[0].length;
		wqe->processed = 0;
		wqe->mem[0] = शून्य;
		/* make sure WQE is completely written beक्रमe valid */
		smp_wmb();
		wqe->wr_status = SIW_WR_INPROGRESS;

		वापस 0;
	पूर्ण
	वापस -EPROTO;
पूर्ण

/*
 * siw_proc_rresp:
 *
 * Place incoming RRESP data पूर्णांकo memory referenced by RREQ WQE
 * which is at the tip of the ORQ
 *
 * Function supports partially received RRESP's (suspending/resuming
 * current receive processing)
 */
पूर्णांक siw_proc_rresp(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	काष्ठा siw_rx_fpdu *frx = &qp->rx_tagged;
	काष्ठा siw_wqe *wqe = rx_wqe(frx);
	काष्ठा siw_mem **mem, *mem_p;
	काष्ठा siw_sge *sge;
	पूर्णांक bytes, rv;

	अगर (frx->first_ddp_seg) अणु
		अगर (unlikely(wqe->wr_status != SIW_WR_IDLE)) अणु
			pr_warn("siw: [QP %u]: proc RRESP: status %d, op %d\n",
				qp_id(qp), wqe->wr_status, wqe->sqe.opcode);
			rv = -EPROTO;
			जाओ error_term;
		पूर्ण
		/*
		 * fetch pending RREQ from orq
		 */
		rv = siw_orqe_start_rx(qp);
		अगर (rv) अणु
			pr_warn("siw: [QP %u]: ORQ empty, size %d\n",
				qp_id(qp), qp->attrs.orq_size);
			जाओ error_term;
		पूर्ण
		rv = siw_rresp_check_ntoh(srx, frx);
		अगर (unlikely(rv)) अणु
			siw_qp_event(qp, IB_EVENT_QP_FATAL);
			वापस rv;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(wqe->wr_status != SIW_WR_INPROGRESS)) अणु
			pr_warn("siw: [QP %u]: resume RRESP: status %d\n",
				qp_id(qp), wqe->wr_status);
			rv = -EPROTO;
			जाओ error_term;
		पूर्ण
	पूर्ण
	अगर (!srx->fpdu_part_rem) /* zero length RRESPONSE */
		वापस 0;

	sge = wqe->sqe.sge; /* there is only one */
	mem = &wqe->mem[0];

	अगर (!(*mem)) अणु
		/*
		 * check target memory which resolves memory on first fragment
		 */
		rv = siw_check_sge(qp->pd, sge, mem, IB_ACCESS_LOCAL_WRITE, 0,
				   wqe->bytes);
		अगर (unlikely(rv)) अणु
			siw_dbg_qp(qp, "target mem check: %d\n", rv);
			wqe->wc_status = SIW_WC_LOC_PROT_ERR;

			siw_init_terminate(qp, TERM_ERROR_LAYER_DDP,
					   DDP_ETYPE_TAGGED_BUF,
					   siw_tagged_error(-rv), 0);

			siw_qp_event(qp, IB_EVENT_QP_ACCESS_ERR);

			वापस -EINVAL;
		पूर्ण
	पूर्ण
	mem_p = *mem;

	bytes = min(srx->fpdu_part_rem, srx->skb_new);

	अगर (mem_p->mem_obj == शून्य)
		rv = siw_rx_kva(srx,
			(व्योम *)(uपूर्णांकptr_t)(sge->laddr + wqe->processed),
			bytes);
	अन्यथा अगर (!mem_p->is_pbl)
		rv = siw_rx_umem(srx, mem_p->umem, sge->laddr + wqe->processed,
				 bytes);
	अन्यथा
		rv = siw_rx_pbl(srx, &frx->pbl_idx, mem_p,
				sge->laddr + wqe->processed, bytes);
	अगर (rv != bytes) अणु
		wqe->wc_status = SIW_WC_GENERAL_ERR;
		rv = -EINVAL;
		जाओ error_term;
	पूर्ण
	srx->fpdu_part_rem -= rv;
	srx->fpdu_part_rcvd += rv;
	wqe->processed += rv;

	अगर (!srx->fpdu_part_rem) अणु
		srx->ddp_to += srx->fpdu_part_rcvd;
		वापस 0;
	पूर्ण
	वापस -EAGAIN;

error_term:
	siw_init_terminate(qp, TERM_ERROR_LAYER_DDP, DDP_ETYPE_CATASTROPHIC,
			   DDP_ECODE_CATASTROPHIC, 0);
	वापस rv;
पूर्ण

पूर्णांक siw_proc_terminate(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	काष्ठा sk_buff *skb = srx->skb;
	काष्ठा iwarp_terminate *term = &srx->hdr.terminate;
	जोड़ iwarp_hdr term_info;
	u8 *infop = (u8 *)&term_info;
	क्रमागत rdma_opcode op;
	u16 to_copy = माप(काष्ठा iwarp_ctrl);

	pr_warn("siw: got TERMINATE. layer %d, type %d, code %d\n",
		__rdmap_term_layer(term), __rdmap_term_etype(term),
		__rdmap_term_ecode(term));

	अगर (be32_to_cpu(term->ddp_qn) != RDMAP_UNTAGGED_QN_TERMINATE ||
	    be32_to_cpu(term->ddp_msn) !=
		    qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_TERMINATE] ||
	    be32_to_cpu(term->ddp_mo) != 0) अणु
		pr_warn("siw: rx bogus TERM [QN x%08x, MSN x%08x, MO x%08x]\n",
			be32_to_cpu(term->ddp_qn), be32_to_cpu(term->ddp_msn),
			be32_to_cpu(term->ddp_mo));
		वापस -ECONNRESET;
	पूर्ण
	/*
	 * Receive reमुख्यing pieces of TERM अगर indicated
	 */
	अगर (!term->flag_m)
		वापस -ECONNRESET;

	/* Do not take the efक्रमt to reassemble a network fragmented
	 * TERM message
	 */
	अगर (srx->skb_new < माप(काष्ठा iwarp_ctrl_tagged))
		वापस -ECONNRESET;

	स_रखो(infop, 0, माप(term_info));

	skb_copy_bits(skb, srx->skb_offset, infop, to_copy);

	op = __rdmap_get_opcode(&term_info.ctrl);
	अगर (op >= RDMAP_TERMINATE)
		जाओ out;

	infop += to_copy;
	srx->skb_offset += to_copy;
	srx->skb_new -= to_copy;
	srx->skb_copied += to_copy;
	srx->fpdu_part_rcvd += to_copy;
	srx->fpdu_part_rem -= to_copy;

	to_copy = iwarp_pktinfo[op].hdr_len - to_copy;

	/* Again, no network fragmented TERM's */
	अगर (to_copy + MPA_CRC_SIZE > srx->skb_new)
		वापस -ECONNRESET;

	skb_copy_bits(skb, srx->skb_offset, infop, to_copy);

	अगर (term->flag_r) अणु
		siw_dbg_qp(qp, "TERM reports RDMAP hdr type %u, len %u (%s)\n",
			   op, be16_to_cpu(term_info.ctrl.mpa_len),
			   term->flag_m ? "valid" : "invalid");
	पूर्ण अन्यथा अगर (term->flag_d) अणु
		siw_dbg_qp(qp, "TERM reports DDP hdr type %u, len %u (%s)\n",
			   op, be16_to_cpu(term_info.ctrl.mpa_len),
			   term->flag_m ? "valid" : "invalid");
	पूर्ण
out:
	srx->skb_new -= to_copy;
	srx->skb_offset += to_copy;
	srx->skb_copied += to_copy;
	srx->fpdu_part_rcvd += to_copy;
	srx->fpdu_part_rem -= to_copy;

	वापस -ECONNRESET;
पूर्ण

अटल पूर्णांक siw_get_trailer(काष्ठा siw_qp *qp, काष्ठा siw_rx_stream *srx)
अणु
	काष्ठा sk_buff *skb = srx->skb;
	u8 *tbuf = (u8 *)&srx->trailer.crc - srx->pad;
	__wsum crc_in, crc_own = 0;

	siw_dbg_qp(qp, "expected %d, available %d, pad %u\n",
		   srx->fpdu_part_rem, srx->skb_new, srx->pad);

	अगर (srx->skb_new < srx->fpdu_part_rem)
		वापस -EAGAIN;

	skb_copy_bits(skb, srx->skb_offset, tbuf, srx->fpdu_part_rem);

	अगर (srx->mpa_crc_hd && srx->pad)
		crypto_shash_update(srx->mpa_crc_hd, tbuf, srx->pad);

	srx->skb_new -= srx->fpdu_part_rem;
	srx->skb_offset += srx->fpdu_part_rem;
	srx->skb_copied += srx->fpdu_part_rem;

	अगर (!srx->mpa_crc_hd)
		वापस 0;

	/*
	 * CRC32 is computed, transmitted and received directly in NBO,
	 * so there's never a reason to convert byte order.
	 */
	crypto_shash_final(srx->mpa_crc_hd, (u8 *)&crc_own);
	crc_in = (__क्रमce __wsum)srx->trailer.crc;

	अगर (unlikely(crc_in != crc_own)) अणु
		pr_warn("siw: crc error. in: %08x, own %08x, op %u\n",
			crc_in, crc_own, qp->rx_stream.rdmap_op);

		siw_init_terminate(qp, TERM_ERROR_LAYER_LLP,
				   LLP_ETYPE_MPA,
				   LLP_ECODE_RECEIVED_CRC, 0);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MIN_DDP_HDR माप(काष्ठा iwarp_ctrl_tagged)

अटल पूर्णांक siw_get_hdr(काष्ठा siw_rx_stream *srx)
अणु
	काष्ठा sk_buff *skb = srx->skb;
	काष्ठा siw_qp *qp = rx_qp(srx);
	काष्ठा iwarp_ctrl *c_hdr = &srx->hdr.ctrl;
	काष्ठा siw_rx_fpdu *frx;
	u8 opcode;
	पूर्णांक bytes;

	अगर (srx->fpdu_part_rcvd < MIN_DDP_HDR) अणु
		/*
		 * copy a mimimum sized (tagged) DDP frame control part
		 */
		bytes = min_t(पूर्णांक, srx->skb_new,
			      MIN_DDP_HDR - srx->fpdu_part_rcvd);

		skb_copy_bits(skb, srx->skb_offset,
			      (अक्षर *)c_hdr + srx->fpdu_part_rcvd, bytes);

		srx->fpdu_part_rcvd += bytes;

		srx->skb_new -= bytes;
		srx->skb_offset += bytes;
		srx->skb_copied += bytes;

		अगर (srx->fpdu_part_rcvd < MIN_DDP_HDR)
			वापस -EAGAIN;

		अगर (unlikely(__ddp_get_version(c_hdr) != DDP_VERSION)) अणु
			क्रमागत ddp_etype etype;
			क्रमागत ddp_ecode ecode;

			pr_warn("siw: received ddp version unsupported %d\n",
				__ddp_get_version(c_hdr));

			अगर (c_hdr->ddp_rdmap_ctrl & DDP_FLAG_TAGGED) अणु
				etype = DDP_ETYPE_TAGGED_BUF;
				ecode = DDP_ECODE_T_VERSION;
			पूर्ण अन्यथा अणु
				etype = DDP_ETYPE_UNTAGGED_BUF;
				ecode = DDP_ECODE_UT_VERSION;
			पूर्ण
			siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_DDP,
					   etype, ecode, 0);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(__rdmap_get_version(c_hdr) != RDMAP_VERSION)) अणु
			pr_warn("siw: received rdmap version unsupported %d\n",
				__rdmap_get_version(c_hdr));

			siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_RDMAP,
					   RDMAP_ETYPE_REMOTE_OPERATION,
					   RDMAP_ECODE_VERSION, 0);
			वापस -EINVAL;
		पूर्ण
		opcode = __rdmap_get_opcode(c_hdr);

		अगर (opcode > RDMAP_TERMINATE) अणु
			pr_warn("siw: received unknown packet type %u\n",
				opcode);

			siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_RDMAP,
					   RDMAP_ETYPE_REMOTE_OPERATION,
					   RDMAP_ECODE_OPCODE, 0);
			वापस -EINVAL;
		पूर्ण
		siw_dbg_qp(rx_qp(srx), "new header, opcode %u\n", opcode);
	पूर्ण अन्यथा अणु
		opcode = __rdmap_get_opcode(c_hdr);
	पूर्ण
	set_rx_fpdu_context(qp, opcode);
	frx = qp->rx_fpdu;

	/*
	 * Figure out len of current hdr: variable length of
	 * iwarp hdr may क्रमce us to copy hdr inक्रमmation in
	 * two steps. Only tagged DDP messages are alपढ़ोy
	 * completely received.
	 */
	अगर (iwarp_pktinfo[opcode].hdr_len > माप(काष्ठा iwarp_ctrl_tagged)) अणु
		bytes = iwarp_pktinfo[opcode].hdr_len - MIN_DDP_HDR;

		अगर (srx->skb_new < bytes)
			वापस -EAGAIN;

		skb_copy_bits(skb, srx->skb_offset,
			      (अक्षर *)c_hdr + srx->fpdu_part_rcvd, bytes);

		srx->fpdu_part_rcvd += bytes;

		srx->skb_new -= bytes;
		srx->skb_offset += bytes;
		srx->skb_copied += bytes;
	पूर्ण

	/*
	 * DDP/RDMAP header receive completed. Check अगर the current
	 * DDP segment starts a new RDMAP message or जारीs a previously
	 * started RDMAP message.
	 *
	 * Alternating reception of DDP segments (or FPDUs) from incomplete
	 * tagged and untagged RDMAP messages is supported, as दीर्घ as
	 * the current tagged or untagged message माला_लो eventually completed
	 * w/o पूर्णांकersection from another message of the same type
	 * (tagged/untagged). E.g., a WRITE can get पूर्णांकersected by a SEND,
	 * but not by a READ RESPONSE etc.
	 */
	अगर (srx->mpa_crc_hd) अणु
		/*
		 * Restart CRC computation
		 */
		crypto_shash_init(srx->mpa_crc_hd);
		crypto_shash_update(srx->mpa_crc_hd, (u8 *)c_hdr,
				    srx->fpdu_part_rcvd);
	पूर्ण
	अगर (frx->more_ddp_segs) अणु
		frx->first_ddp_seg = 0;
		अगर (frx->prev_rdmap_op != opcode) अणु
			pr_warn("siw: packet intersection: %u : %u\n",
				frx->prev_rdmap_op, opcode);
			/*
			 * The last inbound RDMA operation of same type
			 * (tagged or untagged) is left unfinished.
			 * To complete it in error, make it the current
			 * operation again, even with the header alपढ़ोy
			 * overwritten. For error handling, only the opcode
			 * and current rx context are relevant.
			 */
			set_rx_fpdu_context(qp, frx->prev_rdmap_op);
			__rdmap_set_opcode(c_hdr, frx->prev_rdmap_op);
			वापस -EPROTO;
		पूर्ण
	पूर्ण अन्यथा अणु
		frx->prev_rdmap_op = opcode;
		frx->first_ddp_seg = 1;
	पूर्ण
	frx->more_ddp_segs = c_hdr->ddp_rdmap_ctrl & DDP_FLAG_LAST ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक siw_check_tx_fence(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_wqe *tx_रुकोing = tx_wqe(qp);
	काष्ठा siw_sqe *rreq;
	पूर्णांक resume_tx = 0, rv = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->orq_lock, flags);

	rreq = orq_get_current(qp);

	/* मुक्त current orq entry */
	WRITE_ONCE(rreq->flags, 0);

	अगर (qp->tx_ctx.orq_fence) अणु
		अगर (unlikely(tx_रुकोing->wr_status != SIW_WR_QUEUED)) अणु
			pr_warn("siw: [QP %u]: fence resume: bad status %d\n",
				qp_id(qp), tx_रुकोing->wr_status);
			rv = -EPROTO;
			जाओ out;
		पूर्ण
		/* resume SQ processing */
		अगर (tx_रुकोing->sqe.opcode == SIW_OP_READ ||
		    tx_रुकोing->sqe.opcode == SIW_OP_READ_LOCAL_INV) अणु
			rreq = orq_get_tail(qp);
			अगर (unlikely(!rreq)) अणु
				pr_warn("siw: [QP %u]: no ORQE\n", qp_id(qp));
				rv = -EPROTO;
				जाओ out;
			पूर्ण
			siw_पढ़ो_to_orq(rreq, &tx_रुकोing->sqe);

			qp->orq_put++;
			qp->tx_ctx.orq_fence = 0;
			resume_tx = 1;

		पूर्ण अन्यथा अगर (siw_orq_empty(qp)) अणु
			qp->tx_ctx.orq_fence = 0;
			resume_tx = 1;
		पूर्ण अन्यथा अणु
			pr_warn("siw: [QP %u]: fence resume: orq idx: %d:%d\n",
				qp_id(qp), qp->orq_get, qp->orq_put);
			rv = -EPROTO;
		पूर्ण
	पूर्ण
	qp->orq_get++;
out:
	spin_unlock_irqrestore(&qp->orq_lock, flags);

	अगर (resume_tx)
		rv = siw_sq_start(qp);

	वापस rv;
पूर्ण

/*
 * siw_rdmap_complete()
 *
 * Complete processing of an RDMA message after receiving all
 * DDP segmens or ABort processing after encountering error हाल.
 *
 *   o SENDs + RRESPs will need क्रम completion,
 *   o RREQs need क्रम  READ RESPONSE initialization
 *   o WRITEs need memory dereferencing
 *
 * TODO: Failed WRITEs need local error to be surfaced.
 */
अटल पूर्णांक siw_rdmap_complete(काष्ठा siw_qp *qp, पूर्णांक error)
अणु
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	काष्ठा siw_wqe *wqe = rx_wqe(qp->rx_fpdu);
	क्रमागत siw_wc_status wc_status = wqe->wc_status;
	u8 opcode = __rdmap_get_opcode(&srx->hdr.ctrl);
	पूर्णांक rv = 0;

	चयन (opcode) अणु
	हाल RDMAP_SEND_SE:
	हाल RDMAP_SEND_SE_INVAL:
		wqe->rqe.flags |= SIW_WQE_SOLICITED;
		fallthrough;

	हाल RDMAP_SEND:
	हाल RDMAP_SEND_INVAL:
		अगर (wqe->wr_status == SIW_WR_IDLE)
			अवरोध;

		srx->ddp_msn[RDMAP_UNTAGGED_QN_SEND]++;

		अगर (error != 0 && wc_status == SIW_WC_SUCCESS)
			wc_status = SIW_WC_GENERAL_ERR;
		/*
		 * Handle STag invalidation request
		 */
		अगर (wc_status == SIW_WC_SUCCESS &&
		    (opcode == RDMAP_SEND_INVAL ||
		     opcode == RDMAP_SEND_SE_INVAL)) अणु
			rv = siw_invalidate_stag(qp->pd, srx->inval_stag);
			अगर (rv) अणु
				siw_init_terminate(
					qp, TERM_ERROR_LAYER_RDMAP,
					rv == -EACCES ?
						RDMAP_ETYPE_REMOTE_PROTECTION :
						RDMAP_ETYPE_REMOTE_OPERATION,
					RDMAP_ECODE_CANNOT_INVALIDATE, 0);

				wc_status = SIW_WC_REM_INV_REQ_ERR;
			पूर्ण
			rv = siw_rqe_complete(qp, &wqe->rqe, wqe->processed,
					      rv ? 0 : srx->inval_stag,
					      wc_status);
		पूर्ण अन्यथा अणु
			rv = siw_rqe_complete(qp, &wqe->rqe, wqe->processed,
					      0, wc_status);
		पूर्ण
		siw_wqe_put_mem(wqe, SIW_OP_RECEIVE);
		अवरोध;

	हाल RDMAP_RDMA_READ_RESP:
		अगर (wqe->wr_status == SIW_WR_IDLE)
			अवरोध;

		अगर (error != 0) अणु
			अगर ((srx->state == SIW_GET_HDR &&
			     qp->rx_fpdu->first_ddp_seg) || error == -ENODATA)
				/* possible RREQ in ORQ left untouched */
				अवरोध;

			अगर (wc_status == SIW_WC_SUCCESS)
				wc_status = SIW_WC_GENERAL_ERR;
		पूर्ण अन्यथा अगर (rdma_is_kernel_res(&qp->base_qp.res) &&
			   rx_type(wqe) == SIW_OP_READ_LOCAL_INV) अणु
			/*
			 * Handle any STag invalidation request
			 */
			rv = siw_invalidate_stag(qp->pd, wqe->sqe.sge[0].lkey);
			अगर (rv) अणु
				siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
						   RDMAP_ETYPE_CATASTROPHIC,
						   RDMAP_ECODE_UNSPECIFIED, 0);

				अगर (wc_status == SIW_WC_SUCCESS) अणु
					wc_status = SIW_WC_GENERAL_ERR;
					error = rv;
				पूर्ण
			पूर्ण
		पूर्ण
		/*
		 * All errors turn the wqe पूर्णांकo संकेतled.
		 */
		अगर ((wqe->sqe.flags & SIW_WQE_SIGNALLED) || error != 0)
			rv = siw_sqe_complete(qp, &wqe->sqe, wqe->processed,
					      wc_status);
		siw_wqe_put_mem(wqe, SIW_OP_READ);

		अगर (!error) अणु
			rv = siw_check_tx_fence(qp);
		पूर्ण अन्यथा अणु
			/* Disable current ORQ element */
			अगर (qp->attrs.orq_size)
				WRITE_ONCE(orq_get_current(qp)->flags, 0);
		पूर्ण
		अवरोध;

	हाल RDMAP_RDMA_READ_REQ:
		अगर (!error) अणु
			rv = siw_init_rresp(qp, srx);
			srx->ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ]++;
		पूर्ण
		अवरोध;

	हाल RDMAP_RDMA_WRITE:
		अगर (wqe->wr_status == SIW_WR_IDLE)
			अवरोध;

		/*
		 * Free References from memory object अगर
		 * attached to receive context (inbound WRITE).
		 * While a zero-length WRITE is allowed,
		 * no memory reference got created.
		 */
		अगर (rx_mem(&qp->rx_tagged)) अणु
			siw_mem_put(rx_mem(&qp->rx_tagged));
			rx_mem(&qp->rx_tagged) = शून्य;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	wqe->wr_status = SIW_WR_IDLE;

	वापस rv;
पूर्ण

/*
 * siw_tcp_rx_data()
 *
 * Main routine to consume inbound TCP payload
 *
 * @rd_desc:	पढ़ो descriptor
 * @skb:	socket buffer
 * @off:	offset in skb
 * @len:	skb->len - offset : payload in skb
 */
पूर्णांक siw_tcp_rx_data(पढ़ो_descriptor_t *rd_desc, काष्ठा sk_buff *skb,
		    अचिन्हित पूर्णांक off, माप_प्रकार len)
अणु
	काष्ठा siw_qp *qp = rd_desc->arg.data;
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	पूर्णांक rv;

	srx->skb = skb;
	srx->skb_new = skb->len - off;
	srx->skb_offset = off;
	srx->skb_copied = 0;

	siw_dbg_qp(qp, "new data, len %d\n", srx->skb_new);

	जबतक (srx->skb_new) अणु
		पूर्णांक run_completion = 1;

		अगर (unlikely(srx->rx_suspend)) अणु
			/* Do not process any more data */
			srx->skb_copied += srx->skb_new;
			अवरोध;
		पूर्ण
		चयन (srx->state) अणु
		हाल SIW_GET_HDR:
			rv = siw_get_hdr(srx);
			अगर (!rv) अणु
				srx->fpdu_part_rem =
					be16_to_cpu(srx->hdr.ctrl.mpa_len) -
					srx->fpdu_part_rcvd + MPA_HDR_SIZE;

				अगर (srx->fpdu_part_rem)
					srx->pad = -srx->fpdu_part_rem & 0x3;
				अन्यथा
					srx->pad = 0;

				srx->state = SIW_GET_DATA_START;
				srx->fpdu_part_rcvd = 0;
			पूर्ण
			अवरोध;

		हाल SIW_GET_DATA_MORE:
			/*
			 * Another data fragment of the same DDP segment.
			 * Setting first_ddp_seg = 0 aव्योमs repeating
			 * initializations that shall occur only once per
			 * DDP segment.
			 */
			qp->rx_fpdu->first_ddp_seg = 0;
			fallthrough;

		हाल SIW_GET_DATA_START:
			/*
			 * Headers will be checked by the opcode-specअगरic
			 * data receive function below.
			 */
			rv = iwarp_pktinfo[qp->rx_stream.rdmap_op].rx_data(qp);
			अगर (!rv) अणु
				पूर्णांक mpa_len =
					be16_to_cpu(srx->hdr.ctrl.mpa_len)
					+ MPA_HDR_SIZE;

				srx->fpdu_part_rem = (-mpa_len & 0x3)
						      + MPA_CRC_SIZE;
				srx->fpdu_part_rcvd = 0;
				srx->state = SIW_GET_TRAILER;
			पूर्ण अन्यथा अणु
				अगर (unlikely(rv == -ECONNRESET))
					run_completion = 0;
				अन्यथा
					srx->state = SIW_GET_DATA_MORE;
			पूर्ण
			अवरोध;

		हाल SIW_GET_TRAILER:
			/*
			 * पढ़ो CRC + any padding
			 */
			rv = siw_get_trailer(qp, srx);
			अगर (likely(!rv)) अणु
				/*
				 * FPDU completed.
				 * complete RDMAP message अगर last fragment
				 */
				srx->state = SIW_GET_HDR;
				srx->fpdu_part_rcvd = 0;

				अगर (!(srx->hdr.ctrl.ddp_rdmap_ctrl &
				      DDP_FLAG_LAST))
					/* more frags */
					अवरोध;

				rv = siw_rdmap_complete(qp, 0);
				run_completion = 0;
			पूर्ण
			अवरोध;

		शेष:
			pr_warn("QP[%u]: RX out of state\n", qp_id(qp));
			rv = -EPROTO;
			run_completion = 0;
		पूर्ण
		अगर (unlikely(rv != 0 && rv != -EAGAIN)) अणु
			अगर ((srx->state > SIW_GET_HDR ||
			     qp->rx_fpdu->more_ddp_segs) && run_completion)
				siw_rdmap_complete(qp, rv);

			siw_dbg_qp(qp, "rx error %d, rx state %d\n", rv,
				   srx->state);

			siw_qp_cm_drop(qp, 1);

			अवरोध;
		पूर्ण
		अगर (rv) अणु
			siw_dbg_qp(qp, "fpdu fragment, state %d, missing %d\n",
				   srx->state, srx->fpdu_part_rem);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस srx->skb_copied;
पूर्ण
