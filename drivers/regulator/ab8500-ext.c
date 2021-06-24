<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Authors: Bengt Jonsson <bengt.g.jonsson@stericsson.com>
 *
 * This file is based on drivers/regulator/ab8500.c
 *
 * AB8500 बाह्यal regulators
 *
 * ab8500-ext supports the following regulators:
 * - VextSupply3
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>

/* AB8500 बाह्यal regulators */
क्रमागत ab8500_ext_regulator_id अणु
	AB8500_EXT_SUPPLY1,
	AB8500_EXT_SUPPLY2,
	AB8500_EXT_SUPPLY3,
	AB8500_NUM_EXT_REGULATORS,
पूर्ण;

काष्ठा ab8500_ext_regulator_cfg अणु
	bool hwreq; /* requires hw mode or high घातer mode */
पूर्ण;

/* supply क्रम VextSupply3 */
अटल काष्ठा regulator_consumer_supply ab8500_ext_supply3_consumers[] = अणु
	/* SIM supply क्रम 3 V SIM cards */
	REGULATOR_SUPPLY("vinvsim", "sim-detect.0"),
पूर्ण;

/*
 * AB8500 बाह्यal regulators
 */
अटल काष्ठा regulator_init_data ab8500_ext_regulators[] = अणु
	/* fixed Vbat supplies VSMPS1_EXT_1V8 */
	[AB8500_EXT_SUPPLY1] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "ab8500-ext-supply1",
			.min_uV = 1800000,
			.max_uV = 1800000,
			.initial_mode = REGULATOR_MODE_IDLE,
			.boot_on = 1,
			.always_on = 1,
		पूर्ण,
	पूर्ण,
	/* fixed Vbat supplies VSMPS2_EXT_1V36 and VSMPS5_EXT_1V15 */
	[AB8500_EXT_SUPPLY2] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "ab8500-ext-supply2",
			.min_uV = 1360000,
			.max_uV = 1360000,
		पूर्ण,
	पूर्ण,
	/* fixed Vbat supplies VSMPS3_EXT_3V4 and VSMPS4_EXT_3V4 */
	[AB8500_EXT_SUPPLY3] = अणु
		.स्थिरraपूर्णांकs = अणु
			.name = "ab8500-ext-supply3",
			.min_uV = 3400000,
			.max_uV = 3400000,
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies =
			ARRAY_SIZE(ab8500_ext_supply3_consumers),
		.consumer_supplies = ab8500_ext_supply3_consumers,
	पूर्ण,
पूर्ण;

/**
 * काष्ठा ab8500_ext_regulator_info - ab8500 regulator inक्रमmation
 * @dev: device poपूर्णांकer
 * @desc: regulator description
 * @cfg: regulator configuration (extension of regulator FW configuration)
 * @update_bank: bank to control on/off
 * @update_reg: रेजिस्टर to control on/off
 * @update_mask: mask to enable/disable and set mode of regulator
 * @update_val: bits holding the regulator current mode
 * @update_val_hp: bits to set EN pin active (LPn pin deactive)
 *                 normally this means high घातer mode
 * @update_val_lp: bits to set EN pin active and LPn pin active
 *                 normally this means low घातer mode
 * @update_val_hw: bits to set regulator pins in HW control
 *                 SysClkReq pins and logic will choose mode
 */
काष्ठा ab8500_ext_regulator_info अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा ab8500_ext_regulator_cfg *cfg;
	u8 update_bank;
	u8 update_reg;
	u8 update_mask;
	u8 update_val;
	u8 update_val_hp;
	u8 update_val_lp;
	u8 update_val_hw;
पूर्ण;

अटल पूर्णांक ab8500_ext_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * To satisfy both HW high घातer request and SW request, the regulator
	 * must be on in high घातer.
	 */
	अगर (info->cfg && info->cfg->hwreq)
		regval = info->update_val_hp;
	अन्यथा
		regval = info->update_val;

	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
		info->update_bank, info->update_reg,
		info->update_mask, regval);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"couldn't set enable bits for regulator\n");
		वापस ret;
	पूर्ण

	dev_dbg(rdev_get_dev(rdev),
		"%s-enable (bank, reg, mask, value): 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, regval);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_ext_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set the regulator in HW request mode अगर configured
	 */
	अगर (info->cfg && info->cfg->hwreq)
		regval = info->update_val_hw;
	अन्यथा
		regval = 0;

	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
		info->update_bank, info->update_reg,
		info->update_mask, regval);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"couldn't set disable bits for regulator\n");
		वापस ret;
	पूर्ण

	dev_dbg(rdev_get_dev(rdev), "%s-disable (bank, reg, mask, value):"
		" 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, regval);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_ext_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(info->dev,
		info->update_bank, info->update_reg, &regval);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"couldn't read 0x%x register\n", info->update_reg);
		वापस ret;
	पूर्ण

	dev_dbg(rdev_get_dev(rdev), "%s-is_enabled (bank, reg, mask, value):"
		" 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, regval);

	अगर (((regval & info->update_mask) == info->update_val_lp) ||
	    ((regval & info->update_mask) == info->update_val_hp))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक ab8500_ext_regulator_set_mode(काष्ठा regulator_dev *rdev,
					 अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	काष्ठा ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		regval = info->update_val_hp;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		regval = info->update_val_lp;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* If regulator is enabled and info->cfg->hwreq is set, the regulator
	   must be on in high घातer, so we करोn't need to ग_लिखो the रेजिस्टर with
	   the same value.
	 */
	अगर (ab8500_ext_regulator_is_enabled(rdev) &&
	    !(info->cfg && info->cfg->hwreq)) अणु
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
					info->update_bank, info->update_reg,
					info->update_mask, regval);
		अगर (ret < 0) अणु
			dev_err(rdev_get_dev(rdev),
				"Could not set regulator mode.\n");
			वापस ret;
		पूर्ण

		dev_dbg(rdev_get_dev(rdev),
			"%s-set_mode (bank, reg, mask, value): "
			"0x%x, 0x%x, 0x%x, 0x%x\n",
			info->desc.name, info->update_bank, info->update_reg,
			info->update_mask, regval);
	पूर्ण

	info->update_val = regval;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ab8500_ext_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->update_val == info->update_val_hp)
		ret = REGULATOR_MODE_NORMAL;
	अन्यथा अगर (info->update_val == info->update_val_lp)
		ret = REGULATOR_MODE_IDLE;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_ext_set_voltage(काष्ठा regulator_dev *rdev, पूर्णांक min_uV,
				  पूर्णांक max_uV, अचिन्हित *selector)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *regu_स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;

	अगर (!regu_स्थिरraपूर्णांकs) अणु
		dev_err(rdev_get_dev(rdev), "No regulator constraints\n");
		वापस -EINVAL;
	पूर्ण

	अगर (regu_स्थिरraपूर्णांकs->min_uV == min_uV &&
	    regu_स्थिरraपूर्णांकs->max_uV == max_uV)
		वापस 0;

	dev_err(rdev_get_dev(rdev),
		"Requested min %duV max %duV != constrained min %duV max %duV\n",
		min_uV, max_uV,
		regu_स्थिरraपूर्णांकs->min_uV, regu_स्थिरraपूर्णांकs->max_uV);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ab8500_ext_list_voltage(काष्ठा regulator_dev *rdev,
				   अचिन्हित selector)
अणु
	काष्ठा regulation_स्थिरraपूर्णांकs *regu_स्थिरraपूर्णांकs = rdev->स्थिरraपूर्णांकs;

	अगर (regu_स्थिरraपूर्णांकs == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator constraints null pointer\n");
		वापस -EINVAL;
	पूर्ण
	/* वापस the uV क्रम the fixed regulators */
	अगर (regu_स्थिरraपूर्णांकs->min_uV && regu_स्थिरraपूर्णांकs->max_uV) अणु
		अगर (regu_स्थिरraपूर्णांकs->min_uV == regu_स्थिरraपूर्णांकs->max_uV)
			वापस regu_स्थिरraपूर्णांकs->min_uV;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops ab8500_ext_regulator_ops = अणु
	.enable			= ab8500_ext_regulator_enable,
	.disable		= ab8500_ext_regulator_disable,
	.is_enabled		= ab8500_ext_regulator_is_enabled,
	.set_mode		= ab8500_ext_regulator_set_mode,
	.get_mode		= ab8500_ext_regulator_get_mode,
	.set_voltage		= ab8500_ext_set_voltage,
	.list_voltage		= ab8500_ext_list_voltage,
पूर्ण;

अटल काष्ठा ab8500_ext_regulator_info
		ab8500_ext_regulator_info[AB8500_NUM_EXT_REGULATORS] = अणु
	[AB8500_EXT_SUPPLY1] = अणु
		.desc = अणु
			.name		= "VEXTSUPPLY1",
			.of_match	= of_match_ptr("ab8500_ext1"),
			.ops		= &ab8500_ext_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_EXT_SUPPLY1,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
		पूर्ण,
		.update_bank		= 0x04,
		.update_reg		= 0x08,
		.update_mask		= 0x03,
		.update_val		= 0x01,
		.update_val_hp		= 0x01,
		.update_val_lp		= 0x03,
		.update_val_hw		= 0x02,
	पूर्ण,
	[AB8500_EXT_SUPPLY2] = अणु
		.desc = अणु
			.name		= "VEXTSUPPLY2",
			.of_match	= of_match_ptr("ab8500_ext2"),
			.ops		= &ab8500_ext_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_EXT_SUPPLY2,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
		पूर्ण,
		.update_bank		= 0x04,
		.update_reg		= 0x08,
		.update_mask		= 0x0c,
		.update_val		= 0x04,
		.update_val_hp		= 0x04,
		.update_val_lp		= 0x0c,
		.update_val_hw		= 0x08,
	पूर्ण,
	[AB8500_EXT_SUPPLY3] = अणु
		.desc = अणु
			.name		= "VEXTSUPPLY3",
			.of_match	= of_match_ptr("ab8500_ext3"),
			.ops		= &ab8500_ext_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_EXT_SUPPLY3,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
		पूर्ण,
		.update_bank		= 0x04,
		.update_reg		= 0x08,
		.update_mask		= 0x30,
		.update_val		= 0x10,
		.update_val_hp		= 0x10,
		.update_val_lp		= 0x30,
		.update_val_hw		= 0x20,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ab8500_ext_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	अगर (!ab8500) अणु
		dev_err(&pdev->dev, "null mfd parent\n");
		वापस -EINVAL;
	पूर्ण

	/* check क्रम AB8500 2.x */
	अगर (is_ab8500_2p0_or_earlier(ab8500)) अणु
		काष्ठा ab8500_ext_regulator_info *info;

		/* VextSupply3LPn is inverted on AB8500 2.x */
		info = &ab8500_ext_regulator_info[AB8500_EXT_SUPPLY3];
		info->update_val = 0x30;
		info->update_val_hp = 0x30;
		info->update_val_lp = 0x10;
	पूर्ण

	/* रेजिस्टर all regulators */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_ext_regulator_info); i++) अणु
		काष्ठा ab8500_ext_regulator_info *info = शून्य;

		/* assign per-regulator data */
		info = &ab8500_ext_regulator_info[i];
		info->dev = &pdev->dev;
		info->cfg = (काष्ठा ab8500_ext_regulator_cfg *)
			ab8500_ext_regulators[i].driver_data;

		config.dev = &pdev->dev;
		config.driver_data = info;
		config.init_data = &ab8500_ext_regulators[i];

		/* रेजिस्टर regulator with framework */
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
					info->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण

		dev_dbg(&pdev->dev, "%s-probed\n", info->desc.name);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ab8500_ext_regulator_driver = अणु
	.probe = ab8500_ext_regulator_probe,
	.driver         = अणु
		.name   = "ab8500-ext-regulator",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ab8500_ext_regulator_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&ab8500_ext_regulator_driver);
	अगर (ret)
		pr_err("Failed to register ab8500 ext regulator: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(ab8500_ext_regulator_init);

अटल व्योम __निकास ab8500_ext_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ab8500_ext_regulator_driver);
पूर्ण
module_निकास(ab8500_ext_regulator_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Bengt Jonsson <bengt.g.jonsson@stericsson.com>");
MODULE_DESCRIPTION("AB8500 external regulator driver");
MODULE_ALIAS("platform:ab8500-ext-regulator");
