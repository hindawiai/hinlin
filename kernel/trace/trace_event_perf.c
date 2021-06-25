<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace event based perf event profiling/tracing
 *
 * Copyright (C) 2009 Red Hat Inc, Peter Zijlstra
 * Copyright (C) 2009-2010 Frederic Weisbecker <fweisbec@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/security.h>
#समावेश "trace.h"
#समावेश "trace_probe.h"

अटल अक्षर __percpu *perf_trace_buf[PERF_NR_CONTEXTS];

/*
 * Force it to be aligned to अचिन्हित दीर्घ to aव्योम misaligned accesses
 * surprises
 */
प्रकार typeof(अचिन्हित दीर्घ [PERF_MAX_TRACE_SIZE / माप(अचिन्हित दीर्घ)])
	perf_trace_t;

/* Count the events in use (per event id, not per instance) */
अटल पूर्णांक	total_ref_count;

अटल पूर्णांक perf_trace_event_perm(काष्ठा trace_event_call *tp_event,
				 काष्ठा perf_event *p_event)
अणु
	पूर्णांक ret;

	अगर (tp_event->perf_perm) अणु
		ret = tp_event->perf_perm(tp_event, p_event);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * We checked and allowed to create parent,
	 * allow children without checking.
	 */
	अगर (p_event->parent)
		वापस 0;

	/*
	 * It's ok to check current process (owner) permissions in here,
	 * because code below is called only via perf_event_खोलो syscall.
	 */

	/* The ftrace function trace is allowed only क्रम root. */
	अगर (ftrace_event_is_function(tp_event)) अणु
		ret = perf_allow_tracepoपूर्णांक(&p_event->attr);
		अगर (ret)
			वापस ret;

		अगर (!is_sampling_event(p_event))
			वापस 0;

		/*
		 * We करोn't allow user space callchains क्रम  function trace
		 * event, due to issues with page faults जबतक tracing page
		 * fault handler and its overall trickiness nature.
		 */
		अगर (!p_event->attr.exclude_callchain_user)
			वापस -EINVAL;

		/*
		 * Same reason to disable user stack dump as क्रम user space
		 * callchains above.
		 */
		अगर (p_event->attr.sample_type & PERF_SAMPLE_STACK_USER)
			वापस -EINVAL;
	पूर्ण

	/* No tracing, just counting, so no obvious leak */
	अगर (!(p_event->attr.sample_type & PERF_SAMPLE_RAW))
		वापस 0;

	/* Some events are ok to be traced by non-root users... */
	अगर (p_event->attach_state == PERF_ATTACH_TASK) अणु
		अगर (tp_event->flags & TRACE_EVENT_FL_CAP_ANY)
			वापस 0;
	पूर्ण

	/*
	 * ...otherwise raw tracepoपूर्णांक data can be a severe data leak,
	 * only allow root to have these.
	 */
	ret = perf_allow_tracepoपूर्णांक(&p_event->attr);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_trace_event_reg(काष्ठा trace_event_call *tp_event,
				काष्ठा perf_event *p_event)
अणु
	काष्ठा hlist_head __percpu *list;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक cpu;

	p_event->tp_event = tp_event;
	अगर (tp_event->perf_refcount++ > 0)
		वापस 0;

	list = alloc_percpu(काष्ठा hlist_head);
	अगर (!list)
		जाओ fail;

	क्रम_each_possible_cpu(cpu)
		INIT_HLIST_HEAD(per_cpu_ptr(list, cpu));

	tp_event->perf_events = list;

	अगर (!total_ref_count) अणु
		अक्षर __percpu *buf;
		पूर्णांक i;

		क्रम (i = 0; i < PERF_NR_CONTEXTS; i++) अणु
			buf = (अक्षर __percpu *)alloc_percpu(perf_trace_t);
			अगर (!buf)
				जाओ fail;

			perf_trace_buf[i] = buf;
		पूर्ण
	पूर्ण

	ret = tp_event->class->reg(tp_event, TRACE_REG_PERF_REGISTER, शून्य);
	अगर (ret)
		जाओ fail;

	total_ref_count++;
	वापस 0;

fail:
	अगर (!total_ref_count) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PERF_NR_CONTEXTS; i++) अणु
			मुक्त_percpu(perf_trace_buf[i]);
			perf_trace_buf[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (!--tp_event->perf_refcount) अणु
		मुक्त_percpu(tp_event->perf_events);
		tp_event->perf_events = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम perf_trace_event_unreg(काष्ठा perf_event *p_event)
अणु
	काष्ठा trace_event_call *tp_event = p_event->tp_event;
	पूर्णांक i;

	अगर (--tp_event->perf_refcount > 0)
		जाओ out;

	tp_event->class->reg(tp_event, TRACE_REG_PERF_UNREGISTER, शून्य);

	/*
	 * Ensure our callback won't be called anymore. The buffers
	 * will be मुक्तd after that.
	 */
	tracepoपूर्णांक_synchronize_unरेजिस्टर();

	मुक्त_percpu(tp_event->perf_events);
	tp_event->perf_events = शून्य;

	अगर (!--total_ref_count) अणु
		क्रम (i = 0; i < PERF_NR_CONTEXTS; i++) अणु
			मुक्त_percpu(perf_trace_buf[i]);
			perf_trace_buf[i] = शून्य;
		पूर्ण
	पूर्ण
out:
	module_put(tp_event->mod);
पूर्ण

अटल पूर्णांक perf_trace_event_खोलो(काष्ठा perf_event *p_event)
अणु
	काष्ठा trace_event_call *tp_event = p_event->tp_event;
	वापस tp_event->class->reg(tp_event, TRACE_REG_PERF_OPEN, p_event);
पूर्ण

अटल व्योम perf_trace_event_बंद(काष्ठा perf_event *p_event)
अणु
	काष्ठा trace_event_call *tp_event = p_event->tp_event;
	tp_event->class->reg(tp_event, TRACE_REG_PERF_CLOSE, p_event);
पूर्ण

अटल पूर्णांक perf_trace_event_init(काष्ठा trace_event_call *tp_event,
				 काष्ठा perf_event *p_event)
अणु
	पूर्णांक ret;

	ret = perf_trace_event_perm(tp_event, p_event);
	अगर (ret)
		वापस ret;

	ret = perf_trace_event_reg(tp_event, p_event);
	अगर (ret)
		वापस ret;

	ret = perf_trace_event_खोलो(p_event);
	अगर (ret) अणु
		perf_trace_event_unreg(p_event);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_trace_init(काष्ठा perf_event *p_event)
अणु
	काष्ठा trace_event_call *tp_event;
	u64 event_id = p_event->attr.config;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&event_mutex);
	list_क्रम_each_entry(tp_event, &ftrace_events, list) अणु
		अगर (tp_event->event.type == event_id &&
		    tp_event->class && tp_event->class->reg &&
		    try_module_get(tp_event->mod)) अणु
			ret = perf_trace_event_init(tp_event, p_event);
			अगर (ret)
				module_put(tp_event->mod);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

व्योम perf_trace_destroy(काष्ठा perf_event *p_event)
अणु
	mutex_lock(&event_mutex);
	perf_trace_event_बंद(p_event);
	perf_trace_event_unreg(p_event);
	mutex_unlock(&event_mutex);
पूर्ण

#अगर_घोषित CONFIG_KPROBE_EVENTS
पूर्णांक perf_kprobe_init(काष्ठा perf_event *p_event, bool is_retprobe)
अणु
	पूर्णांक ret;
	अक्षर *func = शून्य;
	काष्ठा trace_event_call *tp_event;

	अगर (p_event->attr.kprobe_func) अणु
		func = kzalloc(KSYM_NAME_LEN, GFP_KERNEL);
		अगर (!func)
			वापस -ENOMEM;
		ret = म_नकलन_from_user(
			func, u64_to_user_ptr(p_event->attr.kprobe_func),
			KSYM_NAME_LEN);
		अगर (ret == KSYM_NAME_LEN)
			ret = -E2BIG;
		अगर (ret < 0)
			जाओ out;

		अगर (func[0] == '\0') अणु
			kमुक्त(func);
			func = शून्य;
		पूर्ण
	पूर्ण

	tp_event = create_local_trace_kprobe(
		func, (व्योम *)(अचिन्हित दीर्घ)(p_event->attr.kprobe_addr),
		p_event->attr.probe_offset, is_retprobe);
	अगर (IS_ERR(tp_event)) अणु
		ret = PTR_ERR(tp_event);
		जाओ out;
	पूर्ण

	mutex_lock(&event_mutex);
	ret = perf_trace_event_init(tp_event, p_event);
	अगर (ret)
		destroy_local_trace_kprobe(tp_event);
	mutex_unlock(&event_mutex);
out:
	kमुक्त(func);
	वापस ret;
पूर्ण

व्योम perf_kprobe_destroy(काष्ठा perf_event *p_event)
अणु
	mutex_lock(&event_mutex);
	perf_trace_event_बंद(p_event);
	perf_trace_event_unreg(p_event);
	mutex_unlock(&event_mutex);

	destroy_local_trace_kprobe(p_event->tp_event);
पूर्ण
#पूर्ण_अगर /* CONFIG_KPROBE_EVENTS */

#अगर_घोषित CONFIG_UPROBE_EVENTS
पूर्णांक perf_uprobe_init(काष्ठा perf_event *p_event,
		     अचिन्हित दीर्घ ref_ctr_offset, bool is_retprobe)
अणु
	पूर्णांक ret;
	अक्षर *path = शून्य;
	काष्ठा trace_event_call *tp_event;

	अगर (!p_event->attr.uprobe_path)
		वापस -EINVAL;

	path = strndup_user(u64_to_user_ptr(p_event->attr.uprobe_path),
			    PATH_MAX);
	अगर (IS_ERR(path)) अणु
		ret = PTR_ERR(path);
		वापस (ret == -EINVAL) ? -E2BIG : ret;
	पूर्ण
	अगर (path[0] == '\0') अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	tp_event = create_local_trace_uprobe(path, p_event->attr.probe_offset,
					     ref_ctr_offset, is_retprobe);
	अगर (IS_ERR(tp_event)) अणु
		ret = PTR_ERR(tp_event);
		जाओ out;
	पूर्ण

	/*
	 * local trace_uprobe need to hold event_mutex to call
	 * uprobe_buffer_enable() and uprobe_buffer_disable().
	 * event_mutex is not required क्रम local trace_kprobes.
	 */
	mutex_lock(&event_mutex);
	ret = perf_trace_event_init(tp_event, p_event);
	अगर (ret)
		destroy_local_trace_uprobe(tp_event);
	mutex_unlock(&event_mutex);
out:
	kमुक्त(path);
	वापस ret;
पूर्ण

व्योम perf_uprobe_destroy(काष्ठा perf_event *p_event)
अणु
	mutex_lock(&event_mutex);
	perf_trace_event_बंद(p_event);
	perf_trace_event_unreg(p_event);
	mutex_unlock(&event_mutex);
	destroy_local_trace_uprobe(p_event->tp_event);
पूर्ण
#पूर्ण_अगर /* CONFIG_UPROBE_EVENTS */

पूर्णांक perf_trace_add(काष्ठा perf_event *p_event, पूर्णांक flags)
अणु
	काष्ठा trace_event_call *tp_event = p_event->tp_event;

	अगर (!(flags & PERF_EF_START))
		p_event->hw.state = PERF_HES_STOPPED;

	/*
	 * If TRACE_REG_PERF_ADD वापसs false; no custom action was perक्रमmed
	 * and we need to take the शेष action of enqueueing our event on
	 * the right per-cpu hlist.
	 */
	अगर (!tp_event->class->reg(tp_event, TRACE_REG_PERF_ADD, p_event)) अणु
		काष्ठा hlist_head __percpu *pcpu_list;
		काष्ठा hlist_head *list;

		pcpu_list = tp_event->perf_events;
		अगर (WARN_ON_ONCE(!pcpu_list))
			वापस -EINVAL;

		list = this_cpu_ptr(pcpu_list);
		hlist_add_head_rcu(&p_event->hlist_entry, list);
	पूर्ण

	वापस 0;
पूर्ण

व्योम perf_trace_del(काष्ठा perf_event *p_event, पूर्णांक flags)
अणु
	काष्ठा trace_event_call *tp_event = p_event->tp_event;

	/*
	 * If TRACE_REG_PERF_DEL वापसs false; no custom action was perक्रमmed
	 * and we need to take the शेष action of dequeueing our event from
	 * the right per-cpu hlist.
	 */
	अगर (!tp_event->class->reg(tp_event, TRACE_REG_PERF_DEL, p_event))
		hlist_del_rcu(&p_event->hlist_entry);
पूर्ण

व्योम *perf_trace_buf_alloc(पूर्णांक size, काष्ठा pt_regs **regs, पूर्णांक *rctxp)
अणु
	अक्षर *raw_data;
	पूर्णांक rctx;

	BUILD_BUG_ON(PERF_MAX_TRACE_SIZE % माप(अचिन्हित दीर्घ));

	अगर (WARN_ONCE(size > PERF_MAX_TRACE_SIZE,
		      "perf buffer not large enough"))
		वापस शून्य;

	*rctxp = rctx = perf_swevent_get_recursion_context();
	अगर (rctx < 0)
		वापस शून्य;

	अगर (regs)
		*regs = this_cpu_ptr(&__perf_regs[rctx]);
	raw_data = this_cpu_ptr(perf_trace_buf[rctx]);

	/* zero the dead bytes from align to not leak stack to user */
	स_रखो(&raw_data[size - माप(u64)], 0, माप(u64));
	वापस raw_data;
पूर्ण
EXPORT_SYMBOL_GPL(perf_trace_buf_alloc);
NOKPROBE_SYMBOL(perf_trace_buf_alloc);

व्योम perf_trace_buf_update(व्योम *record, u16 type)
अणु
	काष्ठा trace_entry *entry = record;

	tracing_generic_entry_update(entry, type, tracing_gen_ctx());
पूर्ण
NOKPROBE_SYMBOL(perf_trace_buf_update);

#अगर_घोषित CONFIG_FUNCTION_TRACER
अटल व्योम
perf_ftrace_function_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			  काष्ठा ftrace_ops *ops,  काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा ftrace_entry *entry;
	काष्ठा perf_event *event;
	काष्ठा hlist_head head;
	काष्ठा pt_regs regs;
	पूर्णांक rctx;
	पूर्णांक bit;

	अगर (!rcu_is_watching())
		वापस;

	अगर ((अचिन्हित दीर्घ)ops->निजी != smp_processor_id())
		वापस;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	event = container_of(ops, काष्ठा perf_event, ftrace_ops);

	/*
	 * @event->hlist entry is शून्य (per INIT_HLIST_NODE), and all
	 * the perf code करोes is hlist_क्रम_each_entry_rcu(), so we can
	 * get away with simply setting the @head.first poपूर्णांकer in order
	 * to create a singular list.
	 */
	head.first = &event->hlist_entry;

#घोषणा ENTRY_SIZE (ALIGN(माप(काष्ठा ftrace_entry) + माप(u32), \
		    माप(u64)) - माप(u32))

	BUILD_BUG_ON(ENTRY_SIZE > PERF_MAX_TRACE_SIZE);

	स_रखो(&regs, 0, माप(regs));
	perf_fetch_caller_regs(&regs);

	entry = perf_trace_buf_alloc(ENTRY_SIZE, शून्य, &rctx);
	अगर (!entry)
		जाओ out;

	entry->ip = ip;
	entry->parent_ip = parent_ip;
	perf_trace_buf_submit(entry, ENTRY_SIZE, rctx, TRACE_FN,
			      1, &regs, &head, शून्य);

out:
	ftrace_test_recursion_unlock(bit);
#अघोषित ENTRY_SIZE
पूर्ण

अटल पूर्णांक perf_ftrace_function_रेजिस्टर(काष्ठा perf_event *event)
अणु
	काष्ठा ftrace_ops *ops = &event->ftrace_ops;

	ops->func    = perf_ftrace_function_call;
	ops->निजी = (व्योम *)(अचिन्हित दीर्घ)nr_cpu_ids;

	वापस रेजिस्टर_ftrace_function(ops);
पूर्ण

अटल पूर्णांक perf_ftrace_function_unरेजिस्टर(काष्ठा perf_event *event)
अणु
	काष्ठा ftrace_ops *ops = &event->ftrace_ops;
	पूर्णांक ret = unरेजिस्टर_ftrace_function(ops);
	ftrace_मुक्त_filter(ops);
	वापस ret;
पूर्ण

पूर्णांक perf_ftrace_event_रेजिस्टर(काष्ठा trace_event_call *call,
			       क्रमागत trace_reg type, व्योम *data)
अणु
	काष्ठा perf_event *event = data;

	चयन (type) अणु
	हाल TRACE_REG_REGISTER:
	हाल TRACE_REG_UNREGISTER:
		अवरोध;
	हाल TRACE_REG_PERF_REGISTER:
	हाल TRACE_REG_PERF_UNREGISTER:
		वापस 0;
	हाल TRACE_REG_PERF_OPEN:
		वापस perf_ftrace_function_रेजिस्टर(data);
	हाल TRACE_REG_PERF_CLOSE:
		वापस perf_ftrace_function_unरेजिस्टर(data);
	हाल TRACE_REG_PERF_ADD:
		event->ftrace_ops.निजी = (व्योम *)(अचिन्हित दीर्घ)smp_processor_id();
		वापस 1;
	हाल TRACE_REG_PERF_DEL:
		event->ftrace_ops.निजी = (व्योम *)(अचिन्हित दीर्घ)nr_cpu_ids;
		वापस 1;
	पूर्ण

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */
