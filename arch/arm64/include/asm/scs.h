<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SCS_H
#घोषणा _ASM_SCS_H

#अगर_घोषित __ASSEMBLY__

#समावेश <यंत्र/यंत्र-offsets.h>

#अगर_घोषित CONFIG_SHADOW_CALL_STACK
	scs_sp	.req	x18

	.macro scs_load tsk, पंचांगp
	ldr	scs_sp, [\टsk, #TSK_TI_SCS_SP]
	.endm

	.macro scs_save tsk, पंचांगp
	str	scs_sp, [\टsk, #TSK_TI_SCS_SP]
	.endm
#अन्यथा
	.macro scs_load tsk, पंचांगp
	.endm

	.macro scs_save tsk, पंचांगp
	.endm
#पूर्ण_अगर /* CONFIG_SHADOW_CALL_STACK */

#पूर्ण_अगर /* __ASSEMBLY __ */

#पूर्ण_अगर /* _ASM_SCS_H */
