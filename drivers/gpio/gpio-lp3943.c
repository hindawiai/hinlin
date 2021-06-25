<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI/National Semiconductor LP3943 GPIO driver
 *
 * Copyright 2013 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/lp3943.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

क्रमागत lp3943_gpios अणु
	LP3943_GPIO1,
	LP3943_GPIO2,
	LP3943_GPIO3,
	LP3943_GPIO4,
	LP3943_GPIO5,
	LP3943_GPIO6,
	LP3943_GPIO7,
	LP3943_GPIO8,
	LP3943_GPIO9,
	LP3943_GPIO10,
	LP3943_GPIO11,
	LP3943_GPIO12,
	LP3943_GPIO13,
	LP3943_GPIO14,
	LP3943_GPIO15,
	LP3943_GPIO16,
	LP3943_MAX_GPIO,
पूर्ण;

काष्ठा lp3943_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा lp3943 *lp3943;
	u16 input_mask;		/* 1 = GPIO is input direction, 0 = output */
पूर्ण;

अटल पूर्णांक lp3943_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);
	काष्ठा lp3943 *lp3943 = lp3943_gpio->lp3943;

	/* Return an error अगर the pin is alपढ़ोy asचिन्हित */
	अगर (test_and_set_bit(offset, &lp3943->pin_used))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम lp3943_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);
	काष्ठा lp3943 *lp3943 = lp3943_gpio->lp3943;

	clear_bit(offset, &lp3943->pin_used);
पूर्ण

अटल पूर्णांक lp3943_gpio_set_mode(काष्ठा lp3943_gpio *lp3943_gpio, u8 offset,
				u8 val)
अणु
	काष्ठा lp3943 *lp3943 = lp3943_gpio->lp3943;
	स्थिर काष्ठा lp3943_reg_cfg *mux = lp3943->mux_cfg;

	वापस lp3943_update_bits(lp3943, mux[offset].reg, mux[offset].mask,
				  val << mux[offset].shअगरt);
पूर्ण

अटल पूर्णांक lp3943_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);

	lp3943_gpio->input_mask |= BIT(offset);

	वापस lp3943_gpio_set_mode(lp3943_gpio, offset, LP3943_GPIO_IN);
पूर्ण

अटल पूर्णांक lp3943_get_gpio_in_status(काष्ठा lp3943_gpio *lp3943_gpio,
				     काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	u8 addr, पढ़ो;
	पूर्णांक err;

	चयन (offset) अणु
	हाल LP3943_GPIO1 ... LP3943_GPIO8:
		addr = LP3943_REG_GPIO_A;
		अवरोध;
	हाल LP3943_GPIO9 ... LP3943_GPIO16:
		addr = LP3943_REG_GPIO_B;
		offset = offset - 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = lp3943_पढ़ो_byte(lp3943_gpio->lp3943, addr, &पढ़ो);
	अगर (err)
		वापस err;

	वापस !!(पढ़ो & BIT(offset));
पूर्ण

अटल पूर्णांक lp3943_get_gpio_out_status(काष्ठा lp3943_gpio *lp3943_gpio,
				      काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा lp3943 *lp3943 = lp3943_gpio->lp3943;
	स्थिर काष्ठा lp3943_reg_cfg *mux = lp3943->mux_cfg;
	u8 पढ़ो;
	पूर्णांक err;

	err = lp3943_पढ़ो_byte(lp3943, mux[offset].reg, &पढ़ो);
	अगर (err)
		वापस err;

	पढ़ो = (पढ़ो & mux[offset].mask) >> mux[offset].shअगरt;

	अगर (पढ़ो == LP3943_GPIO_OUT_HIGH)
		वापस 1;
	अन्यथा अगर (पढ़ो == LP3943_GPIO_OUT_LOW)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक lp3943_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);

	/*
	 * Limitation:
	 *   LP3943 करोesn't have the GPIO direction रेजिस्टर. It provides
	 *   only input and output status रेजिस्टरs.
	 *   So, direction info is required to handle the 'get' operation.
	 *   This variable is updated whenever the direction is changed and
	 *   it is used here.
	 */

	अगर (lp3943_gpio->input_mask & BIT(offset))
		वापस lp3943_get_gpio_in_status(lp3943_gpio, chip, offset);
	अन्यथा
		वापस lp3943_get_gpio_out_status(lp3943_gpio, chip, offset);
पूर्ण

अटल व्योम lp3943_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);
	u8 data;

	अगर (value)
		data = LP3943_GPIO_OUT_HIGH;
	अन्यथा
		data = LP3943_GPIO_OUT_LOW;

	lp3943_gpio_set_mode(lp3943_gpio, offset, data);
पूर्ण

अटल पूर्णांक lp3943_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
					पूर्णांक value)
अणु
	काष्ठा lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);

	lp3943_gpio_set(chip, offset, value);
	lp3943_gpio->input_mask &= ~BIT(offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gpio_chip lp3943_gpio_chip = अणु
	.label			= "lp3943",
	.owner			= THIS_MODULE,
	.request		= lp3943_gpio_request,
	.मुक्त			= lp3943_gpio_मुक्त,
	.direction_input	= lp3943_gpio_direction_input,
	.get			= lp3943_gpio_get,
	.direction_output	= lp3943_gpio_direction_output,
	.set			= lp3943_gpio_set,
	.base			= -1,
	.ngpio			= LP3943_MAX_GPIO,
	.can_sleep		= 1,
पूर्ण;

अटल पूर्णांक lp3943_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp3943 *lp3943 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lp3943_gpio *lp3943_gpio;

	lp3943_gpio = devm_kzalloc(&pdev->dev, माप(*lp3943_gpio),
				GFP_KERNEL);
	अगर (!lp3943_gpio)
		वापस -ENOMEM;

	lp3943_gpio->lp3943 = lp3943;
	lp3943_gpio->chip = lp3943_gpio_chip;
	lp3943_gpio->chip.parent = &pdev->dev;

	platक्रमm_set_drvdata(pdev, lp3943_gpio);

	वापस devm_gpiochip_add_data(&pdev->dev, &lp3943_gpio->chip,
				      lp3943_gpio);
पूर्ण

अटल स्थिर काष्ठा of_device_id lp3943_gpio_of_match[] = अणु
	अणु .compatible = "ti,lp3943-gpio", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lp3943_gpio_of_match);

अटल काष्ठा platक्रमm_driver lp3943_gpio_driver = अणु
	.probe = lp3943_gpio_probe,
	.driver = अणु
		.name = "lp3943-gpio",
		.of_match_table = lp3943_gpio_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp3943_gpio_driver);

MODULE_DESCRIPTION("LP3943 GPIO driver");
MODULE_ALIAS("platform:lp3943-gpio");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
