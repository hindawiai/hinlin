<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* यंत्रmacro.h: Assembler macros.
 *
 * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)
 */

#अगर_अघोषित _SPARC_ASMMACRO_H
#घोषणा _SPARC_ASMMACRO_H

/* All trap entry poपूर्णांकs _must_ begin with this macro or अन्यथा you
 * lose.  It makes sure the kernel has a proper winकरोw so that
 * c-code can be called.
 */
#घोषणा SAVE_ALL_HEAD \
	sethi	%hi(trap_setup), %l4; \
	jmpl	%l4 + %lo(trap_setup), %l6;
#घोषणा SAVE_ALL \
	SAVE_ALL_HEAD \
	 nop;

/* All traps low-level code here must end with this macro. */
#घोषणा RESTORE_ALL b ret_trap_entry; clr %l6;

/* Support क्रम run-समय patching of single inकाष्ठाions.
 * This is used to handle the dअगरferences in the ASI क्रम
 * MMUREGS क्रम LEON and SUN.
 *
 * Sample:
 * LEON_PI(lda [%g0] ASI_LEON_MMUREGS, %o0
 * SUN_PI_(lda [%g0] ASI_M_MMUREGS, %o0
 * PI == Patch Inकाष्ठाion
 *
 * For LEON we will use the first variant,
 * and क्रम all other we will use the SUN variant.
 * The order is important.
 */
#घोषणा LEON_PI(...)				\
662:	__VA_ARGS__

#घोषणा SUN_PI_(...)				\
	.section .leon_1insn_patch, "ax";	\
	.word 662b;				\
	__VA_ARGS__;				\
	.previous

#पूर्ण_अगर /* !(_SPARC_ASMMACRO_H) */
