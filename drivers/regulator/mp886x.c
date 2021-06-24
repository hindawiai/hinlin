<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MP8867/MP8869 regulator driver
//
// Copyright (C) 2020 Synaptics Incorporated
//
// Author: Jisheng Zhang <jszhang@kernel.org>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा MP886X_VSEL		0x00
#घोषणा  MP886X_V_BOOT		(1 << 7)
#घोषणा MP886X_SYSCNTLREG1	0x01
#घोषणा  MP886X_MODE		(1 << 0)
#घोषणा  MP886X_SLEW_SHIFT	3
#घोषणा  MP886X_SLEW_MASK	(0x7 << MP886X_SLEW_SHIFT)
#घोषणा  MP886X_GO		(1 << 6)
#घोषणा  MP886X_EN		(1 << 7)
#घोषणा MP8869_SYSCNTLREG2	0x02

काष्ठा mp886x_cfg_info अणु
	स्थिर काष्ठा regulator_ops *rops;
	स्थिर पूर्णांक slew_rates[8];
	स्थिर पूर्णांक चयन_freq[4];
	स्थिर u8 fs_reg;
	स्थिर u8 fs_shअगरt;
पूर्ण;

काष्ठा mp886x_device_info अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_init_data *regulator;
	काष्ठा gpio_desc *en_gpio;
	स्थिर काष्ठा mp886x_cfg_info *ci;
	u32 r[2];
	अचिन्हित पूर्णांक sel;
पूर्ण;

अटल पूर्णांक mp886x_set_ramp(काष्ठा regulator_dev *rdev, पूर्णांक ramp)
अणु
	काष्ठा mp886x_device_info *di = rdev_get_drvdata(rdev);
	स्थिर काष्ठा mp886x_cfg_info *ci = di->ci;
	पूर्णांक reg = -1, i;

	क्रम (i = 0; i < ARRAY_SIZE(ci->slew_rates); i++) अणु
		अगर (ramp <= ci->slew_rates[i])
			reg = i;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (reg < 0) अणु
		dev_err(di->dev, "unsupported ramp value %d\n", ramp);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, MP886X_SYSCNTLREG1,
				  MP886X_SLEW_MASK, reg << MP886X_SLEW_SHIFT);
पूर्ण

अटल व्योम mp886x_set_चयन_freq(काष्ठा mp886x_device_info *di,
				   काष्ठा regmap *regmap,
				   u32 freq)
अणु
	स्थिर काष्ठा mp886x_cfg_info *ci = di->ci;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ci->चयन_freq); i++) अणु
		अगर (freq == ci->चयन_freq[i]) अणु
			regmap_update_bits(regmap, ci->fs_reg,
				  0x3 << ci->fs_shअगरt, i << ci->fs_shअगरt);
			वापस;
		पूर्ण
	पूर्ण

	dev_err(di->dev, "invalid frequency %d\n", freq);
पूर्ण

अटल पूर्णांक mp886x_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		regmap_update_bits(rdev->regmap, MP886X_SYSCNTLREG1,
				   MP886X_MODE, MP886X_MODE);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		regmap_update_bits(rdev->regmap, MP886X_SYSCNTLREG1,
				   MP886X_MODE, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mp886x_get_mode(काष्ठा regulator_dev *rdev)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, MP886X_SYSCNTLREG1, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val & MP886X_MODE)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक mp8869_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(rdev->regmap, MP886X_SYSCNTLREG1,
				 MP886X_GO, MP886X_GO);
	अगर (ret < 0)
		वापस ret;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;
	वापस regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
				  MP886X_V_BOOT | rdev->desc->vsel_mask, sel);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mp8869_scale(अचिन्हित पूर्णांक uv, u32 r1, u32 r2)
अणु
	u32 पंचांगp = uv * r1 / r2;

	वापस uv + पंचांगp;
पूर्ण

अटल पूर्णांक mp8869_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mp886x_device_info *di = rdev_get_drvdata(rdev);
	पूर्णांक ret, uv;
	अचिन्हित पूर्णांक val;
	bool fbloop;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret)
		वापस ret;

	fbloop = val & MP886X_V_BOOT;
	अगर (fbloop) अणु
		uv = rdev->desc->min_uV;
		uv = mp8869_scale(uv, di->r[0], di->r[1]);
		वापस regulator_map_voltage_linear(rdev, uv, uv);
	पूर्ण

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	वापस val;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mp8869_regulator_ops = अणु
	.set_voltage_sel = mp8869_set_voltage_sel,
	.get_voltage_sel = mp8869_get_voltage_sel,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.map_voltage = regulator_map_voltage_linear,
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = mp886x_set_mode,
	.get_mode = mp886x_get_mode,
	.set_ramp_delay = mp886x_set_ramp,
पूर्ण;

अटल स्थिर काष्ठा mp886x_cfg_info mp8869_ci = अणु
	.rops = &mp8869_regulator_ops,
	.slew_rates = अणु
		40000,
		30000,
		20000,
		10000,
		5000,
		2500,
		1250,
		625,
	पूर्ण,
	.चयन_freq = अणु
		500000,
		750000,
		1000000,
		1250000,
	पूर्ण,
	.fs_reg = MP8869_SYSCNTLREG2,
	.fs_shअगरt = 4,
पूर्ण;

अटल पूर्णांक mp8867_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel)
अणु
	काष्ठा mp886x_device_info *di = rdev_get_drvdata(rdev);
	पूर्णांक ret, delta;

	ret = mp8869_set_voltage_sel(rdev, sel);
	अगर (ret < 0)
		वापस ret;

	delta = di->sel - sel;
	अगर (असल(delta) <= 5)
		ret = regmap_update_bits(rdev->regmap, MP886X_SYSCNTLREG1,
					 MP886X_GO, 0);
	di->sel = sel;

	वापस ret;
पूर्ण

अटल पूर्णांक mp8867_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mp886x_device_info *di = rdev_get_drvdata(rdev);
	पूर्णांक ret, uv;
	अचिन्हित पूर्णांक val;
	bool fbloop;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret)
		वापस ret;

	fbloop = val & MP886X_V_BOOT;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	अगर (fbloop) अणु
		uv = regulator_list_voltage_linear(rdev, val);
		uv = mp8869_scale(uv, di->r[0], di->r[1]);
		वापस regulator_map_voltage_linear(rdev, uv, uv);
	पूर्ण

	वापस val;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mp8867_regulator_ops = अणु
	.set_voltage_sel = mp8867_set_voltage_sel,
	.get_voltage_sel = mp8867_get_voltage_sel,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.map_voltage = regulator_map_voltage_linear,
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = mp886x_set_mode,
	.get_mode = mp886x_get_mode,
	.set_ramp_delay = mp886x_set_ramp,
पूर्ण;

अटल स्थिर काष्ठा mp886x_cfg_info mp8867_ci = अणु
	.rops = &mp8867_regulator_ops,
	.slew_rates = अणु
		64000,
		32000,
		16000,
		8000,
		4000,
		2000,
		1000,
		500,
	पूर्ण,
	.चयन_freq = अणु
		500000,
		750000,
		1000000,
		1500000,
	पूर्ण,
	.fs_reg = MP886X_SYSCNTLREG1,
	.fs_shअगरt = 1,
पूर्ण;

अटल पूर्णांक mp886x_regulator_रेजिस्टर(काष्ठा mp886x_device_info *di,
				     काष्ठा regulator_config *config)
अणु
	काष्ठा regulator_desc *rdesc = &di->desc;
	काष्ठा regulator_dev *rdev;

	rdesc->name = "mp886x-reg";
	rdesc->supply_name = "vin";
	rdesc->ops = di->ci->rops;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->n_voltages = 128;
	rdesc->enable_reg = MP886X_SYSCNTLREG1;
	rdesc->enable_mask = MP886X_EN;
	rdesc->min_uV = 600000;
	rdesc->uV_step = 10000;
	rdesc->vsel_reg = MP886X_VSEL;
	rdesc->vsel_mask = 0x3f;
	rdesc->owner = THIS_MODULE;

	rdev = devm_regulator_रेजिस्टर(di->dev, &di->desc, config);
	अगर (IS_ERR(rdev))
		वापस PTR_ERR(rdev);
	di->sel = rdesc->ops->get_voltage_sel(rdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config mp886x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक mp886x_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा mp886x_device_info *di;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	u32 freq;
	पूर्णांक ret;

	di = devm_kzalloc(dev, माप(काष्ठा mp886x_device_info), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	di->regulator = of_get_regulator_init_data(dev, np, &di->desc);
	अगर (!di->regulator) अणु
		dev_err(dev, "Platform data not found!\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np, "mps,fb-voltage-divider",
					 di->r, 2);
	अगर (ret)
		वापस ret;

	di->en_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(di->en_gpio))
		वापस PTR_ERR(di->en_gpio);

	di->ci = of_device_get_match_data(dev);
	di->dev = dev;

	regmap = devm_regmap_init_i2c(client, &mp886x_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to allocate regmap!\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	i2c_set_clientdata(client, di);

	config.dev = di->dev;
	config.init_data = di->regulator;
	config.regmap = regmap;
	config.driver_data = di;
	config.of_node = np;

	अगर (!of_property_पढ़ो_u32(np, "mps,switch-frequency-hz", &freq))
		mp886x_set_चयन_freq(di, regmap, freq);

	ret = mp886x_regulator_रेजिस्टर(di, &config);
	अगर (ret < 0)
		dev_err(dev, "Failed to register regulator!\n");
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mp886x_dt_ids[] = अणु
	अणु
		.compatible = "mps,mp8867",
		.data = &mp8867_ci
	पूर्ण,
	अणु
		.compatible = "mps,mp8869",
		.data = &mp8869_ci
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mp886x_dt_ids);

अटल स्थिर काष्ठा i2c_device_id mp886x_id[] = अणु
	अणु "mp886x", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mp886x_id);

अटल काष्ठा i2c_driver mp886x_regulator_driver = अणु
	.driver = अणु
		.name = "mp886x-regulator",
		.of_match_table = of_match_ptr(mp886x_dt_ids),
	पूर्ण,
	.probe_new = mp886x_i2c_probe,
	.id_table = mp886x_id,
पूर्ण;
module_i2c_driver(mp886x_regulator_driver);

MODULE_AUTHOR("Jisheng Zhang <jszhang@kernel.org>");
MODULE_DESCRIPTION("MP886x regulator driver");
MODULE_LICENSE("GPL v2");
