<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <media/v4l2-flash-led-class.h>

#घोषणा RT4505_REG_RESET	0x0
#घोषणा RT4505_REG_CONFIG	0x8
#घोषणा RT4505_REG_ILED		0x9
#घोषणा RT4505_REG_ENABLE	0xA
#घोषणा RT4505_REG_FLAGS	0xB

#घोषणा RT4505_RESET_MASK	BIT(7)
#घोषणा RT4505_FLASHTO_MASK	GENMASK(2, 0)
#घोषणा RT4505_ITORCH_MASK	GENMASK(7, 5)
#घोषणा RT4505_ITORCH_SHIFT	5
#घोषणा RT4505_IFLASH_MASK	GENMASK(4, 0)
#घोषणा RT4505_ENABLE_MASK	GENMASK(5, 0)
#घोषणा RT4505_TORCH_SET	(BIT(0) | BIT(4))
#घोषणा RT4505_FLASH_SET	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#घोषणा RT4505_EXT_FLASH_SET	(BIT(0) | BIT(1) | BIT(4) | BIT(5))
#घोषणा RT4505_FLASH_GET	(BIT(0) | BIT(1) | BIT(4))
#घोषणा RT4505_OVP_MASK		BIT(3)
#घोषणा RT4505_SHORT_MASK	BIT(2)
#घोषणा RT4505_OTP_MASK		BIT(1)
#घोषणा RT4505_TIMEOUT_MASK	BIT(0)

#घोषणा RT4505_ITORCH_MINUA	46000
#घोषणा RT4505_ITORCH_MAXUA	375000
#घोषणा RT4505_ITORCH_STPUA	47000
#घोषणा RT4505_IFLASH_MINUA	93750
#घोषणा RT4505_IFLASH_MAXUA	1500000
#घोषणा RT4505_IFLASH_STPUA	93750
#घोषणा RT4505_FLASHTO_MINUS	100000
#घोषणा RT4505_FLASHTO_MAXUS	800000
#घोषणा RT4505_FLASHTO_STPUS	100000

काष्ठा rt4505_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;
	काष्ठा led_classdev_flash flash;
	काष्ठा v4l2_flash *v4l2_flash;
पूर्ण;

अटल पूर्णांक rt4505_torch_brightness_set(काष्ठा led_classdev *lcdev,
				       क्रमागत led_brightness level)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(lcdev, काष्ठा rt4505_priv, flash.led_cdev);
	u32 val = 0;
	पूर्णांक ret;

	mutex_lock(&priv->lock);

	अगर (level != LED_OFF) अणु
		ret = regmap_update_bits(priv->regmap,
					 RT4505_REG_ILED, RT4505_ITORCH_MASK,
					 (level - 1) << RT4505_ITORCH_SHIFT);
		अगर (ret)
			जाओ unlock;

		val = RT4505_TORCH_SET;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, RT4505_REG_ENABLE,
				 RT4505_ENABLE_MASK, val);

unlock:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल क्रमागत led_brightness rt4505_torch_brightness_get(
						काष्ठा led_classdev *lcdev)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(lcdev, काष्ठा rt4505_priv, flash.led_cdev);
	u32 val;
	पूर्णांक ret;

	mutex_lock(&priv->lock);

	ret = regmap_पढ़ो(priv->regmap, RT4505_REG_ENABLE, &val);
	अगर (ret) अणु
		dev_err(lcdev->dev, "Failed to get LED enable\n");
		ret = LED_OFF;
		जाओ unlock;
	पूर्ण

	अगर ((val & RT4505_ENABLE_MASK) != RT4505_TORCH_SET) अणु
		ret = LED_OFF;
		जाओ unlock;
	पूर्ण

	ret = regmap_पढ़ो(priv->regmap, RT4505_REG_ILED, &val);
	अगर (ret) अणु
		dev_err(lcdev->dev, "Failed to get LED brightness\n");
		ret = LED_OFF;
		जाओ unlock;
	पूर्ण

	ret = ((val & RT4505_ITORCH_MASK) >> RT4505_ITORCH_SHIFT) + 1;

unlock:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rt4505_flash_brightness_set(काष्ठा led_classdev_flash *fled_cdev,
				       u32 brightness)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(fled_cdev, काष्ठा rt4505_priv, flash);
	काष्ठा led_flash_setting *s = &fled_cdev->brightness;
	u32 val = (brightness - s->min) / s->step;
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = regmap_update_bits(priv->regmap, RT4505_REG_ILED,
				 RT4505_IFLASH_MASK, val);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rt4505_flash_strobe_set(काष्ठा led_classdev_flash *fled_cdev,
				   bool state)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(fled_cdev, काष्ठा rt4505_priv, flash);
	u32 val = state ? RT4505_FLASH_SET : 0;
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = regmap_update_bits(priv->regmap, RT4505_REG_ENABLE,
				 RT4505_ENABLE_MASK, val);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rt4505_flash_strobe_get(काष्ठा led_classdev_flash *fled_cdev,
				   bool *state)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(fled_cdev, काष्ठा rt4505_priv, flash);
	u32 val;
	पूर्णांक ret;

	mutex_lock(&priv->lock);

	ret = regmap_पढ़ो(priv->regmap, RT4505_REG_ENABLE, &val);
	अगर (ret)
		जाओ unlock;

	*state = (val & RT4505_FLASH_GET) == RT4505_FLASH_GET;

unlock:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rt4505_flash_समयout_set(काष्ठा led_classdev_flash *fled_cdev,
				    u32 समयout)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(fled_cdev, काष्ठा rt4505_priv, flash);
	काष्ठा led_flash_setting *s = &fled_cdev->समयout;
	u32 val = (समयout - s->min) / s->step;
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = regmap_update_bits(priv->regmap, RT4505_REG_CONFIG,
				 RT4505_FLASHTO_MASK, val);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rt4505_fault_get(काष्ठा led_classdev_flash *fled_cdev, u32 *fault)
अणु
	काष्ठा rt4505_priv *priv =
		container_of(fled_cdev, काष्ठा rt4505_priv, flash);
	u32 val, led_faults = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, RT4505_REG_FLAGS, &val);
	अगर (ret)
		वापस ret;

	अगर (val & RT4505_OVP_MASK)
		led_faults |= LED_FAULT_OVER_VOLTAGE;

	अगर (val & RT4505_SHORT_MASK)
		led_faults |= LED_FAULT_SHORT_CIRCUIT;

	अगर (val & RT4505_OTP_MASK)
		led_faults |= LED_FAULT_OVER_TEMPERATURE;

	अगर (val & RT4505_TIMEOUT_MASK)
		led_faults |= LED_FAULT_TIMEOUT;

	*fault = led_faults;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops rt4505_flash_ops = अणु
	.flash_brightness_set = rt4505_flash_brightness_set,
	.strobe_set = rt4505_flash_strobe_set,
	.strobe_get = rt4505_flash_strobe_get,
	.समयout_set = rt4505_flash_समयout_set,
	.fault_get = rt4505_fault_get,
पूर्ण;

अटल bool rt4505_is_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == RT4505_REG_RESET ||
		(reg >= RT4505_REG_CONFIG && reg <= RT4505_REG_FLAGS))
		वापस true;
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config rt4505_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RT4505_REG_FLAGS,

	.पढ़ोable_reg = rt4505_is_accessible_reg,
	.ग_लिखोable_reg = rt4505_is_accessible_reg,
पूर्ण;

#अगर IS_ENABLED(CONFIG_V4L2_FLASH_LED_CLASS)
अटल पूर्णांक rt4505_flash_बाह्यal_strobe_set(काष्ठा v4l2_flash *v4l2_flash,
					    bool enable)
अणु
	काष्ठा led_classdev_flash *flash = v4l2_flash->fled_cdev;
	काष्ठा rt4505_priv *priv =
		container_of(flash, काष्ठा rt4505_priv, flash);
	u32 val = enable ? RT4505_EXT_FLASH_SET : 0;
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = regmap_update_bits(priv->regmap, RT4505_REG_ENABLE,
				 RT4505_ENABLE_MASK, val);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops = अणु
	.बाह्यal_strobe_set = rt4505_flash_बाह्यal_strobe_set,
पूर्ण;

अटल व्योम rt4505_init_v4l2_config(काष्ठा rt4505_priv *priv,
				    काष्ठा v4l2_flash_config *config)
अणु
	काष्ठा led_classdev_flash *flash = &priv->flash;
	काष्ठा led_classdev *lcdev = &flash->led_cdev;
	काष्ठा led_flash_setting *s;

	strscpy(config->dev_name, lcdev->dev->kobj.name,
		माप(config->dev_name));

	s = &config->पूर्णांकensity;
	s->min = RT4505_ITORCH_MINUA;
	s->step = RT4505_ITORCH_STPUA;
	s->max = s->val = s->min + (lcdev->max_brightness - 1) * s->step;

	config->flash_faults = LED_FAULT_OVER_VOLTAGE |
			       LED_FAULT_SHORT_CIRCUIT |
			       LED_FAULT_LED_OVER_TEMPERATURE |
			       LED_FAULT_TIMEOUT;
	config->has_बाह्यal_strobe = 1;
पूर्ण
#अन्यथा
अटल स्थिर काष्ठा v4l2_flash_ops v4l2_flash_ops;
अटल व्योम rt4505_init_v4l2_config(काष्ठा rt4505_priv *priv,
				    काष्ठा v4l2_flash_config *config)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम rt4505_init_flash_properties(काष्ठा rt4505_priv *priv,
					 काष्ठा fwnode_handle *child)
अणु
	काष्ठा led_classdev_flash *flash = &priv->flash;
	काष्ठा led_classdev *lcdev = &flash->led_cdev;
	काष्ठा led_flash_setting *s;
	u32 val;
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u32(child, "led-max-microamp", &val);
	अगर (ret) अणु
		dev_warn(priv->dev, "led-max-microamp DT property missing\n");
		val = RT4505_ITORCH_MINUA;
	पूर्ण अन्यथा
		val = clamp_val(val, RT4505_ITORCH_MINUA, RT4505_ITORCH_MAXUA);

	lcdev->max_brightness =
		(val - RT4505_ITORCH_MINUA) / RT4505_ITORCH_STPUA + 1;
	lcdev->brightness_set_blocking = rt4505_torch_brightness_set;
	lcdev->brightness_get = rt4505_torch_brightness_get;
	lcdev->flags |= LED_DEV_CAP_FLASH;

	ret = fwnode_property_पढ़ो_u32(child, "flash-max-microamp", &val);
	अगर (ret) अणु
		dev_warn(priv->dev, "flash-max-microamp DT property missing\n");
		val = RT4505_IFLASH_MINUA;
	पूर्ण अन्यथा
		val = clamp_val(val, RT4505_IFLASH_MINUA, RT4505_IFLASH_MAXUA);

	s = &flash->brightness;
	s->min = RT4505_IFLASH_MINUA;
	s->step = RT4505_IFLASH_STPUA;
	s->max = s->val = val;

	ret = fwnode_property_पढ़ो_u32(child, "flash-max-timeout-us", &val);
	अगर (ret) अणु
		dev_warn(priv->dev,
			 "flash-max-timeout-us DT property missing\n");
		val = RT4505_FLASHTO_MINUS;
	पूर्ण अन्यथा
		val = clamp_val(val, RT4505_FLASHTO_MINUS,
				RT4505_FLASHTO_MAXUS);

	s = &flash->समयout;
	s->min = RT4505_FLASHTO_MINUS;
	s->step = RT4505_FLASHTO_STPUS;
	s->max = s->val = val;

	flash->ops = &rt4505_flash_ops;
पूर्ण

अटल पूर्णांक rt4505_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा rt4505_priv *priv;
	काष्ठा fwnode_handle *child;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा v4l2_flash_config v4l2_config = अणुपूर्ण;
	पूर्णांक ret;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &client->dev;
	mutex_init(&priv->lock);

	priv->regmap = devm_regmap_init_i2c(client, &rt4505_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(priv->dev, "Failed to allocate register map\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, RT4505_REG_RESET, RT4505_RESET_MASK);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to reset registers\n");
		वापस ret;
	पूर्ण

	child = fwnode_get_next_available_child_node(client->dev.fwnode, शून्य);
	अगर (!child) अणु
		dev_err(priv->dev, "Failed to get child node\n");
		वापस -EINVAL;
	पूर्ण
	init_data.fwnode = child;

	rt4505_init_flash_properties(priv, child);
	ret = devm_led_classdev_flash_रेजिस्टर_ext(priv->dev, &priv->flash,
						   &init_data);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to register flash\n");
		वापस ret;
	पूर्ण

	rt4505_init_v4l2_config(priv, &v4l2_config);
	priv->v4l2_flash = v4l2_flash_init(priv->dev, init_data.fwnode,
					   &priv->flash, &v4l2_flash_ops,
					   &v4l2_config);
	अगर (IS_ERR(priv->v4l2_flash)) अणु
		dev_err(priv->dev, "Failed to register v4l2 flash\n");
		वापस PTR_ERR(priv->v4l2_flash);
	पूर्ण

	i2c_set_clientdata(client, priv);
	वापस 0;
पूर्ण

अटल पूर्णांक rt4505_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rt4505_priv *priv = i2c_get_clientdata(client);

	v4l2_flash_release(priv->v4l2_flash);
	वापस 0;
पूर्ण

अटल व्योम rt4505_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा rt4505_priv *priv = i2c_get_clientdata(client);

	/* Reset रेजिस्टरs to make sure all off beक्रमe shutकरोwn */
	regmap_ग_लिखो(priv->regmap, RT4505_REG_RESET, RT4505_RESET_MASK);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused rt4505_leds_match[] = अणु
	अणु .compatible = "richtek,rt4505", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt4505_leds_match);

अटल काष्ठा i2c_driver rt4505_driver = अणु
	.driver = अणु
		.name = "rt4505",
		.of_match_table = of_match_ptr(rt4505_leds_match),
	पूर्ण,
	.probe_new = rt4505_probe,
	.हटाओ = rt4505_हटाओ,
	.shutकरोwn = rt4505_shutकरोwn,
पूर्ण;
module_i2c_driver(rt4505_driver);

MODULE_AUTHOR("ChiYuan Huang <cy_huang@richtek.com>");
MODULE_LICENSE("GPL v2");
