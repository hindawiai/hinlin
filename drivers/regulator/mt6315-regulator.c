<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2021 MediaTek Inc.

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/mt6315-regulator.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/spmi.h>

#घोषणा MT6315_BUCK_MODE_AUTO		0
#घोषणा MT6315_BUCK_MODE_FORCE_PWM	1
#घोषणा MT6315_BUCK_MODE_LP		2

काष्ठा mt6315_regulator_info अणु
	काष्ठा regulator_desc desc;
	u32 status_reg;
	u32 lp_mode_mask;
	u32 lp_mode_shअगरt;
पूर्ण;

काष्ठा mt_regulator_init_data अणु
	u32 modeset_mask[MT6315_VBUCK_MAX];
पूर्ण;

काष्ठा mt6315_chip अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

#घोषणा MT_BUCK(_name, _bid, _vsel)				\
[_bid] = अणु							\
	.desc = अणु						\
		.name = _name,					\
		.of_match = of_match_ptr(_name),		\
		.regulators_node = "regulators",		\
		.ops = &mt6315_volt_range_ops,			\
		.type = REGULATOR_VOLTAGE,			\
		.id = _bid,					\
		.owner = THIS_MODULE,				\
		.n_voltages = 0xc0,				\
		.linear_ranges = mt_volt_range1,		\
		.n_linear_ranges = ARRAY_SIZE(mt_volt_range1),	\
		.vsel_reg = _vsel,				\
		.vsel_mask = 0xff,				\
		.enable_reg = MT6315_BUCK_TOP_CON0,		\
		.enable_mask = BIT(_bid),			\
		.of_map_mode = mt6315_map_mode,			\
	पूर्ण,							\
	.status_reg = _bid##_DBG4,				\
	.lp_mode_mask = BIT(_bid),				\
	.lp_mode_shअगरt = _bid,					\
पूर्ण

अटल स्थिर काष्ठा linear_range mt_volt_range1[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0, 0xbf, 6250),
पूर्ण;

अटल अचिन्हित पूर्णांक mt6315_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल MT6315_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	हाल MT6315_BUCK_MODE_FORCE_PWM:
		वापस REGULATOR_MODE_FAST;
	हाल MT6315_BUCK_MODE_LP:
		वापस REGULATOR_MODE_IDLE;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक mt6315_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mt_regulator_init_data *init = rdev_get_drvdata(rdev);
	स्थिर काष्ठा mt6315_regulator_info *info;
	पूर्णांक ret, regval;
	u32 modeset_mask;

	info = container_of(rdev->desc, काष्ठा mt6315_regulator_info, desc);
	modeset_mask = init->modeset_mask[rdev_get_id(rdev)];
	ret = regmap_पढ़ो(rdev->regmap, MT6315_BUCK_TOP_4PHASE_ANA_CON42, &regval);
	अगर (ret != 0) अणु
		dev_notice(&rdev->dev, "Failed to get mode: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर ((regval & modeset_mask) == modeset_mask)
		वापस REGULATOR_MODE_FAST;

	ret = regmap_पढ़ो(rdev->regmap, MT6315_BUCK_TOP_CON1, &regval);
	अगर (ret != 0) अणु
		dev_notice(&rdev->dev, "Failed to get lp mode: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (regval & info->lp_mode_mask)
		वापस REGULATOR_MODE_IDLE;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक mt6315_regulator_set_mode(काष्ठा regulator_dev *rdev,
				     u32 mode)
अणु
	काष्ठा mt_regulator_init_data *init = rdev_get_drvdata(rdev);
	स्थिर काष्ठा mt6315_regulator_info *info;
	पूर्णांक ret, val, curr_mode;
	u32 modeset_mask;

	info = container_of(rdev->desc, काष्ठा mt6315_regulator_info, desc);
	modeset_mask = init->modeset_mask[rdev_get_id(rdev)];
	curr_mode = mt6315_regulator_get_mode(rdev);
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		ret = regmap_update_bits(rdev->regmap,
					 MT6315_BUCK_TOP_4PHASE_ANA_CON42,
					 modeset_mask,
					 modeset_mask);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		अगर (curr_mode == REGULATOR_MODE_FAST) अणु
			ret = regmap_update_bits(rdev->regmap,
						 MT6315_BUCK_TOP_4PHASE_ANA_CON42,
						 modeset_mask,
						 0);
		पूर्ण अन्यथा अगर (curr_mode == REGULATOR_MODE_IDLE) अणु
			ret = regmap_update_bits(rdev->regmap,
						 MT6315_BUCK_TOP_CON1,
						 info->lp_mode_mask,
						 0);
			usleep_range(100, 110);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = MT6315_BUCK_MODE_LP >> 1;
		val <<= info->lp_mode_shअगरt;
		ret = regmap_update_bits(rdev->regmap,
					 MT6315_BUCK_TOP_CON1,
					 info->lp_mode_mask,
					 val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_notice(&rdev->dev, "Unsupported mode: %d\n", mode);
		अवरोध;
	पूर्ण

	अगर (ret != 0) अणु
		dev_notice(&rdev->dev, "Failed to set mode: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6315_get_status(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा mt6315_regulator_info *info;
	पूर्णांक ret;
	u32 regval;

	info = container_of(rdev->desc, काष्ठा mt6315_regulator_info, desc);
	ret = regmap_पढ़ो(rdev->regmap, info->status_reg, &regval);
	अगर (ret < 0) अणु
		dev_notice(&rdev->dev, "Failed to get enable reg: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस (regval & BIT(0)) ? REGULATOR_STATUS_ON : REGULATOR_STATUS_OFF;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mt6315_volt_range_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6315_get_status,
	.set_mode = mt6315_regulator_set_mode,
	.get_mode = mt6315_regulator_get_mode,
पूर्ण;

अटल स्थिर काष्ठा mt6315_regulator_info mt6315_regulators[MT6315_VBUCK_MAX] = अणु
	MT_BUCK("vbuck1", MT6315_VBUCK1, MT6315_BUCK_TOP_ELR0),
	MT_BUCK("vbuck2", MT6315_VBUCK2, MT6315_BUCK_TOP_ELR2),
	MT_BUCK("vbuck3", MT6315_VBUCK3, MT6315_BUCK_TOP_ELR4),
	MT_BUCK("vbuck4", MT6315_VBUCK4, MT6315_BUCK_TOP_ELR6),
पूर्ण;

अटल स्थिर काष्ठा regmap_config mt6315_regmap_config = अणु
	.reg_bits	= 16,
	.val_bits	= 8,
	.max_रेजिस्टर	= 0x16d0,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt6315_of_match[] = अणु
	अणु
		.compatible = "mediatek,mt6315-regulator",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6315_of_match);

अटल पूर्णांक mt6315_regulator_probe(काष्ठा spmi_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	काष्ठा mt6315_chip *chip;
	काष्ठा mt_regulator_init_data *init_data;
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	regmap = devm_regmap_init_spmi_ext(pdev, &mt6315_regmap_config);
	अगर (!regmap)
		वापस -ENODEV;

	chip = devm_kzalloc(dev, माप(काष्ठा mt6315_chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	init_data = devm_kzalloc(dev, माप(काष्ठा mt_regulator_init_data), GFP_KERNEL);
	अगर (!init_data)
		वापस -ENOMEM;

	चयन (pdev->usid) अणु
	हाल MT6315_PP:
		init_data->modeset_mask[MT6315_VBUCK1] = BIT(MT6315_VBUCK1) | BIT(MT6315_VBUCK2) |
							 BIT(MT6315_VBUCK4);
		अवरोध;
	हाल MT6315_SP:
	हाल MT6315_RP:
		init_data->modeset_mask[MT6315_VBUCK1] = BIT(MT6315_VBUCK1) | BIT(MT6315_VBUCK2);
		अवरोध;
	शेष:
		init_data->modeset_mask[MT6315_VBUCK1] = BIT(MT6315_VBUCK1);
		अवरोध;
	पूर्ण
	क्रम (i = MT6315_VBUCK2; i < MT6315_VBUCK_MAX; i++)
		init_data->modeset_mask[i] = BIT(i);

	chip->dev = dev;
	chip->regmap = regmap;
	dev_set_drvdata(dev, chip);

	config.dev = dev;
	config.regmap = regmap;
	क्रम (i = MT6315_VBUCK1; i < MT6315_VBUCK_MAX; i++) अणु
		config.driver_data = init_data;
		rdev = devm_regulator_रेजिस्टर(dev, &mt6315_regulators[i].desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_notice(dev, "Failed to register %s\n", mt6315_regulators[i].desc.name);
			जारी;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt6315_regulator_shutकरोwn(काष्ठा spmi_device *pdev)
अणु
	काष्ठा mt6315_chip *chip = dev_get_drvdata(&pdev->dev);
	पूर्णांक ret = 0;

	ret |= regmap_ग_लिखो(chip->regmap, MT6315_TOP_TMA_KEY_H, PROTECTION_KEY_H);
	ret |= regmap_ग_लिखो(chip->regmap, MT6315_TOP_TMA_KEY, PROTECTION_KEY);
	ret |= regmap_update_bits(chip->regmap, MT6315_TOP2_ELR7, 1, 1);
	ret |= regmap_ग_लिखो(chip->regmap, MT6315_TOP_TMA_KEY, 0);
	ret |= regmap_ग_लिखो(chip->regmap, MT6315_TOP_TMA_KEY_H, 0);
	अगर (ret < 0)
		dev_notice(&pdev->dev, "[%#x] Failed to enable power off sequence. %d\n",
			   pdev->usid, ret);
पूर्ण

अटल काष्ठा spmi_driver mt6315_regulator_driver = अणु
	.driver		= अणु
		.name	= "mt6315-regulator",
		.of_match_table = mt6315_of_match,
	पूर्ण,
	.probe = mt6315_regulator_probe,
	.shutकरोwn = mt6315_regulator_shutकरोwn,
पूर्ण;

module_spmi_driver(mt6315_regulator_driver);

MODULE_AUTHOR("Hsin-Hsiung Wang <hsin-hsiung.wang@mediatek.com>");
MODULE_DESCRIPTION("Regulator Driver for MediaTek MT6315 PMIC");
MODULE_LICENSE("GPL");
