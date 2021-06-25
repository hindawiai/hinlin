<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Dove PMU support
 */
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/reset.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/करोve/pmu.h>
#समावेश <linux/spinlock.h>

#घोषणा NR_PMU_IRQS		7

#घोषणा PMC_SW_RST		0x30
#घोषणा PMC_IRQ_CAUSE		0x50
#घोषणा PMC_IRQ_MASK		0x54

#घोषणा PMU_PWR			0x10
#घोषणा PMU_ISO			0x58

काष्ठा pmu_data अणु
	spinlock_t lock;
	काष्ठा device_node *of_node;
	व्योम __iomem *pmc_base;
	व्योम __iomem *pmu_base;
	काष्ठा irq_chip_generic *irq_gc;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
#अगर_घोषित CONFIG_RESET_CONTROLLER
	काष्ठा reset_controller_dev reset;
#पूर्ण_अगर
पूर्ण;

/*
 * The PMU contains a रेजिस्टर to reset various subप्रणालीs within the
 * SoC.  Export this as a reset controller.
 */
#अगर_घोषित CONFIG_RESET_CONTROLLER
#घोषणा rcdev_to_pmu(rcdev) container_of(rcdev, काष्ठा pmu_data, reset)

अटल पूर्णांक pmu_reset_reset(काष्ठा reset_controller_dev *rc, अचिन्हित दीर्घ id)
अणु
	काष्ठा pmu_data *pmu = rcdev_to_pmu(rc);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&pmu->lock, flags);
	val = पढ़ोl_relaxed(pmu->pmc_base + PMC_SW_RST);
	ग_लिखोl_relaxed(val & ~BIT(id), pmu->pmc_base + PMC_SW_RST);
	ग_लिखोl_relaxed(val | BIT(id), pmu->pmc_base + PMC_SW_RST);
	spin_unlock_irqrestore(&pmu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_reset_निश्चित(काष्ठा reset_controller_dev *rc, अचिन्हित दीर्घ id)
अणु
	काष्ठा pmu_data *pmu = rcdev_to_pmu(rc);
	अचिन्हित दीर्घ flags;
	u32 val = ~BIT(id);

	spin_lock_irqsave(&pmu->lock, flags);
	val &= पढ़ोl_relaxed(pmu->pmc_base + PMC_SW_RST);
	ग_लिखोl_relaxed(val, pmu->pmc_base + PMC_SW_RST);
	spin_unlock_irqrestore(&pmu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_reset_deनिश्चित(काष्ठा reset_controller_dev *rc, अचिन्हित दीर्घ id)
अणु
	काष्ठा pmu_data *pmu = rcdev_to_pmu(rc);
	अचिन्हित दीर्घ flags;
	u32 val = BIT(id);

	spin_lock_irqsave(&pmu->lock, flags);
	val |= पढ़ोl_relaxed(pmu->pmc_base + PMC_SW_RST);
	ग_लिखोl_relaxed(val, pmu->pmc_base + PMC_SW_RST);
	spin_unlock_irqrestore(&pmu->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops pmu_reset_ops = अणु
	.reset = pmu_reset_reset,
	.निश्चित = pmu_reset_निश्चित,
	.deनिश्चित = pmu_reset_deनिश्चित,
पूर्ण;

अटल काष्ठा reset_controller_dev pmu_reset __initdata = अणु
	.ops = &pmu_reset_ops,
	.owner = THIS_MODULE,
	.nr_resets = 32,
पूर्ण;

अटल व्योम __init pmu_reset_init(काष्ठा pmu_data *pmu)
अणु
	पूर्णांक ret;

	pmu->reset = pmu_reset;
	pmu->reset.of_node = pmu->of_node;

	ret = reset_controller_रेजिस्टर(&pmu->reset);
	अगर (ret)
		pr_err("pmu: %s failed: %d\n", "reset_controller_register", ret);
पूर्ण
#अन्यथा
अटल व्योम __init pmu_reset_init(काष्ठा pmu_data *pmu)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा pmu_करोमुख्य अणु
	काष्ठा pmu_data *pmu;
	u32 pwr_mask;
	u32 rst_mask;
	u32 iso_mask;
	काष्ठा generic_pm_करोमुख्य base;
पूर्ण;

#घोषणा to_pmu_करोमुख्य(करोm) container_of(करोm, काष्ठा pmu_करोमुख्य, base)

/*
 * This deals with the "old" Marvell sequence of bringing a घातer करोमुख्य
 * करोwn/up, which is: apply घातer, release reset, disable isolators.
 *
 * Later devices apparantly use a dअगरferent sequence: घातer up, disable
 * isolators, निश्चित repair संकेत, enable SRMA घड़ी, enable AXI घड़ी,
 * enable module घड़ी, deनिश्चित reset.
 *
 * Note: पढ़ोing the assembly, it seems that the IO accessors have an
 * unक्रमtunate side-effect - they cause memory alपढ़ोy पढ़ो पूर्णांकo रेजिस्टरs
 * क्रम the अगर () to be re-पढ़ो क्रम the bit-set or bit-clear operation.
 * The code is written to aव्योम this.
 */
अटल पूर्णांक pmu_करोमुख्य_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा pmu_करोमुख्य *pmu_करोm = to_pmu_करोमुख्य(करोमुख्य);
	काष्ठा pmu_data *pmu = pmu_करोm->pmu;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	व्योम __iomem *pmu_base = pmu->pmu_base;
	व्योम __iomem *pmc_base = pmu->pmc_base;

	spin_lock_irqsave(&pmu->lock, flags);

	/* Enable isolators */
	अगर (pmu_करोm->iso_mask) अणु
		val = ~pmu_करोm->iso_mask;
		val &= पढ़ोl_relaxed(pmu_base + PMU_ISO);
		ग_लिखोl_relaxed(val, pmu_base + PMU_ISO);
	पूर्ण

	/* Reset unit */
	अगर (pmu_करोm->rst_mask) अणु
		val = ~pmu_करोm->rst_mask;
		val &= पढ़ोl_relaxed(pmc_base + PMC_SW_RST);
		ग_लिखोl_relaxed(val, pmc_base + PMC_SW_RST);
	पूर्ण

	/* Power करोwn */
	val = पढ़ोl_relaxed(pmu_base + PMU_PWR) | pmu_करोm->pwr_mask;
	ग_लिखोl_relaxed(val, pmu_base + PMU_PWR);

	spin_unlock_irqrestore(&pmu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pmu_करोमुख्य_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा pmu_करोमुख्य *pmu_करोm = to_pmu_करोमुख्य(करोमुख्य);
	काष्ठा pmu_data *pmu = pmu_करोm->pmu;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	व्योम __iomem *pmu_base = pmu->pmu_base;
	व्योम __iomem *pmc_base = pmu->pmc_base;

	spin_lock_irqsave(&pmu->lock, flags);

	/* Power on */
	val = ~pmu_करोm->pwr_mask & पढ़ोl_relaxed(pmu_base + PMU_PWR);
	ग_लिखोl_relaxed(val, pmu_base + PMU_PWR);

	/* Release reset */
	अगर (pmu_करोm->rst_mask) अणु
		val = pmu_करोm->rst_mask;
		val |= पढ़ोl_relaxed(pmc_base + PMC_SW_RST);
		ग_लिखोl_relaxed(val, pmc_base + PMC_SW_RST);
	पूर्ण

	/* Disable isolators */
	अगर (pmu_करोm->iso_mask) अणु
		val = pmu_करोm->iso_mask;
		val |= पढ़ोl_relaxed(pmu_base + PMU_ISO);
		ग_लिखोl_relaxed(val, pmu_base + PMU_ISO);
	पूर्ण

	spin_unlock_irqrestore(&pmu->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम __pmu_करोमुख्य_रेजिस्टर(काष्ठा pmu_करोमुख्य *करोमुख्य,
	काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक val = पढ़ोl_relaxed(करोमुख्य->pmu->pmu_base + PMU_PWR);

	करोमुख्य->base.घातer_off = pmu_करोमुख्य_घातer_off;
	करोमुख्य->base.घातer_on = pmu_करोमुख्य_घातer_on;

	pm_genpd_init(&करोमुख्य->base, शून्य, !(val & करोमुख्य->pwr_mask));

	अगर (np)
		of_genpd_add_provider_simple(np, &करोमुख्य->base);
पूर्ण

/* PMU IRQ controller */
अटल व्योम pmu_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा pmu_data *pmu = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip_generic *gc = pmu->irq_gc;
	काष्ठा irq_करोमुख्य *करोमुख्य = pmu->irq_करोमुख्य;
	व्योम __iomem *base = gc->reg_base;
	u32 stat = पढ़ोl_relaxed(base + PMC_IRQ_CAUSE) & gc->mask_cache;
	u32 करोne = ~0;

	अगर (stat == 0) अणु
		handle_bad_irq(desc);
		वापस;
	पूर्ण

	जबतक (stat) अणु
		u32 hwirq = fls(stat) - 1;

		stat &= ~(1 << hwirq);
		करोne &= ~(1 << hwirq);

		generic_handle_irq(irq_find_mapping(करोमुख्य, hwirq));
	पूर्ण

	/*
	 * The PMU mask रेजिस्टर is not RW0C: it is RW.  This means that
	 * the bits take whatever value is written to them; अगर you ग_लिखो
	 * a '1', you will set the पूर्णांकerrupt.
	 *
	 * Unक्रमtunately this means there is NO race मुक्त way to clear
	 * these पूर्णांकerrupts.
	 *
	 * So, let's काष्ठाure the code so that the winकरोw is as small as
	 * possible.
	 */
	irq_gc_lock(gc);
	करोne &= पढ़ोl_relaxed(base + PMC_IRQ_CAUSE);
	ग_लिखोl_relaxed(करोne, base + PMC_IRQ_CAUSE);
	irq_gc_unlock(gc);
पूर्ण

अटल पूर्णांक __init करोve_init_pmu_irq(काष्ठा pmu_data *pmu, पूर्णांक irq)
अणु
	स्थिर अक्षर *name = "pmu_irq";
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक ret;

	/* mask and clear all पूर्णांकerrupts */
	ग_लिखोl(0, pmu->pmc_base + PMC_IRQ_MASK);
	ग_लिखोl(0, pmu->pmc_base + PMC_IRQ_CAUSE);

	करोमुख्य = irq_करोमुख्य_add_linear(pmu->of_node, NR_PMU_IRQS,
				       &irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%s: unable to add irq domain\n", name);
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, NR_PMU_IRQS, 1, name,
					     handle_level_irq,
					     IRQ_NOREQUEST | IRQ_NOPROBE, 0,
					     IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_err("%s: unable to alloc irq domain gc: %d\n", name, ret);
		irq_करोमुख्य_हटाओ(करोमुख्य);
		वापस ret;
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	gc->reg_base = pmu->pmc_base;
	gc->chip_types[0].regs.mask = PMC_IRQ_MASK;
	gc->chip_types[0].chip.irq_mask = irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask = irq_gc_mask_set_bit;

	pmu->irq_करोमुख्य = करोमुख्य;
	pmu->irq_gc = gc;

	irq_set_handler_data(irq, pmu);
	irq_set_chained_handler(irq, pmu_irq_handler);

	वापस 0;
पूर्ण

पूर्णांक __init करोve_init_pmu_legacy(स्थिर काष्ठा करोve_pmu_initdata *initdata)
अणु
	स्थिर काष्ठा करोve_pmu_करोमुख्य_initdata *करोमुख्य_initdata;
	काष्ठा pmu_data *pmu;
	पूर्णांक ret;

	pmu = kzalloc(माप(*pmu), GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;

	spin_lock_init(&pmu->lock);
	pmu->pmc_base = initdata->pmc_base;
	pmu->pmu_base = initdata->pmu_base;

	pmu_reset_init(pmu);
	क्रम (करोमुख्य_initdata = initdata->करोमुख्यs; करोमुख्य_initdata->name;
	     करोमुख्य_initdata++) अणु
		काष्ठा pmu_करोमुख्य *करोमुख्य;

		करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
		अगर (करोमुख्य) अणु
			करोमुख्य->pmu = pmu;
			करोमुख्य->pwr_mask = करोमुख्य_initdata->pwr_mask;
			करोमुख्य->rst_mask = करोमुख्य_initdata->rst_mask;
			करोमुख्य->iso_mask = करोमुख्य_initdata->iso_mask;
			करोमुख्य->base.name = करोमुख्य_initdata->name;

			__pmu_करोमुख्य_रेजिस्टर(करोमुख्य, शून्य);
		पूर्ण
	पूर्ण

	ret = करोve_init_pmu_irq(pmu, initdata->irq);
	अगर (ret)
		pr_err("dove_init_pmu_irq() failed: %d\n", ret);

	अगर (pmu->irq_करोमुख्य)
		irq_करोमुख्य_associate_many(pmu->irq_करोमुख्य,
					  initdata->irq_करोमुख्य_start,
					  0, NR_PMU_IRQS);

	वापस 0;
पूर्ण

/*
 * pmu: घातer-manager@d0000 अणु
 *	compatible = "marvell,dove-pmu";
 *	reg = <0xd0000 0x8000> <0xd8000 0x8000>;
 *	पूर्णांकerrupts = <33>;
 *	पूर्णांकerrupt-controller;
 *	#reset-cells = 1;
 *	vpu_करोमुख्य: vpu-करोमुख्य अणु
 *		#घातer-करोमुख्य-cells = <0>;
 *		marvell,pmu_pwr_mask = <0x00000008>;
 *		marvell,pmu_iso_mask = <0x00000001>;
 *		resets = <&pmu 16>;
 *	पूर्ण;
 *	gpu_करोमुख्य: gpu-करोमुख्य अणु
 *		#घातer-करोमुख्य-cells = <0>;
 *		marvell,pmu_pwr_mask = <0x00000004>;
 *		marvell,pmu_iso_mask = <0x00000002>;
 *		resets = <&pmu 18>;
 *	पूर्ण;
 * पूर्ण;
 */
पूर्णांक __init करोve_init_pmu(व्योम)
अणु
	काष्ठा device_node *np_pmu, *करोमुख्यs_node, *np;
	काष्ठा pmu_data *pmu;
	पूर्णांक ret, parent_irq;

	/* Lookup the PMU node */
	np_pmu = of_find_compatible_node(शून्य, शून्य, "marvell,dove-pmu");
	अगर (!np_pmu)
		वापस 0;

	करोमुख्यs_node = of_get_child_by_name(np_pmu, "domains");
	अगर (!करोमुख्यs_node) अणु
		pr_err("%pOFn: failed to find domains sub-node\n", np_pmu);
		वापस 0;
	पूर्ण

	pmu = kzalloc(माप(*pmu), GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;

	spin_lock_init(&pmu->lock);
	pmu->of_node = np_pmu;
	pmu->pmc_base = of_iomap(pmu->of_node, 0);
	pmu->pmu_base = of_iomap(pmu->of_node, 1);
	अगर (!pmu->pmc_base || !pmu->pmu_base) अणु
		pr_err("%pOFn: failed to map PMU\n", np_pmu);
		iounmap(pmu->pmu_base);
		iounmap(pmu->pmc_base);
		kमुक्त(pmu);
		वापस -ENOMEM;
	पूर्ण

	pmu_reset_init(pmu);

	क्रम_each_available_child_of_node(करोमुख्यs_node, np) अणु
		काष्ठा of_phandle_args args;
		काष्ठा pmu_करोमुख्य *करोमुख्य;

		करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
		अगर (!करोमुख्य)
			अवरोध;

		करोमुख्य->pmu = pmu;
		करोमुख्य->base.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn", np);
		अगर (!करोमुख्य->base.name) अणु
			kमुक्त(करोमुख्य);
			अवरोध;
		पूर्ण

		of_property_पढ़ो_u32(np, "marvell,pmu_pwr_mask",
				     &करोमुख्य->pwr_mask);
		of_property_पढ़ो_u32(np, "marvell,pmu_iso_mask",
				     &करोमुख्य->iso_mask);

		/*
		 * We parse the reset controller property directly here
		 * to ensure that we can operate when the reset controller
		 * support is not configured पूर्णांकo the kernel.
		 */
		ret = of_parse_phandle_with_args(np, "resets", "#reset-cells",
						 0, &args);
		अगर (ret == 0) अणु
			अगर (args.np == pmu->of_node)
				करोमुख्य->rst_mask = BIT(args.args[0]);
			of_node_put(args.np);
		पूर्ण

		__pmu_करोमुख्य_रेजिस्टर(करोमुख्य, np);
	पूर्ण

	/* Loss of the पूर्णांकerrupt controller is not a fatal error. */
	parent_irq = irq_of_parse_and_map(pmu->of_node, 0);
	अगर (!parent_irq) अणु
		pr_err("%pOFn: no interrupt specified\n", np_pmu);
	पूर्ण अन्यथा अणु
		ret = करोve_init_pmu_irq(pmu, parent_irq);
		अगर (ret)
			pr_err("dove_init_pmu_irq() failed: %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण
