<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_BUG_H
#घोषणा _ASM_RISCV_BUG_H

#समावेश <linux/compiler.h>
#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/यंत्र.h>

#घोषणा __INSN_LENGTH_MASK  _UL(0x3)
#घोषणा __INSN_LENGTH_32    _UL(0x3)
#घोषणा __COMPRESSED_INSN_MASK	_UL(0xffff)

#घोषणा __BUG_INSN_32	_UL(0x00100073) /* eअवरोध */
#घोषणा __BUG_INSN_16	_UL(0x9002) /* c.eअवरोध */

#घोषणा GET_INSN_LENGTH(insn)						\
(अणु									\
	अचिन्हित दीर्घ __len;						\
	__len = ((insn & __INSN_LENGTH_MASK) == __INSN_LENGTH_32) ?	\
		4UL : 2UL;						\
	__len;								\
पूर्ण)

प्रकार u32 bug_insn_t;

#अगर_घोषित CONFIG_GENERIC_BUG_RELATIVE_POINTERS
#घोषणा __BUG_ENTRY_ADDR	RISCV_INT " 1b - 2b"
#घोषणा __BUG_ENTRY_खाता	RISCV_INT " %0 - 2b"
#अन्यथा
#घोषणा __BUG_ENTRY_ADDR	RISCV_PTR " 1b"
#घोषणा __BUG_ENTRY_खाता	RISCV_PTR " %0"
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#घोषणा __BUG_ENTRY			\
	__BUG_ENTRY_ADDR "\n\t"		\
	__BUG_ENTRY_खाता "\n\t"		\
	RISCV_SHORT " %1\n\t"		\
	RISCV_SHORT " %2"
#अन्यथा
#घोषणा __BUG_ENTRY			\
	__BUG_ENTRY_ADDR "\n\t"		\
	RISCV_SHORT " %2"
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_BUG
#घोषणा __BUG_FLAGS(flags)					\
करो अणु								\
	__यंत्र__ __अस्थिर__ (					\
		"1:\n\t"					\
			"ebreak\n"				\
			".pushsection __bug_table,\"aw\"\n\t"	\
		"2:\n\t"					\
			__BUG_ENTRY "\n\t"			\
			".org 2b + %3\n\t"                      \
			".popsection"				\
		:						\
		: "i" (__खाता__), "i" (__LINE__),		\
		  "i" (flags),					\
		  "i" (माप(काष्ठा bug_entry)));              \
पूर्ण जबतक (0)
#अन्यथा /* CONFIG_GENERIC_BUG */
#घोषणा __BUG_FLAGS(flags) करो अणु					\
	__यंत्र__ __अस्थिर__ ("ebreak\n");			\
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_GENERIC_BUG */

#घोषणा BUG() करो अणु						\
	__BUG_FLAGS(0);						\
	unreachable();						\
पूर्ण जबतक (0)

#घोषणा __WARN_FLAGS(flags) __BUG_FLAGS(BUGFLAG_WARNING|(flags))

#घोषणा HAVE_ARCH_BUG

#समावेश <यंत्र-generic/bug.h>

काष्ठा pt_regs;
काष्ठा task_काष्ठा;

व्योम __show_regs(काष्ठा pt_regs *regs);
व्योम die(काष्ठा pt_regs *regs, स्थिर अक्षर *str);
व्योम करो_trap(काष्ठा pt_regs *regs, पूर्णांक signo, पूर्णांक code, अचिन्हित दीर्घ addr);

#पूर्ण_अगर /* _ASM_RISCV_BUG_H */
