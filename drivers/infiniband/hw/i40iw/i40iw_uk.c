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
#समावेश "i40iw_status.h"
#समावेश "i40iw_d.h"
#समावेश "i40iw_user.h"
#समावेश "i40iw_register.h"

अटल u32 nop_signature = 0x55550000;

/**
 * i40iw_nop_1 - insert a nop wqe and move head. no post work
 * @qp: hw qp ptr
 */
अटल क्रमागत i40iw_status_code i40iw_nop_1(काष्ठा i40iw_qp_uk *qp)
अणु
	u64 header, *wqe;
	u64 *wqe_0 = शून्य;
	u32 wqe_idx, peek_head;
	bool संकेतed = false;

	अगर (!qp->sq_ring.head)
		वापस I40IW_ERR_PARAM;

	wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
	wqe = qp->sq_base[wqe_idx].elem;

	qp->sq_wrtrk_array[wqe_idx].wqe_size = I40IW_QP_WQE_MIN_SIZE;

	peek_head = (qp->sq_ring.head + 1) % qp->sq_ring.size;
	wqe_0 = qp->sq_base[peek_head].elem;
	अगर (peek_head)
		wqe_0[3] = LS_64(!qp->swqe_polarity, I40IWQPSQ_VALID);
	अन्यथा
		wqe_0[3] = LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	set_64bit_val(wqe, 0, 0);
	set_64bit_val(wqe, 8, 0);
	set_64bit_val(wqe, 16, 0);

	header = LS_64(I40IWQP_OP_NOP, I40IWQPSQ_OPCODE) |
	    LS_64(संकेतed, I40IWQPSQ_SIGCOMPL) |
	    LS_64(qp->swqe_polarity, I40IWQPSQ_VALID) | nop_signature++;

	wmb();	/* Memory barrier to ensure data is written beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);
	वापस 0;
पूर्ण

/**
 * i40iw_qp_post_wr - post wr to hrdware
 * @qp: hw qp ptr
 */
व्योम i40iw_qp_post_wr(काष्ठा i40iw_qp_uk *qp)
अणु
	u64 temp;
	u32 hw_sq_tail;
	u32 sw_sq_head;

	mb(); /* valid bit is written and loads completed beक्रमe पढ़ोing shaकरोw */

	/* पढ़ो the करोorbell shaकरोw area */
	get_64bit_val(qp->shaकरोw_area, 0, &temp);

	hw_sq_tail = (u32)RS_64(temp, I40IW_QP_DBSA_HW_SQ_TAIL);
	sw_sq_head = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
	अगर (sw_sq_head != hw_sq_tail) अणु
		अगर (sw_sq_head > qp->initial_ring.head) अणु
			अगर ((hw_sq_tail >= qp->initial_ring.head) &&
			    (hw_sq_tail < sw_sq_head)) अणु
				ग_लिखोl(qp->qp_id, qp->wqe_alloc_reg);
			पूर्ण
		पूर्ण अन्यथा अगर (sw_sq_head != qp->initial_ring.head) अणु
			अगर ((hw_sq_tail >= qp->initial_ring.head) ||
			    (hw_sq_tail < sw_sq_head)) अणु
				ग_लिखोl(qp->qp_id, qp->wqe_alloc_reg);
			पूर्ण
		पूर्ण
	पूर्ण

	qp->initial_ring.head = qp->sq_ring.head;
पूर्ण

/**
 * i40iw_qp_get_next_send_wqe - वापस next wqe ptr
 * @qp: hw qp ptr
 * @wqe_idx: वापस wqe index
 * @wqe_size: size of sq wqe
 * @total_size: work request length
 * @wr_id: work request id
 */
u64 *i40iw_qp_get_next_send_wqe(काष्ठा i40iw_qp_uk *qp,
				u32 *wqe_idx,
				u8 wqe_size,
				u32 total_size,
				u64 wr_id
				)
अणु
	u64 *wqe = शून्य;
	u64 wqe_ptr;
	u32 peek_head = 0;
	u16 offset;
	क्रमागत i40iw_status_code ret_code = 0;
	u8 nop_wqe_cnt = 0, i;
	u64 *wqe_0 = शून्य;

	*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);

	अगर (!*wqe_idx)
		qp->swqe_polarity = !qp->swqe_polarity;
	wqe_ptr = (uपूर्णांकptr_t)qp->sq_base[*wqe_idx].elem;
	offset = (u16)(wqe_ptr) & 0x7F;
	अगर ((offset + wqe_size) > I40IW_QP_WQE_MAX_SIZE) अणु
		nop_wqe_cnt = (u8)(I40IW_QP_WQE_MAX_SIZE - offset) / I40IW_QP_WQE_MIN_SIZE;
		क्रम (i = 0; i < nop_wqe_cnt; i++) अणु
			i40iw_nop_1(qp);
			I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
			अगर (ret_code)
				वापस शून्य;
		पूर्ण

		*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
		अगर (!*wqe_idx)
			qp->swqe_polarity = !qp->swqe_polarity;
	पूर्ण

	अगर (((*wqe_idx & 3) == 1) && (wqe_size == I40IW_WQE_SIZE_64)) अणु
		i40iw_nop_1(qp);
		I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
		अगर (ret_code)
			वापस शून्य;
		*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
		अगर (!*wqe_idx)
			qp->swqe_polarity = !qp->swqe_polarity;
	पूर्ण
	I40IW_RING_MOVE_HEAD_BY_COUNT(qp->sq_ring,
				      wqe_size / I40IW_QP_WQE_MIN_SIZE, ret_code);
	अगर (ret_code)
		वापस शून्य;

	wqe = qp->sq_base[*wqe_idx].elem;

	peek_head = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
	wqe_0 = qp->sq_base[peek_head].elem;

	अगर (((peek_head & 3) == 1) || ((peek_head & 3) == 3)) अणु
		अगर (RS_64(wqe_0[3], I40IWQPSQ_VALID) != !qp->swqe_polarity)
			wqe_0[3] = LS_64(!qp->swqe_polarity, I40IWQPSQ_VALID);
	पूर्ण

	qp->sq_wrtrk_array[*wqe_idx].wrid = wr_id;
	qp->sq_wrtrk_array[*wqe_idx].wr_len = total_size;
	qp->sq_wrtrk_array[*wqe_idx].wqe_size = wqe_size;
	वापस wqe;
पूर्ण

/**
 * i40iw_set_fragment - set fragment in wqe
 * @wqe: wqe क्रम setting fragment
 * @offset: offset value
 * @sge: sge length and stag
 */
अटल व्योम i40iw_set_fragment(u64 *wqe, u32 offset, काष्ठा i40iw_sge *sge)
अणु
	अगर (sge) अणु
		set_64bit_val(wqe, offset, LS_64(sge->tag_off, I40IWQPSQ_FRAG_TO));
		set_64bit_val(wqe, (offset + 8),
			      (LS_64(sge->len, I40IWQPSQ_FRAG_LEN) |
			       LS_64(sge->stag, I40IWQPSQ_FRAG_STAG)));
	पूर्ण
पूर्ण

/**
 * i40iw_qp_get_next_recv_wqe - get next qp's rcv wqe
 * @qp: hw qp ptr
 * @wqe_idx: वापस wqe index
 */
u64 *i40iw_qp_get_next_recv_wqe(काष्ठा i40iw_qp_uk *qp, u32 *wqe_idx)
अणु
	u64 *wqe = शून्य;
	क्रमागत i40iw_status_code ret_code;

	अगर (I40IW_RING_FULL_ERR(qp->rq_ring))
		वापस शून्य;

	I40IW_ATOMIC_RING_MOVE_HEAD(qp->rq_ring, *wqe_idx, ret_code);
	अगर (ret_code)
		वापस शून्य;
	अगर (!*wqe_idx)
		qp->rwqe_polarity = !qp->rwqe_polarity;
	/* rq_wqe_size_multiplier is no of qwords in one rq wqe */
	wqe = qp->rq_base[*wqe_idx * (qp->rq_wqe_size_multiplier >> 2)].elem;

	वापस wqe;
पूर्ण

/**
 * i40iw_rdma_ग_लिखो - rdma ग_लिखो operation
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_rdma_ग_लिखो(काष्ठा i40iw_qp_uk *qp,
					       काष्ठा i40iw_post_sq_info *info,
					       bool post_sq)
अणु
	u64 header;
	u64 *wqe;
	काष्ठा i40iw_rdma_ग_लिखो *op_info;
	u32 i, wqe_idx;
	u32 total_size = 0, byte_off;
	क्रमागत i40iw_status_code ret_code;
	bool पढ़ो_fence = false;
	u8 wqe_size;

	op_info = &info->op.rdma_ग_लिखो;
	अगर (op_info->num_lo_sges > qp->max_sq_frag_cnt)
		वापस I40IW_ERR_INVALID_FRAG_COUNT;

	क्रम (i = 0; i < op_info->num_lo_sges; i++)
		total_size += op_info->lo_sg_list[i].len;

	अगर (total_size > I40IW_MAX_OUTBOUND_MESSAGE_SIZE)
		वापस I40IW_ERR_QP_INVALID_MSG_SIZE;

	पढ़ो_fence |= info->पढ़ो_fence;

	ret_code = i40iw_fragcnt_to_wqesize_sq(op_info->num_lo_sges, &wqe_size);
	अगर (ret_code)
		वापस ret_code;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, total_size, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	set_64bit_val(wqe, 16,
		      LS_64(op_info->rem_addr.tag_off, I40IWQPSQ_FRAG_TO));
	अगर (!op_info->rem_addr.stag)
		वापस I40IW_ERR_BAD_STAG;

	header = LS_64(op_info->rem_addr.stag, I40IWQPSQ_REMSTAG) |
		 LS_64(I40IWQP_OP_RDMA_WRITE, I40IWQPSQ_OPCODE) |
		 LS_64((op_info->num_lo_sges > 1 ?  (op_info->num_lo_sges - 1) : 0), I40IWQPSQ_ADDFRAGCNT) |
		 LS_64(पढ़ो_fence, I40IWQPSQ_READFENCE) |
		 LS_64(info->local_fence, I40IWQPSQ_LOCALFENCE) |
		 LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
		 LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	i40iw_set_fragment(wqe, 0, op_info->lo_sg_list);

	क्रम (i = 1, byte_off = 32; i < op_info->num_lo_sges; i++) अणु
		i40iw_set_fragment(wqe, byte_off, &op_info->lo_sg_list[i]);
		byte_off += 16;
	पूर्ण

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);

	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_rdma_पढ़ो - rdma पढ़ो command
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @inv_stag: flag क्रम inv_stag
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_rdma_पढ़ो(काष्ठा i40iw_qp_uk *qp,
					      काष्ठा i40iw_post_sq_info *info,
					      bool inv_stag,
					      bool post_sq)
अणु
	u64 *wqe;
	काष्ठा i40iw_rdma_पढ़ो *op_info;
	u64 header;
	u32 wqe_idx;
	क्रमागत i40iw_status_code ret_code;
	u8 wqe_size;
	bool local_fence = false;

	op_info = &info->op.rdma_पढ़ो;
	ret_code = i40iw_fragcnt_to_wqesize_sq(1, &wqe_size);
	अगर (ret_code)
		वापस ret_code;
	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, op_info->lo_addr.len, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	local_fence |= info->local_fence;

	set_64bit_val(wqe, 16, LS_64(op_info->rem_addr.tag_off, I40IWQPSQ_FRAG_TO));
	header = LS_64(op_info->rem_addr.stag, I40IWQPSQ_REMSTAG) |
		 LS_64((inv_stag ? I40IWQP_OP_RDMA_READ_LOC_INV : I40IWQP_OP_RDMA_READ), I40IWQPSQ_OPCODE) |
		 LS_64(info->पढ़ो_fence, I40IWQPSQ_READFENCE) |
		 LS_64(local_fence, I40IWQPSQ_LOCALFENCE) |
		 LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
		 LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	i40iw_set_fragment(wqe, 0, &op_info->lo_addr);

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);
	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_send - rdma send command
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @stag_to_inv: stag_to_inv value
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_send(काष्ठा i40iw_qp_uk *qp,
					 काष्ठा i40iw_post_sq_info *info,
					 u32 stag_to_inv,
					 bool post_sq)
अणु
	u64 *wqe;
	काष्ठा i40iw_post_send *op_info;
	u64 header;
	u32 i, wqe_idx, total_size = 0, byte_off;
	क्रमागत i40iw_status_code ret_code;
	bool पढ़ो_fence = false;
	u8 wqe_size;

	op_info = &info->op.send;
	अगर (qp->max_sq_frag_cnt < op_info->num_sges)
		वापस I40IW_ERR_INVALID_FRAG_COUNT;

	क्रम (i = 0; i < op_info->num_sges; i++)
		total_size += op_info->sg_list[i].len;
	ret_code = i40iw_fragcnt_to_wqesize_sq(op_info->num_sges, &wqe_size);
	अगर (ret_code)
		वापस ret_code;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, total_size, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;

	पढ़ो_fence |= info->पढ़ो_fence;
	set_64bit_val(wqe, 16, 0);
	header = LS_64(stag_to_inv, I40IWQPSQ_REMSTAG) |
		 LS_64(info->op_type, I40IWQPSQ_OPCODE) |
		 LS_64((op_info->num_sges > 1 ? (op_info->num_sges - 1) : 0),
		       I40IWQPSQ_ADDFRAGCNT) |
		 LS_64(पढ़ो_fence, I40IWQPSQ_READFENCE) |
		 LS_64(info->local_fence, I40IWQPSQ_LOCALFENCE) |
		 LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
		 LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	i40iw_set_fragment(wqe, 0, op_info->sg_list);

	क्रम (i = 1, byte_off = 32; i < op_info->num_sges; i++) अणु
		i40iw_set_fragment(wqe, byte_off, &op_info->sg_list[i]);
		byte_off += 16;
	पूर्ण

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);
	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_अंतरभूत_rdma_ग_लिखो - अंतरभूत rdma ग_लिखो operation
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_अंतरभूत_rdma_ग_लिखो(काष्ठा i40iw_qp_uk *qp,
						      काष्ठा i40iw_post_sq_info *info,
						      bool post_sq)
अणु
	u64 *wqe;
	u8 *dest, *src;
	काष्ठा i40iw_अंतरभूत_rdma_ग_लिखो *op_info;
	u64 header = 0;
	u32 wqe_idx;
	क्रमागत i40iw_status_code ret_code;
	bool पढ़ो_fence = false;
	u8 wqe_size;

	op_info = &info->op.अंतरभूत_rdma_ग_लिखो;
	अगर (op_info->len > I40IW_MAX_INLINE_DATA_SIZE)
		वापस I40IW_ERR_INVALID_INLINE_DATA_SIZE;

	ret_code = i40iw_अंतरभूत_data_माप_प्रकारo_wqesize(op_info->len, &wqe_size);
	अगर (ret_code)
		वापस ret_code;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, op_info->len, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;

	पढ़ो_fence |= info->पढ़ो_fence;
	set_64bit_val(wqe, 16,
		      LS_64(op_info->rem_addr.tag_off, I40IWQPSQ_FRAG_TO));

	header = LS_64(op_info->rem_addr.stag, I40IWQPSQ_REMSTAG) |
		 LS_64(I40IWQP_OP_RDMA_WRITE, I40IWQPSQ_OPCODE) |
		 LS_64(op_info->len, I40IWQPSQ_INLINEDATALEN) |
		 LS_64(1, I40IWQPSQ_INLINEDATAFLAG) |
		 LS_64(पढ़ो_fence, I40IWQPSQ_READFENCE) |
		 LS_64(info->local_fence, I40IWQPSQ_LOCALFENCE) |
		 LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
		 LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	dest = (u8 *)wqe;
	src = (u8 *)(op_info->data);

	अगर (op_info->len <= 16) अणु
		स_नकल(dest, src, op_info->len);
	पूर्ण अन्यथा अणु
		स_नकल(dest, src, 16);
		src += 16;
		dest = (u8 *)wqe + 32;
		स_नकल(dest, src, op_info->len - 16);
	पूर्ण

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);

	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_अंतरभूत_send - अंतरभूत send operation
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @stag_to_inv: remote stag
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_अंतरभूत_send(काष्ठा i40iw_qp_uk *qp,
						काष्ठा i40iw_post_sq_info *info,
						u32 stag_to_inv,
						bool post_sq)
अणु
	u64 *wqe;
	u8 *dest, *src;
	काष्ठा i40iw_post_अंतरभूत_send *op_info;
	u64 header;
	u32 wqe_idx;
	क्रमागत i40iw_status_code ret_code;
	bool पढ़ो_fence = false;
	u8 wqe_size;

	op_info = &info->op.अंतरभूत_send;
	अगर (op_info->len > I40IW_MAX_INLINE_DATA_SIZE)
		वापस I40IW_ERR_INVALID_INLINE_DATA_SIZE;

	ret_code = i40iw_अंतरभूत_data_माप_प्रकारo_wqesize(op_info->len, &wqe_size);
	अगर (ret_code)
		वापस ret_code;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, op_info->len, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;

	पढ़ो_fence |= info->पढ़ो_fence;
	header = LS_64(stag_to_inv, I40IWQPSQ_REMSTAG) |
	    LS_64(info->op_type, I40IWQPSQ_OPCODE) |
	    LS_64(op_info->len, I40IWQPSQ_INLINEDATALEN) |
	    LS_64(1, I40IWQPSQ_INLINEDATAFLAG) |
	    LS_64(पढ़ो_fence, I40IWQPSQ_READFENCE) |
	    LS_64(info->local_fence, I40IWQPSQ_LOCALFENCE) |
	    LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
	    LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	dest = (u8 *)wqe;
	src = (u8 *)(op_info->data);

	अगर (op_info->len <= 16) अणु
		स_नकल(dest, src, op_info->len);
	पूर्ण अन्यथा अणु
		स_नकल(dest, src, 16);
		src += 16;
		dest = (u8 *)wqe + 32;
		स_नकल(dest, src, op_info->len - 16);
	पूर्ण

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);

	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_stag_local_invalidate - stag invalidate operation
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_stag_local_invalidate(काष्ठा i40iw_qp_uk *qp,
							  काष्ठा i40iw_post_sq_info *info,
							  bool post_sq)
अणु
	u64 *wqe;
	काष्ठा i40iw_inv_local_stag *op_info;
	u64 header;
	u32 wqe_idx;
	bool local_fence = false;

	op_info = &info->op.inv_local_stag;
	local_fence = info->local_fence;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, I40IW_QP_WQE_MIN_SIZE, 0, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	set_64bit_val(wqe, 0, 0);
	set_64bit_val(wqe, 8,
		      LS_64(op_info->target_stag, I40IWQPSQ_LOCSTAG));
	set_64bit_val(wqe, 16, 0);
	header = LS_64(I40IW_OP_TYPE_INV_STAG, I40IWQPSQ_OPCODE) |
	    LS_64(info->पढ़ो_fence, I40IWQPSQ_READFENCE) |
	    LS_64(local_fence, I40IWQPSQ_LOCALFENCE) |
	    LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
	    LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);

	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_mw_bind - Memory Winकरोw bind operation
 * @qp: hw qp ptr
 * @info: post sq inक्रमmation
 * @post_sq: flag to post sq
 */
अटल क्रमागत i40iw_status_code i40iw_mw_bind(काष्ठा i40iw_qp_uk *qp,
					    काष्ठा i40iw_post_sq_info *info,
					    bool post_sq)
अणु
	u64 *wqe;
	काष्ठा i40iw_bind_winकरोw *op_info;
	u64 header;
	u32 wqe_idx;
	bool local_fence = false;

	op_info = &info->op.bind_winकरोw;

	local_fence |= info->local_fence;
	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, I40IW_QP_WQE_MIN_SIZE, 0, info->wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	set_64bit_val(wqe, 0, (uपूर्णांकptr_t)op_info->va);
	set_64bit_val(wqe, 8,
		      LS_64(op_info->mr_stag, I40IWQPSQ_PARENTMRSTAG) |
		      LS_64(op_info->mw_stag, I40IWQPSQ_MWSTAG));
	set_64bit_val(wqe, 16, op_info->bind_length);
	header = LS_64(I40IW_OP_TYPE_BIND_MW, I40IWQPSQ_OPCODE) |
	    LS_64(((op_info->enable_पढ़ोs << 2) |
		   (op_info->enable_ग_लिखोs << 3)),
		  I40IWQPSQ_STAGRIGHTS) |
	    LS_64((op_info->addressing_type == I40IW_ADDR_TYPE_VA_BASED ?  1 : 0),
		  I40IWQPSQ_VABASEDTO) |
	    LS_64(info->पढ़ो_fence, I40IWQPSQ_READFENCE) |
	    LS_64(local_fence, I40IWQPSQ_LOCALFENCE) |
	    LS_64(info->संकेतed, I40IWQPSQ_SIGCOMPL) |
	    LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);

	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_post_receive - post receive wqe
 * @qp: hw qp ptr
 * @info: post rq inक्रमmation
 */
अटल क्रमागत i40iw_status_code i40iw_post_receive(काष्ठा i40iw_qp_uk *qp,
						 काष्ठा i40iw_post_rq_info *info)
अणु
	u64 *wqe;
	u64 header;
	u32 total_size = 0, wqe_idx, i, byte_off;

	अगर (qp->max_rq_frag_cnt < info->num_sges)
		वापस I40IW_ERR_INVALID_FRAG_COUNT;
	क्रम (i = 0; i < info->num_sges; i++)
		total_size += info->sg_list[i].len;
	wqe = i40iw_qp_get_next_recv_wqe(qp, &wqe_idx);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;

	qp->rq_wrid_array[wqe_idx] = info->wr_id;
	set_64bit_val(wqe, 16, 0);

	header = LS_64((info->num_sges > 1 ? (info->num_sges - 1) : 0),
		       I40IWQPSQ_ADDFRAGCNT) |
	    LS_64(qp->rwqe_polarity, I40IWQPSQ_VALID);

	i40iw_set_fragment(wqe, 0, info->sg_list);

	क्रम (i = 1, byte_off = 32; i < info->num_sges; i++) अणु
		i40iw_set_fragment(wqe, byte_off, &info->sg_list[i]);
		byte_off += 16;
	पूर्ण

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);

	वापस 0;
पूर्ण

/**
 * i40iw_cq_request_notअगरication - cq notअगरication request (करोor bell)
 * @cq: hw cq
 * @cq_notअगरy: notअगरication type
 */
अटल व्योम i40iw_cq_request_notअगरication(काष्ठा i40iw_cq_uk *cq,
					  क्रमागत i40iw_completion_notअगरy cq_notअगरy)
अणु
	u64 temp_val;
	u16 sw_cq_sel;
	u8 arm_next_se = 0;
	u8 arm_next = 0;
	u8 arm_seq_num;

	get_64bit_val(cq->shaकरोw_area, 32, &temp_val);
	arm_seq_num = (u8)RS_64(temp_val, I40IW_CQ_DBSA_ARM_SEQ_NUM);
	arm_seq_num++;

	sw_cq_sel = (u16)RS_64(temp_val, I40IW_CQ_DBSA_SW_CQ_SELECT);
	arm_next_se = (u8)RS_64(temp_val, I40IW_CQ_DBSA_ARM_NEXT_SE);
	arm_next_se |= 1;
	अगर (cq_notअगरy == IW_CQ_COMPL_EVENT)
		arm_next = 1;
	temp_val = LS_64(arm_seq_num, I40IW_CQ_DBSA_ARM_SEQ_NUM) |
	    LS_64(sw_cq_sel, I40IW_CQ_DBSA_SW_CQ_SELECT) |
	    LS_64(arm_next_se, I40IW_CQ_DBSA_ARM_NEXT_SE) |
	    LS_64(arm_next, I40IW_CQ_DBSA_ARM_NEXT);

	set_64bit_val(cq->shaकरोw_area, 32, temp_val);

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	ग_लिखोl(cq->cq_id, cq->cqe_alloc_reg);
पूर्ण

/**
 * i40iw_cq_post_entries - update tail in shaकरोw memory
 * @cq: hw cq
 * @count: # of entries processed
 */
अटल क्रमागत i40iw_status_code i40iw_cq_post_entries(काष्ठा i40iw_cq_uk *cq,
						    u8 count)
अणु
	I40IW_RING_MOVE_TAIL_BY_COUNT(cq->cq_ring, count);
	set_64bit_val(cq->shaकरोw_area, 0,
		      I40IW_RING_GETCURRENT_HEAD(cq->cq_ring));
	वापस 0;
पूर्ण

/**
 * i40iw_cq_poll_completion - get cq completion info
 * @cq: hw cq
 * @info: cq poll inक्रमmation वापसed
 */
अटल क्रमागत i40iw_status_code i40iw_cq_poll_completion(काष्ठा i40iw_cq_uk *cq,
						       काष्ठा i40iw_cq_poll_info *info)
अणु
	u64 comp_ctx, qword0, qword2, qword3, wqe_qword;
	u64 *cqe, *sw_wqe;
	काष्ठा i40iw_qp_uk *qp;
	काष्ठा i40iw_ring *pring = शून्य;
	u32 wqe_idx, q_type, array_idx = 0;
	क्रमागत i40iw_status_code ret_code = 0;
	bool move_cq_head = true;
	u8 polarity;
	u8 addl_wqes = 0;

	अगर (cq->aव्योम_mem_cflct)
		cqe = (u64 *)I40IW_GET_CURRENT_EXTENDED_CQ_ELEMENT(cq);
	अन्यथा
		cqe = (u64 *)I40IW_GET_CURRENT_CQ_ELEMENT(cq);

	get_64bit_val(cqe, 24, &qword3);
	polarity = (u8)RS_64(qword3, I40IW_CQ_VALID);

	अगर (polarity != cq->polarity)
		वापस I40IW_ERR_QUEUE_EMPTY;

	q_type = (u8)RS_64(qword3, I40IW_CQ_SQ);
	info->error = (bool)RS_64(qword3, I40IW_CQ_ERROR);
	अगर (info->error) अणु
		info->comp_status = I40IW_COMPL_STATUS_FLUSHED;
		info->major_err = (bool)RS_64(qword3, I40IW_CQ_MAJERR);
		info->minor_err = (bool)RS_64(qword3, I40IW_CQ_MINERR);
	पूर्ण अन्यथा अणु
		info->comp_status = I40IW_COMPL_STATUS_SUCCESS;
	पूर्ण

	get_64bit_val(cqe, 0, &qword0);
	get_64bit_val(cqe, 16, &qword2);

	info->tcp_seq_num = (u32)RS_64(qword0, I40IWCQ_TCPSEQNUM);

	info->qp_id = (u32)RS_64(qword2, I40IWCQ_QPID);

	get_64bit_val(cqe, 8, &comp_ctx);

	info->solicited_event = (bool)RS_64(qword3, I40IWCQ_SOEVENT);
	info->is_srq = (bool)RS_64(qword3, I40IWCQ_SRQ);

	qp = (काष्ठा i40iw_qp_uk *)(अचिन्हित दीर्घ)comp_ctx;
	अगर (!qp) अणु
		ret_code = I40IW_ERR_QUEUE_DESTROYED;
		जाओ निकास;
	पूर्ण
	wqe_idx = (u32)RS_64(qword3, I40IW_CQ_WQEIDX);
	info->qp_handle = (i40iw_qp_handle)(अचिन्हित दीर्घ)qp;

	अगर (q_type == I40IW_CQE_QTYPE_RQ) अणु
		array_idx = (wqe_idx * 4) / qp->rq_wqe_size_multiplier;
		अगर (info->comp_status == I40IW_COMPL_STATUS_FLUSHED) अणु
			info->wr_id = qp->rq_wrid_array[qp->rq_ring.tail];
			array_idx = qp->rq_ring.tail;
		पूर्ण अन्यथा अणु
			info->wr_id = qp->rq_wrid_array[array_idx];
		पूर्ण

		info->op_type = I40IW_OP_TYPE_REC;
		अगर (qword3 & I40IWCQ_STAG_MASK) अणु
			info->stag_invalid_set = true;
			info->inv_stag = (u32)RS_64(qword2, I40IWCQ_INVSTAG);
		पूर्ण अन्यथा अणु
			info->stag_invalid_set = false;
		पूर्ण
		info->bytes_xfered = (u32)RS_64(qword0, I40IWCQ_PAYLDLEN);
		I40IW_RING_SET_TAIL(qp->rq_ring, array_idx + 1);
		pring = &qp->rq_ring;
	पूर्ण अन्यथा अणु
		अगर (qp->first_sq_wq) अणु
			qp->first_sq_wq = false;
			अगर (!wqe_idx && (qp->sq_ring.head == qp->sq_ring.tail)) अणु
				I40IW_RING_MOVE_HEAD_NOCHECK(cq->cq_ring);
				I40IW_RING_MOVE_TAIL(cq->cq_ring);
				set_64bit_val(cq->shaकरोw_area, 0,
					      I40IW_RING_GETCURRENT_HEAD(cq->cq_ring));
				स_रखो(info, 0, माप(काष्ठा i40iw_cq_poll_info));
				वापस i40iw_cq_poll_completion(cq, info);
			पूर्ण
		पूर्ण

		अगर (info->comp_status != I40IW_COMPL_STATUS_FLUSHED) अणु
			info->wr_id = qp->sq_wrtrk_array[wqe_idx].wrid;
			info->bytes_xfered = qp->sq_wrtrk_array[wqe_idx].wr_len;

			info->op_type = (u8)RS_64(qword3, I40IWCQ_OP);
			sw_wqe = qp->sq_base[wqe_idx].elem;
			get_64bit_val(sw_wqe, 24, &wqe_qword);

			addl_wqes = qp->sq_wrtrk_array[wqe_idx].wqe_size / I40IW_QP_WQE_MIN_SIZE;
			I40IW_RING_SET_TAIL(qp->sq_ring, (wqe_idx + addl_wqes));
		पूर्ण अन्यथा अणु
			करो अणु
				u8 op_type;
				u32 tail;

				tail = qp->sq_ring.tail;
				sw_wqe = qp->sq_base[tail].elem;
				get_64bit_val(sw_wqe, 24, &wqe_qword);
				op_type = (u8)RS_64(wqe_qword, I40IWQPSQ_OPCODE);
				info->op_type = op_type;
				addl_wqes = qp->sq_wrtrk_array[tail].wqe_size / I40IW_QP_WQE_MIN_SIZE;
				I40IW_RING_SET_TAIL(qp->sq_ring, (tail + addl_wqes));
				अगर (op_type != I40IWQP_OP_NOP) अणु
					info->wr_id = qp->sq_wrtrk_array[tail].wrid;
					info->bytes_xfered = qp->sq_wrtrk_array[tail].wr_len;
					अवरोध;
				पूर्ण
			पूर्ण जबतक (1);
		पूर्ण
		pring = &qp->sq_ring;
	पूर्ण

	ret_code = 0;

निकास:
	अगर (!ret_code &&
	    (info->comp_status == I40IW_COMPL_STATUS_FLUSHED))
		अगर (pring && (I40IW_RING_MORE_WORK(*pring)))
			move_cq_head = false;

	अगर (move_cq_head) अणु
		I40IW_RING_MOVE_HEAD_NOCHECK(cq->cq_ring);

		अगर (I40IW_RING_GETCURRENT_HEAD(cq->cq_ring) == 0)
			cq->polarity ^= 1;

		I40IW_RING_MOVE_TAIL(cq->cq_ring);
		set_64bit_val(cq->shaकरोw_area, 0,
			      I40IW_RING_GETCURRENT_HEAD(cq->cq_ring));
	पूर्ण अन्यथा अणु
		अगर (info->is_srq)
			वापस ret_code;
		qword3 &= ~I40IW_CQ_WQEIDX_MASK;
		qword3 |= LS_64(pring->tail, I40IW_CQ_WQEIDX);
		set_64bit_val(cqe, 24, qword3);
	पूर्ण

	वापस ret_code;
पूर्ण

/**
 * i40iw_get_wqe_shअगरt - get shअगरt count क्रम maximum wqe size
 * @sge: Maximum Scatter Gather Elements wqe
 * @अंतरभूत_data: Maximum अंतरभूत data size
 * @shअगरt: Returns the shअगरt needed based on sge
 *
 * Shअगरt can be used to left shअगरt the wqe size based on number of SGEs and inlind data size.
 * For 1 SGE or अंतरभूत data <= 16, shअगरt = 0 (wqe size of 32 bytes).
 * For 2 or 3 SGEs or अंतरभूत data <= 48, shअगरt = 1 (wqe size of 64 bytes).
 * Shअगरt of 2 otherwise (wqe size of 128 bytes).
 */
व्योम i40iw_get_wqe_shअगरt(u32 sge, u32 अंतरभूत_data, u8 *shअगरt)
अणु
	*shअगरt = 0;
	अगर (sge > 1 || अंतरभूत_data > 16)
		*shअगरt = (sge < 4 && अंतरभूत_data <= 48) ? 1 : 2;
पूर्ण

/*
 * i40iw_get_sqdepth - get SQ depth (quantas)
 * @sq_size: SQ size
 * @shअगरt: shअगरt which determines size of WQE
 * @sqdepth: depth of SQ
 *
 */
क्रमागत i40iw_status_code i40iw_get_sqdepth(u32 sq_size, u8 shअगरt, u32 *sqdepth)
अणु
	*sqdepth = roundup_घात_of_two((sq_size << shअगरt) + I40IW_SQ_RSVD);

	अगर (*sqdepth < (I40IW_QP_SW_MIN_WQSIZE << shअगरt))
		*sqdepth = I40IW_QP_SW_MIN_WQSIZE << shअगरt;
	अन्यथा अगर (*sqdepth > I40IW_QP_SW_MAX_SQ_QUANTAS)
		वापस I40IW_ERR_INVALID_SIZE;

	वापस 0;
पूर्ण

/*
 * i40iw_get_rq_depth - get RQ depth (quantas)
 * @rq_size: RQ size
 * @shअगरt: shअगरt which determines size of WQE
 * @rqdepth: depth of RQ
 *
 */
क्रमागत i40iw_status_code i40iw_get_rqdepth(u32 rq_size, u8 shअगरt, u32 *rqdepth)
अणु
	*rqdepth = roundup_घात_of_two((rq_size << shअगरt) + I40IW_RQ_RSVD);

	अगर (*rqdepth < (I40IW_QP_SW_MIN_WQSIZE << shअगरt))
		*rqdepth = I40IW_QP_SW_MIN_WQSIZE << shअगरt;
	अन्यथा अगर (*rqdepth > I40IW_QP_SW_MAX_RQ_QUANTAS)
		वापस I40IW_ERR_INVALID_SIZE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i40iw_qp_uk_ops iw_qp_uk_ops = अणु
	.iw_qp_post_wr = i40iw_qp_post_wr,
	.iw_rdma_ग_लिखो = i40iw_rdma_ग_लिखो,
	.iw_rdma_पढ़ो = i40iw_rdma_पढ़ो,
	.iw_send = i40iw_send,
	.iw_अंतरभूत_rdma_ग_लिखो = i40iw_अंतरभूत_rdma_ग_लिखो,
	.iw_अंतरभूत_send = i40iw_अंतरभूत_send,
	.iw_stag_local_invalidate = i40iw_stag_local_invalidate,
	.iw_mw_bind = i40iw_mw_bind,
	.iw_post_receive = i40iw_post_receive,
	.iw_post_nop = i40iw_nop
पूर्ण;

अटल स्थिर काष्ठा i40iw_cq_ops iw_cq_ops = अणु
	.iw_cq_request_notअगरication = i40iw_cq_request_notअगरication,
	.iw_cq_poll_completion = i40iw_cq_poll_completion,
	.iw_cq_post_entries = i40iw_cq_post_entries,
	.iw_cq_clean = i40iw_clean_cq
पूर्ण;

अटल स्थिर काष्ठा i40iw_device_uk_ops iw_device_uk_ops = अणु
	.iwarp_cq_uk_init = i40iw_cq_uk_init,
	.iwarp_qp_uk_init = i40iw_qp_uk_init,
पूर्ण;

/**
 * i40iw_qp_uk_init - initialize shared qp
 * @qp: hw qp (user and kernel)
 * @info: qp initialization info
 *
 * initializes the vars used in both user and kernel mode.
 * size of the wqe depends on numbers of max. fragements
 * allowed. Then size of wqe * the number of wqes should be the
 * amount of memory allocated क्रम sq and rq. If srq is used,
 * then rq_base will poपूर्णांक to one rq wqe only (not the whole
 * array of wqes)
 */
क्रमागत i40iw_status_code i40iw_qp_uk_init(काष्ठा i40iw_qp_uk *qp,
					काष्ठा i40iw_qp_uk_init_info *info)
अणु
	क्रमागत i40iw_status_code ret_code = 0;
	u32 sq_ring_size;
	u8 sqshअगरt, rqshअगरt;

	अगर (info->max_sq_frag_cnt > I40IW_MAX_WQ_FRAGMENT_COUNT)
		वापस I40IW_ERR_INVALID_FRAG_COUNT;

	अगर (info->max_rq_frag_cnt > I40IW_MAX_WQ_FRAGMENT_COUNT)
		वापस I40IW_ERR_INVALID_FRAG_COUNT;
	i40iw_get_wqe_shअगरt(info->max_sq_frag_cnt, info->max_अंतरभूत_data, &sqshअगरt);

	qp->sq_base = info->sq;
	qp->rq_base = info->rq;
	qp->shaकरोw_area = info->shaकरोw_area;
	qp->sq_wrtrk_array = info->sq_wrtrk_array;
	qp->rq_wrid_array = info->rq_wrid_array;

	qp->wqe_alloc_reg = info->wqe_alloc_reg;
	qp->qp_id = info->qp_id;
	qp->sq_size = info->sq_size;
	qp->max_sq_frag_cnt = info->max_sq_frag_cnt;
	sq_ring_size = qp->sq_size << sqshअगरt;

	I40IW_RING_INIT(qp->sq_ring, sq_ring_size);
	I40IW_RING_INIT(qp->initial_ring, sq_ring_size);
	I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
	I40IW_RING_MOVE_TAIL(qp->sq_ring);
	I40IW_RING_MOVE_HEAD(qp->initial_ring, ret_code);
	qp->swqe_polarity = 1;
	qp->first_sq_wq = true;
	qp->swqe_polarity_deferred = 1;
	qp->rwqe_polarity = 0;

	अगर (!qp->use_srq) अणु
		qp->rq_size = info->rq_size;
		qp->max_rq_frag_cnt = info->max_rq_frag_cnt;
		I40IW_RING_INIT(qp->rq_ring, qp->rq_size);
		चयन (info->abi_ver) अणु
		हाल 4:
			i40iw_get_wqe_shअगरt(info->max_rq_frag_cnt, 0, &rqshअगरt);
			अवरोध;
		हाल 5: /* fallthrough until next ABI version */
		शेष:
			rqshअगरt = I40IW_MAX_RQ_WQE_SHIFT;
			अवरोध;
		पूर्ण
		qp->rq_wqe_size = rqshअगरt;
		qp->rq_wqe_size_multiplier = 4 << rqshअगरt;
	पूर्ण
	qp->ops = iw_qp_uk_ops;

	वापस ret_code;
पूर्ण

/**
 * i40iw_cq_uk_init - initialize shared cq (user and kernel)
 * @cq: hw cq
 * @info: hw cq initialization info
 */
क्रमागत i40iw_status_code i40iw_cq_uk_init(काष्ठा i40iw_cq_uk *cq,
					काष्ठा i40iw_cq_uk_init_info *info)
अणु
	अगर ((info->cq_size < I40IW_MIN_CQ_SIZE) ||
	    (info->cq_size > I40IW_MAX_CQ_SIZE))
		वापस I40IW_ERR_INVALID_SIZE;
	cq->cq_base = (काष्ठा i40iw_cqe *)info->cq_base;
	cq->cq_id = info->cq_id;
	cq->cq_size = info->cq_size;
	cq->cqe_alloc_reg = info->cqe_alloc_reg;
	cq->shaकरोw_area = info->shaकरोw_area;
	cq->aव्योम_mem_cflct = info->aव्योम_mem_cflct;

	I40IW_RING_INIT(cq->cq_ring, cq->cq_size);
	cq->polarity = 1;
	cq->ops = iw_cq_ops;

	वापस 0;
पूर्ण

/**
 * i40iw_device_init_uk - setup routines क्रम iwarp shared device
 * @dev: iwarp shared (user and kernel)
 */
व्योम i40iw_device_init_uk(काष्ठा i40iw_dev_uk *dev)
अणु
	dev->ops_uk = iw_device_uk_ops;
पूर्ण

/**
 * i40iw_clean_cq - clean cq entries
 * @queue: completion context
 * @cq: cq to clean
 */
व्योम i40iw_clean_cq(व्योम *queue, काष्ठा i40iw_cq_uk *cq)
अणु
	u64 *cqe;
	u64 qword3, comp_ctx;
	u32 cq_head;
	u8 polarity, temp;

	cq_head = cq->cq_ring.head;
	temp = cq->polarity;
	करो अणु
		अगर (cq->aव्योम_mem_cflct)
			cqe = (u64 *)&(((काष्ठा i40iw_extended_cqe *)cq->cq_base)[cq_head]);
		अन्यथा
			cqe = (u64 *)&cq->cq_base[cq_head];
		get_64bit_val(cqe, 24, &qword3);
		polarity = (u8)RS_64(qword3, I40IW_CQ_VALID);

		अगर (polarity != temp)
			अवरोध;

		get_64bit_val(cqe, 8, &comp_ctx);
		अगर ((व्योम *)(अचिन्हित दीर्घ)comp_ctx == queue)
			set_64bit_val(cqe, 8, 0);

		cq_head = (cq_head + 1) % cq->cq_ring.size;
		अगर (!cq_head)
			temp ^= 1;
	पूर्ण जबतक (true);
पूर्ण

/**
 * i40iw_nop - send a nop
 * @qp: hw qp ptr
 * @wr_id: work request id
 * @संकेतed: flag अगर संकेतed क्रम completion
 * @post_sq: flag to post sq
 */
क्रमागत i40iw_status_code i40iw_nop(काष्ठा i40iw_qp_uk *qp,
				 u64 wr_id,
				 bool संकेतed,
				 bool post_sq)
अणु
	u64 header, *wqe;
	u32 wqe_idx;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, I40IW_QP_WQE_MIN_SIZE, 0, wr_id);
	अगर (!wqe)
		वापस I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	set_64bit_val(wqe, 0, 0);
	set_64bit_val(wqe, 8, 0);
	set_64bit_val(wqe, 16, 0);

	header = LS_64(I40IWQP_OP_NOP, I40IWQPSQ_OPCODE) |
	    LS_64(संकेतed, I40IWQPSQ_SIGCOMPL) |
	    LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	wmb(); /* make sure WQE is populated beक्रमe valid bit is set */

	set_64bit_val(wqe, 24, header);
	अगर (post_sq)
		i40iw_qp_post_wr(qp);

	वापस 0;
पूर्ण

/**
 * i40iw_fragcnt_to_wqesize_sq - calculate wqe size based on fragment count क्रम SQ
 * @frag_cnt: number of fragments
 * @wqe_size: size of sq wqe वापसed
 */
क्रमागत i40iw_status_code i40iw_fragcnt_to_wqesize_sq(u32 frag_cnt, u8 *wqe_size)
अणु
	चयन (frag_cnt) अणु
	हाल 0:
	हाल 1:
		*wqe_size = I40IW_QP_WQE_MIN_SIZE;
		अवरोध;
	हाल 2:
	हाल 3:
		*wqe_size = 64;
		अवरोध;
	हाल 4:
	हाल 5:
		*wqe_size = 96;
		अवरोध;
	हाल 6:
	हाल 7:
		*wqe_size = 128;
		अवरोध;
	शेष:
		वापस I40IW_ERR_INVALID_FRAG_COUNT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40iw_fragcnt_to_wqesize_rq - calculate wqe size based on fragment count क्रम RQ
 * @frag_cnt: number of fragments
 * @wqe_size: size of rq wqe वापसed
 */
क्रमागत i40iw_status_code i40iw_fragcnt_to_wqesize_rq(u32 frag_cnt, u8 *wqe_size)
अणु
	चयन (frag_cnt) अणु
	हाल 0:
	हाल 1:
		*wqe_size = 32;
		अवरोध;
	हाल 2:
	हाल 3:
		*wqe_size = 64;
		अवरोध;
	हाल 4:
	हाल 5:
	हाल 6:
	हाल 7:
		*wqe_size = 128;
		अवरोध;
	शेष:
		वापस I40IW_ERR_INVALID_FRAG_COUNT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40iw_अंतरभूत_data_माप_प्रकारo_wqesize - based on अंतरभूत data, wqe size
 * @data_size: data size क्रम अंतरभूत
 * @wqe_size: size of sq wqe वापसed
 */
क्रमागत i40iw_status_code i40iw_अंतरभूत_data_माप_प्रकारo_wqesize(u32 data_size,
							 u8 *wqe_size)
अणु
	अगर (data_size > I40IW_MAX_INLINE_DATA_SIZE)
		वापस I40IW_ERR_INVALID_INLINE_DATA_SIZE;

	अगर (data_size <= 16)
		*wqe_size = I40IW_QP_WQE_MIN_SIZE;
	अन्यथा
		*wqe_size = 64;

	वापस 0;
पूर्ण
