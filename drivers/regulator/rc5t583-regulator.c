<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम RICOH RC5T583 घातer management chip.
 *
 * Copyright (c) 2011-2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Laxman dewangan <ldewangan@nvidia.com>
 *
 * based on code
 *      Copyright (C) 2011 RICOH COMPANY,LTD
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mfd/rc5t583.h>

काष्ठा rc5t583_regulator_info अणु
	पूर्णांक			deepsleep_id;

	/* Regulator रेजिस्टर address.*/
	uपूर्णांक8_t			reg_disc_reg;
	uपूर्णांक8_t			disc_bit;
	uपूर्णांक8_t			deepsleep_reg;

	/* Regulator specअगरic turn-on delay  and voltage settling समय*/
	पूर्णांक			enable_uv_per_us;

	/* Used by regulator core */
	काष्ठा regulator_desc	desc;
पूर्ण;

अटल पूर्णांक rc5t583_regulator_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rc5t583_regulator_info *reg_info = rdev_get_drvdata(rdev);
	पूर्णांक vsel = regulator_get_voltage_sel_regmap(rdev);
	पूर्णांक curr_uV = regulator_list_voltage_linear(rdev, vsel);

	वापस DIV_ROUND_UP(curr_uV, reg_info->enable_uv_per_us);
पूर्ण

अटल स्थिर काष्ठा regulator_ops rc5t583_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.enable_समय		= rc5t583_regulator_enable_समय,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
पूर्ण;

#घोषणा RC5T583_REG(_id, _en_reg, _en_bit, _disc_reg, _disc_bit, \
		_vout_mask, _min_mv, _max_mv, _step_uV, _enable_mv) \
अणु								\
	.reg_disc_reg	= RC5T583_REG_##_disc_reg,		\
	.disc_bit	= _disc_bit,				\
	.deepsleep_reg	= RC5T583_REG_##_id##DAC_DS,		\
	.enable_uv_per_us = _enable_mv * 1000,			\
	.deepsleep_id	= RC5T583_DS_##_id,			\
	.desc = अणु						\
		.name = "rc5t583-regulator-"#_id,		\
		.id = RC5T583_REGULATOR_##_id,			\
		.n_voltages = (_max_mv - _min_mv) * 1000 / _step_uV + 1, \
		.ops = &rc5t583_ops,				\
		.type = REGULATOR_VOLTAGE,			\
		.owner = THIS_MODULE,				\
		.vsel_reg = RC5T583_REG_##_id##DAC,		\
		.vsel_mask = _vout_mask,			\
		.enable_reg = RC5T583_REG_##_en_reg,		\
		.enable_mask = BIT(_en_bit),			\
		.min_uV	= _min_mv * 1000,			\
		.uV_step = _step_uV,				\
		.ramp_delay = 40 * 1000,			\
	पूर्ण,							\
पूर्ण

अटल काष्ठा rc5t583_regulator_info rc5t583_reg_info[RC5T583_REGULATOR_MAX] = अणु
	RC5T583_REG(DC0, DC0CTL, 0, DC0CTL, 1, 0x7F, 700, 1500, 12500, 4),
	RC5T583_REG(DC1, DC1CTL, 0, DC1CTL, 1, 0x7F, 700, 1500, 12500, 14),
	RC5T583_REG(DC2, DC2CTL, 0, DC2CTL, 1, 0x7F, 900, 2400, 12500, 14),
	RC5T583_REG(DC3, DC3CTL, 0, DC3CTL, 1, 0x7F, 900, 2400, 12500, 14),
	RC5T583_REG(LDO0, LDOEN2, 0, LDODIS2, 0, 0x7F, 900, 3400, 25000, 160),
	RC5T583_REG(LDO1, LDOEN2, 1, LDODIS2, 1, 0x7F, 900, 3400, 25000, 160),
	RC5T583_REG(LDO2, LDOEN2, 2, LDODIS2, 2, 0x7F, 900, 3400, 25000, 160),
	RC5T583_REG(LDO3, LDOEN2, 3, LDODIS2, 3, 0x7F, 900, 3400, 25000, 160),
	RC5T583_REG(LDO4, LDOEN2, 4, LDODIS2, 4, 0x3F, 750, 1500, 12500, 133),
	RC5T583_REG(LDO5, LDOEN2, 5, LDODIS2, 5, 0x7F, 900, 3400, 25000, 267),
	RC5T583_REG(LDO6, LDOEN2, 6, LDODIS2, 6, 0x7F, 900, 3400, 25000, 133),
	RC5T583_REG(LDO7, LDOEN2, 7, LDODIS2, 7, 0x7F, 900, 3400, 25000, 233),
	RC5T583_REG(LDO8, LDOEN1, 0, LDODIS1, 0, 0x7F, 900, 3400, 25000, 233),
	RC5T583_REG(LDO9, LDOEN1, 1, LDODIS1, 1, 0x7F, 900, 3400, 25000, 133),
पूर्ण;

अटल पूर्णांक rc5t583_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा rc5t583_platक्रमm_data *pdata = dev_get_platdata(rc5t583->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा rc5t583_regulator_info *ri;
	पूर्णांक ret;
	पूर्णांक id;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data, exiting...\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (id = 0; id < RC5T583_REGULATOR_MAX; ++id) अणु
		ri = &rc5t583_reg_info[id];

		अगर (ri->deepsleep_id == RC5T583_DS_NONE)
			जाओ skip_ext_pwr_config;

		ret = rc5t583_ext_घातer_req_config(rc5t583->dev,
				ri->deepsleep_id,
				pdata->regulator_ext_pwr_control[id],
				pdata->regulator_deepsleep_slot[id]);
		/*
		 * Configuring बाह्यal control is not a major issue,
		 * just give warning.
		 */
		अगर (ret < 0)
			dev_warn(&pdev->dev,
				"Failed to configure ext control %d\n", id);

skip_ext_pwr_config:
		config.dev = &pdev->dev;
		config.init_data = pdata->reg_init_data[id];
		config.driver_data = ri;
		config.regmap = rc5t583->regmap;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &ri->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "Failed to register regulator %s\n",
						ri->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rc5t583_regulator_driver = अणु
	.driver	= अणु
		.name	= "rc5t583-regulator",
	पूर्ण,
	.probe		= rc5t583_regulator_probe,
पूर्ण;

अटल पूर्णांक __init rc5t583_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rc5t583_regulator_driver);
पूर्ण
subsys_initcall(rc5t583_regulator_init);

अटल व्योम __निकास rc5t583_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rc5t583_regulator_driver);
पूर्ण
module_निकास(rc5t583_regulator_निकास);

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_DESCRIPTION("RC5T583 regulator driver");
MODULE_ALIAS("platform:rc5t583-regulator");
MODULE_LICENSE("GPL v2");
