<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * "RTT as Real Time Clock" driver क्रम AT91SAM9 SoC family
 *
 * (C) 2007 Michel Benoit
 *
 * Based on rtc-at91rm9200.c by Rick Bronson
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/समय.स>

/*
 * This driver uses two configurable hardware resources that live in the
 * AT91SAM9 backup घातer करोमुख्य (पूर्णांकended to be घातered at all बार)
 * to implement the Real Time Clock पूर्णांकerfaces
 *
 *  - A "Real-time Timer" (RTT) counts up in seconds from a base समय.
 *    We can't assign the counter value (CRTV) ... but we can reset it.
 *
 *  - One of the "General Purpose Backup Registers" (GPBRs) holds the
 *    base समय, normally an offset from the beginning of the POSIX
 *    epoch (1970-Jan-1 00:00:00 UTC).  Some प्रणालीs also include the
 *    local समयzone's offset.
 *
 * The RTC's value is the RTT counter plus that offset.  The RTC's alarm
 * is likewise a base (ALMV) plus that offset.
 *
 * Not all RTTs will be used as RTCs; some प्रणालीs have multiple RTTs to
 * choose from, or a "real" RTC module.  All प्रणालीs have multiple GPBR
 * रेजिस्टरs available, likewise usable क्रम more than "RTC" support.
 */

#घोषणा AT91_RTT_MR		0x00		/* Real-समय Mode Register */
#घोषणा AT91_RTT_RTPRES		(0xffff << 0)	/* Timer Prescaler Value */
#घोषणा AT91_RTT_ALMIEN		BIT(16)		/* Alarm Interrupt Enable */
#घोषणा AT91_RTT_RTTINCIEN	BIT(17)		/* Increment Interrupt Enable */
#घोषणा AT91_RTT_RTTRST		BIT(18)		/* Timer Restart */

#घोषणा AT91_RTT_AR		0x04		/* Real-समय Alarm Register */
#घोषणा AT91_RTT_ALMV		(0xffffffff)	/* Alarm Value */

#घोषणा AT91_RTT_VR		0x08		/* Real-समय Value Register */
#घोषणा AT91_RTT_CRTV		(0xffffffff)	/* Current Real-समय Value */

#घोषणा AT91_RTT_SR		0x0c		/* Real-समय Status Register */
#घोषणा AT91_RTT_ALMS		BIT(0)		/* Alarm Status */
#घोषणा AT91_RTT_RTTINC		BIT(1)		/* Timer Increment */

/*
 * We store ALARM_DISABLED in ALMV to record that no alarm is set.
 * It's also the reset value क्रम that field.
 */
#घोषणा ALARM_DISABLED	((u32)~0)

काष्ठा sam9_rtc अणु
	व्योम __iomem		*rtt;
	काष्ठा rtc_device	*rtcdev;
	u32			imr;
	काष्ठा regmap		*gpbr;
	अचिन्हित पूर्णांक		gpbr_offset;
	पूर्णांक			irq;
	काष्ठा clk		*sclk;
	bool			suspended;
	अचिन्हित दीर्घ		events;
	spinlock_t		lock;
पूर्ण;

#घोषणा rtt_पढ़ोl(rtc, field) \
	पढ़ोl((rtc)->rtt + AT91_RTT_ ## field)
#घोषणा rtt_ग_लिखोl(rtc, field, val) \
	ग_लिखोl((val), (rtc)->rtt + AT91_RTT_ ## field)

अटल अंतरभूत अचिन्हित पूर्णांक gpbr_पढ़ोl(काष्ठा sam9_rtc *rtc)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(rtc->gpbr, rtc->gpbr_offset, &val);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम gpbr_ग_लिखोl(काष्ठा sam9_rtc *rtc, अचिन्हित पूर्णांक val)
अणु
	regmap_ग_लिखो(rtc->gpbr, rtc->gpbr_offset, val);
पूर्ण

/*
 * Read current समय and date in RTC
 */
अटल पूर्णांक at91_rtc_पढ़ोसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sam9_rtc *rtc = dev_get_drvdata(dev);
	u32 secs, secs2;
	u32 offset;

	/* पढ़ो current समय offset */
	offset = gpbr_पढ़ोl(rtc);
	अगर (offset == 0)
		वापस -EILSEQ;

	/* reपढ़ो the counter to help sync the two घड़ी करोमुख्यs */
	secs = rtt_पढ़ोl(rtc, VR);
	secs2 = rtt_पढ़ोl(rtc, VR);
	अगर (secs != secs2)
		secs = rtt_पढ़ोl(rtc, VR);

	rtc_समय64_to_पंचांग(offset + secs, पंचांग);

	dev_dbg(dev, "%s: %ptR\n", __func__, पंचांग);

	वापस 0;
पूर्ण

/*
 * Set current समय and date in RTC
 */
अटल पूर्णांक at91_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sam9_rtc *rtc = dev_get_drvdata(dev);
	u32 offset, alarm, mr;
	अचिन्हित दीर्घ secs;

	dev_dbg(dev, "%s: %ptR\n", __func__, पंचांग);

	secs = rtc_पंचांग_to_समय64(पंचांग);

	mr = rtt_पढ़ोl(rtc, MR);

	/* disable पूर्णांकerrupts */
	rtt_ग_लिखोl(rtc, MR, mr & ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN));

	/* पढ़ो current समय offset */
	offset = gpbr_पढ़ोl(rtc);

	/* store the new base समय in a battery backup रेजिस्टर */
	secs += 1;
	gpbr_ग_लिखोl(rtc, secs);

	/* adjust the alarm समय क्रम the new base */
	alarm = rtt_पढ़ोl(rtc, AR);
	अगर (alarm != ALARM_DISABLED) अणु
		अगर (offset > secs) अणु
			/* समय jumped backwards, increase समय until alarm */
			alarm += (offset - secs);
		पूर्ण अन्यथा अगर ((alarm + offset) > secs) अणु
			/* समय jumped क्रमwards, decrease समय until alarm */
			alarm -= (secs - offset);
		पूर्ण अन्यथा अणु
			/* समय jumped past the alarm, disable alarm */
			alarm = ALARM_DISABLED;
			mr &= ~AT91_RTT_ALMIEN;
		पूर्ण
		rtt_ग_लिखोl(rtc, AR, alarm);
	पूर्ण

	/* reset the समयr, and re-enable पूर्णांकerrupts */
	rtt_ग_लिखोl(rtc, MR, mr | AT91_RTT_RTTRST);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_पढ़ोalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sam9_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	u32 alarm = rtt_पढ़ोl(rtc, AR);
	u32 offset;

	offset = gpbr_पढ़ोl(rtc);
	अगर (offset == 0)
		वापस -EILSEQ;

	स_रखो(alrm, 0, माप(*alrm));
	अगर (alarm != ALARM_DISABLED && offset != 0) अणु
		rtc_समय64_to_पंचांग(offset + alarm, पंचांग);

		dev_dbg(dev, "%s: %ptR\n", __func__, पंचांग);

		अगर (rtt_पढ़ोl(rtc, MR) & AT91_RTT_ALMIEN)
			alrm->enabled = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sam9_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	अचिन्हित दीर्घ secs;
	u32 offset;
	u32 mr;

	secs = rtc_पंचांग_to_समय64(पंचांग);

	offset = gpbr_पढ़ोl(rtc);
	अगर (offset == 0) अणु
		/* समय is not set */
		वापस -EILSEQ;
	पूर्ण
	mr = rtt_पढ़ोl(rtc, MR);
	rtt_ग_लिखोl(rtc, MR, mr & ~AT91_RTT_ALMIEN);

	/* alarm in the past? finish and leave disabled */
	अगर (secs <= offset) अणु
		rtt_ग_लिखोl(rtc, AR, ALARM_DISABLED);
		वापस 0;
	पूर्ण

	/* अन्यथा set alarm and maybe enable it */
	rtt_ग_लिखोl(rtc, AR, secs - offset);
	अगर (alrm->enabled)
		rtt_ग_लिखोl(rtc, MR, mr | AT91_RTT_ALMIEN);

	dev_dbg(dev, "%s: %ptR\n", __func__, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा sam9_rtc *rtc = dev_get_drvdata(dev);
	u32 mr = rtt_पढ़ोl(rtc, MR);

	dev_dbg(dev, "alarm_irq_enable: enabled=%08x, mr %08x\n", enabled, mr);
	अगर (enabled)
		rtt_ग_लिखोl(rtc, MR, mr | AT91_RTT_ALMIEN);
	अन्यथा
		rtt_ग_लिखोl(rtc, MR, mr & ~AT91_RTT_ALMIEN);
	वापस 0;
पूर्ण

/*
 * Provide additional RTC inक्रमmation in /proc/driver/rtc
 */
अटल पूर्णांक at91_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा sam9_rtc *rtc = dev_get_drvdata(dev);
	u32 mr = rtt_पढ़ोl(rtc, MR);

	seq_म_लिखो(seq, "update_IRQ\t: %s\n",
		   (mr & AT91_RTT_RTTINCIEN) ? "yes" : "no");
	वापस 0;
पूर्ण

अटल irqवापस_t at91_rtc_cache_events(काष्ठा sam9_rtc *rtc)
अणु
	u32 sr, mr;

	/* Shared पूर्णांकerrupt may be क्रम another device.  Note: पढ़ोing
	 * SR clears it, so we must only पढ़ो it in this irq handler!
	 */
	mr = rtt_पढ़ोl(rtc, MR) & (AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN);
	sr = rtt_पढ़ोl(rtc, SR) & (mr >> 16);
	अगर (!sr)
		वापस IRQ_NONE;

	/* alarm status */
	अगर (sr & AT91_RTT_ALMS)
		rtc->events |= (RTC_AF | RTC_IRQF);

	/* समयr update/increment */
	अगर (sr & AT91_RTT_RTTINC)
		rtc->events |= (RTC_UF | RTC_IRQF);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम at91_rtc_flush_events(काष्ठा sam9_rtc *rtc)
अणु
	अगर (!rtc->events)
		वापस;

	rtc_update_irq(rtc->rtcdev, 1, rtc->events);
	rtc->events = 0;

	pr_debug("%s: num=%ld, events=0x%02lx\n", __func__,
		 rtc->events >> 8, rtc->events & 0x000000FF);
पूर्ण

/*
 * IRQ handler क्रम the RTC
 */
अटल irqवापस_t at91_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *_rtc)
अणु
	काष्ठा sam9_rtc *rtc = _rtc;
	पूर्णांक ret;

	spin_lock(&rtc->lock);

	ret = at91_rtc_cache_events(rtc);

	/* We're called in suspended state */
	अगर (rtc->suspended) अणु
		/* Mask irqs coming from this peripheral */
		rtt_ग_लिखोl(rtc, MR,
			   rtt_पढ़ोl(rtc, MR) &
			   ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN));
		/* Trigger a प्रणाली wakeup */
		pm_प्रणाली_wakeup();
	पूर्ण अन्यथा अणु
		at91_rtc_flush_events(rtc);
	पूर्ण

	spin_unlock(&rtc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops at91_rtc_ops = अणु
	.पढ़ो_समय	= at91_rtc_पढ़ोसमय,
	.set_समय	= at91_rtc_समय_रखो,
	.पढ़ो_alarm	= at91_rtc_पढ़ोalarm,
	.set_alarm	= at91_rtc_setalarm,
	.proc		= at91_rtc_proc,
	.alarm_irq_enable = at91_rtc_alarm_irq_enable,
पूर्ण;

/*
 * Initialize and install RTC driver
 */
अटल पूर्णांक at91_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sam9_rtc	*rtc;
	पूर्णांक		ret, irq;
	u32		mr;
	अचिन्हित पूर्णांक	sclk_rate;
	काष्ठा of_phandle_args args;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	spin_lock_init(&rtc->lock);
	rtc->irq = irq;

	/* platक्रमm setup code should have handled this; sigh */
	अगर (!device_can_wakeup(&pdev->dev))
		device_init_wakeup(&pdev->dev, 1);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtt = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->rtt))
		वापस PTR_ERR(rtc->rtt);

	ret = of_parse_phandle_with_fixed_args(pdev->dev.of_node,
					       "atmel,rtt-rtc-time-reg", 1, 0,
					       &args);
	अगर (ret)
		वापस ret;

	rtc->gpbr = syscon_node_to_regmap(args.np);
	rtc->gpbr_offset = args.args[0];
	अगर (IS_ERR(rtc->gpbr)) अणु
		dev_err(&pdev->dev, "failed to retrieve gpbr regmap, aborting.\n");
		वापस -ENOMEM;
	पूर्ण

	rtc->sclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rtc->sclk))
		वापस PTR_ERR(rtc->sclk);

	ret = clk_prepare_enable(rtc->sclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable slow clock\n");
		वापस ret;
	पूर्ण

	sclk_rate = clk_get_rate(rtc->sclk);
	अगर (!sclk_rate || sclk_rate > AT91_RTT_RTPRES) अणु
		dev_err(&pdev->dev, "Invalid slow clock rate\n");
		ret = -EINVAL;
		जाओ err_clk;
	पूर्ण

	mr = rtt_पढ़ोl(rtc, MR);

	/* unless RTT is counting at 1 Hz, re-initialize it */
	अगर ((mr & AT91_RTT_RTPRES) != sclk_rate) अणु
		mr = AT91_RTT_RTTRST | (sclk_rate & AT91_RTT_RTPRES);
		gpbr_ग_लिखोl(rtc, 0);
	पूर्ण

	/* disable all पूर्णांकerrupts (same as on shutकरोwn path) */
	mr &= ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN);
	rtt_ग_लिखोl(rtc, MR, mr);

	rtc->rtcdev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtcdev)) अणु
		ret = PTR_ERR(rtc->rtcdev);
		जाओ err_clk;
	पूर्ण

	rtc->rtcdev->ops = &at91_rtc_ops;
	rtc->rtcdev->range_max = U32_MAX;

	/* रेजिस्टर irq handler after we know what name we'll use */
	ret = devm_request_irq(&pdev->dev, rtc->irq, at91_rtc_पूर्णांकerrupt,
			       IRQF_SHARED | IRQF_COND_SUSPEND,
			       dev_name(&rtc->rtcdev->dev), rtc);
	अगर (ret) अणु
		dev_dbg(&pdev->dev, "can't share IRQ %d?\n", rtc->irq);
		जाओ err_clk;
	पूर्ण

	/* NOTE:  sam9260 rev A silicon has a ROM bug which resets the
	 * RTT on at least some reboots.  If you have that chip, you must
	 * initialize the समय from some बाह्यal source like a GPS, wall
	 * घड़ी, discrete RTC, etc
	 */

	अगर (gpbr_पढ़ोl(rtc) == 0)
		dev_warn(&pdev->dev, "%s: SET TIME!\n",
			 dev_name(&rtc->rtcdev->dev));

	वापस devm_rtc_रेजिस्टर_device(rtc->rtcdev);

err_clk:
	clk_disable_unprepare(rtc->sclk);

	वापस ret;
पूर्ण

/*
 * Disable and हटाओ the RTC driver
 */
अटल पूर्णांक at91_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sam9_rtc	*rtc = platक्रमm_get_drvdata(pdev);
	u32		mr = rtt_पढ़ोl(rtc, MR);

	/* disable all पूर्णांकerrupts */
	rtt_ग_लिखोl(rtc, MR, mr & ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN));

	clk_disable_unprepare(rtc->sclk);

	वापस 0;
पूर्ण

अटल व्योम at91_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sam9_rtc	*rtc = platक्रमm_get_drvdata(pdev);
	u32		mr = rtt_पढ़ोl(rtc, MR);

	rtc->imr = mr & (AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN);
	rtt_ग_लिखोl(rtc, MR, mr & ~rtc->imr);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

/* AT91SAM9 RTC Power management control */

अटल पूर्णांक at91_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sam9_rtc	*rtc = dev_get_drvdata(dev);
	u32		mr = rtt_पढ़ोl(rtc, MR);

	/*
	 * This IRQ is shared with DBGU and other hardware which isn't
	 * necessarily a wakeup event source.
	 */
	rtc->imr = mr & (AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN);
	अगर (rtc->imr) अणु
		अगर (device_may_wakeup(dev) && (mr & AT91_RTT_ALMIEN)) अणु
			अचिन्हित दीर्घ flags;

			enable_irq_wake(rtc->irq);
			spin_lock_irqsave(&rtc->lock, flags);
			rtc->suspended = true;
			spin_unlock_irqrestore(&rtc->lock, flags);
			/* करोn't let RTTINC cause wakeups */
			अगर (mr & AT91_RTT_RTTINCIEN)
				rtt_ग_लिखोl(rtc, MR, mr & ~AT91_RTT_RTTINCIEN);
		पूर्ण अन्यथा अणु
			rtt_ग_लिखोl(rtc, MR, mr & ~rtc->imr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा sam9_rtc	*rtc = dev_get_drvdata(dev);
	u32		mr;

	अगर (rtc->imr) अणु
		अचिन्हित दीर्घ flags;

		अगर (device_may_wakeup(dev))
			disable_irq_wake(rtc->irq);
		mr = rtt_पढ़ोl(rtc, MR);
		rtt_ग_लिखोl(rtc, MR, mr | rtc->imr);

		spin_lock_irqsave(&rtc->lock, flags);
		rtc->suspended = false;
		at91_rtc_cache_events(rtc);
		at91_rtc_flush_events(rtc);
		spin_unlock_irqrestore(&rtc->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(at91_rtc_pm_ops, at91_rtc_suspend, at91_rtc_resume);

अटल स्थिर काष्ठा of_device_id at91_rtc_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9260-rtt" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_rtc_dt_ids);

अटल काष्ठा platक्रमm_driver at91_rtc_driver = अणु
	.probe		= at91_rtc_probe,
	.हटाओ		= at91_rtc_हटाओ,
	.shutकरोwn	= at91_rtc_shutकरोwn,
	.driver		= अणु
		.name	= "rtc-at91sam9",
		.pm	= &at91_rtc_pm_ops,
		.of_match_table = of_match_ptr(at91_rtc_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(at91_rtc_driver);

MODULE_AUTHOR("Michel Benoit");
MODULE_DESCRIPTION("RTC driver for Atmel AT91SAM9x");
MODULE_LICENSE("GPL");
