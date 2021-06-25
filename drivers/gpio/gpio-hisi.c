<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 HiSilicon Limited. */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#घोषणा HISI_GPIO_SWPORT_DR_SET_WX	0x000
#घोषणा HISI_GPIO_SWPORT_DR_CLR_WX	0x004
#घोषणा HISI_GPIO_SWPORT_DDR_SET_WX	0x010
#घोषणा HISI_GPIO_SWPORT_DDR_CLR_WX	0x014
#घोषणा HISI_GPIO_SWPORT_DDR_ST_WX	0x018
#घोषणा HISI_GPIO_INTEN_SET_WX		0x020
#घोषणा HISI_GPIO_INTEN_CLR_WX		0x024
#घोषणा HISI_GPIO_INTMASK_SET_WX	0x030
#घोषणा HISI_GPIO_INTMASK_CLR_WX	0x034
#घोषणा HISI_GPIO_INTTYPE_EDGE_SET_WX	0x040
#घोषणा HISI_GPIO_INTTYPE_EDGE_CLR_WX	0x044
#घोषणा HISI_GPIO_INT_POLARITY_SET_WX	0x050
#घोषणा HISI_GPIO_INT_POLARITY_CLR_WX	0x054
#घोषणा HISI_GPIO_DEBOUNCE_SET_WX	0x060
#घोषणा HISI_GPIO_DEBOUNCE_CLR_WX	0x064
#घोषणा HISI_GPIO_INTSTATUS_WX		0x070
#घोषणा HISI_GPIO_PORTA_EOI_WX		0x078
#घोषणा HISI_GPIO_EXT_PORT_WX		0x080
#घोषणा HISI_GPIO_INTCOMB_MASK_WX	0x0a0
#घोषणा HISI_GPIO_INT_DEDGE_SET		0x0b0
#घोषणा HISI_GPIO_INT_DEDGE_CLR		0x0b4
#घोषणा HISI_GPIO_INT_DEDGE_ST		0x0b8

#घोषणा HISI_GPIO_LINE_NUM_MAX	32
#घोषणा HISI_GPIO_DRIVER_NAME	"gpio-hisi"

काष्ठा hisi_gpio अणु
	काष्ठा gpio_chip	chip;
	काष्ठा device		*dev;
	व्योम __iomem		*reg_base;
	अचिन्हित पूर्णांक		line_num;
	काष्ठा irq_chip		irq_chip;
	पूर्णांक			irq;
पूर्ण;

अटल अंतरभूत u32 hisi_gpio_पढ़ो_reg(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक off)
अणु
	काष्ठा hisi_gpio *hisi_gpio =
			container_of(chip, काष्ठा hisi_gpio, chip);
	व्योम __iomem *reg = hisi_gpio->reg_base + off;

	वापस पढ़ोl(reg);
पूर्ण

अटल अंतरभूत व्योम hisi_gpio_ग_लिखो_reg(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक off, u32 val)
अणु
	काष्ठा hisi_gpio *hisi_gpio =
			container_of(chip, काष्ठा hisi_gpio, chip);
	व्योम __iomem *reg = hisi_gpio->reg_base + off;

	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम hisi_gpio_set_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक off,
				   u32 debounce)
अणु
	अगर (debounce)
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_DEBOUNCE_SET_WX, BIT(off));
	अन्यथा
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_DEBOUNCE_CLR_WX, BIT(off));
पूर्ण

अटल पूर्णांक hisi_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				अचिन्हित दीर्घ config)
अणु
	u32 config_para = pinconf_to_config_param(config);
	u32 config_arg;

	चयन (config_para) अणु
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		config_arg = pinconf_to_config_argument(config);
		hisi_gpio_set_debounce(chip, offset, config_arg);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hisi_gpio_set_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);

	hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_PORTA_EOI_WX, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम hisi_gpio_irq_set_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);

	hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTMASK_SET_WX, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम hisi_gpio_irq_clr_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);

	hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTMASK_CLR_WX, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल पूर्णांक hisi_gpio_irq_set_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक mask = BIT(irqd_to_hwirq(d));

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INT_DEDGE_SET, mask);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTTYPE_EDGE_SET_WX, mask);
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INT_POLARITY_SET_WX, mask);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTTYPE_EDGE_SET_WX, mask);
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INT_POLARITY_CLR_WX, mask);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTTYPE_EDGE_CLR_WX, mask);
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INT_POLARITY_SET_WX, mask);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTTYPE_EDGE_CLR_WX, mask);
		hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INT_POLARITY_CLR_WX, mask);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * The dual-edge पूर्णांकerrupt and other पूर्णांकerrupt's रेजिस्टरs करो not
	 * take effect at the same समय. The रेजिस्टरs of the two-edge
	 * पूर्णांकerrupts have higher priorities, the configuration of
	 * the dual-edge पूर्णांकerrupts must be disabled beक्रमe the configuration
	 * of other kind of पूर्णांकerrupts.
	 */
	अगर (type != IRQ_TYPE_EDGE_BOTH) अणु
		अचिन्हित पूर्णांक both = hisi_gpio_पढ़ो_reg(chip, HISI_GPIO_INT_DEDGE_ST);

		अगर (both & mask)
			hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INT_DEDGE_CLR, mask);
	पूर्ण

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);

	वापस 0;
पूर्ण

अटल व्योम hisi_gpio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);

	hisi_gpio_irq_clr_mask(d);
	hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTEN_SET_WX, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम hisi_gpio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);

	hisi_gpio_irq_set_mask(d);
	hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTEN_CLR_WX, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम hisi_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा hisi_gpio *hisi_gpio = irq_desc_get_handler_data(desc);
	अचिन्हित दीर्घ irq_msk = hisi_gpio_पढ़ो_reg(&hisi_gpio->chip,
						   HISI_GPIO_INTSTATUS_WX);
	काष्ठा irq_chip *irq_c = irq_desc_get_chip(desc);
	पूर्णांक hwirq;

	chained_irq_enter(irq_c, desc);
	क्रम_each_set_bit(hwirq, &irq_msk, HISI_GPIO_LINE_NUM_MAX)
		generic_handle_irq(irq_find_mapping(hisi_gpio->chip.irq.करोमुख्य,
						    hwirq));
	chained_irq_निकास(irq_c, desc);
पूर्ण

अटल व्योम hisi_gpio_init_irq(काष्ठा hisi_gpio *hisi_gpio)
अणु
	काष्ठा gpio_chip *chip = &hisi_gpio->chip;
	काष्ठा gpio_irq_chip *girq_chip = &chip->irq;

	/* Set hooks क्रम irq_chip */
	hisi_gpio->irq_chip.irq_ack = hisi_gpio_set_ack;
	hisi_gpio->irq_chip.irq_mask = hisi_gpio_irq_set_mask;
	hisi_gpio->irq_chip.irq_unmask = hisi_gpio_irq_clr_mask;
	hisi_gpio->irq_chip.irq_set_type = hisi_gpio_irq_set_type;
	hisi_gpio->irq_chip.irq_enable = hisi_gpio_irq_enable;
	hisi_gpio->irq_chip.irq_disable = hisi_gpio_irq_disable;

	girq_chip->chip = &hisi_gpio->irq_chip;
	girq_chip->शेष_type = IRQ_TYPE_NONE;
	girq_chip->num_parents = 1;
	girq_chip->parents = &hisi_gpio->irq;
	girq_chip->parent_handler = hisi_gpio_irq_handler;
	girq_chip->parent_handler_data = hisi_gpio;

	/* Clear Mask of GPIO controller combine IRQ */
	hisi_gpio_ग_लिखो_reg(chip, HISI_GPIO_INTCOMB_MASK_WX, 1);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_gpio_acpi_match[] = अणु
	अणु"HISI0184", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_gpio_acpi_match);

अटल व्योम hisi_gpio_get_pdata(काष्ठा device *dev,
				काष्ठा hisi_gpio *hisi_gpio)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक idx = 0;

	device_क्रम_each_child_node(dev, fwnode)  अणु
		/* Cycle क्रम once, no need क्रम an array to save line_num */
		अगर (fwnode_property_पढ़ो_u32(fwnode, "ngpios",
					     &hisi_gpio->line_num)) अणु
			dev_err(dev,
				"failed to get number of lines for port%d and use default value instead\n",
				idx);
			hisi_gpio->line_num = HISI_GPIO_LINE_NUM_MAX;
		पूर्ण

		अगर (WARN_ON(hisi_gpio->line_num > HISI_GPIO_LINE_NUM_MAX))
			hisi_gpio->line_num = HISI_GPIO_LINE_NUM_MAX;

		hisi_gpio->irq = platक्रमm_get_irq(pdev, idx);

		dev_info(dev,
			 "get hisi_gpio[%d] with %d lines\n", idx,
			 hisi_gpio->line_num);

		idx++;
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hisi_gpio *hisi_gpio;
	पूर्णांक port_num;
	पूर्णांक ret;

	/*
	 * One GPIO controller own one port currently,
	 * अगर we get more from ACPI table, वापस error.
	 */
	port_num = device_get_child_node_count(dev);
	अगर (WARN_ON(port_num != 1))
		वापस -ENODEV;

	hisi_gpio = devm_kzalloc(dev, माप(*hisi_gpio), GFP_KERNEL);
	अगर (!hisi_gpio)
		वापस -ENOMEM;

	hisi_gpio->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hisi_gpio->reg_base))
		वापस PTR_ERR(hisi_gpio->reg_base);

	hisi_gpio_get_pdata(dev, hisi_gpio);

	hisi_gpio->dev = dev;

	ret = bgpio_init(&hisi_gpio->chip, hisi_gpio->dev, 0x4,
			 hisi_gpio->reg_base + HISI_GPIO_EXT_PORT_WX,
			 hisi_gpio->reg_base + HISI_GPIO_SWPORT_DR_SET_WX,
			 hisi_gpio->reg_base + HISI_GPIO_SWPORT_DR_CLR_WX,
			 hisi_gpio->reg_base + HISI_GPIO_SWPORT_DDR_SET_WX,
			 hisi_gpio->reg_base + HISI_GPIO_SWPORT_DDR_CLR_WX,
			 BGPIOF_NO_SET_ON_INPUT);
	अगर (ret) अणु
		dev_err(dev, "failed to init, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	hisi_gpio->chip.set_config = hisi_gpio_set_config;
	hisi_gpio->chip.ngpio = hisi_gpio->line_num;
	hisi_gpio->chip.bgpio_dir_unपढ़ोable = 1;
	hisi_gpio->chip.base = -1;

	अगर (hisi_gpio->irq > 0)
		hisi_gpio_init_irq(hisi_gpio);

	ret = devm_gpiochip_add_data(dev, &hisi_gpio->chip, hisi_gpio);
	अगर (ret) अणु
		dev_err(dev, "failed to register gpiochip, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hisi_gpio_driver = अणु
	.driver		= अणु
		.name	= HISI_GPIO_DRIVER_NAME,
		.acpi_match_table = hisi_gpio_acpi_match,
	पूर्ण,
	.probe		= hisi_gpio_probe,
पूर्ण;

module_platक्रमm_driver(hisi_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luo Jiaxing <luojiaxing@huawei.com>");
MODULE_DESCRIPTION("HiSilicon GPIO controller driver");
MODULE_ALIAS("platform:" HISI_GPIO_DRIVER_NAME);
