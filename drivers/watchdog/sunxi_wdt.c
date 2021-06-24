<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      sunxi Watchकरोg Driver
 *
 *      Copyright (c) 2013 Carlo Caione
 *                    2012 Henrik Nordstrom
 *
 *      Based on xen_wdt.c
 *      (c) Copyright 2010 Novell, Inc.
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

#घोषणा WDT_MAX_TIMEOUT         16
#घोषणा WDT_MIN_TIMEOUT         1
#घोषणा WDT_TIMEOUT_MASK        0x0F

#घोषणा WDT_CTRL_RELOAD         ((1 << 0) | (0x0a57 << 1))

#घोषणा WDT_MODE_EN             (1 << 0)

#घोषणा DRV_NAME		"sunxi-wdt"
#घोषणा DRV_VERSION		"1.0"

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक समयout;

/*
 * This काष्ठाure stores the रेजिस्टर offsets क्रम dअगरferent variants
 * of Allwinner's watchकरोg hardware.
 */
काष्ठा sunxi_wdt_reg अणु
	u8 wdt_ctrl;
	u8 wdt_cfg;
	u8 wdt_mode;
	u8 wdt_समयout_shअगरt;
	u8 wdt_reset_mask;
	u8 wdt_reset_val;
पूर्ण;

काष्ठा sunxi_wdt_dev अणु
	काष्ठा watchकरोg_device wdt_dev;
	व्योम __iomem *wdt_base;
	स्थिर काष्ठा sunxi_wdt_reg *wdt_regs;
पूर्ण;

/*
 * wdt_समयout_map maps the watchकरोg समयr पूर्णांकerval value in seconds to
 * the value of the रेजिस्टर WDT_MODE at bits .wdt_समयout_shअगरt ~ +3
 *
 * [समयout seconds] = रेजिस्टर value
 *
 */

अटल स्थिर पूर्णांक wdt_समयout_map[] = अणु
	[1] = 0x1,  /* 1s  */
	[2] = 0x2,  /* 2s  */
	[3] = 0x3,  /* 3s  */
	[4] = 0x4,  /* 4s  */
	[5] = 0x5,  /* 5s  */
	[6] = 0x6,  /* 6s  */
	[8] = 0x7,  /* 8s  */
	[10] = 0x8, /* 10s */
	[12] = 0x9, /* 12s */
	[14] = 0xA, /* 14s */
	[16] = 0xB, /* 16s */
पूर्ण;


अटल पूर्णांक sunxi_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा sunxi_wdt_dev *sunxi_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = sunxi_wdt->wdt_base;
	स्थिर काष्ठा sunxi_wdt_reg *regs = sunxi_wdt->wdt_regs;
	u32 val;

	/* Set प्रणाली reset function */
	val = पढ़ोl(wdt_base + regs->wdt_cfg);
	val &= ~(regs->wdt_reset_mask);
	val |= regs->wdt_reset_val;
	ग_लिखोl(val, wdt_base + regs->wdt_cfg);

	/* Set lowest समयout and enable watchकरोg */
	val = पढ़ोl(wdt_base + regs->wdt_mode);
	val &= ~(WDT_TIMEOUT_MASK << regs->wdt_समयout_shअगरt);
	val |= WDT_MODE_EN;
	ग_लिखोl(val, wdt_base + regs->wdt_mode);

	/*
	 * Restart the watchकरोg. The शेष (and lowest) पूर्णांकerval
	 * value क्रम the watchकरोg is 0.5s.
	 */
	ग_लिखोl(WDT_CTRL_RELOAD, wdt_base + regs->wdt_ctrl);

	जबतक (1) अणु
		mdelay(5);
		val = पढ़ोl(wdt_base + regs->wdt_mode);
		val |= WDT_MODE_EN;
		ग_लिखोl(val, wdt_base + regs->wdt_mode);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा sunxi_wdt_dev *sunxi_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = sunxi_wdt->wdt_base;
	स्थिर काष्ठा sunxi_wdt_reg *regs = sunxi_wdt->wdt_regs;

	ग_लिखोl(WDT_CTRL_RELOAD, wdt_base + regs->wdt_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
		अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sunxi_wdt_dev *sunxi_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = sunxi_wdt->wdt_base;
	स्थिर काष्ठा sunxi_wdt_reg *regs = sunxi_wdt->wdt_regs;
	u32 reg;

	अगर (wdt_समयout_map[समयout] == 0)
		समयout++;

	sunxi_wdt->wdt_dev.समयout = समयout;

	reg = पढ़ोl(wdt_base + regs->wdt_mode);
	reg &= ~(WDT_TIMEOUT_MASK << regs->wdt_समयout_shअगरt);
	reg |= wdt_समयout_map[समयout] << regs->wdt_समयout_shअगरt;
	ग_लिखोl(reg, wdt_base + regs->wdt_mode);

	sunxi_wdt_ping(wdt_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा sunxi_wdt_dev *sunxi_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = sunxi_wdt->wdt_base;
	स्थिर काष्ठा sunxi_wdt_reg *regs = sunxi_wdt->wdt_regs;

	ग_लिखोl(0, wdt_base + regs->wdt_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	u32 reg;
	काष्ठा sunxi_wdt_dev *sunxi_wdt = watchकरोg_get_drvdata(wdt_dev);
	व्योम __iomem *wdt_base = sunxi_wdt->wdt_base;
	स्थिर काष्ठा sunxi_wdt_reg *regs = sunxi_wdt->wdt_regs;
	पूर्णांक ret;

	ret = sunxi_wdt_set_समयout(&sunxi_wdt->wdt_dev,
			sunxi_wdt->wdt_dev.समयout);
	अगर (ret < 0)
		वापस ret;

	/* Set प्रणाली reset function */
	reg = पढ़ोl(wdt_base + regs->wdt_cfg);
	reg &= ~(regs->wdt_reset_mask);
	reg |= regs->wdt_reset_val;
	ग_लिखोl(reg, wdt_base + regs->wdt_cfg);

	/* Enable watchकरोg */
	reg = पढ़ोl(wdt_base + regs->wdt_mode);
	reg |= WDT_MODE_EN;
	ग_लिखोl(reg, wdt_base + regs->wdt_mode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sunxi_wdt_info = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sunxi_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= sunxi_wdt_start,
	.stop		= sunxi_wdt_stop,
	.ping		= sunxi_wdt_ping,
	.set_समयout	= sunxi_wdt_set_समयout,
	.restart	= sunxi_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा sunxi_wdt_reg sun4i_wdt_reg = अणु
	.wdt_ctrl = 0x00,
	.wdt_cfg = 0x04,
	.wdt_mode = 0x04,
	.wdt_समयout_shअगरt = 3,
	.wdt_reset_mask = 0x02,
	.wdt_reset_val = 0x02,
पूर्ण;

अटल स्थिर काष्ठा sunxi_wdt_reg sun6i_wdt_reg = अणु
	.wdt_ctrl = 0x10,
	.wdt_cfg = 0x14,
	.wdt_mode = 0x18,
	.wdt_समयout_shअगरt = 4,
	.wdt_reset_mask = 0x03,
	.wdt_reset_val = 0x01,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_wdt_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-wdt", .data = &sun4i_wdt_reg पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-wdt", .data = &sun6i_wdt_reg पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_wdt_dt_ids);

अटल पूर्णांक sunxi_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sunxi_wdt_dev *sunxi_wdt;
	पूर्णांक err;

	sunxi_wdt = devm_kzalloc(dev, माप(*sunxi_wdt), GFP_KERNEL);
	अगर (!sunxi_wdt)
		वापस -ENOMEM;

	sunxi_wdt->wdt_regs = of_device_get_match_data(dev);
	अगर (!sunxi_wdt->wdt_regs)
		वापस -ENODEV;

	sunxi_wdt->wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sunxi_wdt->wdt_base))
		वापस PTR_ERR(sunxi_wdt->wdt_base);

	sunxi_wdt->wdt_dev.info = &sunxi_wdt_info;
	sunxi_wdt->wdt_dev.ops = &sunxi_wdt_ops;
	sunxi_wdt->wdt_dev.समयout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.max_समयout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.min_समयout = WDT_MIN_TIMEOUT;
	sunxi_wdt->wdt_dev.parent = dev;

	watchकरोg_init_समयout(&sunxi_wdt->wdt_dev, समयout, dev);
	watchकरोg_set_nowayout(&sunxi_wdt->wdt_dev, nowayout);
	watchकरोg_set_restart_priority(&sunxi_wdt->wdt_dev, 128);

	watchकरोg_set_drvdata(&sunxi_wdt->wdt_dev, sunxi_wdt);

	sunxi_wdt_stop(&sunxi_wdt->wdt_dev);

	watchकरोg_stop_on_reboot(&sunxi_wdt->wdt_dev);
	err = devm_watchकरोg_रेजिस्टर_device(dev, &sunxi_wdt->wdt_dev);
	अगर (unlikely(err))
		वापस err;

	dev_info(dev, "Watchdog enabled (timeout=%d sec, nowayout=%d)",
		 sunxi_wdt->wdt_dev.समयout, nowayout);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sunxi_wdt_driver = अणु
	.probe		= sunxi_wdt_probe,
	.driver		= अणु
		.name		= DRV_NAME,
		.of_match_table	= sunxi_wdt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sunxi_wdt_driver);

module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog heartbeat in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
		"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carlo Caione <carlo.caione@gmail.com>");
MODULE_AUTHOR("Henrik Nordstrom <henrik@henriknordstrom.net>");
MODULE_DESCRIPTION("sunxi WatchDog Timer Driver");
MODULE_VERSION(DRV_VERSION);
