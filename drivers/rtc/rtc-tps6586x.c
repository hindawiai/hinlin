<शैली गुरु>
/*
 * rtc-tps6586x.c: RTC driver क्रम TI PMIC TPS6586X
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/tps6586x.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

#घोषणा RTC_CTRL			0xc0
#घोषणा POR_RESET_N			BIT(7)
#घोषणा OSC_SRC_SEL			BIT(6)
#घोषणा RTC_ENABLE			BIT(5)	/* enables alarm */
#घोषणा RTC_BUF_ENABLE			BIT(4)	/* 32 KHz buffer enable */
#घोषणा PRE_BYPASS			BIT(3)	/* 0=1KHz or 1=32KHz updates */
#घोषणा CL_SEL_MASK			(BIT(2)|BIT(1))
#घोषणा CL_SEL_POS			1
#घोषणा RTC_ALARM1_HI			0xc1
#घोषणा RTC_COUNT4			0xc6

/* start a PMU RTC access by पढ़ोing the रेजिस्टर prior to the RTC_COUNT4 */
#घोषणा RTC_COUNT4_DUMMYREAD		0xc5

/*only 14-bits width in second*/
#घोषणा ALM1_VALID_RANGE_IN_SEC		0x3FFF

#घोषणा TPS6586X_RTC_CL_SEL_1_5PF	0x0
#घोषणा TPS6586X_RTC_CL_SEL_6_5PF	0x1
#घोषणा TPS6586X_RTC_CL_SEL_7_5PF	0x2
#घोषणा TPS6586X_RTC_CL_SEL_12_5PF	0x3

काष्ठा tps6586x_rtc अणु
	काष्ठा device		*dev;
	काष्ठा rtc_device	*rtc;
	पूर्णांक			irq;
	bool			irq_en;
पूर्ण;

अटल अंतरभूत काष्ठा device *to_tps6586x_dev(काष्ठा device *dev)
अणु
	वापस dev->parent;
पूर्ण

अटल पूर्णांक tps6586x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा device *tps_dev = to_tps6586x_dev(dev);
	अचिन्हित दीर्घ दीर्घ ticks = 0;
	समय64_t seconds;
	u8 buff[6];
	पूर्णांक ret;
	पूर्णांक i;

	ret = tps6586x_पढ़ोs(tps_dev, RTC_COUNT4_DUMMYREAD, माप(buff), buff);
	अगर (ret < 0) अणु
		dev_err(dev, "read counter failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 1; i < माप(buff); i++) अणु
		ticks <<= 8;
		ticks |= buff[i];
	पूर्ण

	seconds = ticks >> 10;
	rtc_समय64_to_पंचांग(seconds, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक tps6586x_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा device *tps_dev = to_tps6586x_dev(dev);
	अचिन्हित दीर्घ दीर्घ ticks;
	समय64_t seconds;
	u8 buff[5];
	पूर्णांक ret;

	seconds = rtc_पंचांग_to_समय64(पंचांग);

	ticks = (अचिन्हित दीर्घ दीर्घ)seconds << 10;
	buff[0] = (ticks >> 32) & 0xff;
	buff[1] = (ticks >> 24) & 0xff;
	buff[2] = (ticks >> 16) & 0xff;
	buff[3] = (ticks >> 8) & 0xff;
	buff[4] = ticks & 0xff;

	/* Disable RTC beक्रमe changing समय */
	ret = tps6586x_clr_bits(tps_dev, RTC_CTRL, RTC_ENABLE);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to clear RTC_ENABLE\n");
		वापस ret;
	पूर्ण

	ret = tps6586x_ग_लिखोs(tps_dev, RTC_COUNT4, माप(buff), buff);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to program new time\n");
		वापस ret;
	पूर्ण

	/* Enable RTC */
	ret = tps6586x_set_bits(tps_dev, RTC_CTRL, RTC_ENABLE);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set RTC_ENABLE\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps6586x_rtc_alarm_irq_enable(काष्ठा device *dev,
			 अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा tps6586x_rtc *rtc = dev_get_drvdata(dev);

	अगर (enabled && !rtc->irq_en) अणु
		enable_irq(rtc->irq);
		rtc->irq_en = true;
	पूर्ण अन्यथा अगर (!enabled && rtc->irq_en)  अणु
		disable_irq(rtc->irq);
		rtc->irq_en = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps6586x_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा device *tps_dev = to_tps6586x_dev(dev);
	समय64_t seconds;
	अचिन्हित दीर्घ ticks;
	अचिन्हित दीर्घ rtc_current_समय;
	अचिन्हित दीर्घ दीर्घ rticks = 0;
	u8 buff[3];
	u8 rbuff[6];
	पूर्णांक ret;
	पूर्णांक i;

	seconds = rtc_पंचांग_to_समय64(&alrm->समय);

	ret = tps6586x_rtc_alarm_irq_enable(dev, alrm->enabled);
	अगर (ret < 0) अणु
		dev_err(dev, "can't set alarm irq, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tps6586x_पढ़ोs(tps_dev, RTC_COUNT4_DUMMYREAD,
			माप(rbuff), rbuff);
	अगर (ret < 0) अणु
		dev_err(dev, "read counter failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 1; i < माप(rbuff); i++) अणु
		rticks <<= 8;
		rticks |= rbuff[i];
	पूर्ण

	rtc_current_समय = rticks >> 10;
	अगर ((seconds - rtc_current_समय) > ALM1_VALID_RANGE_IN_SEC)
		seconds = rtc_current_समय - 1;

	ticks = (अचिन्हित दीर्घ दीर्घ)seconds << 10;
	buff[0] = (ticks >> 16) & 0xff;
	buff[1] = (ticks >> 8) & 0xff;
	buff[2] = ticks & 0xff;

	ret = tps6586x_ग_लिखोs(tps_dev, RTC_ALARM1_HI, माप(buff), buff);
	अगर (ret)
		dev_err(dev, "programming alarm failed with err %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tps6586x_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा device *tps_dev = to_tps6586x_dev(dev);
	अचिन्हित दीर्घ ticks;
	समय64_t seconds;
	u8 buff[3];
	पूर्णांक ret;

	ret = tps6586x_पढ़ोs(tps_dev, RTC_ALARM1_HI, माप(buff), buff);
	अगर (ret) अणु
		dev_err(dev, "read RTC_ALARM1_HI failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	ticks = (buff[0] << 16) | (buff[1] << 8) | buff[2];
	seconds = ticks >> 10;

	rtc_समय64_to_पंचांग(seconds, &alrm->समय);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops tps6586x_rtc_ops = अणु
	.पढ़ो_समय	= tps6586x_rtc_पढ़ो_समय,
	.set_समय	= tps6586x_rtc_set_समय,
	.set_alarm	= tps6586x_rtc_set_alarm,
	.पढ़ो_alarm	= tps6586x_rtc_पढ़ो_alarm,
	.alarm_irq_enable = tps6586x_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t tps6586x_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tps6586x_rtc *rtc = data;

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tps6586x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *tps_dev = to_tps6586x_dev(&pdev->dev);
	काष्ठा tps6586x_rtc *rtc;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->dev = &pdev->dev;
	rtc->irq = platक्रमm_get_irq(pdev, 0);

	/* 1 kHz tick mode, enable tick counting */
	ret = tps6586x_update(tps_dev, RTC_CTRL,
		RTC_ENABLE | OSC_SRC_SEL |
		((TPS6586X_RTC_CL_SEL_1_5PF << CL_SEL_POS) & CL_SEL_MASK),
		RTC_ENABLE | OSC_SRC_SEL | PRE_BYPASS | CL_SEL_MASK);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to start counter\n");
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	platक्रमm_set_drvdata(pdev, rtc);
	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc)) अणु
		ret = PTR_ERR(rtc->rtc);
		जाओ fail_rtc_रेजिस्टर;
	पूर्ण

	rtc->rtc->ops = &tps6586x_rtc_ops;
	rtc->rtc->range_max = (1ULL << 30) - 1; /* 30-bit seconds */
	rtc->rtc->start_secs = स_गढ़ो64(2009, 1, 1, 0, 0, 0);
	rtc->rtc->set_start_समय = true;

	irq_set_status_flags(rtc->irq, IRQ_NOAUTOEN);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
				tps6586x_rtc_irq,
				IRQF_ONESHOT,
				dev_name(&pdev->dev), rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request IRQ(%d) failed with ret %d\n",
				rtc->irq, ret);
		जाओ fail_rtc_रेजिस्टर;
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret)
		जाओ fail_rtc_रेजिस्टर;

	वापस 0;

fail_rtc_रेजिस्टर:
	tps6586x_update(tps_dev, RTC_CTRL, 0,
		RTC_ENABLE | OSC_SRC_SEL | PRE_BYPASS | CL_SEL_MASK);
	वापस ret;
पूर्ण;

अटल पूर्णांक tps6586x_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *tps_dev = to_tps6586x_dev(&pdev->dev);

	tps6586x_update(tps_dev, RTC_CTRL, 0,
		RTC_ENABLE | OSC_SRC_SEL | PRE_BYPASS | CL_SEL_MASK);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tps6586x_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tps6586x_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(rtc->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक tps6586x_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा tps6586x_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(rtc->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tps6586x_pm_ops, tps6586x_rtc_suspend,
			tps6586x_rtc_resume);

अटल काष्ठा platक्रमm_driver tps6586x_rtc_driver = अणु
	.driver	= अणु
		.name	= "tps6586x-rtc",
		.pm	= &tps6586x_pm_ops,
	पूर्ण,
	.probe	= tps6586x_rtc_probe,
	.हटाओ	= tps6586x_rtc_हटाओ,
पूर्ण;
module_platक्रमm_driver(tps6586x_rtc_driver);

MODULE_ALIAS("platform:tps6586x-rtc");
MODULE_DESCRIPTION("TI TPS6586x RTC driver");
MODULE_AUTHOR("Laxman dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
