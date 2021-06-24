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

#अगर_अघोषित I40IW_USER_H
#घोषणा I40IW_USER_H

क्रमागत i40iw_device_capabilities_स्थिर अणु
	I40IW_WQE_SIZE =			4,
	I40IW_CQP_WQE_SIZE =			8,
	I40IW_CQE_SIZE =			4,
	I40IW_EXTENDED_CQE_SIZE =		8,
	I40IW_AEQE_SIZE =			2,
	I40IW_CEQE_SIZE =			1,
	I40IW_CQP_CTX_SIZE =			8,
	I40IW_SHADOW_AREA_SIZE =		8,
	I40IW_CEQ_MAX_COUNT =			256,
	I40IW_QUERY_FPM_BUF_SIZE =		128,
	I40IW_COMMIT_FPM_BUF_SIZE =		128,
	I40IW_MIN_IW_QP_ID =			1,
	I40IW_MAX_IW_QP_ID =			262143,
	I40IW_MIN_CEQID =			0,
	I40IW_MAX_CEQID =			256,
	I40IW_MIN_CQID =			0,
	I40IW_MAX_CQID =			131071,
	I40IW_MIN_AEQ_ENTRIES =			1,
	I40IW_MAX_AEQ_ENTRIES =			524287,
	I40IW_MIN_CEQ_ENTRIES =			1,
	I40IW_MAX_CEQ_ENTRIES =			131071,
	I40IW_MIN_CQ_SIZE =			1,
	I40IW_MAX_CQ_SIZE =			1048575,
	I40IW_DB_ID_ZERO =			0,
	I40IW_MAX_WQ_FRAGMENT_COUNT =		3,
	I40IW_MAX_SGE_RD =			1,
	I40IW_MAX_OUTBOUND_MESSAGE_SIZE =	2147483647,
	I40IW_MAX_INBOUND_MESSAGE_SIZE =	2147483647,
	I40IW_MAX_PE_ENABLED_VF_COUNT =		32,
	I40IW_MAX_VF_FPM_ID =			47,
	I40IW_MAX_VF_PER_PF =			127,
	I40IW_MAX_SQ_PAYLOAD_SIZE =		2145386496,
	I40IW_MAX_INLINE_DATA_SIZE =		48,
	I40IW_MAX_IRD_SIZE =			64,
	I40IW_MAX_ORD_SIZE =			127,
	I40IW_MAX_WQ_ENTRIES =			2048,
	I40IW_Q2_BUFFER_SIZE =			(248 + 100),
	I40IW_MAX_WQE_SIZE_RQ =			128,
	I40IW_QP_CTX_SIZE =			248,
	I40IW_MAX_PDS = 			32768
पूर्ण;

#घोषणा i40iw_handle व्योम *
#घोषणा i40iw_adapter_handle i40iw_handle
#घोषणा i40iw_qp_handle i40iw_handle
#घोषणा i40iw_cq_handle i40iw_handle
#घोषणा i40iw_srq_handle i40iw_handle
#घोषणा i40iw_pd_id i40iw_handle
#घोषणा i40iw_stag_handle i40iw_handle
#घोषणा i40iw_stag_index u32
#घोषणा i40iw_stag u32
#घोषणा i40iw_stag_key u8

#घोषणा i40iw_tagged_offset u64
#घोषणा i40iw_access_privileges u32
#घोषणा i40iw_physical_fragment u64
#घोषणा i40iw_address_list u64 *

#घोषणा	I40IW_MAX_MR_SIZE	0x10000000000L
#घोषणा	I40IW_MAX_RQ_WQE_SHIFT	2

काष्ठा i40iw_qp_uk;
काष्ठा i40iw_cq_uk;
काष्ठा i40iw_srq_uk;
काष्ठा i40iw_qp_uk_init_info;
काष्ठा i40iw_cq_uk_init_info;
काष्ठा i40iw_srq_uk_init_info;

काष्ठा i40iw_sge अणु
	i40iw_tagged_offset tag_off;
	u32 len;
	i40iw_stag stag;
पूर्ण;

#घोषणा i40iw_sgl काष्ठा i40iw_sge *

काष्ठा i40iw_ring अणु
	u32 head;
	u32 tail;
	u32 size;
पूर्ण;

काष्ठा i40iw_cqe अणु
	u64 buf[I40IW_CQE_SIZE];
पूर्ण;

काष्ठा i40iw_extended_cqe अणु
	u64 buf[I40IW_EXTENDED_CQE_SIZE];
पूर्ण;

काष्ठा i40iw_wqe अणु
	u64 buf[I40IW_WQE_SIZE];
पूर्ण;

काष्ठा i40iw_qp_uk_ops;

क्रमागत i40iw_addressing_type अणु
	I40IW_ADDR_TYPE_ZERO_BASED = 0,
	I40IW_ADDR_TYPE_VA_BASED = 1,
पूर्ण;

#घोषणा I40IW_ACCESS_FLAGS_LOCALREAD		0x01
#घोषणा I40IW_ACCESS_FLAGS_LOCALWRITE		0x02
#घोषणा I40IW_ACCESS_FLAGS_REMOTEREAD_ONLY	0x04
#घोषणा I40IW_ACCESS_FLAGS_REMOTEREAD		0x05
#घोषणा I40IW_ACCESS_FLAGS_REMOTEWRITE_ONLY	0x08
#घोषणा I40IW_ACCESS_FLAGS_REMOTEWRITE		0x0a
#घोषणा I40IW_ACCESS_FLAGS_BIND_WINDOW		0x10
#घोषणा I40IW_ACCESS_FLAGS_ALL			0x1F

#घोषणा I40IW_OP_TYPE_RDMA_WRITE	0
#घोषणा I40IW_OP_TYPE_RDMA_READ		1
#घोषणा I40IW_OP_TYPE_SEND		3
#घोषणा I40IW_OP_TYPE_SEND_INV		4
#घोषणा I40IW_OP_TYPE_SEND_SOL		5
#घोषणा I40IW_OP_TYPE_SEND_SOL_INV	6
#घोषणा I40IW_OP_TYPE_REC		7
#घोषणा I40IW_OP_TYPE_BIND_MW		8
#घोषणा I40IW_OP_TYPE_FAST_REG_NSMR	9
#घोषणा I40IW_OP_TYPE_INV_STAG		10
#घोषणा I40IW_OP_TYPE_RDMA_READ_INV_STAG 11
#घोषणा I40IW_OP_TYPE_NOP		12

क्रमागत i40iw_completion_status अणु
	I40IW_COMPL_STATUS_SUCCESS = 0,
	I40IW_COMPL_STATUS_FLUSHED,
	I40IW_COMPL_STATUS_INVALID_WQE,
	I40IW_COMPL_STATUS_QP_CATASTROPHIC,
	I40IW_COMPL_STATUS_REMOTE_TERMINATION,
	I40IW_COMPL_STATUS_INVALID_STAG,
	I40IW_COMPL_STATUS_BASE_BOUND_VIOLATION,
	I40IW_COMPL_STATUS_ACCESS_VIOLATION,
	I40IW_COMPL_STATUS_INVALID_PD_ID,
	I40IW_COMPL_STATUS_WRAP_ERROR,
	I40IW_COMPL_STATUS_STAG_INVALID_PDID,
	I40IW_COMPL_STATUS_RDMA_READ_ZERO_ORD,
	I40IW_COMPL_STATUS_QP_NOT_PRIVLEDGED,
	I40IW_COMPL_STATUS_STAG_NOT_INVALID,
	I40IW_COMPL_STATUS_INVALID_PHYS_BUFFER_SIZE,
	I40IW_COMPL_STATUS_INVALID_PHYS_BUFFER_ENTRY,
	I40IW_COMPL_STATUS_INVALID_FBO,
	I40IW_COMPL_STATUS_INVALID_LENGTH,
	I40IW_COMPL_STATUS_INVALID_ACCESS,
	I40IW_COMPL_STATUS_PHYS_BUFFER_LIST_TOO_LONG,
	I40IW_COMPL_STATUS_INVALID_VIRT_ADDRESS,
	I40IW_COMPL_STATUS_INVALID_REGION,
	I40IW_COMPL_STATUS_INVALID_WINDOW,
	I40IW_COMPL_STATUS_INVALID_TOTAL_LENGTH
पूर्ण;

क्रमागत i40iw_completion_notअगरy अणु
	IW_CQ_COMPL_EVENT = 0,
	IW_CQ_COMPL_SOLICITED = 1
पूर्ण;

काष्ठा i40iw_post_send अणु
	i40iw_sgl sg_list;
	u32 num_sges;
पूर्ण;

काष्ठा i40iw_post_अंतरभूत_send अणु
	व्योम *data;
	u32 len;
पूर्ण;

काष्ठा i40iw_rdma_ग_लिखो अणु
	i40iw_sgl lo_sg_list;
	u32 num_lo_sges;
	काष्ठा i40iw_sge rem_addr;
पूर्ण;

काष्ठा i40iw_अंतरभूत_rdma_ग_लिखो अणु
	व्योम *data;
	u32 len;
	काष्ठा i40iw_sge rem_addr;
पूर्ण;

काष्ठा i40iw_rdma_पढ़ो अणु
	काष्ठा i40iw_sge lo_addr;
	काष्ठा i40iw_sge rem_addr;
पूर्ण;

काष्ठा i40iw_bind_winकरोw अणु
	i40iw_stag mr_stag;
	u64 bind_length;
	व्योम *va;
	क्रमागत i40iw_addressing_type addressing_type;
	bool enable_पढ़ोs;
	bool enable_ग_लिखोs;
	i40iw_stag mw_stag;
पूर्ण;

काष्ठा i40iw_inv_local_stag अणु
	i40iw_stag target_stag;
पूर्ण;

काष्ठा i40iw_post_sq_info अणु
	u64 wr_id;
	u8 op_type;
	bool संकेतed;
	bool पढ़ो_fence;
	bool local_fence;
	bool अंतरभूत_data;
	bool defer_flag;
	जोड़ अणु
		काष्ठा i40iw_post_send send;
		काष्ठा i40iw_rdma_ग_लिखो rdma_ग_लिखो;
		काष्ठा i40iw_rdma_पढ़ो rdma_पढ़ो;
		काष्ठा i40iw_rdma_पढ़ो rdma_पढ़ो_inv;
		काष्ठा i40iw_bind_winकरोw bind_winकरोw;
		काष्ठा i40iw_inv_local_stag inv_local_stag;
		काष्ठा i40iw_अंतरभूत_rdma_ग_लिखो अंतरभूत_rdma_ग_लिखो;
		काष्ठा i40iw_post_अंतरभूत_send अंतरभूत_send;
	पूर्ण op;
पूर्ण;

काष्ठा i40iw_post_rq_info अणु
	u64 wr_id;
	i40iw_sgl sg_list;
	u32 num_sges;
पूर्ण;

काष्ठा i40iw_cq_poll_info अणु
	u64 wr_id;
	i40iw_qp_handle qp_handle;
	u32 bytes_xfered;
	u32 tcp_seq_num;
	u32 qp_id;
	i40iw_stag inv_stag;
	क्रमागत i40iw_completion_status comp_status;
	u16 major_err;
	u16 minor_err;
	u8 op_type;
	bool stag_invalid_set;
	bool error;
	bool is_srq;
	bool solicited_event;
पूर्ण;

काष्ठा i40iw_qp_uk_ops अणु
	व्योम (*iw_qp_post_wr)(काष्ठा i40iw_qp_uk *);
	क्रमागत i40iw_status_code (*iw_rdma_ग_लिखो)(काष्ठा i40iw_qp_uk *,
						काष्ठा i40iw_post_sq_info *, bool);
	क्रमागत i40iw_status_code (*iw_rdma_पढ़ो)(काष्ठा i40iw_qp_uk *,
					       काष्ठा i40iw_post_sq_info *, bool, bool);
	क्रमागत i40iw_status_code (*iw_send)(काष्ठा i40iw_qp_uk *,
					  काष्ठा i40iw_post_sq_info *, u32, bool);
	क्रमागत i40iw_status_code (*iw_अंतरभूत_rdma_ग_लिखो)(काष्ठा i40iw_qp_uk *,
						       काष्ठा i40iw_post_sq_info *, bool);
	क्रमागत i40iw_status_code (*iw_अंतरभूत_send)(काष्ठा i40iw_qp_uk *,
						 काष्ठा i40iw_post_sq_info *, u32, bool);
	क्रमागत i40iw_status_code (*iw_stag_local_invalidate)(काष्ठा i40iw_qp_uk *,
							   काष्ठा i40iw_post_sq_info *, bool);
	क्रमागत i40iw_status_code (*iw_mw_bind)(काष्ठा i40iw_qp_uk *,
					     काष्ठा i40iw_post_sq_info *, bool);
	क्रमागत i40iw_status_code (*iw_post_receive)(काष्ठा i40iw_qp_uk *,
						  काष्ठा i40iw_post_rq_info *);
	क्रमागत i40iw_status_code (*iw_post_nop)(काष्ठा i40iw_qp_uk *, u64, bool, bool);
पूर्ण;

काष्ठा i40iw_cq_ops अणु
	व्योम (*iw_cq_request_notअगरication)(काष्ठा i40iw_cq_uk *,
					   क्रमागत i40iw_completion_notअगरy);
	क्रमागत i40iw_status_code (*iw_cq_poll_completion)(काष्ठा i40iw_cq_uk *,
							काष्ठा i40iw_cq_poll_info *);
	क्रमागत i40iw_status_code (*iw_cq_post_entries)(काष्ठा i40iw_cq_uk *, u8 count);
	व्योम (*iw_cq_clean)(व्योम *, काष्ठा i40iw_cq_uk *);
पूर्ण;

काष्ठा i40iw_dev_uk;

काष्ठा i40iw_device_uk_ops अणु
	क्रमागत i40iw_status_code (*iwarp_cq_uk_init)(काष्ठा i40iw_cq_uk *,
						   काष्ठा i40iw_cq_uk_init_info *);
	क्रमागत i40iw_status_code (*iwarp_qp_uk_init)(काष्ठा i40iw_qp_uk *,
						   काष्ठा i40iw_qp_uk_init_info *);
पूर्ण;

काष्ठा i40iw_dev_uk अणु
	काष्ठा i40iw_device_uk_ops ops_uk;
पूर्ण;

काष्ठा i40iw_sq_uk_wr_trk_info अणु
	u64 wrid;
	u32 wr_len;
	u8 wqe_size;
	u8 reserved[3];
पूर्ण;

काष्ठा i40iw_qp_quanta अणु
	u64 elem[I40IW_WQE_SIZE];
पूर्ण;

काष्ठा i40iw_qp_uk अणु
	काष्ठा i40iw_qp_quanta *sq_base;
	काष्ठा i40iw_qp_quanta *rq_base;
	u32 __iomem *wqe_alloc_reg;
	काष्ठा i40iw_sq_uk_wr_trk_info *sq_wrtrk_array;
	u64 *rq_wrid_array;
	u64 *shaकरोw_area;
	काष्ठा i40iw_ring sq_ring;
	काष्ठा i40iw_ring rq_ring;
	काष्ठा i40iw_ring initial_ring;
	u32 qp_id;
	u32 sq_size;
	u32 rq_size;
	u32 max_sq_frag_cnt;
	u32 max_rq_frag_cnt;
	काष्ठा i40iw_qp_uk_ops ops;
	bool use_srq;
	u8 swqe_polarity;
	u8 swqe_polarity_deferred;
	u8 rwqe_polarity;
	u8 rq_wqe_size;
	u8 rq_wqe_size_multiplier;
	bool first_sq_wq;
	bool deferred_flag;
पूर्ण;

काष्ठा i40iw_cq_uk अणु
	काष्ठा i40iw_cqe *cq_base;
	u32 __iomem *cqe_alloc_reg;
	u64 *shaकरोw_area;
	u32 cq_id;
	u32 cq_size;
	काष्ठा i40iw_ring cq_ring;
	u8 polarity;
	bool aव्योम_mem_cflct;

	काष्ठा i40iw_cq_ops ops;
पूर्ण;

काष्ठा i40iw_qp_uk_init_info अणु
	काष्ठा i40iw_qp_quanta *sq;
	काष्ठा i40iw_qp_quanta *rq;
	u32 __iomem *wqe_alloc_reg;
	u64 *shaकरोw_area;
	काष्ठा i40iw_sq_uk_wr_trk_info *sq_wrtrk_array;
	u64 *rq_wrid_array;
	u32 qp_id;
	u32 sq_size;
	u32 rq_size;
	u32 max_sq_frag_cnt;
	u32 max_rq_frag_cnt;
	u32 max_अंतरभूत_data;
	पूर्णांक abi_ver;
पूर्ण;

काष्ठा i40iw_cq_uk_init_info अणु
	u32 __iomem *cqe_alloc_reg;
	काष्ठा i40iw_cqe *cq_base;
	u64 *shaकरोw_area;
	u32 cq_size;
	u32 cq_id;
	bool aव्योम_mem_cflct;
पूर्ण;

व्योम i40iw_device_init_uk(काष्ठा i40iw_dev_uk *dev);

व्योम i40iw_qp_post_wr(काष्ठा i40iw_qp_uk *qp);
u64 *i40iw_qp_get_next_send_wqe(काष्ठा i40iw_qp_uk *qp, u32 *wqe_idx,
				u8 wqe_size,
				u32 total_size,
				u64 wr_id
				);
u64 *i40iw_qp_get_next_recv_wqe(काष्ठा i40iw_qp_uk *qp, u32 *wqe_idx);
u64 *i40iw_qp_get_next_srq_wqe(काष्ठा i40iw_srq_uk *srq, u32 *wqe_idx);

क्रमागत i40iw_status_code i40iw_cq_uk_init(काष्ठा i40iw_cq_uk *cq,
					काष्ठा i40iw_cq_uk_init_info *info);
क्रमागत i40iw_status_code i40iw_qp_uk_init(काष्ठा i40iw_qp_uk *qp,
					काष्ठा i40iw_qp_uk_init_info *info);

व्योम i40iw_clean_cq(व्योम *queue, काष्ठा i40iw_cq_uk *cq);
क्रमागत i40iw_status_code i40iw_nop(काष्ठा i40iw_qp_uk *qp, u64 wr_id,
				 bool संकेतed, bool post_sq);
क्रमागत i40iw_status_code i40iw_fragcnt_to_wqesize_sq(u32 frag_cnt, u8 *wqe_size);
क्रमागत i40iw_status_code i40iw_fragcnt_to_wqesize_rq(u32 frag_cnt, u8 *wqe_size);
क्रमागत i40iw_status_code i40iw_अंतरभूत_data_माप_प्रकारo_wqesize(u32 data_size,
							 u8 *wqe_size);
व्योम i40iw_get_wqe_shअगरt(u32 sge, u32 अंतरभूत_data, u8 *shअगरt);
क्रमागत i40iw_status_code i40iw_get_sqdepth(u32 sq_size, u8 shअगरt, u32 *sqdepth);
क्रमागत i40iw_status_code i40iw_get_rqdepth(u32 rq_size, u8 shअगरt, u32 *rqdepth);
#पूर्ण_अगर
