<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BUG_H
#घोषणा _ASM_POWERPC_BUG_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/यंत्र-compat.h>

#अगर_घोषित CONFIG_BUG

#अगर_घोषित __ASSEMBLY__
#समावेश <यंत्र/यंत्र-offsets.h>
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
.macro EMIT_BUG_ENTRY addr,file,line,flags
	 .section __bug_table,"aw"
5001:	 .4byte \चddr - 5001b, 5002f - 5001b
	 .लघु \line, \पlags
	 .org 5001b+BUG_ENTRY_SIZE
	 .previous
	 .section .rodata,"a"
5002:	 .asciz "\file"
	 .previous
.endm
#अन्यथा
.macro EMIT_BUG_ENTRY addr,file,line,flags
	 .section __bug_table,"aw"
5001:	 .4byte \चddr - 5001b
	 .लघु \पlags
	 .org 5001b+BUG_ENTRY_SIZE
	 .previous
.endm
#पूर्ण_अगर /* verbose */

#अन्यथा /* !__ASSEMBLY__ */
/* _EMIT_BUG_ENTRY expects args %0,%1,%2,%3 to be खाता, LINE, flags and
   माप(काष्ठा bug_entry), respectively */
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#घोषणा _EMIT_BUG_ENTRY				\
	".section __bug_table,\"aw\"\n"		\
	"2:\t.4byte 1b - 2b, %0 - 2b\n"		\
	"\t.short %1, %2\n"			\
	".org 2b+%3\n"				\
	".previous\n"
#अन्यथा
#घोषणा _EMIT_BUG_ENTRY				\
	".section __bug_table,\"aw\"\n"		\
	"2:\t.4byte 1b - 2b\n"			\
	"\t.short %2\n"				\
	".org 2b+%3\n"				\
	".previous\n"
#पूर्ण_अगर

#घोषणा BUG_ENTRY(insn, flags, ...)			\
	__यंत्र__ __अस्थिर__(				\
		"1:	" insn "\n"			\
		_EMIT_BUG_ENTRY				\
		: : "i" (__खाता__), "i" (__LINE__),	\
		  "i" (flags),				\
		  "i" (माप(काष्ठा bug_entry)),	\
		  ##__VA_ARGS__)

/*
 * BUG_ON() and WARN_ON() करो their best to cooperate with compile-समय
 * optimisations. However depending on the complनिकासy of the condition
 * some compiler versions may not produce optimal results.
 */

#घोषणा BUG() करो अणु						\
	BUG_ENTRY("twi 31, 0, 0", 0);				\
	unreachable();						\
पूर्ण जबतक (0)

#घोषणा BUG_ON(x) करो अणु						\
	अगर (__builtin_स्थिरant_p(x)) अणु				\
		अगर (x)						\
			BUG();					\
	पूर्ण अन्यथा अणु						\
		BUG_ENTRY(PPC_TLNEI " %4, 0", 0, "r" ((__क्रमce दीर्घ)(x)));	\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा __WARN_FLAGS(flags) BUG_ENTRY("twi 31, 0, 0", BUGFLAG_WARNING | (flags))

#घोषणा WARN_ON(x) (अणु						\
	पूर्णांक __ret_warn_on = !!(x);				\
	अगर (__builtin_स्थिरant_p(__ret_warn_on)) अणु		\
		अगर (__ret_warn_on)				\
			__WARN();				\
	पूर्ण अन्यथा अणु						\
		BUG_ENTRY(PPC_TLNEI " %4, 0",			\
			  BUGFLAG_WARNING | BUGFLAG_TAINT(TAINT_WARN),	\
			  "r" (__ret_warn_on));	\
	पूर्ण							\
	unlikely(__ret_warn_on);				\
पूर्ण)

#घोषणा HAVE_ARCH_BUG
#घोषणा HAVE_ARCH_BUG_ON
#घोषणा HAVE_ARCH_WARN_ON
#पूर्ण_अगर /* __ASSEMBLY __ */
#अन्यथा
#अगर_घोषित __ASSEMBLY__
.macro EMIT_BUG_ENTRY addr,file,line,flags
.endm
#अन्यथा /* !__ASSEMBLY__ */
#घोषणा _EMIT_BUG_ENTRY
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_BUG */

#समावेश <यंत्र-generic/bug.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा pt_regs;
व्योम hash__करो_page_fault(काष्ठा pt_regs *);
व्योम bad_page_fault(काष्ठा pt_regs *, पूर्णांक);
बाह्य व्योम _exception(पूर्णांक, काष्ठा pt_regs *, पूर्णांक, अचिन्हित दीर्घ);
बाह्य व्योम _exception_pkey(काष्ठा pt_regs *, अचिन्हित दीर्घ, पूर्णांक);
बाह्य व्योम die(स्थिर अक्षर *, काष्ठा pt_regs *, दीर्घ);
व्योम die_mce(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err);
बाह्य bool die_will_crash(व्योम);
बाह्य व्योम panic_flush_kmsg_start(व्योम);
बाह्य व्योम panic_flush_kmsg_end(व्योम);
#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_BUG_H */
