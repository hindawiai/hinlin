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

#अगर_अघोषित __MLX5_WQ_H__
#घोषणा __MLX5_WQ_H__

#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/qp.h>

काष्ठा mlx5_wq_param अणु
	पूर्णांक		buf_numa_node;
	पूर्णांक		db_numa_node;
पूर्ण;

काष्ठा mlx5_wq_ctrl अणु
	काष्ठा mlx5_core_dev	*mdev;
	काष्ठा mlx5_frag_buf	buf;
	काष्ठा mlx5_db		db;
पूर्ण;

काष्ठा mlx5_wq_cyc अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	__be32			*db;
	u16			sz;
	u16			wqe_ctr;
	u16			cur_sz;
पूर्ण;

काष्ठा mlx5_wq_qp अणु
	काष्ठा mlx5_wq_cyc	rq;
	काष्ठा mlx5_wq_cyc	sq;
पूर्ण;

काष्ठा mlx5_cqwq अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	__be32			  *db;
	u32			  cc; /* consumer counter */
पूर्ण;

काष्ठा mlx5_wq_ll अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	__be32			*db;
	__be16			*tail_next;
	u16			head;
	u16			wqe_ctr;
	u16			cur_sz;
पूर्ण;

पूर्णांक mlx5_wq_cyc_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		       व्योम *wqc, काष्ठा mlx5_wq_cyc *wq,
		       काष्ठा mlx5_wq_ctrl *wq_ctrl);
व्योम mlx5_wq_cyc_wqe_dump(काष्ठा mlx5_wq_cyc *wq, u16 ix, u8 nstrides);
व्योम mlx5_wq_cyc_reset(काष्ठा mlx5_wq_cyc *wq);

पूर्णांक mlx5_wq_qp_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		      व्योम *qpc, काष्ठा mlx5_wq_qp *wq,
		      काष्ठा mlx5_wq_ctrl *wq_ctrl);

पूर्णांक mlx5_cqwq_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		     व्योम *cqc, काष्ठा mlx5_cqwq *wq,
		     काष्ठा mlx5_wq_ctrl *wq_ctrl);

पूर्णांक mlx5_wq_ll_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_wq_param *param,
		      व्योम *wqc, काष्ठा mlx5_wq_ll *wq,
		      काष्ठा mlx5_wq_ctrl *wq_ctrl);
व्योम mlx5_wq_ll_reset(काष्ठा mlx5_wq_ll *wq);

व्योम mlx5_wq_destroy(काष्ठा mlx5_wq_ctrl *wq_ctrl);

अटल अंतरभूत u32 mlx5_wq_cyc_get_size(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस (u32)wq->fbc.sz_m1 + 1;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_cyc_is_full(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस wq->cur_sz == wq->sz;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_cyc_missing(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस wq->sz - wq->cur_sz;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_cyc_is_empty(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस !wq->cur_sz;
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_cyc_push(काष्ठा mlx5_wq_cyc *wq)
अणु
	wq->wqe_ctr++;
	wq->cur_sz++;
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_cyc_push_n(काष्ठा mlx5_wq_cyc *wq, u8 n)
अणु
	wq->wqe_ctr += n;
	wq->cur_sz += n;
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_cyc_pop(काष्ठा mlx5_wq_cyc *wq)
अणु
	wq->cur_sz--;
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_cyc_update_db_record(काष्ठा mlx5_wq_cyc *wq)
अणु
	*wq->db = cpu_to_be32(wq->wqe_ctr);
पूर्ण

अटल अंतरभूत u16 mlx5_wq_cyc_ctr2ix(काष्ठा mlx5_wq_cyc *wq, u16 ctr)
अणु
	वापस ctr & wq->fbc.sz_m1;
पूर्ण

अटल अंतरभूत u16 mlx5_wq_cyc_get_head(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस mlx5_wq_cyc_ctr2ix(wq, wq->wqe_ctr);
पूर्ण

अटल अंतरभूत u16 mlx5_wq_cyc_get_tail(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस mlx5_wq_cyc_ctr2ix(wq, wq->wqe_ctr - wq->cur_sz);
पूर्ण

अटल अंतरभूत व्योम *mlx5_wq_cyc_get_wqe(काष्ठा mlx5_wq_cyc *wq, u16 ix)
अणु
	वापस mlx5_frag_buf_get_wqe(&wq->fbc, ix);
पूर्ण

अटल अंतरभूत u16 mlx5_wq_cyc_get_contig_wqebbs(काष्ठा mlx5_wq_cyc *wq, u16 ix)
अणु
	वापस mlx5_frag_buf_get_idx_last_contig_stride(&wq->fbc, ix) - ix + 1;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_cyc_cc_bigger(u16 cc1, u16 cc2)
अणु
	पूर्णांक equal   = (cc1 == cc2);
	पूर्णांक smaller = 0x8000 & (cc1 - cc2);

	वापस !equal && !smaller;
पूर्ण

अटल अंतरभूत u16 mlx5_wq_cyc_get_counter(काष्ठा mlx5_wq_cyc *wq)
अणु
	वापस wq->wqe_ctr;
पूर्ण

अटल अंतरभूत u32 mlx5_cqwq_get_size(काष्ठा mlx5_cqwq *wq)
अणु
	वापस wq->fbc.sz_m1 + 1;
पूर्ण

अटल अंतरभूत u8 mlx5_cqwq_get_log_stride_size(काष्ठा mlx5_cqwq *wq)
अणु
	वापस wq->fbc.log_stride;
पूर्ण

अटल अंतरभूत u32 mlx5_cqwq_ctr2ix(काष्ठा mlx5_cqwq *wq, u32 ctr)
अणु
	वापस ctr & wq->fbc.sz_m1;
पूर्ण

अटल अंतरभूत u32 mlx5_cqwq_get_ci(काष्ठा mlx5_cqwq *wq)
अणु
	वापस mlx5_cqwq_ctr2ix(wq, wq->cc);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_cqe64 *mlx5_cqwq_get_wqe(काष्ठा mlx5_cqwq *wq, u32 ix)
अणु
	काष्ठा mlx5_cqe64 *cqe = mlx5_frag_buf_get_wqe(&wq->fbc, ix);

	/* For 128B CQEs the data is in the last 64B */
	cqe += wq->fbc.log_stride == 7;

	वापस cqe;
पूर्ण

अटल अंतरभूत u32 mlx5_cqwq_get_ctr_wrap_cnt(काष्ठा mlx5_cqwq *wq, u32 ctr)
अणु
	वापस ctr >> wq->fbc.log_sz;
पूर्ण

अटल अंतरभूत u32 mlx5_cqwq_get_wrap_cnt(काष्ठा mlx5_cqwq *wq)
अणु
	वापस mlx5_cqwq_get_ctr_wrap_cnt(wq, wq->cc);
पूर्ण

अटल अंतरभूत व्योम mlx5_cqwq_pop(काष्ठा mlx5_cqwq *wq)
अणु
	wq->cc++;
पूर्ण

अटल अंतरभूत व्योम mlx5_cqwq_update_db_record(काष्ठा mlx5_cqwq *wq)
अणु
	*wq->db = cpu_to_be32(wq->cc & 0xffffff);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_cqe64 *mlx5_cqwq_get_cqe(काष्ठा mlx5_cqwq *wq)
अणु
	u32 ci = mlx5_cqwq_get_ci(wq);
	काष्ठा mlx5_cqe64 *cqe = mlx5_cqwq_get_wqe(wq, ci);
	u8 cqe_ownership_bit = cqe->op_own & MLX5_CQE_OWNER_MASK;
	u8 sw_ownership_val = mlx5_cqwq_get_wrap_cnt(wq) & 1;

	अगर (cqe_ownership_bit != sw_ownership_val)
		वापस शून्य;

	/* ensure cqe content is पढ़ो after cqe ownership bit */
	dma_rmb();

	वापस cqe;
पूर्ण

अटल अंतरभूत u32 mlx5_wq_ll_get_size(काष्ठा mlx5_wq_ll *wq)
अणु
	वापस (u32)wq->fbc.sz_m1 + 1;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_ll_is_full(काष्ठा mlx5_wq_ll *wq)
अणु
	वापस wq->cur_sz == wq->fbc.sz_m1;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_ll_is_empty(काष्ठा mlx5_wq_ll *wq)
अणु
	वापस !wq->cur_sz;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_wq_ll_missing(काष्ठा mlx5_wq_ll *wq)
अणु
	वापस wq->fbc.sz_m1 - wq->cur_sz;
पूर्ण

अटल अंतरभूत व्योम *mlx5_wq_ll_get_wqe(काष्ठा mlx5_wq_ll *wq, u16 ix)
अणु
	वापस mlx5_frag_buf_get_wqe(&wq->fbc, ix);
पूर्ण

अटल अंतरभूत u16 mlx5_wq_ll_get_wqe_next_ix(काष्ठा mlx5_wq_ll *wq, u16 ix)
अणु
	काष्ठा mlx5_wqe_srq_next_seg *wqe = mlx5_wq_ll_get_wqe(wq, ix);

	वापस be16_to_cpu(wqe->next_wqe_index);
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_ll_push(काष्ठा mlx5_wq_ll *wq, u16 head_next)
अणु
	wq->head = head_next;
	wq->wqe_ctr++;
	wq->cur_sz++;
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_ll_pop(काष्ठा mlx5_wq_ll *wq, __be16 ix,
				  __be16 *next_tail_next)
अणु
	*wq->tail_next = ix;
	wq->tail_next = next_tail_next;
	wq->cur_sz--;
पूर्ण

अटल अंतरभूत व्योम mlx5_wq_ll_update_db_record(काष्ठा mlx5_wq_ll *wq)
अणु
	*wq->db = cpu_to_be32(wq->wqe_ctr);
पूर्ण

अटल अंतरभूत u16 mlx5_wq_ll_get_head(काष्ठा mlx5_wq_ll *wq)
अणु
	वापस wq->head;
पूर्ण

अटल अंतरभूत u16 mlx5_wq_ll_get_counter(काष्ठा mlx5_wq_ll *wq)
अणु
	वापस wq->wqe_ctr;
पूर्ण

#पूर्ण_अगर /* __MLX5_WQ_H__ */
