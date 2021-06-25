<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 *  Copyright (C) 2017 Hauke Mehrtens <hauke@hauke-m.de>
 *  Based on EP93xx wdt driver
 */

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <lantiq_soc.h>

#घोषणा LTQ_XRX_RCU_RST_STAT		0x0014
#घोषणा LTQ_XRX_RCU_RST_STAT_WDT	BIT(31)

/* CPU0 Reset Source Register */
#घोषणा LTQ_FALCON_SYS1_CPU0RS		0x0060
/* reset cause mask */
#घोषणा LTQ_FALCON_SYS1_CPU0RS_MASK	0x0007
#घोषणा LTQ_FALCON_SYS1_CPU0RS_WDT	0x02

/*
 * Section 3.4 of the datasheet
 * The password sequence protects the WDT control रेजिस्टर from unपूर्णांकended
 * ग_लिखो actions, which might cause malfunction of the WDT.
 *
 * essentially the following two magic passwords need to be written to allow
 * IO access to the WDT core
 */
#घोषणा LTQ_WDT_CR_PW1		0x00BE0000
#घोषणा LTQ_WDT_CR_PW2		0x00DC0000

#घोषणा LTQ_WDT_CR		0x0		/* watchकरोg control रेजिस्टर */
#घोषणा  LTQ_WDT_CR_GEN		BIT(31)		/* enable bit */
/* Pre-warning limit set to 1/16 of max WDT period */
#घोषणा  LTQ_WDT_CR_PWL		(0x3 << 26)
/* set घड़ी भागider to 0x40000 */
#घोषणा  LTQ_WDT_CR_CLKDIV	(0x3 << 24)
#घोषणा  LTQ_WDT_CR_PW_MASK	GENMASK(23, 16)	/* Password field */
#घोषणा  LTQ_WDT_CR_MAX_TIMEOUT	((1 << 16) - 1)	/* The reload field is 16 bit */
#घोषणा LTQ_WDT_SR		0x8		/* watchकरोg status रेजिस्टर */
#घोषणा  LTQ_WDT_SR_EN		BIT(31)		/* Enable */
#घोषणा  LTQ_WDT_SR_VALUE_MASK	GENMASK(15, 0)	/* Timer value */

#घोषणा LTQ_WDT_DIVIDER		0x40000

अटल bool nowayout = WATCHDOG_NOWAYOUT;

काष्ठा ltq_wdt_hw अणु
	पूर्णांक (*bootstatus_get)(काष्ठा device *dev);
पूर्ण;

काष्ठा ltq_wdt_priv अणु
	काष्ठा watchकरोg_device wdt;
	व्योम __iomem *membase;
	अचिन्हित दीर्घ clk_rate;
पूर्ण;

अटल u32 ltq_wdt_r32(काष्ठा ltq_wdt_priv *priv, u32 offset)
अणु
	वापस __raw_पढ़ोl(priv->membase + offset);
पूर्ण

अटल व्योम ltq_wdt_w32(काष्ठा ltq_wdt_priv *priv, u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, priv->membase + offset);
पूर्ण

अटल व्योम ltq_wdt_mask(काष्ठा ltq_wdt_priv *priv, u32 clear, u32 set,
			 u32 offset)
अणु
	u32 val = ltq_wdt_r32(priv, offset);

	val &= ~(clear);
	val |= set;
	ltq_wdt_w32(priv, val, offset);
पूर्ण

अटल काष्ठा ltq_wdt_priv *ltq_wdt_get_priv(काष्ठा watchकरोg_device *wdt)
अणु
	वापस container_of(wdt, काष्ठा ltq_wdt_priv, wdt);
पूर्ण

अटल काष्ठा watchकरोg_info ltq_wdt_info = अणु
	.options = WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
		   WDIOF_CARDRESET,
	.identity = "ltq_wdt",
पूर्ण;

अटल पूर्णांक ltq_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);
	u32 समयout;

	समयout = wdt->समयout * priv->clk_rate;

	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK, LTQ_WDT_CR_PW1, LTQ_WDT_CR);
	/* ग_लिखो the second magic plus the configuration and new समयout */
	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK | LTQ_WDT_CR_MAX_TIMEOUT,
		     LTQ_WDT_CR_GEN | LTQ_WDT_CR_PWL | LTQ_WDT_CR_CLKDIV |
		     LTQ_WDT_CR_PW2 | समयout,
		     LTQ_WDT_CR);

	वापस 0;
पूर्ण

अटल पूर्णांक ltq_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);

	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK, LTQ_WDT_CR_PW1, LTQ_WDT_CR);
	ltq_wdt_mask(priv, LTQ_WDT_CR_GEN | LTQ_WDT_CR_PW_MASK,
		     LTQ_WDT_CR_PW2, LTQ_WDT_CR);

	वापस 0;
पूर्ण

अटल पूर्णांक ltq_wdt_ping(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);
	u32 समयout;

	समयout = wdt->समयout * priv->clk_rate;

	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK, LTQ_WDT_CR_PW1, LTQ_WDT_CR);
	/* ग_लिखो the second magic plus the configuration and new समयout */
	ltq_wdt_mask(priv, LTQ_WDT_CR_PW_MASK | LTQ_WDT_CR_MAX_TIMEOUT,
		     LTQ_WDT_CR_PW2 | समयout, LTQ_WDT_CR);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ltq_wdt_get_समयleft(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा ltq_wdt_priv *priv = ltq_wdt_get_priv(wdt);
	u64 समयout;

	समयout = ltq_wdt_r32(priv, LTQ_WDT_SR) & LTQ_WDT_SR_VALUE_MASK;
	वापस करो_भाग(समयout, priv->clk_rate);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops ltq_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= ltq_wdt_start,
	.stop		= ltq_wdt_stop,
	.ping		= ltq_wdt_ping,
	.get_समयleft	= ltq_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक ltq_wdt_xrx_bootstatus_get(काष्ठा device *dev)
अणु
	काष्ठा regmap *rcu_regmap;
	u32 val;
	पूर्णांक err;

	rcu_regmap = syscon_regmap_lookup_by_phandle(dev->of_node, "regmap");
	अगर (IS_ERR(rcu_regmap))
		वापस PTR_ERR(rcu_regmap);

	err = regmap_पढ़ो(rcu_regmap, LTQ_XRX_RCU_RST_STAT, &val);
	अगर (err)
		वापस err;

	अगर (val & LTQ_XRX_RCU_RST_STAT_WDT)
		वापस WDIOF_CARDRESET;

	वापस 0;
पूर्ण

अटल पूर्णांक ltq_wdt_falcon_bootstatus_get(काष्ठा device *dev)
अणु
	काष्ठा regmap *rcu_regmap;
	u32 val;
	पूर्णांक err;

	rcu_regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
						     "lantiq,rcu");
	अगर (IS_ERR(rcu_regmap))
		वापस PTR_ERR(rcu_regmap);

	err = regmap_पढ़ो(rcu_regmap, LTQ_FALCON_SYS1_CPU0RS, &val);
	अगर (err)
		वापस err;

	अगर ((val & LTQ_FALCON_SYS1_CPU0RS_MASK) == LTQ_FALCON_SYS1_CPU0RS_WDT)
		वापस WDIOF_CARDRESET;

	वापस 0;
पूर्ण

अटल पूर्णांक ltq_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ltq_wdt_priv *priv;
	काष्ठा watchकरोg_device *wdt;
	काष्ठा clk *clk;
	स्थिर काष्ठा ltq_wdt_hw *ltq_wdt_hw;
	पूर्णांक ret;
	u32 status;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->membase))
		वापस PTR_ERR(priv->membase);

	/* we करो not need to enable the घड़ी as it is always running */
	clk = clk_get_io();
	priv->clk_rate = clk_get_rate(clk) / LTQ_WDT_DIVIDER;
	अगर (!priv->clk_rate) अणु
		dev_err(dev, "clock rate less than divider %i\n",
			LTQ_WDT_DIVIDER);
		वापस -EINVAL;
	पूर्ण

	wdt = &priv->wdt;
	wdt->info		= &ltq_wdt_info;
	wdt->ops		= &ltq_wdt_ops;
	wdt->min_समयout	= 1;
	wdt->max_समयout	= LTQ_WDT_CR_MAX_TIMEOUT / priv->clk_rate;
	wdt->समयout		= wdt->max_समयout;
	wdt->parent		= dev;

	ltq_wdt_hw = of_device_get_match_data(dev);
	अगर (ltq_wdt_hw && ltq_wdt_hw->bootstatus_get) अणु
		ret = ltq_wdt_hw->bootstatus_get(dev);
		अगर (ret >= 0)
			wdt->bootstatus = ret;
	पूर्ण

	watchकरोg_set_nowayout(wdt, nowayout);
	watchकरोg_init_समयout(wdt, 0, dev);

	status = ltq_wdt_r32(priv, LTQ_WDT_SR);
	अगर (status & LTQ_WDT_SR_EN) अणु
		/*
		 * If the watchकरोg is alपढ़ोy running overग_लिखो it with our
		 * new settings. Stop is not needed as the start call will
		 * replace all settings anyway.
		 */
		ltq_wdt_start(wdt);
		set_bit(WDOG_HW_RUNNING, &wdt->status);
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdt);
पूर्ण

अटल स्थिर काष्ठा ltq_wdt_hw ltq_wdt_xrx100 = अणु
	.bootstatus_get = ltq_wdt_xrx_bootstatus_get,
पूर्ण;

अटल स्थिर काष्ठा ltq_wdt_hw ltq_wdt_falcon = अणु
	.bootstatus_get = ltq_wdt_falcon_bootstatus_get,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ltq_wdt_match[] = अणु
	अणु .compatible = "lantiq,wdt", .data = शून्य पूर्ण,
	अणु .compatible = "lantiq,xrx100-wdt", .data = &ltq_wdt_xrx100 पूर्ण,
	अणु .compatible = "lantiq,falcon-wdt", .data = &ltq_wdt_falcon पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_wdt_match);

अटल काष्ठा platक्रमm_driver ltq_wdt_driver = अणु
	.probe = ltq_wdt_probe,
	.driver = अणु
		.name = "wdt",
		.of_match_table = ltq_wdt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ltq_wdt_driver);

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started");
MODULE_AUTHOR("John Crispin <john@phrozen.org>");
MODULE_DESCRIPTION("Lantiq SoC Watchdog");
MODULE_LICENSE("GPL");
