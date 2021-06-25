<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1996-2000 Russell King - Converted to ARM.
 *  Original Copyright (C) 1995  Linus Torvalds
 */
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/virt.h>

#समावेश "reboot.h"

प्रकार व्योम (*phys_reset_t)(अचिन्हित दीर्घ, bool);

/*
 * Function poपूर्णांकers to optional machine specअगरic functions
 */
व्योम (*arm_pm_restart)(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *cmd);
व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL(pm_घातer_off);

/*
 * A temporary stack to use क्रम CPU reset. This is अटल so that we
 * करोn't clobber it with the identity mapping. When running with this
 * stack, any references to the current task *will not work* so you
 * should really करो as little as possible beक्रमe jumping to your reset
 * code.
 */
अटल u64 soft_restart_stack[16];

अटल व्योम __soft_restart(व्योम *addr)
अणु
	phys_reset_t phys_reset;

	/* Take out a flat memory mapping. */
	setup_mm_क्रम_reboot();

	/* Clean and invalidate caches */
	flush_cache_all();

	/* Turn off caching */
	cpu_proc_fin();

	/* Push out any further dirty data, and ensure cache is empty */
	flush_cache_all();

	/* Switch to the identity mapping. */
	phys_reset = (phys_reset_t)virt_to_idmap(cpu_reset);

	/* original stub should be restored by kvm */
	phys_reset((अचिन्हित दीर्घ)addr, is_hyp_mode_available());

	/* Should never get here. */
	BUG();
पूर्ण

व्योम _soft_restart(अचिन्हित दीर्घ addr, bool disable_l2)
अणु
	u64 *stack = soft_restart_stack + ARRAY_SIZE(soft_restart_stack);

	/* Disable पूर्णांकerrupts first */
	raw_local_irq_disable();
	local_fiq_disable();

	/* Disable the L2 अगर we're the last man standing. */
	अगर (disable_l2)
		outer_disable();

	/* Change to the new stack and जारी with the reset. */
	call_with_stack(__soft_restart, (व्योम *)addr, (व्योम *)stack);

	/* Should never get here. */
	BUG();
पूर्ण

व्योम soft_restart(अचिन्हित दीर्घ addr)
अणु
	_soft_restart(addr, num_online_cpus() == 1);
पूर्ण

/*
 * Called by kexec, immediately prior to machine_kexec().
 *
 * This must completely disable all secondary CPUs; simply causing those CPUs
 * to execute e.g. a RAM-based pin loop is not sufficient. This allows the
 * kexec'd kernel to use any and all RAM as it sees fit, without having to
 * aव्योम any code or data used by any SW CPU pin loop. The CPU hotplug
 * functionality embodied in smp_shutकरोwn_nonboot_cpus() to achieve this.
 */
व्योम machine_shutकरोwn(व्योम)
अणु
	smp_shutकरोwn_nonboot_cpus(reboot_cpu);
पूर्ण

/*
 * Halting simply requires that the secondary CPUs stop perक्रमming any
 * activity (executing tasks, handling पूर्णांकerrupts). smp_send_stop()
 * achieves this.
 */
व्योम machine_halt(व्योम)
अणु
	local_irq_disable();
	smp_send_stop();
	जबतक (1);
पूर्ण

/*
 * Power-off simply requires that the secondary CPUs stop perक्रमming any
 * activity (executing tasks, handling पूर्णांकerrupts). smp_send_stop()
 * achieves this. When the प्रणाली घातer is turned off, it will take all CPUs
 * with it.
 */
व्योम machine_घातer_off(व्योम)
अणु
	local_irq_disable();
	smp_send_stop();

	अगर (pm_घातer_off)
		pm_घातer_off();
पूर्ण

/*
 * Restart requires that the secondary CPUs stop perक्रमming any activity
 * जबतक the primary CPU resets the प्रणाली. Systems with a single CPU can
 * use soft_restart() as their machine descriptor's .restart hook, since that
 * will cause the only available CPU to reset. Systems with multiple CPUs must
 * provide a HW restart implementation, to ensure that all CPUs reset at once.
 * This is required so that any code running after reset on the primary CPU
 * करोesn't have to co-ordinate with other CPUs to ensure they aren't still
 * executing pre-reset code, and using RAM that the primary CPU's code wishes
 * to use. Implementing such co-ordination would be essentially impossible.
 */
व्योम machine_restart(अक्षर *cmd)
अणु
	local_irq_disable();
	smp_send_stop();

	अगर (arm_pm_restart)
		arm_pm_restart(reboot_mode, cmd);
	अन्यथा
		करो_kernel_restart(cmd);

	/* Give a grace period क्रम failure to restart of 1s */
	mdelay(1000);

	/* Whoops - the platक्रमm was unable to reboot. Tell the user! */
	prपूर्णांकk("Reboot failed -- System halted\n");
	जबतक (1);
पूर्ण
