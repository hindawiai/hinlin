<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Authors: Sundar Iyer <sundar.iyer@stericsson.com> क्रम ST-Ericsson
 *          Bengt Jonsson <bengt.g.jonsson@stericsson.com> क्रम ST-Ericsson
 *          Daniel Willerud <daniel.willerud@stericsson.com> क्रम ST-Ericsson
 *
 * AB8500 peripheral regulators
 *
 * AB8500 supports the following regulators:
 *   VAUX1/2/3, VINTCORE, VTVOUT, VUSB, VAUDIO, VAMIC1/2, VDMIC, VANA
 *
 * AB8505 supports the following regulators:
 *   VAUX1/2/3/4/5/6, VINTCORE, VADC, VUSB, VAUDIO, VAMIC1/2, VDMIC, VANA
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/slab.h>

/* AB8500 regulators */
क्रमागत ab8500_regulator_id अणु
	AB8500_LDO_AUX1,
	AB8500_LDO_AUX2,
	AB8500_LDO_AUX3,
	AB8500_LDO_INTCORE,
	AB8500_LDO_TVOUT,
	AB8500_LDO_AUDIO,
	AB8500_LDO_ANAMIC1,
	AB8500_LDO_ANAMIC2,
	AB8500_LDO_DMIC,
	AB8500_LDO_ANA,
	AB8500_NUM_REGULATORS,
पूर्ण;

/* AB8505 regulators */
क्रमागत ab8505_regulator_id अणु
	AB8505_LDO_AUX1,
	AB8505_LDO_AUX2,
	AB8505_LDO_AUX3,
	AB8505_LDO_AUX4,
	AB8505_LDO_AUX5,
	AB8505_LDO_AUX6,
	AB8505_LDO_INTCORE,
	AB8505_LDO_ADC,
	AB8505_LDO_AUDIO,
	AB8505_LDO_ANAMIC1,
	AB8505_LDO_ANAMIC2,
	AB8505_LDO_AUX8,
	AB8505_LDO_ANA,
	AB8505_NUM_REGULATORS,
पूर्ण;

/* AB8500 रेजिस्टरs */
क्रमागत ab8500_regulator_reg अणु
	AB8500_REGUREQUESTCTRL2,
	AB8500_REGUREQUESTCTRL3,
	AB8500_REGUREQUESTCTRL4,
	AB8500_REGUSYSCLKREQ1HPVALID1,
	AB8500_REGUSYSCLKREQ1HPVALID2,
	AB8500_REGUHWHPREQ1VALID1,
	AB8500_REGUHWHPREQ1VALID2,
	AB8500_REGUHWHPREQ2VALID1,
	AB8500_REGUHWHPREQ2VALID2,
	AB8500_REGUSWHPREQVALID1,
	AB8500_REGUSWHPREQVALID2,
	AB8500_REGUSYSCLKREQVALID1,
	AB8500_REGUSYSCLKREQVALID2,
	AB8500_REGUMISC1,
	AB8500_VAUDIOSUPPLY,
	AB8500_REGUCTRL1VAMIC,
	AB8500_VPLLVANAREGU,
	AB8500_VREFDDR,
	AB8500_EXTSUPPLYREGU,
	AB8500_VAUX12REGU,
	AB8500_VRF1VAUX3REGU,
	AB8500_VAUX1SEL,
	AB8500_VAUX2SEL,
	AB8500_VRF1VAUX3SEL,
	AB8500_REGUCTRL2SPARE,
	AB8500_REGUCTRLDISCH,
	AB8500_REGUCTRLDISCH2,
	AB8500_NUM_REGULATOR_REGISTERS,
पूर्ण;

/* AB8505 रेजिस्टरs */
क्रमागत ab8505_regulator_reg अणु
	AB8505_REGUREQUESTCTRL1,
	AB8505_REGUREQUESTCTRL2,
	AB8505_REGUREQUESTCTRL3,
	AB8505_REGUREQUESTCTRL4,
	AB8505_REGUSYSCLKREQ1HPVALID1,
	AB8505_REGUSYSCLKREQ1HPVALID2,
	AB8505_REGUHWHPREQ1VALID1,
	AB8505_REGUHWHPREQ1VALID2,
	AB8505_REGUHWHPREQ2VALID1,
	AB8505_REGUHWHPREQ2VALID2,
	AB8505_REGUSWHPREQVALID1,
	AB8505_REGUSWHPREQVALID2,
	AB8505_REGUSYSCLKREQVALID1,
	AB8505_REGUSYSCLKREQVALID2,
	AB8505_REGUVAUX4REQVALID,
	AB8505_REGUMISC1,
	AB8505_VAUDIOSUPPLY,
	AB8505_REGUCTRL1VAMIC,
	AB8505_VSMPSAREGU,
	AB8505_VSMPSBREGU,
	AB8505_VSAFEREGU, /* NOTE! PRCMU रेजिस्टर */
	AB8505_VPLLVANAREGU,
	AB8505_EXTSUPPLYREGU,
	AB8505_VAUX12REGU,
	AB8505_VRF1VAUX3REGU,
	AB8505_VSMPSASEL1,
	AB8505_VSMPSASEL2,
	AB8505_VSMPSASEL3,
	AB8505_VSMPSBSEL1,
	AB8505_VSMPSBSEL2,
	AB8505_VSMPSBSEL3,
	AB8505_VSAFESEL1, /* NOTE! PRCMU रेजिस्टर */
	AB8505_VSAFESEL2, /* NOTE! PRCMU रेजिस्टर */
	AB8505_VSAFESEL3, /* NOTE! PRCMU रेजिस्टर */
	AB8505_VAUX1SEL,
	AB8505_VAUX2SEL,
	AB8505_VRF1VAUX3SEL,
	AB8505_VAUX4REQCTRL,
	AB8505_VAUX4REGU,
	AB8505_VAUX4SEL,
	AB8505_REGUCTRLDISCH,
	AB8505_REGUCTRLDISCH2,
	AB8505_REGUCTRLDISCH3,
	AB8505_CTRLVAUX5,
	AB8505_CTRLVAUX6,
	AB8505_NUM_REGULATOR_REGISTERS,
पूर्ण;

/**
 * काष्ठा ab8500_shared_mode - is used when mode is shared between
 * two regulators.
 * @shared_regulator: poपूर्णांकer to the other sharing regulator
 * @lp_mode_req: low घातer mode requested by this regulator
 */
काष्ठा ab8500_shared_mode अणु
	काष्ठा ab8500_regulator_info *shared_regulator;
	bool lp_mode_req;
पूर्ण;

/**
 * काष्ठा ab8500_regulator_info - ab8500 regulator inक्रमmation
 * @dev: device poपूर्णांकer
 * @desc: regulator description
 * @shared_mode: used when mode is shared between two regulators
 * @load_lp_uA: maximum load in idle (low घातer) mode
 * @update_bank: bank to control on/off
 * @update_reg: रेजिस्टर to control on/off
 * @update_mask: mask to enable/disable and set mode of regulator
 * @update_val: bits holding the regulator current mode
 * @update_val_idle: bits to enable the regulator in idle (low घातer) mode
 * @update_val_normal: bits to enable the regulator in normal (high घातer) mode
 * @mode_bank: bank with location of mode रेजिस्टर
 * @mode_reg: mode रेजिस्टर
 * @mode_mask: mask क्रम setting mode
 * @mode_val_idle: mode setting क्रम low घातer
 * @mode_val_normal: mode setting क्रम normal घातer
 * @voltage_bank: bank to control regulator voltage
 * @voltage_reg: रेजिस्टर to control regulator voltage
 * @voltage_mask: mask to control regulator voltage
 * @expand_रेजिस्टर: 
 */
काष्ठा ab8500_regulator_info अणु
	काष्ठा device		*dev;
	काष्ठा regulator_desc	desc;
	काष्ठा ab8500_shared_mode *shared_mode;
	पूर्णांक load_lp_uA;
	u8 update_bank;
	u8 update_reg;
	u8 update_mask;
	u8 update_val;
	u8 update_val_idle;
	u8 update_val_normal;
	u8 mode_bank;
	u8 mode_reg;
	u8 mode_mask;
	u8 mode_val_idle;
	u8 mode_val_normal;
	u8 voltage_bank;
	u8 voltage_reg;
	u8 voltage_mask;
पूर्ण;

/* voltage tables क्रम the vauxn/vपूर्णांकcore supplies */
अटल स्थिर अचिन्हित पूर्णांक lकरो_vauxn_voltages[] = अणु
	1100000,
	1200000,
	1300000,
	1400000,
	1500000,
	1800000,
	1850000,
	1900000,
	2500000,
	2650000,
	2700000,
	2750000,
	2800000,
	2900000,
	3000000,
	3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_vaux3_voltages[] = अणु
	1200000,
	1500000,
	1800000,
	2100000,
	2500000,
	2750000,
	2790000,
	2910000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_vaux56_voltages[] = अणु
	1800000,
	1050000,
	1100000,
	1200000,
	1500000,
	2200000,
	2500000,
	2790000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_vपूर्णांकcore_voltages[] = अणु
	1200000,
	1225000,
	1250000,
	1275000,
	1300000,
	1325000,
	1350000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_1200000_voltage[] = अणु
	1200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_1800000_voltage[] = अणु
	1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_2000000_voltage[] = अणु
	2000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fixed_2050000_voltage[] = अणु
	2050000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_vana_voltages[] = अणु
	1050000,
	1075000,
	1100000,
	1125000,
	1150000,
	1175000,
	1200000,
	1225000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_vaudio_voltages[] = अणु
	2000000,
	2100000,
	2200000,
	2300000,
	2400000,
	2500000,
	2600000,
	2600000,	/* Duplicated in Vaudio and IsoUicc Control रेजिस्टर. */
पूर्ण;

अटल DEFINE_MUTEX(shared_mode_mutex);
अटल काष्ठा ab8500_shared_mode lकरो_anamic1_shared;
अटल काष्ठा ab8500_shared_mode lकरो_anamic2_shared;

अटल पूर्णांक ab8500_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
		info->update_bank, info->update_reg,
		info->update_mask, info->update_val);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"couldn't set enable bits for regulator\n");
		वापस ret;
	पूर्ण

	dev_vdbg(rdev_get_dev(rdev),
		"%s-enable (bank, reg, mask, value): 0x%x, 0x%x, 0x%x, 0x%x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, info->update_val);

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
		info->update_bank, info->update_reg,
		info->update_mask, 0x0);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"couldn't set disable bits for regulator\n");
		वापस ret;
	पूर्ण

	dev_vdbg(rdev_get_dev(rdev),
		"%s-disable (bank, reg, mask, value): 0x%x, 0x%x, 0x%x, 0x%x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, 0x0);

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);
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

	dev_vdbg(rdev_get_dev(rdev),
		"%s-is_enabled (bank, reg, mask, value): 0x%x, 0x%x, 0x%x,"
		" 0x%x\n",
		info->desc.name, info->update_bank, info->update_reg,
		info->update_mask, regval);

	अगर (regval & info->update_mask)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ab8500_regulator_get_optimum_mode(
		काष्ठा regulator_dev *rdev, पूर्णांक input_uV,
		पूर्णांक output_uV, पूर्णांक load_uA)
अणु
	अचिन्हित पूर्णांक mode;

	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (load_uA <= info->load_lp_uA)
		mode = REGULATOR_MODE_IDLE;
	अन्यथा
		mode = REGULATOR_MODE_NORMAL;

	वापस mode;
पूर्ण

अटल पूर्णांक ab8500_regulator_set_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	u8 bank, reg, mask, val;
	bool lp_mode_req = false;
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->mode_mask) अणु
		bank = info->mode_bank;
		reg = info->mode_reg;
		mask = info->mode_mask;
	पूर्ण अन्यथा अणु
		bank = info->update_bank;
		reg = info->update_reg;
		mask = info->update_mask;
	पूर्ण

	अगर (info->shared_mode)
		mutex_lock(&shared_mode_mutex);

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		अगर (info->shared_mode)
			lp_mode_req = false;

		अगर (info->mode_mask)
			val = info->mode_val_normal;
		अन्यथा
			val = info->update_val_normal;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		अगर (info->shared_mode) अणु
			काष्ठा ab8500_regulator_info *shared_regulator;

			shared_regulator = info->shared_mode->shared_regulator;
			अगर (!shared_regulator->shared_mode->lp_mode_req) अणु
				/* Other regulator prevent LP mode */
				info->shared_mode->lp_mode_req = true;
				जाओ out_unlock;
			पूर्ण

			lp_mode_req = true;
		पूर्ण

		अगर (info->mode_mask)
			val = info->mode_val_idle;
		अन्यथा
			val = info->update_val_idle;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (info->mode_mask || ab8500_regulator_is_enabled(rdev)) अणु
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
			bank, reg, mask, val);
		अगर (ret < 0) अणु
			dev_err(rdev_get_dev(rdev),
				"couldn't set regulator mode\n");
			जाओ out_unlock;
		पूर्ण

		dev_vdbg(rdev_get_dev(rdev),
			"%s-set_mode (bank, reg, mask, value): "
			"0x%x, 0x%x, 0x%x, 0x%x\n",
			info->desc.name, bank, reg,
			mask, val);
	पूर्ण

	अगर (!info->mode_mask)
		info->update_val = val;

	अगर (info->shared_mode)
		info->shared_mode->lp_mode_req = lp_mode_req;

out_unlock:
	अगर (info->shared_mode)
		mutex_unlock(&shared_mode_mutex);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक ab8500_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	u8 val;
	u8 val_normal;
	u8 val_idle;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	/* Need special handling क्रम shared mode */
	अगर (info->shared_mode) अणु
		अगर (info->shared_mode->lp_mode_req)
			वापस REGULATOR_MODE_IDLE;
		अन्यथा
			वापस REGULATOR_MODE_NORMAL;
	पूर्ण

	अगर (info->mode_mask) अणु
		/* Dedicated रेजिस्टर क्रम handling mode */
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(info->dev,
		info->mode_bank, info->mode_reg, &val);
		val = val & info->mode_mask;

		val_normal = info->mode_val_normal;
		val_idle = info->mode_val_idle;
	पूर्ण अन्यथा अणु
		/* Mode रेजिस्टर same as enable रेजिस्टर */
		val = info->update_val;
		val_normal = info->update_val_normal;
		val_idle = info->update_val_idle;
	पूर्ण

	अगर (val == val_normal)
		ret = REGULATOR_MODE_NORMAL;
	अन्यथा अगर (val == val_idle)
		ret = REGULATOR_MODE_IDLE;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_regulator_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret, voltage_shअगरt;
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	voltage_shअगरt = ffs(info->voltage_mask) - 1;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(info->dev,
			info->voltage_bank, info->voltage_reg, &regval);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"couldn't read voltage reg for regulator\n");
		वापस ret;
	पूर्ण

	dev_vdbg(rdev_get_dev(rdev),
		"%s-get_voltage (bank, reg, mask, shift, value): "
		"0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n",
		info->desc.name, info->voltage_bank,
		info->voltage_reg, info->voltage_mask,
		voltage_shअगरt, regval);

	वापस (regval & info->voltage_mask) >> voltage_shअगरt;
पूर्ण

अटल पूर्णांक ab8500_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
					    अचिन्हित selector)
अणु
	पूर्णांक ret, voltage_shअगरt;
	काष्ठा ab8500_regulator_info *info = rdev_get_drvdata(rdev);
	u8 regval;

	अगर (info == शून्य) अणु
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		वापस -EINVAL;
	पूर्ण

	voltage_shअगरt = ffs(info->voltage_mask) - 1;

	/* set the रेजिस्टरs क्रम the request */
	regval = (u8)selector << voltage_shअगरt;
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(info->dev,
			info->voltage_bank, info->voltage_reg,
			info->voltage_mask, regval);
	अगर (ret < 0)
		dev_err(rdev_get_dev(rdev),
		"couldn't set voltage reg for regulator\n");

	dev_vdbg(rdev_get_dev(rdev),
		"%s-set_voltage (bank, reg, mask, value): 0x%x, 0x%x, 0x%x,"
		" 0x%x\n",
		info->desc.name, info->voltage_bank, info->voltage_reg,
		info->voltage_mask, regval);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops ab8500_regulator_volt_mode_ops = अणु
	.enable			= ab8500_regulator_enable,
	.disable		= ab8500_regulator_disable,
	.is_enabled		= ab8500_regulator_is_enabled,
	.get_optimum_mode	= ab8500_regulator_get_optimum_mode,
	.set_mode		= ab8500_regulator_set_mode,
	.get_mode		= ab8500_regulator_get_mode,
	.get_voltage_sel 	= ab8500_regulator_get_voltage_sel,
	.set_voltage_sel	= ab8500_regulator_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops ab8500_regulator_volt_ops = अणु
	.enable		= ab8500_regulator_enable,
	.disable	= ab8500_regulator_disable,
	.is_enabled	= ab8500_regulator_is_enabled,
	.get_voltage_sel = ab8500_regulator_get_voltage_sel,
	.set_voltage_sel = ab8500_regulator_set_voltage_sel,
	.list_voltage	= regulator_list_voltage_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops ab8500_regulator_mode_ops = अणु
	.enable			= ab8500_regulator_enable,
	.disable		= ab8500_regulator_disable,
	.is_enabled		= ab8500_regulator_is_enabled,
	.get_optimum_mode	= ab8500_regulator_get_optimum_mode,
	.set_mode		= ab8500_regulator_set_mode,
	.get_mode		= ab8500_regulator_get_mode,
	.list_voltage		= regulator_list_voltage_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops ab8500_regulator_ops = अणु
	.enable			= ab8500_regulator_enable,
	.disable		= ab8500_regulator_disable,
	.is_enabled		= ab8500_regulator_is_enabled,
	.list_voltage		= regulator_list_voltage_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops ab8500_regulator_anamic_mode_ops = अणु
	.enable		= ab8500_regulator_enable,
	.disable	= ab8500_regulator_disable,
	.is_enabled	= ab8500_regulator_is_enabled,
	.set_mode	= ab8500_regulator_set_mode,
	.get_mode	= ab8500_regulator_get_mode,
	.list_voltage	= regulator_list_voltage_table,
पूर्ण;

/* AB8500 regulator inक्रमmation */
अटल काष्ठा ab8500_regulator_info
		ab8500_regulator_info[AB8500_NUM_REGULATORS] = अणु
	/*
	 * Variable Voltage Regulators
	 *   name, min mV, max mV,
	 *   update bank, reg, mask, enable val
	 *   volt bank, reg, mask
	 */
	[AB8500_LDO_AUX1] = अणु
		.desc = अणु
			.name		= "LDO-AUX1",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_AUX1,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vauxn_voltages),
			.volt_table	= lकरो_vauxn_voltages,
			.enable_समय	= 200,
			.supply_name    = "vin",
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x04,
		.update_reg		= 0x09,
		.update_mask		= 0x03,
		.update_val		= 0x01,
		.update_val_idle	= 0x03,
		.update_val_normal	= 0x01,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x1f,
		.voltage_mask		= 0x0f,
	पूर्ण,
	[AB8500_LDO_AUX2] = अणु
		.desc = अणु
			.name		= "LDO-AUX2",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_AUX2,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vauxn_voltages),
			.volt_table	= lकरो_vauxn_voltages,
			.enable_समय	= 200,
			.supply_name    = "vin",
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x04,
		.update_reg		= 0x09,
		.update_mask		= 0x0c,
		.update_val		= 0x04,
		.update_val_idle	= 0x0c,
		.update_val_normal	= 0x04,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x20,
		.voltage_mask		= 0x0f,
	पूर्ण,
	[AB8500_LDO_AUX3] = अणु
		.desc = अणु
			.name		= "LDO-AUX3",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_AUX3,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vaux3_voltages),
			.volt_table	= lकरो_vaux3_voltages,
			.enable_समय	= 450,
			.supply_name    = "vin",
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x04,
		.update_reg		= 0x0a,
		.update_mask		= 0x03,
		.update_val		= 0x01,
		.update_val_idle	= 0x03,
		.update_val_normal	= 0x01,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x21,
		.voltage_mask		= 0x07,
	पूर्ण,
	[AB8500_LDO_INTCORE] = अणु
		.desc = अणु
			.name		= "LDO-INTCORE",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_INTCORE,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vपूर्णांकcore_voltages),
			.volt_table	= lकरो_vपूर्णांकcore_voltages,
			.enable_समय	= 750,
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x03,
		.update_reg		= 0x80,
		.update_mask		= 0x44,
		.update_val		= 0x44,
		.update_val_idle	= 0x44,
		.update_val_normal	= 0x04,
		.voltage_bank		= 0x03,
		.voltage_reg		= 0x80,
		.voltage_mask		= 0x38,
	पूर्ण,

	/*
	 * Fixed Voltage Regulators
	 *   name, fixed mV,
	 *   update bank, reg, mask, enable val
	 */
	[AB8500_LDO_TVOUT] = अणु
		.desc = अणु
			.name		= "LDO-TVOUT",
			.ops		= &ab8500_regulator_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_TVOUT,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.volt_table	= fixed_2000000_voltage,
			.enable_समय	= 500,
		पूर्ण,
		.load_lp_uA		= 1000,
		.update_bank		= 0x03,
		.update_reg		= 0x80,
		.update_mask		= 0x82,
		.update_val		= 0x02,
		.update_val_idle	= 0x82,
		.update_val_normal	= 0x02,
	पूर्ण,
	[AB8500_LDO_AUDIO] = अणु
		.desc = अणु
			.name		= "LDO-AUDIO",
			.ops		= &ab8500_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_AUDIO,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.enable_समय	= 140,
			.volt_table	= fixed_2000000_voltage,
		पूर्ण,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x02,
		.update_val		= 0x02,
	पूर्ण,
	[AB8500_LDO_ANAMIC1] = अणु
		.desc = अणु
			.name		= "LDO-ANAMIC1",
			.ops		= &ab8500_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_ANAMIC1,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.enable_समय	= 500,
			.volt_table	= fixed_2050000_voltage,
		पूर्ण,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x08,
		.update_val		= 0x08,
	पूर्ण,
	[AB8500_LDO_ANAMIC2] = अणु
		.desc = अणु
			.name		= "LDO-ANAMIC2",
			.ops		= &ab8500_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_ANAMIC2,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.enable_समय	= 500,
			.volt_table	= fixed_2050000_voltage,
		पूर्ण,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x10,
		.update_val		= 0x10,
	पूर्ण,
	[AB8500_LDO_DMIC] = अणु
		.desc = अणु
			.name		= "LDO-DMIC",
			.ops		= &ab8500_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_DMIC,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.enable_समय	= 420,
			.volt_table	= fixed_1800000_voltage,
		पूर्ण,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x04,
		.update_val		= 0x04,
	पूर्ण,

	/*
	 * Regulators with fixed voltage and normal/idle modes
	 */
	[AB8500_LDO_ANA] = अणु
		.desc = अणु
			.name		= "LDO-ANA",
			.ops		= &ab8500_regulator_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8500_LDO_ANA,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.enable_समय	= 140,
			.volt_table	= fixed_1200000_voltage,
		पूर्ण,
		.load_lp_uA		= 1000,
		.update_bank		= 0x04,
		.update_reg		= 0x06,
		.update_mask		= 0x0c,
		.update_val		= 0x04,
		.update_val_idle	= 0x0c,
		.update_val_normal	= 0x04,
	पूर्ण,
पूर्ण;

/* AB8505 regulator inक्रमmation */
अटल काष्ठा ab8500_regulator_info
		ab8505_regulator_info[AB8505_NUM_REGULATORS] = अणु
	/*
	 * Variable Voltage Regulators
	 *   name, min mV, max mV,
	 *   update bank, reg, mask, enable val
	 *   volt bank, reg, mask
	 */
	[AB8505_LDO_AUX1] = अणु
		.desc = अणु
			.name		= "LDO-AUX1",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX1,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vauxn_voltages),
			.volt_table	= lकरो_vauxn_voltages,
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x04,
		.update_reg		= 0x09,
		.update_mask		= 0x03,
		.update_val		= 0x01,
		.update_val_idle	= 0x03,
		.update_val_normal	= 0x01,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x1f,
		.voltage_mask		= 0x0f,
	पूर्ण,
	[AB8505_LDO_AUX2] = अणु
		.desc = अणु
			.name		= "LDO-AUX2",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX2,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vauxn_voltages),
			.volt_table	= lकरो_vauxn_voltages,
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x04,
		.update_reg		= 0x09,
		.update_mask		= 0x0c,
		.update_val		= 0x04,
		.update_val_idle	= 0x0c,
		.update_val_normal	= 0x04,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x20,
		.voltage_mask		= 0x0f,
	पूर्ण,
	[AB8505_LDO_AUX3] = अणु
		.desc = अणु
			.name		= "LDO-AUX3",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX3,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vaux3_voltages),
			.volt_table	= lकरो_vaux3_voltages,
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x04,
		.update_reg		= 0x0a,
		.update_mask		= 0x03,
		.update_val		= 0x01,
		.update_val_idle	= 0x03,
		.update_val_normal	= 0x01,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x21,
		.voltage_mask		= 0x07,
	पूर्ण,
	[AB8505_LDO_AUX4] = अणु
		.desc = अणु
			.name		= "LDO-AUX4",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX4,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vauxn_voltages),
			.volt_table	= lकरो_vauxn_voltages,
		पूर्ण,
		.load_lp_uA		= 5000,
		/* values क्रम Vaux4Regu रेजिस्टर */
		.update_bank		= 0x04,
		.update_reg		= 0x2e,
		.update_mask		= 0x03,
		.update_val		= 0x01,
		.update_val_idle	= 0x03,
		.update_val_normal	= 0x01,
		/* values क्रम Vaux4SEL रेजिस्टर */
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x2f,
		.voltage_mask		= 0x0f,
	पूर्ण,
	[AB8505_LDO_AUX5] = अणु
		.desc = अणु
			.name		= "LDO-AUX5",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX5,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vaux56_voltages),
			.volt_table	= lकरो_vaux56_voltages,
		पूर्ण,
		.load_lp_uA		= 2000,
		/* values क्रम CtrlVaux5 रेजिस्टर */
		.update_bank		= 0x01,
		.update_reg		= 0x55,
		.update_mask		= 0x18,
		.update_val		= 0x10,
		.update_val_idle	= 0x18,
		.update_val_normal	= 0x10,
		.voltage_bank		= 0x01,
		.voltage_reg		= 0x55,
		.voltage_mask		= 0x07,
	पूर्ण,
	[AB8505_LDO_AUX6] = अणु
		.desc = अणु
			.name		= "LDO-AUX6",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX6,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vaux56_voltages),
			.volt_table	= lकरो_vaux56_voltages,
		पूर्ण,
		.load_lp_uA		= 2000,
		/* values क्रम CtrlVaux6 रेजिस्टर */
		.update_bank		= 0x01,
		.update_reg		= 0x56,
		.update_mask		= 0x18,
		.update_val		= 0x10,
		.update_val_idle	= 0x18,
		.update_val_normal	= 0x10,
		.voltage_bank		= 0x01,
		.voltage_reg		= 0x56,
		.voltage_mask		= 0x07,
	पूर्ण,
	[AB8505_LDO_INTCORE] = अणु
		.desc = अणु
			.name		= "LDO-INTCORE",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_INTCORE,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vपूर्णांकcore_voltages),
			.volt_table	= lकरो_vपूर्णांकcore_voltages,
		पूर्ण,
		.load_lp_uA		= 5000,
		.update_bank		= 0x03,
		.update_reg		= 0x80,
		.update_mask		= 0x44,
		.update_val		= 0x04,
		.update_val_idle	= 0x44,
		.update_val_normal	= 0x04,
		.voltage_bank		= 0x03,
		.voltage_reg		= 0x80,
		.voltage_mask		= 0x38,
	पूर्ण,

	/*
	 * Fixed Voltage Regulators
	 *   name, fixed mV,
	 *   update bank, reg, mask, enable val
	 */
	[AB8505_LDO_ADC] = अणु
		.desc = अणु
			.name		= "LDO-ADC",
			.ops		= &ab8500_regulator_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_ADC,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.volt_table	= fixed_2000000_voltage,
			.enable_समय	= 10000,
		पूर्ण,
		.load_lp_uA		= 1000,
		.update_bank		= 0x03,
		.update_reg		= 0x80,
		.update_mask		= 0x82,
		.update_val		= 0x02,
		.update_val_idle	= 0x82,
		.update_val_normal	= 0x02,
	पूर्ण,
	[AB8505_LDO_AUDIO] = अणु
		.desc = अणु
			.name		= "LDO-AUDIO",
			.ops		= &ab8500_regulator_volt_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUDIO,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vaudio_voltages),
			.volt_table	= lकरो_vaudio_voltages,
		पूर्ण,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x02,
		.update_val		= 0x02,
		.voltage_bank		= 0x01,
		.voltage_reg		= 0x57,
		.voltage_mask		= 0x70,
	पूर्ण,
	[AB8505_LDO_ANAMIC1] = अणु
		.desc = अणु
			.name		= "LDO-ANAMIC1",
			.ops		= &ab8500_regulator_anamic_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_ANAMIC1,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.volt_table	= fixed_2050000_voltage,
		पूर्ण,
		.shared_mode		= &lकरो_anamic1_shared,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x08,
		.update_val		= 0x08,
		.mode_bank		= 0x01,
		.mode_reg		= 0x54,
		.mode_mask		= 0x04,
		.mode_val_idle		= 0x04,
		.mode_val_normal	= 0x00,
	पूर्ण,
	[AB8505_LDO_ANAMIC2] = अणु
		.desc = अणु
			.name		= "LDO-ANAMIC2",
			.ops		= &ab8500_regulator_anamic_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_ANAMIC2,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.volt_table	= fixed_2050000_voltage,
		पूर्ण,
		.shared_mode		= &lकरो_anamic2_shared,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x10,
		.update_val		= 0x10,
		.mode_bank		= 0x01,
		.mode_reg		= 0x54,
		.mode_mask		= 0x04,
		.mode_val_idle		= 0x04,
		.mode_val_normal	= 0x00,
	पूर्ण,
	[AB8505_LDO_AUX8] = अणु
		.desc = अणु
			.name		= "LDO-AUX8",
			.ops		= &ab8500_regulator_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_AUX8,
			.owner		= THIS_MODULE,
			.n_voltages	= 1,
			.volt_table	= fixed_1800000_voltage,
		पूर्ण,
		.update_bank		= 0x03,
		.update_reg		= 0x83,
		.update_mask		= 0x04,
		.update_val		= 0x04,
	पूर्ण,
	/*
	 * Regulators with fixed voltage and normal/idle modes
	 */
	[AB8505_LDO_ANA] = अणु
		.desc = अणु
			.name		= "LDO-ANA",
			.ops		= &ab8500_regulator_volt_mode_ops,
			.type		= REGULATOR_VOLTAGE,
			.id		= AB8505_LDO_ANA,
			.owner		= THIS_MODULE,
			.n_voltages	= ARRAY_SIZE(lकरो_vana_voltages),
			.volt_table	= lकरो_vana_voltages,
		पूर्ण,
		.load_lp_uA		= 1000,
		.update_bank		= 0x04,
		.update_reg		= 0x06,
		.update_mask		= 0x0c,
		.update_val		= 0x04,
		.update_val_idle	= 0x0c,
		.update_val_normal	= 0x04,
		.voltage_bank		= 0x04,
		.voltage_reg		= 0x29,
		.voltage_mask		= 0x7,
	पूर्ण,
पूर्ण;

अटल काष्ठा ab8500_shared_mode lकरो_anamic1_shared = अणु
	.shared_regulator = &ab8505_regulator_info[AB8505_LDO_ANAMIC2],
पूर्ण;

अटल काष्ठा ab8500_shared_mode lकरो_anamic2_shared = अणु
	.shared_regulator = &ab8505_regulator_info[AB8505_LDO_ANAMIC1],
पूर्ण;

काष्ठा ab8500_reg_init अणु
	u8 bank;
	u8 addr;
	u8 mask;
पूर्ण;

#घोषणा REG_INIT(_id, _bank, _addr, _mask)	\
	[_id] = अणु				\
		.bank = _bank,			\
		.addr = _addr,			\
		.mask = _mask,			\
	पूर्ण

/* AB8500 रेजिस्टर init */
अटल काष्ठा ab8500_reg_init ab8500_reg_init[] = अणु
	/*
	 * 0x30, VanaRequestCtrl
	 * 0xc0, VextSupply1RequestCtrl
	 */
	REG_INIT(AB8500_REGUREQUESTCTRL2,	0x03, 0x04, 0xf0),
	/*
	 * 0x03, VextSupply2RequestCtrl
	 * 0x0c, VextSupply3RequestCtrl
	 * 0x30, Vaux1RequestCtrl
	 * 0xc0, Vaux2RequestCtrl
	 */
	REG_INIT(AB8500_REGUREQUESTCTRL3,	0x03, 0x05, 0xff),
	/*
	 * 0x03, Vaux3RequestCtrl
	 * 0x04, SwHPReq
	 */
	REG_INIT(AB8500_REGUREQUESTCTRL4,	0x03, 0x06, 0x07),
	/*
	 * 0x08, VanaSysClkReq1HPValid
	 * 0x20, Vaux1SysClkReq1HPValid
	 * 0x40, Vaux2SysClkReq1HPValid
	 * 0x80, Vaux3SysClkReq1HPValid
	 */
	REG_INIT(AB8500_REGUSYSCLKREQ1HPVALID1,	0x03, 0x07, 0xe8),
	/*
	 * 0x10, VextSupply1SysClkReq1HPValid
	 * 0x20, VextSupply2SysClkReq1HPValid
	 * 0x40, VextSupply3SysClkReq1HPValid
	 */
	REG_INIT(AB8500_REGUSYSCLKREQ1HPVALID2,	0x03, 0x08, 0x70),
	/*
	 * 0x08, VanaHwHPReq1Valid
	 * 0x20, Vaux1HwHPReq1Valid
	 * 0x40, Vaux2HwHPReq1Valid
	 * 0x80, Vaux3HwHPReq1Valid
	 */
	REG_INIT(AB8500_REGUHWHPREQ1VALID1,	0x03, 0x09, 0xe8),
	/*
	 * 0x01, VextSupply1HwHPReq1Valid
	 * 0x02, VextSupply2HwHPReq1Valid
	 * 0x04, VextSupply3HwHPReq1Valid
	 */
	REG_INIT(AB8500_REGUHWHPREQ1VALID2,	0x03, 0x0a, 0x07),
	/*
	 * 0x08, VanaHwHPReq2Valid
	 * 0x20, Vaux1HwHPReq2Valid
	 * 0x40, Vaux2HwHPReq2Valid
	 * 0x80, Vaux3HwHPReq2Valid
	 */
	REG_INIT(AB8500_REGUHWHPREQ2VALID1,	0x03, 0x0b, 0xe8),
	/*
	 * 0x01, VextSupply1HwHPReq2Valid
	 * 0x02, VextSupply2HwHPReq2Valid
	 * 0x04, VextSupply3HwHPReq2Valid
	 */
	REG_INIT(AB8500_REGUHWHPREQ2VALID2,	0x03, 0x0c, 0x07),
	/*
	 * 0x20, VanaSwHPReqValid
	 * 0x80, Vaux1SwHPReqValid
	 */
	REG_INIT(AB8500_REGUSWHPREQVALID1,	0x03, 0x0d, 0xa0),
	/*
	 * 0x01, Vaux2SwHPReqValid
	 * 0x02, Vaux3SwHPReqValid
	 * 0x04, VextSupply1SwHPReqValid
	 * 0x08, VextSupply2SwHPReqValid
	 * 0x10, VextSupply3SwHPReqValid
	 */
	REG_INIT(AB8500_REGUSWHPREQVALID2,	0x03, 0x0e, 0x1f),
	/*
	 * 0x02, SysClkReq2Valid1
	 * 0x04, SysClkReq3Valid1
	 * 0x08, SysClkReq4Valid1
	 * 0x10, SysClkReq5Valid1
	 * 0x20, SysClkReq6Valid1
	 * 0x40, SysClkReq7Valid1
	 * 0x80, SysClkReq8Valid1
	 */
	REG_INIT(AB8500_REGUSYSCLKREQVALID1,	0x03, 0x0f, 0xfe),
	/*
	 * 0x02, SysClkReq2Valid2
	 * 0x04, SysClkReq3Valid2
	 * 0x08, SysClkReq4Valid2
	 * 0x10, SysClkReq5Valid2
	 * 0x20, SysClkReq6Valid2
	 * 0x40, SysClkReq7Valid2
	 * 0x80, SysClkReq8Valid2
	 */
	REG_INIT(AB8500_REGUSYSCLKREQVALID2,	0x03, 0x10, 0xfe),
	/*
	 * 0x02, VTVoutEna
	 * 0x04, Vपूर्णांकcore12Ena
	 * 0x38, Vपूर्णांकcore12Sel
	 * 0x40, Vपूर्णांकcore12LP
	 * 0x80, VTVoutLP
	 */
	REG_INIT(AB8500_REGUMISC1,		0x03, 0x80, 0xfe),
	/*
	 * 0x02, VaudioEna
	 * 0x04, VdmicEna
	 * 0x08, Vamic1Ena
	 * 0x10, Vamic2Ena
	 */
	REG_INIT(AB8500_VAUDIOSUPPLY,		0x03, 0x83, 0x1e),
	/*
	 * 0x01, Vamic1_dzout
	 * 0x02, Vamic2_dzout
	 */
	REG_INIT(AB8500_REGUCTRL1VAMIC,		0x03, 0x84, 0x03),
	/*
	 * 0x03, VpllRegu (NOTE! PRCMU रेजिस्टर bits)
	 * 0x0c, VanaRegu
	 */
	REG_INIT(AB8500_VPLLVANAREGU,		0x04, 0x06, 0x0f),
	/*
	 * 0x01, VrefDDREna
	 * 0x02, VrefDDRSleepMode
	 */
	REG_INIT(AB8500_VREFDDR,		0x04, 0x07, 0x03),
	/*
	 * 0x03, VextSupply1Regu
	 * 0x0c, VextSupply2Regu
	 * 0x30, VextSupply3Regu
	 * 0x40, ExtSupply2Bypass
	 * 0x80, ExtSupply3Bypass
	 */
	REG_INIT(AB8500_EXTSUPPLYREGU,		0x04, 0x08, 0xff),
	/*
	 * 0x03, Vaux1Regu
	 * 0x0c, Vaux2Regu
	 */
	REG_INIT(AB8500_VAUX12REGU,		0x04, 0x09, 0x0f),
	/*
	 * 0x03, Vaux3Regu
	 */
	REG_INIT(AB8500_VRF1VAUX3REGU,		0x04, 0x0a, 0x03),
	/*
	 * 0x0f, Vaux1Sel
	 */
	REG_INIT(AB8500_VAUX1SEL,		0x04, 0x1f, 0x0f),
	/*
	 * 0x0f, Vaux2Sel
	 */
	REG_INIT(AB8500_VAUX2SEL,		0x04, 0x20, 0x0f),
	/*
	 * 0x07, Vaux3Sel
	 */
	REG_INIT(AB8500_VRF1VAUX3SEL,		0x04, 0x21, 0x07),
	/*
	 * 0x01, VextSupply12LP
	 */
	REG_INIT(AB8500_REGUCTRL2SPARE,		0x04, 0x22, 0x01),
	/*
	 * 0x04, Vaux1Disch
	 * 0x08, Vaux2Disch
	 * 0x10, Vaux3Disch
	 * 0x20, Vपूर्णांकcore12Disch
	 * 0x40, VTVoutDisch
	 * 0x80, VaudioDisch
	 */
	REG_INIT(AB8500_REGUCTRLDISCH,		0x04, 0x43, 0xfc),
	/*
	 * 0x02, VanaDisch
	 * 0x04, VdmicPullDownEna
	 * 0x10, VdmicDisch
	 */
	REG_INIT(AB8500_REGUCTRLDISCH2,		0x04, 0x44, 0x16),
पूर्ण;

/* AB8505 रेजिस्टर init */
अटल काष्ठा ab8500_reg_init ab8505_reg_init[] = अणु
	/*
	 * 0x03, VarmRequestCtrl
	 * 0x0c, VsmpsCRequestCtrl
	 * 0x30, VsmpsARequestCtrl
	 * 0xc0, VsmpsBRequestCtrl
	 */
	REG_INIT(AB8505_REGUREQUESTCTRL1,	0x03, 0x03, 0xff),
	/*
	 * 0x03, VsafeRequestCtrl
	 * 0x0c, VpllRequestCtrl
	 * 0x30, VanaRequestCtrl
	 */
	REG_INIT(AB8505_REGUREQUESTCTRL2,	0x03, 0x04, 0x3f),
	/*
	 * 0x30, Vaux1RequestCtrl
	 * 0xc0, Vaux2RequestCtrl
	 */
	REG_INIT(AB8505_REGUREQUESTCTRL3,	0x03, 0x05, 0xf0),
	/*
	 * 0x03, Vaux3RequestCtrl
	 * 0x04, SwHPReq
	 */
	REG_INIT(AB8505_REGUREQUESTCTRL4,	0x03, 0x06, 0x07),
	/*
	 * 0x01, VsmpsASysClkReq1HPValid
	 * 0x02, VsmpsBSysClkReq1HPValid
	 * 0x04, VsafeSysClkReq1HPValid
	 * 0x08, VanaSysClkReq1HPValid
	 * 0x10, VpllSysClkReq1HPValid
	 * 0x20, Vaux1SysClkReq1HPValid
	 * 0x40, Vaux2SysClkReq1HPValid
	 * 0x80, Vaux3SysClkReq1HPValid
	 */
	REG_INIT(AB8505_REGUSYSCLKREQ1HPVALID1,	0x03, 0x07, 0xff),
	/*
	 * 0x01, VsmpsCSysClkReq1HPValid
	 * 0x02, VarmSysClkReq1HPValid
	 * 0x04, VbbSysClkReq1HPValid
	 * 0x08, VsmpsMSysClkReq1HPValid
	 */
	REG_INIT(AB8505_REGUSYSCLKREQ1HPVALID2,	0x03, 0x08, 0x0f),
	/*
	 * 0x01, VsmpsAHwHPReq1Valid
	 * 0x02, VsmpsBHwHPReq1Valid
	 * 0x04, VsafeHwHPReq1Valid
	 * 0x08, VanaHwHPReq1Valid
	 * 0x10, VpllHwHPReq1Valid
	 * 0x20, Vaux1HwHPReq1Valid
	 * 0x40, Vaux2HwHPReq1Valid
	 * 0x80, Vaux3HwHPReq1Valid
	 */
	REG_INIT(AB8505_REGUHWHPREQ1VALID1,	0x03, 0x09, 0xff),
	/*
	 * 0x08, VsmpsMHwHPReq1Valid
	 */
	REG_INIT(AB8505_REGUHWHPREQ1VALID2,	0x03, 0x0a, 0x08),
	/*
	 * 0x01, VsmpsAHwHPReq2Valid
	 * 0x02, VsmpsBHwHPReq2Valid
	 * 0x04, VsafeHwHPReq2Valid
	 * 0x08, VanaHwHPReq2Valid
	 * 0x10, VpllHwHPReq2Valid
	 * 0x20, Vaux1HwHPReq2Valid
	 * 0x40, Vaux2HwHPReq2Valid
	 * 0x80, Vaux3HwHPReq2Valid
	 */
	REG_INIT(AB8505_REGUHWHPREQ2VALID1,	0x03, 0x0b, 0xff),
	/*
	 * 0x08, VsmpsMHwHPReq2Valid
	 */
	REG_INIT(AB8505_REGUHWHPREQ2VALID2,	0x03, 0x0c, 0x08),
	/*
	 * 0x01, VsmpsCSwHPReqValid
	 * 0x02, VarmSwHPReqValid
	 * 0x04, VsmpsASwHPReqValid
	 * 0x08, VsmpsBSwHPReqValid
	 * 0x10, VsafeSwHPReqValid
	 * 0x20, VanaSwHPReqValid
	 * 0x40, VpllSwHPReqValid
	 * 0x80, Vaux1SwHPReqValid
	 */
	REG_INIT(AB8505_REGUSWHPREQVALID1,	0x03, 0x0d, 0xff),
	/*
	 * 0x01, Vaux2SwHPReqValid
	 * 0x02, Vaux3SwHPReqValid
	 * 0x20, VsmpsMSwHPReqValid
	 */
	REG_INIT(AB8505_REGUSWHPREQVALID2,	0x03, 0x0e, 0x23),
	/*
	 * 0x02, SysClkReq2Valid1
	 * 0x04, SysClkReq3Valid1
	 * 0x08, SysClkReq4Valid1
	 */
	REG_INIT(AB8505_REGUSYSCLKREQVALID1,	0x03, 0x0f, 0x0e),
	/*
	 * 0x02, SysClkReq2Valid2
	 * 0x04, SysClkReq3Valid2
	 * 0x08, SysClkReq4Valid2
	 */
	REG_INIT(AB8505_REGUSYSCLKREQVALID2,	0x03, 0x10, 0x0e),
	/*
	 * 0x01, Vaux4SwHPReqValid
	 * 0x02, Vaux4HwHPReq2Valid
	 * 0x04, Vaux4HwHPReq1Valid
	 * 0x08, Vaux4SysClkReq1HPValid
	 */
	REG_INIT(AB8505_REGUVAUX4REQVALID,	0x03, 0x11, 0x0f),
	/*
	 * 0x02, VadcEna
	 * 0x04, Vपूर्णांकCore12Ena
	 * 0x38, Vपूर्णांकCore12Sel
	 * 0x40, Vपूर्णांकCore12LP
	 * 0x80, VadcLP
	 */
	REG_INIT(AB8505_REGUMISC1,		0x03, 0x80, 0xfe),
	/*
	 * 0x02, VaudioEna
	 * 0x04, VdmicEna
	 * 0x08, Vamic1Ena
	 * 0x10, Vamic2Ena
	 */
	REG_INIT(AB8505_VAUDIOSUPPLY,		0x03, 0x83, 0x1e),
	/*
	 * 0x01, Vamic1_dzout
	 * 0x02, Vamic2_dzout
	 */
	REG_INIT(AB8505_REGUCTRL1VAMIC,		0x03, 0x84, 0x03),
	/*
	 * 0x03, VsmpsARegu
	 * 0x0c, VsmpsASelCtrl
	 * 0x10, VsmpsAAutoMode
	 * 0x20, VsmpsAPWMMode
	 */
	REG_INIT(AB8505_VSMPSAREGU,		0x04, 0x03, 0x3f),
	/*
	 * 0x03, VsmpsBRegu
	 * 0x0c, VsmpsBSelCtrl
	 * 0x10, VsmpsBAutoMode
	 * 0x20, VsmpsBPWMMode
	 */
	REG_INIT(AB8505_VSMPSBREGU,		0x04, 0x04, 0x3f),
	/*
	 * 0x03, VsafeRegu
	 * 0x0c, VsafeSelCtrl
	 * 0x10, VsafeAutoMode
	 * 0x20, VsafePWMMode
	 */
	REG_INIT(AB8505_VSAFEREGU,		0x04, 0x05, 0x3f),
	/*
	 * 0x03, VpllRegu (NOTE! PRCMU रेजिस्टर bits)
	 * 0x0c, VanaRegu
	 */
	REG_INIT(AB8505_VPLLVANAREGU,		0x04, 0x06, 0x0f),
	/*
	 * 0x03, VextSupply1Regu
	 * 0x0c, VextSupply2Regu
	 * 0x30, VextSupply3Regu
	 * 0x40, ExtSupply2Bypass
	 * 0x80, ExtSupply3Bypass
	 */
	REG_INIT(AB8505_EXTSUPPLYREGU,		0x04, 0x08, 0xff),
	/*
	 * 0x03, Vaux1Regu
	 * 0x0c, Vaux2Regu
	 */
	REG_INIT(AB8505_VAUX12REGU,		0x04, 0x09, 0x0f),
	/*
	 * 0x0f, Vaux3Regu
	 */
	REG_INIT(AB8505_VRF1VAUX3REGU,		0x04, 0x0a, 0x0f),
	/*
	 * 0x3f, VsmpsASel1
	 */
	REG_INIT(AB8505_VSMPSASEL1,		0x04, 0x13, 0x3f),
	/*
	 * 0x3f, VsmpsASel2
	 */
	REG_INIT(AB8505_VSMPSASEL2,		0x04, 0x14, 0x3f),
	/*
	 * 0x3f, VsmpsASel3
	 */
	REG_INIT(AB8505_VSMPSASEL3,		0x04, 0x15, 0x3f),
	/*
	 * 0x3f, VsmpsBSel1
	 */
	REG_INIT(AB8505_VSMPSBSEL1,		0x04, 0x17, 0x3f),
	/*
	 * 0x3f, VsmpsBSel2
	 */
	REG_INIT(AB8505_VSMPSBSEL2,		0x04, 0x18, 0x3f),
	/*
	 * 0x3f, VsmpsBSel3
	 */
	REG_INIT(AB8505_VSMPSBSEL3,		0x04, 0x19, 0x3f),
	/*
	 * 0x7f, VsafeSel1
	 */
	REG_INIT(AB8505_VSAFESEL1,		0x04, 0x1b, 0x7f),
	/*
	 * 0x3f, VsafeSel2
	 */
	REG_INIT(AB8505_VSAFESEL2,		0x04, 0x1c, 0x7f),
	/*
	 * 0x3f, VsafeSel3
	 */
	REG_INIT(AB8505_VSAFESEL3,		0x04, 0x1d, 0x7f),
	/*
	 * 0x0f, Vaux1Sel
	 */
	REG_INIT(AB8505_VAUX1SEL,		0x04, 0x1f, 0x0f),
	/*
	 * 0x0f, Vaux2Sel
	 */
	REG_INIT(AB8505_VAUX2SEL,		0x04, 0x20, 0x0f),
	/*
	 * 0x07, Vaux3Sel
	 * 0x30, VRF1Sel
	 */
	REG_INIT(AB8505_VRF1VAUX3SEL,		0x04, 0x21, 0x37),
	/*
	 * 0x03, Vaux4RequestCtrl
	 */
	REG_INIT(AB8505_VAUX4REQCTRL,		0x04, 0x2d, 0x03),
	/*
	 * 0x03, Vaux4Regu
	 */
	REG_INIT(AB8505_VAUX4REGU,		0x04, 0x2e, 0x03),
	/*
	 * 0x0f, Vaux4Sel
	 */
	REG_INIT(AB8505_VAUX4SEL,		0x04, 0x2f, 0x0f),
	/*
	 * 0x04, Vaux1Disch
	 * 0x08, Vaux2Disch
	 * 0x10, Vaux3Disch
	 * 0x20, Vपूर्णांकcore12Disch
	 * 0x40, VTVoutDisch
	 * 0x80, VaudioDisch
	 */
	REG_INIT(AB8505_REGUCTRLDISCH,		0x04, 0x43, 0xfc),
	/*
	 * 0x02, VanaDisch
	 * 0x04, VdmicPullDownEna
	 * 0x10, VdmicDisch
	 */
	REG_INIT(AB8505_REGUCTRLDISCH2,		0x04, 0x44, 0x16),
	/*
	 * 0x01, Vaux4Disch
	 */
	REG_INIT(AB8505_REGUCTRLDISCH3,		0x04, 0x48, 0x01),
	/*
	 * 0x07, Vaux5Sel
	 * 0x08, Vaux5LP
	 * 0x10, Vaux5Ena
	 * 0x20, Vaux5Disch
	 * 0x40, Vaux5DisSfst
	 * 0x80, Vaux5DisPulld
	 */
	REG_INIT(AB8505_CTRLVAUX5,		0x01, 0x55, 0xff),
	/*
	 * 0x07, Vaux6Sel
	 * 0x08, Vaux6LP
	 * 0x10, Vaux6Ena
	 * 0x80, Vaux6DisPulld
	 */
	REG_INIT(AB8505_CTRLVAUX6,		0x01, 0x56, 0x9f),
पूर्ण;

अटल काष्ठा of_regulator_match ab8500_regulator_match[] = अणु
	अणु .name	= "ab8500_ldo_aux1",    .driver_data = (व्योम *) AB8500_LDO_AUX1, पूर्ण,
	अणु .name	= "ab8500_ldo_aux2",    .driver_data = (व्योम *) AB8500_LDO_AUX2, पूर्ण,
	अणु .name	= "ab8500_ldo_aux3",    .driver_data = (व्योम *) AB8500_LDO_AUX3, पूर्ण,
	अणु .name	= "ab8500_ldo_intcore", .driver_data = (व्योम *) AB8500_LDO_INTCORE, पूर्ण,
	अणु .name	= "ab8500_ldo_tvout",   .driver_data = (व्योम *) AB8500_LDO_TVOUT, पूर्ण,
	अणु .name = "ab8500_ldo_audio",   .driver_data = (व्योम *) AB8500_LDO_AUDIO, पूर्ण,
	अणु .name	= "ab8500_ldo_anamic1", .driver_data = (व्योम *) AB8500_LDO_ANAMIC1, पूर्ण,
	अणु .name	= "ab8500_ldo_anamic2", .driver_data = (व्योम *) AB8500_LDO_ANAMIC2, पूर्ण,
	अणु .name	= "ab8500_ldo_dmic",    .driver_data = (व्योम *) AB8500_LDO_DMIC, पूर्ण,
	अणु .name	= "ab8500_ldo_ana",     .driver_data = (व्योम *) AB8500_LDO_ANA, पूर्ण,
पूर्ण;

अटल काष्ठा of_regulator_match ab8505_regulator_match[] = अणु
	अणु .name	= "ab8500_ldo_aux1",    .driver_data = (व्योम *) AB8505_LDO_AUX1, पूर्ण,
	अणु .name	= "ab8500_ldo_aux2",    .driver_data = (व्योम *) AB8505_LDO_AUX2, पूर्ण,
	अणु .name	= "ab8500_ldo_aux3",    .driver_data = (व्योम *) AB8505_LDO_AUX3, पूर्ण,
	अणु .name	= "ab8500_ldo_aux4",    .driver_data = (व्योम *) AB8505_LDO_AUX4, पूर्ण,
	अणु .name	= "ab8500_ldo_aux5",    .driver_data = (व्योम *) AB8505_LDO_AUX5, पूर्ण,
	अणु .name	= "ab8500_ldo_aux6",    .driver_data = (व्योम *) AB8505_LDO_AUX6, पूर्ण,
	अणु .name	= "ab8500_ldo_intcore", .driver_data = (व्योम *) AB8505_LDO_INTCORE, पूर्ण,
	अणु .name	= "ab8500_ldo_adc",	.driver_data = (व्योम *) AB8505_LDO_ADC, पूर्ण,
	अणु .name = "ab8500_ldo_audio",   .driver_data = (व्योम *) AB8505_LDO_AUDIO, पूर्ण,
	अणु .name	= "ab8500_ldo_anamic1", .driver_data = (व्योम *) AB8505_LDO_ANAMIC1, पूर्ण,
	अणु .name	= "ab8500_ldo_anamic2", .driver_data = (व्योम *) AB8505_LDO_ANAMIC2, पूर्ण,
	अणु .name	= "ab8500_ldo_aux8",    .driver_data = (व्योम *) AB8505_LDO_AUX8, पूर्ण,
	अणु .name	= "ab8500_ldo_ana",     .driver_data = (व्योम *) AB8505_LDO_ANA, पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	काष्ठा ab8500_regulator_info *info;
	पूर्णांक info_size;
	काष्ठा ab8500_reg_init *init;
	पूर्णांक init_size;
	काष्ठा of_regulator_match *match;
	पूर्णांक match_size;
पूर्ण abx500_regulator;

अटल व्योम abx500_get_regulator_info(काष्ठा ab8500 *ab8500)
अणु
	अगर (is_ab8505(ab8500)) अणु
		abx500_regulator.info = ab8505_regulator_info;
		abx500_regulator.info_size = ARRAY_SIZE(ab8505_regulator_info);
		abx500_regulator.init = ab8505_reg_init;
		abx500_regulator.init_size = AB8505_NUM_REGULATOR_REGISTERS;
		abx500_regulator.match = ab8505_regulator_match;
		abx500_regulator.match_size = ARRAY_SIZE(ab8505_regulator_match);
	पूर्ण अन्यथा अणु
		abx500_regulator.info = ab8500_regulator_info;
		abx500_regulator.info_size = ARRAY_SIZE(ab8500_regulator_info);
		abx500_regulator.init = ab8500_reg_init;
		abx500_regulator.init_size = AB8500_NUM_REGULATOR_REGISTERS;
		abx500_regulator.match = ab8500_regulator_match;
		abx500_regulator.match_size = ARRAY_SIZE(ab8500_regulator_match);
	पूर्ण
पूर्ण

अटल पूर्णांक ab8500_regulator_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				     काष्ठा regulator_init_data *init_data,
				     पूर्णांक id, काष्ठा device_node *np)
अणु
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा ab8500_regulator_info *info = शून्य;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;

	/* assign per-regulator data */
	info = &abx500_regulator.info[id];
	info->dev = &pdev->dev;

	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.driver_data = info;
	config.of_node = np;

	/* fix क्रम hardware beक्रमe ab8500v2.0 */
	अगर (is_ab8500_1p1_or_earlier(ab8500)) अणु
		अगर (info->desc.id == AB8500_LDO_AUX3) अणु
			info->desc.n_voltages =
				ARRAY_SIZE(lकरो_vauxn_voltages);
			info->desc.volt_table = lकरो_vauxn_voltages;
			info->voltage_mask = 0xf;
		पूर्ण
	पूर्ण

	/* रेजिस्टर regulator with framework */
	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "failed to register regulator %s\n",
			info->desc.name);
		वापस PTR_ERR(rdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा of_regulator_match *match;
	पूर्णांक err, i;

	अगर (!ab8500) अणु
		dev_err(&pdev->dev, "null mfd parent\n");
		वापस -EINVAL;
	पूर्ण

	abx500_get_regulator_info(ab8500);

	err = of_regulator_match(&pdev->dev, np,
				 abx500_regulator.match,
				 abx500_regulator.match_size);
	अगर (err < 0) अणु
		dev_err(&pdev->dev,
			"Error parsing regulator init data: %d\n", err);
		वापस err;
	पूर्ण

	match = abx500_regulator.match;
	क्रम (i = 0; i < abx500_regulator.info_size; i++) अणु
		err = ab8500_regulator_रेजिस्टर(pdev, match[i].init_data, i,
						match[i].of_node);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ab8500_regulator_driver = अणु
	.probe = ab8500_regulator_probe,
	.driver         = अणु
		.name   = "ab8500-regulator",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ab8500_regulator_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&ab8500_regulator_driver);
	अगर (ret != 0)
		pr_err("Failed to register ab8500 regulator: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(ab8500_regulator_init);

अटल व्योम __निकास ab8500_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ab8500_regulator_driver);
पूर्ण
module_निकास(ab8500_regulator_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sundar Iyer <sundar.iyer@stericsson.com>");
MODULE_AUTHOR("Bengt Jonsson <bengt.g.jonsson@stericsson.com>");
MODULE_AUTHOR("Daniel Willerud <daniel.willerud@stericsson.com>");
MODULE_DESCRIPTION("Regulator Driver for ST-Ericsson AB8500 Mixed-Sig PMIC");
MODULE_ALIAS("platform:ab8500-regulator");
