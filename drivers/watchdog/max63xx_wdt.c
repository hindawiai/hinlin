<शैली गुरु>
/*
 * drivers/अक्षर/watchकरोg/max63xx_wdt.c
 *
 * Driver क्रम max63अणु69,70,71,72,73,74पूर्ण watchकरोg समयrs
 *
 * Copyright (C) 2009 Marc Zyngier <maz@misterjones.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * This driver assumes the watchकरोg pins are memory mapped (as it is
 * the हाल क्रम the Arcom Zeus). Should it be connected over GPIOs or
 * another पूर्णांकerface, some असलtraction will have to be पूर्णांकroduced.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा DEFAULT_HEARTBEAT 60
#घोषणा MAX_HEARTBEAT     60

अटल अचिन्हित पूर्णांक heartbeat = DEFAULT_HEARTBEAT;
अटल bool nowayout  = WATCHDOG_NOWAYOUT;

/*
 * Memory mapping: a single byte, 3 first lower bits to select bit 3
 * to ping the watchकरोg.
 */
#घोषणा MAX6369_WDSET	(7 << 0)
#घोषणा MAX6369_WDI	(1 << 3)

#घोषणा MAX6369_WDSET_DISABLED	3

अटल पूर्णांक nodelay;

काष्ठा max63xx_wdt अणु
	काष्ठा watchकरोg_device wdd;
	स्थिर काष्ठा max63xx_समयout *समयout;

	/* memory mapping */
	व्योम __iomem *base;
	spinlock_t lock;

	/* WDI and WSET bits ग_लिखो access routines */
	व्योम (*ping)(काष्ठा max63xx_wdt *wdt);
	व्योम (*set)(काष्ठा max63xx_wdt *wdt, u8 set);
पूर्ण;

/*
 * The समयout values used are actually the असलolute minimum the chip
 * offers. Typical values on my board are slightly over twice as दीर्घ
 * (10s setting ends up with a 25s समयout), and can be up to 3 बार
 * the nominal setting (according to the datasheet). So please take
 * these values with a grain of salt. Same goes क्रम the initial delay
 * "feature". Only max6373/74 have a few settings without this initial
 * delay (selected with the "nodelay" parameter).
 *
 * I also decided to हटाओ from the tables any समयout smaller than a
 * second, as it looked completly overसमाप्त...
 */

/* Timeouts in second */
काष्ठा max63xx_समयout अणु
	स्थिर u8 wdset;
	स्थिर u8 tdelay;
	स्थिर u8 twd;
पूर्ण;

अटल स्थिर काष्ठा max63xx_समयout max6369_table[] = अणु
	अणु 5,  1,  1 पूर्ण,
	अणु 6, 10, 10 पूर्ण,
	अणु 7, 60, 60 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा max63xx_समयout max6371_table[] = अणु
	अणु 6, 60,  3 पूर्ण,
	अणु 7, 60, 60 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा max63xx_समयout max6373_table[] = अणु
	अणु 2, 60,  1 पूर्ण,
	अणु 5,  0,  1 पूर्ण,
	अणु 1,  3,  3 पूर्ण,
	अणु 7, 60, 10 पूर्ण,
	अणु 6,  0, 10 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा max63xx_समयout *
max63xx_select_समयout(काष्ठा max63xx_समयout *table, पूर्णांक value)
अणु
	जबतक (table->twd) अणु
		अगर (value <= table->twd) अणु
			अगर (nodelay && table->tdelay == 0)
				वापस table;

			अगर (!nodelay)
				वापस table;
		पूर्ण

		table++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक max63xx_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा max63xx_wdt *wdt = watchकरोg_get_drvdata(wdd);

	wdt->ping(wdt);
	वापस 0;
पूर्ण

अटल पूर्णांक max63xx_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा max63xx_wdt *wdt = watchकरोg_get_drvdata(wdd);

	wdt->set(wdt, wdt->समयout->wdset);

	/* check क्रम a edge triggered startup */
	अगर (wdt->समयout->tdelay == 0)
		wdt->ping(wdt);
	वापस 0;
पूर्ण

अटल पूर्णांक max63xx_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा max63xx_wdt *wdt = watchकरोg_get_drvdata(wdd);

	wdt->set(wdt, MAX6369_WDSET_DISABLED);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops max63xx_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = max63xx_wdt_start,
	.stop = max63xx_wdt_stop,
	.ping = max63xx_wdt_ping,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info max63xx_wdt_info = अणु
	.options = WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "max63xx Watchdog",
पूर्ण;

अटल व्योम max63xx_mmap_ping(काष्ठा max63xx_wdt *wdt)
अणु
	u8 val;

	spin_lock(&wdt->lock);

	val = __raw_पढ़ोb(wdt->base);

	__raw_ग_लिखोb(val | MAX6369_WDI, wdt->base);
	__raw_ग_लिखोb(val & ~MAX6369_WDI, wdt->base);

	spin_unlock(&wdt->lock);
पूर्ण

अटल व्योम max63xx_mmap_set(काष्ठा max63xx_wdt *wdt, u8 set)
अणु
	u8 val;

	spin_lock(&wdt->lock);

	val = __raw_पढ़ोb(wdt->base);
	val &= ~MAX6369_WDSET;
	val |= set & MAX6369_WDSET;
	__raw_ग_लिखोb(val, wdt->base);

	spin_unlock(&wdt->lock);
पूर्ण

अटल पूर्णांक max63xx_mmap_init(काष्ठा platक्रमm_device *p, काष्ठा max63xx_wdt *wdt)
अणु
	wdt->base = devm_platक्रमm_ioremap_resource(p, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	spin_lock_init(&wdt->lock);

	wdt->ping = max63xx_mmap_ping;
	wdt->set = max63xx_mmap_set;
	वापस 0;
पूर्ण

अटल पूर्णांक max63xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा max63xx_wdt *wdt;
	काष्ठा max63xx_समयout *table;
	पूर्णांक err;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	table = (काष्ठा max63xx_समयout *)pdev->id_entry->driver_data;

	अगर (heartbeat < 1 || heartbeat > MAX_HEARTBEAT)
		heartbeat = DEFAULT_HEARTBEAT;

	wdt->समयout = max63xx_select_समयout(table, heartbeat);
	अगर (!wdt->समयout) अणु
		dev_err(dev, "unable to satisfy %ds heartbeat request\n",
			heartbeat);
		वापस -EINVAL;
	पूर्ण

	err = max63xx_mmap_init(pdev, wdt);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, &wdt->wdd);
	watchकरोg_set_drvdata(&wdt->wdd, wdt);

	wdt->wdd.parent = dev;
	wdt->wdd.समयout = wdt->समयout->twd;
	wdt->wdd.info = &max63xx_wdt_info;
	wdt->wdd.ops = &max63xx_wdt_ops;

	watchकरोg_set_nowayout(&wdt->wdd, nowayout);

	err = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
	अगर (err)
		वापस err;

	dev_info(dev, "using %ds heartbeat with %ds initial delay\n",
		 wdt->समयout->twd, wdt->समयout->tdelay);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max63xx_id_table[] = अणु
	अणु "max6369_wdt", (kernel_uदीर्घ_t)max6369_table, पूर्ण,
	अणु "max6370_wdt", (kernel_uदीर्घ_t)max6369_table, पूर्ण,
	अणु "max6371_wdt", (kernel_uदीर्घ_t)max6371_table, पूर्ण,
	अणु "max6372_wdt", (kernel_uदीर्घ_t)max6371_table, पूर्ण,
	अणु "max6373_wdt", (kernel_uदीर्घ_t)max6373_table, पूर्ण,
	अणु "max6374_wdt", (kernel_uदीर्घ_t)max6373_table, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max63xx_id_table);

अटल काष्ठा platक्रमm_driver max63xx_wdt_driver = अणु
	.probe		= max63xx_wdt_probe,
	.id_table	= max63xx_id_table,
	.driver		= अणु
		.name	= "max63xx_wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(max63xx_wdt_driver);

MODULE_AUTHOR("Marc Zyngier <maz@misterjones.org>");
MODULE_DESCRIPTION("max63xx Watchdog Driver");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
		 "Watchdog heartbeat period in seconds from 1 to "
		 __MODULE_STRING(MAX_HEARTBEAT) ", default "
		 __MODULE_STRING(DEFAULT_HEARTBEAT));

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

module_param(nodelay, पूर्णांक, 0);
MODULE_PARM_DESC(nodelay,
		 "Force selection of a timeout setting without initial delay "
		 "(max6373/74 only, default=0)");

MODULE_LICENSE("GPL v2");
