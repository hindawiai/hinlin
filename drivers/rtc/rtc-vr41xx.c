<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम NEC VR4100 series Real Time Clock unit.
 *
 *  Copyright (C) 2003-2008  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/compat.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/log2.h>

#समावेश <यंत्र/भाग64.h>

MODULE_AUTHOR("Yoichi Yuasa <yuasa@linux-mips.org>");
MODULE_DESCRIPTION("NEC VR4100 series RTC driver");
MODULE_LICENSE("GPL v2");

/* RTC 1 रेजिस्टरs */
#घोषणा ETIMELREG		0x00
#घोषणा ETIMEMREG		0x02
#घोषणा ETIMEHREG		0x04
/* RFU */
#घोषणा ECMPLREG		0x08
#घोषणा ECMPMREG		0x0a
#घोषणा ECMPHREG		0x0c
/* RFU */
#घोषणा RTCL1LREG		0x10
#घोषणा RTCL1HREG		0x12
#घोषणा RTCL1CNTLREG		0x14
#घोषणा RTCL1CNTHREG		0x16
#घोषणा RTCL2LREG		0x18
#घोषणा RTCL2HREG		0x1a
#घोषणा RTCL2CNTLREG		0x1c
#घोषणा RTCL2CNTHREG		0x1e

/* RTC 2 रेजिस्टरs */
#घोषणा TCLKLREG		0x00
#घोषणा TCLKHREG		0x02
#घोषणा TCLKCNTLREG		0x04
#घोषणा TCLKCNTHREG		0x06
/* RFU */
#घोषणा RTCINTREG		0x1e
 #घोषणा TCLOCK_INT		0x08
 #घोषणा RTCLONG2_INT		0x04
 #घोषणा RTCLONG1_INT		0x02
 #घोषणा ELAPSEDTIME_INT	0x01

#घोषणा RTC_FREQUENCY		32768
#घोषणा MAX_PERIODIC_RATE	6553

अटल व्योम __iomem *rtc1_base;
अटल व्योम __iomem *rtc2_base;

#घोषणा rtc1_पढ़ो(offset)		पढ़ोw(rtc1_base + (offset))
#घोषणा rtc1_ग_लिखो(offset, value)	ग_लिखोw((value), rtc1_base + (offset))

#घोषणा rtc2_पढ़ो(offset)		पढ़ोw(rtc2_base + (offset))
#घोषणा rtc2_ग_लिखो(offset, value)	ग_लिखोw((value), rtc2_base + (offset))

/* 32-bit compat क्रम ioctls that nobody अन्यथा uses */
#घोषणा RTC_EPOCH_READ32	_IOR('p', 0x0d, __u32)

अटल अचिन्हित दीर्घ epoch = 1970;	/* Jan 1 1970 00:00:00 */

अटल DEFINE_SPINLOCK(rtc_lock);
अटल अक्षर rtc_name[] = "RTC";
अटल अचिन्हित दीर्घ periodic_count;
अटल अचिन्हित पूर्णांक alarm_enabled;
अटल पूर्णांक aie_irq;
अटल पूर्णांक pie_irq;

अटल अंतरभूत समय64_t पढ़ो_elapsed_second(व्योम)
अणु

	अचिन्हित दीर्घ first_low, first_mid, first_high;

	अचिन्हित दीर्घ second_low, second_mid, second_high;

	करो अणु
		first_low = rtc1_पढ़ो(ETIMELREG);
		first_mid = rtc1_पढ़ो(ETIMEMREG);
		first_high = rtc1_पढ़ो(ETIMEHREG);
		second_low = rtc1_पढ़ो(ETIMELREG);
		second_mid = rtc1_पढ़ो(ETIMEMREG);
		second_high = rtc1_पढ़ो(ETIMEHREG);
	पूर्ण जबतक (first_low != second_low || first_mid != second_mid ||
		 first_high != second_high);

	वापस ((u64)first_high << 17) | (first_mid << 1) | (first_low >> 15);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_elapsed_second(समय64_t sec)
अणु
	spin_lock_irq(&rtc_lock);

	rtc1_ग_लिखो(ETIMELREG, (uपूर्णांक16_t)(sec << 15));
	rtc1_ग_लिखो(ETIMEMREG, (uपूर्णांक16_t)(sec >> 1));
	rtc1_ग_लिखो(ETIMEHREG, (uपूर्णांक16_t)(sec >> 17));

	spin_unlock_irq(&rtc_lock);
पूर्ण

अटल पूर्णांक vr41xx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	समय64_t epoch_sec, elapsed_sec;

	epoch_sec = स_गढ़ो64(epoch, 1, 1, 0, 0, 0);
	elapsed_sec = पढ़ो_elapsed_second();

	rtc_समय64_to_पंचांग(epoch_sec + elapsed_sec, समय);

	वापस 0;
पूर्ण

अटल पूर्णांक vr41xx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	समय64_t epoch_sec, current_sec;

	epoch_sec = स_गढ़ो64(epoch, 1, 1, 0, 0, 0);
	current_sec = rtc_पंचांग_to_समय64(समय);

	ग_लिखो_elapsed_second(current_sec - epoch_sec);

	वापस 0;
पूर्ण

अटल पूर्णांक vr41xx_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	अचिन्हित दीर्घ low, mid, high;
	काष्ठा rtc_समय *समय = &wkalrm->समय;

	spin_lock_irq(&rtc_lock);

	low = rtc1_पढ़ो(ECMPLREG);
	mid = rtc1_पढ़ो(ECMPMREG);
	high = rtc1_पढ़ो(ECMPHREG);
	wkalrm->enabled = alarm_enabled;

	spin_unlock_irq(&rtc_lock);

	rtc_समय64_to_पंचांग((high << 17) | (mid << 1) | (low >> 15), समय);

	वापस 0;
पूर्ण

अटल पूर्णांक vr41xx_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	समय64_t alarm_sec;

	alarm_sec = rtc_पंचांग_to_समय64(&wkalrm->समय);

	spin_lock_irq(&rtc_lock);

	अगर (alarm_enabled)
		disable_irq(aie_irq);

	rtc1_ग_लिखो(ECMPLREG, (uपूर्णांक16_t)(alarm_sec << 15));
	rtc1_ग_लिखो(ECMPMREG, (uपूर्णांक16_t)(alarm_sec >> 1));
	rtc1_ग_लिखो(ECMPHREG, (uपूर्णांक16_t)(alarm_sec >> 17));

	अगर (wkalrm->enabled)
		enable_irq(aie_irq);

	alarm_enabled = wkalrm->enabled;

	spin_unlock_irq(&rtc_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vr41xx_rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल RTC_EPOCH_READ:
		वापस put_user(epoch, (अचिन्हित दीर्घ __user *)arg);
#अगर_घोषित CONFIG_64BIT
	हाल RTC_EPOCH_READ32:
		वापस put_user(epoch, (अचिन्हित पूर्णांक __user *)arg);
#पूर्ण_अगर
	हाल RTC_EPOCH_SET:
		/* Doesn't support beक्रमe 1900 */
		अगर (arg < 1900)
			वापस -EINVAL;
		epoch = arg;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vr41xx_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	spin_lock_irq(&rtc_lock);
	अगर (enabled) अणु
		अगर (!alarm_enabled) अणु
			enable_irq(aie_irq);
			alarm_enabled = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (alarm_enabled) अणु
			disable_irq(aie_irq);
			alarm_enabled = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rtc_lock);
	वापस 0;
पूर्ण

अटल irqवापस_t elapsedसमय_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = (काष्ठा platक्रमm_device *)dev_id;
	काष्ठा rtc_device *rtc = platक्रमm_get_drvdata(pdev);

	rtc2_ग_लिखो(RTCINTREG, ELAPSEDTIME_INT);

	rtc_update_irq(rtc, 1, RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rtcदीर्घ1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = (काष्ठा platक्रमm_device *)dev_id;
	काष्ठा rtc_device *rtc = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ count = periodic_count;

	rtc2_ग_लिखो(RTCINTREG, RTCLONG1_INT);

	rtc1_ग_लिखो(RTCL1LREG, count);
	rtc1_ग_लिखो(RTCL1HREG, count >> 16);

	rtc_update_irq(rtc, 1, RTC_PF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops vr41xx_rtc_ops = अणु
	.ioctl			= vr41xx_rtc_ioctl,
	.पढ़ो_समय		= vr41xx_rtc_पढ़ो_समय,
	.set_समय		= vr41xx_rtc_set_समय,
	.पढ़ो_alarm		= vr41xx_rtc_पढ़ो_alarm,
	.set_alarm		= vr41xx_rtc_set_alarm,
	.alarm_irq_enable	= vr41xx_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा rtc_device *rtc;
	पूर्णांक retval;

	अगर (pdev->num_resources != 4)
		वापस -EBUSY;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EBUSY;

	rtc1_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!rtc1_base)
		वापस -EBUSY;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		retval = -EBUSY;
		जाओ err_rtc1_iounmap;
	पूर्ण

	rtc2_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!rtc2_base) अणु
		retval = -EBUSY;
		जाओ err_rtc1_iounmap;
	पूर्ण

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc)) अणु
		retval = PTR_ERR(rtc);
		जाओ err_iounmap_all;
	पूर्ण

	rtc->ops = &vr41xx_rtc_ops;

	/* 48-bit counter at 32.768 kHz */
	rtc->range_max = (1ULL << 33) - 1;
	rtc->max_user_freq = MAX_PERIODIC_RATE;

	spin_lock_irq(&rtc_lock);

	rtc1_ग_लिखो(ECMPLREG, 0);
	rtc1_ग_लिखो(ECMPMREG, 0);
	rtc1_ग_लिखो(ECMPHREG, 0);
	rtc1_ग_लिखो(RTCL1LREG, 0);
	rtc1_ग_लिखो(RTCL1HREG, 0);

	spin_unlock_irq(&rtc_lock);

	aie_irq = platक्रमm_get_irq(pdev, 0);
	अगर (aie_irq <= 0) अणु
		retval = -EBUSY;
		जाओ err_iounmap_all;
	पूर्ण

	retval = devm_request_irq(&pdev->dev, aie_irq, elapsedसमय_पूर्णांकerrupt, 0,
				"elapsed_time", pdev);
	अगर (retval < 0)
		जाओ err_iounmap_all;

	pie_irq = platक्रमm_get_irq(pdev, 1);
	अगर (pie_irq <= 0) अणु
		retval = -EBUSY;
		जाओ err_iounmap_all;
	पूर्ण

	retval = devm_request_irq(&pdev->dev, pie_irq, rtcदीर्घ1_पूर्णांकerrupt, 0,
				"rtclong1", pdev);
	अगर (retval < 0)
		जाओ err_iounmap_all;

	platक्रमm_set_drvdata(pdev, rtc);

	disable_irq(aie_irq);
	disable_irq(pie_irq);

	dev_info(&pdev->dev, "Real Time Clock of NEC VR4100 series\n");

	retval = devm_rtc_रेजिस्टर_device(rtc);
	अगर (retval)
		जाओ err_iounmap_all;

	वापस 0;

err_iounmap_all:
	rtc2_base = शून्य;

err_rtc1_iounmap:
	rtc1_base = शून्य;

	वापस retval;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:RTC");

अटल काष्ठा platक्रमm_driver rtc_platक्रमm_driver = अणु
	.probe		= rtc_probe,
	.driver		= अणु
		.name	= rtc_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rtc_platक्रमm_driver);
