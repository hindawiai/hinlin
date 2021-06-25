<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies, Ltd.  All rights reserved.
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

#समावेश <linux/mlx5/driver.h>
#समावेश "wq.h"
#समावेश "mlx5_core.h"

पूर्णांक mlx5_wq_cyc_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		       व्योम *wqc, काष्ठा mlx5_wq_cyc *wq,
		       काष्ठा mlx5_wq_ctrl *wq_ctrl)
अणु
	u8 log_wq_stride = MLX5_GET(wq, wqc, log_wq_stride);
	u8 log_wq_sz     = MLX5_GET(wq, wqc, log_wq_sz);
	काष्ठा mlx5_frag_buf_ctrl *fbc = &wq->fbc;
	पूर्णांक err;

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		वापस err;
	पूर्ण

	wq->db  = wq_ctrl->db.db;

	err = mlx5_frag_buf_alloc_node(mdev, wq_get_byte_sz(log_wq_sz, log_wq_stride),
				       &wq_ctrl->buf, param->buf_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n", err);
		जाओ err_db_मुक्त;
	पूर्ण

	mlx5_init_fbc(wq_ctrl->buf.frags, log_wq_stride, log_wq_sz, fbc);
	wq->sz = mlx5_wq_cyc_get_size(wq);

	wq_ctrl->mdev = mdev;

	वापस 0;

err_db_मुक्त:
	mlx5_db_मुक्त(mdev, &wq_ctrl->db);

	वापस err;
पूर्ण

व्योम mlx5_wq_cyc_wqe_dump(काष्ठा mlx5_wq_cyc *wq, u16 ix, u8 nstrides)
अणु
	माप_प्रकार len;
	व्योम *wqe;

	अगर (!net_ratelimit())
		वापस;

	nstrides = max_t(u8, nstrides, 1);

	len = nstrides << wq->fbc.log_stride;
	wqe = mlx5_wq_cyc_get_wqe(wq, ix);

	pr_info("WQE DUMP: WQ size %d WQ cur size %d, WQE index 0x%x, len: %zu\n",
		mlx5_wq_cyc_get_size(wq), wq->cur_sz, ix, len);
	prपूर्णांक_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1, wqe, len, false);
पूर्ण

व्योम mlx5_wq_cyc_reset(काष्ठा mlx5_wq_cyc *wq)
अणु
	wq->wqe_ctr = 0;
	wq->cur_sz = 0;
	mlx5_wq_cyc_update_db_record(wq);
पूर्ण

पूर्णांक mlx5_wq_qp_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		      व्योम *qpc, काष्ठा mlx5_wq_qp *wq,
		      काष्ठा mlx5_wq_ctrl *wq_ctrl)
अणु
	u8 log_rq_stride = MLX5_GET(qpc, qpc, log_rq_stride) + 4;
	u8 log_rq_sz     = MLX5_GET(qpc, qpc, log_rq_size);
	u8 log_sq_stride = ilog2(MLX5_SEND_WQE_BB);
	u8 log_sq_sz     = MLX5_GET(qpc, qpc, log_sq_size);

	u32 rq_byte_size;
	पूर्णांक err;



	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		वापस err;
	पूर्ण

	err = mlx5_frag_buf_alloc_node(mdev,
				       wq_get_byte_sz(log_rq_sz, log_rq_stride) +
				       wq_get_byte_sz(log_sq_sz, log_sq_stride),
				       &wq_ctrl->buf, param->buf_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n", err);
		जाओ err_db_मुक्त;
	पूर्ण

	mlx5_init_fbc(wq_ctrl->buf.frags, log_rq_stride, log_rq_sz, &wq->rq.fbc);

	rq_byte_size = wq_get_byte_sz(log_rq_sz, log_rq_stride);

	अगर (rq_byte_size < PAGE_SIZE) अणु
		/* SQ starts within the same page of the RQ */
		u16 sq_strides_offset = rq_byte_size / MLX5_SEND_WQE_BB;

		mlx5_init_fbc_offset(wq_ctrl->buf.frags,
				     log_sq_stride, log_sq_sz, sq_strides_offset,
				     &wq->sq.fbc);
	पूर्ण अन्यथा अणु
		u16 rq_npages = rq_byte_size >> PAGE_SHIFT;

		mlx5_init_fbc(wq_ctrl->buf.frags + rq_npages,
			      log_sq_stride, log_sq_sz, &wq->sq.fbc);
	पूर्ण

	wq->rq.db  = &wq_ctrl->db.db[MLX5_RCV_DBR];
	wq->sq.db  = &wq_ctrl->db.db[MLX5_SND_DBR];

	wq_ctrl->mdev = mdev;

	वापस 0;

err_db_मुक्त:
	mlx5_db_मुक्त(mdev, &wq_ctrl->db);

	वापस err;
पूर्ण

पूर्णांक mlx5_cqwq_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		     व्योम *cqc, काष्ठा mlx5_cqwq *wq,
		     काष्ठा mlx5_wq_ctrl *wq_ctrl)
अणु
	/* CQE_STRIDE_128 and CQE_STRIDE_128_PAD both mean 128B stride */
	u8 log_wq_stride = MLX5_GET(cqc, cqc, cqe_sz) == CQE_STRIDE_64 ? 6 : 7;
	u8 log_wq_sz     = MLX5_GET(cqc, cqc, log_cq_size);
	पूर्णांक err;

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		वापस err;
	पूर्ण

	wq->db  = wq_ctrl->db.db;

	err = mlx5_frag_buf_alloc_node(mdev, wq_get_byte_sz(log_wq_sz, log_wq_stride),
				       &wq_ctrl->buf,
				       param->buf_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n",
			       err);
		जाओ err_db_मुक्त;
	पूर्ण

	mlx5_init_fbc(wq_ctrl->buf.frags, log_wq_stride, log_wq_sz, &wq->fbc);

	wq_ctrl->mdev = mdev;

	वापस 0;

err_db_मुक्त:
	mlx5_db_मुक्त(mdev, &wq_ctrl->db);

	वापस err;
पूर्ण

अटल व्योम mlx5_wq_ll_init_list(काष्ठा mlx5_wq_ll *wq)
अणु
	काष्ठा mlx5_wqe_srq_next_seg *next_seg;
	पूर्णांक i;

	क्रम (i = 0; i < wq->fbc.sz_m1; i++) अणु
		next_seg = mlx5_wq_ll_get_wqe(wq, i);
		next_seg->next_wqe_index = cpu_to_be16(i + 1);
	पूर्ण
	next_seg = mlx5_wq_ll_get_wqe(wq, i);
	wq->tail_next = &next_seg->next_wqe_index;
पूर्ण

पूर्णांक mlx5_wq_ll_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		      व्योम *wqc, काष्ठा mlx5_wq_ll *wq,
		      काष्ठा mlx5_wq_ctrl *wq_ctrl)
अणु
	u8 log_wq_stride = MLX5_GET(wq, wqc, log_wq_stride);
	u8 log_wq_sz     = MLX5_GET(wq, wqc, log_wq_sz);
	काष्ठा mlx5_frag_buf_ctrl *fbc = &wq->fbc;
	पूर्णांक err;

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_db_alloc_node() failed, %d\n", err);
		वापस err;
	पूर्ण

	wq->db  = wq_ctrl->db.db;

	err = mlx5_frag_buf_alloc_node(mdev, wq_get_byte_sz(log_wq_sz, log_wq_stride),
				       &wq_ctrl->buf, param->buf_numa_node);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_frag_buf_alloc_node() failed, %d\n", err);
		जाओ err_db_मुक्त;
	पूर्ण

	mlx5_init_fbc(wq_ctrl->buf.frags, log_wq_stride, log_wq_sz, fbc);

	mlx5_wq_ll_init_list(wq);
	wq_ctrl->mdev = mdev;

	वापस 0;

err_db_मुक्त:
	mlx5_db_मुक्त(mdev, &wq_ctrl->db);

	वापस err;
पूर्ण

व्योम mlx5_wq_ll_reset(काष्ठा mlx5_wq_ll *wq)
अणु
	wq->head = 0;
	wq->wqe_ctr = 0;
	wq->cur_sz = 0;
	mlx5_wq_ll_init_list(wq);
	mlx5_wq_ll_update_db_record(wq);
पूर्ण

व्योम mlx5_wq_destroy(काष्ठा mlx5_wq_ctrl *wq_ctrl)
अणु
	mlx5_frag_buf_मुक्त(wq_ctrl->mdev, &wq_ctrl->buf);
	mlx5_db_मुक्त(wq_ctrl->mdev, &wq_ctrl->db);
पूर्ण

