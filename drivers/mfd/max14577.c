<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max14577.c - mfd core driver क्रम the Maxim 14577/77836
//
// Copyright (C) 2014 Samsung Electronics
// Chanwoo Choi <cw00.choi@samsung.com>
// Krzysztof Kozlowski <krzk@kernel.org>
//
// This driver is based on max8997.c

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max14577.h>
#समावेश <linux/mfd/max14577-निजी.h>

/*
 * Table of valid अक्षरger currents क्रम dअगरferent Maxim chipsets.
 * It is placed here because it is used by both अक्षरger and regulator driver.
 */
स्थिर काष्ठा maxim_अक्षरger_current maxim_अक्षरger_currents[] = अणु
	[MAXIM_DEVICE_TYPE_UNKNOWN] = अणु 0, 0, 0, 0 पूर्ण,
	[MAXIM_DEVICE_TYPE_MAX14577] = अणु
		.min		= MAX14577_CHARGER_CURRENT_LIMIT_MIN,
		.high_start	= MAX14577_CHARGER_CURRENT_LIMIT_HIGH_START,
		.high_step	= MAX14577_CHARGER_CURRENT_LIMIT_HIGH_STEP,
		.max		= MAX14577_CHARGER_CURRENT_LIMIT_MAX,
	पूर्ण,
	[MAXIM_DEVICE_TYPE_MAX77836] = अणु
		.min		= MAX77836_CHARGER_CURRENT_LIMIT_MIN,
		.high_start	= MAX77836_CHARGER_CURRENT_LIMIT_HIGH_START,
		.high_step	= MAX77836_CHARGER_CURRENT_LIMIT_HIGH_STEP,
		.max		= MAX77836_CHARGER_CURRENT_LIMIT_MAX,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(maxim_अक्षरger_currents);

/*
 * maxim_अक्षरger_calc_reg_current - Calculate रेजिस्टर value क्रम current
 * @limits:	स्थिरraपूर्णांकs क्रम अक्षरger, matching the MBCICHWRC रेजिस्टर
 * @min_ua:	minimal requested current, micro Amps
 * @max_ua:	maximum requested current, micro Amps
 * @dst:	destination to store calculated रेजिस्टर value
 *
 * Calculates the value of MBCICHWRC (Fast Battery Charge Current) रेजिस्टर
 * क्रम given current and stores it under poपूर्णांकed 'dst'. The stored value
 * combines low bit (MBCICHWRCL) and high bits (MBCICHWRCH). It is also
 * properly shअगरted.
 *
 * The calculated रेजिस्टर value matches the current which:
 *  - is always between <limits.min, limits.max>;
 *  - is always less or equal to max_ua;
 *  - is the highest possible value;
 *  - may be lower than min_ua.
 *
 * On success वापसs 0. On error वापसs -EINVAL (requested min/max current
 * is outside of given अक्षरger limits) and 'dst' is not set.
 */
पूर्णांक maxim_अक्षरger_calc_reg_current(स्थिर काष्ठा maxim_अक्षरger_current *limits,
		अचिन्हित पूर्णांक min_ua, अचिन्हित पूर्णांक max_ua, u8 *dst)
अणु
	अचिन्हित पूर्णांक current_bits;

	अगर (min_ua > max_ua)
		वापस -EINVAL;

	अगर (min_ua > limits->max || max_ua < limits->min)
		वापस -EINVAL;

	अगर (max_ua < limits->high_start) अणु
		/*
		 * Less than high_start, so set the minimal current
		 * (turn Low Bit off, 0 as high bits).
		 */
		*dst = 0x0;
		वापस 0;
	पूर्ण

	/* max_ua is in range: <high_start, infinite>, cut it to limits.max */
	max_ua = min(limits->max, max_ua);
	max_ua -= limits->high_start;
	/*
	 * There is no risk of overflow 'max_ua' here because:
	 *  - max_ua >= सीमा.सigh_start
	 *  - BUILD_BUG checks that 'limits' are: max >= high_start + high_step
	 */
	current_bits = max_ua / limits->high_step;

	/* Turn Low Bit on (use range <सीमा.सigh_start, limits.max>) ... */
	*dst = 0x1 << CHGCTRL4_MBCICHWRCL_SHIFT;
	/* and set proper High Bits */
	*dst |= current_bits << CHGCTRL4_MBCICHWRCH_SHIFT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(maxim_अक्षरger_calc_reg_current);

अटल स्थिर काष्ठा mfd_cell max14577_devs[] = अणु
	अणु
		.name = "max14577-muic",
		.of_compatible = "maxim,max14577-muic",
	पूर्ण,
	अणु
		.name = "max14577-regulator",
		.of_compatible = "maxim,max14577-regulator",
	पूर्ण,
	अणु
		.name = "max14577-charger",
		.of_compatible = "maxim,max14577-charger",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell max77836_devs[] = अणु
	अणु
		.name = "max77836-muic",
		.of_compatible = "maxim,max77836-muic",
	पूर्ण,
	अणु
		.name = "max77836-regulator",
		.of_compatible = "maxim,max77836-regulator",
	पूर्ण,
	अणु
		.name = "max77836-charger",
		.of_compatible = "maxim,max77836-charger",
	पूर्ण,
	अणु
		.name = "max77836-battery",
		.of_compatible = "maxim,max77836-battery",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id max14577_dt_match[] = अणु
	अणु
		.compatible = "maxim,max14577",
		.data = (व्योम *)MAXIM_DEVICE_TYPE_MAX14577,
	पूर्ण,
	अणु
		.compatible = "maxim,max77836",
		.data = (व्योम *)MAXIM_DEVICE_TYPE_MAX77836,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल bool max14577_muic_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX14577_REG_INT1 ... MAX14577_REG_STATUS3:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल bool max77836_muic_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Any max14577 अस्थिर रेजिस्टरs are also max77836 अस्थिर. */
	अगर (max14577_muic_अस्थिर_reg(dev, reg))
		वापस true;

	चयन (reg) अणु
	हाल MAX77836_FG_REG_VCELL_MSB ... MAX77836_FG_REG_SOC_LSB:
	हाल MAX77836_FG_REG_CRATE_MSB ... MAX77836_FG_REG_CRATE_LSB:
	हाल MAX77836_FG_REG_STATUS_H ... MAX77836_FG_REG_STATUS_L:
	हाल MAX77836_PMIC_REG_INTSRC:
	हाल MAX77836_PMIC_REG_TOPSYS_INT:
	हाल MAX77836_PMIC_REG_TOPSYS_STAT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config max14577_muic_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.अस्थिर_reg	= max14577_muic_अस्थिर_reg,
	.max_रेजिस्टर	= MAX14577_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77836_pmic_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.अस्थिर_reg	= max77836_muic_अस्थिर_reg,
	.max_रेजिस्टर	= MAX77836_PMIC_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max14577_irqs[] = अणु
	/* INT1 पूर्णांकerrupts */
	अणु .reg_offset = 0, .mask = MAX14577_INT1_ADC_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX14577_INT1_ADCLOW_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX14577_INT1_ADCERR_MASK, पूर्ण,
	/* INT2 पूर्णांकerrupts */
	अणु .reg_offset = 1, .mask = MAX14577_INT2_CHGTYP_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_CHGDETRUN_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_DCDTMR_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_DBCHG_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_VBVOLT_MASK, पूर्ण,
	/* INT3 पूर्णांकerrupts */
	अणु .reg_offset = 2, .mask = MAX14577_INT3_EOC_MASK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX14577_INT3_CGMBC_MASK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX14577_INT3_OVP_MASK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX14577_INT3_MBCCHGERR_MASK, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max14577_irq_chip = अणु
	.name			= "max14577",
	.status_base		= MAX14577_REG_INT1,
	.mask_base		= MAX14577_REG_INTMASK1,
	.mask_invert		= true,
	.num_regs		= 3,
	.irqs			= max14577_irqs,
	.num_irqs		= ARRAY_SIZE(max14577_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77836_muic_irqs[] = अणु
	/* INT1 पूर्णांकerrupts */
	अणु .reg_offset = 0, .mask = MAX14577_INT1_ADC_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX14577_INT1_ADCLOW_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX14577_INT1_ADCERR_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77836_INT1_ADC1K_MASK, पूर्ण,
	/* INT2 पूर्णांकerrupts */
	अणु .reg_offset = 1, .mask = MAX14577_INT2_CHGTYP_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_CHGDETRUN_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_DCDTMR_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_DBCHG_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX14577_INT2_VBVOLT_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX77836_INT2_VIDRM_MASK, पूर्ण,
	/* INT3 पूर्णांकerrupts */
	अणु .reg_offset = 2, .mask = MAX14577_INT3_EOC_MASK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX14577_INT3_CGMBC_MASK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX14577_INT3_OVP_MASK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX14577_INT3_MBCCHGERR_MASK, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77836_muic_irq_chip = अणु
	.name			= "max77836-muic",
	.status_base		= MAX14577_REG_INT1,
	.mask_base		= MAX14577_REG_INTMASK1,
	.mask_invert		= true,
	.num_regs		= 3,
	.irqs			= max77836_muic_irqs,
	.num_irqs		= ARRAY_SIZE(max77836_muic_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77836_pmic_irqs[] = अणु
	अणु .reg_offset = 0, .mask = MAX77836_TOPSYS_INT_T120C_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77836_TOPSYS_INT_T140C_MASK, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77836_pmic_irq_chip = अणु
	.name			= "max77836-pmic",
	.status_base		= MAX77836_PMIC_REG_TOPSYS_INT,
	.mask_base		= MAX77836_PMIC_REG_TOPSYS_INT_MASK,
	.mask_invert		= false,
	.num_regs		= 1,
	.irqs			= max77836_pmic_irqs,
	.num_irqs		= ARRAY_SIZE(max77836_pmic_irqs),
पूर्ण;

अटल व्योम max14577_prपूर्णांक_dev_type(काष्ठा max14577 *max14577)
अणु
	u8 reg_data, venकरोr_id, device_id;
	पूर्णांक ret;

	ret = max14577_पढ़ो_reg(max14577->regmap, MAX14577_REG_DEVICEID,
			&reg_data);
	अगर (ret) अणु
		dev_err(max14577->dev,
			"Failed to read DEVICEID register: %d\n", ret);
		वापस;
	पूर्ण

	venकरोr_id = ((reg_data & DEVID_VENDORID_MASK) >>
				DEVID_VENDORID_SHIFT);
	device_id = ((reg_data & DEVID_DEVICEID_MASK) >>
				DEVID_DEVICEID_SHIFT);

	dev_info(max14577->dev, "Device type: %u (ID: 0x%x, vendor: 0x%x)\n",
			max14577->dev_type, device_id, venकरोr_id);
पूर्ण

/*
 * Max77836 specअगरic initialization code क्रम driver probe.
 * Adds new I2C dummy device, regmap and regmap IRQ chip.
 * Unmasks Interrupt Source रेजिस्टर.
 *
 * On success वापसs 0.
 * On failure वापसs त्रुटि_सं and reverts any changes करोne so far (e.g. हटाओ
 * I2C dummy device), except masking the INT SRC रेजिस्टर.
 */
अटल पूर्णांक max77836_init(काष्ठा max14577 *max14577)
अणु
	पूर्णांक ret;
	u8 पूर्णांकsrc_mask;

	max14577->i2c_pmic = i2c_new_dummy_device(max14577->i2c->adapter,
			I2C_ADDR_PMIC);
	अगर (IS_ERR(max14577->i2c_pmic)) अणु
		dev_err(max14577->dev, "Failed to register PMIC I2C device\n");
		वापस PTR_ERR(max14577->i2c_pmic);
	पूर्ण
	i2c_set_clientdata(max14577->i2c_pmic, max14577);

	max14577->regmap_pmic = devm_regmap_init_i2c(max14577->i2c_pmic,
			&max77836_pmic_regmap_config);
	अगर (IS_ERR(max14577->regmap_pmic)) अणु
		ret = PTR_ERR(max14577->regmap_pmic);
		dev_err(max14577->dev, "Failed to allocate PMIC register map: %d\n",
				ret);
		जाओ err;
	पूर्ण

	/* Un-mask MAX77836 Interrupt Source रेजिस्टर */
	ret = max14577_पढ़ो_reg(max14577->regmap_pmic,
			MAX77836_PMIC_REG_INTSRC_MASK, &पूर्णांकsrc_mask);
	अगर (ret < 0) अणु
		dev_err(max14577->dev, "Failed to read PMIC register\n");
		जाओ err;
	पूर्ण

	पूर्णांकsrc_mask &= ~(MAX77836_INTSRC_MASK_TOP_INT_MASK);
	पूर्णांकsrc_mask &= ~(MAX77836_INTSRC_MASK_MUIC_CHG_INT_MASK);
	ret = max14577_ग_लिखो_reg(max14577->regmap_pmic,
			MAX77836_PMIC_REG_INTSRC_MASK, पूर्णांकsrc_mask);
	अगर (ret < 0) अणु
		dev_err(max14577->dev, "Failed to write PMIC register\n");
		जाओ err;
	पूर्ण

	ret = regmap_add_irq_chip(max14577->regmap_pmic, max14577->irq,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT | IRQF_SHARED,
			0, &max77836_pmic_irq_chip,
			&max14577->irq_data_pmic);
	अगर (ret != 0) अणु
		dev_err(max14577->dev, "Failed to request PMIC IRQ %d: %d\n",
				max14577->irq, ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	i2c_unरेजिस्टर_device(max14577->i2c_pmic);

	वापस ret;
पूर्ण

/*
 * Max77836 specअगरic de-initialization code क्रम driver हटाओ.
 */
अटल व्योम max77836_हटाओ(काष्ठा max14577 *max14577)
अणु
	regmap_del_irq_chip(max14577->irq, max14577->irq_data_pmic);
	i2c_unरेजिस्टर_device(max14577->i2c_pmic);
पूर्ण

अटल पूर्णांक max14577_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max14577 *max14577;
	काष्ठा max14577_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा device_node *np = i2c->dev.of_node;
	पूर्णांक ret = 0;
	स्थिर काष्ठा regmap_irq_chip *irq_chip;
	स्थिर काष्ठा mfd_cell *mfd_devs;
	अचिन्हित पूर्णांक mfd_devs_size;
	पूर्णांक irq_flags;

	अगर (np) अणु
		pdata = devm_kzalloc(&i2c->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
		i2c->dev.platक्रमm_data = pdata;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&i2c->dev, "No platform data found.\n");
		वापस -EINVAL;
	पूर्ण

	max14577 = devm_kzalloc(&i2c->dev, माप(*max14577), GFP_KERNEL);
	अगर (!max14577)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max14577);
	max14577->dev = &i2c->dev;
	max14577->i2c = i2c;
	max14577->irq = i2c->irq;

	max14577->regmap = devm_regmap_init_i2c(i2c,
			&max14577_muic_regmap_config);
	अगर (IS_ERR(max14577->regmap)) अणु
		ret = PTR_ERR(max14577->regmap);
		dev_err(max14577->dev, "Failed to allocate register map: %d\n",
				ret);
		वापस ret;
	पूर्ण

	अगर (np) अणु
		स्थिर काष्ठा of_device_id *of_id;

		of_id = of_match_device(max14577_dt_match, &i2c->dev);
		अगर (of_id)
			max14577->dev_type =
				(क्रमागत maxim_device_type)of_id->data;
	पूर्ण अन्यथा अणु
		max14577->dev_type = id->driver_data;
	पूर्ण

	max14577_prपूर्णांक_dev_type(max14577);

	चयन (max14577->dev_type) अणु
	हाल MAXIM_DEVICE_TYPE_MAX77836:
		irq_chip = &max77836_muic_irq_chip;
		mfd_devs = max77836_devs;
		mfd_devs_size = ARRAY_SIZE(max77836_devs);
		irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT | IRQF_SHARED;
		अवरोध;
	हाल MAXIM_DEVICE_TYPE_MAX14577:
	शेष:
		irq_chip = &max14577_irq_chip;
		mfd_devs = max14577_devs;
		mfd_devs_size = ARRAY_SIZE(max14577_devs);
		irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;
		अवरोध;
	पूर्ण

	ret = regmap_add_irq_chip(max14577->regmap, max14577->irq,
				  irq_flags, 0, irq_chip,
				  &max14577->irq_data);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request IRQ %d: %d\n",
				max14577->irq, ret);
		वापस ret;
	पूर्ण

	/* Max77836 specअगरic initialization code (additional regmap) */
	अगर (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836) अणु
		ret = max77836_init(max14577);
		अगर (ret < 0)
			जाओ err_max77836;
	पूर्ण

	ret = mfd_add_devices(max14577->dev, -1, mfd_devs,
			mfd_devs_size, शून्य, 0, शून्य);
	अगर (ret < 0)
		जाओ err_mfd;

	device_init_wakeup(max14577->dev, 1);

	वापस 0;

err_mfd:
	अगर (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836)
		max77836_हटाओ(max14577);
err_max77836:
	regmap_del_irq_chip(max14577->irq, max14577->irq_data);

	वापस ret;
पूर्ण

अटल पूर्णांक max14577_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा max14577 *max14577 = i2c_get_clientdata(i2c);

	mfd_हटाओ_devices(max14577->dev);
	regmap_del_irq_chip(max14577->irq, max14577->irq_data);
	अगर (max14577->dev_type == MAXIM_DEVICE_TYPE_MAX77836)
		max77836_हटाओ(max14577);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max14577_i2c_id[] = अणु
	अणु "max14577", MAXIM_DEVICE_TYPE_MAX14577, पूर्ण,
	अणु "max77836", MAXIM_DEVICE_TYPE_MAX77836, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max14577_i2c_id);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max14577_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max14577 *max14577 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(max14577->irq);
	/*
	 * MUIC IRQ must be disabled during suspend because अगर it happens
	 * जबतक suspended it will be handled beक्रमe resuming I2C.
	 *
	 * When device is woken up from suspend (e.g. by ADC change),
	 * an पूर्णांकerrupt occurs beक्रमe resuming I2C bus controller.
	 * Interrupt handler tries to पढ़ो रेजिस्टरs but this पढ़ो
	 * will fail because I2C is still suspended.
	 */
	disable_irq(max14577->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक max14577_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max14577 *max14577 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(max14577->irq);
	enable_irq(max14577->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(max14577_pm, max14577_suspend, max14577_resume);

अटल काष्ठा i2c_driver max14577_i2c_driver = अणु
	.driver = अणु
		.name = "max14577",
		.pm = &max14577_pm,
		.of_match_table = max14577_dt_match,
	पूर्ण,
	.probe = max14577_i2c_probe,
	.हटाओ = max14577_i2c_हटाओ,
	.id_table = max14577_i2c_id,
पूर्ण;

अटल पूर्णांक __init max14577_i2c_init(व्योम)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(max14577_i2c_id) != MAXIM_DEVICE_TYPE_NUM);
	BUILD_BUG_ON(ARRAY_SIZE(max14577_dt_match) != MAXIM_DEVICE_TYPE_NUM);

	/* Valid अक्षरger current values must be provided क्रम each chipset */
	BUILD_BUG_ON(ARRAY_SIZE(maxim_अक्षरger_currents) != MAXIM_DEVICE_TYPE_NUM);

	/* Check क्रम valid values क्रम अक्षरger */
	BUILD_BUG_ON(MAX14577_CHARGER_CURRENT_LIMIT_HIGH_START +
			MAX14577_CHARGER_CURRENT_LIMIT_HIGH_STEP * 0xf !=
			MAX14577_CHARGER_CURRENT_LIMIT_MAX);
	BUILD_BUG_ON(MAX14577_CHARGER_CURRENT_LIMIT_HIGH_STEP == 0);

	BUILD_BUG_ON(MAX77836_CHARGER_CURRENT_LIMIT_HIGH_START +
			MAX77836_CHARGER_CURRENT_LIMIT_HIGH_STEP * 0xf !=
			MAX77836_CHARGER_CURRENT_LIMIT_MAX);
	BUILD_BUG_ON(MAX77836_CHARGER_CURRENT_LIMIT_HIGH_STEP == 0);

	वापस i2c_add_driver(&max14577_i2c_driver);
पूर्ण
module_init(max14577_i2c_init);

अटल व्योम __निकास max14577_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&max14577_i2c_driver);
पूर्ण
module_निकास(max14577_i2c_निकास);

MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>, Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_DESCRIPTION("Maxim 14577/77836 multi-function core driver");
MODULE_LICENSE("GPL");
