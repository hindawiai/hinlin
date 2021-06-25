<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DEFAULT_TIMEOUT	30	/* seconds */

#घोषणा GXBB_WDT_CTRL_REG			0x0
#घोषणा GXBB_WDT_TCNT_REG			0x8
#घोषणा GXBB_WDT_RSET_REG			0xc

#घोषणा GXBB_WDT_CTRL_CLKDIV_EN			BIT(25)
#घोषणा GXBB_WDT_CTRL_CLK_EN			BIT(24)
#घोषणा GXBB_WDT_CTRL_EE_RESET			BIT(21)
#घोषणा GXBB_WDT_CTRL_EN			BIT(18)
#घोषणा GXBB_WDT_CTRL_DIV_MASK			(BIT(18) - 1)

#घोषणा GXBB_WDT_TCNT_SETUP_MASK		(BIT(16) - 1)
#घोषणा GXBB_WDT_TCNT_CNT_SHIFT			16

काष्ठा meson_gxbb_wdt अणु
	व्योम __iomem *reg_base;
	काष्ठा watchकरोg_device wdt_dev;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक meson_gxbb_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_gxbb_wdt *data = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(पढ़ोl(data->reg_base + GXBB_WDT_CTRL_REG) | GXBB_WDT_CTRL_EN,
	       data->reg_base + GXBB_WDT_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_gxbb_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_gxbb_wdt *data = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(पढ़ोl(data->reg_base + GXBB_WDT_CTRL_REG) & ~GXBB_WDT_CTRL_EN,
	       data->reg_base + GXBB_WDT_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_gxbb_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_gxbb_wdt *data = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(0, data->reg_base + GXBB_WDT_RSET_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_gxbb_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				      अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा meson_gxbb_wdt *data = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ tcnt = समयout * 1000;

	अगर (tcnt > GXBB_WDT_TCNT_SETUP_MASK)
		tcnt = GXBB_WDT_TCNT_SETUP_MASK;

	wdt_dev->समयout = समयout;

	meson_gxbb_wdt_ping(wdt_dev);

	ग_लिखोl(tcnt, data->reg_base + GXBB_WDT_TCNT_REG);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक meson_gxbb_wdt_get_समयleft(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा meson_gxbb_wdt *data = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(data->reg_base + GXBB_WDT_TCNT_REG);

	वापस ((reg & GXBB_WDT_TCNT_SETUP_MASK) -
		(reg >> GXBB_WDT_TCNT_CNT_SHIFT)) / 1000;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops meson_gxbb_wdt_ops = अणु
	.start = meson_gxbb_wdt_start,
	.stop = meson_gxbb_wdt_stop,
	.ping = meson_gxbb_wdt_ping,
	.set_समयout = meson_gxbb_wdt_set_समयout,
	.get_समयleft = meson_gxbb_wdt_get_समयleft,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info meson_gxbb_wdt_info = अणु
	.identity = "Meson GXBB Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल पूर्णांक __maybe_unused meson_gxbb_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा meson_gxbb_wdt *data = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&data->wdt_dev))
		meson_gxbb_wdt_start(&data->wdt_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused meson_gxbb_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा meson_gxbb_wdt *data = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&data->wdt_dev))
		meson_gxbb_wdt_stop(&data->wdt_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops meson_gxbb_wdt_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(meson_gxbb_wdt_suspend, meson_gxbb_wdt_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_gxbb_wdt_dt_ids[] = अणु
	 अणु .compatible = "amlogic,meson-gxbb-wdt", पूर्ण,
	 अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_gxbb_wdt_dt_ids);

अटल व्योम meson_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक meson_gxbb_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_gxbb_wdt *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->reg_base))
		वापस PTR_ERR(data->reg_base);

	data->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(dev, meson_clk_disable_unprepare,
				       data->clk);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, data);

	data->wdt_dev.parent = dev;
	data->wdt_dev.info = &meson_gxbb_wdt_info;
	data->wdt_dev.ops = &meson_gxbb_wdt_ops;
	data->wdt_dev.max_hw_heartbeat_ms = GXBB_WDT_TCNT_SETUP_MASK;
	data->wdt_dev.min_समयout = 1;
	data->wdt_dev.समयout = DEFAULT_TIMEOUT;
	watchकरोg_set_drvdata(&data->wdt_dev, data);

	/* Setup with 1ms समयbase */
	ग_लिखोl(((clk_get_rate(data->clk) / 1000) & GXBB_WDT_CTRL_DIV_MASK) |
		GXBB_WDT_CTRL_EE_RESET |
		GXBB_WDT_CTRL_CLK_EN |
		GXBB_WDT_CTRL_CLKDIV_EN,
		data->reg_base + GXBB_WDT_CTRL_REG);

	meson_gxbb_wdt_set_समयout(&data->wdt_dev, data->wdt_dev.समयout);

	watchकरोg_stop_on_reboot(&data->wdt_dev);
	वापस devm_watchकरोg_रेजिस्टर_device(dev, &data->wdt_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver meson_gxbb_wdt_driver = अणु
	.probe	= meson_gxbb_wdt_probe,
	.driver = अणु
		.name = "meson-gxbb-wdt",
		.pm = &meson_gxbb_wdt_pm_ops,
		.of_match_table	= meson_gxbb_wdt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_gxbb_wdt_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Amlogic Meson GXBB Watchdog timer driver");
MODULE_LICENSE("Dual BSD/GPL");
