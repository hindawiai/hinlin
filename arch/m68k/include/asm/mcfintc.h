<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfपूर्णांकc.h -- support definitions क्रम the simple ColdFire
 *		     Interrupt Controller
 *
 * 	(C) Copyright 2009,  Greg Ungerer <gerg@uclinux.org>
 */

/****************************************************************************/
#अगर_अघोषित	mcfपूर्णांकc_h
#घोषणा	mcfपूर्णांकc_h
/****************************************************************************/

/*
 * Most of the older ColdFire parts use the same simple पूर्णांकerrupt
 * controller. This is currently used on the 5206, 5206e, 5249, 5307
 * and 5407 parts.
 *
 * The builtin peripherals are masked through dedicated bits in the
 * Interrupt Mask रेजिस्टर (IMR) - and this is not indexed (or in any way
 * related to) the actual पूर्णांकerrupt number they use. So knowing the IRQ
 * number करोesn't explicitly map to a certain पूर्णांकernal device क्रम
 * पूर्णांकerrupt control purposes.
 */

/*
 * Bit definitions क्रम the ICR family of रेजिस्टरs.
 */
#घोषणा	MCFSIM_ICR_AUTOVEC	0x80		/* Auto-vectored पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL0	0x00		/* Level 0 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL1	0x04		/* Level 1 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL2	0x08		/* Level 2 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL3	0x0c		/* Level 3 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL4	0x10		/* Level 4 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL5	0x14		/* Level 5 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL6	0x18		/* Level 6 पूर्णांकr */
#घोषणा	MCFSIM_ICR_LEVEL7	0x1c		/* Level 7 पूर्णांकr */

#घोषणा	MCFSIM_ICR_PRI0		0x00		/* Priority 0 पूर्णांकr */
#घोषणा	MCFSIM_ICR_PRI1		0x01		/* Priority 1 पूर्णांकr */
#घोषणा	MCFSIM_ICR_PRI2		0x02		/* Priority 2 पूर्णांकr */
#घोषणा	MCFSIM_ICR_PRI3		0x03		/* Priority 3 पूर्णांकr */

/*
 * IMR bit position definitions. Not all ColdFire parts with this पूर्णांकerrupt
 * controller actually support all of these पूर्णांकerrupt sources. But the bit
 * numbers are the same in all cores.
 */
#घोषणा	MCFINTC_EINT1		1		/* External पूर्णांक #1 */
#घोषणा	MCFINTC_EINT2		2		/* External पूर्णांक #2 */
#घोषणा	MCFINTC_EINT3		3		/* External पूर्णांक #3 */
#घोषणा	MCFINTC_EINT4		4		/* External पूर्णांक #4 */
#घोषणा	MCFINTC_EINT5		5		/* External पूर्णांक #5 */
#घोषणा	MCFINTC_EINT6		6		/* External पूर्णांक #6 */
#घोषणा	MCFINTC_EINT7		7		/* External पूर्णांक #7 */
#घोषणा	MCFINTC_SWT		8		/* Software Watchकरोg */
#घोषणा	MCFINTC_TIMER1		9
#घोषणा	MCFINTC_TIMER2		10
#घोषणा	MCFINTC_I2C		11		/* I2C / MBUS */
#घोषणा	MCFINTC_UART0		12
#घोषणा	MCFINTC_UART1		13
#घोषणा	MCFINTC_DMA0		14
#घोषणा	MCFINTC_DMA1		15
#घोषणा	MCFINTC_DMA2		16
#घोषणा	MCFINTC_DMA3		17
#घोषणा	MCFINTC_QSPI		18

#अगर_अघोषित __ASSEMBLER__

/*
 * There is no one-is-one correspondance between the पूर्णांकerrupt number (irq)
 * and the bit fields on the mask रेजिस्टर. So we create a per-cpu type
 * mapping of irq to mask bit. The CPU platक्रमm code needs to रेजिस्टर
 * its supported irq's at init समय, using this function.
 */
बाह्य अचिन्हित अक्षर mcf_irq2imr[];
अटल अंतरभूत व्योम mcf_mapirq2imr(पूर्णांक irq, पूर्णांक imr)
अणु
	mcf_irq2imr[irq] = imr;
पूर्ण

व्योम mcf_स्वतःvector(पूर्णांक irq);
व्योम mcf_setimr(पूर्णांक index);
व्योम mcf_clrimr(पूर्णांक index);
#पूर्ण_अगर

/****************************************************************************/
#पूर्ण_अगर	/* mcfपूर्णांकc_h */
