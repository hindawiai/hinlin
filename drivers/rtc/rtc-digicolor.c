<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Real Time Clock driver क्रम Conexant Digicolor
 *
 * Copyright (C) 2015 Paraकरोx Innovation Ltd.
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 */

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>

#घोषणा DC_RTC_CONTROL		0x0
#घोषणा DC_RTC_TIME		0x8
#घोषणा DC_RTC_REFERENCE	0xc
#घोषणा DC_RTC_ALARM		0x10
#घोषणा DC_RTC_INTFLAG_CLEAR	0x14
#घोषणा DC_RTC_INTENABLE	0x16

#घोषणा DC_RTC_CMD_MASK		0xf
#घोषणा DC_RTC_GO_BUSY		BIT(7)

#घोषणा CMD_NOP			0
#घोषणा CMD_RESET		1
#घोषणा CMD_WRITE		3
#घोषणा CMD_READ		4

#घोषणा CMD_DELAY_US		(10*1000)
#घोषणा CMD_TIMEOUT_US		(500*CMD_DELAY_US)

काष्ठा dc_rtc अणु
	काष्ठा rtc_device	*rtc_dev;
	व्योम __iomem		*regs;
पूर्ण;

अटल पूर्णांक dc_rtc_cmds(काष्ठा dc_rtc *rtc, स्थिर u8 *cmds, पूर्णांक len)
अणु
	u8 val;
	पूर्णांक i, ret;

	क्रम (i = 0; i < len; i++) अणु
		ग_लिखोb_relaxed((cmds[i] & DC_RTC_CMD_MASK) | DC_RTC_GO_BUSY,
			       rtc->regs + DC_RTC_CONTROL);
		ret = पढ़ोb_relaxed_poll_समयout(
			rtc->regs + DC_RTC_CONTROL, val,
			!(val & DC_RTC_GO_BUSY), CMD_DELAY_US, CMD_TIMEOUT_US);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dc_rtc_पढ़ो(काष्ठा dc_rtc *rtc, अचिन्हित दीर्घ *val)
अणु
	अटल स्थिर u8 पढ़ो_cmds[] = अणुCMD_READ, CMD_NOPपूर्ण;
	u32 reference, समय1, समय2;
	पूर्णांक ret;

	ret = dc_rtc_cmds(rtc, पढ़ो_cmds, ARRAY_SIZE(पढ़ो_cmds));
	अगर (ret < 0)
		वापस ret;

	reference = पढ़ोl_relaxed(rtc->regs + DC_RTC_REFERENCE);
	समय1 = पढ़ोl_relaxed(rtc->regs + DC_RTC_TIME);
	/* Read twice to ensure consistency */
	जबतक (1) अणु
		समय2 = पढ़ोl_relaxed(rtc->regs + DC_RTC_TIME);
		अगर (समय1 == समय2)
			अवरोध;
		समय1 = समय2;
	पूर्ण

	*val = reference + समय1;
	वापस 0;
पूर्ण

अटल पूर्णांक dc_rtc_ग_लिखो(काष्ठा dc_rtc *rtc, u32 val)
अणु
	अटल स्थिर u8 ग_लिखो_cmds[] = अणुCMD_WRITE, CMD_NOP, CMD_RESET, CMD_NOPपूर्ण;

	ग_लिखोl_relaxed(val, rtc->regs + DC_RTC_REFERENCE);
	वापस dc_rtc_cmds(rtc, ग_लिखो_cmds, ARRAY_SIZE(ग_लिखो_cmds));
पूर्ण

अटल पूर्णांक dc_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा dc_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ now;
	पूर्णांक ret;

	ret = dc_rtc_पढ़ो(rtc, &now);
	अगर (ret < 0)
		वापस ret;
	rtc_समय64_to_पंचांग(now, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा dc_rtc *rtc = dev_get_drvdata(dev);

	वापस dc_rtc_ग_लिखो(rtc, rtc_पंचांग_to_समय64(पंचांग));
पूर्ण

अटल पूर्णांक dc_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा dc_rtc *rtc = dev_get_drvdata(dev);
	u32 alarm_reg, reference;
	अचिन्हित दीर्घ now;
	पूर्णांक ret;

	alarm_reg = पढ़ोl_relaxed(rtc->regs + DC_RTC_ALARM);
	reference = पढ़ोl_relaxed(rtc->regs + DC_RTC_REFERENCE);
	rtc_समय64_to_पंचांग(reference + alarm_reg, &alarm->समय);

	ret = dc_rtc_पढ़ो(rtc, &now);
	अगर (ret < 0)
		वापस ret;

	alarm->pending = alarm_reg + reference > now;
	alarm->enabled = पढ़ोl_relaxed(rtc->regs + DC_RTC_INTENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा dc_rtc *rtc = dev_get_drvdata(dev);
	समय64_t alarm_समय;
	u32 reference;

	alarm_समय = rtc_पंचांग_to_समय64(&alarm->समय);

	reference = पढ़ोl_relaxed(rtc->regs + DC_RTC_REFERENCE);
	ग_लिखोl_relaxed(alarm_समय - reference, rtc->regs + DC_RTC_ALARM);

	ग_लिखोb_relaxed(!!alarm->enabled, rtc->regs + DC_RTC_INTENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा dc_rtc *rtc = dev_get_drvdata(dev);

	ग_लिखोb_relaxed(!!enabled, rtc->regs + DC_RTC_INTENABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops dc_rtc_ops = अणु
	.पढ़ो_समय		= dc_rtc_पढ़ो_समय,
	.set_समय		= dc_rtc_set_समय,
	.पढ़ो_alarm		= dc_rtc_पढ़ो_alarm,
	.set_alarm		= dc_rtc_set_alarm,
	.alarm_irq_enable	= dc_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t dc_rtc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dc_rtc *rtc = dev_id;

	ग_लिखोb_relaxed(1, rtc->regs + DC_RTC_INTFLAG_CLEAR);
	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init dc_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dc_rtc *rtc;
	पूर्णांक irq, ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->regs))
		वापस PTR_ERR(rtc->regs);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	ret = devm_request_irq(&pdev->dev, irq, dc_rtc_irq, 0, pdev->name, rtc);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev->ops = &dc_rtc_ops;
	rtc->rtc_dev->range_max = U32_MAX;

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id dc_dt_ids[] = अणु
	अणु .compatible = "cnxt,cx92755-rtc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dc_dt_ids);

अटल काष्ठा platक्रमm_driver dc_rtc_driver = अणु
	.driver = अणु
		.name = "digicolor_rtc",
		.of_match_table = of_match_ptr(dc_dt_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver_probe(dc_rtc_driver, dc_rtc_probe);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Conexant Digicolor Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL");
