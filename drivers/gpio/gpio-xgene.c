<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppliedMicro X-Gene SoC GPIO Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Feng Kan <fkan@apm.com>.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#घोषणा GPIO_SET_DR_OFFSET	0x0C
#घोषणा GPIO_DATA_OFFSET	0x14
#घोषणा GPIO_BANK_STRIDE	0x0C

#घोषणा XGENE_GPIOS_PER_BANK	16
#घोषणा XGENE_MAX_GPIO_BANKS	3
#घोषणा XGENE_MAX_GPIOS		(XGENE_GPIOS_PER_BANK * XGENE_MAX_GPIO_BANKS)

#घोषणा GPIO_BIT_OFFSET(x)	(x % XGENE_GPIOS_PER_BANK)
#घोषणा GPIO_BANK_OFFSET(x)	((x / XGENE_GPIOS_PER_BANK) * GPIO_BANK_STRIDE)

काष्ठा xgene_gpio अणु
	काष्ठा gpio_chip	chip;
	व्योम __iomem		*base;
	spinlock_t		lock;
	u32			set_dr_val[XGENE_MAX_GPIO_BANKS];
पूर्ण;

अटल पूर्णांक xgene_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा xgene_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ bank_offset;
	u32 bit_offset;

	bank_offset = GPIO_DATA_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);
	वापस !!(ioपढ़ो32(chip->base + bank_offset) & BIT(bit_offset));
पूर्ण

अटल व्योम __xgene_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा xgene_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ bank_offset;
	u32 setval, bit_offset;

	bank_offset = GPIO_SET_DR_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset) + XGENE_GPIOS_PER_BANK;

	setval = ioपढ़ो32(chip->base + bank_offset);
	अगर (val)
		setval |= BIT(bit_offset);
	अन्यथा
		setval &= ~BIT(bit_offset);
	ioग_लिखो32(setval, chip->base + bank_offset);
पूर्ण

अटल व्योम xgene_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा xgene_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	__xgene_gpio_set(gc, offset, val);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल पूर्णांक xgene_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा xgene_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ bank_offset, bit_offset;

	bank_offset = GPIO_SET_DR_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	अगर (ioपढ़ो32(chip->base + bank_offset) & BIT(bit_offset))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक xgene_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा xgene_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags, bank_offset;
	u32 dirval, bit_offset;

	bank_offset = GPIO_SET_DR_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	spin_lock_irqsave(&chip->lock, flags);

	dirval = ioपढ़ो32(chip->base + bank_offset);
	dirval |= BIT(bit_offset);
	ioग_लिखो32(dirval, chip->base + bank_offset);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_gpio_dir_out(काष्ठा gpio_chip *gc,
					अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा xgene_gpio *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags, bank_offset;
	u32 dirval, bit_offset;

	bank_offset = GPIO_SET_DR_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	spin_lock_irqsave(&chip->lock, flags);

	dirval = ioपढ़ो32(chip->base + bank_offset);
	dirval &= ~BIT(bit_offset);
	ioग_लिखो32(dirval, chip->base + bank_offset);
	__xgene_gpio_set(gc, offset, val);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक xgene_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा xgene_gpio *gpio = dev_get_drvdata(dev);
	अचिन्हित दीर्घ bank_offset;
	अचिन्हित पूर्णांक bank;

	क्रम (bank = 0; bank < XGENE_MAX_GPIO_BANKS; bank++) अणु
		bank_offset = GPIO_SET_DR_OFFSET + bank * GPIO_BANK_STRIDE;
		gpio->set_dr_val[bank] = ioपढ़ो32(gpio->base + bank_offset);
	पूर्ण
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक xgene_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा xgene_gpio *gpio = dev_get_drvdata(dev);
	अचिन्हित दीर्घ bank_offset;
	अचिन्हित पूर्णांक bank;

	क्रम (bank = 0; bank < XGENE_MAX_GPIO_BANKS; bank++) अणु
		bank_offset = GPIO_SET_DR_OFFSET + bank * GPIO_BANK_STRIDE;
		ioग_लिखो32(gpio->set_dr_val[bank], gpio->base + bank_offset);
	पूर्ण
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(xgene_gpio_pm, xgene_gpio_suspend, xgene_gpio_resume);

अटल पूर्णांक xgene_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_gpio *gpio;
	पूर्णांक err = 0;

	gpio = devm_kzalloc(&pdev->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio->base))
		वापस PTR_ERR(gpio->base);

	gpio->chip.ngpio = XGENE_MAX_GPIOS;

	spin_lock_init(&gpio->lock);
	gpio->chip.parent = &pdev->dev;
	gpio->chip.get_direction = xgene_gpio_get_direction;
	gpio->chip.direction_input = xgene_gpio_dir_in;
	gpio->chip.direction_output = xgene_gpio_dir_out;
	gpio->chip.get = xgene_gpio_get;
	gpio->chip.set = xgene_gpio_set;
	gpio->chip.label = dev_name(&pdev->dev);
	gpio->chip.base = -1;

	platक्रमm_set_drvdata(pdev, gpio);

	err = devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed to register gpiochip.\n");
		वापस err;
	पूर्ण

	dev_info(&pdev->dev, "X-Gene GPIO driver registered.\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_gpio_of_match[] = अणु
	अणु .compatible = "apm,xgene-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_gpio_acpi_match[] = अणु
	अणु "APMC0D14", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xgene_gpio_driver = अणु
	.driver = अणु
		.name = "xgene-gpio",
		.of_match_table = xgene_gpio_of_match,
		.acpi_match_table = ACPI_PTR(xgene_gpio_acpi_match),
		.pm     = &xgene_gpio_pm,
	पूर्ण,
	.probe = xgene_gpio_probe,
पूर्ण;
builtin_platक्रमm_driver(xgene_gpio_driver);
