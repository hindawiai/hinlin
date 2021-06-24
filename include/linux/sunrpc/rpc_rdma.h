<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2015-2017 Oracle. All rights reserved.
 * Copyright (c) 2003-2007 Network Appliance, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the BSD-type
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *      Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      Redistributions in binary क्रमm must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the करोcumentation and/or other materials provided
 *      with the distribution.
 *
 *      Neither the name of the Network Appliance, Inc. nor the names of
 *      its contributors may be used to enकरोrse or promote products
 *      derived from this software without specअगरic prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _LINUX_SUNRPC_RPC_RDMA_H
#घोषणा _LINUX_SUNRPC_RPC_RDMA_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#घोषणा RPCRDMA_VERSION		1
#घोषणा rpcrdma_version		cpu_to_be32(RPCRDMA_VERSION)

क्रमागत अणु
	RPCRDMA_V1_DEF_INLINE_SIZE	= 1024,
पूर्ण;

/*
 * XDR sizes, in quads
 */
क्रमागत अणु
	rpcrdma_fixed_maxsz	= 4,
	rpcrdma_segment_maxsz	= 4,
	rpcrdma_पढ़ोseg_maxsz	= 1 + rpcrdma_segment_maxsz,
	rpcrdma_पढ़ोchunk_maxsz	= 1 + rpcrdma_पढ़ोseg_maxsz,
पूर्ण;

/*
 * Smallest RPC/RDMA header: rm_xid through rm_type, then rm_nochunks
 */
#घोषणा RPCRDMA_HDRLEN_MIN	(माप(__be32) * 7)
#घोषणा RPCRDMA_HDRLEN_ERR	(माप(__be32) * 5)

क्रमागत rpcrdma_errcode अणु
	ERR_VERS = 1,
	ERR_CHUNK = 2
पूर्ण;

क्रमागत rpcrdma_proc अणु
	RDMA_MSG = 0,		/* An RPC call or reply msg */
	RDMA_NOMSG = 1,		/* An RPC call or reply msg - separate body */
	RDMA_MSGP = 2,		/* An RPC call or reply msg with padding */
	RDMA_DONE = 3,		/* Client संकेतs reply completion */
	RDMA_ERROR = 4		/* An RPC RDMA encoding error */
पूर्ण;

#घोषणा rdma_msg	cpu_to_be32(RDMA_MSG)
#घोषणा rdma_nomsg	cpu_to_be32(RDMA_NOMSG)
#घोषणा rdma_msgp	cpu_to_be32(RDMA_MSGP)
#घोषणा rdma_करोne	cpu_to_be32(RDMA_DONE)
#घोषणा rdma_error	cpu_to_be32(RDMA_ERROR)

#घोषणा err_vers	cpu_to_be32(ERR_VERS)
#घोषणा err_chunk	cpu_to_be32(ERR_CHUNK)

/*
 * Private extension to RPC-over-RDMA Version One.
 * Message passed during RDMA-CM connection set-up.
 *
 * Add new fields at the end, and करोn't permute existing
 * fields.
 */
काष्ठा rpcrdma_connect_निजी अणु
	__be32			cp_magic;
	u8			cp_version;
	u8			cp_flags;
	u8			cp_send_size;
	u8			cp_recv_size;
पूर्ण __packed;

#घोषणा rpcrdma_cmp_magic	__cpu_to_be32(0xf6ab0e18)

क्रमागत अणु
	RPCRDMA_CMP_VERSION		= 1,
	RPCRDMA_CMP_F_SND_W_INV_OK	= BIT(0),
पूर्ण;

अटल अंतरभूत u8
rpcrdma_encode_buffer_size(अचिन्हित पूर्णांक size)
अणु
	वापस (size >> 10) - 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
rpcrdma_decode_buffer_size(u8 val)
अणु
	वापस ((अचिन्हित पूर्णांक)val + 1) << 10;
पूर्ण

/**
 * xdr_encode_rdma_segment - Encode contents of an RDMA segment
 * @p: Poपूर्णांकer पूर्णांकo a send buffer
 * @handle: The RDMA handle to encode
 * @length: The RDMA length to encode
 * @offset: The RDMA offset to encode
 *
 * Return value:
 *   Poपूर्णांकer to the XDR position that follows the encoded RDMA segment
 */
अटल अंतरभूत __be32 *xdr_encode_rdma_segment(__be32 *p, u32 handle,
					      u32 length, u64 offset)
अणु
	*p++ = cpu_to_be32(handle);
	*p++ = cpu_to_be32(length);
	वापस xdr_encode_hyper(p, offset);
पूर्ण

/**
 * xdr_encode_पढ़ो_segment - Encode contents of a Read segment
 * @p: Poपूर्णांकer पूर्णांकo a send buffer
 * @position: The position to encode
 * @handle: The RDMA handle to encode
 * @length: The RDMA length to encode
 * @offset: The RDMA offset to encode
 *
 * Return value:
 *   Poपूर्णांकer to the XDR position that follows the encoded Read segment
 */
अटल अंतरभूत __be32 *xdr_encode_पढ़ो_segment(__be32 *p, u32 position,
					      u32 handle, u32 length,
					      u64 offset)
अणु
	*p++ = cpu_to_be32(position);
	वापस xdr_encode_rdma_segment(p, handle, length, offset);
पूर्ण

/**
 * xdr_decode_rdma_segment - Decode contents of an RDMA segment
 * @p: Poपूर्णांकer to the undecoded RDMA segment
 * @handle: Upon वापस, the RDMA handle
 * @length: Upon वापस, the RDMA length
 * @offset: Upon वापस, the RDMA offset
 *
 * Return value:
 *   Poपूर्णांकer to the XDR item that follows the RDMA segment
 */
अटल अंतरभूत __be32 *xdr_decode_rdma_segment(__be32 *p, u32 *handle,
					      u32 *length, u64 *offset)
अणु
	*handle = be32_to_cpup(p++);
	*length = be32_to_cpup(p++);
	वापस xdr_decode_hyper(p, offset);
पूर्ण

/**
 * xdr_decode_पढ़ो_segment - Decode contents of a Read segment
 * @p: Poपूर्णांकer to the undecoded Read segment
 * @position: Upon वापस, the segment's position
 * @handle: Upon वापस, the RDMA handle
 * @length: Upon वापस, the RDMA length
 * @offset: Upon वापस, the RDMA offset
 *
 * Return value:
 *   Poपूर्णांकer to the XDR item that follows the Read segment
 */
अटल अंतरभूत __be32 *xdr_decode_पढ़ो_segment(__be32 *p, u32 *position,
					      u32 *handle, u32 *length,
					      u64 *offset)
अणु
	*position = be32_to_cpup(p++);
	वापस xdr_decode_rdma_segment(p, handle, length, offset);
पूर्ण

#पूर्ण_अगर				/* _LINUX_SUNRPC_RPC_RDMA_H */
