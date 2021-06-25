<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim MAX77620 Watchकरोg Driver
 *
 * Copyright (C) 2016 NVIDIA CORPORATION. All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mfd/max77620.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;

काष्ठा max77620_wdt अणु
	काष्ठा device			*dev;
	काष्ठा regmap			*rmap;
	काष्ठा watchकरोg_device		wdt_dev;
पूर्ण;

अटल पूर्णांक max77620_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा max77620_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);

	वापस regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL2,
				  MAX77620_WDTEN, MAX77620_WDTEN);
पूर्ण

अटल पूर्णांक max77620_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा max77620_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);

	वापस regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL2,
				  MAX77620_WDTEN, 0);
पूर्ण

अटल पूर्णांक max77620_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा max77620_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);

	वापस regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL3,
				  MAX77620_WDTC_MASK, 0x1);
पूर्ण

अटल पूर्णांक max77620_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				    अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा max77620_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित पूर्णांक wdt_समयout;
	u8 regval;
	पूर्णांक ret;

	चयन (समयout) अणु
	हाल 0 ... 2:
		regval = MAX77620_TWD_2s;
		wdt_समयout = 2;
		अवरोध;

	हाल 3 ... 16:
		regval = MAX77620_TWD_16s;
		wdt_समयout = 16;
		अवरोध;

	हाल 17 ... 64:
		regval = MAX77620_TWD_64s;
		wdt_समयout = 64;
		अवरोध;

	शेष:
		regval = MAX77620_TWD_128s;
		wdt_समयout = 128;
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL3,
				 MAX77620_WDTC_MASK, 0x1);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL2,
				 MAX77620_TWD_MASK, regval);
	अगर (ret < 0)
		वापस ret;

	wdt_dev->समयout = wdt_समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info max77620_wdt_info = अणु
	.identity = "max77620-watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops max77620_wdt_ops = अणु
	.start		= max77620_wdt_start,
	.stop		= max77620_wdt_stop,
	.ping		= max77620_wdt_ping,
	.set_समयout	= max77620_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक max77620_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा max77620_wdt *wdt;
	काष्ठा watchकरोg_device *wdt_dev;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->dev = dev;
	wdt->rmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!wdt->rmap) अणु
		dev_err(wdt->dev, "Failed to get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	wdt_dev = &wdt->wdt_dev;
	wdt_dev->info = &max77620_wdt_info;
	wdt_dev->ops = &max77620_wdt_ops;
	wdt_dev->min_समयout = 2;
	wdt_dev->max_समयout = 128;
	wdt_dev->max_hw_heartbeat_ms = 128 * 1000;

	platक्रमm_set_drvdata(pdev, wdt);

	/* Enable WD_RST_WK - WDT expire results in a restart */
	ret = regmap_update_bits(wdt->rmap, MAX77620_REG_ONOFFCNFG2,
				 MAX77620_ONOFFCNFG2_WD_RST_WK,
				 MAX77620_ONOFFCNFG2_WD_RST_WK);
	अगर (ret < 0) अणु
		dev_err(wdt->dev, "Failed to set WD_RST_WK: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set WDT clear in OFF and sleep mode */
	ret = regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL2,
				 MAX77620_WDTOFFC | MAX77620_WDTSLPC,
				 MAX77620_WDTOFFC | MAX77620_WDTSLPC);
	अगर (ret < 0) अणु
		dev_err(wdt->dev, "Failed to set WDT OFF mode: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Check अगर WDT running and अगर yes then set flags properly */
	ret = regmap_पढ़ो(wdt->rmap, MAX77620_REG_CNFGGLBL2, &regval);
	अगर (ret < 0) अणु
		dev_err(wdt->dev, "Failed to read WDT CFG register: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (regval & MAX77620_TWD_MASK) अणु
	हाल MAX77620_TWD_2s:
		wdt_dev->समयout = 2;
		अवरोध;
	हाल MAX77620_TWD_16s:
		wdt_dev->समयout = 16;
		अवरोध;
	हाल MAX77620_TWD_64s:
		wdt_dev->समयout = 64;
		अवरोध;
	शेष:
		wdt_dev->समयout = 128;
		अवरोध;
	पूर्ण

	अगर (regval & MAX77620_WDTEN)
		set_bit(WDOG_HW_RUNNING, &wdt_dev->status);

	watchकरोg_set_nowayout(wdt_dev, nowayout);
	watchकरोg_set_drvdata(wdt_dev, wdt);

	watchकरोg_stop_on_unरेजिस्टर(wdt_dev);
	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdt_dev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77620_wdt_devtype[] = अणु
	अणु .name = "max77620-watchdog", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77620_wdt_devtype);

अटल काष्ठा platक्रमm_driver max77620_wdt_driver = अणु
	.driver	= अणु
		.name	= "max77620-watchdog",
	पूर्ण,
	.probe	= max77620_wdt_probe,
	.id_table = max77620_wdt_devtype,
पूर्ण;

module_platक्रमm_driver(max77620_wdt_driver);

MODULE_DESCRIPTION("Max77620 watchdog timer driver");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
