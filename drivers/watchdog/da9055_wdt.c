<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * System monitoring driver क्रम DA9055 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/delay.h>

#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/reg.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा DA9055_DEF_TIMEOUT	4
#घोषणा DA9055_TWDMIN		256

काष्ठा da9055_wdt_data अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा da9055 *da9055;
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 reg_val;
	पूर्णांक user_समय;  /* In seconds */
पूर्ण da9055_wdt_maps[] = अणु
	अणु 0, 0 पूर्ण,
	अणु 1, 2 पूर्ण,
	अणु 2, 4 पूर्ण,
	अणु 3, 8 पूर्ण,
	अणु 4, 16 पूर्ण,
	अणु 5, 32 पूर्ण,
	अणु 5, 33 पूर्ण,  /* Actual समय  32.768s so included both 32s and 33s */
	अणु 6, 65 पूर्ण,
	अणु 6, 66 पूर्ण,  /* Actual समय 65.536s so include both, 65s and 66s */
	अणु 7, 131 पूर्ण,
पूर्ण;

अटल पूर्णांक da9055_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा da9055_wdt_data *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा da9055 *da9055 = driver_data->da9055;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(da9055_wdt_maps); i++)
		अगर (da9055_wdt_maps[i].user_समय == समयout)
			अवरोध;

	अगर (i == ARRAY_SIZE(da9055_wdt_maps))
		ret = -EINVAL;
	अन्यथा
		ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
					DA9055_TWDSCALE_MASK,
					da9055_wdt_maps[i].reg_val <<
					DA9055_TWDSCALE_SHIFT);
	अगर (ret < 0) अणु
		dev_err(da9055->dev,
			"Failed to update timescale bit, %d\n", ret);
		वापस ret;
	पूर्ण

	wdt_dev->समयout = समयout;

	वापस 0;
पूर्ण

अटल पूर्णांक da9055_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा da9055_wdt_data *driver_data = watchकरोg_get_drvdata(wdt_dev);
	काष्ठा da9055 *da9055 = driver_data->da9055;

	/*
	 * We have a minimum समय क्रम watchकरोg winकरोw called TWDMIN. A ग_लिखो
	 * to the watchकरोg beक्रमe this elapsed समय will cause an error.
	 */
	mdelay(DA9055_TWDMIN);

	/* Reset the watchकरोg समयr */
	वापस da9055_reg_update(da9055, DA9055_REG_CONTROL_E,
				 DA9055_WATCHDOG_MASK, 1);
पूर्ण

अटल पूर्णांक da9055_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	वापस da9055_wdt_set_समयout(wdt_dev, wdt_dev->समयout);
पूर्ण

अटल पूर्णांक da9055_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	वापस da9055_wdt_set_समयout(wdt_dev, 0);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info da9055_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity	= "DA9055 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops da9055_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = da9055_wdt_start,
	.stop = da9055_wdt_stop,
	.ping = da9055_wdt_ping,
	.set_समयout = da9055_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक da9055_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा da9055 *da9055 = dev_get_drvdata(dev->parent);
	काष्ठा da9055_wdt_data *driver_data;
	काष्ठा watchकरोg_device *da9055_wdt;
	पूर्णांक ret;

	driver_data = devm_kzalloc(dev, माप(*driver_data), GFP_KERNEL);
	अगर (!driver_data)
		वापस -ENOMEM;

	driver_data->da9055 = da9055;

	da9055_wdt = &driver_data->wdt;

	da9055_wdt->समयout = DA9055_DEF_TIMEOUT;
	da9055_wdt->info = &da9055_wdt_info;
	da9055_wdt->ops = &da9055_wdt_ops;
	da9055_wdt->parent = dev;
	watchकरोg_set_nowayout(da9055_wdt, nowayout);
	watchकरोg_set_drvdata(da9055_wdt, driver_data);

	ret = da9055_wdt_stop(da9055_wdt);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to stop watchdog, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &driver_data->wdt);
	अगर (ret != 0)
		dev_err(da9055->dev, "watchdog_register_device() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver da9055_wdt_driver = अणु
	.probe = da9055_wdt_probe,
	.driver = अणु
		.name	= "da9055-watchdog",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9055_wdt_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("DA9055 watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9055-watchdog");
