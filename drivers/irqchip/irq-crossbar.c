<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/irqchip/irq-crossbar.c
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 *  Author: Sriअक्षरan R <r.sriअक्षरan@ti.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>

#घोषणा IRQ_FREE	-1
#घोषणा IRQ_RESERVED	-2
#घोषणा IRQ_SKIP	-3
#घोषणा GIC_IRQ_START	32

/**
 * काष्ठा crossbar_device - crossbar device description
 * @lock: spinlock serializing access to @irq_map
 * @पूर्णांक_max: maximum number of supported पूर्णांकerrupts
 * @safe_map: safe शेष value to initialize the crossbar
 * @max_crossbar_sources: Maximum number of crossbar sources
 * @irq_map: array of पूर्णांकerrupts to crossbar number mapping
 * @crossbar_base: crossbar base address
 * @रेजिस्टर_offsets: offsets क्रम each irq number
 * @ग_लिखो: रेजिस्टर ग_लिखो function poपूर्णांकer
 */
काष्ठा crossbar_device अणु
	raw_spinlock_t lock;
	uपूर्णांक पूर्णांक_max;
	uपूर्णांक safe_map;
	uपूर्णांक max_crossbar_sources;
	uपूर्णांक *irq_map;
	व्योम __iomem *crossbar_base;
	पूर्णांक *रेजिस्टर_offsets;
	व्योम (*ग_लिखो)(पूर्णांक, पूर्णांक);
पूर्ण;

अटल काष्ठा crossbar_device *cb;

अटल व्योम crossbar_ग_लिखोl(पूर्णांक irq_no, पूर्णांक cb_no)
अणु
	ग_लिखोl(cb_no, cb->crossbar_base + cb->रेजिस्टर_offsets[irq_no]);
पूर्ण

अटल व्योम crossbar_ग_लिखोw(पूर्णांक irq_no, पूर्णांक cb_no)
अणु
	ग_लिखोw(cb_no, cb->crossbar_base + cb->रेजिस्टर_offsets[irq_no]);
पूर्ण

अटल व्योम crossbar_ग_लिखोb(पूर्णांक irq_no, पूर्णांक cb_no)
अणु
	ग_लिखोb(cb_no, cb->crossbar_base + cb->रेजिस्टर_offsets[irq_no]);
पूर्ण

अटल काष्ठा irq_chip crossbar_chip = अणु
	.name			= "CBAR",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_type		= irq_chip_set_type_parent,
	.flags			= IRQCHIP_MASK_ON_SUSPEND |
				  IRQCHIP_SKIP_SET_WAKE,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक allocate_gic_irq(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित virq,
			    irq_hw_number_t hwirq)
अणु
	काष्ठा irq_fwspec fwspec;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!irq_करोमुख्य_get_of_node(करोमुख्य->parent))
		वापस -EINVAL;

	raw_spin_lock(&cb->lock);
	क्रम (i = cb->पूर्णांक_max - 1; i >= 0; i--) अणु
		अगर (cb->irq_map[i] == IRQ_FREE) अणु
			cb->irq_map[i] = hwirq;
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock(&cb->lock);

	अगर (i < 0)
		वापस -ENODEV;

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = 0;	/* SPI */
	fwspec.param[1] = i;
	fwspec.param[2] = IRQ_TYPE_LEVEL_HIGH;

	err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (err)
		cb->irq_map[i] = IRQ_FREE;
	अन्यथा
		cb->ग_लिखो(i, hwirq);

	वापस err;
पूर्ण

अटल पूर्णांक crossbar_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	irq_hw_number_t hwirq;
	पूर्णांक i;

	अगर (fwspec->param_count != 3)
		वापस -EINVAL;	/* Not GIC compliant */
	अगर (fwspec->param[0] != 0)
		वापस -EINVAL;	/* No PPI should poपूर्णांक to this करोमुख्य */

	hwirq = fwspec->param[1];
	अगर ((hwirq + nr_irqs) > cb->max_crossbar_sources)
		वापस -EINVAL;	/* Can't deal with this */

	क्रम (i = 0; i < nr_irqs; i++) अणु
		पूर्णांक err = allocate_gic_irq(d, virq + i, hwirq + i);

		अगर (err)
			वापस err;

		irq_करोमुख्य_set_hwirq_and_chip(d, virq + i, hwirq + i,
					      &crossbar_chip, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * crossbar_करोमुख्य_मुक्त - unmap/मुक्त a crossbar<->irq connection
 * @करोमुख्य: करोमुख्य of irq to unmap
 * @virq: virq number
 * @nr_irqs: number of irqs to मुक्त
 *
 * We करो not मुख्यtain a use count of total number of map/unmap
 * calls क्रम a particular irq to find out अगर a irq can be really
 * unmapped. This is because unmap is called during irq_dispose_mapping(irq),
 * after which irq is anyways unusable. So an explicit map has to be called
 * after that.
 */
अटल व्योम crossbar_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	raw_spin_lock(&cb->lock);
	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);

		irq_करोमुख्य_reset_irq_data(d);
		cb->irq_map[d->hwirq] = IRQ_FREE;
		cb->ग_लिखो(d->hwirq, cb->safe_map);
	पूर्ण
	raw_spin_unlock(&cb->lock);
पूर्ण

अटल पूर्णांक crossbar_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				     काष्ठा irq_fwspec *fwspec,
				     अचिन्हित दीर्घ *hwirq,
				     अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		/* No PPI should poपूर्णांक to this करोमुख्य */
		अगर (fwspec->param[0] != 0)
			वापस -EINVAL;

		*hwirq = fwspec->param[1];
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops crossbar_करोमुख्य_ops = अणु
	.alloc		= crossbar_करोमुख्य_alloc,
	.मुक्त		= crossbar_करोमुख्य_मुक्त,
	.translate	= crossbar_करोमुख्य_translate,
पूर्ण;

अटल पूर्णांक __init crossbar_of_init(काष्ठा device_node *node)
अणु
	u32 max = 0, entry, reg_size;
	पूर्णांक i, size, reserved = 0;
	स्थिर __be32 *irqsr;
	पूर्णांक ret = -ENOMEM;

	cb = kzalloc(माप(*cb), GFP_KERNEL);

	अगर (!cb)
		वापस ret;

	cb->crossbar_base = of_iomap(node, 0);
	अगर (!cb->crossbar_base)
		जाओ err_cb;

	of_property_पढ़ो_u32(node, "ti,max-crossbar-sources",
			     &cb->max_crossbar_sources);
	अगर (!cb->max_crossbar_sources) अणु
		pr_err("missing 'ti,max-crossbar-sources' property\n");
		ret = -EINVAL;
		जाओ err_base;
	पूर्ण

	of_property_पढ़ो_u32(node, "ti,max-irqs", &max);
	अगर (!max) अणु
		pr_err("missing 'ti,max-irqs' property\n");
		ret = -EINVAL;
		जाओ err_base;
	पूर्ण
	cb->irq_map = kसुस्मृति(max, माप(पूर्णांक), GFP_KERNEL);
	अगर (!cb->irq_map)
		जाओ err_base;

	cb->पूर्णांक_max = max;

	क्रम (i = 0; i < max; i++)
		cb->irq_map[i] = IRQ_FREE;

	/* Get and mark reserved irqs */
	irqsr = of_get_property(node, "ti,irqs-reserved", &size);
	अगर (irqsr) अणु
		size /= माप(__be32);

		क्रम (i = 0; i < size; i++) अणु
			of_property_पढ़ो_u32_index(node,
						   "ti,irqs-reserved",
						   i, &entry);
			अगर (entry >= max) अणु
				pr_err("Invalid reserved entry\n");
				ret = -EINVAL;
				जाओ err_irq_map;
			पूर्ण
			cb->irq_map[entry] = IRQ_RESERVED;
		पूर्ण
	पूर्ण

	/* Skip irqs hardwired to bypass the crossbar */
	irqsr = of_get_property(node, "ti,irqs-skip", &size);
	अगर (irqsr) अणु
		size /= माप(__be32);

		क्रम (i = 0; i < size; i++) अणु
			of_property_पढ़ो_u32_index(node,
						   "ti,irqs-skip",
						   i, &entry);
			अगर (entry >= max) अणु
				pr_err("Invalid skip entry\n");
				ret = -EINVAL;
				जाओ err_irq_map;
			पूर्ण
			cb->irq_map[entry] = IRQ_SKIP;
		पूर्ण
	पूर्ण


	cb->रेजिस्टर_offsets = kसुस्मृति(max, माप(पूर्णांक), GFP_KERNEL);
	अगर (!cb->रेजिस्टर_offsets)
		जाओ err_irq_map;

	of_property_पढ़ो_u32(node, "ti,reg-size", &reg_size);

	चयन (reg_size) अणु
	हाल 1:
		cb->ग_लिखो = crossbar_ग_लिखोb;
		अवरोध;
	हाल 2:
		cb->ग_लिखो = crossbar_ग_लिखोw;
		अवरोध;
	हाल 4:
		cb->ग_लिखो = crossbar_ग_लिखोl;
		अवरोध;
	शेष:
		pr_err("Invalid reg-size property\n");
		ret = -EINVAL;
		जाओ err_reg_offset;
		अवरोध;
	पूर्ण

	/*
	 * Register offsets are not linear because of the
	 * reserved irqs. so find and store the offsets once.
	 */
	क्रम (i = 0; i < max; i++) अणु
		अगर (cb->irq_map[i] == IRQ_RESERVED)
			जारी;

		cb->रेजिस्टर_offsets[i] = reserved;
		reserved += reg_size;
	पूर्ण

	of_property_पढ़ो_u32(node, "ti,irqs-safe-map", &cb->safe_map);
	/* Initialize the crossbar with safe map to start with */
	क्रम (i = 0; i < max; i++) अणु
		अगर (cb->irq_map[i] == IRQ_RESERVED ||
		    cb->irq_map[i] == IRQ_SKIP)
			जारी;

		cb->ग_लिखो(i, cb->safe_map);
	पूर्ण

	raw_spin_lock_init(&cb->lock);

	वापस 0;

err_reg_offset:
	kमुक्त(cb->रेजिस्टर_offsets);
err_irq_map:
	kमुक्त(cb->irq_map);
err_base:
	iounmap(cb->crossbar_base);
err_cb:
	kमुक्त(cb);

	cb = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक __init irqcrossbar_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	पूर्णांक err;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	err = crossbar_of_init(node);
	अगर (err)
		वापस err;

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0,
					  cb->max_crossbar_sources,
					  node, &crossbar_करोमुख्य_ops,
					  शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%pOF: failed to allocated domain\n", node);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(ti_irqcrossbar, "ti,irq-crossbar", irqcrossbar_init);
