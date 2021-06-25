<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Watchकरोg driver क्रम Faraday Technology FTWDT010
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Inspired by the out-of-tree drivers from OpenWRT:
 * Copyright (C) 2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>

#घोषणा FTWDT010_WDCOUNTER	0x0
#घोषणा FTWDT010_WDLOAD		0x4
#घोषणा FTWDT010_WDRESTART	0x8
#घोषणा FTWDT010_WDCR		0xC

#घोषणा WDRESTART_MAGIC		0x5AB9

#घोषणा WDCR_CLOCK_5MHZ		BIT(4)
#घोषणा WDCR_WDEXT		BIT(3)
#घोषणा WDCR_WDINTR		BIT(2)
#घोषणा WDCR_SYS_RST		BIT(1)
#घोषणा WDCR_ENABLE		BIT(0)

#घोषणा WDT_CLOCK		5000000		/* 5 MHz */

काष्ठा ftwdt010_wdt अणु
	काष्ठा watchकरोg_device	wdd;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	bool			has_irq;
पूर्ण;

अटल अंतरभूत
काष्ठा ftwdt010_wdt *to_ftwdt010_wdt(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा ftwdt010_wdt, wdd);
पूर्ण

अटल पूर्णांक ftwdt010_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);
	u32 enable;

	ग_लिखोl(wdd->समयout * WDT_CLOCK, gwdt->base + FTWDT010_WDLOAD);
	ग_लिखोl(WDRESTART_MAGIC, gwdt->base + FTWDT010_WDRESTART);
	/* set घड़ी beक्रमe enabling */
	enable = WDCR_CLOCK_5MHZ | WDCR_SYS_RST;
	ग_लिखोl(enable, gwdt->base + FTWDT010_WDCR);
	अगर (gwdt->has_irq)
		enable |= WDCR_WDINTR;
	enable |= WDCR_ENABLE;
	ग_लिखोl(enable, gwdt->base + FTWDT010_WDCR);

	वापस 0;
पूर्ण

अटल पूर्णांक ftwdt010_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);

	ग_लिखोl(0, gwdt->base + FTWDT010_WDCR);

	वापस 0;
पूर्ण

अटल पूर्णांक ftwdt010_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);

	ग_लिखोl(WDRESTART_MAGIC, gwdt->base + FTWDT010_WDRESTART);

	वापस 0;
पूर्ण

अटल पूर्णांक ftwdt010_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	wdd->समयout = समयout;
	अगर (watchकरोg_active(wdd))
		ftwdt010_wdt_start(wdd);

	वापस 0;
पूर्ण

अटल irqवापस_t ftwdt010_wdt_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ftwdt010_wdt *gwdt = data;

	watchकरोg_notअगरy_preसमयout(&gwdt->wdd);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops ftwdt010_wdt_ops = अणु
	.start		= ftwdt010_wdt_start,
	.stop		= ftwdt010_wdt_stop,
	.ping		= ftwdt010_wdt_ping,
	.set_समयout	= ftwdt010_wdt_set_समयout,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info ftwdt010_wdt_info = अणु
	.options	= WDIOF_KEEPALIVEPING
			| WDIOF_MAGICCLOSE
			| WDIOF_SETTIMEOUT,
	.identity	= KBUILD_MODNAME,
पूर्ण;


अटल पूर्णांक ftwdt010_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ftwdt010_wdt *gwdt;
	अचिन्हित पूर्णांक reg;
	पूर्णांक irq;
	पूर्णांक ret;

	gwdt = devm_kzalloc(dev, माप(*gwdt), GFP_KERNEL);
	अगर (!gwdt)
		वापस -ENOMEM;

	gwdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gwdt->base))
		वापस PTR_ERR(gwdt->base);

	gwdt->dev = dev;
	gwdt->wdd.info = &ftwdt010_wdt_info;
	gwdt->wdd.ops = &ftwdt010_wdt_ops;
	gwdt->wdd.min_समयout = 1;
	gwdt->wdd.max_समयout = 0xFFFFFFFF / WDT_CLOCK;
	gwdt->wdd.parent = dev;

	/*
	 * If 'timeout-sec' unspecअगरied in devicetree, assume a 13 second
	 * शेष.
	 */
	gwdt->wdd.समयout = 13U;
	watchकरोg_init_समयout(&gwdt->wdd, 0, dev);

	reg = पढ़ोw(gwdt->base + FTWDT010_WDCR);
	अगर (reg & WDCR_ENABLE) अणु
		/* Watchकरोg was enabled by the bootloader, disable it. */
		reg &= ~WDCR_ENABLE;
		ग_लिखोl(reg, gwdt->base + FTWDT010_WDCR);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq) अणु
		ret = devm_request_irq(dev, irq, ftwdt010_wdt_पूर्णांकerrupt, 0,
				       "watchdog bark", gwdt);
		अगर (ret)
			वापस ret;
		gwdt->has_irq = true;
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &gwdt->wdd);
	अगर (ret)
		वापस ret;

	/* Set up platक्रमm driver data */
	platक्रमm_set_drvdata(pdev, gwdt);
	dev_info(dev, "FTWDT010 watchdog driver enabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ftwdt010_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा ftwdt010_wdt *gwdt = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोw(gwdt->base + FTWDT010_WDCR);
	reg &= ~WDCR_ENABLE;
	ग_लिखोl(reg, gwdt->base + FTWDT010_WDCR);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ftwdt010_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा ftwdt010_wdt *gwdt = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;

	अगर (watchकरोg_active(&gwdt->wdd)) अणु
		reg = पढ़ोw(gwdt->base + FTWDT010_WDCR);
		reg |= WDCR_ENABLE;
		ग_लिखोl(reg, gwdt->base + FTWDT010_WDCR);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ftwdt010_wdt_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ftwdt010_wdt_suspend,
				ftwdt010_wdt_resume)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ftwdt010_wdt_match[] = अणु
	अणु .compatible = "faraday,ftwdt010" पूर्ण,
	अणु .compatible = "cortina,gemini-watchdog" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ftwdt010_wdt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ftwdt010_wdt_driver = अणु
	.probe		= ftwdt010_wdt_probe,
	.driver		= अणु
		.name	= "ftwdt010-wdt",
		.of_match_table = of_match_ptr(ftwdt010_wdt_match),
		.pm = &ftwdt010_wdt_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ftwdt010_wdt_driver);
MODULE_AUTHOR("Linus Walleij");
MODULE_DESCRIPTION("Watchdog driver for Faraday Technology FTWDT010");
MODULE_LICENSE("GPL");
