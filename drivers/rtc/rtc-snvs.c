<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2011-2012 Freescale Semiconductor, Inc.

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/rtc.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#घोषणा SNVS_LPREGISTER_OFFSET	0x34

/* These रेजिस्टर offsets are relative to LP (Low Power) range */
#घोषणा SNVS_LPCR		0x04
#घोषणा SNVS_LPSR		0x18
#घोषणा SNVS_LPSRTCMR		0x1c
#घोषणा SNVS_LPSRTCLR		0x20
#घोषणा SNVS_LPTAR		0x24
#घोषणा SNVS_LPPGDR		0x30

#घोषणा SNVS_LPCR_SRTC_ENV	(1 << 0)
#घोषणा SNVS_LPCR_LPTA_EN	(1 << 1)
#घोषणा SNVS_LPCR_LPWUI_EN	(1 << 3)
#घोषणा SNVS_LPSR_LPTA		(1 << 0)

#घोषणा SNVS_LPPGDR_INIT	0x41736166
#घोषणा CNTR_TO_SECS_SH		15

काष्ठा snvs_rtc_data अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *regmap;
	पूर्णांक offset;
	पूर्णांक irq;
	काष्ठा clk *clk;
पूर्ण;

/* Read 64 bit समयr रेजिस्टर, which could be in inconsistent state */
अटल u64 rtc_पढ़ो_lpsrt(काष्ठा snvs_rtc_data *data)
अणु
	u32 msb, lsb;

	regmap_पढ़ो(data->regmap, data->offset + SNVS_LPSRTCMR, &msb);
	regmap_पढ़ो(data->regmap, data->offset + SNVS_LPSRTCLR, &lsb);
	वापस (u64)msb << 32 | lsb;
पूर्ण

/* Read the secure real समय counter, taking care to deal with the हालs of the
 * counter updating जबतक being पढ़ो.
 */
अटल u32 rtc_पढ़ो_lp_counter(काष्ठा snvs_rtc_data *data)
अणु
	u64 पढ़ो1, पढ़ो2;
	अचिन्हित पूर्णांक समयout = 100;

	/* As expected, the रेजिस्टरs might update between the पढ़ो of the LSB
	 * reg and the MSB reg.  It's also possible that one रेजिस्टर might be
	 * in partially modअगरied state as well.
	 */
	पढ़ो1 = rtc_पढ़ो_lpsrt(data);
	करो अणु
		पढ़ो2 = पढ़ो1;
		पढ़ो1 = rtc_पढ़ो_lpsrt(data);
	पूर्ण जबतक (पढ़ो1 != पढ़ो2 && --समयout);
	अगर (!समयout)
		dev_err(&data->rtc->dev, "Timeout trying to get valid LPSRT Counter read\n");

	/* Convert 47-bit counter to 32-bit raw second count */
	वापस (u32) (पढ़ो1 >> CNTR_TO_SECS_SH);
पूर्ण

/* Just पढ़ो the lsb from the counter, dealing with inconsistent state */
अटल पूर्णांक rtc_पढ़ो_lp_counter_lsb(काष्ठा snvs_rtc_data *data, u32 *lsb)
अणु
	u32 count1, count2;
	अचिन्हित पूर्णांक समयout = 100;

	regmap_पढ़ो(data->regmap, data->offset + SNVS_LPSRTCLR, &count1);
	करो अणु
		count2 = count1;
		regmap_पढ़ो(data->regmap, data->offset + SNVS_LPSRTCLR, &count1);
	पूर्ण जबतक (count1 != count2 && --समयout);
	अगर (!समयout) अणु
		dev_err(&data->rtc->dev, "Timeout trying to get valid LPSRT Counter read\n");
		वापस -ETIMEDOUT;
	पूर्ण

	*lsb = count1;
	वापस 0;
पूर्ण

अटल पूर्णांक rtc_ग_लिखो_sync_lp(काष्ठा snvs_rtc_data *data)
अणु
	u32 count1, count2;
	u32 elapsed;
	अचिन्हित पूर्णांक समयout = 1000;
	पूर्णांक ret;

	ret = rtc_पढ़ो_lp_counter_lsb(data, &count1);
	अगर (ret)
		वापस ret;

	/* Wait क्रम 3 CKIL cycles, about 61.0-91.5 तगs */
	करो अणु
		ret = rtc_पढ़ो_lp_counter_lsb(data, &count2);
		अगर (ret)
			वापस ret;
		elapsed = count2 - count1; /* wrap around _is_ handled! */
	पूर्ण जबतक (elapsed < 3 && --समयout);
	अगर (!समयout) अणु
		dev_err(&data->rtc->dev, "Timeout waiting for LPSRT Counter to change\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snvs_rtc_enable(काष्ठा snvs_rtc_data *data, bool enable)
अणु
	पूर्णांक समयout = 1000;
	u32 lpcr;

	regmap_update_bits(data->regmap, data->offset + SNVS_LPCR, SNVS_LPCR_SRTC_ENV,
			   enable ? SNVS_LPCR_SRTC_ENV : 0);

	जबतक (--समयout) अणु
		regmap_पढ़ो(data->regmap, data->offset + SNVS_LPCR, &lpcr);

		अगर (enable) अणु
			अगर (lpcr & SNVS_LPCR_SRTC_ENV)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (!(lpcr & SNVS_LPCR_SRTC_ENV))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!समयout)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक snvs_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;
	पूर्णांक ret;

	ret = clk_enable(data->clk);
	अगर (ret)
		वापस ret;

	समय = rtc_पढ़ो_lp_counter(data);
	rtc_समय64_to_पंचांग(समय, पंचांग);

	clk_disable(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक snvs_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय = rtc_पंचांग_to_समय64(पंचांग);
	पूर्णांक ret;

	ret = clk_enable(data->clk);
	अगर (ret)
		वापस ret;

	/* Disable RTC first */
	ret = snvs_rtc_enable(data, false);
	अगर (ret)
		वापस ret;

	/* Write 32-bit समय to 47-bit समयr, leaving 15 LSBs blank */
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPSRTCLR, समय << CNTR_TO_SECS_SH);
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPSRTCMR, समय >> (32 - CNTR_TO_SECS_SH));

	/* Enable RTC again */
	ret = snvs_rtc_enable(data, true);

	clk_disable(data->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक snvs_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);
	u32 lptar, lpsr;
	पूर्णांक ret;

	ret = clk_enable(data->clk);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(data->regmap, data->offset + SNVS_LPTAR, &lptar);
	rtc_समय64_to_पंचांग(lptar, &alrm->समय);

	regmap_पढ़ो(data->regmap, data->offset + SNVS_LPSR, &lpsr);
	alrm->pending = (lpsr & SNVS_LPSR_LPTA) ? 1 : 0;

	clk_disable(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक snvs_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_enable(data->clk);
	अगर (ret)
		वापस ret;

	regmap_update_bits(data->regmap, data->offset + SNVS_LPCR,
			   (SNVS_LPCR_LPTA_EN | SNVS_LPCR_LPWUI_EN),
			   enable ? (SNVS_LPCR_LPTA_EN | SNVS_LPCR_LPWUI_EN) : 0);

	ret = rtc_ग_लिखो_sync_lp(data);

	clk_disable(data->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक snvs_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय = rtc_पंचांग_to_समय64(&alrm->समय);
	पूर्णांक ret;

	ret = clk_enable(data->clk);
	अगर (ret)
		वापस ret;

	regmap_update_bits(data->regmap, data->offset + SNVS_LPCR, SNVS_LPCR_LPTA_EN, 0);
	ret = rtc_ग_लिखो_sync_lp(data);
	अगर (ret)
		वापस ret;
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPTAR, समय);

	/* Clear alarm पूर्णांकerrupt status bit */
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPSR, SNVS_LPSR_LPTA);

	clk_disable(data->clk);

	वापस snvs_rtc_alarm_irq_enable(dev, alrm->enabled);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops snvs_rtc_ops = अणु
	.पढ़ो_समय = snvs_rtc_पढ़ो_समय,
	.set_समय = snvs_rtc_set_समय,
	.पढ़ो_alarm = snvs_rtc_पढ़ो_alarm,
	.set_alarm = snvs_rtc_set_alarm,
	.alarm_irq_enable = snvs_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t snvs_rtc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा device *dev = dev_id;
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);
	u32 lpsr;
	u32 events = 0;

	clk_enable(data->clk);

	regmap_पढ़ो(data->regmap, data->offset + SNVS_LPSR, &lpsr);

	अगर (lpsr & SNVS_LPSR_LPTA) अणु
		events |= (RTC_AF | RTC_IRQF);

		/* RTC alarm should be one-shot */
		snvs_rtc_alarm_irq_enable(dev, 0);

		rtc_update_irq(data->rtc, 1, events);
	पूर्ण

	/* clear पूर्णांकerrupt status */
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPSR, lpsr);

	clk_disable(data->clk);

	वापस events ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा regmap_config snvs_rtc_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल व्योम snvs_rtc_action(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक snvs_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snvs_rtc_data *data;
	पूर्णांक ret;
	व्योम __iomem *mmio;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(data->rtc))
		वापस PTR_ERR(data->rtc);

	data->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node, "regmap");

	अगर (IS_ERR(data->regmap)) अणु
		dev_warn(&pdev->dev, "snvs rtc: you use old dts file, please update it\n");

		mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(mmio))
			वापस PTR_ERR(mmio);

		data->regmap = devm_regmap_init_mmio(&pdev->dev, mmio, &snvs_rtc_config);
	पूर्ण अन्यथा अणु
		data->offset = SNVS_LPREGISTER_OFFSET;
		of_property_पढ़ो_u32(pdev->dev.of_node, "offset", &data->offset);
	पूर्ण

	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&pdev->dev, "Can't find snvs syscon\n");
		वापस -ENODEV;
	पूर्ण

	data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (data->irq < 0)
		वापस data->irq;

	data->clk = devm_clk_get(&pdev->dev, "snvs-rtc");
	अगर (IS_ERR(data->clk)) अणु
		data->clk = शून्य;
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(data->clk);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Could not prepare or enable the snvs clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_add_action_or_reset(&pdev->dev, snvs_rtc_action, data->clk);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, data);

	/* Initialize glitch detect */
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPPGDR, SNVS_LPPGDR_INIT);

	/* Clear पूर्णांकerrupt status */
	regmap_ग_लिखो(data->regmap, data->offset + SNVS_LPSR, 0xffffffff);

	/* Enable RTC */
	ret = snvs_rtc_enable(data, true);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable rtc %d\n", ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);
	ret = dev_pm_set_wake_irq(&pdev->dev, data->irq);
	अगर (ret)
		dev_err(&pdev->dev, "failed to enable irq wake\n");

	ret = devm_request_irq(&pdev->dev, data->irq, snvs_rtc_irq_handler,
			       IRQF_SHARED, "rtc alarm", &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request irq %d: %d\n",
			data->irq, ret);
		वापस ret;
	पूर्ण

	data->rtc->ops = &snvs_rtc_ops;
	data->rtc->range_max = U32_MAX;

	वापस devm_rtc_रेजिस्टर_device(data->rtc);
पूर्ण

अटल पूर्णांक __maybe_unused snvs_rtc_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);

	clk_disable(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused snvs_rtc_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा snvs_rtc_data *data = dev_get_drvdata(dev);

	अगर (data->clk)
		वापस clk_enable(data->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops snvs_rtc_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(snvs_rtc_suspend_noirq, snvs_rtc_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा of_device_id snvs_dt_ids[] = अणु
	अणु .compatible = "fsl,sec-v4.0-mon-rtc-lp", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, snvs_dt_ids);

अटल काष्ठा platक्रमm_driver snvs_rtc_driver = अणु
	.driver = अणु
		.name	= "snvs_rtc",
		.pm	= &snvs_rtc_pm_ops,
		.of_match_table = snvs_dt_ids,
	पूर्ण,
	.probe		= snvs_rtc_probe,
पूर्ण;
module_platक्रमm_driver(snvs_rtc_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Freescale SNVS RTC Driver");
MODULE_LICENSE("GPL");
