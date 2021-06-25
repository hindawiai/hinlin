<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PARISC_LINKAGE_H
#घोषणा __ASM_PARISC_LINKAGE_H

#समावेश <यंत्र/dwarf.h>

#अगर_अघोषित __ALIGN
#घोषणा __ALIGN         .align 4
#घोषणा __ALIGN_STR     ".align 4"
#पूर्ण_अगर

/*
 * In parisc assembly a semicolon marks a comment जबतक a
 * exclamation mark is used to separate independent lines.
 */
#घोषणा ASM_NL	!

#अगर_घोषित __ASSEMBLY__

#घोषणा ENTRY(name) \
	ALIGN	!\
name:		ASM_NL\
	.export name

#घोषणा ENTRY_CFI(name, ...) \
	ENTRY(name)	ASM_NL\
	.proc		ASM_NL\
	.callinfo __VA_ARGS__	ASM_NL\
	.entry		ASM_NL\
	CFI_STARTPROC

#घोषणा ENDPROC_CFI(name) \
	CFI_ENDPROC	ASM_NL\
	.निकास		ASM_NL\
	.procend	ASM_NL\
	ENDPROC(name)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर  /* __ASM_PARISC_LINKAGE_H */
