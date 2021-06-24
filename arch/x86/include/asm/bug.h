<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BUG_H
#घोषणा _ASM_X86_BUG_H

#समावेश <linux/stringअगरy.h>
#समावेश <linux/instrumentation.h>

/*
 * Despite that some emulators terminate on UD2, we use it क्रम WARN().
 */
#घोषणा ASM_UD2		".byte 0x0f, 0x0b"
#घोषणा INSN_UD2	0x0b0f
#घोषणा LEN_UD2		2

#अगर_घोषित CONFIG_GENERIC_BUG

#अगर_घोषित CONFIG_X86_32
# define __BUG_REL(val)	".long " __stringअगरy(val)
#अन्यथा
# define __BUG_REL(val)	".long " __stringअगरy(val) " - 2b"
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE

#घोषणा _BUG_FLAGS(ins, flags)						\
करो अणु									\
	यंत्र_अंतरभूत अस्थिर("1:\t" ins "\n"				\
		     ".pushsection __bug_table,\"aw\"\n"		\
		     "2:\t" __BUG_REL(1b) "\t# bug_entry::bug_addr\n"	\
		     "\t"  __BUG_REL(%c0) "\t# bug_entry::file\n"	\
		     "\t.word %c1"        "\t# bug_entry::line\n"	\
		     "\t.word %c2"        "\t# bug_entry::flags\n"	\
		     "\t.org 2b+%c3\n"					\
		     ".popsection"					\
		     : : "i" (__खाता__), "i" (__LINE__),		\
			 "i" (flags),					\
			 "i" (माप(काष्ठा bug_entry)));		\
पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_DEBUG_BUGVERBOSE */

#घोषणा _BUG_FLAGS(ins, flags)						\
करो अणु									\
	यंत्र_अंतरभूत अस्थिर("1:\t" ins "\n"				\
		     ".pushsection __bug_table,\"aw\"\n"		\
		     "2:\t" __BUG_REL(1b) "\t# bug_entry::bug_addr\n"	\
		     "\t.word %c0"        "\t# bug_entry::flags\n"	\
		     "\t.org 2b+%c1\n"					\
		     ".popsection"					\
		     : : "i" (flags),					\
			 "i" (माप(काष्ठा bug_entry)));		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_DEBUG_BUGVERBOSE */

#अन्यथा

#घोषणा _BUG_FLAGS(ins, flags)  यंत्र अस्थिर(ins)

#पूर्ण_अगर /* CONFIG_GENERIC_BUG */

#घोषणा HAVE_ARCH_BUG
#घोषणा BUG()							\
करो अणु								\
	instrumentation_begin();				\
	_BUG_FLAGS(ASM_UD2, 0);					\
	unreachable();						\
पूर्ण जबतक (0)

/*
 * This instrumentation_begin() is strictly speaking incorrect; but it
 * suppresses the complaपूर्णांकs from WARN()s in noinstr code. If such a WARN()
 * were to trigger, we'd rather wreck the machine in an attempt to get the
 * message out than not know about it.
 */
#घोषणा __WARN_FLAGS(flags)					\
करो अणु								\
	instrumentation_begin();				\
	_BUG_FLAGS(ASM_UD2, BUGFLAG_WARNING|(flags));		\
	annotate_reachable();					\
	instrumentation_end();					\
पूर्ण जबतक (0)

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर /* _ASM_X86_BUG_H */
