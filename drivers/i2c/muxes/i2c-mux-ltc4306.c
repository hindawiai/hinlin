<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linear Technology LTC4306 and LTC4305 I2C multiplexer/चयन
 *
 * Copyright (C) 2017 Analog Devices Inc.
 *
 * Based on: i2c-mux-pca954x.c
 *
 * Datasheet: http://cds.linear.com/करोcs/en/datasheet/4306.pdf
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा LTC4305_MAX_NCHANS 2
#घोषणा LTC4306_MAX_NCHANS 4

#घोषणा LTC_REG_STATUS	0x0
#घोषणा LTC_REG_CONFIG	0x1
#घोषणा LTC_REG_MODE	0x2
#घोषणा LTC_REG_SWITCH	0x3

#घोषणा LTC_DOWNSTREAM_ACCL_EN	BIT(6)
#घोषणा LTC_UPSTREAM_ACCL_EN	BIT(7)

#घोषणा LTC_GPIO_ALL_INPUT	0xC0
#घोषणा LTC_SWITCH_MASK		0xF0

क्रमागत ltc_type अणु
	ltc_4305,
	ltc_4306,
पूर्ण;

काष्ठा chip_desc अणु
	u8 nchans;
	u8 num_gpios;
पूर्ण;

काष्ठा ltc4306 अणु
	काष्ठा regmap *regmap;
	काष्ठा gpio_chip gpiochip;
	स्थिर काष्ठा chip_desc *chip;
पूर्ण;

अटल स्थिर काष्ठा chip_desc chips[] = अणु
	[ltc_4305] = अणु
		.nchans = LTC4305_MAX_NCHANS,
	पूर्ण,
	[ltc_4306] = अणु
		.nchans = LTC4306_MAX_NCHANS,
		.num_gpios = 2,
	पूर्ण,
पूर्ण;

अटल bool ltc4306_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == LTC_REG_CONFIG) ? true : false;
पूर्ण

अटल स्थिर काष्ठा regmap_config ltc4306_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LTC_REG_SWITCH,
	.अस्थिर_reg = ltc4306_is_अस्थिर_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक ltc4306_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ltc4306 *data = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, LTC_REG_CONFIG, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & BIT(1 - offset));
पूर्ण

अटल व्योम ltc4306_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	काष्ठा ltc4306 *data = gpiochip_get_data(chip);

	regmap_update_bits(data->regmap, LTC_REG_CONFIG, BIT(5 - offset),
			   value ? BIT(5 - offset) : 0);
पूर्ण

अटल पूर्णांक ltc4306_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ltc4306 *data = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, LTC_REG_MODE, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & BIT(7 - offset));
पूर्ण

अटल पूर्णांक ltc4306_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ltc4306 *data = gpiochip_get_data(chip);

	वापस regmap_update_bits(data->regmap, LTC_REG_MODE,
				  BIT(7 - offset), BIT(7 - offset));
पूर्ण

अटल पूर्णांक ltc4306_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा ltc4306 *data = gpiochip_get_data(chip);

	ltc4306_gpio_set(chip, offset, value);
	वापस regmap_update_bits(data->regmap, LTC_REG_MODE,
				  BIT(7 - offset), 0);
पूर्ण

अटल पूर्णांक ltc4306_gpio_set_config(काष्ठा gpio_chip *chip,
				   अचिन्हित पूर्णांक offset, अचिन्हित दीर्घ config)
अणु
	काष्ठा ltc4306 *data = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		val = 0;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		val = BIT(4 - offset);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस regmap_update_bits(data->regmap, LTC_REG_MODE,
				  BIT(4 - offset), val);
पूर्ण

अटल पूर्णांक ltc4306_gpio_init(काष्ठा ltc4306 *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);

	अगर (!data->chip->num_gpios)
		वापस 0;

	data->gpiochip.label = dev_name(dev);
	data->gpiochip.base = -1;
	data->gpiochip.ngpio = data->chip->num_gpios;
	data->gpiochip.parent = dev;
	data->gpiochip.can_sleep = true;
	data->gpiochip.get_direction = ltc4306_gpio_get_direction;
	data->gpiochip.direction_input = ltc4306_gpio_direction_input;
	data->gpiochip.direction_output = ltc4306_gpio_direction_output;
	data->gpiochip.get = ltc4306_gpio_get;
	data->gpiochip.set = ltc4306_gpio_set;
	data->gpiochip.set_config = ltc4306_gpio_set_config;
	data->gpiochip.owner = THIS_MODULE;

	/* gpiolib assumes all GPIOs शेष input */
	regmap_ग_लिखो(data->regmap, LTC_REG_MODE, LTC_GPIO_ALL_INPUT);

	वापस devm_gpiochip_add_data(dev, &data->gpiochip, data);
पूर्ण

अटल पूर्णांक ltc4306_select_mux(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा ltc4306 *data = i2c_mux_priv(muxc);

	वापस regmap_update_bits(data->regmap, LTC_REG_SWITCH,
				  LTC_SWITCH_MASK, BIT(7 - chan));
पूर्ण

अटल पूर्णांक ltc4306_deselect_mux(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा ltc4306 *data = i2c_mux_priv(muxc);

	वापस regmap_update_bits(data->regmap, LTC_REG_SWITCH,
				  LTC_SWITCH_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4306_id[] = अणु
	अणु "ltc4305", ltc_4305 पूर्ण,
	अणु "ltc4306", ltc_4306 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc4306_id);

अटल स्थिर काष्ठा of_device_id ltc4306_of_match[] = अणु
	अणु .compatible = "lltc,ltc4305", .data = &chips[ltc_4305] पूर्ण,
	अणु .compatible = "lltc,ltc4306", .data = &chips[ltc_4306] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc4306_of_match);

अटल पूर्णांक ltc4306_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	स्थिर काष्ठा chip_desc *chip;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा ltc4306 *data;
	काष्ठा gpio_desc *gpio;
	bool idle_disc;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक num, ret;

	chip = of_device_get_match_data(&client->dev);

	अगर (!chip)
		chip = &chips[i2c_match_id(ltc4306_id, client)->driver_data];

	idle_disc = device_property_पढ़ो_bool(&client->dev,
					      "i2c-mux-idle-disconnect");

	muxc = i2c_mux_alloc(adap, &client->dev,
			     chip->nchans, माप(*data),
			     I2C_MUX_LOCKED, ltc4306_select_mux,
			     idle_disc ? ltc4306_deselect_mux : शून्य);
	अगर (!muxc)
		वापस -ENOMEM;
	data = i2c_mux_priv(muxc);
	data->chip = chip;

	i2c_set_clientdata(client, muxc);

	data->regmap = devm_regmap_init_i2c(client, &ltc4306_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		ret = PTR_ERR(data->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* Reset and enable the mux अगर an enable GPIO is specअगरied. */
	gpio = devm_gpiod_get_optional(&client->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	अगर (gpio) अणु
		udelay(1);
		gpiod_set_value(gpio, 1);
	पूर्ण

	/*
	 * Write the mux रेजिस्टर at addr to verअगरy
	 * that the mux is in fact present. This also
	 * initializes the mux to disconnected state.
	 */
	अगर (regmap_ग_लिखो(data->regmap, LTC_REG_SWITCH, 0) < 0) अणु
		dev_warn(&client->dev, "probe failed\n");
		वापस -ENODEV;
	पूर्ण

	अगर (device_property_पढ़ो_bool(&client->dev,
				      "ltc,downstream-accelerators-enable"))
		val |= LTC_DOWNSTREAM_ACCL_EN;

	अगर (device_property_पढ़ो_bool(&client->dev,
				      "ltc,upstream-accelerators-enable"))
		val |= LTC_UPSTREAM_ACCL_EN;

	अगर (regmap_ग_लिखो(data->regmap, LTC_REG_CONFIG, val) < 0)
		वापस -ENODEV;

	ret = ltc4306_gpio_init(data);
	अगर (ret < 0)
		वापस ret;

	/* Now create an adapter क्रम each channel */
	क्रम (num = 0; num < chip->nchans; num++) अणु
		ret = i2c_mux_add_adapter(muxc, 0, num, 0);
		अगर (ret) अणु
			i2c_mux_del_adapters(muxc);
			वापस ret;
		पूर्ण
	पूर्ण

	dev_info(&client->dev,
		 "registered %d multiplexed busses for I2C switch %s\n",
		 num, client->name);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4306_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);

	i2c_mux_del_adapters(muxc);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver ltc4306_driver = अणु
	.driver		= अणु
		.name	= "ltc4306",
		.of_match_table = of_match_ptr(ltc4306_of_match),
	पूर्ण,
	.probe_new	= ltc4306_probe,
	.हटाओ		= ltc4306_हटाओ,
	.id_table	= ltc4306_id,
पूर्ण;

module_i2c_driver(ltc4306_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Linear Technology LTC4306, LTC4305 I2C mux/switch driver");
MODULE_LICENSE("GPL v2");
