<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित __ASSEMBLY__

/* kfr2r09 board specअगरic boot code:
 * converts the "partner-jet-script.txt" script पूर्णांकo assembly
 * the assembly code is the first code to be executed in the romImage
 */

#समावेश <यंत्र/romimage-macros.h>
#समावेश <mach/partner-jet-setup.txt>

	/* execute icbi after enabling cache */
	mov.l	1f, r0
	icbi	@r0

	/* jump to cached area */
	mova	2f, r0
	jmp	@r0
	 nop

	.align 2
1:	.दीर्घ 0xa8000000
2:

#अन्यथा /* __ASSEMBLY__ */

अटल अंतरभूत व्योम mmcअगर_update_progress(पूर्णांक nr)
अणु
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
