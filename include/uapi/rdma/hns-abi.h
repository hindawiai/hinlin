<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#अगर_अघोषित HNS_ABI_USER_H
#घोषणा HNS_ABI_USER_H

#समावेश <linux/types.h>

काष्ठा hns_roce_ib_create_cq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u32 cqe_size;
	__u32 reserved;
पूर्ण;

क्रमागत hns_roce_cq_cap_flags अणु
	HNS_ROCE_CQ_FLAG_RECORD_DB = 1 << 0,
पूर्ण;

काष्ठा hns_roce_ib_create_cq_resp अणु
	__aligned_u64 cqn; /* Only 32 bits used, 64 क्रम compat */
	__aligned_u64 cap_flags;
पूर्ण;

काष्ठा hns_roce_ib_create_srq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__aligned_u64 que_addr;
पूर्ण;

काष्ठा hns_roce_ib_create_srq_resp अणु
	__u32	srqn;
	__u32	reserved;
पूर्ण;

काष्ठा hns_roce_ib_create_qp अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u8    log_sq_bb_count;
	__u8    log_sq_stride;
	__u8    sq_no_prefetch;
	__u8    reserved[5];
	__aligned_u64 sdb_addr;
पूर्ण;

क्रमागत hns_roce_qp_cap_flags अणु
	HNS_ROCE_QP_CAP_RQ_RECORD_DB = 1 << 0,
	HNS_ROCE_QP_CAP_SQ_RECORD_DB = 1 << 1,
	HNS_ROCE_QP_CAP_OWNER_DB = 1 << 2,
पूर्ण;

काष्ठा hns_roce_ib_create_qp_resp अणु
	__aligned_u64 cap_flags;
पूर्ण;

काष्ठा hns_roce_ib_alloc_ucontext_resp अणु
	__u32	qp_tab_size;
	__u32	cqe_size;
	__u32	srq_tab_size;
	__u32	reserved;
पूर्ण;

काष्ठा hns_roce_ib_alloc_pd_resp अणु
	__u32 pdn;
पूर्ण;

#पूर्ण_अगर /* HNS_ABI_USER_H */
