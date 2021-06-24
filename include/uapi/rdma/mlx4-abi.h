<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MLX4_ABI_USER_H
#घोषणा MLX4_ABI_USER_H

#समावेश <linux/types.h>

/*
 * Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */

#घोषणा MLX4_IB_UVERBS_NO_DEV_CAPS_ABI_VERSION	3
#घोषणा MLX4_IB_UVERBS_ABI_VERSION		4

/*
 * Make sure that all काष्ठाs defined in this file reमुख्य laid out so
 * that they pack the same way on 32-bit and 64-bit architectures (to
 * aव्योम incompatibility between 32-bit userspace and 64-bit kernels).
 * In particular करो not use poपूर्णांकer types -- pass poपूर्णांकers in __u64
 * instead.
 */

काष्ठा mlx4_ib_alloc_ucontext_resp_v3 अणु
	__u32	qp_tab_size;
	__u16	bf_reg_size;
	__u16	bf_regs_per_page;
पूर्ण;

क्रमागत अणु
	MLX4_USER_DEV_CAP_LARGE_CQE	= 1L << 0,
पूर्ण;

काष्ठा mlx4_ib_alloc_ucontext_resp अणु
	__u32	dev_caps;
	__u32	qp_tab_size;
	__u16	bf_reg_size;
	__u16	bf_regs_per_page;
	__u32	cqe_size;
पूर्ण;

काष्ठा mlx4_ib_alloc_pd_resp अणु
	__u32	pdn;
	__u32	reserved;
पूर्ण;

काष्ठा mlx4_ib_create_cq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
पूर्ण;

काष्ठा mlx4_ib_create_cq_resp अणु
	__u32	cqn;
	__u32	reserved;
पूर्ण;

काष्ठा mlx4_ib_resize_cq अणु
	__aligned_u64 buf_addr;
पूर्ण;

काष्ठा mlx4_ib_create_srq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
पूर्ण;

काष्ठा mlx4_ib_create_srq_resp अणु
	__u32	srqn;
	__u32	reserved;
पूर्ण;

काष्ठा mlx4_ib_create_qp_rss अणु
	__aligned_u64 rx_hash_fields_mask; /* Use  क्रमागत mlx4_ib_rx_hash_fields */
	__u8    rx_hash_function; /* Use क्रमागत mlx4_ib_rx_hash_function_flags */
	__u8    reserved[7];
	__u8    rx_hash_key[40];
	__u32   comp_mask;
	__u32   reserved1;
पूर्ण;

काष्ठा mlx4_ib_create_qp अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u8	log_sq_bb_count;
	__u8	log_sq_stride;
	__u8	sq_no_prefetch;
	__u8	reserved;
	__u32	inl_recv_sz;
पूर्ण;

काष्ठा mlx4_ib_create_wq अणु
	__aligned_u64 buf_addr;
	__aligned_u64 db_addr;
	__u8	log_range_size;
	__u8	reserved[3];
	__u32   comp_mask;
पूर्ण;

काष्ठा mlx4_ib_modअगरy_wq अणु
	__u32	comp_mask;
	__u32	reserved;
पूर्ण;

काष्ठा mlx4_ib_create_rwq_ind_tbl_resp अणु
	__u32	response_length;
	__u32	reserved;
पूर्ण;

/* RX Hash function flags */
क्रमागत mlx4_ib_rx_hash_function_flags अणु
	MLX4_IB_RX_HASH_FUNC_TOEPLITZ	= 1 << 0,
पूर्ण;

/*
 * RX Hash flags, these flags allows to set which incoming packet's field should
 * participates in RX Hash. Each flag represent certain packet's field,
 * when the flag is set the field that is represented by the flag will
 * participate in RX Hash calculation.
 */
क्रमागत mlx4_ib_rx_hash_fields अणु
	MLX4_IB_RX_HASH_SRC_IPV4	= 1 << 0,
	MLX4_IB_RX_HASH_DST_IPV4	= 1 << 1,
	MLX4_IB_RX_HASH_SRC_IPV6	= 1 << 2,
	MLX4_IB_RX_HASH_DST_IPV6	= 1 << 3,
	MLX4_IB_RX_HASH_SRC_PORT_TCP	= 1 << 4,
	MLX4_IB_RX_HASH_DST_PORT_TCP	= 1 << 5,
	MLX4_IB_RX_HASH_SRC_PORT_UDP	= 1 << 6,
	MLX4_IB_RX_HASH_DST_PORT_UDP	= 1 << 7,
	MLX4_IB_RX_HASH_INNER		= 1ULL << 31,
पूर्ण;

काष्ठा mlx4_ib_rss_caps अणु
	__aligned_u64 rx_hash_fields_mask; /* क्रमागत mlx4_ib_rx_hash_fields */
	__u8 rx_hash_function; /* क्रमागत mlx4_ib_rx_hash_function_flags */
	__u8 reserved[7];
पूर्ण;

क्रमागत query_device_resp_mask अणु
	MLX4_IB_QUERY_DEV_RESP_MASK_CORE_CLOCK_OFFSET = 1UL << 0,
पूर्ण;

काष्ठा mlx4_ib_tso_caps अणु
	__u32 max_tso; /* Maximum tso payload size in bytes */
	/* Corresponding bit will be set अगर qp type from
	 * 'enum ib_qp_type' is supported.
	 */
	__u32 supported_qpts;
पूर्ण;

काष्ठा mlx4_uverbs_ex_query_device_resp अणु
	__u32			comp_mask;
	__u32			response_length;
	__aligned_u64		hca_core_घड़ी_offset;
	__u32			max_inl_recv_sz;
	__u32			reserved;
	काष्ठा mlx4_ib_rss_caps	rss_caps;
	काष्ठा mlx4_ib_tso_caps tso_caps;
पूर्ण;

#पूर्ण_अगर /* MLX4_ABI_USER_H */
