<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SMP_H
#घोषणा __ASM_SMP_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/pal.h>

/* HACK: Cabrio WHAMI वापस value is bogus अगर more than 8 bits used.. :-( */

अटल __अंतरभूत__ अचिन्हित अक्षर
__hard_smp_processor_id(व्योम)
अणु
	रेजिस्टर अचिन्हित अक्षर __r0 __यंत्र__("$0");
	__यंत्र__ __अस्थिर__(
		"call_pal %1 #whami"
		: "=r"(__r0)
		:"i" (PAL_whami)
		: "$1", "$22", "$23", "$24", "$25");
	वापस __r0;
पूर्ण

#अगर_घोषित CONFIG_SMP

#समावेश <यंत्र/irq.h>

काष्ठा cpuinfo_alpha अणु
	अचिन्हित दीर्घ loops_per_jअगरfy;
	अचिन्हित दीर्घ last_asn;
	पूर्णांक need_new_asn;
	पूर्णांक asn_lock;
	अचिन्हित दीर्घ ipi_count;
	अचिन्हित दीर्घ prof_multiplier;
	अचिन्हित दीर्घ prof_counter;
	अचिन्हित अक्षर mcheck_expected;
	अचिन्हित अक्षर mcheck_taken;
	अचिन्हित अक्षर mcheck_extra;
पूर्ण __attribute__((aligned(64)));

बाह्य काष्ठा cpuinfo_alpha cpu_data[NR_CPUS];

#घोषणा hard_smp_processor_id()	__hard_smp_processor_id()
#घोषणा raw_smp_processor_id()	(current_thपढ़ो_info()->cpu)

बाह्य पूर्णांक smp_num_cpus;

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

#अन्यथा /* CONFIG_SMP */

#घोषणा hard_smp_processor_id()		0
#घोषणा smp_call_function_on_cpu(func,info,रुको,cpu)    (अणु 0; पूर्ण)

#पूर्ण_अगर /* CONFIG_SMP */

#घोषणा NO_PROC_ID	(-1)

#पूर्ण_अगर
