<शैली गुरु>
/*
 * TI TPS65132 Regulator driver
 *
 * Copyright (C) 2017 NVIDIA CORPORATION. All rights reserved.
 *
 * Author: Venkat Reddy Talla <vreddytalla@nvidia.com>
 *		Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

#घोषणा TPS65132_REG_VPOS		0x00
#घोषणा TPS65132_REG_VNEG		0x01
#घोषणा TPS65132_REG_APPS_DISP_DISN	0x03
#घोषणा TPS65132_REG_CONTROL		0x0FF

#घोषणा TPS65132_VOUT_MASK		0x1F
#घोषणा TPS65132_VOUT_N_VOLTAGE		0x15
#घोषणा TPS65132_VOUT_VMIN		4000000
#घोषणा TPS65132_VOUT_VMAX		6000000
#घोषणा TPS65132_VOUT_STEP		100000

#घोषणा TPS65132_REG_APPS_DIS_VPOS		BIT(0)
#घोषणा TPS65132_REG_APPS_DIS_VNEG		BIT(1)

#घोषणा TPS65132_REGULATOR_ID_VPOS	0
#घोषणा TPS65132_REGULATOR_ID_VNEG	1
#घोषणा TPS65132_MAX_REGULATORS		2

#घोषणा TPS65132_ACT_DIS_TIME_SLACK		1000

काष्ठा tps65132_reg_pdata अणु
	काष्ठा gpio_desc *en_gpiod;
	काष्ठा gpio_desc *act_dis_gpiod;
	अचिन्हित पूर्णांक act_dis_समय_us;
	पूर्णांक ena_gpio_state;
पूर्ण;

काष्ठा tps65132_regulator अणु
	काष्ठा device *dev;
	काष्ठा tps65132_reg_pdata reg_pdata[TPS65132_MAX_REGULATORS];
पूर्ण;

अटल पूर्णांक tps65132_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps65132_regulator *tps = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा tps65132_reg_pdata *rpdata = &tps->reg_pdata[id];
	पूर्णांक ret;

	अगर (!IS_ERR(rpdata->en_gpiod)) अणु
		gpiod_set_value_cansleep(rpdata->en_gpiod, 1);
		rpdata->ena_gpio_state = 1;
	पूर्ण

	/* Hardware स्वतःmatically enable disअक्षरge bit in enable */
	अगर (rdev->स्थिरraपूर्णांकs->active_disअक्षरge ==
			REGULATOR_ACTIVE_DISCHARGE_DISABLE) अणु
		ret = regulator_set_active_disअक्षरge_regmap(rdev, false);
		अगर (ret < 0) अणु
			dev_err(tps->dev, "Failed to disable active discharge: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65132_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps65132_regulator *tps = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा tps65132_reg_pdata *rpdata = &tps->reg_pdata[id];

	अगर (!IS_ERR(rpdata->en_gpiod)) अणु
		gpiod_set_value_cansleep(rpdata->en_gpiod, 0);
		rpdata->ena_gpio_state = 0;
	पूर्ण

	अगर (!IS_ERR(rpdata->act_dis_gpiod)) अणु
		gpiod_set_value_cansleep(rpdata->act_dis_gpiod, 1);
		usleep_range(rpdata->act_dis_समय_us, rpdata->act_dis_समय_us +
			     TPS65132_ACT_DIS_TIME_SLACK);
		gpiod_set_value_cansleep(rpdata->act_dis_gpiod, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65132_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps65132_regulator *tps = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा tps65132_reg_pdata *rpdata = &tps->reg_pdata[id];

	अगर (!IS_ERR(rpdata->en_gpiod))
		वापस rpdata->ena_gpio_state;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps65132_regulator_ops = अणु
	.enable = tps65132_regulator_enable,
	.disable = tps65132_regulator_disable,
	.is_enabled = tps65132_regulator_is_enabled,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_active_disअक्षरge = regulator_set_active_disअक्षरge_regmap,
पूर्ण;

अटल पूर्णांक tps65132_of_parse_cb(काष्ठा device_node *np,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config)
अणु
	काष्ठा tps65132_regulator *tps = config->driver_data;
	काष्ठा tps65132_reg_pdata *rpdata = &tps->reg_pdata[desc->id];
	पूर्णांक ret;

	rpdata->en_gpiod = devm_fwnode_gpiod_get(tps->dev, of_fwnode_handle(np),
						 "enable", GPIOD_ASIS,
						 "enable");
	अगर (IS_ERR(rpdata->en_gpiod)) अणु
		ret = PTR_ERR(rpdata->en_gpiod);

		/* Ignore the error other than probe defer */
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		वापस 0;
	पूर्ण

	rpdata->act_dis_gpiod = devm_fwnode_gpiod_get(tps->dev,
						      of_fwnode_handle(np),
						      "active-discharge",
						      GPIOD_ASIS,
						      "active-discharge");
	अगर (IS_ERR(rpdata->act_dis_gpiod)) अणु
		ret = PTR_ERR(rpdata->act_dis_gpiod);

		/* Ignore the error other than probe defer */
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		वापस 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "ti,active-discharge-time-us",
				   &rpdata->act_dis_समय_us);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "Failed to read active discharge time:%d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा TPS65132_REGULATOR_DESC(_id, _name)		\
	[TPS65132_REGULATOR_ID_##_id] = अणु		\
		.name = "tps65132-"#_name,		\
		.supply_name = "vin",			\
		.id = TPS65132_REGULATOR_ID_##_id,	\
		.of_match = of_match_ptr(#_name),	\
		.of_parse_cb	= tps65132_of_parse_cb,	\
		.ops = &tps65132_regulator_ops,		\
		.n_voltages = TPS65132_VOUT_N_VOLTAGE,	\
		.min_uV = TPS65132_VOUT_VMIN,		\
		.uV_step = TPS65132_VOUT_STEP,		\
		.enable_समय = 500,			\
		.vsel_mask = TPS65132_VOUT_MASK,	\
		.vsel_reg = TPS65132_REG_##_id,		\
		.active_disअक्षरge_off = 0,			\
		.active_disअक्षरge_on = TPS65132_REG_APPS_DIS_##_id, \
		.active_disअक्षरge_mask = TPS65132_REG_APPS_DIS_##_id, \
		.active_disअक्षरge_reg = TPS65132_REG_APPS_DISP_DISN, \
		.type = REGULATOR_VOLTAGE,		\
		.owner = THIS_MODULE,			\
	पूर्ण

अटल स्थिर काष्ठा regulator_desc tps_regs_desc[TPS65132_MAX_REGULATORS] = अणु
	TPS65132_REGULATOR_DESC(VPOS, outp),
	TPS65132_REGULATOR_DESC(VNEG, outn),
पूर्ण;

अटल स्थिर काष्ठा regmap_range tps65132_no_reg_ranges[] = अणु
	regmap_reg_range(TPS65132_REG_APPS_DISP_DISN + 1,
			 TPS65132_REG_CONTROL - 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tps65132_no_reg_table = अणु
	.no_ranges = tps65132_no_reg_ranges,
	.n_no_ranges = ARRAY_SIZE(tps65132_no_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config tps65132_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= TPS65132_REG_CONTROL,
	.cache_type	= REGCACHE_NONE,
	.rd_table	= &tps65132_no_reg_table,
	.wr_table	= &tps65132_no_reg_table,
पूर्ण;

अटल पूर्णांक tps65132_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tps65132_regulator *tps;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *rmap;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक id;
	पूर्णांक ret;

	tps = devm_kzalloc(dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	rmap = devm_regmap_init_i2c(client, &tps65132_regmap_config);
	अगर (IS_ERR(rmap)) अणु
		ret = PTR_ERR(rmap);
		dev_err(dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, tps);
	tps->dev = dev;

	क्रम (id = 0; id < TPS65132_MAX_REGULATORS; ++id) अणु
		config.regmap = rmap;
		config.dev = dev;
		config.driver_data = tps;

		rdev = devm_regulator_रेजिस्टर(dev, &tps_regs_desc[id],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(dev, "regulator %s register failed: %d\n",
				tps_regs_desc[id].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65132_id[] = अणु
	अणु.name = "tps65132",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps65132_id);

अटल काष्ठा i2c_driver tps65132_i2c_driver = अणु
	.driver = अणु
		.name = "tps65132",
	पूर्ण,
	.probe_new = tps65132_probe,
	.id_table = tps65132_id,
पूर्ण;

module_i2c_driver(tps65132_i2c_driver);

MODULE_DESCRIPTION("tps65132 regulator driver");
MODULE_AUTHOR("Venkat Reddy Talla <vreddytalla@nvidia.com>");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
