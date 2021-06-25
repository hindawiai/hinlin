<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 1999, 2012
 *    Author(s): Denis Joseph Barrow,
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 */
#अगर_अघोषित __ASM_SMP_H
#घोषणा __ASM_SMP_H

#समावेश <यंत्र/sigp.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/processor.h>

#घोषणा raw_smp_processor_id()	(S390_lowcore.cpu_nr)

बाह्य काष्ठा mutex smp_cpu_state_mutex;
बाह्य अचिन्हित पूर्णांक smp_cpu_mt_shअगरt;
बाह्य अचिन्हित पूर्णांक smp_cpu_mtid;
बाह्य __vector128 __initdata boot_cpu_vector_save_area[__NUM_VXRS];

बाह्य पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle);

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

बाह्य व्योम smp_call_online_cpu(व्योम (*func)(व्योम *), व्योम *);
बाह्य व्योम smp_call_ipl_cpu(व्योम (*func)(व्योम *), व्योम *);
बाह्य व्योम smp_emergency_stop(व्योम);

बाह्य पूर्णांक smp_find_processor_id(u16 address);
बाह्य पूर्णांक smp_store_status(पूर्णांक cpu);
बाह्य व्योम smp_save_dump_cpus(व्योम);
बाह्य व्योम smp_yield_cpu(पूर्णांक cpu);
बाह्य व्योम smp_cpu_set_polarization(पूर्णांक cpu, पूर्णांक val);
बाह्य पूर्णांक smp_cpu_get_polarization(पूर्णांक cpu);
बाह्य पूर्णांक smp_cpu_get_cpu_address(पूर्णांक cpu);
बाह्य व्योम smp_fill_possible_mask(व्योम);
बाह्य व्योम smp_detect_cpus(व्योम);

अटल अंतरभूत व्योम smp_stop_cpu(व्योम)
अणु
	u16 pcpu = stap();

	क्रम (;;) अणु
		__pcpu_sigp(pcpu, SIGP_STOP, 0, शून्य);
		cpu_relax();
	पूर्ण
पूर्ण

/* Return thपढ़ो 0 CPU number as base CPU */
अटल अंतरभूत पूर्णांक smp_get_base_cpu(पूर्णांक cpu)
अणु
	वापस cpu - (cpu % (smp_cpu_mtid + 1));
पूर्ण

अटल अंतरभूत व्योम smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

बाह्य पूर्णांक smp_rescan_cpus(व्योम);
बाह्य व्योम __noवापस cpu_die(व्योम);
बाह्य व्योम __cpu_die(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक __cpu_disable(व्योम);
बाह्य व्योम schedule_mcck_handler(व्योम);
व्योम notrace smp_yield_cpu(पूर्णांक cpu);

#पूर्ण_अगर /* __ASM_SMP_H */
