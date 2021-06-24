<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/kref.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_cache.h>
#समावेश "mlx5_ib.h"
#समावेश "srq.h"
#समावेश "qp.h"

अटल व्योम mlx5_ib_cq_comp(काष्ठा mlx5_core_cq *cq, काष्ठा mlx5_eqe *eqe)
अणु
	काष्ठा ib_cq *ibcq = &to_mibcq(cq)->ibcq;

	ibcq->comp_handler(ibcq, ibcq->cq_context);
पूर्ण

अटल व्योम mlx5_ib_cq_event(काष्ठा mlx5_core_cq *mcq, क्रमागत mlx5_event type)
अणु
	काष्ठा mlx5_ib_cq *cq = container_of(mcq, काष्ठा mlx5_ib_cq, mcq);
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	काष्ठा ib_cq *ibcq = &cq->ibcq;
	काष्ठा ib_event event;

	अगर (type != MLX5_EVENT_TYPE_CQ_ERROR) अणु
		mlx5_ib_warn(dev, "Unexpected event type %d on CQ %06x\n",
			     type, mcq->cqn);
		वापस;
	पूर्ण

	अगर (ibcq->event_handler) अणु
		event.device     = &dev->ib_dev;
		event.event      = IB_EVENT_CQ_ERR;
		event.element.cq = ibcq;
		ibcq->event_handler(&event, ibcq->cq_context);
	पूर्ण
पूर्ण

अटल व्योम *get_cqe(काष्ठा mlx5_ib_cq *cq, पूर्णांक n)
अणु
	वापस mlx5_frag_buf_get_wqe(&cq->buf.fbc, n);
पूर्ण

अटल u8 sw_ownership_bit(पूर्णांक n, पूर्णांक nent)
अणु
	वापस (n & nent) ? 1 : 0;
पूर्ण

अटल व्योम *get_sw_cqe(काष्ठा mlx5_ib_cq *cq, पूर्णांक n)
अणु
	व्योम *cqe = get_cqe(cq, n & cq->ibcq.cqe);
	काष्ठा mlx5_cqe64 *cqe64;

	cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;

	अगर (likely(get_cqe_opcode(cqe64) != MLX5_CQE_INVALID) &&
	    !((cqe64->op_own & MLX5_CQE_OWNER_MASK) ^ !!(n & (cq->ibcq.cqe + 1)))) अणु
		वापस cqe;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम *next_cqe_sw(काष्ठा mlx5_ib_cq *cq)
अणु
	वापस get_sw_cqe(cq, cq->mcq.cons_index);
पूर्ण

अटल क्रमागत ib_wc_opcode get_umr_comp(काष्ठा mlx5_ib_wq *wq, पूर्णांक idx)
अणु
	चयन (wq->wr_data[idx]) अणु
	हाल MLX5_IB_WR_UMR:
		वापस 0;

	हाल IB_WR_LOCAL_INV:
		वापस IB_WC_LOCAL_INV;

	हाल IB_WR_REG_MR:
		वापस IB_WC_REG_MR;

	शेष:
		pr_warn("unknown completion status\n");
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम handle_good_req(काष्ठा ib_wc *wc, काष्ठा mlx5_cqe64 *cqe,
			    काष्ठा mlx5_ib_wq *wq, पूर्णांक idx)
अणु
	wc->wc_flags = 0;
	चयन (be32_to_cpu(cqe->sop_drop_qpn) >> 24) अणु
	हाल MLX5_OPCODE_RDMA_WRITE_IMM:
		wc->wc_flags |= IB_WC_WITH_IMM;
		fallthrough;
	हाल MLX5_OPCODE_RDMA_WRITE:
		wc->opcode    = IB_WC_RDMA_WRITE;
		अवरोध;
	हाल MLX5_OPCODE_SEND_IMM:
		wc->wc_flags |= IB_WC_WITH_IMM;
		fallthrough;
	हाल MLX5_OPCODE_SEND:
	हाल MLX5_OPCODE_SEND_INVAL:
		wc->opcode    = IB_WC_SEND;
		अवरोध;
	हाल MLX5_OPCODE_RDMA_READ:
		wc->opcode    = IB_WC_RDMA_READ;
		wc->byte_len  = be32_to_cpu(cqe->byte_cnt);
		अवरोध;
	हाल MLX5_OPCODE_ATOMIC_CS:
		wc->opcode    = IB_WC_COMP_SWAP;
		wc->byte_len  = 8;
		अवरोध;
	हाल MLX5_OPCODE_ATOMIC_FA:
		wc->opcode    = IB_WC_FETCH_ADD;
		wc->byte_len  = 8;
		अवरोध;
	हाल MLX5_OPCODE_ATOMIC_MASKED_CS:
		wc->opcode    = IB_WC_MASKED_COMP_SWAP;
		wc->byte_len  = 8;
		अवरोध;
	हाल MLX5_OPCODE_ATOMIC_MASKED_FA:
		wc->opcode    = IB_WC_MASKED_FETCH_ADD;
		wc->byte_len  = 8;
		अवरोध;
	हाल MLX5_OPCODE_UMR:
		wc->opcode = get_umr_comp(wq, idx);
		अवरोध;
	पूर्ण
पूर्ण

क्रमागत अणु
	MLX5_GRH_IN_BUFFER = 1,
	MLX5_GRH_IN_CQE	   = 2,
पूर्ण;

अटल व्योम handle_responder(काष्ठा ib_wc *wc, काष्ठा mlx5_cqe64 *cqe,
			     काष्ठा mlx5_ib_qp *qp)
अणु
	क्रमागत rdma_link_layer ll = rdma_port_get_link_layer(qp->ibqp.device, 1);
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->ibqp.device);
	काष्ठा mlx5_ib_srq *srq = शून्य;
	काष्ठा mlx5_ib_wq *wq;
	u16 wqe_ctr;
	u8  roce_packet_type;
	bool vlan_present;
	u8 g;

	अगर (qp->ibqp.srq || qp->ibqp.xrcd) अणु
		काष्ठा mlx5_core_srq *msrq = शून्य;

		अगर (qp->ibqp.xrcd) अणु
			msrq = mlx5_cmd_get_srq(dev, be32_to_cpu(cqe->srqn));
			अगर (msrq)
				srq = to_mibsrq(msrq);
		पूर्ण अन्यथा अणु
			srq = to_msrq(qp->ibqp.srq);
		पूर्ण
		अगर (srq) अणु
			wqe_ctr = be16_to_cpu(cqe->wqe_counter);
			wc->wr_id = srq->wrid[wqe_ctr];
			mlx5_ib_मुक्त_srq_wqe(srq, wqe_ctr);
			अगर (msrq)
				mlx5_core_res_put(&msrq->common);
		पूर्ण
	पूर्ण अन्यथा अणु
		wq	  = &qp->rq;
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;
	पूर्ण
	wc->byte_len = be32_to_cpu(cqe->byte_cnt);

	चयन (get_cqe_opcode(cqe)) अणु
	हाल MLX5_CQE_RESP_WR_IMM:
		wc->opcode	= IB_WC_RECV_RDMA_WITH_IMM;
		wc->wc_flags	= IB_WC_WITH_IMM;
		wc->ex.imm_data = cqe->immediate;
		अवरोध;
	हाल MLX5_CQE_RESP_SEND:
		wc->opcode   = IB_WC_RECV;
		wc->wc_flags = IB_WC_IP_CSUM_OK;
		अगर (unlikely(!((cqe->hds_ip_ext & CQE_L3_OK) &&
			       (cqe->hds_ip_ext & CQE_L4_OK))))
			wc->wc_flags = 0;
		अवरोध;
	हाल MLX5_CQE_RESP_SEND_IMM:
		wc->opcode	= IB_WC_RECV;
		wc->wc_flags	= IB_WC_WITH_IMM;
		wc->ex.imm_data = cqe->immediate;
		अवरोध;
	हाल MLX5_CQE_RESP_SEND_INV:
		wc->opcode	= IB_WC_RECV;
		wc->wc_flags	= IB_WC_WITH_INVALIDATE;
		wc->ex.invalidate_rkey = be32_to_cpu(cqe->inval_rkey);
		अवरोध;
	पूर्ण
	wc->src_qp	   = be32_to_cpu(cqe->flags_rqpn) & 0xffffff;
	wc->dlid_path_bits = cqe->ml_path;
	g = (be32_to_cpu(cqe->flags_rqpn) >> 28) & 3;
	wc->wc_flags |= g ? IB_WC_GRH : 0;
	अगर (unlikely(is_qp1(qp->ibqp.qp_type))) अणु
		u16 pkey = be32_to_cpu(cqe->pkey) & 0xffff;

		ib_find_cached_pkey(&dev->ib_dev, qp->port, pkey,
				    &wc->pkey_index);
	पूर्ण अन्यथा अणु
		wc->pkey_index = 0;
	पूर्ण

	अगर (ll != IB_LINK_LAYER_ETHERNET) अणु
		wc->slid = be16_to_cpu(cqe->slid);
		wc->sl = (be32_to_cpu(cqe->flags_rqpn) >> 24) & 0xf;
		वापस;
	पूर्ण

	wc->slid = 0;
	vlan_present = cqe->l4_l3_hdr_type & 0x1;
	roce_packet_type   = (be32_to_cpu(cqe->flags_rqpn) >> 24) & 0x3;
	अगर (vlan_present) अणु
		wc->vlan_id = (be16_to_cpu(cqe->vlan_info)) & 0xfff;
		wc->sl = (be16_to_cpu(cqe->vlan_info) >> 13) & 0x7;
		wc->wc_flags |= IB_WC_WITH_VLAN;
	पूर्ण अन्यथा अणु
		wc->sl = 0;
	पूर्ण

	चयन (roce_packet_type) अणु
	हाल MLX5_CQE_ROCE_L3_HEADER_TYPE_GRH:
		wc->network_hdr_type = RDMA_NETWORK_ROCE_V1;
		अवरोध;
	हाल MLX5_CQE_ROCE_L3_HEADER_TYPE_IPV6:
		wc->network_hdr_type = RDMA_NETWORK_IPV6;
		अवरोध;
	हाल MLX5_CQE_ROCE_L3_HEADER_TYPE_IPV4:
		wc->network_hdr_type = RDMA_NETWORK_IPV4;
		अवरोध;
	पूर्ण
	wc->wc_flags |= IB_WC_WITH_NETWORK_HDR_TYPE;
पूर्ण

अटल व्योम dump_cqe(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_err_cqe *cqe)
अणु
	mlx5_ib_warn(dev, "dump error cqe\n");
	mlx5_dump_err_cqe(dev->mdev, cqe);
पूर्ण

अटल व्योम mlx5_handle_error_cqe(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_err_cqe *cqe,
				  काष्ठा ib_wc *wc)
अणु
	पूर्णांक dump = 1;

	चयन (cqe->syndrome) अणु
	हाल MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR:
		wc->status = IB_WC_LOC_LEN_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR:
		wc->status = IB_WC_LOC_QP_OP_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_LOCAL_PROT_ERR:
		wc->status = IB_WC_LOC_PROT_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_WR_FLUSH_ERR:
		dump = 0;
		wc->status = IB_WC_WR_FLUSH_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_MW_BIND_ERR:
		wc->status = IB_WC_MW_BIND_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_BAD_RESP_ERR:
		wc->status = IB_WC_BAD_RESP_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_LOCAL_ACCESS_ERR:
		wc->status = IB_WC_LOC_ACCESS_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR:
		wc->status = IB_WC_REM_INV_REQ_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_REMOTE_ACCESS_ERR:
		wc->status = IB_WC_REM_ACCESS_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_REMOTE_OP_ERR:
		wc->status = IB_WC_REM_OP_ERR;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR:
		wc->status = IB_WC_RETRY_EXC_ERR;
		dump = 0;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_RNR_RETRY_EXC_ERR:
		wc->status = IB_WC_RNR_RETRY_EXC_ERR;
		dump = 0;
		अवरोध;
	हाल MLX5_CQE_SYNDROME_REMOTE_ABORTED_ERR:
		wc->status = IB_WC_REM_ABORT_ERR;
		अवरोध;
	शेष:
		wc->status = IB_WC_GENERAL_ERR;
		अवरोध;
	पूर्ण

	wc->venकरोr_err = cqe->venकरोr_err_synd;
	अगर (dump)
		dump_cqe(dev, cqe);
पूर्ण

अटल व्योम handle_atomics(काष्ठा mlx5_ib_qp *qp, काष्ठा mlx5_cqe64 *cqe64,
			   u16 tail, u16 head)
अणु
	u16 idx;

	करो अणु
		idx = tail & (qp->sq.wqe_cnt - 1);
		अगर (idx == head)
			अवरोध;

		tail = qp->sq.w_list[idx].next;
	पूर्ण जबतक (1);
	tail = qp->sq.w_list[idx].next;
	qp->sq.last_poll = tail;
पूर्ण

अटल व्योम मुक्त_cq_buf(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq_buf *buf)
अणु
	mlx5_frag_buf_मुक्त(dev->mdev, &buf->frag_buf);
पूर्ण

अटल व्योम get_sig_err_item(काष्ठा mlx5_sig_err_cqe *cqe,
			     काष्ठा ib_sig_err *item)
अणु
	u16 syndrome = be16_to_cpu(cqe->syndrome);

#घोषणा GUARD_ERR   (1 << 13)
#घोषणा APPTAG_ERR  (1 << 12)
#घोषणा REFTAG_ERR  (1 << 11)

	अगर (syndrome & GUARD_ERR) अणु
		item->err_type = IB_SIG_BAD_GUARD;
		item->expected = be32_to_cpu(cqe->expected_trans_sig) >> 16;
		item->actual = be32_to_cpu(cqe->actual_trans_sig) >> 16;
	पूर्ण अन्यथा
	अगर (syndrome & REFTAG_ERR) अणु
		item->err_type = IB_SIG_BAD_REFTAG;
		item->expected = be32_to_cpu(cqe->expected_reftag);
		item->actual = be32_to_cpu(cqe->actual_reftag);
	पूर्ण अन्यथा
	अगर (syndrome & APPTAG_ERR) अणु
		item->err_type = IB_SIG_BAD_APPTAG;
		item->expected = be32_to_cpu(cqe->expected_trans_sig) & 0xffff;
		item->actual = be32_to_cpu(cqe->actual_trans_sig) & 0xffff;
	पूर्ण अन्यथा अणु
		pr_err("Got signature completion error with bad syndrome %04x\n",
		       syndrome);
	पूर्ण

	item->sig_err_offset = be64_to_cpu(cqe->err_offset);
	item->key = be32_to_cpu(cqe->mkey);
पूर्ण

अटल व्योम sw_comp(काष्ठा mlx5_ib_qp *qp, पूर्णांक num_entries, काष्ठा ib_wc *wc,
		    पूर्णांक *npolled, bool is_send)
अणु
	काष्ठा mlx5_ib_wq *wq;
	अचिन्हित पूर्णांक cur;
	पूर्णांक np;
	पूर्णांक i;

	wq = (is_send) ? &qp->sq : &qp->rq;
	cur = wq->head - wq->tail;
	np = *npolled;

	अगर (cur == 0)
		वापस;

	क्रम (i = 0;  i < cur && np < num_entries; i++) अणु
		अचिन्हित पूर्णांक idx;

		idx = (is_send) ? wq->last_poll : wq->tail;
		idx &= (wq->wqe_cnt - 1);
		wc->wr_id = wq->wrid[idx];
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->venकरोr_err = MLX5_CQE_SYNDROME_WR_FLUSH_ERR;
		wq->tail++;
		अगर (is_send)
			wq->last_poll = wq->w_list[idx].next;
		np++;
		wc->qp = &qp->ibqp;
		wc++;
	पूर्ण
	*npolled = np;
पूर्ण

अटल व्योम mlx5_ib_poll_sw_comp(काष्ठा mlx5_ib_cq *cq, पूर्णांक num_entries,
				 काष्ठा ib_wc *wc, पूर्णांक *npolled)
अणु
	काष्ठा mlx5_ib_qp *qp;

	*npolled = 0;
	/* Find uncompleted WQEs beदीर्घing to that cq and वापस mmics ones */
	list_क्रम_each_entry(qp, &cq->list_send_qp, cq_send_list) अणु
		sw_comp(qp, num_entries, wc + *npolled, npolled, true);
		अगर (*npolled >= num_entries)
			वापस;
	पूर्ण

	list_क्रम_each_entry(qp, &cq->list_recv_qp, cq_recv_list) अणु
		sw_comp(qp, num_entries, wc + *npolled, npolled, false);
		अगर (*npolled >= num_entries)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_poll_one(काष्ठा mlx5_ib_cq *cq,
			 काष्ठा mlx5_ib_qp **cur_qp,
			 काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	काष्ठा mlx5_err_cqe *err_cqe;
	काष्ठा mlx5_cqe64 *cqe64;
	काष्ठा mlx5_core_qp *mqp;
	काष्ठा mlx5_ib_wq *wq;
	uपूर्णांक8_t opcode;
	uपूर्णांक32_t qpn;
	u16 wqe_ctr;
	व्योम *cqe;
	पूर्णांक idx;

repoll:
	cqe = next_cqe_sw(cq);
	अगर (!cqe)
		वापस -EAGAIN;

	cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;

	++cq->mcq.cons_index;

	/* Make sure we पढ़ो CQ entry contents after we've checked the
	 * ownership bit.
	 */
	rmb();

	opcode = get_cqe_opcode(cqe64);
	अगर (unlikely(opcode == MLX5_CQE_RESIZE_CQ)) अणु
		अगर (likely(cq->resize_buf)) अणु
			मुक्त_cq_buf(dev, &cq->buf);
			cq->buf = *cq->resize_buf;
			kमुक्त(cq->resize_buf);
			cq->resize_buf = शून्य;
			जाओ repoll;
		पूर्ण अन्यथा अणु
			mlx5_ib_warn(dev, "unexpected resize cqe\n");
		पूर्ण
	पूर्ण

	qpn = ntohl(cqe64->sop_drop_qpn) & 0xffffff;
	अगर (!*cur_qp || (qpn != (*cur_qp)->ibqp.qp_num)) अणु
		/* We करो not have to take the QP table lock here,
		 * because CQs will be locked जबतक QPs are हटाओd
		 * from the table.
		 */
		mqp = radix_tree_lookup(&dev->qp_table.tree, qpn);
		*cur_qp = to_mibqp(mqp);
	पूर्ण

	wc->qp  = &(*cur_qp)->ibqp;
	चयन (opcode) अणु
	हाल MLX5_CQE_REQ:
		wq = &(*cur_qp)->sq;
		wqe_ctr = be16_to_cpu(cqe64->wqe_counter);
		idx = wqe_ctr & (wq->wqe_cnt - 1);
		handle_good_req(wc, cqe64, wq, idx);
		handle_atomics(*cur_qp, cqe64, wq->last_poll, idx);
		wc->wr_id = wq->wrid[idx];
		wq->tail = wq->wqe_head[idx] + 1;
		wc->status = IB_WC_SUCCESS;
		अवरोध;
	हाल MLX5_CQE_RESP_WR_IMM:
	हाल MLX5_CQE_RESP_SEND:
	हाल MLX5_CQE_RESP_SEND_IMM:
	हाल MLX5_CQE_RESP_SEND_INV:
		handle_responder(wc, cqe64, *cur_qp);
		wc->status = IB_WC_SUCCESS;
		अवरोध;
	हाल MLX5_CQE_RESIZE_CQ:
		अवरोध;
	हाल MLX5_CQE_REQ_ERR:
	हाल MLX5_CQE_RESP_ERR:
		err_cqe = (काष्ठा mlx5_err_cqe *)cqe64;
		mlx5_handle_error_cqe(dev, err_cqe, wc);
		mlx5_ib_dbg(dev, "%s error cqe on cqn 0x%x:\n",
			    opcode == MLX5_CQE_REQ_ERR ?
			    "Requestor" : "Responder", cq->mcq.cqn);
		mlx5_ib_dbg(dev, "syndrome 0x%x, vendor syndrome 0x%x\n",
			    err_cqe->syndrome, err_cqe->venकरोr_err_synd);
		अगर (opcode == MLX5_CQE_REQ_ERR) अणु
			wq = &(*cur_qp)->sq;
			wqe_ctr = be16_to_cpu(cqe64->wqe_counter);
			idx = wqe_ctr & (wq->wqe_cnt - 1);
			wc->wr_id = wq->wrid[idx];
			wq->tail = wq->wqe_head[idx] + 1;
		पूर्ण अन्यथा अणु
			काष्ठा mlx5_ib_srq *srq;

			अगर ((*cur_qp)->ibqp.srq) अणु
				srq = to_msrq((*cur_qp)->ibqp.srq);
				wqe_ctr = be16_to_cpu(cqe64->wqe_counter);
				wc->wr_id = srq->wrid[wqe_ctr];
				mlx5_ib_मुक्त_srq_wqe(srq, wqe_ctr);
			पूर्ण अन्यथा अणु
				wq = &(*cur_qp)->rq;
				wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
				++wq->tail;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MLX5_CQE_संक_त्रुटि: अणु
		काष्ठा mlx5_sig_err_cqe *sig_err_cqe =
			(काष्ठा mlx5_sig_err_cqe *)cqe64;
		काष्ठा mlx5_core_sig_ctx *sig;

		xa_lock(&dev->sig_mrs);
		sig = xa_load(&dev->sig_mrs,
				mlx5_base_mkey(be32_to_cpu(sig_err_cqe->mkey)));
		get_sig_err_item(sig_err_cqe, &sig->err_item);
		sig->sig_err_exists = true;
		sig->sigerr_count++;

		mlx5_ib_warn(dev, "CQN: 0x%x Got SIGERR on key: 0x%x err_type %x err_offset %llx expected %x actual %x\n",
			     cq->mcq.cqn, sig->err_item.key,
			     sig->err_item.err_type,
			     sig->err_item.sig_err_offset,
			     sig->err_item.expected,
			     sig->err_item.actual);

		xa_unlock(&dev->sig_mrs);
		जाओ repoll;
	पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक poll_soft_wc(काष्ठा mlx5_ib_cq *cq, पूर्णांक num_entries,
			काष्ठा ib_wc *wc, bool is_fatal_err)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	काष्ठा mlx5_ib_wc *soft_wc, *next;
	पूर्णांक npolled = 0;

	list_क्रम_each_entry_safe(soft_wc, next, &cq->wc_list, list) अणु
		अगर (npolled >= num_entries)
			अवरोध;

		mlx5_ib_dbg(dev, "polled software generated completion on CQ 0x%x\n",
			    cq->mcq.cqn);

		अगर (unlikely(is_fatal_err)) अणु
			soft_wc->wc.status = IB_WC_WR_FLUSH_ERR;
			soft_wc->wc.venकरोr_err = MLX5_CQE_SYNDROME_WR_FLUSH_ERR;
		पूर्ण
		wc[npolled++] = soft_wc->wc;
		list_del(&soft_wc->list);
		kमुक्त(soft_wc);
	पूर्ण

	वापस npolled;
पूर्ण

पूर्णांक mlx5_ib_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_cq *cq = to_mcq(ibcq);
	काष्ठा mlx5_ib_qp *cur_qp = शून्य;
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक soft_polled = 0;
	पूर्णांक npolled;

	spin_lock_irqsave(&cq->lock, flags);
	अगर (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		/* make sure no soft wqe's are रुकोing */
		अगर (unlikely(!list_empty(&cq->wc_list)))
			soft_polled = poll_soft_wc(cq, num_entries, wc, true);

		mlx5_ib_poll_sw_comp(cq, num_entries - soft_polled,
				     wc + soft_polled, &npolled);
		जाओ out;
	पूर्ण

	अगर (unlikely(!list_empty(&cq->wc_list)))
		soft_polled = poll_soft_wc(cq, num_entries, wc, false);

	क्रम (npolled = 0; npolled < num_entries - soft_polled; npolled++) अणु
		अगर (mlx5_poll_one(cq, &cur_qp, wc + soft_polled + npolled))
			अवरोध;
	पूर्ण

	अगर (npolled)
		mlx5_cq_set_ci(&cq->mcq);
out:
	spin_unlock_irqrestore(&cq->lock, flags);

	वापस soft_polled + npolled;
पूर्ण

पूर्णांक mlx5_ib_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा mlx5_core_dev *mdev = to_mdev(ibcq->device)->mdev;
	काष्ठा mlx5_ib_cq *cq = to_mcq(ibcq);
	व्योम __iomem *uar_page = mdev->priv.uar->map;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&cq->lock, irq_flags);
	अगर (cq->notअगरy_flags != IB_CQ_NEXT_COMP)
		cq->notअगरy_flags = flags & IB_CQ_SOLICITED_MASK;

	अगर ((flags & IB_CQ_REPORT_MISSED_EVENTS) && !list_empty(&cq->wc_list))
		ret = 1;
	spin_unlock_irqrestore(&cq->lock, irq_flags);

	mlx5_cq_arm(&cq->mcq,
		    (flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		    MLX5_CQ_DB_REQ_NOT_SOL : MLX5_CQ_DB_REQ_NOT,
		    uar_page, to_mcq(ibcq)->mcq.cons_index);

	वापस ret;
पूर्ण

अटल पूर्णांक alloc_cq_frag_buf(काष्ठा mlx5_ib_dev *dev,
			     काष्ठा mlx5_ib_cq_buf *buf,
			     पूर्णांक nent,
			     पूर्णांक cqe_size)
अणु
	काष्ठा mlx5_frag_buf *frag_buf = &buf->frag_buf;
	u8 log_wq_stride = 6 + (cqe_size == 128 ? 1 : 0);
	u8 log_wq_sz     = ilog2(cqe_size);
	पूर्णांक err;

	err = mlx5_frag_buf_alloc_node(dev->mdev,
				       nent * cqe_size,
				       frag_buf,
				       dev->mdev->priv.numa_node);
	अगर (err)
		वापस err;

	mlx5_init_fbc(frag_buf->frags, log_wq_stride, log_wq_sz, &buf->fbc);

	buf->cqe_size = cqe_size;
	buf->nent = nent;

	वापस 0;
पूर्ण

क्रमागत अणु
	MLX5_CQE_RES_FORMAT_HASH = 0,
	MLX5_CQE_RES_FORMAT_CSUM = 1,
	MLX5_CQE_RES_FORMAT_CSUM_STRIDX = 3,
पूर्ण;

अटल पूर्णांक mini_cqe_res_क्रमmat_to_hw(काष्ठा mlx5_ib_dev *dev, u8 क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल MLX5_IB_CQE_RES_FORMAT_HASH:
		वापस MLX5_CQE_RES_FORMAT_HASH;
	हाल MLX5_IB_CQE_RES_FORMAT_CSUM:
		वापस MLX5_CQE_RES_FORMAT_CSUM;
	हाल MLX5_IB_CQE_RES_FORMAT_CSUM_STRIDX:
		अगर (MLX5_CAP_GEN(dev->mdev, mini_cqe_resp_stride_index))
			वापस MLX5_CQE_RES_FORMAT_CSUM_STRIDX;
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक create_cq_user(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_udata *udata,
			  काष्ठा mlx5_ib_cq *cq, पूर्णांक entries, u32 **cqb,
			  पूर्णांक *cqe_size, पूर्णांक *index, पूर्णांक *inlen)
अणु
	काष्ठा mlx5_ib_create_cq ucmd = अणुपूर्ण;
	अचिन्हित दीर्घ page_size;
	अचिन्हित पूर्णांक page_offset_quantized;
	माप_प्रकार ucmdlen;
	__be64 *pas;
	पूर्णांक ncont;
	व्योम *cqc;
	पूर्णांक err;
	काष्ठा mlx5_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	ucmdlen = min(udata->inlen, माप(ucmd));
	अगर (ucmdlen < दुरत्व(काष्ठा mlx5_ib_create_cq, flags))
		वापस -EINVAL;

	अगर (ib_copy_from_udata(&ucmd, udata, ucmdlen))
		वापस -EFAULT;

	अगर ((ucmd.flags & ~(MLX5_IB_CREATE_CQ_FLAGS_CQE_128B_PAD |
			    MLX5_IB_CREATE_CQ_FLAGS_UAR_PAGE_INDEX)))
		वापस -EINVAL;

	अगर ((ucmd.cqe_size != 64 && ucmd.cqe_size != 128) ||
	    ucmd.reserved0 || ucmd.reserved1)
		वापस -EINVAL;

	*cqe_size = ucmd.cqe_size;

	cq->buf.umem =
		ib_umem_get(&dev->ib_dev, ucmd.buf_addr,
			    entries * ucmd.cqe_size, IB_ACCESS_LOCAL_WRITE);
	अगर (IS_ERR(cq->buf.umem)) अणु
		err = PTR_ERR(cq->buf.umem);
		वापस err;
	पूर्ण

	page_size = mlx5_umem_find_best_cq_quantized_pgoff(
		cq->buf.umem, cqc, log_page_size, MLX5_ADAPTER_PAGE_SHIFT,
		page_offset, 64, &page_offset_quantized);
	अगर (!page_size) अणु
		err = -EINVAL;
		जाओ err_umem;
	पूर्ण

	err = mlx5_ib_db_map_user(context, udata, ucmd.db_addr, &cq->db);
	अगर (err)
		जाओ err_umem;

	ncont = ib_umem_num_dma_blocks(cq->buf.umem, page_size);
	mlx5_ib_dbg(
		dev,
		"addr 0x%llx, size %u, npages %zu, page_size %lu, ncont %d\n",
		ucmd.buf_addr, entries * ucmd.cqe_size,
		ib_umem_num_pages(cq->buf.umem), page_size, ncont);

	*inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		 MLX5_FLD_SZ_BYTES(create_cq_in, pas[0]) * ncont;
	*cqb = kvzalloc(*inlen, GFP_KERNEL);
	अगर (!*cqb) अणु
		err = -ENOMEM;
		जाओ err_db;
	पूर्ण

	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, *cqb, pas);
	mlx5_ib_populate_pas(cq->buf.umem, page_size, pas, 0);

	cqc = MLX5_ADDR_OF(create_cq_in, *cqb, cq_context);
	MLX5_SET(cqc, cqc, log_page_size,
		 order_base_2(page_size) - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(cqc, cqc, page_offset, page_offset_quantized);

	अगर (ucmd.flags & MLX5_IB_CREATE_CQ_FLAGS_UAR_PAGE_INDEX) अणु
		*index = ucmd.uar_page_index;
	पूर्ण अन्यथा अगर (context->bfregi.lib_uar_dyn) अणु
		err = -EINVAL;
		जाओ err_cqb;
	पूर्ण अन्यथा अणु
		*index = context->bfregi.sys_pages[0];
	पूर्ण

	अगर (ucmd.cqe_comp_en == 1) अणु
		पूर्णांक mini_cqe_क्रमmat;

		अगर (!((*cqe_size == 128 &&
		       MLX5_CAP_GEN(dev->mdev, cqe_compression_128)) ||
		      (*cqe_size == 64  &&
		       MLX5_CAP_GEN(dev->mdev, cqe_compression)))) अणु
			err = -EOPNOTSUPP;
			mlx5_ib_warn(dev, "CQE compression is not supported for size %d!\n",
				     *cqe_size);
			जाओ err_cqb;
		पूर्ण

		mini_cqe_क्रमmat =
			mini_cqe_res_क्रमmat_to_hw(dev,
						  ucmd.cqe_comp_res_क्रमmat);
		अगर (mini_cqe_क्रमmat < 0) अणु
			err = mini_cqe_क्रमmat;
			mlx5_ib_dbg(dev, "CQE compression res format %d error: %d\n",
				    ucmd.cqe_comp_res_क्रमmat, err);
			जाओ err_cqb;
		पूर्ण

		MLX5_SET(cqc, cqc, cqe_comp_en, 1);
		MLX5_SET(cqc, cqc, mini_cqe_res_क्रमmat, mini_cqe_क्रमmat);
	पूर्ण

	अगर (ucmd.flags & MLX5_IB_CREATE_CQ_FLAGS_CQE_128B_PAD) अणु
		अगर (*cqe_size != 128 ||
		    !MLX5_CAP_GEN(dev->mdev, cqe_128_always)) अणु
			err = -EOPNOTSUPP;
			mlx5_ib_warn(dev,
				     "CQE padding is not supported for CQE size of %dB!\n",
				     *cqe_size);
			जाओ err_cqb;
		पूर्ण

		cq->निजी_flags |= MLX5_IB_CQ_PR_FLAGS_CQE_128_PAD;
	पूर्ण

	MLX5_SET(create_cq_in, *cqb, uid, context->devx_uid);
	वापस 0;

err_cqb:
	kvमुक्त(*cqb);

err_db:
	mlx5_ib_db_unmap_user(context, &cq->db);

err_umem:
	ib_umem_release(cq->buf.umem);
	वापस err;
पूर्ण

अटल व्योम destroy_cq_user(काष्ठा mlx5_ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	mlx5_ib_db_unmap_user(context, &cq->db);
	ib_umem_release(cq->buf.umem);
पूर्ण

अटल व्योम init_cq_frag_buf(काष्ठा mlx5_ib_cq_buf *buf)
अणु
	पूर्णांक i;
	व्योम *cqe;
	काष्ठा mlx5_cqe64 *cqe64;

	क्रम (i = 0; i < buf->nent; i++) अणु
		cqe = mlx5_frag_buf_get_wqe(&buf->fbc, i);
		cqe64 = buf->cqe_size == 64 ? cqe : cqe + 64;
		cqe64->op_own = MLX5_CQE_INVALID << 4;
	पूर्ण
पूर्ण

अटल पूर्णांक create_cq_kernel(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *cq,
			    पूर्णांक entries, पूर्णांक cqe_size,
			    u32 **cqb, पूर्णांक *index, पूर्णांक *inlen)
अणु
	__be64 *pas;
	व्योम *cqc;
	पूर्णांक err;

	err = mlx5_db_alloc(dev->mdev, &cq->db);
	अगर (err)
		वापस err;

	cq->mcq.set_ci_db  = cq->db.db;
	cq->mcq.arm_db     = cq->db.db + 1;
	cq->mcq.cqe_sz = cqe_size;

	err = alloc_cq_frag_buf(dev, &cq->buf, entries, cqe_size);
	अगर (err)
		जाओ err_db;

	init_cq_frag_buf(&cq->buf);

	*inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		 MLX5_FLD_SZ_BYTES(create_cq_in, pas[0]) *
		 cq->buf.frag_buf.npages;
	*cqb = kvzalloc(*inlen, GFP_KERNEL);
	अगर (!*cqb) अणु
		err = -ENOMEM;
		जाओ err_buf;
	पूर्ण

	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, *cqb, pas);
	mlx5_fill_page_frag_array(&cq->buf.frag_buf, pas);

	cqc = MLX5_ADDR_OF(create_cq_in, *cqb, cq_context);
	MLX5_SET(cqc, cqc, log_page_size,
		 cq->buf.frag_buf.page_shअगरt -
		 MLX5_ADAPTER_PAGE_SHIFT);

	*index = dev->mdev->priv.uar->index;

	वापस 0;

err_buf:
	मुक्त_cq_buf(dev, &cq->buf);

err_db:
	mlx5_db_मुक्त(dev->mdev, &cq->db);
	वापस err;
पूर्ण

अटल व्योम destroy_cq_kernel(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *cq)
अणु
	मुक्त_cq_buf(dev, &cq->buf);
	mlx5_db_मुक्त(dev->mdev, &cq->db);
पूर्ण

अटल व्योम notअगरy_soft_wc_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_ib_cq *cq = container_of(work, काष्ठा mlx5_ib_cq,
					     notअगरy_work);

	cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
पूर्ण

पूर्णांक mlx5_ib_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		      काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	पूर्णांक entries = attr->cqe;
	पूर्णांक vector = attr->comp_vector;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_ib_cq *cq = to_mcq(ibcq);
	u32 out[MLX5_ST_SZ_DW(create_cq_out)];
	पूर्णांक index;
	पूर्णांक inlen;
	u32 *cqb = शून्य;
	व्योम *cqc;
	पूर्णांक cqe_size;
	अचिन्हित पूर्णांक irqn;
	पूर्णांक eqn;
	पूर्णांक err;

	अगर (entries < 0 ||
	    (entries > (1 << MLX5_CAP_GEN(dev->mdev, log_max_cq_sz))))
		वापस -EINVAL;

	अगर (check_cq_create_flags(attr->flags))
		वापस -EOPNOTSUPP;

	entries = roundup_घात_of_two(entries + 1);
	अगर (entries > (1 << MLX5_CAP_GEN(dev->mdev, log_max_cq_sz)))
		वापस -EINVAL;

	cq->ibcq.cqe = entries - 1;
	mutex_init(&cq->resize_mutex);
	spin_lock_init(&cq->lock);
	cq->resize_buf = शून्य;
	cq->resize_umem = शून्य;
	cq->create_flags = attr->flags;
	INIT_LIST_HEAD(&cq->list_send_qp);
	INIT_LIST_HEAD(&cq->list_recv_qp);

	अगर (udata) अणु
		err = create_cq_user(dev, udata, cq, entries, &cqb, &cqe_size,
				     &index, &inlen);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		cqe_size = cache_line_size() == 128 ? 128 : 64;
		err = create_cq_kernel(dev, cq, entries, cqe_size, &cqb,
				       &index, &inlen);
		अगर (err)
			वापस err;

		INIT_WORK(&cq->notअगरy_work, notअगरy_soft_wc_handler);
	पूर्ण

	err = mlx5_vector2eqn(dev->mdev, vector, &eqn, &irqn);
	अगर (err)
		जाओ err_cqb;

	cq->cqe_size = cqe_size;

	cqc = MLX5_ADDR_OF(create_cq_in, cqb, cq_context);
	MLX5_SET(cqc, cqc, cqe_sz,
		 cqe_sz_to_mlx_sz(cqe_size,
				  cq->निजी_flags &
				  MLX5_IB_CQ_PR_FLAGS_CQE_128_PAD));
	MLX5_SET(cqc, cqc, log_cq_size, ilog2(entries));
	MLX5_SET(cqc, cqc, uar_page, index);
	MLX5_SET(cqc, cqc, c_eqn, eqn);
	MLX5_SET64(cqc, cqc, dbr_addr, cq->db.dma);
	अगर (cq->create_flags & IB_UVERBS_CQ_FLAGS_IGNORE_OVERRUN)
		MLX5_SET(cqc, cqc, oi, 1);

	err = mlx5_core_create_cq(dev->mdev, &cq->mcq, cqb, inlen, out, माप(out));
	अगर (err)
		जाओ err_cqb;

	mlx5_ib_dbg(dev, "cqn 0x%x\n", cq->mcq.cqn);
	cq->mcq.irqn = irqn;
	अगर (udata)
		cq->mcq.tasklet_ctx.comp = mlx5_ib_cq_comp;
	अन्यथा
		cq->mcq.comp  = mlx5_ib_cq_comp;
	cq->mcq.event = mlx5_ib_cq_event;

	INIT_LIST_HEAD(&cq->wc_list);

	अगर (udata)
		अगर (ib_copy_to_udata(udata, &cq->mcq.cqn, माप(__u32))) अणु
			err = -EFAULT;
			जाओ err_cmd;
		पूर्ण


	kvमुक्त(cqb);
	वापस 0;

err_cmd:
	mlx5_core_destroy_cq(dev->mdev, &cq->mcq);

err_cqb:
	kvमुक्त(cqb);
	अगर (udata)
		destroy_cq_user(cq, udata);
	अन्यथा
		destroy_cq_kernel(dev, cq);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->device);
	काष्ठा mlx5_ib_cq *mcq = to_mcq(cq);
	पूर्णांक ret;

	ret = mlx5_core_destroy_cq(dev->mdev, &mcq->mcq);
	अगर (ret)
		वापस ret;

	अगर (udata)
		destroy_cq_user(mcq, udata);
	अन्यथा
		destroy_cq_kernel(dev, mcq);
	वापस 0;
पूर्ण

अटल पूर्णांक is_equal_rsn(काष्ठा mlx5_cqe64 *cqe64, u32 rsn)
अणु
	वापस rsn == (ntohl(cqe64->sop_drop_qpn) & 0xffffff);
पूर्ण

व्योम __mlx5_ib_cq_clean(काष्ठा mlx5_ib_cq *cq, u32 rsn, काष्ठा mlx5_ib_srq *srq)
अणु
	काष्ठा mlx5_cqe64 *cqe64, *dest64;
	व्योम *cqe, *dest;
	u32 prod_index;
	पूर्णांक nमुक्तd = 0;
	u8 owner_bit;

	अगर (!cq)
		वापस;

	/* First we need to find the current producer index, so we
	 * know where to start cleaning from.  It करोesn't matter अगर HW
	 * adds new entries after this loop -- the QP we're worried
	 * about is alपढ़ोy in RESET, so the new entries won't come
	 * from our QP and thereक्रमe करोn't need to be checked.
	 */
	क्रम (prod_index = cq->mcq.cons_index; get_sw_cqe(cq, prod_index); prod_index++)
		अगर (prod_index == cq->mcq.cons_index + cq->ibcq.cqe)
			अवरोध;

	/* Now sweep backwards through the CQ, removing CQ entries
	 * that match our QP by copying older entries on top of them.
	 */
	जबतक ((पूर्णांक) --prod_index - (पूर्णांक) cq->mcq.cons_index >= 0) अणु
		cqe = get_cqe(cq, prod_index & cq->ibcq.cqe);
		cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;
		अगर (is_equal_rsn(cqe64, rsn)) अणु
			अगर (srq && (ntohl(cqe64->srqn) & 0xffffff))
				mlx5_ib_मुक्त_srq_wqe(srq, be16_to_cpu(cqe64->wqe_counter));
			++nमुक्तd;
		पूर्ण अन्यथा अगर (nमुक्तd) अणु
			dest = get_cqe(cq, (prod_index + nमुक्तd) & cq->ibcq.cqe);
			dest64 = (cq->mcq.cqe_sz == 64) ? dest : dest + 64;
			owner_bit = dest64->op_own & MLX5_CQE_OWNER_MASK;
			स_नकल(dest, cqe, cq->mcq.cqe_sz);
			dest64->op_own = owner_bit |
				(dest64->op_own & ~MLX5_CQE_OWNER_MASK);
		पूर्ण
	पूर्ण

	अगर (nमुक्तd) अणु
		cq->mcq.cons_index += nमुक्तd;
		/* Make sure update of buffer contents is करोne beक्रमe
		 * updating consumer index.
		 */
		wmb();
		mlx5_cq_set_ci(&cq->mcq);
	पूर्ण
पूर्ण

व्योम mlx5_ib_cq_clean(काष्ठा mlx5_ib_cq *cq, u32 qpn, काष्ठा mlx5_ib_srq *srq)
अणु
	अगर (!cq)
		वापस;

	spin_lock_irq(&cq->lock);
	__mlx5_ib_cq_clean(cq, qpn, srq);
	spin_unlock_irq(&cq->lock);
पूर्ण

पूर्णांक mlx5_ib_modअगरy_cq(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->device);
	काष्ठा mlx5_ib_cq *mcq = to_mcq(cq);
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev->mdev, cq_moderation))
		वापस -EOPNOTSUPP;

	अगर (cq_period > MLX5_MAX_CQ_PERIOD)
		वापस -EINVAL;

	err = mlx5_core_modअगरy_cq_moderation(dev->mdev, &mcq->mcq,
					     cq_period, cq_count);
	अगर (err)
		mlx5_ib_warn(dev, "modify cq 0x%x failed\n", mcq->mcq.cqn);

	वापस err;
पूर्ण

अटल पूर्णांक resize_user(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *cq,
		       पूर्णांक entries, काष्ठा ib_udata *udata,
		       पूर्णांक *cqe_size)
अणु
	काष्ठा mlx5_ib_resize_cq ucmd;
	काष्ठा ib_umem *umem;
	पूर्णांक err;

	err = ib_copy_from_udata(&ucmd, udata, माप(ucmd));
	अगर (err)
		वापस err;

	अगर (ucmd.reserved0 || ucmd.reserved1)
		वापस -EINVAL;

	/* check multiplication overflow */
	अगर (ucmd.cqe_size && SIZE_MAX / ucmd.cqe_size <= entries - 1)
		वापस -EINVAL;

	umem = ib_umem_get(&dev->ib_dev, ucmd.buf_addr,
			   (माप_प्रकार)ucmd.cqe_size * entries,
			   IB_ACCESS_LOCAL_WRITE);
	अगर (IS_ERR(umem)) अणु
		err = PTR_ERR(umem);
		वापस err;
	पूर्ण

	cq->resize_umem = umem;
	*cqe_size = ucmd.cqe_size;

	वापस 0;
पूर्ण

अटल पूर्णांक resize_kernel(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *cq,
			 पूर्णांक entries, पूर्णांक cqe_size)
अणु
	पूर्णांक err;

	cq->resize_buf = kzalloc(माप(*cq->resize_buf), GFP_KERNEL);
	अगर (!cq->resize_buf)
		वापस -ENOMEM;

	err = alloc_cq_frag_buf(dev, cq->resize_buf, entries, cqe_size);
	अगर (err)
		जाओ ex;

	init_cq_frag_buf(cq->resize_buf);

	वापस 0;

ex:
	kमुक्त(cq->resize_buf);
	वापस err;
पूर्ण

अटल पूर्णांक copy_resize_cqes(काष्ठा mlx5_ib_cq *cq)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	काष्ठा mlx5_cqe64 *scqe64;
	काष्ठा mlx5_cqe64 *dcqe64;
	व्योम *start_cqe;
	व्योम *scqe;
	व्योम *dcqe;
	पूर्णांक ssize;
	पूर्णांक dsize;
	पूर्णांक i;
	u8 sw_own;

	ssize = cq->buf.cqe_size;
	dsize = cq->resize_buf->cqe_size;
	अगर (ssize != dsize) अणु
		mlx5_ib_warn(dev, "resize from different cqe size is not supported\n");
		वापस -EINVAL;
	पूर्ण

	i = cq->mcq.cons_index;
	scqe = get_sw_cqe(cq, i);
	scqe64 = ssize == 64 ? scqe : scqe + 64;
	start_cqe = scqe;
	अगर (!scqe) अणु
		mlx5_ib_warn(dev, "expected cqe in sw ownership\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (get_cqe_opcode(scqe64) != MLX5_CQE_RESIZE_CQ) अणु
		dcqe = mlx5_frag_buf_get_wqe(&cq->resize_buf->fbc,
					     (i + 1) & cq->resize_buf->nent);
		dcqe64 = dsize == 64 ? dcqe : dcqe + 64;
		sw_own = sw_ownership_bit(i + 1, cq->resize_buf->nent);
		स_नकल(dcqe, scqe, dsize);
		dcqe64->op_own = (dcqe64->op_own & ~MLX5_CQE_OWNER_MASK) | sw_own;

		++i;
		scqe = get_sw_cqe(cq, i);
		scqe64 = ssize == 64 ? scqe : scqe + 64;
		अगर (!scqe) अणु
			mlx5_ib_warn(dev, "expected cqe in sw ownership\n");
			वापस -EINVAL;
		पूर्ण

		अगर (scqe == start_cqe) अणु
			pr_warn("resize CQ failed to get resize CQE, CQN 0x%x\n",
				cq->mcq.cqn);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	++cq->mcq.cons_index;
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक entries, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibcq->device);
	काष्ठा mlx5_ib_cq *cq = to_mcq(ibcq);
	व्योम *cqc;
	u32 *in;
	पूर्णांक err;
	पूर्णांक npas;
	__be64 *pas;
	अचिन्हित पूर्णांक page_offset_quantized = 0;
	अचिन्हित पूर्णांक page_shअगरt;
	पूर्णांक inlen;
	पूर्णांक cqe_size;
	अचिन्हित दीर्घ flags;

	अगर (!MLX5_CAP_GEN(dev->mdev, cq_resize)) अणु
		pr_info("Firmware does not support resize CQ\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (entries < 1 ||
	    entries > (1 << MLX5_CAP_GEN(dev->mdev, log_max_cq_sz))) अणु
		mlx5_ib_warn(dev, "wrong entries number %d, max %d\n",
			     entries,
			     1 << MLX5_CAP_GEN(dev->mdev, log_max_cq_sz));
		वापस -EINVAL;
	पूर्ण

	entries = roundup_घात_of_two(entries + 1);
	अगर (entries > (1 << MLX5_CAP_GEN(dev->mdev, log_max_cq_sz)) + 1)
		वापस -EINVAL;

	अगर (entries == ibcq->cqe + 1)
		वापस 0;

	mutex_lock(&cq->resize_mutex);
	अगर (udata) अणु
		अचिन्हित दीर्घ page_size;

		err = resize_user(dev, cq, entries, udata, &cqe_size);
		अगर (err)
			जाओ ex;

		page_size = mlx5_umem_find_best_cq_quantized_pgoff(
			cq->resize_umem, cqc, log_page_size,
			MLX5_ADAPTER_PAGE_SHIFT, page_offset, 64,
			&page_offset_quantized);
		अगर (!page_size) अणु
			err = -EINVAL;
			जाओ ex_resize;
		पूर्ण
		npas = ib_umem_num_dma_blocks(cq->resize_umem, page_size);
		page_shअगरt = order_base_2(page_size);
	पूर्ण अन्यथा अणु
		काष्ठा mlx5_frag_buf *frag_buf;

		cqe_size = 64;
		err = resize_kernel(dev, cq, entries, cqe_size);
		अगर (err)
			जाओ ex;
		frag_buf = &cq->resize_buf->frag_buf;
		npas = frag_buf->npages;
		page_shअगरt = frag_buf->page_shअगरt;
	पूर्ण

	inlen = MLX5_ST_SZ_BYTES(modअगरy_cq_in) +
		MLX5_FLD_SZ_BYTES(modअगरy_cq_in, pas[0]) * npas;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ ex_resize;
	पूर्ण

	pas = (__be64 *)MLX5_ADDR_OF(modअगरy_cq_in, in, pas);
	अगर (udata)
		mlx5_ib_populate_pas(cq->resize_umem, 1UL << page_shअगरt, pas,
				     0);
	अन्यथा
		mlx5_fill_page_frag_array(&cq->resize_buf->frag_buf, pas);

	MLX5_SET(modअगरy_cq_in, in,
		 modअगरy_field_select_resize_field_select.resize_field_select.resize_field_select,
		 MLX5_MODIFY_CQ_MASK_LOG_SIZE  |
		 MLX5_MODIFY_CQ_MASK_PG_OFFSET |
		 MLX5_MODIFY_CQ_MASK_PG_SIZE);

	cqc = MLX5_ADDR_OF(modअगरy_cq_in, in, cq_context);

	MLX5_SET(cqc, cqc, log_page_size,
		 page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(cqc, cqc, page_offset, page_offset_quantized);
	MLX5_SET(cqc, cqc, cqe_sz,
		 cqe_sz_to_mlx_sz(cqe_size,
				  cq->निजी_flags &
				  MLX5_IB_CQ_PR_FLAGS_CQE_128_PAD));
	MLX5_SET(cqc, cqc, log_cq_size, ilog2(entries));

	MLX5_SET(modअगरy_cq_in, in, op_mod, MLX5_CQ_OPMOD_RESIZE);
	MLX5_SET(modअगरy_cq_in, in, cqn, cq->mcq.cqn);

	err = mlx5_core_modअगरy_cq(dev->mdev, &cq->mcq, in, inlen);
	अगर (err)
		जाओ ex_alloc;

	अगर (udata) अणु
		cq->ibcq.cqe = entries - 1;
		ib_umem_release(cq->buf.umem);
		cq->buf.umem = cq->resize_umem;
		cq->resize_umem = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा mlx5_ib_cq_buf tbuf;
		पूर्णांक resized = 0;

		spin_lock_irqsave(&cq->lock, flags);
		अगर (cq->resize_buf) अणु
			err = copy_resize_cqes(cq);
			अगर (!err) अणु
				tbuf = cq->buf;
				cq->buf = *cq->resize_buf;
				kमुक्त(cq->resize_buf);
				cq->resize_buf = शून्य;
				resized = 1;
			पूर्ण
		पूर्ण
		cq->ibcq.cqe = entries - 1;
		spin_unlock_irqrestore(&cq->lock, flags);
		अगर (resized)
			मुक्त_cq_buf(dev, &tbuf);
	पूर्ण
	mutex_unlock(&cq->resize_mutex);

	kvमुक्त(in);
	वापस 0;

ex_alloc:
	kvमुक्त(in);

ex_resize:
	ib_umem_release(cq->resize_umem);
	अगर (!udata) अणु
		मुक्त_cq_buf(dev, cq->resize_buf);
		cq->resize_buf = शून्य;
	पूर्ण
ex:
	mutex_unlock(&cq->resize_mutex);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_get_cqe_size(काष्ठा ib_cq *ibcq)
अणु
	काष्ठा mlx5_ib_cq *cq;

	अगर (!ibcq)
		वापस 128;

	cq = to_mcq(ibcq);
	वापस cq->cqe_size;
पूर्ण

/* Called from atomic context */
पूर्णांक mlx5_ib_generate_wc(काष्ठा ib_cq *ibcq, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_wc *soft_wc;
	काष्ठा mlx5_ib_cq *cq = to_mcq(ibcq);
	अचिन्हित दीर्घ flags;

	soft_wc = kदो_स्मृति(माप(*soft_wc), GFP_ATOMIC);
	अगर (!soft_wc)
		वापस -ENOMEM;

	soft_wc->wc = *wc;
	spin_lock_irqsave(&cq->lock, flags);
	list_add_tail(&soft_wc->list, &cq->wc_list);
	अगर (cq->notअगरy_flags == IB_CQ_NEXT_COMP ||
	    wc->status != IB_WC_SUCCESS) अणु
		cq->notअगरy_flags = 0;
		schedule_work(&cq->notअगरy_work);
	पूर्ण
	spin_unlock_irqrestore(&cq->lock, flags);

	वापस 0;
पूर्ण
