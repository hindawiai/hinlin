<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace context चयन
 *
 * Copyright (C) 2007 Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ftrace.h>
#समावेश <trace/events/sched.h>

#समावेश "trace.h"

#घोषणा RECORD_CMDLINE	1
#घोषणा RECORD_TGID	2

अटल पूर्णांक		sched_cmdline_ref;
अटल पूर्णांक		sched_tgid_ref;
अटल DEFINE_MUTEX(sched_रेजिस्टर_mutex);

अटल व्योम
probe_sched_चयन(व्योम *ignore, bool preempt,
		   काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	पूर्णांक flags;

	flags = (RECORD_TGID * !!sched_tgid_ref) +
		(RECORD_CMDLINE * !!sched_cmdline_ref);

	अगर (!flags)
		वापस;
	tracing_record_taskinfo_sched_चयन(prev, next, flags);
पूर्ण

अटल व्योम
probe_sched_wakeup(व्योम *ignore, काष्ठा task_काष्ठा *wakee)
अणु
	पूर्णांक flags;

	flags = (RECORD_TGID * !!sched_tgid_ref) +
		(RECORD_CMDLINE * !!sched_cmdline_ref);

	अगर (!flags)
		वापस;
	tracing_record_taskinfo(current, flags);
पूर्ण

अटल पूर्णांक tracing_sched_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_trace_sched_wakeup(probe_sched_wakeup, शून्य);
	अगर (ret) अणु
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_wakeup\n");
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_trace_sched_wakeup_new(probe_sched_wakeup, शून्य);
	अगर (ret) अणु
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_wakeup_new\n");
		जाओ fail_deprobe;
	पूर्ण

	ret = रेजिस्टर_trace_sched_चयन(probe_sched_चयन, शून्य);
	अगर (ret) अणु
		pr_info("sched trace: Couldn't activate tracepoint"
			" probe to kernel_sched_switch\n");
		जाओ fail_deprobe_wake_new;
	पूर्ण

	वापस ret;
fail_deprobe_wake_new:
	unरेजिस्टर_trace_sched_wakeup_new(probe_sched_wakeup, शून्य);
fail_deprobe:
	unरेजिस्टर_trace_sched_wakeup(probe_sched_wakeup, शून्य);
	वापस ret;
पूर्ण

अटल व्योम tracing_sched_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_trace_sched_चयन(probe_sched_चयन, शून्य);
	unरेजिस्टर_trace_sched_wakeup_new(probe_sched_wakeup, शून्य);
	unरेजिस्टर_trace_sched_wakeup(probe_sched_wakeup, शून्य);
पूर्ण

अटल व्योम tracing_start_sched_चयन(पूर्णांक ops)
अणु
	bool sched_रेजिस्टर;

	mutex_lock(&sched_रेजिस्टर_mutex);
	sched_रेजिस्टर = (!sched_cmdline_ref && !sched_tgid_ref);

	चयन (ops) अणु
	हाल RECORD_CMDLINE:
		sched_cmdline_ref++;
		अवरोध;

	हाल RECORD_TGID:
		sched_tgid_ref++;
		अवरोध;
	पूर्ण

	अगर (sched_रेजिस्टर && (sched_cmdline_ref || sched_tgid_ref))
		tracing_sched_रेजिस्टर();
	mutex_unlock(&sched_रेजिस्टर_mutex);
पूर्ण

अटल व्योम tracing_stop_sched_चयन(पूर्णांक ops)
अणु
	mutex_lock(&sched_रेजिस्टर_mutex);

	चयन (ops) अणु
	हाल RECORD_CMDLINE:
		sched_cmdline_ref--;
		अवरोध;

	हाल RECORD_TGID:
		sched_tgid_ref--;
		अवरोध;
	पूर्ण

	अगर (!sched_cmdline_ref && !sched_tgid_ref)
		tracing_sched_unरेजिस्टर();
	mutex_unlock(&sched_रेजिस्टर_mutex);
पूर्ण

व्योम tracing_start_cmdline_record(व्योम)
अणु
	tracing_start_sched_चयन(RECORD_CMDLINE);
पूर्ण

व्योम tracing_stop_cmdline_record(व्योम)
अणु
	tracing_stop_sched_चयन(RECORD_CMDLINE);
पूर्ण

व्योम tracing_start_tgid_record(व्योम)
अणु
	tracing_start_sched_चयन(RECORD_TGID);
पूर्ण

व्योम tracing_stop_tgid_record(व्योम)
अणु
	tracing_stop_sched_चयन(RECORD_TGID);
पूर्ण
