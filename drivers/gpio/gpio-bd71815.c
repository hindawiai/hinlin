<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support to GPOs on ROHM BD71815
 * Copyright 2021 ROHM Semiconductors.
 * Author: Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>
 *
 * Copyright 2014 Embest Technology Co. Ltd. Inc.
 * Author: yanglsh@embest-tech.com
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
/* For the BD71815 रेजिस्टर definitions */
#समावेश <linux/mfd/rohm-bd71815.h>

काष्ठा bd71815_gpio अणु
	/* chip.parent poपूर्णांकs the MFD which provides DT node and regmap */
	काष्ठा gpio_chip chip;
	/* dev poपूर्णांकs to the platक्रमm device क्रम devm and prपूर्णांकs */
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक bd71815gpo_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bd71815_gpio *bd71815 = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(bd71815->regmap, BD71815_REG_GPO, &val);
	अगर (ret)
		वापस ret;

	वापस (val >> offset) & 1;
पूर्ण

अटल व्योम bd71815gpo_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा bd71815_gpio *bd71815 = gpiochip_get_data(chip);
	पूर्णांक ret, bit;

	bit = BIT(offset);

	अगर (value)
		ret = regmap_set_bits(bd71815->regmap, BD71815_REG_GPO, bit);
	अन्यथा
		ret = regmap_clear_bits(bd71815->regmap, BD71815_REG_GPO, bit);

	अगर (ret)
		dev_warn(bd71815->dev, "failed to toggle GPO\n");
पूर्ण

अटल पूर्णांक bd71815_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा bd71815_gpio *bdgpio = gpiochip_get_data(chip);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(bdgpio->regmap,
					  BD71815_REG_GPO,
					  BD71815_GPIO_DRIVE_MASK << offset,
					  BD71815_GPIO_OPEN_DRAIN << offset);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(bdgpio->regmap,
					  BD71815_REG_GPO,
					  BD71815_GPIO_DRIVE_MASK << offset,
					  BD71815_GPIO_CMOS << offset);
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

/* BD71815 GPIO is actually GPO */
अटल पूर्णांक bd71815gpo_direction_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

/* Template क्रम GPIO chip */
अटल स्थिर काष्ठा gpio_chip bd71815gpo_chip = अणु
	.label			= "bd71815",
	.owner			= THIS_MODULE,
	.get			= bd71815gpo_get,
	.get_direction		= bd71815gpo_direction_get,
	.set			= bd71815gpo_set,
	.set_config		= bd71815_gpio_set_config,
	.can_sleep		= true,
पूर्ण;

#घोषणा BD71815_TWO_GPIOS	GENMASK(1, 0)
#घोषणा BD71815_ONE_GPIO	BIT(0)

/*
 * Sigh. The BD71815 and BD71817 were originally deचिन्हित to support two GPO
 * pins. At some poपूर्णांक it was noticed the second GPO pin which is the E5 pin
 * located at the center of IC is hard to use on PCB (due to the location). It
 * was decided to not promote this second GPO and the pin is marked as GND in
 * the datasheet. The functionality is still there though! I guess driving a GPO
 * connected to the ground is a bad idea. Thus we करो not support it by शेष.
 * OTOH - the original driver written by colleagues at Embest did support
 * controlling this second GPO. It is thus possible this is used in some of the
 * products.
 *
 * This driver करोes not by शेष support configuring this second GPO
 * but allows using it by providing the DT property
 * "rohm,enable-hidden-gpo".
 */
अटल पूर्णांक bd71815_init_valid_mask(काष्ठा gpio_chip *gc,
				   अचिन्हित दीर्घ *valid_mask,
				   अचिन्हित पूर्णांक ngpios)
अणु
	अगर (ngpios != 2)
		वापस 0;

	अगर (gc->parent && device_property_present(gc->parent,
						  "rohm,enable-hidden-gpo"))
		*valid_mask = BD71815_TWO_GPIOS;
	अन्यथा
		*valid_mask = BD71815_ONE_GPIO;

	वापस 0;
पूर्ण

अटल पूर्णांक gpo_bd71815_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd71815_gpio *g;
	काष्ठा device *parent, *dev;

	/*
	 * Bind devm lअगरeसमय to this platक्रमm device => use dev क्रम devm.
	 * also the prपूर्णांकs should originate from this device.
	 */
	dev = &pdev->dev;
	/* The device-tree and regmap come from MFD => use parent क्रम that */
	parent = dev->parent;

	g = devm_kzalloc(dev, माप(*g), GFP_KERNEL);
	अगर (!g)
		वापस -ENOMEM;

	g->chip = bd71815gpo_chip;

	/*
	 * FIXME: As writing of this the sysfs पूर्णांकerface क्रम GPIO control करोes
	 * not respect the valid_mask. Do not trust it but rather set the ngpios
	 * to 1 अगर "rohm,enable-hidden-gpo" is not given.
	 *
	 * This check can be हटाओd later अगर the sysfs export is fixed and
	 * अगर the fix is backported.
	 *
	 * For now it is safest to just set the ngpios though.
	 */
	अगर (device_property_present(parent, "rohm,enable-hidden-gpo"))
		g->chip.ngpio = 2;
	अन्यथा
		g->chip.ngpio = 1;

	g->chip.init_valid_mask = bd71815_init_valid_mask;
	g->chip.base = -1;
	g->chip.parent = parent;
	g->regmap = dev_get_regmap(parent, शून्य);
	g->dev = dev;

	वापस devm_gpiochip_add_data(dev, &g->chip, g);
पूर्ण

अटल काष्ठा platक्रमm_driver gpo_bd71815_driver = अणु
	.driver = अणु
		.name	= "bd71815-gpo",
	पूर्ण,
	.probe		= gpo_bd71815_probe,
पूर्ण;
module_platक्रमm_driver(gpo_bd71815_driver);

MODULE_ALIAS("platform:bd71815-gpo");
MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_AUTHOR("Peter Yang <yanglsh@embest-tech.com>");
MODULE_DESCRIPTION("GPO interface for BD71815");
MODULE_LICENSE("GPL");
