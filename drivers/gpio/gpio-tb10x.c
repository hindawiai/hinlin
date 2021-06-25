<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Abilis Systems MODULE DESCRIPTION
 *
 * Copyright (C) Abilis Systems 2013
 *
 * Authors: Sascha Leuenberger <sascha.leuenberger@abilis.com>
 *          Christian Ruppert <christian.ruppert@abilis.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pinctrl/consumer.h>

#घोषणा TB10X_GPIO_सूची_IN	(0x00000000)
#घोषणा TB10X_GPIO_सूची_OUT	(0x00000001)
#घोषणा OFFSET_TO_REG_DDR	(0x00)
#घोषणा OFFSET_TO_REG_DATA	(0x04)
#घोषणा OFFSET_TO_REG_INT_EN	(0x08)
#घोषणा OFFSET_TO_REG_CHANGE	(0x0C)
#घोषणा OFFSET_TO_REG_WRMASK	(0x10)
#घोषणा OFFSET_TO_REG_INT_TYPE	(0x14)


/**
 * @base: रेजिस्टर base address
 * @करोमुख्य: IRQ करोमुख्य of GPIO generated पूर्णांकerrupts managed by this controller
 * @irq: Interrupt line of parent पूर्णांकerrupt controller
 * @gc: gpio_chip काष्ठाure associated to this GPIO controller
 */
काष्ठा tb10x_gpio अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक irq;
	काष्ठा gpio_chip gc;
पूर्ण;

अटल अंतरभूत u32 tb10x_reg_पढ़ो(काष्ठा tb10x_gpio *gpio, अचिन्हित पूर्णांक offs)
अणु
	वापस ioपढ़ो32(gpio->base + offs);
पूर्ण

अटल अंतरभूत व्योम tb10x_reg_ग_लिखो(काष्ठा tb10x_gpio *gpio, अचिन्हित पूर्णांक offs,
				u32 val)
अणु
	ioग_लिखो32(val, gpio->base + offs);
पूर्ण

अटल अंतरभूत व्योम tb10x_set_bits(काष्ठा tb10x_gpio *gpio, अचिन्हित पूर्णांक offs,
				u32 mask, u32 val)
अणु
	u32 r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio->gc.bgpio_lock, flags);

	r = tb10x_reg_पढ़ो(gpio, offs);
	r = (r & ~mask) | (val & mask);

	tb10x_reg_ग_लिखो(gpio, offs, r);

	spin_unlock_irqrestore(&gpio->gc.bgpio_lock, flags);
पूर्ण

अटल पूर्णांक tb10x_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा tb10x_gpio *tb10x_gpio = gpiochip_get_data(chip);

	वापस irq_create_mapping(tb10x_gpio->करोमुख्य, offset);
पूर्ण

अटल पूर्णांक tb10x_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	अगर ((type & IRQF_TRIGGER_MASK) != IRQ_TYPE_EDGE_BOTH) अणु
		pr_err("Only (both) edge triggered interrupts supported.\n");
		वापस -EINVAL;
	पूर्ण

	irqd_set_trigger_type(data, type);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल irqवापस_t tb10x_gpio_irq_cascade(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tb10x_gpio *tb10x_gpio = data;
	u32 r = tb10x_reg_पढ़ो(tb10x_gpio, OFFSET_TO_REG_CHANGE);
	u32 m = tb10x_reg_पढ़ो(tb10x_gpio, OFFSET_TO_REG_INT_EN);
	स्थिर अचिन्हित दीर्घ bits = r & m;
	पूर्णांक i;

	क्रम_each_set_bit(i, &bits, 32)
		generic_handle_irq(irq_find_mapping(tb10x_gpio->करोमुख्य, i));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tb10x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tb10x_gpio *tb10x_gpio;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret = -EBUSY;
	u32 ngpio;

	अगर (!np)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(np, "abilis,ngpio", &ngpio))
		वापस -EINVAL;

	tb10x_gpio = devm_kzalloc(dev, माप(*tb10x_gpio), GFP_KERNEL);
	अगर (tb10x_gpio == शून्य)
		वापस -ENOMEM;

	tb10x_gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tb10x_gpio->base))
		वापस PTR_ERR(tb10x_gpio->base);

	tb10x_gpio->gc.label =
		devm_kaप्र_लिखो(dev, GFP_KERNEL, "%pOF", pdev->dev.of_node);
	अगर (!tb10x_gpio->gc.label)
		वापस -ENOMEM;

	/*
	 * Initialize generic GPIO with one single रेजिस्टर क्रम पढ़ोing and setting
	 * the lines, no special set or clear रेजिस्टरs and a data direction रेजिस्टर
	 * wher 1 means "output".
	 */
	ret = bgpio_init(&tb10x_gpio->gc, dev, 4,
			 tb10x_gpio->base + OFFSET_TO_REG_DATA,
			 शून्य,
			 शून्य,
			 tb10x_gpio->base + OFFSET_TO_REG_DDR,
			 शून्य,
			 0);
	अगर (ret) अणु
		dev_err(dev, "unable to init generic GPIO\n");
		वापस ret;
	पूर्ण
	tb10x_gpio->gc.base = -1;
	tb10x_gpio->gc.parent = dev;
	tb10x_gpio->gc.owner = THIS_MODULE;
	/*
	 * ngpio is set by bgpio_init() but we override it, this .request()
	 * callback also overrides the one set up by generic GPIO.
	 */
	tb10x_gpio->gc.ngpio = ngpio;
	tb10x_gpio->gc.request = gpiochip_generic_request;
	tb10x_gpio->gc.मुक्त = gpiochip_generic_मुक्त;

	ret = devm_gpiochip_add_data(dev, &tb10x_gpio->gc, tb10x_gpio);
	अगर (ret < 0) अणु
		dev_err(dev, "Could not add gpiochip.\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tb10x_gpio);

	अगर (of_find_property(np, "interrupt-controller", शून्य)) अणु
		काष्ठा irq_chip_generic *gc;

		ret = platक्रमm_get_irq(pdev, 0);
		अगर (ret < 0)
			वापस ret;

		tb10x_gpio->gc.to_irq	= tb10x_gpio_to_irq;
		tb10x_gpio->irq		= ret;

		ret = devm_request_irq(dev, ret, tb10x_gpio_irq_cascade,
				IRQF_TRIGGER_NONE | IRQF_SHARED,
				dev_name(dev), tb10x_gpio);
		अगर (ret != 0)
			वापस ret;

		tb10x_gpio->करोमुख्य = irq_करोमुख्य_add_linear(np,
						tb10x_gpio->gc.ngpio,
						&irq_generic_chip_ops, शून्य);
		अगर (!tb10x_gpio->करोमुख्य) अणु
			वापस -ENOMEM;
		पूर्ण

		ret = irq_alloc_करोमुख्य_generic_chips(tb10x_gpio->करोमुख्य,
				tb10x_gpio->gc.ngpio, 1, tb10x_gpio->gc.label,
				handle_edge_irq, IRQ_NOREQUEST, IRQ_NOPROBE,
				IRQ_GC_INIT_MASK_CACHE);
		अगर (ret)
			वापस ret;

		gc = tb10x_gpio->करोमुख्य->gc->gc[0];
		gc->reg_base                         = tb10x_gpio->base;
		gc->chip_types[0].type               = IRQ_TYPE_EDGE_BOTH;
		gc->chip_types[0].chip.irq_ack       = irq_gc_ack_set_bit;
		gc->chip_types[0].chip.irq_mask      = irq_gc_mask_clr_bit;
		gc->chip_types[0].chip.irq_unmask    = irq_gc_mask_set_bit;
		gc->chip_types[0].chip.irq_set_type  = tb10x_gpio_irq_set_type;
		gc->chip_types[0].regs.ack           = OFFSET_TO_REG_CHANGE;
		gc->chip_types[0].regs.mask          = OFFSET_TO_REG_INT_EN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tb10x_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tb10x_gpio *tb10x_gpio = platक्रमm_get_drvdata(pdev);

	अगर (tb10x_gpio->gc.to_irq) अणु
		irq_हटाओ_generic_chip(tb10x_gpio->करोमुख्य->gc->gc[0],
					BIT(tb10x_gpio->gc.ngpio) - 1, 0, 0);
		kमुक्त(tb10x_gpio->करोमुख्य->gc);
		irq_करोमुख्य_हटाओ(tb10x_gpio->करोमुख्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tb10x_gpio_dt_ids[] = अणु
	अणु .compatible = "abilis,tb10x-gpio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tb10x_gpio_dt_ids);

अटल काष्ठा platक्रमm_driver tb10x_gpio_driver = अणु
	.probe		= tb10x_gpio_probe,
	.हटाओ		= tb10x_gpio_हटाओ,
	.driver = अणु
		.name	= "tb10x-gpio",
		.of_match_table = tb10x_gpio_dt_ids,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(tb10x_gpio_driver);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("tb10x gpio.");
