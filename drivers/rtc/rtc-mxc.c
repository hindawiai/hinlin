<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2004-2008 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/पन.स>
#समावेश <linux/rtc.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#घोषणा RTC_INPUT_CLK_32768HZ	(0x00 << 5)
#घोषणा RTC_INPUT_CLK_32000HZ	(0x01 << 5)
#घोषणा RTC_INPUT_CLK_38400HZ	(0x02 << 5)

#घोषणा RTC_SW_BIT      (1 << 0)
#घोषणा RTC_ALM_BIT     (1 << 2)
#घोषणा RTC_1HZ_BIT     (1 << 4)
#घोषणा RTC_2HZ_BIT     (1 << 7)
#घोषणा RTC_SAM0_BIT    (1 << 8)
#घोषणा RTC_SAM1_BIT    (1 << 9)
#घोषणा RTC_SAM2_BIT    (1 << 10)
#घोषणा RTC_SAM3_BIT    (1 << 11)
#घोषणा RTC_SAM4_BIT    (1 << 12)
#घोषणा RTC_SAM5_BIT    (1 << 13)
#घोषणा RTC_SAM6_BIT    (1 << 14)
#घोषणा RTC_SAM7_BIT    (1 << 15)
#घोषणा PIT_ALL_ON      (RTC_2HZ_BIT | RTC_SAM0_BIT | RTC_SAM1_BIT | \
			 RTC_SAM2_BIT | RTC_SAM3_BIT | RTC_SAM4_BIT | \
			 RTC_SAM5_BIT | RTC_SAM6_BIT | RTC_SAM7_BIT)

#घोषणा RTC_ENABLE_BIT  (1 << 7)

#घोषणा MAX_PIE_NUM     9
#घोषणा MAX_PIE_FREQ    512

#घोषणा MXC_RTC_TIME	0
#घोषणा MXC_RTC_ALARM	1

#घोषणा RTC_HOURMIN	0x00	/*  32bit rtc hour/min counter reg */
#घोषणा RTC_SECOND	0x04	/*  32bit rtc seconds counter reg */
#घोषणा RTC_ALRM_HM	0x08	/*  32bit rtc alarm hour/min reg */
#घोषणा RTC_ALRM_SEC	0x0C	/*  32bit rtc alarm seconds reg */
#घोषणा RTC_RTCCTL	0x10	/*  32bit rtc control reg */
#घोषणा RTC_RTCISR	0x14	/*  32bit rtc पूर्णांकerrupt status reg */
#घोषणा RTC_RTCIENR	0x18	/*  32bit rtc पूर्णांकerrupt enable reg */
#घोषणा RTC_STPWCH	0x1C	/*  32bit rtc stopwatch min reg */
#घोषणा RTC_DAYR	0x20	/*  32bit rtc days counter reg */
#घोषणा RTC_DAYALARM	0x24	/*  32bit rtc day alarm reg */
#घोषणा RTC_TEST1	0x28	/*  32bit rtc test reg 1 */
#घोषणा RTC_TEST2	0x2C	/*  32bit rtc test reg 2 */
#घोषणा RTC_TEST3	0x30	/*  32bit rtc test reg 3 */

क्रमागत imx_rtc_type अणु
	IMX1_RTC,
	IMX21_RTC,
पूर्ण;

काष्ठा rtc_plat_data अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;
	पूर्णांक irq;
	काष्ठा clk *clk_ref;
	काष्ठा clk *clk_ipg;
	काष्ठा rtc_समय g_rtc_alarm;
	क्रमागत imx_rtc_type devtype;
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_rtc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx1-rtc", .data = (स्थिर व्योम *)IMX1_RTC पूर्ण,
	अणु .compatible = "fsl,imx21-rtc", .data = (स्थिर व्योम *)IMX21_RTC पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_rtc_dt_ids);

अटल अंतरभूत पूर्णांक is_imx1_rtc(काष्ठा rtc_plat_data *data)
अणु
	वापस data->devtype == IMX1_RTC;
पूर्ण

/*
 * This function is used to obtain the RTC समय or the alarm value in
 * second.
 */
अटल समय64_t get_alarm_or_समय(काष्ठा device *dev, पूर्णांक समय_alarm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32 day = 0, hr = 0, min = 0, sec = 0, hr_min = 0;

	चयन (समय_alarm) अणु
	हाल MXC_RTC_TIME:
		day = पढ़ोw(ioaddr + RTC_DAYR);
		hr_min = पढ़ोw(ioaddr + RTC_HOURMIN);
		sec = पढ़ोw(ioaddr + RTC_SECOND);
		अवरोध;
	हाल MXC_RTC_ALARM:
		day = पढ़ोw(ioaddr + RTC_DAYALARM);
		hr_min = पढ़ोw(ioaddr + RTC_ALRM_HM) & 0xffff;
		sec = पढ़ोw(ioaddr + RTC_ALRM_SEC);
		अवरोध;
	पूर्ण

	hr = hr_min >> 8;
	min = hr_min & 0xff;

	वापस ((((समय64_t)day * 24 + hr) * 60) + min) * 60 + sec;
पूर्ण

/*
 * This function sets the RTC alarm value or the समय value.
 */
अटल व्योम set_alarm_or_समय(काष्ठा device *dev, पूर्णांक समय_alarm, समय64_t समय)
अणु
	u32 tod, day, hr, min, sec, temp;
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;

	day = भाग_s64_rem(समय, 86400, &tod);

	/* समय is within a day now */
	hr = tod / 3600;
	tod -= hr * 3600;

	/* समय is within an hour now */
	min = tod / 60;
	sec = tod - min * 60;

	temp = (hr << 8) + min;

	चयन (समय_alarm) अणु
	हाल MXC_RTC_TIME:
		ग_लिखोw(day, ioaddr + RTC_DAYR);
		ग_लिखोw(sec, ioaddr + RTC_SECOND);
		ग_लिखोw(temp, ioaddr + RTC_HOURMIN);
		अवरोध;
	हाल MXC_RTC_ALARM:
		ग_लिखोw(day, ioaddr + RTC_DAYALARM);
		ग_लिखोw(sec, ioaddr + RTC_ALRM_SEC);
		ग_लिखोw(temp, ioaddr + RTC_ALRM_HM);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This function updates the RTC alarm रेजिस्टरs and then clears all the
 * पूर्णांकerrupt status bits.
 */
अटल व्योम rtc_update_alarm(काष्ठा device *dev, काष्ठा rtc_समय *alrm)
अणु
	समय64_t समय;
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;

	समय = rtc_पंचांग_to_समय64(alrm);

	/* clear all the पूर्णांकerrupt status bits */
	ग_लिखोw(पढ़ोw(ioaddr + RTC_RTCISR), ioaddr + RTC_RTCISR);
	set_alarm_or_समय(dev, MXC_RTC_ALARM, समय);
पूर्ण

अटल व्योम mxc_rtc_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक bit,
				अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32 reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->rtc->irq_lock, flags);
	reg = पढ़ोw(ioaddr + RTC_RTCIENR);

	अगर (enabled)
		reg |= bit;
	अन्यथा
		reg &= ~bit;

	ग_लिखोw(reg, ioaddr + RTC_RTCIENR);
	spin_unlock_irqrestore(&pdata->rtc->irq_lock, flags);
पूर्ण

/* This function is the RTC पूर्णांकerrupt service routine. */
अटल irqवापस_t mxc_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा rtc_plat_data *pdata = platक्रमm_get_drvdata(pdev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32 status;
	u32 events = 0;

	spin_lock(&pdata->rtc->irq_lock);
	status = पढ़ोw(ioaddr + RTC_RTCISR) & पढ़ोw(ioaddr + RTC_RTCIENR);
	/* clear पूर्णांकerrupt sources */
	ग_लिखोw(status, ioaddr + RTC_RTCISR);

	/* update irq data & counter */
	अगर (status & RTC_ALM_BIT) अणु
		events |= (RTC_AF | RTC_IRQF);
		/* RTC alarm should be one-shot */
		mxc_rtc_irq_enable(&pdev->dev, RTC_ALM_BIT, 0);
	पूर्ण

	अगर (status & PIT_ALL_ON)
		events |= (RTC_PF | RTC_IRQF);

	rtc_update_irq(pdata->rtc, 1, events);
	spin_unlock(&pdata->rtc->irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxc_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	mxc_rtc_irq_enable(dev, RTC_ALM_BIT, enabled);
	वापस 0;
पूर्ण

/*
 * This function पढ़ोs the current RTC समय पूर्णांकo पंचांग in Gregorian date.
 */
अटल पूर्णांक mxc_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t val;

	/* Aव्योम roll-over from पढ़ोing the dअगरferent रेजिस्टरs */
	करो अणु
		val = get_alarm_or_समय(dev, MXC_RTC_TIME);
	पूर्ण जबतक (val != get_alarm_or_समय(dev, MXC_RTC_TIME));

	rtc_समय64_to_पंचांग(val, पंचांग);

	वापस 0;
पूर्ण

/*
 * This function sets the पूर्णांकernal RTC समय based on पंचांग in Gregorian date.
 */
अटल पूर्णांक mxc_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t समय = rtc_पंचांग_to_समय64(पंचांग);

	/* Aव्योम roll-over from पढ़ोing the dअगरferent रेजिस्टरs */
	करो अणु
		set_alarm_or_समय(dev, MXC_RTC_TIME, समय);
	पूर्ण जबतक (समय != get_alarm_or_समय(dev, MXC_RTC_TIME));

	वापस 0;
पूर्ण

/*
 * This function पढ़ोs the current alarm value पूर्णांकo the passed in 'alrm'
 * argument. It updates the alrm's pending field value based on the whether
 * an alarm पूर्णांकerrupt occurs or not.
 */
अटल पूर्णांक mxc_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;

	rtc_समय64_to_पंचांग(get_alarm_or_समय(dev, MXC_RTC_ALARM), &alrm->समय);
	alrm->pending = ((पढ़ोw(ioaddr + RTC_RTCISR) & RTC_ALM_BIT)) ? 1 : 0;

	वापस 0;
पूर्ण

/*
 * This function sets the RTC alarm based on passed in alrm.
 */
अटल पूर्णांक mxc_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);

	rtc_update_alarm(dev, &alrm->समय);

	स_नकल(&pdata->g_rtc_alarm, &alrm->समय, माप(काष्ठा rtc_समय));
	mxc_rtc_irq_enable(dev, RTC_ALM_BIT, alrm->enabled);

	वापस 0;
पूर्ण

/* RTC layer */
अटल स्थिर काष्ठा rtc_class_ops mxc_rtc_ops = अणु
	.पढ़ो_समय		= mxc_rtc_पढ़ो_समय,
	.set_समय		= mxc_rtc_set_समय,
	.पढ़ो_alarm		= mxc_rtc_पढ़ो_alarm,
	.set_alarm		= mxc_rtc_set_alarm,
	.alarm_irq_enable	= mxc_rtc_alarm_irq_enable,
पूर्ण;

अटल व्योम mxc_rtc_action(व्योम *p)
अणु
	काष्ठा rtc_plat_data *pdata = p;

	clk_disable_unprepare(pdata->clk_ref);
	clk_disable_unprepare(pdata->clk_ipg);
पूर्ण

अटल पूर्णांक mxc_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा rtc_plat_data *pdata = शून्य;
	u32 reg;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->devtype = (क्रमागत imx_rtc_type)of_device_get_match_data(&pdev->dev);

	pdata->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->ioaddr))
		वापस PTR_ERR(pdata->ioaddr);

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	pdata->rtc = rtc;
	rtc->ops = &mxc_rtc_ops;
	अगर (is_imx1_rtc(pdata)) अणु
		काष्ठा rtc_समय पंचांग;

		/* 9bit days + hours minutes seconds */
		rtc->range_max = (1 << 9) * 86400 - 1;

		/*
		 * Set the start date as beginning of the current year. This can
		 * be overridden using device tree.
		 */
		rtc_समय64_to_पंचांग(kसमय_get_real_seconds(), &पंचांग);
		rtc->start_secs =  स_गढ़ो64(पंचांग.पंचांग_year, 1, 1, 0, 0, 0);
		rtc->set_start_समय = true;
	पूर्ण अन्यथा अणु
		/* 16bit days + hours minutes seconds */
		rtc->range_max = (1 << 16) * 86400ULL - 1;
	पूर्ण

	pdata->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(pdata->clk_ipg)) अणु
		dev_err(&pdev->dev, "unable to get ipg clock!\n");
		वापस PTR_ERR(pdata->clk_ipg);
	पूर्ण

	ret = clk_prepare_enable(pdata->clk_ipg);
	अगर (ret)
		वापस ret;

	pdata->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(pdata->clk_ref)) अणु
		clk_disable_unprepare(pdata->clk_ipg);
		dev_err(&pdev->dev, "unable to get ref clock!\n");
		वापस PTR_ERR(pdata->clk_ref);
	पूर्ण

	ret = clk_prepare_enable(pdata->clk_ref);
	अगर (ret) अणु
		clk_disable_unprepare(pdata->clk_ipg);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&pdev->dev, mxc_rtc_action, pdata);
	अगर (ret)
		वापस ret;

	rate = clk_get_rate(pdata->clk_ref);

	अगर (rate == 32768)
		reg = RTC_INPUT_CLK_32768HZ;
	अन्यथा अगर (rate == 32000)
		reg = RTC_INPUT_CLK_32000HZ;
	अन्यथा अगर (rate == 38400)
		reg = RTC_INPUT_CLK_38400HZ;
	अन्यथा अणु
		dev_err(&pdev->dev, "rtc clock is not valid (%lu)\n", rate);
		वापस -EINVAL;
	पूर्ण

	reg |= RTC_ENABLE_BIT;
	ग_लिखोw(reg, (pdata->ioaddr + RTC_RTCCTL));
	अगर (((पढ़ोw(pdata->ioaddr + RTC_RTCCTL)) & RTC_ENABLE_BIT) == 0) अणु
		dev_err(&pdev->dev, "hardware module can't be enabled!\n");
		वापस -EIO;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pdata);

	/* Configure and enable the RTC */
	pdata->irq = platक्रमm_get_irq(pdev, 0);

	अगर (pdata->irq >= 0 &&
	    devm_request_irq(&pdev->dev, pdata->irq, mxc_rtc_पूर्णांकerrupt,
			     IRQF_SHARED, pdev->name, pdev) < 0) अणु
		dev_warn(&pdev->dev, "interrupt not available.\n");
		pdata->irq = -1;
	पूर्ण

	अगर (pdata->irq >= 0) अणु
		device_init_wakeup(&pdev->dev, 1);
		ret = dev_pm_set_wake_irq(&pdev->dev, pdata->irq);
		अगर (ret)
			dev_err(&pdev->dev, "failed to enable irq wake\n");
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(rtc);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mxc_rtc_driver = अणु
	.driver = अणु
		   .name	= "mxc_rtc",
		   .of_match_table = imx_rtc_dt_ids,
	पूर्ण,
	.probe = mxc_rtc_probe,
पूर्ण;

module_platक्रमm_driver(mxc_rtc_driver)

MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>");
MODULE_DESCRIPTION("RTC driver for Freescale MXC");
MODULE_LICENSE("GPL");

