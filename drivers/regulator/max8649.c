<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulators driver क्रम Maxim max8649
 *
 * Copyright (C) 2009-2010 Marvell International Ltd.
 *      Haojian Zhuang <haojian.zhuang@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/max8649.h>
#समावेश <linux/regmap.h>

#घोषणा MAX8649_DCDC_VMIN	750000		/* uV */
#घोषणा MAX8649_DCDC_VMAX	1380000		/* uV */
#घोषणा MAX8649_DCDC_STEP	10000		/* uV */
#घोषणा MAX8649_VOL_MASK	0x3f

/* Registers */
#घोषणा MAX8649_MODE0		0x00
#घोषणा MAX8649_MODE1		0x01
#घोषणा MAX8649_MODE2		0x02
#घोषणा MAX8649_MODE3		0x03
#घोषणा MAX8649_CONTROL		0x04
#घोषणा MAX8649_SYNC		0x05
#घोषणा MAX8649_RAMP		0x06
#घोषणा MAX8649_CHIP_ID1	0x08
#घोषणा MAX8649_CHIP_ID2	0x09

/* Bits */
#घोषणा MAX8649_EN_PD		(1 << 7)
#घोषणा MAX8649_VID0_PD		(1 << 6)
#घोषणा MAX8649_VID1_PD		(1 << 5)
#घोषणा MAX8649_VID_MASK	(3 << 5)

#घोषणा MAX8649_FORCE_PWM	(1 << 7)
#घोषणा MAX8649_SYNC_EXTCLK	(1 << 6)

#घोषणा MAX8649_EXT_MASK	(3 << 6)

#घोषणा MAX8649_RAMP_MASK	(7 << 5)
#घोषणा MAX8649_RAMP_DOWN	(1 << 1)

काष्ठा max8649_regulator_info अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;

	अचिन्हित	mode:2;	/* bit[1:0] = VID1, VID0 */
	अचिन्हित	extclk_freq:2;
	अचिन्हित	extclk:1;
	अचिन्हित	ramp_timing:3;
	अचिन्हित	ramp_करोwn:1;
पूर्ण;

अटल पूर्णांक max8649_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8649_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक voltage, rate, ret;
	अचिन्हित पूर्णांक val;

	/* get voltage */
	ret = regmap_पढ़ो(info->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret != 0)
		वापस ret;
	val &= MAX8649_VOL_MASK;
	voltage = regulator_list_voltage_linear(rdev, (अचिन्हित अक्षर)val);

	/* get rate */
	ret = regmap_पढ़ो(info->regmap, MAX8649_RAMP, &val);
	अगर (ret != 0)
		वापस ret;
	ret = (val & MAX8649_RAMP_MASK) >> 5;
	rate = (32 * 1000) >> ret;	/* uV/uS */

	वापस DIV_ROUND_UP(voltage, rate);
पूर्ण

अटल पूर्णांक max8649_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max8649_regulator_info *info = rdev_get_drvdata(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		regmap_update_bits(info->regmap, rdev->desc->vsel_reg,
				   MAX8649_FORCE_PWM, MAX8649_FORCE_PWM);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		regmap_update_bits(info->regmap, rdev->desc->vsel_reg,
				   MAX8649_FORCE_PWM, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक max8649_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8649_regulator_info *info = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret != 0)
		वापस ret;
	अगर (val & MAX8649_FORCE_PWM)
		वापस REGULATOR_MODE_FAST;
	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8649_dcdc_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage	= regulator_list_voltage_linear,
	.map_voltage	= regulator_map_voltage_linear,
	.enable		= regulator_enable_regmap,
	.disable	= regulator_disable_regmap,
	.is_enabled	= regulator_is_enabled_regmap,
	.enable_समय	= max8649_enable_समय,
	.set_mode	= max8649_set_mode,
	.get_mode	= max8649_get_mode,

पूर्ण;

अटल काष्ठा regulator_desc dcdc_desc = अणु
	.name		= "max8649",
	.ops		= &max8649_dcdc_ops,
	.type		= REGULATOR_VOLTAGE,
	.n_voltages	= 1 << 6,
	.owner		= THIS_MODULE,
	.vsel_mask	= MAX8649_VOL_MASK,
	.min_uV		= MAX8649_DCDC_VMIN,
	.uV_step	= MAX8649_DCDC_STEP,
	.enable_reg	= MAX8649_CONTROL,
	.enable_mask	= MAX8649_EN_PD,
	.enable_is_inverted = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max8649_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक max8649_regulator_probe(काष्ठा i2c_client *client,
					     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max8649_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा max8649_regulator_info *info = शून्य;
	काष्ठा regulator_dev *regulator;
	काष्ठा regulator_config config = अणु पूर्ण;
	अचिन्हित पूर्णांक val;
	अचिन्हित अक्षर data;
	पूर्णांक ret;

	info = devm_kzalloc(&client->dev, माप(काष्ठा max8649_regulator_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->regmap = devm_regmap_init_i2c(client, &max8649_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		ret = PTR_ERR(info->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	info->dev = &client->dev;
	i2c_set_clientdata(client, info);

	info->mode = pdata->mode;
	चयन (info->mode) अणु
	हाल 0:
		dcdc_desc.vsel_reg = MAX8649_MODE0;
		अवरोध;
	हाल 1:
		dcdc_desc.vsel_reg = MAX8649_MODE1;
		अवरोध;
	हाल 2:
		dcdc_desc.vsel_reg = MAX8649_MODE2;
		अवरोध;
	हाल 3:
		dcdc_desc.vsel_reg = MAX8649_MODE3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, MAX8649_CHIP_ID1, &val);
	अगर (ret != 0) अणु
		dev_err(info->dev, "Failed to detect ID of MAX8649:%d\n",
			ret);
		वापस ret;
	पूर्ण
	dev_info(info->dev, "Detected MAX8649 (ID:%x)\n", val);

	/* enable VID0 & VID1 */
	regmap_update_bits(info->regmap, MAX8649_CONTROL, MAX8649_VID_MASK, 0);

	/* enable/disable बाह्यal घड़ी synchronization */
	info->extclk = pdata->extclk;
	data = (info->extclk) ? MAX8649_SYNC_EXTCLK : 0;
	regmap_update_bits(info->regmap, dcdc_desc.vsel_reg,
			   MAX8649_SYNC_EXTCLK, data);
	अगर (info->extclk) अणु
		/* set बाह्यal घड़ी frequency */
		info->extclk_freq = pdata->extclk_freq;
		regmap_update_bits(info->regmap, MAX8649_SYNC, MAX8649_EXT_MASK,
				   info->extclk_freq << 6);
	पूर्ण

	अगर (pdata->ramp_timing) अणु
		info->ramp_timing = pdata->ramp_timing;
		regmap_update_bits(info->regmap, MAX8649_RAMP, MAX8649_RAMP_MASK,
				   info->ramp_timing << 5);
	पूर्ण

	info->ramp_करोwn = pdata->ramp_करोwn;
	अगर (info->ramp_करोwn) अणु
		regmap_update_bits(info->regmap, MAX8649_RAMP, MAX8649_RAMP_DOWN,
				   MAX8649_RAMP_DOWN);
	पूर्ण

	config.dev = &client->dev;
	config.init_data = pdata->regulator;
	config.driver_data = info;
	config.regmap = info->regmap;

	regulator = devm_regulator_रेजिस्टर(&client->dev, &dcdc_desc,
						  &config);
	अगर (IS_ERR(regulator)) अणु
		dev_err(info->dev, "failed to register regulator %s\n",
			dcdc_desc.name);
		वापस PTR_ERR(regulator);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8649_id[] = अणु
	अणु "max8649", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max8649_id);

अटल काष्ठा i2c_driver max8649_driver = अणु
	.probe		= max8649_regulator_probe,
	.driver		= अणु
		.name	= "max8649",
	पूर्ण,
	.id_table	= max8649_id,
पूर्ण;

अटल पूर्णांक __init max8649_init(व्योम)
अणु
	वापस i2c_add_driver(&max8649_driver);
पूर्ण
subsys_initcall(max8649_init);

अटल व्योम __निकास max8649_निकास(व्योम)
अणु
	i2c_del_driver(&max8649_driver);
पूर्ण
module_निकास(max8649_निकास);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MAXIM 8649 voltage regulator driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
