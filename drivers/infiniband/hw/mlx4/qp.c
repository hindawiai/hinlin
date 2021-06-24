<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/log2.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>

#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश <linux/mlx4/driver.h>
#समावेश <linux/mlx4/qp.h>

#समावेश "mlx4_ib.h"
#समावेश <rdma/mlx4-abi.h>

अटल व्योम mlx4_ib_lock_cqs(काष्ठा mlx4_ib_cq *send_cq,
			     काष्ठा mlx4_ib_cq *recv_cq);
अटल व्योम mlx4_ib_unlock_cqs(काष्ठा mlx4_ib_cq *send_cq,
			       काष्ठा mlx4_ib_cq *recv_cq);
अटल पूर्णांक _mlx4_ib_modअगरy_wq(काष्ठा ib_wq *ibwq, क्रमागत ib_wq_state new_state,
			      काष्ठा ib_udata *udata);

क्रमागत अणु
	MLX4_IB_ACK_REQ_FREQ	= 8,
पूर्ण;

क्रमागत अणु
	MLX4_IB_DEFAULT_SCHED_QUEUE	= 0x83,
	MLX4_IB_DEFAULT_QP0_SCHED_QUEUE	= 0x3f,
	MLX4_IB_LINK_TYPE_IB		= 0,
	MLX4_IB_LINK_TYPE_ETH		= 1
पूर्ण;

क्रमागत अणु
	MLX4_IB_MIN_SQ_STRIDE	= 6,
	MLX4_IB_CACHE_LINE_SIZE	= 64,
पूर्ण;

क्रमागत अणु
	MLX4_RAW_QP_MTU		= 7,
	MLX4_RAW_QP_MSGMAX	= 31,
पूर्ण;

#अगर_अघोषित ETH_ALEN
#घोषणा ETH_ALEN        6
#पूर्ण_अगर

अटल स्थिर __be32 mlx4_ib_opcode[] = अणु
	[IB_WR_SEND]				= cpu_to_be32(MLX4_OPCODE_SEND),
	[IB_WR_LSO]				= cpu_to_be32(MLX4_OPCODE_LSO),
	[IB_WR_SEND_WITH_IMM]			= cpu_to_be32(MLX4_OPCODE_SEND_IMM),
	[IB_WR_RDMA_WRITE]			= cpu_to_be32(MLX4_OPCODE_RDMA_WRITE),
	[IB_WR_RDMA_WRITE_WITH_IMM]		= cpu_to_be32(MLX4_OPCODE_RDMA_WRITE_IMM),
	[IB_WR_RDMA_READ]			= cpu_to_be32(MLX4_OPCODE_RDMA_READ),
	[IB_WR_ATOMIC_CMP_AND_SWP]		= cpu_to_be32(MLX4_OPCODE_ATOMIC_CS),
	[IB_WR_ATOMIC_FETCH_AND_ADD]		= cpu_to_be32(MLX4_OPCODE_ATOMIC_FA),
	[IB_WR_SEND_WITH_INV]			= cpu_to_be32(MLX4_OPCODE_SEND_INVAL),
	[IB_WR_LOCAL_INV]			= cpu_to_be32(MLX4_OPCODE_LOCAL_INVAL),
	[IB_WR_REG_MR]				= cpu_to_be32(MLX4_OPCODE_FMR),
	[IB_WR_MASKED_ATOMIC_CMP_AND_SWP]	= cpu_to_be32(MLX4_OPCODE_MASKED_ATOMIC_CS),
	[IB_WR_MASKED_ATOMIC_FETCH_AND_ADD]	= cpu_to_be32(MLX4_OPCODE_MASKED_ATOMIC_FA),
पूर्ण;

क्रमागत mlx4_ib_source_type अणु
	MLX4_IB_QP_SRC	= 0,
	MLX4_IB_RWQ_SRC	= 1,
पूर्ण;

अटल पूर्णांक is_tunnel_qp(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	अगर (!mlx4_is_master(dev->dev))
		वापस 0;

	वापस qp->mqp.qpn >= dev->dev->phys_caps.base_tunnel_sqpn &&
	       qp->mqp.qpn < dev->dev->phys_caps.base_tunnel_sqpn +
		8 * MLX4_MFUNC_MAX;
पूर्ण

अटल पूर्णांक is_sqp(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	पूर्णांक proxy_sqp = 0;
	पूर्णांक real_sqp = 0;
	पूर्णांक i;
	/* PPF or Native -- real SQP */
	real_sqp = ((mlx4_is_master(dev->dev) || !mlx4_is_mfunc(dev->dev)) &&
		    qp->mqp.qpn >= dev->dev->phys_caps.base_sqpn &&
		    qp->mqp.qpn <= dev->dev->phys_caps.base_sqpn + 3);
	अगर (real_sqp)
		वापस 1;
	/* VF or PF -- proxy SQP */
	अगर (mlx4_is_mfunc(dev->dev)) अणु
		क्रम (i = 0; i < dev->dev->caps.num_ports; i++) अणु
			अगर (qp->mqp.qpn == dev->dev->caps.spec_qps[i].qp0_proxy ||
			    qp->mqp.qpn == dev->dev->caps.spec_qps[i].qp1_proxy) अणु
				proxy_sqp = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (proxy_sqp)
		वापस 1;

	वापस !!(qp->flags & MLX4_IB_ROCE_V2_GSI_QP);
पूर्ण

/* used क्रम INIT/CLOSE port logic */
अटल पूर्णांक is_qp0(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	पूर्णांक proxy_qp0 = 0;
	पूर्णांक real_qp0 = 0;
	पूर्णांक i;
	/* PPF or Native -- real QP0 */
	real_qp0 = ((mlx4_is_master(dev->dev) || !mlx4_is_mfunc(dev->dev)) &&
		    qp->mqp.qpn >= dev->dev->phys_caps.base_sqpn &&
		    qp->mqp.qpn <= dev->dev->phys_caps.base_sqpn + 1);
	अगर (real_qp0)
		वापस 1;
	/* VF or PF -- proxy QP0 */
	अगर (mlx4_is_mfunc(dev->dev)) अणु
		क्रम (i = 0; i < dev->dev->caps.num_ports; i++) अणु
			अगर (qp->mqp.qpn == dev->dev->caps.spec_qps[i].qp0_proxy) अणु
				proxy_qp0 = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस proxy_qp0;
पूर्ण

अटल व्योम *get_wqe(काष्ठा mlx4_ib_qp *qp, पूर्णांक offset)
अणु
	वापस mlx4_buf_offset(&qp->buf, offset);
पूर्ण

अटल व्योम *get_recv_wqe(काष्ठा mlx4_ib_qp *qp, पूर्णांक n)
अणु
	वापस get_wqe(qp, qp->rq.offset + (n << qp->rq.wqe_shअगरt));
पूर्ण

अटल व्योम *get_send_wqe(काष्ठा mlx4_ib_qp *qp, पूर्णांक n)
अणु
	वापस get_wqe(qp, qp->sq.offset + (n << qp->sq.wqe_shअगरt));
पूर्ण

/*
 * Stamp a SQ WQE so that it is invalid अगर prefetched by marking the
 * first four bytes of every 64 byte chunk with 0xffffffff, except क्रम
 * the very first chunk of the WQE.
 */
अटल व्योम stamp_send_wqe(काष्ठा mlx4_ib_qp *qp, पूर्णांक n)
अणु
	__be32 *wqe;
	पूर्णांक i;
	पूर्णांक s;
	व्योम *buf;
	काष्ठा mlx4_wqe_ctrl_seg *ctrl;

	buf = get_send_wqe(qp, n & (qp->sq.wqe_cnt - 1));
	ctrl = (काष्ठा mlx4_wqe_ctrl_seg *)buf;
	s = (ctrl->qpn_vlan.fence_size & 0x3f) << 4;
	क्रम (i = 64; i < s; i += 64) अणु
		wqe = buf + i;
		*wqe = cpu_to_be32(0xffffffff);
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_qp_event(काष्ठा mlx4_qp *qp, क्रमागत mlx4_event type)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_qp *ibqp = &to_mibqp(qp)->ibqp;

	अगर (type == MLX4_EVENT_TYPE_PATH_MIG)
		to_mibqp(qp)->port = to_mibqp(qp)->alt_port;

	अगर (ibqp->event_handler) अणु
		event.device     = ibqp->device;
		event.element.qp = ibqp;
		चयन (type) अणु
		हाल MLX4_EVENT_TYPE_PATH_MIG:
			event.event = IB_EVENT_PATH_MIG;
			अवरोध;
		हाल MLX4_EVENT_TYPE_COMM_EST:
			event.event = IB_EVENT_COMM_EST;
			अवरोध;
		हाल MLX4_EVENT_TYPE_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			अवरोध;
		हाल MLX4_EVENT_TYPE_SRQ_QP_LAST_WQE:
			event.event = IB_EVENT_QP_LAST_WQE_REACHED;
			अवरोध;
		हाल MLX4_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_QP_FATAL;
			अवरोध;
		हाल MLX4_EVENT_TYPE_PATH_MIG_FAILED:
			event.event = IB_EVENT_PATH_MIG_ERR;
			अवरोध;
		हाल MLX4_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
			event.event = IB_EVENT_QP_REQ_ERR;
			अवरोध;
		हाल MLX4_EVENT_TYPE_WQ_ACCESS_ERROR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			अवरोध;
		शेष:
			pr_warn("Unexpected event type %d "
			       "on QP %06x\n", type, qp->qpn);
			वापस;
		पूर्ण

		ibqp->event_handler(&event, ibqp->qp_context);
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_wq_event(काष्ठा mlx4_qp *qp, क्रमागत mlx4_event type)
अणु
	pr_warn_ratelimited("Unexpected event type %d on WQ 0x%06x. Events are not supported for WQs\n",
			    type, qp->qpn);
पूर्ण

अटल पूर्णांक send_wqe_overhead(क्रमागत mlx4_ib_qp_type type, u32 flags)
अणु
	/*
	 * UD WQEs must have a datagram segment.
	 * RC and UC WQEs might have a remote address segment.
	 * MLX WQEs need two extra अंतरभूत data segments (क्रम the UD
	 * header and space क्रम the ICRC).
	 */
	चयन (type) अणु
	हाल MLX4_IB_QPT_UD:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg) +
			माप (काष्ठा mlx4_wqe_datagram_seg) +
			((flags & MLX4_IB_QP_LSO) ? MLX4_IB_LSO_HEADER_SPARE : 0);
	हाल MLX4_IB_QPT_PROXY_SMI_OWNER:
	हाल MLX4_IB_QPT_PROXY_SMI:
	हाल MLX4_IB_QPT_PROXY_GSI:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg) +
			माप (काष्ठा mlx4_wqe_datagram_seg) + 64;
	हाल MLX4_IB_QPT_TUN_SMI_OWNER:
	हाल MLX4_IB_QPT_TUN_GSI:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg) +
			माप (काष्ठा mlx4_wqe_datagram_seg);

	हाल MLX4_IB_QPT_UC:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg) +
			माप (काष्ठा mlx4_wqe_raddr_seg);
	हाल MLX4_IB_QPT_RC:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg) +
			माप (काष्ठा mlx4_wqe_masked_atomic_seg) +
			माप (काष्ठा mlx4_wqe_raddr_seg);
	हाल MLX4_IB_QPT_SMI:
	हाल MLX4_IB_QPT_GSI:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg) +
			ALIGN(MLX4_IB_UD_HEADER_SIZE +
			      DIV_ROUND_UP(MLX4_IB_UD_HEADER_SIZE,
					   MLX4_INLINE_ALIGN) *
			      माप (काष्ठा mlx4_wqe_अंतरभूत_seg),
			      माप (काष्ठा mlx4_wqe_data_seg)) +
			ALIGN(4 +
			      माप (काष्ठा mlx4_wqe_अंतरभूत_seg),
			      माप (काष्ठा mlx4_wqe_data_seg));
	शेष:
		वापस माप (काष्ठा mlx4_wqe_ctrl_seg);
	पूर्ण
पूर्ण

अटल पूर्णांक set_rq_size(काष्ठा mlx4_ib_dev *dev, काष्ठा ib_qp_cap *cap,
		       bool is_user, bool has_rq, काष्ठा mlx4_ib_qp *qp,
		       u32 inl_recv_sz)
अणु
	/* Sanity check RQ size beक्रमe proceeding */
	अगर (cap->max_recv_wr > dev->dev->caps.max_wqes - MLX4_IB_SQ_MAX_SPARE ||
	    cap->max_recv_sge > min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_rq_sg))
		वापस -EINVAL;

	अगर (!has_rq) अणु
		अगर (cap->max_recv_wr || inl_recv_sz)
			वापस -EINVAL;

		qp->rq.wqe_cnt = qp->rq.max_gs = 0;
	पूर्ण अन्यथा अणु
		u32 max_inl_recv_sz = dev->dev->caps.max_rq_sg *
			माप(काष्ठा mlx4_wqe_data_seg);
		u32 wqe_size;

		/* HW requires >= 1 RQ entry with >= 1 gather entry */
		अगर (is_user && (!cap->max_recv_wr || !cap->max_recv_sge ||
				inl_recv_sz > max_inl_recv_sz))
			वापस -EINVAL;

		qp->rq.wqe_cnt	 = roundup_घात_of_two(max(1U, cap->max_recv_wr));
		qp->rq.max_gs	 = roundup_घात_of_two(max(1U, cap->max_recv_sge));
		wqe_size = qp->rq.max_gs * माप(काष्ठा mlx4_wqe_data_seg);
		qp->rq.wqe_shअगरt = ilog2(max_t(u32, wqe_size, inl_recv_sz));
	पूर्ण

	/* leave userspace वापस values as they were, so as not to अवरोध ABI */
	अगर (is_user) अणु
		cap->max_recv_wr  = qp->rq.max_post = qp->rq.wqe_cnt;
		cap->max_recv_sge = qp->rq.max_gs;
	पूर्ण अन्यथा अणु
		cap->max_recv_wr  = qp->rq.max_post =
			min(dev->dev->caps.max_wqes - MLX4_IB_SQ_MAX_SPARE, qp->rq.wqe_cnt);
		cap->max_recv_sge = min(qp->rq.max_gs,
					min(dev->dev->caps.max_sq_sg,
					    dev->dev->caps.max_rq_sg));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_kernel_sq_size(काष्ठा mlx4_ib_dev *dev, काष्ठा ib_qp_cap *cap,
			      क्रमागत mlx4_ib_qp_type type, काष्ठा mlx4_ib_qp *qp)
अणु
	पूर्णांक s;

	/* Sanity check SQ size beक्रमe proceeding */
	अगर (cap->max_send_wr  > (dev->dev->caps.max_wqes - MLX4_IB_SQ_MAX_SPARE) ||
	    cap->max_send_sge > min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_rq_sg) ||
	    cap->max_अंतरभूत_data + send_wqe_overhead(type, qp->flags) +
	    माप (काष्ठा mlx4_wqe_अंतरभूत_seg) > dev->dev->caps.max_sq_desc_sz)
		वापस -EINVAL;

	/*
	 * For MLX transport we need 2 extra S/G entries:
	 * one क्रम the header and one क्रम the checksum at the end
	 */
	अगर ((type == MLX4_IB_QPT_SMI || type == MLX4_IB_QPT_GSI ||
	     type & (MLX4_IB_QPT_PROXY_SMI_OWNER | MLX4_IB_QPT_TUN_SMI_OWNER)) &&
	    cap->max_send_sge + 2 > dev->dev->caps.max_sq_sg)
		वापस -EINVAL;

	s = max(cap->max_send_sge * माप (काष्ठा mlx4_wqe_data_seg),
		cap->max_अंतरभूत_data + माप (काष्ठा mlx4_wqe_अंतरभूत_seg)) +
		send_wqe_overhead(type, qp->flags);

	अगर (s > dev->dev->caps.max_sq_desc_sz)
		वापस -EINVAL;

	qp->sq.wqe_shअगरt = ilog2(roundup_घात_of_two(s));

	/*
	 * We need to leave 2 KB + 1 WR of headroom in the SQ to
	 * allow HW to prefetch.
	 */
	qp->sq_spare_wqes = MLX4_IB_SQ_HEADROOM(qp->sq.wqe_shअगरt);
	qp->sq.wqe_cnt = roundup_घात_of_two(cap->max_send_wr +
					    qp->sq_spare_wqes);

	qp->sq.max_gs =
		(min(dev->dev->caps.max_sq_desc_sz,
		     (1 << qp->sq.wqe_shअगरt)) -
		 send_wqe_overhead(type, qp->flags)) /
		माप (काष्ठा mlx4_wqe_data_seg);

	qp->buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shअगरt) +
		(qp->sq.wqe_cnt << qp->sq.wqe_shअगरt);
	अगर (qp->rq.wqe_shअगरt > qp->sq.wqe_shअगरt) अणु
		qp->rq.offset = 0;
		qp->sq.offset = qp->rq.wqe_cnt << qp->rq.wqe_shअगरt;
	पूर्ण अन्यथा अणु
		qp->rq.offset = qp->sq.wqe_cnt << qp->sq.wqe_shअगरt;
		qp->sq.offset = 0;
	पूर्ण

	cap->max_send_wr  = qp->sq.max_post =
		qp->sq.wqe_cnt - qp->sq_spare_wqes;
	cap->max_send_sge = min(qp->sq.max_gs,
				min(dev->dev->caps.max_sq_sg,
				    dev->dev->caps.max_rq_sg));
	/* We करोn't support अंतरभूत sends क्रम kernel QPs (yet) */
	cap->max_अंतरभूत_data = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक set_user_sq_size(काष्ठा mlx4_ib_dev *dev,
			    काष्ठा mlx4_ib_qp *qp,
			    काष्ठा mlx4_ib_create_qp *ucmd)
अणु
	/* Sanity check SQ size beक्रमe proceeding */
	अगर ((1 << ucmd->log_sq_bb_count) > dev->dev->caps.max_wqes	 ||
	    ucmd->log_sq_stride >
		ilog2(roundup_घात_of_two(dev->dev->caps.max_sq_desc_sz)) ||
	    ucmd->log_sq_stride < MLX4_IB_MIN_SQ_STRIDE)
		वापस -EINVAL;

	qp->sq.wqe_cnt   = 1 << ucmd->log_sq_bb_count;
	qp->sq.wqe_shअगरt = ucmd->log_sq_stride;

	qp->buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shअगरt) +
		(qp->sq.wqe_cnt << qp->sq.wqe_shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_proxy_bufs(काष्ठा ib_device *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	पूर्णांक i;

	qp->sqp_proxy_rcv =
		kदो_स्मृति_array(qp->rq.wqe_cnt, माप(काष्ठा mlx4_ib_buf),
			      GFP_KERNEL);
	अगर (!qp->sqp_proxy_rcv)
		वापस -ENOMEM;
	क्रम (i = 0; i < qp->rq.wqe_cnt; i++) अणु
		qp->sqp_proxy_rcv[i].addr =
			kदो_स्मृति(माप (काष्ठा mlx4_ib_proxy_sqp_hdr),
				GFP_KERNEL);
		अगर (!qp->sqp_proxy_rcv[i].addr)
			जाओ err;
		qp->sqp_proxy_rcv[i].map =
			ib_dma_map_single(dev, qp->sqp_proxy_rcv[i].addr,
					  माप (काष्ठा mlx4_ib_proxy_sqp_hdr),
					  DMA_FROM_DEVICE);
		अगर (ib_dma_mapping_error(dev, qp->sqp_proxy_rcv[i].map)) अणु
			kमुक्त(qp->sqp_proxy_rcv[i].addr);
			जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;

err:
	जबतक (i > 0) अणु
		--i;
		ib_dma_unmap_single(dev, qp->sqp_proxy_rcv[i].map,
				    माप (काष्ठा mlx4_ib_proxy_sqp_hdr),
				    DMA_FROM_DEVICE);
		kमुक्त(qp->sqp_proxy_rcv[i].addr);
	पूर्ण
	kमुक्त(qp->sqp_proxy_rcv);
	qp->sqp_proxy_rcv = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_proxy_bufs(काष्ठा ib_device *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qp->rq.wqe_cnt; i++) अणु
		ib_dma_unmap_single(dev, qp->sqp_proxy_rcv[i].map,
				    माप (काष्ठा mlx4_ib_proxy_sqp_hdr),
				    DMA_FROM_DEVICE);
		kमुक्त(qp->sqp_proxy_rcv[i].addr);
	पूर्ण
	kमुक्त(qp->sqp_proxy_rcv);
पूर्ण

अटल bool qp_has_rq(काष्ठा ib_qp_init_attr *attr)
अणु
	अगर (attr->qp_type == IB_QPT_XRC_INI || attr->qp_type == IB_QPT_XRC_TGT)
		वापस false;

	वापस !attr->srq;
पूर्ण

अटल पूर्णांक qp0_enabled_vf(काष्ठा mlx4_dev *dev, पूर्णांक qpn)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dev->caps.num_ports; i++) अणु
		अगर (qpn == dev->caps.spec_qps[i].qp0_proxy)
			वापस !!dev->caps.spec_qps[i].qp0_qkey;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx4_ib_मुक्त_qp_counter(काष्ठा mlx4_ib_dev *dev,
				    काष्ठा mlx4_ib_qp *qp)
अणु
	mutex_lock(&dev->counters_table[qp->port - 1].mutex);
	mlx4_counter_मुक्त(dev->dev, qp->counter_index->index);
	list_del(&qp->counter_index->list);
	mutex_unlock(&dev->counters_table[qp->port - 1].mutex);

	kमुक्त(qp->counter_index);
	qp->counter_index = शून्य;
पूर्ण

अटल पूर्णांक set_qp_rss(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_rss *rss_ctx,
		      काष्ठा ib_qp_init_attr *init_attr,
		      काष्ठा mlx4_ib_create_qp_rss *ucmd)
अणु
	rss_ctx->base_qpn_tbl_sz = init_attr->rwq_ind_tbl->ind_tbl[0]->wq_num |
		(init_attr->rwq_ind_tbl->log_ind_tbl_size << 24);

	अगर ((ucmd->rx_hash_function == MLX4_IB_RX_HASH_FUNC_TOEPLITZ) &&
	    (dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_TOP)) अणु
		स_नकल(rss_ctx->rss_key, ucmd->rx_hash_key,
		       MLX4_EN_RSS_KEY_SIZE);
	पूर्ण अन्यथा अणु
		pr_debug("RX Hash function is not supported\n");
		वापस (-EOPNOTSUPP);
	पूर्ण

	अगर (ucmd->rx_hash_fields_mask & ~(MLX4_IB_RX_HASH_SRC_IPV4	|
					  MLX4_IB_RX_HASH_DST_IPV4	|
					  MLX4_IB_RX_HASH_SRC_IPV6	|
					  MLX4_IB_RX_HASH_DST_IPV6	|
					  MLX4_IB_RX_HASH_SRC_PORT_TCP	|
					  MLX4_IB_RX_HASH_DST_PORT_TCP	|
					  MLX4_IB_RX_HASH_SRC_PORT_UDP	|
					  MLX4_IB_RX_HASH_DST_PORT_UDP  |
					  MLX4_IB_RX_HASH_INNER)) अणु
		pr_debug("RX Hash fields_mask has unsupported mask (0x%llx)\n",
			 ucmd->rx_hash_fields_mask);
		वापस (-EOPNOTSUPP);
	पूर्ण

	अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV4) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV4)) अणु
		rss_ctx->flags = MLX4_RSS_IPV4;
	पूर्ण अन्यथा अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV4) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV4)) अणु
		pr_debug("RX Hash fields_mask is not supported - both IPv4 SRC and DST must be set\n");
		वापस (-EOPNOTSUPP);
	पूर्ण

	अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV6) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV6)) अणु
		rss_ctx->flags |= MLX4_RSS_IPV6;
	पूर्ण अन्यथा अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_IPV6) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_IPV6)) अणु
		pr_debug("RX Hash fields_mask is not supported - both IPv6 SRC and DST must be set\n");
		वापस (-EOPNOTSUPP);
	पूर्ण

	अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_UDP) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_UDP)) अणु
		अगर (!(dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_UDP_RSS)) अणु
			pr_debug("RX Hash fields_mask for UDP is not supported\n");
			वापस (-EOPNOTSUPP);
		पूर्ण

		अगर (rss_ctx->flags & MLX4_RSS_IPV4)
			rss_ctx->flags |= MLX4_RSS_UDP_IPV4;
		अगर (rss_ctx->flags & MLX4_RSS_IPV6)
			rss_ctx->flags |= MLX4_RSS_UDP_IPV6;
		अगर (!(rss_ctx->flags & (MLX4_RSS_IPV6 | MLX4_RSS_IPV4))) अणु
			pr_debug("RX Hash fields_mask is not supported - UDP must be set with IPv4 or IPv6\n");
			वापस (-EOPNOTSUPP);
		पूर्ण
	पूर्ण अन्यथा अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_UDP) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_UDP)) अणु
		pr_debug("RX Hash fields_mask is not supported - both UDP SRC and DST must be set\n");
		वापस (-EOPNOTSUPP);
	पूर्ण

	अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_TCP) &&
	    (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_TCP)) अणु
		अगर (rss_ctx->flags & MLX4_RSS_IPV4)
			rss_ctx->flags |= MLX4_RSS_TCP_IPV4;
		अगर (rss_ctx->flags & MLX4_RSS_IPV6)
			rss_ctx->flags |= MLX4_RSS_TCP_IPV6;
		अगर (!(rss_ctx->flags & (MLX4_RSS_IPV6 | MLX4_RSS_IPV4))) अणु
			pr_debug("RX Hash fields_mask is not supported - TCP must be set with IPv4 or IPv6\n");
			वापस (-EOPNOTSUPP);
		पूर्ण
	पूर्ण अन्यथा अगर ((ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_SRC_PORT_TCP) ||
		   (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_DST_PORT_TCP)) अणु
		pr_debug("RX Hash fields_mask is not supported - both TCP SRC and DST must be set\n");
		वापस (-EOPNOTSUPP);
	पूर्ण

	अगर (ucmd->rx_hash_fields_mask & MLX4_IB_RX_HASH_INNER) अणु
		अगर (dev->dev->caps.tunnel_offload_mode ==
		    MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) अणु
			/*
			 * Hash according to inner headers अगर exist, otherwise
			 * according to outer headers.
			 */
			rss_ctx->flags |= MLX4_RSS_BY_INNER_HEADERS_IPONLY;
		पूर्ण अन्यथा अणु
			pr_debug("RSS Hash for inner headers isn't supported\n");
			वापस (-EOPNOTSUPP);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_qp_rss(काष्ठा mlx4_ib_dev *dev,
			 काष्ठा ib_qp_init_attr *init_attr,
			 काष्ठा mlx4_ib_create_qp_rss *ucmd,
			 काष्ठा mlx4_ib_qp *qp)
अणु
	पूर्णांक qpn;
	पूर्णांक err;

	qp->mqp.usage = MLX4_RES_USAGE_USER_VERBS;

	err = mlx4_qp_reserve_range(dev->dev, 1, 1, &qpn, 0, qp->mqp.usage);
	अगर (err)
		वापस err;

	err = mlx4_qp_alloc(dev->dev, qpn, &qp->mqp);
	अगर (err)
		जाओ err_qpn;

	INIT_LIST_HEAD(&qp->gid_list);
	INIT_LIST_HEAD(&qp->steering_rules);

	qp->mlx4_ib_qp_type = MLX4_IB_QPT_RAW_PACKET;
	qp->state = IB_QPS_RESET;

	/* Set dummy send resources to be compatible with HV and PRM */
	qp->sq_no_prefetch = 1;
	qp->sq.wqe_cnt = 1;
	qp->sq.wqe_shअगरt = MLX4_IB_MIN_SQ_STRIDE;
	qp->buf_size = qp->sq.wqe_cnt << MLX4_IB_MIN_SQ_STRIDE;
	qp->mtt = (to_mqp(
		   (काष्ठा ib_qp *)init_attr->rwq_ind_tbl->ind_tbl[0]))->mtt;

	qp->rss_ctx = kzalloc(माप(*qp->rss_ctx), GFP_KERNEL);
	अगर (!qp->rss_ctx) अणु
		err = -ENOMEM;
		जाओ err_qp_alloc;
	पूर्ण

	err = set_qp_rss(dev, qp->rss_ctx, init_attr, ucmd);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	kमुक्त(qp->rss_ctx);

err_qp_alloc:
	mlx4_qp_हटाओ(dev->dev, &qp->mqp);
	mlx4_qp_मुक्त(dev->dev, &qp->mqp);

err_qpn:
	mlx4_qp_release_range(dev->dev, qpn, 1);
	वापस err;
पूर्ण

अटल पूर्णांक _mlx4_ib_create_qp_rss(काष्ठा ib_pd *pd, काष्ठा mlx4_ib_qp *qp,
				  काष्ठा ib_qp_init_attr *init_attr,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_create_qp_rss ucmd = अणुपूर्ण;
	माप_प्रकार required_cmd_sz;
	पूर्णांक err;

	अगर (!udata) अणु
		pr_debug("RSS QP with NULL udata\n");
		वापस -EINVAL;
	पूर्ण

	अगर (udata->outlen)
		वापस -EOPNOTSUPP;

	required_cmd_sz = दुरत्व(typeof(ucmd), reserved1) +
					माप(ucmd.reserved1);
	अगर (udata->inlen < required_cmd_sz) अणु
		pr_debug("invalid inlen\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ib_copy_from_udata(&ucmd, udata, min(माप(ucmd), udata->inlen))) अणु
		pr_debug("copy failed\n");
		वापस -EFAULT;
	पूर्ण

	अगर (स_प्रथम_inv(ucmd.reserved, 0, माप(ucmd.reserved)))
		वापस -EOPNOTSUPP;

	अगर (ucmd.comp_mask || ucmd.reserved1)
		वापस -EOPNOTSUPP;

	अगर (udata->inlen > माप(ucmd) &&
	    !ib_is_udata_cleared(udata, माप(ucmd),
				 udata->inlen - माप(ucmd))) अणु
		pr_debug("inlen is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->qp_type != IB_QPT_RAW_PACKET) अणु
		pr_debug("RSS QP with unsupported QP type %d\n",
			 init_attr->qp_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->create_flags) अणु
		pr_debug("RSS QP doesn't support create flags\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->send_cq || init_attr->cap.max_send_wr) अणु
		pr_debug("RSS QP with unsupported send attributes\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	qp->pri.vid = 0xFFFF;
	qp->alt.vid = 0xFFFF;

	err = create_qp_rss(to_mdev(pd->device), init_attr, &ucmd, qp);
	अगर (err)
		वापस err;

	qp->ibqp.qp_num = qp->mqp.qpn;
	वापस 0;
पूर्ण

/*
 * This function allocates a WQN from a range which is consecutive and aligned
 * to its size. In हाल the range is full, then it creates a new range and
 * allocates WQN from it. The new range will be used क्रम following allocations.
 */
अटल पूर्णांक mlx4_ib_alloc_wqn(काष्ठा mlx4_ib_ucontext *context,
			     काष्ठा mlx4_ib_qp *qp, पूर्णांक range_size, पूर्णांक *wqn)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(context->ibucontext.device);
	काष्ठा mlx4_wqn_range *range;
	पूर्णांक err = 0;

	mutex_lock(&context->wqn_ranges_mutex);

	range = list_first_entry_or_null(&context->wqn_ranges_list,
					 काष्ठा mlx4_wqn_range, list);

	अगर (!range || (range->refcount == range->size) || range->dirty) अणु
		range = kzalloc(माप(*range), GFP_KERNEL);
		अगर (!range) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = mlx4_qp_reserve_range(dev->dev, range_size,
					    range_size, &range->base_wqn, 0,
					    qp->mqp.usage);
		अगर (err) अणु
			kमुक्त(range);
			जाओ out;
		पूर्ण

		range->size = range_size;
		list_add(&range->list, &context->wqn_ranges_list);
	पूर्ण अन्यथा अगर (range_size != 1) अणु
		/*
		 * Requesting a new range (>1) when last range is still खोलो, is
		 * not valid.
		 */
		err = -EINVAL;
		जाओ out;
	पूर्ण

	qp->wqn_range = range;

	*wqn = range->base_wqn + range->refcount;

	range->refcount++;

out:
	mutex_unlock(&context->wqn_ranges_mutex);

	वापस err;
पूर्ण

अटल व्योम mlx4_ib_release_wqn(काष्ठा mlx4_ib_ucontext *context,
				काष्ठा mlx4_ib_qp *qp, bool dirty_release)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(context->ibucontext.device);
	काष्ठा mlx4_wqn_range *range;

	mutex_lock(&context->wqn_ranges_mutex);

	range = qp->wqn_range;

	range->refcount--;
	अगर (!range->refcount) अणु
		mlx4_qp_release_range(dev->dev, range->base_wqn,
				      range->size);
		list_del(&range->list);
		kमुक्त(range);
	पूर्ण अन्यथा अगर (dirty_release) अणु
	/*
	 * A range which one of its WQNs is destroyed, won't be able to be
	 * reused क्रम further WQN allocations.
	 * The next created WQ will allocate a new range.
	 */
		range->dirty = true;
	पूर्ण

	mutex_unlock(&context->wqn_ranges_mutex);
पूर्ण

अटल पूर्णांक create_rq(काष्ठा ib_pd *pd, काष्ठा ib_qp_init_attr *init_attr,
		     काष्ठा ib_udata *udata, काष्ठा mlx4_ib_qp *qp)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(pd->device);
	पूर्णांक qpn;
	पूर्णांक err;
	काष्ठा mlx4_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx4_ib_ucontext, ibucontext);
	काष्ठा mlx4_ib_cq *mcq;
	अचिन्हित दीर्घ flags;
	पूर्णांक range_size;
	काष्ठा mlx4_ib_create_wq wq;
	माप_प्रकार copy_len;
	पूर्णांक shअगरt;
	पूर्णांक n;

	qp->mlx4_ib_qp_type = MLX4_IB_QPT_RAW_PACKET;

	spin_lock_init(&qp->sq.lock);
	spin_lock_init(&qp->rq.lock);
	INIT_LIST_HEAD(&qp->gid_list);
	INIT_LIST_HEAD(&qp->steering_rules);

	qp->state = IB_QPS_RESET;

	copy_len = min(माप(काष्ठा mlx4_ib_create_wq), udata->inlen);

	अगर (ib_copy_from_udata(&wq, udata, copy_len)) अणु
		err = -EFAULT;
		जाओ err;
	पूर्ण

	अगर (wq.comp_mask || wq.reserved[0] || wq.reserved[1] ||
	    wq.reserved[2]) अणु
		pr_debug("user command isn't supported\n");
		err = -EOPNOTSUPP;
		जाओ err;
	पूर्ण

	अगर (wq.log_range_size > ilog2(dev->dev->caps.max_rss_tbl_sz)) अणु
		pr_debug("WQN range size must be equal or smaller than %d\n",
			 dev->dev->caps.max_rss_tbl_sz);
		err = -EOPNOTSUPP;
		जाओ err;
	पूर्ण
	range_size = 1 << wq.log_range_size;

	अगर (init_attr->create_flags & IB_QP_CREATE_SCATTER_FCS)
		qp->flags |= MLX4_IB_QP_SCATTER_FCS;

	err = set_rq_size(dev, &init_attr->cap, true, true, qp, qp->inl_recv_sz);
	अगर (err)
		जाओ err;

	qp->sq_no_prefetch = 1;
	qp->sq.wqe_cnt = 1;
	qp->sq.wqe_shअगरt = MLX4_IB_MIN_SQ_STRIDE;
	qp->buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shअगरt) +
		       (qp->sq.wqe_cnt << qp->sq.wqe_shअगरt);

	qp->umem = ib_umem_get(pd->device, wq.buf_addr, qp->buf_size, 0);
	अगर (IS_ERR(qp->umem)) अणु
		err = PTR_ERR(qp->umem);
		जाओ err;
	पूर्ण

	shअगरt = mlx4_ib_umem_calc_optimal_mtt_size(qp->umem, 0, &n);
	err = mlx4_mtt_init(dev->dev, n, shअगरt, &qp->mtt);

	अगर (err)
		जाओ err_buf;

	err = mlx4_ib_umem_ग_लिखो_mtt(dev, &qp->mtt, qp->umem);
	अगर (err)
		जाओ err_mtt;

	err = mlx4_ib_db_map_user(udata, wq.db_addr, &qp->db);
	अगर (err)
		जाओ err_mtt;
	qp->mqp.usage = MLX4_RES_USAGE_USER_VERBS;

	err = mlx4_ib_alloc_wqn(context, qp, range_size, &qpn);
	अगर (err)
		जाओ err_wrid;

	err = mlx4_qp_alloc(dev->dev, qpn, &qp->mqp);
	अगर (err)
		जाओ err_qpn;

	/*
	 * Hardware wants QPN written in big-endian order (after
	 * shअगरting) क्रम send करोorbell.  Precompute this value to save
	 * a little bit when posting sends.
	 */
	qp->करोorbell_qpn = swab32(qp->mqp.qpn << 8);

	qp->mqp.event = mlx4_ib_wq_event;

	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx4_ib_lock_cqs(to_mcq(init_attr->send_cq),
			 to_mcq(init_attr->recv_cq));
	/* Maपूर्णांकain device to QPs access, needed क्रम further handling
	 * via reset flow
	 */
	list_add_tail(&qp->qps_list, &dev->qp_list);
	/* Maपूर्णांकain CQ to QPs access, needed क्रम further handling
	 * via reset flow
	 */
	mcq = to_mcq(init_attr->send_cq);
	list_add_tail(&qp->cq_send_list, &mcq->send_qp_list);
	mcq = to_mcq(init_attr->recv_cq);
	list_add_tail(&qp->cq_recv_list, &mcq->recv_qp_list);
	mlx4_ib_unlock_cqs(to_mcq(init_attr->send_cq),
			   to_mcq(init_attr->recv_cq));
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);
	वापस 0;

err_qpn:
	mlx4_ib_release_wqn(context, qp, 0);
err_wrid:
	mlx4_ib_db_unmap_user(context, &qp->db);

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &qp->mtt);
err_buf:
	ib_umem_release(qp->umem);
err:
	वापस err;
पूर्ण

अटल पूर्णांक create_qp_common(काष्ठा ib_pd *pd, काष्ठा ib_qp_init_attr *init_attr,
			    काष्ठा ib_udata *udata, पूर्णांक sqpn,
			    काष्ठा mlx4_ib_qp *qp)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(pd->device);
	पूर्णांक qpn;
	पूर्णांक err;
	काष्ठा mlx4_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx4_ib_ucontext, ibucontext);
	क्रमागत mlx4_ib_qp_type qp_type = (क्रमागत mlx4_ib_qp_type) init_attr->qp_type;
	काष्ठा mlx4_ib_cq *mcq;
	अचिन्हित दीर्घ flags;

	/* When tunneling special qps, we use a plain UD qp */
	अगर (sqpn) अणु
		अगर (mlx4_is_mfunc(dev->dev) &&
		    (!mlx4_is_master(dev->dev) ||
		     !(init_attr->create_flags & MLX4_IB_SRIOV_SQP))) अणु
			अगर (init_attr->qp_type == IB_QPT_GSI)
				qp_type = MLX4_IB_QPT_PROXY_GSI;
			अन्यथा अणु
				अगर (mlx4_is_master(dev->dev) ||
				    qp0_enabled_vf(dev->dev, sqpn))
					qp_type = MLX4_IB_QPT_PROXY_SMI_OWNER;
				अन्यथा
					qp_type = MLX4_IB_QPT_PROXY_SMI;
			पूर्ण
		पूर्ण
		qpn = sqpn;
		/* add extra sg entry क्रम tunneling */
		init_attr->cap.max_recv_sge++;
	पूर्ण अन्यथा अगर (init_attr->create_flags & MLX4_IB_SRIOV_TUNNEL_QP) अणु
		काष्ठा mlx4_ib_qp_tunnel_init_attr *tnl_init =
			container_of(init_attr,
				     काष्ठा mlx4_ib_qp_tunnel_init_attr, init_attr);
		अगर ((tnl_init->proxy_qp_type != IB_QPT_SMI &&
		     tnl_init->proxy_qp_type != IB_QPT_GSI)   ||
		    !mlx4_is_master(dev->dev))
			वापस -EINVAL;
		अगर (tnl_init->proxy_qp_type == IB_QPT_GSI)
			qp_type = MLX4_IB_QPT_TUN_GSI;
		अन्यथा अगर (tnl_init->slave == mlx4_master_func_num(dev->dev) ||
			 mlx4_vf_smi_enabled(dev->dev, tnl_init->slave,
					     tnl_init->port))
			qp_type = MLX4_IB_QPT_TUN_SMI_OWNER;
		अन्यथा
			qp_type = MLX4_IB_QPT_TUN_SMI;
		/* we are definitely in the PPF here, since we are creating
		 * tunnel QPs. base_tunnel_sqpn is thereक्रमe valid. */
		qpn = dev->dev->phys_caps.base_tunnel_sqpn + 8 * tnl_init->slave
			+ tnl_init->proxy_qp_type * 2 + tnl_init->port - 1;
		sqpn = qpn;
	पूर्ण

	अगर (init_attr->qp_type == IB_QPT_SMI ||
	    init_attr->qp_type == IB_QPT_GSI || qp_type == MLX4_IB_QPT_SMI ||
	    qp_type == MLX4_IB_QPT_GSI ||
	    (qp_type & (MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_SMI_OWNER |
			MLX4_IB_QPT_PROXY_GSI | MLX4_IB_QPT_TUN_SMI_OWNER))) अणु
		qp->sqp = kzalloc(माप(काष्ठा mlx4_ib_sqp), GFP_KERNEL);
		अगर (!qp->sqp)
			वापस -ENOMEM;
	पूर्ण

	qp->mlx4_ib_qp_type = qp_type;

	spin_lock_init(&qp->sq.lock);
	spin_lock_init(&qp->rq.lock);
	INIT_LIST_HEAD(&qp->gid_list);
	INIT_LIST_HEAD(&qp->steering_rules);

	qp->state = IB_QPS_RESET;
	अगर (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		qp->sq_संकेत_bits = cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE);

	अगर (udata) अणु
		काष्ठा mlx4_ib_create_qp ucmd;
		माप_प्रकार copy_len;
		पूर्णांक shअगरt;
		पूर्णांक n;

		copy_len = माप(काष्ठा mlx4_ib_create_qp);

		अगर (ib_copy_from_udata(&ucmd, udata, copy_len)) अणु
			err = -EFAULT;
			जाओ err;
		पूर्ण

		qp->inl_recv_sz = ucmd.inl_recv_sz;

		अगर (init_attr->create_flags & IB_QP_CREATE_SCATTER_FCS) अणु
			अगर (!(dev->dev->caps.flags &
			      MLX4_DEV_CAP_FLAG_FCS_KEEP)) अणु
				pr_debug("scatter FCS is unsupported\n");
				err = -EOPNOTSUPP;
				जाओ err;
			पूर्ण

			qp->flags |= MLX4_IB_QP_SCATTER_FCS;
		पूर्ण

		err = set_rq_size(dev, &init_attr->cap, udata,
				  qp_has_rq(init_attr), qp, qp->inl_recv_sz);
		अगर (err)
			जाओ err;

		qp->sq_no_prefetch = ucmd.sq_no_prefetch;

		err = set_user_sq_size(dev, qp, &ucmd);
		अगर (err)
			जाओ err;

		qp->umem =
			ib_umem_get(pd->device, ucmd.buf_addr, qp->buf_size, 0);
		अगर (IS_ERR(qp->umem)) अणु
			err = PTR_ERR(qp->umem);
			जाओ err;
		पूर्ण

		shअगरt = mlx4_ib_umem_calc_optimal_mtt_size(qp->umem, 0, &n);
		err = mlx4_mtt_init(dev->dev, n, shअगरt, &qp->mtt);

		अगर (err)
			जाओ err_buf;

		err = mlx4_ib_umem_ग_लिखो_mtt(dev, &qp->mtt, qp->umem);
		अगर (err)
			जाओ err_mtt;

		अगर (qp_has_rq(init_attr)) अणु
			err = mlx4_ib_db_map_user(udata, ucmd.db_addr, &qp->db);
			अगर (err)
				जाओ err_mtt;
		पूर्ण
		qp->mqp.usage = MLX4_RES_USAGE_USER_VERBS;
	पूर्ण अन्यथा अणु
		err = set_rq_size(dev, &init_attr->cap, udata,
				  qp_has_rq(init_attr), qp, 0);
		अगर (err)
			जाओ err;

		qp->sq_no_prefetch = 0;

		अगर (init_attr->create_flags & IB_QP_CREATE_IPOIB_UD_LSO)
			qp->flags |= MLX4_IB_QP_LSO;

		अगर (init_attr->create_flags & IB_QP_CREATE_NETIF_QP) अणु
			अगर (dev->steering_support ==
			    MLX4_STEERING_MODE_DEVICE_MANAGED)
				qp->flags |= MLX4_IB_QP_NETIF;
			अन्यथा
				जाओ err;
		पूर्ण

		err = set_kernel_sq_size(dev, &init_attr->cap, qp_type, qp);
		अगर (err)
			जाओ err;

		अगर (qp_has_rq(init_attr)) अणु
			err = mlx4_db_alloc(dev->dev, &qp->db, 0);
			अगर (err)
				जाओ err;

			*qp->db.db = 0;
		पूर्ण

		अगर (mlx4_buf_alloc(dev->dev, qp->buf_size,  PAGE_SIZE * 2,
				   &qp->buf)) अणु
			err = -ENOMEM;
			जाओ err_db;
		पूर्ण

		err = mlx4_mtt_init(dev->dev, qp->buf.npages, qp->buf.page_shअगरt,
				    &qp->mtt);
		अगर (err)
			जाओ err_buf;

		err = mlx4_buf_ग_लिखो_mtt(dev->dev, &qp->mtt, &qp->buf);
		अगर (err)
			जाओ err_mtt;

		qp->sq.wrid = kvदो_स्मृति_array(qp->sq.wqe_cnt,
					     माप(u64), GFP_KERNEL);
		qp->rq.wrid = kvदो_स्मृति_array(qp->rq.wqe_cnt,
					     माप(u64), GFP_KERNEL);
		अगर (!qp->sq.wrid || !qp->rq.wrid) अणु
			err = -ENOMEM;
			जाओ err_wrid;
		पूर्ण
		qp->mqp.usage = MLX4_RES_USAGE_DRIVER;
	पूर्ण

	अगर (sqpn) अणु
		अगर (qp->mlx4_ib_qp_type & (MLX4_IB_QPT_PROXY_SMI_OWNER |
		    MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_GSI)) अणु
			अगर (alloc_proxy_bufs(pd->device, qp)) अणु
				err = -ENOMEM;
				जाओ err_wrid;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Raw packet QPNs may not have bits 6,7 set in their qp_num;
		 * otherwise, the WQE BlueFlame setup flow wrongly causes
		 * VLAN insertion. */
		अगर (init_attr->qp_type == IB_QPT_RAW_PACKET)
			err = mlx4_qp_reserve_range(dev->dev, 1, 1, &qpn,
						    (init_attr->cap.max_send_wr ?
						     MLX4_RESERVE_ETH_BF_QP : 0) |
						    (init_attr->cap.max_recv_wr ?
						     MLX4_RESERVE_A0_QP : 0),
						    qp->mqp.usage);
		अन्यथा
			अगर (qp->flags & MLX4_IB_QP_NETIF)
				err = mlx4_ib_steer_qp_alloc(dev, 1, &qpn);
			अन्यथा
				err = mlx4_qp_reserve_range(dev->dev, 1, 1,
							    &qpn, 0, qp->mqp.usage);
		अगर (err)
			जाओ err_proxy;
	पूर्ण

	अगर (init_attr->create_flags & IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK)
		qp->flags |= MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK;

	err = mlx4_qp_alloc(dev->dev, qpn, &qp->mqp);
	अगर (err)
		जाओ err_qpn;

	अगर (init_attr->qp_type == IB_QPT_XRC_TGT)
		qp->mqp.qpn |= (1 << 23);

	/*
	 * Hardware wants QPN written in big-endian order (after
	 * shअगरting) क्रम send करोorbell.  Precompute this value to save
	 * a little bit when posting sends.
	 */
	qp->करोorbell_qpn = swab32(qp->mqp.qpn << 8);

	qp->mqp.event = mlx4_ib_qp_event;

	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx4_ib_lock_cqs(to_mcq(init_attr->send_cq),
			 to_mcq(init_attr->recv_cq));
	/* Maपूर्णांकain device to QPs access, needed क्रम further handling
	 * via reset flow
	 */
	list_add_tail(&qp->qps_list, &dev->qp_list);
	/* Maपूर्णांकain CQ to QPs access, needed क्रम further handling
	 * via reset flow
	 */
	mcq = to_mcq(init_attr->send_cq);
	list_add_tail(&qp->cq_send_list, &mcq->send_qp_list);
	mcq = to_mcq(init_attr->recv_cq);
	list_add_tail(&qp->cq_recv_list, &mcq->recv_qp_list);
	mlx4_ib_unlock_cqs(to_mcq(init_attr->send_cq),
			   to_mcq(init_attr->recv_cq));
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);
	वापस 0;

err_qpn:
	अगर (!sqpn) अणु
		अगर (qp->flags & MLX4_IB_QP_NETIF)
			mlx4_ib_steer_qp_मुक्त(dev, qpn, 1);
		अन्यथा
			mlx4_qp_release_range(dev->dev, qpn, 1);
	पूर्ण
err_proxy:
	अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_PROXY_GSI)
		मुक्त_proxy_bufs(pd->device, qp);
err_wrid:
	अगर (udata) अणु
		अगर (qp_has_rq(init_attr))
			mlx4_ib_db_unmap_user(context, &qp->db);
	पूर्ण अन्यथा अणु
		kvमुक्त(qp->sq.wrid);
		kvमुक्त(qp->rq.wrid);
	पूर्ण

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &qp->mtt);

err_buf:
	अगर (!qp->umem)
		mlx4_buf_मुक्त(dev->dev, qp->buf_size, &qp->buf);
	ib_umem_release(qp->umem);

err_db:
	अगर (!udata && qp_has_rq(init_attr))
		mlx4_db_मुक्त(dev->dev, &qp->db);

err:
	kमुक्त(qp->sqp);
	वापस err;
पूर्ण

अटल क्रमागत mlx4_qp_state to_mlx4_state(क्रमागत ib_qp_state state)
अणु
	चयन (state) अणु
	हाल IB_QPS_RESET:	वापस MLX4_QP_STATE_RST;
	हाल IB_QPS_INIT:	वापस MLX4_QP_STATE_INIT;
	हाल IB_QPS_RTR:	वापस MLX4_QP_STATE_RTR;
	हाल IB_QPS_RTS:	वापस MLX4_QP_STATE_RTS;
	हाल IB_QPS_SQD:	वापस MLX4_QP_STATE_SQD;
	हाल IB_QPS_SQE:	वापस MLX4_QP_STATE_SQER;
	हाल IB_QPS_ERR:	वापस MLX4_QP_STATE_ERR;
	शेष:		वापस -1;
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_lock_cqs(काष्ठा mlx4_ib_cq *send_cq, काष्ठा mlx4_ib_cq *recv_cq)
	__acquires(&send_cq->lock) __acquires(&recv_cq->lock)
अणु
	अगर (send_cq == recv_cq) अणु
		spin_lock(&send_cq->lock);
		__acquire(&recv_cq->lock);
	पूर्ण अन्यथा अगर (send_cq->mcq.cqn < recv_cq->mcq.cqn) अणु
		spin_lock(&send_cq->lock);
		spin_lock_nested(&recv_cq->lock, SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु
		spin_lock(&recv_cq->lock);
		spin_lock_nested(&send_cq->lock, SINGLE_DEPTH_NESTING);
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_unlock_cqs(काष्ठा mlx4_ib_cq *send_cq, काष्ठा mlx4_ib_cq *recv_cq)
	__releases(&send_cq->lock) __releases(&recv_cq->lock)
अणु
	अगर (send_cq == recv_cq) अणु
		__release(&recv_cq->lock);
		spin_unlock(&send_cq->lock);
	पूर्ण अन्यथा अगर (send_cq->mcq.cqn < recv_cq->mcq.cqn) अणु
		spin_unlock(&recv_cq->lock);
		spin_unlock(&send_cq->lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&send_cq->lock);
		spin_unlock(&recv_cq->lock);
	पूर्ण
पूर्ण

अटल व्योम del_gid_entries(काष्ठा mlx4_ib_qp *qp)
अणु
	काष्ठा mlx4_ib_gid_entry *ge, *पंचांगp;

	list_क्रम_each_entry_safe(ge, पंचांगp, &qp->gid_list, list) अणु
		list_del(&ge->list);
		kमुक्त(ge);
	पूर्ण
पूर्ण

अटल काष्ठा mlx4_ib_pd *get_pd(काष्ठा mlx4_ib_qp *qp)
अणु
	अगर (qp->ibqp.qp_type == IB_QPT_XRC_TGT)
		वापस to_mpd(to_mxrcd(qp->ibqp.xrcd)->pd);
	अन्यथा
		वापस to_mpd(qp->ibqp.pd);
पूर्ण

अटल व्योम get_cqs(काष्ठा mlx4_ib_qp *qp, क्रमागत mlx4_ib_source_type src,
		    काष्ठा mlx4_ib_cq **send_cq, काष्ठा mlx4_ib_cq **recv_cq)
अणु
	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_XRC_TGT:
		*send_cq = to_mcq(to_mxrcd(qp->ibqp.xrcd)->cq);
		*recv_cq = *send_cq;
		अवरोध;
	हाल IB_QPT_XRC_INI:
		*send_cq = to_mcq(qp->ibqp.send_cq);
		*recv_cq = *send_cq;
		अवरोध;
	शेष:
		*recv_cq = (src == MLX4_IB_QP_SRC) ? to_mcq(qp->ibqp.recv_cq) :
						     to_mcq(qp->ibwq.cq);
		*send_cq = (src == MLX4_IB_QP_SRC) ? to_mcq(qp->ibqp.send_cq) :
						     *recv_cq;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम destroy_qp_rss(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	अगर (qp->state != IB_QPS_RESET) अणु
		पूर्णांक i;

		क्रम (i = 0; i < (1 << qp->ibqp.rwq_ind_tbl->log_ind_tbl_size);
		     i++) अणु
			काष्ठा ib_wq *ibwq = qp->ibqp.rwq_ind_tbl->ind_tbl[i];
			काष्ठा mlx4_ib_qp *wq =	to_mqp((काष्ठा ib_qp *)ibwq);

			mutex_lock(&wq->mutex);

			wq->rss_usecnt--;

			mutex_unlock(&wq->mutex);
		पूर्ण

		अगर (mlx4_qp_modअगरy(dev->dev, शून्य, to_mlx4_state(qp->state),
				   MLX4_QP_STATE_RST, शून्य, 0, 0, &qp->mqp))
			pr_warn("modify QP %06x to RESET failed.\n",
				qp->mqp.qpn);
	पूर्ण

	mlx4_qp_हटाओ(dev->dev, &qp->mqp);
	mlx4_qp_मुक्त(dev->dev, &qp->mqp);
	mlx4_qp_release_range(dev->dev, qp->mqp.qpn, 1);
	del_gid_entries(qp);
पूर्ण

अटल व्योम destroy_qp_common(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp,
			      क्रमागत mlx4_ib_source_type src,
			      काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_cq *send_cq, *recv_cq;
	अचिन्हित दीर्घ flags;

	अगर (qp->state != IB_QPS_RESET) अणु
		अगर (mlx4_qp_modअगरy(dev->dev, शून्य, to_mlx4_state(qp->state),
				   MLX4_QP_STATE_RST, शून्य, 0, 0, &qp->mqp))
			pr_warn("modify QP %06x to RESET failed.\n",
			       qp->mqp.qpn);
		अगर (qp->pri.smac || (!qp->pri.smac && qp->pri.smac_port)) अणु
			mlx4_unरेजिस्टर_mac(dev->dev, qp->pri.smac_port, qp->pri.smac);
			qp->pri.smac = 0;
			qp->pri.smac_port = 0;
		पूर्ण
		अगर (qp->alt.smac) अणु
			mlx4_unरेजिस्टर_mac(dev->dev, qp->alt.smac_port, qp->alt.smac);
			qp->alt.smac = 0;
		पूर्ण
		अगर (qp->pri.vid < 0x1000) अणु
			mlx4_unरेजिस्टर_vlan(dev->dev, qp->pri.vlan_port, qp->pri.vid);
			qp->pri.vid = 0xFFFF;
			qp->pri.candidate_vid = 0xFFFF;
			qp->pri.update_vid = 0;
		पूर्ण
		अगर (qp->alt.vid < 0x1000) अणु
			mlx4_unरेजिस्टर_vlan(dev->dev, qp->alt.vlan_port, qp->alt.vid);
			qp->alt.vid = 0xFFFF;
			qp->alt.candidate_vid = 0xFFFF;
			qp->alt.update_vid = 0;
		पूर्ण
	पूर्ण

	get_cqs(qp, src, &send_cq, &recv_cq);

	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx4_ib_lock_cqs(send_cq, recv_cq);

	/* del from lists under both locks above to protect reset flow paths */
	list_del(&qp->qps_list);
	list_del(&qp->cq_send_list);
	list_del(&qp->cq_recv_list);
	अगर (!udata) अणु
		__mlx4_ib_cq_clean(recv_cq, qp->mqp.qpn,
				 qp->ibqp.srq ? to_msrq(qp->ibqp.srq): शून्य);
		अगर (send_cq != recv_cq)
			__mlx4_ib_cq_clean(send_cq, qp->mqp.qpn, शून्य);
	पूर्ण

	mlx4_qp_हटाओ(dev->dev, &qp->mqp);

	mlx4_ib_unlock_cqs(send_cq, recv_cq);
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

	mlx4_qp_मुक्त(dev->dev, &qp->mqp);

	अगर (!is_sqp(dev, qp) && !is_tunnel_qp(dev, qp)) अणु
		अगर (qp->flags & MLX4_IB_QP_NETIF)
			mlx4_ib_steer_qp_मुक्त(dev, qp->mqp.qpn, 1);
		अन्यथा अगर (src == MLX4_IB_RWQ_SRC)
			mlx4_ib_release_wqn(
				rdma_udata_to_drv_context(
					udata,
					काष्ठा mlx4_ib_ucontext,
					ibucontext),
				qp, 1);
		अन्यथा
			mlx4_qp_release_range(dev->dev, qp->mqp.qpn, 1);
	पूर्ण

	mlx4_mtt_cleanup(dev->dev, &qp->mtt);

	अगर (udata) अणु
		अगर (qp->rq.wqe_cnt) अणु
			काष्ठा mlx4_ib_ucontext *mcontext =
				rdma_udata_to_drv_context(
					udata,
					काष्ठा mlx4_ib_ucontext,
					ibucontext);

			mlx4_ib_db_unmap_user(mcontext, &qp->db);
		पूर्ण
	पूर्ण अन्यथा अणु
		kvमुक्त(qp->sq.wrid);
		kvमुक्त(qp->rq.wrid);
		अगर (qp->mlx4_ib_qp_type & (MLX4_IB_QPT_PROXY_SMI_OWNER |
		    MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_GSI))
			मुक्त_proxy_bufs(&dev->ib_dev, qp);
		mlx4_buf_मुक्त(dev->dev, qp->buf_size, &qp->buf);
		अगर (qp->rq.wqe_cnt)
			mlx4_db_मुक्त(dev->dev, &qp->db);
	पूर्ण
	ib_umem_release(qp->umem);

	del_gid_entries(qp);
पूर्ण

अटल u32 get_sqp_num(काष्ठा mlx4_ib_dev *dev, काष्ठा ib_qp_init_attr *attr)
अणु
	/* Native or PPF */
	अगर (!mlx4_is_mfunc(dev->dev) ||
	    (mlx4_is_master(dev->dev) &&
	     attr->create_flags & MLX4_IB_SRIOV_SQP)) अणु
		वापस  dev->dev->phys_caps.base_sqpn +
			(attr->qp_type == IB_QPT_SMI ? 0 : 2) +
			attr->port_num - 1;
	पूर्ण
	/* PF or VF -- creating proxies */
	अगर (attr->qp_type == IB_QPT_SMI)
		वापस dev->dev->caps.spec_qps[attr->port_num - 1].qp0_proxy;
	अन्यथा
		वापस dev->dev->caps.spec_qps[attr->port_num - 1].qp1_proxy;
पूर्ण

अटल पूर्णांक _mlx4_ib_create_qp(काष्ठा ib_pd *pd, काष्ठा mlx4_ib_qp *qp,
			      काष्ठा ib_qp_init_attr *init_attr,
			      काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	पूर्णांक sup_u_create_flags = MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK;
	u16 xrcdn = 0;

	अगर (init_attr->rwq_ind_tbl)
		वापस _mlx4_ib_create_qp_rss(pd, qp, init_attr, udata);

	/*
	 * We only support LSO, venकरोr flag1, and multicast loopback blocking,
	 * and only क्रम kernel UD QPs.
	 */
	अगर (init_attr->create_flags & ~(MLX4_IB_QP_LSO |
					MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK |
					MLX4_IB_SRIOV_TUNNEL_QP |
					MLX4_IB_SRIOV_SQP |
					MLX4_IB_QP_NETIF |
					MLX4_IB_QP_CREATE_ROCE_V2_GSI))
		वापस -EOPNOTSUPP;

	अगर (init_attr->create_flags & IB_QP_CREATE_NETIF_QP) अणु
		अगर (init_attr->qp_type != IB_QPT_UD)
			वापस -EINVAL;
	पूर्ण

	अगर (init_attr->create_flags) अणु
		अगर (udata && init_attr->create_flags & ~(sup_u_create_flags))
			वापस -EINVAL;

		अगर ((init_attr->create_flags & ~(MLX4_IB_SRIOV_SQP |
						 MLX4_IB_QP_CREATE_ROCE_V2_GSI  |
						 MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK) &&
		     init_attr->qp_type != IB_QPT_UD) ||
		    (init_attr->create_flags & MLX4_IB_SRIOV_SQP &&
		     init_attr->qp_type > IB_QPT_GSI) ||
		    (init_attr->create_flags & MLX4_IB_QP_CREATE_ROCE_V2_GSI &&
		     init_attr->qp_type != IB_QPT_GSI))
			वापस -EINVAL;
	पूर्ण

	चयन (init_attr->qp_type) अणु
	हाल IB_QPT_XRC_TGT:
		pd = to_mxrcd(init_attr->xrcd)->pd;
		xrcdn = to_mxrcd(init_attr->xrcd)->xrcdn;
		init_attr->send_cq = to_mxrcd(init_attr->xrcd)->cq;
		fallthrough;
	हाल IB_QPT_XRC_INI:
		अगर (!(to_mdev(pd->device)->dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC))
			वापस -ENOSYS;
		init_attr->recv_cq = init_attr->send_cq;
		fallthrough;
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
	हाल IB_QPT_RAW_PACKET:
	हाल IB_QPT_UD:
		qp->pri.vid = 0xFFFF;
		qp->alt.vid = 0xFFFF;
		err = create_qp_common(pd, init_attr, udata, 0, qp);
		अगर (err)
			वापस err;

		qp->ibqp.qp_num = qp->mqp.qpn;
		qp->xrcdn = xrcdn;
		अवरोध;
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
	अणु
		पूर्णांक sqpn;

		अगर (init_attr->create_flags & MLX4_IB_QP_CREATE_ROCE_V2_GSI) अणु
			पूर्णांक res = mlx4_qp_reserve_range(to_mdev(pd->device)->dev,
							1, 1, &sqpn, 0,
							MLX4_RES_USAGE_DRIVER);

			अगर (res)
				वापस res;
		पूर्ण अन्यथा अणु
			sqpn = get_sqp_num(to_mdev(pd->device), init_attr);
		पूर्ण

		qp->pri.vid = 0xFFFF;
		qp->alt.vid = 0xFFFF;
		err = create_qp_common(pd, init_attr, udata, sqpn, qp);
		अगर (err)
			वापस err;

		अगर (init_attr->create_flags &
		    (MLX4_IB_SRIOV_SQP | MLX4_IB_SRIOV_TUNNEL_QP))
			/* Internal QP created with ib_create_qp */
			rdma_restrack_no_track(&qp->ibqp.res);

		qp->port	= init_attr->port_num;
		qp->ibqp.qp_num = init_attr->qp_type == IB_QPT_SMI ? 0 :
			init_attr->create_flags & MLX4_IB_QP_CREATE_ROCE_V2_GSI ? sqpn : 1;
		अवरोध;
	पूर्ण
	शेष:
		/* Don't support raw QPs */
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा ib_qp *mlx4_ib_create_qp(काष्ठा ib_pd *pd,
				काष्ठा ib_qp_init_attr *init_attr,
				काष्ठा ib_udata *udata) अणु
	काष्ठा ib_device *device = pd ? pd->device : init_attr->xrcd->device;
	काष्ठा mlx4_ib_dev *dev = to_mdev(device);
	काष्ठा mlx4_ib_qp *qp;
	पूर्णांक ret;

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&qp->mutex);
	ret = _mlx4_ib_create_qp(pd, qp, init_attr, udata);
	अगर (ret) अणु
		kमुक्त(qp);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (init_attr->qp_type == IB_QPT_GSI &&
	    !(init_attr->create_flags & MLX4_IB_QP_CREATE_ROCE_V2_GSI)) अणु
		काष्ठा mlx4_ib_sqp *sqp = qp->sqp;
		पूर्णांक is_eth = rdma_cap_eth_ah(&dev->ib_dev, init_attr->port_num);

		अगर (is_eth &&
		    dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2) अणु
			init_attr->create_flags |= MLX4_IB_QP_CREATE_ROCE_V2_GSI;
			sqp->roce_v2_gsi = ib_create_qp(pd, init_attr);

			अगर (IS_ERR(sqp->roce_v2_gsi)) अणु
				pr_err("Failed to create GSI QP for RoCEv2 (%ld)\n", PTR_ERR(sqp->roce_v2_gsi));
				sqp->roce_v2_gsi = शून्य;
			पूर्ण अन्यथा अणु
				to_mqp(sqp->roce_v2_gsi)->flags |=
					MLX4_IB_ROCE_V2_GSI_QP;
			पूर्ण

			init_attr->create_flags &= ~MLX4_IB_QP_CREATE_ROCE_V2_GSI;
		पूर्ण
	पूर्ण
	वापस &qp->ibqp;
पूर्ण

अटल पूर्णांक _mlx4_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx4_ib_qp *mqp = to_mqp(qp);

	अगर (is_qp0(dev, mqp))
		mlx4_CLOSE_PORT(dev->dev, mqp->port);

	अगर (mqp->mlx4_ib_qp_type == MLX4_IB_QPT_PROXY_GSI &&
	    dev->qp1_proxy[mqp->port - 1] == mqp) अणु
		mutex_lock(&dev->qp1_proxy_lock[mqp->port - 1]);
		dev->qp1_proxy[mqp->port - 1] = शून्य;
		mutex_unlock(&dev->qp1_proxy_lock[mqp->port - 1]);
	पूर्ण

	अगर (mqp->counter_index)
		mlx4_ib_मुक्त_qp_counter(dev, mqp);

	अगर (qp->rwq_ind_tbl) अणु
		destroy_qp_rss(dev, mqp);
	पूर्ण अन्यथा अणु
		destroy_qp_common(dev, mqp, MLX4_IB_QP_SRC, udata);
	पूर्ण

	kमुक्त(mqp->sqp);
	kमुक्त(mqp);

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_qp *mqp = to_mqp(qp);

	अगर (mqp->mlx4_ib_qp_type == MLX4_IB_QPT_GSI) अणु
		काष्ठा mlx4_ib_sqp *sqp = mqp->sqp;

		अगर (sqp->roce_v2_gsi)
			ib_destroy_qp(sqp->roce_v2_gsi);
	पूर्ण

	वापस _mlx4_ib_destroy_qp(qp, udata);
पूर्ण

अटल पूर्णांक to_mlx4_st(काष्ठा mlx4_ib_dev *dev, क्रमागत mlx4_ib_qp_type type)
अणु
	चयन (type) अणु
	हाल MLX4_IB_QPT_RC:		वापस MLX4_QP_ST_RC;
	हाल MLX4_IB_QPT_UC:		वापस MLX4_QP_ST_UC;
	हाल MLX4_IB_QPT_UD:		वापस MLX4_QP_ST_UD;
	हाल MLX4_IB_QPT_XRC_INI:
	हाल MLX4_IB_QPT_XRC_TGT:	वापस MLX4_QP_ST_XRC;
	हाल MLX4_IB_QPT_SMI:
	हाल MLX4_IB_QPT_GSI:
	हाल MLX4_IB_QPT_RAW_PACKET:	वापस MLX4_QP_ST_MLX;

	हाल MLX4_IB_QPT_PROXY_SMI_OWNER:
	हाल MLX4_IB_QPT_TUN_SMI_OWNER:	वापस (mlx4_is_mfunc(dev->dev) ?
						MLX4_QP_ST_MLX : -1);
	हाल MLX4_IB_QPT_PROXY_SMI:
	हाल MLX4_IB_QPT_TUN_SMI:
	हाल MLX4_IB_QPT_PROXY_GSI:
	हाल MLX4_IB_QPT_TUN_GSI:	वापस (mlx4_is_mfunc(dev->dev) ?
						MLX4_QP_ST_UD : -1);
	शेष:			वापस -1;
	पूर्ण
पूर्ण

अटल __be32 to_mlx4_access_flags(काष्ठा mlx4_ib_qp *qp, स्थिर काष्ठा ib_qp_attr *attr,
				   पूर्णांक attr_mask)
अणु
	u8 dest_rd_atomic;
	u32 access_flags;
	u32 hw_access_flags = 0;

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		dest_rd_atomic = attr->max_dest_rd_atomic;
	अन्यथा
		dest_rd_atomic = qp->resp_depth;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		access_flags = attr->qp_access_flags;
	अन्यथा
		access_flags = qp->atomic_rd_en;

	अगर (!dest_rd_atomic)
		access_flags &= IB_ACCESS_REMOTE_WRITE;

	अगर (access_flags & IB_ACCESS_REMOTE_READ)
		hw_access_flags |= MLX4_QP_BIT_RRE;
	अगर (access_flags & IB_ACCESS_REMOTE_ATOMIC)
		hw_access_flags |= MLX4_QP_BIT_RAE;
	अगर (access_flags & IB_ACCESS_REMOTE_WRITE)
		hw_access_flags |= MLX4_QP_BIT_RWE;

	वापस cpu_to_be32(hw_access_flags);
पूर्ण

अटल व्योम store_sqp_attrs(काष्ठा mlx4_ib_sqp *sqp, स्थिर काष्ठा ib_qp_attr *attr,
			    पूर्णांक attr_mask)
अणु
	अगर (attr_mask & IB_QP_PKEY_INDEX)
		sqp->pkey_index = attr->pkey_index;
	अगर (attr_mask & IB_QP_QKEY)
		sqp->qkey = attr->qkey;
	अगर (attr_mask & IB_QP_SQ_PSN)
		sqp->send_psn = attr->sq_psn;
पूर्ण

अटल व्योम mlx4_set_sched(काष्ठा mlx4_qp_path *path, u8 port)
अणु
	path->sched_queue = (path->sched_queue & 0xbf) | ((port - 1) << 6);
पूर्ण

अटल पूर्णांक _mlx4_set_path(काष्ठा mlx4_ib_dev *dev,
			  स्थिर काष्ठा rdma_ah_attr *ah,
			  u64 smac, u16 vlan_tag, काष्ठा mlx4_qp_path *path,
			  काष्ठा mlx4_roce_smac_vlan_info *smac_info, u8 port)
अणु
	पूर्णांक vidx;
	पूर्णांक smac_index;
	पूर्णांक err;

	path->grh_mylmc = rdma_ah_get_path_bits(ah) & 0x7f;
	path->rlid = cpu_to_be16(rdma_ah_get_dlid(ah));
	अगर (rdma_ah_get_अटल_rate(ah)) अणु
		path->अटल_rate = rdma_ah_get_अटल_rate(ah) +
				    MLX4_STAT_RATE_OFFSET;
		जबतक (path->अटल_rate > IB_RATE_2_5_GBPS + MLX4_STAT_RATE_OFFSET &&
		       !(1 << path->अटल_rate & dev->dev->caps.stat_rate_support))
			--path->अटल_rate;
	पूर्ण अन्यथा
		path->अटल_rate = 0;

	अगर (rdma_ah_get_ah_flags(ah) & IB_AH_GRH) अणु
		स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah);
		पूर्णांक real_sgid_index =
			mlx4_ib_gid_index_to_real_index(dev, grh->sgid_attr);

		अगर (real_sgid_index < 0)
			वापस real_sgid_index;
		अगर (real_sgid_index >= dev->dev->caps.gid_table_len[port]) अणु
			pr_err("sgid_index (%u) too large. max is %d\n",
			       real_sgid_index, dev->dev->caps.gid_table_len[port] - 1);
			वापस -1;
		पूर्ण

		path->grh_mylmc |= 1 << 7;
		path->mgid_index = real_sgid_index;
		path->hop_limit  = grh->hop_limit;
		path->tclass_flowlabel =
			cpu_to_be32((grh->traffic_class << 20) |
				    (grh->flow_label));
		स_नकल(path->rgid, grh->dgid.raw, 16);
	पूर्ण

	अगर (ah->type == RDMA_AH_ATTR_TYPE_ROCE) अणु
		अगर (!(rdma_ah_get_ah_flags(ah) & IB_AH_GRH))
			वापस -1;

		path->sched_queue = MLX4_IB_DEFAULT_SCHED_QUEUE |
			((port - 1) << 6) | ((rdma_ah_get_sl(ah) & 7) << 3);

		path->feup |= MLX4_FEUP_FORCE_ETH_UP;
		अगर (vlan_tag < 0x1000) अणु
			अगर (smac_info->vid < 0x1000) अणु
				/* both valid vlan ids */
				अगर (smac_info->vid != vlan_tag) अणु
					/* dअगरferent VIDs.  unreg old and reg new */
					err = mlx4_रेजिस्टर_vlan(dev->dev, port, vlan_tag, &vidx);
					अगर (err)
						वापस err;
					smac_info->candidate_vid = vlan_tag;
					smac_info->candidate_vlan_index = vidx;
					smac_info->candidate_vlan_port = port;
					smac_info->update_vid = 1;
					path->vlan_index = vidx;
				पूर्ण अन्यथा अणु
					path->vlan_index = smac_info->vlan_index;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* no current vlan tag in qp */
				err = mlx4_रेजिस्टर_vlan(dev->dev, port, vlan_tag, &vidx);
				अगर (err)
					वापस err;
				smac_info->candidate_vid = vlan_tag;
				smac_info->candidate_vlan_index = vidx;
				smac_info->candidate_vlan_port = port;
				smac_info->update_vid = 1;
				path->vlan_index = vidx;
			पूर्ण
			path->feup |= MLX4_FVL_FORCE_ETH_VLAN;
			path->fl = 1 << 6;
		पूर्ण अन्यथा अणु
			/* have current vlan tag. unरेजिस्टर it at modअगरy-qp success */
			अगर (smac_info->vid < 0x1000) अणु
				smac_info->candidate_vid = 0xFFFF;
				smac_info->update_vid = 1;
			पूर्ण
		पूर्ण

		/* get smac_index क्रम RoCE use.
		 * If no smac was yet asचिन्हित, रेजिस्टर one.
		 * If one was alपढ़ोy asचिन्हित, but the new mac dअगरfers,
		 * unरेजिस्टर the old one and रेजिस्टर the new one.
		*/
		अगर ((!smac_info->smac && !smac_info->smac_port) ||
		    smac_info->smac != smac) अणु
			/* रेजिस्टर candidate now, unreg अगर needed, after success */
			smac_index = mlx4_रेजिस्टर_mac(dev->dev, port, smac);
			अगर (smac_index >= 0) अणु
				smac_info->candidate_smac_index = smac_index;
				smac_info->candidate_smac = smac;
				smac_info->candidate_smac_port = port;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			smac_index = smac_info->smac_index;
		पूर्ण
		स_नकल(path->dmac, ah->roce.dmac, 6);
		path->ackto = MLX4_IB_LINK_TYPE_ETH;
		/* put MAC table smac index क्रम IBoE */
		path->grh_mylmc = (u8) (smac_index) | 0x80;
	पूर्ण अन्यथा अणु
		path->sched_queue = MLX4_IB_DEFAULT_SCHED_QUEUE |
			((port - 1) << 6) | ((rdma_ah_get_sl(ah) & 0xf) << 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_set_path(काष्ठा mlx4_ib_dev *dev, स्थिर काष्ठा ib_qp_attr *qp,
			 क्रमागत ib_qp_attr_mask qp_attr_mask,
			 काष्ठा mlx4_ib_qp *mqp,
			 काष्ठा mlx4_qp_path *path, u8 port,
			 u16 vlan_id, u8 *smac)
अणु
	वापस _mlx4_set_path(dev, &qp->ah_attr,
			      mlx4_mac_to_u64(smac),
			      vlan_id,
			      path, &mqp->pri, port);
पूर्ण

अटल पूर्णांक mlx4_set_alt_path(काष्ठा mlx4_ib_dev *dev,
			     स्थिर काष्ठा ib_qp_attr *qp,
			     क्रमागत ib_qp_attr_mask qp_attr_mask,
			     काष्ठा mlx4_ib_qp *mqp,
			     काष्ठा mlx4_qp_path *path, u8 port)
अणु
	वापस _mlx4_set_path(dev, &qp->alt_ah_attr,
			      0,
			      0xffff,
			      path, &mqp->alt, port);
पूर्ण

अटल व्योम update_mcg_macs(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	काष्ठा mlx4_ib_gid_entry *ge, *पंचांगp;

	list_क्रम_each_entry_safe(ge, पंचांगp, &qp->gid_list, list) अणु
		अगर (!ge->added && mlx4_ib_add_mc(dev, qp, &ge->gid)) अणु
			ge->added = 1;
			ge->port = qp->port;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक handle_eth_ud_smac_index(काष्ठा mlx4_ib_dev *dev,
				    काष्ठा mlx4_ib_qp *qp,
				    काष्ठा mlx4_qp_context *context)
अणु
	u64 u64_mac;
	पूर्णांक smac_index;

	u64_mac = atomic64_पढ़ो(&dev->iboe.mac[qp->port - 1]);

	context->pri_path.sched_queue = MLX4_IB_DEFAULT_SCHED_QUEUE | ((qp->port - 1) << 6);
	अगर (!qp->pri.smac && !qp->pri.smac_port) अणु
		smac_index = mlx4_रेजिस्टर_mac(dev->dev, qp->port, u64_mac);
		अगर (smac_index >= 0) अणु
			qp->pri.candidate_smac_index = smac_index;
			qp->pri.candidate_smac = u64_mac;
			qp->pri.candidate_smac_port = qp->port;
			context->pri_path.grh_mylmc = 0x80 | (u8) smac_index;
		पूर्ण अन्यथा अणु
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक create_qp_lb_counter(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_qp *qp)
अणु
	काष्ठा counter_index *new_counter_index;
	पूर्णांक err;
	u32 पंचांगp_idx;

	अगर (rdma_port_get_link_layer(&dev->ib_dev, qp->port) !=
	    IB_LINK_LAYER_ETHERNET ||
	    !(qp->flags & MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK) ||
	    !(dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_LB_SRC_CHK))
		वापस 0;

	err = mlx4_counter_alloc(dev->dev, &पंचांगp_idx, MLX4_RES_USAGE_DRIVER);
	अगर (err)
		वापस err;

	new_counter_index = kदो_स्मृति(माप(*new_counter_index), GFP_KERNEL);
	अगर (!new_counter_index) अणु
		mlx4_counter_मुक्त(dev->dev, पंचांगp_idx);
		वापस -ENOMEM;
	पूर्ण

	new_counter_index->index = पंचांगp_idx;
	new_counter_index->allocated = 1;
	qp->counter_index = new_counter_index;

	mutex_lock(&dev->counters_table[qp->port - 1].mutex);
	list_add_tail(&new_counter_index->list,
		      &dev->counters_table[qp->port - 1].counters_list);
	mutex_unlock(&dev->counters_table[qp->port - 1].mutex);

	वापस 0;
पूर्ण

क्रमागत अणु
	MLX4_QPC_ROCE_MODE_1 = 0,
	MLX4_QPC_ROCE_MODE_2 = 2,
	MLX4_QPC_ROCE_MODE_UNDEFINED = 0xff
पूर्ण;

अटल u8 gid_type_to_qpc(क्रमागत ib_gid_type gid_type)
अणु
	चयन (gid_type) अणु
	हाल IB_GID_TYPE_ROCE:
		वापस MLX4_QPC_ROCE_MODE_1;
	हाल IB_GID_TYPE_ROCE_UDP_ENCAP:
		वापस MLX4_QPC_ROCE_MODE_2;
	शेष:
		वापस MLX4_QPC_ROCE_MODE_UNDEFINED;
	पूर्ण
पूर्ण

/*
 * Go over all RSS QP's childes (WQs) and apply their HW state according to
 * their logic state अगर the RSS QP is the first RSS QP associated क्रम the WQ.
 */
अटल पूर्णांक bringup_rss_rwqs(काष्ठा ib_rwq_ind_table *ind_tbl, u8 port_num,
			    काष्ठा ib_udata *udata)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < (1 << ind_tbl->log_ind_tbl_size); i++) अणु
		काष्ठा ib_wq *ibwq = ind_tbl->ind_tbl[i];
		काष्ठा mlx4_ib_qp *wq = to_mqp((काष्ठा ib_qp *)ibwq);

		mutex_lock(&wq->mutex);

		/* Mlx4_ib restrictions:
		 * WQ's is associated to a port according to the RSS QP it is
		 * associates to.
		 * In हाल the WQ is associated to a dअगरferent port by another
		 * RSS QP, वापस a failure.
		 */
		अगर ((wq->rss_usecnt > 0) && (wq->port != port_num)) अणु
			err = -EINVAL;
			mutex_unlock(&wq->mutex);
			अवरोध;
		पूर्ण
		wq->port = port_num;
		अगर ((wq->rss_usecnt == 0) && (ibwq->state == IB_WQS_RDY)) अणु
			err = _mlx4_ib_modअगरy_wq(ibwq, IB_WQS_RDY, udata);
			अगर (err) अणु
				mutex_unlock(&wq->mutex);
				अवरोध;
			पूर्ण
		पूर्ण
		wq->rss_usecnt++;

		mutex_unlock(&wq->mutex);
	पूर्ण

	अगर (i && err) अणु
		पूर्णांक j;

		क्रम (j = (i - 1); j >= 0; j--) अणु
			काष्ठा ib_wq *ibwq = ind_tbl->ind_tbl[j];
			काष्ठा mlx4_ib_qp *wq = to_mqp((काष्ठा ib_qp *)ibwq);

			mutex_lock(&wq->mutex);

			अगर ((wq->rss_usecnt == 1) &&
			    (ibwq->state == IB_WQS_RDY))
				अगर (_mlx4_ib_modअगरy_wq(ibwq, IB_WQS_RESET,
						       udata))
					pr_warn("failed to reverse WQN=0x%06x\n",
						ibwq->wq_num);
			wq->rss_usecnt--;

			mutex_unlock(&wq->mutex);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम bring_करोwn_rss_rwqs(काष्ठा ib_rwq_ind_table *ind_tbl,
				काष्ठा ib_udata *udata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (1 << ind_tbl->log_ind_tbl_size); i++) अणु
		काष्ठा ib_wq *ibwq = ind_tbl->ind_tbl[i];
		काष्ठा mlx4_ib_qp *wq = to_mqp((काष्ठा ib_qp *)ibwq);

		mutex_lock(&wq->mutex);

		अगर ((wq->rss_usecnt == 1) && (ibwq->state == IB_WQS_RDY))
			अगर (_mlx4_ib_modअगरy_wq(ibwq, IB_WQS_RESET, udata))
				pr_warn("failed to reverse WQN=%x\n",
					ibwq->wq_num);
		wq->rss_usecnt--;

		mutex_unlock(&wq->mutex);
	पूर्ण
पूर्ण

अटल व्योम fill_qp_rss_context(काष्ठा mlx4_qp_context *context,
				काष्ठा mlx4_ib_qp *qp)
अणु
	काष्ठा mlx4_rss_context *rss_context;

	rss_context = (व्योम *)context + दुरत्व(काष्ठा mlx4_qp_context,
			pri_path) + MLX4_RSS_OFFSET_IN_QPC_PRI_PATH;

	rss_context->base_qpn = cpu_to_be32(qp->rss_ctx->base_qpn_tbl_sz);
	rss_context->शेष_qpn =
		cpu_to_be32(qp->rss_ctx->base_qpn_tbl_sz & 0xffffff);
	अगर (qp->rss_ctx->flags & (MLX4_RSS_UDP_IPV4 | MLX4_RSS_UDP_IPV6))
		rss_context->base_qpn_udp = rss_context->शेष_qpn;
	rss_context->flags = qp->rss_ctx->flags;
	/* Currently support just toeplitz */
	rss_context->hash_fn = MLX4_RSS_HASH_TOP;

	स_नकल(rss_context->rss_key, qp->rss_ctx->rss_key,
	       MLX4_EN_RSS_KEY_SIZE);
पूर्ण

अटल पूर्णांक __mlx4_ib_modअगरy_qp(व्योम *src, क्रमागत mlx4_ib_source_type src_type,
			       स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
			       क्रमागत ib_qp_state cur_state,
			       क्रमागत ib_qp_state new_state,
			       काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_srq  *ibsrq;
	स्थिर काष्ठा ib_gid_attr *gid_attr = शून्य;
	काष्ठा ib_rwq_ind_table *rwq_ind_tbl;
	क्रमागत ib_qp_type qp_type;
	काष्ठा mlx4_ib_dev *dev;
	काष्ठा mlx4_ib_qp *qp;
	काष्ठा mlx4_ib_pd *pd;
	काष्ठा mlx4_ib_cq *send_cq, *recv_cq;
	काष्ठा mlx4_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx4_ib_ucontext, ibucontext);
	काष्ठा mlx4_qp_context *context;
	क्रमागत mlx4_qp_optpar optpar = 0;
	पूर्णांक sqd_event;
	पूर्णांक steer_qp = 0;
	पूर्णांक err = -EINVAL;
	पूर्णांक counter_index;

	अगर (src_type == MLX4_IB_RWQ_SRC) अणु
		काष्ठा ib_wq *ibwq;

		ibwq	    = (काष्ठा ib_wq *)src;
		ibsrq	    = शून्य;
		rwq_ind_tbl = शून्य;
		qp_type     = IB_QPT_RAW_PACKET;
		qp	    = to_mqp((काष्ठा ib_qp *)ibwq);
		dev	    = to_mdev(ibwq->device);
		pd	    = to_mpd(ibwq->pd);
	पूर्ण अन्यथा अणु
		काष्ठा ib_qp *ibqp;

		ibqp	    = (काष्ठा ib_qp *)src;
		ibsrq	    = ibqp->srq;
		rwq_ind_tbl = ibqp->rwq_ind_tbl;
		qp_type     = ibqp->qp_type;
		qp	    = to_mqp(ibqp);
		dev	    = to_mdev(ibqp->device);
		pd	    = get_pd(qp);
	पूर्ण

	/* APM is not supported under RoCE */
	अगर (attr_mask & IB_QP_ALT_PATH &&
	    rdma_port_get_link_layer(&dev->ib_dev, qp->port) ==
	    IB_LINK_LAYER_ETHERNET)
		वापस -ENOTSUPP;

	context = kzalloc(माप *context, GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	context->flags = cpu_to_be32((to_mlx4_state(new_state) << 28) |
				     (to_mlx4_st(dev, qp->mlx4_ib_qp_type) << 16));

	अगर (!(attr_mask & IB_QP_PATH_MIG_STATE))
		context->flags |= cpu_to_be32(MLX4_QP_PM_MIGRATED << 11);
	अन्यथा अणु
		optpar |= MLX4_QP_OPTPAR_PM_STATE;
		चयन (attr->path_mig_state) अणु
		हाल IB_MIG_MIGRATED:
			context->flags |= cpu_to_be32(MLX4_QP_PM_MIGRATED << 11);
			अवरोध;
		हाल IB_MIG_REARM:
			context->flags |= cpu_to_be32(MLX4_QP_PM_REARM << 11);
			अवरोध;
		हाल IB_MIG_ARMED:
			context->flags |= cpu_to_be32(MLX4_QP_PM_ARMED << 11);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (qp->inl_recv_sz)
		context->param3 |= cpu_to_be32(1 << 25);

	अगर (qp->flags & MLX4_IB_QP_SCATTER_FCS)
		context->param3 |= cpu_to_be32(1 << 29);

	अगर (qp_type == IB_QPT_GSI || qp_type == IB_QPT_SMI)
		context->mtu_msgmax = (IB_MTU_4096 << 5) | 11;
	अन्यथा अगर (qp_type == IB_QPT_RAW_PACKET)
		context->mtu_msgmax = (MLX4_RAW_QP_MTU << 5) | MLX4_RAW_QP_MSGMAX;
	अन्यथा अगर (qp_type == IB_QPT_UD) अणु
		अगर (qp->flags & MLX4_IB_QP_LSO)
			context->mtu_msgmax = (IB_MTU_4096 << 5) |
					      ilog2(dev->dev->caps.max_gso_sz);
		अन्यथा
			context->mtu_msgmax = (IB_MTU_4096 << 5) | 13;
	पूर्ण अन्यथा अगर (attr_mask & IB_QP_PATH_MTU) अणु
		अगर (attr->path_mtu < IB_MTU_256 || attr->path_mtu > IB_MTU_4096) अणु
			pr_err("path MTU (%u) is invalid\n",
			       attr->path_mtu);
			जाओ out;
		पूर्ण
		context->mtu_msgmax = (attr->path_mtu << 5) |
			ilog2(dev->dev->caps.max_msg_sz);
	पूर्ण

	अगर (!rwq_ind_tbl) अणु /* PRM RSS receive side should be left zeros */
		अगर (qp->rq.wqe_cnt)
			context->rq_size_stride = ilog2(qp->rq.wqe_cnt) << 3;
		context->rq_size_stride |= qp->rq.wqe_shअगरt - 4;
	पूर्ण

	अगर (qp->sq.wqe_cnt)
		context->sq_size_stride = ilog2(qp->sq.wqe_cnt) << 3;
	context->sq_size_stride |= qp->sq.wqe_shअगरt - 4;

	अगर (new_state == IB_QPS_RESET && qp->counter_index)
		mlx4_ib_मुक्त_qp_counter(dev, qp);

	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		context->sq_size_stride |= !!qp->sq_no_prefetch << 7;
		context->xrcd = cpu_to_be32((u32) qp->xrcdn);
		अगर (qp_type == IB_QPT_RAW_PACKET)
			context->param3 |= cpu_to_be32(1 << 30);
	पूर्ण

	अगर (ucontext)
		context->usr_page = cpu_to_be32(
			mlx4_to_hw_uar_index(dev->dev, ucontext->uar.index));
	अन्यथा
		context->usr_page = cpu_to_be32(
			mlx4_to_hw_uar_index(dev->dev, dev->priv_uar.index));

	अगर (attr_mask & IB_QP_DEST_QPN)
		context->remote_qpn = cpu_to_be32(attr->dest_qp_num);

	अगर (attr_mask & IB_QP_PORT) अणु
		अगर (cur_state == IB_QPS_SQD && new_state == IB_QPS_SQD &&
		    !(attr_mask & IB_QP_AV)) अणु
			mlx4_set_sched(&context->pri_path, attr->port_num);
			optpar |= MLX4_QP_OPTPAR_SCHED_QUEUE;
		पूर्ण
	पूर्ण

	अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) अणु
		err = create_qp_lb_counter(dev, qp);
		अगर (err)
			जाओ out;

		counter_index =
			dev->counters_table[qp->port - 1].शेष_counter;
		अगर (qp->counter_index)
			counter_index = qp->counter_index->index;

		अगर (counter_index != -1) अणु
			context->pri_path.counter_index = counter_index;
			optpar |= MLX4_QP_OPTPAR_COUNTER_INDEX;
			अगर (qp->counter_index) अणु
				context->pri_path.fl |=
					MLX4_FL_ETH_SRC_CHECK_MC_LB;
				context->pri_path.vlan_control |=
					MLX4_CTRL_ETH_SRC_CHECK_IF_COUNTER;
			पूर्ण
		पूर्ण अन्यथा
			context->pri_path.counter_index =
				MLX4_SINK_COUNTER_INDEX(dev->dev);

		अगर (qp->flags & MLX4_IB_QP_NETIF) अणु
			mlx4_ib_steer_qp_reg(dev, qp, 1);
			steer_qp = 1;
		पूर्ण

		अगर (qp_type == IB_QPT_GSI) अणु
			क्रमागत ib_gid_type gid_type = qp->flags & MLX4_IB_ROCE_V2_GSI_QP ?
				IB_GID_TYPE_ROCE_UDP_ENCAP : IB_GID_TYPE_ROCE;
			u8 qpc_roce_mode = gid_type_to_qpc(gid_type);

			context->rlkey_roce_mode |= (qpc_roce_mode << 6);
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_PKEY_INDEX) अणु
		अगर (qp->mlx4_ib_qp_type & MLX4_IB_QPT_ANY_SRIOV)
			context->pri_path.disable_pkey_check = 0x40;
		context->pri_path.pkey_index = attr->pkey_index;
		optpar |= MLX4_QP_OPTPAR_PKEY_INDEX;
	पूर्ण

	अगर (attr_mask & IB_QP_AV) अणु
		u8 port_num = mlx4_is_bonded(dev->dev) ? 1 :
			attr_mask & IB_QP_PORT ? attr->port_num : qp->port;
		u16 vlan = 0xffff;
		u8 smac[ETH_ALEN];
		पूर्णांक is_eth =
			rdma_cap_eth_ah(&dev->ib_dev, port_num) &&
			rdma_ah_get_ah_flags(&attr->ah_attr) & IB_AH_GRH;

		अगर (is_eth) अणु
			gid_attr = attr->ah_attr.grh.sgid_attr;
			err = rdma_पढ़ो_gid_l2_fields(gid_attr, &vlan,
						      &smac[0]);
			अगर (err)
				जाओ out;
		पूर्ण

		अगर (mlx4_set_path(dev, attr, attr_mask, qp, &context->pri_path,
				  port_num, vlan, smac))
			जाओ out;

		optpar |= (MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH |
			   MLX4_QP_OPTPAR_SCHED_QUEUE);

		अगर (is_eth &&
		    (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR)) अणु
			u8 qpc_roce_mode = gid_type_to_qpc(gid_attr->gid_type);

			अगर (qpc_roce_mode == MLX4_QPC_ROCE_MODE_UNDEFINED) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			context->rlkey_roce_mode |= (qpc_roce_mode << 6);
		पूर्ण

	पूर्ण

	अगर (attr_mask & IB_QP_TIMEOUT) अणु
		context->pri_path.ackto |= attr->समयout << 3;
		optpar |= MLX4_QP_OPTPAR_ACK_TIMEOUT;
	पूर्ण

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		अगर (attr->alt_port_num == 0 ||
		    attr->alt_port_num > dev->dev->caps.num_ports)
			जाओ out;

		अगर (attr->alt_pkey_index >=
		    dev->dev->caps.pkey_table_len[attr->alt_port_num])
			जाओ out;

		अगर (mlx4_set_alt_path(dev, attr, attr_mask, qp,
				      &context->alt_path,
				      attr->alt_port_num))
			जाओ out;

		context->alt_path.pkey_index = attr->alt_pkey_index;
		context->alt_path.ackto = attr->alt_समयout << 3;
		optpar |= MLX4_QP_OPTPAR_ALT_ADDR_PATH;
	पूर्ण

	context->pd = cpu_to_be32(pd->pdn);

	अगर (!rwq_ind_tbl) अणु
		context->params1 = cpu_to_be32(MLX4_IB_ACK_REQ_FREQ << 28);
		get_cqs(qp, src_type, &send_cq, &recv_cq);
	पूर्ण अन्यथा अणु /* Set dummy CQs to be compatible with HV and PRM */
		send_cq = to_mcq(rwq_ind_tbl->ind_tbl[0]->cq);
		recv_cq = send_cq;
	पूर्ण
	context->cqn_send = cpu_to_be32(send_cq->mcq.cqn);
	context->cqn_recv = cpu_to_be32(recv_cq->mcq.cqn);

	/* Set "fast registration enabled" क्रम all kernel QPs */
	अगर (!ucontext)
		context->params1 |= cpu_to_be32(1 << 11);

	अगर (attr_mask & IB_QP_RNR_RETRY) अणु
		context->params1 |= cpu_to_be32(attr->rnr_retry << 13);
		optpar |= MLX4_QP_OPTPAR_RNR_RETRY;
	पूर्ण

	अगर (attr_mask & IB_QP_RETRY_CNT) अणु
		context->params1 |= cpu_to_be32(attr->retry_cnt << 16);
		optpar |= MLX4_QP_OPTPAR_RETRY_COUNT;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		अगर (attr->max_rd_atomic)
			context->params1 |=
				cpu_to_be32(fls(attr->max_rd_atomic - 1) << 21);
		optpar |= MLX4_QP_OPTPAR_SRA_MAX;
	पूर्ण

	अगर (attr_mask & IB_QP_SQ_PSN)
		context->next_send_psn = cpu_to_be32(attr->sq_psn);

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) अणु
		अगर (attr->max_dest_rd_atomic)
			context->params2 |=
				cpu_to_be32(fls(attr->max_dest_rd_atomic - 1) << 21);
		optpar |= MLX4_QP_OPTPAR_RRA_MAX;
	पूर्ण

	अगर (attr_mask & (IB_QP_ACCESS_FLAGS | IB_QP_MAX_DEST_RD_ATOMIC)) अणु
		context->params2 |= to_mlx4_access_flags(qp, attr, attr_mask);
		optpar |= MLX4_QP_OPTPAR_RWE | MLX4_QP_OPTPAR_RRE | MLX4_QP_OPTPAR_RAE;
	पूर्ण

	अगर (ibsrq)
		context->params2 |= cpu_to_be32(MLX4_QP_BIT_RIC);

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER) अणु
		context->rnr_nextrecvpsn |= cpu_to_be32(attr->min_rnr_समयr << 24);
		optpar |= MLX4_QP_OPTPAR_RNR_TIMEOUT;
	पूर्ण
	अगर (attr_mask & IB_QP_RQ_PSN)
		context->rnr_nextrecvpsn |= cpu_to_be32(attr->rq_psn);

	/* proxy and tunnel qp qkeys will be changed in modअगरy-qp wrappers */
	अगर (attr_mask & IB_QP_QKEY) अणु
		अगर (qp->mlx4_ib_qp_type &
		    (MLX4_IB_QPT_PROXY_SMI_OWNER | MLX4_IB_QPT_TUN_SMI_OWNER))
			context->qkey = cpu_to_be32(IB_QP_SET_QKEY);
		अन्यथा अणु
			अगर (mlx4_is_mfunc(dev->dev) &&
			    !(qp->mlx4_ib_qp_type & MLX4_IB_QPT_ANY_SRIOV) &&
			    (attr->qkey & MLX4_RESERVED_QKEY_MASK) ==
			    MLX4_RESERVED_QKEY_BASE) अणु
				pr_err("Cannot use reserved QKEY"
				       " 0x%x (range 0xffff0000..0xffffffff"
				       " is reserved)\n", attr->qkey);
				err = -EINVAL;
				जाओ out;
			पूर्ण
			context->qkey = cpu_to_be32(attr->qkey);
		पूर्ण
		optpar |= MLX4_QP_OPTPAR_Q_KEY;
	पूर्ण

	अगर (ibsrq)
		context->srqn = cpu_to_be32(1 << 24 |
					    to_msrq(ibsrq)->msrq.srqn);

	अगर (qp->rq.wqe_cnt &&
	    cur_state == IB_QPS_RESET &&
	    new_state == IB_QPS_INIT)
		context->db_rec_addr = cpu_to_be64(qp->db.dma);

	अगर (cur_state == IB_QPS_INIT &&
	    new_state == IB_QPS_RTR  &&
	    (qp_type == IB_QPT_GSI || qp_type == IB_QPT_SMI ||
	     qp_type == IB_QPT_UD || qp_type == IB_QPT_RAW_PACKET)) अणु
		context->pri_path.sched_queue = (qp->port - 1) << 6;
		अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_SMI ||
		    qp->mlx4_ib_qp_type &
		    (MLX4_IB_QPT_PROXY_SMI_OWNER | MLX4_IB_QPT_TUN_SMI_OWNER)) अणु
			context->pri_path.sched_queue |= MLX4_IB_DEFAULT_QP0_SCHED_QUEUE;
			अगर (qp->mlx4_ib_qp_type != MLX4_IB_QPT_SMI)
				context->pri_path.fl = 0x80;
		पूर्ण अन्यथा अणु
			अगर (qp->mlx4_ib_qp_type & MLX4_IB_QPT_ANY_SRIOV)
				context->pri_path.fl = 0x80;
			context->pri_path.sched_queue |= MLX4_IB_DEFAULT_SCHED_QUEUE;
		पूर्ण
		अगर (rdma_port_get_link_layer(&dev->ib_dev, qp->port) ==
		    IB_LINK_LAYER_ETHERNET) अणु
			अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_TUN_GSI ||
			    qp->mlx4_ib_qp_type == MLX4_IB_QPT_GSI)
				context->pri_path.feup = 1 << 7; /* करोn't fsm */
			/* handle smac_index */
			अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_UD ||
			    qp->mlx4_ib_qp_type == MLX4_IB_QPT_PROXY_GSI ||
			    qp->mlx4_ib_qp_type == MLX4_IB_QPT_TUN_GSI) अणु
				err = handle_eth_ud_smac_index(dev, qp, context);
				अगर (err) अणु
					err = -EINVAL;
					जाओ out;
				पूर्ण
				अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_PROXY_GSI)
					dev->qp1_proxy[qp->port - 1] = qp;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (qp_type == IB_QPT_RAW_PACKET) अणु
		context->pri_path.ackto = (context->pri_path.ackto & 0xf8) |
					MLX4_IB_LINK_TYPE_ETH;
		अगर (dev->dev->caps.tunnel_offload_mode ==  MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) अणु
			/* set QP to receive both tunneled & non-tunneled packets */
			अगर (!rwq_ind_tbl)
				context->srqn = cpu_to_be32(7 << 28);
		पूर्ण
	पूर्ण

	अगर (qp_type == IB_QPT_UD && (new_state == IB_QPS_RTR)) अणु
		पूर्णांक is_eth = rdma_port_get_link_layer(
				&dev->ib_dev, qp->port) ==
				IB_LINK_LAYER_ETHERNET;
		अगर (is_eth) अणु
			context->pri_path.ackto = MLX4_IB_LINK_TYPE_ETH;
			optpar |= MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH;
		पूर्ण
	पूर्ण

	अगर (cur_state == IB_QPS_RTS && new_state == IB_QPS_SQD	&&
	    attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY && attr->en_sqd_async_notअगरy)
		sqd_event = 1;
	अन्यथा
		sqd_event = 0;

	अगर (!ucontext &&
	    cur_state == IB_QPS_RESET &&
	    new_state == IB_QPS_INIT)
		context->rlkey_roce_mode |= (1 << 4);

	/*
	 * Beक्रमe passing a kernel QP to the HW, make sure that the
	 * ownership bits of the send queue are set and the SQ
	 * headroom is stamped so that the hardware करोesn't start
	 * processing stale work requests.
	 */
	अगर (!ucontext &&
	    cur_state == IB_QPS_RESET &&
	    new_state == IB_QPS_INIT) अणु
		काष्ठा mlx4_wqe_ctrl_seg *ctrl;
		पूर्णांक i;

		क्रम (i = 0; i < qp->sq.wqe_cnt; ++i) अणु
			ctrl = get_send_wqe(qp, i);
			ctrl->owner_opcode = cpu_to_be32(1 << 31);
			ctrl->qpn_vlan.fence_size =
				1 << (qp->sq.wqe_shअगरt - 4);
			stamp_send_wqe(qp, i);
		पूर्ण
	पूर्ण

	अगर (rwq_ind_tbl	&&
	    cur_state == IB_QPS_RESET &&
	    new_state == IB_QPS_INIT) अणु
		fill_qp_rss_context(context, qp);
		context->flags |= cpu_to_be32(1 << MLX4_RSS_QPC_FLAG_OFFSET);
	पूर्ण

	err = mlx4_qp_modअगरy(dev->dev, &qp->mtt, to_mlx4_state(cur_state),
			     to_mlx4_state(new_state), context, optpar,
			     sqd_event, &qp->mqp);
	अगर (err)
		जाओ out;

	qp->state = new_state;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		qp->atomic_rd_en = attr->qp_access_flags;
	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		qp->resp_depth = attr->max_dest_rd_atomic;
	अगर (attr_mask & IB_QP_PORT) अणु
		qp->port = attr->port_num;
		update_mcg_macs(dev, qp);
	पूर्ण
	अगर (attr_mask & IB_QP_ALT_PATH)
		qp->alt_port = attr->alt_port_num;

	अगर (is_sqp(dev, qp))
		store_sqp_attrs(qp->sqp, attr, attr_mask);

	/*
	 * If we moved QP0 to RTR, bring the IB link up; अगर we moved
	 * QP0 to RESET or ERROR, bring the link back करोwn.
	 */
	अगर (is_qp0(dev, qp)) अणु
		अगर (cur_state != IB_QPS_RTR && new_state == IB_QPS_RTR)
			अगर (mlx4_INIT_PORT(dev->dev, qp->port))
				pr_warn("INIT_PORT failed for port %d\n",
				       qp->port);

		अगर (cur_state != IB_QPS_RESET && cur_state != IB_QPS_ERR &&
		    (new_state == IB_QPS_RESET || new_state == IB_QPS_ERR))
			mlx4_CLOSE_PORT(dev->dev, qp->port);
	पूर्ण

	/*
	 * If we moved a kernel QP to RESET, clean up all old CQ
	 * entries and reinitialize the QP.
	 */
	अगर (new_state == IB_QPS_RESET) अणु
		अगर (!ucontext) अणु
			mlx4_ib_cq_clean(recv_cq, qp->mqp.qpn,
					 ibsrq ? to_msrq(ibsrq) : शून्य);
			अगर (send_cq != recv_cq)
				mlx4_ib_cq_clean(send_cq, qp->mqp.qpn, शून्य);

			qp->rq.head = 0;
			qp->rq.tail = 0;
			qp->sq.head = 0;
			qp->sq.tail = 0;
			qp->sq_next_wqe = 0;
			अगर (qp->rq.wqe_cnt)
				*qp->db.db  = 0;

			अगर (qp->flags & MLX4_IB_QP_NETIF)
				mlx4_ib_steer_qp_reg(dev, qp, 0);
		पूर्ण
		अगर (qp->pri.smac || (!qp->pri.smac && qp->pri.smac_port)) अणु
			mlx4_unरेजिस्टर_mac(dev->dev, qp->pri.smac_port, qp->pri.smac);
			qp->pri.smac = 0;
			qp->pri.smac_port = 0;
		पूर्ण
		अगर (qp->alt.smac) अणु
			mlx4_unरेजिस्टर_mac(dev->dev, qp->alt.smac_port, qp->alt.smac);
			qp->alt.smac = 0;
		पूर्ण
		अगर (qp->pri.vid < 0x1000) अणु
			mlx4_unरेजिस्टर_vlan(dev->dev, qp->pri.vlan_port, qp->pri.vid);
			qp->pri.vid = 0xFFFF;
			qp->pri.candidate_vid = 0xFFFF;
			qp->pri.update_vid = 0;
		पूर्ण

		अगर (qp->alt.vid < 0x1000) अणु
			mlx4_unरेजिस्टर_vlan(dev->dev, qp->alt.vlan_port, qp->alt.vid);
			qp->alt.vid = 0xFFFF;
			qp->alt.candidate_vid = 0xFFFF;
			qp->alt.update_vid = 0;
		पूर्ण
	पूर्ण
out:
	अगर (err && qp->counter_index)
		mlx4_ib_मुक्त_qp_counter(dev, qp);
	अगर (err && steer_qp)
		mlx4_ib_steer_qp_reg(dev, qp, 0);
	kमुक्त(context);
	अगर (qp->pri.candidate_smac ||
	    (!qp->pri.candidate_smac && qp->pri.candidate_smac_port)) अणु
		अगर (err) अणु
			mlx4_unरेजिस्टर_mac(dev->dev, qp->pri.candidate_smac_port, qp->pri.candidate_smac);
		पूर्ण अन्यथा अणु
			अगर (qp->pri.smac || (!qp->pri.smac && qp->pri.smac_port))
				mlx4_unरेजिस्टर_mac(dev->dev, qp->pri.smac_port, qp->pri.smac);
			qp->pri.smac = qp->pri.candidate_smac;
			qp->pri.smac_index = qp->pri.candidate_smac_index;
			qp->pri.smac_port = qp->pri.candidate_smac_port;
		पूर्ण
		qp->pri.candidate_smac = 0;
		qp->pri.candidate_smac_index = 0;
		qp->pri.candidate_smac_port = 0;
	पूर्ण
	अगर (qp->alt.candidate_smac) अणु
		अगर (err) अणु
			mlx4_unरेजिस्टर_mac(dev->dev, qp->alt.candidate_smac_port, qp->alt.candidate_smac);
		पूर्ण अन्यथा अणु
			अगर (qp->alt.smac)
				mlx4_unरेजिस्टर_mac(dev->dev, qp->alt.smac_port, qp->alt.smac);
			qp->alt.smac = qp->alt.candidate_smac;
			qp->alt.smac_index = qp->alt.candidate_smac_index;
			qp->alt.smac_port = qp->alt.candidate_smac_port;
		पूर्ण
		qp->alt.candidate_smac = 0;
		qp->alt.candidate_smac_index = 0;
		qp->alt.candidate_smac_port = 0;
	पूर्ण

	अगर (qp->pri.update_vid) अणु
		अगर (err) अणु
			अगर (qp->pri.candidate_vid < 0x1000)
				mlx4_unरेजिस्टर_vlan(dev->dev, qp->pri.candidate_vlan_port,
						     qp->pri.candidate_vid);
		पूर्ण अन्यथा अणु
			अगर (qp->pri.vid < 0x1000)
				mlx4_unरेजिस्टर_vlan(dev->dev, qp->pri.vlan_port,
						     qp->pri.vid);
			qp->pri.vid = qp->pri.candidate_vid;
			qp->pri.vlan_port = qp->pri.candidate_vlan_port;
			qp->pri.vlan_index =  qp->pri.candidate_vlan_index;
		पूर्ण
		qp->pri.candidate_vid = 0xFFFF;
		qp->pri.update_vid = 0;
	पूर्ण

	अगर (qp->alt.update_vid) अणु
		अगर (err) अणु
			अगर (qp->alt.candidate_vid < 0x1000)
				mlx4_unरेजिस्टर_vlan(dev->dev, qp->alt.candidate_vlan_port,
						     qp->alt.candidate_vid);
		पूर्ण अन्यथा अणु
			अगर (qp->alt.vid < 0x1000)
				mlx4_unरेजिस्टर_vlan(dev->dev, qp->alt.vlan_port,
						     qp->alt.vid);
			qp->alt.vid = qp->alt.candidate_vid;
			qp->alt.vlan_port = qp->alt.candidate_vlan_port;
			qp->alt.vlan_index =  qp->alt.candidate_vlan_index;
		पूर्ण
		qp->alt.candidate_vid = 0xFFFF;
		qp->alt.update_vid = 0;
	पूर्ण

	वापस err;
पूर्ण

क्रमागत अणु
	MLX4_IB_MODIFY_QP_RSS_SUP_ATTR_MSK = (IB_QP_STATE	|
					      IB_QP_PORT),
पूर्ण;

अटल पूर्णांक _mlx4_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
			      पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx4_ib_qp *qp = to_mqp(ibqp);
	क्रमागत ib_qp_state cur_state, new_state;
	पूर्णांक err = -EINVAL;
	mutex_lock(&qp->mutex);

	cur_state = attr_mask & IB_QP_CUR_STATE ? attr->cur_qp_state : qp->state;
	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;

	अगर (!ib_modअगरy_qp_is_ok(cur_state, new_state, ibqp->qp_type,
				attr_mask)) अणु
		pr_debug("qpn 0x%x: invalid attribute mask specified "
			 "for transition %d to %d. qp_type %d,"
			 " attr_mask 0x%x\n",
			 ibqp->qp_num, cur_state, new_state,
			 ibqp->qp_type, attr_mask);
		जाओ out;
	पूर्ण

	अगर (ibqp->rwq_ind_tbl) अणु
		अगर (!(((cur_state == IB_QPS_RESET) &&
		       (new_state == IB_QPS_INIT)) ||
		      ((cur_state == IB_QPS_INIT)  &&
		       (new_state == IB_QPS_RTR)))) अणु
			pr_debug("qpn 0x%x: RSS QP unsupported transition %d to %d\n",
				 ibqp->qp_num, cur_state, new_state);

			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		अगर (attr_mask & ~MLX4_IB_MODIFY_QP_RSS_SUP_ATTR_MSK) अणु
			pr_debug("qpn 0x%x: RSS QP unsupported attribute mask 0x%x for transition %d to %d\n",
				 ibqp->qp_num, attr_mask, cur_state, new_state);

			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (mlx4_is_bonded(dev->dev) && (attr_mask & IB_QP_PORT)) अणु
		अगर ((cur_state == IB_QPS_RESET) && (new_state == IB_QPS_INIT)) अणु
			अगर ((ibqp->qp_type == IB_QPT_RC) ||
			    (ibqp->qp_type == IB_QPT_UD) ||
			    (ibqp->qp_type == IB_QPT_UC) ||
			    (ibqp->qp_type == IB_QPT_RAW_PACKET) ||
			    (ibqp->qp_type == IB_QPT_XRC_INI)) अणु
				attr->port_num = mlx4_ib_bond_next_port(dev);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* no sense in changing port_num
			 * when ports are bonded */
			attr_mask &= ~IB_QP_PORT;
		पूर्ण
	पूर्ण

	अगर ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 || attr->port_num > dev->num_ports)) अणु
		pr_debug("qpn 0x%x: invalid port number (%d) specified "
			 "for transition %d to %d. qp_type %d\n",
			 ibqp->qp_num, attr->port_num, cur_state,
			 new_state, ibqp->qp_type);
		जाओ out;
	पूर्ण

	अगर ((attr_mask & IB_QP_PORT) && (ibqp->qp_type == IB_QPT_RAW_PACKET) &&
	    (rdma_port_get_link_layer(&dev->ib_dev, attr->port_num) !=
	     IB_LINK_LAYER_ETHERNET))
		जाओ out;

	अगर (attr_mask & IB_QP_PKEY_INDEX) अणु
		पूर्णांक p = attr_mask & IB_QP_PORT ? attr->port_num : qp->port;
		अगर (attr->pkey_index >= dev->dev->caps.pkey_table_len[p]) अणु
			pr_debug("qpn 0x%x: invalid pkey index (%d) specified "
				 "for transition %d to %d. qp_type %d\n",
				 ibqp->qp_num, attr->pkey_index, cur_state,
				 new_state, ibqp->qp_type);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic > dev->dev->caps.max_qp_init_rdma) अणु
		pr_debug("qpn 0x%x: max_rd_atomic (%d) too large. "
			 "Transition %d to %d. qp_type %d\n",
			 ibqp->qp_num, attr->max_rd_atomic, cur_state,
			 new_state, ibqp->qp_type);
		जाओ out;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic > dev->dev->caps.max_qp_dest_rdma) अणु
		pr_debug("qpn 0x%x: max_dest_rd_atomic (%d) too large. "
			 "Transition %d to %d. qp_type %d\n",
			 ibqp->qp_num, attr->max_dest_rd_atomic, cur_state,
			 new_state, ibqp->qp_type);
		जाओ out;
	पूर्ण

	अगर (cur_state == new_state && cur_state == IB_QPS_RESET) अणु
		err = 0;
		जाओ out;
	पूर्ण

	अगर (ibqp->rwq_ind_tbl && (new_state == IB_QPS_INIT)) अणु
		err = bringup_rss_rwqs(ibqp->rwq_ind_tbl, attr->port_num,
				       udata);
		अगर (err)
			जाओ out;
	पूर्ण

	err = __mlx4_ib_modअगरy_qp(ibqp, MLX4_IB_QP_SRC, attr, attr_mask,
				  cur_state, new_state, udata);

	अगर (ibqp->rwq_ind_tbl && err)
		bring_करोwn_rss_rwqs(ibqp->rwq_ind_tbl, udata);

	अगर (mlx4_is_bonded(dev->dev) && (attr_mask & IB_QP_PORT))
		attr->port_num = 1;

out:
	mutex_unlock(&qp->mutex);
	वापस err;
पूर्ण

पूर्णांक mlx4_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_qp *mqp = to_mqp(ibqp);
	पूर्णांक ret;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	ret = _mlx4_ib_modअगरy_qp(ibqp, attr, attr_mask, udata);

	अगर (mqp->mlx4_ib_qp_type == MLX4_IB_QPT_GSI) अणु
		काष्ठा mlx4_ib_sqp *sqp = mqp->sqp;
		पूर्णांक err = 0;

		अगर (sqp->roce_v2_gsi)
			err = ib_modअगरy_qp(sqp->roce_v2_gsi, attr, attr_mask);
		अगर (err)
			pr_err("Failed to modify GSI QP for RoCEv2 (%d)\n",
			       err);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vf_get_qp0_qkey(काष्ठा mlx4_dev *dev, पूर्णांक qpn, u32 *qkey)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dev->caps.num_ports; i++) अणु
		अगर (qpn == dev->caps.spec_qps[i].qp0_proxy ||
		    qpn == dev->caps.spec_qps[i].qp0_tunnel) अणु
			*qkey = dev->caps.spec_qps[i].qp0_qkey;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक build_sriov_qp0_header(काष्ठा mlx4_ib_qp *qp,
				  स्थिर काष्ठा ib_ud_wr *wr,
				  व्योम *wqe, अचिन्हित *mlx_seg_len)
अणु
	काष्ठा mlx4_ib_dev *mdev = to_mdev(qp->ibqp.device);
	काष्ठा mlx4_ib_sqp *sqp = qp->sqp;
	काष्ठा ib_device *ib_dev = qp->ibqp.device;
	काष्ठा mlx4_wqe_mlx_seg *mlx = wqe;
	काष्ठा mlx4_wqe_अंतरभूत_seg *inl = wqe + माप *mlx;
	काष्ठा mlx4_ib_ah *ah = to_mah(wr->ah);
	u16 pkey;
	u32 qkey;
	पूर्णांक send_size;
	पूर्णांक header_size;
	पूर्णांक spc;
	पूर्णांक err;
	पूर्णांक i;

	अगर (wr->wr.opcode != IB_WR_SEND)
		वापस -EINVAL;

	send_size = 0;

	क्रम (i = 0; i < wr->wr.num_sge; ++i)
		send_size += wr->wr.sg_list[i].length;

	/* क्रम proxy-qp0 sends, need to add in size of tunnel header */
	/* क्रम tunnel-qp0 sends, tunnel header is alपढ़ोy in s/g list */
	अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_PROXY_SMI_OWNER)
		send_size += माप (काष्ठा mlx4_ib_tunnel_header);

	ib_ud_header_init(send_size, 1, 0, 0, 0, 0, 0, 0, &sqp->ud_header);

	अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_PROXY_SMI_OWNER) अणु
		sqp->ud_header.lrh.service_level =
			be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 28;
		sqp->ud_header.lrh.destination_lid =
			cpu_to_be16(ah->av.ib.g_slid & 0x7f);
		sqp->ud_header.lrh.source_lid =
			cpu_to_be16(ah->av.ib.g_slid & 0x7f);
	पूर्ण

	mlx->flags &= cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE);

	/* क्रमce loopback */
	mlx->flags |= cpu_to_be32(MLX4_WQE_MLX_VL15 | 0x1 | MLX4_WQE_MLX_SLR);
	mlx->rlid = sqp->ud_header.lrh.destination_lid;

	sqp->ud_header.lrh.भव_lane    = 0;
	sqp->ud_header.bth.solicited_event = !!(wr->wr.send_flags & IB_SEND_SOLICITED);
	err = ib_get_cached_pkey(ib_dev, qp->port, 0, &pkey);
	अगर (err)
		वापस err;
	sqp->ud_header.bth.pkey = cpu_to_be16(pkey);
	अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_TUN_SMI_OWNER)
		sqp->ud_header.bth.destination_qpn = cpu_to_be32(wr->remote_qpn);
	अन्यथा
		sqp->ud_header.bth.destination_qpn =
			cpu_to_be32(mdev->dev->caps.spec_qps[qp->port - 1].qp0_tunnel);

	sqp->ud_header.bth.psn = cpu_to_be32((sqp->send_psn++) & ((1 << 24) - 1));
	अगर (mlx4_is_master(mdev->dev)) अणु
		अगर (mlx4_get_parav_qkey(mdev->dev, qp->mqp.qpn, &qkey))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (vf_get_qp0_qkey(mdev->dev, qp->mqp.qpn, &qkey))
			वापस -EINVAL;
	पूर्ण
	sqp->ud_header.deth.qkey = cpu_to_be32(qkey);
	sqp->ud_header.deth.source_qpn = cpu_to_be32(qp->mqp.qpn);

	sqp->ud_header.bth.opcode        = IB_OPCODE_UD_SEND_ONLY;
	sqp->ud_header.immediate_present = 0;

	header_size = ib_ud_header_pack(&sqp->ud_header, sqp->header_buf);

	/*
	 * Inline data segments may not cross a 64 byte boundary.  If
	 * our UD header is bigger than the space available up to the
	 * next 64 byte boundary in the WQE, use two अंतरभूत data
	 * segments to hold the UD header.
	 */
	spc = MLX4_INLINE_ALIGN -
	      ((अचिन्हित दीर्घ) (inl + 1) & (MLX4_INLINE_ALIGN - 1));
	अगर (header_size <= spc) अणु
		inl->byte_count = cpu_to_be32(1 << 31 | header_size);
		स_नकल(inl + 1, sqp->header_buf, header_size);
		i = 1;
	पूर्ण अन्यथा अणु
		inl->byte_count = cpu_to_be32(1 << 31 | spc);
		स_नकल(inl + 1, sqp->header_buf, spc);

		inl = (व्योम *) (inl + 1) + spc;
		स_नकल(inl + 1, sqp->header_buf + spc, header_size - spc);
		/*
		 * Need a barrier here to make sure all the data is
		 * visible beक्रमe the byte_count field is set.
		 * Otherwise the HCA prefetcher could grab the 64-byte
		 * chunk with this अंतरभूत segment and get a valid (!=
		 * 0xffffffff) byte count but stale data, and end up
		 * generating a packet with bad headers.
		 *
		 * The first अंतरभूत segment's byte_count field doesn't
		 * need a barrier, because it comes after a
		 * control/MLX segment and thereक्रमe is at an offset
		 * of 16 mod 64.
		 */
		wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | (header_size - spc));
		i = 2;
	पूर्ण

	*mlx_seg_len =
	ALIGN(i * माप (काष्ठा mlx4_wqe_अंतरभूत_seg) + header_size, 16);
	वापस 0;
पूर्ण

अटल u8 sl_to_vl(काष्ठा mlx4_ib_dev *dev, u8 sl, पूर्णांक port_num)
अणु
	जोड़ sl2vl_tbl_to_u64 पंचांगp_vltab;
	u8 vl;

	अगर (sl > 15)
		वापस 0xf;
	पंचांगp_vltab.sl64 = atomic64_पढ़ो(&dev->sl2vl[port_num - 1]);
	vl = पंचांगp_vltab.sl8[sl >> 1];
	अगर (sl & 1)
		vl &= 0x0f;
	अन्यथा
		vl >>= 4;
	वापस vl;
पूर्ण

अटल पूर्णांक fill_gid_by_hw_index(काष्ठा mlx4_ib_dev *ibdev, u8 port_num,
				पूर्णांक index, जोड़ ib_gid *gid,
				क्रमागत ib_gid_type *gid_type)
अणु
	काष्ठा mlx4_ib_iboe *iboe = &ibdev->iboe;
	काष्ठा mlx4_port_gid_table *port_gid_table;
	अचिन्हित दीर्घ flags;

	port_gid_table = &iboe->gids[port_num - 1];
	spin_lock_irqsave(&iboe->lock, flags);
	स_नकल(gid, &port_gid_table->gids[index].gid, माप(*gid));
	*gid_type = port_gid_table->gids[index].gid_type;
	spin_unlock_irqrestore(&iboe->lock, flags);
	अगर (rdma_is_zero_gid(gid))
		वापस -ENOENT;

	वापस 0;
पूर्ण

#घोषणा MLX4_ROCEV2_QP1_SPORT 0xC000
अटल पूर्णांक build_mlx_header(काष्ठा mlx4_ib_qp *qp, स्थिर काष्ठा ib_ud_wr *wr,
			    व्योम *wqe, अचिन्हित *mlx_seg_len)
अणु
	काष्ठा mlx4_ib_sqp *sqp = qp->sqp;
	काष्ठा ib_device *ib_dev = qp->ibqp.device;
	काष्ठा mlx4_ib_dev *ibdev = to_mdev(ib_dev);
	काष्ठा mlx4_wqe_mlx_seg *mlx = wqe;
	काष्ठा mlx4_wqe_ctrl_seg *ctrl = wqe;
	काष्ठा mlx4_wqe_अंतरभूत_seg *inl = wqe + माप *mlx;
	काष्ठा mlx4_ib_ah *ah = to_mah(wr->ah);
	जोड़ ib_gid sgid;
	u16 pkey;
	पूर्णांक send_size;
	पूर्णांक header_size;
	पूर्णांक spc;
	पूर्णांक i;
	पूर्णांक err = 0;
	u16 vlan = 0xffff;
	bool is_eth;
	bool is_vlan = false;
	bool is_grh;
	bool is_udp = false;
	पूर्णांक ip_version = 0;

	send_size = 0;
	क्रम (i = 0; i < wr->wr.num_sge; ++i)
		send_size += wr->wr.sg_list[i].length;

	is_eth = rdma_port_get_link_layer(qp->ibqp.device, qp->port) == IB_LINK_LAYER_ETHERNET;
	is_grh = mlx4_ib_ah_grh_present(ah);
	अगर (is_eth) अणु
		क्रमागत ib_gid_type gid_type;
		अगर (mlx4_is_mfunc(to_mdev(ib_dev)->dev)) अणु
			/* When multi-function is enabled, the ib_core gid
			 * indexes करोn't necessarily match the hw ones, so
			 * we must use our own cache */
			err = mlx4_get_roce_gid_from_slave(to_mdev(ib_dev)->dev,
							   be32_to_cpu(ah->av.ib.port_pd) >> 24,
							   ah->av.ib.gid_index, &sgid.raw[0]);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा  अणु
			err = fill_gid_by_hw_index(ibdev, qp->port,
						   ah->av.ib.gid_index, &sgid,
						   &gid_type);
			अगर (!err) अणु
				is_udp = gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP;
				अगर (is_udp) अणु
					अगर (ipv6_addr_v4mapped((काष्ठा in6_addr *)&sgid))
						ip_version = 4;
					अन्यथा
						ip_version = 6;
					is_grh = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				वापस err;
			पूर्ण
		पूर्ण
		अगर (ah->av.eth.vlan != cpu_to_be16(0xffff)) अणु
			vlan = be16_to_cpu(ah->av.eth.vlan) & 0x0fff;
			is_vlan = true;
		पूर्ण
	पूर्ण
	err = ib_ud_header_init(send_size, !is_eth, is_eth, is_vlan, is_grh,
			  ip_version, is_udp, 0, &sqp->ud_header);
	अगर (err)
		वापस err;

	अगर (!is_eth) अणु
		sqp->ud_header.lrh.service_level =
			be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 28;
		sqp->ud_header.lrh.destination_lid = ah->av.ib.dlid;
		sqp->ud_header.lrh.source_lid = cpu_to_be16(ah->av.ib.g_slid & 0x7f);
	पूर्ण

	अगर (is_grh || (ip_version == 6)) अणु
		sqp->ud_header.grh.traffic_class =
			(be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 20) & 0xff;
		sqp->ud_header.grh.flow_label    =
			ah->av.ib.sl_tclass_flowlabel & cpu_to_be32(0xfffff);
		sqp->ud_header.grh.hop_limit     = ah->av.ib.hop_limit;
		अगर (is_eth) अणु
			स_नकल(sqp->ud_header.grh.source_gid.raw, sgid.raw, 16);
		पूर्ण अन्यथा अणु
			अगर (mlx4_is_mfunc(to_mdev(ib_dev)->dev)) अणु
				/* When multi-function is enabled, the ib_core gid
				 * indexes करोn't necessarily match the hw ones, so
				 * we must use our own cache
				 */
				sqp->ud_header.grh.source_gid.global
					.subnet_prefix =
					cpu_to_be64(atomic64_पढ़ो(
						&(to_mdev(ib_dev)
							  ->sriov
							  .demux[qp->port - 1]
							  .subnet_prefix)));
				sqp->ud_header.grh.source_gid.global
					.पूर्णांकerface_id =
					to_mdev(ib_dev)
						->sriov.demux[qp->port - 1]
						.guid_cache[ah->av.ib.gid_index];
			पूर्ण अन्यथा अणु
				sqp->ud_header.grh.source_gid =
					ah->ibah.sgid_attr->gid;
			पूर्ण
		पूर्ण
		स_नकल(sqp->ud_header.grh.destination_gid.raw,
		       ah->av.ib.dgid, 16);
	पूर्ण

	अगर (ip_version == 4) अणु
		sqp->ud_header.ip4.tos =
			(be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 20) & 0xff;
		sqp->ud_header.ip4.id = 0;
		sqp->ud_header.ip4.frag_off = htons(IP_DF);
		sqp->ud_header.ip4.ttl = ah->av.eth.hop_limit;

		स_नकल(&sqp->ud_header.ip4.saddr,
		       sgid.raw + 12, 4);
		स_नकल(&sqp->ud_header.ip4.daddr, ah->av.ib.dgid + 12, 4);
		sqp->ud_header.ip4.check = ib_ud_ip4_csum(&sqp->ud_header);
	पूर्ण

	अगर (is_udp) अणु
		sqp->ud_header.udp.dport = htons(ROCE_V2_UDP_DPORT);
		sqp->ud_header.udp.sport = htons(MLX4_ROCEV2_QP1_SPORT);
		sqp->ud_header.udp.csum = 0;
	पूर्ण

	mlx->flags &= cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE);

	अगर (!is_eth) अणु
		mlx->flags |=
			cpu_to_be32((!qp->ibqp.qp_num ? MLX4_WQE_MLX_VL15 : 0) |
				    (sqp->ud_header.lrh.destination_lid ==
						     IB_LID_PERMISSIVE ?
					     MLX4_WQE_MLX_SLR :
					     0) |
				    (sqp->ud_header.lrh.service_level << 8));
		अगर (ah->av.ib.port_pd & cpu_to_be32(0x80000000))
			mlx->flags |= cpu_to_be32(0x1); /* क्रमce loopback */
		mlx->rlid = sqp->ud_header.lrh.destination_lid;
	पूर्ण

	चयन (wr->wr.opcode) अणु
	हाल IB_WR_SEND:
		sqp->ud_header.bth.opcode	 = IB_OPCODE_UD_SEND_ONLY;
		sqp->ud_header.immediate_present = 0;
		अवरोध;
	हाल IB_WR_SEND_WITH_IMM:
		sqp->ud_header.bth.opcode	 = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
		sqp->ud_header.immediate_present = 1;
		sqp->ud_header.immediate_data    = wr->wr.ex.imm_data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (is_eth) अणु
		u16 ether_type;
		u16 pcp = (be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 29) << 13;

		ether_type = (!is_udp) ? ETH_P_IBOE:
			(ip_version == 4 ? ETH_P_IP : ETH_P_IPV6);

		mlx->sched_prio = cpu_to_be16(pcp);

		ether_addr_copy(sqp->ud_header.eth.smac_h, ah->av.eth.s_mac);
		स_नकल(sqp->ud_header.eth.dmac_h, ah->av.eth.mac, 6);
		स_नकल(&ctrl->srcrb_flags16[0], ah->av.eth.mac, 2);
		स_नकल(&ctrl->imm, ah->av.eth.mac + 2, 4);

		अगर (!स_भेद(sqp->ud_header.eth.smac_h, sqp->ud_header.eth.dmac_h, 6))
			mlx->flags |= cpu_to_be32(MLX4_WQE_CTRL_FORCE_LOOPBACK);
		अगर (!is_vlan) अणु
			sqp->ud_header.eth.type = cpu_to_be16(ether_type);
		पूर्ण अन्यथा अणु
			sqp->ud_header.vlan.type = cpu_to_be16(ether_type);
			sqp->ud_header.vlan.tag = cpu_to_be16(vlan | pcp);
		पूर्ण
	पूर्ण अन्यथा अणु
		sqp->ud_header.lrh.भव_lane =
			!qp->ibqp.qp_num ?
				15 :
				sl_to_vl(to_mdev(ib_dev),
					 sqp->ud_header.lrh.service_level,
					 qp->port);
		अगर (qp->ibqp.qp_num && sqp->ud_header.lrh.भव_lane == 15)
			वापस -EINVAL;
		अगर (sqp->ud_header.lrh.destination_lid == IB_LID_PERMISSIVE)
			sqp->ud_header.lrh.source_lid = IB_LID_PERMISSIVE;
	पूर्ण
	sqp->ud_header.bth.solicited_event = !!(wr->wr.send_flags & IB_SEND_SOLICITED);
	अगर (!qp->ibqp.qp_num)
		err = ib_get_cached_pkey(ib_dev, qp->port, sqp->pkey_index,
					 &pkey);
	अन्यथा
		err = ib_get_cached_pkey(ib_dev, qp->port, wr->pkey_index,
					 &pkey);
	अगर (err)
		वापस err;

	sqp->ud_header.bth.pkey = cpu_to_be16(pkey);
	sqp->ud_header.bth.destination_qpn = cpu_to_be32(wr->remote_qpn);
	sqp->ud_header.bth.psn = cpu_to_be32((sqp->send_psn++) & ((1 << 24) - 1));
	sqp->ud_header.deth.qkey = cpu_to_be32(wr->remote_qkey & 0x80000000 ?
					       sqp->qkey : wr->remote_qkey);
	sqp->ud_header.deth.source_qpn = cpu_to_be32(qp->ibqp.qp_num);

	header_size = ib_ud_header_pack(&sqp->ud_header, sqp->header_buf);

	अगर (0) अणु
		pr_err("built UD header of size %d:\n", header_size);
		क्रम (i = 0; i < header_size / 4; ++i) अणु
			अगर (i % 8 == 0)
				pr_err("  [%02x] ", i * 4);
			pr_cont(" %08x",
				be32_to_cpu(((__be32 *) sqp->header_buf)[i]));
			अगर ((i + 1) % 8 == 0)
				pr_cont("\n");
		पूर्ण
		pr_err("\n");
	पूर्ण

	/*
	 * Inline data segments may not cross a 64 byte boundary.  If
	 * our UD header is bigger than the space available up to the
	 * next 64 byte boundary in the WQE, use two अंतरभूत data
	 * segments to hold the UD header.
	 */
	spc = MLX4_INLINE_ALIGN -
		((अचिन्हित दीर्घ) (inl + 1) & (MLX4_INLINE_ALIGN - 1));
	अगर (header_size <= spc) अणु
		inl->byte_count = cpu_to_be32(1 << 31 | header_size);
		स_नकल(inl + 1, sqp->header_buf, header_size);
		i = 1;
	पूर्ण अन्यथा अणु
		inl->byte_count = cpu_to_be32(1 << 31 | spc);
		स_नकल(inl + 1, sqp->header_buf, spc);

		inl = (व्योम *) (inl + 1) + spc;
		स_नकल(inl + 1, sqp->header_buf + spc, header_size - spc);
		/*
		 * Need a barrier here to make sure all the data is
		 * visible beक्रमe the byte_count field is set.
		 * Otherwise the HCA prefetcher could grab the 64-byte
		 * chunk with this अंतरभूत segment and get a valid (!=
		 * 0xffffffff) byte count but stale data, and end up
		 * generating a packet with bad headers.
		 *
		 * The first अंतरभूत segment's byte_count field doesn't
		 * need a barrier, because it comes after a
		 * control/MLX segment and thereक्रमe is at an offset
		 * of 16 mod 64.
		 */
		wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | (header_size - spc));
		i = 2;
	पूर्ण

	*mlx_seg_len =
		ALIGN(i * माप (काष्ठा mlx4_wqe_अंतरभूत_seg) + header_size, 16);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_wq_overflow(काष्ठा mlx4_ib_wq *wq, पूर्णांक nreq, काष्ठा ib_cq *ib_cq)
अणु
	अचिन्हित cur;
	काष्ठा mlx4_ib_cq *cq;

	cur = wq->head - wq->tail;
	अगर (likely(cur + nreq < wq->max_post))
		वापस 0;

	cq = to_mcq(ib_cq);
	spin_lock(&cq->lock);
	cur = wq->head - wq->tail;
	spin_unlock(&cq->lock);

	वापस cur + nreq >= wq->max_post;
पूर्ण

अटल __be32 convert_access(पूर्णांक acc)
अणु
	वापस (acc & IB_ACCESS_REMOTE_ATOMIC ?
		cpu_to_be32(MLX4_WQE_FMR_AND_BIND_PERM_ATOMIC)       : 0) |
	       (acc & IB_ACCESS_REMOTE_WRITE  ?
		cpu_to_be32(MLX4_WQE_FMR_AND_BIND_PERM_REMOTE_WRITE) : 0) |
	       (acc & IB_ACCESS_REMOTE_READ   ?
		cpu_to_be32(MLX4_WQE_FMR_AND_BIND_PERM_REMOTE_READ)  : 0) |
	       (acc & IB_ACCESS_LOCAL_WRITE   ? cpu_to_be32(MLX4_WQE_FMR_PERM_LOCAL_WRITE)  : 0) |
		cpu_to_be32(MLX4_WQE_FMR_PERM_LOCAL_READ);
पूर्ण

अटल व्योम set_reg_seg(काष्ठा mlx4_wqe_fmr_seg *fseg,
			स्थिर काष्ठा ib_reg_wr *wr)
अणु
	काष्ठा mlx4_ib_mr *mr = to_mmr(wr->mr);

	fseg->flags		= convert_access(wr->access);
	fseg->mem_key		= cpu_to_be32(wr->key);
	fseg->buf_list		= cpu_to_be64(mr->page_map);
	fseg->start_addr	= cpu_to_be64(mr->ibmr.iova);
	fseg->reg_len		= cpu_to_be64(mr->ibmr.length);
	fseg->offset		= 0; /* XXX -- is this just क्रम ZBVA? */
	fseg->page_size		= cpu_to_be32(ilog2(mr->ibmr.page_size));
	fseg->reserved[0]	= 0;
	fseg->reserved[1]	= 0;
पूर्ण

अटल व्योम set_local_inv_seg(काष्ठा mlx4_wqe_local_inval_seg *iseg, u32 rkey)
अणु
	स_रखो(iseg, 0, माप(*iseg));
	iseg->mem_key = cpu_to_be32(rkey);
पूर्ण

अटल __always_अंतरभूत व्योम set_raddr_seg(काष्ठा mlx4_wqe_raddr_seg *rseg,
					  u64 remote_addr, u32 rkey)
अणु
	rseg->raddr    = cpu_to_be64(remote_addr);
	rseg->rkey     = cpu_to_be32(rkey);
	rseg->reserved = 0;
पूर्ण

अटल व्योम set_atomic_seg(काष्ठा mlx4_wqe_atomic_seg *aseg,
			   स्थिर काष्ठा ib_atomic_wr *wr)
अणु
	अगर (wr->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP) अणु
		aseg->swap_add = cpu_to_be64(wr->swap);
		aseg->compare  = cpu_to_be64(wr->compare_add);
	पूर्ण अन्यथा अगर (wr->wr.opcode == IB_WR_MASKED_ATOMIC_FETCH_AND_ADD) अणु
		aseg->swap_add = cpu_to_be64(wr->compare_add);
		aseg->compare  = cpu_to_be64(wr->compare_add_mask);
	पूर्ण अन्यथा अणु
		aseg->swap_add = cpu_to_be64(wr->compare_add);
		aseg->compare  = 0;
	पूर्ण

पूर्ण

अटल व्योम set_masked_atomic_seg(काष्ठा mlx4_wqe_masked_atomic_seg *aseg,
				  स्थिर काष्ठा ib_atomic_wr *wr)
अणु
	aseg->swap_add		= cpu_to_be64(wr->swap);
	aseg->swap_add_mask	= cpu_to_be64(wr->swap_mask);
	aseg->compare		= cpu_to_be64(wr->compare_add);
	aseg->compare_mask	= cpu_to_be64(wr->compare_add_mask);
पूर्ण

अटल व्योम set_datagram_seg(काष्ठा mlx4_wqe_datagram_seg *dseg,
			     स्थिर काष्ठा ib_ud_wr *wr)
अणु
	स_नकल(dseg->av, &to_mah(wr->ah)->av, माप (काष्ठा mlx4_av));
	dseg->dqpn = cpu_to_be32(wr->remote_qpn);
	dseg->qkey = cpu_to_be32(wr->remote_qkey);
	dseg->vlan = to_mah(wr->ah)->av.eth.vlan;
	स_नकल(dseg->mac, to_mah(wr->ah)->av.eth.mac, 6);
पूर्ण

अटल व्योम set_tunnel_datagram_seg(काष्ठा mlx4_ib_dev *dev,
				    काष्ठा mlx4_wqe_datagram_seg *dseg,
				    स्थिर काष्ठा ib_ud_wr *wr,
				    क्रमागत mlx4_ib_qp_type qpt)
अणु
	जोड़ mlx4_ext_av *av = &to_mah(wr->ah)->av;
	काष्ठा mlx4_av sqp_av = अणु0पूर्ण;
	पूर्णांक port = *((u8 *) &av->ib.port_pd) & 0x3;

	/* क्रमce loopback */
	sqp_av.port_pd = av->ib.port_pd | cpu_to_be32(0x80000000);
	sqp_av.g_slid = av->ib.g_slid & 0x7f; /* no GRH */
	sqp_av.sl_tclass_flowlabel = av->ib.sl_tclass_flowlabel &
			cpu_to_be32(0xf0000000);

	स_नकल(dseg->av, &sqp_av, माप (काष्ठा mlx4_av));
	अगर (qpt == MLX4_IB_QPT_PROXY_GSI)
		dseg->dqpn = cpu_to_be32(dev->dev->caps.spec_qps[port - 1].qp1_tunnel);
	अन्यथा
		dseg->dqpn = cpu_to_be32(dev->dev->caps.spec_qps[port - 1].qp0_tunnel);
	/* Use QKEY from the QP context, which is set by master */
	dseg->qkey = cpu_to_be32(IB_QP_SET_QKEY);
पूर्ण

अटल व्योम build_tunnel_header(स्थिर काष्ठा ib_ud_wr *wr, व्योम *wqe,
				अचिन्हित *mlx_seg_len)
अणु
	काष्ठा mlx4_wqe_अंतरभूत_seg *inl = wqe;
	काष्ठा mlx4_ib_tunnel_header hdr;
	काष्ठा mlx4_ib_ah *ah = to_mah(wr->ah);
	पूर्णांक spc;
	पूर्णांक i;

	स_नकल(&hdr.av, &ah->av, माप hdr.av);
	hdr.remote_qpn = cpu_to_be32(wr->remote_qpn);
	hdr.pkey_index = cpu_to_be16(wr->pkey_index);
	hdr.qkey = cpu_to_be32(wr->remote_qkey);
	स_नकल(hdr.mac, ah->av.eth.mac, 6);
	hdr.vlan = ah->av.eth.vlan;

	spc = MLX4_INLINE_ALIGN -
		((अचिन्हित दीर्घ) (inl + 1) & (MLX4_INLINE_ALIGN - 1));
	अगर (माप (hdr) <= spc) अणु
		स_नकल(inl + 1, &hdr, माप (hdr));
		wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | माप (hdr));
		i = 1;
	पूर्ण अन्यथा अणु
		स_नकल(inl + 1, &hdr, spc);
		wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | spc);

		inl = (व्योम *) (inl + 1) + spc;
		स_नकल(inl + 1, (व्योम *) &hdr + spc, माप (hdr) - spc);
		wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | (माप (hdr) - spc));
		i = 2;
	पूर्ण

	*mlx_seg_len =
		ALIGN(i * माप (काष्ठा mlx4_wqe_अंतरभूत_seg) + माप (hdr), 16);
पूर्ण

अटल व्योम set_mlx_icrc_seg(व्योम *dseg)
अणु
	u32 *t = dseg;
	काष्ठा mlx4_wqe_अंतरभूत_seg *iseg = dseg;

	t[1] = 0;

	/*
	 * Need a barrier here beक्रमe writing the byte_count field to
	 * make sure that all the data is visible beक्रमe the
	 * byte_count field is set.  Otherwise, अगर the segment begins
	 * a new cacheline, the HCA prefetcher could grab the 64-byte
	 * chunk and get a valid (!= * 0xffffffff) byte count but
	 * stale data, and end up sending the wrong data.
	 */
	wmb();

	iseg->byte_count = cpu_to_be32((1 << 31) | 4);
पूर्ण

अटल व्योम set_data_seg(काष्ठा mlx4_wqe_data_seg *dseg, काष्ठा ib_sge *sg)
अणु
	dseg->lkey       = cpu_to_be32(sg->lkey);
	dseg->addr       = cpu_to_be64(sg->addr);

	/*
	 * Need a barrier here beक्रमe writing the byte_count field to
	 * make sure that all the data is visible beक्रमe the
	 * byte_count field is set.  Otherwise, अगर the segment begins
	 * a new cacheline, the HCA prefetcher could grab the 64-byte
	 * chunk and get a valid (!= * 0xffffffff) byte count but
	 * stale data, and end up sending the wrong data.
	 */
	wmb();

	dseg->byte_count = cpu_to_be32(sg->length);
पूर्ण

अटल व्योम __set_data_seg(काष्ठा mlx4_wqe_data_seg *dseg, काष्ठा ib_sge *sg)
अणु
	dseg->byte_count = cpu_to_be32(sg->length);
	dseg->lkey       = cpu_to_be32(sg->lkey);
	dseg->addr       = cpu_to_be64(sg->addr);
पूर्ण

अटल पूर्णांक build_lso_seg(काष्ठा mlx4_wqe_lso_seg *wqe,
			 स्थिर काष्ठा ib_ud_wr *wr, काष्ठा mlx4_ib_qp *qp,
			 अचिन्हित *lso_seg_len, __be32 *lso_hdr_sz, __be32 *blh)
अणु
	अचिन्हित halign = ALIGN(माप *wqe + wr->hlen, 16);

	अगर (unlikely(halign > MLX4_IB_CACHE_LINE_SIZE))
		*blh = cpu_to_be32(1 << 6);

	अगर (unlikely(!(qp->flags & MLX4_IB_QP_LSO) &&
		     wr->wr.num_sge > qp->sq.max_gs - (halign >> 4)))
		वापस -EINVAL;

	स_नकल(wqe->header, wr->header, wr->hlen);

	*lso_hdr_sz  = cpu_to_be32(wr->mss << 16 | wr->hlen);
	*lso_seg_len = halign;
	वापस 0;
पूर्ण

अटल __be32 send_ieth(स्थिर काष्ठा ib_send_wr *wr)
अणु
	चयन (wr->opcode) अणु
	हाल IB_WR_SEND_WITH_IMM:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		वापस wr->ex.imm_data;

	हाल IB_WR_SEND_WITH_INV:
		वापस cpu_to_be32(wr->ex.invalidate_rkey);

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम add_zero_len_अंतरभूत(व्योम *wqe)
अणु
	काष्ठा mlx4_wqe_अंतरभूत_seg *inl = wqe;
	स_रखो(wqe, 0, 16);
	inl->byte_count = cpu_to_be32(1 << 31);
पूर्ण

अटल पूर्णांक _mlx4_ib_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			      स्थिर काष्ठा ib_send_wr **bad_wr, bool drain)
अणु
	काष्ठा mlx4_ib_qp *qp = to_mqp(ibqp);
	व्योम *wqe;
	काष्ठा mlx4_wqe_ctrl_seg *ctrl;
	काष्ठा mlx4_wqe_data_seg *dseg;
	अचिन्हित दीर्घ flags;
	पूर्णांक nreq;
	पूर्णांक err = 0;
	अचिन्हित ind;
	पूर्णांक size;
	अचिन्हित seglen;
	__be32 dummy;
	__be32 *lso_wqe;
	__be32 lso_hdr_sz;
	__be32 blh;
	पूर्णांक i;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibqp->device);

	अगर (qp->mlx4_ib_qp_type == MLX4_IB_QPT_GSI) अणु
		काष्ठा mlx4_ib_sqp *sqp = qp->sqp;

		अगर (sqp->roce_v2_gsi) अणु
			काष्ठा mlx4_ib_ah *ah = to_mah(ud_wr(wr)->ah);
			क्रमागत ib_gid_type gid_type;
			जोड़ ib_gid gid;

			अगर (!fill_gid_by_hw_index(mdev, qp->port,
					   ah->av.ib.gid_index,
					   &gid, &gid_type))
				qp = (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) ?
						to_mqp(sqp->roce_v2_gsi) : qp;
			अन्यथा
				pr_err("Failed to get gid at index %d. RoCEv2 will not work properly\n",
				       ah->av.ib.gid_index);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&qp->sq.lock, flags);
	अगर (mdev->dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR &&
	    !drain) अणु
		err = -EIO;
		*bad_wr = wr;
		nreq = 0;
		जाओ out;
	पूर्ण

	ind = qp->sq_next_wqe;

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		lso_wqe = &dummy;
		blh = 0;

		अगर (mlx4_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)) अणु
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		अगर (unlikely(wr->num_sge > qp->sq.max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		ctrl = wqe = get_send_wqe(qp, ind & (qp->sq.wqe_cnt - 1));
		qp->sq.wrid[(qp->sq.head + nreq) & (qp->sq.wqe_cnt - 1)] = wr->wr_id;

		ctrl->srcrb_flags =
			(wr->send_flags & IB_SEND_SIGNALED ?
			 cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE) : 0) |
			(wr->send_flags & IB_SEND_SOLICITED ?
			 cpu_to_be32(MLX4_WQE_CTRL_SOLICITED) : 0) |
			((wr->send_flags & IB_SEND_IP_CSUM) ?
			 cpu_to_be32(MLX4_WQE_CTRL_IP_CSUM |
				     MLX4_WQE_CTRL_TCP_UDP_CSUM) : 0) |
			qp->sq_संकेत_bits;

		ctrl->imm = send_ieth(wr);

		wqe += माप *ctrl;
		size = माप *ctrl / 16;

		चयन (qp->mlx4_ib_qp_type) अणु
		हाल MLX4_IB_QPT_RC:
		हाल MLX4_IB_QPT_UC:
			चयन (wr->opcode) अणु
			हाल IB_WR_ATOMIC_CMP_AND_SWP:
			हाल IB_WR_ATOMIC_FETCH_AND_ADD:
			हाल IB_WR_MASKED_ATOMIC_FETCH_AND_ADD:
				set_raddr_seg(wqe, atomic_wr(wr)->remote_addr,
					      atomic_wr(wr)->rkey);
				wqe  += माप (काष्ठा mlx4_wqe_raddr_seg);

				set_atomic_seg(wqe, atomic_wr(wr));
				wqe  += माप (काष्ठा mlx4_wqe_atomic_seg);

				size += (माप (काष्ठा mlx4_wqe_raddr_seg) +
					 माप (काष्ठा mlx4_wqe_atomic_seg)) / 16;

				अवरोध;

			हाल IB_WR_MASKED_ATOMIC_CMP_AND_SWP:
				set_raddr_seg(wqe, atomic_wr(wr)->remote_addr,
					      atomic_wr(wr)->rkey);
				wqe  += माप (काष्ठा mlx4_wqe_raddr_seg);

				set_masked_atomic_seg(wqe, atomic_wr(wr));
				wqe  += माप (काष्ठा mlx4_wqe_masked_atomic_seg);

				size += (माप (काष्ठा mlx4_wqe_raddr_seg) +
					 माप (काष्ठा mlx4_wqe_masked_atomic_seg)) / 16;

				अवरोध;

			हाल IB_WR_RDMA_READ:
			हाल IB_WR_RDMA_WRITE:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
				set_raddr_seg(wqe, rdma_wr(wr)->remote_addr,
					      rdma_wr(wr)->rkey);
				wqe  += माप (काष्ठा mlx4_wqe_raddr_seg);
				size += माप (काष्ठा mlx4_wqe_raddr_seg) / 16;
				अवरोध;

			हाल IB_WR_LOCAL_INV:
				ctrl->srcrb_flags |=
					cpu_to_be32(MLX4_WQE_CTRL_STRONG_ORDER);
				set_local_inv_seg(wqe, wr->ex.invalidate_rkey);
				wqe  += माप (काष्ठा mlx4_wqe_local_inval_seg);
				size += माप (काष्ठा mlx4_wqe_local_inval_seg) / 16;
				अवरोध;

			हाल IB_WR_REG_MR:
				ctrl->srcrb_flags |=
					cpu_to_be32(MLX4_WQE_CTRL_STRONG_ORDER);
				set_reg_seg(wqe, reg_wr(wr));
				wqe  += माप(काष्ठा mlx4_wqe_fmr_seg);
				size += माप(काष्ठा mlx4_wqe_fmr_seg) / 16;
				अवरोध;

			शेष:
				/* No extra segments required क्रम sends */
				अवरोध;
			पूर्ण
			अवरोध;

		हाल MLX4_IB_QPT_TUN_SMI_OWNER:
			err = build_sriov_qp0_header(qp, ud_wr(wr), ctrl,
						     &seglen);
			अगर (unlikely(err)) अणु
				*bad_wr = wr;
				जाओ out;
			पूर्ण
			wqe  += seglen;
			size += seglen / 16;
			अवरोध;
		हाल MLX4_IB_QPT_TUN_SMI:
		हाल MLX4_IB_QPT_TUN_GSI:
			/* this is a UD qp used in MAD responses to slaves. */
			set_datagram_seg(wqe, ud_wr(wr));
			/* set the क्रमced-loopback bit in the data seg av */
			*(__be32 *) wqe |= cpu_to_be32(0x80000000);
			wqe  += माप (काष्ठा mlx4_wqe_datagram_seg);
			size += माप (काष्ठा mlx4_wqe_datagram_seg) / 16;
			अवरोध;
		हाल MLX4_IB_QPT_UD:
			set_datagram_seg(wqe, ud_wr(wr));
			wqe  += माप (काष्ठा mlx4_wqe_datagram_seg);
			size += माप (काष्ठा mlx4_wqe_datagram_seg) / 16;

			अगर (wr->opcode == IB_WR_LSO) अणु
				err = build_lso_seg(wqe, ud_wr(wr), qp, &seglen,
						&lso_hdr_sz, &blh);
				अगर (unlikely(err)) अणु
					*bad_wr = wr;
					जाओ out;
				पूर्ण
				lso_wqe = (__be32 *) wqe;
				wqe  += seglen;
				size += seglen / 16;
			पूर्ण
			अवरोध;

		हाल MLX4_IB_QPT_PROXY_SMI_OWNER:
			err = build_sriov_qp0_header(qp, ud_wr(wr), ctrl,
						     &seglen);
			अगर (unlikely(err)) अणु
				*bad_wr = wr;
				जाओ out;
			पूर्ण
			wqe  += seglen;
			size += seglen / 16;
			/* to start tunnel header on a cache-line boundary */
			add_zero_len_अंतरभूत(wqe);
			wqe += 16;
			size++;
			build_tunnel_header(ud_wr(wr), wqe, &seglen);
			wqe  += seglen;
			size += seglen / 16;
			अवरोध;
		हाल MLX4_IB_QPT_PROXY_SMI:
		हाल MLX4_IB_QPT_PROXY_GSI:
			/* If we are tunneling special qps, this is a UD qp.
			 * In this हाल we first add a UD segment targeting
			 * the tunnel qp, and then add a header with address
			 * inक्रमmation */
			set_tunnel_datagram_seg(to_mdev(ibqp->device), wqe,
						ud_wr(wr),
						qp->mlx4_ib_qp_type);
			wqe  += माप (काष्ठा mlx4_wqe_datagram_seg);
			size += माप (काष्ठा mlx4_wqe_datagram_seg) / 16;
			build_tunnel_header(ud_wr(wr), wqe, &seglen);
			wqe  += seglen;
			size += seglen / 16;
			अवरोध;

		हाल MLX4_IB_QPT_SMI:
		हाल MLX4_IB_QPT_GSI:
			err = build_mlx_header(qp, ud_wr(wr), ctrl, &seglen);
			अगर (unlikely(err)) अणु
				*bad_wr = wr;
				जाओ out;
			पूर्ण
			wqe  += seglen;
			size += seglen / 16;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		/*
		 * Write data segments in reverse order, so as to
		 * overग_लिखो cacheline stamp last within each
		 * cacheline.  This aव्योमs issues with WQE
		 * prefetching.
		 */

		dseg = wqe;
		dseg += wr->num_sge - 1;
		size += wr->num_sge * (माप (काष्ठा mlx4_wqe_data_seg) / 16);

		/* Add one more अंतरभूत data segment क्रम ICRC क्रम MLX sends */
		अगर (unlikely(qp->mlx4_ib_qp_type == MLX4_IB_QPT_SMI ||
			     qp->mlx4_ib_qp_type == MLX4_IB_QPT_GSI ||
			     qp->mlx4_ib_qp_type &
			     (MLX4_IB_QPT_PROXY_SMI_OWNER | MLX4_IB_QPT_TUN_SMI_OWNER))) अणु
			set_mlx_icrc_seg(dseg + 1);
			size += माप (काष्ठा mlx4_wqe_data_seg) / 16;
		पूर्ण

		क्रम (i = wr->num_sge - 1; i >= 0; --i, --dseg)
			set_data_seg(dseg, wr->sg_list + i);

		/*
		 * Possibly overग_लिखो stamping in cacheline with LSO
		 * segment only after making sure all data segments
		 * are written.
		 */
		wmb();
		*lso_wqe = lso_hdr_sz;

		ctrl->qpn_vlan.fence_size = (wr->send_flags & IB_SEND_FENCE ?
					     MLX4_WQE_CTRL_FENCE : 0) | size;

		/*
		 * Make sure descriptor is fully written beक्रमe
		 * setting ownership bit (because HW can start
		 * executing as soon as we करो).
		 */
		wmb();

		अगर (wr->opcode < 0 || wr->opcode >= ARRAY_SIZE(mlx4_ib_opcode)) अणु
			*bad_wr = wr;
			err = -EINVAL;
			जाओ out;
		पूर्ण

		ctrl->owner_opcode = mlx4_ib_opcode[wr->opcode] |
			(ind & qp->sq.wqe_cnt ? cpu_to_be32(1 << 31) : 0) | blh;

		/*
		 * We can improve latency by not stamping the last
		 * send queue WQE until after ringing the करोorbell, so
		 * only stamp here अगर there are still more WQEs to post.
		 */
		अगर (wr->next)
			stamp_send_wqe(qp, ind + qp->sq_spare_wqes);
		ind++;
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		qp->sq.head += nreq;

		/*
		 * Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();

		ग_लिखोl_relaxed(qp->करोorbell_qpn,
			to_mdev(ibqp->device)->uar_map + MLX4_SEND_DOORBELL);

		stamp_send_wqe(qp, ind + qp->sq_spare_wqes - 1);

		qp->sq_next_wqe = ind;
	पूर्ण

	spin_unlock_irqrestore(&qp->sq.lock, flags);

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		      स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	वापस _mlx4_ib_post_send(ibqp, wr, bad_wr, false);
पूर्ण

अटल पूर्णांक _mlx4_ib_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
			      स्थिर काष्ठा ib_recv_wr **bad_wr, bool drain)
अणु
	काष्ठा mlx4_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx4_wqe_data_seg *scat;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक ind;
	पूर्णांक max_gs;
	पूर्णांक i;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibqp->device);

	max_gs = qp->rq.max_gs;
	spin_lock_irqsave(&qp->rq.lock, flags);

	अगर (mdev->dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR &&
	    !drain) अणु
		err = -EIO;
		*bad_wr = wr;
		nreq = 0;
		जाओ out;
	पूर्ण

	ind = qp->rq.head & (qp->rq.wqe_cnt - 1);

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (mlx4_wq_overflow(&qp->rq, nreq, qp->ibqp.recv_cq)) अणु
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		अगर (unlikely(wr->num_sge > qp->rq.max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		scat = get_recv_wqe(qp, ind);

		अगर (qp->mlx4_ib_qp_type & (MLX4_IB_QPT_PROXY_SMI_OWNER |
		    MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_GSI)) अणु
			ib_dma_sync_single_क्रम_device(ibqp->device,
						      qp->sqp_proxy_rcv[ind].map,
						      माप (काष्ठा mlx4_ib_proxy_sqp_hdr),
						      DMA_FROM_DEVICE);
			scat->byte_count =
				cpu_to_be32(माप (काष्ठा mlx4_ib_proxy_sqp_hdr));
			/* use dma lkey from upper layer entry */
			scat->lkey = cpu_to_be32(wr->sg_list->lkey);
			scat->addr = cpu_to_be64(qp->sqp_proxy_rcv[ind].map);
			scat++;
			max_gs--;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i)
			__set_data_seg(scat + i, wr->sg_list + i);

		अगर (i < max_gs) अणु
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX4_INVALID_LKEY);
			scat[i].addr       = 0;
		पूर्ण

		qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (qp->rq.wqe_cnt - 1);
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		qp->rq.head += nreq;

		/*
		 * Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();

		*qp->db.db = cpu_to_be32(qp->rq.head & 0xffff);
	पूर्ण

	spin_unlock_irqrestore(&qp->rq.lock, flags);

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	वापस _mlx4_ib_post_recv(ibqp, wr, bad_wr, false);
पूर्ण

अटल अंतरभूत क्रमागत ib_qp_state to_ib_qp_state(क्रमागत mlx4_qp_state mlx4_state)
अणु
	चयन (mlx4_state) अणु
	हाल MLX4_QP_STATE_RST:      वापस IB_QPS_RESET;
	हाल MLX4_QP_STATE_INIT:     वापस IB_QPS_INIT;
	हाल MLX4_QP_STATE_RTR:      वापस IB_QPS_RTR;
	हाल MLX4_QP_STATE_RTS:      वापस IB_QPS_RTS;
	हाल MLX4_QP_STATE_SQ_DRAINING:
	हाल MLX4_QP_STATE_SQD:      वापस IB_QPS_SQD;
	हाल MLX4_QP_STATE_SQER:     वापस IB_QPS_SQE;
	हाल MLX4_QP_STATE_ERR:      वापस IB_QPS_ERR;
	शेष:		     वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत ib_mig_state to_ib_mig_state(पूर्णांक mlx4_mig_state)
अणु
	चयन (mlx4_mig_state) अणु
	हाल MLX4_QP_PM_ARMED:		वापस IB_MIG_ARMED;
	हाल MLX4_QP_PM_REARM:		वापस IB_MIG_REARM;
	हाल MLX4_QP_PM_MIGRATED:	वापस IB_MIG_MIGRATED;
	शेष: वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक to_ib_qp_access_flags(पूर्णांक mlx4_flags)
अणु
	पूर्णांक ib_flags = 0;

	अगर (mlx4_flags & MLX4_QP_BIT_RRE)
		ib_flags |= IB_ACCESS_REMOTE_READ;
	अगर (mlx4_flags & MLX4_QP_BIT_RWE)
		ib_flags |= IB_ACCESS_REMOTE_WRITE;
	अगर (mlx4_flags & MLX4_QP_BIT_RAE)
		ib_flags |= IB_ACCESS_REMOTE_ATOMIC;

	वापस ib_flags;
पूर्ण

अटल व्योम to_rdma_ah_attr(काष्ठा mlx4_ib_dev *ibdev,
			    काष्ठा rdma_ah_attr *ah_attr,
			    काष्ठा mlx4_qp_path *path)
अणु
	काष्ठा mlx4_dev *dev = ibdev->dev;
	u8 port_num = path->sched_queue & 0x40 ? 2 : 1;

	स_रखो(ah_attr, 0, माप(*ah_attr));
	अगर (port_num == 0 || port_num > dev->caps.num_ports)
		वापस;
	ah_attr->type = rdma_ah_find_type(&ibdev->ib_dev, port_num);

	अगर (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE)
		rdma_ah_set_sl(ah_attr, ((path->sched_queue >> 3) & 0x7) |
			       ((path->sched_queue & 4) << 1));
	अन्यथा
		rdma_ah_set_sl(ah_attr, (path->sched_queue >> 2) & 0xf);
	rdma_ah_set_port_num(ah_attr, port_num);

	rdma_ah_set_dlid(ah_attr, be16_to_cpu(path->rlid));
	rdma_ah_set_path_bits(ah_attr, path->grh_mylmc & 0x7f);
	rdma_ah_set_अटल_rate(ah_attr,
				path->अटल_rate ? path->अटल_rate - 5 : 0);
	अगर (path->grh_mylmc & (1 << 7)) अणु
		rdma_ah_set_grh(ah_attr, शून्य,
				be32_to_cpu(path->tclass_flowlabel) & 0xfffff,
				path->mgid_index,
				path->hop_limit,
				(be32_to_cpu(path->tclass_flowlabel)
				 >> 20) & 0xff);
		rdma_ah_set_dgid_raw(ah_attr, path->rgid);
	पूर्ण
पूर्ण

पूर्णांक mlx4_ib_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr, पूर्णांक qp_attr_mask,
		     काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx4_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx4_qp_context context;
	पूर्णांक mlx4_state;
	पूर्णांक err = 0;

	अगर (ibqp->rwq_ind_tbl)
		वापस -EOPNOTSUPP;

	mutex_lock(&qp->mutex);

	अगर (qp->state == IB_QPS_RESET) अणु
		qp_attr->qp_state = IB_QPS_RESET;
		जाओ करोne;
	पूर्ण

	err = mlx4_qp_query(dev->dev, &qp->mqp, &context);
	अगर (err) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	mlx4_state = be32_to_cpu(context.flags) >> 28;

	qp->state		     = to_ib_qp_state(mlx4_state);
	qp_attr->qp_state	     = qp->state;
	qp_attr->path_mtu	     = context.mtu_msgmax >> 5;
	qp_attr->path_mig_state	     =
		to_ib_mig_state((be32_to_cpu(context.flags) >> 11) & 0x3);
	qp_attr->qkey		     = be32_to_cpu(context.qkey);
	qp_attr->rq_psn		     = be32_to_cpu(context.rnr_nextrecvpsn) & 0xffffff;
	qp_attr->sq_psn		     = be32_to_cpu(context.next_send_psn) & 0xffffff;
	qp_attr->dest_qp_num	     = be32_to_cpu(context.remote_qpn) & 0xffffff;
	qp_attr->qp_access_flags     =
		to_ib_qp_access_flags(be32_to_cpu(context.params2));

	अगर (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC ||
	    qp->ibqp.qp_type == IB_QPT_XRC_INI ||
	    qp->ibqp.qp_type == IB_QPT_XRC_TGT) अणु
		to_rdma_ah_attr(dev, &qp_attr->ah_attr, &context.pri_path);
		to_rdma_ah_attr(dev, &qp_attr->alt_ah_attr, &context.alt_path);
		qp_attr->alt_pkey_index = context.alt_path.pkey_index & 0x7f;
		qp_attr->alt_port_num	=
			rdma_ah_get_port_num(&qp_attr->alt_ah_attr);
	पूर्ण

	qp_attr->pkey_index = context.pri_path.pkey_index & 0x7f;
	अगर (qp_attr->qp_state == IB_QPS_INIT)
		qp_attr->port_num = qp->port;
	अन्यथा
		qp_attr->port_num = context.pri_path.sched_queue & 0x40 ? 2 : 1;

	/* qp_attr->en_sqd_async_notअगरy is only applicable in modअगरy qp */
	qp_attr->sq_draining = mlx4_state == MLX4_QP_STATE_SQ_DRAINING;

	qp_attr->max_rd_atomic = 1 << ((be32_to_cpu(context.params1) >> 21) & 0x7);

	qp_attr->max_dest_rd_atomic =
		1 << ((be32_to_cpu(context.params2) >> 21) & 0x7);
	qp_attr->min_rnr_समयr	    =
		(be32_to_cpu(context.rnr_nextrecvpsn) >> 24) & 0x1f;
	qp_attr->समयout	    = context.pri_path.ackto >> 3;
	qp_attr->retry_cnt	    = (be32_to_cpu(context.params1) >> 16) & 0x7;
	qp_attr->rnr_retry	    = (be32_to_cpu(context.params1) >> 13) & 0x7;
	qp_attr->alt_समयout	    = context.alt_path.ackto >> 3;

करोne:
	qp_attr->cur_qp_state	     = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr     = qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge    = qp->rq.max_gs;

	अगर (!ibqp->uobject) अणु
		qp_attr->cap.max_send_wr  = qp->sq.wqe_cnt;
		qp_attr->cap.max_send_sge = qp->sq.max_gs;
	पूर्ण अन्यथा अणु
		qp_attr->cap.max_send_wr  = 0;
		qp_attr->cap.max_send_sge = 0;
	पूर्ण

	/*
	 * We करोn't support अंतरभूत sends क्रम kernel QPs (yet), and we
	 * करोn't know what userspace's value should be.
	 */
	qp_attr->cap.max_अंतरभूत_data = 0;

	qp_init_attr->cap	     = qp_attr->cap;

	qp_init_attr->create_flags = 0;
	अगर (qp->flags & MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK)
		qp_init_attr->create_flags |= IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK;

	अगर (qp->flags & MLX4_IB_QP_LSO)
		qp_init_attr->create_flags |= IB_QP_CREATE_IPOIB_UD_LSO;

	अगर (qp->flags & MLX4_IB_QP_NETIF)
		qp_init_attr->create_flags |= IB_QP_CREATE_NETIF_QP;

	qp_init_attr->sq_sig_type =
		qp->sq_संकेत_bits == cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE) ?
		IB_SIGNAL_ALL_WR : IB_SIGNAL_REQ_WR;

out:
	mutex_unlock(&qp->mutex);
	वापस err;
पूर्ण

काष्ठा ib_wq *mlx4_ib_create_wq(काष्ठा ib_pd *pd,
				काष्ठा ib_wq_init_attr *init_attr,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_dev *dev = to_mdev(pd->device)->dev;
	काष्ठा ib_qp_init_attr ib_qp_init_attr = अणुपूर्ण;
	काष्ठा mlx4_ib_qp *qp;
	काष्ठा mlx4_ib_create_wq ucmd;
	पूर्णांक err, required_cmd_sz;

	अगर (!udata)
		वापस ERR_PTR(-EINVAL);

	required_cmd_sz = दुरत्व(typeof(ucmd), comp_mask) +
			  माप(ucmd.comp_mask);
	अगर (udata->inlen < required_cmd_sz) अणु
		pr_debug("invalid inlen\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (udata->inlen > माप(ucmd) &&
	    !ib_is_udata_cleared(udata, माप(ucmd),
				 udata->inlen - माप(ucmd))) अणु
		pr_debug("inlen is not supported\n");
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	अगर (udata->outlen)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (init_attr->wq_type != IB_WQT_RQ) अणु
		pr_debug("unsupported wq type %d\n", init_attr->wq_type);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	अगर (init_attr->create_flags & ~IB_WQ_FLAGS_SCATTER_FCS ||
	    !(dev->caps.flags & MLX4_DEV_CAP_FLAG_FCS_KEEP)) अणु
		pr_debug("unsupported create_flags %u\n",
			 init_attr->create_flags);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&qp->mutex);
	qp->pri.vid = 0xFFFF;
	qp->alt.vid = 0xFFFF;

	ib_qp_init_attr.qp_context = init_attr->wq_context;
	ib_qp_init_attr.qp_type = IB_QPT_RAW_PACKET;
	ib_qp_init_attr.cap.max_recv_wr = init_attr->max_wr;
	ib_qp_init_attr.cap.max_recv_sge = init_attr->max_sge;
	ib_qp_init_attr.recv_cq = init_attr->cq;
	ib_qp_init_attr.send_cq = ib_qp_init_attr.recv_cq; /* Dummy CQ */

	अगर (init_attr->create_flags & IB_WQ_FLAGS_SCATTER_FCS)
		ib_qp_init_attr.create_flags |= IB_QP_CREATE_SCATTER_FCS;

	err = create_rq(pd, &ib_qp_init_attr, udata, qp);
	अगर (err) अणु
		kमुक्त(qp);
		वापस ERR_PTR(err);
	पूर्ण

	qp->ibwq.event_handler = init_attr->event_handler;
	qp->ibwq.wq_num = qp->mqp.qpn;
	qp->ibwq.state = IB_WQS_RESET;

	वापस &qp->ibwq;
पूर्ण

अटल पूर्णांक ib_wq2qp_state(क्रमागत ib_wq_state state)
अणु
	चयन (state) अणु
	हाल IB_WQS_RESET:
		वापस IB_QPS_RESET;
	हाल IB_WQS_RDY:
		वापस IB_QPS_RTR;
	शेष:
		वापस IB_QPS_ERR;
	पूर्ण
पूर्ण

अटल पूर्णांक _mlx4_ib_modअगरy_wq(काष्ठा ib_wq *ibwq, क्रमागत ib_wq_state new_state,
			      काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_qp *qp = to_mqp((काष्ठा ib_qp *)ibwq);
	क्रमागत ib_qp_state qp_cur_state;
	क्रमागत ib_qp_state qp_new_state;
	पूर्णांक attr_mask;
	पूर्णांक err;

	/* ib_qp.state represents the WQ HW state जबतक ib_wq.state represents
	 * the WQ logic state.
	 */
	qp_cur_state = qp->state;
	qp_new_state = ib_wq2qp_state(new_state);

	अगर (ib_wq2qp_state(new_state) == qp_cur_state)
		वापस 0;

	अगर (new_state == IB_WQS_RDY) अणु
		काष्ठा ib_qp_attr attr = अणुपूर्ण;

		attr.port_num = qp->port;
		attr_mask = IB_QP_PORT;

		err = __mlx4_ib_modअगरy_qp(ibwq, MLX4_IB_RWQ_SRC, &attr,
					  attr_mask, IB_QPS_RESET, IB_QPS_INIT,
					  udata);
		अगर (err) अणु
			pr_debug("WQN=0x%06x failed to apply RST->INIT on the HW QP\n",
				 ibwq->wq_num);
			वापस err;
		पूर्ण

		qp_cur_state = IB_QPS_INIT;
	पूर्ण

	attr_mask = 0;
	err = __mlx4_ib_modअगरy_qp(ibwq, MLX4_IB_RWQ_SRC, शून्य, attr_mask,
				  qp_cur_state,  qp_new_state, udata);

	अगर (err && (qp_cur_state == IB_QPS_INIT)) अणु
		qp_new_state = IB_QPS_RESET;
		अगर (__mlx4_ib_modअगरy_qp(ibwq, MLX4_IB_RWQ_SRC, शून्य,
					attr_mask, IB_QPS_INIT, IB_QPS_RESET,
					udata)) अणु
			pr_warn("WQN=0x%06x failed with reverting HW's resources failure\n",
				ibwq->wq_num);
			qp_new_state = IB_QPS_INIT;
		पूर्ण
	पूर्ण

	qp->state = qp_new_state;

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_modअगरy_wq(काष्ठा ib_wq *ibwq, काष्ठा ib_wq_attr *wq_attr,
		      u32 wq_attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_qp *qp = to_mqp((काष्ठा ib_qp *)ibwq);
	काष्ठा mlx4_ib_modअगरy_wq ucmd = अणुपूर्ण;
	माप_प्रकार required_cmd_sz;
	क्रमागत ib_wq_state cur_state, new_state;
	पूर्णांक err = 0;

	required_cmd_sz = दुरत्व(typeof(ucmd), reserved) +
				   माप(ucmd.reserved);
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

	अगर (wq_attr_mask & IB_WQ_FLAGS)
		वापस -EOPNOTSUPP;

	cur_state = wq_attr_mask & IB_WQ_CUR_STATE ? wq_attr->curr_wq_state :
						     ibwq->state;
	new_state = wq_attr_mask & IB_WQ_STATE ? wq_attr->wq_state : cur_state;

	अगर (cur_state  < IB_WQS_RESET || cur_state  > IB_WQS_ERR ||
	    new_state < IB_WQS_RESET || new_state > IB_WQS_ERR)
		वापस -EINVAL;

	अगर ((new_state == IB_WQS_RDY) && (cur_state == IB_WQS_ERR))
		वापस -EINVAL;

	अगर ((new_state == IB_WQS_ERR) && (cur_state == IB_WQS_RESET))
		वापस -EINVAL;

	/* Need to protect against the parent RSS which also may modअगरy WQ
	 * state.
	 */
	mutex_lock(&qp->mutex);

	/* Can update HW state only अगर a RSS QP has alपढ़ोy associated to this
	 * WQ, so we can apply its port on the WQ.
	 */
	अगर (qp->rss_usecnt)
		err = _mlx4_ib_modअगरy_wq(ibwq, new_state, udata);

	अगर (!err)
		ibwq->state = new_state;

	mutex_unlock(&qp->mutex);

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_destroy_wq(काष्ठा ib_wq *ibwq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibwq->device);
	काष्ठा mlx4_ib_qp *qp = to_mqp((काष्ठा ib_qp *)ibwq);

	अगर (qp->counter_index)
		mlx4_ib_मुक्त_qp_counter(dev, qp);

	destroy_qp_common(dev, qp, MLX4_IB_RWQ_SRC, udata);

	kमुक्त(qp);
	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_create_rwq_ind_table(काष्ठा ib_rwq_ind_table *rwq_ind_table,
				 काष्ठा ib_rwq_ind_table_init_attr *init_attr,
				 काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_create_rwq_ind_tbl_resp resp = अणुपूर्ण;
	अचिन्हित पूर्णांक ind_tbl_size = 1 << init_attr->log_ind_tbl_size;
	काष्ठा ib_device *device = rwq_ind_table->device;
	अचिन्हित पूर्णांक base_wqn;
	माप_प्रकार min_resp_len;
	पूर्णांक i, err = 0;

	अगर (udata->inlen > 0 &&
	    !ib_is_udata_cleared(udata, 0,
				 udata->inlen))
		वापस -EOPNOTSUPP;

	min_resp_len = दुरत्व(typeof(resp), reserved) + माप(resp.reserved);
	अगर (udata->outlen && udata->outlen < min_resp_len)
		वापस -EINVAL;

	अगर (ind_tbl_size >
	    device->attrs.rss_caps.max_rwq_indirection_table_size) अणु
		pr_debug("log_ind_tbl_size = %d is bigger than supported = %d\n",
			 ind_tbl_size,
			 device->attrs.rss_caps.max_rwq_indirection_table_size);
		वापस -EINVAL;
	पूर्ण

	base_wqn = init_attr->ind_tbl[0]->wq_num;

	अगर (base_wqn % ind_tbl_size) अणु
		pr_debug("WQN=0x%x isn't aligned with indirection table size\n",
			 base_wqn);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 1; i < ind_tbl_size; i++) अणु
		अगर (++base_wqn != init_attr->ind_tbl[i]->wq_num) अणु
			pr_debug("indirection table's WQNs aren't consecutive\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (udata->outlen) अणु
		resp.response_length = दुरत्व(typeof(resp), response_length) +
					माप(resp.response_length);
		err = ib_copy_to_udata(udata, &resp, resp.response_length);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा mlx4_ib_drain_cqe अणु
	काष्ठा ib_cqe cqe;
	काष्ठा completion करोne;
पूर्ण;

अटल व्योम mlx4_ib_drain_qp_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx4_ib_drain_cqe *cqe = container_of(wc->wr_cqe,
						     काष्ठा mlx4_ib_drain_cqe,
						     cqe);

	complete(&cqe->करोne);
पूर्ण

/* This function वापसs only once the drained WR was completed */
अटल व्योम handle_drain_completion(काष्ठा ib_cq *cq,
				    काष्ठा mlx4_ib_drain_cqe *sdrain,
				    काष्ठा mlx4_ib_dev *dev)
अणु
	काष्ठा mlx4_dev *mdev = dev->dev;

	अगर (cq->poll_ctx == IB_POLL_सूचीECT) अणु
		जबतक (रुको_क्रम_completion_समयout(&sdrain->करोne, HZ / 10) <= 0)
			ib_process_cq_direct(cq, -1);
		वापस;
	पूर्ण

	अगर (mdev->persist->state == MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		काष्ठा mlx4_ib_cq *mcq = to_mcq(cq);
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
		mcq->mcq.comp(&mcq->mcq);
	पूर्ण

	रुको_क्रम_completion(&sdrain->करोne);
पूर्ण

व्योम mlx4_ib_drain_sq(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_cq *cq = qp->send_cq;
	काष्ठा ib_qp_attr attr = अणु .qp_state = IB_QPS_ERR पूर्ण;
	काष्ठा mlx4_ib_drain_cqe sdrain;
	स्थिर काष्ठा ib_send_wr *bad_swr;
	काष्ठा ib_rdma_wr swr = अणु
		.wr = अणु
			.next = शून्य,
			अणु .wr_cqe	= &sdrain.cqe, पूर्ण,
			.opcode	= IB_WR_RDMA_WRITE,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	काष्ठा mlx4_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx4_dev *mdev = dev->dev;

	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret && mdev->persist->state != MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		WARN_ONCE(ret, "failed to drain send queue: %d\n", ret);
		वापस;
	पूर्ण

	sdrain.cqe.करोne = mlx4_ib_drain_qp_करोne;
	init_completion(&sdrain.करोne);

	ret = _mlx4_ib_post_send(qp, &swr.wr, &bad_swr, true);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain send queue: %d\n", ret);
		वापस;
	पूर्ण

	handle_drain_completion(cq, &sdrain, dev);
पूर्ण

व्योम mlx4_ib_drain_rq(काष्ठा ib_qp *qp)
अणु
	काष्ठा ib_cq *cq = qp->recv_cq;
	काष्ठा ib_qp_attr attr = अणु .qp_state = IB_QPS_ERR पूर्ण;
	काष्ठा mlx4_ib_drain_cqe rdrain;
	काष्ठा ib_recv_wr rwr = अणुपूर्ण;
	स्थिर काष्ठा ib_recv_wr *bad_rwr;
	पूर्णांक ret;
	काष्ठा mlx4_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx4_dev *mdev = dev->dev;

	ret = ib_modअगरy_qp(qp, &attr, IB_QP_STATE);
	अगर (ret && mdev->persist->state != MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		वापस;
	पूर्ण

	rwr.wr_cqe = &rdrain.cqe;
	rdrain.cqe.करोne = mlx4_ib_drain_qp_करोne;
	init_completion(&rdrain.करोne);

	ret = _mlx4_ib_post_recv(qp, &rwr, &bad_rwr, true);
	अगर (ret) अणु
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		वापस;
	पूर्ण

	handle_drain_completion(cq, &rdrain, dev);
पूर्ण
