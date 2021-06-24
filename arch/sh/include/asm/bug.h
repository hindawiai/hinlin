<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BUG_H
#घोषणा __ASM_SH_BUG_H

#समावेश <linux/linkage.h>

#घोषणा TRAPA_BUG_OPCODE	0xc33e	/* trapa #0x3e */
#घोषणा BUGFLAG_UNWINDER	(1 << 1)

#अगर_घोषित CONFIG_GENERIC_BUG
#घोषणा HAVE_ARCH_BUG
#घोषणा HAVE_ARCH_WARN_ON

/**
 * _EMIT_BUG_ENTRY
 * %1 - __खाता__
 * %2 - __LINE__
 * %3 - trap type
 * %4 - माप(काष्ठा bug_entry)
 *
 * The trapa opcode itself sits in %0.
 * The %O notation is used to aव्योम # generation.
 *
 * The offending file and line are encoded in the __bug_table section.
 */
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#घोषणा _EMIT_BUG_ENTRY				\
	"\t.pushsection __bug_table,\"aw\"\n"	\
	"2:\t.long 1b, %O1\n"			\
	"\t.short %O2, %O3\n"			\
	"\t.org 2b+%O4\n"			\
	"\t.popsection\n"
#अन्यथा
#घोषणा _EMIT_BUG_ENTRY				\
	"\t.pushsection __bug_table,\"aw\"\n"	\
	"2:\t.long 1b\n"			\
	"\t.short %O3\n"			\
	"\t.org 2b+%O4\n"			\
	"\t.popsection\n"
#पूर्ण_अगर

#घोषणा BUG()						\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
		"1:\t.short %O0\n"			\
		_EMIT_BUG_ENTRY				\
		 :					\
		 : "n" (TRAPA_BUG_OPCODE),		\
		   "i" (__खाता__),			\
		   "i" (__LINE__), "i" (0),		\
		   "i" (माप(काष्ठा bug_entry)));	\
	unreachable();					\
पूर्ण जबतक (0)

#घोषणा __WARN_FLAGS(flags)				\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
		"1:\t.short %O0\n"			\
		 _EMIT_BUG_ENTRY			\
		 :					\
		 : "n" (TRAPA_BUG_OPCODE),		\
		   "i" (__खाता__),			\
		   "i" (__LINE__),			\
		   "i" (BUGFLAG_WARNING|(flags)),	\
		   "i" (माप(काष्ठा bug_entry)));	\
पूर्ण जबतक (0)

#घोषणा WARN_ON(x) (अणु						\
	पूर्णांक __ret_warn_on = !!(x);				\
	अगर (__builtin_स्थिरant_p(__ret_warn_on)) अणु		\
		अगर (__ret_warn_on)				\
			__WARN();				\
	पूर्ण अन्यथा अणु						\
		अगर (unlikely(__ret_warn_on))			\
			__WARN();				\
	पूर्ण							\
	unlikely(__ret_warn_on);				\
पूर्ण)

#घोषणा UNWINDER_BUG()					\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
		"1:\t.short %O0\n"			\
		_EMIT_BUG_ENTRY				\
		 :					\
		 : "n" (TRAPA_BUG_OPCODE),		\
		   "i" (__खाता__),			\
		   "i" (__LINE__),			\
		   "i" (BUGFLAG_UNWINDER),		\
		   "i" (माप(काष्ठा bug_entry)));	\
पूर्ण जबतक (0)

#घोषणा UNWINDER_BUG_ON(x) (अणु					\
	पूर्णांक __ret_unwinder_on = !!(x);				\
	अगर (__builtin_स्थिरant_p(__ret_unwinder_on)) अणु		\
		अगर (__ret_unwinder_on)				\
			UNWINDER_BUG();				\
	पूर्ण अन्यथा अणु						\
		अगर (unlikely(__ret_unwinder_on))		\
			UNWINDER_BUG();				\
	पूर्ण							\
	unlikely(__ret_unwinder_on);				\
पूर्ण)

#अन्यथा

#घोषणा UNWINDER_BUG	BUG
#घोषणा UNWINDER_BUG_ON	BUG_ON

#पूर्ण_अगर /* CONFIG_GENERIC_BUG */

#समावेश <यंत्र-generic/bug.h>

काष्ठा pt_regs;

/* arch/sh/kernel/traps.c */
बाह्य व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err) __attribute__ ((noवापस));
बाह्य व्योम die_अगर_kernel(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err);
बाह्य व्योम die_अगर_no_fixup(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err);

#पूर्ण_अगर /* __ASM_SH_BUG_H */
