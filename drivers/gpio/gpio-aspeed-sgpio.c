<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2019 American Megatrends International LLC.
 *
 * Author: Karthikeyan Mani <karthikeyanm@amiindia.co.in>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>

/*
 * MAX_NR_HW_GPIO represents the number of actual hardware-supported GPIOs (ie,
 * slots within the घड़ीed serial GPIO data). Since each HW GPIO is both an
 * input and an output, we provide MAX_NR_HW_GPIO * 2 lines on our gpiochip
 * device.
 *
 * We use SGPIO_OUTPUT_OFFSET to define the split between the inमाला_दो and
 * outमाला_दो; the inमाला_दो start at line 0, the outमाला_दो start at OUTPUT_OFFSET.
 */
#घोषणा MAX_NR_HW_SGPIO			80
#घोषणा SGPIO_OUTPUT_OFFSET		MAX_NR_HW_SGPIO

#घोषणा ASPEED_SGPIO_CTRL		0x54

#घोषणा ASPEED_SGPIO_PINS_MASK		GENMASK(9, 6)
#घोषणा ASPEED_SGPIO_CLK_DIV_MASK	GENMASK(31, 16)
#घोषणा ASPEED_SGPIO_ENABLE		BIT(0)

काष्ठा aspeed_sgpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा clk *pclk;
	spinlock_t lock;
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक n_sgpio;
पूर्ण;

काष्ठा aspeed_sgpio_bank अणु
	uपूर्णांक16_t    val_regs;
	uपूर्णांक16_t    rdata_reg;
	uपूर्णांक16_t    irq_regs;
	स्थिर अक्षर  names[4][3];
पूर्ण;

/*
 * Note: The "value" रेजिस्टर वापसs the input value when the GPIO is
 *	 configured as an input.
 *
 *	 The "rdata" रेजिस्टर वापसs the output value when the GPIO is
 *	 configured as an output.
 */
अटल स्थिर काष्ठा aspeed_sgpio_bank aspeed_sgpio_banks[] = अणु
	अणु
		.val_regs = 0x0000,
		.rdata_reg = 0x0070,
		.irq_regs = 0x0004,
		.names = अणु "A", "B", "C", "D" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x001C,
		.rdata_reg = 0x0074,
		.irq_regs = 0x0020,
		.names = अणु "E", "F", "G", "H" पूर्ण,
	पूर्ण,
	अणु
		.val_regs = 0x0038,
		.rdata_reg = 0x0078,
		.irq_regs = 0x003C,
		.names = अणु "I", "J" पूर्ण,
	पूर्ण,
पूर्ण;

क्रमागत aspeed_sgpio_reg अणु
	reg_val,
	reg_rdata,
	reg_irq_enable,
	reg_irq_type0,
	reg_irq_type1,
	reg_irq_type2,
	reg_irq_status,
पूर्ण;

#घोषणा GPIO_VAL_VALUE      0x00
#घोषणा GPIO_IRQ_ENABLE     0x00
#घोषणा GPIO_IRQ_TYPE0      0x04
#घोषणा GPIO_IRQ_TYPE1      0x08
#घोषणा GPIO_IRQ_TYPE2      0x0C
#घोषणा GPIO_IRQ_STATUS     0x10

अटल व्योम __iomem *bank_reg(काष्ठा aspeed_sgpio *gpio,
				     स्थिर काष्ठा aspeed_sgpio_bank *bank,
				     स्थिर क्रमागत aspeed_sgpio_reg reg)
अणु
	चयन (reg) अणु
	हाल reg_val:
		वापस gpio->base + bank->val_regs + GPIO_VAL_VALUE;
	हाल reg_rdata:
		वापस gpio->base + bank->rdata_reg;
	हाल reg_irq_enable:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_ENABLE;
	हाल reg_irq_type0:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_TYPE0;
	हाल reg_irq_type1:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_TYPE1;
	हाल reg_irq_type2:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_TYPE2;
	हाल reg_irq_status:
		वापस gpio->base + bank->irq_regs + GPIO_IRQ_STATUS;
	शेष:
		/* acturally अगर code runs to here, it's an error हाल */
		BUG();
	पूर्ण
पूर्ण

#घोषणा GPIO_BANK(x)    ((x % SGPIO_OUTPUT_OFFSET) >> 5)
#घोषणा GPIO_OFFSET(x)  ((x % SGPIO_OUTPUT_OFFSET) & 0x1f)
#घोषणा GPIO_BIT(x)     BIT(GPIO_OFFSET(x))

अटल स्थिर काष्ठा aspeed_sgpio_bank *to_bank(अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक bank;

	bank = GPIO_BANK(offset);

	WARN_ON(bank >= ARRAY_SIZE(aspeed_sgpio_banks));
	वापस &aspeed_sgpio_banks[bank];
पूर्ण

अटल पूर्णांक aspeed_sgpio_init_valid_mask(काष्ठा gpio_chip *gc,
		अचिन्हित दीर्घ *valid_mask, अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा aspeed_sgpio *sgpio = gpiochip_get_data(gc);
	पूर्णांक n = sgpio->n_sgpio;
	पूर्णांक c = SGPIO_OUTPUT_OFFSET - n;

	WARN_ON(ngpios < MAX_NR_HW_SGPIO * 2);

	/* input GPIOs in the lower range */
	biपंचांगap_set(valid_mask, 0, n);
	biपंचांगap_clear(valid_mask, n, c);

	/* output GPIOS above SGPIO_OUTPUT_OFFSET */
	biपंचांगap_set(valid_mask, SGPIO_OUTPUT_OFFSET, n);
	biपंचांगap_clear(valid_mask, SGPIO_OUTPUT_OFFSET + n, c);

	वापस 0;
पूर्ण

अटल व्योम aspeed_sgpio_irq_init_valid_mask(काष्ठा gpio_chip *gc,
		अचिन्हित दीर्घ *valid_mask, अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा aspeed_sgpio *sgpio = gpiochip_get_data(gc);
	पूर्णांक n = sgpio->n_sgpio;

	WARN_ON(ngpios < MAX_NR_HW_SGPIO * 2);

	/* input GPIOs in the lower range */
	biपंचांगap_set(valid_mask, 0, n);
	biपंचांगap_clear(valid_mask, n, ngpios - n);
पूर्ण

अटल bool aspeed_sgpio_is_input(अचिन्हित पूर्णांक offset)
अणु
	वापस offset < SGPIO_OUTPUT_OFFSET;
पूर्ण

अटल पूर्णांक aspeed_sgpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा aspeed_sgpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_sgpio_bank *bank = to_bank(offset);
	अचिन्हित दीर्घ flags;
	क्रमागत aspeed_sgpio_reg reg;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&gpio->lock, flags);

	reg = aspeed_sgpio_is_input(offset) ? reg_val : reg_rdata;
	rc = !!(ioपढ़ो32(bank_reg(gpio, bank, reg)) & GPIO_BIT(offset));

	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक sgpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा aspeed_sgpio *gpio = gpiochip_get_data(gc);
	स्थिर काष्ठा aspeed_sgpio_bank *bank = to_bank(offset);
	व्योम __iomem *addr_r, *addr_w;
	u32 reg = 0;

	अगर (aspeed_sgpio_is_input(offset))
		वापस -EINVAL;

	/* Since this is an output, पढ़ो the cached value from rdata, then
	 * update val. */
	addr_r = bank_reg(gpio, bank, reg_rdata);
	addr_w = bank_reg(gpio, bank, reg_val);

	reg = ioपढ़ो32(addr_r);

	अगर (val)
		reg |= GPIO_BIT(offset);
	अन्यथा
		reg &= ~GPIO_BIT(offset);

	ioग_लिखो32(reg, addr_w);

	वापस 0;
पूर्ण

अटल व्योम aspeed_sgpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा aspeed_sgpio *gpio = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio->lock, flags);

	sgpio_set_value(gc, offset, val);

	spin_unlock_irqrestore(&gpio->lock, flags);
पूर्ण

अटल पूर्णांक aspeed_sgpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	वापस aspeed_sgpio_is_input(offset) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक aspeed_sgpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा aspeed_sgpio *gpio = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/* No special action is required क्रम setting the direction; we'll
	 * error-out in sgpio_set_value अगर this isn't an output GPIO */

	spin_lock_irqsave(&gpio->lock, flags);
	rc = sgpio_set_value(gc, offset, val);
	spin_unlock_irqrestore(&gpio->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक aspeed_sgpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	वापस !!aspeed_sgpio_is_input(offset);
पूर्ण

अटल व्योम irqd_to_aspeed_sgpio_data(काष्ठा irq_data *d,
					काष्ठा aspeed_sgpio **gpio,
					स्थिर काष्ठा aspeed_sgpio_bank **bank,
					u32 *bit, पूर्णांक *offset)
अणु
	काष्ठा aspeed_sgpio *पूर्णांकernal;

	*offset = irqd_to_hwirq(d);
	पूर्णांकernal = irq_data_get_irq_chip_data(d);
	WARN_ON(!पूर्णांकernal);

	*gpio = पूर्णांकernal;
	*bank = to_bank(*offset);
	*bit = GPIO_BIT(*offset);
पूर्ण

अटल व्योम aspeed_sgpio_irq_ack(काष्ठा irq_data *d)
अणु
	स्थिर काष्ठा aspeed_sgpio_bank *bank;
	काष्ठा aspeed_sgpio *gpio;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *status_addr;
	पूर्णांक offset;
	u32 bit;

	irqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);

	status_addr = bank_reg(gpio, bank, reg_irq_status);

	spin_lock_irqsave(&gpio->lock, flags);

	ioग_लिखो32(bit, status_addr);

	spin_unlock_irqrestore(&gpio->lock, flags);
पूर्ण

अटल व्योम aspeed_sgpio_irq_set_mask(काष्ठा irq_data *d, bool set)
अणु
	स्थिर काष्ठा aspeed_sgpio_bank *bank;
	काष्ठा aspeed_sgpio *gpio;
	अचिन्हित दीर्घ flags;
	u32 reg, bit;
	व्योम __iomem *addr;
	पूर्णांक offset;

	irqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);
	addr = bank_reg(gpio, bank, reg_irq_enable);

	spin_lock_irqsave(&gpio->lock, flags);

	reg = ioपढ़ो32(addr);
	अगर (set)
		reg |= bit;
	अन्यथा
		reg &= ~bit;

	ioग_लिखो32(reg, addr);

	spin_unlock_irqrestore(&gpio->lock, flags);
पूर्ण

अटल व्योम aspeed_sgpio_irq_mask(काष्ठा irq_data *d)
अणु
	aspeed_sgpio_irq_set_mask(d, false);
पूर्ण

अटल व्योम aspeed_sgpio_irq_unmask(काष्ठा irq_data *d)
अणु
	aspeed_sgpio_irq_set_mask(d, true);
पूर्ण

अटल पूर्णांक aspeed_sgpio_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	u32 type0 = 0;
	u32 type1 = 0;
	u32 type2 = 0;
	u32 bit, reg;
	स्थिर काष्ठा aspeed_sgpio_bank *bank;
	irq_flow_handler_t handler;
	काष्ठा aspeed_sgpio *gpio;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr;
	पूर्णांक offset;

	irqd_to_aspeed_sgpio_data(d, &gpio, &bank, &bit, &offset);

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		type2 |= bit;
		fallthrough;
	हाल IRQ_TYPE_EDGE_RISING:
		type0 |= bit;
		fallthrough;
	हाल IRQ_TYPE_EDGE_FALLING:
		handler = handle_edge_irq;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		type0 |= bit;
		fallthrough;
	हाल IRQ_TYPE_LEVEL_LOW:
		type1 |= bit;
		handler = handle_level_irq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&gpio->lock, flags);

	addr = bank_reg(gpio, bank, reg_irq_type0);
	reg = ioपढ़ो32(addr);
	reg = (reg & ~bit) | type0;
	ioग_लिखो32(reg, addr);

	addr = bank_reg(gpio, bank, reg_irq_type1);
	reg = ioपढ़ो32(addr);
	reg = (reg & ~bit) | type1;
	ioग_लिखो32(reg, addr);

	addr = bank_reg(gpio, bank, reg_irq_type2);
	reg = ioपढ़ो32(addr);
	reg = (reg & ~bit) | type2;
	ioग_लिखो32(reg, addr);

	spin_unlock_irqrestore(&gpio->lock, flags);

	irq_set_handler_locked(d, handler);

	वापस 0;
पूर्ण

अटल व्योम aspeed_sgpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *ic = irq_desc_get_chip(desc);
	काष्ठा aspeed_sgpio *data = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक i, p, girq;
	अचिन्हित दीर्घ reg;

	chained_irq_enter(ic, desc);

	क्रम (i = 0; i < ARRAY_SIZE(aspeed_sgpio_banks); i++) अणु
		स्थिर काष्ठा aspeed_sgpio_bank *bank = &aspeed_sgpio_banks[i];

		reg = ioपढ़ो32(bank_reg(data, bank, reg_irq_status));

		क्रम_each_set_bit(p, &reg, 32) अणु
			girq = irq_find_mapping(gc->irq.करोमुख्य, i * 32 + p);
			generic_handle_irq(girq);
		पूर्ण

	पूर्ण

	chained_irq_निकास(ic, desc);
पूर्ण

अटल काष्ठा irq_chip aspeed_sgpio_irqchip = अणु
	.name       = "aspeed-sgpio",
	.irq_ack    = aspeed_sgpio_irq_ack,
	.irq_mask   = aspeed_sgpio_irq_mask,
	.irq_unmask = aspeed_sgpio_irq_unmask,
	.irq_set_type   = aspeed_sgpio_set_type,
पूर्ण;

अटल पूर्णांक aspeed_sgpio_setup_irqs(काष्ठा aspeed_sgpio *gpio,
				   काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc, i;
	स्थिर काष्ठा aspeed_sgpio_bank *bank;
	काष्ठा gpio_irq_chip *irq;

	rc = platक्रमm_get_irq(pdev, 0);
	अगर (rc < 0)
		वापस rc;

	gpio->irq = rc;

	/* Disable IRQ and clear Interrupt status रेजिस्टरs क्रम all SGPIO Pins. */
	क्रम (i = 0; i < ARRAY_SIZE(aspeed_sgpio_banks); i++) अणु
		bank =  &aspeed_sgpio_banks[i];
		/* disable irq enable bits */
		ioग_लिखो32(0x00000000, bank_reg(gpio, bank, reg_irq_enable));
		/* clear status bits */
		ioग_लिखो32(0xffffffff, bank_reg(gpio, bank, reg_irq_status));
	पूर्ण

	irq = &gpio->chip.irq;
	irq->chip = &aspeed_sgpio_irqchip;
	irq->init_valid_mask = aspeed_sgpio_irq_init_valid_mask;
	irq->handler = handle_bad_irq;
	irq->शेष_type = IRQ_TYPE_NONE;
	irq->parent_handler = aspeed_sgpio_irq_handler;
	irq->parent_handler_data = gpio;
	irq->parents = &gpio->irq;
	irq->num_parents = 1;

	/* Apply शेष IRQ settings */
	क्रम (i = 0; i < ARRAY_SIZE(aspeed_sgpio_banks); i++) अणु
		bank = &aspeed_sgpio_banks[i];
		/* set falling or level-low irq */
		ioग_लिखो32(0x00000000, bank_reg(gpio, bank, reg_irq_type0));
		/* trigger type is edge */
		ioग_लिखो32(0x00000000, bank_reg(gpio, bank, reg_irq_type1));
		/* single edge trigger */
		ioग_लिखो32(0x00000000, bank_reg(gpio, bank, reg_irq_type2));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_sgpio_of_table[] = अणु
	अणु .compatible = "aspeed,ast2400-sgpio" पूर्ण,
	अणु .compatible = "aspeed,ast2500-sgpio" पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aspeed_sgpio_of_table);

अटल पूर्णांक __init aspeed_sgpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_sgpio *gpio;
	u32 nr_gpios, sgpio_freq, sgpio_clk_भाग;
	पूर्णांक rc;
	अचिन्हित दीर्घ apb_freq;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio->base))
		वापस PTR_ERR(gpio->base);

	rc = of_property_पढ़ो_u32(pdev->dev.of_node, "ngpios", &nr_gpios);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Could not read ngpios property\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (nr_gpios > MAX_NR_HW_SGPIO) अणु
		dev_err(&pdev->dev, "Number of GPIOs exceeds the maximum of %d: %d\n",
			MAX_NR_HW_SGPIO, nr_gpios);
		वापस -EINVAL;
	पूर्ण
	gpio->n_sgpio = nr_gpios;

	rc = of_property_पढ़ो_u32(pdev->dev.of_node, "bus-frequency", &sgpio_freq);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Could not read bus-frequency property\n");
		वापस -EINVAL;
	पूर्ण

	gpio->pclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(gpio->pclk)) अणु
		dev_err(&pdev->dev, "devm_clk_get failed\n");
		वापस PTR_ERR(gpio->pclk);
	पूर्ण

	apb_freq = clk_get_rate(gpio->pclk);

	/*
	 * From the datasheet,
	 *	SGPIO period = 1/PCLK * 2 * (GPIO254[31:16] + 1)
	 *	period = 2 * (GPIO254[31:16] + 1) / PCLK
	 *	frequency = 1 / (2 * (GPIO254[31:16] + 1) / PCLK)
	 *	frequency = PCLK / (2 * (GPIO254[31:16] + 1))
	 *	frequency * 2 * (GPIO254[31:16] + 1) = PCLK
	 *	GPIO254[31:16] = PCLK / (frequency * 2) - 1
	 */
	अगर (sgpio_freq == 0)
		वापस -EINVAL;

	sgpio_clk_भाग = (apb_freq / (sgpio_freq * 2)) - 1;

	अगर (sgpio_clk_भाग > (1 << 16) - 1)
		वापस -EINVAL;

	ioग_लिखो32(FIELD_PREP(ASPEED_SGPIO_CLK_DIV_MASK, sgpio_clk_भाग) |
		  FIELD_PREP(ASPEED_SGPIO_PINS_MASK, (nr_gpios / 8)) |
		  ASPEED_SGPIO_ENABLE,
		  gpio->base + ASPEED_SGPIO_CTRL);

	spin_lock_init(&gpio->lock);

	gpio->chip.parent = &pdev->dev;
	gpio->chip.ngpio = MAX_NR_HW_SGPIO * 2;
	gpio->chip.init_valid_mask = aspeed_sgpio_init_valid_mask;
	gpio->chip.direction_input = aspeed_sgpio_dir_in;
	gpio->chip.direction_output = aspeed_sgpio_dir_out;
	gpio->chip.get_direction = aspeed_sgpio_get_direction;
	gpio->chip.request = शून्य;
	gpio->chip.मुक्त = शून्य;
	gpio->chip.get = aspeed_sgpio_get;
	gpio->chip.set = aspeed_sgpio_set;
	gpio->chip.set_config = शून्य;
	gpio->chip.label = dev_name(&pdev->dev);
	gpio->chip.base = -1;

	aspeed_sgpio_setup_irqs(gpio, pdev);

	rc = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_sgpio_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = aspeed_sgpio_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(aspeed_sgpio_driver, aspeed_sgpio_probe);
MODULE_DESCRIPTION("Aspeed Serial GPIO Driver");
MODULE_LICENSE("GPL");
