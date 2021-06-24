<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/minmax.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

/*
 * Total रेजिस्टर block size is 0x1C क्रम one bank of four ports (A, B, C, D).
 * An optional second bank, with ports E, F, G, and H, may be present, starting
 * at रेजिस्टर offset 0x1C.
 */

/*
 * Pin select: (0) "normal", (1) "dedicate peripheral"
 * Not used on RTL8380/RTL8390, peripheral selection is managed by control bits
 * in the peripheral रेजिस्टरs.
 */
#घोषणा REALTEK_GPIO_REG_CNR		0x00
/* Clear bit (0) क्रम input, set bit (1) क्रम output */
#घोषणा REALTEK_GPIO_REG_सूची		0x08
#घोषणा REALTEK_GPIO_REG_DATA		0x0C
/* Read bit क्रम IRQ status, ग_लिखो 1 to clear IRQ */
#घोषणा REALTEK_GPIO_REG_ISR		0x10
/* Two bits per GPIO in IMR रेजिस्टरs */
#घोषणा REALTEK_GPIO_REG_IMR		0x14
#घोषणा REALTEK_GPIO_REG_IMR_AB		0x14
#घोषणा REALTEK_GPIO_REG_IMR_CD		0x18
#घोषणा REALTEK_GPIO_IMR_LINE_MASK	GENMASK(1, 0)
#घोषणा REALTEK_GPIO_IRQ_EDGE_FALLING	1
#घोषणा REALTEK_GPIO_IRQ_EDGE_RISING	2
#घोषणा REALTEK_GPIO_IRQ_EDGE_BOTH	3

#घोषणा REALTEK_GPIO_MAX		32
#घोषणा REALTEK_GPIO_PORTS_PER_BANK	4

/**
 * realtek_gpio_ctrl - Realtek Otto GPIO driver data
 *
 * @gc: Associated gpio_chip instance
 * @base: Base address of the रेजिस्टर block क्रम a GPIO bank
 * @lock: Lock क्रम accessing the IRQ रेजिस्टरs and values
 * @पूर्णांकr_mask: Mask क्रम पूर्णांकerrupts lines
 * @पूर्णांकr_type: Interrupt type selection
 *
 * Because the पूर्णांकerrupt mask रेजिस्टर (IMR) combines the function of IRQ type
 * selection and masking, two extra values are stored. @पूर्णांकr_mask is used to
 * mask/unmask the पूर्णांकerrupts क्रम a GPIO port, and @पूर्णांकr_type is used to store
 * the selected पूर्णांकerrupt types. The logical AND of these values is written to
 * IMR on changes.
 */
काष्ठा realtek_gpio_ctrl अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *base;
	raw_spinlock_t lock;
	u16 पूर्णांकr_mask[REALTEK_GPIO_PORTS_PER_BANK];
	u16 पूर्णांकr_type[REALTEK_GPIO_PORTS_PER_BANK];
पूर्ण;

/* Expand with more flags as devices with other quirks are added */
क्रमागत realtek_gpio_flags अणु
	/*
	 * Allow disabling पूर्णांकerrupts, क्रम हालs where the port order is
	 * unknown. This may result in a port mismatch between ISR and IMR.
	 * An पूर्णांकerrupt would appear to come from a dअगरferent line than the
	 * line the IRQ handler was asचिन्हित to, causing uncaught पूर्णांकerrupts.
	 */
	GPIO_INTERRUPTS_DISABLED = BIT(0),
पूर्ण;

अटल काष्ठा realtek_gpio_ctrl *irq_data_to_ctrl(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(data);

	वापस container_of(gc, काष्ठा realtek_gpio_ctrl, gc);
पूर्ण

/*
 * Normal port order रेजिस्टर access
 *
 * Port inक्रमmation is stored with the first port at offset 0, followed by the
 * second, etc. Most रेजिस्टरs store one bit per GPIO and use a u8 value per
 * port. The two पूर्णांकerrupt mask रेजिस्टरs store two bits per GPIO, so use u16
 * values.
 */
अटल व्योम realtek_gpio_ग_लिखो_imr(काष्ठा realtek_gpio_ctrl *ctrl,
	अचिन्हित पूर्णांक port, u16 irq_type, u16 irq_mask)
अणु
	ioग_लिखो16(irq_type & irq_mask, ctrl->base + REALTEK_GPIO_REG_IMR + 2 * port);
पूर्ण

अटल व्योम realtek_gpio_clear_isr(काष्ठा realtek_gpio_ctrl *ctrl,
	अचिन्हित पूर्णांक port, u8 mask)
अणु
	ioग_लिखो8(mask, ctrl->base + REALTEK_GPIO_REG_ISR + port);
पूर्ण

अटल u8 realtek_gpio_पढ़ो_isr(काष्ठा realtek_gpio_ctrl *ctrl, अचिन्हित पूर्णांक port)
अणु
	वापस ioपढ़ो8(ctrl->base + REALTEK_GPIO_REG_ISR + port);
पूर्ण

/* Set the rising and falling edge mask bits क्रम a GPIO port pin */
अटल u16 realtek_gpio_imr_bits(अचिन्हित पूर्णांक pin, u16 value)
अणु
	वापस (value & REALTEK_GPIO_IMR_LINE_MASK) << 2 * pin;
पूर्ण

अटल व्योम realtek_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा realtek_gpio_ctrl *ctrl = irq_data_to_ctrl(data);
	irq_hw_number_t line = irqd_to_hwirq(data);
	अचिन्हित पूर्णांक port = line / 8;
	अचिन्हित पूर्णांक port_pin = line % 8;

	realtek_gpio_clear_isr(ctrl, port, BIT(port_pin));
पूर्ण

अटल व्योम realtek_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा realtek_gpio_ctrl *ctrl = irq_data_to_ctrl(data);
	अचिन्हित पूर्णांक line = irqd_to_hwirq(data);
	अचिन्हित पूर्णांक port = line / 8;
	अचिन्हित पूर्णांक port_pin = line % 8;
	अचिन्हित दीर्घ flags;
	u16 m;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	m = ctrl->पूर्णांकr_mask[port];
	m |= realtek_gpio_imr_bits(port_pin, REALTEK_GPIO_IMR_LINE_MASK);
	ctrl->पूर्णांकr_mask[port] = m;
	realtek_gpio_ग_लिखो_imr(ctrl, port, ctrl->पूर्णांकr_type[port], m);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल व्योम realtek_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा realtek_gpio_ctrl *ctrl = irq_data_to_ctrl(data);
	अचिन्हित पूर्णांक line = irqd_to_hwirq(data);
	अचिन्हित पूर्णांक port = line / 8;
	अचिन्हित पूर्णांक port_pin = line % 8;
	अचिन्हित दीर्घ flags;
	u16 m;

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	m = ctrl->पूर्णांकr_mask[port];
	m &= ~realtek_gpio_imr_bits(port_pin, REALTEK_GPIO_IMR_LINE_MASK);
	ctrl->पूर्णांकr_mask[port] = m;
	realtek_gpio_ग_लिखो_imr(ctrl, port, ctrl->पूर्णांकr_type[port], m);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल पूर्णांक realtek_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा realtek_gpio_ctrl *ctrl = irq_data_to_ctrl(data);
	अचिन्हित पूर्णांक line = irqd_to_hwirq(data);
	अचिन्हित पूर्णांक port = line / 8;
	अचिन्हित पूर्णांक port_pin = line % 8;
	अचिन्हित दीर्घ flags;
	u16 type, t;

	चयन (flow_type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		type = REALTEK_GPIO_IRQ_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		type = REALTEK_GPIO_IRQ_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		type = REALTEK_GPIO_IRQ_EDGE_BOTH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	irq_set_handler_locked(data, handle_edge_irq);

	raw_spin_lock_irqsave(&ctrl->lock, flags);
	t = ctrl->पूर्णांकr_type[port];
	t &= ~realtek_gpio_imr_bits(port_pin, REALTEK_GPIO_IMR_LINE_MASK);
	t |= realtek_gpio_imr_bits(port_pin, type);
	ctrl->पूर्णांकr_type[port] = t;
	realtek_gpio_ग_लिखो_imr(ctrl, port, t, ctrl->पूर्णांकr_mask[port]);
	raw_spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम realtek_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा realtek_gpio_ctrl *ctrl = gpiochip_get_data(gc);
	काष्ठा irq_chip *irq_chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक lines_करोne;
	अचिन्हित पूर्णांक port_pin_count;
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ status;
	पूर्णांक offset;

	chained_irq_enter(irq_chip, desc);

	क्रम (lines_करोne = 0; lines_करोne < gc->ngpio; lines_करोne += 8) अणु
		status = realtek_gpio_पढ़ो_isr(ctrl, lines_करोne / 8);
		port_pin_count = min(gc->ngpio - lines_करोne, 8U);
		क्रम_each_set_bit(offset, &status, port_pin_count) अणु
			irq = irq_find_mapping(gc->irq.करोमुख्य, offset);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(irq_chip, desc);
पूर्ण

अटल पूर्णांक realtek_gpio_irq_init(काष्ठा gpio_chip *gc)
अणु
	काष्ठा realtek_gpio_ctrl *ctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक port;

	क्रम (port = 0; (port * 8) < gc->ngpio; port++) अणु
		realtek_gpio_ग_लिखो_imr(ctrl, port, 0, 0);
		realtek_gpio_clear_isr(ctrl, port, GENMASK(7, 0));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip realtek_gpio_irq_chip = अणु
	.name = "realtek-otto-gpio",
	.irq_ack = realtek_gpio_irq_ack,
	.irq_mask = realtek_gpio_irq_mask,
	.irq_unmask = realtek_gpio_irq_unmask,
	.irq_set_type = realtek_gpio_irq_set_type,
पूर्ण;

अटल स्थिर काष्ठा of_device_id realtek_gpio_of_match[] = अणु
	अणु
		.compatible = "realtek,otto-gpio",
		.data = (व्योम *)GPIO_INTERRUPTS_DISABLED,
	पूर्ण,
	अणु
		.compatible = "realtek,rtl8380-gpio",
	पूर्ण,
	अणु
		.compatible = "realtek,rtl8390-gpio",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, realtek_gpio_of_match);

अटल पूर्णांक realtek_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक dev_flags;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा realtek_gpio_ctrl *ctrl;
	u32 ngpios;
	पूर्णांक err, irq;

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	dev_flags = (अचिन्हित पूर्णांक) device_get_match_data(dev);

	ngpios = REALTEK_GPIO_MAX;
	device_property_पढ़ो_u32(dev, "ngpios", &ngpios);

	अगर (ngpios > REALTEK_GPIO_MAX) अणु
		dev_err(&pdev->dev, "invalid ngpios (max. %d)\n",
			REALTEK_GPIO_MAX);
		वापस -EINVAL;
	पूर्ण

	ctrl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctrl->base))
		वापस PTR_ERR(ctrl->base);

	raw_spin_lock_init(&ctrl->lock);

	err = bgpio_init(&ctrl->gc, dev, 4,
		ctrl->base + REALTEK_GPIO_REG_DATA, शून्य, शून्य,
		ctrl->base + REALTEK_GPIO_REG_सूची, शून्य,
		BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	अगर (err) अणु
		dev_err(dev, "unable to init generic GPIO");
		वापस err;
	पूर्ण

	ctrl->gc.ngpio = ngpios;
	ctrl->gc.owner = THIS_MODULE;

	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (!(dev_flags & GPIO_INTERRUPTS_DISABLED) && irq > 0) अणु
		girq = &ctrl->gc.irq;
		girq->chip = &realtek_gpio_irq_chip;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
		girq->parent_handler = realtek_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, girq->num_parents,
					माप(*girq->parents),	GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = irq;
		girq->init_hw = realtek_gpio_irq_init;
	पूर्ण

	वापस devm_gpiochip_add_data(dev, &ctrl->gc, ctrl);
पूर्ण

अटल काष्ठा platक्रमm_driver realtek_gpio_driver = अणु
	.driver = अणु
		.name = "realtek-otto-gpio",
		.of_match_table	= realtek_gpio_of_match,
	पूर्ण,
	.probe = realtek_gpio_probe,
पूर्ण;
module_platक्रमm_driver(realtek_gpio_driver);

MODULE_DESCRIPTION("Realtek Otto GPIO support");
MODULE_AUTHOR("Sander Vanheule <sander@svanheule.net>");
MODULE_LICENSE("GPL v2");
