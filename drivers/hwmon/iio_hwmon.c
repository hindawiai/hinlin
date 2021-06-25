<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Hwmon client क्रम industrial I/O devices
 *
 * Copyright (c) 2011 Jonathan Cameron
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/of.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>

/**
 * काष्ठा iio_hwmon_state - device instance state
 * @channels:		filled with array of channels from iio
 * @num_channels:	number of channels in channels (saves counting twice)
 * @attr_group:		the group of attributes
 * @groups:		null terminated array of attribute groups
 * @attrs:		null terminated array of attribute poपूर्णांकers.
 */
काष्ठा iio_hwmon_state अणु
	काष्ठा iio_channel *channels;
	पूर्णांक num_channels;
	काष्ठा attribute_group attr_group;
	स्थिर काष्ठा attribute_group *groups[2];
	काष्ठा attribute **attrs;
पूर्ण;

/*
 * Assumes that IIO and hwmon operate in the same base units.
 * This is supposed to be true, but needs verअगरication क्रम
 * new channel types.
 */
अटल sमाप_प्रकार iio_hwmon_पढ़ो_val(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	पूर्णांक result;
	पूर्णांक ret;
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा iio_hwmon_state *state = dev_get_drvdata(dev);
	काष्ठा iio_channel *chan = &state->channels[sattr->index];
	क्रमागत iio_chan_type type;

	ret = iio_पढ़ो_channel_processed(chan, &result);
	अगर (ret < 0)
		वापस ret;

	ret = iio_get_channel_type(chan, &type);
	अगर (ret < 0)
		वापस ret;

	अगर (type == IIO_POWER)
		result *= 1000; /* mili-Watts to micro-Watts conversion */

	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल पूर्णांक iio_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_hwmon_state *st;
	काष्ठा sensor_device_attribute *a;
	पूर्णांक ret, i;
	पूर्णांक in_i = 1, temp_i = 1, curr_i = 1, humidity_i = 1, घातer_i = 1;
	क्रमागत iio_chan_type type;
	काष्ठा iio_channel *channels;
	काष्ठा device *hwmon_dev;
	अक्षर *sname;

	channels = devm_iio_channel_get_all(dev);
	अगर (IS_ERR(channels)) अणु
		अगर (PTR_ERR(channels) == -ENODEV)
			वापस -EPROBE_DEFER;
		वापस PTR_ERR(channels);
	पूर्ण

	st = devm_kzalloc(dev, माप(*st), GFP_KERNEL);
	अगर (st == शून्य)
		वापस -ENOMEM;

	st->channels = channels;

	/* count how many attributes we have */
	जबतक (st->channels[st->num_channels].indio_dev)
		st->num_channels++;

	st->attrs = devm_kसुस्मृति(dev,
				 st->num_channels + 1, माप(*st->attrs),
				 GFP_KERNEL);
	अगर (st->attrs == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < st->num_channels; i++) अणु
		स्थिर अक्षर *prefix;
		पूर्णांक n;

		a = devm_kzalloc(dev, माप(*a), GFP_KERNEL);
		अगर (a == शून्य)
			वापस -ENOMEM;

		sysfs_attr_init(&a->dev_attr.attr);
		ret = iio_get_channel_type(&st->channels[i], &type);
		अगर (ret < 0)
			वापस ret;

		चयन (type) अणु
		हाल IIO_VOLTAGE:
			n = in_i++;
			prefix = "in";
			अवरोध;
		हाल IIO_TEMP:
			n = temp_i++;
			prefix = "temp";
			अवरोध;
		हाल IIO_CURRENT:
			n = curr_i++;
			prefix = "curr";
			अवरोध;
		हाल IIO_POWER:
			n = घातer_i++;
			prefix = "power";
			अवरोध;
		हाल IIO_HUMIDITYRELATIVE:
			n = humidity_i++;
			prefix = "humidity";
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		a->dev_attr.attr.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						       "%s%d_input",
						       prefix, n);
		अगर (a->dev_attr.attr.name == शून्य)
			वापस -ENOMEM;

		a->dev_attr.show = iio_hwmon_पढ़ो_val;
		a->dev_attr.attr.mode = 0444;
		a->index = i;
		st->attrs[i] = &a->dev_attr.attr;
	पूर्ण

	st->attr_group.attrs = st->attrs;
	st->groups[0] = &st->attr_group;

	अगर (dev->of_node) अणु
		sname = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%pOFn", dev->of_node);
		अगर (!sname)
			वापस -ENOMEM;
		strreplace(sname, '-', '_');
	पूर्ण अन्यथा अणु
		sname = "iio_hwmon";
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, sname, st,
							   st->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id iio_hwmon_of_match[] = अणु
	अणु .compatible = "iio-hwmon", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iio_hwmon_of_match);

अटल काष्ठा platक्रमm_driver iio_hwmon_driver = अणु
	.driver = अणु
		.name = "iio_hwmon",
		.of_match_table = iio_hwmon_of_match,
	पूर्ण,
	.probe = iio_hwmon_probe,
पूर्ण;

module_platक्रमm_driver(iio_hwmon_driver);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("IIO to hwmon driver");
MODULE_LICENSE("GPL v2");
