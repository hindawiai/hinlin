<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Imagination Technologies Ltd.
 *
 * Arbitrary Monitor Interface
 */
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/mips-boards/launch.h>
#समावेश <यंत्र/vpe.h>

पूर्णांक amon_cpu_avail(पूर्णांक cpu)
अणु
	काष्ठा cpulaunch *launch = (काष्ठा cpulaunch *)CKSEG0ADDR(CPULAUNCH);

	अगर (cpu < 0 || cpu >= NCPULAUNCH) अणु
		pr_debug("avail: cpu%d is out of range\n", cpu);
		वापस 0;
	पूर्ण

	launch += cpu;
	अगर (!(launch->flags & LAUNCH_FREADY)) अणु
		pr_debug("avail: cpu%d is not ready\n", cpu);
		वापस 0;
	पूर्ण
	अगर (launch->flags & (LAUNCH_FGO|LAUNCH_FGONE)) अणु
		pr_debug("avail: too late.. cpu%d is already gone\n", cpu);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक amon_cpu_start(पूर्णांक cpu,
		    अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp,
		    अचिन्हित दीर्घ gp, अचिन्हित दीर्घ a0)
अणु
	अस्थिर काष्ठा cpulaunch *launch =
		(काष्ठा cpulaunch  *)CKSEG0ADDR(CPULAUNCH);

	अगर (!amon_cpu_avail(cpu))
		वापस -1;
	अगर (cpu == smp_processor_id()) अणु
		pr_debug("launch: I am cpu%d!\n", cpu);
		वापस -1;
	पूर्ण
	launch += cpu;

	pr_debug("launch: starting cpu%d\n", cpu);

	launch->pc = pc;
	launch->gp = gp;
	launch->sp = sp;
	launch->a0 = a0;

	smp_wmb();		/* Target must see parameters beक्रमe go */
	launch->flags |= LAUNCH_FGO;
	smp_wmb();		/* Target must see go beक्रमe we poll  */

	जबतक ((launch->flags & LAUNCH_FGONE) == 0)
		;
	smp_rmb();	/* Target will be updating flags soon */
	pr_debug("launch: cpu%d gone!\n", cpu);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MIPS_VPE_LOADER_CMP
पूर्णांक vpe_run(काष्ठा vpe *v)
अणु
	काष्ठा vpe_notअगरications *n;

	अगर (amon_cpu_start(aprp_cpu_index(), v->__start, 0, 0, 0) < 0)
		वापस -1;

	list_क्रम_each_entry(n, &v->notअगरy, list)
		n->start(VPE_MODULE_MINOR);

	वापस 0;
पूर्ण
#पूर्ण_अगर
