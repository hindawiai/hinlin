<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम Aपंचांगel AT91SAM9x processors.
 *
 * Copyright (C) 2008 Renaud CERRATO r.cerrato@til-technologies.fr
 *
 */

/*
 * The Watchकरोg Timer Mode Register can be only written to once. If the
 * समयout need to be set from Linux, be sure that the bootstrap or the
 * bootloader करोesn't ग_लिखो to this रेजिस्टर.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

#समावेश "at91sam9_wdt.h"

#घोषणा DRV_NAME "AT91SAM9 Watchdog"

#घोषणा wdt_पढ़ो(wdt, field) \
	पढ़ोl_relaxed((wdt)->base + (field))
#घोषणा wdt_ग_लिखो(wtd, field, val) \
	ग_लिखोl_relaxed((val), (wdt)->base + (field))

/* AT91SAM9 watchकरोg runs a 12bit counter @ 256Hz,
 * use this to convert a watchकरोg
 * value from/to milliseconds.
 */
#घोषणा ticks_to_hz_roundकरोwn(t)	((((t) + 1) * HZ) >> 8)
#घोषणा ticks_to_hz_roundup(t)		(((((t) + 1) * HZ) + 255) >> 8)
#घोषणा ticks_to_secs(t)		(((t) + 1) >> 8)
#घोषणा secs_to_ticks(s)		((s) ? (((s) << 8) - 1) : 0)

#घोषणा WDT_MR_RESET	0x3FFF2FFF

/* Watchकरोg max counter value in ticks */
#घोषणा WDT_COUNTER_MAX_TICKS	0xFFF

/* Watchकरोg max delta/value in secs */
#घोषणा WDT_COUNTER_MAX_SECS	ticks_to_secs(WDT_COUNTER_MAX_TICKS)

/* Hardware समयout in seconds */
#घोषणा WDT_HW_TIMEOUT 2

/* Timer heartbeat (500ms) */
#घोषणा WDT_TIMEOUT	(HZ/2)

/* User land समयout */
#घोषणा WDT_HEARTBEAT 15
अटल पूर्णांक heartbeat;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeats in seconds. "
	"(default = " __MODULE_STRING(WDT_HEARTBEAT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा to_wdt(wdd) container_of(wdd, काष्ठा at91wdt, wdd)
काष्ठा at91wdt अणु
	काष्ठा watchकरोg_device wdd;
	व्योम __iomem *base;
	अचिन्हित दीर्घ next_heartbeat;	/* the next_heartbeat क्रम the समयr */
	काष्ठा समयr_list समयr;	/* The समयr that pings the watchकरोg */
	u32 mr;
	u32 mr_mask;
	अचिन्हित दीर्घ heartbeat;	/* WDT heartbeat in jअगरfies */
	bool nowayout;
	अचिन्हित पूर्णांक irq;
	काष्ठा clk *sclk;
पूर्ण;

/* ......................................................................... */

अटल irqवापस_t wdt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा at91wdt *wdt = (काष्ठा at91wdt *)dev_id;

	अगर (wdt_पढ़ो(wdt, AT91_WDT_SR)) अणु
		pr_crit("at91sam9 WDT software reset\n");
		emergency_restart();
		pr_crit("Reboot didn't ?????\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Reload the watchकरोg समयr.  (ie, pat the watchकरोg)
 */
अटल अंतरभूत व्योम at91_wdt_reset(काष्ठा at91wdt *wdt)
अणु
	wdt_ग_लिखो(wdt, AT91_WDT_CR, AT91_WDT_KEY | AT91_WDT_WDRSTT);
पूर्ण

/*
 * Timer tick
 */
अटल व्योम at91_ping(काष्ठा समयr_list *t)
अणु
	काष्ठा at91wdt *wdt = from_समयr(wdt, t, समयr);
	अगर (समय_beक्रमe(jअगरfies, wdt->next_heartbeat) ||
	    !watchकरोg_active(&wdt->wdd)) अणु
		at91_wdt_reset(wdt);
		mod_समयr(&wdt->समयr, jअगरfies + wdt->heartbeat);
	पूर्ण अन्यथा अणु
		pr_crit("I will reset your machine !\n");
	पूर्ण
पूर्ण

अटल पूर्णांक at91_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा at91wdt *wdt = to_wdt(wdd);
	/* calculate when the next userspace समयout will be */
	wdt->next_heartbeat = jअगरfies + wdd->समयout * HZ;
	वापस 0;
पूर्ण

अटल पूर्णांक at91_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	/* The watchकरोg समयr hardware can not be stopped... */
	वापस 0;
पूर्ण

अटल पूर्णांक at91_wdt_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक new_समयout)
अणु
	wdd->समयout = new_समयout;
	वापस at91_wdt_start(wdd);
पूर्ण

अटल पूर्णांक at91_wdt_init(काष्ठा platक्रमm_device *pdev, काष्ठा at91wdt *wdt)
अणु
	u32 पंचांगp;
	u32 delta;
	u32 value;
	पूर्णांक err;
	u32 mask = wdt->mr_mask;
	अचिन्हित दीर्घ min_heartbeat = 1;
	अचिन्हित दीर्घ max_heartbeat;
	काष्ठा device *dev = &pdev->dev;

	पंचांगp = wdt_पढ़ो(wdt, AT91_WDT_MR);
	अगर ((पंचांगp & mask) != (wdt->mr & mask)) अणु
		अगर (पंचांगp == WDT_MR_RESET) अणु
			wdt_ग_लिखो(wdt, AT91_WDT_MR, wdt->mr);
			पंचांगp = wdt_पढ़ो(wdt, AT91_WDT_MR);
		पूर्ण
	पूर्ण

	अगर (पंचांगp & AT91_WDT_WDDIS) अणु
		अगर (wdt->mr & AT91_WDT_WDDIS)
			वापस 0;
		dev_err(dev, "watchdog is disabled\n");
		वापस -EINVAL;
	पूर्ण

	value = पंचांगp & AT91_WDT_WDV;
	delta = (पंचांगp & AT91_WDT_WDD) >> 16;

	अगर (delta < value)
		min_heartbeat = ticks_to_hz_roundup(value - delta);

	max_heartbeat = ticks_to_hz_roundकरोwn(value);
	अगर (!max_heartbeat) अणु
		dev_err(dev,
			"heartbeat is too small for the system to handle it correctly\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Try to reset the watchकरोg counter 4 or 2 बार more often than
	 * actually requested, to aव्योम spurious watchकरोg reset.
	 * If this is not possible because of the min_heartbeat value, reset
	 * it at the min_heartbeat period.
	 */
	अगर ((max_heartbeat / 4) >= min_heartbeat)
		wdt->heartbeat = max_heartbeat / 4;
	अन्यथा अगर ((max_heartbeat / 2) >= min_heartbeat)
		wdt->heartbeat = max_heartbeat / 2;
	अन्यथा
		wdt->heartbeat = min_heartbeat;

	अगर (max_heartbeat < min_heartbeat + 4)
		dev_warn(dev,
			 "min heartbeat and max heartbeat might be too close for the system to handle it correctly\n");

	अगर ((पंचांगp & AT91_WDT_WDFIEN) && wdt->irq) अणु
		err = request_irq(wdt->irq, wdt_पूर्णांकerrupt,
				  IRQF_SHARED | IRQF_IRQPOLL |
				  IRQF_NO_SUSPEND,
				  pdev->name, wdt);
		अगर (err)
			वापस err;
	पूर्ण

	अगर ((पंचांगp & wdt->mr_mask) != (wdt->mr & wdt->mr_mask))
		dev_warn(dev,
			 "watchdog already configured differently (mr = %x expecting %x)\n",
			 पंचांगp & wdt->mr_mask, wdt->mr & wdt->mr_mask);

	समयr_setup(&wdt->समयr, at91_ping, 0);

	/*
	 * Use min_heartbeat the first समय to aव्योम spurious watchकरोg reset:
	 * we करोn't know क्रम how दीर्घ the watchकरोg counter is running, and
	 *  - resetting it right now might trigger a watchकरोg fault reset
	 *  - रुकोing क्रम heartbeat समय might lead to a watchकरोg समयout
	 *    reset
	 */
	mod_समयr(&wdt->समयr, jअगरfies + min_heartbeat);

	/* Try to set समयout from device tree first */
	अगर (watchकरोg_init_समयout(&wdt->wdd, 0, dev))
		watchकरोg_init_समयout(&wdt->wdd, heartbeat, dev);
	watchकरोg_set_nowayout(&wdt->wdd, wdt->nowayout);
	err = watchकरोg_रेजिस्टर_device(&wdt->wdd);
	अगर (err)
		जाओ out_stop_समयr;

	wdt->next_heartbeat = jअगरfies + wdt->wdd.समयout * HZ;

	वापस 0;

out_stop_समयr:
	del_समयr(&wdt->समयr);
	वापस err;
पूर्ण

/* ......................................................................... */

अटल स्थिर काष्ठा watchकरोg_info at91_wdt_info = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
						WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops at91_wdt_ops = अणु
	.owner =	THIS_MODULE,
	.start =	at91_wdt_start,
	.stop =		at91_wdt_stop,
	.set_समयout =	at91_wdt_set_समयout,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल पूर्णांक of_at91wdt_init(काष्ठा device_node *np, काष्ठा at91wdt *wdt)
अणु
	u32 min = 0;
	u32 max = WDT_COUNTER_MAX_SECS;
	स्थिर अक्षर *पंचांगp;

	/* Get the पूर्णांकerrupts property */
	wdt->irq = irq_of_parse_and_map(np, 0);
	अगर (!wdt->irq)
		dev_warn(wdt->wdd.parent, "failed to get IRQ from DT\n");

	अगर (!of_property_पढ़ो_u32_index(np, "atmel,max-heartbeat-sec", 0,
					&max)) अणु
		अगर (!max || max > WDT_COUNTER_MAX_SECS)
			max = WDT_COUNTER_MAX_SECS;

		अगर (!of_property_पढ़ो_u32_index(np, "atmel,min-heartbeat-sec",
						0, &min)) अणु
			अगर (min >= max)
				min = max - 1;
		पूर्ण
	पूर्ण

	min = secs_to_ticks(min);
	max = secs_to_ticks(max);

	wdt->mr_mask = 0x3FFFFFFF;
	wdt->mr = 0;
	अगर (!of_property_पढ़ो_string(np, "atmel,watchdog-type", &पंचांगp) &&
	    !म_भेद(पंचांगp, "software")) अणु
		wdt->mr |= AT91_WDT_WDFIEN;
		wdt->mr_mask &= ~AT91_WDT_WDRPROC;
	पूर्ण अन्यथा अणु
		wdt->mr |= AT91_WDT_WDRSTEN;
	पूर्ण

	अगर (!of_property_पढ़ो_string(np, "atmel,reset-type", &पंचांगp) &&
	    !म_भेद(पंचांगp, "proc"))
		wdt->mr |= AT91_WDT_WDRPROC;

	अगर (of_property_पढ़ो_bool(np, "atmel,disable")) अणु
		wdt->mr |= AT91_WDT_WDDIS;
		wdt->mr_mask &= AT91_WDT_WDDIS;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "atmel,idle-halt"))
		wdt->mr |= AT91_WDT_WDIDLEHLT;

	अगर (of_property_पढ़ो_bool(np, "atmel,dbg-halt"))
		wdt->mr |= AT91_WDT_WDDBGHLT;

	wdt->mr |= max | ((max - min) << 16);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक of_at91wdt_init(काष्ठा device_node *np, काष्ठा at91wdt *wdt)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init at91wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा at91wdt *wdt;

	wdt = devm_kzalloc(&pdev->dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->mr = (WDT_HW_TIMEOUT * 256) | AT91_WDT_WDRSTEN | AT91_WDT_WDD |
		  AT91_WDT_WDDBGHLT | AT91_WDT_WDIDLEHLT;
	wdt->mr_mask = 0x3FFFFFFF;
	wdt->nowayout = nowayout;
	wdt->wdd.parent = &pdev->dev;
	wdt->wdd.info = &at91_wdt_info;
	wdt->wdd.ops = &at91_wdt_ops;
	wdt->wdd.समयout = WDT_HEARTBEAT;
	wdt->wdd.min_समयout = 1;
	wdt->wdd.max_समयout = 0xFFFF;

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	wdt->sclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(wdt->sclk))
		वापस PTR_ERR(wdt->sclk);

	err = clk_prepare_enable(wdt->sclk);
	अगर (err) अणु
		dev_err(&pdev->dev, "Could not enable slow clock\n");
		वापस err;
	पूर्ण

	अगर (pdev->dev.of_node) अणु
		err = of_at91wdt_init(pdev->dev.of_node, wdt);
		अगर (err)
			जाओ err_clk;
	पूर्ण

	err = at91_wdt_init(pdev, wdt);
	अगर (err)
		जाओ err_clk;

	platक्रमm_set_drvdata(pdev, wdt);

	pr_info("enabled (heartbeat=%d sec, nowayout=%d)\n",
		wdt->wdd.समयout, wdt->nowayout);

	वापस 0;

err_clk:
	clk_disable_unprepare(wdt->sclk);

	वापस err;
पूर्ण

अटल पूर्णांक __निकास at91wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91wdt *wdt = platक्रमm_get_drvdata(pdev);
	watchकरोg_unरेजिस्टर_device(&wdt->wdd);

	pr_warn("I quit now, hardware will probably reboot!\n");
	del_समयr(&wdt->समयr);
	clk_disable_unprepare(wdt->sclk);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id at91_wdt_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9260-wdt" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, at91_wdt_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver at91wdt_driver = अणु
	.हटाओ		= __निकास_p(at91wdt_हटाओ),
	.driver		= अणु
		.name	= "at91_wdt",
		.of_match_table = of_match_ptr(at91_wdt_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(at91wdt_driver, at91wdt_probe);

MODULE_AUTHOR("Renaud CERRATO <r.cerrato@til-technologies.fr>");
MODULE_DESCRIPTION("Watchdog driver for Atmel AT91SAM9x processors");
MODULE_LICENSE("GPL");
