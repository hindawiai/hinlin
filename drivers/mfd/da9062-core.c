<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Core, IRQ and I2C device driver क्रम DA9061 and DA9062 PMICs
 * Copyright (C) 2015-2017  Dialog Semiconductor
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/da9062/core.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा	DA9062_REG_EVENT_A_OFFSET	0
#घोषणा	DA9062_REG_EVENT_B_OFFSET	1
#घोषणा	DA9062_REG_EVENT_C_OFFSET	2

#घोषणा	DA9062_IRQ_LOW	0
#घोषणा	DA9062_IRQ_HIGH	1

अटल काष्ठा regmap_irq da9061_irqs[] = अणु
	/* EVENT A */
	[DA9061_IRQ_ONKEY] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_NONKEY_MASK,
	पूर्ण,
	[DA9061_IRQ_WDG_WARN] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_WDG_WARN_MASK,
	पूर्ण,
	[DA9061_IRQ_SEQ_RDY] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_SEQ_RDY_MASK,
	पूर्ण,
	/* EVENT B */
	[DA9061_IRQ_TEMP] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_TEMP_MASK,
	पूर्ण,
	[DA9061_IRQ_LDO_LIM] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_LDO_LIM_MASK,
	पूर्ण,
	[DA9061_IRQ_DVC_RDY] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_DVC_RDY_MASK,
	पूर्ण,
	[DA9061_IRQ_VDD_WARN] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_VDD_WARN_MASK,
	पूर्ण,
	/* EVENT C */
	[DA9061_IRQ_GPI0] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI0_MASK,
	पूर्ण,
	[DA9061_IRQ_GPI1] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI1_MASK,
	पूर्ण,
	[DA9061_IRQ_GPI2] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI2_MASK,
	पूर्ण,
	[DA9061_IRQ_GPI3] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI3_MASK,
	पूर्ण,
	[DA9061_IRQ_GPI4] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip da9061_irq_chip = अणु
	.name = "da9061-irq",
	.irqs = da9061_irqs,
	.num_irqs = DA9061_NUM_IRQ,
	.num_regs = 3,
	.status_base = DA9062AA_EVENT_A,
	.mask_base = DA9062AA_IRQ_MASK_A,
	.ack_base = DA9062AA_EVENT_A,
पूर्ण;

अटल काष्ठा regmap_irq da9062_irqs[] = अणु
	/* EVENT A */
	[DA9062_IRQ_ONKEY] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_NONKEY_MASK,
	पूर्ण,
	[DA9062_IRQ_ALARM] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_ALARM_MASK,
	पूर्ण,
	[DA9062_IRQ_TICK] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_TICK_MASK,
	पूर्ण,
	[DA9062_IRQ_WDG_WARN] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_WDG_WARN_MASK,
	पूर्ण,
	[DA9062_IRQ_SEQ_RDY] = अणु
		.reg_offset = DA9062_REG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_SEQ_RDY_MASK,
	पूर्ण,
	/* EVENT B */
	[DA9062_IRQ_TEMP] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_TEMP_MASK,
	पूर्ण,
	[DA9062_IRQ_LDO_LIM] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_LDO_LIM_MASK,
	पूर्ण,
	[DA9062_IRQ_DVC_RDY] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_DVC_RDY_MASK,
	पूर्ण,
	[DA9062_IRQ_VDD_WARN] = अणु
		.reg_offset = DA9062_REG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_VDD_WARN_MASK,
	पूर्ण,
	/* EVENT C */
	[DA9062_IRQ_GPI0] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI0_MASK,
	पूर्ण,
	[DA9062_IRQ_GPI1] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI1_MASK,
	पूर्ण,
	[DA9062_IRQ_GPI2] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI2_MASK,
	पूर्ण,
	[DA9062_IRQ_GPI3] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI3_MASK,
	पूर्ण,
	[DA9062_IRQ_GPI4] = अणु
		.reg_offset = DA9062_REG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI4_MASK,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip da9062_irq_chip = अणु
	.name = "da9062-irq",
	.irqs = da9062_irqs,
	.num_irqs = DA9062_NUM_IRQ,
	.num_regs = 3,
	.status_base = DA9062AA_EVENT_A,
	.mask_base = DA9062AA_IRQ_MASK_A,
	.ack_base = DA9062AA_EVENT_A,
पूर्ण;

अटल स्थिर काष्ठा resource da9061_core_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9061_IRQ_VDD_WARN, "VDD_WARN"),
पूर्ण;

अटल स्थिर काष्ठा resource da9061_regulators_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9061_IRQ_LDO_LIM, "LDO_LIM"),
पूर्ण;

अटल स्थिर काष्ठा resource da9061_thermal_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9061_IRQ_TEMP, "THERMAL"),
पूर्ण;

अटल स्थिर काष्ठा resource da9061_wdt_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9061_IRQ_WDG_WARN, "WD_WARN"),
पूर्ण;

अटल स्थिर काष्ठा resource da9061_onkey_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(DA9061_IRQ_ONKEY, "ONKEY"),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell da9061_devs[] = अणु
	अणु
		.name		= "da9061-core",
		.num_resources	= ARRAY_SIZE(da9061_core_resources),
		.resources	= da9061_core_resources,
	पूर्ण,
	अणु
		.name		= "da9062-regulators",
		.num_resources	= ARRAY_SIZE(da9061_regulators_resources),
		.resources	= da9061_regulators_resources,
	पूर्ण,
	अणु
		.name		= "da9061-watchdog",
		.num_resources	= ARRAY_SIZE(da9061_wdt_resources),
		.resources	= da9061_wdt_resources,
		.of_compatible  = "dlg,da9061-watchdog",
	पूर्ण,
	अणु
		.name		= "da9061-thermal",
		.num_resources	= ARRAY_SIZE(da9061_thermal_resources),
		.resources	= da9061_thermal_resources,
		.of_compatible  = "dlg,da9061-thermal",
	पूर्ण,
	अणु
		.name		= "da9061-onkey",
		.num_resources	= ARRAY_SIZE(da9061_onkey_resources),
		.resources	= da9061_onkey_resources,
		.of_compatible = "dlg,da9061-onkey",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource da9062_core_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_VDD_WARN, 1, "VDD_WARN", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource da9062_regulators_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_LDO_LIM, 1, "LDO_LIM", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource da9062_thermal_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_TEMP, 1, "THERMAL", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource da9062_wdt_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_WDG_WARN, 1, "WD_WARN", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource da9062_rtc_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_ALARM, 1, "ALARM", IORESOURCE_IRQ),
	DEFINE_RES_NAMED(DA9062_IRQ_TICK, 1, "TICK", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource da9062_onkey_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_ONKEY, 1, "ONKEY", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource da9062_gpio_resources[] = अणु
	DEFINE_RES_NAMED(DA9062_IRQ_GPI0, 1, "GPI0", IORESOURCE_IRQ),
	DEFINE_RES_NAMED(DA9062_IRQ_GPI1, 1, "GPI1", IORESOURCE_IRQ),
	DEFINE_RES_NAMED(DA9062_IRQ_GPI2, 1, "GPI2", IORESOURCE_IRQ),
	DEFINE_RES_NAMED(DA9062_IRQ_GPI3, 1, "GPI3", IORESOURCE_IRQ),
	DEFINE_RES_NAMED(DA9062_IRQ_GPI4, 1, "GPI4", IORESOURCE_IRQ),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell da9062_devs[] = अणु
	अणु
		.name		= "da9062-core",
		.num_resources	= ARRAY_SIZE(da9062_core_resources),
		.resources	= da9062_core_resources,
	पूर्ण,
	अणु
		.name		= "da9062-regulators",
		.num_resources	= ARRAY_SIZE(da9062_regulators_resources),
		.resources	= da9062_regulators_resources,
	पूर्ण,
	अणु
		.name		= "da9062-watchdog",
		.num_resources	= ARRAY_SIZE(da9062_wdt_resources),
		.resources	= da9062_wdt_resources,
		.of_compatible  = "dlg,da9062-watchdog",
	पूर्ण,
	अणु
		.name		= "da9062-thermal",
		.num_resources	= ARRAY_SIZE(da9062_thermal_resources),
		.resources	= da9062_thermal_resources,
		.of_compatible  = "dlg,da9062-thermal",
	पूर्ण,
	अणु
		.name		= "da9062-rtc",
		.num_resources	= ARRAY_SIZE(da9062_rtc_resources),
		.resources	= da9062_rtc_resources,
		.of_compatible  = "dlg,da9062-rtc",
	पूर्ण,
	अणु
		.name		= "da9062-onkey",
		.num_resources	= ARRAY_SIZE(da9062_onkey_resources),
		.resources	= da9062_onkey_resources,
		.of_compatible	= "dlg,da9062-onkey",
	पूर्ण,
	अणु
		.name		= "da9062-gpio",
		.num_resources	= ARRAY_SIZE(da9062_gpio_resources),
		.resources	= da9062_gpio_resources,
		.of_compatible	= "dlg,da9062-gpio",
	पूर्ण,
पूर्ण;

अटल पूर्णांक da9062_clear_fault_log(काष्ठा da9062 *chip)
अणु
	पूर्णांक ret;
	पूर्णांक fault_log;

	ret = regmap_पढ़ो(chip->regmap, DA9062AA_FAULT_LOG, &fault_log);
	अगर (ret < 0)
		वापस ret;

	अगर (fault_log) अणु
		अगर (fault_log & DA9062AA_TWD_ERROR_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: TWD_ERROR\n");
		अगर (fault_log & DA9062AA_POR_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: POR\n");
		अगर (fault_log & DA9062AA_VDD_FAULT_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: VDD_FAULT\n");
		अगर (fault_log & DA9062AA_VDD_START_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: VDD_START\n");
		अगर (fault_log & DA9062AA_TEMP_CRIT_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: TEMP_CRIT\n");
		अगर (fault_log & DA9062AA_KEY_RESET_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: KEY_RESET\n");
		अगर (fault_log & DA9062AA_NSHUTDOWN_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: NSHUTDOWN\n");
		अगर (fault_log & DA9062AA_WAIT_SHUT_MASK)
			dev_dbg(chip->dev, "Fault log entry detected: WAIT_SHUT\n");

		ret = regmap_ग_लिखो(chip->regmap, DA9062AA_FAULT_LOG,
				   fault_log);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_get_device_type(काष्ठा da9062 *chip)
अणु
	पूर्णांक device_id, variant_id, variant_mrc, variant_vrc;
	अक्षर *type;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, DA9062AA_DEVICE_ID, &device_id);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Cannot read chip ID.\n");
		वापस -EIO;
	पूर्ण
	अगर (device_id != DA9062_PMIC_DEVICE_ID) अणु
		dev_err(chip->dev, "Invalid device ID: 0x%02x\n", device_id);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, DA9062AA_VARIANT_ID, &variant_id);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Cannot read chip variant id.\n");
		वापस -EIO;
	पूर्ण

	variant_vrc = (variant_id & DA9062AA_VRC_MASK) >> DA9062AA_VRC_SHIFT;

	चयन (variant_vrc) अणु
	हाल DA9062_PMIC_VARIANT_VRC_DA9061:
		type = "DA9061";
		अवरोध;
	हाल DA9062_PMIC_VARIANT_VRC_DA9062:
		type = "DA9062";
		अवरोध;
	शेष:
		type = "Unknown";
		अवरोध;
	पूर्ण

	dev_info(chip->dev,
		 "Device detected (device-ID: 0x%02X, var-ID: 0x%02X, %s)\n",
		 device_id, variant_id, type);

	variant_mrc = (variant_id & DA9062AA_MRC_MASK) >> DA9062AA_MRC_SHIFT;

	अगर (variant_mrc < DA9062_PMIC_VARIANT_MRC_AA) अणु
		dev_err(chip->dev,
			"Cannot support variant MRC: 0x%02X\n", variant_mrc);
		वापस -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 da9062_configure_irq_type(काष्ठा da9062 *chip, पूर्णांक irq, u32 *trigger)
अणु
	u32 irq_type = 0;
	काष्ठा irq_data *irq_data = irq_get_irq_data(irq);

	अगर (!irq_data) अणु
		dev_err(chip->dev, "Invalid IRQ: %d\n", irq);
		वापस -EINVAL;
	पूर्ण
	*trigger = irqd_get_trigger_type(irq_data);

	चयन (*trigger) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_type = DA9062_IRQ_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_type = DA9062_IRQ_LOW;
		अवरोध;
	शेष:
		dev_warn(chip->dev, "Unsupported IRQ type: %d\n", *trigger);
		वापस -EINVAL;
	पूर्ण
	वापस regmap_update_bits(chip->regmap, DA9062AA_CONFIG_A,
			DA9062AA_IRQ_TYPE_MASK,
			irq_type << DA9062AA_IRQ_TYPE_SHIFT);
पूर्ण

अटल स्थिर काष्ठा regmap_range da9061_aa_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	regmap_reg_range(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	regmap_reg_range(DA9062AA_IRQ_MASK_A, DA9062AA_IRQ_MASK_C),
	regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_GPIO_4),
	regmap_reg_range(DA9062AA_GPIO_WKUP_MODE, DA9062AA_GPIO_OUT3_4),
	regmap_reg_range(DA9062AA_BUCK1_CONT, DA9062AA_BUCK4_CONT),
	regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
	regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
	regmap_reg_range(DA9062AA_SEQ, DA9062AA_ID_4_3),
	regmap_reg_range(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	regmap_reg_range(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	regmap_reg_range(DA9062AA_SEQ_A, DA9062AA_WAIT),
	regmap_reg_range(DA9062AA_RESET, DA9062AA_BUCK_ILIM_C),
	regmap_reg_range(DA9062AA_BUCK1_CFG, DA9062AA_BUCK3_CFG),
	regmap_reg_range(DA9062AA_VBUCK1_A, DA9062AA_VBUCK4_A),
	regmap_reg_range(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	regmap_reg_range(DA9062AA_VLDO1_A, DA9062AA_VLDO4_A),
	regmap_reg_range(DA9062AA_CONFIG_A, DA9062AA_CONFIG_A),
	regmap_reg_range(DA9062AA_VBUCK1_B, DA9062AA_VBUCK4_B),
	regmap_reg_range(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	regmap_reg_range(DA9062AA_VLDO1_B, DA9062AA_VLDO4_B),
	regmap_reg_range(DA9062AA_INTERFACE, DA9062AA_CONFIG_E),
	regmap_reg_range(DA9062AA_CONFIG_G, DA9062AA_CONFIG_K),
	regmap_reg_range(DA9062AA_CONFIG_M, DA9062AA_CONFIG_M),
	regmap_reg_range(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
	regmap_reg_range(DA9062AA_DEVICE_ID, DA9062AA_CONFIG_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9061_aa_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_PAGE_CON),
	regmap_reg_range(DA9062AA_FAULT_LOG, DA9062AA_EVENT_C),
	regmap_reg_range(DA9062AA_IRQ_MASK_A, DA9062AA_IRQ_MASK_C),
	regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_GPIO_4),
	regmap_reg_range(DA9062AA_GPIO_WKUP_MODE, DA9062AA_GPIO_OUT3_4),
	regmap_reg_range(DA9062AA_BUCK1_CONT, DA9062AA_BUCK4_CONT),
	regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
	regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
	regmap_reg_range(DA9062AA_SEQ, DA9062AA_ID_4_3),
	regmap_reg_range(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	regmap_reg_range(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	regmap_reg_range(DA9062AA_SEQ_A, DA9062AA_WAIT),
	regmap_reg_range(DA9062AA_RESET, DA9062AA_BUCK_ILIM_C),
	regmap_reg_range(DA9062AA_BUCK1_CFG, DA9062AA_BUCK3_CFG),
	regmap_reg_range(DA9062AA_VBUCK1_A, DA9062AA_VBUCK4_A),
	regmap_reg_range(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	regmap_reg_range(DA9062AA_VLDO1_A, DA9062AA_VLDO4_A),
	regmap_reg_range(DA9062AA_CONFIG_A, DA9062AA_CONFIG_A),
	regmap_reg_range(DA9062AA_VBUCK1_B, DA9062AA_VBUCK4_B),
	regmap_reg_range(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	regmap_reg_range(DA9062AA_VLDO1_B, DA9062AA_VLDO4_B),
	regmap_reg_range(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9061_aa_अस्थिर_ranges[] = अणु
	regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	regmap_reg_range(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_CONTROL_B),
	regmap_reg_range(DA9062AA_CONTROL_E, DA9062AA_CONTROL_F),
	regmap_reg_range(DA9062AA_BUCK1_CONT, DA9062AA_BUCK4_CONT),
	regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
	regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
	regmap_reg_range(DA9062AA_SEQ, DA9062AA_SEQ),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9061_aa_पढ़ोable_table = अणु
	.yes_ranges = da9061_aa_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9061_aa_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9061_aa_ग_लिखोable_table = अणु
	.yes_ranges = da9061_aa_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9061_aa_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9061_aa_अस्थिर_table = अणु
	.yes_ranges = da9061_aa_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9061_aa_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg da9061_range_cfg[] = अणु
	अणु
		.range_min = DA9062AA_PAGE_CON,
		.range_max = DA9062AA_CONFIG_ID,
		.selector_reg = DA9062AA_PAGE_CON,
		.selector_mask = 1 << DA9062_I2C_PAGE_SEL_SHIFT,
		.selector_shअगरt = DA9062_I2C_PAGE_SEL_SHIFT,
		.winकरोw_start = 0,
		.winकरोw_len = 256,
	पूर्ण
पूर्ण;

अटल काष्ठा regmap_config da9061_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ranges = da9061_range_cfg,
	.num_ranges = ARRAY_SIZE(da9061_range_cfg),
	.max_रेजिस्टर = DA9062AA_CONFIG_ID,
	.cache_type = REGCACHE_RBTREE,
	.rd_table = &da9061_aa_पढ़ोable_table,
	.wr_table = &da9061_aa_ग_लिखोable_table,
	.अस्थिर_table = &da9061_aa_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9062_aa_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	regmap_reg_range(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	regmap_reg_range(DA9062AA_IRQ_MASK_A, DA9062AA_IRQ_MASK_C),
	regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_GPIO_4),
	regmap_reg_range(DA9062AA_GPIO_WKUP_MODE, DA9062AA_BUCK4_CONT),
	regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
	regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
	regmap_reg_range(DA9062AA_COUNT_S, DA9062AA_SECOND_D),
	regmap_reg_range(DA9062AA_SEQ, DA9062AA_ID_4_3),
	regmap_reg_range(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	regmap_reg_range(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	regmap_reg_range(DA9062AA_SEQ_A, DA9062AA_BUCK3_CFG),
	regmap_reg_range(DA9062AA_VBUCK2_A, DA9062AA_VBUCK4_A),
	regmap_reg_range(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	regmap_reg_range(DA9062AA_VLDO1_A, DA9062AA_VLDO4_A),
	regmap_reg_range(DA9062AA_VBUCK2_B, DA9062AA_VBUCK4_B),
	regmap_reg_range(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	regmap_reg_range(DA9062AA_VLDO1_B, DA9062AA_VLDO4_B),
	regmap_reg_range(DA9062AA_BBAT_CONT, DA9062AA_BBAT_CONT),
	regmap_reg_range(DA9062AA_INTERFACE, DA9062AA_CONFIG_E),
	regmap_reg_range(DA9062AA_CONFIG_G, DA9062AA_CONFIG_K),
	regmap_reg_range(DA9062AA_CONFIG_M, DA9062AA_CONFIG_M),
	regmap_reg_range(DA9062AA_TRIM_CLDR, DA9062AA_GP_ID_19),
	regmap_reg_range(DA9062AA_DEVICE_ID, DA9062AA_CONFIG_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9062_aa_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_PAGE_CON),
	regmap_reg_range(DA9062AA_FAULT_LOG, DA9062AA_EVENT_C),
	regmap_reg_range(DA9062AA_IRQ_MASK_A, DA9062AA_IRQ_MASK_C),
	regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_GPIO_4),
	regmap_reg_range(DA9062AA_GPIO_WKUP_MODE, DA9062AA_BUCK4_CONT),
	regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
	regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
	regmap_reg_range(DA9062AA_COUNT_S, DA9062AA_ALARM_Y),
	regmap_reg_range(DA9062AA_SEQ, DA9062AA_ID_4_3),
	regmap_reg_range(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	regmap_reg_range(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	regmap_reg_range(DA9062AA_SEQ_A, DA9062AA_BUCK3_CFG),
	regmap_reg_range(DA9062AA_VBUCK2_A, DA9062AA_VBUCK4_A),
	regmap_reg_range(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	regmap_reg_range(DA9062AA_VLDO1_A, DA9062AA_VLDO4_A),
	regmap_reg_range(DA9062AA_VBUCK2_B, DA9062AA_VBUCK4_B),
	regmap_reg_range(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	regmap_reg_range(DA9062AA_VLDO1_B, DA9062AA_VLDO4_B),
	regmap_reg_range(DA9062AA_BBAT_CONT, DA9062AA_BBAT_CONT),
	regmap_reg_range(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9062_aa_अस्थिर_ranges[] = अणु
	regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	regmap_reg_range(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_CONTROL_B),
	regmap_reg_range(DA9062AA_CONTROL_E, DA9062AA_CONTROL_F),
	regmap_reg_range(DA9062AA_BUCK2_CONT, DA9062AA_BUCK4_CONT),
	regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
	regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
	regmap_reg_range(DA9062AA_COUNT_S, DA9062AA_SECOND_D),
	regmap_reg_range(DA9062AA_SEQ, DA9062AA_SEQ),
	regmap_reg_range(DA9062AA_EN_32K, DA9062AA_EN_32K),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9062_aa_पढ़ोable_table = अणु
	.yes_ranges = da9062_aa_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9062_aa_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9062_aa_ग_लिखोable_table = अणु
	.yes_ranges = da9062_aa_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9062_aa_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9062_aa_अस्थिर_table = अणु
	.yes_ranges = da9062_aa_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9062_aa_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg da9062_range_cfg[] = अणु
	अणु
		.range_min = DA9062AA_PAGE_CON,
		.range_max = DA9062AA_CONFIG_ID,
		.selector_reg = DA9062AA_PAGE_CON,
		.selector_mask = 1 << DA9062_I2C_PAGE_SEL_SHIFT,
		.selector_shअगरt = DA9062_I2C_PAGE_SEL_SHIFT,
		.winकरोw_start = 0,
		.winकरोw_len = 256,
	पूर्ण
पूर्ण;

अटल काष्ठा regmap_config da9062_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ranges = da9062_range_cfg,
	.num_ranges = ARRAY_SIZE(da9062_range_cfg),
	.max_रेजिस्टर = DA9062AA_CONFIG_ID,
	.cache_type = REGCACHE_RBTREE,
	.rd_table = &da9062_aa_पढ़ोable_table,
	.wr_table = &da9062_aa_ग_लिखोable_table,
	.अस्थिर_table = &da9062_aa_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा of_device_id da9062_dt_ids[] = अणु
	अणु .compatible = "dlg,da9061", .data = (व्योम *)COMPAT_TYPE_DA9061, पूर्ण,
	अणु .compatible = "dlg,da9062", .data = (व्योम *)COMPAT_TYPE_DA9062, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da9062_dt_ids);

अटल पूर्णांक da9062_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9062 *chip;
	स्थिर काष्ठा of_device_id *match;
	अचिन्हित पूर्णांक irq_base;
	स्थिर काष्ठा mfd_cell *cell;
	स्थिर काष्ठा regmap_irq_chip *irq_chip;
	स्थिर काष्ठा regmap_config *config;
	पूर्णांक cell_num;
	u32 trigger_type = 0;
	पूर्णांक ret;

	chip = devm_kzalloc(&i2c->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	अगर (i2c->dev.of_node) अणु
		match = of_match_node(da9062_dt_ids, i2c->dev.of_node);
		अगर (!match)
			वापस -EINVAL;

		chip->chip_type = (uपूर्णांकptr_t)match->data;
	पूर्ण अन्यथा अणु
		chip->chip_type = id->driver_data;
	पूर्ण

	i2c_set_clientdata(i2c, chip);
	chip->dev = &i2c->dev;

	अगर (!i2c->irq) अणु
		dev_err(chip->dev, "No IRQ configured\n");
		वापस -EINVAL;
	पूर्ण

	चयन (chip->chip_type) अणु
	हाल COMPAT_TYPE_DA9061:
		cell = da9061_devs;
		cell_num = ARRAY_SIZE(da9061_devs);
		irq_chip = &da9061_irq_chip;
		config = &da9061_regmap_config;
		अवरोध;
	हाल COMPAT_TYPE_DA9062:
		cell = da9062_devs;
		cell_num = ARRAY_SIZE(da9062_devs);
		irq_chip = &da9062_irq_chip;
		config = &da9062_regmap_config;
		अवरोध;
	शेष:
		dev_err(chip->dev, "Unrecognised chip type\n");
		वापस -ENODEV;
	पूर्ण

	chip->regmap = devm_regmap_init_i2c(i2c, config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = da9062_clear_fault_log(chip);
	अगर (ret < 0)
		dev_warn(chip->dev, "Cannot clear fault log\n");

	ret = da9062_get_device_type(chip);
	अगर (ret)
		वापस ret;

	ret = da9062_configure_irq_type(chip, i2c->irq, &trigger_type);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to configure IRQ type\n");
		वापस ret;
	पूर्ण

	ret = regmap_add_irq_chip(chip->regmap, i2c->irq,
			trigger_type | IRQF_SHARED | IRQF_ONESHOT,
			-1, irq_chip, &chip->regmap_irq);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to request IRQ %d: %d\n",
			i2c->irq, ret);
		वापस ret;
	पूर्ण

	irq_base = regmap_irq_chip_get_base(chip->regmap_irq);

	ret = mfd_add_devices(chip->dev, PLATFORM_DEVID_NONE, cell,
			      cell_num, शून्य, irq_base,
			      शून्य);
	अगर (ret) अणु
		dev_err(chip->dev, "Cannot register child devices\n");
		regmap_del_irq_chip(i2c->irq, chip->regmap_irq);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा da9062 *chip = i2c_get_clientdata(i2c);

	mfd_हटाओ_devices(chip->dev);
	regmap_del_irq_chip(i2c->irq, chip->regmap_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9062_i2c_id[] = अणु
	अणु "da9061", COMPAT_TYPE_DA9061 पूर्ण,
	अणु "da9062", COMPAT_TYPE_DA9062 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9062_i2c_id);

अटल काष्ठा i2c_driver da9062_i2c_driver = अणु
	.driver = अणु
		.name = "da9062",
		.of_match_table = da9062_dt_ids,
	पूर्ण,
	.probe    = da9062_i2c_probe,
	.हटाओ   = da9062_i2c_हटाओ,
	.id_table = da9062_i2c_id,
पूर्ण;

module_i2c_driver(da9062_i2c_driver);

MODULE_DESCRIPTION("Core device driver for Dialog DA9061 and DA9062");
MODULE_AUTHOR("Steve Twiss <stwiss.opensource@diasemi.com>");
MODULE_LICENSE("GPL");
