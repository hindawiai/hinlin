<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/अक्षर/watchकरोg/pnx4008_wdt.c
 *
 * Watchकरोg driver क्रम PNX4008 board
 *
 * Authors: Dmitry Chigirev <source@mvista.com>,
 *	    Vitaly Wool <vitalywool@gmail.com>
 * Based on sa1100 driver,
 * Copyright (C) 2000 Oleg Drokin <green@crimea.edu>
 *
 * 2005-2006 (c) MontaVista Software, Inc.
 *
 * (C) 2012 Wolfram Sang, Pengutronix
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>

/* WatchDog Timer - Chapter 23 Page 207 */

#घोषणा DEFAULT_HEARTBEAT 19
#घोषणा MAX_HEARTBEAT     60

/* Watchकरोg समयr रेजिस्टर set definition */
#घोषणा WDTIM_INT(p)     ((p) + 0x0)
#घोषणा WDTIM_CTRL(p)    ((p) + 0x4)
#घोषणा WDTIM_COUNTER(p) ((p) + 0x8)
#घोषणा WDTIM_MCTRL(p)   ((p) + 0xC)
#घोषणा WDTIM_MATCH0(p)  ((p) + 0x10)
#घोषणा WDTIM_EMR(p)     ((p) + 0x14)
#घोषणा WDTIM_PULSE(p)   ((p) + 0x18)
#घोषणा WDTIM_RES(p)     ((p) + 0x1C)

/* WDTIM_INT bit definitions */
#घोषणा MATCH_INT      1

/* WDTIM_CTRL bit definitions */
#घोषणा COUNT_ENAB     1
#घोषणा RESET_COUNT    (1 << 1)
#घोषणा DEBUG_EN       (1 << 2)

/* WDTIM_MCTRL bit definitions */
#घोषणा MR0_INT        1
#अघोषित  RESET_COUNT0
#घोषणा RESET_COUNT0   (1 << 2)
#घोषणा STOP_COUNT0    (1 << 2)
#घोषणा M_RES1         (1 << 3)
#घोषणा M_RES2         (1 << 4)
#घोषणा RESFRC1        (1 << 5)
#घोषणा RESFRC2        (1 << 6)

/* WDTIM_EMR bit definitions */
#घोषणा EXT_MATCH0      1
#घोषणा MATCH_OUTPUT_HIGH (2 << 4)	/*a MATCH_CTRL setting */

/* WDTIM_RES bit definitions */
#घोषणा WDOG_RESET      1	/* पढ़ो only */

#घोषणा WDOG_COUNTER_RATE 13000000	/*the counter घड़ी is 13 MHz fixed */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक heartbeat;

अटल DEFINE_SPINLOCK(io_lock);
अटल व्योम __iomem	*wdt_base;
अटल काष्ठा clk	*wdt_clk;

अटल पूर्णांक pnx4008_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	spin_lock(&io_lock);

	/* stop counter, initiate counter reset */
	ग_लिखोl(RESET_COUNT, WDTIM_CTRL(wdt_base));
	/*रुको क्रम reset to complete. 100% guarantee event */
	जबतक (पढ़ोl(WDTIM_COUNTER(wdt_base)))
		cpu_relax();
	/* पूर्णांकernal and बाह्यal reset, stop after that */
	ग_लिखोl(M_RES2 | STOP_COUNT0 | RESET_COUNT0, WDTIM_MCTRL(wdt_base));
	/* configure match output */
	ग_लिखोl(MATCH_OUTPUT_HIGH, WDTIM_EMR(wdt_base));
	/* clear पूर्णांकerrupt, just in हाल */
	ग_लिखोl(MATCH_INT, WDTIM_INT(wdt_base));
	/* the दीर्घest pulse period 65541/(13*10^6) seconds ~ 5 ms. */
	ग_लिखोl(0xFFFF, WDTIM_PULSE(wdt_base));
	ग_लिखोl(wdd->समयout * WDOG_COUNTER_RATE, WDTIM_MATCH0(wdt_base));
	/*enable counter, stop when debugger active */
	ग_लिखोl(COUNT_ENAB | DEBUG_EN, WDTIM_CTRL(wdt_base));

	spin_unlock(&io_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pnx4008_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	spin_lock(&io_lock);

	ग_लिखोl(0, WDTIM_CTRL(wdt_base));	/*stop counter */

	spin_unlock(&io_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pnx4008_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				    अचिन्हित पूर्णांक new_समयout)
अणु
	wdd->समयout = new_समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक pnx4008_restart_handler(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	स्थिर अक्षर *boot_cmd = cmd;

	/*
	 * Verअगरy अगर a "cmd" passed from the userspace program rebooting
	 * the प्रणाली; अगर available, handle it.
	 * - For details, see the 'reboot' syscall in kernel/reboot.c
	 * - If the received "cmd" is not supported, use the शेष mode.
	 */
	अगर (boot_cmd) अणु
		अगर (boot_cmd[0] == 'h')
			mode = REBOOT_HARD;
		अन्यथा अगर (boot_cmd[0] == 's')
			mode = REBOOT_SOFT;
	पूर्ण

	अगर (mode == REBOOT_SOFT) अणु
		/* Force match output active */
		ग_लिखोl(EXT_MATCH0, WDTIM_EMR(wdt_base));
		/* Internal reset on match output (RESOUT_N not निश्चितed) */
		ग_लिखोl(M_RES1, WDTIM_MCTRL(wdt_base));
	पूर्ण अन्यथा अणु
		/* Instant निश्चित of RESETOUT_N with pulse length 1mS */
		ग_लिखोl(13000, WDTIM_PULSE(wdt_base));
		ग_लिखोl(M_RES2 | RESFRC1 | RESFRC2, WDTIM_MCTRL(wdt_base));
	पूर्ण

	/* Wait क्रम watchकरोg to reset प्रणाली */
	mdelay(1000);

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info pnx4008_wdt_ident = अणु
	.options = WDIOF_CARDRESET | WDIOF_MAGICCLOSE |
	    WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = "PNX4008 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops pnx4008_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = pnx4008_wdt_start,
	.stop = pnx4008_wdt_stop,
	.set_समयout = pnx4008_wdt_set_समयout,
	.restart = pnx4008_restart_handler,
पूर्ण;

अटल काष्ठा watchकरोg_device pnx4008_wdd = अणु
	.info = &pnx4008_wdt_ident,
	.ops = &pnx4008_wdt_ops,
	.समयout = DEFAULT_HEARTBEAT,
	.min_समयout = 1,
	.max_समयout = MAX_HEARTBEAT,
पूर्ण;

अटल व्योम pnx4008_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक pnx4008_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret = 0;

	watchकरोg_init_समयout(&pnx4008_wdd, heartbeat, dev);

	wdt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt_base))
		वापस PTR_ERR(wdt_base);

	wdt_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(wdt_clk))
		वापस PTR_ERR(wdt_clk);

	ret = clk_prepare_enable(wdt_clk);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(dev, pnx4008_clk_disable_unprepare,
				       wdt_clk);
	अगर (ret)
		वापस ret;

	pnx4008_wdd.bootstatus = (पढ़ोl(WDTIM_RES(wdt_base)) & WDOG_RESET) ?
			WDIOF_CARDRESET : 0;
	pnx4008_wdd.parent = dev;
	watchकरोg_set_nowayout(&pnx4008_wdd, nowayout);
	watchकरोg_set_restart_priority(&pnx4008_wdd, 128);

	अगर (पढ़ोl(WDTIM_CTRL(wdt_base)) & COUNT_ENAB)
		set_bit(WDOG_HW_RUNNING, &pnx4008_wdd.status);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &pnx4008_wdd);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "heartbeat %d sec\n", pnx4008_wdd.समयout);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pnx4008_wdt_match[] = अणु
	अणु .compatible = "nxp,pnx4008-wdt" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pnx4008_wdt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver platक्रमm_wdt_driver = अणु
	.driver = अणु
		.name = "pnx4008-watchdog",
		.of_match_table = of_match_ptr(pnx4008_wdt_match),
	पूर्ण,
	.probe = pnx4008_wdt_probe,
पूर्ण;

module_platक्रमm_driver(platक्रमm_wdt_driver);

MODULE_AUTHOR("MontaVista Software, Inc. <source@mvista.com>");
MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
MODULE_DESCRIPTION("PNX4008 Watchdog Driver");

module_param(heartbeat, uपूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
		 "Watchdog heartbeat period in seconds from 1 to "
		 __MODULE_STRING(MAX_HEARTBEAT) ", default "
		 __MODULE_STRING(DEFAULT_HEARTBEAT));

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Set to 1 to keep watchdog running after device release");

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pnx4008-watchdog");
