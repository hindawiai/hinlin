<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * preemptoff and irqoff tracepoपूर्णांकs
 *
 * Copyright (C) Joel Fernandes (Google) <joel@joelfernandes.org>
 */

#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kprobes.h>
#समावेश "trace.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/preemptirq.h>

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
/* Per-cpu variable to prevent redundant calls when IRQs alपढ़ोy off */
अटल DEFINE_PER_CPU(पूर्णांक, tracing_irq_cpu);

/*
 * Like trace_hardirqs_on() but without the lockdep invocation. This is
 * used in the low level entry code where the ordering vs. RCU is important
 * and lockdep uses a staged approach which splits the lockdep hardirq
 * tracking पूर्णांकo a RCU on and a RCU off section.
 */
व्योम trace_hardirqs_on_prepare(व्योम)
अणु
	अगर (this_cpu_पढ़ो(tracing_irq_cpu)) अणु
		अगर (!in_nmi())
			trace_irq_enable(CALLER_ADDR0, CALLER_ADDR1);
		tracer_hardirqs_on(CALLER_ADDR0, CALLER_ADDR1);
		this_cpu_ग_लिखो(tracing_irq_cpu, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(trace_hardirqs_on_prepare);
NOKPROBE_SYMBOL(trace_hardirqs_on_prepare);

व्योम trace_hardirqs_on(व्योम)
अणु
	अगर (this_cpu_पढ़ो(tracing_irq_cpu)) अणु
		अगर (!in_nmi())
			trace_irq_enable_rcuidle(CALLER_ADDR0, CALLER_ADDR1);
		tracer_hardirqs_on(CALLER_ADDR0, CALLER_ADDR1);
		this_cpu_ग_लिखो(tracing_irq_cpu, 0);
	पूर्ण

	lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	lockdep_hardirqs_on(CALLER_ADDR0);
पूर्ण
EXPORT_SYMBOL(trace_hardirqs_on);
NOKPROBE_SYMBOL(trace_hardirqs_on);

/*
 * Like trace_hardirqs_off() but without the lockdep invocation. This is
 * used in the low level entry code where the ordering vs. RCU is important
 * and lockdep uses a staged approach which splits the lockdep hardirq
 * tracking पूर्णांकo a RCU on and a RCU off section.
 */
व्योम trace_hardirqs_off_finish(व्योम)
अणु
	अगर (!this_cpu_पढ़ो(tracing_irq_cpu)) अणु
		this_cpu_ग_लिखो(tracing_irq_cpu, 1);
		tracer_hardirqs_off(CALLER_ADDR0, CALLER_ADDR1);
		अगर (!in_nmi())
			trace_irq_disable(CALLER_ADDR0, CALLER_ADDR1);
	पूर्ण

पूर्ण
EXPORT_SYMBOL(trace_hardirqs_off_finish);
NOKPROBE_SYMBOL(trace_hardirqs_off_finish);

व्योम trace_hardirqs_off(व्योम)
अणु
	lockdep_hardirqs_off(CALLER_ADDR0);

	अगर (!this_cpu_पढ़ो(tracing_irq_cpu)) अणु
		this_cpu_ग_लिखो(tracing_irq_cpu, 1);
		tracer_hardirqs_off(CALLER_ADDR0, CALLER_ADDR1);
		अगर (!in_nmi())
			trace_irq_disable_rcuidle(CALLER_ADDR0, CALLER_ADDR1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(trace_hardirqs_off);
NOKPROBE_SYMBOL(trace_hardirqs_off);

__visible व्योम trace_hardirqs_on_caller(अचिन्हित दीर्घ caller_addr)
अणु
	अगर (this_cpu_पढ़ो(tracing_irq_cpu)) अणु
		अगर (!in_nmi())
			trace_irq_enable_rcuidle(CALLER_ADDR0, caller_addr);
		tracer_hardirqs_on(CALLER_ADDR0, caller_addr);
		this_cpu_ग_लिखो(tracing_irq_cpu, 0);
	पूर्ण

	lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	lockdep_hardirqs_on(CALLER_ADDR0);
पूर्ण
EXPORT_SYMBOL(trace_hardirqs_on_caller);
NOKPROBE_SYMBOL(trace_hardirqs_on_caller);

__visible व्योम trace_hardirqs_off_caller(अचिन्हित दीर्घ caller_addr)
अणु
	lockdep_hardirqs_off(CALLER_ADDR0);

	अगर (!this_cpu_पढ़ो(tracing_irq_cpu)) अणु
		this_cpu_ग_लिखो(tracing_irq_cpu, 1);
		tracer_hardirqs_off(CALLER_ADDR0, caller_addr);
		अगर (!in_nmi())
			trace_irq_disable_rcuidle(CALLER_ADDR0, caller_addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(trace_hardirqs_off_caller);
NOKPROBE_SYMBOL(trace_hardirqs_off_caller);
#पूर्ण_अगर /* CONFIG_TRACE_IRQFLAGS */

#अगर_घोषित CONFIG_TRACE_PREEMPT_TOGGLE

व्योम trace_preempt_on(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1)
अणु
	अगर (!in_nmi())
		trace_preempt_enable_rcuidle(a0, a1);
	tracer_preempt_on(a0, a1);
पूर्ण

व्योम trace_preempt_off(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1)
अणु
	अगर (!in_nmi())
		trace_preempt_disable_rcuidle(a0, a1);
	tracer_preempt_off(a0, a1);
पूर्ण
#पूर्ण_अगर
