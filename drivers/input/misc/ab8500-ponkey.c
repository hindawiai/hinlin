<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Sundar Iyer <sundar.iyer@stericsson.com> क्रम ST-Ericsson
 *
 * AB8500 Power-On Key handler
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

/**
 * काष्ठा ab8500_ponkey - ab8500 ponkey inक्रमmation
 * @idev: poपूर्णांकer to input device
 * @ab8500: ab8500 parent
 * @irq_dbf: irq number क्रम falling transition
 * @irq_dbr: irq number क्रम rising transition
 */
काष्ठा ab8500_ponkey अणु
	काष्ठा input_dev	*idev;
	काष्ठा ab8500		*ab8500;
	पूर्णांक			irq_dbf;
	पूर्णांक			irq_dbr;
पूर्ण;

/* AB8500 gives us an पूर्णांकerrupt when ONKEY is held */
अटल irqवापस_t ab8500_ponkey_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ab8500_ponkey *ponkey = data;

	अगर (irq == ponkey->irq_dbf)
		input_report_key(ponkey->idev, KEY_POWER, true);
	अन्यथा अगर (irq == ponkey->irq_dbr)
		input_report_key(ponkey->idev, KEY_POWER, false);

	input_sync(ponkey->idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ab8500_ponkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500 *ab8500 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा ab8500_ponkey *ponkey;
	काष्ठा input_dev *input;
	पूर्णांक irq_dbf, irq_dbr;
	पूर्णांक error;

	irq_dbf = platक्रमm_get_irq_byname(pdev, "ONKEY_DBF");
	अगर (irq_dbf < 0)
		वापस irq_dbf;

	irq_dbr = platक्रमm_get_irq_byname(pdev, "ONKEY_DBR");
	अगर (irq_dbr < 0)
		वापस irq_dbr;

	ponkey = devm_kzalloc(&pdev->dev, माप(काष्ठा ab8500_ponkey),
			      GFP_KERNEL);
	अगर (!ponkey)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	ponkey->idev = input;
	ponkey->ab8500 = ab8500;
	ponkey->irq_dbf = irq_dbf;
	ponkey->irq_dbr = irq_dbr;

	input->name = "AB8500 POn(PowerOn) Key";
	input->dev.parent = &pdev->dev;

	input_set_capability(input, EV_KEY, KEY_POWER);

	error = devm_request_any_context_irq(&pdev->dev, ponkey->irq_dbf,
					     ab8500_ponkey_handler, 0,
					     "ab8500-ponkey-dbf", ponkey);
	अगर (error < 0) अणु
		dev_err(ab8500->dev, "Failed to request dbf IRQ#%d: %d\n",
			ponkey->irq_dbf, error);
		वापस error;
	पूर्ण

	error = devm_request_any_context_irq(&pdev->dev, ponkey->irq_dbr,
					     ab8500_ponkey_handler, 0,
					     "ab8500-ponkey-dbr", ponkey);
	अगर (error < 0) अणु
		dev_err(ab8500->dev, "Failed to request dbr IRQ#%d: %d\n",
			ponkey->irq_dbr, error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ponkey->idev);
	अगर (error) अणु
		dev_err(ab8500->dev, "Can't register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ab8500_ponkey_match[] = अणु
	अणु .compatible = "stericsson,ab8500-ponkey", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ab8500_ponkey_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ab8500_ponkey_driver = अणु
	.driver		= अणु
		.name	= "ab8500-poweron-key",
		.of_match_table = of_match_ptr(ab8500_ponkey_match),
	पूर्ण,
	.probe		= ab8500_ponkey_probe,
पूर्ण;
module_platक्रमm_driver(ab8500_ponkey_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sundar Iyer <sundar.iyer@stericsson.com>");
MODULE_DESCRIPTION("ST-Ericsson AB8500 Power-ON(Pon) Key driver");
