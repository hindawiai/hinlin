<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Cavium, Inc.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#अगर_अघोषित __LINUX_KVM_MIPS_H
#घोषणा __LINUX_KVM_MIPS_H

#समावेश <linux/types.h>

/*
 * KVM MIPS specअगरic काष्ठाures and definitions.
 *
 * Some parts derived from the x86 version of this file.
 */

/*
 * क्रम KVM_GET_REGS and KVM_SET_REGS
 *
 * If Config[AT] is zero (32-bit CPU), the रेजिस्टर contents are
 * stored in the lower 32-bits of the काष्ठा kvm_regs fields and sign
 * extended to 64-bits.
 */
काष्ठा kvm_regs अणु
	/* out (KVM_GET_REGS) / in (KVM_SET_REGS) */
	__u64 gpr[32];
	__u64 hi;
	__u64 lo;
	__u64 pc;
पूर्ण;

/*
 * क्रम KVM_GET_FPU and KVM_SET_FPU
 */
काष्ठा kvm_fpu अणु
पूर्ण;


/*
 * For MIPS, we use KVM_SET_ONE_REG and KVM_GET_ONE_REG to access various
 * रेजिस्टरs.  The id field is broken करोwn as follows:
 *
 *  bits[63..52] - As per linux/kvm.h
 *  bits[51..32] - Must be zero.
 *  bits[31..16] - Register set.
 *
 * Register set = 0: GP रेजिस्टरs from kvm_regs (see definitions below).
 *
 * Register set = 1: CP0 रेजिस्टरs.
 *  bits[15..8]  - Must be zero.
 *  bits[7..3]   - Register 'rd'  index.
 *  bits[2..0]   - Register 'sel' index.
 *
 * Register set = 2: KVM specअगरic रेजिस्टरs (see definitions below).
 *
 * Register set = 3: FPU / MSA रेजिस्टरs (see definitions below).
 *
 * Other sets रेजिस्टरs may be added in the future.  Each set would
 * have its own identअगरier in bits[31..16].
 */

#घोषणा KVM_REG_MIPS_GP		(KVM_REG_MIPS | 0x0000000000000000ULL)
#घोषणा KVM_REG_MIPS_CP0	(KVM_REG_MIPS | 0x0000000000010000ULL)
#घोषणा KVM_REG_MIPS_KVM	(KVM_REG_MIPS | 0x0000000000020000ULL)
#घोषणा KVM_REG_MIPS_FPU	(KVM_REG_MIPS | 0x0000000000030000ULL)


/*
 * KVM_REG_MIPS_GP - General purpose रेजिस्टरs from kvm_regs.
 */

#घोषणा KVM_REG_MIPS_R0		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  0)
#घोषणा KVM_REG_MIPS_R1		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  1)
#घोषणा KVM_REG_MIPS_R2		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  2)
#घोषणा KVM_REG_MIPS_R3		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  3)
#घोषणा KVM_REG_MIPS_R4		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  4)
#घोषणा KVM_REG_MIPS_R5		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  5)
#घोषणा KVM_REG_MIPS_R6		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  6)
#घोषणा KVM_REG_MIPS_R7		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  7)
#घोषणा KVM_REG_MIPS_R8		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  8)
#घोषणा KVM_REG_MIPS_R9		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 |  9)
#घोषणा KVM_REG_MIPS_R10	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 10)
#घोषणा KVM_REG_MIPS_R11	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 11)
#घोषणा KVM_REG_MIPS_R12	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 12)
#घोषणा KVM_REG_MIPS_R13	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 13)
#घोषणा KVM_REG_MIPS_R14	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 14)
#घोषणा KVM_REG_MIPS_R15	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 15)
#घोषणा KVM_REG_MIPS_R16	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 16)
#घोषणा KVM_REG_MIPS_R17	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 17)
#घोषणा KVM_REG_MIPS_R18	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 18)
#घोषणा KVM_REG_MIPS_R19	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 19)
#घोषणा KVM_REG_MIPS_R20	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 20)
#घोषणा KVM_REG_MIPS_R21	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 21)
#घोषणा KVM_REG_MIPS_R22	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 22)
#घोषणा KVM_REG_MIPS_R23	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 23)
#घोषणा KVM_REG_MIPS_R24	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 24)
#घोषणा KVM_REG_MIPS_R25	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 25)
#घोषणा KVM_REG_MIPS_R26	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 26)
#घोषणा KVM_REG_MIPS_R27	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 27)
#घोषणा KVM_REG_MIPS_R28	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 28)
#घोषणा KVM_REG_MIPS_R29	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 29)
#घोषणा KVM_REG_MIPS_R30	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 30)
#घोषणा KVM_REG_MIPS_R31	(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 31)

#घोषणा KVM_REG_MIPS_HI		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 32)
#घोषणा KVM_REG_MIPS_LO		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 33)
#घोषणा KVM_REG_MIPS_PC		(KVM_REG_MIPS_GP | KVM_REG_SIZE_U64 | 34)


/*
 * KVM_REG_MIPS_KVM - KVM specअगरic control रेजिस्टरs.
 */

/*
 * CP0_Count control
 * DC:    Set 0: Master disable CP0_Count and set COUNT_RESUME to now
 *        Set 1: Master re-enable CP0_Count with unchanged bias, handling समयr
 *               पूर्णांकerrupts since COUNT_RESUME
 *        This can be used to मुक्तze the समयr to get a consistent snapshot of
 *        the CP0_Count and समयr पूर्णांकerrupt pending state, जबतक also resuming
 *        safely without losing समय or guest समयr पूर्णांकerrupts.
 * Other: Reserved, करो not change.
 */
#घोषणा KVM_REG_MIPS_COUNT_CTL	    (KVM_REG_MIPS_KVM | KVM_REG_SIZE_U64 | 0)
#घोषणा KVM_REG_MIPS_COUNT_CTL_DC	0x00000001

/*
 * CP0_Count resume monotonic nanoseconds
 * The monotonic nanosecond समय of the last set of COUNT_CTL.DC (master
 * disable). Any पढ़ोs and ग_लिखोs of Count related रेजिस्टरs जबतक
 * COUNT_CTL.DC=1 will appear to occur at this समय. When COUNT_CTL.DC is
 * cleared again (master enable) any समयr पूर्णांकerrupts since this समय will be
 * emulated.
 * Modअगरications to बार in the future are rejected.
 */
#घोषणा KVM_REG_MIPS_COUNT_RESUME   (KVM_REG_MIPS_KVM | KVM_REG_SIZE_U64 | 1)
/*
 * CP0_Count rate in Hz
 * Specअगरies the rate of the CP0_Count समयr in Hz. Modअगरications occur without
 * discontinuities in CP0_Count.
 */
#घोषणा KVM_REG_MIPS_COUNT_HZ	    (KVM_REG_MIPS_KVM | KVM_REG_SIZE_U64 | 2)


/*
 * KVM_REG_MIPS_FPU - Floating Poपूर्णांक and MIPS SIMD Architecture (MSA) रेजिस्टरs.
 *
 *  bits[15..8]  - Register subset (see definitions below).
 *  bits[7..5]   - Must be zero.
 *  bits[4..0]   - Register number within रेजिस्टर subset.
 */

#घोषणा KVM_REG_MIPS_FPR	(KVM_REG_MIPS_FPU | 0x0000000000000000ULL)
#घोषणा KVM_REG_MIPS_FCR	(KVM_REG_MIPS_FPU | 0x0000000000000100ULL)
#घोषणा KVM_REG_MIPS_MSACR	(KVM_REG_MIPS_FPU | 0x0000000000000200ULL)

/*
 * KVM_REG_MIPS_FPR - Floating poपूर्णांक / Vector रेजिस्टरs.
 */
#घोषणा KVM_REG_MIPS_FPR_32(n)	(KVM_REG_MIPS_FPR | KVM_REG_SIZE_U32  | (n))
#घोषणा KVM_REG_MIPS_FPR_64(n)	(KVM_REG_MIPS_FPR | KVM_REG_SIZE_U64  | (n))
#घोषणा KVM_REG_MIPS_VEC_128(n)	(KVM_REG_MIPS_FPR | KVM_REG_SIZE_U128 | (n))

/*
 * KVM_REG_MIPS_FCR - Floating poपूर्णांक control रेजिस्टरs.
 */
#घोषणा KVM_REG_MIPS_FCR_IR	(KVM_REG_MIPS_FCR | KVM_REG_SIZE_U32 |  0)
#घोषणा KVM_REG_MIPS_FCR_CSR	(KVM_REG_MIPS_FCR | KVM_REG_SIZE_U32 | 31)

/*
 * KVM_REG_MIPS_MSACR - MIPS SIMD Architecture (MSA) control रेजिस्टरs.
 */
#घोषणा KVM_REG_MIPS_MSA_IR	 (KVM_REG_MIPS_MSACR | KVM_REG_SIZE_U32 |  0)
#घोषणा KVM_REG_MIPS_MSA_CSR	 (KVM_REG_MIPS_MSACR | KVM_REG_SIZE_U32 |  1)


/*
 * KVM MIPS specअगरic काष्ठाures and definitions
 *
 */
काष्ठा kvm_debug_निकास_arch अणु
	__u64 epc;
पूर्ण;

/* क्रम KVM_SET_GUEST_DEBUG */
काष्ठा kvm_guest_debug_arch अणु
पूर्ण;

/* definition of रेजिस्टरs in kvm_run */
काष्ठा kvm_sync_regs अणु
पूर्ण;

/* dummy definition */
काष्ठा kvm_sregs अणु
पूर्ण;

काष्ठा kvm_mips_पूर्णांकerrupt अणु
	/* in */
	__u32 cpu;
	__u32 irq;
पूर्ण;

#पूर्ण_अगर /* __LINUX_KVM_MIPS_H */
