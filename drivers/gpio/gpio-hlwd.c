<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (C) 2008-2009 The GameCube Linux Team
// Copyright (C) 2008,2009 Albert Herranz
// Copyright (C) 2017-2018 Jonathan Neuschथअfer
//
// Nपूर्णांकenकरो Wii (Hollywood) GPIO driver

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

/*
 * Register names and offsets courtesy of WiiBrew:
 * https://wiibrew.org/wiki/Hardware/Hollywood_GPIOs
 *
 * Note that क्रम most रेजिस्टरs, there are two versions:
 * - HW_GPIOB_* Is always accessible by the Broadway PowerPC core, but करोes
 *   always give access to all GPIO lines
 * - HW_GPIO_* Is only accessible by the Broadway PowerPC code अगर the memory
 *   firewall (AHBPROT) in the Hollywood chipset has been configured to allow
 *   such access.
 *
 * The ownership of each GPIO line can be configured in the HW_GPIO_OWNER
 * रेजिस्टर: A one bit configures the line क्रम access via the HW_GPIOB_*
 * रेजिस्टरs, a zero bit indicates access via HW_GPIO_*. This driver uses
 * HW_GPIOB_*.
 */
#घोषणा HW_GPIOB_OUT		0x00
#घोषणा HW_GPIOB_सूची		0x04
#घोषणा HW_GPIOB_IN		0x08
#घोषणा HW_GPIOB_INTLVL		0x0c
#घोषणा HW_GPIOB_INTFLAG	0x10
#घोषणा HW_GPIOB_INTMASK	0x14
#घोषणा HW_GPIOB_INMIR		0x18
#घोषणा HW_GPIO_ENABLE		0x1c
#घोषणा HW_GPIO_OUT		0x20
#घोषणा HW_GPIO_सूची		0x24
#घोषणा HW_GPIO_IN		0x28
#घोषणा HW_GPIO_INTLVL		0x2c
#घोषणा HW_GPIO_INTFLAG		0x30
#घोषणा HW_GPIO_INTMASK		0x34
#घोषणा HW_GPIO_INMIR		0x38
#घोषणा HW_GPIO_OWNER		0x3c

काष्ठा hlwd_gpio अणु
	काष्ठा gpio_chip gpioc;
	काष्ठा irq_chip irqc;
	व्योम __iomem *regs;
	पूर्णांक irq;
	u32 edge_emulation;
	u32 rising_edge, falling_edge;
पूर्ण;

अटल व्योम hlwd_gpio_irqhandler(काष्ठा irq_desc *desc)
अणु
	काष्ठा hlwd_gpio *hlwd =
		gpiochip_get_data(irq_desc_get_handler_data(desc));
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pending;
	पूर्णांक hwirq;
	u32 emulated_pending;

	spin_lock_irqsave(&hlwd->gpioc.bgpio_lock, flags);
	pending = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTFLAG);
	pending &= ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTMASK);

	/* Treat पूर्णांकerrupts due to edge trigger emulation separately */
	emulated_pending = hlwd->edge_emulation & pending;
	pending &= ~emulated_pending;
	अगर (emulated_pending) अणु
		u32 level, rising, falling;

		level = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTLVL);
		rising = level & emulated_pending;
		falling = ~level & emulated_pending;

		/* Invert the levels */
		ioग_लिखो32be(level ^ emulated_pending,
			    hlwd->regs + HW_GPIOB_INTLVL);

		/* Ack all emulated-edge पूर्णांकerrupts */
		ioग_लिखो32be(emulated_pending, hlwd->regs + HW_GPIOB_INTFLAG);

		/* Signal पूर्णांकerrupts only on the correct edge */
		rising &= hlwd->rising_edge;
		falling &= hlwd->falling_edge;

		/* Mark emulated पूर्णांकerrupts as pending */
		pending |= rising | falling;
	पूर्ण
	spin_unlock_irqrestore(&hlwd->gpioc.bgpio_lock, flags);

	chained_irq_enter(chip, desc);

	क्रम_each_set_bit(hwirq, &pending, 32) अणु
		पूर्णांक irq = irq_find_mapping(hlwd->gpioc.irq.करोमुख्य, hwirq);

		generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम hlwd_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा hlwd_gpio *hlwd =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	ioग_लिखो32be(BIT(data->hwirq), hlwd->regs + HW_GPIOB_INTFLAG);
पूर्ण

अटल व्योम hlwd_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा hlwd_gpio *hlwd =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));
	अचिन्हित दीर्घ flags;
	u32 mask;

	spin_lock_irqsave(&hlwd->gpioc.bgpio_lock, flags);
	mask = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTMASK);
	mask &= ~BIT(data->hwirq);
	ioग_लिखो32be(mask, hlwd->regs + HW_GPIOB_INTMASK);
	spin_unlock_irqrestore(&hlwd->gpioc.bgpio_lock, flags);
पूर्ण

अटल व्योम hlwd_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा hlwd_gpio *hlwd =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));
	अचिन्हित दीर्घ flags;
	u32 mask;

	spin_lock_irqsave(&hlwd->gpioc.bgpio_lock, flags);
	mask = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTMASK);
	mask |= BIT(data->hwirq);
	ioग_लिखो32be(mask, hlwd->regs + HW_GPIOB_INTMASK);
	spin_unlock_irqrestore(&hlwd->gpioc.bgpio_lock, flags);
पूर्ण

अटल व्योम hlwd_gpio_irq_enable(काष्ठा irq_data *data)
अणु
	hlwd_gpio_irq_ack(data);
	hlwd_gpio_irq_unmask(data);
पूर्ण

अटल व्योम hlwd_gpio_irq_setup_emulation(काष्ठा hlwd_gpio *hlwd, पूर्णांक hwirq,
					  अचिन्हित पूर्णांक flow_type)
अणु
	u32 level, state;

	/* Set the trigger level to the inactive level */
	level = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTLVL);
	state = ioपढ़ो32be(hlwd->regs + HW_GPIOB_IN) & BIT(hwirq);
	level &= ~BIT(hwirq);
	level |= state ^ BIT(hwirq);
	ioग_लिखो32be(level, hlwd->regs + HW_GPIOB_INTLVL);

	hlwd->edge_emulation |= BIT(hwirq);
	hlwd->rising_edge &= ~BIT(hwirq);
	hlwd->falling_edge &= ~BIT(hwirq);
	अगर (flow_type & IRQ_TYPE_EDGE_RISING)
		hlwd->rising_edge |= BIT(hwirq);
	अगर (flow_type & IRQ_TYPE_EDGE_FALLING)
		hlwd->falling_edge |= BIT(hwirq);
पूर्ण

अटल पूर्णांक hlwd_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा hlwd_gpio *hlwd =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));
	अचिन्हित दीर्घ flags;
	u32 level;

	spin_lock_irqsave(&hlwd->gpioc.bgpio_lock, flags);

	hlwd->edge_emulation &= ~BIT(data->hwirq);

	चयन (flow_type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		level = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTLVL);
		level |= BIT(data->hwirq);
		ioग_लिखो32be(level, hlwd->regs + HW_GPIOB_INTLVL);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		level = ioपढ़ो32be(hlwd->regs + HW_GPIOB_INTLVL);
		level &= ~BIT(data->hwirq);
		ioग_लिखो32be(level, hlwd->regs + HW_GPIOB_INTLVL);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		hlwd_gpio_irq_setup_emulation(hlwd, data->hwirq, flow_type);
		अवरोध;
	शेष:
		spin_unlock_irqrestore(&hlwd->gpioc.bgpio_lock, flags);
		वापस -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&hlwd->gpioc.bgpio_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक hlwd_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hlwd_gpio *hlwd;
	u32 ngpios;
	पूर्णांक res;

	hlwd = devm_kzalloc(&pdev->dev, माप(*hlwd), GFP_KERNEL);
	अगर (!hlwd)
		वापस -ENOMEM;

	hlwd->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hlwd->regs))
		वापस PTR_ERR(hlwd->regs);

	/*
	 * Claim all GPIOs using the OWNER रेजिस्टर. This will not work on
	 * प्रणालीs where the AHBPROT memory firewall hasn't been configured to
	 * permit PPC access to HW_GPIO_*.
	 *
	 * Note that this has to happen beक्रमe bgpio_init पढ़ोs the
	 * HW_GPIOB_OUT and HW_GPIOB_सूची, because otherwise it पढ़ोs the wrong
	 * values.
	 */
	ioग_लिखो32be(0xffffffff, hlwd->regs + HW_GPIO_OWNER);

	res = bgpio_init(&hlwd->gpioc, &pdev->dev, 4,
			hlwd->regs + HW_GPIOB_IN, hlwd->regs + HW_GPIOB_OUT,
			शून्य, hlwd->regs + HW_GPIOB_सूची, शून्य,
			BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	अगर (res < 0) अणु
		dev_warn(&pdev->dev, "bgpio_init failed: %d\n", res);
		वापस res;
	पूर्ण

	res = of_property_पढ़ो_u32(pdev->dev.of_node, "ngpios", &ngpios);
	अगर (res)
		ngpios = 32;
	hlwd->gpioc.ngpio = ngpios;

	/* Mask and ack all पूर्णांकerrupts */
	ioग_लिखो32be(0, hlwd->regs + HW_GPIOB_INTMASK);
	ioग_लिखो32be(0xffffffff, hlwd->regs + HW_GPIOB_INTFLAG);

	/*
	 * If this GPIO controller is not marked as an पूर्णांकerrupt controller in
	 * the DT, skip पूर्णांकerrupt support.
	 */
	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "interrupt-controller")) अणु
		काष्ठा gpio_irq_chip *girq;

		hlwd->irq = platक्रमm_get_irq(pdev, 0);
		अगर (hlwd->irq < 0) अणु
			dev_info(&pdev->dev, "platform_get_irq returned %d\n",
				 hlwd->irq);
			वापस hlwd->irq;
		पूर्ण

		hlwd->irqc.name = dev_name(&pdev->dev);
		hlwd->irqc.irq_mask = hlwd_gpio_irq_mask;
		hlwd->irqc.irq_unmask = hlwd_gpio_irq_unmask;
		hlwd->irqc.irq_enable = hlwd_gpio_irq_enable;
		hlwd->irqc.irq_set_type = hlwd_gpio_irq_set_type;

		girq = &hlwd->gpioc.irq;
		girq->chip = &hlwd->irqc;
		girq->parent_handler = hlwd_gpio_irqhandler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = hlwd->irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
	पूर्ण

	वापस devm_gpiochip_add_data(&pdev->dev, &hlwd->gpioc, hlwd);
पूर्ण

अटल स्थिर काष्ठा of_device_id hlwd_gpio_match[] = अणु
	अणु .compatible = "nintendo,hollywood-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hlwd_gpio_match);

अटल काष्ठा platक्रमm_driver hlwd_gpio_driver = अणु
	.driver	= अणु
		.name		= "gpio-hlwd",
		.of_match_table	= hlwd_gpio_match,
	पूर्ण,
	.probe	= hlwd_gpio_probe,
पूर्ण;
module_platक्रमm_driver(hlwd_gpio_driver);

MODULE_AUTHOR("Jonathan Neuschथअfer <j.neuschaefer@gmx.net>");
MODULE_DESCRIPTION("Nintendo Wii GPIO driver");
MODULE_LICENSE("GPL");
