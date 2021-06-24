<शैली गुरु>
/*
 * Synopsys DW APB ICTL irqchip driver.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * based on GPL'ed 2.6 kernel sources
 *  (c) Marvell International Ltd.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा APB_INT_ENABLE_L	0x00
#घोषणा APB_INT_ENABLE_H	0x04
#घोषणा APB_INT_MASK_L		0x08
#घोषणा APB_INT_MASK_H		0x0c
#घोषणा APB_INT_FINALSTATUS_L	0x30
#घोषणा APB_INT_FINALSTATUS_H	0x34
#घोषणा APB_INT_BASE_OFFSET	0x04

/* irq करोमुख्य of the primary पूर्णांकerrupt controller. */
अटल काष्ठा irq_करोमुख्य *dw_apb_ictl_irq_करोमुख्य;

अटल व्योम __irq_entry dw_apb_ictl_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा irq_करोमुख्य *d = dw_apb_ictl_irq_करोमुख्य;
	पूर्णांक n;

	क्रम (n = 0; n < d->revmap_size; n += 32) अणु
		काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(d, n);
		u32 stat = पढ़ोl_relaxed(gc->reg_base + APB_INT_FINALSTATUS_L);

		जबतक (stat) अणु
			u32 hwirq = ffs(stat) - 1;

			handle_करोमुख्य_irq(d, hwirq, regs);
			stat &= ~BIT(hwirq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dw_apb_ictl_handle_irq_cascaded(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *d = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक n;

	chained_irq_enter(chip, desc);

	क्रम (n = 0; n < d->revmap_size; n += 32) अणु
		काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(d, n);
		u32 stat = पढ़ोl_relaxed(gc->reg_base + APB_INT_FINALSTATUS_L);

		जबतक (stat) अणु
			u32 hwirq = ffs(stat) - 1;
			u32 virq = irq_find_mapping(d, gc->irq_base + hwirq);

			generic_handle_irq(virq);
			stat &= ~BIT(hwirq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक dw_apb_ictl_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i, ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = arg;

	ret = irq_करोमुख्य_translate_onecell(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++)
		irq_map_generic_chip(करोमुख्य, virq + i, hwirq + i);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops dw_apb_ictl_irq_करोमुख्य_ops = अणु
	.translate = irq_करोमुख्य_translate_onecell,
	.alloc = dw_apb_ictl_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_top,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल व्योम dw_apb_ictl_resume(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);

	irq_gc_lock(gc);
	ग_लिखोl_relaxed(~0, gc->reg_base + ct->regs.enable);
	ग_लिखोl_relaxed(*ct->mask_cache, gc->reg_base + ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण
#अन्यथा
#घोषणा dw_apb_ictl_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक __init dw_apb_ictl_init(काष्ठा device_node *np,
				   काष्ठा device_node *parent)
अणु
	स्थिर काष्ठा irq_करोमुख्य_ops *करोमुख्य_ops;
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा resource r;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip_generic *gc;
	व्योम __iomem *iobase;
	पूर्णांक ret, nrirqs, parent_irq, i;
	u32 reg;

	अगर (!parent) अणु
		/* Used as the primary पूर्णांकerrupt controller */
		parent_irq = 0;
		करोमुख्य_ops = &dw_apb_ictl_irq_करोमुख्य_ops;
	पूर्ण अन्यथा अणु
		/* Map the parent पूर्णांकerrupt क्रम the chained handler */
		parent_irq = irq_of_parse_and_map(np, 0);
		अगर (parent_irq <= 0) अणु
			pr_err("%pOF: unable to parse irq\n", np);
			वापस -EINVAL;
		पूर्ण
		करोमुख्य_ops = &irq_generic_chip_ops;
	पूर्ण

	ret = of_address_to_resource(np, 0, &r);
	अगर (ret) अणु
		pr_err("%pOF: unable to get resource\n", np);
		वापस ret;
	पूर्ण

	अगर (!request_mem_region(r.start, resource_size(&r), np->full_name)) अणु
		pr_err("%pOF: unable to request mem region\n", np);
		वापस -ENOMEM;
	पूर्ण

	iobase = ioremap(r.start, resource_size(&r));
	अगर (!iobase) अणु
		pr_err("%pOF: unable to map resource\n", np);
		ret = -ENOMEM;
		जाओ err_release;
	पूर्ण

	/*
	 * DW IP can be configured to allow 2-64 irqs. We can determine
	 * the number of irqs supported by writing पूर्णांकo enable रेजिस्टर
	 * and look क्रम bits not set, as corresponding flip-flops will
	 * have been हटाओd by synthesis tool.
	 */

	/* mask and enable all पूर्णांकerrupts */
	ग_लिखोl_relaxed(~0, iobase + APB_INT_MASK_L);
	ग_लिखोl_relaxed(~0, iobase + APB_INT_MASK_H);
	ग_लिखोl_relaxed(~0, iobase + APB_INT_ENABLE_L);
	ग_लिखोl_relaxed(~0, iobase + APB_INT_ENABLE_H);

	reg = पढ़ोl_relaxed(iobase + APB_INT_ENABLE_H);
	अगर (reg)
		nrirqs = 32 + fls(reg);
	अन्यथा
		nrirqs = fls(पढ़ोl_relaxed(iobase + APB_INT_ENABLE_L));

	करोमुख्य = irq_करोमुख्य_add_linear(np, nrirqs, करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%pOF: unable to add irq domain\n", np);
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, 32, 1, np->name,
					     handle_level_irq, clr, 0,
					     IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_err("%pOF: unable to alloc irq domain gc\n", np);
		जाओ err_unmap;
	पूर्ण

	क्रम (i = 0; i < DIV_ROUND_UP(nrirqs, 32); i++) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, i * 32);
		gc->reg_base = iobase + i * APB_INT_BASE_OFFSET;
		gc->chip_types[0].regs.mask = APB_INT_MASK_L;
		gc->chip_types[0].regs.enable = APB_INT_ENABLE_L;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_set_bit;
		gc->chip_types[0].chip.irq_unmask = irq_gc_mask_clr_bit;
		gc->chip_types[0].chip.irq_resume = dw_apb_ictl_resume;
	पूर्ण

	अगर (parent_irq) अणु
		irq_set_chained_handler_and_data(parent_irq,
				dw_apb_ictl_handle_irq_cascaded, करोमुख्य);
	पूर्ण अन्यथा अणु
		dw_apb_ictl_irq_करोमुख्य = करोमुख्य;
		set_handle_irq(dw_apb_ictl_handle_irq);
	पूर्ण

	वापस 0;

err_unmap:
	iounmap(iobase);
err_release:
	release_mem_region(r.start, resource_size(&r));
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(dw_apb_ictl,
		"snps,dw-apb-ictl", dw_apb_ictl_init);
