<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel SoC PMIC MFD Driver
 *
 * Copyright (C) 2013, 2014 Intel Corporation. All rights reserved.
 *
 * Author: Yang, Bin <bin.yang@पूर्णांकel.com>
 * Author: Zhu, Lejun <lejun.zhu@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

#समावेश "intel_soc_pmic_core.h"

/* Crystal Cove PMIC shares same ACPI ID between dअगरferent platक्रमms */
#घोषणा BYT_CRC_HRV		2
#घोषणा CHT_CRC_HRV		3

/* PWM consumed by the Intel GFX */
अटल काष्ठा pwm_lookup crc_pwm_lookup[] = अणु
	PWM_LOOKUP("crystal_cove_pwm", 0, "0000:00:02.0", "pwm_pmic_backlight", 0, PWM_POLARITY_NORMAL),
पूर्ण;

अटल पूर्णांक पूर्णांकel_soc_pmic_i2c_probe(काष्ठा i2c_client *i2c,
				    स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा पूर्णांकel_soc_pmic_config *config;
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	अचिन्हित दीर्घ दीर्घ hrv;
	acpi_status status;
	पूर्णांक ret;

	/*
	 * There are 2 dअगरferent Crystal Cove PMICs a Bay Trail and Cherry
	 * Trail version, use _HRV to dअगरferentiate between the 2.
	 */
	status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(dev), "_HRV", शून्य, &hrv);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Failed to get PMIC hardware revision\n");
		वापस -ENODEV;
	पूर्ण

	चयन (hrv) अणु
	हाल BYT_CRC_HRV:
		config = &पूर्णांकel_soc_pmic_config_byt_crc;
		अवरोध;
	हाल CHT_CRC_HRV:
		config = &पूर्णांकel_soc_pmic_config_cht_crc;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown hardware rev %llu, assuming BYT\n", hrv);
		config = &पूर्णांकel_soc_pmic_config_byt_crc;
	पूर्ण

	pmic = devm_kzalloc(dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	dev_set_drvdata(dev, pmic);

	pmic->regmap = devm_regmap_init_i2c(i2c, config->regmap_config);
	अगर (IS_ERR(pmic->regmap))
		वापस PTR_ERR(pmic->regmap);

	pmic->irq = i2c->irq;

	ret = regmap_add_irq_chip(pmic->regmap, pmic->irq,
				  config->irq_flags | IRQF_ONESHOT,
				  0, config->irq_chip,
				  &pmic->irq_chip_data);
	अगर (ret)
		वापस ret;

	ret = enable_irq_wake(pmic->irq);
	अगर (ret)
		dev_warn(dev, "Can't enable IRQ as wake source: %d\n", ret);

	/* Add lookup table क्रम crc-pwm */
	pwm_add_table(crc_pwm_lookup, ARRAY_SIZE(crc_pwm_lookup));

	ret = mfd_add_devices(dev, -1, config->cell_dev,
			      config->n_cell_devs, शून्य, 0,
			      regmap_irq_get_करोमुख्य(pmic->irq_chip_data));
	अगर (ret)
		जाओ err_del_irq_chip;

	वापस 0;

err_del_irq_chip:
	regmap_del_irq_chip(pmic->irq, pmic->irq_chip_data);
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_soc_pmic_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(&i2c->dev);

	regmap_del_irq_chip(pmic->irq, pmic->irq_chip_data);

	/* हटाओ crc-pwm lookup table */
	pwm_हटाओ_table(crc_pwm_lookup, ARRAY_SIZE(crc_pwm_lookup));

	mfd_हटाओ_devices(&i2c->dev);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_soc_pmic_shutकरोwn(काष्ठा i2c_client *i2c)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(&i2c->dev);

	disable_irq(pmic->irq);

	वापस;
पूर्ण

#अगर defined(CONFIG_PM_SLEEP)
अटल पूर्णांक पूर्णांकel_soc_pmic_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	disable_irq(pmic->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_soc_pmic_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	enable_irq(pmic->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(पूर्णांकel_soc_pmic_pm_ops, पूर्णांकel_soc_pmic_suspend,
			 पूर्णांकel_soc_pmic_resume);

अटल स्थिर काष्ठा i2c_device_id पूर्णांकel_soc_pmic_i2c_id[] = अणु
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पूर्णांकel_soc_pmic_i2c_id);

#अगर defined(CONFIG_ACPI)
अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_soc_pmic_acpi_match[] = अणु
	अणु "INT33FD" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_soc_pmic_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver पूर्णांकel_soc_pmic_i2c_driver = अणु
	.driver = अणु
		.name = "intel_soc_pmic_i2c",
		.pm = &पूर्णांकel_soc_pmic_pm_ops,
		.acpi_match_table = ACPI_PTR(पूर्णांकel_soc_pmic_acpi_match),
	पूर्ण,
	.probe = पूर्णांकel_soc_pmic_i2c_probe,
	.हटाओ = पूर्णांकel_soc_pmic_i2c_हटाओ,
	.id_table = पूर्णांकel_soc_pmic_i2c_id,
	.shutकरोwn = पूर्णांकel_soc_pmic_shutकरोwn,
पूर्ण;

module_i2c_driver(पूर्णांकel_soc_pmic_i2c_driver);

MODULE_DESCRIPTION("I2C driver for Intel SoC PMIC");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yang, Bin <bin.yang@intel.com>");
MODULE_AUTHOR("Zhu, Lejun <lejun.zhu@linux.intel.com>");
