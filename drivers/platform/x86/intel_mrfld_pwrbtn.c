<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power-button driver क्रम Basin Cove PMIC
 *
 * Copyright (c) 2019, Intel Corporation.
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic_mrfld.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/slab.h>

#घोषणा BCOVE_PBSTATUS		0x27
#घोषणा BCOVE_PBSTATUS_PBLVL	BIT(4)	/* 1 - release, 0 - press */

अटल irqवापस_t mrfld_pwrbtn_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा input_dev *input = dev_id;
	काष्ठा device *dev = input->dev.parent;
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक state;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, BCOVE_PBSTATUS, &state);
	अगर (ret)
		वापस IRQ_NONE;

	dev_dbg(dev, "PBSTATUS=0x%x\n", state);
	input_report_key(input, KEY_POWER, !(state & BCOVE_PBSTATUS_PBLVL));
	input_sync(input);

	regmap_update_bits(regmap, BCOVE_MIRQLVL1, BCOVE_LVL1_PWRBTN, 0);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mrfld_pwrbtn_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev->parent);
	काष्ठा input_dev *input;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;
	input->name = pdev->name;
	input->phys = "power-button/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = dev;
	input_set_capability(input, EV_KEY, KEY_POWER);
	ret = input_रेजिस्टर_device(input);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(dev, pmic->regmap);

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, mrfld_pwrbtn_पूर्णांकerrupt,
					IRQF_ONESHOT | IRQF_SHARED, pdev->name,
					input);
	अगर (ret)
		वापस ret;

	regmap_update_bits(pmic->regmap, BCOVE_MIRQLVL1, BCOVE_LVL1_PWRBTN, 0);
	regmap_update_bits(pmic->regmap, BCOVE_MPBIRQ, BCOVE_PBIRQ_PBTN, 0);

	device_init_wakeup(dev, true);
	dev_pm_set_wake_irq(dev, irq);
	वापस 0;
पूर्ण

अटल पूर्णांक mrfld_pwrbtn_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	dev_pm_clear_wake_irq(dev);
	device_init_wakeup(dev, false);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mrfld_pwrbtn_id_table[] = अणु
	अणु .name = "mrfld_bcove_pwrbtn" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mrfld_pwrbtn_id_table);

अटल काष्ठा platक्रमm_driver mrfld_pwrbtn_driver = अणु
	.driver = अणु
		.name	= "mrfld_bcove_pwrbtn",
	पूर्ण,
	.probe		= mrfld_pwrbtn_probe,
	.हटाओ		= mrfld_pwrbtn_हटाओ,
	.id_table	= mrfld_pwrbtn_id_table,
पूर्ण;
module_platक्रमm_driver(mrfld_pwrbtn_driver);

MODULE_DESCRIPTION("Power-button driver for Basin Cove PMIC");
MODULE_LICENSE("GPL v2");
