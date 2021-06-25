<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rtc-twl.c -- TWL Real Time Clock पूर्णांकerface
 *
 * Copyright (C) 2007 MontaVista Software, Inc
 * Author: Alexandre Rusev <source@mvista.com>
 *
 * Based on original TI driver twl4030-rtc.c
 *   Copyright (C) 2006 Texas Instruments, Inc.
 *
 * Based on rtc-omap.c
 *   Copyright (C) 2003 MontaVista Software, Inc.
 *   Author: George G. Davis <gdavis@mvista.com> or <source@mvista.com>
 *   Copyright (C) 2006 David Brownell
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>

#समावेश <linux/mfd/twl.h>

क्रमागत twl_class अणु
	TWL_4030 = 0,
	TWL_6030,
पूर्ण;

/*
 * RTC block रेजिस्टर offsets (use TWL_MODULE_RTC)
 */
क्रमागत अणु
	REG_SECONDS_REG = 0,
	REG_MINUTES_REG,
	REG_HOURS_REG,
	REG_DAYS_REG,
	REG_MONTHS_REG,
	REG_YEARS_REG,
	REG_WEEKS_REG,

	REG_ALARM_SECONDS_REG,
	REG_ALARM_MINUTES_REG,
	REG_ALARM_HOURS_REG,
	REG_ALARM_DAYS_REG,
	REG_ALARM_MONTHS_REG,
	REG_ALARM_YEARS_REG,

	REG_RTC_CTRL_REG,
	REG_RTC_STATUS_REG,
	REG_RTC_INTERRUPTS_REG,

	REG_RTC_COMP_LSB_REG,
	REG_RTC_COMP_MSB_REG,
पूर्ण;
अटल स्थिर u8 twl4030_rtc_reg_map[] = अणु
	[REG_SECONDS_REG] = 0x00,
	[REG_MINUTES_REG] = 0x01,
	[REG_HOURS_REG] = 0x02,
	[REG_DAYS_REG] = 0x03,
	[REG_MONTHS_REG] = 0x04,
	[REG_YEARS_REG] = 0x05,
	[REG_WEEKS_REG] = 0x06,

	[REG_ALARM_SECONDS_REG] = 0x07,
	[REG_ALARM_MINUTES_REG] = 0x08,
	[REG_ALARM_HOURS_REG] = 0x09,
	[REG_ALARM_DAYS_REG] = 0x0A,
	[REG_ALARM_MONTHS_REG] = 0x0B,
	[REG_ALARM_YEARS_REG] = 0x0C,

	[REG_RTC_CTRL_REG] = 0x0D,
	[REG_RTC_STATUS_REG] = 0x0E,
	[REG_RTC_INTERRUPTS_REG] = 0x0F,

	[REG_RTC_COMP_LSB_REG] = 0x10,
	[REG_RTC_COMP_MSB_REG] = 0x11,
पूर्ण;
अटल स्थिर u8 twl6030_rtc_reg_map[] = अणु
	[REG_SECONDS_REG] = 0x00,
	[REG_MINUTES_REG] = 0x01,
	[REG_HOURS_REG] = 0x02,
	[REG_DAYS_REG] = 0x03,
	[REG_MONTHS_REG] = 0x04,
	[REG_YEARS_REG] = 0x05,
	[REG_WEEKS_REG] = 0x06,

	[REG_ALARM_SECONDS_REG] = 0x08,
	[REG_ALARM_MINUTES_REG] = 0x09,
	[REG_ALARM_HOURS_REG] = 0x0A,
	[REG_ALARM_DAYS_REG] = 0x0B,
	[REG_ALARM_MONTHS_REG] = 0x0C,
	[REG_ALARM_YEARS_REG] = 0x0D,

	[REG_RTC_CTRL_REG] = 0x10,
	[REG_RTC_STATUS_REG] = 0x11,
	[REG_RTC_INTERRUPTS_REG] = 0x12,

	[REG_RTC_COMP_LSB_REG] = 0x13,
	[REG_RTC_COMP_MSB_REG] = 0x14,
पूर्ण;

/* RTC_CTRL_REG bitfields */
#घोषणा BIT_RTC_CTRL_REG_STOP_RTC_M              0x01
#घोषणा BIT_RTC_CTRL_REG_ROUND_30S_M             0x02
#घोषणा BIT_RTC_CTRL_REG_AUTO_COMP_M             0x04
#घोषणा BIT_RTC_CTRL_REG_MODE_12_24_M            0x08
#घोषणा BIT_RTC_CTRL_REG_TEST_MODE_M             0x10
#घोषणा BIT_RTC_CTRL_REG_SET_32_COUNTER_M        0x20
#घोषणा BIT_RTC_CTRL_REG_GET_TIME_M              0x40
#घोषणा BIT_RTC_CTRL_REG_RTC_V_OPT               0x80

/* RTC_STATUS_REG bitfields */
#घोषणा BIT_RTC_STATUS_REG_RUN_M                 0x02
#घोषणा BIT_RTC_STATUS_REG_1S_EVENT_M            0x04
#घोषणा BIT_RTC_STATUS_REG_1M_EVENT_M            0x08
#घोषणा BIT_RTC_STATUS_REG_1H_EVENT_M            0x10
#घोषणा BIT_RTC_STATUS_REG_1D_EVENT_M            0x20
#घोषणा BIT_RTC_STATUS_REG_ALARM_M               0x40
#घोषणा BIT_RTC_STATUS_REG_POWER_UP_M            0x80

/* RTC_INTERRUPTS_REG bitfields */
#घोषणा BIT_RTC_INTERRUPTS_REG_EVERY_M           0x03
#घोषणा BIT_RTC_INTERRUPTS_REG_IT_TIMER_M        0x04
#घोषणा BIT_RTC_INTERRUPTS_REG_IT_ALARM_M        0x08


/* REG_SECONDS_REG through REG_YEARS_REG is how many रेजिस्टरs? */
#घोषणा ALL_TIME_REGS		6

/*----------------------------------------------------------------------*/
काष्ठा twl_rtc अणु
	काष्ठा device *dev;
	काष्ठा rtc_device *rtc;
	u8 *reg_map;
	/*
	 * Cache the value क्रम समयr/alarm पूर्णांकerrupts रेजिस्टर; this is
	 * only changed by callers holding rtc ops lock (or resume).
	 */
	अचिन्हित अक्षर rtc_irq_bits;
	bool wake_enabled;
#अगर_घोषित CONFIG_PM_SLEEP
	अचिन्हित अक्षर irqstat;
#पूर्ण_अगर
	क्रमागत twl_class class;
पूर्ण;

/*
 * Supports 1 byte पढ़ो from TWL RTC रेजिस्टर.
 */
अटल पूर्णांक twl_rtc_पढ़ो_u8(काष्ठा twl_rtc *twl_rtc, u8 *data, u8 reg)
अणु
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_RTC, data, (twl_rtc->reg_map[reg]));
	अगर (ret < 0)
		pr_err("Could not read TWL register %X - error %d\n", reg, ret);
	वापस ret;
पूर्ण

/*
 * Supports 1 byte ग_लिखो to TWL RTC रेजिस्टरs.
 */
अटल पूर्णांक twl_rtc_ग_लिखो_u8(काष्ठा twl_rtc *twl_rtc, u8 data, u8 reg)
अणु
	पूर्णांक ret;

	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_RTC, data, (twl_rtc->reg_map[reg]));
	अगर (ret < 0)
		pr_err("Could not write TWL register %X - error %d\n",
		       reg, ret);
	वापस ret;
पूर्ण

/*
 * Enable 1/second update and/or alarm पूर्णांकerrupts.
 */
अटल पूर्णांक set_rtc_irq_bit(काष्ठा twl_rtc *twl_rtc, अचिन्हित अक्षर bit)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक ret;

	/* अगर the bit is set, वापस from here */
	अगर (twl_rtc->rtc_irq_bits & bit)
		वापस 0;

	val = twl_rtc->rtc_irq_bits | bit;
	val &= ~BIT_RTC_INTERRUPTS_REG_EVERY_M;
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, val, REG_RTC_INTERRUPTS_REG);
	अगर (ret == 0)
		twl_rtc->rtc_irq_bits = val;

	वापस ret;
पूर्ण

/*
 * Disable update and/or alarm पूर्णांकerrupts.
 */
अटल पूर्णांक mask_rtc_irq_bit(काष्ठा twl_rtc *twl_rtc, अचिन्हित अक्षर bit)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक ret;

	/* अगर the bit is clear, वापस from here */
	अगर (!(twl_rtc->rtc_irq_bits & bit))
		वापस 0;

	val = twl_rtc->rtc_irq_bits & ~bit;
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, val, REG_RTC_INTERRUPTS_REG);
	अगर (ret == 0)
		twl_rtc->rtc_irq_bits = val;

	वापस ret;
पूर्ण

अटल पूर्णांक twl_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित enabled)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	पूर्णांक ret;

	अगर (enabled) अणु
		ret = set_rtc_irq_bit(twl_rtc,
				      BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
		अगर (device_can_wakeup(dev) && !twl_rtc->wake_enabled) अणु
			enable_irq_wake(irq);
			twl_rtc->wake_enabled = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = mask_rtc_irq_bit(twl_rtc,
				       BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
		अगर (twl_rtc->wake_enabled) अणु
			disable_irq_wake(irq);
			twl_rtc->wake_enabled = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Gets current TWL RTC समय and date parameters.
 *
 * The RTC's समय/alarm representation is not what स_जमट(3) requires
 * Linux to use:
 *
 *  - Months are 1..12 vs Linux 0-11
 *  - Years are 0..99 vs Linux 1900..N (we assume 21st century)
 */
अटल पूर्णांक twl_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);
	अचिन्हित अक्षर rtc_data[ALL_TIME_REGS];
	पूर्णांक ret;
	u8 save_control;
	u8 rtc_control;

	ret = twl_rtc_पढ़ो_u8(twl_rtc, &save_control, REG_RTC_CTRL_REG);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: reading CTRL_REG, error %d\n", __func__, ret);
		वापस ret;
	पूर्ण
	/* क्रम twl6030/32 make sure BIT_RTC_CTRL_REG_GET_TIME_M is clear */
	अगर (twl_rtc->class == TWL_6030) अणु
		अगर (save_control & BIT_RTC_CTRL_REG_GET_TIME_M) अणु
			save_control &= ~BIT_RTC_CTRL_REG_GET_TIME_M;
			ret = twl_rtc_ग_लिखो_u8(twl_rtc, save_control,
					       REG_RTC_CTRL_REG);
			अगर (ret < 0) अणु
				dev_err(dev, "%s clr GET_TIME, error %d\n",
					__func__, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Copy RTC counting रेजिस्टरs to अटल रेजिस्टरs or latches */
	rtc_control = save_control | BIT_RTC_CTRL_REG_GET_TIME_M;

	/* क्रम twl6030/32 enable पढ़ो access to अटल shaकरोwed रेजिस्टरs */
	अगर (twl_rtc->class == TWL_6030)
		rtc_control |= BIT_RTC_CTRL_REG_RTC_V_OPT;

	ret = twl_rtc_ग_लिखो_u8(twl_rtc, rtc_control, REG_RTC_CTRL_REG);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: writing CTRL_REG, error %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = twl_i2c_पढ़ो(TWL_MODULE_RTC, rtc_data,
			(twl_rtc->reg_map[REG_SECONDS_REG]), ALL_TIME_REGS);

	अगर (ret < 0) अणु
		dev_err(dev, "%s: reading data, error %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	/* क्रम twl6030 restore original state of rtc control रेजिस्टर */
	अगर (twl_rtc->class == TWL_6030) अणु
		ret = twl_rtc_ग_लिखो_u8(twl_rtc, save_control, REG_RTC_CTRL_REG);
		अगर (ret < 0) अणु
			dev_err(dev, "%s: restore CTRL_REG, error %d\n",
				__func__, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rtc_data[0]);
	पंचांग->पंचांग_min = bcd2bin(rtc_data[1]);
	पंचांग->पंचांग_hour = bcd2bin(rtc_data[2]);
	पंचांग->पंचांग_mday = bcd2bin(rtc_data[3]);
	पंचांग->पंचांग_mon = bcd2bin(rtc_data[4]) - 1;
	पंचांग->पंचांग_year = bcd2bin(rtc_data[5]) + 100;

	वापस ret;
पूर्ण

अटल पूर्णांक twl_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);
	अचिन्हित अक्षर save_control;
	अचिन्हित अक्षर rtc_data[ALL_TIME_REGS];
	पूर्णांक ret;

	rtc_data[0] = bin2bcd(पंचांग->पंचांग_sec);
	rtc_data[1] = bin2bcd(पंचांग->पंचांग_min);
	rtc_data[2] = bin2bcd(पंचांग->पंचांग_hour);
	rtc_data[3] = bin2bcd(पंचांग->पंचांग_mday);
	rtc_data[4] = bin2bcd(पंचांग->पंचांग_mon + 1);
	rtc_data[5] = bin2bcd(पंचांग->पंचांग_year - 100);

	/* Stop RTC जबतक updating the TC रेजिस्टरs */
	ret = twl_rtc_पढ़ो_u8(twl_rtc, &save_control, REG_RTC_CTRL_REG);
	अगर (ret < 0)
		जाओ out;

	save_control &= ~BIT_RTC_CTRL_REG_STOP_RTC_M;
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, save_control, REG_RTC_CTRL_REG);
	अगर (ret < 0)
		जाओ out;

	/* update all the समय रेजिस्टरs in one shot */
	ret = twl_i2c_ग_लिखो(TWL_MODULE_RTC, rtc_data,
		(twl_rtc->reg_map[REG_SECONDS_REG]), ALL_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_set_time error %d\n", ret);
		जाओ out;
	पूर्ण

	/* Start back RTC */
	save_control |= BIT_RTC_CTRL_REG_STOP_RTC_M;
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, save_control, REG_RTC_CTRL_REG);

out:
	वापस ret;
पूर्ण

/*
 * Gets current TWL RTC alarm समय.
 */
अटल पूर्णांक twl_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);
	अचिन्हित अक्षर rtc_data[ALL_TIME_REGS];
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो(TWL_MODULE_RTC, rtc_data,
			twl_rtc->reg_map[REG_ALARM_SECONDS_REG], ALL_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_read_alarm error %d\n", ret);
		वापस ret;
	पूर्ण

	/* some of these fields may be wildcard/"match all" */
	alm->समय.पंचांग_sec = bcd2bin(rtc_data[0]);
	alm->समय.पंचांग_min = bcd2bin(rtc_data[1]);
	alm->समय.पंचांग_hour = bcd2bin(rtc_data[2]);
	alm->समय.पंचांग_mday = bcd2bin(rtc_data[3]);
	alm->समय.पंचांग_mon = bcd2bin(rtc_data[4]) - 1;
	alm->समय.पंचांग_year = bcd2bin(rtc_data[5]) + 100;

	/* report cached alarm enable state */
	अगर (twl_rtc->rtc_irq_bits & BIT_RTC_INTERRUPTS_REG_IT_ALARM_M)
		alm->enabled = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक twl_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);

	अचिन्हित अक्षर alarm_data[ALL_TIME_REGS];
	पूर्णांक ret;

	ret = twl_rtc_alarm_irq_enable(dev, 0);
	अगर (ret)
		जाओ out;

	alarm_data[0] = bin2bcd(alm->समय.पंचांग_sec);
	alarm_data[1] = bin2bcd(alm->समय.पंचांग_min);
	alarm_data[2] = bin2bcd(alm->समय.पंचांग_hour);
	alarm_data[3] = bin2bcd(alm->समय.पंचांग_mday);
	alarm_data[4] = bin2bcd(alm->समय.पंचांग_mon + 1);
	alarm_data[5] = bin2bcd(alm->समय.पंचांग_year - 100);

	/* update all the alarm रेजिस्टरs in one shot */
	ret = twl_i2c_ग_लिखो(TWL_MODULE_RTC, alarm_data,
			twl_rtc->reg_map[REG_ALARM_SECONDS_REG], ALL_TIME_REGS);
	अगर (ret) अणु
		dev_err(dev, "rtc_set_alarm error %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (alm->enabled)
		ret = twl_rtc_alarm_irq_enable(dev, 1);
out:
	वापस ret;
पूर्ण

अटल irqवापस_t twl_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा twl_rtc *twl_rtc = data;
	अचिन्हित दीर्घ events;
	पूर्णांक ret = IRQ_NONE;
	पूर्णांक res;
	u8 rd_reg;

	res = twl_rtc_पढ़ो_u8(twl_rtc, &rd_reg, REG_RTC_STATUS_REG);
	अगर (res)
		जाओ out;
	/*
	 * Figure out source of पूर्णांकerrupt: ALARM or TIMER in RTC_STATUS_REG.
	 * only one (ALARM or RTC) पूर्णांकerrupt source may be enabled
	 * at समय, we also could check our results
	 * by पढ़ोing RTS_INTERRUPTS_REGISTER[IT_TIMER,IT_ALARM]
	 */
	अगर (rd_reg & BIT_RTC_STATUS_REG_ALARM_M)
		events = RTC_IRQF | RTC_AF;
	अन्यथा
		events = RTC_IRQF | RTC_PF;

	res = twl_rtc_ग_लिखो_u8(twl_rtc, BIT_RTC_STATUS_REG_ALARM_M,
			       REG_RTC_STATUS_REG);
	अगर (res)
		जाओ out;

	अगर (twl_rtc->class == TWL_4030) अणु
		/* Clear on Read enabled. RTC_IT bit of TWL4030_INT_PWR_ISR1
		 * needs 2 पढ़ोs to clear the पूर्णांकerrupt. One पढ़ो is करोne in
		 * करो_twl_pwrirq(). Doing the second पढ़ो, to clear
		 * the bit.
		 *
		 * FIXME the reason PWR_ISR1 needs an extra पढ़ो is that
		 * RTC_IF retriggered until we cleared REG_ALARM_M above.
		 * But re-पढ़ोing like this is a bad hack; by करोing so we
		 * risk wrongly clearing status क्रम some other IRQ (losing
		 * the पूर्णांकerrupt).  Be smarter about handling RTC_UF ...
		 */
		res = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INT,
			&rd_reg, TWL4030_INT_PWR_ISR1);
		अगर (res)
			जाओ out;
	पूर्ण

	/* Notअगरy RTC core on event */
	rtc_update_irq(twl_rtc->rtc, 1, events);

	ret = IRQ_HANDLED;
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops twl_rtc_ops = अणु
	.पढ़ो_समय	= twl_rtc_पढ़ो_समय,
	.set_समय	= twl_rtc_set_समय,
	.पढ़ो_alarm	= twl_rtc_पढ़ो_alarm,
	.set_alarm	= twl_rtc_set_alarm,
	.alarm_irq_enable = twl_rtc_alarm_irq_enable,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल पूर्णांक twl_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_rtc *twl_rtc;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret = -EINVAL;
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	u8 rd_reg;

	अगर (!np) अणु
		dev_err(&pdev->dev, "no DT info\n");
		वापस -EINVAL;
	पूर्ण

	अगर (irq <= 0)
		वापस ret;

	twl_rtc = devm_kzalloc(&pdev->dev, माप(*twl_rtc), GFP_KERNEL);
	अगर (!twl_rtc)
		वापस -ENOMEM;

	अगर (twl_class_is_4030()) अणु
		twl_rtc->class = TWL_4030;
		twl_rtc->reg_map = (u8 *)twl4030_rtc_reg_map;
	पूर्ण अन्यथा अगर (twl_class_is_6030()) अणु
		twl_rtc->class = TWL_6030;
		twl_rtc->reg_map = (u8 *)twl6030_rtc_reg_map;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "TWL Class not supported.\n");
		वापस -EINVAL;
	पूर्ण

	ret = twl_rtc_पढ़ो_u8(twl_rtc, &rd_reg, REG_RTC_STATUS_REG);
	अगर (ret < 0)
		वापस ret;

	अगर (rd_reg & BIT_RTC_STATUS_REG_POWER_UP_M)
		dev_warn(&pdev->dev, "Power up reset detected.\n");

	अगर (rd_reg & BIT_RTC_STATUS_REG_ALARM_M)
		dev_warn(&pdev->dev, "Pending Alarm interrupt detected.\n");

	/* Clear RTC Power up reset and pending alarm पूर्णांकerrupts */
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, rd_reg, REG_RTC_STATUS_REG);
	अगर (ret < 0)
		वापस ret;

	अगर (twl_rtc->class == TWL_6030) अणु
		twl6030_पूर्णांकerrupt_unmask(TWL6030_RTC_INT_MASK,
			REG_INT_MSK_LINE_A);
		twl6030_पूर्णांकerrupt_unmask(TWL6030_RTC_INT_MASK,
			REG_INT_MSK_STS_A);
	पूर्ण

	dev_info(&pdev->dev, "Enabling TWL-RTC\n");
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, BIT_RTC_CTRL_REG_STOP_RTC_M,
			       REG_RTC_CTRL_REG);
	अगर (ret < 0)
		वापस ret;

	/* ensure पूर्णांकerrupts are disabled, bootloaders can be strange */
	ret = twl_rtc_ग_लिखो_u8(twl_rtc, 0, REG_RTC_INTERRUPTS_REG);
	अगर (ret < 0)
		dev_warn(&pdev->dev, "unable to disable interrupt\n");

	/* init cached IRQ enable bits */
	ret = twl_rtc_पढ़ो_u8(twl_rtc, &twl_rtc->rtc_irq_bits,
			      REG_RTC_INTERRUPTS_REG);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, twl_rtc);
	device_init_wakeup(&pdev->dev, 1);

	twl_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
					&twl_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(twl_rtc->rtc)) अणु
		dev_err(&pdev->dev, "can't register RTC device, err %ld\n",
			PTR_ERR(twl_rtc->rtc));
		वापस PTR_ERR(twl_rtc->rtc);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					twl_rtc_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(&twl_rtc->rtc->dev), twl_rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "IRQ is not free.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Disable all TWL RTC module पूर्णांकerrupts.
 * Sets status flag to मुक्त.
 */
अटल पूर्णांक twl_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_rtc *twl_rtc = platक्रमm_get_drvdata(pdev);

	/* leave rtc running, but disable irqs */
	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);
	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);
	अगर (twl_rtc->class == TWL_6030) अणु
		twl6030_पूर्णांकerrupt_mask(TWL6030_RTC_INT_MASK,
			REG_INT_MSK_LINE_A);
		twl6030_पूर्णांकerrupt_mask(TWL6030_RTC_INT_MASK,
			REG_INT_MSK_STS_A);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_rtc *twl_rtc = platक्रमm_get_drvdata(pdev);

	/* mask समयr पूर्णांकerrupts, but leave alarm पूर्णांकerrupts on to enable
	   घातer-on when alarm is triggered */
	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक twl_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);

	twl_rtc->irqstat = twl_rtc->rtc_irq_bits;

	mask_rtc_irq_bit(twl_rtc, BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);
	वापस 0;
पूर्ण

अटल पूर्णांक twl_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा twl_rtc *twl_rtc = dev_get_drvdata(dev);

	set_rtc_irq_bit(twl_rtc, twl_rtc->irqstat);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(twl_rtc_pm_ops, twl_rtc_suspend, twl_rtc_resume);

अटल स्थिर काष्ठा of_device_id twl_rtc_of_match[] = अणु
	अणु.compatible = "ti,twl4030-rtc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_rtc_of_match);

अटल काष्ठा platक्रमm_driver twl4030rtc_driver = अणु
	.probe		= twl_rtc_probe,
	.हटाओ		= twl_rtc_हटाओ,
	.shutकरोwn	= twl_rtc_shutकरोwn,
	.driver		= अणु
		.name		= "twl_rtc",
		.pm		= &twl_rtc_pm_ops,
		.of_match_table = twl_rtc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(twl4030rtc_driver);

MODULE_AUTHOR("Texas Instruments, MontaVista Software");
MODULE_LICENSE("GPL");
