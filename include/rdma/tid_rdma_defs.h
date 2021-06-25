<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */

#अगर_अघोषित TID_RDMA_DEFS_H
#घोषणा TID_RDMA_DEFS_H

#समावेश <rdma/ib_pack.h>

काष्ठा tid_rdma_पढ़ो_req अणु
	__le32 kdeth0;
	__le32 kdeth1;
	काष्ठा ib_reth reth;
	__be32 tid_flow_psn;
	__be32 tid_flow_qp;
	__be32 verbs_qp;
पूर्ण;

काष्ठा tid_rdma_पढ़ो_resp अणु
	__le32 kdeth0;
	__le32 kdeth1;
	__be32 aeth;
	__be32 reserved[4];
	__be32 verbs_psn;
	__be32 verbs_qp;
पूर्ण;

काष्ठा tid_rdma_ग_लिखो_req अणु
	__le32 kdeth0;
	__le32 kdeth1;
	काष्ठा ib_reth reth;
	__be32 reserved[2];
	__be32 verbs_qp;
पूर्ण;

काष्ठा tid_rdma_ग_लिखो_resp अणु
	__le32 kdeth0;
	__le32 kdeth1;
	__be32 aeth;
	__be32 reserved[3];
	__be32 tid_flow_psn;
	__be32 tid_flow_qp;
	__be32 verbs_qp;
पूर्ण;

काष्ठा tid_rdma_ग_लिखो_data अणु
	__le32 kdeth0;
	__le32 kdeth1;
	__be32 reserved[6];
	__be32 verbs_qp;
पूर्ण;

काष्ठा tid_rdma_resync अणु
	__le32 kdeth0;
	__le32 kdeth1;
	__be32 reserved[6];
	__be32 verbs_qp;
पूर्ण;

काष्ठा tid_rdma_ack अणु
	__le32 kdeth0;
	__le32 kdeth1;
	__be32 aeth;
	__be32 reserved[2];
	__be32 tid_flow_psn;
	__be32 verbs_psn;
	__be32 tid_flow_qp;
	__be32 verbs_qp;
पूर्ण;

/*
 * TID RDMA Opcodes
 */
#घोषणा IB_OPCODE_TID_RDMA 0xe0
क्रमागत अणु
	IB_OPCODE_WRITE_REQ       = 0x0,
	IB_OPCODE_WRITE_RESP      = 0x1,
	IB_OPCODE_WRITE_DATA      = 0x2,
	IB_OPCODE_WRITE_DATA_LAST = 0x3,
	IB_OPCODE_READ_REQ        = 0x4,
	IB_OPCODE_READ_RESP       = 0x5,
	IB_OPCODE_RESYNC          = 0x6,
	IB_OPCODE_ACK             = 0x7,

	IB_OPCODE(TID_RDMA, WRITE_REQ),
	IB_OPCODE(TID_RDMA, WRITE_RESP),
	IB_OPCODE(TID_RDMA, WRITE_DATA),
	IB_OPCODE(TID_RDMA, WRITE_DATA_LAST),
	IB_OPCODE(TID_RDMA, READ_REQ),
	IB_OPCODE(TID_RDMA, READ_RESP),
	IB_OPCODE(TID_RDMA, RESYNC),
	IB_OPCODE(TID_RDMA, ACK),
पूर्ण;

#घोषणा TID_OP(x) IB_OPCODE_TID_RDMA_##x

/*
 * Define TID RDMA specअगरic WR opcodes. The ib_wr_opcode
 * क्रमागत alपढ़ोy provides some reserved values क्रम use by
 * low level drivers. Two of those are used but नामd
 * to be more descriptive.
 */
#घोषणा IB_WR_TID_RDMA_WRITE IB_WR_RESERVED1
#घोषणा IB_WR_TID_RDMA_READ  IB_WR_RESERVED2

#पूर्ण_अगर /* TID_RDMA_DEFS_H */
