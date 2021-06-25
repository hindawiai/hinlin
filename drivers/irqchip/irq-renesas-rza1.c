<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RZ/A1 IRQC Driver
 *
 * Copyright (C) 2019 Glider bvba
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा IRQC_NUM_IRQ		8

#घोषणा ICR0			0	/* Interrupt Control Register 0 */

#घोषणा ICR0_NMIL		BIT(15)	/* NMI Input Level (0=low, 1=high) */
#घोषणा ICR0_NMIE		BIT(8)	/* Edge Select (0=falling, 1=rising) */
#घोषणा ICR0_NMIF		BIT(1)	/* NMI Interrupt Request */

#घोषणा ICR1			2	/* Interrupt Control Register 1 */

#घोषणा ICR1_IRQS(n, sense)	((sense) << ((n) * 2))	/* IRQ Sense Select */
#घोषणा ICR1_IRQS_LEVEL_LOW	0
#घोषणा ICR1_IRQS_EDGE_FALLING	1
#घोषणा ICR1_IRQS_EDGE_RISING	2
#घोषणा ICR1_IRQS_EDGE_BOTH	3
#घोषणा ICR1_IRQS_MASK(n)	ICR1_IRQS((n), 3)

#घोषणा IRQRR			4	/* IRQ Interrupt Request Register */


काष्ठा rza1_irqc_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा irq_chip chip;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा of_phandle_args map[IRQC_NUM_IRQ];
पूर्ण;

अटल काष्ठा rza1_irqc_priv *irq_data_to_priv(काष्ठा irq_data *data)
अणु
	वापस data->करोमुख्य->host_data;
पूर्ण

अटल व्योम rza1_irqc_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा rza1_irqc_priv *priv = irq_data_to_priv(d);
	u16 bit = BIT(irqd_to_hwirq(d));
	u16 पंचांगp;

	पंचांगp = पढ़ोw_relaxed(priv->base + IRQRR);
	अगर (पंचांगp & bit)
		ग_लिखोw_relaxed(GENMASK(IRQC_NUM_IRQ - 1, 0) & ~bit,
			       priv->base + IRQRR);

	irq_chip_eoi_parent(d);
पूर्ण

अटल पूर्णांक rza1_irqc_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा rza1_irqc_priv *priv = irq_data_to_priv(d);
	अचिन्हित पूर्णांक hw_irq = irqd_to_hwirq(d);
	u16 sense, पंचांगp;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		sense = ICR1_IRQS_LEVEL_LOW;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		sense = ICR1_IRQS_EDGE_FALLING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		sense = ICR1_IRQS_EDGE_RISING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		sense = ICR1_IRQS_EDGE_BOTH;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	पंचांगp = पढ़ोw_relaxed(priv->base + ICR1);
	पंचांगp &= ~ICR1_IRQS_MASK(hw_irq);
	पंचांगp |= ICR1_IRQS(hw_irq, sense);
	ग_लिखोw_relaxed(पंचांगp, priv->base + ICR1);
	वापस 0;
पूर्ण

अटल पूर्णांक rza1_irqc_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			   अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा rza1_irqc_priv *priv = करोमुख्य->host_data;
	काष्ठा irq_fwspec *fwspec = arg;
	अचिन्हित पूर्णांक hwirq = fwspec->param[0];
	काष्ठा irq_fwspec spec;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq, &priv->chip,
					    priv);
	अगर (ret)
		वापस ret;

	spec.fwnode = &priv->dev->of_node->fwnode;
	spec.param_count = priv->map[hwirq].args_count;
	क्रम (i = 0; i < spec.param_count; i++)
		spec.param[i] = priv->map[hwirq].args[i];

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, &spec);
पूर्ण

अटल पूर्णांक rza1_irqc_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
			       काष्ठा irq_fwspec *fwspec, अचिन्हित दीर्घ *hwirq,
			       अचिन्हित पूर्णांक *type)
अणु
	अगर (fwspec->param_count != 2 || fwspec->param[0] >= IRQC_NUM_IRQ)
		वापस -EINVAL;

	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops rza1_irqc_करोमुख्य_ops = अणु
	.alloc = rza1_irqc_alloc,
	.translate = rza1_irqc_translate,
पूर्ण;

अटल पूर्णांक rza1_irqc_parse_map(काष्ठा rza1_irqc_priv *priv,
			       काष्ठा device_node *gic_node)
अणु
	अचिन्हित पूर्णांक imaplen, i, j, ret;
	काष्ठा device *dev = priv->dev;
	काष्ठा device_node *ipar;
	स्थिर __be32 *imap;
	u32 पूर्णांकsize;

	imap = of_get_property(dev->of_node, "interrupt-map", &imaplen);
	अगर (!imap)
		वापस -EINVAL;

	क्रम (i = 0; i < IRQC_NUM_IRQ; i++) अणु
		अगर (imaplen < 3)
			वापस -EINVAL;

		/* Check पूर्णांकerrupt number, ignore sense */
		अगर (be32_to_cpup(imap) != i)
			वापस -EINVAL;

		ipar = of_find_node_by_phandle(be32_to_cpup(imap + 2));
		अगर (ipar != gic_node) अणु
			of_node_put(ipar);
			वापस -EINVAL;
		पूर्ण

		imap += 3;
		imaplen -= 3;

		ret = of_property_पढ़ो_u32(ipar, "#interrupt-cells", &पूर्णांकsize);
		of_node_put(ipar);
		अगर (ret)
			वापस ret;

		अगर (imaplen < पूर्णांकsize)
			वापस -EINVAL;

		priv->map[i].args_count = पूर्णांकsize;
		क्रम (j = 0; j < पूर्णांकsize; j++)
			priv->map[i].args[j] = be32_to_cpup(imap++);

		imaplen -= पूर्णांकsize;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rza1_irqc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा irq_करोमुख्य *parent = शून्य;
	काष्ठा device_node *gic_node;
	काष्ठा rza1_irqc_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);
	priv->dev = dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	gic_node = of_irq_find_parent(np);
	अगर (gic_node)
		parent = irq_find_host(gic_node);

	अगर (!parent) अणु
		dev_err(dev, "cannot find parent domain\n");
		ret = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	ret = rza1_irqc_parse_map(priv, gic_node);
	अगर (ret) अणु
		dev_err(dev, "cannot parse %s: %d\n", "interrupt-map", ret);
		जाओ out_put_node;
	पूर्ण

	priv->chip.name = "rza1-irqc",
	priv->chip.irq_mask = irq_chip_mask_parent,
	priv->chip.irq_unmask = irq_chip_unmask_parent,
	priv->chip.irq_eoi = rza1_irqc_eoi,
	priv->chip.irq_retrigger = irq_chip_retrigger_hierarchy,
	priv->chip.irq_set_type = rza1_irqc_set_type,
	priv->chip.flags = IRQCHIP_MASK_ON_SUSPEND | IRQCHIP_SKIP_SET_WAKE;

	priv->irq_करोमुख्य = irq_करोमुख्य_add_hierarchy(parent, 0, IRQC_NUM_IRQ,
						    np, &rza1_irqc_करोमुख्य_ops,
						    priv);
	अगर (!priv->irq_करोमुख्य) अणु
		dev_err(dev, "cannot initialize irq domain\n");
		ret = -ENOMEM;
	पूर्ण

out_put_node:
	of_node_put(gic_node);
	वापस ret;
पूर्ण

अटल पूर्णांक rza1_irqc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rza1_irqc_priv *priv = platक्रमm_get_drvdata(pdev);

	irq_करोमुख्य_हटाओ(priv->irq_करोमुख्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rza1_irqc_dt_ids[] = अणु
	अणु .compatible = "renesas,rza1-irqc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rza1_irqc_dt_ids);

अटल काष्ठा platक्रमm_driver rza1_irqc_device_driver = अणु
	.probe		= rza1_irqc_probe,
	.हटाओ		= rza1_irqc_हटाओ,
	.driver		= अणु
		.name	= "renesas_rza1_irqc",
		.of_match_table	= rza1_irqc_dt_ids,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init rza1_irqc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rza1_irqc_device_driver);
पूर्ण
postcore_initcall(rza1_irqc_init);

अटल व्योम __निकास rza1_irqc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rza1_irqc_device_driver);
पूर्ण
module_निकास(rza1_irqc_निकास);

MODULE_AUTHOR("Geert Uytterhoeven <geert+renesas@glider.be>");
MODULE_DESCRIPTION("Renesas RZ/A1 IRQC Driver");
MODULE_LICENSE("GPL v2");
