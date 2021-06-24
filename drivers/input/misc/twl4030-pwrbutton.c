<शैली गुरु>
/**
 * twl4030-pwrbutton.c - TWL4030 Power Button Input Driver
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Written by Peter De Schrijver <peter.de-schrijver@nokia.com>
 * Several fixes by Felipe Balbi <felipe.balbi@nokia.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/twl.h>

#घोषणा PWR_PWRON_IRQ (1 << 0)

#घोषणा STS_HW_CONDITIONS 0xf

अटल irqवापस_t घातerbutton_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा input_dev *pwr = _pwr;
	पूर्णांक err;
	u8 value;

	err = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &value, STS_HW_CONDITIONS);
	अगर (!err)  अणु
		pm_wakeup_event(pwr->dev.parent, 0);
		input_report_key(pwr, KEY_POWER, value & PWR_PWRON_IRQ);
		input_sync(pwr);
	पूर्ण अन्यथा अणु
		dev_err(pwr->dev.parent, "twl4030: i2c error %d while reading"
			" TWL4030 PM_MASTER STS_HW_CONDITIONS register\n", err);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक twl4030_pwrbutton_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *pwr;
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	पूर्णांक err;

	pwr = devm_input_allocate_device(&pdev->dev);
	अगर (!pwr) अणु
		dev_err(&pdev->dev, "Can't allocate power button\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_capability(pwr, EV_KEY, KEY_POWER);
	pwr->name = "twl4030_pwrbutton";
	pwr->phys = "twl4030_pwrbutton/input0";
	pwr->dev.parent = &pdev->dev;

	err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, घातerbutton_irq,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
			IRQF_ONESHOT,
			"twl4030_pwrbutton", pwr);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Can't get IRQ for pwrbutton: %d\n", err);
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(pwr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't register power button: %d\n", err);
		वापस err;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id twl4030_pwrbutton_dt_match_table[] = अणु
       अणु .compatible = "ti,twl4030-pwrbutton" पूर्ण,
       अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl4030_pwrbutton_dt_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver twl4030_pwrbutton_driver = अणु
	.probe		= twl4030_pwrbutton_probe,
	.driver		= अणु
		.name	= "twl4030_pwrbutton",
		.of_match_table = of_match_ptr(twl4030_pwrbutton_dt_match_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(twl4030_pwrbutton_driver);

MODULE_ALIAS("platform:twl4030_pwrbutton");
MODULE_DESCRIPTION("Triton2 Power Button");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter De Schrijver <peter.de-schrijver@nokia.com>");
MODULE_AUTHOR("Felipe Balbi <felipe.balbi@nokia.com>");

