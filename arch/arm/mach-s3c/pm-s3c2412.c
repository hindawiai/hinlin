<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://armlinux.simtec.co.uk/.

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/irq.h>

#समावेश <mach/irqs.h>
#समावेश "regs-gpio.h"

#समावेश "cpu.h"
#समावेश "pm.h"
#समावेश "wakeup-mask.h"

#समावेश "regs-dsc-s3c24xx.h"
#समावेश "s3c2412-power.h"

बाह्य व्योम s3c2412_sleep_enter(व्योम);

अटल पूर्णांक s3c2412_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* set our standby method to sleep */

	पंचांगp = __raw_पढ़ोl(S3C2412_PWRCFG);
	पंचांगp |= S3C2412_PWRCFG_STANDBYWFI_SLEEP;
	__raw_ग_लिखोl(पंचांगp, S3C2412_PWRCFG);

	s3c2412_sleep_enter();

	pr_info("Failed to suspend the system\n");
	वापस 1; /* Aborting suspend */
पूर्ण

/* mapping of पूर्णांकerrupts to parts of the wakeup mask */
अटल स्थिर काष्ठा samsung_wakeup_mask wake_irqs[] = अणु
	अणु .irq = IRQ_RTC,	.bit = S3C2412_PWRCFG_RTC_MASKIRQ, पूर्ण,
पूर्ण;

अटल व्योम s3c2412_pm_prepare(व्योम)
अणु
	samsung_sync_wakemask(S3C2412_PWRCFG,
			      wake_irqs, ARRAY_SIZE(wake_irqs));
पूर्ण

अटल पूर्णांक s3c2412_pm_add(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	pm_cpu_prep = s3c2412_pm_prepare;
	pm_cpu_sleep = s3c2412_cpu_suspend;

	वापस 0;
पूर्ण

अटल काष्ठा sleep_save s3c2412_sleep[] = अणु
	SAVE_ITEM(S3C2412_DSC0),
	SAVE_ITEM(S3C2412_DSC1),
	SAVE_ITEM(S3C2413_GPJDAT),
	SAVE_ITEM(S3C2413_GPJCON),
	SAVE_ITEM(S3C2413_GPJUP),

	/* save the PWRCFG to get back to original sleep method */

	SAVE_ITEM(S3C2412_PWRCFG),

	/* save the sleep configuration anyway, just in हाल these
	 * get damaged during wakeup */

	SAVE_ITEM(S3C2412_GPBSLPCON),
	SAVE_ITEM(S3C2412_GPCSLPCON),
	SAVE_ITEM(S3C2412_GPDSLPCON),
	SAVE_ITEM(S3C2412_GPFSLPCON),
	SAVE_ITEM(S3C2412_GPGSLPCON),
	SAVE_ITEM(S3C2412_GPHSLPCON),
	SAVE_ITEM(S3C2413_GPJSLPCON),
पूर्ण;

अटल काष्ठा subsys_पूर्णांकerface s3c2412_pm_पूर्णांकerface = अणु
	.name		= "s3c2412_pm",
	.subsys		= &s3c2412_subsys,
	.add_dev	= s3c2412_pm_add,
पूर्ण;

अटल __init पूर्णांक s3c2412_pm_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2412_pm_पूर्णांकerface);
पूर्ण

arch_initcall(s3c2412_pm_init);

अटल पूर्णांक s3c2412_pm_suspend(व्योम)
अणु
	s3c_pm_करो_save(s3c2412_sleep, ARRAY_SIZE(s3c2412_sleep));
	वापस 0;
पूर्ण

अटल व्योम s3c2412_pm_resume(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = __raw_पढ़ोl(S3C2412_PWRCFG);
	पंचांगp &= ~S3C2412_PWRCFG_STANDBYWFI_MASK;
	पंचांगp |=  S3C2412_PWRCFG_STANDBYWFI_IDLE;
	__raw_ग_लिखोl(पंचांगp, S3C2412_PWRCFG);

	s3c_pm_करो_restore(s3c2412_sleep, ARRAY_SIZE(s3c2412_sleep));
पूर्ण

काष्ठा syscore_ops s3c2412_pm_syscore_ops = अणु
	.suspend	= s3c2412_pm_suspend,
	.resume		= s3c2412_pm_resume,
पूर्ण;
