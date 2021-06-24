<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/machine.h>

#घोषणा LDO_RAMP_UP_UNIT_IN_CYCLES      64 /* 64 cycles per step */
#घोषणा LDO_RAMP_UP_FREQ_IN_MHZ         24 /* cycle based on 24M OSC */

#घोषणा LDO_POWER_GATE			0x00
#घोषणा LDO_FET_FULL_ON			0x1f

काष्ठा anatop_regulator अणु
	u32 delay_reg;
	पूर्णांक delay_bit_shअगरt;
	पूर्णांक delay_bit_width;
	काष्ठा regulator_desc rdesc;
	bool bypass;
	पूर्णांक sel;
पूर्ण;

अटल पूर्णांक anatop_regmap_set_voltage_समय_sel(काष्ठा regulator_dev *reg,
	अचिन्हित पूर्णांक old_sel,
	अचिन्हित पूर्णांक new_sel)
अणु
	काष्ठा anatop_regulator *anatop_reg = rdev_get_drvdata(reg);
	u32 val;
	पूर्णांक ret = 0;

	/* check whether need to care about LDO ramp up speed */
	अगर (anatop_reg->delay_bit_width && new_sel > old_sel) अणु
		/*
		 * the delay क्रम LDO ramp up समय is
		 * based on the रेजिस्टर setting, we need
		 * to calculate how many steps LDO need to
		 * ramp up, and how much delay needed. (us)
		 */
		regmap_पढ़ो(reg->regmap, anatop_reg->delay_reg, &val);
		val = (val >> anatop_reg->delay_bit_shअगरt) &
			((1 << anatop_reg->delay_bit_width) - 1);
		ret = (new_sel - old_sel) * (LDO_RAMP_UP_UNIT_IN_CYCLES <<
			val) / LDO_RAMP_UP_FREQ_IN_MHZ + 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक anatop_regmap_enable(काष्ठा regulator_dev *reg)
अणु
	काष्ठा anatop_regulator *anatop_reg = rdev_get_drvdata(reg);
	पूर्णांक sel;

	sel = anatop_reg->bypass ? LDO_FET_FULL_ON : anatop_reg->sel;
	वापस regulator_set_voltage_sel_regmap(reg, sel);
पूर्ण

अटल पूर्णांक anatop_regmap_disable(काष्ठा regulator_dev *reg)
अणु
	वापस regulator_set_voltage_sel_regmap(reg, LDO_POWER_GATE);
पूर्ण

अटल पूर्णांक anatop_regmap_is_enabled(काष्ठा regulator_dev *reg)
अणु
	वापस regulator_get_voltage_sel_regmap(reg) != LDO_POWER_GATE;
पूर्ण

अटल पूर्णांक anatop_regmap_core_set_voltage_sel(काष्ठा regulator_dev *reg,
					      अचिन्हित selector)
अणु
	काष्ठा anatop_regulator *anatop_reg = rdev_get_drvdata(reg);
	पूर्णांक ret;

	अगर (anatop_reg->bypass || !anatop_regmap_is_enabled(reg)) अणु
		anatop_reg->sel = selector;
		वापस 0;
	पूर्ण

	ret = regulator_set_voltage_sel_regmap(reg, selector);
	अगर (!ret)
		anatop_reg->sel = selector;
	वापस ret;
पूर्ण

अटल पूर्णांक anatop_regmap_core_get_voltage_sel(काष्ठा regulator_dev *reg)
अणु
	काष्ठा anatop_regulator *anatop_reg = rdev_get_drvdata(reg);

	अगर (anatop_reg->bypass || !anatop_regmap_is_enabled(reg))
		वापस anatop_reg->sel;

	वापस regulator_get_voltage_sel_regmap(reg);
पूर्ण

अटल पूर्णांक anatop_regmap_get_bypass(काष्ठा regulator_dev *reg, bool *enable)
अणु
	काष्ठा anatop_regulator *anatop_reg = rdev_get_drvdata(reg);
	पूर्णांक sel;

	sel = regulator_get_voltage_sel_regmap(reg);
	अगर (sel == LDO_FET_FULL_ON)
		WARN_ON(!anatop_reg->bypass);
	अन्यथा अगर (sel != LDO_POWER_GATE)
		WARN_ON(anatop_reg->bypass);

	*enable = anatop_reg->bypass;
	वापस 0;
पूर्ण

अटल पूर्णांक anatop_regmap_set_bypass(काष्ठा regulator_dev *reg, bool enable)
अणु
	काष्ठा anatop_regulator *anatop_reg = rdev_get_drvdata(reg);
	पूर्णांक sel;

	अगर (enable == anatop_reg->bypass)
		वापस 0;

	sel = enable ? LDO_FET_FULL_ON : anatop_reg->sel;
	anatop_reg->bypass = enable;

	वापस regulator_set_voltage_sel_regmap(reg, sel);
पूर्ण

अटल काष्ठा regulator_ops anatop_rops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops anatop_core_rops = अणु
	.enable = anatop_regmap_enable,
	.disable = anatop_regmap_disable,
	.is_enabled = anatop_regmap_is_enabled,
	.set_voltage_sel = anatop_regmap_core_set_voltage_sel,
	.set_voltage_समय_sel = anatop_regmap_set_voltage_समय_sel,
	.get_voltage_sel = anatop_regmap_core_get_voltage_sel,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_bypass = anatop_regmap_get_bypass,
	.set_bypass = anatop_regmap_set_bypass,
पूर्ण;

अटल पूर्णांक anatop_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *anatop_np;
	काष्ठा regulator_desc *rdesc;
	काष्ठा regulator_dev *rdev;
	काष्ठा anatop_regulator *sreg;
	काष्ठा regulator_init_data *initdata;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	u32 control_reg;
	u32 vol_bit_shअगरt;
	u32 vol_bit_width;
	u32 min_bit_val;
	u32 min_voltage;
	u32 max_voltage;
	पूर्णांक ret = 0;
	u32 val;

	sreg = devm_kzalloc(dev, माप(*sreg), GFP_KERNEL);
	अगर (!sreg)
		वापस -ENOMEM;

	rdesc = &sreg->rdesc;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->owner = THIS_MODULE;

	of_property_पढ़ो_string(np, "regulator-name", &rdesc->name);
	अगर (!rdesc->name) अणु
		dev_err(dev, "failed to get a regulator-name\n");
		वापस -EINVAL;
	पूर्ण

	initdata = of_get_regulator_init_data(dev, np, rdesc);
	अगर (!initdata)
		वापस -ENOMEM;

	initdata->supply_regulator = "vin";

	anatop_np = of_get_parent(np);
	अगर (!anatop_np)
		वापस -ENODEV;
	regmap = syscon_node_to_regmap(anatop_np);
	of_node_put(anatop_np);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = of_property_पढ़ो_u32(np, "anatop-reg-offset", &control_reg);
	अगर (ret) अणु
		dev_err(dev, "no anatop-reg-offset property set\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "anatop-vol-bit-width", &vol_bit_width);
	अगर (ret) अणु
		dev_err(dev, "no anatop-vol-bit-width property set\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "anatop-vol-bit-shift", &vol_bit_shअगरt);
	अगर (ret) अणु
		dev_err(dev, "no anatop-vol-bit-shift property set\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "anatop-min-bit-val", &min_bit_val);
	अगर (ret) अणु
		dev_err(dev, "no anatop-min-bit-val property set\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "anatop-min-voltage", &min_voltage);
	अगर (ret) अणु
		dev_err(dev, "no anatop-min-voltage property set\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "anatop-max-voltage", &max_voltage);
	अगर (ret) अणु
		dev_err(dev, "no anatop-max-voltage property set\n");
		वापस ret;
	पूर्ण

	/* पढ़ो LDO ramp up setting, only क्रम core reg */
	of_property_पढ़ो_u32(np, "anatop-delay-reg-offset",
			     &sreg->delay_reg);
	of_property_पढ़ो_u32(np, "anatop-delay-bit-width",
			     &sreg->delay_bit_width);
	of_property_पढ़ो_u32(np, "anatop-delay-bit-shift",
			     &sreg->delay_bit_shअगरt);

	rdesc->n_voltages = (max_voltage - min_voltage) / 25000 + 1
			    + min_bit_val;
	rdesc->min_uV = min_voltage;
	rdesc->uV_step = 25000;
	rdesc->linear_min_sel = min_bit_val;
	rdesc->vsel_reg = control_reg;
	rdesc->vsel_mask = ((1 << vol_bit_width) - 1) << vol_bit_shअगरt;
	rdesc->min_dropout_uV = 125000;

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = sreg;
	config.of_node = pdev->dev.of_node;
	config.regmap = regmap;

	/* Only core regulators have the ramp up delay configuration. */
	अगर (control_reg && sreg->delay_bit_width) अणु
		rdesc->ops = &anatop_core_rops;

		ret = regmap_पढ़ो(config.regmap, rdesc->vsel_reg, &val);
		अगर (ret) अणु
			dev_err(dev, "failed to read initial state\n");
			वापस ret;
		पूर्ण

		sreg->sel = (val & rdesc->vsel_mask) >> vol_bit_shअगरt;
		अगर (sreg->sel == LDO_FET_FULL_ON) अणु
			sreg->sel = 0;
			sreg->bypass = true;
		पूर्ण

		/*
		 * In हाल vddpu was disabled by the bootloader, we need to set
		 * a sane शेष until imx6-cpufreq was probed and changes the
		 * voltage to the correct value. In this हाल we set 1.25V.
		 */
		अगर (!sreg->sel && !म_भेद(rdesc->name, "vddpu"))
			sreg->sel = 22;

		/* set the शेष voltage of the pcie phy to be 1.100v */
		अगर (!sreg->sel && !म_भेद(rdesc->name, "vddpcie"))
			sreg->sel = 0x10;

		अगर (!sreg->bypass && !sreg->sel) अणु
			dev_err(&pdev->dev, "Failed to read a valid default voltage selector.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 enable_bit;

		rdesc->ops = &anatop_rops;

		अगर (!of_property_पढ़ो_u32(np, "anatop-enable-bit",
					  &enable_bit)) अणु
			anatop_rops.enable  = regulator_enable_regmap;
			anatop_rops.disable = regulator_disable_regmap;
			anatop_rops.is_enabled = regulator_is_enabled_regmap;

			rdesc->enable_reg = control_reg;
			rdesc->enable_mask = BIT(enable_bit);
		पूर्ण
	पूर्ण

	/* रेजिस्टर regulator */
	rdev = devm_regulator_रेजिस्टर(dev, rdesc, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		अगर (ret == -EPROBE_DEFER)
			dev_dbg(dev, "failed to register %s, deferring...\n",
				rdesc->name);
		अन्यथा
			dev_err(dev, "failed to register %s\n", rdesc->name);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_anatop_regulator_match_tbl[] = अणु
	अणु .compatible = "fsl,anatop-regulator", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_anatop_regulator_match_tbl);

अटल काष्ठा platक्रमm_driver anatop_regulator_driver = अणु
	.driver = अणु
		.name	= "anatop_regulator",
		.of_match_table = of_anatop_regulator_match_tbl,
	पूर्ण,
	.probe	= anatop_regulator_probe,
पूर्ण;

अटल पूर्णांक __init anatop_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&anatop_regulator_driver);
पूर्ण
postcore_initcall(anatop_regulator_init);

अटल व्योम __निकास anatop_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&anatop_regulator_driver);
पूर्ण
module_निकास(anatop_regulator_निकास);

MODULE_AUTHOR("Nancy Chen <Nancy.Chen@freescale.com>");
MODULE_AUTHOR("Ying-Chun Liu (PaulLiu) <paul.liu@linaro.org>");
MODULE_DESCRIPTION("ANATOP Regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:anatop_regulator");
