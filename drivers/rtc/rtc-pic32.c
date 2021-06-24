<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PIC32 RTC driver
 *
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2016 Microchip Technology Inc.  All rights reserved.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>

#समावेश <यंत्र/mach-pic32/pic32.h>

#घोषणा PIC32_RTCCON		0x00
#घोषणा PIC32_RTCCON_ON		BIT(15)
#घोषणा PIC32_RTCCON_SIDL	BIT(13)
#घोषणा PIC32_RTCCON_RTCCLKSEL	(3 << 9)
#घोषणा PIC32_RTCCON_RTCCLKON	BIT(6)
#घोषणा PIC32_RTCCON_RTCWREN	BIT(3)
#घोषणा PIC32_RTCCON_RTCSYNC	BIT(2)
#घोषणा PIC32_RTCCON_HALFSEC	BIT(1)
#घोषणा PIC32_RTCCON_RTCOE	BIT(0)

#घोषणा PIC32_RTCALRM		0x10
#घोषणा PIC32_RTCALRM_ALRMEN	BIT(15)
#घोषणा PIC32_RTCALRM_CHIME	BIT(14)
#घोषणा PIC32_RTCALRM_PIV	BIT(13)
#घोषणा PIC32_RTCALRM_ALARMSYNC	BIT(12)
#घोषणा PIC32_RTCALRM_AMASK	0x0F00
#घोषणा PIC32_RTCALRM_ARPT	0xFF

#घोषणा PIC32_RTCHOUR		0x23
#घोषणा PIC32_RTCMIN		0x22
#घोषणा PIC32_RTCSEC		0x21
#घोषणा PIC32_RTCYEAR		0x33
#घोषणा PIC32_RTCMON		0x32
#घोषणा PIC32_RTCDAY		0x31

#घोषणा PIC32_ALRMTIME		0x40
#घोषणा PIC32_ALRMDATE		0x50

#घोषणा PIC32_ALRMHOUR		0x43
#घोषणा PIC32_ALRMMIN		0x42
#घोषणा PIC32_ALRMSEC		0x41
#घोषणा PIC32_ALRMYEAR		0x53
#घोषणा PIC32_ALRMMON		0x52
#घोषणा PIC32_ALRMDAY		0x51

काष्ठा pic32_rtc_dev अणु
	काष्ठा rtc_device	*rtc;
	व्योम __iomem		*reg_base;
	काष्ठा clk		*clk;
	spinlock_t		alarm_lock;
	पूर्णांक			alarm_irq;
	bool			alarm_clk_enabled;
पूर्ण;

अटल व्योम pic32_rtc_alarm_clk_enable(काष्ठा pic32_rtc_dev *pdata,
				       bool enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->alarm_lock, flags);
	अगर (enable) अणु
		अगर (!pdata->alarm_clk_enabled) अणु
			clk_enable(pdata->clk);
			pdata->alarm_clk_enabled = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pdata->alarm_clk_enabled) अणु
			clk_disable(pdata->clk);
			pdata->alarm_clk_enabled = false;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pdata->alarm_lock, flags);
पूर्ण

अटल irqवापस_t pic32_rtc_alarmirq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा pic32_rtc_dev *pdata = (काष्ठा pic32_rtc_dev *)id;

	clk_enable(pdata->clk);
	rtc_update_irq(pdata->rtc, 1, RTC_AF | RTC_IRQF);
	clk_disable(pdata->clk);

	pic32_rtc_alarm_clk_enable(pdata, false);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pic32_rtc_setaie(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	व्योम __iomem *base = pdata->reg_base;

	clk_enable(pdata->clk);

	ग_लिखोl(PIC32_RTCALRM_ALRMEN,
	       base + (enabled ? PIC32_SET(PIC32_RTCALRM) :
		       PIC32_CLR(PIC32_RTCALRM)));

	clk_disable(pdata->clk);

	pic32_rtc_alarm_clk_enable(pdata, enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_setfreq(काष्ठा device *dev, पूर्णांक freq)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	व्योम __iomem *base = pdata->reg_base;

	clk_enable(pdata->clk);

	ग_लिखोl(PIC32_RTCALRM_AMASK, base + PIC32_CLR(PIC32_RTCALRM));
	ग_लिखोl(freq << 8, base + PIC32_SET(PIC32_RTCALRM));
	ग_लिखोl(PIC32_RTCALRM_CHIME, base + PIC32_SET(PIC32_RTCALRM));

	clk_disable(pdata->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	व्योम __iomem *base = pdata->reg_base;
	अचिन्हित पूर्णांक tries = 0;

	clk_enable(pdata->clk);

	करो अणु
		rtc_पंचांग->पंचांग_hour = पढ़ोb(base + PIC32_RTCHOUR);
		rtc_पंचांग->पंचांग_min = पढ़ोb(base + PIC32_RTCMIN);
		rtc_पंचांग->पंचांग_mon  = पढ़ोb(base + PIC32_RTCMON);
		rtc_पंचांग->पंचांग_mday = पढ़ोb(base + PIC32_RTCDAY);
		rtc_पंचांग->पंचांग_year = पढ़ोb(base + PIC32_RTCYEAR);
		rtc_पंचांग->पंचांग_sec  = पढ़ोb(base + PIC32_RTCSEC);

		/*
		 * The only way to work out whether the प्रणाली was mid-update
		 * when we पढ़ो it is to check the second counter, and अगर it
		 * is zero, then we re-try the entire पढ़ो.
		 */
		tries += 1;
	पूर्ण जबतक (rtc_पंचांग->पंचांग_sec == 0 && tries < 2);

	rtc_पंचांग->पंचांग_sec = bcd2bin(rtc_पंचांग->पंचांग_sec);
	rtc_पंचांग->पंचांग_min = bcd2bin(rtc_पंचांग->पंचांग_min);
	rtc_पंचांग->पंचांग_hour = bcd2bin(rtc_पंचांग->पंचांग_hour);
	rtc_पंचांग->पंचांग_mday = bcd2bin(rtc_पंचांग->पंचांग_mday);
	rtc_पंचांग->पंचांग_mon = bcd2bin(rtc_पंचांग->पंचांग_mon) - 1;
	rtc_पंचांग->पंचांग_year = bcd2bin(rtc_पंचांग->पंचांग_year);

	rtc_पंचांग->पंचांग_year += 100;

	dev_dbg(dev, "read time %ptR\n", rtc_पंचांग);

	clk_disable(pdata->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	व्योम __iomem *base = pdata->reg_base;

	dev_dbg(dev, "set time %ptR\n", पंचांग);

	clk_enable(pdata->clk);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec),  base + PIC32_RTCSEC);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_min),  base + PIC32_RTCMIN);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), base + PIC32_RTCHOUR);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), base + PIC32_RTCDAY);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), base + PIC32_RTCMON);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_year - 100), base + PIC32_RTCYEAR);
	clk_disable(pdata->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_getalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alm_पंचांग = &alrm->समय;
	व्योम __iomem *base = pdata->reg_base;
	अचिन्हित पूर्णांक alm_en;

	clk_enable(pdata->clk);
	alm_पंचांग->पंचांग_sec  = पढ़ोb(base + PIC32_ALRMSEC);
	alm_पंचांग->पंचांग_min  = पढ़ोb(base + PIC32_ALRMMIN);
	alm_पंचांग->पंचांग_hour = पढ़ोb(base + PIC32_ALRMHOUR);
	alm_पंचांग->पंचांग_mon  = पढ़ोb(base + PIC32_ALRMMON);
	alm_पंचांग->पंचांग_mday = पढ़ोb(base + PIC32_ALRMDAY);
	alm_पंचांग->पंचांग_year = पढ़ोb(base + PIC32_ALRMYEAR);

	alm_en = पढ़ोb(base + PIC32_RTCALRM);

	alrm->enabled = (alm_en & PIC32_RTCALRM_ALRMEN) ? 1 : 0;

	dev_dbg(dev, "getalarm: %d, %ptR\n", alm_en, alm_पंचांग);

	alm_पंचांग->पंचांग_sec = bcd2bin(alm_पंचांग->पंचांग_sec);
	alm_पंचांग->पंचांग_min = bcd2bin(alm_पंचांग->पंचांग_min);
	alm_पंचांग->पंचांग_hour = bcd2bin(alm_पंचांग->पंचांग_hour);
	alm_पंचांग->पंचांग_mday = bcd2bin(alm_पंचांग->पंचांग_mday);
	alm_पंचांग->पंचांग_mon = bcd2bin(alm_पंचांग->पंचांग_mon) - 1;
	alm_पंचांग->पंचांग_year = bcd2bin(alm_पंचांग->पंचांग_year);

	clk_disable(pdata->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	व्योम __iomem *base = pdata->reg_base;

	clk_enable(pdata->clk);
	dev_dbg(dev, "setalarm: %d, %ptR\n", alrm->enabled, पंचांग);

	ग_लिखोl(0x00, base + PIC32_ALRMTIME);
	ग_लिखोl(0x00, base + PIC32_ALRMDATE);

	pic32_rtc_setaie(dev, alrm->enabled);

	clk_disable(pdata->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा pic32_rtc_dev *pdata = dev_get_drvdata(dev);
	व्योम __iomem *base = pdata->reg_base;
	अचिन्हित पूर्णांक repeat;

	clk_enable(pdata->clk);

	repeat = पढ़ोw(base + PIC32_RTCALRM);
	repeat &= PIC32_RTCALRM_ARPT;
	seq_म_लिखो(seq, "periodic_IRQ\t: %s\n", repeat  ? "yes" : "no");

	clk_disable(pdata->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pic32_rtcops = अणु
	.पढ़ो_समय	  = pic32_rtc_समय_लो,
	.set_समय	  = pic32_rtc_समय_रखो,
	.पढ़ो_alarm	  = pic32_rtc_getalarm,
	.set_alarm	  = pic32_rtc_setalarm,
	.proc		  = pic32_rtc_proc,
	.alarm_irq_enable = pic32_rtc_setaie,
पूर्ण;

अटल व्योम pic32_rtc_enable(काष्ठा pic32_rtc_dev *pdata, पूर्णांक en)
अणु
	व्योम __iomem *base = pdata->reg_base;

	अगर (!base)
		वापस;

	clk_enable(pdata->clk);
	अगर (!en) अणु
		ग_लिखोl(PIC32_RTCCON_ON, base + PIC32_CLR(PIC32_RTCCON));
	पूर्ण अन्यथा अणु
		pic32_syskey_unlock();

		ग_लिखोl(PIC32_RTCCON_RTCWREN, base + PIC32_SET(PIC32_RTCCON));
		ग_लिखोl(3 << 9, base + PIC32_CLR(PIC32_RTCCON));

		अगर (!(पढ़ोl(base + PIC32_RTCCON) & PIC32_RTCCON_ON))
			ग_लिखोl(PIC32_RTCCON_ON, base + PIC32_SET(PIC32_RTCCON));
	पूर्ण
	clk_disable(pdata->clk);
पूर्ण

अटल पूर्णांक pic32_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pic32_rtc_dev *pdata = platक्रमm_get_drvdata(pdev);

	pic32_rtc_setaie(&pdev->dev, 0);
	clk_unprepare(pdata->clk);
	pdata->clk = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pic32_rtc_dev *pdata;
	पूर्णांक ret;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pdata);

	pdata->alarm_irq = platक्रमm_get_irq(pdev, 0);
	अगर (pdata->alarm_irq < 0)
		वापस pdata->alarm_irq;

	pdata->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->reg_base))
		वापस PTR_ERR(pdata->reg_base);

	pdata->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pdata->clk)) अणु
		dev_err(&pdev->dev, "failed to find rtc clock source\n");
		ret = PTR_ERR(pdata->clk);
		pdata->clk = शून्य;
		वापस ret;
	पूर्ण

	spin_lock_init(&pdata->alarm_lock);

	clk_prepare_enable(pdata->clk);

	pic32_rtc_enable(pdata, 1);

	device_init_wakeup(&pdev->dev, 1);

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc))
		वापस PTR_ERR(pdata->rtc);

	pdata->rtc->ops = &pic32_rtcops;
	pdata->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	pdata->rtc->range_max = RTC_TIMESTAMP_END_2099;

	ret = devm_rtc_रेजिस्टर_device(pdata->rtc);
	अगर (ret)
		जाओ err_nortc;

	pdata->rtc->max_user_freq = 128;

	pic32_rtc_setfreq(&pdev->dev, 1);
	ret = devm_request_irq(&pdev->dev, pdata->alarm_irq,
			       pic32_rtc_alarmirq, 0,
			       dev_name(&pdev->dev), pdata);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"IRQ %d error %d\n", pdata->alarm_irq, ret);
		जाओ err_nortc;
	पूर्ण

	clk_disable(pdata->clk);

	वापस 0;

err_nortc:
	pic32_rtc_enable(pdata, 0);
	clk_disable_unprepare(pdata->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_rtc_dt_ids[] = अणु
	अणु .compatible = "microchip,pic32mzda-rtc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_rtc_dt_ids);

अटल काष्ठा platक्रमm_driver pic32_rtc_driver = अणु
	.probe		= pic32_rtc_probe,
	.हटाओ		= pic32_rtc_हटाओ,
	.driver		= अणु
		.name	= "pic32-rtc",
		.of_match_table	= of_match_ptr(pic32_rtc_dt_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pic32_rtc_driver);

MODULE_DESCRIPTION("Microchip PIC32 RTC Driver");
MODULE_AUTHOR("Joshua Henderson <joshua.henderson@microchip.com>");
MODULE_LICENSE("GPL");
