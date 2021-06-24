<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// MXC GPIO support. (c) 2008 Daniel Mack <daniel@caiaq.de>
// Copyright 2008 Juergen Beisert, kernel@pengutronix.de
//
// Based on code from Freescale Semiconductor,
// Authors: Daniel Mack, Juergen Beisert.
// Copyright (C) 2004-2010 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/bug.h>

/* device type dependent stuff */
काष्ठा mxc_gpio_hwdata अणु
	अचिन्हित dr_reg;
	अचिन्हित gdir_reg;
	अचिन्हित psr_reg;
	अचिन्हित icr1_reg;
	अचिन्हित icr2_reg;
	अचिन्हित imr_reg;
	अचिन्हित isr_reg;
	पूर्णांक edge_sel_reg;
	अचिन्हित low_level;
	अचिन्हित high_level;
	अचिन्हित rise_edge;
	अचिन्हित fall_edge;
पूर्ण;

काष्ठा mxc_gpio_reg_saved अणु
	u32 icr1;
	u32 icr2;
	u32 imr;
	u32 gdir;
	u32 edge_sel;
	u32 dr;
पूर्ण;

काष्ठा mxc_gpio_port अणु
	काष्ठा list_head node;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	पूर्णांक irq;
	पूर्णांक irq_high;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा gpio_chip gc;
	काष्ठा device *dev;
	u32 both_edges;
	काष्ठा mxc_gpio_reg_saved gpio_saved_reg;
	bool घातer_off;
	स्थिर काष्ठा mxc_gpio_hwdata *hwdata;
पूर्ण;

अटल काष्ठा mxc_gpio_hwdata imx1_imx21_gpio_hwdata = अणु
	.dr_reg		= 0x1c,
	.gdir_reg	= 0x00,
	.psr_reg	= 0x24,
	.icr1_reg	= 0x28,
	.icr2_reg	= 0x2c,
	.imr_reg	= 0x30,
	.isr_reg	= 0x34,
	.edge_sel_reg	= -EINVAL,
	.low_level	= 0x03,
	.high_level	= 0x02,
	.rise_edge	= 0x00,
	.fall_edge	= 0x01,
पूर्ण;

अटल काष्ठा mxc_gpio_hwdata imx31_gpio_hwdata = अणु
	.dr_reg		= 0x00,
	.gdir_reg	= 0x04,
	.psr_reg	= 0x08,
	.icr1_reg	= 0x0c,
	.icr2_reg	= 0x10,
	.imr_reg	= 0x14,
	.isr_reg	= 0x18,
	.edge_sel_reg	= -EINVAL,
	.low_level	= 0x00,
	.high_level	= 0x01,
	.rise_edge	= 0x02,
	.fall_edge	= 0x03,
पूर्ण;

अटल काष्ठा mxc_gpio_hwdata imx35_gpio_hwdata = अणु
	.dr_reg		= 0x00,
	.gdir_reg	= 0x04,
	.psr_reg	= 0x08,
	.icr1_reg	= 0x0c,
	.icr2_reg	= 0x10,
	.imr_reg	= 0x14,
	.isr_reg	= 0x18,
	.edge_sel_reg	= 0x1c,
	.low_level	= 0x00,
	.high_level	= 0x01,
	.rise_edge	= 0x02,
	.fall_edge	= 0x03,
पूर्ण;

#घोषणा GPIO_DR			(port->hwdata->dr_reg)
#घोषणा GPIO_Gसूची		(port->hwdata->gdir_reg)
#घोषणा GPIO_PSR		(port->hwdata->psr_reg)
#घोषणा GPIO_ICR1		(port->hwdata->icr1_reg)
#घोषणा GPIO_ICR2		(port->hwdata->icr2_reg)
#घोषणा GPIO_IMR		(port->hwdata->imr_reg)
#घोषणा GPIO_ISR		(port->hwdata->isr_reg)
#घोषणा GPIO_EDGE_SEL		(port->hwdata->edge_sel_reg)

#घोषणा GPIO_INT_LOW_LEV	(port->hwdata->low_level)
#घोषणा GPIO_INT_HIGH_LEV	(port->hwdata->high_level)
#घोषणा GPIO_INT_RISE_EDGE	(port->hwdata->rise_edge)
#घोषणा GPIO_INT_FALL_EDGE	(port->hwdata->fall_edge)
#घोषणा GPIO_INT_BOTH_EDGES	0x4

अटल स्थिर काष्ठा of_device_id mxc_gpio_dt_ids[] = अणु
	अणु .compatible = "fsl,imx1-gpio", .data =  &imx1_imx21_gpio_hwdata पूर्ण,
	अणु .compatible = "fsl,imx21-gpio", .data = &imx1_imx21_gpio_hwdata पूर्ण,
	अणु .compatible = "fsl,imx31-gpio", .data = &imx31_gpio_hwdata पूर्ण,
	अणु .compatible = "fsl,imx35-gpio", .data = &imx35_gpio_hwdata पूर्ण,
	अणु .compatible = "fsl,imx7d-gpio", .data = &imx35_gpio_hwdata पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxc_gpio_dt_ids);

/*
 * MX2 has one पूर्णांकerrupt *क्रम all* gpio ports. The list is used
 * to save the references to all ports, so that mx2_gpio_irq_handler
 * can walk through all पूर्णांकerrupt status रेजिस्टरs.
 */
अटल LIST_HEAD(mxc_gpio_ports);

/* Note: This driver assumes 32 GPIOs are handled in one रेजिस्टर */

अटल पूर्णांक gpio_set_irq_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mxc_gpio_port *port = gc->निजी;
	u32 bit, val;
	u32 gpio_idx = d->hwirq;
	पूर्णांक edge;
	व्योम __iomem *reg = port->base;

	port->both_edges &= ~(1 << gpio_idx);
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		edge = GPIO_INT_RISE_EDGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		edge = GPIO_INT_FALL_EDGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		अगर (GPIO_EDGE_SEL >= 0) अणु
			edge = GPIO_INT_BOTH_EDGES;
		पूर्ण अन्यथा अणु
			val = port->gc.get(&port->gc, gpio_idx);
			अगर (val) अणु
				edge = GPIO_INT_LOW_LEV;
				pr_debug("mxc: set GPIO %d to low trigger\n", gpio_idx);
			पूर्ण अन्यथा अणु
				edge = GPIO_INT_HIGH_LEV;
				pr_debug("mxc: set GPIO %d to high trigger\n", gpio_idx);
			पूर्ण
			port->both_edges |= 1 << gpio_idx;
		पूर्ण
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		edge = GPIO_INT_LOW_LEV;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		edge = GPIO_INT_HIGH_LEV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (GPIO_EDGE_SEL >= 0) अणु
		val = पढ़ोl(port->base + GPIO_EDGE_SEL);
		अगर (edge == GPIO_INT_BOTH_EDGES)
			ग_लिखोl(val | (1 << gpio_idx),
				port->base + GPIO_EDGE_SEL);
		अन्यथा
			ग_लिखोl(val & ~(1 << gpio_idx),
				port->base + GPIO_EDGE_SEL);
	पूर्ण

	अगर (edge != GPIO_INT_BOTH_EDGES) अणु
		reg += GPIO_ICR1 + ((gpio_idx & 0x10) >> 2); /* lower or upper रेजिस्टर */
		bit = gpio_idx & 0xf;
		val = पढ़ोl(reg) & ~(0x3 << (bit << 1));
		ग_लिखोl(val | (edge << (bit << 1)), reg);
	पूर्ण

	ग_लिखोl(1 << gpio_idx, port->base + GPIO_ISR);

	वापस 0;
पूर्ण

अटल व्योम mxc_flip_edge(काष्ठा mxc_gpio_port *port, u32 gpio)
अणु
	व्योम __iomem *reg = port->base;
	u32 bit, val;
	पूर्णांक edge;

	reg += GPIO_ICR1 + ((gpio & 0x10) >> 2); /* lower or upper रेजिस्टर */
	bit = gpio & 0xf;
	val = पढ़ोl(reg);
	edge = (val >> (bit << 1)) & 3;
	val &= ~(0x3 << (bit << 1));
	अगर (edge == GPIO_INT_HIGH_LEV) अणु
		edge = GPIO_INT_LOW_LEV;
		pr_debug("mxc: switch GPIO %d to low trigger\n", gpio);
	पूर्ण अन्यथा अगर (edge == GPIO_INT_LOW_LEV) अणु
		edge = GPIO_INT_HIGH_LEV;
		pr_debug("mxc: switch GPIO %d to high trigger\n", gpio);
	पूर्ण अन्यथा अणु
		pr_err("mxc: invalid configuration for GPIO %d: %x\n",
		       gpio, edge);
		वापस;
	पूर्ण
	ग_लिखोl(val | (edge << (bit << 1)), reg);
पूर्ण

/* handle 32 पूर्णांकerrupts in one status रेजिस्टर */
अटल व्योम mxc_gpio_irq_handler(काष्ठा mxc_gpio_port *port, u32 irq_stat)
अणु
	जबतक (irq_stat != 0) अणु
		पूर्णांक irqoffset = fls(irq_stat) - 1;

		अगर (port->both_edges & (1 << irqoffset))
			mxc_flip_edge(port, irqoffset);

		generic_handle_irq(irq_find_mapping(port->करोमुख्य, irqoffset));

		irq_stat &= ~(1 << irqoffset);
	पूर्ण
पूर्ण

/* MX1 and MX3 has one पूर्णांकerrupt *per* gpio port */
अटल व्योम mx3_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	u32 irq_stat;
	काष्ठा mxc_gpio_port *port = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);

	irq_stat = पढ़ोl(port->base + GPIO_ISR) & पढ़ोl(port->base + GPIO_IMR);

	mxc_gpio_irq_handler(port, irq_stat);

	chained_irq_निकास(chip, desc);
पूर्ण

/* MX2 has one पूर्णांकerrupt *क्रम all* gpio ports */
अटल व्योम mx2_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	u32 irq_msk, irq_stat;
	काष्ठा mxc_gpio_port *port;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);

	/* walk through all पूर्णांकerrupt status रेजिस्टरs */
	list_क्रम_each_entry(port, &mxc_gpio_ports, node) अणु
		irq_msk = पढ़ोl(port->base + GPIO_IMR);
		अगर (!irq_msk)
			जारी;

		irq_stat = पढ़ोl(port->base + GPIO_ISR) & irq_msk;
		अगर (irq_stat)
			mxc_gpio_irq_handler(port, irq_stat);
	पूर्ण
	chained_irq_निकास(chip, desc);
पूर्ण

/*
 * Set पूर्णांकerrupt number "irq" in the GPIO as a wake-up source.
 * While प्रणाली is running, all रेजिस्टरed GPIO पूर्णांकerrupts need to have
 * wake-up enabled. When प्रणाली is suspended, only selected GPIO पूर्णांकerrupts
 * need to have wake-up enabled.
 * @param  irq          पूर्णांकerrupt source number
 * @param  enable       enable as wake-up अगर equal to non-zero
 * @वापस       This function वापसs 0 on success.
 */
अटल पूर्णांक gpio_set_wake_irq(काष्ठा irq_data *d, u32 enable)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mxc_gpio_port *port = gc->निजी;
	u32 gpio_idx = d->hwirq;
	पूर्णांक ret;

	अगर (enable) अणु
		अगर (port->irq_high && (gpio_idx >= 16))
			ret = enable_irq_wake(port->irq_high);
		अन्यथा
			ret = enable_irq_wake(port->irq);
	पूर्ण अन्यथा अणु
		अगर (port->irq_high && (gpio_idx >= 16))
			ret = disable_irq_wake(port->irq_high);
		अन्यथा
			ret = disable_irq_wake(port->irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxc_gpio_init_gc(काष्ठा mxc_gpio_port *port, पूर्णांक irq_base)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	पूर्णांक rv;

	gc = devm_irq_alloc_generic_chip(port->dev, "gpio-mxc", 1, irq_base,
					 port->base, handle_level_irq);
	अगर (!gc)
		वापस -ENOMEM;
	gc->निजी = port;

	ct = gc->chip_types;
	ct->chip.irq_ack = irq_gc_ack_set_bit;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	ct->chip.irq_set_type = gpio_set_irq_type;
	ct->chip.irq_set_wake = gpio_set_wake_irq;
	ct->chip.flags = IRQCHIP_MASK_ON_SUSPEND;
	ct->regs.ack = GPIO_ISR;
	ct->regs.mask = GPIO_IMR;

	rv = devm_irq_setup_generic_chip(port->dev, gc, IRQ_MSK(32),
					 IRQ_GC_INIT_NESTED_LOCK,
					 IRQ_NOREQUEST, 0);

	वापस rv;
पूर्ण

अटल पूर्णांक mxc_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा mxc_gpio_port *port = gpiochip_get_data(gc);

	वापस irq_find_mapping(port->करोमुख्य, offset);
पूर्ण

अटल पूर्णांक mxc_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mxc_gpio_port *port;
	पूर्णांक irq_count;
	पूर्णांक irq_base;
	पूर्णांक err;

	port = devm_kzalloc(&pdev->dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->dev = &pdev->dev;

	port->hwdata = device_get_match_data(&pdev->dev);

	port->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(port->base))
		वापस PTR_ERR(port->base);

	irq_count = platक्रमm_irq_count(pdev);
	अगर (irq_count < 0)
		वापस irq_count;

	अगर (irq_count > 1) अणु
		port->irq_high = platक्रमm_get_irq(pdev, 1);
		अगर (port->irq_high < 0)
			port->irq_high = 0;
	पूर्ण

	port->irq = platक्रमm_get_irq(pdev, 0);
	अगर (port->irq < 0)
		वापस port->irq;

	/* the controller घड़ी is optional */
	port->clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(port->clk))
		वापस PTR_ERR(port->clk);

	err = clk_prepare_enable(port->clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		वापस err;
	पूर्ण

	अगर (of_device_is_compatible(np, "fsl,imx7d-gpio"))
		port->घातer_off = true;

	/* disable the पूर्णांकerrupt and clear the status */
	ग_लिखोl(0, port->base + GPIO_IMR);
	ग_लिखोl(~0, port->base + GPIO_ISR);

	अगर (of_device_is_compatible(np, "fsl,imx21-gpio")) अणु
		/*
		 * Setup one handler क्रम all GPIO पूर्णांकerrupts. Actually setting
		 * the handler is needed only once, but करोing it क्रम every port
		 * is more robust and easier.
		 */
		irq_set_chained_handler(port->irq, mx2_gpio_irq_handler);
	पूर्ण अन्यथा अणु
		/* setup one handler क्रम each entry */
		irq_set_chained_handler_and_data(port->irq,
						 mx3_gpio_irq_handler, port);
		अगर (port->irq_high > 0)
			/* setup handler क्रम GPIO 16 to 31 */
			irq_set_chained_handler_and_data(port->irq_high,
							 mx3_gpio_irq_handler,
							 port);
	पूर्ण

	err = bgpio_init(&port->gc, &pdev->dev, 4,
			 port->base + GPIO_PSR,
			 port->base + GPIO_DR, शून्य,
			 port->base + GPIO_Gसूची, शून्य,
			 BGPIOF_READ_OUTPUT_REG_SET);
	अगर (err)
		जाओ out_bgio;

	port->gc.request = gpiochip_generic_request;
	port->gc.मुक्त = gpiochip_generic_मुक्त;
	port->gc.to_irq = mxc_gpio_to_irq;
	port->gc.base = (pdev->id < 0) ? of_alias_get_id(np, "gpio") * 32 :
					     pdev->id * 32;

	err = devm_gpiochip_add_data(&pdev->dev, &port->gc, port);
	अगर (err)
		जाओ out_bgio;

	irq_base = devm_irq_alloc_descs(&pdev->dev, -1, 0, 32, numa_node_id());
	अगर (irq_base < 0) अणु
		err = irq_base;
		जाओ out_bgio;
	पूर्ण

	port->करोमुख्य = irq_करोमुख्य_add_legacy(np, 32, irq_base, 0,
					     &irq_करोमुख्य_simple_ops, शून्य);
	अगर (!port->करोमुख्य) अणु
		err = -ENODEV;
		जाओ out_bgio;
	पूर्ण

	/* gpio-mxc can be a generic irq chip */
	err = mxc_gpio_init_gc(port, irq_base);
	अगर (err < 0)
		जाओ out_irqकरोमुख्य_हटाओ;

	list_add_tail(&port->node, &mxc_gpio_ports);

	platक्रमm_set_drvdata(pdev, port);

	वापस 0;

out_irqकरोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(port->करोमुख्य);
out_bgio:
	clk_disable_unprepare(port->clk);
	dev_info(&pdev->dev, "%s failed with errno %d\n", __func__, err);
	वापस err;
पूर्ण

अटल व्योम mxc_gpio_save_regs(काष्ठा mxc_gpio_port *port)
अणु
	अगर (!port->घातer_off)
		वापस;

	port->gpio_saved_reg.icr1 = पढ़ोl(port->base + GPIO_ICR1);
	port->gpio_saved_reg.icr2 = पढ़ोl(port->base + GPIO_ICR2);
	port->gpio_saved_reg.imr = पढ़ोl(port->base + GPIO_IMR);
	port->gpio_saved_reg.gdir = पढ़ोl(port->base + GPIO_Gसूची);
	port->gpio_saved_reg.edge_sel = पढ़ोl(port->base + GPIO_EDGE_SEL);
	port->gpio_saved_reg.dr = पढ़ोl(port->base + GPIO_DR);
पूर्ण

अटल व्योम mxc_gpio_restore_regs(काष्ठा mxc_gpio_port *port)
अणु
	अगर (!port->घातer_off)
		वापस;

	ग_लिखोl(port->gpio_saved_reg.icr1, port->base + GPIO_ICR1);
	ग_लिखोl(port->gpio_saved_reg.icr2, port->base + GPIO_ICR2);
	ग_लिखोl(port->gpio_saved_reg.imr, port->base + GPIO_IMR);
	ग_लिखोl(port->gpio_saved_reg.gdir, port->base + GPIO_Gसूची);
	ग_लिखोl(port->gpio_saved_reg.edge_sel, port->base + GPIO_EDGE_SEL);
	ग_लिखोl(port->gpio_saved_reg.dr, port->base + GPIO_DR);
पूर्ण

अटल पूर्णांक mxc_gpio_syscore_suspend(व्योम)
अणु
	काष्ठा mxc_gpio_port *port;

	/* walk through all ports */
	list_क्रम_each_entry(port, &mxc_gpio_ports, node) अणु
		mxc_gpio_save_regs(port);
		clk_disable_unprepare(port->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mxc_gpio_syscore_resume(व्योम)
अणु
	काष्ठा mxc_gpio_port *port;
	पूर्णांक ret;

	/* walk through all ports */
	list_क्रम_each_entry(port, &mxc_gpio_ports, node) अणु
		ret = clk_prepare_enable(port->clk);
		अगर (ret) अणु
			pr_err("mxc: failed to enable gpio clock %d\n", ret);
			वापस;
		पूर्ण
		mxc_gpio_restore_regs(port);
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops mxc_gpio_syscore_ops = अणु
	.suspend = mxc_gpio_syscore_suspend,
	.resume = mxc_gpio_syscore_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver mxc_gpio_driver = अणु
	.driver		= अणु
		.name	= "gpio-mxc",
		.of_match_table = mxc_gpio_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= mxc_gpio_probe,
पूर्ण;

अटल पूर्णांक __init gpio_mxc_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&mxc_gpio_syscore_ops);

	वापस platक्रमm_driver_रेजिस्टर(&mxc_gpio_driver);
पूर्ण
subsys_initcall(gpio_mxc_init);

MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("i.MX GPIO Driver");
MODULE_LICENSE("GPL");
