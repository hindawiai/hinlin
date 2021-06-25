<शैली गुरु>
/*
 * Marvell 88PM80x ONKEY driver
 *
 * Copyright (C) 2012 Marvell International Ltd.
 * Haojian Zhuang <haojian.zhuang@marvell.com>
 * Qiao Zhou <zhouqiao@marvell.com>
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
#समावेश <linux/input.h>
#समावेश <linux/mfd/88pm80x.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा PM800_LONG_ONKEY_EN		(1 << 0)
#घोषणा PM800_LONG_KEY_DELAY		(8)	/* 1 .. 16 seconds */
#घोषणा PM800_LONKEY_PRESS_TIME		((PM800_LONG_KEY_DELAY-1) << 4)
#घोषणा PM800_LONKEY_PRESS_TIME_MASK	(0xF0)
#घोषणा PM800_SW_PDOWN			(1 << 5)

काष्ठा pm80x_onkey_info अणु
	काष्ठा input_dev *idev;
	काष्ठा pm80x_chip *pm80x;
	काष्ठा regmap *map;
	पूर्णांक irq;
पूर्ण;

/* 88PM80x gives us an पूर्णांकerrupt when ONKEY is held */
अटल irqवापस_t pm80x_onkey_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm80x_onkey_info *info = data;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(info->map, PM800_STATUS_1, &val);
	अगर (ret < 0) अणु
		dev_err(info->idev->dev.parent, "failed to read status: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण
	val &= PM800_ONKEY_STS1;

	input_report_key(info->idev, KEY_POWER, val);
	input_sync(info->idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pm80x_onkey_pm_ops, pm80x_dev_suspend,
			 pm80x_dev_resume);

अटल पूर्णांक pm80x_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु

	काष्ठा pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm80x_onkey_info *info;
	पूर्णांक err;

	info = kzalloc(माप(काष्ठा pm80x_onkey_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->pm80x = chip;

	info->irq = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq < 0) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	info->map = info->pm80x->regmap;
	अगर (!info->map) अणु
		dev_err(&pdev->dev, "no regmap!\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	info->idev = input_allocate_device();
	अगर (!info->idev) अणु
		dev_err(&pdev->dev, "Failed to allocate input dev\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	info->idev->name = "88pm80x_on";
	info->idev->phys = "88pm80x_on/input0";
	info->idev->id.bustype = BUS_I2C;
	info->idev->dev.parent = &pdev->dev;
	info->idev->evbit[0] = BIT_MASK(EV_KEY);
	__set_bit(KEY_POWER, info->idev->keybit);

	err = pm80x_request_irq(info->pm80x, info->irq, pm80x_onkey_handler,
					    IRQF_ONESHOT, "onkey", info);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, err);
		जाओ out_reg;
	पूर्ण

	err = input_रेजिस्टर_device(info->idev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't register input device: %d\n", err);
		जाओ out_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	/* Enable दीर्घ onkey detection */
	regmap_update_bits(info->map, PM800_RTC_MISC4, PM800_LONG_ONKEY_EN,
			   PM800_LONG_ONKEY_EN);
	/* Set 8-second पूर्णांकerval */
	regmap_update_bits(info->map, PM800_RTC_MISC3,
			   PM800_LONKEY_PRESS_TIME_MASK,
			   PM800_LONKEY_PRESS_TIME);

	device_init_wakeup(&pdev->dev, 1);
	वापस 0;

out_irq:
	pm80x_मुक्त_irq(info->pm80x, info->irq, info);
out_reg:
	input_मुक्त_device(info->idev);
out:
	kमुक्त(info);
	वापस err;
पूर्ण

अटल पूर्णांक pm80x_onkey_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm80x_onkey_info *info = platक्रमm_get_drvdata(pdev);

	pm80x_मुक्त_irq(info->pm80x, info->irq, info);
	input_unरेजिस्टर_device(info->idev);
	kमुक्त(info);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm80x_onkey_driver = अणु
	.driver = अणु
		   .name = "88pm80x-onkey",
		   .pm = &pm80x_onkey_pm_ops,
		   पूर्ण,
	.probe = pm80x_onkey_probe,
	.हटाओ = pm80x_onkey_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm80x_onkey_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Marvell 88PM80x ONKEY driver");
MODULE_AUTHOR("Qiao Zhou <zhouqiao@marvell.com>");
MODULE_ALIAS("platform:88pm80x-onkey");
