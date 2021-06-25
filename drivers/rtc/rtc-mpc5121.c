<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Real-समय घड़ी driver क्रम MPC5121
 *
 * Copyright 2007, Domen Puncer <करोmen.puncer@telargo.com>
 * Copyright 2008, Freescale Semiconductor, Inc. All rights reserved.
 * Copyright 2011, Dmitry Eremin-Solenikov
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

काष्ठा mpc5121_rtc_regs अणु
	u8 set_समय;		/* RTC + 0x00 */
	u8 hour_set;		/* RTC + 0x01 */
	u8 minute_set;		/* RTC + 0x02 */
	u8 second_set;		/* RTC + 0x03 */

	u8 set_date;		/* RTC + 0x04 */
	u8 month_set;		/* RTC + 0x05 */
	u8 weekday_set;		/* RTC + 0x06 */
	u8 date_set;		/* RTC + 0x07 */

	u8 ग_लिखो_sw;		/* RTC + 0x08 */
	u8 sw_set;		/* RTC + 0x09 */
	u16 year_set;		/* RTC + 0x0a */

	u8 alm_enable;		/* RTC + 0x0c */
	u8 alm_hour_set;	/* RTC + 0x0d */
	u8 alm_min_set;		/* RTC + 0x0e */
	u8 पूर्णांक_enable;		/* RTC + 0x0f */

	u8 reserved1;
	u8 hour;		/* RTC + 0x11 */
	u8 minute;		/* RTC + 0x12 */
	u8 second;		/* RTC + 0x13 */

	u8 month;		/* RTC + 0x14 */
	u8 wday_mday;		/* RTC + 0x15 */
	u16 year;		/* RTC + 0x16 */

	u8 पूर्णांक_alm;		/* RTC + 0x18 */
	u8 पूर्णांक_sw;		/* RTC + 0x19 */
	u8 alm_status;		/* RTC + 0x1a */
	u8 sw_minute;		/* RTC + 0x1b */

	u8 bus_error_1;		/* RTC + 0x1c */
	u8 पूर्णांक_day;		/* RTC + 0x1d */
	u8 पूर्णांक_min;		/* RTC + 0x1e */
	u8 पूर्णांक_sec;		/* RTC + 0x1f */

	/*
	 * target_समय:
	 *	पूर्णांकended to be used क्रम hibernation but hibernation
	 *	करोes not work on silicon rev 1.5 so use it क्रम non-अस्थिर
	 *	storage of offset between the actual_समय रेजिस्टर and linux
	 *	समय
	 */
	u32 target_समय;	/* RTC + 0x20 */
	/*
	 * actual_समय:
	 *	पढ़ोonly समय since VBAT_RTC was last connected
	 */
	u32 actual_समय;	/* RTC + 0x24 */
	u32 keep_alive;		/* RTC + 0x28 */
पूर्ण;

काष्ठा mpc5121_rtc_data अणु
	अचिन्हित irq;
	अचिन्हित irq_periodic;
	काष्ठा mpc5121_rtc_regs __iomem *regs;
	काष्ठा rtc_device *rtc;
	काष्ठा rtc_wkalrm wkalarm;
पूर्ण;

/*
 * Update second/minute/hour रेजिस्टरs.
 *
 * This is just so alarm will work.
 */
अटल व्योम mpc5121_rtc_update_smh(काष्ठा mpc5121_rtc_regs __iomem *regs,
				   काष्ठा rtc_समय *पंचांग)
अणु
	out_8(&regs->second_set, पंचांग->पंचांग_sec);
	out_8(&regs->minute_set, पंचांग->पंचांग_min);
	out_8(&regs->hour_set, पंचांग->पंचांग_hour);

	/* set समय sequence */
	out_8(&regs->set_समय, 0x1);
	out_8(&regs->set_समय, 0x3);
	out_8(&regs->set_समय, 0x1);
	out_8(&regs->set_समय, 0x0);
पूर्ण

अटल पूर्णांक mpc5121_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;
	अचिन्हित दीर्घ now;

	/*
	 * linux समय is actual_समय plus the offset saved in target_समय
	 */
	now = in_be32(&regs->actual_समय) + in_be32(&regs->target_समय);

	rtc_समय64_to_पंचांग(now, पंचांग);

	/*
	 * update second minute hour रेजिस्टरs
	 * so alarms will work
	 */
	mpc5121_rtc_update_smh(regs, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc5121_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;
	अचिन्हित दीर्घ now;

	/*
	 * The actual_समय रेजिस्टर is पढ़ो only so we ग_लिखो the offset
	 * between it and linux समय to the target_समय रेजिस्टर.
	 */
	now = rtc_पंचांग_to_समय64(पंचांग);
	out_be32(&regs->target_समय, now - in_be32(&regs->actual_समय));

	/*
	 * update second minute hour रेजिस्टरs
	 * so alarms will work
	 */
	mpc5121_rtc_update_smh(regs, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc5200_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;
	पूर्णांक पंचांगp;

	पंचांग->पंचांग_sec = in_8(&regs->second);
	पंचांग->पंचांग_min = in_8(&regs->minute);

	/* 12 hour क्रमmat? */
	अगर (in_8(&regs->hour) & 0x20)
		पंचांग->पंचांग_hour = (in_8(&regs->hour) >> 1) +
			(in_8(&regs->hour) & 1 ? 12 : 0);
	अन्यथा
		पंचांग->पंचांग_hour = in_8(&regs->hour);

	पंचांगp = in_8(&regs->wday_mday);
	पंचांग->पंचांग_mday = पंचांगp & 0x1f;
	पंचांग->पंचांग_mon = in_8(&regs->month) - 1;
	पंचांग->पंचांग_year = in_be16(&regs->year) - 1900;
	पंचांग->पंचांग_wday = (पंचांगp >> 5) % 7;
	पंचांग->पंचांग_yday = rtc_year_days(पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year);
	पंचांग->पंचांग_isdst = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mpc5200_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;

	mpc5121_rtc_update_smh(regs, पंचांग);

	/* date */
	out_8(&regs->month_set, पंचांग->पंचांग_mon + 1);
	out_8(&regs->weekday_set, पंचांग->पंचांग_wday ? पंचांग->पंचांग_wday : 7);
	out_8(&regs->date_set, पंचांग->पंचांग_mday);
	out_be16(&regs->year_set, पंचांग->पंचांग_year + 1900);

	/* set date sequence */
	out_8(&regs->set_date, 0x1);
	out_8(&regs->set_date, 0x3);
	out_8(&regs->set_date, 0x1);
	out_8(&regs->set_date, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc5121_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;

	*alarm = rtc->wkalarm;

	alarm->pending = in_8(&regs->alm_status);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc5121_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;

	/*
	 * the alarm has no seconds so deal with it
	 */
	अगर (alarm->समय.पंचांग_sec) अणु
		alarm->समय.पंचांग_sec = 0;
		alarm->समय.पंचांग_min++;
		अगर (alarm->समय.पंचांग_min >= 60) अणु
			alarm->समय.पंचांग_min = 0;
			alarm->समय.पंचांग_hour++;
			अगर (alarm->समय.पंचांग_hour >= 24)
				alarm->समय.पंचांग_hour = 0;
		पूर्ण
	पूर्ण

	alarm->समय.पंचांग_mday = -1;
	alarm->समय.पंचांग_mon = -1;
	alarm->समय.पंचांग_year = -1;

	out_8(&regs->alm_min_set, alarm->समय.पंचांग_min);
	out_8(&regs->alm_hour_set, alarm->समय.पंचांग_hour);

	out_8(&regs->alm_enable, alarm->enabled);

	rtc->wkalarm = *alarm;
	वापस 0;
पूर्ण

अटल irqवापस_t mpc5121_rtc_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata((काष्ठा device *)dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;

	अगर (in_8(&regs->पूर्णांक_alm)) अणु
		/* acknowledge and clear status */
		out_8(&regs->पूर्णांक_alm, 1);
		out_8(&regs->alm_status, 1);

		rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t mpc5121_rtc_handler_upd(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata((काष्ठा device *)dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;

	अगर (in_8(&regs->पूर्णांक_sec) && (in_8(&regs->पूर्णांक_enable) & 0x1)) अणु
		/* acknowledge */
		out_8(&regs->पूर्णांक_sec, 1);

		rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_UF);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक mpc5121_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा mpc5121_rtc_data *rtc = dev_get_drvdata(dev);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;
	पूर्णांक val;

	अगर (enabled)
		val = 1;
	अन्यथा
		val = 0;

	out_8(&regs->alm_enable, val);
	rtc->wkalarm.enabled = val;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mpc5121_rtc_ops = अणु
	.पढ़ो_समय = mpc5121_rtc_पढ़ो_समय,
	.set_समय = mpc5121_rtc_set_समय,
	.पढ़ो_alarm = mpc5121_rtc_पढ़ो_alarm,
	.set_alarm = mpc5121_rtc_set_alarm,
	.alarm_irq_enable = mpc5121_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा rtc_class_ops mpc5200_rtc_ops = अणु
	.पढ़ो_समय = mpc5200_rtc_पढ़ो_समय,
	.set_समय = mpc5200_rtc_set_समय,
	.पढ़ो_alarm = mpc5121_rtc_पढ़ो_alarm,
	.set_alarm = mpc5121_rtc_set_alarm,
	.alarm_irq_enable = mpc5121_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक mpc5121_rtc_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mpc5121_rtc_data *rtc;
	पूर्णांक err = 0;

	rtc = devm_kzalloc(&op->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->regs = devm_platक्रमm_ioremap_resource(op, 0);
	अगर (IS_ERR(rtc->regs)) अणु
		dev_err(&op->dev, "%s: couldn't map io space\n", __func__);
		वापस PTR_ERR(rtc->regs);
	पूर्ण

	device_init_wakeup(&op->dev, 1);

	platक्रमm_set_drvdata(op, rtc);

	rtc->irq = irq_of_parse_and_map(op->dev.of_node, 1);
	err = devm_request_irq(&op->dev, rtc->irq, mpc5121_rtc_handler, 0,
			       "mpc5121-rtc", &op->dev);
	अगर (err) अणु
		dev_err(&op->dev, "%s: could not request irq: %i\n",
							__func__, rtc->irq);
		जाओ out_dispose;
	पूर्ण

	rtc->irq_periodic = irq_of_parse_and_map(op->dev.of_node, 0);
	err = devm_request_irq(&op->dev, rtc->irq_periodic,
			       mpc5121_rtc_handler_upd, 0, "mpc5121-rtc_upd",
			       &op->dev);
	अगर (err) अणु
		dev_err(&op->dev, "%s: could not request irq: %i\n",
						__func__, rtc->irq_periodic);
		जाओ out_dispose2;
	पूर्ण

	rtc->rtc = devm_rtc_allocate_device(&op->dev);
	अगर (IS_ERR(rtc->rtc)) अणु
		err = PTR_ERR(rtc->rtc);
		जाओ out_dispose2;
	पूर्ण

	rtc->rtc->ops = &mpc5200_rtc_ops;
	rtc->rtc->uie_unsupported = 1;
	rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_0000;
	rtc->rtc->range_max = 65733206399ULL; /* 4052-12-31 23:59:59 */

	अगर (of_device_is_compatible(op->dev.of_node, "fsl,mpc5121-rtc")) अणु
		u32 ka;
		ka = in_be32(&rtc->regs->keep_alive);
		अगर (ka & 0x02) अणु
			dev_warn(&op->dev,
				"mpc5121-rtc: Battery or oscillator failure!\n");
			out_be32(&rtc->regs->keep_alive, ka);
		पूर्ण
		rtc->rtc->ops = &mpc5121_rtc_ops;
		/*
		 * This is a limitation of the driver that abuses the target
		 * समय रेजिस्टर, the actual maximum year क्रम the mpc5121 is
		 * also 4052.
		 */
		rtc->rtc->range_min = 0;
		rtc->rtc->range_max = U32_MAX;
	पूर्ण

	err = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (err)
		जाओ out_dispose2;

	वापस 0;

out_dispose2:
	irq_dispose_mapping(rtc->irq_periodic);
out_dispose:
	irq_dispose_mapping(rtc->irq);

	वापस err;
पूर्ण

अटल पूर्णांक mpc5121_rtc_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mpc5121_rtc_data *rtc = platक्रमm_get_drvdata(op);
	काष्ठा mpc5121_rtc_regs __iomem *regs = rtc->regs;

	/* disable पूर्णांकerrupt, so there are no nasty surprises */
	out_8(&regs->alm_enable, 0);
	out_8(&regs->पूर्णांक_enable, in_8(&regs->पूर्णांक_enable) & ~0x1);

	irq_dispose_mapping(rtc->irq);
	irq_dispose_mapping(rtc->irq_periodic);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mpc5121_rtc_match[] = अणु
	अणु .compatible = "fsl,mpc5121-rtc", पूर्ण,
	अणु .compatible = "fsl,mpc5200-rtc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc5121_rtc_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mpc5121_rtc_driver = अणु
	.driver = अणु
		.name = "mpc5121-rtc",
		.of_match_table = of_match_ptr(mpc5121_rtc_match),
	पूर्ण,
	.probe = mpc5121_rtc_probe,
	.हटाओ = mpc5121_rtc_हटाओ,
पूर्ण;

module_platक्रमm_driver(mpc5121_rtc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Rigby <jcrigby@gmail.com>");
