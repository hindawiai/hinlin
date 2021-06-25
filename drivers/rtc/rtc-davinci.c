<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DaVinci Power Management and Real Time Clock Driver क्रम TI platक्रमms
 *
 * Copyright (C) 2009 Texas Instruments, Inc
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

/*
 * The DaVinci RTC is a simple RTC with the following
 * Sec: 0 - 59 : BCD count
 * Min: 0 - 59 : BCD count
 * Hour: 0 - 23 : BCD count
 * Day: 0 - 0x7FFF(32767) : Binary count ( Over 89 years )
 */

/* PRTC पूर्णांकerface रेजिस्टरs */
#घोषणा DAVINCI_PRTCIF_PID		0x00
#घोषणा PRTCIF_CTLR			0x04
#घोषणा PRTCIF_LDATA			0x08
#घोषणा PRTCIF_UDATA			0x0C
#घोषणा PRTCIF_INTEN			0x10
#घोषणा PRTCIF_INTFLG			0x14

/* PRTCIF_CTLR bit fields */
#घोषणा PRTCIF_CTLR_BUSY		BIT(31)
#घोषणा PRTCIF_CTLR_SIZE		BIT(25)
#घोषणा PRTCIF_CTLR_सूची			BIT(24)
#घोषणा PRTCIF_CTLR_BENU_MSB		BIT(23)
#घोषणा PRTCIF_CTLR_BENU_3RD_BYTE	BIT(22)
#घोषणा PRTCIF_CTLR_BENU_2ND_BYTE	BIT(21)
#घोषणा PRTCIF_CTLR_BENU_LSB		BIT(20)
#घोषणा PRTCIF_CTLR_BENU_MASK		(0x00F00000)
#घोषणा PRTCIF_CTLR_BENL_MSB		BIT(19)
#घोषणा PRTCIF_CTLR_BENL_3RD_BYTE	BIT(18)
#घोषणा PRTCIF_CTLR_BENL_2ND_BYTE	BIT(17)
#घोषणा PRTCIF_CTLR_BENL_LSB		BIT(16)
#घोषणा PRTCIF_CTLR_BENL_MASK		(0x000F0000)

/* PRTCIF_INTEN bit fields */
#घोषणा PRTCIF_INTEN_RTCSS		BIT(1)
#घोषणा PRTCIF_INTEN_RTCIF		BIT(0)
#घोषणा PRTCIF_INTEN_MASK		(PRTCIF_INTEN_RTCSS \
					| PRTCIF_INTEN_RTCIF)

/* PRTCIF_INTFLG bit fields */
#घोषणा PRTCIF_INTFLG_RTCSS		BIT(1)
#घोषणा PRTCIF_INTFLG_RTCIF		BIT(0)
#घोषणा PRTCIF_INTFLG_MASK		(PRTCIF_INTFLG_RTCSS \
					| PRTCIF_INTFLG_RTCIF)

/* PRTC subप्रणाली रेजिस्टरs */
#घोषणा PRTCSS_RTC_INTC_EXTENA1		(0x0C)
#घोषणा PRTCSS_RTC_CTRL			(0x10)
#घोषणा PRTCSS_RTC_WDT			(0x11)
#घोषणा PRTCSS_RTC_TMR0			(0x12)
#घोषणा PRTCSS_RTC_TMR1			(0x13)
#घोषणा PRTCSS_RTC_CCTRL		(0x14)
#घोषणा PRTCSS_RTC_SEC			(0x15)
#घोषणा PRTCSS_RTC_MIN			(0x16)
#घोषणा PRTCSS_RTC_HOUR			(0x17)
#घोषणा PRTCSS_RTC_DAY0			(0x18)
#घोषणा PRTCSS_RTC_DAY1			(0x19)
#घोषणा PRTCSS_RTC_AMIN			(0x1A)
#घोषणा PRTCSS_RTC_AHOUR		(0x1B)
#घोषणा PRTCSS_RTC_ADAY0		(0x1C)
#घोषणा PRTCSS_RTC_ADAY1		(0x1D)
#घोषणा PRTCSS_RTC_CLKC_CNT		(0x20)

/* PRTCSS_RTC_INTC_EXTENA1 */
#घोषणा PRTCSS_RTC_INTC_EXTENA1_MASK	(0x07)

/* PRTCSS_RTC_CTRL bit fields */
#घोषणा PRTCSS_RTC_CTRL_WDTBUS		BIT(7)
#घोषणा PRTCSS_RTC_CTRL_WEN		BIT(6)
#घोषणा PRTCSS_RTC_CTRL_WDRT		BIT(5)
#घोषणा PRTCSS_RTC_CTRL_WDTFLG		BIT(4)
#घोषणा PRTCSS_RTC_CTRL_TE		BIT(3)
#घोषणा PRTCSS_RTC_CTRL_TIEN		BIT(2)
#घोषणा PRTCSS_RTC_CTRL_TMRFLG		BIT(1)
#घोषणा PRTCSS_RTC_CTRL_TMMD		BIT(0)

/* PRTCSS_RTC_CCTRL bit fields */
#घोषणा PRTCSS_RTC_CCTRL_CALBUSY	BIT(7)
#घोषणा PRTCSS_RTC_CCTRL_DAEN		BIT(5)
#घोषणा PRTCSS_RTC_CCTRL_HAEN		BIT(4)
#घोषणा PRTCSS_RTC_CCTRL_MAEN		BIT(3)
#घोषणा PRTCSS_RTC_CCTRL_ALMFLG		BIT(2)
#घोषणा PRTCSS_RTC_CCTRL_AIEN		BIT(1)
#घोषणा PRTCSS_RTC_CCTRL_CAEN		BIT(0)

अटल DEFINE_SPINLOCK(davinci_rtc_lock);

काष्ठा davinci_rtc अणु
	काष्ठा rtc_device		*rtc;
	व्योम __iomem			*base;
	पूर्णांक				irq;
पूर्ण;

अटल अंतरभूत व्योम rtcअगर_ग_लिखो(काष्ठा davinci_rtc *davinci_rtc,
			       u32 val, u32 addr)
अणु
	ग_लिखोl(val, davinci_rtc->base + addr);
पूर्ण

अटल अंतरभूत u32 rtcअगर_पढ़ो(काष्ठा davinci_rtc *davinci_rtc, u32 addr)
अणु
	वापस पढ़ोl(davinci_rtc->base + addr);
पूर्ण

अटल अंतरभूत व्योम rtcअगर_रुको(काष्ठा davinci_rtc *davinci_rtc)
अणु
	जबतक (rtcअगर_पढ़ो(davinci_rtc, PRTCIF_CTLR) & PRTCIF_CTLR_BUSY)
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम rtcss_ग_लिखो(काष्ठा davinci_rtc *davinci_rtc,
			       अचिन्हित दीर्घ val, u8 addr)
अणु
	rtcअगर_रुको(davinci_rtc);

	rtcअगर_ग_लिखो(davinci_rtc, PRTCIF_CTLR_BENL_LSB | addr, PRTCIF_CTLR);
	rtcअगर_ग_लिखो(davinci_rtc, val, PRTCIF_LDATA);

	rtcअगर_रुको(davinci_rtc);
पूर्ण

अटल अंतरभूत u8 rtcss_पढ़ो(काष्ठा davinci_rtc *davinci_rtc, u8 addr)
अणु
	rtcअगर_रुको(davinci_rtc);

	rtcअगर_ग_लिखो(davinci_rtc, PRTCIF_CTLR_सूची | PRTCIF_CTLR_BENL_LSB | addr,
		    PRTCIF_CTLR);

	rtcअगर_रुको(davinci_rtc);

	वापस rtcअगर_पढ़ो(davinci_rtc, PRTCIF_LDATA);
पूर्ण

अटल अंतरभूत व्योम davinci_rtcss_calendar_रुको(काष्ठा davinci_rtc *davinci_rtc)
अणु
	जबतक (rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CCTRL) &
	       PRTCSS_RTC_CCTRL_CALBUSY)
		cpu_relax();
पूर्ण

अटल irqवापस_t davinci_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *class_dev)
अणु
	काष्ठा davinci_rtc *davinci_rtc = class_dev;
	अचिन्हित दीर्घ events = 0;
	u32 irq_flg;
	u8 alm_irq, पंचांगr_irq;
	u8 rtc_ctrl, rtc_cctrl;
	पूर्णांक ret = IRQ_NONE;

	irq_flg = rtcअगर_पढ़ो(davinci_rtc, PRTCIF_INTFLG) &
		  PRTCIF_INTFLG_RTCSS;

	alm_irq = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CCTRL) &
		  PRTCSS_RTC_CCTRL_ALMFLG;

	पंचांगr_irq = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CTRL) &
		  PRTCSS_RTC_CTRL_TMRFLG;

	अगर (irq_flg) अणु
		अगर (alm_irq) अणु
			events |= RTC_IRQF | RTC_AF;
			rtc_cctrl = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CCTRL);
			rtc_cctrl |=  PRTCSS_RTC_CCTRL_ALMFLG;
			rtcss_ग_लिखो(davinci_rtc, rtc_cctrl, PRTCSS_RTC_CCTRL);
		पूर्ण अन्यथा अगर (पंचांगr_irq) अणु
			events |= RTC_IRQF | RTC_PF;
			rtc_ctrl = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CTRL);
			rtc_ctrl |=  PRTCSS_RTC_CTRL_TMRFLG;
			rtcss_ग_लिखो(davinci_rtc, rtc_ctrl, PRTCSS_RTC_CTRL);
		पूर्ण

		rtcअगर_ग_लिखो(davinci_rtc, PRTCIF_INTFLG_RTCSS,
				    PRTCIF_INTFLG);
		rtc_update_irq(davinci_rtc->rtc, 1, events);

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
davinci_rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u8 rtc_ctrl;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	rtc_ctrl = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CTRL);

	चयन (cmd) अणु
	हाल RTC_WIE_ON:
		rtc_ctrl |= PRTCSS_RTC_CTRL_WEN | PRTCSS_RTC_CTRL_WDTFLG;
		अवरोध;
	हाल RTC_WIE_OFF:
		rtc_ctrl &= ~PRTCSS_RTC_CTRL_WEN;
		अवरोध;
	शेष:
		ret = -ENOIOCTLCMD;
	पूर्ण

	rtcss_ग_लिखो(davinci_rtc, rtc_ctrl, PRTCSS_RTC_CTRL);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम convertfromdays(u16 days, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक पंचांगp_days, year, mon;

	क्रम (year = 2000;; year++) अणु
		पंचांगp_days = rtc_year_days(1, 12, year);
		अगर (days >= पंचांगp_days)
			days -= पंचांगp_days;
		अन्यथा अणु
			क्रम (mon = 0;; mon++) अणु
				पंचांगp_days = rtc_month_days(mon, year);
				अगर (days >= पंचांगp_days) अणु
					days -= पंचांगp_days;
				पूर्ण अन्यथा अणु
					पंचांग->पंचांग_year = year - 1900;
					पंचांग->पंचांग_mon = mon;
					पंचांग->पंचांग_mday = days + 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम convert2days(u16 *days, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक i;
	*days = 0;

	क्रम (i = 2000; i < 1900 + पंचांग->पंचांग_year; i++)
		*days += rtc_year_days(1, 12, i);

	*days += rtc_year_days(पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, 1900 + पंचांग->पंचांग_year);
पूर्ण

अटल पूर्णांक davinci_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u16 days = 0;
	u8 day0, day1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	पंचांग->पंचांग_sec = bcd2bin(rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_SEC));

	davinci_rtcss_calendar_रुको(davinci_rtc);
	पंचांग->पंचांग_min = bcd2bin(rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_MIN));

	davinci_rtcss_calendar_रुको(davinci_rtc);
	पंचांग->पंचांग_hour = bcd2bin(rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_HOUR));

	davinci_rtcss_calendar_रुको(davinci_rtc);
	day0 = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_DAY0);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	day1 = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_DAY1);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	days |= day1;
	days <<= 8;
	days |= day0;

	convertfromdays(days, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u16 days;
	u8 rtc_cctrl;
	अचिन्हित दीर्घ flags;

	convert2days(&days, पंचांग);

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, bin2bcd(पंचांग->पंचांग_sec), PRTCSS_RTC_SEC);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, bin2bcd(पंचांग->पंचांग_min), PRTCSS_RTC_MIN);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, bin2bcd(पंचांग->पंचांग_hour), PRTCSS_RTC_HOUR);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, days & 0xFF, PRTCSS_RTC_DAY0);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, (days & 0xFF00) >> 8, PRTCSS_RTC_DAY1);

	rtc_cctrl = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CCTRL);
	rtc_cctrl |= PRTCSS_RTC_CCTRL_CAEN;
	rtcss_ग_लिखो(davinci_rtc, rtc_cctrl, PRTCSS_RTC_CCTRL);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u8 rtc_cctrl = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_CCTRL);

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	अगर (enabled)
		rtc_cctrl |= PRTCSS_RTC_CCTRL_DAEN |
			     PRTCSS_RTC_CCTRL_HAEN |
			     PRTCSS_RTC_CCTRL_MAEN |
			     PRTCSS_RTC_CCTRL_ALMFLG |
			     PRTCSS_RTC_CCTRL_AIEN;
	अन्यथा
		rtc_cctrl &= ~PRTCSS_RTC_CCTRL_AIEN;

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, rtc_cctrl, PRTCSS_RTC_CCTRL);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u16 days = 0;
	u8 day0, day1;
	अचिन्हित दीर्घ flags;

	alm->समय.पंचांग_sec = 0;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	alm->समय.पंचांग_min = bcd2bin(rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_AMIN));

	davinci_rtcss_calendar_रुको(davinci_rtc);
	alm->समय.पंचांग_hour = bcd2bin(rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_AHOUR));

	davinci_rtcss_calendar_रुको(davinci_rtc);
	day0 = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_ADAY0);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	day1 = rtcss_पढ़ो(davinci_rtc, PRTCSS_RTC_ADAY1);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);
	days |= day1;
	days <<= 8;
	days |= day0;

	convertfromdays(days, &alm->समय);

	alm->pending = !!(rtcss_पढ़ो(davinci_rtc,
			  PRTCSS_RTC_CCTRL) &
			PRTCSS_RTC_CCTRL_AIEN);
	alm->enabled = alm->pending && device_may_wakeup(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u16 days;

	convert2days(&days, &alm->समय);

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, bin2bcd(alm->समय.पंचांग_min), PRTCSS_RTC_AMIN);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, bin2bcd(alm->समय.पंचांग_hour), PRTCSS_RTC_AHOUR);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, days & 0xFF, PRTCSS_RTC_ADAY0);

	davinci_rtcss_calendar_रुको(davinci_rtc);
	rtcss_ग_लिखो(davinci_rtc, (days & 0xFF00) >> 8, PRTCSS_RTC_ADAY1);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops davinci_rtc_ops = अणु
	.ioctl			= davinci_rtc_ioctl,
	.पढ़ो_समय		= davinci_rtc_पढ़ो_समय,
	.set_समय		= davinci_rtc_set_समय,
	.alarm_irq_enable	= davinci_rtc_alarm_irq_enable,
	.पढ़ो_alarm		= davinci_rtc_पढ़ो_alarm,
	.set_alarm		= davinci_rtc_set_alarm,
पूर्ण;

अटल पूर्णांक __init davinci_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा davinci_rtc *davinci_rtc;
	पूर्णांक ret = 0;

	davinci_rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा davinci_rtc), GFP_KERNEL);
	अगर (!davinci_rtc)
		वापस -ENOMEM;

	davinci_rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (davinci_rtc->irq < 0)
		वापस davinci_rtc->irq;

	davinci_rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(davinci_rtc->base))
		वापस PTR_ERR(davinci_rtc->base);

	platक्रमm_set_drvdata(pdev, davinci_rtc);

	davinci_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(davinci_rtc->rtc))
		वापस PTR_ERR(davinci_rtc->rtc);

	davinci_rtc->rtc->ops = &davinci_rtc_ops;
	davinci_rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	davinci_rtc->rtc->range_max = RTC_TIMESTAMP_BEGIN_2000 + (1 << 16) * 86400ULL - 1;

	rtcअगर_ग_लिखो(davinci_rtc, PRTCIF_INTFLG_RTCSS, PRTCIF_INTFLG);
	rtcअगर_ग_लिखो(davinci_rtc, 0, PRTCIF_INTEN);
	rtcss_ग_लिखो(davinci_rtc, 0, PRTCSS_RTC_INTC_EXTENA1);

	rtcss_ग_लिखो(davinci_rtc, 0, PRTCSS_RTC_CTRL);
	rtcss_ग_लिखो(davinci_rtc, 0, PRTCSS_RTC_CCTRL);

	ret = devm_request_irq(dev, davinci_rtc->irq, davinci_rtc_पूर्णांकerrupt,
			  0, "davinci_rtc", davinci_rtc);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register davinci RTC interrupt\n");
		वापस ret;
	पूर्ण

	/* Enable पूर्णांकerrupts */
	rtcअगर_ग_लिखो(davinci_rtc, PRTCIF_INTEN_RTCSS, PRTCIF_INTEN);
	rtcss_ग_लिखो(davinci_rtc, PRTCSS_RTC_INTC_EXTENA1_MASK,
			    PRTCSS_RTC_INTC_EXTENA1);

	rtcss_ग_लिखो(davinci_rtc, PRTCSS_RTC_CCTRL_CAEN, PRTCSS_RTC_CCTRL);

	device_init_wakeup(&pdev->dev, 0);

	वापस devm_rtc_रेजिस्टर_device(davinci_rtc->rtc);
पूर्ण

अटल पूर्णांक __निकास davinci_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_rtc *davinci_rtc = platक्रमm_get_drvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);

	rtcअगर_ग_लिखो(davinci_rtc, 0, PRTCIF_INTEN);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_rtc_driver = अणु
	.हटाओ		= __निकास_p(davinci_rtc_हटाओ),
	.driver		= अणु
		.name = "rtc_davinci",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(davinci_rtc_driver, davinci_rtc_probe);

MODULE_AUTHOR("Miguel Aguilar <miguel.aguilar@ridgerun.com>");
MODULE_DESCRIPTION("Texas Instruments DaVinci PRTC Driver");
MODULE_LICENSE("GPL");
