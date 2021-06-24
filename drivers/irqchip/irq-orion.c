<शैली गुरु>
/*
 * Marvell Orion SoCs IRQ chip driver.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

/*
 * Orion SoC मुख्य पूर्णांकerrupt controller
 */
#घोषणा ORION_IRQS_PER_CHIP		32

#घोषणा ORION_IRQ_CAUSE			0x00
#घोषणा ORION_IRQ_MASK			0x04
#घोषणा ORION_IRQ_FIQ_MASK		0x08
#घोषणा ORION_IRQ_ENDP_MASK		0x0c

अटल काष्ठा irq_करोमुख्य *orion_irq_करोमुख्य;

अटल व्योम
__exception_irq_entry orion_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा irq_करोमुख्य_chip_generic *dgc = orion_irq_करोमुख्य->gc;
	पूर्णांक n, base = 0;

	क्रम (n = 0; n < dgc->num_chips; n++, base += ORION_IRQS_PER_CHIP) अणु
		काष्ठा irq_chip_generic *gc =
			irq_get_करोमुख्य_generic_chip(orion_irq_करोमुख्य, base);
		u32 stat = पढ़ोl_relaxed(gc->reg_base + ORION_IRQ_CAUSE) &
			gc->mask_cache;
		जबतक (stat) अणु
			u32 hwirq = __fls(stat);
			handle_करोमुख्य_irq(orion_irq_करोमुख्य,
					  gc->irq_base + hwirq, regs);
			stat &= ~(1 << hwirq);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init orion_irq_init(काष्ठा device_node *np,
				 काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	पूर्णांक n, ret, base, num_chips = 0;
	काष्ठा resource r;

	/* count number of irq chips by valid reg addresses */
	जबतक (of_address_to_resource(np, num_chips, &r) == 0)
		num_chips++;

	orion_irq_करोमुख्य = irq_करोमुख्य_add_linear(np,
				num_chips * ORION_IRQS_PER_CHIP,
				&irq_generic_chip_ops, शून्य);
	अगर (!orion_irq_करोमुख्य)
		panic("%pOFn: unable to add irq domain\n", np);

	ret = irq_alloc_करोमुख्य_generic_chips(orion_irq_करोमुख्य,
				ORION_IRQS_PER_CHIP, 1, np->full_name,
				handle_level_irq, clr, 0,
				IRQ_GC_INIT_MASK_CACHE);
	अगर (ret)
		panic("%pOFn: unable to alloc irq domain gc\n", np);

	क्रम (n = 0, base = 0; n < num_chips; n++, base += ORION_IRQS_PER_CHIP) अणु
		काष्ठा irq_chip_generic *gc =
			irq_get_करोमुख्य_generic_chip(orion_irq_करोमुख्य, base);

		of_address_to_resource(np, n, &r);

		अगर (!request_mem_region(r.start, resource_size(&r), np->name))
			panic("%pOFn: unable to request mem region %d",
			      np, n);

		gc->reg_base = ioremap(r.start, resource_size(&r));
		अगर (!gc->reg_base)
			panic("%pOFn: unable to map resource %d", np, n);

		gc->chip_types[0].regs.mask = ORION_IRQ_MASK;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_clr_bit;
		gc->chip_types[0].chip.irq_unmask = irq_gc_mask_set_bit;

		/* mask all पूर्णांकerrupts */
		ग_लिखोl(0, gc->reg_base + ORION_IRQ_MASK);
	पूर्ण

	set_handle_irq(orion_handle_irq);
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(orion_पूर्णांकc, "marvell,orion-intc", orion_irq_init);

/*
 * Orion SoC bridge पूर्णांकerrupt controller
 */
#घोषणा ORION_BRIDGE_IRQ_CAUSE	0x00
#घोषणा ORION_BRIDGE_IRQ_MASK	0x04

अटल व्योम orion_bridge_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *d = irq_desc_get_handler_data(desc);

	काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(d, 0);
	u32 stat = पढ़ोl_relaxed(gc->reg_base + ORION_BRIDGE_IRQ_CAUSE) &
		   gc->mask_cache;

	जबतक (stat) अणु
		u32 hwirq = __fls(stat);

		generic_handle_irq(irq_find_mapping(d, gc->irq_base + hwirq));
		stat &= ~(1 << hwirq);
	पूर्ण
पूर्ण

/*
 * Bridge IRQ_CAUSE is निश्चितed regardless of IRQ_MASK रेजिस्टर.
 * To aव्योम पूर्णांकerrupt events on stale irqs, we clear them beक्रमe unmask.
 */
अटल अचिन्हित पूर्णांक orion_bridge_irq_startup(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);

	ct->chip.irq_ack(d);
	ct->chip.irq_unmask(d);
	वापस 0;
पूर्ण

अटल पूर्णांक __init orion_bridge_irq_init(काष्ठा device_node *np,
					काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा resource r;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक ret, irq, nrirqs = 32;

	/* get optional number of पूर्णांकerrupts provided */
	of_property_पढ़ो_u32(np, "marvell,#interrupts", &nrirqs);

	करोमुख्य = irq_करोमुख्य_add_linear(np, nrirqs,
				       &irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%pOFn: unable to add irq domain\n", np);
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, nrirqs, 1, np->name,
			     handle_edge_irq, clr, 0, IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_err("%pOFn: unable to alloc irq domain gc\n", np);
		वापस ret;
	पूर्ण

	ret = of_address_to_resource(np, 0, &r);
	अगर (ret) अणु
		pr_err("%pOFn: unable to get resource\n", np);
		वापस ret;
	पूर्ण

	अगर (!request_mem_region(r.start, resource_size(&r), np->name)) अणु
		pr_err("%s: unable to request mem region\n", np->name);
		वापस -ENOMEM;
	पूर्ण

	/* Map the parent पूर्णांकerrupt क्रम the chained handler */
	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0) अणु
		pr_err("%pOFn: unable to parse irq\n", np);
		वापस -EINVAL;
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	gc->reg_base = ioremap(r.start, resource_size(&r));
	अगर (!gc->reg_base) अणु
		pr_err("%pOFn: unable to map resource\n", np);
		वापस -ENOMEM;
	पूर्ण

	gc->chip_types[0].regs.ack = ORION_BRIDGE_IRQ_CAUSE;
	gc->chip_types[0].regs.mask = ORION_BRIDGE_IRQ_MASK;
	gc->chip_types[0].chip.irq_startup = orion_bridge_irq_startup;
	gc->chip_types[0].chip.irq_ack = irq_gc_ack_clr_bit;
	gc->chip_types[0].chip.irq_mask = irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask = irq_gc_mask_set_bit;

	/* mask and clear all पूर्णांकerrupts */
	ग_लिखोl(0, gc->reg_base + ORION_BRIDGE_IRQ_MASK);
	ग_लिखोl(0, gc->reg_base + ORION_BRIDGE_IRQ_CAUSE);

	irq_set_chained_handler_and_data(irq, orion_bridge_irq_handler,
					 करोमुख्य);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(orion_bridge_पूर्णांकc,
		"marvell,orion-bridge-intc", orion_bridge_irq_init);
