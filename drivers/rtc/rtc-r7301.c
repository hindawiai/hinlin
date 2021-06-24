<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EPSON TOYOCOM RTC-7301SF/DG Driver
 *
 * Copyright (c) 2016 Akinobu Mita <akinobu.mita@gmail.com>
 *
 * Based on rtc-rp5c01.c
 *
 * Datasheet: http://www5.epsondevice.com/en/products/parallel/rtc7301sf.hपंचांगl
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा DRV_NAME "rtc-r7301"

#घोषणा RTC7301_1_SEC		0x0	/* Bank 0 and Band 1 */
#घोषणा RTC7301_10_SEC		0x1	/* Bank 0 and Band 1 */
#घोषणा RTC7301_AE		BIT(3)
#घोषणा RTC7301_1_MIN		0x2	/* Bank 0 and Band 1 */
#घोषणा RTC7301_10_MIN		0x3	/* Bank 0 and Band 1 */
#घोषणा RTC7301_1_HOUR		0x4	/* Bank 0 and Band 1 */
#घोषणा RTC7301_10_HOUR		0x5	/* Bank 0 and Band 1 */
#घोषणा RTC7301_DAY_OF_WEEK	0x6	/* Bank 0 and Band 1 */
#घोषणा RTC7301_1_DAY		0x7	/* Bank 0 and Band 1 */
#घोषणा RTC7301_10_DAY		0x8	/* Bank 0 and Band 1 */
#घोषणा RTC7301_1_MONTH		0x9	/* Bank 0 */
#घोषणा RTC7301_10_MONTH	0xa	/* Bank 0 */
#घोषणा RTC7301_1_YEAR		0xb	/* Bank 0 */
#घोषणा RTC7301_10_YEAR		0xc	/* Bank 0 */
#घोषणा RTC7301_100_YEAR	0xd	/* Bank 0 */
#घोषणा RTC7301_1000_YEAR	0xe	/* Bank 0 */
#घोषणा RTC7301_ALARM_CONTROL	0xe	/* Bank 1 */
#घोषणा RTC7301_ALARM_CONTROL_AIE	BIT(0)
#घोषणा RTC7301_ALARM_CONTROL_AF	BIT(1)
#घोषणा RTC7301_TIMER_CONTROL	0xe	/* Bank 2 */
#घोषणा RTC7301_TIMER_CONTROL_TIE	BIT(0)
#घोषणा RTC7301_TIMER_CONTROL_TF	BIT(1)
#घोषणा RTC7301_CONTROL		0xf	/* All banks */
#घोषणा RTC7301_CONTROL_BUSY		BIT(0)
#घोषणा RTC7301_CONTROL_STOP		BIT(1)
#घोषणा RTC7301_CONTROL_BANK_SEL_0	BIT(2)
#घोषणा RTC7301_CONTROL_BANK_SEL_1	BIT(3)

काष्ठा rtc7301_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	spinlock_t lock;
	u8 bank;
पूर्ण;

अटल स्थिर काष्ठा regmap_config rtc7301_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.reg_stride = 4,
पूर्ण;

अटल u8 rtc7301_पढ़ो(काष्ठा rtc7301_priv *priv, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक reg_stride = regmap_get_reg_stride(priv->regmap);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(priv->regmap, reg_stride * reg, &val);

	वापस val & 0xf;
पूर्ण

अटल व्योम rtc7301_ग_लिखो(काष्ठा rtc7301_priv *priv, u8 val, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक reg_stride = regmap_get_reg_stride(priv->regmap);

	regmap_ग_लिखो(priv->regmap, reg_stride * reg, val);
पूर्ण

अटल व्योम rtc7301_update_bits(काष्ठा rtc7301_priv *priv, अचिन्हित पूर्णांक reg,
				u8 mask, u8 val)
अणु
	पूर्णांक reg_stride = regmap_get_reg_stride(priv->regmap);

	regmap_update_bits(priv->regmap, reg_stride * reg, mask, val);
पूर्ण

अटल पूर्णांक rtc7301_रुको_जबतक_busy(काष्ठा rtc7301_priv *priv)
अणु
	पूर्णांक retries = 100;

	जबतक (retries-- > 0) अणु
		u8 val;

		val = rtc7301_पढ़ो(priv, RTC7301_CONTROL);
		अगर (!(val & RTC7301_CONTROL_BUSY))
			वापस 0;

		udelay(300);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम rtc7301_stop(काष्ठा rtc7301_priv *priv)
अणु
	rtc7301_update_bits(priv, RTC7301_CONTROL, RTC7301_CONTROL_STOP,
			    RTC7301_CONTROL_STOP);
पूर्ण

अटल व्योम rtc7301_start(काष्ठा rtc7301_priv *priv)
अणु
	rtc7301_update_bits(priv, RTC7301_CONTROL, RTC7301_CONTROL_STOP, 0);
पूर्ण

अटल व्योम rtc7301_select_bank(काष्ठा rtc7301_priv *priv, u8 bank)
अणु
	u8 val = 0;

	अगर (bank == priv->bank)
		वापस;

	अगर (bank & BIT(0))
		val |= RTC7301_CONTROL_BANK_SEL_0;
	अगर (bank & BIT(1))
		val |= RTC7301_CONTROL_BANK_SEL_1;

	rtc7301_update_bits(priv, RTC7301_CONTROL,
			    RTC7301_CONTROL_BANK_SEL_0 |
			    RTC7301_CONTROL_BANK_SEL_1, val);

	priv->bank = bank;
पूर्ण

अटल व्योम rtc7301_get_समय(काष्ठा rtc7301_priv *priv, काष्ठा rtc_समय *पंचांग,
			     bool alarm)
अणु
	पूर्णांक year;

	पंचांग->पंचांग_sec = rtc7301_पढ़ो(priv, RTC7301_1_SEC);
	पंचांग->पंचांग_sec += (rtc7301_पढ़ो(priv, RTC7301_10_SEC) & ~RTC7301_AE) * 10;
	पंचांग->पंचांग_min = rtc7301_पढ़ो(priv, RTC7301_1_MIN);
	पंचांग->पंचांग_min += (rtc7301_पढ़ो(priv, RTC7301_10_MIN) & ~RTC7301_AE) * 10;
	पंचांग->पंचांग_hour = rtc7301_पढ़ो(priv, RTC7301_1_HOUR);
	पंचांग->पंचांग_hour += (rtc7301_पढ़ो(priv, RTC7301_10_HOUR) & ~RTC7301_AE) * 10;
	पंचांग->पंचांग_mday = rtc7301_पढ़ो(priv, RTC7301_1_DAY);
	पंचांग->पंचांग_mday += (rtc7301_पढ़ो(priv, RTC7301_10_DAY) & ~RTC7301_AE) * 10;

	अगर (alarm) अणु
		पंचांग->पंचांग_wday = -1;
		पंचांग->पंचांग_mon = -1;
		पंचांग->पंचांग_year = -1;
		पंचांग->पंचांग_yday = -1;
		पंचांग->पंचांग_isdst = -1;
		वापस;
	पूर्ण

	पंचांग->पंचांग_wday = (rtc7301_पढ़ो(priv, RTC7301_DAY_OF_WEEK) & ~RTC7301_AE);
	पंचांग->पंचांग_mon = rtc7301_पढ़ो(priv, RTC7301_10_MONTH) * 10 +
		     rtc7301_पढ़ो(priv, RTC7301_1_MONTH) - 1;
	year = rtc7301_पढ़ो(priv, RTC7301_1000_YEAR) * 1000 +
	       rtc7301_पढ़ो(priv, RTC7301_100_YEAR) * 100 +
	       rtc7301_पढ़ो(priv, RTC7301_10_YEAR) * 10 +
	       rtc7301_पढ़ो(priv, RTC7301_1_YEAR);

	पंचांग->पंचांग_year = year - 1900;
पूर्ण

अटल व्योम rtc7301_ग_लिखो_समय(काष्ठा rtc7301_priv *priv, काष्ठा rtc_समय *पंचांग,
			       bool alarm)
अणु
	पूर्णांक year;

	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_sec % 10, RTC7301_1_SEC);
	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_sec / 10, RTC7301_10_SEC);

	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_min % 10, RTC7301_1_MIN);
	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_min / 10, RTC7301_10_MIN);

	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_hour % 10, RTC7301_1_HOUR);
	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_hour / 10, RTC7301_10_HOUR);

	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_mday % 10, RTC7301_1_DAY);
	rtc7301_ग_लिखो(priv, पंचांग->पंचांग_mday / 10, RTC7301_10_DAY);

	/* Don't care क्रम alarm रेजिस्टर */
	rtc7301_ग_लिखो(priv, alarm ? RTC7301_AE : पंचांग->पंचांग_wday,
		      RTC7301_DAY_OF_WEEK);

	अगर (alarm)
		वापस;

	rtc7301_ग_लिखो(priv, (पंचांग->पंचांग_mon + 1) % 10, RTC7301_1_MONTH);
	rtc7301_ग_लिखो(priv, (पंचांग->पंचांग_mon + 1) / 10, RTC7301_10_MONTH);

	year = पंचांग->पंचांग_year + 1900;

	rtc7301_ग_लिखो(priv, year % 10, RTC7301_1_YEAR);
	rtc7301_ग_लिखो(priv, (year / 10) % 10, RTC7301_10_YEAR);
	rtc7301_ग_लिखो(priv, (year / 100) % 10, RTC7301_100_YEAR);
	rtc7301_ग_लिखो(priv, year / 1000, RTC7301_1000_YEAR);
पूर्ण

अटल व्योम rtc7301_alarm_irq(काष्ठा rtc7301_priv *priv, अचिन्हित पूर्णांक enabled)
अणु
	rtc7301_update_bits(priv, RTC7301_ALARM_CONTROL,
			    RTC7301_ALARM_CONTROL_AF |
			    RTC7301_ALARM_CONTROL_AIE,
			    enabled ? RTC7301_ALARM_CONTROL_AIE : 0);
पूर्ण

अटल पूर्णांक rtc7301_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 0);

	err = rtc7301_रुको_जबतक_busy(priv);
	अगर (!err)
		rtc7301_get_समय(priv, पंचांग, false);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक rtc7301_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_stop(priv);
	udelay(300);
	rtc7301_select_bank(priv, 0);
	rtc7301_ग_लिखो_समय(priv, पंचांग, false);
	rtc7301_start(priv);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rtc7301_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u8 alrm_ctrl;

	अगर (priv->irq <= 0)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 1);
	rtc7301_get_समय(priv, &alarm->समय, true);

	alrm_ctrl = rtc7301_पढ़ो(priv, RTC7301_ALARM_CONTROL);

	alarm->enabled = !!(alrm_ctrl & RTC7301_ALARM_CONTROL_AIE);
	alarm->pending = !!(alrm_ctrl & RTC7301_ALARM_CONTROL_AF);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rtc7301_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	अगर (priv->irq <= 0)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 1);
	rtc7301_ग_लिखो_समय(priv, &alarm->समय, true);
	rtc7301_alarm_irq(priv, alarm->enabled);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rtc7301_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	अगर (priv->irq <= 0)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 1);
	rtc7301_alarm_irq(priv, enabled);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc7301_rtc_ops = अणु
	.पढ़ो_समय	= rtc7301_पढ़ो_समय,
	.set_समय	= rtc7301_set_समय,
	.पढ़ो_alarm	= rtc7301_पढ़ो_alarm,
	.set_alarm	= rtc7301_set_alarm,
	.alarm_irq_enable = rtc7301_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t rtc7301_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rtc_device *rtc = dev_id;
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(rtc->dev.parent);
	irqवापस_t ret = IRQ_NONE;
	u8 alrm_ctrl;

	spin_lock(&priv->lock);

	rtc7301_select_bank(priv, 1);

	alrm_ctrl = rtc7301_पढ़ो(priv, RTC7301_ALARM_CONTROL);
	अगर (alrm_ctrl & RTC7301_ALARM_CONTROL_AF) अणु
		ret = IRQ_HANDLED;
		rtc7301_alarm_irq(priv, false);
		rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF);
	पूर्ण

	spin_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल व्योम rtc7301_init(काष्ठा rtc7301_priv *priv)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 2);
	rtc7301_ग_लिखो(priv, 0, RTC7301_TIMER_CONTROL);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक __init rtc7301_rtc_probe(काष्ठा platक्रमm_device *dev)
अणु
	व्योम __iomem *regs;
	काष्ठा rtc7301_priv *priv;
	काष्ठा rtc_device *rtc;
	पूर्णांक ret;

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	regs = devm_platक्रमm_ioremap_resource(dev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	priv->regmap = devm_regmap_init_mmio(&dev->dev, regs,
					     &rtc7301_regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->irq = platक्रमm_get_irq(dev, 0);

	spin_lock_init(&priv->lock);
	priv->bank = -1;

	rtc7301_init(priv);

	platक्रमm_set_drvdata(dev, priv);

	rtc = devm_rtc_device_रेजिस्टर(&dev->dev, DRV_NAME, &rtc7301_rtc_ops,
				       THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	अगर (priv->irq > 0) अणु
		ret = devm_request_irq(&dev->dev, priv->irq,
				       rtc7301_irq_handler, IRQF_SHARED,
				       dev_name(&dev->dev), rtc);
		अगर (ret) अणु
			priv->irq = 0;
			dev_err(&dev->dev, "unable to request IRQ\n");
		पूर्ण अन्यथा अणु
			device_set_wakeup_capable(&dev->dev, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक rtc7301_suspend(काष्ठा device *dev)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(priv->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक rtc7301_resume(काष्ठा device *dev)
अणु
	काष्ठा rtc7301_priv *priv = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(priv->irq);

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rtc7301_pm_ops, rtc7301_suspend, rtc7301_resume);

अटल स्थिर काष्ठा of_device_id rtc7301_dt_match[] = अणु
	अणु .compatible = "epson,rtc7301sf" पूर्ण,
	अणु .compatible = "epson,rtc7301dg" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rtc7301_dt_match);

अटल काष्ठा platक्रमm_driver rtc7301_rtc_driver = अणु
	.driver	= अणु
		.name = DRV_NAME,
		.of_match_table = rtc7301_dt_match,
		.pm = &rtc7301_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(rtc7301_rtc_driver, rtc7301_rtc_probe);

MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("EPSON TOYOCOM RTC-7301SF/DG Driver");
MODULE_ALIAS("platform:rtc-r7301");
