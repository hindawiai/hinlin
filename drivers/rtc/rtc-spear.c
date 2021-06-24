<शैली गुरु>
/*
 * drivers/rtc/rtc-spear.c
 *
 * Copyright (C) 2010 ST Microelectronics
 * Rajeev Kumar<rajeev-dlh.kumar@st.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/bcd.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

/* RTC रेजिस्टरs */
#घोषणा TIME_REG		0x00
#घोषणा DATE_REG		0x04
#घोषणा ALARM_TIME_REG		0x08
#घोषणा ALARM_DATE_REG		0x0C
#घोषणा CTRL_REG		0x10
#घोषणा STATUS_REG		0x14

/* TIME_REG & ALARM_TIME_REG */
#घोषणा SECONDS_UNITS		(0xf<<0)	/* seconds units position */
#घोषणा SECONDS_TENS		(0x7<<4)	/* seconds tens position */
#घोषणा MINUTES_UNITS		(0xf<<8)	/* minutes units position */
#घोषणा MINUTES_TENS		(0x7<<12)	/* minutes tens position */
#घोषणा HOURS_UNITS		(0xf<<16)	/* hours units position */
#घोषणा HOURS_TENS		(0x3<<20)	/* hours tens position */

/* DATE_REG & ALARM_DATE_REG */
#घोषणा DAYS_UNITS		(0xf<<0)	/* days units position */
#घोषणा DAYS_TENS		(0x3<<4)	/* days tens position */
#घोषणा MONTHS_UNITS		(0xf<<8)	/* months units position */
#घोषणा MONTHS_TENS		(0x1<<12)	/* months tens position */
#घोषणा YEARS_UNITS		(0xf<<16)	/* years units position */
#घोषणा YEARS_TENS		(0xf<<20)	/* years tens position */
#घोषणा YEARS_HUNDREDS		(0xf<<24)	/* years hundereds position */
#घोषणा YEARS_MILLENIUMS	(0xf<<28)	/* years millenium position */

/* MASK SHIFT TIME_REG & ALARM_TIME_REG*/
#घोषणा SECOND_SHIFT		0x00		/* seconds units */
#घोषणा MINUTE_SHIFT		0x08		/* minutes units position */
#घोषणा HOUR_SHIFT		0x10		/* hours units position */
#घोषणा MDAY_SHIFT		0x00		/* Month day shअगरt */
#घोषणा MONTH_SHIFT		0x08		/* Month shअगरt */
#घोषणा YEAR_SHIFT		0x10		/* Year shअगरt */

#घोषणा SECOND_MASK		0x7F
#घोषणा MIN_MASK		0x7F
#घोषणा HOUR_MASK		0x3F
#घोषणा DAY_MASK		0x3F
#घोषणा MONTH_MASK		0x7F
#घोषणा YEAR_MASK		0xFFFF

/* date reg equal to समय reg, क्रम debug only */
#घोषणा TIME_BYP		(1<<9)
#घोषणा INT_ENABLE		(1<<31)		/* पूर्णांकerrupt enable */

/* STATUS_REG */
#घोषणा CLK_UNCONNECTED		(1<<0)
#घोषणा PEND_WR_TIME		(1<<2)
#घोषणा PEND_WR_DATE		(1<<3)
#घोषणा LOST_WR_TIME		(1<<4)
#घोषणा LOST_WR_DATE		(1<<5)
#घोषणा RTC_INT_MASK		(1<<31)
#घोषणा STATUS_BUSY		(PEND_WR_TIME | PEND_WR_DATE)
#घोषणा STATUS_FAIL		(LOST_WR_TIME | LOST_WR_DATE)

काष्ठा spear_rtc_config अणु
	काष्ठा rtc_device *rtc;
	काष्ठा clk *clk;
	spinlock_t lock;
	व्योम __iomem *ioaddr;
	अचिन्हित पूर्णांक irq_wake;
पूर्ण;

अटल अंतरभूत व्योम spear_rtc_clear_पूर्णांकerrupt(काष्ठा spear_rtc_config *config)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&config->lock, flags);
	val = पढ़ोl(config->ioaddr + STATUS_REG);
	val |= RTC_INT_MASK;
	ग_लिखोl(val, config->ioaddr + STATUS_REG);
	spin_unlock_irqrestore(&config->lock, flags);
पूर्ण

अटल अंतरभूत व्योम spear_rtc_enable_पूर्णांकerrupt(काष्ठा spear_rtc_config *config)
अणु
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(config->ioaddr + CTRL_REG);
	अगर (!(val & INT_ENABLE)) अणु
		spear_rtc_clear_पूर्णांकerrupt(config);
		val |= INT_ENABLE;
		ग_लिखोl(val, config->ioaddr + CTRL_REG);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम spear_rtc_disable_पूर्णांकerrupt(काष्ठा spear_rtc_config *config)
अणु
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(config->ioaddr + CTRL_REG);
	अगर (val & INT_ENABLE) अणु
		val &= ~INT_ENABLE;
		ग_लिखोl(val, config->ioaddr + CTRL_REG);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_ग_लिखो_complete(काष्ठा spear_rtc_config *config)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&config->lock, flags);
	अगर ((पढ़ोl(config->ioaddr + STATUS_REG)) & STATUS_FAIL)
		ret = -EIO;
	spin_unlock_irqrestore(&config->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम rtc_रुको_not_busy(काष्ठा spear_rtc_config *config)
अणु
	पूर्णांक status, count = 0;
	अचिन्हित दीर्घ flags;

	/* Assuming BUSY may stay active क्रम 80 msec) */
	क्रम (count = 0; count < 80; count++) अणु
		spin_lock_irqsave(&config->lock, flags);
		status = पढ़ोl(config->ioaddr + STATUS_REG);
		spin_unlock_irqrestore(&config->lock, flags);
		अगर ((status & STATUS_BUSY) == 0)
			अवरोध;
		/* check status busy, after each msec */
		msleep(1);
	पूर्ण
पूर्ण

अटल irqवापस_t spear_rtc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spear_rtc_config *config = dev_id;
	अचिन्हित दीर्घ events = 0;
	अचिन्हित पूर्णांक irq_data;

	spin_lock(&config->lock);
	irq_data = पढ़ोl(config->ioaddr + STATUS_REG);
	spin_unlock(&config->lock);

	अगर ((irq_data & RTC_INT_MASK)) अणु
		spear_rtc_clear_पूर्णांकerrupt(config);
		events = RTC_IRQF | RTC_AF;
		rtc_update_irq(config->rtc, 1, events);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;

पूर्ण

अटल व्योम पंचांग2bcd(काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bin2bcd(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bin2bcd(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bin2bcd(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bin2bcd(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bin2bcd(पंचांग->पंचांग_mon + 1);
	पंचांग->पंचांग_year = bin2bcd(पंचांग->पंचांग_year);
पूर्ण

अटल व्योम bcd2पंचांग(काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon) - 1;
	/* epoch == 1900 */
	पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year);
पूर्ण

/*
 * spear_rtc_पढ़ो_समय - set the समय
 * @dev: rtc device in use
 * @पंचांग: holds date and समय
 *
 * This function पढ़ो समय and date. On success it will वापस 0
 * otherwise -ve error is वापसed.
 */
अटल पूर्णांक spear_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spear_rtc_config *config = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समय, date;

	/* we करोn't report wday/yday/isdst ... */
	rtc_रुको_not_busy(config);

	समय = पढ़ोl(config->ioaddr + TIME_REG);
	date = पढ़ोl(config->ioaddr + DATE_REG);
	पंचांग->पंचांग_sec = (समय >> SECOND_SHIFT) & SECOND_MASK;
	पंचांग->पंचांग_min = (समय >> MINUTE_SHIFT) & MIN_MASK;
	पंचांग->पंचांग_hour = (समय >> HOUR_SHIFT) & HOUR_MASK;
	पंचांग->पंचांग_mday = (date >> MDAY_SHIFT) & DAY_MASK;
	पंचांग->पंचांग_mon = (date >> MONTH_SHIFT) & MONTH_MASK;
	पंचांग->पंचांग_year = (date >> YEAR_SHIFT) & YEAR_MASK;

	bcd2पंचांग(पंचांग);
	वापस 0;
पूर्ण

/*
 * spear_rtc_set_समय - set the समय
 * @dev: rtc device in use
 * @पंचांग: holds date and समय
 *
 * This function set समय and date. On success it will वापस 0
 * otherwise -ve error is वापसed.
 */
अटल पूर्णांक spear_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा spear_rtc_config *config = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समय, date;

	पंचांग2bcd(पंचांग);

	rtc_रुको_not_busy(config);
	समय = (पंचांग->पंचांग_sec << SECOND_SHIFT) | (पंचांग->पंचांग_min << MINUTE_SHIFT) |
		(पंचांग->पंचांग_hour << HOUR_SHIFT);
	date = (पंचांग->पंचांग_mday << MDAY_SHIFT) | (पंचांग->पंचांग_mon << MONTH_SHIFT) |
		(पंचांग->पंचांग_year << YEAR_SHIFT);
	ग_लिखोl(समय, config->ioaddr + TIME_REG);
	ग_लिखोl(date, config->ioaddr + DATE_REG);

	वापस is_ग_लिखो_complete(config);
पूर्ण

/*
 * spear_rtc_पढ़ो_alarm - पढ़ो the alarm समय
 * @dev: rtc device in use
 * @alm: holds alarm date and समय
 *
 * This function पढ़ो alarm समय and date. On success it will वापस 0
 * otherwise -ve error is वापसed.
 */
अटल पूर्णांक spear_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा spear_rtc_config *config = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समय, date;

	rtc_रुको_not_busy(config);

	समय = पढ़ोl(config->ioaddr + ALARM_TIME_REG);
	date = पढ़ोl(config->ioaddr + ALARM_DATE_REG);
	alm->समय.पंचांग_sec = (समय >> SECOND_SHIFT) & SECOND_MASK;
	alm->समय.पंचांग_min = (समय >> MINUTE_SHIFT) & MIN_MASK;
	alm->समय.पंचांग_hour = (समय >> HOUR_SHIFT) & HOUR_MASK;
	alm->समय.पंचांग_mday = (date >> MDAY_SHIFT) & DAY_MASK;
	alm->समय.पंचांग_mon = (date >> MONTH_SHIFT) & MONTH_MASK;
	alm->समय.पंचांग_year = (date >> YEAR_SHIFT) & YEAR_MASK;

	bcd2पंचांग(&alm->समय);
	alm->enabled = पढ़ोl(config->ioaddr + CTRL_REG) & INT_ENABLE;

	वापस 0;
पूर्ण

/*
 * spear_rtc_set_alarm - set the alarm समय
 * @dev: rtc device in use
 * @alm: holds alarm date and समय
 *
 * This function set alarm समय and date. On success it will वापस 0
 * otherwise -ve error is वापसed.
 */
अटल पूर्णांक spear_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा spear_rtc_config *config = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक समय, date;
	पूर्णांक err;

	पंचांग2bcd(&alm->समय);

	rtc_रुको_not_busy(config);

	समय = (alm->समय.पंचांग_sec << SECOND_SHIFT) | (alm->समय.पंचांग_min <<
			MINUTE_SHIFT) |	(alm->समय.पंचांग_hour << HOUR_SHIFT);
	date = (alm->समय.पंचांग_mday << MDAY_SHIFT) | (alm->समय.पंचांग_mon <<
			MONTH_SHIFT) | (alm->समय.पंचांग_year << YEAR_SHIFT);

	ग_लिखोl(समय, config->ioaddr + ALARM_TIME_REG);
	ग_लिखोl(date, config->ioaddr + ALARM_DATE_REG);
	err = is_ग_लिखो_complete(config);
	अगर (err < 0)
		वापस err;

	अगर (alm->enabled)
		spear_rtc_enable_पूर्णांकerrupt(config);
	अन्यथा
		spear_rtc_disable_पूर्णांकerrupt(config);

	वापस 0;
पूर्ण

अटल पूर्णांक spear_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा spear_rtc_config *config = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	spear_rtc_clear_पूर्णांकerrupt(config);

	चयन (enabled) अणु
	हाल 0:
		/* alarm off */
		spear_rtc_disable_पूर्णांकerrupt(config);
		अवरोध;
	हाल 1:
		/* alarm on */
		spear_rtc_enable_पूर्णांकerrupt(config);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops spear_rtc_ops = अणु
	.पढ़ो_समय = spear_rtc_पढ़ो_समय,
	.set_समय = spear_rtc_set_समय,
	.पढ़ो_alarm = spear_rtc_पढ़ो_alarm,
	.set_alarm = spear_rtc_set_alarm,
	.alarm_irq_enable = spear_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक spear_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spear_rtc_config *config;
	पूर्णांक status = 0;
	पूर्णांक irq;

	config = devm_kzalloc(&pdev->dev, माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;

	/* alarm irqs */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	status = devm_request_irq(&pdev->dev, irq, spear_rtc_irq, 0, pdev->name,
			config);
	अगर (status) अणु
		dev_err(&pdev->dev, "Alarm interrupt IRQ%d already claimed\n",
				irq);
		वापस status;
	पूर्ण

	config->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(config->ioaddr))
		वापस PTR_ERR(config->ioaddr);

	config->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(config->clk))
		वापस PTR_ERR(config->clk);

	status = clk_prepare_enable(config->clk);
	अगर (status < 0)
		वापस status;

	spin_lock_init(&config->lock);
	platक्रमm_set_drvdata(pdev, config);

	config->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
					&spear_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(config->rtc)) अणु
		dev_err(&pdev->dev, "can't register RTC device, err %ld\n",
				PTR_ERR(config->rtc));
		status = PTR_ERR(config->rtc);
		जाओ err_disable_घड़ी;
	पूर्ण

	config->rtc->uie_unsupported = 1;

	अगर (!device_can_wakeup(&pdev->dev))
		device_init_wakeup(&pdev->dev, 1);

	वापस 0;

err_disable_घड़ी:
	clk_disable_unprepare(config->clk);

	वापस status;
पूर्ण

अटल पूर्णांक spear_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spear_rtc_config *config = platक्रमm_get_drvdata(pdev);

	spear_rtc_disable_पूर्णांकerrupt(config);
	clk_disable_unprepare(config->clk);
	device_init_wakeup(&pdev->dev, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक spear_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा spear_rtc_config *config = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (!enable_irq_wake(irq))
			config->irq_wake = 1;
	पूर्ण अन्यथा अणु
		spear_rtc_disable_पूर्णांकerrupt(config);
		clk_disable(config->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spear_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा spear_rtc_config *config = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (config->irq_wake) अणु
			disable_irq_wake(irq);
			config->irq_wake = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_enable(config->clk);
		spear_rtc_enable_पूर्णांकerrupt(config);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(spear_rtc_pm_ops, spear_rtc_suspend, spear_rtc_resume);

अटल व्योम spear_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spear_rtc_config *config = platक्रमm_get_drvdata(pdev);

	spear_rtc_disable_पूर्णांकerrupt(config);
	clk_disable(config->clk);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spear_rtc_id_table[] = अणु
	अणु .compatible = "st,spear600-rtc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_rtc_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spear_rtc_driver = अणु
	.probe = spear_rtc_probe,
	.हटाओ = spear_rtc_हटाओ,
	.shutकरोwn = spear_rtc_shutकरोwn,
	.driver = अणु
		.name = "rtc-spear",
		.pm = &spear_rtc_pm_ops,
		.of_match_table = of_match_ptr(spear_rtc_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spear_rtc_driver);

MODULE_ALIAS("platform:rtc-spear");
MODULE_AUTHOR("Rajeev Kumar <rajeev-dlh.kumar@st.com>");
MODULE_DESCRIPTION("ST SPEAr Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL");
