<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale vf610 GPIO support through PORT and GPIO
 *
 * Copyright (c) 2014 Toradex AG.
 *
 * Author: Stefan Agner <stefan@agner.ch>.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>

#घोषणा VF610_GPIO_PER_PORT		32

काष्ठा fsl_gpio_soc_data अणु
	/* SoCs has a Port Data Direction Register (PDDR) */
	bool have_paddr;
पूर्ण;

काष्ठा vf610_gpio_port अणु
	काष्ठा gpio_chip gc;
	काष्ठा irq_chip ic;
	व्योम __iomem *base;
	व्योम __iomem *gpio_base;
	स्थिर काष्ठा fsl_gpio_soc_data *sdata;
	u8 irqc[VF610_GPIO_PER_PORT];
	काष्ठा clk *clk_port;
	काष्ठा clk *clk_gpio;
	पूर्णांक irq;
पूर्ण;

#घोषणा GPIO_PDOR		0x00
#घोषणा GPIO_PSOR		0x04
#घोषणा GPIO_PCOR		0x08
#घोषणा GPIO_PTOR		0x0c
#घोषणा GPIO_Pसूची		0x10
#घोषणा GPIO_PDDR		0x14

#घोषणा PORT_PCR(n)		((n) * 0x4)
#घोषणा PORT_PCR_IRQC_OFFSET	16

#घोषणा PORT_ISFR		0xa0
#घोषणा PORT_DFER		0xc0
#घोषणा PORT_DFCR		0xc4
#घोषणा PORT_DFWR		0xc8

#घोषणा PORT_INT_OFF		0x0
#घोषणा PORT_INT_LOGIC_ZERO	0x8
#घोषणा PORT_INT_RISING_EDGE	0x9
#घोषणा PORT_INT_FALLING_EDGE	0xa
#घोषणा PORT_INT_EITHER_EDGE	0xb
#घोषणा PORT_INT_LOGIC_ONE	0xc

अटल स्थिर काष्ठा fsl_gpio_soc_data imx_data = अणु
	.have_paddr = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vf610_gpio_dt_ids[] = अणु
	अणु .compatible = "fsl,vf610-gpio",	.data = शून्य, पूर्ण,
	अणु .compatible = "fsl,imx7ulp-gpio",	.data = &imx_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल अंतरभूत व्योम vf610_gpio_ग_लिखोl(u32 val, व्योम __iomem *reg)
अणु
	ग_लिखोl_relaxed(val, reg);
पूर्ण

अटल अंतरभूत u32 vf610_gpio_पढ़ोl(व्योम __iomem *reg)
अणु
	वापस पढ़ोl_relaxed(reg);
पूर्ण

अटल पूर्णांक vf610_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा vf610_gpio_port *port = gpiochip_get_data(gc);
	अचिन्हित दीर्घ mask = BIT(gpio);
	अचिन्हित दीर्घ offset = GPIO_Pसूची;

	अगर (port->sdata && port->sdata->have_paddr) अणु
		mask &= vf610_gpio_पढ़ोl(port->gpio_base + GPIO_PDDR);
		अगर (mask)
			offset = GPIO_PDOR;
	पूर्ण

	वापस !!(vf610_gpio_पढ़ोl(port->gpio_base + offset) & BIT(gpio));
पूर्ण

अटल व्योम vf610_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा vf610_gpio_port *port = gpiochip_get_data(gc);
	अचिन्हित दीर्घ mask = BIT(gpio);
	अचिन्हित दीर्घ offset = val ? GPIO_PSOR : GPIO_PCOR;

	vf610_gpio_ग_लिखोl(mask, port->gpio_base + offset);
पूर्ण

अटल पूर्णांक vf610_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा vf610_gpio_port *port = gpiochip_get_data(chip);
	अचिन्हित दीर्घ mask = BIT(gpio);
	u32 val;

	अगर (port->sdata && port->sdata->have_paddr) अणु
		val = vf610_gpio_पढ़ोl(port->gpio_base + GPIO_PDDR);
		val &= ~mask;
		vf610_gpio_ग_लिखोl(val, port->gpio_base + GPIO_PDDR);
	पूर्ण

	वापस pinctrl_gpio_direction_input(chip->base + gpio);
पूर्ण

अटल पूर्णांक vf610_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित gpio,
				       पूर्णांक value)
अणु
	काष्ठा vf610_gpio_port *port = gpiochip_get_data(chip);
	अचिन्हित दीर्घ mask = BIT(gpio);

	अगर (port->sdata && port->sdata->have_paddr)
		vf610_gpio_ग_लिखोl(mask, port->gpio_base + GPIO_PDDR);

	vf610_gpio_set(chip, gpio, value);

	वापस pinctrl_gpio_direction_output(chip->base + gpio);
पूर्ण

अटल व्योम vf610_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा vf610_gpio_port *port =
		gpiochip_get_data(irq_desc_get_handler_data(desc));
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक pin;
	अचिन्हित दीर्घ irq_isfr;

	chained_irq_enter(chip, desc);

	irq_isfr = vf610_gpio_पढ़ोl(port->base + PORT_ISFR);

	क्रम_each_set_bit(pin, &irq_isfr, VF610_GPIO_PER_PORT) अणु
		vf610_gpio_ग_लिखोl(BIT(pin), port->base + PORT_ISFR);

		generic_handle_irq(irq_find_mapping(port->gc.irq.करोमुख्य, pin));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम vf610_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा vf610_gpio_port *port =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	पूर्णांक gpio = d->hwirq;

	vf610_gpio_ग_लिखोl(BIT(gpio), port->base + PORT_ISFR);
पूर्ण

अटल पूर्णांक vf610_gpio_irq_set_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा vf610_gpio_port *port =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	u8 irqc;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		irqc = PORT_INT_RISING_EDGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irqc = PORT_INT_FALLING_EDGE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		irqc = PORT_INT_EITHER_EDGE;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irqc = PORT_INT_LOGIC_ZERO;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irqc = PORT_INT_LOGIC_ONE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	port->irqc[d->hwirq] = irqc;

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_edge_irq);

	वापस 0;
पूर्ण

अटल व्योम vf610_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा vf610_gpio_port *port =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	व्योम __iomem *pcr_base = port->base + PORT_PCR(d->hwirq);

	vf610_gpio_ग_लिखोl(0, pcr_base);
पूर्ण

अटल व्योम vf610_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा vf610_gpio_port *port =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	व्योम __iomem *pcr_base = port->base + PORT_PCR(d->hwirq);

	vf610_gpio_ग_लिखोl(port->irqc[d->hwirq] << PORT_PCR_IRQC_OFFSET,
			  pcr_base);
पूर्ण

अटल पूर्णांक vf610_gpio_irq_set_wake(काष्ठा irq_data *d, u32 enable)
अणु
	काष्ठा vf610_gpio_port *port =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));

	अगर (enable)
		enable_irq_wake(port->irq);
	अन्यथा
		disable_irq_wake(port->irq);

	वापस 0;
पूर्ण

अटल व्योम vf610_gpio_disable_clk(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक vf610_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा vf610_gpio_port *port;
	काष्ठा gpio_chip *gc;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा irq_chip *ic;
	पूर्णांक i;
	पूर्णांक ret;

	port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->sdata = of_device_get_match_data(dev);
	port->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(port->base))
		वापस PTR_ERR(port->base);

	port->gpio_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(port->gpio_base))
		वापस PTR_ERR(port->gpio_base);

	port->irq = platक्रमm_get_irq(pdev, 0);
	अगर (port->irq < 0)
		वापस port->irq;

	port->clk_port = devm_clk_get(dev, "port");
	ret = PTR_ERR_OR_ZERO(port->clk_port);
	अगर (!ret) अणु
		ret = clk_prepare_enable(port->clk_port);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, vf610_gpio_disable_clk,
					       port->clk_port);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (ret == -EPROBE_DEFER) अणु
		/*
		 * Percolate deferrals, क्रम anything अन्यथा,
		 * just live without the घड़ीing.
		 */
		वापस ret;
	पूर्ण

	port->clk_gpio = devm_clk_get(dev, "gpio");
	ret = PTR_ERR_OR_ZERO(port->clk_gpio);
	अगर (!ret) अणु
		ret = clk_prepare_enable(port->clk_gpio);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, vf610_gpio_disable_clk,
					       port->clk_gpio);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (ret == -EPROBE_DEFER) अणु
		वापस ret;
	पूर्ण

	gc = &port->gc;
	gc->of_node = np;
	gc->parent = dev;
	gc->label = "vf610-gpio";
	gc->ngpio = VF610_GPIO_PER_PORT;
	gc->base = of_alias_get_id(np, "gpio") * VF610_GPIO_PER_PORT;

	gc->request = gpiochip_generic_request;
	gc->मुक्त = gpiochip_generic_मुक्त;
	gc->direction_input = vf610_gpio_direction_input;
	gc->get = vf610_gpio_get;
	gc->direction_output = vf610_gpio_direction_output;
	gc->set = vf610_gpio_set;

	ic = &port->ic;
	ic->name = "gpio-vf610";
	ic->irq_ack = vf610_gpio_irq_ack;
	ic->irq_mask = vf610_gpio_irq_mask;
	ic->irq_unmask = vf610_gpio_irq_unmask;
	ic->irq_set_type = vf610_gpio_irq_set_type;
	ic->irq_set_wake = vf610_gpio_irq_set_wake;

	/* Mask all GPIO पूर्णांकerrupts */
	क्रम (i = 0; i < gc->ngpio; i++)
		vf610_gpio_ग_लिखोl(0, port->base + PORT_PCR(i));

	/* Clear the पूर्णांकerrupt status रेजिस्टर क्रम all GPIO's */
	vf610_gpio_ग_लिखोl(~0, port->base + PORT_ISFR);

	girq = &gc->irq;
	girq->chip = ic;
	girq->parent_handler = vf610_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
				     माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->parents[0] = port->irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;

	वापस devm_gpiochip_add_data(dev, gc, port);
पूर्ण

अटल काष्ठा platक्रमm_driver vf610_gpio_driver = अणु
	.driver		= अणु
		.name	= "gpio-vf610",
		.of_match_table = vf610_gpio_dt_ids,
	पूर्ण,
	.probe		= vf610_gpio_probe,
पूर्ण;

builtin_platक्रमm_driver(vf610_gpio_driver);
