<शैली गुरु>
/*
 * Au1xxx counter0 (aka Time-Of-Year counter) RTC पूर्णांकerface driver.
 *
 * Copyright (C) 2008 Manuel Lauss <mano@roarinelk.homelinux.net>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

/* All current Au1xxx SoCs have 2 counters fed by an बाह्यal 32.768 kHz
 * crystal. Counter 0, which keeps counting during sleep/घातerकरोwn, is
 * used to count seconds since the beginning of the unix epoch.
 *
 * The counters must be configured and enabled by bootloader/board code;
 * no checks as to whether they really get a proper 32.768kHz घड़ी are
 * made as this would take far too दीर्घ.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mach-au1x00/au1000.h>

/* 32kHz घड़ी enabled and detected */
#घोषणा CNTR_OK (SYS_CNTRL_E0 | SYS_CNTRL_32S)

अटल पूर्णांक au1xtoy_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ t;

	t = alchemy_rdsys(AU1000_SYS_TOYREAD);

	rtc_समय64_to_पंचांग(t, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक au1xtoy_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ t;

	t = rtc_पंचांग_to_समय64(पंचांग);

	alchemy_wrsys(t, AU1000_SYS_TOYWRITE);

	/* रुको क्रम the pending रेजिस्टर ग_लिखो to succeed.  This can
	 * take up to 6 seconds...
	 */
	जबतक (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_C0S)
		msleep(1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops au1xtoy_rtc_ops = अणु
	.पढ़ो_समय	= au1xtoy_rtc_पढ़ो_समय,
	.set_समय	= au1xtoy_rtc_set_समय,
पूर्ण;

अटल पूर्णांक au1xtoy_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtcdev;
	अचिन्हित दीर्घ t;

	t = alchemy_rdsys(AU1000_SYS_CNTRCTRL);
	अगर (!(t & CNTR_OK)) अणु
		dev_err(&pdev->dev, "counters not working; aborting.\n");
		वापस -ENODEV;
	पूर्ण

	/* set counter0 tickrate to 1Hz अगर necessary */
	अगर (alchemy_rdsys(AU1000_SYS_TOYTRIM) != 32767) अणु
		/* रुको until hardware gives access to TRIM रेजिस्टर */
		t = 0x00100000;
		जबतक ((alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_T0S) && --t)
			msleep(1);

		अगर (!t) अणु
			/* समयd out रुकोing क्रम रेजिस्टर access; assume
			 * counters are unusable.
			 */
			dev_err(&pdev->dev, "timeout waiting for access\n");
			वापस -ETIMEDOUT;
		पूर्ण

		/* set 1Hz TOY tick rate */
		alchemy_wrsys(32767, AU1000_SYS_TOYTRIM);
	पूर्ण

	/* रुको until the hardware allows ग_लिखोs to the counter reg */
	जबतक (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_C0S)
		msleep(1);

	rtcdev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtcdev))
		वापस PTR_ERR(rtcdev);

	rtcdev->ops = &au1xtoy_rtc_ops;
	rtcdev->range_max = U32_MAX;

	platक्रमm_set_drvdata(pdev, rtcdev);

	वापस devm_rtc_रेजिस्टर_device(rtcdev);
पूर्ण

अटल काष्ठा platक्रमm_driver au1xrtc_driver = अणु
	.driver		= अणु
		.name	= "rtc-au1xxx",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(au1xrtc_driver, au1xtoy_rtc_probe);

MODULE_DESCRIPTION("Au1xxx TOY-counter-based RTC driver");
MODULE_AUTHOR("Manuel Lauss <manuel.lauss@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-au1xxx");
