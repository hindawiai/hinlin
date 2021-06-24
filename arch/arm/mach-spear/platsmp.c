<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-spear13xx/platsmp.c
 *
 * based upon linux/arch/arm/mach-realview/platsmp.c
 *
 * Copyright (C) 2012 ST Microelectronics Ltd.
 * Shiraz Hashim <shiraz.linux.kernel@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <mach/spear.h>
#समावेश "generic.h"

/* XXX spear_pen_release is cargo culted code - DO NOT COPY XXX */
अस्थिर पूर्णांक spear_pen_release = -1;

/*
 * XXX CARGO CULTED CODE - DO NOT COPY XXX
 *
 * Write spear_pen_release in a way that is guaranteed to be visible to
 * all observers, irrespective of whether they're taking part in coherency
 * or not.  This is necessary क्रम the hotplug code to work reliably.
 */
अटल व्योम spear_ग_लिखो_pen_release(पूर्णांक val)
अणु
	spear_pen_release = val;
	smp_wmb();
	sync_cache_w(&spear_pen_release);
पूर्ण

अटल DEFINE_SPINLOCK(boot_lock);

अटल व्योम __iomem *scu_base = IOMEM(VA_SCU_BASE);

अटल व्योम spear13xx_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * let the primary processor know we're out of the
	 * pen, then head off पूर्णांकo the C entry poपूर्णांक
	 */
	spear_ग_लिखो_pen_release(-1);

	/*
	 * Synchronise with the boot thपढ़ो.
	 */
	spin_lock(&boot_lock);
	spin_unlock(&boot_lock);
पूर्ण

अटल पूर्णांक spear13xx_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ समयout;

	/*
	 * set synchronisation state between this boot processor
	 * and the secondary one
	 */
	spin_lock(&boot_lock);

	/*
	 * The secondary processor is रुकोing to be released from
	 * the holding pen - release it, then रुको क्रम it to flag
	 * that it has been released by resetting spear_pen_release.
	 *
	 * Note that "spear_pen_release" is the hardware CPU ID, whereas
	 * "cpu" is Linux's पूर्णांकernal ID.
	 */
	spear_ग_लिखो_pen_release(cpu);

	समयout = jअगरfies + (1 * HZ);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		smp_rmb();
		अगर (spear_pen_release == -1)
			अवरोध;

		udelay(10);
	पूर्ण

	/*
	 * now the secondary core is starting up let it run its
	 * calibrations, then रुको क्रम it to finish
	 */
	spin_unlock(&boot_lock);

	वापस spear_pen_release != -1 ? -ENOSYS : 0;
पूर्ण

/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the प्रणाली.
 */
अटल व्योम __init spear13xx_smp_init_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक i, ncores = scu_get_core_count(scu_base);

	अगर (ncores > nr_cpu_ids) अणु
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
			ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
	पूर्ण

	क्रम (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);
पूर्ण

अटल व्योम __init spear13xx_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु

	scu_enable(scu_base);

	/*
	 * Write the address of secondary startup पूर्णांकo the प्रणाली-wide location
	 * (presently it is in SRAM). The BootMonitor रुकोs until it receives a
	 * soft पूर्णांकerrupt, and then the secondary CPU branches to this address.
	 */
	__raw_ग_लिखोl(__pa_symbol(spear13xx_secondary_startup), SYS_LOCATION);
पूर्ण

स्थिर काष्ठा smp_operations spear13xx_smp_ops __initस्थिर = अणु
       .smp_init_cpus		= spear13xx_smp_init_cpus,
       .smp_prepare_cpus	= spear13xx_smp_prepare_cpus,
       .smp_secondary_init	= spear13xx_secondary_init,
       .smp_boot_secondary	= spear13xx_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
       .cpu_die			= spear13xx_cpu_die,
#पूर्ण_अगर
पूर्ण;
