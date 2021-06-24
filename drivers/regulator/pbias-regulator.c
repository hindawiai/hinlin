<शैली गुरु>
/*
 * pbias-regulator.c
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Balaji T K <balajitk@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

काष्ठा pbias_reg_info अणु
	u32 enable;
	u32 enable_mask;
	u32 disable_val;
	u32 vmode;
	अचिन्हित पूर्णांक enable_समय;
	अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pbias_volt_table;
	पूर्णांक n_voltages;
पूर्ण;

काष्ठा pbias_of_data अणु
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pbias_volt_table_3_0V[] = अणु
	1800000,
	3000000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pbias_volt_table_3_3V[] = अणु
	1800000,
	3300000
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pbias_regulator_voltage_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा pbias_reg_info pbias_mmc_omap2430 = अणु
	.enable = BIT(1),
	.enable_mask = BIT(1),
	.vmode = BIT(0),
	.disable_val = 0,
	.enable_समय = 100,
	.pbias_volt_table = pbias_volt_table_3_0V,
	.n_voltages = 2,
	.name = "pbias_mmc_omap2430"
पूर्ण;

अटल स्थिर काष्ठा pbias_reg_info pbias_sim_omap3 = अणु
	.enable = BIT(9),
	.enable_mask = BIT(9),
	.vmode = BIT(8),
	.enable_समय = 100,
	.pbias_volt_table = pbias_volt_table_3_0V,
	.n_voltages = 2,
	.name = "pbias_sim_omap3"
पूर्ण;

अटल स्थिर काष्ठा pbias_reg_info pbias_mmc_omap4 = अणु
	.enable = BIT(26) | BIT(22),
	.enable_mask = BIT(26) | BIT(25) | BIT(22),
	.disable_val = BIT(25),
	.vmode = BIT(21),
	.enable_समय = 100,
	.pbias_volt_table = pbias_volt_table_3_0V,
	.n_voltages = 2,
	.name = "pbias_mmc_omap4"
पूर्ण;

अटल स्थिर काष्ठा pbias_reg_info pbias_mmc_omap5 = अणु
	.enable = BIT(27) | BIT(26),
	.enable_mask = BIT(27) | BIT(25) | BIT(26),
	.disable_val = BIT(25),
	.vmode = BIT(21),
	.enable_समय = 100,
	.pbias_volt_table = pbias_volt_table_3_3V,
	.n_voltages = 2,
	.name = "pbias_mmc_omap5"
पूर्ण;

अटल काष्ठा of_regulator_match pbias_matches[] = अणु
	अणु .name = "pbias_mmc_omap2430", .driver_data = (व्योम *)&pbias_mmc_omap2430पूर्ण,
	अणु .name = "pbias_sim_omap3", .driver_data = (व्योम *)&pbias_sim_omap3पूर्ण,
	अणु .name = "pbias_mmc_omap4", .driver_data = (व्योम *)&pbias_mmc_omap4पूर्ण,
	अणु .name = "pbias_mmc_omap5", .driver_data = (व्योम *)&pbias_mmc_omap5पूर्ण,
पूर्ण;
#घोषणा PBIAS_NUM_REGS	ARRAY_SIZE(pbias_matches)

/* Offset from SCM general area (and syscon) base */

अटल स्थिर काष्ठा pbias_of_data pbias_of_data_omap2 = अणु
	.offset = 0x230,
पूर्ण;

अटल स्थिर काष्ठा pbias_of_data pbias_of_data_omap3 = अणु
	.offset = 0x2b0,
पूर्ण;

अटल स्थिर काष्ठा pbias_of_data pbias_of_data_omap4 = अणु
	.offset = 0x60,
पूर्ण;

अटल स्थिर काष्ठा pbias_of_data pbias_of_data_omap5 = अणु
	.offset = 0x60,
पूर्ण;

अटल स्थिर काष्ठा pbias_of_data pbias_of_data_dra7 = अणु
	.offset = 0xe00,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pbias_of_match[] = अणु
	अणु .compatible = "ti,pbias-omap", पूर्ण,
	अणु .compatible = "ti,pbias-omap2", .data = &pbias_of_data_omap2, पूर्ण,
	अणु .compatible = "ti,pbias-omap3", .data = &pbias_of_data_omap3, पूर्ण,
	अणु .compatible = "ti,pbias-omap4", .data = &pbias_of_data_omap4, पूर्ण,
	अणु .compatible = "ti,pbias-omap5", .data = &pbias_of_data_omap5, पूर्ण,
	अणु .compatible = "ti,pbias-dra7", .data = &pbias_of_data_dra7, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pbias_of_match);

अटल पूर्णांक pbias_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_desc *desc;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *syscon;
	स्थिर काष्ठा pbias_reg_info *info;
	पूर्णांक ret, count, idx;
	स्थिर काष्ठा pbias_of_data *data;
	अचिन्हित पूर्णांक offset;

	count = of_regulator_match(&pdev->dev, np, pbias_matches,
						PBIAS_NUM_REGS);
	अगर (count < 0)
		वापस count;

	desc = devm_kसुस्मृति(&pdev->dev, count, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	syscon = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(syscon))
		वापस PTR_ERR(syscon);

	data = of_device_get_match_data(&pdev->dev);
	अगर (data) अणु
		offset = data->offset;
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (!res)
			वापस -EINVAL;

		offset = res->start;
		dev_WARN(&pdev->dev,
			 "using legacy dt data for pbias offset\n");
	पूर्ण

	cfg.regmap = syscon;
	cfg.dev = &pdev->dev;

	क्रम (idx = 0; idx < PBIAS_NUM_REGS && count; idx++) अणु
		अगर (!pbias_matches[idx].init_data ||
			!pbias_matches[idx].of_node)
			जारी;

		info = pbias_matches[idx].driver_data;
		अगर (!info)
			वापस -ENODEV;

		desc->name = info->name;
		desc->owner = THIS_MODULE;
		desc->type = REGULATOR_VOLTAGE;
		desc->ops = &pbias_regulator_voltage_ops;
		desc->volt_table = info->pbias_volt_table;
		desc->n_voltages = info->n_voltages;
		desc->enable_समय = info->enable_समय;
		desc->vsel_reg = offset;
		desc->vsel_mask = info->vmode;
		desc->enable_reg = offset;
		desc->enable_mask = info->enable_mask;
		desc->enable_val = info->enable;
		desc->disable_val = info->disable_val;

		cfg.init_data = pbias_matches[idx].init_data;
		cfg.of_node = pbias_matches[idx].of_node;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, desc, &cfg);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(&pdev->dev,
				"Failed to register regulator: %d\n", ret);
			वापस ret;
		पूर्ण
		desc++;
		count--;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pbias_regulator_driver = अणु
	.probe		= pbias_regulator_probe,
	.driver		= अणु
		.name		= "pbias-regulator",
		.of_match_table = of_match_ptr(pbias_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pbias_regulator_driver);

MODULE_AUTHOR("Balaji T K <balajitk@ti.com>");
MODULE_DESCRIPTION("pbias voltage regulator");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pbias-regulator");
