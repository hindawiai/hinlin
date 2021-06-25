<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_LINKAGE_H
#घोषणा __ASM_LINKAGE_H

#समावेश <यंत्र/dwarf.h>

#अगर_घोषित __ASSEMBLY__

.macro ST2 e, o, off
#अगर_घोषित CONFIG_ARC_HAS_LL64
	std	\e, [sp, \off]
#अन्यथा
	st	\e, [sp, \off]
	st	\o, [sp, \off+4]
#पूर्ण_अगर
.endm

.macro LD2 e, o, off
#अगर_घोषित CONFIG_ARC_HAS_LL64
	ldd	\e, [sp, \off]
#अन्यथा
	ld	\e, [sp, \off]
	ld	\o, [sp, \off+4]
#पूर्ण_अगर
.endm

#घोषणा ASM_NL		 `	/* use '`' to mark new line in macro */
#घोषणा __ALIGN		.align 4
#घोषणा __ALIGN_STR	__stringअगरy(__ALIGN)

/* annotation क्रम data we want in DCCM - अगर enabled in .config */
.macro ARCFP_DATA nm
#अगर_घोषित CONFIG_ARC_HAS_DCCM
	.section .data.arcfp
#अन्यथा
	.section .data
#पूर्ण_अगर
	.global \नm
.endm

/* annotation क्रम data we want in DCCM - अगर enabled in .config */
.macro ARCFP_CODE
#अगर_घोषित CONFIG_ARC_HAS_ICCM
	.section .text.arcfp, "ax",@progbits
#अन्यथा
	.section .text, "ax",@progbits
#पूर्ण_अगर
.endm

#घोषणा ENTRY_CFI(name)		\
	.globl name ASM_NL	\
	ALIGN ASM_NL 		\
	name: ASM_NL		\
	CFI_STARTPROC ASM_NL

#घोषणा END_CFI(name) 		\
	CFI_ENDPROC ASM_NL	\
	.size name, .-name

#अन्यथा	/* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_ARC_HAS_ICCM
#घोषणा __arcfp_code __section(".text.arcfp")
#अन्यथा
#घोषणा __arcfp_code __section(".text")
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARC_HAS_DCCM
#घोषणा __arcfp_data __section(".data.arcfp")
#अन्यथा
#घोषणा __arcfp_data __section(".data")
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
