<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/rtc/rtc-rc5t619.c
 *
 * Real समय घड़ी driver क्रम RICOH RC5T619 घातer management chip.
 *
 * Copyright (C) 2019 Andreas Kemnade
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/rn5t618.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqकरोमुख्य.h>

काष्ठा rc5t619_rtc अणु
	पूर्णांक			irq;
	काष्ठा rtc_device	*rtc;
	काष्ठा rn5t618 *rn5t618;
पूर्ण;

#घोषणा CTRL1_ALARM_ENABLED 0x40
#घोषणा CTRL1_24HR 0x20
#घोषणा CTRL1_PERIODIC_MASK 0xf

#घोषणा CTRL2_PON 0x10
#घोषणा CTRL2_ALARM_STATUS 0x80
#घोषणा CTRL2_CTFG 0x4
#घोषणा CTRL2_CTC 0x1

#घोषणा MONTH_CENTFLAG 0x80
#घोषणा HOUR_PMFLAG 0x20
#घोषणा MDAY_DAL_EXT 0x80

अटल uपूर्णांक8_t rtc5t619_12hour_bcd2bin(uपूर्णांक8_t hour)
अणु
	अगर (hour & HOUR_PMFLAG) अणु
		hour = bcd2bin(hour & ~HOUR_PMFLAG);
		वापस hour == 12 ? 12 : 12 + hour;
	पूर्ण

	hour = bcd2bin(hour);
	वापस hour == 12 ? 0 : hour;
पूर्ण

अटल uपूर्णांक8_t rtc5t619_12hour_bin2bcd(uपूर्णांक8_t hour)
अणु
	अगर (!hour)
		वापस 0x12;

	अगर (hour < 12)
		वापस bin2bcd(hour);

	अगर (hour == 12)
		वापस 0x12 | HOUR_PMFLAG;

	वापस bin2bcd(hour - 12) | HOUR_PMFLAG;
पूर्ण

अटल पूर्णांक rc5t619_rtc_periodic_disable(काष्ठा device *dev)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक err;

	/* disable function */
	err = regmap_update_bits(rtc->rn5t618->regmap,
				 RN5T618_RTC_CTRL1, CTRL1_PERIODIC_MASK, 0);
	अगर (err < 0)
		वापस err;

	/* clear alarm flag and CTFG */
	err = regmap_update_bits(rtc->rn5t618->regmap, RN5T618_RTC_CTRL2,
				 CTRL2_ALARM_STATUS | CTRL2_CTFG | CTRL2_CTC,
				 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/* things to be करोne once after घातer on */
अटल पूर्णांक rc5t619_rtc_pon_setup(काष्ठा device *dev)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक err;
	अचिन्हित पूर्णांक reg_data;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL2, &reg_data);
	अगर (err < 0)
		वापस err;

	/* clear VDET PON */
	reg_data &= ~(CTRL2_PON | CTRL2_CTC | 0x4a);	/* 0101-1011 */
	reg_data |= 0x20;	/* 0010-0000 */
	err = regmap_ग_लिखो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL2, reg_data);
	अगर (err < 0)
		वापस err;

	/* clearing RTC Adjust रेजिस्टर */
	err = regmap_ग_लिखो(rtc->rn5t618->regmap, RN5T618_RTC_ADJUST, 0);
	अगर (err)
		वापस err;

	वापस regmap_update_bits(rtc->rn5t618->regmap,
					RN5T618_RTC_CTRL1,
					CTRL1_24HR, CTRL1_24HR);
पूर्ण

अटल पूर्णांक rc5t619_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);
	u8 buff[7];
	पूर्णांक err;
	पूर्णांक cent_flag;
	अचिन्हित पूर्णांक ctrl1;
	अचिन्हित पूर्णांक ctrl2;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL2, &ctrl2);
	अगर (err < 0)
		वापस err;

	अगर (ctrl2 & CTRL2_PON)
		वापस -EINVAL;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL1, &ctrl1);
	अगर (err < 0)
		वापस err;

	err = regmap_bulk_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_SECONDS,
			       buff, माप(buff));
	अगर (err < 0)
		वापस err;

	अगर (buff[5] & MONTH_CENTFLAG)
		cent_flag = 1;
	अन्यथा
		cent_flag = 0;

	पंचांग->पंचांग_sec  = bcd2bin(buff[0]);
	पंचांग->पंचांग_min  = bcd2bin(buff[1]);

	अगर (ctrl1 & CTRL1_24HR)
		पंचांग->पंचांग_hour = bcd2bin(buff[2]);
	अन्यथा
		पंचांग->पंचांग_hour = rtc5t619_12hour_bcd2bin(buff[2]);

	पंचांग->पंचांग_wday = bcd2bin(buff[3]);
	पंचांग->पंचांग_mday = bcd2bin(buff[4]);
	पंचांग->पंचांग_mon  = bcd2bin(buff[5] & 0x1f) - 1; /* back to प्रणाली 0-11 */
	पंचांग->पंचांग_year = bcd2bin(buff[6]) + 100 * cent_flag;

	वापस 0;
पूर्ण

अटल पूर्णांक rc5t619_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);
	u8 buff[7];
	पूर्णांक err;
	पूर्णांक cent_flag;
	अचिन्हित पूर्णांक ctrl1;
	अचिन्हित पूर्णांक ctrl2;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL2, &ctrl2);
	अगर (err < 0)
		वापस err;

	अगर (ctrl2 & CTRL2_PON)
		rc5t619_rtc_pon_setup(dev);

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL1, &ctrl1);
	अगर (err < 0)
		वापस err;

	अगर (पंचांग->पंचांग_year >= 100)
		cent_flag = 1;
	अन्यथा
		cent_flag = 0;

	buff[0] = bin2bcd(पंचांग->पंचांग_sec);
	buff[1] = bin2bcd(पंचांग->पंचांग_min);

	अगर (ctrl1 & CTRL1_24HR)
		buff[2] = bin2bcd(पंचांग->पंचांग_hour);
	अन्यथा
		buff[2] = rtc5t619_12hour_bin2bcd(पंचांग->पंचांग_hour);

	buff[3] = bin2bcd(पंचांग->पंचांग_wday);
	buff[4] = bin2bcd(पंचांग->पंचांग_mday);
	buff[5] = bin2bcd(पंचांग->पंचांग_mon + 1);	/* प्रणाली set 0-11 */
	buff[6] = bin2bcd(पंचांग->पंचांग_year - cent_flag * 100);

	अगर (cent_flag)
		buff[5] |= MONTH_CENTFLAG;

	err = regmap_bulk_ग_लिखो(rtc->rn5t618->regmap, RN5T618_RTC_SECONDS,
				buff, माप(buff));
	अगर (err < 0) अणु
		dev_err(dev, "failed to program new time: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* 0-disable, 1-enable */
अटल पूर्णांक rc5t619_rtc_alarm_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);

	वापस regmap_update_bits(rtc->rn5t618->regmap,
			RN5T618_RTC_CTRL1,
			CTRL1_ALARM_ENABLED,
			enabled ? CTRL1_ALARM_ENABLED : 0);
पूर्ण

अटल पूर्णांक rc5t619_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);
	u8 buff[6];
	अचिन्हित पूर्णांक buff_cent;
	पूर्णांक err;
	पूर्णांक cent_flag;
	अचिन्हित पूर्णांक ctrl1;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL1, &ctrl1);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_MONTH, &buff_cent);
	अगर (err < 0) अणु
		dev_err(dev, "failed to read time: %d\n", err);
		वापस err;
	पूर्ण

	अगर (buff_cent & MONTH_CENTFLAG)
		cent_flag = 1;
	अन्यथा
		cent_flag = 0;

	err = regmap_bulk_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_ALARM_Y_SEC,
			       buff, माप(buff));
	अगर (err)
		वापस err;

	buff[3] = buff[3] & 0x3f;

	alrm->समय.पंचांग_sec  = bcd2bin(buff[0]);
	alrm->समय.पंचांग_min  = bcd2bin(buff[1]);

	अगर (ctrl1 & CTRL1_24HR)
		alrm->समय.पंचांग_hour = bcd2bin(buff[2]);
	अन्यथा
		alrm->समय.पंचांग_hour = rtc5t619_12hour_bcd2bin(buff[2]);

	alrm->समय.पंचांग_mday = bcd2bin(buff[3]);
	alrm->समय.पंचांग_mon  = bcd2bin(buff[4]) - 1;
	alrm->समय.पंचांग_year = bcd2bin(buff[5]) + 100 * cent_flag;
	alrm->enabled = !!(ctrl1 & CTRL1_ALARM_ENABLED);
	dev_dbg(dev, "read alarm: %ptR\n", &alrm->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक rc5t619_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);
	u8 buff[6];
	पूर्णांक err;
	पूर्णांक cent_flag;
	अचिन्हित पूर्णांक ctrl1;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL1, &ctrl1);
	अगर (err)
		वापस err;

	err = rc5t619_rtc_alarm_enable(dev, 0);
	अगर (err < 0)
		वापस err;

	अगर (rtc->irq == -1)
		वापस -EINVAL;

	अगर (alrm->enabled == 0)
		वापस 0;

	अगर (alrm->समय.पंचांग_year >= 100)
		cent_flag = 1;
	अन्यथा
		cent_flag = 0;

	alrm->समय.पंचांग_mon += 1;
	buff[0] = bin2bcd(alrm->समय.पंचांग_sec);
	buff[1] = bin2bcd(alrm->समय.पंचांग_min);

	अगर (ctrl1 & CTRL1_24HR)
		buff[2] = bin2bcd(alrm->समय.पंचांग_hour);
	अन्यथा
		buff[2] = rtc5t619_12hour_bin2bcd(alrm->समय.पंचांग_hour);

	buff[3] = bin2bcd(alrm->समय.पंचांग_mday);
	buff[4] = bin2bcd(alrm->समय.पंचांग_mon);
	buff[5] = bin2bcd(alrm->समय.पंचांग_year - 100 * cent_flag);
	buff[3] |= MDAY_DAL_EXT;

	err = regmap_bulk_ग_लिखो(rtc->rn5t618->regmap, RN5T618_RTC_ALARM_Y_SEC,
				buff, माप(buff));
	अगर (err < 0)
		वापस err;

	वापस rc5t619_rtc_alarm_enable(dev, alrm->enabled);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rc5t619_rtc_ops = अणु
	.पढ़ो_समय	= rc5t619_rtc_पढ़ो_समय,
	.set_समय	= rc5t619_rtc_set_समय,
	.set_alarm	= rc5t619_rtc_set_alarm,
	.पढ़ो_alarm	= rc5t619_rtc_पढ़ो_alarm,
	.alarm_irq_enable = rc5t619_rtc_alarm_enable,
पूर्ण;

अटल पूर्णांक rc5t619_rtc_alarm_flag_clr(काष्ठा device *dev)
अणु
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);

	/* clear alarm-D status bits.*/
	वापस regmap_update_bits(rtc->rn5t618->regmap,
				RN5T618_RTC_CTRL2,
				CTRL2_ALARM_STATUS | CTRL2_CTC, 0);
पूर्ण

अटल irqवापस_t rc5t619_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा rc5t619_rtc *rtc = dev_get_drvdata(dev);

	rc5t619_rtc_alarm_flag_clr(dev);

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rc5t619_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rn5t618 *rn5t618 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा rc5t619_rtc *rtc;
	अचिन्हित पूर्णांक ctrl2;
	पूर्णांक err;

	rtc = devm_kzalloc(dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->rn5t618 = rn5t618;

	dev_set_drvdata(dev, rtc);
	rtc->irq = -1;

	अगर (rn5t618->irq_data)
		rtc->irq = regmap_irq_get_virq(rn5t618->irq_data,
					       RN5T618_IRQ_RTC);

	अगर (rtc->irq  < 0)
		rtc->irq = -1;

	err = regmap_पढ़ो(rtc->rn5t618->regmap, RN5T618_RTC_CTRL2, &ctrl2);
	अगर (err < 0)
		वापस err;

	/* disable rtc periodic function */
	err = rc5t619_rtc_periodic_disable(&pdev->dev);
	अगर (err)
		वापस err;

	अगर (ctrl2 & CTRL2_PON) अणु
		err = rc5t619_rtc_alarm_flag_clr(&pdev->dev);
		अगर (err)
			वापस err;
	पूर्ण

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc)) अणु
		err = PTR_ERR(rtc->rtc);
		dev_err(dev, "RTC device register: err %d\n", err);
		वापस err;
	पूर्ण

	rtc->rtc->ops = &rc5t619_rtc_ops;
	rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_1900;
	rtc->rtc->range_max = RTC_TIMESTAMP_END_2099;

	/* set पूर्णांकerrupt and enable it */
	अगर (rtc->irq != -1) अणु
		err = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
						rc5t619_rtc_irq,
						IRQF_ONESHOT,
						"rtc-rc5t619",
						&pdev->dev);
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "request IRQ:%d fail\n", rtc->irq);
			rtc->irq = -1;

			err = rc5t619_rtc_alarm_enable(&pdev->dev, 0);
			अगर (err)
				वापस err;

		पूर्ण अन्यथा अणु
			/* enable wake */
			device_init_wakeup(&pdev->dev, 1);
			enable_irq_wake(rtc->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* प्रणाली करोn't want to using alarm पूर्णांकerrupt, so बंद it */
		err = rc5t619_rtc_alarm_enable(&pdev->dev, 0);
		अगर (err)
			वापस err;

		dev_warn(&pdev->dev, "rc5t619 interrupt is disabled\n");
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver rc5t619_rtc_driver = अणु
	.driver	= अणु
		.name	= "rc5t619-rtc",
	पूर्ण,
	.probe	= rc5t619_rtc_probe,
पूर्ण;

module_platक्रमm_driver(rc5t619_rtc_driver);
MODULE_ALIAS("platform:rc5t619-rtc");
MODULE_DESCRIPTION("RICOH RC5T619 RTC driver");
MODULE_LICENSE("GPL");
