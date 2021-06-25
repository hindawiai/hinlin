<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg driver क्रम Renesas WDT watchकरोg
 *
 * Copyright (C) 2015-17 Wolfram Sang, Sang Engineering <wsa@sang-engineering.com>
 * Copyright (C) 2015-17 Renesas Electronics Corporation
 */
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/smp.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/watchकरोg.h>

#घोषणा RWTCNT		0
#घोषणा RWTCSRA		4
#घोषणा RWTCSRA_WOVF	BIT(4)
#घोषणा RWTCSRA_WRFLG	BIT(5)
#घोषणा RWTCSRA_TME	BIT(7)
#घोषणा RWTCSRB		8

#घोषणा RWDT_DEFAULT_TIMEOUT 60U

/*
 * In probe, clk_rate is checked to be not more than 16 bit * biggest घड़ी
 * भागider (12 bits). d is only a factor to fully utilize the WDT counter and
 * will not exceed its 16 bits. Thus, no overflow, we stay below 32 bits.
 */
#घोषणा MUL_BY_CLKS_PER_SEC(p, d) \
	DIV_ROUND_UP((d) * (p)->clk_rate, clk_भागs[(p)->cks])

/* d is 16 bit, clk_भागs 12 bit -> no 32 bit overflow */
#घोषणा DIV_BY_CLKS_PER_SEC(p, d) ((d) * clk_भागs[(p)->cks] / (p)->clk_rate)

अटल स्थिर अचिन्हित पूर्णांक clk_भागs[] = अणु 1, 4, 16, 32, 64, 128, 1024, 4096 पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा rwdt_priv अणु
	व्योम __iomem *base;
	काष्ठा watchकरोg_device wdev;
	अचिन्हित दीर्घ clk_rate;
	u8 cks;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम rwdt_ग_लिखो(काष्ठा rwdt_priv *priv, u32 val, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == RWTCNT)
		val |= 0x5a5a0000;
	अन्यथा
		val |= 0xa5a5a500;

	ग_लिखोl_relaxed(val, priv->base + reg);
पूर्ण

अटल पूर्णांक rwdt_init_समयout(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rwdt_priv *priv = watchकरोg_get_drvdata(wdev);

	rwdt_ग_लिखो(priv, 65536 - MUL_BY_CLKS_PER_SEC(priv, wdev->समयout), RWTCNT);

	वापस 0;
पूर्ण

अटल व्योम rwdt_रुको_cycles(काष्ठा rwdt_priv *priv, अचिन्हित पूर्णांक cycles)
अणु
	अचिन्हित पूर्णांक delay;

	delay = DIV_ROUND_UP(cycles * 1000000, priv->clk_rate);

	usleep_range(delay, 2 * delay);
पूर्ण

अटल पूर्णांक rwdt_start(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rwdt_priv *priv = watchकरोg_get_drvdata(wdev);
	u8 val;

	pm_runसमय_get_sync(wdev->parent);

	/* Stop the समयr beक्रमe we modअगरy any रेजिस्टर */
	val = पढ़ोb_relaxed(priv->base + RWTCSRA) & ~RWTCSRA_TME;
	rwdt_ग_लिखो(priv, val, RWTCSRA);
	/* Delay 2 cycles beक्रमe setting watchकरोg counter */
	rwdt_रुको_cycles(priv, 2);

	rwdt_init_समयout(wdev);
	rwdt_ग_लिखो(priv, priv->cks, RWTCSRA);
	rwdt_ग_लिखो(priv, 0, RWTCSRB);

	जबतक (पढ़ोb_relaxed(priv->base + RWTCSRA) & RWTCSRA_WRFLG)
		cpu_relax();

	rwdt_ग_लिखो(priv, priv->cks | RWTCSRA_TME, RWTCSRA);

	वापस 0;
पूर्ण

अटल पूर्णांक rwdt_stop(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rwdt_priv *priv = watchकरोg_get_drvdata(wdev);

	rwdt_ग_लिखो(priv, priv->cks, RWTCSRA);
	/* Delay 3 cycles beक्रमe disabling module घड़ी */
	rwdt_रुको_cycles(priv, 3);
	pm_runसमय_put(wdev->parent);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rwdt_get_समयleft(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rwdt_priv *priv = watchकरोg_get_drvdata(wdev);
	u16 val = पढ़ोw_relaxed(priv->base + RWTCNT);

	वापस DIV_BY_CLKS_PER_SEC(priv, 65536 - val);
पूर्ण

/* needs to be atomic - no RPM, no usleep_range, no scheduling! */
अटल पूर्णांक rwdt_restart(काष्ठा watchकरोg_device *wdev, अचिन्हित दीर्घ action,
			व्योम *data)
अणु
	काष्ठा rwdt_priv *priv = watchकरोg_get_drvdata(wdev);
	u8 val;

	clk_prepare_enable(priv->clk);

	/* Stop the समयr beक्रमe we modअगरy any रेजिस्टर */
	val = पढ़ोb_relaxed(priv->base + RWTCSRA) & ~RWTCSRA_TME;
	rwdt_ग_लिखो(priv, val, RWTCSRA);
	/* Delay 2 cycles beक्रमe setting watchकरोg counter */
	udelay(DIV_ROUND_UP(2 * 1000000, priv->clk_rate));

	rwdt_ग_लिखो(priv, 0xffff, RWTCNT);
	/* smallest भागider to reboot soon */
	rwdt_ग_लिखो(priv, 0, RWTCSRA);

	पढ़ोb_poll_समयout_atomic(priv->base + RWTCSRA, val,
				  !(val & RWTCSRA_WRFLG), 1, 100);

	rwdt_ग_लिखो(priv, RWTCSRA_TME, RWTCSRA);

	/* रुको 2 cycles, so watchकरोg will trigger */
	udelay(DIV_ROUND_UP(2 * 1000000, priv->clk_rate));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info rwdt_ident = अणु
	.options = WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
		WDIOF_CARDRESET,
	.identity = "Renesas WDT Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops rwdt_ops = अणु
	.owner = THIS_MODULE,
	.start = rwdt_start,
	.stop = rwdt_stop,
	.ping = rwdt_init_समयout,
	.get_समयleft = rwdt_get_समयleft,
	.restart = rwdt_restart,
पूर्ण;

#अगर defined(CONFIG_ARCH_RCAR_GEN2) && defined(CONFIG_SMP)
/*
 * Watchकरोg-reset पूर्णांकegration is broken on early revisions of R-Car Gen2 SoCs
 */
अटल स्थिर काष्ठा soc_device_attribute rwdt_quirks_match[] = अणु
	अणु
		.soc_id = "r8a7790",
		.revision = "ES1.*",
		.data = (व्योम *)1,	/* needs single CPU */
	पूर्ण, अणु
		.soc_id = "r8a7791",
		.revision = "ES1.*",
		.data = (व्योम *)1,	/* needs single CPU */
	पूर्ण, अणु
		.soc_id = "r8a7792",
		.data = (व्योम *)0,	/* needs SMP disabled */
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल bool rwdt_blacklisted(काष्ठा device *dev)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;

	attr = soc_device_match(rwdt_quirks_match);
	अगर (attr && setup_max_cpus > (uपूर्णांकptr_t)attr->data) अणु
		dev_info(dev, "Watchdog blacklisted on %s %s\n", attr->soc_id,
			 attr->revision);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा /* !CONFIG_ARCH_RCAR_GEN2 || !CONFIG_SMP */
अटल अंतरभूत bool rwdt_blacklisted(काष्ठा device *dev) अणु वापस false; पूर्ण
#पूर्ण_अगर /* !CONFIG_ARCH_RCAR_GEN2 || !CONFIG_SMP */

अटल पूर्णांक rwdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rwdt_priv *priv;
	अचिन्हित दीर्घ clks_per_sec;
	पूर्णांक ret, i;
	u8 csra;

	अगर (rwdt_blacklisted(dev))
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);
	priv->clk_rate = clk_get_rate(priv->clk);
	csra = पढ़ोb_relaxed(priv->base + RWTCSRA);
	priv->wdev.bootstatus = csra & RWTCSRA_WOVF ? WDIOF_CARDRESET : 0;
	pm_runसमय_put(dev);

	अगर (!priv->clk_rate) अणु
		ret = -ENOENT;
		जाओ out_pm_disable;
	पूर्ण

	क्रम (i = ARRAY_SIZE(clk_भागs) - 1; i >= 0; i--) अणु
		clks_per_sec = priv->clk_rate / clk_भागs[i];
		अगर (clks_per_sec && clks_per_sec < 65536) अणु
			priv->cks = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i < 0) अणु
		dev_err(dev, "Can't find suitable clock divider\n");
		ret = -दुस्फल;
		जाओ out_pm_disable;
	पूर्ण

	priv->wdev.info = &rwdt_ident;
	priv->wdev.ops = &rwdt_ops;
	priv->wdev.parent = dev;
	priv->wdev.min_समयout = 1;
	priv->wdev.max_समयout = DIV_BY_CLKS_PER_SEC(priv, 65536);
	priv->wdev.समयout = min(priv->wdev.max_समयout, RWDT_DEFAULT_TIMEOUT);

	platक्रमm_set_drvdata(pdev, priv);
	watchकरोg_set_drvdata(&priv->wdev, priv);
	watchकरोg_set_nowayout(&priv->wdev, nowayout);
	watchकरोg_set_restart_priority(&priv->wdev, 0);
	watchकरोg_stop_on_unरेजिस्टर(&priv->wdev);

	/* This overrides the शेष समयout only अगर DT configuration was found */
	watchकरोg_init_समयout(&priv->wdev, 0, dev);

	/* Check अगर FW enabled the watchकरोg */
	अगर (csra & RWTCSRA_TME) अणु
		/* Ensure properly initialized भागiders */
		rwdt_start(&priv->wdev);
		set_bit(WDOG_HW_RUNNING, &priv->wdev.status);
	पूर्ण

	ret = watchकरोg_रेजिस्टर_device(&priv->wdev);
	अगर (ret < 0)
		जाओ out_pm_disable;

	वापस 0;

 out_pm_disable:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rwdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rwdt_priv *priv = platक्रमm_get_drvdata(pdev);

	watchकरोg_unरेजिस्टर_device(&priv->wdev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rwdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा rwdt_priv *priv = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&priv->wdev))
		rwdt_stop(&priv->wdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rwdt_resume(काष्ठा device *dev)
अणु
	काष्ठा rwdt_priv *priv = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&priv->wdev))
		rwdt_start(&priv->wdev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rwdt_pm_ops, rwdt_suspend, rwdt_resume);

अटल स्थिर काष्ठा of_device_id rwdt_ids[] = अणु
	अणु .compatible = "renesas,rcar-gen2-wdt", पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-wdt", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rwdt_ids);

अटल काष्ठा platक्रमm_driver rwdt_driver = अणु
	.driver = अणु
		.name = "renesas_wdt",
		.of_match_table = rwdt_ids,
		.pm = &rwdt_pm_ops,
	पूर्ण,
	.probe = rwdt_probe,
	.हटाओ = rwdt_हटाओ,
पूर्ण;
module_platक्रमm_driver(rwdt_driver);

MODULE_DESCRIPTION("Renesas WDT Watchdog Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Wolfram Sang <wsa@sang-engineering.com>");
