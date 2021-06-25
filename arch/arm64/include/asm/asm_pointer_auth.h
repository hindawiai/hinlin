<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ASM_POINTER_AUTH_H
#घोषणा __ASM_ASM_POINTER_AUTH_H

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/sysreg.h>

#अगर_घोषित CONFIG_ARM64_PTR_AUTH
/*
 * thपढ़ो.keys_user.ap* as offset exceeds the #imm offset range
 * so use the base value of ldp as thपढ़ो.keys_user and offset as
 * thपढ़ो.keys_user.ap*.
 */
	.macro __ptrauth_keys_install_user tsk, पंचांगp1, पंचांगp2, पंचांगp3
	mov	\टmp1, #THREAD_KEYS_USER
	add	\टmp1, \टsk, \टmp1
	ldp	\टmp2, \टmp3, [\टmp1, #PTRAUTH_USER_KEY_APIA]
	msr_s	SYS_APIAKEYLO_EL1, \टmp2
	msr_s	SYS_APIAKEYHI_EL1, \टmp3
	.endm

	.macro __ptrauth_keys_install_kernel_nosync tsk, पंचांगp1, पंचांगp2, पंचांगp3
	mov	\टmp1, #THREAD_KEYS_KERNEL
	add	\टmp1, \टsk, \टmp1
	ldp	\टmp2, \टmp3, [\टmp1, #PTRAUTH_KERNEL_KEY_APIA]
	msr_s	SYS_APIAKEYLO_EL1, \टmp2
	msr_s	SYS_APIAKEYHI_EL1, \टmp3
	.endm

	.macro ptrauth_keys_install_kernel_nosync tsk, पंचांगp1, पंचांगp2, पंचांगp3
alternative_अगर ARM64_HAS_ADDRESS_AUTH
	__ptrauth_keys_install_kernel_nosync \टsk, \टmp1, \टmp2, \टmp3
alternative_अन्यथा_nop_endअगर
	.endm

	.macro ptrauth_keys_install_kernel tsk, पंचांगp1, पंचांगp2, पंचांगp3
alternative_अगर ARM64_HAS_ADDRESS_AUTH
	__ptrauth_keys_install_kernel_nosync \टsk, \टmp1, \टmp2, \टmp3
	isb
alternative_अन्यथा_nop_endअगर
	.endm

	.macro __ptrauth_keys_init_cpu tsk, पंचांगp1, पंचांगp2, पंचांगp3
	mrs	\टmp1, id_aa64isar1_el1
	ubfx	\टmp1, \टmp1, #ID_AA64ISAR1_APA_SHIFT, #8
	cbz	\टmp1, .Lno_addr_auth\@
	mov_q	\टmp1, (SCTLR_ELx_ENIA | SCTLR_ELx_ENIB | \
			SCTLR_ELx_ENDA | SCTLR_ELx_ENDB)
	mrs	\टmp2, sctlr_el1
	orr	\टmp2, \टmp2, \टmp1
	msr	sctlr_el1, \टmp2
	__ptrauth_keys_install_kernel_nosync \टsk, \टmp1, \टmp2, \टmp3
	isb
.Lno_addr_auth\@:
	.endm

	.macro ptrauth_keys_init_cpu tsk, पंचांगp1, पंचांगp2, पंचांगp3
alternative_अगर_not ARM64_HAS_ADDRESS_AUTH
	b	.Lno_addr_auth\@
alternative_अन्यथा_nop_endअगर
	__ptrauth_keys_init_cpu \टsk, \टmp1, \टmp2, \टmp3
.Lno_addr_auth\@:
	.endm

#अन्यथा /* CONFIG_ARM64_PTR_AUTH */

	.macro ptrauth_keys_install_user tsk, पंचांगp1, पंचांगp2, पंचांगp3
	.endm

	.macro ptrauth_keys_install_kernel_nosync tsk, पंचांगp1, पंचांगp2, पंचांगp3
	.endm

	.macro ptrauth_keys_install_kernel tsk, पंचांगp1, पंचांगp2, पंचांगp3
	.endm

#पूर्ण_अगर /* CONFIG_ARM64_PTR_AUTH */

#पूर्ण_अगर /* __ASM_ASM_POINTER_AUTH_H */
