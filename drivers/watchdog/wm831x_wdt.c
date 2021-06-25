<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम the wm831x PMICs
 *
 * Copyright (C) 2009 Wolfson Microelectronics
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/watchकरोg.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा wm831x_wdt_drvdata अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा wm831x *wm831x;
	काष्ठा mutex lock;
	पूर्णांक update_state;
पूर्ण;

/* We can't use the sub-second values here but they're included
 * क्रम completeness.  */
अटल काष्ठा अणु
	अचिन्हित पूर्णांक समय;  /* Seconds */
	u16 val;            /* WDOG_TO value */
पूर्ण wm831x_wdt_cfgs[] = अणु
	अणु  1, 2 पूर्ण,
	अणु  2, 3 पूर्ण,
	अणु  4, 4 पूर्ण,
	अणु  8, 5 पूर्ण,
	अणु 16, 6 पूर्ण,
	अणु 32, 7 पूर्ण,
	अणु 33, 7 पूर्ण,  /* Actually 32.768s so include both, others round करोwn */
पूर्ण;

अटल पूर्णांक wm831x_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा wm831x_wdt_drvdata *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा wm831x *wm831x = driver_data->wm831x;
	पूर्णांक ret;

	mutex_lock(&driver_data->lock);

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret == 0) अणु
		ret = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_ENA, WM831X_WDOG_ENA);
		wm831x_reg_lock(wm831x);
	पूर्ण अन्यथा अणु
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	पूर्ण

	mutex_unlock(&driver_data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm831x_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा wm831x_wdt_drvdata *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा wm831x *wm831x = driver_data->wm831x;
	पूर्णांक ret;

	mutex_lock(&driver_data->lock);

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret == 0) अणु
		ret = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_ENA, 0);
		wm831x_reg_lock(wm831x);
	पूर्ण अन्यथा अणु
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	पूर्ण

	mutex_unlock(&driver_data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm831x_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा wm831x_wdt_drvdata *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा wm831x *wm831x = driver_data->wm831x;
	पूर्णांक ret;
	u16 reg;

	mutex_lock(&driver_data->lock);

	reg = wm831x_reg_पढ़ो(wm831x, WM831X_WATCHDOG);

	अगर (!(reg & WM831X_WDOG_RST_SRC)) अणु
		dev_err(wm831x->dev, "Hardware watchdog update unsupported\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	reg |= WM831X_WDOG_RESET;

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret == 0) अणु
		ret = wm831x_reg_ग_लिखो(wm831x, WM831X_WATCHDOG, reg);
		wm831x_reg_lock(wm831x);
	पूर्ण अन्यथा अणु
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	पूर्ण

out:
	mutex_unlock(&driver_data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक wm831x_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा wm831x_wdt_drvdata *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा wm831x *wm831x = driver_data->wm831x;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(wm831x_wdt_cfgs); i++)
		अगर (wm831x_wdt_cfgs[i].समय == समयout)
			अवरोध;
	अगर (i == ARRAY_SIZE(wm831x_wdt_cfgs))
		वापस -EINVAL;

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret == 0) अणु
		ret = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_TO_MASK,
				      wm831x_wdt_cfgs[i].val);
		wm831x_reg_lock(wm831x);
	पूर्ण अन्यथा अणु
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	पूर्ण

	wdt_dev->समयout = समयout;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info wm831x_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "WM831x Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wm831x_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wm831x_wdt_start,
	.stop = wm831x_wdt_stop,
	.ping = wm831x_wdt_ping,
	.set_समयout = wm831x_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक wm831x_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev->parent);
	काष्ठा wm831x_pdata *chip_pdata = dev_get_platdata(dev->parent);
	काष्ठा wm831x_watchकरोg_pdata *pdata;
	काष्ठा wm831x_wdt_drvdata *driver_data;
	काष्ठा watchकरोg_device *wm831x_wdt;
	पूर्णांक reg, ret, i;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_WATCHDOG);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Failed to read watchdog status: %d\n",
			ret);
		वापस ret;
	पूर्ण
	reg = ret;

	अगर (reg & WM831X_WDOG_DEBUG)
		dev_warn(wm831x->dev, "Watchdog is paused\n");

	driver_data = devm_kzalloc(dev, माप(*driver_data), GFP_KERNEL);
	अगर (!driver_data)
		वापस -ENOMEM;

	mutex_init(&driver_data->lock);
	driver_data->wm831x = wm831x;

	wm831x_wdt = &driver_data->wdt;

	wm831x_wdt->info = &wm831x_wdt_info;
	wm831x_wdt->ops = &wm831x_wdt_ops;
	wm831x_wdt->parent = dev;
	watchकरोg_set_nowayout(wm831x_wdt, nowayout);
	watchकरोg_set_drvdata(wm831x_wdt, driver_data);

	reg = wm831x_reg_पढ़ो(wm831x, WM831X_WATCHDOG);
	reg &= WM831X_WDOG_TO_MASK;
	क्रम (i = 0; i < ARRAY_SIZE(wm831x_wdt_cfgs); i++)
		अगर (wm831x_wdt_cfgs[i].val == reg)
			अवरोध;
	अगर (i == ARRAY_SIZE(wm831x_wdt_cfgs))
		dev_warn(wm831x->dev,
			 "Unknown watchdog timeout: %x\n", reg);
	अन्यथा
		wm831x_wdt->समयout = wm831x_wdt_cfgs[i].समय;

	/* Apply any configuration */
	अगर (chip_pdata)
		pdata = chip_pdata->watchकरोg;
	अन्यथा
		pdata = शून्य;

	अगर (pdata) अणु
		reg &= ~(WM831X_WDOG_SECACT_MASK | WM831X_WDOG_PRIMACT_MASK |
			 WM831X_WDOG_RST_SRC);

		reg |= pdata->primary << WM831X_WDOG_PRIMACT_SHIFT;
		reg |= pdata->secondary << WM831X_WDOG_SECACT_SHIFT;
		reg |= pdata->software << WM831X_WDOG_RST_SRC_SHIFT;

		ret = wm831x_reg_unlock(wm831x);
		अगर (ret == 0) अणु
			ret = wm831x_reg_ग_लिखो(wm831x, WM831X_WATCHDOG, reg);
			wm831x_reg_lock(wm831x);
		पूर्ण अन्यथा अणु
			dev_err(wm831x->dev,
				"Failed to unlock security key: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &driver_data->wdt);
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_wdt_driver = अणु
	.probe = wm831x_wdt_probe,
	.driver = अणु
		.name = "wm831x-watchdog",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm831x_wdt_driver);

MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("WM831x Watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-watchdog");
