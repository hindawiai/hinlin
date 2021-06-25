<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel BXT Whiskey Cove PMIC TMU driver
 *
 * Copyright (C) 2016 Intel Corporation. All rights reserved.
 *
 * This driver adds TMU (Time Management Unit) support क्रम Intel BXT platक्रमm.
 * It enables the alarm wake-up functionality in the TMU unit of Whiskey Cove
 * PMIC.
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>

#घोषणा BXTWC_TMUIRQ		0x4fb6
#घोषणा BXTWC_MIRQLVL1		0x4e0e
#घोषणा BXTWC_MTMUIRQ_REG	0x4fb7
#घोषणा BXTWC_MIRQLVL1_MTMU	BIT(1)
#घोषणा BXTWC_TMU_WK_ALRM	BIT(1)
#घोषणा BXTWC_TMU_SYS_ALRM	BIT(2)
#घोषणा BXTWC_TMU_ALRM_MASK	(BXTWC_TMU_WK_ALRM | BXTWC_TMU_SYS_ALRM)
#घोषणा BXTWC_TMU_ALRM_IRQ	(BXTWC_TMU_WK_ALRM | BXTWC_TMU_SYS_ALRM)

काष्ठा wcove_पंचांगu अणु
	पूर्णांक irq;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल irqवापस_t bxt_wcove_पंचांगu_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wcove_पंचांगu *wcपंचांगu = data;
	अचिन्हित पूर्णांक पंचांगu_irq;

	/* Read TMU पूर्णांकerrupt reg */
	regmap_पढ़ो(wcपंचांगu->regmap, BXTWC_TMUIRQ, &पंचांगu_irq);
	अगर (पंचांगu_irq & BXTWC_TMU_ALRM_IRQ) अणु
		/* clear TMU irq */
		regmap_ग_लिखो(wcपंचांगu->regmap, BXTWC_TMUIRQ, पंचांगu_irq);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक bxt_wcove_पंचांगu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regmap_irq_chip_data *regmap_irq_chip;
	काष्ठा wcove_पंचांगu *wcपंचांगu;
	पूर्णांक ret, virq, irq;

	wcपंचांगu = devm_kzalloc(&pdev->dev, माप(*wcपंचांगu), GFP_KERNEL);
	अगर (!wcपंचांगu)
		वापस -ENOMEM;

	wcपंचांगu->dev = &pdev->dev;
	wcपंचांगu->regmap = pmic->regmap;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regmap_irq_chip = pmic->irq_chip_data_पंचांगu;
	virq = regmap_irq_get_virq(regmap_irq_chip, irq);
	अगर (virq < 0) अणु
		dev_err(&pdev->dev,
			"failed to get virtual interrupt=%d\n", irq);
		वापस virq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, virq,
					शून्य, bxt_wcove_पंचांगu_irq_handler,
					IRQF_ONESHOT, "bxt_wcove_tmu", wcपंचांगu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request irq failed: %d,virq: %d\n",
							ret, virq);
		वापस ret;
	पूर्ण
	wcपंचांगu->irq = virq;

	/* Unmask TMU second level Wake & System alarm */
	regmap_update_bits(wcपंचांगu->regmap, BXTWC_MTMUIRQ_REG,
				  BXTWC_TMU_ALRM_MASK, 0);

	platक्रमm_set_drvdata(pdev, wcपंचांगu);
	वापस 0;
पूर्ण

अटल पूर्णांक bxt_wcove_पंचांगu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wcove_पंचांगu *wcपंचांगu = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक val;

	/* Mask TMU पूर्णांकerrupts */
	regmap_पढ़ो(wcपंचांगu->regmap, BXTWC_MIRQLVL1, &val);
	regmap_ग_लिखो(wcपंचांगu->regmap, BXTWC_MIRQLVL1,
			val | BXTWC_MIRQLVL1_MTMU);
	regmap_पढ़ो(wcपंचांगu->regmap, BXTWC_MTMUIRQ_REG, &val);
	regmap_ग_लिखो(wcपंचांगu->regmap, BXTWC_MTMUIRQ_REG,
			val | BXTWC_TMU_ALRM_MASK);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bxtwc_पंचांगu_suspend(काष्ठा device *dev)
अणु
	काष्ठा wcove_पंचांगu *wcपंचांगu = dev_get_drvdata(dev);

	enable_irq_wake(wcपंचांगu->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक bxtwc_पंचांगu_resume(काष्ठा device *dev)
अणु
	काष्ठा wcove_पंचांगu *wcपंचांगu = dev_get_drvdata(dev);

	disable_irq_wake(wcपंचांगu->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(bxtwc_पंचांगu_pm_ops, bxtwc_पंचांगu_suspend, bxtwc_पंचांगu_resume);

अटल स्थिर काष्ठा platक्रमm_device_id bxt_wcove_पंचांगu_id_table[] = अणु
	अणु .name = "bxt_wcove_tmu" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bxt_wcove_पंचांगu_id_table);

अटल काष्ठा platक्रमm_driver bxt_wcove_पंचांगu_driver = अणु
	.probe = bxt_wcove_पंचांगu_probe,
	.हटाओ = bxt_wcove_पंचांगu_हटाओ,
	.driver = अणु
		.name = "bxt_wcove_tmu",
		.pm     = &bxtwc_पंचांगu_pm_ops,
	पूर्ण,
	.id_table = bxt_wcove_पंचांगu_id_table,
पूर्ण;

module_platक्रमm_driver(bxt_wcove_पंचांगu_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Nilesh Bacchewar <nilesh.bacchewar@intel.com>");
MODULE_DESCRIPTION("BXT Whiskey Cove TMU Driver");
