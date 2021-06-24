<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP Real Time Clock पूर्णांकerface क्रम Linux
 *
 * Copyright (C) 2003 MontaVista Software, Inc.
 * Author: George G. Davis <gdavis@mvista.com> or <source@mvista.com>
 *
 * Copyright (C) 2006 David Brownell (new RTC framework)
 * Copyright (C) 2014 Johan Hovold <johan@kernel.org>
 */

#समावेश <linux/bcd.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rtc.h>

/*
 * The OMAP RTC is a year/month/day/hours/minutes/seconds BCD घड़ी
 * with century-range alarm matching, driven by the 32kHz घड़ी.
 *
 * The मुख्य user-visible ways it dअगरfers from PC RTCs are by omitting
 * "don't care" alarm fields and sub-second periodic IRQs, and having
 * an स्वतःadjust mechanism to calibrate to the true oscillator rate.
 *
 * Board-specअगरic wiring options include using split घातer mode with
 * RTC_OFF_NOFF used as the reset संकेत (so the RTC won't be reset),
 * and wiring RTC_WAKE_INT (so the RTC alarm can wake the प्रणाली from
 * low घातer modes) क्रम OMAP1 boards (OMAP-L138 has this built पूर्णांकo
 * the SoC). See the BOARD-SPECIFIC CUSTOMIZATION comment.
 */

/* RTC रेजिस्टरs */
#घोषणा OMAP_RTC_SECONDS_REG		0x00
#घोषणा OMAP_RTC_MINUTES_REG		0x04
#घोषणा OMAP_RTC_HOURS_REG		0x08
#घोषणा OMAP_RTC_DAYS_REG		0x0C
#घोषणा OMAP_RTC_MONTHS_REG		0x10
#घोषणा OMAP_RTC_YEARS_REG		0x14
#घोषणा OMAP_RTC_WEEKS_REG		0x18

#घोषणा OMAP_RTC_ALARM_SECONDS_REG	0x20
#घोषणा OMAP_RTC_ALARM_MINUTES_REG	0x24
#घोषणा OMAP_RTC_ALARM_HOURS_REG	0x28
#घोषणा OMAP_RTC_ALARM_DAYS_REG		0x2c
#घोषणा OMAP_RTC_ALARM_MONTHS_REG	0x30
#घोषणा OMAP_RTC_ALARM_YEARS_REG	0x34

#घोषणा OMAP_RTC_CTRL_REG		0x40
#घोषणा OMAP_RTC_STATUS_REG		0x44
#घोषणा OMAP_RTC_INTERRUPTS_REG		0x48

#घोषणा OMAP_RTC_COMP_LSB_REG		0x4c
#घोषणा OMAP_RTC_COMP_MSB_REG		0x50
#घोषणा OMAP_RTC_OSC_REG		0x54

#घोषणा OMAP_RTC_SCRATCH0_REG		0x60
#घोषणा OMAP_RTC_SCRATCH1_REG		0x64
#घोषणा OMAP_RTC_SCRATCH2_REG		0x68

#घोषणा OMAP_RTC_KICK0_REG		0x6c
#घोषणा OMAP_RTC_KICK1_REG		0x70

#घोषणा OMAP_RTC_IRQWAKEEN		0x7c

#घोषणा OMAP_RTC_ALARM2_SECONDS_REG	0x80
#घोषणा OMAP_RTC_ALARM2_MINUTES_REG	0x84
#घोषणा OMAP_RTC_ALARM2_HOURS_REG	0x88
#घोषणा OMAP_RTC_ALARM2_DAYS_REG	0x8c
#घोषणा OMAP_RTC_ALARM2_MONTHS_REG	0x90
#घोषणा OMAP_RTC_ALARM2_YEARS_REG	0x94

#घोषणा OMAP_RTC_PMIC_REG		0x98

/* OMAP_RTC_CTRL_REG bit fields: */
#घोषणा OMAP_RTC_CTRL_SPLIT		BIT(7)
#घोषणा OMAP_RTC_CTRL_DISABLE		BIT(6)
#घोषणा OMAP_RTC_CTRL_SET_32_COUNTER	BIT(5)
#घोषणा OMAP_RTC_CTRL_TEST		BIT(4)
#घोषणा OMAP_RTC_CTRL_MODE_12_24	BIT(3)
#घोषणा OMAP_RTC_CTRL_AUTO_COMP		BIT(2)
#घोषणा OMAP_RTC_CTRL_ROUND_30S		BIT(1)
#घोषणा OMAP_RTC_CTRL_STOP		BIT(0)

/* OMAP_RTC_STATUS_REG bit fields: */
#घोषणा OMAP_RTC_STATUS_POWER_UP	BIT(7)
#घोषणा OMAP_RTC_STATUS_ALARM2		BIT(7)
#घोषणा OMAP_RTC_STATUS_ALARM		BIT(6)
#घोषणा OMAP_RTC_STATUS_1D_EVENT	BIT(5)
#घोषणा OMAP_RTC_STATUS_1H_EVENT	BIT(4)
#घोषणा OMAP_RTC_STATUS_1M_EVENT	BIT(3)
#घोषणा OMAP_RTC_STATUS_1S_EVENT	BIT(2)
#घोषणा OMAP_RTC_STATUS_RUN		BIT(1)
#घोषणा OMAP_RTC_STATUS_BUSY		BIT(0)

/* OMAP_RTC_INTERRUPTS_REG bit fields: */
#घोषणा OMAP_RTC_INTERRUPTS_IT_ALARM2	BIT(4)
#घोषणा OMAP_RTC_INTERRUPTS_IT_ALARM	BIT(3)
#घोषणा OMAP_RTC_INTERRUPTS_IT_TIMER	BIT(2)

/* OMAP_RTC_OSC_REG bit fields: */
#घोषणा OMAP_RTC_OSC_32KCLK_EN		BIT(6)
#घोषणा OMAP_RTC_OSC_SEL_32KCLK_SRC	BIT(3)
#घोषणा OMAP_RTC_OSC_OSC32K_GZ_DISABLE	BIT(4)

/* OMAP_RTC_IRQWAKEEN bit fields: */
#घोषणा OMAP_RTC_IRQWAKEEN_ALARM_WAKEEN	BIT(1)

/* OMAP_RTC_PMIC bit fields: */
#घोषणा OMAP_RTC_PMIC_POWER_EN_EN	BIT(16)
#घोषणा OMAP_RTC_PMIC_EXT_WKUP_EN(x)	BIT(x)
#घोषणा OMAP_RTC_PMIC_EXT_WKUP_POL(x)	BIT(4 + x)

/* OMAP_RTC_KICKER values */
#घोषणा	KICK0_VALUE			0x83e70b13
#घोषणा	KICK1_VALUE			0x95a4f1e0

काष्ठा omap_rtc;

काष्ठा omap_rtc_device_type अणु
	bool has_32kclk_en;
	bool has_irqwakeen;
	bool has_pmic_mode;
	bool has_घातer_up_reset;
	व्योम (*lock)(काष्ठा omap_rtc *rtc);
	व्योम (*unlock)(काष्ठा omap_rtc *rtc);
पूर्ण;

काष्ठा omap_rtc अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	पूर्णांक irq_alarm;
	पूर्णांक irq_समयr;
	u8 पूर्णांकerrupts_reg;
	bool is_pmic_controller;
	bool has_ext_clk;
	bool is_suspending;
	स्थिर काष्ठा omap_rtc_device_type *type;
	काष्ठा pinctrl_dev *pctldev;
पूर्ण;

अटल अंतरभूत u8 rtc_पढ़ो(काष्ठा omap_rtc *rtc, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb(rtc->base + reg);
पूर्ण

अटल अंतरभूत u32 rtc_पढ़ोl(काष्ठा omap_rtc *rtc, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(rtc->base + reg);
पूर्ण

अटल अंतरभूत व्योम rtc_ग_लिखो(काष्ठा omap_rtc *rtc, अचिन्हित पूर्णांक reg, u8 val)
अणु
	ग_लिखोb(val, rtc->base + reg);
पूर्ण

अटल अंतरभूत व्योम rtc_ग_लिखोl(काष्ठा omap_rtc *rtc, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, rtc->base + reg);
पूर्ण

अटल व्योम am3352_rtc_unlock(काष्ठा omap_rtc *rtc)
अणु
	rtc_ग_लिखोl(rtc, OMAP_RTC_KICK0_REG, KICK0_VALUE);
	rtc_ग_लिखोl(rtc, OMAP_RTC_KICK1_REG, KICK1_VALUE);
पूर्ण

अटल व्योम am3352_rtc_lock(काष्ठा omap_rtc *rtc)
अणु
	rtc_ग_लिखोl(rtc, OMAP_RTC_KICK0_REG, 0);
	rtc_ग_लिखोl(rtc, OMAP_RTC_KICK1_REG, 0);
पूर्ण

अटल व्योम शेष_rtc_unlock(काष्ठा omap_rtc *rtc)
अणु
पूर्ण

अटल व्योम शेष_rtc_lock(काष्ठा omap_rtc *rtc)
अणु
पूर्ण

/*
 * We rely on the rtc framework to handle locking (rtc->ops_lock),
 * so the only other requirement is that रेजिस्टर accesses which
 * require BUSY to be clear are made with IRQs locally disabled
 */
अटल व्योम rtc_रुको_not_busy(काष्ठा omap_rtc *rtc)
अणु
	पूर्णांक count;
	u8 status;

	/* BUSY may stay active क्रम 1/32768 second (~30 usec) */
	क्रम (count = 0; count < 50; count++) अणु
		status = rtc_पढ़ो(rtc, OMAP_RTC_STATUS_REG);
		अगर (!(status & OMAP_RTC_STATUS_BUSY))
			अवरोध;
		udelay(1);
	पूर्ण
	/* now we have ~15 usec to पढ़ो/ग_लिखो various रेजिस्टरs */
पूर्ण

अटल irqवापस_t rtc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_rtc	*rtc = dev_id;
	अचिन्हित दीर्घ events = 0;
	u8 irq_data;

	irq_data = rtc_पढ़ो(rtc, OMAP_RTC_STATUS_REG);

	/* alarm irq? */
	अगर (irq_data & OMAP_RTC_STATUS_ALARM) अणु
		rtc->type->unlock(rtc);
		rtc_ग_लिखो(rtc, OMAP_RTC_STATUS_REG, OMAP_RTC_STATUS_ALARM);
		rtc->type->lock(rtc);
		events |= RTC_IRQF | RTC_AF;
	पूर्ण

	/* 1/sec periodic/update irq? */
	अगर (irq_data & OMAP_RTC_STATUS_1S_EVENT)
		events |= RTC_IRQF | RTC_UF;

	rtc_update_irq(rtc->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक omap_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);
	u8 reg, irqwake_reg = 0;

	local_irq_disable();
	rtc_रुको_not_busy(rtc);
	reg = rtc_पढ़ो(rtc, OMAP_RTC_INTERRUPTS_REG);
	अगर (rtc->type->has_irqwakeen)
		irqwake_reg = rtc_पढ़ो(rtc, OMAP_RTC_IRQWAKEEN);

	अगर (enabled) अणु
		reg |= OMAP_RTC_INTERRUPTS_IT_ALARM;
		irqwake_reg |= OMAP_RTC_IRQWAKEEN_ALARM_WAKEEN;
	पूर्ण अन्यथा अणु
		reg &= ~OMAP_RTC_INTERRUPTS_IT_ALARM;
		irqwake_reg &= ~OMAP_RTC_IRQWAKEEN_ALARM_WAKEEN;
	पूर्ण
	rtc_रुको_not_busy(rtc);
	rtc->type->unlock(rtc);
	rtc_ग_लिखो(rtc, OMAP_RTC_INTERRUPTS_REG, reg);
	अगर (rtc->type->has_irqwakeen)
		rtc_ग_लिखो(rtc, OMAP_RTC_IRQWAKEEN, irqwake_reg);
	rtc->type->lock(rtc);
	local_irq_enable();

	वापस 0;
पूर्ण

/* this hardware करोesn't support "don't care" alarm fields */
अटल व्योम पंचांग2bcd(काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bin2bcd(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bin2bcd(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bin2bcd(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bin2bcd(पंचांग->पंचांग_mday);

	पंचांग->पंचांग_mon = bin2bcd(पंचांग->पंचांग_mon + 1);
	पंचांग->पंचांग_year = bin2bcd(पंचांग->पंचांग_year - 100);
पूर्ण

अटल व्योम bcd2पंचांग(काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon) - 1;
	/* epoch == 1900 */
	पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year) + 100;
पूर्ण

अटल व्योम omap_rtc_पढ़ो_समय_raw(काष्ठा omap_rtc *rtc, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = rtc_पढ़ो(rtc, OMAP_RTC_SECONDS_REG);
	पंचांग->पंचांग_min = rtc_पढ़ो(rtc, OMAP_RTC_MINUTES_REG);
	पंचांग->पंचांग_hour = rtc_पढ़ो(rtc, OMAP_RTC_HOURS_REG);
	पंचांग->पंचांग_mday = rtc_पढ़ो(rtc, OMAP_RTC_DAYS_REG);
	पंचांग->पंचांग_mon = rtc_पढ़ो(rtc, OMAP_RTC_MONTHS_REG);
	पंचांग->पंचांग_year = rtc_पढ़ो(rtc, OMAP_RTC_YEARS_REG);
पूर्ण

अटल पूर्णांक omap_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);

	/* we करोn't report wday/yday/isdst ... */
	local_irq_disable();
	rtc_रुको_not_busy(rtc);
	omap_rtc_पढ़ो_समय_raw(rtc, पंचांग);
	local_irq_enable();

	bcd2पंचांग(पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);

	पंचांग2bcd(पंचांग);

	local_irq_disable();
	rtc_रुको_not_busy(rtc);

	rtc->type->unlock(rtc);
	rtc_ग_लिखो(rtc, OMAP_RTC_YEARS_REG, पंचांग->पंचांग_year);
	rtc_ग_लिखो(rtc, OMAP_RTC_MONTHS_REG, पंचांग->पंचांग_mon);
	rtc_ग_लिखो(rtc, OMAP_RTC_DAYS_REG, पंचांग->पंचांग_mday);
	rtc_ग_लिखो(rtc, OMAP_RTC_HOURS_REG, पंचांग->पंचांग_hour);
	rtc_ग_लिखो(rtc, OMAP_RTC_MINUTES_REG, पंचांग->पंचांग_min);
	rtc_ग_लिखो(rtc, OMAP_RTC_SECONDS_REG, पंचांग->पंचांग_sec);
	rtc->type->lock(rtc);

	local_irq_enable();

	वापस 0;
पूर्ण

अटल पूर्णांक omap_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);
	u8 पूर्णांकerrupts;

	local_irq_disable();
	rtc_रुको_not_busy(rtc);

	alm->समय.पंचांग_sec = rtc_पढ़ो(rtc, OMAP_RTC_ALARM_SECONDS_REG);
	alm->समय.पंचांग_min = rtc_पढ़ो(rtc, OMAP_RTC_ALARM_MINUTES_REG);
	alm->समय.पंचांग_hour = rtc_पढ़ो(rtc, OMAP_RTC_ALARM_HOURS_REG);
	alm->समय.पंचांग_mday = rtc_पढ़ो(rtc, OMAP_RTC_ALARM_DAYS_REG);
	alm->समय.पंचांग_mon = rtc_पढ़ो(rtc, OMAP_RTC_ALARM_MONTHS_REG);
	alm->समय.पंचांग_year = rtc_पढ़ो(rtc, OMAP_RTC_ALARM_YEARS_REG);

	local_irq_enable();

	bcd2पंचांग(&alm->समय);

	पूर्णांकerrupts = rtc_पढ़ो(rtc, OMAP_RTC_INTERRUPTS_REG);
	alm->enabled = !!(पूर्णांकerrupts & OMAP_RTC_INTERRUPTS_IT_ALARM);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);
	u8 reg, irqwake_reg = 0;

	पंचांग2bcd(&alm->समय);

	local_irq_disable();
	rtc_रुको_not_busy(rtc);

	rtc->type->unlock(rtc);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM_YEARS_REG, alm->समय.पंचांग_year);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM_MONTHS_REG, alm->समय.पंचांग_mon);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM_DAYS_REG, alm->समय.पंचांग_mday);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM_HOURS_REG, alm->समय.पंचांग_hour);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM_MINUTES_REG, alm->समय.पंचांग_min);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM_SECONDS_REG, alm->समय.पंचांग_sec);

	reg = rtc_पढ़ो(rtc, OMAP_RTC_INTERRUPTS_REG);
	अगर (rtc->type->has_irqwakeen)
		irqwake_reg = rtc_पढ़ो(rtc, OMAP_RTC_IRQWAKEEN);

	अगर (alm->enabled) अणु
		reg |= OMAP_RTC_INTERRUPTS_IT_ALARM;
		irqwake_reg |= OMAP_RTC_IRQWAKEEN_ALARM_WAKEEN;
	पूर्ण अन्यथा अणु
		reg &= ~OMAP_RTC_INTERRUPTS_IT_ALARM;
		irqwake_reg &= ~OMAP_RTC_IRQWAKEEN_ALARM_WAKEEN;
	पूर्ण
	rtc_ग_लिखो(rtc, OMAP_RTC_INTERRUPTS_REG, reg);
	अगर (rtc->type->has_irqwakeen)
		rtc_ग_लिखो(rtc, OMAP_RTC_IRQWAKEEN, irqwake_reg);
	rtc->type->lock(rtc);

	local_irq_enable();

	वापस 0;
पूर्ण

अटल काष्ठा omap_rtc *omap_rtc_घातer_off_rtc;

/**
 * omap_rtc_घातer_off_program: Set the pmic घातer off sequence. The RTC
 * generates pmic_pwr_enable control, which can be used to control an बाह्यal
 * PMIC.
 */
पूर्णांक omap_rtc_घातer_off_program(काष्ठा device *dev)
अणु
	काष्ठा omap_rtc *rtc = omap_rtc_घातer_off_rtc;
	काष्ठा rtc_समय पंचांग;
	अचिन्हित दीर्घ now;
	पूर्णांक seconds;
	u32 val;

	rtc->type->unlock(rtc);
	/* enable pmic_घातer_en control */
	val = rtc_पढ़ोl(rtc, OMAP_RTC_PMIC_REG);
	rtc_ग_लिखोl(rtc, OMAP_RTC_PMIC_REG, val | OMAP_RTC_PMIC_POWER_EN_EN);

again:
	/* Clear any existing ALARM2 event */
	rtc_ग_लिखोl(rtc, OMAP_RTC_STATUS_REG, OMAP_RTC_STATUS_ALARM2);

	/* set alarm one second from now */
	omap_rtc_पढ़ो_समय_raw(rtc, &पंचांग);
	seconds = पंचांग.पंचांग_sec;
	bcd2पंचांग(&पंचांग);
	now = rtc_पंचांग_to_समय64(&पंचांग);
	rtc_समय64_to_पंचांग(now + 1, &पंचांग);

	पंचांग2bcd(&पंचांग);

	rtc_रुको_not_busy(rtc);

	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM2_SECONDS_REG, पंचांग.पंचांग_sec);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM2_MINUTES_REG, पंचांग.पंचांग_min);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM2_HOURS_REG, पंचांग.पंचांग_hour);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM2_DAYS_REG, पंचांग.पंचांग_mday);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM2_MONTHS_REG, पंचांग.पंचांग_mon);
	rtc_ग_लिखो(rtc, OMAP_RTC_ALARM2_YEARS_REG, पंचांग.पंचांग_year);

	/*
	 * enable ALARM2 पूर्णांकerrupt
	 *
	 * NOTE: this fails on AM3352 अगर rtc_ग_लिखो (ग_लिखोb) is used
	 */
	val = rtc_पढ़ो(rtc, OMAP_RTC_INTERRUPTS_REG);
	rtc_ग_लिखोl(rtc, OMAP_RTC_INTERRUPTS_REG,
			val | OMAP_RTC_INTERRUPTS_IT_ALARM2);

	/* Retry in हाल roll over happened beक्रमe alarm was armed. */
	अगर (rtc_पढ़ो(rtc, OMAP_RTC_SECONDS_REG) != seconds) अणु
		val = rtc_पढ़ो(rtc, OMAP_RTC_STATUS_REG);
		अगर (!(val & OMAP_RTC_STATUS_ALARM2))
			जाओ again;
	पूर्ण

	rtc->type->lock(rtc);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(omap_rtc_घातer_off_program);

/*
 * omap_rtc_घातeroff: RTC-controlled घातer off
 *
 * The RTC can be used to control an बाह्यal PMIC via the pmic_घातer_en pin,
 * which can be configured to transition to OFF on ALARM2 events.
 *
 * Notes:
 * The one-second alarm offset is the लघुest offset possible as the alarm
 * रेजिस्टरs must be set beक्रमe the next समयr update and the offset
 * calculation is too heavy क्रम everything to be करोne within a single access
 * period (~15 us).
 *
 * Called with local पूर्णांकerrupts disabled.
 */
अटल व्योम omap_rtc_घातer_off(व्योम)
अणु
	काष्ठा rtc_device *rtc = omap_rtc_घातer_off_rtc->rtc;
	u32 val;

	omap_rtc_घातer_off_program(rtc->dev.parent);

	/* Set PMIC घातer enable and EXT_WAKEUP in हाल PB घातer on is used */
	omap_rtc_घातer_off_rtc->type->unlock(omap_rtc_घातer_off_rtc);
	val = rtc_पढ़ोl(omap_rtc_घातer_off_rtc, OMAP_RTC_PMIC_REG);
	val |= OMAP_RTC_PMIC_POWER_EN_EN | OMAP_RTC_PMIC_EXT_WKUP_POL(0) |
			OMAP_RTC_PMIC_EXT_WKUP_EN(0);
	rtc_ग_लिखोl(omap_rtc_घातer_off_rtc, OMAP_RTC_PMIC_REG, val);
	omap_rtc_घातer_off_rtc->type->lock(omap_rtc_घातer_off_rtc);

	/*
	 * Wait क्रम alarm to trigger (within one second) and बाह्यal PMIC to
	 * घातer off the प्रणाली. Add a 500 ms margin क्रम बाह्यal latencies
	 * (e.g. debounce circuits).
	 */
	mdelay(1500);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops omap_rtc_ops = अणु
	.पढ़ो_समय	= omap_rtc_पढ़ो_समय,
	.set_समय	= omap_rtc_set_समय,
	.पढ़ो_alarm	= omap_rtc_पढ़ो_alarm,
	.set_alarm	= omap_rtc_set_alarm,
	.alarm_irq_enable = omap_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा omap_rtc_device_type omap_rtc_शेष_type = अणु
	.has_घातer_up_reset = true,
	.lock		= शेष_rtc_lock,
	.unlock		= शेष_rtc_unlock,
पूर्ण;

अटल स्थिर काष्ठा omap_rtc_device_type omap_rtc_am3352_type = अणु
	.has_32kclk_en	= true,
	.has_irqwakeen	= true,
	.has_pmic_mode	= true,
	.lock		= am3352_rtc_lock,
	.unlock		= am3352_rtc_unlock,
पूर्ण;

अटल स्थिर काष्ठा omap_rtc_device_type omap_rtc_da830_type = अणु
	.lock		= am3352_rtc_lock,
	.unlock		= am3352_rtc_unlock,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id omap_rtc_id_table[] = अणु
	अणु
		.name	= "omap_rtc",
		.driver_data = (kernel_uदीर्घ_t)&omap_rtc_शेष_type,
	पूर्ण, अणु
		.name	= "am3352-rtc",
		.driver_data = (kernel_uदीर्घ_t)&omap_rtc_am3352_type,
	पूर्ण, अणु
		.name	= "da830-rtc",
		.driver_data = (kernel_uदीर्घ_t)&omap_rtc_da830_type,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, omap_rtc_id_table);

अटल स्थिर काष्ठा of_device_id omap_rtc_of_match[] = अणु
	अणु
		.compatible	= "ti,am3352-rtc",
		.data		= &omap_rtc_am3352_type,
	पूर्ण, अणु
		.compatible	= "ti,da830-rtc",
		.data		= &omap_rtc_da830_type,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_rtc_of_match);

अटल स्थिर काष्ठा pinctrl_pin_desc rtc_pins_desc[] = अणु
	PINCTRL_PIN(0, "ext_wakeup0"),
	PINCTRL_PIN(1, "ext_wakeup1"),
	PINCTRL_PIN(2, "ext_wakeup2"),
	PINCTRL_PIN(3, "ext_wakeup3"),
पूर्ण;

अटल पूर्णांक rtc_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *rtc_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक group)
अणु
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rtc_pinctrl_ops = अणु
	.get_groups_count = rtc_pinctrl_get_groups_count,
	.get_group_name = rtc_pinctrl_get_group_name,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

#घोषणा PIN_CONFIG_ACTIVE_HIGH		(PIN_CONFIG_END + 1)

अटल स्थिर काष्ठा pinconf_generic_params rtc_params[] = अणु
	अणु"ti,active-high", PIN_CONFIG_ACTIVE_HIGH, 0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item rtc_conf_items[ARRAY_SIZE(rtc_params)] = अणु
	PCONFDUMP(PIN_CONFIG_ACTIVE_HIGH, "input active high", शून्य, false),
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक rtc_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा omap_rtc *rtc = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	u32 val;
	u16 arg = 0;

	val = rtc_पढ़ोl(rtc, OMAP_RTC_PMIC_REG);

	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (!(val & OMAP_RTC_PMIC_EXT_WKUP_EN(pin)))
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_ACTIVE_HIGH:
		अगर (val & OMAP_RTC_PMIC_EXT_WKUP_POL(pin))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक rtc_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
			अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा omap_rtc *rtc = pinctrl_dev_get_drvdata(pctldev);
	u32 val;
	अचिन्हित पूर्णांक param;
	u32 param_val;
	पूर्णांक i;

	val = rtc_पढ़ोl(rtc, OMAP_RTC_PMIC_REG);

	/* active low by शेष */
	val |= OMAP_RTC_PMIC_EXT_WKUP_POL(pin);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_INPUT_ENABLE:
			अगर (param_val)
				val |= OMAP_RTC_PMIC_EXT_WKUP_EN(pin);
			अन्यथा
				val &= ~OMAP_RTC_PMIC_EXT_WKUP_EN(pin);
			अवरोध;
		हाल PIN_CONFIG_ACTIVE_HIGH:
			val &= ~OMAP_RTC_PMIC_EXT_WKUP_POL(pin);
			अवरोध;
		शेष:
			dev_err(&rtc->rtc->dev, "Property %u not supported\n",
				param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	rtc->type->unlock(rtc);
	rtc_ग_लिखोl(rtc, OMAP_RTC_PMIC_REG, val);
	rtc->type->lock(rtc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops rtc_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = rtc_pinconf_get,
	.pin_config_set = rtc_pinconf_set,
पूर्ण;

अटल काष्ठा pinctrl_desc rtc_pinctrl_desc = अणु
	.pins = rtc_pins_desc,
	.npins = ARRAY_SIZE(rtc_pins_desc),
	.pctlops = &rtc_pinctrl_ops,
	.confops = &rtc_pinconf_ops,
	.custom_params = rtc_params,
	.num_custom_params = ARRAY_SIZE(rtc_params),
#अगर_घोषित CONFIG_DEBUG_FS
	.custom_conf_items = rtc_conf_items,
#पूर्ण_अगर
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक omap_rtc_scratch_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *_val,
				 माप_प्रकार bytes)
अणु
	काष्ठा omap_rtc	*rtc = priv;
	u32 *val = _val;
	पूर्णांक i;

	क्रम (i = 0; i < bytes / 4; i++)
		val[i] = rtc_पढ़ोl(rtc,
				   OMAP_RTC_SCRATCH0_REG + offset + (i * 4));

	वापस 0;
पूर्ण

अटल पूर्णांक omap_rtc_scratch_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *_val,
				  माप_प्रकार bytes)
अणु
	काष्ठा omap_rtc	*rtc = priv;
	u32 *val = _val;
	पूर्णांक i;

	rtc->type->unlock(rtc);
	क्रम (i = 0; i < bytes / 4; i++)
		rtc_ग_लिखोl(rtc,
			   OMAP_RTC_SCRATCH0_REG + offset + (i * 4), val[i]);
	rtc->type->lock(rtc);

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config omap_rtc_nvmem_config = अणु
	.name = "omap_rtc_scratch",
	.word_size = 4,
	.stride = 4,
	.size = OMAP_RTC_KICK0_REG - OMAP_RTC_SCRATCH0_REG,
	.reg_पढ़ो = omap_rtc_scratch_पढ़ो,
	.reg_ग_लिखो = omap_rtc_scratch_ग_लिखो,
पूर्ण;

अटल पूर्णांक omap_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_rtc	*rtc;
	u8 reg, mask, new_ctrl;
	स्थिर काष्ठा platक्रमm_device_id *id_entry;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	of_id = of_match_device(omap_rtc_of_match, &pdev->dev);
	अगर (of_id) अणु
		rtc->type = of_id->data;
		rtc->is_pmic_controller = rtc->type->has_pmic_mode &&
			of_device_is_प्रणाली_घातer_controller(pdev->dev.of_node);
	पूर्ण अन्यथा अणु
		id_entry = platक्रमm_get_device_id(pdev);
		rtc->type = (व्योम *)id_entry->driver_data;
	पूर्ण

	rtc->irq_समयr = platक्रमm_get_irq(pdev, 0);
	अगर (rtc->irq_समयr <= 0)
		वापस -ENOENT;

	rtc->irq_alarm = platक्रमm_get_irq(pdev, 1);
	अगर (rtc->irq_alarm <= 0)
		वापस -ENOENT;

	rtc->clk = devm_clk_get(&pdev->dev, "ext-clk");
	अगर (!IS_ERR(rtc->clk))
		rtc->has_ext_clk = true;
	अन्यथा
		rtc->clk = devm_clk_get(&pdev->dev, "int-clk");

	अगर (!IS_ERR(rtc->clk))
		clk_prepare_enable(rtc->clk);

	rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->base)) अणु
		clk_disable_unprepare(rtc->clk);
		वापस PTR_ERR(rtc->base);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc);

	/* Enable the घड़ी/module so that we can access the रेजिस्टरs */
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	rtc->type->unlock(rtc);

	/*
	 * disable पूर्णांकerrupts
	 *
	 * NOTE: ALARM2 is not cleared on AM3352 अगर rtc_ग_लिखो (ग_लिखोb) is used
	 */
	rtc_ग_लिखोl(rtc, OMAP_RTC_INTERRUPTS_REG, 0);

	/* enable RTC functional घड़ी */
	अगर (rtc->type->has_32kclk_en) अणु
		reg = rtc_पढ़ो(rtc, OMAP_RTC_OSC_REG);
		rtc_ग_लिखो(rtc, OMAP_RTC_OSC_REG, reg | OMAP_RTC_OSC_32KCLK_EN);
	पूर्ण

	/* clear old status */
	reg = rtc_पढ़ो(rtc, OMAP_RTC_STATUS_REG);

	mask = OMAP_RTC_STATUS_ALARM;

	अगर (rtc->type->has_pmic_mode)
		mask |= OMAP_RTC_STATUS_ALARM2;

	अगर (rtc->type->has_घातer_up_reset) अणु
		mask |= OMAP_RTC_STATUS_POWER_UP;
		अगर (reg & OMAP_RTC_STATUS_POWER_UP)
			dev_info(&pdev->dev, "RTC power up reset detected\n");
	पूर्ण

	अगर (reg & mask)
		rtc_ग_लिखो(rtc, OMAP_RTC_STATUS_REG, reg & mask);

	/* On boards with split घातer, RTC_ON_NOFF won't reset the RTC */
	reg = rtc_पढ़ो(rtc, OMAP_RTC_CTRL_REG);
	अगर (reg & OMAP_RTC_CTRL_STOP)
		dev_info(&pdev->dev, "already running\n");

	/* क्रमce to 24 hour mode */
	new_ctrl = reg & (OMAP_RTC_CTRL_SPLIT | OMAP_RTC_CTRL_AUTO_COMP);
	new_ctrl |= OMAP_RTC_CTRL_STOP;

	/*
	 * BOARD-SPECIFIC CUSTOMIZATION CAN GO HERE:
	 *
	 *  - Device wake-up capability setting should come through chip
	 *    init logic. OMAP1 boards should initialize the "wakeup capable"
	 *    flag in the platक्रमm device अगर the board is wired right क्रम
	 *    being woken up by RTC alarm. For OMAP-L138, this capability
	 *    is built पूर्णांकo the SoC by the "Deep Sleep" capability.
	 *
	 *  - Boards wired so RTC_ON_nOFF is used as the reset संकेत,
	 *    rather than nPWRON_RESET, should क्रमcibly enable split
	 *    घातer mode.  (Some chip errata report that RTC_CTRL_SPLIT
	 *    is ग_लिखो-only, and always पढ़ोs as zero...)
	 */

	अगर (new_ctrl & OMAP_RTC_CTRL_SPLIT)
		dev_info(&pdev->dev, "split power mode\n");

	अगर (reg != new_ctrl)
		rtc_ग_लिखो(rtc, OMAP_RTC_CTRL_REG, new_ctrl);

	/*
	 * If we have the बाह्यal घड़ी then चयन to it so we can keep
	 * ticking across suspend.
	 */
	अगर (rtc->has_ext_clk) अणु
		reg = rtc_पढ़ो(rtc, OMAP_RTC_OSC_REG);
		reg &= ~OMAP_RTC_OSC_OSC32K_GZ_DISABLE;
		reg |= OMAP_RTC_OSC_32KCLK_EN | OMAP_RTC_OSC_SEL_32KCLK_SRC;
		rtc_ग_लिखो(rtc, OMAP_RTC_OSC_REG, reg);
	पूर्ण

	rtc->type->lock(rtc);

	device_init_wakeup(&pdev->dev, true);

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc)) अणु
		ret = PTR_ERR(rtc->rtc);
		जाओ err;
	पूर्ण

	rtc->rtc->ops = &omap_rtc_ops;
	rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->rtc->range_max = RTC_TIMESTAMP_END_2099;
	omap_rtc_nvmem_config.priv = rtc;

	/* handle periodic and alarm irqs */
	ret = devm_request_irq(&pdev->dev, rtc->irq_समयr, rtc_irq, 0,
			dev_name(&rtc->rtc->dev), rtc);
	अगर (ret)
		जाओ err;

	अगर (rtc->irq_समयr != rtc->irq_alarm) अणु
		ret = devm_request_irq(&pdev->dev, rtc->irq_alarm, rtc_irq, 0,
				dev_name(&rtc->rtc->dev), rtc);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Support ext_wakeup pinconf */
	rtc_pinctrl_desc.name = dev_name(&pdev->dev);

	rtc->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &rtc_pinctrl_desc, rtc);
	अगर (IS_ERR(rtc->pctldev)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		ret = PTR_ERR(rtc->pctldev);
		जाओ err;
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret)
		जाओ err;

	devm_rtc_nvmem_रेजिस्टर(rtc->rtc, &omap_rtc_nvmem_config);

	अगर (rtc->is_pmic_controller) अणु
		अगर (!pm_घातer_off) अणु
			omap_rtc_घातer_off_rtc = rtc;
			pm_घातer_off = omap_rtc_घातer_off;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	clk_disable_unprepare(rtc->clk);
	device_init_wakeup(&pdev->dev, false);
	rtc->type->lock(rtc);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_rtc *rtc = platक्रमm_get_drvdata(pdev);
	u8 reg;

	अगर (pm_घातer_off == omap_rtc_घातer_off &&
			omap_rtc_घातer_off_rtc == rtc) अणु
		pm_घातer_off = शून्य;
		omap_rtc_घातer_off_rtc = शून्य;
	पूर्ण

	device_init_wakeup(&pdev->dev, 0);

	अगर (!IS_ERR(rtc->clk))
		clk_disable_unprepare(rtc->clk);

	rtc->type->unlock(rtc);
	/* leave rtc running, but disable irqs */
	rtc_ग_लिखो(rtc, OMAP_RTC_INTERRUPTS_REG, 0);

	अगर (rtc->has_ext_clk) अणु
		reg = rtc_पढ़ो(rtc, OMAP_RTC_OSC_REG);
		reg &= ~OMAP_RTC_OSC_SEL_32KCLK_SRC;
		rtc_ग_लिखो(rtc, OMAP_RTC_OSC_REG, reg);
	पूर्ण

	rtc->type->lock(rtc);

	/* Disable the घड़ी/module */
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);

	rtc->पूर्णांकerrupts_reg = rtc_पढ़ो(rtc, OMAP_RTC_INTERRUPTS_REG);

	rtc->type->unlock(rtc);
	/*
	 * FIXME: the RTC alarm is not currently acting as a wakeup event
	 * source on some platक्रमms, and in fact this enable() call is just
	 * saving a flag that's never used...
	 */
	अगर (device_may_wakeup(dev))
		enable_irq_wake(rtc->irq_alarm);
	अन्यथा
		rtc_ग_लिखो(rtc, OMAP_RTC_INTERRUPTS_REG, 0);
	rtc->type->lock(rtc);

	rtc->is_suspending = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);

	rtc->type->unlock(rtc);
	अगर (device_may_wakeup(dev))
		disable_irq_wake(rtc->irq_alarm);
	अन्यथा
		rtc_ग_लिखो(rtc, OMAP_RTC_INTERRUPTS_REG, rtc->पूर्णांकerrupts_reg);
	rtc->type->lock(rtc);

	rtc->is_suspending = false;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rtc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_rtc *rtc = dev_get_drvdata(dev);

	अगर (rtc->is_suspending && !rtc->has_ext_clk)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_rtc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap_rtc_suspend, omap_rtc_resume)
	SET_RUNTIME_PM_OPS(omap_rtc_runसमय_suspend, शून्य, शून्य)
पूर्ण;

अटल व्योम omap_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_rtc *rtc = platक्रमm_get_drvdata(pdev);
	u8 mask;

	/*
	 * Keep the ALARM पूर्णांकerrupt enabled to allow the प्रणाली to घातer up on
	 * alarm events.
	 */
	rtc->type->unlock(rtc);
	mask = rtc_पढ़ो(rtc, OMAP_RTC_INTERRUPTS_REG);
	mask &= OMAP_RTC_INTERRUPTS_IT_ALARM;
	rtc_ग_लिखो(rtc, OMAP_RTC_INTERRUPTS_REG, mask);
	rtc->type->lock(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver omap_rtc_driver = अणु
	.probe		= omap_rtc_probe,
	.हटाओ		= omap_rtc_हटाओ,
	.shutकरोwn	= omap_rtc_shutकरोwn,
	.driver		= अणु
		.name	= "omap_rtc",
		.pm	= &omap_rtc_pm_ops,
		.of_match_table = omap_rtc_of_match,
	पूर्ण,
	.id_table	= omap_rtc_id_table,
पूर्ण;

module_platक्रमm_driver(omap_rtc_driver);

MODULE_ALIAS("platform:omap_rtc");
MODULE_AUTHOR("George G. Davis (and others)");
MODULE_LICENSE("GPL");
