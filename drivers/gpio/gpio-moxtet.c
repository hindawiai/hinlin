<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Turris Mox Moxtet GPIO expander
 *
 *  Copyright (C) 2018 Marek Behथजn <kabel@kernel.org>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/moxtet.h>
#समावेश <linux/module.h>

#घोषणा MOXTET_GPIO_NGPIOS	12
#घोषणा MOXTET_GPIO_INPUTS	4

काष्ठा moxtet_gpio_desc अणु
	u16 in_mask;
	u16 out_mask;
पूर्ण;

अटल स्थिर काष्ठा moxtet_gpio_desc descs[] = अणु
	[TURRIS_MOX_MODULE_SFP] = अणु
		.in_mask = GENMASK(2, 0),
		.out_mask = GENMASK(5, 4),
	पूर्ण,
पूर्ण;

काष्ठा moxtet_gpio_chip अणु
	काष्ठा device			*dev;
	काष्ठा gpio_chip		gpio_chip;
	स्थिर काष्ठा moxtet_gpio_desc	*desc;
पूर्ण;

अटल पूर्णांक moxtet_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा moxtet_gpio_chip *chip = gpiochip_get_data(gc);
	पूर्णांक ret;

	अगर (chip->desc->in_mask & BIT(offset)) अणु
		ret = moxtet_device_पढ़ो(chip->dev);
	पूर्ण अन्यथा अगर (chip->desc->out_mask & BIT(offset)) अणु
		ret = moxtet_device_written(chip->dev);
		अगर (ret >= 0)
			ret <<= MOXTET_GPIO_INPUTS;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & BIT(offset));
पूर्ण

अटल व्योम moxtet_gpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				  पूर्णांक val)
अणु
	काष्ठा moxtet_gpio_chip *chip = gpiochip_get_data(gc);
	पूर्णांक state;

	state = moxtet_device_written(chip->dev);
	अगर (state < 0)
		वापस;

	offset -= MOXTET_GPIO_INPUTS;

	अगर (val)
		state |= BIT(offset);
	अन्यथा
		state &= ~BIT(offset);

	moxtet_device_ग_लिखो(chip->dev, state);
पूर्ण

अटल पूर्णांक moxtet_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा moxtet_gpio_chip *chip = gpiochip_get_data(gc);

	/* All lines are hard wired to be either input or output, not both. */
	अगर (chip->desc->in_mask & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_IN;
	अन्यथा अगर (chip->desc->out_mask & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक moxtet_gpio_direction_input(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा moxtet_gpio_chip *chip = gpiochip_get_data(gc);

	अगर (chip->desc->in_mask & BIT(offset))
		वापस 0;
	अन्यथा अगर (chip->desc->out_mask & BIT(offset))
		वापस -ENOTSUPP;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक moxtet_gpio_direction_output(काष्ठा gpio_chip *gc,
					अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा moxtet_gpio_chip *chip = gpiochip_get_data(gc);

	अगर (chip->desc->out_mask & BIT(offset))
		moxtet_gpio_set_value(gc, offset, val);
	अन्यथा अगर (chip->desc->in_mask & BIT(offset))
		वापस -ENOTSUPP;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक moxtet_gpio_probe(काष्ठा device *dev)
अणु
	काष्ठा moxtet_gpio_chip *chip;
	काष्ठा device_node *nc = dev->of_node;
	पूर्णांक id;

	id = to_moxtet_device(dev)->id;

	अगर (id >= ARRAY_SIZE(descs)) अणु
		dev_err(dev, "%pOF Moxtet device id 0x%x is not supported by gpio-moxtet driver\n",
			nc, id);
		वापस -ENOTSUPP;
	पूर्ण

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = dev;
	chip->gpio_chip.parent = dev;
	chip->desc = &descs[id];

	dev_set_drvdata(dev, chip);

	chip->gpio_chip.label = dev_name(dev);
	chip->gpio_chip.get_direction = moxtet_gpio_get_direction;
	chip->gpio_chip.direction_input = moxtet_gpio_direction_input;
	chip->gpio_chip.direction_output = moxtet_gpio_direction_output;
	chip->gpio_chip.get = moxtet_gpio_get_value;
	chip->gpio_chip.set = moxtet_gpio_set_value;
	chip->gpio_chip.base = -1;

	chip->gpio_chip.ngpio = MOXTET_GPIO_NGPIOS;

	chip->gpio_chip.can_sleep = true;
	chip->gpio_chip.owner = THIS_MODULE;

	वापस devm_gpiochip_add_data(dev, &chip->gpio_chip, chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id moxtet_gpio_dt_ids[] = अणु
	अणु .compatible = "cznic,moxtet-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, moxtet_gpio_dt_ids);

अटल स्थिर क्रमागत turris_mox_module_id moxtet_gpio_module_table[] = अणु
	TURRIS_MOX_MODULE_SFP,
	0,
पूर्ण;

अटल काष्ठा moxtet_driver moxtet_gpio_driver = अणु
	.driver = अणु
		.name		= "moxtet-gpio",
		.of_match_table	= moxtet_gpio_dt_ids,
		.probe		= moxtet_gpio_probe,
	पूर्ण,
	.id_table = moxtet_gpio_module_table,
पूर्ण;
module_moxtet_driver(moxtet_gpio_driver);

MODULE_AUTHOR("Marek Behun <kabel@kernel.org>");
MODULE_DESCRIPTION("Turris Mox Moxtet GPIO expander");
MODULE_LICENSE("GPL v2");
