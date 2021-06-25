<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock (RTC) Driver क्रम i.MX53
 * Copyright (c) 2004-2011 Freescale Semiconductor, Inc.
 * Copyright (c) 2017 Beckhoff Automation GmbH & Co. KG
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/rtc.h>

#घोषणा SRTC_LPPDR_INIT       0x41736166	/* init क्रम glitch detect */

#घोषणा SRTC_LPCR_EN_LP       BIT(3)	/* lp enable */
#घोषणा SRTC_LPCR_WAE         BIT(4)	/* lp wakeup alarm enable */
#घोषणा SRTC_LPCR_ALP         BIT(7)	/* lp alarm flag */
#घोषणा SRTC_LPCR_NSA         BIT(11)	/* lp non secure access */
#घोषणा SRTC_LPCR_NVE         BIT(14)	/* lp non valid state निकास bit */
#घोषणा SRTC_LPCR_IE          BIT(15)	/* lp init state निकास bit */

#घोषणा SRTC_LPSR_ALP         BIT(3)	/* lp alarm flag */
#घोषणा SRTC_LPSR_NVES        BIT(14)	/* lp non-valid state निकास status */
#घोषणा SRTC_LPSR_IES         BIT(15)	/* lp init state निकास status */

#घोषणा SRTC_LPSCMR	0x00	/* LP Secure Counter MSB Reg */
#घोषणा SRTC_LPSCLR	0x04	/* LP Secure Counter LSB Reg */
#घोषणा SRTC_LPSAR	0x08	/* LP Secure Alarm Reg */
#घोषणा SRTC_LPCR	0x10	/* LP Control Reg */
#घोषणा SRTC_LPSR	0x14	/* LP Status Reg */
#घोषणा SRTC_LPPDR	0x18	/* LP Power Supply Glitch Detector Reg */

/* max. number of retries to पढ़ो रेजिस्टरs, 120 was max during test */
#घोषणा REG_READ_TIMEOUT 2000

काष्ठा mxc_rtc_data अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;
	काष्ठा clk *clk;
	spinlock_t lock; /* protects रेजिस्टर access */
	पूर्णांक irq;
पूर्ण;

/*
 * This function करोes ग_लिखो synchronization क्रम ग_लिखोs to the lp srtc block.
 * To take care of the asynchronous CKIL घड़ी, all ग_लिखोs from the IP करोमुख्य
 * will be synchronized to the CKIL करोमुख्य.
 * The caller should hold the pdata->lock
 */
अटल व्योम mxc_rtc_sync_lp_locked(काष्ठा device *dev, व्योम __iomem *ioaddr)
अणु
	अचिन्हित पूर्णांक i;

	/* Wait क्रम 3 CKIL cycles */
	क्रम (i = 0; i < 3; i++) अणु
		स्थिर u32 count = पढ़ोl(ioaddr + SRTC_LPSCLR);
		अचिन्हित पूर्णांक समयout = REG_READ_TIMEOUT;

		जबतक ((पढ़ोl(ioaddr + SRTC_LPSCLR)) == count) अणु
			अगर (!--समयout) अणु
				dev_err_once(dev, "SRTC_LPSCLR stuck! Check your hw.\n");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* This function is the RTC पूर्णांकerrupt service routine. */
अटल irqवापस_t mxc_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा device *dev = dev_id;
	काष्ठा mxc_rtc_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	u32 lp_status;
	u32 lp_cr;

	spin_lock(&pdata->lock);
	अगर (clk_enable(pdata->clk)) अणु
		spin_unlock(&pdata->lock);
		वापस IRQ_NONE;
	पूर्ण

	lp_status = पढ़ोl(ioaddr + SRTC_LPSR);
	lp_cr = पढ़ोl(ioaddr + SRTC_LPCR);

	/* update irq data & counter */
	अगर (lp_status & SRTC_LPSR_ALP) अणु
		अगर (lp_cr & SRTC_LPCR_ALP)
			rtc_update_irq(pdata->rtc, 1, RTC_AF | RTC_IRQF);

		/* disable further lp alarm पूर्णांकerrupts */
		lp_cr &= ~(SRTC_LPCR_ALP | SRTC_LPCR_WAE);
	पूर्ण

	/* Update पूर्णांकerrupt enables */
	ग_लिखोl(lp_cr, ioaddr + SRTC_LPCR);

	/* clear पूर्णांकerrupt status */
	ग_लिखोl(lp_status, ioaddr + SRTC_LPSR);

	mxc_rtc_sync_lp_locked(dev, ioaddr);
	clk_disable(pdata->clk);
	spin_unlock(&pdata->lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Enable clk and aquire spinlock
 * @वापस  0 अगर successful; non-zero otherwise.
 */
अटल पूर्णांक mxc_rtc_lock(काष्ठा mxc_rtc_data *स्थिर pdata)
अणु
	पूर्णांक ret;

	spin_lock_irq(&pdata->lock);
	ret = clk_enable(pdata->clk);
	अगर (ret) अणु
		spin_unlock_irq(&pdata->lock);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxc_rtc_unlock(काष्ठा mxc_rtc_data *स्थिर pdata)
अणु
	clk_disable(pdata->clk);
	spin_unlock_irq(&pdata->lock);
	वापस 0;
पूर्ण

/*
 * This function पढ़ोs the current RTC समय पूर्णांकo पंचांग in Gregorian date.
 *
 * @param  पंचांग           contains the RTC समय value upon वापस
 *
 * @वापस  0 अगर successful; non-zero otherwise.
 */
अटल पूर्णांक mxc_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mxc_rtc_data *pdata = dev_get_drvdata(dev);
	स्थिर पूर्णांक clk_failed = clk_enable(pdata->clk);

	अगर (!clk_failed) अणु
		स्थिर समय64_t now = पढ़ोl(pdata->ioaddr + SRTC_LPSCMR);

		rtc_समय64_to_पंचांग(now, पंचांग);
		clk_disable(pdata->clk);
		वापस 0;
	पूर्ण
	वापस clk_failed;
पूर्ण

/*
 * This function sets the पूर्णांकernal RTC समय based on पंचांग in Gregorian date.
 *
 * @param  पंचांग           the समय value to be set in the RTC
 *
 * @वापस  0 अगर successful; non-zero otherwise.
 */
अटल पूर्णांक mxc_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mxc_rtc_data *pdata = dev_get_drvdata(dev);
	समय64_t समय = rtc_पंचांग_to_समय64(पंचांग);
	पूर्णांक ret;

	ret = mxc_rtc_lock(pdata);
	अगर (ret)
		वापस ret;

	ग_लिखोl(समय, pdata->ioaddr + SRTC_LPSCMR);
	mxc_rtc_sync_lp_locked(dev, pdata->ioaddr);
	वापस mxc_rtc_unlock(pdata);
पूर्ण

/*
 * This function पढ़ोs the current alarm value पूर्णांकo the passed in \म alrm
 * argument. It updates the \म alrm's pending field value based on the whether
 * an alarm पूर्णांकerrupt occurs or not.
 *
 * @param  alrm         contains the RTC alarm value upon वापस
 *
 * @वापस  0 अगर successful; non-zero otherwise.
 */
अटल पूर्णांक mxc_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा mxc_rtc_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr;
	पूर्णांक ret;

	ret = mxc_rtc_lock(pdata);
	अगर (ret)
		वापस ret;

	rtc_समय64_to_पंचांग(पढ़ोl(ioaddr + SRTC_LPSAR), &alrm->समय);
	alrm->pending = !!(पढ़ोl(ioaddr + SRTC_LPSR) & SRTC_LPSR_ALP);
	वापस mxc_rtc_unlock(pdata);
पूर्ण

/*
 * Enable/Disable alarm पूर्णांकerrupt
 * The caller should hold the pdata->lock
 */
अटल व्योम mxc_rtc_alarm_irq_enable_locked(काष्ठा mxc_rtc_data *pdata,
					    अचिन्हित पूर्णांक enable)
अणु
	u32 lp_cr = पढ़ोl(pdata->ioaddr + SRTC_LPCR);

	अगर (enable)
		lp_cr |= (SRTC_LPCR_ALP | SRTC_LPCR_WAE);
	अन्यथा
		lp_cr &= ~(SRTC_LPCR_ALP | SRTC_LPCR_WAE);

	ग_लिखोl(lp_cr, pdata->ioaddr + SRTC_LPCR);
पूर्ण

अटल पूर्णांक mxc_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा mxc_rtc_data *pdata = dev_get_drvdata(dev);
	पूर्णांक ret = mxc_rtc_lock(pdata);

	अगर (ret)
		वापस ret;

	mxc_rtc_alarm_irq_enable_locked(pdata, enable);
	वापस mxc_rtc_unlock(pdata);
पूर्ण

/*
 * This function sets the RTC alarm based on passed in alrm.
 *
 * @param  alrm         the alarm value to be set in the RTC
 *
 * @वापस  0 अगर successful; non-zero otherwise.
 */
अटल पूर्णांक mxc_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	स्थिर समय64_t समय = rtc_पंचांग_to_समय64(&alrm->समय);
	काष्ठा mxc_rtc_data *pdata = dev_get_drvdata(dev);
	पूर्णांक ret = mxc_rtc_lock(pdata);

	अगर (ret)
		वापस ret;

	ग_लिखोl((u32)समय, pdata->ioaddr + SRTC_LPSAR);

	/* clear alarm पूर्णांकerrupt status bit */
	ग_लिखोl(SRTC_LPSR_ALP, pdata->ioaddr + SRTC_LPSR);
	mxc_rtc_sync_lp_locked(dev, pdata->ioaddr);

	mxc_rtc_alarm_irq_enable_locked(pdata, alrm->enabled);
	mxc_rtc_sync_lp_locked(dev, pdata->ioaddr);
	mxc_rtc_unlock(pdata);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mxc_rtc_ops = अणु
	.पढ़ो_समय = mxc_rtc_पढ़ो_समय,
	.set_समय = mxc_rtc_set_समय,
	.पढ़ो_alarm = mxc_rtc_पढ़ो_alarm,
	.set_alarm = mxc_rtc_set_alarm,
	.alarm_irq_enable = mxc_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक mxc_rtc_रुको_क्रम_flag(व्योम __iomem *ioaddr, पूर्णांक flag)
अणु
	अचिन्हित पूर्णांक समयout = REG_READ_TIMEOUT;

	जबतक (!(पढ़ोl(ioaddr) & flag)) अणु
		अगर (!--समयout)
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxc_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_rtc_data *pdata;
	व्योम __iomem *ioaddr;
	पूर्णांक ret = 0;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->ioaddr))
		वापस PTR_ERR(pdata->ioaddr);

	ioaddr = pdata->ioaddr;

	pdata->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pdata->clk)) अणु
		dev_err(&pdev->dev, "unable to get rtc clock!\n");
		वापस PTR_ERR(pdata->clk);
	पूर्ण

	spin_lock_init(&pdata->lock);
	pdata->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pdata->irq < 0)
		वापस pdata->irq;

	device_init_wakeup(&pdev->dev, 1);
	ret = dev_pm_set_wake_irq(&pdev->dev, pdata->irq);
	अगर (ret)
		dev_err(&pdev->dev, "failed to enable irq wake\n");

	ret = clk_prepare_enable(pdata->clk);
	अगर (ret)
		वापस ret;
	/* initialize glitch detect */
	ग_लिखोl(SRTC_LPPDR_INIT, ioaddr + SRTC_LPPDR);

	/* clear lp पूर्णांकerrupt status */
	ग_लिखोl(0xFFFFFFFF, ioaddr + SRTC_LPSR);

	/* move out of init state */
	ग_लिखोl((SRTC_LPCR_IE | SRTC_LPCR_NSA), ioaddr + SRTC_LPCR);
	ret = mxc_rtc_रुको_क्रम_flag(ioaddr + SRTC_LPSR, SRTC_LPSR_IES);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Timeout waiting for SRTC_LPSR_IES\n");
		clk_disable_unprepare(pdata->clk);
		वापस ret;
	पूर्ण

	/* move out of non-valid state */
	ग_लिखोl((SRTC_LPCR_IE | SRTC_LPCR_NVE | SRTC_LPCR_NSA |
		SRTC_LPCR_EN_LP), ioaddr + SRTC_LPCR);
	ret = mxc_rtc_रुको_क्रम_flag(ioaddr + SRTC_LPSR, SRTC_LPSR_NVES);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Timeout waiting for SRTC_LPSR_NVES\n");
		clk_disable_unprepare(pdata->clk);
		वापस ret;
	पूर्ण

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc))
		वापस PTR_ERR(pdata->rtc);

	pdata->rtc->ops = &mxc_rtc_ops;
	pdata->rtc->range_max = U32_MAX;

	clk_disable(pdata->clk);
	platक्रमm_set_drvdata(pdev, pdata);
	ret =
	    devm_request_irq(&pdev->dev, pdata->irq, mxc_rtc_पूर्णांकerrupt, 0,
			     pdev->name, &pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "interrupt not available.\n");
		clk_unprepare(pdata->clk);
		वापस ret;
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(pdata->rtc);
	अगर (ret < 0)
		clk_unprepare(pdata->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mxc_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_rtc_data *pdata = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(pdata->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxc_ids[] = अणु
	अणु .compatible = "fsl,imx53-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mxc_rtc_driver = अणु
	.driver = अणु
		.name = "mxc_rtc_v2",
		.of_match_table = mxc_ids,
	पूर्ण,
	.probe = mxc_rtc_probe,
	.हटाओ = mxc_rtc_हटाओ,
पूर्ण;

module_platक्रमm_driver(mxc_rtc_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Real Time Clock (RTC) Driver for i.MX53");
MODULE_LICENSE("GPL");
