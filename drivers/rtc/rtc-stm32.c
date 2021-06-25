<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2017
 * Author:  Amelie Delaunay <amelie.delaunay@st.com>
 */

#समावेश <linux/bcd.h>
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

#घोषणा DRIVER_NAME "stm32_rtc"

/* STM32_RTC_TR bit fields  */
#घोषणा STM32_RTC_TR_SEC_SHIFT		0
#घोषणा STM32_RTC_TR_SEC		GENMASK(6, 0)
#घोषणा STM32_RTC_TR_MIN_SHIFT		8
#घोषणा STM32_RTC_TR_MIN		GENMASK(14, 8)
#घोषणा STM32_RTC_TR_HOUR_SHIFT		16
#घोषणा STM32_RTC_TR_HOUR		GENMASK(21, 16)

/* STM32_RTC_DR bit fields */
#घोषणा STM32_RTC_DR_DATE_SHIFT		0
#घोषणा STM32_RTC_DR_DATE		GENMASK(5, 0)
#घोषणा STM32_RTC_DR_MONTH_SHIFT	8
#घोषणा STM32_RTC_DR_MONTH		GENMASK(12, 8)
#घोषणा STM32_RTC_DR_WDAY_SHIFT		13
#घोषणा STM32_RTC_DR_WDAY		GENMASK(15, 13)
#घोषणा STM32_RTC_DR_YEAR_SHIFT		16
#घोषणा STM32_RTC_DR_YEAR		GENMASK(23, 16)

/* STM32_RTC_CR bit fields */
#घोषणा STM32_RTC_CR_FMT		BIT(6)
#घोषणा STM32_RTC_CR_ALRAE		BIT(8)
#घोषणा STM32_RTC_CR_ALRAIE		BIT(12)

/* STM32_RTC_ISR/STM32_RTC_ICSR bit fields */
#घोषणा STM32_RTC_ISR_ALRAWF		BIT(0)
#घोषणा STM32_RTC_ISR_INITS		BIT(4)
#घोषणा STM32_RTC_ISR_RSF		BIT(5)
#घोषणा STM32_RTC_ISR_INITF		BIT(6)
#घोषणा STM32_RTC_ISR_INIT		BIT(7)
#घोषणा STM32_RTC_ISR_ALRAF		BIT(8)

/* STM32_RTC_PRER bit fields */
#घोषणा STM32_RTC_PRER_PRED_S_SHIFT	0
#घोषणा STM32_RTC_PRER_PRED_S		GENMASK(14, 0)
#घोषणा STM32_RTC_PRER_PRED_A_SHIFT	16
#घोषणा STM32_RTC_PRER_PRED_A		GENMASK(22, 16)

/* STM32_RTC_ALRMAR and STM32_RTC_ALRMBR bit fields */
#घोषणा STM32_RTC_ALRMXR_SEC_SHIFT	0
#घोषणा STM32_RTC_ALRMXR_SEC		GENMASK(6, 0)
#घोषणा STM32_RTC_ALRMXR_SEC_MASK	BIT(7)
#घोषणा STM32_RTC_ALRMXR_MIN_SHIFT	8
#घोषणा STM32_RTC_ALRMXR_MIN		GENMASK(14, 8)
#घोषणा STM32_RTC_ALRMXR_MIN_MASK	BIT(15)
#घोषणा STM32_RTC_ALRMXR_HOUR_SHIFT	16
#घोषणा STM32_RTC_ALRMXR_HOUR		GENMASK(21, 16)
#घोषणा STM32_RTC_ALRMXR_PM		BIT(22)
#घोषणा STM32_RTC_ALRMXR_HOUR_MASK	BIT(23)
#घोषणा STM32_RTC_ALRMXR_DATE_SHIFT	24
#घोषणा STM32_RTC_ALRMXR_DATE		GENMASK(29, 24)
#घोषणा STM32_RTC_ALRMXR_WDSEL		BIT(30)
#घोषणा STM32_RTC_ALRMXR_WDAY_SHIFT	24
#घोषणा STM32_RTC_ALRMXR_WDAY		GENMASK(27, 24)
#घोषणा STM32_RTC_ALRMXR_DATE_MASK	BIT(31)

/* STM32_RTC_SR/_SCR bit fields */
#घोषणा STM32_RTC_SR_ALRA		BIT(0)

/* STM32_RTC_VERR bit fields */
#घोषणा STM32_RTC_VERR_MINREV_SHIFT	0
#घोषणा STM32_RTC_VERR_MINREV		GENMASK(3, 0)
#घोषणा STM32_RTC_VERR_MAJREV_SHIFT	4
#घोषणा STM32_RTC_VERR_MAJREV		GENMASK(7, 4)

/* STM32_RTC_WPR key स्थिरants */
#घोषणा RTC_WPR_1ST_KEY			0xCA
#घोषणा RTC_WPR_2ND_KEY			0x53
#घोषणा RTC_WPR_WRONG_KEY		0xFF

/* Max STM32 RTC रेजिस्टर offset is 0x3FC */
#घोषणा UNDEF_REG			0xFFFF

काष्ठा sपंचांग32_rtc;

काष्ठा sपंचांग32_rtc_रेजिस्टरs अणु
	u16 tr;
	u16 dr;
	u16 cr;
	u16 isr;
	u16 prer;
	u16 alrmar;
	u16 wpr;
	u16 sr;
	u16 scr;
	u16 verr;
पूर्ण;

काष्ठा sपंचांग32_rtc_events अणु
	u32 alra;
पूर्ण;

काष्ठा sपंचांग32_rtc_data अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs regs;
	स्थिर काष्ठा sपंचांग32_rtc_events events;
	व्योम (*clear_events)(काष्ठा sपंचांग32_rtc *rtc, अचिन्हित पूर्णांक flags);
	bool has_pclk;
	bool need_dbp;
	bool has_wakeirq;
पूर्ण;

काष्ठा sपंचांग32_rtc अणु
	काष्ठा rtc_device *rtc_dev;
	व्योम __iomem *base;
	काष्ठा regmap *dbp;
	अचिन्हित पूर्णांक dbp_reg;
	अचिन्हित पूर्णांक dbp_mask;
	काष्ठा clk *pclk;
	काष्ठा clk *rtc_ck;
	स्थिर काष्ठा sपंचांग32_rtc_data *data;
	पूर्णांक irq_alarm;
	पूर्णांक wakeirq_alarm;
पूर्ण;

अटल व्योम sपंचांग32_rtc_wpr_unlock(काष्ठा sपंचांग32_rtc *rtc)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;

	ग_लिखोl_relaxed(RTC_WPR_1ST_KEY, rtc->base + regs->wpr);
	ग_लिखोl_relaxed(RTC_WPR_2ND_KEY, rtc->base + regs->wpr);
पूर्ण

अटल व्योम sपंचांग32_rtc_wpr_lock(काष्ठा sपंचांग32_rtc *rtc)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;

	ग_लिखोl_relaxed(RTC_WPR_WRONG_KEY, rtc->base + regs->wpr);
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_enter_init_mode(काष्ठा sपंचांग32_rtc *rtc)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक isr = पढ़ोl_relaxed(rtc->base + regs->isr);

	अगर (!(isr & STM32_RTC_ISR_INITF)) अणु
		isr |= STM32_RTC_ISR_INIT;
		ग_लिखोl_relaxed(isr, rtc->base + regs->isr);

		/*
		 * It takes around 2 rtc_ck घड़ी cycles to enter in
		 * initialization phase mode (and have INITF flag set). As
		 * slowest rtc_ck frequency may be 32kHz and highest should be
		 * 1MHz, we poll every 10 us with a समयout of 100ms.
		 */
		वापस पढ़ोl_relaxed_poll_समयout_atomic(
					rtc->base + regs->isr,
					isr, (isr & STM32_RTC_ISR_INITF),
					10, 100000);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_rtc_निकास_init_mode(काष्ठा sपंचांग32_rtc *rtc)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक isr = पढ़ोl_relaxed(rtc->base + regs->isr);

	isr &= ~STM32_RTC_ISR_INIT;
	ग_लिखोl_relaxed(isr, rtc->base + regs->isr);
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_रुको_sync(काष्ठा sपंचांग32_rtc *rtc)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक isr = पढ़ोl_relaxed(rtc->base + regs->isr);

	isr &= ~STM32_RTC_ISR_RSF;
	ग_लिखोl_relaxed(isr, rtc->base + regs->isr);

	/*
	 * Wait क्रम RSF to be set to ensure the calendar रेजिस्टरs are
	 * synchronised, it takes around 2 rtc_ck घड़ी cycles
	 */
	वापस पढ़ोl_relaxed_poll_समयout_atomic(rtc->base + regs->isr,
						 isr,
						 (isr & STM32_RTC_ISR_RSF),
						 10, 100000);
पूर्ण

अटल व्योम sपंचांग32_rtc_clear_event_flags(काष्ठा sपंचांग32_rtc *rtc,
					अचिन्हित पूर्णांक flags)
अणु
	rtc->data->clear_events(rtc, flags);
पूर्ण

अटल irqवापस_t sपंचांग32_rtc_alarm_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांग32_rtc *rtc = (काष्ठा sपंचांग32_rtc *)dev_id;
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	स्थिर काष्ठा sपंचांग32_rtc_events *evts = &rtc->data->events;
	अचिन्हित पूर्णांक status, cr;

	rtc_lock(rtc->rtc_dev);

	status = पढ़ोl_relaxed(rtc->base + regs->sr);
	cr = पढ़ोl_relaxed(rtc->base + regs->cr);

	अगर ((status & evts->alra) &&
	    (cr & STM32_RTC_CR_ALRAIE)) अणु
		/* Alarm A flag - Alarm पूर्णांकerrupt */
		dev_dbg(&rtc->rtc_dev->dev, "Alarm occurred\n");

		/* Pass event to the kernel */
		rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);

		/* Clear event flags, otherwise new events won't be received */
		sपंचांग32_rtc_clear_event_flags(rtc, evts->alra);
	पूर्ण

	rtc_unlock(rtc->rtc_dev);

	वापस IRQ_HANDLED;
पूर्ण

/* Convert rtc_समय काष्ठाure from bin to bcd क्रमmat */
अटल व्योम पंचांग2bcd(काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bin2bcd(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bin2bcd(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bin2bcd(पंचांग->पंचांग_hour);

	पंचांग->पंचांग_mday = bin2bcd(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bin2bcd(पंचांग->पंचांग_mon + 1);
	पंचांग->पंचांग_year = bin2bcd(पंचांग->पंचांग_year - 100);
	/*
	 * Number of days since Sunday
	 * - on kernel side, 0=Sunday...6=Saturday
	 * - on rtc side, 0=invalid,1=Monday...7=Sunday
	 */
	पंचांग->पंचांग_wday = (!पंचांग->पंचांग_wday) ? 7 : पंचांग->पंचांग_wday;
पूर्ण

/* Convert rtc_समय काष्ठाure from bcd to bin क्रमmat */
अटल व्योम bcd2पंचांग(काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);

	पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon) - 1;
	पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year) + 100;
	/*
	 * Number of days since Sunday
	 * - on kernel side, 0=Sunday...6=Saturday
	 * - on rtc side, 0=invalid,1=Monday...7=Sunday
	 */
	पंचांग->पंचांग_wday %= 7;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक tr, dr;

	/* Time and Date in BCD क्रमmat */
	tr = पढ़ोl_relaxed(rtc->base + regs->tr);
	dr = पढ़ोl_relaxed(rtc->base + regs->dr);

	पंचांग->पंचांग_sec = (tr & STM32_RTC_TR_SEC) >> STM32_RTC_TR_SEC_SHIFT;
	पंचांग->पंचांग_min = (tr & STM32_RTC_TR_MIN) >> STM32_RTC_TR_MIN_SHIFT;
	पंचांग->पंचांग_hour = (tr & STM32_RTC_TR_HOUR) >> STM32_RTC_TR_HOUR_SHIFT;

	पंचांग->पंचांग_mday = (dr & STM32_RTC_DR_DATE) >> STM32_RTC_DR_DATE_SHIFT;
	पंचांग->पंचांग_mon = (dr & STM32_RTC_DR_MONTH) >> STM32_RTC_DR_MONTH_SHIFT;
	पंचांग->पंचांग_year = (dr & STM32_RTC_DR_YEAR) >> STM32_RTC_DR_YEAR_SHIFT;
	पंचांग->पंचांग_wday = (dr & STM32_RTC_DR_WDAY) >> STM32_RTC_DR_WDAY_SHIFT;

	/* We करोn't report पंचांग_yday and पंचांग_isdst */

	bcd2पंचांग(पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक tr, dr;
	पूर्णांक ret = 0;

	पंचांग2bcd(पंचांग);

	/* Time in BCD क्रमmat */
	tr = ((पंचांग->पंचांग_sec << STM32_RTC_TR_SEC_SHIFT) & STM32_RTC_TR_SEC) |
	     ((पंचांग->पंचांग_min << STM32_RTC_TR_MIN_SHIFT) & STM32_RTC_TR_MIN) |
	     ((पंचांग->पंचांग_hour << STM32_RTC_TR_HOUR_SHIFT) & STM32_RTC_TR_HOUR);

	/* Date in BCD क्रमmat */
	dr = ((पंचांग->पंचांग_mday << STM32_RTC_DR_DATE_SHIFT) & STM32_RTC_DR_DATE) |
	     ((पंचांग->पंचांग_mon << STM32_RTC_DR_MONTH_SHIFT) & STM32_RTC_DR_MONTH) |
	     ((पंचांग->पंचांग_year << STM32_RTC_DR_YEAR_SHIFT) & STM32_RTC_DR_YEAR) |
	     ((पंचांग->पंचांग_wday << STM32_RTC_DR_WDAY_SHIFT) & STM32_RTC_DR_WDAY);

	sपंचांग32_rtc_wpr_unlock(rtc);

	ret = sपंचांग32_rtc_enter_init_mode(rtc);
	अगर (ret) अणु
		dev_err(dev, "Can't enter in init mode. Set time aborted.\n");
		जाओ end;
	पूर्ण

	ग_लिखोl_relaxed(tr, rtc->base + regs->tr);
	ग_लिखोl_relaxed(dr, rtc->base + regs->dr);

	sपंचांग32_rtc_निकास_init_mode(rtc);

	ret = sपंचांग32_rtc_रुको_sync(rtc);
end:
	sपंचांग32_rtc_wpr_lock(rtc);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	स्थिर काष्ठा sपंचांग32_rtc_events *evts = &rtc->data->events;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	अचिन्हित पूर्णांक alrmar, cr, status;

	alrmar = पढ़ोl_relaxed(rtc->base + regs->alrmar);
	cr = पढ़ोl_relaxed(rtc->base + regs->cr);
	status = पढ़ोl_relaxed(rtc->base + regs->sr);

	अगर (alrmar & STM32_RTC_ALRMXR_DATE_MASK) अणु
		/*
		 * Date/day करोesn't matter in Alarm comparison so alarm
		 * triggers every day
		 */
		पंचांग->पंचांग_mday = -1;
		पंचांग->पंचांग_wday = -1;
	पूर्ण अन्यथा अणु
		अगर (alrmar & STM32_RTC_ALRMXR_WDSEL) अणु
			/* Alarm is set to a day of week */
			पंचांग->पंचांग_mday = -1;
			पंचांग->पंचांग_wday = (alrmar & STM32_RTC_ALRMXR_WDAY) >>
				      STM32_RTC_ALRMXR_WDAY_SHIFT;
			पंचांग->पंचांग_wday %= 7;
		पूर्ण अन्यथा अणु
			/* Alarm is set to a day of month */
			पंचांग->पंचांग_wday = -1;
			पंचांग->पंचांग_mday = (alrmar & STM32_RTC_ALRMXR_DATE) >>
				       STM32_RTC_ALRMXR_DATE_SHIFT;
		पूर्ण
	पूर्ण

	अगर (alrmar & STM32_RTC_ALRMXR_HOUR_MASK) अणु
		/* Hours करोn't matter in Alarm comparison */
		पंचांग->पंचांग_hour = -1;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_hour = (alrmar & STM32_RTC_ALRMXR_HOUR) >>
			       STM32_RTC_ALRMXR_HOUR_SHIFT;
		अगर (alrmar & STM32_RTC_ALRMXR_PM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण

	अगर (alrmar & STM32_RTC_ALRMXR_MIN_MASK) अणु
		/* Minutes करोn't matter in Alarm comparison */
		पंचांग->पंचांग_min = -1;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_min = (alrmar & STM32_RTC_ALRMXR_MIN) >>
			      STM32_RTC_ALRMXR_MIN_SHIFT;
	पूर्ण

	अगर (alrmar & STM32_RTC_ALRMXR_SEC_MASK) अणु
		/* Seconds करोn't matter in Alarm comparison */
		पंचांग->पंचांग_sec = -1;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_sec = (alrmar & STM32_RTC_ALRMXR_SEC) >>
			      STM32_RTC_ALRMXR_SEC_SHIFT;
	पूर्ण

	bcd2पंचांग(पंचांग);

	alrm->enabled = (cr & STM32_RTC_CR_ALRAE) ? 1 : 0;
	alrm->pending = (status & evts->alra) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	स्थिर काष्ठा sपंचांग32_rtc_events *evts = &rtc->data->events;
	अचिन्हित पूर्णांक cr;

	cr = पढ़ोl_relaxed(rtc->base + regs->cr);

	sपंचांग32_rtc_wpr_unlock(rtc);

	/* We expose Alarm A to the kernel */
	अगर (enabled)
		cr |= (STM32_RTC_CR_ALRAIE | STM32_RTC_CR_ALRAE);
	अन्यथा
		cr &= ~(STM32_RTC_CR_ALRAIE | STM32_RTC_CR_ALRAE);
	ग_लिखोl_relaxed(cr, rtc->base + regs->cr);

	/* Clear event flags, otherwise new events won't be received */
	sपंचांग32_rtc_clear_event_flags(rtc, evts->alra);

	sपंचांग32_rtc_wpr_lock(rtc);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_valid_alrm(काष्ठा sपंचांग32_rtc *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	पूर्णांक cur_day, cur_mon, cur_year, cur_hour, cur_min, cur_sec;
	अचिन्हित पूर्णांक dr = पढ़ोl_relaxed(rtc->base + regs->dr);
	अचिन्हित पूर्णांक tr = पढ़ोl_relaxed(rtc->base + regs->tr);

	cur_day = (dr & STM32_RTC_DR_DATE) >> STM32_RTC_DR_DATE_SHIFT;
	cur_mon = (dr & STM32_RTC_DR_MONTH) >> STM32_RTC_DR_MONTH_SHIFT;
	cur_year = (dr & STM32_RTC_DR_YEAR) >> STM32_RTC_DR_YEAR_SHIFT;
	cur_sec = (tr & STM32_RTC_TR_SEC) >> STM32_RTC_TR_SEC_SHIFT;
	cur_min = (tr & STM32_RTC_TR_MIN) >> STM32_RTC_TR_MIN_SHIFT;
	cur_hour = (tr & STM32_RTC_TR_HOUR) >> STM32_RTC_TR_HOUR_SHIFT;

	/*
	 * Assuming current date is M-D-Y H:M:S.
	 * RTC alarm can't be set on a specअगरic month and year.
	 * So the valid alarm range is:
	 *	M-D-Y H:M:S < alarm <= (M+1)-D-Y H:M:S
	 * with a specअगरic हाल क्रम December...
	 */
	अगर ((((पंचांग->पंचांग_year > cur_year) &&
	      (पंचांग->पंचांग_mon == 0x1) && (cur_mon == 0x12)) ||
	     ((पंचांग->पंचांग_year == cur_year) &&
	      (पंचांग->पंचांग_mon <= cur_mon + 1))) &&
	    ((पंचांग->पंचांग_mday > cur_day) ||
	     ((पंचांग->पंचांग_mday == cur_day) &&
	     ((पंचांग->पंचांग_hour > cur_hour) ||
	      ((पंचांग->पंचांग_hour == cur_hour) && (पंचांग->पंचांग_min > cur_min)) ||
	      ((पंचांग->पंचांग_hour == cur_hour) && (पंचांग->पंचांग_min == cur_min) &&
	       (पंचांग->पंचांग_sec >= cur_sec))))))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	अचिन्हित पूर्णांक cr, isr, alrmar;
	पूर्णांक ret = 0;

	पंचांग2bcd(पंचांग);

	/*
	 * RTC alarm can't be set on a specअगरic date, unless this date is
	 * up to the same day of month next month.
	 */
	अगर (sपंचांग32_rtc_valid_alrm(rtc, पंचांग) < 0) अणु
		dev_err(dev, "Alarm can be set only on upcoming month.\n");
		वापस -EINVAL;
	पूर्ण

	alrmar = 0;
	/* पंचांग_year and पंचांग_mon are not used because not supported by RTC */
	alrmar |= (पंचांग->पंचांग_mday << STM32_RTC_ALRMXR_DATE_SHIFT) &
		  STM32_RTC_ALRMXR_DATE;
	/* 24-hour क्रमmat */
	alrmar &= ~STM32_RTC_ALRMXR_PM;
	alrmar |= (पंचांग->पंचांग_hour << STM32_RTC_ALRMXR_HOUR_SHIFT) &
		  STM32_RTC_ALRMXR_HOUR;
	alrmar |= (पंचांग->पंचांग_min << STM32_RTC_ALRMXR_MIN_SHIFT) &
		  STM32_RTC_ALRMXR_MIN;
	alrmar |= (पंचांग->पंचांग_sec << STM32_RTC_ALRMXR_SEC_SHIFT) &
		  STM32_RTC_ALRMXR_SEC;

	sपंचांग32_rtc_wpr_unlock(rtc);

	/* Disable Alarm */
	cr = पढ़ोl_relaxed(rtc->base + regs->cr);
	cr &= ~STM32_RTC_CR_ALRAE;
	ग_लिखोl_relaxed(cr, rtc->base + regs->cr);

	/*
	 * Poll Alarm ग_लिखो flag to be sure that Alarm update is allowed: it
	 * takes around 2 rtc_ck घड़ी cycles
	 */
	ret = पढ़ोl_relaxed_poll_समयout_atomic(rtc->base + regs->isr,
						isr,
						(isr & STM32_RTC_ISR_ALRAWF),
						10, 100000);

	अगर (ret) अणु
		dev_err(dev, "Alarm update not allowed\n");
		जाओ end;
	पूर्ण

	/* Write to Alarm रेजिस्टर */
	ग_लिखोl_relaxed(alrmar, rtc->base + regs->alrmar);

	sपंचांग32_rtc_alarm_irq_enable(dev, alrm->enabled);
end:
	sपंचांग32_rtc_wpr_lock(rtc);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sपंचांग32_rtc_ops = अणु
	.पढ़ो_समय	= sपंचांग32_rtc_पढ़ो_समय,
	.set_समय	= sपंचांग32_rtc_set_समय,
	.पढ़ो_alarm	= sपंचांग32_rtc_पढ़ो_alarm,
	.set_alarm	= sपंचांग32_rtc_set_alarm,
	.alarm_irq_enable = sपंचांग32_rtc_alarm_irq_enable,
पूर्ण;

अटल व्योम sपंचांग32_rtc_clear_events(काष्ठा sपंचांग32_rtc *rtc,
				   अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;

	/* Flags are cleared by writing 0 in RTC_ISR */
	ग_लिखोl_relaxed(पढ़ोl_relaxed(rtc->base + regs->isr) & ~flags,
		       rtc->base + regs->isr);
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_rtc_data sपंचांग32_rtc_data = अणु
	.has_pclk = false,
	.need_dbp = true,
	.has_wakeirq = false,
	.regs = अणु
		.tr = 0x00,
		.dr = 0x04,
		.cr = 0x08,
		.isr = 0x0C,
		.prer = 0x10,
		.alrmar = 0x1C,
		.wpr = 0x24,
		.sr = 0x0C, /* set to ISR offset to ease alarm management */
		.scr = UNDEF_REG,
		.verr = UNDEF_REG,
	पूर्ण,
	.events = अणु
		.alra = STM32_RTC_ISR_ALRAF,
	पूर्ण,
	.clear_events = sपंचांग32_rtc_clear_events,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_rtc_data sपंचांग32h7_rtc_data = अणु
	.has_pclk = true,
	.need_dbp = true,
	.has_wakeirq = false,
	.regs = अणु
		.tr = 0x00,
		.dr = 0x04,
		.cr = 0x08,
		.isr = 0x0C,
		.prer = 0x10,
		.alrmar = 0x1C,
		.wpr = 0x24,
		.sr = 0x0C, /* set to ISR offset to ease alarm management */
		.scr = UNDEF_REG,
		.verr = UNDEF_REG,
	पूर्ण,
	.events = अणु
		.alra = STM32_RTC_ISR_ALRAF,
	पूर्ण,
	.clear_events = sपंचांग32_rtc_clear_events,
पूर्ण;

अटल व्योम sपंचांग32mp1_rtc_clear_events(काष्ठा sपंचांग32_rtc *rtc,
				      अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sपंचांग32_rtc_रेजिस्टरs regs = rtc->data->regs;

	/* Flags are cleared by writing 1 in RTC_SCR */
	ग_लिखोl_relaxed(flags, rtc->base + regs.scr);
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_rtc_data sपंचांग32mp1_data = अणु
	.has_pclk = true,
	.need_dbp = false,
	.has_wakeirq = true,
	.regs = अणु
		.tr = 0x00,
		.dr = 0x04,
		.cr = 0x18,
		.isr = 0x0C, /* named RTC_ICSR on sपंचांग32mp1 */
		.prer = 0x10,
		.alrmar = 0x40,
		.wpr = 0x24,
		.sr = 0x50,
		.scr = 0x5C,
		.verr = 0x3F4,
	पूर्ण,
	.events = अणु
		.alra = STM32_RTC_SR_ALRA,
	पूर्ण,
	.clear_events = sपंचांग32mp1_rtc_clear_events,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_rtc_of_match[] = अणु
	अणु .compatible = "st,stm32-rtc", .data = &sपंचांग32_rtc_data पूर्ण,
	अणु .compatible = "st,stm32h7-rtc", .data = &sपंचांग32h7_rtc_data पूर्ण,
	अणु .compatible = "st,stm32mp1-rtc", .data = &sपंचांग32mp1_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_rtc_of_match);

अटल पूर्णांक sपंचांग32_rtc_init(काष्ठा platक्रमm_device *pdev,
			  काष्ठा sपंचांग32_rtc *rtc)
अणु
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक prer, pred_a, pred_s, pred_a_max, pred_s_max, cr;
	अचिन्हित पूर्णांक rate;
	पूर्णांक ret = 0;

	rate = clk_get_rate(rtc->rtc_ck);

	/* Find preभाग_a and preभाग_s to obtain the 1Hz calendar घड़ी */
	pred_a_max = STM32_RTC_PRER_PRED_A >> STM32_RTC_PRER_PRED_A_SHIFT;
	pred_s_max = STM32_RTC_PRER_PRED_S >> STM32_RTC_PRER_PRED_S_SHIFT;

	क्रम (pred_a = pred_a_max; pred_a + 1 > 0; pred_a--) अणु
		pred_s = (rate / (pred_a + 1)) - 1;

		अगर (((pred_s + 1) * (pred_a + 1)) == rate)
			अवरोध;
	पूर्ण

	/*
	 * Can't find a 1Hz, so give priority to RTC घातer consumption
	 * by choosing the higher possible value क्रम preभाग_a
	 */
	अगर ((pred_s > pred_s_max) || (pred_a > pred_a_max)) अणु
		pred_a = pred_a_max;
		pred_s = (rate / (pred_a + 1)) - 1;

		dev_warn(&pdev->dev, "rtc_ck is %s\n",
			 (rate < ((pred_a + 1) * (pred_s + 1))) ?
			 "fast" : "slow");
	पूर्ण

	sपंचांग32_rtc_wpr_unlock(rtc);

	ret = sपंचांग32_rtc_enter_init_mode(rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Can't enter in init mode. Prescaler config failed.\n");
		जाओ end;
	पूर्ण

	prer = (pred_s << STM32_RTC_PRER_PRED_S_SHIFT) & STM32_RTC_PRER_PRED_S;
	ग_लिखोl_relaxed(prer, rtc->base + regs->prer);
	prer |= (pred_a << STM32_RTC_PRER_PRED_A_SHIFT) & STM32_RTC_PRER_PRED_A;
	ग_लिखोl_relaxed(prer, rtc->base + regs->prer);

	/* Force 24h समय क्रमmat */
	cr = पढ़ोl_relaxed(rtc->base + regs->cr);
	cr &= ~STM32_RTC_CR_FMT;
	ग_लिखोl_relaxed(cr, rtc->base + regs->cr);

	sपंचांग32_rtc_निकास_init_mode(rtc);

	ret = sपंचांग32_rtc_रुको_sync(rtc);
end:
	sपंचांग32_rtc_wpr_lock(rtc);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_rtc *rtc;
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->base))
		वापस PTR_ERR(rtc->base);

	rtc->data = (काष्ठा sपंचांग32_rtc_data *)
		    of_device_get_match_data(&pdev->dev);
	regs = &rtc->data->regs;

	अगर (rtc->data->need_dbp) अणु
		rtc->dbp = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							   "st,syscfg");
		अगर (IS_ERR(rtc->dbp)) अणु
			dev_err(&pdev->dev, "no st,syscfg\n");
			वापस PTR_ERR(rtc->dbp);
		पूर्ण

		ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "st,syscfg",
						 1, &rtc->dbp_reg);
		अगर (ret) अणु
			dev_err(&pdev->dev, "can't read DBP register offset\n");
			वापस ret;
		पूर्ण

		ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "st,syscfg",
						 2, &rtc->dbp_mask);
		अगर (ret) अणु
			dev_err(&pdev->dev, "can't read DBP register mask\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!rtc->data->has_pclk) अणु
		rtc->pclk = शून्य;
		rtc->rtc_ck = devm_clk_get(&pdev->dev, शून्य);
	पूर्ण अन्यथा अणु
		rtc->pclk = devm_clk_get(&pdev->dev, "pclk");
		अगर (IS_ERR(rtc->pclk)) अणु
			dev_err(&pdev->dev, "no pclk clock");
			वापस PTR_ERR(rtc->pclk);
		पूर्ण
		rtc->rtc_ck = devm_clk_get(&pdev->dev, "rtc_ck");
	पूर्ण
	अगर (IS_ERR(rtc->rtc_ck)) अणु
		dev_err(&pdev->dev, "no rtc_ck clock");
		वापस PTR_ERR(rtc->rtc_ck);
	पूर्ण

	अगर (rtc->data->has_pclk) अणु
		ret = clk_prepare_enable(rtc->pclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(rtc->rtc_ck);
	अगर (ret)
		जाओ err;

	अगर (rtc->data->need_dbp)
		regmap_update_bits(rtc->dbp, rtc->dbp_reg,
				   rtc->dbp_mask, rtc->dbp_mask);

	/*
	 * After a प्रणाली reset, RTC_ISR.INITS flag can be पढ़ो to check अगर
	 * the calendar has been initialized or not. INITS flag is reset by a
	 * घातer-on reset (no vbat, no घातer-supply). It is not reset अगर
	 * rtc_ck parent घड़ी has changed (so RTC prescalers need to be
	 * changed). That's why we cannot rely on this flag to know अगर RTC
	 * init has to be करोne.
	 */
	ret = sपंचांग32_rtc_init(pdev, rtc);
	अगर (ret)
		जाओ err;

	rtc->irq_alarm = platक्रमm_get_irq(pdev, 0);
	अगर (rtc->irq_alarm <= 0) अणु
		ret = rtc->irq_alarm;
		जाओ err;
	पूर्ण

	ret = device_init_wakeup(&pdev->dev, true);
	अगर (rtc->data->has_wakeirq) अणु
		rtc->wakeirq_alarm = platक्रमm_get_irq(pdev, 1);
		अगर (rtc->wakeirq_alarm > 0) अणु
			ret = dev_pm_set_dedicated_wake_irq(&pdev->dev,
							    rtc->wakeirq_alarm);
		पूर्ण अन्यथा अणु
			ret = rtc->wakeirq_alarm;
			अगर (rtc->wakeirq_alarm == -EPROBE_DEFER)
				जाओ err;
		पूर्ण
	पूर्ण
	अगर (ret)
		dev_warn(&pdev->dev, "alarm can't wake up the system: %d", ret);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
						&sपंचांग32_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc->rtc_dev)) अणु
		ret = PTR_ERR(rtc->rtc_dev);
		dev_err(&pdev->dev, "rtc device registration failed, err=%d\n",
			ret);
		जाओ err;
	पूर्ण

	/* Handle RTC alarm पूर्णांकerrupts */
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq_alarm, शून्य,
					sपंचांग32_rtc_alarm_irq, IRQF_ONESHOT,
					pdev->name, rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ%d (alarm interrupt) already claimed\n",
			rtc->irq_alarm);
		जाओ err;
	पूर्ण

	/*
	 * If INITS flag is reset (calendar year field set to 0x00), calendar
	 * must be initialized
	 */
	अगर (!(पढ़ोl_relaxed(rtc->base + regs->isr) & STM32_RTC_ISR_INITS))
		dev_warn(&pdev->dev, "Date/Time must be initialized\n");

	अगर (regs->verr != UNDEF_REG) अणु
		u32 ver = पढ़ोl_relaxed(rtc->base + regs->verr);

		dev_info(&pdev->dev, "registered rev:%d.%d\n",
			 (ver >> STM32_RTC_VERR_MAJREV_SHIFT) & 0xF,
			 (ver >> STM32_RTC_VERR_MINREV_SHIFT) & 0xF);
	पूर्ण

	वापस 0;
err:
	अगर (rtc->data->has_pclk)
		clk_disable_unprepare(rtc->pclk);
	clk_disable_unprepare(rtc->rtc_ck);

	अगर (rtc->data->need_dbp)
		regmap_update_bits(rtc->dbp, rtc->dbp_reg, rtc->dbp_mask, 0);

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_rtc *rtc = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा sपंचांग32_rtc_रेजिस्टरs *regs = &rtc->data->regs;
	अचिन्हित पूर्णांक cr;

	/* Disable पूर्णांकerrupts */
	sपंचांग32_rtc_wpr_unlock(rtc);
	cr = पढ़ोl_relaxed(rtc->base + regs->cr);
	cr &= ~STM32_RTC_CR_ALRAIE;
	ग_लिखोl_relaxed(cr, rtc->base + regs->cr);
	sपंचांग32_rtc_wpr_lock(rtc);

	clk_disable_unprepare(rtc->rtc_ck);
	अगर (rtc->data->has_pclk)
		clk_disable_unprepare(rtc->pclk);

	/* Enable backup करोमुख्य ग_लिखो protection अगर needed */
	अगर (rtc->data->need_dbp)
		regmap_update_bits(rtc->dbp, rtc->dbp_reg, rtc->dbp_mask, 0);

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);

	अगर (rtc->data->has_pclk)
		clk_disable_unprepare(rtc->pclk);

	अगर (device_may_wakeup(dev))
		वापस enable_irq_wake(rtc->irq_alarm);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (rtc->data->has_pclk) अणु
		ret = clk_prepare_enable(rtc->pclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sपंचांग32_rtc_रुको_sync(rtc);
	अगर (ret < 0) अणु
		अगर (rtc->data->has_pclk)
			clk_disable_unprepare(rtc->pclk);
		वापस ret;
	पूर्ण

	अगर (device_may_wakeup(dev))
		वापस disable_irq_wake(rtc->irq_alarm);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_rtc_pm_ops,
			 sपंचांग32_rtc_suspend, sपंचांग32_rtc_resume);

अटल काष्ठा platक्रमm_driver sपंचांग32_rtc_driver = अणु
	.probe		= sपंचांग32_rtc_probe,
	.हटाओ		= sपंचांग32_rtc_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm	= &sपंचांग32_rtc_pm_ops,
		.of_match_table = sपंचांग32_rtc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_rtc_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 Real Time Clock driver");
MODULE_LICENSE("GPL v2");
