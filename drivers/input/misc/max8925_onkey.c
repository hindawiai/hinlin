<शैली गुरु>
/**
 * MAX8925 ONKEY driver
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *      Haojian Zhuang <haojian.zhuang@marvell.com>
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/max8925.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#घोषणा SW_INPUT		(1 << 7)	/* 0/1 -- up/करोwn */
#घोषणा HARDRESET_EN		(1 << 7)
#घोषणा PWREN_EN		(1 << 7)

काष्ठा max8925_onkey_info अणु
	काष्ठा input_dev	*idev;
	काष्ठा i2c_client	*i2c;
	काष्ठा device		*dev;
	अचिन्हित पूर्णांक		irq[2];
पूर्ण;

/*
 * MAX8925 gives us an पूर्णांकerrupt when ONKEY is pressed or released.
 * max8925_set_bits() operates I2C bus and may sleep. So implement
 * it in thपढ़ो IRQ handler.
 */
अटल irqवापस_t max8925_onkey_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8925_onkey_info *info = data;
	पूर्णांक state;

	state = max8925_reg_पढ़ो(info->i2c, MAX8925_ON_OFF_STATUS);

	input_report_key(info->idev, KEY_POWER, state & SW_INPUT);
	input_sync(info->idev);

	dev_dbg(info->dev, "onkey state:%d\n", state);

	/* Enable hardreset to halt अगर प्रणाली isn't shutकरोwn on समय */
	max8925_set_bits(info->i2c, MAX8925_SYSENSEL,
			 HARDRESET_EN, HARDRESET_EN);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max8925_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8925_onkey_info *info;
	काष्ठा input_dev *input;
	पूर्णांक irq[2], error;

	irq[0] = platक्रमm_get_irq(pdev, 0);
	अगर (irq[0] < 0)
		वापस -EINVAL;

	irq[1] = platक्रमm_get_irq(pdev, 1);
	अगर (irq[1] < 0)
		वापस -EINVAL;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max8925_onkey_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	info->idev = input;
	info->i2c = chip->i2c;
	info->dev = &pdev->dev;
	info->irq[0] = irq[0];
	info->irq[1] = irq[1];

	input->name = "max8925_on";
	input->phys = "max8925_on/input0";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &pdev->dev;
	input_set_capability(input, EV_KEY, KEY_POWER);

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq[0], शून्य,
					  max8925_onkey_handler, IRQF_ONESHOT,
					  "onkey-down", info);
	अगर (error < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			irq[0], error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq[1], शून्य,
					  max8925_onkey_handler, IRQF_ONESHOT,
					  "onkey-up", info);
	अगर (error < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			irq[1], error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(info->idev);
	अगर (error) अणु
		dev_err(chip->dev, "Can't register input device: %d\n", error);
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max8925_onkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max8925_onkey_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev)) अणु
		chip->wakeup_flag |= 1 << info->irq[0];
		chip->wakeup_flag |= 1 << info->irq[1];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max8925_onkey_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max8925_onkey_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev)) अणु
		chip->wakeup_flag &= ~(1 << info->irq[0]);
		chip->wakeup_flag &= ~(1 << info->irq[1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max8925_onkey_pm_ops, max8925_onkey_suspend, max8925_onkey_resume);

अटल काष्ठा platक्रमm_driver max8925_onkey_driver = अणु
	.driver		= अणु
		.name	= "max8925-onkey",
		.pm	= &max8925_onkey_pm_ops,
	पूर्ण,
	.probe		= max8925_onkey_probe,
पूर्ण;
module_platक्रमm_driver(max8925_onkey_driver);

MODULE_DESCRIPTION("Maxim MAX8925 ONKEY driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
