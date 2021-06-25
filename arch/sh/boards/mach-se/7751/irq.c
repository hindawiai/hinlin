<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7751/irq.c
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine Support.
 *
 * Modअगरied क्रम 7751 Solution Engine by
 * Ian da Silva and Jeremy Siegel, 2001.
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/irq.h>
#समावेश <mach-se/mach/se7751.h>

अटल काष्ठा ipr_data ipr_irq_table[] = अणु
	अणु 13, 3, 3, 2 पूर्ण,
	/* Add additional entries here as drivers are added and tested. */
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
		.name	= "IPR-se7751",
	पूर्ण,
पूर्ण;

/*
 * Initialize IRQ setting
 */
व्योम __init init_7751se_IRQ(व्योम)
अणु
	रेजिस्टर_ipr_controller(&ipr_irq_desc);
पूर्ण
