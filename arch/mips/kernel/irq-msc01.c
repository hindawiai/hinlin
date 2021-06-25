<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (c) 2004 MIPS Inc
 * Author: chris@mips.com
 *
 * Copyright (C) 2004, 06 Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/msc01_ic.h>
#समावेश <यंत्र/traps.h>

अटल अचिन्हित दीर्घ _icctrl_msc;
#घोषणा MSC01_IC_REG_BASE	_icctrl_msc

#घोषणा MSCIC_WRITE(reg, data)	करो अणु *(अस्थिर u32 *)(reg) = data; पूर्ण जबतक (0)
#घोषणा MSCIC_READ(reg, data)	करो अणु data = *(अस्थिर u32 *)(reg); पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक irq_base;

/* mask off an पूर्णांकerrupt */
अटल अंतरभूत व्योम mask_msc_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर (irq < (irq_base + 32))
		MSCIC_WRITE(MSC01_IC_DISL, 1<<(irq - irq_base));
	अन्यथा
		MSCIC_WRITE(MSC01_IC_DISH, 1<<(irq - irq_base - 32));
पूर्ण

/* unmask an पूर्णांकerrupt */
अटल अंतरभूत व्योम unmask_msc_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	अगर (irq < (irq_base + 32))
		MSCIC_WRITE(MSC01_IC_ENAL, 1<<(irq - irq_base));
	अन्यथा
		MSCIC_WRITE(MSC01_IC_ENAH, 1<<(irq - irq_base - 32));
पूर्ण

/*
 * Masks and ACKs an IRQ
 */
अटल व्योम level_mask_and_ack_msc_irq(काष्ठा irq_data *d)
अणु
	mask_msc_irq(d);
	अगर (!cpu_has_veic)
		MSCIC_WRITE(MSC01_IC_EOI, 0);
पूर्ण

/*
 * Masks and ACKs an IRQ
 */
अटल व्योम edge_mask_and_ack_msc_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;

	mask_msc_irq(d);
	अगर (!cpu_has_veic)
		MSCIC_WRITE(MSC01_IC_EOI, 0);
	अन्यथा अणु
		u32 r;
		MSCIC_READ(MSC01_IC_SUP+irq*8, r);
		MSCIC_WRITE(MSC01_IC_SUP+irq*8, r | ~MSC01_IC_SUP_EDGE_BIT);
		MSCIC_WRITE(MSC01_IC_SUP+irq*8, r);
	पूर्ण
पूर्ण

/*
 * Interrupt handler क्रम पूर्णांकerrupts coming from SOC-it.
 */
व्योम ll_msc_irq(व्योम)
अणु
	अचिन्हित पूर्णांक irq;

	/* पढ़ो the पूर्णांकerrupt vector रेजिस्टर */
	MSCIC_READ(MSC01_IC_VEC, irq);
	अगर (irq < 64)
		करो_IRQ(irq + irq_base);
	अन्यथा अणु
		/* Ignore spurious पूर्णांकerrupt */
	पूर्ण
पूर्ण

अटल व्योम msc_bind_eic_पूर्णांकerrupt(पूर्णांक irq, पूर्णांक set)
अणु
	MSCIC_WRITE(MSC01_IC_RAMW,
		    (irq<<MSC01_IC_RAMW_ADDR_SHF) | (set<<MSC01_IC_RAMW_DATA_SHF));
पूर्ण

अटल काष्ठा irq_chip msc_levelirq_type = अणु
	.name = "SOC-it-Level",
	.irq_ack = level_mask_and_ack_msc_irq,
	.irq_mask = mask_msc_irq,
	.irq_mask_ack = level_mask_and_ack_msc_irq,
	.irq_unmask = unmask_msc_irq,
	.irq_eoi = unmask_msc_irq,
पूर्ण;

अटल काष्ठा irq_chip msc_edgeirq_type = अणु
	.name = "SOC-it-Edge",
	.irq_ack = edge_mask_and_ack_msc_irq,
	.irq_mask = mask_msc_irq,
	.irq_mask_ack = edge_mask_and_ack_msc_irq,
	.irq_unmask = unmask_msc_irq,
	.irq_eoi = unmask_msc_irq,
पूर्ण;


व्योम __init init_msc_irqs(अचिन्हित दीर्घ icubase, अचिन्हित पूर्णांक irqbase, msc_irqmap_t *imp, पूर्णांक nirq)
अणु
	_icctrl_msc = (अचिन्हित दीर्घ) ioremap(icubase, 0x40000);

	/* Reset पूर्णांकerrupt controller - initialises all रेजिस्टरs to 0 */
	MSCIC_WRITE(MSC01_IC_RST, MSC01_IC_RST_RST_BIT);

	board_bind_eic_पूर्णांकerrupt = &msc_bind_eic_पूर्णांकerrupt;

	क्रम (; nirq > 0; nirq--, imp++) अणु
		पूर्णांक n = imp->im_irq;

		चयन (imp->im_type) अणु
		हाल MSC01_IRQ_EDGE:
			irq_set_chip_and_handler_name(irqbase + n,
						      &msc_edgeirq_type,
						      handle_edge_irq,
						      "edge");
			अगर (cpu_has_veic)
				MSCIC_WRITE(MSC01_IC_SUP+n*8, MSC01_IC_SUP_EDGE_BIT);
			अन्यथा
				MSCIC_WRITE(MSC01_IC_SUP+n*8, MSC01_IC_SUP_EDGE_BIT | imp->im_lvl);
			अवरोध;
		हाल MSC01_IRQ_LEVEL:
			irq_set_chip_and_handler_name(irqbase + n,
						      &msc_levelirq_type,
						      handle_level_irq,
						      "level");
			अगर (cpu_has_veic)
				MSCIC_WRITE(MSC01_IC_SUP+n*8, 0);
			अन्यथा
				MSCIC_WRITE(MSC01_IC_SUP+n*8, imp->im_lvl);
		पूर्ण
	पूर्ण

	irq_base = irqbase;

	MSCIC_WRITE(MSC01_IC_GENA, MSC01_IC_GENA_GENA_BIT);	/* Enable पूर्णांकerrupt generation */

पूर्ण
