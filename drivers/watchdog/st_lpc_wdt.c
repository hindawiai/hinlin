<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ST's LPC Watchकरोg
 *
 * Copyright (C) 2014 STMicroelectronics -- All Rights Reserved
 *
 * Author: David Paris <david.paris@st.com> क्रम STMicroelectronics
 *         Lee Jones <lee.jones@linaro.org> क्रम STMicroelectronics
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

#समावेश <dt-bindings/mfd/st-lpc.h>

/* Low Power Alarm */
#घोषणा LPC_LPA_LSB_OFF			0x410
#घोषणा LPC_LPA_START_OFF		0x418

/* LPC as WDT */
#घोषणा LPC_WDT_OFF			0x510

अटल काष्ठा watchकरोg_device st_wकरोg_dev;

काष्ठा st_wकरोg_syscfg अणु
	अचिन्हित पूर्णांक reset_type_reg;
	अचिन्हित पूर्णांक reset_type_mask;
	अचिन्हित पूर्णांक enable_reg;
	अचिन्हित पूर्णांक enable_mask;
पूर्ण;

काष्ठा st_wकरोg अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा st_wकरोg_syscfg *syscfg;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clkrate;
	bool warm_reset;
पूर्ण;

अटल काष्ठा st_wकरोg_syscfg stih407_syscfg = अणु
	.enable_reg		= 0x204,
	.enable_mask		= BIT(19),
पूर्ण;

अटल स्थिर काष्ठा of_device_id st_wकरोg_match[] = अणु
	अणु
		.compatible = "st,stih407-lpc",
		.data = &stih407_syscfg,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_wकरोg_match);

अटल व्योम st_wकरोg_setup(काष्ठा st_wकरोg *st_wकरोg, bool enable)
अणु
	/* Type of watchकरोg reset - 0: Cold 1: Warm */
	अगर (st_wकरोg->syscfg->reset_type_reg)
		regmap_update_bits(st_wकरोg->regmap,
				   st_wकरोg->syscfg->reset_type_reg,
				   st_wकरोg->syscfg->reset_type_mask,
				   st_wकरोg->warm_reset);

	/* Mask/unmask watchकरोg reset */
	regmap_update_bits(st_wकरोg->regmap,
			   st_wकरोg->syscfg->enable_reg,
			   st_wकरोg->syscfg->enable_mask,
			   enable ? 0 : st_wकरोg->syscfg->enable_mask);
पूर्ण

अटल व्योम st_wकरोg_load_समयr(काष्ठा st_wकरोg *st_wकरोg, अचिन्हित पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ clkrate = st_wकरोg->clkrate;

	ग_लिखोl_relaxed(समयout * clkrate, st_wकरोg->base + LPC_LPA_LSB_OFF);
	ग_लिखोl_relaxed(1, st_wकरोg->base + LPC_LPA_START_OFF);
पूर्ण

अटल पूर्णांक st_wकरोg_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(wdd);

	ग_लिखोl_relaxed(1, st_wकरोg->base + LPC_WDT_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक st_wकरोg_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(wdd);

	ग_लिखोl_relaxed(0, st_wकरोg->base + LPC_WDT_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक st_wकरोg_set_समयout(काष्ठा watchकरोg_device *wdd,
			       अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(wdd);

	wdd->समयout = समयout;
	st_wकरोg_load_समयr(st_wकरोg, समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक st_wकरोg_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(wdd);

	st_wकरोg_load_समयr(st_wकरोg, wdd->समयout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info st_wकरोg_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "ST LPC WDT",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops st_wकरोg_ops = अणु
	.owner		= THIS_MODULE,
	.start		= st_wकरोg_start,
	.stop		= st_wकरोg_stop,
	.ping		= st_wकरोg_keepalive,
	.set_समयout	= st_wकरोg_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device st_wकरोg_dev = अणु
	.info		= &st_wकरोg_info,
	.ops		= &st_wकरोg_ops,
पूर्ण;

अटल व्योम st_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक st_wकरोg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा st_wकरोg *st_wकरोg;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	uपूर्णांक32_t mode;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "st,lpc-mode", &mode);
	अगर (ret) अणु
		dev_err(dev, "An LPC mode must be provided\n");
		वापस -EINVAL;
	पूर्ण

	/* LPC can either run as a Clocksource or in RTC or WDT mode */
	अगर (mode != ST_LPC_MODE_WDT)
		वापस -ENODEV;

	st_wकरोg = devm_kzalloc(dev, माप(*st_wकरोg), GFP_KERNEL);
	अगर (!st_wकरोg)
		वापस -ENOMEM;

	match = of_match_device(st_wकरोg_match, dev);
	अगर (!match) अणु
		dev_err(dev, "Couldn't match device\n");
		वापस -ENODEV;
	पूर्ण
	st_wकरोg->syscfg	= (काष्ठा st_wकरोg_syscfg *)match->data;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "No syscfg phandle specified\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "Unable to request clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	st_wकरोg->dev		= dev;
	st_wकरोg->base		= base;
	st_wकरोg->clk		= clk;
	st_wकरोg->regmap		= regmap;
	st_wकरोg->warm_reset	= of_property_पढ़ो_bool(np, "st,warm_reset");
	st_wकरोg->clkrate	= clk_get_rate(st_wकरोg->clk);

	अगर (!st_wकरोg->clkrate) अणु
		dev_err(dev, "Unable to fetch clock rate\n");
		वापस -EINVAL;
	पूर्ण
	st_wकरोg_dev.max_समयout = 0xFFFFFFFF / st_wकरोg->clkrate;
	st_wकरोg_dev.parent = dev;

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, st_clk_disable_unprepare, clk);
	अगर (ret)
		वापस ret;

	watchकरोg_set_drvdata(&st_wकरोg_dev, st_wकरोg);
	watchकरोg_set_nowayout(&st_wकरोg_dev, WATCHDOG_NOWAYOUT);

	/* Init Watchकरोg समयout with value in DT */
	ret = watchकरोg_init_समयout(&st_wकरोg_dev, 0, dev);
	अगर (ret)
		वापस ret;

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &st_wकरोg_dev);
	अगर (ret)
		वापस ret;

	st_wकरोg_setup(st_wकरोg, true);

	dev_info(dev, "LPC Watchdog driver registered, reset type is %s",
		 st_wकरोg->warm_reset ? "warm" : "cold");

	वापस ret;
पूर्ण

अटल पूर्णांक st_wकरोg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(&st_wकरोg_dev);

	st_wकरोg_setup(st_wकरोg, false);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक st_wकरोg_suspend(काष्ठा device *dev)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(&st_wकरोg_dev);

	अगर (watchकरोg_active(&st_wकरोg_dev))
		st_wकरोg_stop(&st_wकरोg_dev);

	st_wकरोg_setup(st_wकरोg, false);

	clk_disable(st_wकरोg->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक st_wकरोg_resume(काष्ठा device *dev)
अणु
	काष्ठा st_wकरोg *st_wकरोg = watchकरोg_get_drvdata(&st_wकरोg_dev);
	पूर्णांक ret;

	ret = clk_enable(st_wकरोg->clk);
	अगर (ret) अणु
		dev_err(dev, "Unable to re-enable clock\n");
		watchकरोg_unरेजिस्टर_device(&st_wकरोg_dev);
		clk_unprepare(st_wकरोg->clk);
		वापस ret;
	पूर्ण

	st_wकरोg_setup(st_wकरोg, true);

	अगर (watchकरोg_active(&st_wकरोg_dev)) अणु
		st_wकरोg_load_समयr(st_wकरोg, st_wकरोg_dev.समयout);
		st_wकरोg_start(&st_wकरोg_dev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(st_wकरोg_pm_ops,
			 st_wकरोg_suspend,
			 st_wकरोg_resume);

अटल काष्ठा platक्रमm_driver st_wकरोg_driver = अणु
	.driver	= अणु
		.name = "st-lpc-wdt",
		.pm = &st_wकरोg_pm_ops,
		.of_match_table = st_wकरोg_match,
	पूर्ण,
	.probe = st_wकरोg_probe,
	.हटाओ = st_wकरोg_हटाओ,
पूर्ण;
module_platक्रमm_driver(st_wकरोg_driver);

MODULE_AUTHOR("David Paris <david.paris@st.com>");
MODULE_DESCRIPTION("ST LPC Watchdog Driver");
MODULE_LICENSE("GPL");
