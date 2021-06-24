<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC पूर्णांकerface क्रम Wilco Embedded Controller with R/W abilities
 *
 * Copyright 2018 Google LLC
 *
 * The corresponding platक्रमm device is typically रेजिस्टरed in
 * drivers/platक्रमm/chrome/wilco_ec/core.c
 */

#समावेश <linux/bcd.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/rtc.h>
#समावेश <linux/समयkeeping.h>

#घोषणा EC_COMMAND_CMOS			0x7c
#घोषणा EC_CMOS_TOD_WRITE		0x02
#घोषणा EC_CMOS_TOD_READ		0x08

/* Message sent to the EC to request the current समय. */
काष्ठा ec_rtc_पढ़ो_request अणु
	u8 command;
	u8 reserved;
	u8 param;
पूर्ण __packed;
अटल काष्ठा ec_rtc_पढ़ो_request पढ़ो_rq = अणु
	.command = EC_COMMAND_CMOS,
	.param = EC_CMOS_TOD_READ,
पूर्ण;

/**
 * काष्ठा ec_rtc_पढ़ो_response - Format of RTC वापसed by EC.
 * @reserved: Unused byte
 * @second: Second value (0..59)
 * @minute: Minute value (0..59)
 * @hour: Hour value (0..23)
 * @day: Day value (1..31)
 * @month: Month value (1..12)
 * @year: Year value (full year % 100)
 * @century: Century value (full year / 100)
 *
 * All values are presented in binary (not BCD).
 */
काष्ठा ec_rtc_पढ़ो_response अणु
	u8 reserved;
	u8 second;
	u8 minute;
	u8 hour;
	u8 day;
	u8 month;
	u8 year;
	u8 century;
पूर्ण __packed;

/**
 * काष्ठा ec_rtc_ग_लिखो_request - Format of RTC sent to the EC.
 * @command: Always EC_COMMAND_CMOS
 * @reserved: Unused byte
 * @param: Always EC_CMOS_TOD_WRITE
 * @century: Century value (full year / 100)
 * @year: Year value (full year % 100)
 * @month: Month value (1..12)
 * @day: Day value (1..31)
 * @hour: Hour value (0..23)
 * @minute: Minute value (0..59)
 * @second: Second value (0..59)
 * @weekday: Day of the week (0=Saturday)
 *
 * All values are presented in BCD.
 */
काष्ठा ec_rtc_ग_लिखो_request अणु
	u8 command;
	u8 reserved;
	u8 param;
	u8 century;
	u8 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
	u8 weekday;
पूर्ण __packed;

अटल पूर्णांक wilco_ec_rtc_पढ़ो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(dev->parent);
	काष्ठा ec_rtc_पढ़ो_response rtc;
	काष्ठा wilco_ec_message msg;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = &पढ़ो_rq;
	msg.request_size = माप(पढ़ो_rq);
	msg.response_data = &rtc;
	msg.response_size = माप(rtc);

	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0)
		वापस ret;

	पंचांग->पंचांग_sec	= rtc.second;
	पंचांग->पंचांग_min	= rtc.minute;
	पंचांग->पंचांग_hour	= rtc.hour;
	पंचांग->पंचांग_mday	= rtc.day;
	पंचांग->पंचांग_mon	= rtc.month - 1;
	पंचांग->पंचांग_year	= rtc.year + (rtc.century * 100) - 1900;
	/* Ignore other पंचांग fields, man rtc says userspace shouldn't use them. */

	अगर (rtc_valid_पंचांग(पंचांग)) अणु
		dev_err(dev, "Time from RTC is invalid: %ptRr\n", पंचांग);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilco_ec_rtc_ग_लिखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(dev->parent);
	काष्ठा ec_rtc_ग_लिखो_request rtc;
	काष्ठा wilco_ec_message msg;
	पूर्णांक year = पंचांग->पंचांग_year + 1900;
	/*
	 * Convert from 0=Sunday to 0=Saturday क्रम the EC
	 * We DO need to set weekday because the EC controls battery अक्षरging
	 * schedules that depend on the day of the week.
	 */
	पूर्णांक wday = पंचांग->पंचांग_wday == 6 ? 0 : पंचांग->पंचांग_wday + 1;
	पूर्णांक ret;

	rtc.command	= EC_COMMAND_CMOS;
	rtc.param	= EC_CMOS_TOD_WRITE;
	rtc.century	= bin2bcd(year / 100);
	rtc.year	= bin2bcd(year % 100);
	rtc.month	= bin2bcd(पंचांग->पंचांग_mon + 1);
	rtc.day		= bin2bcd(पंचांग->पंचांग_mday);
	rtc.hour	= bin2bcd(पंचांग->पंचांग_hour);
	rtc.minute	= bin2bcd(पंचांग->पंचांग_min);
	rtc.second	= bin2bcd(पंचांग->पंचांग_sec);
	rtc.weekday	= bin2bcd(wday);

	स_रखो(&msg, 0, माप(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = &rtc;
	msg.request_size = माप(rtc);

	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops wilco_ec_rtc_ops = अणु
	.पढ़ो_समय = wilco_ec_rtc_पढ़ो,
	.set_समय = wilco_ec_rtc_ग_लिखो,
पूर्ण;

अटल पूर्णांक wilco_ec_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &wilco_ec_rtc_ops;
	/* EC only supports this century */
	rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->range_max = RTC_TIMESTAMP_END_2099;
	rtc->owner = THIS_MODULE;

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver wilco_ec_rtc_driver = अणु
	.driver = अणु
		.name = "rtc-wilco-ec",
	पूर्ण,
	.probe = wilco_ec_rtc_probe,
पूर्ण;

module_platक्रमm_driver(wilco_ec_rtc_driver);

MODULE_ALIAS("platform:rtc-wilco-ec");
MODULE_AUTHOR("Nick Crews <ncrews@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Wilco EC RTC driver");
