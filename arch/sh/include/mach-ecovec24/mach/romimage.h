<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित __ASSEMBLY__

/* EcoVec board specअगरic boot code:
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
1 :	.दीर्घ 0xa8000000
2 :

#अन्यथा /* __ASSEMBLY__ */

/* Ecovec board specअगरic inक्रमmation:
 *
 * Set the following to enable MMCIF boot from the MMC card in CN12:
 *
 * DS1.5 = OFF (SH BOOT pin set to L)
 * DS2.6 = OFF (Select MMCIF on CN12 instead of SDHI1)
 * DS2.7 = ON  (Select MMCIF on CN12 instead of SDHI1)
 *
 */
#घोषणा HIZCRA		0xa4050158
#घोषणा PGDR		0xa405012c

अटल अंतरभूत व्योम mmcअगर_update_progress(पूर्णांक nr)
अणु
	/* disable Hi-Z क्रम LED pins */
	__raw_ग_लिखोw(__raw_पढ़ोw(HIZCRA) & ~(1 << 1), HIZCRA);

	/* update progress on LED4, LED5, LED6 and LED7 */
	__raw_ग_लिखोb(1 << (nr - 1), PGDR);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
