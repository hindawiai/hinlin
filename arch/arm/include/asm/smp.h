<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/smp.h
 *
 *  Copyright (C) 2004-2005 ARM Ltd.
 */
#अगर_अघोषित __ASM_ARM_SMP_H
#घोषणा __ASM_ARM_SMP_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/thपढ़ो_info.h>

#अगर_अघोषित CONFIG_SMP
# error "<asm/smp.h> included in non-SMP build"
#पूर्ण_अगर

#घोषणा raw_smp_processor_id() (current_thपढ़ो_info()->cpu)

काष्ठा seq_file;

/*
 * generate IPI list text
 */
बाह्य व्योम show_ipi_list(काष्ठा seq_file *, पूर्णांक);

/*
 * Called from assembly code, this handles an IPI.
 */
यंत्रlinkage व्योम करो_IPI(पूर्णांक ipinr, काष्ठा pt_regs *regs);

/*
 * Called from C code, this handles an IPI.
 */
व्योम handle_IPI(पूर्णांक ipinr, काष्ठा pt_regs *regs);

/*
 * Setup the set of possible CPUs (via set_cpu_possible)
 */
बाह्य व्योम smp_init_cpus(व्योम);

/*
 * Register IPI पूर्णांकerrupts with the arch SMP code
 */
बाह्य व्योम set_smp_ipi_range(पूर्णांक ipi_base, पूर्णांक nr_ipi);

/*
 * Called from platक्रमm specअगरic assembly code, this is the
 * secondary CPU entry poपूर्णांक.
 */
यंत्रlinkage व्योम secondary_start_kernel(व्योम);


/*
 * Initial data क्रम bringing up a secondary CPU.
 */
काष्ठा secondary_data अणु
	जोड़ अणु
		काष्ठा mpu_rgn_info *mpu_rgn_info;
		u64 pgdir;
	पूर्ण;
	अचिन्हित दीर्घ swapper_pg_dir;
	व्योम *stack;
पूर्ण;
बाह्य काष्ठा secondary_data secondary_data;
बाह्य व्योम secondary_startup(व्योम);
बाह्य व्योम secondary_startup_arm(व्योम);

बाह्य पूर्णांक __cpu_disable(व्योम);

बाह्य व्योम __cpu_die(अचिन्हित पूर्णांक cpu);

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);
बाह्य व्योम arch_send_wakeup_ipi_mask(स्थिर काष्ठा cpumask *mask);

बाह्य पूर्णांक रेजिस्टर_ipi_completion(काष्ठा completion *completion, पूर्णांक cpu);

काष्ठा smp_operations अणु
#अगर_घोषित CONFIG_SMP
	/*
	 * Setup the set of possible CPUs (via set_cpu_possible)
	 */
	व्योम (*smp_init_cpus)(व्योम);
	/*
	 * Initialize cpu_possible map, and enable coherency
	 */
	व्योम (*smp_prepare_cpus)(अचिन्हित पूर्णांक max_cpus);

	/*
	 * Perक्रमm platक्रमm specअगरic initialisation of the specअगरied CPU.
	 */
	व्योम (*smp_secondary_init)(अचिन्हित पूर्णांक cpu);
	/*
	 * Boot a secondary CPU, and assign it the specअगरied idle task.
	 * This also gives us the initial stack to use क्रम this CPU.
	 */
	पूर्णांक  (*smp_boot_secondary)(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle);
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक  (*cpu_समाप्त)(अचिन्हित पूर्णांक cpu);
	व्योम (*cpu_die)(अचिन्हित पूर्णांक cpu);
	bool  (*cpu_can_disable)(अचिन्हित पूर्णांक cpu);
	पूर्णांक  (*cpu_disable)(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

काष्ठा of_cpu_method अणु
	स्थिर अक्षर *method;
	स्थिर काष्ठा smp_operations *ops;
पूर्ण;

#घोषणा CPU_METHOD_OF_DECLARE(name, _method, _ops)			\
	अटल स्थिर काष्ठा of_cpu_method __cpu_method_of_table_##name	\
		__used __section("__cpu_method_of_table")		\
		= अणु .method = _method, .ops = _ops पूर्ण
/*
 * set platक्रमm specअगरic SMP operations
 */
बाह्य व्योम smp_set_ops(स्थिर काष्ठा smp_operations *);

#पूर्ण_अगर /* अगरndef __ASM_ARM_SMP_H */
