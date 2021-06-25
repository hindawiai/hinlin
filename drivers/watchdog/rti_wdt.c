<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg driver क्रम the K3 RTI module
 *
 * (c) Copyright 2019-2020 Texas Instruments Inc.
 * All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DEFAULT_HEARTBEAT 60

/* Max heartbeat is calculated at 32kHz source घड़ी */
#घोषणा MAX_HEARTBEAT	1000

/* Timer रेजिस्टर set definition */
#घोषणा RTIDWDCTRL	0x90
#घोषणा RTIDWDPRLD	0x94
#घोषणा RTIWDSTATUS	0x98
#घोषणा RTIWDKEY	0x9c
#घोषणा RTIDWDCNTR	0xa0
#घोषणा RTIWWDRXCTRL	0xa4
#घोषणा RTIWWDSIZECTRL	0xa8

#घोषणा RTIWWDRX_NMI	0xa

#घोषणा RTIWWDSIZE_50P		0x50
#घोषणा RTIWWDSIZE_25P		0x500
#घोषणा RTIWWDSIZE_12P5		0x5000
#घोषणा RTIWWDSIZE_6P25		0x50000
#घोषणा RTIWWDSIZE_3P125	0x500000

#घोषणा WDENABLE_KEY	0xa98559da

#घोषणा WDKEY_SEQ0		0xe51a
#घोषणा WDKEY_SEQ1		0xa35c

#घोषणा WDT_PRELOAD_SHIFT	13

#घोषणा WDT_PRELOAD_MAX		0xfff

#घोषणा DWDST			BIT(1)

अटल पूर्णांक heartbeat = DEFAULT_HEARTBEAT;

/*
 * काष्ठा to hold data क्रम each WDT device
 * @base - base io address of WD device
 * @freq - source घड़ी frequency of WDT
 * @wdd  - hold watchकरोg device as is in WDT core
 */
काष्ठा rti_wdt_device अणु
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		freq;
	काष्ठा watchकरोg_device	wdd;
पूर्ण;

अटल पूर्णांक rti_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	u32 समयr_margin;
	काष्ठा rti_wdt_device *wdt = watchकरोg_get_drvdata(wdd);

	/* set समयout period */
	समयr_margin = (u64)wdd->समयout * wdt->freq;
	समयr_margin >>= WDT_PRELOAD_SHIFT;
	अगर (समयr_margin > WDT_PRELOAD_MAX)
		समयr_margin = WDT_PRELOAD_MAX;
	ग_लिखोl_relaxed(समयr_margin, wdt->base + RTIDWDPRLD);

	/*
	 * RTI only supports a winकरोwed mode, where the watchकरोg can only
	 * be petted during the खोलो winकरोw; not too early or not too late.
	 * The HW configuration options only allow क्रम the खोलो winकरोw size
	 * to be 50% or less than that; we obviouly want to configure the खोलो
	 * winकरोw as large as possible so we select the 50% option.
	 */
	wdd->min_hw_heartbeat_ms = 500 * wdd->समयout;

	/* Generate NMI when wdt expires */
	ग_लिखोl_relaxed(RTIWWDRX_NMI, wdt->base + RTIWWDRXCTRL);

	/* Open winकरोw size 50%; this is the largest winकरोw size available */
	ग_लिखोl_relaxed(RTIWWDSIZE_50P, wdt->base + RTIWWDSIZECTRL);

	पढ़ोl_relaxed(wdt->base + RTIWWDSIZECTRL);

	/* enable watchकरोg */
	ग_लिखोl_relaxed(WDENABLE_KEY, wdt->base + RTIDWDCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक rti_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा rti_wdt_device *wdt = watchकरोg_get_drvdata(wdd);

	/* put watchकरोg in service state */
	ग_लिखोl_relaxed(WDKEY_SEQ0, wdt->base + RTIWDKEY);
	/* put watchकरोg in active state */
	ग_लिखोl_relaxed(WDKEY_SEQ1, wdt->base + RTIWDKEY);

	वापस 0;
पूर्ण

अटल पूर्णांक rti_wdt_setup_hw_hb(काष्ठा watchकरोg_device *wdd, u32 wsize)
अणु
	/*
	 * RTI only supports a winकरोwed mode, where the watchकरोg can only
	 * be petted during the खोलो winकरोw; not too early or not too late.
	 * The HW configuration options only allow क्रम the खोलो winकरोw size
	 * to be 50% or less than that.
	 */
	चयन (wsize) अणु
	हाल RTIWWDSIZE_50P:
		/* 50% खोलो winकरोw => 50% min heartbeat */
		wdd->min_hw_heartbeat_ms = 500 * heartbeat;
		अवरोध;

	हाल RTIWWDSIZE_25P:
		/* 25% खोलो winकरोw => 75% min heartbeat */
		wdd->min_hw_heartbeat_ms = 750 * heartbeat;
		अवरोध;

	हाल RTIWWDSIZE_12P5:
		/* 12.5% खोलो winकरोw => 87.5% min heartbeat */
		wdd->min_hw_heartbeat_ms = 875 * heartbeat;
		अवरोध;

	हाल RTIWWDSIZE_6P25:
		/* 6.5% खोलो winकरोw => 93.5% min heartbeat */
		wdd->min_hw_heartbeat_ms = 935 * heartbeat;
		अवरोध;

	हाल RTIWWDSIZE_3P125:
		/* 3.125% खोलो winकरोw => 96.9% min heartbeat */
		wdd->min_hw_heartbeat_ms = 969 * heartbeat;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rti_wdt_get_समयleft_ms(काष्ठा watchकरोg_device *wdd)
अणु
	u64 समयr_counter;
	u32 val;
	काष्ठा rti_wdt_device *wdt = watchकरोg_get_drvdata(wdd);

	/* अगर समयout has occurred then वापस 0 */
	val = पढ़ोl_relaxed(wdt->base + RTIWDSTATUS);
	अगर (val & DWDST)
		वापस 0;

	समयr_counter = पढ़ोl_relaxed(wdt->base + RTIDWDCNTR);

	समयr_counter *= 1000;

	करो_भाग(समयr_counter, wdt->freq);

	वापस समयr_counter;
पूर्ण

अटल अचिन्हित पूर्णांक rti_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	वापस rti_wdt_get_समयleft_ms(wdd) / 1000;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info rti_wdt_info = अणु
	.options = WDIOF_KEEPALIVEPING,
	.identity = "K3 RTI Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops rti_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= rti_wdt_start,
	.ping		= rti_wdt_ping,
	.get_समयleft	= rti_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक rti_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *wdt_mem;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा rti_wdt_device *wdt;
	काष्ठा clk *clk;
	u32 last_ping = 0;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	clk = clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk), "failed to get clock\n");

	wdt->freq = clk_get_rate(clk);

	clk_put(clk);

	अगर (!wdt->freq) अणु
		dev_err(dev, "Failed to get fck rate.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * If watchकरोg is running at 32k घड़ी, it is not accurate.
	 * Adjust frequency करोwn in this हाल so that we करोn't pet
	 * the watchकरोg too often.
	 */
	अगर (wdt->freq < 32768)
		wdt->freq = wdt->freq * 9 / 10;

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret) अणु
		pm_runसमय_put_noidle(dev);
		वापस dev_err_probe(dev, ret, "runtime pm failed\n");
	पूर्ण

	platक्रमm_set_drvdata(pdev, wdt);

	wdd = &wdt->wdd;
	wdd->info = &rti_wdt_info;
	wdd->ops = &rti_wdt_ops;
	wdd->min_समयout = 1;
	wdd->max_hw_heartbeat_ms = (WDT_PRELOAD_MAX << WDT_PRELOAD_SHIFT) /
		wdt->freq * 1000;
	wdd->parent = dev;

	watchकरोg_set_drvdata(wdd, wdt);
	watchकरोg_set_nowayout(wdd, 1);
	watchकरोg_set_restart_priority(wdd, 128);

	wdt_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	wdt->base = devm_ioremap_resource(dev, wdt_mem);
	अगर (IS_ERR(wdt->base)) अणु
		ret = PTR_ERR(wdt->base);
		जाओ err_iomap;
	पूर्ण

	अगर (पढ़ोl(wdt->base + RTIDWDCTRL) == WDENABLE_KEY) अणु
		u32 समय_left_ms;
		u64 heartbeat_ms;
		u32 wsize;

		set_bit(WDOG_HW_RUNNING, &wdd->status);
		समय_left_ms = rti_wdt_get_समयleft_ms(wdd);
		heartbeat_ms = पढ़ोl(wdt->base + RTIDWDPRLD);
		heartbeat_ms <<= WDT_PRELOAD_SHIFT;
		heartbeat_ms *= 1000;
		करो_भाग(heartbeat_ms, wdt->freq);
		अगर (heartbeat_ms != heartbeat * 1000)
			dev_warn(dev, "watchdog already running, ignoring heartbeat config!\n");

		heartbeat = heartbeat_ms;
		heartbeat /= 1000;

		wsize = पढ़ोl(wdt->base + RTIWWDSIZECTRL);
		ret = rti_wdt_setup_hw_hb(wdd, wsize);
		अगर (ret) अणु
			dev_err(dev, "bad window size.\n");
			जाओ err_iomap;
		पूर्ण

		last_ping = heartbeat_ms - समय_left_ms;
		अगर (समय_left_ms > heartbeat_ms) अणु
			dev_warn(dev, "time_left > heartbeat? Assuming last ping just before now.\n");
			last_ping = 0;
		पूर्ण
	पूर्ण

	watchकरोg_init_समयout(wdd, heartbeat, dev);

	ret = watchकरोg_रेजिस्टर_device(wdd);
	अगर (ret) अणु
		dev_err(dev, "cannot register watchdog device\n");
		जाओ err_iomap;
	पूर्ण

	अगर (last_ping)
		watchकरोg_set_last_hw_keepalive(wdd, last_ping);

	वापस 0;

err_iomap:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rti_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rti_wdt_device *wdt = platक्रमm_get_drvdata(pdev);

	watchकरोg_unरेजिस्टर_device(&wdt->wdd);
	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rti_wdt_of_match[] = अणु
	अणु .compatible = "ti,j7-rti-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rti_wdt_of_match);

अटल काष्ठा platक्रमm_driver rti_wdt_driver = अणु
	.driver = अणु
		.name = "rti-wdt",
		.of_match_table = rti_wdt_of_match,
	पूर्ण,
	.probe = rti_wdt_probe,
	.हटाओ = rti_wdt_हटाओ,
पूर्ण;

module_platक्रमm_driver(rti_wdt_driver);

MODULE_AUTHOR("Tero Kristo <t-kristo@ti.com>");
MODULE_DESCRIPTION("K3 RTI Watchdog Driver");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
		 "Watchdog heartbeat period in seconds from 1 to "
		 __MODULE_STRING(MAX_HEARTBEAT) ", default "
		 __MODULE_STRING(DEFAULT_HEARTBEAT));

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rti-wdt");
