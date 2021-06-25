<शैली गुरु>
/*
 * tps62360.c -- TI tps62360
 *
 * Driver क्रम processor core supply tps62360, tps62361B, tps62362 and tps62363.
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/tps62360.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

/* Register definitions */
#घोषणा REG_VSET0		0
#घोषणा REG_VSET1		1
#घोषणा REG_VSET2		2
#घोषणा REG_VSET3		3
#घोषणा REG_CONTROL		4
#घोषणा REG_TEMP		5
#घोषणा REG_RAMPCTRL		6
#घोषणा REG_CHIPID		8

#घोषणा FORCE_PWM_ENABLE	BIT(7)

क्रमागत chips अणुTPS62360, TPS62361, TPS62362, TPS62363पूर्ण;

#घोषणा TPS62360_BASE_VOLTAGE	770000
#घोषणा TPS62360_N_VOLTAGES	64

#घोषणा TPS62361_BASE_VOLTAGE	500000
#घोषणा TPS62361_N_VOLTAGES	128

/* tps 62360 chip inक्रमmation */
काष्ठा tps62360_chip अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	पूर्णांक vsel0_gpio;
	पूर्णांक vsel1_gpio;
	u8 voltage_reg_mask;
	bool en_पूर्णांकernal_pulldn;
	bool en_disअक्षरge;
	bool valid_gpios;
	पूर्णांक lru_index[4];
	पूर्णांक curr_vset_vsel[4];
	पूर्णांक curr_vset_id;
पूर्ण;

/*
 * find_voltage_set_रेजिस्टर: Find new voltage configuration रेजिस्टर
 * (VSET) id.
 * The finding of the new VSET रेजिस्टर will be based on the LRU mechanism.
 * Each VSET रेजिस्टर will have dअगरferent voltage configured . This
 * Function will look अगर any of the VSET रेजिस्टर have requested voltage set
 * or not.
 *     - If it is alपढ़ोy there then it will make that रेजिस्टर as most
 *       recently used and वापस as found so that caller need not to set
 *       the VSET रेजिस्टर but need to set the proper gpios to select this
 *       VSET रेजिस्टर.
 *     - If requested voltage is not found then it will use the least
 *       recently mechanism to get new VSET रेजिस्टर क्रम new configuration
 *       and will वापस not_found so that caller need to set new VSET
 *       रेजिस्टर and then gpios (both).
 */
अटल bool find_voltage_set_रेजिस्टर(काष्ठा tps62360_chip *tps,
		पूर्णांक req_vsel, पूर्णांक *vset_reg_id)
अणु
	पूर्णांक i;
	bool found = false;
	पूर्णांक new_vset_reg = tps->lru_index[3];
	पूर्णांक found_index = 3;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (tps->curr_vset_vsel[tps->lru_index[i]] == req_vsel) अणु
			new_vset_reg = tps->lru_index[i];
			found_index = i;
			found = true;
			जाओ update_lru_index;
		पूर्ण
	पूर्ण

update_lru_index:
	क्रम (i = found_index; i > 0; i--)
		tps->lru_index[i] = tps->lru_index[i - 1];

	tps->lru_index[0] = new_vset_reg;
	*vset_reg_id = new_vset_reg;
	वापस found;
पूर्ण

अटल पूर्णांक tps62360_dcdc_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps62360_chip *tps = rdev_get_drvdata(dev);
	पूर्णांक vsel;
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps->regmap, REG_VSET0 + tps->curr_vset_id, &data);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "%s(): register %d read failed with err %d\n",
			__func__, REG_VSET0 + tps->curr_vset_id, ret);
		वापस ret;
	पूर्ण
	vsel = (पूर्णांक)data & tps->voltage_reg_mask;
	वापस vsel;
पूर्ण

अटल पूर्णांक tps62360_dcdc_set_voltage_sel(काष्ठा regulator_dev *dev,
					 अचिन्हित selector)
अणु
	काष्ठा tps62360_chip *tps = rdev_get_drvdata(dev);
	पूर्णांक ret;
	bool found = false;
	पूर्णांक new_vset_id = tps->curr_vset_id;

	/*
	 * If gpios are available to select the VSET रेजिस्टर then least
	 * recently used रेजिस्टर क्रम new configuration.
	 */
	अगर (tps->valid_gpios)
		found = find_voltage_set_रेजिस्टर(tps, selector, &new_vset_id);

	अगर (!found) अणु
		ret = regmap_update_bits(tps->regmap, REG_VSET0 + new_vset_id,
				tps->voltage_reg_mask, selector);
		अगर (ret < 0) अणु
			dev_err(tps->dev,
				"%s(): register %d update failed with err %d\n",
				 __func__, REG_VSET0 + new_vset_id, ret);
			वापस ret;
		पूर्ण
		tps->curr_vset_id = new_vset_id;
		tps->curr_vset_vsel[new_vset_id] = selector;
	पूर्ण

	/* Select proper VSET रेजिस्टर vio gpios */
	अगर (tps->valid_gpios) अणु
		gpio_set_value_cansleep(tps->vsel0_gpio, new_vset_id & 0x1);
		gpio_set_value_cansleep(tps->vsel1_gpio,
					(new_vset_id >> 1) & 0x1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps62360_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा tps62360_chip *tps = rdev_get_drvdata(rdev);
	पूर्णांक i;
	पूर्णांक val;
	पूर्णांक ret;

	/* Enable क्रमce PWM mode in FAST mode only. */
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = FORCE_PWM_ENABLE;
		अवरोध;

	हाल REGULATOR_MODE_NORMAL:
		val = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!tps->valid_gpios) अणु
		ret = regmap_update_bits(tps->regmap,
			REG_VSET0 + tps->curr_vset_id, FORCE_PWM_ENABLE, val);
		अगर (ret < 0)
			dev_err(tps->dev,
				"%s(): register %d update failed with err %d\n",
				__func__, REG_VSET0 + tps->curr_vset_id, ret);
		वापस ret;
	पूर्ण

	/* If gpios are valid then all रेजिस्टर set need to be control */
	क्रम (i = 0; i < 4; ++i) अणु
		ret = regmap_update_bits(tps->regmap,
					REG_VSET0 + i, FORCE_PWM_ENABLE, val);
		अगर (ret < 0) अणु
			dev_err(tps->dev,
				"%s(): register %d update failed with err %d\n",
				__func__, REG_VSET0 + i, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक tps62360_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tps62360_chip *tps = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps->regmap, REG_VSET0 + tps->curr_vset_id, &data);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "%s(): register %d read failed with err %d\n",
			__func__, REG_VSET0 + tps->curr_vset_id, ret);
		वापस ret;
	पूर्ण
	वापस (data & FORCE_PWM_ENABLE) ?
				REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps62360_dcdc_ops = अणु
	.get_voltage_sel	= tps62360_dcdc_get_voltage_sel,
	.set_voltage_sel	= tps62360_dcdc_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_mode		= tps62360_set_mode,
	.get_mode		= tps62360_get_mode,
पूर्ण;

अटल पूर्णांक tps62360_init_dcdc(काष्ठा tps62360_chip *tps,
		काष्ठा tps62360_regulator_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ramp_ctrl;

	/* Initialize पूर्णांकernal pull up/करोwn control */
	अगर (tps->en_पूर्णांकernal_pulldn)
		ret = regmap_ग_लिखो(tps->regmap, REG_CONTROL, 0xE0);
	अन्यथा
		ret = regmap_ग_लिखो(tps->regmap, REG_CONTROL, 0x0);
	अगर (ret < 0) अणु
		dev_err(tps->dev,
			"%s(): register %d write failed with err %d\n",
			__func__, REG_CONTROL, ret);
		वापस ret;
	पूर्ण

	/* Reset output disअक्षरge path to reduce घातer consumption */
	ret = regmap_update_bits(tps->regmap, REG_RAMPCTRL, BIT(2), 0);
	अगर (ret < 0) अणु
		dev_err(tps->dev,
			"%s(): register %d update failed with err %d\n",
			__func__, REG_RAMPCTRL, ret);
		वापस ret;
	पूर्ण

	/* Get ramp value from ramp control रेजिस्टर */
	ret = regmap_पढ़ो(tps->regmap, REG_RAMPCTRL, &ramp_ctrl);
	अगर (ret < 0) अणु
		dev_err(tps->dev,
			"%s(): register %d read failed with err %d\n",
			__func__, REG_RAMPCTRL, ret);
		वापस ret;
	पूर्ण
	ramp_ctrl = (ramp_ctrl >> 5) & 0x7;

	/* ramp mV/us = 32/(2^ramp_ctrl) */
	tps->desc.ramp_delay = DIV_ROUND_UP(32000, BIT(ramp_ctrl));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_config tps62360_regmap_config = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= REG_CHIPID,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा tps62360_regulator_platक्रमm_data *
	of_get_tps62360_platक्रमm_data(काष्ठा device *dev,
				      स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा tps62360_regulator_platक्रमm_data *pdata;
	काष्ठा device_node *np = dev->of_node;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->reg_init_data = of_get_regulator_init_data(dev, dev->of_node,
							  desc);
	अगर (!pdata->reg_init_data) अणु
		dev_err(dev, "Not able to get OF regulator init data\n");
		वापस शून्य;
	पूर्ण

	pdata->vsel0_gpio = of_get_named_gpio(np, "vsel0-gpio", 0);
	pdata->vsel1_gpio = of_get_named_gpio(np, "vsel1-gpio", 0);

	अगर (of_find_property(np, "ti,vsel0-state-high", शून्य))
		pdata->vsel0_def_state = 1;

	अगर (of_find_property(np, "ti,vsel1-state-high", शून्य))
		pdata->vsel1_def_state = 1;

	अगर (of_find_property(np, "ti,enable-pull-down", शून्य))
		pdata->en_पूर्णांकernal_pulldn = true;

	अगर (of_find_property(np, "ti,enable-vout-discharge", शून्य))
		pdata->en_disअक्षरge = true;

	वापस pdata;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tps62360_of_match[] = अणु
	 अणु .compatible = "ti,tps62360", .data = (व्योम *)TPS62360पूर्ण,
	 अणु .compatible = "ti,tps62361", .data = (व्योम *)TPS62361पूर्ण,
	 अणु .compatible = "ti,tps62362", .data = (व्योम *)TPS62362पूर्ण,
	 अणु .compatible = "ti,tps62363", .data = (व्योम *)TPS62363पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps62360_of_match);
#पूर्ण_अगर

अटल पूर्णांक tps62360_probe(काष्ठा i2c_client *client,
				     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा tps62360_regulator_platक्रमm_data *pdata;
	काष्ठा regulator_dev *rdev;
	काष्ठा tps62360_chip *tps;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक chip_id;

	pdata = dev_get_platdata(&client->dev);

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	tps->desc.name = client->name;
	tps->desc.id = 0;
	tps->desc.ops = &tps62360_dcdc_ops;
	tps->desc.type = REGULATOR_VOLTAGE;
	tps->desc.owner = THIS_MODULE;
	tps->desc.uV_step = 10000;

	अगर (client->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_device(of_match_ptr(tps62360_of_match),
				&client->dev);
		अगर (!match) अणु
			dev_err(&client->dev, "Error: No device match found\n");
			वापस -ENODEV;
		पूर्ण
		chip_id = (पूर्णांक)(दीर्घ)match->data;
		अगर (!pdata)
			pdata = of_get_tps62360_platक्रमm_data(&client->dev,
							      &tps->desc);
	पूर्ण अन्यथा अगर (id) अणु
		chip_id = id->driver_data;
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "No device tree match or id table match found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&client->dev, "%s(): Platform data not found\n",
						__func__);
		वापस -EIO;
	पूर्ण

	tps->en_disअक्षरge = pdata->en_disअक्षरge;
	tps->en_पूर्णांकernal_pulldn = pdata->en_पूर्णांकernal_pulldn;
	tps->vsel0_gpio = pdata->vsel0_gpio;
	tps->vsel1_gpio = pdata->vsel1_gpio;
	tps->dev = &client->dev;

	चयन (chip_id) अणु
	हाल TPS62360:
	हाल TPS62362:
		tps->desc.min_uV = TPS62360_BASE_VOLTAGE;
		tps->voltage_reg_mask = 0x3F;
		tps->desc.n_voltages = TPS62360_N_VOLTAGES;
		अवरोध;
	हाल TPS62361:
	हाल TPS62363:
		tps->desc.min_uV = TPS62361_BASE_VOLTAGE;
		tps->voltage_reg_mask = 0x7F;
		tps->desc.n_voltages = TPS62361_N_VOLTAGES;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	tps->regmap = devm_regmap_init_i2c(client, &tps62360_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		ret = PTR_ERR(tps->regmap);
		dev_err(&client->dev,
			"%s(): regmap allocation failed with err %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण
	i2c_set_clientdata(client, tps);

	tps->curr_vset_id = (pdata->vsel1_def_state & 1) * 2 +
				(pdata->vsel0_def_state & 1);
	tps->lru_index[0] = tps->curr_vset_id;
	tps->valid_gpios = false;

	अगर (gpio_is_valid(tps->vsel0_gpio) && gpio_is_valid(tps->vsel1_gpio)) अणु
		पूर्णांक gpio_flags;
		gpio_flags = (pdata->vsel0_def_state) ?
				GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
		ret = devm_gpio_request_one(&client->dev, tps->vsel0_gpio,
				gpio_flags, "tps62360-vsel0");
		अगर (ret) अणु
			dev_err(&client->dev,
				"%s(): Could not obtain vsel0 GPIO %d: %d\n",
				__func__, tps->vsel0_gpio, ret);
			वापस ret;
		पूर्ण

		gpio_flags = (pdata->vsel1_def_state) ?
				GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
		ret = devm_gpio_request_one(&client->dev, tps->vsel1_gpio,
				gpio_flags, "tps62360-vsel1");
		अगर (ret) अणु
			dev_err(&client->dev,
				"%s(): Could not obtain vsel1 GPIO %d: %d\n",
				__func__, tps->vsel1_gpio, ret);
			वापस ret;
		पूर्ण
		tps->valid_gpios = true;

		/*
		 * Initialize the lru index with vset_reg id
		 * The index 0 will be most recently used and
		 * set with the tps->curr_vset_id */
		क्रम (i = 0; i < 4; ++i)
			tps->lru_index[i] = i;
		tps->lru_index[0] = tps->curr_vset_id;
		tps->lru_index[tps->curr_vset_id] = 0;
	पूर्ण

	ret = tps62360_init_dcdc(tps, pdata);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "%s(): Init failed with err = %d\n",
				__func__, ret);
		वापस ret;
	पूर्ण

	config.dev = &client->dev;
	config.init_data = pdata->reg_init_data;
	config.driver_data = tps;
	config.of_node = client->dev.of_node;

	/* Register the regulators */
	rdev = devm_regulator_रेजिस्टर(&client->dev, &tps->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(tps->dev,
			"%s(): regulator register failed with err %s\n",
			__func__, id->name);
		वापस PTR_ERR(rdev);
	पूर्ण

	tps->rdev = rdev;
	वापस 0;
पूर्ण

अटल व्योम tps62360_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा tps62360_chip *tps = i2c_get_clientdata(client);
	पूर्णांक st;

	अगर (!tps->en_disअक्षरge)
		वापस;

	/* Configure the output disअक्षरge path */
	st = regmap_update_bits(tps->regmap, REG_RAMPCTRL, BIT(2), BIT(2));
	अगर (st < 0)
		dev_err(tps->dev,
			"%s(): register %d update failed with err %d\n",
			__func__, REG_RAMPCTRL, st);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps62360_id[] = अणु
	अणु.name = "tps62360", .driver_data = TPS62360पूर्ण,
	अणु.name = "tps62361", .driver_data = TPS62361पूर्ण,
	अणु.name = "tps62362", .driver_data = TPS62362पूर्ण,
	अणु.name = "tps62363", .driver_data = TPS62363पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tps62360_id);

अटल काष्ठा i2c_driver tps62360_i2c_driver = अणु
	.driver = अणु
		.name = "tps62360",
		.of_match_table = of_match_ptr(tps62360_of_match),
	पूर्ण,
	.probe = tps62360_probe,
	.shutकरोwn = tps62360_shutकरोwn,
	.id_table = tps62360_id,
पूर्ण;

अटल पूर्णांक __init tps62360_init(व्योम)
अणु
	वापस i2c_add_driver(&tps62360_i2c_driver);
पूर्ण
subsys_initcall(tps62360_init);

अटल व्योम __निकास tps62360_cleanup(व्योम)
अणु
	i2c_del_driver(&tps62360_i2c_driver);
पूर्ण
module_निकास(tps62360_cleanup);

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_DESCRIPTION("TPS6236x voltage regulator driver");
MODULE_LICENSE("GPL v2");
