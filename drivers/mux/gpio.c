<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO-controlled multiplexer driver
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

काष्ठा mux_gpio अणु
	काष्ठा gpio_descs *gpios;
पूर्ण;

अटल पूर्णांक mux_gpio_set(काष्ठा mux_control *mux, पूर्णांक state)
अणु
	काष्ठा mux_gpio *mux_gpio = mux_chip_priv(mux->chip);
	DECLARE_BITMAP(values, BITS_PER_TYPE(state));
	u32 value = state;

	biपंचांगap_from_arr32(values, &value, BITS_PER_TYPE(value));

	gpiod_set_array_value_cansleep(mux_gpio->gpios->ndescs,
				       mux_gpio->gpios->desc,
				       mux_gpio->gpios->info, values);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mux_control_ops mux_gpio_ops = अणु
	.set = mux_gpio_set,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mux_gpio_dt_ids[] = अणु
	अणु .compatible = "gpio-mux", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mux_gpio_dt_ids);

अटल पूर्णांक mux_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mux_chip *mux_chip;
	काष्ठा mux_gpio *mux_gpio;
	पूर्णांक pins;
	s32 idle_state;
	पूर्णांक ret;

	pins = gpiod_count(dev, "mux");
	अगर (pins < 0)
		वापस pins;

	mux_chip = devm_mux_chip_alloc(dev, 1, माप(*mux_gpio));
	अगर (IS_ERR(mux_chip))
		वापस PTR_ERR(mux_chip);

	mux_gpio = mux_chip_priv(mux_chip);
	mux_chip->ops = &mux_gpio_ops;

	mux_gpio->gpios = devm_gpiod_get_array(dev, "mux", GPIOD_OUT_LOW);
	अगर (IS_ERR(mux_gpio->gpios))
		वापस dev_err_probe(dev, PTR_ERR(mux_gpio->gpios),
				     "failed to get gpios\n");
	WARN_ON(pins != mux_gpio->gpios->ndescs);
	mux_chip->mux->states = BIT(pins);

	ret = device_property_पढ़ो_u32(dev, "idle-state", (u32 *)&idle_state);
	अगर (ret >= 0 && idle_state != MUX_IDLE_AS_IS) अणु
		अगर (idle_state < 0 || idle_state >= mux_chip->mux->states) अणु
			dev_err(dev, "invalid idle-state %u\n", idle_state);
			वापस -EINVAL;
		पूर्ण

		mux_chip->mux->idle_state = idle_state;
	पूर्ण

	ret = devm_mux_chip_रेजिस्टर(dev, mux_chip);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "%u-way mux-controller registered\n",
		 mux_chip->mux->states);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mux_gpio_driver = अणु
	.driver = अणु
		.name = "gpio-mux",
		.of_match_table	= mux_gpio_dt_ids,
	पूर्ण,
	.probe = mux_gpio_probe,
पूर्ण;
module_platक्रमm_driver(mux_gpio_driver);

MODULE_DESCRIPTION("GPIO-controlled multiplexer driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
