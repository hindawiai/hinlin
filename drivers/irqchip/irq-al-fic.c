<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

/* FIC Registers */
#घोषणा AL_FIC_CAUSE		0x00
#घोषणा AL_FIC_SET_CAUSE	0x08
#घोषणा AL_FIC_MASK		0x10
#घोषणा AL_FIC_CONTROL		0x28

#घोषणा CONTROL_TRIGGER_RISING	BIT(3)
#घोषणा CONTROL_MASK_MSI_X	BIT(5)

#घोषणा NR_FIC_IRQS 32

MODULE_AUTHOR("Talel Shenhar");
MODULE_DESCRIPTION("Amazon's Annapurna Labs Interrupt Controller Driver");
MODULE_LICENSE("GPL v2");

क्रमागत al_fic_state अणु
	AL_FIC_UNCONFIGURED = 0,
	AL_FIC_CONFIGURED_LEVEL,
	AL_FIC_CONFIGURED_RISING_EDGE,
पूर्ण;

काष्ठा al_fic अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक parent_irq;
	क्रमागत al_fic_state state;
पूर्ण;

अटल व्योम al_fic_set_trigger(काष्ठा al_fic *fic,
			       काष्ठा irq_chip_generic *gc,
			       क्रमागत al_fic_state new_state)
अणु
	irq_flow_handler_t handler;
	u32 control = पढ़ोl_relaxed(fic->base + AL_FIC_CONTROL);

	अगर (new_state == AL_FIC_CONFIGURED_LEVEL) अणु
		handler = handle_level_irq;
		control &= ~CONTROL_TRIGGER_RISING;
	पूर्ण अन्यथा अणु
		handler = handle_edge_irq;
		control |= CONTROL_TRIGGER_RISING;
	पूर्ण
	gc->chip_types->handler = handler;
	fic->state = new_state;
	ग_लिखोl_relaxed(control, fic->base + AL_FIC_CONTROL);
पूर्ण

अटल पूर्णांक al_fic_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	काष्ठा al_fic *fic = gc->निजी;
	क्रमागत al_fic_state new_state;
	पूर्णांक ret = 0;

	irq_gc_lock(gc);

	अगर (((flow_type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_LEVEL_HIGH) &&
	    ((flow_type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_EDGE_RISING)) अणु
		pr_debug("fic doesn't support flow type %d\n", flow_type);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	new_state = (flow_type & IRQ_TYPE_LEVEL_HIGH) ?
		AL_FIC_CONFIGURED_LEVEL : AL_FIC_CONFIGURED_RISING_EDGE;

	/*
	 * A given FIC instance can be either all level or all edge triggered.
	 * This is generally fixed depending on what pieces of HW it's wired up
	 * to.
	 *
	 * We configure it based on the sensitivity of the first source
	 * being setup, and reject any subsequent attempt at configuring it in a
	 * dअगरferent way.
	 */
	अगर (fic->state == AL_FIC_UNCONFIGURED) अणु
		al_fic_set_trigger(fic, gc, new_state);
	पूर्ण अन्यथा अगर (fic->state != new_state) अणु
		pr_debug("fic %s state already configured to %d\n",
			 fic->name, fic->state);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

err:
	irq_gc_unlock(gc);

	वापस ret;
पूर्ण

अटल व्योम al_fic_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा al_fic *fic = irq_desc_get_handler_data(desc);
	काष्ठा irq_करोमुख्य *करोमुख्य = fic->करोमुख्य;
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	काष्ठा irq_chip_generic *gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक irq;
	u32 hwirq;

	chained_irq_enter(irqchip, desc);

	pending = पढ़ोl_relaxed(fic->base + AL_FIC_CAUSE);
	pending &= ~gc->mask_cache;

	क्रम_each_set_bit(hwirq, &pending, NR_FIC_IRQS) अणु
		irq = irq_find_mapping(करोमुख्य, hwirq);
		generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल पूर्णांक al_fic_irq_retrigger(काष्ठा irq_data *data)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	काष्ठा al_fic *fic = gc->निजी;

	ग_लिखोl_relaxed(BIT(data->hwirq), fic->base + AL_FIC_SET_CAUSE);

	वापस 1;
पूर्ण

अटल पूर्णांक al_fic_रेजिस्टर(काष्ठा device_node *node,
			   काष्ठा al_fic *fic)
अणु
	काष्ठा irq_chip_generic *gc;
	पूर्णांक ret;

	fic->करोमुख्य = irq_करोमुख्य_add_linear(node,
					    NR_FIC_IRQS,
					    &irq_generic_chip_ops,
					    fic);
	अगर (!fic->करोमुख्य) अणु
		pr_err("fail to add irq domain\n");
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(fic->करोमुख्य,
					     NR_FIC_IRQS,
					     1, fic->name,
					     handle_level_irq,
					     0, 0, IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_err("fail to allocate generic chip (%d)\n", ret);
		जाओ err_करोमुख्य_हटाओ;
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(fic->करोमुख्य, 0);
	gc->reg_base = fic->base;
	gc->chip_types->regs.mask = AL_FIC_MASK;
	gc->chip_types->regs.ack = AL_FIC_CAUSE;
	gc->chip_types->chip.irq_mask = irq_gc_mask_set_bit;
	gc->chip_types->chip.irq_unmask = irq_gc_mask_clr_bit;
	gc->chip_types->chip.irq_ack = irq_gc_ack_clr_bit;
	gc->chip_types->chip.irq_set_type = al_fic_irq_set_type;
	gc->chip_types->chip.irq_retrigger = al_fic_irq_retrigger;
	gc->chip_types->chip.flags = IRQCHIP_SKIP_SET_WAKE;
	gc->निजी = fic;

	irq_set_chained_handler_and_data(fic->parent_irq,
					 al_fic_irq_handler,
					 fic);
	वापस 0;

err_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(fic->करोमुख्य);

	वापस ret;
पूर्ण

/*
 * al_fic_wire_init() - initialize and configure fic in wire mode
 * @of_node: optional poपूर्णांकer to पूर्णांकerrupt controller's device tree node.
 * @base: mmio to fic रेजिस्टर
 * @name: name of the fic
 * @parent_irq: पूर्णांकerrupt of parent
 *
 * This API will configure the fic hardware to to work in wire mode.
 * In wire mode, fic hardware is generating a wire ("wired") पूर्णांकerrupt.
 * Interrupt can be generated based on positive edge or level - configuration is
 * to be determined based on connected hardware to this fic.
 */
अटल काष्ठा al_fic *al_fic_wire_init(काष्ठा device_node *node,
				       व्योम __iomem *base,
				       स्थिर अक्षर *name,
				       अचिन्हित पूर्णांक parent_irq)
अणु
	काष्ठा al_fic *fic;
	पूर्णांक ret;
	u32 control = CONTROL_MASK_MSI_X;

	fic = kzalloc(माप(*fic), GFP_KERNEL);
	अगर (!fic)
		वापस ERR_PTR(-ENOMEM);

	fic->base = base;
	fic->parent_irq = parent_irq;
	fic->name = name;

	/* mask out all पूर्णांकerrupts */
	ग_लिखोl_relaxed(0xFFFFFFFF, fic->base + AL_FIC_MASK);

	/* clear any pending पूर्णांकerrupt */
	ग_लिखोl_relaxed(0, fic->base + AL_FIC_CAUSE);

	ग_लिखोl_relaxed(control, fic->base + AL_FIC_CONTROL);

	ret = al_fic_रेजिस्टर(node, fic);
	अगर (ret) अणु
		pr_err("fail to register irqchip\n");
		जाओ err_मुक्त;
	पूर्ण

	pr_debug("%s initialized successfully in Legacy mode (parent-irq=%u)\n",
		 fic->name, parent_irq);

	वापस fic;

err_मुक्त:
	kमुक्त(fic);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक __init al_fic_init_dt(काष्ठा device_node *node,
				 काष्ठा device_node *parent)
अणु
	पूर्णांक ret;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक parent_irq;
	काष्ठा al_fic *fic;

	अगर (!parent) अणु
		pr_err("%s: unsupported - device require a parent\n",
		       node->name);
		वापस -EINVAL;
	पूर्ण

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("%s: fail to map memory\n", node->name);
		वापस -ENOMEM;
	पूर्ण

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq) अणु
		pr_err("%s: fail to map irq\n", node->name);
		ret = -EINVAL;
		जाओ err_unmap;
	पूर्ण

	fic = al_fic_wire_init(node,
			       base,
			       node->name,
			       parent_irq);
	अगर (IS_ERR(fic)) अणु
		pr_err("%s: fail to initialize irqchip (%lu)\n",
		       node->name,
		       PTR_ERR(fic));
		ret = PTR_ERR(fic);
		जाओ err_irq_dispose;
	पूर्ण

	वापस 0;

err_irq_dispose:
	irq_dispose_mapping(parent_irq);
err_unmap:
	iounmap(base);

	वापस ret;
पूर्ण

IRQCHIP_DECLARE(al_fic, "amazon,al-fic", al_fic_init_dt);
