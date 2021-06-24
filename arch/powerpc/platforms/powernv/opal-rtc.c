<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV Real Time Clock.
 *
 * Copyright 2011 IBM Corp.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/machdep.h>

अटल व्योम opal_to_पंचांग(u32 y_m_d, u64 h_m_s_ms, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_year	= ((bcd2bin(y_m_d >> 24) * 100) +
			   bcd2bin((y_m_d >> 16) & 0xff)) - 1900;
	पंचांग->पंचांग_mon	= bcd2bin((y_m_d >> 8) & 0xff) - 1;
	पंचांग->पंचांग_mday	= bcd2bin(y_m_d & 0xff);
	पंचांग->पंचांग_hour	= bcd2bin((h_m_s_ms >> 56) & 0xff);
	पंचांग->पंचांग_min	= bcd2bin((h_m_s_ms >> 48) & 0xff);
	पंचांग->पंचांग_sec	= bcd2bin((h_m_s_ms >> 40) & 0xff);
	पंचांग->पंचांग_wday     = -1;
पूर्ण

समय64_t __init opal_get_boot_समय(व्योम)
अणु
	काष्ठा rtc_समय पंचांग;
	u32 y_m_d;
	u64 h_m_s_ms;
	__be32 __y_m_d;
	__be64 __h_m_s_ms;
	दीर्घ rc = OPAL_BUSY;

	अगर (!opal_check_token(OPAL_RTC_READ))
		वापस 0;

	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_rtc_पढ़ो(&__y_m_d, &__h_m_s_ms);
		अगर (rc == OPAL_BUSY_EVENT) अणु
			mdelay(OPAL_BUSY_DELAY_MS);
			opal_poll_events(शून्य);
		पूर्ण अन्यथा अगर (rc == OPAL_BUSY) अणु
			mdelay(OPAL_BUSY_DELAY_MS);
		पूर्ण
	पूर्ण
	अगर (rc != OPAL_SUCCESS)
		वापस 0;

	y_m_d = be32_to_cpu(__y_m_d);
	h_m_s_ms = be64_to_cpu(__h_m_s_ms);
	opal_to_पंचांग(y_m_d, h_m_s_ms, &पंचांग);
	वापस rtc_पंचांग_to_समय64(&पंचांग);
पूर्ण

अटल __init पूर्णांक opal_समय_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *rtc;

	rtc = of_find_node_by_path("/ibm,opal/rtc");
	अगर (rtc) अणु
		pdev = of_platक्रमm_device_create(rtc, "opal-rtc", शून्य);
		of_node_put(rtc);
	पूर्ण अन्यथा अणु
		अगर (opal_check_token(OPAL_RTC_READ) ||
		    opal_check_token(OPAL_READ_TPO))
			pdev = platक्रमm_device_रेजिस्टर_simple("opal-rtc", -1,
							       शून्य, 0);
		अन्यथा
			वापस -ENODEV;
	पूर्ण

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण
machine_subsys_initcall(घातernv, opal_समय_init);
