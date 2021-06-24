<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power-button driver क्रम Dollar Cove TI PMIC
 * Copyright (C) 2014 Intel Corp
 * Copyright (c) 2017 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/slab.h>

#घोषणा CHTDC_TI_SIRQ_REG	0x3
#घोषणा SIRQ_PWRBTN_REL		BIT(0)

अटल irqवापस_t chtdc_ti_pwrbtn_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा input_dev *input = dev_id;
	काष्ठा device *dev = input->dev.parent;
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	पूर्णांक state;

	अगर (!regmap_पढ़ो(regmap, CHTDC_TI_SIRQ_REG, &state)) अणु
		dev_dbg(dev, "SIRQ_REG=0x%x\n", state);
		input_report_key(input, KEY_POWER, !(state & SIRQ_PWRBTN_REL));
		input_sync(input);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक chtdc_ti_pwrbtn_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev->parent);
	काष्ठा input_dev *input;
	पूर्णांक irq, err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;
	input->name = pdev->name;
	input->phys = "power-button/input0";
	input->id.bustype = BUS_HOST;
	input_set_capability(input, EV_KEY, KEY_POWER);
	err = input_रेजिस्टर_device(input);
	अगर (err)
		वापस err;

	dev_set_drvdata(dev, pmic->regmap);

	err = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					chtdc_ti_pwrbtn_पूर्णांकerrupt,
					IRQF_ONESHOT, KBUILD_MODNAME, input);
	अगर (err)
		वापस err;

	device_init_wakeup(dev, true);
	dev_pm_set_wake_irq(dev, irq);
	वापस 0;
पूर्ण

अटल पूर्णांक chtdc_ti_pwrbtn_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id chtdc_ti_pwrbtn_id_table[] = अणु
	अणु .name = "chtdc_ti_pwrbtn" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, chtdc_ti_pwrbtn_id_table);

अटल काष्ठा platक्रमm_driver chtdc_ti_pwrbtn_driver = अणु
	.driver = अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
	.probe		= chtdc_ti_pwrbtn_probe,
	.हटाओ		= chtdc_ti_pwrbtn_हटाओ,
	.id_table	= chtdc_ti_pwrbtn_id_table,
पूर्ण;
module_platक्रमm_driver(chtdc_ti_pwrbtn_driver);

MODULE_DESCRIPTION("Power-button driver for Dollar Cove TI PMIC");
MODULE_LICENSE("GPL v2");
