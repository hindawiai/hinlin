<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2014-2017 Broadcom
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/reboot.h>
#समावेश <linux/rtc.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/suspend.h>

काष्ठा brcmstb_wakeपंचांगr अणु
	काष्ठा rtc_device *rtc;
	काष्ठा device *dev;
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा notअगरier_block reboot_notअगरier;
	काष्ठा clk *clk;
	u32 rate;
पूर्ण;

#घोषणा BRCMSTB_WKTMR_EVENT		0x00
#घोषणा BRCMSTB_WKTMR_COUNTER		0x04
#घोषणा BRCMSTB_WKTMR_ALARM		0x08
#घोषणा BRCMSTB_WKTMR_PRESCALER		0x0C
#घोषणा BRCMSTB_WKTMR_PRESCALER_VAL	0x10

#घोषणा BRCMSTB_WKTMR_DEFAULT_FREQ	27000000

अटल अंतरभूत व्योम brcmstb_wakeपंचांगr_clear_alarm(काष्ठा brcmstb_wakeपंचांगr *समयr)
अणु
	ग_लिखोl_relaxed(1, समयr->base + BRCMSTB_WKTMR_EVENT);
	(व्योम)पढ़ोl_relaxed(समयr->base + BRCMSTB_WKTMR_EVENT);
पूर्ण

अटल व्योम brcmstb_wakeपंचांगr_set_alarm(काष्ठा brcmstb_wakeपंचांगr *समयr,
				      अचिन्हित पूर्णांक secs)
अणु
	brcmstb_wakeपंचांगr_clear_alarm(समयr);

	/* Make sure we are actually counting in seconds */
	ग_लिखोl_relaxed(समयr->rate, समयr->base + BRCMSTB_WKTMR_PRESCALER);

	ग_लिखोl_relaxed(secs + 1, समयr->base + BRCMSTB_WKTMR_ALARM);
पूर्ण

अटल irqवापस_t brcmstb_wakeपंचांगr_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = data;

	pm_wakeup_event(समयr->dev, 0);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा wkपंचांगr_समय अणु
	u32 sec;
	u32 pre;
पूर्ण;

अटल व्योम wkपंचांगr_पढ़ो(काष्ठा brcmstb_wakeपंचांगr *समयr,
		       काष्ठा wkपंचांगr_समय *t)
अणु
	u32 पंचांगp;

	करो अणु
		t->sec = पढ़ोl_relaxed(समयr->base + BRCMSTB_WKTMR_COUNTER);
		पंचांगp = पढ़ोl_relaxed(समयr->base + BRCMSTB_WKTMR_PRESCALER_VAL);
	पूर्ण जबतक (पंचांगp >= समयr->rate);

	t->pre = समयr->rate - पंचांगp;
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_prepare_suspend(काष्ठा brcmstb_wakeपंचांगr *समयr)
अणु
	काष्ठा device *dev = समयr->dev;
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(dev)) अणु
		ret = enable_irq_wake(समयr->irq);
		अगर (ret) अणु
			dev_err(dev, "failed to enable wake-up interrupt\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* If enabled as a wakeup-source, arm the समयr when घातering off */
अटल पूर्णांक brcmstb_wakeपंचांगr_reboot(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr;

	समयr = container_of(nb, काष्ठा brcmstb_wakeपंचांगr, reboot_notअगरier);

	/* Set समयr क्रम cold boot */
	अगर (action == SYS_POWER_OFF)
		brcmstb_wakeपंचांगr_prepare_suspend(समयr);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_समय_लो(काष्ठा device *dev,
				   काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(dev);
	काष्ठा wkपंचांगr_समय now;

	wkपंचांगr_पढ़ो(समयr, &now);

	rtc_समय64_to_पंचांग(now.sec, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_समय_रखो(काष्ठा device *dev,
				   काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(dev);
	समय64_t sec;

	sec = rtc_पंचांग_to_समय64(पंचांग);

	ग_लिखोl_relaxed(sec, समयr->base + BRCMSTB_WKTMR_COUNTER);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_getalarm(काष्ठा device *dev,
				    काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(dev);
	समय64_t sec;
	u32 reg;

	sec = पढ़ोl_relaxed(समयr->base + BRCMSTB_WKTMR_ALARM);
	अगर (sec != 0) अणु
		/* Alarm is enabled */
		alarm->enabled = 1;
		rtc_समय64_to_पंचांग(sec, &alarm->समय);
	पूर्ण

	reg = पढ़ोl_relaxed(समयr->base + BRCMSTB_WKTMR_EVENT);
	alarm->pending = !!(reg & 1);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_setalarm(काष्ठा device *dev,
				     काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(dev);
	समय64_t sec;

	अगर (alarm->enabled)
		sec = rtc_पंचांग_to_समय64(&alarm->समय);
	अन्यथा
		sec = 0;

	brcmstb_wakeपंचांगr_set_alarm(समयr, sec);

	वापस 0;
पूर्ण

/*
 * Does not करो much but keep the RTC class happy. We always support
 * alarms.
 */
अटल पूर्णांक brcmstb_wakeपंचांगr_alarm_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops brcmstb_wakeपंचांगr_ops = अणु
	.पढ़ो_समय	= brcmstb_wakeपंचांगr_समय_लो,
	.set_समय	= brcmstb_wakeपंचांगr_समय_रखो,
	.पढ़ो_alarm	= brcmstb_wakeपंचांगr_getalarm,
	.set_alarm	= brcmstb_wakeपंचांगr_setalarm,
	.alarm_irq_enable = brcmstb_wakeपंचांगr_alarm_enable,
पूर्ण;

अटल पूर्णांक brcmstb_wakeपंचांगr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा brcmstb_wakeपंचांगr *समयr;
	पूर्णांक ret;

	समयr = devm_kzalloc(dev, माप(*समयr), GFP_KERNEL);
	अगर (!समयr)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, समयr);
	समयr->dev = dev;

	समयr->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(समयr->base))
		वापस PTR_ERR(समयr->base);

	समयr->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(समयr->rtc))
		वापस PTR_ERR(समयr->rtc);

	/*
	 * Set wakeup capability beक्रमe requesting wakeup पूर्णांकerrupt, so we can
	 * process boot-समय "wakeups" (e.g., from S5 soft-off)
	 */
	device_set_wakeup_capable(dev, true);
	device_wakeup_enable(dev);

	समयr->irq = platक्रमm_get_irq(pdev, 0);
	अगर (समयr->irq < 0)
		वापस -ENODEV;

	समयr->clk = devm_clk_get(dev, शून्य);
	अगर (!IS_ERR(समयr->clk)) अणु
		ret = clk_prepare_enable(समयr->clk);
		अगर (ret)
			वापस ret;
		समयr->rate = clk_get_rate(समयr->clk);
		अगर (!समयr->rate)
			समयr->rate = BRCMSTB_WKTMR_DEFAULT_FREQ;
	पूर्ण अन्यथा अणु
		समयr->rate = BRCMSTB_WKTMR_DEFAULT_FREQ;
		समयr->clk = शून्य;
	पूर्ण

	ret = devm_request_irq(dev, समयr->irq, brcmstb_wakeपंचांगr_irq, 0,
			       "brcmstb-waketimer", समयr);
	अगर (ret < 0)
		जाओ err_clk;

	समयr->reboot_notअगरier.notअगरier_call = brcmstb_wakeपंचांगr_reboot;
	रेजिस्टर_reboot_notअगरier(&समयr->reboot_notअगरier);

	समयr->rtc->ops = &brcmstb_wakeपंचांगr_ops;
	समयr->rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(समयr->rtc);
	अगर (ret)
		जाओ err_notअगरier;

	dev_info(dev, "registered, with irq %d\n", समयr->irq);

	वापस 0;

err_notअगरier:
	unरेजिस्टर_reboot_notअगरier(&समयr->reboot_notअगरier);

err_clk:
	clk_disable_unprepare(समयr->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(&pdev->dev);

	unरेजिस्टर_reboot_notअगरier(&समयr->reboot_notअगरier);
	clk_disable_unprepare(समयr->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcmstb_wakeपंचांगr_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(dev);

	वापस brcmstb_wakeपंचांगr_prepare_suspend(समयr);
पूर्ण

अटल पूर्णांक brcmstb_wakeपंचांगr_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_wakeपंचांगr *समयr = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!device_may_wakeup(dev))
		वापस 0;

	ret = disable_irq_wake(समयr->irq);

	brcmstb_wakeपंचांगr_clear_alarm(समयr);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(brcmstb_wakeपंचांगr_pm_ops,
			 brcmstb_wakeपंचांगr_suspend, brcmstb_wakeपंचांगr_resume);

अटल स्थिर __maybe_unused काष्ठा of_device_id brcmstb_wakeपंचांगr_of_match[] = अणु
	अणु .compatible = "brcm,brcmstb-waketimer" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver brcmstb_wakeपंचांगr_driver = अणु
	.probe			= brcmstb_wakeपंचांगr_probe,
	.हटाओ			= brcmstb_wakeपंचांगr_हटाओ,
	.driver = अणु
		.name		= "brcmstb-waketimer",
		.pm		= &brcmstb_wakeपंचांगr_pm_ops,
		.of_match_table	= of_match_ptr(brcmstb_wakeपंचांगr_of_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(brcmstb_wakeपंचांगr_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Norris");
MODULE_AUTHOR("Markus Mayer");
MODULE_DESCRIPTION("Wake-up timer driver for STB chips");
