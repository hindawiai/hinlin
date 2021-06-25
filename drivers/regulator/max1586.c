<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max1586.c  --  Voltage and current regulation क्रम the Maxim 1586
 *
 * Copyright (C) 2008 Robert Jarzmik
 */
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/max1586.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा MAX1586_V3_MAX_VSEL 31
#घोषणा MAX1586_V6_MAX_VSEL 3

#घोषणा MAX1586_V3_MIN_UV   700000
#घोषणा MAX1586_V3_MAX_UV  1475000

#घोषणा MAX1586_V6_MIN_UV        0
#घोषणा MAX1586_V6_MAX_UV  3000000

#घोषणा I2C_V3_SELECT (0 << 5)
#घोषणा I2C_V6_SELECT (1 << 5)

काष्ठा max1586_data अणु
	काष्ठा i2c_client *client;

	/* min/max V3 voltage */
	अचिन्हित पूर्णांक min_uV;
	अचिन्हित पूर्णांक max_uV;

	अचिन्हित पूर्णांक v3_curr_sel;
	अचिन्हित पूर्णांक v6_curr_sel;
पूर्ण;

/*
 * V6 voltage
 * On I2C bus, sending a "x" byte to the max1586 means :
 *   set V6 to either 0V, 1.8V, 2.5V, 3V depending on (x & 0x3)
 * As regulator framework करोesn't accept voltages to be 0V, we use 1uV.
 */
अटल स्थिर अचिन्हित पूर्णांक v6_voltages_uv[] = अणु 1, 1800000, 2500000, 3000000 पूर्ण;

/*
 * V3 voltage
 * On I2C bus, sending a "x" byte to the max1586 means :
 *   set V3 to 0.700V + (x & 0x1f) * 0.025V
 * This voltage can be increased by बाह्यal resistors
 * R24 and R25=100kOhm as described in the data sheet.
 * The gain is approximately: 1 + R24/R25 + R24/185.5kOhm
 */
अटल पूर्णांक max1586_v3_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max1586_data *max1586 = rdev_get_drvdata(rdev);

	वापस max1586->v3_curr_sel;
पूर्ण

अटल पूर्णांक max1586_v3_set_voltage_sel(काष्ठा regulator_dev *rdev,
				      अचिन्हित selector)
अणु
	काष्ठा max1586_data *max1586 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = max1586->client;
	पूर्णांक ret;
	u8 v3_prog;

	dev_dbg(&client->dev, "changing voltage v3 to %dmv\n",
		regulator_list_voltage_linear(rdev, selector) / 1000);

	v3_prog = I2C_V3_SELECT | (u8) selector;
	ret = i2c_smbus_ग_लिखो_byte(client, v3_prog);
	अगर (ret)
		वापस ret;

	max1586->v3_curr_sel = selector;

	वापस 0;
पूर्ण

अटल पूर्णांक max1586_v6_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max1586_data *max1586 = rdev_get_drvdata(rdev);

	वापस max1586->v6_curr_sel;
पूर्ण

अटल पूर्णांक max1586_v6_set_voltage_sel(काष्ठा regulator_dev *rdev,
				      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा max1586_data *max1586 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *client = max1586->client;
	u8 v6_prog;
	पूर्णांक ret;

	dev_dbg(&client->dev, "changing voltage v6 to %dmv\n",
		rdev->desc->volt_table[selector] / 1000);

	v6_prog = I2C_V6_SELECT | (u8) selector;
	ret = i2c_smbus_ग_लिखो_byte(client, v6_prog);
	अगर (ret)
		वापस ret;

	max1586->v6_curr_sel = selector;

	वापस 0;
पूर्ण

/*
 * The Maxim 1586 controls V3 and V6 voltages, but offers no way of पढ़ोing back
 * the set up value.
 */
अटल स्थिर काष्ठा regulator_ops max1586_v3_ops = अणु
	.get_voltage_sel = max1586_v3_get_voltage_sel,
	.set_voltage_sel = max1586_v3_set_voltage_sel,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max1586_v6_ops = अणु
	.get_voltage_sel = max1586_v6_get_voltage_sel,
	.set_voltage_sel = max1586_v6_set_voltage_sel,
	.list_voltage = regulator_list_voltage_table,
पूर्ण;

अटल काष्ठा regulator_desc max1586_reg[] = अणु
	अणु
		.name = "Output_V3",
		.id = MAX1586_V3,
		.ops = &max1586_v3_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX1586_V3_MAX_VSEL + 1,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "Output_V6",
		.id = MAX1586_V6,
		.ops = &max1586_v6_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX1586_V6_MAX_VSEL + 1,
		.volt_table = v6_voltages_uv,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक of_get_max1586_platक्रमm_data(काष्ठा device *dev,
				 काष्ठा max1586_platक्रमm_data *pdata)
अणु
	काष्ठा max1586_subdev_data *sub;
	काष्ठा of_regulator_match rmatch[ARRAY_SIZE(max1586_reg)] = अणु पूर्ण;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक i, matched;

	अगर (of_property_पढ़ो_u32(np, "v3-gain",
				 &pdata->v3_gain) < 0) अणु
		dev_err(dev, "%pOF has no 'v3-gain' property\n", np);
		वापस -EINVAL;
	पूर्ण

	np = of_get_child_by_name(np, "regulators");
	अगर (!np) अणु
		dev_err(dev, "missing 'regulators' subnode in DT\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rmatch); i++)
		rmatch[i].name = max1586_reg[i].name;

	matched = of_regulator_match(dev, np, rmatch, ARRAY_SIZE(rmatch));
	of_node_put(np);
	/*
	 * If matched is 0, ie. neither Output_V3 nor Output_V6 have been found,
	 * वापस 0, which संकेतs the normal situation where no subregulator is
	 * available. This is normal because the max1586 करोesn't provide any
	 * पढ़ोback support, so the subregulators can't report any status
	 * anyway.  If matched < 0, वापस the error.
	 */
	अगर (matched <= 0)
		वापस matched;

	pdata->subdevs = devm_kसुस्मृति(dev,
				      matched,
				      माप(काष्ठा max1586_subdev_data),
				      GFP_KERNEL);
	अगर (!pdata->subdevs)
		वापस -ENOMEM;

	pdata->num_subdevs = matched;
	sub = pdata->subdevs;

	क्रम (i = 0; i < matched; i++) अणु
		sub->id = i;
		sub->name = rmatch[i].of_node->name;
		sub->platक्रमm_data = rmatch[i].init_data;
		sub++;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused max1586_of_match[] = अणु
	अणु .compatible = "maxim,max1586", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max1586_of_match);

अटल पूर्णांक max1586_pmic_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा max1586_platक्रमm_data *pdata, pdata_of;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा max1586_data *max1586;
	पूर्णांक i, id, ret;
	स्थिर काष्ठा of_device_id *match;

	pdata = dev_get_platdata(&client->dev);
	अगर (client->dev.of_node && !pdata) अणु
		match = of_match_device(of_match_ptr(max1586_of_match),
					&client->dev);
		अगर (!match) अणु
			dev_err(&client->dev, "Error: No device match found\n");
			वापस -ENODEV;
		पूर्ण
		ret = of_get_max1586_platक्रमm_data(&client->dev, &pdata_of);
		अगर (ret < 0)
			वापस ret;
		pdata = &pdata_of;
	पूर्ण

	max1586 = devm_kzalloc(&client->dev, माप(काष्ठा max1586_data),
			GFP_KERNEL);
	अगर (!max1586)
		वापस -ENOMEM;

	max1586->client = client;

	अगर (!pdata->v3_gain)
		वापस -EINVAL;

	max1586->min_uV = MAX1586_V3_MIN_UV / 1000 * pdata->v3_gain / 1000;
	max1586->max_uV = MAX1586_V3_MAX_UV / 1000 * pdata->v3_gain / 1000;

	/* Set curr_sel to शेष voltage on घातer-up */
	max1586->v3_curr_sel = 24; /* 1.3V */
	max1586->v6_curr_sel = 0;

	क्रम (i = 0; i < pdata->num_subdevs && i <= MAX1586_V6; i++) अणु
		काष्ठा regulator_dev *rdev;

		id = pdata->subdevs[i].id;
		अगर (!pdata->subdevs[i].platक्रमm_data)
			जारी;
		अगर (id < MAX1586_V3 || id > MAX1586_V6) अणु
			dev_err(&client->dev, "invalid regulator id %d\n", id);
			वापस -EINVAL;
		पूर्ण

		अगर (id == MAX1586_V3) अणु
			max1586_reg[id].min_uV = max1586->min_uV;
			max1586_reg[id].uV_step =
					(max1586->max_uV - max1586->min_uV) /
					MAX1586_V3_MAX_VSEL;
		पूर्ण

		config.dev = &client->dev;
		config.init_data = pdata->subdevs[i].platक्रमm_data;
		config.driver_data = max1586;

		rdev = devm_regulator_रेजिस्टर(&client->dev,
						  &max1586_reg[id], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&client->dev, "failed to register %s\n",
				max1586_reg[id].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, max1586);
	dev_info(&client->dev, "Maxim 1586 regulator driver loaded\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max1586_id[] = अणु
	अणु "max1586", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max1586_id);

अटल काष्ठा i2c_driver max1586_pmic_driver = अणु
	.probe = max1586_pmic_probe,
	.driver		= अणु
		.name	= "max1586",
		.of_match_table = of_match_ptr(max1586_of_match),
	पूर्ण,
	.id_table	= max1586_id,
पूर्ण;

अटल पूर्णांक __init max1586_pmic_init(व्योम)
अणु
	वापस i2c_add_driver(&max1586_pmic_driver);
पूर्ण
subsys_initcall(max1586_pmic_init);

अटल व्योम __निकास max1586_pmic_निकास(व्योम)
अणु
	i2c_del_driver(&max1586_pmic_driver);
पूर्ण
module_निकास(max1586_pmic_निकास);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MAXIM 1586 voltage regulator driver");
MODULE_AUTHOR("Robert Jarzmik");
MODULE_LICENSE("GPL");
