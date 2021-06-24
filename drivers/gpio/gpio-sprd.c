<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Spपढ़ोtrum Communications Inc.
 * Copyright (C) 2018 Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

/* GPIO रेजिस्टरs definition */
#घोषणा SPRD_GPIO_DATA		0x0
#घोषणा SPRD_GPIO_DMSK		0x4
#घोषणा SPRD_GPIO_सूची		0x8
#घोषणा SPRD_GPIO_IS		0xc
#घोषणा SPRD_GPIO_IBE		0x10
#घोषणा SPRD_GPIO_IEV		0x14
#घोषणा SPRD_GPIO_IE		0x18
#घोषणा SPRD_GPIO_RIS		0x1c
#घोषणा SPRD_GPIO_MIS		0x20
#घोषणा SPRD_GPIO_IC		0x24
#घोषणा SPRD_GPIO_INEN		0x28

/* We have 16 banks GPIOs and each bank contain 16 GPIOs */
#घोषणा SPRD_GPIO_BANK_NR	16
#घोषणा SPRD_GPIO_NR		256
#घोषणा SPRD_GPIO_BANK_SIZE	0x80
#घोषणा SPRD_GPIO_BANK_MASK	GENMASK(15, 0)
#घोषणा SPRD_GPIO_BIT(x)	((x) & (SPRD_GPIO_BANK_NR - 1))

काष्ठा sprd_gpio अणु
	काष्ठा gpio_chip chip;
	व्योम __iomem *base;
	spinlock_t lock;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत व्योम __iomem *sprd_gpio_bank_base(काष्ठा sprd_gpio *sprd_gpio,
						अचिन्हित पूर्णांक bank)
अणु
	वापस sprd_gpio->base + SPRD_GPIO_BANK_SIZE * bank;
पूर्ण

अटल व्योम sprd_gpio_update(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     u16 reg, पूर्णांक val)
अणु
	काष्ठा sprd_gpio *sprd_gpio = gpiochip_get_data(chip);
	व्योम __iomem *base = sprd_gpio_bank_base(sprd_gpio,
						 offset / SPRD_GPIO_BANK_NR);
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&sprd_gpio->lock, flags);
	पंचांगp = पढ़ोl_relaxed(base + reg);

	अगर (val)
		पंचांगp |= BIT(SPRD_GPIO_BIT(offset));
	अन्यथा
		पंचांगp &= ~BIT(SPRD_GPIO_BIT(offset));

	ग_लिखोl_relaxed(पंचांगp, base + reg);
	spin_unlock_irqrestore(&sprd_gpio->lock, flags);
पूर्ण

अटल पूर्णांक sprd_gpio_पढ़ो(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, u16 reg)
अणु
	काष्ठा sprd_gpio *sprd_gpio = gpiochip_get_data(chip);
	व्योम __iomem *base = sprd_gpio_bank_base(sprd_gpio,
						 offset / SPRD_GPIO_BANK_NR);

	वापस !!(पढ़ोl_relaxed(base + reg) & BIT(SPRD_GPIO_BIT(offset)));
पूर्ण

अटल पूर्णांक sprd_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	sprd_gpio_update(chip, offset, SPRD_GPIO_DMSK, 1);
	वापस 0;
पूर्ण

अटल व्योम sprd_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	sprd_gpio_update(chip, offset, SPRD_GPIO_DMSK, 0);
पूर्ण

अटल पूर्णांक sprd_gpio_direction_input(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	sprd_gpio_update(chip, offset, SPRD_GPIO_सूची, 0);
	sprd_gpio_update(chip, offset, SPRD_GPIO_INEN, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_gpio_direction_output(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	sprd_gpio_update(chip, offset, SPRD_GPIO_सूची, 1);
	sprd_gpio_update(chip, offset, SPRD_GPIO_INEN, 0);
	sprd_gpio_update(chip, offset, SPRD_GPIO_DATA, value);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस sprd_gpio_पढ़ो(chip, offset, SPRD_GPIO_DATA);
पूर्ण

अटल व्योम sprd_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			  पूर्णांक value)
अणु
	sprd_gpio_update(chip, offset, SPRD_GPIO_DATA, value);
पूर्ण

अटल व्योम sprd_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);

	sprd_gpio_update(chip, offset, SPRD_GPIO_IE, 0);
पूर्ण

अटल व्योम sprd_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);

	sprd_gpio_update(chip, offset, SPRD_GPIO_IC, 1);
पूर्ण

अटल व्योम sprd_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);

	sprd_gpio_update(chip, offset, SPRD_GPIO_IE, 1);
पूर्ण

अटल पूर्णांक sprd_gpio_irq_set_type(काष्ठा irq_data *data,
				  अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	u32 offset = irqd_to_hwirq(data);

	चयन (flow_type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		sprd_gpio_update(chip, offset, SPRD_GPIO_IS, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IBE, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IEV, 1);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IC, 1);
		irq_set_handler_locked(data, handle_edge_irq);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		sprd_gpio_update(chip, offset, SPRD_GPIO_IS, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IBE, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IEV, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IC, 1);
		irq_set_handler_locked(data, handle_edge_irq);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		sprd_gpio_update(chip, offset, SPRD_GPIO_IS, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IBE, 1);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IC, 1);
		irq_set_handler_locked(data, handle_edge_irq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		sprd_gpio_update(chip, offset, SPRD_GPIO_IS, 1);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IBE, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IEV, 1);
		irq_set_handler_locked(data, handle_level_irq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		sprd_gpio_update(chip, offset, SPRD_GPIO_IS, 1);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IBE, 0);
		sprd_gpio_update(chip, offset, SPRD_GPIO_IEV, 0);
		irq_set_handler_locked(data, handle_level_irq);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *ic = irq_desc_get_chip(desc);
	काष्ठा sprd_gpio *sprd_gpio = gpiochip_get_data(chip);
	u32 bank, n, girq;

	chained_irq_enter(ic, desc);

	क्रम (bank = 0; bank * SPRD_GPIO_BANK_NR < chip->ngpio; bank++) अणु
		व्योम __iomem *base = sprd_gpio_bank_base(sprd_gpio, bank);
		अचिन्हित दीर्घ reg = पढ़ोl_relaxed(base + SPRD_GPIO_MIS) &
			SPRD_GPIO_BANK_MASK;

		क्रम_each_set_bit(n, &reg, SPRD_GPIO_BANK_NR) अणु
			girq = irq_find_mapping(chip->irq.करोमुख्य,
						bank * SPRD_GPIO_BANK_NR + n);

			generic_handle_irq(girq);
		पूर्ण

	पूर्ण
	chained_irq_निकास(ic, desc);
पूर्ण

अटल काष्ठा irq_chip sprd_gpio_irqchip = अणु
	.name = "sprd-gpio",
	.irq_ack = sprd_gpio_irq_ack,
	.irq_mask = sprd_gpio_irq_mask,
	.irq_unmask = sprd_gpio_irq_unmask,
	.irq_set_type = sprd_gpio_irq_set_type,
	.flags = IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक sprd_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_irq_chip *irq;
	काष्ठा sprd_gpio *sprd_gpio;
	पूर्णांक ret;

	sprd_gpio = devm_kzalloc(&pdev->dev, माप(*sprd_gpio), GFP_KERNEL);
	अगर (!sprd_gpio)
		वापस -ENOMEM;

	sprd_gpio->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sprd_gpio->irq < 0)
		वापस sprd_gpio->irq;

	sprd_gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sprd_gpio->base))
		वापस PTR_ERR(sprd_gpio->base);

	spin_lock_init(&sprd_gpio->lock);

	sprd_gpio->chip.label = dev_name(&pdev->dev);
	sprd_gpio->chip.ngpio = SPRD_GPIO_NR;
	sprd_gpio->chip.base = -1;
	sprd_gpio->chip.parent = &pdev->dev;
	sprd_gpio->chip.of_node = pdev->dev.of_node;
	sprd_gpio->chip.request = sprd_gpio_request;
	sprd_gpio->chip.मुक्त = sprd_gpio_मुक्त;
	sprd_gpio->chip.get = sprd_gpio_get;
	sprd_gpio->chip.set = sprd_gpio_set;
	sprd_gpio->chip.direction_input = sprd_gpio_direction_input;
	sprd_gpio->chip.direction_output = sprd_gpio_direction_output;

	irq = &sprd_gpio->chip.irq;
	irq->chip = &sprd_gpio_irqchip;
	irq->handler = handle_bad_irq;
	irq->शेष_type = IRQ_TYPE_NONE;
	irq->parent_handler = sprd_gpio_irq_handler;
	irq->parent_handler_data = sprd_gpio;
	irq->num_parents = 1;
	irq->parents = &sprd_gpio->irq;

	ret = devm_gpiochip_add_data(&pdev->dev, &sprd_gpio->chip, sprd_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sprd_gpio);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_gpio_of_match[] = अणु
	अणु .compatible = "sprd,sc9860-gpio", पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_gpio_of_match);

अटल काष्ठा platक्रमm_driver sprd_gpio_driver = अणु
	.probe = sprd_gpio_probe,
	.driver = अणु
		.name = "sprd-gpio",
		.of_match_table	= sprd_gpio_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(sprd_gpio_driver, sprd_gpio_probe);

MODULE_DESCRIPTION("Spreadtrum GPIO driver");
MODULE_LICENSE("GPL v2");
