<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Zhao Zhang <zhzhl555@gmail.com>
 *
 * Derived from driver/rtc/rtc-au1xxx.c
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <loongson1.h>

#घोषणा LS1X_RTC_REG_OFFSET	(LS1X_RTC_BASE + 0x20)
#घोषणा LS1X_RTC_REGS(x) \
		((व्योम __iomem *)KSEG1ADDR(LS1X_RTC_REG_OFFSET + (x)))

/*RTC programmable counters 0 and 1*/
#घोषणा SYS_COUNTER_CNTRL		(LS1X_RTC_REGS(0x20))
#घोषणा SYS_CNTRL_ERS			(1 << 23)
#घोषणा SYS_CNTRL_RTS			(1 << 20)
#घोषणा SYS_CNTRL_RM2			(1 << 19)
#घोषणा SYS_CNTRL_RM1			(1 << 18)
#घोषणा SYS_CNTRL_RM0			(1 << 17)
#घोषणा SYS_CNTRL_RS			(1 << 16)
#घोषणा SYS_CNTRL_BP			(1 << 14)
#घोषणा SYS_CNTRL_REN			(1 << 13)
#घोषणा SYS_CNTRL_BRT			(1 << 12)
#घोषणा SYS_CNTRL_TEN			(1 << 11)
#घोषणा SYS_CNTRL_BTT			(1 << 10)
#घोषणा SYS_CNTRL_E0			(1 << 8)
#घोषणा SYS_CNTRL_ETS			(1 << 7)
#घोषणा SYS_CNTRL_32S			(1 << 5)
#घोषणा SYS_CNTRL_TTS			(1 << 4)
#घोषणा SYS_CNTRL_TM2			(1 << 3)
#घोषणा SYS_CNTRL_TM1			(1 << 2)
#घोषणा SYS_CNTRL_TM0			(1 << 1)
#घोषणा SYS_CNTRL_TS			(1 << 0)

/* Programmable Counter 0 Registers */
#घोषणा SYS_TOYTRIM		(LS1X_RTC_REGS(0))
#घोषणा SYS_TOYWRITE0		(LS1X_RTC_REGS(4))
#घोषणा SYS_TOYWRITE1		(LS1X_RTC_REGS(8))
#घोषणा SYS_TOYREAD0		(LS1X_RTC_REGS(0xC))
#घोषणा SYS_TOYREAD1		(LS1X_RTC_REGS(0x10))
#घोषणा SYS_TOYMATCH0		(LS1X_RTC_REGS(0x14))
#घोषणा SYS_TOYMATCH1		(LS1X_RTC_REGS(0x18))
#घोषणा SYS_TOYMATCH2		(LS1X_RTC_REGS(0x1C))

/* Programmable Counter 1 Registers */
#घोषणा SYS_RTCTRIM		(LS1X_RTC_REGS(0x40))
#घोषणा SYS_RTCWRITE0		(LS1X_RTC_REGS(0x44))
#घोषणा SYS_RTCREAD0		(LS1X_RTC_REGS(0x48))
#घोषणा SYS_RTCMATCH0		(LS1X_RTC_REGS(0x4C))
#घोषणा SYS_RTCMATCH1		(LS1X_RTC_REGS(0x50))
#घोषणा SYS_RTCMATCH2		(LS1X_RTC_REGS(0x54))

#घोषणा LS1X_SEC_OFFSET		(4)
#घोषणा LS1X_MIN_OFFSET		(10)
#घोषणा LS1X_HOUR_OFFSET	(16)
#घोषणा LS1X_DAY_OFFSET		(21)
#घोषणा LS1X_MONTH_OFFSET	(26)


#घोषणा LS1X_SEC_MASK		(0x3f)
#घोषणा LS1X_MIN_MASK		(0x3f)
#घोषणा LS1X_HOUR_MASK		(0x1f)
#घोषणा LS1X_DAY_MASK		(0x1f)
#घोषणा LS1X_MONTH_MASK		(0x3f)
#घोषणा LS1X_YEAR_MASK		(0xffffffff)

#घोषणा ls1x_get_sec(t)		(((t) >> LS1X_SEC_OFFSET) & LS1X_SEC_MASK)
#घोषणा ls1x_get_min(t)		(((t) >> LS1X_MIN_OFFSET) & LS1X_MIN_MASK)
#घोषणा ls1x_get_hour(t)	(((t) >> LS1X_HOUR_OFFSET) & LS1X_HOUR_MASK)
#घोषणा ls1x_get_day(t)		(((t) >> LS1X_DAY_OFFSET) & LS1X_DAY_MASK)
#घोषणा ls1x_get_month(t)	(((t) >> LS1X_MONTH_OFFSET) & LS1X_MONTH_MASK)

#घोषणा RTC_CNTR_OK (SYS_CNTRL_E0 | SYS_CNTRL_32S)

अटल पूर्णांक ls1x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *rपंचांग)
अणु
	अचिन्हित दीर्घ v;
	समय64_t t;

	v = पढ़ोl(SYS_TOYREAD0);
	t = पढ़ोl(SYS_TOYREAD1);

	स_रखो(rपंचांग, 0, माप(काष्ठा rtc_समय));
	t  = स_गढ़ो64((t & LS1X_YEAR_MASK), ls1x_get_month(v),
			ls1x_get_day(v), ls1x_get_hour(v),
			ls1x_get_min(v), ls1x_get_sec(v));
	rtc_समय64_to_पंचांग(t, rपंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_rtc_set_समय(काष्ठा device *dev, काष्ठा  rtc_समय *rपंचांग)
अणु
	अचिन्हित दीर्घ v, t, c;
	पूर्णांक ret = -ETIMEDOUT;

	v = ((rपंचांग->पंचांग_mon + 1)  << LS1X_MONTH_OFFSET)
		| (rपंचांग->पंचांग_mday << LS1X_DAY_OFFSET)
		| (rपंचांग->पंचांग_hour << LS1X_HOUR_OFFSET)
		| (rपंचांग->पंचांग_min  << LS1X_MIN_OFFSET)
		| (rपंचांग->पंचांग_sec  << LS1X_SEC_OFFSET);

	ग_लिखोl(v, SYS_TOYWRITE0);
	c = 0x10000;
	/* add समयout check counter, क्रम more safe */
	जबतक ((पढ़ोl(SYS_COUNTER_CNTRL) & SYS_CNTRL_TS) && --c)
		usleep_range(1000, 3000);

	अगर (!c) अणु
		dev_err(dev, "set time timeout!\n");
		जाओ err;
	पूर्ण

	t = rपंचांग->पंचांग_year + 1900;
	ग_लिखोl(t, SYS_TOYWRITE1);
	c = 0x10000;
	जबतक ((पढ़ोl(SYS_COUNTER_CNTRL) & SYS_CNTRL_TS) && --c)
		usleep_range(1000, 3000);

	अगर (!c) अणु
		dev_err(dev, "set time timeout!\n");
		जाओ err;
	पूर्ण
	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops  ls1x_rtc_ops = अणु
	.पढ़ो_समय	= ls1x_rtc_पढ़ो_समय,
	.set_समय	= ls1x_rtc_set_समय,
पूर्ण;

अटल पूर्णांक ls1x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtcdev;
	अचिन्हित दीर्घ v;

	v = पढ़ोl(SYS_COUNTER_CNTRL);
	अगर (!(v & RTC_CNTR_OK)) अणु
		dev_err(&pdev->dev, "rtc counters not working\n");
		वापस -ENODEV;
	पूर्ण

	/* set to 1 HZ अगर needed */
	अगर (पढ़ोl(SYS_TOYTRIM) != 32767) अणु
		v = 0x100000;
		जबतक ((पढ़ोl(SYS_COUNTER_CNTRL) & SYS_CNTRL_TTS) && --v)
			usleep_range(1000, 3000);

		अगर (!v) अणु
			dev_err(&pdev->dev, "time out\n");
			वापस -ETIMEDOUT;
		पूर्ण
		ग_लिखोl(32767, SYS_TOYTRIM);
	पूर्ण
	/* this loop coundn't be endless */
	जबतक (पढ़ोl(SYS_COUNTER_CNTRL) & SYS_CNTRL_TTS)
		usleep_range(1000, 3000);

	rtcdev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtcdev))
		वापस PTR_ERR(rtcdev);

	platक्रमm_set_drvdata(pdev, rtcdev);
	rtcdev->ops = &ls1x_rtc_ops;
	rtcdev->range_min = RTC_TIMESTAMP_BEGIN_1900;
	rtcdev->range_max = RTC_TIMESTAMP_END_2099;

	वापस devm_rtc_रेजिस्टर_device(rtcdev);
पूर्ण

अटल काष्ठा platक्रमm_driver  ls1x_rtc_driver = अणु
	.driver		= अणु
		.name	= "ls1x-rtc",
	पूर्ण,
	.probe		= ls1x_rtc_probe,
पूर्ण;

module_platक्रमm_driver(ls1x_rtc_driver);

MODULE_AUTHOR("zhao zhang <zhzhl555@gmail.com>");
MODULE_LICENSE("GPL");
