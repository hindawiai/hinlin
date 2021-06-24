<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM OPAL RTC driver
 * Copyright (C) 2014 IBM
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRVNAME		"rtc-opal"

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/firmware.h>

अटल व्योम opal_to_पंचांग(u32 y_m_d, u64 h_m_s_ms, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_year = ((bcd2bin(y_m_d >> 24) * 100) +
		       bcd2bin((y_m_d >> 16) & 0xff)) - 1900;
	पंचांग->पंचांग_mon  = bcd2bin((y_m_d >> 8) & 0xff) - 1;
	पंचांग->पंचांग_mday = bcd2bin(y_m_d & 0xff);
	पंचांग->पंचांग_hour = bcd2bin((h_m_s_ms >> 56) & 0xff);
	पंचांग->पंचांग_min  = bcd2bin((h_m_s_ms >> 48) & 0xff);
	पंचांग->पंचांग_sec  = bcd2bin((h_m_s_ms >> 40) & 0xff);

	पंचांग->पंचांग_wday = -1;
पूर्ण

अटल व्योम पंचांग_to_opal(काष्ठा rtc_समय *पंचांग, u32 *y_m_d, u64 *h_m_s_ms)
अणु
	*y_m_d |= ((u32)bin2bcd((पंचांग->पंचांग_year + 1900) / 100)) << 24;
	*y_m_d |= ((u32)bin2bcd((पंचांग->पंचांग_year + 1900) % 100)) << 16;
	*y_m_d |= ((u32)bin2bcd((पंचांग->पंचांग_mon + 1))) << 8;
	*y_m_d |= ((u32)bin2bcd(पंचांग->पंचांग_mday));

	*h_m_s_ms |= ((u64)bin2bcd(पंचांग->पंचांग_hour)) << 56;
	*h_m_s_ms |= ((u64)bin2bcd(पंचांग->पंचांग_min)) << 48;
	*h_m_s_ms |= ((u64)bin2bcd(पंचांग->पंचांग_sec)) << 40;
पूर्ण

अटल पूर्णांक opal_get_rtc_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	s64 rc = OPAL_BUSY;
	पूर्णांक retries = 10;
	u32 y_m_d;
	u64 h_m_s_ms;
	__be32 __y_m_d;
	__be64 __h_m_s_ms;

	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_rtc_पढ़ो(&__y_m_d, &__h_m_s_ms);
		अगर (rc == OPAL_BUSY_EVENT) अणु
			msleep(OPAL_BUSY_DELAY_MS);
			opal_poll_events(शून्य);
		पूर्ण अन्यथा अगर (rc == OPAL_BUSY) अणु
			msleep(OPAL_BUSY_DELAY_MS);
		पूर्ण अन्यथा अगर (rc == OPAL_HARDWARE || rc == OPAL_INTERNAL_ERROR) अणु
			अगर (retries--) अणु
				msleep(10); /* Wait 10ms beक्रमe retry */
				rc = OPAL_BUSY; /* go around again */
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rc != OPAL_SUCCESS)
		वापस -EIO;

	y_m_d = be32_to_cpu(__y_m_d);
	h_m_s_ms = be64_to_cpu(__h_m_s_ms);
	opal_to_पंचांग(y_m_d, h_m_s_ms, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक opal_set_rtc_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	s64 rc = OPAL_BUSY;
	पूर्णांक retries = 10;
	u32 y_m_d = 0;
	u64 h_m_s_ms = 0;

	पंचांग_to_opal(पंचांग, &y_m_d, &h_m_s_ms);

	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_rtc_ग_लिखो(y_m_d, h_m_s_ms);
		अगर (rc == OPAL_BUSY_EVENT) अणु
			msleep(OPAL_BUSY_DELAY_MS);
			opal_poll_events(शून्य);
		पूर्ण अन्यथा अगर (rc == OPAL_BUSY) अणु
			msleep(OPAL_BUSY_DELAY_MS);
		पूर्ण अन्यथा अगर (rc == OPAL_HARDWARE || rc == OPAL_INTERNAL_ERROR) अणु
			अगर (retries--) अणु
				msleep(10); /* Wait 10ms beक्रमe retry */
				rc = OPAL_BUSY; /* go around again */
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc == OPAL_SUCCESS ? 0 : -EIO;
पूर्ण

/*
 * TPO	Timed Power-On
 *
 * TPO get/set OPAL calls care about the hour and min and to make it consistent
 * with the rtc utility समय conversion functions, we use the 'u64' to store
 * its value and perक्रमm bit shअगरt by 32 beक्रमe use..
 */
अटल पूर्णांक opal_get_tpo_समय(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	__be32 __y_m_d, __h_m;
	काष्ठा opal_msg msg;
	पूर्णांक rc, token;
	u64 h_m_s_ms;
	u32 y_m_d;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			pr_err("Failed to get the async token\n");

		वापस token;
	पूर्ण

	rc = opal_tpo_पढ़ो(token, &__y_m_d, &__h_m);
	अगर (rc != OPAL_ASYNC_COMPLETION) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	rc = opal_async_रुको_response(token, &msg);
	अगर (rc) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	rc = opal_get_async_rc(msg);
	अगर (rc != OPAL_SUCCESS) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	y_m_d = be32_to_cpu(__y_m_d);
	h_m_s_ms = ((u64)be32_to_cpu(__h_m) << 32);

	/* check अगर no alarm is set */
	अगर (y_m_d == 0 && h_m_s_ms == 0) अणु
		pr_debug("No alarm is set\n");
		rc = -ENOENT;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		pr_debug("Alarm set to %x %llx\n", y_m_d, h_m_s_ms);
	पूर्ण

	opal_to_पंचांग(y_m_d, h_m_s_ms, &alarm->समय);

निकास:
	opal_async_release_token(token);
	वापस rc;
पूर्ण

/* Set Timed Power-On */
अटल पूर्णांक opal_set_tpo_समय(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	u64 h_m_s_ms = 0;
	काष्ठा opal_msg msg;
	u32 y_m_d = 0;
	पूर्णांक token, rc;

	/* अगर alarm is enabled */
	अगर (alarm->enabled) अणु
		पंचांग_to_opal(&alarm->समय, &y_m_d, &h_m_s_ms);
		pr_debug("Alarm set to %x %llx\n", y_m_d, h_m_s_ms);

	पूर्ण अन्यथा अणु
		pr_debug("Alarm getting disabled\n");
	पूर्ण

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			pr_err("Failed to get the async token\n");

		वापस token;
	पूर्ण

	/* TPO, we care about hour and minute */
	rc = opal_tpo_ग_लिखो(token, y_m_d,
			    (u32)((h_m_s_ms >> 32) & 0xffff0000));
	अगर (rc != OPAL_ASYNC_COMPLETION) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	rc = opal_async_रुको_response(token, &msg);
	अगर (rc) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	rc = opal_get_async_rc(msg);
	अगर (rc != OPAL_SUCCESS)
		rc = -EIO;

निकास:
	opal_async_release_token(token);
	वापस rc;
पूर्ण

अटल पूर्णांक opal_tpo_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rtc_wkalrm alarm = अणु .enabled = 0 पूर्ण;

	/*
	 * TPO is स्वतःmatically enabled when opal_set_tpo_समय() is called with
	 * non-zero rtc-समय. We only handle disable हाल which needs to be
	 * explicitly told to opal.
	 */
	वापस enabled ? 0 : opal_set_tpo_समय(dev, &alarm);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops opal_rtc_ops = अणु
	.पढ़ो_समय	= opal_get_rtc_समय,
	.set_समय	= opal_set_rtc_समय,
	.पढ़ो_alarm	= opal_get_tpo_समय,
	.set_alarm	= opal_set_tpo_समय,
	.alarm_irq_enable = opal_tpo_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक opal_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	अगर (pdev->dev.of_node &&
	    (of_property_पढ़ो_bool(pdev->dev.of_node, "wakeup-source") ||
	     of_property_पढ़ो_bool(pdev->dev.of_node, "has-tpo")/* legacy */))
		device_set_wakeup_capable(&pdev->dev, true);
	अन्यथा
		clear_bit(RTC_FEATURE_ALARM, rtc->features);

	rtc->ops = &opal_rtc_ops;
	rtc->range_min = RTC_TIMESTAMP_BEGIN_0000;
	rtc->range_max = RTC_TIMESTAMP_END_9999;
	rtc->uie_unsupported = 1;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल स्थिर काष्ठा of_device_id opal_rtc_match[] = अणु
	अणु
		.compatible	= "ibm,opal-rtc",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, opal_rtc_match);

अटल स्थिर काष्ठा platक्रमm_device_id opal_rtc_driver_ids[] = अणु
	अणु
		.name		= "opal-rtc",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, opal_rtc_driver_ids);

अटल काष्ठा platक्रमm_driver opal_rtc_driver = अणु
	.probe		= opal_rtc_probe,
	.id_table	= opal_rtc_driver_ids,
	.driver		= अणु
		.name		= DRVNAME,
		.of_match_table	= opal_rtc_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init opal_rtc_init(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&opal_rtc_driver);
पूर्ण

अटल व्योम __निकास opal_rtc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&opal_rtc_driver);
पूर्ण

MODULE_AUTHOR("Neelesh Gupta <neelegup@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("IBM OPAL RTC driver");
MODULE_LICENSE("GPL");

module_init(opal_rtc_init);
module_निकास(opal_rtc_निकास);
