<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Infraकाष्ठाure क्रम profiling code inserted by 'gcc -pg'.
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2004-2008 Ingo Molnar <mingo@redhat.com>
 *
 * Originally ported from the -rt patch by:
 *   Copyright (C) 2007 Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Based on code in the latency_tracer, that is:
 *
 *  Copyright (C) 2004-2006 Ingo Molnar
 *  Copyright (C) 2004 Nadia Yvette Chambers
 */

#समावेश <linux/stop_machine.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/security.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/tracefs.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sort.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/kprobes.h>

#समावेश <trace/events/sched.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>

#समावेश "ftrace_internal.h"
#समावेश "trace_output.h"
#समावेश "trace_stat.h"

#घोषणा FTRACE_WARN_ON(cond)			\
	(अणु					\
		पूर्णांक ___r = cond;		\
		अगर (WARN_ON(___r))		\
			ftrace_समाप्त();		\
		___r;				\
	पूर्ण)

#घोषणा FTRACE_WARN_ON_ONCE(cond)		\
	(अणु					\
		पूर्णांक ___r = cond;		\
		अगर (WARN_ON_ONCE(___r))		\
			ftrace_समाप्त();		\
		___r;				\
	पूर्ण)

/* hash bits क्रम specअगरic function selection */
#घोषणा FTRACE_HASH_DEFAULT_BITS 10
#घोषणा FTRACE_HASH_MAX_BITS 12

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#घोषणा INIT_OPS_HASH(opsname)	\
	.func_hash		= &opsname.local_hash,			\
	.local_hash.regex_lock	= __MUTEX_INITIALIZER(opsname.local_hash.regex_lock),
#अन्यथा
#घोषणा INIT_OPS_HASH(opsname)
#पूर्ण_अगर

क्रमागत अणु
	FTRACE_MODIFY_ENABLE_FL		= (1 << 0),
	FTRACE_MODIFY_MAY_SLEEP_FL	= (1 << 1),
पूर्ण;

काष्ठा ftrace_ops ftrace_list_end __पढ़ो_mostly = अणु
	.func		= ftrace_stub,
	.flags		= FTRACE_OPS_FL_STUB,
	INIT_OPS_HASH(ftrace_list_end)
पूर्ण;

/* ftrace_enabled is a method to turn ftrace on or off */
पूर्णांक ftrace_enabled __पढ़ो_mostly;
अटल पूर्णांक last_ftrace_enabled;

/* Current function tracing op */
काष्ठा ftrace_ops *function_trace_op __पढ़ो_mostly = &ftrace_list_end;
/* What to set function_trace_op to */
अटल काष्ठा ftrace_ops *set_function_trace_op;

अटल bool ftrace_pids_enabled(काष्ठा ftrace_ops *ops)
अणु
	काष्ठा trace_array *tr;

	अगर (!(ops->flags & FTRACE_OPS_FL_PID) || !ops->निजी)
		वापस false;

	tr = ops->निजी;

	वापस tr->function_pids != शून्य || tr->function_no_pids != शून्य;
पूर्ण

अटल व्योम ftrace_update_trampoline(काष्ठा ftrace_ops *ops);

/*
 * ftrace_disabled is set when an anomaly is discovered.
 * ftrace_disabled is much stronger than ftrace_enabled.
 */
अटल पूर्णांक ftrace_disabled __पढ़ो_mostly;

DEFINE_MUTEX(ftrace_lock);

काष्ठा ftrace_ops __rcu *ftrace_ops_list __पढ़ो_mostly = &ftrace_list_end;
ftrace_func_t ftrace_trace_function __पढ़ो_mostly = ftrace_stub;
काष्ठा ftrace_ops global_ops;

#अगर ARCH_SUPPORTS_FTRACE_OPS
अटल व्योम ftrace_ops_list_func(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				 काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs);
#अन्यथा
/* See comment below, where ftrace_ops_list_func is defined */
अटल व्योम ftrace_ops_no_ops(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip);
#घोषणा ftrace_ops_list_func ((ftrace_func_t)ftrace_ops_no_ops)
#पूर्ण_अगर

अटल अंतरभूत व्योम ftrace_ops_init(काष्ठा ftrace_ops *ops)
अणु
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	अगर (!(ops->flags & FTRACE_OPS_FL_INITIALIZED)) अणु
		mutex_init(&ops->local_hash.regex_lock);
		ops->func_hash = &ops->local_hash;
		ops->flags |= FTRACE_OPS_FL_INITIALIZED;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम ftrace_pid_func(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
			    काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा trace_array *tr = op->निजी;
	पूर्णांक pid;

	अगर (tr) अणु
		pid = this_cpu_पढ़ो(tr->array_buffer.data->ftrace_ignore_pid);
		अगर (pid == FTRACE_PID_IGNORE)
			वापस;
		अगर (pid != FTRACE_PID_TRACE &&
		    pid != current->pid)
			वापस;
	पूर्ण

	op->saved_func(ip, parent_ip, op, fregs);
पूर्ण

अटल व्योम ftrace_sync_ipi(व्योम *data)
अणु
	/* Probably not needed, but करो it anyway */
	smp_rmb();
पूर्ण

अटल ftrace_func_t ftrace_ops_get_list_func(काष्ठा ftrace_ops *ops)
अणु
	/*
	 * If this is a dynamic, RCU, or per CPU ops, or we क्रमce list func,
	 * then it needs to call the list anyway.
	 */
	अगर (ops->flags & (FTRACE_OPS_FL_DYNAMIC | FTRACE_OPS_FL_RCU) ||
	    FTRACE_FORCE_LIST_FUNC)
		वापस ftrace_ops_list_func;

	वापस ftrace_ops_get_func(ops);
पूर्ण

अटल व्योम update_ftrace_function(व्योम)
अणु
	ftrace_func_t func;

	/*
	 * Prepare the ftrace_ops that the arch callback will use.
	 * If there's only one ftrace_ops रेजिस्टरed, the ftrace_ops_list
	 * will poपूर्णांक to the ops we want.
	 */
	set_function_trace_op = rcu_dereference_रक्षित(ftrace_ops_list,
						lockdep_is_held(&ftrace_lock));

	/* If there's no ftrace_ops रेजिस्टरed, just call the stub function */
	अगर (set_function_trace_op == &ftrace_list_end) अणु
		func = ftrace_stub;

	/*
	 * If we are at the end of the list and this ops is
	 * recursion safe and not dynamic and the arch supports passing ops,
	 * then have the mcount trampoline call the function directly.
	 */
	पूर्ण अन्यथा अगर (rcu_dereference_रक्षित(ftrace_ops_list->next,
			lockdep_is_held(&ftrace_lock)) == &ftrace_list_end) अणु
		func = ftrace_ops_get_list_func(ftrace_ops_list);

	पूर्ण अन्यथा अणु
		/* Just use the शेष ftrace_ops */
		set_function_trace_op = &ftrace_list_end;
		func = ftrace_ops_list_func;
	पूर्ण

	update_function_graph_func();

	/* If there's no change, then करो nothing more here */
	अगर (ftrace_trace_function == func)
		वापस;

	/*
	 * If we are using the list function, it करोesn't care
	 * about the function_trace_ops.
	 */
	अगर (func == ftrace_ops_list_func) अणु
		ftrace_trace_function = func;
		/*
		 * Don't even bother setting function_trace_ops,
		 * it would be racy to करो so anyway.
		 */
		वापस;
	पूर्ण

#अगर_अघोषित CONFIG_DYNAMIC_FTRACE
	/*
	 * For अटल tracing, we need to be a bit more careful.
	 * The function change takes affect immediately. Thus,
	 * we need to coordinate the setting of the function_trace_ops
	 * with the setting of the ftrace_trace_function.
	 *
	 * Set the function to the list ops, which will call the
	 * function we want, albeit indirectly, but it handles the
	 * ftrace_ops and करोesn't depend on function_trace_op.
	 */
	ftrace_trace_function = ftrace_ops_list_func;
	/*
	 * Make sure all CPUs see this. Yes this is slow, but अटल
	 * tracing is slow and nasty to have enabled.
	 */
	synchronize_rcu_tasks_rude();
	/* Now all cpus are using the list ops. */
	function_trace_op = set_function_trace_op;
	/* Make sure the function_trace_op is visible on all CPUs */
	smp_wmb();
	/* Nasty way to क्रमce a rmb on all cpus */
	smp_call_function(ftrace_sync_ipi, शून्य, 1);
	/* OK, we are all set to update the ftrace_trace_function now! */
#पूर्ण_अगर /* !CONFIG_DYNAMIC_FTRACE */

	ftrace_trace_function = func;
पूर्ण

अटल व्योम add_ftrace_ops(काष्ठा ftrace_ops __rcu **list,
			   काष्ठा ftrace_ops *ops)
अणु
	rcu_assign_poपूर्णांकer(ops->next, *list);

	/*
	 * We are entering ops पूर्णांकo the list but another
	 * CPU might be walking that list. We need to make sure
	 * the ops->next poपूर्णांकer is valid beक्रमe another CPU sees
	 * the ops poपूर्णांकer included पूर्णांकo the list.
	 */
	rcu_assign_poपूर्णांकer(*list, ops);
पूर्ण

अटल पूर्णांक हटाओ_ftrace_ops(काष्ठा ftrace_ops __rcu **list,
			     काष्ठा ftrace_ops *ops)
अणु
	काष्ठा ftrace_ops **p;

	/*
	 * If we are removing the last function, then simply poपूर्णांक
	 * to the ftrace_stub.
	 */
	अगर (rcu_dereference_रक्षित(*list,
			lockdep_is_held(&ftrace_lock)) == ops &&
	    rcu_dereference_रक्षित(ops->next,
			lockdep_is_held(&ftrace_lock)) == &ftrace_list_end) अणु
		*list = &ftrace_list_end;
		वापस 0;
	पूर्ण

	क्रम (p = list; *p != &ftrace_list_end; p = &(*p)->next)
		अगर (*p == ops)
			अवरोध;

	अगर (*p != ops)
		वापस -1;

	*p = (*p)->next;
	वापस 0;
पूर्ण

अटल व्योम ftrace_update_trampoline(काष्ठा ftrace_ops *ops);

पूर्णांक __रेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops)
अणु
	अगर (ops->flags & FTRACE_OPS_FL_DELETED)
		वापस -EINVAL;

	अगर (WARN_ON(ops->flags & FTRACE_OPS_FL_ENABLED))
		वापस -EBUSY;

#अगर_अघोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	/*
	 * If the ftrace_ops specअगरies SAVE_REGS, then it only can be used
	 * अगर the arch supports it, or SAVE_REGS_IF_SUPPORTED is also set.
	 * Setting SAVE_REGS_IF_SUPPORTED makes SAVE_REGS irrelevant.
	 */
	अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS &&
	    !(ops->flags & FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED))
		वापस -EINVAL;

	अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED)
		ops->flags |= FTRACE_OPS_FL_SAVE_REGS;
#पूर्ण_अगर
	अगर (!ftrace_enabled && (ops->flags & FTRACE_OPS_FL_PERMANENT))
		वापस -EBUSY;

	अगर (!core_kernel_data((अचिन्हित दीर्घ)ops))
		ops->flags |= FTRACE_OPS_FL_DYNAMIC;

	add_ftrace_ops(&ftrace_ops_list, ops);

	/* Always save the function, and reset at unरेजिस्टरing */
	ops->saved_func = ops->func;

	अगर (ftrace_pids_enabled(ops))
		ops->func = ftrace_pid_func;

	ftrace_update_trampoline(ops);

	अगर (ftrace_enabled)
		update_ftrace_function();

	वापस 0;
पूर्ण

पूर्णांक __unरेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!(ops->flags & FTRACE_OPS_FL_ENABLED)))
		वापस -EBUSY;

	ret = हटाओ_ftrace_ops(&ftrace_ops_list, ops);

	अगर (ret < 0)
		वापस ret;

	अगर (ftrace_enabled)
		update_ftrace_function();

	ops->func = ops->saved_func;

	वापस 0;
पूर्ण

अटल व्योम ftrace_update_pid_func(व्योम)
अणु
	काष्ठा ftrace_ops *op;

	/* Only करो something अगर we are tracing something */
	अगर (ftrace_trace_function == ftrace_stub)
		वापस;

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		अगर (op->flags & FTRACE_OPS_FL_PID) अणु
			op->func = ftrace_pids_enabled(op) ?
				ftrace_pid_func : op->saved_func;
			ftrace_update_trampoline(op);
		पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_op(op);

	update_ftrace_function();
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_PROखाताR
काष्ठा ftrace_profile अणु
	काष्ठा hlist_node		node;
	अचिन्हित दीर्घ			ip;
	अचिन्हित दीर्घ			counter;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अचिन्हित दीर्घ दीर्घ		समय;
	अचिन्हित दीर्घ दीर्घ		समय_squared;
#पूर्ण_अगर
पूर्ण;

काष्ठा ftrace_profile_page अणु
	काष्ठा ftrace_profile_page	*next;
	अचिन्हित दीर्घ			index;
	काष्ठा ftrace_profile		records[];
पूर्ण;

काष्ठा ftrace_profile_stat अणु
	atomic_t			disabled;
	काष्ठा hlist_head		*hash;
	काष्ठा ftrace_profile_page	*pages;
	काष्ठा ftrace_profile_page	*start;
	काष्ठा tracer_stat		stat;
पूर्ण;

#घोषणा PROखाता_RECORDS_SIZE						\
	(PAGE_SIZE - दुरत्व(काष्ठा ftrace_profile_page, records))

#घोषणा PROखाताS_PER_PAGE					\
	(PROखाता_RECORDS_SIZE / माप(काष्ठा ftrace_profile))

अटल पूर्णांक ftrace_profile_enabled __पढ़ो_mostly;

/* ftrace_profile_lock - synchronize the enable and disable of the profiler */
अटल DEFINE_MUTEX(ftrace_profile_lock);

अटल DEFINE_PER_CPU(काष्ठा ftrace_profile_stat, ftrace_profile_stats);

#घोषणा FTRACE_PROखाता_HASH_BITS 10
#घोषणा FTRACE_PROखाता_HASH_SIZE (1 << FTRACE_PROखाता_HASH_BITS)

अटल व्योम *
function_stat_next(व्योम *v, पूर्णांक idx)
अणु
	काष्ठा ftrace_profile *rec = v;
	काष्ठा ftrace_profile_page *pg;

	pg = (काष्ठा ftrace_profile_page *)((अचिन्हित दीर्घ)rec & PAGE_MASK);

 again:
	अगर (idx != 0)
		rec++;

	अगर ((व्योम *)rec >= (व्योम *)&pg->records[pg->index]) अणु
		pg = pg->next;
		अगर (!pg)
			वापस शून्य;
		rec = &pg->records[0];
		अगर (!rec->counter)
			जाओ again;
	पूर्ण

	वापस rec;
पूर्ण

अटल व्योम *function_stat_start(काष्ठा tracer_stat *trace)
अणु
	काष्ठा ftrace_profile_stat *stat =
		container_of(trace, काष्ठा ftrace_profile_stat, stat);

	अगर (!stat || !stat->start)
		वापस शून्य;

	वापस function_stat_next(&stat->start->records[0], 0);
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
/* function graph compares on total समय */
अटल पूर्णांक function_stat_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा ftrace_profile *a = p1;
	स्थिर काष्ठा ftrace_profile *b = p2;

	अगर (a->समय < b->समय)
		वापस -1;
	अगर (a->समय > b->समय)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण
#अन्यथा
/* not function graph compares against hits */
अटल पूर्णांक function_stat_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा ftrace_profile *a = p1;
	स्थिर काष्ठा ftrace_profile *b = p2;

	अगर (a->counter < b->counter)
		वापस -1;
	अगर (a->counter > b->counter)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक function_stat_headers(काष्ठा seq_file *m)
अणु
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	seq_माला_दो(m, "  Function                               "
		 "Hit    Time            Avg             s^2\न"
		    "  --------                               "
		 "---    ----            ---             ---\n");
#अन्यथा
	seq_माला_दो(m, "  Function                               Hit\n"
		    "  --------                               ---\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक function_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ftrace_profile *rec = v;
	अक्षर str[KSYM_SYMBOL_LEN];
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अटल काष्ठा trace_seq s;
	अचिन्हित दीर्घ दीर्घ avg;
	अचिन्हित दीर्घ दीर्घ stddev;
#पूर्ण_अगर
	mutex_lock(&ftrace_profile_lock);

	/* we raced with function_profile_reset() */
	अगर (unlikely(rec->counter == 0)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	avg = भाग64_ul(rec->समय, rec->counter);
	अगर (tracing_thresh && (avg < tracing_thresh))
		जाओ out;
#पूर्ण_अगर

	kallsyms_lookup(rec->ip, शून्य, शून्य, शून्य, str);
	seq_म_लिखो(m, "  %-30.30s  %10lu", str, rec->counter);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	seq_माला_दो(m, "    ");

	/* Sample standard deviation (s^2) */
	अगर (rec->counter <= 1)
		stddev = 0;
	अन्यथा अणु
		/*
		 * Apply Welक्रमd's method:
		 * s^2 = 1 / (n * (n-1)) * (n * \Sum (x_i)^2 - (\Sum x_i)^2)
		 */
		stddev = rec->counter * rec->समय_squared -
			 rec->समय * rec->समय;

		/*
		 * Divide only 1000 क्रम ns^2 -> us^2 conversion.
		 * trace_prपूर्णांक_graph_duration will भागide 1000 again.
		 */
		stddev = भाग64_ul(stddev,
				  rec->counter * (rec->counter - 1) * 1000);
	पूर्ण

	trace_seq_init(&s);
	trace_prपूर्णांक_graph_duration(rec->समय, &s);
	trace_seq_माला_दो(&s, "    ");
	trace_prपूर्णांक_graph_duration(avg, &s);
	trace_seq_माला_दो(&s, "    ");
	trace_prपूर्णांक_graph_duration(stddev, &s);
	trace_prपूर्णांक_seq(m, &s);
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
out:
	mutex_unlock(&ftrace_profile_lock);

	वापस ret;
पूर्ण

अटल व्योम ftrace_profile_reset(काष्ठा ftrace_profile_stat *stat)
अणु
	काष्ठा ftrace_profile_page *pg;

	pg = stat->pages = stat->start;

	जबतक (pg) अणु
		स_रखो(pg->records, 0, PROखाता_RECORDS_SIZE);
		pg->index = 0;
		pg = pg->next;
	पूर्ण

	स_रखो(stat->hash, 0,
	       FTRACE_PROखाता_HASH_SIZE * माप(काष्ठा hlist_head));
पूर्ण

पूर्णांक ftrace_profile_pages_init(काष्ठा ftrace_profile_stat *stat)
अणु
	काष्ठा ftrace_profile_page *pg;
	पूर्णांक functions;
	पूर्णांक pages;
	पूर्णांक i;

	/* If we alपढ़ोy allocated, करो nothing */
	अगर (stat->pages)
		वापस 0;

	stat->pages = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!stat->pages)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	functions = ftrace_update_tot_cnt;
#अन्यथा
	/*
	 * We करो not know the number of functions that exist because
	 * dynamic tracing is what counts them. With past experience
	 * we have around 20K functions. That should be more than enough.
	 * It is highly unlikely we will execute every function in
	 * the kernel.
	 */
	functions = 20000;
#पूर्ण_अगर

	pg = stat->start = stat->pages;

	pages = DIV_ROUND_UP(functions, PROखाताS_PER_PAGE);

	क्रम (i = 1; i < pages; i++) अणु
		pg->next = (व्योम *)get_zeroed_page(GFP_KERNEL);
		अगर (!pg->next)
			जाओ out_मुक्त;
		pg = pg->next;
	पूर्ण

	वापस 0;

 out_मुक्त:
	pg = stat->start;
	जबतक (pg) अणु
		अचिन्हित दीर्घ पंचांगp = (अचिन्हित दीर्घ)pg;

		pg = pg->next;
		मुक्त_page(पंचांगp);
	पूर्ण

	stat->pages = शून्य;
	stat->start = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ftrace_profile_init_cpu(पूर्णांक cpu)
अणु
	काष्ठा ftrace_profile_stat *stat;
	पूर्णांक size;

	stat = &per_cpu(ftrace_profile_stats, cpu);

	अगर (stat->hash) अणु
		/* If the profile is alपढ़ोy created, simply reset it */
		ftrace_profile_reset(stat);
		वापस 0;
	पूर्ण

	/*
	 * We are profiling all functions, but usually only a few thousand
	 * functions are hit. We'll make a hash of 1024 items.
	 */
	size = FTRACE_PROखाता_HASH_SIZE;

	stat->hash = kसुस्मृति(size, माप(काष्ठा hlist_head), GFP_KERNEL);

	अगर (!stat->hash)
		वापस -ENOMEM;

	/* Pपुनः_स्मृतिate the function profiling pages */
	अगर (ftrace_profile_pages_init(stat) < 0) अणु
		kमुक्त(stat->hash);
		stat->hash = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_profile_init(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक ret = 0;

	क्रम_each_possible_cpu(cpu) अणु
		ret = ftrace_profile_init_cpu(cpu);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* पूर्णांकerrupts must be disabled */
अटल काष्ठा ftrace_profile *
ftrace_find_profiled_func(काष्ठा ftrace_profile_stat *stat, अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_profile *rec;
	काष्ठा hlist_head *hhd;
	अचिन्हित दीर्घ key;

	key = hash_दीर्घ(ip, FTRACE_PROखाता_HASH_BITS);
	hhd = &stat->hash[key];

	अगर (hlist_empty(hhd))
		वापस शून्य;

	hlist_क्रम_each_entry_rcu_notrace(rec, hhd, node) अणु
		अगर (rec->ip == ip)
			वापस rec;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ftrace_add_profile(काष्ठा ftrace_profile_stat *stat,
			       काष्ठा ftrace_profile *rec)
अणु
	अचिन्हित दीर्घ key;

	key = hash_दीर्घ(rec->ip, FTRACE_PROखाता_HASH_BITS);
	hlist_add_head_rcu(&rec->node, &stat->hash[key]);
पूर्ण

/*
 * The memory is alपढ़ोy allocated, this simply finds a new record to use.
 */
अटल काष्ठा ftrace_profile *
ftrace_profile_alloc(काष्ठा ftrace_profile_stat *stat, अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_profile *rec = शून्य;

	/* prevent recursion (from NMIs) */
	अगर (atomic_inc_वापस(&stat->disabled) != 1)
		जाओ out;

	/*
	 * Try to find the function again since an NMI
	 * could have added it
	 */
	rec = ftrace_find_profiled_func(stat, ip);
	अगर (rec)
		जाओ out;

	अगर (stat->pages->index == PROखाताS_PER_PAGE) अणु
		अगर (!stat->pages->next)
			जाओ out;
		stat->pages = stat->pages->next;
	पूर्ण

	rec = &stat->pages->records[stat->pages->index++];
	rec->ip = ip;
	ftrace_add_profile(stat, rec);

 out:
	atomic_dec(&stat->disabled);

	वापस rec;
पूर्ण

अटल व्योम
function_profile_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		      काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा ftrace_profile_stat *stat;
	काष्ठा ftrace_profile *rec;
	अचिन्हित दीर्घ flags;

	अगर (!ftrace_profile_enabled)
		वापस;

	local_irq_save(flags);

	stat = this_cpu_ptr(&ftrace_profile_stats);
	अगर (!stat->hash || !ftrace_profile_enabled)
		जाओ out;

	rec = ftrace_find_profiled_func(stat, ip);
	अगर (!rec) अणु
		rec = ftrace_profile_alloc(stat, ip);
		अगर (!rec)
			जाओ out;
	पूर्ण

	rec->counter++;
 out:
	local_irq_restore(flags);
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
अटल bool fgraph_graph_समय = true;

व्योम ftrace_graph_graph_समय_control(bool enable)
अणु
	fgraph_graph_समय = enable;
पूर्ण

अटल पूर्णांक profile_graph_entry(काष्ठा ftrace_graph_ent *trace)
अणु
	काष्ठा ftrace_ret_stack *ret_stack;

	function_profile_call(trace->func, 0, शून्य, शून्य);

	/* If function graph is shutting करोwn, ret_stack can be शून्य */
	अगर (!current->ret_stack)
		वापस 0;

	ret_stack = ftrace_graph_get_ret_stack(current, 0);
	अगर (ret_stack)
		ret_stack->subसमय = 0;

	वापस 1;
पूर्ण

अटल व्योम profile_graph_वापस(काष्ठा ftrace_graph_ret *trace)
अणु
	काष्ठा ftrace_ret_stack *ret_stack;
	काष्ठा ftrace_profile_stat *stat;
	अचिन्हित दीर्घ दीर्घ callसमय;
	काष्ठा ftrace_profile *rec;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	stat = this_cpu_ptr(&ftrace_profile_stats);
	अगर (!stat->hash || !ftrace_profile_enabled)
		जाओ out;

	/* If the callसमय was zero'd ignore it */
	अगर (!trace->callसमय)
		जाओ out;

	callसमय = trace->retसमय - trace->callसमय;

	अगर (!fgraph_graph_समय) अणु

		/* Append this call समय to the parent समय to subtract */
		ret_stack = ftrace_graph_get_ret_stack(current, 1);
		अगर (ret_stack)
			ret_stack->subसमय += callसमय;

		ret_stack = ftrace_graph_get_ret_stack(current, 0);
		अगर (ret_stack && ret_stack->subसमय < callसमय)
			callसमय -= ret_stack->subसमय;
		अन्यथा
			callसमय = 0;
	पूर्ण

	rec = ftrace_find_profiled_func(stat, trace->func);
	अगर (rec) अणु
		rec->समय += callसमय;
		rec->समय_squared += callसमय * callसमय;
	पूर्ण

 out:
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा fgraph_ops fprofiler_ops = अणु
	.entryfunc = &profile_graph_entry,
	.retfunc = &profile_graph_वापस,
पूर्ण;

अटल पूर्णांक रेजिस्टर_ftrace_profiler(व्योम)
अणु
	वापस रेजिस्टर_ftrace_graph(&fprofiler_ops);
पूर्ण

अटल व्योम unरेजिस्टर_ftrace_profiler(व्योम)
अणु
	unरेजिस्टर_ftrace_graph(&fprofiler_ops);
पूर्ण
#अन्यथा
अटल काष्ठा ftrace_ops ftrace_profile_ops __पढ़ो_mostly = अणु
	.func		= function_profile_call,
	.flags		= FTRACE_OPS_FL_INITIALIZED,
	INIT_OPS_HASH(ftrace_profile_ops)
पूर्ण;

अटल पूर्णांक रेजिस्टर_ftrace_profiler(व्योम)
अणु
	वापस रेजिस्टर_ftrace_function(&ftrace_profile_ops);
पूर्ण

अटल व्योम unरेजिस्टर_ftrace_profiler(व्योम)
अणु
	unरेजिस्टर_ftrace_function(&ftrace_profile_ops);
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

अटल sमाप_प्रकार
ftrace_profile_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(ubuf, cnt, 10, &val);
	अगर (ret)
		वापस ret;

	val = !!val;

	mutex_lock(&ftrace_profile_lock);
	अगर (ftrace_profile_enabled ^ val) अणु
		अगर (val) अणु
			ret = ftrace_profile_init();
			अगर (ret < 0) अणु
				cnt = ret;
				जाओ out;
			पूर्ण

			ret = रेजिस्टर_ftrace_profiler();
			अगर (ret < 0) अणु
				cnt = ret;
				जाओ out;
			पूर्ण
			ftrace_profile_enabled = 1;
		पूर्ण अन्यथा अणु
			ftrace_profile_enabled = 0;
			/*
			 * unरेजिस्टर_ftrace_profiler calls stop_machine
			 * so this acts like an synchronize_rcu.
			 */
			unरेजिस्टर_ftrace_profiler();
		पूर्ण
	पूर्ण
 out:
	mutex_unlock(&ftrace_profile_lock);

	*ppos += cnt;

	वापस cnt;
पूर्ण

अटल sमाप_प्रकार
ftrace_profile_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[64];		/* big enough to hold a number */
	पूर्णांक r;

	r = प्र_लिखो(buf, "%u\n", ftrace_profile_enabled);
	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, r);
पूर्ण

अटल स्थिर काष्ठा file_operations ftrace_profile_fops = अणु
	.खोलो		= tracing_खोलो_generic,
	.पढ़ो		= ftrace_profile_पढ़ो,
	.ग_लिखो		= ftrace_profile_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

/* used to initialize the real stat files */
अटल काष्ठा tracer_stat function_stats __initdata = अणु
	.name		= "functions",
	.stat_start	= function_stat_start,
	.stat_next	= function_stat_next,
	.stat_cmp	= function_stat_cmp,
	.stat_headers	= function_stat_headers,
	.stat_show	= function_stat_show
पूर्ण;

अटल __init व्योम ftrace_profile_tracefs(काष्ठा dentry *d_tracer)
अणु
	काष्ठा ftrace_profile_stat *stat;
	काष्ठा dentry *entry;
	अक्षर *name;
	पूर्णांक ret;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		stat = &per_cpu(ftrace_profile_stats, cpu);

		name = kaप्र_लिखो(GFP_KERNEL, "function%d", cpu);
		अगर (!name) अणु
			/*
			 * The files created are permanent, अगर something happens
			 * we still करो not मुक्त memory.
			 */
			WARN(1,
			     "Could not allocate stat file for cpu %d\n",
			     cpu);
			वापस;
		पूर्ण
		stat->stat = function_stats;
		stat->stat.name = name;
		ret = रेजिस्टर_stat_tracer(&stat->stat);
		अगर (ret) अणु
			WARN(1,
			     "Could not register function stat for cpu %d\n",
			     cpu);
			kमुक्त(name);
			वापस;
		पूर्ण
	पूर्ण

	entry = tracefs_create_file("function_profile_enabled", 0644,
				    d_tracer, शून्य, &ftrace_profile_fops);
	अगर (!entry)
		pr_warn("Could not create tracefs 'function_profile_enabled' entry\n");
पूर्ण

#अन्यथा /* CONFIG_FUNCTION_PROखाताR */
अटल __init व्योम ftrace_profile_tracefs(काष्ठा dentry *d_tracer)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_PROखाताR */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

अटल काष्ठा ftrace_ops *हटाओd_ops;

/*
 * Set when करोing a global update, like enabling all recs or disabling them.
 * It is not set when just updating a single ftrace_ops.
 */
अटल bool update_all_ops;

#अगर_अघोषित CONFIG_FTRACE_MCOUNT_RECORD
# error Dynamic ftrace depends on MCOUNT_RECORD
#पूर्ण_अगर

काष्ठा ftrace_func_probe अणु
	काष्ठा ftrace_probe_ops	*probe_ops;
	काष्ठा ftrace_ops	ops;
	काष्ठा trace_array	*tr;
	काष्ठा list_head	list;
	व्योम			*data;
	पूर्णांक			ref;
पूर्ण;

/*
 * We make these स्थिरant because no one should touch them,
 * but they are used as the शेष "empty hash", to aव्योम allocating
 * it all the समय. These are in a पढ़ो only section such that अगर
 * anyone करोes try to modअगरy it, it will cause an exception.
 */
अटल स्थिर काष्ठा hlist_head empty_buckets[1];
अटल स्थिर काष्ठा ftrace_hash empty_hash = अणु
	.buckets = (काष्ठा hlist_head *)empty_buckets,
पूर्ण;
#घोषणा EMPTY_HASH	((काष्ठा ftrace_hash *)&empty_hash)

काष्ठा ftrace_ops global_ops = अणु
	.func				= ftrace_stub,
	.local_hash.notrace_hash	= EMPTY_HASH,
	.local_hash.filter_hash		= EMPTY_HASH,
	INIT_OPS_HASH(global_ops)
	.flags				= FTRACE_OPS_FL_INITIALIZED |
					  FTRACE_OPS_FL_PID,
पूर्ण;

/*
 * Used by the stack unwinder to know about dynamic ftrace trampolines.
 */
काष्ठा ftrace_ops *ftrace_ops_trampoline(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_ops *op = शून्य;

	/*
	 * Some of the ops may be dynamically allocated,
	 * they are मुक्तd after a synchronize_rcu().
	 */
	preempt_disable_notrace();

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		/*
		 * This is to check क्रम dynamically allocated trampolines.
		 * Trampolines that are in kernel text will have
		 * core_kernel_text() वापस true.
		 */
		अगर (op->trampoline && op->trampoline_size)
			अगर (addr >= op->trampoline &&
			    addr < op->trampoline + op->trampoline_size) अणु
				preempt_enable_notrace();
				वापस op;
			पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_op(op);
	preempt_enable_notrace();

	वापस शून्य;
पूर्ण

/*
 * This is used by __kernel_text_address() to वापस true अगर the
 * address is on a dynamically allocated trampoline that would
 * not वापस true क्रम either core_kernel_text() or
 * is_module_text_address().
 */
bool is_ftrace_trampoline(अचिन्हित दीर्घ addr)
अणु
	वापस ftrace_ops_trampoline(addr) != शून्य;
पूर्ण

काष्ठा ftrace_page अणु
	काष्ठा ftrace_page	*next;
	काष्ठा dyn_ftrace	*records;
	पूर्णांक			index;
	पूर्णांक			order;
पूर्ण;

#घोषणा ENTRY_SIZE माप(काष्ठा dyn_ftrace)
#घोषणा ENTRIES_PER_PAGE (PAGE_SIZE / ENTRY_SIZE)

अटल काष्ठा ftrace_page	*ftrace_pages_start;
अटल काष्ठा ftrace_page	*ftrace_pages;

अटल __always_अंतरभूत अचिन्हित दीर्घ
ftrace_hash_key(काष्ठा ftrace_hash *hash, अचिन्हित दीर्घ ip)
अणु
	अगर (hash->size_bits > 0)
		वापस hash_दीर्घ(ip, hash->size_bits);

	वापस 0;
पूर्ण

/* Only use this function अगर ftrace_hash_empty() has alपढ़ोy been tested */
अटल __always_अंतरभूत काष्ठा ftrace_func_entry *
__ftrace_lookup_ip(काष्ठा ftrace_hash *hash, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ key;
	काष्ठा ftrace_func_entry *entry;
	काष्ठा hlist_head *hhd;

	key = ftrace_hash_key(hash, ip);
	hhd = &hash->buckets[key];

	hlist_क्रम_each_entry_rcu_notrace(entry, hhd, hlist) अणु
		अगर (entry->ip == ip)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * ftrace_lookup_ip - Test to see अगर an ip exists in an ftrace_hash
 * @hash: The hash to look at
 * @ip: The inकाष्ठाion poपूर्णांकer to test
 *
 * Search a given @hash to see अगर a given inकाष्ठाion poपूर्णांकer (@ip)
 * exists in it.
 *
 * Returns the entry that holds the @ip अगर found. शून्य otherwise.
 */
काष्ठा ftrace_func_entry *
ftrace_lookup_ip(काष्ठा ftrace_hash *hash, अचिन्हित दीर्घ ip)
अणु
	अगर (ftrace_hash_empty(hash))
		वापस शून्य;

	वापस __ftrace_lookup_ip(hash, ip);
पूर्ण

अटल व्योम __add_hash_entry(काष्ठा ftrace_hash *hash,
			     काष्ठा ftrace_func_entry *entry)
अणु
	काष्ठा hlist_head *hhd;
	अचिन्हित दीर्घ key;

	key = ftrace_hash_key(hash, entry->ip);
	hhd = &hash->buckets[key];
	hlist_add_head(&entry->hlist, hhd);
	hash->count++;
पूर्ण

अटल पूर्णांक add_hash_entry(काष्ठा ftrace_hash *hash, अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_func_entry *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->ip = ip;
	__add_hash_entry(hash, entry);

	वापस 0;
पूर्ण

अटल व्योम
मुक्त_hash_entry(काष्ठा ftrace_hash *hash,
		  काष्ठा ftrace_func_entry *entry)
अणु
	hlist_del(&entry->hlist);
	kमुक्त(entry);
	hash->count--;
पूर्ण

अटल व्योम
हटाओ_hash_entry(काष्ठा ftrace_hash *hash,
		  काष्ठा ftrace_func_entry *entry)
अणु
	hlist_del_rcu(&entry->hlist);
	hash->count--;
पूर्ण

अटल व्योम ftrace_hash_clear(काष्ठा ftrace_hash *hash)
अणु
	काष्ठा hlist_head *hhd;
	काष्ठा hlist_node *tn;
	काष्ठा ftrace_func_entry *entry;
	पूर्णांक size = 1 << hash->size_bits;
	पूर्णांक i;

	अगर (!hash->count)
		वापस;

	क्रम (i = 0; i < size; i++) अणु
		hhd = &hash->buckets[i];
		hlist_क्रम_each_entry_safe(entry, tn, hhd, hlist)
			मुक्त_hash_entry(hash, entry);
	पूर्ण
	FTRACE_WARN_ON(hash->count);
पूर्ण

अटल व्योम मुक्त_ftrace_mod(काष्ठा ftrace_mod_load *ftrace_mod)
अणु
	list_del(&ftrace_mod->list);
	kमुक्त(ftrace_mod->module);
	kमुक्त(ftrace_mod->func);
	kमुक्त(ftrace_mod);
पूर्ण

अटल व्योम clear_ftrace_mod_list(काष्ठा list_head *head)
अणु
	काष्ठा ftrace_mod_load *p, *n;

	/* stack tracer isn't supported yet */
	अगर (!head)
		वापस;

	mutex_lock(&ftrace_lock);
	list_क्रम_each_entry_safe(p, n, head, list)
		मुक्त_ftrace_mod(p);
	mutex_unlock(&ftrace_lock);
पूर्ण

अटल व्योम मुक्त_ftrace_hash(काष्ठा ftrace_hash *hash)
अणु
	अगर (!hash || hash == EMPTY_HASH)
		वापस;
	ftrace_hash_clear(hash);
	kमुक्त(hash->buckets);
	kमुक्त(hash);
पूर्ण

अटल व्योम __मुक्त_ftrace_hash_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा ftrace_hash *hash;

	hash = container_of(rcu, काष्ठा ftrace_hash, rcu);
	मुक्त_ftrace_hash(hash);
पूर्ण

अटल व्योम मुक्त_ftrace_hash_rcu(काष्ठा ftrace_hash *hash)
अणु
	अगर (!hash || hash == EMPTY_HASH)
		वापस;
	call_rcu(&hash->rcu, __मुक्त_ftrace_hash_rcu);
पूर्ण

व्योम ftrace_मुक्त_filter(काष्ठा ftrace_ops *ops)
अणु
	ftrace_ops_init(ops);
	मुक्त_ftrace_hash(ops->func_hash->filter_hash);
	मुक्त_ftrace_hash(ops->func_hash->notrace_hash);
पूर्ण

अटल काष्ठा ftrace_hash *alloc_ftrace_hash(पूर्णांक size_bits)
अणु
	काष्ठा ftrace_hash *hash;
	पूर्णांक size;

	hash = kzalloc(माप(*hash), GFP_KERNEL);
	अगर (!hash)
		वापस शून्य;

	size = 1 << size_bits;
	hash->buckets = kसुस्मृति(size, माप(*hash->buckets), GFP_KERNEL);

	अगर (!hash->buckets) अणु
		kमुक्त(hash);
		वापस शून्य;
	पूर्ण

	hash->size_bits = size_bits;

	वापस hash;
पूर्ण


अटल पूर्णांक ftrace_add_mod(काष्ठा trace_array *tr,
			  स्थिर अक्षर *func, स्थिर अक्षर *module,
			  पूर्णांक enable)
अणु
	काष्ठा ftrace_mod_load *ftrace_mod;
	काष्ठा list_head *mod_head = enable ? &tr->mod_trace : &tr->mod_notrace;

	ftrace_mod = kzalloc(माप(*ftrace_mod), GFP_KERNEL);
	अगर (!ftrace_mod)
		वापस -ENOMEM;

	ftrace_mod->func = kstrdup(func, GFP_KERNEL);
	ftrace_mod->module = kstrdup(module, GFP_KERNEL);
	ftrace_mod->enable = enable;

	अगर (!ftrace_mod->func || !ftrace_mod->module)
		जाओ out_मुक्त;

	list_add(&ftrace_mod->list, mod_head);

	वापस 0;

 out_मुक्त:
	मुक्त_ftrace_mod(ftrace_mod);

	वापस -ENOMEM;
पूर्ण

अटल काष्ठा ftrace_hash *
alloc_and_copy_ftrace_hash(पूर्णांक size_bits, काष्ठा ftrace_hash *hash)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_hash *new_hash;
	पूर्णांक size;
	पूर्णांक ret;
	पूर्णांक i;

	new_hash = alloc_ftrace_hash(size_bits);
	अगर (!new_hash)
		वापस शून्य;

	अगर (hash)
		new_hash->flags = hash->flags;

	/* Empty hash? */
	अगर (ftrace_hash_empty(hash))
		वापस new_hash;

	size = 1 << hash->size_bits;
	क्रम (i = 0; i < size; i++) अणु
		hlist_क्रम_each_entry(entry, &hash->buckets[i], hlist) अणु
			ret = add_hash_entry(new_hash, entry->ip);
			अगर (ret < 0)
				जाओ मुक्त_hash;
		पूर्ण
	पूर्ण

	FTRACE_WARN_ON(new_hash->count != hash->count);

	वापस new_hash;

 मुक्त_hash:
	मुक्त_ftrace_hash(new_hash);
	वापस शून्य;
पूर्ण

अटल व्योम
ftrace_hash_rec_disable_modअगरy(काष्ठा ftrace_ops *ops, पूर्णांक filter_hash);
अटल व्योम
ftrace_hash_rec_enable_modअगरy(काष्ठा ftrace_ops *ops, पूर्णांक filter_hash);

अटल पूर्णांक ftrace_hash_ipmodअगरy_update(काष्ठा ftrace_ops *ops,
				       काष्ठा ftrace_hash *new_hash);

अटल काष्ठा ftrace_hash *dup_hash(काष्ठा ftrace_hash *src, पूर्णांक size)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_hash *new_hash;
	काष्ठा hlist_head *hhd;
	काष्ठा hlist_node *tn;
	पूर्णांक bits = 0;
	पूर्णांक i;

	/*
	 * Use around half the size (max bit of it), but
	 * a minimum of 2 is fine (as size of 0 or 1 both give 1 क्रम bits).
	 */
	bits = fls(size / 2);

	/* Don't allocate too much */
	अगर (bits > FTRACE_HASH_MAX_BITS)
		bits = FTRACE_HASH_MAX_BITS;

	new_hash = alloc_ftrace_hash(bits);
	अगर (!new_hash)
		वापस शून्य;

	new_hash->flags = src->flags;

	size = 1 << src->size_bits;
	क्रम (i = 0; i < size; i++) अणु
		hhd = &src->buckets[i];
		hlist_क्रम_each_entry_safe(entry, tn, hhd, hlist) अणु
			हटाओ_hash_entry(src, entry);
			__add_hash_entry(new_hash, entry);
		पूर्ण
	पूर्ण
	वापस new_hash;
पूर्ण

अटल काष्ठा ftrace_hash *
__ftrace_hash_move(काष्ठा ftrace_hash *src)
अणु
	पूर्णांक size = src->count;

	/*
	 * If the new source is empty, just वापस the empty_hash.
	 */
	अगर (ftrace_hash_empty(src))
		वापस EMPTY_HASH;

	वापस dup_hash(src, size);
पूर्ण

अटल पूर्णांक
ftrace_hash_move(काष्ठा ftrace_ops *ops, पूर्णांक enable,
		 काष्ठा ftrace_hash **dst, काष्ठा ftrace_hash *src)
अणु
	काष्ठा ftrace_hash *new_hash;
	पूर्णांक ret;

	/* Reject setting notrace hash on IPMODIFY ftrace_ops */
	अगर (ops->flags & FTRACE_OPS_FL_IPMODIFY && !enable)
		वापस -EINVAL;

	new_hash = __ftrace_hash_move(src);
	अगर (!new_hash)
		वापस -ENOMEM;

	/* Make sure this can be applied अगर it is IPMODIFY ftrace_ops */
	अगर (enable) अणु
		/* IPMODIFY should be updated only when filter_hash updating */
		ret = ftrace_hash_ipmodअगरy_update(ops, new_hash);
		अगर (ret < 0) अणु
			मुक्त_ftrace_hash(new_hash);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Remove the current set, update the hash and add
	 * them back.
	 */
	ftrace_hash_rec_disable_modअगरy(ops, enable);

	rcu_assign_poपूर्णांकer(*dst, new_hash);

	ftrace_hash_rec_enable_modअगरy(ops, enable);

	वापस 0;
पूर्ण

अटल bool hash_contains_ip(अचिन्हित दीर्घ ip,
			     काष्ठा ftrace_ops_hash *hash)
अणु
	/*
	 * The function record is a match अगर it exists in the filter
	 * hash and not in the notrace hash. Note, an empty hash is
	 * considered a match क्रम the filter hash, but an empty
	 * notrace hash is considered not in the notrace hash.
	 */
	वापस (ftrace_hash_empty(hash->filter_hash) ||
		__ftrace_lookup_ip(hash->filter_hash, ip)) &&
		(ftrace_hash_empty(hash->notrace_hash) ||
		 !__ftrace_lookup_ip(hash->notrace_hash, ip));
पूर्ण

/*
 * Test the hashes क्रम this ops to see अगर we want to call
 * the ops->func or not.
 *
 * It's a match अगर the ip is in the ops->filter_hash or
 * the filter_hash करोes not exist or is empty,
 *  AND
 * the ip is not in the ops->notrace_hash.
 *
 * This needs to be called with preemption disabled as
 * the hashes are मुक्तd with call_rcu().
 */
पूर्णांक
ftrace_ops_test(काष्ठा ftrace_ops *ops, अचिन्हित दीर्घ ip, व्योम *regs)
अणु
	काष्ठा ftrace_ops_hash hash;
	पूर्णांक ret;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	/*
	 * There's a small race when adding ops that the ftrace handler
	 * that wants regs, may be called without them. We can not
	 * allow that handler to be called अगर regs is शून्य.
	 */
	अगर (regs == शून्य && (ops->flags & FTRACE_OPS_FL_SAVE_REGS))
		वापस 0;
#पूर्ण_अगर

	rcu_assign_poपूर्णांकer(hash.filter_hash, ops->func_hash->filter_hash);
	rcu_assign_poपूर्णांकer(hash.notrace_hash, ops->func_hash->notrace_hash);

	अगर (hash_contains_ip(ip, &hash))
		ret = 1;
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

/*
 * This is a द्विगुन क्रम. Do not use 'break' to अवरोध out of the loop,
 * you must use a जाओ.
 */
#घोषणा करो_क्रम_each_ftrace_rec(pg, rec)					\
	क्रम (pg = ftrace_pages_start; pg; pg = pg->next) अणु		\
		पूर्णांक _____i;						\
		क्रम (_____i = 0; _____i < pg->index; _____i++) अणु	\
			rec = &pg->records[_____i];

#घोषणा जबतक_क्रम_each_ftrace_rec()		\
		पूर्ण				\
	पूर्ण


अटल पूर्णांक ftrace_cmp_recs(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा dyn_ftrace *key = a;
	स्थिर काष्ठा dyn_ftrace *rec = b;

	अगर (key->flags < rec->ip)
		वापस -1;
	अगर (key->ip >= rec->ip + MCOUNT_INSN_SIZE)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा dyn_ftrace *lookup_rec(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec = शून्य;
	काष्ठा dyn_ftrace key;

	key.ip = start;
	key.flags = end;	/* overload flags, as it is अचिन्हित दीर्घ */

	क्रम (pg = ftrace_pages_start; pg; pg = pg->next) अणु
		अगर (end < pg->records[0].ip ||
		    start >= (pg->records[pg->index - 1].ip + MCOUNT_INSN_SIZE))
			जारी;
		rec = द्वा_खोज(&key, pg->records, pg->index,
			      माप(काष्ठा dyn_ftrace),
			      ftrace_cmp_recs);
		अगर (rec)
			अवरोध;
	पूर्ण
	वापस rec;
पूर्ण

/**
 * ftrace_location_range - वापस the first address of a traced location
 *	अगर it touches the given ip range
 * @start: start of range to search.
 * @end: end of range to search (inclusive). @end poपूर्णांकs to the last byte
 *	to check.
 *
 * Returns rec->ip अगर the related ftrace location is a least partly within
 * the given address range. That is, the first address of the inकाष्ठाion
 * that is either a NOP or call to the function tracer. It checks the ftrace
 * पूर्णांकernal tables to determine अगर the address beदीर्घs or not.
 */
अचिन्हित दीर्घ ftrace_location_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा dyn_ftrace *rec;

	rec = lookup_rec(start, end);
	अगर (rec)
		वापस rec->ip;

	वापस 0;
पूर्ण

/**
 * ftrace_location - वापस true अगर the ip giving is a traced location
 * @ip: the inकाष्ठाion poपूर्णांकer to check
 *
 * Returns rec->ip अगर @ip given is a poपूर्णांकer to a ftrace location.
 * That is, the inकाष्ठाion that is either a NOP or call to
 * the function tracer. It checks the ftrace पूर्णांकernal tables to
 * determine अगर the address beदीर्घs or not.
 */
अचिन्हित दीर्घ ftrace_location(अचिन्हित दीर्घ ip)
अणु
	वापस ftrace_location_range(ip, ip);
पूर्ण

/**
 * ftrace_text_reserved - वापस true अगर range contains an ftrace location
 * @start: start of range to search
 * @end: end of range to search (inclusive). @end poपूर्णांकs to the last byte to check.
 *
 * Returns 1 अगर @start and @end contains a ftrace location.
 * That is, the inकाष्ठाion that is either a NOP or call to
 * the function tracer. It checks the ftrace पूर्णांकernal tables to
 * determine अगर the address beदीर्घs or not.
 */
पूर्णांक ftrace_text_reserved(स्थिर व्योम *start, स्थिर व्योम *end)
अणु
	अचिन्हित दीर्घ ret;

	ret = ftrace_location_range((अचिन्हित दीर्घ)start,
				    (अचिन्हित दीर्घ)end);

	वापस (पूर्णांक)!!ret;
पूर्ण

/* Test अगर ops रेजिस्टरed to this rec needs regs */
अटल bool test_rec_ops_needs_regs(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *ops;
	bool keep_regs = false;

	क्रम (ops = ftrace_ops_list;
	     ops != &ftrace_list_end; ops = ops->next) अणु
		/* pass rec in as regs to have non-शून्य val */
		अगर (ftrace_ops_test(ops, rec->ip, rec)) अणु
			अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS) अणु
				keep_regs = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस  keep_regs;
पूर्ण

अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_any(काष्ठा dyn_ftrace *rec);
अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_any_other(काष्ठा dyn_ftrace *rec, काष्ठा ftrace_ops *op_exclude);
अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_next(काष्ठा dyn_ftrace *rec, काष्ठा ftrace_ops *ops);

अटल bool __ftrace_hash_rec_update(काष्ठा ftrace_ops *ops,
				     पूर्णांक filter_hash,
				     bool inc)
अणु
	काष्ठा ftrace_hash *hash;
	काष्ठा ftrace_hash *other_hash;
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec;
	bool update = false;
	पूर्णांक count = 0;
	पूर्णांक all = false;

	/* Only update अगर the ops has been रेजिस्टरed */
	अगर (!(ops->flags & FTRACE_OPS_FL_ENABLED))
		वापस false;

	/*
	 * In the filter_hash हाल:
	 *   If the count is zero, we update all records.
	 *   Otherwise we just update the items in the hash.
	 *
	 * In the notrace_hash हाल:
	 *   We enable the update in the hash.
	 *   As disabling notrace means enabling the tracing,
	 *   and enabling notrace means disabling, the inc variable
	 *   माला_लो inversed.
	 */
	अगर (filter_hash) अणु
		hash = ops->func_hash->filter_hash;
		other_hash = ops->func_hash->notrace_hash;
		अगर (ftrace_hash_empty(hash))
			all = true;
	पूर्ण अन्यथा अणु
		inc = !inc;
		hash = ops->func_hash->notrace_hash;
		other_hash = ops->func_hash->filter_hash;
		/*
		 * If the notrace hash has no items,
		 * then there's nothing to करो.
		 */
		अगर (ftrace_hash_empty(hash))
			वापस false;
	पूर्ण

	करो_क्रम_each_ftrace_rec(pg, rec) अणु
		पूर्णांक in_other_hash = 0;
		पूर्णांक in_hash = 0;
		पूर्णांक match = 0;

		अगर (rec->flags & FTRACE_FL_DISABLED)
			जारी;

		अगर (all) अणु
			/*
			 * Only the filter_hash affects all records.
			 * Update अगर the record is not in the notrace hash.
			 */
			अगर (!other_hash || !ftrace_lookup_ip(other_hash, rec->ip))
				match = 1;
		पूर्ण अन्यथा अणु
			in_hash = !!ftrace_lookup_ip(hash, rec->ip);
			in_other_hash = !!ftrace_lookup_ip(other_hash, rec->ip);

			/*
			 * If filter_hash is set, we want to match all functions
			 * that are in the hash but not in the other hash.
			 *
			 * If filter_hash is not set, then we are decrementing.
			 * That means we match anything that is in the hash
			 * and also in the other_hash. That is, we need to turn
			 * off functions in the other hash because they are disabled
			 * by this hash.
			 */
			अगर (filter_hash && in_hash && !in_other_hash)
				match = 1;
			अन्यथा अगर (!filter_hash && in_hash &&
				 (in_other_hash || ftrace_hash_empty(other_hash)))
				match = 1;
		पूर्ण
		अगर (!match)
			जारी;

		अगर (inc) अणु
			rec->flags++;
			अगर (FTRACE_WARN_ON(ftrace_rec_count(rec) == FTRACE_REF_MAX))
				वापस false;

			अगर (ops->flags & FTRACE_OPS_FL_सूचीECT)
				rec->flags |= FTRACE_FL_सूचीECT;

			/*
			 * If there's only a single callback रेजिस्टरed to a
			 * function, and the ops has a trampoline रेजिस्टरed
			 * क्रम it, then we can call it directly.
			 */
			अगर (ftrace_rec_count(rec) == 1 && ops->trampoline)
				rec->flags |= FTRACE_FL_TRAMP;
			अन्यथा
				/*
				 * If we are adding another function callback
				 * to this function, and the previous had a
				 * custom trampoline in use, then we need to go
				 * back to the शेष trampoline.
				 */
				rec->flags &= ~FTRACE_FL_TRAMP;

			/*
			 * If any ops wants regs saved क्रम this function
			 * then all ops will get saved regs.
			 */
			अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS)
				rec->flags |= FTRACE_FL_REGS;
		पूर्ण अन्यथा अणु
			अगर (FTRACE_WARN_ON(ftrace_rec_count(rec) == 0))
				वापस false;
			rec->flags--;

			/*
			 * Only the पूर्णांकernal direct_ops should have the
			 * सूचीECT flag set. Thus, अगर it is removing a
			 * function, then that function should no दीर्घer
			 * be direct.
			 */
			अगर (ops->flags & FTRACE_OPS_FL_सूचीECT)
				rec->flags &= ~FTRACE_FL_सूचीECT;

			/*
			 * If the rec had REGS enabled and the ops that is
			 * being हटाओd had REGS set, then see अगर there is
			 * still any ops क्रम this record that wants regs.
			 * If not, we can stop recording them.
			 */
			अगर (ftrace_rec_count(rec) > 0 &&
			    rec->flags & FTRACE_FL_REGS &&
			    ops->flags & FTRACE_OPS_FL_SAVE_REGS) अणु
				अगर (!test_rec_ops_needs_regs(rec))
					rec->flags &= ~FTRACE_FL_REGS;
			पूर्ण

			/*
			 * The TRAMP needs to be set only अगर rec count
			 * is decremented to one, and the ops that is
			 * left has a trampoline. As TRAMP can only be
			 * enabled अगर there is only a single ops attached
			 * to it.
			 */
			अगर (ftrace_rec_count(rec) == 1 &&
			    ftrace_find_tramp_ops_any_other(rec, ops))
				rec->flags |= FTRACE_FL_TRAMP;
			अन्यथा
				rec->flags &= ~FTRACE_FL_TRAMP;

			/*
			 * flags will be cleared in ftrace_check_record()
			 * अगर rec count is zero.
			 */
		पूर्ण
		count++;

		/* Must match FTRACE_UPDATE_CALLS in ftrace_modअगरy_all_code() */
		update |= ftrace_test_record(rec, true) != FTRACE_UPDATE_IGNORE;

		/* Shortcut, अगर we handled all records, we are करोne. */
		अगर (!all && count == hash->count)
			वापस update;
	पूर्ण जबतक_क्रम_each_ftrace_rec();

	वापस update;
पूर्ण

अटल bool ftrace_hash_rec_disable(काष्ठा ftrace_ops *ops,
				    पूर्णांक filter_hash)
अणु
	वापस __ftrace_hash_rec_update(ops, filter_hash, 0);
पूर्ण

अटल bool ftrace_hash_rec_enable(काष्ठा ftrace_ops *ops,
				   पूर्णांक filter_hash)
अणु
	वापस __ftrace_hash_rec_update(ops, filter_hash, 1);
पूर्ण

अटल व्योम ftrace_hash_rec_update_modअगरy(काष्ठा ftrace_ops *ops,
					  पूर्णांक filter_hash, पूर्णांक inc)
अणु
	काष्ठा ftrace_ops *op;

	__ftrace_hash_rec_update(ops, filter_hash, inc);

	अगर (ops->func_hash != &global_ops.local_hash)
		वापस;

	/*
	 * If the ops shares the global_ops hash, then we need to update
	 * all ops that are enabled and use this hash.
	 */
	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		/* Alपढ़ोy करोne */
		अगर (op == ops)
			जारी;
		अगर (op->func_hash == &global_ops.local_hash)
			__ftrace_hash_rec_update(op, filter_hash, inc);
	पूर्ण जबतक_क्रम_each_ftrace_op(op);
पूर्ण

अटल व्योम ftrace_hash_rec_disable_modअगरy(काष्ठा ftrace_ops *ops,
					   पूर्णांक filter_hash)
अणु
	ftrace_hash_rec_update_modअगरy(ops, filter_hash, 0);
पूर्ण

अटल व्योम ftrace_hash_rec_enable_modअगरy(काष्ठा ftrace_ops *ops,
					  पूर्णांक filter_hash)
अणु
	ftrace_hash_rec_update_modअगरy(ops, filter_hash, 1);
पूर्ण

/*
 * Try to update IPMODIFY flag on each ftrace_rec. Return 0 अगर it is OK
 * or no-needed to update, -EBUSY अगर it detects a conflict of the flag
 * on a ftrace_rec, and -EINVAL अगर the new_hash tries to trace all recs.
 * Note that old_hash and new_hash has below meanings
 *  - If the hash is शून्य, it hits all recs (अगर IPMODIFY is set, this is rejected)
 *  - If the hash is EMPTY_HASH, it hits nothing
 *  - Anything अन्यथा hits the recs which match the hash entries.
 */
अटल पूर्णांक __ftrace_hash_update_ipmodअगरy(काष्ठा ftrace_ops *ops,
					 काष्ठा ftrace_hash *old_hash,
					 काष्ठा ftrace_hash *new_hash)
अणु
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec, *end = शून्य;
	पूर्णांक in_old, in_new;

	/* Only update अगर the ops has been रेजिस्टरed */
	अगर (!(ops->flags & FTRACE_OPS_FL_ENABLED))
		वापस 0;

	अगर (!(ops->flags & FTRACE_OPS_FL_IPMODIFY))
		वापस 0;

	/*
	 * Since the IPMODIFY is a very address sensitive action, we करो not
	 * allow ftrace_ops to set all functions to new hash.
	 */
	अगर (!new_hash || !old_hash)
		वापस -EINVAL;

	/* Update rec->flags */
	करो_क्रम_each_ftrace_rec(pg, rec) अणु

		अगर (rec->flags & FTRACE_FL_DISABLED)
			जारी;

		/* We need to update only dअगरferences of filter_hash */
		in_old = !!ftrace_lookup_ip(old_hash, rec->ip);
		in_new = !!ftrace_lookup_ip(new_hash, rec->ip);
		अगर (in_old == in_new)
			जारी;

		अगर (in_new) अणु
			/* New entries must ensure no others are using it */
			अगर (rec->flags & FTRACE_FL_IPMODIFY)
				जाओ rollback;
			rec->flags |= FTRACE_FL_IPMODIFY;
		पूर्ण अन्यथा /* Removed entry */
			rec->flags &= ~FTRACE_FL_IPMODIFY;
	पूर्ण जबतक_क्रम_each_ftrace_rec();

	वापस 0;

rollback:
	end = rec;

	/* Roll back what we did above */
	करो_क्रम_each_ftrace_rec(pg, rec) अणु

		अगर (rec->flags & FTRACE_FL_DISABLED)
			जारी;

		अगर (rec == end)
			जाओ err_out;

		in_old = !!ftrace_lookup_ip(old_hash, rec->ip);
		in_new = !!ftrace_lookup_ip(new_hash, rec->ip);
		अगर (in_old == in_new)
			जारी;

		अगर (in_new)
			rec->flags &= ~FTRACE_FL_IPMODIFY;
		अन्यथा
			rec->flags |= FTRACE_FL_IPMODIFY;
	पूर्ण जबतक_क्रम_each_ftrace_rec();

err_out:
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ftrace_hash_ipmodअगरy_enable(काष्ठा ftrace_ops *ops)
अणु
	काष्ठा ftrace_hash *hash = ops->func_hash->filter_hash;

	अगर (ftrace_hash_empty(hash))
		hash = शून्य;

	वापस __ftrace_hash_update_ipmodअगरy(ops, EMPTY_HASH, hash);
पूर्ण

/* Disabling always succeeds */
अटल व्योम ftrace_hash_ipmodअगरy_disable(काष्ठा ftrace_ops *ops)
अणु
	काष्ठा ftrace_hash *hash = ops->func_hash->filter_hash;

	अगर (ftrace_hash_empty(hash))
		hash = शून्य;

	__ftrace_hash_update_ipmodअगरy(ops, hash, EMPTY_HASH);
पूर्ण

अटल पूर्णांक ftrace_hash_ipmodअगरy_update(काष्ठा ftrace_ops *ops,
				       काष्ठा ftrace_hash *new_hash)
अणु
	काष्ठा ftrace_hash *old_hash = ops->func_hash->filter_hash;

	अगर (ftrace_hash_empty(old_hash))
		old_hash = शून्य;

	अगर (ftrace_hash_empty(new_hash))
		new_hash = शून्य;

	वापस __ftrace_hash_update_ipmodअगरy(ops, old_hash, new_hash);
पूर्ण

अटल व्योम prपूर्णांक_ip_ins(स्थिर अक्षर *fmt, स्थिर अचिन्हित अक्षर *p)
अणु
	अक्षर ins[MCOUNT_INSN_SIZE];
	पूर्णांक i;

	अगर (copy_from_kernel_nofault(ins, p, MCOUNT_INSN_SIZE)) अणु
		prपूर्णांकk(KERN_CONT "%s[FAULT] %px\n", fmt, p);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_CONT "%s", fmt);

	क्रम (i = 0; i < MCOUNT_INSN_SIZE; i++)
		prपूर्णांकk(KERN_CONT "%s%02x", i ? ":" : "", ins[i]);
पूर्ण

क्रमागत ftrace_bug_type ftrace_bug_type;
स्थिर व्योम *ftrace_expected;

अटल व्योम prपूर्णांक_bug_type(व्योम)
अणु
	चयन (ftrace_bug_type) अणु
	हाल FTRACE_BUG_UNKNOWN:
		अवरोध;
	हाल FTRACE_BUG_INIT:
		pr_info("Initializing ftrace call sites\n");
		अवरोध;
	हाल FTRACE_BUG_NOP:
		pr_info("Setting ftrace call site to NOP\n");
		अवरोध;
	हाल FTRACE_BUG_CALL:
		pr_info("Setting ftrace call site to call ftrace function\n");
		अवरोध;
	हाल FTRACE_BUG_UPDATE:
		pr_info("Updating ftrace call site to call a different ftrace function\n");
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ftrace_bug - report and shutकरोwn function tracer
 * @failed: The failed type (EFAULT, EINVAL, EPERM)
 * @rec: The record that failed
 *
 * The arch code that enables or disables the function tracing
 * can call ftrace_bug() when it has detected a problem in
 * modअगरying the code. @failed should be one of either:
 * EFAULT - अगर the problem happens on पढ़ोing the @ip address
 * EINVAL - अगर what is पढ़ो at @ip is not what was expected
 * EPERM - अगर the problem happens on writing to the @ip address
 */
व्योम ftrace_bug(पूर्णांक failed, काष्ठा dyn_ftrace *rec)
अणु
	अचिन्हित दीर्घ ip = rec ? rec->ip : 0;

	pr_info("------------[ ftrace bug ]------------\n");

	चयन (failed) अणु
	हाल -EFAULT:
		pr_info("ftrace faulted on modifying ");
		prपूर्णांक_ip_sym(KERN_INFO, ip);
		अवरोध;
	हाल -EINVAL:
		pr_info("ftrace failed to modify ");
		prपूर्णांक_ip_sym(KERN_INFO, ip);
		prपूर्णांक_ip_ins(" actual:   ", (अचिन्हित अक्षर *)ip);
		pr_cont("\n");
		अगर (ftrace_expected) अणु
			prपूर्णांक_ip_ins(" expected: ", ftrace_expected);
			pr_cont("\n");
		पूर्ण
		अवरोध;
	हाल -EPERM:
		pr_info("ftrace faulted on writing ");
		prपूर्णांक_ip_sym(KERN_INFO, ip);
		अवरोध;
	शेष:
		pr_info("ftrace faulted on unknown error ");
		prपूर्णांक_ip_sym(KERN_INFO, ip);
	पूर्ण
	prपूर्णांक_bug_type();
	अगर (rec) अणु
		काष्ठा ftrace_ops *ops = शून्य;

		pr_info("ftrace record flags: %lx\n", rec->flags);
		pr_cont(" (%ld)%s", ftrace_rec_count(rec),
			rec->flags & FTRACE_FL_REGS ? " R" : "  ");
		अगर (rec->flags & FTRACE_FL_TRAMP_EN) अणु
			ops = ftrace_find_tramp_ops_any(rec);
			अगर (ops) अणु
				करो अणु
					pr_cont("\ttramp: %pS (%pS)",
						(व्योम *)ops->trampoline,
						(व्योम *)ops->func);
					ops = ftrace_find_tramp_ops_next(rec, ops);
				पूर्ण जबतक (ops);
			पूर्ण अन्यथा
				pr_cont("\ttramp: ERROR!");

		पूर्ण
		ip = ftrace_get_addr_curr(rec);
		pr_cont("\n expected tramp: %lx\n", ip);
	पूर्ण

	FTRACE_WARN_ON_ONCE(1);
पूर्ण

अटल पूर्णांक ftrace_check_record(काष्ठा dyn_ftrace *rec, bool enable, bool update)
अणु
	अचिन्हित दीर्घ flag = 0UL;

	ftrace_bug_type = FTRACE_BUG_UNKNOWN;

	अगर (rec->flags & FTRACE_FL_DISABLED)
		वापस FTRACE_UPDATE_IGNORE;

	/*
	 * If we are updating calls:
	 *
	 *   If the record has a ref count, then we need to enable it
	 *   because someone is using it.
	 *
	 *   Otherwise we make sure its disabled.
	 *
	 * If we are disabling calls, then disable all records that
	 * are enabled.
	 */
	अगर (enable && ftrace_rec_count(rec))
		flag = FTRACE_FL_ENABLED;

	/*
	 * If enabling and the REGS flag करोes not match the REGS_EN, or
	 * the TRAMP flag करोesn't match the TRAMP_EN, then करो not ignore
	 * this record. Set flags to fail the compare against ENABLED.
	 * Same क्रम direct calls.
	 */
	अगर (flag) अणु
		अगर (!(rec->flags & FTRACE_FL_REGS) !=
		    !(rec->flags & FTRACE_FL_REGS_EN))
			flag |= FTRACE_FL_REGS;

		अगर (!(rec->flags & FTRACE_FL_TRAMP) !=
		    !(rec->flags & FTRACE_FL_TRAMP_EN))
			flag |= FTRACE_FL_TRAMP;

		/*
		 * Direct calls are special, as count matters.
		 * We must test the record क्रम direct, अगर the
		 * सूचीECT and सूचीECT_EN करो not match, but only
		 * अगर the count is 1. That's because, अगर the
		 * count is something other than one, we करो not
		 * want the direct enabled (it will be करोne via the
		 * direct helper). But अगर सूचीECT_EN is set, and
		 * the count is not one, we need to clear it.
		 */
		अगर (ftrace_rec_count(rec) == 1) अणु
			अगर (!(rec->flags & FTRACE_FL_सूचीECT) !=
			    !(rec->flags & FTRACE_FL_सूचीECT_EN))
				flag |= FTRACE_FL_सूचीECT;
		पूर्ण अन्यथा अगर (rec->flags & FTRACE_FL_सूचीECT_EN) अणु
			flag |= FTRACE_FL_सूचीECT;
		पूर्ण
	पूर्ण

	/* If the state of this record hasn't changed, then करो nothing */
	अगर ((rec->flags & FTRACE_FL_ENABLED) == flag)
		वापस FTRACE_UPDATE_IGNORE;

	अगर (flag) अणु
		/* Save off अगर rec is being enabled (क्रम वापस value) */
		flag ^= rec->flags & FTRACE_FL_ENABLED;

		अगर (update) अणु
			rec->flags |= FTRACE_FL_ENABLED;
			अगर (flag & FTRACE_FL_REGS) अणु
				अगर (rec->flags & FTRACE_FL_REGS)
					rec->flags |= FTRACE_FL_REGS_EN;
				अन्यथा
					rec->flags &= ~FTRACE_FL_REGS_EN;
			पूर्ण
			अगर (flag & FTRACE_FL_TRAMP) अणु
				अगर (rec->flags & FTRACE_FL_TRAMP)
					rec->flags |= FTRACE_FL_TRAMP_EN;
				अन्यथा
					rec->flags &= ~FTRACE_FL_TRAMP_EN;
			पूर्ण

			अगर (flag & FTRACE_FL_सूचीECT) अणु
				/*
				 * If there's only one user (direct_ops helper)
				 * then we can call the direct function
				 * directly (no ftrace trampoline).
				 */
				अगर (ftrace_rec_count(rec) == 1) अणु
					अगर (rec->flags & FTRACE_FL_सूचीECT)
						rec->flags |= FTRACE_FL_सूचीECT_EN;
					अन्यथा
						rec->flags &= ~FTRACE_FL_सूचीECT_EN;
				पूर्ण अन्यथा अणु
					/*
					 * Can only call directly अगर there's
					 * only one callback to the function.
					 */
					rec->flags &= ~FTRACE_FL_सूचीECT_EN;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * If this record is being updated from a nop, then
		 *   वापस UPDATE_MAKE_CALL.
		 * Otherwise,
		 *   वापस UPDATE_MODIFY_CALL to tell the caller to convert
		 *   from the save regs, to a non-save regs function or
		 *   vice versa, or from a trampoline call.
		 */
		अगर (flag & FTRACE_FL_ENABLED) अणु
			ftrace_bug_type = FTRACE_BUG_CALL;
			वापस FTRACE_UPDATE_MAKE_CALL;
		पूर्ण

		ftrace_bug_type = FTRACE_BUG_UPDATE;
		वापस FTRACE_UPDATE_MODIFY_CALL;
	पूर्ण

	अगर (update) अणु
		/* If there's no more users, clear all flags */
		अगर (!ftrace_rec_count(rec))
			rec->flags = 0;
		अन्यथा
			/*
			 * Just disable the record, but keep the ops TRAMP
			 * and REGS states. The _EN flags must be disabled though.
			 */
			rec->flags &= ~(FTRACE_FL_ENABLED | FTRACE_FL_TRAMP_EN |
					FTRACE_FL_REGS_EN | FTRACE_FL_सूचीECT_EN);
	पूर्ण

	ftrace_bug_type = FTRACE_BUG_NOP;
	वापस FTRACE_UPDATE_MAKE_NOP;
पूर्ण

/**
 * ftrace_update_record, set a record that now is tracing or not
 * @rec: the record to update
 * @enable: set to true अगर the record is tracing, false to क्रमce disable
 *
 * The records that represent all functions that can be traced need
 * to be updated when tracing has been enabled.
 */
पूर्णांक ftrace_update_record(काष्ठा dyn_ftrace *rec, bool enable)
अणु
	वापस ftrace_check_record(rec, enable, true);
पूर्ण

/**
 * ftrace_test_record, check अगर the record has been enabled or not
 * @rec: the record to test
 * @enable: set to true to check अगर enabled, false अगर it is disabled
 *
 * The arch code may need to test अगर a record is alपढ़ोy set to
 * tracing to determine how to modअगरy the function code that it
 * represents.
 */
पूर्णांक ftrace_test_record(काष्ठा dyn_ftrace *rec, bool enable)
अणु
	वापस ftrace_check_record(rec, enable, false);
पूर्ण

अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_any(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *op;
	अचिन्हित दीर्घ ip = rec->ip;

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु

		अगर (!op->trampoline)
			जारी;

		अगर (hash_contains_ip(ip, op->func_hash))
			वापस op;
	पूर्ण जबतक_क्रम_each_ftrace_op(op);

	वापस शून्य;
पूर्ण

अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_any_other(काष्ठा dyn_ftrace *rec, काष्ठा ftrace_ops *op_exclude)
अणु
	काष्ठा ftrace_ops *op;
	अचिन्हित दीर्घ ip = rec->ip;

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु

		अगर (op == op_exclude || !op->trampoline)
			जारी;

		अगर (hash_contains_ip(ip, op->func_hash))
			वापस op;
	पूर्ण जबतक_क्रम_each_ftrace_op(op);

	वापस शून्य;
पूर्ण

अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_next(काष्ठा dyn_ftrace *rec,
			   काष्ठा ftrace_ops *op)
अणु
	अचिन्हित दीर्घ ip = rec->ip;

	जबतक_क्रम_each_ftrace_op(op) अणु

		अगर (!op->trampoline)
			जारी;

		अगर (hash_contains_ip(ip, op->func_hash))
			वापस op;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_curr(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *op;
	अचिन्हित दीर्घ ip = rec->ip;

	/*
	 * Need to check हटाओd ops first.
	 * If they are being हटाओd, and this rec has a tramp,
	 * and this rec is in the ops list, then it would be the
	 * one with the tramp.
	 */
	अगर (हटाओd_ops) अणु
		अगर (hash_contains_ip(ip, &हटाओd_ops->old_hash))
			वापस हटाओd_ops;
	पूर्ण

	/*
	 * Need to find the current trampoline क्रम a rec.
	 * Now, a trampoline is only attached to a rec अगर there
	 * was a single 'ops' attached to it. But this can be called
	 * when we are adding another op to the rec or removing the
	 * current one. Thus, अगर the op is being added, we can
	 * ignore it because it hasn't attached itself to the rec
	 * yet.
	 *
	 * If an ops is being modअगरied (hooking to dअगरferent functions)
	 * then we करोn't care about the new functions that are being
	 * added, just the old ones (that are probably being हटाओd).
	 *
	 * If we are adding an ops to a function that alपढ़ोy is using
	 * a trampoline, it needs to be हटाओd (trampolines are only
	 * क्रम single ops connected), then an ops that is not being
	 * modअगरied also needs to be checked.
	 */
	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु

		अगर (!op->trampoline)
			जारी;

		/*
		 * If the ops is being added, it hasn't gotten to
		 * the poपूर्णांक to be हटाओd from this tree yet.
		 */
		अगर (op->flags & FTRACE_OPS_FL_ADDING)
			जारी;


		/*
		 * If the ops is being modअगरied and is in the old
		 * hash, then it is probably being हटाओd from this
		 * function.
		 */
		अगर ((op->flags & FTRACE_OPS_FL_MODIFYING) &&
		    hash_contains_ip(ip, &op->old_hash))
			वापस op;
		/*
		 * If the ops is not being added or modअगरied, and it's
		 * in its normal filter hash, then this must be the one
		 * we want!
		 */
		अगर (!(op->flags & FTRACE_OPS_FL_MODIFYING) &&
		    hash_contains_ip(ip, op->func_hash))
			वापस op;

	पूर्ण जबतक_क्रम_each_ftrace_op(op);

	वापस शून्य;
पूर्ण

अटल काष्ठा ftrace_ops *
ftrace_find_tramp_ops_new(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *op;
	अचिन्हित दीर्घ ip = rec->ip;

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		/* pass rec in as regs to have non-शून्य val */
		अगर (hash_contains_ip(ip, op->func_hash))
			वापस op;
	पूर्ण जबतक_क्रम_each_ftrace_op(op);

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS
/* Protected by rcu_tasks क्रम पढ़ोing, and direct_mutex क्रम writing */
अटल काष्ठा ftrace_hash *direct_functions = EMPTY_HASH;
अटल DEFINE_MUTEX(direct_mutex);
पूर्णांक ftrace_direct_func_count;

/*
 * Search the direct_functions hash to see अगर the given inकाष्ठाion poपूर्णांकer
 * has a direct caller attached to it.
 */
अचिन्हित दीर्घ ftrace_find_rec_direct(अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_func_entry *entry;

	entry = __ftrace_lookup_ip(direct_functions, ip);
	अगर (!entry)
		वापस 0;

	वापस entry->direct;
पूर्ण

अटल व्योम call_direct_funcs(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ pip,
			      काष्ठा ftrace_ops *ops, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा pt_regs *regs = ftrace_get_regs(fregs);
	अचिन्हित दीर्घ addr;

	addr = ftrace_find_rec_direct(ip);
	अगर (!addr)
		वापस;

	arch_ftrace_set_direct_caller(regs, addr);
पूर्ण

काष्ठा ftrace_ops direct_ops = अणु
	.func		= call_direct_funcs,
	.flags		= FTRACE_OPS_FL_IPMODIFY
			  | FTRACE_OPS_FL_सूचीECT | FTRACE_OPS_FL_SAVE_REGS
			  | FTRACE_OPS_FL_PERMANENT,
	/*
	 * By declaring the मुख्य trampoline as this trampoline
	 * it will never have one allocated क्रम it. Allocated
	 * trampolines should not call direct functions.
	 * The direct_ops should only be called by the builtin
	 * ftrace_regs_caller trampoline.
	 */
	.trampoline	= FTRACE_REGS_ADDR,
पूर्ण;
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS */

/**
 * ftrace_get_addr_new - Get the call address to set to
 * @rec:  The ftrace record descriptor
 *
 * If the record has the FTRACE_FL_REGS set, that means that it
 * wants to convert to a callback that saves all regs. If FTRACE_FL_REGS
 * is not set, then it wants to convert to the normal callback.
 *
 * Returns the address of the trampoline to set to
 */
अचिन्हित दीर्घ ftrace_get_addr_new(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *ops;
	अचिन्हित दीर्घ addr;

	अगर ((rec->flags & FTRACE_FL_सूचीECT) &&
	    (ftrace_rec_count(rec) == 1)) अणु
		addr = ftrace_find_rec_direct(rec->ip);
		अगर (addr)
			वापस addr;
		WARN_ON_ONCE(1);
	पूर्ण

	/* Trampolines take precedence over regs */
	अगर (rec->flags & FTRACE_FL_TRAMP) अणु
		ops = ftrace_find_tramp_ops_new(rec);
		अगर (FTRACE_WARN_ON(!ops || !ops->trampoline)) अणु
			pr_warn("Bad trampoline accounting at: %p (%pS) (%lx)\n",
				(व्योम *)rec->ip, (व्योम *)rec->ip, rec->flags);
			/* Ftrace is shutting करोwn, वापस anything */
			वापस (अचिन्हित दीर्घ)FTRACE_ADDR;
		पूर्ण
		वापस ops->trampoline;
	पूर्ण

	अगर (rec->flags & FTRACE_FL_REGS)
		वापस (अचिन्हित दीर्घ)FTRACE_REGS_ADDR;
	अन्यथा
		वापस (अचिन्हित दीर्घ)FTRACE_ADDR;
पूर्ण

/**
 * ftrace_get_addr_curr - Get the call address that is alपढ़ोy there
 * @rec:  The ftrace record descriptor
 *
 * The FTRACE_FL_REGS_EN is set when the record alपढ़ोy poपूर्णांकs to
 * a function that saves all the regs. Basically the '_EN' version
 * represents the current state of the function.
 *
 * Returns the address of the trampoline that is currently being called
 */
अचिन्हित दीर्घ ftrace_get_addr_curr(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *ops;
	अचिन्हित दीर्घ addr;

	/* Direct calls take precedence over trampolines */
	अगर (rec->flags & FTRACE_FL_सूचीECT_EN) अणु
		addr = ftrace_find_rec_direct(rec->ip);
		अगर (addr)
			वापस addr;
		WARN_ON_ONCE(1);
	पूर्ण

	/* Trampolines take precedence over regs */
	अगर (rec->flags & FTRACE_FL_TRAMP_EN) अणु
		ops = ftrace_find_tramp_ops_curr(rec);
		अगर (FTRACE_WARN_ON(!ops)) अणु
			pr_warn("Bad trampoline accounting at: %p (%pS)\n",
				(व्योम *)rec->ip, (व्योम *)rec->ip);
			/* Ftrace is shutting करोwn, वापस anything */
			वापस (अचिन्हित दीर्घ)FTRACE_ADDR;
		पूर्ण
		वापस ops->trampoline;
	पूर्ण

	अगर (rec->flags & FTRACE_FL_REGS_EN)
		वापस (अचिन्हित दीर्घ)FTRACE_REGS_ADDR;
	अन्यथा
		वापस (अचिन्हित दीर्घ)FTRACE_ADDR;
पूर्ण

अटल पूर्णांक
__ftrace_replace_code(काष्ठा dyn_ftrace *rec, bool enable)
अणु
	अचिन्हित दीर्घ ftrace_old_addr;
	अचिन्हित दीर्घ ftrace_addr;
	पूर्णांक ret;

	ftrace_addr = ftrace_get_addr_new(rec);

	/* This needs to be करोne beक्रमe we call ftrace_update_record */
	ftrace_old_addr = ftrace_get_addr_curr(rec);

	ret = ftrace_update_record(rec, enable);

	ftrace_bug_type = FTRACE_BUG_UNKNOWN;

	चयन (ret) अणु
	हाल FTRACE_UPDATE_IGNORE:
		वापस 0;

	हाल FTRACE_UPDATE_MAKE_CALL:
		ftrace_bug_type = FTRACE_BUG_CALL;
		वापस ftrace_make_call(rec, ftrace_addr);

	हाल FTRACE_UPDATE_MAKE_NOP:
		ftrace_bug_type = FTRACE_BUG_NOP;
		वापस ftrace_make_nop(शून्य, rec, ftrace_old_addr);

	हाल FTRACE_UPDATE_MODIFY_CALL:
		ftrace_bug_type = FTRACE_BUG_UPDATE;
		वापस ftrace_modअगरy_call(rec, ftrace_old_addr, ftrace_addr);
	पूर्ण

	वापस -1; /* unknown ftrace bug */
पूर्ण

व्योम __weak ftrace_replace_code(पूर्णांक mod_flags)
अणु
	काष्ठा dyn_ftrace *rec;
	काष्ठा ftrace_page *pg;
	bool enable = mod_flags & FTRACE_MODIFY_ENABLE_FL;
	पूर्णांक schedulable = mod_flags & FTRACE_MODIFY_MAY_SLEEP_FL;
	पूर्णांक failed;

	अगर (unlikely(ftrace_disabled))
		वापस;

	करो_क्रम_each_ftrace_rec(pg, rec) अणु

		अगर (rec->flags & FTRACE_FL_DISABLED)
			जारी;

		failed = __ftrace_replace_code(rec, enable);
		अगर (failed) अणु
			ftrace_bug(failed, rec);
			/* Stop processing */
			वापस;
		पूर्ण
		अगर (schedulable)
			cond_resched();
	पूर्ण जबतक_क्रम_each_ftrace_rec();
पूर्ण

काष्ठा ftrace_rec_iter अणु
	काष्ठा ftrace_page	*pg;
	पूर्णांक			index;
पूर्ण;

/**
 * ftrace_rec_iter_start, start up iterating over traced functions
 *
 * Returns an iterator handle that is used to iterate over all
 * the records that represent address locations where functions
 * are traced.
 *
 * May वापस शून्य अगर no records are available.
 */
काष्ठा ftrace_rec_iter *ftrace_rec_iter_start(व्योम)
अणु
	/*
	 * We only use a single iterator.
	 * Protected by the ftrace_lock mutex.
	 */
	अटल काष्ठा ftrace_rec_iter ftrace_rec_iter;
	काष्ठा ftrace_rec_iter *iter = &ftrace_rec_iter;

	iter->pg = ftrace_pages_start;
	iter->index = 0;

	/* Could have empty pages */
	जबतक (iter->pg && !iter->pg->index)
		iter->pg = iter->pg->next;

	अगर (!iter->pg)
		वापस शून्य;

	वापस iter;
पूर्ण

/**
 * ftrace_rec_iter_next, get the next record to process.
 * @iter: The handle to the iterator.
 *
 * Returns the next iterator after the given iterator @iter.
 */
काष्ठा ftrace_rec_iter *ftrace_rec_iter_next(काष्ठा ftrace_rec_iter *iter)
अणु
	iter->index++;

	अगर (iter->index >= iter->pg->index) अणु
		iter->pg = iter->pg->next;
		iter->index = 0;

		/* Could have empty pages */
		जबतक (iter->pg && !iter->pg->index)
			iter->pg = iter->pg->next;
	पूर्ण

	अगर (!iter->pg)
		वापस शून्य;

	वापस iter;
पूर्ण

/**
 * ftrace_rec_iter_record, get the record at the iterator location
 * @iter: The current iterator location
 *
 * Returns the record that the current @iter is at.
 */
काष्ठा dyn_ftrace *ftrace_rec_iter_record(काष्ठा ftrace_rec_iter *iter)
अणु
	वापस &iter->pg->records[iter->index];
पूर्ण

अटल पूर्णांक
ftrace_nop_initialize(काष्ठा module *mod, काष्ठा dyn_ftrace *rec)
अणु
	पूर्णांक ret;

	अगर (unlikely(ftrace_disabled))
		वापस 0;

	ret = ftrace_init_nop(mod, rec);
	अगर (ret) अणु
		ftrace_bug_type = FTRACE_BUG_INIT;
		ftrace_bug(ret, rec);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * archs can override this function अगर they must करो something
 * beक्रमe the modअगरying code is perक्रमmed.
 */
पूर्णांक __weak ftrace_arch_code_modअगरy_prepare(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * archs can override this function अगर they must करो something
 * after the modअगरying code is perक्रमmed.
 */
पूर्णांक __weak ftrace_arch_code_modअगरy_post_process(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम ftrace_modअगरy_all_code(पूर्णांक command)
अणु
	पूर्णांक update = command & FTRACE_UPDATE_TRACE_FUNC;
	पूर्णांक mod_flags = 0;
	पूर्णांक err = 0;

	अगर (command & FTRACE_MAY_SLEEP)
		mod_flags = FTRACE_MODIFY_MAY_SLEEP_FL;

	/*
	 * If the ftrace_caller calls a ftrace_ops func directly,
	 * we need to make sure that it only traces functions it
	 * expects to trace. When करोing the चयन of functions,
	 * we need to update to the ftrace_ops_list_func first
	 * beक्रमe the transition between old and new calls are set,
	 * as the ftrace_ops_list_func will check the ops hashes
	 * to make sure the ops are having the right functions
	 * traced.
	 */
	अगर (update) अणु
		err = ftrace_update_ftrace_func(ftrace_ops_list_func);
		अगर (FTRACE_WARN_ON(err))
			वापस;
	पूर्ण

	अगर (command & FTRACE_UPDATE_CALLS)
		ftrace_replace_code(mod_flags | FTRACE_MODIFY_ENABLE_FL);
	अन्यथा अगर (command & FTRACE_DISABLE_CALLS)
		ftrace_replace_code(mod_flags);

	अगर (update && ftrace_trace_function != ftrace_ops_list_func) अणु
		function_trace_op = set_function_trace_op;
		smp_wmb();
		/* If irqs are disabled, we are in stop machine */
		अगर (!irqs_disabled())
			smp_call_function(ftrace_sync_ipi, शून्य, 1);
		err = ftrace_update_ftrace_func(ftrace_trace_function);
		अगर (FTRACE_WARN_ON(err))
			वापस;
	पूर्ण

	अगर (command & FTRACE_START_FUNC_RET)
		err = ftrace_enable_ftrace_graph_caller();
	अन्यथा अगर (command & FTRACE_STOP_FUNC_RET)
		err = ftrace_disable_ftrace_graph_caller();
	FTRACE_WARN_ON(err);
पूर्ण

अटल पूर्णांक __ftrace_modअगरy_code(व्योम *data)
अणु
	पूर्णांक *command = data;

	ftrace_modअगरy_all_code(*command);

	वापस 0;
पूर्ण

/**
 * ftrace_run_stop_machine, go back to the stop machine method
 * @command: The command to tell ftrace what to करो
 *
 * If an arch needs to fall back to the stop machine method, the
 * it can call this function.
 */
व्योम ftrace_run_stop_machine(पूर्णांक command)
अणु
	stop_machine(__ftrace_modअगरy_code, &command, शून्य);
पूर्ण

/**
 * arch_ftrace_update_code, modअगरy the code to trace or not trace
 * @command: The command that needs to be करोne
 *
 * Archs can override this function अगर it करोes not need to
 * run stop_machine() to modअगरy code.
 */
व्योम __weak arch_ftrace_update_code(पूर्णांक command)
अणु
	ftrace_run_stop_machine(command);
पूर्ण

अटल व्योम ftrace_run_update_code(पूर्णांक command)
अणु
	पूर्णांक ret;

	ret = ftrace_arch_code_modअगरy_prepare();
	FTRACE_WARN_ON(ret);
	अगर (ret)
		वापस;

	/*
	 * By शेष we use stop_machine() to modअगरy the code.
	 * But archs can करो what ever they want as दीर्घ as it
	 * is safe. The stop_machine() is the safest, but also
	 * produces the most overhead.
	 */
	arch_ftrace_update_code(command);

	ret = ftrace_arch_code_modअगरy_post_process();
	FTRACE_WARN_ON(ret);
पूर्ण

अटल व्योम ftrace_run_modअगरy_code(काष्ठा ftrace_ops *ops, पूर्णांक command,
				   काष्ठा ftrace_ops_hash *old_hash)
अणु
	ops->flags |= FTRACE_OPS_FL_MODIFYING;
	ops->old_hash.filter_hash = old_hash->filter_hash;
	ops->old_hash.notrace_hash = old_hash->notrace_hash;
	ftrace_run_update_code(command);
	ops->old_hash.filter_hash = शून्य;
	ops->old_hash.notrace_hash = शून्य;
	ops->flags &= ~FTRACE_OPS_FL_MODIFYING;
पूर्ण

अटल ftrace_func_t saved_ftrace_func;
अटल पूर्णांक ftrace_start_up;

व्योम __weak arch_ftrace_trampoline_मुक्त(काष्ठा ftrace_ops *ops)
अणु
पूर्ण

/* List of trace_ops that have allocated trampolines */
अटल LIST_HEAD(ftrace_ops_trampoline_list);

अटल व्योम ftrace_add_trampoline_to_kallsyms(काष्ठा ftrace_ops *ops)
अणु
	lockdep_निश्चित_held(&ftrace_lock);
	list_add_rcu(&ops->list, &ftrace_ops_trampoline_list);
पूर्ण

अटल व्योम ftrace_हटाओ_trampoline_from_kallsyms(काष्ठा ftrace_ops *ops)
अणु
	lockdep_निश्चित_held(&ftrace_lock);
	list_del_rcu(&ops->list);
	synchronize_rcu();
पूर्ण

/*
 * "__builtin__ftrace" is used as a module name in /proc/kallsyms क्रम symbols
 * क्रम pages allocated क्रम ftrace purposes, even though "__builtin__ftrace" is
 * not a module.
 */
#घोषणा FTRACE_TRAMPOLINE_MOD "__builtin__ftrace"
#घोषणा FTRACE_TRAMPOLINE_SYM "ftrace_trampoline"

अटल व्योम ftrace_trampoline_मुक्त(काष्ठा ftrace_ops *ops)
अणु
	अगर (ops && (ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP) &&
	    ops->trampoline) अणु
		/*
		 * Record the text poke event beक्रमe the ksymbol unरेजिस्टर
		 * event.
		 */
		perf_event_text_poke((व्योम *)ops->trampoline,
				     (व्योम *)ops->trampoline,
				     ops->trampoline_size, शून्य, 0);
		perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_OOL,
				   ops->trampoline, ops->trampoline_size,
				   true, FTRACE_TRAMPOLINE_SYM);
		/* Remove from kallsyms after the perf events */
		ftrace_हटाओ_trampoline_from_kallsyms(ops);
	पूर्ण

	arch_ftrace_trampoline_मुक्त(ops);
पूर्ण

अटल व्योम ftrace_startup_enable(पूर्णांक command)
अणु
	अगर (saved_ftrace_func != ftrace_trace_function) अणु
		saved_ftrace_func = ftrace_trace_function;
		command |= FTRACE_UPDATE_TRACE_FUNC;
	पूर्ण

	अगर (!command || !ftrace_enabled)
		वापस;

	ftrace_run_update_code(command);
पूर्ण

अटल व्योम ftrace_startup_all(पूर्णांक command)
अणु
	update_all_ops = true;
	ftrace_startup_enable(command);
	update_all_ops = false;
पूर्ण

पूर्णांक ftrace_startup(काष्ठा ftrace_ops *ops, पूर्णांक command)
अणु
	पूर्णांक ret;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	ret = __रेजिस्टर_ftrace_function(ops);
	अगर (ret)
		वापस ret;

	ftrace_start_up++;

	/*
	 * Note that ftrace probes uses this to start up
	 * and modअगरy functions it will probe. But we still
	 * set the ADDING flag क्रम modअगरication, as probes
	 * करो not have trampolines. If they add them in the
	 * future, then the probes will need to distinguish
	 * between adding and updating probes.
	 */
	ops->flags |= FTRACE_OPS_FL_ENABLED | FTRACE_OPS_FL_ADDING;

	ret = ftrace_hash_ipmodअगरy_enable(ops);
	अगर (ret < 0) अणु
		/* Rollback registration process */
		__unरेजिस्टर_ftrace_function(ops);
		ftrace_start_up--;
		ops->flags &= ~FTRACE_OPS_FL_ENABLED;
		अगर (ops->flags & FTRACE_OPS_FL_DYNAMIC)
			ftrace_trampoline_मुक्त(ops);
		वापस ret;
	पूर्ण

	अगर (ftrace_hash_rec_enable(ops, 1))
		command |= FTRACE_UPDATE_CALLS;

	ftrace_startup_enable(command);

	ops->flags &= ~FTRACE_OPS_FL_ADDING;

	वापस 0;
पूर्ण

पूर्णांक ftrace_shutकरोwn(काष्ठा ftrace_ops *ops, पूर्णांक command)
अणु
	पूर्णांक ret;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	ret = __unरेजिस्टर_ftrace_function(ops);
	अगर (ret)
		वापस ret;

	ftrace_start_up--;
	/*
	 * Just warn in हाल of unbalance, no need to समाप्त ftrace, it's not
	 * critical but the ftrace_call callers may be never nopped again after
	 * further ftrace uses.
	 */
	WARN_ON_ONCE(ftrace_start_up < 0);

	/* Disabling ipmodअगरy never fails */
	ftrace_hash_ipmodअगरy_disable(ops);

	अगर (ftrace_hash_rec_disable(ops, 1))
		command |= FTRACE_UPDATE_CALLS;

	ops->flags &= ~FTRACE_OPS_FL_ENABLED;

	अगर (saved_ftrace_func != ftrace_trace_function) अणु
		saved_ftrace_func = ftrace_trace_function;
		command |= FTRACE_UPDATE_TRACE_FUNC;
	पूर्ण

	अगर (!command || !ftrace_enabled) अणु
		/*
		 * If these are dynamic or per_cpu ops, they still
		 * need their data मुक्तd. Since, function tracing is
		 * not currently active, we can just मुक्त them
		 * without synchronizing all CPUs.
		 */
		अगर (ops->flags & FTRACE_OPS_FL_DYNAMIC)
			जाओ मुक्त_ops;

		वापस 0;
	पूर्ण

	/*
	 * If the ops uses a trampoline, then it needs to be
	 * tested first on update.
	 */
	ops->flags |= FTRACE_OPS_FL_REMOVING;
	हटाओd_ops = ops;

	/* The trampoline logic checks the old hashes */
	ops->old_hash.filter_hash = ops->func_hash->filter_hash;
	ops->old_hash.notrace_hash = ops->func_hash->notrace_hash;

	ftrace_run_update_code(command);

	/*
	 * If there's no more ops रेजिस्टरed with ftrace, run a
	 * sanity check to make sure all rec flags are cleared.
	 */
	अगर (rcu_dereference_रक्षित(ftrace_ops_list,
			lockdep_is_held(&ftrace_lock)) == &ftrace_list_end) अणु
		काष्ठा ftrace_page *pg;
		काष्ठा dyn_ftrace *rec;

		करो_क्रम_each_ftrace_rec(pg, rec) अणु
			अगर (FTRACE_WARN_ON_ONCE(rec->flags & ~FTRACE_FL_DISABLED))
				pr_warn("  %pS flags:%lx\n",
					(व्योम *)rec->ip, rec->flags);
		पूर्ण जबतक_क्रम_each_ftrace_rec();
	पूर्ण

	ops->old_hash.filter_hash = शून्य;
	ops->old_hash.notrace_hash = शून्य;

	हटाओd_ops = शून्य;
	ops->flags &= ~FTRACE_OPS_FL_REMOVING;

	/*
	 * Dynamic ops may be मुक्तd, we must make sure that all
	 * callers are करोne beक्रमe leaving this function.
	 * The same goes क्रम मुक्तing the per_cpu data of the per_cpu
	 * ops.
	 */
	अगर (ops->flags & FTRACE_OPS_FL_DYNAMIC) अणु
		/*
		 * We need to करो a hard क्रमce of sched synchronization.
		 * This is because we use preempt_disable() to करो RCU, but
		 * the function tracers can be called where RCU is not watching
		 * (like beक्रमe user_निकास()). We can not rely on the RCU
		 * infraकाष्ठाure to करो the synchronization, thus we must करो it
		 * ourselves.
		 */
		synchronize_rcu_tasks_rude();

		/*
		 * When the kernel is preemptive, tasks can be preempted
		 * जबतक on a ftrace trampoline. Just scheduling a task on
		 * a CPU is not good enough to flush them. Calling
		 * synchronize_rcu_tasks() will रुको क्रम those tasks to
		 * execute and either schedule voluntarily or enter user space.
		 */
		अगर (IS_ENABLED(CONFIG_PREEMPTION))
			synchronize_rcu_tasks();

 मुक्त_ops:
		ftrace_trampoline_मुक्त(ops);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ftrace_startup_sysctl(व्योम)
अणु
	पूर्णांक command;

	अगर (unlikely(ftrace_disabled))
		वापस;

	/* Force update next समय */
	saved_ftrace_func = शून्य;
	/* ftrace_start_up is true अगर we want ftrace running */
	अगर (ftrace_start_up) अणु
		command = FTRACE_UPDATE_CALLS;
		अगर (ftrace_graph_active)
			command |= FTRACE_START_FUNC_RET;
		ftrace_startup_enable(command);
	पूर्ण
पूर्ण

अटल व्योम ftrace_shutकरोwn_sysctl(व्योम)
अणु
	पूर्णांक command;

	अगर (unlikely(ftrace_disabled))
		वापस;

	/* ftrace_start_up is true अगर ftrace is running */
	अगर (ftrace_start_up) अणु
		command = FTRACE_DISABLE_CALLS;
		अगर (ftrace_graph_active)
			command |= FTRACE_STOP_FUNC_RET;
		ftrace_run_update_code(command);
	पूर्ण
पूर्ण

अटल u64		ftrace_update_समय;
अचिन्हित दीर्घ		ftrace_update_tot_cnt;
अचिन्हित दीर्घ		ftrace_number_of_pages;
अचिन्हित दीर्घ		ftrace_number_of_groups;

अटल अंतरभूत पूर्णांक ops_traces_mod(काष्ठा ftrace_ops *ops)
अणु
	/*
	 * Filter_hash being empty will शेष to trace module.
	 * But notrace hash requires a test of inभागidual module functions.
	 */
	वापस ftrace_hash_empty(ops->func_hash->filter_hash) &&
		ftrace_hash_empty(ops->func_hash->notrace_hash);
पूर्ण

/*
 * Check अगर the current ops references the record.
 *
 * If the ops traces all functions, then it was alपढ़ोy accounted क्रम.
 * If the ops करोes not trace the current record function, skip it.
 * If the ops ignores the function via notrace filter, skip it.
 */
अटल अंतरभूत bool
ops_references_rec(काष्ठा ftrace_ops *ops, काष्ठा dyn_ftrace *rec)
अणु
	/* If ops isn't enabled, ignore it */
	अगर (!(ops->flags & FTRACE_OPS_FL_ENABLED))
		वापस false;

	/* If ops traces all then it includes this function */
	अगर (ops_traces_mod(ops))
		वापस true;

	/* The function must be in the filter */
	अगर (!ftrace_hash_empty(ops->func_hash->filter_hash) &&
	    !__ftrace_lookup_ip(ops->func_hash->filter_hash, rec->ip))
		वापस false;

	/* If in notrace hash, we ignore it too */
	अगर (ftrace_lookup_ip(ops->func_hash->notrace_hash, rec->ip))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ftrace_update_code(काष्ठा module *mod, काष्ठा ftrace_page *new_pgs)
अणु
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *p;
	u64 start, stop;
	अचिन्हित दीर्घ update_cnt = 0;
	अचिन्हित दीर्घ rec_flags = 0;
	पूर्णांक i;

	start = ftrace_now(raw_smp_processor_id());

	/*
	 * When a module is loaded, this function is called to convert
	 * the calls to mcount in its text to nops, and also to create
	 * an entry in the ftrace data. Now, अगर ftrace is activated
	 * after this call, but beक्रमe the module sets its text to
	 * पढ़ो-only, the modअगरication of enabling ftrace can fail अगर
	 * the पढ़ो-only is करोne जबतक ftrace is converting the calls.
	 * To prevent this, the module's records are set as disabled
	 * and will be enabled after the call to set the module's text
	 * to पढ़ो-only.
	 */
	अगर (mod)
		rec_flags |= FTRACE_FL_DISABLED;

	क्रम (pg = new_pgs; pg; pg = pg->next) अणु

		क्रम (i = 0; i < pg->index; i++) अणु

			/* If something went wrong, bail without enabling anything */
			अगर (unlikely(ftrace_disabled))
				वापस -1;

			p = &pg->records[i];
			p->flags = rec_flags;

			/*
			 * Do the initial record conversion from mcount jump
			 * to the NOP inकाष्ठाions.
			 */
			अगर (!__is_defined(CC_USING_NOP_MCOUNT) &&
			    !ftrace_nop_initialize(mod, p))
				अवरोध;

			update_cnt++;
		पूर्ण
	पूर्ण

	stop = ftrace_now(raw_smp_processor_id());
	ftrace_update_समय = stop - start;
	ftrace_update_tot_cnt += update_cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_allocate_records(काष्ठा ftrace_page *pg, पूर्णांक count)
अणु
	पूर्णांक order;
	पूर्णांक pages;
	पूर्णांक cnt;

	अगर (WARN_ON(!count))
		वापस -EINVAL;

	/* We want to fill as much as possible, with no empty pages */
	pages = DIV_ROUND_UP(count, ENTRIES_PER_PAGE);
	order = fls(pages) - 1;

 again:
	pg->records = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);

	अगर (!pg->records) अणु
		/* अगर we can't allocate this size, try something smaller */
		अगर (!order)
			वापस -ENOMEM;
		order >>= 1;
		जाओ again;
	पूर्ण

	ftrace_number_of_pages += 1 << order;
	ftrace_number_of_groups++;

	cnt = (PAGE_SIZE << order) / ENTRY_SIZE;
	pg->order = order;

	अगर (cnt > count)
		cnt = count;

	वापस cnt;
पूर्ण

अटल काष्ठा ftrace_page *
ftrace_allocate_pages(अचिन्हित दीर्घ num_to_init)
अणु
	काष्ठा ftrace_page *start_pg;
	काष्ठा ftrace_page *pg;
	पूर्णांक cnt;

	अगर (!num_to_init)
		वापस शून्य;

	start_pg = pg = kzalloc(माप(*pg), GFP_KERNEL);
	अगर (!pg)
		वापस शून्य;

	/*
	 * Try to allocate as much as possible in one जारीs
	 * location that fills in all of the space. We want to
	 * waste as little space as possible.
	 */
	क्रम (;;) अणु
		cnt = ftrace_allocate_records(pg, num_to_init);
		अगर (cnt < 0)
			जाओ मुक्त_pages;

		num_to_init -= cnt;
		अगर (!num_to_init)
			अवरोध;

		pg->next = kzalloc(माप(*pg), GFP_KERNEL);
		अगर (!pg->next)
			जाओ मुक्त_pages;

		pg = pg->next;
	पूर्ण

	वापस start_pg;

 मुक्त_pages:
	pg = start_pg;
	जबतक (pg) अणु
		अगर (pg->records) अणु
			मुक्त_pages((अचिन्हित दीर्घ)pg->records, pg->order);
			ftrace_number_of_pages -= 1 << pg->order;
		पूर्ण
		start_pg = pg->next;
		kमुक्त(pg);
		pg = start_pg;
		ftrace_number_of_groups--;
	पूर्ण
	pr_info("ftrace: FAILED to allocate memory for functions\n");
	वापस शून्य;
पूर्ण

#घोषणा FTRACE_BUFF_MAX (KSYM_SYMBOL_LEN+4) /* room क्रम wildcards */

काष्ठा ftrace_iterator अणु
	loff_t				pos;
	loff_t				func_pos;
	loff_t				mod_pos;
	काष्ठा ftrace_page		*pg;
	काष्ठा dyn_ftrace		*func;
	काष्ठा ftrace_func_probe	*probe;
	काष्ठा ftrace_func_entry	*probe_entry;
	काष्ठा trace_parser		parser;
	काष्ठा ftrace_hash		*hash;
	काष्ठा ftrace_ops		*ops;
	काष्ठा trace_array		*tr;
	काष्ठा list_head		*mod_list;
	पूर्णांक				pidx;
	पूर्णांक				idx;
	अचिन्हित			flags;
पूर्ण;

अटल व्योम *
t_probe_next(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	काष्ठा trace_array *tr = iter->ops->निजी;
	काष्ठा list_head *func_probes;
	काष्ठा ftrace_hash *hash;
	काष्ठा list_head *next;
	काष्ठा hlist_node *hnd = शून्य;
	काष्ठा hlist_head *hhd;
	पूर्णांक size;

	(*pos)++;
	iter->pos = *pos;

	अगर (!tr)
		वापस शून्य;

	func_probes = &tr->func_probes;
	अगर (list_empty(func_probes))
		वापस शून्य;

	अगर (!iter->probe) अणु
		next = func_probes->next;
		iter->probe = list_entry(next, काष्ठा ftrace_func_probe, list);
	पूर्ण

	अगर (iter->probe_entry)
		hnd = &iter->probe_entry->hlist;

	hash = iter->probe->ops.func_hash->filter_hash;

	/*
	 * A probe being रेजिस्टरed may temporarily have an empty hash
	 * and it's at the end of the func_probes list.
	 */
	अगर (!hash || hash == EMPTY_HASH)
		वापस शून्य;

	size = 1 << hash->size_bits;

 retry:
	अगर (iter->pidx >= size) अणु
		अगर (iter->probe->list.next == func_probes)
			वापस शून्य;
		next = iter->probe->list.next;
		iter->probe = list_entry(next, काष्ठा ftrace_func_probe, list);
		hash = iter->probe->ops.func_hash->filter_hash;
		size = 1 << hash->size_bits;
		iter->pidx = 0;
	पूर्ण

	hhd = &hash->buckets[iter->pidx];

	अगर (hlist_empty(hhd)) अणु
		iter->pidx++;
		hnd = शून्य;
		जाओ retry;
	पूर्ण

	अगर (!hnd)
		hnd = hhd->first;
	अन्यथा अणु
		hnd = hnd->next;
		अगर (!hnd) अणु
			iter->pidx++;
			जाओ retry;
		पूर्ण
	पूर्ण

	अगर (WARN_ON_ONCE(!hnd))
		वापस शून्य;

	iter->probe_entry = hlist_entry(hnd, काष्ठा ftrace_func_entry, hlist);

	वापस iter;
पूर्ण

अटल व्योम *t_probe_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	व्योम *p = शून्य;
	loff_t l;

	अगर (!(iter->flags & FTRACE_ITER_DO_PROBES))
		वापस शून्य;

	अगर (iter->mod_pos > *pos)
		वापस शून्य;

	iter->probe = शून्य;
	iter->probe_entry = शून्य;
	iter->pidx = 0;
	क्रम (l = 0; l <= (*pos - iter->mod_pos); ) अणु
		p = t_probe_next(m, &l);
		अगर (!p)
			अवरोध;
	पूर्ण
	अगर (!p)
		वापस शून्य;

	/* Only set this अगर we have an item */
	iter->flags |= FTRACE_ITER_PROBE;

	वापस iter;
पूर्ण

अटल पूर्णांक
t_probe_show(काष्ठा seq_file *m, काष्ठा ftrace_iterator *iter)
अणु
	काष्ठा ftrace_func_entry *probe_entry;
	काष्ठा ftrace_probe_ops *probe_ops;
	काष्ठा ftrace_func_probe *probe;

	probe = iter->probe;
	probe_entry = iter->probe_entry;

	अगर (WARN_ON_ONCE(!probe || !probe_entry))
		वापस -EIO;

	probe_ops = probe->probe_ops;

	अगर (probe_ops->prपूर्णांक)
		वापस probe_ops->prपूर्णांक(m, probe_entry->ip, probe_ops, probe->data);

	seq_म_लिखो(m, "%ps:%ps\n", (व्योम *)probe_entry->ip,
		   (व्योम *)probe_ops->func);

	वापस 0;
पूर्ण

अटल व्योम *
t_mod_next(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	काष्ठा trace_array *tr = iter->tr;

	(*pos)++;
	iter->pos = *pos;

	iter->mod_list = iter->mod_list->next;

	अगर (iter->mod_list == &tr->mod_trace ||
	    iter->mod_list == &tr->mod_notrace) अणु
		iter->flags &= ~FTRACE_ITER_MOD;
		वापस शून्य;
	पूर्ण

	iter->mod_pos = *pos;

	वापस iter;
पूर्ण

अटल व्योम *t_mod_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	व्योम *p = शून्य;
	loff_t l;

	अगर (iter->func_pos > *pos)
		वापस शून्य;

	iter->mod_pos = iter->func_pos;

	/* probes are only available अगर tr is set */
	अगर (!iter->tr)
		वापस शून्य;

	क्रम (l = 0; l <= (*pos - iter->func_pos); ) अणु
		p = t_mod_next(m, &l);
		अगर (!p)
			अवरोध;
	पूर्ण
	अगर (!p) अणु
		iter->flags &= ~FTRACE_ITER_MOD;
		वापस t_probe_start(m, pos);
	पूर्ण

	/* Only set this अगर we have an item */
	iter->flags |= FTRACE_ITER_MOD;

	वापस iter;
पूर्ण

अटल पूर्णांक
t_mod_show(काष्ठा seq_file *m, काष्ठा ftrace_iterator *iter)
अणु
	काष्ठा ftrace_mod_load *ftrace_mod;
	काष्ठा trace_array *tr = iter->tr;

	अगर (WARN_ON_ONCE(!iter->mod_list) ||
			 iter->mod_list == &tr->mod_trace ||
			 iter->mod_list == &tr->mod_notrace)
		वापस -EIO;

	ftrace_mod = list_entry(iter->mod_list, काष्ठा ftrace_mod_load, list);

	अगर (ftrace_mod->func)
		seq_म_लिखो(m, "%s", ftrace_mod->func);
	अन्यथा
		seq_अ_दो(m, '*');

	seq_म_लिखो(m, ":mod:%s\n", ftrace_mod->module);

	वापस 0;
पूर्ण

अटल व्योम *
t_func_next(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	काष्ठा dyn_ftrace *rec = शून्य;

	(*pos)++;

 retry:
	अगर (iter->idx >= iter->pg->index) अणु
		अगर (iter->pg->next) अणु
			iter->pg = iter->pg->next;
			iter->idx = 0;
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		rec = &iter->pg->records[iter->idx++];
		अगर (((iter->flags & (FTRACE_ITER_FILTER | FTRACE_ITER_NOTRACE)) &&
		     !ftrace_lookup_ip(iter->hash, rec->ip)) ||

		    ((iter->flags & FTRACE_ITER_ENABLED) &&
		     !(rec->flags & FTRACE_FL_ENABLED))) अणु

			rec = शून्य;
			जाओ retry;
		पूर्ण
	पूर्ण

	अगर (!rec)
		वापस शून्य;

	iter->pos = iter->func_pos = *pos;
	iter->func = rec;

	वापस iter;
पूर्ण

अटल व्योम *
t_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	loff_t l = *pos; /* t_probe_start() must use original pos */
	व्योम *ret;

	अगर (unlikely(ftrace_disabled))
		वापस शून्य;

	अगर (iter->flags & FTRACE_ITER_PROBE)
		वापस t_probe_next(m, pos);

	अगर (iter->flags & FTRACE_ITER_MOD)
		वापस t_mod_next(m, pos);

	अगर (iter->flags & FTRACE_ITER_PRINTALL) अणु
		/* next must increment pos, and t_probe_start करोes not */
		(*pos)++;
		वापस t_mod_start(m, &l);
	पूर्ण

	ret = t_func_next(m, pos);

	अगर (!ret)
		वापस t_mod_start(m, &l);

	वापस ret;
पूर्ण

अटल व्योम reset_iter_पढ़ो(काष्ठा ftrace_iterator *iter)
अणु
	iter->pos = 0;
	iter->func_pos = 0;
	iter->flags &= ~(FTRACE_ITER_PRINTALL | FTRACE_ITER_PROBE | FTRACE_ITER_MOD);
पूर्ण

अटल व्योम *t_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	व्योम *p = शून्य;
	loff_t l;

	mutex_lock(&ftrace_lock);

	अगर (unlikely(ftrace_disabled))
		वापस शून्य;

	/*
	 * If an lseek was करोne, then reset and start from beginning.
	 */
	अगर (*pos < iter->pos)
		reset_iter_पढ़ो(iter);

	/*
	 * For set_ftrace_filter पढ़ोing, अगर we have the filter
	 * off, we can लघु cut and just prपूर्णांक out that all
	 * functions are enabled.
	 */
	अगर ((iter->flags & (FTRACE_ITER_FILTER | FTRACE_ITER_NOTRACE)) &&
	    ftrace_hash_empty(iter->hash)) अणु
		iter->func_pos = 1; /* Account क्रम the message */
		अगर (*pos > 0)
			वापस t_mod_start(m, pos);
		iter->flags |= FTRACE_ITER_PRINTALL;
		/* reset in हाल of seek/pपढ़ो */
		iter->flags &= ~FTRACE_ITER_PROBE;
		वापस iter;
	पूर्ण

	अगर (iter->flags & FTRACE_ITER_MOD)
		वापस t_mod_start(m, pos);

	/*
	 * Unक्रमtunately, we need to restart at ftrace_pages_start
	 * every समय we let go of the ftrace_mutex. This is because
	 * those poपूर्णांकers can change without the lock.
	 */
	iter->pg = ftrace_pages_start;
	iter->idx = 0;
	क्रम (l = 0; l <= *pos; ) अणु
		p = t_func_next(m, &l);
		अगर (!p)
			अवरोध;
	पूर्ण

	अगर (!p)
		वापस t_mod_start(m, pos);

	वापस iter;
पूर्ण

अटल व्योम t_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&ftrace_lock);
पूर्ण

व्योम * __weak
arch_ftrace_trampoline_func(काष्ठा ftrace_ops *ops, काष्ठा dyn_ftrace *rec)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम add_trampoline_func(काष्ठा seq_file *m, काष्ठा ftrace_ops *ops,
				काष्ठा dyn_ftrace *rec)
अणु
	व्योम *ptr;

	ptr = arch_ftrace_trampoline_func(ops, rec);
	अगर (ptr)
		seq_म_लिखो(m, " ->%pS", ptr);
पूर्ण

अटल पूर्णांक t_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ftrace_iterator *iter = m->निजी;
	काष्ठा dyn_ftrace *rec;

	अगर (iter->flags & FTRACE_ITER_PROBE)
		वापस t_probe_show(m, iter);

	अगर (iter->flags & FTRACE_ITER_MOD)
		वापस t_mod_show(m, iter);

	अगर (iter->flags & FTRACE_ITER_PRINTALL) अणु
		अगर (iter->flags & FTRACE_ITER_NOTRACE)
			seq_माला_दो(m, "#### no functions disabled ####\n");
		अन्यथा
			seq_माला_दो(m, "#### all functions enabled ####\n");
		वापस 0;
	पूर्ण

	rec = iter->func;

	अगर (!rec)
		वापस 0;

	seq_म_लिखो(m, "%ps", (व्योम *)rec->ip);
	अगर (iter->flags & FTRACE_ITER_ENABLED) अणु
		काष्ठा ftrace_ops *ops;

		seq_म_लिखो(m, " (%ld)%s%s%s",
			   ftrace_rec_count(rec),
			   rec->flags & FTRACE_FL_REGS ? " R" : "  ",
			   rec->flags & FTRACE_FL_IPMODIFY ? " I" : "  ",
			   rec->flags & FTRACE_FL_सूचीECT ? " D" : "  ");
		अगर (rec->flags & FTRACE_FL_TRAMP_EN) अणु
			ops = ftrace_find_tramp_ops_any(rec);
			अगर (ops) अणु
				करो अणु
					seq_म_लिखो(m, "\ttramp: %pS (%pS)",
						   (व्योम *)ops->trampoline,
						   (व्योम *)ops->func);
					add_trampoline_func(m, ops, rec);
					ops = ftrace_find_tramp_ops_next(rec, ops);
				पूर्ण जबतक (ops);
			पूर्ण अन्यथा
				seq_माला_दो(m, "\ttramp: ERROR!");
		पूर्ण अन्यथा अणु
			add_trampoline_func(m, शून्य, rec);
		पूर्ण
		अगर (rec->flags & FTRACE_FL_सूचीECT) अणु
			अचिन्हित दीर्घ direct;

			direct = ftrace_find_rec_direct(rec->ip);
			अगर (direct)
				seq_म_लिखो(m, "\n\tdirect-->%pS", (व्योम *)direct);
		पूर्ण
	पूर्ण

	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations show_ftrace_seq_ops = अणु
	.start = t_start,
	.next = t_next,
	.stop = t_stop,
	.show = t_show,
पूर्ण;

अटल पूर्णांक
ftrace_avail_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_iterator *iter;
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	iter = __seq_खोलो_निजी(file, &show_ftrace_seq_ops, माप(*iter));
	अगर (!iter)
		वापस -ENOMEM;

	iter->pg = ftrace_pages_start;
	iter->ops = &global_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक
ftrace_enabled_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_iterator *iter;

	/*
	 * This shows us what functions are currently being
	 * traced and by what. Not sure अगर we want lockकरोwn
	 * to hide such critical inक्रमmation क्रम an admin.
	 * Although, perhaps it can show inक्रमmation we करोn't
	 * want people to see, but अगर something is tracing
	 * something, we probably want to know about it.
	 */

	iter = __seq_खोलो_निजी(file, &show_ftrace_seq_ops, माप(*iter));
	अगर (!iter)
		वापस -ENOMEM;

	iter->pg = ftrace_pages_start;
	iter->flags = FTRACE_ITER_ENABLED;
	iter->ops = &global_ops;

	वापस 0;
पूर्ण

/**
 * ftrace_regex_खोलो - initialize function tracer filter files
 * @ops: The ftrace_ops that hold the hash filters
 * @flag: The type of filter to process
 * @inode: The inode, usually passed in to your खोलो routine
 * @file: The file, usually passed in to your खोलो routine
 *
 * ftrace_regex_खोलो() initializes the filter files क्रम the
 * @ops. Depending on @flag it may process the filter hash or
 * the notrace hash of @ops. With this called from the खोलो
 * routine, you can use ftrace_filter_ग_लिखो() क्रम the ग_लिखो
 * routine अगर @flag has FTRACE_ITER_FILTER set, or
 * ftrace_notrace_ग_लिखो() अगर @flag has FTRACE_ITER_NOTRACE set.
 * tracing_lseek() should be used as the lseek routine, and
 * release must call ftrace_regex_release().
 */
पूर्णांक
ftrace_regex_खोलो(काष्ठा ftrace_ops *ops, पूर्णांक flag,
		  काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_iterator *iter;
	काष्ठा ftrace_hash *hash;
	काष्ठा list_head *mod_head;
	काष्ठा trace_array *tr = ops->निजी;
	पूर्णांक ret = -ENOMEM;

	ftrace_ops_init(ops);

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	अगर (tracing_check_खोलो_get_tr(tr))
		वापस -ENODEV;

	iter = kzalloc(माप(*iter), GFP_KERNEL);
	अगर (!iter)
		जाओ out;

	अगर (trace_parser_get_init(&iter->parser, FTRACE_BUFF_MAX))
		जाओ out;

	iter->ops = ops;
	iter->flags = flag;
	iter->tr = tr;

	mutex_lock(&ops->func_hash->regex_lock);

	अगर (flag & FTRACE_ITER_NOTRACE) अणु
		hash = ops->func_hash->notrace_hash;
		mod_head = tr ? &tr->mod_notrace : शून्य;
	पूर्ण अन्यथा अणु
		hash = ops->func_hash->filter_hash;
		mod_head = tr ? &tr->mod_trace : शून्य;
	पूर्ण

	iter->mod_list = mod_head;

	अगर (file->f_mode & FMODE_WRITE) अणु
		स्थिर पूर्णांक size_bits = FTRACE_HASH_DEFAULT_BITS;

		अगर (file->f_flags & O_TRUNC) अणु
			iter->hash = alloc_ftrace_hash(size_bits);
			clear_ftrace_mod_list(mod_head);
	        पूर्ण अन्यथा अणु
			iter->hash = alloc_and_copy_ftrace_hash(size_bits, hash);
		पूर्ण

		अगर (!iter->hash) अणु
			trace_parser_put(&iter->parser);
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा
		iter->hash = hash;

	ret = 0;

	अगर (file->f_mode & FMODE_READ) अणु
		iter->pg = ftrace_pages_start;

		ret = seq_खोलो(file, &show_ftrace_seq_ops);
		अगर (!ret) अणु
			काष्ठा seq_file *m = file->निजी_data;
			m->निजी = iter;
		पूर्ण अन्यथा अणु
			/* Failed */
			मुक्त_ftrace_hash(iter->hash);
			trace_parser_put(&iter->parser);
		पूर्ण
	पूर्ण अन्यथा
		file->निजी_data = iter;

 out_unlock:
	mutex_unlock(&ops->func_hash->regex_lock);

 out:
	अगर (ret) अणु
		kमुक्त(iter);
		अगर (tr)
			trace_array_put(tr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_filter_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_ops *ops = inode->i_निजी;

	/* Checks क्रम tracefs lockकरोwn */
	वापस ftrace_regex_खोलो(ops,
			FTRACE_ITER_FILTER | FTRACE_ITER_DO_PROBES,
			inode, file);
पूर्ण

अटल पूर्णांक
ftrace_notrace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_ops *ops = inode->i_निजी;

	/* Checks क्रम tracefs lockकरोwn */
	वापस ftrace_regex_खोलो(ops, FTRACE_ITER_NOTRACE,
				 inode, file);
पूर्ण

/* Type क्रम quick search ftrace basic regexes (globs) from filter_parse_regex */
काष्ठा ftrace_glob अणु
	अक्षर *search;
	अचिन्हित len;
	पूर्णांक type;
पूर्ण;

/*
 * If symbols in an architecture करोn't correspond exactly to the user-visible
 * name of what they represent, it is possible to define this function to
 * perक्रमm the necessary adjusपंचांगents.
*/
अक्षर * __weak arch_ftrace_match_adjust(अक्षर *str, स्थिर अक्षर *search)
अणु
	वापस str;
पूर्ण

अटल पूर्णांक ftrace_match(अक्षर *str, काष्ठा ftrace_glob *g)
अणु
	पूर्णांक matched = 0;
	पूर्णांक slen;

	str = arch_ftrace_match_adjust(str, g->search);

	चयन (g->type) अणु
	हाल MATCH_FULL:
		अगर (म_भेद(str, g->search) == 0)
			matched = 1;
		अवरोध;
	हाल MATCH_FRONT_ONLY:
		अगर (म_भेदन(str, g->search, g->len) == 0)
			matched = 1;
		अवरोध;
	हाल MATCH_MIDDLE_ONLY:
		अगर (म_माला(str, g->search))
			matched = 1;
		अवरोध;
	हाल MATCH_END_ONLY:
		slen = म_माप(str);
		अगर (slen >= g->len &&
		    स_भेद(str + slen - g->len, g->search, g->len) == 0)
			matched = 1;
		अवरोध;
	हाल MATCH_GLOB:
		अगर (glob_match(g->search, str))
			matched = 1;
		अवरोध;
	पूर्ण

	वापस matched;
पूर्ण

अटल पूर्णांक
enter_record(काष्ठा ftrace_hash *hash, काष्ठा dyn_ftrace *rec, पूर्णांक clear_filter)
अणु
	काष्ठा ftrace_func_entry *entry;
	पूर्णांक ret = 0;

	entry = ftrace_lookup_ip(hash, rec->ip);
	अगर (clear_filter) अणु
		/* Do nothing अगर it करोesn't exist */
		अगर (!entry)
			वापस 0;

		मुक्त_hash_entry(hash, entry);
	पूर्ण अन्यथा अणु
		/* Do nothing अगर it exists */
		अगर (entry)
			वापस 0;

		ret = add_hash_entry(hash, rec->ip);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
add_rec_by_index(काष्ठा ftrace_hash *hash, काष्ठा ftrace_glob *func_g,
		 पूर्णांक clear_filter)
अणु
	दीर्घ index = simple_म_से_अदीर्घ(func_g->search, शून्य, 0);
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec;

	/* The index starts at 1 */
	अगर (--index < 0)
		वापस 0;

	करो_क्रम_each_ftrace_rec(pg, rec) अणु
		अगर (pg->index <= index) अणु
			index -= pg->index;
			/* this is a द्विगुन loop, अवरोध goes to the next page */
			अवरोध;
		पूर्ण
		rec = &pg->records[index];
		enter_record(hash, rec, clear_filter);
		वापस 1;
	पूर्ण जबतक_क्रम_each_ftrace_rec();
	वापस 0;
पूर्ण

अटल पूर्णांक
ftrace_match_record(काष्ठा dyn_ftrace *rec, काष्ठा ftrace_glob *func_g,
		काष्ठा ftrace_glob *mod_g, पूर्णांक exclude_mod)
अणु
	अक्षर str[KSYM_SYMBOL_LEN];
	अक्षर *modname;

	kallsyms_lookup(rec->ip, शून्य, शून्य, &modname, str);

	अगर (mod_g) अणु
		पूर्णांक mod_matches = (modname) ? ftrace_match(modname, mod_g) : 0;

		/* blank module name to match all modules */
		अगर (!mod_g->len) अणु
			/* blank module globbing: modname xor exclude_mod */
			अगर (!exclude_mod != !modname)
				जाओ func_match;
			वापस 0;
		पूर्ण

		/*
		 * exclude_mod is set to trace everything but the given
		 * module. If it is set and the module matches, then
		 * वापस 0. If it is not set, and the module करोesn't match
		 * also वापस 0. Otherwise, check the function to see अगर
		 * that matches.
		 */
		अगर (!mod_matches == !exclude_mod)
			वापस 0;
func_match:
		/* blank search means to match all funcs in the mod */
		अगर (!func_g->len)
			वापस 1;
	पूर्ण

	वापस ftrace_match(str, func_g);
पूर्ण

अटल पूर्णांक
match_records(काष्ठा ftrace_hash *hash, अक्षर *func, पूर्णांक len, अक्षर *mod)
अणु
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec;
	काष्ठा ftrace_glob func_g = अणु .type = MATCH_FULL पूर्ण;
	काष्ठा ftrace_glob mod_g = अणु .type = MATCH_FULL पूर्ण;
	काष्ठा ftrace_glob *mod_match = (mod) ? &mod_g : शून्य;
	पूर्णांक exclude_mod = 0;
	पूर्णांक found = 0;
	पूर्णांक ret;
	पूर्णांक clear_filter = 0;

	अगर (func) अणु
		func_g.type = filter_parse_regex(func, len, &func_g.search,
						 &clear_filter);
		func_g.len = म_माप(func_g.search);
	पूर्ण

	अगर (mod) अणु
		mod_g.type = filter_parse_regex(mod, म_माप(mod),
				&mod_g.search, &exclude_mod);
		mod_g.len = म_माप(mod_g.search);
	पूर्ण

	mutex_lock(&ftrace_lock);

	अगर (unlikely(ftrace_disabled))
		जाओ out_unlock;

	अगर (func_g.type == MATCH_INDEX) अणु
		found = add_rec_by_index(hash, &func_g, clear_filter);
		जाओ out_unlock;
	पूर्ण

	करो_क्रम_each_ftrace_rec(pg, rec) अणु

		अगर (rec->flags & FTRACE_FL_DISABLED)
			जारी;

		अगर (ftrace_match_record(rec, &func_g, mod_match, exclude_mod)) अणु
			ret = enter_record(hash, rec, clear_filter);
			अगर (ret < 0) अणु
				found = ret;
				जाओ out_unlock;
			पूर्ण
			found = 1;
		पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_rec();
 out_unlock:
	mutex_unlock(&ftrace_lock);

	वापस found;
पूर्ण

अटल पूर्णांक
ftrace_match_records(काष्ठा ftrace_hash *hash, अक्षर *buff, पूर्णांक len)
अणु
	वापस match_records(hash, buff, len, शून्य);
पूर्ण

अटल व्योम ftrace_ops_update_code(काष्ठा ftrace_ops *ops,
				   काष्ठा ftrace_ops_hash *old_hash)
अणु
	काष्ठा ftrace_ops *op;

	अगर (!ftrace_enabled)
		वापस;

	अगर (ops->flags & FTRACE_OPS_FL_ENABLED) अणु
		ftrace_run_modअगरy_code(ops, FTRACE_UPDATE_CALLS, old_hash);
		वापस;
	पूर्ण

	/*
	 * If this is the shared global_ops filter, then we need to
	 * check अगर there is another ops that shares it, is enabled.
	 * If so, we still need to run the modअगरy code.
	 */
	अगर (ops->func_hash != &global_ops.local_hash)
		वापस;

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		अगर (op->func_hash == &global_ops.local_hash &&
		    op->flags & FTRACE_OPS_FL_ENABLED) अणु
			ftrace_run_modअगरy_code(op, FTRACE_UPDATE_CALLS, old_hash);
			/* Only need to करो this once */
			वापस;
		पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_op(op);
पूर्ण

अटल पूर्णांक ftrace_hash_move_and_update_ops(काष्ठा ftrace_ops *ops,
					   काष्ठा ftrace_hash **orig_hash,
					   काष्ठा ftrace_hash *hash,
					   पूर्णांक enable)
अणु
	काष्ठा ftrace_ops_hash old_hash_ops;
	काष्ठा ftrace_hash *old_hash;
	पूर्णांक ret;

	old_hash = *orig_hash;
	old_hash_ops.filter_hash = ops->func_hash->filter_hash;
	old_hash_ops.notrace_hash = ops->func_hash->notrace_hash;
	ret = ftrace_hash_move(ops, enable, orig_hash, hash);
	अगर (!ret) अणु
		ftrace_ops_update_code(ops, &old_hash_ops);
		मुक्त_ftrace_hash_rcu(old_hash);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool module_exists(स्थिर अक्षर *module)
अणु
	/* All modules have the symbol __this_module */
	अटल स्थिर अक्षर this_mod[] = "__this_module";
	अक्षर modname[MAX_PARAM_PREFIX_LEN + माप(this_mod) + 2];
	अचिन्हित दीर्घ val;
	पूर्णांक n;

	n = snम_लिखो(modname, माप(modname), "%s:%s", module, this_mod);

	अगर (n > माप(modname) - 1)
		वापस false;

	val = module_kallsyms_lookup_name(modname);
	वापस val != 0;
पूर्ण

अटल पूर्णांक cache_mod(काष्ठा trace_array *tr,
		     स्थिर अक्षर *func, अक्षर *module, पूर्णांक enable)
अणु
	काष्ठा ftrace_mod_load *ftrace_mod, *n;
	काष्ठा list_head *head = enable ? &tr->mod_trace : &tr->mod_notrace;
	पूर्णांक ret;

	mutex_lock(&ftrace_lock);

	/* We करो not cache inverse filters */
	अगर (func[0] == '!') अणु
		func++;
		ret = -EINVAL;

		/* Look to हटाओ this hash */
		list_क्रम_each_entry_safe(ftrace_mod, n, head, list) अणु
			अगर (म_भेद(ftrace_mod->module, module) != 0)
				जारी;

			/* no func matches all */
			अगर (म_भेद(func, "*") == 0 ||
			    (ftrace_mod->func &&
			     म_भेद(ftrace_mod->func, func) == 0)) अणु
				ret = 0;
				मुक्त_ftrace_mod(ftrace_mod);
				जारी;
			पूर्ण
		पूर्ण
		जाओ out;
	पूर्ण

	ret = -EINVAL;
	/* We only care about modules that have not been loaded yet */
	अगर (module_exists(module))
		जाओ out;

	/* Save this string off, and execute it when the module is loaded */
	ret = ftrace_add_mod(tr, func, module, enable);
 out:
	mutex_unlock(&ftrace_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_set_regex(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf, पूर्णांक len,
		 पूर्णांक reset, पूर्णांक enable);

#अगर_घोषित CONFIG_MODULES
अटल व्योम process_mod_list(काष्ठा list_head *head, काष्ठा ftrace_ops *ops,
			     अक्षर *mod, bool enable)
अणु
	काष्ठा ftrace_mod_load *ftrace_mod, *n;
	काष्ठा ftrace_hash **orig_hash, *new_hash;
	LIST_HEAD(process_mods);
	अक्षर *func;

	mutex_lock(&ops->func_hash->regex_lock);

	अगर (enable)
		orig_hash = &ops->func_hash->filter_hash;
	अन्यथा
		orig_hash = &ops->func_hash->notrace_hash;

	new_hash = alloc_and_copy_ftrace_hash(FTRACE_HASH_DEFAULT_BITS,
					      *orig_hash);
	अगर (!new_hash)
		जाओ out; /* warn? */

	mutex_lock(&ftrace_lock);

	list_क्रम_each_entry_safe(ftrace_mod, n, head, list) अणु

		अगर (म_भेद(ftrace_mod->module, mod) != 0)
			जारी;

		अगर (ftrace_mod->func)
			func = kstrdup(ftrace_mod->func, GFP_KERNEL);
		अन्यथा
			func = kstrdup("*", GFP_KERNEL);

		अगर (!func) /* warn? */
			जारी;

		list_del(&ftrace_mod->list);
		list_add(&ftrace_mod->list, &process_mods);

		/* Use the newly allocated func, as it may be "*" */
		kमुक्त(ftrace_mod->func);
		ftrace_mod->func = func;
	पूर्ण

	mutex_unlock(&ftrace_lock);

	list_क्रम_each_entry_safe(ftrace_mod, n, &process_mods, list) अणु

		func = ftrace_mod->func;

		/* Grअसल ftrace_lock, which is why we have this extra step */
		match_records(new_hash, func, म_माप(func), mod);
		मुक्त_ftrace_mod(ftrace_mod);
	पूर्ण

	अगर (enable && list_empty(head))
		new_hash->flags &= ~FTRACE_HASH_FL_MOD;

	mutex_lock(&ftrace_lock);

	ftrace_hash_move_and_update_ops(ops, orig_hash,
					      new_hash, enable);
	mutex_unlock(&ftrace_lock);

 out:
	mutex_unlock(&ops->func_hash->regex_lock);

	मुक्त_ftrace_hash(new_hash);
पूर्ण

अटल व्योम process_cached_mods(स्थिर अक्षर *mod_name)
अणु
	काष्ठा trace_array *tr;
	अक्षर *mod;

	mod = kstrdup(mod_name, GFP_KERNEL);
	अगर (!mod)
		वापस;

	mutex_lock(&trace_types_lock);
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (!list_empty(&tr->mod_trace))
			process_mod_list(&tr->mod_trace, tr->ops, mod, true);
		अगर (!list_empty(&tr->mod_notrace))
			process_mod_list(&tr->mod_notrace, tr->ops, mod, false);
	पूर्ण
	mutex_unlock(&trace_types_lock);

	kमुक्त(mod);
पूर्ण
#पूर्ण_अगर

/*
 * We रेजिस्टर the module command as a ढाँचा to show others how
 * to रेजिस्टर the a command as well.
 */

अटल पूर्णांक
ftrace_mod_callback(काष्ठा trace_array *tr, काष्ठा ftrace_hash *hash,
		    अक्षर *func_orig, अक्षर *cmd, अक्षर *module, पूर्णांक enable)
अणु
	अक्षर *func;
	पूर्णांक ret;

	/* match_records() modअगरies func, and we need the original */
	func = kstrdup(func_orig, GFP_KERNEL);
	अगर (!func)
		वापस -ENOMEM;

	/*
	 * cmd == 'mod' because we only रेजिस्टरed this func
	 * क्रम the 'mod' ftrace_func_command.
	 * But अगर you रेजिस्टर one func with multiple commands,
	 * you can tell which command was used by the cmd
	 * parameter.
	 */
	ret = match_records(hash, func, म_माप(func), module);
	kमुक्त(func);

	अगर (!ret)
		वापस cache_mod(tr, func_orig, module, enable);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल काष्ठा ftrace_func_command ftrace_mod_cmd = अणु
	.name			= "mod",
	.func			= ftrace_mod_callback,
पूर्ण;

अटल पूर्णांक __init ftrace_mod_cmd_init(व्योम)
अणु
	वापस रेजिस्टर_ftrace_command(&ftrace_mod_cmd);
पूर्ण
core_initcall(ftrace_mod_cmd_init);

अटल व्योम function_trace_probe_call(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				      काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा ftrace_probe_ops *probe_ops;
	काष्ठा ftrace_func_probe *probe;

	probe = container_of(op, काष्ठा ftrace_func_probe, ops);
	probe_ops = probe->probe_ops;

	/*
	 * Disable preemption क्रम these calls to prevent a RCU grace
	 * period. This syncs the hash iteration and मुक्तing of items
	 * on the hash. rcu_पढ़ो_lock is too dangerous here.
	 */
	preempt_disable_notrace();
	probe_ops->func(ip, parent_ip, probe->tr, probe_ops, probe->data);
	preempt_enable_notrace();
पूर्ण

काष्ठा ftrace_func_map अणु
	काष्ठा ftrace_func_entry	entry;
	व्योम				*data;
पूर्ण;

काष्ठा ftrace_func_mapper अणु
	काष्ठा ftrace_hash		hash;
पूर्ण;

/**
 * allocate_ftrace_func_mapper - allocate a new ftrace_func_mapper
 *
 * Returns a ftrace_func_mapper descriptor that can be used to map ips to data.
 */
काष्ठा ftrace_func_mapper *allocate_ftrace_func_mapper(व्योम)
अणु
	काष्ठा ftrace_hash *hash;

	/*
	 * The mapper is simply a ftrace_hash, but since the entries
	 * in the hash are not ftrace_func_entry type, we define it
	 * as a separate काष्ठाure.
	 */
	hash = alloc_ftrace_hash(FTRACE_HASH_DEFAULT_BITS);
	वापस (काष्ठा ftrace_func_mapper *)hash;
पूर्ण

/**
 * ftrace_func_mapper_find_ip - Find some data mapped to an ip
 * @mapper: The mapper that has the ip maps
 * @ip: the inकाष्ठाion poपूर्णांकer to find the data क्रम
 *
 * Returns the data mapped to @ip अगर found otherwise शून्य. The वापस
 * is actually the address of the mapper data poपूर्णांकer. The address is
 * वापसed क्रम use हालs where the data is no bigger than a दीर्घ, and
 * the user can use the data poपूर्णांकer as its data instead of having to
 * allocate more memory क्रम the reference.
 */
व्योम **ftrace_func_mapper_find_ip(काष्ठा ftrace_func_mapper *mapper,
				  अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_func_map *map;

	entry = ftrace_lookup_ip(&mapper->hash, ip);
	अगर (!entry)
		वापस शून्य;

	map = (काष्ठा ftrace_func_map *)entry;
	वापस &map->data;
पूर्ण

/**
 * ftrace_func_mapper_add_ip - Map some data to an ip
 * @mapper: The mapper that has the ip maps
 * @ip: The inकाष्ठाion poपूर्णांकer address to map @data to
 * @data: The data to map to @ip
 *
 * Returns 0 on success otherwise an error.
 */
पूर्णांक ftrace_func_mapper_add_ip(काष्ठा ftrace_func_mapper *mapper,
			      अचिन्हित दीर्घ ip, व्योम *data)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_func_map *map;

	entry = ftrace_lookup_ip(&mapper->hash, ip);
	अगर (entry)
		वापस -EBUSY;

	map = kदो_स्मृति(माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	map->entry.ip = ip;
	map->data = data;

	__add_hash_entry(&mapper->hash, &map->entry);

	वापस 0;
पूर्ण

/**
 * ftrace_func_mapper_हटाओ_ip - Remove an ip from the mapping
 * @mapper: The mapper that has the ip maps
 * @ip: The inकाष्ठाion poपूर्णांकer address to हटाओ the data from
 *
 * Returns the data अगर it is found, otherwise शून्य.
 * Note, अगर the data poपूर्णांकer is used as the data itself, (see 
 * ftrace_func_mapper_find_ip(), then the वापस value may be meaningless,
 * अगर the data poपूर्णांकer was set to zero.
 */
व्योम *ftrace_func_mapper_हटाओ_ip(काष्ठा ftrace_func_mapper *mapper,
				   अचिन्हित दीर्घ ip)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_func_map *map;
	व्योम *data;

	entry = ftrace_lookup_ip(&mapper->hash, ip);
	अगर (!entry)
		वापस शून्य;

	map = (काष्ठा ftrace_func_map *)entry;
	data = map->data;

	हटाओ_hash_entry(&mapper->hash, entry);
	kमुक्त(entry);

	वापस data;
पूर्ण

/**
 * मुक्त_ftrace_func_mapper - मुक्त a mapping of ips and data
 * @mapper: The mapper that has the ip maps
 * @मुक्त_func: A function to be called on each data item.
 *
 * This is used to मुक्त the function mapper. The @मुक्त_func is optional
 * and can be used अगर the data needs to be मुक्तd as well.
 */
व्योम मुक्त_ftrace_func_mapper(काष्ठा ftrace_func_mapper *mapper,
			     ftrace_mapper_func मुक्त_func)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_func_map *map;
	काष्ठा hlist_head *hhd;
	पूर्णांक size, i;

	अगर (!mapper)
		वापस;

	अगर (मुक्त_func && mapper->hash.count) अणु
		size = 1 << mapper->hash.size_bits;
		क्रम (i = 0; i < size; i++) अणु
			hhd = &mapper->hash.buckets[i];
			hlist_क्रम_each_entry(entry, hhd, hlist) अणु
				map = (काष्ठा ftrace_func_map *)entry;
				मुक्त_func(map);
			पूर्ण
		पूर्ण
	पूर्ण
	मुक्त_ftrace_hash(&mapper->hash);
पूर्ण

अटल व्योम release_probe(काष्ठा ftrace_func_probe *probe)
अणु
	काष्ठा ftrace_probe_ops *probe_ops;

	mutex_lock(&ftrace_lock);

	WARN_ON(probe->ref <= 0);

	/* Subtract the ref that was used to protect this instance */
	probe->ref--;

	अगर (!probe->ref) अणु
		probe_ops = probe->probe_ops;
		/*
		 * Sending zero as ip tells probe_ops to मुक्त
		 * the probe->data itself
		 */
		अगर (probe_ops->मुक्त)
			probe_ops->मुक्त(probe_ops, probe->tr, 0, probe->data);
		list_del(&probe->list);
		kमुक्त(probe);
	पूर्ण
	mutex_unlock(&ftrace_lock);
पूर्ण

अटल व्योम acquire_probe_locked(काष्ठा ftrace_func_probe *probe)
अणु
	/*
	 * Add one ref to keep it from being मुक्तd when releasing the
	 * ftrace_lock mutex.
	 */
	probe->ref++;
पूर्ण

पूर्णांक
रेजिस्टर_ftrace_function_probe(अक्षर *glob, काष्ठा trace_array *tr,
			       काष्ठा ftrace_probe_ops *probe_ops,
			       व्योम *data)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_func_probe *probe;
	काष्ठा ftrace_hash **orig_hash;
	काष्ठा ftrace_hash *old_hash;
	काष्ठा ftrace_hash *hash;
	पूर्णांक count = 0;
	पूर्णांक size;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (WARN_ON(!tr))
		वापस -EINVAL;

	/* We करो not support '!' क्रम function probes */
	अगर (WARN_ON(glob[0] == '!'))
		वापस -EINVAL;


	mutex_lock(&ftrace_lock);
	/* Check अगर the probe_ops is alपढ़ोy रेजिस्टरed */
	list_क्रम_each_entry(probe, &tr->func_probes, list) अणु
		अगर (probe->probe_ops == probe_ops)
			अवरोध;
	पूर्ण
	अगर (&probe->list == &tr->func_probes) अणु
		probe = kzalloc(माप(*probe), GFP_KERNEL);
		अगर (!probe) अणु
			mutex_unlock(&ftrace_lock);
			वापस -ENOMEM;
		पूर्ण
		probe->probe_ops = probe_ops;
		probe->ops.func = function_trace_probe_call;
		probe->tr = tr;
		ftrace_ops_init(&probe->ops);
		list_add(&probe->list, &tr->func_probes);
	पूर्ण

	acquire_probe_locked(probe);

	mutex_unlock(&ftrace_lock);

	/*
	 * Note, there's a small winकरोw here that the func_hash->filter_hash
	 * may be शून्य or empty. Need to be careful when पढ़ोing the loop.
	 */
	mutex_lock(&probe->ops.func_hash->regex_lock);

	orig_hash = &probe->ops.func_hash->filter_hash;
	old_hash = *orig_hash;
	hash = alloc_and_copy_ftrace_hash(FTRACE_HASH_DEFAULT_BITS, old_hash);

	अगर (!hash) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = ftrace_match_records(hash, glob, म_माप(glob));

	/* Nothing found? */
	अगर (!ret)
		ret = -EINVAL;

	अगर (ret < 0)
		जाओ out;

	size = 1 << hash->size_bits;
	क्रम (i = 0; i < size; i++) अणु
		hlist_क्रम_each_entry(entry, &hash->buckets[i], hlist) अणु
			अगर (ftrace_lookup_ip(old_hash, entry->ip))
				जारी;
			/*
			 * The caller might want to करो something special
			 * क्रम each function we find. We call the callback
			 * to give the caller an opportunity to करो so.
			 */
			अगर (probe_ops->init) अणु
				ret = probe_ops->init(probe_ops, tr,
						      entry->ip, data,
						      &probe->data);
				अगर (ret < 0) अणु
					अगर (probe_ops->मुक्त && count)
						probe_ops->मुक्त(probe_ops, tr,
								0, probe->data);
					probe->data = शून्य;
					जाओ out;
				पूर्ण
			पूर्ण
			count++;
		पूर्ण
	पूर्ण

	mutex_lock(&ftrace_lock);

	अगर (!count) अणु
		/* Nothing was added? */
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = ftrace_hash_move_and_update_ops(&probe->ops, orig_hash,
					      hash, 1);
	अगर (ret < 0)
		जाओ err_unlock;

	/* One ref क्रम each new function traced */
	probe->ref += count;

	अगर (!(probe->ops.flags & FTRACE_OPS_FL_ENABLED))
		ret = ftrace_startup(&probe->ops, 0);

 out_unlock:
	mutex_unlock(&ftrace_lock);

	अगर (!ret)
		ret = count;
 out:
	mutex_unlock(&probe->ops.func_hash->regex_lock);
	मुक्त_ftrace_hash(hash);

	release_probe(probe);

	वापस ret;

 err_unlock:
	अगर (!probe_ops->मुक्त || !count)
		जाओ out_unlock;

	/* Failed to करो the move, need to call the मुक्त functions */
	क्रम (i = 0; i < size; i++) अणु
		hlist_क्रम_each_entry(entry, &hash->buckets[i], hlist) अणु
			अगर (ftrace_lookup_ip(old_hash, entry->ip))
				जारी;
			probe_ops->मुक्त(probe_ops, tr, entry->ip, probe->data);
		पूर्ण
	पूर्ण
	जाओ out_unlock;
पूर्ण

पूर्णांक
unरेजिस्टर_ftrace_function_probe_func(अक्षर *glob, काष्ठा trace_array *tr,
				      काष्ठा ftrace_probe_ops *probe_ops)
अणु
	काष्ठा ftrace_ops_hash old_hash_ops;
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_func_probe *probe;
	काष्ठा ftrace_glob func_g;
	काष्ठा ftrace_hash **orig_hash;
	काष्ठा ftrace_hash *old_hash;
	काष्ठा ftrace_hash *hash = शून्य;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा hlist_head hhd;
	अक्षर str[KSYM_SYMBOL_LEN];
	पूर्णांक count = 0;
	पूर्णांक i, ret = -ENODEV;
	पूर्णांक size;

	अगर (!glob || !म_माप(glob) || !म_भेद(glob, "*"))
		func_g.search = शून्य;
	अन्यथा अणु
		पूर्णांक not;

		func_g.type = filter_parse_regex(glob, म_माप(glob),
						 &func_g.search, &not);
		func_g.len = म_माप(func_g.search);

		/* we करो not support '!' क्रम function probes */
		अगर (WARN_ON(not))
			वापस -EINVAL;
	पूर्ण

	mutex_lock(&ftrace_lock);
	/* Check अगर the probe_ops is alपढ़ोy रेजिस्टरed */
	list_क्रम_each_entry(probe, &tr->func_probes, list) अणु
		अगर (probe->probe_ops == probe_ops)
			अवरोध;
	पूर्ण
	अगर (&probe->list == &tr->func_probes)
		जाओ err_unlock_ftrace;

	ret = -EINVAL;
	अगर (!(probe->ops.flags & FTRACE_OPS_FL_INITIALIZED))
		जाओ err_unlock_ftrace;

	acquire_probe_locked(probe);

	mutex_unlock(&ftrace_lock);

	mutex_lock(&probe->ops.func_hash->regex_lock);

	orig_hash = &probe->ops.func_hash->filter_hash;
	old_hash = *orig_hash;

	अगर (ftrace_hash_empty(old_hash))
		जाओ out_unlock;

	old_hash_ops.filter_hash = old_hash;
	/* Probes only have filters */
	old_hash_ops.notrace_hash = शून्य;

	ret = -ENOMEM;
	hash = alloc_and_copy_ftrace_hash(FTRACE_HASH_DEFAULT_BITS, old_hash);
	अगर (!hash)
		जाओ out_unlock;

	INIT_HLIST_HEAD(&hhd);

	size = 1 << hash->size_bits;
	क्रम (i = 0; i < size; i++) अणु
		hlist_क्रम_each_entry_safe(entry, पंचांगp, &hash->buckets[i], hlist) अणु

			अगर (func_g.search) अणु
				kallsyms_lookup(entry->ip, शून्य, शून्य,
						शून्य, str);
				अगर (!ftrace_match(str, &func_g))
					जारी;
			पूर्ण
			count++;
			हटाओ_hash_entry(hash, entry);
			hlist_add_head(&entry->hlist, &hhd);
		पूर्ण
	पूर्ण

	/* Nothing found? */
	अगर (!count) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	mutex_lock(&ftrace_lock);

	WARN_ON(probe->ref < count);

	probe->ref -= count;

	अगर (ftrace_hash_empty(hash))
		ftrace_shutकरोwn(&probe->ops, 0);

	ret = ftrace_hash_move_and_update_ops(&probe->ops, orig_hash,
					      hash, 1);

	/* still need to update the function call sites */
	अगर (ftrace_enabled && !ftrace_hash_empty(hash))
		ftrace_run_modअगरy_code(&probe->ops, FTRACE_UPDATE_CALLS,
				       &old_hash_ops);
	synchronize_rcu();

	hlist_क्रम_each_entry_safe(entry, पंचांगp, &hhd, hlist) अणु
		hlist_del(&entry->hlist);
		अगर (probe_ops->मुक्त)
			probe_ops->मुक्त(probe_ops, tr, entry->ip, probe->data);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&ftrace_lock);

 out_unlock:
	mutex_unlock(&probe->ops.func_hash->regex_lock);
	मुक्त_ftrace_hash(hash);

	release_probe(probe);

	वापस ret;

 err_unlock_ftrace:
	mutex_unlock(&ftrace_lock);
	वापस ret;
पूर्ण

व्योम clear_ftrace_function_probes(काष्ठा trace_array *tr)
अणु
	काष्ठा ftrace_func_probe *probe, *n;

	list_क्रम_each_entry_safe(probe, n, &tr->func_probes, list)
		unरेजिस्टर_ftrace_function_probe_func(शून्य, tr, probe->probe_ops);
पूर्ण

अटल LIST_HEAD(ftrace_commands);
अटल DEFINE_MUTEX(ftrace_cmd_mutex);

/*
 * Currently we only रेजिस्टर ftrace commands from __init, so mark this
 * __init too.
 */
__init पूर्णांक रेजिस्टर_ftrace_command(काष्ठा ftrace_func_command *cmd)
अणु
	काष्ठा ftrace_func_command *p;
	पूर्णांक ret = 0;

	mutex_lock(&ftrace_cmd_mutex);
	list_क्रम_each_entry(p, &ftrace_commands, list) अणु
		अगर (म_भेद(cmd->name, p->name) == 0) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	list_add(&cmd->list, &ftrace_commands);
 out_unlock:
	mutex_unlock(&ftrace_cmd_mutex);

	वापस ret;
पूर्ण

/*
 * Currently we only unरेजिस्टर ftrace commands from __init, so mark
 * this __init too.
 */
__init पूर्णांक unरेजिस्टर_ftrace_command(काष्ठा ftrace_func_command *cmd)
अणु
	काष्ठा ftrace_func_command *p, *n;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&ftrace_cmd_mutex);
	list_क्रम_each_entry_safe(p, n, &ftrace_commands, list) अणु
		अगर (म_भेद(cmd->name, p->name) == 0) अणु
			ret = 0;
			list_del_init(&p->list);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
 out_unlock:
	mutex_unlock(&ftrace_cmd_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ftrace_process_regex(काष्ठा ftrace_iterator *iter,
				अक्षर *buff, पूर्णांक len, पूर्णांक enable)
अणु
	काष्ठा ftrace_hash *hash = iter->hash;
	काष्ठा trace_array *tr = iter->ops->निजी;
	अक्षर *func, *command, *next = buff;
	काष्ठा ftrace_func_command *p;
	पूर्णांक ret = -EINVAL;

	func = strsep(&next, ":");

	अगर (!next) अणु
		ret = ftrace_match_records(hash, func, len);
		अगर (!ret)
			ret = -EINVAL;
		अगर (ret < 0)
			वापस ret;
		वापस 0;
	पूर्ण

	/* command found */

	command = strsep(&next, ":");

	mutex_lock(&ftrace_cmd_mutex);
	list_क्रम_each_entry(p, &ftrace_commands, list) अणु
		अगर (म_भेद(p->name, command) == 0) अणु
			ret = p->func(tr, hash, func, command, next, enable);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
 out_unlock:
	mutex_unlock(&ftrace_cmd_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
ftrace_regex_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		   माप_प्रकार cnt, loff_t *ppos, पूर्णांक enable)
अणु
	काष्ठा ftrace_iterator *iter;
	काष्ठा trace_parser *parser;
	sमाप_प्रकार ret, पढ़ो;

	अगर (!cnt)
		वापस 0;

	अगर (file->f_mode & FMODE_READ) अणु
		काष्ठा seq_file *m = file->निजी_data;
		iter = m->निजी;
	पूर्ण अन्यथा
		iter = file->निजी_data;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	/* iter->hash is a local copy, so we करोn't need regex_lock */

	parser = &iter->parser;
	पढ़ो = trace_get_user(parser, ubuf, cnt, ppos);

	अगर (पढ़ो >= 0 && trace_parser_loaded(parser) &&
	    !trace_parser_cont(parser)) अणु
		ret = ftrace_process_regex(iter, parser->buffer,
					   parser->idx, enable);
		trace_parser_clear(parser);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = पढ़ो;
 out:
	वापस ret;
पूर्ण

sमाप_प्रकार
ftrace_filter_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		    माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस ftrace_regex_ग_लिखो(file, ubuf, cnt, ppos, 1);
पूर्ण

sमाप_प्रकार
ftrace_notrace_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		     माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस ftrace_regex_ग_लिखो(file, ubuf, cnt, ppos, 0);
पूर्ण

अटल पूर्णांक
ftrace_match_addr(काष्ठा ftrace_hash *hash, अचिन्हित दीर्घ ip, पूर्णांक हटाओ)
अणु
	काष्ठा ftrace_func_entry *entry;

	अगर (!ftrace_location(ip))
		वापस -EINVAL;

	अगर (हटाओ) अणु
		entry = ftrace_lookup_ip(hash, ip);
		अगर (!entry)
			वापस -ENOENT;
		मुक्त_hash_entry(hash, entry);
		वापस 0;
	पूर्ण

	वापस add_hash_entry(hash, ip);
पूर्ण

अटल पूर्णांक
ftrace_set_hash(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf, पूर्णांक len,
		अचिन्हित दीर्घ ip, पूर्णांक हटाओ, पूर्णांक reset, पूर्णांक enable)
अणु
	काष्ठा ftrace_hash **orig_hash;
	काष्ठा ftrace_hash *hash;
	पूर्णांक ret;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	mutex_lock(&ops->func_hash->regex_lock);

	अगर (enable)
		orig_hash = &ops->func_hash->filter_hash;
	अन्यथा
		orig_hash = &ops->func_hash->notrace_hash;

	अगर (reset)
		hash = alloc_ftrace_hash(FTRACE_HASH_DEFAULT_BITS);
	अन्यथा
		hash = alloc_and_copy_ftrace_hash(FTRACE_HASH_DEFAULT_BITS, *orig_hash);

	अगर (!hash) अणु
		ret = -ENOMEM;
		जाओ out_regex_unlock;
	पूर्ण

	अगर (buf && !ftrace_match_records(hash, buf, len)) अणु
		ret = -EINVAL;
		जाओ out_regex_unlock;
	पूर्ण
	अगर (ip) अणु
		ret = ftrace_match_addr(hash, ip, हटाओ);
		अगर (ret < 0)
			जाओ out_regex_unlock;
	पूर्ण

	mutex_lock(&ftrace_lock);
	ret = ftrace_hash_move_and_update_ops(ops, orig_hash, hash, enable);
	mutex_unlock(&ftrace_lock);

 out_regex_unlock:
	mutex_unlock(&ops->func_hash->regex_lock);

	मुक्त_ftrace_hash(hash);
	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_set_addr(काष्ठा ftrace_ops *ops, अचिन्हित दीर्घ ip, पूर्णांक हटाओ,
		पूर्णांक reset, पूर्णांक enable)
अणु
	वापस ftrace_set_hash(ops, शून्य, 0, ip, हटाओ, reset, enable);
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS

काष्ठा ftrace_direct_func अणु
	काष्ठा list_head	next;
	अचिन्हित दीर्घ		addr;
	पूर्णांक			count;
पूर्ण;

अटल LIST_HEAD(ftrace_direct_funcs);

/**
 * ftrace_find_direct_func - test an address अगर it is a रेजिस्टरed direct caller
 * @addr: The address of a रेजिस्टरed direct caller
 *
 * This searches to see अगर a ftrace direct caller has been रेजिस्टरed
 * at a specअगरic address, and अगर so, it वापसs a descriptor क्रम it.
 *
 * This can be used by architecture code to see अगर an address is
 * a direct caller (trampoline) attached to a fentry/mcount location.
 * This is useful क्रम the function_graph tracer, as it may need to
 * करो adjusपंचांगents अगर it traced a location that also has a direct
 * trampoline attached to it.
 */
काष्ठा ftrace_direct_func *ftrace_find_direct_func(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_direct_func *entry;
	bool found = false;

	/* May be called by fgraph trampoline (रक्षित by rcu tasks) */
	list_क्रम_each_entry_rcu(entry, &ftrace_direct_funcs, next) अणु
		अगर (entry->addr == addr) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found)
		वापस entry;

	वापस शून्य;
पूर्ण

अटल काष्ठा ftrace_direct_func *ftrace_alloc_direct_func(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_direct_func *direct;

	direct = kदो_स्मृति(माप(*direct), GFP_KERNEL);
	अगर (!direct)
		वापस शून्य;
	direct->addr = addr;
	direct->count = 0;
	list_add_rcu(&direct->next, &ftrace_direct_funcs);
	ftrace_direct_func_count++;
	वापस direct;
पूर्ण

/**
 * रेजिस्टर_ftrace_direct - Call a custom trampoline directly
 * @ip: The address of the nop at the beginning of a function
 * @addr: The address of the trampoline to call at @ip
 *
 * This is used to connect a direct call from the nop location (@ip)
 * at the start of ftrace traced functions. The location that it calls
 * (@addr) must be able to handle a direct call, and save the parameters
 * of the function being traced, and restore them (or inject new ones
 * अगर needed), beक्रमe वापसing.
 *
 * Returns:
 *  0 on success
 *  -EBUSY - Another direct function is alपढ़ोy attached (there can be only one)
 *  -ENODEV - @ip करोes not poपूर्णांक to a ftrace nop location (or not supported)
 *  -ENOMEM - There was an allocation failure.
 */
पूर्णांक रेजिस्टर_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_direct_func *direct;
	काष्ठा ftrace_func_entry *entry;
	काष्ठा ftrace_hash *मुक्त_hash = शून्य;
	काष्ठा dyn_ftrace *rec;
	पूर्णांक ret = -EBUSY;

	mutex_lock(&direct_mutex);

	/* See अगर there's a direct function at @ip alपढ़ोy */
	अगर (ftrace_find_rec_direct(ip))
		जाओ out_unlock;

	ret = -ENODEV;
	rec = lookup_rec(ip, ip);
	अगर (!rec)
		जाओ out_unlock;

	/*
	 * Check अगर the rec says it has a direct call but we didn't
	 * find one earlier?
	 */
	अगर (WARN_ON(rec->flags & FTRACE_FL_सूचीECT))
		जाओ out_unlock;

	/* Make sure the ip poपूर्णांकs to the exact record */
	अगर (ip != rec->ip) अणु
		ip = rec->ip;
		/* Need to check this ip क्रम a direct. */
		अगर (ftrace_find_rec_direct(ip))
			जाओ out_unlock;
	पूर्ण

	ret = -ENOMEM;
	अगर (ftrace_hash_empty(direct_functions) ||
	    direct_functions->count > 2 * (1 << direct_functions->size_bits)) अणु
		काष्ठा ftrace_hash *new_hash;
		पूर्णांक size = ftrace_hash_empty(direct_functions) ? 0 :
			direct_functions->count + 1;

		अगर (size < 32)
			size = 32;

		new_hash = dup_hash(direct_functions, size);
		अगर (!new_hash)
			जाओ out_unlock;

		मुक्त_hash = direct_functions;
		direct_functions = new_hash;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		जाओ out_unlock;

	direct = ftrace_find_direct_func(addr);
	अगर (!direct) अणु
		direct = ftrace_alloc_direct_func(addr);
		अगर (!direct) अणु
			kमुक्त(entry);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	entry->ip = ip;
	entry->direct = addr;
	__add_hash_entry(direct_functions, entry);

	ret = ftrace_set_filter_ip(&direct_ops, ip, 0, 0);
	अगर (ret)
		हटाओ_hash_entry(direct_functions, entry);

	अगर (!ret && !(direct_ops.flags & FTRACE_OPS_FL_ENABLED)) अणु
		ret = रेजिस्टर_ftrace_function(&direct_ops);
		अगर (ret)
			ftrace_set_filter_ip(&direct_ops, ip, 1, 0);
	पूर्ण

	अगर (ret) अणु
		kमुक्त(entry);
		अगर (!direct->count) अणु
			list_del_rcu(&direct->next);
			synchronize_rcu_tasks();
			kमुक्त(direct);
			अगर (मुक्त_hash)
				मुक्त_ftrace_hash(मुक्त_hash);
			मुक्त_hash = शून्य;
			ftrace_direct_func_count--;
		पूर्ण
	पूर्ण अन्यथा अणु
		direct->count++;
	पूर्ण
 out_unlock:
	mutex_unlock(&direct_mutex);

	अगर (मुक्त_hash) अणु
		synchronize_rcu_tasks();
		मुक्त_ftrace_hash(मुक्त_hash);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_ftrace_direct);

अटल काष्ठा ftrace_func_entry *find_direct_entry(अचिन्हित दीर्घ *ip,
						   काष्ठा dyn_ftrace **recp)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा dyn_ftrace *rec;

	rec = lookup_rec(*ip, *ip);
	अगर (!rec)
		वापस शून्य;

	entry = __ftrace_lookup_ip(direct_functions, rec->ip);
	अगर (!entry) अणु
		WARN_ON(rec->flags & FTRACE_FL_सूचीECT);
		वापस शून्य;
	पूर्ण

	WARN_ON(!(rec->flags & FTRACE_FL_सूचीECT));

	/* Passed in ip just needs to be on the call site */
	*ip = rec->ip;

	अगर (recp)
		*recp = rec;

	वापस entry;
पूर्ण

पूर्णांक unरेजिस्टर_ftrace_direct(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ftrace_direct_func *direct;
	काष्ठा ftrace_func_entry *entry;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&direct_mutex);

	entry = find_direct_entry(&ip, शून्य);
	अगर (!entry)
		जाओ out_unlock;

	अगर (direct_functions->count == 1)
		unरेजिस्टर_ftrace_function(&direct_ops);

	ret = ftrace_set_filter_ip(&direct_ops, ip, 1, 0);

	WARN_ON(ret);

	हटाओ_hash_entry(direct_functions, entry);

	direct = ftrace_find_direct_func(addr);
	अगर (!WARN_ON(!direct)) अणु
		/* This is the good path (see the ! beक्रमe WARN) */
		direct->count--;
		WARN_ON(direct->count < 0);
		अगर (!direct->count) अणु
			list_del_rcu(&direct->next);
			synchronize_rcu_tasks();
			kमुक्त(direct);
			kमुक्त(entry);
			ftrace_direct_func_count--;
		पूर्ण
	पूर्ण
 out_unlock:
	mutex_unlock(&direct_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_ftrace_direct);

अटल काष्ठा ftrace_ops stub_ops = अणु
	.func		= ftrace_stub,
पूर्ण;

/**
 * ftrace_modअगरy_direct_caller - modअगरy ftrace nop directly
 * @entry: The ftrace hash entry of the direct helper क्रम @rec
 * @rec: The record representing the function site to patch
 * @old_addr: The location that the site at @rec->ip currently calls
 * @new_addr: The location that the site at @rec->ip should call
 *
 * An architecture may overग_लिखो this function to optimize the
 * changing of the direct callback on an ftrace nop location.
 * This is called with the ftrace_lock mutex held, and no other
 * ftrace callbacks are on the associated record (@rec). Thus,
 * it is safe to modअगरy the ftrace record, where it should be
 * currently calling @old_addr directly, to call @new_addr.
 *
 * Safety checks should be made to make sure that the code at
 * @rec->ip is currently calling @old_addr. And this must
 * also update entry->direct to @new_addr.
 */
पूर्णांक __weak ftrace_modअगरy_direct_caller(काष्ठा ftrace_func_entry *entry,
				       काष्ठा dyn_ftrace *rec,
				       अचिन्हित दीर्घ old_addr,
				       अचिन्हित दीर्घ new_addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	पूर्णांक ret;

	/*
	 * The ftrace_lock was used to determine अगर the record
	 * had more than one रेजिस्टरed user to it. If it did,
	 * we needed to prevent that from changing to करो the quick
	 * चयन. But अगर it did not (only a direct caller was attached)
	 * then this function is called. But this function can deal
	 * with attached callers to the rec that we care about, and
	 * since this function uses standard ftrace calls that take
	 * the ftrace_lock mutex, we need to release it.
	 */
	mutex_unlock(&ftrace_lock);

	/*
	 * By setting a stub function at the same address, we क्रमce
	 * the code to call the iterator and the direct_ops helper.
	 * This means that @ip करोes not call the direct call, and
	 * we can simply modअगरy it.
	 */
	ret = ftrace_set_filter_ip(&stub_ops, ip, 0, 0);
	अगर (ret)
		जाओ out_lock;

	ret = रेजिस्टर_ftrace_function(&stub_ops);
	अगर (ret) अणु
		ftrace_set_filter_ip(&stub_ops, ip, 1, 0);
		जाओ out_lock;
	पूर्ण

	entry->direct = new_addr;

	/*
	 * By removing the stub, we put back the direct call, calling
	 * the @new_addr.
	 */
	unरेजिस्टर_ftrace_function(&stub_ops);
	ftrace_set_filter_ip(&stub_ops, ip, 1, 0);

 out_lock:
	mutex_lock(&ftrace_lock);

	वापस ret;
पूर्ण

/**
 * modअगरy_ftrace_direct - Modअगरy an existing direct call to call something अन्यथा
 * @ip: The inकाष्ठाion poपूर्णांकer to modअगरy
 * @old_addr: The address that the current @ip calls directly
 * @new_addr: The address that the @ip should call
 *
 * This modअगरies a ftrace direct caller at an inकाष्ठाion poपूर्णांकer without
 * having to disable it first. The direct call will चयन over to the
 * @new_addr without missing anything.
 *
 * Returns: zero on success. Non zero on error, which includes:
 *  -ENODEV : the @ip given has no direct caller attached
 *  -EINVAL : the @old_addr करोes not match the current direct caller
 */
पूर्णांक modअगरy_ftrace_direct(अचिन्हित दीर्घ ip,
			 अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ new_addr)
अणु
	काष्ठा ftrace_direct_func *direct, *new_direct = शून्य;
	काष्ठा ftrace_func_entry *entry;
	काष्ठा dyn_ftrace *rec;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&direct_mutex);

	mutex_lock(&ftrace_lock);
	entry = find_direct_entry(&ip, &rec);
	अगर (!entry)
		जाओ out_unlock;

	ret = -EINVAL;
	अगर (entry->direct != old_addr)
		जाओ out_unlock;

	direct = ftrace_find_direct_func(old_addr);
	अगर (WARN_ON(!direct))
		जाओ out_unlock;
	अगर (direct->count > 1) अणु
		ret = -ENOMEM;
		new_direct = ftrace_alloc_direct_func(new_addr);
		अगर (!new_direct)
			जाओ out_unlock;
		direct->count--;
		new_direct->count++;
	पूर्ण अन्यथा अणु
		direct->addr = new_addr;
	पूर्ण

	/*
	 * If there's no other ftrace callback on the rec->ip location,
	 * then it can be changed directly by the architecture.
	 * If there is another caller, then we just need to change the
	 * direct caller helper to poपूर्णांक to @new_addr.
	 */
	अगर (ftrace_rec_count(rec) == 1) अणु
		ret = ftrace_modअगरy_direct_caller(entry, rec, old_addr, new_addr);
	पूर्ण अन्यथा अणु
		entry->direct = new_addr;
		ret = 0;
	पूर्ण

	अगर (unlikely(ret && new_direct)) अणु
		direct->count++;
		list_del_rcu(&new_direct->next);
		synchronize_rcu_tasks();
		kमुक्त(new_direct);
		ftrace_direct_func_count--;
	पूर्ण

 out_unlock:
	mutex_unlock(&ftrace_lock);
	mutex_unlock(&direct_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(modअगरy_ftrace_direct);
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE_WITH_सूचीECT_CALLS */

/**
 * ftrace_set_filter_ip - set a function to filter on in ftrace by address
 * @ops - the ops to set the filter with
 * @ip - the address to add to or हटाओ from the filter.
 * @हटाओ - non zero to हटाओ the ip from the filter
 * @reset - non zero to reset all filters beक्रमe applying this filter.
 *
 * Filters denote which functions should be enabled when tracing is enabled
 * If @ip is शून्य, it fails to update filter.
 */
पूर्णांक ftrace_set_filter_ip(काष्ठा ftrace_ops *ops, अचिन्हित दीर्घ ip,
			 पूर्णांक हटाओ, पूर्णांक reset)
अणु
	ftrace_ops_init(ops);
	वापस ftrace_set_addr(ops, ip, हटाओ, reset, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_set_filter_ip);

/**
 * ftrace_ops_set_global_filter - setup ops to use global filters
 * @ops - the ops which will use the global filters
 *
 * ftrace users who need global function trace filtering should call this.
 * It can set the global filter only अगर ops were not initialized beक्रमe.
 */
व्योम ftrace_ops_set_global_filter(काष्ठा ftrace_ops *ops)
अणु
	अगर (ops->flags & FTRACE_OPS_FL_INITIALIZED)
		वापस;

	ftrace_ops_init(ops);
	ops->func_hash = &global_ops.local_hash;
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_ops_set_global_filter);

अटल पूर्णांक
ftrace_set_regex(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf, पूर्णांक len,
		 पूर्णांक reset, पूर्णांक enable)
अणु
	वापस ftrace_set_hash(ops, buf, len, 0, 0, reset, enable);
पूर्ण

/**
 * ftrace_set_filter - set a function to filter on in ftrace
 * @ops - the ops to set the filter with
 * @buf - the string that holds the function filter text.
 * @len - the length of the string.
 * @reset - non zero to reset all filters beक्रमe applying this filter.
 *
 * Filters denote which functions should be enabled when tracing is enabled.
 * If @buf is शून्य and reset is set, all functions will be enabled क्रम tracing.
 */
पूर्णांक ftrace_set_filter(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf,
		       पूर्णांक len, पूर्णांक reset)
अणु
	ftrace_ops_init(ops);
	वापस ftrace_set_regex(ops, buf, len, reset, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_set_filter);

/**
 * ftrace_set_notrace - set a function to not trace in ftrace
 * @ops - the ops to set the notrace filter with
 * @buf - the string that holds the function notrace text.
 * @len - the length of the string.
 * @reset - non zero to reset all filters beक्रमe applying this filter.
 *
 * Notrace Filters denote which functions should not be enabled when tracing
 * is enabled. If @buf is शून्य and reset is set, all functions will be enabled
 * क्रम tracing.
 */
पूर्णांक ftrace_set_notrace(काष्ठा ftrace_ops *ops, अचिन्हित अक्षर *buf,
			पूर्णांक len, पूर्णांक reset)
अणु
	ftrace_ops_init(ops);
	वापस ftrace_set_regex(ops, buf, len, reset, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_set_notrace);
/**
 * ftrace_set_global_filter - set a function to filter on with global tracers
 * @buf - the string that holds the function filter text.
 * @len - the length of the string.
 * @reset - non zero to reset all filters beक्रमe applying this filter.
 *
 * Filters denote which functions should be enabled when tracing is enabled.
 * If @buf is शून्य and reset is set, all functions will be enabled क्रम tracing.
 */
व्योम ftrace_set_global_filter(अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक reset)
अणु
	ftrace_set_regex(&global_ops, buf, len, reset, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_set_global_filter);

/**
 * ftrace_set_global_notrace - set a function to not trace with global tracers
 * @buf - the string that holds the function notrace text.
 * @len - the length of the string.
 * @reset - non zero to reset all filters beक्रमe applying this filter.
 *
 * Notrace Filters denote which functions should not be enabled when tracing
 * is enabled. If @buf is शून्य and reset is set, all functions will be enabled
 * क्रम tracing.
 */
व्योम ftrace_set_global_notrace(अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक reset)
अणु
	ftrace_set_regex(&global_ops, buf, len, reset, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_set_global_notrace);

/*
 * command line पूर्णांकerface to allow users to set filters on boot up.
 */
#घोषणा FTRACE_FILTER_SIZE		COMMAND_LINE_SIZE
अटल अक्षर ftrace_notrace_buf[FTRACE_FILTER_SIZE] __initdata;
अटल अक्षर ftrace_filter_buf[FTRACE_FILTER_SIZE] __initdata;

/* Used by function selftest to not test अगर filter is set */
bool ftrace_filter_param __initdata;

अटल पूर्णांक __init set_ftrace_notrace(अक्षर *str)
अणु
	ftrace_filter_param = true;
	strlcpy(ftrace_notrace_buf, str, FTRACE_FILTER_SIZE);
	वापस 1;
पूर्ण
__setup("ftrace_notrace=", set_ftrace_notrace);

अटल पूर्णांक __init set_ftrace_filter(अक्षर *str)
अणु
	ftrace_filter_param = true;
	strlcpy(ftrace_filter_buf, str, FTRACE_FILTER_SIZE);
	वापस 1;
पूर्ण
__setup("ftrace_filter=", set_ftrace_filter);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
अटल अक्षर ftrace_graph_buf[FTRACE_FILTER_SIZE] __initdata;
अटल अक्षर ftrace_graph_notrace_buf[FTRACE_FILTER_SIZE] __initdata;
अटल पूर्णांक ftrace_graph_set_hash(काष्ठा ftrace_hash *hash, अक्षर *buffer);

अटल पूर्णांक __init set_graph_function(अक्षर *str)
अणु
	strlcpy(ftrace_graph_buf, str, FTRACE_FILTER_SIZE);
	वापस 1;
पूर्ण
__setup("ftrace_graph_filter=", set_graph_function);

अटल पूर्णांक __init set_graph_notrace_function(अक्षर *str)
अणु
	strlcpy(ftrace_graph_notrace_buf, str, FTRACE_FILTER_SIZE);
	वापस 1;
पूर्ण
__setup("ftrace_graph_notrace=", set_graph_notrace_function);

अटल पूर्णांक __init set_graph_max_depth_function(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	fgraph_max_depth = simple_म_से_अदीर्घ(str, शून्य, 0);
	वापस 1;
पूर्ण
__setup("ftrace_graph_max_depth=", set_graph_max_depth_function);

अटल व्योम __init set_ftrace_early_graph(अक्षर *buf, पूर्णांक enable)
अणु
	पूर्णांक ret;
	अक्षर *func;
	काष्ठा ftrace_hash *hash;

	hash = alloc_ftrace_hash(FTRACE_HASH_DEFAULT_BITS);
	अगर (MEM_FAIL(!hash, "Failed to allocate hash\n"))
		वापस;

	जबतक (buf) अणु
		func = strsep(&buf, ",");
		/* we allow only one expression at a समय */
		ret = ftrace_graph_set_hash(hash, func);
		अगर (ret)
			prपूर्णांकk(KERN_DEBUG "ftrace: function %s not "
					  "traceable\n", func);
	पूर्ण

	अगर (enable)
		ftrace_graph_hash = hash;
	अन्यथा
		ftrace_graph_notrace_hash = hash;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

व्योम __init
ftrace_set_early_filter(काष्ठा ftrace_ops *ops, अक्षर *buf, पूर्णांक enable)
अणु
	अक्षर *func;

	ftrace_ops_init(ops);

	जबतक (buf) अणु
		func = strsep(&buf, ",");
		ftrace_set_regex(ops, func, म_माप(func), 0, enable);
	पूर्ण
पूर्ण

अटल व्योम __init set_ftrace_early_filters(व्योम)
अणु
	अगर (ftrace_filter_buf[0])
		ftrace_set_early_filter(&global_ops, ftrace_filter_buf, 1);
	अगर (ftrace_notrace_buf[0])
		ftrace_set_early_filter(&global_ops, ftrace_notrace_buf, 0);
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अगर (ftrace_graph_buf[0])
		set_ftrace_early_graph(ftrace_graph_buf, 1);
	अगर (ftrace_graph_notrace_buf[0])
		set_ftrace_early_graph(ftrace_graph_notrace_buf, 0);
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
पूर्ण

पूर्णांक ftrace_regex_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = (काष्ठा seq_file *)file->निजी_data;
	काष्ठा ftrace_iterator *iter;
	काष्ठा ftrace_hash **orig_hash;
	काष्ठा trace_parser *parser;
	पूर्णांक filter_hash;

	अगर (file->f_mode & FMODE_READ) अणु
		iter = m->निजी;
		seq_release(inode, file);
	पूर्ण अन्यथा
		iter = file->निजी_data;

	parser = &iter->parser;
	अगर (trace_parser_loaded(parser)) अणु
		पूर्णांक enable = !(iter->flags & FTRACE_ITER_NOTRACE);

		ftrace_process_regex(iter, parser->buffer,
				     parser->idx, enable);
	पूर्ण

	trace_parser_put(parser);

	mutex_lock(&iter->ops->func_hash->regex_lock);

	अगर (file->f_mode & FMODE_WRITE) अणु
		filter_hash = !!(iter->flags & FTRACE_ITER_FILTER);

		अगर (filter_hash) अणु
			orig_hash = &iter->ops->func_hash->filter_hash;
			अगर (iter->tr && !list_empty(&iter->tr->mod_trace))
				iter->hash->flags |= FTRACE_HASH_FL_MOD;
		पूर्ण अन्यथा
			orig_hash = &iter->ops->func_hash->notrace_hash;

		mutex_lock(&ftrace_lock);
		ftrace_hash_move_and_update_ops(iter->ops, orig_hash,
						      iter->hash, filter_hash);
		mutex_unlock(&ftrace_lock);
	पूर्ण अन्यथा अणु
		/* For पढ़ो only, the hash is the ops hash */
		iter->hash = शून्य;
	पूर्ण

	mutex_unlock(&iter->ops->func_hash->regex_lock);
	मुक्त_ftrace_hash(iter->hash);
	अगर (iter->tr)
		trace_array_put(iter->tr);
	kमुक्त(iter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ftrace_avail_fops = अणु
	.खोलो = ftrace_avail_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release_निजी,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_enabled_fops = अणु
	.खोलो = ftrace_enabled_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release_निजी,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_filter_fops = अणु
	.खोलो = ftrace_filter_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = ftrace_filter_ग_लिखो,
	.llseek = tracing_lseek,
	.release = ftrace_regex_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_notrace_fops = अणु
	.खोलो = ftrace_notrace_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = ftrace_notrace_ग_लिखो,
	.llseek = tracing_lseek,
	.release = ftrace_regex_release,
पूर्ण;

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

अटल DEFINE_MUTEX(graph_lock);

काष्ठा ftrace_hash __rcu *ftrace_graph_hash = EMPTY_HASH;
काष्ठा ftrace_hash __rcu *ftrace_graph_notrace_hash = EMPTY_HASH;

क्रमागत graph_filter_type अणु
	GRAPH_FILTER_NOTRACE	= 0,
	GRAPH_FILTER_FUNCTION,
पूर्ण;

#घोषणा FTRACE_GRAPH_EMPTY	((व्योम *)1)

काष्ठा ftrace_graph_data अणु
	काष्ठा ftrace_hash		*hash;
	काष्ठा ftrace_func_entry	*entry;
	पूर्णांक				idx;   /* क्रम hash table iteration */
	क्रमागत graph_filter_type		type;
	काष्ठा ftrace_hash		*new_hash;
	स्थिर काष्ठा seq_operations	*seq_ops;
	काष्ठा trace_parser		parser;
पूर्ण;

अटल व्योम *
__g_next(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_graph_data *fgd = m->निजी;
	काष्ठा ftrace_func_entry *entry = fgd->entry;
	काष्ठा hlist_head *head;
	पूर्णांक i, idx = fgd->idx;

	अगर (*pos >= fgd->hash->count)
		वापस शून्य;

	अगर (entry) अणु
		hlist_क्रम_each_entry_जारी(entry, hlist) अणु
			fgd->entry = entry;
			वापस entry;
		पूर्ण

		idx++;
	पूर्ण

	क्रम (i = idx; i < 1 << fgd->hash->size_bits; i++) अणु
		head = &fgd->hash->buckets[i];
		hlist_क्रम_each_entry(entry, head, hlist) अणु
			fgd->entry = entry;
			fgd->idx = i;
			वापस entry;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *
g_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस __g_next(m, pos);
पूर्ण

अटल व्योम *g_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ftrace_graph_data *fgd = m->निजी;

	mutex_lock(&graph_lock);

	अगर (fgd->type == GRAPH_FILTER_FUNCTION)
		fgd->hash = rcu_dereference_रक्षित(ftrace_graph_hash,
					lockdep_is_held(&graph_lock));
	अन्यथा
		fgd->hash = rcu_dereference_रक्षित(ftrace_graph_notrace_hash,
					lockdep_is_held(&graph_lock));

	/* Nothing, tell g_show to prपूर्णांक all functions are enabled */
	अगर (ftrace_hash_empty(fgd->hash) && !*pos)
		वापस FTRACE_GRAPH_EMPTY;

	fgd->idx = 0;
	fgd->entry = शून्य;
	वापस __g_next(m, pos);
पूर्ण

अटल व्योम g_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&graph_lock);
पूर्ण

अटल पूर्णांक g_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ftrace_func_entry *entry = v;

	अगर (!entry)
		वापस 0;

	अगर (entry == FTRACE_GRAPH_EMPTY) अणु
		काष्ठा ftrace_graph_data *fgd = m->निजी;

		अगर (fgd->type == GRAPH_FILTER_FUNCTION)
			seq_माला_दो(m, "#### all functions enabled ####\n");
		अन्यथा
			seq_माला_दो(m, "#### no functions disabled ####\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "%ps\n", (व्योम *)entry->ip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ftrace_graph_seq_ops = अणु
	.start = g_start,
	.next = g_next,
	.stop = g_stop,
	.show = g_show,
पूर्ण;

अटल पूर्णांक
__ftrace_graph_खोलो(काष्ठा inode *inode, काष्ठा file *file,
		    काष्ठा ftrace_graph_data *fgd)
अणु
	पूर्णांक ret;
	काष्ठा ftrace_hash *new_hash = शून्य;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	अगर (file->f_mode & FMODE_WRITE) अणु
		स्थिर पूर्णांक size_bits = FTRACE_HASH_DEFAULT_BITS;

		अगर (trace_parser_get_init(&fgd->parser, FTRACE_BUFF_MAX))
			वापस -ENOMEM;

		अगर (file->f_flags & O_TRUNC)
			new_hash = alloc_ftrace_hash(size_bits);
		अन्यथा
			new_hash = alloc_and_copy_ftrace_hash(size_bits,
							      fgd->hash);
		अगर (!new_hash) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (file->f_mode & FMODE_READ) अणु
		ret = seq_खोलो(file, &ftrace_graph_seq_ops);
		अगर (!ret) अणु
			काष्ठा seq_file *m = file->निजी_data;
			m->निजी = fgd;
		पूर्ण अन्यथा अणु
			/* Failed */
			मुक्त_ftrace_hash(new_hash);
			new_hash = शून्य;
		पूर्ण
	पूर्ण अन्यथा
		file->निजी_data = fgd;

out:
	अगर (ret < 0 && file->f_mode & FMODE_WRITE)
		trace_parser_put(&fgd->parser);

	fgd->new_hash = new_hash;

	/*
	 * All uses of fgd->hash must be taken with the graph_lock
	 * held. The graph_lock is going to be released, so क्रमce
	 * fgd->hash to be reinitialized when it is taken again.
	 */
	fgd->hash = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_graph_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_graph_data *fgd;
	पूर्णांक ret;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	fgd = kदो_स्मृति(माप(*fgd), GFP_KERNEL);
	अगर (fgd == शून्य)
		वापस -ENOMEM;

	mutex_lock(&graph_lock);

	fgd->hash = rcu_dereference_रक्षित(ftrace_graph_hash,
					lockdep_is_held(&graph_lock));
	fgd->type = GRAPH_FILTER_FUNCTION;
	fgd->seq_ops = &ftrace_graph_seq_ops;

	ret = __ftrace_graph_खोलो(inode, file, fgd);
	अगर (ret < 0)
		kमुक्त(fgd);

	mutex_unlock(&graph_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_graph_notrace_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_graph_data *fgd;
	पूर्णांक ret;

	अगर (unlikely(ftrace_disabled))
		वापस -ENODEV;

	fgd = kदो_स्मृति(माप(*fgd), GFP_KERNEL);
	अगर (fgd == शून्य)
		वापस -ENOMEM;

	mutex_lock(&graph_lock);

	fgd->hash = rcu_dereference_रक्षित(ftrace_graph_notrace_hash,
					lockdep_is_held(&graph_lock));
	fgd->type = GRAPH_FILTER_NOTRACE;
	fgd->seq_ops = &ftrace_graph_seq_ops;

	ret = __ftrace_graph_खोलो(inode, file, fgd);
	अगर (ret < 0)
		kमुक्त(fgd);

	mutex_unlock(&graph_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_graph_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ftrace_graph_data *fgd;
	काष्ठा ftrace_hash *old_hash, *new_hash;
	काष्ठा trace_parser *parser;
	पूर्णांक ret = 0;

	अगर (file->f_mode & FMODE_READ) अणु
		काष्ठा seq_file *m = file->निजी_data;

		fgd = m->निजी;
		seq_release(inode, file);
	पूर्ण अन्यथा अणु
		fgd = file->निजी_data;
	पूर्ण


	अगर (file->f_mode & FMODE_WRITE) अणु

		parser = &fgd->parser;

		अगर (trace_parser_loaded((parser))) अणु
			ret = ftrace_graph_set_hash(fgd->new_hash,
						    parser->buffer);
		पूर्ण

		trace_parser_put(parser);

		new_hash = __ftrace_hash_move(fgd->new_hash);
		अगर (!new_hash) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		mutex_lock(&graph_lock);

		अगर (fgd->type == GRAPH_FILTER_FUNCTION) अणु
			old_hash = rcu_dereference_रक्षित(ftrace_graph_hash,
					lockdep_is_held(&graph_lock));
			rcu_assign_poपूर्णांकer(ftrace_graph_hash, new_hash);
		पूर्ण अन्यथा अणु
			old_hash = rcu_dereference_रक्षित(ftrace_graph_notrace_hash,
					lockdep_is_held(&graph_lock));
			rcu_assign_poपूर्णांकer(ftrace_graph_notrace_hash, new_hash);
		पूर्ण

		mutex_unlock(&graph_lock);

		/*
		 * We need to करो a hard क्रमce of sched synchronization.
		 * This is because we use preempt_disable() to करो RCU, but
		 * the function tracers can be called where RCU is not watching
		 * (like beक्रमe user_निकास()). We can not rely on the RCU
		 * infraकाष्ठाure to करो the synchronization, thus we must करो it
		 * ourselves.
		 */
		synchronize_rcu_tasks_rude();

		मुक्त_ftrace_hash(old_hash);
	पूर्ण

 out:
	मुक्त_ftrace_hash(fgd->new_hash);
	kमुक्त(fgd);

	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_graph_set_hash(काष्ठा ftrace_hash *hash, अक्षर *buffer)
अणु
	काष्ठा ftrace_glob func_g;
	काष्ठा dyn_ftrace *rec;
	काष्ठा ftrace_page *pg;
	काष्ठा ftrace_func_entry *entry;
	पूर्णांक fail = 1;
	पूर्णांक not;

	/* decode regex */
	func_g.type = filter_parse_regex(buffer, म_माप(buffer),
					 &func_g.search, &not);

	func_g.len = म_माप(func_g.search);

	mutex_lock(&ftrace_lock);

	अगर (unlikely(ftrace_disabled)) अणु
		mutex_unlock(&ftrace_lock);
		वापस -ENODEV;
	पूर्ण

	करो_क्रम_each_ftrace_rec(pg, rec) अणु

		अगर (rec->flags & FTRACE_FL_DISABLED)
			जारी;

		अगर (ftrace_match_record(rec, &func_g, शून्य, 0)) अणु
			entry = ftrace_lookup_ip(hash, rec->ip);

			अगर (!not) अणु
				fail = 0;

				अगर (entry)
					जारी;
				अगर (add_hash_entry(hash, rec->ip) < 0)
					जाओ out;
			पूर्ण अन्यथा अणु
				अगर (entry) अणु
					मुक्त_hash_entry(hash, entry);
					fail = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_rec();
out:
	mutex_unlock(&ftrace_lock);

	अगर (fail)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
ftrace_graph_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
		   माप_प्रकार cnt, loff_t *ppos)
अणु
	sमाप_प्रकार पढ़ो, ret = 0;
	काष्ठा ftrace_graph_data *fgd = file->निजी_data;
	काष्ठा trace_parser *parser;

	अगर (!cnt)
		वापस 0;

	/* Read mode uses seq functions */
	अगर (file->f_mode & FMODE_READ) अणु
		काष्ठा seq_file *m = file->निजी_data;
		fgd = m->निजी;
	पूर्ण

	parser = &fgd->parser;

	पढ़ो = trace_get_user(parser, ubuf, cnt, ppos);

	अगर (पढ़ो >= 0 && trace_parser_loaded(parser) &&
	    !trace_parser_cont(parser)) अणु

		ret = ftrace_graph_set_hash(fgd->new_hash,
					    parser->buffer);
		trace_parser_clear(parser);
	पूर्ण

	अगर (!ret)
		ret = पढ़ो;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations ftrace_graph_fops = अणु
	.खोलो		= ftrace_graph_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= ftrace_graph_ग_लिखो,
	.llseek		= tracing_lseek,
	.release	= ftrace_graph_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_graph_notrace_fops = अणु
	.खोलो		= ftrace_graph_notrace_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= ftrace_graph_ग_लिखो,
	.llseek		= tracing_lseek,
	.release	= ftrace_graph_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

व्योम ftrace_create_filter_files(काष्ठा ftrace_ops *ops,
				काष्ठा dentry *parent)
अणु

	trace_create_file("set_ftrace_filter", 0644, parent,
			  ops, &ftrace_filter_fops);

	trace_create_file("set_ftrace_notrace", 0644, parent,
			  ops, &ftrace_notrace_fops);
पूर्ण

/*
 * The name "destroy_filter_files" is really a misnomer. Although
 * in the future, it may actually delete the files, but this is
 * really पूर्णांकended to make sure the ops passed in are disabled
 * and that when this function वापसs, the caller is मुक्त to
 * मुक्त the ops.
 *
 * The "destroy" name is only to match the "create" name that this
 * should be paired with.
 */
व्योम ftrace_destroy_filter_files(काष्ठा ftrace_ops *ops)
अणु
	mutex_lock(&ftrace_lock);
	अगर (ops->flags & FTRACE_OPS_FL_ENABLED)
		ftrace_shutकरोwn(ops, 0);
	ops->flags |= FTRACE_OPS_FL_DELETED;
	ftrace_मुक्त_filter(ops);
	mutex_unlock(&ftrace_lock);
पूर्ण

अटल __init पूर्णांक ftrace_init_dyn_tracefs(काष्ठा dentry *d_tracer)
अणु

	trace_create_file("available_filter_functions", 0444,
			d_tracer, शून्य, &ftrace_avail_fops);

	trace_create_file("enabled_functions", 0444,
			d_tracer, शून्य, &ftrace_enabled_fops);

	ftrace_create_filter_files(&global_ops, d_tracer);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	trace_create_file("set_graph_function", 0644, d_tracer,
				    शून्य,
				    &ftrace_graph_fops);
	trace_create_file("set_graph_notrace", 0644, d_tracer,
				    शून्य,
				    &ftrace_graph_notrace_fops);
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_cmp_ips(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर अचिन्हित दीर्घ *ipa = a;
	स्थिर अचिन्हित दीर्घ *ipb = b;

	अगर (*ipa > *ipb)
		वापस 1;
	अगर (*ipa < *ipb)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_process_locs(काष्ठा module *mod,
			       अचिन्हित दीर्घ *start,
			       अचिन्हित दीर्घ *end)
अणु
	काष्ठा ftrace_page *start_pg;
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec;
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ *p;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ flags = 0; /* Shut up gcc */
	पूर्णांक ret = -ENOMEM;

	count = end - start;

	अगर (!count)
		वापस 0;

	sort(start, count, माप(*start),
	     ftrace_cmp_ips, शून्य);

	start_pg = ftrace_allocate_pages(count);
	अगर (!start_pg)
		वापस -ENOMEM;

	mutex_lock(&ftrace_lock);

	/*
	 * Core and each module needs their own pages, as
	 * modules will मुक्त them when they are हटाओd.
	 * Force a new page to be allocated क्रम modules.
	 */
	अगर (!mod) अणु
		WARN_ON(ftrace_pages || ftrace_pages_start);
		/* First initialization */
		ftrace_pages = ftrace_pages_start = start_pg;
	पूर्ण अन्यथा अणु
		अगर (!ftrace_pages)
			जाओ out;

		अगर (WARN_ON(ftrace_pages->next)) अणु
			/* Hmm, we have मुक्त pages? */
			जबतक (ftrace_pages->next)
				ftrace_pages = ftrace_pages->next;
		पूर्ण

		ftrace_pages->next = start_pg;
	पूर्ण

	p = start;
	pg = start_pg;
	जबतक (p < end) अणु
		अचिन्हित दीर्घ end_offset;
		addr = ftrace_call_adjust(*p++);
		/*
		 * Some architecture linkers will pad between
		 * the dअगरferent mcount_loc sections of dअगरferent
		 * object files to satisfy alignments.
		 * Skip any शून्य poपूर्णांकers.
		 */
		अगर (!addr)
			जारी;

		end_offset = (pg->index+1) * माप(pg->records[0]);
		अगर (end_offset > PAGE_SIZE << pg->order) अणु
			/* We should have allocated enough */
			अगर (WARN_ON(!pg->next))
				अवरोध;
			pg = pg->next;
		पूर्ण

		rec = &pg->records[pg->index++];
		rec->ip = addr;
	पूर्ण

	/* We should have used all pages */
	WARN_ON(pg->next);

	/* Assign the last page to ftrace_pages */
	ftrace_pages = pg;

	/*
	 * We only need to disable पूर्णांकerrupts on start up
	 * because we are modअगरying code that an पूर्णांकerrupt
	 * may execute, and the modअगरication is not atomic.
	 * But क्रम modules, nothing runs the code we modअगरy
	 * until we are finished with it, and there's no
	 * reason to cause large पूर्णांकerrupt latencies जबतक we करो it.
	 */
	अगर (!mod)
		local_irq_save(flags);
	ftrace_update_code(mod, start_pg);
	अगर (!mod)
		local_irq_restore(flags);
	ret = 0;
 out:
	mutex_unlock(&ftrace_lock);

	वापस ret;
पूर्ण

काष्ठा ftrace_mod_func अणु
	काष्ठा list_head	list;
	अक्षर			*name;
	अचिन्हित दीर्घ		ip;
	अचिन्हित पूर्णांक		size;
पूर्ण;

काष्ठा ftrace_mod_map अणु
	काष्ठा rcu_head		rcu;
	काष्ठा list_head	list;
	काष्ठा module		*mod;
	अचिन्हित दीर्घ		start_addr;
	अचिन्हित दीर्घ		end_addr;
	काष्ठा list_head	funcs;
	अचिन्हित पूर्णांक		num_funcs;
पूर्ण;

अटल पूर्णांक ftrace_get_trampoline_kallsym(अचिन्हित पूर्णांक symnum,
					 अचिन्हित दीर्घ *value, अक्षर *type,
					 अक्षर *name, अक्षर *module_name,
					 पूर्णांक *exported)
अणु
	काष्ठा ftrace_ops *op;

	list_क्रम_each_entry_rcu(op, &ftrace_ops_trampoline_list, list) अणु
		अगर (!op->trampoline || symnum--)
			जारी;
		*value = op->trampoline;
		*type = 't';
		strlcpy(name, FTRACE_TRAMPOLINE_SYM, KSYM_NAME_LEN);
		strlcpy(module_name, FTRACE_TRAMPOLINE_MOD, MODULE_NAME_LEN);
		*exported = 0;
		वापस 0;
	पूर्ण

	वापस -दुस्फल;
पूर्ण

#अगर_घोषित CONFIG_MODULES

#घोषणा next_to_ftrace_page(p) container_of(p, काष्ठा ftrace_page, next)

अटल LIST_HEAD(ftrace_mod_maps);

अटल पूर्णांक referenced_filters(काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_ops *ops;
	पूर्णांक cnt = 0;

	क्रम (ops = ftrace_ops_list; ops != &ftrace_list_end; ops = ops->next) अणु
		अगर (ops_references_rec(ops, rec)) अणु
			अगर (WARN_ON_ONCE(ops->flags & FTRACE_OPS_FL_सूचीECT))
				जारी;
			अगर (WARN_ON_ONCE(ops->flags & FTRACE_OPS_FL_IPMODIFY))
				जारी;
			cnt++;
			अगर (ops->flags & FTRACE_OPS_FL_SAVE_REGS)
				rec->flags |= FTRACE_FL_REGS;
			अगर (cnt == 1 && ops->trampoline)
				rec->flags |= FTRACE_FL_TRAMP;
			अन्यथा
				rec->flags &= ~FTRACE_FL_TRAMP;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम
clear_mod_from_hash(काष्ठा ftrace_page *pg, काष्ठा ftrace_hash *hash)
अणु
	काष्ठा ftrace_func_entry *entry;
	काष्ठा dyn_ftrace *rec;
	पूर्णांक i;

	अगर (ftrace_hash_empty(hash))
		वापस;

	क्रम (i = 0; i < pg->index; i++) अणु
		rec = &pg->records[i];
		entry = __ftrace_lookup_ip(hash, rec->ip);
		/*
		 * Do not allow this rec to match again.
		 * Yeah, it may waste some memory, but will be हटाओd
		 * अगर/when the hash is modअगरied again.
		 */
		अगर (entry)
			entry->ip = 0;
	पूर्ण
पूर्ण

/* Clear any records from hashes */
अटल व्योम clear_mod_from_hashes(काष्ठा ftrace_page *pg)
अणु
	काष्ठा trace_array *tr;

	mutex_lock(&trace_types_lock);
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (!tr->ops || !tr->ops->func_hash)
			जारी;
		mutex_lock(&tr->ops->func_hash->regex_lock);
		clear_mod_from_hash(pg, tr->ops->func_hash->filter_hash);
		clear_mod_from_hash(pg, tr->ops->func_hash->notrace_hash);
		mutex_unlock(&tr->ops->func_hash->regex_lock);
	पूर्ण
	mutex_unlock(&trace_types_lock);
पूर्ण

अटल व्योम ftrace_मुक्त_mod_map(काष्ठा rcu_head *rcu)
अणु
	काष्ठा ftrace_mod_map *mod_map = container_of(rcu, काष्ठा ftrace_mod_map, rcu);
	काष्ठा ftrace_mod_func *mod_func;
	काष्ठा ftrace_mod_func *n;

	/* All the contents of mod_map are now not visible to पढ़ोers */
	list_क्रम_each_entry_safe(mod_func, n, &mod_map->funcs, list) अणु
		kमुक्त(mod_func->name);
		list_del(&mod_func->list);
		kमुक्त(mod_func);
	पूर्ण

	kमुक्त(mod_map);
पूर्ण

व्योम ftrace_release_mod(काष्ठा module *mod)
अणु
	काष्ठा ftrace_mod_map *mod_map;
	काष्ठा ftrace_mod_map *n;
	काष्ठा dyn_ftrace *rec;
	काष्ठा ftrace_page **last_pg;
	काष्ठा ftrace_page *पंचांगp_page = शून्य;
	काष्ठा ftrace_page *pg;

	mutex_lock(&ftrace_lock);

	अगर (ftrace_disabled)
		जाओ out_unlock;

	list_क्रम_each_entry_safe(mod_map, n, &ftrace_mod_maps, list) अणु
		अगर (mod_map->mod == mod) अणु
			list_del_rcu(&mod_map->list);
			call_rcu(&mod_map->rcu, ftrace_मुक्त_mod_map);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Each module has its own ftrace_pages, हटाओ
	 * them from the list.
	 */
	last_pg = &ftrace_pages_start;
	क्रम (pg = ftrace_pages_start; pg; pg = *last_pg) अणु
		rec = &pg->records[0];
		अगर (within_module_core(rec->ip, mod) ||
		    within_module_init(rec->ip, mod)) अणु
			/*
			 * As core pages are first, the first
			 * page should never be a module page.
			 */
			अगर (WARN_ON(pg == ftrace_pages_start))
				जाओ out_unlock;

			/* Check अगर we are deleting the last page */
			अगर (pg == ftrace_pages)
				ftrace_pages = next_to_ftrace_page(last_pg);

			ftrace_update_tot_cnt -= pg->index;
			*last_pg = pg->next;

			pg->next = पंचांगp_page;
			पंचांगp_page = pg;
		पूर्ण अन्यथा
			last_pg = &pg->next;
	पूर्ण
 out_unlock:
	mutex_unlock(&ftrace_lock);

	क्रम (pg = पंचांगp_page; pg; pg = पंचांगp_page) अणु

		/* Needs to be called outside of ftrace_lock */
		clear_mod_from_hashes(pg);

		अगर (pg->records) अणु
			मुक्त_pages((अचिन्हित दीर्घ)pg->records, pg->order);
			ftrace_number_of_pages -= 1 << pg->order;
		पूर्ण
		पंचांगp_page = pg->next;
		kमुक्त(pg);
		ftrace_number_of_groups--;
	पूर्ण
पूर्ण

व्योम ftrace_module_enable(काष्ठा module *mod)
अणु
	काष्ठा dyn_ftrace *rec;
	काष्ठा ftrace_page *pg;

	mutex_lock(&ftrace_lock);

	अगर (ftrace_disabled)
		जाओ out_unlock;

	/*
	 * If the tracing is enabled, go ahead and enable the record.
	 *
	 * The reason not to enable the record immediately is the
	 * inherent check of ftrace_make_nop/ftrace_make_call क्रम
	 * correct previous inकाष्ठाions.  Making first the NOP
	 * conversion माला_दो the module to the correct state, thus
	 * passing the ftrace_make_call check.
	 *
	 * We also delay this to after the module code alपढ़ोy set the
	 * text to पढ़ो-only, as we now need to set it back to पढ़ो-ग_लिखो
	 * so that we can modअगरy the text.
	 */
	अगर (ftrace_start_up)
		ftrace_arch_code_modअगरy_prepare();

	करो_क्रम_each_ftrace_rec(pg, rec) अणु
		पूर्णांक cnt;
		/*
		 * करो_क्रम_each_ftrace_rec() is a द्विगुन loop.
		 * module text shares the pg. If a record is
		 * not part of this module, then skip this pg,
		 * which the "break" will करो.
		 */
		अगर (!within_module_core(rec->ip, mod) &&
		    !within_module_init(rec->ip, mod))
			अवरोध;

		cnt = 0;

		/*
		 * When adding a module, we need to check अगर tracers are
		 * currently enabled and अगर they are, and can trace this record,
		 * we need to enable the module functions as well as update the
		 * reference counts क्रम those function records.
		 */
		अगर (ftrace_start_up)
			cnt += referenced_filters(rec);

		rec->flags &= ~FTRACE_FL_DISABLED;
		rec->flags += cnt;

		अगर (ftrace_start_up && cnt) अणु
			पूर्णांक failed = __ftrace_replace_code(rec, 1);
			अगर (failed) अणु
				ftrace_bug(failed, rec);
				जाओ out_loop;
			पूर्ण
		पूर्ण

	पूर्ण जबतक_क्रम_each_ftrace_rec();

 out_loop:
	अगर (ftrace_start_up)
		ftrace_arch_code_modअगरy_post_process();

 out_unlock:
	mutex_unlock(&ftrace_lock);

	process_cached_mods(mod->name);
पूर्ण

व्योम ftrace_module_init(काष्ठा module *mod)
अणु
	अगर (ftrace_disabled || !mod->num_ftrace_callsites)
		वापस;

	ftrace_process_locs(mod, mod->ftrace_callsites,
			    mod->ftrace_callsites + mod->num_ftrace_callsites);
पूर्ण

अटल व्योम save_ftrace_mod_rec(काष्ठा ftrace_mod_map *mod_map,
				काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_mod_func *mod_func;
	अचिन्हित दीर्घ symsize;
	अचिन्हित दीर्घ offset;
	अक्षर str[KSYM_SYMBOL_LEN];
	अक्षर *modname;
	स्थिर अक्षर *ret;

	ret = kallsyms_lookup(rec->ip, &symsize, &offset, &modname, str);
	अगर (!ret)
		वापस;

	mod_func = kदो_स्मृति(माप(*mod_func), GFP_KERNEL);
	अगर (!mod_func)
		वापस;

	mod_func->name = kstrdup(str, GFP_KERNEL);
	अगर (!mod_func->name) अणु
		kमुक्त(mod_func);
		वापस;
	पूर्ण

	mod_func->ip = rec->ip - offset;
	mod_func->size = symsize;

	mod_map->num_funcs++;

	list_add_rcu(&mod_func->list, &mod_map->funcs);
पूर्ण

अटल काष्ठा ftrace_mod_map *
allocate_ftrace_mod_map(काष्ठा module *mod,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा ftrace_mod_map *mod_map;

	mod_map = kदो_स्मृति(माप(*mod_map), GFP_KERNEL);
	अगर (!mod_map)
		वापस शून्य;

	mod_map->mod = mod;
	mod_map->start_addr = start;
	mod_map->end_addr = end;
	mod_map->num_funcs = 0;

	INIT_LIST_HEAD_RCU(&mod_map->funcs);

	list_add_rcu(&mod_map->list, &ftrace_mod_maps);

	वापस mod_map;
पूर्ण

अटल स्थिर अक्षर *
ftrace_func_address_lookup(काष्ठा ftrace_mod_map *mod_map,
			   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
			   अचिन्हित दीर्घ *off, अक्षर *sym)
अणु
	काष्ठा ftrace_mod_func *found_func =  शून्य;
	काष्ठा ftrace_mod_func *mod_func;

	list_क्रम_each_entry_rcu(mod_func, &mod_map->funcs, list) अणु
		अगर (addr >= mod_func->ip &&
		    addr < mod_func->ip + mod_func->size) अणु
			found_func = mod_func;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found_func) अणु
		अगर (size)
			*size = found_func->size;
		अगर (off)
			*off = addr - found_func->ip;
		अगर (sym)
			strlcpy(sym, found_func->name, KSYM_NAME_LEN);

		वापस found_func->name;
	पूर्ण

	वापस शून्य;
पूर्ण

स्थिर अक्षर *
ftrace_mod_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
		   अचिन्हित दीर्घ *off, अक्षर **modname, अक्षर *sym)
अणु
	काष्ठा ftrace_mod_map *mod_map;
	स्थिर अक्षर *ret = शून्य;

	/* mod_map is मुक्तd via call_rcu() */
	preempt_disable();
	list_क्रम_each_entry_rcu(mod_map, &ftrace_mod_maps, list) अणु
		ret = ftrace_func_address_lookup(mod_map, addr, size, off, sym);
		अगर (ret) अणु
			अगर (modname)
				*modname = mod_map->mod->name;
			अवरोध;
		पूर्ण
	पूर्ण
	preempt_enable();

	वापस ret;
पूर्ण

पूर्णांक ftrace_mod_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
			   अक्षर *type, अक्षर *name,
			   अक्षर *module_name, पूर्णांक *exported)
अणु
	काष्ठा ftrace_mod_map *mod_map;
	काष्ठा ftrace_mod_func *mod_func;
	पूर्णांक ret;

	preempt_disable();
	list_क्रम_each_entry_rcu(mod_map, &ftrace_mod_maps, list) अणु

		अगर (symnum >= mod_map->num_funcs) अणु
			symnum -= mod_map->num_funcs;
			जारी;
		पूर्ण

		list_क्रम_each_entry_rcu(mod_func, &mod_map->funcs, list) अणु
			अगर (symnum > 1) अणु
				symnum--;
				जारी;
			पूर्ण

			*value = mod_func->ip;
			*type = 'T';
			strlcpy(name, mod_func->name, KSYM_NAME_LEN);
			strlcpy(module_name, mod_map->mod->name, MODULE_NAME_LEN);
			*exported = 1;
			preempt_enable();
			वापस 0;
		पूर्ण
		WARN_ON(1);
		अवरोध;
	पूर्ण
	ret = ftrace_get_trampoline_kallsym(symnum, value, type, name,
					    module_name, exported);
	preempt_enable();
	वापस ret;
पूर्ण

#अन्यथा
अटल व्योम save_ftrace_mod_rec(काष्ठा ftrace_mod_map *mod_map,
				काष्ठा dyn_ftrace *rec) अणु पूर्ण
अटल अंतरभूत काष्ठा ftrace_mod_map *
allocate_ftrace_mod_map(काष्ठा module *mod,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस शून्य;
पूर्ण
पूर्णांक ftrace_mod_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
			   अक्षर *type, अक्षर *name, अक्षर *module_name,
			   पूर्णांक *exported)
अणु
	पूर्णांक ret;

	preempt_disable();
	ret = ftrace_get_trampoline_kallsym(symnum, value, type, name,
					    module_name, exported);
	preempt_enable();
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

काष्ठा ftrace_init_func अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ ip;
पूर्ण;

/* Clear any init ips from hashes */
अटल व्योम
clear_func_from_hash(काष्ठा ftrace_init_func *func, काष्ठा ftrace_hash *hash)
अणु
	काष्ठा ftrace_func_entry *entry;

	entry = ftrace_lookup_ip(hash, func->ip);
	/*
	 * Do not allow this rec to match again.
	 * Yeah, it may waste some memory, but will be हटाओd
	 * अगर/when the hash is modअगरied again.
	 */
	अगर (entry)
		entry->ip = 0;
पूर्ण

अटल व्योम
clear_func_from_hashes(काष्ठा ftrace_init_func *func)
अणु
	काष्ठा trace_array *tr;

	mutex_lock(&trace_types_lock);
	list_क्रम_each_entry(tr, &ftrace_trace_arrays, list) अणु
		अगर (!tr->ops || !tr->ops->func_hash)
			जारी;
		mutex_lock(&tr->ops->func_hash->regex_lock);
		clear_func_from_hash(func, tr->ops->func_hash->filter_hash);
		clear_func_from_hash(func, tr->ops->func_hash->notrace_hash);
		mutex_unlock(&tr->ops->func_hash->regex_lock);
	पूर्ण
	mutex_unlock(&trace_types_lock);
पूर्ण

अटल व्योम add_to_clear_hash_list(काष्ठा list_head *clear_list,
				   काष्ठा dyn_ftrace *rec)
अणु
	काष्ठा ftrace_init_func *func;

	func = kदो_स्मृति(माप(*func), GFP_KERNEL);
	अगर (!func) अणु
		MEM_FAIL(1, "alloc failure, ftrace filter could be stale\n");
		वापस;
	पूर्ण

	func->ip = rec->ip;
	list_add(&func->list, clear_list);
पूर्ण

व्योम ftrace_मुक्त_mem(काष्ठा module *mod, व्योम *start_ptr, व्योम *end_ptr)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)(start_ptr);
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)(end_ptr);
	काष्ठा ftrace_page **last_pg = &ftrace_pages_start;
	काष्ठा ftrace_page *pg;
	काष्ठा dyn_ftrace *rec;
	काष्ठा dyn_ftrace key;
	काष्ठा ftrace_mod_map *mod_map = शून्य;
	काष्ठा ftrace_init_func *func, *func_next;
	काष्ठा list_head clear_hash;

	INIT_LIST_HEAD(&clear_hash);

	key.ip = start;
	key.flags = end;	/* overload flags, as it is अचिन्हित दीर्घ */

	mutex_lock(&ftrace_lock);

	/*
	 * If we are मुक्तing module init memory, then check अगर
	 * any tracer is active. If so, we need to save a mapping of
	 * the module functions being मुक्तd with the address.
	 */
	अगर (mod && ftrace_ops_list != &ftrace_list_end)
		mod_map = allocate_ftrace_mod_map(mod, start, end);

	क्रम (pg = ftrace_pages_start; pg; last_pg = &pg->next, pg = *last_pg) अणु
		अगर (end < pg->records[0].ip ||
		    start >= (pg->records[pg->index - 1].ip + MCOUNT_INSN_SIZE))
			जारी;
 again:
		rec = द्वा_खोज(&key, pg->records, pg->index,
			      माप(काष्ठा dyn_ftrace),
			      ftrace_cmp_recs);
		अगर (!rec)
			जारी;

		/* rec will be cleared from hashes after ftrace_lock unlock */
		add_to_clear_hash_list(&clear_hash, rec);

		अगर (mod_map)
			save_ftrace_mod_rec(mod_map, rec);

		pg->index--;
		ftrace_update_tot_cnt--;
		अगर (!pg->index) अणु
			*last_pg = pg->next;
			अगर (pg->records) अणु
				मुक्त_pages((अचिन्हित दीर्घ)pg->records, pg->order);
				ftrace_number_of_pages -= 1 << pg->order;
			पूर्ण
			ftrace_number_of_groups--;
			kमुक्त(pg);
			pg = container_of(last_pg, काष्ठा ftrace_page, next);
			अगर (!(*last_pg))
				ftrace_pages = pg;
			जारी;
		पूर्ण
		स_हटाओ(rec, rec + 1,
			(pg->index - (rec - pg->records)) * माप(*rec));
		/* More than one function may be in this block */
		जाओ again;
	पूर्ण
	mutex_unlock(&ftrace_lock);

	list_क्रम_each_entry_safe(func, func_next, &clear_hash, list) अणु
		clear_func_from_hashes(func);
		kमुक्त(func);
	पूर्ण
पूर्ण

व्योम __init ftrace_मुक्त_init_mem(व्योम)
अणु
	व्योम *start = (व्योम *)(&__init_begin);
	व्योम *end = (व्योम *)(&__init_end);

	ftrace_मुक्त_mem(शून्य, start, end);
पूर्ण

व्योम __init ftrace_init(व्योम)
अणु
	बाह्य अचिन्हित दीर्घ __start_mcount_loc[];
	बाह्य अचिन्हित दीर्घ __stop_mcount_loc[];
	अचिन्हित दीर्घ count, flags;
	पूर्णांक ret;

	local_irq_save(flags);
	ret = ftrace_dyn_arch_init();
	local_irq_restore(flags);
	अगर (ret)
		जाओ failed;

	count = __stop_mcount_loc - __start_mcount_loc;
	अगर (!count) अणु
		pr_info("ftrace: No functions to be traced?\n");
		जाओ failed;
	पूर्ण

	pr_info("ftrace: allocating %ld entries in %ld pages\n",
		count, count / ENTRIES_PER_PAGE + 1);

	last_ftrace_enabled = ftrace_enabled = 1;

	ret = ftrace_process_locs(शून्य,
				  __start_mcount_loc,
				  __stop_mcount_loc);

	pr_info("ftrace: allocated %ld pages with %ld groups\n",
		ftrace_number_of_pages, ftrace_number_of_groups);

	set_ftrace_early_filters();

	वापस;
 failed:
	ftrace_disabled = 1;
पूर्ण

/* Do nothing अगर arch करोes not support this */
व्योम __weak arch_ftrace_update_trampoline(काष्ठा ftrace_ops *ops)
अणु
पूर्ण

अटल व्योम ftrace_update_trampoline(काष्ठा ftrace_ops *ops)
अणु
	अचिन्हित दीर्घ trampoline = ops->trampoline;

	arch_ftrace_update_trampoline(ops);
	अगर (ops->trampoline && ops->trampoline != trampoline &&
	    (ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP)) अणु
		/* Add to kallsyms beक्रमe the perf events */
		ftrace_add_trampoline_to_kallsyms(ops);
		perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_OOL,
				   ops->trampoline, ops->trampoline_size, false,
				   FTRACE_TRAMPOLINE_SYM);
		/*
		 * Record the perf text poke event after the ksymbol रेजिस्टर
		 * event.
		 */
		perf_event_text_poke((व्योम *)ops->trampoline, शून्य, 0,
				     (व्योम *)ops->trampoline,
				     ops->trampoline_size);
	पूर्ण
पूर्ण

व्योम ftrace_init_trace_array(काष्ठा trace_array *tr)
अणु
	INIT_LIST_HEAD(&tr->func_probes);
	INIT_LIST_HEAD(&tr->mod_trace);
	INIT_LIST_HEAD(&tr->mod_notrace);
पूर्ण
#अन्यथा

काष्ठा ftrace_ops global_ops = अणु
	.func			= ftrace_stub,
	.flags			= FTRACE_OPS_FL_INITIALIZED |
				  FTRACE_OPS_FL_PID,
पूर्ण;

अटल पूर्णांक __init ftrace_nodyn_init(व्योम)
अणु
	ftrace_enabled = 1;
	वापस 0;
पूर्ण
core_initcall(ftrace_nodyn_init);

अटल अंतरभूत पूर्णांक ftrace_init_dyn_tracefs(काष्ठा dentry *d_tracer) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ftrace_startup_enable(पूर्णांक command) अणु पूर्ण
अटल अंतरभूत व्योम ftrace_startup_all(पूर्णांक command) अणु पूर्ण

# define ftrace_startup_sysctl()	करो अणु पूर्ण जबतक (0)
# define ftrace_shutकरोwn_sysctl()	करो अणु पूर्ण जबतक (0)

अटल व्योम ftrace_update_trampoline(काष्ठा ftrace_ops *ops)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

__init व्योम ftrace_init_global_array_ops(काष्ठा trace_array *tr)
अणु
	tr->ops = &global_ops;
	tr->ops->निजी = tr;
	ftrace_init_trace_array(tr);
पूर्ण

व्योम ftrace_init_array_ops(काष्ठा trace_array *tr, ftrace_func_t func)
अणु
	/* If we filter on pids, update to use the pid function */
	अगर (tr->flags & TRACE_ARRAY_FL_GLOBAL) अणु
		अगर (WARN_ON(tr->ops->func != ftrace_stub))
			prपूर्णांकk("ftrace ops had %pS for function\n",
			       tr->ops->func);
	पूर्ण
	tr->ops->func = func;
	tr->ops->निजी = tr;
पूर्ण

व्योम ftrace_reset_array_ops(काष्ठा trace_array *tr)
अणु
	tr->ops->func = ftrace_stub;
पूर्ण

अटल nokprobe_अंतरभूत व्योम
__ftrace_ops_list_func(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
		       काष्ठा ftrace_ops *ignored, काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा pt_regs *regs = ftrace_get_regs(fregs);
	काष्ठा ftrace_ops *op;
	पूर्णांक bit;

	bit = trace_test_and_set_recursion(ip, parent_ip, TRACE_LIST_START, TRACE_LIST_MAX);
	अगर (bit < 0)
		वापस;

	/*
	 * Some of the ops may be dynamically allocated,
	 * they must be मुक्तd after a synchronize_rcu().
	 */
	preempt_disable_notrace();

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		/* Stub functions करोn't need to be called nor tested */
		अगर (op->flags & FTRACE_OPS_FL_STUB)
			जारी;
		/*
		 * Check the following क्रम each ops beक्रमe calling their func:
		 *  अगर RCU flag is set, then rcu_is_watching() must be true
		 *  अगर PER_CPU is set, then ftrace_function_local_disable()
		 *                          must be false
		 *  Otherwise test अगर the ip matches the ops filter
		 *
		 * If any of the above fails then the op->func() is not executed.
		 */
		अगर ((!(op->flags & FTRACE_OPS_FL_RCU) || rcu_is_watching()) &&
		    ftrace_ops_test(op, ip, regs)) अणु
			अगर (FTRACE_WARN_ON(!op->func)) अणु
				pr_warn("op=%p %pS\n", op, op);
				जाओ out;
			पूर्ण
			op->func(ip, parent_ip, op, fregs);
		पूर्ण
	पूर्ण जबतक_क्रम_each_ftrace_op(op);
out:
	preempt_enable_notrace();
	trace_clear_recursion(bit);
पूर्ण

/*
 * Some archs only support passing ip and parent_ip. Even though
 * the list function ignores the op parameter, we करो not want any
 * C side effects, where a function is called without the caller
 * sending a third parameter.
 * Archs are to support both the regs and ftrace_ops at the same समय.
 * If they support ftrace_ops, it is assumed they support regs.
 * If call backs want to use regs, they must either check क्रम regs
 * being शून्य, or CONFIG_DYNAMIC_FTRACE_WITH_REGS.
 * Note, CONFIG_DYNAMIC_FTRACE_WITH_REGS expects a full regs to be saved.
 * An architecture can pass partial regs with ftrace_ops and still
 * set the ARCH_SUPPORTS_FTRACE_OPS.
 */
#अगर ARCH_SUPPORTS_FTRACE_OPS
अटल व्योम ftrace_ops_list_func(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				 काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	__ftrace_ops_list_func(ip, parent_ip, शून्य, fregs);
पूर्ण
NOKPROBE_SYMBOL(ftrace_ops_list_func);
#अन्यथा
अटल व्योम ftrace_ops_no_ops(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip)
अणु
	__ftrace_ops_list_func(ip, parent_ip, शून्य, शून्य);
पूर्ण
NOKPROBE_SYMBOL(ftrace_ops_no_ops);
#पूर्ण_अगर

/*
 * If there's only one function रेजिस्टरed but it करोes not support
 * recursion, needs RCU protection and/or requires per cpu handling, then
 * this function will be called by the mcount trampoline.
 */
अटल व्योम ftrace_ops_assist_func(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				   काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	पूर्णांक bit;

	bit = trace_test_and_set_recursion(ip, parent_ip, TRACE_LIST_START, TRACE_LIST_MAX);
	अगर (bit < 0)
		वापस;

	preempt_disable_notrace();

	अगर (!(op->flags & FTRACE_OPS_FL_RCU) || rcu_is_watching())
		op->func(ip, parent_ip, op, fregs);

	preempt_enable_notrace();
	trace_clear_recursion(bit);
पूर्ण
NOKPROBE_SYMBOL(ftrace_ops_assist_func);

/**
 * ftrace_ops_get_func - get the function a trampoline should call
 * @ops: the ops to get the function क्रम
 *
 * Normally the mcount trampoline will call the ops->func, but there
 * are बार that it should not. For example, अगर the ops करोes not
 * have its own recursion protection, then it should call the
 * ftrace_ops_assist_func() instead.
 *
 * Returns the function that the trampoline should call क्रम @ops.
 */
ftrace_func_t ftrace_ops_get_func(काष्ठा ftrace_ops *ops)
अणु
	/*
	 * If the function करोes not handle recursion or needs to be RCU safe,
	 * then we need to call the assist handler.
	 */
	अगर (ops->flags & (FTRACE_OPS_FL_RECURSION |
			  FTRACE_OPS_FL_RCU))
		वापस ftrace_ops_assist_func;

	वापस ops->func;
पूर्ण

अटल व्योम
ftrace_filter_pid_sched_चयन_probe(व्योम *data, bool preempt,
		    काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_pid_list *no_pid_list;

	pid_list = rcu_dereference_sched(tr->function_pids);
	no_pid_list = rcu_dereference_sched(tr->function_no_pids);

	अगर (trace_ignore_this_task(pid_list, no_pid_list, next))
		this_cpu_ग_लिखो(tr->array_buffer.data->ftrace_ignore_pid,
			       FTRACE_PID_IGNORE);
	अन्यथा
		this_cpu_ग_लिखो(tr->array_buffer.data->ftrace_ignore_pid,
			       next->pid);
पूर्ण

अटल व्योम
ftrace_pid_follow_sched_process_विभाजन(व्योम *data,
				     काष्ठा task_काष्ठा *self,
				     काष्ठा task_काष्ठा *task)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = data;

	pid_list = rcu_dereference_sched(tr->function_pids);
	trace_filter_add_हटाओ_task(pid_list, self, task);

	pid_list = rcu_dereference_sched(tr->function_no_pids);
	trace_filter_add_हटाओ_task(pid_list, self, task);
पूर्ण

अटल व्योम
ftrace_pid_follow_sched_process_निकास(व्योम *data, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = data;

	pid_list = rcu_dereference_sched(tr->function_pids);
	trace_filter_add_हटाओ_task(pid_list, शून्य, task);

	pid_list = rcu_dereference_sched(tr->function_no_pids);
	trace_filter_add_हटाओ_task(pid_list, शून्य, task);
पूर्ण

व्योम ftrace_pid_follow_विभाजन(काष्ठा trace_array *tr, bool enable)
अणु
	अगर (enable) अणु
		रेजिस्टर_trace_sched_process_विभाजन(ftrace_pid_follow_sched_process_विभाजन,
						  tr);
		रेजिस्टर_trace_sched_process_मुक्त(ftrace_pid_follow_sched_process_निकास,
						  tr);
	पूर्ण अन्यथा अणु
		unरेजिस्टर_trace_sched_process_विभाजन(ftrace_pid_follow_sched_process_विभाजन,
						    tr);
		unरेजिस्टर_trace_sched_process_मुक्त(ftrace_pid_follow_sched_process_निकास,
						    tr);
	पूर्ण
पूर्ण

अटल व्योम clear_ftrace_pids(काष्ठा trace_array *tr, पूर्णांक type)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_pid_list *no_pid_list;
	पूर्णांक cpu;

	pid_list = rcu_dereference_रक्षित(tr->function_pids,
					     lockdep_is_held(&ftrace_lock));
	no_pid_list = rcu_dereference_रक्षित(tr->function_no_pids,
						lockdep_is_held(&ftrace_lock));

	/* Make sure there's something to करो */
	अगर (!pid_type_enabled(type, pid_list, no_pid_list))
		वापस;

	/* See अगर the pids still need to be checked after this */
	अगर (!still_need_pid_events(type, pid_list, no_pid_list)) अणु
		unरेजिस्टर_trace_sched_चयन(ftrace_filter_pid_sched_चयन_probe, tr);
		क्रम_each_possible_cpu(cpu)
			per_cpu_ptr(tr->array_buffer.data, cpu)->ftrace_ignore_pid = FTRACE_PID_TRACE;
	पूर्ण

	अगर (type & TRACE_PIDS)
		rcu_assign_poपूर्णांकer(tr->function_pids, शून्य);

	अगर (type & TRACE_NO_PIDS)
		rcu_assign_poपूर्णांकer(tr->function_no_pids, शून्य);

	/* Wait till all users are no दीर्घer using pid filtering */
	synchronize_rcu();

	अगर ((type & TRACE_PIDS) && pid_list)
		trace_मुक्त_pid_list(pid_list);

	अगर ((type & TRACE_NO_PIDS) && no_pid_list)
		trace_मुक्त_pid_list(no_pid_list);
पूर्ण

व्योम ftrace_clear_pids(काष्ठा trace_array *tr)
अणु
	mutex_lock(&ftrace_lock);

	clear_ftrace_pids(tr, TRACE_PIDS | TRACE_NO_PIDS);

	mutex_unlock(&ftrace_lock);
पूर्ण

अटल व्योम ftrace_pid_reset(काष्ठा trace_array *tr, पूर्णांक type)
अणु
	mutex_lock(&ftrace_lock);
	clear_ftrace_pids(tr, type);

	ftrace_update_pid_func();
	ftrace_startup_all(0);

	mutex_unlock(&ftrace_lock);
पूर्ण

/* Greater than any max PID */
#घोषणा FTRACE_NO_PIDS		(व्योम *)(PID_MAX_LIMIT + 1)

अटल व्योम *fpid_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = m->निजी;

	mutex_lock(&ftrace_lock);
	rcu_पढ़ो_lock_sched();

	pid_list = rcu_dereference_sched(tr->function_pids);

	अगर (!pid_list)
		वापस !(*pos) ? FTRACE_NO_PIDS : शून्य;

	वापस trace_pid_start(pid_list, pos);
पूर्ण

अटल व्योम *fpid_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा trace_pid_list *pid_list = rcu_dereference_sched(tr->function_pids);

	अगर (v == FTRACE_NO_PIDS) अणु
		(*pos)++;
		वापस शून्य;
	पूर्ण
	वापस trace_pid_next(pid_list, v, pos);
पूर्ण

अटल व्योम fpid_stop(काष्ठा seq_file *m, व्योम *p)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock_sched();
	mutex_unlock(&ftrace_lock);
पूर्ण

अटल पूर्णांक fpid_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (v == FTRACE_NO_PIDS) अणु
		seq_माला_दो(m, "no pid\n");
		वापस 0;
	पूर्ण

	वापस trace_pid_show(m, v);
पूर्ण

अटल स्थिर काष्ठा seq_operations ftrace_pid_sops = अणु
	.start = fpid_start,
	.next = fpid_next,
	.stop = fpid_stop,
	.show = fpid_show,
पूर्ण;

अटल व्योम *fnpid_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_array *tr = m->निजी;

	mutex_lock(&ftrace_lock);
	rcu_पढ़ो_lock_sched();

	pid_list = rcu_dereference_sched(tr->function_no_pids);

	अगर (!pid_list)
		वापस !(*pos) ? FTRACE_NO_PIDS : शून्य;

	वापस trace_pid_start(pid_list, pos);
पूर्ण

अटल व्योम *fnpid_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा trace_pid_list *pid_list = rcu_dereference_sched(tr->function_no_pids);

	अगर (v == FTRACE_NO_PIDS) अणु
		(*pos)++;
		वापस शून्य;
	पूर्ण
	वापस trace_pid_next(pid_list, v, pos);
पूर्ण

अटल स्थिर काष्ठा seq_operations ftrace_no_pid_sops = अणु
	.start = fnpid_start,
	.next = fnpid_next,
	.stop = fpid_stop,
	.show = fpid_show,
पूर्ण;

अटल पूर्णांक pid_खोलो(काष्ठा inode *inode, काष्ठा file *file, पूर्णांक type)
अणु
	स्थिर काष्ठा seq_operations *seq_ops;
	काष्ठा trace_array *tr = inode->i_निजी;
	काष्ठा seq_file *m;
	पूर्णांक ret = 0;

	ret = tracing_check_खोलो_get_tr(tr);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC))
		ftrace_pid_reset(tr, type);

	चयन (type) अणु
	हाल TRACE_PIDS:
		seq_ops = &ftrace_pid_sops;
		अवरोध;
	हाल TRACE_NO_PIDS:
		seq_ops = &ftrace_no_pid_sops;
		अवरोध;
	शेष:
		trace_array_put(tr);
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	ret = seq_खोलो(file, seq_ops);
	अगर (ret < 0) अणु
		trace_array_put(tr);
	पूर्ण अन्यथा अणु
		m = file->निजी_data;
		/* copy tr over to seq ops */
		m->निजी = tr;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
ftrace_pid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस pid_खोलो(inode, file, TRACE_PIDS);
पूर्ण

अटल पूर्णांक
ftrace_no_pid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस pid_खोलो(inode, file, TRACE_NO_PIDS);
पूर्ण

अटल व्योम ignore_task_cpu(व्योम *data)
अणु
	काष्ठा trace_array *tr = data;
	काष्ठा trace_pid_list *pid_list;
	काष्ठा trace_pid_list *no_pid_list;

	/*
	 * This function is called by on_each_cpu() जबतक the
	 * event_mutex is held.
	 */
	pid_list = rcu_dereference_रक्षित(tr->function_pids,
					     mutex_is_locked(&ftrace_lock));
	no_pid_list = rcu_dereference_रक्षित(tr->function_no_pids,
						mutex_is_locked(&ftrace_lock));

	अगर (trace_ignore_this_task(pid_list, no_pid_list, current))
		this_cpu_ग_लिखो(tr->array_buffer.data->ftrace_ignore_pid,
			       FTRACE_PID_IGNORE);
	अन्यथा
		this_cpu_ग_लिखो(tr->array_buffer.data->ftrace_ignore_pid,
			       current->pid);
पूर्ण

अटल sमाप_प्रकार
pid_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
	  माप_प्रकार cnt, loff_t *ppos, पूर्णांक type)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा trace_array *tr = m->निजी;
	काष्ठा trace_pid_list *filtered_pids;
	काष्ठा trace_pid_list *other_pids;
	काष्ठा trace_pid_list *pid_list;
	sमाप_प्रकार ret;

	अगर (!cnt)
		वापस 0;

	mutex_lock(&ftrace_lock);

	चयन (type) अणु
	हाल TRACE_PIDS:
		filtered_pids = rcu_dereference_रक्षित(tr->function_pids,
					     lockdep_is_held(&ftrace_lock));
		other_pids = rcu_dereference_रक्षित(tr->function_no_pids,
					     lockdep_is_held(&ftrace_lock));
		अवरोध;
	हाल TRACE_NO_PIDS:
		filtered_pids = rcu_dereference_रक्षित(tr->function_no_pids,
					     lockdep_is_held(&ftrace_lock));
		other_pids = rcu_dereference_रक्षित(tr->function_pids,
					     lockdep_is_held(&ftrace_lock));
		अवरोध;
	शेष:
		ret = -EINVAL;
		WARN_ON_ONCE(1);
		जाओ out;
	पूर्ण

	ret = trace_pid_ग_लिखो(filtered_pids, &pid_list, ubuf, cnt);
	अगर (ret < 0)
		जाओ out;

	चयन (type) अणु
	हाल TRACE_PIDS:
		rcu_assign_poपूर्णांकer(tr->function_pids, pid_list);
		अवरोध;
	हाल TRACE_NO_PIDS:
		rcu_assign_poपूर्णांकer(tr->function_no_pids, pid_list);
		अवरोध;
	पूर्ण


	अगर (filtered_pids) अणु
		synchronize_rcu();
		trace_मुक्त_pid_list(filtered_pids);
	पूर्ण अन्यथा अगर (pid_list && !other_pids) अणु
		/* Register a probe to set whether to ignore the tracing of a task */
		रेजिस्टर_trace_sched_चयन(ftrace_filter_pid_sched_चयन_probe, tr);
	पूर्ण

	/*
	 * Ignoring of pids is करोne at task चयन. But we have to
	 * check क्रम those tasks that are currently running.
	 * Always करो this in हाल a pid was appended or हटाओd.
	 */
	on_each_cpu(ignore_task_cpu, tr, 1);

	ftrace_update_pid_func();
	ftrace_startup_all(0);
 out:
	mutex_unlock(&ftrace_lock);

	अगर (ret > 0)
		*ppos += ret;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
ftrace_pid_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		 माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस pid_ग_लिखो(filp, ubuf, cnt, ppos, TRACE_PIDS);
पूर्ण

अटल sमाप_प्रकार
ftrace_no_pid_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		    माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस pid_ग_लिखो(filp, ubuf, cnt, ppos, TRACE_NO_PIDS);
पूर्ण

अटल पूर्णांक
ftrace_pid_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा trace_array *tr = inode->i_निजी;

	trace_array_put(tr);

	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations ftrace_pid_fops = अणु
	.खोलो		= ftrace_pid_खोलो,
	.ग_लिखो		= ftrace_pid_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= tracing_lseek,
	.release	= ftrace_pid_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations ftrace_no_pid_fops = अणु
	.खोलो		= ftrace_no_pid_खोलो,
	.ग_लिखो		= ftrace_no_pid_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= tracing_lseek,
	.release	= ftrace_pid_release,
पूर्ण;

व्योम ftrace_init_tracefs(काष्ठा trace_array *tr, काष्ठा dentry *d_tracer)
अणु
	trace_create_file("set_ftrace_pid", 0644, d_tracer,
			    tr, &ftrace_pid_fops);
	trace_create_file("set_ftrace_notrace_pid", 0644, d_tracer,
			    tr, &ftrace_no_pid_fops);
पूर्ण

व्योम __init ftrace_init_tracefs_toplevel(काष्ठा trace_array *tr,
					 काष्ठा dentry *d_tracer)
अणु
	/* Only the top level directory has the dyn_tracefs and profile */
	WARN_ON(!(tr->flags & TRACE_ARRAY_FL_GLOBAL));

	ftrace_init_dyn_tracefs(d_tracer);
	ftrace_profile_tracefs(d_tracer);
पूर्ण

/**
 * ftrace_समाप्त - समाप्त ftrace
 *
 * This function should be used by panic code. It stops ftrace
 * but in a not so nice way. If you need to simply समाप्त ftrace
 * from a non-atomic section, use ftrace_समाप्त.
 */
व्योम ftrace_समाप्त(व्योम)
अणु
	ftrace_disabled = 1;
	ftrace_enabled = 0;
	ftrace_trace_function = ftrace_stub;
पूर्ण

/**
 * Test अगर ftrace is dead or not.
 */
पूर्णांक ftrace_is_dead(व्योम)
अणु
	वापस ftrace_disabled;
पूर्ण

/**
 * रेजिस्टर_ftrace_function - रेजिस्टर a function क्रम profiling
 * @ops - ops काष्ठाure that holds the function क्रम profiling.
 *
 * Register a function to be called by all functions in the
 * kernel.
 *
 * Note: @ops->func and all the functions it calls must be labeled
 *       with "notrace", otherwise it will go पूर्णांकo a
 *       recursive loop.
 */
पूर्णांक रेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops)
अणु
	पूर्णांक ret = -1;

	ftrace_ops_init(ops);

	mutex_lock(&ftrace_lock);

	ret = ftrace_startup(ops, 0);

	mutex_unlock(&ftrace_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_ftrace_function);

/**
 * unरेजिस्टर_ftrace_function - unरेजिस्टर a function क्रम profiling.
 * @ops - ops काष्ठाure that holds the function to unरेजिस्टर
 *
 * Unरेजिस्टर a function that was added to be called by ftrace profiling.
 */
पूर्णांक unरेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops)
अणु
	पूर्णांक ret;

	mutex_lock(&ftrace_lock);
	ret = ftrace_shutकरोwn(ops, 0);
	mutex_unlock(&ftrace_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_ftrace_function);

अटल bool is_permanent_ops_रेजिस्टरed(व्योम)
अणु
	काष्ठा ftrace_ops *op;

	करो_क्रम_each_ftrace_op(op, ftrace_ops_list) अणु
		अगर (op->flags & FTRACE_OPS_FL_PERMANENT)
			वापस true;
	पूर्ण जबतक_क्रम_each_ftrace_op(op);

	वापस false;
पूर्ण

पूर्णांक
ftrace_enable_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = -ENODEV;

	mutex_lock(&ftrace_lock);

	अगर (unlikely(ftrace_disabled))
		जाओ out;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ret || !ग_लिखो || (last_ftrace_enabled == !!ftrace_enabled))
		जाओ out;

	अगर (ftrace_enabled) अणु

		/* we are starting ftrace again */
		अगर (rcu_dereference_रक्षित(ftrace_ops_list,
			lockdep_is_held(&ftrace_lock)) != &ftrace_list_end)
			update_ftrace_function();

		ftrace_startup_sysctl();

	पूर्ण अन्यथा अणु
		अगर (is_permanent_ops_रेजिस्टरed()) अणु
			ftrace_enabled = true;
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		/* stopping ftrace calls (just send to ftrace_stub) */
		ftrace_trace_function = ftrace_stub;

		ftrace_shutकरोwn_sysctl();
	पूर्ण

	last_ftrace_enabled = !!ftrace_enabled;
 out:
	mutex_unlock(&ftrace_lock);
	वापस ret;
पूर्ण
