<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* smp.h: Sparc64 specअगरic SMP stuff.
 *
 * Copyright (C) 1996, 2008 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _SPARC64_SMP_H
#घोषणा _SPARC64_SMP_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/starfire.h>
#समावेश <यंत्र/spitfire.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/cpumask.h>
#समावेश <linux/cache.h>

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#अगर_घोषित CONFIG_SMP

#अगर_अघोषित __ASSEMBLY__

/*
 *	Private routines/data
 */

#समावेश <linux/bitops.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/percpu.h>

DECLARE_PER_CPU(cpumask_t, cpu_sibling_map);
बाह्य cpumask_t cpu_core_map[NR_CPUS];

व्योम smp_init_cpu_poke(व्योम);
व्योम scheduler_poke(व्योम);

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

/*
 *	General functions that each host प्रणाली must provide.
 */

पूर्णांक hard_smp_processor_id(व्योम);
#घोषणा raw_smp_processor_id() (current_thपढ़ो_info()->cpu)

व्योम smp_fill_in_cpu_possible_map(व्योम);
व्योम smp_fill_in_sib_core_maps(व्योम);
व्योम cpu_play_dead(व्योम);

व्योम smp_fetch_global_regs(व्योम);
व्योम smp_fetch_global_pmu(व्योम);

काष्ठा seq_file;
व्योम smp_bogo(काष्ठा seq_file *);
व्योम smp_info(काष्ठा seq_file *);

व्योम smp_callin(व्योम);
व्योम cpu_panic(व्योम);
व्योम smp_synchronize_tick_client(व्योम);
व्योम smp_capture(व्योम);
व्योम smp_release(व्योम);

#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक __cpu_disable(व्योम);
व्योम __cpu_die(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#अन्यथा

#घोषणा hard_smp_processor_id()		0
#घोषणा smp_fill_in_sib_core_maps() करो अणु पूर्ण जबतक (0)
#घोषणा smp_fetch_global_regs() करो अणु पूर्ण जबतक (0)
#घोषणा smp_fetch_global_pmu() करो अणु पूर्ण जबतक (0)
#घोषणा smp_fill_in_cpu_possible_map() करो अणु पूर्ण जबतक (0)
#घोषणा smp_init_cpu_poke() करो अणु पूर्ण जबतक (0)
#घोषणा scheduler_poke() करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* !(CONFIG_SMP) */

#पूर्ण_अगर /* !(_SPARC64_SMP_H) */
