<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * XPower AXP288 PMIC operation region driver
 *
 * Copyright (C) 2014 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/iosf_mbi.h>
#समावेश "intel_pmic.h"

#घोषणा XPOWER_GPADC_LOW	0x5b
#घोषणा XPOWER_GPI1_CTRL	0x92

#घोषणा GPI1_LDO_MASK		GENMASK(2, 0)
#घोषणा GPI1_LDO_ON		(3 << 0)
#घोषणा GPI1_LDO_OFF		(4 << 0)

#घोषणा AXP288_ADC_TS_CURRENT_ON_OFF_MASK		GENMASK(1, 0)
#घोषणा AXP288_ADC_TS_CURRENT_OFF			(0 << 0)
#घोषणा AXP288_ADC_TS_CURRENT_ON_WHEN_CHARGING		(1 << 0)
#घोषणा AXP288_ADC_TS_CURRENT_ON_ONDEMAND		(2 << 0)
#घोषणा AXP288_ADC_TS_CURRENT_ON			(3 << 0)

अटल काष्ठा pmic_table घातer_table[] = अणु
	अणु
		.address = 0x00,
		.reg = 0x13,
		.bit = 0x05,
	पूर्ण, /* ALD1 */
	अणु
		.address = 0x04,
		.reg = 0x13,
		.bit = 0x06,
	पूर्ण, /* ALD2 */
	अणु
		.address = 0x08,
		.reg = 0x13,
		.bit = 0x07,
	पूर्ण, /* ALD3 */
	अणु
		.address = 0x0c,
		.reg = 0x12,
		.bit = 0x03,
	पूर्ण, /* DLD1 */
	अणु
		.address = 0x10,
		.reg = 0x12,
		.bit = 0x04,
	पूर्ण, /* DLD2 */
	अणु
		.address = 0x14,
		.reg = 0x12,
		.bit = 0x05,
	पूर्ण, /* DLD3 */
	अणु
		.address = 0x18,
		.reg = 0x12,
		.bit = 0x06,
	पूर्ण, /* DLD4 */
	अणु
		.address = 0x1c,
		.reg = 0x12,
		.bit = 0x00,
	पूर्ण, /* ELD1 */
	अणु
		.address = 0x20,
		.reg = 0x12,
		.bit = 0x01,
	पूर्ण, /* ELD2 */
	अणु
		.address = 0x24,
		.reg = 0x12,
		.bit = 0x02,
	पूर्ण, /* ELD3 */
	अणु
		.address = 0x28,
		.reg = 0x13,
		.bit = 0x02,
	पूर्ण, /* FLD1 */
	अणु
		.address = 0x2c,
		.reg = 0x13,
		.bit = 0x03,
	पूर्ण, /* FLD2 */
	अणु
		.address = 0x30,
		.reg = 0x13,
		.bit = 0x04,
	पूर्ण, /* FLD3 */
	अणु
		.address = 0x34,
		.reg = 0x10,
		.bit = 0x03,
	पूर्ण, /* BUC1 */
	अणु
		.address = 0x38,
		.reg = 0x10,
		.bit = 0x06,
	पूर्ण, /* BUC2 */
	अणु
		.address = 0x3c,
		.reg = 0x10,
		.bit = 0x05,
	पूर्ण, /* BUC3 */
	अणु
		.address = 0x40,
		.reg = 0x10,
		.bit = 0x04,
	पूर्ण, /* BUC4 */
	अणु
		.address = 0x44,
		.reg = 0x10,
		.bit = 0x01,
	पूर्ण, /* BUC5 */
	अणु
		.address = 0x48,
		.reg = 0x10,
		.bit = 0x00
	पूर्ण, /* BUC6 */
	अणु
		.address = 0x4c,
		.reg = 0x92,
	पूर्ण, /* GPI1 */
पूर्ण;

/* TMP0 - TMP5 are the same, all from GPADC */
अटल काष्ठा pmic_table thermal_table[] = अणु
	अणु
		.address = 0x00,
		.reg = XPOWER_GPADC_LOW
	पूर्ण,
	अणु
		.address = 0x0c,
		.reg = XPOWER_GPADC_LOW
	पूर्ण,
	अणु
		.address = 0x18,
		.reg = XPOWER_GPADC_LOW
	पूर्ण,
	अणु
		.address = 0x24,
		.reg = XPOWER_GPADC_LOW
	पूर्ण,
	अणु
		.address = 0x30,
		.reg = XPOWER_GPADC_LOW
	पूर्ण,
	अणु
		.address = 0x3c,
		.reg = XPOWER_GPADC_LOW
	पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकel_xघातer_pmic_get_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
				       पूर्णांक bit, u64 *value)
अणु
	पूर्णांक data;

	अगर (regmap_पढ़ो(regmap, reg, &data))
		वापस -EIO;

	/* GPIO1 LDO regulator needs special handling */
	अगर (reg == XPOWER_GPI1_CTRL)
		*value = ((data & GPI1_LDO_MASK) == GPI1_LDO_ON);
	अन्यथा
		*value = (data & BIT(bit)) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_xघातer_pmic_update_घातer(काष्ठा regmap *regmap, पूर्णांक reg,
					  पूर्णांक bit, bool on)
अणु
	पूर्णांक data, ret;

	/* GPIO1 LDO regulator needs special handling */
	अगर (reg == XPOWER_GPI1_CTRL)
		वापस regmap_update_bits(regmap, reg, GPI1_LDO_MASK,
					  on ? GPI1_LDO_ON : GPI1_LDO_OFF);

	ret = iosf_mbi_block_punit_i2c_access();
	अगर (ret)
		वापस ret;

	अगर (regmap_पढ़ो(regmap, reg, &data)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (on)
		data |= BIT(bit);
	अन्यथा
		data &= ~BIT(bit);

	अगर (regmap_ग_लिखो(regmap, reg, data))
		ret = -EIO;
out:
	iosf_mbi_unblock_punit_i2c_access();

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_xघातer_pmic_get_raw_temp(): Get raw temperature पढ़ोing from the PMIC
 *
 * @regmap: regmap of the PMIC device
 * @reg: रेजिस्टर to get the पढ़ोing
 *
 * Return a positive value on success, त्रुटि_सं on failure.
 */
अटल पूर्णांक पूर्णांकel_xघातer_pmic_get_raw_temp(काष्ठा regmap *regmap, पूर्णांक reg)
अणु
	पूर्णांक ret, adc_ts_pin_ctrl;
	u8 buf[2];

	/*
	 * The current-source used क्रम the battery temp-sensor (TS) is shared
	 * with the GPADC. For proper fuel-gauge and अक्षरger operation the TS
	 * current-source needs to be permanently on. But to पढ़ो the GPADC we
	 * need to temporary चयन the TS current-source to ondemand, so that
	 * the GPADC can use it, otherwise we will always पढ़ो an all 0 value.
	 *
	 * Note that the चयनing from on to on-ondemand is not necessary
	 * when the TS current-source is off (this happens on devices which
	 * करो not use the TS-pin).
	 */
	ret = regmap_पढ़ो(regmap, AXP288_ADC_TS_PIN_CTRL, &adc_ts_pin_ctrl);
	अगर (ret)
		वापस ret;

	अगर (adc_ts_pin_ctrl & AXP288_ADC_TS_CURRENT_ON_OFF_MASK) अणु
		ret = regmap_update_bits(regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_CURRENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CURRENT_ON_ONDEMAND);
		अगर (ret)
			वापस ret;

		/* Wait a bit after चयनing the current-source */
		usleep_range(6000, 10000);
	पूर्ण

	ret = regmap_bulk_पढ़ो(regmap, AXP288_GP_ADC_H, buf, 2);
	अगर (ret == 0)
		ret = (buf[0] << 4) + ((buf[1] >> 4) & 0x0f);

	अगर (adc_ts_pin_ctrl & AXP288_ADC_TS_CURRENT_ON_OFF_MASK) अणु
		regmap_update_bits(regmap, AXP288_ADC_TS_PIN_CTRL,
				   AXP288_ADC_TS_CURRENT_ON_OFF_MASK,
				   AXP288_ADC_TS_CURRENT_ON);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा पूर्णांकel_pmic_opregion_data पूर्णांकel_xघातer_pmic_opregion_data = अणु
	.get_घातer = पूर्णांकel_xघातer_pmic_get_घातer,
	.update_घातer = पूर्णांकel_xघातer_pmic_update_घातer,
	.get_raw_temp = पूर्णांकel_xघातer_pmic_get_raw_temp,
	.घातer_table = घातer_table,
	.घातer_table_count = ARRAY_SIZE(घातer_table),
	.thermal_table = thermal_table,
	.thermal_table_count = ARRAY_SIZE(thermal_table),
	.pmic_i2c_address = 0x34,
पूर्ण;

अटल acpi_status पूर्णांकel_xघातer_pmic_gpio_handler(u32 function,
		acpi_physical_address address, u32 bit_width, u64 *value,
		व्योम *handler_context, व्योम *region_context)
अणु
	वापस AE_OK;
पूर्ण

अटल पूर्णांक पूर्णांकel_xघातer_pmic_opregion_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(parent);
	acpi_status status;
	पूर्णांक result;

	status = acpi_install_address_space_handler(ACPI_HANDLE(parent),
			ACPI_ADR_SPACE_GPIO, पूर्णांकel_xघातer_pmic_gpio_handler,
			शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	result = पूर्णांकel_pmic_install_opregion_handler(&pdev->dev,
					ACPI_HANDLE(parent), axp20x->regmap,
					&पूर्णांकel_xघातer_pmic_opregion_data);
	अगर (result)
		acpi_हटाओ_address_space_handler(ACPI_HANDLE(parent),
						  ACPI_ADR_SPACE_GPIO,
						  पूर्णांकel_xघातer_pmic_gpio_handler);

	वापस result;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_xघातer_pmic_opregion_driver = अणु
	.probe = पूर्णांकel_xघातer_pmic_opregion_probe,
	.driver = अणु
		.name = "axp288_pmic_acpi",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(पूर्णांकel_xघातer_pmic_opregion_driver);
