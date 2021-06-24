<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-2-Clause) */
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __VMW_PVRDMA_ABI_H__
#घोषणा __VMW_PVRDMA_ABI_H__

#समावेश <linux/types.h>

#घोषणा PVRDMA_UVERBS_ABI_VERSION	3		/* ABI Version. */
#घोषणा PVRDMA_UAR_HANDLE_MASK		0x00FFFFFF	/* Bottom 24 bits. */
#घोषणा PVRDMA_UAR_QP_OFFSET		0		/* QP करोorbell. */
#घोषणा PVRDMA_UAR_QP_SEND		(1 << 30)	/* Send bit. */
#घोषणा PVRDMA_UAR_QP_RECV		(1 << 31)	/* Recv bit. */
#घोषणा PVRDMA_UAR_CQ_OFFSET		4		/* CQ करोorbell. */
#घोषणा PVRDMA_UAR_CQ_ARM_SOL		(1 << 29)	/* Arm solicited bit. */
#घोषणा PVRDMA_UAR_CQ_ARM		(1 << 30)	/* Arm bit. */
#घोषणा PVRDMA_UAR_CQ_POLL		(1 << 31)	/* Poll bit. */
#घोषणा PVRDMA_UAR_SRQ_OFFSET		8		/* SRQ करोorbell. */
#घोषणा PVRDMA_UAR_SRQ_RECV		(1 << 30)	/* Recv bit. */

क्रमागत pvrdma_wr_opcode अणु
	PVRDMA_WR_RDMA_WRITE,
	PVRDMA_WR_RDMA_WRITE_WITH_IMM,
	PVRDMA_WR_SEND,
	PVRDMA_WR_SEND_WITH_IMM,
	PVRDMA_WR_RDMA_READ,
	PVRDMA_WR_ATOMIC_CMP_AND_SWP,
	PVRDMA_WR_ATOMIC_FETCH_AND_ADD,
	PVRDMA_WR_LSO,
	PVRDMA_WR_SEND_WITH_INV,
	PVRDMA_WR_RDMA_READ_WITH_INV,
	PVRDMA_WR_LOCAL_INV,
	PVRDMA_WR_FAST_REG_MR,
	PVRDMA_WR_MASKED_ATOMIC_CMP_AND_SWP,
	PVRDMA_WR_MASKED_ATOMIC_FETCH_AND_ADD,
	PVRDMA_WR_BIND_MW,
	PVRDMA_WR_REG_SIG_MR,
	PVRDMA_WR_ERROR,
पूर्ण;

क्रमागत pvrdma_wc_status अणु
	PVRDMA_WC_SUCCESS,
	PVRDMA_WC_LOC_LEN_ERR,
	PVRDMA_WC_LOC_QP_OP_ERR,
	PVRDMA_WC_LOC_EEC_OP_ERR,
	PVRDMA_WC_LOC_PROT_ERR,
	PVRDMA_WC_WR_FLUSH_ERR,
	PVRDMA_WC_MW_BIND_ERR,
	PVRDMA_WC_BAD_RESP_ERR,
	PVRDMA_WC_LOC_ACCESS_ERR,
	PVRDMA_WC_REM_INV_REQ_ERR,
	PVRDMA_WC_REM_ACCESS_ERR,
	PVRDMA_WC_REM_OP_ERR,
	PVRDMA_WC_RETRY_EXC_ERR,
	PVRDMA_WC_RNR_RETRY_EXC_ERR,
	PVRDMA_WC_LOC_RDD_VIOL_ERR,
	PVRDMA_WC_REM_INV_RD_REQ_ERR,
	PVRDMA_WC_REM_ABORT_ERR,
	PVRDMA_WC_INV_EECN_ERR,
	PVRDMA_WC_INV_EEC_STATE_ERR,
	PVRDMA_WC_FATAL_ERR,
	PVRDMA_WC_RESP_TIMEOUT_ERR,
	PVRDMA_WC_GENERAL_ERR,
पूर्ण;

क्रमागत pvrdma_wc_opcode अणु
	PVRDMA_WC_SEND,
	PVRDMA_WC_RDMA_WRITE,
	PVRDMA_WC_RDMA_READ,
	PVRDMA_WC_COMP_SWAP,
	PVRDMA_WC_FETCH_ADD,
	PVRDMA_WC_BIND_MW,
	PVRDMA_WC_LSO,
	PVRDMA_WC_LOCAL_INV,
	PVRDMA_WC_FAST_REG_MR,
	PVRDMA_WC_MASKED_COMP_SWAP,
	PVRDMA_WC_MASKED_FETCH_ADD,
	PVRDMA_WC_RECV = 1 << 7,
	PVRDMA_WC_RECV_RDMA_WITH_IMM,
पूर्ण;

क्रमागत pvrdma_wc_flags अणु
	PVRDMA_WC_GRH			= 1 << 0,
	PVRDMA_WC_WITH_IMM		= 1 << 1,
	PVRDMA_WC_WITH_INVALIDATE	= 1 << 2,
	PVRDMA_WC_IP_CSUM_OK		= 1 << 3,
	PVRDMA_WC_WITH_SMAC		= 1 << 4,
	PVRDMA_WC_WITH_VLAN		= 1 << 5,
	PVRDMA_WC_WITH_NETWORK_HDR_TYPE	= 1 << 6,
	PVRDMA_WC_FLAGS_MAX		= PVRDMA_WC_WITH_NETWORK_HDR_TYPE,
पूर्ण;

क्रमागत pvrdma_network_type अणु
	PVRDMA_NETWORK_IB,
	PVRDMA_NETWORK_ROCE_V1 = PVRDMA_NETWORK_IB,
	PVRDMA_NETWORK_IPV4,
	PVRDMA_NETWORK_IPV6
पूर्ण;

काष्ठा pvrdma_alloc_ucontext_resp अणु
	__u32 qp_tab_size;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_alloc_pd_resp अणु
	__u32 pdn;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_create_cq अणु
	__aligned_u64 buf_addr;
	__u32 buf_size;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_create_cq_resp अणु
	__u32 cqn;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_resize_cq अणु
	__aligned_u64 buf_addr;
	__u32 buf_size;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_create_srq अणु
	__aligned_u64 buf_addr;
	__u32 buf_size;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_create_srq_resp अणु
	__u32 srqn;
	__u32 reserved;
पूर्ण;

काष्ठा pvrdma_create_qp अणु
	__aligned_u64 rbuf_addr;
	__aligned_u64 sbuf_addr;
	__u32 rbuf_size;
	__u32 sbuf_size;
	__aligned_u64 qp_addr;
पूर्ण;

काष्ठा pvrdma_create_qp_resp अणु
	__u32 qpn;
	__u32 qp_handle;
पूर्ण;

/* PVRDMA masked atomic compare and swap */
काष्ठा pvrdma_ex_cmp_swap अणु
	__aligned_u64 swap_val;
	__aligned_u64 compare_val;
	__aligned_u64 swap_mask;
	__aligned_u64 compare_mask;
पूर्ण;

/* PVRDMA masked atomic fetch and add */
काष्ठा pvrdma_ex_fetch_add अणु
	__aligned_u64 add_val;
	__aligned_u64 field_boundary;
पूर्ण;

/* PVRDMA address vector. */
काष्ठा pvrdma_av अणु
	__u32 port_pd;
	__u32 sl_tclass_flowlabel;
	__u8 dgid[16];
	__u8 src_path_bits;
	__u8 gid_index;
	__u8 stat_rate;
	__u8 hop_limit;
	__u8 dmac[6];
	__u8 reserved[6];
पूर्ण;

/* PVRDMA scatter/gather entry */
काष्ठा pvrdma_sge अणु
	__aligned_u64 addr;
	__u32   length;
	__u32   lkey;
पूर्ण;

/* PVRDMA receive queue work request */
काष्ठा pvrdma_rq_wqe_hdr अणु
	__aligned_u64 wr_id;		/* wr id */
	__u32 num_sge;		/* size of s/g array */
	__u32 total_len;	/* reserved */
पूर्ण;
/* Use pvrdma_sge (ib_sge) क्रम receive queue s/g array elements. */

/* PVRDMA send queue work request */
काष्ठा pvrdma_sq_wqe_hdr अणु
	__aligned_u64 wr_id;		/* wr id */
	__u32 num_sge;		/* size of s/g array */
	__u32 total_len;	/* reserved */
	__u32 opcode;		/* operation type */
	__u32 send_flags;	/* wr flags */
	जोड़ अणु
		__be32 imm_data;
		__u32 invalidate_rkey;
	पूर्ण ex;
	__u32 reserved;
	जोड़ अणु
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__u32 rkey;
			__u8 reserved[4];
		पूर्ण rdma;
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__aligned_u64 compare_add;
			__aligned_u64 swap;
			__u32 rkey;
			__u32 reserved;
		पूर्ण atomic;
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__u32 log_arg_sz;
			__u32 rkey;
			जोड़ अणु
				काष्ठा pvrdma_ex_cmp_swap  cmp_swap;
				काष्ठा pvrdma_ex_fetch_add fetch_add;
			पूर्ण wr_data;
		पूर्ण masked_atomics;
		काष्ठा अणु
			__aligned_u64 ioबहु_शुरू;
			__aligned_u64 pl_pdir_dma;
			__u32 page_shअगरt;
			__u32 page_list_len;
			__u32 length;
			__u32 access_flags;
			__u32 rkey;
			__u32 reserved;
		पूर्ण fast_reg;
		काष्ठा अणु
			__u32 remote_qpn;
			__u32 remote_qkey;
			काष्ठा pvrdma_av av;
		पूर्ण ud;
	पूर्ण wr;
पूर्ण;
/* Use pvrdma_sge (ib_sge) क्रम send queue s/g array elements. */

/* Completion queue element. */
काष्ठा pvrdma_cqe अणु
	__aligned_u64 wr_id;
	__aligned_u64 qp;
	__u32 opcode;
	__u32 status;
	__u32 byte_len;
	__be32 imm_data;
	__u32 src_qp;
	__u32 wc_flags;
	__u32 venकरोr_err;
	__u16 pkey_index;
	__u16 slid;
	__u8 sl;
	__u8 dlid_path_bits;
	__u8 port_num;
	__u8 smac[6];
	__u8 network_hdr_type;
	__u8 reserved2[6]; /* Pad to next घातer of 2 (64). */
पूर्ण;

#पूर्ण_अगर /* __VMW_PVRDMA_ABI_H__ */
