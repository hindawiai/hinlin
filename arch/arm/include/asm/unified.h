<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/यंत्र-arm/unअगरied.h - Unअगरied Assembler Syntax helper macros
 *
 * Copyright (C) 2008 ARM Limited
 */

#अगर_अघोषित __ASM_UNIFIED_H
#घोषणा __ASM_UNIFIED_H

#अगर defined(__ASSEMBLY__)
	.syntax unअगरied
#अन्यथा
__यंत्र__(".syntax unified");
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_V7M
#घोषणा AR_CLASS(x...)
#घोषणा M_CLASS(x...)	x
#अन्यथा
#घोषणा AR_CLASS(x...)	x
#घोषणा M_CLASS(x...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_THUMB2_KERNEL

#अगर __GNUC__ < 4
#त्रुटि Thumb-2 kernel requires gcc >= 4
#पूर्ण_अगर

/* The CPSR bit describing the inकाष्ठाion set (Thumb) */
#घोषणा PSR_ISETSTATE	PSR_T_BIT

#घोषणा ARM(x...)
#घोषणा THUMB(x...)	x
#अगर_घोषित __ASSEMBLY__
#घोषणा W(instr)	instr.w
#अन्यथा
#घोषणा WASM(instr)	#instr ".w"
#पूर्ण_अगर

#अन्यथा	/* !CONFIG_THUMB2_KERNEL */

/* The CPSR bit describing the inकाष्ठाion set (ARM) */
#घोषणा PSR_ISETSTATE	0

#घोषणा ARM(x...)	x
#घोषणा THUMB(x...)
#अगर_घोषित __ASSEMBLY__
#घोषणा W(instr)	instr
#अन्यथा
#घोषणा WASM(instr)	#instr
#पूर्ण_अगर

#पूर्ण_अगर	/* CONFIG_THUMB2_KERNEL */

#पूर्ण_अगर	/* !__ASM_UNIFIED_H */
