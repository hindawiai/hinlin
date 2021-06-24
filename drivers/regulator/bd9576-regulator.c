<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ROHM Semiconductors
// ROHM BD9576MUF/BD9573MUF regulator driver

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rohm-bd957x.h>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

#घोषणा BD957X_VOUTS1_VOLT	3300000
#घोषणा BD957X_VOUTS4_BASE_VOLT	1030000
#घोषणा BD957X_VOUTS34_NUM_VOLT	32

अटल पूर्णांक vout1_volt_table[] = अणु5000000, 4900000, 4800000, 4700000, 4600000,
				 4500000, 4500000, 4500000, 5000000, 5100000,
				 5200000, 5300000, 5400000, 5500000, 5500000,
				 5500000पूर्ण;

अटल पूर्णांक vout2_volt_table[] = अणु1800000, 1780000, 1760000, 1740000, 1720000,
				 1700000, 1680000, 1660000, 1800000, 1820000,
				 1840000, 1860000, 1880000, 1900000, 1920000,
				 1940000पूर्ण;

अटल पूर्णांक voutl1_volt_table[] = अणु2500000, 2540000, 2580000, 2620000, 2660000,
				  2700000, 2740000, 2780000, 2500000, 2460000,
				  2420000, 2380000, 2340000, 2300000, 2260000,
				  2220000पूर्ण;

काष्ठा bd957x_regulator_data अणु
	काष्ठा regulator_desc desc;
	पूर्णांक base_voltage;
पूर्ण;

अटल पूर्णांक bd957x_vout34_list_voltage(काष्ठा regulator_dev *rdev,
				      अचिन्हित पूर्णांक selector)
अणु
	स्थिर काष्ठा regulator_desc *desc = rdev->desc;
	पूर्णांक multiplier = selector & desc->vsel_mask & 0x7f;
	पूर्णांक tune;

	/* VOUT3 and 4 has 10mV step */
	tune = multiplier * 10000;

	अगर (!(selector & 0x80))
		वापस desc->fixed_uV - tune;

	वापस desc->fixed_uV + tune;
पूर्ण

अटल पूर्णांक bd957x_list_voltage(काष्ठा regulator_dev *rdev,
			       अचिन्हित पूर्णांक selector)
अणु
	स्थिर काष्ठा regulator_desc *desc = rdev->desc;
	पूर्णांक index = selector & desc->vsel_mask & 0x7f;

	अगर (!(selector & 0x80))
		index += desc->n_voltages/2;

	अगर (index >= desc->n_voltages)
		वापस -EINVAL;

	वापस desc->volt_table[index];
पूर्ण

अटल स्थिर काष्ठा regulator_ops bd957x_vout34_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = bd957x_vout34_list_voltage,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd957X_vouts1_regulator_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd957x_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = bd957x_list_voltage,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल काष्ठा bd957x_regulator_data bd9576_regulators[] = अणु
	अणु
		.desc = अणु
			.name = "VD50",
			.of_match = of_match_ptr("regulator-vd50"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD957X_VD50,
			.type = REGULATOR_VOLTAGE,
			.ops = &bd957x_ops,
			.volt_table = &vout1_volt_table[0],
			.n_voltages = ARRAY_SIZE(vout1_volt_table),
			.vsel_reg = BD957X_REG_VOUT1_TUNE,
			.vsel_mask = BD957X_MASK_VOUT1_TUNE,
			.enable_reg = BD957X_REG_POW_TRIGGER1,
			.enable_mask = BD957X_REGULATOR_EN_MASK,
			.enable_val = BD957X_REGULATOR_DIS_VAL,
			.enable_is_inverted = true,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "VD18",
			.of_match = of_match_ptr("regulator-vd18"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD957X_VD18,
			.type = REGULATOR_VOLTAGE,
			.ops = &bd957x_ops,
			.volt_table = &vout2_volt_table[0],
			.n_voltages = ARRAY_SIZE(vout2_volt_table),
			.vsel_reg = BD957X_REG_VOUT2_TUNE,
			.vsel_mask = BD957X_MASK_VOUT2_TUNE,
			.enable_reg = BD957X_REG_POW_TRIGGER2,
			.enable_mask = BD957X_REGULATOR_EN_MASK,
			.enable_val = BD957X_REGULATOR_DIS_VAL,
			.enable_is_inverted = true,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "VDDDR",
			.of_match = of_match_ptr("regulator-vdddr"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD957X_VDDDR,
			.ops = &bd957x_vout34_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD957X_VOUTS34_NUM_VOLT,
			.vsel_reg = BD957X_REG_VOUT3_TUNE,
			.vsel_mask = BD957X_MASK_VOUT3_TUNE,
			.enable_reg = BD957X_REG_POW_TRIGGER3,
			.enable_mask = BD957X_REGULATOR_EN_MASK,
			.enable_val = BD957X_REGULATOR_DIS_VAL,
			.enable_is_inverted = true,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "VD10",
			.of_match = of_match_ptr("regulator-vd10"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD957X_VD10,
			.ops = &bd957x_vout34_ops,
			.type = REGULATOR_VOLTAGE,
			.fixed_uV = BD957X_VOUTS4_BASE_VOLT,
			.n_voltages = BD957X_VOUTS34_NUM_VOLT,
			.vsel_reg = BD957X_REG_VOUT4_TUNE,
			.vsel_mask = BD957X_MASK_VOUT4_TUNE,
			.enable_reg = BD957X_REG_POW_TRIGGER4,
			.enable_mask = BD957X_REGULATOR_EN_MASK,
			.enable_val = BD957X_REGULATOR_DIS_VAL,
			.enable_is_inverted = true,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "VOUTL1",
			.of_match = of_match_ptr("regulator-voutl1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD957X_VOUTL1,
			.ops = &bd957x_ops,
			.type = REGULATOR_VOLTAGE,
			.volt_table = &voutl1_volt_table[0],
			.n_voltages = ARRAY_SIZE(voutl1_volt_table),
			.vsel_reg = BD957X_REG_VOUTL1_TUNE,
			.vsel_mask = BD957X_MASK_VOUTL1_TUNE,
			.enable_reg = BD957X_REG_POW_TRIGGERL1,
			.enable_mask = BD957X_REGULATOR_EN_MASK,
			.enable_val = BD957X_REGULATOR_DIS_VAL,
			.enable_is_inverted = true,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "VOUTS1",
			.of_match = of_match_ptr("regulator-vouts1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD957X_VOUTS1,
			.ops = &bd957X_vouts1_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = 1,
			.fixed_uV = BD957X_VOUTS1_VOLT,
			.enable_reg = BD957X_REG_POW_TRIGGERS1,
			.enable_mask = BD957X_REGULATOR_EN_MASK,
			.enable_val = BD957X_REGULATOR_DIS_VAL,
			.enable_is_inverted = true,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bd957x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_config config = अणु 0 पूर्ण;
	पूर्णांक i;
	bool vout_mode, ddr_sel;
	स्थिर काष्ठा bd957x_regulator_data *reg_data = &bd9576_regulators[0];
	अचिन्हित पूर्णांक num_reg_data = ARRAY_SIZE(bd9576_regulators);
	क्रमागत rohm_chip_type chip = platक्रमm_get_device_id(pdev)->driver_data;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "No regmap\n");
		वापस -EINVAL;
	पूर्ण
	vout_mode = of_property_पढ़ो_bool(pdev->dev.parent->of_node,
					 "rohm,vout1-en-low");
	अगर (vout_mode) अणु
		काष्ठा gpio_desc *en;

		dev_dbg(&pdev->dev, "GPIO controlled mode\n");

		/* VOUT1 enable state judged by VOUT1_EN pin */
		/* See अगर we have GPIO defined */
		en = devm_gpiod_get_from_of_node(&pdev->dev,
						 pdev->dev.parent->of_node,
						 "rohm,vout1-en-gpios", 0,
						 GPIOD_OUT_LOW, "vout1-en");
		अगर (!IS_ERR(en)) अणु
			/* VOUT1_OPS gpio ctrl */
			/*
			 * Regulator core prioritizes the ena_gpio over
			 * enable/disable/is_enabled callbacks so no need to
			 * clear them. We can still use same ops
			 */
			config.ena_gpiod = en;
		पूर्ण अन्यथा अणु
			/*
			 * In theory it is possible someone wants to set
			 * vout1-en LOW during OTP loading and set VOUT1 to be
			 * controlled by GPIO - but control the GPIO from some
			 * where अन्यथा than this driver. For that to work we
			 * should unset the is_enabled callback here.
			 *
			 * I believe such हाल where rohm,vout1-en-low is set
			 * and vout1-en-gpios is not is likely to be a
			 * misconfiguration. So let's just err out क्रम now.
			 */
			dev_err(&pdev->dev,
				"Failed to get VOUT1 control GPIO\n");
			वापस PTR_ERR(en);
		पूर्ण
	पूर्ण

	/*
	 * If more than one PMIC needs to be controlled by same processor then
	 * allocate the regulator data array here and use bd9576_regulators as
	 * ढाँचा. At the moment I see no such use-हाल so I spare some
	 * bytes and use bd9576_regulators directly क्रम non-स्थिरant configs
	 * like DDR voltage selection.
	 */
	ddr_sel =  of_property_पढ़ो_bool(pdev->dev.parent->of_node,
					 "rohm,ddr-sel-low");
	अगर (ddr_sel)
		bd9576_regulators[2].desc.fixed_uV = 1350000;
	अन्यथा
		bd9576_regulators[2].desc.fixed_uV = 1500000;

	चयन (chip) अणु
	हाल ROHM_CHIP_TYPE_BD9576:
		dev_dbg(&pdev->dev, "Found BD9576MUF\n");
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD9573:
		dev_dbg(&pdev->dev, "Found BD9573MUF\n");
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported chip type\n");
		वापस -EINVAL;
	पूर्ण

	config.dev = pdev->dev.parent;
	config.regmap = regmap;

	क्रम (i = 0; i < num_reg_data; i++) अणु

		स्थिर काष्ठा regulator_desc *desc;
		काष्ठा regulator_dev *rdev;
		स्थिर काष्ठा bd957x_regulator_data *r;

		r = &reg_data[i];
		desc = &r->desc;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				desc->name);
			वापस PTR_ERR(rdev);
		पूर्ण
		/*
		 * Clear the VOUT1 GPIO setting - rest of the regulators करो not
		 * support GPIO control
		 */
		config.ena_gpiod = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd957x_pmic_id[] = अणु
	अणु "bd9573-pmic", ROHM_CHIP_TYPE_BD9573 पूर्ण,
	अणु "bd9576-pmic", ROHM_CHIP_TYPE_BD9576 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd957x_pmic_id);

अटल काष्ठा platक्रमm_driver bd957x_regulator = अणु
	.driver = अणु
		.name = "bd957x-pmic",
	पूर्ण,
	.probe = bd957x_probe,
	.id_table = bd957x_pmic_id,
पूर्ण;

module_platक्रमm_driver(bd957x_regulator);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD9576/BD9573 voltage regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd957x-pmic");
