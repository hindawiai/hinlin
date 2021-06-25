<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/m68k/kernel/समय.c
 *
 *  Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *
 * This file contains the m68k-specअगरic समय handling details.
 * Most of the stuff is located in the machine specअगरic files.
 *
 * 1997-09-10	Updated NTP code according to technical memoअक्रमum Jan '96
 *		"A Kernel Model for Precision Timekeeping" by Dave Mills
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq_regs.h>

#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/profile.h>


अचिन्हित दीर्घ (*mach_अक्रमom_get_entropy)(व्योम);
EXPORT_SYMBOL_GPL(mach_अक्रमom_get_entropy);

#अगर_घोषित CONFIG_HEARTBEAT
व्योम समयr_heartbeat(व्योम)
अणु
	/* use घातer LED as a heartbeat instead -- much more useful
	   क्रम debugging -- based on the version क्रम PReP by Cort */
	/* acts like an actual heart beat -- ie thump-thump-छोड़ो... */
	अगर (mach_heartbeat) अणु
	    अटल अचिन्हित cnt = 0, period = 0, dist = 0;

	    अगर (cnt == 0 || cnt == dist)
		mach_heartbeat( 1 );
	    अन्यथा अगर (cnt == 7 || cnt == dist+7)
		mach_heartbeat( 0 );

	    अगर (++cnt > period) अणु
		cnt = 0;
		/* The hyperbolic function below modअगरies the heartbeat period
		 * length in dependency of the current (5min) load. It goes
		 * through the poपूर्णांकs f(0)=126, f(1)=86, f(5)=51,
		 * f(inf)->30. */
		period = ((672<<FSHIFT)/(5*avenrun[0]+(7<<FSHIFT))) + 30;
		dist = period / 4;
	    पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HEARTBEAT */

#अगर_घोषित CONFIG_M68KCLASSIC
#अगर !IS_BUILTIN(CONFIG_RTC_DRV_GENERIC)
व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा rtc_समय समय;

	ts->tv_sec = 0;
	ts->tv_nsec = 0;

	अगर (!mach_hwclk)
		वापस;

	mach_hwclk(0, &समय);

	ts->tv_sec = स_गढ़ो64(समय.पंचांग_year + 1900, समय.पंचांग_mon + 1, समय.पंचांग_mday,
			      समय.पंचांग_hour, समय.पंचांग_min, समय.पंचांग_sec);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RTC_DRV_GENERIC)
अटल पूर्णांक rtc_generic_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	mach_hwclk(0, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक rtc_generic_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अगर (mach_hwclk(1, पंचांग) < 0)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल पूर्णांक rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rtc_pll_info pll;
	काष्ठा rtc_pll_info __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल RTC_PLL_GET:
		अगर (!mach_get_rtc_pll || mach_get_rtc_pll(&pll))
			वापस -EINVAL;
		वापस copy_to_user(argp, &pll, माप pll) ? -EFAULT : 0;

	हाल RTC_PLL_SET:
		अगर (!mach_set_rtc_pll)
			वापस -EINVAL;
		अगर (!capable(CAP_SYS_TIME))
			वापस -EACCES;
		अगर (copy_from_user(&pll, argp, माप(pll)))
			वापस -EFAULT;
		वापस mach_set_rtc_pll(&pll);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops generic_rtc_ops = अणु
	.ioctl = rtc_ioctl,
	.पढ़ो_समय = rtc_generic_get_समय,
	.set_समय = rtc_generic_set_समय,
पूर्ण;

अटल पूर्णांक __init rtc_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!mach_hwclk)
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "rtc-generic", -1,
					     &generic_rtc_ops,
					     माप(generic_rtc_ops));
	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

module_init(rtc_init);
#पूर्ण_अगर /* CONFIG_RTC_DRV_GENERIC */
#पूर्ण_अगर /* CONFIG M68KCLASSIC */

व्योम __init समय_init(व्योम)
अणु
	mach_sched_init();
पूर्ण
