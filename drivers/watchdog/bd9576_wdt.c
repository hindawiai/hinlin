<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 ROHM Semiconductors
 *
 * ROHM BD9576MUF and BD9573MUF Watchकरोg driver
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mfd/rohm-bd957x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

अटल bool nowayout;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default=\"false\")");

#घोषणा HW_MARGIN_MIN 2
#घोषणा HW_MARGIN_MAX 4416
#घोषणा BD957X_WDT_DEFAULT_MARGIN 4416
#घोषणा WATCHDOG_TIMEOUT 30

काष्ठा bd9576_wdt_priv अणु
	काष्ठा gpio_desc	*gpiod_ping;
	काष्ठा gpio_desc	*gpiod_en;
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	bool			always_running;
	काष्ठा watchकरोg_device	wdd;
पूर्ण;

अटल व्योम bd9576_wdt_disable(काष्ठा bd9576_wdt_priv *priv)
अणु
	gpiod_set_value_cansleep(priv->gpiod_en, 0);
पूर्ण

अटल पूर्णांक bd9576_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bd9576_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	/* Pulse */
	gpiod_set_value_cansleep(priv->gpiod_ping, 1);
	gpiod_set_value_cansleep(priv->gpiod_ping, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bd9576_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bd9576_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	gpiod_set_value_cansleep(priv->gpiod_en, 1);

	वापस bd9576_wdt_ping(wdd);
पूर्ण

अटल पूर्णांक bd9576_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bd9576_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	अगर (!priv->always_running)
		bd9576_wdt_disable(priv);
	अन्यथा
		set_bit(WDOG_HW_RUNNING, &wdd->status);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info bd957x_wdt_ident = अणु
	.options	= WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING |
			  WDIOF_SETTIMEOUT,
	.identity	= "BD957x Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops bd957x_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= bd9576_wdt_start,
	.stop		= bd9576_wdt_stop,
	.ping		= bd9576_wdt_ping,
पूर्ण;

/* Unit is hundreds of uS */
#घोषणा FASTNG_MIN 23

अटल पूर्णांक find_बंदst_fast(पूर्णांक target, पूर्णांक *sel, पूर्णांक *val)
अणु
	पूर्णांक i;
	पूर्णांक winकरोw = FASTNG_MIN;

	क्रम (i = 0; i < 8 && winकरोw < target; i++)
		winकरोw <<= 1;

	*val = winकरोw;
	*sel = i;

	अगर (i == 8)
		वापस -EINVAL;

	वापस 0;

पूर्ण

अटल पूर्णांक find_बंदst_slow_by_fast(पूर्णांक fast_val, पूर्णांक target, पूर्णांक *slowsel)
अणु
	पूर्णांक sel;
	अटल स्थिर पूर्णांक multipliers[] = अणु2, 3, 7, 15पूर्ण;

	क्रम (sel = 0; sel < ARRAY_SIZE(multipliers) &&
	     multipliers[sel] * fast_val < target; sel++)
		;

	अगर (sel == ARRAY_SIZE(multipliers))
		वापस -EINVAL;

	*slowsel = sel;

	वापस 0;
पूर्ण

अटल पूर्णांक find_बंदst_slow(पूर्णांक target, पूर्णांक *slow_sel, पूर्णांक *fast_sel)
अणु
	अटल स्थिर पूर्णांक multipliers[] = अणु2, 3, 7, 15पूर्ण;
	पूर्णांक i, j;
	पूर्णांक val = 0;
	पूर्णांक winकरोw = FASTNG_MIN;

	क्रम (i = 0; i < 8; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(multipliers); j++) अणु
			पूर्णांक slow;

			slow = winकरोw * multipliers[j];
			अगर (slow >= target && (!val || slow < val)) अणु
				val = slow;
				*fast_sel = i;
				*slow_sel = j;
			पूर्ण
		पूर्ण
		winकरोw <<= 1;
	पूर्ण
	अगर (!val)
		वापस -EINVAL;

	वापस 0;
पूर्ण

#घोषणा BD957X_WDG_TYPE_WINDOW BIT(5)
#घोषणा BD957X_WDG_TYPE_SLOW 0
#घोषणा BD957X_WDG_TYPE_MASK BIT(5)
#घोषणा BD957X_WDG_NG_RATIO_MASK 0x18
#घोषणा BD957X_WDG_FASTNG_MASK 0x7

अटल पूर्णांक bd957x_set_wdt_mode(काष्ठा bd9576_wdt_priv *priv, पूर्णांक hw_margin,
			       पूर्णांक hw_margin_min)
अणु
	पूर्णांक ret, fastng, slowng, type, reg, mask;
	काष्ठा device *dev = priv->dev;

	/* convert to 100uS */
	hw_margin *= 10;
	hw_margin_min *= 10;
	अगर (hw_margin_min) अणु
		पूर्णांक min;

		type = BD957X_WDG_TYPE_WINDOW;
		dev_dbg(dev, "Setting type WINDOW 0x%x\n", type);
		ret = find_बंदst_fast(hw_margin_min, &fastng, &min);
		अगर (ret) अणु
			dev_err(dev, "bad WDT window for fast timeout\n");
			वापस ret;
		पूर्ण

		ret = find_बंदst_slow_by_fast(min, hw_margin, &slowng);
		अगर (ret) अणु
			dev_err(dev, "bad WDT window\n");
			वापस ret;
		पूर्ण

	पूर्ण अन्यथा अणु
		type = BD957X_WDG_TYPE_SLOW;
		dev_dbg(dev, "Setting type SLOW 0x%x\n", type);
		ret = find_बंदst_slow(hw_margin, &slowng, &fastng);
		अगर (ret) अणु
			dev_err(dev, "bad WDT window\n");
			वापस ret;
		पूर्ण
	पूर्ण

	slowng <<= ffs(BD957X_WDG_NG_RATIO_MASK) - 1;
	reg = type | slowng | fastng;
	mask = BD957X_WDG_TYPE_MASK | BD957X_WDG_NG_RATIO_MASK |
	       BD957X_WDG_FASTNG_MASK;
	ret = regmap_update_bits(priv->regmap, BD957X_REG_WDT_CONF,
				 mask, reg);

	वापस ret;
पूर्ण

अटल पूर्णांक bd9576_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->parent->of_node;
	काष्ठा bd9576_wdt_priv *priv;
	u32 hw_margin[2];
	u32 hw_margin_max = BD957X_WDT_DEFAULT_MARGIN, hw_margin_min = 0;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	priv->dev = dev;
	priv->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!priv->regmap) अणु
		dev_err(dev, "No regmap found\n");
		वापस -ENODEV;
	पूर्ण

	priv->gpiod_en = devm_gpiod_get_from_of_node(dev, dev->parent->of_node,
						     "rohm,watchdog-enable-gpios",
						     0, GPIOD_OUT_LOW,
						     "watchdog-enable");
	अगर (IS_ERR(priv->gpiod_en))
		वापस dev_err_probe(dev, PTR_ERR(priv->gpiod_en),
			      "getting watchdog-enable GPIO failed\n");

	priv->gpiod_ping = devm_gpiod_get_from_of_node(dev, dev->parent->of_node,
						     "rohm,watchdog-ping-gpios",
						     0, GPIOD_OUT_LOW,
						     "watchdog-ping");
	अगर (IS_ERR(priv->gpiod_ping))
		वापस dev_err_probe(dev, PTR_ERR(priv->gpiod_ping),
				     "getting watchdog-ping GPIO failed\n");

	ret = of_property_पढ़ो_variable_u32_array(np, "rohm,hw-timeout-ms",
						  &hw_margin[0], 1, 2);
	अगर (ret < 0 && ret != -EINVAL)
		वापस ret;

	अगर (ret == 1)
		hw_margin_max = hw_margin[0];

	अगर (ret == 2) अणु
		hw_margin_max = hw_margin[1];
		hw_margin_min = hw_margin[0];
	पूर्ण

	ret = bd957x_set_wdt_mode(priv, hw_margin_max, hw_margin_min);
	अगर (ret)
		वापस ret;

	priv->always_running = of_property_पढ़ो_bool(np, "always-running");

	watchकरोg_set_drvdata(&priv->wdd, priv);

	priv->wdd.info			= &bd957x_wdt_ident;
	priv->wdd.ops			= &bd957x_wdt_ops;
	priv->wdd.min_hw_heartbeat_ms	= hw_margin_min;
	priv->wdd.max_hw_heartbeat_ms	= hw_margin_max;
	priv->wdd.parent		= dev;
	priv->wdd.समयout		= WATCHDOG_TIMEOUT;

	watchकरोg_init_समयout(&priv->wdd, 0, dev);
	watchकरोg_set_nowayout(&priv->wdd, nowayout);

	watchकरोg_stop_on_reboot(&priv->wdd);

	अगर (priv->always_running)
		bd9576_wdt_start(&priv->wdd);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &priv->wdd);
पूर्ण

अटल काष्ठा platक्रमm_driver bd9576_wdt_driver = अणु
	.driver	= अणु
		.name = "bd9576-wdt",
	पूर्ण,
	.probe	= bd9576_wdt_probe,
पूर्ण;

module_platक्रमm_driver(bd9576_wdt_driver);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD9576/BD9573 Watchdog driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd9576-wdt");
