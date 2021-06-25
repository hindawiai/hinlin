<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
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
#अगर_अघोषित CXGB4_ABI_USER_H
#घोषणा CXGB4_ABI_USER_H

#समावेश <linux/types.h>

#घोषणा C4IW_UVERBS_ABI_VERSION	3

/*
 * Make sure that all काष्ठाs defined in this file reमुख्य laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * aव्योम incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular करो not use poपूर्णांकer types -- pass poपूर्णांकers in __aligned_u64
 * instead.
 */

क्रमागत अणु
	C4IW_64B_CQE = (1 << 0)
पूर्ण;

काष्ठा c4iw_create_cq अणु
	__u32 flags;
	__u32 reserved;
पूर्ण;

काष्ठा c4iw_create_cq_resp अणु
	__aligned_u64 key;
	__aligned_u64 gts_key;
	__aligned_u64 memsize;
	__u32 cqid;
	__u32 size;
	__u32 qid_mask;
	__u32 flags;
पूर्ण;

क्रमागत अणु
	C4IW_QPF_ONCHIP	= (1 << 0),
	C4IW_QPF_WRITE_W_IMM = (1 << 1)
पूर्ण;

काष्ठा c4iw_create_qp_resp अणु
	__aligned_u64 ma_sync_key;
	__aligned_u64 sq_key;
	__aligned_u64 rq_key;
	__aligned_u64 sq_db_gts_key;
	__aligned_u64 rq_db_gts_key;
	__aligned_u64 sq_memsize;
	__aligned_u64 rq_memsize;
	__u32 sqid;
	__u32 rqid;
	__u32 sq_size;
	__u32 rq_size;
	__u32 qid_mask;
	__u32 flags;
पूर्ण;

काष्ठा c4iw_create_srq_resp अणु
	__aligned_u64 srq_key;
	__aligned_u64 srq_db_gts_key;
	__aligned_u64 srq_memsize;
	__u32 srqid;
	__u32 srq_size;
	__u32 rqt_असल_idx;
	__u32 qid_mask;
	__u32 flags;
	__u32 reserved; /* explicit padding */
पूर्ण;

क्रमागत अणु
	/* HW supports SRQ_LIMIT_REACHED event */
	T4_SRQ_LIMIT_SUPPORT = 1 << 0,
पूर्ण;

काष्ठा c4iw_alloc_ucontext_resp अणु
	__aligned_u64 status_page_key;
	__u32 status_page_size;
	__u32 reserved; /* explicit padding (optional क्रम i386) */
पूर्ण;

काष्ठा c4iw_alloc_pd_resp अणु
	__u32 pdid;
पूर्ण;

#पूर्ण_अगर /* CXGB4_ABI_USER_H */
