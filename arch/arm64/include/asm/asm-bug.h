<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ASM_ASM_BUG_H
/*
 * Copyright (C) 2017  ARM Limited
 */
#घोषणा __ASM_ASM_BUG_H

#समावेश <यंत्र/brk-imm.h>

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#घोषणा _BUGVERBOSE_LOCATION(file, line) __BUGVERBOSE_LOCATION(file, line)
#घोषणा __BUGVERBOSE_LOCATION(file, line)			\
		.pushsection .rodata.str,"aMS",@progbits,1;	\
	14472:	.string file;					\
		.popsection;					\
								\
		.दीर्घ 14472b - 14470b;				\
		.लघु line;
#अन्यथा
#घोषणा _BUGVERBOSE_LOCATION(file, line)
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_BUG

#घोषणा __BUG_ENTRY(flags) 				\
		.pushsection __bug_table,"aw";		\
		.align 2;				\
	14470:	.दीर्घ 14471f - 14470b;			\
_BUGVERBOSE_LOCATION(__खाता__, __LINE__)		\
		.लघु flags; 				\
		.popsection;				\
	14471:
#अन्यथा
#घोषणा __BUG_ENTRY(flags)
#पूर्ण_अगर

#घोषणा ASM_BUG_FLAGS(flags)				\
	__BUG_ENTRY(flags)				\
	brk	BUG_BRK_IMM

#घोषणा ASM_BUG()	ASM_BUG_FLAGS(0)

#पूर्ण_अगर /* __ASM_ASM_BUG_H */
