<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2017 Socionext Inc.
//   Author: Masahiro Yamada <yamada.masahiro@socionext.com>

#समावेश <linux/bits.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <dt-bindings/gpio/uniphier-gpपन.स>

#घोषणा UNIPHIER_GPIO_IRQ_MAX_NUM	24

#घोषणा UNIPHIER_GPIO_PORT_DATA		0x0	/* data */
#घोषणा UNIPHIER_GPIO_PORT_सूची		0x4	/* direction (1:in, 0:out) */
#घोषणा UNIPHIER_GPIO_IRQ_EN		0x90	/* irq enable */
#घोषणा UNIPHIER_GPIO_IRQ_MODE		0x94	/* irq mode (1: both edge) */
#घोषणा UNIPHIER_GPIO_IRQ_FLT_EN	0x98	/* noise filter enable */
#घोषणा UNIPHIER_GPIO_IRQ_FLT_CYC	0x9c	/* noise filter घड़ी cycle */

काष्ठा uniphier_gpio_priv अणु
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip irq_chip;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम __iomem *regs;
	spinlock_t lock;
	u32 saved_vals[];
पूर्ण;

अटल अचिन्हित पूर्णांक uniphier_gpio_bank_to_reg(अचिन्हित पूर्णांक bank)
अणु
	अचिन्हित पूर्णांक reg;

	reg = (bank + 1) * 8;

	/*
	 * Unक्रमtunately, the GPIO port रेजिस्टरs are not contiguous because
	 * offset 0x90-0x9f is used क्रम IRQ.  Add 0x10 when crossing the region.
	 */
	अगर (reg >= UNIPHIER_GPIO_IRQ_EN)
		reg += 0x10;

	वापस reg;
पूर्ण

अटल व्योम uniphier_gpio_get_bank_and_mask(अचिन्हित पूर्णांक offset,
					    अचिन्हित पूर्णांक *bank, u32 *mask)
अणु
	*bank = offset / UNIPHIER_GPIO_LINES_PER_BANK;
	*mask = BIT(offset % UNIPHIER_GPIO_LINES_PER_BANK);
पूर्ण

अटल व्योम uniphier_gpio_reg_update(काष्ठा uniphier_gpio_priv *priv,
				     अचिन्हित पूर्णांक reg, u32 mask, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&priv->lock, flags);
	पंचांगp = पढ़ोl(priv->regs + reg);
	पंचांगp &= ~mask;
	पंचांगp |= mask & val;
	ग_लिखोl(पंचांगp, priv->regs + reg);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम uniphier_gpio_bank_ग_लिखो(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक bank,
				     अचिन्हित पूर्णांक reg, u32 mask, u32 val)
अणु
	काष्ठा uniphier_gpio_priv *priv = gpiochip_get_data(chip);

	अगर (!mask)
		वापस;

	uniphier_gpio_reg_update(priv, uniphier_gpio_bank_to_reg(bank) + reg,
				 mask, val);
पूर्ण

अटल व्योम uniphier_gpio_offset_ग_लिखो(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक reg,
				       पूर्णांक val)
अणु
	अचिन्हित पूर्णांक bank;
	u32 mask;

	uniphier_gpio_get_bank_and_mask(offset, &bank, &mask);

	uniphier_gpio_bank_ग_लिखो(chip, bank, reg, mask, val ? mask : 0);
पूर्ण

अटल पूर्णांक uniphier_gpio_offset_पढ़ो(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा uniphier_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank, reg_offset;
	u32 mask;

	uniphier_gpio_get_bank_and_mask(offset, &bank, &mask);
	reg_offset = uniphier_gpio_bank_to_reg(bank) + reg;

	वापस !!(पढ़ोl(priv->regs + reg_offset) & mask);
पूर्ण

अटल पूर्णांक uniphier_gpio_get_direction(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	अगर (uniphier_gpio_offset_पढ़ो(chip, offset, UNIPHIER_GPIO_PORT_सूची))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक uniphier_gpio_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset)
अणु
	uniphier_gpio_offset_ग_लिखो(chip, offset, UNIPHIER_GPIO_PORT_सूची, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_gpio_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	uniphier_gpio_offset_ग_लिखो(chip, offset, UNIPHIER_GPIO_PORT_DATA, val);
	uniphier_gpio_offset_ग_लिखो(chip, offset, UNIPHIER_GPIO_PORT_सूची, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस uniphier_gpio_offset_पढ़ो(chip, offset, UNIPHIER_GPIO_PORT_DATA);
पूर्ण

अटल व्योम uniphier_gpio_set(काष्ठा gpio_chip *chip,
			      अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	uniphier_gpio_offset_ग_लिखो(chip, offset, UNIPHIER_GPIO_PORT_DATA, val);
पूर्ण

अटल व्योम uniphier_gpio_set_multiple(काष्ठा gpio_chip *chip,
				       अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	अचिन्हित दीर्घ i, bank, bank_mask, bank_bits;

	क्रम_each_set_clump8(i, bank_mask, mask, chip->ngpio) अणु
		bank = i / UNIPHIER_GPIO_LINES_PER_BANK;
		bank_bits = biपंचांगap_get_value8(bits, i);

		uniphier_gpio_bank_ग_लिखो(chip, bank, UNIPHIER_GPIO_PORT_DATA,
					 bank_mask, bank_bits);
	पूर्ण
पूर्ण

अटल पूर्णांक uniphier_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा irq_fwspec fwspec;

	अगर (offset < UNIPHIER_GPIO_IRQ_OFFSET)
		वापस -ENXIO;

	fwspec.fwnode = of_node_to_fwnode(chip->parent->of_node);
	fwspec.param_count = 2;
	fwspec.param[0] = offset - UNIPHIER_GPIO_IRQ_OFFSET;
	/*
	 * IRQ_TYPE_NONE is rejected by the parent irq करोमुख्य. Set LEVEL_HIGH
	 * temporarily. Anyway, ->irq_set_type() will override it later.
	 */
	fwspec.param[1] = IRQ_TYPE_LEVEL_HIGH;

	वापस irq_create_fwspec_mapping(&fwspec);
पूर्ण

अटल व्योम uniphier_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा uniphier_gpio_priv *priv = data->chip_data;
	u32 mask = BIT(data->hwirq);

	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_EN, mask, 0);

	वापस irq_chip_mask_parent(data);
पूर्ण

अटल व्योम uniphier_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा uniphier_gpio_priv *priv = data->chip_data;
	u32 mask = BIT(data->hwirq);

	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_EN, mask, mask);

	वापस irq_chip_unmask_parent(data);
पूर्ण

अटल पूर्णांक uniphier_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा uniphier_gpio_priv *priv = data->chip_data;
	u32 mask = BIT(data->hwirq);
	u32 val = 0;

	अगर (type == IRQ_TYPE_EDGE_BOTH) अणु
		val = mask;
		type = IRQ_TYPE_EDGE_FALLING;
	पूर्ण

	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_MODE, mask, val);
	/* To enable both edge detection, the noise filter must be enabled. */
	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_FLT_EN, mask, val);

	वापस irq_chip_set_type_parent(data, type);
पूर्ण

अटल पूर्णांक uniphier_gpio_irq_get_parent_hwirq(काष्ठा uniphier_gpio_priv *priv,
					      अचिन्हित पूर्णांक hwirq)
अणु
	काष्ठा device_node *np = priv->chip.parent->of_node;
	स्थिर __be32 *range;
	u32 base, parent_base, size;
	पूर्णांक len;

	range = of_get_property(np, "socionext,interrupt-ranges", &len);
	अगर (!range)
		वापस -EINVAL;

	len /= माप(*range);

	क्रम (; len >= 3; len -= 3) अणु
		base = be32_to_cpu(*range++);
		parent_base = be32_to_cpu(*range++);
		size = be32_to_cpu(*range++);

		अगर (base <= hwirq && hwirq < base + size)
			वापस hwirq - base + parent_base;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक uniphier_gpio_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
					      काष्ठा irq_fwspec *fwspec,
					      अचिन्हित दीर्घ *out_hwirq,
					      अचिन्हित पूर्णांक *out_type)
अणु
	अगर (WARN_ON(fwspec->param_count < 2))
		वापस -EINVAL;

	*out_hwirq = fwspec->param[0];
	*out_type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_gpio_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					  अचिन्हित पूर्णांक virq,
					  अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा uniphier_gpio_priv *priv = करोमुख्य->host_data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	अगर (WARN_ON(nr_irqs != 1))
		वापस -EINVAL;

	ret = uniphier_gpio_irq_करोमुख्य_translate(करोमुख्य, arg, &hwirq, &type);
	अगर (ret)
		वापस ret;

	ret = uniphier_gpio_irq_get_parent_hwirq(priv, hwirq);
	अगर (ret < 0)
		वापस ret;

	/* parent is UniPhier AIDET */
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 2;
	parent_fwspec.param[0] = ret;
	parent_fwspec.param[1] = (type == IRQ_TYPE_EDGE_BOTH) ?
						IRQ_TYPE_EDGE_FALLING : type;

	ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					    &priv->irq_chip, priv);
	अगर (ret)
		वापस ret;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &parent_fwspec);
पूर्ण

अटल पूर्णांक uniphier_gpio_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
					     काष्ठा irq_data *data, bool early)
अणु
	काष्ठा uniphier_gpio_priv *priv = करोमुख्य->host_data;
	काष्ठा gpio_chip *chip = &priv->chip;

	वापस gpiochip_lock_as_irq(chip, data->hwirq + UNIPHIER_GPIO_IRQ_OFFSET);
पूर्ण

अटल व्योम uniphier_gpio_irq_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
						काष्ठा irq_data *data)
अणु
	काष्ठा uniphier_gpio_priv *priv = करोमुख्य->host_data;
	काष्ठा gpio_chip *chip = &priv->chip;

	gpiochip_unlock_as_irq(chip, data->hwirq + UNIPHIER_GPIO_IRQ_OFFSET);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops uniphier_gpio_irq_करोमुख्य_ops = अणु
	.alloc = uniphier_gpio_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_common,
	.activate = uniphier_gpio_irq_करोमुख्य_activate,
	.deactivate = uniphier_gpio_irq_करोमुख्य_deactivate,
	.translate = uniphier_gpio_irq_करोमुख्य_translate,
पूर्ण;

अटल व्योम uniphier_gpio_hw_init(काष्ठा uniphier_gpio_priv *priv)
अणु
	/*
	 * Due to the hardware design, the noise filter must be enabled to
	 * detect both edge पूर्णांकerrupts.  This filter is पूर्णांकended to हटाओ the
	 * noise from the irq lines.  It करोes not work क्रम GPIO input, so GPIO
	 * debounce is not supported.  Unक्रमtunately, the filter period is
	 * shared among all irq lines.  Just choose a sensible period here.
	 */
	ग_लिखोl(0xff, priv->regs + UNIPHIER_GPIO_IRQ_FLT_CYC);
पूर्ण

अटल अचिन्हित पूर्णांक uniphier_gpio_get_nbanks(अचिन्हित पूर्णांक ngpio)
अणु
	वापस DIV_ROUND_UP(ngpio, UNIPHIER_GPIO_LINES_PER_BANK);
पूर्ण

अटल पूर्णांक uniphier_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent_np;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा uniphier_gpio_priv *priv;
	काष्ठा gpio_chip *chip;
	काष्ठा irq_chip *irq_chip;
	अचिन्हित पूर्णांक nregs;
	u32 ngpios;
	पूर्णांक ret;

	parent_np = of_irq_find_parent(dev->of_node);
	अगर (!parent_np)
		वापस -ENXIO;

	parent_करोमुख्य = irq_find_host(parent_np);
	of_node_put(parent_np);
	अगर (!parent_करोमुख्य)
		वापस -EPROBE_DEFER;

	ret = of_property_पढ़ो_u32(dev->of_node, "ngpios", &ngpios);
	अगर (ret)
		वापस ret;

	nregs = uniphier_gpio_get_nbanks(ngpios) * 2 + 3;
	priv = devm_kzalloc(dev, काष्ठा_size(priv, saved_vals, nregs),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	spin_lock_init(&priv->lock);

	chip = &priv->chip;
	chip->label = dev_name(dev);
	chip->parent = dev;
	chip->request = gpiochip_generic_request;
	chip->मुक्त = gpiochip_generic_मुक्त;
	chip->get_direction = uniphier_gpio_get_direction;
	chip->direction_input = uniphier_gpio_direction_input;
	chip->direction_output = uniphier_gpio_direction_output;
	chip->get = uniphier_gpio_get;
	chip->set = uniphier_gpio_set;
	chip->set_multiple = uniphier_gpio_set_multiple;
	chip->to_irq = uniphier_gpio_to_irq;
	chip->base = -1;
	chip->ngpio = ngpios;

	irq_chip = &priv->irq_chip;
	irq_chip->name = dev_name(dev);
	irq_chip->irq_mask = uniphier_gpio_irq_mask;
	irq_chip->irq_unmask = uniphier_gpio_irq_unmask;
	irq_chip->irq_eoi = irq_chip_eoi_parent;
	irq_chip->irq_set_affinity = irq_chip_set_affinity_parent;
	irq_chip->irq_set_type = uniphier_gpio_irq_set_type;

	uniphier_gpio_hw_init(priv);

	ret = devm_gpiochip_add_data(dev, chip, priv);
	अगर (ret)
		वापस ret;

	priv->करोमुख्य = irq_करोमुख्य_create_hierarchy(
					parent_करोमुख्य, 0,
					UNIPHIER_GPIO_IRQ_MAX_NUM,
					of_node_to_fwnode(dev->of_node),
					&uniphier_gpio_irq_करोमुख्य_ops, priv);
	अगर (!priv->करोमुख्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_gpio_priv *priv = platक्रमm_get_drvdata(pdev);

	irq_करोमुख्य_हटाओ(priv->करोमुख्य);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा uniphier_gpio_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक nbanks = uniphier_gpio_get_nbanks(priv->chip.ngpio);
	u32 *val = priv->saved_vals;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i;

	क्रम (i = 0; i < nbanks; i++) अणु
		reg = uniphier_gpio_bank_to_reg(i);

		*val++ = पढ़ोl(priv->regs + reg + UNIPHIER_GPIO_PORT_DATA);
		*val++ = पढ़ोl(priv->regs + reg + UNIPHIER_GPIO_PORT_सूची);
	पूर्ण

	*val++ = पढ़ोl(priv->regs + UNIPHIER_GPIO_IRQ_EN);
	*val++ = पढ़ोl(priv->regs + UNIPHIER_GPIO_IRQ_MODE);
	*val++ = पढ़ोl(priv->regs + UNIPHIER_GPIO_IRQ_FLT_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा uniphier_gpio_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक nbanks = uniphier_gpio_get_nbanks(priv->chip.ngpio);
	स्थिर u32 *val = priv->saved_vals;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i;

	क्रम (i = 0; i < nbanks; i++) अणु
		reg = uniphier_gpio_bank_to_reg(i);

		ग_लिखोl(*val++, priv->regs + reg + UNIPHIER_GPIO_PORT_DATA);
		ग_लिखोl(*val++, priv->regs + reg + UNIPHIER_GPIO_PORT_सूची);
	पूर्ण

	ग_लिखोl(*val++, priv->regs + UNIPHIER_GPIO_IRQ_EN);
	ग_लिखोl(*val++, priv->regs + UNIPHIER_GPIO_IRQ_MODE);
	ग_लिखोl(*val++, priv->regs + UNIPHIER_GPIO_IRQ_FLT_EN);

	uniphier_gpio_hw_init(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uniphier_gpio_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(uniphier_gpio_suspend,
				     uniphier_gpio_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_gpio_match[] = अणु
	अणु .compatible = "socionext,uniphier-gpio" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_gpio_match);

अटल काष्ठा platक्रमm_driver uniphier_gpio_driver = अणु
	.probe = uniphier_gpio_probe,
	.हटाओ = uniphier_gpio_हटाओ,
	.driver = अणु
		.name = "uniphier-gpio",
		.of_match_table = uniphier_gpio_match,
		.pm = &uniphier_gpio_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_gpio_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier GPIO driver");
MODULE_LICENSE("GPL v2");
