<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/watchकरोg.h>

#घोषणा WDOG_CS			0x0
#घोषणा WDOG_CS_CMD32EN		BIT(13)
#घोषणा WDOG_CS_ULK		BIT(11)
#घोषणा WDOG_CS_RCS		BIT(10)
#घोषणा LPO_CLK			0x1
#घोषणा LPO_CLK_SHIFT		8
#घोषणा WDOG_CS_CLK		(LPO_CLK << LPO_CLK_SHIFT)
#घोषणा WDOG_CS_EN		BIT(7)
#घोषणा WDOG_CS_UPDATE		BIT(5)
#घोषणा WDOG_CS_WAIT		BIT(1)
#घोषणा WDOG_CS_STOP		BIT(0)

#घोषणा WDOG_CNT	0x4
#घोषणा WDOG_TOVAL	0x8

#घोषणा REFRESH_SEQ0	0xA602
#घोषणा REFRESH_SEQ1	0xB480
#घोषणा REFRESH		((REFRESH_SEQ1 << 16) | REFRESH_SEQ0)

#घोषणा UNLOCK_SEQ0	0xC520
#घोषणा UNLOCK_SEQ1	0xD928
#घोषणा UNLOCK		((UNLOCK_SEQ1 << 16) | UNLOCK_SEQ0)

#घोषणा DEFAULT_TIMEOUT	60
#घोषणा MAX_TIMEOUT	128
#घोषणा WDOG_CLOCK_RATE	1000
#घोषणा WDOG_WAIT_TIMEOUT	20

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0000);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा imx7ulp_wdt_device अणु
	काष्ठा watchकरोg_device wdd;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक imx7ulp_wdt_रुको(व्योम __iomem *base, u32 mask)
अणु
	u32 val = पढ़ोl(base + WDOG_CS);

	अगर (!(val & mask) && पढ़ोl_poll_समयout_atomic(base + WDOG_CS, val,
						       val & mask, 0,
						       WDOG_WAIT_TIMEOUT))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक imx7ulp_wdt_enable(काष्ठा watchकरोg_device *wकरोg, bool enable)
अणु
	काष्ठा imx7ulp_wdt_device *wdt = watchकरोg_get_drvdata(wकरोg);

	u32 val = पढ़ोl(wdt->base + WDOG_CS);
	पूर्णांक ret;

	local_irq_disable();
	ग_लिखोl(UNLOCK, wdt->base + WDOG_CNT);
	ret = imx7ulp_wdt_रुको(wdt->base, WDOG_CS_ULK);
	अगर (ret)
		जाओ enable_out;
	अगर (enable)
		ग_लिखोl(val | WDOG_CS_EN, wdt->base + WDOG_CS);
	अन्यथा
		ग_लिखोl(val & ~WDOG_CS_EN, wdt->base + WDOG_CS);
	imx7ulp_wdt_रुको(wdt->base, WDOG_CS_RCS);

enable_out:
	local_irq_enable();

	वापस ret;
पूर्ण

अटल bool imx7ulp_wdt_is_enabled(व्योम __iomem *base)
अणु
	u32 val = पढ़ोl(base + WDOG_CS);

	वापस val & WDOG_CS_EN;
पूर्ण

अटल पूर्णांक imx7ulp_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा imx7ulp_wdt_device *wdt = watchकरोg_get_drvdata(wकरोg);

	ग_लिखोl(REFRESH, wdt->base + WDOG_CNT);

	वापस 0;
पूर्ण

अटल पूर्णांक imx7ulp_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस imx7ulp_wdt_enable(wकरोg, true);
पूर्ण

अटल पूर्णांक imx7ulp_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	वापस imx7ulp_wdt_enable(wकरोg, false);
पूर्ण

अटल पूर्णांक imx7ulp_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				   अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा imx7ulp_wdt_device *wdt = watchकरोg_get_drvdata(wकरोg);
	u32 val = WDOG_CLOCK_RATE * समयout;
	पूर्णांक ret;

	local_irq_disable();
	ग_लिखोl(UNLOCK, wdt->base + WDOG_CNT);
	ret = imx7ulp_wdt_रुको(wdt->base, WDOG_CS_ULK);
	अगर (ret)
		जाओ समयout_out;
	ग_लिखोl(val, wdt->base + WDOG_TOVAL);
	imx7ulp_wdt_रुको(wdt->base, WDOG_CS_RCS);

	wकरोg->समयout = समयout;

समयout_out:
	local_irq_enable();

	वापस ret;
पूर्ण

अटल पूर्णांक imx7ulp_wdt_restart(काष्ठा watchकरोg_device *wकरोg,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा imx7ulp_wdt_device *wdt = watchकरोg_get_drvdata(wकरोg);
	पूर्णांक ret;

	ret = imx7ulp_wdt_enable(wकरोg, true);
	अगर (ret)
		वापस ret;

	ret = imx7ulp_wdt_set_समयout(&wdt->wdd, 1);
	अगर (ret)
		वापस ret;

	/* रुको क्रम wकरोg to fire */
	जबतक (true)
		;

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops imx7ulp_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = imx7ulp_wdt_start,
	.stop  = imx7ulp_wdt_stop,
	.ping  = imx7ulp_wdt_ping,
	.set_समयout = imx7ulp_wdt_set_समयout,
	.restart = imx7ulp_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info imx7ulp_wdt_info = अणु
	.identity = "i.MX7ULP watchdog timer",
	.options  = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
		    WDIOF_MAGICCLOSE,
पूर्ण;

अटल पूर्णांक imx7ulp_wdt_init(व्योम __iomem *base, अचिन्हित पूर्णांक समयout)
अणु
	u32 val;
	पूर्णांक ret;

	local_irq_disable();
	/* unlock the wकरोg क्रम reconfiguration */
	ग_लिखोl_relaxed(UNLOCK_SEQ0, base + WDOG_CNT);
	ग_लिखोl_relaxed(UNLOCK_SEQ1, base + WDOG_CNT);
	ret = imx7ulp_wdt_रुको(base, WDOG_CS_ULK);
	अगर (ret)
		जाओ init_out;

	/* set an initial समयout value in TOVAL */
	ग_लिखोl(समयout, base + WDOG_TOVAL);
	/* enable 32bit command sequence and reconfigure */
	val = WDOG_CS_CMD32EN | WDOG_CS_CLK | WDOG_CS_UPDATE |
	      WDOG_CS_WAIT | WDOG_CS_STOP;
	ग_लिखोl(val, base + WDOG_CS);
	imx7ulp_wdt_रुको(base, WDOG_CS_RCS);

init_out:
	local_irq_enable();

	वापस ret;
पूर्ण

अटल व्योम imx7ulp_wdt_action(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक imx7ulp_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx7ulp_wdt_device *imx7ulp_wdt;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wकरोg;
	पूर्णांक ret;

	imx7ulp_wdt = devm_kzalloc(dev, माप(*imx7ulp_wdt), GFP_KERNEL);
	अगर (!imx7ulp_wdt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, imx7ulp_wdt);

	imx7ulp_wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(imx7ulp_wdt->base))
		वापस PTR_ERR(imx7ulp_wdt->base);

	imx7ulp_wdt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(imx7ulp_wdt->clk)) अणु
		dev_err(dev, "Failed to get watchdog clock\n");
		वापस PTR_ERR(imx7ulp_wdt->clk);
	पूर्ण

	ret = clk_prepare_enable(imx7ulp_wdt->clk);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, imx7ulp_wdt_action, imx7ulp_wdt->clk);
	अगर (ret)
		वापस ret;

	wकरोg = &imx7ulp_wdt->wdd;
	wकरोg->info = &imx7ulp_wdt_info;
	wकरोg->ops = &imx7ulp_wdt_ops;
	wकरोg->min_समयout = 1;
	wकरोg->max_समयout = MAX_TIMEOUT;
	wकरोg->parent = dev;
	wकरोg->समयout = DEFAULT_TIMEOUT;

	watchकरोg_init_समयout(wकरोg, 0, dev);
	watchकरोg_stop_on_reboot(wकरोg);
	watchकरोg_stop_on_unरेजिस्टर(wकरोg);
	watchकरोg_set_drvdata(wकरोg, imx7ulp_wdt);
	ret = imx7ulp_wdt_init(imx7ulp_wdt->base, wकरोg->समयout * WDOG_CLOCK_RATE);
	अगर (ret)
		वापस ret;

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wकरोg);
पूर्ण

अटल पूर्णांक __maybe_unused imx7ulp_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx7ulp_wdt_device *imx7ulp_wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&imx7ulp_wdt->wdd))
		imx7ulp_wdt_stop(&imx7ulp_wdt->wdd);

	clk_disable_unprepare(imx7ulp_wdt->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx7ulp_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा imx7ulp_wdt_device *imx7ulp_wdt = dev_get_drvdata(dev);
	u32 समयout = imx7ulp_wdt->wdd.समयout * WDOG_CLOCK_RATE;
	पूर्णांक ret;

	ret = clk_prepare_enable(imx7ulp_wdt->clk);
	अगर (ret)
		वापस ret;

	अगर (imx7ulp_wdt_is_enabled(imx7ulp_wdt->base))
		imx7ulp_wdt_init(imx7ulp_wdt->base, समयout);

	अगर (watchकरोg_active(&imx7ulp_wdt->wdd))
		imx7ulp_wdt_start(&imx7ulp_wdt->wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx7ulp_wdt_pm_ops, imx7ulp_wdt_suspend,
			 imx7ulp_wdt_resume);

अटल स्थिर काष्ठा of_device_id imx7ulp_wdt_dt_ids[] = अणु
	अणु .compatible = "fsl,imx7ulp-wdt", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx7ulp_wdt_dt_ids);

अटल काष्ठा platक्रमm_driver imx7ulp_wdt_driver = अणु
	.probe		= imx7ulp_wdt_probe,
	.driver		= अणु
		.name	= "imx7ulp-wdt",
		.pm	= &imx7ulp_wdt_pm_ops,
		.of_match_table = imx7ulp_wdt_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx7ulp_wdt_driver);

MODULE_AUTHOR("Anson Huang <Anson.Huang@nxp.com>");
MODULE_DESCRIPTION("Freescale i.MX7ULP watchdog driver");
MODULE_LICENSE("GPL v2");
