<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dove thermal sensor driver
 *
 * Copyright (C) 2013 Andrew Lunn <andrew@lunn.ch>
 */
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#घोषणा DOVE_THERMAL_TEMP_OFFSET	1
#घोषणा DOVE_THERMAL_TEMP_MASK		0x1FF

/* Dove Thermal Manager Control and Status Register */
#घोषणा PMU_TM_DISABLE_OFFS		0
#घोषणा PMU_TM_DISABLE_MASK		(0x1 << PMU_TM_DISABLE_OFFS)

/* Dove Theraml Diode Control 0 Register */
#घोषणा PMU_TDC0_SW_RST_MASK		(0x1 << 1)
#घोषणा PMU_TDC0_SEL_VCAL_OFFS		5
#घोषणा PMU_TDC0_SEL_VCAL_MASK		(0x3 << PMU_TDC0_SEL_VCAL_OFFS)
#घोषणा PMU_TDC0_REF_CAL_CNT_OFFS	11
#घोषणा PMU_TDC0_REF_CAL_CNT_MASK	(0x1FF << PMU_TDC0_REF_CAL_CNT_OFFS)
#घोषणा PMU_TDC0_AVG_NUM_OFFS		25
#घोषणा PMU_TDC0_AVG_NUM_MASK		(0x7 << PMU_TDC0_AVG_NUM_OFFS)

/* Dove Thermal Diode Control 1 Register */
#घोषणा PMU_TEMP_DIOD_CTRL1_REG		0x04
#घोषणा PMU_TDC1_TEMP_VALID_MASK	(0x1 << 10)

/* Dove Thermal Sensor Dev Structure */
काष्ठा करोve_thermal_priv अणु
	व्योम __iomem *sensor;
	व्योम __iomem *control;
पूर्ण;

अटल पूर्णांक करोve_init_sensor(स्थिर काष्ठा करोve_thermal_priv *priv)
अणु
	u32 reg;
	u32 i;

	/* Configure the Diode Control Register #0 */
	reg = पढ़ोl_relaxed(priv->control);

	/* Use average of 2 */
	reg &= ~PMU_TDC0_AVG_NUM_MASK;
	reg |= (0x1 << PMU_TDC0_AVG_NUM_OFFS);

	/* Reference calibration value */
	reg &= ~PMU_TDC0_REF_CAL_CNT_MASK;
	reg |= (0x0F1 << PMU_TDC0_REF_CAL_CNT_OFFS);

	/* Set the high level reference क्रम calibration */
	reg &= ~PMU_TDC0_SEL_VCAL_MASK;
	reg |= (0x2 << PMU_TDC0_SEL_VCAL_OFFS);
	ग_लिखोl(reg, priv->control);

	/* Reset the sensor */
	reg = पढ़ोl_relaxed(priv->control);
	ग_लिखोl((reg | PMU_TDC0_SW_RST_MASK), priv->control);
	ग_लिखोl(reg, priv->control);

	/* Enable the sensor */
	reg = पढ़ोl_relaxed(priv->sensor);
	reg &= ~PMU_TM_DISABLE_MASK;
	ग_लिखोl(reg, priv->sensor);

	/* Poll the sensor क्रम the first पढ़ोing */
	क्रम (i = 0; i < 1000000; i++) अणु
		reg = पढ़ोl_relaxed(priv->sensor);
		अगर (reg & DOVE_THERMAL_TEMP_MASK)
			अवरोध;
	पूर्ण

	अगर (i == 1000000)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_get_temp(काष्ठा thermal_zone_device *thermal,
			  पूर्णांक *temp)
अणु
	अचिन्हित दीर्घ reg;
	काष्ठा करोve_thermal_priv *priv = thermal->devdata;

	/* Valid check */
	reg = पढ़ोl_relaxed(priv->control + PMU_TEMP_DIOD_CTRL1_REG);
	अगर ((reg & PMU_TDC1_TEMP_VALID_MASK) == 0x0) अणु
		dev_err(&thermal->device,
			"Temperature sensor reading not valid\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Calculate temperature. According to Marvell पूर्णांकernal
	 * करोcumentation the क्रमmula क्रम this is:
	 * Celsius = (322-reg)/1.3625
	 */
	reg = पढ़ोl_relaxed(priv->sensor);
	reg = (reg >> DOVE_THERMAL_TEMP_OFFSET) & DOVE_THERMAL_TEMP_MASK;
	*temp = ((3220000000UL - (10000000UL * reg)) / 13625);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops ops = अणु
	.get_temp = करोve_get_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id करोve_thermal_id_table[] = अणु
	अणु .compatible = "marvell,dove-thermal" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक करोve_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *thermal = शून्य;
	काष्ठा करोve_thermal_priv *priv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->sensor = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->sensor))
		वापस PTR_ERR(priv->sensor);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->control = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->control))
		वापस PTR_ERR(priv->control);

	ret = करोve_init_sensor(priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize sensor\n");
		वापस ret;
	पूर्ण

	thermal = thermal_zone_device_रेजिस्टर("dove_thermal", 0, 0,
					       priv, &ops, शून्य, 0, 0);
	अगर (IS_ERR(thermal)) अणु
		dev_err(&pdev->dev,
			"Failed to register thermal zone device\n");
		वापस PTR_ERR(thermal);
	पूर्ण

	ret = thermal_zone_device_enable(thermal);
	अगर (ret) अणु
		thermal_zone_device_unरेजिस्टर(thermal);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, thermal);

	वापस 0;
पूर्ण

अटल पूर्णांक करोve_thermal_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *करोve_thermal =
		platक्रमm_get_drvdata(pdev);

	thermal_zone_device_unरेजिस्टर(करोve_thermal);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(of, करोve_thermal_id_table);

अटल काष्ठा platक्रमm_driver करोve_thermal_driver = अणु
	.probe = करोve_thermal_probe,
	.हटाओ = करोve_thermal_निकास,
	.driver = अणु
		.name = "dove_thermal",
		.of_match_table = करोve_thermal_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(करोve_thermal_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_DESCRIPTION("Dove thermal driver");
MODULE_LICENSE("GPL");
