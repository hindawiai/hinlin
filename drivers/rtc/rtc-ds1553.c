<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An rtc driver क्रम the Dallas DS1553
 *
 * Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */

#समावेश <linux/bcd.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#घोषणा RTC_REG_SIZE		0x2000
#घोषणा RTC_OFFSET		0x1ff0

#घोषणा RTC_FLAGS		(RTC_OFFSET + 0)
#घोषणा RTC_SECONDS_ALARM	(RTC_OFFSET + 2)
#घोषणा RTC_MINUTES_ALARM	(RTC_OFFSET + 3)
#घोषणा RTC_HOURS_ALARM		(RTC_OFFSET + 4)
#घोषणा RTC_DATE_ALARM		(RTC_OFFSET + 5)
#घोषणा RTC_INTERRUPTS		(RTC_OFFSET + 6)
#घोषणा RTC_WATCHDOG		(RTC_OFFSET + 7)
#घोषणा RTC_CONTROL		(RTC_OFFSET + 8)
#घोषणा RTC_CENTURY		(RTC_OFFSET + 8)
#घोषणा RTC_SECONDS		(RTC_OFFSET + 9)
#घोषणा RTC_MINUTES		(RTC_OFFSET + 10)
#घोषणा RTC_HOURS		(RTC_OFFSET + 11)
#घोषणा RTC_DAY			(RTC_OFFSET + 12)
#घोषणा RTC_DATE		(RTC_OFFSET + 13)
#घोषणा RTC_MONTH		(RTC_OFFSET + 14)
#घोषणा RTC_YEAR		(RTC_OFFSET + 15)

#घोषणा RTC_CENTURY_MASK	0x3f
#घोषणा RTC_SECONDS_MASK	0x7f
#घोषणा RTC_DAY_MASK		0x07

/* Bits in the Control/Century रेजिस्टर */
#घोषणा RTC_WRITE		0x80
#घोषणा RTC_READ		0x40

/* Bits in the Seconds रेजिस्टर */
#घोषणा RTC_STOP		0x80

/* Bits in the Flags रेजिस्टर */
#घोषणा RTC_FLAGS_AF		0x40
#घोषणा RTC_FLAGS_BLF		0x10

/* Bits in the Interrupts रेजिस्टर */
#घोषणा RTC_INTS_AE		0x80

काष्ठा rtc_plat_data अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;
	अचिन्हित दीर्घ last_jअगरfies;
	पूर्णांक irq;
	अचिन्हित पूर्णांक irqen;
	पूर्णांक alrm_sec;
	पूर्णांक alrm_min;
	पूर्णांक alrm_hour;
	पूर्णांक alrm_mday;
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक ds1553_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u8 century;

	century = bin2bcd((पंचांग->पंचांग_year + 1900) / 100);

	ग_लिखोb(RTC_WRITE, pdata->ioaddr + RTC_CONTROL);

	ग_लिखोb(bin2bcd(पंचांग->पंचांग_year % 100), ioaddr + RTC_YEAR);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), ioaddr + RTC_MONTH);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_wday) & RTC_DAY_MASK, ioaddr + RTC_DAY);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), ioaddr + RTC_DATE);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), ioaddr + RTC_HOURS);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_min), ioaddr + RTC_MINUTES);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec) & RTC_SECONDS_MASK, ioaddr + RTC_SECONDS);

	/* RTC_CENTURY and RTC_CONTROL share same रेजिस्टर */
	ग_लिखोb(RTC_WRITE | (century & RTC_CENTURY_MASK), ioaddr + RTC_CENTURY);
	ग_लिखोb(century & RTC_CENTURY_MASK, ioaddr + RTC_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1553_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	अचिन्हित पूर्णांक year, month, day, hour, minute, second, week;
	अचिन्हित पूर्णांक century;

	/* give enough समय to update RTC in हाल of continuous पढ़ो */
	अगर (pdata->last_jअगरfies == jअगरfies)
		msleep(1);
	pdata->last_jअगरfies = jअगरfies;
	ग_लिखोb(RTC_READ, ioaddr + RTC_CONTROL);
	second = पढ़ोb(ioaddr + RTC_SECONDS) & RTC_SECONDS_MASK;
	minute = पढ़ोb(ioaddr + RTC_MINUTES);
	hour = पढ़ोb(ioaddr + RTC_HOURS);
	day = पढ़ोb(ioaddr + RTC_DATE);
	week = पढ़ोb(ioaddr + RTC_DAY) & RTC_DAY_MASK;
	month = पढ़ोb(ioaddr + RTC_MONTH);
	year = पढ़ोb(ioaddr + RTC_YEAR);
	century = पढ़ोb(ioaddr + RTC_CENTURY) & RTC_CENTURY_MASK;
	ग_लिखोb(0, ioaddr + RTC_CONTROL);
	पंचांग->पंचांग_sec = bcd2bin(second);
	पंचांग->पंचांग_min = bcd2bin(minute);
	पंचांग->पंचांग_hour = bcd2bin(hour);
	पंचांग->पंचांग_mday = bcd2bin(day);
	पंचांग->पंचांग_wday = bcd2bin(week);
	पंचांग->पंचांग_mon = bcd2bin(month) - 1;
	/* year is 1900 + पंचांग->पंचांग_year */
	पंचांग->पंचांग_year = bcd2bin(year) + bcd2bin(century) * 100 - 1900;

	वापस 0;
पूर्ण

अटल व्योम ds1553_rtc_update_alarm(काष्ठा rtc_plat_data *pdata)
अणु
	व्योम __iomem *ioaddr = pdata->ioaddr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->lock, flags);
	ग_लिखोb(pdata->alrm_mday < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_mday),
	       ioaddr + RTC_DATE_ALARM);
	ग_लिखोb(pdata->alrm_hour < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_hour),
	       ioaddr + RTC_HOURS_ALARM);
	ग_लिखोb(pdata->alrm_min < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_min),
	       ioaddr + RTC_MINUTES_ALARM);
	ग_लिखोb(pdata->alrm_sec < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_sec),
	       ioaddr + RTC_SECONDS_ALARM);
	ग_लिखोb(pdata->irqen ? RTC_INTS_AE : 0, ioaddr + RTC_INTERRUPTS);
	पढ़ोb(ioaddr + RTC_FLAGS);	/* clear पूर्णांकerrupts */
	spin_unlock_irqrestore(&pdata->lock, flags);
पूर्ण

अटल पूर्णांक ds1553_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);

	अगर (pdata->irq <= 0)
		वापस -EINVAL;
	pdata->alrm_mday = alrm->समय.पंचांग_mday;
	pdata->alrm_hour = alrm->समय.पंचांग_hour;
	pdata->alrm_min = alrm->समय.पंचांग_min;
	pdata->alrm_sec = alrm->समय.पंचांग_sec;
	अगर (alrm->enabled)
		pdata->irqen |= RTC_AF;
	ds1553_rtc_update_alarm(pdata);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1553_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);

	अगर (pdata->irq <= 0)
		वापस -EINVAL;
	alrm->समय.पंचांग_mday = pdata->alrm_mday < 0 ? 0 : pdata->alrm_mday;
	alrm->समय.पंचांग_hour = pdata->alrm_hour < 0 ? 0 : pdata->alrm_hour;
	alrm->समय.पंचांग_min = pdata->alrm_min < 0 ? 0 : pdata->alrm_min;
	alrm->समय.पंचांग_sec = pdata->alrm_sec < 0 ? 0 : pdata->alrm_sec;
	alrm->enabled = (pdata->irqen & RTC_AF) ? 1 : 0;
	वापस 0;
पूर्ण

अटल irqवापस_t ds1553_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा rtc_plat_data *pdata = platक्रमm_get_drvdata(pdev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	अचिन्हित दीर्घ events = 0;

	spin_lock(&pdata->lock);
	/* पढ़ो and clear पूर्णांकerrupt */
	अगर (पढ़ोb(ioaddr + RTC_FLAGS) & RTC_FLAGS_AF) अणु
		events = RTC_IRQF;
		अगर (पढ़ोb(ioaddr + RTC_SECONDS_ALARM) & 0x80)
			events |= RTC_UF;
		अन्यथा
			events |= RTC_AF;
		rtc_update_irq(pdata->rtc, 1, events);
	पूर्ण
	spin_unlock(&pdata->lock);
	वापस events ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक ds1553_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);

	अगर (pdata->irq <= 0)
		वापस -EINVAL;
	अगर (enabled)
		pdata->irqen |= RTC_AF;
	अन्यथा
		pdata->irqen &= ~RTC_AF;
	ds1553_rtc_update_alarm(pdata);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1553_rtc_ops = अणु
	.पढ़ो_समय		= ds1553_rtc_पढ़ो_समय,
	.set_समय		= ds1553_rtc_set_समय,
	.पढ़ो_alarm		= ds1553_rtc_पढ़ो_alarm,
	.set_alarm		= ds1553_rtc_set_alarm,
	.alarm_irq_enable	= ds1553_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक ds1553_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा platक्रमm_device *pdev = priv;
	काष्ठा rtc_plat_data *pdata = platक्रमm_get_drvdata(pdev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u8 *buf = val;

	क्रम (; bytes; bytes--)
		*buf++ = पढ़ोb(ioaddr + pos++);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1553_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा platक्रमm_device *pdev = priv;
	काष्ठा rtc_plat_data *pdata = platक्रमm_get_drvdata(pdev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u8 *buf = val;

	क्रम (; bytes; bytes--)
		ग_लिखोb(*buf++, ioaddr + pos++);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1553_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक cen, sec;
	काष्ठा rtc_plat_data *pdata;
	व्योम __iomem *ioaddr;
	पूर्णांक ret = 0;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "ds1553_nvram",
		.word_size = 1,
		.stride = 1,
		.size = RTC_OFFSET,
		.reg_पढ़ो = ds1553_nvram_पढ़ो,
		.reg_ग_लिखो = ds1553_nvram_ग_लिखो,
		.priv = pdev,
	पूर्ण;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ioaddr))
		वापस PTR_ERR(ioaddr);
	pdata->ioaddr = ioaddr;
	pdata->irq = platक्रमm_get_irq(pdev, 0);

	/* turn RTC on अगर it was not on */
	sec = पढ़ोb(ioaddr + RTC_SECONDS);
	अगर (sec & RTC_STOP) अणु
		sec &= RTC_SECONDS_MASK;
		cen = पढ़ोb(ioaddr + RTC_CENTURY) & RTC_CENTURY_MASK;
		ग_लिखोb(RTC_WRITE, ioaddr + RTC_CONTROL);
		ग_लिखोb(sec, ioaddr + RTC_SECONDS);
		ग_लिखोb(cen & RTC_CENTURY_MASK, ioaddr + RTC_CONTROL);
	पूर्ण
	अगर (पढ़ोb(ioaddr + RTC_FLAGS) & RTC_FLAGS_BLF)
		dev_warn(&pdev->dev, "voltage-low detected.\n");

	spin_lock_init(&pdata->lock);
	pdata->last_jअगरfies = jअगरfies;
	platक्रमm_set_drvdata(pdev, pdata);

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc))
		वापस PTR_ERR(pdata->rtc);

	pdata->rtc->ops = &ds1553_rtc_ops;

	ret = devm_rtc_रेजिस्टर_device(pdata->rtc);
	अगर (ret)
		वापस ret;

	अगर (pdata->irq > 0) अणु
		ग_लिखोb(0, ioaddr + RTC_INTERRUPTS);
		अगर (devm_request_irq(&pdev->dev, pdata->irq,
				ds1553_rtc_पूर्णांकerrupt,
				0, pdev->name, pdev) < 0) अणु
			dev_warn(&pdev->dev, "interrupt not available.\n");
			pdata->irq = 0;
		पूर्ण
	पूर्ण

	devm_rtc_nvmem_रेजिस्टर(pdata->rtc, &nvmem_cfg);

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:rtc-ds1553");

अटल काष्ठा platक्रमm_driver ds1553_rtc_driver = अणु
	.probe		= ds1553_rtc_probe,
	.driver		= अणु
		.name	= "rtc-ds1553",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ds1553_rtc_driver);

MODULE_AUTHOR("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODULE_DESCRIPTION("Dallas DS1553 RTC driver");
MODULE_LICENSE("GPL");
