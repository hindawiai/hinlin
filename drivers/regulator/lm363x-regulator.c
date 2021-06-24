<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LM363X Regulator Driver
 *
 * Copyright 2015 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/ti-lmu.h>
#समावेश <linux/mfd/ti-lmu-रेजिस्टर.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/* LM3631 */
#घोषणा LM3631_BOOST_VSEL_MAX		0x25
#घोषणा LM3631_LDO_VSEL_MAX		0x28
#घोषणा LM3631_CONT_VSEL_MAX		0x03
#घोषणा LM3631_VBOOST_MIN		4500000
#घोषणा LM3631_VCONT_MIN		1800000
#घोषणा LM3631_VLDO_MIN			4000000
#घोषणा ENABLE_TIME_USEC		1000

/* LM3632 */
#घोषणा LM3632_BOOST_VSEL_MAX		0x26
#घोषणा LM3632_LDO_VSEL_MAX		0x28
#घोषणा LM3632_VBOOST_MIN		4500000
#घोषणा LM3632_VLDO_MIN			4000000

/* LM36274 */
#घोषणा LM36274_BOOST_VSEL_MAX		0x3f
#घोषणा LM36274_LDO_VSEL_MAX		0x32
#घोषणा LM36274_VOLTAGE_MIN		4000000

/* Common */
#घोषणा LM363X_STEP_50mV		50000
#घोषणा LM363X_STEP_500mV		500000

अटल स्थिर पूर्णांक lकरो_cont_enable_समय[] = अणु
	0, 2000, 5000, 10000, 20000, 50000, 100000, 200000,
पूर्ण;

अटल पूर्णांक lm363x_regulator_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	क्रमागत lm363x_regulator_id id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val, addr, mask;

	चयन (id) अणु
	हाल LM3631_LDO_CONT:
		addr = LM3631_REG_ENTIME_VCONT;
		mask = LM3631_ENTIME_CONT_MASK;
		अवरोध;
	हाल LM3631_LDO_OREF:
		addr = LM3631_REG_ENTIME_VOREF;
		mask = LM3631_ENTIME_MASK;
		अवरोध;
	हाल LM3631_LDO_POS:
		addr = LM3631_REG_ENTIME_VPOS;
		mask = LM3631_ENTIME_MASK;
		अवरोध;
	हाल LM3631_LDO_NEG:
		addr = LM3631_REG_ENTIME_VNEG;
		mask = LM3631_ENTIME_MASK;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (regmap_पढ़ो(rdev->regmap, addr, &val))
		वापस -EINVAL;

	val = (val & mask) >> LM3631_ENTIME_SHIFT;

	अगर (id == LM3631_LDO_CONT)
		वापस lकरो_cont_enable_समय[val];
	अन्यथा
		वापस ENABLE_TIME_USEC * val;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lm363x_boost_voltage_table_ops = अणु
	.list_voltage     = regulator_list_voltage_linear,
	.set_voltage_sel  = regulator_set_voltage_sel_regmap,
	.get_voltage_sel  = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops lm363x_regulator_voltage_table_ops = अणु
	.list_voltage     = regulator_list_voltage_linear,
	.set_voltage_sel  = regulator_set_voltage_sel_regmap,
	.get_voltage_sel  = regulator_get_voltage_sel_regmap,
	.enable           = regulator_enable_regmap,
	.disable          = regulator_disable_regmap,
	.is_enabled       = regulator_is_enabled_regmap,
	.enable_समय      = lm363x_regulator_enable_समय,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc lm363x_regulator_desc[] = अणु
	/* LM3631 */
	अणु
		.name           = "vboost",
		.of_match	= "vboost",
		.id             = LM3631_BOOST,
		.ops            = &lm363x_boost_voltage_table_ops,
		.n_voltages     = LM3631_BOOST_VSEL_MAX + 1,
		.min_uV         = LM3631_VBOOST_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3631_REG_VOUT_BOOST,
		.vsel_mask      = LM3631_VOUT_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_cont",
		.of_match	= "vcont",
		.id             = LM3631_LDO_CONT,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM3631_CONT_VSEL_MAX + 1,
		.min_uV         = LM3631_VCONT_MIN,
		.uV_step        = LM363X_STEP_500mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3631_REG_VOUT_CONT,
		.vsel_mask      = LM3631_VOUT_CONT_MASK,
		.enable_reg     = LM3631_REG_LDO_CTRL2,
		.enable_mask    = LM3631_EN_CONT_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_oref",
		.of_match	= "voref",
		.id             = LM3631_LDO_OREF,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM3631_LDO_VSEL_MAX + 1,
		.min_uV         = LM3631_VLDO_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3631_REG_VOUT_OREF,
		.vsel_mask      = LM3631_VOUT_MASK,
		.enable_reg     = LM3631_REG_LDO_CTRL1,
		.enable_mask    = LM3631_EN_OREF_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_vpos",
		.of_match	= "vpos",
		.id             = LM3631_LDO_POS,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM3631_LDO_VSEL_MAX + 1,
		.min_uV         = LM3631_VLDO_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3631_REG_VOUT_POS,
		.vsel_mask      = LM3631_VOUT_MASK,
		.enable_reg     = LM3631_REG_LDO_CTRL1,
		.enable_mask    = LM3631_EN_VPOS_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_vneg",
		.of_match	= "vneg",
		.id             = LM3631_LDO_NEG,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM3631_LDO_VSEL_MAX + 1,
		.min_uV         = LM3631_VLDO_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3631_REG_VOUT_NEG,
		.vsel_mask      = LM3631_VOUT_MASK,
		.enable_reg     = LM3631_REG_LDO_CTRL1,
		.enable_mask    = LM3631_EN_VNEG_MASK,
	पूर्ण,
	/* LM3632 */
	अणु
		.name           = "vboost",
		.of_match	= "vboost",
		.id             = LM3632_BOOST,
		.ops            = &lm363x_boost_voltage_table_ops,
		.n_voltages     = LM3632_BOOST_VSEL_MAX + 1,
		.min_uV         = LM3632_VBOOST_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3632_REG_VOUT_BOOST,
		.vsel_mask      = LM3632_VOUT_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_vpos",
		.of_match	= "vpos",
		.id             = LM3632_LDO_POS,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM3632_LDO_VSEL_MAX + 1,
		.min_uV         = LM3632_VLDO_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3632_REG_VOUT_POS,
		.vsel_mask      = LM3632_VOUT_MASK,
		.enable_reg     = LM3632_REG_BIAS_CONFIG,
		.enable_mask    = LM3632_EN_VPOS_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_vneg",
		.of_match	= "vneg",
		.id             = LM3632_LDO_NEG,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM3632_LDO_VSEL_MAX + 1,
		.min_uV         = LM3632_VLDO_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM3632_REG_VOUT_NEG,
		.vsel_mask      = LM3632_VOUT_MASK,
		.enable_reg     = LM3632_REG_BIAS_CONFIG,
		.enable_mask    = LM3632_EN_VNEG_MASK,
	पूर्ण,

	/* LM36274 */
	अणु
		.name           = "vboost",
		.of_match	= "vboost",
		.id             = LM36274_BOOST,
		.ops            = &lm363x_boost_voltage_table_ops,
		.n_voltages     = LM36274_BOOST_VSEL_MAX + 1,
		.min_uV         = LM36274_VOLTAGE_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM36274_REG_VOUT_BOOST,
		.vsel_mask      = LM36274_VOUT_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_vpos",
		.of_match	= "vpos",
		.id             = LM36274_LDO_POS,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM36274_LDO_VSEL_MAX + 1,
		.min_uV         = LM36274_VOLTAGE_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM36274_REG_VOUT_POS,
		.vsel_mask      = LM36274_VOUT_MASK,
		.enable_reg     = LM36274_REG_BIAS_CONFIG_1,
		.enable_mask    = LM36274_EN_VPOS_MASK,
	पूर्ण,
	अणु
		.name           = "ldo_vneg",
		.of_match	= "vneg",
		.id             = LM36274_LDO_NEG,
		.ops            = &lm363x_regulator_voltage_table_ops,
		.n_voltages     = LM36274_LDO_VSEL_MAX + 1,
		.min_uV         = LM36274_VOLTAGE_MIN,
		.uV_step        = LM363X_STEP_50mV,
		.type           = REGULATOR_VOLTAGE,
		.owner          = THIS_MODULE,
		.vsel_reg       = LM36274_REG_VOUT_NEG,
		.vsel_mask      = LM36274_VOUT_MASK,
		.enable_reg     = LM36274_REG_BIAS_CONFIG_1,
		.enable_mask    = LM36274_EN_VNEG_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_desc *lm363x_regulator_of_get_enable_gpio(काष्ठा device *dev, पूर्णांक id)
अणु
	/*
	 * Check LCM_EN1/2_GPIO is configured.
	 * Those pins are used क्रम enabling VPOS/VNEG LDOs.
	 * Do not use devm* here: the regulator core takes over the
	 * lअगरecycle management of the GPIO descriptor.
	 */
	चयन (id) अणु
	हाल LM3632_LDO_POS:
	हाल LM36274_LDO_POS:
		वापस gpiod_get_index_optional(dev, "enable", 0,
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	हाल LM3632_LDO_NEG:
	हाल LM36274_LDO_NEG:
		वापस gpiod_get_index_optional(dev, "enable", 1,
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक lm363x_regulator_set_ext_en(काष्ठा regmap *regmap, पूर्णांक id)
अणु
	पूर्णांक ext_en_mask = 0;

	चयन (id) अणु
	हाल LM3632_LDO_POS:
	हाल LM3632_LDO_NEG:
		ext_en_mask = LM3632_EXT_EN_MASK;
		अवरोध;
	हाल LM36274_LDO_POS:
	हाल LM36274_LDO_NEG:
		ext_en_mask = LM36274_EXT_EN_MASK;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस regmap_update_bits(regmap, lm363x_regulator_desc[id].enable_reg,
				 ext_en_mask, ext_en_mask);
पूर्ण

अटल पूर्णांक lm363x_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_lmu *lmu = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regmap *regmap = lmu->regmap;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक id = pdev->id;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक ret;

	cfg.dev = dev;
	cfg.regmap = regmap;

	/*
	 * LM3632 LDOs can be controlled by बाह्यal pin.
	 * Register update is required अगर the pin is used.
	 */
	gpiod = lm363x_regulator_of_get_enable_gpio(dev, id);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);

	अगर (gpiod) अणु
		cfg.ena_gpiod = gpiod;
		ret = lm363x_regulator_set_ext_en(regmap, id);
		अगर (ret) अणु
			gpiod_put(gpiod);
			dev_err(dev, "External pin err: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	rdev = devm_regulator_रेजिस्टर(dev, &lm363x_regulator_desc[id], &cfg);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(dev, "[%d] regulator register err: %d\n", id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lm363x_regulator_driver = अणु
	.probe = lm363x_regulator_probe,
	.driver = अणु
		.name = "lm363x-regulator",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lm363x_regulator_driver);

MODULE_DESCRIPTION("TI LM363X Regulator Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lm363x-regulator");
