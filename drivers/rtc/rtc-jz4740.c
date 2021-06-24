<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>
 *  Copyright (C) 2010, Paul Cercueil <paul@crapouillou.net>
 *	 JZ4740 SoC RTC driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/reboot.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा JZ_REG_RTC_CTRL		0x00
#घोषणा JZ_REG_RTC_SEC		0x04
#घोषणा JZ_REG_RTC_SEC_ALARM	0x08
#घोषणा JZ_REG_RTC_REGULATOR	0x0C
#घोषणा JZ_REG_RTC_HIBERNATE	0x20
#घोषणा JZ_REG_RTC_WAKEUP_FILTER	0x24
#घोषणा JZ_REG_RTC_RESET_COUNTER	0x28
#घोषणा JZ_REG_RTC_SCRATCHPAD	0x34

/* The following are present on the jz4780 */
#घोषणा JZ_REG_RTC_WENR	0x3C
#घोषणा JZ_RTC_WENR_WEN	BIT(31)

#घोषणा JZ_RTC_CTRL_WRDY	BIT(7)
#घोषणा JZ_RTC_CTRL_1HZ		BIT(6)
#घोषणा JZ_RTC_CTRL_1HZ_IRQ	BIT(5)
#घोषणा JZ_RTC_CTRL_AF		BIT(4)
#घोषणा JZ_RTC_CTRL_AF_IRQ	BIT(3)
#घोषणा JZ_RTC_CTRL_AE		BIT(2)
#घोषणा JZ_RTC_CTRL_ENABLE	BIT(0)

/* Magic value to enable ग_लिखोs on jz4780 */
#घोषणा JZ_RTC_WENR_MAGIC	0xA55A

#घोषणा JZ_RTC_WAKEUP_FILTER_MASK	0x0000FFE0
#घोषणा JZ_RTC_RESET_COUNTER_MASK	0x00000FE0

क्रमागत jz4740_rtc_type अणु
	ID_JZ4740,
	ID_JZ4760,
	ID_JZ4780,
पूर्ण;

काष्ठा jz4740_rtc अणु
	व्योम __iomem *base;
	क्रमागत jz4740_rtc_type type;

	काष्ठा rtc_device *rtc;

	spinlock_t lock;
पूर्ण;

अटल काष्ठा device *dev_क्रम_घातer_off;

अटल अंतरभूत uपूर्णांक32_t jz4740_rtc_reg_पढ़ो(काष्ठा jz4740_rtc *rtc, माप_प्रकार reg)
अणु
	वापस पढ़ोl(rtc->base + reg);
पूर्ण

अटल पूर्णांक jz4740_rtc_रुको_ग_लिखो_पढ़ोy(काष्ठा jz4740_rtc *rtc)
अणु
	uपूर्णांक32_t ctrl;
	पूर्णांक समयout = 10000;

	करो अणु
		ctrl = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_CTRL);
	पूर्ण जबतक (!(ctrl & JZ_RTC_CTRL_WRDY) && --समयout);

	वापस समयout ? 0 : -EIO;
पूर्ण

अटल अंतरभूत पूर्णांक jz4780_rtc_enable_ग_लिखो(काष्ठा jz4740_rtc *rtc)
अणु
	uपूर्णांक32_t ctrl;
	पूर्णांक ret, समयout = 10000;

	ret = jz4740_rtc_रुको_ग_लिखो_पढ़ोy(rtc);
	अगर (ret != 0)
		वापस ret;

	ग_लिखोl(JZ_RTC_WENR_MAGIC, rtc->base + JZ_REG_RTC_WENR);

	करो अणु
		ctrl = पढ़ोl(rtc->base + JZ_REG_RTC_WENR);
	पूर्ण जबतक (!(ctrl & JZ_RTC_WENR_WEN) && --समयout);

	वापस समयout ? 0 : -EIO;
पूर्ण

अटल अंतरभूत पूर्णांक jz4740_rtc_reg_ग_लिखो(काष्ठा jz4740_rtc *rtc, माप_प्रकार reg,
	uपूर्णांक32_t val)
अणु
	पूर्णांक ret = 0;

	अगर (rtc->type >= ID_JZ4760)
		ret = jz4780_rtc_enable_ग_लिखो(rtc);
	अगर (ret == 0)
		ret = jz4740_rtc_रुको_ग_लिखो_पढ़ोy(rtc);
	अगर (ret == 0)
		ग_लिखोl(val, rtc->base + reg);

	वापस ret;
पूर्ण

अटल पूर्णांक jz4740_rtc_ctrl_set_bits(काष्ठा jz4740_rtc *rtc, uपूर्णांक32_t mask,
	bool set)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t ctrl;

	spin_lock_irqsave(&rtc->lock, flags);

	ctrl = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_CTRL);

	/* Don't clear पूर्णांकerrupt flags by accident */
	ctrl |= JZ_RTC_CTRL_1HZ | JZ_RTC_CTRL_AF;

	अगर (set)
		ctrl |= mask;
	अन्यथा
		ctrl &= ~mask;

	ret = jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_CTRL, ctrl);

	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक jz4740_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा jz4740_rtc *rtc = dev_get_drvdata(dev);
	uपूर्णांक32_t secs, secs2;
	पूर्णांक समयout = 5;

	अगर (jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_SCRATCHPAD) != 0x12345678)
		वापस -EINVAL;

	/* If the seconds रेजिस्टर is पढ़ो जबतक it is updated, it can contain a
	 * bogus value. This can be aव्योमed by making sure that two consecutive
	 * पढ़ोs have the same value.
	 */
	secs = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_SEC);
	secs2 = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_SEC);

	जबतक (secs != secs2 && --समयout) अणु
		secs = secs2;
		secs2 = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_SEC);
	पूर्ण

	अगर (समयout == 0)
		वापस -EIO;

	rtc_समय64_to_पंचांग(secs, समय);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा jz4740_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_SEC, rtc_पंचांग_to_समय64(समय));
	अगर (ret)
		वापस ret;

	वापस jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_SCRATCHPAD, 0x12345678);
पूर्ण

अटल पूर्णांक jz4740_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा jz4740_rtc *rtc = dev_get_drvdata(dev);
	uपूर्णांक32_t secs;
	uपूर्णांक32_t ctrl;

	secs = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_SEC_ALARM);

	ctrl = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_CTRL);

	alrm->enabled = !!(ctrl & JZ_RTC_CTRL_AE);
	alrm->pending = !!(ctrl & JZ_RTC_CTRL_AF);

	rtc_समय64_to_पंचांग(secs, &alrm->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	पूर्णांक ret;
	काष्ठा jz4740_rtc *rtc = dev_get_drvdata(dev);
	uपूर्णांक32_t secs = lower_32_bits(rtc_पंचांग_to_समय64(&alrm->समय));

	ret = jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_SEC_ALARM, secs);
	अगर (!ret)
		ret = jz4740_rtc_ctrl_set_bits(rtc,
			JZ_RTC_CTRL_AE | JZ_RTC_CTRL_AF_IRQ, alrm->enabled);

	वापस ret;
पूर्ण

अटल पूर्णांक jz4740_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा jz4740_rtc *rtc = dev_get_drvdata(dev);
	वापस jz4740_rtc_ctrl_set_bits(rtc, JZ_RTC_CTRL_AF_IRQ, enable);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops jz4740_rtc_ops = अणु
	.पढ़ो_समय	= jz4740_rtc_पढ़ो_समय,
	.set_समय	= jz4740_rtc_set_समय,
	.पढ़ो_alarm	= jz4740_rtc_पढ़ो_alarm,
	.set_alarm	= jz4740_rtc_set_alarm,
	.alarm_irq_enable = jz4740_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t jz4740_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा jz4740_rtc *rtc = data;
	uपूर्णांक32_t ctrl;
	अचिन्हित दीर्घ events = 0;

	ctrl = jz4740_rtc_reg_पढ़ो(rtc, JZ_REG_RTC_CTRL);

	अगर (ctrl & JZ_RTC_CTRL_1HZ)
		events |= (RTC_UF | RTC_IRQF);

	अगर (ctrl & JZ_RTC_CTRL_AF)
		events |= (RTC_AF | RTC_IRQF);

	rtc_update_irq(rtc->rtc, 1, events);

	jz4740_rtc_ctrl_set_bits(rtc, JZ_RTC_CTRL_1HZ | JZ_RTC_CTRL_AF, false);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम jz4740_rtc_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा jz4740_rtc *rtc = dev_get_drvdata(dev);
	jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_HIBERNATE, 1);
पूर्ण

अटल व्योम jz4740_rtc_घातer_off(व्योम)
अणु
	jz4740_rtc_घातeroff(dev_क्रम_घातer_off);
	kernel_halt();
पूर्ण

अटल व्योम jz4740_rtc_clk_disable(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4740_rtc_of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-rtc", .data = (व्योम *)ID_JZ4740 पूर्ण,
	अणु .compatible = "ingenic,jz4760-rtc", .data = (व्योम *)ID_JZ4760 पूर्ण,
	अणु .compatible = "ingenic,jz4780-rtc", .data = (व्योम *)ID_JZ4780 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_rtc_of_match);

अटल व्योम jz4740_rtc_set_wakeup_params(काष्ठा jz4740_rtc *rtc,
					 काष्ठा device_node *np,
					 अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ wakeup_ticks, reset_ticks;
	अचिन्हित पूर्णांक min_wakeup_pin_निश्चित_समय = 60; /* Default: 60ms */
	अचिन्हित पूर्णांक reset_pin_निश्चित_समय = 100; /* Default: 100ms */

	of_property_पढ़ो_u32(np, "ingenic,reset-pin-assert-time-ms",
			     &reset_pin_निश्चित_समय);
	of_property_पढ़ो_u32(np, "ingenic,min-wakeup-pin-assert-time-ms",
			     &min_wakeup_pin_निश्चित_समय);

	/*
	 * Set minimum wakeup pin निश्चितion समय: 100 ms.
	 * Range is 0 to 2 sec अगर RTC is घड़ीed at 32 kHz.
	 */
	wakeup_ticks = (min_wakeup_pin_निश्चित_समय * rate) / 1000;
	अगर (wakeup_ticks < JZ_RTC_WAKEUP_FILTER_MASK)
		wakeup_ticks &= JZ_RTC_WAKEUP_FILTER_MASK;
	अन्यथा
		wakeup_ticks = JZ_RTC_WAKEUP_FILTER_MASK;
	jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_WAKEUP_FILTER, wakeup_ticks);

	/*
	 * Set reset pin low-level निश्चितion समय after wakeup: 60 ms.
	 * Range is 0 to 125 ms अगर RTC is घड़ीed at 32 kHz.
	 */
	reset_ticks = (reset_pin_निश्चित_समय * rate) / 1000;
	अगर (reset_ticks < JZ_RTC_RESET_COUNTER_MASK)
		reset_ticks &= JZ_RTC_RESET_COUNTER_MASK;
	अन्यथा
		reset_ticks = JZ_RTC_RESET_COUNTER_MASK;
	jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_RESET_COUNTER, reset_ticks);
पूर्ण

अटल पूर्णांक jz4740_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा jz4740_rtc *rtc;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret, irq;

	rtc = devm_kzalloc(dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->type = (क्रमागत jz4740_rtc_type)device_get_match_data(dev);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->base))
		वापस PTR_ERR(rtc->base);

	clk = devm_clk_get(dev, "rtc");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "Failed to get RTC clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, jz4740_rtc_clk_disable, clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to register devm action\n");
		वापस ret;
	पूर्ण

	spin_lock_init(&rtc->lock);

	platक्रमm_set_drvdata(pdev, rtc);

	device_init_wakeup(dev, 1);

	ret = dev_pm_set_wake_irq(dev, irq);
	अगर (ret) अणु
		dev_err(dev, "Failed to set wake irq: %d\n", ret);
		वापस ret;
	पूर्ण

	rtc->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rtc->rtc)) अणु
		ret = PTR_ERR(rtc->rtc);
		dev_err(dev, "Failed to allocate rtc device: %d\n", ret);
		वापस ret;
	पूर्ण

	rtc->rtc->ops = &jz4740_rtc_ops;
	rtc->rtc->range_max = U32_MAX;

	rate = clk_get_rate(clk);
	jz4740_rtc_set_wakeup_params(rtc, np, rate);

	/* Each 1 Hz pulse should happen after (rate) ticks */
	jz4740_rtc_reg_ग_लिखो(rtc, JZ_REG_RTC_REGULATOR, rate - 1);

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(dev, irq, jz4740_rtc_irq, 0,
			       pdev->name, rtc);
	अगर (ret) अणु
		dev_err(dev, "Failed to request rtc irq: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (of_device_is_प्रणाली_घातer_controller(np)) अणु
		dev_क्रम_घातer_off = dev;

		अगर (!pm_घातer_off)
			pm_घातer_off = jz4740_rtc_घातer_off;
		अन्यथा
			dev_warn(dev, "Poweroff handler already present!\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver jz4740_rtc_driver = अणु
	.probe	 = jz4740_rtc_probe,
	.driver	 = अणु
		.name  = "jz4740-rtc",
		.of_match_table = jz4740_rtc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jz4740_rtc_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RTC driver for the JZ4740 SoC\n");
MODULE_ALIAS("platform:jz4740-rtc");
