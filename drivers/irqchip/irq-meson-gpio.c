<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#घोषणा NUM_CHANNEL 8
#घोषणा MAX_INPUT_MUX 256

#घोषणा REG_EDGE_POL	0x00
#घोषणा REG_PIN_03_SEL	0x04
#घोषणा REG_PIN_47_SEL	0x08
#घोषणा REG_FILTER_SEL	0x0c

/* use क्रम A1 like chips */
#घोषणा REG_PIN_A1_SEL	0x04

/*
 * Note: The S905X3 datasheet reports that BOTH_EDGE is controlled by
 * bits 24 to 31. Tests on the actual HW show that these bits are
 * stuck at 0. Bits 8 to 15 are responsive and have the expected
 * effect.
 */
#घोषणा REG_EDGE_POL_EDGE(params, x)	BIT((params)->edge_single_offset + (x))
#घोषणा REG_EDGE_POL_LOW(params, x)	BIT((params)->pol_low_offset + (x))
#घोषणा REG_BOTH_EDGE(params, x)	BIT((params)->edge_both_offset + (x))
#घोषणा REG_EDGE_POL_MASK(params, x)    (	\
		REG_EDGE_POL_EDGE(params, x) |	\
		REG_EDGE_POL_LOW(params, x)  |	\
		REG_BOTH_EDGE(params, x))
#घोषणा REG_PIN_SEL_SHIFT(x)	(((x) % 4) * 8)
#घोषणा REG_FILTER_SEL_SHIFT(x)	((x) * 4)

काष्ठा meson_gpio_irq_controller;
अटल व्योम meson8_gpio_irq_sel_pin(काष्ठा meson_gpio_irq_controller *ctl,
				    अचिन्हित पूर्णांक channel, अचिन्हित दीर्घ hwirq);
अटल व्योम meson_gpio_irq_init_dummy(काष्ठा meson_gpio_irq_controller *ctl);
अटल व्योम meson_a1_gpio_irq_sel_pin(काष्ठा meson_gpio_irq_controller *ctl,
				      अचिन्हित पूर्णांक channel,
				      अचिन्हित दीर्घ hwirq);
अटल व्योम meson_a1_gpio_irq_init(काष्ठा meson_gpio_irq_controller *ctl);

काष्ठा irq_ctl_ops अणु
	व्योम (*gpio_irq_sel_pin)(काष्ठा meson_gpio_irq_controller *ctl,
				 अचिन्हित पूर्णांक channel, अचिन्हित दीर्घ hwirq);
	व्योम (*gpio_irq_init)(काष्ठा meson_gpio_irq_controller *ctl);
पूर्ण;

काष्ठा meson_gpio_irq_params अणु
	अचिन्हित पूर्णांक nr_hwirq;
	bool support_edge_both;
	अचिन्हित पूर्णांक edge_both_offset;
	अचिन्हित पूर्णांक edge_single_offset;
	अचिन्हित पूर्णांक pol_low_offset;
	अचिन्हित पूर्णांक pin_sel_mask;
	काष्ठा irq_ctl_ops ops;
पूर्ण;

#घोषणा INIT_MESON_COMMON(irqs, init, sel)			\
	.nr_hwirq = irqs,					\
	.ops = अणु						\
		.gpio_irq_init = init,				\
		.gpio_irq_sel_pin = sel,			\
	पूर्ण,

#घोषणा INIT_MESON8_COMMON_DATA(irqs)				\
	INIT_MESON_COMMON(irqs, meson_gpio_irq_init_dummy,	\
			  meson8_gpio_irq_sel_pin)		\
	.edge_single_offset = 0,				\
	.pol_low_offset = 16,					\
	.pin_sel_mask = 0xff,					\

#घोषणा INIT_MESON_A1_COMMON_DATA(irqs)				\
	INIT_MESON_COMMON(irqs, meson_a1_gpio_irq_init,		\
			  meson_a1_gpio_irq_sel_pin)		\
	.support_edge_both = true,				\
	.edge_both_offset = 16,					\
	.edge_single_offset = 8,				\
	.pol_low_offset = 0,					\
	.pin_sel_mask = 0x7f,					\

अटल स्थिर काष्ठा meson_gpio_irq_params meson8_params = अणु
	INIT_MESON8_COMMON_DATA(134)
पूर्ण;

अटल स्थिर काष्ठा meson_gpio_irq_params meson8b_params = अणु
	INIT_MESON8_COMMON_DATA(119)
पूर्ण;

अटल स्थिर काष्ठा meson_gpio_irq_params gxbb_params = अणु
	INIT_MESON8_COMMON_DATA(133)
पूर्ण;

अटल स्थिर काष्ठा meson_gpio_irq_params gxl_params = अणु
	INIT_MESON8_COMMON_DATA(110)
पूर्ण;

अटल स्थिर काष्ठा meson_gpio_irq_params axg_params = अणु
	INIT_MESON8_COMMON_DATA(100)
पूर्ण;

अटल स्थिर काष्ठा meson_gpio_irq_params sm1_params = अणु
	INIT_MESON8_COMMON_DATA(100)
	.support_edge_both = true,
	.edge_both_offset = 8,
पूर्ण;

अटल स्थिर काष्ठा meson_gpio_irq_params a1_params = अणु
	INIT_MESON_A1_COMMON_DATA(62)
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_irq_gpio_matches[] = अणु
	अणु .compatible = "amlogic,meson8-gpio-intc", .data = &meson8_params पूर्ण,
	अणु .compatible = "amlogic,meson8b-gpio-intc", .data = &meson8b_params पूर्ण,
	अणु .compatible = "amlogic,meson-gxbb-gpio-intc", .data = &gxbb_params पूर्ण,
	अणु .compatible = "amlogic,meson-gxl-gpio-intc", .data = &gxl_params पूर्ण,
	अणु .compatible = "amlogic,meson-axg-gpio-intc", .data = &axg_params पूर्ण,
	अणु .compatible = "amlogic,meson-g12a-gpio-intc", .data = &axg_params पूर्ण,
	अणु .compatible = "amlogic,meson-sm1-gpio-intc", .data = &sm1_params पूर्ण,
	अणु .compatible = "amlogic,meson-a1-gpio-intc", .data = &a1_params पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा meson_gpio_irq_controller अणु
	स्थिर काष्ठा meson_gpio_irq_params *params;
	व्योम __iomem *base;
	u32 channel_irqs[NUM_CHANNEL];
	DECLARE_BITMAP(channel_map, NUM_CHANNEL);
	spinlock_t lock;
पूर्ण;

अटल व्योम meson_gpio_irq_update_bits(काष्ठा meson_gpio_irq_controller *ctl,
				       अचिन्हित पूर्णांक reg, u32 mask, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&ctl->lock, flags);

	पंचांगp = पढ़ोl_relaxed(ctl->base + reg);
	पंचांगp &= ~mask;
	पंचांगp |= val;
	ग_लिखोl_relaxed(पंचांगp, ctl->base + reg);

	spin_unlock_irqrestore(&ctl->lock, flags);
पूर्ण

अटल व्योम meson_gpio_irq_init_dummy(काष्ठा meson_gpio_irq_controller *ctl)
अणु
पूर्ण

अटल व्योम meson8_gpio_irq_sel_pin(काष्ठा meson_gpio_irq_controller *ctl,
				    अचिन्हित पूर्णांक channel, अचिन्हित दीर्घ hwirq)
अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक bit_offset;

	reg_offset = (channel < 4) ? REG_PIN_03_SEL : REG_PIN_47_SEL;
	bit_offset = REG_PIN_SEL_SHIFT(channel);

	meson_gpio_irq_update_bits(ctl, reg_offset,
				   ctl->params->pin_sel_mask << bit_offset,
				   hwirq << bit_offset);
पूर्ण

अटल व्योम meson_a1_gpio_irq_sel_pin(काष्ठा meson_gpio_irq_controller *ctl,
				      अचिन्हित पूर्णांक channel,
				      अचिन्हित दीर्घ hwirq)
अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक bit_offset;

	bit_offset = ((channel % 2) == 0) ? 0 : 16;
	reg_offset = REG_PIN_A1_SEL + ((channel / 2) << 2);

	meson_gpio_irq_update_bits(ctl, reg_offset,
				   ctl->params->pin_sel_mask << bit_offset,
				   hwirq << bit_offset);
पूर्ण

/* For a1 or later chips like a1 there is a चयन to enable/disable irq */
अटल व्योम meson_a1_gpio_irq_init(काष्ठा meson_gpio_irq_controller *ctl)
अणु
	meson_gpio_irq_update_bits(ctl, REG_EDGE_POL, BIT(31), BIT(31));
पूर्ण

अटल पूर्णांक
meson_gpio_irq_request_channel(काष्ठा meson_gpio_irq_controller *ctl,
			       अचिन्हित दीर्घ  hwirq,
			       u32 **channel_hwirq)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक idx;

	spin_lock_irqsave(&ctl->lock, flags);

	/* Find a मुक्त channel */
	idx = find_first_zero_bit(ctl->channel_map, NUM_CHANNEL);
	अगर (idx >= NUM_CHANNEL) अणु
		spin_unlock_irqrestore(&ctl->lock, flags);
		pr_err("No channel available\n");
		वापस -ENOSPC;
	पूर्ण

	/* Mark the channel as used */
	set_bit(idx, ctl->channel_map);

	spin_unlock_irqrestore(&ctl->lock, flags);

	/*
	 * Setup the mux of the channel to route the संकेत of the pad
	 * to the appropriate input of the GIC
	 */
	ctl->params->ops.gpio_irq_sel_pin(ctl, idx, hwirq);

	/*
	 * Get the hwirq number asचिन्हित to this channel through
	 * a poपूर्णांकer the channel_irq table. The added benefit of this
	 * method is that we can also retrieve the channel index with
	 * it, using the table base.
	 */
	*channel_hwirq = &(ctl->channel_irqs[idx]);

	pr_debug("hwirq %lu assigned to channel %d - irq %u\n",
		 hwirq, idx, **channel_hwirq);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
meson_gpio_irq_get_channel_idx(काष्ठा meson_gpio_irq_controller *ctl,
			       u32 *channel_hwirq)
अणु
	वापस channel_hwirq - ctl->channel_irqs;
पूर्ण

अटल व्योम
meson_gpio_irq_release_channel(काष्ठा meson_gpio_irq_controller *ctl,
			       u32 *channel_hwirq)
अणु
	अचिन्हित पूर्णांक idx;

	idx = meson_gpio_irq_get_channel_idx(ctl, channel_hwirq);
	clear_bit(idx, ctl->channel_map);
पूर्ण

अटल पूर्णांक meson_gpio_irq_type_setup(काष्ठा meson_gpio_irq_controller *ctl,
				     अचिन्हित पूर्णांक type,
				     u32 *channel_hwirq)
अणु
	u32 val = 0;
	अचिन्हित पूर्णांक idx;
	स्थिर काष्ठा meson_gpio_irq_params *params;

	params = ctl->params;
	idx = meson_gpio_irq_get_channel_idx(ctl, channel_hwirq);

	/*
	 * The controller has a filter block to operate in either LEVEL or
	 * EDGE mode, then संकेत is sent to the GIC. To enable LEVEL_LOW and
	 * EDGE_FALLING support (which the GIC करोes not support), the filter
	 * block is also able to invert the input संकेत it माला_लो beक्रमe
	 * providing it to the GIC.
	 */
	type &= IRQ_TYPE_SENSE_MASK;

	/*
	 * New controller support EDGE_BOTH trigger. This setting takes
	 * precedence over the other edge/polarity settings
	 */
	अगर (type == IRQ_TYPE_EDGE_BOTH) अणु
		अगर (!params->support_edge_both)
			वापस -EINVAL;

		val |= REG_BOTH_EDGE(params, idx);
	पूर्ण अन्यथा अणु
		अगर (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))
			val |= REG_EDGE_POL_EDGE(params, idx);

		अगर (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_EDGE_FALLING))
			val |= REG_EDGE_POL_LOW(params, idx);
	पूर्ण

	meson_gpio_irq_update_bits(ctl, REG_EDGE_POL,
				   REG_EDGE_POL_MASK(params, idx), val);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक meson_gpio_irq_type_output(अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक sense = type & IRQ_TYPE_SENSE_MASK;

	type &= ~IRQ_TYPE_SENSE_MASK;

	/*
	 * The polarity of the संकेत provided to the GIC should always
	 * be high.
	 */
	अगर (sense & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW))
		type |= IRQ_TYPE_LEVEL_HIGH;
	अन्यथा
		type |= IRQ_TYPE_EDGE_RISING;

	वापस type;
पूर्ण

अटल पूर्णांक meson_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा meson_gpio_irq_controller *ctl = data->करोमुख्य->host_data;
	u32 *channel_hwirq = irq_data_get_irq_chip_data(data);
	पूर्णांक ret;

	ret = meson_gpio_irq_type_setup(ctl, type, channel_hwirq);
	अगर (ret)
		वापस ret;

	वापस irq_chip_set_type_parent(data,
					meson_gpio_irq_type_output(type));
पूर्ण

अटल काष्ठा irq_chip meson_gpio_irq_chip = अणु
	.name			= "meson-gpio-irqchip",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_type		= meson_gpio_irq_set_type,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
	.flags			= IRQCHIP_SET_TYPE_MASKED,
पूर्ण;

अटल पूर्णांक meson_gpio_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
					   काष्ठा irq_fwspec *fwspec,
					   अचिन्हित दीर्घ *hwirq,
					   अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode) && fwspec->param_count == 2) अणु
		*hwirq	= fwspec->param[0];
		*type	= fwspec->param[1];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक meson_gpio_irq_allocate_gic_irq(काष्ठा irq_करोमुख्य *करोमुख्य,
					   अचिन्हित पूर्णांक virq,
					   u32 hwirq,
					   अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_fwspec fwspec;

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = 0;	/* SPI */
	fwspec.param[1] = hwirq;
	fwspec.param[2] = meson_gpio_irq_type_output(type);

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
पूर्ण

अटल पूर्णांक meson_gpio_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq,
				       अचिन्हित पूर्णांक nr_irqs,
				       व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा meson_gpio_irq_controller *ctl = करोमुख्य->host_data;
	अचिन्हित दीर्घ hwirq;
	u32 *channel_hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	अगर (WARN_ON(nr_irqs != 1))
		वापस -EINVAL;

	ret = meson_gpio_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	ret = meson_gpio_irq_request_channel(ctl, hwirq, &channel_hwirq);
	अगर (ret)
		वापस ret;

	ret = meson_gpio_irq_allocate_gic_irq(करोमुख्य, virq,
					      *channel_hwirq, type);
	अगर (ret < 0) अणु
		pr_err("failed to allocate gic irq %u\n", *channel_hwirq);
		meson_gpio_irq_release_channel(ctl, channel_hwirq);
		वापस ret;
	पूर्ण

	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
				      &meson_gpio_irq_chip, channel_hwirq);

	वापस 0;
पूर्ण

अटल व्योम meson_gpio_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq,
				       अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा meson_gpio_irq_controller *ctl = करोमुख्य->host_data;
	काष्ठा irq_data *irq_data;
	u32 *channel_hwirq;

	अगर (WARN_ON(nr_irqs != 1))
		वापस;

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, 1);

	irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	channel_hwirq = irq_data_get_irq_chip_data(irq_data);

	meson_gpio_irq_release_channel(ctl, channel_hwirq);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops meson_gpio_irq_करोमुख्य_ops = अणु
	.alloc		= meson_gpio_irq_करोमुख्य_alloc,
	.मुक्त		= meson_gpio_irq_करोमुख्य_मुक्त,
	.translate	= meson_gpio_irq_करोमुख्य_translate,
पूर्ण;

अटल पूर्णांक __init meson_gpio_irq_parse_dt(काष्ठा device_node *node,
					  काष्ठा meson_gpio_irq_controller *ctl)
अणु
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = of_match_node(meson_irq_gpio_matches, node);
	अगर (!match)
		वापस -ENODEV;

	ctl->params = match->data;

	ret = of_property_पढ़ो_variable_u32_array(node,
						  "amlogic,channel-interrupts",
						  ctl->channel_irqs,
						  NUM_CHANNEL,
						  NUM_CHANNEL);
	अगर (ret < 0) अणु
		pr_err("can't get %d channel interrupts\n", NUM_CHANNEL);
		वापस ret;
	पूर्ण

	ctl->params->ops.gpio_irq_init(ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक __init meson_gpio_irq_of_init(काष्ठा device_node *node,
					 काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *parent_करोमुख्य;
	काष्ठा meson_gpio_irq_controller *ctl;
	पूर्णांक ret;

	अगर (!parent) अणु
		pr_err("missing parent interrupt node\n");
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("unable to obtain parent domain\n");
		वापस -ENXIO;
	पूर्ण

	ctl = kzalloc(माप(*ctl), GFP_KERNEL);
	अगर (!ctl)
		वापस -ENOMEM;

	spin_lock_init(&ctl->lock);

	ctl->base = of_iomap(node, 0);
	अगर (!ctl->base) अणु
		ret = -ENOMEM;
		जाओ मुक्त_ctl;
	पूर्ण

	ret = meson_gpio_irq_parse_dt(node, ctl);
	अगर (ret)
		जाओ मुक्त_channel_irqs;

	करोमुख्य = irq_करोमुख्य_create_hierarchy(parent_करोमुख्य, 0,
					     ctl->params->nr_hwirq,
					     of_node_to_fwnode(node),
					     &meson_gpio_irq_करोमुख्य_ops,
					     ctl);
	अगर (!करोमुख्य) अणु
		pr_err("failed to add domain\n");
		ret = -ENODEV;
		जाओ मुक्त_channel_irqs;
	पूर्ण

	pr_info("%d to %d gpio interrupt mux initialized\n",
		ctl->params->nr_hwirq, NUM_CHANNEL);

	वापस 0;

मुक्त_channel_irqs:
	iounmap(ctl->base);
मुक्त_ctl:
	kमुक्त(ctl);

	वापस ret;
पूर्ण

IRQCHIP_DECLARE(meson_gpio_पूर्णांकc, "amlogic,meson-gpio-intc",
		meson_gpio_irq_of_init);
