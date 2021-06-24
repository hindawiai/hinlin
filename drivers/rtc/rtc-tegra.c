<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * An RTC driver क्रम the NVIDIA Tegra 200 series पूर्णांकernal RTC.
 *
 * Copyright (c) 2010-2019, NVIDIA Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

/* Set to 1 = busy every eight 32 kHz घड़ीs during copy of sec+msec to AHB. */
#घोषणा TEGRA_RTC_REG_BUSY			0x004
#घोषणा TEGRA_RTC_REG_SECONDS			0x008
/* When msec is पढ़ो, the seconds are buffered पूर्णांकo shaकरोw seconds. */
#घोषणा TEGRA_RTC_REG_SHADOW_SECONDS		0x00c
#घोषणा TEGRA_RTC_REG_MILLI_SECONDS		0x010
#घोषणा TEGRA_RTC_REG_SECONDS_ALARM0		0x014
#घोषणा TEGRA_RTC_REG_SECONDS_ALARM1		0x018
#घोषणा TEGRA_RTC_REG_MILLI_SECONDS_ALARM0	0x01c
#घोषणा TEGRA_RTC_REG_INTR_MASK			0x028
/* ग_लिखो 1 bits to clear status bits */
#घोषणा TEGRA_RTC_REG_INTR_STATUS		0x02c

/* bits in INTR_MASK */
#घोषणा TEGRA_RTC_INTR_MASK_MSEC_CDN_ALARM	(1<<4)
#घोषणा TEGRA_RTC_INTR_MASK_SEC_CDN_ALARM	(1<<3)
#घोषणा TEGRA_RTC_INTR_MASK_MSEC_ALARM		(1<<2)
#घोषणा TEGRA_RTC_INTR_MASK_SEC_ALARM1		(1<<1)
#घोषणा TEGRA_RTC_INTR_MASK_SEC_ALARM0		(1<<0)

/* bits in INTR_STATUS */
#घोषणा TEGRA_RTC_INTR_STATUS_MSEC_CDN_ALARM	(1<<4)
#घोषणा TEGRA_RTC_INTR_STATUS_SEC_CDN_ALARM	(1<<3)
#घोषणा TEGRA_RTC_INTR_STATUS_MSEC_ALARM	(1<<2)
#घोषणा TEGRA_RTC_INTR_STATUS_SEC_ALARM1	(1<<1)
#घोषणा TEGRA_RTC_INTR_STATUS_SEC_ALARM0	(1<<0)

काष्ठा tegra_rtc_info अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा rtc_device *rtc;
	व्योम __iomem *base; /* शून्य अगर not initialized */
	काष्ठा clk *clk;
	पूर्णांक irq; /* alarm and periodic IRQ */
	spinlock_t lock;
पूर्ण;

/*
 * RTC hardware is busy when it is updating its values over AHB once every
 * eight 32 kHz घड़ीs (~250 us). Outside of these updates the CPU is मुक्त to
 * ग_लिखो. CPU is always मुक्त to पढ़ो.
 */
अटल अंतरभूत u32 tegra_rtc_check_busy(काष्ठा tegra_rtc_info *info)
अणु
	वापस पढ़ोl(info->base + TEGRA_RTC_REG_BUSY) & 1;
पूर्ण

/*
 * Wait क्रम hardware to be पढ़ोy क्रम writing. This function tries to maximize
 * the amount of समय beक्रमe the next update. It करोes this by रुकोing क्रम the
 * RTC to become busy with its periodic update, then वापसing once the RTC
 * first becomes not busy.
 *
 * This periodic update (where the seconds and milliseconds are copied to the
 * AHB side) occurs every eight 32 kHz घड़ीs (~250 us). The behavior of this
 * function allows us to make some assumptions without पूर्णांकroducing a race,
 * because 250 us is plenty of समय to पढ़ो/ग_लिखो a value.
 */
अटल पूर्णांक tegra_rtc_रुको_जबतक_busy(काष्ठा device *dev)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	पूर्णांक retries = 500; /* ~490 us is the worst हाल, ~250 us is best */

	/*
	 * First रुको क्रम the RTC to become busy. This is when it posts its
	 * updated seconds+msec रेजिस्टरs to AHB side.
	 */
	जबतक (tegra_rtc_check_busy(info)) अणु
		अगर (!retries--)
			जाओ retry_failed;

		udelay(1);
	पूर्ण

	/* now we have about 250 us to manipulate रेजिस्टरs */
	वापस 0;

retry_failed:
	dev_err(dev, "write failed: retry count exceeded\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 sec;

	/*
	 * RTC hardware copies seconds to shaकरोw seconds when a पढ़ो of
	 * milliseconds occurs. use a lock to keep other thपढ़ोs out.
	 */
	spin_lock_irqsave(&info->lock, flags);

	पढ़ोl(info->base + TEGRA_RTC_REG_MILLI_SECONDS);
	sec = पढ़ोl(info->base + TEGRA_RTC_REG_SHADOW_SECONDS);

	spin_unlock_irqrestore(&info->lock, flags);

	rtc_समय64_to_पंचांग(sec, पंचांग);

	dev_vdbg(dev, "time read as %u, %ptR\n", sec, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	u32 sec;
	पूर्णांक ret;

	/* convert पंचांग to seconds */
	sec = rtc_पंचांग_to_समय64(पंचांग);

	dev_vdbg(dev, "time set to %u, %ptR\n", sec, पंचांग);

	/* seconds only written अगर रुको succeeded */
	ret = tegra_rtc_रुको_जबतक_busy(dev);
	अगर (!ret)
		ग_लिखोl(sec, info->base + TEGRA_RTC_REG_SECONDS);

	dev_vdbg(dev, "time read back as %d\n",
		 पढ़ोl(info->base + TEGRA_RTC_REG_SECONDS));

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	u32 sec, value;

	sec = पढ़ोl(info->base + TEGRA_RTC_REG_SECONDS_ALARM0);

	अगर (sec == 0) अणु
		/* alarm is disabled */
		alarm->enabled = 0;
	पूर्ण अन्यथा अणु
		/* alarm is enabled */
		alarm->enabled = 1;
		rtc_समय64_to_पंचांग(sec, &alarm->समय);
	पूर्ण

	value = पढ़ोl(info->base + TEGRA_RTC_REG_INTR_STATUS);
	alarm->pending = (value & TEGRA_RTC_INTR_STATUS_SEC_ALARM0) != 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 status;

	tegra_rtc_रुको_जबतक_busy(dev);
	spin_lock_irqsave(&info->lock, flags);

	/* पढ़ो the original value, and OR in the flag */
	status = पढ़ोl(info->base + TEGRA_RTC_REG_INTR_MASK);
	अगर (enabled)
		status |= TEGRA_RTC_INTR_MASK_SEC_ALARM0; /* set it */
	अन्यथा
		status &= ~TEGRA_RTC_INTR_MASK_SEC_ALARM0; /* clear it */

	ग_लिखोl(status, info->base + TEGRA_RTC_REG_INTR_MASK);

	spin_unlock_irqrestore(&info->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	u32 sec;

	अगर (alarm->enabled)
		sec = rtc_पंचांग_to_समय64(&alarm->समय);
	अन्यथा
		sec = 0;

	tegra_rtc_रुको_जबतक_busy(dev);
	ग_लिखोl(sec, info->base + TEGRA_RTC_REG_SECONDS_ALARM0);
	dev_vdbg(dev, "alarm read back as %d\n",
		 पढ़ोl(info->base + TEGRA_RTC_REG_SECONDS_ALARM0));

	/* अगर successfully written and alarm is enabled ... */
	अगर (sec) अणु
		tegra_rtc_alarm_irq_enable(dev, 1);
		dev_vdbg(dev, "alarm set as %u, %ptR\n", sec, &alarm->समय);
	पूर्ण अन्यथा अणु
		/* disable alarm अगर 0 or ग_लिखो error */
		dev_vdbg(dev, "alarm disabled\n");
		tegra_rtc_alarm_irq_enable(dev, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	अगर (!dev || !dev->driver)
		वापस 0;

	seq_म_लिखो(seq, "name\t\t: %s\n", dev_name(dev));

	वापस 0;
पूर्ण

अटल irqवापस_t tegra_rtc_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ events = 0;
	u32 status;

	status = पढ़ोl(info->base + TEGRA_RTC_REG_INTR_STATUS);
	अगर (status) अणु
		/* clear the पूर्णांकerrupt masks and status on any IRQ */
		tegra_rtc_रुको_जबतक_busy(dev);

		spin_lock(&info->lock);
		ग_लिखोl(0, info->base + TEGRA_RTC_REG_INTR_MASK);
		ग_लिखोl(status, info->base + TEGRA_RTC_REG_INTR_STATUS);
		spin_unlock(&info->lock);
	पूर्ण

	/* check अगर alarm */
	अगर (status & TEGRA_RTC_INTR_STATUS_SEC_ALARM0)
		events |= RTC_IRQF | RTC_AF;

	/* check अगर periodic */
	अगर (status & TEGRA_RTC_INTR_STATUS_SEC_CDN_ALARM)
		events |= RTC_IRQF | RTC_PF;

	rtc_update_irq(info->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops tegra_rtc_ops = अणु
	.पढ़ो_समय = tegra_rtc_पढ़ो_समय,
	.set_समय = tegra_rtc_set_समय,
	.पढ़ो_alarm = tegra_rtc_पढ़ो_alarm,
	.set_alarm = tegra_rtc_set_alarm,
	.proc = tegra_rtc_proc,
	.alarm_irq_enable = tegra_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_rtc_dt_match[] = अणु
	अणु .compatible = "nvidia,tegra20-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_rtc_dt_match);

अटल पूर्णांक tegra_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_rtc_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->base))
		वापस PTR_ERR(info->base);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret <= 0)
		वापस ret;

	info->irq = ret;

	info->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(info->rtc))
		वापस PTR_ERR(info->rtc);

	info->rtc->ops = &tegra_rtc_ops;
	info->rtc->range_max = U32_MAX;

	info->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(info->clk))
		वापस PTR_ERR(info->clk);

	ret = clk_prepare_enable(info->clk);
	अगर (ret < 0)
		वापस ret;

	/* set context info */
	info->pdev = pdev;
	spin_lock_init(&info->lock);

	platक्रमm_set_drvdata(pdev, info);

	/* clear out the hardware */
	ग_लिखोl(0, info->base + TEGRA_RTC_REG_SECONDS_ALARM0);
	ग_लिखोl(0xffffffff, info->base + TEGRA_RTC_REG_INTR_STATUS);
	ग_लिखोl(0, info->base + TEGRA_RTC_REG_INTR_MASK);

	device_init_wakeup(&pdev->dev, 1);

	ret = devm_request_irq(&pdev->dev, info->irq, tegra_rtc_irq_handler,
			       IRQF_TRIGGER_HIGH, dev_name(&pdev->dev),
			       &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request interrupt: %d\n", ret);
		जाओ disable_clk;
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(info->rtc);
	अगर (ret)
		जाओ disable_clk;

	dev_notice(&pdev->dev, "Tegra internal Real Time Clock\n");

	वापस 0;

disable_clk:
	clk_disable_unprepare(info->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_rtc_info *info = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);

	tegra_rtc_रुको_जबतक_busy(dev);

	/* only use ALARM0 as a wake source */
	ग_लिखोl(0xffffffff, info->base + TEGRA_RTC_REG_INTR_STATUS);
	ग_लिखोl(TEGRA_RTC_INTR_STATUS_SEC_ALARM0,
	       info->base + TEGRA_RTC_REG_INTR_MASK);

	dev_vdbg(dev, "alarm sec = %d\n",
		 पढ़ोl(info->base + TEGRA_RTC_REG_SECONDS_ALARM0));

	dev_vdbg(dev, "Suspend (device_may_wakeup=%d) IRQ:%d\n",
		 device_may_wakeup(dev), info->irq);

	/* leave the alarms on as a wake source */
	अगर (device_may_wakeup(dev))
		enable_irq_wake(info->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_rtc_info *info = dev_get_drvdata(dev);

	dev_vdbg(dev, "Resume (device_may_wakeup=%d)\n",
		 device_may_wakeup(dev));

	/* alarms were left on as a wake source, turn them off */
	अगर (device_may_wakeup(dev))
		disable_irq_wake(info->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tegra_rtc_pm_ops, tegra_rtc_suspend, tegra_rtc_resume);

अटल व्योम tegra_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	dev_vdbg(&pdev->dev, "disabling interrupts\n");
	tegra_rtc_alarm_irq_enable(&pdev->dev, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_rtc_driver = अणु
	.probe = tegra_rtc_probe,
	.हटाओ = tegra_rtc_हटाओ,
	.shutकरोwn = tegra_rtc_shutकरोwn,
	.driver = अणु
		.name = "tegra_rtc",
		.of_match_table = tegra_rtc_dt_match,
		.pm = &tegra_rtc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_rtc_driver);

MODULE_AUTHOR("Jon Mayo <jmayo@nvidia.com>");
MODULE_DESCRIPTION("driver for Tegra internal RTC");
MODULE_LICENSE("GPL");
