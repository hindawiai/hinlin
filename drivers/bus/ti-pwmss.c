<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI PWM Subप्रणाली driver
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>

अटल स्थिर काष्ठा of_device_id pwmss_of_match[] = अणु
	अणु .compatible	= "ti,am33xx-pwmss" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwmss_of_match);

अटल पूर्णांक pwmss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *node = pdev->dev.of_node;

	pm_runसमय_enable(&pdev->dev);

	/* Populate all the child nodes here... */
	ret = of_platक्रमm_populate(node, शून्य, शून्य, &pdev->dev);
	अगर (ret)
		dev_err(&pdev->dev, "no child node found\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pwmss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pwmss_driver = अणु
	.driver	= अणु
		.name	= "pwmss",
		.of_match_table	= pwmss_of_match,
	पूर्ण,
	.probe	= pwmss_probe,
	.हटाओ	= pwmss_हटाओ,
पूर्ण;

module_platक्रमm_driver(pwmss_driver);

MODULE_DESCRIPTION("PWM Subsystem driver");
MODULE_AUTHOR("Texas Instruments");
MODULE_LICENSE("GPL");
