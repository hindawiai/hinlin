<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RTC driver क्रम the Armada 38x Marvell SoCs
 *
 * Copyright (C) 2015 Marvell
 *
 * Gregory Clement <gregory.clement@मुक्त-electrons.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा RTC_STATUS	    0x0
#घोषणा RTC_STATUS_ALARM1	    BIT(0)
#घोषणा RTC_STATUS_ALARM2	    BIT(1)
#घोषणा RTC_IRQ1_CONF	    0x4
#घोषणा RTC_IRQ2_CONF	    0x8
#घोषणा RTC_IRQ_AL_EN		    BIT(0)
#घोषणा RTC_IRQ_FREQ_EN		    BIT(1)
#घोषणा RTC_IRQ_FREQ_1HZ	    BIT(2)
#घोषणा RTC_CCR		    0x18
#घोषणा RTC_CCR_MODE		    BIT(15)
#घोषणा RTC_CONF_TEST	    0x1C
#घोषणा RTC_NOMINAL_TIMING	    BIT(13)

#घोषणा RTC_TIME	    0xC
#घोषणा RTC_ALARM1	    0x10
#घोषणा RTC_ALARM2	    0x14

/* Armada38x SoC रेजिस्टरs  */
#घोषणा RTC_38X_BRIDGE_TIMING_CTL   0x0
#घोषणा RTC_38X_PERIOD_OFFS		0
#घोषणा RTC_38X_PERIOD_MASK		(0x3FF << RTC_38X_PERIOD_OFFS)
#घोषणा RTC_38X_READ_DELAY_OFFS		26
#घोषणा RTC_38X_READ_DELAY_MASK		(0x1F << RTC_38X_READ_DELAY_OFFS)

/* Armada 7K/8K रेजिस्टरs  */
#घोषणा RTC_8K_BRIDGE_TIMING_CTL0    0x0
#घोषणा RTC_8K_WRCLK_PERIOD_OFFS	0
#घोषणा RTC_8K_WRCLK_PERIOD_MASK	(0xFFFF << RTC_8K_WRCLK_PERIOD_OFFS)
#घोषणा RTC_8K_WRCLK_SETUP_OFFS		16
#घोषणा RTC_8K_WRCLK_SETUP_MASK		(0xFFFF << RTC_8K_WRCLK_SETUP_OFFS)
#घोषणा RTC_8K_BRIDGE_TIMING_CTL1   0x4
#घोषणा RTC_8K_READ_DELAY_OFFS		0
#घोषणा RTC_8K_READ_DELAY_MASK		(0xFFFF << RTC_8K_READ_DELAY_OFFS)

#घोषणा RTC_8K_ISR		    0x10
#घोषणा RTC_8K_IMR		    0x14
#घोषणा RTC_8K_ALARM2			BIT(0)

#घोषणा SOC_RTC_INTERRUPT	    0x8
#घोषणा SOC_RTC_ALARM1			BIT(0)
#घोषणा SOC_RTC_ALARM2			BIT(1)
#घोषणा SOC_RTC_ALARM1_MASK		BIT(2)
#घोषणा SOC_RTC_ALARM2_MASK		BIT(3)

#घोषणा SAMPLE_NR 100

काष्ठा value_to_freq अणु
	u32 value;
	u8 freq;
पूर्ण;

काष्ठा armada38x_rtc अणु
	काष्ठा rtc_device   *rtc_dev;
	व्योम __iomem	    *regs;
	व्योम __iomem	    *regs_soc;
	spinlock_t	    lock;
	पूर्णांक		    irq;
	bool		    initialized;
	काष्ठा value_to_freq *val_to_freq;
	स्थिर काष्ठा armada38x_rtc_data *data;
पूर्ण;

#घोषणा ALARM1	0
#घोषणा ALARM2	1

#घोषणा ALARM_REG(base, alarm)	 ((base) + (alarm) * माप(u32))

काष्ठा armada38x_rtc_data अणु
	/* Initialize the RTC-MBUS bridge timing */
	व्योम (*update_mbus_timing)(काष्ठा armada38x_rtc *rtc);
	u32 (*पढ़ो_rtc_reg)(काष्ठा armada38x_rtc *rtc, u8 rtc_reg);
	व्योम (*clear_isr)(काष्ठा armada38x_rtc *rtc);
	व्योम (*unmask_पूर्णांकerrupt)(काष्ठा armada38x_rtc *rtc);
	u32 alarm;
पूर्ण;

/*
 * According to the datasheet, the OS should रुको 5us after every
 * रेजिस्टर ग_लिखो to the RTC hard macro so that the required update
 * can occur without holding off the प्रणाली bus
 * According to errata RES-3124064, Write to any RTC रेजिस्टर
 * may fail. As a workaround, beक्रमe writing to RTC
 * रेजिस्टर, issue a dummy ग_लिखो of 0x0 twice to RTC Status
 * रेजिस्टर.
 */

अटल व्योम rtc_delayed_ग_लिखो(u32 val, काष्ठा armada38x_rtc *rtc, पूर्णांक offset)
अणु
	ग_लिखोl(0, rtc->regs + RTC_STATUS);
	ग_लिखोl(0, rtc->regs + RTC_STATUS);
	ग_लिखोl(val, rtc->regs + offset);
	udelay(5);
पूर्ण

/* Update RTC-MBUS bridge timing parameters */
अटल व्योम rtc_update_38x_mbus_timing_params(काष्ठा armada38x_rtc *rtc)
अणु
	u32 reg;

	reg = पढ़ोl(rtc->regs_soc + RTC_38X_BRIDGE_TIMING_CTL);
	reg &= ~RTC_38X_PERIOD_MASK;
	reg |= 0x3FF << RTC_38X_PERIOD_OFFS; /* Maximum value */
	reg &= ~RTC_38X_READ_DELAY_MASK;
	reg |= 0x1F << RTC_38X_READ_DELAY_OFFS; /* Maximum value */
	ग_लिखोl(reg, rtc->regs_soc + RTC_38X_BRIDGE_TIMING_CTL);
पूर्ण

अटल व्योम rtc_update_8k_mbus_timing_params(काष्ठा armada38x_rtc *rtc)
अणु
	u32 reg;

	reg = पढ़ोl(rtc->regs_soc + RTC_8K_BRIDGE_TIMING_CTL0);
	reg &= ~RTC_8K_WRCLK_PERIOD_MASK;
	reg |= 0x3FF << RTC_8K_WRCLK_PERIOD_OFFS;
	reg &= ~RTC_8K_WRCLK_SETUP_MASK;
	reg |= 0x29 << RTC_8K_WRCLK_SETUP_OFFS;
	ग_लिखोl(reg, rtc->regs_soc + RTC_8K_BRIDGE_TIMING_CTL0);

	reg = पढ़ोl(rtc->regs_soc + RTC_8K_BRIDGE_TIMING_CTL1);
	reg &= ~RTC_8K_READ_DELAY_MASK;
	reg |= 0x3F << RTC_8K_READ_DELAY_OFFS;
	ग_लिखोl(reg, rtc->regs_soc + RTC_8K_BRIDGE_TIMING_CTL1);
पूर्ण

अटल u32 पढ़ो_rtc_रेजिस्टर(काष्ठा armada38x_rtc *rtc, u8 rtc_reg)
अणु
	वापस पढ़ोl(rtc->regs + rtc_reg);
पूर्ण

अटल u32 पढ़ो_rtc_रेजिस्टर_38x_wa(काष्ठा armada38x_rtc *rtc, u8 rtc_reg)
अणु
	पूर्णांक i, index_max = 0, max = 0;

	क्रम (i = 0; i < SAMPLE_NR; i++) अणु
		rtc->val_to_freq[i].value = पढ़ोl(rtc->regs + rtc_reg);
		rtc->val_to_freq[i].freq = 0;
	पूर्ण

	क्रम (i = 0; i < SAMPLE_NR; i++) अणु
		पूर्णांक j = 0;
		u32 value = rtc->val_to_freq[i].value;

		जबतक (rtc->val_to_freq[j].freq) अणु
			अगर (rtc->val_to_freq[j].value == value) अणु
				rtc->val_to_freq[j].freq++;
				अवरोध;
			पूर्ण
			j++;
		पूर्ण

		अगर (!rtc->val_to_freq[j].freq) अणु
			rtc->val_to_freq[j].value = value;
			rtc->val_to_freq[j].freq = 1;
		पूर्ण

		अगर (rtc->val_to_freq[j].freq > max) अणु
			index_max = j;
			max = rtc->val_to_freq[j].freq;
		पूर्ण

		/*
		 * If a value alपढ़ोy has half of the sample this is the most
		 * frequent one and we can stop the research right now
		 */
		अगर (max > SAMPLE_NR / 2)
			अवरोध;
	पूर्ण

	वापस rtc->val_to_freq[index_max].value;
पूर्ण

अटल व्योम armada38x_clear_isr(काष्ठा armada38x_rtc *rtc)
अणु
	u32 val = पढ़ोl(rtc->regs_soc + SOC_RTC_INTERRUPT);

	ग_लिखोl(val & ~SOC_RTC_ALARM1, rtc->regs_soc + SOC_RTC_INTERRUPT);
पूर्ण

अटल व्योम armada38x_unmask_पूर्णांकerrupt(काष्ठा armada38x_rtc *rtc)
अणु
	u32 val = पढ़ोl(rtc->regs_soc + SOC_RTC_INTERRUPT);

	ग_लिखोl(val | SOC_RTC_ALARM1_MASK, rtc->regs_soc + SOC_RTC_INTERRUPT);
पूर्ण

अटल व्योम armada8k_clear_isr(काष्ठा armada38x_rtc *rtc)
अणु
	ग_लिखोl(RTC_8K_ALARM2, rtc->regs_soc + RTC_8K_ISR);
पूर्ण

अटल व्योम armada8k_unmask_पूर्णांकerrupt(काष्ठा armada38x_rtc *rtc)
अणु
	ग_लिखोl(RTC_8K_ALARM2, rtc->regs_soc + RTC_8K_IMR);
पूर्ण

अटल पूर्णांक armada38x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय, flags;

	spin_lock_irqsave(&rtc->lock, flags);
	समय = rtc->data->पढ़ो_rtc_reg(rtc, RTC_TIME);
	spin_unlock_irqrestore(&rtc->lock, flags);

	rtc_समय64_to_पंचांग(समय, पंचांग);

	वापस 0;
पूर्ण

अटल व्योम armada38x_rtc_reset(काष्ठा armada38x_rtc *rtc)
अणु
	u32 reg;

	reg = rtc->data->पढ़ो_rtc_reg(rtc, RTC_CONF_TEST);
	/* If bits [7:0] are non-zero, assume RTC was uninitialized */
	अगर (reg & 0xff) अणु
		rtc_delayed_ग_लिखो(0, rtc, RTC_CONF_TEST);
		msleep(500); /* Oscillator startup समय */
		rtc_delayed_ग_लिखो(0, rtc, RTC_TIME);
		rtc_delayed_ग_लिखो(SOC_RTC_ALARM1 | SOC_RTC_ALARM2, rtc,
				  RTC_STATUS);
		rtc_delayed_ग_लिखो(RTC_NOMINAL_TIMING, rtc, RTC_CCR);
	पूर्ण
	rtc->initialized = true;
पूर्ण

अटल पूर्णांक armada38x_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय, flags;

	समय = rtc_पंचांग_to_समय64(पंचांग);

	अगर (!rtc->initialized)
		armada38x_rtc_reset(rtc);

	spin_lock_irqsave(&rtc->lock, flags);
	rtc_delayed_ग_लिखो(समय, rtc, RTC_TIME);
	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक armada38x_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय, flags;
	u32 reg = ALARM_REG(RTC_ALARM1, rtc->data->alarm);
	u32 reg_irq = ALARM_REG(RTC_IRQ1_CONF, rtc->data->alarm);
	u32 val;

	spin_lock_irqsave(&rtc->lock, flags);

	समय = rtc->data->पढ़ो_rtc_reg(rtc, reg);
	val = rtc->data->पढ़ो_rtc_reg(rtc, reg_irq) & RTC_IRQ_AL_EN;

	spin_unlock_irqrestore(&rtc->lock, flags);

	alrm->enabled = val ? 1 : 0;
	rtc_समय64_to_पंचांग(समय,  &alrm->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक armada38x_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	u32 reg = ALARM_REG(RTC_ALARM1, rtc->data->alarm);
	u32 reg_irq = ALARM_REG(RTC_IRQ1_CONF, rtc->data->alarm);
	अचिन्हित दीर्घ समय, flags;

	समय = rtc_पंचांग_to_समय64(&alrm->समय);

	spin_lock_irqsave(&rtc->lock, flags);

	rtc_delayed_ग_लिखो(समय, rtc, reg);

	अगर (alrm->enabled) अणु
		rtc_delayed_ग_लिखो(RTC_IRQ_AL_EN, rtc, reg_irq);
		rtc->data->unmask_पूर्णांकerrupt(rtc);
	पूर्ण

	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक armada38x_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	u32 reg_irq = ALARM_REG(RTC_IRQ1_CONF, rtc->data->alarm);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc->lock, flags);

	अगर (enabled)
		rtc_delayed_ग_लिखो(RTC_IRQ_AL_EN, rtc, reg_irq);
	अन्यथा
		rtc_delayed_ग_लिखो(0, rtc, reg_irq);

	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस 0;
पूर्ण

अटल irqवापस_t armada38x_rtc_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा armada38x_rtc *rtc = data;
	u32 val;
	पूर्णांक event = RTC_IRQF | RTC_AF;
	u32 reg_irq = ALARM_REG(RTC_IRQ1_CONF, rtc->data->alarm);

	dev_dbg(&rtc->rtc_dev->dev, "%s:irq(%d)\n", __func__, irq);

	spin_lock(&rtc->lock);

	rtc->data->clear_isr(rtc);
	val = rtc->data->पढ़ो_rtc_reg(rtc, reg_irq);
	/* disable all the पूर्णांकerrupts क्रम alarm*/
	rtc_delayed_ग_लिखो(0, rtc, reg_irq);
	/* Ack the event */
	rtc_delayed_ग_लिखो(1 << rtc->data->alarm, rtc, RTC_STATUS);

	spin_unlock(&rtc->lock);

	अगर (val & RTC_IRQ_FREQ_EN) अणु
		अगर (val & RTC_IRQ_FREQ_1HZ)
			event |= RTC_UF;
		अन्यथा
			event |= RTC_PF;
	पूर्ण

	rtc_update_irq(rtc->rtc_dev, 1, event);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * The inक्रमmation given in the Armada 388 functional spec is complex.
 * They give two dअगरferent क्रमmulas क्रम calculating the offset value,
 * but when considering "Offset" as an 8-bit चिन्हित पूर्णांकeger, they both
 * reduce करोwn to (we shall नाम "Offset" as "val" here):
 *
 *   val = (f_ideal / f_measured - 1) / resolution   where f_ideal = 32768
 *
 * Converting to समय, f = 1/t:
 *   val = (t_measured / t_ideal - 1) / resolution   where t_ideal = 1/32768
 *
 *   =>  t_measured / t_ideal = val * resolution + 1
 *
 * "offset" in the RTC पूर्णांकerface is defined as:
 *   t = t0 * (1 + offset * 1e-9)
 * where t is the desired period, t0 is the measured period with a zero
 * offset, which is t_measured above. With t0 = t_measured and t = t_ideal,
 *   offset = (t_ideal / t_measured - 1) / 1e-9
 *
 *   => t_ideal / t_measured = offset * 1e-9 + 1
 *
 * so:
 *
 *   offset * 1e-9 + 1 = 1 / (val * resolution + 1)
 *
 * We want "resolution" to be an पूर्णांकeger, so resolution = R * 1e-9, giving
 *   offset = 1e18 / (val * R + 1e9) - 1e9
 *   val = (1e18 / (offset + 1e9) - 1e9) / R
 * with a common transक्रमmation:
 *   f(x) = 1e18 / (x + 1e9) - 1e9
 *   offset = f(val * R)
 *   val = f(offset) / R
 *
 * Armada 38x supports two modes, fine mode (954ppb) and coarse mode (3815ppb).
 */
अटल दीर्घ armada38x_ppb_convert(दीर्घ ppb)
अणु
	दीर्घ भाग = ppb + 1000000000L;

	वापस भाग_s64(1000000000000000000LL + भाग / 2, भाग) - 1000000000L;
पूर्ण

अटल पूर्णांक armada38x_rtc_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ccr, flags;
	दीर्घ ppb_cor;

	spin_lock_irqsave(&rtc->lock, flags);
	ccr = rtc->data->पढ़ो_rtc_reg(rtc, RTC_CCR);
	spin_unlock_irqrestore(&rtc->lock, flags);

	ppb_cor = (ccr & RTC_CCR_MODE ? 3815 : 954) * (s8)ccr;
	/* ppb_cor + 1000000000L can never be zero */
	*offset = armada38x_ppb_convert(ppb_cor);

	वापस 0;
पूर्ण

अटल पूर्णांक armada38x_rtc_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ ccr = 0;
	दीर्घ ppb_cor, off;

	/*
	 * The maximum ppb_cor is -128 * 3815 .. 127 * 3815, but we
	 * need to clamp the input.  This equates to -484270 .. 488558.
	 * Not only is this to stop out of range "off" but also to
	 * aव्योम the भागision by zero in armada38x_ppb_convert().
	 */
	offset = clamp(offset, -484270L, 488558L);

	ppb_cor = armada38x_ppb_convert(offset);

	/*
	 * Use low update mode where possible, which gives a better
	 * resolution of correction.
	 */
	off = DIV_ROUND_CLOSEST(ppb_cor, 954);
	अगर (off > 127 || off < -128) अणु
		ccr = RTC_CCR_MODE;
		off = DIV_ROUND_CLOSEST(ppb_cor, 3815);
	पूर्ण

	/*
	 * Armada 388 requires a bit pattern in bits 14..8 depending on
	 * the sign bit: अणु 0, ~S, S, S, S, S, S पूर्ण
	 */
	ccr |= (off & 0x3fff) ^ 0x2000;
	rtc_delayed_ग_लिखो(ccr, rtc, RTC_CCR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops armada38x_rtc_ops = अणु
	.पढ़ो_समय = armada38x_rtc_पढ़ो_समय,
	.set_समय = armada38x_rtc_set_समय,
	.पढ़ो_alarm = armada38x_rtc_पढ़ो_alarm,
	.set_alarm = armada38x_rtc_set_alarm,
	.alarm_irq_enable = armada38x_rtc_alarm_irq_enable,
	.पढ़ो_offset = armada38x_rtc_पढ़ो_offset,
	.set_offset = armada38x_rtc_set_offset,
पूर्ण;

अटल स्थिर काष्ठा armada38x_rtc_data armada38x_data = अणु
	.update_mbus_timing = rtc_update_38x_mbus_timing_params,
	.पढ़ो_rtc_reg = पढ़ो_rtc_रेजिस्टर_38x_wa,
	.clear_isr = armada38x_clear_isr,
	.unmask_पूर्णांकerrupt = armada38x_unmask_पूर्णांकerrupt,
	.alarm = ALARM1,
पूर्ण;

अटल स्थिर काष्ठा armada38x_rtc_data armada8k_data = अणु
	.update_mbus_timing = rtc_update_8k_mbus_timing_params,
	.पढ़ो_rtc_reg = पढ़ो_rtc_रेजिस्टर,
	.clear_isr = armada8k_clear_isr,
	.unmask_पूर्णांकerrupt = armada8k_unmask_पूर्णांकerrupt,
	.alarm = ALARM2,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id armada38x_rtc_of_match_table[] = अणु
	अणु
		.compatible = "marvell,armada-380-rtc",
		.data = &armada38x_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-8k-rtc",
		.data = &armada8k_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, armada38x_rtc_of_match_table);
#पूर्ण_अगर

अटल __init पूर्णांक armada38x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा armada38x_rtc *rtc;

	rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा armada38x_rtc),
			    GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->data = of_device_get_match_data(&pdev->dev);

	rtc->val_to_freq = devm_kसुस्मृति(&pdev->dev, SAMPLE_NR,
				माप(काष्ठा value_to_freq), GFP_KERNEL);
	अगर (!rtc->val_to_freq)
		वापस -ENOMEM;

	spin_lock_init(&rtc->lock);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rtc");
	rtc->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rtc->regs))
		वापस PTR_ERR(rtc->regs);
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rtc-soc");
	rtc->regs_soc = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rtc->regs_soc))
		वापस PTR_ERR(rtc->regs_soc);

	rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rtc->irq < 0)
		वापस rtc->irq;

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	अगर (devm_request_irq(&pdev->dev, rtc->irq, armada38x_rtc_alarm_irq,
				0, pdev->name, rtc) < 0) अणु
		dev_warn(&pdev->dev, "Interrupt not available.\n");
		rtc->irq = -1;
	पूर्ण
	platक्रमm_set_drvdata(pdev, rtc);

	अगर (rtc->irq != -1)
		device_init_wakeup(&pdev->dev, 1);
	अन्यथा
		clear_bit(RTC_FEATURE_ALARM, rtc->rtc_dev->features);

	/* Update RTC-MBUS bridge timing parameters */
	rtc->data->update_mbus_timing(rtc);

	rtc->rtc_dev->ops = &armada38x_rtc_ops;
	rtc->rtc_dev->range_max = U32_MAX;

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक armada38x_rtc_suspend(काष्ठा device *dev)
अणु
	अगर (device_may_wakeup(dev)) अणु
		काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);

		वापस enable_irq_wake(rtc->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक armada38x_rtc_resume(काष्ठा device *dev)
अणु
	अगर (device_may_wakeup(dev)) अणु
		काष्ठा armada38x_rtc *rtc = dev_get_drvdata(dev);

		/* Update RTC-MBUS bridge timing parameters */
		rtc->data->update_mbus_timing(rtc);

		वापस disable_irq_wake(rtc->irq);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(armada38x_rtc_pm_ops,
			 armada38x_rtc_suspend, armada38x_rtc_resume);

अटल काष्ठा platक्रमm_driver armada38x_rtc_driver = अणु
	.driver		= अणु
		.name	= "armada38x-rtc",
		.pm	= &armada38x_rtc_pm_ops,
		.of_match_table = of_match_ptr(armada38x_rtc_of_match_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(armada38x_rtc_driver, armada38x_rtc_probe);

MODULE_DESCRIPTION("Marvell Armada 38x RTC driver");
MODULE_AUTHOR("Gregory CLEMENT <gregory.clement@free-electrons.com>");
MODULE_LICENSE("GPL");
