<शैली गुरु>
/*
 * Retu घातer button driver.
 *
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Original code written by Ari Saastamoinen, Juha Yrjथघlथअ and Felipe Balbi.
 * Rewritten by Aaro Koskinen.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/retu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा RETU_STATUS_PWRONX (1 << 5)

अटल irqवापस_t retu_pwrbutton_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा input_dev *idev = _pwr;
	काष्ठा retu_dev *rdev = input_get_drvdata(idev);
	bool state;

	state = !(retu_पढ़ो(rdev, RETU_REG_STATUS) & RETU_STATUS_PWRONX);
	input_report_key(idev, KEY_POWER, state);
	input_sync(idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक retu_pwrbutton_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा input_dev *idev;
	पूर्णांक irq;
	पूर्णांक error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	idev = devm_input_allocate_device(&pdev->dev);
	अगर (!idev)
		वापस -ENOMEM;

	idev->name = "retu-pwrbutton";
	idev->dev.parent = &pdev->dev;

	input_set_capability(idev, EV_KEY, KEY_POWER);
	input_set_drvdata(idev, rdev);

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					  शून्य, retu_pwrbutton_irq,
					  IRQF_ONESHOT,
					  "retu-pwrbutton", idev);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(idev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver retu_pwrbutton_driver = अणु
	.probe		= retu_pwrbutton_probe,
	.driver		= अणु
		.name	= "retu-pwrbutton",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(retu_pwrbutton_driver);

MODULE_ALIAS("platform:retu-pwrbutton");
MODULE_DESCRIPTION("Retu Power Button");
MODULE_AUTHOR("Ari Saastamoinen");
MODULE_AUTHOR("Felipe Balbi");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
MODULE_LICENSE("GPL");
