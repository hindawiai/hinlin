<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
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

#अगर_अघोषित MTHCA_ABI_USER_H
#घोषणा MTHCA_ABI_USER_H

#समावेश <linux/types.h>

/*
 * Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */
#घोषणा MTHCA_UVERBS_ABI_VERSION	1

/*
 * Make sure that all काष्ठाs defined in this file reमुख्य laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * aव्योम incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular करो not use poपूर्णांकer types -- pass poपूर्णांकers in __u64
 * instead.
 */
काष्ठा mthca_alloc_ucontext_resp अणु
	__u32 qp_tab_size;
	__u32 uarc_size;
पूर्ण;

काष्ठा mthca_alloc_pd_resp अणु
	__u32 pdn;
	__u32 reserved;
पूर्ण;

/*
 * Mark the memory region with a DMA attribute that causes
 * in-flight DMA to be flushed when the region is written to:
 */
#घोषणा MTHCA_MR_DMASYNC	0x1

काष्ठा mthca_reg_mr अणु
	__u32 mr_attrs;
	__u32 reserved;
पूर्ण;

काष्ठा mthca_create_cq अणु
	__u32 lkey;
	__u32 pdn;
	__aligned_u64 arm_db_page;
	__aligned_u64 set_db_page;
	__u32 arm_db_index;
	__u32 set_db_index;
पूर्ण;

काष्ठा mthca_create_cq_resp अणु
	__u32 cqn;
	__u32 reserved;
पूर्ण;

काष्ठा mthca_resize_cq अणु
	__u32 lkey;
	__u32 reserved;
पूर्ण;

काष्ठा mthca_create_srq अणु
	__u32 lkey;
	__u32 db_index;
	__aligned_u64 db_page;
पूर्ण;

काष्ठा mthca_create_srq_resp अणु
	__u32 srqn;
	__u32 reserved;
पूर्ण;

काष्ठा mthca_create_qp अणु
	__u32 lkey;
	__u32 reserved;
	__aligned_u64 sq_db_page;
	__aligned_u64 rq_db_page;
	__u32 sq_db_index;
	__u32 rq_db_index;
पूर्ण;
#पूर्ण_अगर /* MTHCA_ABI_USER_H */
