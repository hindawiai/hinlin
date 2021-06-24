<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Imagination Technologies PowerDown Controller Watchकरोg Timer.
 *
 * Copyright (c) 2014 Imagination Technologies Ltd.
 *
 * Based on drivers/watchकरोg/sunxi_wdt.c Copyright (c) 2013 Carlo Caione
 *                                                     2012 Henrik Nordstrom
 *
 * Notes
 * -----
 * The समयout value is rounded to the next घातer of two घड़ी cycles.
 * This is configured using the PDC_WDT_CONFIG रेजिस्टर, according to this
 * क्रमmula:
 *
 *     समयout = 2^(delay + 1) घड़ी cycles
 *
 * Where 'delay' is the value written in PDC_WDT_CONFIG रेजिस्टर.
 *
 * Thereक्रमe, the hardware only allows to program watchकरोg समयouts, expressed
 * as a घातer of two number of watchकरोg घड़ी cycles. The current implementation
 * guarantees that the actual watchकरोg समयout will be _at least_ the value
 * programmed in the imgpdg_wdt driver.
 *
 * The following table shows how the user-configured समयout relates
 * to the actual hardware समयout (watchकरोg घड़ी @ 40000 Hz):
 *
 * input समयout | WD_DELAY | actual समयout
 * -----------------------------------
 *      10       |   18     |  13 seconds
 *      20       |   19     |  26 seconds
 *      30       |   20     |  52 seconds
 *      60       |   21     |  104 seconds
 *
 * Albeit coarse, this granularity would suffice most watchकरोg uses.
 * If the platक्रमm allows it, the user should be able to change the watchकरोg
 * घड़ी rate and achieve a finer समयout granularity.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>

/* रेजिस्टरs */
#घोषणा PDC_WDT_SOFT_RESET		0x00
#घोषणा PDC_WDT_CONFIG			0x04
  #घोषणा PDC_WDT_CONFIG_ENABLE		BIT(31)
  #घोषणा PDC_WDT_CONFIG_DELAY_MASK	0x1f

#घोषणा PDC_WDT_TICKLE1			0x08
#घोषणा PDC_WDT_TICKLE1_MAGIC		0xabcd1234
#घोषणा PDC_WDT_TICKLE2			0x0c
#घोषणा PDC_WDT_TICKLE2_MAGIC		0x4321dcba

#घोषणा PDC_WDT_TICKLE_STATUS_MASK	0x7
#घोषणा PDC_WDT_TICKLE_STATUS_SHIFT	0
#घोषणा PDC_WDT_TICKLE_STATUS_HRESET	0x0  /* Hard reset */
#घोषणा PDC_WDT_TICKLE_STATUS_TIMEOUT	0x1  /* Timeout */
#घोषणा PDC_WDT_TICKLE_STATUS_TICKLE	0x2  /* Tickled incorrectly */
#घोषणा PDC_WDT_TICKLE_STATUS_SRESET	0x3  /* Soft reset */
#घोषणा PDC_WDT_TICKLE_STATUS_USER	0x4  /* User reset */

/* Timeout values are in seconds */
#घोषणा PDC_WDT_MIN_TIMEOUT		1
#घोषणा PDC_WDT_DEF_TIMEOUT		64

अटल पूर्णांक heartbeat;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeats in seconds "
	"(default=" __MODULE_STRING(PDC_WDT_DEF_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा pdc_wdt_dev अणु
	काष्ठा watchकरोg_device wdt_dev;
	काष्ठा clk *wdt_clk;
	काष्ठा clk *sys_clk;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक pdc_wdt_keepalive(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा pdc_wdt_dev *wdt = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(PDC_WDT_TICKLE1_MAGIC, wdt->base + PDC_WDT_TICKLE1);
	ग_लिखोl(PDC_WDT_TICKLE2_MAGIC, wdt->base + PDC_WDT_TICKLE2);

	वापस 0;
पूर्ण

अटल पूर्णांक pdc_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा pdc_wdt_dev *wdt = watchकरोg_get_drvdata(wdt_dev);

	val = पढ़ोl(wdt->base + PDC_WDT_CONFIG);
	val &= ~PDC_WDT_CONFIG_ENABLE;
	ग_लिखोl(val, wdt->base + PDC_WDT_CONFIG);

	/* Must tickle to finish the stop */
	pdc_wdt_keepalive(wdt_dev);

	वापस 0;
पूर्ण

अटल व्योम __pdc_wdt_set_समयout(काष्ठा pdc_wdt_dev *wdt)
अणु
	अचिन्हित दीर्घ clk_rate = clk_get_rate(wdt->wdt_clk);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(wdt->base + PDC_WDT_CONFIG) & ~PDC_WDT_CONFIG_DELAY_MASK;
	val |= order_base_2(wdt->wdt_dev.समयout * clk_rate) - 1;
	ग_लिखोl(val, wdt->base + PDC_WDT_CONFIG);
पूर्ण

अटल पूर्णांक pdc_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
			       अचिन्हित पूर्णांक new_समयout)
अणु
	काष्ठा pdc_wdt_dev *wdt = watchकरोg_get_drvdata(wdt_dev);

	wdt->wdt_dev.समयout = new_समयout;

	__pdc_wdt_set_समयout(wdt);

	वापस 0;
पूर्ण

/* Start the watchकरोg समयr (delay should alपढ़ोy be set) */
अटल पूर्णांक pdc_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा pdc_wdt_dev *wdt = watchकरोg_get_drvdata(wdt_dev);

	__pdc_wdt_set_समयout(wdt);

	val = पढ़ोl(wdt->base + PDC_WDT_CONFIG);
	val |= PDC_WDT_CONFIG_ENABLE;
	ग_लिखोl(val, wdt->base + PDC_WDT_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक pdc_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा pdc_wdt_dev *wdt = watchकरोg_get_drvdata(wdt_dev);

	/* Assert SOFT_RESET */
	ग_लिखोl(0x1, wdt->base + PDC_WDT_SOFT_RESET);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info pdc_wdt_info = अणु
	.identity	= "IMG PDC Watchdog",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops pdc_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= pdc_wdt_start,
	.stop		= pdc_wdt_stop,
	.ping		= pdc_wdt_keepalive,
	.set_समयout	= pdc_wdt_set_समयout,
	.restart        = pdc_wdt_restart,
पूर्ण;

अटल व्योम pdc_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक pdc_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	u64 भाग;
	पूर्णांक ret, val;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा pdc_wdt_dev *pdc_wdt;

	pdc_wdt = devm_kzalloc(dev, माप(*pdc_wdt), GFP_KERNEL);
	अगर (!pdc_wdt)
		वापस -ENOMEM;

	pdc_wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdc_wdt->base))
		वापस PTR_ERR(pdc_wdt->base);

	pdc_wdt->sys_clk = devm_clk_get(dev, "sys");
	अगर (IS_ERR(pdc_wdt->sys_clk)) अणु
		dev_err(dev, "failed to get the sys clock\n");
		वापस PTR_ERR(pdc_wdt->sys_clk);
	पूर्ण

	pdc_wdt->wdt_clk = devm_clk_get(dev, "wdt");
	अगर (IS_ERR(pdc_wdt->wdt_clk)) अणु
		dev_err(dev, "failed to get the wdt clock\n");
		वापस PTR_ERR(pdc_wdt->wdt_clk);
	पूर्ण

	ret = clk_prepare_enable(pdc_wdt->sys_clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare or enable sys clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, pdc_clk_disable_unprepare,
				       pdc_wdt->sys_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(pdc_wdt->wdt_clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare or enable wdt clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, pdc_clk_disable_unprepare,
				       pdc_wdt->wdt_clk);
	अगर (ret)
		वापस ret;

	/* We use the घड़ी rate to calculate the max समयout */
	clk_rate = clk_get_rate(pdc_wdt->wdt_clk);
	अगर (clk_rate == 0) अणु
		dev_err(dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (order_base_2(clk_rate) > PDC_WDT_CONFIG_DELAY_MASK + 1) अणु
		dev_err(dev, "invalid clock rate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (order_base_2(clk_rate) == 0)
		pdc_wdt->wdt_dev.min_समयout = PDC_WDT_MIN_TIMEOUT + 1;
	अन्यथा
		pdc_wdt->wdt_dev.min_समयout = PDC_WDT_MIN_TIMEOUT;

	pdc_wdt->wdt_dev.info = &pdc_wdt_info;
	pdc_wdt->wdt_dev.ops = &pdc_wdt_ops;

	भाग = 1ULL << (PDC_WDT_CONFIG_DELAY_MASK + 1);
	करो_भाग(भाग, clk_rate);
	pdc_wdt->wdt_dev.max_समयout = भाग;
	pdc_wdt->wdt_dev.समयout = PDC_WDT_DEF_TIMEOUT;
	pdc_wdt->wdt_dev.parent = dev;
	watchकरोg_set_drvdata(&pdc_wdt->wdt_dev, pdc_wdt);

	watchकरोg_init_समयout(&pdc_wdt->wdt_dev, heartbeat, dev);

	pdc_wdt_stop(&pdc_wdt->wdt_dev);

	/* Find what caused the last reset */
	val = पढ़ोl(pdc_wdt->base + PDC_WDT_TICKLE1);
	val = (val & PDC_WDT_TICKLE_STATUS_MASK) >> PDC_WDT_TICKLE_STATUS_SHIFT;
	चयन (val) अणु
	हाल PDC_WDT_TICKLE_STATUS_TICKLE:
	हाल PDC_WDT_TICKLE_STATUS_TIMEOUT:
		pdc_wdt->wdt_dev.bootstatus |= WDIOF_CARDRESET;
		dev_info(dev, "watchdog module last reset due to timeout\n");
		अवरोध;
	हाल PDC_WDT_TICKLE_STATUS_HRESET:
		dev_info(dev,
			 "watchdog module last reset due to hard reset\n");
		अवरोध;
	हाल PDC_WDT_TICKLE_STATUS_SRESET:
		dev_info(dev,
			 "watchdog module last reset due to soft reset\n");
		अवरोध;
	हाल PDC_WDT_TICKLE_STATUS_USER:
		dev_info(dev,
			 "watchdog module last reset due to user reset\n");
		अवरोध;
	शेष:
		dev_info(dev, "contains an illegal status code (%08x)\n", val);
		अवरोध;
	पूर्ण

	watchकरोg_set_nowayout(&pdc_wdt->wdt_dev, nowayout);
	watchकरोg_set_restart_priority(&pdc_wdt->wdt_dev, 128);

	platक्रमm_set_drvdata(pdev, pdc_wdt);

	watchकरोg_stop_on_reboot(&pdc_wdt->wdt_dev);
	watchकरोg_stop_on_unरेजिस्टर(&pdc_wdt->wdt_dev);
	वापस devm_watchकरोg_रेजिस्टर_device(dev, &pdc_wdt->wdt_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id pdc_wdt_match[] = अणु
	अणु .compatible = "img,pdc-wdt" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pdc_wdt_match);

अटल काष्ठा platक्रमm_driver pdc_wdt_driver = अणु
	.driver = अणु
		.name = "imgpdc-wdt",
		.of_match_table	= pdc_wdt_match,
	पूर्ण,
	.probe = pdc_wdt_probe,
पूर्ण;
module_platक्रमm_driver(pdc_wdt_driver);

MODULE_AUTHOR("Jude Abraham <Jude.Abraham@imgtec.com>");
MODULE_AUTHOR("Naidu Tellapati <Naidu.Tellapati@imgtec.com>");
MODULE_DESCRIPTION("Imagination Technologies PDC Watchdog Timer Driver");
MODULE_LICENSE("GPL v2");
