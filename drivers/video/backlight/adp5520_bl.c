<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Backlight driver क्रम Analog Devices ADP5520/ADP5501 MFD PMICs
 *
 * Copyright 2009 Analog Devices Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/mfd/adp5520.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

काष्ठा adp5520_bl अणु
	काष्ठा device *master;
	काष्ठा adp5520_backlight_platक्रमm_data *pdata;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ cached_daylight_max;
	पूर्णांक id;
	पूर्णांक current_brightness;
पूर्ण;

अटल पूर्णांक adp5520_bl_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा adp5520_bl *data = bl_get_data(bl);
	काष्ठा device *master = data->master;
	पूर्णांक ret = 0;

	अगर (data->pdata->en_ambl_sens) अणु
		अगर ((brightness > 0) && (brightness < ADP5020_MAX_BRIGHTNESS)) अणु
			/* Disable Ambient Light स्वतः adjust */
			ret |= adp5520_clr_bits(master, ADP5520_BL_CONTROL,
					ADP5520_BL_AUTO_ADJ);
			ret |= adp5520_ग_लिखो(master, ADP5520_DAYLIGHT_MAX,
					brightness);
		पूर्ण अन्यथा अणु
			/*
			 * MAX_BRIGHTNESS -> Enable Ambient Light स्वतः adjust
			 * restore daylight l3 sysfs brightness
			 */
			ret |= adp5520_ग_लिखो(master, ADP5520_DAYLIGHT_MAX,
					 data->cached_daylight_max);
			ret |= adp5520_set_bits(master, ADP5520_BL_CONTROL,
					 ADP5520_BL_AUTO_ADJ);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret |= adp5520_ग_लिखो(master, ADP5520_DAYLIGHT_MAX, brightness);
	पूर्ण

	अगर (data->current_brightness && brightness == 0)
		ret |= adp5520_set_bits(master,
				ADP5520_MODE_STATUS, ADP5520_DIM_EN);
	अन्यथा अगर (data->current_brightness == 0 && brightness)
		ret |= adp5520_clr_bits(master,
				ADP5520_MODE_STATUS, ADP5520_DIM_EN);

	अगर (!ret)
		data->current_brightness = brightness;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5520_bl_update_status(काष्ठा backlight_device *bl)
अणु
	वापस adp5520_bl_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक adp5520_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा adp5520_bl *data = bl_get_data(bl);
	पूर्णांक error;
	uपूर्णांक8_t reg_val;

	error = adp5520_पढ़ो(data->master, ADP5520_BL_VALUE, &reg_val);

	वापस error ? data->current_brightness : reg_val;
पूर्ण

अटल स्थिर काष्ठा backlight_ops adp5520_bl_ops = अणु
	.update_status	= adp5520_bl_update_status,
	.get_brightness	= adp5520_bl_get_brightness,
पूर्ण;

अटल पूर्णांक adp5520_bl_setup(काष्ठा backlight_device *bl)
अणु
	काष्ठा adp5520_bl *data = bl_get_data(bl);
	काष्ठा device *master = data->master;
	काष्ठा adp5520_backlight_platक्रमm_data *pdata = data->pdata;
	पूर्णांक ret = 0;

	ret |= adp5520_ग_लिखो(master, ADP5520_DAYLIGHT_MAX,
				pdata->l1_daylight_max);
	ret |= adp5520_ग_लिखो(master, ADP5520_DAYLIGHT_DIM,
				pdata->l1_daylight_dim);

	अगर (pdata->en_ambl_sens) अणु
		data->cached_daylight_max = pdata->l1_daylight_max;
		ret |= adp5520_ग_लिखो(master, ADP5520_OFFICE_MAX,
				pdata->l2_office_max);
		ret |= adp5520_ग_लिखो(master, ADP5520_OFFICE_DIM,
				pdata->l2_office_dim);
		ret |= adp5520_ग_लिखो(master, ADP5520_DARK_MAX,
				pdata->l3_dark_max);
		ret |= adp5520_ग_लिखो(master, ADP5520_DARK_DIM,
				pdata->l3_dark_dim);
		ret |= adp5520_ग_लिखो(master, ADP5520_L2_TRIP,
				pdata->l2_trip);
		ret |= adp5520_ग_लिखो(master, ADP5520_L2_HYS,
				pdata->l2_hyst);
		ret |= adp5520_ग_लिखो(master, ADP5520_L3_TRIP,
				 pdata->l3_trip);
		ret |= adp5520_ग_लिखो(master, ADP5520_L3_HYS,
				pdata->l3_hyst);
		ret |= adp5520_ग_लिखो(master, ADP5520_ALS_CMPR_CFG,
				ALS_CMPR_CFG_VAL(pdata->abml_filt,
				ADP5520_L3_EN));
	पूर्ण

	ret |= adp5520_ग_लिखो(master, ADP5520_BL_CONTROL,
			BL_CTRL_VAL(pdata->fade_led_law,
					pdata->en_ambl_sens));

	ret |= adp5520_ग_लिखो(master, ADP5520_BL_FADE, FADE_VAL(pdata->fade_in,
			pdata->fade_out));

	ret |= adp5520_set_bits(master, ADP5520_MODE_STATUS,
			ADP5520_BL_EN | ADP5520_DIM_EN);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार adp5520_show(काष्ठा device *dev, अक्षर *buf, पूर्णांक reg)
अणु
	काष्ठा adp5520_bl *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	uपूर्णांक8_t reg_val;

	mutex_lock(&data->lock);
	ret = adp5520_पढ़ो(data->master, reg, &reg_val);
	mutex_unlock(&data->lock);

	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", reg_val);
पूर्ण

अटल sमाप_प्रकार adp5520_store(काष्ठा device *dev, स्थिर अक्षर *buf,
			 माप_प्रकार count, पूर्णांक reg)
अणु
	काष्ठा adp5520_bl *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->lock);
	adp5520_ग_लिखो(data->master, reg, val);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adp5520_bl_dark_max_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp5520_show(dev, buf, ADP5520_DARK_MAX);
पूर्ण

अटल sमाप_प्रकार adp5520_bl_dark_max_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp5520_store(dev, buf, count, ADP5520_DARK_MAX);
पूर्ण
अटल DEVICE_ATTR(dark_max, 0664, adp5520_bl_dark_max_show,
			adp5520_bl_dark_max_store);

अटल sमाप_प्रकार adp5520_bl_office_max_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp5520_show(dev, buf, ADP5520_OFFICE_MAX);
पूर्ण

अटल sमाप_प्रकार adp5520_bl_office_max_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp5520_store(dev, buf, count, ADP5520_OFFICE_MAX);
पूर्ण
अटल DEVICE_ATTR(office_max, 0664, adp5520_bl_office_max_show,
			adp5520_bl_office_max_store);

अटल sमाप_प्रकार adp5520_bl_daylight_max_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp5520_show(dev, buf, ADP5520_DAYLIGHT_MAX);
पूर्ण

अटल sमाप_प्रकार adp5520_bl_daylight_max_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adp5520_bl *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &data->cached_daylight_max);
	अगर (ret < 0)
		वापस ret;

	वापस adp5520_store(dev, buf, count, ADP5520_DAYLIGHT_MAX);
पूर्ण
अटल DEVICE_ATTR(daylight_max, 0664, adp5520_bl_daylight_max_show,
			adp5520_bl_daylight_max_store);

अटल sमाप_प्रकार adp5520_bl_dark_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp5520_show(dev, buf, ADP5520_DARK_DIM);
पूर्ण

अटल sमाप_प्रकार adp5520_bl_dark_dim_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp5520_store(dev, buf, count, ADP5520_DARK_DIM);
पूर्ण
अटल DEVICE_ATTR(dark_dim, 0664, adp5520_bl_dark_dim_show,
			adp5520_bl_dark_dim_store);

अटल sमाप_प्रकार adp5520_bl_office_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp5520_show(dev, buf, ADP5520_OFFICE_DIM);
पूर्ण

अटल sमाप_प्रकार adp5520_bl_office_dim_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp5520_store(dev, buf, count, ADP5520_OFFICE_DIM);
पूर्ण
अटल DEVICE_ATTR(office_dim, 0664, adp5520_bl_office_dim_show,
			adp5520_bl_office_dim_store);

अटल sमाप_प्रकार adp5520_bl_daylight_dim_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस adp5520_show(dev, buf, ADP5520_DAYLIGHT_DIM);
पूर्ण

अटल sमाप_प्रकार adp5520_bl_daylight_dim_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस adp5520_store(dev, buf, count, ADP5520_DAYLIGHT_DIM);
पूर्ण
अटल DEVICE_ATTR(daylight_dim, 0664, adp5520_bl_daylight_dim_show,
			adp5520_bl_daylight_dim_store);

अटल काष्ठा attribute *adp5520_bl_attributes[] = अणु
	&dev_attr_dark_max.attr,
	&dev_attr_dark_dim.attr,
	&dev_attr_office_max.attr,
	&dev_attr_office_dim.attr,
	&dev_attr_daylight_max.attr,
	&dev_attr_daylight_dim.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adp5520_bl_attr_group = अणु
	.attrs = adp5520_bl_attributes,
पूर्ण;

अटल पूर्णांक adp5520_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bl;
	काष्ठा adp5520_bl *data;
	पूर्णांक ret = 0;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->master = pdev->dev.parent;
	data->pdata = dev_get_platdata(&pdev->dev);

	अगर (data->pdata  == शून्य) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	data->id = pdev->id;
	data->current_brightness = 0;

	mutex_init(&data->lock);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = ADP5020_MAX_BRIGHTNESS;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, pdev->name,
					data->master, data, &adp5520_bl_ops,
					&props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	bl->props.brightness = ADP5020_MAX_BRIGHTNESS;
	अगर (data->pdata->en_ambl_sens)
		ret = sysfs_create_group(&bl->dev.kobj,
			&adp5520_bl_attr_group);

	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register sysfs\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bl);
	ret = adp5520_bl_setup(bl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup\n");
		अगर (data->pdata->en_ambl_sens)
			sysfs_हटाओ_group(&bl->dev.kobj,
					&adp5520_bl_attr_group);
		वापस ret;
	पूर्ण

	backlight_update_status(bl);

	वापस 0;
पूर्ण

अटल पूर्णांक adp5520_bl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bl = platक्रमm_get_drvdata(pdev);
	काष्ठा adp5520_bl *data = bl_get_data(bl);

	adp5520_clr_bits(data->master, ADP5520_MODE_STATUS, ADP5520_BL_EN);

	अगर (data->pdata->en_ambl_sens)
		sysfs_हटाओ_group(&bl->dev.kobj,
				&adp5520_bl_attr_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adp5520_bl_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl = dev_get_drvdata(dev);

	वापस adp5520_bl_set(bl, 0);
पूर्ण

अटल पूर्णांक adp5520_bl_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl = dev_get_drvdata(dev);

	backlight_update_status(bl);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(adp5520_bl_pm_ops, adp5520_bl_suspend,
			adp5520_bl_resume);

अटल काष्ठा platक्रमm_driver adp5520_bl_driver = अणु
	.driver		= अणु
		.name	= "adp5520-backlight",
		.pm	= &adp5520_bl_pm_ops,
	पूर्ण,
	.probe		= adp5520_bl_probe,
	.हटाओ		= adp5520_bl_हटाओ,
पूर्ण;

module_platक्रमm_driver(adp5520_bl_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("ADP5520(01) Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:adp5520-backlight");
