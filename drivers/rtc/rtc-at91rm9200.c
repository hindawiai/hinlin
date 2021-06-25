<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Real Time Clock पूर्णांकerface क्रम Linux on Aपंचांगel AT91RM9200
 *
 *	Copyright (C) 2002 Rick Bronson
 *
 *	Converted to RTC class model by Andrew Victor
 *
 *	Ported to Linux 2.6 by Steven Scholz
 *	Based on s3c2410-rtc.c Simtec Electronics
 *
 *	Based on sa1100-rtc.c by Nils Faerber
 *	Based on rtc.c by Paul Gorपंचांगaker
 */

#समावेश <linux/bcd.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/suspend.h>
#समावेश <linux/समय.स>
#समावेश <linux/uaccess.h>

#घोषणा	AT91_RTC_CR		0x00			/* Control Register */
#घोषणा		AT91_RTC_UPDTIM		BIT(0)		/* Update Request Time Register */
#घोषणा		AT91_RTC_UPDCAL		BIT(1)		/* Update Request Calendar Register */

#घोषणा	AT91_RTC_MR		0x04			/* Mode Register */
#घोषणा		AT91_RTC_HRMOD		BIT(0)		/* 12/24 hour mode */
#घोषणा		AT91_RTC_NEGPPM		BIT(4)		/* Negative PPM correction */
#घोषणा		AT91_RTC_CORRECTION	GENMASK(14, 8)	/* Slow घड़ी correction */
#घोषणा		AT91_RTC_HIGHPPM	BIT(15)		/* High PPM correction */

#घोषणा	AT91_RTC_TIMR		0x08			/* Time Register */
#घोषणा		AT91_RTC_SEC		GENMASK(6, 0)	/* Current Second */
#घोषणा		AT91_RTC_MIN		GENMASK(14, 8)	/* Current Minute */
#घोषणा		AT91_RTC_HOUR		GENMASK(21, 16)	/* Current Hour */
#घोषणा		AT91_RTC_AMPM		BIT(22)		/* Ante Meridiem Post Meridiem Indicator */

#घोषणा	AT91_RTC_CALR		0x0c			/* Calendar Register */
#घोषणा		AT91_RTC_CENT		GENMASK(6, 0)	/* Current Century */
#घोषणा		AT91_RTC_YEAR		GENMASK(15, 8)	/* Current Year */
#घोषणा		AT91_RTC_MONTH		GENMASK(20, 16)	/* Current Month */
#घोषणा		AT91_RTC_DAY		GENMASK(23, 21)	/* Current Day */
#घोषणा		AT91_RTC_DATE		GENMASK(29, 24)	/* Current Date */

#घोषणा	AT91_RTC_TIMALR		0x10			/* Time Alarm Register */
#घोषणा		AT91_RTC_SECEN		BIT(7)		/* Second Alarm Enable */
#घोषणा		AT91_RTC_MINEN		BIT(15)		/* Minute Alarm Enable */
#घोषणा		AT91_RTC_HOUREN		BIT(23)		/* Hour Alarm Enable */

#घोषणा	AT91_RTC_CALALR		0x14			/* Calendar Alarm Register */
#घोषणा		AT91_RTC_MTHEN		BIT(23)		/* Month Alarm Enable */
#घोषणा		AT91_RTC_DATEEN		BIT(31)		/* Date Alarm Enable */

#घोषणा	AT91_RTC_SR		0x18			/* Status Register */
#घोषणा		AT91_RTC_ACKUPD		BIT(0)		/* Acknowledge क्रम Update */
#घोषणा		AT91_RTC_ALARM		BIT(1)		/* Alarm Flag */
#घोषणा		AT91_RTC_SECEV		BIT(2)		/* Second Event */
#घोषणा		AT91_RTC_TIMEV		BIT(3)		/* Time Event */
#घोषणा		AT91_RTC_CALEV		BIT(4)		/* Calendar Event */

#घोषणा	AT91_RTC_SCCR		0x1c			/* Status Clear Command Register */
#घोषणा	AT91_RTC_IER		0x20			/* Interrupt Enable Register */
#घोषणा	AT91_RTC_IDR		0x24			/* Interrupt Disable Register */
#घोषणा	AT91_RTC_IMR		0x28			/* Interrupt Mask Register */

#घोषणा	AT91_RTC_VER		0x2c			/* Valid Entry Register */
#घोषणा		AT91_RTC_NVTIM		BIT(0)		/* Non valid Time */
#घोषणा		AT91_RTC_NVCAL		BIT(1)		/* Non valid Calendar */
#घोषणा		AT91_RTC_NVTIMALR	BIT(2)		/* Non valid Time Alarm */
#घोषणा		AT91_RTC_NVCALALR	BIT(3)		/* Non valid Calendar Alarm */

#घोषणा AT91_RTC_CORR_DIVIDEND		3906000
#घोषणा AT91_RTC_CORR_LOW_RATIO		20

#घोषणा at91_rtc_पढ़ो(field) \
	पढ़ोl_relaxed(at91_rtc_regs + field)
#घोषणा at91_rtc_ग_लिखो(field, val) \
	ग_लिखोl_relaxed((val), at91_rtc_regs + field)

काष्ठा at91_rtc_config अणु
	bool use_shaकरोw_imr;
	bool has_correction;
पूर्ण;

अटल स्थिर काष्ठा at91_rtc_config *at91_rtc_config;
अटल DECLARE_COMPLETION(at91_rtc_updated);
अटल DECLARE_COMPLETION(at91_rtc_upd_rdy);
अटल व्योम __iomem *at91_rtc_regs;
अटल पूर्णांक irq;
अटल DEFINE_SPINLOCK(at91_rtc_lock);
अटल u32 at91_rtc_shaकरोw_imr;
अटल bool suspended;
अटल DEFINE_SPINLOCK(suspended_lock);
अटल अचिन्हित दीर्घ cached_events;
अटल u32 at91_rtc_imr;
अटल काष्ठा clk *sclk;

अटल व्योम at91_rtc_ग_लिखो_ier(u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&at91_rtc_lock, flags);
	at91_rtc_shaकरोw_imr |= mask;
	at91_rtc_ग_लिखो(AT91_RTC_IER, mask);
	spin_unlock_irqrestore(&at91_rtc_lock, flags);
पूर्ण

अटल व्योम at91_rtc_ग_लिखो_idr(u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&at91_rtc_lock, flags);
	at91_rtc_ग_लिखो(AT91_RTC_IDR, mask);
	/*
	 * Register पढ़ो back (of any RTC-रेजिस्टर) needed to make sure
	 * IDR-रेजिस्टर ग_लिखो has reached the peripheral beक्रमe updating
	 * shaकरोw mask.
	 *
	 * Note that there is still a possibility that the mask is updated
	 * beक्रमe पूर्णांकerrupts have actually been disabled in hardware. The only
	 * way to be certain would be to poll the IMR-रेजिस्टर, which is is
	 * the very रेजिस्टर we are trying to emulate. The रेजिस्टर पढ़ो back
	 * is a reasonable heuristic.
	 */
	at91_rtc_पढ़ो(AT91_RTC_SR);
	at91_rtc_shaकरोw_imr &= ~mask;
	spin_unlock_irqrestore(&at91_rtc_lock, flags);
पूर्ण

अटल u32 at91_rtc_पढ़ो_imr(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask;

	अगर (at91_rtc_config->use_shaकरोw_imr) अणु
		spin_lock_irqsave(&at91_rtc_lock, flags);
		mask = at91_rtc_shaकरोw_imr;
		spin_unlock_irqrestore(&at91_rtc_lock, flags);
	पूर्ण अन्यथा अणु
		mask = at91_rtc_पढ़ो(AT91_RTC_IMR);
	पूर्ण

	वापस mask;
पूर्ण

/*
 * Decode समय/date पूर्णांकo rtc_समय काष्ठाure
 */
अटल व्योम at91_rtc_decodeसमय(अचिन्हित पूर्णांक समयreg, अचिन्हित पूर्णांक calreg,
				काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित पूर्णांक समय, date;

	/* must पढ़ो twice in हाल it changes */
	करो अणु
		समय = at91_rtc_पढ़ो(समयreg);
		date = at91_rtc_पढ़ो(calreg);
	पूर्ण जबतक ((समय != at91_rtc_पढ़ो(समयreg)) ||
			(date != at91_rtc_पढ़ो(calreg)));

	पंचांग->पंचांग_sec  = bcd2bin(FIELD_GET(AT91_RTC_SEC, समय));
	पंचांग->पंचांग_min  = bcd2bin(FIELD_GET(AT91_RTC_MIN, समय));
	पंचांग->पंचांग_hour = bcd2bin(FIELD_GET(AT91_RTC_HOUR, समय));

	/*
	 * The Calendar Alarm रेजिस्टर करोes not have a field क्रम
	 * the year - so these will वापस an invalid value.
	 */
	पंचांग->पंचांग_year  = bcd2bin(date & AT91_RTC_CENT) * 100;	/* century */
	पंचांग->पंचांग_year += bcd2bin(FIELD_GET(AT91_RTC_YEAR, date));	/* year */

	पंचांग->पंचांग_wday = bcd2bin(FIELD_GET(AT91_RTC_DAY, date)) - 1;	/* day of the week [0-6], Sunday=0 */
	पंचांग->पंचांग_mon  = bcd2bin(FIELD_GET(AT91_RTC_MONTH, date)) - 1;
	पंचांग->पंचांग_mday = bcd2bin(FIELD_GET(AT91_RTC_DATE, date));
पूर्ण

/*
 * Read current समय and date in RTC
 */
अटल पूर्णांक at91_rtc_पढ़ोसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	at91_rtc_decodeसमय(AT91_RTC_TIMR, AT91_RTC_CALR, पंचांग);
	पंचांग->पंचांग_yday = rtc_year_days(पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year);
	पंचांग->पंचांग_year = पंचांग->पंचांग_year - 1900;

	dev_dbg(dev, "%s(): %ptR\n", __func__, पंचांग);

	वापस 0;
पूर्ण

/*
 * Set current समय and date in RTC
 */
अटल पूर्णांक at91_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ cr;

	dev_dbg(dev, "%s(): %ptR\n", __func__, पंचांग);

	रुको_क्रम_completion(&at91_rtc_upd_rdy);

	/* Stop Time/Calendar from counting */
	cr = at91_rtc_पढ़ो(AT91_RTC_CR);
	at91_rtc_ग_लिखो(AT91_RTC_CR, cr | AT91_RTC_UPDCAL | AT91_RTC_UPDTIM);

	at91_rtc_ग_लिखो_ier(AT91_RTC_ACKUPD);
	रुको_क्रम_completion(&at91_rtc_updated);	/* रुको क्रम ACKUPD पूर्णांकerrupt */
	at91_rtc_ग_लिखो_idr(AT91_RTC_ACKUPD);

	at91_rtc_ग_लिखो(AT91_RTC_TIMR,
			  FIELD_PREP(AT91_RTC_SEC, bin2bcd(पंचांग->पंचांग_sec))
			| FIELD_PREP(AT91_RTC_MIN, bin2bcd(पंचांग->पंचांग_min))
			| FIELD_PREP(AT91_RTC_HOUR, bin2bcd(पंचांग->पंचांग_hour)));

	at91_rtc_ग_लिखो(AT91_RTC_CALR,
			  FIELD_PREP(AT91_RTC_CENT,
				     bin2bcd((पंचांग->पंचांग_year + 1900) / 100))
			| FIELD_PREP(AT91_RTC_YEAR, bin2bcd(पंचांग->पंचांग_year % 100))
			| FIELD_PREP(AT91_RTC_MONTH, bin2bcd(पंचांग->पंचांग_mon + 1))
			| FIELD_PREP(AT91_RTC_DAY, bin2bcd(पंचांग->पंचांग_wday + 1))
			| FIELD_PREP(AT91_RTC_DATE, bin2bcd(पंचांग->पंचांग_mday)));

	/* Restart Time/Calendar */
	cr = at91_rtc_पढ़ो(AT91_RTC_CR);
	at91_rtc_ग_लिखो(AT91_RTC_SCCR, AT91_RTC_SECEV);
	at91_rtc_ग_लिखो(AT91_RTC_CR, cr & ~(AT91_RTC_UPDCAL | AT91_RTC_UPDTIM));
	at91_rtc_ग_लिखो_ier(AT91_RTC_SECEV);

	वापस 0;
पूर्ण

/*
 * Read alarm समय and date in RTC
 */
अटल पूर्णांक at91_rtc_पढ़ोalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_समय *पंचांग = &alrm->समय;

	at91_rtc_decodeसमय(AT91_RTC_TIMALR, AT91_RTC_CALALR, पंचांग);
	पंचांग->पंचांग_year = -1;

	alrm->enabled = (at91_rtc_पढ़ो_imr() & AT91_RTC_ALARM)
			? 1 : 0;

	dev_dbg(dev, "%s(): %ptR %sabled\n", __func__, पंचांग,
		alrm->enabled ? "en" : "dis");

	वापस 0;
पूर्ण

/*
 * Set alarm समय and date in RTC
 */
अटल पूर्णांक at91_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_समय पंचांग = alrm->समय;

	at91_rtc_ग_लिखो_idr(AT91_RTC_ALARM);
	at91_rtc_ग_लिखो(AT91_RTC_TIMALR,
		  FIELD_PREP(AT91_RTC_SEC, bin2bcd(alrm->समय.पंचांग_sec))
		| FIELD_PREP(AT91_RTC_MIN, bin2bcd(alrm->समय.पंचांग_min))
		| FIELD_PREP(AT91_RTC_HOUR, bin2bcd(alrm->समय.पंचांग_hour))
		| AT91_RTC_HOUREN | AT91_RTC_MINEN | AT91_RTC_SECEN);
	at91_rtc_ग_लिखो(AT91_RTC_CALALR,
		  FIELD_PREP(AT91_RTC_MONTH, bin2bcd(alrm->समय.पंचांग_mon + 1))
		| FIELD_PREP(AT91_RTC_DATE, bin2bcd(alrm->समय.पंचांग_mday))
		| AT91_RTC_DATEEN | AT91_RTC_MTHEN);

	अगर (alrm->enabled) अणु
		at91_rtc_ग_लिखो(AT91_RTC_SCCR, AT91_RTC_ALARM);
		at91_rtc_ग_लिखो_ier(AT91_RTC_ALARM);
	पूर्ण

	dev_dbg(dev, "%s(): %ptR\n", __func__, &पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	dev_dbg(dev, "%s(): cmd=%08x\n", __func__, enabled);

	अगर (enabled) अणु
		at91_rtc_ग_लिखो(AT91_RTC_SCCR, AT91_RTC_ALARM);
		at91_rtc_ग_लिखो_ier(AT91_RTC_ALARM);
	पूर्ण अन्यथा
		at91_rtc_ग_लिखो_idr(AT91_RTC_ALARM);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_पढ़ोoffset(काष्ठा device *dev, दीर्घ *offset)
अणु
	u32 mr = at91_rtc_पढ़ो(AT91_RTC_MR);
	दीर्घ val = FIELD_GET(AT91_RTC_CORRECTION, mr);

	अगर (!val) अणु
		*offset = 0;
		वापस 0;
	पूर्ण

	val++;

	अगर (!(mr & AT91_RTC_NEGPPM))
		val = -val;

	अगर (!(mr & AT91_RTC_HIGHPPM))
		val *= AT91_RTC_CORR_LOW_RATIO;

	*offset = DIV_ROUND_CLOSEST(AT91_RTC_CORR_DIVIDEND, val);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_setoffset(काष्ठा device *dev, दीर्घ offset)
अणु
	दीर्घ corr;
	u32 mr;

	अगर (offset > AT91_RTC_CORR_DIVIDEND / 2)
		वापस -दुस्फल;
	अगर (offset < -AT91_RTC_CORR_DIVIDEND / 2)
		वापस -दुस्फल;

	mr = at91_rtc_पढ़ो(AT91_RTC_MR);
	mr &= ~(AT91_RTC_NEGPPM | AT91_RTC_CORRECTION | AT91_RTC_HIGHPPM);

	अगर (offset > 0)
		mr |= AT91_RTC_NEGPPM;
	अन्यथा
		offset = -offset;

	/* offset less than 764 ppb, disable correction*/
	अगर (offset < 764) अणु
		at91_rtc_ग_लिखो(AT91_RTC_MR, mr & ~AT91_RTC_NEGPPM);

		वापस 0;
	पूर्ण

	/*
	 * 29208 ppb is the perfect cutoff between low range and high range
	 * low range values are never better than high range value after that.
	 */
	अगर (offset < 29208) अणु
		corr = DIV_ROUND_CLOSEST(AT91_RTC_CORR_DIVIDEND, offset * AT91_RTC_CORR_LOW_RATIO);
	पूर्ण अन्यथा अणु
		corr = DIV_ROUND_CLOSEST(AT91_RTC_CORR_DIVIDEND, offset);
		mr |= AT91_RTC_HIGHPPM;
	पूर्ण

	अगर (corr > 128)
		corr = 128;

	mr |= FIELD_PREP(AT91_RTC_CORRECTION, corr - 1);

	at91_rtc_ग_लिखो(AT91_RTC_MR, mr);

	वापस 0;
पूर्ण

/*
 * IRQ handler क्रम the RTC
 */
अटल irqवापस_t at91_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा rtc_device *rtc = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक rtsr;
	अचिन्हित दीर्घ events = 0;
	पूर्णांक ret = IRQ_NONE;

	spin_lock(&suspended_lock);
	rtsr = at91_rtc_पढ़ो(AT91_RTC_SR) & at91_rtc_पढ़ो_imr();
	अगर (rtsr) अणु		/* this पूर्णांकerrupt is shared!  Is it ours? */
		अगर (rtsr & AT91_RTC_ALARM)
			events |= (RTC_AF | RTC_IRQF);
		अगर (rtsr & AT91_RTC_SECEV) अणु
			complete(&at91_rtc_upd_rdy);
			at91_rtc_ग_लिखो_idr(AT91_RTC_SECEV);
		पूर्ण
		अगर (rtsr & AT91_RTC_ACKUPD)
			complete(&at91_rtc_updated);

		at91_rtc_ग_लिखो(AT91_RTC_SCCR, rtsr);	/* clear status reg */

		अगर (!suspended) अणु
			rtc_update_irq(rtc, 1, events);

			dev_dbg(&pdev->dev, "%s(): num=%ld, events=0x%02lx\n",
				__func__, events >> 8, events & 0x000000FF);
		पूर्ण अन्यथा अणु
			cached_events |= events;
			at91_rtc_ग_लिखो_idr(at91_rtc_imr);
			pm_प्रणाली_wakeup();
		पूर्ण

		ret = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&suspended_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा at91_rtc_config at91rm9200_config = अणु
पूर्ण;

अटल स्थिर काष्ठा at91_rtc_config at91sam9x5_config = अणु
	.use_shaकरोw_imr	= true,
पूर्ण;

अटल स्थिर काष्ठा at91_rtc_config sama5d4_config = अणु
	.has_correction = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id at91_rtc_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91rm9200-rtc",
		.data = &at91rm9200_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9x5-rtc",
		.data = &at91sam9x5_config,
	पूर्ण, अणु
		.compatible = "atmel,sama5d4-rtc",
		.data = &sama5d4_config,
	पूर्ण, अणु
		.compatible = "atmel,sama5d2-rtc",
		.data = &sama5d4_config,
	पूर्ण, अणु
		.compatible = "microchip,sam9x60-rtc",
		.data = &sama5d4_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_rtc_dt_ids);

अटल स्थिर काष्ठा rtc_class_ops at91_rtc_ops = अणु
	.पढ़ो_समय	= at91_rtc_पढ़ोसमय,
	.set_समय	= at91_rtc_समय_रखो,
	.पढ़ो_alarm	= at91_rtc_पढ़ोalarm,
	.set_alarm	= at91_rtc_setalarm,
	.alarm_irq_enable = at91_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा rtc_class_ops sama5d4_rtc_ops = अणु
	.पढ़ो_समय	= at91_rtc_पढ़ोसमय,
	.set_समय	= at91_rtc_समय_रखो,
	.पढ़ो_alarm	= at91_rtc_पढ़ोalarm,
	.set_alarm	= at91_rtc_setalarm,
	.alarm_irq_enable = at91_rtc_alarm_irq_enable,
	.set_offset	= at91_rtc_setoffset,
	.पढ़ो_offset	= at91_rtc_पढ़ोoffset,
पूर्ण;

/*
 * Initialize and install RTC driver
 */
अटल पूर्णांक __init at91_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा resource *regs;
	पूर्णांक ret = 0;

	at91_rtc_config = of_device_get_match_data(&pdev->dev);
	अगर (!at91_rtc_config)
		वापस -ENODEV;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "no mmio resource defined\n");
		वापस -ENXIO;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	at91_rtc_regs = devm_ioremap(&pdev->dev, regs->start,
				     resource_size(regs));
	अगर (!at91_rtc_regs) अणु
		dev_err(&pdev->dev, "failed to map registers, aborting.\n");
		वापस -ENOMEM;
	पूर्ण

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);
	platक्रमm_set_drvdata(pdev, rtc);

	sclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sclk))
		वापस PTR_ERR(sclk);

	ret = clk_prepare_enable(sclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable slow clock\n");
		वापस ret;
	पूर्ण

	at91_rtc_ग_लिखो(AT91_RTC_CR, 0);
	at91_rtc_ग_लिखो(AT91_RTC_MR, at91_rtc_पढ़ो(AT91_RTC_MR) & ~AT91_RTC_HRMOD);

	/* Disable all पूर्णांकerrupts */
	at91_rtc_ग_लिखो_idr(AT91_RTC_ACKUPD | AT91_RTC_ALARM |
					AT91_RTC_SECEV | AT91_RTC_TIMEV |
					AT91_RTC_CALEV);

	ret = devm_request_irq(&pdev->dev, irq, at91_rtc_पूर्णांकerrupt,
			       IRQF_SHARED | IRQF_COND_SUSPEND,
			       "at91_rtc", pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ %d already in use.\n", irq);
		जाओ err_clk;
	पूर्ण

	/* cpu init code should really have flagged this device as
	 * being wake-capable; अगर it didn't, करो that here.
	 */
	अगर (!device_can_wakeup(&pdev->dev))
		device_init_wakeup(&pdev->dev, 1);

	अगर (at91_rtc_config->has_correction)
		rtc->ops = &sama5d4_rtc_ops;
	अन्यथा
		rtc->ops = &at91_rtc_ops;

	rtc->range_min = RTC_TIMESTAMP_BEGIN_1900;
	rtc->range_max = RTC_TIMESTAMP_END_2099;
	ret = devm_rtc_रेजिस्टर_device(rtc);
	अगर (ret)
		जाओ err_clk;

	/* enable SECEV पूर्णांकerrupt in order to initialize at91_rtc_upd_rdy
	 * completion.
	 */
	at91_rtc_ग_लिखो_ier(AT91_RTC_SECEV);

	dev_info(&pdev->dev, "AT91 Real Time Clock driver.\n");
	वापस 0;

err_clk:
	clk_disable_unprepare(sclk);

	वापस ret;
पूर्ण

/*
 * Disable and हटाओ the RTC driver
 */
अटल पूर्णांक __निकास at91_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* Disable all पूर्णांकerrupts */
	at91_rtc_ग_लिखो_idr(AT91_RTC_ACKUPD | AT91_RTC_ALARM |
					AT91_RTC_SECEV | AT91_RTC_TIMEV |
					AT91_RTC_CALEV);

	clk_disable_unprepare(sclk);

	वापस 0;
पूर्ण

अटल व्योम at91_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	/* Disable all पूर्णांकerrupts */
	at91_rtc_ग_लिखो(AT91_RTC_IDR, AT91_RTC_ACKUPD | AT91_RTC_ALARM |
					AT91_RTC_SECEV | AT91_RTC_TIMEV |
					AT91_RTC_CALEV);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

/* AT91RM9200 RTC Power management control */

अटल पूर्णांक at91_rtc_suspend(काष्ठा device *dev)
अणु
	/* this IRQ is shared with DBGU and other hardware which isn't
	 * necessarily करोing PM like we are...
	 */
	at91_rtc_ग_लिखो(AT91_RTC_SCCR, AT91_RTC_ALARM);

	at91_rtc_imr = at91_rtc_पढ़ो_imr()
			& (AT91_RTC_ALARM|AT91_RTC_SECEV);
	अगर (at91_rtc_imr) अणु
		अगर (device_may_wakeup(dev)) अणु
			अचिन्हित दीर्घ flags;

			enable_irq_wake(irq);

			spin_lock_irqsave(&suspended_lock, flags);
			suspended = true;
			spin_unlock_irqrestore(&suspended_lock, flags);
		पूर्ण अन्यथा अणु
			at91_rtc_ग_लिखो_idr(at91_rtc_imr);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक at91_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा rtc_device *rtc = dev_get_drvdata(dev);

	अगर (at91_rtc_imr) अणु
		अगर (device_may_wakeup(dev)) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&suspended_lock, flags);

			अगर (cached_events) अणु
				rtc_update_irq(rtc, 1, cached_events);
				cached_events = 0;
			पूर्ण

			suspended = false;
			spin_unlock_irqrestore(&suspended_lock, flags);

			disable_irq_wake(irq);
		पूर्ण
		at91_rtc_ग_लिखो_ier(at91_rtc_imr);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(at91_rtc_pm_ops, at91_rtc_suspend, at91_rtc_resume);

अटल काष्ठा platक्रमm_driver at91_rtc_driver = अणु
	.हटाओ		= __निकास_p(at91_rtc_हटाओ),
	.shutकरोwn	= at91_rtc_shutकरोwn,
	.driver		= अणु
		.name	= "at91_rtc",
		.pm	= &at91_rtc_pm_ops,
		.of_match_table = of_match_ptr(at91_rtc_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(at91_rtc_driver, at91_rtc_probe);

MODULE_AUTHOR("Rick Bronson");
MODULE_DESCRIPTION("RTC driver for Atmel AT91RM9200");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:at91_rtc");
