<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम Exar XR17V35X chip
 *
 * Copyright (C) 2015 Sudip Mukherjee <sudip.mukherjee@codethink.co.uk>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा EXAR_OFFSET_MPIOLVL_LO 0x90
#घोषणा EXAR_OFFSET_MPIOSEL_LO 0x93
#घोषणा EXAR_OFFSET_MPIOLVL_HI 0x96
#घोषणा EXAR_OFFSET_MPIOSEL_HI 0x99

#घोषणा DRIVER_NAME "gpio_exar"

अटल DEFINE_IDA(ida_index);

काष्ठा exar_gpio_chip अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा regmap *regmap;
	पूर्णांक index;
	अक्षर name[20];
	अचिन्हित पूर्णांक first_pin;
पूर्ण;

अटल अचिन्हित पूर्णांक
exar_offset_to_sel_addr(काष्ठा exar_gpio_chip *exar_gpio, अचिन्हित पूर्णांक offset)
अणु
	वापस (offset + exar_gpio->first_pin) / 8 ? EXAR_OFFSET_MPIOSEL_HI
						   : EXAR_OFFSET_MPIOSEL_LO;
पूर्ण

अटल अचिन्हित पूर्णांक
exar_offset_to_lvl_addr(काष्ठा exar_gpio_chip *exar_gpio, अचिन्हित पूर्णांक offset)
अणु
	वापस (offset + exar_gpio->first_pin) / 8 ? EXAR_OFFSET_MPIOLVL_HI
						   : EXAR_OFFSET_MPIOLVL_LO;
पूर्ण

अटल अचिन्हित पूर्णांक
exar_offset_to_bit(काष्ठा exar_gpio_chip *exar_gpio, अचिन्हित पूर्णांक offset)
अणु
	वापस (offset + exar_gpio->first_pin) % 8;
पूर्ण

अटल पूर्णांक exar_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक addr = exar_offset_to_sel_addr(exar_gpio, offset);
	अचिन्हित पूर्णांक bit = exar_offset_to_bit(exar_gpio, offset);

	अगर (regmap_test_bits(exar_gpio->regmap, addr, BIT(bit)))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक exar_get_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक addr = exar_offset_to_lvl_addr(exar_gpio, offset);
	अचिन्हित पूर्णांक bit = exar_offset_to_bit(exar_gpio, offset);

	वापस !!(regmap_test_bits(exar_gpio->regmap, addr, BIT(bit)));
पूर्ण

अटल व्योम exar_set_value(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक addr = exar_offset_to_lvl_addr(exar_gpio, offset);
	अचिन्हित पूर्णांक bit = exar_offset_to_bit(exar_gpio, offset);

	अगर (value)
		regmap_set_bits(exar_gpio->regmap, addr, BIT(bit));
	अन्यथा
		regmap_clear_bits(exar_gpio->regmap, addr, BIT(bit));
पूर्ण

अटल पूर्णांक exar_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 पूर्णांक value)
अणु
	काष्ठा exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक addr = exar_offset_to_sel_addr(exar_gpio, offset);
	अचिन्हित पूर्णांक bit = exar_offset_to_bit(exar_gpio, offset);

	exar_set_value(chip, offset, value);
	regmap_clear_bits(exar_gpio->regmap, addr, BIT(bit));

	वापस 0;
पूर्ण

अटल पूर्णांक exar_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक addr = exar_offset_to_sel_addr(exar_gpio, offset);
	अचिन्हित पूर्णांक bit = exar_offset_to_bit(exar_gpio, offset);

	regmap_set_bits(exar_gpio->regmap, addr, BIT(bit));

	वापस 0;
पूर्ण

अटल व्योम exar_devm_ida_मुक्त(व्योम *data)
अणु
	काष्ठा exar_gpio_chip *exar_gpio = data;

	ida_मुक्त(&ida_index, exar_gpio->index);
पूर्ण

अटल स्थिर काष्ठा regmap_config exar_regmap_config = अणु
	.name		= "exar-gpio",
	.reg_bits	= 16,
	.val_bits	= 8,
पूर्ण;

अटल पूर्णांक gpio_exar_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_dev *pcidev = to_pci_dev(dev->parent);
	काष्ठा exar_gpio_chip *exar_gpio;
	u32 first_pin, ngpios;
	व्योम __iomem *p;
	पूर्णांक index, ret;

	/*
	 * The UART driver must have mapped region 0 prior to रेजिस्टरing this
	 * device - use it.
	 */
	p = pcim_iomap_table(pcidev)[0];
	अगर (!p)
		वापस -ENOMEM;

	ret = device_property_पढ़ो_u32(dev, "exar,first-pin", &first_pin);
	अगर (ret)
		वापस ret;

	ret = device_property_पढ़ो_u32(dev, "ngpios", &ngpios);
	अगर (ret)
		वापस ret;

	exar_gpio = devm_kzalloc(dev, माप(*exar_gpio), GFP_KERNEL);
	अगर (!exar_gpio)
		वापस -ENOMEM;

	/*
	 * We करोn't need to check the वापस values of mmio regmap operations (unless
	 * the regmap has a घड़ी attached which is not the हाल here).
	 */
	exar_gpio->regmap = devm_regmap_init_mmio(dev, p, &exar_regmap_config);
	अगर (IS_ERR(exar_gpio->regmap))
		वापस PTR_ERR(exar_gpio->regmap);

	index = ida_alloc(&ida_index, GFP_KERNEL);
	अगर (index < 0)
		वापस index;

	ret = devm_add_action_or_reset(dev, exar_devm_ida_मुक्त, exar_gpio);
	अगर (ret)
		वापस ret;

	प्र_लिखो(exar_gpio->name, "exar_gpio%d", index);
	exar_gpio->gpio_chip.label = exar_gpio->name;
	exar_gpio->gpio_chip.parent = dev;
	exar_gpio->gpio_chip.direction_output = exar_direction_output;
	exar_gpio->gpio_chip.direction_input = exar_direction_input;
	exar_gpio->gpio_chip.get_direction = exar_get_direction;
	exar_gpio->gpio_chip.get = exar_get_value;
	exar_gpio->gpio_chip.set = exar_set_value;
	exar_gpio->gpio_chip.base = -1;
	exar_gpio->gpio_chip.ngpio = ngpios;
	exar_gpio->index = index;
	exar_gpio->first_pin = first_pin;

	ret = devm_gpiochip_add_data(dev, &exar_gpio->gpio_chip, exar_gpio);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, exar_gpio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gpio_exar_driver = अणु
	.probe	= gpio_exar_probe,
	.driver	= अणु
		.name = DRIVER_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_exar_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_DESCRIPTION("Exar GPIO driver");
MODULE_AUTHOR("Sudip Mukherjee <sudip.mukherjee@codethink.co.uk>");
MODULE_LICENSE("GPL");
