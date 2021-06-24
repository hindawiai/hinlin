<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम Emma Mobile EV2
 *
 * Copyright (C) 2012  Renesas Solutions Corp.
 * Copyright (C) 2012  Magnus Damm
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश "common.h"
#समावेश "emev2.h"

#घोषणा EMEV2_SCU_BASE 0x1e000000
#घोषणा EMEV2_SMU_BASE 0xe0110000
#घोषणा SMU_GENERAL_REG0 0x7c0

अटल पूर्णांक emev2_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	arch_send_wakeup_ipi_mask(cpumask_of(cpu_logical_map(cpu)));
	वापस 0;
पूर्ण

अटल व्योम __init emev2_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	व्योम __iomem *smu;

	/* Tell ROM loader about our vector (in headsmp.S) */
	smu = ioremap(EMEV2_SMU_BASE, PAGE_SIZE);
	अगर (smu) अणु
		ioग_लिखो32(__pa(shmobile_boot_vector), smu + SMU_GENERAL_REG0);
		iounmap(smu);
	पूर्ण

	/* setup EMEV2 specअगरic SCU bits */
	shmobile_smp_scu_prepare_cpus(EMEV2_SCU_BASE, max_cpus);
पूर्ण

स्थिर काष्ठा smp_operations emev2_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= emev2_smp_prepare_cpus,
	.smp_boot_secondary	= emev2_boot_secondary,
पूर्ण;
