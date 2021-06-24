<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Oleksij Rempel <linux@rempel-privat.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

/* Miscellaneous रेजिस्टरs */
/* Interrupt Location Register */
#घोषणा HW_ILR			0x00
#घोषणा BM_RTCALF		BIT(1)
#घोषणा BM_RTCCIF		BIT(0)

/* Clock Control Register */
#घोषणा HW_CCR			0x08
/* Calibration counter disable */
#घोषणा BM_CCALOFF		BIT(4)
/* Reset पूर्णांकernal oscillator भागider */
#घोषणा BM_CTCRST		BIT(1)
/* Clock Enable */
#घोषणा BM_CLKEN		BIT(0)

/* Counter Increment Interrupt Register */
#घोषणा HW_CIIR			0x0C
#घोषणा BM_CIIR_IMYEAR		BIT(7)
#घोषणा BM_CIIR_IMMON		BIT(6)
#घोषणा BM_CIIR_IMDOY		BIT(5)
#घोषणा BM_CIIR_IMDOW		BIT(4)
#घोषणा BM_CIIR_IMDOM		BIT(3)
#घोषणा BM_CIIR_IMHOUR		BIT(2)
#घोषणा BM_CIIR_IMMIN		BIT(1)
#घोषणा BM_CIIR_IMSEC		BIT(0)

/* Alarm Mask Register */
#घोषणा HW_AMR			0x10
#घोषणा BM_AMR_IMYEAR		BIT(7)
#घोषणा BM_AMR_IMMON		BIT(6)
#घोषणा BM_AMR_IMDOY		BIT(5)
#घोषणा BM_AMR_IMDOW		BIT(4)
#घोषणा BM_AMR_IMDOM		BIT(3)
#घोषणा BM_AMR_IMHOUR		BIT(2)
#घोषणा BM_AMR_IMMIN		BIT(1)
#घोषणा BM_AMR_IMSEC		BIT(0)
#घोषणा BM_AMR_OFF		0xff

/* Consolidated समय रेजिस्टरs */
#घोषणा HW_CTIME0		0x14
#घोषणा BM_CTIME0_DOW_S		24
#घोषणा BM_CTIME0_DOW_M		0x7
#घोषणा BM_CTIME0_HOUR_S	16
#घोषणा BM_CTIME0_HOUR_M	0x1f
#घोषणा BM_CTIME0_MIN_S		8
#घोषणा BM_CTIME0_MIN_M		0x3f
#घोषणा BM_CTIME0_SEC_S		0
#घोषणा BM_CTIME0_SEC_M		0x3f

#घोषणा HW_CTIME1		0x18
#घोषणा BM_CTIME1_YEAR_S	16
#घोषणा BM_CTIME1_YEAR_M	0xfff
#घोषणा BM_CTIME1_MON_S		8
#घोषणा BM_CTIME1_MON_M		0xf
#घोषणा BM_CTIME1_DOM_S		0
#घोषणा BM_CTIME1_DOM_M		0x1f

#घोषणा HW_CTIME2		0x1C
#घोषणा BM_CTIME2_DOY_S		0
#घोषणा BM_CTIME2_DOY_M		0xfff

/* Time counter रेजिस्टरs */
#घोषणा HW_SEC			0x20
#घोषणा HW_MIN			0x24
#घोषणा HW_HOUR			0x28
#घोषणा HW_DOM			0x2C
#घोषणा HW_DOW			0x30
#घोषणा HW_DOY			0x34
#घोषणा HW_MONTH		0x38
#घोषणा HW_YEAR			0x3C

#घोषणा HW_CALIBRATION		0x40
#घोषणा BM_CALसूची_BACK		BIT(17)
#घोषणा BM_CALVAL_M		0x1ffff

/* General purpose रेजिस्टरs */
#घोषणा HW_GPREG0		0x44
#घोषणा HW_GPREG1		0x48
#घोषणा HW_GPREG2		0x4C
#घोषणा HW_GPREG3		0x50
#घोषणा HW_GPREG4		0x54

/* Alarm रेजिस्टर group */
#घोषणा HW_ALSEC		0x60
#घोषणा HW_ALMIN		0x64
#घोषणा HW_ALHOUR		0x68
#घोषणा HW_ALDOM		0x6C
#घोषणा HW_ALDOW		0x70
#घोषणा HW_ALDOY		0x74
#घोषणा HW_ALMON		0x78
#घोषणा HW_ALYEAR		0x7C

काष्ठा यंत्र9260_rtc_priv अणु
	काष्ठा device		*dev;
	व्योम __iomem		*iobase;
	काष्ठा rtc_device	*rtc;
	काष्ठा clk		*clk;
पूर्ण;

अटल irqवापस_t यंत्र9260_rtc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = dev_id;
	u32 isr;
	अचिन्हित दीर्घ events = 0;

	rtc_lock(priv->rtc);
	isr = ioपढ़ो32(priv->iobase + HW_CIIR);
	अगर (!isr) अणु
		rtc_unlock(priv->rtc);
		वापस IRQ_NONE;
	पूर्ण

	ioग_लिखो32(0, priv->iobase + HW_CIIR);
	rtc_unlock(priv->rtc);

	events |= RTC_AF | RTC_IRQF;

	rtc_update_irq(priv->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक यंत्र9260_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = dev_get_drvdata(dev);
	u32 स_समय0, स_समय1, स_समय2;

	स_समय0 = ioपढ़ो32(priv->iobase + HW_CTIME0);
	स_समय1 = ioपढ़ो32(priv->iobase + HW_CTIME1);
	स_समय2 = ioपढ़ो32(priv->iobase + HW_CTIME2);

	अगर (स_समय1 != ioपढ़ो32(priv->iobase + HW_CTIME1)) अणु
		/*
		 * woops, counter flipped right now. Now we are safe
		 * to reपढ़ो.
		 */
		स_समय0 = ioपढ़ो32(priv->iobase + HW_CTIME0);
		स_समय1 = ioपढ़ो32(priv->iobase + HW_CTIME1);
		स_समय2 = ioपढ़ो32(priv->iobase + HW_CTIME2);
	पूर्ण

	पंचांग->पंचांग_sec  = (स_समय0 >> BM_CTIME0_SEC_S)  & BM_CTIME0_SEC_M;
	पंचांग->पंचांग_min  = (स_समय0 >> BM_CTIME0_MIN_S)  & BM_CTIME0_MIN_M;
	पंचांग->पंचांग_hour = (स_समय0 >> BM_CTIME0_HOUR_S) & BM_CTIME0_HOUR_M;
	पंचांग->पंचांग_wday = (स_समय0 >> BM_CTIME0_DOW_S)  & BM_CTIME0_DOW_M;

	पंचांग->पंचांग_mday = (स_समय1 >> BM_CTIME1_DOM_S)  & BM_CTIME1_DOM_M;
	पंचांग->पंचांग_mon  = (स_समय1 >> BM_CTIME1_MON_S)  & BM_CTIME1_MON_M;
	पंचांग->पंचांग_year = (स_समय1 >> BM_CTIME1_YEAR_S) & BM_CTIME1_YEAR_M;

	पंचांग->पंचांग_yday = (स_समय2 >> BM_CTIME2_DOY_S)  & BM_CTIME2_DOY_M;

	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = dev_get_drvdata(dev);

	/*
	 * make sure SEC counter will not flip other counter on ग_लिखो समय,
	 * real value will be written at the enf of sequence.
	 */
	ioग_लिखो32(0, priv->iobase + HW_SEC);

	ioग_लिखो32(पंचांग->पंचांग_year, priv->iobase + HW_YEAR);
	ioग_लिखो32(पंचांग->पंचांग_mon,  priv->iobase + HW_MONTH);
	ioग_लिखो32(पंचांग->पंचांग_mday, priv->iobase + HW_DOM);
	ioग_लिखो32(पंचांग->पंचांग_wday, priv->iobase + HW_DOW);
	ioग_लिखो32(पंचांग->पंचांग_yday, priv->iobase + HW_DOY);
	ioग_लिखो32(पंचांग->पंचांग_hour, priv->iobase + HW_HOUR);
	ioग_लिखो32(पंचांग->पंचांग_min,  priv->iobase + HW_MIN);
	ioग_लिखो32(पंचांग->पंचांग_sec,  priv->iobase + HW_SEC);

	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = dev_get_drvdata(dev);

	alrm->समय.पंचांग_year = ioपढ़ो32(priv->iobase + HW_ALYEAR);
	alrm->समय.पंचांग_mon  = ioपढ़ो32(priv->iobase + HW_ALMON);
	alrm->समय.पंचांग_mday = ioपढ़ो32(priv->iobase + HW_ALDOM);
	alrm->समय.पंचांग_wday = ioपढ़ो32(priv->iobase + HW_ALDOW);
	alrm->समय.पंचांग_yday = ioपढ़ो32(priv->iobase + HW_ALDOY);
	alrm->समय.पंचांग_hour = ioपढ़ो32(priv->iobase + HW_ALHOUR);
	alrm->समय.पंचांग_min  = ioपढ़ो32(priv->iobase + HW_ALMIN);
	alrm->समय.पंचांग_sec  = ioपढ़ो32(priv->iobase + HW_ALSEC);

	alrm->enabled = ioपढ़ो32(priv->iobase + HW_AMR) ? 1 : 0;
	alrm->pending = ioपढ़ो32(priv->iobase + HW_CIIR) ? 1 : 0;

	वापस rtc_valid_पंचांग(&alrm->समय);
पूर्ण

अटल पूर्णांक यंत्र9260_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = dev_get_drvdata(dev);

	ioग_लिखो32(alrm->समय.पंचांग_year, priv->iobase + HW_ALYEAR);
	ioग_लिखो32(alrm->समय.पंचांग_mon,  priv->iobase + HW_ALMON);
	ioग_लिखो32(alrm->समय.पंचांग_mday, priv->iobase + HW_ALDOM);
	ioग_लिखो32(alrm->समय.पंचांग_wday, priv->iobase + HW_ALDOW);
	ioग_लिखो32(alrm->समय.पंचांग_yday, priv->iobase + HW_ALDOY);
	ioग_लिखो32(alrm->समय.पंचांग_hour, priv->iobase + HW_ALHOUR);
	ioग_लिखो32(alrm->समय.पंचांग_min,  priv->iobase + HW_ALMIN);
	ioग_लिखो32(alrm->समय.पंचांग_sec,  priv->iobase + HW_ALSEC);

	ioग_लिखो32(alrm->enabled ? 0 : BM_AMR_OFF, priv->iobase + HW_AMR);

	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = dev_get_drvdata(dev);

	ioग_लिखो32(enabled ? 0 : BM_AMR_OFF, priv->iobase + HW_AMR);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops यंत्र9260_rtc_ops = अणु
	.पढ़ो_समय		= यंत्र9260_rtc_पढ़ो_समय,
	.set_समय		= यंत्र9260_rtc_set_समय,
	.पढ़ो_alarm		= यंत्र9260_rtc_पढ़ो_alarm,
	.set_alarm		= यंत्र9260_rtc_set_alarm,
	.alarm_irq_enable	= यंत्र9260_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक यंत्र9260_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq_alarm, ret;
	u32 ccr;

	priv = devm_kzalloc(dev, माप(काष्ठा यंत्र9260_rtc_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, priv);

	irq_alarm = platक्रमm_get_irq(pdev, 0);
	अगर (irq_alarm < 0)
		वापस irq_alarm;

	priv->iobase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->iobase))
		वापस PTR_ERR(priv->iobase);

	priv->clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clk!\n");
		वापस ret;
	पूर्ण

	ccr = ioपढ़ो32(priv->iobase + HW_CCR);
	/* अगर dev is not enabled, reset it */
	अगर ((ccr & (BM_CLKEN | BM_CTCRST)) != BM_CLKEN) अणु
		ioग_लिखो32(BM_CTCRST, priv->iobase + HW_CCR);
		ccr = 0;
	पूर्ण

	ioग_लिखो32(BM_CLKEN | ccr, priv->iobase + HW_CCR);
	ioग_लिखो32(0, priv->iobase + HW_CIIR);
	ioग_लिखो32(BM_AMR_OFF, priv->iobase + HW_AMR);

	priv->rtc = devm_rtc_device_रेजिस्टर(dev, dev_name(dev),
					     &यंत्र9260_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(priv->rtc)) अणु
		ret = PTR_ERR(priv->rtc);
		dev_err(dev, "Failed to register RTC device: %d\n", ret);
		जाओ err_वापस;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq_alarm, शून्य,
					यंत्र9260_rtc_irq, IRQF_ONESHOT,
					dev_name(dev), priv);
	अगर (ret < 0) अणु
		dev_err(dev, "can't get irq %i, err %d\n",
			irq_alarm, ret);
		जाओ err_वापस;
	पूर्ण

	वापस 0;

err_वापस:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक यंत्र9260_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा यंत्र9260_rtc_priv *priv = platक्रमm_get_drvdata(pdev);

	/* Disable alarm matching */
	ioग_लिखो32(BM_AMR_OFF, priv->iobase + HW_AMR);
	clk_disable_unprepare(priv->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id यंत्र9260_dt_ids[] = अणु
	अणु .compatible = "alphascale,asm9260-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, यंत्र9260_dt_ids);

अटल काष्ठा platक्रमm_driver यंत्र9260_rtc_driver = अणु
	.probe		= यंत्र9260_rtc_probe,
	.हटाओ		= यंत्र9260_rtc_हटाओ,
	.driver		= अणु
		.name	= "asm9260-rtc",
		.of_match_table = यंत्र9260_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(यंत्र9260_rtc_driver);

MODULE_AUTHOR("Oleksij Rempel <linux@rempel-privat.de>");
MODULE_DESCRIPTION("Alphascale asm9260 SoC Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL");
