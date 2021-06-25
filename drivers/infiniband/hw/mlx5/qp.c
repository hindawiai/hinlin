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

#समावेश <linux/module.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/rdma_counter.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "mlx5_ib.h"
#समावेश "ib_rep.h"
#समावेश "counters.h"
#समावेश "cmd.h"
#समावेश "qp.h"
#समावेश "wr.h"

क्रमागत अणु
	MLX5_IB_ACK_REQ_FREQ	= 8,
पूर्ण;

क्रमागत अणु
	MLX5_IB_DEFAULT_SCHED_QUEUE	= 0x83,
	MLX5_IB_DEFAULT_QP0_SCHED_QUEUE	= 0x3f,
	MLX5_IB_LINK_TYPE_IB		= 0,
	MLX5_IB_LINK_TYPE_ETH		= 1
पूर्ण;

क्रमागत raw_qp_set_mask_map अणु
	MLX5_RAW_QP_MOD_SET_RQ_Q_CTR_ID		= 1UL << 0,
	MLX5_RAW_QP_RATE_LIMIT			= 1UL << 1,
पूर्ण;

काष्ठा mlx5_modअगरy_raw_qp_param अणु
	u16 operation;

	u32 set_mask; /* raw_qp_set_mask_map */

	काष्ठा mlx5_rate_limit rl;

	u8 rq_q_ctr_id;
	u32 port;
पूर्ण;

अटल व्योम get_cqs(क्रमागत ib_qp_type qp_type,
		    काष्ठा ib_cq *ib_send_cq, काष्ठा ib_cq *ib_recv_cq,
		    काष्ठा mlx5_ib_cq **send_cq, काष्ठा mlx5_ib_cq **recv_cq);

अटल पूर्णांक is_qp0(क्रमागत ib_qp_type qp_type)
अणु
	वापस qp_type == IB_QPT_SMI;
पूर्ण

अटल पूर्णांक is_sqp(क्रमागत ib_qp_type qp_type)
अणु
	वापस is_qp0(qp_type) || is_qp1(qp_type);
पूर्ण

/**
 * mlx5_ib_पढ़ो_user_wqe_common() - Copy a WQE (or part of) from user WQ
 * to kernel buffer
 *
 * @umem: User space memory where the WQ is
 * @buffer: buffer to copy to
 * @buflen: buffer length
 * @wqe_index: index of WQE to copy from
 * @wq_offset: offset to start of WQ
 * @wq_wqe_cnt: number of WQEs in WQ
 * @wq_wqe_shअगरt: log2 of WQE size
 * @bcnt: number of bytes to copy
 * @bytes_copied: number of bytes to copy (वापस value)
 *
 * Copies from start of WQE bcnt or less bytes.
 * Does not gurantee to copy the entire WQE.
 *
 * Return: zero on success, or an error code.
 */
अटल पूर्णांक mlx5_ib_पढ़ो_user_wqe_common(काष्ठा ib_umem *umem, व्योम *buffer,
					माप_प्रकार buflen, पूर्णांक wqe_index,
					पूर्णांक wq_offset, पूर्णांक wq_wqe_cnt,
					पूर्णांक wq_wqe_shअगरt, पूर्णांक bcnt,
					माप_प्रकार *bytes_copied)
अणु
	माप_प्रकार offset = wq_offset + ((wqe_index % wq_wqe_cnt) << wq_wqe_shअगरt);
	माप_प्रकार wq_end = wq_offset + (wq_wqe_cnt << wq_wqe_shअगरt);
	माप_प्रकार copy_length;
	पूर्णांक ret;

	/* करोn't copy more than requested, more than buffer length or
	 * beyond WQ end
	 */
	copy_length = min_t(u32, buflen, wq_end - offset);
	copy_length = min_t(u32, copy_length, bcnt);

	ret = ib_umem_copy_from(buffer, umem, offset, copy_length);
	अगर (ret)
		वापस ret;

	अगर (!ret && bytes_copied)
		*bytes_copied = copy_length;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_पढ़ो_kernel_wqe_sq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index,
				      व्योम *buffer, माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *ctrl;
	माप_प्रकार bytes_copied = 0;
	माप_प्रकार wqe_length;
	व्योम *p;
	पूर्णांक ds;

	wqe_index = wqe_index & qp->sq.fbc.sz_m1;

	/* पढ़ो the control segment first */
	p = mlx5_frag_buf_get_wqe(&qp->sq.fbc, wqe_index);
	ctrl = p;
	ds = be32_to_cpu(ctrl->qpn_ds) & MLX5_WQE_CTRL_DS_MASK;
	wqe_length = ds * MLX5_WQE_DS_UNITS;

	/* पढ़ो rest of WQE अगर it spपढ़ोs over more than one stride */
	जबतक (bytes_copied < wqe_length) अणु
		माप_प्रकार copy_length =
			min_t(माप_प्रकार, buflen - bytes_copied, MLX5_SEND_WQE_BB);

		अगर (!copy_length)
			अवरोध;

		स_नकल(buffer + bytes_copied, p, copy_length);
		bytes_copied += copy_length;

		wqe_index = (wqe_index + 1) & qp->sq.fbc.sz_m1;
		p = mlx5_frag_buf_get_wqe(&qp->sq.fbc, wqe_index);
	पूर्ण
	*bc = bytes_copied;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_पढ़ो_user_wqe_sq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index,
				    व्योम *buffer, माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा mlx5_ib_qp_base *base = &qp->trans_qp.base;
	काष्ठा ib_umem *umem = base->ubuffer.umem;
	काष्ठा mlx5_ib_wq *wq = &qp->sq;
	काष्ठा mlx5_wqe_ctrl_seg *ctrl;
	माप_प्रकार bytes_copied;
	माप_प्रकार bytes_copied2;
	माप_प्रकार wqe_length;
	पूर्णांक ret;
	पूर्णांक ds;

	/* at first पढ़ो as much as possible */
	ret = mlx5_ib_पढ़ो_user_wqe_common(umem, buffer, buflen, wqe_index,
					   wq->offset, wq->wqe_cnt,
					   wq->wqe_shअगरt, buflen,
					   &bytes_copied);
	अगर (ret)
		वापस ret;

	/* we need at least control segment size to proceed */
	अगर (bytes_copied < माप(*ctrl))
		वापस -EINVAL;

	ctrl = buffer;
	ds = be32_to_cpu(ctrl->qpn_ds) & MLX5_WQE_CTRL_DS_MASK;
	wqe_length = ds * MLX5_WQE_DS_UNITS;

	/* अगर we copied enough then we are करोne */
	अगर (bytes_copied >= wqe_length) अणु
		*bc = bytes_copied;
		वापस 0;
	पूर्ण

	/* otherwise this a wrapped around wqe
	 * so पढ़ो the reमुख्यing bytes starting
	 * from  wqe_index 0
	 */
	ret = mlx5_ib_पढ़ो_user_wqe_common(umem, buffer + bytes_copied,
					   buflen - bytes_copied, 0, wq->offset,
					   wq->wqe_cnt, wq->wqe_shअगरt,
					   wqe_length - bytes_copied,
					   &bytes_copied2);

	अगर (ret)
		वापस ret;
	*bc = bytes_copied + bytes_copied2;
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_पढ़ो_wqe_sq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index, व्योम *buffer,
			माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा mlx5_ib_qp_base *base = &qp->trans_qp.base;
	काष्ठा ib_umem *umem = base->ubuffer.umem;

	अगर (buflen < माप(काष्ठा mlx5_wqe_ctrl_seg))
		वापस -EINVAL;

	अगर (!umem)
		वापस mlx5_ib_पढ़ो_kernel_wqe_sq(qp, wqe_index, buffer,
						  buflen, bc);

	वापस mlx5_ib_पढ़ो_user_wqe_sq(qp, wqe_index, buffer, buflen, bc);
पूर्ण

अटल पूर्णांक mlx5_ib_पढ़ो_user_wqe_rq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index,
				    व्योम *buffer, माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा mlx5_ib_qp_base *base = &qp->trans_qp.base;
	काष्ठा ib_umem *umem = base->ubuffer.umem;
	काष्ठा mlx5_ib_wq *wq = &qp->rq;
	माप_प्रकार bytes_copied;
	पूर्णांक ret;

	ret = mlx5_ib_पढ़ो_user_wqe_common(umem, buffer, buflen, wqe_index,
					   wq->offset, wq->wqe_cnt,
					   wq->wqe_shअगरt, buflen,
					   &bytes_copied);

	अगर (ret)
		वापस ret;
	*bc = bytes_copied;
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_पढ़ो_wqe_rq(काष्ठा mlx5_ib_qp *qp, पूर्णांक wqe_index, व्योम *buffer,
			माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा mlx5_ib_qp_base *base = &qp->trans_qp.base;
	काष्ठा ib_umem *umem = base->ubuffer.umem;
	काष्ठा mlx5_ib_wq *wq = &qp->rq;
	माप_प्रकार wqe_size = 1 << wq->wqe_shअगरt;

	अगर (buflen < wqe_size)
		वापस -EINVAL;

	अगर (!umem)
		वापस -EOPNOTSUPP;

	वापस mlx5_ib_पढ़ो_user_wqe_rq(qp, wqe_index, buffer, buflen, bc);
पूर्ण

अटल पूर्णांक mlx5_ib_पढ़ो_user_wqe_srq(काष्ठा mlx5_ib_srq *srq, पूर्णांक wqe_index,
				     व्योम *buffer, माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा ib_umem *umem = srq->umem;
	माप_प्रकार bytes_copied;
	पूर्णांक ret;

	ret = mlx5_ib_पढ़ो_user_wqe_common(umem, buffer, buflen, wqe_index, 0,
					   srq->msrq.max, srq->msrq.wqe_shअगरt,
					   buflen, &bytes_copied);

	अगर (ret)
		वापस ret;
	*bc = bytes_copied;
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_पढ़ो_wqe_srq(काष्ठा mlx5_ib_srq *srq, पूर्णांक wqe_index, व्योम *buffer,
			 माप_प्रकार buflen, माप_प्रकार *bc)
अणु
	काष्ठा ib_umem *umem = srq->umem;
	माप_प्रकार wqe_size = 1 << srq->msrq.wqe_shअगरt;

	अगर (buflen < wqe_size)
		वापस -EINVAL;

	अगर (!umem)
		वापस -EOPNOTSUPP;

	वापस mlx5_ib_पढ़ो_user_wqe_srq(srq, wqe_index, buffer, buflen, bc);
पूर्ण

अटल व्योम mlx5_ib_qp_event(काष्ठा mlx5_core_qp *qp, पूर्णांक type)
अणु
	काष्ठा ib_qp *ibqp = &to_mibqp(qp)->ibqp;
	काष्ठा ib_event event;

	अगर (type == MLX5_EVENT_TYPE_PATH_MIG) अणु
		/* This event is only valid क्रम trans_qps */
		to_mibqp(qp)->port = to_mibqp(qp)->trans_qp.alt_port;
	पूर्ण

	अगर (ibqp->event_handler) अणु
		event.device     = ibqp->device;
		event.element.qp = ibqp;
		चयन (type) अणु
		हाल MLX5_EVENT_TYPE_PATH_MIG:
			event.event = IB_EVENT_PATH_MIG;
			अवरोध;
		हाल MLX5_EVENT_TYPE_COMM_EST:
			event.event = IB_EVENT_COMM_EST;
			अवरोध;
		हाल MLX5_EVENT_TYPE_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			अवरोध;
		हाल MLX5_EVENT_TYPE_SRQ_LAST_WQE:
			event.event = IB_EVENT_QP_LAST_WQE_REACHED;
			अवरोध;
		हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_QP_FATAL;
			अवरोध;
		हाल MLX5_EVENT_TYPE_PATH_MIG_FAILED:
			event.event = IB_EVENT_PATH_MIG_ERR;
			अवरोध;
		हाल MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
			event.event = IB_EVENT_QP_REQ_ERR;
			अवरोध;
		हाल MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			अवरोध;
		शेष:
			pr_warn("mlx5_ib: Unexpected event type %d on QP %06x\n", type, qp->qpn);
			वापस;
		पूर्ण

		ibqp->event_handler(&event, ibqp->qp_context);
	पूर्ण
पूर्ण

अटल पूर्णांक set_rq_size(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_qp_cap *cap,
		       पूर्णांक has_rq, काष्ठा mlx5_ib_qp *qp, काष्ठा mlx5_ib_create_qp *ucmd)
अणु
	पूर्णांक wqe_size;
	पूर्णांक wq_size;

	/* Sanity check RQ size beक्रमe proceeding */
	अगर (cap->max_recv_wr > (1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz)))
		वापस -EINVAL;

	अगर (!has_rq) अणु
		qp->rq.max_gs = 0;
		qp->rq.wqe_cnt = 0;
		qp->rq.wqe_shअगरt = 0;
		cap->max_recv_wr = 0;
		cap->max_recv_sge = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक wq_sig = !!(qp->flags_en & MLX5_QP_FLAG_SIGNATURE);

		अगर (ucmd) अणु
			qp->rq.wqe_cnt = ucmd->rq_wqe_count;
			अगर (ucmd->rq_wqe_shअगरt > BITS_PER_BYTE * माप(ucmd->rq_wqe_shअगरt))
				वापस -EINVAL;
			qp->rq.wqe_shअगरt = ucmd->rq_wqe_shअगरt;
			अगर ((1 << qp->rq.wqe_shअगरt) /
				    माप(काष्ठा mlx5_wqe_data_seg) <
			    wq_sig)
				वापस -EINVAL;
			qp->rq.max_gs =
				(1 << qp->rq.wqe_shअगरt) /
					माप(काष्ठा mlx5_wqe_data_seg) -
				wq_sig;
			qp->rq.max_post = qp->rq.wqe_cnt;
		पूर्ण अन्यथा अणु
			wqe_size =
				wq_sig ? माप(काष्ठा mlx5_wqe_signature_seg) :
					 0;
			wqe_size += cap->max_recv_sge * माप(काष्ठा mlx5_wqe_data_seg);
			wqe_size = roundup_घात_of_two(wqe_size);
			wq_size = roundup_घात_of_two(cap->max_recv_wr) * wqe_size;
			wq_size = max_t(पूर्णांक, wq_size, MLX5_SEND_WQE_BB);
			qp->rq.wqe_cnt = wq_size / wqe_size;
			अगर (wqe_size > MLX5_CAP_GEN(dev->mdev, max_wqe_sz_rq)) अणु
				mlx5_ib_dbg(dev, "wqe_size %d, max %d\n",
					    wqe_size,
					    MLX5_CAP_GEN(dev->mdev,
							 max_wqe_sz_rq));
				वापस -EINVAL;
			पूर्ण
			qp->rq.wqe_shअगरt = ilog2(wqe_size);
			qp->rq.max_gs =
				(1 << qp->rq.wqe_shअगरt) /
					माप(काष्ठा mlx5_wqe_data_seg) -
				wq_sig;
			qp->rq.max_post = qp->rq.wqe_cnt;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sq_overhead(काष्ठा ib_qp_init_attr *attr)
अणु
	पूर्णांक size = 0;

	चयन (attr->qp_type) अणु
	हाल IB_QPT_XRC_INI:
		size += माप(काष्ठा mlx5_wqe_xrc_seg);
		fallthrough;
	हाल IB_QPT_RC:
		size += माप(काष्ठा mlx5_wqe_ctrl_seg) +
			max(माप(काष्ठा mlx5_wqe_atomic_seg) +
			    माप(काष्ठा mlx5_wqe_raddr_seg),
			    माप(काष्ठा mlx5_wqe_umr_ctrl_seg) +
			    माप(काष्ठा mlx5_mkey_seg) +
			    MLX5_IB_SQ_UMR_INLINE_THRESHOLD /
			    MLX5_IB_UMR_OCTOWORD);
		अवरोध;

	हाल IB_QPT_XRC_TGT:
		वापस 0;

	हाल IB_QPT_UC:
		size += माप(काष्ठा mlx5_wqe_ctrl_seg) +
			max(माप(काष्ठा mlx5_wqe_raddr_seg),
			    माप(काष्ठा mlx5_wqe_umr_ctrl_seg) +
			    माप(काष्ठा mlx5_mkey_seg));
		अवरोध;

	हाल IB_QPT_UD:
		अगर (attr->create_flags & IB_QP_CREATE_IPOIB_UD_LSO)
			size += माप(काष्ठा mlx5_wqe_eth_pad) +
				माप(काष्ठा mlx5_wqe_eth_seg);
		fallthrough;
	हाल IB_QPT_SMI:
	हाल MLX5_IB_QPT_HW_GSI:
		size += माप(काष्ठा mlx5_wqe_ctrl_seg) +
			माप(काष्ठा mlx5_wqe_datagram_seg);
		अवरोध;

	हाल MLX5_IB_QPT_REG_UMR:
		size += माप(काष्ठा mlx5_wqe_ctrl_seg) +
			माप(काष्ठा mlx5_wqe_umr_ctrl_seg) +
			माप(काष्ठा mlx5_mkey_seg);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक calc_send_wqe(काष्ठा ib_qp_init_attr *attr)
अणु
	पूर्णांक inl_size = 0;
	पूर्णांक size;

	size = sq_overhead(attr);
	अगर (size < 0)
		वापस size;

	अगर (attr->cap.max_अंतरभूत_data) अणु
		inl_size = size + माप(काष्ठा mlx5_wqe_अंतरभूत_seg) +
			attr->cap.max_अंतरभूत_data;
	पूर्ण

	size += attr->cap.max_send_sge * माप(काष्ठा mlx5_wqe_data_seg);
	अगर (attr->create_flags & IB_QP_CREATE_INTEGRITY_EN &&
	    ALIGN(max_t(पूर्णांक, inl_size, size), MLX5_SEND_WQE_BB) < MLX5_SIG_WQE_SIZE)
		वापस MLX5_SIG_WQE_SIZE;
	अन्यथा
		वापस ALIGN(max_t(पूर्णांक, inl_size, size), MLX5_SEND_WQE_BB);
पूर्ण

अटल पूर्णांक get_send_sge(काष्ठा ib_qp_init_attr *attr, पूर्णांक wqe_size)
अणु
	पूर्णांक max_sge;

	अगर (attr->qp_type == IB_QPT_RC)
		max_sge = (min_t(पूर्णांक, wqe_size, 512) -
			   माप(काष्ठा mlx5_wqe_ctrl_seg) -
			   माप(काष्ठा mlx5_wqe_raddr_seg)) /
			माप(काष्ठा mlx5_wqe_data_seg);
	अन्यथा अगर (attr->qp_type == IB_QPT_XRC_INI)
		max_sge = (min_t(पूर्णांक, wqe_size, 512) -
			   माप(काष्ठा mlx5_wqe_ctrl_seg) -
			   माप(काष्ठा mlx5_wqe_xrc_seg) -
			   माप(काष्ठा mlx5_wqe_raddr_seg)) /
			माप(काष्ठा mlx5_wqe_data_seg);
	अन्यथा
		max_sge = (wqe_size - sq_overhead(attr)) /
			माप(काष्ठा mlx5_wqe_data_seg);

	वापस min_t(पूर्णांक, max_sge, wqe_size - sq_overhead(attr) /
		     माप(काष्ठा mlx5_wqe_data_seg));
पूर्ण

अटल पूर्णांक calc_sq_size(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_qp_init_attr *attr,
			काष्ठा mlx5_ib_qp *qp)
अणु
	पूर्णांक wqe_size;
	पूर्णांक wq_size;

	अगर (!attr->cap.max_send_wr)
		वापस 0;

	wqe_size = calc_send_wqe(attr);
	mlx5_ib_dbg(dev, "wqe_size %d\n", wqe_size);
	अगर (wqe_size < 0)
		वापस wqe_size;

	अगर (wqe_size > MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq)) अणु
		mlx5_ib_dbg(dev, "wqe_size(%d) > max_sq_desc_sz(%d)\n",
			    wqe_size, MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq));
		वापस -EINVAL;
	पूर्ण

	qp->max_अंतरभूत_data = wqe_size - sq_overhead(attr) -
			      माप(काष्ठा mlx5_wqe_अंतरभूत_seg);
	attr->cap.max_अंतरभूत_data = qp->max_अंतरभूत_data;

	wq_size = roundup_घात_of_two(attr->cap.max_send_wr * wqe_size);
	qp->sq.wqe_cnt = wq_size / MLX5_SEND_WQE_BB;
	अगर (qp->sq.wqe_cnt > (1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz))) अणु
		mlx5_ib_dbg(dev, "send queue size (%d * %d / %d -> %d) exceeds limits(%d)\n",
			    attr->cap.max_send_wr, wqe_size, MLX5_SEND_WQE_BB,
			    qp->sq.wqe_cnt,
			    1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz));
		वापस -ENOMEM;
	पूर्ण
	qp->sq.wqe_shअगरt = ilog2(MLX5_SEND_WQE_BB);
	qp->sq.max_gs = get_send_sge(attr, wqe_size);
	अगर (qp->sq.max_gs < attr->cap.max_send_sge)
		वापस -ENOMEM;

	attr->cap.max_send_sge = qp->sq.max_gs;
	qp->sq.max_post = wq_size / wqe_size;
	attr->cap.max_send_wr = qp->sq.max_post;

	वापस wq_size;
पूर्ण

अटल पूर्णांक set_user_buf_size(काष्ठा mlx5_ib_dev *dev,
			    काष्ठा mlx5_ib_qp *qp,
			    काष्ठा mlx5_ib_create_qp *ucmd,
			    काष्ठा mlx5_ib_qp_base *base,
			    काष्ठा ib_qp_init_attr *attr)
अणु
	पूर्णांक desc_sz = 1 << qp->sq.wqe_shअगरt;

	अगर (desc_sz > MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq)) अणु
		mlx5_ib_warn(dev, "desc_sz %d, max_sq_desc_sz %d\n",
			     desc_sz, MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq));
		वापस -EINVAL;
	पूर्ण

	अगर (ucmd->sq_wqe_count && !is_घातer_of_2(ucmd->sq_wqe_count)) अणु
		mlx5_ib_warn(dev, "sq_wqe_count %d is not a power of two\n",
			     ucmd->sq_wqe_count);
		वापस -EINVAL;
	पूर्ण

	qp->sq.wqe_cnt = ucmd->sq_wqe_count;

	अगर (qp->sq.wqe_cnt > (1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz))) अणु
		mlx5_ib_warn(dev, "wqe_cnt %d, max_wqes %d\n",
			     qp->sq.wqe_cnt,
			     1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz));
		वापस -EINVAL;
	पूर्ण

	अगर (attr->qp_type == IB_QPT_RAW_PACKET ||
	    qp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		base->ubuffer.buf_size = qp->rq.wqe_cnt << qp->rq.wqe_shअगरt;
		qp->raw_packet_qp.sq.ubuffer.buf_size = qp->sq.wqe_cnt << 6;
	पूर्ण अन्यथा अणु
		base->ubuffer.buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shअगरt) +
					 (qp->sq.wqe_cnt << 6);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qp_has_rq(काष्ठा ib_qp_init_attr *attr)
अणु
	अगर (attr->qp_type == IB_QPT_XRC_INI ||
	    attr->qp_type == IB_QPT_XRC_TGT || attr->srq ||
	    attr->qp_type == MLX5_IB_QPT_REG_UMR ||
	    !attr->cap.max_recv_wr)
		वापस 0;

	वापस 1;
पूर्ण

क्रमागत अणु
	/* this is the first blue flame रेजिस्टर in the array of bfregs asचिन्हित
	 * to a processes. Since we करो not use it क्रम blue flame but rather
	 * regular 64 bit करोorbells, we करो not need a lock क्रम मुख्यtaiing
	 * "odd/even" order
	 */
	NUM_NON_BLUE_FLAME_BFREGS = 1,
पूर्ण;

अटल पूर्णांक max_bfregs(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_bfreg_info *bfregi)
अणु
	वापस get_num_अटल_uars(dev, bfregi) * MLX5_NON_FP_BFREGS_PER_UAR;
पूर्ण

अटल पूर्णांक num_med_bfreg(काष्ठा mlx5_ib_dev *dev,
			 काष्ठा mlx5_bfreg_info *bfregi)
अणु
	पूर्णांक n;

	n = max_bfregs(dev, bfregi) - bfregi->num_low_latency_bfregs -
	    NUM_NON_BLUE_FLAME_BFREGS;

	वापस n >= 0 ? n : 0;
पूर्ण

अटल पूर्णांक first_med_bfreg(काष्ठा mlx5_ib_dev *dev,
			   काष्ठा mlx5_bfreg_info *bfregi)
अणु
	वापस num_med_bfreg(dev, bfregi) ? 1 : -ENOMEM;
पूर्ण

अटल पूर्णांक first_hi_bfreg(काष्ठा mlx5_ib_dev *dev,
			  काष्ठा mlx5_bfreg_info *bfregi)
अणु
	पूर्णांक med;

	med = num_med_bfreg(dev, bfregi);
	वापस ++med;
पूर्ण

अटल पूर्णांक alloc_high_class_bfreg(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_bfreg_info *bfregi)
अणु
	पूर्णांक i;

	क्रम (i = first_hi_bfreg(dev, bfregi); i < max_bfregs(dev, bfregi); i++) अणु
		अगर (!bfregi->count[i]) अणु
			bfregi->count[i]++;
			वापस i;
		पूर्ण
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक alloc_med_class_bfreg(काष्ठा mlx5_ib_dev *dev,
				 काष्ठा mlx5_bfreg_info *bfregi)
अणु
	पूर्णांक minidx = first_med_bfreg(dev, bfregi);
	पूर्णांक i;

	अगर (minidx < 0)
		वापस minidx;

	क्रम (i = minidx; i < first_hi_bfreg(dev, bfregi); i++) अणु
		अगर (bfregi->count[i] < bfregi->count[minidx])
			minidx = i;
		अगर (!bfregi->count[minidx])
			अवरोध;
	पूर्ण

	bfregi->count[minidx]++;
	वापस minidx;
पूर्ण

अटल पूर्णांक alloc_bfreg(काष्ठा mlx5_ib_dev *dev,
		       काष्ठा mlx5_bfreg_info *bfregi)
अणु
	पूर्णांक bfregn = -ENOMEM;

	अगर (bfregi->lib_uar_dyn)
		वापस -EINVAL;

	mutex_lock(&bfregi->lock);
	अगर (bfregi->ver >= 2) अणु
		bfregn = alloc_high_class_bfreg(dev, bfregi);
		अगर (bfregn < 0)
			bfregn = alloc_med_class_bfreg(dev, bfregi);
	पूर्ण

	अगर (bfregn < 0) अणु
		BUILD_BUG_ON(NUM_NON_BLUE_FLAME_BFREGS != 1);
		bfregn = 0;
		bfregi->count[bfregn]++;
	पूर्ण
	mutex_unlock(&bfregi->lock);

	वापस bfregn;
पूर्ण

व्योम mlx5_ib_मुक्त_bfreg(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_bfreg_info *bfregi, पूर्णांक bfregn)
अणु
	mutex_lock(&bfregi->lock);
	bfregi->count[bfregn]--;
	mutex_unlock(&bfregi->lock);
पूर्ण

अटल क्रमागत mlx5_qp_state to_mlx5_state(क्रमागत ib_qp_state state)
अणु
	चयन (state) अणु
	हाल IB_QPS_RESET:	वापस MLX5_QP_STATE_RST;
	हाल IB_QPS_INIT:	वापस MLX5_QP_STATE_INIT;
	हाल IB_QPS_RTR:	वापस MLX5_QP_STATE_RTR;
	हाल IB_QPS_RTS:	वापस MLX5_QP_STATE_RTS;
	हाल IB_QPS_SQD:	वापस MLX5_QP_STATE_SQD;
	हाल IB_QPS_SQE:	वापस MLX5_QP_STATE_SQER;
	हाल IB_QPS_ERR:	वापस MLX5_QP_STATE_ERR;
	शेष:		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक to_mlx5_st(क्रमागत ib_qp_type type)
अणु
	चयन (type) अणु
	हाल IB_QPT_RC:			वापस MLX5_QP_ST_RC;
	हाल IB_QPT_UC:			वापस MLX5_QP_ST_UC;
	हाल IB_QPT_UD:			वापस MLX5_QP_ST_UD;
	हाल MLX5_IB_QPT_REG_UMR:	वापस MLX5_QP_ST_REG_UMR;
	हाल IB_QPT_XRC_INI:
	हाल IB_QPT_XRC_TGT:		वापस MLX5_QP_ST_XRC;
	हाल IB_QPT_SMI:		वापस MLX5_QP_ST_QP0;
	हाल MLX5_IB_QPT_HW_GSI:	वापस MLX5_QP_ST_QP1;
	हाल MLX5_IB_QPT_DCI:		वापस MLX5_QP_ST_DCI;
	हाल IB_QPT_RAW_PACKET:		वापस MLX5_QP_ST_RAW_ETHERTYPE;
	शेष:		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम mlx5_ib_lock_cqs(काष्ठा mlx5_ib_cq *send_cq,
			     काष्ठा mlx5_ib_cq *recv_cq);
अटल व्योम mlx5_ib_unlock_cqs(काष्ठा mlx5_ib_cq *send_cq,
			       काष्ठा mlx5_ib_cq *recv_cq);

पूर्णांक bfregn_to_uar_index(काष्ठा mlx5_ib_dev *dev,
			काष्ठा mlx5_bfreg_info *bfregi, u32 bfregn,
			bool dyn_bfreg)
अणु
	अचिन्हित पूर्णांक bfregs_per_sys_page;
	u32 index_of_sys_page;
	u32 offset;

	अगर (bfregi->lib_uar_dyn)
		वापस -EINVAL;

	bfregs_per_sys_page = get_uars_per_sys_page(dev, bfregi->lib_uar_4k) *
				MLX5_NON_FP_BFREGS_PER_UAR;
	index_of_sys_page = bfregn / bfregs_per_sys_page;

	अगर (dyn_bfreg) अणु
		index_of_sys_page += bfregi->num_अटल_sys_pages;

		अगर (index_of_sys_page >= bfregi->num_sys_pages)
			वापस -EINVAL;

		अगर (bfregn > bfregi->num_dyn_bfregs ||
		    bfregi->sys_pages[index_of_sys_page] == MLX5_IB_INVALID_UAR_INDEX) अणु
			mlx5_ib_dbg(dev, "Invalid dynamic uar index\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	offset = bfregn % bfregs_per_sys_page / MLX5_NON_FP_BFREGS_PER_UAR;
	वापस bfregi->sys_pages[index_of_sys_page] + offset;
पूर्ण

अटल व्योम destroy_user_rq(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
			    काष्ठा mlx5_ib_rwq *rwq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *context =
		rdma_udata_to_drv_context(
			udata,
			काष्ठा mlx5_ib_ucontext,
			ibucontext);

	अगर (rwq->create_flags & MLX5_IB_WQ_FLAGS_DELAY_DROP)
		atomic_dec(&dev->delay_drop.rqs_cnt);

	mlx5_ib_db_unmap_user(context, &rwq->db);
	ib_umem_release(rwq->umem);
पूर्ण

अटल पूर्णांक create_user_rq(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
			  काष्ठा ib_udata *udata, काष्ठा mlx5_ib_rwq *rwq,
			  काष्ठा mlx5_ib_create_wq *ucmd)
अणु
	काष्ठा mlx5_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	अचिन्हित दीर्घ page_size = 0;
	u32 offset = 0;
	पूर्णांक err;

	अगर (!ucmd->buf_addr)
		वापस -EINVAL;

	rwq->umem = ib_umem_get(&dev->ib_dev, ucmd->buf_addr, rwq->buf_size, 0);
	अगर (IS_ERR(rwq->umem)) अणु
		mlx5_ib_dbg(dev, "umem_get failed\n");
		err = PTR_ERR(rwq->umem);
		वापस err;
	पूर्ण

	page_size = mlx5_umem_find_best_quantized_pgoff(
		rwq->umem, wq, log_wq_pg_sz, MLX5_ADAPTER_PAGE_SHIFT,
		page_offset, 64, &rwq->rq_page_offset);
	अगर (!page_size) अणु
		mlx5_ib_warn(dev, "bad offset\n");
		err = -EINVAL;
		जाओ err_umem;
	पूर्ण

	rwq->rq_num_pas = ib_umem_num_dma_blocks(rwq->umem, page_size);
	rwq->page_shअगरt = order_base_2(page_size);
	rwq->log_page_size =  rwq->page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT;
	rwq->wq_sig = !!(ucmd->flags & MLX5_WQ_FLAG_SIGNATURE);

	mlx5_ib_dbg(
		dev,
		"addr 0x%llx, size %zd, npages %zu, page_size %ld, ncont %d, offset %d\n",
		(अचिन्हित दीर्घ दीर्घ)ucmd->buf_addr, rwq->buf_size,
		ib_umem_num_pages(rwq->umem), page_size, rwq->rq_num_pas,
		offset);

	err = mlx5_ib_db_map_user(ucontext, udata, ucmd->db_addr, &rwq->db);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "map failed\n");
		जाओ err_umem;
	पूर्ण

	वापस 0;

err_umem:
	ib_umem_release(rwq->umem);
	वापस err;
पूर्ण

अटल पूर्णांक adjust_bfregn(काष्ठा mlx5_ib_dev *dev,
			 काष्ठा mlx5_bfreg_info *bfregi, पूर्णांक bfregn)
अणु
	वापस bfregn / MLX5_NON_FP_BFREGS_PER_UAR * MLX5_BFREGS_PER_UAR +
				bfregn % MLX5_NON_FP_BFREGS_PER_UAR;
पूर्ण

अटल पूर्णांक _create_user_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
			   काष्ठा mlx5_ib_qp *qp, काष्ठा ib_udata *udata,
			   काष्ठा ib_qp_init_attr *attr, u32 **in,
			   काष्ठा mlx5_ib_create_qp_resp *resp, पूर्णांक *inlen,
			   काष्ठा mlx5_ib_qp_base *base,
			   काष्ठा mlx5_ib_create_qp *ucmd)
अणु
	काष्ठा mlx5_ib_ucontext *context;
	काष्ठा mlx5_ib_ubuffer *ubuffer = &base->ubuffer;
	अचिन्हित पूर्णांक page_offset_quantized = 0;
	अचिन्हित दीर्घ page_size = 0;
	पूर्णांक uar_index = 0;
	पूर्णांक bfregn;
	पूर्णांक ncont = 0;
	__be64 *pas;
	व्योम *qpc;
	पूर्णांक err;
	u16 uid;
	u32 uar_flags;

	context = rdma_udata_to_drv_context(udata, काष्ठा mlx5_ib_ucontext,
					    ibucontext);
	uar_flags = qp->flags_en &
		    (MLX5_QP_FLAG_UAR_PAGE_INDEX | MLX5_QP_FLAG_BFREG_INDEX);
	चयन (uar_flags) अणु
	हाल MLX5_QP_FLAG_UAR_PAGE_INDEX:
		uar_index = ucmd->bfreg_index;
		bfregn = MLX5_IB_INVALID_BFREG;
		अवरोध;
	हाल MLX5_QP_FLAG_BFREG_INDEX:
		uar_index = bfregn_to_uar_index(dev, &context->bfregi,
						ucmd->bfreg_index, true);
		अगर (uar_index < 0)
			वापस uar_index;
		bfregn = MLX5_IB_INVALID_BFREG;
		अवरोध;
	हाल 0:
		अगर (qp->flags & IB_QP_CREATE_CROSS_CHANNEL)
			वापस -EINVAL;
		bfregn = alloc_bfreg(dev, &context->bfregi);
		अगर (bfregn < 0)
			वापस bfregn;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mlx5_ib_dbg(dev, "bfregn 0x%x, uar_index 0x%x\n", bfregn, uar_index);
	अगर (bfregn != MLX5_IB_INVALID_BFREG)
		uar_index = bfregn_to_uar_index(dev, &context->bfregi, bfregn,
						false);

	qp->rq.offset = 0;
	qp->sq.wqe_shअगरt = ilog2(MLX5_SEND_WQE_BB);
	qp->sq.offset = qp->rq.wqe_cnt << qp->rq.wqe_shअगरt;

	err = set_user_buf_size(dev, qp, ucmd, base, attr);
	अगर (err)
		जाओ err_bfreg;

	अगर (ucmd->buf_addr && ubuffer->buf_size) अणु
		ubuffer->buf_addr = ucmd->buf_addr;
		ubuffer->umem = ib_umem_get(&dev->ib_dev, ubuffer->buf_addr,
					    ubuffer->buf_size, 0);
		अगर (IS_ERR(ubuffer->umem)) अणु
			err = PTR_ERR(ubuffer->umem);
			जाओ err_bfreg;
		पूर्ण
		page_size = mlx5_umem_find_best_quantized_pgoff(
			ubuffer->umem, qpc, log_page_size,
			MLX5_ADAPTER_PAGE_SHIFT, page_offset, 64,
			&page_offset_quantized);
		अगर (!page_size) अणु
			err = -EINVAL;
			जाओ err_umem;
		पूर्ण
		ncont = ib_umem_num_dma_blocks(ubuffer->umem, page_size);
	पूर्ण अन्यथा अणु
		ubuffer->umem = शून्य;
	पूर्ण

	*inlen = MLX5_ST_SZ_BYTES(create_qp_in) +
		 MLX5_FLD_SZ_BYTES(create_qp_in, pas[0]) * ncont;
	*in = kvzalloc(*inlen, GFP_KERNEL);
	अगर (!*in) अणु
		err = -ENOMEM;
		जाओ err_umem;
	पूर्ण

	uid = (attr->qp_type != IB_QPT_XRC_INI) ? to_mpd(pd)->uid : 0;
	MLX5_SET(create_qp_in, *in, uid, uid);
	qpc = MLX5_ADDR_OF(create_qp_in, *in, qpc);
	pas = (__be64 *)MLX5_ADDR_OF(create_qp_in, *in, pas);
	अगर (ubuffer->umem) अणु
		mlx5_ib_populate_pas(ubuffer->umem, page_size, pas, 0);
		MLX5_SET(qpc, qpc, log_page_size,
			 order_base_2(page_size) - MLX5_ADAPTER_PAGE_SHIFT);
		MLX5_SET(qpc, qpc, page_offset, page_offset_quantized);
	पूर्ण
	MLX5_SET(qpc, qpc, uar_page, uar_index);
	अगर (bfregn != MLX5_IB_INVALID_BFREG)
		resp->bfreg_index = adjust_bfregn(dev, &context->bfregi, bfregn);
	अन्यथा
		resp->bfreg_index = MLX5_IB_INVALID_BFREG;
	qp->bfregn = bfregn;

	err = mlx5_ib_db_map_user(context, udata, ucmd->db_addr, &qp->db);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "map failed\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;

err_मुक्त:
	kvमुक्त(*in);

err_umem:
	ib_umem_release(ubuffer->umem);

err_bfreg:
	अगर (bfregn != MLX5_IB_INVALID_BFREG)
		mlx5_ib_मुक्त_bfreg(dev, &context->bfregi, bfregn);
	वापस err;
पूर्ण

अटल व्योम destroy_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
		       काष्ठा mlx5_ib_qp_base *base, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	अगर (udata) अणु
		/* User QP */
		mlx5_ib_db_unmap_user(context, &qp->db);
		ib_umem_release(base->ubuffer.umem);

		/*
		 * Free only the BFREGs which are handled by the kernel.
		 * BFREGs of UARs allocated dynamically are handled by user.
		 */
		अगर (qp->bfregn != MLX5_IB_INVALID_BFREG)
			mlx5_ib_मुक्त_bfreg(dev, &context->bfregi, qp->bfregn);
		वापस;
	पूर्ण

	/* Kernel QP */
	kvमुक्त(qp->sq.wqe_head);
	kvमुक्त(qp->sq.w_list);
	kvमुक्त(qp->sq.wrid);
	kvमुक्त(qp->sq.wr_data);
	kvमुक्त(qp->rq.wrid);
	अगर (qp->db.db)
		mlx5_db_मुक्त(dev->mdev, &qp->db);
	अगर (qp->buf.frags)
		mlx5_frag_buf_मुक्त(dev->mdev, &qp->buf);
पूर्ण

अटल पूर्णांक _create_kernel_qp(काष्ठा mlx5_ib_dev *dev,
			     काष्ठा ib_qp_init_attr *init_attr,
			     काष्ठा mlx5_ib_qp *qp, u32 **in, पूर्णांक *inlen,
			     काष्ठा mlx5_ib_qp_base *base)
अणु
	पूर्णांक uar_index;
	व्योम *qpc;
	पूर्णांक err;

	अगर (init_attr->qp_type == MLX5_IB_QPT_REG_UMR)
		qp->bf.bfreg = &dev->fp_bfreg;
	अन्यथा अगर (qp->flags & MLX5_IB_QP_CREATE_WC_TEST)
		qp->bf.bfreg = &dev->wc_bfreg;
	अन्यथा
		qp->bf.bfreg = &dev->bfreg;

	/* We need to भागide by two since each रेजिस्टर is comprised of
	 * two buffers of identical size, namely odd and even
	 */
	qp->bf.buf_size = (1 << MLX5_CAP_GEN(dev->mdev, log_bf_reg_size)) / 2;
	uar_index = qp->bf.bfreg->index;

	err = calc_sq_size(dev, init_attr, qp);
	अगर (err < 0) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		वापस err;
	पूर्ण

	qp->rq.offset = 0;
	qp->sq.offset = qp->rq.wqe_cnt << qp->rq.wqe_shअगरt;
	base->ubuffer.buf_size = err + (qp->rq.wqe_cnt << qp->rq.wqe_shअगरt);

	err = mlx5_frag_buf_alloc_node(dev->mdev, base->ubuffer.buf_size,
				       &qp->buf, dev->mdev->priv.numa_node);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		वापस err;
	पूर्ण

	अगर (qp->rq.wqe_cnt)
		mlx5_init_fbc(qp->buf.frags, qp->rq.wqe_shअगरt,
			      ilog2(qp->rq.wqe_cnt), &qp->rq.fbc);

	अगर (qp->sq.wqe_cnt) अणु
		पूर्णांक sq_strides_offset = (qp->sq.offset  & (PAGE_SIZE - 1)) /
					MLX5_SEND_WQE_BB;
		mlx5_init_fbc_offset(qp->buf.frags +
				     (qp->sq.offset / PAGE_SIZE),
				     ilog2(MLX5_SEND_WQE_BB),
				     ilog2(qp->sq.wqe_cnt),
				     sq_strides_offset, &qp->sq.fbc);

		qp->sq.cur_edge = get_sq_edge(&qp->sq, 0);
	पूर्ण

	*inlen = MLX5_ST_SZ_BYTES(create_qp_in) +
		 MLX5_FLD_SZ_BYTES(create_qp_in, pas[0]) * qp->buf.npages;
	*in = kvzalloc(*inlen, GFP_KERNEL);
	अगर (!*in) अणु
		err = -ENOMEM;
		जाओ err_buf;
	पूर्ण

	qpc = MLX5_ADDR_OF(create_qp_in, *in, qpc);
	MLX5_SET(qpc, qpc, uar_page, uar_index);
	MLX5_SET(qpc, qpc, ts_क्रमmat, mlx5_get_qp_शेष_ts(dev->mdev));
	MLX5_SET(qpc, qpc, log_page_size, qp->buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);

	/* Set "fast registration enabled" क्रम all kernel QPs */
	MLX5_SET(qpc, qpc, fre, 1);
	MLX5_SET(qpc, qpc, rlky, 1);

	अगर (qp->flags & MLX5_IB_QP_CREATE_SQPN_QP1)
		MLX5_SET(qpc, qpc, deth_sqpn, 1);

	mlx5_fill_page_frag_array(&qp->buf,
				  (__be64 *)MLX5_ADDR_OF(create_qp_in,
							 *in, pas));

	err = mlx5_db_alloc(dev->mdev, &qp->db);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		जाओ err_मुक्त;
	पूर्ण

	qp->sq.wrid = kvदो_स्मृति_array(qp->sq.wqe_cnt,
				     माप(*qp->sq.wrid), GFP_KERNEL);
	qp->sq.wr_data = kvदो_स्मृति_array(qp->sq.wqe_cnt,
					माप(*qp->sq.wr_data), GFP_KERNEL);
	qp->rq.wrid = kvदो_स्मृति_array(qp->rq.wqe_cnt,
				     माप(*qp->rq.wrid), GFP_KERNEL);
	qp->sq.w_list = kvदो_स्मृति_array(qp->sq.wqe_cnt,
				       माप(*qp->sq.w_list), GFP_KERNEL);
	qp->sq.wqe_head = kvदो_स्मृति_array(qp->sq.wqe_cnt,
					 माप(*qp->sq.wqe_head), GFP_KERNEL);

	अगर (!qp->sq.wrid || !qp->sq.wr_data || !qp->rq.wrid ||
	    !qp->sq.w_list || !qp->sq.wqe_head) अणु
		err = -ENOMEM;
		जाओ err_wrid;
	पूर्ण

	वापस 0;

err_wrid:
	kvमुक्त(qp->sq.wqe_head);
	kvमुक्त(qp->sq.w_list);
	kvमुक्त(qp->sq.wrid);
	kvमुक्त(qp->sq.wr_data);
	kvमुक्त(qp->rq.wrid);
	mlx5_db_मुक्त(dev->mdev, &qp->db);

err_मुक्त:
	kvमुक्त(*in);

err_buf:
	mlx5_frag_buf_मुक्त(dev->mdev, &qp->buf);
	वापस err;
पूर्ण

अटल u32 get_rx_type(काष्ठा mlx5_ib_qp *qp, काष्ठा ib_qp_init_attr *attr)
अणु
	अगर (attr->srq || (qp->type == IB_QPT_XRC_TGT) ||
	    (qp->type == MLX5_IB_QPT_DCI) || (qp->type == IB_QPT_XRC_INI))
		वापस MLX5_SRQ_RQ;
	अन्यथा अगर (!qp->has_rq)
		वापस MLX5_ZERO_LEN_RQ;

	वापस MLX5_NON_ZERO_RQ;
पूर्ण

अटल पूर्णांक create_raw_packet_qp_tis(काष्ठा mlx5_ib_dev *dev,
				    काष्ठा mlx5_ib_qp *qp,
				    काष्ठा mlx5_ib_sq *sq, u32 tdn,
				    काष्ठा ib_pd *pd)
अणु
	u32 in[MLX5_ST_SZ_DW(create_tis_in)] = अणुपूर्ण;
	व्योम *tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

	MLX5_SET(create_tis_in, in, uid, to_mpd(pd)->uid);
	MLX5_SET(tisc, tisc, transport_करोमुख्य, tdn);
	अगर (qp->flags & IB_QP_CREATE_SOURCE_QPN)
		MLX5_SET(tisc, tisc, underlay_qpn, qp->underlay_qpn);

	वापस mlx5_core_create_tis(dev->mdev, in, &sq->tisn);
पूर्ण

अटल व्योम destroy_raw_packet_qp_tis(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा mlx5_ib_sq *sq, काष्ठा ib_pd *pd)
अणु
	mlx5_cmd_destroy_tis(dev->mdev, sq->tisn, to_mpd(pd)->uid);
पूर्ण

अटल व्योम destroy_flow_rule_vport_sq(काष्ठा mlx5_ib_sq *sq)
अणु
	अगर (sq->flow_rule)
		mlx5_del_flow_rules(sq->flow_rule);
	sq->flow_rule = शून्य;
पूर्ण

अटल पूर्णांक get_rq_ts_क्रमmat(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *send_cq)
अणु
	bool fr_supported =
		MLX5_CAP_GEN(dev->mdev, rq_ts_क्रमmat) ==
			MLX5_RQ_TIMESTAMP_FORMAT_CAP_FREE_RUNNING ||
		MLX5_CAP_GEN(dev->mdev, rq_ts_क्रमmat) ==
			MLX5_RQ_TIMESTAMP_FORMAT_CAP_FREE_RUNNING_AND_REAL_TIME;

	अगर (send_cq->create_flags & IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION) अणु
		अगर (!fr_supported) अणु
			mlx5_ib_dbg(dev, "Free running TS format is not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		वापस MLX5_RQC_TIMESTAMP_FORMAT_FREE_RUNNING;
	पूर्ण
	वापस fr_supported ? MLX5_RQC_TIMESTAMP_FORMAT_FREE_RUNNING :
			      MLX5_RQC_TIMESTAMP_FORMAT_DEFAULT;
पूर्ण

अटल पूर्णांक get_sq_ts_क्रमmat(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *send_cq)
अणु
	bool fr_supported =
		MLX5_CAP_GEN(dev->mdev, sq_ts_क्रमmat) ==
			MLX5_SQ_TIMESTAMP_FORMAT_CAP_FREE_RUNNING ||
		MLX5_CAP_GEN(dev->mdev, sq_ts_क्रमmat) ==
			MLX5_SQ_TIMESTAMP_FORMAT_CAP_FREE_RUNNING_AND_REAL_TIME;

	अगर (send_cq->create_flags & IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION) अणु
		अगर (!fr_supported) अणु
			mlx5_ib_dbg(dev, "Free running TS format is not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		वापस MLX5_SQC_TIMESTAMP_FORMAT_FREE_RUNNING;
	पूर्ण
	वापस fr_supported ? MLX5_SQC_TIMESTAMP_FORMAT_FREE_RUNNING :
			      MLX5_SQC_TIMESTAMP_FORMAT_DEFAULT;
पूर्ण

अटल पूर्णांक get_qp_ts_क्रमmat(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_cq *send_cq,
			    काष्ठा mlx5_ib_cq *recv_cq)
अणु
	bool fr_supported =
		MLX5_CAP_ROCE(dev->mdev, qp_ts_क्रमmat) ==
			MLX5_QP_TIMESTAMP_FORMAT_CAP_FREE_RUNNING ||
		MLX5_CAP_ROCE(dev->mdev, qp_ts_क्रमmat) ==
			MLX5_QP_TIMESTAMP_FORMAT_CAP_FREE_RUNNING_AND_REAL_TIME;
	पूर्णांक ts_क्रमmat = fr_supported ? MLX5_QPC_TIMESTAMP_FORMAT_FREE_RUNNING :
				       MLX5_QPC_TIMESTAMP_FORMAT_DEFAULT;

	अगर (recv_cq &&
	    recv_cq->create_flags & IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION)
		ts_क्रमmat = MLX5_QPC_TIMESTAMP_FORMAT_FREE_RUNNING;

	अगर (send_cq &&
	    send_cq->create_flags & IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION)
		ts_क्रमmat = MLX5_QPC_TIMESTAMP_FORMAT_FREE_RUNNING;

	अगर (ts_क्रमmat == MLX5_QPC_TIMESTAMP_FORMAT_FREE_RUNNING &&
	    !fr_supported) अणु
		mlx5_ib_dbg(dev, "Free running TS format is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ts_क्रमmat;
पूर्ण

अटल पूर्णांक create_raw_packet_qp_sq(काष्ठा mlx5_ib_dev *dev,
				   काष्ठा ib_udata *udata,
				   काष्ठा mlx5_ib_sq *sq, व्योम *qpin,
				   काष्ठा ib_pd *pd, काष्ठा mlx5_ib_cq *cq)
अणु
	काष्ठा mlx5_ib_ubuffer *ubuffer = &sq->ubuffer;
	__be64 *pas;
	व्योम *in;
	व्योम *sqc;
	व्योम *qpc = MLX5_ADDR_OF(create_qp_in, qpin, qpc);
	व्योम *wq;
	पूर्णांक inlen;
	पूर्णांक err;
	अचिन्हित पूर्णांक page_offset_quantized;
	अचिन्हित दीर्घ page_size;
	पूर्णांक ts_क्रमmat;

	ts_क्रमmat = get_sq_ts_क्रमmat(dev, cq);
	अगर (ts_क्रमmat < 0)
		वापस ts_क्रमmat;

	sq->ubuffer.umem = ib_umem_get(&dev->ib_dev, ubuffer->buf_addr,
				       ubuffer->buf_size, 0);
	अगर (IS_ERR(sq->ubuffer.umem))
		वापस PTR_ERR(sq->ubuffer.umem);
	page_size = mlx5_umem_find_best_quantized_pgoff(
		ubuffer->umem, wq, log_wq_pg_sz, MLX5_ADAPTER_PAGE_SHIFT,
		page_offset, 64, &page_offset_quantized);
	अगर (!page_size) अणु
		err = -EINVAL;
		जाओ err_umem;
	पूर्ण

	inlen = MLX5_ST_SZ_BYTES(create_sq_in) +
		माप(u64) *
			ib_umem_num_dma_blocks(sq->ubuffer.umem, page_size);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_umem;
	पूर्ण

	MLX5_SET(create_sq_in, in, uid, to_mpd(pd)->uid);
	sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
	MLX5_SET(sqc, sqc, flush_in_error_en, 1);
	अगर (MLX5_CAP_ETH(dev->mdev, multi_pkt_send_wqe))
		MLX5_SET(sqc, sqc, allow_multi_pkt_send_wqe, 1);
	MLX5_SET(sqc, sqc, state, MLX5_SQC_STATE_RST);
	MLX5_SET(sqc, sqc, ts_क्रमmat, ts_क्रमmat);
	MLX5_SET(sqc, sqc, user_index, MLX5_GET(qpc, qpc, user_index));
	MLX5_SET(sqc, sqc, cqn, MLX5_GET(qpc, qpc, cqn_snd));
	MLX5_SET(sqc, sqc, tis_lst_sz, 1);
	MLX5_SET(sqc, sqc, tis_num_0, sq->tisn);
	अगर (MLX5_CAP_GEN(dev->mdev, eth_net_offloads) &&
	    MLX5_CAP_ETH(dev->mdev, swp))
		MLX5_SET(sqc, sqc, allow_swp, 1);

	wq = MLX5_ADDR_OF(sqc, sqc, wq);
	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	MLX5_SET(wq, wq, pd, MLX5_GET(qpc, qpc, pd));
	MLX5_SET(wq, wq, uar_page, MLX5_GET(qpc, qpc, uar_page));
	MLX5_SET64(wq, wq, dbr_addr, MLX5_GET64(qpc, qpc, dbr_addr));
	MLX5_SET(wq, wq, log_wq_stride, ilog2(MLX5_SEND_WQE_BB));
	MLX5_SET(wq, wq, log_wq_sz, MLX5_GET(qpc, qpc, log_sq_size));
	MLX5_SET(wq, wq, log_wq_pg_sz,
		 order_base_2(page_size) - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(wq, wq, page_offset, page_offset_quantized);

	pas = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	mlx5_ib_populate_pas(sq->ubuffer.umem, page_size, pas, 0);

	err = mlx5_core_create_sq_tracked(dev, in, inlen, &sq->base.mqp);

	kvमुक्त(in);

	अगर (err)
		जाओ err_umem;

	वापस 0;

err_umem:
	ib_umem_release(sq->ubuffer.umem);
	sq->ubuffer.umem = शून्य;

	वापस err;
पूर्ण

अटल व्योम destroy_raw_packet_qp_sq(काष्ठा mlx5_ib_dev *dev,
				     काष्ठा mlx5_ib_sq *sq)
अणु
	destroy_flow_rule_vport_sq(sq);
	mlx5_core_destroy_sq_tracked(dev, &sq->base.mqp);
	ib_umem_release(sq->ubuffer.umem);
पूर्ण

अटल पूर्णांक create_raw_packet_qp_rq(काष्ठा mlx5_ib_dev *dev,
				   काष्ठा mlx5_ib_rq *rq, व्योम *qpin,
				   काष्ठा ib_pd *pd, काष्ठा mlx5_ib_cq *cq)
अणु
	काष्ठा mlx5_ib_qp *mqp = rq->base.container_mibqp;
	__be64 *pas;
	व्योम *in;
	व्योम *rqc;
	व्योम *wq;
	व्योम *qpc = MLX5_ADDR_OF(create_qp_in, qpin, qpc);
	काष्ठा ib_umem *umem = rq->base.ubuffer.umem;
	अचिन्हित पूर्णांक page_offset_quantized;
	अचिन्हित दीर्घ page_size = 0;
	पूर्णांक ts_क्रमmat;
	माप_प्रकार inlen;
	पूर्णांक err;

	ts_क्रमmat = get_rq_ts_क्रमmat(dev, cq);
	अगर (ts_क्रमmat < 0)
		वापस ts_क्रमmat;

	page_size = mlx5_umem_find_best_quantized_pgoff(umem, wq, log_wq_pg_sz,
							MLX5_ADAPTER_PAGE_SHIFT,
							page_offset, 64,
							&page_offset_quantized);
	अगर (!page_size)
		वापस -EINVAL;

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) +
		माप(u64) * ib_umem_num_dma_blocks(umem, page_size);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_rq_in, in, uid, to_mpd(pd)->uid);
	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	अगर (!(rq->flags & MLX5_IB_RQ_CVLAN_STRIPPING))
		MLX5_SET(rqc, rqc, vsd, 1);
	MLX5_SET(rqc, rqc, mem_rq_type, MLX5_RQC_MEM_RQ_TYPE_MEMORY_RQ_INLINE);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc, rqc, ts_क्रमmat, ts_क्रमmat);
	MLX5_SET(rqc, rqc, flush_in_error_en, 1);
	MLX5_SET(rqc, rqc, user_index, MLX5_GET(qpc, qpc, user_index));
	MLX5_SET(rqc, rqc, cqn, MLX5_GET(qpc, qpc, cqn_rcv));

	अगर (mqp->flags & IB_QP_CREATE_SCATTER_FCS)
		MLX5_SET(rqc, rqc, scatter_fcs, 1);

	wq = MLX5_ADDR_OF(rqc, rqc, wq);
	MLX5_SET(wq, wq, wq_type, MLX5_WQ_TYPE_CYCLIC);
	अगर (rq->flags & MLX5_IB_RQ_PCI_WRITE_END_PADDING)
		MLX5_SET(wq, wq, end_padding_mode, MLX5_WQ_END_PAD_MODE_ALIGN);
	MLX5_SET(wq, wq, page_offset, page_offset_quantized);
	MLX5_SET(wq, wq, pd, MLX5_GET(qpc, qpc, pd));
	MLX5_SET64(wq, wq, dbr_addr, MLX5_GET64(qpc, qpc, dbr_addr));
	MLX5_SET(wq, wq, log_wq_stride, MLX5_GET(qpc, qpc, log_rq_stride) + 4);
	MLX5_SET(wq, wq, log_wq_pg_sz,
		 order_base_2(page_size) - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(wq, wq, log_wq_sz, MLX5_GET(qpc, qpc, log_rq_size));

	pas = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	mlx5_ib_populate_pas(umem, page_size, pas, 0);

	err = mlx5_core_create_rq_tracked(dev, in, inlen, &rq->base.mqp);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल व्योम destroy_raw_packet_qp_rq(काष्ठा mlx5_ib_dev *dev,
				     काष्ठा mlx5_ib_rq *rq)
अणु
	mlx5_core_destroy_rq_tracked(dev, &rq->base.mqp);
पूर्ण

अटल व्योम destroy_raw_packet_qp_tir(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा mlx5_ib_rq *rq,
				      u32 qp_flags_en,
				      काष्ठा ib_pd *pd)
अणु
	अगर (qp_flags_en & (MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC |
			   MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC))
		mlx5_ib_disable_lb(dev, false, true);
	mlx5_cmd_destroy_tir(dev->mdev, rq->tirn, to_mpd(pd)->uid);
पूर्ण

अटल पूर्णांक create_raw_packet_qp_tir(काष्ठा mlx5_ib_dev *dev,
				    काष्ठा mlx5_ib_rq *rq, u32 tdn,
				    u32 *qp_flags_en, काष्ठा ib_pd *pd,
				    u32 *out)
अणु
	u8 lb_flag = 0;
	u32 *in;
	व्योम *tirc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_tir_in, in, uid, to_mpd(pd)->uid);
	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_सूचीECT);
	MLX5_SET(tirc, tirc, अंतरभूत_rqn, rq->base.mqp.qpn);
	MLX5_SET(tirc, tirc, transport_करोमुख्य, tdn);
	अगर (*qp_flags_en & MLX5_QP_FLAG_TUNNEL_OFFLOADS)
		MLX5_SET(tirc, tirc, tunneled_offload_en, 1);

	अगर (*qp_flags_en & MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC)
		lb_flag |= MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST;

	अगर (*qp_flags_en & MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC)
		lb_flag |= MLX5_TIRC_SELF_LB_BLOCK_BLOCK_MULTICAST;

	अगर (dev->is_rep) अणु
		lb_flag |= MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST;
		*qp_flags_en |= MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC;
	पूर्ण

	MLX5_SET(tirc, tirc, self_lb_block, lb_flag);
	MLX5_SET(create_tir_in, in, opcode, MLX5_CMD_OP_CREATE_TIR);
	err = mlx5_cmd_exec_inout(dev->mdev, create_tir, in, out);
	rq->tirn = MLX5_GET(create_tir_out, out, tirn);
	अगर (!err && MLX5_GET(tirc, tirc, self_lb_block)) अणु
		err = mlx5_ib_enable_lb(dev, false, true);

		अगर (err)
			destroy_raw_packet_qp_tir(dev, rq, 0, pd);
	पूर्ण
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक create_raw_packet_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
				u32 *in, माप_प्रकार inlen, काष्ठा ib_pd *pd,
				काष्ठा ib_udata *udata,
				काष्ठा mlx5_ib_create_qp_resp *resp,
				काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	काष्ठा mlx5_ib_sq *sq = &raw_packet_qp->sq;
	काष्ठा mlx5_ib_rq *rq = &raw_packet_qp->rq;
	काष्ठा mlx5_ib_ucontext *mucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	पूर्णांक err;
	u32 tdn = mucontext->tdn;
	u16 uid = to_mpd(pd)->uid;
	u32 out[MLX5_ST_SZ_DW(create_tir_out)] = अणुपूर्ण;

	अगर (!qp->sq.wqe_cnt && !qp->rq.wqe_cnt)
		वापस -EINVAL;
	अगर (qp->sq.wqe_cnt) अणु
		err = create_raw_packet_qp_tis(dev, qp, sq, tdn, pd);
		अगर (err)
			वापस err;

		err = create_raw_packet_qp_sq(dev, udata, sq, in, pd,
					      to_mcq(init_attr->send_cq));
		अगर (err)
			जाओ err_destroy_tis;

		अगर (uid) अणु
			resp->tisn = sq->tisn;
			resp->comp_mask |= MLX5_IB_CREATE_QP_RESP_MASK_TISN;
			resp->sqn = sq->base.mqp.qpn;
			resp->comp_mask |= MLX5_IB_CREATE_QP_RESP_MASK_SQN;
		पूर्ण

		sq->base.container_mibqp = qp;
		sq->base.mqp.event = mlx5_ib_qp_event;
	पूर्ण

	अगर (qp->rq.wqe_cnt) अणु
		rq->base.container_mibqp = qp;

		अगर (qp->flags & IB_QP_CREATE_CVLAN_STRIPPING)
			rq->flags |= MLX5_IB_RQ_CVLAN_STRIPPING;
		अगर (qp->flags & IB_QP_CREATE_PCI_WRITE_END_PADDING)
			rq->flags |= MLX5_IB_RQ_PCI_WRITE_END_PADDING;
		err = create_raw_packet_qp_rq(dev, rq, in, pd,
					      to_mcq(init_attr->recv_cq));
		अगर (err)
			जाओ err_destroy_sq;

		err = create_raw_packet_qp_tir(dev, rq, tdn, &qp->flags_en, pd,
					       out);
		अगर (err)
			जाओ err_destroy_rq;

		अगर (uid) अणु
			resp->rqn = rq->base.mqp.qpn;
			resp->comp_mask |= MLX5_IB_CREATE_QP_RESP_MASK_RQN;
			resp->tirn = rq->tirn;
			resp->comp_mask |= MLX5_IB_CREATE_QP_RESP_MASK_TIRN;
			अगर (MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, sw_owner) ||
			    MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, sw_owner_v2)) अणु
				resp->tir_icm_addr = MLX5_GET(
					create_tir_out, out, icm_address_31_0);
				resp->tir_icm_addr |=
					(u64)MLX5_GET(create_tir_out, out,
						      icm_address_39_32)
					<< 32;
				resp->tir_icm_addr |=
					(u64)MLX5_GET(create_tir_out, out,
						      icm_address_63_40)
					<< 40;
				resp->comp_mask |=
					MLX5_IB_CREATE_QP_RESP_MASK_TIR_ICM_ADDR;
			पूर्ण
		पूर्ण
	पूर्ण

	qp->trans_qp.base.mqp.qpn = qp->sq.wqe_cnt ? sq->base.mqp.qpn :
						     rq->base.mqp.qpn;
	वापस 0;

err_destroy_rq:
	destroy_raw_packet_qp_rq(dev, rq);
err_destroy_sq:
	अगर (!qp->sq.wqe_cnt)
		वापस err;
	destroy_raw_packet_qp_sq(dev, sq);
err_destroy_tis:
	destroy_raw_packet_qp_tis(dev, sq, pd);

	वापस err;
पूर्ण

अटल व्योम destroy_raw_packet_qp(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_ib_qp *qp)
अणु
	काष्ठा mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	काष्ठा mlx5_ib_sq *sq = &raw_packet_qp->sq;
	काष्ठा mlx5_ib_rq *rq = &raw_packet_qp->rq;

	अगर (qp->rq.wqe_cnt) अणु
		destroy_raw_packet_qp_tir(dev, rq, qp->flags_en, qp->ibqp.pd);
		destroy_raw_packet_qp_rq(dev, rq);
	पूर्ण

	अगर (qp->sq.wqe_cnt) अणु
		destroy_raw_packet_qp_sq(dev, sq);
		destroy_raw_packet_qp_tis(dev, sq, qp->ibqp.pd);
	पूर्ण
पूर्ण

अटल व्योम raw_packet_qp_copy_info(काष्ठा mlx5_ib_qp *qp,
				    काष्ठा mlx5_ib_raw_packet_qp *raw_packet_qp)
अणु
	काष्ठा mlx5_ib_sq *sq = &raw_packet_qp->sq;
	काष्ठा mlx5_ib_rq *rq = &raw_packet_qp->rq;

	sq->sq = &qp->sq;
	rq->rq = &qp->rq;
	sq->करोorbell = &qp->db;
	rq->करोorbell = &qp->db;
पूर्ण

अटल व्योम destroy_rss_raw_qp_tir(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp)
अणु
	अगर (qp->flags_en & (MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC |
			    MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC))
		mlx5_ib_disable_lb(dev, false, true);
	mlx5_cmd_destroy_tir(dev->mdev, qp->rss_qp.tirn,
			     to_mpd(qp->ibqp.pd)->uid);
पूर्ण

काष्ठा mlx5_create_qp_params अणु
	काष्ठा ib_udata *udata;
	माप_प्रकार inlen;
	माप_प्रकार outlen;
	माप_प्रकार ucmd_size;
	व्योम *ucmd;
	u8 is_rss_raw : 1;
	काष्ठा ib_qp_init_attr *attr;
	u32 uidx;
	काष्ठा mlx5_ib_create_qp_resp resp;
पूर्ण;

अटल पूर्णांक create_rss_raw_qp_tir(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
				 काष्ठा mlx5_ib_qp *qp,
				 काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा ib_qp_init_attr *init_attr = params->attr;
	काष्ठा mlx5_ib_create_qp_rss *ucmd = params->ucmd;
	काष्ठा ib_udata *udata = params->udata;
	काष्ठा mlx5_ib_ucontext *mucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	पूर्णांक inlen;
	पूर्णांक outlen;
	पूर्णांक err;
	u32 *in;
	u32 *out;
	व्योम *tirc;
	व्योम *hfso;
	u32 selected_fields = 0;
	u32 outer_l4;
	u32 tdn = mucontext->tdn;
	u8 lb_flag = 0;

	अगर (ucmd->comp_mask) अणु
		mlx5_ib_dbg(dev, "invalid comp mask\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_INNER &&
	    !(ucmd->flags & MLX5_QP_FLAG_TUNNEL_OFFLOADS)) अणु
		mlx5_ib_dbg(dev, "Tunnel offloads must be set for inner RSS\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (dev->is_rep)
		qp->flags_en |= MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC;

	अगर (qp->flags_en & MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC)
		lb_flag |= MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST;

	अगर (qp->flags_en & MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC)
		lb_flag |= MLX5_TIRC_SELF_LB_BLOCK_BLOCK_MULTICAST;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	outlen = MLX5_ST_SZ_BYTES(create_tir_out);
	in = kvzalloc(inlen + outlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	out = in + MLX5_ST_SZ_DW(create_tir_in);
	MLX5_SET(create_tir_in, in, uid, to_mpd(pd)->uid);
	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
	MLX5_SET(tirc, tirc, disp_type,
		 MLX5_TIRC_DISP_TYPE_INसूचीECT);
	MLX5_SET(tirc, tirc, indirect_table,
		 init_attr->rwq_ind_tbl->ind_tbl_num);
	MLX5_SET(tirc, tirc, transport_करोमुख्य, tdn);

	hfso = MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_outer);

	अगर (ucmd->flags & MLX5_QP_FLAG_TUNNEL_OFFLOADS)
		MLX5_SET(tirc, tirc, tunneled_offload_en, 1);

	MLX5_SET(tirc, tirc, self_lb_block, lb_flag);

	अगर (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_INNER)
		hfso = MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_inner);
	अन्यथा
		hfso = MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_outer);

	चयन (ucmd->rx_hash_function) अणु
	हाल MLX5_RX_HASH_FUNC_TOEPLITZ:
	अणु
		व्योम *rss_key = MLX5_ADDR_OF(tirc, tirc, rx_hash_toeplitz_key);
		माप_प्रकार len = MLX5_FLD_SZ_BYTES(tirc, rx_hash_toeplitz_key);

		अगर (len != ucmd->rx_key_len) अणु
			err = -EINVAL;
			जाओ err;
		पूर्ण

		MLX5_SET(tirc, tirc, rx_hash_fn, MLX5_RX_HASH_FN_TOEPLITZ);
		स_नकल(rss_key, ucmd->rx_hash_key, len);
		अवरोध;
	पूर्ण
	शेष:
		err = -EOPNOTSUPP;
		जाओ err;
	पूर्ण

	अगर (!ucmd->rx_hash_fields_mask) अणु
		/* special हाल when this TIR serves as steering entry without hashing */
		अगर (!init_attr->rwq_ind_tbl->log_ind_tbl_size)
			जाओ create_tir;
		err = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_IPV4) ||
	     (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_IPV4)) &&
	     ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_IPV6) ||
	     (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_IPV6))) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/* If none of IPV4 & IPV6 SRC/DST was set - this bit field is ignored */
	अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_IPV4) ||
	    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_IPV4))
		MLX5_SET(rx_hash_field_select, hfso, l3_prot_type,
			 MLX5_L3_PROT_TYPE_IPV4);
	अन्यथा अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_IPV6) ||
		 (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_IPV6))
		MLX5_SET(rx_hash_field_select, hfso, l3_prot_type,
			 MLX5_L3_PROT_TYPE_IPV6);

	outer_l4 = ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_PORT_TCP) ||
		    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_PORT_TCP))
			   << 0 |
		   ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_PORT_UDP) ||
		    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_PORT_UDP))
			   << 1 |
		   (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_IPSEC_SPI) << 2;

	/* Check that only one l4 protocol is set */
	अगर (outer_l4 & (outer_l4 - 1)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/* If none of TCP & UDP SRC/DST was set - this bit field is ignored */
	अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_PORT_TCP) ||
	    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_PORT_TCP))
		MLX5_SET(rx_hash_field_select, hfso, l4_prot_type,
			 MLX5_L4_PROT_TYPE_TCP);
	अन्यथा अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_PORT_UDP) ||
		 (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_PORT_UDP))
		MLX5_SET(rx_hash_field_select, hfso, l4_prot_type,
			 MLX5_L4_PROT_TYPE_UDP);

	अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_IPV4) ||
	    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_IPV6))
		selected_fields |= MLX5_HASH_FIELD_SEL_SRC_IP;

	अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_IPV4) ||
	    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_IPV6))
		selected_fields |= MLX5_HASH_FIELD_SEL_DST_IP;

	अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_PORT_TCP) ||
	    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_SRC_PORT_UDP))
		selected_fields |= MLX5_HASH_FIELD_SEL_L4_SPORT;

	अगर ((ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_PORT_TCP) ||
	    (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_DST_PORT_UDP))
		selected_fields |= MLX5_HASH_FIELD_SEL_L4_DPORT;

	अगर (ucmd->rx_hash_fields_mask & MLX5_RX_HASH_IPSEC_SPI)
		selected_fields |= MLX5_HASH_FIELD_SEL_IPSEC_SPI;

	MLX5_SET(rx_hash_field_select, hfso, selected_fields, selected_fields);

create_tir:
	MLX5_SET(create_tir_in, in, opcode, MLX5_CMD_OP_CREATE_TIR);
	err = mlx5_cmd_exec_inout(dev->mdev, create_tir, in, out);

	qp->rss_qp.tirn = MLX5_GET(create_tir_out, out, tirn);
	अगर (!err && MLX5_GET(tirc, tirc, self_lb_block)) अणु
		err = mlx5_ib_enable_lb(dev, false, true);

		अगर (err)
			mlx5_cmd_destroy_tir(dev->mdev, qp->rss_qp.tirn,
					     to_mpd(pd)->uid);
	पूर्ण

	अगर (err)
		जाओ err;

	अगर (mucontext->devx_uid) अणु
		params->resp.comp_mask |= MLX5_IB_CREATE_QP_RESP_MASK_TIRN;
		params->resp.tirn = qp->rss_qp.tirn;
		अगर (MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, sw_owner) ||
		    MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, sw_owner_v2)) अणु
			params->resp.tir_icm_addr =
				MLX5_GET(create_tir_out, out, icm_address_31_0);
			params->resp.tir_icm_addr |=
				(u64)MLX5_GET(create_tir_out, out,
					      icm_address_39_32)
				<< 32;
			params->resp.tir_icm_addr |=
				(u64)MLX5_GET(create_tir_out, out,
					      icm_address_63_40)
				<< 40;
			params->resp.comp_mask |=
				MLX5_IB_CREATE_QP_RESP_MASK_TIR_ICM_ADDR;
		पूर्ण
	पूर्ण

	kvमुक्त(in);
	/* qpn is reserved क्रम that QP */
	qp->trans_qp.base.mqp.qpn = 0;
	qp->is_rss = true;
	वापस 0;

err:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम configure_requester_scat_cqe(काष्ठा mlx5_ib_dev *dev,
					 काष्ठा mlx5_ib_qp *qp,
					 काष्ठा ib_qp_init_attr *init_attr,
					 व्योम *qpc)
अणु
	पूर्णांक scqe_sz;
	bool allow_scat_cqe = false;

	allow_scat_cqe = qp->flags_en & MLX5_QP_FLAG_ALLOW_SCATTER_CQE;

	अगर (!allow_scat_cqe && init_attr->sq_sig_type != IB_SIGNAL_ALL_WR)
		वापस;

	scqe_sz = mlx5_ib_get_cqe_size(init_attr->send_cq);
	अगर (scqe_sz == 128) अणु
		MLX5_SET(qpc, qpc, cs_req, MLX5_REQ_SCAT_DATA64_CQE);
		वापस;
	पूर्ण

	अगर (init_attr->qp_type != MLX5_IB_QPT_DCI ||
	    MLX5_CAP_GEN(dev->mdev, dc_req_scat_data_cqe))
		MLX5_SET(qpc, qpc, cs_req, MLX5_REQ_SCAT_DATA32_CQE);
पूर्ण

अटल पूर्णांक atomic_माप_प्रकारo_mode(पूर्णांक size_mask)
अणु
	/* driver करोes not support atomic_size > 256B
	 * and करोes not know how to translate bigger sizes
	 */
	पूर्णांक supported_size_mask = size_mask & 0x1ff;
	पूर्णांक log_max_size;

	अगर (!supported_size_mask)
		वापस -EOPNOTSUPP;

	log_max_size = __fls(supported_size_mask);

	अगर (log_max_size > 3)
		वापस log_max_size;

	वापस MLX5_ATOMIC_MODE_8B;
पूर्ण

अटल पूर्णांक get_atomic_mode(काष्ठा mlx5_ib_dev *dev,
			   क्रमागत ib_qp_type qp_type)
अणु
	u8 atomic_operations = MLX5_CAP_ATOMIC(dev->mdev, atomic_operations);
	u8 atomic = MLX5_CAP_GEN(dev->mdev, atomic);
	पूर्णांक atomic_mode = -EOPNOTSUPP;
	पूर्णांक atomic_size_mask;

	अगर (!atomic)
		वापस -EOPNOTSUPP;

	अगर (qp_type == MLX5_IB_QPT_DCT)
		atomic_size_mask = MLX5_CAP_ATOMIC(dev->mdev, atomic_size_dc);
	अन्यथा
		atomic_size_mask = MLX5_CAP_ATOMIC(dev->mdev, atomic_size_qp);

	अगर ((atomic_operations & MLX5_ATOMIC_OPS_EXTENDED_CMP_SWAP) ||
	    (atomic_operations & MLX5_ATOMIC_OPS_EXTENDED_FETCH_ADD))
		atomic_mode = atomic_माप_प्रकारo_mode(atomic_size_mask);

	अगर (atomic_mode <= 0 &&
	    (atomic_operations & MLX5_ATOMIC_OPS_CMP_SWAP &&
	     atomic_operations & MLX5_ATOMIC_OPS_FETCH_ADD))
		atomic_mode = MLX5_ATOMIC_MODE_IB_COMP;

	वापस atomic_mode;
पूर्ण

अटल पूर्णांक create_xrc_tgt_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			     काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा mlx5_ib_create_qp *ucmd = params->ucmd;
	काष्ठा ib_qp_init_attr *attr = params->attr;
	u32 uidx = params->uidx;
	काष्ठा mlx5_ib_resources *devr = &dev->devr;
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_qp_in);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_ib_qp_base *base;
	अचिन्हित दीर्घ flags;
	व्योम *qpc;
	u32 *in;
	पूर्णांक err;

	अगर (attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		qp->sq_संकेत_bits = MLX5_WQE_CTRL_CQ_UPDATE;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	अगर (MLX5_CAP_GEN(mdev, ece_support) && ucmd)
		MLX5_SET(create_qp_in, in, ece, ucmd->ece_options);
	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_XRC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, pd, to_mpd(devr->p0)->pdn);

	अगर (qp->flags & IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK)
		MLX5_SET(qpc, qpc, block_lb_mc, 1);
	अगर (qp->flags & IB_QP_CREATE_CROSS_CHANNEL)
		MLX5_SET(qpc, qpc, cd_master, 1);
	अगर (qp->flags & IB_QP_CREATE_MANAGED_SEND)
		MLX5_SET(qpc, qpc, cd_slave_send, 1);
	अगर (qp->flags & IB_QP_CREATE_MANAGED_RECV)
		MLX5_SET(qpc, qpc, cd_slave_receive, 1);

	MLX5_SET(qpc, qpc, ts_क्रमmat, mlx5_get_qp_शेष_ts(dev->mdev));
	MLX5_SET(qpc, qpc, rq_type, MLX5_SRQ_RQ);
	MLX5_SET(qpc, qpc, no_sq, 1);
	MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(devr->c0)->mcq.cqn);
	MLX5_SET(qpc, qpc, cqn_snd, to_mcq(devr->c0)->mcq.cqn);
	MLX5_SET(qpc, qpc, srqn_rmpn_xrqn, to_msrq(devr->s0)->msrq.srqn);
	MLX5_SET(qpc, qpc, xrcd, to_mxrcd(attr->xrcd)->xrcdn);
	MLX5_SET64(qpc, qpc, dbr_addr, qp->db.dma);

	/* 0xffffff means we ask to work with cqe version 0 */
	अगर (MLX5_CAP_GEN(mdev, cqe_version) == MLX5_CQE_VERSION_V1)
		MLX5_SET(qpc, qpc, user_index, uidx);

	अगर (qp->flags & IB_QP_CREATE_PCI_WRITE_END_PADDING) अणु
		MLX5_SET(qpc, qpc, end_padding_mode,
			 MLX5_WQ_END_PAD_MODE_ALIGN);
		/* Special हाल to clean flag */
		qp->flags &= ~IB_QP_CREATE_PCI_WRITE_END_PADDING;
	पूर्ण

	base = &qp->trans_qp.base;
	err = mlx5_qpc_create_qp(dev, &base->mqp, in, inlen, out);
	kvमुक्त(in);
	अगर (err)
		वापस err;

	base->container_mibqp = qp;
	base->mqp.event = mlx5_ib_qp_event;
	अगर (MLX5_CAP_GEN(mdev, ece_support))
		params->resp.ece_options = MLX5_GET(create_qp_out, out, ece);

	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	list_add_tail(&qp->qps_list, &dev->qp_list);
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

	qp->trans_qp.xrcdn = to_mxrcd(attr->xrcd)->xrcdn;
	वापस 0;
पूर्ण

अटल पूर्णांक create_user_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
			  काष्ठा mlx5_ib_qp *qp,
			  काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा ib_qp_init_attr *init_attr = params->attr;
	काष्ठा mlx5_ib_create_qp *ucmd = params->ucmd;
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	काष्ठा ib_udata *udata = params->udata;
	u32 uidx = params->uidx;
	काष्ठा mlx5_ib_resources *devr = &dev->devr;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_qp_in);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_ib_cq *send_cq;
	काष्ठा mlx5_ib_cq *recv_cq;
	अचिन्हित दीर्घ flags;
	काष्ठा mlx5_ib_qp_base *base;
	पूर्णांक ts_क्रमmat;
	पूर्णांक mlx5_st;
	व्योम *qpc;
	u32 *in;
	पूर्णांक err;

	spin_lock_init(&qp->sq.lock);
	spin_lock_init(&qp->rq.lock);

	mlx5_st = to_mlx5_st(qp->type);
	अगर (mlx5_st < 0)
		वापस -EINVAL;

	अगर (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		qp->sq_संकेत_bits = MLX5_WQE_CTRL_CQ_UPDATE;

	अगर (qp->flags & IB_QP_CREATE_SOURCE_QPN)
		qp->underlay_qpn = init_attr->source_qpn;

	base = (init_attr->qp_type == IB_QPT_RAW_PACKET ||
		qp->flags & IB_QP_CREATE_SOURCE_QPN) ?
	       &qp->raw_packet_qp.rq.base :
	       &qp->trans_qp.base;

	qp->has_rq = qp_has_rq(init_attr);
	err = set_rq_size(dev, &init_attr->cap, qp->has_rq, qp, ucmd);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		वापस err;
	पूर्ण

	अगर (ucmd->rq_wqe_shअगरt != qp->rq.wqe_shअगरt ||
	    ucmd->rq_wqe_count != qp->rq.wqe_cnt)
		वापस -EINVAL;

	अगर (ucmd->sq_wqe_count > (1 << MLX5_CAP_GEN(mdev, log_max_qp_sz)))
		वापस -EINVAL;

	अगर (init_attr->qp_type != IB_QPT_RAW_PACKET) अणु
		ts_क्रमmat = get_qp_ts_क्रमmat(dev, to_mcq(init_attr->send_cq),
					     to_mcq(init_attr->recv_cq));
		अगर (ts_क्रमmat < 0)
			वापस ts_क्रमmat;
	पूर्ण

	err = _create_user_qp(dev, pd, qp, udata, init_attr, &in, &params->resp,
			      &inlen, base, ucmd);
	अगर (err)
		वापस err;

	अगर (is_sqp(init_attr->qp_type))
		qp->port = init_attr->port_num;

	अगर (MLX5_CAP_GEN(mdev, ece_support))
		MLX5_SET(create_qp_in, in, ece, ucmd->ece_options);
	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, st, mlx5_st);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, pd, to_mpd(pd)->pdn);

	अगर (qp->flags_en & MLX5_QP_FLAG_SIGNATURE)
		MLX5_SET(qpc, qpc, wq_signature, 1);

	अगर (qp->flags & IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK)
		MLX5_SET(qpc, qpc, block_lb_mc, 1);

	अगर (qp->flags & IB_QP_CREATE_CROSS_CHANNEL)
		MLX5_SET(qpc, qpc, cd_master, 1);
	अगर (qp->flags & IB_QP_CREATE_MANAGED_SEND)
		MLX5_SET(qpc, qpc, cd_slave_send, 1);
	अगर (qp->flags & IB_QP_CREATE_MANAGED_RECV)
		MLX5_SET(qpc, qpc, cd_slave_receive, 1);
	अगर (qp->flags_en & MLX5_QP_FLAG_PACKET_BASED_CREDIT_MODE)
		MLX5_SET(qpc, qpc, req_e2e_credit_mode, 1);
	अगर ((qp->flags_en & MLX5_QP_FLAG_SCATTER_CQE) &&
	    (init_attr->qp_type == IB_QPT_RC ||
	     init_attr->qp_type == IB_QPT_UC)) अणु
		पूर्णांक rcqe_sz = mlx5_ib_get_cqe_size(init_attr->recv_cq);

		MLX5_SET(qpc, qpc, cs_res,
			 rcqe_sz == 128 ? MLX5_RES_SCAT_DATA64_CQE :
					  MLX5_RES_SCAT_DATA32_CQE);
	पूर्ण
	अगर ((qp->flags_en & MLX5_QP_FLAG_SCATTER_CQE) &&
	    (qp->type == MLX5_IB_QPT_DCI || qp->type == IB_QPT_RC))
		configure_requester_scat_cqe(dev, qp, init_attr, qpc);

	अगर (qp->rq.wqe_cnt) अणु
		MLX5_SET(qpc, qpc, log_rq_stride, qp->rq.wqe_shअगरt - 4);
		MLX5_SET(qpc, qpc, log_rq_size, ilog2(qp->rq.wqe_cnt));
	पूर्ण

	अगर (init_attr->qp_type != IB_QPT_RAW_PACKET)
		MLX5_SET(qpc, qpc, ts_क्रमmat, ts_क्रमmat);

	MLX5_SET(qpc, qpc, rq_type, get_rx_type(qp, init_attr));

	अगर (qp->sq.wqe_cnt) अणु
		MLX5_SET(qpc, qpc, log_sq_size, ilog2(qp->sq.wqe_cnt));
	पूर्ण अन्यथा अणु
		MLX5_SET(qpc, qpc, no_sq, 1);
		अगर (init_attr->srq &&
		    init_attr->srq->srq_type == IB_SRQT_TM)
			MLX5_SET(qpc, qpc, offload_type,
				 MLX5_QPC_OFFLOAD_TYPE_RNDV);
	पूर्ण

	/* Set शेष resources */
	चयन (init_attr->qp_type) अणु
	हाल IB_QPT_XRC_INI:
		MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(devr->c0)->mcq.cqn);
		MLX5_SET(qpc, qpc, xrcd, devr->xrcdn1);
		MLX5_SET(qpc, qpc, srqn_rmpn_xrqn, to_msrq(devr->s0)->msrq.srqn);
		अवरोध;
	शेष:
		अगर (init_attr->srq) अणु
			MLX5_SET(qpc, qpc, xrcd, devr->xrcdn0);
			MLX5_SET(qpc, qpc, srqn_rmpn_xrqn, to_msrq(init_attr->srq)->msrq.srqn);
		पूर्ण अन्यथा अणु
			MLX5_SET(qpc, qpc, xrcd, devr->xrcdn1);
			MLX5_SET(qpc, qpc, srqn_rmpn_xrqn, to_msrq(devr->s1)->msrq.srqn);
		पूर्ण
	पूर्ण

	अगर (init_attr->send_cq)
		MLX5_SET(qpc, qpc, cqn_snd, to_mcq(init_attr->send_cq)->mcq.cqn);

	अगर (init_attr->recv_cq)
		MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(init_attr->recv_cq)->mcq.cqn);

	MLX5_SET64(qpc, qpc, dbr_addr, qp->db.dma);

	/* 0xffffff means we ask to work with cqe version 0 */
	अगर (MLX5_CAP_GEN(mdev, cqe_version) == MLX5_CQE_VERSION_V1)
		MLX5_SET(qpc, qpc, user_index, uidx);

	अगर (qp->flags & IB_QP_CREATE_PCI_WRITE_END_PADDING &&
	    init_attr->qp_type != IB_QPT_RAW_PACKET) अणु
		MLX5_SET(qpc, qpc, end_padding_mode,
			 MLX5_WQ_END_PAD_MODE_ALIGN);
		/* Special हाल to clean flag */
		qp->flags &= ~IB_QP_CREATE_PCI_WRITE_END_PADDING;
	पूर्ण

	अगर (init_attr->qp_type == IB_QPT_RAW_PACKET ||
	    qp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		qp->raw_packet_qp.sq.ubuffer.buf_addr = ucmd->sq_buf_addr;
		raw_packet_qp_copy_info(qp, &qp->raw_packet_qp);
		err = create_raw_packet_qp(dev, qp, in, inlen, pd, udata,
					   &params->resp, init_attr);
	पूर्ण अन्यथा
		err = mlx5_qpc_create_qp(dev, &base->mqp, in, inlen, out);

	kvमुक्त(in);
	अगर (err)
		जाओ err_create;

	base->container_mibqp = qp;
	base->mqp.event = mlx5_ib_qp_event;
	अगर (MLX5_CAP_GEN(mdev, ece_support))
		params->resp.ece_options = MLX5_GET(create_qp_out, out, ece);

	get_cqs(qp->type, init_attr->send_cq, init_attr->recv_cq,
		&send_cq, &recv_cq);
	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx5_ib_lock_cqs(send_cq, recv_cq);
	/* Maपूर्णांकain device to QPs access, needed क्रम further handling via reset
	 * flow
	 */
	list_add_tail(&qp->qps_list, &dev->qp_list);
	/* Maपूर्णांकain CQ to QPs access, needed क्रम further handling via reset flow
	 */
	अगर (send_cq)
		list_add_tail(&qp->cq_send_list, &send_cq->list_send_qp);
	अगर (recv_cq)
		list_add_tail(&qp->cq_recv_list, &recv_cq->list_recv_qp);
	mlx5_ib_unlock_cqs(send_cq, recv_cq);
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

	वापस 0;

err_create:
	destroy_qp(dev, qp, base, udata);
	वापस err;
पूर्ण

अटल पूर्णांक create_kernel_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
			    काष्ठा mlx5_ib_qp *qp,
			    काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा ib_qp_init_attr *attr = params->attr;
	u32 uidx = params->uidx;
	काष्ठा mlx5_ib_resources *devr = &dev->devr;
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_qp_in);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_ib_cq *send_cq;
	काष्ठा mlx5_ib_cq *recv_cq;
	अचिन्हित दीर्घ flags;
	काष्ठा mlx5_ib_qp_base *base;
	पूर्णांक mlx5_st;
	व्योम *qpc;
	u32 *in;
	पूर्णांक err;

	spin_lock_init(&qp->sq.lock);
	spin_lock_init(&qp->rq.lock);

	mlx5_st = to_mlx5_st(qp->type);
	अगर (mlx5_st < 0)
		वापस -EINVAL;

	अगर (attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		qp->sq_संकेत_bits = MLX5_WQE_CTRL_CQ_UPDATE;

	base = &qp->trans_qp.base;

	qp->has_rq = qp_has_rq(attr);
	err = set_rq_size(dev, &attr->cap, qp->has_rq, qp, शून्य);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		वापस err;
	पूर्ण

	err = _create_kernel_qp(dev, attr, qp, &in, &inlen, base);
	अगर (err)
		वापस err;

	अगर (is_sqp(attr->qp_type))
		qp->port = attr->port_num;

	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, st, mlx5_st);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);

	अगर (attr->qp_type != MLX5_IB_QPT_REG_UMR)
		MLX5_SET(qpc, qpc, pd, to_mpd(pd ? pd : devr->p0)->pdn);
	अन्यथा
		MLX5_SET(qpc, qpc, latency_sensitive, 1);


	अगर (qp->flags & IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK)
		MLX5_SET(qpc, qpc, block_lb_mc, 1);

	अगर (qp->rq.wqe_cnt) अणु
		MLX5_SET(qpc, qpc, log_rq_stride, qp->rq.wqe_shअगरt - 4);
		MLX5_SET(qpc, qpc, log_rq_size, ilog2(qp->rq.wqe_cnt));
	पूर्ण

	MLX5_SET(qpc, qpc, rq_type, get_rx_type(qp, attr));

	अगर (qp->sq.wqe_cnt)
		MLX5_SET(qpc, qpc, log_sq_size, ilog2(qp->sq.wqe_cnt));
	अन्यथा
		MLX5_SET(qpc, qpc, no_sq, 1);

	अगर (attr->srq) अणु
		MLX5_SET(qpc, qpc, xrcd, devr->xrcdn0);
		MLX5_SET(qpc, qpc, srqn_rmpn_xrqn,
			 to_msrq(attr->srq)->msrq.srqn);
	पूर्ण अन्यथा अणु
		MLX5_SET(qpc, qpc, xrcd, devr->xrcdn1);
		MLX5_SET(qpc, qpc, srqn_rmpn_xrqn,
			 to_msrq(devr->s1)->msrq.srqn);
	पूर्ण

	अगर (attr->send_cq)
		MLX5_SET(qpc, qpc, cqn_snd, to_mcq(attr->send_cq)->mcq.cqn);

	अगर (attr->recv_cq)
		MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(attr->recv_cq)->mcq.cqn);

	MLX5_SET64(qpc, qpc, dbr_addr, qp->db.dma);

	/* 0xffffff means we ask to work with cqe version 0 */
	अगर (MLX5_CAP_GEN(mdev, cqe_version) == MLX5_CQE_VERSION_V1)
		MLX5_SET(qpc, qpc, user_index, uidx);

	/* we use IB_QP_CREATE_IPOIB_UD_LSO to indicates ipoib qp */
	अगर (qp->flags & IB_QP_CREATE_IPOIB_UD_LSO)
		MLX5_SET(qpc, qpc, ulp_stateless_offload_mode, 1);

	err = mlx5_qpc_create_qp(dev, &base->mqp, in, inlen, out);
	kvमुक्त(in);
	अगर (err)
		जाओ err_create;

	base->container_mibqp = qp;
	base->mqp.event = mlx5_ib_qp_event;

	get_cqs(qp->type, attr->send_cq, attr->recv_cq,
		&send_cq, &recv_cq);
	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx5_ib_lock_cqs(send_cq, recv_cq);
	/* Maपूर्णांकain device to QPs access, needed क्रम further handling via reset
	 * flow
	 */
	list_add_tail(&qp->qps_list, &dev->qp_list);
	/* Maपूर्णांकain CQ to QPs access, needed क्रम further handling via reset flow
	 */
	अगर (send_cq)
		list_add_tail(&qp->cq_send_list, &send_cq->list_send_qp);
	अगर (recv_cq)
		list_add_tail(&qp->cq_recv_list, &recv_cq->list_recv_qp);
	mlx5_ib_unlock_cqs(send_cq, recv_cq);
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

	वापस 0;

err_create:
	destroy_qp(dev, qp, base, शून्य);
	वापस err;
पूर्ण

अटल व्योम mlx5_ib_lock_cqs(काष्ठा mlx5_ib_cq *send_cq, काष्ठा mlx5_ib_cq *recv_cq)
	__acquires(&send_cq->lock) __acquires(&recv_cq->lock)
अणु
	अगर (send_cq) अणु
		अगर (recv_cq) अणु
			अगर (send_cq->mcq.cqn < recv_cq->mcq.cqn)  अणु
				spin_lock(&send_cq->lock);
				spin_lock_nested(&recv_cq->lock,
						 SINGLE_DEPTH_NESTING);
			पूर्ण अन्यथा अगर (send_cq->mcq.cqn == recv_cq->mcq.cqn) अणु
				spin_lock(&send_cq->lock);
				__acquire(&recv_cq->lock);
			पूर्ण अन्यथा अणु
				spin_lock(&recv_cq->lock);
				spin_lock_nested(&send_cq->lock,
						 SINGLE_DEPTH_NESTING);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_lock(&send_cq->lock);
			__acquire(&recv_cq->lock);
		पूर्ण
	पूर्ण अन्यथा अगर (recv_cq) अणु
		spin_lock(&recv_cq->lock);
		__acquire(&send_cq->lock);
	पूर्ण अन्यथा अणु
		__acquire(&send_cq->lock);
		__acquire(&recv_cq->lock);
	पूर्ण
पूर्ण

अटल व्योम mlx5_ib_unlock_cqs(काष्ठा mlx5_ib_cq *send_cq, काष्ठा mlx5_ib_cq *recv_cq)
	__releases(&send_cq->lock) __releases(&recv_cq->lock)
अणु
	अगर (send_cq) अणु
		अगर (recv_cq) अणु
			अगर (send_cq->mcq.cqn < recv_cq->mcq.cqn)  अणु
				spin_unlock(&recv_cq->lock);
				spin_unlock(&send_cq->lock);
			पूर्ण अन्यथा अगर (send_cq->mcq.cqn == recv_cq->mcq.cqn) अणु
				__release(&recv_cq->lock);
				spin_unlock(&send_cq->lock);
			पूर्ण अन्यथा अणु
				spin_unlock(&send_cq->lock);
				spin_unlock(&recv_cq->lock);
			पूर्ण
		पूर्ण अन्यथा अणु
			__release(&recv_cq->lock);
			spin_unlock(&send_cq->lock);
		पूर्ण
	पूर्ण अन्यथा अगर (recv_cq) अणु
		__release(&send_cq->lock);
		spin_unlock(&recv_cq->lock);
	पूर्ण अन्यथा अणु
		__release(&recv_cq->lock);
		__release(&send_cq->lock);
	पूर्ण
पूर्ण

अटल व्योम get_cqs(क्रमागत ib_qp_type qp_type,
		    काष्ठा ib_cq *ib_send_cq, काष्ठा ib_cq *ib_recv_cq,
		    काष्ठा mlx5_ib_cq **send_cq, काष्ठा mlx5_ib_cq **recv_cq)
अणु
	चयन (qp_type) अणु
	हाल IB_QPT_XRC_TGT:
		*send_cq = शून्य;
		*recv_cq = शून्य;
		अवरोध;
	हाल MLX5_IB_QPT_REG_UMR:
	हाल IB_QPT_XRC_INI:
		*send_cq = ib_send_cq ? to_mcq(ib_send_cq) : शून्य;
		*recv_cq = शून्य;
		अवरोध;

	हाल IB_QPT_SMI:
	हाल MLX5_IB_QPT_HW_GSI:
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
	हाल IB_QPT_UD:
	हाल IB_QPT_RAW_PACKET:
		*send_cq = ib_send_cq ? to_mcq(ib_send_cq) : शून्य;
		*recv_cq = ib_recv_cq ? to_mcq(ib_recv_cq) : शून्य;
		अवरोध;
	शेष:
		*send_cq = शून्य;
		*recv_cq = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक modअगरy_raw_packet_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
				स्थिर काष्ठा mlx5_modअगरy_raw_qp_param *raw_qp_param,
				u8 lag_tx_affinity);

अटल व्योम destroy_qp_common(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			      काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_cq *send_cq, *recv_cq;
	काष्ठा mlx5_ib_qp_base *base;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (qp->is_rss) अणु
		destroy_rss_raw_qp_tir(dev, qp);
		वापस;
	पूर्ण

	base = (qp->type == IB_QPT_RAW_PACKET ||
		qp->flags & IB_QP_CREATE_SOURCE_QPN) ?
		       &qp->raw_packet_qp.rq.base :
		       &qp->trans_qp.base;

	अगर (qp->state != IB_QPS_RESET) अणु
		अगर (qp->type != IB_QPT_RAW_PACKET &&
		    !(qp->flags & IB_QP_CREATE_SOURCE_QPN)) अणु
			err = mlx5_core_qp_modअगरy(dev, MLX5_CMD_OP_2RST_QP, 0,
						  शून्य, &base->mqp, शून्य);
		पूर्ण अन्यथा अणु
			काष्ठा mlx5_modअगरy_raw_qp_param raw_qp_param = अणु
				.operation = MLX5_CMD_OP_2RST_QP
			पूर्ण;

			err = modअगरy_raw_packet_qp(dev, qp, &raw_qp_param, 0);
		पूर्ण
		अगर (err)
			mlx5_ib_warn(dev, "mlx5_ib: modify QP 0x%06x to RESET failed\n",
				     base->mqp.qpn);
	पूर्ण

	get_cqs(qp->type, qp->ibqp.send_cq, qp->ibqp.recv_cq, &send_cq,
		&recv_cq);

	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx5_ib_lock_cqs(send_cq, recv_cq);
	/* del from lists under both locks above to protect reset flow paths */
	list_del(&qp->qps_list);
	अगर (send_cq)
		list_del(&qp->cq_send_list);

	अगर (recv_cq)
		list_del(&qp->cq_recv_list);

	अगर (!udata) अणु
		__mlx5_ib_cq_clean(recv_cq, base->mqp.qpn,
				   qp->ibqp.srq ? to_msrq(qp->ibqp.srq) : शून्य);
		अगर (send_cq != recv_cq)
			__mlx5_ib_cq_clean(send_cq, base->mqp.qpn,
					   शून्य);
	पूर्ण
	mlx5_ib_unlock_cqs(send_cq, recv_cq);
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

	अगर (qp->type == IB_QPT_RAW_PACKET ||
	    qp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		destroy_raw_packet_qp(dev, qp);
	पूर्ण अन्यथा अणु
		err = mlx5_core_destroy_qp(dev, &base->mqp);
		अगर (err)
			mlx5_ib_warn(dev, "failed to destroy QP 0x%x\n",
				     base->mqp.qpn);
	पूर्ण

	destroy_qp(dev, qp, base, udata);
पूर्ण

अटल पूर्णांक create_dct(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
		      काष्ठा mlx5_ib_qp *qp,
		      काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा ib_qp_init_attr *attr = params->attr;
	काष्ठा mlx5_ib_create_qp *ucmd = params->ucmd;
	u32 uidx = params->uidx;
	व्योम *dctc;

	अगर (mlx5_lag_is_active(dev->mdev) && !MLX5_CAP_GEN(dev->mdev, lag_dct))
		वापस -EOPNOTSUPP;

	qp->dct.in = kzalloc(MLX5_ST_SZ_BYTES(create_dct_in), GFP_KERNEL);
	अगर (!qp->dct.in)
		वापस -ENOMEM;

	MLX5_SET(create_dct_in, qp->dct.in, uid, to_mpd(pd)->uid);
	dctc = MLX5_ADDR_OF(create_dct_in, qp->dct.in, dct_context_entry);
	MLX5_SET(dctc, dctc, pd, to_mpd(pd)->pdn);
	MLX5_SET(dctc, dctc, srqn_xrqn, to_msrq(attr->srq)->msrq.srqn);
	MLX5_SET(dctc, dctc, cqn, to_mcq(attr->recv_cq)->mcq.cqn);
	MLX5_SET64(dctc, dctc, dc_access_key, ucmd->access_key);
	MLX5_SET(dctc, dctc, user_index, uidx);
	अगर (MLX5_CAP_GEN(dev->mdev, ece_support))
		MLX5_SET(dctc, dctc, ece, ucmd->ece_options);

	अगर (qp->flags_en & MLX5_QP_FLAG_SCATTER_CQE) अणु
		पूर्णांक rcqe_sz = mlx5_ib_get_cqe_size(attr->recv_cq);

		अगर (rcqe_sz == 128)
			MLX5_SET(dctc, dctc, cs_res, MLX5_RES_SCAT_DATA64_CQE);
	पूर्ण

	qp->state = IB_QPS_RESET;
	rdma_restrack_no_track(&qp->ibqp.res);
	वापस 0;
पूर्ण

अटल पूर्णांक check_qp_type(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_qp_init_attr *attr,
			 क्रमागत ib_qp_type *type)
अणु
	अगर (attr->qp_type == IB_QPT_DRIVER && !MLX5_CAP_GEN(dev->mdev, dct))
		जाओ out;

	चयन (attr->qp_type) अणु
	हाल IB_QPT_XRC_TGT:
	हाल IB_QPT_XRC_INI:
		अगर (!MLX5_CAP_GEN(dev->mdev, xrc))
			जाओ out;
		fallthrough;
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
	हाल IB_QPT_SMI:
	हाल MLX5_IB_QPT_HW_GSI:
	हाल IB_QPT_DRIVER:
	हाल IB_QPT_GSI:
	हाल IB_QPT_RAW_PACKET:
	हाल IB_QPT_UD:
	हाल MLX5_IB_QPT_REG_UMR:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	*type = attr->qp_type;
	वापस 0;

out:
	mlx5_ib_dbg(dev, "Unsupported QP type %d\n", attr->qp_type);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक check_valid_flow(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
			    काष्ठा ib_qp_init_attr *attr,
			    काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	अगर (!udata) अणु
		/* Kernel create_qp callers */
		अगर (attr->rwq_ind_tbl)
			वापस -EOPNOTSUPP;

		चयन (attr->qp_type) अणु
		हाल IB_QPT_RAW_PACKET:
		हाल IB_QPT_DRIVER:
			वापस -EOPNOTSUPP;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	/* Userspace create_qp callers */
	अगर (attr->qp_type == IB_QPT_RAW_PACKET && !ucontext->cqe_version) अणु
		mlx5_ib_dbg(dev,
			"Raw Packet QP is only supported for CQE version > 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (attr->qp_type != IB_QPT_RAW_PACKET && attr->rwq_ind_tbl) अणु
		mlx5_ib_dbg(dev,
			    "Wrong QP type %d for the RWQ indirect table\n",
			    attr->qp_type);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We करोn't need to see this warning, it means that kernel code
	 * missing ib_pd. Placed here to catch developer's mistakes.
	 */
	WARN_ONCE(!pd && attr->qp_type != IB_QPT_XRC_TGT,
		  "There is a missing PD pointer assignment\n");
	वापस 0;
पूर्ण

अटल व्योम process_venकरोr_flag(काष्ठा mlx5_ib_dev *dev, पूर्णांक *flags, पूर्णांक flag,
				bool cond, काष्ठा mlx5_ib_qp *qp)
अणु
	अगर (!(*flags & flag))
		वापस;

	अगर (cond) अणु
		qp->flags_en |= flag;
		*flags &= ~flag;
		वापस;
	पूर्ण

	चयन (flag) अणु
	हाल MLX5_QP_FLAG_SCATTER_CQE:
	हाल MLX5_QP_FLAG_ALLOW_SCATTER_CQE:
		/*
			 * We करोn't वापस error अगर these flags were provided,
			 * and mlx5 करोesn't have right capability.
			 */
		*flags &= ~(MLX5_QP_FLAG_SCATTER_CQE |
			    MLX5_QP_FLAG_ALLOW_SCATTER_CQE);
		वापस;
	शेष:
		अवरोध;
	पूर्ण
	mlx5_ib_dbg(dev, "Vendor create QP flag 0x%X is not supported\n", flag);
पूर्ण

अटल पूर्णांक process_venकरोr_flags(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
				व्योम *ucmd, काष्ठा ib_qp_init_attr *attr)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	bool cond;
	पूर्णांक flags;

	अगर (attr->rwq_ind_tbl)
		flags = ((काष्ठा mlx5_ib_create_qp_rss *)ucmd)->flags;
	अन्यथा
		flags = ((काष्ठा mlx5_ib_create_qp *)ucmd)->flags;

	चयन (flags & (MLX5_QP_FLAG_TYPE_DCT | MLX5_QP_FLAG_TYPE_DCI)) अणु
	हाल MLX5_QP_FLAG_TYPE_DCI:
		qp->type = MLX5_IB_QPT_DCI;
		अवरोध;
	हाल MLX5_QP_FLAG_TYPE_DCT:
		qp->type = MLX5_IB_QPT_DCT;
		अवरोध;
	शेष:
		अगर (qp->type != IB_QPT_DRIVER)
			अवरोध;
		/*
		 * It is IB_QPT_DRIVER and or no subtype or
		 * wrong subtype were provided.
		 */
		वापस -EINVAL;
	पूर्ण

	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_TYPE_DCI, true, qp);
	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_TYPE_DCT, true, qp);

	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_SIGNATURE, true, qp);
	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_SCATTER_CQE,
			    MLX5_CAP_GEN(mdev, sctr_data_cqe), qp);
	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_ALLOW_SCATTER_CQE,
			    MLX5_CAP_GEN(mdev, sctr_data_cqe), qp);

	अगर (qp->type == IB_QPT_RAW_PACKET) अणु
		cond = MLX5_CAP_ETH(mdev, tunnel_stateless_vxlan) ||
		       MLX5_CAP_ETH(mdev, tunnel_stateless_gre) ||
		       MLX5_CAP_ETH(mdev, tunnel_stateless_geneve_rx);
		process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_TUNNEL_OFFLOADS,
				    cond, qp);
		process_venकरोr_flag(dev, &flags,
				    MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC, true,
				    qp);
		process_venकरोr_flag(dev, &flags,
				    MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC, true,
				    qp);
	पूर्ण

	अगर (qp->type == IB_QPT_RC)
		process_venकरोr_flag(dev, &flags,
				    MLX5_QP_FLAG_PACKET_BASED_CREDIT_MODE,
				    MLX5_CAP_GEN(mdev, qp_packet_based), qp);

	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_BFREG_INDEX, true, qp);
	process_venकरोr_flag(dev, &flags, MLX5_QP_FLAG_UAR_PAGE_INDEX, true, qp);

	cond = qp->flags_en & ~(MLX5_QP_FLAG_TUNNEL_OFFLOADS |
				MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC |
				MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC);
	अगर (attr->rwq_ind_tbl && cond) अणु
		mlx5_ib_dbg(dev, "RSS RAW QP has unsupported flags 0x%X\n",
			    cond);
		वापस -EINVAL;
	पूर्ण

	अगर (flags)
		mlx5_ib_dbg(dev, "udata has unsupported flags 0x%X\n", flags);

	वापस (flags) ? -EINVAL : 0;
	पूर्ण

अटल व्योम process_create_flag(काष्ठा mlx5_ib_dev *dev, पूर्णांक *flags, पूर्णांक flag,
				bool cond, काष्ठा mlx5_ib_qp *qp)
अणु
	अगर (!(*flags & flag))
		वापस;

	अगर (cond) अणु
		qp->flags |= flag;
		*flags &= ~flag;
		वापस;
	पूर्ण

	अगर (flag == MLX5_IB_QP_CREATE_WC_TEST) अणु
		/*
		 * Special हाल, अगर condition didn't meet, it won't be error,
		 * just dअगरferent in-kernel flow.
		 */
		*flags &= ~MLX5_IB_QP_CREATE_WC_TEST;
		वापस;
	पूर्ण
	mlx5_ib_dbg(dev, "Verbs create QP flag 0x%X is not supported\n", flag);
पूर्ण

अटल पूर्णांक process_create_flags(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
				काष्ठा ib_qp_init_attr *attr)
अणु
	क्रमागत ib_qp_type qp_type = qp->type;
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	पूर्णांक create_flags = attr->create_flags;
	bool cond;

	अगर (qp_type == MLX5_IB_QPT_DCT)
		वापस (create_flags) ? -EINVAL : 0;

	अगर (qp_type == IB_QPT_RAW_PACKET && attr->rwq_ind_tbl)
		वापस (create_flags) ? -EINVAL : 0;

	process_create_flag(dev, &create_flags, IB_QP_CREATE_NETIF_QP,
			    mlx5_get_flow_namespace(dev->mdev,
						    MLX5_FLOW_NAMESPACE_BYPASS),
			    qp);
	process_create_flag(dev, &create_flags,
			    IB_QP_CREATE_INTEGRITY_EN,
			    MLX5_CAP_GEN(mdev, sho), qp);
	process_create_flag(dev, &create_flags,
			    IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK,
			    MLX5_CAP_GEN(mdev, block_lb_mc), qp);
	process_create_flag(dev, &create_flags, IB_QP_CREATE_CROSS_CHANNEL,
			    MLX5_CAP_GEN(mdev, cd), qp);
	process_create_flag(dev, &create_flags, IB_QP_CREATE_MANAGED_SEND,
			    MLX5_CAP_GEN(mdev, cd), qp);
	process_create_flag(dev, &create_flags, IB_QP_CREATE_MANAGED_RECV,
			    MLX5_CAP_GEN(mdev, cd), qp);

	अगर (qp_type == IB_QPT_UD) अणु
		process_create_flag(dev, &create_flags,
				    IB_QP_CREATE_IPOIB_UD_LSO,
				    MLX5_CAP_GEN(mdev, ipoib_basic_offloads),
				    qp);
		cond = MLX5_CAP_GEN(mdev, port_type) == MLX5_CAP_PORT_TYPE_IB;
		process_create_flag(dev, &create_flags, IB_QP_CREATE_SOURCE_QPN,
				    cond, qp);
	पूर्ण

	अगर (qp_type == IB_QPT_RAW_PACKET) अणु
		cond = MLX5_CAP_GEN(mdev, eth_net_offloads) &&
		       MLX5_CAP_ETH(mdev, scatter_fcs);
		process_create_flag(dev, &create_flags,
				    IB_QP_CREATE_SCATTER_FCS, cond, qp);

		cond = MLX5_CAP_GEN(mdev, eth_net_offloads) &&
		       MLX5_CAP_ETH(mdev, vlan_cap);
		process_create_flag(dev, &create_flags,
				    IB_QP_CREATE_CVLAN_STRIPPING, cond, qp);
	पूर्ण

	process_create_flag(dev, &create_flags,
			    IB_QP_CREATE_PCI_WRITE_END_PADDING,
			    MLX5_CAP_GEN(mdev, end_pad), qp);

	process_create_flag(dev, &create_flags, MLX5_IB_QP_CREATE_WC_TEST,
			    qp_type != MLX5_IB_QPT_REG_UMR, qp);
	process_create_flag(dev, &create_flags, MLX5_IB_QP_CREATE_SQPN_QP1,
			    true, qp);

	अगर (create_flags) अणु
		mlx5_ib_dbg(dev, "Create QP has unsupported flags 0x%X\n",
			    create_flags);
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक process_udata_size(काष्ठा mlx5_ib_dev *dev,
			      काष्ठा mlx5_create_qp_params *params)
अणु
	माप_प्रकार ucmd = माप(काष्ठा mlx5_ib_create_qp);
	काष्ठा ib_udata *udata = params->udata;
	माप_प्रकार outlen = udata->outlen;
	माप_प्रकार inlen = udata->inlen;

	params->outlen = min(outlen, माप(काष्ठा mlx5_ib_create_qp_resp));
	params->ucmd_size = ucmd;
	अगर (!params->is_rss_raw) अणु
		/* User has old rdma-core, which करोesn't support ECE */
		माप_प्रकार min_inlen =
			दुरत्व(काष्ठा mlx5_ib_create_qp, ece_options);

		/*
		 * We will check in check_ucmd_data() that user
		 * cleared everything after inlen.
		 */
		params->inlen = (inlen < min_inlen) ? 0 : min(inlen, ucmd);
		जाओ out;
	पूर्ण

	/* RSS RAW QP */
	अगर (inlen < दुरत्वend(काष्ठा mlx5_ib_create_qp_rss, flags))
		वापस -EINVAL;

	अगर (outlen < दुरत्वend(काष्ठा mlx5_ib_create_qp_resp, bfreg_index))
		वापस -EINVAL;

	ucmd = माप(काष्ठा mlx5_ib_create_qp_rss);
	params->ucmd_size = ucmd;
	अगर (inlen > ucmd && !ib_is_udata_cleared(udata, ucmd, inlen - ucmd))
		वापस -EINVAL;

	params->inlen = min(ucmd, inlen);
out:
	अगर (!params->inlen)
		mlx5_ib_dbg(dev, "udata is too small\n");

	वापस (params->inlen) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक create_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_pd *pd,
		     काष्ठा mlx5_ib_qp *qp,
		     काष्ठा mlx5_create_qp_params *params)
अणु
	पूर्णांक err;

	अगर (params->is_rss_raw) अणु
		err = create_rss_raw_qp_tir(dev, pd, qp, params);
		जाओ out;
	पूर्ण

	चयन (qp->type) अणु
	हाल MLX5_IB_QPT_DCT:
		err = create_dct(dev, pd, qp, params);
		अवरोध;
	हाल IB_QPT_XRC_TGT:
		err = create_xrc_tgt_qp(dev, qp, params);
		अवरोध;
	हाल IB_QPT_GSI:
		err = mlx5_ib_create_gsi(pd, qp, params->attr);
		अवरोध;
	शेष:
		अगर (params->udata)
			err = create_user_qp(dev, pd, qp, params);
		अन्यथा
			err = create_kernel_qp(dev, pd, qp, params);
	पूर्ण

out:
	अगर (err) अणु
		mlx5_ib_err(dev, "Create QP type %d failed\n", qp->type);
		वापस err;
	पूर्ण

	अगर (is_qp0(qp->type))
		qp->ibqp.qp_num = 0;
	अन्यथा अगर (is_qp1(qp->type))
		qp->ibqp.qp_num = 1;
	अन्यथा
		qp->ibqp.qp_num = qp->trans_qp.base.mqp.qpn;

	mlx5_ib_dbg(dev,
		"QP type %d, ib qpn 0x%X, mlx qpn 0x%x, rcqn 0x%x, scqn 0x%x, ece 0x%x\n",
		qp->type, qp->ibqp.qp_num, qp->trans_qp.base.mqp.qpn,
		params->attr->recv_cq ? to_mcq(params->attr->recv_cq)->mcq.cqn :
					-1,
		params->attr->send_cq ? to_mcq(params->attr->send_cq)->mcq.cqn :
					-1,
		params->resp.ece_options);

	वापस 0;
पूर्ण

अटल पूर्णांक check_qp_attr(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			 काष्ठा ib_qp_init_attr *attr)
अणु
	पूर्णांक ret = 0;

	चयन (qp->type) अणु
	हाल MLX5_IB_QPT_DCT:
		ret = (!attr->srq || !attr->recv_cq) ? -EINVAL : 0;
		अवरोध;
	हाल MLX5_IB_QPT_DCI:
		ret = (attr->cap.max_recv_wr || attr->cap.max_recv_sge) ?
			      -EINVAL :
			      0;
		अवरोध;
	हाल IB_QPT_RAW_PACKET:
		ret = (attr->rwq_ind_tbl && attr->send_cq) ? -EINVAL : 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret)
		mlx5_ib_dbg(dev, "QP type %d has wrong attributes\n", qp->type);

	वापस ret;
पूर्ण

अटल पूर्णांक get_qp_uidx(काष्ठा mlx5_ib_qp *qp,
		       काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा mlx5_ib_create_qp *ucmd = params->ucmd;
	काष्ठा ib_udata *udata = params->udata;
	काष्ठा mlx5_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	अगर (params->is_rss_raw)
		वापस 0;

	वापस get_qp_user_index(ucontext, ucmd, माप(*ucmd), &params->uidx);
पूर्ण

अटल पूर्णांक mlx5_ib_destroy_dct(काष्ठा mlx5_ib_qp *mqp)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(mqp->ibqp.device);

	अगर (mqp->state == IB_QPS_RTR) अणु
		पूर्णांक err;

		err = mlx5_core_destroy_dct(dev, &mqp->dct.mdct);
		अगर (err) अणु
			mlx5_ib_warn(dev, "failed to destroy DCT %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	kमुक्त(mqp->dct.in);
	kमुक्त(mqp);
	वापस 0;
पूर्ण

अटल पूर्णांक check_ucmd_data(काष्ठा mlx5_ib_dev *dev,
			   काष्ठा mlx5_create_qp_params *params)
अणु
	काष्ठा ib_udata *udata = params->udata;
	माप_प्रकार size, last;
	पूर्णांक ret;

	अगर (params->is_rss_raw)
		/*
		 * These QPs करोn't have "reserved" field in their
		 * create_qp input काष्ठा, so their data is always valid.
		 */
		last = माप(काष्ठा mlx5_ib_create_qp_rss);
	अन्यथा
		last = दुरत्व(काष्ठा mlx5_ib_create_qp, reserved);

	अगर (udata->inlen <= last)
		वापस 0;

	/*
	 * User provides dअगरferent create_qp काष्ठाures based on the
	 * flow and we need to know अगर he cleared memory after our
	 * काष्ठा create_qp ends.
	 */
	size = udata->inlen - last;
	ret = ib_is_udata_cleared(params->udata, last, size);
	अगर (!ret)
		mlx5_ib_dbg(
			dev,
			"udata is not cleared, inlen = %zu, ucmd = %zu, last = %zu, size = %zu\n",
			udata->inlen, params->ucmd_size, last, size);
	वापस ret ? 0 : -EINVAL;
पूर्ण

काष्ठा ib_qp *mlx5_ib_create_qp(काष्ठा ib_pd *pd, काष्ठा ib_qp_init_attr *attr,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_create_qp_params params = अणुपूर्ण;
	काष्ठा mlx5_ib_dev *dev;
	काष्ठा mlx5_ib_qp *qp;
	क्रमागत ib_qp_type type;
	पूर्णांक err;

	dev = pd ? to_mdev(pd->device) :
		   to_mdev(to_mxrcd(attr->xrcd)->ibxrcd.device);

	err = check_qp_type(dev, attr, &type);
	अगर (err)
		वापस ERR_PTR(err);

	err = check_valid_flow(dev, pd, attr, udata);
	अगर (err)
		वापस ERR_PTR(err);

	params.udata = udata;
	params.uidx = MLX5_IB_DEFAULT_UIDX;
	params.attr = attr;
	params.is_rss_raw = !!attr->rwq_ind_tbl;

	अगर (udata) अणु
		err = process_udata_size(dev, &params);
		अगर (err)
			वापस ERR_PTR(err);

		err = check_ucmd_data(dev, &params);
		अगर (err)
			वापस ERR_PTR(err);

		params.ucmd = kzalloc(params.ucmd_size, GFP_KERNEL);
		अगर (!params.ucmd)
			वापस ERR_PTR(-ENOMEM);

		err = ib_copy_from_udata(params.ucmd, udata, params.inlen);
		अगर (err)
			जाओ मुक्त_ucmd;
	पूर्ण

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp) अणु
		err = -ENOMEM;
		जाओ मुक्त_ucmd;
	पूर्ण

	mutex_init(&qp->mutex);
	qp->type = type;
	अगर (udata) अणु
		err = process_venकरोr_flags(dev, qp, params.ucmd, attr);
		अगर (err)
			जाओ मुक्त_qp;

		err = get_qp_uidx(qp, &params);
		अगर (err)
			जाओ मुक्त_qp;
	पूर्ण
	err = process_create_flags(dev, qp, attr);
	अगर (err)
		जाओ मुक्त_qp;

	err = check_qp_attr(dev, qp, attr);
	अगर (err)
		जाओ मुक्त_qp;

	err = create_qp(dev, pd, qp, &params);
	अगर (err)
		जाओ मुक्त_qp;

	kमुक्त(params.ucmd);
	params.ucmd = शून्य;

	अगर (udata)
		/*
		 * It is safe to copy response क्रम all user create QP flows,
		 * including MLX5_IB_QPT_DCT, which करोesn't need it.
		 * In that हाल, resp will be filled with zeros.
		 */
		err = ib_copy_to_udata(udata, &params.resp, params.outlen);
	अगर (err)
		जाओ destroy_qp;

	वापस &qp->ibqp;

destroy_qp:
	चयन (qp->type) अणु
	हाल MLX5_IB_QPT_DCT:
		mlx5_ib_destroy_dct(qp);
		अवरोध;
	हाल IB_QPT_GSI:
		mlx5_ib_destroy_gsi(qp);
		अवरोध;
	शेष:
		/*
		 * These lines below are temp solution till QP allocation
		 * will be moved to be under IB/core responsiblity.
		 */
		qp->ibqp.send_cq = attr->send_cq;
		qp->ibqp.recv_cq = attr->recv_cq;
		qp->ibqp.pd = pd;
		destroy_qp_common(dev, qp, udata);
	पूर्ण

	qp = शून्य;
मुक्त_qp:
	kमुक्त(qp);
मुक्त_ucmd:
	kमुक्त(params.ucmd);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक mlx5_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);

	अगर (unlikely(qp->qp_type == IB_QPT_GSI))
		वापस mlx5_ib_destroy_gsi(mqp);

	अगर (mqp->type == MLX5_IB_QPT_DCT)
		वापस mlx5_ib_destroy_dct(mqp);

	destroy_qp_common(dev, mqp, udata);

	kमुक्त(mqp);

	वापस 0;
पूर्ण

अटल पूर्णांक set_qpc_atomic_flags(काष्ठा mlx5_ib_qp *qp,
				स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
				व्योम *qpc)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->ibqp.device);
	u8 dest_rd_atomic;
	u32 access_flags;

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		dest_rd_atomic = attr->max_dest_rd_atomic;
	अन्यथा
		dest_rd_atomic = qp->trans_qp.resp_depth;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		access_flags = attr->qp_access_flags;
	अन्यथा
		access_flags = qp->trans_qp.atomic_rd_en;

	अगर (!dest_rd_atomic)
		access_flags &= IB_ACCESS_REMOTE_WRITE;

	MLX5_SET(qpc, qpc, rre, !!(access_flags & IB_ACCESS_REMOTE_READ));

	अगर (access_flags & IB_ACCESS_REMOTE_ATOMIC) अणु
		पूर्णांक atomic_mode;

		atomic_mode = get_atomic_mode(dev, qp->ibqp.qp_type);
		अगर (atomic_mode < 0)
			वापस -EOPNOTSUPP;

		MLX5_SET(qpc, qpc, rae, 1);
		MLX5_SET(qpc, qpc, atomic_mode, atomic_mode);
	पूर्ण

	MLX5_SET(qpc, qpc, rwe, !!(access_flags & IB_ACCESS_REMOTE_WRITE));
	वापस 0;
पूर्ण

क्रमागत अणु
	MLX5_PATH_FLAG_FL	= 1 << 0,
	MLX5_PATH_FLAG_FREE_AR	= 1 << 1,
	MLX5_PATH_FLAG_COUNTER	= 1 << 2,
पूर्ण;

अटल पूर्णांक mlx5_to_ib_rate_map(u8 rate)
अणु
	अटल स्थिर पूर्णांक rates[] = अणु IB_RATE_PORT_CURRENT, IB_RATE_56_GBPS,
				     IB_RATE_25_GBPS,	   IB_RATE_100_GBPS,
				     IB_RATE_200_GBPS,	   IB_RATE_50_GBPS,
				     IB_RATE_400_GBPS पूर्ण;

	अगर (rate < ARRAY_SIZE(rates))
		वापस rates[rate];

	वापस rate - MLX5_STAT_RATE_OFFSET;
पूर्ण

अटल पूर्णांक ib_to_mlx5_rate_map(u8 rate)
अणु
	चयन (rate) अणु
	हाल IB_RATE_PORT_CURRENT:
		वापस 0;
	हाल IB_RATE_56_GBPS:
		वापस 1;
	हाल IB_RATE_25_GBPS:
		वापस 2;
	हाल IB_RATE_100_GBPS:
		वापस 3;
	हाल IB_RATE_200_GBPS:
		वापस 4;
	हाल IB_RATE_50_GBPS:
		वापस 5;
	हाल IB_RATE_400_GBPS:
		वापस 6;
	शेष:
		वापस rate + MLX5_STAT_RATE_OFFSET;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ib_rate_to_mlx5(काष्ठा mlx5_ib_dev *dev, u8 rate)
अणु
	u32 stat_rate_support;

	अगर (rate == IB_RATE_PORT_CURRENT)
		वापस 0;

	अगर (rate < IB_RATE_2_5_GBPS || rate > IB_RATE_600_GBPS)
		वापस -EINVAL;

	stat_rate_support = MLX5_CAP_GEN(dev->mdev, stat_rate_support);
	जबतक (rate != IB_RATE_PORT_CURRENT &&
	       !(1 << ib_to_mlx5_rate_map(rate) & stat_rate_support))
		--rate;

	वापस ib_to_mlx5_rate_map(rate);
पूर्ण

अटल पूर्णांक modअगरy_raw_packet_eth_prio(काष्ठा mlx5_core_dev *dev,
				      काष्ठा mlx5_ib_sq *sq, u8 sl,
				      काष्ठा ib_pd *pd)
अणु
	व्योम *in;
	व्योम *tisc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_tis_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_tis_in, in, biपंचांगask.prio, 1);
	MLX5_SET(modअगरy_tis_in, in, uid, to_mpd(pd)->uid);

	tisc = MLX5_ADDR_OF(modअगरy_tis_in, in, ctx);
	MLX5_SET(tisc, tisc, prio, ((sl & 0x7) << 1));

	err = mlx5_core_modअगरy_tis(dev, sq->tisn, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक modअगरy_raw_packet_tx_affinity(काष्ठा mlx5_core_dev *dev,
					 काष्ठा mlx5_ib_sq *sq, u8 tx_affinity,
					 काष्ठा ib_pd *pd)
अणु
	व्योम *in;
	व्योम *tisc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_tis_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_tis_in, in, biपंचांगask.lag_tx_port_affinity, 1);
	MLX5_SET(modअगरy_tis_in, in, uid, to_mpd(pd)->uid);

	tisc = MLX5_ADDR_OF(modअगरy_tis_in, in, ctx);
	MLX5_SET(tisc, tisc, lag_tx_port_affinity, tx_affinity);

	err = mlx5_core_modअगरy_tis(dev, sq->tisn, in);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल व्योम mlx5_set_path_udp_sport(व्योम *path, स्थिर काष्ठा rdma_ah_attr *ah,
				    u32 lqpn, u32 rqpn)

अणु
	u32 fl = ah->grh.flow_label;

	अगर (!fl)
		fl = rdma_calc_flow_label(lqpn, rqpn);

	MLX5_SET(ads, path, udp_sport, rdma_flow_label_to_udp_sport(fl));
पूर्ण

अटल पूर्णांक mlx5_set_path(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			 स्थिर काष्ठा rdma_ah_attr *ah, व्योम *path, u8 port,
			 पूर्णांक attr_mask, u32 path_flags,
			 स्थिर काष्ठा ib_qp_attr *attr, bool alt)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah);
	पूर्णांक err;
	क्रमागत ib_gid_type gid_type;
	u8 ah_flags = rdma_ah_get_ah_flags(ah);
	u8 sl = rdma_ah_get_sl(ah);

	अगर (attr_mask & IB_QP_PKEY_INDEX)
		MLX5_SET(ads, path, pkey_index,
			 alt ? attr->alt_pkey_index : attr->pkey_index);

	अगर (ah_flags & IB_AH_GRH) अणु
		स्थिर काष्ठा ib_port_immutable *immutable;

		immutable = ib_port_immutable_पढ़ो(&dev->ib_dev, port);
		अगर (grh->sgid_index >= immutable->gid_tbl_len) अणु
			pr_err("sgid_index (%u) too large. max is %d\n",
			       grh->sgid_index,
			       immutable->gid_tbl_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ah->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		अगर (!(ah_flags & IB_AH_GRH))
			वापस -EINVAL;

		ether_addr_copy(MLX5_ADDR_OF(ads, path, rmac_47_32),
				ah->roce.dmac);
		अगर ((qp->ibqp.qp_type == IB_QPT_RC ||
		     qp->ibqp.qp_type == IB_QPT_UC ||
		     qp->ibqp.qp_type == IB_QPT_XRC_INI ||
		     qp->ibqp.qp_type == IB_QPT_XRC_TGT) &&
		    (grh->sgid_attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) &&
		    (attr_mask & IB_QP_DEST_QPN))
			mlx5_set_path_udp_sport(path, ah,
						qp->ibqp.qp_num,
						attr->dest_qp_num);
		MLX5_SET(ads, path, eth_prio, sl & 0x7);
		gid_type = ah->grh.sgid_attr->gid_type;
		अगर (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP)
			MLX5_SET(ads, path, dscp, grh->traffic_class >> 2);
	पूर्ण अन्यथा अणु
		MLX5_SET(ads, path, fl, !!(path_flags & MLX5_PATH_FLAG_FL));
		MLX5_SET(ads, path, मुक्त_ar,
			 !!(path_flags & MLX5_PATH_FLAG_FREE_AR));
		MLX5_SET(ads, path, rlid, rdma_ah_get_dlid(ah));
		MLX5_SET(ads, path, mlid, rdma_ah_get_path_bits(ah));
		MLX5_SET(ads, path, grh, !!(ah_flags & IB_AH_GRH));
		MLX5_SET(ads, path, sl, sl);
	पूर्ण

	अगर (ah_flags & IB_AH_GRH) अणु
		MLX5_SET(ads, path, src_addr_index, grh->sgid_index);
		MLX5_SET(ads, path, hop_limit, grh->hop_limit);
		MLX5_SET(ads, path, tclass, grh->traffic_class);
		MLX5_SET(ads, path, flow_label, grh->flow_label);
		स_नकल(MLX5_ADDR_OF(ads, path, rgid_rip), grh->dgid.raw,
		       माप(grh->dgid.raw));
	पूर्ण

	err = ib_rate_to_mlx5(dev, rdma_ah_get_अटल_rate(ah));
	अगर (err < 0)
		वापस err;
	MLX5_SET(ads, path, stat_rate, err);
	MLX5_SET(ads, path, vhca_port_num, port);

	अगर (attr_mask & IB_QP_TIMEOUT)
		MLX5_SET(ads, path, ack_समयout,
			 alt ? attr->alt_समयout : attr->समयout);

	अगर ((qp->ibqp.qp_type == IB_QPT_RAW_PACKET) && qp->sq.wqe_cnt)
		वापस modअगरy_raw_packet_eth_prio(dev->mdev,
						  &qp->raw_packet_qp.sq,
						  sl & 0xf, qp->ibqp.pd);

	वापस 0;
पूर्ण

अटल क्रमागत mlx5_qp_optpar opt_mask[MLX5_QP_NUM_STATE][MLX5_QP_NUM_STATE][MLX5_QP_ST_MAX] = अणु
	[MLX5_QP_STATE_INIT] = अणु
		[MLX5_QP_STATE_INIT] = अणु
			[MLX5_QP_ST_RC] = MLX5_QP_OPTPAR_RRE		|
					  MLX5_QP_OPTPAR_RAE		|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_PRI_PORT	|
					  MLX5_QP_OPTPAR_LAG_TX_AFF,
			[MLX5_QP_ST_UC] = MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_PRI_PORT	|
					  MLX5_QP_OPTPAR_LAG_TX_AFF,
			[MLX5_QP_ST_UD] = MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_Q_KEY		|
					  MLX5_QP_OPTPAR_PRI_PORT,
			[MLX5_QP_ST_XRC] = MLX5_QP_OPTPAR_RRE		|
					  MLX5_QP_OPTPAR_RAE		|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_PRI_PORT	|
					  MLX5_QP_OPTPAR_LAG_TX_AFF,
		पूर्ण,
		[MLX5_QP_STATE_RTR] = अणु
			[MLX5_QP_ST_RC] = MLX5_QP_OPTPAR_ALT_ADDR_PATH  |
					  MLX5_QP_OPTPAR_RRE            |
					  MLX5_QP_OPTPAR_RAE            |
					  MLX5_QP_OPTPAR_RWE            |
					  MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_LAG_TX_AFF,
			[MLX5_QP_ST_UC] = MLX5_QP_OPTPAR_ALT_ADDR_PATH  |
					  MLX5_QP_OPTPAR_RWE            |
					  MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_LAG_TX_AFF,
			[MLX5_QP_ST_UD] = MLX5_QP_OPTPAR_PKEY_INDEX     |
					  MLX5_QP_OPTPAR_Q_KEY,
			[MLX5_QP_ST_MLX] = MLX5_QP_OPTPAR_PKEY_INDEX	|
					   MLX5_QP_OPTPAR_Q_KEY,
			[MLX5_QP_ST_XRC] = MLX5_QP_OPTPAR_ALT_ADDR_PATH |
					  MLX5_QP_OPTPAR_RRE            |
					  MLX5_QP_OPTPAR_RAE            |
					  MLX5_QP_OPTPAR_RWE            |
					  MLX5_QP_OPTPAR_PKEY_INDEX	|
					  MLX5_QP_OPTPAR_LAG_TX_AFF,
		पूर्ण,
	पूर्ण,
	[MLX5_QP_STATE_RTR] = अणु
		[MLX5_QP_STATE_RTS] = अणु
			[MLX5_QP_ST_RC] = MLX5_QP_OPTPAR_ALT_ADDR_PATH	|
					  MLX5_QP_OPTPAR_RRE		|
					  MLX5_QP_OPTPAR_RAE		|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PM_STATE	|
					  MLX5_QP_OPTPAR_RNR_TIMEOUT,
			[MLX5_QP_ST_UC] = MLX5_QP_OPTPAR_ALT_ADDR_PATH	|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PM_STATE,
			[MLX5_QP_ST_UD] = MLX5_QP_OPTPAR_Q_KEY,
			[MLX5_QP_ST_XRC] = MLX5_QP_OPTPAR_ALT_ADDR_PATH	|
					  MLX5_QP_OPTPAR_RRE		|
					  MLX5_QP_OPTPAR_RAE		|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PM_STATE	|
					  MLX5_QP_OPTPAR_RNR_TIMEOUT,
		पूर्ण,
	पूर्ण,
	[MLX5_QP_STATE_RTS] = अणु
		[MLX5_QP_STATE_RTS] = अणु
			[MLX5_QP_ST_RC] = MLX5_QP_OPTPAR_RRE		|
					  MLX5_QP_OPTPAR_RAE		|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_RNR_TIMEOUT	|
					  MLX5_QP_OPTPAR_PM_STATE	|
					  MLX5_QP_OPTPAR_ALT_ADDR_PATH,
			[MLX5_QP_ST_UC] = MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_PM_STATE	|
					  MLX5_QP_OPTPAR_ALT_ADDR_PATH,
			[MLX5_QP_ST_UD] = MLX5_QP_OPTPAR_Q_KEY		|
					  MLX5_QP_OPTPAR_SRQN		|
					  MLX5_QP_OPTPAR_CQN_RCV,
			[MLX5_QP_ST_XRC] = MLX5_QP_OPTPAR_RRE		|
					  MLX5_QP_OPTPAR_RAE		|
					  MLX5_QP_OPTPAR_RWE		|
					  MLX5_QP_OPTPAR_RNR_TIMEOUT	|
					  MLX5_QP_OPTPAR_PM_STATE	|
					  MLX5_QP_OPTPAR_ALT_ADDR_PATH,
		पूर्ण,
	पूर्ण,
	[MLX5_QP_STATE_SQER] = अणु
		[MLX5_QP_STATE_RTS] = अणु
			[MLX5_QP_ST_UD]	 = MLX5_QP_OPTPAR_Q_KEY,
			[MLX5_QP_ST_MLX] = MLX5_QP_OPTPAR_Q_KEY,
			[MLX5_QP_ST_UC]	 = MLX5_QP_OPTPAR_RWE,
			[MLX5_QP_ST_RC]	 = MLX5_QP_OPTPAR_RNR_TIMEOUT	|
					   MLX5_QP_OPTPAR_RWE		|
					   MLX5_QP_OPTPAR_RAE		|
					   MLX5_QP_OPTPAR_RRE,
			[MLX5_QP_ST_XRC]  = MLX5_QP_OPTPAR_RNR_TIMEOUT	|
					   MLX5_QP_OPTPAR_RWE		|
					   MLX5_QP_OPTPAR_RAE		|
					   MLX5_QP_OPTPAR_RRE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ib_nr_to_mlx5_nr(पूर्णांक ib_mask)
अणु
	चयन (ib_mask) अणु
	हाल IB_QP_STATE:
		वापस 0;
	हाल IB_QP_CUR_STATE:
		वापस 0;
	हाल IB_QP_EN_SQD_ASYNC_NOTIFY:
		वापस 0;
	हाल IB_QP_ACCESS_FLAGS:
		वापस MLX5_QP_OPTPAR_RWE | MLX5_QP_OPTPAR_RRE |
			MLX5_QP_OPTPAR_RAE;
	हाल IB_QP_PKEY_INDEX:
		वापस MLX5_QP_OPTPAR_PKEY_INDEX;
	हाल IB_QP_PORT:
		वापस MLX5_QP_OPTPAR_PRI_PORT;
	हाल IB_QP_QKEY:
		वापस MLX5_QP_OPTPAR_Q_KEY;
	हाल IB_QP_AV:
		वापस MLX5_QP_OPTPAR_PRIMARY_ADDR_PATH |
			MLX5_QP_OPTPAR_PRI_PORT;
	हाल IB_QP_PATH_MTU:
		वापस 0;
	हाल IB_QP_TIMEOUT:
		वापस MLX5_QP_OPTPAR_ACK_TIMEOUT;
	हाल IB_QP_RETRY_CNT:
		वापस MLX5_QP_OPTPAR_RETRY_COUNT;
	हाल IB_QP_RNR_RETRY:
		वापस MLX5_QP_OPTPAR_RNR_RETRY;
	हाल IB_QP_RQ_PSN:
		वापस 0;
	हाल IB_QP_MAX_QP_RD_ATOMIC:
		वापस MLX5_QP_OPTPAR_SRA_MAX;
	हाल IB_QP_ALT_PATH:
		वापस MLX5_QP_OPTPAR_ALT_ADDR_PATH;
	हाल IB_QP_MIN_RNR_TIMER:
		वापस MLX5_QP_OPTPAR_RNR_TIMEOUT;
	हाल IB_QP_SQ_PSN:
		वापस 0;
	हाल IB_QP_MAX_DEST_RD_ATOMIC:
		वापस MLX5_QP_OPTPAR_RRA_MAX | MLX5_QP_OPTPAR_RWE |
			MLX5_QP_OPTPAR_RRE | MLX5_QP_OPTPAR_RAE;
	हाल IB_QP_PATH_MIG_STATE:
		वापस MLX5_QP_OPTPAR_PM_STATE;
	हाल IB_QP_CAP:
		वापस 0;
	हाल IB_QP_DEST_QPN:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ib_mask_to_mlx5_opt(पूर्णांक ib_mask)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8 * माप(पूर्णांक); i++) अणु
		अगर ((1 << i) & ib_mask)
			result |= ib_nr_to_mlx5_nr(1 << i);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक modअगरy_raw_packet_qp_rq(
	काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_rq *rq, पूर्णांक new_state,
	स्थिर काष्ठा mlx5_modअगरy_raw_qp_param *raw_qp_param, काष्ठा ib_pd *pd)
अणु
	व्योम *in;
	व्योम *rqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_rq_in, in, rq_state, rq->state);
	MLX5_SET(modअगरy_rq_in, in, uid, to_mpd(pd)->uid);

	rqc = MLX5_ADDR_OF(modअगरy_rq_in, in, ctx);
	MLX5_SET(rqc, rqc, state, new_state);

	अगर (raw_qp_param->set_mask & MLX5_RAW_QP_MOD_SET_RQ_Q_CTR_ID) अणु
		अगर (MLX5_CAP_GEN(dev->mdev, modअगरy_rq_counter_set_id)) अणु
			MLX5_SET64(modअगरy_rq_in, in, modअगरy_biपंचांगask,
				   MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_RQ_COUNTER_SET_ID);
			MLX5_SET(rqc, rqc, counter_set_id, raw_qp_param->rq_q_ctr_id);
		पूर्ण अन्यथा
			dev_info_once(
				&dev->ib_dev.dev,
				"RAW PACKET QP counters are not supported on current FW\n");
	पूर्ण

	err = mlx5_core_modअगरy_rq(dev->mdev, rq->base.mqp.qpn, in);
	अगर (err)
		जाओ out;

	rq->state = new_state;

out:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक modअगरy_raw_packet_qp_sq(
	काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_ib_sq *sq, पूर्णांक new_state,
	स्थिर काष्ठा mlx5_modअगरy_raw_qp_param *raw_qp_param, काष्ठा ib_pd *pd)
अणु
	काष्ठा mlx5_ib_qp *ibqp = sq->base.container_mibqp;
	काष्ठा mlx5_rate_limit old_rl = ibqp->rl;
	काष्ठा mlx5_rate_limit new_rl = old_rl;
	bool new_rate_added = false;
	u16 rl_index = 0;
	व्योम *in;
	व्योम *sqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_sq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(modअगरy_sq_in, in, uid, to_mpd(pd)->uid);
	MLX5_SET(modअगरy_sq_in, in, sq_state, sq->state);

	sqc = MLX5_ADDR_OF(modअगरy_sq_in, in, ctx);
	MLX5_SET(sqc, sqc, state, new_state);

	अगर (raw_qp_param->set_mask & MLX5_RAW_QP_RATE_LIMIT) अणु
		अगर (new_state != MLX5_SQC_STATE_RDY)
			pr_warn("%s: Rate limit can only be changed when SQ is moving to RDY\n",
				__func__);
		अन्यथा
			new_rl = raw_qp_param->rl;
	पूर्ण

	अगर (!mlx5_rl_are_equal(&old_rl, &new_rl)) अणु
		अगर (new_rl.rate) अणु
			err = mlx5_rl_add_rate(dev, &rl_index, &new_rl);
			अगर (err) अणु
				pr_err("Failed configuring rate limit(err %d): \
				       rate %u, max_burst_sz %u, typical_pkt_sz %u\न",
				       err, new_rl.rate, new_rl.max_burst_sz,
				       new_rl.typical_pkt_sz);

				जाओ out;
			पूर्ण
			new_rate_added = true;
		पूर्ण

		MLX5_SET64(modअगरy_sq_in, in, modअगरy_biपंचांगask, 1);
		/* index 0 means no limit */
		MLX5_SET(sqc, sqc, packet_pacing_rate_limit_index, rl_index);
	पूर्ण

	err = mlx5_core_modअगरy_sq(dev, sq->base.mqp.qpn, in);
	अगर (err) अणु
		/* Remove new rate from table अगर failed */
		अगर (new_rate_added)
			mlx5_rl_हटाओ_rate(dev, &new_rl);
		जाओ out;
	पूर्ण

	/* Only हटाओ the old rate after new rate was set */
	अगर ((old_rl.rate && !mlx5_rl_are_equal(&old_rl, &new_rl)) ||
	    (new_state != MLX5_SQC_STATE_RDY)) अणु
		mlx5_rl_हटाओ_rate(dev, &old_rl);
		अगर (new_state != MLX5_SQC_STATE_RDY)
			स_रखो(&new_rl, 0, माप(new_rl));
	पूर्ण

	ibqp->rl = new_rl;
	sq->state = new_state;

out:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक modअगरy_raw_packet_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
				स्थिर काष्ठा mlx5_modअगरy_raw_qp_param *raw_qp_param,
				u8 tx_affinity)
अणु
	काष्ठा mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	काष्ठा mlx5_ib_rq *rq = &raw_packet_qp->rq;
	काष्ठा mlx5_ib_sq *sq = &raw_packet_qp->sq;
	पूर्णांक modअगरy_rq = !!qp->rq.wqe_cnt;
	पूर्णांक modअगरy_sq = !!qp->sq.wqe_cnt;
	पूर्णांक rq_state;
	पूर्णांक sq_state;
	पूर्णांक err;

	चयन (raw_qp_param->operation) अणु
	हाल MLX5_CMD_OP_RST2INIT_QP:
		rq_state = MLX5_RQC_STATE_RDY;
		sq_state = MLX5_SQC_STATE_RST;
		अवरोध;
	हाल MLX5_CMD_OP_2ERR_QP:
		rq_state = MLX5_RQC_STATE_ERR;
		sq_state = MLX5_SQC_STATE_ERR;
		अवरोध;
	हाल MLX5_CMD_OP_2RST_QP:
		rq_state = MLX5_RQC_STATE_RST;
		sq_state = MLX5_SQC_STATE_RST;
		अवरोध;
	हाल MLX5_CMD_OP_RTR2RTS_QP:
	हाल MLX5_CMD_OP_RTS2RTS_QP:
		अगर (raw_qp_param->set_mask & ~MLX5_RAW_QP_RATE_LIMIT)
			वापस -EINVAL;

		modअगरy_rq = 0;
		sq_state = MLX5_SQC_STATE_RDY;
		अवरोध;
	हाल MLX5_CMD_OP_INIT2INIT_QP:
	हाल MLX5_CMD_OP_INIT2RTR_QP:
		अगर (raw_qp_param->set_mask)
			वापस -EINVAL;
		अन्यथा
			वापस 0;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (modअगरy_rq) अणु
		err =  modअगरy_raw_packet_qp_rq(dev, rq, rq_state, raw_qp_param,
					       qp->ibqp.pd);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (modअगरy_sq) अणु
		काष्ठा mlx5_flow_handle *flow_rule;

		अगर (tx_affinity) अणु
			err = modअगरy_raw_packet_tx_affinity(dev->mdev, sq,
							    tx_affinity,
							    qp->ibqp.pd);
			अगर (err)
				वापस err;
		पूर्ण

		flow_rule = create_flow_rule_vport_sq(dev, sq,
						      raw_qp_param->port);
		अगर (IS_ERR(flow_rule))
			वापस PTR_ERR(flow_rule);

		err = modअगरy_raw_packet_qp_sq(dev->mdev, sq, sq_state,
					      raw_qp_param, qp->ibqp.pd);
		अगर (err) अणु
			अगर (flow_rule)
				mlx5_del_flow_rules(flow_rule);
			वापस err;
		पूर्ण

		अगर (flow_rule) अणु
			destroy_flow_rule_vport_sq(sq);
			sq->flow_rule = flow_rule;
		पूर्ण

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक get_tx_affinity_rr(काष्ठा mlx5_ib_dev *dev,
				       काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	u8 port_num = mlx5_core_native_port_num(dev->mdev) - 1;
	atomic_t *tx_port_affinity;

	अगर (ucontext)
		tx_port_affinity = &ucontext->tx_port_affinity;
	अन्यथा
		tx_port_affinity = &dev->port[port_num].roce.tx_port_affinity;

	वापस (अचिन्हित पूर्णांक)atomic_add_वापस(1, tx_port_affinity) %
		MLX5_MAX_PORTS + 1;
पूर्ण

अटल bool qp_supports_affinity(काष्ठा mlx5_ib_qp *qp)
अणु
	अगर ((qp->type == IB_QPT_RC) || (qp->type == IB_QPT_UD) ||
	    (qp->type == IB_QPT_UC) || (qp->type == IB_QPT_RAW_PACKET) ||
	    (qp->type == IB_QPT_XRC_INI) || (qp->type == IB_QPT_XRC_TGT) ||
	    (qp->type == MLX5_IB_QPT_DCI))
		वापस true;
	वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक get_tx_affinity(काष्ठा ib_qp *qp,
				    स्थिर काष्ठा ib_qp_attr *attr,
				    पूर्णांक attr_mask, u8 init,
				    काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_qp_base *qp_base;
	अचिन्हित पूर्णांक tx_affinity;

	अगर (!(mlx5_ib_lag_should_assign_affinity(dev) &&
	      qp_supports_affinity(mqp)))
		वापस 0;

	अगर (mqp->flags & MLX5_IB_QP_CREATE_SQPN_QP1)
		tx_affinity = mqp->gsi_lag_port;
	अन्यथा अगर (init)
		tx_affinity = get_tx_affinity_rr(dev, udata);
	अन्यथा अगर ((attr_mask & IB_QP_AV) && attr->xmit_slave)
		tx_affinity =
			mlx5_lag_get_slave_port(dev->mdev, attr->xmit_slave);
	अन्यथा
		वापस 0;

	qp_base = &mqp->trans_qp.base;
	अगर (ucontext)
		mlx5_ib_dbg(dev, "Set tx affinity 0x%x to qpn 0x%x ucontext %p\n",
			    tx_affinity, qp_base->mqp.qpn, ucontext);
	अन्यथा
		mlx5_ib_dbg(dev, "Set tx affinity 0x%x to qpn 0x%x\n",
			    tx_affinity, qp_base->mqp.qpn);
	वापस tx_affinity;
पूर्ण

अटल पूर्णांक __mlx5_ib_qp_set_counter(काष्ठा ib_qp *qp,
				    काष्ठा rdma_counter *counter)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	u32 in[MLX5_ST_SZ_DW(rts2rts_qp_in)] = अणुपूर्ण;
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_qp_base *base;
	u32 set_id;
	u32 *qpc;

	अगर (counter)
		set_id = counter->id;
	अन्यथा
		set_id = mlx5_ib_get_counters_id(dev, mqp->port - 1);

	base = &mqp->trans_qp.base;
	MLX5_SET(rts2rts_qp_in, in, opcode, MLX5_CMD_OP_RTS2RTS_QP);
	MLX5_SET(rts2rts_qp_in, in, qpn, base->mqp.qpn);
	MLX5_SET(rts2rts_qp_in, in, uid, base->mqp.uid);
	MLX5_SET(rts2rts_qp_in, in, opt_param_mask,
		 MLX5_QP_OPTPAR_COUNTER_SET_ID);

	qpc = MLX5_ADDR_OF(rts2rts_qp_in, in, qpc);
	MLX5_SET(qpc, qpc, counter_set_id, set_id);
	वापस mlx5_cmd_exec_in(dev->mdev, rts2rts_qp, in);
पूर्ण

अटल पूर्णांक __mlx5_ib_modअगरy_qp(काष्ठा ib_qp *ibqp,
			       स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
			       क्रमागत ib_qp_state cur_state,
			       क्रमागत ib_qp_state new_state,
			       स्थिर काष्ठा mlx5_ib_modअगरy_qp *ucmd,
			       काष्ठा mlx5_ib_modअगरy_qp_resp *resp,
			       काष्ठा ib_udata *udata)
अणु
	अटल स्थिर u16 optab[MLX5_QP_NUM_STATE][MLX5_QP_NUM_STATE] = अणु
		[MLX5_QP_STATE_RST] = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
			[MLX5_QP_STATE_INIT]	= MLX5_CMD_OP_RST2INIT_QP,
		पूर्ण,
		[MLX5_QP_STATE_INIT]  = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
			[MLX5_QP_STATE_INIT]	= MLX5_CMD_OP_INIT2INIT_QP,
			[MLX5_QP_STATE_RTR]	= MLX5_CMD_OP_INIT2RTR_QP,
		पूर्ण,
		[MLX5_QP_STATE_RTR]   = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
			[MLX5_QP_STATE_RTS]	= MLX5_CMD_OP_RTR2RTS_QP,
		पूर्ण,
		[MLX5_QP_STATE_RTS]   = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
			[MLX5_QP_STATE_RTS]	= MLX5_CMD_OP_RTS2RTS_QP,
		पूर्ण,
		[MLX5_QP_STATE_SQD] = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
		पूर्ण,
		[MLX5_QP_STATE_SQER] = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
			[MLX5_QP_STATE_RTS]	= MLX5_CMD_OP_SQERR2RTS_QP,
		पूर्ण,
		[MLX5_QP_STATE_ERR] = अणु
			[MLX5_QP_STATE_RST]	= MLX5_CMD_OP_2RST_QP,
			[MLX5_QP_STATE_ERR]	= MLX5_CMD_OP_2ERR_QP,
		पूर्ण
	पूर्ण;

	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx5_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx5_ib_qp_base *base = &qp->trans_qp.base;
	काष्ठा mlx5_ib_cq *send_cq, *recv_cq;
	काष्ठा mlx5_ib_pd *pd;
	क्रमागत mlx5_qp_state mlx5_cur, mlx5_new;
	व्योम *qpc, *pri_path, *alt_path;
	क्रमागत mlx5_qp_optpar optpar = 0;
	u32 set_id = 0;
	पूर्णांक mlx5_st;
	पूर्णांक err;
	u16 op;
	u8 tx_affinity = 0;

	mlx5_st = to_mlx5_st(qp->type);
	अगर (mlx5_st < 0)
		वापस -EINVAL;

	qpc = kzalloc(MLX5_ST_SZ_BYTES(qpc), GFP_KERNEL);
	अगर (!qpc)
		वापस -ENOMEM;

	pd = to_mpd(qp->ibqp.pd);
	MLX5_SET(qpc, qpc, st, mlx5_st);

	अगर (!(attr_mask & IB_QP_PATH_MIG_STATE)) अणु
		MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	पूर्ण अन्यथा अणु
		चयन (attr->path_mig_state) अणु
		हाल IB_MIG_MIGRATED:
			MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
			अवरोध;
		हाल IB_MIG_REARM:
			MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_REARM);
			अवरोध;
		हाल IB_MIG_ARMED:
			MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_ARMED);
			अवरोध;
		पूर्ण
	पूर्ण

	tx_affinity = get_tx_affinity(ibqp, attr, attr_mask,
				      cur_state == IB_QPS_RESET &&
				      new_state == IB_QPS_INIT, udata);

	MLX5_SET(qpc, qpc, lag_tx_port_affinity, tx_affinity);
	अगर (tx_affinity && new_state == IB_QPS_RTR &&
	    MLX5_CAP_GEN(dev->mdev, init2_lag_tx_port_affinity))
		optpar |= MLX5_QP_OPTPAR_LAG_TX_AFF;

	अगर (is_sqp(ibqp->qp_type)) अणु
		MLX5_SET(qpc, qpc, mtu, IB_MTU_256);
		MLX5_SET(qpc, qpc, log_msg_max, 8);
	पूर्ण अन्यथा अगर ((ibqp->qp_type == IB_QPT_UD &&
		    !(qp->flags & IB_QP_CREATE_SOURCE_QPN)) ||
		   ibqp->qp_type == MLX5_IB_QPT_REG_UMR) अणु
		MLX5_SET(qpc, qpc, mtu, IB_MTU_4096);
		MLX5_SET(qpc, qpc, log_msg_max, 12);
	पूर्ण अन्यथा अगर (attr_mask & IB_QP_PATH_MTU) अणु
		अगर (attr->path_mtu < IB_MTU_256 ||
		    attr->path_mtu > IB_MTU_4096) अणु
			mlx5_ib_warn(dev, "invalid mtu %d\n", attr->path_mtu);
			err = -EINVAL;
			जाओ out;
		पूर्ण
		MLX5_SET(qpc, qpc, mtu, attr->path_mtu);
		MLX5_SET(qpc, qpc, log_msg_max,
			 MLX5_CAP_GEN(dev->mdev, log_max_msg));
	पूर्ण

	अगर (attr_mask & IB_QP_DEST_QPN)
		MLX5_SET(qpc, qpc, remote_qpn, attr->dest_qp_num);

	pri_path = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
	alt_path = MLX5_ADDR_OF(qpc, qpc, secondary_address_path);

	अगर (attr_mask & IB_QP_PKEY_INDEX)
		MLX5_SET(ads, pri_path, pkey_index, attr->pkey_index);

	/* toकरो implement counter_index functionality */

	अगर (is_sqp(ibqp->qp_type))
		MLX5_SET(ads, pri_path, vhca_port_num, qp->port);

	अगर (attr_mask & IB_QP_PORT)
		MLX5_SET(ads, pri_path, vhca_port_num, attr->port_num);

	अगर (attr_mask & IB_QP_AV) अणु
		err = mlx5_set_path(dev, qp, &attr->ah_attr, pri_path,
				    attr_mask & IB_QP_PORT ? attr->port_num :
							     qp->port,
				    attr_mask, 0, attr, false);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_TIMEOUT)
		MLX5_SET(ads, pri_path, ack_समयout, attr->समयout);

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		err = mlx5_set_path(dev, qp, &attr->alt_ah_attr, alt_path,
				    attr->alt_port_num,
				    attr_mask | IB_QP_PKEY_INDEX |
					    IB_QP_TIMEOUT,
				    0, attr, true);
		अगर (err)
			जाओ out;
	पूर्ण

	get_cqs(qp->ibqp.qp_type, qp->ibqp.send_cq, qp->ibqp.recv_cq,
		&send_cq, &recv_cq);

	MLX5_SET(qpc, qpc, pd, pd ? pd->pdn : to_mpd(dev->devr.p0)->pdn);
	अगर (send_cq)
		MLX5_SET(qpc, qpc, cqn_snd, send_cq->mcq.cqn);
	अगर (recv_cq)
		MLX5_SET(qpc, qpc, cqn_rcv, recv_cq->mcq.cqn);

	MLX5_SET(qpc, qpc, log_ack_req_freq, MLX5_IB_ACK_REQ_FREQ);

	अगर (attr_mask & IB_QP_RNR_RETRY)
		MLX5_SET(qpc, qpc, rnr_retry, attr->rnr_retry);

	अगर (attr_mask & IB_QP_RETRY_CNT)
		MLX5_SET(qpc, qpc, retry_count, attr->retry_cnt);

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC && attr->max_rd_atomic)
		MLX5_SET(qpc, qpc, log_sra_max, ilog2(attr->max_rd_atomic));

	अगर (attr_mask & IB_QP_SQ_PSN)
		MLX5_SET(qpc, qpc, next_send_psn, attr->sq_psn);

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC && attr->max_dest_rd_atomic)
		MLX5_SET(qpc, qpc, log_rra_max,
			 ilog2(attr->max_dest_rd_atomic));

	अगर (attr_mask & (IB_QP_ACCESS_FLAGS | IB_QP_MAX_DEST_RD_ATOMIC)) अणु
		err = set_qpc_atomic_flags(qp, attr, attr_mask, qpc);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER)
		MLX5_SET(qpc, qpc, min_rnr_nak, attr->min_rnr_समयr);

	अगर (attr_mask & IB_QP_RQ_PSN)
		MLX5_SET(qpc, qpc, next_rcv_psn, attr->rq_psn);

	अगर (attr_mask & IB_QP_QKEY)
		MLX5_SET(qpc, qpc, q_key, attr->qkey);

	अगर (qp->rq.wqe_cnt && cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT)
		MLX5_SET64(qpc, qpc, dbr_addr, qp->db.dma);

	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		u8 port_num = (attr_mask & IB_QP_PORT ? attr->port_num :
			       qp->port) - 1;

		/* Underlay port should be used - index 0 function per port */
		अगर (qp->flags & IB_QP_CREATE_SOURCE_QPN)
			port_num = 0;

		अगर (ibqp->counter)
			set_id = ibqp->counter->id;
		अन्यथा
			set_id = mlx5_ib_get_counters_id(dev, port_num);
		MLX5_SET(qpc, qpc, counter_set_id, set_id);
	पूर्ण

	अगर (!ibqp->uobject && cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT)
		MLX5_SET(qpc, qpc, rlky, 1);

	अगर (qp->flags & MLX5_IB_QP_CREATE_SQPN_QP1)
		MLX5_SET(qpc, qpc, deth_sqpn, 1);

	mlx5_cur = to_mlx5_state(cur_state);
	mlx5_new = to_mlx5_state(new_state);

	अगर (mlx5_cur >= MLX5_QP_NUM_STATE || mlx5_new >= MLX5_QP_NUM_STATE ||
	    !optab[mlx5_cur][mlx5_new]) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	op = optab[mlx5_cur][mlx5_new];
	optpar |= ib_mask_to_mlx5_opt(attr_mask);
	optpar &= opt_mask[mlx5_cur][mlx5_new][mlx5_st];

	अगर (qp->ibqp.qp_type == IB_QPT_RAW_PACKET ||
	    qp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		काष्ठा mlx5_modअगरy_raw_qp_param raw_qp_param = अणुपूर्ण;

		raw_qp_param.operation = op;
		अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
			raw_qp_param.rq_q_ctr_id = set_id;
			raw_qp_param.set_mask |= MLX5_RAW_QP_MOD_SET_RQ_Q_CTR_ID;
		पूर्ण

		अगर (attr_mask & IB_QP_PORT)
			raw_qp_param.port = attr->port_num;

		अगर (attr_mask & IB_QP_RATE_LIMIT) अणु
			raw_qp_param.rl.rate = attr->rate_limit;

			अगर (ucmd->burst_info.max_burst_sz) अणु
				अगर (attr->rate_limit &&
				    MLX5_CAP_QOS(dev->mdev, packet_pacing_burst_bound)) अणु
					raw_qp_param.rl.max_burst_sz =
						ucmd->burst_info.max_burst_sz;
				पूर्ण अन्यथा अणु
					err = -EINVAL;
					जाओ out;
				पूर्ण
			पूर्ण

			अगर (ucmd->burst_info.typical_pkt_sz) अणु
				अगर (attr->rate_limit &&
				    MLX5_CAP_QOS(dev->mdev, packet_pacing_typical_size)) अणु
					raw_qp_param.rl.typical_pkt_sz =
						ucmd->burst_info.typical_pkt_sz;
				पूर्ण अन्यथा अणु
					err = -EINVAL;
					जाओ out;
				पूर्ण
			पूर्ण

			raw_qp_param.set_mask |= MLX5_RAW_QP_RATE_LIMIT;
		पूर्ण

		err = modअगरy_raw_packet_qp(dev, qp, &raw_qp_param, tx_affinity);
	पूर्ण अन्यथा अणु
		अगर (udata) अणु
			/* For the kernel flows, the resp will stay zero */
			resp->ece_options =
				MLX5_CAP_GEN(dev->mdev, ece_support) ?
					ucmd->ece_options : 0;
			resp->response_length = माप(*resp);
		पूर्ण
		err = mlx5_core_qp_modअगरy(dev, op, optpar, qpc, &base->mqp,
					  &resp->ece_options);
	पूर्ण

	अगर (err)
		जाओ out;

	qp->state = new_state;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		qp->trans_qp.atomic_rd_en = attr->qp_access_flags;
	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		qp->trans_qp.resp_depth = attr->max_dest_rd_atomic;
	अगर (attr_mask & IB_QP_PORT)
		qp->port = attr->port_num;
	अगर (attr_mask & IB_QP_ALT_PATH)
		qp->trans_qp.alt_port = attr->alt_port_num;

	/*
	 * If we moved a kernel QP to RESET, clean up all old CQ
	 * entries and reinitialize the QP.
	 */
	अगर (new_state == IB_QPS_RESET &&
	    !ibqp->uobject && ibqp->qp_type != IB_QPT_XRC_TGT) अणु
		mlx5_ib_cq_clean(recv_cq, base->mqp.qpn,
				 ibqp->srq ? to_msrq(ibqp->srq) : शून्य);
		अगर (send_cq != recv_cq)
			mlx5_ib_cq_clean(send_cq, base->mqp.qpn, शून्य);

		qp->rq.head = 0;
		qp->rq.tail = 0;
		qp->sq.head = 0;
		qp->sq.tail = 0;
		qp->sq.cur_post = 0;
		अगर (qp->sq.wqe_cnt)
			qp->sq.cur_edge = get_sq_edge(&qp->sq, 0);
		qp->sq.last_poll = 0;
		qp->db.db[MLX5_RCV_DBR] = 0;
		qp->db.db[MLX5_SND_DBR] = 0;
	पूर्ण

	अगर ((new_state == IB_QPS_RTS) && qp->counter_pending) अणु
		err = __mlx5_ib_qp_set_counter(ibqp, ibqp->counter);
		अगर (!err)
			qp->counter_pending = 0;
	पूर्ण

out:
	kमुक्त(qpc);
	वापस err;
पूर्ण

अटल अंतरभूत bool is_valid_mask(पूर्णांक mask, पूर्णांक req, पूर्णांक opt)
अणु
	अगर ((mask & req) != req)
		वापस false;

	अगर (mask & ~(req | opt))
		वापस false;

	वापस true;
पूर्ण

/* check valid transition क्रम driver QP types
 * क्रम now the only QP type that this function supports is DCI
 */
अटल bool modअगरy_dci_qp_is_ok(क्रमागत ib_qp_state cur_state, क्रमागत ib_qp_state new_state,
				क्रमागत ib_qp_attr_mask attr_mask)
अणु
	पूर्णांक req = IB_QP_STATE;
	पूर्णांक opt = 0;

	अगर (new_state == IB_QPS_RESET) अणु
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		req |= IB_QP_PKEY_INDEX | IB_QP_PORT;
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_INIT) अणु
		opt = IB_QP_PKEY_INDEX | IB_QP_PORT;
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) अणु
		req |= IB_QP_PATH_MTU;
		opt = IB_QP_PKEY_INDEX | IB_QP_AV;
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_RTR && new_state == IB_QPS_RTS) अणु
		req |= IB_QP_TIMEOUT | IB_QP_RETRY_CNT | IB_QP_RNR_RETRY |
		       IB_QP_MAX_QP_RD_ATOMIC | IB_QP_SQ_PSN;
		opt = IB_QP_MIN_RNR_TIMER;
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_RTS && new_state == IB_QPS_RTS) अणु
		opt = IB_QP_MIN_RNR_TIMER;
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण अन्यथा अगर (cur_state != IB_QPS_RESET && new_state == IB_QPS_ERR) अणु
		वापस is_valid_mask(attr_mask, req, opt);
	पूर्ण
	वापस false;
पूर्ण

/* mlx5_ib_modअगरy_dct: modअगरy a DCT QP
 * valid transitions are:
 * RESET to INIT: must set access_flags, pkey_index and port
 * INIT  to RTR : must set min_rnr_समयr, tclass, flow_label,
 *			   mtu, gid_index and hop_limit
 * Other transitions and attributes are illegal
 */
अटल पूर्णांक mlx5_ib_modअगरy_dct(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
			      पूर्णांक attr_mask, काष्ठा mlx5_ib_modअगरy_qp *ucmd,
			      काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	क्रमागत ib_qp_state cur_state, new_state;
	पूर्णांक required = IB_QP_STATE;
	व्योम *dctc;
	पूर्णांक err;

	अगर (!(attr_mask & IB_QP_STATE))
		वापस -EINVAL;

	cur_state = qp->state;
	new_state = attr->qp_state;

	dctc = MLX5_ADDR_OF(create_dct_in, qp->dct.in, dct_context_entry);
	अगर (MLX5_CAP_GEN(dev->mdev, ece_support) && ucmd->ece_options)
		/*
		 * DCT करोesn't initialize QP till modअगरy command is executed,
		 * so we need to overग_लिखो previously set ECE field अगर user
		 * provided any value except zero, which means not set/not
		 * valid.
		 */
		MLX5_SET(dctc, dctc, ece, ucmd->ece_options);

	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		u16 set_id;

		required |= IB_QP_ACCESS_FLAGS | IB_QP_PKEY_INDEX | IB_QP_PORT;
		अगर (!is_valid_mask(attr_mask, required, 0))
			वापस -EINVAL;

		अगर (attr->port_num == 0 ||
		    attr->port_num > MLX5_CAP_GEN(dev->mdev, num_ports)) अणु
			mlx5_ib_dbg(dev, "invalid port number %d. number of ports is %d\n",
				    attr->port_num, dev->num_ports);
			वापस -EINVAL;
		पूर्ण
		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_READ)
			MLX5_SET(dctc, dctc, rre, 1);
		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_WRITE)
			MLX5_SET(dctc, dctc, rwe, 1);
		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC) अणु
			पूर्णांक atomic_mode;

			atomic_mode = get_atomic_mode(dev, MLX5_IB_QPT_DCT);
			अगर (atomic_mode < 0)
				वापस -EOPNOTSUPP;

			MLX5_SET(dctc, dctc, atomic_mode, atomic_mode);
			MLX5_SET(dctc, dctc, rae, 1);
		पूर्ण
		MLX5_SET(dctc, dctc, pkey_index, attr->pkey_index);
		अगर (mlx5_lag_is_active(dev->mdev))
			MLX5_SET(dctc, dctc, port,
				 get_tx_affinity_rr(dev, udata));
		अन्यथा
			MLX5_SET(dctc, dctc, port, attr->port_num);

		set_id = mlx5_ib_get_counters_id(dev, attr->port_num - 1);
		MLX5_SET(dctc, dctc, counter_set_id, set_id);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) अणु
		काष्ठा mlx5_ib_modअगरy_qp_resp resp = अणुपूर्ण;
		u32 out[MLX5_ST_SZ_DW(create_dct_out)] = अणुपूर्ण;
		u32 min_resp_len = दुरत्वend(typeof(resp), dctn);

		अगर (udata->outlen < min_resp_len)
			वापस -EINVAL;
		/*
		 * If we करोn't have enough space क्रम the ECE options,
		 * simply indicate it with resp.response_length.
		 */
		resp.response_length = (udata->outlen < माप(resp)) ?
					       min_resp_len :
					       माप(resp);

		required |= IB_QP_MIN_RNR_TIMER | IB_QP_AV | IB_QP_PATH_MTU;
		अगर (!is_valid_mask(attr_mask, required, 0))
			वापस -EINVAL;
		MLX5_SET(dctc, dctc, min_rnr_nak, attr->min_rnr_समयr);
		MLX5_SET(dctc, dctc, tclass, attr->ah_attr.grh.traffic_class);
		MLX5_SET(dctc, dctc, flow_label, attr->ah_attr.grh.flow_label);
		MLX5_SET(dctc, dctc, mtu, attr->path_mtu);
		MLX5_SET(dctc, dctc, my_addr_index, attr->ah_attr.grh.sgid_index);
		MLX5_SET(dctc, dctc, hop_limit, attr->ah_attr.grh.hop_limit);

		err = mlx5_core_create_dct(dev, &qp->dct.mdct, qp->dct.in,
					   MLX5_ST_SZ_BYTES(create_dct_in), out,
					   माप(out));
		अगर (err)
			वापस err;
		resp.dctn = qp->dct.mdct.mqp.qpn;
		अगर (MLX5_CAP_GEN(dev->mdev, ece_support))
			resp.ece_options = MLX5_GET(create_dct_out, out, ece);
		err = ib_copy_to_udata(udata, &resp, resp.response_length);
		अगर (err) अणु
			mlx5_core_destroy_dct(dev, &qp->dct.mdct);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		mlx5_ib_warn(dev, "Modify DCT: Invalid transition from %d to %d\n", cur_state, new_state);
		वापस -EINVAL;
	पूर्ण

	qp->state = new_state;
	वापस 0;
पूर्ण

अटल bool mlx5_ib_modअगरy_qp_allowed(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा mlx5_ib_qp *qp,
				      क्रमागत ib_qp_type qp_type)
अणु
	अगर (dev->profile != &raw_eth_profile)
		वापस true;

	अगर (qp_type == IB_QPT_RAW_PACKET || qp_type == MLX5_IB_QPT_REG_UMR)
		वापस true;

	/* Internal QP used क्रम wc testing, with NOPs in wq */
	अगर (qp->flags & MLX5_IB_QP_CREATE_WC_TEST)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक mlx5_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx5_ib_modअगरy_qp_resp resp = अणुपूर्ण;
	काष्ठा mlx5_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx5_ib_modअगरy_qp ucmd = अणुपूर्ण;
	क्रमागत ib_qp_type qp_type;
	क्रमागत ib_qp_state cur_state, new_state;
	पूर्णांक err = -EINVAL;

	अगर (!mlx5_ib_modअगरy_qp_allowed(dev, qp, ibqp->qp_type))
		वापस -EOPNOTSUPP;

	अगर (attr_mask & ~(IB_QP_ATTR_STANDARD_BITS | IB_QP_RATE_LIMIT))
		वापस -EOPNOTSUPP;

	अगर (ibqp->rwq_ind_tbl)
		वापस -ENOSYS;

	अगर (udata && udata->inlen) अणु
		अगर (udata->inlen < दुरत्वend(typeof(ucmd), ece_options))
			वापस -EINVAL;

		अगर (udata->inlen > माप(ucmd) &&
		    !ib_is_udata_cleared(udata, माप(ucmd),
					 udata->inlen - माप(ucmd)))
			वापस -EOPNOTSUPP;

		अगर (ib_copy_from_udata(&ucmd, udata,
				       min(udata->inlen, माप(ucmd))))
			वापस -EFAULT;

		अगर (ucmd.comp_mask ||
		    स_प्रथम_inv(&ucmd.burst_info.reserved, 0,
			       माप(ucmd.burst_info.reserved)))
			वापस -EOPNOTSUPP;

	पूर्ण

	अगर (unlikely(ibqp->qp_type == IB_QPT_GSI))
		वापस mlx5_ib_gsi_modअगरy_qp(ibqp, attr, attr_mask);

	qp_type = (unlikely(ibqp->qp_type == MLX5_IB_QPT_HW_GSI)) ? IB_QPT_GSI :
								    qp->type;

	अगर (qp_type == MLX5_IB_QPT_DCT)
		वापस mlx5_ib_modअगरy_dct(ibqp, attr, attr_mask, &ucmd, udata);

	mutex_lock(&qp->mutex);

	cur_state = attr_mask & IB_QP_CUR_STATE ? attr->cur_qp_state : qp->state;
	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;

	अगर (qp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		अगर (attr_mask & ~(IB_QP_STATE | IB_QP_CUR_STATE)) अणु
			mlx5_ib_dbg(dev, "invalid attr_mask 0x%x when underlay QP is used\n",
				    attr_mask);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (qp_type != MLX5_IB_QPT_REG_UMR &&
		   qp_type != MLX5_IB_QPT_DCI &&
		   !ib_modअगरy_qp_is_ok(cur_state, new_state, qp_type,
				       attr_mask)) अणु
		mlx5_ib_dbg(dev, "invalid QP state transition from %d to %d, qp_type %d, attr_mask 0x%x\n",
			    cur_state, new_state, ibqp->qp_type, attr_mask);
		जाओ out;
	पूर्ण अन्यथा अगर (qp_type == MLX5_IB_QPT_DCI &&
		   !modअगरy_dci_qp_is_ok(cur_state, new_state, attr_mask)) अणु
		mlx5_ib_dbg(dev, "invalid QP state transition from %d to %d, qp_type %d, attr_mask 0x%x\n",
			    cur_state, new_state, qp_type, attr_mask);
		जाओ out;
	पूर्ण

	अगर ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 ||
	     attr->port_num > dev->num_ports)) अणु
		mlx5_ib_dbg(dev, "invalid port number %d. number of ports is %d\n",
			    attr->port_num, dev->num_ports);
		जाओ out;
	पूर्ण

	अगर ((attr_mask & IB_QP_PKEY_INDEX) &&
	    attr->pkey_index >= dev->pkey_table_len) अणु
		mlx5_ib_dbg(dev, "invalid pkey index %d\n", attr->pkey_index);
		जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic >
	    (1 << MLX5_CAP_GEN(dev->mdev, log_max_ra_res_qp))) अणु
		mlx5_ib_dbg(dev, "invalid max_rd_atomic value %d\n",
			    attr->max_rd_atomic);
		जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic >
	    (1 << MLX5_CAP_GEN(dev->mdev, log_max_ra_req_qp))) अणु
		mlx5_ib_dbg(dev, "invalid max_dest_rd_atomic value %d\n",
			    attr->max_dest_rd_atomic);
		जाओ out;
	पूर्ण

	अगर (cur_state == new_state && cur_state == IB_QPS_RESET) अणु
		err = 0;
		जाओ out;
	पूर्ण

	err = __mlx5_ib_modअगरy_qp(ibqp, attr, attr_mask, cur_state,
				  new_state, &ucmd, &resp, udata);

	/* resp.response_length is set in ECE supported flows only */
	अगर (!err && resp.response_length &&
	    udata->outlen >= resp.response_length)
		/* Return -EFAULT to the user and expect him to destroy QP. */
		err = ib_copy_to_udata(udata, &resp, resp.response_length);

out:
	mutex_unlock(&qp->mutex);
	वापस err;
पूर्ण

अटल अंतरभूत क्रमागत ib_qp_state to_ib_qp_state(क्रमागत mlx5_qp_state mlx5_state)
अणु
	चयन (mlx5_state) अणु
	हाल MLX5_QP_STATE_RST:      वापस IB_QPS_RESET;
	हाल MLX5_QP_STATE_INIT:     वापस IB_QPS_INIT;
	हाल MLX5_QP_STATE_RTR:      वापस IB_QPS_RTR;
	हाल MLX5_QP_STATE_RTS:      वापस IB_QPS_RTS;
	हाल MLX5_QP_STATE_SQ_DRAINING:
	हाल MLX5_QP_STATE_SQD:      वापस IB_QPS_SQD;
	हाल MLX5_QP_STATE_SQER:     वापस IB_QPS_SQE;
	हाल MLX5_QP_STATE_ERR:      वापस IB_QPS_ERR;
	शेष:		     वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत ib_mig_state to_ib_mig_state(पूर्णांक mlx5_mig_state)
अणु
	चयन (mlx5_mig_state) अणु
	हाल MLX5_QP_PM_ARMED:		वापस IB_MIG_ARMED;
	हाल MLX5_QP_PM_REARM:		वापस IB_MIG_REARM;
	हाल MLX5_QP_PM_MIGRATED:	वापस IB_MIG_MIGRATED;
	शेष: वापस -1;
	पूर्ण
पूर्ण

अटल व्योम to_rdma_ah_attr(काष्ठा mlx5_ib_dev *ibdev,
			    काष्ठा rdma_ah_attr *ah_attr, व्योम *path)
अणु
	पूर्णांक port = MLX5_GET(ads, path, vhca_port_num);
	पूर्णांक अटल_rate;

	स_रखो(ah_attr, 0, माप(*ah_attr));

	अगर (!port || port > ibdev->num_ports)
		वापस;

	ah_attr->type = rdma_ah_find_type(&ibdev->ib_dev, port);

	rdma_ah_set_port_num(ah_attr, port);
	rdma_ah_set_sl(ah_attr, MLX5_GET(ads, path, sl));

	rdma_ah_set_dlid(ah_attr, MLX5_GET(ads, path, rlid));
	rdma_ah_set_path_bits(ah_attr, MLX5_GET(ads, path, mlid));

	अटल_rate = MLX5_GET(ads, path, stat_rate);
	rdma_ah_set_अटल_rate(ah_attr, mlx5_to_ib_rate_map(अटल_rate));
	अगर (MLX5_GET(ads, path, grh) ||
	    ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		rdma_ah_set_grh(ah_attr, शून्य, MLX5_GET(ads, path, flow_label),
				MLX5_GET(ads, path, src_addr_index),
				MLX5_GET(ads, path, hop_limit),
				MLX5_GET(ads, path, tclass));
		rdma_ah_set_dgid_raw(ah_attr, MLX5_ADDR_OF(ads, path, rgid_rip));
	पूर्ण
पूर्ण

अटल पूर्णांक query_raw_packet_qp_sq_state(काष्ठा mlx5_ib_dev *dev,
					काष्ठा mlx5_ib_sq *sq,
					u8 *sq_state)
अणु
	पूर्णांक err;

	err = mlx5_core_query_sq_state(dev->mdev, sq->base.mqp.qpn, sq_state);
	अगर (err)
		जाओ out;
	sq->state = *sq_state;

out:
	वापस err;
पूर्ण

अटल पूर्णांक query_raw_packet_qp_rq_state(काष्ठा mlx5_ib_dev *dev,
					काष्ठा mlx5_ib_rq *rq,
					u8 *rq_state)
अणु
	व्योम *out;
	व्योम *rqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(query_rq_out);
	out = kvzalloc(inlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_core_query_rq(dev->mdev, rq->base.mqp.qpn, out);
	अगर (err)
		जाओ out;

	rqc = MLX5_ADDR_OF(query_rq_out, out, rq_context);
	*rq_state = MLX5_GET(rqc, rqc, state);
	rq->state = *rq_state;

out:
	kvमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक sqrq_state_to_qp_state(u8 sq_state, u8 rq_state,
				  काष्ठा mlx5_ib_qp *qp, u8 *qp_state)
अणु
	अटल स्थिर u8 sqrq_trans[MLX5_RQ_NUM_STATE][MLX5_SQ_NUM_STATE] = अणु
		[MLX5_RQC_STATE_RST] = अणु
			[MLX5_SQC_STATE_RST]	= IB_QPS_RESET,
			[MLX5_SQC_STATE_RDY]	= MLX5_QP_STATE_BAD,
			[MLX5_SQC_STATE_ERR]	= MLX5_QP_STATE_BAD,
			[MLX5_SQ_STATE_NA]	= IB_QPS_RESET,
		पूर्ण,
		[MLX5_RQC_STATE_RDY] = अणु
			[MLX5_SQC_STATE_RST]	= MLX5_QP_STATE,
			[MLX5_SQC_STATE_RDY]	= MLX5_QP_STATE,
			[MLX5_SQC_STATE_ERR]	= IB_QPS_SQE,
			[MLX5_SQ_STATE_NA]	= MLX5_QP_STATE,
		पूर्ण,
		[MLX5_RQC_STATE_ERR] = अणु
			[MLX5_SQC_STATE_RST]    = MLX5_QP_STATE_BAD,
			[MLX5_SQC_STATE_RDY]	= MLX5_QP_STATE_BAD,
			[MLX5_SQC_STATE_ERR]	= IB_QPS_ERR,
			[MLX5_SQ_STATE_NA]	= IB_QPS_ERR,
		पूर्ण,
		[MLX5_RQ_STATE_NA] = अणु
			[MLX5_SQC_STATE_RST]    = MLX5_QP_STATE,
			[MLX5_SQC_STATE_RDY]	= MLX5_QP_STATE,
			[MLX5_SQC_STATE_ERR]	= MLX5_QP_STATE,
			[MLX5_SQ_STATE_NA]	= MLX5_QP_STATE_BAD,
		पूर्ण,
	पूर्ण;

	*qp_state = sqrq_trans[rq_state][sq_state];

	अगर (*qp_state == MLX5_QP_STATE_BAD) अणु
		WARN(1, "Buggy Raw Packet QP state, SQ 0x%x state: 0x%x, RQ 0x%x state: 0x%x",
		     qp->raw_packet_qp.sq.base.mqp.qpn, sq_state,
		     qp->raw_packet_qp.rq.base.mqp.qpn, rq_state);
		वापस -EINVAL;
	पूर्ण

	अगर (*qp_state == MLX5_QP_STATE)
		*qp_state = qp->state;

	वापस 0;
पूर्ण

अटल पूर्णांक query_raw_packet_qp_state(काष्ठा mlx5_ib_dev *dev,
				     काष्ठा mlx5_ib_qp *qp,
				     u8 *raw_packet_qp_state)
अणु
	काष्ठा mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	काष्ठा mlx5_ib_sq *sq = &raw_packet_qp->sq;
	काष्ठा mlx5_ib_rq *rq = &raw_packet_qp->rq;
	पूर्णांक err;
	u8 sq_state = MLX5_SQ_STATE_NA;
	u8 rq_state = MLX5_RQ_STATE_NA;

	अगर (qp->sq.wqe_cnt) अणु
		err = query_raw_packet_qp_sq_state(dev, sq, &sq_state);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (qp->rq.wqe_cnt) अणु
		err = query_raw_packet_qp_rq_state(dev, rq, &rq_state);
		अगर (err)
			वापस err;
	पूर्ण

	वापस sqrq_state_to_qp_state(sq_state, rq_state, qp,
				      raw_packet_qp_state);
पूर्ण

अटल पूर्णांक query_qp_attr(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			 काष्ठा ib_qp_attr *qp_attr)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_qp_out);
	व्योम *qpc, *pri_path, *alt_path;
	u32 *outb;
	पूर्णांक err;

	outb = kzalloc(outlen, GFP_KERNEL);
	अगर (!outb)
		वापस -ENOMEM;

	err = mlx5_core_qp_query(dev, &qp->trans_qp.base.mqp, outb, outlen);
	अगर (err)
		जाओ out;

	qpc = MLX5_ADDR_OF(query_qp_out, outb, qpc);

	qp->state = to_ib_qp_state(MLX5_GET(qpc, qpc, state));
	अगर (MLX5_GET(qpc, qpc, state) == MLX5_QP_STATE_SQ_DRAINING)
		qp_attr->sq_draining = 1;

	qp_attr->path_mtu = MLX5_GET(qpc, qpc, mtu);
	qp_attr->path_mig_state = to_ib_mig_state(MLX5_GET(qpc, qpc, pm_state));
	qp_attr->qkey = MLX5_GET(qpc, qpc, q_key);
	qp_attr->rq_psn = MLX5_GET(qpc, qpc, next_rcv_psn);
	qp_attr->sq_psn = MLX5_GET(qpc, qpc, next_send_psn);
	qp_attr->dest_qp_num = MLX5_GET(qpc, qpc, remote_qpn);

	अगर (MLX5_GET(qpc, qpc, rre))
		qp_attr->qp_access_flags |= IB_ACCESS_REMOTE_READ;
	अगर (MLX5_GET(qpc, qpc, rwe))
		qp_attr->qp_access_flags |= IB_ACCESS_REMOTE_WRITE;
	अगर (MLX5_GET(qpc, qpc, rae))
		qp_attr->qp_access_flags |= IB_ACCESS_REMOTE_ATOMIC;

	qp_attr->max_rd_atomic = 1 << MLX5_GET(qpc, qpc, log_sra_max);
	qp_attr->max_dest_rd_atomic = 1 << MLX5_GET(qpc, qpc, log_rra_max);
	qp_attr->min_rnr_समयr = MLX5_GET(qpc, qpc, min_rnr_nak);
	qp_attr->retry_cnt = MLX5_GET(qpc, qpc, retry_count);
	qp_attr->rnr_retry = MLX5_GET(qpc, qpc, rnr_retry);

	pri_path = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
	alt_path = MLX5_ADDR_OF(qpc, qpc, secondary_address_path);

	अगर (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC ||
	    qp->ibqp.qp_type == IB_QPT_XRC_INI ||
	    qp->ibqp.qp_type == IB_QPT_XRC_TGT) अणु
		to_rdma_ah_attr(dev, &qp_attr->ah_attr, pri_path);
		to_rdma_ah_attr(dev, &qp_attr->alt_ah_attr, alt_path);
		qp_attr->alt_pkey_index = MLX5_GET(ads, alt_path, pkey_index);
		qp_attr->alt_port_num = MLX5_GET(ads, alt_path, vhca_port_num);
	पूर्ण

	qp_attr->pkey_index = MLX5_GET(ads, pri_path, pkey_index);
	qp_attr->port_num = MLX5_GET(ads, pri_path, vhca_port_num);
	qp_attr->समयout = MLX5_GET(ads, pri_path, ack_समयout);
	qp_attr->alt_समयout = MLX5_GET(ads, alt_path, ack_समयout);

out:
	kमुक्त(outb);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_dct_query_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *mqp,
				काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
				काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा mlx5_core_dct	*dct = &mqp->dct.mdct;
	u32 *out;
	u32 access_flags = 0;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_dct_out);
	व्योम *dctc;
	पूर्णांक err;
	पूर्णांक supported_mask = IB_QP_STATE |
			     IB_QP_ACCESS_FLAGS |
			     IB_QP_PORT |
			     IB_QP_MIN_RNR_TIMER |
			     IB_QP_AV |
			     IB_QP_PATH_MTU |
			     IB_QP_PKEY_INDEX;

	अगर (qp_attr_mask & ~supported_mask)
		वापस -EINVAL;
	अगर (mqp->state != IB_QPS_RTR)
		वापस -EINVAL;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_core_dct_query(dev, dct, out, outlen);
	अगर (err)
		जाओ out;

	dctc = MLX5_ADDR_OF(query_dct_out, out, dct_context_entry);

	अगर (qp_attr_mask & IB_QP_STATE)
		qp_attr->qp_state = IB_QPS_RTR;

	अगर (qp_attr_mask & IB_QP_ACCESS_FLAGS) अणु
		अगर (MLX5_GET(dctc, dctc, rre))
			access_flags |= IB_ACCESS_REMOTE_READ;
		अगर (MLX5_GET(dctc, dctc, rwe))
			access_flags |= IB_ACCESS_REMOTE_WRITE;
		अगर (MLX5_GET(dctc, dctc, rae))
			access_flags |= IB_ACCESS_REMOTE_ATOMIC;
		qp_attr->qp_access_flags = access_flags;
	पूर्ण

	अगर (qp_attr_mask & IB_QP_PORT)
		qp_attr->port_num = MLX5_GET(dctc, dctc, port);
	अगर (qp_attr_mask & IB_QP_MIN_RNR_TIMER)
		qp_attr->min_rnr_समयr = MLX5_GET(dctc, dctc, min_rnr_nak);
	अगर (qp_attr_mask & IB_QP_AV) अणु
		qp_attr->ah_attr.grh.traffic_class = MLX5_GET(dctc, dctc, tclass);
		qp_attr->ah_attr.grh.flow_label = MLX5_GET(dctc, dctc, flow_label);
		qp_attr->ah_attr.grh.sgid_index = MLX5_GET(dctc, dctc, my_addr_index);
		qp_attr->ah_attr.grh.hop_limit = MLX5_GET(dctc, dctc, hop_limit);
	पूर्ण
	अगर (qp_attr_mask & IB_QP_PATH_MTU)
		qp_attr->path_mtu = MLX5_GET(dctc, dctc, mtu);
	अगर (qp_attr_mask & IB_QP_PKEY_INDEX)
		qp_attr->pkey_index = MLX5_GET(dctc, dctc, pkey_index);
out:
	kमुक्त(out);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
		     पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx5_ib_qp *qp = to_mqp(ibqp);
	पूर्णांक err = 0;
	u8 raw_packet_qp_state;

	अगर (ibqp->rwq_ind_tbl)
		वापस -ENOSYS;

	अगर (unlikely(ibqp->qp_type == IB_QPT_GSI))
		वापस mlx5_ib_gsi_query_qp(ibqp, qp_attr, qp_attr_mask,
					    qp_init_attr);

	/* Not all of output fields are applicable, make sure to zero them */
	स_रखो(qp_init_attr, 0, माप(*qp_init_attr));
	स_रखो(qp_attr, 0, माप(*qp_attr));

	अगर (unlikely(qp->type == MLX5_IB_QPT_DCT))
		वापस mlx5_ib_dct_query_qp(dev, qp, qp_attr,
					    qp_attr_mask, qp_init_attr);

	mutex_lock(&qp->mutex);

	अगर (qp->ibqp.qp_type == IB_QPT_RAW_PACKET ||
	    qp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		err = query_raw_packet_qp_state(dev, qp, &raw_packet_qp_state);
		अगर (err)
			जाओ out;
		qp->state = raw_packet_qp_state;
		qp_attr->port_num = 1;
	पूर्ण अन्यथा अणु
		err = query_qp_attr(dev, qp, qp_attr);
		अगर (err)
			जाओ out;
	पूर्ण

	qp_attr->qp_state	     = qp->state;
	qp_attr->cur_qp_state	     = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr     = qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge    = qp->rq.max_gs;

	अगर (!ibqp->uobject) अणु
		qp_attr->cap.max_send_wr  = qp->sq.max_post;
		qp_attr->cap.max_send_sge = qp->sq.max_gs;
		qp_init_attr->qp_context = ibqp->qp_context;
	पूर्ण अन्यथा अणु
		qp_attr->cap.max_send_wr  = 0;
		qp_attr->cap.max_send_sge = 0;
	पूर्ण

	qp_init_attr->qp_type = ibqp->qp_type;
	qp_init_attr->recv_cq = ibqp->recv_cq;
	qp_init_attr->send_cq = ibqp->send_cq;
	qp_init_attr->srq = ibqp->srq;
	qp_attr->cap.max_अंतरभूत_data = qp->max_अंतरभूत_data;

	qp_init_attr->cap	     = qp_attr->cap;

	qp_init_attr->create_flags = qp->flags;

	qp_init_attr->sq_sig_type = qp->sq_संकेत_bits & MLX5_WQE_CTRL_CQ_UPDATE ?
		IB_SIGNAL_ALL_WR : IB_SIGNAL_REQ_WR;

out:
	mutex_unlock(&qp->mutex);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_alloc_xrcd(काष्ठा ib_xrcd *ibxrcd, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibxrcd->device);
	काष्ठा mlx5_ib_xrcd *xrcd = to_mxrcd(ibxrcd);

	अगर (!MLX5_CAP_GEN(dev->mdev, xrc))
		वापस -EOPNOTSUPP;

	वापस mlx5_cmd_xrcd_alloc(dev->mdev, &xrcd->xrcdn, 0);
पूर्ण

पूर्णांक mlx5_ib_dealloc_xrcd(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(xrcd->device);
	u32 xrcdn = to_mxrcd(xrcd)->xrcdn;

	वापस mlx5_cmd_xrcd_dealloc(dev->mdev, xrcdn, 0);
पूर्ण

अटल व्योम mlx5_ib_wq_event(काष्ठा mlx5_core_qp *core_qp, पूर्णांक type)
अणु
	काष्ठा mlx5_ib_rwq *rwq = to_mibrwq(core_qp);
	काष्ठा mlx5_ib_dev *dev = to_mdev(rwq->ibwq.device);
	काष्ठा ib_event event;

	अगर (rwq->ibwq.event_handler) अणु
		event.device     = rwq->ibwq.device;
		event.element.wq = &rwq->ibwq;
		चयन (type) अणु
		हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_WQ_FATAL;
			अवरोध;
		शेष:
			mlx5_ib_warn(dev, "Unexpected event type %d on WQ %06x\n", type, core_qp->qpn);
			वापस;
		पूर्ण

		rwq->ibwq.event_handler(&event, rwq->ibwq.wq_context);
	पूर्ण
पूर्ण

अटल पूर्णांक set_delay_drop(काष्ठा mlx5_ib_dev *dev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->delay_drop.lock);
	अगर (dev->delay_drop.activate)
		जाओ out;

	err = mlx5_core_set_delay_drop(dev, dev->delay_drop.समयout);
	अगर (err)
		जाओ out;

	dev->delay_drop.activate = true;
out:
	mutex_unlock(&dev->delay_drop.lock);

	अगर (!err)
		atomic_inc(&dev->delay_drop.rqs_cnt);
	वापस err;
पूर्ण

अटल पूर्णांक  create_rq(काष्ठा mlx5_ib_rwq *rwq, काष्ठा ib_pd *pd,
		      काष्ठा ib_wq_init_attr *init_attr)
अणु
	काष्ठा mlx5_ib_dev *dev;
	पूर्णांक has_net_offloads;
	__be64 *rq_pas0;
	पूर्णांक ts_क्रमmat;
	व्योम *in;
	व्योम *rqc;
	व्योम *wq;
	पूर्णांक inlen;
	पूर्णांक err;

	dev = to_mdev(pd->device);

	ts_क्रमmat = get_rq_ts_क्रमmat(dev, to_mcq(init_attr->cq));
	अगर (ts_क्रमmat < 0)
		वापस ts_क्रमmat;

	inlen = MLX5_ST_SZ_BYTES(create_rq_in) + माप(u64) * rwq->rq_num_pas;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_rq_in, in, uid, to_mpd(pd)->uid);
	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	MLX5_SET(rqc,  rqc, mem_rq_type,
		 MLX5_RQC_MEM_RQ_TYPE_MEMORY_RQ_INLINE);
	MLX5_SET(rqc, rqc, ts_क्रमmat, ts_क्रमmat);
	MLX5_SET(rqc, rqc, user_index, rwq->user_index);
	MLX5_SET(rqc,  rqc, cqn, to_mcq(init_attr->cq)->mcq.cqn);
	MLX5_SET(rqc,  rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc,  rqc, flush_in_error_en, 1);
	wq = MLX5_ADDR_OF(rqc, rqc, wq);
	MLX5_SET(wq, wq, wq_type,
		 rwq->create_flags & MLX5_IB_WQ_FLAGS_STRIDING_RQ ?
		 MLX5_WQ_TYPE_CYCLIC_STRIDING_RQ : MLX5_WQ_TYPE_CYCLIC);
	अगर (init_attr->create_flags & IB_WQ_FLAGS_PCI_WRITE_END_PADDING) अणु
		अगर (!MLX5_CAP_GEN(dev->mdev, end_pad)) अणु
			mlx5_ib_dbg(dev, "Scatter end padding is not supported\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण अन्यथा अणु
			MLX5_SET(wq, wq, end_padding_mode, MLX5_WQ_END_PAD_MODE_ALIGN);
		पूर्ण
	पूर्ण
	MLX5_SET(wq, wq, log_wq_stride, rwq->log_rq_stride);
	अगर (rwq->create_flags & MLX5_IB_WQ_FLAGS_STRIDING_RQ) अणु
		/*
		 * In Firmware number of strides in each WQE is:
		 *   "512 * 2^single_wqe_log_num_of_strides"
		 * Values 3 to 8 are accepted as 10 to 15, 9 to 18 are
		 * accepted as 0 to 9
		 */
		अटल स्थिर u8 fw_map[] = अणु 10, 11, 12, 13, 14, 15, 0, 1,
					     2,  3,  4,  5,  6,  7,  8, 9 पूर्ण;
		MLX5_SET(wq, wq, two_byte_shअगरt_en, rwq->two_byte_shअगरt_en);
		MLX5_SET(wq, wq, log_wqe_stride_size,
			 rwq->single_stride_log_num_of_bytes -
			 MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES);
		MLX5_SET(wq, wq, log_wqe_num_of_strides,
			 fw_map[rwq->log_num_strides -
				MLX5_EXT_MIN_SINGLE_WQE_LOG_NUM_STRIDES]);
	पूर्ण
	MLX5_SET(wq, wq, log_wq_sz, rwq->log_rq_size);
	MLX5_SET(wq, wq, pd, to_mpd(pd)->pdn);
	MLX5_SET(wq, wq, page_offset, rwq->rq_page_offset);
	MLX5_SET(wq, wq, log_wq_pg_sz, rwq->log_page_size);
	MLX5_SET(wq, wq, wq_signature, rwq->wq_sig);
	MLX5_SET64(wq, wq, dbr_addr, rwq->db.dma);
	has_net_offloads = MLX5_CAP_GEN(dev->mdev, eth_net_offloads);
	अगर (init_attr->create_flags & IB_WQ_FLAGS_CVLAN_STRIPPING) अणु
		अगर (!(has_net_offloads && MLX5_CAP_ETH(dev->mdev, vlan_cap))) अणु
			mlx5_ib_dbg(dev, "VLAN offloads are not supported\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		MLX5_SET(rqc, rqc, vsd, 1);
	पूर्ण
	अगर (init_attr->create_flags & IB_WQ_FLAGS_SCATTER_FCS) अणु
		अगर (!(has_net_offloads && MLX5_CAP_ETH(dev->mdev, scatter_fcs))) अणु
			mlx5_ib_dbg(dev, "Scatter FCS is not supported\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		MLX5_SET(rqc, rqc, scatter_fcs, 1);
	पूर्ण
	अगर (init_attr->create_flags & IB_WQ_FLAGS_DELAY_DROP) अणु
		अगर (!(dev->ib_dev.attrs.raw_packet_caps &
		      IB_RAW_PACKET_CAP_DELAY_DROP)) अणु
			mlx5_ib_dbg(dev, "Delay drop is not supported\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		MLX5_SET(rqc, rqc, delay_drop_en, 1);
	पूर्ण
	rq_pas0 = (__be64 *)MLX5_ADDR_OF(wq, wq, pas);
	mlx5_ib_populate_pas(rwq->umem, 1UL << rwq->page_shअगरt, rq_pas0, 0);
	err = mlx5_core_create_rq_tracked(dev, in, inlen, &rwq->core_qp);
	अगर (!err && init_attr->create_flags & IB_WQ_FLAGS_DELAY_DROP) अणु
		err = set_delay_drop(dev);
		अगर (err) अणु
			mlx5_ib_warn(dev, "Failed to enable delay drop err=%d\n",
				     err);
			mlx5_core_destroy_rq_tracked(dev, &rwq->core_qp);
		पूर्ण अन्यथा अणु
			rwq->create_flags |= MLX5_IB_WQ_FLAGS_DELAY_DROP;
		पूर्ण
	पूर्ण
out:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक set_user_rq_size(काष्ठा mlx5_ib_dev *dev,
			    काष्ठा ib_wq_init_attr *wq_init_attr,
			    काष्ठा mlx5_ib_create_wq *ucmd,
			    काष्ठा mlx5_ib_rwq *rwq)
अणु
	/* Sanity check RQ size beक्रमe proceeding */
	अगर (wq_init_attr->max_wr > (1 << MLX5_CAP_GEN(dev->mdev, log_max_wq_sz)))
		वापस -EINVAL;

	अगर (!ucmd->rq_wqe_count)
		वापस -EINVAL;

	rwq->wqe_count = ucmd->rq_wqe_count;
	rwq->wqe_shअगरt = ucmd->rq_wqe_shअगरt;
	अगर (check_shl_overflow(rwq->wqe_count, rwq->wqe_shअगरt, &rwq->buf_size))
		वापस -EINVAL;

	rwq->log_rq_stride = rwq->wqe_shअगरt;
	rwq->log_rq_size = ilog2(rwq->wqe_count);
	वापस 0;
पूर्ण

अटल bool log_of_strides_valid(काष्ठा mlx5_ib_dev *dev, u32 log_num_strides)
अणु
	अगर ((log_num_strides > MLX5_MAX_SINGLE_WQE_LOG_NUM_STRIDES) ||
	    (log_num_strides < MLX5_EXT_MIN_SINGLE_WQE_LOG_NUM_STRIDES))
		वापस false;

	अगर (!MLX5_CAP_GEN(dev->mdev, ext_stride_num_range) &&
	    (log_num_strides < MLX5_MIN_SINGLE_WQE_LOG_NUM_STRIDES))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक prepare_user_rq(काष्ठा ib_pd *pd,
			   काष्ठा ib_wq_init_attr *init_attr,
			   काष्ठा ib_udata *udata,
			   काष्ठा mlx5_ib_rwq *rwq)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_ib_create_wq ucmd = अणुपूर्ण;
	पूर्णांक err;
	माप_प्रकार required_cmd_sz;

	required_cmd_sz = दुरत्वend(काष्ठा mlx5_ib_create_wq,
				      single_stride_log_num_of_bytes);
	अगर (udata->inlen < required_cmd_sz) अणु
		mlx5_ib_dbg(dev, "invalid inlen\n");
		वापस -EINVAL;
	पूर्ण

	अगर (udata->inlen > माप(ucmd) &&
	    !ib_is_udata_cleared(udata, माप(ucmd),
				 udata->inlen - माप(ucmd))) अणु
		mlx5_ib_dbg(dev, "inlen is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ib_copy_from_udata(&ucmd, udata, min(माप(ucmd), udata->inlen))) अणु
		mlx5_ib_dbg(dev, "copy failed\n");
		वापस -EFAULT;
	पूर्ण

	अगर (ucmd.comp_mask & (~MLX5_IB_CREATE_WQ_STRIDING_RQ)) अणु
		mlx5_ib_dbg(dev, "invalid comp mask\n");
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (ucmd.comp_mask & MLX5_IB_CREATE_WQ_STRIDING_RQ) अणु
		अगर (!MLX5_CAP_GEN(dev->mdev, striding_rq)) अणु
			mlx5_ib_dbg(dev, "Striding RQ is not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर ((ucmd.single_stride_log_num_of_bytes <
		    MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES) ||
		    (ucmd.single_stride_log_num_of_bytes >
		     MLX5_MAX_SINGLE_STRIDE_LOG_NUM_BYTES)) अणु
			mlx5_ib_dbg(dev, "Invalid log stride size (%u. Range is %u - %u)\n",
				    ucmd.single_stride_log_num_of_bytes,
				    MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES,
				    MLX5_MAX_SINGLE_STRIDE_LOG_NUM_BYTES);
			वापस -EINVAL;
		पूर्ण
		अगर (!log_of_strides_valid(dev,
					  ucmd.single_wqe_log_num_of_strides)) अणु
			mlx5_ib_dbg(
				dev,
				"Invalid log num strides (%u. Range is %u - %u)\n",
				ucmd.single_wqe_log_num_of_strides,
				MLX5_CAP_GEN(dev->mdev, ext_stride_num_range) ?
					MLX5_EXT_MIN_SINGLE_WQE_LOG_NUM_STRIDES :
					MLX5_MIN_SINGLE_WQE_LOG_NUM_STRIDES,
				MLX5_MAX_SINGLE_WQE_LOG_NUM_STRIDES);
			वापस -EINVAL;
		पूर्ण
		rwq->single_stride_log_num_of_bytes =
			ucmd.single_stride_log_num_of_bytes;
		rwq->log_num_strides = ucmd.single_wqe_log_num_of_strides;
		rwq->two_byte_shअगरt_en = !!ucmd.two_byte_shअगरt_en;
		rwq->create_flags |= MLX5_IB_WQ_FLAGS_STRIDING_RQ;
	पूर्ण

	err = set_user_rq_size(dev, init_attr, &ucmd, rwq);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		वापस err;
	पूर्ण

	err = create_user_rq(dev, pd, udata, rwq, &ucmd);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "err %d\n", err);
		वापस err;
	पूर्ण

	rwq->user_index = ucmd.user_index;
	वापस 0;
पूर्ण

काष्ठा ib_wq *mlx5_ib_create_wq(काष्ठा ib_pd *pd,
				काष्ठा ib_wq_init_attr *init_attr,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev;
	काष्ठा mlx5_ib_rwq *rwq;
	काष्ठा mlx5_ib_create_wq_resp resp = अणुपूर्ण;
	माप_प्रकार min_resp_len;
	पूर्णांक err;

	अगर (!udata)
		वापस ERR_PTR(-ENOSYS);

	min_resp_len = दुरत्वend(काष्ठा mlx5_ib_create_wq_resp, reserved);
	अगर (udata->outlen && udata->outlen < min_resp_len)
		वापस ERR_PTR(-EINVAL);

	अगर (!capable(CAP_SYS_RAWIO) &&
	    init_attr->create_flags & IB_WQ_FLAGS_DELAY_DROP)
		वापस ERR_PTR(-EPERM);

	dev = to_mdev(pd->device);
	चयन (init_attr->wq_type) अणु
	हाल IB_WQT_RQ:
		rwq = kzalloc(माप(*rwq), GFP_KERNEL);
		अगर (!rwq)
			वापस ERR_PTR(-ENOMEM);
		err = prepare_user_rq(pd, init_attr, udata, rwq);
		अगर (err)
			जाओ err;
		err = create_rq(rwq, pd, init_attr);
		अगर (err)
			जाओ err_user_rq;
		अवरोध;
	शेष:
		mlx5_ib_dbg(dev, "unsupported wq type %d\n",
			    init_attr->wq_type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rwq->ibwq.wq_num = rwq->core_qp.qpn;
	rwq->ibwq.state = IB_WQS_RESET;
	अगर (udata->outlen) अणु
		resp.response_length = दुरत्वend(
			काष्ठा mlx5_ib_create_wq_resp, response_length);
		err = ib_copy_to_udata(udata, &resp, resp.response_length);
		अगर (err)
			जाओ err_copy;
	पूर्ण

	rwq->core_qp.event = mlx5_ib_wq_event;
	rwq->ibwq.event_handler = init_attr->event_handler;
	वापस &rwq->ibwq;

err_copy:
	mlx5_core_destroy_rq_tracked(dev, &rwq->core_qp);
err_user_rq:
	destroy_user_rq(dev, pd, rwq, udata);
err:
	kमुक्त(rwq);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक mlx5_ib_destroy_wq(काष्ठा ib_wq *wq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(wq->device);
	काष्ठा mlx5_ib_rwq *rwq = to_mrwq(wq);
	पूर्णांक ret;

	ret = mlx5_core_destroy_rq_tracked(dev, &rwq->core_qp);
	अगर (ret)
		वापस ret;
	destroy_user_rq(dev, wq->pd, rwq, udata);
	kमुक्त(rwq);
	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_create_rwq_ind_table(काष्ठा ib_rwq_ind_table *ib_rwq_ind_table,
				 काष्ठा ib_rwq_ind_table_init_attr *init_attr,
				 काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_rwq_ind_table *rwq_ind_tbl =
		to_mrwq_ind_table(ib_rwq_ind_table);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ib_rwq_ind_table->device);
	पूर्णांक sz = 1 << init_attr->log_ind_tbl_size;
	काष्ठा mlx5_ib_create_rwq_ind_tbl_resp resp = अणुपूर्ण;
	माप_प्रकार min_resp_len;
	पूर्णांक inlen;
	पूर्णांक err;
	पूर्णांक i;
	u32 *in;
	व्योम *rqtc;

	अगर (udata->inlen > 0 &&
	    !ib_is_udata_cleared(udata, 0,
				 udata->inlen))
		वापस -EOPNOTSUPP;

	अगर (init_attr->log_ind_tbl_size >
	    MLX5_CAP_GEN(dev->mdev, log_max_rqt_size)) अणु
		mlx5_ib_dbg(dev, "log_ind_tbl_size = %d is bigger than supported = %d\n",
			    init_attr->log_ind_tbl_size,
			    MLX5_CAP_GEN(dev->mdev, log_max_rqt_size));
		वापस -EINVAL;
	पूर्ण

	min_resp_len =
		दुरत्वend(काष्ठा mlx5_ib_create_rwq_ind_tbl_resp, reserved);
	अगर (udata->outlen && udata->outlen < min_resp_len)
		वापस -EINVAL;

	inlen = MLX5_ST_SZ_BYTES(create_rqt_in) + माप(u32) * sz;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqtc = MLX5_ADDR_OF(create_rqt_in, in, rqt_context);

	MLX5_SET(rqtc, rqtc, rqt_actual_size, sz);
	MLX5_SET(rqtc, rqtc, rqt_max_size, sz);

	क्रम (i = 0; i < sz; i++)
		MLX5_SET(rqtc, rqtc, rq_num[i], init_attr->ind_tbl[i]->wq_num);

	rwq_ind_tbl->uid = to_mpd(init_attr->ind_tbl[0]->pd)->uid;
	MLX5_SET(create_rqt_in, in, uid, rwq_ind_tbl->uid);

	err = mlx5_core_create_rqt(dev->mdev, in, inlen, &rwq_ind_tbl->rqtn);
	kvमुक्त(in);
	अगर (err)
		वापस err;

	rwq_ind_tbl->ib_rwq_ind_tbl.ind_tbl_num = rwq_ind_tbl->rqtn;
	अगर (udata->outlen) अणु
		resp.response_length =
			दुरत्वend(काष्ठा mlx5_ib_create_rwq_ind_tbl_resp,
				    response_length);
		err = ib_copy_to_udata(udata, &resp, resp.response_length);
		अगर (err)
			जाओ err_copy;
	पूर्ण

	वापस 0;

err_copy:
	mlx5_cmd_destroy_rqt(dev->mdev, rwq_ind_tbl->rqtn, rwq_ind_tbl->uid);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_destroy_rwq_ind_table(काष्ठा ib_rwq_ind_table *ib_rwq_ind_tbl)
अणु
	काष्ठा mlx5_ib_rwq_ind_table *rwq_ind_tbl = to_mrwq_ind_table(ib_rwq_ind_tbl);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ib_rwq_ind_tbl->device);

	वापस mlx5_cmd_destroy_rqt(dev->mdev, rwq_ind_tbl->rqtn, rwq_ind_tbl->uid);
पूर्ण

पूर्णांक mlx5_ib_modअगरy_wq(काष्ठा ib_wq *wq, काष्ठा ib_wq_attr *wq_attr,
		      u32 wq_attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(wq->device);
	काष्ठा mlx5_ib_rwq *rwq = to_mrwq(wq);
	काष्ठा mlx5_ib_modअगरy_wq ucmd = अणुपूर्ण;
	माप_प्रकार required_cmd_sz;
	पूर्णांक curr_wq_state;
	पूर्णांक wq_state;
	पूर्णांक inlen;
	पूर्णांक err;
	व्योम *rqc;
	व्योम *in;

	required_cmd_sz = दुरत्वend(काष्ठा mlx5_ib_modअगरy_wq, reserved);
	अगर (udata->inlen < required_cmd_sz)
		वापस -EINVAL;

	अगर (udata->inlen > माप(ucmd) &&
	    !ib_is_udata_cleared(udata, माप(ucmd),
				 udata->inlen - माप(ucmd)))
		वापस -EOPNOTSUPP;

	अगर (ib_copy_from_udata(&ucmd, udata, min(माप(ucmd), udata->inlen)))
		वापस -EFAULT;

	अगर (ucmd.comp_mask || ucmd.reserved)
		वापस -EOPNOTSUPP;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqc = MLX5_ADDR_OF(modअगरy_rq_in, in, ctx);

	curr_wq_state = (wq_attr_mask & IB_WQ_CUR_STATE) ?
		wq_attr->curr_wq_state : wq->state;
	wq_state = (wq_attr_mask & IB_WQ_STATE) ?
		wq_attr->wq_state : curr_wq_state;
	अगर (curr_wq_state == IB_WQS_ERR)
		curr_wq_state = MLX5_RQC_STATE_ERR;
	अगर (wq_state == IB_WQS_ERR)
		wq_state = MLX5_RQC_STATE_ERR;
	MLX5_SET(modअगरy_rq_in, in, rq_state, curr_wq_state);
	MLX5_SET(modअगरy_rq_in, in, uid, to_mpd(wq->pd)->uid);
	MLX5_SET(rqc, rqc, state, wq_state);

	अगर (wq_attr_mask & IB_WQ_FLAGS) अणु
		अगर (wq_attr->flags_mask & IB_WQ_FLAGS_CVLAN_STRIPPING) अणु
			अगर (!(MLX5_CAP_GEN(dev->mdev, eth_net_offloads) &&
			      MLX5_CAP_ETH(dev->mdev, vlan_cap))) अणु
				mlx5_ib_dbg(dev, "VLAN offloads are not "
					    "supported\n");
				err = -EOPNOTSUPP;
				जाओ out;
			पूर्ण
			MLX5_SET64(modअगरy_rq_in, in, modअगरy_biपंचांगask,
				   MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_VSD);
			MLX5_SET(rqc, rqc, vsd,
				 (wq_attr->flags & IB_WQ_FLAGS_CVLAN_STRIPPING) ? 0 : 1);
		पूर्ण

		अगर (wq_attr->flags_mask & IB_WQ_FLAGS_PCI_WRITE_END_PADDING) अणु
			mlx5_ib_dbg(dev, "Modifying scatter end padding is not supported\n");
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (curr_wq_state == IB_WQS_RESET && wq_state == IB_WQS_RDY) अणु
		u16 set_id;

		set_id = mlx5_ib_get_counters_id(dev, 0);
		अगर (MLX5_CAP_GEN(dev->mdev, modअगरy_rq_counter_set_id)) अणु
			MLX5_SET64(modअगरy_rq_in, in, modअगरy_biपंचांगask,
				   MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_RQ_COUNTER_SET_ID);
			MLX5_SET(rqc, rqc, counter_set_id, set_id);
		पूर्ण अन्यथा
			dev_info_once(
				&dev->ib_dev.dev,
				"Receive WQ counters are not supported on current FW\n");
	पूर्ण

	err = mlx5_core_modअगरy_rq(dev->mdev, rwq->core_qp.qpn, in);
	अगर (!err)
		rwq->ibwq.state = (wq_state == MLX5_RQC_STATE_ERR) ? IB_WQS_ERR : wq_state;

out:
	kvमुक्त(in);
	वापस err;
पूर्ण

काष्ठा mlx5_ib_drain_cqe अणु
	काष्ठा ib_cqe cqe;
	काष्ठा completion करोne;
पूर्ण;

अटल व्योम mlx5_ib_drain_qp_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx5_ib_drain_cqe *cqe = container_of(wc->wr_cqe,
						     काष्ठा mlx5_ib_drain_cqe,
						     cqe);

	complete(&cqe->करोne);
पूर्ण

/* This function वापसs only once the drained WR was completed */
अटल व्योम handle_drain_completion(काष्ठा ib_cq *cq,
				    काष्ठा mlx5_ib_drain_cqe *sdrain,
				    काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	अगर (cq->poll_ctx == IB_POLL_सूचीECT) अणु
		जबतक (रुको_क्रम_completion_समयout(&sdrain->करोne, HZ / 10) <= 0)
			ib_process_cq_direct(cq, -1);
		वापस;
	पूर्ण

	अगर (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		काष्ठा mlx5_ib_cq *mcq = to_mcq(cq);
		bool triggered = false;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
		/* Make sure that the CQ handler won't run if wasn't run yet */
		अगर (!mcq->mcq.reset_notअगरy_added)
			mcq->mcq.reset_notअगरy_added = 1;
		अन्यथा
			triggered = true;
		spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

		अगर (triggered) अणु
			/* Wait क्रम any scheduled/running task to be ended */
			चयन (cq->poll_ctx) अणु
			हाल IB_POLL_SOFTIRQ:
				irq_poll_disable(&cq->iop);
				irq_poll_enable(&cq->iop);
				अवरोध;
			हाल IB_POLL_WORKQUEUE:
				cancel_work_sync(&cq->work);
				अवरोध;
			शेष:
				WARN_ON_ONCE(1);
			पूर्ण
		पूर्ण

		/* Run the CQ handler - this makes sure that the drain WR will
		 * be processed अगर wasn't processed yet.
		 */
		mcq->mcq.comp(&mcq->mcq, शून्य);
	पूर्ण

	रुको_क्रम_completion(&sdrain->करोne);
पूर्ण

व्योम mlx5_ib_drain_sq(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_cq *cq = qp->send_cq;
	काष्ठा ib_qp_attr attr = अणु .qp_state = IB_QPS_ERR पूर्ण;
	काष्ठा mlx5_ib_drain_cqe sdrain;
	स्थिर काष्ठा ib_send_wr *bad_swr;
	काष्ठा ib_rdma_wr swr = अणु
		.wr = अणु
			.next = शून्य,
			अणु .wr_cqe	= &sdrain.cqe, पूर्ण,
			.opcode	= IB_WR_RDMA_WRITE,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret && mdev->state != MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		WARN_ONCE(ret, "failed to drain send queue: %d\n", ret);
		वापस;
	पूर्ण

	sdrain.cqe.करोne = mlx5_ib_drain_qp_करोne;
	init_completion(&sdrain.करोne);

	ret = mlx5_ib_post_send_drain(qp, &swr.wr, &bad_swr);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain send queue: %d\n", ret);
		वापस;
	पूर्ण

	handle_drain_completion(cq, &sdrain, dev);
पूर्ण

व्योम mlx5_ib_drain_rq(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_cq *cq = qp->recv_cq;
	काष्ठा ib_qp_attr attr = अणु .qp_state = IB_QPS_ERR पूर्ण;
	काष्ठा mlx5_ib_drain_cqe rdrain;
	काष्ठा ib_recv_wr rwr = अणुपूर्ण;
	स्थिर काष्ठा ib_recv_wr *bad_rwr;
	पूर्णांक ret;
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret && mdev->state != MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		वापस;
	पूर्ण

	rwr.wr_cqe = &rdrain.cqe;
	rdrain.cqe.करोne = mlx5_ib_drain_qp_करोne;
	init_completion(&rdrain.करोne);

	ret = mlx5_ib_post_recv_drain(qp, &rwr, &bad_rwr);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		वापस;
	पूर्ण

	handle_drain_completion(cq, &rdrain, dev);
पूर्ण

/*
 * Bind a qp to a counter. If @counter is शून्य then bind the qp to
 * the शेष counter
 */
पूर्णांक mlx5_ib_qp_set_counter(काष्ठा ib_qp *qp, काष्ठा rdma_counter *counter)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	पूर्णांक err = 0;

	mutex_lock(&mqp->mutex);
	अगर (mqp->state == IB_QPS_RESET) अणु
		qp->counter = counter;
		जाओ out;
	पूर्ण

	अगर (!MLX5_CAP_GEN(dev->mdev, rts2rts_qp_counters_set_id)) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (mqp->state == IB_QPS_RTS) अणु
		err = __mlx5_ib_qp_set_counter(qp, counter);
		अगर (!err)
			qp->counter = counter;

		जाओ out;
	पूर्ण

	mqp->counter_pending = 1;
	qp->counter = counter;

out:
	mutex_unlock(&mqp->mutex);
	वापस err;
पूर्ण
