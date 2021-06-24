<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ASM_UACCESS_H
#घोषणा __ASM_ASM_UACCESS_H

#समावेश <यंत्र/alternative-macros.h>
#समावेश <यंत्र/kernel-pgtable.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/assembler.h>

/*
 * User access enabling/disabling macros.
 */
#अगर_घोषित CONFIG_ARM64_SW_TTBR0_PAN
	.macro	__uaccess_ttbr0_disable, पंचांगp1
	mrs	\टmp1, ttbr1_el1			// swapper_pg_dir
	bic	\टmp1, \टmp1, #TTBR_ASID_MASK
	sub	\टmp1, \टmp1, #RESERVED_SWAPPER_OFFSET	// reserved_pg_dir
	msr	ttbr0_el1, \टmp1			// set reserved TTBR0_EL1
	isb
	add	\टmp1, \टmp1, #RESERVED_SWAPPER_OFFSET
	msr	ttbr1_el1, \टmp1		// set reserved ASID
	isb
	.endm

	.macro	__uaccess_ttbr0_enable, पंचांगp1, पंचांगp2
	get_current_task \टmp1
	ldr	\टmp1, [\टmp1, #TSK_TI_TTBR0]	// load saved TTBR0_EL1
	mrs	\टmp2, ttbr1_el1
	extr    \टmp2, \टmp2, \टmp1, #48
	ror     \टmp2, \टmp2, #16
	msr	ttbr1_el1, \टmp2		// set the active ASID
	isb
	msr	ttbr0_el1, \टmp1		// set the non-PAN TTBR0_EL1
	isb
	.endm

	.macro	uaccess_ttbr0_disable, पंचांगp1, पंचांगp2
alternative_अगर_not ARM64_HAS_PAN
	save_and_disable_irq \टmp2		// aव्योम preemption
	__uaccess_ttbr0_disable \टmp1
	restore_irq \टmp2
alternative_अन्यथा_nop_endअगर
	.endm

	.macro	uaccess_ttbr0_enable, पंचांगp1, पंचांगp2, पंचांगp3
alternative_अगर_not ARM64_HAS_PAN
	save_and_disable_irq \टmp3		// aव्योम preemption
	__uaccess_ttbr0_enable \टmp1, \टmp2
	restore_irq \टmp3
alternative_अन्यथा_nop_endअगर
	.endm
#अन्यथा
	.macro	uaccess_ttbr0_disable, पंचांगp1, पंचांगp2
	.endm

	.macro	uaccess_ttbr0_enable, पंचांगp1, पंचांगp2, पंचांगp3
	.endm
#पूर्ण_अगर

/*
 * Generate the assembly क्रम LDTR/STTR with exception table entries.
 * This is complicated as there is no post-increment or pair versions of the
 * unprivileged inकाष्ठाions, and USER() only works क्रम single inकाष्ठाions.
 */
	.macro user_ldp l, reg1, reg2, addr, post_inc
8888:		ldtr	\लeg1, [\चddr];
8889:		ldtr	\लeg2, [\चddr, #8];
		add	\चddr, \चddr, \post_inc;

		_यंत्र_extable	8888b,\l;
		_यंत्र_extable	8889b,\l;
	.endm

	.macro user_stp l, reg1, reg2, addr, post_inc
8888:		sttr	\लeg1, [\चddr];
8889:		sttr	\लeg2, [\चddr, #8];
		add	\चddr, \चddr, \post_inc;

		_यंत्र_extable	8888b,\l;
		_यंत्र_extable	8889b,\l;
	.endm

	.macro user_ldst l, inst, reg, addr, post_inc
8888:		\inst		\लeg, [\चddr];
		add		\चddr, \चddr, \post_inc;

		_यंत्र_extable	8888b,\l;
	.endm
#पूर्ण_अगर
