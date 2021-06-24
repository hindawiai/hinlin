<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_SMP_H
#घोषणा __ASM_CSKY_SMP_H

#समावेश <linux/cpumask.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/thपढ़ोs.h>

#अगर_घोषित CONFIG_SMP

व्योम __init setup_smp(व्योम);

व्योम __init setup_smp_ipi(व्योम);

व्योम arch_send_call_function_ipi_mask(काष्ठा cpumask *mask);

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);

व्योम __init set_send_ipi(व्योम (*func)(स्थिर काष्ठा cpumask *mask), पूर्णांक irq);

#घोषणा raw_smp_processor_id()	(current_thपढ़ो_info()->cpu)

पूर्णांक __cpu_disable(व्योम);

व्योम __cpu_die(अचिन्हित पूर्णांक cpu);

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASM_CSKY_SMP_H */
