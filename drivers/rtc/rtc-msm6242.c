<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Oki MSM6242 RTC Driver
 *
 *  Copyright 2009 Geert Uytterhoeven
 *
 *  Based on the A2000 TOD code in arch/m68k/amiga/config.c
 *  Copyright (C) 1993 Hamish Macकरोnald
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>


क्रमागत अणु
	MSM6242_SECOND1		= 0x0,	/* 1-second digit रेजिस्टर */
	MSM6242_SECOND10	= 0x1,	/* 10-second digit रेजिस्टर */
	MSM6242_MINUTE1		= 0x2,	/* 1-minute digit रेजिस्टर */
	MSM6242_MINUTE10	= 0x3,	/* 10-minute digit रेजिस्टर */
	MSM6242_HOUR1		= 0x4,	/* 1-hour digit रेजिस्टर */
	MSM6242_HOUR10		= 0x5,	/* PM/AM, 10-hour digit रेजिस्टर */
	MSM6242_DAY1		= 0x6,	/* 1-day digit रेजिस्टर */
	MSM6242_DAY10		= 0x7,	/* 10-day digit रेजिस्टर */
	MSM6242_MONTH1		= 0x8,	/* 1-month digit रेजिस्टर */
	MSM6242_MONTH10		= 0x9,	/* 10-month digit रेजिस्टर */
	MSM6242_YEAR1		= 0xa,	/* 1-year digit रेजिस्टर */
	MSM6242_YEAR10		= 0xb,	/* 10-year digit रेजिस्टर */
	MSM6242_WEEK		= 0xc,	/* Week रेजिस्टर */
	MSM6242_CD		= 0xd,	/* Control Register D */
	MSM6242_CE		= 0xe,	/* Control Register E */
	MSM6242_CF		= 0xf,	/* Control Register F */
पूर्ण;

#घोषणा MSM6242_HOUR10_AM	(0 << 2)
#घोषणा MSM6242_HOUR10_PM	(1 << 2)
#घोषणा MSM6242_HOUR10_HR_MASK	(3 << 0)

#घोषणा MSM6242_WEEK_SUNDAY	0
#घोषणा MSM6242_WEEK_MONDAY	1
#घोषणा MSM6242_WEEK_TUESDAY	2
#घोषणा MSM6242_WEEK_WEDNESDAY	3
#घोषणा MSM6242_WEEK_THURSDAY	4
#घोषणा MSM6242_WEEK_FRIDAY	5
#घोषणा MSM6242_WEEK_SATURDAY	6

#घोषणा MSM6242_CD_30_S_ADJ	(1 << 3)	/* 30-second adjusपंचांगent */
#घोषणा MSM6242_CD_IRQ_FLAG	(1 << 2)
#घोषणा MSM6242_CD_BUSY		(1 << 1)
#घोषणा MSM6242_CD_HOLD		(1 << 0)

#घोषणा MSM6242_CE_T_MASK	(3 << 2)
#घोषणा MSM6242_CE_T_64HZ	(0 << 2)	/* period 1/64 second */
#घोषणा MSM6242_CE_T_1HZ	(1 << 2)	/* period 1 second */
#घोषणा MSM6242_CE_T_1MINUTE	(2 << 2)	/* period 1 minute */
#घोषणा MSM6242_CE_T_1HOUR	(3 << 2)	/* period 1 hour */

#घोषणा MSM6242_CE_ITRPT_STND	(1 << 1)
#घोषणा MSM6242_CE_MASK		(1 << 0)	/* STD.P output control */

#घोषणा MSM6242_CF_TEST		(1 << 3)
#घोषणा MSM6242_CF_12H		(0 << 2)
#घोषणा MSM6242_CF_24H		(1 << 2)
#घोषणा MSM6242_CF_STOP		(1 << 1)
#घोषणा MSM6242_CF_REST		(1 << 0)	/* reset */


काष्ठा msm6242_priv अणु
	u32 __iomem *regs;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक msm6242_पढ़ो(काष्ठा msm6242_priv *priv,
				       अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(&priv->regs[reg]) & 0xf;
पूर्ण

अटल अंतरभूत व्योम msm6242_ग_लिखो(काष्ठा msm6242_priv *priv, अचिन्हित पूर्णांक val,
				अचिन्हित पूर्णांक reg)
अणु
	__raw_ग_लिखोl(val, &priv->regs[reg]);
पूर्ण

अटल व्योम msm6242_lock(काष्ठा msm6242_priv *priv)
अणु
	पूर्णांक cnt = 5;

	msm6242_ग_लिखो(priv, MSM6242_CD_HOLD|MSM6242_CD_IRQ_FLAG, MSM6242_CD);

	जबतक ((msm6242_पढ़ो(priv, MSM6242_CD) & MSM6242_CD_BUSY) && cnt) अणु
		msm6242_ग_लिखो(priv, MSM6242_CD_IRQ_FLAG, MSM6242_CD);
		udelay(70);
		msm6242_ग_लिखो(priv, MSM6242_CD_HOLD|MSM6242_CD_IRQ_FLAG, MSM6242_CD);
		cnt--;
	पूर्ण

	अगर (!cnt)
		pr_warn("timed out waiting for RTC (0x%x)\n",
			msm6242_पढ़ो(priv, MSM6242_CD));
पूर्ण

अटल व्योम msm6242_unlock(काष्ठा msm6242_priv *priv)
अणु
	msm6242_ग_लिखो(priv, MSM6242_CD_IRQ_FLAG, MSM6242_CD);
पूर्ण

अटल पूर्णांक msm6242_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा msm6242_priv *priv = dev_get_drvdata(dev);

	msm6242_lock(priv);

	पंचांग->पंचांग_sec  = msm6242_पढ़ो(priv, MSM6242_SECOND10) * 10 +
		      msm6242_पढ़ो(priv, MSM6242_SECOND1);
	पंचांग->पंचांग_min  = msm6242_पढ़ो(priv, MSM6242_MINUTE10) * 10 +
		      msm6242_पढ़ो(priv, MSM6242_MINUTE1);
	पंचांग->पंचांग_hour = (msm6242_पढ़ो(priv, MSM6242_HOUR10) &
		       MSM6242_HOUR10_HR_MASK) * 10 +
		      msm6242_पढ़ो(priv, MSM6242_HOUR1);
	पंचांग->पंचांग_mday = msm6242_पढ़ो(priv, MSM6242_DAY10) * 10 +
		      msm6242_पढ़ो(priv, MSM6242_DAY1);
	पंचांग->पंचांग_wday = msm6242_पढ़ो(priv, MSM6242_WEEK);
	पंचांग->पंचांग_mon  = msm6242_पढ़ो(priv, MSM6242_MONTH10) * 10 +
		      msm6242_पढ़ो(priv, MSM6242_MONTH1) - 1;
	पंचांग->पंचांग_year = msm6242_पढ़ो(priv, MSM6242_YEAR10) * 10 +
		      msm6242_पढ़ो(priv, MSM6242_YEAR1);
	अगर (पंचांग->पंचांग_year <= 69)
		पंचांग->पंचांग_year += 100;

	अगर (!(msm6242_पढ़ो(priv, MSM6242_CF) & MSM6242_CF_24H)) अणु
		अचिन्हित पूर्णांक pm = msm6242_पढ़ो(priv, MSM6242_HOUR10) &
				  MSM6242_HOUR10_PM;
		अगर (!pm && पंचांग->पंचांग_hour == 12)
			पंचांग->पंचांग_hour = 0;
		अन्यथा अगर (pm && पंचांग->पंचांग_hour != 12)
			पंचांग->पंचांग_hour += 12;
	पूर्ण

	msm6242_unlock(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक msm6242_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा msm6242_priv *priv = dev_get_drvdata(dev);

	msm6242_lock(priv);

	msm6242_ग_लिखो(priv, पंचांग->पंचांग_sec / 10, MSM6242_SECOND10);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_sec % 10, MSM6242_SECOND1);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_min / 10, MSM6242_MINUTE10);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_min % 10, MSM6242_MINUTE1);
	अगर (msm6242_पढ़ो(priv, MSM6242_CF) & MSM6242_CF_24H)
		msm6242_ग_लिखो(priv, पंचांग->पंचांग_hour / 10, MSM6242_HOUR10);
	अन्यथा अगर (पंचांग->पंचांग_hour >= 12)
		msm6242_ग_लिखो(priv, MSM6242_HOUR10_PM + (पंचांग->पंचांग_hour - 12) / 10,
			      MSM6242_HOUR10);
	अन्यथा
		msm6242_ग_लिखो(priv, पंचांग->पंचांग_hour / 10, MSM6242_HOUR10);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_hour % 10, MSM6242_HOUR1);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_mday / 10, MSM6242_DAY10);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_mday % 10, MSM6242_DAY1);
	अगर (पंचांग->पंचांग_wday != -1)
		msm6242_ग_लिखो(priv, पंचांग->पंचांग_wday, MSM6242_WEEK);
	msm6242_ग_लिखो(priv, (पंचांग->पंचांग_mon + 1) / 10, MSM6242_MONTH10);
	msm6242_ग_लिखो(priv, (पंचांग->पंचांग_mon + 1) % 10, MSM6242_MONTH1);
	अगर (पंचांग->पंचांग_year >= 100)
		पंचांग->पंचांग_year -= 100;
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_year / 10, MSM6242_YEAR10);
	msm6242_ग_लिखो(priv, पंचांग->पंचांग_year % 10, MSM6242_YEAR1);

	msm6242_unlock(priv);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops msm6242_rtc_ops = अणु
	.पढ़ो_समय	= msm6242_पढ़ो_समय,
	.set_समय	= msm6242_set_समय,
पूर्ण;

अटल पूर्णांक __init msm6242_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा msm6242_priv *priv;
	काष्ठा rtc_device *rtc;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!priv->regs)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "rtc-msm6242",
				&msm6242_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	priv->rtc = rtc;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver msm6242_rtc_driver = अणु
	.driver	= अणु
		.name	= "rtc-msm6242",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(msm6242_rtc_driver, msm6242_rtc_probe);

MODULE_AUTHOR("Geert Uytterhoeven <geert@linux-m68k.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Oki MSM6242 RTC driver");
MODULE_ALIAS("platform:rtc-msm6242");
