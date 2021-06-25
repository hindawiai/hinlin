<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
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
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
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

#अगर_अघोषित RDMA_USER_RXE_H
#घोषणा RDMA_USER_RXE_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

क्रमागत अणु
	RXE_NETWORK_TYPE_IPV4 = 1,
	RXE_NETWORK_TYPE_IPV6 = 2,
पूर्ण;

जोड़ rxe_gid अणु
	__u8	raw[16];
	काष्ठा अणु
		__be64	subnet_prefix;
		__be64	पूर्णांकerface_id;
	पूर्ण global;
पूर्ण;

काष्ठा rxe_global_route अणु
	जोड़ rxe_gid	dgid;
	__u32		flow_label;
	__u8		sgid_index;
	__u8		hop_limit;
	__u8		traffic_class;
पूर्ण;

काष्ठा rxe_av अणु
	__u8			port_num;
	/* From RXE_NETWORK_TYPE_* */
	__u8			network_type;
	__u8			dmac[6];
	काष्ठा rxe_global_route	grh;
	जोड़ अणु
		काष्ठा sockaddr_in	_sockaddr_in;
		काष्ठा sockaddr_in6	_sockaddr_in6;
	पूर्ण sgid_addr, dgid_addr;
पूर्ण;

काष्ठा rxe_send_wr अणु
	__aligned_u64		wr_id;
	__u32			num_sge;
	__u32			opcode;
	__u32			send_flags;
	जोड़ अणु
		__be32		imm_data;
		__u32		invalidate_rkey;
	पूर्ण ex;
	जोड़ अणु
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__u32	rkey;
			__u32	reserved;
		पूर्ण rdma;
		काष्ठा अणु
			__aligned_u64 remote_addr;
			__aligned_u64 compare_add;
			__aligned_u64 swap;
			__u32	rkey;
			__u32	reserved;
		पूर्ण atomic;
		काष्ठा अणु
			__u32	remote_qpn;
			__u32	remote_qkey;
			__u16	pkey_index;
		पूर्ण ud;
		/* reg is only used by the kernel and is not part of the uapi */
		काष्ठा अणु
			जोड़ अणु
				काष्ठा ib_mr *mr;
				__aligned_u64 reserved;
			पूर्ण;
			__u32	     key;
			__u32	     access;
		पूर्ण reg;
	पूर्ण wr;
पूर्ण;

काष्ठा rxe_sge अणु
	__aligned_u64 addr;
	__u32	length;
	__u32	lkey;
पूर्ण;

काष्ठा mminfo अणु
	__aligned_u64		offset;
	__u32			size;
	__u32			pad;
पूर्ण;

काष्ठा rxe_dma_info अणु
	__u32			length;
	__u32			resid;
	__u32			cur_sge;
	__u32			num_sge;
	__u32			sge_offset;
	__u32			reserved;
	जोड़ अणु
		__u8		अंतरभूत_data[0];
		काष्ठा rxe_sge	sge[0];
	पूर्ण;
पूर्ण;

काष्ठा rxe_send_wqe अणु
	काष्ठा rxe_send_wr	wr;
	काष्ठा rxe_av		av;
	__u32			status;
	__u32			state;
	__aligned_u64		iova;
	__u32			mask;
	__u32			first_psn;
	__u32			last_psn;
	__u32			ack_length;
	__u32			ssn;
	__u32			has_rd_atomic;
	काष्ठा rxe_dma_info	dma;
पूर्ण;

काष्ठा rxe_recv_wqe अणु
	__aligned_u64		wr_id;
	__u32			num_sge;
	__u32			padding;
	काष्ठा rxe_dma_info	dma;
पूर्ण;

काष्ठा rxe_create_cq_resp अणु
	काष्ठा mminfo mi;
पूर्ण;

काष्ठा rxe_resize_cq_resp अणु
	काष्ठा mminfo mi;
पूर्ण;

काष्ठा rxe_create_qp_resp अणु
	काष्ठा mminfo rq_mi;
	काष्ठा mminfo sq_mi;
पूर्ण;

काष्ठा rxe_create_srq_resp अणु
	काष्ठा mminfo mi;
	__u32 srq_num;
	__u32 reserved;
पूर्ण;

काष्ठा rxe_modअगरy_srq_cmd अणु
	__aligned_u64 mmap_info_addr;
पूर्ण;

/* This data काष्ठाure is stored at the base of work and
 * completion queues shared between user space and kernel space.
 * It contains the producer and consumer indices. Is also
 * contains a copy of the queue size parameters क्रम user space
 * to use but the kernel must use the parameters in the
 * rxe_queue काष्ठा. For perक्रमmance reasons arrange to have
 * producer and consumer indices in separate cache lines
 * the kernel should always mask the indices to aव्योम accessing
 * memory outside of the data area
 */
काष्ठा rxe_queue_buf अणु
	__u32			log2_elem_size;
	__u32			index_mask;
	__u32			pad_1[30];
	__u32			producer_index;
	__u32			pad_2[31];
	__u32			consumer_index;
	__u32			pad_3[31];
	__u8			data[];
पूर्ण;

#पूर्ण_अगर /* RDMA_USER_RXE_H */
