<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm3533-core.c -- LM3533 Core
 *
 * Copyright (C) 2011-2012 Texas Instruments
 *
 * Author: Johan Hovold <jhovold@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/regmap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/mfd/lm3533.h>


#घोषणा LM3533_BOOST_OVP_MASK		0x06
#घोषणा LM3533_BOOST_OVP_SHIFT		1

#घोषणा LM3533_BOOST_FREQ_MASK		0x01
#घोषणा LM3533_BOOST_FREQ_SHIFT		0

#घोषणा LM3533_BL_ID_MASK		1
#घोषणा LM3533_LED_ID_MASK		3
#घोषणा LM3533_BL_ID_MAX		1
#घोषणा LM3533_LED_ID_MAX		3

#घोषणा LM3533_HVLED_ID_MAX		2
#घोषणा LM3533_LVLED_ID_MAX		5

#घोषणा LM3533_REG_OUTPUT_CONF1		0x10
#घोषणा LM3533_REG_OUTPUT_CONF2		0x11
#घोषणा LM3533_REG_BOOST_PWM		0x2c

#घोषणा LM3533_REG_MAX			0xb2


अटल काष्ठा mfd_cell lm3533_als_devs[] = अणु
	अणु
		.name	= "lm3533-als",
		.id	= -1,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell lm3533_bl_devs[] = अणु
	अणु
		.name	= "lm3533-backlight",
		.id	= 0,
	पूर्ण,
	अणु
		.name	= "lm3533-backlight",
		.id	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell lm3533_led_devs[] = अणु
	अणु
		.name	= "lm3533-leds",
		.id	= 0,
	पूर्ण,
	अणु
		.name	= "lm3533-leds",
		.id	= 1,
	पूर्ण,
	अणु
		.name	= "lm3533-leds",
		.id	= 2,
	पूर्ण,
	अणु
		.name	= "lm3533-leds",
		.id	= 3,
	पूर्ण,
पूर्ण;

पूर्णांक lm3533_पढ़ो(काष्ठा lm3533 *lm3533, u8 reg, u8 *val)
अणु
	पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = regmap_पढ़ो(lm3533->regmap, reg, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(lm3533->dev, "failed to read register %02x: %d\n",
								reg, ret);
		वापस ret;
	पूर्ण

	*val = पंचांगp;

	dev_dbg(lm3533->dev, "read [%02x]: %02x\n", reg, *val);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_पढ़ो);

पूर्णांक lm3533_ग_लिखो(काष्ठा lm3533 *lm3533, u8 reg, u8 val)
अणु
	पूर्णांक ret;

	dev_dbg(lm3533->dev, "write [%02x]: %02x\n", reg, val);

	ret = regmap_ग_लिखो(lm3533->regmap, reg, val);
	अगर (ret < 0) अणु
		dev_err(lm3533->dev, "failed to write register %02x: %d\n",
								reg, ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_ग_लिखो);

पूर्णांक lm3533_update(काष्ठा lm3533 *lm3533, u8 reg, u8 val, u8 mask)
अणु
	पूर्णांक ret;

	dev_dbg(lm3533->dev, "update [%02x]: %02x/%02x\n", reg, val, mask);

	ret = regmap_update_bits(lm3533->regmap, reg, mask, val);
	अगर (ret < 0) अणु
		dev_err(lm3533->dev, "failed to update register %02x: %d\n",
								reg, ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lm3533_update);

अटल पूर्णांक lm3533_set_boost_freq(काष्ठा lm3533 *lm3533,
						क्रमागत lm3533_boost_freq freq)
अणु
	पूर्णांक ret;

	ret = lm3533_update(lm3533, LM3533_REG_BOOST_PWM,
					freq << LM3533_BOOST_FREQ_SHIFT,
					LM3533_BOOST_FREQ_MASK);
	अगर (ret)
		dev_err(lm3533->dev, "failed to set boost frequency\n");

	वापस ret;
पूर्ण


अटल पूर्णांक lm3533_set_boost_ovp(काष्ठा lm3533 *lm3533,
						क्रमागत lm3533_boost_ovp ovp)
अणु
	पूर्णांक ret;

	ret = lm3533_update(lm3533, LM3533_REG_BOOST_PWM,
					ovp << LM3533_BOOST_OVP_SHIFT,
					LM3533_BOOST_OVP_MASK);
	अगर (ret)
		dev_err(lm3533->dev, "failed to set boost ovp\n");

	वापस ret;
पूर्ण

/*
 * HVLED output config -- output hvled controlled by backlight bl
 */
अटल पूर्णांक lm3533_set_hvled_config(काष्ठा lm3533 *lm3533, u8 hvled, u8 bl)
अणु
	u8 val;
	u8 mask;
	पूर्णांक shअगरt;
	पूर्णांक ret;

	अगर (hvled == 0 || hvled > LM3533_HVLED_ID_MAX)
		वापस -EINVAL;

	अगर (bl > LM3533_BL_ID_MAX)
		वापस -EINVAL;

	shअगरt = hvled - 1;
	mask = LM3533_BL_ID_MASK << shअगरt;
	val = bl << shअगरt;

	ret = lm3533_update(lm3533, LM3533_REG_OUTPUT_CONF1, val, mask);
	अगर (ret)
		dev_err(lm3533->dev, "failed to set hvled config\n");

	वापस ret;
पूर्ण

/*
 * LVLED output config -- output lvled controlled by LED led
 */
अटल पूर्णांक lm3533_set_lvled_config(काष्ठा lm3533 *lm3533, u8 lvled, u8 led)
अणु
	u8 reg;
	u8 val;
	u8 mask;
	पूर्णांक shअगरt;
	पूर्णांक ret;

	अगर (lvled == 0 || lvled > LM3533_LVLED_ID_MAX)
		वापस -EINVAL;

	अगर (led > LM3533_LED_ID_MAX)
		वापस -EINVAL;

	अगर (lvled < 4) अणु
		reg = LM3533_REG_OUTPUT_CONF1;
		shअगरt = 2 * lvled;
	पूर्ण अन्यथा अणु
		reg = LM3533_REG_OUTPUT_CONF2;
		shअगरt = 2 * (lvled - 4);
	पूर्ण

	mask = LM3533_LED_ID_MASK << shअगरt;
	val = led << shअगरt;

	ret = lm3533_update(lm3533, reg, val, mask);
	अगर (ret)
		dev_err(lm3533->dev, "failed to set lvled config\n");

	वापस ret;
पूर्ण

अटल व्योम lm3533_enable(काष्ठा lm3533 *lm3533)
अणु
	अगर (gpio_is_valid(lm3533->gpio_hwen))
		gpio_set_value(lm3533->gpio_hwen, 1);
पूर्ण

अटल व्योम lm3533_disable(काष्ठा lm3533 *lm3533)
अणु
	अगर (gpio_is_valid(lm3533->gpio_hwen))
		gpio_set_value(lm3533->gpio_hwen, 0);
पूर्ण

क्रमागत lm3533_attribute_type अणु
	LM3533_ATTR_TYPE_BACKLIGHT,
	LM3533_ATTR_TYPE_LED,
पूर्ण;

काष्ठा lm3533_device_attribute अणु
	काष्ठा device_attribute dev_attr;
	क्रमागत lm3533_attribute_type type;
	जोड़ अणु
		काष्ठा अणु
			u8 id;
		पूर्ण output;
	पूर्ण u;
पूर्ण;

#घोषणा to_lm3533_dev_attr(_attr) \
	container_of(_attr, काष्ठा lm3533_device_attribute, dev_attr)

अटल sमाप_प्रकार show_output(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm3533 *lm3533 = dev_get_drvdata(dev);
	काष्ठा lm3533_device_attribute *lattr = to_lm3533_dev_attr(attr);
	पूर्णांक id = lattr->u.output.id;
	u8 reg;
	u8 val;
	u8 mask;
	पूर्णांक shअगरt;
	पूर्णांक ret;

	अगर (lattr->type == LM3533_ATTR_TYPE_BACKLIGHT) अणु
		reg = LM3533_REG_OUTPUT_CONF1;
		shअगरt = id - 1;
		mask = LM3533_BL_ID_MASK << shअगरt;
	पूर्ण अन्यथा अणु
		अगर (id < 4) अणु
			reg = LM3533_REG_OUTPUT_CONF1;
			shअगरt = 2 * id;
		पूर्ण अन्यथा अणु
			reg = LM3533_REG_OUTPUT_CONF2;
			shअगरt = 2 * (id - 4);
		पूर्ण
		mask = LM3533_LED_ID_MASK << shअगरt;
	पूर्ण

	ret = lm3533_पढ़ो(lm3533, reg, &val);
	अगर (ret)
		वापस ret;

	val = (val & mask) >> shअगरt;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार store_output(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lm3533 *lm3533 = dev_get_drvdata(dev);
	काष्ठा lm3533_device_attribute *lattr = to_lm3533_dev_attr(attr);
	पूर्णांक id = lattr->u.output.id;
	u8 val;
	पूर्णांक ret;

	अगर (kstrtou8(buf, 0, &val))
		वापस -EINVAL;

	अगर (lattr->type == LM3533_ATTR_TYPE_BACKLIGHT)
		ret = lm3533_set_hvled_config(lm3533, id, val);
	अन्यथा
		ret = lm3533_set_lvled_config(lm3533, id, val);

	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

#घोषणा LM3533_OUTPUT_ATTR(_name, _mode, _show, _store, _type, _id) \
	काष्ठा lm3533_device_attribute lm3533_dev_attr_##_name = \
		अणु .dev_attr	= __ATTR(_name, _mode, _show, _store), \
		  .type		= _type, \
		  .u.output	= अणु .id = _id पूर्ण, पूर्ण

#घोषणा LM3533_OUTPUT_ATTR_RW(_name, _type, _id) \
	LM3533_OUTPUT_ATTR(output_##_name, S_IRUGO | S_IWUSR, \
					show_output, store_output, _type, _id)

#घोषणा LM3533_OUTPUT_HVLED_ATTR_RW(_nr) \
	LM3533_OUTPUT_ATTR_RW(hvled##_nr, LM3533_ATTR_TYPE_BACKLIGHT, _nr)
#घोषणा LM3533_OUTPUT_LVLED_ATTR_RW(_nr) \
	LM3533_OUTPUT_ATTR_RW(lvled##_nr, LM3533_ATTR_TYPE_LED, _nr)
/*
 * Output config:
 *
 * output_hvled<nr>	0-1
 * output_lvled<nr>	0-3
 */
अटल LM3533_OUTPUT_HVLED_ATTR_RW(1);
अटल LM3533_OUTPUT_HVLED_ATTR_RW(2);
अटल LM3533_OUTPUT_LVLED_ATTR_RW(1);
अटल LM3533_OUTPUT_LVLED_ATTR_RW(2);
अटल LM3533_OUTPUT_LVLED_ATTR_RW(3);
अटल LM3533_OUTPUT_LVLED_ATTR_RW(4);
अटल LM3533_OUTPUT_LVLED_ATTR_RW(5);

अटल काष्ठा attribute *lm3533_attributes[] = अणु
	&lm3533_dev_attr_output_hvled1.dev_attr.attr,
	&lm3533_dev_attr_output_hvled2.dev_attr.attr,
	&lm3533_dev_attr_output_lvled1.dev_attr.attr,
	&lm3533_dev_attr_output_lvled2.dev_attr.attr,
	&lm3533_dev_attr_output_lvled3.dev_attr.attr,
	&lm3533_dev_attr_output_lvled4.dev_attr.attr,
	&lm3533_dev_attr_output_lvled5.dev_attr.attr,
	शून्य,
पूर्ण;

#घोषणा to_dev_attr(_attr) \
	container_of(_attr, काष्ठा device_attribute, attr)

अटल umode_t lm3533_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lm3533 *lm3533 = dev_get_drvdata(dev);
	काष्ठा device_attribute *dattr = to_dev_attr(attr);
	काष्ठा lm3533_device_attribute *lattr = to_lm3533_dev_attr(dattr);
	क्रमागत lm3533_attribute_type type = lattr->type;
	umode_t mode = attr->mode;

	अगर (!lm3533->have_backlights && type == LM3533_ATTR_TYPE_BACKLIGHT)
		mode = 0;
	अन्यथा अगर (!lm3533->have_leds && type == LM3533_ATTR_TYPE_LED)
		mode = 0;

	वापस mode;
पूर्ण;

अटल काष्ठा attribute_group lm3533_attribute_group = अणु
	.is_visible	= lm3533_attr_is_visible,
	.attrs		= lm3533_attributes
पूर्ण;

अटल पूर्णांक lm3533_device_als_init(काष्ठा lm3533 *lm3533)
अणु
	काष्ठा lm3533_platक्रमm_data *pdata = dev_get_platdata(lm3533->dev);
	पूर्णांक ret;

	अगर (!pdata->als)
		वापस 0;

	lm3533_als_devs[0].platक्रमm_data = pdata->als;
	lm3533_als_devs[0].pdata_size = माप(*pdata->als);

	ret = mfd_add_devices(lm3533->dev, 0, lm3533_als_devs, 1, शून्य,
			      0, शून्य);
	अगर (ret) अणु
		dev_err(lm3533->dev, "failed to add ALS device\n");
		वापस ret;
	पूर्ण

	lm3533->have_als = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_device_bl_init(काष्ठा lm3533 *lm3533)
अणु
	काष्ठा lm3533_platक्रमm_data *pdata = dev_get_platdata(lm3533->dev);
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!pdata->backlights || pdata->num_backlights == 0)
		वापस 0;

	अगर (pdata->num_backlights > ARRAY_SIZE(lm3533_bl_devs))
		pdata->num_backlights = ARRAY_SIZE(lm3533_bl_devs);

	क्रम (i = 0; i < pdata->num_backlights; ++i) अणु
		lm3533_bl_devs[i].platक्रमm_data = &pdata->backlights[i];
		lm3533_bl_devs[i].pdata_size = माप(pdata->backlights[i]);
	पूर्ण

	ret = mfd_add_devices(lm3533->dev, 0, lm3533_bl_devs,
			      pdata->num_backlights, शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(lm3533->dev, "failed to add backlight devices\n");
		वापस ret;
	पूर्ण

	lm3533->have_backlights = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_device_led_init(काष्ठा lm3533 *lm3533)
अणु
	काष्ठा lm3533_platक्रमm_data *pdata = dev_get_platdata(lm3533->dev);
	पूर्णांक i;
	पूर्णांक ret;

	अगर (!pdata->leds || pdata->num_leds == 0)
		वापस 0;

	अगर (pdata->num_leds > ARRAY_SIZE(lm3533_led_devs))
		pdata->num_leds = ARRAY_SIZE(lm3533_led_devs);

	क्रम (i = 0; i < pdata->num_leds; ++i) अणु
		lm3533_led_devs[i].platक्रमm_data = &pdata->leds[i];
		lm3533_led_devs[i].pdata_size = माप(pdata->leds[i]);
	पूर्ण

	ret = mfd_add_devices(lm3533->dev, 0, lm3533_led_devs,
			      pdata->num_leds, शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(lm3533->dev, "failed to add LED devices\n");
		वापस ret;
	पूर्ण

	lm3533->have_leds = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_device_setup(काष्ठा lm3533 *lm3533,
					काष्ठा lm3533_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = lm3533_set_boost_freq(lm3533, pdata->boost_freq);
	अगर (ret)
		वापस ret;

	वापस lm3533_set_boost_ovp(lm3533, pdata->boost_ovp);
पूर्ण

अटल पूर्णांक lm3533_device_init(काष्ठा lm3533 *lm3533)
अणु
	काष्ठा lm3533_platक्रमm_data *pdata = dev_get_platdata(lm3533->dev);
	पूर्णांक ret;

	dev_dbg(lm3533->dev, "%s\n", __func__);

	अगर (!pdata) अणु
		dev_err(lm3533->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	lm3533->gpio_hwen = pdata->gpio_hwen;

	dev_set_drvdata(lm3533->dev, lm3533);

	अगर (gpio_is_valid(lm3533->gpio_hwen)) अणु
		ret = devm_gpio_request_one(lm3533->dev, lm3533->gpio_hwen,
					GPIOF_OUT_INIT_LOW, "lm3533-hwen");
		अगर (ret < 0) अणु
			dev_err(lm3533->dev,
				"failed to request HWEN GPIO %d\n",
				lm3533->gpio_hwen);
			वापस ret;
		पूर्ण
	पूर्ण

	lm3533_enable(lm3533);

	ret = lm3533_device_setup(lm3533, pdata);
	अगर (ret)
		जाओ err_disable;

	lm3533_device_als_init(lm3533);
	lm3533_device_bl_init(lm3533);
	lm3533_device_led_init(lm3533);

	ret = sysfs_create_group(&lm3533->dev->kobj, &lm3533_attribute_group);
	अगर (ret < 0) अणु
		dev_err(lm3533->dev, "failed to create sysfs attributes\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_unरेजिस्टर:
	mfd_हटाओ_devices(lm3533->dev);
err_disable:
	lm3533_disable(lm3533);

	वापस ret;
पूर्ण

अटल व्योम lm3533_device_निकास(काष्ठा lm3533 *lm3533)
अणु
	dev_dbg(lm3533->dev, "%s\n", __func__);

	sysfs_हटाओ_group(&lm3533->dev->kobj, &lm3533_attribute_group);

	mfd_हटाओ_devices(lm3533->dev);
	lm3533_disable(lm3533);
पूर्ण

अटल bool lm3533_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x10 ... 0x2c:
	हाल 0x30 ... 0x38:
	हाल 0x40 ... 0x45:
	हाल 0x50 ... 0x57:
	हाल 0x60 ... 0x6e:
	हाल 0x70 ... 0x75:
	हाल 0x80 ... 0x85:
	हाल 0x90 ... 0x95:
	हाल 0xa0 ... 0xa5:
	हाल 0xb0 ... 0xb2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool lm3533_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x34 ... 0x36:	/* zone */
	हाल 0x37 ... 0x38:	/* adc */
	हाल 0xb0 ... 0xb1:	/* fault */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool lm3533_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x34:		/* zone */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= LM3533_REG_MAX,
	.पढ़ोable_reg	= lm3533_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg	= lm3533_अस्थिर_रेजिस्टर,
	.precious_reg	= lm3533_precious_रेजिस्टर,
पूर्ण;

अटल पूर्णांक lm3533_i2c_probe(काष्ठा i2c_client *i2c,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm3533 *lm3533;

	dev_dbg(&i2c->dev, "%s\n", __func__);

	lm3533 = devm_kzalloc(&i2c->dev, माप(*lm3533), GFP_KERNEL);
	अगर (!lm3533)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, lm3533);

	lm3533->regmap = devm_regmap_init_i2c(i2c, &regmap_config);
	अगर (IS_ERR(lm3533->regmap))
		वापस PTR_ERR(lm3533->regmap);

	lm3533->dev = &i2c->dev;
	lm3533->irq = i2c->irq;

	वापस lm3533_device_init(lm3533);
पूर्ण

अटल पूर्णांक lm3533_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा lm3533 *lm3533 = i2c_get_clientdata(i2c);

	dev_dbg(&i2c->dev, "%s\n", __func__);

	lm3533_device_निकास(lm3533);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3533_i2c_ids[] = अणु
	अणु "lm3533", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm3533_i2c_ids);

अटल काष्ठा i2c_driver lm3533_i2c_driver = अणु
	.driver = अणु
		   .name = "lm3533",
	पूर्ण,
	.id_table	= lm3533_i2c_ids,
	.probe		= lm3533_i2c_probe,
	.हटाओ		= lm3533_i2c_हटाओ,
पूर्ण;

अटल पूर्णांक __init lm3533_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&lm3533_i2c_driver);
पूर्ण
subsys_initcall(lm3533_i2c_init);

अटल व्योम __निकास lm3533_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&lm3533_i2c_driver);
पूर्ण
module_निकास(lm3533_i2c_निकास);

MODULE_AUTHOR("Johan Hovold <jhovold@gmail.com>");
MODULE_DESCRIPTION("LM3533 Core");
MODULE_LICENSE("GPL");
