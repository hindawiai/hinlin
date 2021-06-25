<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2010-2014 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// S5PV210 - Power Management support
//
// Based on arch/arm/mach-s3c2410/pm.c
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पन.स>
#समावेश <linux/soc/samsung/s3c-pm.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/suspend.h>

#समावेश "common.h"
#समावेश "regs-clock.h"

/* helper functions to save and restore रेजिस्टर state */
काष्ठा sleep_save अणु
	व्योम __iomem	*reg;
	अचिन्हित दीर्घ	val;
पूर्ण;

#घोषणा SAVE_ITEM(x) \
	अणु .reg = (x) पूर्ण

/**
 * s3c_pm_करो_save() - save a set of रेजिस्टरs क्रम restoration on resume.
 * @ptr: Poपूर्णांकer to an array of रेजिस्टरs.
 * @count: Size of the ptr array.
 *
 * Run through the list of रेजिस्टरs given, saving their contents in the
 * array क्रम later restoration when we wakeup.
 */
अटल व्योम s3c_pm_करो_save(काष्ठा sleep_save *ptr, पूर्णांक count)
अणु
	क्रम (; count > 0; count--, ptr++) अणु
		ptr->val = पढ़ोl_relaxed(ptr->reg);
		S3C_PMDBG("saved %p value %08lx\n", ptr->reg, ptr->val);
	पूर्ण
पूर्ण

/**
 * s3c_pm_करो_restore() - restore रेजिस्टर values from the save list.
 * @ptr: Poपूर्णांकer to an array of रेजिस्टरs.
 * @count: Size of the ptr array.
 *
 * Restore the रेजिस्टर values saved from s3c_pm_करो_save().
 *
 * WARNING: Do not put any debug in here that may effect memory or use
 * peripherals, as things may be changing!
*/

अटल व्योम s3c_pm_करो_restore_core(स्थिर काष्ठा sleep_save *ptr, पूर्णांक count)
अणु
	क्रम (; count > 0; count--, ptr++)
		ग_लिखोl_relaxed(ptr->val, ptr->reg);
पूर्ण

अटल काष्ठा sleep_save s5pv210_core_save[] = अणु
	/* Clock ETC */
	SAVE_ITEM(S5P_MDNIE_SEL),
पूर्ण;

/*
 * VIC wake-up support (TODO)
 */
अटल u32 s5pv210_irqwake_पूर्णांकmask = 0xffffffff;

अटल u32 s5pv210_पढ़ो_eपूर्णांक_wakeup_mask(व्योम)
अणु
	वापस __raw_पढ़ोl(S5P_EINT_WAKEUP_MASK);
पूर्ण

/*
 * Suspend helpers.
 */
अटल पूर्णांक s5pv210_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* issue the standby संकेत पूर्णांकo the pm unit. Note, we
	 * issue a ग_लिखो-buffer drain just in हाल */

	पंचांगp = 0;

	यंत्र("b 1f\n\t"
	    ".align 5\n\t"
	    "1:\n\t"
	    "mcr p15, 0, %0, c7, c10, 5\n\t"
	    "mcr p15, 0, %0, c7, c10, 4\n\t"
	    "wfi" : : "r" (पंचांगp));

	pr_info("Failed to suspend the system\n");
	वापस 1; /* Aborting suspend */
पूर्ण

अटल व्योम s5pv210_pm_prepare(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/*
	 * Set wake-up mask रेजिस्टरs
	 * S5P_EINT_WAKEUP_MASK is set by pinctrl driver in late suspend.
	 */
	__raw_ग_लिखोl(s5pv210_irqwake_पूर्णांकmask, S5P_WAKEUP_MASK);

	/* ensure at least INFORM0 has the resume address */
	__raw_ग_लिखोl(__pa_symbol(s5pv210_cpu_resume), S5P_INFORM0);

	पंचांगp = __raw_पढ़ोl(S5P_SLEEP_CFG);
	पंचांगp &= ~(S5P_SLEEP_CFG_OSC_EN | S5P_SLEEP_CFG_USBOSC_EN);
	__raw_ग_लिखोl(पंचांगp, S5P_SLEEP_CFG);

	/* WFI क्रम SLEEP mode configuration by SYSCON */
	पंचांगp = __raw_पढ़ोl(S5P_PWR_CFG);
	पंचांगp &= S5P_CFG_WFI_CLEAN;
	पंचांगp |= S5P_CFG_WFI_SLEEP;
	__raw_ग_लिखोl(पंचांगp, S5P_PWR_CFG);

	/* SYSCON पूर्णांकerrupt handling disable */
	पंचांगp = __raw_पढ़ोl(S5P_OTHERS);
	पंचांगp |= S5P_OTHER_SYSC_INTOFF;
	__raw_ग_लिखोl(पंचांगp, S5P_OTHERS);

	s3c_pm_करो_save(s5pv210_core_save, ARRAY_SIZE(s5pv210_core_save));
पूर्ण

/*
 * Suspend operations.
 */
अटल पूर्णांक s5pv210_suspend_enter(suspend_state_t state)
अणु
	u32 eपूर्णांक_wakeup_mask = s5pv210_पढ़ो_eपूर्णांक_wakeup_mask();
	पूर्णांक ret;

	S3C_PMDBG("%s: suspending the system...\n", __func__);

	S3C_PMDBG("%s: wakeup masks: %08x,%08x\n", __func__,
			s5pv210_irqwake_पूर्णांकmask, eपूर्णांक_wakeup_mask);

	अगर (s5pv210_irqwake_पूर्णांकmask == -1U
	    && eपूर्णांक_wakeup_mask == -1U) अणु
		pr_err("%s: No wake-up sources!\n", __func__);
		pr_err("%s: Aborting sleep\n", __func__);
		वापस -EINVAL;
	पूर्ण

	s3c_pm_save_uarts(false);
	s5pv210_pm_prepare();
	flush_cache_all();
	s3c_pm_check_store();

	ret = cpu_suspend(0, s5pv210_cpu_suspend);
	अगर (ret)
		वापस ret;

	s3c_pm_restore_uarts(false);

	S3C_PMDBG("%s: wakeup stat: %08x\n", __func__,
			__raw_पढ़ोl(S5P_WAKEUP_STAT));

	s3c_pm_check_restore();

	S3C_PMDBG("%s: resuming the system...\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक s5pv210_suspend_prepare(व्योम)
अणु
	s3c_pm_check_prepare();

	वापस 0;
पूर्ण

अटल व्योम s5pv210_suspend_finish(व्योम)
अणु
	s3c_pm_check_cleanup();
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops s5pv210_suspend_ops = अणु
	.enter		= s5pv210_suspend_enter,
	.prepare	= s5pv210_suspend_prepare,
	.finish		= s5pv210_suspend_finish,
	.valid		= suspend_valid_only_mem,
पूर्ण;

/*
 * Syscore operations used to delay restore of certain रेजिस्टरs.
 */
अटल व्योम s5pv210_pm_resume(व्योम)
अणु
	s3c_pm_करो_restore_core(s5pv210_core_save, ARRAY_SIZE(s5pv210_core_save));
पूर्ण

अटल काष्ठा syscore_ops s5pv210_pm_syscore_ops = अणु
	.resume		= s5pv210_pm_resume,
पूर्ण;

/*
 * Initialization entry poपूर्णांक.
 */
व्योम __init s5pv210_pm_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&s5pv210_pm_syscore_ops);
	suspend_set_ops(&s5pv210_suspend_ops);
पूर्ण
