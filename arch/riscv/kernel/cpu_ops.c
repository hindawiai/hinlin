<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/smp.h>

स्थिर काष्ठा cpu_operations *cpu_ops[NR_CPUS] __ro_after_init;

व्योम *__cpu_up_stack_poपूर्णांकer[NR_CPUS] __section(".data");
व्योम *__cpu_up_task_poपूर्णांकer[NR_CPUS] __section(".data");

बाह्य स्थिर काष्ठा cpu_operations cpu_ops_sbi;
बाह्य स्थिर काष्ठा cpu_operations cpu_ops_spinरुको;

व्योम cpu_update_secondary_bootdata(अचिन्हित पूर्णांक cpuid,
				   काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक hartid = cpuid_to_hartid_map(cpuid);

	/* Make sure tidle is updated */
	smp_mb();
	WRITE_ONCE(__cpu_up_stack_poपूर्णांकer[hartid],
		   task_stack_page(tidle) + THREAD_SIZE);
	WRITE_ONCE(__cpu_up_task_poपूर्णांकer[hartid], tidle);
पूर्ण

व्योम __init cpu_set_ops(पूर्णांक cpuid)
अणु
#अगर IS_ENABLED(CONFIG_RISCV_SBI)
	अगर (sbi_probe_extension(SBI_EXT_HSM) > 0) अणु
		अगर (!cpuid)
			pr_info("SBI v0.2 HSM extension detected\n");
		cpu_ops[cpuid] = &cpu_ops_sbi;
	पूर्ण अन्यथा
#पूर्ण_अगर
		cpu_ops[cpuid] = &cpu_ops_spinरुको;
पूर्ण
