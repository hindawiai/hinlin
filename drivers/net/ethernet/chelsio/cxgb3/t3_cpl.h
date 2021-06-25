<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Chelsio, Inc. All rights reserved.
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
#अगर_अघोषित T3_CPL_H
#घोषणा T3_CPL_H

#अगर !defined(__LITTLE_ENDIAN_BITFIELD) && !defined(__BIG_ENDIAN_BITFIELD)
# include <यंत्र/byteorder.h>
#पूर्ण_अगर

क्रमागत CPL_opcode अणु
	CPL_PASS_OPEN_REQ = 0x1,
	CPL_PASS_ACCEPT_RPL = 0x2,
	CPL_ACT_OPEN_REQ = 0x3,
	CPL_SET_TCB = 0x4,
	CPL_SET_TCB_FIELD = 0x5,
	CPL_GET_TCB = 0x6,
	CPL_PCMD = 0x7,
	CPL_CLOSE_CON_REQ = 0x8,
	CPL_CLOSE_LISTSRV_REQ = 0x9,
	CPL_ABORT_REQ = 0xA,
	CPL_ABORT_RPL = 0xB,
	CPL_TX_DATA = 0xC,
	CPL_RX_DATA_ACK = 0xD,
	CPL_TX_PKT = 0xE,
	CPL_RTE_DELETE_REQ = 0xF,
	CPL_RTE_WRITE_REQ = 0x10,
	CPL_RTE_READ_REQ = 0x11,
	CPL_L2T_WRITE_REQ = 0x12,
	CPL_L2T_READ_REQ = 0x13,
	CPL_SMT_WRITE_REQ = 0x14,
	CPL_SMT_READ_REQ = 0x15,
	CPL_TX_PKT_LSO = 0x16,
	CPL_PCMD_READ = 0x17,
	CPL_BARRIER = 0x18,
	CPL_TID_RELEASE = 0x1A,

	CPL_CLOSE_LISTSRV_RPL = 0x20,
	CPL_ERROR = 0x21,
	CPL_GET_TCB_RPL = 0x22,
	CPL_L2T_WRITE_RPL = 0x23,
	CPL_PCMD_READ_RPL = 0x24,
	CPL_PCMD_RPL = 0x25,
	CPL_PEER_CLOSE = 0x26,
	CPL_RTE_DELETE_RPL = 0x27,
	CPL_RTE_WRITE_RPL = 0x28,
	CPL_RX_DDP_COMPLETE = 0x29,
	CPL_RX_PHYS_ADDR = 0x2A,
	CPL_RX_PKT = 0x2B,
	CPL_RX_URG_NOTIFY = 0x2C,
	CPL_SET_TCB_RPL = 0x2D,
	CPL_SMT_WRITE_RPL = 0x2E,
	CPL_TX_DATA_ACK = 0x2F,

	CPL_ABORT_REQ_RSS = 0x30,
	CPL_ABORT_RPL_RSS = 0x31,
	CPL_CLOSE_CON_RPL = 0x32,
	CPL_ISCSI_HDR = 0x33,
	CPL_L2T_READ_RPL = 0x34,
	CPL_RDMA_CQE = 0x35,
	CPL_RDMA_CQE_READ_RSP = 0x36,
	CPL_RDMA_CQE_ERR = 0x37,
	CPL_RTE_READ_RPL = 0x38,
	CPL_RX_DATA = 0x39,

	CPL_ACT_OPEN_RPL = 0x40,
	CPL_PASS_OPEN_RPL = 0x41,
	CPL_RX_DATA_DDP = 0x42,
	CPL_SMT_READ_RPL = 0x43,

	CPL_ACT_ESTABLISH = 0x50,
	CPL_PASS_ESTABLISH = 0x51,

	CPL_PASS_ACCEPT_REQ = 0x70,

	CPL_ASYNC_NOTIF = 0x80,	/* fake opcode क्रम async notअगरications */

	CPL_TX_DMA_ACK = 0xA0,
	CPL_RDMA_READ_REQ = 0xA1,
	CPL_RDMA_TERMINATE = 0xA2,
	CPL_TRACE_PKT = 0xA3,
	CPL_RDMA_EC_STATUS = 0xA5,

	NUM_CPL_CMDS		/* must be last and previous entries must be sorted */
पूर्ण;

क्रमागत CPL_error अणु
	CPL_ERR_NONE = 0,
	CPL_ERR_TCAM_PARITY = 1,
	CPL_ERR_TCAM_FULL = 3,
	CPL_ERR_CONN_RESET = 20,
	CPL_ERR_CONN_EXIST = 22,
	CPL_ERR_ARP_MISS = 23,
	CPL_ERR_BAD_SYN = 24,
	CPL_ERR_CONN_TIMEDOUT = 30,
	CPL_ERR_XMIT_TIMEDOUT = 31,
	CPL_ERR_PERSIST_TIMEDOUT = 32,
	CPL_ERR_FINWAIT2_TIMEDOUT = 33,
	CPL_ERR_KEEPALIVE_TIMEDOUT = 34,
	CPL_ERR_RTX_NEG_ADVICE = 35,
	CPL_ERR_PERSIST_NEG_ADVICE = 36,
	CPL_ERR_ABORT_FAILED = 42,
	CPL_ERR_GENERAL = 99
पूर्ण;

क्रमागत अणु
	CPL_CONN_POLICY_AUTO = 0,
	CPL_CONN_POLICY_ASK = 1,
	CPL_CONN_POLICY_DENY = 3
पूर्ण;

क्रमागत अणु
	ULP_MODE_NONE = 0,
	ULP_MODE_ISCSI = 2,
	ULP_MODE_RDMA = 4,
	ULP_MODE_TCPDDP = 5
पूर्ण;

क्रमागत अणु
	ULP_CRC_HEADER = 1 << 0,
	ULP_CRC_DATA = 1 << 1
पूर्ण;

क्रमागत अणु
	CPL_PASS_OPEN_ACCEPT,
	CPL_PASS_OPEN_REJECT
पूर्ण;

क्रमागत अणु
	CPL_ABORT_SEND_RST = 0,
	CPL_ABORT_NO_RST,
	CPL_ABORT_POST_CLOSE_REQ = 2
पूर्ण;

क्रमागत अणु				/* TX_PKT_LSO ethernet types */
	CPL_ETH_II,
	CPL_ETH_II_VLAN,
	CPL_ETH_802_3,
	CPL_ETH_802_3_VLAN
पूर्ण;

क्रमागत अणु				/* TCP congestion control algorithms */
	CONG_ALG_RENO,
	CONG_ALG_TAHOE,
	CONG_ALG_NEWRENO,
	CONG_ALG_HIGHSPEED
पूर्ण;

क्रमागत अणु			/* RSS hash type */
	RSS_HASH_NONE = 0,
	RSS_HASH_2_TUPLE = 1,
	RSS_HASH_4_TUPLE = 2,
	RSS_HASH_TCPV6 = 3
पूर्ण;

जोड़ opcode_tid अणु
	__be32 opcode_tid;
	__u8 opcode;
पूर्ण;

#घोषणा S_OPCODE 24
#घोषणा V_OPCODE(x) ((x) << S_OPCODE)
#घोषणा G_OPCODE(x) (((x) >> S_OPCODE) & 0xFF)
#घोषणा G_TID(x)    ((x) & 0xFFFFFF)

#घोषणा S_QNUM 0
#घोषणा G_QNUM(x) (((x) >> S_QNUM) & 0xFFFF)

#घोषणा S_HASHTYPE 22
#घोषणा M_HASHTYPE 0x3
#घोषणा G_HASHTYPE(x) (((x) >> S_HASHTYPE) & M_HASHTYPE)

/* tid is assumed to be 24-bits */
#घोषणा MK_OPCODE_TID(opcode, tid) (V_OPCODE(opcode) | (tid))

#घोषणा OPCODE_TID(cmd) ((cmd)->ot.opcode_tid)

/* extract the TID from a CPL command */
#घोषणा GET_TID(cmd) (G_TID(ntohl(OPCODE_TID(cmd))))

काष्ठा tcp_options अणु
	__be16 mss;
	__u8 wsf;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	 __u8:5;
	__u8 ecn:1;
	__u8 sack:1;
	__u8 tstamp:1;
#अन्यथा
	__u8 tstamp:1;
	__u8 sack:1;
	__u8 ecn:1;
	 __u8:5;
#पूर्ण_अगर
पूर्ण;

काष्ठा rss_header अणु
	__u8 opcode;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 cpu_idx:6;
	__u8 hash_type:2;
#अन्यथा
	__u8 hash_type:2;
	__u8 cpu_idx:6;
#पूर्ण_अगर
	__be16 cq_idx;
	__be32 rss_hash_val;
पूर्ण;

#अगर_अघोषित CHELSIO_FW
काष्ठा work_request_hdr अणु
	__be32 wr_hi;
	__be32 wr_lo;
पूर्ण;

/* wr_hi fields */
#घोषणा S_WR_SGE_CREDITS    0
#घोषणा M_WR_SGE_CREDITS    0xFF
#घोषणा V_WR_SGE_CREDITS(x) ((x) << S_WR_SGE_CREDITS)
#घोषणा G_WR_SGE_CREDITS(x) (((x) >> S_WR_SGE_CREDITS) & M_WR_SGE_CREDITS)

#घोषणा S_WR_SGLSFLT    8
#घोषणा M_WR_SGLSFLT    0xFF
#घोषणा V_WR_SGLSFLT(x) ((x) << S_WR_SGLSFLT)
#घोषणा G_WR_SGLSFLT(x) (((x) >> S_WR_SGLSFLT) & M_WR_SGLSFLT)

#घोषणा S_WR_BCNTLFLT    16
#घोषणा M_WR_BCNTLFLT    0xF
#घोषणा V_WR_BCNTLFLT(x) ((x) << S_WR_BCNTLFLT)
#घोषणा G_WR_BCNTLFLT(x) (((x) >> S_WR_BCNTLFLT) & M_WR_BCNTLFLT)

#घोषणा S_WR_DATATYPE    20
#घोषणा V_WR_DATATYPE(x) ((x) << S_WR_DATATYPE)
#घोषणा F_WR_DATATYPE    V_WR_DATATYPE(1U)

#घोषणा S_WR_COMPL    21
#घोषणा V_WR_COMPL(x) ((x) << S_WR_COMPL)
#घोषणा F_WR_COMPL    V_WR_COMPL(1U)

#घोषणा S_WR_EOP    22
#घोषणा V_WR_EOP(x) ((x) << S_WR_EOP)
#घोषणा F_WR_EOP    V_WR_EOP(1U)

#घोषणा S_WR_SOP    23
#घोषणा V_WR_SOP(x) ((x) << S_WR_SOP)
#घोषणा F_WR_SOP    V_WR_SOP(1U)

#घोषणा S_WR_OP    24
#घोषणा M_WR_OP    0xFF
#घोषणा V_WR_OP(x) ((x) << S_WR_OP)
#घोषणा G_WR_OP(x) (((x) >> S_WR_OP) & M_WR_OP)

/* wr_lo fields */
#घोषणा S_WR_LEN    0
#घोषणा M_WR_LEN    0xFF
#घोषणा V_WR_LEN(x) ((x) << S_WR_LEN)
#घोषणा G_WR_LEN(x) (((x) >> S_WR_LEN) & M_WR_LEN)

#घोषणा S_WR_TID    8
#घोषणा M_WR_TID    0xFFFFF
#घोषणा V_WR_TID(x) ((x) << S_WR_TID)
#घोषणा G_WR_TID(x) (((x) >> S_WR_TID) & M_WR_TID)

#घोषणा S_WR_CR_FLUSH    30
#घोषणा V_WR_CR_FLUSH(x) ((x) << S_WR_CR_FLUSH)
#घोषणा F_WR_CR_FLUSH    V_WR_CR_FLUSH(1U)

#घोषणा S_WR_GEN    31
#घोषणा V_WR_GEN(x) ((x) << S_WR_GEN)
#घोषणा F_WR_GEN    V_WR_GEN(1U)

# define WR_HDR काष्ठा work_request_hdr wr
# define RSS_HDR
#अन्यथा
# define WR_HDR
# define RSS_HDR काष्ठा rss_header rss_hdr;
#पूर्ण_अगर

/* option 0 lower-half fields */
#घोषणा S_CPL_STATUS    0
#घोषणा M_CPL_STATUS    0xFF
#घोषणा V_CPL_STATUS(x) ((x) << S_CPL_STATUS)
#घोषणा G_CPL_STATUS(x) (((x) >> S_CPL_STATUS) & M_CPL_STATUS)

#घोषणा S_INJECT_TIMER    6
#घोषणा V_INJECT_TIMER(x) ((x) << S_INJECT_TIMER)
#घोषणा F_INJECT_TIMER    V_INJECT_TIMER(1U)

#घोषणा S_NO_OFFLOAD    7
#घोषणा V_NO_OFFLOAD(x) ((x) << S_NO_OFFLOAD)
#घोषणा F_NO_OFFLOAD    V_NO_OFFLOAD(1U)

#घोषणा S_ULP_MODE    8
#घोषणा M_ULP_MODE    0xF
#घोषणा V_ULP_MODE(x) ((x) << S_ULP_MODE)
#घोषणा G_ULP_MODE(x) (((x) >> S_ULP_MODE) & M_ULP_MODE)

#घोषणा S_RCV_बफ_मान    12
#घोषणा M_RCV_बफ_मान    0x3FFF
#घोषणा V_RCV_बफ_मान(x) ((x) << S_RCV_बफ_मान)
#घोषणा G_RCV_बफ_मान(x) (((x) >> S_RCV_बफ_मान) & M_RCV_बफ_मान)

#घोषणा S_TOS    26
#घोषणा M_TOS    0x3F
#घोषणा V_TOS(x) ((x) << S_TOS)
#घोषणा G_TOS(x) (((x) >> S_TOS) & M_TOS)

/* option 0 upper-half fields */
#घोषणा S_DELACK    0
#घोषणा V_DELACK(x) ((x) << S_DELACK)
#घोषणा F_DELACK    V_DELACK(1U)

#घोषणा S_NO_CONG    1
#घोषणा V_NO_CONG(x) ((x) << S_NO_CONG)
#घोषणा F_NO_CONG    V_NO_CONG(1U)

#घोषणा S_SRC_MAC_SEL    2
#घोषणा M_SRC_MAC_SEL    0x3
#घोषणा V_SRC_MAC_SEL(x) ((x) << S_SRC_MAC_SEL)
#घोषणा G_SRC_MAC_SEL(x) (((x) >> S_SRC_MAC_SEL) & M_SRC_MAC_SEL)

#घोषणा S_L2T_IDX    4
#घोषणा M_L2T_IDX    0x7FF
#घोषणा V_L2T_IDX(x) ((x) << S_L2T_IDX)
#घोषणा G_L2T_IDX(x) (((x) >> S_L2T_IDX) & M_L2T_IDX)

#घोषणा S_TX_CHANNEL    15
#घोषणा V_TX_CHANNEL(x) ((x) << S_TX_CHANNEL)
#घोषणा F_TX_CHANNEL    V_TX_CHANNEL(1U)

#घोषणा S_TCAM_BYPASS    16
#घोषणा V_TCAM_BYPASS(x) ((x) << S_TCAM_BYPASS)
#घोषणा F_TCAM_BYPASS    V_TCAM_BYPASS(1U)

#घोषणा S_NAGLE    17
#घोषणा V_NAGLE(x) ((x) << S_NAGLE)
#घोषणा F_NAGLE    V_NAGLE(1U)

#घोषणा S_WND_SCALE    18
#घोषणा M_WND_SCALE    0xF
#घोषणा V_WND_SCALE(x) ((x) << S_WND_SCALE)
#घोषणा G_WND_SCALE(x) (((x) >> S_WND_SCALE) & M_WND_SCALE)

#घोषणा S_KEEP_ALIVE    22
#घोषणा V_KEEP_ALIVE(x) ((x) << S_KEEP_ALIVE)
#घोषणा F_KEEP_ALIVE    V_KEEP_ALIVE(1U)

#घोषणा S_MAX_RETRANS    23
#घोषणा M_MAX_RETRANS    0xF
#घोषणा V_MAX_RETRANS(x) ((x) << S_MAX_RETRANS)
#घोषणा G_MAX_RETRANS(x) (((x) >> S_MAX_RETRANS) & M_MAX_RETRANS)

#घोषणा S_MAX_RETRANS_OVERRIDE    27
#घोषणा V_MAX_RETRANS_OVERRIDE(x) ((x) << S_MAX_RETRANS_OVERRIDE)
#घोषणा F_MAX_RETRANS_OVERRIDE    V_MAX_RETRANS_OVERRIDE(1U)

#घोषणा S_MSS_IDX    28
#घोषणा M_MSS_IDX    0xF
#घोषणा V_MSS_IDX(x) ((x) << S_MSS_IDX)
#घोषणा G_MSS_IDX(x) (((x) >> S_MSS_IDX) & M_MSS_IDX)

/* option 1 fields */
#घोषणा S_RSS_ENABLE    0
#घोषणा V_RSS_ENABLE(x) ((x) << S_RSS_ENABLE)
#घोषणा F_RSS_ENABLE    V_RSS_ENABLE(1U)

#घोषणा S_RSS_MASK_LEN    1
#घोषणा M_RSS_MASK_LEN    0x7
#घोषणा V_RSS_MASK_LEN(x) ((x) << S_RSS_MASK_LEN)
#घोषणा G_RSS_MASK_LEN(x) (((x) >> S_RSS_MASK_LEN) & M_RSS_MASK_LEN)

#घोषणा S_CPU_IDX    4
#घोषणा M_CPU_IDX    0x3F
#घोषणा V_CPU_IDX(x) ((x) << S_CPU_IDX)
#घोषणा G_CPU_IDX(x) (((x) >> S_CPU_IDX) & M_CPU_IDX)

#घोषणा S_MAC_MATCH_VALID    18
#घोषणा V_MAC_MATCH_VALID(x) ((x) << S_MAC_MATCH_VALID)
#घोषणा F_MAC_MATCH_VALID    V_MAC_MATCH_VALID(1U)

#घोषणा S_CONN_POLICY    19
#घोषणा M_CONN_POLICY    0x3
#घोषणा V_CONN_POLICY(x) ((x) << S_CONN_POLICY)
#घोषणा G_CONN_POLICY(x) (((x) >> S_CONN_POLICY) & M_CONN_POLICY)

#घोषणा S_SYN_DEFENSE    21
#घोषणा V_SYN_DEFENSE(x) ((x) << S_SYN_DEFENSE)
#घोषणा F_SYN_DEFENSE    V_SYN_DEFENSE(1U)

#घोषणा S_VLAN_PRI    22
#घोषणा M_VLAN_PRI    0x3
#घोषणा V_VLAN_PRI(x) ((x) << S_VLAN_PRI)
#घोषणा G_VLAN_PRI(x) (((x) >> S_VLAN_PRI) & M_VLAN_PRI)

#घोषणा S_VLAN_PRI_VALID    24
#घोषणा V_VLAN_PRI_VALID(x) ((x) << S_VLAN_PRI_VALID)
#घोषणा F_VLAN_PRI_VALID    V_VLAN_PRI_VALID(1U)

#घोषणा S_PKT_TYPE    25
#घोषणा M_PKT_TYPE    0x3
#घोषणा V_PKT_TYPE(x) ((x) << S_PKT_TYPE)
#घोषणा G_PKT_TYPE(x) (((x) >> S_PKT_TYPE) & M_PKT_TYPE)

#घोषणा S_MAC_MATCH    27
#घोषणा M_MAC_MATCH    0x1F
#घोषणा V_MAC_MATCH(x) ((x) << S_MAC_MATCH)
#घोषणा G_MAC_MATCH(x) (((x) >> S_MAC_MATCH) & M_MAC_MATCH)

/* option 2 fields */
#घोषणा S_CPU_INDEX    0
#घोषणा M_CPU_INDEX    0x7F
#घोषणा V_CPU_INDEX(x) ((x) << S_CPU_INDEX)
#घोषणा G_CPU_INDEX(x) (((x) >> S_CPU_INDEX) & M_CPU_INDEX)

#घोषणा S_CPU_INDEX_VALID    7
#घोषणा V_CPU_INDEX_VALID(x) ((x) << S_CPU_INDEX_VALID)
#घोषणा F_CPU_INDEX_VALID    V_CPU_INDEX_VALID(1U)

#घोषणा S_RX_COALESCE    8
#घोषणा M_RX_COALESCE    0x3
#घोषणा V_RX_COALESCE(x) ((x) << S_RX_COALESCE)
#घोषणा G_RX_COALESCE(x) (((x) >> S_RX_COALESCE) & M_RX_COALESCE)

#घोषणा S_RX_COALESCE_VALID    10
#घोषणा V_RX_COALESCE_VALID(x) ((x) << S_RX_COALESCE_VALID)
#घोषणा F_RX_COALESCE_VALID    V_RX_COALESCE_VALID(1U)

#घोषणा S_CONG_CONTROL_FLAVOR    11
#घोषणा M_CONG_CONTROL_FLAVOR    0x3
#घोषणा V_CONG_CONTROL_FLAVOR(x) ((x) << S_CONG_CONTROL_FLAVOR)
#घोषणा G_CONG_CONTROL_FLAVOR(x) (((x) >> S_CONG_CONTROL_FLAVOR) & M_CONG_CONTROL_FLAVOR)

#घोषणा S_PACING_FLAVOR    13
#घोषणा M_PACING_FLAVOR    0x3
#घोषणा V_PACING_FLAVOR(x) ((x) << S_PACING_FLAVOR)
#घोषणा G_PACING_FLAVOR(x) (((x) >> S_PACING_FLAVOR) & M_PACING_FLAVOR)

#घोषणा S_FLAVORS_VALID    15
#घोषणा V_FLAVORS_VALID(x) ((x) << S_FLAVORS_VALID)
#घोषणा F_FLAVORS_VALID    V_FLAVORS_VALID(1U)

#घोषणा S_RX_FC_DISABLE    16
#घोषणा V_RX_FC_DISABLE(x) ((x) << S_RX_FC_DISABLE)
#घोषणा F_RX_FC_DISABLE    V_RX_FC_DISABLE(1U)

#घोषणा S_RX_FC_VALID    17
#घोषणा V_RX_FC_VALID(x) ((x) << S_RX_FC_VALID)
#घोषणा F_RX_FC_VALID    V_RX_FC_VALID(1U)

काष्ठा cpl_pass_खोलो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be32 opt0h;
	__be32 opt0l;
	__be32 peer_neपंचांगask;
	__be32 opt1;
पूर्ण;

काष्ठा cpl_pass_खोलो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__u8 resvd[7];
	__u8 status;
पूर्ण;

काष्ठा cpl_pass_establish अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be32 tos_tid;
	__be16 l2t_idx;
	__be16 tcp_opt;
	__be32 snd_isn;
	__be32 rcv_isn;
पूर्ण;

/* cpl_pass_establish.tos_tid fields */
#घोषणा S_PASS_OPEN_TID    0
#घोषणा M_PASS_OPEN_TID    0xFFFFFF
#घोषणा V_PASS_OPEN_TID(x) ((x) << S_PASS_OPEN_TID)
#घोषणा G_PASS_OPEN_TID(x) (((x) >> S_PASS_OPEN_TID) & M_PASS_OPEN_TID)

#घोषणा S_PASS_OPEN_TOS    24
#घोषणा M_PASS_OPEN_TOS    0xFF
#घोषणा V_PASS_OPEN_TOS(x) ((x) << S_PASS_OPEN_TOS)
#घोषणा G_PASS_OPEN_TOS(x) (((x) >> S_PASS_OPEN_TOS) & M_PASS_OPEN_TOS)

/* cpl_pass_establish.l2t_idx fields */
#घोषणा S_L2T_IDX16    5
#घोषणा M_L2T_IDX16    0x7FF
#घोषणा V_L2T_IDX16(x) ((x) << S_L2T_IDX16)
#घोषणा G_L2T_IDX16(x) (((x) >> S_L2T_IDX16) & M_L2T_IDX16)

/* cpl_pass_establish.tcp_opt fields (also applies act_खोलो_establish) */
#घोषणा G_TCPOPT_WSCALE_OK(x)  (((x) >> 5) & 1)
#घोषणा G_TCPOPT_SACK(x)       (((x) >> 6) & 1)
#घोषणा G_TCPOPT_TSTAMP(x)     (((x) >> 7) & 1)
#घोषणा G_TCPOPT_SND_WSCALE(x) (((x) >> 8) & 0xf)
#घोषणा G_TCPOPT_MSS(x)        (((x) >> 12) & 0xf)

काष्ठा cpl_pass_accept_req अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be32 tos_tid;
	काष्ठा tcp_options tcp_options;
	__u8 dst_mac[6];
	__be16 vlan_tag;
	__u8 src_mac[6];
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	 __u8:3;
	__u8 addr_idx:3;
	__u8 port_idx:1;
	__u8 exact_match:1;
#अन्यथा
	__u8 exact_match:1;
	__u8 port_idx:1;
	__u8 addr_idx:3;
	 __u8:3;
#पूर्ण_अगर
	__u8 rsvd;
	__be32 rcv_isn;
	__be32 rsvd2;
पूर्ण;

काष्ठा cpl_pass_accept_rpl अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 opt2;
	__be32 rsvd;
	__be32 peer_ip;
	__be32 opt0h;
	__be32 opt0l_status;
पूर्ण;

काष्ठा cpl_act_खोलो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be32 opt0h;
	__be32 opt0l;
	__be32 params;
	__be32 opt2;
पूर्ण;

/* cpl_act_खोलो_req.params fields */
#घोषणा S_AOPEN_VLAN_PRI    9
#घोषणा M_AOPEN_VLAN_PRI    0x3
#घोषणा V_AOPEN_VLAN_PRI(x) ((x) << S_AOPEN_VLAN_PRI)
#घोषणा G_AOPEN_VLAN_PRI(x) (((x) >> S_AOPEN_VLAN_PRI) & M_AOPEN_VLAN_PRI)

#घोषणा S_AOPEN_VLAN_PRI_VALID    11
#घोषणा V_AOPEN_VLAN_PRI_VALID(x) ((x) << S_AOPEN_VLAN_PRI_VALID)
#घोषणा F_AOPEN_VLAN_PRI_VALID    V_AOPEN_VLAN_PRI_VALID(1U)

#घोषणा S_AOPEN_PKT_TYPE    12
#घोषणा M_AOPEN_PKT_TYPE    0x3
#घोषणा V_AOPEN_PKT_TYPE(x) ((x) << S_AOPEN_PKT_TYPE)
#घोषणा G_AOPEN_PKT_TYPE(x) (((x) >> S_AOPEN_PKT_TYPE) & M_AOPEN_PKT_TYPE)

#घोषणा S_AOPEN_MAC_MATCH    14
#घोषणा M_AOPEN_MAC_MATCH    0x1F
#घोषणा V_AOPEN_MAC_MATCH(x) ((x) << S_AOPEN_MAC_MATCH)
#घोषणा G_AOPEN_MAC_MATCH(x) (((x) >> S_AOPEN_MAC_MATCH) & M_AOPEN_MAC_MATCH)

#घोषणा S_AOPEN_MAC_MATCH_VALID    19
#घोषणा V_AOPEN_MAC_MATCH_VALID(x) ((x) << S_AOPEN_MAC_MATCH_VALID)
#घोषणा F_AOPEN_MAC_MATCH_VALID    V_AOPEN_MAC_MATCH_VALID(1U)

#घोषणा S_AOPEN_IFF_VLAN    20
#घोषणा M_AOPEN_IFF_VLAN    0xFFF
#घोषणा V_AOPEN_IFF_VLAN(x) ((x) << S_AOPEN_IFF_VLAN)
#घोषणा G_AOPEN_IFF_VLAN(x) (((x) >> S_AOPEN_IFF_VLAN) & M_AOPEN_IFF_VLAN)

काष्ठा cpl_act_खोलो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be32 atid;
	__u8 rsvd[3];
	__u8 status;
पूर्ण;

काष्ठा cpl_act_establish अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be32 tos_tid;
	__be16 l2t_idx;
	__be16 tcp_opt;
	__be32 snd_isn;
	__be32 rcv_isn;
पूर्ण;

काष्ठा cpl_get_tcb अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 cpuno;
	__be16 rsvd;
पूर्ण;

काष्ठा cpl_get_tcb_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 rsvd;
	__u8 status;
	__be16 len;
पूर्ण;

काष्ठा cpl_set_tcb अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 reply;
	__u8 cpu_idx;
	__be16 len;
पूर्ण;

/* cpl_set_tcb.reply fields */
#घोषणा S_NO_REPLY    7
#घोषणा V_NO_REPLY(x) ((x) << S_NO_REPLY)
#घोषणा F_NO_REPLY    V_NO_REPLY(1U)

काष्ठा cpl_set_tcb_field अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 reply;
	__u8 cpu_idx;
	__be16 word;
	__be64 mask;
	__be64 val;
पूर्ण;

काष्ठा cpl_set_tcb_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 rsvd[3];
	__u8 status;
पूर्ण;

काष्ठा cpl_pcmd अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 rsvd[3];
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 src:1;
	__u8 bundle:1;
	__u8 channel:1;
	 __u8:5;
#अन्यथा
	 __u8:5;
	__u8 channel:1;
	__u8 bundle:1;
	__u8 src:1;
#पूर्ण_अगर
	__be32 pcmd_parm[2];
पूर्ण;

काष्ठा cpl_pcmd_reply अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd;
	__be16 len;
पूर्ण;

काष्ठा cpl_बंद_con_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd;
पूर्ण;

काष्ठा cpl_बंद_con_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 rsvd[3];
	__u8 status;
	__be32 snd_nxt;
	__be32 rcv_nxt;
पूर्ण;

काष्ठा cpl_बंद_listserv_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 rsvd0;
	__u8 cpu_idx;
	__be16 rsvd1;
पूर्ण;

काष्ठा cpl_बंद_listserv_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 rsvd[3];
	__u8 status;
पूर्ण;

काष्ठा cpl_पात_req_rss अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 rsvd0;
	__u8 rsvd1;
	__u8 status;
	__u8 rsvd2[6];
पूर्ण;

काष्ठा cpl_पात_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd0;
	__u8 rsvd1;
	__u8 cmd;
	__u8 rsvd2[6];
पूर्ण;

काष्ठा cpl_पात_rpl_rss अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 rsvd0;
	__u8 rsvd1;
	__u8 status;
	__u8 rsvd2[6];
पूर्ण;

काष्ठा cpl_पात_rpl अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd0;
	__u8 rsvd1;
	__u8 cmd;
	__u8 rsvd2[6];
पूर्ण;

काष्ठा cpl_peer_बंद अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 rcv_nxt;
पूर्ण;

काष्ठा tx_data_wr अणु
	__be32 wr_hi;
	__be32 wr_lo;
	__be32 len;
	__be32 flags;
	__be32 sndseq;
	__be32 param;
पूर्ण;

/* tx_data_wr.flags fields */
#घोषणा S_TX_ACK_PAGES	21
#घोषणा M_TX_ACK_PAGES	0x7
#घोषणा V_TX_ACK_PAGES(x) ((x) << S_TX_ACK_PAGES)
#घोषणा G_TX_ACK_PAGES(x) (((x) >> S_TX_ACK_PAGES) & M_TX_ACK_PAGES)

/* tx_data_wr.param fields */
#घोषणा S_TX_PORT    0
#घोषणा M_TX_PORT    0x7
#घोषणा V_TX_PORT(x) ((x) << S_TX_PORT)
#घोषणा G_TX_PORT(x) (((x) >> S_TX_PORT) & M_TX_PORT)

#घोषणा S_TX_MSS    4
#घोषणा M_TX_MSS    0xF
#घोषणा V_TX_MSS(x) ((x) << S_TX_MSS)
#घोषणा G_TX_MSS(x) (((x) >> S_TX_MSS) & M_TX_MSS)

#घोषणा S_TX_QOS    8
#घोषणा M_TX_QOS    0xFF
#घोषणा V_TX_QOS(x) ((x) << S_TX_QOS)
#घोषणा G_TX_QOS(x) (((x) >> S_TX_QOS) & M_TX_QOS)

#घोषणा S_TX_SNDBUF 16
#घोषणा M_TX_SNDBUF 0xFFFF
#घोषणा V_TX_SNDBUF(x) ((x) << S_TX_SNDBUF)
#घोषणा G_TX_SNDBUF(x) (((x) >> S_TX_SNDBUF) & M_TX_SNDBUF)

काष्ठा cpl_tx_data अणु
	जोड़ opcode_tid ot;
	__be32 len;
	__be32 rsvd;
	__be16 urg;
	__be16 flags;
पूर्ण;

/* cpl_tx_data.flags fields */
#घोषणा S_TX_ULP_SUBMODE    6
#घोषणा M_TX_ULP_SUBMODE    0xF
#घोषणा V_TX_ULP_SUBMODE(x) ((x) << S_TX_ULP_SUBMODE)
#घोषणा G_TX_ULP_SUBMODE(x) (((x) >> S_TX_ULP_SUBMODE) & M_TX_ULP_SUBMODE)

#घोषणा S_TX_ULP_MODE    10
#घोषणा M_TX_ULP_MODE    0xF
#घोषणा V_TX_ULP_MODE(x) ((x) << S_TX_ULP_MODE)
#घोषणा G_TX_ULP_MODE(x) (((x) >> S_TX_ULP_MODE) & M_TX_ULP_MODE)

#घोषणा S_TX_SHOVE    14
#घोषणा V_TX_SHOVE(x) ((x) << S_TX_SHOVE)
#घोषणा F_TX_SHOVE    V_TX_SHOVE(1U)

#घोषणा S_TX_MORE    15
#घोषणा V_TX_MORE(x) ((x) << S_TX_MORE)
#घोषणा F_TX_MORE    V_TX_MORE(1U)

/* additional tx_data_wr.flags fields */
#घोषणा S_TX_CPU_IDX    0
#घोषणा M_TX_CPU_IDX    0x3F
#घोषणा V_TX_CPU_IDX(x) ((x) << S_TX_CPU_IDX)
#घोषणा G_TX_CPU_IDX(x) (((x) >> S_TX_CPU_IDX) & M_TX_CPU_IDX)

#घोषणा S_TX_URG    16
#घोषणा V_TX_URG(x) ((x) << S_TX_URG)
#घोषणा F_TX_URG    V_TX_URG(1U)

#घोषणा S_TX_CLOSE    17
#घोषणा V_TX_CLOSE(x) ((x) << S_TX_CLOSE)
#घोषणा F_TX_CLOSE    V_TX_CLOSE(1U)

#घोषणा S_TX_INIT    18
#घोषणा V_TX_INIT(x) ((x) << S_TX_INIT)
#घोषणा F_TX_INIT    V_TX_INIT(1U)

#घोषणा S_TX_IMM_ACK    19
#घोषणा V_TX_IMM_ACK(x) ((x) << S_TX_IMM_ACK)
#घोषणा F_TX_IMM_ACK    V_TX_IMM_ACK(1U)

#घोषणा S_TX_IMM_DMA    20
#घोषणा V_TX_IMM_DMA(x) ((x) << S_TX_IMM_DMA)
#घोषणा F_TX_IMM_DMA    V_TX_IMM_DMA(1U)

काष्ठा cpl_tx_data_ack अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 ack_seq;
पूर्ण;

काष्ठा cpl_wr_ack अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 credits;
	__be16 rsvd;
	__be32 snd_nxt;
	__be32 snd_una;
पूर्ण;

काष्ठा cpl_rdma_ec_status अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 rsvd[3];
	__u8 status;
पूर्ण;

काष्ठा mngt_pktsched_wr अणु
	__be32 wr_hi;
	__be32 wr_lo;
	__u8 mngt_opcode;
	__u8 rsvd[7];
	__u8 sched;
	__u8 idx;
	__u8 min;
	__u8 max;
	__u8 binding;
	__u8 rsvd1[3];
पूर्ण;

काष्ठा cpl_iscsi_hdr अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 pdu_len_ddp;
	__be16 len;
	__be32 seq;
	__be16 urg;
	__u8 rsvd;
	__u8 status;
पूर्ण;

/* cpl_iscsi_hdr.pdu_len_ddp fields */
#घोषणा S_ISCSI_PDU_LEN    0
#घोषणा M_ISCSI_PDU_LEN    0x7FFF
#घोषणा V_ISCSI_PDU_LEN(x) ((x) << S_ISCSI_PDU_LEN)
#घोषणा G_ISCSI_PDU_LEN(x) (((x) >> S_ISCSI_PDU_LEN) & M_ISCSI_PDU_LEN)

#घोषणा S_ISCSI_DDP    15
#घोषणा V_ISCSI_DDP(x) ((x) << S_ISCSI_DDP)
#घोषणा F_ISCSI_DDP    V_ISCSI_DDP(1U)

काष्ठा cpl_rx_data अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 rsvd;
	__be16 len;
	__be32 seq;
	__be16 urg;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 dack_mode:2;
	__u8 psh:1;
	__u8 heartbeat:1;
	 __u8:4;
#अन्यथा
	 __u8:4;
	__u8 heartbeat:1;
	__u8 psh:1;
	__u8 dack_mode:2;
#पूर्ण_अगर
	__u8 status;
पूर्ण;

काष्ठा cpl_rx_data_ack अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 credit_dack;
पूर्ण;

/* cpl_rx_data_ack.ack_seq fields */
#घोषणा S_RX_CREDITS    0
#घोषणा M_RX_CREDITS    0x7FFFFFF
#घोषणा V_RX_CREDITS(x) ((x) << S_RX_CREDITS)
#घोषणा G_RX_CREDITS(x) (((x) >> S_RX_CREDITS) & M_RX_CREDITS)

#घोषणा S_RX_MODULATE    27
#घोषणा V_RX_MODULATE(x) ((x) << S_RX_MODULATE)
#घोषणा F_RX_MODULATE    V_RX_MODULATE(1U)

#घोषणा S_RX_FORCE_ACK    28
#घोषणा V_RX_FORCE_ACK(x) ((x) << S_RX_FORCE_ACK)
#घोषणा F_RX_FORCE_ACK    V_RX_FORCE_ACK(1U)

#घोषणा S_RX_DACK_MODE    29
#घोषणा M_RX_DACK_MODE    0x3
#घोषणा V_RX_DACK_MODE(x) ((x) << S_RX_DACK_MODE)
#घोषणा G_RX_DACK_MODE(x) (((x) >> S_RX_DACK_MODE) & M_RX_DACK_MODE)

#घोषणा S_RX_DACK_CHANGE    31
#घोषणा V_RX_DACK_CHANGE(x) ((x) << S_RX_DACK_CHANGE)
#घोषणा F_RX_DACK_CHANGE    V_RX_DACK_CHANGE(1U)

काष्ठा cpl_rx_urg_notअगरy अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 seq;
पूर्ण;

काष्ठा cpl_rx_ddp_complete अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 ddp_report;
पूर्ण;

काष्ठा cpl_rx_data_ddp अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be16 urg;
	__be16 len;
	__be32 seq;
	जोड़ अणु
		__be32 nxt_seq;
		__be32 ddp_report;
	पूर्ण;
	__be32 ulp_crc;
	__be32 ddpvld_status;
पूर्ण;

/* cpl_rx_data_ddp.ddpvld_status fields */
#घोषणा S_DDP_STATUS    0
#घोषणा M_DDP_STATUS    0xFF
#घोषणा V_DDP_STATUS(x) ((x) << S_DDP_STATUS)
#घोषणा G_DDP_STATUS(x) (((x) >> S_DDP_STATUS) & M_DDP_STATUS)

#घोषणा S_DDP_VALID    15
#घोषणा M_DDP_VALID    0x1FFFF
#घोषणा V_DDP_VALID(x) ((x) << S_DDP_VALID)
#घोषणा G_DDP_VALID(x) (((x) >> S_DDP_VALID) & M_DDP_VALID)

#घोषणा S_DDP_PPOD_MISMATCH    15
#घोषणा V_DDP_PPOD_MISMATCH(x) ((x) << S_DDP_PPOD_MISMATCH)
#घोषणा F_DDP_PPOD_MISMATCH    V_DDP_PPOD_MISMATCH(1U)

#घोषणा S_DDP_PDU    16
#घोषणा V_DDP_PDU(x) ((x) << S_DDP_PDU)
#घोषणा F_DDP_PDU    V_DDP_PDU(1U)

#घोषणा S_DDP_LLIMIT_ERR    17
#घोषणा V_DDP_LLIMIT_ERR(x) ((x) << S_DDP_LLIMIT_ERR)
#घोषणा F_DDP_LLIMIT_ERR    V_DDP_LLIMIT_ERR(1U)

#घोषणा S_DDP_PPOD_PARITY_ERR    18
#घोषणा V_DDP_PPOD_PARITY_ERR(x) ((x) << S_DDP_PPOD_PARITY_ERR)
#घोषणा F_DDP_PPOD_PARITY_ERR    V_DDP_PPOD_PARITY_ERR(1U)

#घोषणा S_DDP_PADDING_ERR    19
#घोषणा V_DDP_PADDING_ERR(x) ((x) << S_DDP_PADDING_ERR)
#घोषणा F_DDP_PADDING_ERR    V_DDP_PADDING_ERR(1U)

#घोषणा S_DDP_HDRCRC_ERR    20
#घोषणा V_DDP_HDRCRC_ERR(x) ((x) << S_DDP_HDRCRC_ERR)
#घोषणा F_DDP_HDRCRC_ERR    V_DDP_HDRCRC_ERR(1U)

#घोषणा S_DDP_DATACRC_ERR    21
#घोषणा V_DDP_DATACRC_ERR(x) ((x) << S_DDP_DATACRC_ERR)
#घोषणा F_DDP_DATACRC_ERR    V_DDP_DATACRC_ERR(1U)

#घोषणा S_DDP_INVALID_TAG    22
#घोषणा V_DDP_INVALID_TAG(x) ((x) << S_DDP_INVALID_TAG)
#घोषणा F_DDP_INVALID_TAG    V_DDP_INVALID_TAG(1U)

#घोषणा S_DDP_ULIMIT_ERR    23
#घोषणा V_DDP_ULIMIT_ERR(x) ((x) << S_DDP_ULIMIT_ERR)
#घोषणा F_DDP_ULIMIT_ERR    V_DDP_ULIMIT_ERR(1U)

#घोषणा S_DDP_OFFSET_ERR    24
#घोषणा V_DDP_OFFSET_ERR(x) ((x) << S_DDP_OFFSET_ERR)
#घोषणा F_DDP_OFFSET_ERR    V_DDP_OFFSET_ERR(1U)

#घोषणा S_DDP_COLOR_ERR    25
#घोषणा V_DDP_COLOR_ERR(x) ((x) << S_DDP_COLOR_ERR)
#घोषणा F_DDP_COLOR_ERR    V_DDP_COLOR_ERR(1U)

#घोषणा S_DDP_TID_MISMATCH    26
#घोषणा V_DDP_TID_MISMATCH(x) ((x) << S_DDP_TID_MISMATCH)
#घोषणा F_DDP_TID_MISMATCH    V_DDP_TID_MISMATCH(1U)

#घोषणा S_DDP_INVALID_PPOD    27
#घोषणा V_DDP_INVALID_PPOD(x) ((x) << S_DDP_INVALID_PPOD)
#घोषणा F_DDP_INVALID_PPOD    V_DDP_INVALID_PPOD(1U)

#घोषणा S_DDP_ULP_MODE    28
#घोषणा M_DDP_ULP_MODE    0xF
#घोषणा V_DDP_ULP_MODE(x) ((x) << S_DDP_ULP_MODE)
#घोषणा G_DDP_ULP_MODE(x) (((x) >> S_DDP_ULP_MODE) & M_DDP_ULP_MODE)

/* cpl_rx_data_ddp.ddp_report fields */
#घोषणा S_DDP_OFFSET    0
#घोषणा M_DDP_OFFSET    0x3FFFFF
#घोषणा V_DDP_OFFSET(x) ((x) << S_DDP_OFFSET)
#घोषणा G_DDP_OFFSET(x) (((x) >> S_DDP_OFFSET) & M_DDP_OFFSET)

#घोषणा S_DDP_URG    24
#घोषणा V_DDP_URG(x) ((x) << S_DDP_URG)
#घोषणा F_DDP_URG    V_DDP_URG(1U)

#घोषणा S_DDP_PSH    25
#घोषणा V_DDP_PSH(x) ((x) << S_DDP_PSH)
#घोषणा F_DDP_PSH    V_DDP_PSH(1U)

#घोषणा S_DDP_BUF_COMPLETE    26
#घोषणा V_DDP_BUF_COMPLETE(x) ((x) << S_DDP_BUF_COMPLETE)
#घोषणा F_DDP_BUF_COMPLETE    V_DDP_BUF_COMPLETE(1U)

#घोषणा S_DDP_BUF_TIMED_OUT    27
#घोषणा V_DDP_BUF_TIMED_OUT(x) ((x) << S_DDP_BUF_TIMED_OUT)
#घोषणा F_DDP_BUF_TIMED_OUT    V_DDP_BUF_TIMED_OUT(1U)

#घोषणा S_DDP_BUF_IDX    28
#घोषणा V_DDP_BUF_IDX(x) ((x) << S_DDP_BUF_IDX)
#घोषणा F_DDP_BUF_IDX    V_DDP_BUF_IDX(1U)

काष्ठा cpl_tx_pkt अणु
	WR_HDR;
	__be32 cntrl;
	__be32 len;
पूर्ण;

काष्ठा cpl_tx_pkt_lso अणु
	WR_HDR;
	__be32 cntrl;
	__be32 len;

	__be32 rsvd;
	__be32 lso_info;
पूर्ण;

/* cpl_tx_pkt*.cntrl fields */
#घोषणा S_TXPKT_VLAN    0
#घोषणा M_TXPKT_VLAN    0xFFFF
#घोषणा V_TXPKT_VLAN(x) ((x) << S_TXPKT_VLAN)
#घोषणा G_TXPKT_VLAN(x) (((x) >> S_TXPKT_VLAN) & M_TXPKT_VLAN)

#घोषणा S_TXPKT_INTF    16
#घोषणा M_TXPKT_INTF    0xF
#घोषणा V_TXPKT_INTF(x) ((x) << S_TXPKT_INTF)
#घोषणा G_TXPKT_INTF(x) (((x) >> S_TXPKT_INTF) & M_TXPKT_INTF)

#घोषणा S_TXPKT_IPCSUM_DIS    20
#घोषणा V_TXPKT_IPCSUM_DIS(x) ((x) << S_TXPKT_IPCSUM_DIS)
#घोषणा F_TXPKT_IPCSUM_DIS    V_TXPKT_IPCSUM_DIS(1U)

#घोषणा S_TXPKT_L4CSUM_DIS    21
#घोषणा V_TXPKT_L4CSUM_DIS(x) ((x) << S_TXPKT_L4CSUM_DIS)
#घोषणा F_TXPKT_L4CSUM_DIS    V_TXPKT_L4CSUM_DIS(1U)

#घोषणा S_TXPKT_VLAN_VLD    22
#घोषणा V_TXPKT_VLAN_VLD(x) ((x) << S_TXPKT_VLAN_VLD)
#घोषणा F_TXPKT_VLAN_VLD    V_TXPKT_VLAN_VLD(1U)

#घोषणा S_TXPKT_LOOPBACK    23
#घोषणा V_TXPKT_LOOPBACK(x) ((x) << S_TXPKT_LOOPBACK)
#घोषणा F_TXPKT_LOOPBACK    V_TXPKT_LOOPBACK(1U)

#घोषणा S_TXPKT_OPCODE    24
#घोषणा M_TXPKT_OPCODE    0xFF
#घोषणा V_TXPKT_OPCODE(x) ((x) << S_TXPKT_OPCODE)
#घोषणा G_TXPKT_OPCODE(x) (((x) >> S_TXPKT_OPCODE) & M_TXPKT_OPCODE)

/* cpl_tx_pkt_lso.lso_info fields */
#घोषणा S_LSO_MSS    0
#घोषणा M_LSO_MSS    0x3FFF
#घोषणा V_LSO_MSS(x) ((x) << S_LSO_MSS)
#घोषणा G_LSO_MSS(x) (((x) >> S_LSO_MSS) & M_LSO_MSS)

#घोषणा S_LSO_ETH_TYPE    14
#घोषणा M_LSO_ETH_TYPE    0x3
#घोषणा V_LSO_ETH_TYPE(x) ((x) << S_LSO_ETH_TYPE)
#घोषणा G_LSO_ETH_TYPE(x) (((x) >> S_LSO_ETH_TYPE) & M_LSO_ETH_TYPE)

#घोषणा S_LSO_TCPHDR_WORDS    16
#घोषणा M_LSO_TCPHDR_WORDS    0xF
#घोषणा V_LSO_TCPHDR_WORDS(x) ((x) << S_LSO_TCPHDR_WORDS)
#घोषणा G_LSO_TCPHDR_WORDS(x) (((x) >> S_LSO_TCPHDR_WORDS) & M_LSO_TCPHDR_WORDS)

#घोषणा S_LSO_IPHDR_WORDS    20
#घोषणा M_LSO_IPHDR_WORDS    0xF
#घोषणा V_LSO_IPHDR_WORDS(x) ((x) << S_LSO_IPHDR_WORDS)
#घोषणा G_LSO_IPHDR_WORDS(x) (((x) >> S_LSO_IPHDR_WORDS) & M_LSO_IPHDR_WORDS)

#घोषणा S_LSO_IPV6    24
#घोषणा V_LSO_IPV6(x) ((x) << S_LSO_IPV6)
#घोषणा F_LSO_IPV6    V_LSO_IPV6(1U)

काष्ठा cpl_trace_pkt अणु
#अगर_घोषित CHELSIO_FW
	__u8 rss_opcode;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 err:1;
	 __u8:7;
#अन्यथा
	 __u8:7;
	__u8 err:1;
#पूर्ण_अगर
	__u8 rsvd0;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 qid:4;
	 __u8:4;
#अन्यथा
	 __u8:4;
	__u8 qid:4;
#पूर्ण_अगर
	__be32 tstamp;
#पूर्ण_अगर				/* CHELSIO_FW */

	__u8 opcode;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 अगरf:4;
	 __u8:4;
#अन्यथा
	 __u8:4;
	__u8 अगरf:4;
#पूर्ण_अगर
	__u8 rsvd[4];
	__be16 len;
पूर्ण;

काष्ठा cpl_rx_pkt अणु
	RSS_HDR __u8 opcode;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 अगरf:4;
	__u8 csum_valid:1;
	__u8 ipmi_pkt:1;
	__u8 vlan_valid:1;
	__u8 fragment:1;
#अन्यथा
	__u8 fragment:1;
	__u8 vlan_valid:1;
	__u8 ipmi_pkt:1;
	__u8 csum_valid:1;
	__u8 अगरf:4;
#पूर्ण_अगर
	__be16 csum;
	__be16 vlan;
	__be16 len;
पूर्ण;

काष्ठा cpl_l2t_ग_लिखो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 params;
	__u8 rsvd[2];
	__u8 dst_mac[6];
पूर्ण;

/* cpl_l2t_ग_लिखो_req.params fields */
#घोषणा S_L2T_W_IDX    0
#घोषणा M_L2T_W_IDX    0x7FF
#घोषणा V_L2T_W_IDX(x) ((x) << S_L2T_W_IDX)
#घोषणा G_L2T_W_IDX(x) (((x) >> S_L2T_W_IDX) & M_L2T_W_IDX)

#घोषणा S_L2T_W_VLAN    11
#घोषणा M_L2T_W_VLAN    0xFFF
#घोषणा V_L2T_W_VLAN(x) ((x) << S_L2T_W_VLAN)
#घोषणा G_L2T_W_VLAN(x) (((x) >> S_L2T_W_VLAN) & M_L2T_W_VLAN)

#घोषणा S_L2T_W_IFF    23
#घोषणा M_L2T_W_IFF    0xF
#घोषणा V_L2T_W_IFF(x) ((x) << S_L2T_W_IFF)
#घोषणा G_L2T_W_IFF(x) (((x) >> S_L2T_W_IFF) & M_L2T_W_IFF)

#घोषणा S_L2T_W_PRIO    27
#घोषणा M_L2T_W_PRIO    0x7
#घोषणा V_L2T_W_PRIO(x) ((x) << S_L2T_W_PRIO)
#घोषणा G_L2T_W_PRIO(x) (((x) >> S_L2T_W_PRIO) & M_L2T_W_PRIO)

काष्ठा cpl_l2t_ग_लिखो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd[3];
पूर्ण;

काष्ठा cpl_l2t_पढ़ो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 rsvd;
	__be16 l2t_idx;
पूर्ण;

काष्ठा cpl_l2t_पढ़ो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__be32 params;
	__u8 rsvd[2];
	__u8 dst_mac[6];
पूर्ण;

/* cpl_l2t_पढ़ो_rpl.params fields */
#घोषणा S_L2T_R_PRIO    0
#घोषणा M_L2T_R_PRIO    0x7
#घोषणा V_L2T_R_PRIO(x) ((x) << S_L2T_R_PRIO)
#घोषणा G_L2T_R_PRIO(x) (((x) >> S_L2T_R_PRIO) & M_L2T_R_PRIO)

#घोषणा S_L2T_R_VLAN    8
#घोषणा M_L2T_R_VLAN    0xFFF
#घोषणा V_L2T_R_VLAN(x) ((x) << S_L2T_R_VLAN)
#घोषणा G_L2T_R_VLAN(x) (((x) >> S_L2T_R_VLAN) & M_L2T_R_VLAN)

#घोषणा S_L2T_R_IFF    20
#घोषणा M_L2T_R_IFF    0xF
#घोषणा V_L2T_R_IFF(x) ((x) << S_L2T_R_IFF)
#घोषणा G_L2T_R_IFF(x) (((x) >> S_L2T_R_IFF) & M_L2T_R_IFF)

#घोषणा S_L2T_STATUS    24
#घोषणा M_L2T_STATUS    0xFF
#घोषणा V_L2T_STATUS(x) ((x) << S_L2T_STATUS)
#घोषणा G_L2T_STATUS(x) (((x) >> S_L2T_STATUS) & M_L2T_STATUS)

काष्ठा cpl_smt_ग_लिखो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 rsvd0;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 mtu_idx:4;
	__u8 अगरf:4;
#अन्यथा
	__u8 अगरf:4;
	__u8 mtu_idx:4;
#पूर्ण_अगर
	__be16 rsvd2;
	__be16 rsvd3;
	__u8 src_mac1[6];
	__be16 rsvd4;
	__u8 src_mac0[6];
पूर्ण;

काष्ठा cpl_smt_ग_लिखो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd[3];
पूर्ण;

काष्ठा cpl_smt_पढ़ो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 rsvd0;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	 __u8:4;
	__u8 अगरf:4;
#अन्यथा
	__u8 अगरf:4;
	 __u8:4;
#पूर्ण_अगर
	__be16 rsvd2;
पूर्ण;

काष्ठा cpl_smt_पढ़ो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 mtu_idx:4;
	 __u8:4;
#अन्यथा
	 __u8:4;
	__u8 mtu_idx:4;
#पूर्ण_अगर
	__be16 rsvd2;
	__be16 rsvd3;
	__u8 src_mac1[6];
	__be16 rsvd4;
	__u8 src_mac0[6];
पूर्ण;

काष्ठा cpl_rte_delete_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 params;
पूर्ण;

/* अणु cpl_rte_delete_req, cpl_rte_पढ़ो_req पूर्ण.params fields */
#घोषणा S_RTE_REQ_LUT_IX    8
#घोषणा M_RTE_REQ_LUT_IX    0x7FF
#घोषणा V_RTE_REQ_LUT_IX(x) ((x) << S_RTE_REQ_LUT_IX)
#घोषणा G_RTE_REQ_LUT_IX(x) (((x) >> S_RTE_REQ_LUT_IX) & M_RTE_REQ_LUT_IX)

#घोषणा S_RTE_REQ_LUT_BASE    19
#घोषणा M_RTE_REQ_LUT_BASE    0x7FF
#घोषणा V_RTE_REQ_LUT_BASE(x) ((x) << S_RTE_REQ_LUT_BASE)
#घोषणा G_RTE_REQ_LUT_BASE(x) (((x) >> S_RTE_REQ_LUT_BASE) & M_RTE_REQ_LUT_BASE)

#घोषणा S_RTE_READ_REQ_SELECT    31
#घोषणा V_RTE_READ_REQ_SELECT(x) ((x) << S_RTE_READ_REQ_SELECT)
#घोषणा F_RTE_READ_REQ_SELECT    V_RTE_READ_REQ_SELECT(1U)

काष्ठा cpl_rte_delete_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd[3];
पूर्ण;

काष्ठा cpl_rte_ग_लिखो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	 __u8:6;
	__u8 ग_लिखो_tcam:1;
	__u8 ग_लिखो_l2t_lut:1;
#अन्यथा
	__u8 ग_लिखो_l2t_lut:1;
	__u8 ग_लिखो_tcam:1;
	 __u8:6;
#पूर्ण_अगर
	__u8 rsvd[3];
	__be32 lut_params;
	__be16 rsvd2;
	__be16 l2t_idx;
	__be32 neपंचांगask;
	__be32 faddr;
पूर्ण;

/* cpl_rte_ग_लिखो_req.lut_params fields */
#घोषणा S_RTE_WRITE_REQ_LUT_IX    10
#घोषणा M_RTE_WRITE_REQ_LUT_IX    0x7FF
#घोषणा V_RTE_WRITE_REQ_LUT_IX(x) ((x) << S_RTE_WRITE_REQ_LUT_IX)
#घोषणा G_RTE_WRITE_REQ_LUT_IX(x) (((x) >> S_RTE_WRITE_REQ_LUT_IX) & M_RTE_WRITE_REQ_LUT_IX)

#घोषणा S_RTE_WRITE_REQ_LUT_BASE    21
#घोषणा M_RTE_WRITE_REQ_LUT_BASE    0x7FF
#घोषणा V_RTE_WRITE_REQ_LUT_BASE(x) ((x) << S_RTE_WRITE_REQ_LUT_BASE)
#घोषणा G_RTE_WRITE_REQ_LUT_BASE(x) (((x) >> S_RTE_WRITE_REQ_LUT_BASE) & M_RTE_WRITE_REQ_LUT_BASE)

काष्ठा cpl_rte_ग_लिखो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd[3];
पूर्ण;

काष्ठा cpl_rte_पढ़ो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 params;
पूर्ण;

काष्ठा cpl_rte_पढ़ो_rpl अणु
	RSS_HDR जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd0;
	__be16 l2t_idx;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	 __u8:7;
	__u8 select:1;
#अन्यथा
	__u8 select:1;
	 __u8:7;
#पूर्ण_अगर
	__u8 rsvd2[3];
	__be32 addr;
पूर्ण;

काष्ठा cpl_tid_release अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd;
पूर्ण;

काष्ठा cpl_barrier अणु
	WR_HDR;
	__u8 opcode;
	__u8 rsvd[7];
पूर्ण;

काष्ठा cpl_rdma_पढ़ो_req अणु
	__u8 opcode;
	__u8 rsvd[15];
पूर्ण;

काष्ठा cpl_rdma_terminate अणु
#अगर_घोषित CHELSIO_FW
	__u8 opcode;
	__u8 rsvd[2];
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 rspq:3;
	 __u8:5;
#अन्यथा
	 __u8:5;
	__u8 rspq:3;
#पूर्ण_अगर
	__be32 tid_len;
#पूर्ण_अगर
	__be32 msn;
	__be32 mo;
	__u8 data[];
पूर्ण;

/* cpl_rdma_terminate.tid_len fields */
#घोषणा S_FLIT_CNT    0
#घोषणा M_FLIT_CNT    0xFF
#घोषणा V_FLIT_CNT(x) ((x) << S_FLIT_CNT)
#घोषणा G_FLIT_CNT(x) (((x) >> S_FLIT_CNT) & M_FLIT_CNT)

#घोषणा S_TERM_TID    8
#घोषणा M_TERM_TID    0xFFFFF
#घोषणा V_TERM_TID(x) ((x) << S_TERM_TID)
#घोषणा G_TERM_TID(x) (((x) >> S_TERM_TID) & M_TERM_TID)

/* ULP_TX opcodes */
क्रमागत अणु ULP_MEM_READ = 2, ULP_MEM_WRITE = 3, ULP_TXPKT = 4 पूर्ण;

#घोषणा S_ULPTX_CMD	28
#घोषणा M_ULPTX_CMD	0xF
#घोषणा V_ULPTX_CMD(x)	((x) << S_ULPTX_CMD)

#घोषणा S_ULPTX_NFLITS	0
#घोषणा M_ULPTX_NFLITS	0xFF
#घोषणा V_ULPTX_NFLITS(x) ((x) << S_ULPTX_NFLITS)

काष्ठा ulp_mem_io अणु
	WR_HDR;
	__be32 cmd_lock_addr;
	__be32 len;
पूर्ण;

/* ulp_mem_io.cmd_lock_addr fields */
#घोषणा S_ULP_MEMIO_ADDR	0
#घोषणा M_ULP_MEMIO_ADDR	0x7FFFFFF
#घोषणा V_ULP_MEMIO_ADDR(x)	((x) << S_ULP_MEMIO_ADDR)
#घोषणा S_ULP_MEMIO_LOCK	27
#घोषणा V_ULP_MEMIO_LOCK(x)	((x) << S_ULP_MEMIO_LOCK)
#घोषणा F_ULP_MEMIO_LOCK	V_ULP_MEMIO_LOCK(1U)

/* ulp_mem_io.len fields */
#घोषणा S_ULP_MEMIO_DATA_LEN	28
#घोषणा M_ULP_MEMIO_DATA_LEN	0xF
#घोषणा V_ULP_MEMIO_DATA_LEN(x)	((x) << S_ULP_MEMIO_DATA_LEN)

#पूर्ण_अगर				/* T3_CPL_H */
