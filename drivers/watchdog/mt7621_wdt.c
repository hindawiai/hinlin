<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ralink MT7621/MT7628 built-in hardware watchकरोg समयr
 *
 * Copyright (C) 2014 John Crispin <john@phrozen.org>
 *
 * This driver was based on: drivers/watchकरोg/rt2880_wdt.c
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

#घोषणा TIMER_REG_TMRSTAT		0x00
#घोषणा TIMER_REG_TMR1LOAD		0x24
#घोषणा TIMER_REG_TMR1CTL		0x20

#घोषणा TMR1CTL_ENABLE			BIT(7)
#घोषणा TMR1CTL_RESTART			BIT(9)
#घोषणा TMR1CTL_PRESCALE_SHIFT		16

अटल व्योम __iomem *mt7621_wdt_base;
अटल काष्ठा reset_control *mt7621_wdt_reset;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अंतरभूत व्योम rt_wdt_w32(अचिन्हित reg, u32 val)
अणु
	ioग_लिखो32(val, mt7621_wdt_base + reg);
पूर्ण

अटल अंतरभूत u32 rt_wdt_r32(अचिन्हित reg)
अणु
	वापस ioपढ़ो32(mt7621_wdt_base + reg);
पूर्ण

अटल पूर्णांक mt7621_wdt_ping(काष्ठा watchकरोg_device *w)
अणु
	rt_wdt_w32(TIMER_REG_TMRSTAT, TMR1CTL_RESTART);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_wdt_set_समयout(काष्ठा watchकरोg_device *w, अचिन्हित पूर्णांक t)
अणु
	w->समयout = t;
	rt_wdt_w32(TIMER_REG_TMR1LOAD, t * 1000);
	mt7621_wdt_ping(w);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_wdt_start(काष्ठा watchकरोg_device *w)
अणु
	u32 t;

	/* set the prescaler to 1ms == 1000us */
	rt_wdt_w32(TIMER_REG_TMR1CTL, 1000 << TMR1CTL_PRESCALE_SHIFT);

	mt7621_wdt_set_समयout(w, w->समयout);

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t |= TMR1CTL_ENABLE;
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_wdt_stop(काष्ठा watchकरोg_device *w)
अणु
	u32 t;

	mt7621_wdt_ping(w);

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t &= ~TMR1CTL_ENABLE;
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_wdt_bootcause(व्योम)
अणु
	अगर (rt_sysc_r32(SYSC_RSTSTAT) & WDT_RST_CAUSE)
		वापस WDIOF_CARDRESET;

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_wdt_is_running(काष्ठा watchकरोg_device *w)
अणु
	वापस !!(rt_wdt_r32(TIMER_REG_TMR1CTL) & TMR1CTL_ENABLE);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info mt7621_wdt_info = अणु
	.identity = "Mediatek Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops mt7621_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = mt7621_wdt_start,
	.stop = mt7621_wdt_stop,
	.ping = mt7621_wdt_ping,
	.set_समयout = mt7621_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device mt7621_wdt_dev = अणु
	.info = &mt7621_wdt_info,
	.ops = &mt7621_wdt_ops,
	.min_समयout = 1,
	.max_समयout = 0xfffful / 1000,
पूर्ण;

अटल पूर्णांक mt7621_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	mt7621_wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mt7621_wdt_base))
		वापस PTR_ERR(mt7621_wdt_base);

	mt7621_wdt_reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (!IS_ERR(mt7621_wdt_reset))
		reset_control_deनिश्चित(mt7621_wdt_reset);

	mt7621_wdt_dev.bootstatus = mt7621_wdt_bootcause();

	watchकरोg_init_समयout(&mt7621_wdt_dev, mt7621_wdt_dev.max_समयout,
			      dev);
	watchकरोg_set_nowayout(&mt7621_wdt_dev, nowayout);
	अगर (mt7621_wdt_is_running(&mt7621_wdt_dev)) अणु
		/*
		 * Make sure to apply समयout from watchकरोg core, taking
		 * the prescaler of this driver here पूर्णांकo account (the
		 * boot loader might be using a dअगरferent prescaler).
		 *
		 * To aव्योम spurious resets because of dअगरferent scaling,
		 * we first disable the watchकरोg, set the new prescaler
		 * and समयout, and then re-enable the watchकरोg.
		 */
		mt7621_wdt_stop(&mt7621_wdt_dev);
		mt7621_wdt_start(&mt7621_wdt_dev);
		set_bit(WDOG_HW_RUNNING, &mt7621_wdt_dev.status);
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &mt7621_wdt_dev);
पूर्ण

अटल व्योम mt7621_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	mt7621_wdt_stop(&mt7621_wdt_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7621_wdt_match[] = अणु
	अणु .compatible = "mediatek,mt7621-wdt" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt7621_wdt_match);

अटल काष्ठा platक्रमm_driver mt7621_wdt_driver = अणु
	.probe		= mt7621_wdt_probe,
	.shutकरोwn	= mt7621_wdt_shutकरोwn,
	.driver		= अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= mt7621_wdt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mt7621_wdt_driver);

MODULE_DESCRIPTION("MediaTek MT762x hardware watchdog driver");
MODULE_AUTHOR("John Crispin <john@phrozen.org");
MODULE_LICENSE("GPL v2");
