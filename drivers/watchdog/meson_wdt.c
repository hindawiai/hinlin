<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      Meson Watchकरोg Driver
 *
 *      Copyright (c) 2014 Carlo Caione
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DRV_NAME		"meson_wdt"

#घोषणा MESON_WDT_TC		0x00
#घोषणा MESON_WDT_DC_RESET	(3 << 24)

#घोषणा MESON_WDT_RESET		0x04

#घोषणा MESON_WDT_TIMEOUT	30
#घोषणा MESON_WDT_MIN_TIMEOUT	1

#घोषणा MESON_SEC_TO_TC(s, c)	((s) * (c))

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक समयout;

काष्ठा meson_wdt_data अणु
	अचिन्हित पूर्णांक enable;
	अचिन्हित पूर्णांक terminal_count_mask;
	अचिन्हित पूर्णांक count_unit;
पूर्ण;

अटल काष्ठा meson_wdt_data meson6_wdt_data = अणु
	.enable			= BIT(22),
	.terminal_count_mask	= 0x3fffff,
	.count_unit		= 100000, /* 10 us */
पूर्ण;

अटल काष्ठा meson_wdt_data meson8b_wdt_data = अणु
	.enable			= BIT(19),
	.terminal_count_mask	= 0xffff,
	.count_unit		= 7812, /* 128 us */
पूर्ण;

काष्ठा meson_wdt_dev अणु
	काष्ठा watchकरोg_device wdt_dev;
	व्योम __iomem *wdt_base;
	स्थिर काष्ठा meson_wdt_data *data;
पूर्ण;

अटल पूर्णांक meson_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा meson_wdt_dev *meson_wdt = watchकरोg_get_drvdata(wdt_dev);
	u32 tc_reboot = MESON_WDT_DC_RESET;

	tc_reboot |= meson_wdt->data->enable;

	जबतक (1) अणु
		ग_लिखोl(tc_reboot, meson_wdt->wdt_base + MESON_WDT_TC);
		mdelay(5);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_wdt_dev *meson_wdt = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(0, meson_wdt->wdt_base + MESON_WDT_RESET);

	वापस 0;
पूर्ण

अटल व्योम meson_wdt_change_समयout(काष्ठा watchकरोg_device *wdt_dev,
				     अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा meson_wdt_dev *meson_wdt = watchकरोg_get_drvdata(wdt_dev);
	u32 reg;

	reg = पढ़ोl(meson_wdt->wdt_base + MESON_WDT_TC);
	reg &= ~meson_wdt->data->terminal_count_mask;
	reg |= MESON_SEC_TO_TC(समयout, meson_wdt->data->count_unit);
	ग_लिखोl(reg, meson_wdt->wdt_base + MESON_WDT_TC);
पूर्ण

अटल पूर्णांक meson_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				 अचिन्हित पूर्णांक समयout)
अणु
	wdt_dev->समयout = समयout;

	meson_wdt_change_समयout(wdt_dev, समयout);
	meson_wdt_ping(wdt_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_wdt_dev *meson_wdt = watchकरोg_get_drvdata(wdt_dev);
	u32 reg;

	reg = पढ़ोl(meson_wdt->wdt_base + MESON_WDT_TC);
	reg &= ~meson_wdt->data->enable;
	ग_लिखोl(reg, meson_wdt->wdt_base + MESON_WDT_TC);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_wdt_dev *meson_wdt = watchकरोg_get_drvdata(wdt_dev);
	u32 reg;

	meson_wdt_change_समयout(wdt_dev, meson_wdt->wdt_dev.समयout);
	meson_wdt_ping(wdt_dev);

	reg = पढ़ोl(meson_wdt->wdt_base + MESON_WDT_TC);
	reg |= meson_wdt->data->enable;
	ग_लिखोl(reg, meson_wdt->wdt_base + MESON_WDT_TC);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info meson_wdt_info = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops meson_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= meson_wdt_start,
	.stop		= meson_wdt_stop,
	.ping		= meson_wdt_ping,
	.set_समयout	= meson_wdt_set_समयout,
	.restart        = meson_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_wdt_dt_ids[] = अणु
	अणु .compatible = "amlogic,meson6-wdt", .data = &meson6_wdt_data पूर्ण,
	अणु .compatible = "amlogic,meson8-wdt", .data = &meson6_wdt_data पूर्ण,
	अणु .compatible = "amlogic,meson8b-wdt", .data = &meson8b_wdt_data पूर्ण,
	अणु .compatible = "amlogic,meson8m2-wdt", .data = &meson8b_wdt_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_wdt_dt_ids);

अटल पूर्णांक meson_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_wdt_dev *meson_wdt;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक err;

	meson_wdt = devm_kzalloc(dev, माप(*meson_wdt), GFP_KERNEL);
	अगर (!meson_wdt)
		वापस -ENOMEM;

	meson_wdt->wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(meson_wdt->wdt_base))
		वापस PTR_ERR(meson_wdt->wdt_base);

	of_id = of_match_device(meson_wdt_dt_ids, dev);
	अगर (!of_id) अणु
		dev_err(dev, "Unable to initialize WDT data\n");
		वापस -ENODEV;
	पूर्ण
	meson_wdt->data = of_id->data;

	meson_wdt->wdt_dev.parent = dev;
	meson_wdt->wdt_dev.info = &meson_wdt_info;
	meson_wdt->wdt_dev.ops = &meson_wdt_ops;
	meson_wdt->wdt_dev.max_समयout =
		meson_wdt->data->terminal_count_mask / meson_wdt->data->count_unit;
	meson_wdt->wdt_dev.min_समयout = MESON_WDT_MIN_TIMEOUT;
	meson_wdt->wdt_dev.समयout = min_t(अचिन्हित पूर्णांक,
					   MESON_WDT_TIMEOUT,
					   meson_wdt->wdt_dev.max_समयout);

	watchकरोg_set_drvdata(&meson_wdt->wdt_dev, meson_wdt);

	watchकरोg_init_समयout(&meson_wdt->wdt_dev, समयout, dev);
	watchकरोg_set_nowayout(&meson_wdt->wdt_dev, nowayout);
	watchकरोg_set_restart_priority(&meson_wdt->wdt_dev, 128);

	meson_wdt_stop(&meson_wdt->wdt_dev);

	watchकरोg_stop_on_reboot(&meson_wdt->wdt_dev);
	err = devm_watchकरोg_रेजिस्टर_device(dev, &meson_wdt->wdt_dev);
	अगर (err)
		वापस err;

	dev_info(dev, "Watchdog enabled (timeout=%d sec, nowayout=%d)",
		 meson_wdt->wdt_dev.समयout, nowayout);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver meson_wdt_driver = अणु
	.probe		= meson_wdt_probe,
	.driver		= अणु
		.name		= DRV_NAME,
		.of_match_table	= meson_wdt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_wdt_driver);

module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog heartbeat in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carlo Caione <carlo@caione.org>");
MODULE_DESCRIPTION("Meson Watchdog Timer Driver");
