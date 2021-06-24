<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित ARCH_PERF_ARM64_EXCEPTION_TYPES_H
#घोषणा ARCH_PERF_ARM64_EXCEPTION_TYPES_H

/* Per यंत्र/virt.h */
#घोषणा HVC_STUB_ERR		  0xbadca11

/* Per यंत्र/kvm_यंत्र.h */
#घोषणा ARM_EXCEPTION_IRQ		0
#घोषणा ARM_EXCEPTION_EL1_SERROR	1
#घोषणा ARM_EXCEPTION_TRAP		2
#घोषणा ARM_EXCEPTION_IL		3
/* The hyp-stub will वापस this क्रम any kvm_call_hyp() call */
#घोषणा ARM_EXCEPTION_HYP_GONE		HVC_STUB_ERR

#घोषणा kvm_arm_exception_type					\
	अणुARM_EXCEPTION_IRQ,		"IRQ"		पूर्ण,	\
	अणुARM_EXCEPTION_EL1_SERROR,	"SERROR"	पूर्ण,	\
	अणुARM_EXCEPTION_TRAP,		"TRAP"		पूर्ण,	\
	अणुARM_EXCEPTION_IL,		"ILLEGAL"	पूर्ण,	\
	अणुARM_EXCEPTION_HYP_GONE,	"HYP_GONE"	पूर्ण

/* Per यंत्र/esr.h */
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
/* Unallocated EC: 0x0d */
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
/* Unallocated EC: 0x1b - 0x1E */
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

#घोषणा ECN(x) अणु ESR_ELx_EC_##x, #x पूर्ण

#घोषणा kvm_arm_exception_class \
	ECN(UNKNOWN), ECN(WFx), ECN(CP15_32), ECN(CP15_64), ECN(CP14_MR), \
	ECN(CP14_LS), ECN(FP_ASIMD), ECN(CP10_ID), ECN(PAC), ECN(CP14_64), \
	ECN(SVC64), ECN(HVC64), ECN(SMC64), ECN(SYS64), ECN(SVE), \
	ECN(IMP_DEF), ECN(IABT_LOW), ECN(IABT_CUR), \
	ECN(PC_ALIGN), ECN(DABT_LOW), ECN(DABT_CUR), \
	ECN(SP_ALIGN), ECN(FP_EXC32), ECN(FP_EXC64), ECN(SERROR), \
	ECN(BREAKPT_LOW), ECN(BREAKPT_CUR), ECN(SOFTSTP_LOW), \
	ECN(SOFTSTP_CUR), ECN(WATCHPT_LOW), ECN(WATCHPT_CUR), \
	ECN(BKPT32), ECN(VECTOR32), ECN(BRK64)

#पूर्ण_अगर /* ARCH_PERF_ARM64_EXCEPTION_TYPES_H */
