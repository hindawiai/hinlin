<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Just-In-Time compiler क्रम BPF filters on 32bit ARM
 *
 * Copyright (c) 2011 Mircea Gherzan <mgherzan@gmail.com>
 */

#अगर_अघोषित PFILTER_OPCODES_ARM_H
#घोषणा PFILTER_OPCODES_ARM_H

/* ARM 32bit Registers */
#घोषणा ARM_R0	0
#घोषणा ARM_R1	1
#घोषणा ARM_R2	2
#घोषणा ARM_R3	3
#घोषणा ARM_R4	4
#घोषणा ARM_R5	5
#घोषणा ARM_R6	6
#घोषणा ARM_R7	7
#घोषणा ARM_R8	8
#घोषणा ARM_R9	9
#घोषणा ARM_R10	10
#घोषणा ARM_FP	11	/* Frame Poपूर्णांकer */
#घोषणा ARM_IP	12	/* Intra-procedure scratch रेजिस्टर */
#घोषणा ARM_SP	13	/* Stack poपूर्णांकer: as load/store base reg */
#घोषणा ARM_LR	14	/* Link Register */
#घोषणा ARM_PC	15	/* Program counter */

#घोषणा ARM_COND_EQ		0x0	/* == */
#घोषणा ARM_COND_NE		0x1	/* != */
#घोषणा ARM_COND_CS		0x2	/* अचिन्हित >= */
#घोषणा ARM_COND_HS		ARM_COND_CS
#घोषणा ARM_COND_CC		0x3	/* अचिन्हित < */
#घोषणा ARM_COND_LO		ARM_COND_CC
#घोषणा ARM_COND_MI		0x4	/* < 0 */
#घोषणा ARM_COND_PL		0x5	/* >= 0 */
#घोषणा ARM_COND_VS		0x6	/* Signed Overflow */
#घोषणा ARM_COND_VC		0x7	/* No Signed Overflow */
#घोषणा ARM_COND_HI		0x8	/* अचिन्हित > */
#घोषणा ARM_COND_LS		0x9	/* अचिन्हित <= */
#घोषणा ARM_COND_GE		0xa	/* Signed >= */
#घोषणा ARM_COND_LT		0xb	/* Signed < */
#घोषणा ARM_COND_GT		0xc	/* Signed > */
#घोषणा ARM_COND_LE		0xd	/* Signed <= */
#घोषणा ARM_COND_AL		0xe	/* None */

/* रेजिस्टर shअगरt types */
#घोषणा SRTYPE_LSL		0
#घोषणा SRTYPE_LSR		1
#घोषणा SRTYPE_ASR		2
#घोषणा SRTYPE_ROR		3
#घोषणा SRTYPE_ASL		(SRTYPE_LSL)

#घोषणा ARM_INST_ADD_R		0x00800000
#घोषणा ARM_INST_ADDS_R		0x00900000
#घोषणा ARM_INST_ADC_R		0x00a00000
#घोषणा ARM_INST_ADC_I		0x02a00000
#घोषणा ARM_INST_ADD_I		0x02800000
#घोषणा ARM_INST_ADDS_I		0x02900000

#घोषणा ARM_INST_AND_R		0x00000000
#घोषणा ARM_INST_ANDS_R		0x00100000
#घोषणा ARM_INST_AND_I		0x02000000

#घोषणा ARM_INST_BIC_R		0x01c00000
#घोषणा ARM_INST_BIC_I		0x03c00000

#घोषणा ARM_INST_B		0x0a000000
#घोषणा ARM_INST_BX		0x012FFF10
#घोषणा ARM_INST_BLX_R		0x012fff30

#घोषणा ARM_INST_CMP_R		0x01500000
#घोषणा ARM_INST_CMP_I		0x03500000

#घोषणा ARM_INST_EOR_R		0x00200000
#घोषणा ARM_INST_EOR_I		0x02200000

#घोषणा ARM_INST_LDST__U	0x00800000
#घोषणा ARM_INST_LDST__IMM12	0x00000fff
#घोषणा ARM_INST_LDRB_I		0x05500000
#घोषणा ARM_INST_LDRB_R		0x07d00000
#घोषणा ARM_INST_LDRD_I		0x014000d0
#घोषणा ARM_INST_LDRH_I		0x015000b0
#घोषणा ARM_INST_LDRH_R		0x019000b0
#घोषणा ARM_INST_LDR_I		0x05100000
#घोषणा ARM_INST_LDR_R		0x07900000

#घोषणा ARM_INST_LDM		0x08900000
#घोषणा ARM_INST_LDM_IA		0x08b00000

#घोषणा ARM_INST_LSL_I		0x01a00000
#घोषणा ARM_INST_LSL_R		0x01a00010

#घोषणा ARM_INST_LSR_I		0x01a00020
#घोषणा ARM_INST_LSR_R		0x01a00030

#घोषणा ARM_INST_ASR_I		0x01a00040
#घोषणा ARM_INST_ASR_R		0x01a00050

#घोषणा ARM_INST_MOV_R		0x01a00000
#घोषणा ARM_INST_MOVS_R		0x01b00000
#घोषणा ARM_INST_MOV_I		0x03a00000
#घोषणा ARM_INST_MOVW		0x03000000
#घोषणा ARM_INST_MOVT		0x03400000

#घोषणा ARM_INST_MUL		0x00000090

#घोषणा ARM_INST_POP		0x08bd0000
#घोषणा ARM_INST_PUSH		0x092d0000

#घोषणा ARM_INST_ORR_R		0x01800000
#घोषणा ARM_INST_ORRS_R		0x01900000
#घोषणा ARM_INST_ORR_I		0x03800000

#घोषणा ARM_INST_REV		0x06bf0f30
#घोषणा ARM_INST_REV16		0x06bf0fb0

#घोषणा ARM_INST_RSB_I		0x02600000
#घोषणा ARM_INST_RSBS_I		0x02700000
#घोषणा ARM_INST_RSC_I		0x02e00000

#घोषणा ARM_INST_SUB_R		0x00400000
#घोषणा ARM_INST_SUBS_R		0x00500000
#घोषणा ARM_INST_RSB_R		0x00600000
#घोषणा ARM_INST_SUB_I		0x02400000
#घोषणा ARM_INST_SUBS_I		0x02500000
#घोषणा ARM_INST_SBC_I		0x02c00000
#घोषणा ARM_INST_SBC_R		0x00c00000
#घोषणा ARM_INST_SBCS_R		0x00d00000

#घोषणा ARM_INST_STR_I		0x05000000
#घोषणा ARM_INST_STRB_I		0x05400000
#घोषणा ARM_INST_STRD_I		0x014000f0
#घोषणा ARM_INST_STRH_I		0x014000b0

#घोषणा ARM_INST_TST_R		0x01100000
#घोषणा ARM_INST_TST_I		0x03100000

#घोषणा ARM_INST_UDIV		0x0730f010

#घोषणा ARM_INST_UMULL		0x00800090

#घोषणा ARM_INST_MLS		0x00600090

#घोषणा ARM_INST_UXTH		0x06ff0070

/*
 * Use a suitable undefined inकाष्ठाion to use क्रम ARM/Thumb2 faulting.
 * We need to be careful not to conflict with those used by other modules
 * (BUG, kprobes, etc) and the रेजिस्टर_undef_hook() प्रणाली.
 *
 * The ARM architecture reference manual guarantees that the following
 * inकाष्ठाion space will produce an undefined inकाष्ठाion exception on
 * all CPUs:
 *
 * ARM:   xxxx 0111 1111 xxxx xxxx xxxx 1111 xxxx	ARMv7-AR, section A5.4
 * Thumb: 1101 1110 xxxx xxxx				ARMv7-M, section A5.2.6
 */
#घोषणा ARM_INST_UDF		0xe7fddef1

/* रेजिस्टर */
#घोषणा _AL3_R(op, rd, rn, rm)	((op ## _R) | (rd) << 12 | (rn) << 16 | (rm))
/* immediate */
#घोषणा _AL3_I(op, rd, rn, imm)	((op ## _I) | (rd) << 12 | (rn) << 16 | (imm))
/* रेजिस्टर with रेजिस्टर-shअगरt */
#घोषणा _AL3_SR(inst)	(inst | (1 << 4))

#घोषणा ARM_ADD_R(rd, rn, rm)	_AL3_R(ARM_INST_ADD, rd, rn, rm)
#घोषणा ARM_ADDS_R(rd, rn, rm)	_AL3_R(ARM_INST_ADDS, rd, rn, rm)
#घोषणा ARM_ADD_I(rd, rn, imm)	_AL3_I(ARM_INST_ADD, rd, rn, imm)
#घोषणा ARM_ADDS_I(rd, rn, imm)	_AL3_I(ARM_INST_ADDS, rd, rn, imm)
#घोषणा ARM_ADC_R(rd, rn, rm)	_AL3_R(ARM_INST_ADC, rd, rn, rm)
#घोषणा ARM_ADC_I(rd, rn, imm)	_AL3_I(ARM_INST_ADC, rd, rn, imm)

#घोषणा ARM_AND_R(rd, rn, rm)	_AL3_R(ARM_INST_AND, rd, rn, rm)
#घोषणा ARM_ANDS_R(rd, rn, rm)	_AL3_R(ARM_INST_ANDS, rd, rn, rm)
#घोषणा ARM_AND_I(rd, rn, imm)	_AL3_I(ARM_INST_AND, rd, rn, imm)

#घोषणा ARM_BIC_R(rd, rn, rm)	_AL3_R(ARM_INST_BIC, rd, rn, rm)
#घोषणा ARM_BIC_I(rd, rn, imm)	_AL3_I(ARM_INST_BIC, rd, rn, imm)

#घोषणा ARM_B(imm24)		(ARM_INST_B | ((imm24) & 0xffffff))
#घोषणा ARM_BX(rm)		(ARM_INST_BX | (rm))
#घोषणा ARM_BLX_R(rm)		(ARM_INST_BLX_R | (rm))

#घोषणा ARM_CMP_R(rn, rm)	_AL3_R(ARM_INST_CMP, 0, rn, rm)
#घोषणा ARM_CMP_I(rn, imm)	_AL3_I(ARM_INST_CMP, 0, rn, imm)

#घोषणा ARM_EOR_R(rd, rn, rm)	_AL3_R(ARM_INST_EOR, rd, rn, rm)
#घोषणा ARM_EOR_I(rd, rn, imm)	_AL3_I(ARM_INST_EOR, rd, rn, imm)

#घोषणा ARM_LDR_R(rt, rn, rm)	(ARM_INST_LDR_R | ARM_INST_LDST__U \
				 | (rt) << 12 | (rn) << 16 \
				 | (rm))
#घोषणा ARM_LDR_R_SI(rt, rn, rm, type, imm) \
				(ARM_INST_LDR_R | ARM_INST_LDST__U \
				 | (rt) << 12 | (rn) << 16 \
				 | (imm) << 7 | (type) << 5 | (rm))
#घोषणा ARM_LDRB_R(rt, rn, rm)	(ARM_INST_LDRB_R | ARM_INST_LDST__U \
				 | (rt) << 12 | (rn) << 16 \
				 | (rm))
#घोषणा ARM_LDRH_R(rt, rn, rm)	(ARM_INST_LDRH_R | ARM_INST_LDST__U \
				 | (rt) << 12 | (rn) << 16 \
				 | (rm))

#घोषणा ARM_LDM(rn, regs)	(ARM_INST_LDM | (rn) << 16 | (regs))
#घोषणा ARM_LDM_IA(rn, regs)	(ARM_INST_LDM_IA | (rn) << 16 | (regs))

#घोषणा ARM_LSL_R(rd, rn, rm)	(_AL3_R(ARM_INST_LSL, rd, 0, rn) | (rm) << 8)
#घोषणा ARM_LSL_I(rd, rn, imm)	(_AL3_I(ARM_INST_LSL, rd, 0, rn) | (imm) << 7)

#घोषणा ARM_LSR_R(rd, rn, rm)	(_AL3_R(ARM_INST_LSR, rd, 0, rn) | (rm) << 8)
#घोषणा ARM_LSR_I(rd, rn, imm)	(_AL3_I(ARM_INST_LSR, rd, 0, rn) | (imm) << 7)
#घोषणा ARM_ASR_R(rd, rn, rm)   (_AL3_R(ARM_INST_ASR, rd, 0, rn) | (rm) << 8)
#घोषणा ARM_ASR_I(rd, rn, imm)  (_AL3_I(ARM_INST_ASR, rd, 0, rn) | (imm) << 7)

#घोषणा ARM_MOV_R(rd, rm)	_AL3_R(ARM_INST_MOV, rd, 0, rm)
#घोषणा ARM_MOVS_R(rd, rm)	_AL3_R(ARM_INST_MOVS, rd, 0, rm)
#घोषणा ARM_MOV_I(rd, imm)	_AL3_I(ARM_INST_MOV, rd, 0, imm)
#घोषणा ARM_MOV_SR(rd, rm, type, rs)	\
	(_AL3_SR(ARM_MOV_R(rd, rm)) | (type) << 5 | (rs) << 8)
#घोषणा ARM_MOV_SI(rd, rm, type, imm6)	\
	(ARM_MOV_R(rd, rm) | (type) << 5 | (imm6) << 7)

#घोषणा ARM_MOVW(rd, imm)	\
	(ARM_INST_MOVW | ((imm) >> 12) << 16 | (rd) << 12 | ((imm) & 0x0fff))

#घोषणा ARM_MOVT(rd, imm)	\
	(ARM_INST_MOVT | ((imm) >> 12) << 16 | (rd) << 12 | ((imm) & 0x0fff))

#घोषणा ARM_MUL(rd, rm, rn)	(ARM_INST_MUL | (rd) << 16 | (rm) << 8 | (rn))

#घोषणा ARM_POP(regs)		(ARM_INST_POP | (regs))
#घोषणा ARM_PUSH(regs)		(ARM_INST_PUSH | (regs))

#घोषणा ARM_ORR_R(rd, rn, rm)	_AL3_R(ARM_INST_ORR, rd, rn, rm)
#घोषणा ARM_ORR_I(rd, rn, imm)	_AL3_I(ARM_INST_ORR, rd, rn, imm)
#घोषणा ARM_ORR_SR(rd, rn, rm, type, rs)	\
	(_AL3_SR(ARM_ORR_R(rd, rn, rm)) | (type) << 5 | (rs) << 8)
#घोषणा ARM_ORRS_R(rd, rn, rm)	_AL3_R(ARM_INST_ORRS, rd, rn, rm)
#घोषणा ARM_ORRS_SR(rd, rn, rm, type, rs)	\
	(_AL3_SR(ARM_ORRS_R(rd, rn, rm)) | (type) << 5 | (rs) << 8)
#घोषणा ARM_ORR_SI(rd, rn, rm, type, imm6)	\
	(ARM_ORR_R(rd, rn, rm) | (type) << 5 | (imm6) << 7)
#घोषणा ARM_ORRS_SI(rd, rn, rm, type, imm6)	\
	(ARM_ORRS_R(rd, rn, rm) | (type) << 5 | (imm6) << 7)

#घोषणा ARM_REV(rd, rm)		(ARM_INST_REV | (rd) << 12 | (rm))
#घोषणा ARM_REV16(rd, rm)	(ARM_INST_REV16 | (rd) << 12 | (rm))

#घोषणा ARM_RSB_I(rd, rn, imm)	_AL3_I(ARM_INST_RSB, rd, rn, imm)
#घोषणा ARM_RSBS_I(rd, rn, imm)	_AL3_I(ARM_INST_RSBS, rd, rn, imm)
#घोषणा ARM_RSC_I(rd, rn, imm)	_AL3_I(ARM_INST_RSC, rd, rn, imm)

#घोषणा ARM_SUB_R(rd, rn, rm)	_AL3_R(ARM_INST_SUB, rd, rn, rm)
#घोषणा ARM_SUBS_R(rd, rn, rm)	_AL3_R(ARM_INST_SUBS, rd, rn, rm)
#घोषणा ARM_RSB_R(rd, rn, rm)	_AL3_R(ARM_INST_RSB, rd, rn, rm)
#घोषणा ARM_SBC_R(rd, rn, rm)	_AL3_R(ARM_INST_SBC, rd, rn, rm)
#घोषणा ARM_SBCS_R(rd, rn, rm)	_AL3_R(ARM_INST_SBCS, rd, rn, rm)
#घोषणा ARM_SUB_I(rd, rn, imm)	_AL3_I(ARM_INST_SUB, rd, rn, imm)
#घोषणा ARM_SUBS_I(rd, rn, imm)	_AL3_I(ARM_INST_SUBS, rd, rn, imm)
#घोषणा ARM_SBC_I(rd, rn, imm)	_AL3_I(ARM_INST_SBC, rd, rn, imm)

#घोषणा ARM_TST_R(rn, rm)	_AL3_R(ARM_INST_TST, 0, rn, rm)
#घोषणा ARM_TST_I(rn, imm)	_AL3_I(ARM_INST_TST, 0, rn, imm)

#घोषणा ARM_UDIV(rd, rn, rm)	(ARM_INST_UDIV | (rd) << 16 | (rn) | (rm) << 8)

#घोषणा ARM_UMULL(rd_lo, rd_hi, rn, rm)	(ARM_INST_UMULL | (rd_hi) << 16 \
					 | (rd_lo) << 12 | (rm) << 8 | rn)

#घोषणा ARM_MLS(rd, rn, rm, ra)	(ARM_INST_MLS | (rd) << 16 | (rn) | (rm) << 8 \
				 | (ra) << 12)
#घोषणा ARM_UXTH(rd, rm)	(ARM_INST_UXTH | (rd) << 12 | (rm))

#पूर्ण_अगर /* PFILTER_OPCODES_ARM_H */
