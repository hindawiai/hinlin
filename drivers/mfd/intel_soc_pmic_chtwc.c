<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MFD core driver क्रम Intel Cherrytrail Whiskey Cove PMIC
 *
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on various non upstream patches to support the CHT Whiskey Cove PMIC:
 * Copyright (C) 2013-2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/regmap.h>

/* PMIC device रेजिस्टरs */
#घोषणा REG_OFFSET_MASK		GENMASK(7, 0)
#घोषणा REG_ADDR_MASK		GENMASK(15, 8)
#घोषणा REG_ADDR_SHIFT		8

#घोषणा CHT_WC_IRQLVL1		0x6e02
#घोषणा CHT_WC_IRQLVL1_MASK	0x6e0e

/* Whiskey Cove PMIC share same ACPI ID between dअगरferent platक्रमms */
#घोषणा CHT_WC_HRV		3

/* Level 1 IRQs (level 2 IRQs are handled in the child device drivers) */
क्रमागत अणु
	CHT_WC_PWRSRC_IRQ = 0,
	CHT_WC_THRM_IRQ,
	CHT_WC_BCU_IRQ,
	CHT_WC_ADC_IRQ,
	CHT_WC_EXT_CHGR_IRQ,
	CHT_WC_GPIO_IRQ,
	/* There is no irq 6 */
	CHT_WC_CRIT_IRQ = 7,
पूर्ण;

अटल स्थिर काष्ठा resource cht_wc_pwrsrc_resources[] = अणु
	DEFINE_RES_IRQ(CHT_WC_PWRSRC_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource cht_wc_ext_अक्षरger_resources[] = अणु
	DEFINE_RES_IRQ(CHT_WC_EXT_CHGR_IRQ),
पूर्ण;

अटल काष्ठा mfd_cell cht_wc_dev[] = अणु
	अणु
		.name = "cht_wcove_pwrsrc",
		.num_resources = ARRAY_SIZE(cht_wc_pwrsrc_resources),
		.resources = cht_wc_pwrsrc_resources,
	पूर्ण, अणु
		.name = "cht_wcove_ext_chgr",
		.num_resources = ARRAY_SIZE(cht_wc_ext_अक्षरger_resources),
		.resources = cht_wc_ext_अक्षरger_resources,
	पूर्ण,
	अणु	.name = "cht_wcove_region", पूर्ण,
	अणु	.name = "cht_wcove_leds", पूर्ण,
पूर्ण;

/*
 * The CHT Whiskey Cove covers multiple I2C addresses, with a 1 Byte
 * रेजिस्टर address space per I2C address, so we use 16 bit रेजिस्टर
 * addresses where the high 8 bits contain the I2C client address.
 */
अटल पूर्णांक cht_wc_byte_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक ret, orig_addr = client->addr;

	अगर (!(reg & REG_ADDR_MASK)) अणु
		dev_err(&client->dev, "Error I2C address not specified\n");
		वापस -EINVAL;
	पूर्ण

	client->addr = (reg & REG_ADDR_MASK) >> REG_ADDR_SHIFT;
	ret = i2c_smbus_पढ़ो_byte_data(client, reg & REG_OFFSET_MASK);
	client->addr = orig_addr;

	अगर (ret < 0)
		वापस ret;

	*val = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक cht_wc_byte_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक ret, orig_addr = client->addr;

	अगर (!(reg & REG_ADDR_MASK)) अणु
		dev_err(&client->dev, "Error I2C address not specified\n");
		वापस -EINVAL;
	पूर्ण

	client->addr = (reg & REG_ADDR_MASK) >> REG_ADDR_SHIFT;
	ret = i2c_smbus_ग_लिखो_byte_data(client, reg & REG_OFFSET_MASK, val);
	client->addr = orig_addr;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_config cht_wc_regmap_cfg = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.reg_ग_लिखो = cht_wc_byte_reg_ग_लिखो,
	.reg_पढ़ो = cht_wc_byte_reg_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq cht_wc_regmap_irqs[] = अणु
	REGMAP_IRQ_REG(CHT_WC_PWRSRC_IRQ, 0, BIT(CHT_WC_PWRSRC_IRQ)),
	REGMAP_IRQ_REG(CHT_WC_THRM_IRQ, 0, BIT(CHT_WC_THRM_IRQ)),
	REGMAP_IRQ_REG(CHT_WC_BCU_IRQ, 0, BIT(CHT_WC_BCU_IRQ)),
	REGMAP_IRQ_REG(CHT_WC_ADC_IRQ, 0, BIT(CHT_WC_ADC_IRQ)),
	REGMAP_IRQ_REG(CHT_WC_EXT_CHGR_IRQ, 0, BIT(CHT_WC_EXT_CHGR_IRQ)),
	REGMAP_IRQ_REG(CHT_WC_GPIO_IRQ, 0, BIT(CHT_WC_GPIO_IRQ)),
	REGMAP_IRQ_REG(CHT_WC_CRIT_IRQ, 0, BIT(CHT_WC_CRIT_IRQ)),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip cht_wc_regmap_irq_chip = अणु
	.name = "cht_wc_irq_chip",
	.status_base = CHT_WC_IRQLVL1,
	.mask_base = CHT_WC_IRQLVL1_MASK,
	.irqs = cht_wc_regmap_irqs,
	.num_irqs = ARRAY_SIZE(cht_wc_regmap_irqs),
	.num_regs = 1,
पूर्ण;

अटल पूर्णांक cht_wc_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ hrv;
	पूर्णांक ret;

	status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(dev), "_HRV", शून्य, &hrv);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Failed to get PMIC hardware revision\n");
		वापस -ENODEV;
	पूर्ण
	अगर (hrv != CHT_WC_HRV) अणु
		dev_err(dev, "Invalid PMIC hardware revision: %llu\n", hrv);
		वापस -ENODEV;
	पूर्ण
	अगर (client->irq < 0) अणु
		dev_err(dev, "Invalid IRQ\n");
		वापस -EINVAL;
	पूर्ण

	pmic = devm_kzalloc(dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	pmic->irq = client->irq;
	pmic->dev = dev;
	i2c_set_clientdata(client, pmic);

	pmic->regmap = devm_regmap_init(dev, शून्य, client, &cht_wc_regmap_cfg);
	अगर (IS_ERR(pmic->regmap))
		वापस PTR_ERR(pmic->regmap);

	ret = devm_regmap_add_irq_chip(dev, pmic->regmap, pmic->irq,
				       IRQF_ONESHOT | IRQF_SHARED, 0,
				       &cht_wc_regmap_irq_chip,
				       &pmic->irq_chip_data);
	अगर (ret)
		वापस ret;

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				cht_wc_dev, ARRAY_SIZE(cht_wc_dev), शून्य, 0,
				regmap_irq_get_करोमुख्य(pmic->irq_chip_data));
पूर्ण

अटल व्योम cht_wc_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = i2c_get_clientdata(client);

	disable_irq(pmic->irq);
पूर्ण

अटल पूर्णांक __maybe_unused cht_wc_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	disable_irq(pmic->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cht_wc_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	enable_irq(pmic->irq);

	वापस 0;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(cht_wc_pm_ops, cht_wc_suspend, cht_wc_resume);

अटल स्थिर काष्ठा i2c_device_id cht_wc_i2c_id[] = अणु
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id cht_wc_acpi_ids[] = अणु
	अणु "INT34D3", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver cht_wc_driver = अणु
	.driver	= अणु
		.name	= "CHT Whiskey Cove PMIC",
		.pm     = &cht_wc_pm_ops,
		.acpi_match_table = cht_wc_acpi_ids,
	पूर्ण,
	.probe_new = cht_wc_probe,
	.shutकरोwn = cht_wc_shutकरोwn,
	.id_table = cht_wc_i2c_id,
पूर्ण;
builtin_i2c_driver(cht_wc_driver);
