<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Lantiq cpu temperature sensor driver
 *
 * Copyright (C) 2017 Florian Eckert <fe@dev.tdt.de>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश <lantiq_soc.h>

/* gphy1 configuration रेजिस्टर contains cpu temperature */
#घोषणा CGU_GPHY1_CR   0x0040
#घोषणा CGU_TEMP_PD    BIT(19)

अटल व्योम ltq_cputemp_enable(व्योम)
अणु
	ltq_cgu_w32(ltq_cgu_r32(CGU_GPHY1_CR) | CGU_TEMP_PD, CGU_GPHY1_CR);
पूर्ण

अटल व्योम ltq_cputemp_disable(व्योम *data)
अणु
	ltq_cgu_w32(ltq_cgu_r32(CGU_GPHY1_CR) & ~CGU_TEMP_PD, CGU_GPHY1_CR);
पूर्ण

अटल पूर्णांक ltq_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	पूर्णांक value;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		/* get the temperature including one decimal place */
		value = (ltq_cgu_r32(CGU_GPHY1_CR) >> 9) & 0x01FF;
		value = value * 5;
		/* range -38 to +154 तओC, रेजिस्टर value zero is -38.0 तओC */
		value -= 380;
		/* scale temp to millidegree */
		value = value * 100;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	*temp = value;
	वापस 0;
पूर्ण

अटल umode_t ltq_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel)
अणु
	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *ltq_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ltq_hwmon_ops = अणु
	.is_visible = ltq_is_visible,
	.पढ़ो = ltq_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ltq_chip_info = अणु
	.ops = &ltq_hwmon_ops,
	.info = ltq_info,
पूर्ण;

अटल पूर्णांक ltq_cputemp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *hwmon_dev;
	पूर्णांक err = 0;

	/* available on vr9 v1.2 SoCs only */
	अगर (ltq_soc_type() != SOC_TYPE_VR9_2)
		वापस -ENODEV;

	err = devm_add_action(&pdev->dev, ltq_cputemp_disable, शून्य);
	अगर (err)
		वापस err;

	ltq_cputemp_enable();

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
							 "ltq_cputemp",
							 शून्य,
							 &ltq_chip_info,
							 शून्य);

	अगर (IS_ERR(hwmon_dev)) अणु
		dev_err(&pdev->dev, "Failed to register as hwmon device");
		वापस PTR_ERR(hwmon_dev);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा of_device_id ltq_cputemp_match[] = अणु
	अणु .compatible = "lantiq,cputemp" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_cputemp_match);

अटल काष्ठा platक्रमm_driver ltq_cputemp_driver = अणु
	.probe = ltq_cputemp_probe,
	.driver = अणु
		.name = "ltq-cputemp",
		.of_match_table = ltq_cputemp_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ltq_cputemp_driver);

MODULE_AUTHOR("Florian Eckert <fe@dev.tdt.de>");
MODULE_DESCRIPTION("Lantiq cpu temperature sensor driver");
MODULE_LICENSE("GPL");
