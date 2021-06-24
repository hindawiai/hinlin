<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#अगर_अघोषित __QEDR_USER_H__
#घोषणा __QEDR_USER_H__

#समावेश <linux/types.h>

#घोषणा QEDR_ABI_VERSION		(8)

/* user kernel communication data काष्ठाures. */
क्रमागत qedr_alloc_ucontext_flags अणु
	QEDR_ALLOC_UCTX_EDPM_MODE	= 1 << 0,
	QEDR_ALLOC_UCTX_DB_REC		= 1 << 1,
	QEDR_SUPPORT_DPM_SIZES		= 1 << 2,
पूर्ण;

काष्ठा qedr_alloc_ucontext_req अणु
	__u32 context_flags;
	__u32 reserved;
पूर्ण;

#घोषणा QEDR_LDPM_MAX_SIZE	(8192)
#घोषणा QEDR_EDPM_TRANS_SIZE	(64)
#घोषणा QEDR_EDPM_MAX_SIZE	(ROCE_REQ_MAX_INLINE_DATA_SIZE)

क्रमागत qedr_rdma_dpm_type अणु
	QEDR_DPM_TYPE_NONE		= 0,
	QEDR_DPM_TYPE_ROCE_ENHANCED	= 1 << 0,
	QEDR_DPM_TYPE_ROCE_LEGACY	= 1 << 1,
	QEDR_DPM_TYPE_IWARP_LEGACY	= 1 << 2,
	QEDR_DPM_TYPE_ROCE_EDPM_MODE	= 1 << 3,
	QEDR_DPM_SIZES_SET		= 1 << 4,
पूर्ण;

काष्ठा qedr_alloc_ucontext_resp अणु
	__aligned_u64 db_pa;
	__u32 db_size;

	__u32 max_send_wr;
	__u32 max_recv_wr;
	__u32 max_srq_wr;
	__u32 sges_per_send_wr;
	__u32 sges_per_recv_wr;
	__u32 sges_per_srq_wr;
	__u32 max_cqes;
	__u8 dpm_flags;
	__u8 wids_enabled;
	__u16 wid_count;
	__u16 ldpm_limit_size;
	__u8 edpm_trans_size;
	__u8 reserved;
	__u16 edpm_limit_size;
	__u8 padding[6];
पूर्ण;

काष्ठा qedr_alloc_pd_ureq अणु
	__aligned_u64 rsvd1;
पूर्ण;

काष्ठा qedr_alloc_pd_uresp अणु
	__u32 pd_id;
	__u32 reserved;
पूर्ण;

काष्ठा qedr_create_cq_ureq अणु
	__aligned_u64 addr;
	__aligned_u64 len;
पूर्ण;

काष्ठा qedr_create_cq_uresp अणु
	__u32 db_offset;
	__u16 icid;
	__u16 reserved;
	__aligned_u64 db_rec_addr;
पूर्ण;

काष्ठा qedr_create_qp_ureq अणु
	__u32 qp_handle_hi;
	__u32 qp_handle_lo;

	/* SQ */
	/* user space भव address of SQ buffer */
	__aligned_u64 sq_addr;

	/* length of SQ buffer */
	__aligned_u64 sq_len;

	/* RQ */
	/* user space भव address of RQ buffer */
	__aligned_u64 rq_addr;

	/* length of RQ buffer */
	__aligned_u64 rq_len;
पूर्ण;

काष्ठा qedr_create_qp_uresp अणु
	__u32 qp_id;
	__u32 atomic_supported;

	/* SQ */
	__u32 sq_db_offset;
	__u16 sq_icid;

	/* RQ */
	__u32 rq_db_offset;
	__u16 rq_icid;

	__u32 rq_db2_offset;
	__u32 reserved;

	/* address of SQ करोorbell recovery user entry */
	__aligned_u64 sq_db_rec_addr;

	/* address of RQ करोorbell recovery user entry */
	__aligned_u64 rq_db_rec_addr;

पूर्ण;

काष्ठा qedr_create_srq_ureq अणु
	/* user space भव address of producer pair */
	__aligned_u64 prod_pair_addr;

	/* user space भव address of SRQ buffer */
	__aligned_u64 srq_addr;

	/* length of SRQ buffer */
	__aligned_u64 srq_len;
पूर्ण;

काष्ठा qedr_create_srq_uresp अणु
	__u16 srq_id;
	__u16 reserved0;
	__u32 reserved1;
पूर्ण;

/* करोorbell recovery entry allocated and populated by userspace करोorbelling
 * entities and mapped to kernel. Kernel uses this to रेजिस्टर करोorbell
 * inक्रमmation with करोorbell drop recovery mechanism.
 */
काष्ठा qedr_user_db_rec अणु
	__aligned_u64 db_data; /* करोorbell data */
पूर्ण;

#पूर्ण_अगर /* __QEDR_USER_H__ */
