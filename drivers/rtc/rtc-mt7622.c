<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम MediaTek SoC based RTC
 *
 * Copyright (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा MTK_RTC_DEV KBUILD_MODNAME

#घोषणा MTK_RTC_PWRCHK1		0x4
#घोषणा	RTC_PWRCHK1_MAGIC	0xc6

#घोषणा MTK_RTC_PWRCHK2		0x8
#घोषणा	RTC_PWRCHK2_MAGIC	0x9a

#घोषणा MTK_RTC_KEY		0xc
#घोषणा	RTC_KEY_MAGIC		0x59

#घोषणा MTK_RTC_PROT1		0x10
#घोषणा	RTC_PROT1_MAGIC		0xa3

#घोषणा MTK_RTC_PROT2		0x14
#घोषणा	RTC_PROT2_MAGIC		0x57

#घोषणा MTK_RTC_PROT3		0x18
#घोषणा	RTC_PROT3_MAGIC		0x67

#घोषणा MTK_RTC_PROT4		0x1c
#घोषणा	RTC_PROT4_MAGIC		0xd2

#घोषणा MTK_RTC_CTL		0x20
#घोषणा	RTC_RC_STOP		BIT(0)

#घोषणा MTK_RTC_DEBNCE		0x2c
#घोषणा	RTC_DEBNCE_MASK		GENMASK(2, 0)

#घोषणा MTK_RTC_INT		0x30
#घोषणा RTC_INT_AL_STA		BIT(4)

/*
 * Ranges from 0x40 to 0x78 provide RTC समय setup क्रम year, month,
 * day of month, day of week, hour, minute and second.
 */
#घोषणा MTK_RTC_TREG(_t, _f)	(0x40 + (0x4 * (_f)) + ((_t) * 0x20))

#घोषणा MTK_RTC_AL_CTL		0x7c
#घोषणा	RTC_AL_EN		BIT(0)
#घोषणा	RTC_AL_ALL		GENMASK(7, 0)

/*
 * The offset is used in the translation क्रम the year between in काष्ठा
 * rtc_समय and in hardware रेजिस्टर MTK_RTC_TREG(x,MTK_YEA)
 */
#घोषणा MTK_RTC_TM_YR_OFFSET	100

/*
 * The lowest value क्रम the valid पंचांग_year. RTC hardware would take incorrectly
 * पंचांग_year 100 as not a leap year and thus it is also required being excluded
 * from the valid options.
 */
#घोषणा MTK_RTC_TM_YR_L		(MTK_RTC_TM_YR_OFFSET + 1)

/*
 * The most year the RTC can hold is 99 and the next to 99 in year रेजिस्टर
 * would be wraparound to 0, क्रम MT7622.
 */
#घोषणा MTK_RTC_HW_YR_LIMIT	99

/* The highest value क्रम the valid पंचांग_year */
#घोषणा MTK_RTC_TM_YR_H		(MTK_RTC_TM_YR_OFFSET + MTK_RTC_HW_YR_LIMIT)

/* Simple macro helps to check whether the hardware supports the पंचांग_year */
#घोषणा MTK_RTC_TM_YR_VALID(_y)	((_y) >= MTK_RTC_TM_YR_L && \
				 (_y) <= MTK_RTC_TM_YR_H)

/* Types of the function the RTC provides are समय counter and alarm. */
क्रमागत अणु
	MTK_TC,
	MTK_AL,
पूर्ण;

/* Indexes are used क्रम the poपूर्णांकer to relevant रेजिस्टरs in MTK_RTC_TREG */
क्रमागत अणु
	MTK_YEA,
	MTK_MON,
	MTK_DOM,
	MTK_DOW,
	MTK_HOU,
	MTK_MIN,
	MTK_SEC
पूर्ण;

काष्ठा mtk_rtc अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम mtk_w32(काष्ठा mtk_rtc *rtc, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, rtc->base + reg);
पूर्ण

अटल u32 mtk_r32(काष्ठा mtk_rtc *rtc, u32 reg)
अणु
	वापस पढ़ोl_relaxed(rtc->base + reg);
पूर्ण

अटल व्योम mtk_rmw(काष्ठा mtk_rtc *rtc, u32 reg, u32 mask, u32 set)
अणु
	u32 val;

	val = mtk_r32(rtc, reg);
	val &= ~mask;
	val |= set;
	mtk_w32(rtc, reg, val);
पूर्ण

अटल व्योम mtk_set(काष्ठा mtk_rtc *rtc, u32 reg, u32 val)
अणु
	mtk_rmw(rtc, reg, 0, val);
पूर्ण

अटल व्योम mtk_clr(काष्ठा mtk_rtc *rtc, u32 reg, u32 val)
अणु
	mtk_rmw(rtc, reg, val, 0);
पूर्ण

अटल व्योम mtk_rtc_hw_init(काष्ठा mtk_rtc *hw)
अणु
	/* The setup of the init sequence is क्रम allowing RTC got to work */
	mtk_w32(hw, MTK_RTC_PWRCHK1, RTC_PWRCHK1_MAGIC);
	mtk_w32(hw, MTK_RTC_PWRCHK2, RTC_PWRCHK2_MAGIC);
	mtk_w32(hw, MTK_RTC_KEY, RTC_KEY_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT1, RTC_PROT1_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT2, RTC_PROT2_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT3, RTC_PROT3_MAGIC);
	mtk_w32(hw, MTK_RTC_PROT4, RTC_PROT4_MAGIC);
	mtk_rmw(hw, MTK_RTC_DEBNCE, RTC_DEBNCE_MASK, 0);
	mtk_clr(hw, MTK_RTC_CTL, RTC_RC_STOP);
पूर्ण

अटल व्योम mtk_rtc_get_alarm_or_समय(काष्ठा mtk_rtc *hw, काष्ठा rtc_समय *पंचांग,
				      पूर्णांक समय_alarm)
अणु
	u32 year, mon, mday, wday, hour, min, sec;

	/*
	 * Read again until the field of the second is not changed which
	 * ensures all fields in the consistent state. Note that MTK_SEC must
	 * be पढ़ो first. In this way, it guarantees the others reमुख्य not
	 * changed when the results क्रम two MTK_SEC consecutive पढ़ोs are same.
	 */
	करो अणु
		sec = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_SEC));
		min = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_MIN));
		hour = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_HOU));
		wday = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_DOW));
		mday = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_DOM));
		mon = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_MON));
		year = mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_YEA));
	पूर्ण जबतक (sec != mtk_r32(hw, MTK_RTC_TREG(समय_alarm, MTK_SEC)));

	पंचांग->पंचांग_sec  = sec;
	पंचांग->पंचांग_min  = min;
	पंचांग->पंचांग_hour = hour;
	पंचांग->पंचांग_wday = wday;
	पंचांग->पंचांग_mday = mday;
	पंचांग->पंचांग_mon  = mon - 1;

	/* Rebase to the असलolute year which userspace queries */
	पंचांग->पंचांग_year = year + MTK_RTC_TM_YR_OFFSET;
पूर्ण

अटल व्योम mtk_rtc_set_alarm_or_समय(काष्ठा mtk_rtc *hw, काष्ठा rtc_समय *पंचांग,
				      पूर्णांक समय_alarm)
अणु
	u32 year;

	/* Rebase to the relative year which RTC hardware requires */
	year = पंचांग->पंचांग_year - MTK_RTC_TM_YR_OFFSET;

	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_YEA), year);
	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_MON), पंचांग->पंचांग_mon + 1);
	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_DOW), पंचांग->पंचांग_wday);
	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_DOM), पंचांग->पंचांग_mday);
	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_HOU), पंचांग->पंचांग_hour);
	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_MIN), पंचांग->पंचांग_min);
	mtk_w32(hw, MTK_RTC_TREG(समय_alarm, MTK_SEC), पंचांग->पंचांग_sec);
पूर्ण

अटल irqवापस_t mtk_rtc_alarmirq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा mtk_rtc *hw = (काष्ठा mtk_rtc *)id;
	u32 irq_sta;

	irq_sta = mtk_r32(hw, MTK_RTC_INT);
	अगर (irq_sta & RTC_INT_AL_STA) अणु
		/* Stop alarm also implicitly disables the alarm पूर्णांकerrupt */
		mtk_w32(hw, MTK_RTC_AL_CTL, 0);
		rtc_update_irq(hw->rtc, 1, RTC_IRQF | RTC_AF);

		/* Ack alarm पूर्णांकerrupt status */
		mtk_w32(hw, MTK_RTC_INT, RTC_INT_AL_STA);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक mtk_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mtk_rtc *hw = dev_get_drvdata(dev);

	mtk_rtc_get_alarm_or_समय(hw, पंचांग, MTK_TC);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mtk_rtc *hw = dev_get_drvdata(dev);

	अगर (!MTK_RTC_TM_YR_VALID(पंचांग->पंचांग_year))
		वापस -EINVAL;

	/* Stop समय counter beक्रमe setting a new one*/
	mtk_set(hw, MTK_RTC_CTL, RTC_RC_STOP);

	mtk_rtc_set_alarm_or_समय(hw, पंचांग, MTK_TC);

	/* Restart the समय counter */
	mtk_clr(hw, MTK_RTC_CTL, RTC_RC_STOP);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rtc_getalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा mtk_rtc *hw = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alrm_पंचांग = &wkalrm->समय;

	mtk_rtc_get_alarm_or_समय(hw, alrm_पंचांग, MTK_AL);

	wkalrm->enabled = !!(mtk_r32(hw, MTK_RTC_AL_CTL) & RTC_AL_EN);
	wkalrm->pending = !!(mtk_r32(hw, MTK_RTC_INT) & RTC_INT_AL_STA);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा mtk_rtc *hw = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alrm_पंचांग = &wkalrm->समय;

	अगर (!MTK_RTC_TM_YR_VALID(alrm_पंचांग->पंचांग_year))
		वापस -EINVAL;

	/*
	 * Stop the alarm also implicitly including disables पूर्णांकerrupt beक्रमe
	 * setting a new one.
	 */
	mtk_clr(hw, MTK_RTC_AL_CTL, RTC_AL_EN);

	/*
	 * Aव्योम contention between mtk_rtc_setalarm and IRQ handler so that
	 * disabling the पूर्णांकerrupt and aरुकोing क्रम pending IRQ handler to
	 * complete.
	 */
	synchronize_irq(hw->irq);

	mtk_rtc_set_alarm_or_समय(hw, alrm_पंचांग, MTK_AL);

	/* Restart the alarm with the new setup */
	mtk_w32(hw, MTK_RTC_AL_CTL, RTC_AL_ALL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mtk_rtc_ops = अणु
	.पढ़ो_समय		= mtk_rtc_समय_लो,
	.set_समय		= mtk_rtc_समय_रखो,
	.पढ़ो_alarm		= mtk_rtc_getalarm,
	.set_alarm		= mtk_rtc_setalarm,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_rtc_match[] = अणु
	अणु .compatible = "mediatek,mt7622-rtc" पूर्ण,
	अणु .compatible = "mediatek,soc-rtc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_rtc_match);

अटल पूर्णांक mtk_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_rtc *hw;
	पूर्णांक ret;

	hw = devm_kzalloc(&pdev->dev, माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hw);

	hw->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hw->base))
		वापस PTR_ERR(hw->base);

	hw->clk = devm_clk_get(&pdev->dev, "rtc");
	अगर (IS_ERR(hw->clk)) अणु
		dev_err(&pdev->dev, "No clock\n");
		वापस PTR_ERR(hw->clk);
	पूर्ण

	ret = clk_prepare_enable(hw->clk);
	अगर (ret)
		वापस ret;

	hw->irq = platक्रमm_get_irq(pdev, 0);
	अगर (hw->irq < 0) अणु
		ret = hw->irq;
		जाओ err;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, hw->irq, mtk_rtc_alarmirq,
			       0, dev_name(&pdev->dev), hw);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't request IRQ\n");
		जाओ err;
	पूर्ण

	mtk_rtc_hw_init(hw);

	device_init_wakeup(&pdev->dev, true);

	hw->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
					   &mtk_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(hw->rtc)) अणु
		ret = PTR_ERR(hw->rtc);
		dev_err(&pdev->dev, "Unable to register device\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	clk_disable_unprepare(hw->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_rtc *hw = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(hw->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_rtc *hw = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(hw->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_rtc *hw = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(hw->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mtk_rtc_pm_ops, mtk_rtc_suspend, mtk_rtc_resume);

#घोषणा MTK_RTC_PM_OPS (&mtk_rtc_pm_ops)
#अन्यथा	/* CONFIG_PM */
#घोषणा MTK_RTC_PM_OPS शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल काष्ठा platक्रमm_driver mtk_rtc_driver = अणु
	.probe	= mtk_rtc_probe,
	.हटाओ	= mtk_rtc_हटाओ,
	.driver = अणु
		.name = MTK_RTC_DEV,
		.of_match_table = mtk_rtc_match,
		.pm = MTK_RTC_PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_rtc_driver);

MODULE_DESCRIPTION("MediaTek SoC based RTC Driver");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("GPL");
