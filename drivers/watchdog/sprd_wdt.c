<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Spपढ़ोtrum watchकरोg driver
 * Copyright (C) 2017 Spपढ़ोtrum - http://www.spपढ़ोtrum.com
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा SPRD_WDT_LOAD_LOW		0x0
#घोषणा SPRD_WDT_LOAD_HIGH		0x4
#घोषणा SPRD_WDT_CTRL			0x8
#घोषणा SPRD_WDT_INT_CLR		0xc
#घोषणा SPRD_WDT_INT_RAW		0x10
#घोषणा SPRD_WDT_INT_MSK		0x14
#घोषणा SPRD_WDT_CNT_LOW		0x18
#घोषणा SPRD_WDT_CNT_HIGH		0x1c
#घोषणा SPRD_WDT_LOCK			0x20
#घोषणा SPRD_WDT_IRQ_LOAD_LOW		0x2c
#घोषणा SPRD_WDT_IRQ_LOAD_HIGH		0x30

/* WDT_CTRL */
#घोषणा SPRD_WDT_INT_EN_BIT		BIT(0)
#घोषणा SPRD_WDT_CNT_EN_BIT		BIT(1)
#घोषणा SPRD_WDT_NEW_VER_EN		BIT(2)
#घोषणा SPRD_WDT_RST_EN_BIT		BIT(3)

/* WDT_INT_CLR */
#घोषणा SPRD_WDT_INT_CLEAR_BIT		BIT(0)
#घोषणा SPRD_WDT_RST_CLEAR_BIT		BIT(3)

/* WDT_INT_RAW */
#घोषणा SPRD_WDT_INT_RAW_BIT		BIT(0)
#घोषणा SPRD_WDT_RST_RAW_BIT		BIT(3)
#घोषणा SPRD_WDT_LD_BUSY_BIT		BIT(4)

/* 1s equal to 32768 counter steps */
#घोषणा SPRD_WDT_CNT_STEP		32768

#घोषणा SPRD_WDT_UNLOCK_KEY		0xe551
#घोषणा SPRD_WDT_MIN_TIMEOUT		3
#घोषणा SPRD_WDT_MAX_TIMEOUT		60

#घोषणा SPRD_WDT_CNT_HIGH_SHIFT		16
#घोषणा SPRD_WDT_LOW_VALUE_MASK		GENMASK(15, 0)
#घोषणा SPRD_WDT_LOAD_TIMEOUT		11

काष्ठा sprd_wdt अणु
	व्योम __iomem *base;
	काष्ठा watchकरोg_device wdd;
	काष्ठा clk *enable;
	काष्ठा clk *rtc_enable;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत काष्ठा sprd_wdt *to_sprd_wdt(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा sprd_wdt, wdd);
पूर्ण

अटल अंतरभूत व्योम sprd_wdt_lock(व्योम __iomem *addr)
अणु
	ग_लिखोl_relaxed(0x0, addr + SPRD_WDT_LOCK);
पूर्ण

अटल अंतरभूत व्योम sprd_wdt_unlock(व्योम __iomem *addr)
अणु
	ग_लिखोl_relaxed(SPRD_WDT_UNLOCK_KEY, addr + SPRD_WDT_LOCK);
पूर्ण

अटल irqवापस_t sprd_wdt_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sprd_wdt *wdt = (काष्ठा sprd_wdt *)dev_id;

	sprd_wdt_unlock(wdt->base);
	ग_लिखोl_relaxed(SPRD_WDT_INT_CLEAR_BIT, wdt->base + SPRD_WDT_INT_CLR);
	sprd_wdt_lock(wdt->base);
	watchकरोg_notअगरy_preसमयout(&wdt->wdd);
	वापस IRQ_HANDLED;
पूर्ण

अटल u32 sprd_wdt_get_cnt_value(काष्ठा sprd_wdt *wdt)
अणु
	u32 val;

	val = पढ़ोl_relaxed(wdt->base + SPRD_WDT_CNT_HIGH) <<
		SPRD_WDT_CNT_HIGH_SHIFT;
	val |= पढ़ोl_relaxed(wdt->base + SPRD_WDT_CNT_LOW) &
		SPRD_WDT_LOW_VALUE_MASK;

	वापस val;
पूर्ण

अटल पूर्णांक sprd_wdt_load_value(काष्ठा sprd_wdt *wdt, u32 समयout,
			       u32 preसमयout)
अणु
	u32 val, delay_cnt = 0;
	u32 पंचांगr_step = समयout * SPRD_WDT_CNT_STEP;
	u32 prपंचांगr_step = preसमयout * SPRD_WDT_CNT_STEP;

	/*
	 * Checking busy bit to make sure the previous loading operation is
	 * करोne. According to the specअगरication, the busy bit would be set
	 * after a new loading operation and last 2 or 3 RTC घड़ी
	 * cycles (about 60us~92us).
	 */
	करो अणु
		val = पढ़ोl_relaxed(wdt->base + SPRD_WDT_INT_RAW);
		अगर (!(val & SPRD_WDT_LD_BUSY_BIT))
			अवरोध;

		usleep_range(10, 100);
	पूर्ण जबतक (delay_cnt++ < SPRD_WDT_LOAD_TIMEOUT);

	अगर (delay_cnt >= SPRD_WDT_LOAD_TIMEOUT)
		वापस -EBUSY;

	sprd_wdt_unlock(wdt->base);
	ग_लिखोl_relaxed((पंचांगr_step >> SPRD_WDT_CNT_HIGH_SHIFT) &
		      SPRD_WDT_LOW_VALUE_MASK, wdt->base + SPRD_WDT_LOAD_HIGH);
	ग_लिखोl_relaxed((पंचांगr_step & SPRD_WDT_LOW_VALUE_MASK),
		       wdt->base + SPRD_WDT_LOAD_LOW);
	ग_लिखोl_relaxed((prपंचांगr_step >> SPRD_WDT_CNT_HIGH_SHIFT) &
			SPRD_WDT_LOW_VALUE_MASK,
		       wdt->base + SPRD_WDT_IRQ_LOAD_HIGH);
	ग_लिखोl_relaxed(prपंचांगr_step & SPRD_WDT_LOW_VALUE_MASK,
		       wdt->base + SPRD_WDT_IRQ_LOAD_LOW);
	sprd_wdt_lock(wdt->base);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_wdt_enable(काष्ठा sprd_wdt *wdt)
अणु
	u32 val;
	पूर्णांक ret;

	ret = clk_prepare_enable(wdt->enable);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(wdt->rtc_enable);
	अगर (ret) अणु
		clk_disable_unprepare(wdt->enable);
		वापस ret;
	पूर्ण

	sprd_wdt_unlock(wdt->base);
	val = पढ़ोl_relaxed(wdt->base + SPRD_WDT_CTRL);
	val |= SPRD_WDT_NEW_VER_EN;
	ग_लिखोl_relaxed(val, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);
	वापस 0;
पूर्ण

अटल व्योम sprd_wdt_disable(व्योम *_data)
अणु
	काष्ठा sprd_wdt *wdt = _data;

	sprd_wdt_unlock(wdt->base);
	ग_लिखोl_relaxed(0x0, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);

	clk_disable_unprepare(wdt->rtc_enable);
	clk_disable_unprepare(wdt->enable);
पूर्ण

अटल पूर्णांक sprd_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sprd_wdt *wdt = to_sprd_wdt(wdd);
	u32 val;
	पूर्णांक ret;

	ret = sprd_wdt_load_value(wdt, wdd->समयout, wdd->preसमयout);
	अगर (ret)
		वापस ret;

	sprd_wdt_unlock(wdt->base);
	val = पढ़ोl_relaxed(wdt->base + SPRD_WDT_CTRL);
	val |= SPRD_WDT_CNT_EN_BIT | SPRD_WDT_INT_EN_BIT | SPRD_WDT_RST_EN_BIT;
	ग_लिखोl_relaxed(val, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);
	set_bit(WDOG_HW_RUNNING, &wdd->status);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sprd_wdt *wdt = to_sprd_wdt(wdd);
	u32 val;

	sprd_wdt_unlock(wdt->base);
	val = पढ़ोl_relaxed(wdt->base + SPRD_WDT_CTRL);
	val &= ~(SPRD_WDT_CNT_EN_BIT | SPRD_WDT_RST_EN_BIT |
		SPRD_WDT_INT_EN_BIT);
	ग_लिखोl_relaxed(val, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);
	वापस 0;
पूर्ण

अटल पूर्णांक sprd_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				u32 समयout)
अणु
	काष्ठा sprd_wdt *wdt = to_sprd_wdt(wdd);

	अगर (समयout == wdd->समयout)
		वापस 0;

	wdd->समयout = समयout;

	वापस sprd_wdt_load_value(wdt, समयout, wdd->preसमयout);
पूर्ण

अटल पूर्णांक sprd_wdt_set_preसमयout(काष्ठा watchकरोg_device *wdd,
				   u32 new_preसमयout)
अणु
	काष्ठा sprd_wdt *wdt = to_sprd_wdt(wdd);

	अगर (new_preसमयout < wdd->min_समयout)
		वापस -EINVAL;

	wdd->preसमयout = new_preसमयout;

	वापस sprd_wdt_load_value(wdt, wdd->समयout, new_preसमयout);
पूर्ण

अटल u32 sprd_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sprd_wdt *wdt = to_sprd_wdt(wdd);
	u32 val;

	val = sprd_wdt_get_cnt_value(wdt);
	वापस val / SPRD_WDT_CNT_STEP;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops sprd_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = sprd_wdt_start,
	.stop = sprd_wdt_stop,
	.set_समयout = sprd_wdt_set_समयout,
	.set_preसमयout = sprd_wdt_set_preसमयout,
	.get_समयleft = sprd_wdt_get_समयleft,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info sprd_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT |
		   WDIOF_PRETIMEOUT |
		   WDIOF_MAGICCLOSE |
		   WDIOF_KEEPALIVEPING,
	.identity = "Spreadtrum Watchdog Timer",
पूर्ण;

अटल पूर्णांक sprd_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sprd_wdt *wdt;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	wdt->enable = devm_clk_get(dev, "enable");
	अगर (IS_ERR(wdt->enable)) अणु
		dev_err(dev, "can't get the enable clock\n");
		वापस PTR_ERR(wdt->enable);
	पूर्ण

	wdt->rtc_enable = devm_clk_get(dev, "rtc_enable");
	अगर (IS_ERR(wdt->rtc_enable)) अणु
		dev_err(dev, "can't get the rtc enable clock\n");
		वापस PTR_ERR(wdt->rtc_enable);
	पूर्ण

	wdt->irq = platक्रमm_get_irq(pdev, 0);
	अगर (wdt->irq < 0)
		वापस wdt->irq;

	ret = devm_request_irq(dev, wdt->irq, sprd_wdt_isr, IRQF_NO_SUSPEND,
			       "sprd-wdt", (व्योम *)wdt);
	अगर (ret) अणु
		dev_err(dev, "failed to register irq\n");
		वापस ret;
	पूर्ण

	wdt->wdd.info = &sprd_wdt_info;
	wdt->wdd.ops = &sprd_wdt_ops;
	wdt->wdd.parent = dev;
	wdt->wdd.min_समयout = SPRD_WDT_MIN_TIMEOUT;
	wdt->wdd.max_समयout = SPRD_WDT_MAX_TIMEOUT;
	wdt->wdd.समयout = SPRD_WDT_MAX_TIMEOUT;

	ret = sprd_wdt_enable(wdt);
	अगर (ret) अणु
		dev_err(dev, "failed to enable wdt\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, sprd_wdt_disable, wdt);
	अगर (ret) अणु
		dev_err(dev, "Failed to add wdt disable action\n");
		वापस ret;
	पूर्ण

	watchकरोg_set_nowayout(&wdt->wdd, WATCHDOG_NOWAYOUT);
	watchकरोg_init_समयout(&wdt->wdd, 0, dev);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
	अगर (ret) अणु
		sprd_wdt_disable(wdt);
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, wdt);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_wdt_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sprd_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		sprd_wdt_stop(&wdt->wdd);
	sprd_wdt_disable(wdt);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_wdt_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा sprd_wdt *wdt = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sprd_wdt_enable(wdt);
	अगर (ret)
		वापस ret;

	अगर (watchकरोg_active(&wdt->wdd))
		ret = sprd_wdt_start(&wdt->wdd);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sprd_wdt_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sprd_wdt_pm_suspend,
				sprd_wdt_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sprd_wdt_match_table[] = अणु
	अणु .compatible = "sprd,sp9860-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_wdt_match_table);

अटल काष्ठा platक्रमm_driver sprd_watchकरोg_driver = अणु
	.probe	= sprd_wdt_probe,
	.driver	= अणु
		.name = "sprd-wdt",
		.of_match_table = sprd_wdt_match_table,
		.pm = &sprd_wdt_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sprd_watchकरोg_driver);

MODULE_AUTHOR("Eric Long <eric.long@spreadtrum.com>");
MODULE_DESCRIPTION("Spreadtrum Watchdog Timer Controller Driver");
MODULE_LICENSE("GPL v2");
