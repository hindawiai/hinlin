<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम R-Mobile / SH-Mobile
 *
 * Copyright (C) 2010  Magnus Damm
 * Copyright (C) 2011  Paul Mundt
 *
 * Based on vexpress, Copyright (C) 2002 ARM Ltd, All Rights Reserved
 */
#समावेश <linux/init.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश "common.h"

बाह्य अचिन्हित दीर्घ shmobile_smp_fn[];
बाह्य अचिन्हित दीर्घ shmobile_smp_arg[];
बाह्य अचिन्हित दीर्घ shmobile_smp_mpidr[];

व्योम shmobile_smp_hook(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ fn, अचिन्हित दीर्घ arg)
अणु
	shmobile_smp_fn[cpu] = 0;
	flush_cache_all();

	shmobile_smp_mpidr[cpu] = cpu_logical_map(cpu);
	shmobile_smp_fn[cpu] = fn;
	shmobile_smp_arg[cpu] = arg;
	flush_cache_all();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
bool shmobile_smp_cpu_can_disable(अचिन्हित पूर्णांक cpu)
अणु
	वापस true; /* Hotplug of any CPU is supported */
पूर्ण
#पूर्ण_अगर
