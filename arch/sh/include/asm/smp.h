<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SMP_H
#घोषणा __ASM_SH_SMP_H

#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/smp-ops.h>

#अगर_घोषित CONFIG_SMP

#समावेश <linux/atomic.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/percpu.h>

#घोषणा raw_smp_processor_id()	(current_thपढ़ो_info()->cpu)

/* Map from cpu id to sequential logical cpu number. */
बाह्य पूर्णांक __cpu_number_map[NR_CPUS];
#घोषणा cpu_number_map(cpu)  __cpu_number_map[cpu]

/* The reverse map from sequential logical cpu number to cpu id.  */
बाह्य पूर्णांक __cpu_logical_map[NR_CPUS];
#घोषणा cpu_logical_map(cpu)  __cpu_logical_map[cpu]

क्रमागत अणु
	SMP_MSG_FUNCTION,
	SMP_MSG_RESCHEDULE,
	SMP_MSG_FUNCTION_SINGLE,
	SMP_MSG_TIMER,

	SMP_MSG_NR,	/* must be last */
पूर्ण;

DECLARE_PER_CPU(पूर्णांक, cpu_state);

व्योम smp_message_recv(अचिन्हित पूर्णांक msg);

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

व्योम native_play_dead(व्योम);
व्योम native_cpu_die(अचिन्हित पूर्णांक cpu);
पूर्णांक native_cpu_disable(अचिन्हित पूर्णांक cpu);

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम play_dead_common(व्योम);
बाह्य पूर्णांक __cpu_disable(व्योम);

अटल अंतरभूत व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	बाह्य काष्ठा plat_smp_ops *mp_ops;     /* निजी */

	mp_ops->cpu_die(cpu);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक hard_smp_processor_id(व्योम)
अणु
	बाह्य काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	अगर (!mp_ops)
		वापस 0;	/* boot CPU */

	वापस mp_ops->smp_processor_id();
पूर्ण

काष्ठा of_cpu_method अणु
	स्थिर अक्षर *method;
	काष्ठा plat_smp_ops *ops;
पूर्ण;

#घोषणा CPU_METHOD_OF_DECLARE(name, _method, _ops)			\
	अटल स्थिर काष्ठा of_cpu_method __cpu_method_of_table_##name	\
		__used __section("__cpu_method_of_table")		\
		= अणु .method = _method, .ops = _ops पूर्ण

#अन्यथा

#घोषणा hard_smp_processor_id()	(0)

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASM_SH_SMP_H */
