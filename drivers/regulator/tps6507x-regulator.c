<शैली गुरु>
/*
 * tps6507x-regulator.c
 *
 * Regulator driver क्रम TPS65073 PMIC
 *
 * Copyright (C) 2009 Texas Instrument Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/tps6507x.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/tps6507x.h>
#समावेश <linux/regulator/of_regulator.h>

/* DCDC's */
#घोषणा TPS6507X_DCDC_1				0
#घोषणा TPS6507X_DCDC_2				1
#घोषणा TPS6507X_DCDC_3				2
/* LDOs */
#घोषणा TPS6507X_LDO_1				3
#घोषणा TPS6507X_LDO_2				4

#घोषणा TPS6507X_MAX_REG_ID			TPS6507X_LDO_2

/* Number of step-करोwn converters available */
#घोषणा TPS6507X_NUM_DCDC			3
/* Number of LDO voltage regulators  available */
#घोषणा TPS6507X_NUM_LDO			2
/* Number of total regulators available */
#घोषणा TPS6507X_NUM_REGULATOR		(TPS6507X_NUM_DCDC + TPS6507X_NUM_LDO)

/* Supported voltage values क्रम regulators (in microVolts) */
अटल स्थिर अचिन्हित पूर्णांक VDCDCx_VSEL_table[] = अणु
	725000, 750000, 775000, 800000,
	825000, 850000, 875000, 900000,
	925000, 950000, 975000, 1000000,
	1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000,
	1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000,
	1425000, 1450000, 1475000, 1500000,
	1550000, 1600000, 1650000, 1700000,
	1750000, 1800000, 1850000, 1900000,
	1950000, 2000000, 2050000, 2100000,
	2150000, 2200000, 2250000, 2300000,
	2350000, 2400000, 2450000, 2500000,
	2550000, 2600000, 2650000, 2700000,
	2750000, 2800000, 2850000, 2900000,
	3000000, 3100000, 3200000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO1_VSEL_table[] = अणु
	1000000, 1100000, 1200000, 1250000,
	1300000, 1350000, 1400000, 1500000,
	1600000, 1800000, 2500000, 2750000,
	2800000, 3000000, 3100000, 3300000,
पूर्ण;

/* The voltage mapping table क्रम LDO2 is the same as VDCDCx */
#घोषणा LDO2_VSEL_table VDCDCx_VSEL_table

काष्ठा tps_info अणु
	स्थिर अक्षर *name;
	u8 table_len;
	स्थिर अचिन्हित पूर्णांक *table;

	/* Does DCDC high or the low रेजिस्टर defines output voltage? */
	bool defdcdc_शेष;
पूर्ण;

अटल काष्ठा tps_info tps6507x_pmic_regs[] = अणु
	अणु
		.name = "VDCDC1",
		.table_len = ARRAY_SIZE(VDCDCx_VSEL_table),
		.table = VDCDCx_VSEL_table,
	पूर्ण,
	अणु
		.name = "VDCDC2",
		.table_len = ARRAY_SIZE(VDCDCx_VSEL_table),
		.table = VDCDCx_VSEL_table,
	पूर्ण,
	अणु
		.name = "VDCDC3",
		.table_len = ARRAY_SIZE(VDCDCx_VSEL_table),
		.table = VDCDCx_VSEL_table,
	पूर्ण,
	अणु
		.name = "LDO1",
		.table_len = ARRAY_SIZE(LDO1_VSEL_table),
		.table = LDO1_VSEL_table,
	पूर्ण,
	अणु
		.name = "LDO2",
		.table_len = ARRAY_SIZE(LDO2_VSEL_table),
		.table = LDO2_VSEL_table,
	पूर्ण,
पूर्ण;

काष्ठा tps6507x_pmic अणु
	काष्ठा regulator_desc desc[TPS6507X_NUM_REGULATOR];
	काष्ठा tps6507x_dev *mfd;
	काष्ठा tps_info *info[TPS6507X_NUM_REGULATOR];
	काष्ठा mutex io_lock;
पूर्ण;
अटल अंतरभूत पूर्णांक tps6507x_pmic_पढ़ो(काष्ठा tps6507x_pmic *tps, u8 reg)
अणु
	u8 val;
	पूर्णांक err;

	err = tps->mfd->पढ़ो_dev(tps->mfd, reg, 1, &val);

	अगर (err)
		वापस err;

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक tps6507x_pmic_ग_लिखो(काष्ठा tps6507x_pmic *tps, u8 reg, u8 val)
अणु
	वापस tps->mfd->ग_लिखो_dev(tps->mfd, reg, 1, &val);
पूर्ण

अटल पूर्णांक tps6507x_pmic_set_bits(काष्ठा tps6507x_pmic *tps, u8 reg, u8 mask)
अणु
	पूर्णांक err, data;

	mutex_lock(&tps->io_lock);

	data = tps6507x_pmic_पढ़ो(tps, reg);
	अगर (data < 0) अणु
		dev_err(tps->mfd->dev, "Read from reg 0x%x failed\n", reg);
		err = data;
		जाओ out;
	पूर्ण

	data |= mask;
	err = tps6507x_pmic_ग_लिखो(tps, reg, data);
	अगर (err)
		dev_err(tps->mfd->dev, "Write for reg 0x%x failed\n", reg);

out:
	mutex_unlock(&tps->io_lock);
	वापस err;
पूर्ण

अटल पूर्णांक tps6507x_pmic_clear_bits(काष्ठा tps6507x_pmic *tps, u8 reg, u8 mask)
अणु
	पूर्णांक err, data;

	mutex_lock(&tps->io_lock);

	data = tps6507x_pmic_पढ़ो(tps, reg);
	अगर (data < 0) अणु
		dev_err(tps->mfd->dev, "Read from reg 0x%x failed\n", reg);
		err = data;
		जाओ out;
	पूर्ण

	data &= ~mask;
	err = tps6507x_pmic_ग_लिखो(tps, reg, data);
	अगर (err)
		dev_err(tps->mfd->dev, "Write for reg 0x%x failed\n", reg);

out:
	mutex_unlock(&tps->io_lock);
	वापस err;
पूर्ण

अटल पूर्णांक tps6507x_pmic_reg_पढ़ो(काष्ठा tps6507x_pmic *tps, u8 reg)
अणु
	पूर्णांक data;

	mutex_lock(&tps->io_lock);

	data = tps6507x_pmic_पढ़ो(tps, reg);
	अगर (data < 0)
		dev_err(tps->mfd->dev, "Read from reg 0x%x failed\n", reg);

	mutex_unlock(&tps->io_lock);
	वापस data;
पूर्ण

अटल पूर्णांक tps6507x_pmic_reg_ग_लिखो(काष्ठा tps6507x_pmic *tps, u8 reg, u8 val)
अणु
	पूर्णांक err;

	mutex_lock(&tps->io_lock);

	err = tps6507x_pmic_ग_लिखो(tps, reg, val);
	अगर (err < 0)
		dev_err(tps->mfd->dev, "Write for reg 0x%x failed\n", reg);

	mutex_unlock(&tps->io_lock);
	वापस err;
पूर्ण

अटल पूर्णांक tps6507x_pmic_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps6507x_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक data, rid = rdev_get_id(dev);
	u8 shअगरt;

	अगर (rid < TPS6507X_DCDC_1 || rid > TPS6507X_LDO_2)
		वापस -EINVAL;

	shअगरt = TPS6507X_MAX_REG_ID - rid;
	data = tps6507x_pmic_reg_पढ़ो(tps, TPS6507X_REG_CON_CTRL1);

	अगर (data < 0)
		वापस data;
	अन्यथा
		वापस (data & 1<<shअगरt) ? 1 : 0;
पूर्ण

अटल पूर्णांक tps6507x_pmic_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps6507x_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक rid = rdev_get_id(dev);
	u8 shअगरt;

	अगर (rid < TPS6507X_DCDC_1 || rid > TPS6507X_LDO_2)
		वापस -EINVAL;

	shअगरt = TPS6507X_MAX_REG_ID - rid;
	वापस tps6507x_pmic_set_bits(tps, TPS6507X_REG_CON_CTRL1, 1 << shअगरt);
पूर्ण

अटल पूर्णांक tps6507x_pmic_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps6507x_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक rid = rdev_get_id(dev);
	u8 shअगरt;

	अगर (rid < TPS6507X_DCDC_1 || rid > TPS6507X_LDO_2)
		वापस -EINVAL;

	shअगरt = TPS6507X_MAX_REG_ID - rid;
	वापस tps6507x_pmic_clear_bits(tps, TPS6507X_REG_CON_CTRL1,
					1 << shअगरt);
पूर्ण

अटल पूर्णांक tps6507x_pmic_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps6507x_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक data, rid = rdev_get_id(dev);
	u8 reg, mask;

	चयन (rid) अणु
	हाल TPS6507X_DCDC_1:
		reg = TPS6507X_REG_DEFDCDC1;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		अवरोध;
	हाल TPS6507X_DCDC_2:
		अगर (tps->info[rid]->defdcdc_शेष)
			reg = TPS6507X_REG_DEFDCDC2_HIGH;
		अन्यथा
			reg = TPS6507X_REG_DEFDCDC2_LOW;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		अवरोध;
	हाल TPS6507X_DCDC_3:
		अगर (tps->info[rid]->defdcdc_शेष)
			reg = TPS6507X_REG_DEFDCDC3_HIGH;
		अन्यथा
			reg = TPS6507X_REG_DEFDCDC3_LOW;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		अवरोध;
	हाल TPS6507X_LDO_1:
		reg = TPS6507X_REG_LDO_CTRL1;
		mask = TPS6507X_REG_LDO_CTRL1_LDO1_MASK;
		अवरोध;
	हाल TPS6507X_LDO_2:
		reg = TPS6507X_REG_DEFLDO2;
		mask = TPS6507X_REG_DEFLDO2_LDO2_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data = tps6507x_pmic_reg_पढ़ो(tps, reg);
	अगर (data < 0)
		वापस data;

	data &= mask;
	वापस data;
पूर्ण

अटल पूर्णांक tps6507x_pmic_set_voltage_sel(काष्ठा regulator_dev *dev,
					  अचिन्हित selector)
अणु
	काष्ठा tps6507x_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक data, rid = rdev_get_id(dev);
	u8 reg, mask;

	चयन (rid) अणु
	हाल TPS6507X_DCDC_1:
		reg = TPS6507X_REG_DEFDCDC1;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		अवरोध;
	हाल TPS6507X_DCDC_2:
		अगर (tps->info[rid]->defdcdc_शेष)
			reg = TPS6507X_REG_DEFDCDC2_HIGH;
		अन्यथा
			reg = TPS6507X_REG_DEFDCDC2_LOW;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		अवरोध;
	हाल TPS6507X_DCDC_3:
		अगर (tps->info[rid]->defdcdc_शेष)
			reg = TPS6507X_REG_DEFDCDC3_HIGH;
		अन्यथा
			reg = TPS6507X_REG_DEFDCDC3_LOW;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		अवरोध;
	हाल TPS6507X_LDO_1:
		reg = TPS6507X_REG_LDO_CTRL1;
		mask = TPS6507X_REG_LDO_CTRL1_LDO1_MASK;
		अवरोध;
	हाल TPS6507X_LDO_2:
		reg = TPS6507X_REG_DEFLDO2;
		mask = TPS6507X_REG_DEFLDO2_LDO2_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data = tps6507x_pmic_reg_पढ़ो(tps, reg);
	अगर (data < 0)
		वापस data;

	data &= ~mask;
	data |= selector;

	वापस tps6507x_pmic_reg_ग_लिखो(tps, reg, data);
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps6507x_pmic_ops = अणु
	.is_enabled = tps6507x_pmic_is_enabled,
	.enable = tps6507x_pmic_enable,
	.disable = tps6507x_pmic_disable,
	.get_voltage_sel = tps6507x_pmic_get_voltage_sel,
	.set_voltage_sel = tps6507x_pmic_set_voltage_sel,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
पूर्ण;

अटल पूर्णांक tps6507x_pmic_of_parse_cb(काष्ठा device_node *np,
				     स्थिर काष्ठा regulator_desc *desc,
				     काष्ठा regulator_config *config)
अणु
	काष्ठा tps6507x_pmic *tps = config->driver_data;
	काष्ठा tps_info *info = tps->info[desc->id];
	u32 prop;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "ti,defdcdc_default", &prop);
	अगर (!ret)
		info->defdcdc_शेष = prop;

	वापस 0;
पूर्ण

अटल पूर्णांक tps6507x_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps6507x_dev *tps6507x_dev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps_info *info = &tps6507x_pmic_regs[0];
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_init_data *init_data = शून्य;
	काष्ठा regulator_dev *rdev;
	काष्ठा tps6507x_pmic *tps;
	काष्ठा tps6507x_board *tps_board;
	पूर्णांक i;

	/**
	 * tps_board poपूर्णांकs to pmic related स्थिरants
	 * coming from the board-evm file.
	 */

	tps_board = dev_get_platdata(tps6507x_dev->dev);
	अगर (tps_board)
		init_data = tps_board->tps6507x_pmic_init_data;

	tps = devm_kzalloc(&pdev->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	mutex_init(&tps->io_lock);

	/* common क्रम all regulators */
	tps->mfd = tps6507x_dev;

	क्रम (i = 0; i < TPS6507X_NUM_REGULATOR; i++, info++) अणु
		/* Register the regulators */
		tps->info[i] = info;
		अगर (init_data && init_data[i].driver_data) अणु
			काष्ठा tps6507x_reg_platक्रमm_data *data =
					init_data[i].driver_data;
			info->defdcdc_शेष = data->defdcdc_शेष;
		पूर्ण

		tps->desc[i].name = info->name;
		tps->desc[i].of_match = of_match_ptr(info->name);
		tps->desc[i].regulators_node = of_match_ptr("regulators");
		tps->desc[i].of_parse_cb = tps6507x_pmic_of_parse_cb;
		tps->desc[i].id = i;
		tps->desc[i].n_voltages = info->table_len;
		tps->desc[i].volt_table = info->table;
		tps->desc[i].ops = &tps6507x_pmic_ops;
		tps->desc[i].type = REGULATOR_VOLTAGE;
		tps->desc[i].owner = THIS_MODULE;

		config.dev = tps6507x_dev->dev;
		config.init_data = init_data;
		config.driver_data = tps;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &tps->desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(tps6507x_dev->dev,
				"failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	tps6507x_dev->pmic = tps;
	platक्रमm_set_drvdata(pdev, tps6507x_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps6507x_pmic_driver = अणु
	.driver = अणु
		.name = "tps6507x-pmic",
	पूर्ण,
	.probe = tps6507x_pmic_probe,
पूर्ण;

अटल पूर्णांक __init tps6507x_pmic_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps6507x_pmic_driver);
पूर्ण
subsys_initcall(tps6507x_pmic_init);

अटल व्योम __निकास tps6507x_pmic_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps6507x_pmic_driver);
पूर्ण
module_निकास(tps6507x_pmic_cleanup);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("TPS6507x voltage regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps6507x-pmic");
