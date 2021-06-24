<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Virupax Sadashivpetimath <virupax.sadashivpetimath@stericsson.com>
 *
 * RTC घड़ी driver क्रम the RTC part of the AB8500 Power management chip.
 * Based on RTC घड़ी driver क्रम the AB3100 Analog Baseband Chip by
 * Linus Walleij <linus.walleij@stericsson.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_wakeirq.h>

#घोषणा AB8500_RTC_SOFF_STAT_REG	0x00
#घोषणा AB8500_RTC_CC_CONF_REG		0x01
#घोषणा AB8500_RTC_READ_REQ_REG		0x02
#घोषणा AB8500_RTC_WATCH_TSECMID_REG	0x03
#घोषणा AB8500_RTC_WATCH_TSECHI_REG	0x04
#घोषणा AB8500_RTC_WATCH_TMIN_LOW_REG	0x05
#घोषणा AB8500_RTC_WATCH_TMIN_MID_REG	0x06
#घोषणा AB8500_RTC_WATCH_TMIN_HI_REG	0x07
#घोषणा AB8500_RTC_ALRM_MIN_LOW_REG	0x08
#घोषणा AB8500_RTC_ALRM_MIN_MID_REG	0x09
#घोषणा AB8500_RTC_ALRM_MIN_HI_REG	0x0A
#घोषणा AB8500_RTC_STAT_REG		0x0B
#घोषणा AB8500_RTC_BKUP_CHG_REG		0x0C
#घोषणा AB8500_RTC_FORCE_BKUP_REG	0x0D
#घोषणा AB8500_RTC_CALIB_REG		0x0E
#घोषणा AB8500_RTC_SWITCH_STAT_REG	0x0F

/* RtcReadRequest bits */
#घोषणा RTC_READ_REQUEST		0x01
#घोषणा RTC_WRITE_REQUEST		0x02

/* RtcCtrl bits */
#घोषणा RTC_ALARM_ENA			0x04
#घोषणा RTC_STATUS_DATA			0x01

#घोषणा COUNTS_PER_SEC			(0xF000 / 60)

अटल स्थिर u8 ab8500_rtc_समय_regs[] = अणु
	AB8500_RTC_WATCH_TMIN_HI_REG, AB8500_RTC_WATCH_TMIN_MID_REG,
	AB8500_RTC_WATCH_TMIN_LOW_REG, AB8500_RTC_WATCH_TSECHI_REG,
	AB8500_RTC_WATCH_TSECMID_REG
पूर्ण;

अटल स्थिर u8 ab8500_rtc_alarm_regs[] = अणु
	AB8500_RTC_ALRM_MIN_HI_REG, AB8500_RTC_ALRM_MIN_MID_REG,
	AB8500_RTC_ALRM_MIN_LOW_REG
पूर्ण;

अटल पूर्णांक ab8500_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	पूर्णांक retval, i;
	अचिन्हित दीर्घ mins, secs;
	अचिन्हित अक्षर buf[ARRAY_SIZE(ab8500_rtc_समय_regs)];
	u8 value;

	/* Request a data पढ़ो */
	retval = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev,
		AB8500_RTC, AB8500_RTC_READ_REQ_REG, RTC_READ_REQUEST);
	अगर (retval < 0)
		वापस retval;

	/* Wait क्रम some cycles after enabling the rtc पढ़ो in ab8500 */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		retval = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
			AB8500_RTC, AB8500_RTC_READ_REQ_REG, &value);
		अगर (retval < 0)
			वापस retval;

		अगर (!(value & RTC_READ_REQUEST))
			अवरोध;

		usleep_range(1000, 5000);
	पूर्ण

	/* Read the Watchसमय रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_rtc_समय_regs); i++) अणु
		retval = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev,
			AB8500_RTC, ab8500_rtc_समय_regs[i], &value);
		अगर (retval < 0)
			वापस retval;
		buf[i] = value;
	पूर्ण

	mins = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	secs =	(buf[3] << 8) | buf[4];
	secs =	secs / COUNTS_PER_SEC;
	secs =	secs + (mins * 60);

	rtc_समय64_to_पंचांग(secs, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक retval, i;
	अचिन्हित अक्षर buf[ARRAY_SIZE(ab8500_rtc_समय_regs)];
	अचिन्हित दीर्घ no_secs, no_mins, secs = 0;

	secs = rtc_पंचांग_to_समय64(पंचांग);

	no_mins = secs / 60;

	no_secs = secs % 60;
	/* Make the seconds count as per the RTC resolution */
	no_secs = no_secs * COUNTS_PER_SEC;

	buf[4] = no_secs & 0xFF;
	buf[3] = (no_secs >> 8) & 0xFF;

	buf[2] = no_mins & 0xFF;
	buf[1] = (no_mins >> 8) & 0xFF;
	buf[0] = (no_mins >> 16) & 0xFF;

	क्रम (i = 0; i < ARRAY_SIZE(ab8500_rtc_समय_regs); i++) अणु
		retval = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
			ab8500_rtc_समय_regs[i], buf[i]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	/* Request a data ग_लिखो */
	वापस abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
		AB8500_RTC_READ_REQ_REG, RTC_WRITE_REQUEST);
पूर्ण

अटल पूर्णांक ab8500_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक retval, i;
	u8 rtc_ctrl, value;
	अचिन्हित अक्षर buf[ARRAY_SIZE(ab8500_rtc_alarm_regs)];
	अचिन्हित दीर्घ secs, mins;

	/* Check अगर the alarm is enabled or not */
	retval = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, &rtc_ctrl);
	अगर (retval < 0)
		वापस retval;

	अगर (rtc_ctrl & RTC_ALARM_ENA)
		alarm->enabled = 1;
	अन्यथा
		alarm->enabled = 0;

	alarm->pending = 0;

	क्रम (i = 0; i < ARRAY_SIZE(ab8500_rtc_alarm_regs); i++) अणु
		retval = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
			ab8500_rtc_alarm_regs[i], &value);
		अगर (retval < 0)
			वापस retval;
		buf[i] = value;
	पूर्ण

	mins = (buf[0] << 16) | (buf[1] << 8) | (buf[2]);
	secs = mins * 60;

	rtc_समय64_to_पंचांग(secs, &alarm->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_rtc_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	वापस abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, RTC_ALARM_ENA,
		enabled ? RTC_ALARM_ENA : 0);
पूर्ण

अटल पूर्णांक ab8500_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक retval, i;
	अचिन्हित अक्षर buf[ARRAY_SIZE(ab8500_rtc_alarm_regs)];
	अचिन्हित दीर्घ mins, secs = 0, cursec = 0;
	काष्ठा rtc_समय curपंचांग;

	/* Get the number of seconds since 1970 */
	secs = rtc_पंचांग_to_समय64(&alarm->समय);

	/*
	 * Check whether alarm is set less than 1min.
	 * Since our RTC करोesn't support alarm resolution less than 1min,
	 * वापस -EINVAL, so UIE EMUL can take it up, inहाल of UIE_ON
	 */
	ab8500_rtc_पढ़ो_समय(dev, &curपंचांग); /* Read current समय */
	cursec = rtc_पंचांग_to_समय64(&curपंचांग);
	अगर ((secs - cursec) < 59) अणु
		dev_dbg(dev, "Alarm less than 1 minute not supported\r\n");
		वापस -EINVAL;
	पूर्ण

	mins = secs / 60;

	buf[2] = mins & 0xFF;
	buf[1] = (mins >> 8) & 0xFF;
	buf[0] = (mins >> 16) & 0xFF;

	/* Set the alarm समय */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_rtc_alarm_regs); i++) अणु
		retval = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
			ab8500_rtc_alarm_regs[i], buf[i]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	वापस ab8500_rtc_irq_enable(dev, alarm->enabled);
पूर्ण

अटल पूर्णांक ab8500_rtc_set_calibration(काष्ठा device *dev, पूर्णांक calibration)
अणु
	पूर्णांक retval;
	u8  rtccal = 0;

	/*
	 * Check that the calibration value (which is in units of 0.5
	 * parts-per-million) is in the AB8500's range क्रम RtcCalibration
	 * रेजिस्टर. -128 (0x80) is not permitted because the AB8500 uses
	 * a sign-bit rather than two's complement, so 0x80 is just another
	 * representation of zero.
	 */
	अगर ((calibration < -127) || (calibration > 127)) अणु
		dev_err(dev, "RtcCalibration value outside permitted range\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The AB8500 uses sign (in bit7) and magnitude (in bits0-7)
	 * so need to convert to this sort of representation beक्रमe writing
	 * पूर्णांकo RtcCalibration रेजिस्टर...
	 */
	अगर (calibration >= 0)
		rtccal = 0x7F & calibration;
	अन्यथा
		rtccal = ~(calibration - 1) | 0x80;

	retval = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
			AB8500_RTC_CALIB_REG, rtccal);

	वापस retval;
पूर्ण

अटल पूर्णांक ab8500_rtc_get_calibration(काष्ठा device *dev, पूर्णांक *calibration)
अणु
	पूर्णांक retval;
	u8  rtccal = 0;

	retval =  abx500_get_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_RTC,
			AB8500_RTC_CALIB_REG, &rtccal);
	अगर (retval >= 0) अणु
		/*
		 * The AB8500 uses sign (in bit7) and magnitude (in bits0-7)
		 * so need to convert value from RtcCalibration रेजिस्टर पूर्णांकo
		 * a two's complement चिन्हित value...
		 */
		अगर (rtccal & 0x80)
			*calibration = 0 - (rtccal & 0x7F);
		अन्यथा
			*calibration = 0x7F & rtccal;
	पूर्ण

	वापस retval;
पूर्ण

अटल sमाप_प्रकार ab8500_sysfs_store_rtc_calibration(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक retval;
	पूर्णांक calibration = 0;

	अगर (माला_पूछो(buf, " %i ", &calibration) != 1) अणु
		dev_err(dev, "Failed to store RTC calibration attribute\n");
		वापस -EINVAL;
	पूर्ण

	retval = ab8500_rtc_set_calibration(dev, calibration);

	वापस retval ? retval : count;
पूर्ण

अटल sमाप_प्रकार ab8500_sysfs_show_rtc_calibration(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक  retval = 0;
	पूर्णांक  calibration = 0;

	retval = ab8500_rtc_get_calibration(dev, &calibration);
	अगर (retval < 0) अणु
		dev_err(dev, "Failed to read RTC calibration attribute\n");
		प्र_लिखो(buf, "0\n");
		वापस retval;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", calibration);
पूर्ण

अटल DEVICE_ATTR(rtc_calibration, S_IRUGO | S_IWUSR,
		   ab8500_sysfs_show_rtc_calibration,
		   ab8500_sysfs_store_rtc_calibration);

अटल काष्ठा attribute *ab8500_rtc_attrs[] = अणु
	&dev_attr_rtc_calibration.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ab8500_rtc_sysfs_files = अणु
	.attrs	= ab8500_rtc_attrs,
पूर्ण;

अटल irqवापस_t rtc_alarm_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rtc_device *rtc = data;
	अचिन्हित दीर्घ events = RTC_IRQF | RTC_AF;

	dev_dbg(&rtc->dev, "%s\n", __func__);
	rtc_update_irq(rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ab8500_rtc_ops = अणु
	.पढ़ो_समय		= ab8500_rtc_पढ़ो_समय,
	.set_समय		= ab8500_rtc_set_समय,
	.पढ़ो_alarm		= ab8500_rtc_पढ़ो_alarm,
	.set_alarm		= ab8500_rtc_set_alarm,
	.alarm_irq_enable	= ab8500_rtc_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id ab85xx_rtc_ids[] = अणु
	अणु "ab8500-rtc", (kernel_uदीर्घ_t)&ab8500_rtc_ops, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, ab85xx_rtc_ids);

अटल पूर्णांक ab8500_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *platid = platक्रमm_get_device_id(pdev);
	पूर्णांक err;
	काष्ठा rtc_device *rtc;
	u8 rtc_ctrl;
	पूर्णांक irq;

	irq = platक्रमm_get_irq_byname(pdev, "ALARM");
	अगर (irq < 0)
		वापस irq;

	/* For RTC supply test */
	err = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(&pdev->dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, RTC_STATUS_DATA, RTC_STATUS_DATA);
	अगर (err < 0)
		वापस err;

	/* Wait क्रम reset by the PorRtc */
	usleep_range(1000, 5000);

	err = abx500_get_रेजिस्टर_पूर्णांकerruptible(&pdev->dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, &rtc_ctrl);
	अगर (err < 0)
		वापस err;

	/* Check अगर the RTC Supply fails */
	अगर (!(rtc_ctrl & RTC_STATUS_DATA)) अणु
		dev_err(&pdev->dev, "RTC supply failure\n");
		वापस -ENODEV;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = (काष्ठा rtc_class_ops *)platid->driver_data;

	err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
			rtc_alarm_handler, IRQF_ONESHOT,
			"ab8500-rtc", rtc);
	अगर (err < 0)
		वापस err;

	dev_pm_set_wake_irq(&pdev->dev, irq);
	platक्रमm_set_drvdata(pdev, rtc);

	rtc->uie_unsupported = 1;

	rtc->range_max = (1ULL << 24) * 60 - 1; // 24-bit minutes + 59 secs
	rtc->start_secs = RTC_TIMESTAMP_BEGIN_2000;
	rtc->set_start_समय = true;

	err = rtc_add_group(rtc, &ab8500_rtc_sysfs_files);
	अगर (err)
		वापस err;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल पूर्णांक ab8500_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ab8500_rtc_driver = अणु
	.driver = अणु
		.name = "ab8500-rtc",
	पूर्ण,
	.probe	= ab8500_rtc_probe,
	.हटाओ = ab8500_rtc_हटाओ,
	.id_table = ab85xx_rtc_ids,
पूर्ण;

module_platक्रमm_driver(ab8500_rtc_driver);

MODULE_AUTHOR("Virupax Sadashivpetimath <virupax.sadashivpetimath@stericsson.com>");
MODULE_DESCRIPTION("AB8500 RTC Driver");
MODULE_LICENSE("GPL v2");
