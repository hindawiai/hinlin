<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// FAN53555 Fairchild Digitally Programmable TinyBuck Regulator Driver.
//
// Supported Part Numbers:
// FAN53555UC00X/01X/03X/04X/05X
//
// Copyright (c) 2012 Marvell Technology Ltd.
// Yunfan Zhang <yfzhang@marvell.com>

#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/of_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/fan53555.h>

/* Voltage setting */
#घोषणा FAN53555_VSEL0		0x00
#घोषणा FAN53555_VSEL1		0x01

#घोषणा TCS4525_VSEL0		0x11
#घोषणा TCS4525_VSEL1		0x10
#घोषणा TCS4525_TIME		0x13
#घोषणा TCS4525_COMMAND		0x14

/* Control रेजिस्टर */
#घोषणा FAN53555_CONTROL	0x02
/* IC Type */
#घोषणा FAN53555_ID1		0x03
/* IC mask version */
#घोषणा FAN53555_ID2		0x04
/* Monitor रेजिस्टर */
#घोषणा FAN53555_MONITOR	0x05

/* VSEL bit definitions */
#घोषणा VSEL_BUCK_EN	(1 << 7)
#घोषणा VSEL_MODE		(1 << 6)
/* Chip ID and Verison */
#घोषणा DIE_ID		0x0F	/* ID1 */
#घोषणा DIE_REV		0x0F	/* ID2 */
/* Control bit definitions */
#घोषणा CTL_OUTPUT_DISCHG	(1 << 7)
#घोषणा CTL_SLEW_MASK		(0x7 << 4)
#घोषणा CTL_SLEW_SHIFT		4
#घोषणा CTL_RESET			(1 << 2)
#घोषणा CTL_MODE_VSEL0_MODE	BIT(0)
#घोषणा CTL_MODE_VSEL1_MODE	BIT(1)

#घोषणा FAN53555_NVOLTAGES	64	/* Numbers of voltages */
#घोषणा FAN53526_NVOLTAGES	128

#घोषणा TCS_VSEL_NSEL_MASK	0x7f
#घोषणा TCS_VSEL0_MODE		(1 << 7)
#घोषणा TCS_VSEL1_MODE		(1 << 6)

#घोषणा TCS_SLEW_SHIFT		3
#घोषणा TCS_SLEW_MASK		(0x3 < 3)

क्रमागत fan53555_venकरोr अणु
	FAN53526_VENDOR_FAIRCHILD = 0,
	FAN53555_VENDOR_FAIRCHILD,
	FAN53555_VENDOR_SILERGY,
	FAN53555_VENDOR_TCS,
पूर्ण;

क्रमागत अणु
	FAN53526_CHIP_ID_01 = 1,
पूर्ण;

क्रमागत अणु
	FAN53526_CHIP_REV_08 = 8,
पूर्ण;

/* IC Type */
क्रमागत अणु
	FAN53555_CHIP_ID_00 = 0,
	FAN53555_CHIP_ID_01,
	FAN53555_CHIP_ID_02,
	FAN53555_CHIP_ID_03,
	FAN53555_CHIP_ID_04,
	FAN53555_CHIP_ID_05,
	FAN53555_CHIP_ID_08 = 8,
पूर्ण;

/* IC mask revision */
क्रमागत अणु
	FAN53555_CHIP_REV_00 = 0x3,
	FAN53555_CHIP_REV_13 = 0xf,
पूर्ण;

क्रमागत अणु
	SILERGY_SYR82X = 8,
	SILERGY_SYR83X = 9,
पूर्ण;

काष्ठा fan53555_device_info अणु
	क्रमागत fan53555_venकरोr venकरोr;
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_init_data *regulator;
	/* IC Type and Rev */
	पूर्णांक chip_id;
	पूर्णांक chip_rev;
	/* Voltage setting रेजिस्टर */
	अचिन्हित पूर्णांक vol_reg;
	अचिन्हित पूर्णांक sleep_reg;
	/* Voltage range and step(linear) */
	अचिन्हित पूर्णांक vsel_min;
	अचिन्हित पूर्णांक vsel_step;
	अचिन्हित पूर्णांक vsel_count;
	/* Mode */
	अचिन्हित पूर्णांक mode_reg;
	अचिन्हित पूर्णांक mode_mask;
	/* Sleep voltage cache */
	अचिन्हित पूर्णांक sleep_vol_cache;
	/* Slew rate */
	अचिन्हित पूर्णांक slew_reg;
	अचिन्हित पूर्णांक slew_mask;
	अचिन्हित पूर्णांक slew_shअगरt;
	अचिन्हित पूर्णांक slew_rate;
पूर्ण;

अटल पूर्णांक fan53555_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा fan53555_device_info *di = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (di->sleep_vol_cache == uV)
		वापस 0;
	ret = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_update_bits(rdev->regmap, di->sleep_reg,
				 di->desc.vsel_mask, ret);
	अगर (ret < 0)
		वापस ret;
	/* Cache the sleep voltage setting.
	 * Might not be the real voltage which is rounded */
	di->sleep_vol_cache = uV;

	वापस 0;
पूर्ण

अटल पूर्णांक fan53555_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fan53555_device_info *di = rdev_get_drvdata(rdev);

	वापस regmap_update_bits(rdev->regmap, di->sleep_reg,
				  VSEL_BUCK_EN, VSEL_BUCK_EN);
पूर्ण

अटल पूर्णांक fan53555_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fan53555_device_info *di = rdev_get_drvdata(rdev);

	वापस regmap_update_bits(rdev->regmap, di->sleep_reg,
				  VSEL_BUCK_EN, 0);
पूर्ण

अटल पूर्णांक fan53555_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा fan53555_device_info *di = rdev_get_drvdata(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		regmap_update_bits(rdev->regmap, di->mode_reg,
				   di->mode_mask, di->mode_mask);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		regmap_update_bits(rdev->regmap, di->vol_reg, di->mode_mask, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक fan53555_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fan53555_device_info *di = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(rdev->regmap, di->mode_reg, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val & di->mode_mask)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर पूर्णांक slew_rates[] = अणु
	64000,
	32000,
	16000,
	 8000,
	 4000,
	 2000,
	 1000,
	  500,
पूर्ण;

अटल स्थिर पूर्णांक tcs_slew_rates[] = अणु
	18700,
	 9300,
	 4600,
	 2300,
पूर्ण;

अटल पूर्णांक fan53555_set_ramp(काष्ठा regulator_dev *rdev, पूर्णांक ramp)
अणु
	काष्ठा fan53555_device_info *di = rdev_get_drvdata(rdev);
	पूर्णांक regval = -1, i;
	स्थिर पूर्णांक *slew_rate_t;
	पूर्णांक slew_rate_n;

	चयन (di->venकरोr) अणु
	हाल FAN53526_VENDOR_FAIRCHILD:
	हाल FAN53555_VENDOR_FAIRCHILD:
	हाल FAN53555_VENDOR_SILERGY:
		slew_rate_t = slew_rates;
		slew_rate_n = ARRAY_SIZE(slew_rates);
		अवरोध;
	हाल FAN53555_VENDOR_TCS:
		slew_rate_t = tcs_slew_rates;
		slew_rate_n = ARRAY_SIZE(tcs_slew_rates);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < slew_rate_n; i++) अणु
		अगर (ramp <= slew_rate_t[i])
			regval = i;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (regval < 0) अणु
		dev_err(di->dev, "unsupported ramp value %d\n", ramp);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, di->slew_reg,
				  di->slew_mask, regval << di->slew_shअगरt);
पूर्ण

अटल स्थिर काष्ठा regulator_ops fan53555_regulator_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.map_voltage = regulator_map_voltage_linear,
	.list_voltage = regulator_list_voltage_linear,
	.set_suspend_voltage = fan53555_set_suspend_voltage,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = fan53555_set_mode,
	.get_mode = fan53555_get_mode,
	.set_ramp_delay = fan53555_set_ramp,
	.set_suspend_enable = fan53555_set_suspend_enable,
	.set_suspend_disable = fan53555_set_suspend_disable,
पूर्ण;

अटल पूर्णांक fan53526_voltages_setup_fairchild(काष्ठा fan53555_device_info *di)
अणु
	/* Init voltage range and step */
	चयन (di->chip_id) अणु
	हाल FAN53526_CHIP_ID_01:
		चयन (di->chip_rev) अणु
		हाल FAN53526_CHIP_REV_08:
			di->vsel_min = 600000;
			di->vsel_step = 6250;
			अवरोध;
		शेष:
			dev_err(di->dev,
				"Chip ID %d with rev %d not supported!\n",
				di->chip_id, di->chip_rev);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(di->dev,
			"Chip ID %d not supported!\n", di->chip_id);
		वापस -EINVAL;
	पूर्ण

	di->vsel_count = FAN53526_NVOLTAGES;

	वापस 0;
पूर्ण

अटल पूर्णांक fan53555_voltages_setup_fairchild(काष्ठा fan53555_device_info *di)
अणु
	/* Init voltage range and step */
	चयन (di->chip_id) अणु
	हाल FAN53555_CHIP_ID_00:
		चयन (di->chip_rev) अणु
		हाल FAN53555_CHIP_REV_00:
			di->vsel_min = 600000;
			di->vsel_step = 10000;
			अवरोध;
		हाल FAN53555_CHIP_REV_13:
			di->vsel_min = 800000;
			di->vsel_step = 10000;
			अवरोध;
		शेष:
			dev_err(di->dev,
				"Chip ID %d with rev %d not supported!\n",
				di->chip_id, di->chip_rev);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल FAN53555_CHIP_ID_01:
	हाल FAN53555_CHIP_ID_03:
	हाल FAN53555_CHIP_ID_05:
	हाल FAN53555_CHIP_ID_08:
		di->vsel_min = 600000;
		di->vsel_step = 10000;
		अवरोध;
	हाल FAN53555_CHIP_ID_04:
		di->vsel_min = 603000;
		di->vsel_step = 12826;
		अवरोध;
	शेष:
		dev_err(di->dev,
			"Chip ID %d not supported!\n", di->chip_id);
		वापस -EINVAL;
	पूर्ण
	di->slew_reg = FAN53555_CONTROL;
	di->slew_mask = CTL_SLEW_MASK;
	di->slew_shअगरt = CTL_SLEW_SHIFT;
	di->vsel_count = FAN53555_NVOLTAGES;

	वापस 0;
पूर्ण

अटल पूर्णांक fan53555_voltages_setup_silergy(काष्ठा fan53555_device_info *di)
अणु
	/* Init voltage range and step */
	चयन (di->chip_id) अणु
	हाल SILERGY_SYR82X:
	हाल SILERGY_SYR83X:
		di->vsel_min = 712500;
		di->vsel_step = 12500;
		अवरोध;
	शेष:
		dev_err(di->dev,
			"Chip ID %d not supported!\n", di->chip_id);
		वापस -EINVAL;
	पूर्ण
	di->slew_reg = FAN53555_CONTROL;
	di->slew_reg = FAN53555_CONTROL;
	di->slew_mask = CTL_SLEW_MASK;
	di->slew_shअगरt = CTL_SLEW_SHIFT;
	di->vsel_count = FAN53555_NVOLTAGES;

	वापस 0;
पूर्ण

अटल पूर्णांक fan53555_voltages_setup_tcs(काष्ठा fan53555_device_info *di)
अणु
	di->slew_reg = TCS4525_TIME;
	di->slew_mask = TCS_SLEW_MASK;
	di->slew_shअगरt = TCS_SLEW_MASK;

	/* Init voltage range and step */
	di->vsel_min = 600000;
	di->vsel_step = 6250;
	di->vsel_count = FAN53526_NVOLTAGES;

	वापस 0;
पूर्ण

/* For 00,01,03,05 options:
 * VOUT = 0.60V + NSELx * 10mV, from 0.60 to 1.23V.
 * For 04 option:
 * VOUT = 0.603V + NSELx * 12.826mV, from 0.603 to 1.411V.
 * */
अटल पूर्णांक fan53555_device_setup(काष्ठा fan53555_device_info *di,
				काष्ठा fan53555_platक्रमm_data *pdata)
अणु
	पूर्णांक ret = 0;

	/* Setup voltage control रेजिस्टर */
	चयन (di->venकरोr) अणु
	हाल FAN53526_VENDOR_FAIRCHILD:
	हाल FAN53555_VENDOR_FAIRCHILD:
	हाल FAN53555_VENDOR_SILERGY:
		चयन (pdata->sleep_vsel_id) अणु
		हाल FAN53555_VSEL_ID_0:
			di->sleep_reg = FAN53555_VSEL0;
			di->vol_reg = FAN53555_VSEL1;
			अवरोध;
		हाल FAN53555_VSEL_ID_1:
			di->sleep_reg = FAN53555_VSEL1;
			di->vol_reg = FAN53555_VSEL0;
			अवरोध;
		शेष:
			dev_err(di->dev, "Invalid VSEL ID!\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल FAN53555_VENDOR_TCS:
		चयन (pdata->sleep_vsel_id) अणु
		हाल FAN53555_VSEL_ID_0:
			di->sleep_reg = TCS4525_VSEL0;
			di->vol_reg = TCS4525_VSEL1;
			अवरोध;
		हाल FAN53555_VSEL_ID_1:
			di->sleep_reg = TCS4525_VSEL1;
			di->vol_reg = TCS4525_VSEL0;
			अवरोध;
		शेष:
			dev_err(di->dev, "Invalid VSEL ID!\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(di->dev, "vendor %d not supported!\n", di->venकरोr);
		वापस -EINVAL;
	पूर्ण

	/* Setup mode control रेजिस्टर */
	चयन (di->venकरोr) अणु
	हाल FAN53526_VENDOR_FAIRCHILD:
		di->mode_reg = FAN53555_CONTROL;

		चयन (pdata->sleep_vsel_id) अणु
		हाल FAN53555_VSEL_ID_0:
			di->mode_mask = CTL_MODE_VSEL1_MODE;
			अवरोध;
		हाल FAN53555_VSEL_ID_1:
			di->mode_mask = CTL_MODE_VSEL0_MODE;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FAN53555_VENDOR_FAIRCHILD:
	हाल FAN53555_VENDOR_SILERGY:
		di->mode_reg = di->vol_reg;
		di->mode_mask = VSEL_MODE;
		अवरोध;
	हाल FAN53555_VENDOR_TCS:
		di->mode_reg = TCS4525_COMMAND;

		चयन (pdata->sleep_vsel_id) अणु
		हाल FAN53555_VSEL_ID_0:
			di->mode_mask = TCS_VSEL1_MODE;
			अवरोध;
		हाल FAN53555_VSEL_ID_1:
			di->mode_mask = TCS_VSEL0_MODE;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(di->dev, "vendor %d not supported!\n", di->venकरोr);
		वापस -EINVAL;
	पूर्ण

	/* Setup voltage range */
	चयन (di->venकरोr) अणु
	हाल FAN53526_VENDOR_FAIRCHILD:
		ret = fan53526_voltages_setup_fairchild(di);
		अवरोध;
	हाल FAN53555_VENDOR_FAIRCHILD:
		ret = fan53555_voltages_setup_fairchild(di);
		अवरोध;
	हाल FAN53555_VENDOR_SILERGY:
		ret = fan53555_voltages_setup_silergy(di);
		अवरोध;
	हाल FAN53555_VENDOR_TCS:
		ret = fan53555_voltages_setup_tcs(di);
		अवरोध;
	शेष:
		dev_err(di->dev, "vendor %d not supported!\n", di->venकरोr);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fan53555_regulator_रेजिस्टर(काष्ठा fan53555_device_info *di,
			काष्ठा regulator_config *config)
अणु
	काष्ठा regulator_desc *rdesc = &di->desc;
	काष्ठा regulator_dev *rdev;

	rdesc->name = "fan53555-reg";
	rdesc->supply_name = "vin";
	rdesc->ops = &fan53555_regulator_ops;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->n_voltages = di->vsel_count;
	rdesc->enable_reg = di->vol_reg;
	rdesc->enable_mask = VSEL_BUCK_EN;
	rdesc->min_uV = di->vsel_min;
	rdesc->uV_step = di->vsel_step;
	rdesc->vsel_reg = di->vol_reg;
	rdesc->vsel_mask = di->vsel_count - 1;
	rdesc->owner = THIS_MODULE;

	rdev = devm_regulator_रेजिस्टर(di->dev, &di->desc, config);
	वापस PTR_ERR_OR_ZERO(rdev);
पूर्ण

अटल स्थिर काष्ठा regmap_config fan53555_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल काष्ठा fan53555_platक्रमm_data *fan53555_parse_dt(काष्ठा device *dev,
					      काष्ठा device_node *np,
					      स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा fan53555_platक्रमm_data *pdata;
	पूर्णांक ret;
	u32 पंचांगp;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->regulator = of_get_regulator_init_data(dev, np, desc);

	ret = of_property_पढ़ो_u32(np, "fcs,suspend-voltage-selector",
				   &पंचांगp);
	अगर (!ret)
		pdata->sleep_vsel_id = पंचांगp;

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused fan53555_dt_ids[] = अणु
	अणु
		.compatible = "fcs,fan53526",
		.data = (व्योम *)FAN53526_VENDOR_FAIRCHILD,
	पूर्ण, अणु
		.compatible = "fcs,fan53555",
		.data = (व्योम *)FAN53555_VENDOR_FAIRCHILD
	पूर्ण, अणु
		.compatible = "silergy,syr827",
		.data = (व्योम *)FAN53555_VENDOR_SILERGY,
	पूर्ण, अणु
		.compatible = "silergy,syr828",
		.data = (व्योम *)FAN53555_VENDOR_SILERGY,
	पूर्ण, अणु
		.compatible = "tcs,tcs4525",
		.data = (व्योम *)FAN53555_VENDOR_TCS
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fan53555_dt_ids);

अटल पूर्णांक fan53555_regulator_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा fan53555_device_info *di;
	काष्ठा fan53555_platक्रमm_data *pdata;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	di = devm_kzalloc(&client->dev, माप(काष्ठा fan53555_device_info),
					GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata)
		pdata = fan53555_parse_dt(&client->dev, np, &di->desc);

	अगर (!pdata || !pdata->regulator) अणु
		dev_err(&client->dev, "Platform data not found!\n");
		वापस -ENODEV;
	पूर्ण

	di->regulator = pdata->regulator;
	अगर (client->dev.of_node) अणु
		di->venकरोr =
			(अचिन्हित दीर्घ)of_device_get_match_data(&client->dev);
	पूर्ण अन्यथा अणु
		/* अगर no ramp स्थिरraपूर्णांक set, get the pdata ramp_delay */
		अगर (!di->regulator->स्थिरraपूर्णांकs.ramp_delay) अणु
			अगर (pdata->slew_rate >= ARRAY_SIZE(slew_rates)) अणु
				dev_err(&client->dev, "Invalid slew_rate\n");
				वापस -EINVAL;
			पूर्ण

			di->regulator->स्थिरraपूर्णांकs.ramp_delay
					= slew_rates[pdata->slew_rate];
		पूर्ण

		di->venकरोr = id->driver_data;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &fan53555_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to allocate regmap!\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	di->dev = &client->dev;
	i2c_set_clientdata(client, di);
	/* Get chip ID */
	ret = regmap_पढ़ो(regmap, FAN53555_ID1, &val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to get chip ID!\n");
		वापस ret;
	पूर्ण
	di->chip_id = val & DIE_ID;
	/* Get chip revision */
	ret = regmap_पढ़ो(regmap, FAN53555_ID2, &val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to get chip Rev!\n");
		वापस ret;
	पूर्ण
	di->chip_rev = val & DIE_REV;
	dev_info(&client->dev, "FAN53555 Option[%d] Rev[%d] Detected!\n",
				di->chip_id, di->chip_rev);
	/* Device init */
	ret = fan53555_device_setup(di, pdata);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to setup device!\n");
		वापस ret;
	पूर्ण
	/* Register regulator */
	config.dev = di->dev;
	config.init_data = di->regulator;
	config.regmap = regmap;
	config.driver_data = di;
	config.of_node = np;

	ret = fan53555_regulator_रेजिस्टर(di, &config);
	अगर (ret < 0)
		dev_err(&client->dev, "Failed to register regulator!\n");
	वापस ret;

पूर्ण

अटल स्थिर काष्ठा i2c_device_id fan53555_id[] = अणु
	अणु
		.name = "fan53526",
		.driver_data = FAN53526_VENDOR_FAIRCHILD
	पूर्ण, अणु
		.name = "fan53555",
		.driver_data = FAN53555_VENDOR_FAIRCHILD
	पूर्ण, अणु
		.name = "syr827",
		.driver_data = FAN53555_VENDOR_SILERGY
	पूर्ण, अणु
		.name = "syr828",
		.driver_data = FAN53555_VENDOR_SILERGY
	पूर्ण, अणु
		.name = "tcs4525",
		.driver_data = FAN53555_VENDOR_TCS
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fan53555_id);

अटल काष्ठा i2c_driver fan53555_regulator_driver = अणु
	.driver = अणु
		.name = "fan53555-regulator",
		.of_match_table = of_match_ptr(fan53555_dt_ids),
	पूर्ण,
	.probe = fan53555_regulator_probe,
	.id_table = fan53555_id,
पूर्ण;

module_i2c_driver(fan53555_regulator_driver);

MODULE_AUTHOR("Yunfan Zhang <yfzhang@marvell.com>");
MODULE_DESCRIPTION("FAN53555 regulator driver");
MODULE_LICENSE("GPL v2");
