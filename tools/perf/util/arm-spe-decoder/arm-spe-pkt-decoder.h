<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Arm Statistical Profiling Extensions (SPE) support
 * Copyright (c) 2017-2018, Arm Ltd.
 */

#अगर_अघोषित INCLUDE__ARM_SPE_PKT_DECODER_H__
#घोषणा INCLUDE__ARM_SPE_PKT_DECODER_H__

#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

#घोषणा ARM_SPE_PKT_DESC_MAX		256

#घोषणा ARM_SPE_NEED_MORE_BYTES		-1
#घोषणा ARM_SPE_BAD_PACKET		-2

#घोषणा ARM_SPE_PKT_MAX_SZ		16

क्रमागत arm_spe_pkt_type अणु
	ARM_SPE_BAD,
	ARM_SPE_PAD,
	ARM_SPE_END,
	ARM_SPE_TIMESTAMP,
	ARM_SPE_ADDRESS,
	ARM_SPE_COUNTER,
	ARM_SPE_CONTEXT,
	ARM_SPE_OP_TYPE,
	ARM_SPE_EVENTS,
	ARM_SPE_DATA_SOURCE,
पूर्ण;

काष्ठा arm_spe_pkt अणु
	क्रमागत arm_spe_pkt_type	type;
	अचिन्हित अक्षर		index;
	uपूर्णांक64_t		payload;
पूर्ण;

/* Short header (HEADER0) and extended header (HEADER1) */
#घोषणा SPE_HEADER0_PAD				0x0
#घोषणा SPE_HEADER0_END				0x1
#घोषणा SPE_HEADER0_TIMESTAMP			0x71
/* Mask क्रम event & data source */
#घोषणा SPE_HEADER0_MASK1			(GENMASK_ULL(7, 6) | GENMASK_ULL(3, 0))
#घोषणा SPE_HEADER0_EVENTS			0x42
#घोषणा SPE_HEADER0_SOURCE			0x43
/* Mask क्रम context & operation */
#घोषणा SPE_HEADER0_MASK2			GENMASK_ULL(7, 2)
#घोषणा SPE_HEADER0_CONTEXT			0x64
#घोषणा SPE_HEADER0_OP_TYPE			0x48
/* Mask क्रम extended क्रमmat */
#घोषणा SPE_HEADER0_EXTENDED			0x20
/* Mask क्रम address & counter */
#घोषणा SPE_HEADER0_MASK3			GENMASK_ULL(7, 3)
#घोषणा SPE_HEADER0_ADDRESS			0xb0
#घोषणा SPE_HEADER0_COUNTER			0x98
#घोषणा SPE_HEADER1_ALIGNMENT			0x0

#घोषणा SPE_HDR_SHORT_INDEX(h)			((h) & GENMASK_ULL(2, 0))
#घोषणा SPE_HDR_EXTENDED_INDEX(h0, h1)		(((h0) & GENMASK_ULL(1, 0)) << 3 | \
						 SPE_HDR_SHORT_INDEX(h1))

/* Address packet header */
#घोषणा SPE_ADDR_PKT_HDR_INDEX_INS		0x0
#घोषणा SPE_ADDR_PKT_HDR_INDEX_BRANCH		0x1
#घोषणा SPE_ADDR_PKT_HDR_INDEX_DATA_VIRT	0x2
#घोषणा SPE_ADDR_PKT_HDR_INDEX_DATA_PHYS	0x3

/* Address packet payload */
#घोषणा SPE_ADDR_PKT_ADDR_BYTE7_SHIFT		56
#घोषणा SPE_ADDR_PKT_ADDR_GET_BYTES_0_6(v)	((v) & GENMASK_ULL(55, 0))
#घोषणा SPE_ADDR_PKT_ADDR_GET_BYTE_6(v)		(((v) & GENMASK_ULL(55, 48)) >> 48)

#घोषणा SPE_ADDR_PKT_GET_NS(v)			(((v) & BIT_ULL(63)) >> 63)
#घोषणा SPE_ADDR_PKT_GET_EL(v)			(((v) & GENMASK_ULL(62, 61)) >> 61)
#घोषणा SPE_ADDR_PKT_GET_CH(v)			(((v) & BIT_ULL(62)) >> 62)
#घोषणा SPE_ADDR_PKT_GET_PAT(v)			(((v) & GENMASK_ULL(59, 56)) >> 56)

#घोषणा SPE_ADDR_PKT_EL0			0
#घोषणा SPE_ADDR_PKT_EL1			1
#घोषणा SPE_ADDR_PKT_EL2			2
#घोषणा SPE_ADDR_PKT_EL3			3

/* Context packet header */
#घोषणा SPE_CTX_PKT_HDR_INDEX(h)		((h) & GENMASK_ULL(1, 0))

/* Counter packet header */
#घोषणा SPE_CNT_PKT_HDR_INDEX_TOTAL_LAT		0x0
#घोषणा SPE_CNT_PKT_HDR_INDEX_ISSUE_LAT		0x1
#घोषणा SPE_CNT_PKT_HDR_INDEX_TRANS_LAT		0x2

/* Event packet payload */
क्रमागत arm_spe_events अणु
	EV_EXCEPTION_GEN	= 0,
	EV_RETIRED		= 1,
	EV_L1D_ACCESS		= 2,
	EV_L1D_REFILL		= 3,
	EV_TLB_ACCESS		= 4,
	EV_TLB_WALK		= 5,
	EV_NOT_TAKEN		= 6,
	EV_MISPRED		= 7,
	EV_LLC_ACCESS		= 8,
	EV_LLC_MISS		= 9,
	EV_REMOTE_ACCESS	= 10,
	EV_ALIGNMENT		= 11,
	EV_PARTIAL_PREDICATE	= 17,
	EV_EMPTY_PREDICATE	= 18,
पूर्ण;

/* Operation packet header */
#घोषणा SPE_OP_PKT_HDR_CLASS(h)			((h) & GENMASK_ULL(1, 0))
#घोषणा SPE_OP_PKT_HDR_CLASS_OTHER		0x0
#घोषणा SPE_OP_PKT_HDR_CLASS_LD_ST_ATOMIC	0x1
#घोषणा SPE_OP_PKT_HDR_CLASS_BR_ERET		0x2

#घोषणा SPE_OP_PKT_IS_OTHER_SVE_OP(v)		(((v) & (BIT(7) | BIT(3) | BIT(0))) == 0x8)

#घोषणा SPE_OP_PKT_COND				BIT(0)

#घोषणा SPE_OP_PKT_LDST_SUBCLASS_GET(v)		((v) & GENMASK_ULL(7, 1))
#घोषणा SPE_OP_PKT_LDST_SUBCLASS_GP_REG		0x0
#घोषणा SPE_OP_PKT_LDST_SUBCLASS_SIMD_FP	0x4
#घोषणा SPE_OP_PKT_LDST_SUBCLASS_UNSPEC_REG	0x10
#घोषणा SPE_OP_PKT_LDST_SUBCLASS_NV_SYSREG	0x30

#घोषणा SPE_OP_PKT_IS_LDST_ATOMIC(v)		(((v) & (GENMASK_ULL(7, 5) | BIT(1))) == 0x2)

#घोषणा SPE_OP_PKT_AR				BIT(4)
#घोषणा SPE_OP_PKT_EXCL				BIT(3)
#घोषणा SPE_OP_PKT_AT				BIT(2)
#घोषणा SPE_OP_PKT_ST				BIT(0)

#घोषणा SPE_OP_PKT_IS_LDST_SVE(v)		(((v) & (BIT(3) | BIT(1))) == 0x8)

#घोषणा SPE_OP_PKT_SVE_SG			BIT(7)
/*
 * SVE effective vector length (EVL) is stored in byte 0 bits [6:4];
 * the length is rounded up to a घातer of two and use 32 as one step,
 * so EVL calculation is:
 *
 *   32 * (2 ^ bits [6:4]) = 32 << (bits [6:4])
 */
#घोषणा SPE_OP_PKG_SVE_EVL(v)			(32 << (((v) & GENMASK_ULL(6, 4)) >> 4))
#घोषणा SPE_OP_PKT_SVE_PRED			BIT(2)
#घोषणा SPE_OP_PKT_SVE_FP			BIT(1)

#घोषणा SPE_OP_PKT_IS_INसूचीECT_BRANCH(v)	(((v) & GENMASK_ULL(7, 1)) == 0x2)

स्थिर अक्षर *arm_spe_pkt_name(क्रमागत arm_spe_pkt_type);

पूर्णांक arm_spe_get_packet(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
		       काष्ठा arm_spe_pkt *packet);

पूर्णांक arm_spe_pkt_desc(स्थिर काष्ठा arm_spe_pkt *packet, अक्षर *buf, माप_प्रकार len);
#पूर्ण_अगर
