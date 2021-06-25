<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device access क्रम Dialog DA9055 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/irq.h>
#समावेश <linux/mutex.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/pdata.h>
#समावेश <linux/mfd/da9055/reg.h>

#घोषणा DA9055_IRQ_NONKEY_MASK		0x01
#घोषणा DA9055_IRQ_ALM_MASK		0x02
#घोषणा DA9055_IRQ_TICK_MASK		0x04
#घोषणा DA9055_IRQ_ADC_MASK		0x08
#घोषणा DA9055_IRQ_BUCK_ILIM_MASK	0x08

अटल bool da9055_रेजिस्टर_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9055_REG_STATUS_A:
	हाल DA9055_REG_STATUS_B:
	हाल DA9055_REG_EVENT_A:
	हाल DA9055_REG_EVENT_B:
	हाल DA9055_REG_EVENT_C:
	हाल DA9055_REG_IRQ_MASK_A:
	हाल DA9055_REG_IRQ_MASK_B:
	हाल DA9055_REG_IRQ_MASK_C:

	हाल DA9055_REG_CONTROL_A:
	हाल DA9055_REG_CONTROL_B:
	हाल DA9055_REG_CONTROL_C:
	हाल DA9055_REG_CONTROL_D:
	हाल DA9055_REG_CONTROL_E:

	हाल DA9055_REG_ADC_MAN:
	हाल DA9055_REG_ADC_CONT:
	हाल DA9055_REG_VSYS_MON:
	हाल DA9055_REG_ADC_RES_L:
	हाल DA9055_REG_ADC_RES_H:
	हाल DA9055_REG_VSYS_RES:
	हाल DA9055_REG_ADCIN1_RES:
	हाल DA9055_REG_ADCIN2_RES:
	हाल DA9055_REG_ADCIN3_RES:

	हाल DA9055_REG_COUNT_S:
	हाल DA9055_REG_COUNT_MI:
	हाल DA9055_REG_COUNT_H:
	हाल DA9055_REG_COUNT_D:
	हाल DA9055_REG_COUNT_MO:
	हाल DA9055_REG_COUNT_Y:
	हाल DA9055_REG_ALARM_H:
	हाल DA9055_REG_ALARM_D:
	हाल DA9055_REG_ALARM_MI:
	हाल DA9055_REG_ALARM_MO:
	हाल DA9055_REG_ALARM_Y:

	हाल DA9055_REG_GPIO0_1:
	हाल DA9055_REG_GPIO2:
	हाल DA9055_REG_GPIO_MODE0_2:

	हाल DA9055_REG_BCORE_CONT:
	हाल DA9055_REG_BMEM_CONT:
	हाल DA9055_REG_LDO1_CONT:
	हाल DA9055_REG_LDO2_CONT:
	हाल DA9055_REG_LDO3_CONT:
	हाल DA9055_REG_LDO4_CONT:
	हाल DA9055_REG_LDO5_CONT:
	हाल DA9055_REG_LDO6_CONT:
	हाल DA9055_REG_BUCK_LIM:
	हाल DA9055_REG_BCORE_MODE:
	हाल DA9055_REG_VBCORE_A:
	हाल DA9055_REG_VBMEM_A:
	हाल DA9055_REG_VLDO1_A:
	हाल DA9055_REG_VLDO2_A:
	हाल DA9055_REG_VLDO3_A:
	हाल DA9055_REG_VLDO4_A:
	हाल DA9055_REG_VLDO5_A:
	हाल DA9055_REG_VLDO6_A:
	हाल DA9055_REG_VBCORE_B:
	हाल DA9055_REG_VBMEM_B:
	हाल DA9055_REG_VLDO1_B:
	हाल DA9055_REG_VLDO2_B:
	हाल DA9055_REG_VLDO3_B:
	हाल DA9055_REG_VLDO4_B:
	हाल DA9055_REG_VLDO5_B:
	हाल DA9055_REG_VLDO6_B:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool da9055_रेजिस्टर_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9055_REG_STATUS_A:
	हाल DA9055_REG_STATUS_B:
	हाल DA9055_REG_EVENT_A:
	हाल DA9055_REG_EVENT_B:
	हाल DA9055_REG_EVENT_C:
	हाल DA9055_REG_IRQ_MASK_A:
	हाल DA9055_REG_IRQ_MASK_B:
	हाल DA9055_REG_IRQ_MASK_C:

	हाल DA9055_REG_CONTROL_A:
	हाल DA9055_REG_CONTROL_B:
	हाल DA9055_REG_CONTROL_C:
	हाल DA9055_REG_CONTROL_D:
	हाल DA9055_REG_CONTROL_E:

	हाल DA9055_REG_ADC_MAN:
	हाल DA9055_REG_ADC_CONT:
	हाल DA9055_REG_VSYS_MON:
	हाल DA9055_REG_ADC_RES_L:
	हाल DA9055_REG_ADC_RES_H:
	हाल DA9055_REG_VSYS_RES:
	हाल DA9055_REG_ADCIN1_RES:
	हाल DA9055_REG_ADCIN2_RES:
	हाल DA9055_REG_ADCIN3_RES:

	हाल DA9055_REG_COUNT_S:
	हाल DA9055_REG_COUNT_MI:
	हाल DA9055_REG_COUNT_H:
	हाल DA9055_REG_COUNT_D:
	हाल DA9055_REG_COUNT_MO:
	हाल DA9055_REG_COUNT_Y:
	हाल DA9055_REG_ALARM_H:
	हाल DA9055_REG_ALARM_D:
	हाल DA9055_REG_ALARM_MI:
	हाल DA9055_REG_ALARM_MO:
	हाल DA9055_REG_ALARM_Y:

	हाल DA9055_REG_GPIO0_1:
	हाल DA9055_REG_GPIO2:
	हाल DA9055_REG_GPIO_MODE0_2:

	हाल DA9055_REG_BCORE_CONT:
	हाल DA9055_REG_BMEM_CONT:
	हाल DA9055_REG_LDO1_CONT:
	हाल DA9055_REG_LDO2_CONT:
	हाल DA9055_REG_LDO3_CONT:
	हाल DA9055_REG_LDO4_CONT:
	हाल DA9055_REG_LDO5_CONT:
	हाल DA9055_REG_LDO6_CONT:
	हाल DA9055_REG_BUCK_LIM:
	हाल DA9055_REG_BCORE_MODE:
	हाल DA9055_REG_VBCORE_A:
	हाल DA9055_REG_VBMEM_A:
	हाल DA9055_REG_VLDO1_A:
	हाल DA9055_REG_VLDO2_A:
	हाल DA9055_REG_VLDO3_A:
	हाल DA9055_REG_VLDO4_A:
	हाल DA9055_REG_VLDO5_A:
	हाल DA9055_REG_VLDO6_A:
	हाल DA9055_REG_VBCORE_B:
	हाल DA9055_REG_VBMEM_B:
	हाल DA9055_REG_VLDO1_B:
	हाल DA9055_REG_VLDO2_B:
	हाल DA9055_REG_VLDO3_B:
	हाल DA9055_REG_VLDO4_B:
	हाल DA9055_REG_VLDO5_B:
	हाल DA9055_REG_VLDO6_B:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool da9055_रेजिस्टर_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9055_REG_STATUS_A:
	हाल DA9055_REG_STATUS_B:
	हाल DA9055_REG_EVENT_A:
	हाल DA9055_REG_EVENT_B:
	हाल DA9055_REG_EVENT_C:

	हाल DA9055_REG_CONTROL_A:
	हाल DA9055_REG_CONTROL_E:

	हाल DA9055_REG_ADC_MAN:
	हाल DA9055_REG_ADC_RES_L:
	हाल DA9055_REG_ADC_RES_H:
	हाल DA9055_REG_VSYS_RES:
	हाल DA9055_REG_ADCIN1_RES:
	हाल DA9055_REG_ADCIN2_RES:
	हाल DA9055_REG_ADCIN3_RES:

	हाल DA9055_REG_COUNT_S:
	हाल DA9055_REG_COUNT_MI:
	हाल DA9055_REG_COUNT_H:
	हाल DA9055_REG_COUNT_D:
	हाल DA9055_REG_COUNT_MO:
	हाल DA9055_REG_COUNT_Y:
	हाल DA9055_REG_ALARM_MI:

	हाल DA9055_REG_BCORE_CONT:
	हाल DA9055_REG_BMEM_CONT:
	हाल DA9055_REG_LDO1_CONT:
	हाल DA9055_REG_LDO2_CONT:
	हाल DA9055_REG_LDO3_CONT:
	हाल DA9055_REG_LDO4_CONT:
	हाल DA9055_REG_LDO5_CONT:
	हाल DA9055_REG_LDO6_CONT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_irq da9055_irqs[] = अणु
	[DA9055_IRQ_NONKEY] = अणु
		.reg_offset = 0,
		.mask = DA9055_IRQ_NONKEY_MASK,
	पूर्ण,
	[DA9055_IRQ_ALARM] = अणु
		.reg_offset = 0,
		.mask = DA9055_IRQ_ALM_MASK,
	पूर्ण,
	[DA9055_IRQ_TICK] = अणु
		.reg_offset = 0,
		.mask = DA9055_IRQ_TICK_MASK,
	पूर्ण,
	[DA9055_IRQ_HWMON] = अणु
		.reg_offset = 0,
		.mask = DA9055_IRQ_ADC_MASK,
	पूर्ण,
	[DA9055_IRQ_REGULATOR] = अणु
		.reg_offset = 1,
		.mask = DA9055_IRQ_BUCK_ILIM_MASK,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_config da9055_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.cache_type = REGCACHE_RBTREE,

	.max_रेजिस्टर = DA9055_MAX_REGISTER_CNT,
	.पढ़ोable_reg = da9055_रेजिस्टर_पढ़ोable,
	.ग_लिखोable_reg = da9055_रेजिस्टर_ग_लिखोable,
	.अस्थिर_reg = da9055_रेजिस्टर_अस्थिर,
पूर्ण;
EXPORT_SYMBOL_GPL(da9055_regmap_config);

अटल स्थिर काष्ठा resource da9055_onkey_resource = अणु
	.name = "ONKEY",
	.start = DA9055_IRQ_NONKEY,
	.end   = DA9055_IRQ_NONKEY,
	.flags = IORESOURCE_IRQ,
पूर्ण;

अटल स्थिर काष्ठा resource da9055_rtc_resource[] = अणु
	अणु
		.name = "ALM",
		.start = DA9055_IRQ_ALARM,
		.end   = DA9055_IRQ_ALARM,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name = "TICK",
		.start = DA9055_IRQ_TICK,
		.end   = DA9055_IRQ_TICK,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource da9055_hwmon_resource = अणु
	.name = "HWMON",
	.start = DA9055_IRQ_HWMON,
	.end   = DA9055_IRQ_HWMON,
	.flags = IORESOURCE_IRQ,
पूर्ण;

अटल स्थिर काष्ठा resource da9055_ld05_6_resource = अणु
	.name = "REGULATOR",
	.start = DA9055_IRQ_REGULATOR,
	.end   = DA9055_IRQ_REGULATOR,
	.flags = IORESOURCE_IRQ,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell da9055_devs[] = अणु
	अणु
		.of_compatible = "dlg,da9055-gpio",
		.name = "da9055-gpio",
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 1,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 2,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 3,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 4,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 5,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 6,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.id = 7,
		.resources = &da9055_ld05_6_resource,
		.num_resources = 1,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-regulator",
		.name = "da9055-regulator",
		.resources = &da9055_ld05_6_resource,
		.num_resources = 1,
		.id = 8,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-onkey",
		.name = "da9055-onkey",
		.resources = &da9055_onkey_resource,
		.num_resources = 1,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-rtc",
		.name = "da9055-rtc",
		.resources = da9055_rtc_resource,
		.num_resources = ARRAY_SIZE(da9055_rtc_resource),
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-hwmon",
		.name = "da9055-hwmon",
		.resources = &da9055_hwmon_resource,
		.num_resources = 1,
	पूर्ण,
	अणु
		.of_compatible = "dlg,da9055-watchdog",
		.name = "da9055-watchdog",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip da9055_regmap_irq_chip = अणु
	.name = "da9055_irq",
	.status_base = DA9055_REG_EVENT_A,
	.mask_base = DA9055_REG_IRQ_MASK_A,
	.ack_base = DA9055_REG_EVENT_A,
	.num_regs = 3,
	.irqs = da9055_irqs,
	.num_irqs = ARRAY_SIZE(da9055_irqs),
पूर्ण;

पूर्णांक da9055_device_init(काष्ठा da9055 *da9055)
अणु
	काष्ठा da9055_pdata *pdata = dev_get_platdata(da9055->dev);
	पूर्णांक ret;
	uपूर्णांक8_t clear_events[3] = अणु0xFF, 0xFF, 0xFFपूर्ण;

	अगर (pdata && pdata->init != शून्य)
		pdata->init(da9055);

	अगर (!pdata || !pdata->irq_base)
		da9055->irq_base = -1;
	अन्यथा
		da9055->irq_base = pdata->irq_base;

	ret = da9055_group_ग_लिखो(da9055, DA9055_REG_EVENT_A, 3, clear_events);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_add_irq_chip(da9055->regmap, da9055->chip_irq,
				  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				  da9055->irq_base, &da9055_regmap_irq_chip,
				  &da9055->irq_data);
	अगर (ret < 0)
		वापस ret;

	da9055->irq_base = regmap_irq_chip_get_base(da9055->irq_data);

	ret = mfd_add_devices(da9055->dev, -1,
			      da9055_devs, ARRAY_SIZE(da9055_devs),
			      शून्य, da9055->irq_base, शून्य);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	mfd_हटाओ_devices(da9055->dev);
	वापस ret;
पूर्ण

व्योम da9055_device_निकास(काष्ठा da9055 *da9055)
अणु
	regmap_del_irq_chip(da9055->chip_irq, da9055->irq_data);
	mfd_हटाओ_devices(da9055->dev);
पूर्ण

MODULE_DESCRIPTION("Core support for the DA9055 PMIC");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
