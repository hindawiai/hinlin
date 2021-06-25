<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ALTERNATIVE_MACROS_H
#घोषणा __ASM_ALTERNATIVE_MACROS_H

#समावेश <यंत्र/cpucaps.h>

#घोषणा ARM64_CB_PATCH ARM64_NCAPS

/* A64 inकाष्ठाions are always 32 bits. */
#घोषणा	AARCH64_INSN_SIZE		4

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/stringअगरy.h>

#घोषणा ALTINSTR_ENTRY(feature)					              \
	" .word 661b - .\n"				/* label           */ \
	" .word 663f - .\n"				/* new inकाष्ठाion */ \
	" .hword " __stringअगरy(feature) "\n"		/* feature bit     */ \
	" .byte 662b-661b\n"				/* source len      */ \
	" .byte 664f-663f\n"				/* replacement len */

#घोषणा ALTINSTR_ENTRY_CB(feature, cb)					      \
	" .word 661b - .\n"				/* label           */ \
	" .word " __stringअगरy(cb) "- .\n"		/* callback */	      \
	" .hword " __stringअगरy(feature) "\n"		/* feature bit     */ \
	" .byte 662b-661b\n"				/* source len      */ \
	" .byte 664f-663f\n"				/* replacement len */

/*
 * alternative assembly primitive:
 *
 * If any of these .org directive fail, it means that insn1 and insn2
 * करोn't have the same length. This used to be written as
 *
 * .अगर ((664b-663b) != (662b-661b))
 * 	.error "Alternatives instruction length mismatch"
 * .endअगर
 *
 * but most assemblers die अगर insn1 or insn2 have a .inst. This should
 * be fixed in a binutils release posterior to 2.25.51.0.2 (anything
 * containing commit 4e4d08cf7399b606 or c1baaddf8861).
 *
 * Alternatives with callbacks करो not generate replacement inकाष्ठाions.
 */
#घोषणा __ALTERNATIVE_CFG(oldinstr, newinstr, feature, cfg_enabled)	\
	".if "__stringअगरy(cfg_enabled)" == 1\n"				\
	"661:\n\t"							\
	oldinstr "\n"							\
	"662:\n"							\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(feature)						\
	".popsection\n"							\
	".subsection 1\n"						\
	"663:\n\t"							\
	newinstr "\n"							\
	"664:\n\t"							\
	".org	. - (664b-663b) + (662b-661b)\n\t"			\
	".org	. - (662b-661b) + (664b-663b)\n\t"			\
	".previous\n"							\
	".endif\n"

#घोषणा __ALTERNATIVE_CFG_CB(oldinstr, feature, cfg_enabled, cb)	\
	".if "__stringअगरy(cfg_enabled)" == 1\n"				\
	"661:\n\t"							\
	oldinstr "\n"							\
	"662:\n"							\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY_CB(feature, cb)					\
	".popsection\n"							\
	"663:\n\t"							\
	"664:\n\t"							\
	".endif\n"

#घोषणा _ALTERNATIVE_CFG(oldinstr, newinstr, feature, cfg, ...)	\
	__ALTERNATIVE_CFG(oldinstr, newinstr, feature, IS_ENABLED(cfg))

#घोषणा ALTERNATIVE_CB(oldinstr, cb) \
	__ALTERNATIVE_CFG_CB(oldinstr, ARM64_CB_PATCH, 1, cb)
#अन्यथा

#समावेश <यंत्र/assembler.h>

.macro altinकाष्ठाion_entry orig_offset alt_offset feature orig_len alt_len
	.word \orig_offset - .
	.word \चlt_offset - .
	.hword \पeature
	.byte \orig_len
	.byte \चlt_len
.endm

.macro alternative_insn insn1, insn2, cap, enable = 1
	.अगर \enable
661:	\insn1
662:	.pushsection .altinकाष्ठाions, "a"
	altinकाष्ठाion_entry 661b, 663f, \cap, 662b-661b, 664f-663f
	.popsection
	.subsection 1
663:	\insn2
664:	.org	. - (664b-663b) + (662b-661b)
	.org	. - (662b-661b) + (664b-663b)
	.previous
	.endअगर
.endm

/*
 * Alternative sequences
 *
 * The code क्रम the हाल where the capability is not present will be
 * assembled and linked as normal. There are no restrictions on this
 * code.
 *
 * The code क्रम the हाल where the capability is present will be
 * assembled पूर्णांकo a special section to be used क्रम dynamic patching.
 * Code क्रम that हाल must:
 *
 * 1. Be exactly the same length (in bytes) as the शेष code
 *    sequence.
 *
 * 2. Not contain a branch target that is used outside of the
 *    alternative sequence it is defined in (branches पूर्णांकo an
 *    alternative sequence are not fixed up).
 */

/*
 * Begin an alternative code sequence.
 */
.macro alternative_अगर_not cap
	.set .Lयंत्र_alt_mode, 0
	.pushsection .altinकाष्ठाions, "a"
	altinकाष्ठाion_entry 661f, 663f, \cap, 662f-661f, 664f-663f
	.popsection
661:
.endm

.macro alternative_अगर cap
	.set .Lयंत्र_alt_mode, 1
	.pushsection .altinकाष्ठाions, "a"
	altinकाष्ठाion_entry 663f, 661f, \cap, 664f-663f, 662f-661f
	.popsection
	.subsection 1
	.align 2	/* So GAS knows label 661 is suitably aligned */
661:
.endm

.macro alternative_cb cb
	.set .Lयंत्र_alt_mode, 0
	.pushsection .altinकाष्ठाions, "a"
	altinकाष्ठाion_entry 661f, \cb, ARM64_CB_PATCH, 662f-661f, 0
	.popsection
661:
.endm

/*
 * Provide the other half of the alternative code sequence.
 */
.macro alternative_अन्यथा
662:
	.अगर .Lयंत्र_alt_mode==0
	.subsection 1
	.अन्यथा
	.previous
	.endअगर
663:
.endm

/*
 * Complete an alternative code sequence.
 */
.macro alternative_endअगर
664:
	.org	. - (664b-663b) + (662b-661b)
	.org	. - (662b-661b) + (664b-663b)
	.अगर .Lयंत्र_alt_mode==0
	.previous
	.endअगर
.endm

/*
 * Callback-based alternative epilogue
 */
.macro alternative_cb_end
662:
.endm

/*
 * Provides a trivial alternative or शेष sequence consisting solely
 * of NOPs. The number of NOPs is chosen स्वतःmatically to match the
 * previous हाल.
 */
.macro alternative_अन्यथा_nop_endअगर
alternative_अन्यथा
	nops	(662b-661b) / AARCH64_INSN_SIZE
alternative_endअगर
.endm

#घोषणा _ALTERNATIVE_CFG(insn1, insn2, cap, cfg, ...)	\
	alternative_insn insn1, insn2, cap, IS_ENABLED(cfg)

.macro user_alt, label, oldinstr, newinstr, cond
9999:	alternative_insn "\oldinstr", "\newinstr", \cond
	_यंत्र_extable 9999b, \label
.endm

#पूर्ण_अगर  /*  __ASSEMBLY__  */

/*
 * Usage: यंत्र(ALTERNATIVE(oldinstr, newinstr, feature));
 *
 * Usage: यंत्र(ALTERNATIVE(oldinstr, newinstr, feature, CONFIG_FOO));
 * N.B. If CONFIG_FOO is specअगरied, but not selected, the whole block
 *      will be omitted, including oldinstr.
 */
#घोषणा ALTERNATIVE(oldinstr, newinstr, ...)   \
	_ALTERNATIVE_CFG(oldinstr, newinstr, __VA_ARGS__, 1)

#पूर्ण_अगर /* __ASM_ALTERNATIVE_MACROS_H */
