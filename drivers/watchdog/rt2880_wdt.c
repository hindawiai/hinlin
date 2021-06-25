<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ralink RT288x/RT3xxx/MT76xx built-in hardware watchकरोg समयr
 *
 * Copyright (C) 2011 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 *
 * This driver was based on: drivers/watchकरोg/softकरोg.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>

#घोषणा SYSC_RSTSTAT			0x38
#घोषणा WDT_RST_CAUSE			BIT(1)

#घोषणा RALINK_WDT_TIMEOUT		30
#घोषणा RALINK_WDT_PRESCALE		65536

#घोषणा TIMER_REG_TMR1LOAD		0x00
#घोषणा TIMER_REG_TMR1CTL		0x08

#घोषणा TMRSTAT_TMR1RST			BIT(5)

#घोषणा TMR1CTL_ENABLE			BIT(7)
#घोषणा TMR1CTL_MODE_SHIFT		4
#घोषणा TMR1CTL_MODE_MASK		0x3
#घोषणा TMR1CTL_MODE_FREE_RUNNING	0x0
#घोषणा TMR1CTL_MODE_PERIODIC		0x1
#घोषणा TMR1CTL_MODE_TIMEOUT		0x2
#घोषणा TMR1CTL_MODE_WDT		0x3
#घोषणा TMR1CTL_PRESCALE_MASK		0xf
#घोषणा TMR1CTL_PRESCALE_65536		0xf

अटल काष्ठा clk *rt288x_wdt_clk;
अटल अचिन्हित दीर्घ rt288x_wdt_freq;
अटल व्योम __iomem *rt288x_wdt_base;
अटल काष्ठा reset_control *rt288x_wdt_reset;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
		__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अंतरभूत व्योम rt_wdt_w32(अचिन्हित reg, u32 val)
अणु
	ioग_लिखो32(val, rt288x_wdt_base + reg);
पूर्ण

अटल अंतरभूत u32 rt_wdt_r32(अचिन्हित reg)
अणु
	वापस ioपढ़ो32(rt288x_wdt_base + reg);
पूर्ण

अटल पूर्णांक rt288x_wdt_ping(काष्ठा watchकरोg_device *w)
अणु
	rt_wdt_w32(TIMER_REG_TMR1LOAD, w->समयout * rt288x_wdt_freq);

	वापस 0;
पूर्ण

अटल पूर्णांक rt288x_wdt_start(काष्ठा watchकरोg_device *w)
अणु
	u32 t;

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t &= ~(TMR1CTL_MODE_MASK << TMR1CTL_MODE_SHIFT |
		TMR1CTL_PRESCALE_MASK);
	t |= (TMR1CTL_MODE_WDT << TMR1CTL_MODE_SHIFT |
		TMR1CTL_PRESCALE_65536);
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	rt288x_wdt_ping(w);

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t |= TMR1CTL_ENABLE;
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	वापस 0;
पूर्ण

अटल पूर्णांक rt288x_wdt_stop(काष्ठा watchकरोg_device *w)
अणु
	u32 t;

	rt288x_wdt_ping(w);

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t &= ~TMR1CTL_ENABLE;
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	वापस 0;
पूर्ण

अटल पूर्णांक rt288x_wdt_set_समयout(काष्ठा watchकरोg_device *w, अचिन्हित पूर्णांक t)
अणु
	w->समयout = t;
	rt288x_wdt_ping(w);

	वापस 0;
पूर्ण

अटल पूर्णांक rt288x_wdt_bootcause(व्योम)
अणु
	अगर (rt_sysc_r32(SYSC_RSTSTAT) & WDT_RST_CAUSE)
		वापस WDIOF_CARDRESET;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info rt288x_wdt_info = अणु
	.identity = "Ralink Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops rt288x_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = rt288x_wdt_start,
	.stop = rt288x_wdt_stop,
	.ping = rt288x_wdt_ping,
	.set_समयout = rt288x_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device rt288x_wdt_dev = अणु
	.info = &rt288x_wdt_info,
	.ops = &rt288x_wdt_ops,
	.min_समयout = 1,
पूर्ण;

अटल पूर्णांक rt288x_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	rt288x_wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rt288x_wdt_base))
		वापस PTR_ERR(rt288x_wdt_base);

	rt288x_wdt_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(rt288x_wdt_clk))
		वापस PTR_ERR(rt288x_wdt_clk);

	rt288x_wdt_reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (!IS_ERR(rt288x_wdt_reset))
		reset_control_deनिश्चित(rt288x_wdt_reset);

	rt288x_wdt_freq = clk_get_rate(rt288x_wdt_clk) / RALINK_WDT_PRESCALE;

	rt288x_wdt_dev.bootstatus = rt288x_wdt_bootcause();
	rt288x_wdt_dev.max_समयout = (0xfffful / rt288x_wdt_freq);
	rt288x_wdt_dev.parent = dev;

	watchकरोg_init_समयout(&rt288x_wdt_dev, rt288x_wdt_dev.max_समयout,
			      dev);
	watchकरोg_set_nowayout(&rt288x_wdt_dev, nowayout);

	watchकरोg_stop_on_reboot(&rt288x_wdt_dev);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, &rt288x_wdt_dev);
	अगर (!ret)
		dev_info(dev, "Initialized\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rt288x_wdt_match[] = अणु
	अणु .compatible = "ralink,rt2880-wdt" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt288x_wdt_match);

अटल काष्ठा platक्रमm_driver rt288x_wdt_driver = अणु
	.probe		= rt288x_wdt_probe,
	.driver		= अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= rt288x_wdt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rt288x_wdt_driver);

MODULE_DESCRIPTION("MediaTek/Ralink RT288x/RT3xxx hardware watchdog driver");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org");
MODULE_LICENSE("GPL v2");
