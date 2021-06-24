<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tracepoपूर्णांक definitions क्रम s390
 *
 * Copyright IBM Corp. 2015
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/percpu.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace/diag.h>

EXPORT_TRACEPOINT_SYMBOL(s390_diagnose);

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, diagnose_trace_depth);

व्योम notrace trace_s390_diagnose_norecursion(पूर्णांक diag_nr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक *depth;

	/* Aव्योम lockdep recursion. */
	अगर (IS_ENABLED(CONFIG_LOCKDEP))
		वापस;
	local_irq_save(flags);
	depth = this_cpu_ptr(&diagnose_trace_depth);
	अगर (*depth == 0) अणु
		(*depth)++;
		trace_s390_diagnose(diag_nr);
		(*depth)--;
	पूर्ण
	local_irq_restore(flags);
पूर्ण
