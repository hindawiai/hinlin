<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/770x/irq.c
 *
 * Copyright (C) 2000  Kazumoto Kojima
 * Copyright (C) 2006  Nobuhiro Iwamatsu
 *
 * Hitachi SolutionEngine Support.
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <mach-se/mach/se.h>

अटल काष्ठा ipr_data ipr_irq_table[] = अणु
	/*
	* Super I/O (Just mimic PC):
	*  1: keyboard
	*  3: serial 0
	*  4: serial 1
	*  5: prपूर्णांकer
	*  6: floppy
	*  8: rtc
	* 12: mouse
	* 14: ide0
	*/
#अगर defined(CONFIG_CPU_SUBTYPE_SH7705)
	/* This is शेष value */
	अणु 13, 0, 8,  0x0f-13, पूर्ण,
	अणु 5 , 0, 4,  0x0f- 5, पूर्ण,
	अणु 10, 1, 0,  0x0f-10, पूर्ण,
	अणु 7 , 2, 4,  0x0f- 7, पूर्ण,
	अणु 3 , 2, 0,  0x0f- 3, पूर्ण,
	अणु 1 , 3, 12, 0x0f- 1, पूर्ण,
	अणु 12, 3, 4,  0x0f-12, पूर्ण, /* LAN */
	अणु 2 , 4, 8,  0x0f- 2, पूर्ण, /* PCIRQ2 */
	अणु 6 , 4, 4,  0x0f- 6, पूर्ण, /* PCIRQ1 */
	अणु 14, 4, 0,  0x0f-14, पूर्ण, /* PCIRQ0 */
	अणु 0 , 5, 12, 0x0f   , पूर्ण, 
	अणु 4 , 5, 4,  0x0f- 4, पूर्ण,
	अणु 8 , 6, 12, 0x0f- 8, पूर्ण,
	अणु 9 , 6, 8,  0x0f- 9, पूर्ण,
	अणु 11, 6, 4,  0x0f-11, पूर्ण,
#अन्यथा
	अणु 14, 0,  8, 0x0f-14, पूर्ण,
	अणु 12, 0,  4, 0x0f-12, पूर्ण,
	अणु  8, 1,  4, 0x0f- 8, पूर्ण,
	अणु  6, 2, 12, 0x0f- 6, पूर्ण,
	अणु  5, 2,  8, 0x0f- 5, पूर्ण,
	अणु  4, 2,  4, 0x0f- 4, पूर्ण,
	अणु  3, 2,  0, 0x0f- 3, पूर्ण,
	अणु  1, 3, 12, 0x0f- 1, पूर्ण,
#अगर defined(CONFIG_STNIC)
	/* ST NIC */
	अणु 10, 3,  4, 0x0f-10, पूर्ण, 	/* LAN */
#पूर्ण_अगर
	/* MRSHPC IRQs setting */
	अणु  0, 4, 12, 0x0f- 0, पूर्ण,	/* PCIRQ3 */
	अणु 11, 4,  8, 0x0f-11, पूर्ण, 	/* PCIRQ2 */
	अणु  9, 4,  4, 0x0f- 9, पूर्ण, 	/* PCIRQ1 */
	अणु  7, 4,  0, 0x0f- 7, पूर्ण, 	/* PCIRQ0 */
	/* #2, #13 are allocated क्रम SLOT IRQ #1 and #2 (क्रम now) */
	/* NOTE: #2 and #13 are not used on PC */
	अणु 13, 6,  4, 0x0f-13, पूर्ण, 	/* SLOTIRQ2 */
	अणु  2, 6,  0, 0x0f- 2, पूर्ण, 	/* SLOTIRQ1 */
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित दीर्घ ipr_offsets[] = अणु
	BCR_ILCRA,
	BCR_ILCRB,
	BCR_ILCRC,
	BCR_ILCRD,
	BCR_ILCRE,
	BCR_ILCRF,
	BCR_ILCRG,
पूर्ण;

अटल काष्ठा ipr_desc ipr_irq_desc = अणु
	.ipr_offsets	= ipr_offsets,
	.nr_offsets	= ARRAY_SIZE(ipr_offsets),

	.ipr_data	= ipr_irq_table,
	.nr_irqs	= ARRAY_SIZE(ipr_irq_table),
	.chip = अणु
		.name	= "IPR-se770x",
	पूर्ण,
पूर्ण;

/*
 * Initialize IRQ setting
 */
व्योम __init init_se_IRQ(व्योम)
अणु
	/* Disable all पूर्णांकerrupts */
	__raw_ग_लिखोw(0, BCR_ILCRA);
	__raw_ग_लिखोw(0, BCR_ILCRB);
	__raw_ग_लिखोw(0, BCR_ILCRC);
	__raw_ग_लिखोw(0, BCR_ILCRD);
	__raw_ग_लिखोw(0, BCR_ILCRE);
	__raw_ग_लिखोw(0, BCR_ILCRF);
	__raw_ग_लिखोw(0, BCR_ILCRG);

	रेजिस्टर_ipr_controller(&ipr_irq_desc);
पूर्ण
