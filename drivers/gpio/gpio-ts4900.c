<शैली गुरु>
/*
 * Digital I/O driver क्रम Technologic Systems I2C FPGA Core
 *
 * Copyright (C) 2015 Technologic Systems
 * Copyright (C) 2016 Savoir-Faire Linux
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#घोषणा DEFAULT_PIN_NUMBER	32
/*
 * Register bits used by the GPIO device
 * Some boards, such as TS-7970 करो not have a separate input bit
 */
#घोषणा TS4900_GPIO_OE		0x01
#घोषणा TS4900_GPIO_OUT		0x02
#घोषणा TS4900_GPIO_IN		0x04
#घोषणा TS7970_GPIO_IN		0x02

काष्ठा ts4900_gpio_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा gpio_chip gpio_chip;
	अचिन्हित पूर्णांक input_bit;
पूर्ण;

अटल पूर्णांक ts4900_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ts4900_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(priv->regmap, offset, &reg);

	अगर (reg & TS4900_GPIO_OE)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक ts4900_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ts4900_gpio_priv *priv = gpiochip_get_data(chip);

	/*
	 * This will clear the output enable bit, the other bits are
	 * करोntcare when this is cleared
	 */
	वापस regmap_ग_लिखो(priv->regmap, offset, 0);
पूर्ण

अटल पूर्णांक ts4900_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा ts4900_gpio_priv *priv = gpiochip_get_data(chip);
	पूर्णांक ret;

	अगर (value)
		ret = regmap_ग_लिखो(priv->regmap, offset, TS4900_GPIO_OE |
							 TS4900_GPIO_OUT);
	अन्यथा
		ret = regmap_ग_लिखो(priv->regmap, offset, TS4900_GPIO_OE);

	वापस ret;
पूर्ण

अटल पूर्णांक ts4900_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ts4900_gpio_priv *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(priv->regmap, offset, &reg);

	वापस !!(reg & priv->input_bit);
पूर्ण

अटल व्योम ts4900_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा ts4900_gpio_priv *priv = gpiochip_get_data(chip);

	अगर (value)
		regmap_update_bits(priv->regmap, offset, TS4900_GPIO_OUT,
				   TS4900_GPIO_OUT);
	अन्यथा
		regmap_update_bits(priv->regmap, offset, TS4900_GPIO_OUT, 0);
पूर्ण

अटल स्थिर काष्ठा regmap_config ts4900_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "ts4900-gpio",
	.owner			= THIS_MODULE,
	.get_direction		= ts4900_gpio_get_direction,
	.direction_input	= ts4900_gpio_direction_input,
	.direction_output	= ts4900_gpio_direction_output,
	.get			= ts4900_gpio_get,
	.set			= ts4900_gpio_set,
	.base			= -1,
	.can_sleep		= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ts4900_gpio_of_match_table[] = अणु
	अणु
		.compatible = "technologic,ts4900-gpio",
		.data = (व्योम *)TS4900_GPIO_IN,
	पूर्ण, अणु
		.compatible = "technologic,ts7970-gpio",
		.data = (व्योम *)TS7970_GPIO_IN,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ts4900_gpio_of_match_table);

अटल पूर्णांक ts4900_gpio_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ts4900_gpio_priv *priv;
	u32 ngpio;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(client->dev.of_node, "ngpios", &ngpio))
		ngpio = DEFAULT_PIN_NUMBER;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->gpio_chip = ढाँचा_chip;
	priv->gpio_chip.label = "ts4900-gpio";
	priv->gpio_chip.ngpio = ngpio;
	priv->gpio_chip.parent = &client->dev;
	priv->input_bit = (uपूर्णांकptr_t)of_device_get_match_data(&client->dev);

	priv->regmap = devm_regmap_init_i2c(client, &ts4900_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_gpiochip_add_data(&client->dev, &priv->gpio_chip, priv);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to register gpiochip\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ts4900_gpio_id_table[] = अणु
	अणु "ts4900-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ts4900_gpio_id_table);

अटल काष्ठा i2c_driver ts4900_gpio_driver = अणु
	.driver = अणु
		.name = "ts4900-gpio",
		.of_match_table = ts4900_gpio_of_match_table,
	पूर्ण,
	.probe = ts4900_gpio_probe,
	.id_table = ts4900_gpio_id_table,
पूर्ण;
module_i2c_driver(ts4900_gpio_driver);

MODULE_AUTHOR("Technologic Systems");
MODULE_DESCRIPTION("GPIO interface for Technologic Systems I2C-FPGA core");
MODULE_LICENSE("GPL");
