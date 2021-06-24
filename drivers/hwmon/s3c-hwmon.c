<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/hwmon/s3c-hwmon.c
 *
 * Copyright (C) 2005, 2008, 2009 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX/S3C64XX ADC hwmon support
*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश <linux/soc/samsung/s3c-adc.h>
#समावेश <linux/platक्रमm_data/hwmon-s3c.h>

काष्ठा s3c_hwmon_attr अणु
	काष्ठा sensor_device_attribute	in;
	काष्ठा sensor_device_attribute	label;
	अक्षर				in_name[12];
	अक्षर				label_name[12];
पूर्ण;

/**
 * काष्ठा s3c_hwmon - ADC hwmon client inक्रमmation
 * @lock: Access lock to serialise the conversions.
 * @client: The client we रेजिस्टरed with the S3C ADC core.
 * @hwmon_dev: The hwmon device we created.
 * @attr: The holders क्रम the channel attributes.
*/
काष्ठा s3c_hwmon अणु
	काष्ठा mutex		lock;
	काष्ठा s3c_adc_client	*client;
	काष्ठा device		*hwmon_dev;

	काष्ठा s3c_hwmon_attr	attrs[8];
पूर्ण;

/**
 * s3c_hwmon_पढ़ो_ch - पढ़ो a value from a given adc channel.
 * @dev: The device.
 * @hwmon: Our state.
 * @channel: The channel we're पढ़ोing from.
 *
 * Read a value from the @channel with the proper locking and sleep until
 * either the पढ़ो completes or we समयout aरुकोing the ADC core to get
 * back to us.
 */
अटल पूर्णांक s3c_hwmon_पढ़ो_ch(काष्ठा device *dev,
			     काष्ठा s3c_hwmon *hwmon, पूर्णांक channel)
अणु
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&hwmon->lock);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dev, "reading channel %d\n", channel);

	ret = s3c_adc_पढ़ो(hwmon->client, channel);
	mutex_unlock(&hwmon->lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SENSORS_S3C_RAW
/**
 * s3c_hwmon_show_raw - show a conversion from the raw channel number.
 * @dev: The device that the attribute beदीर्घs to.
 * @attr: The attribute being पढ़ो.
 * @buf: The result buffer.
 *
 * This show deals with the raw attribute, रेजिस्टरed क्रम each possible
 * ADC channel. This करोes a conversion and वापसs the raw (un-scaled)
 * value वापसed from the hardware.
 */
अटल sमाप_प्रकार s3c_hwmon_show_raw(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा s3c_hwmon *adc = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sa = to_sensor_dev_attr(attr);
	पूर्णांक ret;

	ret = s3c_hwmon_पढ़ो_ch(dev, adc, sa->index);

	वापस  (ret < 0) ? ret : snम_लिखो(buf, PAGE_SIZE, "%d\n", ret);
पूर्ण

अटल SENSOR_DEVICE_ATTR(adc0_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(adc1_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(adc2_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(adc3_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(adc4_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(adc5_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(adc6_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(adc7_raw, S_IRUGO, s3c_hwmon_show_raw, शून्य, 7);

अटल काष्ठा attribute *s3c_hwmon_attrs[9] = अणु
	&sensor_dev_attr_adc0_raw.dev_attr.attr,
	&sensor_dev_attr_adc1_raw.dev_attr.attr,
	&sensor_dev_attr_adc2_raw.dev_attr.attr,
	&sensor_dev_attr_adc3_raw.dev_attr.attr,
	&sensor_dev_attr_adc4_raw.dev_attr.attr,
	&sensor_dev_attr_adc5_raw.dev_attr.attr,
	&sensor_dev_attr_adc6_raw.dev_attr.attr,
	&sensor_dev_attr_adc7_raw.dev_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group s3c_hwmon_attrgroup = अणु
	.attrs	= s3c_hwmon_attrs,
पूर्ण;

अटल अंतरभूत पूर्णांक s3c_hwmon_add_raw(काष्ठा device *dev)
अणु
	वापस sysfs_create_group(&dev->kobj, &s3c_hwmon_attrgroup);
पूर्ण

अटल अंतरभूत व्योम s3c_hwmon_हटाओ_raw(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &s3c_hwmon_attrgroup);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक s3c_hwmon_add_raw(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम s3c_hwmon_हटाओ_raw(काष्ठा device *dev) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SENSORS_S3C_RAW */

/**
 * s3c_hwmon_ch_show - show value of a given channel
 * @dev: The device that the attribute beदीर्घs to.
 * @attr: The attribute being पढ़ो.
 * @buf: The result buffer.
 *
 * Read a value from the ADC and scale it beक्रमe वापसing it to the
 * caller. The scale factor is gained from the channel configuration
 * passed via the platक्रमm data when the device was रेजिस्टरed.
 */
अटल sमाप_प्रकार s3c_hwmon_ch_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sen_attr = to_sensor_dev_attr(attr);
	काष्ठा s3c_hwmon *hwmon = dev_get_drvdata(dev);
	काष्ठा s3c_hwmon_pdata *pdata = dev_get_platdata(dev);
	काष्ठा s3c_hwmon_chcfg *cfg;
	पूर्णांक ret;

	cfg = pdata->in[sen_attr->index];

	ret = s3c_hwmon_पढ़ो_ch(dev, hwmon, sen_attr->index);
	अगर (ret < 0)
		वापस ret;

	ret *= cfg->mult;
	ret = DIV_ROUND_CLOSEST(ret, cfg->भाग);

	वापस sysfs_emit(buf, "%d\n", ret);
पूर्ण

/**
 * s3c_hwmon_label_show - show label name of the given channel.
 * @dev: The device that the attribute beदीर्घs to.
 * @attr: The attribute being पढ़ो.
 * @buf: The result buffer.
 *
 * Return the label name of a given channel
 */
अटल sमाप_प्रकार s3c_hwmon_label_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sen_attr = to_sensor_dev_attr(attr);
	काष्ठा s3c_hwmon_pdata *pdata = dev_get_platdata(dev);
	काष्ठा s3c_hwmon_chcfg *cfg;

	cfg = pdata->in[sen_attr->index];

	वापस sysfs_emit(buf, "%s\n", cfg->name);
पूर्ण

/**
 * s3c_hwmon_create_attr - create hwmon attribute क्रम given channel.
 * @dev: The device to create the attribute on.
 * @cfg: The channel configuration passed from the platक्रमm data.
 * @channel: The ADC channel number to process.
 *
 * Create the scaled attribute क्रम use with hwmon from the specअगरied
 * platक्रमm data in @pdata. The sysfs entry is handled by the routine
 * s3c_hwmon_ch_show().
 *
 * The attribute name is taken from the configuration data अगर present
 * otherwise the name is taken by concatenating in_ with the channel
 * number.
 */
अटल पूर्णांक s3c_hwmon_create_attr(काष्ठा device *dev,
				 काष्ठा s3c_hwmon_chcfg *cfg,
				 काष्ठा s3c_hwmon_attr *attrs,
				 पूर्णांक channel)
अणु
	काष्ठा sensor_device_attribute *attr;
	पूर्णांक ret;

	snम_लिखो(attrs->in_name, माप(attrs->in_name), "in%d_input", channel);

	attr = &attrs->in;
	attr->index = channel;
	sysfs_attr_init(&attr->dev_attr.attr);
	attr->dev_attr.attr.name  = attrs->in_name;
	attr->dev_attr.attr.mode  = S_IRUGO;
	attr->dev_attr.show = s3c_hwmon_ch_show;

	ret =  device_create_file(dev, &attr->dev_attr);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to create input attribute\n");
		वापस ret;
	पूर्ण

	/* अगर this has a name, add a label */
	अगर (cfg->name) अणु
		snम_लिखो(attrs->label_name, माप(attrs->label_name),
			 "in%d_label", channel);

		attr = &attrs->label;
		attr->index = channel;
		sysfs_attr_init(&attr->dev_attr.attr);
		attr->dev_attr.attr.name  = attrs->label_name;
		attr->dev_attr.attr.mode  = S_IRUGO;
		attr->dev_attr.show = s3c_hwmon_label_show;

		ret = device_create_file(dev, &attr->dev_attr);
		अगर (ret < 0) अणु
			device_हटाओ_file(dev, &attrs->in.dev_attr);
			dev_err(dev, "failed to create label attribute\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम s3c_hwmon_हटाओ_attr(काष्ठा device *dev,
				  काष्ठा s3c_hwmon_attr *attrs)
अणु
	device_हटाओ_file(dev, &attrs->in.dev_attr);
	device_हटाओ_file(dev, &attrs->label.dev_attr);
पूर्ण

/**
 * s3c_hwmon_probe - device probe entry.
 * @dev: The device being probed.
*/
अटल पूर्णांक s3c_hwmon_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c_hwmon_pdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा s3c_hwmon *hwmon;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!pdata) अणु
		dev_err(&dev->dev, "no platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	hwmon = devm_kzalloc(&dev->dev, माप(काष्ठा s3c_hwmon), GFP_KERNEL);
	अगर (hwmon == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(dev, hwmon);

	mutex_init(&hwmon->lock);

	/* Register with the core ADC driver. */

	hwmon->client = s3c_adc_रेजिस्टर(dev, शून्य, शून्य, 0);
	अगर (IS_ERR(hwmon->client)) अणु
		dev_err(&dev->dev, "cannot register adc\n");
		वापस PTR_ERR(hwmon->client);
	पूर्ण

	/* add attributes क्रम our adc devices. */

	ret = s3c_hwmon_add_raw(&dev->dev);
	अगर (ret)
		जाओ err_रेजिस्टरed;

	/* रेजिस्टर with the hwmon core */

	hwmon->hwmon_dev = hwmon_device_रेजिस्टर(&dev->dev);
	अगर (IS_ERR(hwmon->hwmon_dev)) अणु
		dev_err(&dev->dev, "error registering with hwmon\n");
		ret = PTR_ERR(hwmon->hwmon_dev);
		जाओ err_raw_attribute;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pdata->in); i++) अणु
		काष्ठा s3c_hwmon_chcfg *cfg = pdata->in[i];

		अगर (!cfg)
			जारी;

		अगर (cfg->mult >= 0x10000)
			dev_warn(&dev->dev,
				 "channel %d multiplier too large\n",
				 i);

		अगर (cfg->भाग == 0) अणु
			dev_err(&dev->dev, "channel %d divider zero\n", i);
			जारी;
		पूर्ण

		ret = s3c_hwmon_create_attr(&dev->dev, pdata->in[i],
					    &hwmon->attrs[i], i);
		अगर (ret) अणु
			dev_err(&dev->dev,
					"error creating channel %d\n", i);

			क्रम (i--; i >= 0; i--)
				s3c_hwmon_हटाओ_attr(&dev->dev,
							      &hwmon->attrs[i]);

			जाओ err_hwmon_रेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

 err_hwmon_रेजिस्टर:
	hwmon_device_unरेजिस्टर(hwmon->hwmon_dev);

 err_raw_attribute:
	s3c_hwmon_हटाओ_raw(&dev->dev);

 err_रेजिस्टरed:
	s3c_adc_release(hwmon->client);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c_hwmon_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c_hwmon *hwmon = platक्रमm_get_drvdata(dev);
	पूर्णांक i;

	s3c_hwmon_हटाओ_raw(&dev->dev);

	क्रम (i = 0; i < ARRAY_SIZE(hwmon->attrs); i++)
		s3c_hwmon_हटाओ_attr(&dev->dev, &hwmon->attrs[i]);

	hwmon_device_unरेजिस्टर(hwmon->hwmon_dev);
	s3c_adc_release(hwmon->client);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c_hwmon_driver = अणु
	.driver	= अणु
		.name		= "s3c-hwmon",
	पूर्ण,
	.probe		= s3c_hwmon_probe,
	.हटाओ		= s3c_hwmon_हटाओ,
पूर्ण;

module_platक्रमm_driver(s3c_hwmon_driver);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("S3C ADC HWMon driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:s3c-hwmon");
