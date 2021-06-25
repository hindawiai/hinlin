<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

#समावेश "i40iw_osdep.h"
#समावेश "i40iw_register.h"
#समावेश "i40iw_status.h"
#समावेश "i40iw_hmc.h"

#समावेश "i40iw_d.h"
#समावेश "i40iw_type.h"
#समावेश "i40iw_p.h"
#समावेश "i40iw_puda.h"

अटल व्योम i40iw_ieq_receive(काष्ठा i40iw_sc_vsi *vsi,
			      काष्ठा i40iw_puda_buf *buf);
अटल व्योम i40iw_ieq_tx_compl(काष्ठा i40iw_sc_vsi *vsi, व्योम *sqwrid);
अटल व्योम i40iw_ilq_putback_rcvbuf(काष्ठा i40iw_sc_qp *qp, u32 wqe_idx);
अटल क्रमागत i40iw_status_code i40iw_puda_replenish_rq(काष्ठा i40iw_puda_rsrc
						      *rsrc, bool initial);
/**
 * i40iw_puda_get_listbuf - get buffer from puda list
 * @list: list to use क्रम buffers (ILQ or IEQ)
 */
अटल काष्ठा i40iw_puda_buf *i40iw_puda_get_listbuf(काष्ठा list_head *list)
अणु
	काष्ठा i40iw_puda_buf *buf = शून्य;

	अगर (!list_empty(list)) अणु
		buf = (काष्ठा i40iw_puda_buf *)list->next;
		list_del((काष्ठा list_head *)&buf->list);
	पूर्ण
	वापस buf;
पूर्ण

/**
 * i40iw_puda_get_bufpool - वापस buffer from resource
 * @rsrc: resource to use क्रम buffer
 */
काष्ठा i40iw_puda_buf *i40iw_puda_get_bufpool(काष्ठा i40iw_puda_rsrc *rsrc)
अणु
	काष्ठा i40iw_puda_buf *buf = शून्य;
	काष्ठा list_head *list = &rsrc->bufpool;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&rsrc->bufpool_lock, flags);
	buf = i40iw_puda_get_listbuf(list);
	अगर (buf)
		rsrc->avail_buf_count--;
	अन्यथा
		rsrc->stats_buf_alloc_fail++;
	spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
	वापस buf;
पूर्ण

/**
 * i40iw_puda_ret_bufpool - वापस buffer to rsrc list
 * @rsrc: resource to use क्रम buffer
 * @buf: buffe to वापस to resouce
 */
व्योम i40iw_puda_ret_bufpool(काष्ठा i40iw_puda_rsrc *rsrc,
			    काष्ठा i40iw_puda_buf *buf)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&rsrc->bufpool_lock, flags);
	list_add(&buf->list, &rsrc->bufpool);
	spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
	rsrc->avail_buf_count++;
पूर्ण

/**
 * i40iw_puda_post_recvbuf - set wqe क्रम rcv buffer
 * @rsrc: resource ptr
 * @wqe_idx: wqe index to use
 * @buf: puda buffer क्रम rcv q
 * @initial: flag अगर during init समय
 */
अटल व्योम i40iw_puda_post_recvbuf(काष्ठा i40iw_puda_rsrc *rsrc, u32 wqe_idx,
				    काष्ठा i40iw_puda_buf *buf, bool initial)
अणु
	u64 *wqe;
	काष्ठा i40iw_sc_qp *qp = &rsrc->qp;
	u64 offset24 = 0;

	qp->qp_uk.rq_wrid_array[wqe_idx] = (uपूर्णांकptr_t)buf;
	wqe = qp->qp_uk.rq_base[wqe_idx].elem;
	i40iw_debug(rsrc->dev, I40IW_DEBUG_PUDA,
		    "%s: wqe_idx= %d buf = %p wqe = %p\n", __func__,
		    wqe_idx, buf, wqe);
	अगर (!initial)
		get_64bit_val(wqe, 24, &offset24);

	offset24 = (offset24) ? 0 : LS_64(1, I40IWQPSQ_VALID);

	set_64bit_val(wqe, 0, buf->mem.pa);
	set_64bit_val(wqe, 8,
		      LS_64(buf->mem.size, I40IWQPSQ_FRAG_LEN));
	i40iw_insert_wqe_hdr(wqe, offset24);
पूर्ण

/**
 * i40iw_puda_replenish_rq - post rcv buffers
 * @rsrc: resource to use क्रम buffer
 * @initial: flag अगर during init समय
 */
अटल क्रमागत i40iw_status_code i40iw_puda_replenish_rq(काष्ठा i40iw_puda_rsrc *rsrc,
						      bool initial)
अणु
	u32 i;
	u32 invalid_cnt = rsrc->rxq_invalid_cnt;
	काष्ठा i40iw_puda_buf *buf = शून्य;

	क्रम (i = 0; i < invalid_cnt; i++) अणु
		buf = i40iw_puda_get_bufpool(rsrc);
		अगर (!buf)
			वापस I40IW_ERR_list_empty;
		i40iw_puda_post_recvbuf(rsrc, rsrc->rx_wqe_idx, buf,
					initial);
		rsrc->rx_wqe_idx =
		    ((rsrc->rx_wqe_idx + 1) % rsrc->rq_size);
		rsrc->rxq_invalid_cnt--;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40iw_puda_alloc_buf - allocate mem क्रम buffer
 * @dev: iwarp device
 * @length: length of buffer
 */
अटल काष्ठा i40iw_puda_buf *i40iw_puda_alloc_buf(काष्ठा i40iw_sc_dev *dev,
						   u32 length)
अणु
	काष्ठा i40iw_puda_buf *buf = शून्य;
	काष्ठा i40iw_virt_mem buf_mem;
	क्रमागत i40iw_status_code ret;

	ret = i40iw_allocate_virt_mem(dev->hw, &buf_mem,
				      माप(काष्ठा i40iw_puda_buf));
	अगर (ret) अणु
		i40iw_debug(dev, I40IW_DEBUG_PUDA,
			    "%s: error mem for buf\n", __func__);
		वापस शून्य;
	पूर्ण
	buf = (काष्ठा i40iw_puda_buf *)buf_mem.va;
	ret = i40iw_allocate_dma_mem(dev->hw, &buf->mem, length, 1);
	अगर (ret) अणु
		i40iw_debug(dev, I40IW_DEBUG_PUDA,
			    "%s: error dma mem for buf\n", __func__);
		i40iw_मुक्त_virt_mem(dev->hw, &buf_mem);
		वापस शून्य;
	पूर्ण
	buf->buf_mem.va = buf_mem.va;
	buf->buf_mem.size = buf_mem.size;
	वापस buf;
पूर्ण

/**
 * i40iw_puda_dele_buf - delete buffer back to प्रणाली
 * @dev: iwarp device
 * @buf: buffer to मुक्त
 */
अटल व्योम i40iw_puda_dele_buf(काष्ठा i40iw_sc_dev *dev,
				काष्ठा i40iw_puda_buf *buf)
अणु
	i40iw_मुक्त_dma_mem(dev->hw, &buf->mem);
	i40iw_मुक्त_virt_mem(dev->hw, &buf->buf_mem);
पूर्ण

/**
 * i40iw_puda_get_next_send_wqe - वापस next wqe क्रम processing
 * @qp: puda qp क्रम wqe
 * @wqe_idx: wqe index क्रम caller
 */
अटल u64 *i40iw_puda_get_next_send_wqe(काष्ठा i40iw_qp_uk *qp, u32 *wqe_idx)
अणु
	u64 *wqe = शून्य;
	क्रमागत i40iw_status_code ret_code = 0;

	*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
	अगर (!*wqe_idx)
		qp->swqe_polarity = !qp->swqe_polarity;
	I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
	अगर (ret_code)
		वापस wqe;
	wqe = qp->sq_base[*wqe_idx].elem;

	वापस wqe;
पूर्ण

/**
 * i40iw_puda_poll_info - poll cq क्रम completion
 * @cq: cq क्रम poll
 * @info: info वापस क्रम successful completion
 */
अटल क्रमागत i40iw_status_code i40iw_puda_poll_info(काष्ठा i40iw_sc_cq *cq,
						   काष्ठा i40iw_puda_completion_info *info)
अणु
	u64 qword0, qword2, qword3;
	u64 *cqe;
	u64 comp_ctx;
	bool valid_bit;
	u32 major_err, minor_err;
	bool error;

	cqe = (u64 *)I40IW_GET_CURRENT_CQ_ELEMENT(&cq->cq_uk);
	get_64bit_val(cqe, 24, &qword3);
	valid_bit = (bool)RS_64(qword3, I40IW_CQ_VALID);

	अगर (valid_bit != cq->cq_uk.polarity)
		वापस I40IW_ERR_QUEUE_EMPTY;

	i40iw_debug_buf(cq->dev, I40IW_DEBUG_PUDA, "PUDA CQE", cqe, 32);
	error = (bool)RS_64(qword3, I40IW_CQ_ERROR);
	अगर (error) अणु
		i40iw_debug(cq->dev, I40IW_DEBUG_PUDA, "%s receive error\n", __func__);
		major_err = (u32)(RS_64(qword3, I40IW_CQ_MAJERR));
		minor_err = (u32)(RS_64(qword3, I40IW_CQ_MINERR));
		info->compl_error = major_err << 16 | minor_err;
		वापस I40IW_ERR_CQ_COMPL_ERROR;
	पूर्ण

	get_64bit_val(cqe, 0, &qword0);
	get_64bit_val(cqe, 16, &qword2);

	info->q_type = (u8)RS_64(qword3, I40IW_CQ_SQ);
	info->qp_id = (u32)RS_64(qword2, I40IWCQ_QPID);

	get_64bit_val(cqe, 8, &comp_ctx);
	info->qp = (काष्ठा i40iw_qp_uk *)(अचिन्हित दीर्घ)comp_ctx;
	info->wqe_idx = (u32)RS_64(qword3, I40IW_CQ_WQEIDX);

	अगर (info->q_type == I40IW_CQE_QTYPE_RQ) अणु
		info->vlan_valid = (bool)RS_64(qword3, I40IW_VLAN_TAG_VALID);
		info->l4proto = (u8)RS_64(qword2, I40IW_UDA_L4PROTO);
		info->l3proto = (u8)RS_64(qword2, I40IW_UDA_L3PROTO);
		info->payload_len = (u16)RS_64(qword0, I40IW_UDA_PAYLOADLEN);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40iw_puda_poll_completion - processes completion क्रम cq
 * @dev: iwarp device
 * @cq: cq getting पूर्णांकerrupt
 * @compl_err: वापस any completion err
 */
क्रमागत i40iw_status_code i40iw_puda_poll_completion(काष्ठा i40iw_sc_dev *dev,
						  काष्ठा i40iw_sc_cq *cq, u32 *compl_err)
अणु
	काष्ठा i40iw_qp_uk *qp;
	काष्ठा i40iw_cq_uk *cq_uk = &cq->cq_uk;
	काष्ठा i40iw_puda_completion_info info;
	क्रमागत i40iw_status_code ret = 0;
	काष्ठा i40iw_puda_buf *buf;
	काष्ठा i40iw_puda_rsrc *rsrc;
	व्योम *sqwrid;
	u8 cq_type = cq->cq_type;
	अचिन्हित दीर्घ	flags;

	अगर ((cq_type == I40IW_CQ_TYPE_ILQ) || (cq_type == I40IW_CQ_TYPE_IEQ)) अणु
		rsrc = (cq_type == I40IW_CQ_TYPE_ILQ) ? cq->vsi->ilq : cq->vsi->ieq;
	पूर्ण अन्यथा अणु
		i40iw_debug(dev, I40IW_DEBUG_PUDA, "%s qp_type error\n", __func__);
		वापस I40IW_ERR_BAD_PTR;
	पूर्ण
	स_रखो(&info, 0, माप(info));
	ret = i40iw_puda_poll_info(cq, &info);
	*compl_err = info.compl_error;
	अगर (ret == I40IW_ERR_QUEUE_EMPTY)
		वापस ret;
	अगर (ret)
		जाओ करोne;

	qp = info.qp;
	अगर (!qp || !rsrc) अणु
		ret = I40IW_ERR_BAD_PTR;
		जाओ करोne;
	पूर्ण

	अगर (qp->qp_id != rsrc->qp_id) अणु
		ret = I40IW_ERR_BAD_PTR;
		जाओ करोne;
	पूर्ण

	अगर (info.q_type == I40IW_CQE_QTYPE_RQ) अणु
		buf = (काष्ठा i40iw_puda_buf *)(uपूर्णांकptr_t)qp->rq_wrid_array[info.wqe_idx];
		/* Get all the tcpip inक्रमmation in the buf header */
		ret = i40iw_puda_get_tcpip_info(&info, buf);
		अगर (ret) अणु
			rsrc->stats_rcvd_pkt_err++;
			अगर (cq_type == I40IW_CQ_TYPE_ILQ) अणु
				i40iw_ilq_putback_rcvbuf(&rsrc->qp,
							 info.wqe_idx);
			पूर्ण अन्यथा अणु
				i40iw_puda_ret_bufpool(rsrc, buf);
				i40iw_puda_replenish_rq(rsrc, false);
			पूर्ण
			जाओ करोne;
		पूर्ण

		rsrc->stats_pkt_rcvd++;
		rsrc->compl_rxwqe_idx = info.wqe_idx;
		i40iw_debug(dev, I40IW_DEBUG_PUDA, "%s RQ completion\n", __func__);
		rsrc->receive(rsrc->vsi, buf);
		अगर (cq_type == I40IW_CQ_TYPE_ILQ)
			i40iw_ilq_putback_rcvbuf(&rsrc->qp, info.wqe_idx);
		अन्यथा
			i40iw_puda_replenish_rq(rsrc, false);

	पूर्ण अन्यथा अणु
		i40iw_debug(dev, I40IW_DEBUG_PUDA, "%s SQ completion\n", __func__);
		sqwrid = (व्योम *)(uपूर्णांकptr_t)qp->sq_wrtrk_array[info.wqe_idx].wrid;
		I40IW_RING_SET_TAIL(qp->sq_ring, info.wqe_idx);
		rsrc->xmit_complete(rsrc->vsi, sqwrid);
		spin_lock_irqsave(&rsrc->bufpool_lock, flags);
		rsrc->tx_wqe_avail_cnt++;
		spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
		अगर (!list_empty(&rsrc->txpend))
			i40iw_puda_send_buf(rsrc, शून्य);
	पूर्ण

करोne:
	I40IW_RING_MOVE_HEAD(cq_uk->cq_ring, ret);
	अगर (I40IW_RING_GETCURRENT_HEAD(cq_uk->cq_ring) == 0)
		cq_uk->polarity = !cq_uk->polarity;
	/* update cq tail in cq shaकरोw memory also */
	I40IW_RING_MOVE_TAIL(cq_uk->cq_ring);
	set_64bit_val(cq_uk->shaकरोw_area, 0,
		      I40IW_RING_GETCURRENT_HEAD(cq_uk->cq_ring));
	वापस 0;
पूर्ण

/**
 * i40iw_puda_send - complete send wqe क्रम transmit
 * @qp: puda qp क्रम send
 * @info: buffer inक्रमmation क्रम transmit
 */
क्रमागत i40iw_status_code i40iw_puda_send(काष्ठा i40iw_sc_qp *qp,
				       काष्ठा i40iw_puda_send_info *info)
अणु
	u64 *wqe;
	u32 iplen, l4len;
	u64 header[2];
	u32 wqe_idx;
	u8 iipt;

	/* number of 32 bits DWORDS in header */
	l4len = info->tcplen >> 2;
	अगर (info->ipv4) अणु
		iipt = 3;
		iplen = 5;
	पूर्ण अन्यथा अणु
		iipt = 1;
		iplen = 10;
	पूर्ण

	wqe = i40iw_puda_get_next_send_wqe(&qp->qp_uk, &wqe_idx);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	qp->qp_uk.sq_wrtrk_array[wqe_idx].wrid = (uपूर्णांकptr_t)info->scratch;
	/* Third line of WQE descriptor */
	/* maclen is in words */
	header[0] = LS_64((info->maclen >> 1), I40IW_UDA_QPSQ_MACLEN) |
		    LS_64(iplen, I40IW_UDA_QPSQ_IPLEN) | LS_64(1, I40IW_UDA_QPSQ_L4T) |
		    LS_64(iipt, I40IW_UDA_QPSQ_IIPT) |
		    LS_64(l4len, I40IW_UDA_QPSQ_L4LEN);
	/* Forth line of WQE descriptor */
	header[1] = LS_64(I40IW_OP_TYPE_SEND, I40IW_UDA_QPSQ_OPCODE) |
		    LS_64(1, I40IW_UDA_QPSQ_SIGCOMPL) |
		    LS_64(info->करोloopback, I40IW_UDA_QPSQ_DOLOOPBACK) |
		    LS_64(qp->qp_uk.swqe_polarity, I40IW_UDA_QPSQ_VALID);

	set_64bit_val(wqe, 0, info->paddr);
	set_64bit_val(wqe, 8, LS_64(info->len, I40IWQPSQ_FRAG_LEN));
	set_64bit_val(wqe, 16, header[0]);

	i40iw_insert_wqe_hdr(wqe, header[1]);

	i40iw_debug_buf(qp->dev, I40IW_DEBUG_PUDA, "PUDA SEND WQE", wqe, 32);
	i40iw_qp_post_wr(&qp->qp_uk);
	वापस 0;
पूर्ण

/**
 * i40iw_puda_send_buf - transmit puda buffer
 * @rsrc: resource to use क्रम buffer
 * @buf: puda buffer to transmit
 */
व्योम i40iw_puda_send_buf(काष्ठा i40iw_puda_rsrc *rsrc, काष्ठा i40iw_puda_buf *buf)
अणु
	काष्ठा i40iw_puda_send_info info;
	क्रमागत i40iw_status_code ret = 0;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&rsrc->bufpool_lock, flags);
	/* अगर no wqe available or not from a completion and we have
	 * pending buffers, we must queue new buffer
	 */
	अगर (!rsrc->tx_wqe_avail_cnt || (buf && !list_empty(&rsrc->txpend))) अणु
		list_add_tail(&buf->list, &rsrc->txpend);
		spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
		rsrc->stats_sent_pkt_q++;
		अगर (rsrc->type == I40IW_PUDA_RSRC_TYPE_ILQ)
			i40iw_debug(rsrc->dev, I40IW_DEBUG_PUDA,
				    "%s: adding to txpend\n", __func__);
		वापस;
	पूर्ण
	rsrc->tx_wqe_avail_cnt--;
	/* अगर we are coming from a completion and have pending buffers
	 * then Get one from pending list
	 */
	अगर (!buf) अणु
		buf = i40iw_puda_get_listbuf(&rsrc->txpend);
		अगर (!buf)
			जाओ करोne;
	पूर्ण

	info.scratch = (व्योम *)buf;
	info.paddr = buf->mem.pa;
	info.len = buf->totallen;
	info.tcplen = buf->tcphlen;
	info.maclen = buf->maclen;
	info.ipv4 = buf->ipv4;
	info.करोloopback = (rsrc->type == I40IW_PUDA_RSRC_TYPE_IEQ);

	ret = i40iw_puda_send(&rsrc->qp, &info);
	अगर (ret) अणु
		rsrc->tx_wqe_avail_cnt++;
		rsrc->stats_sent_pkt_q++;
		list_add(&buf->list, &rsrc->txpend);
		अगर (rsrc->type == I40IW_PUDA_RSRC_TYPE_ILQ)
			i40iw_debug(rsrc->dev, I40IW_DEBUG_PUDA,
				    "%s: adding to puda_send\n", __func__);
	पूर्ण अन्यथा अणु
		rsrc->stats_pkt_sent++;
	पूर्ण
करोne:
	spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
पूर्ण

/**
 * i40iw_puda_qp_setctx - during init, set qp's context
 * @rsrc: qp's resource
 */
अटल व्योम i40iw_puda_qp_setctx(काष्ठा i40iw_puda_rsrc *rsrc)
अणु
	काष्ठा i40iw_sc_qp *qp = &rsrc->qp;
	u64 *qp_ctx = qp->hw_host_ctx;

	set_64bit_val(qp_ctx, 8, qp->sq_pa);
	set_64bit_val(qp_ctx, 16, qp->rq_pa);

	set_64bit_val(qp_ctx, 24,
		      LS_64(qp->hw_rq_size, I40IWQPC_RQSIZE) |
		      LS_64(qp->hw_sq_size, I40IWQPC_SQSIZE));

	set_64bit_val(qp_ctx, 48, LS_64(rsrc->buf_size, I40IW_UDA_QPC_MAXFRAMESIZE));
	set_64bit_val(qp_ctx, 56, 0);
	set_64bit_val(qp_ctx, 64, 1);

	set_64bit_val(qp_ctx, 136,
		      LS_64(rsrc->cq_id, I40IWQPC_TXCQNUM) |
		      LS_64(rsrc->cq_id, I40IWQPC_RXCQNUM));

	set_64bit_val(qp_ctx, 160, LS_64(1, I40IWQPC_PRIVEN));

	set_64bit_val(qp_ctx, 168,
		      LS_64((uपूर्णांकptr_t)qp, I40IWQPC_QPCOMPCTX));

	set_64bit_val(qp_ctx, 176,
		      LS_64(qp->sq_tph_val, I40IWQPC_SQTPHVAL) |
		      LS_64(qp->rq_tph_val, I40IWQPC_RQTPHVAL) |
		      LS_64(qp->qs_handle, I40IWQPC_QSHANDLE));

	i40iw_debug_buf(rsrc->dev, I40IW_DEBUG_PUDA, "PUDA QP CONTEXT",
			qp_ctx, I40IW_QP_CTX_SIZE);
पूर्ण

/**
 * i40iw_puda_qp_wqe - setup wqe क्रम qp create
 * @dev: iwarp device
 * @qp: resource क्रम qp
 */
अटल क्रमागत i40iw_status_code i40iw_puda_qp_wqe(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_sc_cqp *cqp;
	u64 *wqe;
	u64 header;
	काष्ठा i40iw_ccq_cqe_info compl_info;
	क्रमागत i40iw_status_code status = 0;

	cqp = dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, 0);
	अगर (!wqe)
		वापस I40IW_ERR_RING_FULL;

	set_64bit_val(wqe, 16, qp->hw_host_ctx_pa);
	set_64bit_val(wqe, 40, qp->shaकरोw_area_pa);
	header = qp->qp_uk.qp_id |
		 LS_64(I40IW_CQP_OP_CREATE_QP, I40IW_CQPSQ_OPCODE) |
		 LS_64(I40IW_QP_TYPE_UDA, I40IW_CQPSQ_QP_QPTYPE) |
		 LS_64(1, I40IW_CQPSQ_QP_CQNUMVALID) |
		 LS_64(2, I40IW_CQPSQ_QP_NEXTIWSTATE) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_PUDA, "PUDA CQE", wqe, 32);
	i40iw_sc_cqp_post_sq(cqp);
	status = dev->cqp_ops->poll_क्रम_cqp_op_करोne(dev->cqp,
						    I40IW_CQP_OP_CREATE_QP,
						    &compl_info);
	वापस status;
पूर्ण

/**
 * i40iw_puda_qp_create - create qp क्रम resource
 * @rsrc: resource to use क्रम buffer
 */
अटल क्रमागत i40iw_status_code i40iw_puda_qp_create(काष्ठा i40iw_puda_rsrc *rsrc)
अणु
	काष्ठा i40iw_sc_qp *qp = &rsrc->qp;
	काष्ठा i40iw_qp_uk *ukqp = &qp->qp_uk;
	क्रमागत i40iw_status_code ret = 0;
	u32 sq_size, rq_size, t_size;
	काष्ठा i40iw_dma_mem *mem;

	sq_size = rsrc->sq_size * I40IW_QP_WQE_MIN_SIZE;
	rq_size = rsrc->rq_size * I40IW_QP_WQE_MIN_SIZE;
	t_size = (sq_size + rq_size + (I40IW_SHADOW_AREA_SIZE << 3) +
		  I40IW_QP_CTX_SIZE);
	/* Get page aligned memory */
	ret =
	    i40iw_allocate_dma_mem(rsrc->dev->hw, &rsrc->qpmem, t_size,
				   I40IW_HW_PAGE_SIZE);
	अगर (ret) अणु
		i40iw_debug(rsrc->dev, I40IW_DEBUG_PUDA, "%s: error dma mem\n", __func__);
		वापस ret;
	पूर्ण

	mem = &rsrc->qpmem;
	स_रखो(mem->va, 0, t_size);
	qp->hw_sq_size = i40iw_get_encoded_wqe_size(rsrc->sq_size, false);
	qp->hw_rq_size = i40iw_get_encoded_wqe_size(rsrc->rq_size, false);
	qp->pd = &rsrc->sc_pd;
	qp->qp_type = I40IW_QP_TYPE_UDA;
	qp->dev = rsrc->dev;
	qp->back_qp = (व्योम *)rsrc;
	qp->sq_pa = mem->pa;
	qp->rq_pa = qp->sq_pa + sq_size;
	qp->vsi = rsrc->vsi;
	ukqp->sq_base = mem->va;
	ukqp->rq_base = &ukqp->sq_base[rsrc->sq_size];
	ukqp->shaकरोw_area = ukqp->rq_base[rsrc->rq_size].elem;
	qp->shaकरोw_area_pa = qp->rq_pa + rq_size;
	qp->hw_host_ctx = ukqp->shaकरोw_area + I40IW_SHADOW_AREA_SIZE;
	qp->hw_host_ctx_pa =
		qp->shaकरोw_area_pa + (I40IW_SHADOW_AREA_SIZE << 3);
	ukqp->qp_id = rsrc->qp_id;
	ukqp->sq_wrtrk_array = rsrc->sq_wrtrk_array;
	ukqp->rq_wrid_array = rsrc->rq_wrid_array;

	ukqp->qp_id = rsrc->qp_id;
	ukqp->sq_size = rsrc->sq_size;
	ukqp->rq_size = rsrc->rq_size;

	I40IW_RING_INIT(ukqp->sq_ring, ukqp->sq_size);
	I40IW_RING_INIT(ukqp->initial_ring, ukqp->sq_size);
	I40IW_RING_INIT(ukqp->rq_ring, ukqp->rq_size);

	अगर (qp->pd->dev->is_pf)
		ukqp->wqe_alloc_reg = (u32 __iomem *)(i40iw_get_hw_addr(qp->pd->dev) +
						    I40E_PFPE_WQEALLOC);
	अन्यथा
		ukqp->wqe_alloc_reg = (u32 __iomem *)(i40iw_get_hw_addr(qp->pd->dev) +
						    I40E_VFPE_WQEALLOC1);

	qp->user_pri = 0;
	i40iw_qp_add_qos(qp);
	i40iw_puda_qp_setctx(rsrc);
	अगर (rsrc->dev->ceq_valid)
		ret = i40iw_cqp_qp_create_cmd(rsrc->dev, qp);
	अन्यथा
		ret = i40iw_puda_qp_wqe(rsrc->dev, qp);
	अगर (ret) अणु
		i40iw_qp_rem_qos(qp);
		i40iw_मुक्त_dma_mem(rsrc->dev->hw, &rsrc->qpmem);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40iw_puda_cq_wqe - setup wqe क्रम cq create
 * @dev: iwarp device
 * @cq: cq to setup
 */
अटल क्रमागत i40iw_status_code i40iw_puda_cq_wqe(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_sc_cq *cq)
अणु
	u64 *wqe;
	काष्ठा i40iw_sc_cqp *cqp;
	u64 header;
	काष्ठा i40iw_ccq_cqe_info compl_info;
	क्रमागत i40iw_status_code status = 0;

	cqp = dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, 0);
	अगर (!wqe)
		वापस I40IW_ERR_RING_FULL;

	set_64bit_val(wqe, 0, cq->cq_uk.cq_size);
	set_64bit_val(wqe, 8, RS_64_1(cq, 1));
	set_64bit_val(wqe, 16,
		      LS_64(cq->shaकरोw_पढ़ो_threshold,
			    I40IW_CQPSQ_CQ_SHADOW_READ_THRESHOLD));
	set_64bit_val(wqe, 32, cq->cq_pa);

	set_64bit_val(wqe, 40, cq->shaकरोw_area_pa);

	header = cq->cq_uk.cq_id |
	    LS_64(I40IW_CQP_OP_CREATE_CQ, I40IW_CQPSQ_OPCODE) |
	    LS_64(1, I40IW_CQPSQ_CQ_CHKOVERFLOW) |
	    LS_64(1, I40IW_CQPSQ_CQ_ENCEQEMASK) |
	    LS_64(1, I40IW_CQPSQ_CQ_CEQIDVALID) |
	    LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);
	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(dev, I40IW_DEBUG_PUDA, "PUDA CQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	i40iw_sc_cqp_post_sq(dev->cqp);
	status = dev->cqp_ops->poll_क्रम_cqp_op_करोne(dev->cqp,
						 I40IW_CQP_OP_CREATE_CQ,
						 &compl_info);
	वापस status;
पूर्ण

/**
 * i40iw_puda_cq_create - create cq क्रम resource
 * @rsrc: resource क्रम which cq to create
 */
अटल क्रमागत i40iw_status_code i40iw_puda_cq_create(काष्ठा i40iw_puda_rsrc *rsrc)
अणु
	काष्ठा i40iw_sc_dev *dev = rsrc->dev;
	काष्ठा i40iw_sc_cq *cq = &rsrc->cq;
	क्रमागत i40iw_status_code ret = 0;
	u32 tsize, cqsize;
	काष्ठा i40iw_dma_mem *mem;
	काष्ठा i40iw_cq_init_info info;
	काष्ठा i40iw_cq_uk_init_info *init_info = &info.cq_uk_init_info;

	cq->vsi = rsrc->vsi;
	cqsize = rsrc->cq_size * (माप(काष्ठा i40iw_cqe));
	tsize = cqsize + माप(काष्ठा i40iw_cq_shaकरोw_area);
	ret = i40iw_allocate_dma_mem(dev->hw, &rsrc->cqmem, tsize,
				     I40IW_CQ0_ALIGNMENT);
	अगर (ret)
		वापस ret;

	mem = &rsrc->cqmem;
	स_रखो(&info, 0, माप(info));
	info.dev = dev;
	info.type = (rsrc->type == I40IW_PUDA_RSRC_TYPE_ILQ) ?
			 I40IW_CQ_TYPE_ILQ : I40IW_CQ_TYPE_IEQ;
	info.shaकरोw_पढ़ो_threshold = rsrc->cq_size >> 2;
	info.ceq_id_valid = true;
	info.cq_base_pa = mem->pa;
	info.shaकरोw_area_pa = mem->pa + cqsize;
	init_info->cq_base = mem->va;
	init_info->shaकरोw_area = (u64 *)((u8 *)mem->va + cqsize);
	init_info->cq_size = rsrc->cq_size;
	init_info->cq_id = rsrc->cq_id;
	info.ceqe_mask = true;
	info.ceq_id_valid = true;
	ret = dev->iw_priv_cq_ops->cq_init(cq, &info);
	अगर (ret)
		जाओ error;
	अगर (rsrc->dev->ceq_valid)
		ret = i40iw_cqp_cq_create_cmd(dev, cq);
	अन्यथा
		ret = i40iw_puda_cq_wqe(dev, cq);
error:
	अगर (ret)
		i40iw_मुक्त_dma_mem(dev->hw, &rsrc->cqmem);
	वापस ret;
पूर्ण

/**
 * i40iw_puda_मुक्त_qp - मुक्त qp क्रम resource
 * @rsrc: resource क्रम which qp to मुक्त
 */
अटल व्योम i40iw_puda_मुक्त_qp(काष्ठा i40iw_puda_rsrc *rsrc)
अणु
	क्रमागत i40iw_status_code ret;
	काष्ठा i40iw_ccq_cqe_info compl_info;
	काष्ठा i40iw_sc_dev *dev = rsrc->dev;

	अगर (rsrc->dev->ceq_valid) अणु
		i40iw_cqp_qp_destroy_cmd(dev, &rsrc->qp);
		वापस;
	पूर्ण

	ret = dev->iw_priv_qp_ops->qp_destroy(&rsrc->qp,
			0, false, true, true);
	अगर (ret)
		i40iw_debug(dev, I40IW_DEBUG_PUDA,
			    "%s error puda qp destroy wqe\n",
			    __func__);

	अगर (!ret) अणु
		ret = dev->cqp_ops->poll_क्रम_cqp_op_करोne(dev->cqp,
				I40IW_CQP_OP_DESTROY_QP,
				&compl_info);
		अगर (ret)
			i40iw_debug(dev, I40IW_DEBUG_PUDA,
				    "%s error puda qp destroy failed\n",
				    __func__);
	पूर्ण
पूर्ण

/**
 * i40iw_puda_मुक्त_cq - मुक्त cq क्रम resource
 * @rsrc: resource क्रम which cq to मुक्त
 */
अटल व्योम i40iw_puda_मुक्त_cq(काष्ठा i40iw_puda_rsrc *rsrc)
अणु
	क्रमागत i40iw_status_code ret;
	काष्ठा i40iw_ccq_cqe_info compl_info;
	काष्ठा i40iw_sc_dev *dev = rsrc->dev;

	अगर (rsrc->dev->ceq_valid) अणु
		i40iw_cqp_cq_destroy_cmd(dev, &rsrc->cq);
		वापस;
	पूर्ण
	ret = dev->iw_priv_cq_ops->cq_destroy(&rsrc->cq, 0, true);

	अगर (ret)
		i40iw_debug(dev, I40IW_DEBUG_PUDA,
			    "%s error ieq cq destroy\n",
			    __func__);

	अगर (!ret) अणु
		ret = dev->cqp_ops->poll_क्रम_cqp_op_करोne(dev->cqp,
				I40IW_CQP_OP_DESTROY_CQ,
				&compl_info);
		अगर (ret)
			i40iw_debug(dev, I40IW_DEBUG_PUDA,
				    "%s error ieq qp destroy done\n",
				    __func__);
	पूर्ण
पूर्ण

/**
 * i40iw_puda_dele_resources - delete all resources during बंद
 * @vsi: poपूर्णांकer to vsi काष्ठाure
 * @type: type of resource to dele
 * @reset: true अगर reset chip
 */
व्योम i40iw_puda_dele_resources(काष्ठा i40iw_sc_vsi *vsi,
			       क्रमागत puda_resource_type type,
			       bool reset)
अणु
	काष्ठा i40iw_sc_dev *dev = vsi->dev;
	काष्ठा i40iw_puda_rsrc *rsrc;
	काष्ठा i40iw_puda_buf *buf = शून्य;
	काष्ठा i40iw_puda_buf *nextbuf = शून्य;
	काष्ठा i40iw_virt_mem *vmem;

	चयन (type) अणु
	हाल I40IW_PUDA_RSRC_TYPE_ILQ:
		rsrc = vsi->ilq;
		vmem = &vsi->ilq_mem;
		अवरोध;
	हाल I40IW_PUDA_RSRC_TYPE_IEQ:
		rsrc = vsi->ieq;
		vmem = &vsi->ieq_mem;
		अवरोध;
	शेष:
		i40iw_debug(dev, I40IW_DEBUG_PUDA, "%s: error resource type = 0x%x\n",
			    __func__, type);
		वापस;
	पूर्ण

	चयन (rsrc->completion) अणु
	हाल PUDA_HASH_CRC_COMPLETE:
		i40iw_मुक्त_hash_desc(rsrc->hash_desc);
		fallthrough;
	हाल PUDA_QP_CREATED:
		अगर (!reset)
			i40iw_puda_मुक्त_qp(rsrc);

		i40iw_मुक्त_dma_mem(dev->hw, &rsrc->qpmem);
		fallthrough;
	हाल PUDA_CQ_CREATED:
		अगर (!reset)
			i40iw_puda_मुक्त_cq(rsrc);

		i40iw_मुक्त_dma_mem(dev->hw, &rsrc->cqmem);
		अवरोध;
	शेष:
		i40iw_debug(rsrc->dev, I40IW_DEBUG_PUDA, "%s error no resources\n", __func__);
		अवरोध;
	पूर्ण
	/* Free all allocated puda buffers क्रम both tx and rx */
	buf = rsrc->alloclist;
	जबतक (buf) अणु
		nextbuf = buf->next;
		i40iw_puda_dele_buf(dev, buf);
		buf = nextbuf;
		rsrc->alloc_buf_count--;
	पूर्ण
	i40iw_मुक्त_virt_mem(dev->hw, vmem);
पूर्ण

/**
 * i40iw_puda_allocbufs - allocate buffers क्रम resource
 * @rsrc: resource क्रम buffer allocation
 * @count: number of buffers to create
 */
अटल क्रमागत i40iw_status_code i40iw_puda_allocbufs(काष्ठा i40iw_puda_rsrc *rsrc,
						   u32 count)
अणु
	u32 i;
	काष्ठा i40iw_puda_buf *buf;
	काष्ठा i40iw_puda_buf *nextbuf;

	क्रम (i = 0; i < count; i++) अणु
		buf = i40iw_puda_alloc_buf(rsrc->dev, rsrc->buf_size);
		अगर (!buf) अणु
			rsrc->stats_buf_alloc_fail++;
			वापस I40IW_ERR_NO_MEMORY;
		पूर्ण
		i40iw_puda_ret_bufpool(rsrc, buf);
		rsrc->alloc_buf_count++;
		अगर (!rsrc->alloclist) अणु
			rsrc->alloclist = buf;
		पूर्ण अन्यथा अणु
			nextbuf = rsrc->alloclist;
			rsrc->alloclist = buf;
			buf->next = nextbuf;
		पूर्ण
	पूर्ण
	rsrc->avail_buf_count = rsrc->alloc_buf_count;
	वापस 0;
पूर्ण

/**
 * i40iw_puda_create_rsrc - create resouce (ilq or ieq)
 * @vsi: poपूर्णांकer to vsi काष्ठाure
 * @info: resource inक्रमmation
 */
क्रमागत i40iw_status_code i40iw_puda_create_rsrc(काष्ठा i40iw_sc_vsi *vsi,
					      काष्ठा i40iw_puda_rsrc_info *info)
अणु
	काष्ठा i40iw_sc_dev *dev = vsi->dev;
	क्रमागत i40iw_status_code ret = 0;
	काष्ठा i40iw_puda_rsrc *rsrc;
	u32 pudasize;
	u32 sqwridsize, rqwridsize;
	काष्ठा i40iw_virt_mem *vmem;

	info->count = 1;
	pudasize = माप(काष्ठा i40iw_puda_rsrc);
	sqwridsize = info->sq_size * माप(काष्ठा i40iw_sq_uk_wr_trk_info);
	rqwridsize = info->rq_size * 8;
	चयन (info->type) अणु
	हाल I40IW_PUDA_RSRC_TYPE_ILQ:
		vmem = &vsi->ilq_mem;
		अवरोध;
	हाल I40IW_PUDA_RSRC_TYPE_IEQ:
		vmem = &vsi->ieq_mem;
		अवरोध;
	शेष:
		वापस I40IW_NOT_SUPPORTED;
	पूर्ण
	ret =
	    i40iw_allocate_virt_mem(dev->hw, vmem,
				    pudasize + sqwridsize + rqwridsize);
	अगर (ret)
		वापस ret;
	rsrc = (काष्ठा i40iw_puda_rsrc *)vmem->va;
	spin_lock_init(&rsrc->bufpool_lock);
	अगर (info->type == I40IW_PUDA_RSRC_TYPE_ILQ) अणु
		vsi->ilq = (काष्ठा i40iw_puda_rsrc *)vmem->va;
		vsi->ilq_count = info->count;
		rsrc->receive = info->receive;
		rsrc->xmit_complete = info->xmit_complete;
	पूर्ण अन्यथा अणु
		vmem = &vsi->ieq_mem;
		vsi->ieq_count = info->count;
		vsi->ieq = (काष्ठा i40iw_puda_rsrc *)vmem->va;
		rsrc->receive = i40iw_ieq_receive;
		rsrc->xmit_complete = i40iw_ieq_tx_compl;
	पूर्ण

	rsrc->type = info->type;
	rsrc->sq_wrtrk_array = (काष्ठा i40iw_sq_uk_wr_trk_info *)((u8 *)vmem->va + pudasize);
	rsrc->rq_wrid_array = (u64 *)((u8 *)vmem->va + pudasize + sqwridsize);
	/* Initialize all ieq lists */
	INIT_LIST_HEAD(&rsrc->bufpool);
	INIT_LIST_HEAD(&rsrc->txpend);

	rsrc->tx_wqe_avail_cnt = info->sq_size - 1;
	dev->iw_pd_ops->pd_init(dev, &rsrc->sc_pd, info->pd_id, -1);
	rsrc->qp_id = info->qp_id;
	rsrc->cq_id = info->cq_id;
	rsrc->sq_size = info->sq_size;
	rsrc->rq_size = info->rq_size;
	rsrc->cq_size = info->rq_size + info->sq_size;
	rsrc->buf_size = info->buf_size;
	rsrc->dev = dev;
	rsrc->vsi = vsi;

	ret = i40iw_puda_cq_create(rsrc);
	अगर (!ret) अणु
		rsrc->completion = PUDA_CQ_CREATED;
		ret = i40iw_puda_qp_create(rsrc);
	पूर्ण
	अगर (ret) अणु
		i40iw_debug(dev, I40IW_DEBUG_PUDA, "[%s] error qp_create\n",
			    __func__);
		जाओ error;
	पूर्ण
	rsrc->completion = PUDA_QP_CREATED;

	ret = i40iw_puda_allocbufs(rsrc, info->tx_buf_cnt + info->rq_size);
	अगर (ret) अणु
		i40iw_debug(dev, I40IW_DEBUG_PUDA, "[%s] error alloc_buf\n",
			    __func__);
		जाओ error;
	पूर्ण

	rsrc->rxq_invalid_cnt = info->rq_size;
	ret = i40iw_puda_replenish_rq(rsrc, true);
	अगर (ret)
		जाओ error;

	अगर (info->type == I40IW_PUDA_RSRC_TYPE_IEQ) अणु
		अगर (!i40iw_init_hash_desc(&rsrc->hash_desc)) अणु
			rsrc->check_crc = true;
			rsrc->completion = PUDA_HASH_CRC_COMPLETE;
			ret = 0;
		पूर्ण
	पूर्ण

	dev->ccq_ops->ccq_arm(&rsrc->cq);
	वापस ret;
 error:
	i40iw_puda_dele_resources(vsi, info->type, false);

	वापस ret;
पूर्ण

/**
 * i40iw_ilq_putback_rcvbuf - ilq buffer to put back on rq
 * @qp: ilq's qp resource
 * @wqe_idx:  wqe index of completed rcvbuf
 */
अटल व्योम i40iw_ilq_putback_rcvbuf(काष्ठा i40iw_sc_qp *qp, u32 wqe_idx)
अणु
	u64 *wqe;
	u64 offset24;

	wqe = qp->qp_uk.rq_base[wqe_idx].elem;
	get_64bit_val(wqe, 24, &offset24);
	offset24 = (offset24) ? 0 : LS_64(1, I40IWQPSQ_VALID);
	set_64bit_val(wqe, 24, offset24);
पूर्ण

/**
 * i40iw_ieq_get_fpdu_length - given length वापस fpdu length
 * @length: length अगर fpdu
 */
अटल u16 i40iw_ieq_get_fpdu_length(u16 length)
अणु
	u16 fpdu_len;

	fpdu_len = length + I40IW_IEQ_MPA_FRAMING;
	fpdu_len = (fpdu_len + 3) & 0xfffffffc;
	वापस fpdu_len;
पूर्ण

/**
 * i40iw_ieq_copy_to_txbuf - copydata from rcv buf to tx buf
 * @buf: rcv buffer with partial
 * @txbuf: tx buffer क्रम sendign back
 * @buf_offset: rcv buffer offset to copy from
 * @txbuf_offset: at offset in tx buf to copy
 * @length: length of data to copy
 */
अटल व्योम i40iw_ieq_copy_to_txbuf(काष्ठा i40iw_puda_buf *buf,
				    काष्ठा i40iw_puda_buf *txbuf,
				    u16 buf_offset, u32 txbuf_offset,
				    u32 length)
अणु
	व्योम *mem1 = (u8 *)buf->mem.va + buf_offset;
	व्योम *mem2 = (u8 *)txbuf->mem.va + txbuf_offset;

	स_नकल(mem2, mem1, length);
पूर्ण

/**
 * i40iw_ieq_setup_tx_buf - setup tx buffer क्रम partial handling
 * @buf: reeive buffer with partial
 * @txbuf: buffer to prepare
 */
अटल व्योम i40iw_ieq_setup_tx_buf(काष्ठा i40iw_puda_buf *buf,
				   काष्ठा i40iw_puda_buf *txbuf)
अणु
	txbuf->maclen = buf->maclen;
	txbuf->tcphlen = buf->tcphlen;
	txbuf->ipv4 = buf->ipv4;
	txbuf->hdrlen = buf->hdrlen;
	i40iw_ieq_copy_to_txbuf(buf, txbuf, 0, 0, buf->hdrlen);
पूर्ण

/**
 * i40iw_ieq_check_first_buf - check अगर rcv buffer's seq is in range
 * @buf: receive exception buffer
 * @fps: first partial sequence number
 */
अटल व्योम i40iw_ieq_check_first_buf(काष्ठा i40iw_puda_buf *buf, u32 fps)
अणु
	u32 offset;

	अगर (buf->seqnum < fps) अणु
		offset = fps - buf->seqnum;
		अगर (offset > buf->datalen)
			वापस;
		buf->data += offset;
		buf->datalen -= (u16)offset;
		buf->seqnum = fps;
	पूर्ण
पूर्ण

/**
 * i40iw_ieq_compl_pfpdu - ग_लिखो txbuf with full fpdu
 * @ieq: ieq resource
 * @rxlist: ieq's received buffer list
 * @pbufl: temporary list क्रम buffers क्रम fpddu
 * @txbuf: tx buffer क्रम fpdu
 * @fpdu_len: total length of fpdu
 */
अटल व्योम  i40iw_ieq_compl_pfpdu(काष्ठा i40iw_puda_rsrc *ieq,
				   काष्ठा list_head *rxlist,
				   काष्ठा list_head *pbufl,
				   काष्ठा i40iw_puda_buf *txbuf,
				   u16 fpdu_len)
अणु
	काष्ठा i40iw_puda_buf *buf;
	u32 nextseqnum;
	u16 txoffset, bufoffset;

	buf = i40iw_puda_get_listbuf(pbufl);
	अगर (!buf)
		वापस;
	nextseqnum = buf->seqnum + fpdu_len;
	txbuf->totallen = buf->hdrlen + fpdu_len;
	txbuf->data = (u8 *)txbuf->mem.va + buf->hdrlen;
	i40iw_ieq_setup_tx_buf(buf, txbuf);

	txoffset = buf->hdrlen;
	bufoffset = (u16)(buf->data - (u8 *)buf->mem.va);

	करो अणु
		अगर (buf->datalen >= fpdu_len) अणु
			/* copied full fpdu */
			i40iw_ieq_copy_to_txbuf(buf, txbuf, bufoffset, txoffset, fpdu_len);
			buf->datalen -= fpdu_len;
			buf->data += fpdu_len;
			buf->seqnum = nextseqnum;
			अवरोध;
		पूर्ण
		/* copy partial fpdu */
		i40iw_ieq_copy_to_txbuf(buf, txbuf, bufoffset, txoffset, buf->datalen);
		txoffset += buf->datalen;
		fpdu_len -= buf->datalen;
		i40iw_puda_ret_bufpool(ieq, buf);
		buf = i40iw_puda_get_listbuf(pbufl);
		अगर (!buf)
			वापस;
		bufoffset = (u16)(buf->data - (u8 *)buf->mem.va);
	पूर्ण जबतक (1);

	/* last buffer on the list*/
	अगर (buf->datalen)
		list_add(&buf->list, rxlist);
	अन्यथा
		i40iw_puda_ret_bufpool(ieq, buf);
पूर्ण

/**
 * i40iw_ieq_create_pbufl - create buffer list क्रम single fpdu
 * @pfpdu: partial management per user qp
 * @rxlist: resource list क्रम receive ieq buffes
 * @pbufl: temp. list क्रम buffers क्रम fpddu
 * @buf: first receive buffer
 * @fpdu_len: total length of fpdu
 */
अटल क्रमागत i40iw_status_code i40iw_ieq_create_pbufl(
						     काष्ठा i40iw_pfpdu *pfpdu,
						     काष्ठा list_head *rxlist,
						     काष्ठा list_head *pbufl,
						     काष्ठा i40iw_puda_buf *buf,
						     u16 fpdu_len)
अणु
	क्रमागत i40iw_status_code status = 0;
	काष्ठा i40iw_puda_buf *nextbuf;
	u32	nextseqnum;
	u16 plen = fpdu_len - buf->datalen;
	bool करोne = false;

	nextseqnum = buf->seqnum + buf->datalen;
	करो अणु
		nextbuf = i40iw_puda_get_listbuf(rxlist);
		अगर (!nextbuf) अणु
			status = I40IW_ERR_list_empty;
			अवरोध;
		पूर्ण
		list_add_tail(&nextbuf->list, pbufl);
		अगर (nextbuf->seqnum != nextseqnum) अणु
			pfpdu->bad_seq_num++;
			status = I40IW_ERR_SEQ_NUM;
			अवरोध;
		पूर्ण
		अगर (nextbuf->datalen >= plen) अणु
			करोne = true;
		पूर्ण अन्यथा अणु
			plen -= nextbuf->datalen;
			nextseqnum = nextbuf->seqnum + nextbuf->datalen;
		पूर्ण

	पूर्ण जबतक (!करोne);

	वापस status;
पूर्ण

/**
 * i40iw_ieq_handle_partial - process partial fpdu buffer
 * @ieq: ieq resource
 * @pfpdu: partial management per user qp
 * @buf: receive buffer
 * @fpdu_len: fpdu len in the buffer
 */
अटल क्रमागत i40iw_status_code i40iw_ieq_handle_partial(काष्ठा i40iw_puda_rsrc *ieq,
						       काष्ठा i40iw_pfpdu *pfpdu,
						       काष्ठा i40iw_puda_buf *buf,
						       u16 fpdu_len)
अणु
	क्रमागत i40iw_status_code status = 0;
	u8 *crcptr;
	u32 mpacrc;
	u32 seqnum = buf->seqnum;
	काष्ठा list_head pbufl;	/* partial buffer list */
	काष्ठा i40iw_puda_buf *txbuf = शून्य;
	काष्ठा list_head *rxlist = &pfpdu->rxlist;

	INIT_LIST_HEAD(&pbufl);
	list_add(&buf->list, &pbufl);

	status = i40iw_ieq_create_pbufl(pfpdu, rxlist, &pbufl, buf, fpdu_len);
	अगर (status)
		जाओ error;

	txbuf = i40iw_puda_get_bufpool(ieq);
	अगर (!txbuf) अणु
		pfpdu->no_tx_bufs++;
		status = I40IW_ERR_NO_TXBUFS;
		जाओ error;
	पूर्ण

	i40iw_ieq_compl_pfpdu(ieq, rxlist, &pbufl, txbuf, fpdu_len);
	i40iw_ieq_update_tcpip_info(txbuf, fpdu_len, seqnum);
	crcptr = txbuf->data + fpdu_len - 4;
	mpacrc = *(u32 *)crcptr;
	अगर (ieq->check_crc) अणु
		status = i40iw_ieq_check_mpacrc(ieq->hash_desc, txbuf->data,
						(fpdu_len - 4), mpacrc);
		अगर (status) अणु
			i40iw_debug(ieq->dev, I40IW_DEBUG_IEQ,
				    "%s: error bad crc\n", __func__);
			जाओ error;
		पूर्ण
	पूर्ण

	i40iw_debug_buf(ieq->dev, I40IW_DEBUG_IEQ, "IEQ TX BUFFER",
			txbuf->mem.va, txbuf->totallen);
	i40iw_puda_send_buf(ieq, txbuf);
	pfpdu->rcv_nxt = seqnum + fpdu_len;
	वापस status;
 error:
	जबतक (!list_empty(&pbufl)) अणु
		buf = (काष्ठा i40iw_puda_buf *)(pbufl.prev);
		list_del(&buf->list);
		list_add(&buf->list, rxlist);
	पूर्ण
	अगर (txbuf)
		i40iw_puda_ret_bufpool(ieq, txbuf);
	वापस status;
पूर्ण

/**
 * i40iw_ieq_process_buf - process buffer rcvd क्रम ieq
 * @ieq: ieq resource
 * @pfpdu: partial management per user qp
 * @buf: receive buffer
 */
अटल क्रमागत i40iw_status_code i40iw_ieq_process_buf(काष्ठा i40iw_puda_rsrc *ieq,
						    काष्ठा i40iw_pfpdu *pfpdu,
						    काष्ठा i40iw_puda_buf *buf)
अणु
	u16 fpdu_len = 0;
	u16 datalen = buf->datalen;
	u8 *datap = buf->data;
	u8 *crcptr;
	u16 ioffset = 0;
	u32 mpacrc;
	u32 seqnum = buf->seqnum;
	u16 length = 0;
	u16 full = 0;
	bool partial = false;
	काष्ठा i40iw_puda_buf *txbuf;
	काष्ठा list_head *rxlist = &pfpdu->rxlist;
	क्रमागत i40iw_status_code ret = 0;
	क्रमागत i40iw_status_code status = 0;

	ioffset = (u16)(buf->data - (u8 *)buf->mem.va);
	जबतक (datalen) अणु
		fpdu_len = i40iw_ieq_get_fpdu_length(ntohs(*(__be16 *)datap));
		अगर (fpdu_len > pfpdu->max_fpdu_data) अणु
			i40iw_debug(ieq->dev, I40IW_DEBUG_IEQ,
				    "%s: error bad fpdu_len\n", __func__);
			status = I40IW_ERR_MPA_CRC;
			list_add(&buf->list, rxlist);
			वापस status;
		पूर्ण

		अगर (datalen < fpdu_len) अणु
			partial = true;
			अवरोध;
		पूर्ण
		crcptr = datap + fpdu_len - 4;
		mpacrc = *(u32 *)crcptr;
		अगर (ieq->check_crc)
			ret = i40iw_ieq_check_mpacrc(ieq->hash_desc,
						     datap, fpdu_len - 4, mpacrc);
		अगर (ret) अणु
			status = I40IW_ERR_MPA_CRC;
			list_add(&buf->list, rxlist);
			वापस status;
		पूर्ण
		full++;
		pfpdu->fpdu_processed++;
		datap += fpdu_len;
		length += fpdu_len;
		datalen -= fpdu_len;
	पूर्ण
	अगर (full) अणु
		/* copy full pdu's in the txbuf and send them out */
		txbuf = i40iw_puda_get_bufpool(ieq);
		अगर (!txbuf) अणु
			pfpdu->no_tx_bufs++;
			status = I40IW_ERR_NO_TXBUFS;
			list_add(&buf->list, rxlist);
			वापस status;
		पूर्ण
		/* modअगरy txbuf's buffer header */
		i40iw_ieq_setup_tx_buf(buf, txbuf);
		/* copy full fpdu's to new buffer */
		i40iw_ieq_copy_to_txbuf(buf, txbuf, ioffset, buf->hdrlen,
					length);
		txbuf->totallen = buf->hdrlen + length;

		i40iw_ieq_update_tcpip_info(txbuf, length, buf->seqnum);
		i40iw_puda_send_buf(ieq, txbuf);

		अगर (!datalen) अणु
			pfpdu->rcv_nxt = buf->seqnum + length;
			i40iw_puda_ret_bufpool(ieq, buf);
			वापस status;
		पूर्ण
		buf->data = datap;
		buf->seqnum = seqnum + length;
		buf->datalen = datalen;
		pfpdu->rcv_nxt = buf->seqnum;
	पूर्ण
	अगर (partial)
		status = i40iw_ieq_handle_partial(ieq, pfpdu, buf, fpdu_len);

	वापस status;
पूर्ण

/**
 * i40iw_ieq_process_fpdus - process fpdu's buffers on its list
 * @qp: qp क्रम which partial fpdus
 * @ieq: ieq resource
 */
अटल व्योम i40iw_ieq_process_fpdus(काष्ठा i40iw_sc_qp *qp,
				    काष्ठा i40iw_puda_rsrc *ieq)
अणु
	काष्ठा i40iw_pfpdu *pfpdu = &qp->pfpdu;
	काष्ठा list_head *rxlist = &pfpdu->rxlist;
	काष्ठा i40iw_puda_buf *buf;
	क्रमागत i40iw_status_code status;

	करो अणु
		अगर (list_empty(rxlist))
			अवरोध;
		buf = i40iw_puda_get_listbuf(rxlist);
		अगर (!buf) अणु
			i40iw_debug(ieq->dev, I40IW_DEBUG_IEQ,
				    "%s: error no buf\n", __func__);
			अवरोध;
		पूर्ण
		अगर (buf->seqnum != pfpdu->rcv_nxt) अणु
			/* This could be out of order or missing packet */
			pfpdu->out_of_order++;
			list_add(&buf->list, rxlist);
			अवरोध;
		पूर्ण
		/* keep processing buffers from the head of the list */
		status = i40iw_ieq_process_buf(ieq, pfpdu, buf);
		अगर (status == I40IW_ERR_MPA_CRC) अणु
			pfpdu->mpa_crc_err = true;
			जबतक (!list_empty(rxlist)) अणु
				buf = i40iw_puda_get_listbuf(rxlist);
				i40iw_puda_ret_bufpool(ieq, buf);
				pfpdu->crc_err++;
			पूर्ण
			/* create CQP क्रम AE */
			i40iw_ieq_mpa_crc_ae(ieq->dev, qp);
		पूर्ण
	पूर्ण जबतक (!status);
पूर्ण

/**
 * i40iw_ieq_handle_exception - handle qp's exception
 * @ieq: ieq resource
 * @qp: qp receiving excpetion
 * @buf: receive buffer
 */
अटल व्योम i40iw_ieq_handle_exception(काष्ठा i40iw_puda_rsrc *ieq,
				       काष्ठा i40iw_sc_qp *qp,
				       काष्ठा i40iw_puda_buf *buf)
अणु
	काष्ठा i40iw_puda_buf *पंचांगpbuf = शून्य;
	काष्ठा i40iw_pfpdu *pfpdu = &qp->pfpdu;
	u32 *hw_host_ctx = (u32 *)qp->hw_host_ctx;
	u32 rcv_wnd = hw_host_ctx[23];
	/* first partial seq # in q2 */
	u32 fps = *(u32 *)(qp->q2_buf + Q2_FPSN_OFFSET);
	काष्ठा list_head *rxlist = &pfpdu->rxlist;
	काष्ठा list_head *plist;

	pfpdu->total_ieq_bufs++;

	अगर (pfpdu->mpa_crc_err) अणु
		pfpdu->crc_err++;
		जाओ error;
	पूर्ण
	अगर (pfpdu->mode && (fps != pfpdu->fps)) अणु
		/* clean up qp as it is new partial sequence */
		i40iw_ieq_cleanup_qp(ieq, qp);
		i40iw_debug(ieq->dev, I40IW_DEBUG_IEQ,
			    "%s: restarting new partial\n", __func__);
		pfpdu->mode = false;
	पूर्ण

	अगर (!pfpdu->mode) अणु
		i40iw_debug_buf(ieq->dev, I40IW_DEBUG_IEQ, "Q2 BUFFER", (u64 *)qp->q2_buf, 128);
		/* First_Partial_Sequence_Number check */
		pfpdu->rcv_nxt = fps;
		pfpdu->fps = fps;
		pfpdu->mode = true;
		pfpdu->max_fpdu_data = (buf->ipv4) ? (ieq->vsi->mtu - I40IW_MTU_TO_MSS_IPV4) :
				       (ieq->vsi->mtu - I40IW_MTU_TO_MSS_IPV6);
		pfpdu->pmode_count++;
		INIT_LIST_HEAD(rxlist);
		i40iw_ieq_check_first_buf(buf, fps);
	पूर्ण

	अगर (!(rcv_wnd >= (buf->seqnum - pfpdu->rcv_nxt))) अणु
		pfpdu->bad_seq_num++;
		जाओ error;
	पूर्ण

	अगर (!list_empty(rxlist)) अणु
		पंचांगpbuf = (काष्ठा i40iw_puda_buf *)rxlist->next;
		जबतक ((काष्ठा list_head *)पंचांगpbuf != rxlist) अणु
			अगर ((पूर्णांक)(buf->seqnum - पंचांगpbuf->seqnum) < 0)
				अवरोध;
			plist = &पंचांगpbuf->list;
			पंचांगpbuf = (काष्ठा i40iw_puda_buf *)plist->next;
		पूर्ण
		/* Insert buf beक्रमe पंचांगpbuf */
		list_add_tail(&buf->list, &पंचांगpbuf->list);
	पूर्ण अन्यथा अणु
		list_add_tail(&buf->list, rxlist);
	पूर्ण
	i40iw_ieq_process_fpdus(qp, ieq);
	वापस;
 error:
	i40iw_puda_ret_bufpool(ieq, buf);
पूर्ण

/**
 * i40iw_ieq_receive - received exception buffer
 * @vsi: poपूर्णांकer to vsi काष्ठाure
 * @buf: exception buffer received
 */
अटल व्योम i40iw_ieq_receive(काष्ठा i40iw_sc_vsi *vsi,
			      काष्ठा i40iw_puda_buf *buf)
अणु
	काष्ठा i40iw_puda_rsrc *ieq = vsi->ieq;
	काष्ठा i40iw_sc_qp *qp = शून्य;
	u32 wqe_idx = ieq->compl_rxwqe_idx;

	qp = i40iw_ieq_get_qp(vsi->dev, buf);
	अगर (!qp) अणु
		ieq->stats_bad_qp_id++;
		i40iw_puda_ret_bufpool(ieq, buf);
	पूर्ण अन्यथा अणु
		i40iw_ieq_handle_exception(ieq, qp, buf);
	पूर्ण
	/*
	 * ieq->rx_wqe_idx is used by i40iw_puda_replenish_rq()
	 * on which wqe_idx to start replenish rq
	 */
	अगर (!ieq->rxq_invalid_cnt)
		ieq->rx_wqe_idx = wqe_idx;
	ieq->rxq_invalid_cnt++;
पूर्ण

/**
 * i40iw_ieq_tx_compl - put back after sending completed exception buffer
 * @vsi: poपूर्णांकer to the vsi काष्ठाure
 * @sqwrid: poपूर्णांकer to puda buffer
 */
अटल व्योम i40iw_ieq_tx_compl(काष्ठा i40iw_sc_vsi *vsi, व्योम *sqwrid)
अणु
	काष्ठा i40iw_puda_rsrc *ieq = vsi->ieq;
	काष्ठा i40iw_puda_buf *buf = (काष्ठा i40iw_puda_buf *)sqwrid;

	i40iw_puda_ret_bufpool(ieq, buf);
पूर्ण

/**
 * i40iw_ieq_cleanup_qp - qp is being destroyed
 * @ieq: ieq resource
 * @qp: all pending fpdu buffers
 */
व्योम i40iw_ieq_cleanup_qp(काष्ठा i40iw_puda_rsrc *ieq, काष्ठा i40iw_sc_qp *qp)
अणु
	काष्ठा i40iw_puda_buf *buf;
	काष्ठा i40iw_pfpdu *pfpdu = &qp->pfpdu;
	काष्ठा list_head *rxlist = &pfpdu->rxlist;

	अगर (!pfpdu->mode)
		वापस;
	जबतक (!list_empty(rxlist)) अणु
		buf = i40iw_puda_get_listbuf(rxlist);
		i40iw_puda_ret_bufpool(ieq, buf);
	पूर्ण
पूर्ण
