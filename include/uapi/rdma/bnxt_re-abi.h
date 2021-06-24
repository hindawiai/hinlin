<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-2-Clause) */
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Uverbs ABI header file
 */

#अगर_अघोषित __BNXT_RE_UVERBS_ABI_H__
#घोषणा __BNXT_RE_UVERBS_ABI_H__

#समावेश <linux/types.h>

#घोषणा BNXT_RE_ABI_VERSION	1

#घोषणा BNXT_RE_CHIP_ID0_CHIP_NUM_SFT		0x00
#घोषणा BNXT_RE_CHIP_ID0_CHIP_REV_SFT		0x10
#घोषणा BNXT_RE_CHIP_ID0_CHIP_MET_SFT		0x18

क्रमागत अणु
	BNXT_RE_UCNTX_CMASK_HAVE_CCTX = 0x1ULL
पूर्ण;

काष्ठा bnxt_re_uctx_resp अणु
	__u32 dev_id;
	__u32 max_qp;
	__u32 pg_size;
	__u32 cqe_sz;
	__u32 max_cqd;
	__u32 rsvd;
	__aligned_u64 comp_mask;
	__u32 chip_id0;
	__u32 chip_id1;
पूर्ण;

/*
 * This काष्ठा is placed after the ib_uverbs_alloc_pd_resp काष्ठा, which is
 * not 8 byted aligned. To aव्योम undesired padding in various हालs we have to
 * set this काष्ठा to packed.
 */
काष्ठा bnxt_re_pd_resp अणु
	__u32 pdid;
	__u32 dpi;
	__u64 dbr;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा bnxt_re_cq_req अणु
	__aligned_u64 cq_va;
	__aligned_u64 cq_handle;
पूर्ण;

काष्ठा bnxt_re_cq_resp अणु
	__u32 cqid;
	__u32 tail;
	__u32 phase;
	__u32 rsvd;
पूर्ण;

काष्ठा bnxt_re_qp_req अणु
	__aligned_u64 qpsva;
	__aligned_u64 qprva;
	__aligned_u64 qp_handle;
पूर्ण;

काष्ठा bnxt_re_qp_resp अणु
	__u32 qpid;
	__u32 rsvd;
पूर्ण;

काष्ठा bnxt_re_srq_req अणु
	__aligned_u64 srqva;
	__aligned_u64 srq_handle;
पूर्ण;

काष्ठा bnxt_re_srq_resp अणु
	__u32 srqid;
पूर्ण;

क्रमागत bnxt_re_shpg_offt अणु
	BNXT_RE_BEG_RESV_OFFT	= 0x00,
	BNXT_RE_AVID_OFFT	= 0x10,
	BNXT_RE_AVID_SIZE	= 0x04,
	BNXT_RE_END_RESV_OFFT	= 0xFF0
पूर्ण;

#पूर्ण_अगर /* __BNXT_RE_UVERBS_ABI_H__*/
