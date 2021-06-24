<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ASM_ESR_H
#घोषणा __ASM_ESR_H

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/sysreg.h>

#घोषणा ESR_ELx_EC_UNKNOWN	(0x00)
#घोषणा ESR_ELx_EC_WFx		(0x01)
/* Unallocated EC: 0x02 */
#घोषणा ESR_ELx_EC_CP15_32	(0x03)
#घोषणा ESR_ELx_EC_CP15_64	(0x04)
#घोषणा ESR_ELx_EC_CP14_MR	(0x05)
#घोषणा ESR_ELx_EC_CP14_LS	(0x06)
#घोषणा ESR_ELx_EC_FP_ASIMD	(0x07)
#घोषणा ESR_ELx_EC_CP10_ID	(0x08)	/* EL2 only */
#घोषणा ESR_ELx_EC_PAC		(0x09)	/* EL2 and above */
/* Unallocated EC: 0x0A - 0x0B */
#घोषणा ESR_ELx_EC_CP14_64	(0x0C)
#घोषणा ESR_ELx_EC_BTI		(0x0D)
#घोषणा ESR_ELx_EC_ILL		(0x0E)
/* Unallocated EC: 0x0F - 0x10 */
#घोषणा ESR_ELx_EC_SVC32	(0x11)
#घोषणा ESR_ELx_EC_HVC32	(0x12)	/* EL2 only */
#घोषणा ESR_ELx_EC_SMC32	(0x13)	/* EL2 and above */
/* Unallocated EC: 0x14 */
#घोषणा ESR_ELx_EC_SVC64	(0x15)
#घोषणा ESR_ELx_EC_HVC64	(0x16)	/* EL2 and above */
#घोषणा ESR_ELx_EC_SMC64	(0x17)	/* EL2 and above */
#घोषणा ESR_ELx_EC_SYS64	(0x18)
#घोषणा ESR_ELx_EC_SVE		(0x19)
#घोषणा ESR_ELx_EC_ERET		(0x1a)	/* EL2 only */
/* Unallocated EC: 0x1B */
#घोषणा ESR_ELx_EC_FPAC		(0x1C)	/* EL1 and above */
/* Unallocated EC: 0x1D - 0x1E */
#घोषणा ESR_ELx_EC_IMP_DEF	(0x1f)	/* EL3 only */
#घोषणा ESR_ELx_EC_IABT_LOW	(0x20)
#घोषणा ESR_ELx_EC_IABT_CUR	(0x21)
#घोषणा ESR_ELx_EC_PC_ALIGN	(0x22)
/* Unallocated EC: 0x23 */
#घोषणा ESR_ELx_EC_DABT_LOW	(0x24)
#घोषणा ESR_ELx_EC_DABT_CUR	(0x25)
#घोषणा ESR_ELx_EC_SP_ALIGN	(0x26)
/* Unallocated EC: 0x27 */
#घोषणा ESR_ELx_EC_FP_EXC32	(0x28)
/* Unallocated EC: 0x29 - 0x2B */
#घोषणा ESR_ELx_EC_FP_EXC64	(0x2C)
/* Unallocated EC: 0x2D - 0x2E */
#घोषणा ESR_ELx_EC_SERROR	(0x2F)
#घोषणा ESR_ELx_EC_BREAKPT_LOW	(0x30)
#घोषणा ESR_ELx_EC_BREAKPT_CUR	(0x31)
#घोषणा ESR_ELx_EC_SOFTSTP_LOW	(0x32)
#घोषणा ESR_ELx_EC_SOFTSTP_CUR	(0x33)
#घोषणा ESR_ELx_EC_WATCHPT_LOW	(0x34)
#घोषणा ESR_ELx_EC_WATCHPT_CUR	(0x35)
/* Unallocated EC: 0x36 - 0x37 */
#घोषणा ESR_ELx_EC_BKPT32	(0x38)
/* Unallocated EC: 0x39 */
#घोषणा ESR_ELx_EC_VECTOR32	(0x3A)	/* EL2 only */
/* Unallocated EC: 0x3B */
#घोषणा ESR_ELx_EC_BRK64	(0x3C)
/* Unallocated EC: 0x3D - 0x3F */
#घोषणा ESR_ELx_EC_MAX		(0x3F)

#घोषणा ESR_ELx_EC_SHIFT	(26)
#घोषणा ESR_ELx_EC_MASK		(UL(0x3F) << ESR_ELx_EC_SHIFT)
#घोषणा ESR_ELx_EC(esr)		(((esr) & ESR_ELx_EC_MASK) >> ESR_ELx_EC_SHIFT)

#घोषणा ESR_ELx_IL_SHIFT	(25)
#घोषणा ESR_ELx_IL		(UL(1) << ESR_ELx_IL_SHIFT)
#घोषणा ESR_ELx_ISS_MASK	(ESR_ELx_IL - 1)

/* ISS field definitions shared by dअगरferent classes */
#घोषणा ESR_ELx_WNR_SHIFT	(6)
#घोषणा ESR_ELx_WNR		(UL(1) << ESR_ELx_WNR_SHIFT)

/* Asynchronous Error Type */
#घोषणा ESR_ELx_IDS_SHIFT	(24)
#घोषणा ESR_ELx_IDS		(UL(1) << ESR_ELx_IDS_SHIFT)
#घोषणा ESR_ELx_AET_SHIFT	(10)
#घोषणा ESR_ELx_AET		(UL(0x7) << ESR_ELx_AET_SHIFT)

#घोषणा ESR_ELx_AET_UC		(UL(0) << ESR_ELx_AET_SHIFT)
#घोषणा ESR_ELx_AET_UEU		(UL(1) << ESR_ELx_AET_SHIFT)
#घोषणा ESR_ELx_AET_UEO		(UL(2) << ESR_ELx_AET_SHIFT)
#घोषणा ESR_ELx_AET_UER		(UL(3) << ESR_ELx_AET_SHIFT)
#घोषणा ESR_ELx_AET_CE		(UL(6) << ESR_ELx_AET_SHIFT)

/* Shared ISS field definitions क्रम Data/Inकाष्ठाion पातs */
#घोषणा ESR_ELx_SET_SHIFT	(11)
#घोषणा ESR_ELx_SET_MASK	(UL(3) << ESR_ELx_SET_SHIFT)
#घोषणा ESR_ELx_FnV_SHIFT	(10)
#घोषणा ESR_ELx_FnV		(UL(1) << ESR_ELx_FnV_SHIFT)
#घोषणा ESR_ELx_EA_SHIFT	(9)
#घोषणा ESR_ELx_EA		(UL(1) << ESR_ELx_EA_SHIFT)
#घोषणा ESR_ELx_S1PTW_SHIFT	(7)
#घोषणा ESR_ELx_S1PTW		(UL(1) << ESR_ELx_S1PTW_SHIFT)

/* Shared ISS fault status code(IFSC/DFSC) क्रम Data/Inकाष्ठाion पातs */
#घोषणा ESR_ELx_FSC		(0x3F)
#घोषणा ESR_ELx_FSC_TYPE	(0x3C)
#घोषणा ESR_ELx_FSC_LEVEL	(0x03)
#घोषणा ESR_ELx_FSC_EXTABT	(0x10)
#घोषणा ESR_ELx_FSC_MTE		(0x11)
#घोषणा ESR_ELx_FSC_SERROR	(0x11)
#घोषणा ESR_ELx_FSC_ACCESS	(0x08)
#घोषणा ESR_ELx_FSC_FAULT	(0x04)
#घोषणा ESR_ELx_FSC_PERM	(0x0C)

/* ISS field definitions क्रम Data Aborts */
#घोषणा ESR_ELx_ISV_SHIFT	(24)
#घोषणा ESR_ELx_ISV		(UL(1) << ESR_ELx_ISV_SHIFT)
#घोषणा ESR_ELx_SAS_SHIFT	(22)
#घोषणा ESR_ELx_SAS		(UL(3) << ESR_ELx_SAS_SHIFT)
#घोषणा ESR_ELx_SSE_SHIFT	(21)
#घोषणा ESR_ELx_SSE		(UL(1) << ESR_ELx_SSE_SHIFT)
#घोषणा ESR_ELx_SRT_SHIFT	(16)
#घोषणा ESR_ELx_SRT_MASK	(UL(0x1F) << ESR_ELx_SRT_SHIFT)
#घोषणा ESR_ELx_SF_SHIFT	(15)
#घोषणा ESR_ELx_SF 		(UL(1) << ESR_ELx_SF_SHIFT)
#घोषणा ESR_ELx_AR_SHIFT	(14)
#घोषणा ESR_ELx_AR 		(UL(1) << ESR_ELx_AR_SHIFT)
#घोषणा ESR_ELx_CM_SHIFT	(8)
#घोषणा ESR_ELx_CM 		(UL(1) << ESR_ELx_CM_SHIFT)

/* ISS field definitions क्रम exceptions taken in to Hyp */
#घोषणा ESR_ELx_CV		(UL(1) << 24)
#घोषणा ESR_ELx_COND_SHIFT	(20)
#घोषणा ESR_ELx_COND_MASK	(UL(0xF) << ESR_ELx_COND_SHIFT)
#घोषणा ESR_ELx_WFx_ISS_TI	(UL(1) << 0)
#घोषणा ESR_ELx_WFx_ISS_WFI	(UL(0) << 0)
#घोषणा ESR_ELx_WFx_ISS_WFE	(UL(1) << 0)
#घोषणा ESR_ELx_xVC_IMM_MASK	((1UL << 16) - 1)

#घोषणा DISR_EL1_IDS		(UL(1) << 24)
/*
 * DISR_EL1 and ESR_ELx share the bottom 13 bits, but the RES0 bits may mean
 * dअगरferent things in the future...
 */
#घोषणा DISR_EL1_ESR_MASK	(ESR_ELx_AET | ESR_ELx_EA | ESR_ELx_FSC)

/* ESR value ढाँचाs क्रम specअगरic events */
#घोषणा ESR_ELx_WFx_MASK	(ESR_ELx_EC_MASK | ESR_ELx_WFx_ISS_TI)
#घोषणा ESR_ELx_WFx_WFI_VAL	((ESR_ELx_EC_WFx << ESR_ELx_EC_SHIFT) |	\
				 ESR_ELx_WFx_ISS_WFI)

/* BRK inकाष्ठाion trap from AArch64 state */
#घोषणा ESR_ELx_BRK64_ISS_COMMENT_MASK	0xffff

/* ISS field definitions क्रम System inकाष्ठाion traps */
#घोषणा ESR_ELx_SYS64_ISS_RES0_SHIFT	22
#घोषणा ESR_ELx_SYS64_ISS_RES0_MASK	(UL(0x7) << ESR_ELx_SYS64_ISS_RES0_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_सूची_MASK	0x1
#घोषणा ESR_ELx_SYS64_ISS_सूची_READ	0x1
#घोषणा ESR_ELx_SYS64_ISS_सूची_WRITE	0x0

#घोषणा ESR_ELx_SYS64_ISS_RT_SHIFT	5
#घोषणा ESR_ELx_SYS64_ISS_RT_MASK	(UL(0x1f) << ESR_ELx_SYS64_ISS_RT_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_CRM_SHIFT	1
#घोषणा ESR_ELx_SYS64_ISS_CRM_MASK	(UL(0xf) << ESR_ELx_SYS64_ISS_CRM_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_CRN_SHIFT	10
#घोषणा ESR_ELx_SYS64_ISS_CRN_MASK	(UL(0xf) << ESR_ELx_SYS64_ISS_CRN_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_OP1_SHIFT	14
#घोषणा ESR_ELx_SYS64_ISS_OP1_MASK	(UL(0x7) << ESR_ELx_SYS64_ISS_OP1_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_OP2_SHIFT	17
#घोषणा ESR_ELx_SYS64_ISS_OP2_MASK	(UL(0x7) << ESR_ELx_SYS64_ISS_OP2_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_OP0_SHIFT	20
#घोषणा ESR_ELx_SYS64_ISS_OP0_MASK	(UL(0x3) << ESR_ELx_SYS64_ISS_OP0_SHIFT)
#घोषणा ESR_ELx_SYS64_ISS_SYS_MASK	(ESR_ELx_SYS64_ISS_OP0_MASK | \
					 ESR_ELx_SYS64_ISS_OP1_MASK | \
					 ESR_ELx_SYS64_ISS_OP2_MASK | \
					 ESR_ELx_SYS64_ISS_CRN_MASK | \
					 ESR_ELx_SYS64_ISS_CRM_MASK)
#घोषणा ESR_ELx_SYS64_ISS_SYS_VAL(op0, op1, op2, crn, crm) \
					(((op0) << ESR_ELx_SYS64_ISS_OP0_SHIFT) | \
					 ((op1) << ESR_ELx_SYS64_ISS_OP1_SHIFT) | \
					 ((op2) << ESR_ELx_SYS64_ISS_OP2_SHIFT) | \
					 ((crn) << ESR_ELx_SYS64_ISS_CRN_SHIFT) | \
					 ((crm) << ESR_ELx_SYS64_ISS_CRM_SHIFT))

#घोषणा ESR_ELx_SYS64_ISS_SYS_OP_MASK	(ESR_ELx_SYS64_ISS_SYS_MASK | \
					 ESR_ELx_SYS64_ISS_सूची_MASK)
#घोषणा ESR_ELx_SYS64_ISS_RT(esr) \
	(((esr) & ESR_ELx_SYS64_ISS_RT_MASK) >> ESR_ELx_SYS64_ISS_RT_SHIFT)
/*
 * User space cache operations have the following sysreg encoding
 * in System inकाष्ठाions.
 * op0=1, op1=3, op2=1, crn=7, crm=अणु 5, 10, 11, 12, 13, 14 पूर्ण, WRITE (L=0)
 */
#घोषणा ESR_ELx_SYS64_ISS_CRM_DC_CIVAC	14
#घोषणा ESR_ELx_SYS64_ISS_CRM_DC_CVADP	13
#घोषणा ESR_ELx_SYS64_ISS_CRM_DC_CVAP	12
#घोषणा ESR_ELx_SYS64_ISS_CRM_DC_CVAU	11
#घोषणा ESR_ELx_SYS64_ISS_CRM_DC_CVAC	10
#घोषणा ESR_ELx_SYS64_ISS_CRM_IC_IVAU	5

#घोषणा ESR_ELx_SYS64_ISS_EL0_CACHE_OP_MASK	(ESR_ELx_SYS64_ISS_OP0_MASK | \
						 ESR_ELx_SYS64_ISS_OP1_MASK | \
						 ESR_ELx_SYS64_ISS_OP2_MASK | \
						 ESR_ELx_SYS64_ISS_CRN_MASK | \
						 ESR_ELx_SYS64_ISS_सूची_MASK)
#घोषणा ESR_ELx_SYS64_ISS_EL0_CACHE_OP_VAL \
				(ESR_ELx_SYS64_ISS_SYS_VAL(1, 3, 1, 7, 0) | \
				 ESR_ELx_SYS64_ISS_सूची_WRITE)
/*
 * User space MRS operations which are supported क्रम emulation
 * have the following sysreg encoding in System inकाष्ठाions.
 * op0 = 3, op1= 0, crn = 0, अणुcrm = 0, 4-7पूर्ण, READ (L = 1)
 */
#घोषणा ESR_ELx_SYS64_ISS_SYS_MRS_OP_MASK	(ESR_ELx_SYS64_ISS_OP0_MASK | \
						 ESR_ELx_SYS64_ISS_OP1_MASK | \
						 ESR_ELx_SYS64_ISS_CRN_MASK | \
						 ESR_ELx_SYS64_ISS_सूची_MASK)
#घोषणा ESR_ELx_SYS64_ISS_SYS_MRS_OP_VAL \
				(ESR_ELx_SYS64_ISS_SYS_VAL(3, 0, 0, 0, 0) | \
				 ESR_ELx_SYS64_ISS_सूची_READ)

#घोषणा ESR_ELx_SYS64_ISS_SYS_CTR	ESR_ELx_SYS64_ISS_SYS_VAL(3, 3, 1, 0, 0)
#घोषणा ESR_ELx_SYS64_ISS_SYS_CTR_READ	(ESR_ELx_SYS64_ISS_SYS_CTR | \
					 ESR_ELx_SYS64_ISS_सूची_READ)

#घोषणा ESR_ELx_SYS64_ISS_SYS_CNTVCT	(ESR_ELx_SYS64_ISS_SYS_VAL(3, 3, 2, 14, 0) | \
					 ESR_ELx_SYS64_ISS_सूची_READ)

#घोषणा ESR_ELx_SYS64_ISS_SYS_CNTFRQ	(ESR_ELx_SYS64_ISS_SYS_VAL(3, 3, 0, 14, 0) | \
					 ESR_ELx_SYS64_ISS_सूची_READ)

#घोषणा esr_sys64_to_sysreg(e)					\
	sys_reg((((e) & ESR_ELx_SYS64_ISS_OP0_MASK) >>		\
		 ESR_ELx_SYS64_ISS_OP0_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_OP1_MASK) >>		\
		 ESR_ELx_SYS64_ISS_OP1_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_CRN_MASK) >>		\
		 ESR_ELx_SYS64_ISS_CRN_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_CRM_MASK) >>		\
		 ESR_ELx_SYS64_ISS_CRM_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_OP2_MASK) >>		\
		 ESR_ELx_SYS64_ISS_OP2_SHIFT))

#घोषणा esr_cp15_to_sysreg(e)					\
	sys_reg(3,						\
		(((e) & ESR_ELx_SYS64_ISS_OP1_MASK) >>		\
		 ESR_ELx_SYS64_ISS_OP1_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_CRN_MASK) >>		\
		 ESR_ELx_SYS64_ISS_CRN_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_CRM_MASK) >>		\
		 ESR_ELx_SYS64_ISS_CRM_SHIFT),			\
		(((e) & ESR_ELx_SYS64_ISS_OP2_MASK) >>		\
		 ESR_ELx_SYS64_ISS_OP2_SHIFT))

/*
 * ISS field definitions क्रम भग्नing-poपूर्णांक exception traps
 * (FP_EXC_32/FP_EXC_64).
 *
 * (The FPEXC_* स्थिरants are used instead क्रम common bits.)
 */

#घोषणा ESR_ELx_FP_EXC_TFV	(UL(1) << 23)

/*
 * ISS field definitions क्रम CP15 accesses
 */
#घोषणा ESR_ELx_CP15_32_ISS_सूची_MASK	0x1
#घोषणा ESR_ELx_CP15_32_ISS_सूची_READ	0x1
#घोषणा ESR_ELx_CP15_32_ISS_सूची_WRITE	0x0

#घोषणा ESR_ELx_CP15_32_ISS_RT_SHIFT	5
#घोषणा ESR_ELx_CP15_32_ISS_RT_MASK	(UL(0x1f) << ESR_ELx_CP15_32_ISS_RT_SHIFT)
#घोषणा ESR_ELx_CP15_32_ISS_CRM_SHIFT	1
#घोषणा ESR_ELx_CP15_32_ISS_CRM_MASK	(UL(0xf) << ESR_ELx_CP15_32_ISS_CRM_SHIFT)
#घोषणा ESR_ELx_CP15_32_ISS_CRN_SHIFT	10
#घोषणा ESR_ELx_CP15_32_ISS_CRN_MASK	(UL(0xf) << ESR_ELx_CP15_32_ISS_CRN_SHIFT)
#घोषणा ESR_ELx_CP15_32_ISS_OP1_SHIFT	14
#घोषणा ESR_ELx_CP15_32_ISS_OP1_MASK	(UL(0x7) << ESR_ELx_CP15_32_ISS_OP1_SHIFT)
#घोषणा ESR_ELx_CP15_32_ISS_OP2_SHIFT	17
#घोषणा ESR_ELx_CP15_32_ISS_OP2_MASK	(UL(0x7) << ESR_ELx_CP15_32_ISS_OP2_SHIFT)

#घोषणा ESR_ELx_CP15_32_ISS_SYS_MASK	(ESR_ELx_CP15_32_ISS_OP1_MASK | \
					 ESR_ELx_CP15_32_ISS_OP2_MASK | \
					 ESR_ELx_CP15_32_ISS_CRN_MASK | \
					 ESR_ELx_CP15_32_ISS_CRM_MASK | \
					 ESR_ELx_CP15_32_ISS_सूची_MASK)
#घोषणा ESR_ELx_CP15_32_ISS_SYS_VAL(op1, op2, crn, crm) \
					(((op1) << ESR_ELx_CP15_32_ISS_OP1_SHIFT) | \
					 ((op2) << ESR_ELx_CP15_32_ISS_OP2_SHIFT) | \
					 ((crn) << ESR_ELx_CP15_32_ISS_CRN_SHIFT) | \
					 ((crm) << ESR_ELx_CP15_32_ISS_CRM_SHIFT))

#घोषणा ESR_ELx_CP15_64_ISS_सूची_MASK	0x1
#घोषणा ESR_ELx_CP15_64_ISS_सूची_READ	0x1
#घोषणा ESR_ELx_CP15_64_ISS_सूची_WRITE	0x0

#घोषणा ESR_ELx_CP15_64_ISS_RT_SHIFT	5
#घोषणा ESR_ELx_CP15_64_ISS_RT_MASK	(UL(0x1f) << ESR_ELx_CP15_64_ISS_RT_SHIFT)

#घोषणा ESR_ELx_CP15_64_ISS_RT2_SHIFT	10
#घोषणा ESR_ELx_CP15_64_ISS_RT2_MASK	(UL(0x1f) << ESR_ELx_CP15_64_ISS_RT2_SHIFT)

#घोषणा ESR_ELx_CP15_64_ISS_OP1_SHIFT	16
#घोषणा ESR_ELx_CP15_64_ISS_OP1_MASK	(UL(0xf) << ESR_ELx_CP15_64_ISS_OP1_SHIFT)
#घोषणा ESR_ELx_CP15_64_ISS_CRM_SHIFT	1
#घोषणा ESR_ELx_CP15_64_ISS_CRM_MASK	(UL(0xf) << ESR_ELx_CP15_64_ISS_CRM_SHIFT)

#घोषणा ESR_ELx_CP15_64_ISS_SYS_VAL(op1, crm) \
					(((op1) << ESR_ELx_CP15_64_ISS_OP1_SHIFT) | \
					 ((crm) << ESR_ELx_CP15_64_ISS_CRM_SHIFT))

#घोषणा ESR_ELx_CP15_64_ISS_SYS_MASK	(ESR_ELx_CP15_64_ISS_OP1_MASK |	\
					 ESR_ELx_CP15_64_ISS_CRM_MASK | \
					 ESR_ELx_CP15_64_ISS_सूची_MASK)

#घोषणा ESR_ELx_CP15_64_ISS_SYS_CNTVCT	(ESR_ELx_CP15_64_ISS_SYS_VAL(1, 14) | \
					 ESR_ELx_CP15_64_ISS_सूची_READ)

#घोषणा ESR_ELx_CP15_32_ISS_SYS_CNTFRQ	(ESR_ELx_CP15_32_ISS_SYS_VAL(0, 0, 14, 0) |\
					 ESR_ELx_CP15_32_ISS_सूची_READ)

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/types.h>

अटल अंतरभूत bool esr_is_data_पात(u32 esr)
अणु
	स्थिर u32 ec = ESR_ELx_EC(esr);

	वापस ec == ESR_ELx_EC_DABT_LOW || ec == ESR_ELx_EC_DABT_CUR;
पूर्ण

स्थिर अक्षर *esr_get_class_string(u32 esr);
#पूर्ण_अगर /* __ASSEMBLY */

#पूर्ण_अगर /* __ASM_ESR_H */
