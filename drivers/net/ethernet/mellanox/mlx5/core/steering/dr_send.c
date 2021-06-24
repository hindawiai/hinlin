<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/smp.h>
#समावेश "dr_types.h"

#घोषणा QUEUE_SIZE 128
#घोषणा SIGNAL_PER_DIV_QUEUE 16
#घोषणा TH_NUMS_TO_DRAIN 2

क्रमागत अणु CQ_OK = 0, CQ_EMPTY = -1, CQ_POLL_ERR = -2 पूर्ण;

काष्ठा dr_data_seg अणु
	u64 addr;
	u32 length;
	u32 lkey;
	अचिन्हित पूर्णांक send_flags;
पूर्ण;

काष्ठा postsend_info अणु
	काष्ठा dr_data_seg ग_लिखो;
	काष्ठा dr_data_seg पढ़ो;
	u64 remote_addr;
	u32 rkey;
पूर्ण;

काष्ठा dr_qp_rtr_attr अणु
	काष्ठा mlx5dr_cmd_gid_attr dgid_attr;
	क्रमागत ib_mtu mtu;
	u32 qp_num;
	u16 port_num;
	u8 min_rnr_समयr;
	u8 sgid_index;
	u16 udp_src_port;
	u8 fl:1;
पूर्ण;

काष्ठा dr_qp_rts_attr अणु
	u8 समयout;
	u8 retry_cnt;
	u8 rnr_retry;
पूर्ण;

काष्ठा dr_qp_init_attr अणु
	u32 cqn;
	u32 pdn;
	u32 max_send_wr;
	काष्ठा mlx5_uars_page *uar;
	u8 isolate_vl_tc:1;
पूर्ण;

अटल पूर्णांक dr_parse_cqe(काष्ठा mlx5dr_cq *dr_cq, काष्ठा mlx5_cqe64 *cqe64)
अणु
	अचिन्हित पूर्णांक idx;
	u8 opcode;

	opcode = get_cqe_opcode(cqe64);
	अगर (opcode == MLX5_CQE_REQ_ERR) अणु
		idx = be16_to_cpu(cqe64->wqe_counter) &
			(dr_cq->qp->sq.wqe_cnt - 1);
		dr_cq->qp->sq.cc = dr_cq->qp->sq.wqe_head[idx] + 1;
	पूर्ण अन्यथा अगर (opcode == MLX5_CQE_RESP_ERR) अणु
		++dr_cq->qp->sq.cc;
	पूर्ण अन्यथा अणु
		idx = be16_to_cpu(cqe64->wqe_counter) &
			(dr_cq->qp->sq.wqe_cnt - 1);
		dr_cq->qp->sq.cc = dr_cq->qp->sq.wqe_head[idx] + 1;

		वापस CQ_OK;
	पूर्ण

	वापस CQ_POLL_ERR;
पूर्ण

अटल पूर्णांक dr_cq_poll_one(काष्ठा mlx5dr_cq *dr_cq)
अणु
	काष्ठा mlx5_cqe64 *cqe64;
	पूर्णांक err;

	cqe64 = mlx5_cqwq_get_cqe(&dr_cq->wq);
	अगर (!cqe64)
		वापस CQ_EMPTY;

	mlx5_cqwq_pop(&dr_cq->wq);
	err = dr_parse_cqe(dr_cq, cqe64);
	mlx5_cqwq_update_db_record(&dr_cq->wq);

	वापस err;
पूर्ण

अटल पूर्णांक dr_poll_cq(काष्ठा mlx5dr_cq *dr_cq, पूर्णांक ne)
अणु
	पूर्णांक npolled;
	पूर्णांक err = 0;

	क्रम (npolled = 0; npolled < ne; ++npolled) अणु
		err = dr_cq_poll_one(dr_cq);
		अगर (err != CQ_OK)
			अवरोध;
	पूर्ण

	वापस err == CQ_POLL_ERR ? err : npolled;
पूर्ण

अटल काष्ठा mlx5dr_qp *dr_create_rc_qp(काष्ठा mlx5_core_dev *mdev,
					 काष्ठा dr_qp_init_attr *attr)
अणु
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	u32 temp_qpc[MLX5_ST_SZ_DW(qpc)] = अणुपूर्ण;
	काष्ठा mlx5_wq_param wqp;
	काष्ठा mlx5dr_qp *dr_qp;
	पूर्णांक inlen;
	व्योम *qpc;
	व्योम *in;
	पूर्णांक err;

	dr_qp = kzalloc(माप(*dr_qp), GFP_KERNEL);
	अगर (!dr_qp)
		वापस शून्य;

	wqp.buf_numa_node = mdev->priv.numa_node;
	wqp.db_numa_node = mdev->priv.numa_node;

	dr_qp->rq.pc = 0;
	dr_qp->rq.cc = 0;
	dr_qp->rq.wqe_cnt = 4;
	dr_qp->sq.pc = 0;
	dr_qp->sq.cc = 0;
	dr_qp->sq.wqe_cnt = roundup_घात_of_two(attr->max_send_wr);

	MLX5_SET(qpc, temp_qpc, log_rq_stride, ilog2(MLX5_SEND_WQE_DS) - 4);
	MLX5_SET(qpc, temp_qpc, log_rq_size, ilog2(dr_qp->rq.wqe_cnt));
	MLX5_SET(qpc, temp_qpc, log_sq_size, ilog2(dr_qp->sq.wqe_cnt));
	err = mlx5_wq_qp_create(mdev, &wqp, temp_qpc, &dr_qp->wq,
				&dr_qp->wq_ctrl);
	अगर (err) अणु
		mlx5_core_warn(mdev, "Can't create QP WQ\n");
		जाओ err_wq;
	पूर्ण

	dr_qp->sq.wqe_head = kसुस्मृति(dr_qp->sq.wqe_cnt,
				     माप(dr_qp->sq.wqe_head[0]),
				     GFP_KERNEL);

	अगर (!dr_qp->sq.wqe_head) अणु
		mlx5_core_warn(mdev, "Can't allocate wqe head\n");
		जाओ err_wqe_head;
	पूर्ण

	inlen = MLX5_ST_SZ_BYTES(create_qp_in) +
		MLX5_FLD_SZ_BYTES(create_qp_in, pas[0]) *
		dr_qp->wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_in;
	पूर्ण

	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_RC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, isolate_vl_tc, attr->isolate_vl_tc);
	MLX5_SET(qpc, qpc, pd, attr->pdn);
	MLX5_SET(qpc, qpc, uar_page, attr->uar->index);
	MLX5_SET(qpc, qpc, log_page_size,
		 dr_qp->wq_ctrl.buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(qpc, qpc, fre, 1);
	MLX5_SET(qpc, qpc, rlky, 1);
	MLX5_SET(qpc, qpc, cqn_snd, attr->cqn);
	MLX5_SET(qpc, qpc, cqn_rcv, attr->cqn);
	MLX5_SET(qpc, qpc, log_rq_stride, ilog2(MLX5_SEND_WQE_DS) - 4);
	MLX5_SET(qpc, qpc, log_rq_size, ilog2(dr_qp->rq.wqe_cnt));
	MLX5_SET(qpc, qpc, rq_type, MLX5_NON_ZERO_RQ);
	MLX5_SET(qpc, qpc, log_sq_size, ilog2(dr_qp->sq.wqe_cnt));
	MLX5_SET(qpc, qpc, ts_क्रमmat, mlx5_get_qp_शेष_ts(mdev));
	MLX5_SET64(qpc, qpc, dbr_addr, dr_qp->wq_ctrl.db.dma);
	अगर (MLX5_CAP_GEN(mdev, cqe_version) == 1)
		MLX5_SET(qpc, qpc, user_index, 0xFFFFFF);
	mlx5_fill_page_frag_array(&dr_qp->wq_ctrl.buf,
				  (__be64 *)MLX5_ADDR_OF(create_qp_in,
							 in, pas));

	MLX5_SET(create_qp_in, in, opcode, MLX5_CMD_OP_CREATE_QP);
	err = mlx5_cmd_exec(mdev, in, inlen, out, माप(out));
	dr_qp->qpn = MLX5_GET(create_qp_out, out, qpn);
	kvमुक्त(in);
	अगर (err)
		जाओ err_in;
	dr_qp->uar = attr->uar;

	वापस dr_qp;

err_in:
	kमुक्त(dr_qp->sq.wqe_head);
err_wqe_head:
	mlx5_wq_destroy(&dr_qp->wq_ctrl);
err_wq:
	kमुक्त(dr_qp);
	वापस शून्य;
पूर्ण

अटल व्योम dr_destroy_qp(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mlx5dr_qp *dr_qp)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_qp_in)] = अणुपूर्ण;

	MLX5_SET(destroy_qp_in, in, opcode, MLX5_CMD_OP_DESTROY_QP);
	MLX5_SET(destroy_qp_in, in, qpn, dr_qp->qpn);
	mlx5_cmd_exec_in(mdev, destroy_qp, in);

	kमुक्त(dr_qp->sq.wqe_head);
	mlx5_wq_destroy(&dr_qp->wq_ctrl);
	kमुक्त(dr_qp);
पूर्ण

अटल व्योम dr_cmd_notअगरy_hw(काष्ठा mlx5dr_qp *dr_qp, व्योम *ctrl)
अणु
	dma_wmb();
	*dr_qp->wq.sq.db = cpu_to_be32(dr_qp->sq.pc & 0xffff);

	/* After wmb() the hw aware of new work */
	wmb();

	mlx5_ग_लिखो64(ctrl, dr_qp->uar->map + MLX5_BF_OFFSET);
पूर्ण

अटल व्योम dr_rdma_segments(काष्ठा mlx5dr_qp *dr_qp, u64 remote_addr,
			     u32 rkey, काष्ठा dr_data_seg *data_seg,
			     u32 opcode, bool notअगरy_hw)
अणु
	काष्ठा mlx5_wqe_raddr_seg *wq_raddr;
	काष्ठा mlx5_wqe_ctrl_seg *wq_ctrl;
	काष्ठा mlx5_wqe_data_seg *wq_dseg;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक idx;

	size = माप(*wq_ctrl) / 16 + माप(*wq_dseg) / 16 +
		माप(*wq_raddr) / 16;

	idx = dr_qp->sq.pc & (dr_qp->sq.wqe_cnt - 1);

	wq_ctrl = mlx5_wq_cyc_get_wqe(&dr_qp->wq.sq, idx);
	wq_ctrl->imm = 0;
	wq_ctrl->fm_ce_se = (data_seg->send_flags) ?
		MLX5_WQE_CTRL_CQ_UPDATE : 0;
	wq_ctrl->opmod_idx_opcode = cpu_to_be32(((dr_qp->sq.pc & 0xffff) << 8) |
						opcode);
	wq_ctrl->qpn_ds = cpu_to_be32(size | dr_qp->qpn << 8);
	wq_raddr = (व्योम *)(wq_ctrl + 1);
	wq_raddr->raddr = cpu_to_be64(remote_addr);
	wq_raddr->rkey = cpu_to_be32(rkey);
	wq_raddr->reserved = 0;

	wq_dseg = (व्योम *)(wq_raddr + 1);
	wq_dseg->byte_count = cpu_to_be32(data_seg->length);
	wq_dseg->lkey = cpu_to_be32(data_seg->lkey);
	wq_dseg->addr = cpu_to_be64(data_seg->addr);

	dr_qp->sq.wqe_head[idx] = dr_qp->sq.pc++;

	अगर (notअगरy_hw)
		dr_cmd_notअगरy_hw(dr_qp, wq_ctrl);
पूर्ण

अटल व्योम dr_post_send(काष्ठा mlx5dr_qp *dr_qp, काष्ठा postsend_info *send_info)
अणु
	dr_rdma_segments(dr_qp, send_info->remote_addr, send_info->rkey,
			 &send_info->ग_लिखो, MLX5_OPCODE_RDMA_WRITE, false);
	dr_rdma_segments(dr_qp, send_info->remote_addr, send_info->rkey,
			 &send_info->पढ़ो, MLX5_OPCODE_RDMA_READ, true);
पूर्ण

/**
 * mlx5dr_send_fill_and_append_ste_send_info: Add data to be sent
 * with send_list parameters:
 *
 *     @ste:       The data that attached to this specअगरic ste
 *     @size:      of data to ग_लिखो
 *     @offset:    of the data from start of the hw_ste entry
 *     @data:      data
 *     @ste_info:  ste to be sent with send_list
 *     @send_list: to append पूर्णांकo it
 *     @copy_data: अगर true indicates that the data should be kept because
 *                 it's not backuped any where (like in re-hash).
 *                 अगर false, it lets the data to be updated after
 *                 it was added to the list.
 */
व्योम mlx5dr_send_fill_and_append_ste_send_info(काष्ठा mlx5dr_ste *ste, u16 size,
					       u16 offset, u8 *data,
					       काष्ठा mlx5dr_ste_send_info *ste_info,
					       काष्ठा list_head *send_list,
					       bool copy_data)
अणु
	ste_info->size = size;
	ste_info->ste = ste;
	ste_info->offset = offset;

	अगर (copy_data) अणु
		स_नकल(ste_info->data_cont, data, size);
		ste_info->data = ste_info->data_cont;
	पूर्ण अन्यथा अणु
		ste_info->data = data;
	पूर्ण

	list_add_tail(&ste_info->send_list, send_list);
पूर्ण

/* The function tries to consume one wc each समय, unless the queue is full, in
 * that हाल, which means that the hw is behind the sw in a full queue len
 * the function will drain the cq till it empty.
 */
अटल पूर्णांक dr_handle_pending_wc(काष्ठा mlx5dr_करोमुख्य *dmn,
				काष्ठा mlx5dr_send_ring *send_ring)
अणु
	bool is_drain = false;
	पूर्णांक ne;

	अगर (send_ring->pending_wqe < send_ring->संकेत_th)
		वापस 0;

	/* Queue is full start drain it */
	अगर (send_ring->pending_wqe >=
	    dmn->send_ring->संकेत_th * TH_NUMS_TO_DRAIN)
		is_drain = true;

	करो अणु
		ne = dr_poll_cq(send_ring->cq, 1);
		अगर (ne < 0)
			वापस ne;
		अन्यथा अगर (ne == 1)
			send_ring->pending_wqe -= send_ring->संकेत_th;
	पूर्ण जबतक (is_drain && send_ring->pending_wqe);

	वापस 0;
पूर्ण

अटल व्योम dr_fill_data_segs(काष्ठा mlx5dr_send_ring *send_ring,
			      काष्ठा postsend_info *send_info)
अणु
	send_ring->pending_wqe++;

	अगर (send_ring->pending_wqe % send_ring->संकेत_th == 0)
		send_info->ग_लिखो.send_flags |= IB_SEND_SIGNALED;

	send_ring->pending_wqe++;
	send_info->पढ़ो.length = send_info->ग_लिखो.length;
	/* Read पूर्णांकo the same ग_लिखो area */
	send_info->पढ़ो.addr = (uपूर्णांकptr_t)send_info->ग_लिखो.addr;
	send_info->पढ़ो.lkey = send_ring->mr->mkey.key;

	अगर (send_ring->pending_wqe % send_ring->संकेत_th == 0)
		send_info->पढ़ो.send_flags = IB_SEND_SIGNALED;
	अन्यथा
		send_info->पढ़ो.send_flags = 0;
पूर्ण

अटल पूर्णांक dr_postsend_icm_data(काष्ठा mlx5dr_करोमुख्य *dmn,
				काष्ठा postsend_info *send_info)
अणु
	काष्ठा mlx5dr_send_ring *send_ring = dmn->send_ring;
	u32 buff_offset;
	पूर्णांक ret;

	spin_lock(&send_ring->lock);

	ret = dr_handle_pending_wc(dmn, send_ring);
	अगर (ret)
		जाओ out_unlock;

	अगर (send_info->ग_लिखो.length > dmn->info.max_अंतरभूत_size) अणु
		buff_offset = (send_ring->tx_head &
			       (dmn->send_ring->संकेत_th - 1)) *
			send_ring->max_post_send_size;
		/* Copy to ring mr */
		स_नकल(send_ring->buf + buff_offset,
		       (व्योम *)(uपूर्णांकptr_t)send_info->ग_लिखो.addr,
		       send_info->ग_लिखो.length);
		send_info->ग_लिखो.addr = (uपूर्णांकptr_t)send_ring->mr->dma_addr + buff_offset;
		send_info->ग_लिखो.lkey = send_ring->mr->mkey.key;
	पूर्ण

	send_ring->tx_head++;
	dr_fill_data_segs(send_ring, send_info);
	dr_post_send(send_ring->qp, send_info);

out_unlock:
	spin_unlock(&send_ring->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dr_get_tbl_copy_details(काष्ठा mlx5dr_करोमुख्य *dmn,
				   काष्ठा mlx5dr_ste_htbl *htbl,
				   u8 **data,
				   u32 *byte_size,
				   पूर्णांक *iterations,
				   पूर्णांक *num_stes)
अणु
	पूर्णांक alloc_size;

	अगर (htbl->chunk->byte_size > dmn->send_ring->max_post_send_size) अणु
		*iterations = htbl->chunk->byte_size /
			dmn->send_ring->max_post_send_size;
		*byte_size = dmn->send_ring->max_post_send_size;
		alloc_size = *byte_size;
		*num_stes = *byte_size / DR_STE_SIZE;
	पूर्ण अन्यथा अणु
		*iterations = 1;
		*num_stes = htbl->chunk->num_of_entries;
		alloc_size = *num_stes * DR_STE_SIZE;
	पूर्ण

	*data = kvzalloc(alloc_size, GFP_KERNEL);
	अगर (!*data)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * mlx5dr_send_postsend_ste: ग_लिखो size bytes पूर्णांकo offset from the hw cm.
 *
 *     @dmn:    Doमुख्य
 *     @ste:    The ste काष्ठा that contains the data (at
 *              least part of it)
 *     @data:   The real data to send size data
 *     @size:   क्रम writing.
 *     @offset: The offset from the icm mapped data to
 *              start ग_लिखो to this क्रम ग_लिखो only part of the
 *              buffer.
 *
 * Return: 0 on success.
 */
पूर्णांक mlx5dr_send_postsend_ste(काष्ठा mlx5dr_करोमुख्य *dmn, काष्ठा mlx5dr_ste *ste,
			     u8 *data, u16 size, u16 offset)
अणु
	काष्ठा postsend_info send_info = अणुपूर्ण;

	mlx5dr_ste_prepare_क्रम_postsend(dmn->ste_ctx, data, size);

	send_info.ग_लिखो.addr = (uपूर्णांकptr_t)data;
	send_info.ग_लिखो.length = size;
	send_info.ग_लिखो.lkey = 0;
	send_info.remote_addr = mlx5dr_ste_get_mr_addr(ste) + offset;
	send_info.rkey = ste->htbl->chunk->rkey;

	वापस dr_postsend_icm_data(dmn, &send_info);
पूर्ण

पूर्णांक mlx5dr_send_postsend_htbl(काष्ठा mlx5dr_करोमुख्य *dmn,
			      काष्ठा mlx5dr_ste_htbl *htbl,
			      u8 *क्रमmatted_ste, u8 *mask)
अणु
	u32 byte_size = htbl->chunk->byte_size;
	पूर्णांक num_stes_per_iter;
	पूर्णांक iterations;
	u8 *data;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक j;

	ret = dr_get_tbl_copy_details(dmn, htbl, &data, &byte_size,
				      &iterations, &num_stes_per_iter);
	अगर (ret)
		वापस ret;

	mlx5dr_ste_prepare_क्रम_postsend(dmn->ste_ctx, क्रमmatted_ste, DR_STE_SIZE);

	/* Send the data iteration बार */
	क्रम (i = 0; i < iterations; i++) अणु
		u32 ste_index = i * (byte_size / DR_STE_SIZE);
		काष्ठा postsend_info send_info = अणुपूर्ण;

		/* Copy all ste's on the data buffer
		 * need to add the bit_mask
		 */
		क्रम (j = 0; j < num_stes_per_iter; j++) अणु
			काष्ठा mlx5dr_ste *ste = &htbl->ste_arr[ste_index + j];
			u32 ste_off = j * DR_STE_SIZE;

			अगर (mlx5dr_ste_is_not_used(ste)) अणु
				स_नकल(data + ste_off,
				       क्रमmatted_ste, DR_STE_SIZE);
			पूर्ण अन्यथा अणु
				/* Copy data */
				स_नकल(data + ste_off,
				       htbl->ste_arr[ste_index + j].hw_ste,
				       DR_STE_SIZE_REDUCED);
				/* Copy bit_mask */
				स_नकल(data + ste_off + DR_STE_SIZE_REDUCED,
				       mask, DR_STE_SIZE_MASK);
				/* Only when we have mask we need to re-arrange the STE */
				mlx5dr_ste_prepare_क्रम_postsend(dmn->ste_ctx,
								data + (j * DR_STE_SIZE),
								DR_STE_SIZE);
			पूर्ण
		पूर्ण

		send_info.ग_लिखो.addr = (uपूर्णांकptr_t)data;
		send_info.ग_लिखो.length = byte_size;
		send_info.ग_लिखो.lkey = 0;
		send_info.remote_addr =
			mlx5dr_ste_get_mr_addr(htbl->ste_arr + ste_index);
		send_info.rkey = htbl->chunk->rkey;

		ret = dr_postsend_icm_data(dmn, &send_info);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kvमुक्त(data);
	वापस ret;
पूर्ण

/* Initialize htble with शेष STEs */
पूर्णांक mlx5dr_send_postsend_क्रमmatted_htbl(काष्ठा mlx5dr_करोमुख्य *dmn,
					काष्ठा mlx5dr_ste_htbl *htbl,
					u8 *ste_init_data,
					bool update_hw_ste)
अणु
	u32 byte_size = htbl->chunk->byte_size;
	पूर्णांक iterations;
	पूर्णांक num_stes;
	u8 *copy_dst;
	u8 *data;
	पूर्णांक ret;
	पूर्णांक i;

	ret = dr_get_tbl_copy_details(dmn, htbl, &data, &byte_size,
				      &iterations, &num_stes);
	अगर (ret)
		वापस ret;

	अगर (update_hw_ste) अणु
		/* Copy the reduced STE to hash table ste_arr */
		क्रम (i = 0; i < num_stes; i++) अणु
			copy_dst = htbl->hw_ste_arr + i * DR_STE_SIZE_REDUCED;
			स_नकल(copy_dst, ste_init_data, DR_STE_SIZE_REDUCED);
		पूर्ण
	पूर्ण

	mlx5dr_ste_prepare_क्रम_postsend(dmn->ste_ctx, ste_init_data, DR_STE_SIZE);

	/* Copy the same STE on the data buffer */
	क्रम (i = 0; i < num_stes; i++) अणु
		copy_dst = data + i * DR_STE_SIZE;
		स_नकल(copy_dst, ste_init_data, DR_STE_SIZE);
	पूर्ण

	/* Send the data iteration बार */
	क्रम (i = 0; i < iterations; i++) अणु
		u8 ste_index = i * (byte_size / DR_STE_SIZE);
		काष्ठा postsend_info send_info = अणुपूर्ण;

		send_info.ग_लिखो.addr = (uपूर्णांकptr_t)data;
		send_info.ग_लिखो.length = byte_size;
		send_info.ग_लिखो.lkey = 0;
		send_info.remote_addr =
			mlx5dr_ste_get_mr_addr(htbl->ste_arr + ste_index);
		send_info.rkey = htbl->chunk->rkey;

		ret = dr_postsend_icm_data(dmn, &send_info);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kvमुक्त(data);
	वापस ret;
पूर्ण

पूर्णांक mlx5dr_send_postsend_action(काष्ठा mlx5dr_करोमुख्य *dmn,
				काष्ठा mlx5dr_action *action)
अणु
	काष्ठा postsend_info send_info = अणुपूर्ण;
	पूर्णांक ret;

	send_info.ग_लिखो.addr = (uपूर्णांकptr_t)action->reग_लिखो->data;
	send_info.ग_लिखो.length = action->reग_लिखो->num_of_actions *
				 DR_MODIFY_ACTION_SIZE;
	send_info.ग_लिखो.lkey = 0;
	send_info.remote_addr = action->reग_लिखो->chunk->mr_addr;
	send_info.rkey = action->reग_लिखो->chunk->rkey;

	ret = dr_postsend_icm_data(dmn, &send_info);

	वापस ret;
पूर्ण

अटल पूर्णांक dr_modअगरy_qp_rst2init(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5dr_qp *dr_qp,
				 पूर्णांक port)
अणु
	u32 in[MLX5_ST_SZ_DW(rst2init_qp_in)] = अणुपूर्ण;
	व्योम *qpc;

	qpc = MLX5_ADDR_OF(rst2init_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, primary_address_path.vhca_port_num, port);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QPC_PM_STATE_MIGRATED);
	MLX5_SET(qpc, qpc, rre, 1);
	MLX5_SET(qpc, qpc, rwe, 1);

	MLX5_SET(rst2init_qp_in, in, opcode, MLX5_CMD_OP_RST2INIT_QP);
	MLX5_SET(rst2init_qp_in, in, qpn, dr_qp->qpn);

	वापस mlx5_cmd_exec_in(mdev, rst2init_qp, in);
पूर्ण

अटल पूर्णांक dr_cmd_modअगरy_qp_rtr2rts(काष्ठा mlx5_core_dev *mdev,
				    काष्ठा mlx5dr_qp *dr_qp,
				    काष्ठा dr_qp_rts_attr *attr)
अणु
	u32 in[MLX5_ST_SZ_DW(rtr2rts_qp_in)] = अणुपूर्ण;
	व्योम *qpc;

	qpc  = MLX5_ADDR_OF(rtr2rts_qp_in, in, qpc);

	MLX5_SET(rtr2rts_qp_in, in, qpn, dr_qp->qpn);

	MLX5_SET(qpc, qpc, retry_count, attr->retry_cnt);
	MLX5_SET(qpc, qpc, rnr_retry, attr->rnr_retry);

	MLX5_SET(rtr2rts_qp_in, in, opcode, MLX5_CMD_OP_RTR2RTS_QP);
	MLX5_SET(rtr2rts_qp_in, in, qpn, dr_qp->qpn);

	वापस mlx5_cmd_exec_in(mdev, rtr2rts_qp, in);
पूर्ण

अटल पूर्णांक dr_cmd_modअगरy_qp_init2rtr(काष्ठा mlx5_core_dev *mdev,
				     काष्ठा mlx5dr_qp *dr_qp,
				     काष्ठा dr_qp_rtr_attr *attr)
अणु
	u32 in[MLX5_ST_SZ_DW(init2rtr_qp_in)] = अणुपूर्ण;
	व्योम *qpc;

	qpc = MLX5_ADDR_OF(init2rtr_qp_in, in, qpc);

	MLX5_SET(init2rtr_qp_in, in, qpn, dr_qp->qpn);

	MLX5_SET(qpc, qpc, mtu, attr->mtu);
	MLX5_SET(qpc, qpc, log_msg_max, DR_CHUNK_SIZE_MAX - 1);
	MLX5_SET(qpc, qpc, remote_qpn, attr->qp_num);
	स_नकल(MLX5_ADDR_OF(qpc, qpc, primary_address_path.rmac_47_32),
	       attr->dgid_attr.mac, माप(attr->dgid_attr.mac));
	स_नकल(MLX5_ADDR_OF(qpc, qpc, primary_address_path.rgid_rip),
	       attr->dgid_attr.gid, माप(attr->dgid_attr.gid));
	MLX5_SET(qpc, qpc, primary_address_path.src_addr_index,
		 attr->sgid_index);

	अगर (attr->dgid_attr.roce_ver == MLX5_ROCE_VERSION_2)
		MLX5_SET(qpc, qpc, primary_address_path.udp_sport,
			 attr->udp_src_port);

	MLX5_SET(qpc, qpc, primary_address_path.vhca_port_num, attr->port_num);
	MLX5_SET(qpc, qpc, primary_address_path.fl, attr->fl);
	MLX5_SET(qpc, qpc, min_rnr_nak, 1);

	MLX5_SET(init2rtr_qp_in, in, opcode, MLX5_CMD_OP_INIT2RTR_QP);
	MLX5_SET(init2rtr_qp_in, in, qpn, dr_qp->qpn);

	वापस mlx5_cmd_exec_in(mdev, init2rtr_qp, in);
पूर्ण

अटल bool dr_send_allow_fl(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	/* Check whether RC RoCE QP creation with क्रमce loopback is allowed.
	 * There are two separate capability bits क्रम this:
	 *  - क्रमce loopback when RoCE is enabled
	 *  - क्रमce loopback when RoCE is disabled
	 */
	वापस ((caps->roce_caps.roce_en &&
		 caps->roce_caps.fl_rc_qp_when_roce_enabled) ||
		(!caps->roce_caps.roce_en &&
		 caps->roce_caps.fl_rc_qp_when_roce_disabled));
पूर्ण

अटल पूर्णांक dr_prepare_qp_to_rts(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा mlx5dr_qp *dr_qp = dmn->send_ring->qp;
	काष्ठा dr_qp_rts_attr rts_attr = अणुपूर्ण;
	काष्ठा dr_qp_rtr_attr rtr_attr = अणुपूर्ण;
	क्रमागत ib_mtu mtu = IB_MTU_1024;
	u16 gid_index = 0;
	पूर्णांक port = 1;
	पूर्णांक ret;

	/* Init */
	ret = dr_modअगरy_qp_rst2init(dmn->mdev, dr_qp, port);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed modify QP rst2init\n");
		वापस ret;
	पूर्ण

	/* RTR */
	rtr_attr.mtu		= mtu;
	rtr_attr.qp_num		= dr_qp->qpn;
	rtr_attr.min_rnr_समयr	= 12;
	rtr_attr.port_num	= port;
	rtr_attr.udp_src_port	= dmn->info.caps.roce_min_src_udp;

	/* If QP creation with क्रमce loopback is allowed, then there
	 * is no need क्रम GID index when creating the QP.
	 * Otherwise we query GID attributes and use GID index.
	 */
	rtr_attr.fl = dr_send_allow_fl(&dmn->info.caps);
	अगर (!rtr_attr.fl) अणु
		ret = mlx5dr_cmd_query_gid(dmn->mdev, port, gid_index,
					   &rtr_attr.dgid_attr);
		अगर (ret)
			वापस ret;

		rtr_attr.sgid_index = gid_index;
	पूर्ण

	ret = dr_cmd_modअगरy_qp_init2rtr(dmn->mdev, dr_qp, &rtr_attr);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed modify QP init2rtr\n");
		वापस ret;
	पूर्ण

	/* RTS */
	rts_attr.समयout	= 14;
	rts_attr.retry_cnt	= 7;
	rts_attr.rnr_retry	= 7;

	ret = dr_cmd_modअगरy_qp_rtr2rts(dmn->mdev, dr_qp, &rts_attr);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed modify QP rtr2rts\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dr_cq_complete(काष्ठा mlx5_core_cq *mcq,
			   काष्ठा mlx5_eqe *eqe)
अणु
	pr_err("CQ completion CQ: #%u\n", mcq->cqn);
पूर्ण

अटल काष्ठा mlx5dr_cq *dr_create_cq(काष्ठा mlx5_core_dev *mdev,
				      काष्ठा mlx5_uars_page *uar,
				      माप_प्रकार ncqe)
अणु
	u32 temp_cqc[MLX5_ST_SZ_DW(cqc)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(create_cq_out)];
	काष्ठा mlx5_wq_param wqp;
	काष्ठा mlx5_cqe64 *cqe;
	काष्ठा mlx5dr_cq *cq;
	पूर्णांक inlen, err, eqn;
	अचिन्हित पूर्णांक irqn;
	व्योम *cqc, *in;
	__be64 *pas;
	पूर्णांक vector;
	u32 i;

	cq = kzalloc(माप(*cq), GFP_KERNEL);
	अगर (!cq)
		वापस शून्य;

	ncqe = roundup_घात_of_two(ncqe);
	MLX5_SET(cqc, temp_cqc, log_cq_size, ilog2(ncqe));

	wqp.buf_numa_node = mdev->priv.numa_node;
	wqp.db_numa_node = mdev->priv.numa_node;

	err = mlx5_cqwq_create(mdev, &wqp, temp_cqc, &cq->wq,
			       &cq->wq_ctrl);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < mlx5_cqwq_get_size(&cq->wq); i++) अणु
		cqe = mlx5_cqwq_get_wqe(&cq->wq, i);
		cqe->op_own = MLX5_CQE_INVALID << 4 | MLX5_CQE_OWNER_MASK;
	पूर्ण

	inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		माप(u64) * cq->wq_ctrl.buf.npages;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		जाओ err_cqwq;

	vector = raw_smp_processor_id() % mlx5_comp_vectors_count(mdev);
	err = mlx5_vector2eqn(mdev, vector, &eqn, &irqn);
	अगर (err) अणु
		kvमुक्त(in);
		जाओ err_cqwq;
	पूर्ण

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);
	MLX5_SET(cqc, cqc, log_cq_size, ilog2(ncqe));
	MLX5_SET(cqc, cqc, c_eqn, eqn);
	MLX5_SET(cqc, cqc, uar_page, uar->index);
	MLX5_SET(cqc, cqc, log_page_size, cq->wq_ctrl.buf.page_shअगरt -
		 MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(cqc, cqc, dbr_addr, cq->wq_ctrl.db.dma);

	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, in, pas);
	mlx5_fill_page_frag_array(&cq->wq_ctrl.buf, pas);

	cq->mcq.comp  = dr_cq_complete;

	err = mlx5_core_create_cq(mdev, &cq->mcq, in, inlen, out, माप(out));
	kvमुक्त(in);

	अगर (err)
		जाओ err_cqwq;

	cq->mcq.cqe_sz = 64;
	cq->mcq.set_ci_db = cq->wq_ctrl.db.db;
	cq->mcq.arm_db = cq->wq_ctrl.db.db + 1;
	*cq->mcq.set_ci_db = 0;

	/* set no-zero value, in order to aव्योम the HW to run db-recovery on
	 * CQ that used in polling mode.
	 */
	*cq->mcq.arm_db = cpu_to_be32(2 << 28);

	cq->mcq.vector = 0;
	cq->mcq.irqn = irqn;
	cq->mcq.uar = uar;

	वापस cq;

err_cqwq:
	mlx5_wq_destroy(&cq->wq_ctrl);
out:
	kमुक्त(cq);
	वापस शून्य;
पूर्ण

अटल व्योम dr_destroy_cq(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5dr_cq *cq)
अणु
	mlx5_core_destroy_cq(mdev, &cq->mcq);
	mlx5_wq_destroy(&cq->wq_ctrl);
	kमुक्त(cq);
पूर्ण

अटल पूर्णांक
dr_create_mkey(काष्ठा mlx5_core_dev *mdev, u32 pdn, काष्ठा mlx5_core_mkey *mkey)
अणु
	u32 in[MLX5_ST_SZ_DW(create_mkey_in)] = अणुपूर्ण;
	व्योम *mkc;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_PA);
	MLX5_SET(mkc, mkc, a, 1);
	MLX5_SET(mkc, mkc, rw, 1);
	MLX5_SET(mkc, mkc, rr, 1);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);

	MLX5_SET(mkc, mkc, pd, pdn);
	MLX5_SET(mkc, mkc, length64, 1);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);

	वापस mlx5_core_create_mkey(mdev, mkey, in, माप(in));
पूर्ण

अटल काष्ठा mlx5dr_mr *dr_reg_mr(काष्ठा mlx5_core_dev *mdev,
				   u32 pdn, व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा mlx5dr_mr *mr = kzalloc(माप(*mr), GFP_KERNEL);
	काष्ठा device *dma_device;
	dma_addr_t dma_addr;
	पूर्णांक err;

	अगर (!mr)
		वापस शून्य;

	dma_device = mlx5_core_dma_dev(mdev);
	dma_addr = dma_map_single(dma_device, buf, size,
				  DMA_BIसूचीECTIONAL);
	err = dma_mapping_error(dma_device, dma_addr);
	अगर (err) अणु
		mlx5_core_warn(mdev, "Can't dma buf\n");
		kमुक्त(mr);
		वापस शून्य;
	पूर्ण

	err = dr_create_mkey(mdev, pdn, &mr->mkey);
	अगर (err) अणु
		mlx5_core_warn(mdev, "Can't create mkey\n");
		dma_unmap_single(dma_device, dma_addr, size,
				 DMA_BIसूचीECTIONAL);
		kमुक्त(mr);
		वापस शून्य;
	पूर्ण

	mr->dma_addr = dma_addr;
	mr->size = size;
	mr->addr = buf;

	वापस mr;
पूर्ण

अटल व्योम dr_dereg_mr(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5dr_mr *mr)
अणु
	mlx5_core_destroy_mkey(mdev, &mr->mkey);
	dma_unmap_single(mlx5_core_dma_dev(mdev), mr->dma_addr, mr->size,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(mr);
पूर्ण

पूर्णांक mlx5dr_send_ring_alloc(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा dr_qp_init_attr init_attr = अणुपूर्ण;
	पूर्णांक cq_size;
	पूर्णांक size;
	पूर्णांक ret;

	dmn->send_ring = kzalloc(माप(*dmn->send_ring), GFP_KERNEL);
	अगर (!dmn->send_ring)
		वापस -ENOMEM;

	cq_size = QUEUE_SIZE + 1;
	dmn->send_ring->cq = dr_create_cq(dmn->mdev, dmn->uar, cq_size);
	अगर (!dmn->send_ring->cq) अणु
		mlx5dr_err(dmn, "Failed creating CQ\n");
		ret = -ENOMEM;
		जाओ मुक्त_send_ring;
	पूर्ण

	init_attr.cqn = dmn->send_ring->cq->mcq.cqn;
	init_attr.pdn = dmn->pdn;
	init_attr.uar = dmn->uar;
	init_attr.max_send_wr = QUEUE_SIZE;

	/* Isolated VL is applicable only अगर क्रमce loopback is supported */
	अगर (dr_send_allow_fl(&dmn->info.caps))
		init_attr.isolate_vl_tc = dmn->info.caps.isolate_vl_tc;

	spin_lock_init(&dmn->send_ring->lock);

	dmn->send_ring->qp = dr_create_rc_qp(dmn->mdev, &init_attr);
	अगर (!dmn->send_ring->qp)  अणु
		mlx5dr_err(dmn, "Failed creating QP\n");
		ret = -ENOMEM;
		जाओ clean_cq;
	पूर्ण

	dmn->send_ring->cq->qp = dmn->send_ring->qp;

	dmn->info.max_send_wr = QUEUE_SIZE;
	dmn->info.max_अंतरभूत_size = min(dmn->send_ring->qp->max_अंतरभूत_data,
					DR_STE_SIZE);

	dmn->send_ring->संकेत_th = dmn->info.max_send_wr /
		SIGNAL_PER_DIV_QUEUE;

	/* Prepare qp to be used */
	ret = dr_prepare_qp_to_rts(dmn);
	अगर (ret)
		जाओ clean_qp;

	dmn->send_ring->max_post_send_size =
		mlx5dr_icm_pool_chunk_माप_प्रकारo_byte(DR_CHUNK_SIZE_1K,
						   DR_ICM_TYPE_STE);

	/* Allocating the max size as a buffer क्रम writing */
	size = dmn->send_ring->संकेत_th * dmn->send_ring->max_post_send_size;
	dmn->send_ring->buf = kzalloc(size, GFP_KERNEL);
	अगर (!dmn->send_ring->buf) अणु
		ret = -ENOMEM;
		जाओ clean_qp;
	पूर्ण

	dmn->send_ring->buf_size = size;

	dmn->send_ring->mr = dr_reg_mr(dmn->mdev,
				       dmn->pdn, dmn->send_ring->buf, size);
	अगर (!dmn->send_ring->mr) अणु
		ret = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	dmn->send_ring->sync_mr = dr_reg_mr(dmn->mdev,
					    dmn->pdn, dmn->send_ring->sync_buff,
					    MIN_READ_SYNC);
	अगर (!dmn->send_ring->sync_mr) अणु
		ret = -ENOMEM;
		जाओ clean_mr;
	पूर्ण

	वापस 0;

clean_mr:
	dr_dereg_mr(dmn->mdev, dmn->send_ring->mr);
मुक्त_mem:
	kमुक्त(dmn->send_ring->buf);
clean_qp:
	dr_destroy_qp(dmn->mdev, dmn->send_ring->qp);
clean_cq:
	dr_destroy_cq(dmn->mdev, dmn->send_ring->cq);
मुक्त_send_ring:
	kमुक्त(dmn->send_ring);

	वापस ret;
पूर्ण

व्योम mlx5dr_send_ring_मुक्त(काष्ठा mlx5dr_करोमुख्य *dmn,
			   काष्ठा mlx5dr_send_ring *send_ring)
अणु
	dr_destroy_qp(dmn->mdev, send_ring->qp);
	dr_destroy_cq(dmn->mdev, send_ring->cq);
	dr_dereg_mr(dmn->mdev, send_ring->sync_mr);
	dr_dereg_mr(dmn->mdev, send_ring->mr);
	kमुक्त(send_ring->buf);
	kमुक्त(send_ring);
पूर्ण

पूर्णांक mlx5dr_send_ring_क्रमce_drain(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा mlx5dr_send_ring *send_ring = dmn->send_ring;
	काष्ठा postsend_info send_info = अणुपूर्ण;
	u8 data[DR_STE_SIZE];
	पूर्णांक num_of_sends_req;
	पूर्णांक ret;
	पूर्णांक i;

	/* Sending this amount of requests makes sure we will get drain */
	num_of_sends_req = send_ring->संकेत_th * TH_NUMS_TO_DRAIN / 2;

	/* Send fake requests क्रमcing the last to be संकेतed */
	send_info.ग_लिखो.addr = (uपूर्णांकptr_t)data;
	send_info.ग_लिखो.length = DR_STE_SIZE;
	send_info.ग_लिखो.lkey = 0;
	/* Using the sync_mr in order to ग_लिखो/पढ़ो */
	send_info.remote_addr = (uपूर्णांकptr_t)send_ring->sync_mr->addr;
	send_info.rkey = send_ring->sync_mr->mkey.key;

	क्रम (i = 0; i < num_of_sends_req; i++) अणु
		ret = dr_postsend_icm_data(dmn, &send_info);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock(&send_ring->lock);
	ret = dr_handle_pending_wc(dmn, send_ring);
	spin_unlock(&send_ring->lock);

	वापस ret;
पूर्ण
