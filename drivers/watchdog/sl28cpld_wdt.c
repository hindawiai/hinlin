<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sl28cpld watchकरोg driver
 *
 * Copyright 2020 Kontron Europe GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

/*
 * Watchकरोg समयr block रेजिस्टरs.
 */
#घोषणा WDT_CTRL			0x00
#घोषणा  WDT_CTRL_EN			BIT(0)
#घोषणा  WDT_CTRL_LOCK			BIT(2)
#घोषणा  WDT_CTRL_ASSERT_SYS_RESET	BIT(6)
#घोषणा  WDT_CTRL_ASSERT_WDT_TIMEOUT	BIT(7)
#घोषणा WDT_TIMEOUT			0x01
#घोषणा WDT_KICK			0x02
#घोषणा  WDT_KICK_VALUE			0x6b
#घोषणा WDT_COUNT			0x03

#घोषणा WDT_DEFAULT_TIMEOUT		10

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक समयout;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Initial watchdog timeout in seconds");

काष्ठा sl28cpld_wdt अणु
	काष्ठा watchकरोg_device wdd;
	काष्ठा regmap *regmap;
	u32 offset;
	bool निश्चित_wdt_समयout;
पूर्ण;

अटल पूर्णांक sl28cpld_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sl28cpld_wdt *wdt = watchकरोg_get_drvdata(wdd);

	वापस regmap_ग_लिखो(wdt->regmap, wdt->offset + WDT_KICK,
			    WDT_KICK_VALUE);
पूर्ण

अटल पूर्णांक sl28cpld_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sl28cpld_wdt *wdt = watchकरोg_get_drvdata(wdd);
	अचिन्हित पूर्णांक val;

	val = WDT_CTRL_EN | WDT_CTRL_ASSERT_SYS_RESET;
	अगर (wdt->निश्चित_wdt_समयout)
		val |= WDT_CTRL_ASSERT_WDT_TIMEOUT;
	अगर (nowayout)
		val |= WDT_CTRL_LOCK;

	वापस regmap_update_bits(wdt->regmap, wdt->offset + WDT_CTRL,
				  val, val);
पूर्ण

अटल पूर्णांक sl28cpld_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sl28cpld_wdt *wdt = watchकरोg_get_drvdata(wdd);

	वापस regmap_update_bits(wdt->regmap, wdt->offset + WDT_CTRL,
				  WDT_CTRL_EN, 0);
पूर्ण

अटल अचिन्हित पूर्णांक sl28cpld_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sl28cpld_wdt *wdt = watchकरोg_get_drvdata(wdd);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(wdt->regmap, wdt->offset + WDT_COUNT, &val);
	अगर (ret)
		वापस 0;

	वापस val;
पूर्ण

अटल पूर्णांक sl28cpld_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				    अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sl28cpld_wdt *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(wdt->regmap, wdt->offset + WDT_TIMEOUT, समयout);
	अगर (ret)
		वापस ret;

	wdd->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sl28cpld_wdt_info = अणु
	.options = WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = "sl28cpld watchdog",
पूर्ण;

अटल काष्ठा watchकरोg_ops sl28cpld_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = sl28cpld_wdt_start,
	.stop = sl28cpld_wdt_stop,
	.ping = sl28cpld_wdt_ping,
	.set_समयout = sl28cpld_wdt_set_समयout,
	.get_समयleft = sl28cpld_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक sl28cpld_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wdd;
	काष्ठा sl28cpld_wdt *wdt;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!pdev->dev.parent)
		वापस -ENODEV;

	wdt = devm_kzalloc(&pdev->dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!wdt->regmap)
		वापस -ENODEV;

	ret = device_property_पढ़ो_u32(&pdev->dev, "reg", &wdt->offset);
	अगर (ret)
		वापस -EINVAL;

	wdt->निश्चित_wdt_समयout = device_property_पढ़ो_bool(&pdev->dev,
							    "kontron,assert-wdt-timeout-pin");

	/* initialize काष्ठा watchकरोg_device */
	wdd = &wdt->wdd;
	wdd->parent = &pdev->dev;
	wdd->info = &sl28cpld_wdt_info;
	wdd->ops = &sl28cpld_wdt_ops;
	wdd->min_समयout = 1;
	wdd->max_समयout = 255;

	watchकरोg_set_drvdata(wdd, wdt);
	watchकरोg_stop_on_reboot(wdd);

	/*
	 * Read the status early, in हाल of an error, we haven't modअगरied the
	 * hardware.
	 */
	ret = regmap_पढ़ो(wdt->regmap, wdt->offset + WDT_CTRL, &status);
	अगर (ret)
		वापस ret;

	/*
	 * Initial समयout value, may be overwritten by device tree or module
	 * parmeter in watchकरोg_init_समयout().
	 *
	 * Reading a zero here means that either the hardware has a शेष
	 * value of zero (which is very unlikely and definitely a hardware
	 * bug) or the bootloader set it to zero. In any हाल, we handle
	 * this हाल gracefully and set out own समयout.
	 */
	ret = regmap_पढ़ो(wdt->regmap, wdt->offset + WDT_TIMEOUT, &val);
	अगर (ret)
		वापस ret;

	अगर (val)
		wdd->समयout = val;
	अन्यथा
		wdd->समयout = WDT_DEFAULT_TIMEOUT;

	watchकरोg_init_समयout(wdd, समयout, &pdev->dev);
	sl28cpld_wdt_set_समयout(wdd, wdd->समयout);

	/* अगर the watchकरोg is locked, we set nowayout */
	अगर (status & WDT_CTRL_LOCK)
		nowayout = true;
	watchकरोg_set_nowayout(wdd, nowayout);

	/*
	 * If watchकरोg is alपढ़ोy running, keep it enabled, but make
	 * sure its mode is set correctly.
	 */
	अगर (status & WDT_CTRL_EN) अणु
		sl28cpld_wdt_start(wdd);
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(&pdev->dev, wdd);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register watchdog device\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "initial timeout %d sec%s\n",
		 wdd->समयout, nowayout ? ", nowayout" : "");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sl28cpld_wdt_of_match[] = अणु
	अणु .compatible = "kontron,sl28cpld-wdt" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sl28cpld_wdt_of_match);

अटल काष्ठा platक्रमm_driver sl28cpld_wdt_driver = अणु
	.probe = sl28cpld_wdt_probe,
	.driver = अणु
		.name = "sl28cpld-wdt",
		.of_match_table = sl28cpld_wdt_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sl28cpld_wdt_driver);

MODULE_DESCRIPTION("sl28cpld Watchdog Driver");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
