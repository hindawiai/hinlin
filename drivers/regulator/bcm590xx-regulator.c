<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom BCM590xx regulator driver
 *
 * Copyright 2014 Linaro Limited
 * Author: Matt Porter <mporter@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/bcm590xx.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/* I2C slave 0 रेजिस्टरs */
#घोषणा BCM590XX_RFLDOPMCTRL1	0x60
#घोषणा BCM590XX_IOSR1PMCTRL1	0x7a
#घोषणा BCM590XX_IOSR2PMCTRL1	0x7c
#घोषणा BCM590XX_CSRPMCTRL1	0x7e
#घोषणा BCM590XX_SDSR1PMCTRL1	0x82
#घोषणा BCM590XX_SDSR2PMCTRL1	0x86
#घोषणा BCM590XX_MSRPMCTRL1	0x8a
#घोषणा BCM590XX_VSRPMCTRL1	0x8e
#घोषणा BCM590XX_RFLDOCTRL	0x96
#घोषणा BCM590XX_CSRVOUT1	0xc0

/* I2C slave 1 रेजिस्टरs */
#घोषणा BCM590XX_GPLDO5PMCTRL1	0x16
#घोषणा BCM590XX_GPLDO6PMCTRL1	0x18
#घोषणा BCM590XX_GPLDO1CTRL	0x1a
#घोषणा BCM590XX_GPLDO2CTRL	0x1b
#घोषणा BCM590XX_GPLDO3CTRL	0x1c
#घोषणा BCM590XX_GPLDO4CTRL	0x1d
#घोषणा BCM590XX_GPLDO5CTRL	0x1e
#घोषणा BCM590XX_GPLDO6CTRL	0x1f
#घोषणा BCM590XX_OTG_CTRL	0x40
#घोषणा BCM590XX_GPLDO1PMCTRL1	0x57
#घोषणा BCM590XX_GPLDO2PMCTRL1	0x59
#घोषणा BCM590XX_GPLDO3PMCTRL1	0x5b
#घोषणा BCM590XX_GPLDO4PMCTRL1	0x5d

#घोषणा BCM590XX_REG_ENABLE	BIT(7)
#घोषणा BCM590XX_VBUS_ENABLE	BIT(2)
#घोषणा BCM590XX_LDO_VSEL_MASK	GENMASK(5, 3)
#घोषणा BCM590XX_SR_VSEL_MASK	GENMASK(5, 0)

/*
 * RFLDO to VSR regulators are
 * accessed via I2C slave 0
 */

/* LDO regulator IDs */
#घोषणा BCM590XX_REG_RFLDO	0
#घोषणा BCM590XX_REG_CAMLDO1	1
#घोषणा BCM590XX_REG_CAMLDO2	2
#घोषणा BCM590XX_REG_SIMLDO1	3
#घोषणा BCM590XX_REG_SIMLDO2	4
#घोषणा BCM590XX_REG_SDLDO	5
#घोषणा BCM590XX_REG_SDXLDO	6
#घोषणा BCM590XX_REG_MMCLDO1	7
#घोषणा BCM590XX_REG_MMCLDO2	8
#घोषणा BCM590XX_REG_AUDLDO	9
#घोषणा BCM590XX_REG_MICLDO	10
#घोषणा BCM590XX_REG_USBLDO	11
#घोषणा BCM590XX_REG_VIBLDO	12

/* DCDC regulator IDs */
#घोषणा BCM590XX_REG_CSR	13
#घोषणा BCM590XX_REG_IOSR1	14
#घोषणा BCM590XX_REG_IOSR2	15
#घोषणा BCM590XX_REG_MSR	16
#घोषणा BCM590XX_REG_SDSR1	17
#घोषणा BCM590XX_REG_SDSR2	18
#घोषणा BCM590XX_REG_VSR	19

/*
 * GPLDO1 to VBUS regulators are
 * accessed via I2C slave 1
 */

#घोषणा BCM590XX_REG_GPLDO1	20
#घोषणा BCM590XX_REG_GPLDO2	21
#घोषणा BCM590XX_REG_GPLDO3	22
#घोषणा BCM590XX_REG_GPLDO4	23
#घोषणा BCM590XX_REG_GPLDO5	24
#घोषणा BCM590XX_REG_GPLDO6	25
#घोषणा BCM590XX_REG_VBUS	26

#घोषणा BCM590XX_NUM_REGS	27

#घोषणा BCM590XX_REG_IS_LDO(n)	(n < BCM590XX_REG_CSR)
#घोषणा BCM590XX_REG_IS_GPLDO(n) \
	((n > BCM590XX_REG_VSR) && (n < BCM590XX_REG_VBUS))
#घोषणा BCM590XX_REG_IS_VBUS(n)	(n == BCM590XX_REG_VBUS)

/* LDO group A: supported voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक lकरो_a_table[] = अणु
	1200000, 1800000, 2500000, 2700000, 2800000,
	2900000, 3000000, 3300000,
पूर्ण;

/* LDO group C: supported voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक lकरो_c_table[] = अणु
	3100000, 1800000, 2500000, 2700000, 2800000,
	2900000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_vbus[] = अणु
	5000000,
पूर्ण;

/* DCDC group CSR: supported voltages in microvolts */
अटल स्थिर काष्ठा linear_range dcdc_csr_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(860000, 2, 50, 10000),
	REGULATOR_LINEAR_RANGE(1360000, 51, 55, 20000),
	REGULATOR_LINEAR_RANGE(900000, 56, 63, 0),
पूर्ण;

/* DCDC group IOSR1: supported voltages in microvolts */
अटल स्थिर काष्ठा linear_range dcdc_iosr1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(860000, 2, 51, 10000),
	REGULATOR_LINEAR_RANGE(1500000, 52, 52, 0),
	REGULATOR_LINEAR_RANGE(1800000, 53, 53, 0),
	REGULATOR_LINEAR_RANGE(900000, 54, 63, 0),
पूर्ण;

/* DCDC group SDSR1: supported voltages in microvolts */
अटल स्थिर काष्ठा linear_range dcdc_sdsr1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(860000, 2, 50, 10000),
	REGULATOR_LINEAR_RANGE(1340000, 51, 51, 0),
	REGULATOR_LINEAR_RANGE(900000, 52, 63, 0),
पूर्ण;

काष्ठा bcm590xx_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *vin_name;
	u8 n_voltages;
	स्थिर अचिन्हित पूर्णांक *volt_table;
	u8 n_linear_ranges;
	स्थिर काष्ठा linear_range *linear_ranges;
पूर्ण;

#घोषणा BCM590XX_REG_TABLE(_name, _table) \
	अणु \
		.name = #_name, \
		.n_voltages = ARRAY_SIZE(_table), \
		.volt_table = _table, \
	पूर्ण

#घोषणा BCM590XX_REG_RANGES(_name, _ranges) \
	अणु \
		.name = #_name, \
		.n_voltages = 64, \
		.n_linear_ranges = ARRAY_SIZE(_ranges), \
		.linear_ranges = _ranges, \
	पूर्ण

अटल काष्ठा bcm590xx_info bcm590xx_regs[] = अणु
	BCM590XX_REG_TABLE(rflकरो, lकरो_a_table),
	BCM590XX_REG_TABLE(camlकरो1, lकरो_c_table),
	BCM590XX_REG_TABLE(camlकरो2, lकरो_c_table),
	BCM590XX_REG_TABLE(simlकरो1, lकरो_a_table),
	BCM590XX_REG_TABLE(simlकरो2, lकरो_a_table),
	BCM590XX_REG_TABLE(sdlकरो, lकरो_c_table),
	BCM590XX_REG_TABLE(sdxlकरो, lकरो_a_table),
	BCM590XX_REG_TABLE(mmclकरो1, lकरो_a_table),
	BCM590XX_REG_TABLE(mmclकरो2, lकरो_a_table),
	BCM590XX_REG_TABLE(audlकरो, lकरो_a_table),
	BCM590XX_REG_TABLE(miclकरो, lकरो_a_table),
	BCM590XX_REG_TABLE(usblकरो, lकरो_a_table),
	BCM590XX_REG_TABLE(viblकरो, lकरो_c_table),
	BCM590XX_REG_RANGES(csr, dcdc_csr_ranges),
	BCM590XX_REG_RANGES(iosr1, dcdc_iosr1_ranges),
	BCM590XX_REG_RANGES(iosr2, dcdc_iosr1_ranges),
	BCM590XX_REG_RANGES(msr, dcdc_iosr1_ranges),
	BCM590XX_REG_RANGES(sdsr1, dcdc_sdsr1_ranges),
	BCM590XX_REG_RANGES(sdsr2, dcdc_iosr1_ranges),
	BCM590XX_REG_RANGES(vsr, dcdc_iosr1_ranges),
	BCM590XX_REG_TABLE(gplकरो1, lकरो_a_table),
	BCM590XX_REG_TABLE(gplकरो2, lकरो_a_table),
	BCM590XX_REG_TABLE(gplकरो3, lकरो_a_table),
	BCM590XX_REG_TABLE(gplकरो4, lकरो_a_table),
	BCM590XX_REG_TABLE(gplकरो5, lकरो_a_table),
	BCM590XX_REG_TABLE(gplकरो6, lकरो_a_table),
	BCM590XX_REG_TABLE(vbus, lकरो_vbus),
पूर्ण;

काष्ठा bcm590xx_reg अणु
	काष्ठा regulator_desc *desc;
	काष्ठा bcm590xx *mfd;
पूर्ण;

अटल पूर्णांक bcm590xx_get_vsel_रेजिस्टर(पूर्णांक id)
अणु
	अगर (BCM590XX_REG_IS_LDO(id))
		वापस BCM590XX_RFLDOCTRL + id;
	अन्यथा अगर (BCM590XX_REG_IS_GPLDO(id))
		वापस BCM590XX_GPLDO1CTRL + id;
	अन्यथा
		वापस BCM590XX_CSRVOUT1 + (id - BCM590XX_REG_CSR) * 3;
पूर्ण

अटल पूर्णांक bcm590xx_get_enable_रेजिस्टर(पूर्णांक id)
अणु
	पूर्णांक reg = 0;

	अगर (BCM590XX_REG_IS_LDO(id))
		reg = BCM590XX_RFLDOPMCTRL1 + id * 2;
	अन्यथा अगर (BCM590XX_REG_IS_GPLDO(id))
		reg = BCM590XX_GPLDO1PMCTRL1 + id * 2;
	अन्यथा
		चयन (id) अणु
		हाल BCM590XX_REG_CSR:
			reg = BCM590XX_CSRPMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_IOSR1:
			reg = BCM590XX_IOSR1PMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_IOSR2:
			reg = BCM590XX_IOSR2PMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_MSR:
			reg = BCM590XX_MSRPMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_SDSR1:
			reg = BCM590XX_SDSR1PMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_SDSR2:
			reg = BCM590XX_SDSR2PMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_VSR:
			reg = BCM590XX_VSRPMCTRL1;
			अवरोध;
		हाल BCM590XX_REG_VBUS:
			reg = BCM590XX_OTG_CTRL;
			अवरोध;
		पूर्ण


	वापस reg;
पूर्ण

अटल स्थिर काष्ठा regulator_ops bcm590xx_ops_lकरो = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_iterate,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bcm590xx_ops_dcdc = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bcm590xx_ops_vbus = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
पूर्ण;

अटल पूर्णांक bcm590xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm590xx *bcm590xx = dev_get_drvdata(pdev->dev.parent);
	काष्ठा bcm590xx_reg *pmu;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा bcm590xx_info *info;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	pmu = devm_kzalloc(&pdev->dev, माप(*pmu), GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;

	pmu->mfd = bcm590xx;

	platक्रमm_set_drvdata(pdev, pmu);

	pmu->desc = devm_kसुस्मृति(&pdev->dev,
				 BCM590XX_NUM_REGS,
				 माप(काष्ठा regulator_desc),
				 GFP_KERNEL);
	अगर (!pmu->desc)
		वापस -ENOMEM;

	info = bcm590xx_regs;

	क्रम (i = 0; i < BCM590XX_NUM_REGS; i++, info++) अणु
		/* Register the regulators */
		pmu->desc[i].name = info->name;
		pmu->desc[i].of_match = of_match_ptr(info->name);
		pmu->desc[i].regulators_node = of_match_ptr("regulators");
		pmu->desc[i].supply_name = info->vin_name;
		pmu->desc[i].id = i;
		pmu->desc[i].volt_table = info->volt_table;
		pmu->desc[i].n_voltages = info->n_voltages;
		pmu->desc[i].linear_ranges = info->linear_ranges;
		pmu->desc[i].n_linear_ranges = info->n_linear_ranges;

		अगर ((BCM590XX_REG_IS_LDO(i)) || (BCM590XX_REG_IS_GPLDO(i))) अणु
			pmu->desc[i].ops = &bcm590xx_ops_lकरो;
			pmu->desc[i].vsel_mask = BCM590XX_LDO_VSEL_MASK;
		पूर्ण अन्यथा अगर (BCM590XX_REG_IS_VBUS(i))
			pmu->desc[i].ops = &bcm590xx_ops_vbus;
		अन्यथा अणु
			pmu->desc[i].ops = &bcm590xx_ops_dcdc;
			pmu->desc[i].vsel_mask = BCM590XX_SR_VSEL_MASK;
		पूर्ण

		अगर (BCM590XX_REG_IS_VBUS(i))
			pmu->desc[i].enable_mask = BCM590XX_VBUS_ENABLE;
		अन्यथा अणु
			pmu->desc[i].vsel_reg = bcm590xx_get_vsel_रेजिस्टर(i);
			pmu->desc[i].enable_is_inverted = true;
			pmu->desc[i].enable_mask = BCM590XX_REG_ENABLE;
		पूर्ण
		pmu->desc[i].enable_reg = bcm590xx_get_enable_रेजिस्टर(i);
		pmu->desc[i].type = REGULATOR_VOLTAGE;
		pmu->desc[i].owner = THIS_MODULE;

		config.dev = bcm590xx->dev;
		config.driver_data = pmu;
		अगर (BCM590XX_REG_IS_GPLDO(i) || BCM590XX_REG_IS_VBUS(i))
			config.regmap = bcm590xx->regmap_sec;
		अन्यथा
			config.regmap = bcm590xx->regmap_pri;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &pmu->desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(bcm590xx->dev,
				"failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm590xx_regulator_driver = अणु
	.driver = अणु
		.name = "bcm590xx-vregs",
	पूर्ण,
	.probe = bcm590xx_probe,
पूर्ण;
module_platक्रमm_driver(bcm590xx_regulator_driver);

MODULE_AUTHOR("Matt Porter <mporter@linaro.org>");
MODULE_DESCRIPTION("BCM590xx voltage regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bcm590xx-vregs");
