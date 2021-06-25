<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2004
 *
 *  Author: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _S390_CPUTIME_H
#घोषणा _S390_CPUTIME_H

#समावेश <linux/types.h>
#समावेश <यंत्र/समयx.h>

#घोषणा CPUTIME_PER_USEC 4096ULL
#घोषणा CPUTIME_PER_SEC (CPUTIME_PER_USEC * USEC_PER_SEC)

/* We want to use full resolution of the CPU समयr: 2**-12 micro-seconds. */

#घोषणा cmpxchg_cpuसमय(ptr, old, new) cmpxchg64(ptr, old, new)

/*
 * Convert cpuसमय to microseconds.
 */
अटल अंतरभूत u64 cpuसमय_प्रकारo_usecs(स्थिर u64 cpuसमय)
अणु
	वापस cpuसमय >> 12;
पूर्ण

/*
 * Convert cpuसमय to nanoseconds.
 */
#घोषणा cpuसमय_प्रकारo_nsecs(cpuसमय) tod_to_ns(cpuसमय)

u64 arch_cpu_idle_समय(पूर्णांक cpu);

#घोषणा arch_idle_समय(cpu) arch_cpu_idle_समय(cpu)

व्योम account_idle_समय_irq(व्योम);

#पूर्ण_अगर /* _S390_CPUTIME_H */
