<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2004-2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// S3C common घातer management (suspend to ram) support.

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/suspend.h>

#समावेश "map.h"
#समावेश "regs-clock.h"
#समावेश "regs-irq.h"
#समावेश <mach/irqs.h>

#समावेश <यंत्र/irq.h>

#समावेश "cpu.h"
#समावेश "pm.h"
#समावेश "pm-core.h"

/* क्रम बाह्यal use */

अचिन्हित दीर्घ s3c_pm_flags;

/* The IRQ ext-पूर्णांक code goes here, it is too small to currently bother
 * with its own file. */

अचिन्हित दीर्घ s3c_irqwake_पूर्णांकmask	= 0xffffffffL;
अचिन्हित दीर्घ s3c_irqwake_eपूर्णांकmask	= 0xffffffffL;

पूर्णांक s3c_irqext_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक state)
अणु
	अचिन्हित दीर्घ bit = 1L << IRQ_EINT_BIT(data->irq);

	अगर (!(s3c_irqwake_eपूर्णांकallow & bit))
		वापस -ENOENT;

	prपूर्णांकk(KERN_INFO "wake %s for irq %d\n",
	       state ? "enabled" : "disabled", data->irq);

	अगर (!state)
		s3c_irqwake_eपूर्णांकmask |= bit;
	अन्यथा
		s3c_irqwake_eपूर्णांकmask &= ~bit;

	वापस 0;
पूर्ण

व्योम (*pm_cpu_prep)(व्योम);
पूर्णांक (*pm_cpu_sleep)(अचिन्हित दीर्घ);

#घोषणा any_allowed(mask, allow) (((mask) & (allow)) != (allow))

/* s3c_pm_enter
 *
 * central control क्रम sleep/resume process
*/

अटल पूर्णांक s3c_pm_enter(suspend_state_t state)
अणु
	पूर्णांक ret;
	/* ensure the debug is initialised (अगर enabled) */
	s3c_pm_debug_init_uart();

	S3C_PMDBG("%s(%d)\n", __func__, state);

	अगर (pm_cpu_prep == शून्य || pm_cpu_sleep == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: error: no cpu sleep function\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* check अगर we have anything to wake-up with... bad things seem
	 * to happen अगर you suspend with no wakeup (प्रणाली will often
	 * require a full घातer-cycle)
	*/

	अगर (!of_have_populated_dt() &&
	    !any_allowed(s3c_irqwake_पूर्णांकmask, s3c_irqwake_पूर्णांकallow) &&
	    !any_allowed(s3c_irqwake_eपूर्णांकmask, s3c_irqwake_eपूर्णांकallow)) अणु
		prपूर्णांकk(KERN_ERR "%s: No wake-up sources!\n", __func__);
		prपूर्णांकk(KERN_ERR "%s: Aborting sleep\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* save all necessary core रेजिस्टरs not covered by the drivers */

	अगर (!of_have_populated_dt()) अणु
		samsung_pm_save_gpios();
		samsung_pm_saved_gpios();
	पूर्ण

	s3c_pm_save_uarts(soc_is_s3c2410());
	s3c_pm_save_core();

	/* set the irq configuration क्रम wake */

	s3c_pm_configure_extपूर्णांक();

	S3C_PMDBG("sleep: irq wakeup masks: %08lx,%08lx\n",
	    s3c_irqwake_पूर्णांकmask, s3c_irqwake_eपूर्णांकmask);

	s3c_pm_arch_prepare_irqs();

	/* call cpu specअगरic preparation */

	pm_cpu_prep();

	/* flush cache back to ram */

	flush_cache_all();

	s3c_pm_check_store();

	/* send the cpu to sleep... */

	s3c_pm_arch_stop_घड़ीs();

	/* this will also act as our वापस poपूर्णांक from when
	 * we resume as it saves its own रेजिस्टर state and restores it
	 * during the resume.  */

	ret = cpu_suspend(0, pm_cpu_sleep);
	अगर (ret)
		वापस ret;

	/* restore the प्रणाली state */

	s3c_pm_restore_core();
	s3c_pm_restore_uarts(soc_is_s3c2410());

	अगर (!of_have_populated_dt()) अणु
		samsung_pm_restore_gpios();
		s3c_pm_restored_gpios();
	पूर्ण

	s3c_pm_debug_init_uart();

	/* check what irq (अगर any) restored the प्रणाली */

	s3c_pm_arch_show_resume_irqs();

	S3C_PMDBG("%s: post sleep, preparing to return\n", __func__);

	/* LEDs should now be 1110 */
	s3c_pm_debug_smdkled(1 << 1, 0);

	s3c_pm_check_restore();

	/* ok, let's वापस from sleep */

	S3C_PMDBG("S3C PM Resume (post-restore)\n");
	वापस 0;
पूर्ण

अटल पूर्णांक s3c_pm_prepare(व्योम)
अणु
	/* prepare check area अगर configured */

	s3c_pm_check_prepare();
	वापस 0;
पूर्ण

अटल व्योम s3c_pm_finish(व्योम)
अणु
	s3c_pm_check_cleanup();
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops s3c_pm_ops = अणु
	.enter		= s3c_pm_enter,
	.prepare	= s3c_pm_prepare,
	.finish		= s3c_pm_finish,
	.valid		= suspend_valid_only_mem,
पूर्ण;

/* s3c_pm_init
 *
 * Attach the घातer management functions. This should be called
 * from the board specअगरic initialisation अगर the board supports
 * it.
*/

पूर्णांक __init s3c_pm_init(व्योम)
अणु
	prपूर्णांकk("S3C Power Management, Copyright 2004 Simtec Electronics\n");

	suspend_set_ops(&s3c_pm_ops);
	वापस 0;
पूर्ण
