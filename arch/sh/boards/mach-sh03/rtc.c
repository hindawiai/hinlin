<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/sh03/rtc.c -- CTP/PCI-SH03 on-chip RTC support
 *
 *  Copyright (C) 2004  Saito.K & Jeanne(ksaito@पूर्णांकerface.co.jp)
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/bcd.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा RTC_BASE	0xb0000000
#घोषणा RTC_SEC1	(RTC_BASE + 0)
#घोषणा RTC_SEC10	(RTC_BASE + 1)
#घोषणा RTC_MIN1	(RTC_BASE + 2)
#घोषणा RTC_MIN10	(RTC_BASE + 3)
#घोषणा RTC_HOU1	(RTC_BASE + 4)
#घोषणा RTC_HOU10	(RTC_BASE + 5)
#घोषणा RTC_WEE1	(RTC_BASE + 6)
#घोषणा RTC_DAY1	(RTC_BASE + 7)
#घोषणा RTC_DAY10	(RTC_BASE + 8)
#घोषणा RTC_MON1	(RTC_BASE + 9)
#घोषणा RTC_MON10	(RTC_BASE + 10)
#घोषणा RTC_YEA1	(RTC_BASE + 11)
#घोषणा RTC_YEA10	(RTC_BASE + 12)
#घोषणा RTC_YEA100	(RTC_BASE + 13)
#घोषणा RTC_YEA1000	(RTC_BASE + 14)
#घोषणा RTC_CTL		(RTC_BASE + 15)
#घोषणा RTC_BUSY	1
#घोषणा RTC_STOP	2

अटल DEFINE_SPINLOCK(sh03_rtc_lock);

अटल पूर्णांक sh03_rtc_समय_लोofday(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित पूर्णांक year, mon, day, hour, min, sec;

	spin_lock(&sh03_rtc_lock);
 again:
	करो अणु
		sec  = (__raw_पढ़ोb(RTC_SEC1) & 0xf) + (__raw_पढ़ोb(RTC_SEC10) & 0x7) * 10;
		min  = (__raw_पढ़ोb(RTC_MIN1) & 0xf) + (__raw_पढ़ोb(RTC_MIN10) & 0xf) * 10;
		hour = (__raw_पढ़ोb(RTC_HOU1) & 0xf) + (__raw_पढ़ोb(RTC_HOU10) & 0xf) * 10;
		day  = (__raw_पढ़ोb(RTC_DAY1) & 0xf) + (__raw_पढ़ोb(RTC_DAY10) & 0xf) * 10;
		mon  = (__raw_पढ़ोb(RTC_MON1) & 0xf) + (__raw_पढ़ोb(RTC_MON10) & 0xf) * 10;
		year = (__raw_पढ़ोb(RTC_YEA1) & 0xf) + (__raw_पढ़ोb(RTC_YEA10) & 0xf) * 10
		     + (__raw_पढ़ोb(RTC_YEA100 ) & 0xf) * 100
		     + (__raw_पढ़ोb(RTC_YEA1000) & 0xf) * 1000;
	पूर्ण जबतक (sec != (__raw_पढ़ोb(RTC_SEC1) & 0xf) + (__raw_पढ़ोb(RTC_SEC10) & 0x7) * 10);
	अगर (year == 0 || mon < 1 || mon > 12 || day > 31 || day < 1 ||
	    hour > 23 || min > 59 || sec > 59) अणु
		prपूर्णांकk(KERN_ERR
		       "SH-03 RTC: invalid value, resetting to 1 Jan 2000\n");
		prपूर्णांकk("year=%d, mon=%d, day=%d, hour=%d, min=%d, sec=%d\n",
		       year, mon, day, hour, min, sec);

		__raw_ग_लिखोb(0, RTC_SEC1); __raw_ग_लिखोb(0, RTC_SEC10);
		__raw_ग_लिखोb(0, RTC_MIN1); __raw_ग_लिखोb(0, RTC_MIN10);
		__raw_ग_लिखोb(0, RTC_HOU1); __raw_ग_लिखोb(0, RTC_HOU10);
		__raw_ग_लिखोb(6, RTC_WEE1);
		__raw_ग_लिखोb(1, RTC_DAY1); __raw_ग_लिखोb(0, RTC_DAY10);
		__raw_ग_लिखोb(1, RTC_MON1); __raw_ग_लिखोb(0, RTC_MON10);
		__raw_ग_लिखोb(0, RTC_YEA1); __raw_ग_लिखोb(0, RTC_YEA10);
		__raw_ग_लिखोb(0, RTC_YEA100);
		__raw_ग_लिखोb(2, RTC_YEA1000);
		__raw_ग_लिखोb(0, RTC_CTL);
		जाओ again;
	पूर्ण

	spin_unlock(&sh03_rtc_lock);

	पंचांग->पंचांग_sec  = sec;
	पंचांग->पंचांग_min  = min;
	पंचांग->पंचांग_hour = hour;
	पंचांग->पंचांग_mday = day;
	पंचांग->पंचांग_mon  = mon;
	पंचांग->पंचांग_year = year - 1900;

	वापस 0;
पूर्ण

अटल पूर्णांक set_rtc_mmss(काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक retval = 0;
	पूर्णांक real_seconds, real_minutes, cmos_minutes;
	पूर्णांक i;

	/* माला_लो recalled with irq locally disabled */
	spin_lock(&sh03_rtc_lock);
	क्रम (i = 0 ; i < 1000000 ; i++)	/* may take up to 1 second... */
		अगर (!(__raw_पढ़ोb(RTC_CTL) & RTC_BUSY))
			अवरोध;
	cmos_minutes = (__raw_पढ़ोb(RTC_MIN1) & 0xf) + (__raw_पढ़ोb(RTC_MIN10) & 0xf) * 10;
	real_seconds = पंचांग->पंचांग_sec;
	real_minutes = पंचांग->पंचांग_min;
	अगर (((असल(real_minutes - cmos_minutes) + 15)/30) & 1)
		real_minutes += 30;		/* correct क्रम half hour समय zone */
	real_minutes %= 60;

	अगर (असल(real_minutes - cmos_minutes) < 30) अणु
		__raw_ग_लिखोb(real_seconds % 10, RTC_SEC1);
		__raw_ग_लिखोb(real_seconds / 10, RTC_SEC10);
		__raw_ग_लिखोb(real_minutes % 10, RTC_MIN1);
		__raw_ग_लिखोb(real_minutes / 10, RTC_MIN10);
	पूर्ण अन्यथा अणु
		prपूर्णांकk_once(KERN_NOTICE
		       "set_rtc_mmss: can't update from %d to %d\n",
		       cmos_minutes, real_minutes);
		retval = -EINVAL;
	पूर्ण
	spin_unlock(&sh03_rtc_lock);

	वापस retval;
पूर्ण

पूर्णांक sh03_rtc_समय_रखोofday(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	वापस set_rtc_mmss(पंचांग);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_generic_ops = अणु
	.पढ़ो_समय = sh03_rtc_समय_लोofday,
	.set_समय = sh03_rtc_समय_रखोofday,
पूर्ण;

अटल पूर्णांक __init sh03_समय_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "rtc-generic", -1,
					     &rtc_generic_ops,
					     माप(rtc_generic_ops));

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
arch_initcall(sh03_समय_init);
