<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019, Linaro Limited

#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>

#घोषणा WCD_PIN_MASK(p) BIT(p)
#घोषणा WCD_REG_सूची_CTL_OFFSET 0x42
#घोषणा WCD_REG_VAL_CTL_OFFSET 0x43
#घोषणा WCD934X_NPINS		5

काष्ठा wcd_gpio_data अणु
	काष्ठा regmap *map;
	काष्ठा gpio_chip chip;
पूर्ण;

अटल पूर्णांक wcd_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा wcd_gpio_data *data = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->map, WCD_REG_सूची_CTL_OFFSET, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (value & WCD_PIN_MASK(pin))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक wcd_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा wcd_gpio_data *data = gpiochip_get_data(chip);

	वापस regmap_update_bits(data->map, WCD_REG_सूची_CTL_OFFSET,
				  WCD_PIN_MASK(pin), 0);
पूर्ण

अटल पूर्णांक wcd_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
				     पूर्णांक val)
अणु
	काष्ठा wcd_gpio_data *data = gpiochip_get_data(chip);

	regmap_update_bits(data->map, WCD_REG_सूची_CTL_OFFSET,
			   WCD_PIN_MASK(pin), WCD_PIN_MASK(pin));

	वापस regmap_update_bits(data->map, WCD_REG_VAL_CTL_OFFSET,
				  WCD_PIN_MASK(pin),
				  val ? WCD_PIN_MASK(pin) : 0);
पूर्ण

अटल पूर्णांक wcd_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा wcd_gpio_data *data = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक value;

	regmap_पढ़ो(data->map, WCD_REG_VAL_CTL_OFFSET, &value);

	वापस !!(value & WCD_PIN_MASK(pin));
पूर्ण

अटल व्योम wcd_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin, पूर्णांक val)
अणु
	काष्ठा wcd_gpio_data *data = gpiochip_get_data(chip);

	regmap_update_bits(data->map, WCD_REG_VAL_CTL_OFFSET,
			   WCD_PIN_MASK(pin), val ? WCD_PIN_MASK(pin) : 0);
पूर्ण

अटल पूर्णांक wcd_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wcd_gpio_data *data;
	काष्ठा gpio_chip *chip;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->map = dev_get_regmap(dev->parent, शून्य);
	अगर (!data->map) अणु
		dev_err(dev, "%s: failed to get regmap\n", __func__);
		वापस  -EINVAL;
	पूर्ण

	chip = &data->chip;
	chip->direction_input  = wcd_gpio_direction_input;
	chip->direction_output = wcd_gpio_direction_output;
	chip->get_direction = wcd_gpio_get_direction;
	chip->get = wcd_gpio_get;
	chip->set = wcd_gpio_set;
	chip->parent = dev;
	chip->base = -1;
	chip->ngpio = WCD934X_NPINS;
	chip->label = dev_name(dev);
	chip->of_gpio_n_cells = 2;
	chip->can_sleep = false;

	वापस devm_gpiochip_add_data(dev, chip, data);
पूर्ण

अटल स्थिर काष्ठा of_device_id wcd_gpio_of_match[] = अणु
	अणु .compatible = "qcom,wcd9340-gpio" पूर्ण,
	अणु .compatible = "qcom,wcd9341-gpio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wcd_gpio_of_match);

अटल काष्ठा platक्रमm_driver wcd_gpio_driver = अणु
	.driver = अणु
		   .name = "wcd934x-gpio",
		   .of_match_table = wcd_gpio_of_match,
	पूर्ण,
	.probe = wcd_gpio_probe,
पूर्ण;

module_platक्रमm_driver(wcd_gpio_driver);
MODULE_DESCRIPTION("Qualcomm Technologies, Inc WCD GPIO control driver");
MODULE_LICENSE("GPL v2");
