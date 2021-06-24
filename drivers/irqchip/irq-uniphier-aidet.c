<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम UniPhier AIDET (ARM Interrupt Detector)
 *
 * Copyright (C) 2017 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा UNIPHIER_AIDET_NR_IRQS		256

#घोषणा UNIPHIER_AIDET_DETCONF		0x04	/* inverter रेजिस्टर base */

काष्ठा uniphier_aidet_priv अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम __iomem *reg_base;
	spinlock_t lock;
	u32 saved_vals[UNIPHIER_AIDET_NR_IRQS / 32];
पूर्ण;

अटल व्योम uniphier_aidet_reg_update(काष्ठा uniphier_aidet_priv *priv,
				      अचिन्हित पूर्णांक reg, u32 mask, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&priv->lock, flags);
	पंचांगp = पढ़ोl_relaxed(priv->reg_base + reg);
	पंचांगp &= ~mask;
	पंचांगp |= mask & val;
	ग_लिखोl_relaxed(पंचांगp, priv->reg_base + reg);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम uniphier_aidet_detconf_update(काष्ठा uniphier_aidet_priv *priv,
					  अचिन्हित दीर्घ index, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक reg;
	u32 mask;

	reg = UNIPHIER_AIDET_DETCONF + index / 32 * 4;
	mask = BIT(index % 32);

	uniphier_aidet_reg_update(priv, reg, mask, val ? mask : 0);
पूर्ण

अटल पूर्णांक uniphier_aidet_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा uniphier_aidet_priv *priv = data->chip_data;
	अचिन्हित पूर्णांक val;

	/* enable inverter क्रम active low triggers */
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		val = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		val = 1;
		type = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		val = 1;
		type = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	uniphier_aidet_detconf_update(priv, data->hwirq, val);

	वापस irq_chip_set_type_parent(data, type);
पूर्ण

अटल काष्ठा irq_chip uniphier_aidet_irq_chip = अणु
	.name = "AIDET",
	.irq_mask = irq_chip_mask_parent,
	.irq_unmask = irq_chip_unmask_parent,
	.irq_eoi = irq_chip_eoi_parent,
	.irq_set_affinity = irq_chip_set_affinity_parent,
	.irq_set_type = uniphier_aidet_irq_set_type,
पूर्ण;

अटल पूर्णांक uniphier_aidet_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
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

अटल पूर्णांक uniphier_aidet_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				       व्योम *arg)
अणु
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret;

	अगर (nr_irqs != 1)
		वापस -EINVAL;

	ret = uniphier_aidet_करोमुख्य_translate(करोमुख्य, arg, &hwirq, &type);
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

	अगर (hwirq >= UNIPHIER_AIDET_NR_IRQS)
		वापस -ENXIO;

	ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					    &uniphier_aidet_irq_chip,
					    करोमुख्य->host_data);
	अगर (ret)
		वापस ret;

	/* parent is GIC */
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 3;
	parent_fwspec.param[0] = 0;		/* SPI */
	parent_fwspec.param[1] = hwirq;
	parent_fwspec.param[2] = type;

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops uniphier_aidet_करोमुख्य_ops = अणु
	.alloc = uniphier_aidet_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_common,
	.translate = uniphier_aidet_करोमुख्य_translate,
पूर्ण;

अटल पूर्णांक uniphier_aidet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent_np;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा uniphier_aidet_priv *priv;

	parent_np = of_irq_find_parent(dev->of_node);
	अगर (!parent_np)
		वापस -ENXIO;

	parent_करोमुख्य = irq_find_host(parent_np);
	of_node_put(parent_np);
	अगर (!parent_करोमुख्य)
		वापस -EPROBE_DEFER;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->reg_base))
		वापस PTR_ERR(priv->reg_base);

	spin_lock_init(&priv->lock);

	priv->करोमुख्य = irq_करोमुख्य_create_hierarchy(
					parent_करोमुख्य, 0,
					UNIPHIER_AIDET_NR_IRQS,
					of_node_to_fwnode(dev->of_node),
					&uniphier_aidet_करोमुख्य_ops, priv);
	अगर (!priv->करोमुख्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_aidet_suspend(काष्ठा device *dev)
अणु
	काष्ठा uniphier_aidet_priv *priv = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->saved_vals); i++)
		priv->saved_vals[i] = पढ़ोl_relaxed(
			priv->reg_base + UNIPHIER_AIDET_DETCONF + i * 4);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_aidet_resume(काष्ठा device *dev)
अणु
	काष्ठा uniphier_aidet_priv *priv = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->saved_vals); i++)
		ग_लिखोl_relaxed(priv->saved_vals[i],
			       priv->reg_base + UNIPHIER_AIDET_DETCONF + i * 4);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uniphier_aidet_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(uniphier_aidet_suspend,
				      uniphier_aidet_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_aidet_match[] = अणु
	अणु .compatible = "socionext,uniphier-ld4-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-pro4-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-sld8-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-pro5-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-pxs2-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-ld11-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-ld20-aidet" पूर्ण,
	अणु .compatible = "socionext,uniphier-pxs3-aidet" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver uniphier_aidet_driver = अणु
	.probe = uniphier_aidet_probe,
	.driver = अणु
		.name = "uniphier-aidet",
		.of_match_table = uniphier_aidet_match,
		.pm = &uniphier_aidet_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(uniphier_aidet_driver);
