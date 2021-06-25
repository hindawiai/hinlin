<शैली गुरु>
/*
 * Realtek RTD129x watchकरोg
 *
 * Copyright (c) 2017 Andreas Fथअrber
 *
 * SPDX-License-Identअगरier: GPL-2.0+
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा RTD119X_TCWCR		0x0
#घोषणा RTD119X_TCWTR		0x4
#घोषणा RTD119X_TCWOV		0xc

#घोषणा RTD119X_TCWCR_WDEN_DISABLED		0xa5
#घोषणा RTD119X_TCWCR_WDEN_ENABLED		0xff
#घोषणा RTD119X_TCWCR_WDEN_MASK			0xff

#घोषणा RTD119X_TCWTR_WDCLR			BIT(0)

काष्ठा rtd119x_watchकरोg_device अणु
	काष्ठा watchकरोg_device wdt_dev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक rtd119x_wdt_start(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rtd119x_watchकरोg_device *data = watchकरोg_get_drvdata(wdev);
	u32 val;

	val = पढ़ोl_relaxed(data->base + RTD119X_TCWCR);
	val &= ~RTD119X_TCWCR_WDEN_MASK;
	val |= RTD119X_TCWCR_WDEN_ENABLED;
	ग_लिखोl(val, data->base + RTD119X_TCWCR);

	वापस 0;
पूर्ण

अटल पूर्णांक rtd119x_wdt_stop(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rtd119x_watchकरोg_device *data = watchकरोg_get_drvdata(wdev);
	u32 val;

	val = पढ़ोl_relaxed(data->base + RTD119X_TCWCR);
	val &= ~RTD119X_TCWCR_WDEN_MASK;
	val |= RTD119X_TCWCR_WDEN_DISABLED;
	ग_लिखोl(val, data->base + RTD119X_TCWCR);

	वापस 0;
पूर्ण

अटल पूर्णांक rtd119x_wdt_ping(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rtd119x_watchकरोg_device *data = watchकरोg_get_drvdata(wdev);

	ग_लिखोl_relaxed(RTD119X_TCWTR_WDCLR, data->base + RTD119X_TCWTR);

	वापस rtd119x_wdt_start(wdev);
पूर्ण

अटल पूर्णांक rtd119x_wdt_set_समयout(काष्ठा watchकरोg_device *wdev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा rtd119x_watchकरोg_device *data = watchकरोg_get_drvdata(wdev);

	ग_लिखोl(val * clk_get_rate(data->clk), data->base + RTD119X_TCWOV);

	data->wdt_dev.समयout = val;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops rtd119x_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start		= rtd119x_wdt_start,
	.stop		= rtd119x_wdt_stop,
	.ping		= rtd119x_wdt_ping,
	.set_समयout	= rtd119x_wdt_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info rtd119x_wdt_info = अणु
	.identity = "rtd119x-wdt",
	.options = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rtd119x_wdt_dt_ids[] = अणु
	 अणु .compatible = "realtek,rtd1295-watchdog" पूर्ण,
	 अणु पूर्ण
पूर्ण;

अटल व्योम rtd119x_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक rtd119x_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rtd119x_watchकरोg_device *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(dev, rtd119x_clk_disable_unprepare,
				       data->clk);
	अगर (ret)
		वापस ret;

	data->wdt_dev.info = &rtd119x_wdt_info;
	data->wdt_dev.ops = &rtd119x_wdt_ops;
	data->wdt_dev.समयout = 120;
	data->wdt_dev.max_समयout = 0xffffffff / clk_get_rate(data->clk);
	data->wdt_dev.min_समयout = 1;
	data->wdt_dev.parent = dev;

	watchकरोg_stop_on_reboot(&data->wdt_dev);
	watchकरोg_set_drvdata(&data->wdt_dev, data);
	platक्रमm_set_drvdata(pdev, data);

	ग_लिखोl_relaxed(RTD119X_TCWTR_WDCLR, data->base + RTD119X_TCWTR);
	rtd119x_wdt_set_समयout(&data->wdt_dev, data->wdt_dev.समयout);
	rtd119x_wdt_stop(&data->wdt_dev);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &data->wdt_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver rtd119x_wdt_driver = अणु
	.probe = rtd119x_wdt_probe,
	.driver = अणु
		.name = "rtd1295-watchdog",
		.of_match_table	= rtd119x_wdt_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(rtd119x_wdt_driver);
