<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A RTC driver क्रम the Simtek STK17TA8
 *
 * By Thomas Hommel <thomas.hommel@ge.com>
 *
 * Based on the DS1553 driver from
 * Atsushi Nemoto <anemo@mba.ocn.ne.jp>
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

#घोषणा RTC_REG_SIZE		0x20000
#घोषणा RTC_OFFSET		0x1fff0

#घोषणा RTC_FLAGS		(RTC_OFFSET + 0)
#घोषणा RTC_CENTURY		(RTC_OFFSET + 1)
#घोषणा RTC_SECONDS_ALARM	(RTC_OFFSET + 2)
#घोषणा RTC_MINUTES_ALARM	(RTC_OFFSET + 3)
#घोषणा RTC_HOURS_ALARM		(RTC_OFFSET + 4)
#घोषणा RTC_DATE_ALARM		(RTC_OFFSET + 5)
#घोषणा RTC_INTERRUPTS		(RTC_OFFSET + 6)
#घोषणा RTC_WATCHDOG		(RTC_OFFSET + 7)
#घोषणा RTC_CALIBRATION		(RTC_OFFSET + 8)
#घोषणा RTC_SECONDS		(RTC_OFFSET + 9)
#घोषणा RTC_MINUTES		(RTC_OFFSET + 10)
#घोषणा RTC_HOURS		(RTC_OFFSET + 11)
#घोषणा RTC_DAY			(RTC_OFFSET + 12)
#घोषणा RTC_DATE		(RTC_OFFSET + 13)
#घोषणा RTC_MONTH		(RTC_OFFSET + 14)
#घोषणा RTC_YEAR		(RTC_OFFSET + 15)

#घोषणा RTC_SECONDS_MASK	0x7f
#घोषणा RTC_DAY_MASK		0x07
#घोषणा RTC_CAL_MASK		0x3f

/* Bits in the Calibration रेजिस्टर */
#घोषणा RTC_STOP		0x80

/* Bits in the Flags रेजिस्टर */
#घोषणा RTC_FLAGS_AF		0x40
#घोषणा RTC_FLAGS_PF		0x20
#घोषणा RTC_WRITE		0x02
#घोषणा RTC_READ		0x01

/* Bits in the Interrupts रेजिस्टर */
#घोषणा RTC_INTS_AIE		0x40

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

अटल पूर्णांक stk17ta8_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u8 flags;

	flags = पढ़ोb(pdata->ioaddr + RTC_FLAGS);
	ग_लिखोb(flags | RTC_WRITE, pdata->ioaddr + RTC_FLAGS);

	ग_लिखोb(bin2bcd(पंचांग->पंचांग_year % 100), ioaddr + RTC_YEAR);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), ioaddr + RTC_MONTH);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_wday) & RTC_DAY_MASK, ioaddr + RTC_DAY);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), ioaddr + RTC_DATE);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), ioaddr + RTC_HOURS);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_min), ioaddr + RTC_MINUTES);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec) & RTC_SECONDS_MASK, ioaddr + RTC_SECONDS);
	ग_लिखोb(bin2bcd((पंचांग->पंचांग_year + 1900) / 100), ioaddr + RTC_CENTURY);

	ग_लिखोb(flags & ~RTC_WRITE, pdata->ioaddr + RTC_FLAGS);
	वापस 0;
पूर्ण

अटल पूर्णांक stk17ta8_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	अचिन्हित पूर्णांक year, month, day, hour, minute, second, week;
	अचिन्हित पूर्णांक century;
	u8 flags;

	/* give enough समय to update RTC in हाल of continuous पढ़ो */
	अगर (pdata->last_jअगरfies == jअगरfies)
		msleep(1);
	pdata->last_jअगरfies = jअगरfies;

	flags = पढ़ोb(pdata->ioaddr + RTC_FLAGS);
	ग_लिखोb(flags | RTC_READ, ioaddr + RTC_FLAGS);
	second = पढ़ोb(ioaddr + RTC_SECONDS) & RTC_SECONDS_MASK;
	minute = पढ़ोb(ioaddr + RTC_MINUTES);
	hour = पढ़ोb(ioaddr + RTC_HOURS);
	day = पढ़ोb(ioaddr + RTC_DATE);
	week = पढ़ोb(ioaddr + RTC_DAY) & RTC_DAY_MASK;
	month = पढ़ोb(ioaddr + RTC_MONTH);
	year = पढ़ोb(ioaddr + RTC_YEAR);
	century = पढ़ोb(ioaddr + RTC_CENTURY);
	ग_लिखोb(flags & ~RTC_READ, ioaddr + RTC_FLAGS);
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

अटल व्योम stk17ta8_rtc_update_alarm(काष्ठा rtc_plat_data *pdata)
अणु
	व्योम __iomem *ioaddr = pdata->ioaddr;
	अचिन्हित दीर्घ irqflags;
	u8 flags;

	spin_lock_irqsave(&pdata->lock, irqflags);

	flags = पढ़ोb(ioaddr + RTC_FLAGS);
	ग_लिखोb(flags | RTC_WRITE, ioaddr + RTC_FLAGS);

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
	ग_लिखोb(pdata->irqen ? RTC_INTS_AIE : 0, ioaddr + RTC_INTERRUPTS);
	पढ़ोb(ioaddr + RTC_FLAGS);	/* clear पूर्णांकerrupts */
	ग_लिखोb(flags & ~RTC_WRITE, ioaddr + RTC_FLAGS);
	spin_unlock_irqrestore(&pdata->lock, irqflags);
पूर्ण

अटल पूर्णांक stk17ta8_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
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
	stk17ta8_rtc_update_alarm(pdata);
	वापस 0;
पूर्ण

अटल पूर्णांक stk17ta8_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
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

अटल irqवापस_t stk17ta8_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
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

अटल पूर्णांक stk17ta8_rtc_alarm_irq_enable(काष्ठा device *dev,
	अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);

	अगर (pdata->irq <= 0)
		वापस -EINVAL;
	अगर (enabled)
		pdata->irqen |= RTC_AF;
	अन्यथा
		pdata->irqen &= ~RTC_AF;
	stk17ta8_rtc_update_alarm(pdata);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops stk17ta8_rtc_ops = अणु
	.पढ़ो_समय		= stk17ta8_rtc_पढ़ो_समय,
	.set_समय		= stk17ta8_rtc_set_समय,
	.पढ़ो_alarm		= stk17ta8_rtc_पढ़ो_alarm,
	.set_alarm		= stk17ta8_rtc_set_alarm,
	.alarm_irq_enable	= stk17ta8_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक stk17ta8_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			       माप_प्रकार bytes)
अणु
	काष्ठा rtc_plat_data *pdata = priv;
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u8 *buf = val;

	क्रम (; bytes; bytes--)
		*buf++ = पढ़ोb(ioaddr + pos++);
	वापस 0;
पूर्ण

अटल पूर्णांक stk17ta8_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
				माप_प्रकार bytes)
अणु
	काष्ठा rtc_plat_data *pdata = priv;
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u8 *buf = val;

	क्रम (; bytes; bytes--)
		ग_लिखोb(*buf++, ioaddr + pos++);
	वापस 0;
पूर्ण

अटल पूर्णांक stk17ta8_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक cal;
	अचिन्हित पूर्णांक flags;
	काष्ठा rtc_plat_data *pdata;
	व्योम __iomem *ioaddr;
	पूर्णांक ret = 0;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "stk17ta8_nvram",
		.word_size = 1,
		.stride = 1,
		.size = RTC_OFFSET,
		.reg_पढ़ो = stk17ta8_nvram_पढ़ो,
		.reg_ग_लिखो = stk17ta8_nvram_ग_लिखो,
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
	cal = पढ़ोb(ioaddr + RTC_CALIBRATION);
	अगर (cal & RTC_STOP) अणु
		cal &= RTC_CAL_MASK;
		flags = पढ़ोb(ioaddr + RTC_FLAGS);
		ग_लिखोb(flags | RTC_WRITE, ioaddr + RTC_FLAGS);
		ग_लिखोb(cal, ioaddr + RTC_CALIBRATION);
		ग_लिखोb(flags & ~RTC_WRITE, ioaddr + RTC_FLAGS);
	पूर्ण
	अगर (पढ़ोb(ioaddr + RTC_FLAGS) & RTC_FLAGS_PF)
		dev_warn(&pdev->dev, "voltage-low detected.\n");

	spin_lock_init(&pdata->lock);
	pdata->last_jअगरfies = jअगरfies;
	platक्रमm_set_drvdata(pdev, pdata);
	अगर (pdata->irq > 0) अणु
		ग_लिखोb(0, ioaddr + RTC_INTERRUPTS);
		अगर (devm_request_irq(&pdev->dev, pdata->irq,
				stk17ta8_rtc_पूर्णांकerrupt,
				IRQF_SHARED,
				pdev->name, pdev) < 0) अणु
			dev_warn(&pdev->dev, "interrupt not available.\n");
			pdata->irq = 0;
		पूर्ण
	पूर्ण

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc))
		वापस PTR_ERR(pdata->rtc);

	pdata->rtc->ops = &stk17ta8_rtc_ops;

	nvmem_cfg.priv = pdata;
	ret = devm_rtc_nvmem_रेजिस्टर(pdata->rtc, &nvmem_cfg);
	अगर (ret)
		वापस ret;

	वापस devm_rtc_रेजिस्टर_device(pdata->rtc);
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:stk17ta8");

अटल काष्ठा platक्रमm_driver stk17ta8_rtc_driver = अणु
	.probe		= stk17ta8_rtc_probe,
	.driver		= अणु
		.name	= "stk17ta8",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(stk17ta8_rtc_driver);

MODULE_AUTHOR("Thomas Hommel <thomas.hommel@ge.com>");
MODULE_DESCRIPTION("Simtek STK17TA8 RTC driver");
MODULE_LICENSE("GPL");
