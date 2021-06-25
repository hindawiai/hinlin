<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_BUG_H
#घोषणा _PARISC_BUG_H

#समावेश <linux/kernel.h>	/* क्रम BUGFLAG_TAINT */

/*
 * Tell the user there is some problem.
 * The offending file and line are encoded in the __bug_table section.
 */

#अगर_घोषित CONFIG_BUG
#घोषणा HAVE_ARCH_BUG
#घोषणा HAVE_ARCH_WARN_ON

/* the अवरोध inकाष्ठाion is used as BUG() marker.  */
#घोषणा	PARISC_BUG_BREAK_ASM	"break 0x1f, 0x1fff"
#घोषणा	PARISC_BUG_BREAK_INSN	0x03ffe01f  /* PARISC_BUG_BREAK_ASM */

#अगर defined(CONFIG_64BIT)
#घोषणा ASM_WORD_INSN		".dword\t"
#अन्यथा
#घोषणा ASM_WORD_INSN		".word\t"
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#घोषणा BUG()								\
	करो अणु								\
		यंत्र अस्थिर("\n"					\
			     "1:\t" PARISC_BUG_BREAK_ASM "\n"		\
			     "\t.pushsection __bug_table,\"aw\"\n"	\
			     "2:\t" ASM_WORD_INSN "1b, %c0\n"		\
			     "\t.short %c1, %c2\n"			\
			     "\t.org 2b+%c3\n"				\
			     "\t.popsection"				\
			     : : "i" (__खाता__), "i" (__LINE__),	\
			     "i" (0), "i" (माप(काष्ठा bug_entry)) ); \
		unreachable();						\
	पूर्ण जबतक(0)

#अन्यथा
#घोषणा BUG()								\
	करो अणु								\
		यंत्र अस्थिर(PARISC_BUG_BREAK_ASM : : );		\
		unreachable();						\
	पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#घोषणा __WARN_FLAGS(flags)						\
	करो अणु								\
		यंत्र अस्थिर("\n"					\
			     "1:\t" PARISC_BUG_BREAK_ASM "\n"		\
			     "\t.pushsection __bug_table,\"aw\"\n"	\
			     "2:\t" ASM_WORD_INSN "1b, %c0\n"		\
			     "\t.short %c1, %c2\n"			\
			     "\t.org 2b+%c3\n"				\
			     "\t.popsection"				\
			     : : "i" (__खाता__), "i" (__LINE__),	\
			     "i" (BUGFLAG_WARNING|(flags)),		\
			     "i" (माप(काष्ठा bug_entry)) );		\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा __WARN_FLAGS(flags)						\
	करो अणु								\
		यंत्र अस्थिर("\n"					\
			     "1:\t" PARISC_BUG_BREAK_ASM "\n"		\
			     "\t.pushsection __bug_table,\"aw\"\n"	\
			     "2:\t" ASM_WORD_INSN "1b\n"		\
			     "\t.short %c0\n"				\
			     "\t.org 2b+%c1\n"				\
			     "\t.popsection"				\
			     : : "i" (BUGFLAG_WARNING|(flags)),		\
			     "i" (माप(काष्ठा bug_entry)) );		\
	पूर्ण जबतक(0)
#पूर्ण_अगर


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

#पूर्ण_अगर

#समावेश <यंत्र-generic/bug.h>
#पूर्ण_अगर

