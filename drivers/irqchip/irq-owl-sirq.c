<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi Owl SoCs SIRQ पूर्णांकerrupt controller driver
 *
 * Copyright (C) 2014 Actions Semi Inc.
 * David Liu <liuwei@actions-semi.com>
 *
 * Author: Parthiban Nallathambi <pn@denx.de>
 * Author: Saravanan Sekar <sravanhome@gmail.com>
 * Author: Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा NUM_SIRQ			3

#घोषणा INTC_EXTCTL_PENDING		BIT(0)
#घोषणा INTC_EXTCTL_CLK_SEL		BIT(4)
#घोषणा INTC_EXTCTL_EN			BIT(5)
#घोषणा INTC_EXTCTL_TYPE_MASK		GENMASK(7, 6)
#घोषणा INTC_EXTCTL_TYPE_HIGH		0
#घोषणा INTC_EXTCTL_TYPE_LOW		BIT(6)
#घोषणा INTC_EXTCTL_TYPE_RISING		BIT(7)
#घोषणा INTC_EXTCTL_TYPE_FALLING	(BIT(6) | BIT(7))

/* S500 & S700 SIRQ control रेजिस्टर masks */
#घोषणा INTC_EXTCTL_SIRQ0_MASK		GENMASK(23, 16)
#घोषणा INTC_EXTCTL_SIRQ1_MASK		GENMASK(15, 8)
#घोषणा INTC_EXTCTL_SIRQ2_MASK		GENMASK(7, 0)

/* S900 SIRQ control रेजिस्टर offsets, relative to controller base address */
#घोषणा INTC_EXTCTL0			0x0000
#घोषणा INTC_EXTCTL1			0x0328
#घोषणा INTC_EXTCTL2			0x032c

काष्ठा owl_sirq_params अणु
	/* INTC_EXTCTL reg shared क्रम all three SIRQ lines */
	bool reg_shared;
	/* INTC_EXTCTL reg offsets relative to controller base address */
	u16 reg_offset[NUM_SIRQ];
पूर्ण;

काष्ठा owl_sirq_chip_data अणु
	स्थिर काष्ठा owl_sirq_params	*params;
	व्योम __iomem			*base;
	raw_spinlock_t			lock;
	u32				ext_irqs[NUM_SIRQ];
पूर्ण;

/* S500 & S700 SoCs */
अटल स्थिर काष्ठा owl_sirq_params owl_sirq_s500_params = अणु
	.reg_shared = true,
	.reg_offset = अणु 0, 0, 0 पूर्ण,
पूर्ण;

/* S900 SoC */
अटल स्थिर काष्ठा owl_sirq_params owl_sirq_s900_params = अणु
	.reg_shared = false,
	.reg_offset = अणु INTC_EXTCTL0, INTC_EXTCTL1, INTC_EXTCTL2 पूर्ण,
पूर्ण;

अटल u32 owl_field_get(u32 val, u32 index)
अणु
	चयन (index) अणु
	हाल 0:
		वापस FIELD_GET(INTC_EXTCTL_SIRQ0_MASK, val);
	हाल 1:
		वापस FIELD_GET(INTC_EXTCTL_SIRQ1_MASK, val);
	हाल 2:
	शेष:
		वापस FIELD_GET(INTC_EXTCTL_SIRQ2_MASK, val);
	पूर्ण
पूर्ण

अटल u32 owl_field_prep(u32 val, u32 index)
अणु
	चयन (index) अणु
	हाल 0:
		वापस FIELD_PREP(INTC_EXTCTL_SIRQ0_MASK, val);
	हाल 1:
		वापस FIELD_PREP(INTC_EXTCTL_SIRQ1_MASK, val);
	हाल 2:
	शेष:
		वापस FIELD_PREP(INTC_EXTCTL_SIRQ2_MASK, val);
	पूर्ण
पूर्ण

अटल u32 owl_sirq_पढ़ो_extctl(काष्ठा owl_sirq_chip_data *data, u32 index)
अणु
	u32 val;

	val = पढ़ोl_relaxed(data->base + data->params->reg_offset[index]);
	अगर (data->params->reg_shared)
		val = owl_field_get(val, index);

	वापस val;
पूर्ण

अटल व्योम owl_sirq_ग_लिखो_extctl(काष्ठा owl_sirq_chip_data *data,
				  u32 extctl, u32 index)
अणु
	u32 val;

	अगर (data->params->reg_shared) अणु
		val = पढ़ोl_relaxed(data->base + data->params->reg_offset[index]);
		val &= ~owl_field_prep(0xff, index);
		extctl = owl_field_prep(extctl, index) | val;
	पूर्ण

	ग_लिखोl_relaxed(extctl, data->base + data->params->reg_offset[index]);
पूर्ण

अटल व्योम owl_sirq_clear_set_extctl(काष्ठा owl_sirq_chip_data *d,
				      u32 clear, u32 set, u32 index)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&d->lock, flags);
	val = owl_sirq_पढ़ो_extctl(d, index);
	val &= ~clear;
	val |= set;
	owl_sirq_ग_लिखो_extctl(d, val, index);
	raw_spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

अटल व्योम owl_sirq_eoi(काष्ठा irq_data *data)
अणु
	काष्ठा owl_sirq_chip_data *chip_data = irq_data_get_irq_chip_data(data);

	/*
	 * Software must clear बाह्यal पूर्णांकerrupt pending, when पूर्णांकerrupt type
	 * is edge triggered, so we need per SIRQ based clearing.
	 */
	अगर (!irqd_is_level_type(data))
		owl_sirq_clear_set_extctl(chip_data, 0, INTC_EXTCTL_PENDING,
					  data->hwirq);

	irq_chip_eoi_parent(data);
पूर्ण

अटल व्योम owl_sirq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा owl_sirq_chip_data *chip_data = irq_data_get_irq_chip_data(data);

	owl_sirq_clear_set_extctl(chip_data, INTC_EXTCTL_EN, 0, data->hwirq);
	irq_chip_mask_parent(data);
पूर्ण

अटल व्योम owl_sirq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा owl_sirq_chip_data *chip_data = irq_data_get_irq_chip_data(data);

	owl_sirq_clear_set_extctl(chip_data, 0, INTC_EXTCTL_EN, data->hwirq);
	irq_chip_unmask_parent(data);
पूर्ण

/*
 * GIC करोes not handle falling edge or active low, hence SIRQ shall be
 * programmed to convert falling edge to rising edge संकेत and active
 * low to active high संकेत.
 */
अटल पूर्णांक owl_sirq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा owl_sirq_chip_data *chip_data = irq_data_get_irq_chip_data(data);
	u32 sirq_type;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		sirq_type = INTC_EXTCTL_TYPE_LOW;
		type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		sirq_type = INTC_EXTCTL_TYPE_HIGH;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		sirq_type = INTC_EXTCTL_TYPE_FALLING;
		type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		sirq_type = INTC_EXTCTL_TYPE_RISING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	owl_sirq_clear_set_extctl(chip_data, INTC_EXTCTL_TYPE_MASK, sirq_type,
				  data->hwirq);

	वापस irq_chip_set_type_parent(data, type);
पूर्ण

अटल काष्ठा irq_chip owl_sirq_chip = अणु
	.name		= "owl-sirq",
	.irq_mask	= owl_sirq_mask,
	.irq_unmask	= owl_sirq_unmask,
	.irq_eoi	= owl_sirq_eoi,
	.irq_set_type	= owl_sirq_set_type,
	.irq_retrigger	= irq_chip_retrigger_hierarchy,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक owl_sirq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				     काष्ठा irq_fwspec *fwspec,
				     अचिन्हित दीर्घ *hwirq,
				     अचिन्हित पूर्णांक *type)
अणु
	अगर (!is_of_node(fwspec->fwnode))
		वापस -EINVAL;

	अगर (fwspec->param_count != 2 || fwspec->param[0] >= NUM_SIRQ)
		वापस -EINVAL;

	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];

	वापस 0;
पूर्ण

अटल पूर्णांक owl_sirq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा owl_sirq_chip_data *chip_data = करोमुख्य->host_data;
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	अगर (WARN_ON(nr_irqs != 1))
		वापस -EINVAL;

	ret = owl_sirq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq, &owl_sirq_chip,
				      chip_data);

	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 3;
	parent_fwspec.param[0] = GIC_SPI;
	parent_fwspec.param[1] = chip_data->ext_irqs[hwirq];
	parent_fwspec.param[2] = type;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops owl_sirq_करोमुख्य_ops = अणु
	.translate	= owl_sirq_करोमुख्य_translate,
	.alloc		= owl_sirq_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init owl_sirq_init(स्थिर काष्ठा owl_sirq_params *params,
				काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *parent_करोमुख्य;
	काष्ठा owl_sirq_chip_data *chip_data;
	पूर्णांक ret, i;

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: failed to find sirq parent domain\n", node);
		वापस -ENXIO;
	पूर्ण

	chip_data = kzalloc(माप(*chip_data), GFP_KERNEL);
	अगर (!chip_data)
		वापस -ENOMEM;

	raw_spin_lock_init(&chip_data->lock);

	chip_data->params = params;

	chip_data->base = of_iomap(node, 0);
	अगर (!chip_data->base) अणु
		pr_err("%pOF: failed to map sirq registers\n", node);
		ret = -ENXIO;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < NUM_SIRQ; i++) अणु
		काष्ठा of_phandle_args irq;

		ret = of_irq_parse_one(node, i, &irq);
		अगर (ret) अणु
			pr_err("%pOF: failed to parse interrupt %d\n", node, i);
			जाओ out_unmap;
		पूर्ण

		अगर (WARN_ON(irq.args_count != 3)) अणु
			ret = -EINVAL;
			जाओ out_unmap;
		पूर्ण

		chip_data->ext_irqs[i] = irq.args[1];

		/* Set 24MHz बाह्यal पूर्णांकerrupt घड़ी freq */
		owl_sirq_clear_set_extctl(chip_data, 0, INTC_EXTCTL_CLK_SEL, i);
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, NUM_SIRQ, node,
					  &owl_sirq_करोमुख्य_ops, chip_data);
	अगर (!करोमुख्य) अणु
		pr_err("%pOF: failed to add domain\n", node);
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	वापस 0;

out_unmap:
	iounmap(chip_data->base);
out_मुक्त:
	kमुक्त(chip_data);

	वापस ret;
पूर्ण

अटल पूर्णांक __init owl_sirq_s500_of_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	वापस owl_sirq_init(&owl_sirq_s500_params, node, parent);
पूर्ण

IRQCHIP_DECLARE(owl_sirq_s500, "actions,s500-sirq", owl_sirq_s500_of_init);
IRQCHIP_DECLARE(owl_sirq_s700, "actions,s700-sirq", owl_sirq_s500_of_init);

अटल पूर्णांक __init owl_sirq_s900_of_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	वापस owl_sirq_init(&owl_sirq_s900_params, node, parent);
पूर्ण

IRQCHIP_DECLARE(owl_sirq_s900, "actions,s900-sirq", owl_sirq_s900_of_init);
