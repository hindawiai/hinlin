<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *      पूर्णांकel-mid_wdt: generic Intel MID SCU watchकरोg driver
 *
 *      Platक्रमms supported so far:
 *      - Merrअगरield only
 *
 *      Copyright (C) 2014 Intel Corporation. All rights reserved.
 *      Contact: David Cohen <david.a.cohen@linux.पूर्णांकel.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/nmi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_data/पूर्णांकel-mid_wdt.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>
#समावेश <यंत्र/पूर्णांकel-mid.h>

#घोषणा IPC_WATCHDOG 0xf8

#घोषणा MID_WDT_PRETIMEOUT		15
#घोषणा MID_WDT_TIMEOUT_MIN		(1 + MID_WDT_PRETIMEOUT)
#घोषणा MID_WDT_TIMEOUT_MAX		170
#घोषणा MID_WDT_DEFAULT_TIMEOUT		90

/* SCU watchकरोg messages */
क्रमागत अणु
	SCU_WATCHDOG_START = 0,
	SCU_WATCHDOG_STOP,
	SCU_WATCHDOG_KEEPALIVE,
पूर्ण;

काष्ठा mid_wdt अणु
	काष्ठा watchकरोg_device wd;
	काष्ठा device *dev;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
पूर्ण;

अटल अंतरभूत पूर्णांक
wdt_command(काष्ठा mid_wdt *mid, पूर्णांक sub, स्थिर व्योम *in, माप_प्रकार inlen, माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = mid->scu;

	वापस पूर्णांकel_scu_ipc_dev_command_with_size(scu, IPC_WATCHDOG, sub, in,
						   inlen, size, शून्य, 0);
पूर्ण

अटल पूर्णांक wdt_start(काष्ठा watchकरोg_device *wd)
अणु
	काष्ठा mid_wdt *mid = watchकरोg_get_drvdata(wd);
	पूर्णांक ret, in_size;
	पूर्णांक समयout = wd->समयout;
	काष्ठा ipc_wd_start अणु
		u32 preसमयout;
		u32 समयout;
	पूर्ण ipc_wd_start = अणु समयout - MID_WDT_PRETIMEOUT, समयout पूर्ण;

	/*
	 * SCU expects the input size क्रम watchकरोg IPC to be 2 which is the
	 * size of the काष्ठाure in dwords. SCU IPC normally takes bytes
	 * but this is a special हाल where we specअगरy size to be dअगरferent
	 * than inlen.
	 */
	in_size = DIV_ROUND_UP(माप(ipc_wd_start), 4);

	ret = wdt_command(mid, SCU_WATCHDOG_START, &ipc_wd_start,
			  माप(ipc_wd_start), in_size);
	अगर (ret)
		dev_crit(mid->dev, "error starting watchdog: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक wdt_ping(काष्ठा watchकरोg_device *wd)
अणु
	काष्ठा mid_wdt *mid = watchकरोg_get_drvdata(wd);
	पूर्णांक ret;

	ret = wdt_command(mid, SCU_WATCHDOG_KEEPALIVE, शून्य, 0, 0);
	अगर (ret)
		dev_crit(mid->dev, "Error executing keepalive: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक wdt_stop(काष्ठा watchकरोg_device *wd)
अणु
	काष्ठा mid_wdt *mid = watchकरोg_get_drvdata(wd);
	पूर्णांक ret;

	ret = wdt_command(mid, SCU_WATCHDOG_STOP, शून्य, 0, 0);
	अगर (ret)
		dev_crit(mid->dev, "Error stopping watchdog: %d\n", ret);

	वापस ret;
पूर्ण

अटल irqवापस_t mid_wdt_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	panic("Kernel Watchdog");

	/* This code should not be reached */
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info mid_wdt_info = अणु
	.identity = "Intel MID SCU watchdog",
	.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops mid_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wdt_start,
	.stop = wdt_stop,
	.ping = wdt_ping,
पूर्ण;

अटल पूर्णांक mid_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdt_dev;
	काष्ठा पूर्णांकel_mid_wdt_pdata *pdata = dev->platक्रमm_data;
	काष्ठा mid_wdt *mid;
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_err(dev, "missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->probe) अणु
		ret = pdata->probe(pdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	mid = devm_kzalloc(dev, माप(*mid), GFP_KERNEL);
	अगर (!mid)
		वापस -ENOMEM;

	mid->dev = dev;
	wdt_dev = &mid->wd;

	wdt_dev->info = &mid_wdt_info;
	wdt_dev->ops = &mid_wdt_ops;
	wdt_dev->min_समयout = MID_WDT_TIMEOUT_MIN;
	wdt_dev->max_समयout = MID_WDT_TIMEOUT_MAX;
	wdt_dev->समयout = MID_WDT_DEFAULT_TIMEOUT;
	wdt_dev->parent = dev;

	watchकरोg_set_nowayout(wdt_dev, WATCHDOG_NOWAYOUT);
	watchकरोg_set_drvdata(wdt_dev, mid);

	mid->scu = devm_पूर्णांकel_scu_ipc_dev_get(dev);
	अगर (!mid->scu)
		वापस -EPROBE_DEFER;

	ret = devm_request_irq(dev, pdata->irq, mid_wdt_irq,
			       IRQF_SHARED | IRQF_NO_SUSPEND, "watchdog",
			       wdt_dev);
	अगर (ret) अणु
		dev_err(dev, "error requesting warning irq %d\n", pdata->irq);
		वापस ret;
	पूर्ण

	/*
	 * The firmware followed by U-Boot leaves the watchकरोg running
	 * with the शेष threshold which may vary. When we get here
	 * we should make a decision to prevent any side effects beक्रमe
	 * user space daemon will take care of it. The best option,
	 * taking पूर्णांकo consideration that there is no way to पढ़ो values
	 * back from hardware, is to enक्रमce watchकरोg being run with
	 * deterministic values.
	 */
	ret = wdt_start(wdt_dev);
	अगर (ret)
		वापस ret;

	/* Make sure the watchकरोg is serviced */
	set_bit(WDOG_HW_RUNNING, &wdt_dev->status);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdt_dev);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Intel MID watchdog device probed\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mid_wdt_driver = अणु
	.probe		= mid_wdt_probe,
	.driver		= अणु
		.name	= "intel_mid_wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mid_wdt_driver);

MODULE_AUTHOR("David Cohen <david.a.cohen@linux.intel.com>");
MODULE_DESCRIPTION("Watchdog Driver for Intel MID platform");
MODULE_LICENSE("GPL");
