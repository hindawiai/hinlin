<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/rtc.c
 *
 *  Copyright (C) 1991, 1992, 1995, 1999, 2000  Linus Torvalds
 *
 * This file contains date handling.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "proto.h"


/*
 * Support क्रम the RTC device.
 *
 * We करोn't want to use the rtc-cmos driver, because we don't want to support
 * alarms, as that would be indistinguishable from समयr पूर्णांकerrupts.
 *
 * Further, generic code is really, really tied to a 1900 epoch.  This is
 * true in __get_rtc_समय as well as the users of काष्ठा rtc_समय e.g.
 * rtc_पंचांग_to_समय.  Thankfully all of the other epochs in use are later
 * than 1900, and so it's easy to adjust.
 */

अटल अचिन्हित दीर्घ rtc_epoch;

अटल पूर्णांक __init
specअगरiy_epoch(अक्षर *str)
अणु
	अचिन्हित दीर्घ epoch = simple_म_से_अदीर्घ(str, शून्य, 0);
	अगर (epoch < 1900)
		prपूर्णांकk("Ignoring invalid user specified epoch %lu\n", epoch);
	अन्यथा
		rtc_epoch = epoch;
	वापस 1;
पूर्ण
__setup("epoch=", specअगरiy_epoch);

अटल व्योम __init
init_rtc_epoch(व्योम)
अणु
	पूर्णांक epoch, year, ctrl;

	अगर (rtc_epoch != 0) अणु
		/* The epoch was specअगरied on the command-line.  */
		वापस;
	पूर्ण

	/* Detect the epoch in use on this computer.  */
	ctrl = CMOS_READ(RTC_CONTROL);
	year = CMOS_READ(RTC_YEAR);
	अगर (!(ctrl & RTC_DM_BINARY) || RTC_ALWAYS_BCD)
		year = bcd2bin(year);

	/* PC-like is standard; used क्रम year >= 70 */
	epoch = 1900;
	अगर (year < 20) अणु
		epoch = 2000;
	पूर्ण अन्यथा अगर (year >= 20 && year < 48) अणु
		/* NT epoch */
		epoch = 1980;
	पूर्ण अन्यथा अगर (year >= 48 && year < 70) अणु
		/* Digital UNIX epoch */
		epoch = 1952;
	पूर्ण
	rtc_epoch = epoch;

	prपूर्णांकk(KERN_INFO "Using epoch %d for rtc year %d\n", epoch, year);
पूर्ण

अटल पूर्णांक
alpha_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	mc146818_get_समय(पंचांग);

	/* Adjust क्रम non-शेष epochs.  It's easier to depend on the
	   generic __get_rtc_समय and adjust the epoch here than create
	   a copy of __get_rtc_समय with the edits we need.  */
	अगर (rtc_epoch != 1900) अणु
		पूर्णांक year = पंचांग->पंचांग_year;
		/* Unकरो the century adjusपंचांगent made in __get_rtc_समय.  */
		अगर (year >= 100)
			year -= 100;
		year += rtc_epoch - 1900;
		/* Reकरो the century adjusपंचांगent with the epoch in place.  */
		अगर (year <= 69)
			year += 100;
		पंचांग->पंचांग_year = year;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
alpha_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_समय xपंचांग;

	अगर (rtc_epoch != 1900) अणु
		xपंचांग = *पंचांग;
		xपंचांग.पंचांग_year -= rtc_epoch - 1900;
		पंचांग = &xपंचांग;
	पूर्ण

	वापस mc146818_set_समय(पंचांग);
पूर्ण

अटल पूर्णांक
alpha_rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल RTC_EPOCH_READ:
		वापस put_user(rtc_epoch, (अचिन्हित दीर्घ __user *)arg);
	हाल RTC_EPOCH_SET:
		अगर (arg < 1900)
			वापस -EINVAL;
		rtc_epoch = arg;
		वापस 0;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops alpha_rtc_ops = अणु
	.पढ़ो_समय = alpha_rtc_पढ़ो_समय,
	.set_समय = alpha_rtc_set_समय,
	.ioctl = alpha_rtc_ioctl,
पूर्ण;

/*
 * Similarly, except करो the actual CMOS access on the boot cpu only.
 * This requires marshalling the data across an पूर्णांकerprocessor call.
 */

#अगर defined(CONFIG_SMP) && \
    (defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_MARVEL))
# define HAVE_REMOTE_RTC 1

जोड़ remote_data अणु
	काष्ठा rtc_समय *पंचांग;
	दीर्घ retval;
पूर्ण;

अटल व्योम
करो_remote_पढ़ो(व्योम *data)
अणु
	जोड़ remote_data *x = data;
	x->retval = alpha_rtc_पढ़ो_समय(शून्य, x->पंचांग);
पूर्ण

अटल पूर्णांक
remote_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	जोड़ remote_data x;
	अगर (smp_processor_id() != boot_cpuid) अणु
		x.पंचांग = पंचांग;
		smp_call_function_single(boot_cpuid, करो_remote_पढ़ो, &x, 1);
		वापस x.retval;
	पूर्ण
	वापस alpha_rtc_पढ़ो_समय(शून्य, पंचांग);
पूर्ण

अटल व्योम
करो_remote_set(व्योम *data)
अणु
	जोड़ remote_data *x = data;
	x->retval = alpha_rtc_set_समय(शून्य, x->पंचांग);
पूर्ण

अटल पूर्णांक
remote_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	जोड़ remote_data x;
	अगर (smp_processor_id() != boot_cpuid) अणु
		x.पंचांग = पंचांग;
		smp_call_function_single(boot_cpuid, करो_remote_set, &x, 1);
		वापस x.retval;
	पूर्ण
	वापस alpha_rtc_set_समय(शून्य, पंचांग);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops remote_rtc_ops = अणु
	.पढ़ो_समय = remote_पढ़ो_समय,
	.set_समय = remote_set_समय,
	.ioctl = alpha_rtc_ioctl,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init
alpha_rtc_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा rtc_device *rtc;

	init_rtc_epoch();

	pdev = platक्रमm_device_रेजिस्टर_simple("rtc-alpha", -1, शून्य, 0);
	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	platक्रमm_set_drvdata(pdev, rtc);
	rtc->ops = &alpha_rtc_ops;

#अगर_घोषित HAVE_REMOTE_RTC
	अगर (alpha_mv.rtc_boot_cpu_only)
		rtc->ops = &remote_rtc_ops;
#पूर्ण_अगर

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण
device_initcall(alpha_rtc_init);
