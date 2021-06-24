<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Broadcom
 */

#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

/*
 * In stingray thermal IO memory,
 * Total Number of available TMONs MASK is at offset 0
 * temperature रेजिस्टरs BASE is at 4 byte offset.
 * Each TMON temperature रेजिस्टर size is 4.
 */
#घोषणा SR_TMON_TEMP_BASE(id)   ((id) * 0x4)

#घोषणा SR_TMON_MAX_LIST        6

काष्ठा sr_पंचांगon अणु
	काष्ठा thermal_zone_device *tz;
	अचिन्हित पूर्णांक crit_temp;
	अचिन्हित पूर्णांक पंचांगon_id;
	काष्ठा sr_thermal *priv;
पूर्ण;

काष्ठा sr_thermal अणु
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक max_crit_temp;
	काष्ठा sr_पंचांगon पंचांगon[SR_TMON_MAX_LIST];
पूर्ण;

अटल पूर्णांक sr_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा sr_पंचांगon *पंचांगon = data;
	काष्ठा sr_thermal *sr_thermal = पंचांगon->priv;

	*temp = पढ़ोl(sr_thermal->regs + SR_TMON_TEMP_BASE(पंचांगon->पंचांगon_id));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops sr_tz_ops = अणु
	.get_temp = sr_get_temp,
पूर्ण;

अटल पूर्णांक sr_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sr_thermal *sr_thermal;
	काष्ठा sr_पंचांगon *पंचांगon;
	काष्ठा resource *res;
	u32 sr_पंचांगon_list = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	sr_thermal = devm_kzalloc(dev, माप(*sr_thermal), GFP_KERNEL);
	अगर (!sr_thermal)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sr_thermal->regs = (व्योम __iomem *)devm_memremap(&pdev->dev, res->start,
							 resource_size(res),
							 MEMREMAP_WB);
	अगर (IS_ERR(sr_thermal->regs)) अणु
		dev_err(dev, "failed to get io address\n");
		वापस PTR_ERR(sr_thermal->regs);
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "brcm,tmon-mask", &sr_पंचांगon_list);
	अगर (ret)
		वापस ret;

	पंचांगon = sr_thermal->पंचांगon;
	क्रम (i = 0; i < SR_TMON_MAX_LIST; i++, पंचांगon++) अणु
		अगर (!(sr_पंचांगon_list & BIT(i)))
			जारी;

		/* Flush temperature रेजिस्टरs */
		ग_लिखोl(0, sr_thermal->regs + SR_TMON_TEMP_BASE(i));
		पंचांगon->पंचांगon_id = i;
		पंचांगon->priv = sr_thermal;
		पंचांगon->tz = devm_thermal_zone_of_sensor_रेजिस्टर(dev, i, पंचांगon,
								&sr_tz_ops);
		अगर (IS_ERR(पंचांगon->tz))
			वापस PTR_ERR(पंचांगon->tz);

		dev_dbg(dev, "thermal sensor %d registered\n", i);
	पूर्ण
	platक्रमm_set_drvdata(pdev, sr_thermal);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sr_thermal_of_match[] = अणु
	अणु .compatible = "brcm,sr-thermal", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sr_thermal_of_match);

अटल काष्ठा platक्रमm_driver sr_thermal_driver = अणु
	.probe		= sr_thermal_probe,
	.driver = अणु
		.name = "sr-thermal",
		.of_match_table = sr_thermal_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sr_thermal_driver);

MODULE_AUTHOR("Pramod Kumar <pramod.kumar@broadcom.com>");
MODULE_DESCRIPTION("Stingray thermal driver");
MODULE_LICENSE("GPL v2");
