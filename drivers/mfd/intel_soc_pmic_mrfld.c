<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device access क्रम Basin Cove PMIC
 *
 * Copyright (c) 2019, Intel Corporation.
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic_mrfld.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

/*
 * Level 2 IRQs
 *
 * Firmware on the प्रणालीs with Basin Cove PMIC services Level 1 IRQs
 * without an assistance. Thus, each of the Level 1 IRQ is represented
 * as a separate RTE in IOAPIC.
 */
अटल काष्ठा resource irq_level2_resources[] = अणु
	DEFINE_RES_IRQ(0), /* घातer button */
	DEFINE_RES_IRQ(0), /* TMU */
	DEFINE_RES_IRQ(0), /* thermal */
	DEFINE_RES_IRQ(0), /* BCU */
	DEFINE_RES_IRQ(0), /* ADC */
	DEFINE_RES_IRQ(0), /* अक्षरger */
	DEFINE_RES_IRQ(0), /* GPIO */
पूर्ण;

अटल स्थिर काष्ठा mfd_cell bcove_dev[] = अणु
	अणु
		.name = "mrfld_bcove_pwrbtn",
		.num_resources = 1,
		.resources = &irq_level2_resources[0],
	पूर्ण, अणु
		.name = "mrfld_bcove_tmu",
		.num_resources = 1,
		.resources = &irq_level2_resources[1],
	पूर्ण, अणु
		.name = "mrfld_bcove_thermal",
		.num_resources = 1,
		.resources = &irq_level2_resources[2],
	पूर्ण, अणु
		.name = "mrfld_bcove_bcu",
		.num_resources = 1,
		.resources = &irq_level2_resources[3],
	पूर्ण, अणु
		.name = "mrfld_bcove_adc",
		.num_resources = 1,
		.resources = &irq_level2_resources[4],
	पूर्ण, अणु
		.name = "mrfld_bcove_charger",
		.num_resources = 1,
		.resources = &irq_level2_resources[5],
	पूर्ण, अणु
		.name = "mrfld_bcove_pwrsrc",
		.num_resources = 1,
		.resources = &irq_level2_resources[5],
	पूर्ण, अणु
		.name = "mrfld_bcove_gpio",
		.num_resources = 1,
		.resources = &irq_level2_resources[6],
	पूर्ण,
	अणु	.name = "mrfld_bcove_region", पूर्ण,
पूर्ण;

अटल पूर्णांक bcove_ipc_byte_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक *val)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = context;
	u8 ipc_out;
	पूर्णांक ret;

	ret = पूर्णांकel_scu_ipc_dev_ioपढ़ो8(pmic->scu, reg, &ipc_out);
	अगर (ret)
		वापस ret;

	*val = ipc_out;
	वापस 0;
पूर्ण

अटल पूर्णांक bcove_ipc_byte_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				     अचिन्हित पूर्णांक val)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = context;
	u8 ipc_in = val;

	वापस पूर्णांकel_scu_ipc_dev_ioग_लिखो8(pmic->scu, reg, ipc_in);
पूर्ण

अटल स्थिर काष्ठा regmap_config bcove_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,
	.reg_ग_लिखो = bcove_ipc_byte_reg_ग_लिखो,
	.reg_पढ़ो = bcove_ipc_byte_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक bcove_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	pmic = devm_kzalloc(dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	pmic->scu = devm_पूर्णांकel_scu_ipc_dev_get(dev);
	अगर (!pmic->scu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pmic);
	pmic->dev = &pdev->dev;

	pmic->regmap = devm_regmap_init(dev, शून्य, pmic, &bcove_regmap_config);
	अगर (IS_ERR(pmic->regmap))
		वापस PTR_ERR(pmic->regmap);

	क्रम (i = 0; i < ARRAY_SIZE(irq_level2_resources); i++) अणु
		ret = platक्रमm_get_irq(pdev, i);
		अगर (ret < 0)
			वापस ret;

		irq_level2_resources[i].start = ret;
		irq_level2_resources[i].end = ret;
	पूर्ण

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				    bcove_dev, ARRAY_SIZE(bcove_dev),
				    शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id bcove_acpi_ids[] = अणु
	अणु "INTC100E" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bcove_acpi_ids);

अटल काष्ठा platक्रमm_driver bcove_driver = अणु
	.driver = अणु
		.name = "intel_soc_pmic_mrfld",
		.acpi_match_table = bcove_acpi_ids,
	पूर्ण,
	.probe = bcove_probe,
पूर्ण;
module_platक्रमm_driver(bcove_driver);

MODULE_DESCRIPTION("IPC driver for Intel SoC Basin Cove PMIC");
MODULE_LICENSE("GPL v2");
