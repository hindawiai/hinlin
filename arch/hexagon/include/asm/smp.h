<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SMP definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __ASM_SMP_H
#घोषणा __ASM_SMP_H

#समावेश <linux/cpumask.h>

#घोषणा raw_smp_processor_id() (current_thपढ़ो_info()->cpu)

क्रमागत ipi_message_type अणु
	IPI_NOP = 0,
	IPI_RESCHEDULE = 1,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
	IPI_TIMER,
पूर्ण;

बाह्य व्योम send_ipi(स्थिर काष्ठा cpumask *cpumask, क्रमागत ipi_message_type msg);
बाह्य व्योम smp_start_cpus(व्योम);
बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

बाह्य व्योम smp_vm_unmask_irq(व्योम *info);

#पूर्ण_अगर
