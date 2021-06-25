<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/smp.h>

स्थिर काष्ठा cpu_operations cpu_ops_spinरुको;

अटल पूर्णांक spinरुको_cpu_prepare(अचिन्हित पूर्णांक cpuid)
अणु
	अगर (!cpu_ops_spinरुको.cpu_start) अणु
		pr_err("cpu start method not defined for CPU [%d]\n", cpuid);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक spinरुको_cpu_start(अचिन्हित पूर्णांक cpuid, काष्ठा task_काष्ठा *tidle)
अणु
	/*
	 * In this protocol, all cpus boot on their own accord.  _start
	 * selects the first cpu to boot the kernel and causes the reमुख्यder
	 * of the cpus to spin in a loop रुकोing क्रम their stack poपूर्णांकer to be
	 * setup by that मुख्य cpu.  Writing to bootdata
	 * (i.e __cpu_up_stack_poपूर्णांकer) संकेतs to the spinning cpus that they
	 * can जारी the boot process.
	 */
	cpu_update_secondary_bootdata(cpuid, tidle);

	वापस 0;
पूर्ण

स्थिर काष्ठा cpu_operations cpu_ops_spinरुको = अणु
	.name		= "spinwait",
	.cpu_prepare	= spinरुको_cpu_prepare,
	.cpu_start	= spinरुको_cpu_start,
पूर्ण;
