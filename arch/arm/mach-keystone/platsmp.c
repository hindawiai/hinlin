<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keystone SOC SMP platक्रमm code
 *
 * Copyright 2013 Texas Instruments, Inc.
 *	Cyril Chemparathy <cyril@ti.com>
 *	Santosh Shilimkar <santosh.shillimkar@ti.com>
 *
 * Based on platsmp.c, Copyright (C) 2002 ARM Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "keystone.h"

अटल पूर्णांक keystone_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
						काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ start = virt_to_idmap(&secondary_startup);
	पूर्णांक error;

	pr_debug("keystone-smp: booting cpu %d, vector %08lx\n",
		 cpu, start);

	error = keystone_cpu_smc(KEYSTONE_MON_CPU_UP_IDX, cpu, start);
	अगर (error)
		pr_err("CPU %d bringup failed with %d\n", cpu, error);

	वापस error;
पूर्ण

स्थिर काष्ठा smp_operations keystone_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= keystone_smp_boot_secondary,
पूर्ण;
