<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2010 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// S3C2416 - PM support (Based on Ben Dooks' S3C2412 PM support)

#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cacheflush.h>

#समावेश "regs-s3c2443-clock.h"

#समावेश "cpu.h"
#समावेश "pm.h"

#समावेश "s3c2412-power.h"

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य व्योम s3c2412_sleep_enter(व्योम);

अटल पूर्णांक s3c2416_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	/* enable wakeup sources regardless of battery state */
	__raw_ग_लिखोl(S3C2443_PWRCFG_SLEEP, S3C2443_PWRCFG);

	/* set the mode as sleep, 2BED represents "Go to BED" */
	__raw_ग_लिखोl(0x2BED, S3C2443_PWRMODE);

	s3c2412_sleep_enter();

	pr_info("Failed to suspend the system\n");
	वापस 1; /* Aborting suspend */
पूर्ण

अटल व्योम s3c2416_pm_prepare(व्योम)
अणु
	/*
	 * ग_लिखो the magic value u-boot uses to check क्रम resume पूर्णांकo
	 * the INFORM0 रेजिस्टर, and ensure INFORM1 is set to the
	 * correct address to resume from.
	 */
	__raw_ग_लिखोl(0x2BED, S3C2412_INFORM0);
	__raw_ग_लिखोl(__pa_symbol(s3c_cpu_resume), S3C2412_INFORM1);
पूर्ण

अटल पूर्णांक s3c2416_pm_add(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	pm_cpu_prep = s3c2416_pm_prepare;
	pm_cpu_sleep = s3c2416_cpu_suspend;

	वापस 0;
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2416_pm_पूर्णांकerface = अणु
	.name		= "s3c2416_pm",
	.subsys		= &s3c2416_subsys,
	.add_dev	= s3c2416_pm_add,
पूर्ण;

अटल __init पूर्णांक s3c2416_pm_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2416_pm_पूर्णांकerface);
पूर्ण

arch_initcall(s3c2416_pm_init);
#पूर्ण_अगर

अटल व्योम s3c2416_pm_resume(व्योम)
अणु
	/* unset the वापस-from-sleep amd inक्रमm flags */
	__raw_ग_लिखोl(0x0, S3C2443_PWRMODE);
	__raw_ग_लिखोl(0x0, S3C2412_INFORM0);
	__raw_ग_लिखोl(0x0, S3C2412_INFORM1);
पूर्ण

काष्ठा syscore_ops s3c2416_pm_syscore_ops = अणु
	.resume		= s3c2416_pm_resume,
पूर्ण;
