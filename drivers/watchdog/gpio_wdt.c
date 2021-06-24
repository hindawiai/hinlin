<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम watchकरोg device controlled through GPIO-line
 *
 * Author: 2013, Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा SOFT_TIMEOUT_MIN	1
#घोषणा SOFT_TIMEOUT_DEF	60

क्रमागत अणु
	HW_ALGO_TOGGLE,
	HW_ALGO_LEVEL,
पूर्ण;

काष्ठा gpio_wdt_priv अणु
	काष्ठा gpio_desc	*gpiod;
	bool			state;
	bool			always_running;
	अचिन्हित पूर्णांक		hw_algo;
	काष्ठा watchकरोg_device	wdd;
पूर्ण;

अटल व्योम gpio_wdt_disable(काष्ठा gpio_wdt_priv *priv)
अणु
	/* Eternal ping */
	gpiod_set_value_cansleep(priv->gpiod, 1);

	/* Put GPIO back to tristate */
	अगर (priv->hw_algo == HW_ALGO_TOGGLE)
		gpiod_direction_input(priv->gpiod);
पूर्ण

अटल पूर्णांक gpio_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा gpio_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	चयन (priv->hw_algo) अणु
	हाल HW_ALGO_TOGGLE:
		/* Toggle output pin */
		priv->state = !priv->state;
		gpiod_set_value_cansleep(priv->gpiod, priv->state);
		अवरोध;
	हाल HW_ALGO_LEVEL:
		/* Pulse */
		gpiod_set_value_cansleep(priv->gpiod, 1);
		udelay(1);
		gpiod_set_value_cansleep(priv->gpiod, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा gpio_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	priv->state = 0;
	gpiod_direction_output(priv->gpiod, priv->state);

	set_bit(WDOG_HW_RUNNING, &wdd->status);

	वापस gpio_wdt_ping(wdd);
पूर्ण

अटल पूर्णांक gpio_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा gpio_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	अगर (!priv->always_running) अणु
		gpio_wdt_disable(priv);
	पूर्ण अन्यथा अणु
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info gpio_wdt_ident = अणु
	.options	= WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING |
			  WDIOF_SETTIMEOUT,
	.identity	= "GPIO Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops gpio_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= gpio_wdt_start,
	.stop		= gpio_wdt_stop,
	.ping		= gpio_wdt_ping,
पूर्ण;

अटल पूर्णांक gpio_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_wdt_priv *priv;
	क्रमागत gpiod_flags gflags;
	अचिन्हित पूर्णांक hw_margin;
	स्थिर अक्षर *algo;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	ret = of_property_पढ़ो_string(np, "hw_algo", &algo);
	अगर (ret)
		वापस ret;
	अगर (!म_भेद(algo, "toggle")) अणु
		priv->hw_algo = HW_ALGO_TOGGLE;
		gflags = GPIOD_IN;
	पूर्ण अन्यथा अगर (!म_भेद(algo, "level")) अणु
		priv->hw_algo = HW_ALGO_LEVEL;
		gflags = GPIOD_OUT_LOW;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	priv->gpiod = devm_gpiod_get(dev, शून्य, gflags);
	अगर (IS_ERR(priv->gpiod))
		वापस PTR_ERR(priv->gpiod);

	ret = of_property_पढ़ो_u32(np,
				   "hw_margin_ms", &hw_margin);
	अगर (ret)
		वापस ret;
	/* Disallow values lower than 2 and higher than 65535 ms */
	अगर (hw_margin < 2 || hw_margin > 65535)
		वापस -EINVAL;

	priv->always_running = of_property_पढ़ो_bool(np,
						     "always-running");

	watchकरोg_set_drvdata(&priv->wdd, priv);

	priv->wdd.info		= &gpio_wdt_ident;
	priv->wdd.ops		= &gpio_wdt_ops;
	priv->wdd.min_समयout	= SOFT_TIMEOUT_MIN;
	priv->wdd.max_hw_heartbeat_ms = hw_margin;
	priv->wdd.parent	= dev;
	priv->wdd.समयout	= SOFT_TIMEOUT_DEF;

	watchकरोg_init_समयout(&priv->wdd, 0, dev);
	watchकरोg_set_nowayout(&priv->wdd, nowayout);

	watchकरोg_stop_on_reboot(&priv->wdd);

	अगर (priv->always_running)
		gpio_wdt_start(&priv->wdd);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &priv->wdd);
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_wdt_dt_ids[] = अणु
	अणु .compatible = "linux,wdt-gpio", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_wdt_dt_ids);

अटल काष्ठा platक्रमm_driver gpio_wdt_driver = अणु
	.driver	= अणु
		.name		= "gpio-wdt",
		.of_match_table	= gpio_wdt_dt_ids,
	पूर्ण,
	.probe	= gpio_wdt_probe,
पूर्ण;

#अगर_घोषित CONFIG_GPIO_WATCHDOG_ARCH_INITCALL
अटल पूर्णांक __init gpio_wdt_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpio_wdt_driver);
पूर्ण
arch_initcall(gpio_wdt_init);
#अन्यथा
module_platक्रमm_driver(gpio_wdt_driver);
#पूर्ण_अगर

MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("GPIO Watchdog");
MODULE_LICENSE("GPL");
