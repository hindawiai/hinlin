<शैली गुरु>
/*
 * Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __ASM_OPENRISC_SMP_H
#घोषणा __ASM_OPENRISC_SMP_H

#समावेश <यंत्र/spr.h>
#समावेश <यंत्र/spr_defs.h>

#घोषणा raw_smp_processor_id()	(current_thपढ़ो_info()->cpu)
#घोषणा hard_smp_processor_id()	mfspr(SPR_COREID)

बाह्य व्योम smp_init_cpus(व्योम);

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

बाह्य व्योम set_smp_cross_call(व्योम (*)(स्थिर काष्ठा cpumask *, अचिन्हित पूर्णांक));
बाह्य व्योम handle_IPI(अचिन्हित पूर्णांक ipi_msg);

#पूर्ण_अगर /* __ASM_OPENRISC_SMP_H */
