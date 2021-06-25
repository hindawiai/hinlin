<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/rtc/rtc-s3c.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Copyright (c) 2004,2006 Simtec Electronics
 *	Ben Dooks, <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C2410/S3C2440/S3C24XX Internal RTC Driver
*/

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/clk.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश "rtc-s3c.h"

काष्ठा s3c_rtc अणु
	काष्ठा device *dev;
	काष्ठा rtc_device *rtc;

	व्योम __iomem *base;
	काष्ठा clk *rtc_clk;
	काष्ठा clk *rtc_src_clk;
	bool alarm_enabled;

	स्थिर काष्ठा s3c_rtc_data *data;

	पूर्णांक irq_alarm;
	spinlock_t alarm_lock;

	bool wake_en;
पूर्ण;

काष्ठा s3c_rtc_data अणु
	bool needs_src_clk;

	व्योम (*irq_handler) (काष्ठा s3c_rtc *info, पूर्णांक mask);
	व्योम (*enable) (काष्ठा s3c_rtc *info);
	व्योम (*disable) (काष्ठा s3c_rtc *info);
पूर्ण;

अटल पूर्णांक s3c_rtc_enable_clk(काष्ठा s3c_rtc *info)
अणु
	पूर्णांक ret;

	ret = clk_enable(info->rtc_clk);
	अगर (ret)
		वापस ret;

	अगर (info->data->needs_src_clk) अणु
		ret = clk_enable(info->rtc_src_clk);
		अगर (ret) अणु
			clk_disable(info->rtc_clk);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम s3c_rtc_disable_clk(काष्ठा s3c_rtc *info)
अणु
	अगर (info->data->needs_src_clk)
		clk_disable(info->rtc_src_clk);
	clk_disable(info->rtc_clk);
पूर्ण

/* IRQ Handler */
अटल irqवापस_t s3c_rtc_alarmirq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा s3c_rtc *info = (काष्ठा s3c_rtc *)id;

	अगर (info->data->irq_handler)
		info->data->irq_handler(info, S3C2410_INTP_ALM);

	वापस IRQ_HANDLED;
पूर्ण

/* Update control रेजिस्टरs */
अटल पूर्णांक s3c_rtc_setaie(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	dev_dbg(info->dev, "%s: aie=%d\n", __func__, enabled);

	ret = s3c_rtc_enable_clk(info);
	अगर (ret)
		वापस ret;

	पंचांगp = पढ़ोb(info->base + S3C2410_RTCALM) & ~S3C2410_RTCALM_ALMEN;

	अगर (enabled)
		पंचांगp |= S3C2410_RTCALM_ALMEN;

	ग_लिखोb(पंचांगp, info->base + S3C2410_RTCALM);

	spin_lock_irqsave(&info->alarm_lock, flags);

	अगर (info->alarm_enabled && !enabled)
		s3c_rtc_disable_clk(info);
	अन्यथा अगर (!info->alarm_enabled && enabled)
		ret = s3c_rtc_enable_clk(info);

	info->alarm_enabled = enabled;
	spin_unlock_irqrestore(&info->alarm_lock, flags);

	s3c_rtc_disable_clk(info);

	वापस ret;
पूर्ण

/* Time पढ़ो/ग_लिखो */
अटल पूर्णांक s3c_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक have_retried = 0;
	पूर्णांक ret;

	ret = s3c_rtc_enable_clk(info);
	अगर (ret)
		वापस ret;

retry_get_समय:
	rtc_पंचांग->पंचांग_min  = पढ़ोb(info->base + S3C2410_RTCMIN);
	rtc_पंचांग->पंचांग_hour = पढ़ोb(info->base + S3C2410_RTCHOUR);
	rtc_पंचांग->पंचांग_mday = पढ़ोb(info->base + S3C2410_RTCDATE);
	rtc_पंचांग->पंचांग_mon  = पढ़ोb(info->base + S3C2410_RTCMON);
	rtc_पंचांग->पंचांग_year = पढ़ोb(info->base + S3C2410_RTCYEAR);
	rtc_पंचांग->पंचांग_sec  = पढ़ोb(info->base + S3C2410_RTCSEC);

	/* the only way to work out whether the प्रणाली was mid-update
	 * when we पढ़ो it is to check the second counter, and अगर it
	 * is zero, then we re-try the entire पढ़ो
	 */

	अगर (rtc_पंचांग->पंचांग_sec == 0 && !have_retried) अणु
		have_retried = 1;
		जाओ retry_get_समय;
	पूर्ण

	rtc_पंचांग->पंचांग_sec = bcd2bin(rtc_पंचांग->पंचांग_sec);
	rtc_पंचांग->पंचांग_min = bcd2bin(rtc_पंचांग->पंचांग_min);
	rtc_पंचांग->पंचांग_hour = bcd2bin(rtc_पंचांग->पंचांग_hour);
	rtc_पंचांग->पंचांग_mday = bcd2bin(rtc_पंचांग->पंचांग_mday);
	rtc_पंचांग->पंचांग_mon = bcd2bin(rtc_पंचांग->पंचांग_mon);
	rtc_पंचांग->पंचांग_year = bcd2bin(rtc_पंचांग->पंचांग_year);

	s3c_rtc_disable_clk(info);

	rtc_पंचांग->पंचांग_year += 100;
	rtc_पंचांग->पंचांग_mon -= 1;

	dev_dbg(dev, "read time %ptR\n", rtc_पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);
	पूर्णांक year = पंचांग->पंचांग_year - 100;
	पूर्णांक ret;

	dev_dbg(dev, "set time %ptR\n", पंचांग);

	/* we get around y2k by simply not supporting it */

	अगर (year < 0 || year >= 100) अणु
		dev_err(dev, "rtc only supports 100 years\n");
		वापस -EINVAL;
	पूर्ण

	ret = s3c_rtc_enable_clk(info);
	अगर (ret)
		वापस ret;

	ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec),  info->base + S3C2410_RTCSEC);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_min),  info->base + S3C2410_RTCMIN);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), info->base + S3C2410_RTCHOUR);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), info->base + S3C2410_RTCDATE);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), info->base + S3C2410_RTCMON);
	ग_लिखोb(bin2bcd(year), info->base + S3C2410_RTCYEAR);

	s3c_rtc_disable_clk(info);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_rtc_getalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alm_पंचांग = &alrm->समय;
	अचिन्हित पूर्णांक alm_en;
	पूर्णांक ret;

	ret = s3c_rtc_enable_clk(info);
	अगर (ret)
		वापस ret;

	alm_पंचांग->पंचांग_sec  = पढ़ोb(info->base + S3C2410_ALMSEC);
	alm_पंचांग->पंचांग_min  = पढ़ोb(info->base + S3C2410_ALMMIN);
	alm_पंचांग->पंचांग_hour = पढ़ोb(info->base + S3C2410_ALMHOUR);
	alm_पंचांग->पंचांग_mon  = पढ़ोb(info->base + S3C2410_ALMMON);
	alm_पंचांग->पंचांग_mday = पढ़ोb(info->base + S3C2410_ALMDATE);
	alm_पंचांग->पंचांग_year = पढ़ोb(info->base + S3C2410_ALMYEAR);

	alm_en = पढ़ोb(info->base + S3C2410_RTCALM);

	s3c_rtc_disable_clk(info);

	alrm->enabled = (alm_en & S3C2410_RTCALM_ALMEN) ? 1 : 0;

	dev_dbg(dev, "read alarm %d, %ptR\n", alm_en, alm_पंचांग);

	/* decode the alarm enable field */
	अगर (alm_en & S3C2410_RTCALM_SECEN)
		alm_पंचांग->पंचांग_sec = bcd2bin(alm_पंचांग->पंचांग_sec);

	अगर (alm_en & S3C2410_RTCALM_MINEN)
		alm_पंचांग->पंचांग_min = bcd2bin(alm_पंचांग->पंचांग_min);

	अगर (alm_en & S3C2410_RTCALM_HOUREN)
		alm_पंचांग->पंचांग_hour = bcd2bin(alm_पंचांग->पंचांग_hour);

	अगर (alm_en & S3C2410_RTCALM_DAYEN)
		alm_पंचांग->पंचांग_mday = bcd2bin(alm_पंचांग->पंचांग_mday);

	अगर (alm_en & S3C2410_RTCALM_MONEN) अणु
		alm_पंचांग->पंचांग_mon = bcd2bin(alm_पंचांग->पंचांग_mon);
		alm_पंचांग->पंचांग_mon -= 1;
	पूर्ण

	अगर (alm_en & S3C2410_RTCALM_YEAREN)
		alm_पंचांग->पंचांग_year = bcd2bin(alm_पंचांग->पंचांग_year);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	अचिन्हित पूर्णांक alrm_en;
	पूर्णांक ret;

	dev_dbg(dev, "s3c_rtc_setalarm: %d, %ptR\n", alrm->enabled, पंचांग);

	ret = s3c_rtc_enable_clk(info);
	अगर (ret)
		वापस ret;

	alrm_en = पढ़ोb(info->base + S3C2410_RTCALM) & S3C2410_RTCALM_ALMEN;
	ग_लिखोb(0x00, info->base + S3C2410_RTCALM);

	अगर (पंचांग->पंचांग_sec < 60 && पंचांग->पंचांग_sec >= 0) अणु
		alrm_en |= S3C2410_RTCALM_SECEN;
		ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec), info->base + S3C2410_ALMSEC);
	पूर्ण

	अगर (पंचांग->पंचांग_min < 60 && पंचांग->पंचांग_min >= 0) अणु
		alrm_en |= S3C2410_RTCALM_MINEN;
		ग_लिखोb(bin2bcd(पंचांग->पंचांग_min), info->base + S3C2410_ALMMIN);
	पूर्ण

	अगर (पंचांग->पंचांग_hour < 24 && पंचांग->पंचांग_hour >= 0) अणु
		alrm_en |= S3C2410_RTCALM_HOUREN;
		ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), info->base + S3C2410_ALMHOUR);
	पूर्ण

	अगर (पंचांग->पंचांग_mon < 12 && पंचांग->पंचांग_mon >= 0) अणु
		alrm_en |= S3C2410_RTCALM_MONEN;
		ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), info->base + S3C2410_ALMMON);
	पूर्ण

	अगर (पंचांग->पंचांग_mday <= 31 && पंचांग->पंचांग_mday >= 1) अणु
		alrm_en |= S3C2410_RTCALM_DAYEN;
		ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), info->base + S3C2410_ALMDATE);
	पूर्ण

	dev_dbg(dev, "setting S3C2410_RTCALM to %08x\n", alrm_en);

	ग_लिखोb(alrm_en, info->base + S3C2410_RTCALM);

	s3c_rtc_setaie(dev, alrm->enabled);

	s3c_rtc_disable_clk(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops s3c_rtcops = अणु
	.पढ़ो_समय	= s3c_rtc_समय_लो,
	.set_समय	= s3c_rtc_समय_रखो,
	.पढ़ो_alarm	= s3c_rtc_getalarm,
	.set_alarm	= s3c_rtc_setalarm,
	.alarm_irq_enable = s3c_rtc_setaie,
पूर्ण;

अटल व्योम s3c24xx_rtc_enable(काष्ठा s3c_rtc *info)
अणु
	अचिन्हित पूर्णांक con, पंचांगp;

	con = पढ़ोw(info->base + S3C2410_RTCCON);
	/* re-enable the device, and check it is ok */
	अगर ((con & S3C2410_RTCCON_RTCEN) == 0) अणु
		dev_info(info->dev, "rtc disabled, re-enabling\n");

		पंचांगp = पढ़ोw(info->base + S3C2410_RTCCON);
		ग_लिखोw(पंचांगp | S3C2410_RTCCON_RTCEN, info->base + S3C2410_RTCCON);
	पूर्ण

	अगर (con & S3C2410_RTCCON_CNTSEL) अणु
		dev_info(info->dev, "removing RTCCON_CNTSEL\n");

		पंचांगp = पढ़ोw(info->base + S3C2410_RTCCON);
		ग_लिखोw(पंचांगp & ~S3C2410_RTCCON_CNTSEL,
		       info->base + S3C2410_RTCCON);
	पूर्ण

	अगर (con & S3C2410_RTCCON_CLKRST) अणु
		dev_info(info->dev, "removing RTCCON_CLKRST\n");

		पंचांगp = पढ़ोw(info->base + S3C2410_RTCCON);
		ग_लिखोw(पंचांगp & ~S3C2410_RTCCON_CLKRST,
		       info->base + S3C2410_RTCCON);
	पूर्ण
पूर्ण

अटल व्योम s3c24xx_rtc_disable(काष्ठा s3c_rtc *info)
अणु
	अचिन्हित पूर्णांक con;

	con = पढ़ोw(info->base + S3C2410_RTCCON);
	con &= ~S3C2410_RTCCON_RTCEN;
	ग_लिखोw(con, info->base + S3C2410_RTCCON);

	con = पढ़ोb(info->base + S3C2410_TICNT);
	con &= ~S3C2410_TICNT_ENABLE;
	ग_लिखोb(con, info->base + S3C2410_TICNT);
पूर्ण

अटल व्योम s3c6410_rtc_disable(काष्ठा s3c_rtc *info)
अणु
	अचिन्हित पूर्णांक con;

	con = पढ़ोw(info->base + S3C2410_RTCCON);
	con &= ~S3C64XX_RTCCON_TICEN;
	con &= ~S3C2410_RTCCON_RTCEN;
	ग_लिखोw(con, info->base + S3C2410_RTCCON);
पूर्ण

अटल पूर्णांक s3c_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_rtc *info = platक्रमm_get_drvdata(pdev);

	s3c_rtc_setaie(info->dev, 0);

	अगर (info->data->needs_src_clk)
		clk_unprepare(info->rtc_src_clk);
	clk_unprepare(info->rtc_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_rtc *info = शून्य;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->data = of_device_get_match_data(&pdev->dev);
	अगर (!info->data) अणु
		dev_err(&pdev->dev, "failed getting s3c_rtc_data\n");
		वापस -EINVAL;
	पूर्ण
	spin_lock_init(&info->alarm_lock);

	platक्रमm_set_drvdata(pdev, info);

	info->irq_alarm = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq_alarm < 0)
		वापस info->irq_alarm;

	dev_dbg(&pdev->dev, "s3c2410_rtc: alarm irq %d\n", info->irq_alarm);

	/* get the memory region */
	info->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->base))
		वापस PTR_ERR(info->base);

	info->rtc_clk = devm_clk_get(&pdev->dev, "rtc");
	अगर (IS_ERR(info->rtc_clk)) अणु
		ret = PTR_ERR(info->rtc_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to find rtc clock\n");
		अन्यथा
			dev_dbg(&pdev->dev, "probe deferred due to missing rtc clk\n");
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(info->rtc_clk);
	अगर (ret)
		वापस ret;

	अगर (info->data->needs_src_clk) अणु
		info->rtc_src_clk = devm_clk_get(&pdev->dev, "rtc_src");
		अगर (IS_ERR(info->rtc_src_clk)) अणु
			ret = dev_err_probe(&pdev->dev, PTR_ERR(info->rtc_src_clk),
					    "failed to find rtc source clock\n");
			जाओ err_src_clk;
		पूर्ण
		ret = clk_prepare_enable(info->rtc_src_clk);
		अगर (ret)
			जाओ err_src_clk;
	पूर्ण

	/* disable RTC enable bits potentially set by the bootloader */
	अगर (info->data->disable)
		info->data->disable(info);

	/* check to see अगर everything is setup correctly */
	अगर (info->data->enable)
		info->data->enable(info);

	dev_dbg(&pdev->dev, "s3c2410_rtc: RTCCON=%02x\n",
		पढ़ोw(info->base + S3C2410_RTCCON));

	device_init_wakeup(&pdev->dev, 1);

	/* रेजिस्टर RTC and निकास */
	info->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "s3c", &s3c_rtcops,
					     THIS_MODULE);
	अगर (IS_ERR(info->rtc)) अणु
		dev_err(&pdev->dev, "cannot attach rtc\n");
		ret = PTR_ERR(info->rtc);
		जाओ err_nortc;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, info->irq_alarm, s3c_rtc_alarmirq,
			       0, "s3c2410-rtc alarm", info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ%d error %d\n", info->irq_alarm, ret);
		जाओ err_nortc;
	पूर्ण

	s3c_rtc_disable_clk(info);

	वापस 0;

err_nortc:
	अगर (info->data->disable)
		info->data->disable(info);

	अगर (info->data->needs_src_clk)
		clk_disable_unprepare(info->rtc_src_clk);
err_src_clk:
	clk_disable_unprepare(info->rtc_clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक s3c_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = s3c_rtc_enable_clk(info);
	अगर (ret)
		वापस ret;

	अगर (info->data->disable)
		info->data->disable(info);

	अगर (device_may_wakeup(dev) && !info->wake_en) अणु
		अगर (enable_irq_wake(info->irq_alarm) == 0)
			info->wake_en = true;
		अन्यथा
			dev_err(dev, "enable_irq_wake failed\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा s3c_rtc *info = dev_get_drvdata(dev);

	अगर (info->data->enable)
		info->data->enable(info);

	s3c_rtc_disable_clk(info);

	अगर (device_may_wakeup(dev) && info->wake_en) अणु
		disable_irq_wake(info->irq_alarm);
		info->wake_en = false;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(s3c_rtc_pm_ops, s3c_rtc_suspend, s3c_rtc_resume);

अटल व्योम s3c24xx_rtc_irq(काष्ठा s3c_rtc *info, पूर्णांक mask)
अणु
	rtc_update_irq(info->rtc, 1, RTC_AF | RTC_IRQF);
पूर्ण

अटल व्योम s3c6410_rtc_irq(काष्ठा s3c_rtc *info, पूर्णांक mask)
अणु
	rtc_update_irq(info->rtc, 1, RTC_AF | RTC_IRQF);
	ग_लिखोb(mask, info->base + S3C2410_INTP);
पूर्ण

अटल काष्ठा s3c_rtc_data स्थिर s3c2410_rtc_data = अणु
	.irq_handler		= s3c24xx_rtc_irq,
	.enable			= s3c24xx_rtc_enable,
	.disable		= s3c24xx_rtc_disable,
पूर्ण;

अटल काष्ठा s3c_rtc_data स्थिर s3c2416_rtc_data = अणु
	.irq_handler		= s3c24xx_rtc_irq,
	.enable			= s3c24xx_rtc_enable,
	.disable		= s3c24xx_rtc_disable,
पूर्ण;

अटल काष्ठा s3c_rtc_data स्थिर s3c2443_rtc_data = अणु
	.irq_handler		= s3c24xx_rtc_irq,
	.enable			= s3c24xx_rtc_enable,
	.disable		= s3c24xx_rtc_disable,
पूर्ण;

अटल काष्ठा s3c_rtc_data स्थिर s3c6410_rtc_data = अणु
	.needs_src_clk		= true,
	.irq_handler		= s3c6410_rtc_irq,
	.enable			= s3c24xx_rtc_enable,
	.disable		= s3c6410_rtc_disable,
पूर्ण;

अटल स्थिर __maybe_unused काष्ठा of_device_id s3c_rtc_dt_match[] = अणु
	अणु
		.compatible = "samsung,s3c2410-rtc",
		.data = &s3c2410_rtc_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c2416-rtc",
		.data = &s3c2416_rtc_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c2443-rtc",
		.data = &s3c2443_rtc_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c6410-rtc",
		.data = &s3c6410_rtc_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos3250-rtc",
		.data = &s3c6410_rtc_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3c_rtc_dt_match);

अटल काष्ठा platक्रमm_driver s3c_rtc_driver = अणु
	.probe		= s3c_rtc_probe,
	.हटाओ		= s3c_rtc_हटाओ,
	.driver		= अणु
		.name	= "s3c-rtc",
		.pm	= &s3c_rtc_pm_ops,
		.of_match_table	= of_match_ptr(s3c_rtc_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(s3c_rtc_driver);

MODULE_DESCRIPTION("Samsung S3C RTC Driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c2410-rtc");
