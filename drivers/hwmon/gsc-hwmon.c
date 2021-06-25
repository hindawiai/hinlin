<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Gateworks System Controller Hardware Monitor module
 *
 * Copyright (C) 2020 Gateworks Corporation
 */
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/mfd/gsc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/gsc_hwmon.h>

#घोषणा GSC_HWMON_MAX_TEMP_CH	16
#घोषणा GSC_HWMON_MAX_IN_CH	16
#घोषणा GSC_HWMON_MAX_FAN_CH	16

#घोषणा GSC_HWMON_RESOLUTION	12
#घोषणा GSC_HWMON_VREF		2500

काष्ठा gsc_hwmon_data अणु
	काष्ठा gsc_dev *gsc;
	काष्ठा gsc_hwmon_platक्रमm_data *pdata;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा gsc_hwmon_channel *temp_ch[GSC_HWMON_MAX_TEMP_CH];
	स्थिर काष्ठा gsc_hwmon_channel *in_ch[GSC_HWMON_MAX_IN_CH];
	स्थिर काष्ठा gsc_hwmon_channel *fan_ch[GSC_HWMON_MAX_FAN_CH];
	u32 temp_config[GSC_HWMON_MAX_TEMP_CH + 1];
	u32 in_config[GSC_HWMON_MAX_IN_CH + 1];
	u32 fan_config[GSC_HWMON_MAX_FAN_CH + 1];
	काष्ठा hwmon_channel_info temp_info;
	काष्ठा hwmon_channel_info in_info;
	काष्ठा hwmon_channel_info fan_info;
	स्थिर काष्ठा hwmon_channel_info *info[4];
	काष्ठा hwmon_chip_info chip;
पूर्ण;

अटल काष्ठा regmap_bus gsc_hwmon_regmap_bus = अणु
	.reg_पढ़ो = gsc_पढ़ो,
	.reg_ग_लिखो = gsc_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gsc_hwmon_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल sमाप_प्रकार pwm_स्वतः_poपूर्णांक_temp_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	काष्ठा gsc_hwmon_data *hwmon = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	u8 reg = hwmon->pdata->fan_base + (2 * attr->index);
	u8 regs[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(hwmon->regmap, reg, regs, 2);
	अगर (ret)
		वापस ret;

	ret = regs[0] | regs[1] << 8;
	वापस प्र_लिखो(buf, "%d\n", ret * 10);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_poपूर्णांक_temp_store(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gsc_hwmon_data *hwmon = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	u8 reg = hwmon->pdata->fan_base + (2 * attr->index);
	u8 regs[2];
	दीर्घ temp;
	पूर्णांक err;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 10000);
	temp = DIV_ROUND_CLOSEST(temp, 10);

	regs[0] = temp & 0xff;
	regs[1] = (temp >> 8) & 0xff;
	err = regmap_bulk_ग_लिखो(hwmon->regmap, reg, regs, 2);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_poपूर्णांक_pwm_show(काष्ठा device *dev,
				       काष्ठा device_attribute *devattr,
				       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	वापस प्र_लिखो(buf, "%d\n", 255 * (50 + (attr->index * 10)) / 100);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक1_pwm, pwm_स्वतः_poपूर्णांक_pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक1_temp, pwm_स्वतः_poपूर्णांक_temp, 0);

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक2_pwm, pwm_स्वतः_poपूर्णांक_pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक2_temp, pwm_स्वतः_poपूर्णांक_temp, 1);

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक3_pwm, pwm_स्वतः_poपूर्णांक_pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक3_temp, pwm_स्वतः_poपूर्णांक_temp, 2);

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक4_pwm, pwm_स्वतः_poपूर्णांक_pwm, 3);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक4_temp, pwm_स्वतः_poपूर्णांक_temp, 3);

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक5_pwm, pwm_स्वतः_poपूर्णांक_pwm, 4);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक5_temp, pwm_स्वतः_poपूर्णांक_temp, 4);

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक6_pwm, pwm_स्वतः_poपूर्णांक_pwm, 5);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक6_temp, pwm_स्वतः_poपूर्णांक_temp, 5);

अटल काष्ठा attribute *gsc_hwmon_attributes[] = अणु
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक6_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक6_temp.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gsc_hwmon_group = अणु
	.attrs = gsc_hwmon_attributes,
पूर्ण;
__ATTRIBUTE_GROUPS(gsc_hwmon);

अटल पूर्णांक
gsc_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
	       पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा gsc_hwmon_data *hwmon = dev_get_drvdata(dev);
	स्थिर काष्ठा gsc_hwmon_channel *ch;
	पूर्णांक sz, ret;
	दीर्घ पंचांगp;
	u8 buf[3];

	चयन (type) अणु
	हाल hwmon_in:
		ch = hwmon->in_ch[channel];
		अवरोध;
	हाल hwmon_temp:
		ch = hwmon->temp_ch[channel];
		अवरोध;
	हाल hwmon_fan:
		ch = hwmon->fan_ch[channel];
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	sz = (ch->mode == mode_voltage_24bit) ? 3 : 2;
	ret = regmap_bulk_पढ़ो(hwmon->regmap, ch->reg, buf, sz);
	अगर (ret)
		वापस ret;

	पंचांगp = 0;
	जबतक (sz-- > 0)
		पंचांगp |= (buf[sz] << (8 * sz));

	चयन (ch->mode) अणु
	हाल mode_temperature:
		अगर (पंचांगp > 0x8000)
			पंचांगp -= 0xffff;
		पंचांगp *= 100; /* convert to millidegrees celsius */
		अवरोध;
	हाल mode_voltage_raw:
		पंचांगp = clamp_val(पंचांगp, 0, BIT(GSC_HWMON_RESOLUTION));
		/* scale based on ref voltage and ADC resolution */
		पंचांगp *= GSC_HWMON_VREF;
		पंचांगp >>= GSC_HWMON_RESOLUTION;
		/* scale based on optional voltage भागider */
		अगर (ch->vभाग[0] && ch->vभाग[1]) अणु
			पंचांगp *= (ch->vभाग[0] + ch->vभाग[1]);
			पंचांगp /= ch->vभाग[1];
		पूर्ण
		/* adjust by uV offset */
		पंचांगp += ch->mvoffset;
		अवरोध;
	हाल mode_fan:
		पंचांगp *= 30; /* convert to revolutions per minute */
		अवरोध;
	हाल mode_voltage_24bit:
	हाल mode_voltage_16bit:
		/* no adjusपंचांगent needed */
		अवरोध;
	पूर्ण

	*val = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक
gsc_hwmon_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel, स्थिर अक्षर **buf)
अणु
	काष्ठा gsc_hwmon_data *hwmon = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_in:
		*buf = hwmon->in_ch[channel]->name;
		अवरोध;
	हाल hwmon_temp:
		*buf = hwmon->temp_ch[channel]->name;
		अवरोध;
	हाल hwmon_fan:
		*buf = hwmon->fan_ch[channel]->name;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल umode_t
gsc_hwmon_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type, u32 attr,
		     पूर्णांक ch)
अणु
	वापस 0444;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops gsc_hwmon_ops = अणु
	.is_visible = gsc_hwmon_is_visible,
	.पढ़ो = gsc_hwmon_पढ़ो,
	.पढ़ो_string = gsc_hwmon_पढ़ो_string,
पूर्ण;

अटल काष्ठा gsc_hwmon_platक्रमm_data *
gsc_hwmon_get_devtree_pdata(काष्ठा device *dev)
अणु
	काष्ठा gsc_hwmon_platक्रमm_data *pdata;
	काष्ठा gsc_hwmon_channel *ch;
	काष्ठा fwnode_handle *child;
	काष्ठा device_node *fan;
	पूर्णांक nchannels;

	nchannels = device_get_child_node_count(dev);
	अगर (nchannels == 0)
		वापस ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(dev,
			     माप(*pdata) + nchannels * माप(*ch),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);
	ch = (काष्ठा gsc_hwmon_channel *)(pdata + 1);
	pdata->channels = ch;
	pdata->nchannels = nchannels;

	/* fan controller base address */
	fan = of_find_compatible_node(dev->parent->of_node, शून्य, "gw,gsc-fan");
	अगर (fan && of_property_पढ़ो_u32(fan, "reg", &pdata->fan_base)) अणु
		dev_err(dev, "fan node without base\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* allocate काष्ठाures क्रम channels and count instances of each type */
	device_क्रम_each_child_node(dev, child) अणु
		अगर (fwnode_property_पढ़ो_string(child, "label", &ch->name)) अणु
			dev_err(dev, "channel without label\n");
			fwnode_handle_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (fwnode_property_पढ़ो_u32(child, "reg", &ch->reg)) अणु
			dev_err(dev, "channel without reg\n");
			fwnode_handle_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (fwnode_property_पढ़ो_u32(child, "gw,mode", &ch->mode)) अणु
			dev_err(dev, "channel without mode\n");
			fwnode_handle_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (ch->mode > mode_max) अणु
			dev_err(dev, "invalid channel mode\n");
			fwnode_handle_put(child);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		अगर (!fwnode_property_पढ़ो_u32(child,
					      "gw,voltage-offset-microvolt",
					      &ch->mvoffset))
			ch->mvoffset /= 1000;
		fwnode_property_पढ़ो_u32_array(child,
					       "gw,voltage-divider-ohms",
					       ch->vभाग, ARRAY_SIZE(ch->vभाग));
		ch++;
	पूर्ण

	वापस pdata;
पूर्ण

अटल पूर्णांक gsc_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gsc_dev *gsc = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा gsc_hwmon_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा gsc_hwmon_data *hwmon;
	स्थिर काष्ठा attribute_group **groups;
	पूर्णांक i, i_in, i_temp, i_fan;

	अगर (!pdata) अणु
		pdata = gsc_hwmon_get_devtree_pdata(dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	hwmon = devm_kzalloc(dev, माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;
	hwmon->gsc = gsc;
	hwmon->pdata = pdata;

	hwmon->regmap = devm_regmap_init(dev, &gsc_hwmon_regmap_bus,
					 gsc->i2c_hwmon,
					 &gsc_hwmon_regmap_config);
	अगर (IS_ERR(hwmon->regmap))
		वापस PTR_ERR(hwmon->regmap);

	क्रम (i = 0, i_in = 0, i_temp = 0, i_fan = 0; i < hwmon->pdata->nchannels; i++) अणु
		स्थिर काष्ठा gsc_hwmon_channel *ch = &pdata->channels[i];

		चयन (ch->mode) अणु
		हाल mode_temperature:
			अगर (i_temp == GSC_HWMON_MAX_TEMP_CH) अणु
				dev_err(gsc->dev, "too many temp channels\n");
				वापस -EINVAL;
			पूर्ण
			hwmon->temp_ch[i_temp] = ch;
			hwmon->temp_config[i_temp] = HWMON_T_INPUT |
						     HWMON_T_LABEL;
			i_temp++;
			अवरोध;
		हाल mode_fan:
			अगर (i_fan == GSC_HWMON_MAX_FAN_CH) अणु
				dev_err(gsc->dev, "too many fan channels\n");
				वापस -EINVAL;
			पूर्ण
			hwmon->fan_ch[i_fan] = ch;
			hwmon->fan_config[i_fan] = HWMON_F_INPUT |
						   HWMON_F_LABEL;
			i_fan++;
			अवरोध;
		हाल mode_voltage_24bit:
		हाल mode_voltage_16bit:
		हाल mode_voltage_raw:
			अगर (i_in == GSC_HWMON_MAX_IN_CH) अणु
				dev_err(gsc->dev, "too many input channels\n");
				वापस -EINVAL;
			पूर्ण
			hwmon->in_ch[i_in] = ch;
			hwmon->in_config[i_in] =
				HWMON_I_INPUT | HWMON_I_LABEL;
			i_in++;
			अवरोध;
		शेष:
			dev_err(gsc->dev, "invalid mode: %d\n", ch->mode);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* setup config काष्ठाures */
	hwmon->chip.ops = &gsc_hwmon_ops;
	hwmon->chip.info = hwmon->info;
	hwmon->info[0] = &hwmon->temp_info;
	hwmon->info[1] = &hwmon->in_info;
	hwmon->info[2] = &hwmon->fan_info;
	hwmon->temp_info.type = hwmon_temp;
	hwmon->temp_info.config = hwmon->temp_config;
	hwmon->in_info.type = hwmon_in;
	hwmon->in_info.config = hwmon->in_config;
	hwmon->fan_info.type = hwmon_fan;
	hwmon->fan_info.config = hwmon->fan_config;

	groups = pdata->fan_base ? gsc_hwmon_groups : शून्य;
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev,
							 KBUILD_MODNAME, hwmon,
							 &hwmon->chip, groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id gsc_hwmon_of_match[] = अणु
	अणु .compatible = "gw,gsc-adc", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver gsc_hwmon_driver = अणु
	.driver = अणु
		.name = "gsc-hwmon",
		.of_match_table = gsc_hwmon_of_match,
	पूर्ण,
	.probe = gsc_hwmon_probe,
पूर्ण;

module_platक्रमm_driver(gsc_hwmon_driver);

MODULE_AUTHOR("Tim Harvey <tharvey@gateworks.com>");
MODULE_DESCRIPTION("GSC hardware monitor driver");
MODULE_LICENSE("GPL v2");
