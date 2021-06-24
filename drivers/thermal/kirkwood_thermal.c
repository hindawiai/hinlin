<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kirkwood thermal sensor driver
 *
 * Copyright (C) 2012 Nobuhiro Iwamatsu <iwamatsu@nigauri.org>
 */
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#घोषणा KIRKWOOD_THERMAL_VALID_OFFSET	9
#घोषणा KIRKWOOD_THERMAL_VALID_MASK	0x1
#घोषणा KIRKWOOD_THERMAL_TEMP_OFFSET	10
#घोषणा KIRKWOOD_THERMAL_TEMP_MASK	0x1FF

/* Kirkwood Thermal Sensor Dev Structure */
काष्ठा kirkwood_thermal_priv अणु
	व्योम __iomem *sensor;
पूर्ण;

अटल पूर्णांक kirkwood_get_temp(काष्ठा thermal_zone_device *thermal,
			  पूर्णांक *temp)
अणु
	अचिन्हित दीर्घ reg;
	काष्ठा kirkwood_thermal_priv *priv = thermal->devdata;

	reg = पढ़ोl_relaxed(priv->sensor);

	/* Valid check */
	अगर (!((reg >> KIRKWOOD_THERMAL_VALID_OFFSET) &
	    KIRKWOOD_THERMAL_VALID_MASK)) अणु
		dev_err(&thermal->device,
			"Temperature sensor reading not valid\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Calculate temperature. According to Marvell पूर्णांकernal
	 * करोcumentation the क्रमmula क्रम this is:
	 * Celsius = (322-reg)/1.3625
	 */
	reg = (reg >> KIRKWOOD_THERMAL_TEMP_OFFSET) &
		KIRKWOOD_THERMAL_TEMP_MASK;
	*temp = ((3220000000UL - (10000000UL * reg)) / 13625);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops ops = अणु
	.get_temp = kirkwood_get_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id kirkwood_thermal_id_table[] = अणु
	अणु .compatible = "marvell,kirkwood-thermal" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक kirkwood_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *thermal = शून्य;
	काष्ठा kirkwood_thermal_priv *priv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->sensor = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->sensor))
		वापस PTR_ERR(priv->sensor);

	thermal = thermal_zone_device_रेजिस्टर("kirkwood_thermal", 0, 0,
					       priv, &ops, शून्य, 0, 0);
	अगर (IS_ERR(thermal)) अणु
		dev_err(&pdev->dev,
			"Failed to register thermal zone device\n");
		वापस PTR_ERR(thermal);
	पूर्ण
	ret = thermal_zone_device_enable(thermal);
	अगर (ret) अणु
		thermal_zone_device_unरेजिस्टर(thermal);
		dev_err(&pdev->dev, "Failed to enable thermal zone device\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, thermal);

	वापस 0;
पूर्ण

अटल पूर्णांक kirkwood_thermal_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *kirkwood_thermal =
		platक्रमm_get_drvdata(pdev);

	thermal_zone_device_unरेजिस्टर(kirkwood_thermal);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(of, kirkwood_thermal_id_table);

अटल काष्ठा platक्रमm_driver kirkwood_thermal_driver = अणु
	.probe = kirkwood_thermal_probe,
	.हटाओ = kirkwood_thermal_निकास,
	.driver = अणु
		.name = "kirkwood_thermal",
		.of_match_table = kirkwood_thermal_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kirkwood_thermal_driver);

MODULE_AUTHOR("Nobuhiro Iwamatsu <iwamatsu@nigauri.org>");
MODULE_DESCRIPTION("kirkwood thermal driver");
MODULE_LICENSE("GPL");
