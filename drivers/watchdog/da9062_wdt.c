<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg device driver क्रम DA9062 and DA9061 PMICs
 * Copyright (C) 2015  Dialog Semiconductor Ltd.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>
#समावेश <linux/mfd/da9062/core.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>

अटल स्थिर अचिन्हित पूर्णांक wdt_समयout[] = अणु 0, 2, 4, 8, 16, 32, 65, 131 पूर्ण;
#घोषणा DA9062_TWDSCALE_DISABLE		0
#घोषणा DA9062_TWDSCALE_MIN		1
#घोषणा DA9062_TWDSCALE_MAX		(ARRAY_SIZE(wdt_समयout) - 1)
#घोषणा DA9062_WDT_MIN_TIMEOUT		wdt_समयout[DA9062_TWDSCALE_MIN]
#घोषणा DA9062_WDT_MAX_TIMEOUT		wdt_समयout[DA9062_TWDSCALE_MAX]
#घोषणा DA9062_WDG_DEFAULT_TIMEOUT	wdt_समयout[DA9062_TWDSCALE_MAX-1]
#घोषणा DA9062_RESET_PROTECTION_MS	300

काष्ठा da9062_watchकरोg अणु
	काष्ठा da9062 *hw;
	काष्ठा watchकरोg_device wdtdev;
	bool use_sw_pm;
पूर्ण;

अटल अचिन्हित पूर्णांक da9062_wdt_पढ़ो_समयout(काष्ठा da9062_watchकरोg *wdt)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(wdt->hw->regmap, DA9062AA_CONTROL_D, &val);

	वापस wdt_समयout[val & DA9062AA_TWDSCALE_MASK];
पूर्ण

अटल अचिन्हित पूर्णांक da9062_wdt_समयout_to_sel(अचिन्हित पूर्णांक secs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = DA9062_TWDSCALE_MIN; i <= DA9062_TWDSCALE_MAX; i++) अणु
		अगर (wdt_समयout[i] >= secs)
			वापस i;
	पूर्ण

	वापस DA9062_TWDSCALE_MAX;
पूर्ण

अटल पूर्णांक da9062_reset_watchकरोg_समयr(काष्ठा da9062_watchकरोg *wdt)
अणु
	वापस regmap_update_bits(wdt->hw->regmap, DA9062AA_CONTROL_F,
				  DA9062AA_WATCHDOG_MASK,
				  DA9062AA_WATCHDOG_MASK);
पूर्ण

अटल पूर्णांक da9062_wdt_update_समयout_रेजिस्टर(काष्ठा da9062_watchकरोg *wdt,
					      अचिन्हित पूर्णांक regval)
अणु
	काष्ठा da9062 *chip = wdt->hw;

	regmap_update_bits(chip->regmap,
				  DA9062AA_CONTROL_D,
				  DA9062AA_TWDSCALE_MASK,
				  DA9062_TWDSCALE_DISABLE);

	usleep_range(150, 300);

	वापस regmap_update_bits(chip->regmap,
				  DA9062AA_CONTROL_D,
				  DA9062AA_TWDSCALE_MASK,
				  regval);
पूर्ण

अटल पूर्णांक da9062_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);
	अचिन्हित पूर्णांक selector;
	पूर्णांक ret;

	selector = da9062_wdt_समयout_to_sel(wdt->wdtdev.समयout);
	ret = da9062_wdt_update_समयout_रेजिस्टर(wdt, selector);
	अगर (ret)
		dev_err(wdt->hw->dev, "Watchdog failed to start (err = %d)\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = regmap_update_bits(wdt->hw->regmap,
				 DA9062AA_CONTROL_D,
				 DA9062AA_TWDSCALE_MASK,
				 DA9062_TWDSCALE_DISABLE);
	अगर (ret)
		dev_err(wdt->hw->dev, "Watchdog failed to stop (err = %d)\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	ret = da9062_reset_watchकरोg_समयr(wdt);
	अगर (ret)
		dev_err(wdt->hw->dev, "Failed to ping the watchdog (err = %d)\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);
	अचिन्हित पूर्णांक selector;
	पूर्णांक ret;

	selector = da9062_wdt_समयout_to_sel(समयout);
	ret = da9062_wdt_update_समयout_रेजिस्टर(wdt, selector);
	अगर (ret)
		dev_err(wdt->hw->dev, "Failed to set watchdog timeout (err = %d)\n",
			ret);
	अन्यथा
		wdd->समयout = wdt_समयout[selector];

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_wdt_restart(काष्ठा watchकरोg_device *wdd, अचिन्हित दीर्घ action,
			      व्योम *data)
अणु
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);
	काष्ठा i2c_client *client = to_i2c_client(wdt->hw->dev);
	पूर्णांक ret;

	/* Don't use regmap because it is not atomic safe */
	ret = i2c_smbus_ग_लिखो_byte_data(client, DA9062AA_CONTROL_F,
					DA9062AA_SHUTDOWN_MASK);
	अगर (ret < 0)
		dev_alert(wdt->hw->dev, "Failed to shutdown (err = %d)\n",
			  ret);

	/* रुको क्रम reset to निश्चित... */
	mdelay(500);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info da9062_watchकरोg_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = "DA9062 WDT",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops da9062_watchकरोg_ops = अणु
	.owner = THIS_MODULE,
	.start = da9062_wdt_start,
	.stop = da9062_wdt_stop,
	.ping = da9062_wdt_ping,
	.set_समयout = da9062_wdt_set_समयout,
	.restart = da9062_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा of_device_id da9062_compatible_id_table[] = अणु
	अणु .compatible = "dlg,da9062-watchdog", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, da9062_compatible_id_table);

अटल पूर्णांक da9062_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक समयout;
	काष्ठा da9062 *chip;
	काष्ठा da9062_watchकरोg *wdt;

	chip = dev_get_drvdata(dev->parent);
	अगर (!chip)
		वापस -EINVAL;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->use_sw_pm = device_property_present(dev, "dlg,use-sw-pm");

	wdt->hw = chip;

	wdt->wdtdev.info = &da9062_watchकरोg_info;
	wdt->wdtdev.ops = &da9062_watchकरोg_ops;
	wdt->wdtdev.min_समयout = DA9062_WDT_MIN_TIMEOUT;
	wdt->wdtdev.max_समयout = DA9062_WDT_MAX_TIMEOUT;
	wdt->wdtdev.min_hw_heartbeat_ms = DA9062_RESET_PROTECTION_MS;
	wdt->wdtdev.समयout = DA9062_WDG_DEFAULT_TIMEOUT;
	wdt->wdtdev.status = WATCHDOG_NOWAYOUT_INIT_STATUS;
	wdt->wdtdev.parent = dev;

	watchकरोg_set_restart_priority(&wdt->wdtdev, 128);

	watchकरोg_set_drvdata(&wdt->wdtdev, wdt);
	dev_set_drvdata(dev, &wdt->wdtdev);

	समयout = da9062_wdt_पढ़ो_समयout(wdt);
	अगर (समयout)
		wdt->wdtdev.समयout = समयout;

	/* Set समयout from DT value अगर available */
	watchकरोg_init_समयout(&wdt->wdtdev, 0, dev);

	अगर (समयout) अणु
		da9062_wdt_set_समयout(&wdt->wdtdev, wdt->wdtdev.समयout);
		set_bit(WDOG_HW_RUNNING, &wdt->wdtdev.status);
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdtdev);
पूर्ण

अटल पूर्णांक __maybe_unused da9062_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);

	अगर (!wdt->use_sw_pm)
		वापस 0;

	अगर (watchकरोg_active(wdd))
		वापस da9062_wdt_stop(wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused da9062_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	काष्ठा da9062_watchकरोg *wdt = watchकरोg_get_drvdata(wdd);

	अगर (!wdt->use_sw_pm)
		वापस 0;

	अगर (watchकरोg_active(wdd))
		वापस da9062_wdt_start(wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(da9062_wdt_pm_ops,
			 da9062_wdt_suspend, da9062_wdt_resume);

अटल काष्ठा platक्रमm_driver da9062_wdt_driver = अणु
	.probe = da9062_wdt_probe,
	.driver = अणु
		.name = "da9062-watchdog",
		.pm = &da9062_wdt_pm_ops,
		.of_match_table = da9062_compatible_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da9062_wdt_driver);

MODULE_AUTHOR("S Twiss <stwiss.opensource@diasemi.com>");
MODULE_DESCRIPTION("WDT device driver for Dialog DA9062 and DA9061");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9062-watchdog");
