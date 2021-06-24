<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2011 Paul Parsons <lost.distance@yahoo.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/asic3.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>

/*
 *	The HTC ASIC3 LED GPIOs are inमाला_दो, not outमाला_दो.
 *	Hence we turn the LEDs on/off via the TimeBase रेजिस्टर.
 */

/*
 *	When TimeBase is 4 the घड़ी resolution is about 32Hz.
 *	This driver supports hardware blinking with an on+off
 *	period from 62ms (2 घड़ीs) to 125s (4000 घड़ीs).
 */
#घोषणा MS_TO_CLK(ms)	DIV_ROUND_CLOSEST(((ms)*1024), 32000)
#घोषणा CLK_TO_MS(clk)	(((clk)*32000)/1024)
#घोषणा MAX_CLK		4000            /* Fits पूर्णांकo 12-bit Time रेजिस्टरs */
#घोषणा MAX_MS		CLK_TO_MS(MAX_CLK)

अटल स्थिर अचिन्हित पूर्णांक led_n_base[ASIC3_NUM_LEDS] = अणु
	[0] = ASIC3_LED_0_Base,
	[1] = ASIC3_LED_1_Base,
	[2] = ASIC3_LED_2_Base,
पूर्ण;

अटल व्योम brightness_set(काष्ठा led_classdev *cdev,
	क्रमागत led_brightness value)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(cdev->dev->parent);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);
	u32 समयbase;
	अचिन्हित पूर्णांक base;

	समयbase = (value == LED_OFF) ? 0 : (LED_EN|0x4);

	base = led_n_base[cell->id];
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_PeriodTime), 32);
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_DutyTime), 32);
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_AutoStopCount), 0);
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_TimeBase), समयbase);
पूर्ण

अटल पूर्णांक blink_set(काष्ठा led_classdev *cdev,
	अचिन्हित दीर्घ *delay_on,
	अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(cdev->dev->parent);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा asic3 *asic = dev_get_drvdata(pdev->dev.parent);
	u32 on;
	u32 off;
	अचिन्हित पूर्णांक base;

	अगर (*delay_on > MAX_MS || *delay_off > MAX_MS)
		वापस -EINVAL;

	अगर (*delay_on == 0 && *delay_off == 0) अणु
		/* If both are zero then a sensible शेष should be chosen */
		on = MS_TO_CLK(500);
		off = MS_TO_CLK(500);
	पूर्ण अन्यथा अणु
		on = MS_TO_CLK(*delay_on);
		off = MS_TO_CLK(*delay_off);
		अगर ((on + off) > MAX_CLK)
			वापस -EINVAL;
	पूर्ण

	base = led_n_base[cell->id];
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_PeriodTime), (on + off));
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_DutyTime), on);
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_AutoStopCount), 0);
	asic3_ग_लिखो_रेजिस्टर(asic, (base + ASIC3_LED_TimeBase), (LED_EN|0x4));

	*delay_on = CLK_TO_MS(on);
	*delay_off = CLK_TO_MS(off);

	वापस 0;
पूर्ण

अटल पूर्णांक asic3_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3_led *led = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	ret = mfd_cell_enable(pdev);
	अगर (ret < 0)
		वापस ret;

	led->cdev = devm_kzalloc(&pdev->dev, माप(काष्ठा led_classdev),
				GFP_KERNEL);
	अगर (!led->cdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	led->cdev->name = led->name;
	led->cdev->flags = LED_CORE_SUSPENDRESUME;
	led->cdev->brightness_set = brightness_set;
	led->cdev->blink_set = blink_set;
	led->cdev->शेष_trigger = led->शेष_trigger;

	ret = led_classdev_रेजिस्टर(&pdev->dev, led->cdev);
	अगर (ret < 0)
		जाओ out;

	वापस 0;

out:
	(व्योम) mfd_cell_disable(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक asic3_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा asic3_led *led = dev_get_platdata(&pdev->dev);

	led_classdev_unरेजिस्टर(led->cdev);

	वापस mfd_cell_disable(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक asic3_led_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	पूर्णांक ret;

	ret = 0;
	अगर (cell->suspend)
		ret = (*cell->suspend)(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक asic3_led_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	पूर्णांक ret;

	ret = 0;
	अगर (cell->resume)
		ret = (*cell->resume)(pdev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(asic3_led_pm_ops, asic3_led_suspend, asic3_led_resume);

अटल काष्ठा platक्रमm_driver asic3_led_driver = अणु
	.probe		= asic3_led_probe,
	.हटाओ		= asic3_led_हटाओ,
	.driver		= अणु
		.name	= "leds-asic3",
		.pm	= &asic3_led_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(asic3_led_driver);

MODULE_AUTHOR("Paul Parsons <lost.distance@yahoo.com>");
MODULE_DESCRIPTION("HTC ASIC3 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-asic3");
