<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014 Belkin Inc.
 * Copyright 2015 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा TLC591XX_MAX_LEDS	16
#घोषणा TLC591XX_MAX_BRIGHTNESS	256

#घोषणा TLC591XX_REG_MODE1	0x00
#घोषणा MODE1_RESPON_ADDR_MASK	0xF0
#घोषणा MODE1_NORMAL_MODE	(0 << 4)
#घोषणा MODE1_SPEED_MODE	(1 << 4)

#घोषणा TLC591XX_REG_MODE2	0x01
#घोषणा MODE2_DIM		(0 << 5)
#घोषणा MODE2_BLINK		(1 << 5)
#घोषणा MODE2_OCH_STOP		(0 << 3)
#घोषणा MODE2_OCH_ACK		(1 << 3)

#घोषणा TLC591XX_REG_PWM(x)	(0x02 + (x))

#घोषणा TLC591XX_REG_GRPPWM	0x12
#घोषणा TLC591XX_REG_GRPFREQ	0x13

/* LED Driver Output State, determine the source that drives LED outमाला_दो */
#घोषणा LEDOUT_OFF		0x0	/* Output LOW */
#घोषणा LEDOUT_ON		0x1	/* Output HI-Z */
#घोषणा LEDOUT_DIM		0x2	/* Dimming */
#घोषणा LEDOUT_BLINK		0x3	/* Blinking */
#घोषणा LEDOUT_MASK		0x3

#घोषणा ldev_to_led(c)		container_of(c, काष्ठा tlc591xx_led, ldev)

काष्ठा tlc591xx_led अणु
	bool active;
	अचिन्हित पूर्णांक led_no;
	काष्ठा led_classdev ldev;
	काष्ठा tlc591xx_priv *priv;
पूर्ण;

काष्ठा tlc591xx_priv अणु
	काष्ठा tlc591xx_led leds[TLC591XX_MAX_LEDS];
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक reg_leकरोut_offset;
पूर्ण;

काष्ठा tlc591xx अणु
	अचिन्हित पूर्णांक max_leds;
	अचिन्हित पूर्णांक reg_leकरोut_offset;
पूर्ण;

अटल स्थिर काष्ठा tlc591xx tlc59116 = अणु
	.max_leds = 16,
	.reg_leकरोut_offset = 0x14,
पूर्ण;

अटल स्थिर काष्ठा tlc591xx tlc59108 = अणु
	.max_leds = 8,
	.reg_leकरोut_offset = 0x0c,
पूर्ण;

अटल पूर्णांक
tlc591xx_set_mode(काष्ठा regmap *regmap, u8 mode)
अणु
	पूर्णांक err;
	u8 val;

	err = regmap_ग_लिखो(regmap, TLC591XX_REG_MODE1, MODE1_NORMAL_MODE);
	अगर (err)
		वापस err;

	val = MODE2_OCH_STOP | mode;

	वापस regmap_ग_लिखो(regmap, TLC591XX_REG_MODE2, val);
पूर्ण

अटल पूर्णांक
tlc591xx_set_leकरोut(काष्ठा tlc591xx_priv *priv, काष्ठा tlc591xx_led *led,
		    u8 val)
अणु
	अचिन्हित पूर्णांक i = (led->led_no % 4) * 2;
	अचिन्हित पूर्णांक mask = LEDOUT_MASK << i;
	अचिन्हित पूर्णांक addr = priv->reg_leकरोut_offset + (led->led_no >> 2);

	val = val << i;

	वापस regmap_update_bits(priv->regmap, addr, mask, val);
पूर्ण

अटल पूर्णांक
tlc591xx_set_pwm(काष्ठा tlc591xx_priv *priv, काष्ठा tlc591xx_led *led,
		 u8 brightness)
अणु
	u8 pwm = TLC591XX_REG_PWM(led->led_no);

	वापस regmap_ग_लिखो(priv->regmap, pwm, brightness);
पूर्ण

अटल पूर्णांक
tlc591xx_brightness_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness brightness)
अणु
	काष्ठा tlc591xx_led *led = ldev_to_led(led_cdev);
	काष्ठा tlc591xx_priv *priv = led->priv;
	पूर्णांक err;

	चयन ((पूर्णांक)brightness) अणु
	हाल 0:
		err = tlc591xx_set_leकरोut(priv, led, LEDOUT_OFF);
		अवरोध;
	हाल TLC591XX_MAX_BRIGHTNESS:
		err = tlc591xx_set_leकरोut(priv, led, LEDOUT_ON);
		अवरोध;
	शेष:
		err = tlc591xx_set_leकरोut(priv, led, LEDOUT_DIM);
		अगर (!err)
			err = tlc591xx_set_pwm(priv, led, brightness);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा regmap_config tlc591xx_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x1e,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_tlc591xx_leds_match[] = अणु
	अणु .compatible = "ti,tlc59116",
	  .data = &tlc59116 पूर्ण,
	अणु .compatible = "ti,tlc59108",
	  .data = &tlc59108 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_tlc591xx_leds_match);

अटल पूर्णांक
tlc591xx_probe(काष्ठा i2c_client *client,
	       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = dev_of_node(&client->dev), *child;
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा tlc591xx *tlc591xx;
	काष्ठा tlc591xx_priv *priv;
	पूर्णांक err, count, reg;

	tlc591xx = device_get_match_data(dev);
	अगर (!np)
		वापस -ENODEV;

	count = of_get_available_child_count(np);
	अगर (!count || count > tlc591xx->max_leds)
		वापस -EINVAL;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init_i2c(client, &tlc591xx_regmap);
	अगर (IS_ERR(priv->regmap)) अणु
		err = PTR_ERR(priv->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", err);
		वापस err;
	पूर्ण
	priv->reg_leकरोut_offset = tlc591xx->reg_leकरोut_offset;

	i2c_set_clientdata(client, priv);

	err = tlc591xx_set_mode(priv->regmap, MODE2_DIM);
	अगर (err < 0)
		वापस err;

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा tlc591xx_led *led;
		काष्ठा led_init_data init_data = अणुपूर्ण;

		init_data.fwnode = of_fwnode_handle(child);

		err = of_property_पढ़ो_u32(child, "reg", &reg);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
		अगर (reg < 0 || reg >= tlc591xx->max_leds ||
		    priv->leds[reg].active) अणु
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण
		led = &priv->leds[reg];

		led->active = true;
		led->priv = priv;
		led->led_no = reg;
		led->ldev.brightness_set_blocking = tlc591xx_brightness_set;
		led->ldev.max_brightness = TLC591XX_MAX_BRIGHTNESS;
		err = devm_led_classdev_रेजिस्टर_ext(dev, &led->ldev,
						     &init_data);
		अगर (err < 0) अणु
			of_node_put(child);
			वापस dev_err_probe(dev, err,
					     "couldn't register LED %s\n",
					     led->ldev.name);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tlc591xx_id[] = अणु
	अणु "tlc59116" पूर्ण,
	अणु "tlc59108" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tlc591xx_id);

अटल काष्ठा i2c_driver tlc591xx_driver = अणु
	.driver = अणु
		.name = "tlc591xx",
		.of_match_table = of_match_ptr(of_tlc591xx_leds_match),
	पूर्ण,
	.probe = tlc591xx_probe,
	.id_table = tlc591xx_id,
पूर्ण;

module_i2c_driver(tlc591xx_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TLC591XX LED driver");
