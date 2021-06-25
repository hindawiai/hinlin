<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम DA9063 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: Mariusz Wojtasik <mariusz.wojtasik@diasemi.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>
#समावेश <linux/mfd/da9063/core.h>
#समावेश <linux/regmap.h>

/*
 * Watchकरोg selector to समयout in seconds.
 *   0: WDT disabled;
 *   others: समयout = 2048 ms * 2^(TWDSCALE-1).
 */
अटल स्थिर अचिन्हित पूर्णांक wdt_समयout[] = अणु 0, 2, 4, 8, 16, 32, 65, 131 पूर्ण;
#घोषणा DA9063_TWDSCALE_DISABLE		0
#घोषणा DA9063_TWDSCALE_MIN		1
#घोषणा DA9063_TWDSCALE_MAX		(ARRAY_SIZE(wdt_समयout) - 1)
#घोषणा DA9063_WDT_MIN_TIMEOUT		wdt_समयout[DA9063_TWDSCALE_MIN]
#घोषणा DA9063_WDT_MAX_TIMEOUT		wdt_समयout[DA9063_TWDSCALE_MAX]
#घोषणा DA9063_WDG_TIMEOUT		wdt_समयout[3]
#घोषणा DA9063_RESET_PROTECTION_MS	256

अटल अचिन्हित पूर्णांक da9063_wdt_समयout_to_sel(अचिन्हित पूर्णांक secs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = DA9063_TWDSCALE_MIN; i <= DA9063_TWDSCALE_MAX; i++) अणु
		अगर (wdt_समयout[i] >= secs)
			वापस i;
	पूर्ण

	वापस DA9063_TWDSCALE_MAX;
पूर्ण

/*
 * Read the currently active समयout.
 * Zero means the watchकरोg is disabled.
 */
अटल अचिन्हित पूर्णांक da9063_wdt_पढ़ो_समयout(काष्ठा da9063 *da9063)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(da9063->regmap, DA9063_REG_CONTROL_D, &val);

	वापस wdt_समयout[val & DA9063_TWDSCALE_MASK];
पूर्ण

अटल पूर्णांक da9063_wdt_disable_समयr(काष्ठा da9063 *da9063)
अणु
	वापस regmap_update_bits(da9063->regmap, DA9063_REG_CONTROL_D,
				  DA9063_TWDSCALE_MASK,
				  DA9063_TWDSCALE_DISABLE);
पूर्ण

अटल पूर्णांक
da9063_wdt_update_समयout(काष्ठा da9063 *da9063, अचिन्हित पूर्णांक समयout)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	/*
	 * The watchकरोg triggers a reboot अगर a समयout value is alपढ़ोy
	 * programmed because the समयout value combines two functions
	 * in one: indicating the counter limit and starting the watchकरोg.
	 * The watchकरोg must be disabled to be able to change the समयout
	 * value अगर the watchकरोg is alपढ़ोy running. Then we can set the
	 * new समयout value which enables the watchकरोg again.
	 */
	ret = da9063_wdt_disable_समयr(da9063);
	अगर (ret)
		वापस ret;

	usleep_range(150, 300);
	regval = da9063_wdt_समयout_to_sel(समयout);

	वापस regmap_update_bits(da9063->regmap, DA9063_REG_CONTROL_D,
				  DA9063_TWDSCALE_MASK, regval);
पूर्ण

अटल पूर्णांक da9063_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा da9063 *da9063 = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = da9063_wdt_update_समयout(da9063, wdd->समयout);
	अगर (ret)
		dev_err(da9063->dev, "Watchdog failed to start (err = %d)\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा da9063 *da9063 = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = da9063_wdt_disable_समयr(da9063);
	अगर (ret)
		dev_alert(da9063->dev, "Watchdog failed to stop (err = %d)\n",
			  ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा da9063 *da9063 = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(da9063->regmap, DA9063_REG_CONTROL_F,
			   DA9063_WATCHDOG);
	अगर (ret)
		dev_alert(da9063->dev, "Failed to ping the watchdog (err = %d)\n",
			  ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा da9063 *da9063 = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret = 0;

	/*
	 * There are two हालs when a set_समयout() will be called:
	 * 1. The watchकरोg is off and someone wants to set the समयout क्रम the
	 *    further use.
	 * 2. The watchकरोg is alपढ़ोy running and a new समयout value should be
	 *    set.
	 *
	 * The watchकरोg can't store a समयout value not equal zero without
	 * enabling the watchकरोg, so the समयout must be buffered by the driver.
	 */
	अगर (watchकरोg_active(wdd))
		ret = da9063_wdt_update_समयout(da9063, समयout);

	अगर (ret)
		dev_err(da9063->dev, "Failed to set watchdog timeout (err = %d)\n",
			ret);
	अन्यथा
		wdd->समयout = wdt_समयout[da9063_wdt_समयout_to_sel(समयout)];

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_wdt_restart(काष्ठा watchकरोg_device *wdd, अचिन्हित दीर्घ action,
			      व्योम *data)
अणु
	काष्ठा da9063 *da9063 = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(da9063->regmap, DA9063_REG_CONTROL_F,
			   DA9063_SHUTDOWN);
	अगर (ret)
		dev_alert(da9063->dev, "Failed to shutdown (err = %d)\n",
			  ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info da9063_watchकरोg_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = "DA9063 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops da9063_watchकरोg_ops = अणु
	.owner = THIS_MODULE,
	.start = da9063_wdt_start,
	.stop = da9063_wdt_stop,
	.ping = da9063_wdt_ping,
	.set_समयout = da9063_wdt_set_समयout,
	.restart = da9063_wdt_restart,
पूर्ण;

अटल पूर्णांक da9063_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9063 *da9063;
	काष्ठा watchकरोg_device *wdd;
	अचिन्हित पूर्णांक समयout;

	अगर (!dev->parent)
		वापस -EINVAL;

	da9063 = dev_get_drvdata(dev->parent);
	अगर (!da9063)
		वापस -EINVAL;

	wdd = devm_kzalloc(dev, माप(*wdd), GFP_KERNEL);
	अगर (!wdd)
		वापस -ENOMEM;

	wdd->info = &da9063_watchकरोg_info;
	wdd->ops = &da9063_watchकरोg_ops;
	wdd->min_समयout = DA9063_WDT_MIN_TIMEOUT;
	wdd->max_समयout = DA9063_WDT_MAX_TIMEOUT;
	wdd->min_hw_heartbeat_ms = DA9063_RESET_PROTECTION_MS;
	wdd->parent = dev;
	wdd->status = WATCHDOG_NOWAYOUT_INIT_STATUS;

	watchकरोg_set_restart_priority(wdd, 128);
	watchकरोg_set_drvdata(wdd, da9063);

	wdd->समयout = DA9063_WDG_TIMEOUT;

	/* Use pre-configured समयout अगर watchकरोg is alपढ़ोy running. */
	समयout = da9063_wdt_पढ़ो_समयout(da9063);
	अगर (समयout)
		wdd->समयout = समयout;

	/* Set समयout, maybe override it with DT value, scale it */
	watchकरोg_init_समयout(wdd, 0, dev);
	da9063_wdt_set_समयout(wdd, wdd->समयout);

	/* Update समयout अगर the watchकरोg is alपढ़ोy running. */
	अगर (समयout) अणु
		da9063_wdt_update_समयout(da9063, wdd->समयout);
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdd);
पूर्ण

अटल काष्ठा platक्रमm_driver da9063_wdt_driver = अणु
	.probe = da9063_wdt_probe,
	.driver = अणु
		.name = DA9063_DRVNAME_WATCHDOG,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da9063_wdt_driver);

MODULE_AUTHOR("Mariusz Wojtasik <mariusz.wojtasik@diasemi.com>");
MODULE_DESCRIPTION("Watchdog driver for Dialog DA9063");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DA9063_DRVNAME_WATCHDOG);
