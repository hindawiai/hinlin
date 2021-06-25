<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_SMP_H
#घोषणा _XTENSA_SMP_H

#अगर_घोषित CONFIG_SMP

#घोषणा raw_smp_processor_id()	(current_thपढ़ो_info()->cpu)
#घोषणा cpu_logical_map(cpu)	(cpu)

काष्ठा start_info अणु
	अचिन्हित दीर्घ stack;
पूर्ण;
बाह्य काष्ठा start_info start_info;

काष्ठा cpumask;
व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);
व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);

व्योम smp_init_cpus(व्योम);
व्योम secondary_init_irq(व्योम);
व्योम ipi_init(व्योम);
काष्ठा seq_file;
व्योम show_ipi_list(काष्ठा seq_file *p, पूर्णांक prec);

#अगर_घोषित CONFIG_HOTPLUG_CPU

व्योम __cpu_die(अचिन्हित पूर्णांक cpu);
पूर्णांक __cpu_disable(व्योम);
व्योम cpu_die(व्योम);
व्योम cpu_restart(व्योम);

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर	/* _XTENSA_SMP_H */
