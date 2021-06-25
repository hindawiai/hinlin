<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Thermal Sensor Driver
 *
 * Copyright (C) 2017 Huan Biao <huan.biao@amlogic.com>
 * Copyright (C) 2019 Guillaume La Roque <glaroque@baylibre.com>
 *
 * Register value to celsius temperature क्रमmulas:
 *	Read_Val	    m * U
 * U = ---------, Uptat = ---------
 *	2^16		  1 + n * U
 *
 * Temperature = A * ( Uptat + u_efuse / 2^16 )- B
 *
 *  A B m n : calibration parameters
 *  u_efuse : fused calibration value, it's a चिन्हित 16 bits value
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"
#समावेश "thermal_hwmon.h"

#घोषणा TSENSOR_CFG_REG1			0x4
	#घोषणा TSENSOR_CFG_REG1_RSET_VBG	BIT(12)
	#घोषणा TSENSOR_CFG_REG1_RSET_ADC	BIT(11)
	#घोषणा TSENSOR_CFG_REG1_VCM_EN		BIT(10)
	#घोषणा TSENSOR_CFG_REG1_VBG_EN		BIT(9)
	#घोषणा TSENSOR_CFG_REG1_OUT_CTL	BIT(6)
	#घोषणा TSENSOR_CFG_REG1_FILTER_EN	BIT(5)
	#घोषणा TSENSOR_CFG_REG1_DEM_EN		BIT(3)
	#घोषणा TSENSOR_CFG_REG1_CH_SEL		GENMASK(1, 0)
	#घोषणा TSENSOR_CFG_REG1_ENABLE		\
		(TSENSOR_CFG_REG1_FILTER_EN |	\
		 TSENSOR_CFG_REG1_VCM_EN |	\
		 TSENSOR_CFG_REG1_VBG_EN |	\
		 TSENSOR_CFG_REG1_DEM_EN |	\
		 TSENSOR_CFG_REG1_CH_SEL)

#घोषणा TSENSOR_STAT0			0x40

#घोषणा TSENSOR_STAT9			0x64

#घोषणा TSENSOR_READ_TEMP_MASK		GENMASK(15, 0)
#घोषणा TSENSOR_TEMP_MASK		GENMASK(11, 0)

#घोषणा TSENSOR_TRIM_SIGN_MASK		BIT(15)
#घोषणा TSENSOR_TRIM_TEMP_MASK		GENMASK(14, 0)
#घोषणा TSENSOR_TRIM_VERSION_MASK	GENMASK(31, 24)

#घोषणा TSENSOR_TRIM_VERSION(_version)	\
	FIELD_GET(TSENSOR_TRIM_VERSION_MASK, _version)

#घोषणा TSENSOR_TRIM_CALIB_VALID_MASK	(GENMASK(3, 2) | BIT(7))

#घोषणा TSENSOR_CALIB_OFFSET	1
#घोषणा TSENSOR_CALIB_SHIFT	4

/**
 * काष्ठा amlogic_thermal_soc_calib_data
 * @A: calibration parameters
 * @B: calibration parameters
 * @m: calibration parameters
 * @n: calibration parameters
 *
 * This काष्ठाure is required क्रम configuration of amlogic thermal driver.
 */
काष्ठा amlogic_thermal_soc_calib_data अणु
	पूर्णांक A;
	पूर्णांक B;
	पूर्णांक m;
	पूर्णांक n;
पूर्ण;

/**
 * काष्ठा amlogic_thermal_data
 * @u_efuse_off: रेजिस्टर offset to पढ़ो fused calibration value
 * @calibration_parameters: calibration parameters काष्ठाure poपूर्णांकer
 * @regmap_config: regmap config क्रम the device
 * This काष्ठाure is required क्रम configuration of amlogic thermal driver.
 */
काष्ठा amlogic_thermal_data अणु
	पूर्णांक u_efuse_off;
	स्थिर काष्ठा amlogic_thermal_soc_calib_data *calibration_parameters;
	स्थिर काष्ठा regmap_config *regmap_config;
पूर्ण;

काष्ठा amlogic_thermal अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा amlogic_thermal_data *data;
	काष्ठा regmap *regmap;
	काष्ठा regmap *sec_ao_map;
	काष्ठा clk *clk;
	काष्ठा thermal_zone_device *tzd;
	u32 trim_info;
पूर्ण;

/*
 * Calculate a temperature value from a temperature code.
 * The unit of the temperature is degree milliCelsius.
 */
अटल पूर्णांक amlogic_thermal_code_to_millicelsius(काष्ठा amlogic_thermal *pdata,
						पूर्णांक temp_code)
अणु
	स्थिर काष्ठा amlogic_thermal_soc_calib_data *param =
					pdata->data->calibration_parameters;
	पूर्णांक temp;
	s64 factor, Uptat, uefuse;

	uefuse = pdata->trim_info & TSENSOR_TRIM_SIGN_MASK ?
			     ~(pdata->trim_info & TSENSOR_TRIM_TEMP_MASK) + 1 :
			     (pdata->trim_info & TSENSOR_TRIM_TEMP_MASK);

	factor = param->n * temp_code;
	factor = भाग_s64(factor, 100);

	Uptat = temp_code * param->m;
	Uptat = भाग_s64(Uptat, 100);
	Uptat = Uptat * BIT(16);
	Uptat = भाग_s64(Uptat, BIT(16) + factor);

	temp = (Uptat + uefuse) * param->A;
	temp = भाग_s64(temp, BIT(16));
	temp = (temp - param->B) * 100;

	वापस temp;
पूर्ण

अटल पूर्णांक amlogic_thermal_initialize(काष्ठा amlogic_thermal *pdata)
अणु
	पूर्णांक ret = 0;
	पूर्णांक ver;

	regmap_पढ़ो(pdata->sec_ao_map, pdata->data->u_efuse_off,
		    &pdata->trim_info);

	ver = TSENSOR_TRIM_VERSION(pdata->trim_info);

	अगर ((ver & TSENSOR_TRIM_CALIB_VALID_MASK) == 0) अणु
		ret = -EINVAL;
		dev_err(&pdata->pdev->dev,
			"tsensor thermal calibration not supported: 0x%x!\n",
			ver);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक amlogic_thermal_enable(काष्ठा amlogic_thermal *data)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(data->clk);
	अगर (ret)
		वापस ret;

	regmap_update_bits(data->regmap, TSENSOR_CFG_REG1,
			   TSENSOR_CFG_REG1_ENABLE, TSENSOR_CFG_REG1_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक amlogic_thermal_disable(काष्ठा amlogic_thermal *data)
अणु
	regmap_update_bits(data->regmap, TSENSOR_CFG_REG1,
			   TSENSOR_CFG_REG1_ENABLE, 0);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक amlogic_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	अचिन्हित पूर्णांक tval;
	काष्ठा amlogic_thermal *pdata = data;

	अगर (!data)
		वापस -EINVAL;

	regmap_पढ़ो(pdata->regmap, TSENSOR_STAT0, &tval);
	*temp =
	   amlogic_thermal_code_to_millicelsius(pdata,
						tval & TSENSOR_READ_TEMP_MASK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops amlogic_thermal_ops = अणु
	.get_temp	= amlogic_thermal_get_temp,
पूर्ण;

अटल स्थिर काष्ठा regmap_config amlogic_thermal_regmap_config_g12a = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = TSENSOR_STAT9,
पूर्ण;

अटल स्थिर काष्ठा amlogic_thermal_soc_calib_data amlogic_thermal_g12a = अणु
	.A = 9411,
	.B = 3159,
	.m = 424,
	.n = 324,
पूर्ण;

अटल स्थिर काष्ठा amlogic_thermal_data amlogic_thermal_g12a_cpu_param = अणु
	.u_efuse_off = 0x128,
	.calibration_parameters = &amlogic_thermal_g12a,
	.regmap_config = &amlogic_thermal_regmap_config_g12a,
पूर्ण;

अटल स्थिर काष्ठा amlogic_thermal_data amlogic_thermal_g12a_ddr_param = अणु
	.u_efuse_off = 0xf0,
	.calibration_parameters = &amlogic_thermal_g12a,
	.regmap_config = &amlogic_thermal_regmap_config_g12a,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_amlogic_thermal_match[] = अणु
	अणु
		.compatible = "amlogic,g12a-ddr-thermal",
		.data = &amlogic_thermal_g12a_ddr_param,
	पूर्ण,
	अणु
		.compatible = "amlogic,g12a-cpu-thermal",
		.data = &amlogic_thermal_g12a_cpu_param,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_amlogic_thermal_match);

अटल पूर्णांक amlogic_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amlogic_thermal *pdata;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	पूर्णांक ret;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->data = of_device_get_match_data(dev);
	pdata->pdev = pdev;
	platक्रमm_set_drvdata(pdev, pdata);

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	pdata->regmap = devm_regmap_init_mmio(dev, base,
					      pdata->data->regmap_config);
	अगर (IS_ERR(pdata->regmap))
		वापस PTR_ERR(pdata->regmap);

	pdata->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(pdata->clk)) अणु
		अगर (PTR_ERR(pdata->clk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(pdata->clk);
	पूर्ण

	pdata->sec_ao_map = syscon_regmap_lookup_by_phandle
		(pdev->dev.of_node, "amlogic,ao-secure");
	अगर (IS_ERR(pdata->sec_ao_map)) अणु
		dev_err(dev, "syscon regmap lookup failed.\n");
		वापस PTR_ERR(pdata->sec_ao_map);
	पूर्ण

	pdata->tzd = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev,
							  0,
							  pdata,
							  &amlogic_thermal_ops);
	अगर (IS_ERR(pdata->tzd)) अणु
		ret = PTR_ERR(pdata->tzd);
		dev_err(dev, "Failed to register tsensor: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (devm_thermal_add_hwmon_sysfs(pdata->tzd))
		dev_warn(&pdev->dev, "Failed to add hwmon sysfs attributes\n");

	ret = amlogic_thermal_initialize(pdata);
	अगर (ret)
		वापस ret;

	ret = amlogic_thermal_enable(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक amlogic_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amlogic_thermal *data = platक्रमm_get_drvdata(pdev);

	वापस amlogic_thermal_disable(data);
पूर्ण

अटल पूर्णांक __maybe_unused amlogic_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा amlogic_thermal *data = dev_get_drvdata(dev);

	वापस amlogic_thermal_disable(data);
पूर्ण

अटल पूर्णांक __maybe_unused amlogic_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा amlogic_thermal *data = dev_get_drvdata(dev);

	वापस amlogic_thermal_enable(data);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(amlogic_thermal_pm_ops,
			 amlogic_thermal_suspend, amlogic_thermal_resume);

अटल काष्ठा platक्रमm_driver amlogic_thermal_driver = अणु
	.driver = अणु
		.name		= "amlogic_thermal",
		.pm		= &amlogic_thermal_pm_ops,
		.of_match_table = of_amlogic_thermal_match,
	पूर्ण,
	.probe	= amlogic_thermal_probe,
	.हटाओ	= amlogic_thermal_हटाओ,
पूर्ण;

module_platक्रमm_driver(amlogic_thermal_driver);

MODULE_AUTHOR("Guillaume La Roque <glaroque@baylibre.com>");
MODULE_DESCRIPTION("Amlogic thermal driver");
MODULE_LICENSE("GPL v2");
