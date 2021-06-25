<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the RTC in Marvell SoCs.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>


#घोषणा RTC_TIME_REG_OFFS	0
#घोषणा RTC_SECONDS_OFFS	0
#घोषणा RTC_MINUTES_OFFS	8
#घोषणा RTC_HOURS_OFFS		16
#घोषणा RTC_WDAY_OFFS		24
#घोषणा RTC_HOURS_12H_MODE	BIT(22) /* 12 hour mode */

#घोषणा RTC_DATE_REG_OFFS	4
#घोषणा RTC_MDAY_OFFS		0
#घोषणा RTC_MONTH_OFFS		8
#घोषणा RTC_YEAR_OFFS		16

#घोषणा RTC_ALARM_TIME_REG_OFFS	8
#घोषणा RTC_ALARM_DATE_REG_OFFS	0xc
#घोषणा RTC_ALARM_VALID		BIT(7)

#घोषणा RTC_ALARM_INTERRUPT_MASK_REG_OFFS	0x10
#घोषणा RTC_ALARM_INTERRUPT_CASUE_REG_OFFS	0x14

काष्ठा rtc_plat_data अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;
	पूर्णांक		irq;
	काष्ठा clk	*clk;
पूर्ण;

अटल पूर्णांक mv_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32	rtc_reg;

	rtc_reg = (bin2bcd(पंचांग->पंचांग_sec) << RTC_SECONDS_OFFS) |
		(bin2bcd(पंचांग->पंचांग_min) << RTC_MINUTES_OFFS) |
		(bin2bcd(पंचांग->पंचांग_hour) << RTC_HOURS_OFFS) |
		(bin2bcd(पंचांग->पंचांग_wday) << RTC_WDAY_OFFS);
	ग_लिखोl(rtc_reg, ioaddr + RTC_TIME_REG_OFFS);

	rtc_reg = (bin2bcd(पंचांग->पंचांग_mday) << RTC_MDAY_OFFS) |
		(bin2bcd(पंचांग->पंचांग_mon + 1) << RTC_MONTH_OFFS) |
		(bin2bcd(पंचांग->पंचांग_year - 100) << RTC_YEAR_OFFS);
	ग_लिखोl(rtc_reg, ioaddr + RTC_DATE_REG_OFFS);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32	rtc_समय, rtc_date;
	अचिन्हित पूर्णांक year, month, day, hour, minute, second, wday;

	rtc_समय = पढ़ोl(ioaddr + RTC_TIME_REG_OFFS);
	rtc_date = पढ़ोl(ioaddr + RTC_DATE_REG_OFFS);

	second = rtc_समय & 0x7f;
	minute = (rtc_समय >> RTC_MINUTES_OFFS) & 0x7f;
	hour = (rtc_समय >> RTC_HOURS_OFFS) & 0x3f; /* assume 24 hour mode */
	wday = (rtc_समय >> RTC_WDAY_OFFS) & 0x7;

	day = rtc_date & 0x3f;
	month = (rtc_date >> RTC_MONTH_OFFS) & 0x3f;
	year = (rtc_date >> RTC_YEAR_OFFS) & 0xff;

	पंचांग->पंचांग_sec = bcd2bin(second);
	पंचांग->पंचांग_min = bcd2bin(minute);
	पंचांग->पंचांग_hour = bcd2bin(hour);
	पंचांग->पंचांग_mday = bcd2bin(day);
	पंचांग->पंचांग_wday = bcd2bin(wday);
	पंचांग->पंचांग_mon = bcd2bin(month) - 1;
	/* hw counts from year 2000, but पंचांग_year is relative to 1900 */
	पंचांग->पंचांग_year = bcd2bin(year) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32	rtc_समय, rtc_date;
	अचिन्हित पूर्णांक year, month, day, hour, minute, second, wday;

	rtc_समय = पढ़ोl(ioaddr + RTC_ALARM_TIME_REG_OFFS);
	rtc_date = पढ़ोl(ioaddr + RTC_ALARM_DATE_REG_OFFS);

	second = rtc_समय & 0x7f;
	minute = (rtc_समय >> RTC_MINUTES_OFFS) & 0x7f;
	hour = (rtc_समय >> RTC_HOURS_OFFS) & 0x3f; /* assume 24 hour mode */
	wday = (rtc_समय >> RTC_WDAY_OFFS) & 0x7;

	day = rtc_date & 0x3f;
	month = (rtc_date >> RTC_MONTH_OFFS) & 0x3f;
	year = (rtc_date >> RTC_YEAR_OFFS) & 0xff;

	alm->समय.पंचांग_sec = bcd2bin(second);
	alm->समय.पंचांग_min = bcd2bin(minute);
	alm->समय.पंचांग_hour = bcd2bin(hour);
	alm->समय.पंचांग_mday = bcd2bin(day);
	alm->समय.पंचांग_wday = bcd2bin(wday);
	alm->समय.पंचांग_mon = bcd2bin(month) - 1;
	/* hw counts from year 2000, but पंचांग_year is relative to 1900 */
	alm->समय.पंचांग_year = bcd2bin(year) + 100;

	alm->enabled = !!पढ़ोl(ioaddr + RTC_ALARM_INTERRUPT_MASK_REG_OFFS);

	वापस rtc_valid_पंचांग(&alm->समय);
पूर्ण

अटल पूर्णांक mv_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32 rtc_reg = 0;

	अगर (alm->समय.पंचांग_sec >= 0)
		rtc_reg |= (RTC_ALARM_VALID | bin2bcd(alm->समय.पंचांग_sec))
			<< RTC_SECONDS_OFFS;
	अगर (alm->समय.पंचांग_min >= 0)
		rtc_reg |= (RTC_ALARM_VALID | bin2bcd(alm->समय.पंचांग_min))
			<< RTC_MINUTES_OFFS;
	अगर (alm->समय.पंचांग_hour >= 0)
		rtc_reg |= (RTC_ALARM_VALID | bin2bcd(alm->समय.पंचांग_hour))
			<< RTC_HOURS_OFFS;

	ग_लिखोl(rtc_reg, ioaddr + RTC_ALARM_TIME_REG_OFFS);

	अगर (alm->समय.पंचांग_mday >= 0)
		rtc_reg = (RTC_ALARM_VALID | bin2bcd(alm->समय.पंचांग_mday))
			<< RTC_MDAY_OFFS;
	अन्यथा
		rtc_reg = 0;

	अगर (alm->समय.पंचांग_mon >= 0)
		rtc_reg |= (RTC_ALARM_VALID | bin2bcd(alm->समय.पंचांग_mon + 1))
			<< RTC_MONTH_OFFS;

	अगर (alm->समय.पंचांग_year >= 0)
		rtc_reg |= (RTC_ALARM_VALID | bin2bcd(alm->समय.पंचांग_year - 100))
			<< RTC_YEAR_OFFS;

	ग_लिखोl(rtc_reg, ioaddr + RTC_ALARM_DATE_REG_OFFS);
	ग_लिखोl(0, ioaddr + RTC_ALARM_INTERRUPT_CASUE_REG_OFFS);
	ग_लिखोl(alm->enabled ? 1 : 0,
	       ioaddr + RTC_ALARM_INTERRUPT_MASK_REG_OFFS);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;

	अगर (pdata->irq < 0)
		वापस -EINVAL; /* fall back पूर्णांकo rtc-dev's emulation */

	अगर (enabled)
		ग_लिखोl(1, ioaddr + RTC_ALARM_INTERRUPT_MASK_REG_OFFS);
	अन्यथा
		ग_लिखोl(0, ioaddr + RTC_ALARM_INTERRUPT_MASK_REG_OFFS);
	वापस 0;
पूर्ण

अटल irqवापस_t mv_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rtc_plat_data *pdata = data;
	व्योम __iomem *ioaddr = pdata->ioaddr;

	/* alarm irq? */
	अगर (!पढ़ोl(ioaddr + RTC_ALARM_INTERRUPT_CASUE_REG_OFFS))
		वापस IRQ_NONE;

	/* clear पूर्णांकerrupt */
	ग_लिखोl(0, ioaddr + RTC_ALARM_INTERRUPT_CASUE_REG_OFFS);
	rtc_update_irq(pdata->rtc, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mv_rtc_ops = अणु
	.पढ़ो_समय	= mv_rtc_पढ़ो_समय,
	.set_समय	= mv_rtc_set_समय,
	.पढ़ो_alarm	= mv_rtc_पढ़ो_alarm,
	.set_alarm	= mv_rtc_set_alarm,
	.alarm_irq_enable = mv_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक __init mv_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_plat_data *pdata;
	u32 rtc_समय;
	पूर्णांक ret = 0;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->ioaddr))
		वापस PTR_ERR(pdata->ioaddr);

	pdata->clk = devm_clk_get(&pdev->dev, शून्य);
	/* Not all SoCs require a घड़ी.*/
	अगर (!IS_ERR(pdata->clk))
		clk_prepare_enable(pdata->clk);

	/* make sure the 24 hour mode is enabled */
	rtc_समय = पढ़ोl(pdata->ioaddr + RTC_TIME_REG_OFFS);
	अगर (rtc_समय & RTC_HOURS_12H_MODE) अणु
		dev_err(&pdev->dev, "12 Hour mode is enabled but not supported.\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* make sure it is actually functional */
	अगर (rtc_समय == 0x01000000) अणु
		ssleep(1);
		rtc_समय = पढ़ोl(pdata->ioaddr + RTC_TIME_REG_OFFS);
		अगर (rtc_समय == 0x01000000) अणु
			dev_err(&pdev->dev, "internal RTC not ticking\n");
			ret = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण

	pdata->irq = platक्रमm_get_irq(pdev, 0);

	platक्रमm_set_drvdata(pdev, pdata);

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc)) अणु
		ret = PTR_ERR(pdata->rtc);
		जाओ out;
	पूर्ण

	अगर (pdata->irq >= 0) अणु
		ग_लिखोl(0, pdata->ioaddr + RTC_ALARM_INTERRUPT_MASK_REG_OFFS);
		अगर (devm_request_irq(&pdev->dev, pdata->irq, mv_rtc_पूर्णांकerrupt,
				     IRQF_SHARED,
				     pdev->name, pdata) < 0) अणु
			dev_warn(&pdev->dev, "interrupt not available.\n");
			pdata->irq = -1;
		पूर्ण
	पूर्ण

	अगर (pdata->irq >= 0)
		device_init_wakeup(&pdev->dev, 1);
	अन्यथा
		clear_bit(RTC_FEATURE_ALARM, pdata->rtc->features);

	pdata->rtc->ops = &mv_rtc_ops;
	pdata->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	pdata->rtc->range_max = RTC_TIMESTAMP_END_2099;

	ret = devm_rtc_रेजिस्टर_device(pdata->rtc);
	अगर (!ret)
		वापस 0;
out:
	अगर (!IS_ERR(pdata->clk))
		clk_disable_unprepare(pdata->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास mv_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_plat_data *pdata = platक्रमm_get_drvdata(pdev);

	अगर (pdata->irq >= 0)
		device_init_wakeup(&pdev->dev, 0);

	अगर (!IS_ERR(pdata->clk))
		clk_disable_unprepare(pdata->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rtc_mv_of_match_table[] = अणु
	अणु .compatible = "marvell,orion-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rtc_mv_of_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mv_rtc_driver = अणु
	.हटाओ		= __निकास_p(mv_rtc_हटाओ),
	.driver		= अणु
		.name	= "rtc-mv",
		.of_match_table = of_match_ptr(rtc_mv_of_match_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(mv_rtc_driver, mv_rtc_probe);

MODULE_AUTHOR("Saeed Bishara <saeed@marvell.com>");
MODULE_DESCRIPTION("Marvell RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-mv");
