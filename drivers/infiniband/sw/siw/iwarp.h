<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#अगर_अघोषित _IWARP_H
#घोषणा _IWARP_H

#समावेश <rdma/rdma_user_cm.h> /* RDMA_MAX_PRIVATE_DATA */
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा RDMAP_VERSION 1
#घोषणा DDP_VERSION 1
#घोषणा MPA_REVISION_1 1
#घोषणा MPA_REVISION_2 2
#घोषणा MPA_MAX_PRIVDATA RDMA_MAX_PRIVATE_DATA
#घोषणा MPA_KEY_REQ "MPA ID Req Frame"
#घोषणा MPA_KEY_REP "MPA ID Rep Frame"
#घोषणा MPA_IRD_ORD_MASK 0x3fff

काष्ठा mpa_rr_params अणु
	__be16 bits;
	__be16 pd_len;
पूर्ण;

/*
 * MPA request/response header bits & fields
 */
क्रमागत अणु
	MPA_RR_FLAG_MARKERS = cpu_to_be16(0x8000),
	MPA_RR_FLAG_CRC = cpu_to_be16(0x4000),
	MPA_RR_FLAG_REJECT = cpu_to_be16(0x2000),
	MPA_RR_FLAG_ENHANCED = cpu_to_be16(0x1000),
	MPA_RR_FLAG_GSO_EXP = cpu_to_be16(0x0800),
	MPA_RR_MASK_REVISION = cpu_to_be16(0x00ff)
पूर्ण;

/*
 * MPA request/reply header
 */
काष्ठा mpa_rr अणु
	__u8 key[16];
	काष्ठा mpa_rr_params params;
पूर्ण;

अटल अंतरभूत व्योम __mpa_rr_set_revision(__be16 *bits, u8 rev)
अणु
	*bits = (*bits & ~MPA_RR_MASK_REVISION) |
		(cpu_to_be16(rev) & MPA_RR_MASK_REVISION);
पूर्ण

अटल अंतरभूत u8 __mpa_rr_revision(__be16 mpa_rr_bits)
अणु
	__be16 rev = mpa_rr_bits & MPA_RR_MASK_REVISION;

	वापस be16_to_cpu(rev);
पूर्ण

क्रमागत mpa_v2_ctrl अणु
	MPA_V2_PEER_TO_PEER = cpu_to_be16(0x8000),
	MPA_V2_ZERO_LENGTH_RTR = cpu_to_be16(0x4000),
	MPA_V2_RDMA_WRITE_RTR = cpu_to_be16(0x8000),
	MPA_V2_RDMA_READ_RTR = cpu_to_be16(0x4000),
	MPA_V2_RDMA_NO_RTR = cpu_to_be16(0x0000),
	MPA_V2_MASK_IRD_ORD = cpu_to_be16(0x3fff)
पूर्ण;

काष्ठा mpa_v2_data अणु
	__be16 ird;
	__be16 ord;
पूर्ण;

काष्ठा mpa_marker अणु
	__be16 rsvd;
	__be16 fpdu_hmd; /* FPDU header-marker distance (= MPA's FPDUPTR) */
पूर्ण;

/*
 * maximum MPA trailer
 */
काष्ठा mpa_trailer अणु
	__u8 pad[4];
	__be32 crc;
पूर्ण;

#घोषणा MPA_HDR_SIZE 2
#घोषणा MPA_CRC_SIZE 4

/*
 * Common portion of iWARP headers (MPA, DDP, RDMAP)
 * क्रम any FPDU
 */
काष्ठा iwarp_ctrl अणु
	__be16 mpa_len;
	__be16 ddp_rdmap_ctrl;
पूर्ण;

/*
 * DDP/RDMAP Hdr bits & fields
 */
क्रमागत अणु
	DDP_FLAG_TAGGED = cpu_to_be16(0x8000),
	DDP_FLAG_LAST = cpu_to_be16(0x4000),
	DDP_MASK_RESERVED = cpu_to_be16(0x3C00),
	DDP_MASK_VERSION = cpu_to_be16(0x0300),
	RDMAP_MASK_VERSION = cpu_to_be16(0x00C0),
	RDMAP_MASK_RESERVED = cpu_to_be16(0x0030),
	RDMAP_MASK_OPCODE = cpu_to_be16(0x000f)
पूर्ण;

अटल अंतरभूत u8 __ddp_get_version(काष्ठा iwarp_ctrl *ctrl)
अणु
	वापस be16_to_cpu(ctrl->ddp_rdmap_ctrl & DDP_MASK_VERSION) >> 8;
पूर्ण

अटल अंतरभूत u8 __rdmap_get_version(काष्ठा iwarp_ctrl *ctrl)
अणु
	__be16 ver = ctrl->ddp_rdmap_ctrl & RDMAP_MASK_VERSION;

	वापस be16_to_cpu(ver) >> 6;
पूर्ण

अटल अंतरभूत u8 __rdmap_get_opcode(काष्ठा iwarp_ctrl *ctrl)
अणु
	वापस be16_to_cpu(ctrl->ddp_rdmap_ctrl & RDMAP_MASK_OPCODE);
पूर्ण

अटल अंतरभूत व्योम __rdmap_set_opcode(काष्ठा iwarp_ctrl *ctrl, u8 opcode)
अणु
	ctrl->ddp_rdmap_ctrl = (ctrl->ddp_rdmap_ctrl & ~RDMAP_MASK_OPCODE) |
			       (cpu_to_be16(opcode) & RDMAP_MASK_OPCODE);
पूर्ण

काष्ठा iwarp_rdma_ग_लिखो अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 sink_stag;
	__be64 sink_to;
पूर्ण;

काष्ठा iwarp_rdma_rreq अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 rsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
	__be32 sink_stag;
	__be64 sink_to;
	__be32 पढ़ो_size;
	__be32 source_stag;
	__be64 source_to;
पूर्ण;

काष्ठा iwarp_rdma_rresp अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 sink_stag;
	__be64 sink_to;
पूर्ण;

काष्ठा iwarp_send अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 rsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
पूर्ण;

काष्ठा iwarp_send_inv अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 inval_stag;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
पूर्ण;

काष्ठा iwarp_terminate अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 rsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__be32 layer : 4;
	__be32 etype : 4;
	__be32 ecode : 8;
	__be32 flag_m : 1;
	__be32 flag_d : 1;
	__be32 flag_r : 1;
	__be32 reserved : 13;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__be32 reserved : 13;
	__be32 flag_r : 1;
	__be32 flag_d : 1;
	__be32 flag_m : 1;
	__be32 ecode : 8;
	__be32 etype : 4;
	__be32 layer : 4;
#अन्यथा
#त्रुटि "undefined byte order"
#पूर्ण_अगर
पूर्ण;

/*
 * Terminate Hdr bits & fields
 */
क्रमागत अणु
	TERM_MASK_LAYER = cpu_to_be32(0xf0000000),
	TERM_MASK_ETYPE = cpu_to_be32(0x0f000000),
	TERM_MASK_ECODE = cpu_to_be32(0x00ff0000),
	TERM_FLAG_M = cpu_to_be32(0x00008000),
	TERM_FLAG_D = cpu_to_be32(0x00004000),
	TERM_FLAG_R = cpu_to_be32(0x00002000),
	TERM_MASK_RESVD = cpu_to_be32(0x00001fff)
पूर्ण;

अटल अंतरभूत u8 __rdmap_term_layer(काष्ठा iwarp_terminate *term)
अणु
	वापस term->layer;
पूर्ण

अटल अंतरभूत व्योम __rdmap_term_set_layer(काष्ठा iwarp_terminate *term,
					  u8 layer)
अणु
	term->layer = layer & 0xf;
पूर्ण

अटल अंतरभूत u8 __rdmap_term_etype(काष्ठा iwarp_terminate *term)
अणु
	वापस term->etype;
पूर्ण

अटल अंतरभूत व्योम __rdmap_term_set_etype(काष्ठा iwarp_terminate *term,
					  u8 etype)
अणु
	term->etype = etype & 0xf;
पूर्ण

अटल अंतरभूत u8 __rdmap_term_ecode(काष्ठा iwarp_terminate *term)
अणु
	वापस term->ecode;
पूर्ण

अटल अंतरभूत व्योम __rdmap_term_set_ecode(काष्ठा iwarp_terminate *term,
					  u8 ecode)
अणु
	term->ecode = ecode;
पूर्ण

/*
 * Common portion of iWARP headers (MPA, DDP, RDMAP)
 * क्रम an FPDU carrying an untagged DDP segment
 */
काष्ठा iwarp_ctrl_untagged अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 rsvd;
	__be32 ddp_qn;
	__be32 ddp_msn;
	__be32 ddp_mo;
पूर्ण;

/*
 * Common portion of iWARP headers (MPA, DDP, RDMAP)
 * क्रम an FPDU carrying a tagged DDP segment
 */
काष्ठा iwarp_ctrl_tagged अणु
	काष्ठा iwarp_ctrl ctrl;
	__be32 ddp_stag;
	__be64 ddp_to;
पूर्ण;

जोड़ iwarp_hdr अणु
	काष्ठा iwarp_ctrl ctrl;
	काष्ठा iwarp_ctrl_untagged c_untagged;
	काष्ठा iwarp_ctrl_tagged c_tagged;
	काष्ठा iwarp_rdma_ग_लिखो rग_लिखो;
	काष्ठा iwarp_rdma_rreq rreq;
	काष्ठा iwarp_rdma_rresp rresp;
	काष्ठा iwarp_terminate terminate;
	काष्ठा iwarp_send send;
	काष्ठा iwarp_send_inv send_inv;
पूर्ण;

क्रमागत term_elayer अणु
	TERM_ERROR_LAYER_RDMAP = 0x00,
	TERM_ERROR_LAYER_DDP = 0x01,
	TERM_ERROR_LAYER_LLP = 0x02 /* eg., MPA */
पूर्ण;

क्रमागत ddp_etype अणु
	DDP_ETYPE_CATASTROPHIC = 0x0,
	DDP_ETYPE_TAGGED_BUF = 0x1,
	DDP_ETYPE_UNTAGGED_BUF = 0x2,
	DDP_ETYPE_RSVD = 0x3
पूर्ण;

क्रमागत ddp_ecode अणु
	/* unspecअगरied, set to zero */
	DDP_ECODE_CATASTROPHIC = 0x00,
	/* Tagged Buffer Errors */
	DDP_ECODE_T_INVALID_STAG = 0x00,
	DDP_ECODE_T_BASE_BOUNDS = 0x01,
	DDP_ECODE_T_STAG_NOT_ASSOC = 0x02,
	DDP_ECODE_T_TO_WRAP = 0x03,
	DDP_ECODE_T_VERSION = 0x04,
	/* Untagged Buffer Errors */
	DDP_ECODE_UT_INVALID_QN = 0x01,
	DDP_ECODE_UT_INVALID_MSN_NOBUF = 0x02,
	DDP_ECODE_UT_INVALID_MSN_RANGE = 0x03,
	DDP_ECODE_UT_INVALID_MO = 0x04,
	DDP_ECODE_UT_MSG_TOOLONG = 0x05,
	DDP_ECODE_UT_VERSION = 0x06
पूर्ण;

क्रमागत rdmap_untagged_qn अणु
	RDMAP_UNTAGGED_QN_SEND = 0,
	RDMAP_UNTAGGED_QN_RDMA_READ = 1,
	RDMAP_UNTAGGED_QN_TERMINATE = 2,
	RDMAP_UNTAGGED_QN_COUNT = 3
पूर्ण;

क्रमागत rdmap_etype अणु
	RDMAP_ETYPE_CATASTROPHIC = 0x0,
	RDMAP_ETYPE_REMOTE_PROTECTION = 0x1,
	RDMAP_ETYPE_REMOTE_OPERATION = 0x2
पूर्ण;

क्रमागत rdmap_ecode अणु
	RDMAP_ECODE_INVALID_STAG = 0x00,
	RDMAP_ECODE_BASE_BOUNDS = 0x01,
	RDMAP_ECODE_ACCESS_RIGHTS = 0x02,
	RDMAP_ECODE_STAG_NOT_ASSOC = 0x03,
	RDMAP_ECODE_TO_WRAP = 0x04,
	RDMAP_ECODE_VERSION = 0x05,
	RDMAP_ECODE_OPCODE = 0x06,
	RDMAP_ECODE_CATASTROPHIC_STREAM = 0x07,
	RDMAP_ECODE_CATASTROPHIC_GLOBAL = 0x08,
	RDMAP_ECODE_CANNOT_INVALIDATE = 0x09,
	RDMAP_ECODE_UNSPECIFIED = 0xff
पूर्ण;

क्रमागत llp_ecode अणु
	LLP_ECODE_TCP_STREAM_LOST = 0x01, /* How to transfer this ?? */
	LLP_ECODE_RECEIVED_CRC = 0x02,
	LLP_ECODE_FPDU_START = 0x03,
	LLP_ECODE_INVALID_REQ_RESP = 0x04,

	/* Errors क्रम Enhanced Connection Establishment only */
	LLP_ECODE_LOCAL_CATASTROPHIC = 0x05,
	LLP_ECODE_INSUFFICIENT_IRD = 0x06,
	LLP_ECODE_NO_MATCHING_RTR = 0x07
पूर्ण;

क्रमागत llp_etype अणु LLP_ETYPE_MPA = 0x00 पूर्ण;

क्रमागत rdma_opcode अणु
	RDMAP_RDMA_WRITE = 0x0,
	RDMAP_RDMA_READ_REQ = 0x1,
	RDMAP_RDMA_READ_RESP = 0x2,
	RDMAP_SEND = 0x3,
	RDMAP_SEND_INVAL = 0x4,
	RDMAP_SEND_SE = 0x5,
	RDMAP_SEND_SE_INVAL = 0x6,
	RDMAP_TERMINATE = 0x7,
	RDMAP_NOT_SUPPORTED = RDMAP_TERMINATE + 1
पूर्ण;

#पूर्ण_अगर
