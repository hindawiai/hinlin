<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HWMON Driver क्रम Dialog DA9052
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>
#समावेश <linux/regulator/consumer.h>

काष्ठा da9052_hwmon अणु
	काष्ठा da9052		*da9052;
	काष्ठा mutex		hwmon_lock;
	bool			tsi_as_adc;
	पूर्णांक			tsiref_mv;
	काष्ठा regulator	*tsiref;
	काष्ठा completion	tsiकरोne;
पूर्ण;

अटल स्थिर अक्षर * स्थिर input_names[] = अणु
	[DA9052_ADC_VDDOUT]	=	"VDDOUT",
	[DA9052_ADC_ICH]	=	"CHARGING CURRENT",
	[DA9052_ADC_TBAT]	=	"BATTERY TEMP",
	[DA9052_ADC_VBAT]	=	"BATTERY VOLTAGE",
	[DA9052_ADC_IN4]	=	"ADC IN4",
	[DA9052_ADC_IN5]	=	"ADC IN5",
	[DA9052_ADC_IN6]	=	"ADC IN6",
	[DA9052_ADC_TSI_XP]	=	"ADC TS X+",
	[DA9052_ADC_TSI_YP]	=	"ADC TS Y+",
	[DA9052_ADC_TSI_XN]	=	"ADC TS X-",
	[DA9052_ADC_TSI_YN]	=	"ADC TS Y-",
	[DA9052_ADC_TJUNC]	=	"BATTERY JUNCTION TEMP",
	[DA9052_ADC_VBBAT]	=	"BACK-UP BATTERY VOLTAGE",
पूर्ण;

/* Conversion function क्रम VDDOUT and VBAT */
अटल अंतरभूत पूर्णांक volt_reg_to_mv(पूर्णांक value)
अणु
	वापस DIV_ROUND_CLOSEST(value * 2000, 1023) + 2500;
पूर्ण

/* Conversion function क्रम ADC channels 4, 5 and 6 */
अटल अंतरभूत पूर्णांक input_reg_to_mv(पूर्णांक value)
अणु
	वापस DIV_ROUND_CLOSEST(value * 2500, 1023);
पूर्ण

/* Conversion function क्रम VBBAT */
अटल अंतरभूत पूर्णांक vbbat_reg_to_mv(पूर्णांक value)
अणु
	वापस DIV_ROUND_CLOSEST(value * 5000, 1023);
पूर्ण

अटल अंतरभूत पूर्णांक input_tsireg_to_mv(काष्ठा da9052_hwmon *hwmon, पूर्णांक value)
अणु
	वापस DIV_ROUND_CLOSEST(value * hwmon->tsiref_mv, 1023);
पूर्ण

अटल अंतरभूत पूर्णांक da9052_enable_vdकरोut_channel(काष्ठा da9052 *da9052)
अणु
	वापस da9052_reg_update(da9052, DA9052_ADC_CONT_REG,
				 DA9052_ADCCONT_AUTOVDDEN,
				 DA9052_ADCCONT_AUTOVDDEN);
पूर्ण

अटल अंतरभूत पूर्णांक da9052_disable_vdकरोut_channel(काष्ठा da9052 *da9052)
अणु
	वापस da9052_reg_update(da9052, DA9052_ADC_CONT_REG,
				 DA9052_ADCCONT_AUTOVDDEN, 0);
पूर्ण

अटल sमाप_प्रकार da9052_vdकरोut_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक ret, vdd;

	mutex_lock(&hwmon->hwmon_lock);

	ret = da9052_enable_vdकरोut_channel(hwmon->da9052);
	अगर (ret < 0)
		जाओ hwmon_err;

	vdd = da9052_reg_पढ़ो(hwmon->da9052, DA9052_VDD_RES_REG);
	अगर (vdd < 0) अणु
		ret = vdd;
		जाओ hwmon_err_release;
	पूर्ण

	ret = da9052_disable_vdकरोut_channel(hwmon->da9052);
	अगर (ret < 0)
		जाओ hwmon_err;

	mutex_unlock(&hwmon->hwmon_lock);
	वापस प्र_लिखो(buf, "%d\n", volt_reg_to_mv(vdd));

hwmon_err_release:
	da9052_disable_vdकरोut_channel(hwmon->da9052);
hwmon_err:
	mutex_unlock(&hwmon->hwmon_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार da9052_ich_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = da9052_reg_पढ़ो(hwmon->da9052, DA9052_ICHG_AV_REG);
	अगर (ret < 0)
		वापस ret;

	/* Equivalent to 3.9mA/bit in रेजिस्टर ICHG_AV */
	वापस प्र_लिखो(buf, "%d\n", DIV_ROUND_CLOSEST(ret * 39, 10));
पूर्ण

अटल sमाप_प्रकार da9052_tbat_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", da9052_adc_पढ़ो_temp(hwmon->da9052));
पूर्ण

अटल sमाप_प्रकार da9052_vbat_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = da9052_adc_manual_पढ़ो(hwmon->da9052, DA9052_ADC_VBAT);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", volt_reg_to_mv(ret));
पूर्ण

अटल sमाप_प्रकार da9052_misc_channel_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(devattr)->index;
	पूर्णांक ret;

	ret = da9052_adc_manual_पढ़ो(hwmon->da9052, channel);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", input_reg_to_mv(ret));
पूर्ण

अटल पूर्णांक da9052_request_tsi_पढ़ो(काष्ठा da9052_hwmon *hwmon, पूर्णांक channel)
अणु
	u8 val = DA9052_TSICONTB_TSIMAN;

	चयन (channel) अणु
	हाल DA9052_ADC_TSI_XP:
		val |= DA9052_TSICONTB_TSIMUX_XP;
		अवरोध;
	हाल DA9052_ADC_TSI_YP:
		val |= DA9052_TSICONTB_TSIMUX_YP;
		अवरोध;
	हाल DA9052_ADC_TSI_XN:
		val |= DA9052_TSICONTB_TSIMUX_XN;
		अवरोध;
	हाल DA9052_ADC_TSI_YN:
		val |= DA9052_TSICONTB_TSIMUX_YN;
		अवरोध;
	पूर्ण

	वापस da9052_reg_ग_लिखो(hwmon->da9052, DA9052_TSI_CONT_B_REG, val);
पूर्ण

अटल पूर्णांक da9052_get_tsi_result(काष्ठा da9052_hwmon *hwmon, पूर्णांक channel)
अणु
	u8 regs[3];
	पूर्णांक msb, lsb, err;

	/* block पढ़ो to aव्योम separation of MSB and LSB */
	err = da9052_group_पढ़ो(hwmon->da9052, DA9052_TSI_X_MSB_REG,
				ARRAY_SIZE(regs), regs);
	अगर (err)
		वापस err;

	चयन (channel) अणु
	हाल DA9052_ADC_TSI_XP:
	हाल DA9052_ADC_TSI_XN:
		msb = regs[0] << DA9052_TSILSB_TSIXL_BITS;
		lsb = regs[2] & DA9052_TSILSB_TSIXL;
		lsb >>= DA9052_TSILSB_TSIXL_SHIFT;
		अवरोध;
	हाल DA9052_ADC_TSI_YP:
	हाल DA9052_ADC_TSI_YN:
		msb = regs[1] << DA9052_TSILSB_TSIYL_BITS;
		lsb = regs[2] & DA9052_TSILSB_TSIYL;
		lsb >>= DA9052_TSILSB_TSIYL_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस msb | lsb;
पूर्ण


अटल sमाप_प्रकार __da9052_पढ़ो_tsi(काष्ठा device *dev, पूर्णांक channel)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक ret;

	reinit_completion(&hwmon->tsiकरोne);

	ret = da9052_request_tsi_पढ़ो(hwmon, channel);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम an conversion करोne पूर्णांकerrupt */
	अगर (!रुको_क्रम_completion_समयout(&hwmon->tsiकरोne,
					 msecs_to_jअगरfies(500)))
		वापस -ETIMEDOUT;

	वापस da9052_get_tsi_result(hwmon, channel);
पूर्ण

अटल sमाप_प्रकार da9052_tsi_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(devattr)->index;
	पूर्णांक ret;

	mutex_lock(&hwmon->da9052->auxadc_lock);
	ret = __da9052_पढ़ो_tsi(dev, channel);
	mutex_unlock(&hwmon->da9052->auxadc_lock);

	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", input_tsireg_to_mv(hwmon, ret));
पूर्ण

अटल sमाप_प्रकार da9052_tjunc_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक tjunc;
	पूर्णांक toffset;

	tjunc = da9052_reg_पढ़ो(hwmon->da9052, DA9052_TJUNC_RES_REG);
	अगर (tjunc < 0)
		वापस tjunc;

	toffset = da9052_reg_पढ़ो(hwmon->da9052, DA9052_T_OFFSET_REG);
	अगर (toffset < 0)
		वापस toffset;

	/*
	 * Degrees celsius = 1.708 * (TJUNC_RES - T_OFFSET) - 108.8
	 * T_OFFSET is a trim value used to improve accuracy of the result
	 */
	वापस प्र_लिखो(buf, "%d\n", 1708 * (tjunc - toffset) - 108800);
पूर्ण

अटल sमाप_प्रकार da9052_vbbat_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = da9052_adc_manual_पढ़ो(hwmon->da9052, DA9052_ADC_VBBAT);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", vbbat_reg_to_mv(ret));
पूर्ण

अटल sमाप_प्रकार label_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n",
		       input_names[to_sensor_dev_attr(devattr)->index]);
पूर्ण

अटल umode_t da9052_channel_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा da9052_hwmon *hwmon = dev_get_drvdata(dev);
	काष्ठा device_attribute *dattr = container_of(attr,
				काष्ठा device_attribute, attr);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(dattr);

	अगर (!hwmon->tsi_as_adc) अणु
		चयन (sattr->index) अणु
		हाल DA9052_ADC_TSI_XP:
		हाल DA9052_ADC_TSI_YP:
		हाल DA9052_ADC_TSI_XN:
		हाल DA9052_ADC_TSI_YN:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, da9052_vdकरोut, DA9052_ADC_VDDOUT);
अटल SENSOR_DEVICE_ATTR_RO(in0_label, label, DA9052_ADC_VDDOUT);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, da9052_vbat, DA9052_ADC_VBAT);
अटल SENSOR_DEVICE_ATTR_RO(in3_label, label, DA9052_ADC_VBAT);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, da9052_misc_channel, DA9052_ADC_IN4);
अटल SENSOR_DEVICE_ATTR_RO(in4_label, label, DA9052_ADC_IN4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, da9052_misc_channel, DA9052_ADC_IN5);
अटल SENSOR_DEVICE_ATTR_RO(in5_label, label, DA9052_ADC_IN5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, da9052_misc_channel, DA9052_ADC_IN6);
अटल SENSOR_DEVICE_ATTR_RO(in6_label, label, DA9052_ADC_IN6);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, da9052_vbbat, DA9052_ADC_VBBAT);
अटल SENSOR_DEVICE_ATTR_RO(in9_label, label, DA9052_ADC_VBBAT);

अटल SENSOR_DEVICE_ATTR_RO(in70_input, da9052_tsi, DA9052_ADC_TSI_XP);
अटल SENSOR_DEVICE_ATTR_RO(in70_label, label, DA9052_ADC_TSI_XP);
अटल SENSOR_DEVICE_ATTR_RO(in71_input, da9052_tsi, DA9052_ADC_TSI_XN);
अटल SENSOR_DEVICE_ATTR_RO(in71_label, label, DA9052_ADC_TSI_XN);
अटल SENSOR_DEVICE_ATTR_RO(in72_input, da9052_tsi, DA9052_ADC_TSI_YP);
अटल SENSOR_DEVICE_ATTR_RO(in72_label, label, DA9052_ADC_TSI_YP);
अटल SENSOR_DEVICE_ATTR_RO(in73_input, da9052_tsi, DA9052_ADC_TSI_YN);
अटल SENSOR_DEVICE_ATTR_RO(in73_label, label, DA9052_ADC_TSI_YN);

अटल SENSOR_DEVICE_ATTR_RO(curr1_input, da9052_ich, DA9052_ADC_ICH);
अटल SENSOR_DEVICE_ATTR_RO(curr1_label, label, DA9052_ADC_ICH);

अटल SENSOR_DEVICE_ATTR_RO(temp2_input, da9052_tbat, DA9052_ADC_TBAT);
अटल SENSOR_DEVICE_ATTR_RO(temp2_label, label, DA9052_ADC_TBAT);
अटल SENSOR_DEVICE_ATTR_RO(temp8_input, da9052_tjunc, DA9052_ADC_TJUNC);
अटल SENSOR_DEVICE_ATTR_RO(temp8_label, label, DA9052_ADC_TJUNC);

अटल काष्ठा attribute *da9052_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_label.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_label.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_label.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_label.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_label.dev_attr.attr,
	&sensor_dev_attr_in70_input.dev_attr.attr,
	&sensor_dev_attr_in70_label.dev_attr.attr,
	&sensor_dev_attr_in71_input.dev_attr.attr,
	&sensor_dev_attr_in71_label.dev_attr.attr,
	&sensor_dev_attr_in72_input.dev_attr.attr,
	&sensor_dev_attr_in72_label.dev_attr.attr,
	&sensor_dev_attr_in73_input.dev_attr.attr,
	&sensor_dev_attr_in73_label.dev_attr.attr,
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in9_label.dev_attr.attr,
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_label.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_label.dev_attr.attr,
	&sensor_dev_attr_temp8_input.dev_attr.attr,
	&sensor_dev_attr_temp8_label.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group da9052_group = अणु
	.attrs = da9052_attrs,
	.is_visible = da9052_channel_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(da9052);

अटल irqवापस_t da9052_tsi_datardy_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9052_hwmon *hwmon = data;

	complete(&hwmon->tsiकरोne);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9052_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9052_hwmon *hwmon;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	hwmon = devm_kzalloc(dev, माप(काष्ठा da9052_hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hwmon);

	mutex_init(&hwmon->hwmon_lock);
	hwmon->da9052 = dev_get_drvdata(pdev->dev.parent);

	init_completion(&hwmon->tsiकरोne);

	hwmon->tsi_as_adc =
		device_property_पढ़ो_bool(pdev->dev.parent, "dlg,tsi-as-adc");

	अगर (hwmon->tsi_as_adc) अणु
		hwmon->tsiref = devm_regulator_get(pdev->dev.parent, "tsiref");
		अगर (IS_ERR(hwmon->tsiref)) अणु
			err = PTR_ERR(hwmon->tsiref);
			dev_err(&pdev->dev, "failed to get tsiref: %d", err);
			वापस err;
		पूर्ण

		err = regulator_enable(hwmon->tsiref);
		अगर (err)
			वापस err;

		hwmon->tsiref_mv = regulator_get_voltage(hwmon->tsiref);
		अगर (hwmon->tsiref_mv < 0) अणु
			err = hwmon->tsiref_mv;
			जाओ निकास_regulator;
		पूर्ण

		/* convert from microvolt (DT) to millivolt (hwmon) */
		hwmon->tsiref_mv /= 1000;

		/* TSIREF limits from datasheet */
		अगर (hwmon->tsiref_mv < 1800 || hwmon->tsiref_mv > 2600) अणु
			dev_err(hwmon->da9052->dev, "invalid TSIREF voltage: %d",
				hwmon->tsiref_mv);
			err = -ENXIO;
			जाओ निकास_regulator;
		पूर्ण

		/* disable touchscreen features */
		da9052_reg_ग_लिखो(hwmon->da9052, DA9052_TSI_CONT_A_REG, 0x00);

		/* Sample every 1ms */
		da9052_reg_update(hwmon->da9052, DA9052_ADC_CONT_REG,
					  DA9052_ADCCONT_ADCMODE,
					  DA9052_ADCCONT_ADCMODE);

		err = da9052_request_irq(hwmon->da9052, DA9052_IRQ_TSIREADY,
					 "tsiready-irq", da9052_tsi_datardy_irq,
					 hwmon);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to register TSIRDY IRQ: %d",
				err);
			जाओ निकास_regulator;
		पूर्ण
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, "da9052",
							   hwmon,
							   da9052_groups);
	err = PTR_ERR_OR_ZERO(hwmon_dev);
	अगर (err)
		जाओ निकास_irq;

	वापस 0;

निकास_irq:
	अगर (hwmon->tsi_as_adc)
		da9052_मुक्त_irq(hwmon->da9052, DA9052_IRQ_TSIREADY, hwmon);
निकास_regulator:
	अगर (hwmon->tsiref)
		regulator_disable(hwmon->tsiref);

	वापस err;
पूर्ण

अटल पूर्णांक da9052_hwmon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_hwmon *hwmon = platक्रमm_get_drvdata(pdev);

	अगर (hwmon->tsi_as_adc) अणु
		da9052_मुक्त_irq(hwmon->da9052, DA9052_IRQ_TSIREADY, hwmon);
		regulator_disable(hwmon->tsiref);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_hwmon_driver = अणु
	.probe = da9052_hwmon_probe,
	.हटाओ = da9052_hwmon_हटाओ,
	.driver = अणु
		.name = "da9052-hwmon",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9052_hwmon_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("DA9052 HWMON driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-hwmon");
