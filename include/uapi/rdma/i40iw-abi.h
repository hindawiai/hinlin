<शैली गुरु>
/*
 * Copyright (c) 2006 - 2016 Intel Corporation.  All rights reserved.
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Open Grid Computing, Inc. All rights reserved.
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
 *
 */

#अगर_अघोषित I40IW_ABI_H
#घोषणा I40IW_ABI_H

#समावेश <linux/types.h>

#घोषणा I40IW_ABI_VER 5

काष्ठा i40iw_alloc_ucontext_req अणु
	__u32 reserved32;
	__u8 userspace_ver;
	__u8 reserved8[3];
पूर्ण;

काष्ठा i40iw_alloc_ucontext_resp अणु
	__u32 max_pds;		/* maximum pds allowed क्रम this user process */
	__u32 max_qps;		/* maximum qps allowed क्रम this user process */
	__u32 wq_size;		/* size of the WQs (sq+rq) allocated to the mmaped area */
	__u8 kernel_ver;
	__u8 reserved[3];
पूर्ण;

काष्ठा i40iw_alloc_pd_resp अणु
	__u32 pd_id;
	__u8 reserved[4];
पूर्ण;

काष्ठा i40iw_create_cq_req अणु
	__aligned_u64 user_cq_buffer;
	__aligned_u64 user_shaकरोw_area;
पूर्ण;

काष्ठा i40iw_create_qp_req अणु
	__aligned_u64 user_wqe_buffers;
	__aligned_u64 user_compl_ctx;

	/* UDA QP PHB */
	__aligned_u64 user_sq_phb;	/* place क्रम VA of the sq phb buff */
	__aligned_u64 user_rq_phb;	/* place क्रम VA of the rq phb buff */
पूर्ण;

क्रमागत i40iw_memreg_type अणु
	IW_MEMREG_TYPE_MEM = 0x0000,
	IW_MEMREG_TYPE_QP = 0x0001,
	IW_MEMREG_TYPE_CQ = 0x0002,
पूर्ण;

काष्ठा i40iw_mem_reg_req अणु
	__u16 reg_type;		/* Memory, QP or CQ */
	__u16 cq_pages;
	__u16 rq_pages;
	__u16 sq_pages;
पूर्ण;

काष्ठा i40iw_create_cq_resp अणु
	__u32 cq_id;
	__u32 cq_size;
	__u32 mmap_db_index;
	__u32 reserved;
पूर्ण;

काष्ठा i40iw_create_qp_resp अणु
	__u32 qp_id;
	__u32 actual_sq_size;
	__u32 actual_rq_size;
	__u32 i40iw_drv_opt;
	__u16 push_idx;
	__u8  lsmm;
	__u8  rsvd2;
पूर्ण;

#पूर्ण_अगर
