<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Core driver क्रम ams AS3722 PMICs
 *
 * Copyright (C) 2013 AMS AG
 * Copyright (c) 2013, NVIDIA Corporation. All rights reserved.
 *
 * Author: Florian Lobmaier <florian.lobmaier@ams.com>
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/as3722.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा AS3722_DEVICE_ID	0x0C

अटल स्थिर काष्ठा resource as3722_rtc_resource[] = अणु
	अणु
		.name = "as3722-rtc-alarm",
		.start = AS3722_IRQ_RTC_ALARM,
		.end = AS3722_IRQ_RTC_ALARM,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource as3722_adc_resource[] = अणु
	अणु
		.name = "as3722-adc",
		.start = AS3722_IRQ_ADC,
		.end = AS3722_IRQ_ADC,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell as3722_devs[] = अणु
	अणु
		.name = "as3722-pinctrl",
	पूर्ण,
	अणु
		.name = "as3722-regulator",
	पूर्ण,
	अणु
		.name = "as3722-rtc",
		.num_resources = ARRAY_SIZE(as3722_rtc_resource),
		.resources = as3722_rtc_resource,
	पूर्ण,
	अणु
		.name = "as3722-adc",
		.num_resources = ARRAY_SIZE(as3722_adc_resource),
		.resources = as3722_adc_resource,
	पूर्ण,
	अणु
		.name = "as3722-power-off",
	पूर्ण,
	अणु
		.name = "as3722-wdt",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq as3722_irqs[] = अणु
	/* INT1 IRQs */
	[AS3722_IRQ_LID] = अणु
		.mask = AS3722_INTERRUPT_MASK1_LID,
	पूर्ण,
	[AS3722_IRQ_ACOK] = अणु
		.mask = AS3722_INTERRUPT_MASK1_ACOK,
	पूर्ण,
	[AS3722_IRQ_ENABLE1] = अणु
		.mask = AS3722_INTERRUPT_MASK1_ENABLE1,
	पूर्ण,
	[AS3722_IRQ_OCCUR_ALARM_SD0] = अणु
		.mask = AS3722_INTERRUPT_MASK1_OCURR_ALARM_SD0,
	पूर्ण,
	[AS3722_IRQ_ONKEY_LONG_PRESS] = अणु
		.mask = AS3722_INTERRUPT_MASK1_ONKEY_LONG,
	पूर्ण,
	[AS3722_IRQ_ONKEY] = अणु
		.mask = AS3722_INTERRUPT_MASK1_ONKEY,
	पूर्ण,
	[AS3722_IRQ_OVTMP] = अणु
		.mask = AS3722_INTERRUPT_MASK1_OVTMP,
	पूर्ण,
	[AS3722_IRQ_LOWBAT] = अणु
		.mask = AS3722_INTERRUPT_MASK1_LOWBAT,
	पूर्ण,

	/* INT2 IRQs */
	[AS3722_IRQ_SD0_LV] = अणु
		.mask = AS3722_INTERRUPT_MASK2_SD0_LV,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_SD1_LV] = अणु
		.mask = AS3722_INTERRUPT_MASK2_SD1_LV,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_SD2_LV] = अणु
		.mask = AS3722_INTERRUPT_MASK2_SD2345_LV,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_PWM1_OV_PROT] = अणु
		.mask = AS3722_INTERRUPT_MASK2_PWM1_OV_PROT,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_PWM2_OV_PROT] = अणु
		.mask = AS3722_INTERRUPT_MASK2_PWM2_OV_PROT,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_ENABLE2] = अणु
		.mask = AS3722_INTERRUPT_MASK2_ENABLE2,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_SD6_LV] = अणु
		.mask = AS3722_INTERRUPT_MASK2_SD6_LV,
		.reg_offset = 1,
	पूर्ण,
	[AS3722_IRQ_RTC_REP] = अणु
		.mask = AS3722_INTERRUPT_MASK2_RTC_REP,
		.reg_offset = 1,
	पूर्ण,

	/* INT3 IRQs */
	[AS3722_IRQ_RTC_ALARM] = अणु
		.mask = AS3722_INTERRUPT_MASK3_RTC_ALARM,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_GPIO1] = अणु
		.mask = AS3722_INTERRUPT_MASK3_GPIO1,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_GPIO2] = अणु
		.mask = AS3722_INTERRUPT_MASK3_GPIO2,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_GPIO3] = अणु
		.mask = AS3722_INTERRUPT_MASK3_GPIO3,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_GPIO4] = अणु
		.mask = AS3722_INTERRUPT_MASK3_GPIO4,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_GPIO5] = अणु
		.mask = AS3722_INTERRUPT_MASK3_GPIO5,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_WATCHDOG] = अणु
		.mask = AS3722_INTERRUPT_MASK3_WATCHDOG,
		.reg_offset = 2,
	पूर्ण,
	[AS3722_IRQ_ENABLE3] = अणु
		.mask = AS3722_INTERRUPT_MASK3_ENABLE3,
		.reg_offset = 2,
	पूर्ण,

	/* INT4 IRQs */
	[AS3722_IRQ_TEMP_SD0_SHUTDOWN] = अणु
		.mask = AS3722_INTERRUPT_MASK4_TEMP_SD0_SHUTDOWN,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_TEMP_SD1_SHUTDOWN] = अणु
		.mask = AS3722_INTERRUPT_MASK4_TEMP_SD1_SHUTDOWN,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_TEMP_SD2_SHUTDOWN] = अणु
		.mask = AS3722_INTERRUPT_MASK4_TEMP_SD6_SHUTDOWN,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_TEMP_SD0_ALARM] = अणु
		.mask = AS3722_INTERRUPT_MASK4_TEMP_SD0_ALARM,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_TEMP_SD1_ALARM] = अणु
		.mask = AS3722_INTERRUPT_MASK4_TEMP_SD1_ALARM,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_TEMP_SD6_ALARM] = अणु
		.mask = AS3722_INTERRUPT_MASK4_TEMP_SD6_ALARM,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_OCCUR_ALARM_SD6] = अणु
		.mask = AS3722_INTERRUPT_MASK4_OCCUR_ALARM_SD6,
		.reg_offset = 3,
	पूर्ण,
	[AS3722_IRQ_ADC] = अणु
		.mask = AS3722_INTERRUPT_MASK4_ADC,
		.reg_offset = 3,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip as3722_irq_chip = अणु
	.name = "as3722",
	.irqs = as3722_irqs,
	.num_irqs = ARRAY_SIZE(as3722_irqs),
	.num_regs = 4,
	.status_base = AS3722_INTERRUPT_STATUS1_REG,
	.mask_base = AS3722_INTERRUPT_MASK1_REG,
पूर्ण;

अटल पूर्णांक as3722_check_device_id(काष्ठा as3722 *as3722)
अणु
	u32 val;
	पूर्णांक ret;

	/* Check that this is actually a AS3722 */
	ret = as3722_पढ़ो(as3722, AS3722_ASIC_ID1_REG, &val);
	अगर (ret < 0) अणु
		dev_err(as3722->dev, "ASIC_ID1 read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (val != AS3722_DEVICE_ID) अणु
		dev_err(as3722->dev, "Device is not AS3722, ID is 0x%x\n", val);
		वापस -ENODEV;
	पूर्ण

	ret = as3722_पढ़ो(as3722, AS3722_ASIC_ID2_REG, &val);
	अगर (ret < 0) अणु
		dev_err(as3722->dev, "ASIC_ID2 read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(as3722->dev, "AS3722 with revision 0x%x found\n", val);
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_configure_pullups(काष्ठा as3722 *as3722)
अणु
	पूर्णांक ret;
	u32 val = 0;

	अगर (as3722->en_पूर्णांकern_पूर्णांक_pullup)
		val |= AS3722_INT_PULL_UP;
	अगर (as3722->en_पूर्णांकern_i2c_pullup)
		val |= AS3722_I2C_PULL_UP;

	ret = as3722_update_bits(as3722, AS3722_IOVOLTAGE_REG,
			AS3722_INT_PULL_UP | AS3722_I2C_PULL_UP, val);
	अगर (ret < 0)
		dev_err(as3722->dev, "IOVOLTAGE_REG update failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_range as3722_पढ़ोable_ranges[] = अणु
	regmap_reg_range(AS3722_SD0_VOLTAGE_REG, AS3722_SD6_VOLTAGE_REG),
	regmap_reg_range(AS3722_GPIO0_CONTROL_REG, AS3722_LDO7_VOLTAGE_REG),
	regmap_reg_range(AS3722_LDO9_VOLTAGE_REG, AS3722_REG_SEQU_MOD3_REG),
	regmap_reg_range(AS3722_SD_PHSW_CTRL_REG, AS3722_PWM_CONTROL_H_REG),
	regmap_reg_range(AS3722_WATCHDOG_TIMER_REG, AS3722_WATCHDOG_TIMER_REG),
	regmap_reg_range(AS3722_WATCHDOG_SOFTWARE_SIGNAL_REG,
					AS3722_BATTERY_VOLTAGE_MONITOR2_REG),
	regmap_reg_range(AS3722_SD_CONTROL_REG, AS3722_PWM_VCONTROL4_REG),
	regmap_reg_range(AS3722_BB_CHARGER_REG, AS3722_SRAM_REG),
	regmap_reg_range(AS3722_RTC_ACCESS_REG, AS3722_RTC_ACCESS_REG),
	regmap_reg_range(AS3722_RTC_STATUS_REG, AS3722_TEMP_STATUS_REG),
	regmap_reg_range(AS3722_ADC0_CONTROL_REG, AS3722_ADC_CONFIGURATION_REG),
	regmap_reg_range(AS3722_ASIC_ID1_REG, AS3722_ASIC_ID2_REG),
	regmap_reg_range(AS3722_LOCK_REG, AS3722_LOCK_REG),
	regmap_reg_range(AS3722_FUSE7_REG, AS3722_FUSE7_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table as3722_पढ़ोable_table = अणु
	.yes_ranges = as3722_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(as3722_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range as3722_writable_ranges[] = अणु
	regmap_reg_range(AS3722_SD0_VOLTAGE_REG, AS3722_SD6_VOLTAGE_REG),
	regmap_reg_range(AS3722_GPIO0_CONTROL_REG, AS3722_LDO7_VOLTAGE_REG),
	regmap_reg_range(AS3722_LDO9_VOLTAGE_REG, AS3722_GPIO_SIGNAL_OUT_REG),
	regmap_reg_range(AS3722_REG_SEQU_MOD1_REG, AS3722_REG_SEQU_MOD3_REG),
	regmap_reg_range(AS3722_SD_PHSW_CTRL_REG, AS3722_PWM_CONTROL_H_REG),
	regmap_reg_range(AS3722_WATCHDOG_TIMER_REG, AS3722_WATCHDOG_TIMER_REG),
	regmap_reg_range(AS3722_WATCHDOG_SOFTWARE_SIGNAL_REG,
					AS3722_BATTERY_VOLTAGE_MONITOR2_REG),
	regmap_reg_range(AS3722_SD_CONTROL_REG, AS3722_PWM_VCONTROL4_REG),
	regmap_reg_range(AS3722_BB_CHARGER_REG, AS3722_SRAM_REG),
	regmap_reg_range(AS3722_INTERRUPT_MASK1_REG, AS3722_TEMP_STATUS_REG),
	regmap_reg_range(AS3722_ADC0_CONTROL_REG, AS3722_ADC1_CONTROL_REG),
	regmap_reg_range(AS3722_ADC1_THRESHOLD_HI_MSB_REG,
					AS3722_ADC_CONFIGURATION_REG),
	regmap_reg_range(AS3722_LOCK_REG, AS3722_LOCK_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table as3722_writable_table = अणु
	.yes_ranges = as3722_writable_ranges,
	.n_yes_ranges = ARRAY_SIZE(as3722_writable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range as3722_cacheable_ranges[] = अणु
	regmap_reg_range(AS3722_SD0_VOLTAGE_REG, AS3722_LDO11_VOLTAGE_REG),
	regmap_reg_range(AS3722_SD_CONTROL_REG, AS3722_LDOCONTROL1_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table as3722_अस्थिर_table = अणु
	.no_ranges = as3722_cacheable_ranges,
	.n_no_ranges = ARRAY_SIZE(as3722_cacheable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config as3722_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = AS3722_MAX_REGISTER,
	.cache_type = REGCACHE_RBTREE,
	.rd_table = &as3722_पढ़ोable_table,
	.wr_table = &as3722_writable_table,
	.अस्थिर_table = &as3722_अस्थिर_table,
पूर्ण;

अटल पूर्णांक as3722_i2c_of_probe(काष्ठा i2c_client *i2c,
			काष्ठा as3722 *as3722)
अणु
	काष्ठा device_node *np = i2c->dev.of_node;
	काष्ठा irq_data *irq_data;

	अगर (!np) अणु
		dev_err(&i2c->dev, "Device Tree not found\n");
		वापस -EINVAL;
	पूर्ण

	irq_data = irq_get_irq_data(i2c->irq);
	अगर (!irq_data) अणु
		dev_err(&i2c->dev, "Invalid IRQ: %d\n", i2c->irq);
		वापस -EINVAL;
	पूर्ण

	as3722->en_पूर्णांकern_पूर्णांक_pullup = of_property_पढ़ो_bool(np,
					"ams,enable-internal-int-pullup");
	as3722->en_पूर्णांकern_i2c_pullup = of_property_पढ़ो_bool(np,
					"ams,enable-internal-i2c-pullup");
	as3722->en_ac_ok_pwr_on = of_property_पढ़ो_bool(np,
					"ams,enable-ac-ok-power-on");
	as3722->irq_flags = irqd_get_trigger_type(irq_data);
	dev_dbg(&i2c->dev, "IRQ flags are 0x%08lx\n", as3722->irq_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_i2c_probe(काष्ठा i2c_client *i2c,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा as3722 *as3722;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret;
	u8 val = 0;

	as3722 = devm_kzalloc(&i2c->dev, माप(काष्ठा as3722), GFP_KERNEL);
	अगर (!as3722)
		वापस -ENOMEM;

	as3722->dev = &i2c->dev;
	as3722->chip_irq = i2c->irq;
	i2c_set_clientdata(i2c, as3722);

	ret = as3722_i2c_of_probe(i2c, as3722);
	अगर (ret < 0)
		वापस ret;

	as3722->regmap = devm_regmap_init_i2c(i2c, &as3722_regmap_config);
	अगर (IS_ERR(as3722->regmap)) अणु
		ret = PTR_ERR(as3722->regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = as3722_check_device_id(as3722);
	अगर (ret < 0)
		वापस ret;

	irq_flags = as3722->irq_flags | IRQF_ONESHOT;
	ret = devm_regmap_add_irq_chip(as3722->dev, as3722->regmap,
				       as3722->chip_irq,
				       irq_flags, -1, &as3722_irq_chip,
				       &as3722->irq_data);
	अगर (ret < 0) अणु
		dev_err(as3722->dev, "Failed to add regmap irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = as3722_configure_pullups(as3722);
	अगर (ret < 0)
		वापस ret;

	अगर (as3722->en_ac_ok_pwr_on)
		val = AS3722_CTRL_SEQU1_AC_OK_PWR_ON;
	ret = as3722_update_bits(as3722, AS3722_CTRL_SEQU1_REG,
			AS3722_CTRL_SEQU1_AC_OK_PWR_ON, val);
	अगर (ret < 0) अणु
		dev_err(as3722->dev, "CTRLsequ1 update failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(&i2c->dev, -1, as3722_devs,
				   ARRAY_SIZE(as3722_devs), शून्य, 0,
				   regmap_irq_get_करोमुख्य(as3722->irq_data));
	अगर (ret) अणु
		dev_err(as3722->dev, "Failed to add MFD devices: %d\n", ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(as3722->dev, true);

	dev_dbg(as3722->dev, "AS3722 core driver initialized successfully\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused as3722_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा as3722 *as3722 = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(as3722->chip_irq);
	disable_irq(as3722->chip_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused as3722_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा as3722 *as3722 = dev_get_drvdata(dev);

	enable_irq(as3722->chip_irq);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(as3722->chip_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id as3722_of_match[] = अणु
	अणु .compatible = "ams,as3722", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, as3722_of_match);

अटल स्थिर काष्ठा i2c_device_id as3722_i2c_id[] = अणु
	अणु "as3722", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, as3722_i2c_id);

अटल स्थिर काष्ठा dev_pm_ops as3722_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(as3722_i2c_suspend, as3722_i2c_resume)
पूर्ण;

अटल काष्ठा i2c_driver as3722_i2c_driver = अणु
	.driver = अणु
		.name = "as3722",
		.of_match_table = as3722_of_match,
		.pm = &as3722_pm_ops,
	पूर्ण,
	.probe = as3722_i2c_probe,
	.id_table = as3722_i2c_id,
पूर्ण;

module_i2c_driver(as3722_i2c_driver);

MODULE_DESCRIPTION("I2C support for AS3722 PMICs");
MODULE_AUTHOR("Florian Lobmaier <florian.lobmaier@ams.com>");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL");
