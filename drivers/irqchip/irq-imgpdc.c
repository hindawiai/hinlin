<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IMG PowerDown Controller (PDC)
 *
 * Copyright 2010-2013 Imagination Technologies Ltd.
 *
 * Exposes the syswake and PDC peripheral wake पूर्णांकerrupts to the प्रणाली.
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

/* PDC पूर्णांकerrupt रेजिस्टर numbers */

#घोषणा PDC_IRQ_STATUS			0x310
#घोषणा PDC_IRQ_ENABLE			0x314
#घोषणा PDC_IRQ_CLEAR			0x318
#घोषणा PDC_IRQ_ROUTE			0x31c
#घोषणा PDC_SYS_WAKE_BASE		0x330
#घोषणा PDC_SYS_WAKE_STRIDE		0x8
#घोषणा PDC_SYS_WAKE_CONFIG_BASE	0x334
#घोषणा PDC_SYS_WAKE_CONFIG_STRIDE	0x8

/* PDC पूर्णांकerrupt रेजिस्टर field masks */

#घोषणा PDC_IRQ_SYS3			0x08
#घोषणा PDC_IRQ_SYS2			0x04
#घोषणा PDC_IRQ_SYS1			0x02
#घोषणा PDC_IRQ_SYS0			0x01
#घोषणा PDC_IRQ_ROUTE_WU_EN_SYS3	0x08000000
#घोषणा PDC_IRQ_ROUTE_WU_EN_SYS2	0x04000000
#घोषणा PDC_IRQ_ROUTE_WU_EN_SYS1	0x02000000
#घोषणा PDC_IRQ_ROUTE_WU_EN_SYS0	0x01000000
#घोषणा PDC_IRQ_ROUTE_WU_EN_WD		0x00040000
#घोषणा PDC_IRQ_ROUTE_WU_EN_IR		0x00020000
#घोषणा PDC_IRQ_ROUTE_WU_EN_RTC		0x00010000
#घोषणा PDC_IRQ_ROUTE_EXT_EN_SYS3	0x00000800
#घोषणा PDC_IRQ_ROUTE_EXT_EN_SYS2	0x00000400
#घोषणा PDC_IRQ_ROUTE_EXT_EN_SYS1	0x00000200
#घोषणा PDC_IRQ_ROUTE_EXT_EN_SYS0	0x00000100
#घोषणा PDC_IRQ_ROUTE_EXT_EN_WD		0x00000004
#घोषणा PDC_IRQ_ROUTE_EXT_EN_IR		0x00000002
#घोषणा PDC_IRQ_ROUTE_EXT_EN_RTC	0x00000001
#घोषणा PDC_SYS_WAKE_RESET		0x00000010
#घोषणा PDC_SYS_WAKE_INT_MODE		0x0000000e
#घोषणा PDC_SYS_WAKE_INT_MODE_SHIFT	1
#घोषणा PDC_SYS_WAKE_PIN_VAL		0x00000001

/* PDC पूर्णांकerrupt स्थिरants */

#घोषणा PDC_SYS_WAKE_INT_LOW		0x0
#घोषणा PDC_SYS_WAKE_INT_HIGH		0x1
#घोषणा PDC_SYS_WAKE_INT_DOWN		0x2
#घोषणा PDC_SYS_WAKE_INT_UP		0x3
#घोषणा PDC_SYS_WAKE_INT_CHANGE		0x6
#घोषणा PDC_SYS_WAKE_INT_NONE		0x4

/**
 * काष्ठा pdc_पूर्णांकc_priv - निजी pdc पूर्णांकerrupt data.
 * @nr_perips:		Number of peripheral पूर्णांकerrupt संकेतs.
 * @nr_syswakes:	Number of syswake संकेतs.
 * @perip_irqs:		List of peripheral IRQ numbers handled.
 * @syswake_irq:	Shared PDC syswake IRQ number.
 * @करोमुख्य:		IRQ करोमुख्य क्रम PDC peripheral and syswake IRQs.
 * @pdc_base:		Base of PDC रेजिस्टरs.
 * @irq_route:		Cached version of PDC_IRQ_ROUTE रेजिस्टर.
 * @lock:		Lock to protect the PDC syswake रेजिस्टरs and the cached
 *			values of those रेजिस्टरs in this काष्ठा.
 */
काष्ठा pdc_पूर्णांकc_priv अणु
	अचिन्हित पूर्णांक		nr_perips;
	अचिन्हित पूर्णांक		nr_syswakes;
	अचिन्हित पूर्णांक		*perip_irqs;
	अचिन्हित पूर्णांक		syswake_irq;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	व्योम __iomem		*pdc_base;

	u32			irq_route;
	raw_spinlock_t		lock;
पूर्ण;

अटल व्योम pdc_ग_लिखो(काष्ठा pdc_पूर्णांकc_priv *priv, अचिन्हित पूर्णांक reg_offs,
		      अचिन्हित पूर्णांक data)
अणु
	ioग_लिखो32(data, priv->pdc_base + reg_offs);
पूर्ण

अटल अचिन्हित पूर्णांक pdc_पढ़ो(काष्ठा pdc_पूर्णांकc_priv *priv,
			     अचिन्हित पूर्णांक reg_offs)
अणु
	वापस ioपढ़ो32(priv->pdc_base + reg_offs);
पूर्ण

/* Generic IRQ callbacks */

#घोषणा SYS0_HWIRQ	8

अटल अचिन्हित पूर्णांक hwirq_is_syswake(irq_hw_number_t hw)
अणु
	वापस hw >= SYS0_HWIRQ;
पूर्ण

अटल अचिन्हित पूर्णांक hwirq_to_syswake(irq_hw_number_t hw)
अणु
	वापस hw - SYS0_HWIRQ;
पूर्ण

अटल irq_hw_number_t syswake_to_hwirq(अचिन्हित पूर्णांक syswake)
अणु
	वापस SYS0_HWIRQ + syswake;
पूर्ण

अटल काष्ठा pdc_पूर्णांकc_priv *irqd_to_priv(काष्ठा irq_data *data)
अणु
	वापस (काष्ठा pdc_पूर्णांकc_priv *)data->करोमुख्य->host_data;
पूर्ण

/*
 * perip_irq_mask() and perip_irq_unmask() use IRQ_ROUTE which also contains
 * wake bits, thereक्रमe we cannot use the generic irqchip mask callbacks as they
 * cache the mask.
 */

अटल व्योम perip_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv = irqd_to_priv(data);

	raw_spin_lock(&priv->lock);
	priv->irq_route &= ~data->mask;
	pdc_ग_लिखो(priv, PDC_IRQ_ROUTE, priv->irq_route);
	raw_spin_unlock(&priv->lock);
पूर्ण

अटल व्योम perip_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv = irqd_to_priv(data);

	raw_spin_lock(&priv->lock);
	priv->irq_route |= data->mask;
	pdc_ग_लिखो(priv, PDC_IRQ_ROUTE, priv->irq_route);
	raw_spin_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक syswake_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv = irqd_to_priv(data);
	अचिन्हित पूर्णांक syswake = hwirq_to_syswake(data->hwirq);
	अचिन्हित पूर्णांक irq_mode;
	अचिन्हित पूर्णांक soc_sys_wake_regoff, soc_sys_wake;

	/* translate to syswake IRQ mode */
	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_mode = PDC_SYS_WAKE_INT_CHANGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		irq_mode = PDC_SYS_WAKE_INT_UP;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_mode = PDC_SYS_WAKE_INT_DOWN;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_mode = PDC_SYS_WAKE_INT_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_mode = PDC_SYS_WAKE_INT_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock(&priv->lock);

	/* set the IRQ mode */
	soc_sys_wake_regoff = PDC_SYS_WAKE_BASE + syswake*PDC_SYS_WAKE_STRIDE;
	soc_sys_wake = pdc_पढ़ो(priv, soc_sys_wake_regoff);
	soc_sys_wake &= ~PDC_SYS_WAKE_INT_MODE;
	soc_sys_wake |= irq_mode << PDC_SYS_WAKE_INT_MODE_SHIFT;
	pdc_ग_लिखो(priv, soc_sys_wake_regoff, soc_sys_wake);

	/* and update the handler */
	irq_setup_alt_chip(data, flow_type);

	raw_spin_unlock(&priv->lock);

	वापस 0;
पूर्ण

/* applies to both peripheral and syswake पूर्णांकerrupts */
अटल पूर्णांक pdc_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv = irqd_to_priv(data);
	irq_hw_number_t hw = data->hwirq;
	अचिन्हित पूर्णांक mask = (1 << 16) << hw;
	अचिन्हित पूर्णांक dst_irq;

	raw_spin_lock(&priv->lock);
	अगर (on)
		priv->irq_route |= mask;
	अन्यथा
		priv->irq_route &= ~mask;
	pdc_ग_लिखो(priv, PDC_IRQ_ROUTE, priv->irq_route);
	raw_spin_unlock(&priv->lock);

	/* control the destination IRQ wakeup too क्रम standby mode */
	अगर (hwirq_is_syswake(hw))
		dst_irq = priv->syswake_irq;
	अन्यथा
		dst_irq = priv->perip_irqs[hw];
	irq_set_irq_wake(dst_irq, on);

	वापस 0;
पूर्ण

अटल व्योम pdc_पूर्णांकc_perip_isr(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा pdc_पूर्णांकc_priv *priv;
	अचिन्हित पूर्णांक i, irq_no;

	priv = (काष्ठा pdc_पूर्णांकc_priv *)irq_desc_get_handler_data(desc);

	/* find the peripheral number */
	क्रम (i = 0; i < priv->nr_perips; ++i)
		अगर (irq == priv->perip_irqs[i])
			जाओ found;

	/* should never get here */
	वापस;
found:

	/* pass on the पूर्णांकerrupt */
	irq_no = irq_linear_revmap(priv->करोमुख्य, i);
	generic_handle_irq(irq_no);
पूर्ण

अटल व्योम pdc_पूर्णांकc_syswake_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv;
	अचिन्हित पूर्णांक syswake, irq_no;
	अचिन्हित पूर्णांक status;

	priv = (काष्ठा pdc_पूर्णांकc_priv *)irq_desc_get_handler_data(desc);

	status = pdc_पढ़ो(priv, PDC_IRQ_STATUS) &
		 pdc_पढ़ो(priv, PDC_IRQ_ENABLE);
	status &= (1 << priv->nr_syswakes) - 1;

	क्रम (syswake = 0; status; status >>= 1, ++syswake) अणु
		/* Has this sys_wake triggered? */
		अगर (!(status & 1))
			जारी;

		irq_no = irq_linear_revmap(priv->करोमुख्य,
					   syswake_to_hwirq(syswake));
		generic_handle_irq(irq_no);
	पूर्ण
पूर्ण

अटल व्योम pdc_पूर्णांकc_setup(काष्ठा pdc_पूर्णांकc_priv *priv)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक soc_sys_wake_regoff;
	अचिन्हित पूर्णांक soc_sys_wake;

	/*
	 * Mask all syswake पूर्णांकerrupts beक्रमe routing, or we could receive an
	 * पूर्णांकerrupt beक्रमe we're पढ़ोy to handle it.
	 */
	pdc_ग_लिखो(priv, PDC_IRQ_ENABLE, 0);

	/*
	 * Enable routing of all syswakes
	 * Disable all wake sources
	 */
	priv->irq_route = ((PDC_IRQ_ROUTE_EXT_EN_SYS0 << priv->nr_syswakes) -
				PDC_IRQ_ROUTE_EXT_EN_SYS0);
	pdc_ग_लिखो(priv, PDC_IRQ_ROUTE, priv->irq_route);

	/* Initialise syswake IRQ */
	क्रम (i = 0; i < priv->nr_syswakes; ++i) अणु
		/* set the IRQ mode to none */
		soc_sys_wake_regoff = PDC_SYS_WAKE_BASE + i*PDC_SYS_WAKE_STRIDE;
		soc_sys_wake = PDC_SYS_WAKE_INT_NONE
				<< PDC_SYS_WAKE_INT_MODE_SHIFT;
		pdc_ग_लिखो(priv, soc_sys_wake_regoff, soc_sys_wake);
	पूर्ण
पूर्ण

अटल पूर्णांक pdc_पूर्णांकc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा resource *res_regs;
	काष्ठा irq_chip_generic *gc;
	अचिन्हित पूर्णांक i;
	पूर्णांक irq, ret;
	u32 val;

	अगर (!node)
		वापस -ENOENT;

	/* Get रेजिस्टरs */
	res_regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res_regs == शून्य) अणु
		dev_err(&pdev->dev, "cannot find registers resource\n");
		वापस -ENOENT;
	पूर्ण

	/* Allocate driver data */
	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&pdev->dev, "cannot allocate device data\n");
		वापस -ENOMEM;
	पूर्ण
	raw_spin_lock_init(&priv->lock);
	platक्रमm_set_drvdata(pdev, priv);

	/* Ioremap the रेजिस्टरs */
	priv->pdc_base = devm_ioremap(&pdev->dev, res_regs->start,
				      resource_size(res_regs));
	अगर (!priv->pdc_base)
		वापस -EIO;

	/* Get number of peripherals */
	ret = of_property_पढ़ो_u32(node, "num-perips", &val);
	अगर (ret) अणु
		dev_err(&pdev->dev, "No num-perips node property found\n");
		वापस -EINVAL;
	पूर्ण
	अगर (val > SYS0_HWIRQ) अणु
		dev_err(&pdev->dev, "num-perips (%u) out of range\n", val);
		वापस -EINVAL;
	पूर्ण
	priv->nr_perips = val;

	/* Get number of syswakes */
	ret = of_property_पढ़ो_u32(node, "num-syswakes", &val);
	अगर (ret) अणु
		dev_err(&pdev->dev, "No num-syswakes node property found\n");
		वापस -EINVAL;
	पूर्ण
	अगर (val > SYS0_HWIRQ) अणु
		dev_err(&pdev->dev, "num-syswakes (%u) out of range\n", val);
		वापस -EINVAL;
	पूर्ण
	priv->nr_syswakes = val;

	/* Get peripheral IRQ numbers */
	priv->perip_irqs = devm_kसुस्मृति(&pdev->dev, 4, priv->nr_perips,
					GFP_KERNEL);
	अगर (!priv->perip_irqs) अणु
		dev_err(&pdev->dev, "cannot allocate perip IRQ list\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < priv->nr_perips; ++i) अणु
		irq = platक्रमm_get_irq(pdev, 1 + i);
		अगर (irq < 0)
			वापस irq;
		priv->perip_irqs[i] = irq;
	पूर्ण
	/* check अगर too many were provided */
	अगर (platक्रमm_get_irq(pdev, 1 + i) >= 0) अणु
		dev_err(&pdev->dev, "surplus perip IRQs detected\n");
		वापस -EINVAL;
	पूर्ण

	/* Get syswake IRQ number */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	priv->syswake_irq = irq;

	/* Set up an IRQ करोमुख्य */
	priv->करोमुख्य = irq_करोमुख्य_add_linear(node, 16, &irq_generic_chip_ops,
					     priv);
	अगर (unlikely(!priv->करोमुख्य)) अणु
		dev_err(&pdev->dev, "cannot add IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Set up 2 generic irq chips with 2 chip types.
	 * The first one क्रम peripheral irqs (only 1 chip type used)
	 * The second one क्रम syswake irqs (edge and level chip types)
	 */
	ret = irq_alloc_करोमुख्य_generic_chips(priv->करोमुख्य, 8, 2, "pdc",
					     handle_level_irq, 0, 0,
					     IRQ_GC_INIT_NESTED_LOCK);
	अगर (ret)
		जाओ err_generic;

	/* peripheral पूर्णांकerrupt chip */

	gc = irq_get_करोमुख्य_generic_chip(priv->करोमुख्य, 0);
	gc->unused	= ~(BIT(priv->nr_perips) - 1);
	gc->reg_base	= priv->pdc_base;
	/*
	 * IRQ_ROUTE contains wake bits, so we can't use the generic versions as
	 * they cache the mask
	 */
	gc->chip_types[0].regs.mask		= PDC_IRQ_ROUTE;
	gc->chip_types[0].chip.irq_mask		= perip_irq_mask;
	gc->chip_types[0].chip.irq_unmask	= perip_irq_unmask;
	gc->chip_types[0].chip.irq_set_wake	= pdc_irq_set_wake;

	/* syswake पूर्णांकerrupt chip */

	gc = irq_get_करोमुख्य_generic_chip(priv->करोमुख्य, 8);
	gc->unused	= ~(BIT(priv->nr_syswakes) - 1);
	gc->reg_base	= priv->pdc_base;

	/* edge पूर्णांकerrupts */
	gc->chip_types[0].type			= IRQ_TYPE_EDGE_BOTH;
	gc->chip_types[0].handler		= handle_edge_irq;
	gc->chip_types[0].regs.ack		= PDC_IRQ_CLEAR;
	gc->chip_types[0].regs.mask		= PDC_IRQ_ENABLE;
	gc->chip_types[0].chip.irq_ack		= irq_gc_ack_set_bit;
	gc->chip_types[0].chip.irq_mask		= irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask	= irq_gc_mask_set_bit;
	gc->chip_types[0].chip.irq_set_type	= syswake_irq_set_type;
	gc->chip_types[0].chip.irq_set_wake	= pdc_irq_set_wake;
	/* क्रम standby we pass on to the shared syswake IRQ */
	gc->chip_types[0].chip.flags		= IRQCHIP_MASK_ON_SUSPEND;

	/* level पूर्णांकerrupts */
	gc->chip_types[1].type			= IRQ_TYPE_LEVEL_MASK;
	gc->chip_types[1].handler		= handle_level_irq;
	gc->chip_types[1].regs.ack		= PDC_IRQ_CLEAR;
	gc->chip_types[1].regs.mask		= PDC_IRQ_ENABLE;
	gc->chip_types[1].chip.irq_ack		= irq_gc_ack_set_bit;
	gc->chip_types[1].chip.irq_mask		= irq_gc_mask_clr_bit;
	gc->chip_types[1].chip.irq_unmask	= irq_gc_mask_set_bit;
	gc->chip_types[1].chip.irq_set_type	= syswake_irq_set_type;
	gc->chip_types[1].chip.irq_set_wake	= pdc_irq_set_wake;
	/* क्रम standby we pass on to the shared syswake IRQ */
	gc->chip_types[1].chip.flags		= IRQCHIP_MASK_ON_SUSPEND;

	/* Set up the hardware to enable पूर्णांकerrupt routing */
	pdc_पूर्णांकc_setup(priv);

	/* Setup chained handlers क्रम the peripheral IRQs */
	क्रम (i = 0; i < priv->nr_perips; ++i) अणु
		irq = priv->perip_irqs[i];
		irq_set_chained_handler_and_data(irq, pdc_पूर्णांकc_perip_isr,
						 priv);
	पूर्ण

	/* Setup chained handler क्रम the syswake IRQ */
	irq_set_chained_handler_and_data(priv->syswake_irq,
					 pdc_पूर्णांकc_syswake_isr, priv);

	dev_info(&pdev->dev,
		 "PDC IRQ controller initialised (%u perip IRQs, %u syswake IRQs)\n",
		 priv->nr_perips,
		 priv->nr_syswakes);

	वापस 0;
err_generic:
	irq_करोमुख्य_हटाओ(priv->करोमुख्य);
	वापस ret;
पूर्ण

अटल पूर्णांक pdc_पूर्णांकc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pdc_पूर्णांकc_priv *priv = platक्रमm_get_drvdata(pdev);

	irq_करोमुख्य_हटाओ(priv->करोमुख्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pdc_पूर्णांकc_match[] = अणु
	अणु .compatible = "img,pdc-intc" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver pdc_पूर्णांकc_driver = अणु
	.driver = अणु
		.name		= "pdc-intc",
		.of_match_table	= pdc_पूर्णांकc_match,
	पूर्ण,
	.probe = pdc_पूर्णांकc_probe,
	.हटाओ = pdc_पूर्णांकc_हटाओ,
पूर्ण;

अटल पूर्णांक __init pdc_पूर्णांकc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pdc_पूर्णांकc_driver);
पूर्ण
core_initcall(pdc_पूर्णांकc_init);
