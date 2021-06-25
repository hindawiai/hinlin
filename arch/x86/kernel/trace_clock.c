<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * X86 trace घड़ीs
 */
#समावेश <यंत्र/trace_घड़ी.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/msr.h>

/*
 * trace_घड़ी_x86_tsc(): A घड़ी that is just the cycle counter.
 *
 * Unlike the other घड़ीs, this is not in nanoseconds.
 */
u64 notrace trace_घड़ी_x86_tsc(व्योम)
अणु
	वापस rdtsc_ordered();
पूर्ण
