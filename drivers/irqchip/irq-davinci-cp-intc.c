<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Author: Steve Chen <schen@mvista.com>
// Copyright (C) 2008-2009, MontaVista Software, Inc. <source@mvista.com>
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
// Copyright (C) 2019, Texas Instruments
//
// TI Common Platक्रमm Interrupt Controller (cp_पूर्णांकc) driver

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/irq-davinci-cp-पूर्णांकc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/exception.h>

#घोषणा DAVINCI_CP_INTC_CTRL			0x04
#घोषणा DAVINCI_CP_INTC_HOST_CTRL		0x0c
#घोषणा DAVINCI_CP_INTC_GLOBAL_ENABLE		0x10
#घोषणा DAVINCI_CP_INTC_SYS_STAT_IDX_CLR	0x24
#घोषणा DAVINCI_CP_INTC_SYS_ENABLE_IDX_SET	0x28
#घोषणा DAVINCI_CP_INTC_SYS_ENABLE_IDX_CLR	0x2c
#घोषणा DAVINCI_CP_INTC_HOST_ENABLE_IDX_SET	0x34
#घोषणा DAVINCI_CP_INTC_HOST_ENABLE_IDX_CLR	0x38
#घोषणा DAVINCI_CP_INTC_PRIO_IDX		0x80
#घोषणा DAVINCI_CP_INTC_SYS_STAT_CLR(n)		(0x0280 + (n << 2))
#घोषणा DAVINCI_CP_INTC_SYS_ENABLE_CLR(n)	(0x0380 + (n << 2))
#घोषणा DAVINCI_CP_INTC_CHAN_MAP(n)		(0x0400 + (n << 2))
#घोषणा DAVINCI_CP_INTC_SYS_POLARITY(n)		(0x0d00 + (n << 2))
#घोषणा DAVINCI_CP_INTC_SYS_TYPE(n)		(0x0d80 + (n << 2))
#घोषणा DAVINCI_CP_INTC_HOST_ENABLE(n)		(0x1500 + (n << 2))
#घोषणा DAVINCI_CP_INTC_PRI_INDX_MASK		GENMASK(9, 0)
#घोषणा DAVINCI_CP_INTC_GPIR_NONE		BIT(31)

अटल व्योम __iomem *davinci_cp_पूर्णांकc_base;
अटल काष्ठा irq_करोमुख्य *davinci_cp_पूर्णांकc_irq_करोमुख्य;

अटल अंतरभूत अचिन्हित पूर्णांक davinci_cp_पूर्णांकc_पढ़ो(अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(davinci_cp_पूर्णांकc_base + offset);
पूर्ण

अटल अंतरभूत व्योम davinci_cp_पूर्णांकc_ग_लिखो(अचिन्हित दीर्घ value,
					 अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl_relaxed(value, davinci_cp_पूर्णांकc_base + offset);
पूर्ण

अटल व्योम davinci_cp_पूर्णांकc_ack_irq(काष्ठा irq_data *d)
अणु
	davinci_cp_पूर्णांकc_ग_लिखो(d->hwirq, DAVINCI_CP_INTC_SYS_STAT_IDX_CLR);
पूर्ण

अटल व्योम davinci_cp_पूर्णांकc_mask_irq(काष्ठा irq_data *d)
अणु
	/* XXX करोn't know why we need to disable nIRQ here... */
	davinci_cp_पूर्णांकc_ग_लिखो(1, DAVINCI_CP_INTC_HOST_ENABLE_IDX_CLR);
	davinci_cp_पूर्णांकc_ग_लिखो(d->hwirq, DAVINCI_CP_INTC_SYS_ENABLE_IDX_CLR);
	davinci_cp_पूर्णांकc_ग_लिखो(1, DAVINCI_CP_INTC_HOST_ENABLE_IDX_SET);
पूर्ण

अटल व्योम davinci_cp_पूर्णांकc_unmask_irq(काष्ठा irq_data *d)
अणु
	davinci_cp_पूर्णांकc_ग_लिखो(d->hwirq, DAVINCI_CP_INTC_SYS_ENABLE_IDX_SET);
पूर्ण

अटल पूर्णांक davinci_cp_पूर्णांकc_set_irq_type(काष्ठा irq_data *d,
					अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित पूर्णांक reg, mask, polarity, type;

	reg = BIT_WORD(d->hwirq);
	mask = BIT_MASK(d->hwirq);
	polarity = davinci_cp_पूर्णांकc_पढ़ो(DAVINCI_CP_INTC_SYS_POLARITY(reg));
	type = davinci_cp_पूर्णांकc_पढ़ो(DAVINCI_CP_INTC_SYS_TYPE(reg));

	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		polarity |= mask;
		type |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		polarity &= ~mask;
		type |= mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		polarity |= mask;
		type &= ~mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		polarity &= ~mask;
		type &= ~mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	davinci_cp_पूर्णांकc_ग_लिखो(polarity, DAVINCI_CP_INTC_SYS_POLARITY(reg));
	davinci_cp_पूर्णांकc_ग_लिखो(type, DAVINCI_CP_INTC_SYS_TYPE(reg));

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip davinci_cp_पूर्णांकc_irq_chip = अणु
	.name		= "cp_intc",
	.irq_ack	= davinci_cp_पूर्णांकc_ack_irq,
	.irq_mask	= davinci_cp_पूर्णांकc_mask_irq,
	.irq_unmask	= davinci_cp_पूर्णांकc_unmask_irq,
	.irq_set_type	= davinci_cp_पूर्णांकc_set_irq_type,
	.flags		= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल यंत्रlinkage व्योम __exception_irq_entry
davinci_cp_पूर्णांकc_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक gpir, irqnr, none;

	/*
	 * The पूर्णांकerrupt number is in first ten bits. The NONE field set to 1
	 * indicates a spurious irq.
	 */

	gpir = davinci_cp_पूर्णांकc_पढ़ो(DAVINCI_CP_INTC_PRIO_IDX);
	irqnr = gpir & DAVINCI_CP_INTC_PRI_INDX_MASK;
	none = gpir & DAVINCI_CP_INTC_GPIR_NONE;

	अगर (unlikely(none)) अणु
		pr_err_once("%s: spurious irq!\n", __func__);
		वापस;
	पूर्ण

	handle_करोमुख्य_irq(davinci_cp_पूर्णांकc_irq_करोमुख्य, irqnr, regs);
पूर्ण

अटल पूर्णांक davinci_cp_पूर्णांकc_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	pr_debug("cp_intc_host_map(%d, 0x%lx)\n", virq, hw);

	irq_set_chip(virq, &davinci_cp_पूर्णांकc_irq_chip);
	irq_set_probe(virq);
	irq_set_handler(virq, handle_edge_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops davinci_cp_पूर्णांकc_irq_करोमुख्य_ops = अणु
	.map = davinci_cp_पूर्णांकc_host_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल पूर्णांक __init
davinci_cp_पूर्णांकc_करो_init(स्थिर काष्ठा davinci_cp_पूर्णांकc_config *config,
			काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक num_regs = BITS_TO_LONGS(config->num_irqs);
	पूर्णांक offset, irq_base;
	व्योम __iomem *req;

	req = request_mem_region(config->reg.start,
				 resource_size(&config->reg),
				 "davinci-cp-intc");
	अगर (!req) अणु
		pr_err("%s: register range busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	davinci_cp_पूर्णांकc_base = ioremap(config->reg.start,
				       resource_size(&config->reg));
	अगर (!davinci_cp_पूर्णांकc_base) अणु
		pr_err("%s: unable to ioremap register range\n", __func__);
		वापस -EINVAL;
	पूर्ण

	davinci_cp_पूर्णांकc_ग_लिखो(0, DAVINCI_CP_INTC_GLOBAL_ENABLE);

	/* Disable all host पूर्णांकerrupts */
	davinci_cp_पूर्णांकc_ग_लिखो(0, DAVINCI_CP_INTC_HOST_ENABLE(0));

	/* Disable प्रणाली पूर्णांकerrupts */
	क्रम (offset = 0; offset < num_regs; offset++)
		davinci_cp_पूर्णांकc_ग_लिखो(~0,
			DAVINCI_CP_INTC_SYS_ENABLE_CLR(offset));

	/* Set to normal mode, no nesting, no priority hold */
	davinci_cp_पूर्णांकc_ग_लिखो(0, DAVINCI_CP_INTC_CTRL);
	davinci_cp_पूर्णांकc_ग_लिखो(0, DAVINCI_CP_INTC_HOST_CTRL);

	/* Clear प्रणाली पूर्णांकerrupt status */
	क्रम (offset = 0; offset < num_regs; offset++)
		davinci_cp_पूर्णांकc_ग_लिखो(~0,
			DAVINCI_CP_INTC_SYS_STAT_CLR(offset));

	/* Enable nIRQ (what about nFIQ?) */
	davinci_cp_पूर्णांकc_ग_लिखो(1, DAVINCI_CP_INTC_HOST_ENABLE_IDX_SET);

	/* Default all priorities to channel 7. */
	num_regs = (config->num_irqs + 3) >> 2;	/* 4 channels per रेजिस्टर */
	क्रम (offset = 0; offset < num_regs; offset++)
		davinci_cp_पूर्णांकc_ग_लिखो(0x07070707,
			DAVINCI_CP_INTC_CHAN_MAP(offset));

	irq_base = irq_alloc_descs(-1, 0, config->num_irqs, 0);
	अगर (irq_base < 0) अणु
		pr_err("%s: unable to allocate interrupt descriptors: %d\n",
		       __func__, irq_base);
		वापस irq_base;
	पूर्ण

	davinci_cp_पूर्णांकc_irq_करोमुख्य = irq_करोमुख्य_add_legacy(
					node, config->num_irqs, irq_base, 0,
					&davinci_cp_पूर्णांकc_irq_करोमुख्य_ops, शून्य);

	अगर (!davinci_cp_पूर्णांकc_irq_करोमुख्य) अणु
		pr_err("%s: unable to create an interrupt domain\n", __func__);
		वापस -EINVAL;
	पूर्ण

	set_handle_irq(davinci_cp_पूर्णांकc_handle_irq);

	/* Enable global पूर्णांकerrupt */
	davinci_cp_पूर्णांकc_ग_लिखो(1, DAVINCI_CP_INTC_GLOBAL_ENABLE);

	वापस 0;
पूर्ण

पूर्णांक __init davinci_cp_पूर्णांकc_init(स्थिर काष्ठा davinci_cp_पूर्णांकc_config *config)
अणु
	वापस davinci_cp_पूर्णांकc_करो_init(config, शून्य);
पूर्ण

अटल पूर्णांक __init davinci_cp_पूर्णांकc_of_init(काष्ठा device_node *node,
					  काष्ठा device_node *parent)
अणु
	काष्ठा davinci_cp_पूर्णांकc_config config = अणु पूर्ण;
	पूर्णांक ret;

	ret = of_address_to_resource(node, 0, &config.reg);
	अगर (ret) अणु
		pr_err("%s: unable to get the register range from device-tree\n",
		       __func__);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "ti,intc-size", &config.num_irqs);
	अगर (ret) अणु
		pr_err("%s: unable to read the 'ti,intc-size' property\n",
		       __func__);
		वापस ret;
	पूर्ण

	वापस davinci_cp_पूर्णांकc_करो_init(&config, node);
पूर्ण
IRQCHIP_DECLARE(cp_पूर्णांकc, "ti,cp-intc", davinci_cp_पूर्णांकc_of_init);
