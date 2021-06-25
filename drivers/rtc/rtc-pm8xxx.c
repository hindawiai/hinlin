<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 */
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

/* RTC Register offsets from RTC CTRL REG */
#घोषणा PM8XXX_ALARM_CTRL_OFFSET	0x01
#घोषणा PM8XXX_RTC_WRITE_OFFSET		0x02
#घोषणा PM8XXX_RTC_READ_OFFSET		0x06
#घोषणा PM8XXX_ALARM_RW_OFFSET		0x0A

/* RTC_CTRL रेजिस्टर bit fields */
#घोषणा PM8xxx_RTC_ENABLE		BIT(7)
#घोषणा PM8xxx_RTC_ALARM_CLEAR		BIT(0)
#घोषणा PM8xxx_RTC_ALARM_ENABLE		BIT(7)

#घोषणा NUM_8_BIT_RTC_REGS		0x4

/**
 * काष्ठा pm8xxx_rtc_regs - describe RTC रेजिस्टरs per PMIC versions
 * @ctrl: base address of control रेजिस्टर
 * @ग_लिखो: base address of ग_लिखो रेजिस्टर
 * @पढ़ो: base address of पढ़ो रेजिस्टर
 * @alarm_ctrl: base address of alarm control रेजिस्टर
 * @alarm_ctrl2: base address of alarm control2 रेजिस्टर
 * @alarm_rw: base address of alarm पढ़ो-ग_लिखो रेजिस्टर
 * @alarm_en: alarm enable mask
 */
काष्ठा pm8xxx_rtc_regs अणु
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक ग_लिखो;
	अचिन्हित पूर्णांक पढ़ो;
	अचिन्हित पूर्णांक alarm_ctrl;
	अचिन्हित पूर्णांक alarm_ctrl2;
	अचिन्हित पूर्णांक alarm_rw;
	अचिन्हित पूर्णांक alarm_en;
पूर्ण;

/**
 * काष्ठा pm8xxx_rtc -  rtc driver पूर्णांकernal काष्ठाure
 * @rtc:		rtc device क्रम this driver.
 * @regmap:		regmap used to access RTC रेजिस्टरs
 * @allow_set_समय:	indicates whether writing to the RTC is allowed
 * @rtc_alarm_irq:	rtc alarm irq number.
 * @regs:		rtc रेजिस्टरs description.
 * @rtc_dev:		device काष्ठाure.
 * @ctrl_reg_lock:	spinlock protecting access to ctrl_reg.
 */
काष्ठा pm8xxx_rtc अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *regmap;
	bool allow_set_समय;
	पूर्णांक rtc_alarm_irq;
	स्थिर काष्ठा pm8xxx_rtc_regs *regs;
	काष्ठा device *rtc_dev;
	spinlock_t ctrl_reg_lock;
पूर्ण;

/*
 * Steps to ग_लिखो the RTC रेजिस्टरs.
 * 1. Disable alarm अगर enabled.
 * 2. Disable rtc अगर enabled.
 * 3. Write 0x00 to LSB.
 * 4. Write Byte[1], Byte[2], Byte[3] then Byte[0].
 * 5. Enable rtc अगर disabled in step 2.
 * 6. Enable alarm अगर disabled in step 1.
 */
अटल पूर्णांक pm8xxx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक rc, i;
	अचिन्हित दीर्घ secs, irq_flags;
	u8 value[NUM_8_BIT_RTC_REGS], alarm_enabled = 0, rtc_disabled = 0;
	अचिन्हित पूर्णांक ctrl_reg, rtc_ctrl_reg;
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;

	अगर (!rtc_dd->allow_set_समय)
		वापस -EACCES;

	secs = rtc_पंचांग_to_समय64(पंचांग);

	dev_dbg(dev, "Seconds value to be written to RTC = %lu\n", secs);

	क्रम (i = 0; i < NUM_8_BIT_RTC_REGS; i++) अणु
		value[i] = secs & 0xFF;
		secs >>= 8;
	पूर्ण

	spin_lock_irqsave(&rtc_dd->ctrl_reg_lock, irq_flags);

	rc = regmap_पढ़ो(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	अगर (rc)
		जाओ rtc_rw_fail;

	अगर (ctrl_reg & regs->alarm_en) अणु
		alarm_enabled = 1;
		ctrl_reg &= ~regs->alarm_en;
		rc = regmap_ग_लिखो(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
		अगर (rc) अणु
			dev_err(dev, "Write to RTC Alarm control register failed\n");
			जाओ rtc_rw_fail;
		पूर्ण
	पूर्ण

	/* Disable RTC H/w beक्रमe writing on RTC रेजिस्टर */
	rc = regmap_पढ़ो(rtc_dd->regmap, regs->ctrl, &rtc_ctrl_reg);
	अगर (rc)
		जाओ rtc_rw_fail;

	अगर (rtc_ctrl_reg & PM8xxx_RTC_ENABLE) अणु
		rtc_disabled = 1;
		rtc_ctrl_reg &= ~PM8xxx_RTC_ENABLE;
		rc = regmap_ग_लिखो(rtc_dd->regmap, regs->ctrl, rtc_ctrl_reg);
		अगर (rc) अणु
			dev_err(dev, "Write to RTC control register failed\n");
			जाओ rtc_rw_fail;
		पूर्ण
	पूर्ण

	/* Write 0 to Byte[0] */
	rc = regmap_ग_लिखो(rtc_dd->regmap, regs->ग_लिखो, 0);
	अगर (rc) अणु
		dev_err(dev, "Write to RTC write data register failed\n");
		जाओ rtc_rw_fail;
	पूर्ण

	/* Write Byte[1], Byte[2], Byte[3] */
	rc = regmap_bulk_ग_लिखो(rtc_dd->regmap, regs->ग_लिखो + 1,
			       &value[1], माप(value) - 1);
	अगर (rc) अणु
		dev_err(dev, "Write to RTC write data register failed\n");
		जाओ rtc_rw_fail;
	पूर्ण

	/* Write Byte[0] */
	rc = regmap_ग_लिखो(rtc_dd->regmap, regs->ग_लिखो, value[0]);
	अगर (rc) अणु
		dev_err(dev, "Write to RTC write data register failed\n");
		जाओ rtc_rw_fail;
	पूर्ण

	/* Enable RTC H/w after writing on RTC रेजिस्टर */
	अगर (rtc_disabled) अणु
		rtc_ctrl_reg |= PM8xxx_RTC_ENABLE;
		rc = regmap_ग_लिखो(rtc_dd->regmap, regs->ctrl, rtc_ctrl_reg);
		अगर (rc) अणु
			dev_err(dev, "Write to RTC control register failed\n");
			जाओ rtc_rw_fail;
		पूर्ण
	पूर्ण

	अगर (alarm_enabled) अणु
		ctrl_reg |= regs->alarm_en;
		rc = regmap_ग_लिखो(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
		अगर (rc) अणु
			dev_err(dev, "Write to RTC Alarm control register failed\n");
			जाओ rtc_rw_fail;
		पूर्ण
	पूर्ण

rtc_rw_fail:
	spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);

	वापस rc;
पूर्ण

अटल पूर्णांक pm8xxx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक rc;
	u8 value[NUM_8_BIT_RTC_REGS];
	अचिन्हित दीर्घ secs;
	अचिन्हित पूर्णांक reg;
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;

	rc = regmap_bulk_पढ़ो(rtc_dd->regmap, regs->पढ़ो, value, माप(value));
	अगर (rc) अणु
		dev_err(dev, "RTC read data register failed\n");
		वापस rc;
	पूर्ण

	/*
	 * Read the LSB again and check अगर there has been a carry over.
	 * If there is, reकरो the पढ़ो operation.
	 */
	rc = regmap_पढ़ो(rtc_dd->regmap, regs->पढ़ो, &reg);
	अगर (rc < 0) अणु
		dev_err(dev, "RTC read data register failed\n");
		वापस rc;
	पूर्ण

	अगर (unlikely(reg < value[0])) अणु
		rc = regmap_bulk_पढ़ो(rtc_dd->regmap, regs->पढ़ो,
				      value, माप(value));
		अगर (rc) अणु
			dev_err(dev, "RTC read data register failed\n");
			वापस rc;
		पूर्ण
	पूर्ण

	secs = value[0] | (value[1] << 8) | (value[2] << 16) |
	       ((अचिन्हित दीर्घ)value[3] << 24);

	rtc_समय64_to_पंचांग(secs, पंचांग);

	dev_dbg(dev, "secs = %lu, h:m:s == %ptRt, y-m-d = %ptRdr\n", secs, पंचांग, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक rc, i;
	u8 value[NUM_8_BIT_RTC_REGS];
	अचिन्हित पूर्णांक ctrl_reg;
	अचिन्हित दीर्घ secs, irq_flags;
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;

	secs = rtc_पंचांग_to_समय64(&alarm->समय);

	क्रम (i = 0; i < NUM_8_BIT_RTC_REGS; i++) अणु
		value[i] = secs & 0xFF;
		secs >>= 8;
	पूर्ण

	spin_lock_irqsave(&rtc_dd->ctrl_reg_lock, irq_flags);

	rc = regmap_bulk_ग_लिखो(rtc_dd->regmap, regs->alarm_rw, value,
			       माप(value));
	अगर (rc) अणु
		dev_err(dev, "Write to RTC ALARM register failed\n");
		जाओ rtc_rw_fail;
	पूर्ण

	rc = regmap_पढ़ो(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	अगर (rc)
		जाओ rtc_rw_fail;

	अगर (alarm->enabled)
		ctrl_reg |= regs->alarm_en;
	अन्यथा
		ctrl_reg &= ~regs->alarm_en;

	rc = regmap_ग_लिखो(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
	अगर (rc) अणु
		dev_err(dev, "Write to RTC alarm control register failed\n");
		जाओ rtc_rw_fail;
	पूर्ण

	dev_dbg(dev, "Alarm Set for h:m:s=%ptRt, y-m-d=%ptRdr\n",
		&alarm->समय, &alarm->समय);
rtc_rw_fail:
	spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक pm8xxx_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक ctrl_reg;
	u8 value[NUM_8_BIT_RTC_REGS];
	अचिन्हित दीर्घ secs;
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;

	rc = regmap_bulk_पढ़ो(rtc_dd->regmap, regs->alarm_rw, value,
			      माप(value));
	अगर (rc) अणु
		dev_err(dev, "RTC alarm time read failed\n");
		वापस rc;
	पूर्ण

	secs = value[0] | (value[1] << 8) | (value[2] << 16) |
	       ((अचिन्हित दीर्घ)value[3] << 24);

	rtc_समय64_to_पंचांग(secs, &alarm->समय);

	rc = regmap_पढ़ो(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	अगर (rc) अणु
		dev_err(dev, "Read from RTC alarm control register failed\n");
		वापस rc;
	पूर्ण
	alarm->enabled = !!(ctrl_reg & PM8xxx_RTC_ALARM_ENABLE);

	dev_dbg(dev, "Alarm set for - h:m:s=%ptRt, y-m-d=%ptRdr\n",
		&alarm->समय, &alarm->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ irq_flags;
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;
	अचिन्हित पूर्णांक ctrl_reg;
	u8 value[NUM_8_BIT_RTC_REGS] = अणु0पूर्ण;

	spin_lock_irqsave(&rtc_dd->ctrl_reg_lock, irq_flags);

	rc = regmap_पढ़ो(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	अगर (rc)
		जाओ rtc_rw_fail;

	अगर (enable)
		ctrl_reg |= regs->alarm_en;
	अन्यथा
		ctrl_reg &= ~regs->alarm_en;

	rc = regmap_ग_लिखो(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
	अगर (rc) अणु
		dev_err(dev, "Write to RTC control register failed\n");
		जाओ rtc_rw_fail;
	पूर्ण

	/* Clear Alarm रेजिस्टर */
	अगर (!enable) अणु
		rc = regmap_bulk_ग_लिखो(rtc_dd->regmap, regs->alarm_rw, value,
				       माप(value));
		अगर (rc) अणु
			dev_err(dev, "Clear RTC ALARM register failed\n");
			जाओ rtc_rw_fail;
		पूर्ण
	पूर्ण

rtc_rw_fail:
	spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pm8xxx_rtc_ops = अणु
	.पढ़ो_समय	= pm8xxx_rtc_पढ़ो_समय,
	.set_समय	= pm8xxx_rtc_set_समय,
	.set_alarm	= pm8xxx_rtc_set_alarm,
	.पढ़ो_alarm	= pm8xxx_rtc_पढ़ो_alarm,
	.alarm_irq_enable = pm8xxx_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t pm8xxx_alarm_trigger(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pm8xxx_rtc *rtc_dd = dev_id;
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;
	अचिन्हित पूर्णांक ctrl_reg;
	पूर्णांक rc;

	rtc_update_irq(rtc_dd->rtc, 1, RTC_IRQF | RTC_AF);

	spin_lock(&rtc_dd->ctrl_reg_lock);

	/* Clear the alarm enable bit */
	rc = regmap_पढ़ो(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	अगर (rc) अणु
		spin_unlock(&rtc_dd->ctrl_reg_lock);
		जाओ rtc_alarm_handled;
	पूर्ण

	ctrl_reg &= ~regs->alarm_en;

	rc = regmap_ग_लिखो(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
	अगर (rc) अणु
		spin_unlock(&rtc_dd->ctrl_reg_lock);
		dev_err(rtc_dd->rtc_dev,
			"Write to alarm control register failed\n");
		जाओ rtc_alarm_handled;
	पूर्ण

	spin_unlock(&rtc_dd->ctrl_reg_lock);

	/* Clear RTC alarm रेजिस्टर */
	rc = regmap_पढ़ो(rtc_dd->regmap, regs->alarm_ctrl2, &ctrl_reg);
	अगर (rc) अणु
		dev_err(rtc_dd->rtc_dev,
			"RTC Alarm control2 register read failed\n");
		जाओ rtc_alarm_handled;
	पूर्ण

	ctrl_reg |= PM8xxx_RTC_ALARM_CLEAR;
	rc = regmap_ग_लिखो(rtc_dd->regmap, regs->alarm_ctrl2, ctrl_reg);
	अगर (rc)
		dev_err(rtc_dd->rtc_dev,
			"Write to RTC Alarm control2 register failed\n");

rtc_alarm_handled:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm8xxx_rtc_enable(काष्ठा pm8xxx_rtc *rtc_dd)
अणु
	स्थिर काष्ठा pm8xxx_rtc_regs *regs = rtc_dd->regs;
	अचिन्हित पूर्णांक ctrl_reg;
	पूर्णांक rc;

	/* Check अगर the RTC is on, अन्यथा turn it on */
	rc = regmap_पढ़ो(rtc_dd->regmap, regs->ctrl, &ctrl_reg);
	अगर (rc)
		वापस rc;

	अगर (!(ctrl_reg & PM8xxx_RTC_ENABLE)) अणु
		ctrl_reg |= PM8xxx_RTC_ENABLE;
		rc = regmap_ग_लिखो(rtc_dd->regmap, regs->ctrl, ctrl_reg);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pm8xxx_rtc_regs pm8921_regs = अणु
	.ctrl		= 0x11d,
	.ग_लिखो		= 0x11f,
	.पढ़ो		= 0x123,
	.alarm_rw	= 0x127,
	.alarm_ctrl	= 0x11d,
	.alarm_ctrl2	= 0x11e,
	.alarm_en	= BIT(1),
पूर्ण;

अटल स्थिर काष्ठा pm8xxx_rtc_regs pm8058_regs = अणु
	.ctrl		= 0x1e8,
	.ग_लिखो		= 0x1ea,
	.पढ़ो		= 0x1ee,
	.alarm_rw	= 0x1f2,
	.alarm_ctrl	= 0x1e8,
	.alarm_ctrl2	= 0x1e9,
	.alarm_en	= BIT(1),
पूर्ण;

अटल स्थिर काष्ठा pm8xxx_rtc_regs pm8941_regs = अणु
	.ctrl		= 0x6046,
	.ग_लिखो		= 0x6040,
	.पढ़ो		= 0x6048,
	.alarm_rw	= 0x6140,
	.alarm_ctrl	= 0x6146,
	.alarm_ctrl2	= 0x6148,
	.alarm_en	= BIT(7),
पूर्ण;

अटल स्थिर काष्ठा pm8xxx_rtc_regs pmk8350_regs = अणु
	.ctrl		= 0x6146,
	.ग_लिखो		= 0x6140,
	.पढ़ो		= 0x6148,
	.alarm_rw	= 0x6240,
	.alarm_ctrl	= 0x6246,
	.alarm_ctrl2	= 0x6248,
	.alarm_en	= BIT(7),
पूर्ण;

/*
 * Hardcoded RTC bases until IORESOURCE_REG mapping is figured out
 */
अटल स्थिर काष्ठा of_device_id pm8xxx_id_table[] = अणु
	अणु .compatible = "qcom,pm8921-rtc", .data = &pm8921_regs पूर्ण,
	अणु .compatible = "qcom,pm8018-rtc", .data = &pm8921_regs पूर्ण,
	अणु .compatible = "qcom,pm8058-rtc", .data = &pm8058_regs पूर्ण,
	अणु .compatible = "qcom,pm8941-rtc", .data = &pm8941_regs पूर्ण,
	अणु .compatible = "qcom,pmk8350-rtc", .data = &pmk8350_regs पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_id_table);

अटल पूर्णांक pm8xxx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	काष्ठा pm8xxx_rtc *rtc_dd;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_node(pm8xxx_id_table, pdev->dev.of_node);
	अगर (!match)
		वापस -ENXIO;

	rtc_dd = devm_kzalloc(&pdev->dev, माप(*rtc_dd), GFP_KERNEL);
	अगर (rtc_dd == शून्य)
		वापस -ENOMEM;

	/* Initialise spinlock to protect RTC control रेजिस्टर */
	spin_lock_init(&rtc_dd->ctrl_reg_lock);

	rtc_dd->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!rtc_dd->regmap) अणु
		dev_err(&pdev->dev, "Parent regmap unavailable.\n");
		वापस -ENXIO;
	पूर्ण

	rtc_dd->rtc_alarm_irq = platक्रमm_get_irq(pdev, 0);
	अगर (rtc_dd->rtc_alarm_irq < 0)
		वापस -ENXIO;

	rtc_dd->allow_set_समय = of_property_पढ़ो_bool(pdev->dev.of_node,
						      "allow-set-time");

	rtc_dd->regs = match->data;
	rtc_dd->rtc_dev = &pdev->dev;

	rc = pm8xxx_rtc_enable(rtc_dd);
	अगर (rc)
		वापस rc;

	platक्रमm_set_drvdata(pdev, rtc_dd);

	device_init_wakeup(&pdev->dev, 1);

	/* Register the RTC device */
	rtc_dd->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc_dd->rtc))
		वापस PTR_ERR(rtc_dd->rtc);

	rtc_dd->rtc->ops = &pm8xxx_rtc_ops;
	rtc_dd->rtc->range_max = U32_MAX;

	/* Request the alarm IRQ */
	rc = devm_request_any_context_irq(&pdev->dev, rtc_dd->rtc_alarm_irq,
					  pm8xxx_alarm_trigger,
					  IRQF_TRIGGER_RISING,
					  "pm8xxx_rtc_alarm", rtc_dd);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Request IRQ failed (%d)\n", rc);
		वापस rc;
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(rtc_dd->rtc);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pm8xxx_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(rtc_dd->rtc_alarm_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(rtc_dd->rtc_alarm_irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pm8xxx_rtc_pm_ops,
			 pm8xxx_rtc_suspend,
			 pm8xxx_rtc_resume);

अटल काष्ठा platक्रमm_driver pm8xxx_rtc_driver = अणु
	.probe		= pm8xxx_rtc_probe,
	.driver	= अणु
		.name		= "rtc-pm8xxx",
		.pm		= &pm8xxx_rtc_pm_ops,
		.of_match_table	= pm8xxx_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pm8xxx_rtc_driver);

MODULE_ALIAS("platform:rtc-pm8xxx");
MODULE_DESCRIPTION("PMIC8xxx RTC driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Anirudh Ghayal <aghayal@codeaurora.org>");
