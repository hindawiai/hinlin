<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम R-Mobile / SH-Mobile - sh73a0 portion
 *
 * Copyright (C) 2010  Magnus Damm
 * Copyright (C) 2010  Takashi Yoshii
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश <यंत्र/smp_plat.h>

#समावेश "common.h"
#समावेश "sh73a0.h"

#घोषणा CPG_BASE2	0xe6151000
#घोषणा WUPCR		0x10	/* System-CPU Wake Up Control Register */
#घोषणा SRESCR		0x18	/* System-CPU Software Reset Control Register */
#घोषणा PSTR		0x40	/* System-CPU Power Status Register */

#घोषणा SYSC_BASE	0xe6180000
#घोषणा SBAR		0x20	/* SYS Boot Address Register */

#घोषणा AP_BASE		0xe6f10000
#घोषणा APARMBAREA	0x20	/* Address Translation Area Register */

#घोषणा SH73A0_SCU_BASE 0xf0000000

अटल पूर्णांक sh73a0_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित पूर्णांक lcpu = cpu_logical_map(cpu);
	व्योम __iomem *cpg2 = ioremap(CPG_BASE2, PAGE_SIZE);

	अगर (((पढ़ोl(cpg2 + PSTR) >> (4 * lcpu)) & 3) == 3)
		ग_लिखोl(1 << lcpu, cpg2 + WUPCR);	/* wake up */
	अन्यथा
		ग_लिखोl(1 << lcpu, cpg2 + SRESCR);	/* reset */
	iounmap(cpg2);
	वापस 0;
पूर्ण

अटल व्योम __init sh73a0_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	व्योम __iomem *ap = ioremap(AP_BASE, PAGE_SIZE);
	व्योम __iomem *sysc = ioremap(SYSC_BASE, PAGE_SIZE);

	/* Map the reset vector (in headsmp.S) */
	ग_लिखोl(0, ap + APARMBAREA);      /* 4k */
	ग_लिखोl(__pa(shmobile_boot_vector), sysc + SBAR);
	iounmap(sysc);
	iounmap(ap);

	/* setup sh73a0 specअगरic SCU bits */
	shmobile_smp_scu_prepare_cpus(SH73A0_SCU_BASE, max_cpus);
पूर्ण

स्थिर काष्ठा smp_operations sh73a0_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= sh73a0_smp_prepare_cpus,
	.smp_boot_secondary	= sh73a0_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_can_disable	= shmobile_smp_cpu_can_disable,
	.cpu_die		= shmobile_smp_scu_cpu_die,
	.cpu_समाप्त		= shmobile_smp_scu_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
