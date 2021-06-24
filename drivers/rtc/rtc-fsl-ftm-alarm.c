<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale FlexTimer Module (FTM) alarm device driver.
 *
 * Copyright 2014 Freescale Semiconductor, Inc.
 * Copyright 2019-2020 NXP
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/fsl/fपंचांग.h>
#समावेश <linux/rtc.h>
#समावेश <linux/समय.स>
#समावेश <linux/acpi.h>
#समावेश <linux/pm_wakeirq.h>

#घोषणा FTM_SC_CLK(c)		((c) << FTM_SC_CLK_MASK_SHIFT)

/*
 * Select Fixed frequency घड़ी (32KHz) as घड़ी source
 * of FlexTimer Module
 */
#घोषणा FTM_SC_CLKS_FIXED_FREQ	0x02
#घोषणा FIXED_FREQ_CLK		32000

/* Select 128 (2^7) as भागider factor */
#घोषणा MAX_FREQ_DIV		(1 << FTM_SC_PS_MASK)

/* Maximum counter value in FlexTimer's CNT रेजिस्टरs */
#घोषणा MAX_COUNT_VAL		0xffff

काष्ठा fपंचांग_rtc अणु
	काष्ठा rtc_device *rtc_dev;
	व्योम __iomem *base;
	bool big_endian;
	u32 alarm_freq;
पूर्ण;

अटल अंतरभूत u32 rtc_पढ़ोl(काष्ठा fपंचांग_rtc *dev, u32 reg)
अणु
	अगर (dev->big_endian)
		वापस ioपढ़ो32be(dev->base + reg);
	अन्यथा
		वापस ioपढ़ो32(dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम rtc_ग_लिखोl(काष्ठा fपंचांग_rtc *dev, u32 reg, u32 val)
अणु
	अगर (dev->big_endian)
		ioग_लिखो32be(val, dev->base + reg);
	अन्यथा
		ioग_लिखो32(val, dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_counter_enable(काष्ठा fपंचांग_rtc *rtc)
अणु
	u32 val;

	/* select and enable counter घड़ी source */
	val = rtc_पढ़ोl(rtc, FTM_SC);
	val &= ~(FTM_SC_PS_MASK | FTM_SC_CLK_MASK);
	val |= (FTM_SC_PS_MASK | FTM_SC_CLK(FTM_SC_CLKS_FIXED_FREQ));
	rtc_ग_लिखोl(rtc, FTM_SC, val);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_counter_disable(काष्ठा fपंचांग_rtc *rtc)
अणु
	u32 val;

	/* disable counter घड़ी source */
	val = rtc_पढ़ोl(rtc, FTM_SC);
	val &= ~(FTM_SC_PS_MASK | FTM_SC_CLK_MASK);
	rtc_ग_लिखोl(rtc, FTM_SC, val);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_irq_acknowledge(काष्ठा fपंचांग_rtc *rtc)
अणु
	अचिन्हित पूर्णांक समयout = 100;

	/*
	 *Fix errata A-007728 क्रम flexसमयr
	 *	If the FTM counter reaches the FTM_MOD value between
	 *	the पढ़ोing of the TOF bit and the writing of 0 to
	 *	the TOF bit, the process of clearing the TOF bit
	 *	करोes not work as expected when FTMx_CONF[NUMTOF] != 0
	 *	and the current TOF count is less than FTMx_CONF[NUMTOF].
	 *	If the above condition is met, the TOF bit reमुख्यs set.
	 *	If the TOF पूर्णांकerrupt is enabled (FTMx_SC[TOIE] = 1),the
	 *	TOF पूर्णांकerrupt also reमुख्यs निश्चितed.
	 *
	 *	Above is the errata discription
	 *
	 *	In one word: software clearing TOF bit not works when
	 *	FTMx_CONF[NUMTOF] was seted as nonzero and FTM counter
	 *	reaches the FTM_MOD value.
	 *
	 *	The workaround is clearing TOF bit until it works
	 *	(FTM counter करोesn't always reache the FTM_MOD anyway),
	 *	which may cost some cycles.
	 */
	जबतक ((FTM_SC_TOF & rtc_पढ़ोl(rtc, FTM_SC)) && समयout--)
		rtc_ग_लिखोl(rtc, FTM_SC, rtc_पढ़ोl(rtc, FTM_SC) & (~FTM_SC_TOF));
पूर्ण

अटल अंतरभूत व्योम fपंचांग_irq_enable(काष्ठा fपंचांग_rtc *rtc)
अणु
	u32 val;

	val = rtc_पढ़ोl(rtc, FTM_SC);
	val |= FTM_SC_TOIE;
	rtc_ग_लिखोl(rtc, FTM_SC, val);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_irq_disable(काष्ठा fपंचांग_rtc *rtc)
अणु
	u32 val;

	val = rtc_पढ़ोl(rtc, FTM_SC);
	val &= ~FTM_SC_TOIE;
	rtc_ग_लिखोl(rtc, FTM_SC, val);
पूर्ण

अटल अंतरभूत व्योम fपंचांग_reset_counter(काष्ठा fपंचांग_rtc *rtc)
अणु
	/*
	 * The CNT रेजिस्टर contains the FTM counter value.
	 * Reset clears the CNT रेजिस्टर. Writing any value to COUNT
	 * updates the counter with its initial value, CNTIN.
	 */
	rtc_ग_लिखोl(rtc, FTM_CNT, 0x00);
पूर्ण

अटल व्योम fपंचांग_clean_alarm(काष्ठा fपंचांग_rtc *rtc)
अणु
	fपंचांग_counter_disable(rtc);

	rtc_ग_लिखोl(rtc, FTM_CNTIN, 0x00);
	rtc_ग_लिखोl(rtc, FTM_MOD, ~0U);

	fपंचांग_reset_counter(rtc);
पूर्ण

अटल irqवापस_t fपंचांग_rtc_alarm_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा fपंचांग_rtc *rtc = dev;

	rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);

	fपंचांग_irq_acknowledge(rtc);
	fपंचांग_irq_disable(rtc);
	fपंचांग_clean_alarm(rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fपंचांग_rtc_alarm_irq_enable(काष्ठा device *dev,
		अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा fपंचांग_rtc *rtc = dev_get_drvdata(dev);

	अगर (enabled)
		fपंचांग_irq_enable(rtc);
	अन्यथा
		fपंचांग_irq_disable(rtc);

	वापस 0;
पूर्ण

/*
 * Note:
 *	The function is not really getting समय from the RTC
 *	since FlexTimer is not a RTC device, but we need to
 *	get समय to setup alarm, so we are using प्रणाली समय
 *	क्रम now.
 */
अटल पूर्णांक fपंचांग_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	rtc_समय64_to_पंचांग(kसमय_get_real_seconds(), पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	वापस 0;
पूर्ण

/*
 * 1. Select fixed frequency घड़ी (32KHz) as घड़ी source;
 * 2. Select 128 (2^7) as भागider factor;
 * So घड़ी is 250 Hz (32KHz/128).
 *
 * 3. FlexTimer's CNT रेजिस्टर is a 32bit रेजिस्टर,
 * but the रेजिस्टर's 16 bit as counter value,it's other 16 bit
 * is reserved.So minimum counter value is 0x0,maximum counter
 * value is 0xffff.
 * So max alarm value is 262 (65536 / 250) seconds
 */
अटल पूर्णांक fपंचांग_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	समय64_t alm_समय;
	अचिन्हित दीर्घ दीर्घ cycle;
	काष्ठा fपंचांग_rtc *rtc = dev_get_drvdata(dev);

	alm_समय = rtc_पंचांग_to_समय64(&alm->समय);

	fपंचांग_clean_alarm(rtc);
	cycle = (alm_समय - kसमय_get_real_seconds()) * rtc->alarm_freq;
	अगर (cycle > MAX_COUNT_VAL) अणु
		pr_err("Out of alarm range {0~262} seconds.\n");
		वापस -दुस्फल;
	पूर्ण

	fपंचांग_irq_disable(rtc);

	/*
	 * The counter increments until the value of MOD is reached,
	 * at which poपूर्णांक the counter is reloaded with the value of CNTIN.
	 * The TOF (the overflow flag) bit is set when the FTM counter
	 * changes from MOD to CNTIN. So we should using the cycle - 1.
	 */
	rtc_ग_लिखोl(rtc, FTM_MOD, cycle - 1);

	fपंचांग_counter_enable(rtc);
	fपंचांग_irq_enable(rtc);

	वापस 0;

पूर्ण

अटल स्थिर काष्ठा rtc_class_ops fपंचांग_rtc_ops = अणु
	.पढ़ो_समय		= fपंचांग_rtc_पढ़ो_समय,
	.पढ़ो_alarm		= fपंचांग_rtc_पढ़ो_alarm,
	.set_alarm		= fपंचांग_rtc_set_alarm,
	.alarm_irq_enable	= fपंचांग_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक fपंचांग_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq;
	पूर्णांक ret;
	काष्ठा fपंचांग_rtc *rtc;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (unlikely(!rtc)) अणु
		dev_err(&pdev->dev, "cannot alloc memory for rtc\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->base)) अणु
		dev_err(&pdev->dev, "cannot ioremap resource for rtc\n");
		वापस PTR_ERR(rtc->base);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, fपंचांग_rtc_alarm_पूर्णांकerrupt,
			       0, dev_name(&pdev->dev), rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	rtc->big_endian =
		device_property_पढ़ो_bool(&pdev->dev, "big-endian");

	rtc->alarm_freq = (u32)FIXED_FREQ_CLK / (u32)MAX_FREQ_DIV;
	rtc->rtc_dev->ops = &fपंचांग_rtc_ops;

	device_init_wakeup(&pdev->dev, true);
	ret = dev_pm_set_wake_irq(&pdev->dev, irq);
	अगर (ret)
		dev_err(&pdev->dev, "failed to enable irq wake\n");

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't register rtc device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fपंचांग_rtc_match[] = अणु
	अणु .compatible = "fsl,ls1012a-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,ls1021a-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,ls1028a-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,ls1043a-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,ls1046a-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,ls1088a-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,ls208xa-ftm-alarm", पूर्ण,
	अणु .compatible = "fsl,lx2160a-ftm-alarm", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fपंचांग_rtc_match);

अटल स्थिर काष्ठा acpi_device_id fपंचांग_imx_acpi_ids[] = अणु
	अणु"NXP0014",पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fपंचांग_imx_acpi_ids);

अटल काष्ठा platक्रमm_driver fपंचांग_rtc_driver = अणु
	.probe		= fपंचांग_rtc_probe,
	.driver		= अणु
		.name	= "ftm-alarm",
		.of_match_table = fपंचांग_rtc_match,
		.acpi_match_table = ACPI_PTR(fपंचांग_imx_acpi_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init fपंचांग_alarm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fपंचांग_rtc_driver);
पूर्ण

device_initcall(fपंचांग_alarm_init);

MODULE_DESCRIPTION("NXP/Freescale FlexTimer alarm driver");
MODULE_AUTHOR("Biwen Li <biwen.li@nxp.com>");
MODULE_LICENSE("GPL");
