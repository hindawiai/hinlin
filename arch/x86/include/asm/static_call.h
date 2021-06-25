<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_STATIC_CALL_H
#घोषणा _ASM_STATIC_CALL_H

#समावेश <यंत्र/text-patching.h>

/*
 * For CONFIG_HAVE_STATIC_CALL_INLINE, this is a temporary trampoline which
 * uses the current value of the key->func poपूर्णांकer to करो an indirect jump to
 * the function.  This trampoline is only used during boot, beक्रमe the call
 * sites get patched by अटल_call_update().  The name of this trampoline has
 * a magical aspect: objtool uses it to find अटल call sites so it can create
 * the .अटल_call_sites section.
 *
 * For CONFIG_HAVE_STATIC_CALL, this is a permanent trampoline which
 * करोes a direct jump to the function.  The direct jump माला_लो patched by
 * अटल_call_update().
 *
 * Having the trampoline in a special section क्रमces GCC to emit a JMP.d32 when
 * it करोes tail-call optimization on the call; since you cannot compute the
 * relative displacement across sections.
 */

#घोषणा __ARCH_DEFINE_STATIC_CALL_TRAMP(name, insns)			\
	यंत्र(".pushsection .static_call.text, \"ax\"		\n"	\
	    ".align 4						\n"	\
	    ".globl " STATIC_CALL_TRAMP_STR(name) "		\n"	\
	    STATIC_CALL_TRAMP_STR(name) ":			\n"	\
	    insns "						\n"	\
	    ".type " STATIC_CALL_TRAMP_STR(name) ", @function	\n"	\
	    ".size " STATIC_CALL_TRAMP_STR(name) ", . - " STATIC_CALL_TRAMP_STR(name) " \n" \
	    ".popsection					\n")

#घोषणा ARCH_DEFINE_STATIC_CALL_TRAMP(name, func)			\
	__ARCH_DEFINE_STATIC_CALL_TRAMP(name, ".byte 0xe9; .long " #func " - (. + 4)")

#घोषणा ARCH_DEFINE_STATIC_CALL_शून्य_TRAMP(name)			\
	__ARCH_DEFINE_STATIC_CALL_TRAMP(name, "ret; nop; nop; nop; nop")


#घोषणा ARCH_ADD_TRAMP_KEY(name)					\
	यंत्र(".pushsection .static_call_tramp_key, \"a\"		\n"	\
	    ".long " STATIC_CALL_TRAMP_STR(name) " - .		\n"	\
	    ".long " STATIC_CALL_KEY_STR(name) " - .		\n"	\
	    ".popsection					\n")

#पूर्ण_अगर /* _ASM_STATIC_CALL_H */
