<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Broadcom AVS RO thermal sensor driver
 *
 * based on brcmstb_thermal
 *
 * Copyright (C) 2020 Stefan Wahren
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

#समावेश "../thermal_hwmon.h"

#घोषणा AVS_RO_TEMP_STATUS		0x200
#घोषणा AVS_RO_TEMP_STATUS_VALID_MSK	(BIT(16) | BIT(10))
#घोषणा AVS_RO_TEMP_STATUS_DATA_MSK	GENMASK(9, 0)

काष्ठा bcm2711_thermal_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा thermal_zone_device *thermal;
पूर्ण;

अटल पूर्णांक bcm2711_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा bcm2711_thermal_priv *priv = data;
	पूर्णांक slope = thermal_zone_get_slope(priv->thermal);
	पूर्णांक offset = thermal_zone_get_offset(priv->thermal);
	u32 val;
	पूर्णांक ret;
	दीर्घ t;

	ret = regmap_पढ़ो(priv->regmap, AVS_RO_TEMP_STATUS, &val);
	अगर (ret)
		वापस ret;

	अगर (!(val & AVS_RO_TEMP_STATUS_VALID_MSK))
		वापस -EIO;

	val &= AVS_RO_TEMP_STATUS_DATA_MSK;

	/* Convert a HW code to a temperature पढ़ोing (millidegree celsius) */
	t = slope * val + offset;

	*temp = t < 0 ? 0 : t;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops bcm2711_thermal_of_ops = अणु
	.get_temp	= bcm2711_get_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm2711_thermal_id_table[] = अणु
	अणु .compatible = "brcm,bcm2711-thermal" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2711_thermal_id_table);

अटल पूर्णांक bcm2711_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *thermal;
	काष्ठा bcm2711_thermal_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* get regmap from syscon node */
	parent = of_get_parent(dev->of_node); /* parent should be syscon node */
	regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(dev, "failed to get regmap: %d\n", ret);
		वापस ret;
	पूर्ण
	priv->regmap = regmap;

	thermal = devm_thermal_zone_of_sensor_रेजिस्टर(dev, 0, priv,
						       &bcm2711_thermal_of_ops);
	अगर (IS_ERR(thermal)) अणु
		ret = PTR_ERR(thermal);
		dev_err(dev, "could not register sensor: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->thermal = thermal;

	thermal->tzp->no_hwmon = false;
	वापस thermal_add_hwmon_sysfs(thermal);
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2711_thermal_driver = अणु
	.probe = bcm2711_thermal_probe,
	.driver = अणु
		.name = "bcm2711_thermal",
		.of_match_table = bcm2711_thermal_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2711_thermal_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefan Wahren");
MODULE_DESCRIPTION("Broadcom AVS RO thermal sensor driver");
