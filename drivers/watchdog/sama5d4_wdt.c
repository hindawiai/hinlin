<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Aपंचांगel SAMA5D4 Watchकरोg Timer
 *
 * Copyright (C) 2015-2019 Microchip Technology Inc. and its subsidiaries
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/watchकरोg.h>

#समावेश "at91sam9_wdt.h"

/* minimum and maximum watchकरोg समयout, in seconds */
#घोषणा MIN_WDT_TIMEOUT		1
#घोषणा MAX_WDT_TIMEOUT		16
#घोषणा WDT_DEFAULT_TIMEOUT	MAX_WDT_TIMEOUT

#घोषणा WDT_SEC2TICKS(s)	((s) ? (((s) << 8) - 1) : 0)

काष्ठा sama5d4_wdt अणु
	काष्ठा watchकरोg_device	wdd;
	व्योम __iomem		*reg_base;
	u32			mr;
	u32			ir;
	अचिन्हित दीर्घ		last_ping;
	bool			need_irq;
	bool			sam9x60_support;
पूर्ण;

अटल पूर्णांक wdt_समयout;
अटल bool nowayout = WATCHDOG_NOWAYOUT;

module_param(wdt_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_समयout,
	"Watchdog timeout in seconds. (default = "
	__MODULE_STRING(WDT_DEFAULT_TIMEOUT) ")");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा wdt_enabled (!(wdt->mr & AT91_WDT_WDDIS))

#घोषणा wdt_पढ़ो(wdt, field) \
	पढ़ोl_relaxed((wdt)->reg_base + (field))

/* 4 slow घड़ी periods is 4/32768 = 122.07तगs*/
#घोषणा WDT_DELAY	usecs_to_jअगरfies(123)

अटल व्योम wdt_ग_लिखो(काष्ठा sama5d4_wdt *wdt, u32 field, u32 val)
अणु
	/*
	 * WDT_CR and WDT_MR must not be modअगरied within three slow घड़ी
	 * periods following a restart of the watchकरोg perक्रमmed by a ग_लिखो
	 * access in WDT_CR.
	 */
	जबतक (समय_beक्रमe(jअगरfies, wdt->last_ping + WDT_DELAY))
		usleep_range(30, 125);
	ग_लिखोl_relaxed(val, wdt->reg_base + field);
	wdt->last_ping = jअगरfies;
पूर्ण

अटल व्योम wdt_ग_लिखो_nosleep(काष्ठा sama5d4_wdt *wdt, u32 field, u32 val)
अणु
	अगर (समय_beक्रमe(jअगरfies, wdt->last_ping + WDT_DELAY))
		udelay(123);
	ग_लिखोl_relaxed(val, wdt->reg_base + field);
	wdt->last_ping = jअगरfies;
पूर्ण

अटल पूर्णांक sama5d4_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sama5d4_wdt *wdt = watchकरोg_get_drvdata(wdd);

	अगर (wdt->sam9x60_support) अणु
		ग_लिखोl_relaxed(wdt->ir, wdt->reg_base + AT91_SAM9X60_IER);
		wdt->mr &= ~AT91_SAM9X60_WDDIS;
	पूर्ण अन्यथा अणु
		wdt->mr &= ~AT91_WDT_WDDIS;
	पूर्ण
	wdt_ग_लिखो(wdt, AT91_WDT_MR, wdt->mr);

	वापस 0;
पूर्ण

अटल पूर्णांक sama5d4_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sama5d4_wdt *wdt = watchकरोg_get_drvdata(wdd);

	अगर (wdt->sam9x60_support) अणु
		ग_लिखोl_relaxed(wdt->ir, wdt->reg_base + AT91_SAM9X60_IDR);
		wdt->mr |= AT91_SAM9X60_WDDIS;
	पूर्ण अन्यथा अणु
		wdt->mr |= AT91_WDT_WDDIS;
	पूर्ण
	wdt_ग_लिखो(wdt, AT91_WDT_MR, wdt->mr);

	वापस 0;
पूर्ण

अटल पूर्णांक sama5d4_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sama5d4_wdt *wdt = watchकरोg_get_drvdata(wdd);

	wdt_ग_लिखो(wdt, AT91_WDT_CR, AT91_WDT_KEY | AT91_WDT_WDRSTT);

	वापस 0;
पूर्ण

अटल पूर्णांक sama5d4_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				 अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sama5d4_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u32 value = WDT_SEC2TICKS(समयout);

	अगर (wdt->sam9x60_support) अणु
		wdt_ग_लिखो(wdt, AT91_SAM9X60_WLR,
			  AT91_SAM9X60_SET_COUNTER(value));

		wdd->समयout = समयout;
		वापस 0;
	पूर्ण

	wdt->mr &= ~AT91_WDT_WDV;
	wdt->mr |= AT91_WDT_SET_WDV(value);

	/*
	 * WDDIS has to be 0 when updating WDD/WDV. The datasheet states: When
	 * setting the WDDIS bit, and जबतक it is set, the fields WDV and WDD
	 * must not be modअगरied.
	 * If the watchकरोg is enabled, then the समयout can be updated. Else,
	 * रुको that the user enables it.
	 */
	अगर (wdt_enabled)
		wdt_ग_लिखो(wdt, AT91_WDT_MR, wdt->mr & ~AT91_WDT_WDDIS);

	wdd->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sama5d4_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "Atmel SAMA5D4 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sama5d4_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = sama5d4_wdt_start,
	.stop = sama5d4_wdt_stop,
	.ping = sama5d4_wdt_ping,
	.set_समयout = sama5d4_wdt_set_समयout,
पूर्ण;

अटल irqवापस_t sama5d4_wdt_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sama5d4_wdt *wdt = platक्रमm_get_drvdata(dev_id);
	u32 reg;

	अगर (wdt->sam9x60_support)
		reg = wdt_पढ़ो(wdt, AT91_SAM9X60_ISR);
	अन्यथा
		reg = wdt_पढ़ो(wdt, AT91_WDT_SR);

	अगर (reg) अणु
		pr_crit("Atmel Watchdog Software Reset\n");
		emergency_restart();
		pr_crit("Reboot didn't succeed\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक of_sama5d4_wdt_init(काष्ठा device_node *np, काष्ठा sama5d4_wdt *wdt)
अणु
	स्थिर अक्षर *पंचांगp;

	अगर (wdt->sam9x60_support)
		wdt->mr = AT91_SAM9X60_WDDIS;
	अन्यथा
		wdt->mr = AT91_WDT_WDDIS;

	अगर (!of_property_पढ़ो_string(np, "atmel,watchdog-type", &पंचांगp) &&
	    !म_भेद(पंचांगp, "software"))
		wdt->need_irq = true;

	अगर (of_property_पढ़ो_bool(np, "atmel,idle-halt"))
		wdt->mr |= AT91_WDT_WDIDLEHLT;

	अगर (of_property_पढ़ो_bool(np, "atmel,dbg-halt"))
		wdt->mr |= AT91_WDT_WDDBGHLT;

	वापस 0;
पूर्ण

अटल पूर्णांक sama5d4_wdt_init(काष्ठा sama5d4_wdt *wdt)
अणु
	u32 reg, val;

	val = WDT_SEC2TICKS(WDT_DEFAULT_TIMEOUT);
	/*
	 * When booting and resuming, the bootloader may have changed the
	 * watchकरोg configuration.
	 * If the watchकरोg is alपढ़ोy running, we can safely update it.
	 * Else, we have to disable it properly.
	 */
	अगर (!wdt_enabled) अणु
		reg = wdt_पढ़ो(wdt, AT91_WDT_MR);
		अगर (wdt->sam9x60_support && (!(reg & AT91_SAM9X60_WDDIS)))
			wdt_ग_लिखो_nosleep(wdt, AT91_WDT_MR,
					  reg | AT91_SAM9X60_WDDIS);
		अन्यथा अगर (!wdt->sam9x60_support &&
			 (!(reg & AT91_WDT_WDDIS)))
			wdt_ग_लिखो_nosleep(wdt, AT91_WDT_MR,
					  reg | AT91_WDT_WDDIS);
	पूर्ण

	अगर (wdt->sam9x60_support) अणु
		अगर (wdt->need_irq)
			wdt->ir = AT91_SAM9X60_PERINT;
		अन्यथा
			wdt->mr |= AT91_SAM9X60_PERIODRST;

		wdt_ग_लिखो(wdt, AT91_SAM9X60_IER, wdt->ir);
		wdt_ग_लिखो(wdt, AT91_SAM9X60_WLR, AT91_SAM9X60_SET_COUNTER(val));
	पूर्ण अन्यथा अणु
		wdt->mr |= AT91_WDT_SET_WDD(WDT_SEC2TICKS(MAX_WDT_TIMEOUT));
		wdt->mr |= AT91_WDT_SET_WDV(val);

		अगर (wdt->need_irq)
			wdt->mr |= AT91_WDT_WDFIEN;
		अन्यथा
			wdt->mr |= AT91_WDT_WDRSTEN;
	पूर्ण

	wdt_ग_लिखो_nosleep(wdt, AT91_WDT_MR, wdt->mr);

	वापस 0;
पूर्ण

अटल पूर्णांक sama5d4_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा sama5d4_wdt *wdt;
	व्योम __iomem *regs;
	u32 irq = 0;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdd = &wdt->wdd;
	wdd->समयout = WDT_DEFAULT_TIMEOUT;
	wdd->info = &sama5d4_wdt_info;
	wdd->ops = &sama5d4_wdt_ops;
	wdd->min_समयout = MIN_WDT_TIMEOUT;
	wdd->max_समयout = MAX_WDT_TIMEOUT;
	wdt->last_ping = jअगरfies;
	wdt->sam9x60_support = of_device_is_compatible(dev->of_node,
						       "microchip,sam9x60-wdt");

	watchकरोg_set_drvdata(wdd, wdt);

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	wdt->reg_base = regs;

	ret = of_sama5d4_wdt_init(dev->of_node, wdt);
	अगर (ret)
		वापस ret;

	अगर (wdt->need_irq) अणु
		irq = irq_of_parse_and_map(dev->of_node, 0);
		अगर (!irq) अणु
			dev_warn(dev, "failed to get IRQ from DT\n");
			wdt->need_irq = false;
		पूर्ण
	पूर्ण

	अगर (wdt->need_irq) अणु
		ret = devm_request_irq(dev, irq, sama5d4_wdt_irq_handler,
				       IRQF_SHARED | IRQF_IRQPOLL |
				       IRQF_NO_SUSPEND, pdev->name, pdev);
		अगर (ret) अणु
			dev_err(dev, "cannot register interrupt handler\n");
			वापस ret;
		पूर्ण
	पूर्ण

	watchकरोg_init_समयout(wdd, wdt_समयout, dev);

	ret = sama5d4_wdt_init(wdt);
	अगर (ret)
		वापस ret;

	watchकरोg_set_nowayout(wdd, nowayout);

	watchकरोg_stop_on_unरेजिस्टर(wdd);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdt);

	dev_info(dev, "initialized (timeout = %d sec, nowayout = %d)\n",
		 wdd->समयout, nowayout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sama5d4_wdt_of_match[] = अणु
	अणु
		.compatible = "atmel,sama5d4-wdt",
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-wdt",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sama5d4_wdt_of_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sama5d4_wdt_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा sama5d4_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		sama5d4_wdt_stop(&wdt->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक sama5d4_wdt_resume_early(काष्ठा device *dev)
अणु
	काष्ठा sama5d4_wdt *wdt = dev_get_drvdata(dev);

	/*
	 * FIXME: writing MR also pings the watchकरोg which may not be desired.
	 * This should only be करोne when the रेजिस्टरs are lost on suspend but
	 * there is no way to get this inक्रमmation right now.
	 */
	sama5d4_wdt_init(wdt);

	अगर (watchकरोg_active(&wdt->wdd))
		sama5d4_wdt_start(&wdt->wdd);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sama5d4_wdt_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(sama5d4_wdt_suspend_late,
			sama5d4_wdt_resume_early)
पूर्ण;

अटल काष्ठा platक्रमm_driver sama5d4_wdt_driver = अणु
	.probe		= sama5d4_wdt_probe,
	.driver		= अणु
		.name	= "sama5d4_wdt",
		.pm	= &sama5d4_wdt_pm_ops,
		.of_match_table = sama5d4_wdt_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sama5d4_wdt_driver);

MODULE_AUTHOR("Atmel Corporation");
MODULE_DESCRIPTION("Atmel SAMA5D4 Watchdog Timer driver");
MODULE_LICENSE("GPL v2");
