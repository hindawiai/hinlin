<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sky81452-backlight.c	SKY81452 backlight driver
 *
 * Copyright 2014 Skyworks Solutions Inc.
 * Author : Gyungoh Yoo <jack.yoo@skyworksinc.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* रेजिस्टरs */
#घोषणा SKY81452_REG0	0x00
#घोषणा SKY81452_REG1	0x01
#घोषणा SKY81452_REG2	0x02
#घोषणा SKY81452_REG4	0x04
#घोषणा SKY81452_REG5	0x05

/* bit mask */
#घोषणा SKY81452_CS	0xFF
#घोषणा SKY81452_EN	0x3F
#घोषणा SKY81452_IGPW	0x20
#घोषणा SKY81452_PWMMD	0x10
#घोषणा SKY81452_PHASE	0x08
#घोषणा SKY81452_ILIM	0x04
#घोषणा SKY81452_VSHRT	0x03
#घोषणा SKY81452_OCP	0x80
#घोषणा SKY81452_OTMP	0x40
#घोषणा SKY81452_SHRT	0x3F
#घोषणा SKY81452_OPN	0x3F

#घोषणा SKY81452_DEFAULT_NAME "lcd-backlight"
#घोषणा SKY81452_MAX_BRIGHTNESS	(SKY81452_CS + 1)

/**
 * काष्ठा sky81452_platक्रमm_data
 * @name:	backlight driver name.
 *		If it is not defined, शेष name is lcd-backlight.
 * @gpiod_enable:GPIO descriptor which control EN pin
 * @enable:	Enable mask क्रम current sink channel 1, 2, 3, 4, 5 and 6.
 * @ignore_pwm:	true अगर DPWMI should be ignored.
 * @dpwm_mode:	true is DPWM dimming mode, otherwise Analog dimming mode.
 * @phase_shअगरt:true is phase shअगरt mode.
 * @लघु_detection_threshold:	It should be one of 4, 5, 6 and 7V.
 * @boost_current_limit:	It should be one of 2300, 2750mA.
 */
काष्ठा sky81452_bl_platक्रमm_data अणु
	स्थिर अक्षर *name;
	काष्ठा gpio_desc *gpiod_enable;
	अचिन्हित पूर्णांक enable;
	bool ignore_pwm;
	bool dpwm_mode;
	bool phase_shअगरt;
	अचिन्हित पूर्णांक लघु_detection_threshold;
	अचिन्हित पूर्णांक boost_current_limit;
पूर्ण;

#घोषणा CTZ(b) __builtin_ctz(b)

अटल पूर्णांक sky81452_bl_update_status(काष्ठा backlight_device *bd)
अणु
	स्थिर काष्ठा sky81452_bl_platक्रमm_data *pdata =
			dev_get_platdata(bd->dev.parent);
	स्थिर अचिन्हित पूर्णांक brightness = (अचिन्हित पूर्णांक)bd->props.brightness;
	काष्ठा regmap *regmap = bl_get_data(bd);
	पूर्णांक ret;

	अगर (brightness > 0) अणु
		ret = regmap_ग_लिखो(regmap, SKY81452_REG0, brightness - 1);
		अगर (ret < 0)
			वापस ret;

		वापस regmap_update_bits(regmap, SKY81452_REG1, SKY81452_EN,
					pdata->enable << CTZ(SKY81452_EN));
	पूर्ण

	वापस regmap_update_bits(regmap, SKY81452_REG1, SKY81452_EN, 0);
पूर्ण

अटल स्थिर काष्ठा backlight_ops sky81452_bl_ops = अणु
	.update_status = sky81452_bl_update_status,
पूर्ण;

अटल sमाप_प्रकार sky81452_bl_store_enable(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा regmap *regmap = bl_get_data(to_backlight_device(dev));
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 16, &value);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(regmap, SKY81452_REG1, SKY81452_EN,
					value << CTZ(SKY81452_EN));
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sky81452_bl_show_खोलो_लघु(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regmap *regmap = bl_get_data(to_backlight_device(dev));
	अचिन्हित पूर्णांक reg, value = 0;
	अक्षर पंचांगp[3];
	पूर्णांक i, ret;

	reg = !म_भेद(attr->attr.name, "open") ? SKY81452_REG5 : SKY81452_REG4;
	ret = regmap_पढ़ो(regmap, reg, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (value & SKY81452_SHRT) अणु
		*buf = 0;
		क्रम (i = 0; i < 6; i++) अणु
			अगर (value & 0x01) अणु
				प्र_लिखो(पंचांगp, "%d ", i + 1);
				म_जोड़ो(buf, पंचांगp);
			पूर्ण
			value >>= 1;
		पूर्ण
		म_जोड़ो(buf, "\n");
	पूर्ण अन्यथा अणु
		म_नकल(buf, "none\n");
	पूर्ण

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार sky81452_bl_show_fault(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा regmap *regmap = bl_get_data(to_backlight_device(dev));
	अचिन्हित पूर्णांक value = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, SKY81452_REG4, &value);
	अगर (ret < 0)
		वापस ret;

	*buf = 0;

	अगर (value & SKY81452_OCP)
		म_जोड़ो(buf, "over-current ");

	अगर (value & SKY81452_OTMP)
		म_जोड़ो(buf, "over-temperature");

	म_जोड़ो(buf, "\n");
	वापस म_माप(buf);
पूर्ण

अटल DEVICE_ATTR(enable, S_IWGRP | S_IWUSR, शून्य, sky81452_bl_store_enable);
अटल DEVICE_ATTR(खोलो, S_IRUGO, sky81452_bl_show_खोलो_लघु, शून्य);
अटल DEVICE_ATTR(लघु, S_IRUGO, sky81452_bl_show_खोलो_लघु, शून्य);
अटल DEVICE_ATTR(fault, S_IRUGO, sky81452_bl_show_fault, शून्य);

अटल काष्ठा attribute *sky81452_bl_attribute[] = अणु
	&dev_attr_enable.attr,
	&dev_attr_खोलो.attr,
	&dev_attr_लघु.attr,
	&dev_attr_fault.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group sky81452_bl_attr_group = अणु
	.attrs = sky81452_bl_attribute,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा sky81452_bl_platक्रमm_data *sky81452_bl_parse_dt(
							काष्ठा device *dev)
अणु
	काष्ठा device_node *np = of_node_get(dev->of_node);
	काष्ठा sky81452_bl_platक्रमm_data *pdata;
	पूर्णांक num_entry;
	अचिन्हित पूर्णांक sources[6];
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(dev, "backlight node not found.\n");
		वापस ERR_PTR(-ENODATA);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		of_node_put(np);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	of_property_पढ़ो_string(np, "name", &pdata->name);
	pdata->ignore_pwm = of_property_पढ़ो_bool(np, "skyworks,ignore-pwm");
	pdata->dpwm_mode = of_property_पढ़ो_bool(np, "skyworks,dpwm-mode");
	pdata->phase_shअगरt = of_property_पढ़ो_bool(np, "skyworks,phase-shift");
	pdata->gpiod_enable = devm_gpiod_get_optional(dev, शून्य, GPIOD_OUT_HIGH);

	ret = of_property_count_u32_elems(np, "led-sources");
	अगर (ret < 0) अणु
		pdata->enable = SKY81452_EN >> CTZ(SKY81452_EN);
	पूर्ण अन्यथा अणु
		num_entry = ret;
		अगर (num_entry > 6)
			num_entry = 6;

		ret = of_property_पढ़ो_u32_array(np, "led-sources", sources,
					num_entry);
		अगर (ret < 0) अणु
			dev_err(dev, "led-sources node is invalid.\n");
			of_node_put(np);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		pdata->enable = 0;
		जबतक (--num_entry)
			pdata->enable |= (1 << sources[num_entry]);
	पूर्ण

	ret = of_property_पढ़ो_u32(np,
			"skyworks,short-detection-threshold-volt",
			&pdata->लघु_detection_threshold);
	अगर (ret < 0)
		pdata->लघु_detection_threshold = 7;

	ret = of_property_पढ़ो_u32(np, "skyworks,current-limit-mA",
			&pdata->boost_current_limit);
	अगर (ret < 0)
		pdata->boost_current_limit = 2750;

	of_node_put(np);
	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा sky81452_bl_platक्रमm_data *sky81452_bl_parse_dt(
							काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sky81452_bl_init_device(काष्ठा regmap *regmap,
		काष्ठा sky81452_bl_platक्रमm_data *pdata)
अणु
	अचिन्हित पूर्णांक value;

	value = pdata->ignore_pwm ? SKY81452_IGPW : 0;
	value |= pdata->dpwm_mode ? SKY81452_PWMMD : 0;
	value |= pdata->phase_shअगरt ? 0 : SKY81452_PHASE;

	अगर (pdata->boost_current_limit == 2300)
		value |= SKY81452_ILIM;
	अन्यथा अगर (pdata->boost_current_limit != 2750)
		वापस -EINVAL;

	अगर (pdata->लघु_detection_threshold < 4 ||
				pdata->लघु_detection_threshold > 7)
		वापस -EINVAL;
	value |= (7 - pdata->लघु_detection_threshold) << CTZ(SKY81452_VSHRT);

	वापस regmap_ग_लिखो(regmap, SKY81452_REG2, value);
पूर्ण

अटल पूर्णांक sky81452_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap = dev_get_drvdata(dev->parent);
	काष्ठा sky81452_bl_platक्रमm_data *pdata;
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	pdata = sky81452_bl_parse_dt(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	ret = sky81452_bl_init_device(regmap, pdata);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize. err=%d\n", ret);
		वापस ret;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.max_brightness = SKY81452_MAX_BRIGHTNESS;
	name = pdata->name ? pdata->name : SKY81452_DEFAULT_NAME;
	bd = devm_backlight_device_रेजिस्टर(dev, name, dev, regmap,
						&sky81452_bl_ops, &props);
	अगर (IS_ERR(bd)) अणु
		dev_err(dev, "failed to register. err=%ld\n", PTR_ERR(bd));
		वापस PTR_ERR(bd);
	पूर्ण

	platक्रमm_set_drvdata(pdev, bd);

	ret = sysfs_create_group(&bd->dev.kobj, &sky81452_bl_attr_group);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to create attribute. err=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sky81452_bl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sky81452_bl_platक्रमm_data *pdata =
						dev_get_platdata(&pdev->dev);
	काष्ठा backlight_device *bd = platक्रमm_get_drvdata(pdev);

	sysfs_हटाओ_group(&bd->dev.kobj, &sky81452_bl_attr_group);

	bd->props.घातer = FB_BLANK_UNBLANK;
	bd->props.brightness = 0;
	backlight_update_status(bd);

	अगर (pdata->gpiod_enable)
		gpiod_set_value_cansleep(pdata->gpiod_enable, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sky81452_bl_of_match[] = अणु
	अणु .compatible = "skyworks,sky81452-backlight", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sky81452_bl_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sky81452_bl_driver = अणु
	.driver = अणु
		.name = "sky81452-backlight",
		.of_match_table = of_match_ptr(sky81452_bl_of_match),
	पूर्ण,
	.probe = sky81452_bl_probe,
	.हटाओ = sky81452_bl_हटाओ,
पूर्ण;

module_platक्रमm_driver(sky81452_bl_driver);

MODULE_DESCRIPTION("Skyworks SKY81452 backlight driver");
MODULE_AUTHOR("Gyungoh Yoo <jack.yoo@skyworksinc.com>");
MODULE_LICENSE("GPL v2");
