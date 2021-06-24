<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MFD core driver क्रम Intel Broxton Whiskey Cove PMIC
 *
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic_bxtwc.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

/* PMIC device रेजिस्टरs */
#घोषणा REG_ADDR_MASK		0xFF00
#घोषणा REG_ADDR_SHIFT		8
#घोषणा REG_OFFSET_MASK		0xFF

/* Interrupt Status Registers */
#घोषणा BXTWC_IRQLVL1		0x4E02

#घोषणा BXTWC_PWRBTNIRQ		0x4E03
#घोषणा BXTWC_THRM0IRQ		0x4E04
#घोषणा BXTWC_THRM1IRQ		0x4E05
#घोषणा BXTWC_THRM2IRQ		0x4E06
#घोषणा BXTWC_BCUIRQ		0x4E07
#घोषणा BXTWC_ADCIRQ		0x4E08
#घोषणा BXTWC_CHGR0IRQ		0x4E09
#घोषणा BXTWC_CHGR1IRQ		0x4E0A
#घोषणा BXTWC_GPIOIRQ0		0x4E0B
#घोषणा BXTWC_GPIOIRQ1		0x4E0C
#घोषणा BXTWC_CRITIRQ		0x4E0D
#घोषणा BXTWC_TMUIRQ		0x4FB6

/* Interrupt MASK Registers */
#घोषणा BXTWC_MIRQLVL1		0x4E0E
#घोषणा BXTWC_MIRQLVL1_MCHGR	BIT(5)

#घोषणा BXTWC_MPWRBTNIRQ	0x4E0F
#घोषणा BXTWC_MTHRM0IRQ		0x4E12
#घोषणा BXTWC_MTHRM1IRQ		0x4E13
#घोषणा BXTWC_MTHRM2IRQ		0x4E14
#घोषणा BXTWC_MBCUIRQ		0x4E15
#घोषणा BXTWC_MADCIRQ		0x4E16
#घोषणा BXTWC_MCHGR0IRQ		0x4E17
#घोषणा BXTWC_MCHGR1IRQ		0x4E18
#घोषणा BXTWC_MGPIO0IRQ		0x4E19
#घोषणा BXTWC_MGPIO1IRQ		0x4E1A
#घोषणा BXTWC_MCRITIRQ		0x4E1B
#घोषणा BXTWC_MTMUIRQ		0x4FB7

/* Whiskey Cove PMIC share same ACPI ID between dअगरferent platक्रमms */
#घोषणा BROXTON_PMIC_WC_HRV	4

#घोषणा PMC_PMIC_ACCESS		0xFF
#घोषणा PMC_PMIC_READ		0x0
#घोषणा PMC_PMIC_WRITE		0x1

क्रमागत bxtwc_irqs अणु
	BXTWC_PWRBTN_LVL1_IRQ = 0,
	BXTWC_TMU_LVL1_IRQ,
	BXTWC_THRM_LVL1_IRQ,
	BXTWC_BCU_LVL1_IRQ,
	BXTWC_ADC_LVL1_IRQ,
	BXTWC_CHGR_LVL1_IRQ,
	BXTWC_GPIO_LVL1_IRQ,
	BXTWC_CRIT_LVL1_IRQ,
पूर्ण;

क्रमागत bxtwc_irqs_pwrbtn अणु
	BXTWC_PWRBTN_IRQ = 0,
	BXTWC_UIBTN_IRQ,
पूर्ण;

क्रमागत bxtwc_irqs_bcu अणु
	BXTWC_BCU_IRQ = 0,
पूर्ण;

क्रमागत bxtwc_irqs_adc अणु
	BXTWC_ADC_IRQ = 0,
पूर्ण;

क्रमागत bxtwc_irqs_chgr अणु
	BXTWC_USBC_IRQ = 0,
	BXTWC_CHGR0_IRQ,
	BXTWC_CHGR1_IRQ,
पूर्ण;

क्रमागत bxtwc_irqs_पंचांगu अणु
	BXTWC_TMU_IRQ = 0,
पूर्ण;

क्रमागत bxtwc_irqs_crit अणु
	BXTWC_CRIT_IRQ = 0,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs[] = अणु
	REGMAP_IRQ_REG(BXTWC_PWRBTN_LVL1_IRQ, 0, BIT(0)),
	REGMAP_IRQ_REG(BXTWC_TMU_LVL1_IRQ, 0, BIT(1)),
	REGMAP_IRQ_REG(BXTWC_THRM_LVL1_IRQ, 0, BIT(2)),
	REGMAP_IRQ_REG(BXTWC_BCU_LVL1_IRQ, 0, BIT(3)),
	REGMAP_IRQ_REG(BXTWC_ADC_LVL1_IRQ, 0, BIT(4)),
	REGMAP_IRQ_REG(BXTWC_CHGR_LVL1_IRQ, 0, BIT(5)),
	REGMAP_IRQ_REG(BXTWC_GPIO_LVL1_IRQ, 0, BIT(6)),
	REGMAP_IRQ_REG(BXTWC_CRIT_LVL1_IRQ, 0, BIT(7)),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs_pwrbtn[] = अणु
	REGMAP_IRQ_REG(BXTWC_PWRBTN_IRQ, 0, 0x01),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs_bcu[] = अणु
	REGMAP_IRQ_REG(BXTWC_BCU_IRQ, 0, 0x1f),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs_adc[] = अणु
	REGMAP_IRQ_REG(BXTWC_ADC_IRQ, 0, 0xff),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs_chgr[] = अणु
	REGMAP_IRQ_REG(BXTWC_USBC_IRQ, 0, 0x20),
	REGMAP_IRQ_REG(BXTWC_CHGR0_IRQ, 0, 0x1f),
	REGMAP_IRQ_REG(BXTWC_CHGR1_IRQ, 1, 0x1f),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs_पंचांगu[] = अणु
	REGMAP_IRQ_REG(BXTWC_TMU_IRQ, 0, 0x06),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bxtwc_regmap_irqs_crit[] = अणु
	REGMAP_IRQ_REG(BXTWC_CRIT_IRQ, 0, 0x03),
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip = अणु
	.name = "bxtwc_irq_chip",
	.status_base = BXTWC_IRQLVL1,
	.mask_base = BXTWC_MIRQLVL1,
	.irqs = bxtwc_regmap_irqs,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs),
	.num_regs = 1,
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip_pwrbtn = अणु
	.name = "bxtwc_irq_chip_pwrbtn",
	.status_base = BXTWC_PWRBTNIRQ,
	.mask_base = BXTWC_MPWRBTNIRQ,
	.irqs = bxtwc_regmap_irqs_pwrbtn,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs_pwrbtn),
	.num_regs = 1,
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip_पंचांगu = अणु
	.name = "bxtwc_irq_chip_tmu",
	.status_base = BXTWC_TMUIRQ,
	.mask_base = BXTWC_MTMUIRQ,
	.irqs = bxtwc_regmap_irqs_पंचांगu,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs_पंचांगu),
	.num_regs = 1,
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip_bcu = अणु
	.name = "bxtwc_irq_chip_bcu",
	.status_base = BXTWC_BCUIRQ,
	.mask_base = BXTWC_MBCUIRQ,
	.irqs = bxtwc_regmap_irqs_bcu,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs_bcu),
	.num_regs = 1,
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip_adc = अणु
	.name = "bxtwc_irq_chip_adc",
	.status_base = BXTWC_ADCIRQ,
	.mask_base = BXTWC_MADCIRQ,
	.irqs = bxtwc_regmap_irqs_adc,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs_adc),
	.num_regs = 1,
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip_chgr = अणु
	.name = "bxtwc_irq_chip_chgr",
	.status_base = BXTWC_CHGR0IRQ,
	.mask_base = BXTWC_MCHGR0IRQ,
	.irqs = bxtwc_regmap_irqs_chgr,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs_chgr),
	.num_regs = 2,
पूर्ण;

अटल काष्ठा regmap_irq_chip bxtwc_regmap_irq_chip_crit = अणु
	.name = "bxtwc_irq_chip_crit",
	.status_base = BXTWC_CRITIRQ,
	.mask_base = BXTWC_MCRITIRQ,
	.irqs = bxtwc_regmap_irqs_crit,
	.num_irqs = ARRAY_SIZE(bxtwc_regmap_irqs_crit),
	.num_regs = 1,
पूर्ण;

अटल स्थिर काष्ठा resource gpio_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(BXTWC_GPIO_LVL1_IRQ, "GPIO"),
पूर्ण;

अटल स्थिर काष्ठा resource adc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(BXTWC_ADC_IRQ, "ADC"),
पूर्ण;

अटल स्थिर काष्ठा resource usbc_resources[] = अणु
	DEFINE_RES_IRQ(BXTWC_USBC_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource अक्षरger_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(BXTWC_CHGR0_IRQ, "CHARGER"),
	DEFINE_RES_IRQ_NAMED(BXTWC_CHGR1_IRQ, "CHARGER1"),
पूर्ण;

अटल स्थिर काष्ठा resource thermal_resources[] = अणु
	DEFINE_RES_IRQ(BXTWC_THRM_LVL1_IRQ),
पूर्ण;

अटल स्थिर काष्ठा resource bcu_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(BXTWC_BCU_IRQ, "BCU"),
पूर्ण;

अटल स्थिर काष्ठा resource पंचांगu_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(BXTWC_TMU_IRQ, "TMU"),
पूर्ण;

अटल काष्ठा mfd_cell bxt_wc_dev[] = अणु
	अणु
		.name = "bxt_wcove_gpadc",
		.num_resources = ARRAY_SIZE(adc_resources),
		.resources = adc_resources,
	पूर्ण,
	अणु
		.name = "bxt_wcove_thermal",
		.num_resources = ARRAY_SIZE(thermal_resources),
		.resources = thermal_resources,
	पूर्ण,
	अणु
		.name = "bxt_wcove_usbc",
		.num_resources = ARRAY_SIZE(usbc_resources),
		.resources = usbc_resources,
	पूर्ण,
	अणु
		.name = "bxt_wcove_ext_charger",
		.num_resources = ARRAY_SIZE(अक्षरger_resources),
		.resources = अक्षरger_resources,
	पूर्ण,
	अणु
		.name = "bxt_wcove_bcu",
		.num_resources = ARRAY_SIZE(bcu_resources),
		.resources = bcu_resources,
	पूर्ण,
	अणु
		.name = "bxt_wcove_tmu",
		.num_resources = ARRAY_SIZE(पंचांगu_resources),
		.resources = पंचांगu_resources,
	पूर्ण,

	अणु
		.name = "bxt_wcove_gpio",
		.num_resources = ARRAY_SIZE(gpio_resources),
		.resources = gpio_resources,
	पूर्ण,
	अणु
		.name = "bxt_wcove_region",
	पूर्ण,
पूर्ण;

अटल पूर्णांक regmap_ipc_byte_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	पूर्णांक i2c_addr;
	u8 ipc_in[2];
	u8 ipc_out[4];
	काष्ठा पूर्णांकel_soc_pmic *pmic = context;

	अगर (!pmic)
		वापस -EINVAL;

	अगर (reg & REG_ADDR_MASK)
		i2c_addr = (reg & REG_ADDR_MASK) >> REG_ADDR_SHIFT;
	अन्यथा
		i2c_addr = BXTWC_DEVICE1_ADDR;

	reg &= REG_OFFSET_MASK;

	ipc_in[0] = reg;
	ipc_in[1] = i2c_addr;
	ret = पूर्णांकel_scu_ipc_dev_command(pmic->scu, PMC_PMIC_ACCESS,
					PMC_PMIC_READ, ipc_in, माप(ipc_in),
					ipc_out, माप(ipc_out));
	अगर (ret)
		वापस ret;

	*val = ipc_out[0];

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_ipc_byte_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				       अचिन्हित पूर्णांक val)
अणु
	पूर्णांक i2c_addr;
	u8 ipc_in[3];
	काष्ठा पूर्णांकel_soc_pmic *pmic = context;

	अगर (!pmic)
		वापस -EINVAL;

	अगर (reg & REG_ADDR_MASK)
		i2c_addr = (reg & REG_ADDR_MASK) >> REG_ADDR_SHIFT;
	अन्यथा
		i2c_addr = BXTWC_DEVICE1_ADDR;

	reg &= REG_OFFSET_MASK;

	ipc_in[0] = reg;
	ipc_in[1] = i2c_addr;
	ipc_in[2] = val;
	वापस पूर्णांकel_scu_ipc_dev_command(pmic->scu, PMC_PMIC_ACCESS,
					 PMC_PMIC_WRITE, ipc_in, माप(ipc_in),
					 शून्य, 0);
पूर्ण

/* sysfs पूर्णांकerfaces to r/w PMIC रेजिस्टरs, required by initial script */
अटल अचिन्हित दीर्घ bxtwc_reg_addr;
अटल sमाप_प्रकार bxtwc_reg_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%lx\n", bxtwc_reg_addr);
पूर्ण

अटल sमाप_प्रकार bxtwc_reg_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (kम_से_अदीर्घ(buf, 0, &bxtwc_reg_addr)) अणु
		dev_err(dev, "Invalid register address\n");
		वापस -EINVAL;
	पूर्ण
	वापस (sमाप_प्रकार)count;
पूर्ण

अटल sमाप_प्रकार bxtwc_val_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	ret = regmap_पढ़ो(pmic->regmap, bxtwc_reg_addr, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read 0x%lx\n", bxtwc_reg_addr);
		वापस -EIO;
	पूर्ण

	वापस प्र_लिखो(buf, "0x%02x\n", val);
पूर्ण

अटल sमाप_प्रकार bxtwc_val_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(pmic->regmap, bxtwc_reg_addr, val);
	अगर (ret) अणु
		dev_err(dev, "Failed to write value 0x%02x to address 0x%lx",
			val, bxtwc_reg_addr);
		वापस -EIO;
	पूर्ण
	वापस count;
पूर्ण

अटल DEVICE_ATTR(addr, S_IWUSR | S_IRUSR, bxtwc_reg_show, bxtwc_reg_store);
अटल DEVICE_ATTR(val, S_IWUSR | S_IRUSR, bxtwc_val_show, bxtwc_val_store);
अटल काष्ठा attribute *bxtwc_attrs[] = अणु
	&dev_attr_addr.attr,
	&dev_attr_val.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group bxtwc_group = अणु
	.attrs = bxtwc_attrs,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bxtwc_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.reg_ग_लिखो = regmap_ipc_byte_reg_ग_लिखो,
	.reg_पढ़ो = regmap_ipc_byte_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक bxtwc_add_chained_irq_chip(काष्ठा पूर्णांकel_soc_pmic *pmic,
				काष्ठा regmap_irq_chip_data *pdata,
				पूर्णांक pirq, पूर्णांक irq_flags,
				स्थिर काष्ठा regmap_irq_chip *chip,
				काष्ठा regmap_irq_chip_data **data)
अणु
	पूर्णांक irq;

	irq = regmap_irq_get_virq(pdata, pirq);
	अगर (irq < 0) अणु
		dev_err(pmic->dev,
			"Failed to get parent vIRQ(%d) for chip %s, ret:%d\n",
			pirq, chip->name, irq);
		वापस irq;
	पूर्ण

	वापस devm_regmap_add_irq_chip(pmic->dev, pmic->regmap, irq, irq_flags,
					0, chip, data);
पूर्ण

अटल पूर्णांक bxtwc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	acpi_handle handle;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ hrv;
	काष्ठा पूर्णांकel_soc_pmic *pmic;

	handle = ACPI_HANDLE(&pdev->dev);
	status = acpi_evaluate_पूर्णांकeger(handle, "_HRV", शून्य, &hrv);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&pdev->dev, "Failed to get PMIC hardware revision\n");
		वापस -ENODEV;
	पूर्ण
	अगर (hrv != BROXTON_PMIC_WC_HRV) अणु
		dev_err(&pdev->dev, "Invalid PMIC hardware revision: %llu\n",
			hrv);
		वापस -ENODEV;
	पूर्ण

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	pmic->irq = ret;

	dev_set_drvdata(&pdev->dev, pmic);
	pmic->dev = &pdev->dev;

	pmic->scu = devm_पूर्णांकel_scu_ipc_dev_get(&pdev->dev);
	अगर (!pmic->scu)
		वापस -EPROBE_DEFER;

	pmic->regmap = devm_regmap_init(&pdev->dev, शून्य, pmic,
					&bxtwc_regmap_config);
	अगर (IS_ERR(pmic->regmap)) अणु
		ret = PTR_ERR(pmic->regmap);
		dev_err(&pdev->dev, "Failed to initialise regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_regmap_add_irq_chip(&pdev->dev, pmic->regmap, pmic->irq,
				       IRQF_ONESHOT | IRQF_SHARED,
				       0, &bxtwc_regmap_irq_chip,
				       &pmic->irq_chip_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add IRQ chip\n");
		वापस ret;
	पूर्ण

	ret = bxtwc_add_chained_irq_chip(pmic, pmic->irq_chip_data,
					 BXTWC_PWRBTN_LVL1_IRQ,
					 IRQF_ONESHOT,
					 &bxtwc_regmap_irq_chip_pwrbtn,
					 &pmic->irq_chip_data_pwrbtn);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add PWRBTN IRQ chip\n");
		वापस ret;
	पूर्ण

	ret = bxtwc_add_chained_irq_chip(pmic, pmic->irq_chip_data,
					 BXTWC_TMU_LVL1_IRQ,
					 IRQF_ONESHOT,
					 &bxtwc_regmap_irq_chip_पंचांगu,
					 &pmic->irq_chip_data_पंचांगu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add TMU IRQ chip\n");
		वापस ret;
	पूर्ण

	/* Add chained IRQ handler क्रम BCU IRQs */
	ret = bxtwc_add_chained_irq_chip(pmic, pmic->irq_chip_data,
					 BXTWC_BCU_LVL1_IRQ,
					 IRQF_ONESHOT,
					 &bxtwc_regmap_irq_chip_bcu,
					 &pmic->irq_chip_data_bcu);


	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add BUC IRQ chip\n");
		वापस ret;
	पूर्ण

	/* Add chained IRQ handler क्रम ADC IRQs */
	ret = bxtwc_add_chained_irq_chip(pmic, pmic->irq_chip_data,
					 BXTWC_ADC_LVL1_IRQ,
					 IRQF_ONESHOT,
					 &bxtwc_regmap_irq_chip_adc,
					 &pmic->irq_chip_data_adc);


	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add ADC IRQ chip\n");
		वापस ret;
	पूर्ण

	/* Add chained IRQ handler क्रम CHGR IRQs */
	ret = bxtwc_add_chained_irq_chip(pmic, pmic->irq_chip_data,
					 BXTWC_CHGR_LVL1_IRQ,
					 IRQF_ONESHOT,
					 &bxtwc_regmap_irq_chip_chgr,
					 &pmic->irq_chip_data_chgr);


	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add CHGR IRQ chip\n");
		वापस ret;
	पूर्ण

	/* Add chained IRQ handler क्रम CRIT IRQs */
	ret = bxtwc_add_chained_irq_chip(pmic, pmic->irq_chip_data,
					 BXTWC_CRIT_LVL1_IRQ,
					 IRQF_ONESHOT,
					 &bxtwc_regmap_irq_chip_crit,
					 &pmic->irq_chip_data_crit);


	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add CRIT IRQ chip\n");
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE, bxt_wc_dev,
				   ARRAY_SIZE(bxt_wc_dev), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add devices\n");
		वापस ret;
	पूर्ण

	ret = sysfs_create_group(&pdev->dev.kobj, &bxtwc_group);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to create sysfs group %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * There is known hw bug. Upon reset BIT 5 of रेजिस्टर
	 * BXTWC_CHGR_LVL1_IRQ is 0 which is the expected value. However,
	 * later it's set to 1(masked) स्वतःmatically by hardware. So we
	 * have the software workaround here to unmaksed it in order to let
	 * अक्षरger पूर्णांकerrutp work.
	 */
	regmap_update_bits(pmic->regmap, BXTWC_MIRQLVL1,
				BXTWC_MIRQLVL1_MCHGR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bxtwc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sysfs_हटाओ_group(&pdev->dev.kobj, &bxtwc_group);

	वापस 0;
पूर्ण

अटल व्योम bxtwc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(&pdev->dev);

	disable_irq(pmic->irq);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bxtwc_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	disable_irq(pmic->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक bxtwc_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	enable_irq(pmic->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(bxtwc_pm_ops, bxtwc_suspend, bxtwc_resume);

अटल स्थिर काष्ठा acpi_device_id bxtwc_acpi_ids[] = अणु
	अणु "INT34D3", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bxtwc_acpi_ids);

अटल काष्ठा platक्रमm_driver bxtwc_driver = अणु
	.probe = bxtwc_probe,
	.हटाओ	= bxtwc_हटाओ,
	.shutकरोwn = bxtwc_shutकरोwn,
	.driver	= अणु
		.name	= "BXTWC PMIC",
		.pm     = &bxtwc_pm_ops,
		.acpi_match_table = ACPI_PTR(bxtwc_acpi_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bxtwc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Qipeng Zha<qipeng.zha@intel.com>");
