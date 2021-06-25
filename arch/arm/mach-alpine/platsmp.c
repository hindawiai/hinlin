<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMP operations क्रम Alpine platक्रमm.
 *
 * Copyright (C) 2015 Annapurna Lअसल Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश <यंत्र/smp_plat.h>

#समावेश "alpine_cpu_pm.h"

अटल पूर्णांक alpine_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	phys_addr_t addr;

	addr = __pa_symbol(secondary_startup);

	अगर (addr > (phys_addr_t)(uपूर्णांक32_t)(-1)) अणु
		pr_err("FAIL: resume address over 32bit (%pa)", &addr);
		वापस -EINVAL;
	पूर्ण

	वापस alpine_cpu_wakeup(cpu_logical_map(cpu), (uपूर्णांक32_t)addr);
पूर्ण

अटल व्योम __init alpine_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	alpine_cpu_pm_init();
पूर्ण

अटल स्थिर काष्ठा smp_operations alpine_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= alpine_smp_prepare_cpus,
	.smp_boot_secondary	= alpine_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(alpine_smp, "al,alpine-smp", &alpine_smp_ops);
