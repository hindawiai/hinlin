<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// da9052-regulator.c: Regulator driver क्रम DA9052
//
// Copyright(c) 2011 Dialog Semiconductor Ltd.
//
// Author: David Dajun Chen <dchen@diasemi.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>
#समावेश <linux/mfd/da9052/pdata.h>

/* Buck step size */
#घोषणा DA9052_BUCK_PERI_3uV_STEP		100000
#घोषणा DA9052_BUCK_PERI_REG_MAP_UPTO_3uV	24
#घोषणा DA9052_CONST_3uV			3000000

#घोषणा DA9052_MIN_UA		0
#घोषणा DA9052_MAX_UA		3
#घोषणा DA9052_CURRENT_RANGE	4

/* Bit masks */
#घोषणा DA9052_BUCK_ILIM_MASK_EVEN	0x0c
#घोषणा DA9052_BUCK_ILIM_MASK_ODD	0xc0

/* DA9052 REGULATOR IDs */
#घोषणा DA9052_ID_BUCK1		0
#घोषणा DA9052_ID_BUCK2		1
#घोषणा DA9052_ID_BUCK3		2
#घोषणा DA9052_ID_BUCK4		3
#घोषणा DA9052_ID_LDO1		4
#घोषणा DA9052_ID_LDO2		5
#घोषणा DA9052_ID_LDO3		6
#घोषणा DA9052_ID_LDO4		7
#घोषणा DA9052_ID_LDO5		8
#घोषणा DA9052_ID_LDO6		9
#घोषणा DA9052_ID_LDO7		10
#घोषणा DA9052_ID_LDO8		11
#घोषणा DA9052_ID_LDO9		12
#घोषणा DA9052_ID_LDO10		13

अटल स्थिर u32 da9052_current_limits[3][4] = अणु
	अणु700000, 800000, 1000000, 1200000पूर्ण,	/* DA9052-BC BUCKs */
	अणु1600000, 2000000, 2400000, 3000000पूर्ण,	/* DA9053-AA/Bx BUCK-CORE */
	अणु800000, 1000000, 1200000, 1500000पूर्ण,	/* DA9053-AA/Bx BUCK-PRO,
						 * BUCK-MEM and BUCK-PERI
						*/
पूर्ण;

काष्ठा da9052_regulator_info अणु
	काष्ठा regulator_desc reg_desc;
	पूर्णांक step_uV;
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	अचिन्हित अक्षर activate_bit;
पूर्ण;

काष्ठा da9052_regulator अणु
	काष्ठा da9052 *da9052;
	काष्ठा da9052_regulator_info *info;
	काष्ठा regulator_dev *rdev;
पूर्ण;

अटल पूर्णांक verअगरy_range(काष्ठा da9052_regulator_info *info,
			 पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	अगर (min_uV > info->max_uV || max_uV < info->min_uV)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_dcdc_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9052_regulator *regulator = rdev_get_drvdata(rdev);
	पूर्णांक offset = rdev_get_id(rdev);
	पूर्णांक ret, row = 2;

	ret = da9052_reg_पढ़ो(regulator->da9052, DA9052_BUCKA_REG + offset/2);
	अगर (ret < 0)
		वापस ret;

	/* Determine the even or odd position of the buck current limit
	 * रेजिस्टर field
	*/
	अगर (offset % 2 == 0)
		ret = (ret & DA9052_BUCK_ILIM_MASK_EVEN) >> 2;
	अन्यथा
		ret = (ret & DA9052_BUCK_ILIM_MASK_ODD) >> 6;

	/* Select the appropriate current limit range */
	अगर (regulator->da9052->chip_id == DA9052)
		row = 0;
	अन्यथा अगर (offset == 0)
		row = 1;

	वापस da9052_current_limits[row][ret];
पूर्ण

अटल पूर्णांक da9052_dcdc_set_current_limit(काष्ठा regulator_dev *rdev, पूर्णांक min_uA,
					  पूर्णांक max_uA)
अणु
	काष्ठा da9052_regulator *regulator = rdev_get_drvdata(rdev);
	पूर्णांक offset = rdev_get_id(rdev);
	पूर्णांक reg_val = 0;
	पूर्णांक i, row = 2;

	/* Select the appropriate current limit range */
	अगर (regulator->da9052->chip_id == DA9052)
		row = 0;
	अन्यथा अगर (offset == 0)
		row = 1;

	क्रम (i = DA9052_CURRENT_RANGE - 1; i >= 0; i--) अणु
		अगर ((min_uA <= da9052_current_limits[row][i]) &&
		    (da9052_current_limits[row][i] <= max_uA)) अणु
			reg_val = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i < 0)
		वापस -EINVAL;

	/* Determine the even or odd position of the buck current limit
	 * रेजिस्टर field
	*/
	अगर (offset % 2 == 0)
		वापस da9052_reg_update(regulator->da9052,
					 DA9052_BUCKA_REG + offset/2,
					 DA9052_BUCK_ILIM_MASK_EVEN,
					 reg_val << 2);
	अन्यथा
		वापस da9052_reg_update(regulator->da9052,
					 DA9052_BUCKA_REG + offset/2,
					 DA9052_BUCK_ILIM_MASK_ODD,
					 reg_val << 6);
पूर्ण

अटल पूर्णांक da9052_list_voltage(काष्ठा regulator_dev *rdev,
				अचिन्हित पूर्णांक selector)
अणु
	काष्ठा da9052_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9052_regulator_info *info = regulator->info;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक volt_uV;

	अगर ((id == DA9052_ID_BUCK4) && (regulator->da9052->chip_id == DA9052)
		&& (selector >= DA9052_BUCK_PERI_REG_MAP_UPTO_3uV)) अणु
		volt_uV = ((DA9052_BUCK_PERI_REG_MAP_UPTO_3uV * info->step_uV)
			  + info->min_uV);
		volt_uV += (selector - DA9052_BUCK_PERI_REG_MAP_UPTO_3uV)
				    * (DA9052_BUCK_PERI_3uV_STEP);
	पूर्ण अन्यथा अणु
		volt_uV = (selector * info->step_uV) + info->min_uV;
	पूर्ण

	अगर (volt_uV > info->max_uV)
		वापस -EINVAL;

	वापस volt_uV;
पूर्ण

अटल पूर्णांक da9052_map_voltage(काष्ठा regulator_dev *rdev,
			      पूर्णांक min_uV, पूर्णांक max_uV)
अणु
	काष्ठा da9052_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9052_regulator_info *info = regulator->info;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक ret, sel;

	ret = verअगरy_range(info, min_uV, max_uV);
	अगर (ret < 0)
		वापस ret;

	अगर (min_uV < info->min_uV)
		min_uV = info->min_uV;

	अगर ((id == DA9052_ID_BUCK4) && (regulator->da9052->chip_id == DA9052)
		&& (min_uV >= DA9052_CONST_3uV)) अणु
			sel = DA9052_BUCK_PERI_REG_MAP_UPTO_3uV +
			      DIV_ROUND_UP(min_uV - DA9052_CONST_3uV,
					   DA9052_BUCK_PERI_3uV_STEP);
	पूर्ण अन्यथा अणु
		sel = DIV_ROUND_UP(min_uV - info->min_uV, info->step_uV);
	पूर्ण

	ret = da9052_list_voltage(rdev, sel);
	अगर (ret < 0)
		वापस ret;

	वापस sel;
पूर्ण

अटल पूर्णांक da9052_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
					    अचिन्हित पूर्णांक selector)
अणु
	काष्ठा da9052_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9052_regulator_info *info = regulator->info;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक ret;

	ret = da9052_reg_update(regulator->da9052, rdev->desc->vsel_reg,
				rdev->desc->vsel_mask, selector);
	अगर (ret < 0)
		वापस ret;

	/* Some LDOs and DCDCs are DVC controlled which requires enabling of
	 * the activate bit to implment the changes on the output.
	 */
	चयन (id) अणु
	हाल DA9052_ID_BUCK1:
	हाल DA9052_ID_BUCK2:
	हाल DA9052_ID_BUCK3:
	हाल DA9052_ID_LDO2:
	हाल DA9052_ID_LDO3:
		ret = da9052_reg_update(regulator->da9052, DA9052_SUPPLY_REG,
					info->activate_bit, info->activate_bit);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9052_regulator_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
						 अचिन्हित पूर्णांक old_sel,
						 अचिन्हित पूर्णांक new_sel)
अणु
	काष्ठा da9052_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9052_regulator_info *info = regulator->info;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक ret = 0;

	/* The DVC controlled LDOs and DCDCs ramp with 6.25mV/तगs after enabling
	 * the activate bit.
	 */
	चयन (id) अणु
	हाल DA9052_ID_BUCK1:
	हाल DA9052_ID_BUCK2:
	हाल DA9052_ID_BUCK3:
	हाल DA9052_ID_LDO2:
	हाल DA9052_ID_LDO3:
		ret = (new_sel - old_sel) * info->step_uV / 6250;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops da9052_dcdc_ops = अणु
	.get_current_limit = da9052_dcdc_get_current_limit,
	.set_current_limit = da9052_dcdc_set_current_limit,

	.list_voltage = da9052_list_voltage,
	.map_voltage = da9052_map_voltage,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = da9052_regulator_set_voltage_sel,
	.set_voltage_समय_sel = da9052_regulator_set_voltage_समय_sel,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da9052_lकरो_ops = अणु
	.list_voltage = da9052_list_voltage,
	.map_voltage = da9052_map_voltage,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = da9052_regulator_set_voltage_sel,
	.set_voltage_समय_sel = da9052_regulator_set_voltage_समय_sel,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

#घोषणा DA9052_LDO(_id, _name, step, min, max, sbits, ebits, abits) \
अणु\
	.reg_desc = अणु\
		.name = #_name,\
		.of_match = of_match_ptr(#_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.ops = &da9052_lकरो_ops,\
		.type = REGULATOR_VOLTAGE,\
		.id = DA9052_ID_##_id,\
		.n_voltages = (max - min) / step + 1, \
		.owner = THIS_MODULE,\
		.vsel_reg = DA9052_BUCKCORE_REG + DA9052_ID_##_id, \
		.vsel_mask = (1 << (sbits)) - 1,\
		.enable_reg = DA9052_BUCKCORE_REG + DA9052_ID_##_id, \
		.enable_mask = 1 << (ebits),\
	पूर्ण,\
	.min_uV = (min) * 1000,\
	.max_uV = (max) * 1000,\
	.step_uV = (step) * 1000,\
	.activate_bit = (abits),\
पूर्ण

#घोषणा DA9052_DCDC(_id, _name, step, min, max, sbits, ebits, abits) \
अणु\
	.reg_desc = अणु\
		.name = #_name,\
		.of_match = of_match_ptr(#_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.ops = &da9052_dcdc_ops,\
		.type = REGULATOR_VOLTAGE,\
		.id = DA9052_ID_##_id,\
		.n_voltages = (max - min) / step + 1, \
		.owner = THIS_MODULE,\
		.vsel_reg = DA9052_BUCKCORE_REG + DA9052_ID_##_id, \
		.vsel_mask = (1 << (sbits)) - 1,\
		.enable_reg = DA9052_BUCKCORE_REG + DA9052_ID_##_id, \
		.enable_mask = 1 << (ebits),\
	पूर्ण,\
	.min_uV = (min) * 1000,\
	.max_uV = (max) * 1000,\
	.step_uV = (step) * 1000,\
	.activate_bit = (abits),\
पूर्ण

अटल काष्ठा da9052_regulator_info da9052_regulator_info[] = अणु
	DA9052_DCDC(BUCK1, buck1, 25, 500, 2075, 6, 6, DA9052_SUPPLY_VBCOREGO),
	DA9052_DCDC(BUCK2, buck2, 25, 500, 2075, 6, 6, DA9052_SUPPLY_VBPROGO),
	DA9052_DCDC(BUCK3, buck3, 25, 950, 2525, 6, 6, DA9052_SUPPLY_VBMEMGO),
	DA9052_DCDC(BUCK4, buck4, 50, 1800, 3600, 5, 6, 0),
	DA9052_LDO(LDO1, lकरो1, 50, 600, 1800, 5, 6, 0),
	DA9052_LDO(LDO2, lकरो2, 25, 600, 1800, 6, 6, DA9052_SUPPLY_VLDO2GO),
	DA9052_LDO(LDO3, lकरो3, 25, 1725, 3300, 6, 6, DA9052_SUPPLY_VLDO3GO),
	DA9052_LDO(LDO4, lकरो4, 25, 1725, 3300, 6, 6, 0),
	DA9052_LDO(LDO5, lकरो5, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO6, lकरो6, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO7, lकरो7, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO8, lकरो8, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO9, lकरो9, 50, 1250, 3650, 6, 6, 0),
	DA9052_LDO(LDO10, lकरो10, 50, 1200, 3600, 6, 6, 0),
पूर्ण;

अटल काष्ठा da9052_regulator_info da9053_regulator_info[] = अणु
	DA9052_DCDC(BUCK1, buck1, 25, 500, 2075, 6, 6, DA9052_SUPPLY_VBCOREGO),
	DA9052_DCDC(BUCK2, buck2, 25, 500, 2075, 6, 6, DA9052_SUPPLY_VBPROGO),
	DA9052_DCDC(BUCK3, buck3, 25, 950, 2525, 6, 6, DA9052_SUPPLY_VBMEMGO),
	DA9052_DCDC(BUCK4, buck4, 25, 950, 2525, 6, 6, 0),
	DA9052_LDO(LDO1, lकरो1, 50, 600, 1800, 5, 6, 0),
	DA9052_LDO(LDO2, lकरो2, 25, 600, 1800, 6, 6, DA9052_SUPPLY_VLDO2GO),
	DA9052_LDO(LDO3, lकरो3, 25, 1725, 3300, 6, 6, DA9052_SUPPLY_VLDO3GO),
	DA9052_LDO(LDO4, lकरो4, 25, 1725, 3300, 6, 6, 0),
	DA9052_LDO(LDO5, lकरो5, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO6, lकरो6, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO7, lकरो7, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO8, lकरो8, 50, 1200, 3600, 6, 6, 0),
	DA9052_LDO(LDO9, lकरो9, 50, 1250, 3650, 6, 6, 0),
	DA9052_LDO(LDO10, lकरो10, 50, 1200, 3600, 6, 6, 0),
पूर्ण;

अटल अंतरभूत काष्ठा da9052_regulator_info *find_regulator_info(u8 chip_id,
								 पूर्णांक id)
अणु
	काष्ठा da9052_regulator_info *info;
	पूर्णांक i;

	चयन (chip_id) अणु
	हाल DA9052:
		क्रम (i = 0; i < ARRAY_SIZE(da9052_regulator_info); i++) अणु
			info = &da9052_regulator_info[i];
			अगर (info->reg_desc.id == id)
				वापस info;
		पूर्ण
		अवरोध;
	हाल DA9053_AA:
	हाल DA9053_BA:
	हाल DA9053_BB:
	हाल DA9053_BC:
		क्रम (i = 0; i < ARRAY_SIZE(da9053_regulator_info); i++) अणु
			info = &da9053_regulator_info[i];
			अगर (info->reg_desc.id == id)
				वापस info;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक da9052_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा da9052_regulator *regulator;
	काष्ठा da9052 *da9052;
	काष्ठा da9052_pdata *pdata;

	regulator = devm_kzalloc(&pdev->dev, माप(काष्ठा da9052_regulator),
				 GFP_KERNEL);
	अगर (!regulator)
		वापस -ENOMEM;

	da9052 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(da9052->dev);
	regulator->da9052 = da9052;

	regulator->info = find_regulator_info(regulator->da9052->chip_id,
					      cell->id);
	अगर (regulator->info == शून्य) अणु
		dev_err(&pdev->dev, "invalid regulator ID specified\n");
		वापस -EINVAL;
	पूर्ण

	config.dev = da9052->dev;
	config.driver_data = regulator;
	config.regmap = da9052->regmap;
	अगर (pdata)
		config.init_data = pdata->regulators[cell->id];

	regulator->rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						  &regulator->info->reg_desc,
						  &config);
	अगर (IS_ERR(regulator->rdev)) अणु
		dev_err(&pdev->dev, "failed to register regulator %s\n",
			regulator->info->reg_desc.name);
		वापस PTR_ERR(regulator->rdev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, regulator);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_regulator_driver = अणु
	.probe = da9052_regulator_probe,
	.driver = अणु
		.name = "da9052-regulator",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init da9052_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da9052_regulator_driver);
पूर्ण
subsys_initcall(da9052_regulator_init);

अटल व्योम __निकास da9052_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&da9052_regulator_driver);
पूर्ण
module_निकास(da9052_regulator_निकास);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("Power Regulator driver for Dialog DA9052 PMIC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-regulator");
