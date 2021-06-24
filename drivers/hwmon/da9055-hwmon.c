<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HWMON Driver क्रम Dialog DA9055
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/completion.h>

#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/reg.h>

#घोषणा DA9055_ADCIN_DIV	102
#घोषणा DA9055_VSYS_DIV	85

#घोषणा DA9055_ADC_VSYS	0
#घोषणा DA9055_ADC_ADCIN1	1
#घोषणा DA9055_ADC_ADCIN2	2
#घोषणा DA9055_ADC_ADCIN3	3
#घोषणा DA9055_ADC_TJUNC	4

काष्ठा da9055_hwmon अणु
	काष्ठा da9055	*da9055;
	काष्ठा mutex	hwmon_lock;
	काष्ठा mutex	irq_lock;
	काष्ठा completion करोne;
पूर्ण;

अटल स्थिर अक्षर * स्थिर input_names[] = अणु
	[DA9055_ADC_VSYS]	= "VSYS",
	[DA9055_ADC_ADCIN1]	= "ADC IN1",
	[DA9055_ADC_ADCIN2]	= "ADC IN2",
	[DA9055_ADC_ADCIN3]	= "ADC IN3",
	[DA9055_ADC_TJUNC]	= "CHIP TEMP",
पूर्ण;

अटल स्थिर u8 chan_mux[DA9055_ADC_TJUNC + 1] = अणु
	[DA9055_ADC_VSYS]	= DA9055_ADC_MUX_VSYS,
	[DA9055_ADC_ADCIN1]	= DA9055_ADC_MUX_ADCIN1,
	[DA9055_ADC_ADCIN2]	= DA9055_ADC_MUX_ADCIN2,
	[DA9055_ADC_ADCIN3]	= DA9055_ADC_MUX_ADCIN3,
	[DA9055_ADC_TJUNC]	= DA9055_ADC_MUX_T_SENSE,
पूर्ण;

अटल पूर्णांक da9055_adc_manual_पढ़ो(काष्ठा da9055_hwmon *hwmon,
					अचिन्हित अक्षर channel)
अणु
	पूर्णांक ret;
	अचिन्हित लघु calc_data;
	अचिन्हित लघु data;
	अचिन्हित अक्षर mux_sel;
	काष्ठा da9055 *da9055 = hwmon->da9055;

	अगर (channel > DA9055_ADC_TJUNC)
		वापस -EINVAL;

	mutex_lock(&hwmon->irq_lock);

	/* Selects desired MUX क्रम manual conversion */
	mux_sel = chan_mux[channel] | DA9055_ADC_MAN_CONV;

	ret = da9055_reg_ग_लिखो(da9055, DA9055_REG_ADC_MAN, mux_sel);
	अगर (ret < 0)
		जाओ err;

	/* Wait क्रम an पूर्णांकerrupt */
	अगर (!रुको_क्रम_completion_समयout(&hwmon->करोne,
					msecs_to_jअगरfies(500))) अणु
		dev_err(da9055->dev,
			"timeout waiting for ADC conversion interrupt\n");
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	ret = da9055_reg_पढ़ो(da9055, DA9055_REG_ADC_RES_H);
	अगर (ret < 0)
		जाओ err;

	calc_data = (अचिन्हित लघु)ret;
	data = calc_data << 2;

	ret = da9055_reg_पढ़ो(da9055, DA9055_REG_ADC_RES_L);
	अगर (ret < 0)
		जाओ err;

	calc_data = (अचिन्हित लघु)(ret & DA9055_ADC_LSB_MASK);
	data |= calc_data;

	ret = data;

err:
	mutex_unlock(&hwmon->irq_lock);
	वापस ret;
पूर्ण

अटल irqवापस_t da9055_auxadc_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा da9055_hwmon *hwmon = irq_data;

	complete(&hwmon->करोne);

	वापस IRQ_HANDLED;
पूर्ण

/* Conversion function क्रम VSYS and ADCINx */
अटल अंतरभूत पूर्णांक volt_reg_to_mv(पूर्णांक value, पूर्णांक channel)
अणु
	अगर (channel == DA9055_ADC_VSYS)
		वापस DIV_ROUND_CLOSEST(value * 1000, DA9055_VSYS_DIV) + 2500;
	अन्यथा
		वापस DIV_ROUND_CLOSEST(value * 1000, DA9055_ADCIN_DIV);
पूर्ण

अटल पूर्णांक da9055_enable_स्वतः_mode(काष्ठा da9055 *da9055, पूर्णांक channel)
अणु

	वापस da9055_reg_update(da9055, DA9055_REG_ADC_CONT, 1 << channel,
				1 << channel);

पूर्ण

अटल पूर्णांक da9055_disable_स्वतः_mode(काष्ठा da9055 *da9055, पूर्णांक channel)
अणु

	वापस da9055_reg_update(da9055, DA9055_REG_ADC_CONT, 1 << channel, 0);
पूर्ण

अटल sमाप_प्रकार da9055_स्वतः_ch_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	काष्ठा da9055_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक ret, adc;
	पूर्णांक channel = to_sensor_dev_attr(devattr)->index;

	mutex_lock(&hwmon->hwmon_lock);

	ret = da9055_enable_स्वतः_mode(hwmon->da9055, channel);
	अगर (ret < 0)
		जाओ hwmon_err;

	usleep_range(10000, 10500);

	adc = da9055_reg_पढ़ो(hwmon->da9055, DA9055_REG_VSYS_RES + channel);
	अगर (adc < 0) अणु
		ret = adc;
		जाओ hwmon_err_release;
	पूर्ण

	ret = da9055_disable_स्वतः_mode(hwmon->da9055, channel);
	अगर (ret < 0)
		जाओ hwmon_err;

	mutex_unlock(&hwmon->hwmon_lock);

	वापस प्र_लिखो(buf, "%d\n", volt_reg_to_mv(adc, channel));

hwmon_err_release:
	da9055_disable_स्वतः_mode(hwmon->da9055, channel);
hwmon_err:
	mutex_unlock(&hwmon->hwmon_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार da9055_tjunc_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा da9055_hwmon *hwmon = dev_get_drvdata(dev);
	पूर्णांक tjunc;
	पूर्णांक toffset;

	tjunc = da9055_adc_manual_पढ़ो(hwmon, DA9055_ADC_TJUNC);
	अगर (tjunc < 0)
		वापस tjunc;

	toffset = da9055_reg_पढ़ो(hwmon->da9055, DA9055_REG_T_OFFSET);
	अगर (toffset < 0)
		वापस toffset;

	/*
	 * Degrees celsius = -0.4084 * (ADC_RES - T_OFFSET) + 307.6332
	 * T_OFFSET is a trim value used to improve accuracy of the result
	 */
	वापस प्र_लिखो(buf, "%d\n", DIV_ROUND_CLOSEST(-4084 * (tjunc - toffset)
							+ 3076332, 10000));
पूर्ण

अटल sमाप_प्रकार label_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n",
		       input_names[to_sensor_dev_attr(devattr)->index]);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, da9055_स्वतः_ch, DA9055_ADC_VSYS);
अटल SENSOR_DEVICE_ATTR_RO(in0_label, label, DA9055_ADC_VSYS);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, da9055_स्वतः_ch, DA9055_ADC_ADCIN1);
अटल SENSOR_DEVICE_ATTR_RO(in1_label, label, DA9055_ADC_ADCIN1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, da9055_स्वतः_ch, DA9055_ADC_ADCIN2);
अटल SENSOR_DEVICE_ATTR_RO(in2_label, label, DA9055_ADC_ADCIN2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, da9055_स्वतः_ch, DA9055_ADC_ADCIN3);
अटल SENSOR_DEVICE_ATTR_RO(in3_label, label, DA9055_ADC_ADCIN3);

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, da9055_tjunc, DA9055_ADC_TJUNC);
अटल SENSOR_DEVICE_ATTR_RO(temp1_label, label, DA9055_ADC_TJUNC);

अटल काष्ठा attribute *da9055_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_label.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_label.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_label.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_label.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_label.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(da9055);

अटल पूर्णांक da9055_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9055_hwmon *hwmon;
	काष्ठा device *hwmon_dev;
	पूर्णांक hwmon_irq, ret;

	hwmon = devm_kzalloc(dev, माप(काष्ठा da9055_hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	mutex_init(&hwmon->hwmon_lock);
	mutex_init(&hwmon->irq_lock);

	init_completion(&hwmon->करोne);
	hwmon->da9055 = dev_get_drvdata(pdev->dev.parent);

	hwmon_irq = platक्रमm_get_irq_byname(pdev, "HWMON");
	अगर (hwmon_irq < 0)
		वापस hwmon_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, hwmon_irq,
					शून्य, da9055_auxadc_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"adc-irq", hwmon);
	अगर (ret != 0) अणु
		dev_err(hwmon->da9055->dev, "DA9055 ADC IRQ failed ret=%d\n",
			ret);
		वापस ret;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, "da9055",
							   hwmon,
							   da9055_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver da9055_hwmon_driver = अणु
	.probe = da9055_hwmon_probe,
	.driver = अणु
		.name = "da9055-hwmon",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9055_hwmon_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("DA9055 HWMON driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9055-hwmon");
