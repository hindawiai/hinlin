<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम Marvell Armada 37xx SoCs
 *
 * Author: Marek Behथजn <kabel@kernel.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

/*
 * There are four counters that can be used क्रम watchकरोg on Armada 37xx.
 * The addresses क्रम counter control रेजिस्टरs are रेजिस्टर base plus ID*0x10,
 * where ID is 0, 1, 2 or 3.
 *
 * In this driver we use IDs 0 and 1. Counter ID 1 is used as watchकरोg counter,
 * जबतक counter ID 0 is used to implement pinging the watchकरोg: counter ID 1 is
 * set to restart counting from initial value on counter ID 0 end count event.
 * Pinging is करोne by क्रमcing immediate end count event on counter ID 0.
 * If only one counter was used, pinging would have to be implemented by
 * disabling and enabling the counter, leaving the प्रणाली in a vulnerable state
 * क्रम a (really) लघु period of समय.
 *
 * Counters ID 2 and 3 are enabled by शेष even beक्रमe U-Boot loads,
 * thereक्रमe this driver करोes not provide a way to use them, eg. by setting a
 * property in device tree.
 */

#घोषणा CNTR_ID_RETRIGGER		0
#घोषणा CNTR_ID_WDOG			1

/* relative to cpu_misc */
#घोषणा WDT_TIMER_SELECT		0x64
#घोषणा WDT_TIMER_SELECT_MASK		0xf
#घोषणा WDT_TIMER_SELECT_VAL		BIT(CNTR_ID_WDOG)

/* relative to reg */
#घोषणा CNTR_CTRL(id)			((id) * 0x10)
#घोषणा CNTR_CTRL_ENABLE		0x0001
#घोषणा CNTR_CTRL_ACTIVE		0x0002
#घोषणा CNTR_CTRL_MODE_MASK		0x000c
#घोषणा CNTR_CTRL_MODE_ONESHOT		0x0000
#घोषणा CNTR_CTRL_MODE_HWSIG		0x000c
#घोषणा CNTR_CTRL_TRIG_SRC_MASK		0x00f0
#घोषणा CNTR_CTRL_TRIG_SRC_PREV_CNTR	0x0050
#घोषणा CNTR_CTRL_PRESCALE_MASK		0xff00
#घोषणा CNTR_CTRL_PRESCALE_MIN		2
#घोषणा CNTR_CTRL_PRESCALE_SHIFT	8

#घोषणा CNTR_COUNT_LOW(id)		(CNTR_CTRL(id) + 0x4)
#घोषणा CNTR_COUNT_HIGH(id)		(CNTR_CTRL(id) + 0x8)

#घोषणा WATCHDOG_TIMEOUT		120

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			   __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा armada_37xx_watchकरोg अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा regmap *cpu_misc;
	व्योम __iomem *reg;
	u64 समयout; /* in घड़ी ticks */
	अचिन्हित दीर्घ clk_rate;
	काष्ठा clk *clk;
पूर्ण;

अटल u64 get_counter_value(काष्ठा armada_37xx_watchकरोg *dev, पूर्णांक id)
अणु
	u64 val;

	/*
	 * when low is पढ़ो, high is latched पूर्णांकo flip-flops so that it can be
	 * पढ़ो consistently without using software debouncing
	 */
	val = पढ़ोl(dev->reg + CNTR_COUNT_LOW(id));
	val |= ((u64)पढ़ोl(dev->reg + CNTR_COUNT_HIGH(id))) << 32;

	वापस val;
पूर्ण

अटल व्योम set_counter_value(काष्ठा armada_37xx_watchकरोg *dev, पूर्णांक id, u64 val)
अणु
	ग_लिखोl(val & 0xffffffff, dev->reg + CNTR_COUNT_LOW(id));
	ग_लिखोl(val >> 32, dev->reg + CNTR_COUNT_HIGH(id));
पूर्ण

अटल व्योम counter_enable(काष्ठा armada_37xx_watchकरोg *dev, पूर्णांक id)
अणु
	u32 reg;

	reg = पढ़ोl(dev->reg + CNTR_CTRL(id));
	reg |= CNTR_CTRL_ENABLE;
	ग_लिखोl(reg, dev->reg + CNTR_CTRL(id));
पूर्ण

अटल व्योम counter_disable(काष्ठा armada_37xx_watchकरोg *dev, पूर्णांक id)
अणु
	u32 reg;

	reg = पढ़ोl(dev->reg + CNTR_CTRL(id));
	reg &= ~CNTR_CTRL_ENABLE;
	ग_लिखोl(reg, dev->reg + CNTR_CTRL(id));
पूर्ण

अटल व्योम init_counter(काष्ठा armada_37xx_watchकरोg *dev, पूर्णांक id, u32 mode,
			 u32 trig_src)
अणु
	u32 reg;

	reg = पढ़ोl(dev->reg + CNTR_CTRL(id));

	reg &= ~(CNTR_CTRL_MODE_MASK | CNTR_CTRL_PRESCALE_MASK |
		 CNTR_CTRL_TRIG_SRC_MASK);

	/* set mode */
	reg |= mode & CNTR_CTRL_MODE_MASK;

	/* set prescaler to the min value */
	reg |= CNTR_CTRL_PRESCALE_MIN << CNTR_CTRL_PRESCALE_SHIFT;

	/* set trigger source */
	reg |= trig_src & CNTR_CTRL_TRIG_SRC_MASK;

	ग_लिखोl(reg, dev->reg + CNTR_CTRL(id));
पूर्ण

अटल पूर्णांक armada_37xx_wdt_ping(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा armada_37xx_watchकरोg *dev = watchकरोg_get_drvdata(wdt);

	/* counter 1 is retriggered by क्रमcing end count on counter 0 */
	counter_disable(dev, CNTR_ID_RETRIGGER);
	counter_enable(dev, CNTR_ID_RETRIGGER);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक armada_37xx_wdt_get_समयleft(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा armada_37xx_watchकरोg *dev = watchकरोg_get_drvdata(wdt);
	u64 res;

	res = get_counter_value(dev, CNTR_ID_WDOG) * CNTR_CTRL_PRESCALE_MIN;
	करो_भाग(res, dev->clk_rate);

	वापस res;
पूर्ण

अटल पूर्णांक armada_37xx_wdt_set_समयout(काष्ठा watchकरोg_device *wdt,
				       अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा armada_37xx_watchकरोg *dev = watchकरोg_get_drvdata(wdt);

	wdt->समयout = समयout;

	/*
	 * Compute the समयout in घड़ी rate. We use smallest possible
	 * prescaler, which भागides the घड़ी rate by 2
	 * (CNTR_CTRL_PRESCALE_MIN).
	 */
	dev->समयout = (u64)dev->clk_rate * समयout;
	करो_भाग(dev->समयout, CNTR_CTRL_PRESCALE_MIN);

	वापस 0;
पूर्ण

अटल bool armada_37xx_wdt_is_running(काष्ठा armada_37xx_watchकरोg *dev)
अणु
	u32 reg;

	regmap_पढ़ो(dev->cpu_misc, WDT_TIMER_SELECT, &reg);
	अगर ((reg & WDT_TIMER_SELECT_MASK) != WDT_TIMER_SELECT_VAL)
		वापस false;

	reg = पढ़ोl(dev->reg + CNTR_CTRL(CNTR_ID_WDOG));
	वापस !!(reg & CNTR_CTRL_ACTIVE);
पूर्ण

अटल पूर्णांक armada_37xx_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा armada_37xx_watchकरोg *dev = watchकरोg_get_drvdata(wdt);

	/* select counter 1 as watchकरोg counter */
	regmap_ग_लिखो(dev->cpu_misc, WDT_TIMER_SELECT, WDT_TIMER_SELECT_VAL);

	/* init counter 0 as retrigger counter क्रम counter 1 */
	init_counter(dev, CNTR_ID_RETRIGGER, CNTR_CTRL_MODE_ONESHOT, 0);
	set_counter_value(dev, CNTR_ID_RETRIGGER, 0);

	/* init counter 1 to be retriggerable by counter 0 end count */
	init_counter(dev, CNTR_ID_WDOG, CNTR_CTRL_MODE_HWSIG,
		     CNTR_CTRL_TRIG_SRC_PREV_CNTR);
	set_counter_value(dev, CNTR_ID_WDOG, dev->समयout);

	/* enable counter 1 */
	counter_enable(dev, CNTR_ID_WDOG);

	/* start counter 1 by क्रमcing immediate end count on counter 0 */
	counter_enable(dev, CNTR_ID_RETRIGGER);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_37xx_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा armada_37xx_watchकरोg *dev = watchकरोg_get_drvdata(wdt);

	counter_disable(dev, CNTR_ID_WDOG);
	counter_disable(dev, CNTR_ID_RETRIGGER);
	regmap_ग_लिखो(dev->cpu_misc, WDT_TIMER_SELECT, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info armada_37xx_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "Armada 37xx Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops armada_37xx_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = armada_37xx_wdt_start,
	.stop = armada_37xx_wdt_stop,
	.ping = armada_37xx_wdt_ping,
	.set_समयout = armada_37xx_wdt_set_समयout,
	.get_समयleft = armada_37xx_wdt_get_समयleft,
पूर्ण;

अटल व्योम armada_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक armada_37xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा armada_37xx_watchकरोg *dev;
	काष्ठा resource *res;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	dev = devm_kzalloc(&pdev->dev, माप(काष्ठा armada_37xx_watchकरोg),
			   GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->wdt.info = &armada_37xx_wdt_info;
	dev->wdt.ops = &armada_37xx_wdt_ops;

	regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						 "marvell,system-controller");
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);
	dev->cpu_misc = regmap;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	dev->reg = devm_ioremap(&pdev->dev, res->start, resource_size(res));

	/* init घड़ी */
	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);

	ret = clk_prepare_enable(dev->clk);
	अगर (ret)
		वापस ret;
	ret = devm_add_action_or_reset(&pdev->dev,
				       armada_clk_disable_unprepare, dev->clk);
	अगर (ret)
		वापस ret;

	dev->clk_rate = clk_get_rate(dev->clk);
	अगर (!dev->clk_rate)
		वापस -EINVAL;

	/*
	 * Since the समयout in seconds is given as 32 bit अचिन्हित पूर्णांक, and
	 * the counters hold 64 bit values, even after multiplication by घड़ी
	 * rate the counter can hold समयout of अच_पूर्णांक_उच्च seconds.
	 */
	dev->wdt.min_समयout = 1;
	dev->wdt.max_समयout = अच_पूर्णांक_उच्च;
	dev->wdt.parent = &pdev->dev;

	/* शेष value, possibly override by module parameter or dtb */
	dev->wdt.समयout = WATCHDOG_TIMEOUT;
	watchकरोg_init_समयout(&dev->wdt, समयout, &pdev->dev);

	platक्रमm_set_drvdata(pdev, &dev->wdt);
	watchकरोg_set_drvdata(&dev->wdt, dev);

	armada_37xx_wdt_set_समयout(&dev->wdt, dev->wdt.समयout);

	अगर (armada_37xx_wdt_is_running(dev))
		set_bit(WDOG_HW_RUNNING, &dev->wdt.status);

	watchकरोg_set_nowayout(&dev->wdt, nowayout);
	watchकरोg_stop_on_reboot(&dev->wdt);
	ret = devm_watchकरोg_रेजिस्टर_device(&pdev->dev, &dev->wdt);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev, "Initial timeout %d sec%s\n",
		 dev->wdt.समयout, nowayout ? ", nowayout" : "");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused armada_37xx_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wdt = dev_get_drvdata(dev);

	वापस armada_37xx_wdt_stop(wdt);
पूर्ण

अटल पूर्णांक __maybe_unused armada_37xx_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(wdt))
		वापस armada_37xx_wdt_start(wdt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops armada_37xx_wdt_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(armada_37xx_wdt_suspend,
				armada_37xx_wdt_resume)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id armada_37xx_wdt_match[] = अणु
	अणु .compatible = "marvell,armada-3700-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, armada_37xx_wdt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver armada_37xx_wdt_driver = अणु
	.probe		= armada_37xx_wdt_probe,
	.driver		= अणु
		.name	= "armada_37xx_wdt",
		.of_match_table = of_match_ptr(armada_37xx_wdt_match),
		.pm = &armada_37xx_wdt_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(armada_37xx_wdt_driver);

MODULE_AUTHOR("Marek Behun <kabel@kernel.org>");
MODULE_DESCRIPTION("Armada 37xx CPU Watchdog");

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:armada_37xx_wdt");
