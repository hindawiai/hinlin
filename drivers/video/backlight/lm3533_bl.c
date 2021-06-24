<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm3533-bl.c -- LM3533 Backlight driver
 *
 * Copyright (C) 2011-2012 Texas Instruments
 *
 * Author: Johan Hovold <jhovold@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/lm3533.h>


#घोषणा LM3533_HVCTRLBANK_COUNT		2
#घोषणा LM3533_BL_MAX_BRIGHTNESS	255

#घोषणा LM3533_REG_CTRLBANK_AB_BCONF	0x1a


काष्ठा lm3533_bl अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा lm3533_ctrlbank cb;
	काष्ठा backlight_device *bd;
	पूर्णांक id;
पूर्ण;


अटल अंतरभूत पूर्णांक lm3533_bl_get_ctrlbank_id(काष्ठा lm3533_bl *bl)
अणु
	वापस bl->id;
पूर्ण

अटल पूर्णांक lm3533_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा lm3533_bl *bl = bl_get_data(bd);

	वापस lm3533_ctrlbank_set_brightness(&bl->cb, backlight_get_brightness(bd));
पूर्ण

अटल पूर्णांक lm3533_bl_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा lm3533_bl *bl = bl_get_data(bd);
	u8 val;
	पूर्णांक ret;

	ret = lm3533_ctrlbank_get_brightness(&bl->cb, &val);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lm3533_bl_ops = अणु
	.get_brightness	= lm3533_bl_get_brightness,
	.update_status	= lm3533_bl_update_status,
पूर्ण;

अटल sमाप_प्रकार show_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", bl->id);
पूर्ण

अटल sमाप_प्रकार show_als_channel(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	अचिन्हित channel = lm3533_bl_get_ctrlbank_id(bl);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", channel);
पूर्ण

अटल sमाप_प्रकार show_als_en(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	पूर्णांक ctrlbank = lm3533_bl_get_ctrlbank_id(bl);
	u8 val;
	u8 mask;
	bool enable;
	पूर्णांक ret;

	ret = lm3533_पढ़ो(bl->lm3533, LM3533_REG_CTRLBANK_AB_BCONF, &val);
	अगर (ret)
		वापस ret;

	mask = 1 << (2 * ctrlbank);
	enable = val & mask;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", enable);
पूर्ण

अटल sमाप_प्रकार store_als_en(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	पूर्णांक ctrlbank = lm3533_bl_get_ctrlbank_id(bl);
	पूर्णांक enable;
	u8 val;
	u8 mask;
	पूर्णांक ret;

	अगर (kstrtoपूर्णांक(buf, 0, &enable))
		वापस -EINVAL;

	mask = 1 << (2 * ctrlbank);

	अगर (enable)
		val = mask;
	अन्यथा
		val = 0;

	ret = lm3533_update(bl->lm3533, LM3533_REG_CTRLBANK_AB_BCONF, val,
									mask);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार show_linear(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	u8 val;
	u8 mask;
	पूर्णांक linear;
	पूर्णांक ret;

	ret = lm3533_पढ़ो(bl->lm3533, LM3533_REG_CTRLBANK_AB_BCONF, &val);
	अगर (ret)
		वापस ret;

	mask = 1 << (2 * lm3533_bl_get_ctrlbank_id(bl) + 1);

	अगर (val & mask)
		linear = 1;
	अन्यथा
		linear = 0;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%x\n", linear);
पूर्ण

अटल sमाप_प्रकार store_linear(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	अचिन्हित दीर्घ linear;
	u8 mask;
	u8 val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 0, &linear))
		वापस -EINVAL;

	mask = 1 << (2 * lm3533_bl_get_ctrlbank_id(bl) + 1);

	अगर (linear)
		val = mask;
	अन्यथा
		val = 0;

	ret = lm3533_update(bl->lm3533, LM3533_REG_CTRLBANK_AB_BCONF, val,
									mask);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	u8 val;
	पूर्णांक ret;

	ret = lm3533_ctrlbank_get_pwm(&bl->cb, &val);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार store_pwm(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	u8 val;
	पूर्णांक ret;

	अगर (kstrtou8(buf, 0, &val))
		वापस -EINVAL;

	ret = lm3533_ctrlbank_set_pwm(&bl->cb, val);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल LM3533_ATTR_RO(als_channel);
अटल LM3533_ATTR_RW(als_en);
अटल LM3533_ATTR_RO(id);
अटल LM3533_ATTR_RW(linear);
अटल LM3533_ATTR_RW(pwm);

अटल काष्ठा attribute *lm3533_bl_attributes[] = अणु
	&dev_attr_als_channel.attr,
	&dev_attr_als_en.attr,
	&dev_attr_id.attr,
	&dev_attr_linear.attr,
	&dev_attr_pwm.attr,
	शून्य,
पूर्ण;

अटल umode_t lm3533_bl_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_als_channel.attr ||
					attr == &dev_attr_als_en.attr) अणु
		अगर (!bl->lm3533->have_als)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण;

अटल काष्ठा attribute_group lm3533_bl_attribute_group = अणु
	.is_visible	= lm3533_bl_attr_is_visible,
	.attrs		= lm3533_bl_attributes
पूर्ण;

अटल पूर्णांक lm3533_bl_setup(काष्ठा lm3533_bl *bl,
					काष्ठा lm3533_bl_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = lm3533_ctrlbank_set_max_current(&bl->cb, pdata->max_current);
	अगर (ret)
		वापस ret;

	वापस lm3533_ctrlbank_set_pwm(&bl->cb, pdata->pwm);
पूर्ण

अटल पूर्णांक lm3533_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा lm3533_bl_platक्रमm_data *pdata;
	काष्ठा lm3533_bl *bl;
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	lm3533 = dev_get_drvdata(pdev->dev.parent);
	अगर (!lm3533)
		वापस -EINVAL;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdev->id < 0 || pdev->id >= LM3533_HVCTRLBANK_COUNT) अणु
		dev_err(&pdev->dev, "illegal backlight id %d\n", pdev->id);
		वापस -EINVAL;
	पूर्ण

	bl = devm_kzalloc(&pdev->dev, माप(*bl), GFP_KERNEL);
	अगर (!bl)
		वापस -ENOMEM;

	bl->lm3533 = lm3533;
	bl->id = pdev->id;

	bl->cb.lm3533 = lm3533;
	bl->cb.id = lm3533_bl_get_ctrlbank_id(bl);
	bl->cb.dev = शून्य;			/* until रेजिस्टरed */

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = LM3533_BL_MAX_BRIGHTNESS;
	props.brightness = pdata->शेष_brightness;
	bd = devm_backlight_device_रेजिस्टर(&pdev->dev, pdata->name,
					pdev->dev.parent, bl, &lm3533_bl_ops,
					&props);
	अगर (IS_ERR(bd)) अणु
		dev_err(&pdev->dev, "failed to register backlight device\n");
		वापस PTR_ERR(bd);
	पूर्ण

	bl->bd = bd;
	bl->cb.dev = &bl->bd->dev;

	platक्रमm_set_drvdata(pdev, bl);

	ret = sysfs_create_group(&bd->dev.kobj, &lm3533_bl_attribute_group);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to create sysfs attributes\n");
		वापस ret;
	पूर्ण

	backlight_update_status(bd);

	ret = lm3533_bl_setup(bl, pdata);
	अगर (ret)
		जाओ err_sysfs_हटाओ;

	ret = lm3533_ctrlbank_enable(&bl->cb);
	अगर (ret)
		जाओ err_sysfs_हटाओ;

	वापस 0;

err_sysfs_हटाओ:
	sysfs_हटाओ_group(&bd->dev.kobj, &lm3533_bl_attribute_group);

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_bl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lm3533_bl *bl = platक्रमm_get_drvdata(pdev);
	काष्ठा backlight_device *bd = bl->bd;

	dev_dbg(&bd->dev, "%s\n", __func__);

	bd->props.घातer = FB_BLANK_POWERDOWN;
	bd->props.brightness = 0;

	lm3533_ctrlbank_disable(&bl->cb);
	sysfs_हटाओ_group(&bd->dev.kobj, &lm3533_bl_attribute_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक lm3533_bl_suspend(काष्ठा device *dev)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	वापस lm3533_ctrlbank_disable(&bl->cb);
पूर्ण

अटल पूर्णांक lm3533_bl_resume(काष्ठा device *dev)
अणु
	काष्ठा lm3533_bl *bl = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	वापस lm3533_ctrlbank_enable(&bl->cb);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(lm3533_bl_pm_ops, lm3533_bl_suspend, lm3533_bl_resume);

अटल व्योम lm3533_bl_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lm3533_bl *bl = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);

	lm3533_ctrlbank_disable(&bl->cb);
पूर्ण

अटल काष्ठा platक्रमm_driver lm3533_bl_driver = अणु
	.driver = अणु
		.name	= "lm3533-backlight",
		.pm	= &lm3533_bl_pm_ops,
	पूर्ण,
	.probe		= lm3533_bl_probe,
	.हटाओ		= lm3533_bl_हटाओ,
	.shutकरोwn	= lm3533_bl_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(lm3533_bl_driver);

MODULE_AUTHOR("Johan Hovold <jhovold@gmail.com>");
MODULE_DESCRIPTION("LM3533 Backlight driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lm3533-backlight");
