<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_EMAD_H
#घोषणा _MLXSW_EMAD_H

#घोषणा MLXSW_EMAD_MAX_FRAME_LEN 1518	/* Length in u8 */
#घोषणा MLXSW_EMAD_MAX_RETRY 5

/* EMAD Ethernet header */
#घोषणा MLXSW_EMAD_ETH_HDR_LEN 0x10	/* Length in u8 */
#घोषणा MLXSW_EMAD_EH_DMAC "\x01\x02\xc9\x00\x00\x01"
#घोषणा MLXSW_EMAD_EH_SMAC "\x00\x02\xc9\x01\x02\x03"
#घोषणा MLXSW_EMAD_EH_ETHERTYPE 0x8932
#घोषणा MLXSW_EMAD_EH_MLX_PROTO 0
#घोषणा MLXSW_EMAD_EH_PROTO_VERSION 0

/* EMAD TLV Types */
क्रमागत अणु
	MLXSW_EMAD_TLV_TYPE_END,
	MLXSW_EMAD_TLV_TYPE_OP,
	MLXSW_EMAD_TLV_TYPE_STRING,
	MLXSW_EMAD_TLV_TYPE_REG,
पूर्ण;

/* OP TLV */
#घोषणा MLXSW_EMAD_OP_TLV_LEN 4		/* Length in u32 */

क्रमागत अणु
	MLXSW_EMAD_OP_TLV_CLASS_REG_ACCESS = 1,
	MLXSW_EMAD_OP_TLV_CLASS_IPC = 2,
पूर्ण;

क्रमागत mlxsw_emad_op_tlv_status अणु
	MLXSW_EMAD_OP_TLV_STATUS_SUCCESS,
	MLXSW_EMAD_OP_TLV_STATUS_BUSY,
	MLXSW_EMAD_OP_TLV_STATUS_VERSION_NOT_SUPPORTED,
	MLXSW_EMAD_OP_TLV_STATUS_UNKNOWN_TLV,
	MLXSW_EMAD_OP_TLV_STATUS_REGISTER_NOT_SUPPORTED,
	MLXSW_EMAD_OP_TLV_STATUS_CLASS_NOT_SUPPORTED,
	MLXSW_EMAD_OP_TLV_STATUS_METHOD_NOT_SUPPORTED,
	MLXSW_EMAD_OP_TLV_STATUS_BAD_PARAMETER,
	MLXSW_EMAD_OP_TLV_STATUS_RESOURCE_NOT_AVAILABLE,
	MLXSW_EMAD_OP_TLV_STATUS_MESSAGE_RECEIPT_ACK,
	MLXSW_EMAD_OP_TLV_STATUS_INTERNAL_ERROR = 0x70,
पूर्ण;

अटल अंतरभूत अक्षर *mlxsw_emad_op_tlv_status_str(u8 status)
अणु
	चयन (status) अणु
	हाल MLXSW_EMAD_OP_TLV_STATUS_SUCCESS:
		वापस "operation performed";
	हाल MLXSW_EMAD_OP_TLV_STATUS_BUSY:
		वापस "device is busy";
	हाल MLXSW_EMAD_OP_TLV_STATUS_VERSION_NOT_SUPPORTED:
		वापस "version not supported";
	हाल MLXSW_EMAD_OP_TLV_STATUS_UNKNOWN_TLV:
		वापस "unknown TLV";
	हाल MLXSW_EMAD_OP_TLV_STATUS_REGISTER_NOT_SUPPORTED:
		वापस "register not supported";
	हाल MLXSW_EMAD_OP_TLV_STATUS_CLASS_NOT_SUPPORTED:
		वापस "class not supported";
	हाल MLXSW_EMAD_OP_TLV_STATUS_METHOD_NOT_SUPPORTED:
		वापस "method not supported";
	हाल MLXSW_EMAD_OP_TLV_STATUS_BAD_PARAMETER:
		वापस "bad parameter";
	हाल MLXSW_EMAD_OP_TLV_STATUS_RESOURCE_NOT_AVAILABLE:
		वापस "resource not available";
	हाल MLXSW_EMAD_OP_TLV_STATUS_MESSAGE_RECEIPT_ACK:
		वापस "acknowledged. retransmit";
	हाल MLXSW_EMAD_OP_TLV_STATUS_INTERNAL_ERROR:
		वापस "internal error";
	शेष:
		वापस "*UNKNOWN*";
	पूर्ण
पूर्ण

क्रमागत अणु
	MLXSW_EMAD_OP_TLV_REQUEST,
	MLXSW_EMAD_OP_TLV_RESPONSE
पूर्ण;

क्रमागत अणु
	MLXSW_EMAD_OP_TLV_METHOD_QUERY = 1,
	MLXSW_EMAD_OP_TLV_METHOD_WRITE = 2,
	MLXSW_EMAD_OP_TLV_METHOD_SEND = 3,
	MLXSW_EMAD_OP_TLV_METHOD_EVENT = 5,
पूर्ण;

/* STRING TLV */
#घोषणा MLXSW_EMAD_STRING_TLV_LEN 33	/* Length in u32 */

/* END TLV */
#घोषणा MLXSW_EMAD_END_TLV_LEN 1	/* Length in u32 */

#पूर्ण_अगर
