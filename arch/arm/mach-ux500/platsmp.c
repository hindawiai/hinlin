<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2002 ARM Ltd.
 * Copyright (C) 2008 STMicroelctronics.
 * Copyright (C) 2009 ST-Ericsson.
 * Author: Srinidhi Kasagar <srinidhi.kasagar@stericsson.com>
 *
 * This file is based on arm realview platक्रमm
 */
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश "db8500-regs.h"

/* Magic triggers in backup RAM */
#घोषणा UX500_CPU1_JUMPADDR_OFFSET 0x1FF4
#घोषणा UX500_CPU1_WAKEMAGIC_OFFSET 0x1FF0

अटल व्योम __iomem *backupram;

अटल व्योम __init ux500_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	अटल व्योम __iomem *scu_base;
	अचिन्हित पूर्णांक ncores;
	पूर्णांक i;

	np = of_find_compatible_node(शून्य, शून्य, "ste,dbx500-backupram");
	अगर (!np) अणु
		pr_err("No backupram base address\n");
		वापस;
	पूर्ण
	backupram = of_iomap(np, 0);
	of_node_put(np);
	अगर (!backupram) अणु
		pr_err("No backupram remap\n");
		वापस;
	पूर्ण

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
	अगर (!np) अणु
		pr_err("No SCU base address\n");
		वापस;
	पूर्ण
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!scu_base) अणु
		pr_err("No SCU remap\n");
		वापस;
	पूर्ण

	scu_enable(scu_base);
	ncores = scu_get_core_count(scu_base);
	क्रम (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);
	iounmap(scu_base);
पूर्ण

अटल पूर्णांक ux500_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	/*
	 * ग_लिखो the address of secondary startup पूर्णांकo the backup ram रेजिस्टर
	 * at offset 0x1FF4, then ग_लिखो the magic number 0xA1FEED01 to the
	 * backup ram रेजिस्टर at offset 0x1FF0, which is what boot rom code
	 * is रुकोing क्रम. This will wake up the secondary core from WFE.
	 */
	ग_लिखोl(__pa_symbol(secondary_startup),
	       backupram + UX500_CPU1_JUMPADDR_OFFSET);
	ग_लिखोl(0xA1FEED01,
	       backupram + UX500_CPU1_WAKEMAGIC_OFFSET);

	/* make sure ग_लिखो buffer is drained */
	mb();
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम ux500_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	wfi();
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations ux500_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= ux500_smp_prepare_cpus,
	.smp_boot_secondary	= ux500_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= ux500_cpu_die,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(ux500_smp, "ste,dbx500-smp", &ux500_smp_ops);
