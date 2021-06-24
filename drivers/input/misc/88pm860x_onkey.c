<शैली गुरु>
/*
 * 88pm860x_onkey.c - Marvell 88PM860x ONKEY driver
 *
 * Copyright (C) 2009-2010 Marvell International Ltd.
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
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#घोषणा PM8607_WAKEUP		0x0b

#घोषणा LONG_ONKEY_EN		(1 << 1)
#घोषणा ONKEY_STATUS		(1 << 0)

काष्ठा pm860x_onkey_info अणु
	काष्ठा input_dev	*idev;
	काष्ठा pm860x_chip	*chip;
	काष्ठा i2c_client	*i2c;
	काष्ठा device		*dev;
	पूर्णांक			irq;
पूर्ण;

/* 88PM860x gives us an पूर्णांकerrupt when ONKEY is held */
अटल irqवापस_t pm860x_onkey_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_onkey_info *info = data;
	पूर्णांक ret;

	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_STATUS_2);
	ret &= ONKEY_STATUS;
	input_report_key(info->idev, KEY_POWER, ret);
	input_sync(info->idev);

	/* Enable 8-second दीर्घ onkey detection */
	pm860x_set_bits(info->i2c, PM8607_WAKEUP, 3, LONG_ONKEY_EN);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm860x_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_onkey_info *info;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा pm860x_onkey_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->chip = chip;
	info->i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->dev = &pdev->dev;
	info->irq = irq;

	info->idev = devm_input_allocate_device(&pdev->dev);
	अगर (!info->idev) अणु
		dev_err(chip->dev, "Failed to allocate input dev\n");
		वापस -ENOMEM;
	पूर्ण

	info->idev->name = "88pm860x_on";
	info->idev->phys = "88pm860x_on/input0";
	info->idev->id.bustype = BUS_I2C;
	info->idev->dev.parent = &pdev->dev;
	info->idev->evbit[0] = BIT_MASK(EV_KEY);
	info->idev->keybit[BIT_WORD(KEY_POWER)] = BIT_MASK(KEY_POWER);

	ret = input_रेजिस्टर_device(info->idev);
	अगर (ret) अणु
		dev_err(chip->dev, "Can't register input device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
					pm860x_onkey_handler, IRQF_ONESHOT,
					"onkey", info);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm860x_onkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag |= 1 << PM8607_IRQ_ONKEY;
	वापस 0;
पूर्ण
अटल पूर्णांक __maybe_unused pm860x_onkey_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag &= ~(1 << PM8607_IRQ_ONKEY);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pm860x_onkey_pm_ops, pm860x_onkey_suspend, pm860x_onkey_resume);

अटल काष्ठा platक्रमm_driver pm860x_onkey_driver = अणु
	.driver		= अणु
		.name	= "88pm860x-onkey",
		.pm	= &pm860x_onkey_pm_ops,
	पूर्ण,
	.probe		= pm860x_onkey_probe,
पूर्ण;
module_platक्रमm_driver(pm860x_onkey_driver);

MODULE_DESCRIPTION("Marvell 88PM860x ONKEY driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
