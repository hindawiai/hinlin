<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 SiFive
 * Copyright (C) 2018 Christoph Hellwig
 */
#घोषणा pr_fmt(fmt) "plic: " fmt
#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/smp.h>

/*
 * This driver implements a version of the RISC-V PLIC with the actual layout
 * specअगरied in chapter 8 of the SiFive U5 Coreplex Series Manual:
 *
 *     https://अटल.dev.sअगरive.com/U54-MC-RVCoreIP.pdf
 *
 * The largest number supported by devices marked as 'sifive,plic-1.0.0', is
 * 1024, of which device 0 is defined as non-existent by the RISC-V Privileged
 * Spec.
 */

#घोषणा MAX_DEVICES			1024
#घोषणा MAX_CONTEXTS			15872

/*
 * Each पूर्णांकerrupt source has a priority रेजिस्टर associated with it.
 * We always hardwire it to one in Linux.
 */
#घोषणा PRIORITY_BASE			0
#घोषणा     PRIORITY_PER_ID		4

/*
 * Each hart context has a vector of पूर्णांकerrupt enable bits associated with it.
 * There's one bit क्रम each पूर्णांकerrupt source.
 */
#घोषणा ENABLE_BASE			0x2000
#घोषणा     ENABLE_PER_HART		0x80

/*
 * Each hart context has a set of control रेजिस्टरs associated with it.  Right
 * now there's only two: a source priority threshold over which the hart will
 * take an पूर्णांकerrupt, and a रेजिस्टर to claim पूर्णांकerrupts.
 */
#घोषणा CONTEXT_BASE			0x200000
#घोषणा     CONTEXT_PER_HART		0x1000
#घोषणा     CONTEXT_THRESHOLD		0x00
#घोषणा     CONTEXT_CLAIM		0x04

#घोषणा	PLIC_DISABLE_THRESHOLD		0x7
#घोषणा	PLIC_ENABLE_THRESHOLD		0

काष्ठा plic_priv अणु
	काष्ठा cpumask lmask;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	व्योम __iomem *regs;
पूर्ण;

काष्ठा plic_handler अणु
	bool			present;
	व्योम __iomem		*hart_base;
	/*
	 * Protect mask operations on the रेजिस्टरs given that we can't
	 * assume atomic memory operations work on them.
	 */
	raw_spinlock_t		enable_lock;
	व्योम __iomem		*enable_base;
	काष्ठा plic_priv	*priv;
पूर्ण;
अटल पूर्णांक plic_parent_irq __ro_after_init;
अटल bool plic_cpuhp_setup_करोne __ro_after_init;
अटल DEFINE_PER_CPU(काष्ठा plic_handler, plic_handlers);

अटल अंतरभूत व्योम plic_toggle(काष्ठा plic_handler *handler,
				पूर्णांक hwirq, पूर्णांक enable)
अणु
	u32 __iomem *reg = handler->enable_base + (hwirq / 32) * माप(u32);
	u32 hwirq_mask = 1 << (hwirq % 32);

	raw_spin_lock(&handler->enable_lock);
	अगर (enable)
		ग_लिखोl(पढ़ोl(reg) | hwirq_mask, reg);
	अन्यथा
		ग_लिखोl(पढ़ोl(reg) & ~hwirq_mask, reg);
	raw_spin_unlock(&handler->enable_lock);
पूर्ण

अटल अंतरभूत व्योम plic_irq_toggle(स्थिर काष्ठा cpumask *mask,
				   काष्ठा irq_data *d, पूर्णांक enable)
अणु
	पूर्णांक cpu;
	काष्ठा plic_priv *priv = irq_data_get_irq_chip_data(d);

	ग_लिखोl(enable, priv->regs + PRIORITY_BASE + d->hwirq * PRIORITY_PER_ID);
	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा plic_handler *handler = per_cpu_ptr(&plic_handlers, cpu);

		अगर (handler->present &&
		    cpumask_test_cpu(cpu, &handler->priv->lmask))
			plic_toggle(handler, d->hwirq, enable);
	पूर्ण
पूर्ण

अटल व्योम plic_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा cpumask amask;
	अचिन्हित पूर्णांक cpu;
	काष्ठा plic_priv *priv = irq_data_get_irq_chip_data(d);

	cpumask_and(&amask, &priv->lmask, cpu_online_mask);
	cpu = cpumask_any_and(irq_data_get_affinity_mask(d),
					   &amask);
	अगर (WARN_ON_ONCE(cpu >= nr_cpu_ids))
		वापस;
	plic_irq_toggle(cpumask_of(cpu), d, 1);
पूर्ण

अटल व्योम plic_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा plic_priv *priv = irq_data_get_irq_chip_data(d);

	plic_irq_toggle(&priv->lmask, d, 0);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक plic_set_affinity(काष्ठा irq_data *d,
			     स्थिर काष्ठा cpumask *mask_val, bool क्रमce)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा cpumask amask;
	काष्ठा plic_priv *priv = irq_data_get_irq_chip_data(d);

	cpumask_and(&amask, &priv->lmask, mask_val);

	अगर (क्रमce)
		cpu = cpumask_first(&amask);
	अन्यथा
		cpu = cpumask_any_and(&amask, cpu_online_mask);

	अगर (cpu >= nr_cpu_ids)
		वापस -EINVAL;

	plic_irq_toggle(&priv->lmask, d, 0);
	plic_irq_toggle(cpumask_of(cpu), d, !irqd_irq_masked(d));

	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण
#पूर्ण_अगर

अटल व्योम plic_irq_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा plic_handler *handler = this_cpu_ptr(&plic_handlers);

	ग_लिखोl(d->hwirq, handler->hart_base + CONTEXT_CLAIM);
पूर्ण

अटल काष्ठा irq_chip plic_chip = अणु
	.name		= "SiFive PLIC",
	.irq_mask	= plic_irq_mask,
	.irq_unmask	= plic_irq_unmask,
	.irq_eoi	= plic_irq_eoi,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = plic_set_affinity,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक plic_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hwirq)
अणु
	काष्ठा plic_priv *priv = d->host_data;

	irq_करोमुख्य_set_info(d, irq, hwirq, &plic_chip, d->host_data,
			    handle_fasteoi_irq, शून्य, शून्य);
	irq_set_noprobe(irq);
	irq_set_affinity(irq, &priv->lmask);
	वापस 0;
पूर्ण

अटल पूर्णांक plic_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i, ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	काष्ठा irq_fwspec *fwspec = arg;

	ret = irq_करोमुख्य_translate_onecell(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		ret = plic_irqकरोमुख्य_map(करोमुख्य, virq + i, hwirq + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops plic_irqकरोमुख्य_ops = अणु
	.translate	= irq_करोमुख्य_translate_onecell,
	.alloc		= plic_irq_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_top,
पूर्ण;

/*
 * Handling an पूर्णांकerrupt is a two-step process: first you claim the पूर्णांकerrupt
 * by पढ़ोing the claim रेजिस्टर, then you complete the पूर्णांकerrupt by writing
 * that source ID back to the same claim रेजिस्टर.  This स्वतःmatically enables
 * and disables the पूर्णांकerrupt, so there's nothing अन्यथा to करो.
 */
अटल व्योम plic_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा plic_handler *handler = this_cpu_ptr(&plic_handlers);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	व्योम __iomem *claim = handler->hart_base + CONTEXT_CLAIM;
	irq_hw_number_t hwirq;

	WARN_ON_ONCE(!handler->present);

	chained_irq_enter(chip, desc);

	जबतक ((hwirq = पढ़ोl(claim))) अणु
		पूर्णांक irq = irq_find_mapping(handler->priv->irqकरोमुख्य, hwirq);

		अगर (unlikely(irq <= 0))
			pr_warn_ratelimited("can't find mapping for hwirq %lu\n",
					hwirq);
		अन्यथा
			generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम plic_set_threshold(काष्ठा plic_handler *handler, u32 threshold)
अणु
	/* priority must be > threshold to trigger an पूर्णांकerrupt */
	ग_लिखोl(threshold, handler->hart_base + CONTEXT_THRESHOLD);
पूर्ण

अटल पूर्णांक plic_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (plic_parent_irq)
		disable_percpu_irq(plic_parent_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक plic_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा plic_handler *handler = this_cpu_ptr(&plic_handlers);

	अगर (plic_parent_irq)
		enable_percpu_irq(plic_parent_irq,
				  irq_get_trigger_type(plic_parent_irq));
	अन्यथा
		pr_warn("cpu%d: parent irq not available\n", cpu);
	plic_set_threshold(handler, PLIC_ENABLE_THRESHOLD);

	वापस 0;
पूर्ण

अटल पूर्णांक __init plic_init(काष्ठा device_node *node,
		काष्ठा device_node *parent)
अणु
	पूर्णांक error = 0, nr_contexts, nr_handlers = 0, i;
	u32 nr_irqs;
	काष्ठा plic_priv *priv;
	काष्ठा plic_handler *handler;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = of_iomap(node, 0);
	अगर (WARN_ON(!priv->regs)) अणु
		error = -EIO;
		जाओ out_मुक्त_priv;
	पूर्ण

	error = -EINVAL;
	of_property_पढ़ो_u32(node, "riscv,ndev", &nr_irqs);
	अगर (WARN_ON(!nr_irqs))
		जाओ out_iounmap;

	nr_contexts = of_irq_count(node);
	अगर (WARN_ON(!nr_contexts))
		जाओ out_iounmap;

	error = -ENOMEM;
	priv->irqकरोमुख्य = irq_करोमुख्य_add_linear(node, nr_irqs + 1,
			&plic_irqकरोमुख्य_ops, priv);
	अगर (WARN_ON(!priv->irqकरोमुख्य))
		जाओ out_iounmap;

	क्रम (i = 0; i < nr_contexts; i++) अणु
		काष्ठा of_phandle_args parent;
		irq_hw_number_t hwirq;
		पूर्णांक cpu, hartid;

		अगर (of_irq_parse_one(node, i, &parent)) अणु
			pr_err("failed to parse parent for context %d.\n", i);
			जारी;
		पूर्ण

		/*
		 * Skip contexts other than बाह्यal पूर्णांकerrupts क्रम our
		 * privilege level.
		 */
		अगर (parent.args[0] != RV_IRQ_EXT)
			जारी;

		hartid = riscv_of_parent_hartid(parent.np);
		अगर (hartid < 0) अणु
			pr_warn("failed to parse hart ID for context %d.\n", i);
			जारी;
		पूर्ण

		cpu = riscv_hartid_to_cpuid(hartid);
		अगर (cpu < 0) अणु
			pr_warn("Invalid cpuid for context %d\n", i);
			जारी;
		पूर्ण

		/* Find parent करोमुख्य and रेजिस्टर chained handler */
		अगर (!plic_parent_irq && irq_find_host(parent.np)) अणु
			plic_parent_irq = irq_of_parse_and_map(node, i);
			अगर (plic_parent_irq)
				irq_set_chained_handler(plic_parent_irq,
							plic_handle_irq);
		पूर्ण

		/*
		 * When running in M-mode we need to ignore the S-mode handler.
		 * Here we assume it always comes later, but that might be a
		 * little fragile.
		 */
		handler = per_cpu_ptr(&plic_handlers, cpu);
		अगर (handler->present) अणु
			pr_warn("handler already present for context %d.\n", i);
			plic_set_threshold(handler, PLIC_DISABLE_THRESHOLD);
			जाओ करोne;
		पूर्ण

		cpumask_set_cpu(cpu, &priv->lmask);
		handler->present = true;
		handler->hart_base =
			priv->regs + CONTEXT_BASE + i * CONTEXT_PER_HART;
		raw_spin_lock_init(&handler->enable_lock);
		handler->enable_base =
			priv->regs + ENABLE_BASE + i * ENABLE_PER_HART;
		handler->priv = priv;
करोne:
		क्रम (hwirq = 1; hwirq <= nr_irqs; hwirq++)
			plic_toggle(handler, hwirq, 0);
		nr_handlers++;
	पूर्ण

	/*
	 * We can have multiple PLIC instances so setup cpuhp state only
	 * when context handler क्रम current/boot CPU is present.
	 */
	handler = this_cpu_ptr(&plic_handlers);
	अगर (handler->present && !plic_cpuhp_setup_करोne) अणु
		cpuhp_setup_state(CPUHP_AP_IRQ_SIFIVE_PLIC_STARTING,
				  "irqchip/sifive/plic:starting",
				  plic_starting_cpu, plic_dying_cpu);
		plic_cpuhp_setup_करोne = true;
	पूर्ण

	pr_info("%pOFP: mapped %d interrupts with %d handlers for"
		" %d contexts.\n", node, nr_irqs, nr_handlers, nr_contexts);
	वापस 0;

out_iounmap:
	iounmap(priv->regs);
out_मुक्त_priv:
	kमुक्त(priv);
	वापस error;
पूर्ण

IRQCHIP_DECLARE(sअगरive_plic, "sifive,plic-1.0.0", plic_init);
IRQCHIP_DECLARE(riscv_plic0, "riscv,plic0", plic_init); /* क्रम legacy प्रणालीs */
