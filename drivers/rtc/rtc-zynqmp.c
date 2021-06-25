<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Zynq Ultrascale+ MPSoC Real Time Clock Driver
 *
 * Copyright (C) 2015 Xilinx, Inc.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

/* RTC Registers */
#घोषणा RTC_SET_TM_WR		0x00
#घोषणा RTC_SET_TM_RD		0x04
#घोषणा RTC_CALIB_WR		0x08
#घोषणा RTC_CALIB_RD		0x0C
#घोषणा RTC_CUR_TM		0x10
#घोषणा RTC_CUR_TICK		0x14
#घोषणा RTC_ALRM		0x18
#घोषणा RTC_INT_STS		0x20
#घोषणा RTC_INT_MASK		0x24
#घोषणा RTC_INT_EN		0x28
#घोषणा RTC_INT_DIS		0x2C
#घोषणा RTC_CTRL		0x40

#घोषणा RTC_FR_EN		BIT(20)
#घोषणा RTC_FR_DATSHIFT		16
#घोषणा RTC_TICK_MASK		0xFFFF
#घोषणा RTC_INT_SEC		BIT(0)
#घोषणा RTC_INT_ALRM		BIT(1)
#घोषणा RTC_OSC_EN		BIT(24)
#घोषणा RTC_BATT_EN		BIT(31)

#घोषणा RTC_CALIB_DEF		0x198233
#घोषणा RTC_CALIB_MASK		0x1FFFFF
#घोषणा RTC_ALRM_MASK          BIT(1)
#घोषणा RTC_MSEC               1000

काष्ठा xlnx_rtc_dev अणु
	काष्ठा rtc_device	*rtc;
	व्योम __iomem		*reg_base;
	पूर्णांक			alarm_irq;
	पूर्णांक			sec_irq;
	अचिन्हित पूर्णांक		calibval;
पूर्ण;

अटल पूर्णांक xlnx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);
	अचिन्हित दीर्घ new_समय;

	/*
	 * The value written will be updated after 1 sec पूर्णांकo the
	 * seconds पढ़ो रेजिस्टर, so we need to program समय +1 sec
	 * to get the correct समय on पढ़ो.
	 */
	new_समय = rtc_पंचांग_to_समय64(पंचांग) + 1;

	/*
	 * Writing पूर्णांकo calibration रेजिस्टर will clear the Tick Counter and
	 * क्रमce the next second to be संकेतed exactly in 1 second period
	 */
	xrtcdev->calibval &= RTC_CALIB_MASK;
	ग_लिखोl(xrtcdev->calibval, (xrtcdev->reg_base + RTC_CALIB_WR));

	ग_लिखोl(new_समय, xrtcdev->reg_base + RTC_SET_TM_WR);

	/*
	 * Clear the rtc पूर्णांकerrupt status रेजिस्टर after setting the
	 * समय. During a पढ़ो_समय function, the code should पढ़ो the
	 * RTC_INT_STATUS रेजिस्टर and अगर bit 0 is still 0, it means
	 * that one second has not elapsed yet since RTC was set and
	 * the current समय should be पढ़ो from SET_TIME_READ रेजिस्टर;
	 * otherwise, CURRENT_TIME रेजिस्टर is पढ़ो to report the समय
	 */
	ग_लिखोl(RTC_INT_SEC, xrtcdev->reg_base + RTC_INT_STS);

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	u32 status;
	अचिन्हित दीर्घ पढ़ो_समय;
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	status = पढ़ोl(xrtcdev->reg_base + RTC_INT_STS);

	अगर (status & RTC_INT_SEC) अणु
		/*
		 * RTC has updated the CURRENT_TIME with the समय written पूर्णांकo
		 * SET_TIME_WRITE रेजिस्टर.
		 */
		पढ़ो_समय = पढ़ोl(xrtcdev->reg_base + RTC_CUR_TM);
	पूर्ण अन्यथा अणु
		/*
		 * Time written in SET_TIME_WRITE has not yet updated पूर्णांकo
		 * the seconds पढ़ो रेजिस्टर, so पढ़ो the समय from the
		 * SET_TIME_WRITE instead of CURRENT_TIME रेजिस्टर.
		 * Since we add +1 sec जबतक writing, we need to -1 sec जबतक
		 * पढ़ोing.
		 */
		पढ़ो_समय = पढ़ोl(xrtcdev->reg_base + RTC_SET_TM_RD) - 1;
	पूर्ण
	rtc_समय64_to_पंचांग(पढ़ो_समय, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(xrtcdev->reg_base + RTC_ALRM), &alrm->समय);
	alrm->enabled = पढ़ोl(xrtcdev->reg_base + RTC_INT_MASK) & RTC_INT_ALRM;

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_rtc_alarm_irq_enable(काष्ठा device *dev, u32 enabled)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक status;
	uदीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(RTC_MSEC);

	अगर (enabled) अणु
		जबतक (1) अणु
			status = पढ़ोl(xrtcdev->reg_base + RTC_INT_STS);
			अगर (!((status & RTC_ALRM_MASK) == RTC_ALRM_MASK))
				अवरोध;

			अगर (समय_after_eq(jअगरfies, समयout)) अणु
				dev_err(dev, "Time out occur, while clearing alarm status bit\n");
				वापस -ETIMEDOUT;
			पूर्ण
			ग_लिखोl(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_STS);
		पूर्ण

		ग_लिखोl(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_EN);
	पूर्ण अन्यथा अणु
		ग_लिखोl(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_DIS);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);
	अचिन्हित दीर्घ alarm_समय;

	alarm_समय = rtc_पंचांग_to_समय64(&alrm->समय);

	ग_लिखोl((u32)alarm_समय, (xrtcdev->reg_base + RTC_ALRM));

	xlnx_rtc_alarm_irq_enable(dev, alrm->enabled);

	वापस 0;
पूर्ण

अटल व्योम xlnx_init_rtc(काष्ठा xlnx_rtc_dev *xrtcdev)
अणु
	u32 rtc_ctrl;

	/* Enable RTC चयन to battery when VCC_PSAUX is not available */
	rtc_ctrl = पढ़ोl(xrtcdev->reg_base + RTC_CTRL);
	rtc_ctrl |= RTC_BATT_EN;
	ग_लिखोl(rtc_ctrl, xrtcdev->reg_base + RTC_CTRL);

	/*
	 * Based on crystal freq of 33.330 KHz
	 * set the seconds counter and enable, set fractions counter
	 * to शेष value suggested as per design spec
	 * to correct RTC delay in frequency over period of समय.
	 */
	xrtcdev->calibval &= RTC_CALIB_MASK;
	ग_लिखोl(xrtcdev->calibval, (xrtcdev->reg_base + RTC_CALIB_WR));
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops xlnx_rtc_ops = अणु
	.set_समय	  = xlnx_rtc_set_समय,
	.पढ़ो_समय	  = xlnx_rtc_पढ़ो_समय,
	.पढ़ो_alarm	  = xlnx_rtc_पढ़ो_alarm,
	.set_alarm	  = xlnx_rtc_set_alarm,
	.alarm_irq_enable = xlnx_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t xlnx_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = (काष्ठा xlnx_rtc_dev *)id;
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(xrtcdev->reg_base + RTC_INT_STS);
	/* Check अगर पूर्णांकerrupt निश्चितed */
	अगर (!(status & (RTC_INT_SEC | RTC_INT_ALRM)))
		वापस IRQ_NONE;

	/* Disable RTC_INT_ALRM पूर्णांकerrupt only */
	ग_लिखोl(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_DIS);

	अगर (status & RTC_INT_ALRM)
		rtc_update_irq(xrtcdev->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xlnx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev;
	पूर्णांक ret;

	xrtcdev = devm_kzalloc(&pdev->dev, माप(*xrtcdev), GFP_KERNEL);
	अगर (!xrtcdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, xrtcdev);

	xrtcdev->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(xrtcdev->rtc))
		वापस PTR_ERR(xrtcdev->rtc);

	xrtcdev->rtc->ops = &xlnx_rtc_ops;
	xrtcdev->rtc->range_max = U32_MAX;

	xrtcdev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xrtcdev->reg_base))
		वापस PTR_ERR(xrtcdev->reg_base);

	xrtcdev->alarm_irq = platक्रमm_get_irq_byname(pdev, "alarm");
	अगर (xrtcdev->alarm_irq < 0)
		वापस xrtcdev->alarm_irq;
	ret = devm_request_irq(&pdev->dev, xrtcdev->alarm_irq,
			       xlnx_rtc_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), xrtcdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request irq failed\n");
		वापस ret;
	पूर्ण

	xrtcdev->sec_irq = platक्रमm_get_irq_byname(pdev, "sec");
	अगर (xrtcdev->sec_irq < 0)
		वापस xrtcdev->sec_irq;
	ret = devm_request_irq(&pdev->dev, xrtcdev->sec_irq,
			       xlnx_rtc_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), xrtcdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request irq failed\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "calibration",
				   &xrtcdev->calibval);
	अगर (ret)
		xrtcdev->calibval = RTC_CALIB_DEF;

	xlnx_init_rtc(xrtcdev);

	device_init_wakeup(&pdev->dev, 1);

	वापस devm_rtc_रेजिस्टर_device(xrtcdev->rtc);
पूर्ण

अटल पूर्णांक xlnx_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	xlnx_rtc_alarm_irq_enable(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xlnx_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(xrtcdev->alarm_irq);
	अन्यथा
		xlnx_rtc_alarm_irq_enable(dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xlnx_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(xrtcdev->alarm_irq);
	अन्यथा
		xlnx_rtc_alarm_irq_enable(dev, 1);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(xlnx_rtc_pm_ops, xlnx_rtc_suspend, xlnx_rtc_resume);

अटल स्थिर काष्ठा of_device_id xlnx_rtc_of_match[] = अणु
	अणु.compatible = "xlnx,zynqmp-rtc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xlnx_rtc_of_match);

अटल काष्ठा platक्रमm_driver xlnx_rtc_driver = अणु
	.probe		= xlnx_rtc_probe,
	.हटाओ		= xlnx_rtc_हटाओ,
	.driver		= अणु
		.name	= KBUILD_MODNAME,
		.pm	= &xlnx_rtc_pm_ops,
		.of_match_table	= xlnx_rtc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xlnx_rtc_driver);

MODULE_DESCRIPTION("Xilinx Zynq MPSoC RTC driver");
MODULE_AUTHOR("Xilinx Inc.");
MODULE_LICENSE("GPL v2");
