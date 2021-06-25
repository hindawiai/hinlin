<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <rdma/ib_pack.h>
#समावेश "rxe_opcode.h"
#समावेश "rxe_hdr.h"

/* useful inक्रमmation about work request opcodes and pkt opcodes in
 * table क्रमm
 */
काष्ठा rxe_wr_opcode_info rxe_wr_opcode_info[] = अणु
	[IB_WR_RDMA_WRITE]				= अणु
		.name	= "IB_WR_RDMA_WRITE",
		.mask	= अणु
			[IB_QPT_RC]	= WR_INLINE_MASK | WR_WRITE_MASK,
			[IB_QPT_UC]	= WR_INLINE_MASK | WR_WRITE_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_RDMA_WRITE_WITH_IMM]			= अणु
		.name	= "IB_WR_RDMA_WRITE_WITH_IMM",
		.mask	= अणु
			[IB_QPT_RC]	= WR_INLINE_MASK | WR_WRITE_MASK,
			[IB_QPT_UC]	= WR_INLINE_MASK | WR_WRITE_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_SEND]					= अणु
		.name	= "IB_WR_SEND",
		.mask	= अणु
			[IB_QPT_SMI]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_GSI]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_RC]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_UC]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_UD]	= WR_INLINE_MASK | WR_SEND_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_SEND_WITH_IMM]				= अणु
		.name	= "IB_WR_SEND_WITH_IMM",
		.mask	= अणु
			[IB_QPT_SMI]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_GSI]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_RC]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_UC]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_UD]	= WR_INLINE_MASK | WR_SEND_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_RDMA_READ]				= अणु
		.name	= "IB_WR_RDMA_READ",
		.mask	= अणु
			[IB_QPT_RC]	= WR_READ_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_ATOMIC_CMP_AND_SWP]			= अणु
		.name	= "IB_WR_ATOMIC_CMP_AND_SWP",
		.mask	= अणु
			[IB_QPT_RC]	= WR_ATOMIC_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_ATOMIC_FETCH_AND_ADD]			= अणु
		.name	= "IB_WR_ATOMIC_FETCH_AND_ADD",
		.mask	= अणु
			[IB_QPT_RC]	= WR_ATOMIC_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_LSO]					= अणु
		.name	= "IB_WR_LSO",
		.mask	= अणु
			/* not supported */
		पूर्ण,
	पूर्ण,
	[IB_WR_SEND_WITH_INV]				= अणु
		.name	= "IB_WR_SEND_WITH_INV",
		.mask	= अणु
			[IB_QPT_RC]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_UC]	= WR_INLINE_MASK | WR_SEND_MASK,
			[IB_QPT_UD]	= WR_INLINE_MASK | WR_SEND_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_RDMA_READ_WITH_INV]			= अणु
		.name	= "IB_WR_RDMA_READ_WITH_INV",
		.mask	= अणु
			[IB_QPT_RC]	= WR_READ_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_LOCAL_INV]				= अणु
		.name	= "IB_WR_LOCAL_INV",
		.mask	= अणु
			[IB_QPT_RC]	= WR_REG_MASK,
		पूर्ण,
	पूर्ण,
	[IB_WR_REG_MR]					= अणु
		.name	= "IB_WR_REG_MR",
		.mask	= अणु
			[IB_QPT_RC]	= WR_REG_MASK,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा rxe_opcode_info rxe_opcode[RXE_NUM_OPCODE] = अणु
	[IB_OPCODE_RC_SEND_FIRST]			= अणु
		.name	= "IB_OPCODE_RC_SEND_FIRST",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_RWR_MASK
				| RXE_SEND_MASK | RXE_START_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_MIDDLE]		= अणु
		.name	= "IB_OPCODE_RC_SEND_MIDDLE]",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_SEND_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_LAST]			= अणु
		.name	= "IB_OPCODE_RC_SEND_LAST",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_COMP_MASK
				| RXE_SEND_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE",
		.mask	= RXE_IMMDT_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_SEND_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IMMDT]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_ONLY]			= अणु
		.name	= "IB_OPCODE_RC_SEND_ONLY",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_COMP_MASK
				| RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RC_SEND_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_IMMDT_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IMMDT]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_WRITE_FIRST]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_WRITE_FIRST",
		.mask	= RXE_RETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_WRITE_MIDDLE]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_WRITE_MIDDLE",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_WRITE_LAST]			= अणु
		.name	= "IB_OPCODE_RC_RDMA_WRITE_LAST",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE",
		.mask	= RXE_IMMDT_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IMMDT]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_WRITE_ONLY]			= अणु
		.name	= "IB_OPCODE_RC_RDMA_WRITE_ONLY",
		.mask	= RXE_RETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_START_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_WRITE_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_WRITE_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_RETH_MASK | RXE_IMMDT_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_READ_REQUEST]			= अणु
		.name	= "IB_OPCODE_RC_RDMA_READ_REQUEST",
		.mask	= RXE_RETH_MASK | RXE_REQ_MASK | RXE_READ_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST",
		.mask	= RXE_AETH_MASK | RXE_PAYLOAD_MASK | RXE_ACK_MASK
				| RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_AETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE",
		.mask	= RXE_PAYLOAD_MASK | RXE_ACK_MASK | RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST",
		.mask	= RXE_AETH_MASK | RXE_PAYLOAD_MASK | RXE_ACK_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_AETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY]		= अणु
		.name	= "IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY",
		.mask	= RXE_AETH_MASK | RXE_PAYLOAD_MASK | RXE_ACK_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_AETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_ACKNOWLEDGE]			= अणु
		.name	= "IB_OPCODE_RC_ACKNOWLEDGE",
		.mask	= RXE_AETH_MASK | RXE_ACK_MASK | RXE_START_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_AETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE]			= अणु
		.name	= "IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE",
		.mask	= RXE_AETH_MASK | RXE_ATMACK_MASK | RXE_ACK_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_ATMACK_BYTES + RXE_AETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_AETH]	= RXE_BTH_BYTES,
			[RXE_ATMACK]	= RXE_BTH_BYTES
						+ RXE_AETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
					+ RXE_ATMACK_BYTES + RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_COMPARE_SWAP]			= अणु
		.name	= "IB_OPCODE_RC_COMPARE_SWAP",
		.mask	= RXE_ATMETH_MASK | RXE_REQ_MASK | RXE_ATOMIC_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_ATMETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_ATMETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_ATMETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_FETCH_ADD]			= अणु
		.name	= "IB_OPCODE_RC_FETCH_ADD",
		.mask	= RXE_ATMETH_MASK | RXE_REQ_MASK | RXE_ATOMIC_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_ATMETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_ATMETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_ATMETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE]		= अणु
		.name	= "IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE",
		.mask	= RXE_IETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_SEND_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RC_SEND_ONLY_WITH_INVALIDATE]		= अणु
		.name	= "IB_OPCODE_RC_SEND_ONLY_INV",
		.mask	= RXE_IETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_END_MASK  | RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_IETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IETH_BYTES,
		पूर्ण
	पूर्ण,

	/* UC */
	[IB_OPCODE_UC_SEND_FIRST]			= अणु
		.name	= "IB_OPCODE_UC_SEND_FIRST",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_RWR_MASK
				| RXE_SEND_MASK | RXE_START_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_SEND_MIDDLE]		= अणु
		.name	= "IB_OPCODE_UC_SEND_MIDDLE",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_SEND_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_SEND_LAST]			= अणु
		.name	= "IB_OPCODE_UC_SEND_LAST",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_COMP_MASK
				| RXE_SEND_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE",
		.mask	= RXE_IMMDT_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_SEND_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IMMDT]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_SEND_ONLY]			= अणु
		.name	= "IB_OPCODE_UC_SEND_ONLY",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_COMP_MASK
				| RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_IMMDT_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IMMDT]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_RDMA_WRITE_FIRST]		= अणु
		.name	= "IB_OPCODE_UC_RDMA_WRITE_FIRST",
		.mask	= RXE_RETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_RDMA_WRITE_MIDDLE]		= अणु
		.name	= "IB_OPCODE_UC_RDMA_WRITE_MIDDLE",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_RDMA_WRITE_LAST]			= अणु
		.name	= "IB_OPCODE_UC_RDMA_WRITE_LAST",
		.mask	= RXE_PAYLOAD_MASK | RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE",
		.mask	= RXE_IMMDT_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_IMMDT]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_RDMA_WRITE_ONLY]			= अणु
		.name	= "IB_OPCODE_UC_RDMA_WRITE_ONLY",
		.mask	= RXE_RETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_START_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_RETH_MASK | RXE_IMMDT_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_RETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RETH]	= RXE_BTH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,

	/* RD */
	[IB_OPCODE_RD_SEND_FIRST]			= अणु
		.name	= "IB_OPCODE_RD_SEND_FIRST",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_SEND_MIDDLE]		= अणु
		.name	= "IB_OPCODE_RD_SEND_MIDDLE",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_SEND_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_SEND_LAST]			= अणु
		.name	= "IB_OPCODE_RD_SEND_LAST",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_COMP_MASK | RXE_SEND_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_SEND_LAST_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RD_SEND_LAST_WITH_IMMEDIATE",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_IMMDT_MASK
				| RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_SEND_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_SEND_ONLY]			= अणु
		.name	= "IB_OPCODE_RD_SEND_ONLY",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_SEND_MASK | RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_SEND_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RD_SEND_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_IMMDT_MASK
				| RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_WRITE_FIRST]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_WRITE_FIRST",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_RETH_MASK
				| RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_RETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_WRITE_MIDDLE]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_WRITE_MIDDLE",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_WRITE_LAST]			= अणु
		.name	= "IB_OPCODE_RD_RDMA_WRITE_LAST",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_WRITE_LAST_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_WRITE_LAST_WITH_IMMEDIATE",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_IMMDT_MASK
				| RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_WRITE_ONLY]			= अणु
		.name	= "IB_OPCODE_RD_RDMA_WRITE_ONLY",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_RETH_MASK
				| RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_WRITE_MASK | RXE_START_MASK
				| RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_RETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_RETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_WRITE_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_WRITE_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_RETH_MASK
				| RXE_IMMDT_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_WRITE_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_RETH_BYTES
				+ RXE_DETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_RETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_RETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_RETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_READ_REQUEST]			= अणु
		.name	= "IB_OPCODE_RD_RDMA_READ_REQUEST",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_RETH_MASK
				| RXE_REQ_MASK | RXE_READ_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_RETH_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_RETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RETH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_RDETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_READ_RESPONSE_FIRST]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_READ_RESPONSE_FIRST",
		.mask	= RXE_RDETH_MASK | RXE_AETH_MASK
				| RXE_PAYLOAD_MASK | RXE_ACK_MASK
				| RXE_START_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_AETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_READ_RESPONSE_MIDDLE]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_READ_RESPONSE_MIDDLE",
		.mask	= RXE_RDETH_MASK | RXE_PAYLOAD_MASK | RXE_ACK_MASK
				| RXE_MIDDLE_MASK,
		.length = RXE_BTH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_READ_RESPONSE_LAST]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_READ_RESPONSE_LAST",
		.mask	= RXE_RDETH_MASK | RXE_AETH_MASK | RXE_PAYLOAD_MASK
				| RXE_ACK_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_AETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_RDMA_READ_RESPONSE_ONLY]		= अणु
		.name	= "IB_OPCODE_RD_RDMA_READ_RESPONSE_ONLY",
		.mask	= RXE_RDETH_MASK | RXE_AETH_MASK | RXE_PAYLOAD_MASK
				| RXE_ACK_MASK | RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_AETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_ACKNOWLEDGE]			= अणु
		.name	= "IB_OPCODE_RD_ACKNOWLEDGE",
		.mask	= RXE_RDETH_MASK | RXE_AETH_MASK | RXE_ACK_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_AETH_BYTES + RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_AETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_ATOMIC_ACKNOWLEDGE]			= अणु
		.name	= "IB_OPCODE_RD_ATOMIC_ACKNOWLEDGE",
		.mask	= RXE_RDETH_MASK | RXE_AETH_MASK | RXE_ATMACK_MASK
				| RXE_ACK_MASK | RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_ATMACK_BYTES + RXE_AETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_AETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_ATMACK]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_AETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_COMPARE_SWAP]			= अणु
		.name	= "RD_COMPARE_SWAP",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_ATMETH_MASK
				| RXE_REQ_MASK | RXE_ATOMIC_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_ATMETH_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_ATMETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES +
						+ RXE_ATMETH_BYTES
						+ RXE_DETH_BYTES +
						+ RXE_RDETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_RD_FETCH_ADD]			= अणु
		.name	= "IB_OPCODE_RD_FETCH_ADD",
		.mask	= RXE_RDETH_MASK | RXE_DETH_MASK | RXE_ATMETH_MASK
				| RXE_REQ_MASK | RXE_ATOMIC_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_ATMETH_BYTES + RXE_DETH_BYTES
				+ RXE_RDETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_RDETH]	= RXE_BTH_BYTES,
			[RXE_DETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES,
			[RXE_ATMETH]	= RXE_BTH_BYTES
						+ RXE_RDETH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES +
						+ RXE_ATMETH_BYTES
						+ RXE_DETH_BYTES +
						+ RXE_RDETH_BYTES,
		पूर्ण
	पूर्ण,

	/* UD */
	[IB_OPCODE_UD_SEND_ONLY]			= अणु
		.name	= "IB_OPCODE_UD_SEND_ONLY",
		.mask	= RXE_DETH_MASK | RXE_PAYLOAD_MASK | RXE_REQ_MASK
				| RXE_COMP_MASK | RXE_RWR_MASK | RXE_SEND_MASK
				| RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_DETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_DETH]	= RXE_BTH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_DETH_BYTES,
		पूर्ण
	पूर्ण,
	[IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE]		= अणु
		.name	= "IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE",
		.mask	= RXE_DETH_MASK | RXE_IMMDT_MASK | RXE_PAYLOAD_MASK
				| RXE_REQ_MASK | RXE_COMP_MASK | RXE_RWR_MASK
				| RXE_SEND_MASK | RXE_START_MASK | RXE_END_MASK,
		.length = RXE_BTH_BYTES + RXE_IMMDT_BYTES + RXE_DETH_BYTES,
		.offset = अणु
			[RXE_BTH]	= 0,
			[RXE_DETH]	= RXE_BTH_BYTES,
			[RXE_IMMDT]	= RXE_BTH_BYTES
						+ RXE_DETH_BYTES,
			[RXE_PAYLOAD]	= RXE_BTH_BYTES
						+ RXE_DETH_BYTES
						+ RXE_IMMDT_BYTES,
		पूर्ण
	पूर्ण,

पूर्ण;
