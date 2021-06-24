<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* arch/arm64/include/यंत्र/kvm_ptrauth.h: Guest/host ptrauth save/restore
 * Copyright 2019 Arm Limited
 * Authors: Mark Rutland <mark.rutland@arm.com>
 *         Amit Daniel Kachhap <amit.kachhap@arm.com>
 */

#अगर_अघोषित __ASM_KVM_PTRAUTH_H
#घोषणा __ASM_KVM_PTRAUTH_H

#अगर_घोषित __ASSEMBLY__

#समावेश <यंत्र/sysreg.h>

#अगर_घोषित	CONFIG_ARM64_PTR_AUTH

#घोषणा PTRAUTH_REG_OFFSET(x)	(x - CPU_APIAKEYLO_EL1)

/*
 * CPU_AP*_EL1 values exceed immediate offset range (512) क्रम stp
 * inकाष्ठाion so below macros takes CPU_APIAKEYLO_EL1 as base and
 * calculates the offset of the keys from this base to aव्योम an extra add
 * inकाष्ठाion. These macros assumes the keys offsets follow the order of
 * the sysreg क्रमागत in kvm_host.h.
 */
.macro	ptrauth_save_state base, reg1, reg2
	mrs_s	\लeg1, SYS_APIAKEYLO_EL1
	mrs_s	\लeg2, SYS_APIAKEYHI_EL1
	stp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APIAKEYLO_EL1)]
	mrs_s	\लeg1, SYS_APIBKEYLO_EL1
	mrs_s	\लeg2, SYS_APIBKEYHI_EL1
	stp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APIBKEYLO_EL1)]
	mrs_s	\लeg1, SYS_APDAKEYLO_EL1
	mrs_s	\लeg2, SYS_APDAKEYHI_EL1
	stp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APDAKEYLO_EL1)]
	mrs_s	\लeg1, SYS_APDBKEYLO_EL1
	mrs_s	\लeg2, SYS_APDBKEYHI_EL1
	stp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APDBKEYLO_EL1)]
	mrs_s	\लeg1, SYS_APGAKEYLO_EL1
	mrs_s	\लeg2, SYS_APGAKEYHI_EL1
	stp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APGAKEYLO_EL1)]
.endm

.macro	ptrauth_restore_state base, reg1, reg2
	ldp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APIAKEYLO_EL1)]
	msr_s	SYS_APIAKEYLO_EL1, \लeg1
	msr_s	SYS_APIAKEYHI_EL1, \लeg2
	ldp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APIBKEYLO_EL1)]
	msr_s	SYS_APIBKEYLO_EL1, \लeg1
	msr_s	SYS_APIBKEYHI_EL1, \लeg2
	ldp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APDAKEYLO_EL1)]
	msr_s	SYS_APDAKEYLO_EL1, \लeg1
	msr_s	SYS_APDAKEYHI_EL1, \लeg2
	ldp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APDBKEYLO_EL1)]
	msr_s	SYS_APDBKEYLO_EL1, \लeg1
	msr_s	SYS_APDBKEYHI_EL1, \लeg2
	ldp	\लeg1, \लeg2, [\मase, #PTRAUTH_REG_OFFSET(CPU_APGAKEYLO_EL1)]
	msr_s	SYS_APGAKEYLO_EL1, \लeg1
	msr_s	SYS_APGAKEYHI_EL1, \लeg2
.endm

/*
 * Both ptrauth_चयन_to_guest and ptrauth_चयन_to_hyp macros will
 * check क्रम the presence ARM64_HAS_ADDRESS_AUTH, which is defined as
 * (ARM64_HAS_ADDRESS_AUTH_ARCH || ARM64_HAS_ADDRESS_AUTH_IMP_DEF) and
 * then proceed ahead with the save/restore of Poपूर्णांकer Authentication
 * key रेजिस्टरs अगर enabled क्रम the guest.
 */
.macro ptrauth_चयन_to_guest g_ctxt, reg1, reg2, reg3
alternative_अगर_not ARM64_HAS_ADDRESS_AUTH
	b	.L__skip_चयन\@
alternative_अन्यथा_nop_endअगर
	mrs	\लeg1, hcr_el2
	and	\लeg1, \लeg1, #(HCR_API | HCR_APK)
	cbz	\लeg1, .L__skip_चयन\@
	add	\लeg1, \g_ctxt, #CPU_APIAKEYLO_EL1
	ptrauth_restore_state	\लeg1, \लeg2, \लeg3
.L__skip_चयन\@:
.endm

.macro ptrauth_चयन_to_hyp g_ctxt, h_ctxt, reg1, reg2, reg3
alternative_अगर_not ARM64_HAS_ADDRESS_AUTH
	b	.L__skip_चयन\@
alternative_अन्यथा_nop_endअगर
	mrs	\लeg1, hcr_el2
	and	\लeg1, \लeg1, #(HCR_API | HCR_APK)
	cbz	\लeg1, .L__skip_चयन\@
	add	\लeg1, \g_ctxt, #CPU_APIAKEYLO_EL1
	ptrauth_save_state	\लeg1, \लeg2, \लeg3
	add	\लeg1, \h_ctxt, #CPU_APIAKEYLO_EL1
	ptrauth_restore_state	\लeg1, \लeg2, \लeg3
	isb
.L__skip_चयन\@:
.endm

#अन्यथा /* !CONFIG_ARM64_PTR_AUTH */
.macro ptrauth_चयन_to_guest g_ctxt, reg1, reg2, reg3
.endm
.macro ptrauth_चयन_to_hyp g_ctxt, h_ctxt, reg1, reg2, reg3
.endm
#पूर्ण_अगर /* CONFIG_ARM64_PTR_AUTH */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_KVM_PTRAUTH_H */
