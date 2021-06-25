<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Junction temperature thermal driver क्रम Maxim Max77620.
 *
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *	   Mallikarjun Kasoju <mkasoju@nvidia.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/max77620.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#घोषणा MAX77620_NORMAL_OPERATING_TEMP	100000
#घोषणा MAX77620_TJALARM1_TEMP		120000
#घोषणा MAX77620_TJALARM2_TEMP		140000

काष्ठा max77620_therm_info अणु
	काष्ठा device			*dev;
	काष्ठा regmap			*rmap;
	काष्ठा thermal_zone_device	*tz_device;
	पूर्णांक				irq_tjalarm1;
	पूर्णांक				irq_tjalarm2;
पूर्ण;

/**
 * max77620_thermal_पढ़ो_temp: Read PMIC die temperatue.
 * @data:	Device specअगरic data.
 * @temp:	Temperature in millidegrees Celsius
 *
 * The actual temperature of PMIC die is not available from PMIC.
 * PMIC only tells the status अगर it has crossed or not the threshold level
 * of 120degC or 140degC.
 * If threshold has not been crossed then assume die temperature as 100degC
 * अन्यथा 120degC or 140deG based on the PMIC die temp threshold status.
 *
 * Return 0 on success otherwise error number to show reason of failure.
 */

अटल पूर्णांक max77620_thermal_पढ़ो_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा max77620_therm_info *mtherm = data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(mtherm->rmap, MAX77620_REG_STATLBT, &val);
	अगर (ret < 0) अणु
		dev_err(mtherm->dev, "Failed to read STATLBT: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (val & MAX77620_IRQ_TJALRM2_MASK)
		*temp = MAX77620_TJALARM2_TEMP;
	अन्यथा अगर (val & MAX77620_IRQ_TJALRM1_MASK)
		*temp = MAX77620_TJALARM1_TEMP;
	अन्यथा
		*temp = MAX77620_NORMAL_OPERATING_TEMP;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops max77620_thermal_ops = अणु
	.get_temp = max77620_thermal_पढ़ो_temp,
पूर्ण;

अटल irqवापस_t max77620_thermal_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77620_therm_info *mtherm = data;

	अगर (irq == mtherm->irq_tjalarm1)
		dev_warn(mtherm->dev, "Junction Temp Alarm1(120C) occurred\n");
	अन्यथा अगर (irq == mtherm->irq_tjalarm2)
		dev_crit(mtherm->dev, "Junction Temp Alarm2(140C) occurred\n");

	thermal_zone_device_update(mtherm->tz_device,
				   THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max77620_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77620_therm_info *mtherm;
	पूर्णांक ret;

	mtherm = devm_kzalloc(&pdev->dev, माप(*mtherm), GFP_KERNEL);
	अगर (!mtherm)
		वापस -ENOMEM;

	mtherm->irq_tjalarm1 = platक्रमm_get_irq(pdev, 0);
	mtherm->irq_tjalarm2 = platक्रमm_get_irq(pdev, 1);
	अगर ((mtherm->irq_tjalarm1 < 0) || (mtherm->irq_tjalarm2 < 0)) अणु
		dev_err(&pdev->dev, "Alarm irq number not available\n");
		वापस -EINVAL;
	पूर्ण

	mtherm->dev = &pdev->dev;
	mtherm->rmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!mtherm->rmap) अणु
		dev_err(&pdev->dev, "Failed to get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * The reference taken to the parent's node which will be balanced on
	 * reprobe or on platक्रमm-device release.
	 */
	device_set_of_node_from_dev(&pdev->dev, pdev->dev.parent);

	mtherm->tz_device = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0,
				mtherm, &max77620_thermal_ops);
	अगर (IS_ERR(mtherm->tz_device)) अणु
		ret = PTR_ERR(mtherm->tz_device);
		dev_err(&pdev->dev, "Failed to register thermal zone: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, mtherm->irq_tjalarm1, शून्य,
					max77620_thermal_irq,
					IRQF_ONESHOT | IRQF_SHARED,
					dev_name(&pdev->dev), mtherm);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request irq1: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, mtherm->irq_tjalarm2, शून्य,
					max77620_thermal_irq,
					IRQF_ONESHOT | IRQF_SHARED,
					dev_name(&pdev->dev), mtherm);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request irq2: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mtherm);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device_id max77620_thermal_devtype[] = अणु
	अणु .name = "max77620-thermal", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77620_thermal_devtype);

अटल काष्ठा platक्रमm_driver max77620_thermal_driver = अणु
	.driver = अणु
		.name = "max77620-thermal",
	पूर्ण,
	.probe = max77620_thermal_probe,
	.id_table = max77620_thermal_devtype,
पूर्ण;

module_platक्रमm_driver(max77620_thermal_driver);

MODULE_DESCRIPTION("Max77620 Junction temperature Thermal driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_AUTHOR("Mallikarjun Kasoju <mkasoju@nvidia.com>");
MODULE_LICENSE("GPL v2");
