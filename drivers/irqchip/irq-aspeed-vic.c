<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2015 - Ben Herrenschmidt, IBM Corp.
 *
 *  Driver क्रम Aspeed "new" VIC as found in SoC generation 3 and later
 *
 *  Based on irq-vic.c:
 *
 *  Copyright (C) 1999 - 2003 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/irq.h>

/* These definitions correspond to the "new mapping" of the
 * रेजिस्टर set that पूर्णांकerleaves "high" and "low". The offsets
 * below are क्रम the "low" रेजिस्टर, add 4 to get to the high one
 */
#घोषणा AVIC_IRQ_STATUS		0x00
#घोषणा AVIC_FIQ_STATUS		0x08
#घोषणा AVIC_RAW_STATUS		0x10
#घोषणा AVIC_INT_SELECT		0x18
#घोषणा AVIC_INT_ENABLE		0x20
#घोषणा AVIC_INT_ENABLE_CLR	0x28
#घोषणा AVIC_INT_TRIGGER	0x30
#घोषणा AVIC_INT_TRIGGER_CLR	0x38
#घोषणा AVIC_INT_SENSE		0x40
#घोषणा AVIC_INT_DUAL_EDGE	0x48
#घोषणा AVIC_INT_EVENT		0x50
#घोषणा AVIC_EDGE_CLR		0x58
#घोषणा AVIC_EDGE_STATUS	0x60

#घोषणा NUM_IRQS		64

काष्ठा aspeed_vic अणु
	व्योम __iomem		*base;
	u32			edge_sources[2];
	काष्ठा irq_करोमुख्य	*करोm;
पूर्ण;
अटल काष्ठा aspeed_vic *प्रणाली_avic;

अटल व्योम vic_init_hw(काष्ठा aspeed_vic *vic)
अणु
	u32 sense;

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(0xffffffff, vic->base + AVIC_INT_ENABLE_CLR);
	ग_लिखोl(0xffffffff, vic->base + AVIC_INT_ENABLE_CLR + 4);

	/* Make sure no soft trigger is on */
	ग_लिखोl(0xffffffff, vic->base + AVIC_INT_TRIGGER_CLR);
	ग_लिखोl(0xffffffff, vic->base + AVIC_INT_TRIGGER_CLR + 4);

	/* Set everything to be IRQ */
	ग_लिखोl(0, vic->base + AVIC_INT_SELECT);
	ग_लिखोl(0, vic->base + AVIC_INT_SELECT + 4);

	/* Some पूर्णांकerrupts have a programmable high/low level trigger
	 * (4 GPIO direct inमाला_दो), क्रम now we assume this was configured
	 * by firmware. We पढ़ो which ones are edge now.
	 */
	sense = पढ़ोl(vic->base + AVIC_INT_SENSE);
	vic->edge_sources[0] = ~sense;
	sense = पढ़ोl(vic->base + AVIC_INT_SENSE + 4);
	vic->edge_sources[1] = ~sense;

	/* Clear edge detection latches */
	ग_लिखोl(0xffffffff, vic->base + AVIC_EDGE_CLR);
	ग_लिखोl(0xffffffff, vic->base + AVIC_EDGE_CLR + 4);
पूर्ण

अटल व्योम __exception_irq_entry avic_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा aspeed_vic *vic = प्रणाली_avic;
	u32 stat, irq;

	क्रम (;;) अणु
		irq = 0;
		stat = पढ़ोl_relaxed(vic->base + AVIC_IRQ_STATUS);
		अगर (!stat) अणु
			stat = पढ़ोl_relaxed(vic->base + AVIC_IRQ_STATUS + 4);
			irq = 32;
		पूर्ण
		अगर (stat == 0)
			अवरोध;
		irq += ffs(stat) - 1;
		handle_करोमुख्य_irq(vic->करोm, irq, regs);
	पूर्ण
पूर्ण

अटल व्योम avic_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा aspeed_vic *vic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक sidx = d->hwirq >> 5;
	अचिन्हित पूर्णांक sbit = 1u << (d->hwirq & 0x1f);

	/* Clear edge latch क्रम edge पूर्णांकerrupts, nop क्रम level */
	अगर (vic->edge_sources[sidx] & sbit)
		ग_लिखोl(sbit, vic->base + AVIC_EDGE_CLR + sidx * 4);
पूर्ण

अटल व्योम avic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा aspeed_vic *vic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक sidx = d->hwirq >> 5;
	अचिन्हित पूर्णांक sbit = 1u << (d->hwirq & 0x1f);

	ग_लिखोl(sbit, vic->base + AVIC_INT_ENABLE_CLR + sidx * 4);
पूर्ण

अटल व्योम avic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा aspeed_vic *vic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक sidx = d->hwirq >> 5;
	अचिन्हित पूर्णांक sbit = 1u << (d->hwirq & 0x1f);

	ग_लिखोl(sbit, vic->base + AVIC_INT_ENABLE + sidx * 4);
पूर्ण

/* For level irq, faster than going through a nop "ack" and mask */
अटल व्योम avic_mask_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा aspeed_vic *vic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक sidx = d->hwirq >> 5;
	अचिन्हित पूर्णांक sbit = 1u << (d->hwirq & 0x1f);

	/* First mask */
	ग_लिखोl(sbit, vic->base + AVIC_INT_ENABLE_CLR + sidx * 4);

	/* Then clear edge latch क्रम edge पूर्णांकerrupts */
	अगर (vic->edge_sources[sidx] & sbit)
		ग_लिखोl(sbit, vic->base + AVIC_EDGE_CLR + sidx * 4);
पूर्ण

अटल काष्ठा irq_chip avic_chip = अणु
	.name		= "AVIC",
	.irq_ack	= avic_ack_irq,
	.irq_mask	= avic_mask_irq,
	.irq_unmask	= avic_unmask_irq,
	.irq_mask_ack	= avic_mask_ack_irq,
पूर्ण;

अटल पूर्णांक avic_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		    irq_hw_number_t hwirq)
अणु
	काष्ठा aspeed_vic *vic = d->host_data;
	अचिन्हित पूर्णांक sidx = hwirq >> 5;
	अचिन्हित पूर्णांक sbit = 1u << (hwirq & 0x1f);

	/* Check अगर पूर्णांकerrupt exists */
	अगर (sidx > 1)
		वापस -EPERM;

	अगर (vic->edge_sources[sidx] & sbit)
		irq_set_chip_and_handler(irq, &avic_chip, handle_edge_irq);
	अन्यथा
		irq_set_chip_and_handler(irq, &avic_chip, handle_level_irq);
	irq_set_chip_data(irq, vic);
	irq_set_probe(irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops avic_करोm_ops = अणु
	.map = avic_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल पूर्णांक __init avic_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	व्योम __iomem *regs;
	काष्ठा aspeed_vic *vic;

	अगर (WARN(parent, "non-root Aspeed VIC not supported"))
		वापस -EINVAL;
	अगर (WARN(प्रणाली_avic, "duplicate Aspeed VIC not supported"))
		वापस -EINVAL;

	regs = of_iomap(node, 0);
	अगर (WARN_ON(!regs))
		वापस -EIO;

	vic = kzalloc(माप(काष्ठा aspeed_vic), GFP_KERNEL);
	अगर (WARN_ON(!vic)) अणु
		iounmap(regs);
		वापस -ENOMEM;
	पूर्ण
	vic->base = regs;

	/* Initialize sources, all masked */
	vic_init_hw(vic);

	/* Ready to receive पूर्णांकerrupts */
	प्रणाली_avic = vic;
	set_handle_irq(avic_handle_irq);

	/* Register our करोमुख्य */
	vic->करोm = irq_करोमुख्य_add_simple(node, NUM_IRQS, 0,
					 &avic_करोm_ops, vic);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(ast2400_vic, "aspeed,ast2400-vic", avic_of_init);
IRQCHIP_DECLARE(ast2500_vic, "aspeed,ast2500-vic", avic_of_init);
