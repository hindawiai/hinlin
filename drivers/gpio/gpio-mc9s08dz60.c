<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2009-2012 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * Author: Wu Guoxing <b39297@मुक्तscale.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/driver.h>

#घोषणा GPIO_GROUP_NUM 2
#घोषणा GPIO_NUM_PER_GROUP 8
#घोषणा GPIO_NUM (GPIO_GROUP_NUM*GPIO_NUM_PER_GROUP)

काष्ठा mc9s08dz60 अणु
	काष्ठा i2c_client *client;
	काष्ठा gpio_chip chip;
पूर्ण;

अटल व्योम mc9s_gpio_to_reg_and_bit(पूर्णांक offset, u8 *reg, u8 *bit)
अणु
	*reg = 0x20 + offset / GPIO_NUM_PER_GROUP;
	*bit = offset % GPIO_NUM_PER_GROUP;
पूर्ण

अटल पूर्णांक mc9s08dz60_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	u8 reg, bit;
	s32 value;
	काष्ठा mc9s08dz60 *mc9s = gpiochip_get_data(gc);

	mc9s_gpio_to_reg_and_bit(offset, &reg, &bit);
	value = i2c_smbus_पढ़ो_byte_data(mc9s->client, reg);

	वापस (value >= 0) ? (value >> bit) & 0x1 : 0;
पूर्ण

अटल पूर्णांक mc9s08dz60_set(काष्ठा mc9s08dz60 *mc9s, अचिन्हित offset, पूर्णांक val)
अणु
	u8 reg, bit;
	s32 value;

	mc9s_gpio_to_reg_and_bit(offset, &reg, &bit);
	value = i2c_smbus_पढ़ो_byte_data(mc9s->client, reg);
	अगर (value >= 0) अणु
		अगर (val)
			value |= 1 << bit;
		अन्यथा
			value &= ~(1 << bit);

		वापस i2c_smbus_ग_लिखो_byte_data(mc9s->client, reg, value);
	पूर्ण अन्यथा
		वापस value;

पूर्ण


अटल व्योम mc9s08dz60_set_value(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा mc9s08dz60 *mc9s = gpiochip_get_data(gc);

	mc9s08dz60_set(mc9s, offset, val);
पूर्ण

अटल पूर्णांक mc9s08dz60_direction_output(काष्ठा gpio_chip *gc,
				       अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा mc9s08dz60 *mc9s = gpiochip_get_data(gc);

	वापस mc9s08dz60_set(mc9s, offset, val);
पूर्ण

अटल पूर्णांक mc9s08dz60_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mc9s08dz60 *mc9s;

	mc9s = devm_kzalloc(&client->dev, माप(*mc9s), GFP_KERNEL);
	अगर (!mc9s)
		वापस -ENOMEM;

	mc9s->chip.label = client->name;
	mc9s->chip.base = -1;
	mc9s->chip.parent = &client->dev;
	mc9s->chip.owner = THIS_MODULE;
	mc9s->chip.ngpio = GPIO_NUM;
	mc9s->chip.can_sleep = true;
	mc9s->chip.get = mc9s08dz60_get_value;
	mc9s->chip.set = mc9s08dz60_set_value;
	mc9s->chip.direction_output = mc9s08dz60_direction_output;
	mc9s->client = client;
	i2c_set_clientdata(client, mc9s);

	वापस devm_gpiochip_add_data(&client->dev, &mc9s->chip, mc9s);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mc9s08dz60_id[] = अणु
	अणु"mc9s08dz60", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver mc9s08dz60_i2c_driver = अणु
	.driver = अणु
		.name = "mc9s08dz60",
	पूर्ण,
	.probe = mc9s08dz60_probe,
	.id_table = mc9s08dz60_id,
पूर्ण;
builtin_i2c_driver(mc9s08dz60_i2c_driver);
