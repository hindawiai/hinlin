<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An rtc driver क्रम the Dallas DS1511
 *
 * Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 * Copyright (C) 2007 Andrew Sharp <andy.sharp@lsi.com>
 *
 * Real समय घड़ी driver क्रम the Dallas 1511 chip, which also
 * contains a watchकरोg समयr.  There is a tiny amount of code that
 * platक्रमm code could use to mess with the watchकरोg device a little
 * bit, but not a full watchकरोg driver.
 */

#समावेश <linux/bcd.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

क्रमागत ds1511reg अणु
	DS1511_SEC = 0x0,
	DS1511_MIN = 0x1,
	DS1511_HOUR = 0x2,
	DS1511_DOW = 0x3,
	DS1511_DOM = 0x4,
	DS1511_MONTH = 0x5,
	DS1511_YEAR = 0x6,
	DS1511_CENTURY = 0x7,
	DS1511_AM1_SEC = 0x8,
	DS1511_AM2_MIN = 0x9,
	DS1511_AM3_HOUR = 0xa,
	DS1511_AM4_DATE = 0xb,
	DS1511_WD_MSEC = 0xc,
	DS1511_WD_SEC = 0xd,
	DS1511_CONTROL_A = 0xe,
	DS1511_CONTROL_B = 0xf,
	DS1511_RAMADDR_LSB = 0x10,
	DS1511_RAMDATA = 0x13
पूर्ण;

#घोषणा DS1511_BLF1	0x80
#घोषणा DS1511_BLF2	0x40
#घोषणा DS1511_PRS	0x20
#घोषणा DS1511_PAB	0x10
#घोषणा DS1511_TDF	0x08
#घोषणा DS1511_KSF	0x04
#घोषणा DS1511_WDF	0x02
#घोषणा DS1511_IRQF	0x01
#घोषणा DS1511_TE	0x80
#घोषणा DS1511_CS	0x40
#घोषणा DS1511_BME	0x20
#घोषणा DS1511_TPE	0x10
#घोषणा DS1511_TIE	0x08
#घोषणा DS1511_KIE	0x04
#घोषणा DS1511_WDE	0x02
#घोषणा DS1511_WDS	0x01
#घोषणा DS1511_RAM_MAX	0x100

#घोषणा RTC_CMD		DS1511_CONTROL_B
#घोषणा RTC_CMD1	DS1511_CONTROL_A

#घोषणा RTC_ALARM_SEC	DS1511_AM1_SEC
#घोषणा RTC_ALARM_MIN	DS1511_AM2_MIN
#घोषणा RTC_ALARM_HOUR	DS1511_AM3_HOUR
#घोषणा RTC_ALARM_DATE	DS1511_AM4_DATE

#घोषणा RTC_SEC		DS1511_SEC
#घोषणा RTC_MIN		DS1511_MIN
#घोषणा RTC_HOUR	DS1511_HOUR
#घोषणा RTC_DOW		DS1511_DOW
#घोषणा RTC_DOM		DS1511_DOM
#घोषणा RTC_MON		DS1511_MONTH
#घोषणा RTC_YEAR	DS1511_YEAR
#घोषणा RTC_CENTURY	DS1511_CENTURY

#घोषणा RTC_TIE	DS1511_TIE
#घोषणा RTC_TE	DS1511_TE

काष्ठा rtc_plat_data अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;		/* भव base address */
	पूर्णांक irq;
	अचिन्हित पूर्णांक irqen;
	पूर्णांक alrm_sec;
	पूर्णांक alrm_min;
	पूर्णांक alrm_hour;
	पूर्णांक alrm_mday;
	spinlock_t lock;
पूर्ण;

अटल DEFINE_SPINLOCK(ds1511_lock);

अटल __iomem अक्षर *ds1511_base;
अटल u32 reg_spacing = 1;

अटल noअंतरभूत व्योम
rtc_ग_लिखो(uपूर्णांक8_t val, uपूर्णांक32_t reg)
अणु
	ग_लिखोb(val, ds1511_base + (reg * reg_spacing));
पूर्ण

अटल noअंतरभूत uपूर्णांक8_t
rtc_पढ़ो(क्रमागत ds1511reg reg)
अणु
	वापस पढ़ोb(ds1511_base + (reg * reg_spacing));
पूर्ण

अटल अंतरभूत व्योम
rtc_disable_update(व्योम)
अणु
	rtc_ग_लिखो((rtc_पढ़ो(RTC_CMD) & ~RTC_TE), RTC_CMD);
पूर्ण

अटल व्योम
rtc_enable_update(व्योम)
अणु
	rtc_ग_लिखो((rtc_पढ़ो(RTC_CMD) | RTC_TE), RTC_CMD);
पूर्ण

/*
 * #घोषणा DS1511_WDOG_RESET_SUPPORT
 *
 * Uncomment this अगर you want to use these routines in
 * some platक्रमm code.
 */
#अगर_घोषित DS1511_WDOG_RESET_SUPPORT
/*
 * just enough code to set the watchकरोg समयr so that it
 * will reboot the प्रणाली
 */
व्योम
ds1511_wकरोg_set(अचिन्हित दीर्घ deciseconds)
अणु
	/*
	 * the wकरोg समयr can take 99.99 seconds
	 */
	deciseconds %= 10000;
	/*
	 * set the wकरोg values in the wकरोg रेजिस्टरs
	 */
	rtc_ग_लिखो(bin2bcd(deciseconds % 100), DS1511_WD_MSEC);
	rtc_ग_लिखो(bin2bcd(deciseconds / 100), DS1511_WD_SEC);
	/*
	 * set wकरोg enable and wकरोg 'steering' bit to issue a reset
	 */
	rtc_ग_लिखो(rtc_पढ़ो(RTC_CMD) | DS1511_WDE | DS1511_WDS, RTC_CMD);
पूर्ण

व्योम
ds1511_wकरोg_disable(व्योम)
अणु
	/*
	 * clear wकरोg enable and wकरोg 'steering' bits
	 */
	rtc_ग_लिखो(rtc_पढ़ो(RTC_CMD) & ~(DS1511_WDE | DS1511_WDS), RTC_CMD);
	/*
	 * clear the wकरोg counter
	 */
	rtc_ग_लिखो(0, DS1511_WD_MSEC);
	rtc_ग_लिखो(0, DS1511_WD_SEC);
पूर्ण
#पूर्ण_अगर

/*
 * set the rtc chip's idea of the समय.
 * stupidly, some callers call with year unmolested;
 * and some call with  year = year - 1900.  thanks.
 */
अटल पूर्णांक ds1511_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	u8 mon, day, करोw, hrs, min, sec, yrs, cen;
	अचिन्हित दीर्घ flags;

	/*
	 * won't have to change this क्रम a जबतक
	 */
	अगर (rtc_पंचांग->पंचांग_year < 1900)
		rtc_पंचांग->पंचांग_year += 1900;

	अगर (rtc_पंचांग->पंचांग_year < 1970)
		वापस -EINVAL;

	yrs = rtc_पंचांग->पंचांग_year % 100;
	cen = rtc_पंचांग->पंचांग_year / 100;
	mon = rtc_पंचांग->पंचांग_mon + 1;   /* पंचांग_mon starts at zero */
	day = rtc_पंचांग->पंचांग_mday;
	करोw = rtc_पंचांग->पंचांग_wday & 0x7; /* स्वतःmatic BCD */
	hrs = rtc_पंचांग->पंचांग_hour;
	min = rtc_पंचांग->पंचांग_min;
	sec = rtc_पंचांग->पंचांग_sec;

	अगर ((mon > 12) || (day == 0))
		वापस -EINVAL;

	अगर (day > rtc_month_days(rtc_पंचांग->पंचांग_mon, rtc_पंचांग->पंचांग_year))
		वापस -EINVAL;

	अगर ((hrs >= 24) || (min >= 60) || (sec >= 60))
		वापस -EINVAL;

	/*
	 * each रेजिस्टर is a dअगरferent number of valid bits
	 */
	sec = bin2bcd(sec) & 0x7f;
	min = bin2bcd(min) & 0x7f;
	hrs = bin2bcd(hrs) & 0x3f;
	day = bin2bcd(day) & 0x3f;
	mon = bin2bcd(mon) & 0x1f;
	yrs = bin2bcd(yrs) & 0xff;
	cen = bin2bcd(cen) & 0xff;

	spin_lock_irqsave(&ds1511_lock, flags);
	rtc_disable_update();
	rtc_ग_लिखो(cen, RTC_CENTURY);
	rtc_ग_लिखो(yrs, RTC_YEAR);
	rtc_ग_लिखो((rtc_पढ़ो(RTC_MON) & 0xe0) | mon, RTC_MON);
	rtc_ग_लिखो(day, RTC_DOM);
	rtc_ग_लिखो(hrs, RTC_HOUR);
	rtc_ग_लिखो(min, RTC_MIN);
	rtc_ग_लिखो(sec, RTC_SEC);
	rtc_ग_लिखो(करोw, RTC_DOW);
	rtc_enable_update();
	spin_unlock_irqrestore(&ds1511_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1511_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	अचिन्हित पूर्णांक century;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ds1511_lock, flags);
	rtc_disable_update();

	rtc_पंचांग->पंचांग_sec = rtc_पढ़ो(RTC_SEC) & 0x7f;
	rtc_पंचांग->पंचांग_min = rtc_पढ़ो(RTC_MIN) & 0x7f;
	rtc_पंचांग->पंचांग_hour = rtc_पढ़ो(RTC_HOUR) & 0x3f;
	rtc_पंचांग->पंचांग_mday = rtc_पढ़ो(RTC_DOM) & 0x3f;
	rtc_पंचांग->पंचांग_wday = rtc_पढ़ो(RTC_DOW) & 0x7;
	rtc_पंचांग->पंचांग_mon = rtc_पढ़ो(RTC_MON) & 0x1f;
	rtc_पंचांग->पंचांग_year = rtc_पढ़ो(RTC_YEAR) & 0x7f;
	century = rtc_पढ़ो(RTC_CENTURY);

	rtc_enable_update();
	spin_unlock_irqrestore(&ds1511_lock, flags);

	rtc_पंचांग->पंचांग_sec = bcd2bin(rtc_पंचांग->पंचांग_sec);
	rtc_पंचांग->पंचांग_min = bcd2bin(rtc_पंचांग->पंचांग_min);
	rtc_पंचांग->पंचांग_hour = bcd2bin(rtc_पंचांग->पंचांग_hour);
	rtc_पंचांग->पंचांग_mday = bcd2bin(rtc_पंचांग->पंचांग_mday);
	rtc_पंचांग->पंचांग_wday = bcd2bin(rtc_पंचांग->पंचांग_wday);
	rtc_पंचांग->पंचांग_mon = bcd2bin(rtc_पंचांग->पंचांग_mon);
	rtc_पंचांग->पंचांग_year = bcd2bin(rtc_पंचांग->पंचांग_year);
	century = bcd2bin(century) * 100;

	/*
	 * Account क्रम dअगरferences between how the RTC uses the values
	 * and how they are defined in a काष्ठा rtc_समय;
	 */
	century += rtc_पंचांग->पंचांग_year;
	rtc_पंचांग->पंचांग_year = century - 1900;

	rtc_पंचांग->पंचांग_mon--;

	वापस 0;
पूर्ण

/*
 * ग_लिखो the alarm रेजिस्टर settings
 *
 * we only have the use to पूर्णांकerrupt every second, otherwise
 * known as the update पूर्णांकerrupt, or the पूर्णांकerrupt अगर the whole
 * date/hours/mins/secs matches.  the ds1511 has many more
 * permutations, but the kernel करोesn't.
 */
अटल व्योम
ds1511_rtc_update_alarm(काष्ठा rtc_plat_data *pdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->lock, flags);
	rtc_ग_लिखो(pdata->alrm_mday < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_mday) & 0x3f,
	       RTC_ALARM_DATE);
	rtc_ग_लिखो(pdata->alrm_hour < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_hour) & 0x3f,
	       RTC_ALARM_HOUR);
	rtc_ग_लिखो(pdata->alrm_min < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_min) & 0x7f,
	       RTC_ALARM_MIN);
	rtc_ग_लिखो(pdata->alrm_sec < 0 || (pdata->irqen & RTC_UF) ?
	       0x80 : bin2bcd(pdata->alrm_sec) & 0x7f,
	       RTC_ALARM_SEC);
	rtc_ग_लिखो(rtc_पढ़ो(RTC_CMD) | (pdata->irqen ? RTC_TIE : 0), RTC_CMD);
	rtc_पढ़ो(RTC_CMD1);	/* clear पूर्णांकerrupts */
	spin_unlock_irqrestore(&pdata->lock, flags);
पूर्ण

अटल पूर्णांक
ds1511_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
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

	ds1511_rtc_update_alarm(pdata);
	वापस 0;
पूर्ण

अटल पूर्णांक
ds1511_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
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

अटल irqवापस_t
ds1511_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा rtc_plat_data *pdata = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ events = 0;

	spin_lock(&pdata->lock);
	/*
	 * पढ़ो and clear पूर्णांकerrupt
	 */
	अगर (rtc_पढ़ो(RTC_CMD1) & DS1511_IRQF) अणु
		events = RTC_IRQF;
		अगर (rtc_पढ़ो(RTC_ALARM_SEC) & 0x80)
			events |= RTC_UF;
		अन्यथा
			events |= RTC_AF;
		rtc_update_irq(pdata->rtc, 1, events);
	पूर्ण
	spin_unlock(&pdata->lock);
	वापस events ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक ds1511_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);

	अगर (pdata->irq <= 0)
		वापस -EINVAL;
	अगर (enabled)
		pdata->irqen |= RTC_AF;
	अन्यथा
		pdata->irqen &= ~RTC_AF;
	ds1511_rtc_update_alarm(pdata);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1511_rtc_ops = अणु
	.पढ़ो_समय		= ds1511_rtc_पढ़ो_समय,
	.set_समय		= ds1511_rtc_set_समय,
	.पढ़ो_alarm		= ds1511_rtc_पढ़ो_alarm,
	.set_alarm		= ds1511_rtc_set_alarm,
	.alarm_irq_enable	= ds1511_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक ds1511_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *buf,
			     माप_प्रकार size)
अणु
	पूर्णांक i;

	rtc_ग_लिखो(pos, DS1511_RAMADDR_LSB);
	क्रम (i = 0; i < size; i++)
		*(अक्षर *)buf++ = rtc_पढ़ो(DS1511_RAMDATA);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1511_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *buf,
			      माप_प्रकार size)
अणु
	पूर्णांक i;

	rtc_ग_लिखो(pos, DS1511_RAMADDR_LSB);
	क्रम (i = 0; i < size; i++)
		rtc_ग_लिखो(*(अक्षर *)buf++, DS1511_RAMDATA);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1511_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_plat_data *pdata;
	पूर्णांक ret = 0;
	काष्ठा nvmem_config ds1511_nvmem_cfg = अणु
		.name = "ds1511_nvram",
		.word_size = 1,
		.stride = 1,
		.size = DS1511_RAM_MAX,
		.reg_पढ़ो = ds1511_nvram_पढ़ो,
		.reg_ग_लिखो = ds1511_nvram_ग_लिखो,
		.priv = &pdev->dev,
	पूर्ण;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	ds1511_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ds1511_base))
		वापस PTR_ERR(ds1511_base);
	pdata->ioaddr = ds1511_base;
	pdata->irq = platक्रमm_get_irq(pdev, 0);

	/*
	 * turn on the घड़ी and the crystal, etc.
	 */
	rtc_ग_लिखो(DS1511_BME, RTC_CMD);
	rtc_ग_लिखो(0, RTC_CMD1);
	/*
	 * clear the wकरोg counter
	 */
	rtc_ग_लिखो(0, DS1511_WD_MSEC);
	rtc_ग_लिखो(0, DS1511_WD_SEC);
	/*
	 * start the घड़ी
	 */
	rtc_enable_update();

	/*
	 * check क्रम a dying bat-tree
	 */
	अगर (rtc_पढ़ो(RTC_CMD1) & DS1511_BLF1)
		dev_warn(&pdev->dev, "voltage-low detected.\n");

	spin_lock_init(&pdata->lock);
	platक्रमm_set_drvdata(pdev, pdata);

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc))
		वापस PTR_ERR(pdata->rtc);

	pdata->rtc->ops = &ds1511_rtc_ops;

	ret = devm_rtc_रेजिस्टर_device(pdata->rtc);
	अगर (ret)
		वापस ret;

	devm_rtc_nvmem_रेजिस्टर(pdata->rtc, &ds1511_nvmem_cfg);

	/*
	 * अगर the platक्रमm has an पूर्णांकerrupt in mind क्रम this device,
	 * then by all means, set it
	 */
	अगर (pdata->irq > 0) अणु
		rtc_पढ़ो(RTC_CMD1);
		अगर (devm_request_irq(&pdev->dev, pdata->irq, ds1511_पूर्णांकerrupt,
			IRQF_SHARED, pdev->name, pdev) < 0) अणु

			dev_warn(&pdev->dev, "interrupt not available.\n");
			pdata->irq = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:ds1511");

अटल काष्ठा platक्रमm_driver ds1511_rtc_driver = अणु
	.probe		= ds1511_rtc_probe,
	.driver		= अणु
		.name	= "ds1511",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ds1511_rtc_driver);

MODULE_AUTHOR("Andrew Sharp <andy.sharp@lsi.com>");
MODULE_DESCRIPTION("Dallas DS1511 RTC driver");
MODULE_LICENSE("GPL");
