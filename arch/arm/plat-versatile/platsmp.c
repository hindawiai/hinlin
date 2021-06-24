<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/plat-versatile/platsmp.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This code is specअगरic to the hardware found on ARM Realview and
 * Versatile Express platक्रमms where the CPUs are unable to be inभागidually
 * woken, and where there is no way to hot-unplug CPUs.  Real platक्रमms
 * should not copy this code.
 */
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश <plat/platsmp.h>

/*
 * versatile_cpu_release controls the release of CPUs from the holding
 * pen in headsmp.S, which exists because we are not always able to
 * control the release of inभागidual CPUs from the board firmware.
 * Production platक्रमms करो not need this.
 */
अस्थिर पूर्णांक versatile_cpu_release = -1;

/*
 * Write versatile_cpu_release in a way that is guaranteed to be visible to
 * all observers, irrespective of whether they're taking part in coherency
 * or not.  This is necessary क्रम the hotplug code to work reliably.
 */
अटल व्योम versatile_ग_लिखो_cpu_release(पूर्णांक val)
अणु
	versatile_cpu_release = val;
	smp_wmb();
	sync_cache_w(&versatile_cpu_release);
पूर्ण

/*
 * versatile_lock exists to aव्योम running the loops_per_jअगरfy delay loop
 * calibrations on the secondary CPU जबतक the requesting CPU is using
 * the limited-bandwidth bus - which affects the calibration value.
 * Production platक्रमms करो not need this.
 */
अटल DEFINE_RAW_SPINLOCK(versatile_lock);

व्योम versatile_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * let the primary processor know we're out of the
	 * pen, then head off पूर्णांकo the C entry poपूर्णांक
	 */
	versatile_ग_लिखो_cpu_release(-1);

	/*
	 * Synchronise with the boot thपढ़ो.
	 */
	raw_spin_lock(&versatile_lock);
	raw_spin_unlock(&versatile_lock);
पूर्ण

पूर्णांक versatile_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ समयout;

	/*
	 * Set synchronisation state between this boot processor
	 * and the secondary one
	 */
	raw_spin_lock(&versatile_lock);

	/*
	 * This is really belt and braces; we hold unपूर्णांकended secondary
	 * CPUs in the holding pen until we're पढ़ोy क्रम them.  However,
	 * since we haven't sent them a soft interrupt, they shouldn't
	 * be there.
	 */
	versatile_ग_लिखो_cpu_release(cpu_logical_map(cpu));

	/*
	 * Send the secondary CPU a soft पूर्णांकerrupt, thereby causing
	 * the boot monitor to पढ़ो the प्रणाली wide flags रेजिस्टर,
	 * and branch to the address found there.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	समयout = jअगरfies + (1 * HZ);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		smp_rmb();
		अगर (versatile_cpu_release == -1)
			अवरोध;

		udelay(10);
	पूर्ण

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then रुको क्रम it to finish
	 */
	raw_spin_unlock(&versatile_lock);

	वापस versatile_cpu_release != -1 ? -ENOSYS : 0;
पूर्ण
