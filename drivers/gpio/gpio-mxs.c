<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// MXC GPIO support. (c) 2008 Daniel Mack <daniel@caiaq.de>
// Copyright 2008 Juergen Beisert, kernel@pengutronix.de
//
// Based on code from Freescale,
// Copyright (C) 2004-2010 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>

#घोषणा MXS_SET		0x4
#घोषणा MXS_CLR		0x8

#घोषणा PINCTRL_DOUT(p)		((is_imx23_gpio(p) ? 0x0500 : 0x0700) + (p->id) * 0x10)
#घोषणा PINCTRL_DIN(p)		((is_imx23_gpio(p) ? 0x0600 : 0x0900) + (p->id) * 0x10)
#घोषणा PINCTRL_DOE(p)		((is_imx23_gpio(p) ? 0x0700 : 0x0b00) + (p->id) * 0x10)
#घोषणा PINCTRL_PIN2IRQ(p)	((is_imx23_gpio(p) ? 0x0800 : 0x1000) + (p->id) * 0x10)
#घोषणा PINCTRL_IRQEN(p)	((is_imx23_gpio(p) ? 0x0900 : 0x1100) + (p->id) * 0x10)
#घोषणा PINCTRL_IRQLEV(p)	((is_imx23_gpio(p) ? 0x0a00 : 0x1200) + (p->id) * 0x10)
#घोषणा PINCTRL_IRQPOL(p)	((is_imx23_gpio(p) ? 0x0b00 : 0x1300) + (p->id) * 0x10)
#घोषणा PINCTRL_IRQSTAT(p)	((is_imx23_gpio(p) ? 0x0c00 : 0x1400) + (p->id) * 0x10)

#घोषणा GPIO_INT_FALL_EDGE	0x0
#घोषणा GPIO_INT_LOW_LEV	0x1
#घोषणा GPIO_INT_RISE_EDGE	0x2
#घोषणा GPIO_INT_HIGH_LEV	0x3
#घोषणा GPIO_INT_LEV_MASK	(1 << 0)
#घोषणा GPIO_INT_POL_MASK	(1 << 1)

क्रमागत mxs_gpio_id अणु
	IMX23_GPIO,
	IMX28_GPIO,
पूर्ण;

काष्ठा mxs_gpio_port अणु
	व्योम __iomem *base;
	पूर्णांक id;
	पूर्णांक irq;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा gpio_chip gc;
	काष्ठा device *dev;
	क्रमागत mxs_gpio_id devid;
	u32 both_edges;
पूर्ण;

अटल अंतरभूत पूर्णांक is_imx23_gpio(काष्ठा mxs_gpio_port *port)
अणु
	वापस port->devid == IMX23_GPIO;
पूर्ण

/* Note: This driver assumes 32 GPIOs are handled in one रेजिस्टर */

अटल पूर्णांक mxs_gpio_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	u32 val;
	u32 pin_mask = 1 << d->hwirq;
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा mxs_gpio_port *port = gc->निजी;
	व्योम __iomem *pin_addr;
	पूर्णांक edge;

	अगर (!(ct->type & type))
		अगर (irq_setup_alt_chip(d, type))
			वापस -EINVAL;

	port->both_edges &= ~pin_mask;
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		val = पढ़ोl(port->base + PINCTRL_DIN(port)) & pin_mask;
		अगर (val)
			edge = GPIO_INT_FALL_EDGE;
		अन्यथा
			edge = GPIO_INT_RISE_EDGE;
		port->both_edges |= pin_mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		edge = GPIO_INT_RISE_EDGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		edge = GPIO_INT_FALL_EDGE;
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

	/* set level or edge */
	pin_addr = port->base + PINCTRL_IRQLEV(port);
	अगर (edge & GPIO_INT_LEV_MASK) अणु
		ग_लिखोl(pin_mask, pin_addr + MXS_SET);
		ग_लिखोl(pin_mask, port->base + PINCTRL_IRQEN(port) + MXS_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(pin_mask, pin_addr + MXS_CLR);
		ग_लिखोl(pin_mask, port->base + PINCTRL_PIN2IRQ(port) + MXS_SET);
	पूर्ण

	/* set polarity */
	pin_addr = port->base + PINCTRL_IRQPOL(port);
	अगर (edge & GPIO_INT_POL_MASK)
		ग_लिखोl(pin_mask, pin_addr + MXS_SET);
	अन्यथा
		ग_लिखोl(pin_mask, pin_addr + MXS_CLR);

	ग_लिखोl(pin_mask, port->base + PINCTRL_IRQSTAT(port) + MXS_CLR);

	वापस 0;
पूर्ण

अटल व्योम mxs_flip_edge(काष्ठा mxs_gpio_port *port, u32 gpio)
अणु
	u32 bit, val, edge;
	व्योम __iomem *pin_addr;

	bit = 1 << gpio;

	pin_addr = port->base + PINCTRL_IRQPOL(port);
	val = पढ़ोl(pin_addr);
	edge = val & bit;

	अगर (edge)
		ग_लिखोl(bit, pin_addr + MXS_CLR);
	अन्यथा
		ग_लिखोl(bit, pin_addr + MXS_SET);
पूर्ण

/* MXS has one पूर्णांकerrupt *per* gpio port */
अटल व्योम mxs_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	u32 irq_stat;
	काष्ठा mxs_gpio_port *port = irq_desc_get_handler_data(desc);

	desc->irq_data.chip->irq_ack(&desc->irq_data);

	irq_stat = पढ़ोl(port->base + PINCTRL_IRQSTAT(port)) &
			पढ़ोl(port->base + PINCTRL_IRQEN(port));

	जबतक (irq_stat != 0) अणु
		पूर्णांक irqoffset = fls(irq_stat) - 1;
		अगर (port->both_edges & (1 << irqoffset))
			mxs_flip_edge(port, irqoffset);

		generic_handle_irq(irq_find_mapping(port->करोमुख्य, irqoffset));
		irq_stat &= ~(1 << irqoffset);
	पूर्ण
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
अटल पूर्णांक mxs_gpio_set_wake_irq(काष्ठा irq_data *d, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mxs_gpio_port *port = gc->निजी;

	अगर (enable)
		enable_irq_wake(port->irq);
	अन्यथा
		disable_irq_wake(port->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_gpio_init_gc(काष्ठा mxs_gpio_port *port, पूर्णांक irq_base)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	पूर्णांक rv;

	gc = devm_irq_alloc_generic_chip(port->dev, "gpio-mxs", 2, irq_base,
					 port->base, handle_level_irq);
	अगर (!gc)
		वापस -ENOMEM;

	gc->निजी = port;

	ct = &gc->chip_types[0];
	ct->type = IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW;
	ct->chip.irq_ack = irq_gc_ack_set_bit;
	ct->chip.irq_mask = irq_gc_mask_disable_reg;
	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->chip.irq_set_type = mxs_gpio_set_irq_type;
	ct->chip.irq_set_wake = mxs_gpio_set_wake_irq;
	ct->chip.flags = IRQCHIP_SET_TYPE_MASKED;
	ct->regs.ack = PINCTRL_IRQSTAT(port) + MXS_CLR;
	ct->regs.enable = PINCTRL_PIN2IRQ(port) + MXS_SET;
	ct->regs.disable = PINCTRL_PIN2IRQ(port) + MXS_CLR;

	ct = &gc->chip_types[1];
	ct->type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	ct->chip.irq_ack = irq_gc_ack_set_bit;
	ct->chip.irq_mask = irq_gc_mask_disable_reg;
	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->chip.irq_set_type = mxs_gpio_set_irq_type;
	ct->chip.irq_set_wake = mxs_gpio_set_wake_irq;
	ct->chip.flags = IRQCHIP_SET_TYPE_MASKED;
	ct->regs.ack = PINCTRL_IRQSTAT(port) + MXS_CLR;
	ct->regs.enable = PINCTRL_IRQEN(port) + MXS_SET;
	ct->regs.disable = PINCTRL_IRQEN(port) + MXS_CLR;
	ct->handler = handle_level_irq;

	rv = devm_irq_setup_generic_chip(port->dev, gc, IRQ_MSK(32),
					 IRQ_GC_INIT_NESTED_LOCK,
					 IRQ_NOREQUEST, 0);

	वापस rv;
पूर्ण

अटल पूर्णांक mxs_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा mxs_gpio_port *port = gpiochip_get_data(gc);

	वापस irq_find_mapping(port->करोमुख्य, offset);
पूर्ण

अटल पूर्णांक mxs_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा mxs_gpio_port *port = gpiochip_get_data(gc);
	u32 mask = 1 << offset;
	u32 dir;

	dir = पढ़ोl(port->base + PINCTRL_DOE(port));
	अगर (dir & mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxs_gpio_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-gpio", .data = (व्योम *) IMX23_GPIO, पूर्ण,
	अणु .compatible = "fsl,imx28-gpio", .data = (व्योम *) IMX28_GPIO, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_gpio_dt_ids);

अटल पूर्णांक mxs_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *parent;
	अटल व्योम __iomem *base;
	काष्ठा mxs_gpio_port *port;
	पूर्णांक irq_base;
	पूर्णांक err;

	port = devm_kzalloc(&pdev->dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->id = of_alias_get_id(np, "gpio");
	अगर (port->id < 0)
		वापस port->id;
	port->devid = (क्रमागत mxs_gpio_id)of_device_get_match_data(&pdev->dev);
	port->dev = &pdev->dev;
	port->irq = platक्रमm_get_irq(pdev, 0);
	अगर (port->irq < 0)
		वापस port->irq;

	/*
	 * map memory region only once, as all the gpio ports
	 * share the same one
	 */
	अगर (!base) अणु
		parent = of_get_parent(np);
		base = of_iomap(parent, 0);
		of_node_put(parent);
		अगर (!base)
			वापस -EADDRNOTAVAIL;
	पूर्ण
	port->base = base;

	/* initially disable the पूर्णांकerrupts */
	ग_लिखोl(0, port->base + PINCTRL_PIN2IRQ(port));
	ग_लिखोl(0, port->base + PINCTRL_IRQEN(port));

	/* clear address has to be used to clear IRQSTAT bits */
	ग_लिखोl(~0U, port->base + PINCTRL_IRQSTAT(port) + MXS_CLR);

	irq_base = devm_irq_alloc_descs(&pdev->dev, -1, 0, 32, numa_node_id());
	अगर (irq_base < 0) अणु
		err = irq_base;
		जाओ out_iounmap;
	पूर्ण

	port->करोमुख्य = irq_करोमुख्य_add_legacy(np, 32, irq_base, 0,
					     &irq_करोमुख्य_simple_ops, शून्य);
	अगर (!port->करोमुख्य) अणु
		err = -ENODEV;
		जाओ out_iounmap;
	पूर्ण

	/* gpio-mxs can be a generic irq chip */
	err = mxs_gpio_init_gc(port, irq_base);
	अगर (err < 0)
		जाओ out_irqकरोमुख्य_हटाओ;

	/* setup one handler क्रम each entry */
	irq_set_chained_handler_and_data(port->irq, mxs_gpio_irq_handler,
					 port);

	err = bgpio_init(&port->gc, &pdev->dev, 4,
			 port->base + PINCTRL_DIN(port),
			 port->base + PINCTRL_DOUT(port) + MXS_SET,
			 port->base + PINCTRL_DOUT(port) + MXS_CLR,
			 port->base + PINCTRL_DOE(port), शून्य, 0);
	अगर (err)
		जाओ out_irqकरोमुख्य_हटाओ;

	port->gc.to_irq = mxs_gpio_to_irq;
	port->gc.get_direction = mxs_gpio_get_direction;
	port->gc.base = port->id * 32;

	err = gpiochip_add_data(&port->gc, port);
	अगर (err)
		जाओ out_irqकरोमुख्य_हटाओ;

	वापस 0;

out_irqकरोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(port->करोमुख्य);
out_iounmap:
	iounmap(port->base);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_gpio_driver = अणु
	.driver		= अणु
		.name	= "gpio-mxs",
		.of_match_table = mxs_gpio_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= mxs_gpio_probe,
पूर्ण;

अटल पूर्णांक __init mxs_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mxs_gpio_driver);
पूर्ण
postcore_initcall(mxs_gpio_init);

MODULE_AUTHOR("Freescale Semiconductor, "
	      "Daniel Mack <danielncaiaq.de>, "
	      "Juergen Beisert <kernel@pengutronix.de>");
MODULE_DESCRIPTION("Freescale MXS GPIO");
MODULE_LICENSE("GPL");
