<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// RTC driver क्रम Maxim MAX8997
//
// Copyright (C) 2013 Samsung Electronics Co.Ltd
//
//  based on rtc-max8998.c

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max8997-निजी.h>
#समावेश <linux/irqकरोमुख्य.h>

/* Module parameter क्रम WTSR function control */
अटल पूर्णांक wtsr_en = 1;
module_param(wtsr_en, पूर्णांक, 0444);
MODULE_PARM_DESC(wtsr_en, "Watchdog Timeout & Software Reset (default=on)");
/* Module parameter क्रम SMPL function control */
अटल पूर्णांक smpl_en = 1;
module_param(smpl_en, पूर्णांक, 0444);
MODULE_PARM_DESC(smpl_en, "Sudden Momentary Power Loss (default=on)");

/* RTC Control Register */
#घोषणा BCD_EN_SHIFT			0
#घोषणा BCD_EN_MASK			(1 << BCD_EN_SHIFT)
#घोषणा MODEL24_SHIFT			1
#घोषणा MODEL24_MASK			(1 << MODEL24_SHIFT)
/* RTC Update Register1 */
#घोषणा RTC_UDR_SHIFT			0
#घोषणा RTC_UDR_MASK			(1 << RTC_UDR_SHIFT)
/* WTSR and SMPL Register */
#घोषणा WTSRT_SHIFT			0
#घोषणा SMPLT_SHIFT			2
#घोषणा WTSR_EN_SHIFT			6
#घोषणा SMPL_EN_SHIFT			7
#घोषणा WTSRT_MASK			(3 << WTSRT_SHIFT)
#घोषणा SMPLT_MASK			(3 << SMPLT_SHIFT)
#घोषणा WTSR_EN_MASK			(1 << WTSR_EN_SHIFT)
#घोषणा SMPL_EN_MASK			(1 << SMPL_EN_SHIFT)
/* RTC Hour रेजिस्टर */
#घोषणा HOUR_PM_SHIFT			6
#घोषणा HOUR_PM_MASK			(1 << HOUR_PM_SHIFT)
/* RTC Alarm Enable */
#घोषणा ALARM_ENABLE_SHIFT		7
#घोषणा ALARM_ENABLE_MASK		(1 << ALARM_ENABLE_SHIFT)

क्रमागत अणु
	RTC_SEC = 0,
	RTC_MIN,
	RTC_HOUR,
	RTC_WEEKDAY,
	RTC_MONTH,
	RTC_YEAR,
	RTC_DATE,
	RTC_NR_TIME
पूर्ण;

काष्ठा max8997_rtc_info अणु
	काष्ठा device		*dev;
	काष्ठा max8997_dev	*max8997;
	काष्ठा i2c_client	*rtc;
	काष्ठा rtc_device	*rtc_dev;
	काष्ठा mutex		lock;
	पूर्णांक virq;
	पूर्णांक rtc_24hr_mode;
पूर्ण;

अटल व्योम max8997_rtc_data_to_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग,
				   पूर्णांक rtc_24hr_mode)
अणु
	पंचांग->पंचांग_sec = data[RTC_SEC] & 0x7f;
	पंचांग->पंचांग_min = data[RTC_MIN] & 0x7f;
	अगर (rtc_24hr_mode)
		पंचांग->पंचांग_hour = data[RTC_HOUR] & 0x1f;
	अन्यथा अणु
		पंचांग->पंचांग_hour = data[RTC_HOUR] & 0x0f;
		अगर (data[RTC_HOUR] & HOUR_PM_MASK)
			पंचांग->पंचांग_hour += 12;
	पूर्ण

	पंचांग->पंचांग_wday = fls(data[RTC_WEEKDAY] & 0x7f) - 1;
	पंचांग->पंचांग_mday = data[RTC_DATE] & 0x1f;
	पंचांग->पंचांग_mon = (data[RTC_MONTH] & 0x0f) - 1;
	पंचांग->पंचांग_year = (data[RTC_YEAR] & 0x7f) + 100;
	पंचांग->पंचांग_yday = 0;
	पंचांग->पंचांग_isdst = 0;
पूर्ण

अटल पूर्णांक max8997_rtc_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data)
अणु
	data[RTC_SEC] = पंचांग->पंचांग_sec;
	data[RTC_MIN] = पंचांग->पंचांग_min;
	data[RTC_HOUR] = पंचांग->पंचांग_hour;
	data[RTC_WEEKDAY] = 1 << पंचांग->पंचांग_wday;
	data[RTC_DATE] = पंचांग->पंचांग_mday;
	data[RTC_MONTH] = पंचांग->पंचांग_mon + 1;
	data[RTC_YEAR] = पंचांग->पंचांग_year > 100 ? (पंचांग->पंचांग_year - 100) : 0;

	अगर (पंचांग->पंचांग_year < 100) अणु
		pr_warn("RTC cannot handle the year %d.  Assume it's 2000.\n",
			1900 + पंचांग->पंचांग_year);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक max8997_rtc_set_update_reg(काष्ठा max8997_rtc_info *info)
अणु
	पूर्णांक ret;

	ret = max8997_ग_लिखो_reg(info->rtc, MAX8997_RTC_UPDATE1,
						RTC_UDR_MASK);
	अगर (ret < 0)
		dev_err(info->dev, "%s: fail to write update reg(%d)\n",
				__func__, ret);
	अन्यथा अणु
		/* Minimum 16ms delay required beक्रमe RTC update.
		 * Otherwise, we may पढ़ो and update based on out-of-date
		 * value */
		msleep(20);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max8997_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8997_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	mutex_lock(&info->lock);
	ret = max8997_bulk_पढ़ो(info->rtc, MAX8997_RTC_SEC, RTC_NR_TIME, data);
	mutex_unlock(&info->lock);

	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to read time reg(%d)\n", __func__,
				ret);
		वापस ret;
	पूर्ण

	max8997_rtc_data_to_पंचांग(data, पंचांग, info->rtc_24hr_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8997_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	ret = max8997_rtc_पंचांग_to_data(पंचांग, data);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&info->lock);

	ret = max8997_bulk_ग_लिखो(info->rtc, MAX8997_RTC_SEC, RTC_NR_TIME, data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write time reg(%d)\n", __func__,
				ret);
		जाओ out;
	पूर्ण

	ret = max8997_rtc_set_update_reg(info);
out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max8997_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8997_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	u8 val;
	पूर्णांक i, ret;

	mutex_lock(&info->lock);

	ret = max8997_bulk_पढ़ो(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
			data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s:%d fail to read alarm reg(%d)\n",
				__func__, __LINE__, ret);
		जाओ out;
	पूर्ण

	max8997_rtc_data_to_पंचांग(data, &alrm->समय, info->rtc_24hr_mode);

	alrm->enabled = 0;
	क्रम (i = 0; i < RTC_NR_TIME; i++) अणु
		अगर (data[i] & ALARM_ENABLE_MASK) अणु
			alrm->enabled = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	alrm->pending = 0;
	ret = max8997_पढ़ो_reg(info->max8997->i2c, MAX8997_REG_STATUS1, &val);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s:%d fail to read status1 reg(%d)\n",
				__func__, __LINE__, ret);
		जाओ out;
	पूर्ण

	अगर (val & (1 << 4)) /* RTCA1 */
		alrm->pending = 1;

out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max8997_rtc_stop_alarm(काष्ठा max8997_rtc_info *info)
अणु
	u8 data[RTC_NR_TIME];
	पूर्णांक ret, i;

	अगर (!mutex_is_locked(&info->lock))
		dev_warn(info->dev, "%s: should have mutex locked\n", __func__);

	ret = max8997_bulk_पढ़ो(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to read alarm reg(%d)\n",
				__func__, ret);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < RTC_NR_TIME; i++)
		data[i] &= ~ALARM_ENABLE_MASK;

	ret = max8997_bulk_ग_लिखो(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				 data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write alarm reg(%d)\n",
				__func__, ret);
		जाओ out;
	पूर्ण

	ret = max8997_rtc_set_update_reg(info);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max8997_rtc_start_alarm(काष्ठा max8997_rtc_info *info)
अणु
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	अगर (!mutex_is_locked(&info->lock))
		dev_warn(info->dev, "%s: should have mutex locked\n", __func__);

	ret = max8997_bulk_पढ़ो(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to read alarm reg(%d)\n",
				__func__, ret);
		जाओ out;
	पूर्ण

	data[RTC_SEC] |= (1 << ALARM_ENABLE_SHIFT);
	data[RTC_MIN] |= (1 << ALARM_ENABLE_SHIFT);
	data[RTC_HOUR] |= (1 << ALARM_ENABLE_SHIFT);
	data[RTC_WEEKDAY] &= ~ALARM_ENABLE_MASK;
	अगर (data[RTC_MONTH] & 0xf)
		data[RTC_MONTH] |= (1 << ALARM_ENABLE_SHIFT);
	अगर (data[RTC_YEAR] & 0x7f)
		data[RTC_YEAR] |= (1 << ALARM_ENABLE_SHIFT);
	अगर (data[RTC_DATE] & 0x1f)
		data[RTC_DATE] |= (1 << ALARM_ENABLE_SHIFT);

	ret = max8997_bulk_ग_लिखो(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				 data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write alarm reg(%d)\n",
				__func__, ret);
		जाओ out;
	पूर्ण

	ret = max8997_rtc_set_update_reg(info);
out:
	वापस ret;
पूर्ण
अटल पूर्णांक max8997_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8997_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	ret = max8997_rtc_पंचांग_to_data(&alrm->समय, data);
	अगर (ret < 0)
		वापस ret;

	dev_info(info->dev, "%s: %d-%02d-%02d %02d:%02d:%02d\n", __func__,
			data[RTC_YEAR] + 2000, data[RTC_MONTH], data[RTC_DATE],
			data[RTC_HOUR], data[RTC_MIN], data[RTC_SEC]);

	mutex_lock(&info->lock);

	ret = max8997_rtc_stop_alarm(info);
	अगर (ret < 0)
		जाओ out;

	ret = max8997_bulk_ग_लिखो(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write alarm reg(%d)\n",
				__func__, ret);
		जाओ out;
	पूर्ण

	ret = max8997_rtc_set_update_reg(info);
	अगर (ret < 0)
		जाओ out;

	अगर (alrm->enabled)
		ret = max8997_rtc_start_alarm(info);
out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max8997_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा max8997_rtc_info *info = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&info->lock);
	अगर (enabled)
		ret = max8997_rtc_start_alarm(info);
	अन्यथा
		ret = max8997_rtc_stop_alarm(info);
	mutex_unlock(&info->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t max8997_rtc_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8997_rtc_info *info = data;

	dev_info(info->dev, "%s:irq(%d)\n", __func__, irq);

	rtc_update_irq(info->rtc_dev, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max8997_rtc_ops = अणु
	.पढ़ो_समय = max8997_rtc_पढ़ो_समय,
	.set_समय = max8997_rtc_set_समय,
	.पढ़ो_alarm = max8997_rtc_पढ़ो_alarm,
	.set_alarm = max8997_rtc_set_alarm,
	.alarm_irq_enable = max8997_rtc_alarm_irq_enable,
पूर्ण;

अटल व्योम max8997_rtc_enable_wtsr(काष्ठा max8997_rtc_info *info, bool enable)
अणु
	पूर्णांक ret;
	u8 val, mask;

	अगर (!wtsr_en)
		वापस;

	अगर (enable)
		val = (1 << WTSR_EN_SHIFT) | (3 << WTSRT_SHIFT);
	अन्यथा
		val = 0;

	mask = WTSR_EN_MASK | WTSRT_MASK;

	dev_info(info->dev, "%s: %s WTSR\n", __func__,
			enable ? "enable" : "disable");

	ret = max8997_update_reg(info->rtc, MAX8997_RTC_WTSR_SMPL, val, mask);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to update WTSR reg(%d)\n",
				__func__, ret);
		वापस;
	पूर्ण

	max8997_rtc_set_update_reg(info);
पूर्ण

अटल व्योम max8997_rtc_enable_smpl(काष्ठा max8997_rtc_info *info, bool enable)
अणु
	पूर्णांक ret;
	u8 val, mask;

	अगर (!smpl_en)
		वापस;

	अगर (enable)
		val = (1 << SMPL_EN_SHIFT) | (0 << SMPLT_SHIFT);
	अन्यथा
		val = 0;

	mask = SMPL_EN_MASK | SMPLT_MASK;

	dev_info(info->dev, "%s: %s SMPL\n", __func__,
			enable ? "enable" : "disable");

	ret = max8997_update_reg(info->rtc, MAX8997_RTC_WTSR_SMPL, val, mask);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to update SMPL reg(%d)\n",
				__func__, ret);
		वापस;
	पूर्ण

	max8997_rtc_set_update_reg(info);

	val = 0;
	max8997_पढ़ो_reg(info->rtc, MAX8997_RTC_WTSR_SMPL, &val);
	pr_info("WTSR_SMPL(0x%02x)\n", val);
पूर्ण

अटल पूर्णांक max8997_rtc_init_reg(काष्ठा max8997_rtc_info *info)
अणु
	u8 data[2];
	पूर्णांक ret;

	/* Set RTC control रेजिस्टर : Binary mode, 24hour mकरोe */
	data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
	data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);

	info->rtc_24hr_mode = 1;

	ret = max8997_bulk_ग_लिखो(info->rtc, MAX8997_RTC_CTRLMASK, 2, data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write controlm reg(%d)\n",
				__func__, ret);
		वापस ret;
	पूर्ण

	ret = max8997_rtc_set_update_reg(info);
	वापस ret;
पूर्ण

अटल पूर्णांक max8997_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_dev *max8997 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8997_rtc_info *info;
	पूर्णांक ret, virq;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max8997_rtc_info),
			GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	mutex_init(&info->lock);
	info->dev = &pdev->dev;
	info->max8997 = max8997;
	info->rtc = max8997->rtc;

	platक्रमm_set_drvdata(pdev, info);

	ret = max8997_rtc_init_reg(info);

	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to initialize RTC reg:%d\n", ret);
		वापस ret;
	पूर्ण

	max8997_rtc_enable_wtsr(info, true);
	max8997_rtc_enable_smpl(info, true);

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, "max8997-rtc",
					&max8997_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(info->rtc_dev)) अणु
		ret = PTR_ERR(info->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		वापस ret;
	पूर्ण

	virq = irq_create_mapping(max8997->irq_करोमुख्य, MAX8997_PMICIRQ_RTCA1);
	अगर (!virq) अणु
		dev_err(&pdev->dev, "Failed to create mapping alarm IRQ\n");
		ret = -ENXIO;
		जाओ err_out;
	पूर्ण
	info->virq = virq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, virq, शून्य,
				max8997_rtc_alarm_irq, 0,
				"rtc-alarm0", info);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->virq, ret);

err_out:
	वापस ret;
पूर्ण

अटल व्योम max8997_rtc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_rtc_info *info = platक्रमm_get_drvdata(pdev);

	max8997_rtc_enable_wtsr(info, false);
	max8997_rtc_enable_smpl(info, false);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id rtc_id[] = अणु
	अणु "max8997-rtc", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rtc_id);

अटल काष्ठा platक्रमm_driver max8997_rtc_driver = अणु
	.driver		= अणु
		.name	= "max8997-rtc",
	पूर्ण,
	.probe		= max8997_rtc_probe,
	.shutकरोwn	= max8997_rtc_shutकरोwn,
	.id_table	= rtc_id,
पूर्ण;

module_platक्रमm_driver(max8997_rtc_driver);

MODULE_DESCRIPTION("Maxim MAX8997 RTC driver");
MODULE_AUTHOR("<ms925.kim@samsung.com>");
MODULE_LICENSE("GPL");
