<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 SMP cpu-hotplug support
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Author:
 *      Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Platक्रमm file needed क्रम the OMAP4 SMP. This file is based on arm
 * realview smp platक्रमm.
 * Copyright (c) 2002 ARM Limited.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>

#समावेश "omap-wakeupgen.h"
#समावेश "common.h"
#समावेश "powerdomain.h"

/*
 * platक्रमm-specअगरic code to shutकरोwn a CPU
 * Called with IRQs disabled
 */
व्योम omap4_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक boot_cpu = 0;
	व्योम __iomem *base = omap_get_wakeupgen_base();

	/*
	 * we're पढ़ोy क्रम shutकरोwn now, so करो it
	 */
	अगर (omap_secure_apis_support()) अणु
		अगर (omap_modअगरy_auxcoreboot0(0x0, 0x200) != 0x0)
			pr_err("Secure clear status failed\n");
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(0, base + OMAP_AUX_CORE_BOOT_0);
	पूर्ण


	क्रम (;;) अणु
		/*
		 * Enter पूर्णांकo low घातer state
		 */
		omap4_hotplug_cpu(cpu, PWRDM_POWER_OFF);

		अगर (omap_secure_apis_support())
			boot_cpu = omap_पढ़ो_auxcoreboot0() >> 9;
		अन्यथा
			boot_cpu =
				पढ़ोl_relaxed(base + OMAP_AUX_CORE_BOOT_0) >> 5;

		अगर (boot_cpu == smp_processor_id()) अणु
			/*
			 * OK, proper wakeup, we're करोne
			 */
			अवरोध;
		पूर्ण
		pr_debug("CPU%u: spurious wakeup call\n", cpu);
	पूर्ण
पूर्ण

/* Needed by kexec and platक्रमm_can_cpu_hotplug() */
पूर्णांक omap4_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	वापस 1;
पूर्ण
