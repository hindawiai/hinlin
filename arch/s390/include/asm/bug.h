<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_BUG_H
#घोषणा _ASM_S390_BUG_H

#समावेश <linux/compiler.h>

#अगर_घोषित CONFIG_BUG

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE

#घोषणा __EMIT_BUG(x) करो अणु					\
	यंत्र_अंतरभूत अस्थिर(					\
		"0:	mc	0,0\n"				\
		".section .rodata.str,\"aMS\",@progbits,1\n"	\
		"1:	.asciz	\""__खाता__"\"\n"		\
		".previous\n"					\
		".section __bug_table,\"awM\",@progbits,%2\n"	\
		"2:	.long	0b-2b,1b-2b\n"			\
		"	.short	%0,%1\n"			\
		"	.org	2b+%2\n"			\
		".previous\n"					\
		: : "i" (__LINE__),				\
		    "i" (x),					\
		    "i" (माप(काष्ठा bug_entry)));		\
पूर्ण जबतक (0)

#अन्यथा /* CONFIG_DEBUG_BUGVERBOSE */

#घोषणा __EMIT_BUG(x) करो अणु					\
	यंत्र_अंतरभूत अस्थिर(					\
		"0:	mc	0,0\n"				\
		".section __bug_table,\"awM\",@progbits,%1\n"	\
		"1:	.long	0b-1b\n"			\
		"	.short	%0\n"				\
		"	.org	1b+%1\n"			\
		".previous\n"					\
		: : "i" (x),					\
		    "i" (माप(काष्ठा bug_entry)));		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_DEBUG_BUGVERBOSE */

#घोषणा BUG() करो अणु					\
	__EMIT_BUG(0);					\
	unreachable();					\
पूर्ण जबतक (0)

#घोषणा __WARN_FLAGS(flags) करो अणु			\
	__EMIT_BUG(BUGFLAG_WARNING|(flags));		\
पूर्ण जबतक (0)

#घोषणा WARN_ON(x) (अणु					\
	पूर्णांक __ret_warn_on = !!(x);			\
	अगर (__builtin_स्थिरant_p(__ret_warn_on)) अणु	\
		अगर (__ret_warn_on)			\
			__WARN();			\
	पूर्ण अन्यथा अणु					\
		अगर (unlikely(__ret_warn_on))		\
			__WARN();			\
	पूर्ण						\
	unlikely(__ret_warn_on);			\
पूर्ण)

#घोषणा HAVE_ARCH_BUG
#घोषणा HAVE_ARCH_WARN_ON
#पूर्ण_अगर /* CONFIG_BUG */

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर /* _ASM_S390_BUG_H */
