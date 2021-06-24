<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2008 Thomas Chou <thomas@wytron.com.tw>
 *
 * based on irq.c from m68k which is:
 *
 * Copyright (C) 2007 Greg Ungerer <gerg@snapgear.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>

अटल u32 ienable;

यंत्रlinkage व्योम करो_IRQ(पूर्णांक hwirq, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *oldregs = set_irq_regs(regs);
	पूर्णांक irq;

	irq_enter();
	irq = irq_find_mapping(शून्य, hwirq);
	generic_handle_irq(irq);
	irq_निकास();

	set_irq_regs(oldregs);
पूर्ण

अटल व्योम chip_unmask(काष्ठा irq_data *d)
अणु
	ienable |= (1 << d->hwirq);
	WRCTL(CTL_IENABLE, ienable);
पूर्ण

अटल व्योम chip_mask(काष्ठा irq_data *d)
अणु
	ienable &= ~(1 << d->hwirq);
	WRCTL(CTL_IENABLE, ienable);
पूर्ण

अटल काष्ठा irq_chip m_irq_chip = अणु
	.name		= "NIOS2-INTC",
	.irq_unmask	= chip_unmask,
	.irq_mask	= chip_mask,
पूर्ण;

अटल पूर्णांक irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hw_irq_num)
अणु
	irq_set_chip_and_handler(virq, &m_irq_chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_ops = अणु
	.map	= irq_map,
	.xlate	= irq_करोमुख्य_xlate_onecell,
पूर्ण;

व्योम __init init_IRQ(व्योम)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा device_node *node;

	node = of_find_compatible_node(शून्य, शून्य, "altr,nios2-1.0");
	अगर (!node)
		node = of_find_compatible_node(शून्य, शून्य, "altr,nios2-1.1");

	BUG_ON(!node);

	करोमुख्य = irq_करोमुख्य_add_linear(node, NIOS2_CPU_NR_IRQS, &irq_ops, शून्य);
	BUG_ON(!करोमुख्य);

	irq_set_शेष_host(करोमुख्य);
	of_node_put(node);
	/* Load the initial ienable value */
	ienable = RDCTL(CTL_IENABLE);
पूर्ण
