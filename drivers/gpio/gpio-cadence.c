<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2017-2018 Cadence
 *
 * Authors:
 *  Jan Kotas <jank@cadence.com>
 *  Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा CDNS_GPIO_BYPASS_MODE		0x00
#घोषणा CDNS_GPIO_सूचीECTION_MODE	0x04
#घोषणा CDNS_GPIO_OUTPUT_EN		0x08
#घोषणा CDNS_GPIO_OUTPUT_VALUE		0x0c
#घोषणा CDNS_GPIO_INPUT_VALUE		0x10
#घोषणा CDNS_GPIO_IRQ_MASK		0x14
#घोषणा CDNS_GPIO_IRQ_EN		0x18
#घोषणा CDNS_GPIO_IRQ_DIS		0x1c
#घोषणा CDNS_GPIO_IRQ_STATUS		0x20
#घोषणा CDNS_GPIO_IRQ_TYPE		0x24
#घोषणा CDNS_GPIO_IRQ_VALUE		0x28
#घोषणा CDNS_GPIO_IRQ_ANY_EDGE		0x2c

काष्ठा cdns_gpio_chip अणु
	काष्ठा gpio_chip gc;
	काष्ठा clk *pclk;
	व्योम __iomem *regs;
	u32 bypass_orig;
पूर्ण;

अटल पूर्णांक cdns_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->bgpio_lock, flags);

	ioग_लिखो32(ioपढ़ो32(cgpio->regs + CDNS_GPIO_BYPASS_MODE) & ~BIT(offset),
		  cgpio->regs + CDNS_GPIO_BYPASS_MODE);

	spin_unlock_irqrestore(&chip->bgpio_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम cdns_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->bgpio_lock, flags);

	ioग_लिखो32(ioपढ़ो32(cgpio->regs + CDNS_GPIO_BYPASS_MODE) |
		  (BIT(offset) & cgpio->bypass_orig),
		  cgpio->regs + CDNS_GPIO_BYPASS_MODE);

	spin_unlock_irqrestore(&chip->bgpio_lock, flags);
पूर्ण

अटल व्योम cdns_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा cdns_gpio_chip *cgpio = gpiochip_get_data(chip);

	ioग_लिखो32(BIT(d->hwirq), cgpio->regs + CDNS_GPIO_IRQ_DIS);
पूर्ण

अटल व्योम cdns_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा cdns_gpio_chip *cgpio = gpiochip_get_data(chip);

	ioग_लिखो32(BIT(d->hwirq), cgpio->regs + CDNS_GPIO_IRQ_EN);
पूर्ण

अटल पूर्णांक cdns_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	u32 पूर्णांक_value;
	u32 पूर्णांक_type;
	u32 mask = BIT(d->hwirq);
	पूर्णांक ret = 0;

	spin_lock_irqsave(&chip->bgpio_lock, flags);

	पूर्णांक_value = ioपढ़ो32(cgpio->regs + CDNS_GPIO_IRQ_VALUE) & ~mask;
	पूर्णांक_type = ioपढ़ो32(cgpio->regs + CDNS_GPIO_IRQ_TYPE) & ~mask;

	/*
	 * The GPIO controller करोesn't have an ACK रेजिस्टर.
	 * All पूर्णांकerrupt statuses are cleared on a status रेजिस्टर पढ़ो.
	 * Don't support edge पूर्णांकerrupts क्रम now.
	 */

	अगर (type == IRQ_TYPE_LEVEL_HIGH) अणु
		पूर्णांक_type |= mask;
		पूर्णांक_value |= mask;
	पूर्ण अन्यथा अगर (type == IRQ_TYPE_LEVEL_LOW) अणु
		पूर्णांक_type |= mask;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err_irq_type;
	पूर्ण

	ioग_लिखो32(पूर्णांक_value, cgpio->regs + CDNS_GPIO_IRQ_VALUE);
	ioग_लिखो32(पूर्णांक_type, cgpio->regs + CDNS_GPIO_IRQ_TYPE);

err_irq_type:
	spin_unlock_irqrestore(&chip->bgpio_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम cdns_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ status;
	पूर्णांक hwirq;

	chained_irq_enter(irqchip, desc);

	status = ioपढ़ो32(cgpio->regs + CDNS_GPIO_IRQ_STATUS) &
		~ioपढ़ो32(cgpio->regs + CDNS_GPIO_IRQ_MASK);

	क्रम_each_set_bit(hwirq, &status, chip->ngpio)
		generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य, hwirq));

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल काष्ठा irq_chip cdns_gpio_irqchip = अणु
	.name		= "cdns-gpio",
	.irq_mask	= cdns_gpio_irq_mask,
	.irq_unmask	= cdns_gpio_irq_unmask,
	.irq_set_type	= cdns_gpio_irq_set_type
पूर्ण;

अटल पूर्णांक cdns_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_gpio_chip *cgpio;
	पूर्णांक ret, irq;
	u32 dir_prev;
	u32 num_gpios = 32;

	cgpio = devm_kzalloc(&pdev->dev, माप(*cgpio), GFP_KERNEL);
	अगर (!cgpio)
		वापस -ENOMEM;

	cgpio->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cgpio->regs))
		वापस PTR_ERR(cgpio->regs);

	of_property_पढ़ो_u32(pdev->dev.of_node, "ngpios", &num_gpios);

	अगर (num_gpios > 32) अणु
		dev_err(&pdev->dev, "ngpios must be less or equal 32\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set all pins as inमाला_दो by शेष, otherwise:
	 * gpiochip_lock_as_irq:
	 * tried to flag a GPIO set as output क्रम IRQ
	 * Generic GPIO driver stores the direction value पूर्णांकernally,
	 * so it needs to be changed beक्रमe bgpio_init() is called.
	 */
	dir_prev = ioपढ़ो32(cgpio->regs + CDNS_GPIO_सूचीECTION_MODE);
	ioग_लिखो32(GENMASK(num_gpios - 1, 0),
		  cgpio->regs + CDNS_GPIO_सूचीECTION_MODE);

	ret = bgpio_init(&cgpio->gc, &pdev->dev, 4,
			 cgpio->regs + CDNS_GPIO_INPUT_VALUE,
			 cgpio->regs + CDNS_GPIO_OUTPUT_VALUE,
			 शून्य,
			 शून्य,
			 cgpio->regs + CDNS_GPIO_सूचीECTION_MODE,
			 BGPIOF_READ_OUTPUT_REG_SET);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register generic gpio, %d\n",
			ret);
		जाओ err_revert_dir;
	पूर्ण

	cgpio->gc.label = dev_name(&pdev->dev);
	cgpio->gc.ngpio = num_gpios;
	cgpio->gc.parent = &pdev->dev;
	cgpio->gc.base = -1;
	cgpio->gc.owner = THIS_MODULE;
	cgpio->gc.request = cdns_gpio_request;
	cgpio->gc.मुक्त = cdns_gpio_मुक्त;

	cgpio->pclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(cgpio->pclk)) अणु
		ret = PTR_ERR(cgpio->pclk);
		dev_err(&pdev->dev,
			"Failed to retrieve peripheral clock, %d\n", ret);
		जाओ err_revert_dir;
	पूर्ण

	ret = clk_prepare_enable(cgpio->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to enable the peripheral clock, %d\n", ret);
		जाओ err_revert_dir;
	पूर्ण

	/*
	 * Optional irq_chip support
	 */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq >= 0) अणु
		काष्ठा gpio_irq_chip *girq;

		girq = &cgpio->gc.irq;
		girq->chip = &cdns_gpio_irqchip;
		girq->parent_handler = cdns_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents) अणु
			ret = -ENOMEM;
			जाओ err_disable_clk;
		पूर्ण
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
	पूर्ण

	ret = devm_gpiochip_add_data(&pdev->dev, &cgpio->gc, cgpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		जाओ err_disable_clk;
	पूर्ण

	cgpio->bypass_orig = ioपढ़ो32(cgpio->regs + CDNS_GPIO_BYPASS_MODE);

	/*
	 * Enable gpio outमाला_दो, ignored क्रम input direction
	 */
	ioग_लिखो32(GENMASK(num_gpios - 1, 0),
		  cgpio->regs + CDNS_GPIO_OUTPUT_EN);
	ioग_लिखो32(0, cgpio->regs + CDNS_GPIO_BYPASS_MODE);

	platक्रमm_set_drvdata(pdev, cgpio);
	वापस 0;

err_disable_clk:
	clk_disable_unprepare(cgpio->pclk);

err_revert_dir:
	ioग_लिखो32(dir_prev, cgpio->regs + CDNS_GPIO_सूचीECTION_MODE);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_gpio_chip *cgpio = platक्रमm_get_drvdata(pdev);

	ioग_लिखो32(cgpio->bypass_orig, cgpio->regs + CDNS_GPIO_BYPASS_MODE);
	clk_disable_unprepare(cgpio->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cdns_of_ids[] = अणु
	अणु .compatible = "cdns,gpio-r1p02" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_of_ids);

अटल काष्ठा platक्रमm_driver cdns_gpio_driver = अणु
	.driver = अणु
		.name = "cdns-gpio",
		.of_match_table = cdns_of_ids,
	पूर्ण,
	.probe = cdns_gpio_probe,
	.हटाओ = cdns_gpio_हटाओ,
पूर्ण;
module_platक्रमm_driver(cdns_gpio_driver);

MODULE_AUTHOR("Jan Kotas <jank@cadence.com>");
MODULE_DESCRIPTION("Cadence GPIO driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cdns-gpio");
