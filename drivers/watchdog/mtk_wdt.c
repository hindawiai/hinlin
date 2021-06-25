<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mediatek Watchकरोg Driver
 *
 * Copyright (C) 2014 Matthias Brugger
 *
 * Matthias Brugger <matthias.bgg@gmail.com>
 *
 * Based on sunxi_wdt.c
 */

#समावेश <dt-bindings/reset-controller/mt2712-resets.h>
#समावेश <dt-bindings/reset-controller/mt8183-resets.h>
#समावेश <dt-bindings/reset-controller/mt8192-resets.h>
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
#समावेश <linux/reset-controller.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा WDT_MAX_TIMEOUT		31
#घोषणा WDT_MIN_TIMEOUT		1
#घोषणा WDT_LENGTH_TIMEOUT(n)	((n) << 5)

#घोषणा WDT_LENGTH		0x04
#घोषणा WDT_LENGTH_KEY		0x8

#घोषणा WDT_RST			0x08
#घोषणा WDT_RST_RELOAD		0x1971

#घोषणा WDT_MODE		0x00
#घोषणा WDT_MODE_EN		(1 << 0)
#घोषणा WDT_MODE_EXT_POL_LOW	(0 << 1)
#घोषणा WDT_MODE_EXT_POL_HIGH	(1 << 1)
#घोषणा WDT_MODE_EXRST_EN	(1 << 2)
#घोषणा WDT_MODE_IRQ_EN		(1 << 3)
#घोषणा WDT_MODE_AUTO_START	(1 << 4)
#घोषणा WDT_MODE_DUAL_EN	(1 << 6)
#घोषणा WDT_MODE_KEY		0x22000000

#घोषणा WDT_SWRST		0x14
#घोषणा WDT_SWRST_KEY		0x1209

#घोषणा WDT_SWSYSRST		0x18U
#घोषणा WDT_SWSYS_RST_KEY	0x88000000

#घोषणा DRV_NAME		"mtk-wdt"
#घोषणा DRV_VERSION		"1.0"

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक समयout;

काष्ठा mtk_wdt_dev अणु
	काष्ठा watchकरोg_device wdt_dev;
	व्योम __iomem *wdt_base;
	spinlock_t lock; /* protects WDT_SWSYSRST reg */
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

काष्ठा mtk_wdt_data अणु
	पूर्णांक toprgu_sw_rst_num;
पूर्ण;

अटल स्थिर काष्ठा mtk_wdt_data mt2712_data = अणु
	.toprgu_sw_rst_num = MT2712_TOPRGU_SW_RST_NUM,
पूर्ण;

अटल स्थिर काष्ठा mtk_wdt_data mt8183_data = अणु
	.toprgu_sw_rst_num = MT8183_TOPRGU_SW_RST_NUM,
पूर्ण;

अटल स्थिर काष्ठा mtk_wdt_data mt8192_data = अणु
	.toprgu_sw_rst_num = MT8192_TOPRGU_SW_RST_NUM,
पूर्ण;

अटल पूर्णांक toprgu_reset_update(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id, bool निश्चित)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित दीर्घ flags;
	काष्ठा mtk_wdt_dev *data =
		 container_of(rcdev, काष्ठा mtk_wdt_dev, rcdev);

	spin_lock_irqsave(&data->lock, flags);

	पंचांगp = पढ़ोl(data->wdt_base + WDT_SWSYSRST);
	अगर (निश्चित)
		पंचांगp |= BIT(id);
	अन्यथा
		पंचांगp &= ~BIT(id);
	पंचांगp |= WDT_SWSYS_RST_KEY;
	ग_लिखोl(पंचांगp, data->wdt_base + WDT_SWSYSRST);

	spin_unlock_irqrestore(&data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक toprgu_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस toprgu_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक toprgu_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस toprgu_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक toprgu_reset(काष्ठा reset_controller_dev *rcdev,
			अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;

	ret = toprgu_reset_निश्चित(rcdev, id);
	अगर (ret)
		वापस ret;

	वापस toprgu_reset_deनिश्चित(rcdev, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops toprgu_reset_ops = अणु
	.निश्चित = toprgu_reset_निश्चित,
	.deनिश्चित = toprgu_reset_deनिश्चित,
	.reset = toprgu_reset,
पूर्ण;

अटल पूर्णांक toprgu_रेजिस्टर_reset_controller(काष्ठा platक्रमm_device *pdev,
					    पूर्णांक rst_num)
अणु
	पूर्णांक ret;
	काष्ठा mtk_wdt_dev *mtk_wdt = platक्रमm_get_drvdata(pdev);

	spin_lock_init(&mtk_wdt->lock);

	mtk_wdt->rcdev.owner = THIS_MODULE;
	mtk_wdt->rcdev.nr_resets = rst_num;
	mtk_wdt->rcdev.ops = &toprgu_reset_ops;
	mtk_wdt->rcdev.of_node = pdev->dev.of_node;
	ret = devm_reset_controller_रेजिस्टर(&pdev->dev, &mtk_wdt->rcdev);
	अगर (ret != 0)
		dev_err(&pdev->dev,
			"couldn't register wdt reset controller: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base;

	wdt_base = mtk_wdt->wdt_base;

	जबतक (1) अणु
		ग_लिखोl(WDT_SWRST_KEY, wdt_base + WDT_SWRST);
		mdelay(5);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = mtk_wdt->wdt_base;

	ioग_लिखो32(WDT_RST_RELOAD, wdt_base + WDT_RST);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = mtk_wdt->wdt_base;
	u32 reg;

	wdt_dev->समयout = समयout;

	/*
	 * One bit is the value of 512 ticks
	 * The घड़ी has 32 KHz
	 */
	reg = WDT_LENGTH_TIMEOUT(समयout << 6) | WDT_LENGTH_KEY;
	ioग_लिखो32(reg, wdt_base + WDT_LENGTH);

	mtk_wdt_ping(wdt_dev);

	वापस 0;
पूर्ण

अटल व्योम mtk_wdt_init(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base;

	wdt_base = mtk_wdt->wdt_base;

	अगर (पढ़ोl(wdt_base + WDT_MODE) & WDT_MODE_EN) अणु
		set_bit(WDOG_HW_RUNNING, &wdt_dev->status);
		mtk_wdt_set_समयout(wdt_dev, wdt_dev->समयout);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = mtk_wdt->wdt_base;
	u32 reg;

	reg = पढ़ोl(wdt_base + WDT_MODE);
	reg &= ~WDT_MODE_EN;
	reg |= WDT_MODE_KEY;
	ioग_लिखो32(reg, wdt_base + WDT_MODE);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	u32 reg;
	काष्ठा mtk_wdt_dev *mtk_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = mtk_wdt->wdt_base;
	पूर्णांक ret;

	ret = mtk_wdt_set_समयout(wdt_dev, wdt_dev->समयout);
	अगर (ret < 0)
		वापस ret;

	reg = ioपढ़ो32(wdt_base + WDT_MODE);
	reg &= ~(WDT_MODE_IRQ_EN | WDT_MODE_DUAL_EN);
	reg |= (WDT_MODE_EN | WDT_MODE_KEY);
	ioग_लिखो32(reg, wdt_base + WDT_MODE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info mtk_wdt_info = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops mtk_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= mtk_wdt_start,
	.stop		= mtk_wdt_stop,
	.ping		= mtk_wdt_ping,
	.set_समयout	= mtk_wdt_set_समयout,
	.restart	= mtk_wdt_restart,
पूर्ण;

अटल पूर्णांक mtk_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_wdt_dev *mtk_wdt;
	स्थिर काष्ठा mtk_wdt_data *wdt_data;
	पूर्णांक err;

	mtk_wdt = devm_kzalloc(dev, माप(*mtk_wdt), GFP_KERNEL);
	अगर (!mtk_wdt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mtk_wdt);

	mtk_wdt->wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mtk_wdt->wdt_base))
		वापस PTR_ERR(mtk_wdt->wdt_base);

	mtk_wdt->wdt_dev.info = &mtk_wdt_info;
	mtk_wdt->wdt_dev.ops = &mtk_wdt_ops;
	mtk_wdt->wdt_dev.समयout = WDT_MAX_TIMEOUT;
	mtk_wdt->wdt_dev.max_hw_heartbeat_ms = WDT_MAX_TIMEOUT * 1000;
	mtk_wdt->wdt_dev.min_समयout = WDT_MIN_TIMEOUT;
	mtk_wdt->wdt_dev.parent = dev;

	watchकरोg_init_समयout(&mtk_wdt->wdt_dev, समयout, dev);
	watchकरोg_set_nowayout(&mtk_wdt->wdt_dev, nowayout);
	watchकरोg_set_restart_priority(&mtk_wdt->wdt_dev, 128);

	watchकरोg_set_drvdata(&mtk_wdt->wdt_dev, mtk_wdt);

	mtk_wdt_init(&mtk_wdt->wdt_dev);

	watchकरोg_stop_on_reboot(&mtk_wdt->wdt_dev);
	err = devm_watchकरोg_रेजिस्टर_device(dev, &mtk_wdt->wdt_dev);
	अगर (unlikely(err))
		वापस err;

	dev_info(dev, "Watchdog enabled (timeout=%d sec, nowayout=%d)\n",
		 mtk_wdt->wdt_dev.समयout, nowayout);

	wdt_data = of_device_get_match_data(dev);
	अगर (wdt_data) अणु
		err = toprgu_रेजिस्टर_reset_controller(pdev,
						       wdt_data->toprgu_sw_rst_num);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&mtk_wdt->wdt_dev))
		mtk_wdt_stop(&mtk_wdt->wdt_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_wdt_dev *mtk_wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&mtk_wdt->wdt_dev)) अणु
		mtk_wdt_start(&mtk_wdt->wdt_dev);
		mtk_wdt_ping(&mtk_wdt->wdt_dev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id mtk_wdt_dt_ids[] = अणु
	अणु .compatible = "mediatek,mt2712-wdt", .data = &mt2712_data पूर्ण,
	अणु .compatible = "mediatek,mt6589-wdt" पूर्ण,
	अणु .compatible = "mediatek,mt8183-wdt", .data = &mt8183_data पूर्ण,
	अणु .compatible = "mediatek,mt8192-wdt", .data = &mt8192_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_wdt_dt_ids);

अटल स्थिर काष्ठा dev_pm_ops mtk_wdt_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_wdt_suspend,
				mtk_wdt_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_wdt_driver = अणु
	.probe		= mtk_wdt_probe,
	.driver		= अणु
		.name		= DRV_NAME,
		.pm		= &mtk_wdt_pm_ops,
		.of_match_table	= mtk_wdt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_wdt_driver);

module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog heartbeat in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthias Brugger <matthias.bgg@gmail.com>");
MODULE_DESCRIPTION("Mediatek WatchDog Timer Driver");
MODULE_VERSION(DRV_VERSION);
