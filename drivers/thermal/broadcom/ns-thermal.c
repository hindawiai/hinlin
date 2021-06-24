<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#घोषणा PVTMON_CONTROL0					0x00
#घोषणा PVTMON_CONTROL0_SEL_MASK			0x0000000e
#घोषणा PVTMON_CONTROL0_SEL_TEMP_MONITOR		0x00000000
#घोषणा PVTMON_CONTROL0_SEL_TEST_MODE			0x0000000e
#घोषणा PVTMON_STATUS					0x08

काष्ठा ns_thermal अणु
	काष्ठा thermal_zone_device *tz;
	व्योम __iomem *pvपंचांगon;
पूर्ण;

अटल पूर्णांक ns_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा ns_thermal *ns_thermal = data;
	पूर्णांक offset = thermal_zone_get_offset(ns_thermal->tz);
	पूर्णांक slope = thermal_zone_get_slope(ns_thermal->tz);
	u32 val;

	val = पढ़ोl(ns_thermal->pvपंचांगon + PVTMON_CONTROL0);
	अगर ((val & PVTMON_CONTROL0_SEL_MASK) != PVTMON_CONTROL0_SEL_TEMP_MONITOR) अणु
		/* Clear current mode selection */
		val &= ~PVTMON_CONTROL0_SEL_MASK;

		/* Set temp monitor mode (it's the शेष actually) */
		val |= PVTMON_CONTROL0_SEL_TEMP_MONITOR;

		ग_लिखोl(val, ns_thermal->pvपंचांगon + PVTMON_CONTROL0);
	पूर्ण

	val = पढ़ोl(ns_thermal->pvपंचांगon + PVTMON_STATUS);
	*temp = slope * val + offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops ns_thermal_ops = अणु
	.get_temp = ns_thermal_get_temp,
पूर्ण;

अटल पूर्णांक ns_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ns_thermal *ns_thermal;

	ns_thermal = devm_kzalloc(dev, माप(*ns_thermal), GFP_KERNEL);
	अगर (!ns_thermal)
		वापस -ENOMEM;

	ns_thermal->pvपंचांगon = of_iomap(dev_of_node(dev), 0);
	अगर (WARN_ON(!ns_thermal->pvपंचांगon))
		वापस -ENOENT;

	ns_thermal->tz = devm_thermal_zone_of_sensor_रेजिस्टर(dev, 0,
							      ns_thermal,
							      &ns_thermal_ops);
	अगर (IS_ERR(ns_thermal->tz)) अणु
		iounmap(ns_thermal->pvपंचांगon);
		वापस PTR_ERR(ns_thermal->tz);
	पूर्ण

	platक्रमm_set_drvdata(pdev, ns_thermal);

	वापस 0;
पूर्ण

अटल पूर्णांक ns_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ns_thermal *ns_thermal = platक्रमm_get_drvdata(pdev);

	iounmap(ns_thermal->pvपंचांगon);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ns_thermal_of_match[] = अणु
	अणु .compatible = "brcm,ns-thermal", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ns_thermal_of_match);

अटल काष्ठा platक्रमm_driver ns_thermal_driver = अणु
	.probe		= ns_thermal_probe,
	.हटाओ		= ns_thermal_हटाओ,
	.driver = अणु
		.name = "ns-thermal",
		.of_match_table = ns_thermal_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ns_thermal_driver);

MODULE_AUTHOR("Rafaध Miधecki <rafal@milecki.pl>");
MODULE_DESCRIPTION("Northstar thermal driver");
MODULE_LICENSE("GPL v2");
