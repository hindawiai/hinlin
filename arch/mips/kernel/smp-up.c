<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006, 07 by Ralf Baechle (ralf@linux-mips.org)
 *
 * Symmetric Uniprocessor (TM) Support
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>

/*
 * Send पूर्णांकer-processor पूर्णांकerrupt
 */
अटल व्योम up_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action)
अणु
	panic(KERN_ERR "%s called", __func__);
पूर्ण

अटल अंतरभूत व्योम up_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
				    अचिन्हित पूर्णांक action)
अणु
	panic(KERN_ERR "%s called", __func__);
पूर्ण

/*
 *  After we've करोne initial boot, this function is called to allow the
 *  board code to clean up state, अगर needed
 */
अटल व्योम up_init_secondary(व्योम)
अणु
पूर्ण

अटल व्योम up_smp_finish(व्योम)
अणु
पूर्ण

/*
 * Firmware CPU startup hook
 */
अटल पूर्णांक up_boot_secondary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	वापस 0;
पूर्ण

अटल व्योम __init up_smp_setup(व्योम)
अणु
पूर्ण

अटल व्योम __init up_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक up_cpu_disable(व्योम)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम up_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा plat_smp_ops up_smp_ops = अणु
	.send_ipi_single	= up_send_ipi_single,
	.send_ipi_mask		= up_send_ipi_mask,
	.init_secondary		= up_init_secondary,
	.smp_finish		= up_smp_finish,
	.boot_secondary		= up_boot_secondary,
	.smp_setup		= up_smp_setup,
	.prepare_cpus		= up_prepare_cpus,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= up_cpu_disable,
	.cpu_die		= up_cpu_die,
#पूर्ण_अगर
पूर्ण;
