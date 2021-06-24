<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas IRQC Driver
 *
 *  Copyright (C) 2013 Magnus Damm
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा IRQC_IRQ_MAX	32	/* maximum 32 पूर्णांकerrupts per driver instance */

#घोषणा IRQC_REQ_STS	0x00	/* Interrupt Request Status Register */
#घोषणा IRQC_EN_STS	0x04	/* Interrupt Enable Status Register */
#घोषणा IRQC_EN_SET	0x08	/* Interrupt Enable Set Register */
#घोषणा IRQC_INT_CPU_BASE(n) (0x000 + ((n) * 0x10))
				/* SYS-CPU vs. RT-CPU */
#घोषणा DETECT_STATUS	0x100	/* IRQn Detect Status Register */
#घोषणा MONITOR		0x104	/* IRQn Signal Level Monitor Register */
#घोषणा HLVL_STS	0x108	/* IRQn High Level Detect Status Register */
#घोषणा LLVL_STS	0x10c	/* IRQn Low Level Detect Status Register */
#घोषणा S_R_EDGE_STS	0x110	/* IRQn Sync Rising Edge Detect Status Reg. */
#घोषणा S_F_EDGE_STS	0x114	/* IRQn Sync Falling Edge Detect Status Reg. */
#घोषणा A_R_EDGE_STS	0x118	/* IRQn Async Rising Edge Detect Status Reg. */
#घोषणा A_F_EDGE_STS	0x11c	/* IRQn Async Falling Edge Detect Status Reg. */
#घोषणा CHTEN_STS	0x120	/* Chattering Reduction Status Register */
#घोषणा IRQC_CONFIG(n) (0x180 + ((n) * 0x04))
				/* IRQn Configuration Register */

काष्ठा irqc_irq अणु
	पूर्णांक hw_irq;
	पूर्णांक requested_irq;
	काष्ठा irqc_priv *p;
पूर्ण;

काष्ठा irqc_priv अणु
	व्योम __iomem *iomem;
	व्योम __iomem *cpu_पूर्णांक_base;
	काष्ठा irqc_irq irq[IRQC_IRQ_MAX];
	अचिन्हित पूर्णांक number_of_irqs;
	काष्ठा device *dev;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	atomic_t wakeup_path;
पूर्ण;

अटल काष्ठा irqc_priv *irq_data_to_priv(काष्ठा irq_data *data)
अणु
	वापस data->करोमुख्य->host_data;
पूर्ण

अटल व्योम irqc_dbg(काष्ठा irqc_irq *i, अक्षर *str)
अणु
	dev_dbg(i->p->dev, "%s (%d:%d)\n", str, i->requested_irq, i->hw_irq);
पूर्ण

अटल अचिन्हित अक्षर irqc_sense[IRQ_TYPE_SENSE_MASK + 1] = अणु
	[IRQ_TYPE_LEVEL_LOW]	= 0x01,
	[IRQ_TYPE_LEVEL_HIGH]	= 0x02,
	[IRQ_TYPE_EDGE_FALLING]	= 0x04,	/* Synchronous */
	[IRQ_TYPE_EDGE_RISING]	= 0x08,	/* Synchronous */
	[IRQ_TYPE_EDGE_BOTH]	= 0x0c,	/* Synchronous */
पूर्ण;

अटल पूर्णांक irqc_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irqc_priv *p = irq_data_to_priv(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);
	अचिन्हित अक्षर value = irqc_sense[type & IRQ_TYPE_SENSE_MASK];
	u32 पंचांगp;

	irqc_dbg(&p->irq[hw_irq], "sense");

	अगर (!value)
		वापस -EINVAL;

	पंचांगp = ioपढ़ो32(p->iomem + IRQC_CONFIG(hw_irq));
	पंचांगp &= ~0x3f;
	पंचांगp |= value;
	ioग_लिखो32(पंचांगp, p->iomem + IRQC_CONFIG(hw_irq));
	वापस 0;
पूर्ण

अटल पूर्णांक irqc_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा irqc_priv *p = irq_data_to_priv(d);
	पूर्णांक hw_irq = irqd_to_hwirq(d);

	irq_set_irq_wake(p->irq[hw_irq].requested_irq, on);
	अगर (on)
		atomic_inc(&p->wakeup_path);
	अन्यथा
		atomic_dec(&p->wakeup_path);

	वापस 0;
पूर्ण

अटल irqवापस_t irqc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irqc_irq *i = dev_id;
	काष्ठा irqc_priv *p = i->p;
	u32 bit = BIT(i->hw_irq);

	irqc_dbg(i, "demux1");

	अगर (ioपढ़ो32(p->iomem + DETECT_STATUS) & bit) अणु
		ioग_लिखो32(bit, p->iomem + DETECT_STATUS);
		irqc_dbg(i, "demux2");
		generic_handle_irq(irq_find_mapping(p->irq_करोमुख्य, i->hw_irq));
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक irqc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *name = dev_name(dev);
	काष्ठा irqc_priv *p;
	काष्ठा resource *irq;
	पूर्णांक ret;
	पूर्णांक k;

	p = devm_kzalloc(dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->dev = dev;
	platक्रमm_set_drvdata(pdev, p);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	/* allow any number of IRQs between 1 and IRQC_IRQ_MAX */
	क्रम (k = 0; k < IRQC_IRQ_MAX; k++) अणु
		irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, k);
		अगर (!irq)
			अवरोध;

		p->irq[k].p = p;
		p->irq[k].hw_irq = k;
		p->irq[k].requested_irq = irq->start;
	पूर्ण

	p->number_of_irqs = k;
	अगर (p->number_of_irqs < 1) अणु
		dev_err(dev, "not enough IRQ resources\n");
		ret = -EINVAL;
		जाओ err_runसमय_pm_disable;
	पूर्ण

	/* ioremap IOMEM and setup पढ़ो/ग_लिखो callbacks */
	p->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->iomem)) अणु
		ret = PTR_ERR(p->iomem);
		जाओ err_runसमय_pm_disable;
	पूर्ण

	p->cpu_पूर्णांक_base = p->iomem + IRQC_INT_CPU_BASE(0); /* SYS-SPI */

	p->irq_करोमुख्य = irq_करोमुख्य_add_linear(dev->of_node, p->number_of_irqs,
					      &irq_generic_chip_ops, p);
	अगर (!p->irq_करोमुख्य) अणु
		ret = -ENXIO;
		dev_err(dev, "cannot initialize irq domain\n");
		जाओ err_runसमय_pm_disable;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(p->irq_करोमुख्य, p->number_of_irqs,
					     1, "irqc", handle_level_irq,
					     0, 0, IRQ_GC_INIT_NESTED_LOCK);
	अगर (ret) अणु
		dev_err(dev, "cannot allocate generic chip\n");
		जाओ err_हटाओ_करोमुख्य;
	पूर्ण

	p->gc = irq_get_करोमुख्य_generic_chip(p->irq_करोमुख्य, 0);
	p->gc->reg_base = p->cpu_पूर्णांक_base;
	p->gc->chip_types[0].regs.enable = IRQC_EN_SET;
	p->gc->chip_types[0].regs.disable = IRQC_EN_STS;
	p->gc->chip_types[0].chip.parent_device = dev;
	p->gc->chip_types[0].chip.irq_mask = irq_gc_mask_disable_reg;
	p->gc->chip_types[0].chip.irq_unmask = irq_gc_unmask_enable_reg;
	p->gc->chip_types[0].chip.irq_set_type	= irqc_irq_set_type;
	p->gc->chip_types[0].chip.irq_set_wake	= irqc_irq_set_wake;
	p->gc->chip_types[0].chip.flags	= IRQCHIP_MASK_ON_SUSPEND;

	/* request पूर्णांकerrupts one by one */
	क्रम (k = 0; k < p->number_of_irqs; k++) अणु
		अगर (devm_request_irq(dev, p->irq[k].requested_irq,
				     irqc_irq_handler, 0, name, &p->irq[k])) अणु
			dev_err(dev, "failed to request IRQ\n");
			ret = -ENOENT;
			जाओ err_हटाओ_करोमुख्य;
		पूर्ण
	पूर्ण

	dev_info(dev, "driving %d irqs\n", p->number_of_irqs);

	वापस 0;

err_हटाओ_करोमुख्य:
	irq_करोमुख्य_हटाओ(p->irq_करोमुख्य);
err_runसमय_pm_disable:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक irqc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irqc_priv *p = platक्रमm_get_drvdata(pdev);

	irq_करोमुख्य_हटाओ(p->irq_करोमुख्य);
	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused irqc_suspend(काष्ठा device *dev)
अणु
	काष्ठा irqc_priv *p = dev_get_drvdata(dev);

	अगर (atomic_पढ़ो(&p->wakeup_path))
		device_set_wakeup_path(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(irqc_pm_ops, irqc_suspend, शून्य);

अटल स्थिर काष्ठा of_device_id irqc_dt_ids[] = अणु
	अणु .compatible = "renesas,irqc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, irqc_dt_ids);

अटल काष्ठा platक्रमm_driver irqc_device_driver = अणु
	.probe		= irqc_probe,
	.हटाओ		= irqc_हटाओ,
	.driver		= अणु
		.name	= "renesas_irqc",
		.of_match_table	= irqc_dt_ids,
		.pm	= &irqc_pm_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init irqc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&irqc_device_driver);
पूर्ण
postcore_initcall(irqc_init);

अटल व्योम __निकास irqc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&irqc_device_driver);
पूर्ण
module_निकास(irqc_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Renesas IRQC Driver");
MODULE_LICENSE("GPL v2");
