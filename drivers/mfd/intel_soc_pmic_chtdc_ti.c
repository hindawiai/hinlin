<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device access क्रम Dollar Cove TI PMIC
 *
 * Copyright (c) 2014, Intel Corporation.
 *   Author: Ramakrishna Pallala <ramakrishna.pallala@पूर्णांकel.com>
 *
 * Cleanup and क्रमward-ported
 *   Copyright (c) 2017 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#घोषणा CHTDC_TI_IRQLVL1	0x01
#घोषणा CHTDC_TI_MASK_IRQLVL1	0x02

/* Level 1 IRQs */
क्रमागत अणु
	CHTDC_TI_PWRBTN = 0,	/* घातer button */
	CHTDC_TI_DIETMPWARN,	/* thermal */
	CHTDC_TI_ADCCMPL,	/* ADC */
	/* No IRQ 3 */
	CHTDC_TI_VBATLOW = 4,	/* battery */
	CHTDC_TI_VBUSDET,	/* घातer source */
	/* No IRQ 6 */
	CHTDC_TI_CCEOCAL = 7,	/* battery */
पूर्ण;

अटल स्थिर काष्ठा resource घातer_button_resources[] = अणु
	DEFINE_RES_IRQ(CHTDC_TI_PWRBTN),
पूर्ण;

अटल स्थिर काष्ठा resource thermal_resources[] = अणु
	DEFINE_RES_IRQ(CHTDC_TI_DIETMPWARN),
पूर्ण;

अटल स्थिर काष्ठा resource adc_resources[] = अणु
	DEFINE_RES_IRQ(CHTDC_TI_ADCCMPL),
पूर्ण;

अटल स्थिर काष्ठा resource pwrsrc_resources[] = अणु
	DEFINE_RES_IRQ(CHTDC_TI_VBUSDET),
पूर्ण;

अटल स्थिर काष्ठा resource battery_resources[] = अणु
	DEFINE_RES_IRQ(CHTDC_TI_VBATLOW),
	DEFINE_RES_IRQ(CHTDC_TI_CCEOCAL),
पूर्ण;

अटल काष्ठा mfd_cell chtdc_ti_dev[] = अणु
	अणु
		.name = "chtdc_ti_pwrbtn",
		.num_resources = ARRAY_SIZE(घातer_button_resources),
		.resources = घातer_button_resources,
	पूर्ण, अणु
		.name = "chtdc_ti_adc",
		.num_resources = ARRAY_SIZE(adc_resources),
		.resources = adc_resources,
	पूर्ण, अणु
		.name = "chtdc_ti_thermal",
		.num_resources = ARRAY_SIZE(thermal_resources),
		.resources = thermal_resources,
	पूर्ण, अणु
		.name = "chtdc_ti_pwrsrc",
		.num_resources = ARRAY_SIZE(pwrsrc_resources),
		.resources = pwrsrc_resources,
	पूर्ण, अणु
		.name = "chtdc_ti_battery",
		.num_resources = ARRAY_SIZE(battery_resources),
		.resources = battery_resources,
	पूर्ण,
	अणु	.name = "chtdc_ti_region", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config chtdc_ti_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 128,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq chtdc_ti_irqs[] = अणु
	REGMAP_IRQ_REG(CHTDC_TI_PWRBTN, 0, BIT(CHTDC_TI_PWRBTN)),
	REGMAP_IRQ_REG(CHTDC_TI_DIETMPWARN, 0, BIT(CHTDC_TI_DIETMPWARN)),
	REGMAP_IRQ_REG(CHTDC_TI_ADCCMPL, 0, BIT(CHTDC_TI_ADCCMPL)),
	REGMAP_IRQ_REG(CHTDC_TI_VBATLOW, 0, BIT(CHTDC_TI_VBATLOW)),
	REGMAP_IRQ_REG(CHTDC_TI_VBUSDET, 0, BIT(CHTDC_TI_VBUSDET)),
	REGMAP_IRQ_REG(CHTDC_TI_CCEOCAL, 0, BIT(CHTDC_TI_CCEOCAL)),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip chtdc_ti_irq_chip = अणु
	.name = KBUILD_MODNAME,
	.irqs = chtdc_ti_irqs,
	.num_irqs = ARRAY_SIZE(chtdc_ti_irqs),
	.num_regs = 1,
	.status_base = CHTDC_TI_IRQLVL1,
	.mask_base = CHTDC_TI_MASK_IRQLVL1,
	.ack_base = CHTDC_TI_IRQLVL1,
पूर्ण;

अटल पूर्णांक chtdc_ti_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	पूर्णांक ret;

	pmic = devm_kzalloc(dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, pmic);

	pmic->regmap = devm_regmap_init_i2c(i2c, &chtdc_ti_regmap_config);
	अगर (IS_ERR(pmic->regmap))
		वापस PTR_ERR(pmic->regmap);
	pmic->irq = i2c->irq;

	ret = devm_regmap_add_irq_chip(dev, pmic->regmap, pmic->irq,
				       IRQF_ONESHOT, 0,
				       &chtdc_ti_irq_chip,
				       &pmic->irq_chip_data);
	अगर (ret)
		वापस ret;

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE, chtdc_ti_dev,
				    ARRAY_SIZE(chtdc_ti_dev), शून्य, 0,
				    regmap_irq_get_करोमुख्य(pmic->irq_chip_data));
पूर्ण

अटल व्योम chtdc_ti_shutकरोwn(काष्ठा i2c_client *i2c)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = i2c_get_clientdata(i2c);

	disable_irq(pmic->irq);
पूर्ण

अटल पूर्णांक __maybe_unused chtdc_ti_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	disable_irq(pmic->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused chtdc_ti_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	enable_irq(pmic->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(chtdc_ti_pm_ops, chtdc_ti_suspend, chtdc_ti_resume);

अटल स्थिर काष्ठा acpi_device_id chtdc_ti_acpi_ids[] = अणु
	अणु "INT33F5" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, chtdc_ti_acpi_ids);

अटल काष्ठा i2c_driver chtdc_ti_i2c_driver = अणु
	.driver = अणु
		.name = "intel_soc_pmic_chtdc_ti",
		.pm = &chtdc_ti_pm_ops,
		.acpi_match_table = chtdc_ti_acpi_ids,
	पूर्ण,
	.probe_new = chtdc_ti_probe,
	.shutकरोwn = chtdc_ti_shutकरोwn,
पूर्ण;
module_i2c_driver(chtdc_ti_i2c_driver);

MODULE_DESCRIPTION("I2C driver for Intel SoC Dollar Cove TI PMIC");
MODULE_LICENSE("GPL v2");
