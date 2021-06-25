<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH On-Chip RTC Support
 *
 * Copyright (C) 2006 - 2009  Paul Mundt
 * Copyright (C) 2006  Jamie Lenehan
 * Copyright (C) 2008  Angelo Castello
 *
 * Based on the old arch/sh/kernel/cpu/rtc.c by:
 *
 *  Copyright (C) 2000  Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 1999  Tetsuya Okada & Niibe Yutaka
 */
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_SUPERH
#समावेश <यंत्र/rtc.h>
#अन्यथा
/* Default values क्रम RZ/A RTC */
#घोषणा rtc_reg_size		माप(u16)
#घोषणा RTC_BIT_INVERTED        0	/* no chip bugs */
#घोषणा RTC_CAP_4_DIGIT_YEAR    (1 << 0)
#घोषणा RTC_DEF_CAPABILITIES    RTC_CAP_4_DIGIT_YEAR
#पूर्ण_अगर

#घोषणा DRV_NAME	"sh-rtc"

#घोषणा RTC_REG(r)	((r) * rtc_reg_size)

#घोषणा R64CNT		RTC_REG(0)

#घोषणा RSECCNT		RTC_REG(1)	/* RTC sec */
#घोषणा RMINCNT		RTC_REG(2)	/* RTC min */
#घोषणा RHRCNT		RTC_REG(3)	/* RTC hour */
#घोषणा RWKCNT		RTC_REG(4)	/* RTC week */
#घोषणा RDAYCNT		RTC_REG(5)	/* RTC day */
#घोषणा RMONCNT		RTC_REG(6)	/* RTC month */
#घोषणा RYRCNT		RTC_REG(7)	/* RTC year */
#घोषणा RSECAR		RTC_REG(8)	/* ALARM sec */
#घोषणा RMINAR		RTC_REG(9)	/* ALARM min */
#घोषणा RHRAR		RTC_REG(10)	/* ALARM hour */
#घोषणा RWKAR		RTC_REG(11)	/* ALARM week */
#घोषणा RDAYAR		RTC_REG(12)	/* ALARM day */
#घोषणा RMONAR		RTC_REG(13)	/* ALARM month */
#घोषणा RCR1		RTC_REG(14)	/* Control */
#घोषणा RCR2		RTC_REG(15)	/* Control */

/*
 * Note on RYRAR and RCR3: Up until this poपूर्णांक most of the रेजिस्टर
 * definitions are consistent across all of the available parts. However,
 * the placement of the optional RYRAR and RCR3 (the RYRAR control
 * रेजिस्टर used to control RYRCNT/RYRAR compare) varies considerably
 * across various parts, occasionally being mapped in to a completely
 * unrelated address space. For proper RYRAR support a separate resource
 * would have to be handed off, but as this is purely optional in
 * practice, we simply opt not to support it, thereby keeping the code
 * quite a bit more simplअगरied.
 */

/* ALARM Bits - or with BCD encoded value */
#घोषणा AR_ENB		0x80	/* Enable क्रम alarm cmp   */

/* Period Bits */
#घोषणा PF_HP		0x100	/* Enable Half Period to support 8,32,128Hz */
#घोषणा PF_COUNT	0x200	/* Half periodic counter */
#घोषणा PF_OXS		0x400	/* Periodic One x Second */
#घोषणा PF_KOU		0x800	/* Kernel or User periodic request 1=kernel */
#घोषणा PF_MASK		0xf00

/* RCR1 Bits */
#घोषणा RCR1_CF		0x80	/* Carry Flag             */
#घोषणा RCR1_CIE	0x10	/* Carry Interrupt Enable */
#घोषणा RCR1_AIE	0x08	/* Alarm Interrupt Enable */
#घोषणा RCR1_AF		0x01	/* Alarm Flag             */

/* RCR2 Bits */
#घोषणा RCR2_PEF	0x80	/* PEriodic पूर्णांकerrupt Flag */
#घोषणा RCR2_PESMASK	0x70	/* Periodic पूर्णांकerrupt Set  */
#घोषणा RCR2_RTCEN	0x08	/* ENable RTC              */
#घोषणा RCR2_ADJ	0x04	/* ADJusपंचांगent (30-second)  */
#घोषणा RCR2_RESET	0x02	/* Reset bit               */
#घोषणा RCR2_START	0x01	/* Start bit               */

काष्ठा sh_rtc अणु
	व्योम __iomem		*regbase;
	अचिन्हित दीर्घ		regsize;
	काष्ठा resource		*res;
	पूर्णांक			alarm_irq;
	पूर्णांक			periodic_irq;
	पूर्णांक			carry_irq;
	काष्ठा clk		*clk;
	काष्ठा rtc_device	*rtc_dev;
	spinlock_t		lock;
	अचिन्हित दीर्घ		capabilities;	/* See यंत्र/rtc.h क्रम cap bits */
	अचिन्हित लघु		periodic_freq;
पूर्ण;

अटल पूर्णांक __sh_rtc_पूर्णांकerrupt(काष्ठा sh_rtc *rtc)
अणु
	अचिन्हित पूर्णांक पंचांगp, pending;

	पंचांगp = पढ़ोb(rtc->regbase + RCR1);
	pending = पंचांगp & RCR1_CF;
	पंचांगp &= ~RCR1_CF;
	ग_लिखोb(पंचांगp, rtc->regbase + RCR1);

	/* Users have requested One x Second IRQ */
	अगर (pending && rtc->periodic_freq & PF_OXS)
		rtc_update_irq(rtc->rtc_dev, 1, RTC_UF | RTC_IRQF);

	वापस pending;
पूर्ण

अटल पूर्णांक __sh_rtc_alarm(काष्ठा sh_rtc *rtc)
अणु
	अचिन्हित पूर्णांक पंचांगp, pending;

	पंचांगp = पढ़ोb(rtc->regbase + RCR1);
	pending = पंचांगp & RCR1_AF;
	पंचांगp &= ~(RCR1_AF | RCR1_AIE);
	ग_लिखोb(पंचांगp, rtc->regbase + RCR1);

	अगर (pending)
		rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);

	वापस pending;
पूर्ण

अटल पूर्णांक __sh_rtc_periodic(काष्ठा sh_rtc *rtc)
अणु
	अचिन्हित पूर्णांक पंचांगp, pending;

	पंचांगp = पढ़ोb(rtc->regbase + RCR2);
	pending = पंचांगp & RCR2_PEF;
	पंचांगp &= ~RCR2_PEF;
	ग_लिखोb(पंचांगp, rtc->regbase + RCR2);

	अगर (!pending)
		वापस 0;

	/* Half period enabled than one skipped and the next notअगरied */
	अगर ((rtc->periodic_freq & PF_HP) && (rtc->periodic_freq & PF_COUNT))
		rtc->periodic_freq &= ~PF_COUNT;
	अन्यथा अणु
		अगर (rtc->periodic_freq & PF_HP)
			rtc->periodic_freq |= PF_COUNT;
		rtc_update_irq(rtc->rtc_dev, 1, RTC_PF | RTC_IRQF);
	पूर्ण

	वापस pending;
पूर्ण

अटल irqवापस_t sh_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_rtc *rtc = dev_id;
	पूर्णांक ret;

	spin_lock(&rtc->lock);
	ret = __sh_rtc_पूर्णांकerrupt(rtc);
	spin_unlock(&rtc->lock);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल irqवापस_t sh_rtc_alarm(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_rtc *rtc = dev_id;
	पूर्णांक ret;

	spin_lock(&rtc->lock);
	ret = __sh_rtc_alarm(rtc);
	spin_unlock(&rtc->lock);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल irqवापस_t sh_rtc_periodic(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_rtc *rtc = dev_id;
	पूर्णांक ret;

	spin_lock(&rtc->lock);
	ret = __sh_rtc_periodic(rtc);
	spin_unlock(&rtc->lock);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल irqवापस_t sh_rtc_shared(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_rtc *rtc = dev_id;
	पूर्णांक ret;

	spin_lock(&rtc->lock);
	ret = __sh_rtc_पूर्णांकerrupt(rtc);
	ret |= __sh_rtc_alarm(rtc);
	ret |= __sh_rtc_periodic(rtc);
	spin_unlock(&rtc->lock);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल अंतरभूत व्योम sh_rtc_setaie(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp;

	spin_lock_irq(&rtc->lock);

	पंचांगp = पढ़ोb(rtc->regbase + RCR1);

	अगर (enable)
		पंचांगp |= RCR1_AIE;
	अन्यथा
		पंचांगp &= ~RCR1_AIE;

	ग_लिखोb(पंचांगp, rtc->regbase + RCR1);

	spin_unlock_irq(&rtc->lock);
पूर्ण

अटल पूर्णांक sh_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = पढ़ोb(rtc->regbase + RCR1);
	seq_म_लिखो(seq, "carry_IRQ\t: %s\n", (पंचांगp & RCR1_CIE) ? "yes" : "no");

	पंचांगp = पढ़ोb(rtc->regbase + RCR2);
	seq_म_लिखो(seq, "periodic_IRQ\t: %s\n",
		   (पंचांगp & RCR2_PESMASK) ? "yes" : "no");

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sh_rtc_setcie(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp;

	spin_lock_irq(&rtc->lock);

	पंचांगp = पढ़ोb(rtc->regbase + RCR1);

	अगर (!enable)
		पंचांगp &= ~RCR1_CIE;
	अन्यथा
		पंचांगp |= RCR1_CIE;

	ग_लिखोb(पंचांगp, rtc->regbase + RCR1);

	spin_unlock_irq(&rtc->lock);
पूर्ण

अटल पूर्णांक sh_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	sh_rtc_setaie(dev, enabled);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक sec128, sec2, yr, yr100, cf_bit;

	अगर (!(पढ़ोb(rtc->regbase + RCR2) & RCR2_RTCEN))
		वापस -EINVAL;

	करो अणु
		अचिन्हित पूर्णांक पंचांगp;

		spin_lock_irq(&rtc->lock);

		पंचांगp = पढ़ोb(rtc->regbase + RCR1);
		पंचांगp &= ~RCR1_CF; /* Clear CF-bit */
		पंचांगp |= RCR1_CIE;
		ग_लिखोb(पंचांगp, rtc->regbase + RCR1);

		sec128 = पढ़ोb(rtc->regbase + R64CNT);

		पंचांग->पंचांग_sec	= bcd2bin(पढ़ोb(rtc->regbase + RSECCNT));
		पंचांग->पंचांग_min	= bcd2bin(पढ़ोb(rtc->regbase + RMINCNT));
		पंचांग->पंचांग_hour	= bcd2bin(पढ़ोb(rtc->regbase + RHRCNT));
		पंचांग->पंचांग_wday	= bcd2bin(पढ़ोb(rtc->regbase + RWKCNT));
		पंचांग->पंचांग_mday	= bcd2bin(पढ़ोb(rtc->regbase + RDAYCNT));
		पंचांग->पंचांग_mon	= bcd2bin(पढ़ोb(rtc->regbase + RMONCNT)) - 1;

		अगर (rtc->capabilities & RTC_CAP_4_DIGIT_YEAR) अणु
			yr  = पढ़ोw(rtc->regbase + RYRCNT);
			yr100 = bcd2bin(yr >> 8);
			yr &= 0xff;
		पूर्ण अन्यथा अणु
			yr  = पढ़ोb(rtc->regbase + RYRCNT);
			yr100 = bcd2bin((yr == 0x99) ? 0x19 : 0x20);
		पूर्ण

		पंचांग->पंचांग_year = (yr100 * 100 + bcd2bin(yr)) - 1900;

		sec2 = पढ़ोb(rtc->regbase + R64CNT);
		cf_bit = पढ़ोb(rtc->regbase + RCR1) & RCR1_CF;

		spin_unlock_irq(&rtc->lock);
	पूर्ण जबतक (cf_bit != 0 || ((sec128 ^ sec2) & RTC_BIT_INVERTED) != 0);

#अगर RTC_BIT_INVERTED != 0
	अगर ((sec128 & RTC_BIT_INVERTED))
		पंचांग->पंचांग_sec--;
#पूर्ण_अगर

	/* only keep the carry पूर्णांकerrupt enabled अगर UIE is on */
	अगर (!(rtc->periodic_freq & PF_OXS))
		sh_rtc_setcie(dev, 0);

	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon + 1, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक year;

	spin_lock_irq(&rtc->lock);

	/* Reset pre-scaler & stop RTC */
	पंचांगp = पढ़ोb(rtc->regbase + RCR2);
	पंचांगp |= RCR2_RESET;
	पंचांगp &= ~RCR2_START;
	ग_लिखोb(पंचांगp, rtc->regbase + RCR2);

	ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec),  rtc->regbase + RSECCNT);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_min),  rtc->regbase + RMINCNT);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), rtc->regbase + RHRCNT);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_wday), rtc->regbase + RWKCNT);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), rtc->regbase + RDAYCNT);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), rtc->regbase + RMONCNT);

	अगर (rtc->capabilities & RTC_CAP_4_DIGIT_YEAR) अणु
		year = (bin2bcd((पंचांग->पंचांग_year + 1900) / 100) << 8) |
			bin2bcd(पंचांग->पंचांग_year % 100);
		ग_लिखोw(year, rtc->regbase + RYRCNT);
	पूर्ण अन्यथा अणु
		year = पंचांग->पंचांग_year % 100;
		ग_लिखोb(bin2bcd(year), rtc->regbase + RYRCNT);
	पूर्ण

	/* Start RTC */
	पंचांगp = पढ़ोb(rtc->regbase + RCR2);
	पंचांगp &= ~RCR2_RESET;
	पंचांगp |= RCR2_RTCEN | RCR2_START;
	ग_लिखोb(पंचांगp, rtc->regbase + RCR2);

	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sh_rtc_पढ़ो_alarm_value(काष्ठा sh_rtc *rtc, पूर्णांक reg_off)
अणु
	अचिन्हित पूर्णांक byte;
	पूर्णांक value = -1;			/* वापस -1 क्रम ignored values */

	byte = पढ़ोb(rtc->regbase + reg_off);
	अगर (byte & AR_ENB) अणु
		byte &= ~AR_ENB;	/* strip the enable bit */
		value = bcd2bin(byte);
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक sh_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &wkalrm->समय;

	spin_lock_irq(&rtc->lock);

	पंचांग->पंचांग_sec	= sh_rtc_पढ़ो_alarm_value(rtc, RSECAR);
	पंचांग->पंचांग_min	= sh_rtc_पढ़ो_alarm_value(rtc, RMINAR);
	पंचांग->पंचांग_hour	= sh_rtc_पढ़ो_alarm_value(rtc, RHRAR);
	पंचांग->पंचांग_wday	= sh_rtc_पढ़ो_alarm_value(rtc, RWKAR);
	पंचांग->पंचांग_mday	= sh_rtc_पढ़ो_alarm_value(rtc, RDAYAR);
	पंचांग->पंचांग_mon	= sh_rtc_पढ़ो_alarm_value(rtc, RMONAR);
	अगर (पंचांग->पंचांग_mon > 0)
		पंचांग->पंचांग_mon -= 1; /* RTC is 1-12, पंचांग_mon is 0-11 */

	wkalrm->enabled = (पढ़ोb(rtc->regbase + RCR1) & RCR1_AIE) ? 1 : 0;

	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sh_rtc_ग_लिखो_alarm_value(काष्ठा sh_rtc *rtc,
					    पूर्णांक value, पूर्णांक reg_off)
अणु
	/* < 0 क्रम a value that is ignored */
	अगर (value < 0)
		ग_लिखोb(0, rtc->regbase + reg_off);
	अन्यथा
		ग_लिखोb(bin2bcd(value) | AR_ENB,  rtc->regbase + reg_off);
पूर्ण

अटल पूर्णांक sh_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक rcr1;
	काष्ठा rtc_समय *पंचांग = &wkalrm->समय;
	पूर्णांक mon;

	spin_lock_irq(&rtc->lock);

	/* disable alarm पूर्णांकerrupt and clear the alarm flag */
	rcr1 = पढ़ोb(rtc->regbase + RCR1);
	rcr1 &= ~(RCR1_AF | RCR1_AIE);
	ग_लिखोb(rcr1, rtc->regbase + RCR1);

	/* set alarm समय */
	sh_rtc_ग_लिखो_alarm_value(rtc, पंचांग->पंचांग_sec,  RSECAR);
	sh_rtc_ग_लिखो_alarm_value(rtc, पंचांग->पंचांग_min,  RMINAR);
	sh_rtc_ग_लिखो_alarm_value(rtc, पंचांग->पंचांग_hour, RHRAR);
	sh_rtc_ग_लिखो_alarm_value(rtc, पंचांग->पंचांग_wday, RWKAR);
	sh_rtc_ग_लिखो_alarm_value(rtc, पंचांग->पंचांग_mday, RDAYAR);
	mon = पंचांग->पंचांग_mon;
	अगर (mon >= 0)
		mon += 1;
	sh_rtc_ग_लिखो_alarm_value(rtc, mon, RMONAR);

	अगर (wkalrm->enabled) अणु
		rcr1 |= RCR1_AIE;
		ग_लिखोb(rcr1, rtc->regbase + RCR1);
	पूर्ण

	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sh_rtc_ops = अणु
	.पढ़ो_समय	= sh_rtc_पढ़ो_समय,
	.set_समय	= sh_rtc_set_समय,
	.पढ़ो_alarm	= sh_rtc_पढ़ो_alarm,
	.set_alarm	= sh_rtc_set_alarm,
	.proc		= sh_rtc_proc,
	.alarm_irq_enable = sh_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक __init sh_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_rtc *rtc;
	काष्ठा resource *res;
	अक्षर clk_name[6];
	पूर्णांक clk_id, ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (unlikely(!rtc))
		वापस -ENOMEM;

	spin_lock_init(&rtc->lock);

	/* get periodic/carry/alarm irqs */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (unlikely(ret <= 0)) अणु
		dev_err(&pdev->dev, "No IRQ resource\n");
		वापस -ENOENT;
	पूर्ण

	rtc->periodic_irq = ret;
	rtc->carry_irq = platक्रमm_get_irq(pdev, 1);
	rtc->alarm_irq = platक्रमm_get_irq(pdev, 2);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(res == शून्य)) अणु
		dev_err(&pdev->dev, "No IO resource\n");
		वापस -ENOENT;
	पूर्ण

	rtc->regsize = resource_size(res);

	rtc->res = devm_request_mem_region(&pdev->dev, res->start,
					rtc->regsize, pdev->name);
	अगर (unlikely(!rtc->res))
		वापस -EBUSY;

	rtc->regbase = devm_ioremap(&pdev->dev, rtc->res->start, rtc->regsize);
	अगर (unlikely(!rtc->regbase))
		वापस -EINVAL;

	अगर (!pdev->dev.of_node) अणु
		clk_id = pdev->id;
		/* With a single device, the घड़ी id is still "rtc0" */
		अगर (clk_id < 0)
			clk_id = 0;

		snम_लिखो(clk_name, माप(clk_name), "rtc%d", clk_id);
	पूर्ण अन्यथा
		snम_लिखो(clk_name, माप(clk_name), "fck");

	rtc->clk = devm_clk_get(&pdev->dev, clk_name);
	अगर (IS_ERR(rtc->clk)) अणु
		/*
		 * No error handling क्रम rtc->clk पूर्णांकentionally, not all
		 * platक्रमms will have a unique घड़ी क्रम the RTC, and
		 * the clk API can handle the काष्ठा clk poपूर्णांकer being
		 * शून्य.
		 */
		rtc->clk = शून्य;
	पूर्ण

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	clk_enable(rtc->clk);

	rtc->capabilities = RTC_DEF_CAPABILITIES;

#अगर_घोषित CONFIG_SUPERH
	अगर (dev_get_platdata(&pdev->dev)) अणु
		काष्ठा sh_rtc_platक्रमm_info *pinfo =
			dev_get_platdata(&pdev->dev);

		/*
		 * Some CPUs have special capabilities in addition to the
		 * शेष set. Add those in here.
		 */
		rtc->capabilities |= pinfo->capabilities;
	पूर्ण
#पूर्ण_अगर

	अगर (rtc->carry_irq <= 0) अणु
		/* रेजिस्टर shared periodic/carry/alarm irq */
		ret = devm_request_irq(&pdev->dev, rtc->periodic_irq,
				sh_rtc_shared, 0, "sh-rtc", rtc);
		अगर (unlikely(ret)) अणु
			dev_err(&pdev->dev,
				"request IRQ failed with %d, IRQ %d\n", ret,
				rtc->periodic_irq);
			जाओ err_unmap;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* रेजिस्टर periodic/carry/alarm irqs */
		ret = devm_request_irq(&pdev->dev, rtc->periodic_irq,
				sh_rtc_periodic, 0, "sh-rtc period", rtc);
		अगर (unlikely(ret)) अणु
			dev_err(&pdev->dev,
				"request period IRQ failed with %d, IRQ %d\n",
				ret, rtc->periodic_irq);
			जाओ err_unmap;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, rtc->carry_irq,
				sh_rtc_पूर्णांकerrupt, 0, "sh-rtc carry", rtc);
		अगर (unlikely(ret)) अणु
			dev_err(&pdev->dev,
				"request carry IRQ failed with %d, IRQ %d\n",
				ret, rtc->carry_irq);
			जाओ err_unmap;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, rtc->alarm_irq,
				sh_rtc_alarm, 0, "sh-rtc alarm", rtc);
		अगर (unlikely(ret)) अणु
			dev_err(&pdev->dev,
				"request alarm IRQ failed with %d, IRQ %d\n",
				ret, rtc->alarm_irq);
			जाओ err_unmap;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc);

	/* everything disabled by शेष */
	sh_rtc_setaie(&pdev->dev, 0);
	sh_rtc_setcie(&pdev->dev, 0);

	rtc->rtc_dev->ops = &sh_rtc_ops;
	rtc->rtc_dev->max_user_freq = 256;

	अगर (rtc->capabilities & RTC_CAP_4_DIGIT_YEAR) अणु
		rtc->rtc_dev->range_min = RTC_TIMESTAMP_BEGIN_1900;
		rtc->rtc_dev->range_max = RTC_TIMESTAMP_END_9999;
	पूर्ण अन्यथा अणु
		rtc->rtc_dev->range_min = स_गढ़ो64(1999, 1, 1, 0, 0, 0);
		rtc->rtc_dev->range_max = स_गढ़ो64(2098, 12, 31, 23, 59, 59);
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
	अगर (ret)
		जाओ err_unmap;

	device_init_wakeup(&pdev->dev, 1);
	वापस 0;

err_unmap:
	clk_disable(rtc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास sh_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_rtc *rtc = platक्रमm_get_drvdata(pdev);

	sh_rtc_setaie(&pdev->dev, 0);
	sh_rtc_setcie(&pdev->dev, 0);

	clk_disable(rtc->clk);

	वापस 0;
पूर्ण

अटल व्योम sh_rtc_set_irq_wake(काष्ठा device *dev, पूर्णांक enabled)
अणु
	काष्ठा sh_rtc *rtc = dev_get_drvdata(dev);

	irq_set_irq_wake(rtc->periodic_irq, enabled);

	अगर (rtc->carry_irq > 0) अणु
		irq_set_irq_wake(rtc->carry_irq, enabled);
		irq_set_irq_wake(rtc->alarm_irq, enabled);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused sh_rtc_suspend(काष्ठा device *dev)
अणु
	अगर (device_may_wakeup(dev))
		sh_rtc_set_irq_wake(dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sh_rtc_resume(काष्ठा device *dev)
अणु
	अगर (device_may_wakeup(dev))
		sh_rtc_set_irq_wake(dev, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sh_rtc_pm_ops, sh_rtc_suspend, sh_rtc_resume);

अटल स्थिर काष्ठा of_device_id sh_rtc_of_match[] = अणु
	अणु .compatible = "renesas,sh-rtc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_rtc_of_match);

अटल काष्ठा platक्रमm_driver sh_rtc_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
		.pm	= &sh_rtc_pm_ops,
		.of_match_table = sh_rtc_of_match,
	पूर्ण,
	.हटाओ		= __निकास_p(sh_rtc_हटाओ),
पूर्ण;

module_platक्रमm_driver_probe(sh_rtc_platक्रमm_driver, sh_rtc_probe);

MODULE_DESCRIPTION("SuperH on-chip RTC driver");
MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>, "
	      "Jamie Lenehan <lenehan@twibble.org>, "
	      "Angelo Castello <angelo.castello@st.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
