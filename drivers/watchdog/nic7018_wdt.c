<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 National Instruments Corp.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा LOCK			0xA5
#घोषणा UNLOCK			0x5A

#घोषणा WDT_CTRL_RESET_EN	BIT(7)
#घोषणा WDT_RELOAD_PORT_EN	BIT(7)

#घोषणा WDT_CTRL		1
#घोषणा WDT_RELOAD_CTRL		2
#घोषणा WDT_PRESET_PRESCALE	4
#घोषणा WDT_REG_LOCK		5
#घोषणा WDT_COUNT		6
#घोषणा WDT_RELOAD_PORT		7

#घोषणा WDT_MIN_TIMEOUT		1
#घोषणा WDT_MAX_TIMEOUT		464
#घोषणा WDT_DEFAULT_TIMEOUT	80

#घोषणा WDT_MAX_COUNTER		15

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		 "Watchdog timeout in seconds. (default="
		 __MODULE_STRING(WDT_DEFAULT_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started. (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा nic7018_wdt अणु
	u16 io_base;
	u32 period;
	काष्ठा watchकरोg_device wdd;
पूर्ण;

काष्ठा nic7018_config अणु
	u32 period;
	u8 भागider;
पूर्ण;

अटल स्थिर काष्ठा nic7018_config nic7018_configs[] = अणु
	अणु  2, 4 पूर्ण,
	अणु 32, 5 पूर्ण,
पूर्ण;

अटल अंतरभूत u32 nic7018_समयout(u32 period, u8 counter)
अणु
	वापस period * counter - period / 2;
पूर्ण

अटल स्थिर काष्ठा nic7018_config *nic7018_get_config(u32 समयout,
						       u8 *counter)
अणु
	स्थिर काष्ठा nic7018_config *config;
	u8 count;

	अगर (समयout < 30 && समयout != 16) अणु
		config = &nic7018_configs[0];
		count = समयout / 2 + 1;
	पूर्ण अन्यथा अणु
		config = &nic7018_configs[1];
		count = DIV_ROUND_UP(समयout + 16, 32);

		अगर (count > WDT_MAX_COUNTER)
			count = WDT_MAX_COUNTER;
	पूर्ण
	*counter = count;
	वापस config;
पूर्ण

अटल पूर्णांक nic7018_set_समयout(काष्ठा watchकरोg_device *wdd,
			       अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा nic7018_wdt *wdt = watchकरोg_get_drvdata(wdd);
	स्थिर काष्ठा nic7018_config *config;
	u8 counter;

	config = nic7018_get_config(समयout, &counter);

	outb(counter << 4 | config->भागider,
	     wdt->io_base + WDT_PRESET_PRESCALE);

	wdd->समयout = nic7018_समयout(config->period, counter);
	wdt->period = config->period;

	वापस 0;
पूर्ण

अटल पूर्णांक nic7018_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा nic7018_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u8 control;

	nic7018_set_समयout(wdd, wdd->समयout);

	control = inb(wdt->io_base + WDT_RELOAD_CTRL);
	outb(control | WDT_RELOAD_PORT_EN, wdt->io_base + WDT_RELOAD_CTRL);

	outb(1, wdt->io_base + WDT_RELOAD_PORT);

	control = inb(wdt->io_base + WDT_CTRL);
	outb(control | WDT_CTRL_RESET_EN, wdt->io_base + WDT_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक nic7018_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा nic7018_wdt *wdt = watchकरोg_get_drvdata(wdd);

	outb(0, wdt->io_base + WDT_CTRL);
	outb(0, wdt->io_base + WDT_RELOAD_CTRL);
	outb(0xF0, wdt->io_base + WDT_PRESET_PRESCALE);

	वापस 0;
पूर्ण

अटल पूर्णांक nic7018_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा nic7018_wdt *wdt = watchकरोg_get_drvdata(wdd);

	outb(1, wdt->io_base + WDT_RELOAD_PORT);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nic7018_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा nic7018_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u8 count;

	count = inb(wdt->io_base + WDT_COUNT) & 0xF;
	अगर (!count)
		वापस 0;

	वापस nic7018_समयout(wdt->period, count);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info nic7018_wdd_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "NIC7018 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops nic7018_wdd_ops = अणु
	.owner = THIS_MODULE,
	.start = nic7018_start,
	.stop = nic7018_stop,
	.ping = nic7018_ping,
	.set_समयout = nic7018_set_समयout,
	.get_समयleft = nic7018_get_समयleft,
पूर्ण;

अटल पूर्णांक nic7018_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा nic7018_wdt *wdt;
	काष्ठा resource *io_rc;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, wdt);

	io_rc = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!io_rc) अणु
		dev_err(dev, "missing IO resources\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!devm_request_region(dev, io_rc->start, resource_size(io_rc),
				 KBUILD_MODNAME)) अणु
		dev_err(dev, "failed to get IO region\n");
		वापस -EBUSY;
	पूर्ण

	wdt->io_base = io_rc->start;
	wdd = &wdt->wdd;
	wdd->info = &nic7018_wdd_info;
	wdd->ops = &nic7018_wdd_ops;
	wdd->min_समयout = WDT_MIN_TIMEOUT;
	wdd->max_समयout = WDT_MAX_TIMEOUT;
	wdd->समयout = WDT_DEFAULT_TIMEOUT;
	wdd->parent = dev;

	watchकरोg_set_drvdata(wdd, wdt);
	watchकरोg_set_nowayout(wdd, nowayout);
	watchकरोg_init_समयout(wdd, समयout, dev);

	/* Unlock WDT रेजिस्टर */
	outb(UNLOCK, wdt->io_base + WDT_REG_LOCK);

	ret = watchकरोg_रेजिस्टर_device(wdd);
	अगर (ret) अणु
		outb(LOCK, wdt->io_base + WDT_REG_LOCK);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "io_base=0x%04X, timeout=%d, nowayout=%d\n",
		wdt->io_base, समयout, nowayout);
	वापस 0;
पूर्ण

अटल पूर्णांक nic7018_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nic7018_wdt *wdt = platक्रमm_get_drvdata(pdev);

	watchकरोg_unरेजिस्टर_device(&wdt->wdd);

	/* Lock WDT रेजिस्टर */
	outb(LOCK, wdt->io_base + WDT_REG_LOCK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id nic7018_device_ids[] = अणु
	अणु"NIC7018", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, nic7018_device_ids);

अटल काष्ठा platक्रमm_driver watchकरोg_driver = अणु
	.probe = nic7018_probe,
	.हटाओ = nic7018_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.acpi_match_table = ACPI_PTR(nic7018_device_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(watchकरोg_driver);

MODULE_DESCRIPTION("National Instruments NIC7018 Watchdog driver");
MODULE_AUTHOR("Hui Chun Ong <hui.chun.ong@ni.com>");
MODULE_LICENSE("GPL");
