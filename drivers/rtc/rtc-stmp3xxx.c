<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale STMP37XX/STMP378X Real Time Clock driver
 *
 * Copyright (c) 2007 Sigmatel, Inc.
 * Peter Hartley, <peter.hartley@sigmatel.com>
 *
 * Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 * Copyright 2011 Wolfram Sang, Pengutronix e.K.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/sपंचांगp3xxx_rtc_wdt.h>

#घोषणा STMP3XXX_RTC_CTRL			0x0
#घोषणा STMP3XXX_RTC_CTRL_ALARM_IRQ_EN		0x00000001
#घोषणा STMP3XXX_RTC_CTRL_ONEMSEC_IRQ_EN	0x00000002
#घोषणा STMP3XXX_RTC_CTRL_ALARM_IRQ		0x00000004
#घोषणा STMP3XXX_RTC_CTRL_WATCHDOGEN		0x00000010

#घोषणा STMP3XXX_RTC_STAT			0x10
#घोषणा STMP3XXX_RTC_STAT_STALE_SHIFT		16
#घोषणा STMP3XXX_RTC_STAT_RTC_PRESENT		0x80000000
#घोषणा STMP3XXX_RTC_STAT_XTAL32000_PRESENT	0x10000000
#घोषणा STMP3XXX_RTC_STAT_XTAL32768_PRESENT	0x08000000

#घोषणा STMP3XXX_RTC_SECONDS			0x30

#घोषणा STMP3XXX_RTC_ALARM			0x40

#घोषणा STMP3XXX_RTC_WATCHDOG			0x50

#घोषणा STMP3XXX_RTC_PERSISTENT0		0x60
#घोषणा STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE		(1 << 0)
#घोषणा STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN		(1 << 1)
#घोषणा STMP3XXX_RTC_PERSISTENT0_ALARM_EN		(1 << 2)
#घोषणा STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP	(1 << 4)
#घोषणा STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP	(1 << 5)
#घोषणा STMP3XXX_RTC_PERSISTENT0_XTAL32_FREQ		(1 << 6)
#घोषणा STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE		(1 << 7)

#घोषणा STMP3XXX_RTC_PERSISTENT1		0x70
/* missing biपंचांगask in headers */
#घोषणा STMP3XXX_RTC_PERSISTENT1_FORCE_UPDATER	0x80000000

काष्ठा sपंचांगp3xxx_rtc_data अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *io;
	पूर्णांक irq_alarm;
पूर्ण;

#अगर IS_ENABLED(CONFIG_STMP3XXX_RTC_WATCHDOG)
/**
 * sपंचांगp3xxx_wdt_set_समयout - configure the watchकरोg inside the STMP3xxx RTC
 * @dev: the parent device of the watchकरोg (= the RTC)
 * @समयout: the desired value क्रम the समयout रेजिस्टर of the watchकरोg.
 *           0 disables the watchकरोg
 *
 * The watchकरोg needs one रेजिस्टर and two bits which are in the RTC करोमुख्य.
 * To handle the resource conflict, the RTC driver will create another
 * platक्रमm_device क्रम the watchकरोg driver as a child of the RTC device.
 * The watchकरोg driver is passed the below accessor function via platक्रमm_data
 * to configure the watchकरोg. Locking is not needed because accessing SET/CLR
 * रेजिस्टरs is atomic.
 */

अटल व्योम sपंचांगp3xxx_wdt_set_समयout(काष्ठा device *dev, u32 समयout)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	अगर (समयout) अणु
		ग_लिखोl(समयout, rtc_data->io + STMP3XXX_RTC_WATCHDOG);
		ग_लिखोl(STMP3XXX_RTC_CTRL_WATCHDOGEN,
		       rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_SET);
		ग_लिखोl(STMP3XXX_RTC_PERSISTENT1_FORCE_UPDATER,
		       rtc_data->io + STMP3XXX_RTC_PERSISTENT1 + STMP_OFFSET_REG_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(STMP3XXX_RTC_CTRL_WATCHDOGEN,
		       rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);
		ग_लिखोl(STMP3XXX_RTC_PERSISTENT1_FORCE_UPDATER,
		       rtc_data->io + STMP3XXX_RTC_PERSISTENT1 + STMP_OFFSET_REG_CLR);
	पूर्ण
पूर्ण

अटल काष्ठा sपंचांगp3xxx_wdt_pdata wdt_pdata = अणु
	.wdt_set_समयout = sपंचांगp3xxx_wdt_set_समयout,
पूर्ण;

अटल व्योम sपंचांगp3xxx_wdt_रेजिस्टर(काष्ठा platक्रमm_device *rtc_pdev)
अणु
	पूर्णांक rc = -1;
	काष्ठा platक्रमm_device *wdt_pdev =
		platक्रमm_device_alloc("stmp3xxx_rtc_wdt", rtc_pdev->id);

	अगर (wdt_pdev) अणु
		wdt_pdev->dev.parent = &rtc_pdev->dev;
		wdt_pdev->dev.platक्रमm_data = &wdt_pdata;
		rc = platक्रमm_device_add(wdt_pdev);
	पूर्ण

	अगर (rc)
		dev_err(&rtc_pdev->dev,
			"failed to register stmp3xxx_rtc_wdt\n");
पूर्ण
#अन्यथा
अटल व्योम sपंचांगp3xxx_wdt_रेजिस्टर(काष्ठा platक्रमm_device *rtc_pdev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_STMP3XXX_RTC_WATCHDOG */

अटल पूर्णांक sपंचांगp3xxx_रुको_समय(काष्ठा sपंचांगp3xxx_rtc_data *rtc_data)
अणु
	पूर्णांक समयout = 5000; /* 3ms according to i.MX28 Ref Manual */
	/*
	 * The i.MX28 Applications Processor Reference Manual, Rev. 1, 2010
	 * states:
	 * | The order in which रेजिस्टरs are updated is
	 * | Persistent 0, 1, 2, 3, 4, 5, Alarm, Seconds.
	 * | (This list is in bitfield order, from LSB to MSB, as they would
	 * | appear in the STALE_REGS and NEW_REGS bitfields of the HW_RTC_STAT
	 * | रेजिस्टर. For example, the Seconds रेजिस्टर corresponds to
	 * | STALE_REGS or NEW_REGS containing 0x80.)
	 */
	करो अणु
		अगर (!(पढ़ोl(rtc_data->io + STMP3XXX_RTC_STAT) &
				(0x80 << STMP3XXX_RTC_STAT_STALE_SHIFT)))
			वापस 0;
		udelay(1);
	पूर्ण जबतक (--समयout > 0);
	वापस (पढ़ोl(rtc_data->io + STMP3XXX_RTC_STAT) &
		(0x80 << STMP3XXX_RTC_STAT_STALE_SHIFT)) ? -ETIME : 0;
पूर्ण

/* Time पढ़ो/ग_लिखो */
अटल पूर्णांक sपंचांगp3xxx_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	पूर्णांक ret;
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	ret = sपंचांगp3xxx_रुको_समय(rtc_data);
	अगर (ret)
		वापस ret;

	rtc_समय64_to_पंचांग(पढ़ोl(rtc_data->io + STMP3XXX_RTC_SECONDS), rtc_पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	ग_लिखोl(rtc_पंचांग_to_समय64(rtc_पंचांग), rtc_data->io + STMP3XXX_RTC_SECONDS);
	वापस sपंचांगp3xxx_रुको_समय(rtc_data);
पूर्ण

/* पूर्णांकerrupt(s) handler */
अटल irqवापस_t sपंचांगp3xxx_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev_id);
	u32 status = पढ़ोl(rtc_data->io + STMP3XXX_RTC_CTRL);

	अगर (status & STMP3XXX_RTC_CTRL_ALARM_IRQ) अणु
		ग_लिखोl(STMP3XXX_RTC_CTRL_ALARM_IRQ,
			rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);
		rtc_update_irq(rtc_data->rtc, 1, RTC_AF | RTC_IRQF);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	अगर (enabled) अणु
		ग_लिखोl(STMP3XXX_RTC_PERSISTENT0_ALARM_EN |
				STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN,
			rtc_data->io + STMP3XXX_RTC_PERSISTENT0 +
				STMP_OFFSET_REG_SET);
		ग_लिखोl(STMP3XXX_RTC_CTRL_ALARM_IRQ_EN,
			rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(STMP3XXX_RTC_PERSISTENT0_ALARM_EN |
				STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN,
			rtc_data->io + STMP3XXX_RTC_PERSISTENT0 +
				STMP_OFFSET_REG_CLR);
		ग_लिखोl(STMP3XXX_RTC_CTRL_ALARM_IRQ_EN,
			rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(rtc_data->io + STMP3XXX_RTC_ALARM), &alm->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	ग_लिखोl(rtc_पंचांग_to_समय64(&alm->समय), rtc_data->io + STMP3XXX_RTC_ALARM);

	sपंचांगp3xxx_alarm_irq_enable(dev, alm->enabled);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sपंचांगp3xxx_rtc_ops = अणु
	.alarm_irq_enable =
			  sपंचांगp3xxx_alarm_irq_enable,
	.पढ़ो_समय	= sपंचांगp3xxx_rtc_समय_लो,
	.set_समय	= sपंचांगp3xxx_rtc_समय_रखो,
	.पढ़ो_alarm	= sपंचांगp3xxx_rtc_पढ़ो_alarm,
	.set_alarm	= sपंचांगp3xxx_rtc_set_alarm,
पूर्ण;

अटल पूर्णांक sपंचांगp3xxx_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = platक्रमm_get_drvdata(pdev);

	अगर (!rtc_data)
		वापस 0;

	ग_लिखोl(STMP3XXX_RTC_CTRL_ALARM_IRQ_EN,
		rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data;
	काष्ठा resource *r;
	u32 rtc_stat;
	u32 pers0_set, pers0_clr;
	u32 crystalfreq = 0;
	पूर्णांक err;

	rtc_data = devm_kzalloc(&pdev->dev, माप(*rtc_data), GFP_KERNEL);
	अगर (!rtc_data)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "failed to get resource\n");
		वापस -ENXIO;
	पूर्ण

	rtc_data->io = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!rtc_data->io) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		वापस -EIO;
	पूर्ण

	rtc_data->irq_alarm = platक्रमm_get_irq(pdev, 0);

	rtc_stat = पढ़ोl(rtc_data->io + STMP3XXX_RTC_STAT);
	अगर (!(rtc_stat & STMP3XXX_RTC_STAT_RTC_PRESENT)) अणु
		dev_err(&pdev->dev, "no device onboard\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc_data);

	/*
	 * Resetting the rtc stops the watchकरोg समयr that is potentially
	 * running. So (assuming it is running on purpose) करोn't reset अगर the
	 * watchकरोg is enabled.
	 */
	अगर (पढ़ोl(rtc_data->io + STMP3XXX_RTC_CTRL) &
	    STMP3XXX_RTC_CTRL_WATCHDOGEN) अणु
		dev_info(&pdev->dev,
			 "Watchdog is running, skip resetting rtc\n");
	पूर्ण अन्यथा अणु
		err = sपंचांगp_reset_block(rtc_data->io);
		अगर (err) अणु
			dev_err(&pdev->dev, "stmp_reset_block failed: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * Obviously the rtc needs a घड़ी input to be able to run.
	 * This घड़ी can be provided by an बाह्यal 32k crystal. If that one is
	 * missing XTAL must not be disabled in suspend which consumes a
	 * lot of घातer. Normally the presence and exact frequency (supported
	 * are 32000 Hz and 32768 Hz) is detectable from fuses, but as reality
	 * proves these fuses are not blown correctly on all machines, so the
	 * frequency can be overridden in the device tree.
	 */
	अगर (rtc_stat & STMP3XXX_RTC_STAT_XTAL32000_PRESENT)
		crystalfreq = 32000;
	अन्यथा अगर (rtc_stat & STMP3XXX_RTC_STAT_XTAL32768_PRESENT)
		crystalfreq = 32768;

	of_property_पढ़ो_u32(pdev->dev.of_node, "stmp,crystal-freq",
			     &crystalfreq);

	चयन (crystalfreq) अणु
	हाल 32000:
		/* keep 32kHz crystal running in low-घातer mode */
		pers0_set = STMP3XXX_RTC_PERSISTENT0_XTAL32_FREQ |
			STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE;
		pers0_clr = STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP;
		अवरोध;
	हाल 32768:
		/* keep 32.768kHz crystal running in low-घातer mode */
		pers0_set = STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE;
		pers0_clr = STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_XTAL32_FREQ;
		अवरोध;
	शेष:
		dev_warn(&pdev->dev,
			 "invalid crystal-freq specified in device-tree. Assuming no crystal\n");
		fallthrough;
	हाल 0:
		/* keep XTAL on in low-घातer mode */
		pers0_set = STMP3XXX_RTC_PERSISTENT0_XTAL24MHZ_PWRUP;
		pers0_clr = STMP3XXX_RTC_PERSISTENT0_XTAL32KHZ_PWRUP |
			STMP3XXX_RTC_PERSISTENT0_CLOCKSOURCE;
	पूर्ण

	ग_लिखोl(pers0_set, rtc_data->io + STMP3XXX_RTC_PERSISTENT0 +
			STMP_OFFSET_REG_SET);

	ग_लिखोl(STMP3XXX_RTC_PERSISTENT0_ALARM_EN |
			STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN |
			STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE | pers0_clr,
		rtc_data->io + STMP3XXX_RTC_PERSISTENT0 + STMP_OFFSET_REG_CLR);

	ग_लिखोl(STMP3XXX_RTC_CTRL_ONEMSEC_IRQ_EN |
			STMP3XXX_RTC_CTRL_ALARM_IRQ_EN,
		rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);

	rtc_data->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc_data->rtc))
		वापस PTR_ERR(rtc_data->rtc);

	err = devm_request_irq(&pdev->dev, rtc_data->irq_alarm,
			sपंचांगp3xxx_rtc_पूर्णांकerrupt, 0, "RTC alarm", &pdev->dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot claim IRQ%d\n",
			rtc_data->irq_alarm);
		वापस err;
	पूर्ण

	rtc_data->rtc->ops = &sपंचांगp3xxx_rtc_ops;
	rtc_data->rtc->range_max = U32_MAX;

	err = devm_rtc_रेजिस्टर_device(rtc_data->rtc);
	अगर (err)
		वापस err;

	sपंचांगp3xxx_wdt_रेजिस्टर(pdev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांगp3xxx_rtc_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगp3xxx_rtc_data *rtc_data = dev_get_drvdata(dev);

	sपंचांगp_reset_block(rtc_data->io);
	ग_लिखोl(STMP3XXX_RTC_PERSISTENT0_ALARM_EN |
			STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE_EN |
			STMP3XXX_RTC_PERSISTENT0_ALARM_WAKE,
		rtc_data->io + STMP3XXX_RTC_PERSISTENT0 + STMP_OFFSET_REG_CLR);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sपंचांगp3xxx_rtc_pm_ops, sपंचांगp3xxx_rtc_suspend,
			sपंचांगp3xxx_rtc_resume);

अटल स्थिर काष्ठा of_device_id rtc_dt_ids[] = अणु
	अणु .compatible = "fsl,stmp3xxx-rtc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rtc_dt_ids);

अटल काष्ठा platक्रमm_driver sपंचांगp3xxx_rtcdrv = अणु
	.probe		= sपंचांगp3xxx_rtc_probe,
	.हटाओ		= sपंचांगp3xxx_rtc_हटाओ,
	.driver		= अणु
		.name	= "stmp3xxx-rtc",
		.pm	= &sपंचांगp3xxx_rtc_pm_ops,
		.of_match_table = rtc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांगp3xxx_rtcdrv);

MODULE_DESCRIPTION("STMP3xxx RTC Driver");
MODULE_AUTHOR("dmitry pervushin <dpervushin@embeddedalley.com> and "
		"Wolfram Sang <kernel@pengutronix.de>");
MODULE_LICENSE("GPL");
