<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max8660.c  --  Voltage regulation क्रम the Maxim 8660/8661
 *
 * based on max1586.c and wm8400-regulator.c
 *
 * Copyright (C) 2009 Wolfram Sang, Pengutronix e.K.
 *
 * Some info:
 *
 * Datasheet: http://datasheets.maxim-ic.com/en/ds/MAX8660-MAX8661.pdf
 *
 * This chip is a bit nasty because it is a ग_लिखो-only device. Thus, the driver
 * uses shaकरोw रेजिस्टरs to keep track of its values. The मुख्य problem appears
 * to be the initialization: When Linux boots up, we cannot know अगर the chip is
 * in the शेष state or not, so we would have to pass such inक्रमmation in
 * platक्रमm_data. As this adds a bit of complनिकासy to the driver, this is left
 * out क्रम now until it is really needed.
 *
 * [A|S|M]DTV1 रेजिस्टरs are currently not used, but [A|S|M]DTV2.
 *
 * If the driver is feature complete, it might be worth to check अगर one set of
 * functions क्रम V3-V7 is sufficient. For maximum flexibility during
 * development, they are separated क्रम now.
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/max8660.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा MAX8660_DCDC_MIN_UV	 725000
#घोषणा MAX8660_DCDC_MAX_UV	1800000
#घोषणा MAX8660_DCDC_STEP	  25000
#घोषणा MAX8660_DCDC_MAX_SEL	0x2b

#घोषणा MAX8660_LDO5_MIN_UV	1700000
#घोषणा MAX8660_LDO5_MAX_UV	2000000
#घोषणा MAX8660_LDO5_STEP	  25000
#घोषणा MAX8660_LDO5_MAX_SEL	0x0c

#घोषणा MAX8660_LDO67_MIN_UV	1800000
#घोषणा MAX8660_LDO67_MAX_UV	3300000
#घोषणा MAX8660_LDO67_STEP	 100000
#घोषणा MAX8660_LDO67_MAX_SEL	0x0f

क्रमागत अणु
	MAX8660_OVER1,
	MAX8660_OVER2,
	MAX8660_VCC1,
	MAX8660_ADTV1,
	MAX8660_ADTV2,
	MAX8660_SDTV1,
	MAX8660_SDTV2,
	MAX8660_MDTV1,
	MAX8660_MDTV2,
	MAX8660_L12VCR,
	MAX8660_FPWM,
	MAX8660_N_REGS,	/* not a real रेजिस्टर */
पूर्ण;

काष्ठा max8660 अणु
	काष्ठा i2c_client *client;
	u8 shaकरोw_regs[MAX8660_N_REGS];		/* as chip is ग_लिखो only */
पूर्ण;

अटल पूर्णांक max8660_ग_लिखो(काष्ठा max8660 *max8660, u8 reg, u8 mask, u8 val)
अणु
	अटल स्थिर u8 max8660_addresses[MAX8660_N_REGS] = अणु
	 0x10, 0x12, 0x20, 0x23, 0x24, 0x29, 0x2a, 0x32, 0x33, 0x39, 0x80
	पूर्ण;

	पूर्णांक ret;
	u8 reg_val = (max8660->shaकरोw_regs[reg] & mask) | val;

	dev_vdbg(&max8660->client->dev, "Writing reg %02x with %02x\n",
			max8660_addresses[reg], reg_val);

	ret = i2c_smbus_ग_लिखो_byte_data(max8660->client,
			max8660_addresses[reg], reg_val);
	अगर (ret == 0)
		max8660->shaकरोw_regs[reg] = reg_val;

	वापस ret;
पूर्ण


/*
 * DCDC functions
 */

अटल पूर्णांक max8660_dcdc_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 val = max8660->shaकरोw_regs[MAX8660_OVER1];
	u8 mask = (rdev_get_id(rdev) == MAX8660_V3) ? 1 : 4;

	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक max8660_dcdc_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 bit = (rdev_get_id(rdev) == MAX8660_V3) ? 1 : 4;

	वापस max8660_ग_लिखो(max8660, MAX8660_OVER1, 0xff, bit);
पूर्ण

अटल पूर्णांक max8660_dcdc_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 mask = (rdev_get_id(rdev) == MAX8660_V3) ? ~1 : ~4;

	वापस max8660_ग_लिखो(max8660, MAX8660_OVER1, mask, 0);
पूर्ण

अटल पूर्णांक max8660_dcdc_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 reg = (rdev_get_id(rdev) == MAX8660_V3) ? MAX8660_ADTV2 : MAX8660_SDTV2;
	u8 selector = max8660->shaकरोw_regs[reg];

	वापस selector;
पूर्ण

अटल पूर्णांक max8660_dcdc_set_voltage_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 reg, bits;
	पूर्णांक ret;

	reg = (rdev_get_id(rdev) == MAX8660_V3) ? MAX8660_ADTV2 : MAX8660_SDTV2;
	ret = max8660_ग_लिखो(max8660, reg, 0, selector);
	अगर (ret)
		वापस ret;

	/* Select target voltage रेजिस्टर and activate regulation */
	bits = (rdev_get_id(rdev) == MAX8660_V3) ? 0x03 : 0x30;
	वापस max8660_ग_लिखो(max8660, MAX8660_VCC1, 0xff, bits);
पूर्ण

अटल काष्ठा regulator_ops max8660_dcdc_ops = अणु
	.is_enabled = max8660_dcdc_is_enabled,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.set_voltage_sel = max8660_dcdc_set_voltage_sel,
	.get_voltage_sel = max8660_dcdc_get_voltage_sel,
पूर्ण;


/*
 * LDO5 functions
 */

अटल पूर्णांक max8660_lकरो5_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);

	u8 selector = max8660->shaकरोw_regs[MAX8660_MDTV2];
	वापस selector;
पूर्ण

अटल पूर्णांक max8660_lकरो5_set_voltage_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = max8660_ग_लिखो(max8660, MAX8660_MDTV2, 0, selector);
	अगर (ret)
		वापस ret;

	/* Select target voltage रेजिस्टर and activate regulation */
	वापस max8660_ग_लिखो(max8660, MAX8660_VCC1, 0xff, 0xc0);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8660_lकरो5_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.set_voltage_sel = max8660_lकरो5_set_voltage_sel,
	.get_voltage_sel = max8660_lकरो5_get_voltage_sel,
पूर्ण;


/*
 * LDO67 functions
 */

अटल पूर्णांक max8660_lकरो67_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 val = max8660->shaकरोw_regs[MAX8660_OVER2];
	u8 mask = (rdev_get_id(rdev) == MAX8660_V6) ? 2 : 4;

	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक max8660_lकरो67_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 bit = (rdev_get_id(rdev) == MAX8660_V6) ? 2 : 4;

	वापस max8660_ग_लिखो(max8660, MAX8660_OVER2, 0xff, bit);
पूर्ण

अटल पूर्णांक max8660_lकरो67_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 mask = (rdev_get_id(rdev) == MAX8660_V6) ? ~2 : ~4;

	वापस max8660_ग_लिखो(max8660, MAX8660_OVER2, mask, 0);
पूर्ण

अटल पूर्णांक max8660_lकरो67_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 shअगरt = (rdev_get_id(rdev) == MAX8660_V6) ? 0 : 4;
	u8 selector = (max8660->shaकरोw_regs[MAX8660_L12VCR] >> shअगरt) & 0xf;

	वापस selector;
पूर्ण

अटल पूर्णांक max8660_lकरो67_set_voltage_sel(काष्ठा regulator_dev *rdev,
					 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा max8660 *max8660 = rdev_get_drvdata(rdev);

	अगर (rdev_get_id(rdev) == MAX8660_V6)
		वापस max8660_ग_लिखो(max8660, MAX8660_L12VCR, 0xf0, selector);
	अन्यथा
		वापस max8660_ग_लिखो(max8660, MAX8660_L12VCR, 0x0f,
				     selector << 4);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8660_lकरो67_ops = अणु
	.is_enabled = max8660_lकरो67_is_enabled,
	.enable = max8660_lकरो67_enable,
	.disable = max8660_lकरो67_disable,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = max8660_lकरो67_get_voltage_sel,
	.set_voltage_sel = max8660_lकरो67_set_voltage_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc max8660_reg[] = अणु
	अणु
		.name = "V3(DCDC)",
		.id = MAX8660_V3,
		.ops = &max8660_dcdc_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX8660_DCDC_MAX_SEL + 1,
		.owner = THIS_MODULE,
		.min_uV = MAX8660_DCDC_MIN_UV,
		.uV_step = MAX8660_DCDC_STEP,
	पूर्ण,
	अणु
		.name = "V4(DCDC)",
		.id = MAX8660_V4,
		.ops = &max8660_dcdc_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX8660_DCDC_MAX_SEL + 1,
		.owner = THIS_MODULE,
		.min_uV = MAX8660_DCDC_MIN_UV,
		.uV_step = MAX8660_DCDC_STEP,
	पूर्ण,
	अणु
		.name = "V5(LDO)",
		.id = MAX8660_V5,
		.ops = &max8660_lकरो5_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX8660_LDO5_MAX_SEL + 1,
		.owner = THIS_MODULE,
		.min_uV = MAX8660_LDO5_MIN_UV,
		.uV_step = MAX8660_LDO5_STEP,
	पूर्ण,
	अणु
		.name = "V6(LDO)",
		.id = MAX8660_V6,
		.ops = &max8660_lकरो67_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX8660_LDO67_MAX_SEL + 1,
		.owner = THIS_MODULE,
		.min_uV = MAX8660_LDO67_MIN_UV,
		.uV_step = MAX8660_LDO67_STEP,
	पूर्ण,
	अणु
		.name = "V7(LDO)",
		.id = MAX8660_V7,
		.ops = &max8660_lकरो67_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = MAX8660_LDO67_MAX_SEL + 1,
		.owner = THIS_MODULE,
		.min_uV = MAX8660_LDO67_MIN_UV,
		.uV_step = MAX8660_LDO67_STEP,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	MAX8660 = 0,
	MAX8661 = 1,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max8660_dt_ids[] = अणु
	अणु .compatible = "maxim,max8660", .data = (व्योम *) MAX8660 पूर्ण,
	अणु .compatible = "maxim,max8661", .data = (व्योम *) MAX8661 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max8660_dt_ids);

अटल पूर्णांक max8660_pdata_from_dt(काष्ठा device *dev,
				 काष्ठा device_node **of_node,
				 काष्ठा max8660_platक्रमm_data *pdata)
अणु
	पूर्णांक matched, i;
	काष्ठा device_node *np;
	काष्ठा max8660_subdev_data *sub;
	काष्ठा of_regulator_match rmatch[ARRAY_SIZE(max8660_reg)] = अणु पूर्ण;

	np = of_get_child_by_name(dev->of_node, "regulators");
	अगर (!np) अणु
		dev_err(dev, "missing 'regulators' subnode in DT\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rmatch); i++)
		rmatch[i].name = max8660_reg[i].name;

	matched = of_regulator_match(dev, np, rmatch, ARRAY_SIZE(rmatch));
	of_node_put(np);
	अगर (matched <= 0)
		वापस matched;

	pdata->subdevs = devm_kसुस्मृति(dev,
				      matched,
				      माप(काष्ठा max8660_subdev_data),
				      GFP_KERNEL);
	अगर (!pdata->subdevs)
		वापस -ENOMEM;

	pdata->num_subdevs = matched;
	sub = pdata->subdevs;

	क्रम (i = 0; i < matched; i++) अणु
		sub->id = i;
		sub->name = rmatch[i].name;
		sub->platक्रमm_data = rmatch[i].init_data;
		of_node[i] = rmatch[i].of_node;
		sub++;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक max8660_pdata_from_dt(काष्ठा device *dev,
					काष्ठा device_node **of_node,
					काष्ठा max8660_platक्रमm_data *pdata)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक max8660_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा max8660_platक्रमm_data pdata_of, *pdata = dev_get_platdata(dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा max8660 *max8660;
	पूर्णांक boot_on, i, id, ret = -EINVAL;
	काष्ठा device_node *of_node[MAX8660_V_END];
	अचिन्हित दीर्घ type;

	अगर (dev->of_node && !pdata) अणु
		स्थिर काष्ठा of_device_id *id;

		id = of_match_device(of_match_ptr(max8660_dt_ids), dev);
		अगर (!id)
			वापस -ENODEV;

		ret = max8660_pdata_from_dt(dev, of_node, &pdata_of);
		अगर (ret < 0)
			वापस ret;

		pdata = &pdata_of;
		type = (अचिन्हित दीर्घ) id->data;
	पूर्ण अन्यथा अणु
		type = i2c_id->driver_data;
		स_रखो(of_node, 0, माप(of_node));
	पूर्ण

	अगर (pdata->num_subdevs > MAX8660_V_END) अणु
		dev_err(dev, "Too many regulators found!\n");
		वापस -EINVAL;
	पूर्ण

	max8660 = devm_kzalloc(dev, माप(काष्ठा max8660), GFP_KERNEL);
	अगर (!max8660)
		वापस -ENOMEM;

	max8660->client = client;

	अगर (pdata->en34_is_high) अणु
		/* Simulate always on */
		max8660->shaकरोw_regs[MAX8660_OVER1] = 5;
	पूर्ण अन्यथा अणु
		/* Otherwise devices can be toggled via software */
		max8660_dcdc_ops.enable = max8660_dcdc_enable;
		max8660_dcdc_ops.disable = max8660_dcdc_disable;
	पूर्ण

	/*
	 * First, set up shaकरोw रेजिस्टरs to prevent glitches. As some
	 * रेजिस्टरs are shared between regulators, everything must be properly
	 * set up क्रम all regulators in advance.
	 */
	max8660->shaकरोw_regs[MAX8660_ADTV1] =
		max8660->shaकरोw_regs[MAX8660_ADTV2] =
		max8660->shaकरोw_regs[MAX8660_SDTV1] =
		max8660->shaकरोw_regs[MAX8660_SDTV2] = 0x1b;
	max8660->shaकरोw_regs[MAX8660_MDTV1] =
		max8660->shaकरोw_regs[MAX8660_MDTV2] = 0x04;

	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु

		अगर (!pdata->subdevs[i].platक्रमm_data)
			boot_on = false;
		अन्यथा
			boot_on = pdata->subdevs[i].platक्रमm_data->स्थिरraपूर्णांकs.boot_on;

		चयन (pdata->subdevs[i].id) अणु
		हाल MAX8660_V3:
			अगर (boot_on)
				max8660->shaकरोw_regs[MAX8660_OVER1] |= 1;
			अवरोध;

		हाल MAX8660_V4:
			अगर (boot_on)
				max8660->shaकरोw_regs[MAX8660_OVER1] |= 4;
			अवरोध;

		हाल MAX8660_V5:
			अवरोध;

		हाल MAX8660_V6:
			अगर (boot_on)
				max8660->shaकरोw_regs[MAX8660_OVER2] |= 2;
			अवरोध;

		हाल MAX8660_V7:
			अगर (type == MAX8661) अणु
				dev_err(dev, "Regulator not on this chip!\n");
				वापस -EINVAL;
			पूर्ण

			अगर (boot_on)
				max8660->shaकरोw_regs[MAX8660_OVER2] |= 4;
			अवरोध;

		शेष:
			dev_err(dev, "invalid regulator %s\n",
				 pdata->subdevs[i].name);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Finally रेजिस्टर devices */
	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु
		काष्ठा regulator_dev *rdev;

		id = pdata->subdevs[i].id;

		config.dev = dev;
		config.init_data = pdata->subdevs[i].platक्रमm_data;
		config.of_node = of_node[i];
		config.driver_data = max8660;

		rdev = devm_regulator_रेजिस्टर(&client->dev,
						  &max8660_reg[id], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&client->dev, "failed to register %s\n",
				max8660_reg[id].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, max8660);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8660_id[] = अणु
	अणु .name = "max8660", .driver_data = MAX8660 पूर्ण,
	अणु .name = "max8661", .driver_data = MAX8661 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max8660_id);

अटल काष्ठा i2c_driver max8660_driver = अणु
	.probe = max8660_probe,
	.driver		= अणु
		.name	= "max8660",
	पूर्ण,
	.id_table	= max8660_id,
पूर्ण;

अटल पूर्णांक __init max8660_init(व्योम)
अणु
	वापस i2c_add_driver(&max8660_driver);
पूर्ण
subsys_initcall(max8660_init);

अटल व्योम __निकास max8660_निकास(व्योम)
अणु
	i2c_del_driver(&max8660_driver);
पूर्ण
module_निकास(max8660_निकास);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MAXIM 8660/8661 voltage regulator driver");
MODULE_AUTHOR("Wolfram Sang");
MODULE_LICENSE("GPL v2");
