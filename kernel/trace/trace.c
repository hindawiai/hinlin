<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ring buffer based function tracer
 *
 * Copyright (C) 2007-2012 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2008 Ingo Molnar <mingo@redhat.com>
 *
 * Originally taken from the RT patch by:
 *    Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Based on code from the latency_tracer, that is:
 *  Copyright (C) 2004-2006 Ingo Molnar
 *  Copyright (C) 2004 Nadia Yvette Chambers
 */
#समावेश <linux/ring_buffer.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/security.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/tracefs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/linkage.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <linux/splice.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/माला.स>
#समावेश <linux/mount.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/nmi.h>
#समावेश <linux/fs.h>
#समावेश <linux/trace.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/workqueue.h>

#समावेश "trace.h"
#समावेश "trace_output.h"

/*
 * On boot up, the ring buffer is set to the minimum size, so that
 * we करो not waste memory on प्रणालीs that are not using tracing.
 */
bool ring_buffer_expanded;

/*
 * We need to change this state when a selftest is running.
 * A selftest will lurk पूर्णांकo the ring-buffer to count the
 * entries inserted during the selftest although some concurrent
 * insertions पूर्णांकo the ring-buffer such as trace_prपूर्णांकk could occurred
 * at the same समय, giving false positive or negative results.
 */
अटल bool __पढ़ो_mostly tracing_selftest_running;

/*
 * If boot-समय tracing including tracers/events via kernel cmdline
 * is running, we करो not want to run SELFTEST.
 */
bool __पढ़ो_mostly tracing_selftest_disabled;

#अगर_घोषित CONFIG_FTRACE_STARTUP_TEST
व्योम __init disable_tracing_selftest(स्थिर अक्षर *reason)
अणु
	अगर (!tracing_selftest_disabled) अणु
		tracing_selftest_disabled = true;
		pr_info("Ftrace startup test is disabled due to %s\n", reason);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* Pipe tracepoपूर्णांकs to prपूर्णांकk */
काष्ठा trace_iterator *tracepoपूर्णांक_prपूर्णांक_iter;
पूर्णांक tracepoपूर्णांक_prपूर्णांकk;
अटल DEFINE_STATIC_KEY_FALSE(tracepoपूर्णांक_prपूर्णांकk_key);

/* For tracers that करोn't implement custom flags */
अटल काष्ठा tracer_opt dummy_tracer_opt[] = अणु
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक
dummy_set_flag(काष्ठा trace_array *tr, u32 old_flags, u32 bit, पूर्णांक set)
अणु
	वापस 0;
पूर्ण

/*
 * To prevent the comm cache from being overwritten when no
 * tracing is active, only save the comm when a trace event
 * occurred.
 */
अटल DEFINE_PER_CPU(bool, trace_taskinfo_save);

/*
 * Kill all tracing क्रम good (never come back).
 * It is initialized to 1 but will turn to zero अगर the initialization
 * of the tracer is successful. But that is the only place that sets
 * this back to zero.
 */
अटल पूर्णांक tracing_disabled = 1;

cpumask_var_t __पढ़ो_mostly	tracing_buffer_mask;

/*
 * ftrace_dump_on_oops - variable to dump ftrace buffer on oops
 *
 * If there is an oops (or kernel panic) and the ftrace_dump_on_oops
 * is set, then ftrace_dump is called. This will output the contents
 * of the ftrace buffers to the console.  This is very useful क्रम
 * capturing traces that lead to crashes and outputing it to a
 * serial console.
 *
 * It is शेष off, but you can enable it with either specअगरying
 * "ftrace_dump_on_oops" in the kernel command line, or setting
 * /proc/sys/kernel/ftrace_dump_on_oops
 * Set 1 अगर you want to dump buffers of all CPUs
 * Set 2 अगर you want to dump the buffer of the CPU that triggered oops
 */

क्रमागत ftrace_dump_mode ftrace_dump_on_oops;

/* When set, tracing will stop when a WARN*() is hit */
पूर्णांक __disable_trace_on_warning;

#अगर_घोषित CONFIG_TRACE_EVAL_MAP_खाता
/* Map of क्रमागतs to their values, क्रम "eval_map" file */
काष्ठा trace_eval_map_head अणु
	काष्ठा module			*mod;
	अचिन्हित दीर्घ			length;
पूर्ण;

जोड़ trace_eval_map_item;

काष्ठा trace_eval_map_tail अणु
	/*
	 * "end" is first and poपूर्णांकs to शून्य as it must be dअगरferent
	 * than "mod" or "eval_string"
	 */
	जोड़ trace_eval_map_item	*next;
	स्थिर अक्षर			*end;	/* poपूर्णांकs to शून्य */
पूर्ण;

अटल DEFINE_MUTEX(trace_eval_mutex);

/*
 * The trace_eval_maps are saved in an array with two extra elements,
 * one at the beginning, and one at the end. The beginning item contains
 * the count of the saved maps (head.length), and the module they
 * beदीर्घ to अगर not built in (head.mod). The ending item contains a
 * poपूर्णांकer to the next array of saved eval_map items.
 */
जोड़ trace_eval_map_item अणु
	काष्ठा trace_eval_map		map;
	काष्ठा trace_eval_map_head	head;
	काष्ठा trace_eval_map_tail	tail;
पूर्ण;

अटल जोड़ trace_eval_map_item *trace_eval_maps;
#पूर्ण_अगर /* CONFIG_TRACE_EVAL_MAP_खाता */

पूर्णांक tracing_set_tracer(काष्ठा trace_array *tr, स्थिर अक्षर *buf);
अटल व्योम ftrace_trace_userstack(काष्ठा trace_array *tr,
				   काष्ठा trace_buffer *buffer,
				   अचिन्हित पूर्णांक trace_ctx);

#घोषणा MAX_TRACER_SIZE		100
अटल अक्षर bootup_tracer_buf[MAX_TRACER_SIZE] __initdata;
अटल अक्षर *शेष_bootup_tracer;

अटल bool allocate_snapshot;

अटल पूर्णांक __init set_cmdline_ftrace(अक्षर *str)
अणु
	strlcpy(bootup_tracer_buf, str, MAX_TRACER_SIZE);
	शेष_bootup_tracer = bootup_tracer_buf;
	/* We are using ftrace early, expand it */
	ring_buffer_expanded = true;
	वापस 1;
पूर्ण
__setup("ftrace=", set_cmdline_ftrace);

अटल पूर्णांक __init set_ftrace_dump_on_oops(अक्षर *str)
अणु
	अगर (*str++ != '=' || !*str) अणु
		ftrace_dump_on_oops = DUMP_ALL;
		वापस 1;
	पूर्ण

	अगर (!म_भेद("orig_cpu", str)) अणु
		ftrace_dump_on_oops = DUMP_ORIG;
                वापस 1;
        पूर्ण

        वापस 0;
पूर्ण
__setup("ftrace_dump_on_oops", set_ftrace_dump_on_oops);

अटल पूर्णांक __init stop_trace_on_warning(अक्षर *str)
अणु
	अगर ((म_भेद(str, "=0") != 0 && म_भेद(str, "=off") != 0))
		__disable_trace_on_warning = 1;
	वापस 1;
पूर्ण
__setup("traceoff_on_warning", stop_trace_on_warning);

अटल पूर्णांक __init boot_alloc_snapshot(अक्षर *str)
अणु
	allocate_snapshot = true;
	/* We also need the मुख्य ring buffer expanded */
	ring_buffer_expanded = true;
	वापस 1;
पूर्ण
__setup("alloc_snapshot", boot_alloc_snapshot);


अटल अक्षर trace_boot_options_buf[MAX_TRACER_SIZE] __initdata;

अटल पूर्णांक __init set_trace_boot_options(अक्षर *str)
अणु
	strlcpy(trace_boot_options_buf, str, MAX_TRACER_SIZE);
	वापस 0;
पूर्ण
__setup("trace_options=", set_trace_boot_options);

अटल अक्षर trace_boot_घड़ी_buf[MAX_TRACER_SIZE] __initdata;
अटल अक्षर *trace_boot_घड़ी __initdata;

अटल पूर्णांक __init set_trace_boot_घड़ी(अक्षर *str)
अणु
	strlcpy(trace_boot_घड़ी_buf, str, MAX_TRACER_SIZE);
	trace_boot_घड़ी = trace_boot_घड़ी_buf;
	वापस 0;
पूर्ण
__setup("trace_clock=", set_trace_boot_घड़ी);

अटल पूर्णांक __init set_tracepoपूर्णांक_prपूर्णांकk(अक्षर *str)
अणु
	अगर ((म_भेद(str, "=0") != 0 && म_भेद(str, "=off") != 0))
		tracepoपूर्णांक_prपूर्णांकk = 1;
	वापस 1;
पूर्ण
__setup("tp_printk", set_tracepoपूर्णांक_prपूर्णांकk);

अचिन्हित दीर्घ दीर्घ ns2usecs(u64 nsec)
अणु
	nsec += 500;
	करो_भाग(nsec, 1000);
	वापस nsec;
पूर्ण

अटल व्योम
trace_process_export(काष्ठा trace_export *export,
	       काष्ठा ring_buffer_event *event, पूर्णांक flag)
अणु
	काष्ठा trace_entry *entry;
	अचिन्हित पूर्णांक size = 0;

	अगर (export->flags & flag) अणु
		entry = ring_buffer_event_data(event);
		size = ring_buffer_event_length(event);
		export->ग_लिखो(export, entry, size);
	पूर्ण
पूर्ण

अटल DEFINE_MUTEX(ftrace_export_lock);

अटल काष्ठा trace_export __rcu *ftrace_exports_list __पढ़ो_mostly;

अटल DEFINE_STATIC_KEY_FALSE(trace_function_exports_enabled);
अटल DEFINE_STATIC_KEY_FALSE(trace_event_exports_enabled);
अटल DEFINE_STATIC_KEY_FALSE(trace_marker_exports_enabled);

अटल अंतरभूत व्योम ftrace_exports_enable(काष्ठा trace_export *export)
अणु
	अगर (export->flags & TRACE_EXPORT_FUNCTION)
		अटल_branch_inc(&trace_function_exports_enabled);

	अगर (export->flags & TRACE_EXPORT_EVENT)
		अटल_branch_inc(&trace_event_exports_enabled);

	अगर (export->flags & TRACE_EXPORT_MARKER)
		अटल_branch_inc(&trace_marker_exports_enabled);
पूर्ण

अटल अंतरभूत व्योम ftrace_exports_disable(काष्ठा trace_export *export)
अणु
	अगर (export->flags & TRACE_EXPORT_FUNCTION)
		अटल_branch_dec(&trace_function_exports_enabled);

	अगर (export->flags & TRACE_EXPORT_EVENT)
		अटल_branch_dec(&trace_event_exports_enabled);

	अगर (export->flags & TRACE_EXPORT_MARKER)
		अटल_branch_dec(&trace_marker_exports_enabled);
पूर्ण

अटल व्योम ftrace_exports(काष्ठा ring_buffer_event *event, पूर्णांक flag)
अणु
	काष्ठा trace_export *export;

	preempt_disable_notrace();

	export = rcu_dereference_raw_check(ftrace_exports_list);
	जबतक (export) अणु
		trace_process_export(export, event, flag);
		export = rcu_dereference_raw_check(export->next);
	पूर्ण

	preempt_enable_notrace();
पूर्ण

अटल अंतरभूत व्योम
add_trace_export(काष्ठा trace_export **list, काष्ठा trace_export *export)
अणु
	rcu_assign_poपूर्णांकer(export->next, *list);
	/*
	 * We are entering export पूर्णांकo the list but another
	 * CPU might be walking that list. We need to make sure
	 * the export->next poपूर्णांकer is valid beक्रमe another CPU sees
	 * the export poपूर्णांकer included पूर्णांकo the list.
	 */
	rcu_assign_poपूर्णांकer(*list, export);
पूर्ण

अटल अंतरभूत पूर्णांक
rm_trace_export(काष्ठा trace_export **list, काष्ठा trace_export *export)
अणु
	काष्ठा trace_export **p;

	क्रम (p = list; *p != शून्य; p = &(*p)->next)
		अगर (*p == export)
			अवरोध;

	अगर (*p != export)
		वापस -1;

	rcu_assign_poपूर्णांकer(*p, (*p)->next);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
add_ftrace_export(काष्ठा trace_export **list, काष्ठा trace_export *export)
अणु
	ftrace_exports_enable(export);

	add_trace_export(list, export);
पूर्ण

अटल अंतरभूत पूर्णांक
rm_ftrace_export(काष्ठा trace_export **list, काष्ठा trace_export *export)
अणु
	पूर्णांक ret;

	ret = rm_trace_export(list, export);
	ftrace_exports_disable(export);

	वापस ret;
पूर्ण

पूर्णांक रेजिस्टर_ftrace_export(काष्ठा trace_export *export)
अणु
	अगर (WARN_ON_ONCE(!export->ग_लिखो))
		वापस -1;

	mutex_lock(&ftrace_export_lock);

	add_ftrace_export(&ftrace_exports_list, export);

	mutex_unlock(&ftrace_export_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_ftrace_export);

पूर्णांक unरेजिस्टर_ftrace_export(काष्ठा trace_export *export)
अणु
	पूर्णांक ret;

	mutex_lock(&ftrace_export_lock);

	ret = rm_ftrace_export(&ftrace_exports_list, export);

	mutex_unlock(&ftrace_export_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_ftrace_export);

/* trace_flags holds trace_options शेष values */
#घोषणा TRACE_DEFAULT_FLAGS						\
	(FUNCTION_DEFAULT_FLAGS |					\
	 TRACE_ITER_PRINT_PARENT | TRACE_ITER_PRINTK |			\
	 TRACE_ITER_ANNOTATE | TRACE_ITER_CONTEXT_INFO |		\
	 TRACE_ITER_RECORD_CMD | TRACE_ITER_OVERWRITE |			\
	 TRACE_ITER_IRQ_INFO | TRACE_ITER_MARKERS |			\
	 TRACE_ITER_HASH_PTR)

/* trace_options that are only supported by global_trace */
#घोषणा TOP_LEVEL_TRACE_FLAGS (TRACE_ITER_PRINTK |			\
	       TRACE_ITER_PRINTK_MSGONLY | TRACE_ITER_RECORD_CMD)

/* trace_flags that are शेष zero क्रम instances */
#घोषणा ZEROED_TRACE_FLAGS \
	(TRACE_ITER_EVENT_FORK | TRACE_ITER_FUNC_FORK)

/*
 * The global_trace is the descriptor that holds the top-level tracing
 * buffers क्रम the live tracing.
 */
अटल काष्ठा trace_array global_trace = अणु
	.trace_flags = TRACE_DEFAULT_FLAGS,
पूर्ण;

LIST_HEAD(ftrace_trace_arrays);

पूर्णांक trace_array_get(काष्ठा trace_array *this_tr)
अणु
	काष्ठा trace_array *tr;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&trace_types_lock);
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (tr == this_tr) अणु
			tr->ref++;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण

अटल व्योम __trace_array_put(काष्ठा trace_array *this_tr)
अणु
	WARN_ON(!this_tr->ref);
	this_tr->ref--;
पूर्ण

/**
 * trace_array_put - Decrement the reference counter क्रम this trace array.
 * @this_tr : poपूर्णांकer to the trace array
 *
 * NOTE: Use this when we no दीर्घer need the trace array वापसed by
 * trace_array_get_by_name(). This ensures the trace array can be later
 * destroyed.
 *
 */
व्योम trace_array_put(काष्ठा trace_array *this_tr)
अणु
	अगर (!this_tr)
		वापस;

	mutex_lock(&trace_types_lock);
	__trace_array_put(this_tr);
	mutex_unlock(&trace_types_lock);
पूर्ण
EXPORT_SYMBOL_GPL(trace_array_put);

पूर्णांक tracing_check_खोलो_get_tr(काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	अगर (tracing_disabled)
		वापस -ENODEV;

	अगर (tr && trace_array_get(tr) < 0)
		वापस -ENODEV;

	वापस 0;
पूर्ण

पूर्णांक call_filter_check_discard(काष्ठा trace_event_call *call, व्योम *rec,
			      काष्ठा trace_buffer *buffer,
			      काष्ठा ring_buffer_event *event)
अणु
	अगर (unlikely(call->flags & TRACE_EVENT_FL_FILTERED) &&
	    !filter_match_preds(call->filter, rec)) अणु
		__trace_event_discard_commit(buffer, event);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम trace_मुक्त_pid_list(काष्ठा trace_pid_list *pid_list)
अणु
	vमुक्त(pid_list->pids);
	kमुक्त(pid_list);
पूर्ण

/**
 * trace_find_filtered_pid - check अगर a pid exists in a filtered_pid list
 * @filtered_pids: The list of pids to check
 * @search_pid: The PID to find in @filtered_pids
 *
 * Returns true अगर @search_pid is found in @filtered_pids, and false otherwise.
 */
bool
trace_find_filtered_pid(काष्ठा trace_pid_list *filtered_pids, pid_t search_pid)
अणु
	/*
	 * If pid_max changed after filtered_pids was created, we
	 * by शेष ignore all pids greater than the previous pid_max.
	 */
	अगर (search_pid >= filtered_pids->pid_max)
		वापस false;

	वापस test_bit(search_pid, filtered_pids->pids);
पूर्ण

/**
 * trace_ignore_this_task - should a task be ignored क्रम tracing
 * @filtered_pids: The list of pids to check
 * @filtered_no_pids: The list of pids not to be traced
 * @task: The task that should be ignored अगर not filtered
 *
 * Checks अगर @task should be traced or not from @filtered_pids.
 * Returns true अगर @task should *NOT* be traced.
 * Returns false अगर @task should be traced.
 */
bool
trace_ignore_this_task(काष्ठा trace_pid_list *filtered_pids,
		       काष्ठा trace_pid_list *filtered_no_pids,
		       काष्ठा task_काष्ठा *task)
अणु
	/*
	 * If filtered_no_pids is not empty, and the task's pid is listed
	 * in filtered_no_pids, then वापस true.
	 * Otherwise, अगर filtered_pids is empty, that means we can
	 * trace all tasks. If it has content, then only trace pids
	 * within filtered_pids.
	 */

	वापस (filtered_pids &&
		!trace_find_filtered_pid(filtered_pids, task->pid)) ||
		(filtered_no_pids &&
		 trace_find_filtered_pid(filtered_no_pids, task->pid));
पूर्ण

/**
 * trace_filter_add_हटाओ_task - Add or हटाओ a task from a pid_list
 * @pid_list: The list to modअगरy
 * @self: The current task क्रम विभाजन or शून्य क्रम निकास
 * @task: The task to add or हटाओ
 *
 * If adding a task, अगर @self is defined, the task is only added अगर @self
 * is also included in @pid_list. This happens on विभाजन and tasks should
 * only be added when the parent is listed. If @self is शून्य, then the
 * @task pid will be हटाओd from the list, which would happen on निकास
 * of a task.
 */
व्योम trace_filter_add_हटाओ_task(काष्ठा trace_pid_list *pid_list,
				  काष्ठा task_काष्ठा *self,
				  काष्ठा task_काष्ठा *task)
अणु
	अगर (!pid_list)
		वापस;

	/* For विभाजनs, we only add अगर the विभाजनing task is listed */
	अगर (self) अणु
		अगर (!trace_find_filtered_pid(pid_list, self->pid))
			वापस;
	पूर्ण

	/* Sorry, but we करोn't support pid_max changing after setting */
	अगर (task->pid >= pid_list->pid_max)
		वापस;

	/* "self" is set क्रम विभाजनs, and शून्य क्रम निकासs */
	अगर (self)
		set_bit(task->pid, pid_list->pids);
	अन्यथा
		clear_bit(task->pid, pid_list->pids);
पूर्ण

/**
 * trace_pid_next - Used क्रम seq_file to get to the next pid of a pid_list
 * @pid_list: The pid list to show
 * @v: The last pid that was shown (+1 the actual pid to let zero be displayed)
 * @pos: The position of the file
 *
 * This is used by the seq_file "next" operation to iterate the pids
 * listed in a trace_pid_list काष्ठाure.
 *
 * Returns the pid+1 as we want to display pid of zero, but शून्य would
 * stop the iteration.
 */
व्योम *trace_pid_next(काष्ठा trace_pid_list *pid_list, व्योम *v, loff_t *pos)
अणु
	अचिन्हित दीर्घ pid = (अचिन्हित दीर्घ)v;

	(*pos)++;

	/* pid alपढ़ोy is +1 of the actual previous bit */
	pid = find_next_bit(pid_list->pids, pid_list->pid_max, pid);

	/* Return pid + 1 to allow zero to be represented */
	अगर (pid < pid_list->pid_max)
		वापस (व्योम *)(pid + 1);

	वापस शून्य;
पूर्ण

/**
 * trace_pid_start - Used क्रम seq_file to start पढ़ोing pid lists
 * @pid_list: The pid list to show
 * @pos: The position of the file
 *
 * This is used by seq_file "start" operation to start the iteration
 * of listing pids.
 *
 * Returns the pid+1 as we want to display pid of zero, but शून्य would
 * stop the iteration.
 */
व्योम *trace_pid_start(काष्ठा trace_pid_list *pid_list, loff_t *pos)
अणु
	अचिन्हित दीर्घ pid;
	loff_t l = 0;

	pid = find_first_bit(pid_list->pids, pid_list->pid_max);
	अगर (pid >= pid_list->pid_max)
		वापस शून्य;

	/* Return pid + 1 so that zero can be the निकास value */
	क्रम (pid++; pid && l < *pos;
	     pid = (अचिन्हित दीर्घ)trace_pid_next(pid_list, (व्योम *)pid, &l))
		;
	वापस (व्योम *)pid;
पूर्ण

/**
 * trace_pid_show - show the current pid in seq_file processing
 * @m: The seq_file काष्ठाure to ग_लिखो पूर्णांकo
 * @v: A व्योम poपूर्णांकer of the pid (+1) value to display
 *
 * Can be directly used by seq_file operations to display the current
 * pid value.
 */
पूर्णांक trace_pid_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ pid = (अचिन्हित दीर्घ)v - 1;

	seq_म_लिखो(m, "%lu\n", pid);
	वापस 0;
पूर्ण

/* 128 should be much more than enough */
#घोषणा PID_BUF_SIZE		127

पूर्णांक trace_pid_ग_लिखो(काष्ठा trace_pid_list *filtered_pids,
		    काष्ठा trace_pid_list **new_pid_list,
		    स्थिर अक्षर __user *ubuf, माप_प्रकार cnt)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_parser parser;
	अचिन्हित दीर्घ val;
	पूर्णांक nr_pids = 0;
	sमाप_प्रकार पढ़ो = 0;
	sमाप_प्रकार ret = 0;
	loff_t pos;
	pid_t pid;

	अगर (trace_parser_get_init(&parser, PID_BUF_SIZE + 1))
		वापस -ENOMEM;

	/*
	 * Always recreate a new array. The ग_लिखो is an all or nothing
	 * operation. Always create a new array when adding new pids by
	 * the user. If the operation fails, then the current list is
	 * not modअगरied.
	 */
	pid_list = kदो_स्मृति(माप(*pid_list), GFP_KERNEL);
	अगर (!pid_list) अणु
		trace_parser_put(&parser);
		वापस -ENOMEM;
	पूर्ण

	pid_list->pid_max = READ_ONCE(pid_max);

	/* Only truncating will shrink pid_max */
	अगर (filtered_pids && filtered_pids->pid_max > pid_list->pid_max)
		pid_list->pid_max = filtered_pids->pid_max;

	pid_list->pids = vzalloc((pid_list->pid_max + 7) >> 3);
	अगर (!pid_list->pids) अणु
		trace_parser_put(&parser);
		kमुक्त(pid_list);
		वापस -ENOMEM;
	पूर्ण

	अगर (filtered_pids) अणु
		/* copy the current bits to the new max */
		क्रम_each_set_bit(pid, filtered_pids->pids,
				 filtered_pids->pid_max) अणु
			set_bit(pid, pid_list->pids);
			nr_pids++;
		पूर्ण
	पूर्ण

	जबतक (cnt > 0) अणु

		pos = 0;

		ret = trace_get_user(&parser, ubuf, cnt, &pos);
		अगर (ret < 0 || !trace_parser_loaded(&parser))
			अवरोध;

		पढ़ो += ret;
		ubuf += ret;
		cnt -= ret;

		ret = -EINVAL;
		अगर (kम_से_अदीर्घ(parser.buffer, 0, &val))
			अवरोध;
		अगर (val >= pid_list->pid_max)
			अवरोध;

		pid = (pid_t)val;

		set_bit(pid, pid_list->pids);
		nr_pids++;

		trace_parser_clear(&parser);
		ret = 0;
	पूर्ण
	trace_parser_put(&parser);

	अगर (ret < 0) अणु
		trace_मुक्त_pid_list(pid_list);
		वापस ret;
	पूर्ण

	अगर (!nr_pids) अणु
		/* Cleared the list of pids */
		trace_मुक्त_pid_list(pid_list);
		पढ़ो = ret;
		pid_list = शून्य;
	पूर्ण

	*new_pid_list = pid_list;

	वापस पढ़ो;
पूर्ण

अटल u64 buffer_ftrace_now(काष्ठा array_buffer *buf, पूर्णांक cpu)
अणु
	u64 ts;

	/* Early boot up करोes not have a buffer yet */
	अगर (!buf->buffer)
		वापस trace_घड़ी_local();

	ts = ring_buffer_समय_stamp(buf->buffer);
	ring_buffer_normalize_समय_stamp(buf->buffer, cpu, &ts);

	वापस ts;
पूर्ण

u64 ftrace_now(पूर्णांक cpu)
अणु
	वापस buffer_ftrace_now(&global_trace.array_buffer, cpu);
पूर्ण

/**
 * tracing_is_enabled - Show अगर global_trace has been enabled
 *
 * Shows अगर the global trace has been enabled or not. It uses the
 * mirror flag "buffer_disabled" to be used in fast paths such as क्रम
 * the irqsoff tracer. But it may be inaccurate due to races. If you
 * need to know the accurate state, use tracing_is_on() which is a little
 * slower, but accurate.
 */
पूर्णांक tracing_is_enabled(व्योम)
अणु
	/*
	 * For quick access (irqsoff uses this in fast path), just
	 * वापस the mirror variable of the state of the ring buffer.
	 * It's a little racy, but we don't really care.
	 */
	smp_rmb();
	वापस !global_trace.buffer_disabled;
पूर्ण

/*
 * trace_buf_size is the size in bytes that is allocated
 * क्रम a buffer. Note, the number of bytes is always rounded
 * to page size.
 *
 * This number is purposely set to a low number of 16384.
 * If the dump on oops happens, it will be much appreciated
 * to not have to रुको क्रम all that output. Anyway this can be
 * boot समय and run समय configurable.
 */
#घोषणा TRACE_BUF_SIZE_DEFAULT	1441792UL /* 16384 * 88 (माप(entry)) */

अटल अचिन्हित दीर्घ		trace_buf_size = TRACE_BUF_SIZE_DEFAULT;

/* trace_types holds a link list of available tracers. */
अटल काष्ठा tracer		*trace_types __पढ़ो_mostly;

/*
 * trace_types_lock is used to protect the trace_types list.
 */
DEFINE_MUTEX(trace_types_lock);

/*
 * serialize the access of the ring buffer
 *
 * ring buffer serializes पढ़ोers, but it is low level protection.
 * The validity of the events (which वापसs by ring_buffer_peek() ..etc)
 * are not रक्षित by ring buffer.
 *
 * The content of events may become garbage अगर we allow other process consumes
 * these events concurrently:
 *   A) the page of the consumed events may become a normal page
 *      (not पढ़ोer page) in ring buffer, and this page will be rewritten
 *      by events producer.
 *   B) The page of the consumed events may become a page क्रम splice_पढ़ो,
 *      and this page will be वापसed to प्रणाली.
 *
 * These primitives allow multi process access to dअगरferent cpu ring buffer
 * concurrently.
 *
 * These primitives करोn't distinguish पढ़ो-only and पढ़ो-consume access.
 * Multi पढ़ो-only access are also serialized.
 */

#अगर_घोषित CONFIG_SMP
अटल DECLARE_RWSEM(all_cpu_access_lock);
अटल DEFINE_PER_CPU(काष्ठा mutex, cpu_access_lock);

अटल अंतरभूत व्योम trace_access_lock(पूर्णांक cpu)
अणु
	अगर (cpu == RING_BUFFER_ALL_CPUS) अणु
		/* gain it क्रम accessing the whole ring buffer. */
		करोwn_ग_लिखो(&all_cpu_access_lock);
	पूर्ण अन्यथा अणु
		/* gain it क्रम accessing a cpu ring buffer. */

		/* Firstly block other trace_access_lock(RING_BUFFER_ALL_CPUS). */
		करोwn_पढ़ो(&all_cpu_access_lock);

		/* Secondly block other access to this @cpu ring buffer. */
		mutex_lock(&per_cpu(cpu_access_lock, cpu));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम trace_access_unlock(पूर्णांक cpu)
अणु
	अगर (cpu == RING_BUFFER_ALL_CPUS) अणु
		up_ग_लिखो(&all_cpu_access_lock);
	पूर्ण अन्यथा अणु
		mutex_unlock(&per_cpu(cpu_access_lock, cpu));
		up_पढ़ो(&all_cpu_access_lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम trace_access_lock_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		mutex_init(&per_cpu(cpu_access_lock, cpu));
पूर्ण

#अन्यथा

अटल DEFINE_MUTEX(access_lock);

अटल अंतरभूत व्योम trace_access_lock(पूर्णांक cpu)
अणु
	(व्योम)cpu;
	mutex_lock(&access_lock);
पूर्ण

अटल अंतरभूत व्योम trace_access_unlock(पूर्णांक cpu)
अणु
	(व्योम)cpu;
	mutex_unlock(&access_lock);
पूर्ण

अटल अंतरभूत व्योम trace_access_lock_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_STACKTRACE
अटल व्योम __ftrace_trace_stack(काष्ठा trace_buffer *buffer,
				 अचिन्हित पूर्णांक trace_ctx,
				 पूर्णांक skip, काष्ठा pt_regs *regs);
अटल अंतरभूत व्योम ftrace_trace_stack(काष्ठा trace_array *tr,
				      काष्ठा trace_buffer *buffer,
				      अचिन्हित पूर्णांक trace_ctx,
				      पूर्णांक skip, काष्ठा pt_regs *regs);

#अन्यथा
अटल अंतरभूत व्योम __ftrace_trace_stack(काष्ठा trace_buffer *buffer,
					अचिन्हित पूर्णांक trace_ctx,
					पूर्णांक skip, काष्ठा pt_regs *regs)
अणु
पूर्ण
अटल अंतरभूत व्योम ftrace_trace_stack(काष्ठा trace_array *tr,
				      काष्ठा trace_buffer *buffer,
				      अचिन्हित दीर्घ trace_ctx,
				      पूर्णांक skip, काष्ठा pt_regs *regs)
अणु
पूर्ण

#पूर्ण_अगर

अटल __always_अंतरभूत व्योम
trace_event_setup(काष्ठा ring_buffer_event *event,
		  पूर्णांक type, अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_entry *ent = ring_buffer_event_data(event);

	tracing_generic_entry_update(ent, type, trace_ctx);
पूर्ण

अटल __always_अंतरभूत काष्ठा ring_buffer_event *
__trace_buffer_lock_reserve(काष्ठा trace_buffer *buffer,
			  पूर्णांक type,
			  अचिन्हित दीर्घ len,
			  अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा ring_buffer_event *event;

	event = ring_buffer_lock_reserve(buffer, len);
	अगर (event != शून्य)
		trace_event_setup(event, type, trace_ctx);

	वापस event;
पूर्ण

व्योम tracer_tracing_on(काष्ठा trace_array *tr)
अणु
	अगर (tr->array_buffer.buffer)
		ring_buffer_record_on(tr->array_buffer.buffer);
	/*
	 * This flag is looked at when buffers haven't been allocated
	 * yet, or by some tracers (like irqsoff), that just want to
	 * know अगर the ring buffer has been disabled, but it can handle
	 * races of where it माला_लो disabled but we still करो a record.
	 * As the check is in the fast path of the tracers, it is more
	 * important to be fast than accurate.
	 */
	tr->buffer_disabled = 0;
	/* Make the flag seen by पढ़ोers */
	smp_wmb();
पूर्ण

/**
 * tracing_on - enable tracing buffers
 *
 * This function enables tracing buffers that may have been
 * disabled with tracing_off.
 */
व्योम tracing_on(व्योम)
अणु
	tracer_tracing_on(&global_trace);
पूर्ण
EXPORT_SYMBOL_GPL(tracing_on);


अटल __always_अंतरभूत व्योम
__buffer_unlock_commit(काष्ठा trace_buffer *buffer, काष्ठा ring_buffer_event *event)
अणु
	__this_cpu_ग_लिखो(trace_taskinfo_save, true);

	/* If this is the temp buffer, we need to commit fully */
	अगर (this_cpu_पढ़ो(trace_buffered_event) == event) अणु
		/* Length is in event->array[0] */
		ring_buffer_ग_लिखो(buffer, event->array[0], &event->array[1]);
		/* Release the temp buffer */
		this_cpu_dec(trace_buffered_event_cnt);
	पूर्ण अन्यथा
		ring_buffer_unlock_commit(buffer, event);
पूर्ण

/**
 * __trace_माला_दो - ग_लिखो a स्थिरant string पूर्णांकo the trace buffer.
 * @ip:	   The address of the caller
 * @str:   The स्थिरant string to ग_लिखो
 * @size:  The size of the string.
 */
पूर्णांक __trace_माला_दो(अचिन्हित दीर्घ ip, स्थिर अक्षर *str, पूर्णांक size)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer;
	काष्ठा prपूर्णांक_entry *entry;
	अचिन्हित पूर्णांक trace_ctx;
	पूर्णांक alloc;

	अगर (!(global_trace.trace_flags & TRACE_ITER_PRINTK))
		वापस 0;

	अगर (unlikely(tracing_selftest_running || tracing_disabled))
		वापस 0;

	alloc = माप(*entry) + size + 2; /* possible \न added */

	trace_ctx = tracing_gen_ctx();
	buffer = global_trace.array_buffer.buffer;
	ring_buffer_nest_start(buffer);
	event = __trace_buffer_lock_reserve(buffer, TRACE_PRINT, alloc,
					    trace_ctx);
	अगर (!event) अणु
		size = 0;
		जाओ out;
	पूर्ण

	entry = ring_buffer_event_data(event);
	entry->ip = ip;

	स_नकल(&entry->buf, str, size);

	/* Add a newline अगर necessary */
	अगर (entry->buf[size - 1] != '\n') अणु
		entry->buf[size] = '\n';
		entry->buf[size + 1] = '\0';
	पूर्ण अन्यथा
		entry->buf[size] = '\0';

	__buffer_unlock_commit(buffer, event);
	ftrace_trace_stack(&global_trace, buffer, trace_ctx, 4, शून्य);
 out:
	ring_buffer_nest_end(buffer);
	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(__trace_माला_दो);

/**
 * __trace_bमाला_दो - ग_लिखो the poपूर्णांकer to a स्थिरant string पूर्णांकo trace buffer
 * @ip:	   The address of the caller
 * @str:   The स्थिरant string to ग_लिखो to the buffer to
 */
पूर्णांक __trace_bमाला_दो(अचिन्हित दीर्घ ip, स्थिर अक्षर *str)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer;
	काष्ठा bमाला_दो_entry *entry;
	अचिन्हित पूर्णांक trace_ctx;
	पूर्णांक size = माप(काष्ठा bमाला_दो_entry);
	पूर्णांक ret = 0;

	अगर (!(global_trace.trace_flags & TRACE_ITER_PRINTK))
		वापस 0;

	अगर (unlikely(tracing_selftest_running || tracing_disabled))
		वापस 0;

	trace_ctx = tracing_gen_ctx();
	buffer = global_trace.array_buffer.buffer;

	ring_buffer_nest_start(buffer);
	event = __trace_buffer_lock_reserve(buffer, TRACE_BPUTS, size,
					    trace_ctx);
	अगर (!event)
		जाओ out;

	entry = ring_buffer_event_data(event);
	entry->ip			= ip;
	entry->str			= str;

	__buffer_unlock_commit(buffer, event);
	ftrace_trace_stack(&global_trace, buffer, trace_ctx, 4, शून्य);

	ret = 1;
 out:
	ring_buffer_nest_end(buffer);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__trace_bमाला_दो);

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
अटल व्योम tracing_snapshot_instance_cond(काष्ठा trace_array *tr,
					   व्योम *cond_data)
अणु
	काष्ठा tracer *tracer = tr->current_trace;
	अचिन्हित दीर्घ flags;

	अगर (in_nmi()) अणु
		पूर्णांकernal_trace_माला_दो("*** SNAPSHOT CALLED FROM NMI CONTEXT ***\n");
		पूर्णांकernal_trace_माला_दो("*** snapshot is being ignored        ***\n");
		वापस;
	पूर्ण

	अगर (!tr->allocated_snapshot) अणु
		पूर्णांकernal_trace_माला_दो("*** SNAPSHOT NOT ALLOCATED ***\n");
		पूर्णांकernal_trace_माला_दो("*** stopping trace here!   ***\n");
		tracing_off();
		वापस;
	पूर्ण

	/* Note, snapshot can not be used when the tracer uses it */
	अगर (tracer->use_max_tr) अणु
		पूर्णांकernal_trace_माला_दो("*** LATENCY TRACER ACTIVE ***\n");
		पूर्णांकernal_trace_माला_दो("*** Can not use snapshot (sorry) ***\n");
		वापस;
	पूर्ण

	local_irq_save(flags);
	update_max_tr(tr, current, smp_processor_id(), cond_data);
	local_irq_restore(flags);
पूर्ण

व्योम tracing_snapshot_instance(काष्ठा trace_array *tr)
अणु
	tracing_snapshot_instance_cond(tr, शून्य);
पूर्ण

/**
 * tracing_snapshot - take a snapshot of the current buffer.
 *
 * This causes a swap between the snapshot buffer and the current live
 * tracing buffer. You can use this to take snapshots of the live
 * trace when some condition is triggered, but जारी to trace.
 *
 * Note, make sure to allocate the snapshot with either
 * a tracing_snapshot_alloc(), or by करोing it manually
 * with: echo 1 > /sys/kernel/debug/tracing/snapshot
 *
 * If the snapshot buffer is not allocated, it will stop tracing.
 * Basically making a permanent snapshot.
 */
व्योम tracing_snapshot(व्योम)
अणु
	काष्ठा trace_array *tr = &global_trace;

	tracing_snapshot_instance(tr);
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot);

/**
 * tracing_snapshot_cond - conditionally take a snapshot of the current buffer.
 * @tr:		The tracing instance to snapshot
 * @cond_data:	The data to be tested conditionally, and possibly saved
 *
 * This is the same as tracing_snapshot() except that the snapshot is
 * conditional - the snapshot will only happen अगर the
 * cond_snapshot.update() implementation receiving the cond_data
 * वापसs true, which means that the trace array's cond_snapshot
 * update() operation used the cond_data to determine whether the
 * snapshot should be taken, and अगर it was, presumably saved it aदीर्घ
 * with the snapshot.
 */
व्योम tracing_snapshot_cond(काष्ठा trace_array *tr, व्योम *cond_data)
अणु
	tracing_snapshot_instance_cond(tr, cond_data);
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_cond);

/**
 * tracing_snapshot_cond_data - get the user data associated with a snapshot
 * @tr:		The tracing instance
 *
 * When the user enables a conditional snapshot using
 * tracing_snapshot_cond_enable(), the user-defined cond_data is saved
 * with the snapshot.  This accessor is used to retrieve it.
 *
 * Should not be called from cond_snapshot.update(), since it takes
 * the tr->max_lock lock, which the code calling
 * cond_snapshot.update() has alपढ़ोy करोne.
 *
 * Returns the cond_data associated with the trace array's snapshot.
 */
व्योम *tracing_cond_snapshot_data(काष्ठा trace_array *tr)
अणु
	व्योम *cond_data = शून्य;

	arch_spin_lock(&tr->max_lock);

	अगर (tr->cond_snapshot)
		cond_data = tr->cond_snapshot->cond_data;

	arch_spin_unlock(&tr->max_lock);

	वापस cond_data;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_cond_snapshot_data);

अटल पूर्णांक resize_buffer_duplicate_size(काष्ठा array_buffer *trace_buf,
					काष्ठा array_buffer *size_buf, पूर्णांक cpu_id);
अटल व्योम set_buffer_entries(काष्ठा array_buffer *buf, अचिन्हित दीर्घ val);

पूर्णांक tracing_alloc_snapshot_instance(काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	अगर (!tr->allocated_snapshot) अणु

		/* allocate spare buffer */
		ret = resize_buffer_duplicate_size(&tr->max_buffer,
				   &tr->array_buffer, RING_BUFFER_ALL_CPUS);
		अगर (ret < 0)
			वापस ret;

		tr->allocated_snapshot = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_snapshot(काष्ठा trace_array *tr)
अणु
	/*
	 * We करोn't मुक्त the ring buffer. instead, resize it because
	 * The max_tr ring buffer has some state (e.g. ring->घड़ी) and
	 * we want preserve it.
	 */
	ring_buffer_resize(tr->max_buffer.buffer, 1, RING_BUFFER_ALL_CPUS);
	set_buffer_entries(&tr->max_buffer, 1);
	tracing_reset_online_cpus(&tr->max_buffer);
	tr->allocated_snapshot = false;
पूर्ण

/**
 * tracing_alloc_snapshot - allocate snapshot buffer.
 *
 * This only allocates the snapshot buffer अगर it isn't alपढ़ोy
 * allocated - it करोesn't also take a snapshot.
 *
 * This is meant to be used in हालs where the snapshot buffer needs
 * to be set up क्रम events that can't sleep but need to be able to
 * trigger a snapshot.
 */
पूर्णांक tracing_alloc_snapshot(व्योम)
अणु
	काष्ठा trace_array *tr = &global_trace;
	पूर्णांक ret;

	ret = tracing_alloc_snapshot_instance(tr);
	WARN_ON(ret < 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_alloc_snapshot);

/**
 * tracing_snapshot_alloc - allocate and take a snapshot of the current buffer.
 *
 * This is similar to tracing_snapshot(), but it will allocate the
 * snapshot buffer अगर it isn't alपढ़ोy allocated. Use this only
 * where it is safe to sleep, as the allocation may sleep.
 *
 * This causes a swap between the snapshot buffer and the current live
 * tracing buffer. You can use this to take snapshots of the live
 * trace when some condition is triggered, but जारी to trace.
 */
व्योम tracing_snapshot_alloc(व्योम)
अणु
	पूर्णांक ret;

	ret = tracing_alloc_snapshot();
	अगर (ret < 0)
		वापस;

	tracing_snapshot();
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_alloc);

/**
 * tracing_snapshot_cond_enable - enable conditional snapshot क्रम an instance
 * @tr:		The tracing instance
 * @cond_data:	User data to associate with the snapshot
 * @update:	Implementation of the cond_snapshot update function
 *
 * Check whether the conditional snapshot क्रम the given instance has
 * alपढ़ोy been enabled, or अगर the current tracer is alपढ़ोy using a
 * snapshot; अगर so, वापस -EBUSY, अन्यथा create a cond_snapshot and
 * save the cond_data and update function inside.
 *
 * Returns 0 अगर successful, error otherwise.
 */
पूर्णांक tracing_snapshot_cond_enable(काष्ठा trace_array *tr, व्योम *cond_data,
				 cond_update_fn_t update)
अणु
	काष्ठा cond_snapshot *cond_snapshot;
	पूर्णांक ret = 0;

	cond_snapshot = kzalloc(माप(*cond_snapshot), GFP_KERNEL);
	अगर (!cond_snapshot)
		वापस -ENOMEM;

	cond_snapshot->cond_data = cond_data;
	cond_snapshot->update = update;

	mutex_lock(&trace_types_lock);

	ret = tracing_alloc_snapshot_instance(tr);
	अगर (ret)
		जाओ fail_unlock;

	अगर (tr->current_trace->use_max_tr) अणु
		ret = -EBUSY;
		जाओ fail_unlock;
	पूर्ण

	/*
	 * The cond_snapshot can only change to शून्य without the
	 * trace_types_lock. We करोn't care अगर we race with it going
	 * to शून्य, but we want to make sure that it's not set to
	 * something other than शून्य when we get here, which we can
	 * करो safely with only holding the trace_types_lock and not
	 * having to take the max_lock.
	 */
	अगर (tr->cond_snapshot) अणु
		ret = -EBUSY;
		जाओ fail_unlock;
	पूर्ण

	arch_spin_lock(&tr->max_lock);
	tr->cond_snapshot = cond_snapshot;
	arch_spin_unlock(&tr->max_lock);

	mutex_unlock(&trace_types_lock);

	वापस ret;

 fail_unlock:
	mutex_unlock(&trace_types_lock);
	kमुक्त(cond_snapshot);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_cond_enable);

/**
 * tracing_snapshot_cond_disable - disable conditional snapshot क्रम an instance
 * @tr:		The tracing instance
 *
 * Check whether the conditional snapshot क्रम the given instance is
 * enabled; अगर so, मुक्त the cond_snapshot associated with it,
 * otherwise वापस -EINVAL.
 *
 * Returns 0 अगर successful, error otherwise.
 */
पूर्णांक tracing_snapshot_cond_disable(काष्ठा trace_array *tr)
अणु
	पूर्णांक ret = 0;

	arch_spin_lock(&tr->max_lock);

	अगर (!tr->cond_snapshot)
		ret = -EINVAL;
	अन्यथा अणु
		kमुक्त(tr->cond_snapshot);
		tr->cond_snapshot = शून्य;
	पूर्ण

	arch_spin_unlock(&tr->max_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_cond_disable);
#अन्यथा
व्योम tracing_snapshot(व्योम)
अणु
	WARN_ONCE(1, "Snapshot feature not enabled, but internal snapshot used");
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot);
व्योम tracing_snapshot_cond(काष्ठा trace_array *tr, व्योम *cond_data)
अणु
	WARN_ONCE(1, "Snapshot feature not enabled, but internal conditional snapshot used");
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_cond);
पूर्णांक tracing_alloc_snapshot(व्योम)
अणु
	WARN_ONCE(1, "Snapshot feature not enabled, but snapshot allocation used");
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_alloc_snapshot);
व्योम tracing_snapshot_alloc(व्योम)
अणु
	/* Give warning */
	tracing_snapshot();
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_alloc);
व्योम *tracing_cond_snapshot_data(काष्ठा trace_array *tr)
अणु
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_cond_snapshot_data);
पूर्णांक tracing_snapshot_cond_enable(काष्ठा trace_array *tr, व्योम *cond_data, cond_update_fn_t update)
अणु
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_cond_enable);
पूर्णांक tracing_snapshot_cond_disable(काष्ठा trace_array *tr)
अणु
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(tracing_snapshot_cond_disable);
#पूर्ण_अगर /* CONFIG_TRACER_SNAPSHOT */

व्योम tracer_tracing_off(काष्ठा trace_array *tr)
अणु
	अगर (tr->array_buffer.buffer)
		ring_buffer_record_off(tr->array_buffer.buffer);
	/*
	 * This flag is looked at when buffers haven't been allocated
	 * yet, or by some tracers (like irqsoff), that just want to
	 * know अगर the ring buffer has been disabled, but it can handle
	 * races of where it माला_लो disabled but we still करो a record.
	 * As the check is in the fast path of the tracers, it is more
	 * important to be fast than accurate.
	 */
	tr->buffer_disabled = 1;
	/* Make the flag seen by पढ़ोers */
	smp_wmb();
पूर्ण

/**
 * tracing_off - turn off tracing buffers
 *
 * This function stops the tracing buffers from recording data.
 * It करोes not disable any overhead the tracers themselves may
 * be causing. This function simply causes all recording to
 * the ring buffers to fail.
 */
व्योम tracing_off(व्योम)
अणु
	tracer_tracing_off(&global_trace);
पूर्ण
EXPORT_SYMBOL_GPL(tracing_off);

व्योम disable_trace_on_warning(व्योम)
अणु
	अगर (__disable_trace_on_warning) अणु
		trace_array_prपूर्णांकk_buf(global_trace.array_buffer.buffer, _THIS_IP_,
			"Disabling tracing due to warning\n");
		tracing_off();
	पूर्ण
पूर्ण

/**
 * tracer_tracing_is_on - show real state of ring buffer enabled
 * @tr : the trace array to know अगर ring buffer is enabled
 *
 * Shows real state of the ring buffer अगर it is enabled or not.
 */
bool tracer_tracing_is_on(काष्ठा trace_array *tr)
अणु
	अगर (tr->array_buffer.buffer)
		वापस ring_buffer_record_is_on(tr->array_buffer.buffer);
	वापस !tr->buffer_disabled;
पूर्ण

/**
 * tracing_is_on - show state of ring buffers enabled
 */
पूर्णांक tracing_is_on(व्योम)
अणु
	वापस tracer_tracing_is_on(&global_trace);
पूर्ण
EXPORT_SYMBOL_GPL(tracing_is_on);

अटल पूर्णांक __init set_buf_size(अक्षर *str)
अणु
	अचिन्हित दीर्घ buf_size;

	अगर (!str)
		वापस 0;
	buf_size = memparse(str, &str);
	/* nr_entries can not be zero */
	अगर (buf_size == 0)
		वापस 0;
	trace_buf_size = buf_size;
	वापस 1;
पूर्ण
__setup("trace_buf_size=", set_buf_size);

अटल पूर्णांक __init set_tracing_thresh(अक्षर *str)
अणु
	अचिन्हित दीर्घ threshold;
	पूर्णांक ret;

	अगर (!str)
		वापस 0;
	ret = kम_से_अदीर्घ(str, 0, &threshold);
	अगर (ret < 0)
		वापस 0;
	tracing_thresh = threshold * 1000;
	वापस 1;
पूर्ण
__setup("tracing_thresh=", set_tracing_thresh);

अचिन्हित दीर्घ nsecs_to_usecs(अचिन्हित दीर्घ nsecs)
अणु
	वापस nsecs / 1000;
पूर्ण

/*
 * TRACE_FLAGS is defined as a tuple matching bit masks with strings.
 * It uses C(a, b) where 'a' is the eval (enum) name and 'b' is the string that
 * matches it. By defining "C(a, b) b", TRACE_FLAGS becomes a list
 * of strings in the order that the evals (क्रमागत) were defined.
 */
#अघोषित C
#घोषणा C(a, b) b

/* These must match the bit positions in trace_iterator_flags */
अटल स्थिर अक्षर *trace_options[] = अणु
	TRACE_FLAGS
	शून्य
पूर्ण;

अटल काष्ठा अणु
	u64 (*func)(व्योम);
	स्थिर अक्षर *name;
	पूर्णांक in_ns;		/* is this घड़ी in nanoseconds? */
पूर्ण trace_घड़ीs[] = अणु
	अणु trace_घड़ी_local,		"local",	1 पूर्ण,
	अणु trace_घड़ी_global,		"global",	1 पूर्ण,
	अणु trace_घड़ी_counter,		"counter",	0 पूर्ण,
	अणु trace_घड़ी_jअगरfies,		"uptime",	0 पूर्ण,
	अणु trace_घड़ी,			"perf",		1 पूर्ण,
	अणु kसमय_get_mono_fast_ns,	"mono",		1 पूर्ण,
	अणु kसमय_get_raw_fast_ns,	"mono_raw",	1 पूर्ण,
	अणु kसमय_get_boot_fast_ns,	"boot",		1 पूर्ण,
	ARCH_TRACE_CLOCKS
पूर्ण;

bool trace_घड़ी_in_ns(काष्ठा trace_array *tr)
अणु
	अगर (trace_घड़ीs[tr->घड़ी_id].in_ns)
		वापस true;

	वापस false;
पूर्ण

/*
 * trace_parser_get_init - माला_लो the buffer क्रम trace parser
 */
पूर्णांक trace_parser_get_init(काष्ठा trace_parser *parser, पूर्णांक size)
अणु
	स_रखो(parser, 0, माप(*parser));

	parser->buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!parser->buffer)
		वापस 1;

	parser->size = size;
	वापस 0;
पूर्ण

/*
 * trace_parser_put - मुक्तs the buffer क्रम trace parser
 */
व्योम trace_parser_put(काष्ठा trace_parser *parser)
अणु
	kमुक्त(parser->buffer);
	parser->buffer = शून्य;
पूर्ण

/*
 * trace_get_user - पढ़ोs the user input string separated by  space
 * (matched by है_खाली(ch))
 *
 * For each string found the 'struct trace_parser' is updated,
 * and the function वापसs.
 *
 * Returns number of bytes पढ़ो.
 *
 * See kernel/trace/trace.h क्रम 'struct trace_parser' details.
 */
पूर्णांक trace_get_user(काष्ठा trace_parser *parser, स्थिर अक्षर __user *ubuf,
	माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर ch;
	माप_प्रकार पढ़ो = 0;
	sमाप_प्रकार ret;

	अगर (!*ppos)
		trace_parser_clear(parser);

	ret = get_user(ch, ubuf++);
	अगर (ret)
		जाओ out;

	पढ़ो++;
	cnt--;

	/*
	 * The parser is not finished with the last ग_लिखो,
	 * जारी पढ़ोing the user input without skipping spaces.
	 */
	अगर (!parser->cont) अणु
		/* skip white space */
		जबतक (cnt && है_खाली(ch)) अणु
			ret = get_user(ch, ubuf++);
			अगर (ret)
				जाओ out;
			पढ़ो++;
			cnt--;
		पूर्ण

		parser->idx = 0;

		/* only spaces were written */
		अगर (है_खाली(ch) || !ch) अणु
			*ppos += पढ़ो;
			ret = पढ़ो;
			जाओ out;
		पूर्ण
	पूर्ण

	/* पढ़ो the non-space input */
	जबतक (cnt && !है_खाली(ch) && ch) अणु
		अगर (parser->idx < parser->size - 1)
			parser->buffer[parser->idx++] = ch;
		अन्यथा अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = get_user(ch, ubuf++);
		अगर (ret)
			जाओ out;
		पढ़ो++;
		cnt--;
	पूर्ण

	/* We either got finished input or we have to रुको क्रम another call. */
	अगर (है_खाली(ch) || !ch) अणु
		parser->buffer[parser->idx] = 0;
		parser->cont = false;
	पूर्ण अन्यथा अगर (parser->idx < parser->size - 1) अणु
		parser->cont = true;
		parser->buffer[parser->idx++] = ch;
		/* Make sure the parsed string always terminates with '\0'. */
		parser->buffer[parser->idx] = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	*ppos += पढ़ो;
	ret = पढ़ो;

out:
	वापस ret;
पूर्ण

/* TODO add a seq_buf_to_buffer() */
अटल sमाप_प्रकार trace_seq_to_buffer(काष्ठा trace_seq *s, व्योम *buf, माप_प्रकार cnt)
अणु
	पूर्णांक len;

	अगर (trace_seq_used(s) <= s->seq.पढ़ोpos)
		वापस -EBUSY;

	len = trace_seq_used(s) - s->seq.पढ़ोpos;
	अगर (cnt > len)
		cnt = len;
	स_नकल(buf, s->buffer + s->seq.पढ़ोpos, cnt);

	s->seq.पढ़ोpos += cnt;
	वापस cnt;
पूर्ण

अचिन्हित दीर्घ __पढ़ो_mostly	tracing_thresh;
अटल स्थिर काष्ठा file_operations tracing_max_lat_fops;

#अगर (defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)) && \
	defined(CONFIG_FSNOTIFY)

अटल काष्ठा workqueue_काष्ठा *fsnotअगरy_wq;

अटल व्योम latency_fsnotअगरy_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा trace_array *tr = container_of(work, काष्ठा trace_array,
					      fsnotअगरy_work);
	fsnotअगरy_inode(tr->d_max_latency->d_inode, FS_MODIFY);
पूर्ण

अटल व्योम latency_fsnotअगरy_workfn_irq(काष्ठा irq_work *iwork)
अणु
	काष्ठा trace_array *tr = container_of(iwork, काष्ठा trace_array,
					      fsnotअगरy_irqwork);
	queue_work(fsnotअगरy_wq, &tr->fsnotअगरy_work);
पूर्ण

अटल व्योम trace_create_maxlat_file(काष्ठा trace_array *tr,
				     काष्ठा dentry *d_tracer)
अणु
	INIT_WORK(&tr->fsnotअगरy_work, latency_fsnotअगरy_workfn);
	init_irq_work(&tr->fsnotअगरy_irqwork, latency_fsnotअगरy_workfn_irq);
	tr->d_max_latency = trace_create_file("tracing_max_latency", 0644,
					      d_tracer, &tr->max_latency,
					      &tracing_max_lat_fops);
पूर्ण

__init अटल पूर्णांक latency_fsnotअगरy_init(व्योम)
अणु
	fsnotअगरy_wq = alloc_workqueue("tr_max_lat_wq",
				      WQ_UNBOUND | WQ_HIGHPRI, 0);
	अगर (!fsnotअगरy_wq) अणु
		pr_err("Unable to allocate tr_max_lat_wq\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

late_initcall_sync(latency_fsnotअगरy_init);

व्योम latency_fsnotअगरy(काष्ठा trace_array *tr)
अणु
	अगर (!fsnotअगरy_wq)
		वापस;
	/*
	 * We cannot call queue_work(&tr->fsnotअगरy_work) from here because it's
	 * possible that we are called from __schedule() or करो_idle(), which
	 * could cause a deadlock.
	 */
	irq_work_queue(&tr->fsnotअगरy_irqwork);
पूर्ण

/*
 * (defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)) && \
 *  defined(CONFIG_FSNOTIFY)
 */
#अन्यथा

#घोषणा trace_create_maxlat_file(tr, d_tracer)				\
	trace_create_file("tracing_max_latency", 0644, d_tracer,	\
			  &tr->max_latency, &tracing_max_lat_fops)

#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
/*
 * Copy the new maximum trace पूर्णांकo the separate maximum-trace
 * काष्ठाure. (this way the maximum trace is permanently saved,
 * क्रम later retrieval via /sys/kernel/tracing/tracing_max_latency)
 */
अटल व्योम
__update_max_tr(काष्ठा trace_array *tr, काष्ठा task_काष्ठा *tsk, पूर्णांक cpu)
अणु
	काष्ठा array_buffer *trace_buf = &tr->array_buffer;
	काष्ठा array_buffer *max_buf = &tr->max_buffer;
	काष्ठा trace_array_cpu *data = per_cpu_ptr(trace_buf->data, cpu);
	काष्ठा trace_array_cpu *max_data = per_cpu_ptr(max_buf->data, cpu);

	max_buf->cpu = cpu;
	max_buf->समय_start = data->preempt_बारtamp;

	max_data->saved_latency = tr->max_latency;
	max_data->critical_start = data->critical_start;
	max_data->critical_end = data->critical_end;

	म_नकलन(max_data->comm, tsk->comm, TASK_COMM_LEN);
	max_data->pid = tsk->pid;
	/*
	 * If tsk == current, then use current_uid(), as that करोes not use
	 * RCU. The irq tracer can be called out of RCU scope.
	 */
	अगर (tsk == current)
		max_data->uid = current_uid();
	अन्यथा
		max_data->uid = task_uid(tsk);

	max_data->nice = tsk->अटल_prio - 20 - MAX_RT_PRIO;
	max_data->policy = tsk->policy;
	max_data->rt_priority = tsk->rt_priority;

	/* record this tasks comm */
	tracing_record_cmdline(tsk);
	latency_fsnotअगरy(tr);
पूर्ण

/**
 * update_max_tr - snapshot all trace buffers from global_trace to max_tr
 * @tr: tracer
 * @tsk: the task with the latency
 * @cpu: The cpu that initiated the trace.
 * @cond_data: User data associated with a conditional snapshot
 *
 * Flip the buffers between the @tr and the max_tr and record inक्रमmation
 * about which task was the cause of this latency.
 */
व्योम
update_max_tr(काष्ठा trace_array *tr, काष्ठा task_काष्ठा *tsk, पूर्णांक cpu,
	      व्योम *cond_data)
अणु
	अगर (tr->stop_count)
		वापस;

	WARN_ON_ONCE(!irqs_disabled());

	अगर (!tr->allocated_snapshot) अणु
		/* Only the nop tracer should hit this when disabling */
		WARN_ON_ONCE(tr->current_trace != &nop_trace);
		वापस;
	पूर्ण

	arch_spin_lock(&tr->max_lock);

	/* Inherit the recordable setting from array_buffer */
	अगर (ring_buffer_record_is_set_on(tr->array_buffer.buffer))
		ring_buffer_record_on(tr->max_buffer.buffer);
	अन्यथा
		ring_buffer_record_off(tr->max_buffer.buffer);

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	अगर (tr->cond_snapshot && !tr->cond_snapshot->update(tr, cond_data))
		जाओ out_unlock;
#पूर्ण_अगर
	swap(tr->array_buffer.buffer, tr->max_buffer.buffer);

	__update_max_tr(tr, tsk, cpu);

 out_unlock:
	arch_spin_unlock(&tr->max_lock);
पूर्ण

/**
 * update_max_tr_single - only copy one trace over, and reset the rest
 * @tr: tracer
 * @tsk: task with the latency
 * @cpu: the cpu of the buffer to copy.
 *
 * Flip the trace of a single CPU buffer between the @tr and the max_tr.
 */
व्योम
update_max_tr_single(काष्ठा trace_array *tr, काष्ठा task_काष्ठा *tsk, पूर्णांक cpu)
अणु
	पूर्णांक ret;

	अगर (tr->stop_count)
		वापस;

	WARN_ON_ONCE(!irqs_disabled());
	अगर (!tr->allocated_snapshot) अणु
		/* Only the nop tracer should hit this when disabling */
		WARN_ON_ONCE(tr->current_trace != &nop_trace);
		वापस;
	पूर्ण

	arch_spin_lock(&tr->max_lock);

	ret = ring_buffer_swap_cpu(tr->max_buffer.buffer, tr->array_buffer.buffer, cpu);

	अगर (ret == -EBUSY) अणु
		/*
		 * We failed to swap the buffer due to a commit taking
		 * place on this CPU. We fail to record, but we reset
		 * the max trace buffer (no one ग_लिखोs directly to it)
		 * and flag that it failed.
		 */
		trace_array_prपूर्णांकk_buf(tr->max_buffer.buffer, _THIS_IP_,
			"Failed to swap buffers due to commit in progress\n");
	पूर्ण

	WARN_ON_ONCE(ret && ret != -EAGAIN && ret != -EBUSY);

	__update_max_tr(tr, tsk, cpu);
	arch_spin_unlock(&tr->max_lock);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRACER_MAX_TRACE */

अटल पूर्णांक रुको_on_pipe(काष्ठा trace_iterator *iter, पूर्णांक full)
अणु
	/* Iterators are अटल, they should be filled or empty */
	अगर (trace_buffer_iter(iter, iter->cpu_file))
		वापस 0;

	वापस ring_buffer_रुको(iter->array_buffer->buffer, iter->cpu_file,
				full);
पूर्ण

#अगर_घोषित CONFIG_FTRACE_STARTUP_TEST
अटल bool selftests_can_run;

काष्ठा trace_selftests अणु
	काष्ठा list_head		list;
	काष्ठा tracer			*type;
पूर्ण;

अटल LIST_HEAD(postponed_selftests);

अटल पूर्णांक save_selftest(काष्ठा tracer *type)
अणु
	काष्ठा trace_selftests *selftest;

	selftest = kदो_स्मृति(माप(*selftest), GFP_KERNEL);
	अगर (!selftest)
		वापस -ENOMEM;

	selftest->type = type;
	list_add(&selftest->list, &postponed_selftests);
	वापस 0;
पूर्ण

अटल पूर्णांक run_tracer_selftest(काष्ठा tracer *type)
अणु
	काष्ठा trace_array *tr = &global_trace;
	काष्ठा tracer *saved_tracer = tr->current_trace;
	पूर्णांक ret;

	अगर (!type->selftest || tracing_selftest_disabled)
		वापस 0;

	/*
	 * If a tracer रेजिस्टरs early in boot up (beक्रमe scheduling is
	 * initialized and such), then करो not run its selftests yet.
	 * Instead, run it a little later in the boot process.
	 */
	अगर (!selftests_can_run)
		वापस save_selftest(type);

	अगर (!tracing_is_on()) अणु
		pr_warn("Selftest for tracer %s skipped due to tracing disabled\n",
			type->name);
		वापस 0;
	पूर्ण

	/*
	 * Run a selftest on this tracer.
	 * Here we reset the trace buffer, and set the current
	 * tracer to be this tracer. The tracer can then run some
	 * पूर्णांकernal tracing to verअगरy that everything is in order.
	 * If we fail, we करो not रेजिस्टर this tracer.
	 */
	tracing_reset_online_cpus(&tr->array_buffer);

	tr->current_trace = type;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (type->use_max_tr) अणु
		/* If we expanded the buffers, make sure the max is expanded too */
		अगर (ring_buffer_expanded)
			ring_buffer_resize(tr->max_buffer.buffer, trace_buf_size,
					   RING_BUFFER_ALL_CPUS);
		tr->allocated_snapshot = true;
	पूर्ण
#पूर्ण_अगर

	/* the test is responsible क्रम initializing and enabling */
	pr_info("Testing tracer %s: ", type->name);
	ret = type->selftest(type, tr);
	/* the test is responsible क्रम resetting too */
	tr->current_trace = saved_tracer;
	अगर (ret) अणु
		prपूर्णांकk(KERN_CONT "FAILED!\n");
		/* Add the warning after prपूर्णांकing 'FAILED' */
		WARN_ON(1);
		वापस -1;
	पूर्ण
	/* Only reset on passing, to aव्योम touching corrupted buffers */
	tracing_reset_online_cpus(&tr->array_buffer);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (type->use_max_tr) अणु
		tr->allocated_snapshot = false;

		/* Shrink the max buffer again */
		अगर (ring_buffer_expanded)
			ring_buffer_resize(tr->max_buffer.buffer, 1,
					   RING_BUFFER_ALL_CPUS);
	पूर्ण
#पूर्ण_अगर

	prपूर्णांकk(KERN_CONT "PASSED\n");
	वापस 0;
पूर्ण

अटल __init पूर्णांक init_trace_selftests(व्योम)
अणु
	काष्ठा trace_selftests *p, *n;
	काष्ठा tracer *t, **last;
	पूर्णांक ret;

	selftests_can_run = true;

	mutex_lock(&trace_types_lock);

	अगर (list_empty(&postponed_selftests))
		जाओ out;

	pr_info("Running postponed tracer tests:\n");

	tracing_selftest_running = true;
	list_क्रम_each_entry_safe(p, n, &postponed_selftests, list) अणु
		/* This loop can take minutes when sanitizers are enabled, so
		 * lets make sure we allow RCU processing.
		 */
		cond_resched();
		ret = run_tracer_selftest(p->type);
		/* If the test fails, then warn and हटाओ from available_tracers */
		अगर (ret < 0) अणु
			WARN(1, "tracer: %s failed selftest, disabling\n",
			     p->type->name);
			last = &trace_types;
			क्रम (t = trace_types; t; t = t->next) अणु
				अगर (t == p->type) अणु
					*last = t->next;
					अवरोध;
				पूर्ण
				last = &t->next;
			पूर्ण
		पूर्ण
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण
	tracing_selftest_running = false;

 out:
	mutex_unlock(&trace_types_lock);

	वापस 0;
पूर्ण
core_initcall(init_trace_selftests);
#अन्यथा
अटल अंतरभूत पूर्णांक run_tracer_selftest(काष्ठा tracer *type)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_FTRACE_STARTUP_TEST */

अटल व्योम add_tracer_options(काष्ठा trace_array *tr, काष्ठा tracer *t);

अटल व्योम __init apply_trace_boot_options(व्योम);

/**
 * रेजिस्टर_tracer - रेजिस्टर a tracer with the ftrace प्रणाली.
 * @type: the plugin क्रम the tracer
 *
 * Register a new plugin tracer.
 */
पूर्णांक __init रेजिस्टर_tracer(काष्ठा tracer *type)
अणु
	काष्ठा tracer *t;
	पूर्णांक ret = 0;

	अगर (!type->name) अणु
		pr_info("Tracer must have a name\n");
		वापस -1;
	पूर्ण

	अगर (म_माप(type->name) >= MAX_TRACER_SIZE) अणु
		pr_info("Tracer has a name longer than %d\n", MAX_TRACER_SIZE);
		वापस -1;
	पूर्ण

	अगर (security_locked_करोwn(LOCKDOWN_TRACEFS)) अणु
		pr_warn("Can not register tracer %s due to lockdown\n",
			   type->name);
		वापस -EPERM;
	पूर्ण

	mutex_lock(&trace_types_lock);

	tracing_selftest_running = true;

	क्रम (t = trace_types; t; t = t->next) अणु
		अगर (म_भेद(type->name, t->name) == 0) अणु
			/* alपढ़ोy found */
			pr_info("Tracer %s already registered\n",
				type->name);
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!type->set_flag)
		type->set_flag = &dummy_set_flag;
	अगर (!type->flags) अणु
		/*allocate a dummy tracer_flags*/
		type->flags = kदो_स्मृति(माप(*type->flags), GFP_KERNEL);
		अगर (!type->flags) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		type->flags->val = 0;
		type->flags->opts = dummy_tracer_opt;
	पूर्ण अन्यथा
		अगर (!type->flags->opts)
			type->flags->opts = dummy_tracer_opt;

	/* store the tracer क्रम __set_tracer_option */
	type->flags->trace = type;

	ret = run_tracer_selftest(type);
	अगर (ret < 0)
		जाओ out;

	type->next = trace_types;
	trace_types = type;
	add_tracer_options(&global_trace, type);

 out:
	tracing_selftest_running = false;
	mutex_unlock(&trace_types_lock);

	अगर (ret || !शेष_bootup_tracer)
		जाओ out_unlock;

	अगर (म_भेदन(शेष_bootup_tracer, type->name, MAX_TRACER_SIZE))
		जाओ out_unlock;

	prपूर्णांकk(KERN_INFO "Starting tracer '%s'\n", type->name);
	/* Do we want this tracer to start on bootup? */
	tracing_set_tracer(&global_trace, type->name);
	शेष_bootup_tracer = शून्य;

	apply_trace_boot_options();

	/* disable other selftests, since this will अवरोध it. */
	disable_tracing_selftest("running a tracer");

 out_unlock:
	वापस ret;
पूर्ण

अटल व्योम tracing_reset_cpu(काष्ठा array_buffer *buf, पूर्णांक cpu)
अणु
	काष्ठा trace_buffer *buffer = buf->buffer;

	अगर (!buffer)
		वापस;

	ring_buffer_record_disable(buffer);

	/* Make sure all commits have finished */
	synchronize_rcu();
	ring_buffer_reset_cpu(buffer, cpu);

	ring_buffer_record_enable(buffer);
पूर्ण

व्योम tracing_reset_online_cpus(काष्ठा array_buffer *buf)
अणु
	काष्ठा trace_buffer *buffer = buf->buffer;

	अगर (!buffer)
		वापस;

	ring_buffer_record_disable(buffer);

	/* Make sure all commits have finished */
	synchronize_rcu();

	buf->समय_start = buffer_ftrace_now(buf, buf->cpu);

	ring_buffer_reset_online_cpus(buffer);

	ring_buffer_record_enable(buffer);
पूर्ण

/* Must have trace_types_lock held */
व्योम tracing_reset_all_online_cpus(व्योम)
अणु
	काष्ठा trace_array *tr;

	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (!tr->clear_trace)
			जारी;
		tr->clear_trace = false;
		tracing_reset_online_cpus(&tr->array_buffer);
#अगर_घोषित CONFIG_TRACER_MAX_TRACE
		tracing_reset_online_cpus(&tr->max_buffer);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक *tgid_map;

#घोषणा SAVED_CMDLINES_DEFAULT 128
#घोषणा NO_CMDLINE_MAP अच_पूर्णांक_उच्च
अटल arch_spinlock_t trace_cmdline_lock = __ARCH_SPIN_LOCK_UNLOCKED;
काष्ठा saved_cmdlines_buffer अणु
	अचिन्हित map_pid_to_cmdline[PID_MAX_DEFAULT+1];
	अचिन्हित *map_cmdline_to_pid;
	अचिन्हित cmdline_num;
	पूर्णांक cmdline_idx;
	अक्षर *saved_cmdlines;
पूर्ण;
अटल काष्ठा saved_cmdlines_buffer *savedcmd;

अटल अंतरभूत अक्षर *get_saved_cmdlines(पूर्णांक idx)
अणु
	वापस &savedcmd->saved_cmdlines[idx * TASK_COMM_LEN];
पूर्ण

अटल अंतरभूत व्योम set_cmdline(पूर्णांक idx, स्थिर अक्षर *cmdline)
अणु
	म_नकलन(get_saved_cmdlines(idx), cmdline, TASK_COMM_LEN);
पूर्ण

अटल पूर्णांक allocate_cmdlines_buffer(अचिन्हित पूर्णांक val,
				    काष्ठा saved_cmdlines_buffer *s)
अणु
	s->map_cmdline_to_pid = kदो_स्मृति_array(val,
					      माप(*s->map_cmdline_to_pid),
					      GFP_KERNEL);
	अगर (!s->map_cmdline_to_pid)
		वापस -ENOMEM;

	s->saved_cmdlines = kदो_स्मृति_array(TASK_COMM_LEN, val, GFP_KERNEL);
	अगर (!s->saved_cmdlines) अणु
		kमुक्त(s->map_cmdline_to_pid);
		वापस -ENOMEM;
	पूर्ण

	s->cmdline_idx = 0;
	s->cmdline_num = val;
	स_रखो(&s->map_pid_to_cmdline, NO_CMDLINE_MAP,
	       माप(s->map_pid_to_cmdline));
	स_रखो(s->map_cmdline_to_pid, NO_CMDLINE_MAP,
	       val * माप(*s->map_cmdline_to_pid));

	वापस 0;
पूर्ण

अटल पूर्णांक trace_create_savedcmd(व्योम)
अणु
	पूर्णांक ret;

	savedcmd = kदो_स्मृति(माप(*savedcmd), GFP_KERNEL);
	अगर (!savedcmd)
		वापस -ENOMEM;

	ret = allocate_cmdlines_buffer(SAVED_CMDLINES_DEFAULT, savedcmd);
	अगर (ret < 0) अणु
		kमुक्त(savedcmd);
		savedcmd = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक is_tracing_stopped(व्योम)
अणु
	वापस global_trace.stop_count;
पूर्ण

/**
 * tracing_start - quick start of the tracer
 *
 * If tracing is enabled but was stopped by tracing_stop,
 * this will start the tracer back up.
 */
व्योम tracing_start(व्योम)
अणु
	काष्ठा trace_buffer *buffer;
	अचिन्हित दीर्घ flags;

	अगर (tracing_disabled)
		वापस;

	raw_spin_lock_irqsave(&global_trace.start_lock, flags);
	अगर (--global_trace.stop_count) अणु
		अगर (global_trace.stop_count < 0) अणु
			/* Someone screwed up their debugging */
			WARN_ON_ONCE(1);
			global_trace.stop_count = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	/* Prevent the buffers from चयनing */
	arch_spin_lock(&global_trace.max_lock);

	buffer = global_trace.array_buffer.buffer;
	अगर (buffer)
		ring_buffer_record_enable(buffer);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	buffer = global_trace.max_buffer.buffer;
	अगर (buffer)
		ring_buffer_record_enable(buffer);
#पूर्ण_अगर

	arch_spin_unlock(&global_trace.max_lock);

 out:
	raw_spin_unlock_irqrestore(&global_trace.start_lock, flags);
पूर्ण

अटल व्योम tracing_start_tr(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_buffer *buffer;
	अचिन्हित दीर्घ flags;

	अगर (tracing_disabled)
		वापस;

	/* If global, we need to also start the max tracer */
	अगर (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		वापस tracing_start();

	raw_spin_lock_irqsave(&tr->start_lock, flags);

	अगर (--tr->stop_count) अणु
		अगर (tr->stop_count < 0) अणु
			/* Someone screwed up their debugging */
			WARN_ON_ONCE(1);
			tr->stop_count = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	buffer = tr->array_buffer.buffer;
	अगर (buffer)
		ring_buffer_record_enable(buffer);

 out:
	raw_spin_unlock_irqrestore(&tr->start_lock, flags);
पूर्ण

/**
 * tracing_stop - quick stop of the tracer
 *
 * Light weight way to stop tracing. Use in conjunction with
 * tracing_start.
 */
व्योम tracing_stop(व्योम)
अणु
	काष्ठा trace_buffer *buffer;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&global_trace.start_lock, flags);
	अगर (global_trace.stop_count++)
		जाओ out;

	/* Prevent the buffers from चयनing */
	arch_spin_lock(&global_trace.max_lock);

	buffer = global_trace.array_buffer.buffer;
	अगर (buffer)
		ring_buffer_record_disable(buffer);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	buffer = global_trace.max_buffer.buffer;
	अगर (buffer)
		ring_buffer_record_disable(buffer);
#पूर्ण_अगर

	arch_spin_unlock(&global_trace.max_lock);

 out:
	raw_spin_unlock_irqrestore(&global_trace.start_lock, flags);
पूर्ण

अटल व्योम tracing_stop_tr(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_buffer *buffer;
	अचिन्हित दीर्घ flags;

	/* If global, we need to also stop the max tracer */
	अगर (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		वापस tracing_stop();

	raw_spin_lock_irqsave(&tr->start_lock, flags);
	अगर (tr->stop_count++)
		जाओ out;

	buffer = tr->array_buffer.buffer;
	अगर (buffer)
		ring_buffer_record_disable(buffer);

 out:
	raw_spin_unlock_irqrestore(&tr->start_lock, flags);
पूर्ण

अटल पूर्णांक trace_save_cmdline(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित tpid, idx;

	/* treat recording of idle task as a success */
	अगर (!tsk->pid)
		वापस 1;

	tpid = tsk->pid & (PID_MAX_DEFAULT - 1);

	/*
	 * It's not the end of the world if we don't get
	 * the lock, but we also करोn't want to spin
	 * nor करो we want to disable पूर्णांकerrupts,
	 * so अगर we miss here, then better luck next समय.
	 */
	अगर (!arch_spin_trylock(&trace_cmdline_lock))
		वापस 0;

	idx = savedcmd->map_pid_to_cmdline[tpid];
	अगर (idx == NO_CMDLINE_MAP) अणु
		idx = (savedcmd->cmdline_idx + 1) % savedcmd->cmdline_num;

		savedcmd->map_pid_to_cmdline[tpid] = idx;
		savedcmd->cmdline_idx = idx;
	पूर्ण

	savedcmd->map_cmdline_to_pid[idx] = tsk->pid;
	set_cmdline(idx, tsk->comm);

	arch_spin_unlock(&trace_cmdline_lock);

	वापस 1;
पूर्ण

अटल व्योम __trace_find_cmdline(पूर्णांक pid, अक्षर comm[])
अणु
	अचिन्हित map;
	पूर्णांक tpid;

	अगर (!pid) अणु
		म_नकल(comm, "<idle>");
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(pid < 0)) अणु
		म_नकल(comm, "<XXX>");
		वापस;
	पूर्ण

	tpid = pid & (PID_MAX_DEFAULT - 1);
	map = savedcmd->map_pid_to_cmdline[tpid];
	अगर (map != NO_CMDLINE_MAP) अणु
		tpid = savedcmd->map_cmdline_to_pid[map];
		अगर (tpid == pid) अणु
			strlcpy(comm, get_saved_cmdlines(map), TASK_COMM_LEN);
			वापस;
		पूर्ण
	पूर्ण
	म_नकल(comm, "<...>");
पूर्ण

व्योम trace_find_cmdline(पूर्णांक pid, अक्षर comm[])
अणु
	preempt_disable();
	arch_spin_lock(&trace_cmdline_lock);

	__trace_find_cmdline(pid, comm);

	arch_spin_unlock(&trace_cmdline_lock);
	preempt_enable();
पूर्ण

पूर्णांक trace_find_tgid(पूर्णांक pid)
अणु
	अगर (unlikely(!tgid_map || !pid || pid > PID_MAX_DEFAULT))
		वापस 0;

	वापस tgid_map[pid];
पूर्ण

अटल पूर्णांक trace_save_tgid(काष्ठा task_काष्ठा *tsk)
अणु
	/* treat recording of idle task as a success */
	अगर (!tsk->pid)
		वापस 1;

	अगर (unlikely(!tgid_map || tsk->pid > PID_MAX_DEFAULT))
		वापस 0;

	tgid_map[tsk->pid] = tsk->tgid;
	वापस 1;
पूर्ण

अटल bool tracing_record_taskinfo_skip(पूर्णांक flags)
अणु
	अगर (unlikely(!(flags & (TRACE_RECORD_CMDLINE | TRACE_RECORD_TGID))))
		वापस true;
	अगर (!__this_cpu_पढ़ो(trace_taskinfo_save))
		वापस true;
	वापस false;
पूर्ण

/**
 * tracing_record_taskinfo - record the task info of a task
 *
 * @task:  task to record
 * @flags: TRACE_RECORD_CMDLINE क्रम recording comm
 *         TRACE_RECORD_TGID क्रम recording tgid
 */
व्योम tracing_record_taskinfo(काष्ठा task_काष्ठा *task, पूर्णांक flags)
अणु
	bool करोne;

	अगर (tracing_record_taskinfo_skip(flags))
		वापस;

	/*
	 * Record as much task inक्रमmation as possible. If some fail, जारी
	 * to try to record the others.
	 */
	करोne = !(flags & TRACE_RECORD_CMDLINE) || trace_save_cmdline(task);
	करोne &= !(flags & TRACE_RECORD_TGID) || trace_save_tgid(task);

	/* If recording any inक्रमmation failed, retry again soon. */
	अगर (!करोne)
		वापस;

	__this_cpu_ग_लिखो(trace_taskinfo_save, false);
पूर्ण

/**
 * tracing_record_taskinfo_sched_चयन - record task info क्रम sched_चयन
 *
 * @prev: previous task during sched_चयन
 * @next: next task during sched_चयन
 * @flags: TRACE_RECORD_CMDLINE क्रम recording comm
 *         TRACE_RECORD_TGID क्रम recording tgid
 */
व्योम tracing_record_taskinfo_sched_चयन(काष्ठा task_काष्ठा *prev,
					  काष्ठा task_काष्ठा *next, पूर्णांक flags)
अणु
	bool करोne;

	अगर (tracing_record_taskinfo_skip(flags))
		वापस;

	/*
	 * Record as much task inक्रमmation as possible. If some fail, जारी
	 * to try to record the others.
	 */
	करोne  = !(flags & TRACE_RECORD_CMDLINE) || trace_save_cmdline(prev);
	करोne &= !(flags & TRACE_RECORD_CMDLINE) || trace_save_cmdline(next);
	करोne &= !(flags & TRACE_RECORD_TGID) || trace_save_tgid(prev);
	करोne &= !(flags & TRACE_RECORD_TGID) || trace_save_tgid(next);

	/* If recording any inक्रमmation failed, retry again soon. */
	अगर (!करोne)
		वापस;

	__this_cpu_ग_लिखो(trace_taskinfo_save, false);
पूर्ण

/* Helpers to record a specअगरic task inक्रमmation */
व्योम tracing_record_cmdline(काष्ठा task_काष्ठा *task)
अणु
	tracing_record_taskinfo(task, TRACE_RECORD_CMDLINE);
पूर्ण

व्योम tracing_record_tgid(काष्ठा task_काष्ठा *task)
अणु
	tracing_record_taskinfo(task, TRACE_RECORD_TGID);
पूर्ण

/*
 * Several functions वापस TRACE_TYPE_PARTIAL_LINE अगर the trace_seq
 * overflowed, and TRACE_TYPE_HANDLED otherwise. This helper function
 * simplअगरies those functions and keeps them in sync.
 */
क्रमागत prपूर्णांक_line_t trace_handle_वापस(काष्ठा trace_seq *s)
अणु
	वापस trace_seq_has_overflowed(s) ?
		TRACE_TYPE_PARTIAL_LINE : TRACE_TYPE_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(trace_handle_वापस);

अचिन्हित पूर्णांक tracing_gen_ctx_irq_test(अचिन्हित पूर्णांक irqs_status)
अणु
	अचिन्हित पूर्णांक trace_flags = irqs_status;
	अचिन्हित पूर्णांक pc;

	pc = preempt_count();

	अगर (pc & NMI_MASK)
		trace_flags |= TRACE_FLAG_NMI;
	अगर (pc & HARसूचीQ_MASK)
		trace_flags |= TRACE_FLAG_HARसूचीQ;
	अगर (in_serving_softirq())
		trace_flags |= TRACE_FLAG_SOFTIRQ;

	अगर (tअगर_need_resched())
		trace_flags |= TRACE_FLAG_NEED_RESCHED;
	अगर (test_preempt_need_resched())
		trace_flags |= TRACE_FLAG_PREEMPT_RESCHED;
	वापस (trace_flags << 16) | (pc & 0xff);
पूर्ण

काष्ठा ring_buffer_event *
trace_buffer_lock_reserve(काष्ठा trace_buffer *buffer,
			  पूर्णांक type,
			  अचिन्हित दीर्घ len,
			  अचिन्हित पूर्णांक trace_ctx)
अणु
	वापस __trace_buffer_lock_reserve(buffer, type, len, trace_ctx);
पूर्ण

DEFINE_PER_CPU(काष्ठा ring_buffer_event *, trace_buffered_event);
DEFINE_PER_CPU(पूर्णांक, trace_buffered_event_cnt);
अटल पूर्णांक trace_buffered_event_ref;

/**
 * trace_buffered_event_enable - enable buffering events
 *
 * When events are being filtered, it is quicker to use a temporary
 * buffer to ग_लिखो the event data पूर्णांकo अगर there's a likely chance
 * that it will not be committed. The discard of the ring buffer
 * is not as fast as committing, and is much slower than copying
 * a commit.
 *
 * When an event is to be filtered, allocate per cpu buffers to
 * ग_लिखो the event data पूर्णांकo, and अगर the event is filtered and discarded
 * it is simply dropped, otherwise, the entire data is to be committed
 * in one shot.
 */
व्योम trace_buffered_event_enable(व्योम)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा page *page;
	पूर्णांक cpu;

	WARN_ON_ONCE(!mutex_is_locked(&event_mutex));

	अगर (trace_buffered_event_ref++)
		वापस;

	क्रम_each_tracing_cpu(cpu) अणु
		page = alloc_pages_node(cpu_to_node(cpu),
					GFP_KERNEL | __GFP_NORETRY, 0);
		अगर (!page)
			जाओ failed;

		event = page_address(page);
		स_रखो(event, 0, माप(*event));

		per_cpu(trace_buffered_event, cpu) = event;

		preempt_disable();
		अगर (cpu == smp_processor_id() &&
		    __this_cpu_पढ़ो(trace_buffered_event) !=
		    per_cpu(trace_buffered_event, cpu))
			WARN_ON_ONCE(1);
		preempt_enable();
	पूर्ण

	वापस;
 failed:
	trace_buffered_event_disable();
पूर्ण

अटल व्योम enable_trace_buffered_event(व्योम *data)
अणु
	/* Probably not needed, but करो it anyway */
	smp_rmb();
	this_cpu_dec(trace_buffered_event_cnt);
पूर्ण

अटल व्योम disable_trace_buffered_event(व्योम *data)
अणु
	this_cpu_inc(trace_buffered_event_cnt);
पूर्ण

/**
 * trace_buffered_event_disable - disable buffering events
 *
 * When a filter is हटाओd, it is faster to not use the buffered
 * events, and to commit directly पूर्णांकo the ring buffer. Free up
 * the temp buffers when there are no more users. This requires
 * special synchronization with current events.
 */
व्योम trace_buffered_event_disable(व्योम)
अणु
	पूर्णांक cpu;

	WARN_ON_ONCE(!mutex_is_locked(&event_mutex));

	अगर (WARN_ON_ONCE(!trace_buffered_event_ref))
		वापस;

	अगर (--trace_buffered_event_ref)
		वापस;

	preempt_disable();
	/* For each CPU, set the buffer as used. */
	smp_call_function_many(tracing_buffer_mask,
			       disable_trace_buffered_event, शून्य, 1);
	preempt_enable();

	/* Wait क्रम all current users to finish */
	synchronize_rcu();

	क्रम_each_tracing_cpu(cpu) अणु
		मुक्त_page((अचिन्हित दीर्घ)per_cpu(trace_buffered_event, cpu));
		per_cpu(trace_buffered_event, cpu) = शून्य;
	पूर्ण
	/*
	 * Make sure trace_buffered_event is शून्य beक्रमe clearing
	 * trace_buffered_event_cnt.
	 */
	smp_wmb();

	preempt_disable();
	/* Do the work on each cpu */
	smp_call_function_many(tracing_buffer_mask,
			       enable_trace_buffered_event, शून्य, 1);
	preempt_enable();
पूर्ण

अटल काष्ठा trace_buffer *temp_buffer;

काष्ठा ring_buffer_event *
trace_event_buffer_lock_reserve(काष्ठा trace_buffer **current_rb,
			  काष्ठा trace_event_file *trace_file,
			  पूर्णांक type, अचिन्हित दीर्घ len,
			  अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा ring_buffer_event *entry;
	काष्ठा trace_array *tr = trace_file->tr;
	पूर्णांक val;

	*current_rb = tr->array_buffer.buffer;

	अगर (!tr->no_filter_buffering_ref &&
	    (trace_file->flags & (EVENT_खाता_FL_SOFT_DISABLED | EVENT_खाता_FL_FILTERED)) &&
	    (entry = this_cpu_पढ़ो(trace_buffered_event))) अणु
		/* Try to use the per cpu buffer first */
		val = this_cpu_inc_वापस(trace_buffered_event_cnt);
		अगर ((len < (PAGE_SIZE - माप(*entry) - माप(entry->array[0]))) && val == 1) अणु
			trace_event_setup(entry, type, trace_ctx);
			entry->array[0] = len;
			वापस entry;
		पूर्ण
		this_cpu_dec(trace_buffered_event_cnt);
	पूर्ण

	entry = __trace_buffer_lock_reserve(*current_rb, type, len,
					    trace_ctx);
	/*
	 * If tracing is off, but we have triggers enabled
	 * we still need to look at the event data. Use the temp_buffer
	 * to store the trace event क्रम the trigger to use. It's recursive
	 * safe and will not be recorded anywhere.
	 */
	अगर (!entry && trace_file->flags & EVENT_खाता_FL_TRIGGER_COND) अणु
		*current_rb = temp_buffer;
		entry = __trace_buffer_lock_reserve(*current_rb, type, len,
						    trace_ctx);
	पूर्ण
	वापस entry;
पूर्ण
EXPORT_SYMBOL_GPL(trace_event_buffer_lock_reserve);

अटल DEFINE_SPINLOCK(tracepoपूर्णांक_iter_lock);
अटल DEFINE_MUTEX(tracepoपूर्णांक_prपूर्णांकk_mutex);

अटल व्योम output_prपूर्णांकk(काष्ठा trace_event_buffer *fbuffer)
अणु
	काष्ठा trace_event_call *event_call;
	काष्ठा trace_event_file *file;
	काष्ठा trace_event *event;
	अचिन्हित दीर्घ flags;
	काष्ठा trace_iterator *iter = tracepoपूर्णांक_prपूर्णांक_iter;

	/* We should never get here अगर iter is शून्य */
	अगर (WARN_ON_ONCE(!iter))
		वापस;

	event_call = fbuffer->trace_file->event_call;
	अगर (!event_call || !event_call->event.funcs ||
	    !event_call->event.funcs->trace)
		वापस;

	file = fbuffer->trace_file;
	अगर (test_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &file->flags) ||
	    (unlikely(file->flags & EVENT_खाता_FL_FILTERED) &&
	     !filter_match_preds(file->filter, fbuffer->entry)))
		वापस;

	event = &fbuffer->trace_file->event_call->event;

	spin_lock_irqsave(&tracepoपूर्णांक_iter_lock, flags);
	trace_seq_init(&iter->seq);
	iter->ent = fbuffer->entry;
	event_call->event.funcs->trace(iter, 0, event);
	trace_seq_अ_दो(&iter->seq, 0);
	prपूर्णांकk("%s", iter->seq.buffer);

	spin_unlock_irqrestore(&tracepoपूर्णांक_iter_lock, flags);
पूर्ण

पूर्णांक tracepoपूर्णांक_prपूर्णांकk_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp,
			     loff_t *ppos)
अणु
	पूर्णांक save_tracepoपूर्णांक_prपूर्णांकk;
	पूर्णांक ret;

	mutex_lock(&tracepoपूर्णांक_prपूर्णांकk_mutex);
	save_tracepoपूर्णांक_prपूर्णांकk = tracepoपूर्णांक_prपूर्णांकk;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	/*
	 * This will क्रमce निकासing early, as tracepoपूर्णांक_prपूर्णांकk
	 * is always zero when tracepoपूर्णांक_prपूर्णांकk_iter is not allocated
	 */
	अगर (!tracepoपूर्णांक_prपूर्णांक_iter)
		tracepoपूर्णांक_prपूर्णांकk = 0;

	अगर (save_tracepoपूर्णांक_prपूर्णांकk == tracepoपूर्णांक_prपूर्णांकk)
		जाओ out;

	अगर (tracepoपूर्णांक_prपूर्णांकk)
		अटल_key_enable(&tracepoपूर्णांक_prपूर्णांकk_key.key);
	अन्यथा
		अटल_key_disable(&tracepoपूर्णांक_prपूर्णांकk_key.key);

 out:
	mutex_unlock(&tracepoपूर्णांक_prपूर्णांकk_mutex);

	वापस ret;
पूर्ण

व्योम trace_event_buffer_commit(काष्ठा trace_event_buffer *fbuffer)
अणु
	अगर (अटल_key_false(&tracepoपूर्णांक_prपूर्णांकk_key.key))
		output_prपूर्णांकk(fbuffer);

	अगर (अटल_branch_unlikely(&trace_event_exports_enabled))
		ftrace_exports(fbuffer->event, TRACE_EXPORT_EVENT);
	event_trigger_unlock_commit_regs(fbuffer->trace_file, fbuffer->buffer,
				    fbuffer->event, fbuffer->entry,
				    fbuffer->trace_ctx, fbuffer->regs);
पूर्ण
EXPORT_SYMBOL_GPL(trace_event_buffer_commit);

/*
 * Skip 3:
 *
 *   trace_buffer_unlock_commit_regs()
 *   trace_event_buffer_commit()
 *   trace_event_raw_event_xxx()
 */
# define STACK_SKIP 3

व्योम trace_buffer_unlock_commit_regs(काष्ठा trace_array *tr,
				     काष्ठा trace_buffer *buffer,
				     काष्ठा ring_buffer_event *event,
				     अचिन्हित पूर्णांक trace_ctx,
				     काष्ठा pt_regs *regs)
अणु
	__buffer_unlock_commit(buffer, event);

	/*
	 * If regs is not set, then skip the necessary functions.
	 * Note, we can still get here via blktrace, wakeup tracer
	 * and mmiotrace, but that's ok अगर they lose a function or
	 * two. They are not that meaningful.
	 */
	ftrace_trace_stack(tr, buffer, trace_ctx, regs ? 0 : STACK_SKIP, regs);
	ftrace_trace_userstack(tr, buffer, trace_ctx);
पूर्ण

/*
 * Similar to trace_buffer_unlock_commit_regs() but करो not dump stack.
 */
व्योम
trace_buffer_unlock_commit_nostack(काष्ठा trace_buffer *buffer,
				   काष्ठा ring_buffer_event *event)
अणु
	__buffer_unlock_commit(buffer, event);
पूर्ण

व्योम
trace_function(काष्ठा trace_array *tr, अचिन्हित दीर्घ ip, अचिन्हित दीर्घ
	       parent_ip, अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_event_call *call = &event_function;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ring_buffer_event *event;
	काष्ठा ftrace_entry *entry;

	event = __trace_buffer_lock_reserve(buffer, TRACE_FN, माप(*entry),
					    trace_ctx);
	अगर (!event)
		वापस;
	entry	= ring_buffer_event_data(event);
	entry->ip			= ip;
	entry->parent_ip		= parent_ip;

	अगर (!call_filter_check_discard(call, entry, buffer, event)) अणु
		अगर (अटल_branch_unlikely(&trace_function_exports_enabled))
			ftrace_exports(event, TRACE_EXPORT_FUNCTION);
		__buffer_unlock_commit(buffer, event);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

/* Allow 4 levels of nesting: normal, softirq, irq, NMI */
#घोषणा FTRACE_KSTACK_NESTING	4

#घोषणा FTRACE_KSTACK_ENTRIES	(PAGE_SIZE / FTRACE_KSTACK_NESTING)

काष्ठा ftrace_stack अणु
	अचिन्हित दीर्घ		calls[FTRACE_KSTACK_ENTRIES];
पूर्ण;


काष्ठा ftrace_stacks अणु
	काष्ठा ftrace_stack	stacks[FTRACE_KSTACK_NESTING];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा ftrace_stacks, ftrace_stacks);
अटल DEFINE_PER_CPU(पूर्णांक, ftrace_stack_reserve);

अटल व्योम __ftrace_trace_stack(काष्ठा trace_buffer *buffer,
				 अचिन्हित पूर्णांक trace_ctx,
				 पूर्णांक skip, काष्ठा pt_regs *regs)
अणु
	काष्ठा trace_event_call *call = &event_kernel_stack;
	काष्ठा ring_buffer_event *event;
	अचिन्हित पूर्णांक size, nr_entries;
	काष्ठा ftrace_stack *fstack;
	काष्ठा stack_entry *entry;
	पूर्णांक stackidx;

	/*
	 * Add one, क्रम this function and the call to save_stack_trace()
	 * If regs is set, then these functions will not be in the way.
	 */
#अगर_अघोषित CONFIG_UNWINDER_ORC
	अगर (!regs)
		skip++;
#पूर्ण_अगर

	preempt_disable_notrace();

	stackidx = __this_cpu_inc_वापस(ftrace_stack_reserve) - 1;

	/* This should never happen. If it करोes, yell once and skip */
	अगर (WARN_ON_ONCE(stackidx >= FTRACE_KSTACK_NESTING))
		जाओ out;

	/*
	 * The above __this_cpu_inc_वापस() is 'atomic' cpu local. An
	 * पूर्णांकerrupt will either see the value pre increment or post
	 * increment. If the पूर्णांकerrupt happens pre increment it will have
	 * restored the counter when it वापसs.  We just need a barrier to
	 * keep gcc from moving things around.
	 */
	barrier();

	fstack = this_cpu_ptr(ftrace_stacks.stacks) + stackidx;
	size = ARRAY_SIZE(fstack->calls);

	अगर (regs) अणु
		nr_entries = stack_trace_save_regs(regs, fstack->calls,
						   size, skip);
	पूर्ण अन्यथा अणु
		nr_entries = stack_trace_save(fstack->calls, size, skip);
	पूर्ण

	size = nr_entries * माप(अचिन्हित दीर्घ);
	event = __trace_buffer_lock_reserve(buffer, TRACE_STACK,
				    (माप(*entry) - माप(entry->caller)) + size,
				    trace_ctx);
	अगर (!event)
		जाओ out;
	entry = ring_buffer_event_data(event);

	स_नकल(&entry->caller, fstack->calls, size);
	entry->size = nr_entries;

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		__buffer_unlock_commit(buffer, event);

 out:
	/* Again, करोn't let gcc optimize things here */
	barrier();
	__this_cpu_dec(ftrace_stack_reserve);
	preempt_enable_notrace();

पूर्ण

अटल अंतरभूत व्योम ftrace_trace_stack(काष्ठा trace_array *tr,
				      काष्ठा trace_buffer *buffer,
				      अचिन्हित पूर्णांक trace_ctx,
				      पूर्णांक skip, काष्ठा pt_regs *regs)
अणु
	अगर (!(tr->trace_flags & TRACE_ITER_STACKTRACE))
		वापस;

	__ftrace_trace_stack(buffer, trace_ctx, skip, regs);
पूर्ण

व्योम __trace_stack(काष्ठा trace_array *tr, अचिन्हित पूर्णांक trace_ctx,
		   पूर्णांक skip)
अणु
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;

	अगर (rcu_is_watching()) अणु
		__ftrace_trace_stack(buffer, trace_ctx, skip, शून्य);
		वापस;
	पूर्ण

	/*
	 * When an NMI triggers, RCU is enabled via rcu_nmi_enter(),
	 * but अगर the above rcu_is_watching() failed, then the NMI
	 * triggered someplace critical, and rcu_irq_enter() should
	 * not be called from NMI.
	 */
	अगर (unlikely(in_nmi()))
		वापस;

	rcu_irq_enter_irqson();
	__ftrace_trace_stack(buffer, trace_ctx, skip, शून्य);
	rcu_irq_निकास_irqson();
पूर्ण

/**
 * trace_dump_stack - record a stack back trace in the trace buffer
 * @skip: Number of functions to skip (helper handlers)
 */
व्योम trace_dump_stack(पूर्णांक skip)
अणु
	अगर (tracing_disabled || tracing_selftest_running)
		वापस;

#अगर_अघोषित CONFIG_UNWINDER_ORC
	/* Skip 1 to skip this function. */
	skip++;
#पूर्ण_अगर
	__ftrace_trace_stack(global_trace.array_buffer.buffer,
			     tracing_gen_ctx(), skip, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(trace_dump_stack);

#अगर_घोषित CONFIG_USER_STACKTRACE_SUPPORT
अटल DEFINE_PER_CPU(पूर्णांक, user_stack_count);

अटल व्योम
ftrace_trace_userstack(काष्ठा trace_array *tr,
		       काष्ठा trace_buffer *buffer, अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_event_call *call = &event_user_stack;
	काष्ठा ring_buffer_event *event;
	काष्ठा userstack_entry *entry;

	अगर (!(tr->trace_flags & TRACE_ITER_USERSTACKTRACE))
		वापस;

	/*
	 * NMIs can not handle page faults, even with fix ups.
	 * The save user stack can (and often करोes) fault.
	 */
	अगर (unlikely(in_nmi()))
		वापस;

	/*
	 * prevent recursion, since the user stack tracing may
	 * trigger other kernel events.
	 */
	preempt_disable();
	अगर (__this_cpu_पढ़ो(user_stack_count))
		जाओ out;

	__this_cpu_inc(user_stack_count);

	event = __trace_buffer_lock_reserve(buffer, TRACE_USER_STACK,
					    माप(*entry), trace_ctx);
	अगर (!event)
		जाओ out_drop_count;
	entry	= ring_buffer_event_data(event);

	entry->tgid		= current->tgid;
	स_रखो(&entry->caller, 0, माप(entry->caller));

	stack_trace_save_user(entry->caller, FTRACE_STACK_ENTRIES);
	अगर (!call_filter_check_discard(call, entry, buffer, event))
		__buffer_unlock_commit(buffer, event);

 out_drop_count:
	__this_cpu_dec(user_stack_count);
 out:
	preempt_enable();
पूर्ण
#अन्यथा /* CONFIG_USER_STACKTRACE_SUPPORT */
अटल व्योम ftrace_trace_userstack(काष्ठा trace_array *tr,
				   काष्ठा trace_buffer *buffer,
				   अचिन्हित पूर्णांक trace_ctx)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_USER_STACKTRACE_SUPPORT */

#पूर्ण_अगर /* CONFIG_STACKTRACE */

अटल अंतरभूत व्योम
func_repeats_set_delta_ts(काष्ठा func_repeats_entry *entry,
			  अचिन्हित दीर्घ दीर्घ delta)
अणु
	entry->bottom_delta_ts = delta & U32_MAX;
	entry->top_delta_ts = (delta >> 32);
पूर्ण

व्योम trace_last_func_repeats(काष्ठा trace_array *tr,
			     काष्ठा trace_func_repeats *last_info,
			     अचिन्हित पूर्णांक trace_ctx)
अणु
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा func_repeats_entry *entry;
	काष्ठा ring_buffer_event *event;
	u64 delta;

	event = __trace_buffer_lock_reserve(buffer, TRACE_FUNC_REPEATS,
					    माप(*entry), trace_ctx);
	अगर (!event)
		वापस;

	delta = ring_buffer_event_समय_stamp(buffer, event) -
		last_info->ts_last_call;

	entry = ring_buffer_event_data(event);
	entry->ip = last_info->ip;
	entry->parent_ip = last_info->parent_ip;
	entry->count = last_info->count;
	func_repeats_set_delta_ts(entry, delta);

	__buffer_unlock_commit(buffer, event);
पूर्ण

/* created क्रम use with alloc_percpu */
काष्ठा trace_buffer_काष्ठा अणु
	पूर्णांक nesting;
	अक्षर buffer[4][TRACE_BUF_SIZE];
पूर्ण;

अटल काष्ठा trace_buffer_काष्ठा *trace_percpu_buffer;

/*
 * This allows क्रम lockless recording.  If we're nested too deeply, then
 * this वापसs शून्य.
 */
अटल अक्षर *get_trace_buf(व्योम)
अणु
	काष्ठा trace_buffer_काष्ठा *buffer = this_cpu_ptr(trace_percpu_buffer);

	अगर (!buffer || buffer->nesting >= 4)
		वापस शून्य;

	buffer->nesting++;

	/* Interrupts must see nesting incremented beक्रमe we use the buffer */
	barrier();
	वापस &buffer->buffer[buffer->nesting - 1][0];
पूर्ण

अटल व्योम put_trace_buf(व्योम)
अणु
	/* Don't let the decrement of nesting leak beक्रमe this */
	barrier();
	this_cpu_dec(trace_percpu_buffer->nesting);
पूर्ण

अटल पूर्णांक alloc_percpu_trace_buffer(व्योम)
अणु
	काष्ठा trace_buffer_काष्ठा *buffers;

	अगर (trace_percpu_buffer)
		वापस 0;

	buffers = alloc_percpu(काष्ठा trace_buffer_काष्ठा);
	अगर (MEM_FAIL(!buffers, "Could not allocate percpu trace_printk buffer"))
		वापस -ENOMEM;

	trace_percpu_buffer = buffers;
	वापस 0;
पूर्ण

अटल पूर्णांक buffers_allocated;

व्योम trace_prपूर्णांकk_init_buffers(व्योम)
अणु
	अगर (buffers_allocated)
		वापस;

	अगर (alloc_percpu_trace_buffer())
		वापस;

	/* trace_prपूर्णांकk() is क्रम debug use only. Don't use it in production. */

	pr_warn("\n");
	pr_warn("**********************************************************\n");
	pr_warn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pr_warn("**                                                      **\n");
	pr_warn("** trace_printk() being used. Allocating extra memory.  **\n");
	pr_warn("**                                                      **\n");
	pr_warn("** This means that this is a DEBUG kernel and it is     **\n");
	pr_warn("** unsafe for production use.                           **\n");
	pr_warn("**                                                      **\n");
	pr_warn("** If you see this message and you are not debugging    **\n");
	pr_warn("** the kernel, report this immediately to your vendor!  **\n");
	pr_warn("**                                                      **\n");
	pr_warn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pr_warn("**********************************************************\n");

	/* Expand the buffers to set size */
	tracing_update_buffers();

	buffers_allocated = 1;

	/*
	 * trace_prपूर्णांकk_init_buffers() can be called by modules.
	 * If that happens, then we need to start cmdline recording
	 * directly here. If the global_trace.buffer is alपढ़ोy
	 * allocated here, then this was called by module code.
	 */
	अगर (global_trace.array_buffer.buffer)
		tracing_start_cmdline_record();
पूर्ण
EXPORT_SYMBOL_GPL(trace_prपूर्णांकk_init_buffers);

व्योम trace_prपूर्णांकk_start_comm(व्योम)
अणु
	/* Start tracing comms अगर trace prपूर्णांकk is set */
	अगर (!buffers_allocated)
		वापस;
	tracing_start_cmdline_record();
पूर्ण

अटल व्योम trace_prपूर्णांकk_start_stop_comm(पूर्णांक enabled)
अणु
	अगर (!buffers_allocated)
		वापस;

	अगर (enabled)
		tracing_start_cmdline_record();
	अन्यथा
		tracing_stop_cmdline_record();
पूर्ण

/**
 * trace_vbprपूर्णांकk - ग_लिखो binary msg to tracing buffer
 * @ip:    The address of the caller
 * @fmt:   The string क्रमmat to ग_लिखो to the buffer
 * @args:  Arguments क्रम @fmt
 */
पूर्णांक trace_vbprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा trace_event_call *call = &event_bprपूर्णांक;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer;
	काष्ठा trace_array *tr = &global_trace;
	काष्ठा bprपूर्णांक_entry *entry;
	अचिन्हित पूर्णांक trace_ctx;
	अक्षर *tbuffer;
	पूर्णांक len = 0, size;

	अगर (unlikely(tracing_selftest_running || tracing_disabled))
		वापस 0;

	/* Don't pollute graph traces with trace_vprपूर्णांकk पूर्णांकernals */
	छोड़ो_graph_tracing();

	trace_ctx = tracing_gen_ctx();
	preempt_disable_notrace();

	tbuffer = get_trace_buf();
	अगर (!tbuffer) अणु
		len = 0;
		जाओ out_nobuffer;
	पूर्ण

	len = vbin_म_लिखो((u32 *)tbuffer, TRACE_BUF_SIZE/माप(पूर्णांक), fmt, args);

	अगर (len > TRACE_BUF_SIZE/माप(पूर्णांक) || len < 0)
		जाओ out_put;

	size = माप(*entry) + माप(u32) * len;
	buffer = tr->array_buffer.buffer;
	ring_buffer_nest_start(buffer);
	event = __trace_buffer_lock_reserve(buffer, TRACE_BPRINT, size,
					    trace_ctx);
	अगर (!event)
		जाओ out;
	entry = ring_buffer_event_data(event);
	entry->ip			= ip;
	entry->fmt			= fmt;

	स_नकल(entry->buf, tbuffer, माप(u32) * len);
	अगर (!call_filter_check_discard(call, entry, buffer, event)) अणु
		__buffer_unlock_commit(buffer, event);
		ftrace_trace_stack(tr, buffer, trace_ctx, 6, शून्य);
	पूर्ण

out:
	ring_buffer_nest_end(buffer);
out_put:
	put_trace_buf();

out_nobuffer:
	preempt_enable_notrace();
	unछोड़ो_graph_tracing();

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(trace_vbprपूर्णांकk);

__म_लिखो(3, 0)
अटल पूर्णांक
__trace_array_vprपूर्णांकk(काष्ठा trace_buffer *buffer,
		      अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा trace_event_call *call = &event_prपूर्णांक;
	काष्ठा ring_buffer_event *event;
	पूर्णांक len = 0, size;
	काष्ठा prपूर्णांक_entry *entry;
	अचिन्हित पूर्णांक trace_ctx;
	अक्षर *tbuffer;

	अगर (tracing_disabled || tracing_selftest_running)
		वापस 0;

	/* Don't pollute graph traces with trace_vprपूर्णांकk पूर्णांकernals */
	छोड़ो_graph_tracing();

	trace_ctx = tracing_gen_ctx();
	preempt_disable_notrace();


	tbuffer = get_trace_buf();
	अगर (!tbuffer) अणु
		len = 0;
		जाओ out_nobuffer;
	पूर्ण

	len = vscnम_लिखो(tbuffer, TRACE_BUF_SIZE, fmt, args);

	size = माप(*entry) + len + 1;
	ring_buffer_nest_start(buffer);
	event = __trace_buffer_lock_reserve(buffer, TRACE_PRINT, size,
					    trace_ctx);
	अगर (!event)
		जाओ out;
	entry = ring_buffer_event_data(event);
	entry->ip = ip;

	स_नकल(&entry->buf, tbuffer, len + 1);
	अगर (!call_filter_check_discard(call, entry, buffer, event)) अणु
		__buffer_unlock_commit(buffer, event);
		ftrace_trace_stack(&global_trace, buffer, trace_ctx, 6, शून्य);
	पूर्ण

out:
	ring_buffer_nest_end(buffer);
	put_trace_buf();

out_nobuffer:
	preempt_enable_notrace();
	unछोड़ो_graph_tracing();

	वापस len;
पूर्ण

__म_लिखो(3, 0)
पूर्णांक trace_array_vprपूर्णांकk(काष्ठा trace_array *tr,
			अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस __trace_array_vprपूर्णांकk(tr->array_buffer.buffer, ip, fmt, args);
पूर्ण

/**
 * trace_array_prपूर्णांकk - Prपूर्णांक a message to a specअगरic instance
 * @tr: The instance trace_array descriptor
 * @ip: The inकाष्ठाion poपूर्णांकer that this is called from.
 * @fmt: The क्रमmat to prपूर्णांक (म_लिखो क्रमmat)
 *
 * If a subप्रणाली sets up its own instance, they have the right to
 * prपूर्णांकk strings पूर्णांकo their tracing instance buffer using this
 * function. Note, this function will not ग_लिखो पूर्णांकo the top level
 * buffer (use trace_prपूर्णांकk() क्रम that), as writing पूर्णांकo the top level
 * buffer should only have events that can be inभागidually disabled.
 * trace_prपूर्णांकk() is only used क्रम debugging a kernel, and should not
 * be ever incorporated in normal use.
 *
 * trace_array_prपूर्णांकk() can be used, as it will not add noise to the
 * top level tracing buffer.
 *
 * Note, trace_array_init_prपूर्णांकk() must be called on @tr beक्रमe this
 * can be used.
 */
__म_लिखो(3, 0)
पूर्णांक trace_array_prपूर्णांकk(काष्ठा trace_array *tr,
		       अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret;
	बहु_सूची ap;

	अगर (!tr)
		वापस -ENOENT;

	/* This is only allowed क्रम created instances */
	अगर (tr == &global_trace)
		वापस 0;

	अगर (!(tr->trace_flags & TRACE_ITER_PRINTK))
		वापस 0;

	बहु_शुरू(ap, fmt);
	ret = trace_array_vprपूर्णांकk(tr, ip, fmt, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(trace_array_prपूर्णांकk);

/**
 * trace_array_init_prपूर्णांकk - Initialize buffers क्रम trace_array_prपूर्णांकk()
 * @tr: The trace array to initialize the buffers क्रम
 *
 * As trace_array_prपूर्णांकk() only ग_लिखोs पूर्णांकo instances, they are OK to
 * have in the kernel (unlike trace_prपूर्णांकk()). This needs to be called
 * beक्रमe trace_array_prपूर्णांकk() can be used on a trace_array.
 */
पूर्णांक trace_array_init_prपूर्णांकk(काष्ठा trace_array *tr)
अणु
	अगर (!tr)
		वापस -ENOENT;

	/* This is only allowed क्रम created instances */
	अगर (tr == &global_trace)
		वापस -EINVAL;

	वापस alloc_percpu_trace_buffer();
पूर्ण
EXPORT_SYMBOL_GPL(trace_array_init_prपूर्णांकk);

__म_लिखो(3, 4)
पूर्णांक trace_array_prपूर्णांकk_buf(काष्ठा trace_buffer *buffer,
			   अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret;
	बहु_सूची ap;

	अगर (!(global_trace.trace_flags & TRACE_ITER_PRINTK))
		वापस 0;

	बहु_शुरू(ap, fmt);
	ret = __trace_array_vprपूर्णांकk(buffer, ip, fmt, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण

__म_लिखो(2, 0)
पूर्णांक trace_vprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस trace_array_vprपूर्णांकk(&global_trace, ip, fmt, args);
पूर्ण
EXPORT_SYMBOL_GPL(trace_vprपूर्णांकk);

अटल व्योम trace_iterator_increment(काष्ठा trace_iterator *iter)
अणु
	काष्ठा ring_buffer_iter *buf_iter = trace_buffer_iter(iter, iter->cpu);

	iter->idx++;
	अगर (buf_iter)
		ring_buffer_iter_advance(buf_iter);
पूर्ण

अटल काष्ठा trace_entry *
peek_next_entry(काष्ठा trace_iterator *iter, पूर्णांक cpu, u64 *ts,
		अचिन्हित दीर्घ *lost_events)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा ring_buffer_iter *buf_iter = trace_buffer_iter(iter, cpu);

	अगर (buf_iter) अणु
		event = ring_buffer_iter_peek(buf_iter, ts);
		अगर (lost_events)
			*lost_events = ring_buffer_iter_dropped(buf_iter) ?
				(अचिन्हित दीर्घ)-1 : 0;
	पूर्ण अन्यथा अणु
		event = ring_buffer_peek(iter->array_buffer->buffer, cpu, ts,
					 lost_events);
	पूर्ण

	अगर (event) अणु
		iter->ent_size = ring_buffer_event_length(event);
		वापस ring_buffer_event_data(event);
	पूर्ण
	iter->ent_size = 0;
	वापस शून्य;
पूर्ण

अटल काष्ठा trace_entry *
__find_next_entry(काष्ठा trace_iterator *iter, पूर्णांक *ent_cpu,
		  अचिन्हित दीर्घ *missing_events, u64 *ent_ts)
अणु
	काष्ठा trace_buffer *buffer = iter->array_buffer->buffer;
	काष्ठा trace_entry *ent, *next = शून्य;
	अचिन्हित दीर्घ lost_events = 0, next_lost = 0;
	पूर्णांक cpu_file = iter->cpu_file;
	u64 next_ts = 0, ts;
	पूर्णांक next_cpu = -1;
	पूर्णांक next_size = 0;
	पूर्णांक cpu;

	/*
	 * If we are in a per_cpu trace file, करोn't bother by iterating over
	 * all cpu and peek directly.
	 */
	अगर (cpu_file > RING_BUFFER_ALL_CPUS) अणु
		अगर (ring_buffer_empty_cpu(buffer, cpu_file))
			वापस शून्य;
		ent = peek_next_entry(iter, cpu_file, ent_ts, missing_events);
		अगर (ent_cpu)
			*ent_cpu = cpu_file;

		वापस ent;
	पूर्ण

	क्रम_each_tracing_cpu(cpu) अणु

		अगर (ring_buffer_empty_cpu(buffer, cpu))
			जारी;

		ent = peek_next_entry(iter, cpu, &ts, &lost_events);

		/*
		 * Pick the entry with the smallest बारtamp:
		 */
		अगर (ent && (!next || ts < next_ts)) अणु
			next = ent;
			next_cpu = cpu;
			next_ts = ts;
			next_lost = lost_events;
			next_size = iter->ent_size;
		पूर्ण
	पूर्ण

	iter->ent_size = next_size;

	अगर (ent_cpu)
		*ent_cpu = next_cpu;

	अगर (ent_ts)
		*ent_ts = next_ts;

	अगर (missing_events)
		*missing_events = next_lost;

	वापस next;
पूर्ण

#घोषणा STATIC_FMT_BUF_SIZE	128
अटल अक्षर अटल_fmt_buf[STATIC_FMT_BUF_SIZE];

अटल अक्षर *trace_iter_expand_क्रमmat(काष्ठा trace_iterator *iter)
अणु
	अक्षर *पंचांगp;

	/*
	 * iter->tr is शून्य when used with tp_prपूर्णांकk, which makes
	 * this get called where it is not safe to call kपुनः_स्मृति().
	 */
	अगर (!iter->tr || iter->fmt == अटल_fmt_buf)
		वापस शून्य;

	पंचांगp = kपुनः_स्मृति(iter->fmt, iter->fmt_size + STATIC_FMT_BUF_SIZE,
		       GFP_KERNEL);
	अगर (पंचांगp) अणु
		iter->fmt_size += STATIC_FMT_BUF_SIZE;
		iter->fmt = पंचांगp;
	पूर्ण

	वापस पंचांगp;
पूर्ण

/* Returns true अगर the string is safe to dereference from an event */
अटल bool trace_safe_str(काष्ठा trace_iterator *iter, स्थिर अक्षर *str)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)str;
	काष्ठा trace_event *trace_event;
	काष्ठा trace_event_call *event;

	/* OK अगर part of the event data */
	अगर ((addr >= (अचिन्हित दीर्घ)iter->ent) &&
	    (addr < (अचिन्हित दीर्घ)iter->ent + iter->ent_size))
		वापस true;

	/* OK अगर part of the temp seq buffer */
	अगर ((addr >= (अचिन्हित दीर्घ)iter->पंचांगp_seq.buffer) &&
	    (addr < (अचिन्हित दीर्घ)iter->पंचांगp_seq.buffer + PAGE_SIZE))
		वापस true;

	/* Core rodata can not be मुक्तd */
	अगर (is_kernel_rodata(addr))
		वापस true;

	अगर (trace_is_tracepoपूर्णांक_string(str))
		वापस true;

	/*
	 * Now this could be a module event, referencing core module
	 * data, which is OK.
	 */
	अगर (!iter->ent)
		वापस false;

	trace_event = ftrace_find_event(iter->ent->type);
	अगर (!trace_event)
		वापस false;

	event = container_of(trace_event, काष्ठा trace_event_call, event);
	अगर (!event->mod)
		वापस false;

	/* Would rather have rodata, but this will suffice */
	अगर (within_module_core(addr, event->mod))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर अक्षर *show_buffer(काष्ठा trace_seq *s)
अणु
	काष्ठा seq_buf *seq = &s->seq;

	seq_buf_terminate(seq);

	वापस seq->buffer;
पूर्ण

अटल DEFINE_STATIC_KEY_FALSE(trace_no_verअगरy);

अटल पूर्णांक test_can_verअगरy_check(स्थिर अक्षर *fmt, ...)
अणु
	अक्षर buf[16];
	बहु_सूची ap;
	पूर्णांक ret;

	/*
	 * The verअगरier is dependent on vsnम_लिखो() modअगरies the बहु_सूची
	 * passed to it, where it is sent as a reference. Some architectures
	 * (like x86_32) passes it by value, which means that vsnम_लिखो()
	 * करोes not modअगरy the बहु_सूची passed to it, and the verअगरier
	 * would then need to be able to understand all the values that
	 * vsnम_लिखो can use. If it is passed by value, then the verअगरier
	 * is disabled.
	 */
	बहु_शुरू(ap, fmt);
	vsnम_लिखो(buf, 16, "%d", ap);
	ret = बहु_तर्क(ap, पूर्णांक);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण

अटल व्योम test_can_verअगरy(व्योम)
अणु
	अगर (!test_can_verअगरy_check("%d %d", 0, 1)) अणु
		pr_info("trace event string verifier disabled\n");
		अटल_branch_inc(&trace_no_verअगरy);
	पूर्ण
पूर्ण

/**
 * trace_check_भ_लिखो - Check dereferenced strings जबतक writing to the seq buffer
 * @iter: The iterator that holds the seq buffer and the event being prपूर्णांकed
 * @fmt: The क्रमmat used to prपूर्णांक the event
 * @ap: The बहु_सूची holding the data to prपूर्णांक from @fmt.
 *
 * This ग_लिखोs the data पूर्णांकo the @iter->seq buffer using the data from
 * @fmt and @ap. If the क्रमmat has a %s, then the source of the string
 * is examined to make sure it is safe to prपूर्णांक, otherwise it will
 * warn and prपूर्णांक "[UNSAFE MEMORY]" in place of the dereferenced string
 * poपूर्णांकer.
 */
व्योम trace_check_भ_लिखो(काष्ठा trace_iterator *iter, स्थिर अक्षर *fmt,
			 बहु_सूची ap)
अणु
	स्थिर अक्षर *p = fmt;
	स्थिर अक्षर *str;
	पूर्णांक i, j;

	अगर (WARN_ON_ONCE(!fmt))
		वापस;

	अगर (अटल_branch_unlikely(&trace_no_verअगरy))
		जाओ prपूर्णांक;

	/* Don't bother checking when करोing a ftrace_dump() */
	अगर (iter->fmt == अटल_fmt_buf)
		जाओ prपूर्णांक;

	जबतक (*p) अणु
		bool star = false;
		पूर्णांक len = 0;

		j = 0;

		/* We only care about %s and variants */
		क्रम (i = 0; p[i]; i++) अणु
			अगर (i + 1 >= iter->fmt_size) अणु
				/*
				 * If we can't expand the copy buffer,
				 * just prपूर्णांक it.
				 */
				अगर (!trace_iter_expand_क्रमmat(iter))
					जाओ prपूर्णांक;
			पूर्ण

			अगर (p[i] == '\\' && p[i+1]) अणु
				i++;
				जारी;
			पूर्ण
			अगर (p[i] == '%') अणु
				/* Need to test हालs like %08.*s */
				क्रम (j = 1; p[i+j]; j++) अणु
					अगर (है_अंक(p[i+j]) ||
					    p[i+j] == '.')
						जारी;
					अगर (p[i+j] == '*') अणु
						star = true;
						जारी;
					पूर्ण
					अवरोध;
				पूर्ण
				अगर (p[i+j] == 's')
					अवरोध;
				star = false;
			पूर्ण
			j = 0;
		पूर्ण
		/* If no %s found then just prपूर्णांक normally */
		अगर (!p[i])
			अवरोध;

		/* Copy up to the %s, and prपूर्णांक that */
		म_नकलन(iter->fmt, p, i);
		iter->fmt[i] = '\0';
		trace_seq_भ_लिखो(&iter->seq, iter->fmt, ap);

		अगर (star)
			len = बहु_तर्क(ap, पूर्णांक);

		/* The ap now poपूर्णांकs to the string data of the %s */
		str = बहु_तर्क(ap, स्थिर अक्षर *);

		/*
		 * If you hit this warning, it is likely that the
		 * trace event in question used %s on a string that
		 * was saved at the समय of the event, but may not be
		 * around when the trace is पढ़ो. Use __string(),
		 * __assign_str() and __get_str() helpers in the TRACE_EVENT()
		 * instead. See samples/trace_events/trace-events-sample.h
		 * क्रम reference.
		 */
		अगर (WARN_ONCE(!trace_safe_str(iter, str),
			      "fmt: '%s' current_buffer: '%s'",
			      fmt, show_buffer(&iter->seq))) अणु
			पूर्णांक ret;

			/* Try to safely पढ़ो the string */
			अगर (star) अणु
				अगर (len + 1 > iter->fmt_size)
					len = iter->fmt_size - 1;
				अगर (len < 0)
					len = 0;
				ret = copy_from_kernel_nofault(iter->fmt, str, len);
				iter->fmt[len] = 0;
				star = false;
			पूर्ण अन्यथा अणु
				ret = म_नकलन_from_kernel_nofault(iter->fmt, str,
								  iter->fmt_size);
			पूर्ण
			अगर (ret < 0)
				trace_seq_म_लिखो(&iter->seq, "(0x%px)", str);
			अन्यथा
				trace_seq_म_लिखो(&iter->seq, "(0x%px:%s)",
						 str, iter->fmt);
			str = "[UNSAFE-MEMORY]";
			म_नकल(iter->fmt, "%s");
		पूर्ण अन्यथा अणु
			म_नकलन(iter->fmt, p + i, j + 1);
			iter->fmt[j+1] = '\0';
		पूर्ण
		अगर (star)
			trace_seq_म_लिखो(&iter->seq, iter->fmt, len, str);
		अन्यथा
			trace_seq_म_लिखो(&iter->seq, iter->fmt, str);

		p += i + j + 1;
	पूर्ण
 prपूर्णांक:
	अगर (*p)
		trace_seq_भ_लिखो(&iter->seq, p, ap);
पूर्ण

स्थिर अक्षर *trace_event_क्रमmat(काष्ठा trace_iterator *iter, स्थिर अक्षर *fmt)
अणु
	स्थिर अक्षर *p, *new_fmt;
	अक्षर *q;

	अगर (WARN_ON_ONCE(!fmt))
		वापस fmt;

	अगर (!iter->tr || iter->tr->trace_flags & TRACE_ITER_HASH_PTR)
		वापस fmt;

	p = fmt;
	new_fmt = q = iter->fmt;
	जबतक (*p) अणु
		अगर (unlikely(q - new_fmt + 3 > iter->fmt_size)) अणु
			अगर (!trace_iter_expand_क्रमmat(iter))
				वापस fmt;

			q += iter->fmt - new_fmt;
			new_fmt = iter->fmt;
		पूर्ण

		*q++ = *p++;

		/* Replace %p with %px */
		अगर (p[-1] == '%') अणु
			अगर (p[0] == '%') अणु
				*q++ = *p++;
			पूर्ण अन्यथा अगर (p[0] == 'p' && !है_अक्षर_अंक(p[1])) अणु
				*q++ = *p++;
				*q++ = 'x';
			पूर्ण
		पूर्ण
	पूर्ण
	*q = '\0';

	वापस new_fmt;
पूर्ण

#घोषणा STATIC_TEMP_BUF_SIZE	128
अटल अक्षर अटल_temp_buf[STATIC_TEMP_BUF_SIZE] __aligned(4);

/* Find the next real entry, without updating the iterator itself */
काष्ठा trace_entry *trace_find_next_entry(काष्ठा trace_iterator *iter,
					  पूर्णांक *ent_cpu, u64 *ent_ts)
अणु
	/* __find_next_entry will reset ent_size */
	पूर्णांक ent_size = iter->ent_size;
	काष्ठा trace_entry *entry;

	/*
	 * If called from ftrace_dump(), then the iter->temp buffer
	 * will be the अटल_temp_buf and not created from kदो_स्मृति.
	 * If the entry size is greater than the buffer, we can
	 * not save it. Just वापस शून्य in that हाल. This is only
	 * used to add markers when two consecutive events' समय
	 * stamps have a large delta. See trace_prपूर्णांक_lat_context()
	 */
	अगर (iter->temp == अटल_temp_buf &&
	    STATIC_TEMP_BUF_SIZE < ent_size)
		वापस शून्य;

	/*
	 * The __find_next_entry() may call peek_next_entry(), which may
	 * call ring_buffer_peek() that may make the contents of iter->ent
	 * undefined. Need to copy iter->ent now.
	 */
	अगर (iter->ent && iter->ent != iter->temp) अणु
		अगर ((!iter->temp || iter->temp_size < iter->ent_size) &&
		    !WARN_ON_ONCE(iter->temp == अटल_temp_buf)) अणु
			व्योम *temp;
			temp = kदो_स्मृति(iter->ent_size, GFP_KERNEL);
			अगर (!temp)
				वापस शून्य;
			kमुक्त(iter->temp);
			iter->temp = temp;
			iter->temp_size = iter->ent_size;
		पूर्ण
		स_नकल(iter->temp, iter->ent, iter->ent_size);
		iter->ent = iter->temp;
	पूर्ण
	entry = __find_next_entry(iter, ent_cpu, शून्य, ent_ts);
	/* Put back the original ent_size */
	iter->ent_size = ent_size;

	वापस entry;
पूर्ण

/* Find the next real entry, and increment the iterator to the next entry */
व्योम *trace_find_next_entry_inc(काष्ठा trace_iterator *iter)
अणु
	iter->ent = __find_next_entry(iter, &iter->cpu,
				      &iter->lost_events, &iter->ts);

	अगर (iter->ent)
		trace_iterator_increment(iter);

	वापस iter->ent ? iter : शून्य;
पूर्ण

अटल व्योम trace_consume(काष्ठा trace_iterator *iter)
अणु
	ring_buffer_consume(iter->array_buffer->buffer, iter->cpu, &iter->ts,
			    &iter->lost_events);
पूर्ण

अटल व्योम *s_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_iterator *iter = m->निजी;
	पूर्णांक i = (पूर्णांक)*pos;
	व्योम *ent;

	WARN_ON_ONCE(iter->leftover);

	(*pos)++;

	/* can't go backwards */
	अगर (iter->idx > i)
		वापस शून्य;

	अगर (iter->idx < 0)
		ent = trace_find_next_entry_inc(iter);
	अन्यथा
		ent = iter;

	जबतक (ent && iter->idx < i)
		ent = trace_find_next_entry_inc(iter);

	iter->pos = *pos;

	वापस ent;
पूर्ण

व्योम tracing_iter_reset(काष्ठा trace_iterator *iter, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_iter *buf_iter;
	अचिन्हित दीर्घ entries = 0;
	u64 ts;

	per_cpu_ptr(iter->array_buffer->data, cpu)->skipped_entries = 0;

	buf_iter = trace_buffer_iter(iter, cpu);
	अगर (!buf_iter)
		वापस;

	ring_buffer_iter_reset(buf_iter);

	/*
	 * We could have the हाल with the max latency tracers
	 * that a reset never took place on a cpu. This is evident
	 * by the बारtamp being beक्रमe the start of the buffer.
	 */
	जबतक (ring_buffer_iter_peek(buf_iter, &ts)) अणु
		अगर (ts >= iter->array_buffer->समय_start)
			अवरोध;
		entries++;
		ring_buffer_iter_advance(buf_iter);
	पूर्ण

	per_cpu_ptr(iter->array_buffer->data, cpu)->skipped_entries = entries;
पूर्ण

/*
 * The current tracer is copied to aव्योम a global locking
 * all around.
 */
अटल व्योम *s_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा trace_iterator *iter = m->निजी;
	काष्ठा trace_array *tr = iter->tr;
	पूर्णांक cpu_file = iter->cpu_file;
	व्योम *p = शून्य;
	loff_t l = 0;
	पूर्णांक cpu;

	/*
	 * copy the tracer to aव्योम using a global lock all around.
	 * iter->trace is a copy of current_trace, the poपूर्णांकer to the
	 * name may be used instead of a म_भेद(), as iter->trace->name
	 * will poपूर्णांक to the same string as current_trace->name.
	 */
	mutex_lock(&trace_types_lock);
	अगर (unlikely(tr->current_trace && iter->trace->name != tr->current_trace->name))
		*iter->trace = *tr->current_trace;
	mutex_unlock(&trace_types_lock);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (iter->snapshot && iter->trace->use_max_tr)
		वापस ERR_PTR(-EBUSY);
#पूर्ण_अगर

	अगर (*pos != iter->pos) अणु
		iter->ent = शून्य;
		iter->cpu = 0;
		iter->idx = -1;

		अगर (cpu_file == RING_BUFFER_ALL_CPUS) अणु
			क्रम_each_tracing_cpu(cpu)
				tracing_iter_reset(iter, cpu);
		पूर्ण अन्यथा
			tracing_iter_reset(iter, cpu_file);

		iter->leftover = 0;
		क्रम (p = iter; p && l < *pos; p = s_next(m, p, &l))
			;

	पूर्ण अन्यथा अणु
		/*
		 * If we overflowed the seq_file beक्रमe, then we want
		 * to just reuse the trace_seq buffer again.
		 */
		अगर (iter->leftover)
			p = iter;
		अन्यथा अणु
			l = *pos - 1;
			p = s_next(m, p, &l);
		पूर्ण
	पूर्ण

	trace_event_पढ़ो_lock();
	trace_access_lock(cpu_file);
	वापस p;
पूर्ण

अटल व्योम s_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा trace_iterator *iter = m->निजी;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (iter->snapshot && iter->trace->use_max_tr)
		वापस;
#पूर्ण_अगर

	trace_access_unlock(iter->cpu_file);
	trace_event_पढ़ो_unlock();
पूर्ण

अटल व्योम
get_total_entries_cpu(काष्ठा array_buffer *buf, अचिन्हित दीर्घ *total,
		      अचिन्हित दीर्घ *entries, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ count;

	count = ring_buffer_entries_cpu(buf->buffer, cpu);
	/*
	 * If this buffer has skipped entries, then we hold all
	 * entries क्रम the trace and we need to ignore the
	 * ones beक्रमe the समय stamp.
	 */
	अगर (per_cpu_ptr(buf->data, cpu)->skipped_entries) अणु
		count -= per_cpu_ptr(buf->data, cpu)->skipped_entries;
		/* total is the same as the entries */
		*total = count;
	पूर्ण अन्यथा
		*total = count +
			ring_buffer_overrun_cpu(buf->buffer, cpu);
	*entries = count;
पूर्ण

अटल व्योम
get_total_entries(काष्ठा array_buffer *buf,
		  अचिन्हित दीर्घ *total, अचिन्हित दीर्घ *entries)
अणु
	अचिन्हित दीर्घ t, e;
	पूर्णांक cpu;

	*total = 0;
	*entries = 0;

	क्रम_each_tracing_cpu(cpu) अणु
		get_total_entries_cpu(buf, &t, &e, cpu);
		*total += t;
		*entries += e;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ trace_total_entries_cpu(काष्ठा trace_array *tr, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ total, entries;

	अगर (!tr)
		tr = &global_trace;

	get_total_entries_cpu(&tr->array_buffer, &total, &entries, cpu);

	वापस entries;
पूर्ण

अचिन्हित दीर्घ trace_total_entries(काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ total, entries;

	अगर (!tr)
		tr = &global_trace;

	get_total_entries(&tr->array_buffer, &total, &entries);

	वापस entries;
पूर्ण

अटल व्योम prपूर्णांक_lat_help_header(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "#                    _------=> CPU#            \n"
		    "#                   / _-----=> irqs-off        \n"
		    "#                  | / _----=> need-resched    \n"
		    "#                  || / _---=> hardirq/softirq \n"
		    "#                  ||| / _--=> preempt-depth   \n"
		    "#                  |||| /     delay            \n"
		    "#  cmd     pid     ||||| time  |   caller      \n"
		    "#     \\   /        |||||  \\    |   /         \n");
पूर्ण

अटल व्योम prपूर्णांक_event_info(काष्ठा array_buffer *buf, काष्ठा seq_file *m)
अणु
	अचिन्हित दीर्घ total;
	अचिन्हित दीर्घ entries;

	get_total_entries(buf, &total, &entries);
	seq_म_लिखो(m, "# entries-in-buffer/entries-written: %lu/%lu   #P:%d\n",
		   entries, total, num_online_cpus());
	seq_माला_दो(m, "#\n");
पूर्ण

अटल व्योम prपूर्णांक_func_help_header(काष्ठा array_buffer *buf, काष्ठा seq_file *m,
				   अचिन्हित पूर्णांक flags)
अणु
	bool tgid = flags & TRACE_ITER_RECORD_TGID;

	prपूर्णांक_event_info(buf, m);

	seq_म_लिखो(m, "#           TASK-PID    %s CPU#     TIMESTAMP  FUNCTION\n", tgid ? "   TGID   " : "");
	seq_म_लिखो(m, "#              | |      %s   |         |         |\n",      tgid ? "     |    " : "");
पूर्ण

अटल व्योम prपूर्णांक_func_help_header_irq(काष्ठा array_buffer *buf, काष्ठा seq_file *m,
				       अचिन्हित पूर्णांक flags)
अणु
	bool tgid = flags & TRACE_ITER_RECORD_TGID;
	स्थिर अक्षर *space = "            ";
	पूर्णांक prec = tgid ? 12 : 2;

	prपूर्णांक_event_info(buf, m);

	seq_म_लिखो(m, "#                            %.*s  _-----=> irqs-off\n", prec, space);
	seq_म_लिखो(m, "#                            %.*s / _----=> need-resched\n", prec, space);
	seq_म_लिखो(m, "#                            %.*s| / _---=> hardirq/softirq\n", prec, space);
	seq_म_लिखो(m, "#                            %.*s|| / _--=> preempt-depth\n", prec, space);
	seq_म_लिखो(m, "#                            %.*s||| /     delay\n", prec, space);
	seq_म_लिखो(m, "#           TASK-PID  %.*s CPU#  ||||   TIMESTAMP  FUNCTION\n", prec, "     TGID   ");
	seq_म_लिखो(m, "#              | |    %.*s   |   ||||      |         |\n", prec, "       |    ");
पूर्ण

व्योम
prपूर्णांक_trace_header(काष्ठा seq_file *m, काष्ठा trace_iterator *iter)
अणु
	अचिन्हित दीर्घ sym_flags = (global_trace.trace_flags & TRACE_ITER_SYM_MASK);
	काष्ठा array_buffer *buf = iter->array_buffer;
	काष्ठा trace_array_cpu *data = per_cpu_ptr(buf->data, buf->cpu);
	काष्ठा tracer *type = iter->trace;
	अचिन्हित दीर्घ entries;
	अचिन्हित दीर्घ total;
	स्थिर अक्षर *name = "preemption";

	name = type->name;

	get_total_entries(buf, &total, &entries);

	seq_म_लिखो(m, "# %s latency trace v1.1.5 on %s\n",
		   name, UTS_RELEASE);
	seq_माला_दो(m, "# -----------------------------------"
		 "---------------------------------\n");
	seq_म_लिखो(m, "# latency: %lu us, #%lu/%lu, CPU#%d |"
		   " (M:%s VP:%d, KP:%d, SP:%d HP:%d",
		   nsecs_to_usecs(data->saved_latency),
		   entries,
		   total,
		   buf->cpu,
#अगर defined(CONFIG_PREEMPT_NONE)
		   "server",
#या_अगर defined(CONFIG_PREEMPT_VOLUNTARY)
		   "desktop",
#या_अगर defined(CONFIG_PREEMPT)
		   "preempt",
#या_अगर defined(CONFIG_PREEMPT_RT)
		   "preempt_rt",
#अन्यथा
		   "unknown",
#पूर्ण_अगर
		   /* These are reserved क्रम later use */
		   0, 0, 0, 0);
#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(m, " #P:%d)\n", num_online_cpus());
#अन्यथा
	seq_माला_दो(m, ")\n");
#पूर्ण_अगर
	seq_माला_दो(m, "#    -----------------\n");
	seq_म_लिखो(m, "#    | task: %.16s-%d "
		   "(uid:%d nice:%ld policy:%ld rt_prio:%ld)\n",
		   data->comm, data->pid,
		   from_kuid_munged(seq_user_ns(m), data->uid), data->nice,
		   data->policy, data->rt_priority);
	seq_माला_दो(m, "#    -----------------\n");

	अगर (data->critical_start) अणु
		seq_माला_दो(m, "#  => started at: ");
		seq_prपूर्णांक_ip_sym(&iter->seq, data->critical_start, sym_flags);
		trace_prपूर्णांक_seq(m, &iter->seq);
		seq_माला_दो(m, "\n#  => ended at:   ");
		seq_prपूर्णांक_ip_sym(&iter->seq, data->critical_end, sym_flags);
		trace_prपूर्णांक_seq(m, &iter->seq);
		seq_माला_दो(m, "\n#\n");
	पूर्ण

	seq_माला_दो(m, "#\n");
पूर्ण

अटल व्योम test_cpu_buff_start(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_array *tr = iter->tr;

	अगर (!(tr->trace_flags & TRACE_ITER_ANNOTATE))
		वापस;

	अगर (!(iter->iter_flags & TRACE_खाता_ANNOTATE))
		वापस;

	अगर (cpumask_available(iter->started) &&
	    cpumask_test_cpu(iter->cpu, iter->started))
		वापस;

	अगर (per_cpu_ptr(iter->array_buffer->data, iter->cpu)->skipped_entries)
		वापस;

	अगर (cpumask_available(iter->started))
		cpumask_set_cpu(iter->cpu, iter->started);

	/* Don't prपूर्णांक started cpu buffer क्रम the first entry of the trace */
	अगर (iter->idx > 1)
		trace_seq_म_लिखो(s, "##### CPU %u buffer started ####\n",
				iter->cpu);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t prपूर्णांक_trace_fmt(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	अचिन्हित दीर्घ sym_flags = (tr->trace_flags & TRACE_ITER_SYM_MASK);
	काष्ठा trace_entry *entry;
	काष्ठा trace_event *event;

	entry = iter->ent;

	test_cpu_buff_start(iter);

	event = ftrace_find_event(entry->type);

	अगर (tr->trace_flags & TRACE_ITER_CONTEXT_INFO) अणु
		अगर (iter->iter_flags & TRACE_खाता_LAT_FMT)
			trace_prपूर्णांक_lat_context(iter);
		अन्यथा
			trace_prपूर्णांक_context(iter);
	पूर्ण

	अगर (trace_seq_has_overflowed(s))
		वापस TRACE_TYPE_PARTIAL_LINE;

	अगर (event)
		वापस event->funcs->trace(iter, sym_flags, event);

	trace_seq_म_लिखो(s, "Unknown type %d\n", entry->type);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t prपूर्णांक_raw_fmt(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *entry;
	काष्ठा trace_event *event;

	entry = iter->ent;

	अगर (tr->trace_flags & TRACE_ITER_CONTEXT_INFO)
		trace_seq_म_लिखो(s, "%d %d %llu ",
				 entry->pid, iter->cpu, iter->ts);

	अगर (trace_seq_has_overflowed(s))
		वापस TRACE_TYPE_PARTIAL_LINE;

	event = ftrace_find_event(entry->type);
	अगर (event)
		वापस event->funcs->raw(iter, 0, event);

	trace_seq_म_लिखो(s, "%d ?\n", entry->type);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t prपूर्णांक_hex_fmt(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	अचिन्हित अक्षर newline = '\n';
	काष्ठा trace_entry *entry;
	काष्ठा trace_event *event;

	entry = iter->ent;

	अगर (tr->trace_flags & TRACE_ITER_CONTEXT_INFO) अणु
		SEQ_PUT_HEX_FIELD(s, entry->pid);
		SEQ_PUT_HEX_FIELD(s, iter->cpu);
		SEQ_PUT_HEX_FIELD(s, iter->ts);
		अगर (trace_seq_has_overflowed(s))
			वापस TRACE_TYPE_PARTIAL_LINE;
	पूर्ण

	event = ftrace_find_event(entry->type);
	अगर (event) अणु
		क्रमागत prपूर्णांक_line_t ret = event->funcs->hex(iter, 0, event);
		अगर (ret != TRACE_TYPE_HANDLED)
			वापस ret;
	पूर्ण

	SEQ_PUT_FIELD(s, newline);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t prपूर्णांक_bin_fmt(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *entry;
	काष्ठा trace_event *event;

	entry = iter->ent;

	अगर (tr->trace_flags & TRACE_ITER_CONTEXT_INFO) अणु
		SEQ_PUT_FIELD(s, entry->pid);
		SEQ_PUT_FIELD(s, iter->cpu);
		SEQ_PUT_FIELD(s, iter->ts);
		अगर (trace_seq_has_overflowed(s))
			वापस TRACE_TYPE_PARTIAL_LINE;
	पूर्ण

	event = ftrace_find_event(entry->type);
	वापस event ? event->funcs->binary(iter, 0, event) :
		TRACE_TYPE_HANDLED;
पूर्ण

पूर्णांक trace_empty(काष्ठा trace_iterator *iter)
अणु
	काष्ठा ring_buffer_iter *buf_iter;
	पूर्णांक cpu;

	/* If we are looking at one CPU buffer, only check that one */
	अगर (iter->cpu_file != RING_BUFFER_ALL_CPUS) अणु
		cpu = iter->cpu_file;
		buf_iter = trace_buffer_iter(iter, cpu);
		अगर (buf_iter) अणु
			अगर (!ring_buffer_iter_empty(buf_iter))
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!ring_buffer_empty_cpu(iter->array_buffer->buffer, cpu))
				वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	क्रम_each_tracing_cpu(cpu) अणु
		buf_iter = trace_buffer_iter(iter, cpu);
		अगर (buf_iter) अणु
			अगर (!ring_buffer_iter_empty(buf_iter))
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!ring_buffer_empty_cpu(iter->array_buffer->buffer, cpu))
				वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/*  Called with trace_event_पढ़ो_lock() held. */
क्रमागत prपूर्णांक_line_t prपूर्णांक_trace_line(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_array *tr = iter->tr;
	अचिन्हित दीर्घ trace_flags = tr->trace_flags;
	क्रमागत prपूर्णांक_line_t ret;

	अगर (iter->lost_events) अणु
		अगर (iter->lost_events == (अचिन्हित दीर्घ)-1)
			trace_seq_म_लिखो(&iter->seq, "CPU:%d [LOST EVENTS]\n",
					 iter->cpu);
		अन्यथा
			trace_seq_म_लिखो(&iter->seq, "CPU:%d [LOST %lu EVENTS]\n",
					 iter->cpu, iter->lost_events);
		अगर (trace_seq_has_overflowed(&iter->seq))
			वापस TRACE_TYPE_PARTIAL_LINE;
	पूर्ण

	अगर (iter->trace && iter->trace->prपूर्णांक_line) अणु
		ret = iter->trace->prपूर्णांक_line(iter);
		अगर (ret != TRACE_TYPE_UNHANDLED)
			वापस ret;
	पूर्ण

	अगर (iter->ent->type == TRACE_BPUTS &&
			trace_flags & TRACE_ITER_PRINTK &&
			trace_flags & TRACE_ITER_PRINTK_MSGONLY)
		वापस trace_prपूर्णांक_bमाला_दो_msg_only(iter);

	अगर (iter->ent->type == TRACE_BPRINT &&
			trace_flags & TRACE_ITER_PRINTK &&
			trace_flags & TRACE_ITER_PRINTK_MSGONLY)
		वापस trace_prपूर्णांक_bprपूर्णांकk_msg_only(iter);

	अगर (iter->ent->type == TRACE_PRINT &&
			trace_flags & TRACE_ITER_PRINTK &&
			trace_flags & TRACE_ITER_PRINTK_MSGONLY)
		वापस trace_prपूर्णांक_prपूर्णांकk_msg_only(iter);

	अगर (trace_flags & TRACE_ITER_BIN)
		वापस prपूर्णांक_bin_fmt(iter);

	अगर (trace_flags & TRACE_ITER_HEX)
		वापस prपूर्णांक_hex_fmt(iter);

	अगर (trace_flags & TRACE_ITER_RAW)
		वापस prपूर्णांक_raw_fmt(iter);

	वापस prपूर्णांक_trace_fmt(iter);
पूर्ण

व्योम trace_latency_header(काष्ठा seq_file *m)
अणु
	काष्ठा trace_iterator *iter = m->निजी;
	काष्ठा trace_array *tr = iter->tr;

	/* prपूर्णांक nothing अगर the buffers are empty */
	अगर (trace_empty(iter))
		वापस;

	अगर (iter->iter_flags & TRACE_खाता_LAT_FMT)
		prपूर्णांक_trace_header(m, iter);

	अगर (!(tr->trace_flags & TRACE_ITER_VERBOSE))
		prपूर्णांक_lat_help_header(m);
पूर्ण

व्योम trace_शेष_header(काष्ठा seq_file *m)
अणु
	काष्ठा trace_iterator *iter = m->निजी;
	काष्ठा trace_array *tr = iter->tr;
	अचिन्हित दीर्घ trace_flags = tr->trace_flags;

	अगर (!(trace_flags & TRACE_ITER_CONTEXT_INFO))
		वापस;

	अगर (iter->iter_flags & TRACE_खाता_LAT_FMT) अणु
		/* prपूर्णांक nothing अगर the buffers are empty */
		अगर (trace_empty(iter))
			वापस;
		prपूर्णांक_trace_header(m, iter);
		अगर (!(trace_flags & TRACE_ITER_VERBOSE))
			prपूर्णांक_lat_help_header(m);
	पूर्ण अन्यथा अणु
		अगर (!(trace_flags & TRACE_ITER_VERBOSE)) अणु
			अगर (trace_flags & TRACE_ITER_IRQ_INFO)
				prपूर्णांक_func_help_header_irq(iter->array_buffer,
							   m, trace_flags);
			अन्यथा
				prपूर्णांक_func_help_header(iter->array_buffer, m,
						       trace_flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम test_ftrace_alive(काष्ठा seq_file *m)
अणु
	अगर (!ftrace_is_dead())
		वापस;
	seq_माला_दो(m, "# WARNING: FUNCTION TRACING IS CORRUPTED\n"
		    "#          MAY BE MISSING FUNCTION EVENTS\n");
पूर्ण

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
अटल व्योम show_snapshot_मुख्य_help(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "# echo 0 > snapshot : Clears and frees snapshot buffer\n"
		    "# echo 1 > snapshot : Allocates snapshot buffer, if not already allocated.\n"
		    "#                      Takes a snapshot of the main buffer.\n"
		    "# echo 2 > snapshot : Clears snapshot buffer (but does not allocate or free)\n"
		    "#                      (Doesn't have to be '2' works with any number that\n"
		    "#                       is not a '0' or '1')\n");
पूर्ण

अटल व्योम show_snapshot_percpu_help(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "# echo 0 > snapshot : Invalid for per_cpu snapshot file.\n");
#अगर_घोषित CONFIG_RING_BUFFER_ALLOW_SWAP
	seq_माला_दो(m, "# echo 1 > snapshot : Allocates snapshot buffer, if not already allocated.\n"
		    "#                      Takes a snapshot of the main buffer for this cpu.\n");
#अन्यथा
	seq_माला_दो(m, "# echo 1 > snapshot : Not supported with this kernel.\n"
		    "#                     Must use main snapshot file to allocate.\n");
#पूर्ण_अगर
	seq_माला_दो(m, "# echo 2 > snapshot : Clears this cpu's snapshot buffer (but does not allocate)\n"
		    "#                      (Doesn't have to be '2' works with any number that\n"
		    "#                       is not a '0' or '1')\n");
पूर्ण

अटल व्योम prपूर्णांक_snapshot_help(काष्ठा seq_file *m, काष्ठा trace_iterator *iter)
अणु
	अगर (iter->tr->allocated_snapshot)
		seq_माला_दो(m, "#\n# * Snapshot is allocated *\n#\n");
	अन्यथा
		seq_माला_दो(m, "#\n# * Snapshot is freed *\n#\n");

	seq_माला_दो(m, "# Snapshot commands:\n");
	अगर (iter->cpu_file == RING_BUFFER_ALL_CPUS)
		show_snapshot_मुख्य_help(m);
	अन्यथा
		show_snapshot_percpu_help(m);
पूर्ण
#अन्यथा
/* Should never be called */
अटल अंतरभूत व्योम prपूर्णांक_snapshot_help(काष्ठा seq_file *m, काष्ठा trace_iterator *iter) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा trace_iterator *iter = v;
	पूर्णांक ret;

	अगर (iter->ent == शून्य) अणु
		अगर (iter->tr) अणु
			seq_म_लिखो(m, "# tracer: %s\n", iter->trace->name);
			seq_माला_दो(m, "#\n");
			test_ftrace_alive(m);
		पूर्ण
		अगर (iter->snapshot && trace_empty(iter))
			prपूर्णांक_snapshot_help(m, iter);
		अन्यथा अगर (iter->trace && iter->trace->prपूर्णांक_header)
			iter->trace->prपूर्णांक_header(m);
		अन्यथा
			trace_शेष_header(m);

	पूर्ण अन्यथा अगर (iter->leftover) अणु
		/*
		 * If we filled the seq_file buffer earlier, we
		 * want to just show it now.
		 */
		ret = trace_prपूर्णांक_seq(m, &iter->seq);

		/* ret should this समय be zero, but you never know */
		iter->leftover = ret;

	पूर्ण अन्यथा अणु
		prपूर्णांक_trace_line(iter);
		ret = trace_prपूर्णांक_seq(m, &iter->seq);
		/*
		 * If we overflow the seq_file buffer, then it will
		 * ask us क्रम this data again at start up.
		 * Use that instead.
		 *  ret is 0 अगर seq_file ग_लिखो succeeded.
		 *        -1 otherwise.
		 */
		iter->leftover = ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Should be used after trace_array_get(), trace_types_lock
 * ensures that i_cdev was alपढ़ोy initialized.
 */
अटल अंतरभूत पूर्णांक tracing_get_cpu(काष्ठा inode *inode)
अणु
	अगर (inode->i_cdev) /* See trace_create_cpu_file() */
		वापस (दीर्घ)inode->i_cdev - 1;
	वापस RING_BUFFER_ALL_CPUS;
पूर्ण

अटल स्थिर काष्ठा seq_operations tracer_seq_ops = अणु
	.start		= s_start,
	.next		= s_next,
	.stop		= s_stop,
	.show		= s_show,
पूर्ण;

अटल काष्ठा trace_iterator *
__tracing_खोलो(काष्ठा inode *inode, काष्ठा file *file, bool snapshot)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा trace_iterator *iter;
	पूर्णांक cpu;

	अगर (tracing_disabled)
		वापस ERR_PTR(-ENODEV);

	iter = __seq_खोलो_निजी(file, &tracer_seq_ops, माप(*iter));
	अगर (!iter)
		वापस ERR_PTR(-ENOMEM);

	iter->buffer_iter = kसुस्मृति(nr_cpu_ids, माप(*iter->buffer_iter),
				    GFP_KERNEL);
	अगर (!iter->buffer_iter)
		जाओ release;

	/*
	 * trace_find_next_entry() may need to save off iter->ent.
	 * It will place it पूर्णांकo the iter->temp buffer. As most
	 * events are less than 128, allocate a buffer of that size.
	 * If one is greater, then trace_find_next_entry() will
	 * allocate a new buffer to adjust क्रम the bigger iter->ent.
	 * It's not critical अगर it fails to get allocated here.
	 */
	iter->temp = kदो_स्मृति(128, GFP_KERNEL);
	अगर (iter->temp)
		iter->temp_size = 128;

	/*
	 * trace_event_म_लिखो() may need to modअगरy given क्रमmat
	 * string to replace %p with %px so that it shows real address
	 * instead of hash value. However, that is only क्रम the event
	 * tracing, other tracer may not need. Defer the allocation
	 * until it is needed.
	 */
	iter->fmt = शून्य;
	iter->fmt_size = 0;

	/*
	 * We make a copy of the current tracer to aव्योम concurrent
	 * changes on it जबतक we are पढ़ोing.
	 */
	mutex_lock(&trace_types_lock);
	iter->trace = kzalloc(माप(*iter->trace), GFP_KERNEL);
	अगर (!iter->trace)
		जाओ fail;

	*iter->trace = *tr->current_trace;

	अगर (!zalloc_cpumask_var(&iter->started, GFP_KERNEL))
		जाओ fail;

	iter->tr = tr;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	/* Currently only the top directory has a snapshot */
	अगर (tr->current_trace->prपूर्णांक_max || snapshot)
		iter->array_buffer = &tr->max_buffer;
	अन्यथा
#पूर्ण_अगर
		iter->array_buffer = &tr->array_buffer;
	iter->snapshot = snapshot;
	iter->pos = -1;
	iter->cpu_file = tracing_get_cpu(inode);
	mutex_init(&iter->mutex);

	/* Notअगरy the tracer early; beक्रमe we stop tracing. */
	अगर (iter->trace->खोलो)
		iter->trace->खोलो(iter);

	/* Annotate start of buffers अगर we had overruns */
	अगर (ring_buffer_overruns(iter->array_buffer->buffer))
		iter->iter_flags |= TRACE_खाता_ANNOTATE;

	/* Output in nanoseconds only अगर we are using a घड़ी in nanoseconds. */
	अगर (trace_घड़ीs[tr->घड़ी_id].in_ns)
		iter->iter_flags |= TRACE_खाता_TIME_IN_NS;

	/*
	 * If छोड़ो-on-trace is enabled, then stop the trace जबतक
	 * dumping, unless this is the "snapshot" file
	 */
	अगर (!iter->snapshot && (tr->trace_flags & TRACE_ITER_PAUSE_ON_TRACE))
		tracing_stop_tr(tr);

	अगर (iter->cpu_file == RING_BUFFER_ALL_CPUS) अणु
		क्रम_each_tracing_cpu(cpu) अणु
			iter->buffer_iter[cpu] =
				ring_buffer_पढ़ो_prepare(iter->array_buffer->buffer,
							 cpu, GFP_KERNEL);
		पूर्ण
		ring_buffer_पढ़ो_prepare_sync();
		क्रम_each_tracing_cpu(cpu) अणु
			ring_buffer_पढ़ो_start(iter->buffer_iter[cpu]);
			tracing_iter_reset(iter, cpu);
		पूर्ण
	पूर्ण अन्यथा अणु
		cpu = iter->cpu_file;
		iter->buffer_iter[cpu] =
			ring_buffer_पढ़ो_prepare(iter->array_buffer->buffer,
						 cpu, GFP_KERNEL);
		ring_buffer_पढ़ो_prepare_sync();
		ring_buffer_पढ़ो_start(iter->buffer_iter[cpu]);
		tracing_iter_reset(iter, cpu);
	पूर्ण

	mutex_unlock(&trace_types_lock);

	वापस iter;

 fail:
	mutex_unlock(&trace_types_lock);
	kमुक्त(iter->trace);
	kमुक्त(iter->temp);
	kमुक्त(iter->buffer_iter);
release:
	seq_release_निजी(inode, file);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

पूर्णांक tracing_खोलो_generic(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(शून्य);
	अगर (ret)
		वापस ret;

	filp->निजी_data = inode->i_निजी;
	वापस 0;
पूर्ण

bool tracing_is_disabled(व्योम)
अणु
	वापस (tracing_disabled) ? true: false;
पूर्ण

/*
 * Open and update trace_array ref count.
 * Must have the current trace_array passed to it.
 */
पूर्णांक tracing_खोलो_generic_tr(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	filp->निजी_data = inode->i_निजी;

	वापस 0;
पूर्ण

अटल पूर्णांक tracing_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा trace_iterator *iter;
	पूर्णांक cpu;

	अगर (!(file->f_mode & FMODE_READ)) अणु
		trace_array_put(tr);
		वापस 0;
	पूर्ण

	/* Writes करो not use seq_file */
	iter = m->निजी;
	mutex_lock(&trace_types_lock);

	क्रम_each_tracing_cpu(cpu) अणु
		अगर (iter->buffer_iter[cpu])
			ring_buffer_पढ़ो_finish(iter->buffer_iter[cpu]);
	पूर्ण

	अगर (iter->trace && iter->trace->बंद)
		iter->trace->बंद(iter);

	अगर (!iter->snapshot && tr->stop_count)
		/* reenable tracing अगर it was previously enabled */
		tracing_start_tr(tr);

	__trace_array_put(tr);

	mutex_unlock(&trace_types_lock);

	mutex_destroy(&iter->mutex);
	मुक्त_cpumask_var(iter->started);
	kमुक्त(iter->fmt);
	kमुक्त(iter->temp);
	kमुक्त(iter->trace);
	kमुक्त(iter->buffer_iter);
	seq_release_निजी(inode, file);

	वापस 0;
पूर्ण

अटल पूर्णांक tracing_release_generic_tr(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	trace_array_put(tr);
	वापस 0;
पूर्ण

अटल पूर्णांक tracing_single_release_tr(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	trace_array_put(tr);

	वापस single_release(inode, file);
पूर्ण

अटल पूर्णांक tracing_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा trace_iterator *iter;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	/* If this file was खोलो क्रम ग_लिखो, then erase contents */
	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) अणु
		पूर्णांक cpu = tracing_get_cpu(inode);
		काष्ठा array_buffer *trace_buf = &tr->array_buffer;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
		अगर (tr->current_trace->prपूर्णांक_max)
			trace_buf = &tr->max_buffer;
#पूर्ण_अगर

		अगर (cpu == RING_BUFFER_ALL_CPUS)
			tracing_reset_online_cpus(trace_buf);
		अन्यथा
			tracing_reset_cpu(trace_buf, cpu);
	पूर्ण

	अगर (file->f_mode & FMODE_READ) अणु
		iter = __tracing_खोलो(inode, file, false);
		अगर (IS_ERR(iter))
			ret = PTR_ERR(iter);
		अन्यथा अगर (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
			iter->iter_flags |= TRACE_खाता_LAT_FMT;
	पूर्ण

	अगर (ret < 0)
		trace_array_put(tr);

	वापस ret;
पूर्ण

/*
 * Some tracers are not suitable क्रम instance buffers.
 * A tracer is always available क्रम the global array (toplevel)
 * or अगर it explicitly states that it is.
 */
अटल bool
trace_ok_क्रम_array(काष्ठा tracer *t, काष्ठा trace_array *tr)
अणु
	वापस (tr->flags & TRACE_ARRAY_FL_GLOBAL) || t->allow_instances;
पूर्ण

/* Find the next tracer that this trace array may use */
अटल काष्ठा tracer *
get_tracer_क्रम_array(काष्ठा trace_array *tr, काष्ठा tracer *t)
अणु
	जबतक (t && !trace_ok_क्रम_array(t, tr))
		t = t->next;

	वापस t;
पूर्ण

अटल व्योम *
t_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा tracer *t = v;

	(*pos)++;

	अगर (t)
		t = get_tracer_क्रम_array(tr, t->next);

	वापस t;
पूर्ण

अटल व्योम *t_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा tracer *t;
	loff_t l = 0;

	mutex_lock(&trace_types_lock);

	t = get_tracer_क्रम_array(tr, trace_types);
	क्रम (; t && l < *pos; t = t_next(m, t, &l))
			;

	वापस t;
पूर्ण

अटल व्योम t_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&trace_types_lock);
पूर्ण

अटल पूर्णांक t_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tracer *t = v;

	अगर (!t)
		वापस 0;

	seq_माला_दो(m, t->name);
	अगर (t->next)
		seq_अ_दो(m, ' ');
	अन्यथा
		seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations show_traces_seq_ops = अणु
	.start		= t_start,
	.next		= t_next,
	.stop		= t_stop,
	.show		= t_show,
पूर्ण;

अटल पूर्णांक show_traces_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा seq_file *m;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	ret = seq_खोलो(file, &show_traces_seq_ops);
	अगर (ret) अणु
		trace_array_put(tr);
		वापस ret;
	पूर्ण

	m = file->निजी_data;
	m->निजी = tr;

	वापस 0;
पूर्ण

अटल पूर्णांक show_traces_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	trace_array_put(tr);
	वापस seq_release(inode, file);
पूर्ण

अटल sमाप_प्रकार
tracing_ग_लिखो_stub(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		   माप_प्रकार count, loff_t *ppos)
अणु
	वापस count;
पूर्ण

loff_t tracing_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	पूर्णांक ret;

	अगर (file->f_mode & FMODE_READ)
		ret = seq_lseek(file, offset, whence);
	अन्यथा
		file->f_pos = ret = 0;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_fops = अणु
	.खोलो		= tracing_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= tracing_ग_लिखो_stub,
	.llseek		= tracing_lseek,
	.release	= tracing_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations show_traces_fops = अणु
	.खोलो		= show_traces_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= show_traces_release,
पूर्ण;

अटल sमाप_प्रकार
tracing_cpumask_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = file_inode(filp)->i_निजी;
	अक्षर *mask_str;
	पूर्णांक len;

	len = snम_लिखो(शून्य, 0, "%*pb\n",
		       cpumask_pr_args(tr->tracing_cpumask)) + 1;
	mask_str = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!mask_str)
		वापस -ENOMEM;

	len = snम_लिखो(mask_str, len, "%*pb\n",
		       cpumask_pr_args(tr->tracing_cpumask));
	अगर (len >= count) अणु
		count = -EINVAL;
		जाओ out_err;
	पूर्ण
	count = simple_पढ़ो_from_buffer(ubuf, count, ppos, mask_str, len);

out_err:
	kमुक्त(mask_str);

	वापस count;
पूर्ण

पूर्णांक tracing_set_cpumask(काष्ठा trace_array *tr,
			cpumask_var_t tracing_cpumask_new)
अणु
	पूर्णांक cpu;

	अगर (!tr)
		वापस -EINVAL;

	local_irq_disable();
	arch_spin_lock(&tr->max_lock);
	क्रम_each_tracing_cpu(cpu) अणु
		/*
		 * Increase/decrease the disabled counter अगर we are
		 * about to flip a bit in the cpumask:
		 */
		अगर (cpumask_test_cpu(cpu, tr->tracing_cpumask) &&
				!cpumask_test_cpu(cpu, tracing_cpumask_new)) अणु
			atomic_inc(&per_cpu_ptr(tr->array_buffer.data, cpu)->disabled);
			ring_buffer_record_disable_cpu(tr->array_buffer.buffer, cpu);
		पूर्ण
		अगर (!cpumask_test_cpu(cpu, tr->tracing_cpumask) &&
				cpumask_test_cpu(cpu, tracing_cpumask_new)) अणु
			atomic_dec(&per_cpu_ptr(tr->array_buffer.data, cpu)->disabled);
			ring_buffer_record_enable_cpu(tr->array_buffer.buffer, cpu);
		पूर्ण
	पूर्ण
	arch_spin_unlock(&tr->max_lock);
	local_irq_enable();

	cpumask_copy(tr->tracing_cpumask, tracing_cpumask_new);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
tracing_cpumask_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = file_inode(filp)->i_निजी;
	cpumask_var_t tracing_cpumask_new;
	पूर्णांक err;

	अगर (!zalloc_cpumask_var(&tracing_cpumask_new, GFP_KERNEL))
		वापस -ENOMEM;

	err = cpumask_parse_user(ubuf, count, tracing_cpumask_new);
	अगर (err)
		जाओ err_मुक्त;

	err = tracing_set_cpumask(tr, tracing_cpumask_new);
	अगर (err)
		जाओ err_मुक्त;

	मुक्त_cpumask_var(tracing_cpumask_new);

	वापस count;

err_मुक्त:
	मुक्त_cpumask_var(tracing_cpumask_new);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_cpumask_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.पढ़ो		= tracing_cpumask_पढ़ो,
	.ग_लिखो		= tracing_cpumask_ग_लिखो,
	.release	= tracing_release_generic_tr,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक tracing_trace_options_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tracer_opt *trace_opts;
	काष्ठा trace_array *tr = m->निजी;
	u32 tracer_flags;
	पूर्णांक i;

	mutex_lock(&trace_types_lock);
	tracer_flags = tr->current_trace->flags->val;
	trace_opts = tr->current_trace->flags->opts;

	क्रम (i = 0; trace_options[i]; i++) अणु
		अगर (tr->trace_flags & (1 << i))
			seq_म_लिखो(m, "%s\n", trace_options[i]);
		अन्यथा
			seq_म_लिखो(m, "no%s\n", trace_options[i]);
	पूर्ण

	क्रम (i = 0; trace_opts[i].name; i++) अणु
		अगर (tracer_flags & trace_opts[i].bit)
			seq_म_लिखो(m, "%s\n", trace_opts[i].name);
		अन्यथा
			seq_म_लिखो(m, "no%s\n", trace_opts[i].name);
	पूर्ण
	mutex_unlock(&trace_types_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __set_tracer_option(काष्ठा trace_array *tr,
			       काष्ठा tracer_flags *tracer_flags,
			       काष्ठा tracer_opt *opts, पूर्णांक neg)
अणु
	काष्ठा tracer *trace = tracer_flags->trace;
	पूर्णांक ret;

	ret = trace->set_flag(tr, tracer_flags->val, opts->bit, !neg);
	अगर (ret)
		वापस ret;

	अगर (neg)
		tracer_flags->val &= ~opts->bit;
	अन्यथा
		tracer_flags->val |= opts->bit;
	वापस 0;
पूर्ण

/* Try to assign a tracer specअगरic option */
अटल पूर्णांक set_tracer_option(काष्ठा trace_array *tr, अक्षर *cmp, पूर्णांक neg)
अणु
	काष्ठा tracer *trace = tr->current_trace;
	काष्ठा tracer_flags *tracer_flags = trace->flags;
	काष्ठा tracer_opt *opts = शून्य;
	पूर्णांक i;

	क्रम (i = 0; tracer_flags->opts[i].name; i++) अणु
		opts = &tracer_flags->opts[i];

		अगर (म_भेद(cmp, opts->name) == 0)
			वापस __set_tracer_option(tr, trace->flags, opts, neg);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Some tracers require overग_लिखो to stay enabled */
पूर्णांक trace_keep_overग_लिखो(काष्ठा tracer *tracer, u32 mask, पूर्णांक set)
अणु
	अगर (tracer->enabled && (mask & TRACE_ITER_OVERWRITE) && !set)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक set_tracer_flag(काष्ठा trace_array *tr, अचिन्हित पूर्णांक mask, पूर्णांक enabled)
अणु
	अगर ((mask == TRACE_ITER_RECORD_TGID) ||
	    (mask == TRACE_ITER_RECORD_CMD))
		lockdep_निश्चित_held(&event_mutex);

	/* करो nothing अगर flag is alपढ़ोy set */
	अगर (!!(tr->trace_flags & mask) == !!enabled)
		वापस 0;

	/* Give the tracer a chance to approve the change */
	अगर (tr->current_trace->flag_changed)
		अगर (tr->current_trace->flag_changed(tr, mask, !!enabled))
			वापस -EINVAL;

	अगर (enabled)
		tr->trace_flags |= mask;
	अन्यथा
		tr->trace_flags &= ~mask;

	अगर (mask == TRACE_ITER_RECORD_CMD)
		trace_event_enable_cmd_record(enabled);

	अगर (mask == TRACE_ITER_RECORD_TGID) अणु
		अगर (!tgid_map)
			tgid_map = kvसुस्मृति(PID_MAX_DEFAULT + 1,
					   माप(*tgid_map),
					   GFP_KERNEL);
		अगर (!tgid_map) अणु
			tr->trace_flags &= ~TRACE_ITER_RECORD_TGID;
			वापस -ENOMEM;
		पूर्ण

		trace_event_enable_tgid_record(enabled);
	पूर्ण

	अगर (mask == TRACE_ITER_EVENT_FORK)
		trace_event_follow_विभाजन(tr, enabled);

	अगर (mask == TRACE_ITER_FUNC_FORK)
		ftrace_pid_follow_विभाजन(tr, enabled);

	अगर (mask == TRACE_ITER_OVERWRITE) अणु
		ring_buffer_change_overग_लिखो(tr->array_buffer.buffer, enabled);
#अगर_घोषित CONFIG_TRACER_MAX_TRACE
		ring_buffer_change_overग_लिखो(tr->max_buffer.buffer, enabled);
#पूर्ण_अगर
	पूर्ण

	अगर (mask == TRACE_ITER_PRINTK) अणु
		trace_prपूर्णांकk_start_stop_comm(enabled);
		trace_prपूर्णांकk_control(enabled);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक trace_set_options(काष्ठा trace_array *tr, अक्षर *option)
अणु
	अक्षर *cmp;
	पूर्णांक neg = 0;
	पूर्णांक ret;
	माप_प्रकार orig_len = म_माप(option);
	पूर्णांक len;

	cmp = म_मालाip(option);

	len = str_has_prefix(cmp, "no");
	अगर (len)
		neg = 1;

	cmp += len;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	ret = match_string(trace_options, -1, cmp);
	/* If no option could be set, test the specअगरic tracer options */
	अगर (ret < 0)
		ret = set_tracer_option(tr, cmp, neg);
	अन्यथा
		ret = set_tracer_flag(tr, 1 << ret, !neg);

	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	/*
	 * If the first trailing whitespace is replaced with '\0' by म_मालाip,
	 * turn it back पूर्णांकo a space.
	 */
	अगर (orig_len > म_माप(option))
		option[म_माप(option)] = ' ';

	वापस ret;
पूर्ण

अटल व्योम __init apply_trace_boot_options(व्योम)
अणु
	अक्षर *buf = trace_boot_options_buf;
	अक्षर *option;

	जबतक (true) अणु
		option = strsep(&buf, ",");

		अगर (!option)
			अवरोध;

		अगर (*option)
			trace_set_options(&global_trace, option);

		/* Put back the comma to allow this to be called again */
		अगर (buf)
			*(buf - 1) = ',';
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
tracing_trace_options_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा trace_array *tr = m->निजी;
	अक्षर buf[64];
	पूर्णांक ret;

	अगर (cnt >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;

	ret = trace_set_options(tr, buf);
	अगर (ret < 0)
		वापस ret;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल पूर्णांक tracing_trace_options_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	ret = single_खोलो(file, tracing_trace_options_show, inode->i_निजी);
	अगर (ret < 0)
		trace_array_put(tr);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_iter_fops = अणु
	.खोलो		= tracing_trace_options_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= tracing_single_release_tr,
	.ग_लिखो		= tracing_trace_options_ग_लिखो,
पूर्ण;

अटल स्थिर अक्षर पढ़ोme_msg[] =
	"tracing mini-HOWTO:\n\n"
	"# echo 0 > tracing_on : quick way to disable tracing\n"
	"# echo 1 > tracing_on : quick way to re-enable tracing\n\n"
	" Important files:\n"
	"  trace\t\t\t- The static contents of the buffer\n"
	"\t\t\t  To clear the buffer write into this file: echo > trace\n"
	"  trace_pipe\t\t- A consuming read to see the contents of the buffer\n"
	"  current_tracer\t- function and latency tracers\n"
	"  available_tracers\t- list of configured tracers for current_tracer\n"
	"  error_log\t- error log for failed commands (that support it)\n"
	"  buffer_size_kb\t- view and modify size of per cpu buffer\n"
	"  buffer_total_size_kb  - view total size of all cpu buffers\n\n"
	"  trace_clock\t\t-change the clock used to order events\n"
	"       local:   Per cpu clock but may not be synced across CPUs\n"
	"      global:   Synced across CPUs but slows tracing down.\n"
	"     counter:   Not a clock, but just an increment\n"
	"      uptime:   Jiffy counter from time of boot\n"
	"        perf:   Same clock that perf events use\n"
#अगर_घोषित CONFIG_X86_64
	"     x86-tsc:   TSC cycle counter\n"
#पूर्ण_अगर
	"\n  timestamp_mode\t-view the mode used to timestamp events\n"
	"       delta:   Delta difference against a buffer-wide timestamp\n"
	"    absolute:   Absolute (standalone) timestamp\n"
	"\n  trace_marker\t\t- Writes into this file writes into the kernel buffer\n"
	"\n  trace_marker_raw\t\t- Writes into this file writes binary data into the kernel buffer\n"
	"  tracing_cpumask\t- Limit which CPUs to trace\n"
	"  instances\t\t- Make sub-buffers with: mkdir instances/foo\n"
	"\t\t\t  Remove sub-buffer with rmdir\n"
	"  trace_options\t\t- Set format or modify how tracing happens\n"
	"\t\t\t  Disable an option by prefixing 'no' to the\n"
	"\t\t\t  option name\n"
	"  saved_cmdlines_size\t- echo command number in here to store comm-pid list\n"
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	"\n  available_filter_functions - list of functions that can be filtered on\n"
	"  set_ftrace_filter\t- echo function name in here to only trace these\n"
	"\t\t\t  functions\n"
	"\t     accepts: func_full_name or glob-matching-pattern\n"
	"\t     modules: Can select a group via module\n"
	"\t      Format: :mod:<module-name>\n"
	"\t     example: echo :mod:ext3 > set_ftrace_filter\n"
	"\t    triggers: a command to perform when function is hit\n"
	"\t      Format: <function>:<trigger>[:count]\n"
	"\t     trigger: traceon, traceoff\n"
	"\t\t      enable_event:<system>:<event>\n"
	"\t\t      disable_event:<system>:<event>\n"
#अगर_घोषित CONFIG_STACKTRACE
	"\t\t      stacktrace\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	"\t\t      snapshot\n"
#पूर्ण_अगर
	"\t\t      dump\n"
	"\t\t      cpudump\n"
	"\t     example: echo do_fault:traceoff > set_ftrace_filter\n"
	"\t              echo do_trap:traceoff:3 > set_ftrace_filter\n"
	"\t     The first one will disable tracing every time do_fault is hit\n"
	"\t     The second will disable tracing at most 3 times when do_trap is hit\n"
	"\t       The first time do trap is hit and it disables tracing, the\n"
	"\t       counter will decrement to 2. If tracing is already disabled,\n"
	"\t       the counter will not decrement. It only decrements when the\n"
	"\t       trigger did work\n"
	"\t     To remove trigger without count:\n"
	"\t       echo '!<function>:<trigger> > set_ftrace_filter\n"
	"\t     To remove trigger with a count:\n"
	"\t       echo '!<function>:<trigger>:0 > set_ftrace_filter\n"
	"  set_ftrace_notrace\t- echo function name in here to never trace.\n"
	"\t    accepts: func_full_name, *func_end, func_begin*, *func_middle*\n"
	"\t    modules: Can select a group via module command :mod:\n"
	"\t    Does not accept triggers\n"
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */
#अगर_घोषित CONFIG_FUNCTION_TRACER
	"  set_ftrace_pid\t- Write pid(s) to only function trace those pids\n"
	"\t\t    (function)\n"
	"  set_ftrace_notrace_pid\t- Write pid(s) to not function trace those pids\n"
	"\t\t    (function)\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	"  set_graph_function\t- Trace the nested calls of a function (function_graph)\n"
	"  set_graph_notrace\t- Do not trace the nested calls of a function (function_graph)\n"
	"  max_graph_depth\t- Trace a limited depth of nested calls (0 is unlimited)\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	"\n  snapshot\t\t- Like 'trace' but shows the content of the static\n"
	"\t\t\t  snapshot buffer. Read the contents for more\n"
	"\t\t\t  information\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACK_TRACER
	"  stack_trace\t\t- Shows the max stack trace when active\n"
	"  stack_max_size\t- Shows current max stack size that was traced\n"
	"\t\t\t  Write into this file to reset the max size (trigger a\n"
	"\t\t\t  new trace)\n"
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	"  stack_trace_filter\t- Like set_ftrace_filter but limits what stack_trace\n"
	"\t\t\t  traces\n"
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_STACK_TRACER */
#अगर_घोषित CONFIG_DYNAMIC_EVENTS
	"  dynamic_events\t\t- Create/append/remove/show the generic dynamic events\n"
	"\t\t\t  Write into this file to define/undefine new trace events.\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_KPROBE_EVENTS
	"  kprobe_events\t\t- Create/append/remove/show the kernel dynamic events\n"
	"\t\t\t  Write into this file to define/undefine new trace events.\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBE_EVENTS
	"  uprobe_events\t\t- Create/append/remove/show the userspace dynamic events\n"
	"\t\t\t  Write into this file to define/undefine new trace events.\n"
#पूर्ण_अगर
#अगर defined(CONFIG_KPROBE_EVENTS) || defined(CONFIG_UPROBE_EVENTS)
	"\t  accepts: event-definitions (one definition per line)\n"
	"\t   Format: p[:[<group>/]<event>] <place> [<args>]\n"
	"\t           r[maxactive][:[<group>/]<event>] <place> [<args>]\n"
#अगर_घोषित CONFIG_HIST_TRIGGERS
	"\t           s:[synthetic/]<event> <field> [<field>]\n"
#पूर्ण_अगर
	"\t           -:[<group>/]<event>\n"
#अगर_घोषित CONFIG_KPROBE_EVENTS
	"\t    place: [<module>:]<symbol>[+<offset>]|<memaddr>\n"
  "place (kretprobe): [<module>:]<symbol>[+<offset>]%return|<memaddr>\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBE_EVENTS
  "   place (uprobe): <path>:<offset>[%return][(ref_ctr_offset)]\n"
#पूर्ण_अगर
	"\t     args: <name>=fetcharg[:type]\n"
	"\t fetcharg: %<register>, @<address>, @<symbol>[+|-<offset>],\n"
#अगर_घोषित CONFIG_HAVE_FUNCTION_ARG_ACCESS_API
	"\t           $stack<index>, $stack, $retval, $comm, $arg<N>,\n"
#अन्यथा
	"\t           $stack<index>, $stack, $retval, $comm,\n"
#पूर्ण_अगर
	"\t           +|-[u]<offset>(<fetcharg>), \\imm-value, \\\"imm-string\"\n"
	"\t     type: s8/16/32/64, u8/16/32/64, x8/16/32/64, string, symbol,\n"
	"\t           b<bit-width>@<bit-offset>/<container-size>, ustring,\n"
	"\t           <type>\\[<array-size>\\]\n"
#अगर_घोषित CONFIG_HIST_TRIGGERS
	"\t    field: <stype> <name>;\n"
	"\t    stype: u8/u16/u32/u64, s8/s16/s32/s64, pid_t,\n"
	"\t           [unsigned] char/int/long\n"
#पूर्ण_अगर
#पूर्ण_अगर
	"  events/\t\t- Directory containing all trace event subsystems:\n"
	"      enable\t\t- Write 0/1 to enable/disable tracing of all events\n"
	"  events/<system>/\t- Directory containing all trace events for <system>:\n"
	"      enable\t\t- Write 0/1 to enable/disable tracing of all <system>\n"
	"\t\t\t  events\n"
	"      filter\t\t- If set, only events passing filter are traced\n"
	"  events/<system>/<event>/\t- Directory containing control files for\n"
	"\t\t\t  <event>:\n"
	"      enable\t\t- Write 0/1 to enable/disable tracing of <event>\n"
	"      filter\t\t- If set, only events passing filter are traced\n"
	"      trigger\t\t- If set, a command to perform when event is hit\n"
	"\t    Format: <trigger>[:count][if <filter>]\n"
	"\t   trigger: traceon, traceoff\n"
	"\t            enable_event:<system>:<event>\n"
	"\t            disable_event:<system>:<event>\n"
#अगर_घोषित CONFIG_HIST_TRIGGERS
	"\t            enable_hist:<system>:<event>\n"
	"\t            disable_hist:<system>:<event>\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKTRACE
	"\t\t    stacktrace\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	"\t\t    snapshot\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_HIST_TRIGGERS
	"\t\t    hist (see below)\n"
#पूर्ण_अगर
	"\t   example: echo traceoff > events/block/block_unplug/trigger\n"
	"\t            echo traceoff:3 > events/block/block_unplug/trigger\n"
	"\t            echo 'enable_event:kmem:kmalloc:3 if nr_rq > 1' > \\\n"
	"\t                  events/block/block_unplug/trigger\n"
	"\t   The first disables tracing every time block_unplug is hit.\n"
	"\t   The second disables tracing the first 3 times block_unplug is hit.\n"
	"\t   The third enables the kmalloc event the first 3 times block_unplug\n"
	"\t     is hit and has value of greater than 1 for the 'nr_rq' event field.\n"
	"\t   Like function triggers, the counter is only decremented if it\n"
	"\t    enabled or disabled tracing.\n"
	"\t   To remove a trigger without a count:\n"
	"\t     echo '!<trigger> > <system>/<event>/trigger\n"
	"\t   To remove a trigger with a count:\n"
	"\t     echo '!<trigger>:0 > <system>/<event>/trigger\n"
	"\t   Filters can be ignored when removing a trigger.\n"
#अगर_घोषित CONFIG_HIST_TRIGGERS
	"      hist trigger\t- If set, event hits are aggregated into a hash table\n"
	"\t    Format: hist:keys=<field1[,field2,...]>\n"
	"\t            [:values=<field1[,field2,...]>]\n"
	"\t            [:sort=<field1[,field2,...]>]\n"
	"\t            [:size=#entries]\n"
	"\t            [:pause][:continue][:clear]\n"
	"\t            [:name=histname1]\n"
	"\t            [:<handler>.<action>]\n"
	"\t            [if <filter>]\n\n"
	"\t    When a matching event is hit, an entry is added to a hash\n"
	"\t    table using the key(s) and value(s) named, and the value of a\n"
	"\t    sum called 'hitcount' is incremented.  Keys and values\n"
	"\t    correspond to fields in the event's format description.  Keys\n"
	"\t    can be any field, or the special string 'stacktrace'.\n"
	"\t    Compound keys consisting of up to two fields can be specified\n"
	"\t    by the 'keys' keyword.  Values must correspond to numeric\n"
	"\t    fields.  Sort keys consisting of up to two fields can be\n"
	"\t    specified using the 'sort' keyword.  The sort direction can\n"
	"\t    be modified by appending '.descending' or '.ascending' to a\n"
	"\t    sort field.  The 'size' parameter can be used to specify more\n"
	"\t    or fewer than the default 2048 entries for the hashtable size.\n"
	"\t    If a hist trigger is given a name using the 'name' parameter,\n"
	"\t    its histogram data will be shared with other triggers of the\n"
	"\t    same name, and trigger hits will update this common data.\n\n"
	"\t    Reading the 'hist' file for the event will dump the hash\n"
	"\t    table in its entirety to stdout.  If there are multiple hist\n"
	"\t    triggers attached to an event, there will be a table for each\n"
	"\t    trigger in the output.  The table displayed for a named\n"
	"\t    trigger will be the same as any other instance having the\n"
	"\t    same name.  The default format used to display a given field\n"
	"\t    can be modified by appending any of the following modifiers\n"
	"\t    to the field name, as applicable:\n\n"
	"\t            .hex        display a number as a hex value\n"
	"\t            .sym        display an address as a symbol\n"
	"\t            .sym-offset display an address as a symbol and offset\n"
	"\t            .execname   display a common_pid as a program name\n"
	"\t            .syscall    display a syscall id as a syscall name\n"
	"\t            .log2       display log2 value rather than raw number\n"
	"\t            .usecs      display a common_timestamp in microseconds\n\n"
	"\t    The 'pause' parameter can be used to pause an existing hist\n"
	"\t    trigger or to start a hist trigger but not log any events\n"
	"\t    until told to do so.  'continue' can be used to start or\n"
	"\t    restart a paused hist trigger.\n\n"
	"\t    The 'clear' parameter will clear the contents of a running\n"
	"\t    hist trigger and leave its current paused/active state\n"
	"\t    unchanged.\n\n"
	"\t    The enable_hist and disable_hist triggers can be used to\n"
	"\t    have one event conditionally start and stop another event's\n"
	"\t    already-attached hist trigger.  The syntax is analogous to\n"
	"\t    the enable_event and disable_event triggers.\n\n"
	"\t    Hist trigger handlers and actions are executed whenever a\n"
	"\t    a histogram entry is added or updated.  They take the form:\n\n"
	"\t        <handler>.<action>\n\n"
	"\t    The available handlers are:\n\n"
	"\t        onmatch(matching.event)  - invoke on addition or update\n"
	"\t        onmax(var)               - invoke if var exceeds current max\n"
	"\t        onchange(var)            - invoke action if var changes\n\n"
	"\t    The available actions are:\n\n"
	"\t        trace(<synthetic_event>,param list)  - generate synthetic event\n"
	"\t        save(field,...)                      - save current event fields\n"
#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	"\t        snapshot()                           - snapshot the trace buffer\n\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYNTH_EVENTS
	"  events/synthetic_events\t- Create/append/remove/show synthetic events\n"
	"\t  Write into this file to define/undefine new synthetic events.\n"
	"\t     example: echo 'myevent u64 lat; char name[]' >> synthetic_events\n"
#पूर्ण_अगर
#पूर्ण_अगर
;

अटल sमाप_प्रकार
tracing_पढ़ोme_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		       माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos,
					पढ़ोme_msg, म_माप(पढ़ोme_msg));
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_पढ़ोme_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= tracing_पढ़ोme_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल व्योम *saved_tgids_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	पूर्णांक *ptr = v;

	अगर (*pos || m->count)
		ptr++;

	(*pos)++;

	क्रम (; ptr <= &tgid_map[PID_MAX_DEFAULT]; ptr++) अणु
		अगर (trace_find_tgid(*ptr))
			वापस ptr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *saved_tgids_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	व्योम *v;
	loff_t l = 0;

	अगर (!tgid_map)
		वापस शून्य;

	v = &tgid_map[0];
	जबतक (l <= *pos) अणु
		v = saved_tgids_next(m, v, &l);
		अगर (!v)
			वापस शून्य;
	पूर्ण

	वापस v;
पूर्ण

अटल व्योम saved_tgids_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक saved_tgids_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक pid = (पूर्णांक *)v - tgid_map;

	seq_म_लिखो(m, "%d %d\n", pid, trace_find_tgid(pid));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations tracing_saved_tgids_seq_ops = अणु
	.start		= saved_tgids_start,
	.stop		= saved_tgids_stop,
	.next		= saved_tgids_next,
	.show		= saved_tgids_show,
पूर्ण;

अटल पूर्णांक tracing_saved_tgids_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(शून्य);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(filp, &tracing_saved_tgids_seq_ops);
पूर्ण


अटल स्थिर काष्ठा file_operations tracing_saved_tgids_fops = अणु
	.खोलो		= tracing_saved_tgids_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल व्योम *saved_cmdlines_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	अचिन्हित पूर्णांक *ptr = v;

	अगर (*pos || m->count)
		ptr++;

	(*pos)++;

	क्रम (; ptr < &savedcmd->map_cmdline_to_pid[savedcmd->cmdline_num];
	     ptr++) अणु
		अगर (*ptr == -1 || *ptr == NO_CMDLINE_MAP)
			जारी;

		वापस ptr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *saved_cmdlines_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	व्योम *v;
	loff_t l = 0;

	preempt_disable();
	arch_spin_lock(&trace_cmdline_lock);

	v = &savedcmd->map_cmdline_to_pid[0];
	जबतक (l <= *pos) अणु
		v = saved_cmdlines_next(m, v, &l);
		अगर (!v)
			वापस शून्य;
	पूर्ण

	वापस v;
पूर्ण

अटल व्योम saved_cmdlines_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	arch_spin_unlock(&trace_cmdline_lock);
	preempt_enable();
पूर्ण

अटल पूर्णांक saved_cmdlines_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर buf[TASK_COMM_LEN];
	अचिन्हित पूर्णांक *pid = v;

	__trace_find_cmdline(*pid, buf);
	seq_म_लिखो(m, "%d %s\n", *pid, buf);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations tracing_saved_cmdlines_seq_ops = अणु
	.start		= saved_cmdlines_start,
	.next		= saved_cmdlines_next,
	.stop		= saved_cmdlines_stop,
	.show		= saved_cmdlines_show,
पूर्ण;

अटल पूर्णांक tracing_saved_cmdlines_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(शून्य);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(filp, &tracing_saved_cmdlines_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_saved_cmdlines_fops = अणु
	.खोलो		= tracing_saved_cmdlines_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल sमाप_प्रकार
tracing_saved_cmdlines_size_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				 माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[64];
	पूर्णांक r;

	arch_spin_lock(&trace_cmdline_lock);
	r = scnम_लिखो(buf, माप(buf), "%u\n", savedcmd->cmdline_num);
	arch_spin_unlock(&trace_cmdline_lock);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

अटल व्योम मुक्त_saved_cmdlines_buffer(काष्ठा saved_cmdlines_buffer *s)
अणु
	kमुक्त(s->saved_cmdlines);
	kमुक्त(s->map_cmdline_to_pid);
	kमुक्त(s);
पूर्ण

अटल पूर्णांक tracing_resize_saved_cmdlines(अचिन्हित पूर्णांक val)
अणु
	काष्ठा saved_cmdlines_buffer *s, *savedcmd_temp;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	अगर (allocate_cmdlines_buffer(val, s) < 0) अणु
		kमुक्त(s);
		वापस -ENOMEM;
	पूर्ण

	arch_spin_lock(&trace_cmdline_lock);
	savedcmd_temp = savedcmd;
	savedcmd = s;
	arch_spin_unlock(&trace_cmdline_lock);
	मुक्त_saved_cmdlines_buffer(savedcmd_temp);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
tracing_saved_cmdlines_size_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार cnt, loff_t *ppos)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	/* must have at least 1 entry or less than PID_MAX_DEFAULT */
	अगर (!val || val > PID_MAX_DEFAULT)
		वापस -EINVAL;

	ret = tracing_resize_saved_cmdlines((अचिन्हित पूर्णांक)val);
	अगर (ret < 0)
		वापस ret;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_saved_cmdlines_size_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= tracing_saved_cmdlines_size_पढ़ो,
	.ग_लिखो		= tracing_saved_cmdlines_size_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_TRACE_EVAL_MAP_खाता
अटल जोड़ trace_eval_map_item *
update_eval_map(जोड़ trace_eval_map_item *ptr)
अणु
	अगर (!ptr->map.eval_string) अणु
		अगर (ptr->tail.next) अणु
			ptr = ptr->tail.next;
			/* Set ptr to the next real item (skip head) */
			ptr++;
		पूर्ण अन्यथा
			वापस शून्य;
	पूर्ण
	वापस ptr;
पूर्ण

अटल व्योम *eval_map_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	जोड़ trace_eval_map_item *ptr = v;

	/*
	 * Paranoid! If ptr poपूर्णांकs to end, we करोn't want to increment past it.
	 * This really should never happen.
	 */
	(*pos)++;
	ptr = update_eval_map(ptr);
	अगर (WARN_ON_ONCE(!ptr))
		वापस शून्य;

	ptr++;
	ptr = update_eval_map(ptr);

	वापस ptr;
पूर्ण

अटल व्योम *eval_map_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	जोड़ trace_eval_map_item *v;
	loff_t l = 0;

	mutex_lock(&trace_eval_mutex);

	v = trace_eval_maps;
	अगर (v)
		v++;

	जबतक (v && l < *pos) अणु
		v = eval_map_next(m, v, &l);
	पूर्ण

	वापस v;
पूर्ण

अटल व्योम eval_map_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&trace_eval_mutex);
पूर्ण

अटल पूर्णांक eval_map_show(काष्ठा seq_file *m, व्योम *v)
अणु
	जोड़ trace_eval_map_item *ptr = v;

	seq_म_लिखो(m, "%s %ld (%s)\n",
		   ptr->map.eval_string, ptr->map.eval_value,
		   ptr->map.प्रणाली);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations tracing_eval_map_seq_ops = अणु
	.start		= eval_map_start,
	.next		= eval_map_next,
	.stop		= eval_map_stop,
	.show		= eval_map_show,
पूर्ण;

अटल पूर्णांक tracing_eval_map_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(शून्य);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(filp, &tracing_eval_map_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_eval_map_fops = अणु
	.खोलो		= tracing_eval_map_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

अटल अंतरभूत जोड़ trace_eval_map_item *
trace_eval_jmp_to_tail(जोड़ trace_eval_map_item *ptr)
अणु
	/* Return tail of array given the head */
	वापस ptr + ptr->head.length + 1;
पूर्ण

अटल व्योम
trace_insert_eval_map_file(काष्ठा module *mod, काष्ठा trace_eval_map **start,
			   पूर्णांक len)
अणु
	काष्ठा trace_eval_map **stop;
	काष्ठा trace_eval_map **map;
	जोड़ trace_eval_map_item *map_array;
	जोड़ trace_eval_map_item *ptr;

	stop = start + len;

	/*
	 * The trace_eval_maps contains the map plus a head and tail item,
	 * where the head holds the module and length of array, and the
	 * tail holds a poपूर्णांकer to the next list.
	 */
	map_array = kदो_स्मृति_array(len + 2, माप(*map_array), GFP_KERNEL);
	अगर (!map_array) अणु
		pr_warn("Unable to allocate trace eval mapping\n");
		वापस;
	पूर्ण

	mutex_lock(&trace_eval_mutex);

	अगर (!trace_eval_maps)
		trace_eval_maps = map_array;
	अन्यथा अणु
		ptr = trace_eval_maps;
		क्रम (;;) अणु
			ptr = trace_eval_jmp_to_tail(ptr);
			अगर (!ptr->tail.next)
				अवरोध;
			ptr = ptr->tail.next;

		पूर्ण
		ptr->tail.next = map_array;
	पूर्ण
	map_array->head.mod = mod;
	map_array->head.length = len;
	map_array++;

	क्रम (map = start; (अचिन्हित दीर्घ)map < (अचिन्हित दीर्घ)stop; map++) अणु
		map_array->map = **map;
		map_array++;
	पूर्ण
	स_रखो(map_array, 0, माप(*map_array));

	mutex_unlock(&trace_eval_mutex);
पूर्ण

अटल व्योम trace_create_eval_file(काष्ठा dentry *d_tracer)
अणु
	trace_create_file("eval_map", 0444, d_tracer,
			  शून्य, &tracing_eval_map_fops);
पूर्ण

#अन्यथा /* CONFIG_TRACE_EVAL_MAP_खाता */
अटल अंतरभूत व्योम trace_create_eval_file(काष्ठा dentry *d_tracer) अणु पूर्ण
अटल अंतरभूत व्योम trace_insert_eval_map_file(काष्ठा module *mod,
			      काष्ठा trace_eval_map **start, पूर्णांक len) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_TRACE_EVAL_MAP_खाता */

अटल व्योम trace_insert_eval_map(काष्ठा module *mod,
				  काष्ठा trace_eval_map **start, पूर्णांक len)
अणु
	काष्ठा trace_eval_map **map;

	अगर (len <= 0)
		वापस;

	map = start;

	trace_event_eval_update(map, len);

	trace_insert_eval_map_file(mod, start, len);
पूर्ण

अटल sमाप_प्रकार
tracing_set_trace_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		       माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	अक्षर buf[MAX_TRACER_SIZE+2];
	पूर्णांक r;

	mutex_lock(&trace_types_lock);
	r = प्र_लिखो(buf, "%s\n", tr->current_trace->name);
	mutex_unlock(&trace_types_lock);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

पूर्णांक tracer_init(काष्ठा tracer *t, काष्ठा trace_array *tr)
अणु
	tracing_reset_online_cpus(&tr->array_buffer);
	वापस t->init(tr);
पूर्ण

अटल व्योम set_buffer_entries(काष्ठा array_buffer *buf, अचिन्हित दीर्घ val)
अणु
	पूर्णांक cpu;

	क्रम_each_tracing_cpu(cpu)
		per_cpu_ptr(buf->data, cpu)->entries = val;
पूर्ण

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
/* resize @tr's buffer to the size of @size_tr's entries */
अटल पूर्णांक resize_buffer_duplicate_size(काष्ठा array_buffer *trace_buf,
					काष्ठा array_buffer *size_buf, पूर्णांक cpu_id)
अणु
	पूर्णांक cpu, ret = 0;

	अगर (cpu_id == RING_BUFFER_ALL_CPUS) अणु
		क्रम_each_tracing_cpu(cpu) अणु
			ret = ring_buffer_resize(trace_buf->buffer,
				 per_cpu_ptr(size_buf->data, cpu)->entries, cpu);
			अगर (ret < 0)
				अवरोध;
			per_cpu_ptr(trace_buf->data, cpu)->entries =
				per_cpu_ptr(size_buf->data, cpu)->entries;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ring_buffer_resize(trace_buf->buffer,
				 per_cpu_ptr(size_buf->data, cpu_id)->entries, cpu_id);
		अगर (ret == 0)
			per_cpu_ptr(trace_buf->data, cpu_id)->entries =
				per_cpu_ptr(size_buf->data, cpu_id)->entries;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRACER_MAX_TRACE */

अटल पूर्णांक __tracing_resize_ring_buffer(काष्ठा trace_array *tr,
					अचिन्हित दीर्घ size, पूर्णांक cpu)
अणु
	पूर्णांक ret;

	/*
	 * If kernel or user changes the size of the ring buffer
	 * we use the size that was given, and we can क्रमget about
	 * expanding it later.
	 */
	ring_buffer_expanded = true;

	/* May be called beक्रमe buffers are initialized */
	अगर (!tr->array_buffer.buffer)
		वापस 0;

	ret = ring_buffer_resize(tr->array_buffer.buffer, size, cpu);
	अगर (ret < 0)
		वापस ret;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (!(tr->flags & TRACE_ARRAY_FL_GLOBAL) ||
	    !tr->current_trace->use_max_tr)
		जाओ out;

	ret = ring_buffer_resize(tr->max_buffer.buffer, size, cpu);
	अगर (ret < 0) अणु
		पूर्णांक r = resize_buffer_duplicate_size(&tr->array_buffer,
						     &tr->array_buffer, cpu);
		अगर (r < 0) अणु
			/*
			 * AARGH! We are left with dअगरferent
			 * size max buffer!!!!
			 * The max buffer is our "snapshot" buffer.
			 * When a tracer needs a snapshot (one of the
			 * latency tracers), it swaps the max buffer
			 * with the saved snap shot. We succeeded to
			 * update the size of the मुख्य buffer, but failed to
			 * update the size of the max buffer. But when we tried
			 * to reset the मुख्य buffer to the original size, we
			 * failed there too. This is very unlikely to
			 * happen, but अगर it करोes, warn and समाप्त all
			 * tracing.
			 */
			WARN_ON(1);
			tracing_disabled = 1;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (cpu == RING_BUFFER_ALL_CPUS)
		set_buffer_entries(&tr->max_buffer, size);
	अन्यथा
		per_cpu_ptr(tr->max_buffer.data, cpu)->entries = size;

 out:
#पूर्ण_अगर /* CONFIG_TRACER_MAX_TRACE */

	अगर (cpu == RING_BUFFER_ALL_CPUS)
		set_buffer_entries(&tr->array_buffer, size);
	अन्यथा
		per_cpu_ptr(tr->array_buffer.data, cpu)->entries = size;

	वापस ret;
पूर्ण

sमाप_प्रकार tracing_resize_ring_buffer(काष्ठा trace_array *tr,
				  अचिन्हित दीर्घ size, पूर्णांक cpu_id)
अणु
	पूर्णांक ret = size;

	mutex_lock(&trace_types_lock);

	अगर (cpu_id != RING_BUFFER_ALL_CPUS) अणु
		/* make sure, this cpu is enabled in the mask */
		अगर (!cpumask_test_cpu(cpu_id, tracing_buffer_mask)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = __tracing_resize_ring_buffer(tr, size, cpu_id);
	अगर (ret < 0)
		ret = -ENOMEM;

out:
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण


/**
 * tracing_update_buffers - used by tracing facility to expand ring buffers
 *
 * To save on memory when the tracing is never used on a प्रणाली with it
 * configured in. The ring buffers are set to a minimum size. But once
 * a user starts to use the tracing facility, then they need to grow
 * to their शेष size.
 *
 * This function is to be called when a tracer is about to be used.
 */
पूर्णांक tracing_update_buffers(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&trace_types_lock);
	अगर (!ring_buffer_expanded)
		ret = __tracing_resize_ring_buffer(&global_trace, trace_buf_size,
						RING_BUFFER_ALL_CPUS);
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण

काष्ठा trace_option_dentry;

अटल व्योम
create_trace_option_files(काष्ठा trace_array *tr, काष्ठा tracer *tracer);

/*
 * Used to clear out the tracer beक्रमe deletion of an instance.
 * Must have trace_types_lock held.
 */
अटल व्योम tracing_set_nop(काष्ठा trace_array *tr)
अणु
	अगर (tr->current_trace == &nop_trace)
		वापस;
	
	tr->current_trace->enabled--;

	अगर (tr->current_trace->reset)
		tr->current_trace->reset(tr);

	tr->current_trace = &nop_trace;
पूर्ण

अटल व्योम add_tracer_options(काष्ठा trace_array *tr, काष्ठा tracer *t)
अणु
	/* Only enable अगर the directory has been created alपढ़ोy. */
	अगर (!tr->dir)
		वापस;

	create_trace_option_files(tr, t);
पूर्ण

पूर्णांक tracing_set_tracer(काष्ठा trace_array *tr, स्थिर अक्षर *buf)
अणु
	काष्ठा tracer *t;
#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	bool had_max_tr;
#पूर्ण_अगर
	पूर्णांक ret = 0;

	mutex_lock(&trace_types_lock);

	अगर (!ring_buffer_expanded) अणु
		ret = __tracing_resize_ring_buffer(tr, trace_buf_size,
						RING_BUFFER_ALL_CPUS);
		अगर (ret < 0)
			जाओ out;
		ret = 0;
	पूर्ण

	क्रम (t = trace_types; t; t = t->next) अणु
		अगर (म_भेद(t->name, buf) == 0)
			अवरोध;
	पूर्ण
	अगर (!t) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (t == tr->current_trace)
		जाओ out;

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	अगर (t->use_max_tr) अणु
		arch_spin_lock(&tr->max_lock);
		अगर (tr->cond_snapshot)
			ret = -EBUSY;
		arch_spin_unlock(&tr->max_lock);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर
	/* Some tracers won't work on kernel command line */
	अगर (प्रणाली_state < SYSTEM_RUNNING && t->noboot) अणु
		pr_warn("Tracer '%s' is not allowed on command line, ignored\n",
			t->name);
		जाओ out;
	पूर्ण

	/* Some tracers are only allowed क्रम the top level buffer */
	अगर (!trace_ok_क्रम_array(t, tr)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* If trace pipe files are being पढ़ो, we can't change the tracer */
	अगर (tr->trace_ref) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	trace_branch_disable();

	tr->current_trace->enabled--;

	अगर (tr->current_trace->reset)
		tr->current_trace->reset(tr);

	/* Current trace needs to be nop_trace beक्रमe synchronize_rcu */
	tr->current_trace = &nop_trace;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	had_max_tr = tr->allocated_snapshot;

	अगर (had_max_tr && !t->use_max_tr) अणु
		/*
		 * We need to make sure that the update_max_tr sees that
		 * current_trace changed to nop_trace to keep it from
		 * swapping the buffers after we resize it.
		 * The update_max_tr is called from पूर्णांकerrupts disabled
		 * so a synchronized_sched() is sufficient.
		 */
		synchronize_rcu();
		मुक्त_snapshot(tr);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (t->use_max_tr && !had_max_tr) अणु
		ret = tracing_alloc_snapshot_instance(tr);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (t->init) अणु
		ret = tracer_init(t, tr);
		अगर (ret)
			जाओ out;
	पूर्ण

	tr->current_trace = t;
	tr->current_trace->enabled++;
	trace_branch_enable(tr);
 out:
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
tracing_set_trace_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	अक्षर buf[MAX_TRACER_SIZE+1];
	पूर्णांक i;
	माप_प्रकार ret;
	पूर्णांक err;

	ret = cnt;

	अगर (cnt > MAX_TRACER_SIZE)
		cnt = MAX_TRACER_SIZE;

	अगर (copy_from_user(buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;

	/* strip ending whitespace. */
	क्रम (i = cnt - 1; i > 0 && है_खाली(buf[i]); i--)
		buf[i] = 0;

	err = tracing_set_tracer(tr, buf);
	अगर (err)
		वापस err;

	*ppos += ret;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
tracing_nsecs_पढ़ो(अचिन्हित दीर्घ *ptr, अक्षर __user *ubuf,
		   माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[64];
	पूर्णांक r;

	r = snम_लिखो(buf, माप(buf), "%ld\n",
		     *ptr == (अचिन्हित दीर्घ)-1 ? -1 : nsecs_to_usecs(*ptr));
	अगर (r > माप(buf))
		r = माप(buf);
	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

अटल sमाप_प्रकार
tracing_nsecs_ग_लिखो(अचिन्हित दीर्घ *ptr, स्थिर अक्षर __user *ubuf,
		    माप_प्रकार cnt, loff_t *ppos)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	*ptr = val * 1000;

	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
tracing_thresh_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		    माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस tracing_nsecs_पढ़ो(&tracing_thresh, ubuf, cnt, ppos);
पूर्ण

अटल sमाप_प्रकार
tracing_thresh_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	पूर्णांक ret;

	mutex_lock(&trace_types_lock);
	ret = tracing_nsecs_ग_लिखो(&tracing_thresh, ubuf, cnt, ppos);
	अगर (ret < 0)
		जाओ out;

	अगर (tr->current_trace->update_thresh) अणु
		ret = tr->current_trace->update_thresh(tr);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = cnt;
out:
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण

#अगर defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)

अटल sमाप_प्रकार
tracing_max_lat_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस tracing_nsecs_पढ़ो(filp->निजी_data, ubuf, cnt, ppos);
पूर्ण

अटल sमाप_प्रकार
tracing_max_lat_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		      माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस tracing_nsecs_ग_लिखो(filp->निजी_data, ubuf, cnt, ppos);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक tracing_खोलो_pipe(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा trace_iterator *iter;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	mutex_lock(&trace_types_lock);

	/* create a buffer to store the inक्रमmation to pass to userspace */
	iter = kzalloc(माप(*iter), GFP_KERNEL);
	अगर (!iter) अणु
		ret = -ENOMEM;
		__trace_array_put(tr);
		जाओ out;
	पूर्ण

	trace_seq_init(&iter->seq);
	iter->trace = tr->current_trace;

	अगर (!alloc_cpumask_var(&iter->started, GFP_KERNEL)) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* trace pipe करोes not show start of buffer */
	cpumask_setall(iter->started);

	अगर (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
		iter->iter_flags |= TRACE_खाता_LAT_FMT;

	/* Output in nanoseconds only अगर we are using a घड़ी in nanoseconds. */
	अगर (trace_घड़ीs[tr->घड़ी_id].in_ns)
		iter->iter_flags |= TRACE_खाता_TIME_IN_NS;

	iter->tr = tr;
	iter->array_buffer = &tr->array_buffer;
	iter->cpu_file = tracing_get_cpu(inode);
	mutex_init(&iter->mutex);
	filp->निजी_data = iter;

	अगर (iter->trace->pipe_खोलो)
		iter->trace->pipe_खोलो(iter);

	nonseekable_खोलो(inode, filp);

	tr->trace_ref++;
out:
	mutex_unlock(&trace_types_lock);
	वापस ret;

fail:
	kमुक्त(iter);
	__trace_array_put(tr);
	mutex_unlock(&trace_types_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tracing_release_pipe(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_iterator *iter = file->निजी_data;
	काष्ठा trace_array *tr = inode->i_निजी;

	mutex_lock(&trace_types_lock);

	tr->trace_ref--;

	अगर (iter->trace->pipe_बंद)
		iter->trace->pipe_बंद(iter);

	mutex_unlock(&trace_types_lock);

	मुक्त_cpumask_var(iter->started);
	mutex_destroy(&iter->mutex);
	kमुक्त(iter);

	trace_array_put(tr);

	वापस 0;
पूर्ण

अटल __poll_t
trace_poll(काष्ठा trace_iterator *iter, काष्ठा file *filp, poll_table *poll_table)
अणु
	काष्ठा trace_array *tr = iter->tr;

	/* Iterators are अटल, they should be filled or empty */
	अगर (trace_buffer_iter(iter, iter->cpu_file))
		वापस EPOLLIN | EPOLLRDNORM;

	अगर (tr->trace_flags & TRACE_ITER_BLOCK)
		/*
		 * Always select as पढ़ोable when in blocking mode
		 */
		वापस EPOLLIN | EPOLLRDNORM;
	अन्यथा
		वापस ring_buffer_poll_रुको(iter->array_buffer->buffer, iter->cpu_file,
					     filp, poll_table);
पूर्ण

अटल __poll_t
tracing_poll_pipe(काष्ठा file *filp, poll_table *poll_table)
अणु
	काष्ठा trace_iterator *iter = filp->निजी_data;

	वापस trace_poll(iter, filp, poll_table);
पूर्ण

/* Must be called with iter->mutex held. */
अटल पूर्णांक tracing_रुको_pipe(काष्ठा file *filp)
अणु
	काष्ठा trace_iterator *iter = filp->निजी_data;
	पूर्णांक ret;

	जबतक (trace_empty(iter)) अणु

		अगर ((filp->f_flags & O_NONBLOCK)) अणु
			वापस -EAGAIN;
		पूर्ण

		/*
		 * We block until we पढ़ो something and tracing is disabled.
		 * We still block अगर tracing is disabled, but we have never
		 * पढ़ो anything. This allows a user to cat this file, and
		 * then enable tracing. But after we have पढ़ो something,
		 * we give an खातापूर्ण when tracing is again disabled.
		 *
		 * iter->pos will be 0 अगर we haven't पढ़ो anything.
		 */
		अगर (!tracer_tracing_is_on(iter->tr) && iter->pos)
			अवरोध;

		mutex_unlock(&iter->mutex);

		ret = रुको_on_pipe(iter, 0);

		mutex_lock(&iter->mutex);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Consumer पढ़ोer.
 */
अटल sमाप_प्रकार
tracing_पढ़ो_pipe(काष्ठा file *filp, अक्षर __user *ubuf,
		  माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_iterator *iter = filp->निजी_data;
	sमाप_प्रकार sret;

	/*
	 * Aव्योम more than one consumer on a single file descriptor
	 * This is just a matter of traces coherency, the ring buffer itself
	 * is रक्षित.
	 */
	mutex_lock(&iter->mutex);

	/* वापस any leftover data */
	sret = trace_seq_to_user(&iter->seq, ubuf, cnt);
	अगर (sret != -EBUSY)
		जाओ out;

	trace_seq_init(&iter->seq);

	अगर (iter->trace->पढ़ो) अणु
		sret = iter->trace->पढ़ो(iter, filp, ubuf, cnt, ppos);
		अगर (sret)
			जाओ out;
	पूर्ण

रुकोagain:
	sret = tracing_रुको_pipe(filp);
	अगर (sret <= 0)
		जाओ out;

	/* stop when tracing is finished */
	अगर (trace_empty(iter)) अणु
		sret = 0;
		जाओ out;
	पूर्ण

	अगर (cnt >= PAGE_SIZE)
		cnt = PAGE_SIZE - 1;

	/* reset all but tr, trace, and overruns */
	स_रखो(&iter->seq, 0,
	       माप(काष्ठा trace_iterator) -
	       दुरत्व(काष्ठा trace_iterator, seq));
	cpumask_clear(iter->started);
	trace_seq_init(&iter->seq);
	iter->pos = -1;

	trace_event_पढ़ो_lock();
	trace_access_lock(iter->cpu_file);
	जबतक (trace_find_next_entry_inc(iter) != शून्य) अणु
		क्रमागत prपूर्णांक_line_t ret;
		पूर्णांक save_len = iter->seq.seq.len;

		ret = prपूर्णांक_trace_line(iter);
		अगर (ret == TRACE_TYPE_PARTIAL_LINE) अणु
			/* करोn't prपूर्णांक partial lines */
			iter->seq.seq.len = save_len;
			अवरोध;
		पूर्ण
		अगर (ret != TRACE_TYPE_NO_CONSUME)
			trace_consume(iter);

		अगर (trace_seq_used(&iter->seq) >= cnt)
			अवरोध;

		/*
		 * Setting the full flag means we reached the trace_seq buffer
		 * size and we should leave by partial output condition above.
		 * One of the trace_seq_* functions is not used properly.
		 */
		WARN_ONCE(iter->seq.full, "full flag set for trace type %d",
			  iter->ent->type);
	पूर्ण
	trace_access_unlock(iter->cpu_file);
	trace_event_पढ़ो_unlock();

	/* Now copy what we have to the user */
	sret = trace_seq_to_user(&iter->seq, ubuf, cnt);
	अगर (iter->seq.seq.पढ़ोpos >= trace_seq_used(&iter->seq))
		trace_seq_init(&iter->seq);

	/*
	 * If there was nothing to send to user, in spite of consuming trace
	 * entries, go back to रुको क्रम more entries.
	 */
	अगर (sret == -EBUSY)
		जाओ रुकोagain;

out:
	mutex_unlock(&iter->mutex);

	वापस sret;
पूर्ण

अटल व्योम tracing_spd_release_pipe(काष्ठा splice_pipe_desc *spd,
				     अचिन्हित पूर्णांक idx)
अणु
	__मुक्त_page(spd->pages[idx]);
पूर्ण

अटल माप_प्रकार
tracing_fill_pipe_page(माप_प्रकार rem, काष्ठा trace_iterator *iter)
अणु
	माप_प्रकार count;
	पूर्णांक save_len;
	पूर्णांक ret;

	/* Seq buffer is page-sized, exactly what we need. */
	क्रम (;;) अणु
		save_len = iter->seq.seq.len;
		ret = prपूर्णांक_trace_line(iter);

		अगर (trace_seq_has_overflowed(&iter->seq)) अणु
			iter->seq.seq.len = save_len;
			अवरोध;
		पूर्ण

		/*
		 * This should not be hit, because it should only
		 * be set अगर the iter->seq overflowed. But check it
		 * anyway to be safe.
		 */
		अगर (ret == TRACE_TYPE_PARTIAL_LINE) अणु
			iter->seq.seq.len = save_len;
			अवरोध;
		पूर्ण

		count = trace_seq_used(&iter->seq) - save_len;
		अगर (rem < count) अणु
			rem = 0;
			iter->seq.seq.len = save_len;
			अवरोध;
		पूर्ण

		अगर (ret != TRACE_TYPE_NO_CONSUME)
			trace_consume(iter);
		rem -= count;
		अगर (!trace_find_next_entry_inc(iter))	अणु
			rem = 0;
			iter->ent = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rem;
पूर्ण

अटल sमाप_प्रकार tracing_splice_पढ़ो_pipe(काष्ठा file *filp,
					loff_t *ppos,
					काष्ठा pipe_inode_info *pipe,
					माप_प्रकार len,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा page *pages_def[PIPE_DEF_BUFFERS];
	काष्ठा partial_page partial_def[PIPE_DEF_BUFFERS];
	काष्ठा trace_iterator *iter = filp->निजी_data;
	काष्ठा splice_pipe_desc spd = अणु
		.pages		= pages_def,
		.partial	= partial_def,
		.nr_pages	= 0, /* This माला_लो updated below. */
		.nr_pages_max	= PIPE_DEF_BUFFERS,
		.ops		= &शेष_pipe_buf_ops,
		.spd_release	= tracing_spd_release_pipe,
	पूर्ण;
	sमाप_प्रकार ret;
	माप_प्रकार rem;
	अचिन्हित पूर्णांक i;

	अगर (splice_grow_spd(pipe, &spd))
		वापस -ENOMEM;

	mutex_lock(&iter->mutex);

	अगर (iter->trace->splice_पढ़ो) अणु
		ret = iter->trace->splice_पढ़ो(iter, filp,
					       ppos, pipe, len, flags);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	ret = tracing_रुको_pipe(filp);
	अगर (ret <= 0)
		जाओ out_err;

	अगर (!iter->ent && !trace_find_next_entry_inc(iter)) अणु
		ret = -EFAULT;
		जाओ out_err;
	पूर्ण

	trace_event_पढ़ो_lock();
	trace_access_lock(iter->cpu_file);

	/* Fill as many pages as possible. */
	क्रम (i = 0, rem = len; i < spd.nr_pages_max && rem; i++) अणु
		spd.pages[i] = alloc_page(GFP_KERNEL);
		अगर (!spd.pages[i])
			अवरोध;

		rem = tracing_fill_pipe_page(rem, iter);

		/* Copy the data पूर्णांकo the page, so we can start over. */
		ret = trace_seq_to_buffer(&iter->seq,
					  page_address(spd.pages[i]),
					  trace_seq_used(&iter->seq));
		अगर (ret < 0) अणु
			__मुक्त_page(spd.pages[i]);
			अवरोध;
		पूर्ण
		spd.partial[i].offset = 0;
		spd.partial[i].len = trace_seq_used(&iter->seq);

		trace_seq_init(&iter->seq);
	पूर्ण

	trace_access_unlock(iter->cpu_file);
	trace_event_पढ़ो_unlock();
	mutex_unlock(&iter->mutex);

	spd.nr_pages = i;

	अगर (i)
		ret = splice_to_pipe(pipe, &spd);
	अन्यथा
		ret = 0;
out:
	splice_shrink_spd(&spd);
	वापस ret;

out_err:
	mutex_unlock(&iter->mutex);
	जाओ out;
पूर्ण

अटल sमाप_प्रकार
tracing_entries_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक cpu = tracing_get_cpu(inode);
	अक्षर buf[64];
	पूर्णांक r = 0;
	sमाप_प्रकार ret;

	mutex_lock(&trace_types_lock);

	अगर (cpu == RING_BUFFER_ALL_CPUS) अणु
		पूर्णांक cpu, buf_size_same;
		अचिन्हित दीर्घ size;

		size = 0;
		buf_size_same = 1;
		/* check अगर all cpu sizes are same */
		क्रम_each_tracing_cpu(cpu) अणु
			/* fill in the size from first enabled cpu */
			अगर (size == 0)
				size = per_cpu_ptr(tr->array_buffer.data, cpu)->entries;
			अगर (size != per_cpu_ptr(tr->array_buffer.data, cpu)->entries) अणु
				buf_size_same = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (buf_size_same) अणु
			अगर (!ring_buffer_expanded)
				r = प्र_लिखो(buf, "%lu (expanded: %lu)\n",
					    size >> 10,
					    trace_buf_size >> 10);
			अन्यथा
				r = प्र_लिखो(buf, "%lu\n", size >> 10);
		पूर्ण अन्यथा
			r = प्र_लिखो(buf, "X\n");
	पूर्ण अन्यथा
		r = प्र_लिखो(buf, "%lu\n", per_cpu_ptr(tr->array_buffer.data, cpu)->entries >> 10);

	mutex_unlock(&trace_types_lock);

	ret = simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
tracing_entries_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		      माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा trace_array *tr = inode->i_निजी;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	/* must have at least 1 entry */
	अगर (!val)
		वापस -EINVAL;

	/* value is in KB */
	val <<= 10;
	ret = tracing_resize_ring_buffer(tr, val, tracing_get_cpu(inode));
	अगर (ret < 0)
		वापस ret;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
tracing_total_entries_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	अक्षर buf[64];
	पूर्णांक r, cpu;
	अचिन्हित दीर्घ size = 0, expanded_size = 0;

	mutex_lock(&trace_types_lock);
	क्रम_each_tracing_cpu(cpu) अणु
		size += per_cpu_ptr(tr->array_buffer.data, cpu)->entries >> 10;
		अगर (!ring_buffer_expanded)
			expanded_size += trace_buf_size >> 10;
	पूर्ण
	अगर (ring_buffer_expanded)
		r = प्र_लिखो(buf, "%lu\n", size);
	अन्यथा
		r = प्र_लिखो(buf, "%lu (expanded: %lu)\n", size, expanded_size);
	mutex_unlock(&trace_types_lock);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

अटल sमाप_प्रकार
tracing_मुक्त_buffer_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
			  माप_प्रकार cnt, loff_t *ppos)
अणु
	/*
	 * There is no need to पढ़ो what the user has written, this function
	 * is just to make sure that there is no error when "echo" is used
	 */

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल पूर्णांक
tracing_मुक्त_buffer_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	/* disable tracing ? */
	अगर (tr->trace_flags & TRACE_ITER_STOP_ON_FREE)
		tracer_tracing_off(tr);
	/* resize the ring buffer to 0 */
	tracing_resize_ring_buffer(tr, 0, RING_BUFFER_ALL_CPUS);

	trace_array_put(tr);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
tracing_mark_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
					माप_प्रकार cnt, loff_t *fpos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	काष्ठा ring_buffer_event *event;
	क्रमागत event_trigger_type tt = ETT_NONE;
	काष्ठा trace_buffer *buffer;
	काष्ठा prपूर्णांक_entry *entry;
	sमाप_प्रकार written;
	पूर्णांक size;
	पूर्णांक len;

/* Used in tracing_mark_raw_ग_लिखो() as well */
#घोषणा FAULTED_STR "<faulted>"
#घोषणा FAULTED_SIZE (माप(FAULTED_STR) - 1) /* '\0' is alपढ़ोy accounted क्रम */

	अगर (tracing_disabled)
		वापस -EINVAL;

	अगर (!(tr->trace_flags & TRACE_ITER_MARKERS))
		वापस -EINVAL;

	अगर (cnt > TRACE_BUF_SIZE)
		cnt = TRACE_BUF_SIZE;

	BUILD_BUG_ON(TRACE_BUF_SIZE >= PAGE_SIZE);

	size = माप(*entry) + cnt + 2; /* add '\0' and possible '\n' */

	/* If less than "<faulted>", then make sure we can still add that */
	अगर (cnt < FAULTED_SIZE)
		size += FAULTED_SIZE - cnt;

	buffer = tr->array_buffer.buffer;
	event = __trace_buffer_lock_reserve(buffer, TRACE_PRINT, size,
					    tracing_gen_ctx());
	अगर (unlikely(!event))
		/* Ring buffer disabled, वापस as अगर not खोलो क्रम ग_लिखो */
		वापस -EBADF;

	entry = ring_buffer_event_data(event);
	entry->ip = _THIS_IP_;

	len = __copy_from_user_inatomic(&entry->buf, ubuf, cnt);
	अगर (len) अणु
		स_नकल(&entry->buf, FAULTED_STR, FAULTED_SIZE);
		cnt = FAULTED_SIZE;
		written = -EFAULT;
	पूर्ण अन्यथा
		written = cnt;

	अगर (tr->trace_marker_file && !list_empty(&tr->trace_marker_file->triggers)) अणु
		/* करो not add \न beक्रमe testing triggers, but add \0 */
		entry->buf[cnt] = '\0';
		tt = event_triggers_call(tr->trace_marker_file, buffer, entry, event);
	पूर्ण

	अगर (entry->buf[cnt - 1] != '\n') अणु
		entry->buf[cnt] = '\n';
		entry->buf[cnt + 1] = '\0';
	पूर्ण अन्यथा
		entry->buf[cnt] = '\0';

	अगर (अटल_branch_unlikely(&trace_marker_exports_enabled))
		ftrace_exports(event, TRACE_EXPORT_MARKER);
	__buffer_unlock_commit(buffer, event);

	अगर (tt)
		event_triggers_post_call(tr->trace_marker_file, tt);

	अगर (written > 0)
		*fpos += written;

	वापस written;
पूर्ण

/* Limit it क्रम now to 3K (including tag) */
#घोषणा RAW_DATA_MAX_SIZE (1024*3)

अटल sमाप_प्रकार
tracing_mark_raw_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
					माप_प्रकार cnt, loff_t *fpos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_buffer *buffer;
	काष्ठा raw_data_entry *entry;
	sमाप_प्रकार written;
	पूर्णांक size;
	पूर्णांक len;

#घोषणा FAULT_SIZE_ID (FAULTED_SIZE + माप(पूर्णांक))

	अगर (tracing_disabled)
		वापस -EINVAL;

	अगर (!(tr->trace_flags & TRACE_ITER_MARKERS))
		वापस -EINVAL;

	/* The marker must at least have a tag id */
	अगर (cnt < माप(अचिन्हित पूर्णांक) || cnt > RAW_DATA_MAX_SIZE)
		वापस -EINVAL;

	अगर (cnt > TRACE_BUF_SIZE)
		cnt = TRACE_BUF_SIZE;

	BUILD_BUG_ON(TRACE_BUF_SIZE >= PAGE_SIZE);

	size = माप(*entry) + cnt;
	अगर (cnt < FAULT_SIZE_ID)
		size += FAULT_SIZE_ID - cnt;

	buffer = tr->array_buffer.buffer;
	event = __trace_buffer_lock_reserve(buffer, TRACE_RAW_DATA, size,
					    tracing_gen_ctx());
	अगर (!event)
		/* Ring buffer disabled, वापस as अगर not खोलो क्रम ग_लिखो */
		वापस -EBADF;

	entry = ring_buffer_event_data(event);

	len = __copy_from_user_inatomic(&entry->id, ubuf, cnt);
	अगर (len) अणु
		entry->id = -1;
		स_नकल(&entry->buf, FAULTED_STR, FAULTED_SIZE);
		written = -EFAULT;
	पूर्ण अन्यथा
		written = cnt;

	__buffer_unlock_commit(buffer, event);

	अगर (written > 0)
		*fpos += written;

	वापस written;
पूर्ण

अटल पूर्णांक tracing_घड़ी_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा trace_array *tr = m->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(trace_घड़ीs); i++)
		seq_म_लिखो(m,
			"%s%s%s%s", i ? " " : "",
			i == tr->घड़ी_id ? "[" : "", trace_घड़ीs[i].name,
			i == tr->घड़ी_id ? "]" : "");
	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

पूर्णांक tracing_set_घड़ी(काष्ठा trace_array *tr, स्थिर अक्षर *घड़ीstr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(trace_घड़ीs); i++) अणु
		अगर (म_भेद(trace_घड़ीs[i].name, घड़ीstr) == 0)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(trace_घड़ीs))
		वापस -EINVAL;

	mutex_lock(&trace_types_lock);

	tr->घड़ी_id = i;

	ring_buffer_set_घड़ी(tr->array_buffer.buffer, trace_घड़ीs[i].func);

	/*
	 * New घड़ी may not be consistent with the previous घड़ी.
	 * Reset the buffer so that it करोesn't have incomparable बारtamps.
	 */
	tracing_reset_online_cpus(&tr->array_buffer);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (tr->max_buffer.buffer)
		ring_buffer_set_घड़ी(tr->max_buffer.buffer, trace_घड़ीs[i].func);
	tracing_reset_online_cpus(&tr->max_buffer);
#पूर्ण_अगर

	mutex_unlock(&trace_types_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार tracing_घड़ी_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				   माप_प्रकार cnt, loff_t *fpos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा trace_array *tr = m->निजी;
	अक्षर buf[64];
	स्थिर अक्षर *घड़ीstr;
	पूर्णांक ret;

	अगर (cnt >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;

	घड़ीstr = म_मालाip(buf);

	ret = tracing_set_घड़ी(tr, घड़ीstr);
	अगर (ret)
		वापस ret;

	*fpos += cnt;

	वापस cnt;
पूर्ण

अटल पूर्णांक tracing_घड़ी_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	ret = single_खोलो(file, tracing_घड़ी_show, inode->i_निजी);
	अगर (ret < 0)
		trace_array_put(tr);

	वापस ret;
पूर्ण

अटल पूर्णांक tracing_समय_stamp_mode_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा trace_array *tr = m->निजी;

	mutex_lock(&trace_types_lock);

	अगर (ring_buffer_समय_stamp_असल(tr->array_buffer.buffer))
		seq_माला_दो(m, "delta [absolute]\n");
	अन्यथा
		seq_माला_दो(m, "[delta] absolute\n");

	mutex_unlock(&trace_types_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tracing_समय_stamp_mode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	ret = single_खोलो(file, tracing_समय_stamp_mode_show, inode->i_निजी);
	अगर (ret < 0)
		trace_array_put(tr);

	वापस ret;
पूर्ण

u64 tracing_event_समय_stamp(काष्ठा trace_buffer *buffer, काष्ठा ring_buffer_event *rbe)
अणु
	अगर (rbe == this_cpu_पढ़ो(trace_buffered_event))
		वापस ring_buffer_समय_stamp(buffer);

	वापस ring_buffer_event_समय_stamp(buffer, rbe);
पूर्ण

/*
 * Set or disable using the per CPU trace_buffer_event when possible.
 */
पूर्णांक tracing_set_filter_buffering(काष्ठा trace_array *tr, bool set)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&trace_types_lock);

	अगर (set && tr->no_filter_buffering_ref++)
		जाओ out;

	अगर (!set) अणु
		अगर (WARN_ON_ONCE(!tr->no_filter_buffering_ref)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		--tr->no_filter_buffering_ref;
	पूर्ण
 out:
	mutex_unlock(&trace_types_lock);

	वापस ret;
पूर्ण

काष्ठा ftrace_buffer_info अणु
	काष्ठा trace_iterator	iter;
	व्योम			*spare;
	अचिन्हित पूर्णांक		spare_cpu;
	अचिन्हित पूर्णांक		पढ़ो;
पूर्ण;

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
अटल पूर्णांक tracing_snapshot_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा trace_iterator *iter;
	काष्ठा seq_file *m;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	अगर (file->f_mode & FMODE_READ) अणु
		iter = __tracing_खोलो(inode, file, true);
		अगर (IS_ERR(iter))
			ret = PTR_ERR(iter);
	पूर्ण अन्यथा अणु
		/* Writes still need the seq_file to hold the निजी data */
		ret = -ENOMEM;
		m = kzalloc(माप(*m), GFP_KERNEL);
		अगर (!m)
			जाओ out;
		iter = kzalloc(माप(*iter), GFP_KERNEL);
		अगर (!iter) अणु
			kमुक्त(m);
			जाओ out;
		पूर्ण
		ret = 0;

		iter->tr = tr;
		iter->array_buffer = &tr->max_buffer;
		iter->cpu_file = tracing_get_cpu(inode);
		m->निजी = iter;
		file->निजी_data = m;
	पूर्ण
out:
	अगर (ret < 0)
		trace_array_put(tr);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
tracing_snapshot_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
		       loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा trace_iterator *iter = m->निजी;
	काष्ठा trace_array *tr = iter->tr;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = tracing_update_buffers();
	अगर (ret < 0)
		वापस ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&trace_types_lock);

	अगर (tr->current_trace->use_max_tr) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	arch_spin_lock(&tr->max_lock);
	अगर (tr->cond_snapshot)
		ret = -EBUSY;
	arch_spin_unlock(&tr->max_lock);
	अगर (ret)
		जाओ out;

	चयन (val) अणु
	हाल 0:
		अगर (iter->cpu_file != RING_BUFFER_ALL_CPUS) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (tr->allocated_snapshot)
			मुक्त_snapshot(tr);
		अवरोध;
	हाल 1:
/* Only allow per-cpu swap अगर the ring buffer supports it */
#अगर_अघोषित CONFIG_RING_BUFFER_ALLOW_SWAP
		अगर (iter->cpu_file != RING_BUFFER_ALL_CPUS) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अगर (tr->allocated_snapshot)
			ret = resize_buffer_duplicate_size(&tr->max_buffer,
					&tr->array_buffer, iter->cpu_file);
		अन्यथा
			ret = tracing_alloc_snapshot_instance(tr);
		अगर (ret < 0)
			अवरोध;
		local_irq_disable();
		/* Now, we're going to swap */
		अगर (iter->cpu_file == RING_BUFFER_ALL_CPUS)
			update_max_tr(tr, current, smp_processor_id(), शून्य);
		अन्यथा
			update_max_tr_single(tr, current, iter->cpu_file);
		local_irq_enable();
		अवरोध;
	शेष:
		अगर (tr->allocated_snapshot) अणु
			अगर (iter->cpu_file == RING_BUFFER_ALL_CPUS)
				tracing_reset_online_cpus(&tr->max_buffer);
			अन्यथा
				tracing_reset_cpu(&tr->max_buffer, iter->cpu_file);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (ret >= 0) अणु
		*ppos += cnt;
		ret = cnt;
	पूर्ण
out:
	mutex_unlock(&trace_types_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tracing_snapshot_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	पूर्णांक ret;

	ret = tracing_release(inode, file);

	अगर (file->f_mode & FMODE_READ)
		वापस ret;

	/* If ग_लिखो only, the seq_file is just a stub */
	अगर (m)
		kमुक्त(m->निजी);
	kमुक्त(m);

	वापस 0;
पूर्ण

अटल पूर्णांक tracing_buffers_खोलो(काष्ठा inode *inode, काष्ठा file *filp);
अटल sमाप_प्रकार tracing_buffers_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				    माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक tracing_buffers_release(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार tracing_buffers_splice_पढ़ो(काष्ठा file *file, loff_t *ppos,
		   काष्ठा pipe_inode_info *pipe, माप_प्रकार len, अचिन्हित पूर्णांक flags);

अटल पूर्णांक snapshot_raw_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ftrace_buffer_info *info;
	पूर्णांक ret;

	/* The following checks क्रम tracefs lockकरोwn */
	ret = tracing_buffers_खोलो(inode, filp);
	अगर (ret < 0)
		वापस ret;

	info = filp->निजी_data;

	अगर (info->iter.trace->use_max_tr) अणु
		tracing_buffers_release(inode, filp);
		वापस -EBUSY;
	पूर्ण

	info->iter.snapshot = true;
	info->iter.array_buffer = &info->iter.tr->max_buffer;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_TRACER_SNAPSHOT */


अटल स्थिर काष्ठा file_operations tracing_thresh_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= tracing_thresh_पढ़ो,
	.ग_लिखो		= tracing_thresh_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;

#अगर defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)
अटल स्थिर काष्ठा file_operations tracing_max_lat_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= tracing_max_lat_पढ़ो,
	.ग_लिखो		= tracing_max_lat_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations set_tracer_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= tracing_set_trace_पढ़ो,
	.ग_लिखो		= tracing_set_trace_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations tracing_pipe_fops = अणु
	.खोलो		= tracing_खोलो_pipe,
	.poll		= tracing_poll_pipe,
	.पढ़ो		= tracing_पढ़ो_pipe,
	.splice_पढ़ो	= tracing_splice_पढ़ो_pipe,
	.release	= tracing_release_pipe,
	.llseek		= no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations tracing_entries_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.पढ़ो		= tracing_entries_पढ़ो,
	.ग_लिखो		= tracing_entries_ग_लिखो,
	.llseek		= generic_file_llseek,
	.release	= tracing_release_generic_tr,
पूर्ण;

अटल स्थिर काष्ठा file_operations tracing_total_entries_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.पढ़ो		= tracing_total_entries_पढ़ो,
	.llseek		= generic_file_llseek,
	.release	= tracing_release_generic_tr,
पूर्ण;

अटल स्थिर काष्ठा file_operations tracing_मुक्त_buffer_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.ग_लिखो		= tracing_मुक्त_buffer_ग_लिखो,
	.release	= tracing_मुक्त_buffer_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations tracing_mark_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.ग_लिखो		= tracing_mark_ग_लिखो,
	.llseek		= generic_file_llseek,
	.release	= tracing_release_generic_tr,
पूर्ण;

अटल स्थिर काष्ठा file_operations tracing_mark_raw_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.ग_लिखो		= tracing_mark_raw_ग_लिखो,
	.llseek		= generic_file_llseek,
	.release	= tracing_release_generic_tr,
पूर्ण;

अटल स्थिर काष्ठा file_operations trace_घड़ी_fops = अणु
	.खोलो		= tracing_घड़ी_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= tracing_single_release_tr,
	.ग_लिखो		= tracing_घड़ी_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations trace_समय_stamp_mode_fops = अणु
	.खोलो		= tracing_समय_stamp_mode_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= tracing_single_release_tr,
पूर्ण;

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
अटल स्थिर काष्ठा file_operations snapshot_fops = अणु
	.खोलो		= tracing_snapshot_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= tracing_snapshot_ग_लिखो,
	.llseek		= tracing_lseek,
	.release	= tracing_snapshot_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations snapshot_raw_fops = अणु
	.खोलो		= snapshot_raw_खोलो,
	.पढ़ो		= tracing_buffers_पढ़ो,
	.release	= tracing_buffers_release,
	.splice_पढ़ो	= tracing_buffers_splice_पढ़ो,
	.llseek		= no_llseek,
पूर्ण;

#पूर्ण_अगर /* CONFIG_TRACER_SNAPSHOT */

#घोषणा TRACING_LOG_ERRS_MAX	8
#घोषणा TRACING_LOG_LOC_MAX	128

#घोषणा CMD_PREFIX "  Command: "

काष्ठा err_info अणु
	स्थिर अक्षर	**errs;	/* ptr to loc-specअगरic array of err strings */
	u8		type;	/* index पूर्णांकo errs -> specअगरic err string */
	u8		pos;	/* MAX_FILTER_STR_VAL = 256 */
	u64		ts;
पूर्ण;

काष्ठा tracing_log_err अणु
	काष्ठा list_head	list;
	काष्ठा err_info		info;
	अक्षर			loc[TRACING_LOG_LOC_MAX]; /* err location */
	अक्षर			cmd[MAX_FILTER_STR_VAL]; /* what caused err */
पूर्ण;

अटल DEFINE_MUTEX(tracing_err_log_lock);

अटल काष्ठा tracing_log_err *get_tracing_log_err(काष्ठा trace_array *tr)
अणु
	काष्ठा tracing_log_err *err;

	अगर (tr->n_err_log_entries < TRACING_LOG_ERRS_MAX) अणु
		err = kzalloc(माप(*err), GFP_KERNEL);
		अगर (!err)
			err = ERR_PTR(-ENOMEM);
		tr->n_err_log_entries++;

		वापस err;
	पूर्ण

	err = list_first_entry(&tr->err_log, काष्ठा tracing_log_err, list);
	list_del(&err->list);

	वापस err;
पूर्ण

/**
 * err_pos - find the position of a string within a command क्रम error careting
 * @cmd: The tracing command that caused the error
 * @str: The string to position the caret at within @cmd
 *
 * Finds the position of the first occurrence of @str within @cmd.  The
 * वापस value can be passed to tracing_log_err() क्रम caret placement
 * within @cmd.
 *
 * Returns the index within @cmd of the first occurrence of @str or 0
 * अगर @str was not found.
 */
अचिन्हित पूर्णांक err_pos(अक्षर *cmd, स्थिर अक्षर *str)
अणु
	अक्षर *found;

	अगर (WARN_ON(!म_माप(cmd)))
		वापस 0;

	found = म_माला(cmd, str);
	अगर (found)
		वापस found - cmd;

	वापस 0;
पूर्ण

/**
 * tracing_log_err - ग_लिखो an error to the tracing error log
 * @tr: The associated trace array क्रम the error (शून्य क्रम top level array)
 * @loc: A string describing where the error occurred
 * @cmd: The tracing command that caused the error
 * @errs: The array of loc-specअगरic अटल error strings
 * @type: The index पूर्णांकo errs[], which produces the specअगरic अटल err string
 * @pos: The position the caret should be placed in the cmd
 *
 * Writes an error पूर्णांकo tracing/error_log of the क्रमm:
 *
 * <loc>: error: <text>
 *   Command: <cmd>
 *              ^
 *
 * tracing/error_log is a small log file containing the last
 * TRACING_LOG_ERRS_MAX errors (8).  Memory क्रम errors isn't allocated
 * unless there has been a tracing error, and the error log can be
 * cleared and have its memory मुक्तd by writing the empty string in
 * truncation mode to it i.e. echo > tracing/error_log.
 *
 * NOTE: the @errs array aदीर्घ with the @type param are used to
 * produce a अटल error string - this string is not copied and saved
 * when the error is logged - only a poपूर्णांकer to it is saved.  See
 * existing callers क्रम examples of how अटल strings are typically
 * defined क्रम use with tracing_log_err().
 */
व्योम tracing_log_err(काष्ठा trace_array *tr,
		     स्थिर अक्षर *loc, स्थिर अक्षर *cmd,
		     स्थिर अक्षर **errs, u8 type, u8 pos)
अणु
	काष्ठा tracing_log_err *err;

	अगर (!tr)
		tr = &global_trace;

	mutex_lock(&tracing_err_log_lock);
	err = get_tracing_log_err(tr);
	अगर (PTR_ERR(err) == -ENOMEM) अणु
		mutex_unlock(&tracing_err_log_lock);
		वापस;
	पूर्ण

	snम_लिखो(err->loc, TRACING_LOG_LOC_MAX, "%s: error: ", loc);
	snम_लिखो(err->cmd, MAX_FILTER_STR_VAL,"\n" CMD_PREFIX "%s\n", cmd);

	err->info.errs = errs;
	err->info.type = type;
	err->info.pos = pos;
	err->info.ts = local_घड़ी();

	list_add_tail(&err->list, &tr->err_log);
	mutex_unlock(&tracing_err_log_lock);
पूर्ण

अटल व्योम clear_tracing_err_log(काष्ठा trace_array *tr)
अणु
	काष्ठा tracing_log_err *err, *next;

	mutex_lock(&tracing_err_log_lock);
	list_क्रम_each_entry_safe(err, next, &tr->err_log, list) अणु
		list_del(&err->list);
		kमुक्त(err);
	पूर्ण

	tr->n_err_log_entries = 0;
	mutex_unlock(&tracing_err_log_lock);
पूर्ण

अटल व्योम *tracing_err_log_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा trace_array *tr = m->निजी;

	mutex_lock(&tracing_err_log_lock);

	वापस seq_list_start(&tr->err_log, *pos);
पूर्ण

अटल व्योम *tracing_err_log_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_array *tr = m->निजी;

	वापस seq_list_next(v, &tr->err_log, pos);
पूर्ण

अटल व्योम tracing_err_log_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&tracing_err_log_lock);
पूर्ण

अटल व्योम tracing_err_log_show_pos(काष्ठा seq_file *m, u8 pos)
अणु
	u8 i;

	क्रम (i = 0; i < माप(CMD_PREFIX) - 1; i++)
		seq_अ_दो(m, ' ');
	क्रम (i = 0; i < pos; i++)
		seq_अ_दो(m, ' ');
	seq_माला_दो(m, "^\न");
पूर्ण

अटल पूर्णांक tracing_err_log_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tracing_log_err *err = v;

	अगर (err) अणु
		स्थिर अक्षर *err_text = err->info.errs[err->info.type];
		u64 sec = err->info.ts;
		u32 nsec;

		nsec = करो_भाग(sec, NSEC_PER_SEC);
		seq_म_लिखो(m, "[%5llu.%06u] %s%s", sec, nsec / 1000,
			   err->loc, err_text);
		seq_म_लिखो(m, "%s", err->cmd);
		tracing_err_log_show_pos(m, err->info.pos);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations tracing_err_log_seq_ops = अणु
	.start  = tracing_err_log_seq_start,
	.next   = tracing_err_log_seq_next,
	.stop   = tracing_err_log_seq_stop,
	.show   = tracing_err_log_seq_show
पूर्ण;

अटल पूर्णांक tracing_err_log_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	पूर्णांक ret = 0;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	/* If this file was खोलोed क्रम ग_लिखो, then erase contents */
	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC))
		clear_tracing_err_log(tr);

	अगर (file->f_mode & FMODE_READ) अणु
		ret = seq_खोलो(file, &tracing_err_log_seq_ops);
		अगर (!ret) अणु
			काष्ठा seq_file *m = file->निजी_data;
			m->निजी = tr;
		पूर्ण अन्यथा अणु
			trace_array_put(tr);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार tracing_err_log_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *buffer,
				     माप_प्रकार count, loff_t *ppos)
अणु
	वापस count;
पूर्ण

अटल पूर्णांक tracing_err_log_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	trace_array_put(tr);

	अगर (file->f_mode & FMODE_READ)
		seq_release(inode, file);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_err_log_fops = अणु
	.खोलो           = tracing_err_log_खोलो,
	.ग_लिखो		= tracing_err_log_ग_लिखो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = tracing_err_log_release,
पूर्ण;

अटल पूर्णांक tracing_buffers_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा ftrace_buffer_info *info;
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	info = kvzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		trace_array_put(tr);
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&trace_types_lock);

	info->iter.tr		= tr;
	info->iter.cpu_file	= tracing_get_cpu(inode);
	info->iter.trace	= tr->current_trace;
	info->iter.array_buffer = &tr->array_buffer;
	info->spare		= शून्य;
	/* Force पढ़ोing ring buffer क्रम first पढ़ो */
	info->पढ़ो		= (अचिन्हित पूर्णांक)-1;

	filp->निजी_data = info;

	tr->trace_ref++;

	mutex_unlock(&trace_types_lock);

	ret = nonseekable_खोलो(inode, filp);
	अगर (ret < 0)
		trace_array_put(tr);

	वापस ret;
पूर्ण

अटल __poll_t
tracing_buffers_poll(काष्ठा file *filp, poll_table *poll_table)
अणु
	काष्ठा ftrace_buffer_info *info = filp->निजी_data;
	काष्ठा trace_iterator *iter = &info->iter;

	वापस trace_poll(iter, filp, poll_table);
पूर्ण

अटल sमाप_प्रकार
tracing_buffers_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ftrace_buffer_info *info = filp->निजी_data;
	काष्ठा trace_iterator *iter = &info->iter;
	sमाप_प्रकार ret = 0;
	sमाप_प्रकार size;

	अगर (!count)
		वापस 0;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (iter->snapshot && iter->tr->current_trace->use_max_tr)
		वापस -EBUSY;
#पूर्ण_अगर

	अगर (!info->spare) अणु
		info->spare = ring_buffer_alloc_पढ़ो_page(iter->array_buffer->buffer,
							  iter->cpu_file);
		अगर (IS_ERR(info->spare)) अणु
			ret = PTR_ERR(info->spare);
			info->spare = शून्य;
		पूर्ण अन्यथा अणु
			info->spare_cpu = iter->cpu_file;
		पूर्ण
	पूर्ण
	अगर (!info->spare)
		वापस ret;

	/* Do we have previous पढ़ो data to पढ़ो? */
	अगर (info->पढ़ो < PAGE_SIZE)
		जाओ पढ़ो;

 again:
	trace_access_lock(iter->cpu_file);
	ret = ring_buffer_पढ़ो_page(iter->array_buffer->buffer,
				    &info->spare,
				    count,
				    iter->cpu_file, 0);
	trace_access_unlock(iter->cpu_file);

	अगर (ret < 0) अणु
		अगर (trace_empty(iter)) अणु
			अगर ((filp->f_flags & O_NONBLOCK))
				वापस -EAGAIN;

			ret = रुको_on_pipe(iter, 0);
			अगर (ret)
				वापस ret;

			जाओ again;
		पूर्ण
		वापस 0;
	पूर्ण

	info->पढ़ो = 0;
 पढ़ो:
	size = PAGE_SIZE - info->पढ़ो;
	अगर (size > count)
		size = count;

	ret = copy_to_user(ubuf, info->spare + info->पढ़ो, size);
	अगर (ret == size)
		वापस -EFAULT;

	size -= ret;

	*ppos += size;
	info->पढ़ो += size;

	वापस size;
पूर्ण

अटल पूर्णांक tracing_buffers_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_buffer_info *info = file->निजी_data;
	काष्ठा trace_iterator *iter = &info->iter;

	mutex_lock(&trace_types_lock);

	iter->tr->trace_ref--;

	__trace_array_put(iter->tr);

	अगर (info->spare)
		ring_buffer_मुक्त_पढ़ो_page(iter->array_buffer->buffer,
					   info->spare_cpu, info->spare);
	kvमुक्त(info);

	mutex_unlock(&trace_types_lock);

	वापस 0;
पूर्ण

काष्ठा buffer_ref अणु
	काष्ठा trace_buffer	*buffer;
	व्योम			*page;
	पूर्णांक			cpu;
	refcount_t		refcount;
पूर्ण;

अटल व्योम buffer_ref_release(काष्ठा buffer_ref *ref)
अणु
	अगर (!refcount_dec_and_test(&ref->refcount))
		वापस;
	ring_buffer_मुक्त_पढ़ो_page(ref->buffer, ref->cpu, ref->page);
	kमुक्त(ref);
पूर्ण

अटल व्योम buffer_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
				    काष्ठा pipe_buffer *buf)
अणु
	काष्ठा buffer_ref *ref = (काष्ठा buffer_ref *)buf->निजी;

	buffer_ref_release(ref);
	buf->निजी = 0;
पूर्ण

अटल bool buffer_pipe_buf_get(काष्ठा pipe_inode_info *pipe,
				काष्ठा pipe_buffer *buf)
अणु
	काष्ठा buffer_ref *ref = (काष्ठा buffer_ref *)buf->निजी;

	अगर (refcount_पढ़ो(&ref->refcount) > पूर्णांक_उच्च/2)
		वापस false;

	refcount_inc(&ref->refcount);
	वापस true;
पूर्ण

/* Pipe buffer operations क्रम a buffer. */
अटल स्थिर काष्ठा pipe_buf_operations buffer_pipe_buf_ops = अणु
	.release		= buffer_pipe_buf_release,
	.get			= buffer_pipe_buf_get,
पूर्ण;

/*
 * Callback from splice_to_pipe(), अगर we need to release some pages
 * at the end of the spd in हाल we error'ed out in filling the pipe.
 */
अटल व्योम buffer_spd_release(काष्ठा splice_pipe_desc *spd, अचिन्हित पूर्णांक i)
अणु
	काष्ठा buffer_ref *ref =
		(काष्ठा buffer_ref *)spd->partial[i].निजी;

	buffer_ref_release(ref);
	spd->partial[i].निजी = 0;
पूर्ण

अटल sमाप_प्रकार
tracing_buffers_splice_पढ़ो(काष्ठा file *file, loff_t *ppos,
			    काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
			    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ftrace_buffer_info *info = file->निजी_data;
	काष्ठा trace_iterator *iter = &info->iter;
	काष्ठा partial_page partial_def[PIPE_DEF_BUFFERS];
	काष्ठा page *pages_def[PIPE_DEF_BUFFERS];
	काष्ठा splice_pipe_desc spd = अणु
		.pages		= pages_def,
		.partial	= partial_def,
		.nr_pages_max	= PIPE_DEF_BUFFERS,
		.ops		= &buffer_pipe_buf_ops,
		.spd_release	= buffer_spd_release,
	पूर्ण;
	काष्ठा buffer_ref *ref;
	पूर्णांक entries, i;
	sमाप_प्रकार ret = 0;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	अगर (iter->snapshot && iter->tr->current_trace->use_max_tr)
		वापस -EBUSY;
#पूर्ण_अगर

	अगर (*ppos & (PAGE_SIZE - 1))
		वापस -EINVAL;

	अगर (len & (PAGE_SIZE - 1)) अणु
		अगर (len < PAGE_SIZE)
			वापस -EINVAL;
		len &= PAGE_MASK;
	पूर्ण

	अगर (splice_grow_spd(pipe, &spd))
		वापस -ENOMEM;

 again:
	trace_access_lock(iter->cpu_file);
	entries = ring_buffer_entries_cpu(iter->array_buffer->buffer, iter->cpu_file);

	क्रम (i = 0; i < spd.nr_pages_max && len && entries; i++, len -= PAGE_SIZE) अणु
		काष्ठा page *page;
		पूर्णांक r;

		ref = kzalloc(माप(*ref), GFP_KERNEL);
		अगर (!ref) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		refcount_set(&ref->refcount, 1);
		ref->buffer = iter->array_buffer->buffer;
		ref->page = ring_buffer_alloc_पढ़ो_page(ref->buffer, iter->cpu_file);
		अगर (IS_ERR(ref->page)) अणु
			ret = PTR_ERR(ref->page);
			ref->page = शून्य;
			kमुक्त(ref);
			अवरोध;
		पूर्ण
		ref->cpu = iter->cpu_file;

		r = ring_buffer_पढ़ो_page(ref->buffer, &ref->page,
					  len, iter->cpu_file, 1);
		अगर (r < 0) अणु
			ring_buffer_मुक्त_पढ़ो_page(ref->buffer, ref->cpu,
						   ref->page);
			kमुक्त(ref);
			अवरोध;
		पूर्ण

		page = virt_to_page(ref->page);

		spd.pages[i] = page;
		spd.partial[i].len = PAGE_SIZE;
		spd.partial[i].offset = 0;
		spd.partial[i].निजी = (अचिन्हित दीर्घ)ref;
		spd.nr_pages++;
		*ppos += PAGE_SIZE;

		entries = ring_buffer_entries_cpu(iter->array_buffer->buffer, iter->cpu_file);
	पूर्ण

	trace_access_unlock(iter->cpu_file);
	spd.nr_pages = i;

	/* did we पढ़ो anything? */
	अगर (!spd.nr_pages) अणु
		अगर (ret)
			जाओ out;

		ret = -EAGAIN;
		अगर ((file->f_flags & O_NONBLOCK) || (flags & SPLICE_F_NONBLOCK))
			जाओ out;

		ret = रुको_on_pipe(iter, iter->tr->buffer_percent);
		अगर (ret)
			जाओ out;

		जाओ again;
	पूर्ण

	ret = splice_to_pipe(pipe, &spd);
out:
	splice_shrink_spd(&spd);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_buffers_fops = अणु
	.खोलो		= tracing_buffers_खोलो,
	.पढ़ो		= tracing_buffers_पढ़ो,
	.poll		= tracing_buffers_poll,
	.release	= tracing_buffers_release,
	.splice_पढ़ो	= tracing_buffers_splice_पढ़ो,
	.llseek		= no_llseek,
पूर्ण;

अटल sमाप_प्रकार
tracing_stats_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा array_buffer *trace_buf = &tr->array_buffer;
	पूर्णांक cpu = tracing_get_cpu(inode);
	काष्ठा trace_seq *s;
	अचिन्हित दीर्घ cnt;
	अचिन्हित दीर्घ दीर्घ t;
	अचिन्हित दीर्घ usec_rem;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	trace_seq_init(s);

	cnt = ring_buffer_entries_cpu(trace_buf->buffer, cpu);
	trace_seq_म_लिखो(s, "entries: %ld\n", cnt);

	cnt = ring_buffer_overrun_cpu(trace_buf->buffer, cpu);
	trace_seq_म_लिखो(s, "overrun: %ld\n", cnt);

	cnt = ring_buffer_commit_overrun_cpu(trace_buf->buffer, cpu);
	trace_seq_म_लिखो(s, "commit overrun: %ld\n", cnt);

	cnt = ring_buffer_bytes_cpu(trace_buf->buffer, cpu);
	trace_seq_म_लिखो(s, "bytes: %ld\n", cnt);

	अगर (trace_घड़ीs[tr->घड़ी_id].in_ns) अणु
		/* local or global क्रम trace_घड़ी */
		t = ns2usecs(ring_buffer_oldest_event_ts(trace_buf->buffer, cpu));
		usec_rem = करो_भाग(t, USEC_PER_SEC);
		trace_seq_म_लिखो(s, "oldest event ts: %5llu.%06lu\n",
								t, usec_rem);

		t = ns2usecs(ring_buffer_समय_stamp(trace_buf->buffer));
		usec_rem = करो_भाग(t, USEC_PER_SEC);
		trace_seq_म_लिखो(s, "now ts: %5llu.%06lu\n", t, usec_rem);
	पूर्ण अन्यथा अणु
		/* counter or tsc mode क्रम trace_घड़ी */
		trace_seq_म_लिखो(s, "oldest event ts: %llu\n",
				ring_buffer_oldest_event_ts(trace_buf->buffer, cpu));

		trace_seq_म_लिखो(s, "now ts: %llu\n",
				ring_buffer_समय_stamp(trace_buf->buffer));
	पूर्ण

	cnt = ring_buffer_dropped_events_cpu(trace_buf->buffer, cpu);
	trace_seq_म_लिखो(s, "dropped events: %ld\n", cnt);

	cnt = ring_buffer_पढ़ो_events_cpu(trace_buf->buffer, cpu);
	trace_seq_म_लिखो(s, "read events: %ld\n", cnt);

	count = simple_पढ़ो_from_buffer(ubuf, count, ppos,
					s->buffer, trace_seq_used(s));

	kमुक्त(s);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_stats_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.पढ़ो		= tracing_stats_पढ़ो,
	.llseek		= generic_file_llseek,
	.release	= tracing_release_generic_tr,
पूर्ण;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

अटल sमाप_प्रकार
tracing_पढ़ो_dyn_info(काष्ठा file *filp, अक्षर __user *ubuf,
		  माप_प्रकार cnt, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	अक्षर *buf;
	पूर्णांक r;

	/* 256 should be plenty to hold the amount needed */
	buf = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	r = scnम_लिखो(buf, 256, "%ld pages:%ld groups: %ld\n",
		      ftrace_update_tot_cnt,
		      ftrace_number_of_pages,
		      ftrace_number_of_groups);

	ret = simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations tracing_dyn_info_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= tracing_पढ़ो_dyn_info,
	.llseek		= generic_file_llseek,
पूर्ण;
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर defined(CONFIG_TRACER_SNAPSHOT) && defined(CONFIG_DYNAMIC_FTRACE)
अटल व्योम
ftrace_snapshot(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		व्योम *data)
अणु
	tracing_snapshot_instance(tr);
पूर्ण

अटल व्योम
ftrace_count_snapshot(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		      काष्ठा trace_array *tr, काष्ठा ftrace_probe_ops *ops,
		      व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	दीर्घ *count = शून्य;

	अगर (mapper)
		count = (दीर्घ *)ftrace_func_mapper_find_ip(mapper, ip);

	अगर (count) अणु

		अगर (*count <= 0)
			वापस;

		(*count)--;
	पूर्ण

	tracing_snapshot_instance(tr);
पूर्ण

अटल पूर्णांक
ftrace_snapshot_prपूर्णांक(काष्ठा seq_file *m, अचिन्हित दीर्घ ip,
		      काष्ठा ftrace_probe_ops *ops, व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;
	दीर्घ *count = शून्य;

	seq_म_लिखो(m, "%ps:", (व्योम *)ip);

	seq_माला_दो(m, "snapshot");

	अगर (mapper)
		count = (दीर्घ *)ftrace_func_mapper_find_ip(mapper, ip);

	अगर (count)
		seq_म_लिखो(m, ":count=%ld\n", *count);
	अन्यथा
		seq_माला_दो(m, ":unlimited\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
ftrace_snapshot_init(काष्ठा ftrace_probe_ops *ops, काष्ठा trace_array *tr,
		     अचिन्हित दीर्घ ip, व्योम *init_data, व्योम **data)
अणु
	काष्ठा ftrace_func_mapper *mapper = *data;

	अगर (!mapper) अणु
		mapper = allocate_ftrace_func_mapper();
		अगर (!mapper)
			वापस -ENOMEM;
		*data = mapper;
	पूर्ण

	वापस ftrace_func_mapper_add_ip(mapper, ip, init_data);
पूर्ण

अटल व्योम
ftrace_snapshot_मुक्त(काष्ठा ftrace_probe_ops *ops, काष्ठा trace_array *tr,
		     अचिन्हित दीर्घ ip, व्योम *data)
अणु
	काष्ठा ftrace_func_mapper *mapper = data;

	अगर (!ip) अणु
		अगर (!mapper)
			वापस;
		मुक्त_ftrace_func_mapper(mapper, शून्य);
		वापस;
	पूर्ण

	ftrace_func_mapper_हटाओ_ip(mapper, ip);
पूर्ण

अटल काष्ठा ftrace_probe_ops snapshot_probe_ops = अणु
	.func			= ftrace_snapshot,
	.prपूर्णांक			= ftrace_snapshot_prपूर्णांक,
पूर्ण;

अटल काष्ठा ftrace_probe_ops snapshot_count_probe_ops = अणु
	.func			= ftrace_count_snapshot,
	.prपूर्णांक			= ftrace_snapshot_prपूर्णांक,
	.init			= ftrace_snapshot_init,
	.मुक्त			= ftrace_snapshot_मुक्त,
पूर्ण;

अटल पूर्णांक
ftrace_trace_snapshot_callback(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
			       अक्षर *glob, अक्षर *cmd, अक्षर *param, पूर्णांक enable)
अणु
	काष्ठा ftrace_probe_ops *ops;
	व्योम *count = (व्योम *)-1;
	अक्षर *number;
	पूर्णांक ret;

	अगर (!tr)
		वापस -ENODEV;

	/* hash funcs only work with set_ftrace_filter */
	अगर (!enable)
		वापस -EINVAL;

	ops = param ? &snapshot_count_probe_ops :  &snapshot_probe_ops;

	अगर (glob[0] == '!')
		वापस unरेजिस्टर_ftrace_function_probe_func(glob+1, tr, ops);

	अगर (!param)
		जाओ out_reg;

	number = strsep(&param, ":");

	अगर (!म_माप(number))
		जाओ out_reg;

	/*
	 * We use the callback data field (which is a poपूर्णांकer)
	 * as our counter.
	 */
	ret = kम_से_अदीर्घ(number, 0, (अचिन्हित दीर्घ *)&count);
	अगर (ret)
		वापस ret;

 out_reg:
	ret = tracing_alloc_snapshot_instance(tr);
	अगर (ret < 0)
		जाओ out;

	ret = रेजिस्टर_ftrace_function_probe(glob, tr, ops, count);

 out:
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल काष्ठा ftrace_func_command ftrace_snapshot_cmd = अणु
	.name			= "snapshot",
	.func			= ftrace_trace_snapshot_callback,
पूर्ण;

अटल __init पूर्णांक रेजिस्टर_snapshot_cmd(व्योम)
अणु
	वापस रेजिस्टर_ftrace_command(&ftrace_snapshot_cmd);
पूर्ण
#अन्यथा
अटल अंतरभूत __init पूर्णांक रेजिस्टर_snapshot_cmd(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* defined(CONFIG_TRACER_SNAPSHOT) && defined(CONFIG_DYNAMIC_FTRACE) */

अटल काष्ठा dentry *tracing_get_dentry(काष्ठा trace_array *tr)
अणु
	अगर (WARN_ON(!tr->dir))
		वापस ERR_PTR(-ENODEV);

	/* Top directory uses शून्य as the parent */
	अगर (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		वापस शून्य;

	/* All sub buffers have a descriptor */
	वापस tr->dir;
पूर्ण

अटल काष्ठा dentry *tracing_dentry_percpu(काष्ठा trace_array *tr, पूर्णांक cpu)
अणु
	काष्ठा dentry *d_tracer;

	अगर (tr->percpu_dir)
		वापस tr->percpu_dir;

	d_tracer = tracing_get_dentry(tr);
	अगर (IS_ERR(d_tracer))
		वापस शून्य;

	tr->percpu_dir = tracefs_create_dir("per_cpu", d_tracer);

	MEM_FAIL(!tr->percpu_dir,
		  "Could not create tracefs directory 'per_cpu/%d'\n", cpu);

	वापस tr->percpu_dir;
पूर्ण

अटल काष्ठा dentry *
trace_create_cpu_file(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
		      व्योम *data, दीर्घ cpu, स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा dentry *ret = trace_create_file(name, mode, parent, data, fops);

	अगर (ret) /* See tracing_get_cpu() */
		d_inode(ret)->i_cdev = (व्योम *)(cpu + 1);
	वापस ret;
पूर्ण

अटल व्योम
tracing_init_tracefs_percpu(काष्ठा trace_array *tr, दीर्घ cpu)
अणु
	काष्ठा dentry *d_percpu = tracing_dentry_percpu(tr, cpu);
	काष्ठा dentry *d_cpu;
	अक्षर cpu_dir[30]; /* 30 अक्षरacters should be more than enough */

	अगर (!d_percpu)
		वापस;

	snम_लिखो(cpu_dir, 30, "cpu%ld", cpu);
	d_cpu = tracefs_create_dir(cpu_dir, d_percpu);
	अगर (!d_cpu) अणु
		pr_warn("Could not create tracefs '%s' entry\n", cpu_dir);
		वापस;
	पूर्ण

	/* per cpu trace_pipe */
	trace_create_cpu_file("trace_pipe", 0444, d_cpu,
				tr, cpu, &tracing_pipe_fops);

	/* per cpu trace */
	trace_create_cpu_file("trace", 0644, d_cpu,
				tr, cpu, &tracing_fops);

	trace_create_cpu_file("trace_pipe_raw", 0444, d_cpu,
				tr, cpu, &tracing_buffers_fops);

	trace_create_cpu_file("stats", 0444, d_cpu,
				tr, cpu, &tracing_stats_fops);

	trace_create_cpu_file("buffer_size_kb", 0444, d_cpu,
				tr, cpu, &tracing_entries_fops);

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	trace_create_cpu_file("snapshot", 0644, d_cpu,
				tr, cpu, &snapshot_fops);

	trace_create_cpu_file("snapshot_raw", 0444, d_cpu,
				tr, cpu, &snapshot_raw_fops);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_FTRACE_SELFTEST
/* Let selftest have access to अटल functions in this file */
#समावेश "trace_selftest.c"
#पूर्ण_अगर

अटल sमाप_प्रकार
trace_options_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
			loff_t *ppos)
अणु
	काष्ठा trace_option_dentry *topt = filp->निजी_data;
	अक्षर *buf;

	अगर (topt->flags->val & topt->opt->bit)
		buf = "1\n";
	अन्यथा
		buf = "0\n";

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार
trace_options_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
			 loff_t *ppos)
अणु
	काष्ठा trace_option_dentry *topt = filp->निजी_data;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	अगर (!!(topt->flags->val & topt->opt->bit) != val) अणु
		mutex_lock(&trace_types_lock);
		ret = __set_tracer_option(topt->tr, topt->flags,
					  topt->opt, !val);
		mutex_unlock(&trace_types_lock);
		अगर (ret)
			वापस ret;
	पूर्ण

	*ppos += cnt;

	वापस cnt;
पूर्ण


अटल स्थिर काष्ठा file_operations trace_options_fops = अणु
	.खोलो = tracing_खोलो_generic,
	.पढ़ो = trace_options_पढ़ो,
	.ग_लिखो = trace_options_ग_लिखो,
	.llseek	= generic_file_llseek,
पूर्ण;

/*
 * In order to pass in both the trace_array descriptor as well as the index
 * to the flag that the trace option file represents, the trace_array
 * has a अक्षरacter array of trace_flags_index[], which holds the index
 * of the bit क्रम the flag it represents. index[0] == 0, index[1] == 1, etc.
 * The address of this अक्षरacter array is passed to the flag option file
 * पढ़ो/ग_लिखो callbacks.
 *
 * In order to extract both the index and the trace_array descriptor,
 * get_tr_index() uses the following algorithm.
 *
 *   idx = *ptr;
 *
 * As the poपूर्णांकer itself contains the address of the index (remember
 * index[1] == 1).
 *
 * Then to get the trace_array descriptor, by subtracting that index
 * from the ptr, we get to the start of the index itself.
 *
 *   ptr - idx == &index[0]
 *
 * Then a simple container_of() from that poपूर्णांकer माला_लो us to the
 * trace_array descriptor.
 */
अटल व्योम get_tr_index(व्योम *data, काष्ठा trace_array **ptr,
			 अचिन्हित पूर्णांक *pindex)
अणु
	*pindex = *(अचिन्हित अक्षर *)data;

	*ptr = container_of(data - *pindex, काष्ठा trace_array,
			    trace_flags_index);
पूर्ण

अटल sमाप_प्रकार
trace_options_core_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
			loff_t *ppos)
अणु
	व्योम *tr_index = filp->निजी_data;
	काष्ठा trace_array *tr;
	अचिन्हित पूर्णांक index;
	अक्षर *buf;

	get_tr_index(tr_index, &tr, &index);

	अगर (tr->trace_flags & (1 << index))
		buf = "1\n";
	अन्यथा
		buf = "0\n";

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार
trace_options_core_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf, माप_प्रकार cnt,
			 loff_t *ppos)
अणु
	व्योम *tr_index = filp->निजी_data;
	काष्ठा trace_array *tr;
	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	get_tr_index(tr_index, &tr, &index);

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);
	ret = set_tracer_flag(tr, 1 << index, val);
	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	अगर (ret < 0)
		वापस ret;

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations trace_options_core_fops = अणु
	.खोलो = tracing_खोलो_generic,
	.पढ़ो = trace_options_core_पढ़ो,
	.ग_लिखो = trace_options_core_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

काष्ठा dentry *trace_create_file(स्थिर अक्षर *name,
				 umode_t mode,
				 काष्ठा dentry *parent,
				 व्योम *data,
				 स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा dentry *ret;

	ret = tracefs_create_file(name, mode, parent, data, fops);
	अगर (!ret)
		pr_warn("Could not create tracefs '%s' entry\n", name);

	वापस ret;
पूर्ण


अटल काष्ठा dentry *trace_options_init_dentry(काष्ठा trace_array *tr)
अणु
	काष्ठा dentry *d_tracer;

	अगर (tr->options)
		वापस tr->options;

	d_tracer = tracing_get_dentry(tr);
	अगर (IS_ERR(d_tracer))
		वापस शून्य;

	tr->options = tracefs_create_dir("options", d_tracer);
	अगर (!tr->options) अणु
		pr_warn("Could not create tracefs directory 'options'\n");
		वापस शून्य;
	पूर्ण

	वापस tr->options;
पूर्ण

अटल व्योम
create_trace_option_file(काष्ठा trace_array *tr,
			 काष्ठा trace_option_dentry *topt,
			 काष्ठा tracer_flags *flags,
			 काष्ठा tracer_opt *opt)
अणु
	काष्ठा dentry *t_options;

	t_options = trace_options_init_dentry(tr);
	अगर (!t_options)
		वापस;

	topt->flags = flags;
	topt->opt = opt;
	topt->tr = tr;

	topt->entry = trace_create_file(opt->name, 0644, t_options, topt,
				    &trace_options_fops);

पूर्ण

अटल व्योम
create_trace_option_files(काष्ठा trace_array *tr, काष्ठा tracer *tracer)
अणु
	काष्ठा trace_option_dentry *topts;
	काष्ठा trace_options *tr_topts;
	काष्ठा tracer_flags *flags;
	काष्ठा tracer_opt *opts;
	पूर्णांक cnt;
	पूर्णांक i;

	अगर (!tracer)
		वापस;

	flags = tracer->flags;

	अगर (!flags || !flags->opts)
		वापस;

	/*
	 * If this is an instance, only create flags क्रम tracers
	 * the instance may have.
	 */
	अगर (!trace_ok_क्रम_array(tracer, tr))
		वापस;

	क्रम (i = 0; i < tr->nr_topts; i++) अणु
		/* Make sure there's no duplicate flags. */
		अगर (WARN_ON_ONCE(tr->topts[i].tracer->flags == tracer->flags))
			वापस;
	पूर्ण

	opts = flags->opts;

	क्रम (cnt = 0; opts[cnt].name; cnt++)
		;

	topts = kसुस्मृति(cnt + 1, माप(*topts), GFP_KERNEL);
	अगर (!topts)
		वापस;

	tr_topts = kपुनः_स्मृति(tr->topts, माप(*tr->topts) * (tr->nr_topts + 1),
			    GFP_KERNEL);
	अगर (!tr_topts) अणु
		kमुक्त(topts);
		वापस;
	पूर्ण

	tr->topts = tr_topts;
	tr->topts[tr->nr_topts].tracer = tracer;
	tr->topts[tr->nr_topts].topts = topts;
	tr->nr_topts++;

	क्रम (cnt = 0; opts[cnt].name; cnt++) अणु
		create_trace_option_file(tr, &topts[cnt], flags,
					 &opts[cnt]);
		MEM_FAIL(topts[cnt].entry == शून्य,
			  "Failed to create trace option: %s",
			  opts[cnt].name);
	पूर्ण
पूर्ण

अटल काष्ठा dentry *
create_trace_option_core_file(काष्ठा trace_array *tr,
			      स्थिर अक्षर *option, दीर्घ index)
अणु
	काष्ठा dentry *t_options;

	t_options = trace_options_init_dentry(tr);
	अगर (!t_options)
		वापस शून्य;

	वापस trace_create_file(option, 0644, t_options,
				 (व्योम *)&tr->trace_flags_index[index],
				 &trace_options_core_fops);
पूर्ण

अटल व्योम create_trace_options_dir(काष्ठा trace_array *tr)
अणु
	काष्ठा dentry *t_options;
	bool top_level = tr == &global_trace;
	पूर्णांक i;

	t_options = trace_options_init_dentry(tr);
	अगर (!t_options)
		वापस;

	क्रम (i = 0; trace_options[i]; i++) अणु
		अगर (top_level ||
		    !((1 << i) & TOP_LEVEL_TRACE_FLAGS))
			create_trace_option_core_file(tr, trace_options[i], i);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
rb_simple_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
	       माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	अक्षर buf[64];
	पूर्णांक r;

	r = tracer_tracing_is_on(tr);
	r = प्र_लिखो(buf, "%d\n", r);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

अटल sमाप_प्रकार
rb_simple_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (buffer) अणु
		mutex_lock(&trace_types_lock);
		अगर (!!val == tracer_tracing_is_on(tr)) अणु
			val = 0; /* करो nothing */
		पूर्ण अन्यथा अगर (val) अणु
			tracer_tracing_on(tr);
			अगर (tr->current_trace->start)
				tr->current_trace->start(tr);
		पूर्ण अन्यथा अणु
			tracer_tracing_off(tr);
			अगर (tr->current_trace->stop)
				tr->current_trace->stop(tr);
		पूर्ण
		mutex_unlock(&trace_types_lock);
	पूर्ण

	(*ppos)++;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations rb_simple_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.पढ़ो		= rb_simple_पढ़ो,
	.ग_लिखो		= rb_simple_ग_लिखो,
	.release	= tracing_release_generic_tr,
	.llseek		= शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार
buffer_percent_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		    माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	अक्षर buf[64];
	पूर्णांक r;

	r = tr->buffer_percent;
	r = प्र_लिखो(buf, "%d\n", r);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

अटल sमाप_प्रकार
buffer_percent_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_array *tr = filp->निजी_data;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 100)
		वापस -EINVAL;

	अगर (!val)
		val = 1;

	tr->buffer_percent = val;

	(*ppos)++;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations buffer_percent_fops = अणु
	.खोलो		= tracing_खोलो_generic_tr,
	.पढ़ो		= buffer_percent_पढ़ो,
	.ग_लिखो		= buffer_percent_ग_लिखो,
	.release	= tracing_release_generic_tr,
	.llseek		= शेष_llseek,
पूर्ण;

अटल काष्ठा dentry *trace_instance_dir;

अटल व्योम
init_tracer_tracefs(काष्ठा trace_array *tr, काष्ठा dentry *d_tracer);

अटल पूर्णांक
allocate_trace_buffer(काष्ठा trace_array *tr, काष्ठा array_buffer *buf, पूर्णांक size)
अणु
	क्रमागत ring_buffer_flags rb_flags;

	rb_flags = tr->trace_flags & TRACE_ITER_OVERWRITE ? RB_FL_OVERWRITE : 0;

	buf->tr = tr;

	buf->buffer = ring_buffer_alloc(size, rb_flags);
	अगर (!buf->buffer)
		वापस -ENOMEM;

	buf->data = alloc_percpu(काष्ठा trace_array_cpu);
	अगर (!buf->data) अणु
		ring_buffer_मुक्त(buf->buffer);
		buf->buffer = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/* Allocate the first page क्रम all buffers */
	set_buffer_entries(&tr->array_buffer,
			   ring_buffer_size(tr->array_buffer.buffer, 0));

	वापस 0;
पूर्ण

अटल पूर्णांक allocate_trace_buffers(काष्ठा trace_array *tr, पूर्णांक size)
अणु
	पूर्णांक ret;

	ret = allocate_trace_buffer(tr, &tr->array_buffer, size);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	ret = allocate_trace_buffer(tr, &tr->max_buffer,
				    allocate_snapshot ? size : 1);
	अगर (MEM_FAIL(ret, "Failed to allocate trace buffer\n")) अणु
		ring_buffer_मुक्त(tr->array_buffer.buffer);
		tr->array_buffer.buffer = शून्य;
		मुक्त_percpu(tr->array_buffer.data);
		tr->array_buffer.data = शून्य;
		वापस -ENOMEM;
	पूर्ण
	tr->allocated_snapshot = allocate_snapshot;

	/*
	 * Only the top level trace array माला_लो its snapshot allocated
	 * from the kernel command line.
	 */
	allocate_snapshot = false;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम मुक्त_trace_buffer(काष्ठा array_buffer *buf)
अणु
	अगर (buf->buffer) अणु
		ring_buffer_मुक्त(buf->buffer);
		buf->buffer = शून्य;
		मुक्त_percpu(buf->data);
		buf->data = शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_trace_buffers(काष्ठा trace_array *tr)
अणु
	अगर (!tr)
		वापस;

	मुक्त_trace_buffer(&tr->array_buffer);

#अगर_घोषित CONFIG_TRACER_MAX_TRACE
	मुक्त_trace_buffer(&tr->max_buffer);
#पूर्ण_अगर
पूर्ण

अटल व्योम init_trace_flags_index(काष्ठा trace_array *tr)
अणु
	पूर्णांक i;

	/* Used by the trace options files */
	क्रम (i = 0; i < TRACE_FLAGS_MAX_SIZE; i++)
		tr->trace_flags_index[i] = i;
पूर्ण

अटल व्योम __update_tracer_options(काष्ठा trace_array *tr)
अणु
	काष्ठा tracer *t;

	क्रम (t = trace_types; t; t = t->next)
		add_tracer_options(tr, t);
पूर्ण

अटल व्योम update_tracer_options(काष्ठा trace_array *tr)
अणु
	mutex_lock(&trace_types_lock);
	__update_tracer_options(tr);
	mutex_unlock(&trace_types_lock);
पूर्ण

/* Must have trace_types_lock held */
काष्ठा trace_array *trace_array_find(स्थिर अक्षर *instance)
अणु
	काष्ठा trace_array *tr, *found = शून्य;

	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (tr->name && म_भेद(tr->name, instance) == 0) अणु
			found = tr;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

काष्ठा trace_array *trace_array_find_get(स्थिर अक्षर *instance)
अणु
	काष्ठा trace_array *tr;

	mutex_lock(&trace_types_lock);
	tr = trace_array_find(instance);
	अगर (tr)
		tr->ref++;
	mutex_unlock(&trace_types_lock);

	वापस tr;
पूर्ण

अटल पूर्णांक trace_array_create_dir(काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;

	tr->dir = tracefs_create_dir(tr->name, trace_instance_dir);
	अगर (!tr->dir)
		वापस -EINVAL;

	ret = event_trace_add_tracer(tr->dir, tr);
	अगर (ret)
		tracefs_हटाओ(tr->dir);

	init_tracer_tracefs(tr, tr->dir);
	__update_tracer_options(tr);

	वापस ret;
पूर्ण

अटल काष्ठा trace_array *trace_array_create(स्थिर अक्षर *name)
अणु
	काष्ठा trace_array *tr;
	पूर्णांक ret;

	ret = -ENOMEM;
	tr = kzalloc(माप(*tr), GFP_KERNEL);
	अगर (!tr)
		वापस ERR_PTR(ret);

	tr->name = kstrdup(name, GFP_KERNEL);
	अगर (!tr->name)
		जाओ out_मुक्त_tr;

	अगर (!alloc_cpumask_var(&tr->tracing_cpumask, GFP_KERNEL))
		जाओ out_मुक्त_tr;

	tr->trace_flags = global_trace.trace_flags & ~ZEROED_TRACE_FLAGS;

	cpumask_copy(tr->tracing_cpumask, cpu_all_mask);

	raw_spin_lock_init(&tr->start_lock);

	tr->max_lock = (arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;

	tr->current_trace = &nop_trace;

	INIT_LIST_HEAD(&tr->प्रणालीs);
	INIT_LIST_HEAD(&tr->events);
	INIT_LIST_HEAD(&tr->hist_vars);
	INIT_LIST_HEAD(&tr->err_log);

	अगर (allocate_trace_buffers(tr, trace_buf_size) < 0)
		जाओ out_मुक्त_tr;

	अगर (ftrace_allocate_ftrace_ops(tr) < 0)
		जाओ out_मुक्त_tr;

	ftrace_init_trace_array(tr);

	init_trace_flags_index(tr);

	अगर (trace_instance_dir) अणु
		ret = trace_array_create_dir(tr);
		अगर (ret)
			जाओ out_मुक्त_tr;
	पूर्ण अन्यथा
		__trace_early_add_events(tr);

	list_add(&tr->list, &ftrace_trace_arrays);

	tr->ref++;

	वापस tr;

 out_मुक्त_tr:
	ftrace_मुक्त_ftrace_ops(tr);
	मुक्त_trace_buffers(tr);
	मुक्त_cpumask_var(tr->tracing_cpumask);
	kमुक्त(tr->name);
	kमुक्त(tr);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक instance_सूची_गढ़ो(स्थिर अक्षर *name)
अणु
	काष्ठा trace_array *tr;
	पूर्णांक ret;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	ret = -EEXIST;
	अगर (trace_array_find(name))
		जाओ out_unlock;

	tr = trace_array_create(name);

	ret = PTR_ERR_OR_ZERO(tr);

out_unlock:
	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);
	वापस ret;
पूर्ण

/**
 * trace_array_get_by_name - Create/Lookup a trace array, given its name.
 * @name: The name of the trace array to be looked up/created.
 *
 * Returns poपूर्णांकer to trace array with given name.
 * शून्य, अगर it cannot be created.
 *
 * NOTE: This function increments the reference counter associated with the
 * trace array वापसed. This makes sure it cannot be मुक्तd जबतक in use.
 * Use trace_array_put() once the trace array is no दीर्घer needed.
 * If the trace_array is to be मुक्तd, trace_array_destroy() needs to
 * be called after the trace_array_put(), or simply let user space delete
 * it from the tracefs instances directory. But until the
 * trace_array_put() is called, user space can not delete it.
 *
 */
काष्ठा trace_array *trace_array_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा trace_array *tr;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (tr->name && म_भेद(tr->name, name) == 0)
			जाओ out_unlock;
	पूर्ण

	tr = trace_array_create(name);

	अगर (IS_ERR(tr))
		tr = शून्य;
out_unlock:
	अगर (tr)
		tr->ref++;

	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);
	वापस tr;
पूर्ण
EXPORT_SYMBOL_GPL(trace_array_get_by_name);

अटल पूर्णांक __हटाओ_instance(काष्ठा trace_array *tr)
अणु
	पूर्णांक i;

	/* Reference counter क्रम a newly created trace array = 1. */
	अगर (tr->ref > 1 || (tr->current_trace && tr->trace_ref))
		वापस -EBUSY;

	list_del(&tr->list);

	/* Disable all the flags that were enabled coming in */
	क्रम (i = 0; i < TRACE_FLAGS_MAX_SIZE; i++) अणु
		अगर ((1 << i) & ZEROED_TRACE_FLAGS)
			set_tracer_flag(tr, 1 << i, 0);
	पूर्ण

	tracing_set_nop(tr);
	clear_ftrace_function_probes(tr);
	event_trace_del_tracer(tr);
	ftrace_clear_pids(tr);
	ftrace_destroy_function_files(tr);
	tracefs_हटाओ(tr->dir);
	मुक्त_percpu(tr->last_func_repeats);
	मुक्त_trace_buffers(tr);

	क्रम (i = 0; i < tr->nr_topts; i++) अणु
		kमुक्त(tr->topts[i].topts);
	पूर्ण
	kमुक्त(tr->topts);

	मुक्त_cpumask_var(tr->tracing_cpumask);
	kमुक्त(tr->name);
	kमुक्त(tr);

	वापस 0;
पूर्ण

पूर्णांक trace_array_destroy(काष्ठा trace_array *this_tr)
अणु
	काष्ठा trace_array *tr;
	पूर्णांक ret;

	अगर (!this_tr)
		वापस -EINVAL;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	ret = -ENODEV;

	/* Making sure trace array exists beक्रमe destroying it. */
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (tr == this_tr) अणु
			ret = __हटाओ_instance(tr);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(trace_array_destroy);

अटल पूर्णांक instance_सूची_हटाओ(स्थिर अक्षर *name)
अणु
	काष्ठा trace_array *tr;
	पूर्णांक ret;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	ret = -ENODEV;
	tr = trace_array_find(name);
	अगर (tr)
		ret = __हटाओ_instance(tr);

	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

अटल __init व्योम create_trace_instances(काष्ठा dentry *d_tracer)
अणु
	काष्ठा trace_array *tr;

	trace_instance_dir = tracefs_create_instance_dir("instances", d_tracer,
							 instance_सूची_गढ़ो,
							 instance_सूची_हटाओ);
	अगर (MEM_FAIL(!trace_instance_dir, "Failed to create instances directory\n"))
		वापस;

	mutex_lock(&event_mutex);
	mutex_lock(&trace_types_lock);

	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (!tr->name)
			जारी;
		अगर (MEM_FAIL(trace_array_create_dir(tr) < 0,
			     "Failed to create instance directory\n"))
			अवरोध;
	पूर्ण

	mutex_unlock(&trace_types_lock);
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम
init_tracer_tracefs(काष्ठा trace_array *tr, काष्ठा dentry *d_tracer)
अणु
	काष्ठा trace_event_file *file;
	पूर्णांक cpu;

	trace_create_file("available_tracers", 0444, d_tracer,
			tr, &show_traces_fops);

	trace_create_file("current_tracer", 0644, d_tracer,
			tr, &set_tracer_fops);

	trace_create_file("tracing_cpumask", 0644, d_tracer,
			  tr, &tracing_cpumask_fops);

	trace_create_file("trace_options", 0644, d_tracer,
			  tr, &tracing_iter_fops);

	trace_create_file("trace", 0644, d_tracer,
			  tr, &tracing_fops);

	trace_create_file("trace_pipe", 0444, d_tracer,
			  tr, &tracing_pipe_fops);

	trace_create_file("buffer_size_kb", 0644, d_tracer,
			  tr, &tracing_entries_fops);

	trace_create_file("buffer_total_size_kb", 0444, d_tracer,
			  tr, &tracing_total_entries_fops);

	trace_create_file("free_buffer", 0200, d_tracer,
			  tr, &tracing_मुक्त_buffer_fops);

	trace_create_file("trace_marker", 0220, d_tracer,
			  tr, &tracing_mark_fops);

	file = __find_event_file(tr, "ftrace", "print");
	अगर (file && file->dir)
		trace_create_file("trigger", 0644, file->dir, file,
				  &event_trigger_fops);
	tr->trace_marker_file = file;

	trace_create_file("trace_marker_raw", 0220, d_tracer,
			  tr, &tracing_mark_raw_fops);

	trace_create_file("trace_clock", 0644, d_tracer, tr,
			  &trace_घड़ी_fops);

	trace_create_file("tracing_on", 0644, d_tracer,
			  tr, &rb_simple_fops);

	trace_create_file("timestamp_mode", 0444, d_tracer, tr,
			  &trace_समय_stamp_mode_fops);

	tr->buffer_percent = 50;

	trace_create_file("buffer_percent", 0444, d_tracer,
			tr, &buffer_percent_fops);

	create_trace_options_dir(tr);

#अगर defined(CONFIG_TRACER_MAX_TRACE) || defined(CONFIG_HWLAT_TRACER)
	trace_create_maxlat_file(tr, d_tracer);
#पूर्ण_अगर

	अगर (ftrace_create_function_files(tr, d_tracer))
		MEM_FAIL(1, "Could not allocate function filter files");

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
	trace_create_file("snapshot", 0644, d_tracer,
			  tr, &snapshot_fops);
#पूर्ण_अगर

	trace_create_file("error_log", 0644, d_tracer,
			  tr, &tracing_err_log_fops);

	क्रम_each_tracing_cpu(cpu)
		tracing_init_tracefs_percpu(tr, cpu);

	ftrace_init_tracefs(tr, d_tracer);
पूर्ण

अटल काष्ठा vfsmount *trace_स्वतःmount(काष्ठा dentry *mntpt, व्योम *ingore)
अणु
	काष्ठा vfsmount *mnt;
	काष्ठा file_प्रणाली_type *type;

	/*
	 * To मुख्यtain backward compatibility क्रम tools that mount
	 * debugfs to get to the tracing facility, tracefs is स्वतःmatically
	 * mounted to the debugfs/tracing directory.
	 */
	type = get_fs_type("tracefs");
	अगर (!type)
		वापस शून्य;
	mnt = vfs_submount(mntpt, type, "tracefs", शून्य);
	put_fileप्रणाली(type);
	अगर (IS_ERR(mnt))
		वापस शून्य;
	mntget(mnt);

	वापस mnt;
पूर्ण

/**
 * tracing_init_dentry - initialize top level trace array
 *
 * This is called when creating files or directories in the tracing
 * directory. It is called via fs_initcall() by any of the boot up code
 * and expects to वापस the dentry of the top level tracing directory.
 */
पूर्णांक tracing_init_dentry(व्योम)
अणु
	काष्ठा trace_array *tr = &global_trace;

	अगर (security_locked_करोwn(LOCKDOWN_TRACEFS)) अणु
		pr_warn("Tracing disabled due to lockdown\n");
		वापस -EPERM;
	पूर्ण

	/* The top level trace array uses  शून्य as parent */
	अगर (tr->dir)
		वापस 0;

	अगर (WARN_ON(!tracefs_initialized()))
		वापस -ENODEV;

	/*
	 * As there may still be users that expect the tracing
	 * files to exist in debugfs/tracing, we must स्वतःmount
	 * the tracefs file प्रणाली there, so older tools still
	 * work with the newer kernel.
	 */
	tr->dir = debugfs_create_स्वतःmount("tracing", शून्य,
					   trace_स्वतःmount, शून्य);

	वापस 0;
पूर्ण

बाह्य काष्ठा trace_eval_map *__start_ftrace_eval_maps[];
बाह्य काष्ठा trace_eval_map *__stop_ftrace_eval_maps[];

अटल काष्ठा workqueue_काष्ठा *eval_map_wq __initdata;
अटल काष्ठा work_काष्ठा eval_map_work __initdata;

अटल व्योम __init eval_map_work_func(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक len;

	len = __stop_ftrace_eval_maps - __start_ftrace_eval_maps;
	trace_insert_eval_map(शून्य, __start_ftrace_eval_maps, len);
पूर्ण

अटल पूर्णांक __init trace_eval_init(व्योम)
अणु
	INIT_WORK(&eval_map_work, eval_map_work_func);

	eval_map_wq = alloc_workqueue("eval_map_wq", WQ_UNBOUND, 0);
	अगर (!eval_map_wq) अणु
		pr_err("Unable to allocate eval_map_wq\n");
		/* Do work here */
		eval_map_work_func(&eval_map_work);
		वापस -ENOMEM;
	पूर्ण

	queue_work(eval_map_wq, &eval_map_work);
	वापस 0;
पूर्ण

अटल पूर्णांक __init trace_eval_sync(व्योम)
अणु
	/* Make sure the eval map updates are finished */
	अगर (eval_map_wq)
		destroy_workqueue(eval_map_wq);
	वापस 0;
पूर्ण

late_initcall_sync(trace_eval_sync);


#अगर_घोषित CONFIG_MODULES
अटल व्योम trace_module_add_evals(काष्ठा module *mod)
अणु
	अगर (!mod->num_trace_evals)
		वापस;

	/*
	 * Modules with bad taपूर्णांक करो not have events created, करो
	 * not bother with क्रमागतs either.
	 */
	अगर (trace_module_has_bad_taपूर्णांक(mod))
		वापस;

	trace_insert_eval_map(mod, mod->trace_evals, mod->num_trace_evals);
पूर्ण

#अगर_घोषित CONFIG_TRACE_EVAL_MAP_खाता
अटल व्योम trace_module_हटाओ_evals(काष्ठा module *mod)
अणु
	जोड़ trace_eval_map_item *map;
	जोड़ trace_eval_map_item **last = &trace_eval_maps;

	अगर (!mod->num_trace_evals)
		वापस;

	mutex_lock(&trace_eval_mutex);

	map = trace_eval_maps;

	जबतक (map) अणु
		अगर (map->head.mod == mod)
			अवरोध;
		map = trace_eval_jmp_to_tail(map);
		last = &map->tail.next;
		map = map->tail.next;
	पूर्ण
	अगर (!map)
		जाओ out;

	*last = trace_eval_jmp_to_tail(map)->tail.next;
	kमुक्त(map);
 out:
	mutex_unlock(&trace_eval_mutex);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम trace_module_हटाओ_evals(काष्ठा module *mod) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRACE_EVAL_MAP_खाता */

अटल पूर्णांक trace_module_notअगरy(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;

	चयन (val) अणु
	हाल MODULE_STATE_COMING:
		trace_module_add_evals(mod);
		अवरोध;
	हाल MODULE_STATE_GOING:
		trace_module_हटाओ_evals(mod);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block trace_module_nb = अणु
	.notअगरier_call = trace_module_notअगरy,
	.priority = 0,
पूर्ण;
#पूर्ण_अगर /* CONFIG_MODULES */

अटल __init पूर्णांक tracer_init_tracefs(व्योम)
अणु
	पूर्णांक ret;

	trace_access_lock_init();

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	event_trace_init();

	init_tracer_tracefs(&global_trace, शून्य);
	ftrace_init_tracefs_toplevel(&global_trace, शून्य);

	trace_create_file("tracing_thresh", 0644, शून्य,
			&global_trace, &tracing_thresh_fops);

	trace_create_file("README", 0444, शून्य,
			शून्य, &tracing_पढ़ोme_fops);

	trace_create_file("saved_cmdlines", 0444, शून्य,
			शून्य, &tracing_saved_cmdlines_fops);

	trace_create_file("saved_cmdlines_size", 0644, शून्य,
			  शून्य, &tracing_saved_cmdlines_size_fops);

	trace_create_file("saved_tgids", 0444, शून्य,
			शून्य, &tracing_saved_tgids_fops);

	trace_eval_init();

	trace_create_eval_file(शून्य);

#अगर_घोषित CONFIG_MODULES
	रेजिस्टर_module_notअगरier(&trace_module_nb);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	trace_create_file("dyn_ftrace_total_info", 0444, शून्य,
			शून्य, &tracing_dyn_info_fops);
#पूर्ण_अगर

	create_trace_instances(शून्य);

	update_tracer_options(&global_trace);

	वापस 0;
पूर्ण

अटल पूर्णांक trace_panic_handler(काष्ठा notअगरier_block *this,
			       अचिन्हित दीर्घ event, व्योम *unused)
अणु
	अगर (ftrace_dump_on_oops)
		ftrace_dump(ftrace_dump_on_oops);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block trace_panic_notअगरier = अणु
	.notअगरier_call  = trace_panic_handler,
	.next           = शून्य,
	.priority       = 150   /* priority: पूर्णांक_उच्च >= x >= 0 */
पूर्ण;

अटल पूर्णांक trace_die_handler(काष्ठा notअगरier_block *self,
			     अचिन्हित दीर्घ val,
			     व्योम *data)
अणु
	चयन (val) अणु
	हाल DIE_OOPS:
		अगर (ftrace_dump_on_oops)
			ftrace_dump(ftrace_dump_on_oops);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block trace_die_notअगरier = अणु
	.notअगरier_call = trace_die_handler,
	.priority = 200
पूर्ण;

/*
 * prपूर्णांकk is set to max of 1024, we really करोn't need it that big.
 * Nothing should be prपूर्णांकing 1000 अक्षरacters anyway.
 */
#घोषणा TRACE_MAX_PRINT		1000

/*
 * Define here KERN_TRACE so that we have one place to modअगरy
 * it अगर we decide to change what log level the ftrace dump
 * should be at.
 */
#घोषणा KERN_TRACE		KERN_EMERG

व्योम
trace_prपूर्णांकk_seq(काष्ठा trace_seq *s)
अणु
	/* Probably should prपूर्णांक a warning here. */
	अगर (s->seq.len >= TRACE_MAX_PRINT)
		s->seq.len = TRACE_MAX_PRINT;

	/*
	 * More paranoid code. Although the buffer size is set to
	 * PAGE_SIZE, and TRACE_MAX_PRINT is 1000, this is just
	 * an extra layer of protection.
	 */
	अगर (WARN_ON_ONCE(s->seq.len >= s->seq.size))
		s->seq.len = s->seq.size - 1;

	/* should be zero ended, but we are paranoid. */
	s->buffer[s->seq.len] = 0;

	prपूर्णांकk(KERN_TRACE "%s", s->buffer);

	trace_seq_init(s);
पूर्ण

व्योम trace_init_global_iter(काष्ठा trace_iterator *iter)
अणु
	iter->tr = &global_trace;
	iter->trace = iter->tr->current_trace;
	iter->cpu_file = RING_BUFFER_ALL_CPUS;
	iter->array_buffer = &global_trace.array_buffer;

	अगर (iter->trace && iter->trace->खोलो)
		iter->trace->खोलो(iter);

	/* Annotate start of buffers अगर we had overruns */
	अगर (ring_buffer_overruns(iter->array_buffer->buffer))
		iter->iter_flags |= TRACE_खाता_ANNOTATE;

	/* Output in nanoseconds only अगर we are using a घड़ी in nanoseconds. */
	अगर (trace_घड़ीs[iter->tr->घड़ी_id].in_ns)
		iter->iter_flags |= TRACE_खाता_TIME_IN_NS;
पूर्ण

व्योम ftrace_dump(क्रमागत ftrace_dump_mode oops_dump_mode)
अणु
	/* use अटल because iter can be a bit big क्रम the stack */
	अटल काष्ठा trace_iterator iter;
	अटल atomic_t dump_running;
	काष्ठा trace_array *tr = &global_trace;
	अचिन्हित पूर्णांक old_userobj;
	अचिन्हित दीर्घ flags;
	पूर्णांक cnt = 0, cpu;

	/* Only allow one dump user at a समय. */
	अगर (atomic_inc_वापस(&dump_running) != 1) अणु
		atomic_dec(&dump_running);
		वापस;
	पूर्ण

	/*
	 * Always turn off tracing when we dump.
	 * We करोn't need to show trace output of what happens
	 * between multiple crashes.
	 *
	 * If the user करोes a sysrq-z, then they can re-enable
	 * tracing with echo 1 > tracing_on.
	 */
	tracing_off();

	local_irq_save(flags);
	prपूर्णांकk_nmi_direct_enter();

	/* Simulate the iterator */
	trace_init_global_iter(&iter);
	/* Can not use kदो_स्मृति क्रम iter.temp and iter.fmt */
	iter.temp = अटल_temp_buf;
	iter.temp_size = STATIC_TEMP_BUF_SIZE;
	iter.fmt = अटल_fmt_buf;
	iter.fmt_size = STATIC_FMT_BUF_SIZE;

	क्रम_each_tracing_cpu(cpu) अणु
		atomic_inc(&per_cpu_ptr(iter.array_buffer->data, cpu)->disabled);
	पूर्ण

	old_userobj = tr->trace_flags & TRACE_ITER_SYM_USEROBJ;

	/* करोn't look at user memory in panic mode */
	tr->trace_flags &= ~TRACE_ITER_SYM_USEROBJ;

	चयन (oops_dump_mode) अणु
	हाल DUMP_ALL:
		iter.cpu_file = RING_BUFFER_ALL_CPUS;
		अवरोध;
	हाल DUMP_ORIG:
		iter.cpu_file = raw_smp_processor_id();
		अवरोध;
	हाल DUMP_NONE:
		जाओ out_enable;
	शेष:
		prपूर्णांकk(KERN_TRACE "Bad dumping mode, switching to all CPUs dump\n");
		iter.cpu_file = RING_BUFFER_ALL_CPUS;
	पूर्ण

	prपूर्णांकk(KERN_TRACE "Dumping ftrace buffer:\n");

	/* Did function tracer alपढ़ोy get disabled? */
	अगर (ftrace_is_dead()) अणु
		prपूर्णांकk("# WARNING: FUNCTION TRACING IS CORRUPTED\n");
		prपूर्णांकk("#          MAY BE MISSING FUNCTION EVENTS\n");
	पूर्ण

	/*
	 * We need to stop all tracing on all CPUS to पढ़ो
	 * the next buffer. This is a bit expensive, but is
	 * not करोne often. We fill all what we can पढ़ो,
	 * and then release the locks again.
	 */

	जबतक (!trace_empty(&iter)) अणु

		अगर (!cnt)
			prपूर्णांकk(KERN_TRACE "---------------------------------\n");

		cnt++;

		trace_iterator_reset(&iter);
		iter.iter_flags |= TRACE_खाता_LAT_FMT;

		अगर (trace_find_next_entry_inc(&iter) != शून्य) अणु
			पूर्णांक ret;

			ret = prपूर्णांक_trace_line(&iter);
			अगर (ret != TRACE_TYPE_NO_CONSUME)
				trace_consume(&iter);
		पूर्ण
		touch_nmi_watchकरोg();

		trace_prपूर्णांकk_seq(&iter.seq);
	पूर्ण

	अगर (!cnt)
		prपूर्णांकk(KERN_TRACE "   (ftrace buffer empty)\n");
	अन्यथा
		prपूर्णांकk(KERN_TRACE "---------------------------------\n");

 out_enable:
	tr->trace_flags |= old_userobj;

	क्रम_each_tracing_cpu(cpu) अणु
		atomic_dec(&per_cpu_ptr(iter.array_buffer->data, cpu)->disabled);
	पूर्ण
	atomic_dec(&dump_running);
	prपूर्णांकk_nmi_direct_निकास();
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_dump);

#घोषणा WRITE_बफ_मानE  4096

sमाप_प्रकार trace_parse_run_command(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos,
				पूर्णांक (*createfn)(स्थिर अक्षर *))
अणु
	अक्षर *kbuf, *buf, *पंचांगp;
	पूर्णांक ret = 0;
	माप_प्रकार करोne = 0;
	माप_प्रकार size;

	kbuf = kदो_स्मृति(WRITE_बफ_मानE, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	जबतक (करोne < count) अणु
		size = count - करोne;

		अगर (size >= WRITE_बफ_मानE)
			size = WRITE_बफ_मानE - 1;

		अगर (copy_from_user(kbuf, buffer + करोne, size)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		kbuf[size] = '\0';
		buf = kbuf;
		करो अणु
			पंचांगp = म_अक्षर(buf, '\n');
			अगर (पंचांगp) अणु
				*पंचांगp = '\0';
				size = पंचांगp - buf + 1;
			पूर्ण अन्यथा अणु
				size = म_माप(buf);
				अगर (करोne + size < count) अणु
					अगर (buf != kbuf)
						अवरोध;
					/* This can accept WRITE_बफ_मानE - 2 ('\n' + '\0') */
					pr_warn("Line length is too long: Should be less than %d\n",
						WRITE_बफ_मानE - 2);
					ret = -EINVAL;
					जाओ out;
				पूर्ण
			पूर्ण
			करोne += size;

			/* Remove comments */
			पंचांगp = म_अक्षर(buf, '#');

			अगर (पंचांगp)
				*पंचांगp = '\0';

			ret = createfn(buf);
			अगर (ret)
				जाओ out;
			buf += size;

		पूर्ण जबतक (करोne < count);
	पूर्ण
	ret = करोne;

out:
	kमुक्त(kbuf);

	वापस ret;
पूर्ण

__init अटल पूर्णांक tracer_alloc_buffers(व्योम)
अणु
	पूर्णांक ring_buf_size;
	पूर्णांक ret = -ENOMEM;


	अगर (security_locked_करोwn(LOCKDOWN_TRACEFS)) अणु
		pr_warn("Tracing disabled due to lockdown\n");
		वापस -EPERM;
	पूर्ण

	/*
	 * Make sure we करोn't accidentally add more trace options
	 * than we have bits क्रम.
	 */
	BUILD_BUG_ON(TRACE_ITER_LAST_BIT > TRACE_FLAGS_MAX_SIZE);

	अगर (!alloc_cpumask_var(&tracing_buffer_mask, GFP_KERNEL))
		जाओ out;

	अगर (!alloc_cpumask_var(&global_trace.tracing_cpumask, GFP_KERNEL))
		जाओ out_मुक्त_buffer_mask;

	/* Only allocate trace_prपूर्णांकk buffers अगर a trace_prपूर्णांकk exists */
	अगर (&__stop___trace_bprपूर्णांकk_fmt != &__start___trace_bprपूर्णांकk_fmt)
		/* Must be called beक्रमe global_trace.buffer is allocated */
		trace_prपूर्णांकk_init_buffers();

	/* To save memory, keep the ring buffer size to its minimum */
	अगर (ring_buffer_expanded)
		ring_buf_size = trace_buf_size;
	अन्यथा
		ring_buf_size = 1;

	cpumask_copy(tracing_buffer_mask, cpu_possible_mask);
	cpumask_copy(global_trace.tracing_cpumask, cpu_all_mask);

	raw_spin_lock_init(&global_trace.start_lock);

	/*
	 * The prepare callbacks allocates some memory क्रम the ring buffer. We
	 * करोn't मुक्त the buffer अगर the CPU goes करोwn. If we were to मुक्त
	 * the buffer, then the user would lose any trace that was in the
	 * buffer. The memory will be हटाओd once the "instance" is हटाओd.
	 */
	ret = cpuhp_setup_state_multi(CPUHP_TRACE_RB_PREPARE,
				      "trace/RB:preapre", trace_rb_cpu_prepare,
				      शून्य);
	अगर (ret < 0)
		जाओ out_मुक्त_cpumask;
	/* Used क्रम event triggers */
	ret = -ENOMEM;
	temp_buffer = ring_buffer_alloc(PAGE_SIZE, RB_FL_OVERWRITE);
	अगर (!temp_buffer)
		जाओ out_rm_hp_state;

	अगर (trace_create_savedcmd() < 0)
		जाओ out_मुक्त_temp_buffer;

	/* TODO: make the number of buffers hot pluggable with CPUS */
	अगर (allocate_trace_buffers(&global_trace, ring_buf_size) < 0) अणु
		MEM_FAIL(1, "tracer: failed to allocate ring buffer!\n");
		जाओ out_मुक्त_savedcmd;
	पूर्ण

	अगर (global_trace.buffer_disabled)
		tracing_off();

	अगर (trace_boot_घड़ी) अणु
		ret = tracing_set_घड़ी(&global_trace, trace_boot_घड़ी);
		अगर (ret < 0)
			pr_warn("Trace clock %s not defined, going back to default\n",
				trace_boot_घड़ी);
	पूर्ण

	/*
	 * रेजिस्टर_tracer() might reference current_trace, so it
	 * needs to be set beक्रमe we रेजिस्टर anything. This is
	 * just a bootstrap of current_trace anyway.
	 */
	global_trace.current_trace = &nop_trace;

	global_trace.max_lock = (arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;

	ftrace_init_global_array_ops(&global_trace);

	init_trace_flags_index(&global_trace);

	रेजिस्टर_tracer(&nop_trace);

	/* Function tracing may start here (via kernel command line) */
	init_function_trace();

	/* All seems OK, enable tracing */
	tracing_disabled = 0;

	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &trace_panic_notअगरier);

	रेजिस्टर_die_notअगरier(&trace_die_notअगरier);

	global_trace.flags = TRACE_ARRAY_FL_GLOBAL;

	INIT_LIST_HEAD(&global_trace.प्रणालीs);
	INIT_LIST_HEAD(&global_trace.events);
	INIT_LIST_HEAD(&global_trace.hist_vars);
	INIT_LIST_HEAD(&global_trace.err_log);
	list_add(&global_trace.list, &ftrace_trace_arrays);

	apply_trace_boot_options();

	रेजिस्टर_snapshot_cmd();

	test_can_verअगरy();

	वापस 0;

out_मुक्त_savedcmd:
	मुक्त_saved_cmdlines_buffer(savedcmd);
out_मुक्त_temp_buffer:
	ring_buffer_मुक्त(temp_buffer);
out_rm_hp_state:
	cpuhp_हटाओ_multi_state(CPUHP_TRACE_RB_PREPARE);
out_मुक्त_cpumask:
	मुक्त_cpumask_var(global_trace.tracing_cpumask);
out_मुक्त_buffer_mask:
	मुक्त_cpumask_var(tracing_buffer_mask);
out:
	वापस ret;
पूर्ण

व्योम __init early_trace_init(व्योम)
अणु
	अगर (tracepoपूर्णांक_prपूर्णांकk) अणु
		tracepoपूर्णांक_prपूर्णांक_iter =
			kzalloc(माप(*tracepoपूर्णांक_prपूर्णांक_iter), GFP_KERNEL);
		अगर (MEM_FAIL(!tracepoपूर्णांक_prपूर्णांक_iter,
			     "Failed to allocate trace iterator\n"))
			tracepoपूर्णांक_prपूर्णांकk = 0;
		अन्यथा
			अटल_key_enable(&tracepoपूर्णांक_prपूर्णांकk_key.key);
	पूर्ण
	tracer_alloc_buffers();
पूर्ण

व्योम __init trace_init(व्योम)
अणु
	trace_event_init();
पूर्ण

__init अटल पूर्णांक clear_boot_tracer(व्योम)
अणु
	/*
	 * The शेष tracer at boot buffer is an init section.
	 * This function is called in lateinit. If we did not
	 * find the boot tracer, then clear it out, to prevent
	 * later registration from accessing the buffer that is
	 * about to be मुक्तd.
	 */
	अगर (!शेष_bootup_tracer)
		वापस 0;

	prपूर्णांकk(KERN_INFO "ftrace bootup tracer '%s' not registered.\n",
	       शेष_bootup_tracer);
	शेष_bootup_tracer = शून्य;

	वापस 0;
पूर्ण

fs_initcall(tracer_init_tracefs);
late_initcall_sync(clear_boot_tracer);

#अगर_घोषित CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
__init अटल पूर्णांक tracing_set_शेष_घड़ी(व्योम)
अणु
	/* sched_घड़ी_stable() is determined in late_initcall */
	अगर (!trace_boot_घड़ी && !sched_घड़ी_stable()) अणु
		अगर (security_locked_करोwn(LOCKDOWN_TRACEFS)) अणु
			pr_warn("Can not set tracing clock due to lockdown\n");
			वापस -EPERM;
		पूर्ण

		prपूर्णांकk(KERN_WARNING
		       "Unstable clock detected, switching default tracing clock to \"global\"\n"
		       "If you want to keep using the local clock, then add:\n"
		       "  \"trace_clock=local\"\n"
		       "on the kernel command line\n");
		tracing_set_घड़ी(&global_trace, "global");
	पूर्ण

	वापस 0;
पूर्ण
late_initcall_sync(tracing_set_शेष_घड़ी);
#पूर्ण_अगर
