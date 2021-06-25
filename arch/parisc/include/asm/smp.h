<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SMP_H
#घोषणा __ASM_SMP_H

बाह्य पूर्णांक init_per_cpu(पूर्णांक cpuid);

#अगर defined(CONFIG_SMP)

/* Page Zero Location PDC will look क्रम the address to branch to when we poke
** slave CPUs still in "Icache loop".
*/
#घोषणा PDC_OS_BOOT_RENDEZVOUS     0x10
#घोषणा PDC_OS_BOOT_RENDEZVOUS_HI  0x28

#अगर_अघोषित ASSEMBLY
#समावेश <linux/bitops.h>
#समावेश <linux/thपढ़ोs.h>	/* क्रम NR_CPUS */
#समावेश <linux/cpumask.h>
प्रकार अचिन्हित दीर्घ address_t;


/*
 *	Private routines/data
 *
 *	physical and logical are equivalent until we support CPU hotplug.
 */
#घोषणा cpu_number_map(cpu)	(cpu)
#घोषणा cpu_logical_map(cpu)	(cpu)

बाह्य व्योम smp_send_all_nop(व्योम);

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

#पूर्ण_अगर /* !ASSEMBLY */

#घोषणा raw_smp_processor_id()	(current_thपढ़ो_info()->cpu)

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत व्योम smp_send_all_nop(व्योम) अणु वापस; पूर्ण

#पूर्ण_अगर

#घोषणा NO_PROC_ID		0xFF		/* No processor magic marker */
#घोषणा ANY_PROC_ID		0xFF		/* Any processor magic marker */
अटल अंतरभूत पूर्णांक __cpu_disable (व्योम) अणु
  वापस 0;
पूर्ण
अटल अंतरभूत व्योम __cpu_die (अचिन्हित पूर्णांक cpu) अणु
  जबतक(1)
    ;
पूर्ण

#पूर्ण_अगर /*  __ASM_SMP_H */
