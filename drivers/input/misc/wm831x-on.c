<शैली गुरु>
/*
 * wm831x-on.c - WM831X ON pin driver
 *
 * Copyright (C) 2009 Wolfson Microelectronics plc
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
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mfd/wm831x/core.h>

काष्ठा wm831x_on अणु
	काष्ठा input_dev *dev;
	काष्ठा delayed_work work;
	काष्ठा wm831x *wm831x;
पूर्ण;

/*
 * The chip gives us an पूर्णांकerrupt when the ON pin is निश्चितed but we
 * then need to poll to see when the pin is deनिश्चितed.
 */
अटल व्योम wm831x_poll_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm831x_on *wm831x_on = container_of(work, काष्ठा wm831x_on,
						   work.work);
	काष्ठा wm831x *wm831x = wm831x_on->wm831x;
	पूर्णांक poll, ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_ON_PIN_CONTROL);
	अगर (ret >= 0) अणु
		poll = !(ret & WM831X_ON_PIN_STS);

		input_report_key(wm831x_on->dev, KEY_POWER, poll);
		input_sync(wm831x_on->dev);
	पूर्ण अन्यथा अणु
		dev_err(wm831x->dev, "Failed to read ON status: %d\n", ret);
		poll = 1;
	पूर्ण

	अगर (poll)
		schedule_delayed_work(&wm831x_on->work, 100);
पूर्ण

अटल irqवापस_t wm831x_on_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_on *wm831x_on = data;

	schedule_delayed_work(&wm831x_on->work, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm831x_on_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_on *wm831x_on;
	पूर्णांक irq = wm831x_irq(wm831x, platक्रमm_get_irq(pdev, 0));
	पूर्णांक ret;

	wm831x_on = devm_kzalloc(&pdev->dev, माप(काष्ठा wm831x_on),
				 GFP_KERNEL);
	अगर (!wm831x_on) अणु
		dev_err(&pdev->dev, "Can't allocate data\n");
		वापस -ENOMEM;
	पूर्ण

	wm831x_on->wm831x = wm831x;
	INIT_DELAYED_WORK(&wm831x_on->work, wm831x_poll_on);

	wm831x_on->dev = devm_input_allocate_device(&pdev->dev);
	अगर (!wm831x_on->dev) अणु
		dev_err(&pdev->dev, "Can't allocate input dev\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	wm831x_on->dev->evbit[0] = BIT_MASK(EV_KEY);
	wm831x_on->dev->keybit[BIT_WORD(KEY_POWER)] = BIT_MASK(KEY_POWER);
	wm831x_on->dev->name = "wm831x_on";
	wm831x_on->dev->phys = "wm831x_on/input0";
	wm831x_on->dev->dev.parent = &pdev->dev;

	ret = request_thपढ़ोed_irq(irq, शून्य, wm831x_on_irq,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				   "wm831x_on",
				   wm831x_on);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Unable to request IRQ: %d\n", ret);
		जाओ err_input_dev;
	पूर्ण
	ret = input_रेजिस्टर_device(wm831x_on->dev);
	अगर (ret) अणु
		dev_dbg(&pdev->dev, "Can't register input device: %d\n", ret);
		जाओ err_irq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, wm831x_on);

	वापस 0;

err_irq:
	मुक्त_irq(irq, wm831x_on);
err_input_dev:
err:
	वापस ret;
पूर्ण

अटल पूर्णांक wm831x_on_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x_on *wm831x_on = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	मुक्त_irq(irq, wm831x_on);
	cancel_delayed_work_sync(&wm831x_on->work);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_on_driver = अणु
	.probe		= wm831x_on_probe,
	.हटाओ		= wm831x_on_हटाओ,
	.driver		= अणु
		.name	= "wm831x-on",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(wm831x_on_driver);

MODULE_ALIAS("platform:wm831x-on");
MODULE_DESCRIPTION("WM831x ON pin");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");

