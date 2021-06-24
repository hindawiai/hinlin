<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Access to GPOs on TWL6040 chip
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Authors:
 *	Sergio Aguirre <saaguirre@ti.com>
 *	Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of.h>

#समावेश <linux/mfd/twl6040.h>

अटल पूर्णांक twl6040gpo_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा twl6040 *twl6040 = dev_get_drvdata(chip->parent->parent);
	पूर्णांक ret = 0;

	ret = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_GPOCTL);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & BIT(offset));
पूर्ण

अटल पूर्णांक twl6040gpo_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक twl6040gpo_direction_out(काष्ठा gpio_chip *chip, अचिन्हित offset,
				    पूर्णांक value)
अणु
	/* This only drives GPOs, and can't change direction */
	वापस 0;
पूर्ण

अटल व्योम twl6040gpo_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा twl6040 *twl6040 = dev_get_drvdata(chip->parent->parent);
	पूर्णांक ret;
	u8 gpoctl;

	ret = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_GPOCTL);
	अगर (ret < 0)
		वापस;

	अगर (value)
		gpoctl = ret | BIT(offset);
	अन्यथा
		gpoctl = ret & ~BIT(offset);

	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_GPOCTL, gpoctl);
पूर्ण

अटल काष्ठा gpio_chip twl6040gpo_chip = अणु
	.label			= "twl6040",
	.owner			= THIS_MODULE,
	.get			= twl6040gpo_get,
	.direction_output	= twl6040gpo_direction_out,
	.get_direction		= twl6040gpo_get_direction,
	.set			= twl6040gpo_set,
	.can_sleep		= true,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल पूर्णांक gpo_twl6040_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *twl6040_core_dev = pdev->dev.parent;
	काष्ठा twl6040 *twl6040 = dev_get_drvdata(twl6040_core_dev);
	पूर्णांक ret;

	twl6040gpo_chip.base = -1;

	अगर (twl6040_get_revid(twl6040) < TWL6041_REV_ES2_0)
		twl6040gpo_chip.ngpio = 3; /* twl6040 have 3 GPO */
	अन्यथा
		twl6040gpo_chip.ngpio = 1; /* twl6041 have 1 GPO */

	twl6040gpo_chip.parent = &pdev->dev;
#अगर_घोषित CONFIG_OF_GPIO
	twl6040gpo_chip.of_node = twl6040_core_dev->of_node;
#पूर्ण_अगर

	ret = devm_gpiochip_add_data(&pdev->dev, &twl6040gpo_chip, शून्य);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not register gpiochip, %d\n", ret);
		twl6040gpo_chip.ngpio = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Note:  this hardware lives inside an I2C-based multi-function device. */
MODULE_ALIAS("platform:twl6040-gpo");

अटल काष्ठा platक्रमm_driver gpo_twl6040_driver = अणु
	.driver = अणु
		.name	= "twl6040-gpo",
	पूर्ण,
	.probe		= gpo_twl6040_probe,
पूर्ण;

module_platक्रमm_driver(gpo_twl6040_driver);

MODULE_AUTHOR("Texas Instruments, Inc.");
MODULE_DESCRIPTION("GPO interface for TWL6040");
MODULE_LICENSE("GPL");
