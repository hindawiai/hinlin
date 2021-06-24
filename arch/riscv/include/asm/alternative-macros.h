<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ALTERNATIVE_MACROS_H
#घोषणा __ASM_ALTERNATIVE_MACROS_H

#अगर_घोषित CONFIG_RISCV_ERRATA_ALTERNATIVE

#अगर_घोषित __ASSEMBLY__

.macro ALT_ENTRY oldptr newptr venकरोr_id errata_id new_len
	RISCV_PTR \oldptr
	RISCV_PTR \नewptr
	REG_ASM \खenकरोr_id
	REG_ASM \नew_len
	.word	\errata_id
.endm

.macro ALT_NEW_CONTENT venकरोr_id, errata_id, enable = 1, new_c : vararg
	.अगर \enable
	.pushsection .alternative, "a"
	ALT_ENTRY 886b, 888f, \खenकरोr_id, \errata_id, 889f - 888f
	.popsection
	.subsection 1
888 :
	\नew_c
889 :
	.previous
	.org    . - (889b - 888b) + (887b - 886b)
	.org    . - (887b - 886b) + (889b - 888b)
	.endअगर
.endm

.macro __ALTERNATIVE_CFG old_c, new_c, venकरोr_id, errata_id, enable
886 :
	\old_c
887 :
	ALT_NEW_CONTENT \खenकरोr_id, \errata_id, \enable, \नew_c
.endm

#घोषणा _ALTERNATIVE_CFG(old_c, new_c, venकरोr_id, errata_id, CONFIG_k) \
	__ALTERNATIVE_CFG old_c, new_c, venकरोr_id, errata_id, IS_ENABLED(CONFIG_k)

#अन्यथा /* !__ASSEMBLY__ */

#समावेश <यंत्र/यंत्र.h>
#समावेश <linux/stringअगरy.h>

#घोषणा ALT_ENTRY(oldptr, newptr, venकरोr_id, errata_id, newlen) \
	RISCV_PTR " " oldptr "\n" \
	RISCV_PTR " " newptr "\n" \
	REG_ASM " " venकरोr_id "\n" \
	REG_ASM " " newlen "\n" \
	".word " errata_id "\n"

#घोषणा ALT_NEW_CONTENT(venकरोr_id, errata_id, enable, new_c) \
	".if " __stringअगरy(enable) " == 1\n"				\
	".pushsection .alternative, \"a\"\n"				\
	ALT_ENTRY("886b", "888f", __stringअगरy(venकरोr_id), __stringअगरy(errata_id), "889f - 888f") \
	".popsection\n"							\
	".subsection 1\n"						\
	"888 :\n"							\
	new_c "\n"							\
	"889 :\n"							\
	".previous\n"							\
	".org	. - (887b - 886b) + (889b - 888b)\n"			\
	".org	. - (889b - 888b) + (887b - 886b)\n"			\
	".endif\n"

#घोषणा __ALTERNATIVE_CFG(old_c, new_c, venकरोr_id, errata_id, enable) \
	"886 :\n"	\
	old_c "\n"	\
	"887 :\n"	\
	ALT_NEW_CONTENT(venकरोr_id, errata_id, enable, new_c)

#घोषणा _ALTERNATIVE_CFG(old_c, new_c, venकरोr_id, errata_id, CONFIG_k)	\
	__ALTERNATIVE_CFG(old_c, new_c, venकरोr_id, errata_id, IS_ENABLED(CONFIG_k))

#पूर्ण_अगर /* __ASSEMBLY__ */

#अन्यथा /* !CONFIG_RISCV_ERRATA_ALTERNATIVE*/
#अगर_घोषित __ASSEMBLY__

.macro __ALTERNATIVE_CFG old_c
	\old_c
.endm

#घोषणा _ALTERNATIVE_CFG(old_c, new_c, venकरोr_id, errata_id, CONFIG_k) \
	__ALTERNATIVE_CFG old_c

#अन्यथा /* !__ASSEMBLY__ */

#घोषणा __ALTERNATIVE_CFG(old_c)  \
	old_c "\n"

#घोषणा _ALTERNATIVE_CFG(old_c, new_c, venकरोr_id, errata_id, CONFIG_k) \
	__ALTERNATIVE_CFG(old_c)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_RISCV_ERRATA_ALTERNATIVE */
/*
 * Usage:
 *   ALTERNATIVE(old_content, new_content, venकरोr_id, errata_id, CONFIG_k)
 * in the assembly code. Otherwise,
 *   यंत्र(ALTERNATIVE(old_content, new_content, venकरोr_id, errata_id, CONFIG_k));
 *
 * old_content: The old content which is probably replaced with new content.
 * new_content: The new content.
 * venकरोr_id: The CPU venकरोr ID.
 * errata_id: The errata ID.
 * CONFIG_k: The Kconfig of this errata. When Kconfig is disabled, the old
 *	     content will alwyas be executed.
 */
#घोषणा ALTERNATIVE(old_content, new_content, venकरोr_id, errata_id, CONFIG_k) \
	_ALTERNATIVE_CFG(old_content, new_content, venकरोr_id, errata_id, CONFIG_k)

/*
 * A venकरोr wants to replace an old_content, but another venकरोr has used
 * ALTERNATIVE() to patch its customized content at the same location. In
 * this हाल, this venकरोr can create a new macro ALTERNATIVE_2() based
 * on the following sample code and then replace ALTERNATIVE() with
 * ALTERNATIVE_2() to append its customized content.
 *
 * .macro __ALTERNATIVE_CFG_2 old_c, new_c_1, venकरोr_id_1, errata_id_1, enable_1, \
 *                                   new_c_2, venकरोr_id_2, errata_id_2, enable_2
 * 886 :
 *      \old_c
 * 887 :
 *      ALT_NEW_CONTENT \खenकरोr_id_1, \errata_id_1, \enable_1, \नew_c_1
 *      ALT_NEW_CONTENT \खenकरोr_id_2, \errata_id_2, \enable_2, \नew_c_2
 * .endm
 *
 * #घोषणा _ALTERNATIVE_CFG_2(old_c, new_c_1, venकरोr_id_1, errata_id_1, CONFIG_k_1, \
 *                                   new_c_2, venकरोr_id_2, errata_id_2, CONFIG_k_2) \
 *        __ALTERNATIVE_CFG_2 old_c, new_c_1, venकरोr_id_1, errata_id_1, IS_ENABLED(CONFIG_k_1), \
 *                                   new_c_2, venकरोr_id_2, errata_id_2, IS_ENABLED(CONFIG_k_2) \
 *
 * #घोषणा ALTERNATIVE_2(old_content, new_content_1, venकरोr_id_1, errata_id_1, CONFIG_k_1, \
 *                                    new_content_2, venकरोr_id_2, errata_id_2, CONFIG_k_2) \
 *         _ALTERNATIVE_CFG_2(old_content, new_content_1, venकरोr_id_1, errata_id_1, CONFIG_k_1, \
 *                                         new_content_2, venकरोr_id_2, errata_id_2, CONFIG_k_2)
 *
 */
#पूर्ण_अगर
