<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम R-Mobile / SH-Mobile - r8a7779 portion
 *
 * Copyright (C) 2011  Renesas Solutions Corp.
 * Copyright (C) 2011  Magnus Damm
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/soc/renesas/rcar-sysc.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश "common.h"
#समावेश "r8a7779.h"

#घोषणा HPBREG_BASE		0xfe700000
#घोषणा AVECR			0x0040	/* ARM Reset Vector Address Register */

#घोषणा R8A7779_SCU_BASE	0xf0000000

अटल पूर्णांक r8a7779_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret = -EIO;

	cpu = cpu_logical_map(cpu);
	अगर (cpu)
		ret = rcar_sysc_घातer_up_cpu(cpu);

	वापस ret;
पूर्ण

अटल व्योम __init r8a7779_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	व्योम __iomem *base = ioremap(HPBREG_BASE, 0x1000);

	/* Map the reset vector (in headsmp-scu.S, headsmp.S) */
	ग_लिखोl(__pa(shmobile_boot_vector), base + AVECR);

	/* setup r8a7779 specअगरic SCU bits */
	shmobile_smp_scu_prepare_cpus(R8A7779_SCU_BASE, max_cpus);

	iounmap(base);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक r8a7779_platक्रमm_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = -EIO;

	cpu = cpu_logical_map(cpu);
	अगर (cpu)
		ret = rcar_sysc_घातer_करोwn_cpu(cpu);

	वापस ret ? ret : 1;
पूर्ण

अटल पूर्णांक r8a7779_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	अगर (shmobile_smp_scu_cpu_समाप्त(cpu))
		वापस r8a7779_platक्रमm_cpu_समाप्त(cpu);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

स्थिर काष्ठा smp_operations r8a7779_smp_ops  __initस्थिर = अणु
	.smp_prepare_cpus	= r8a7779_smp_prepare_cpus,
	.smp_boot_secondary	= r8a7779_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= shmobile_smp_scu_cpu_die,
	.cpu_समाप्त		= r8a7779_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
