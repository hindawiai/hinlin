<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kprobes-based tracing events
 *
 * Created by Masami Hiramatsu <mhiramat@redhat.com>
 *
 */
#घोषणा pr_fmt(fmt)	"trace_kprobe: " fmt

#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/rculist.h>
#समावेश <linux/error-injection.h>

#समावेश <यंत्र/setup.h>  /* क्रम COMMAND_LINE_SIZE */

#समावेश "trace_dynevent.h"
#समावेश "trace_kprobe_selftest.h"
#समावेश "trace_probe.h"
#समावेश "trace_probe_tmpl.h"

#घोषणा KPROBE_EVENT_SYSTEM "kprobes"
#घोषणा KRETPROBE_MAXACTIVE_MAX 4096

/* Kprobe early definition from command line */
अटल अक्षर kprobe_boot_events_buf[COMMAND_LINE_SIZE] __initdata;

अटल पूर्णांक __init set_kprobe_boot_events(अक्षर *str)
अणु
	strlcpy(kprobe_boot_events_buf, str, COMMAND_LINE_SIZE);
	disable_tracing_selftest("running kprobe events");

	वापस 0;
पूर्ण
__setup("kprobe_event=", set_kprobe_boot_events);

अटल पूर्णांक trace_kprobe_create(स्थिर अक्षर *raw_command);
अटल पूर्णांक trace_kprobe_show(काष्ठा seq_file *m, काष्ठा dyn_event *ev);
अटल पूर्णांक trace_kprobe_release(काष्ठा dyn_event *ev);
अटल bool trace_kprobe_is_busy(काष्ठा dyn_event *ev);
अटल bool trace_kprobe_match(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
			पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev);

अटल काष्ठा dyn_event_operations trace_kprobe_ops = अणु
	.create = trace_kprobe_create,
	.show = trace_kprobe_show,
	.is_busy = trace_kprobe_is_busy,
	.मुक्त = trace_kprobe_release,
	.match = trace_kprobe_match,
पूर्ण;

/*
 * Kprobe event core functions
 */
काष्ठा trace_kprobe अणु
	काष्ठा dyn_event	devent;
	काष्ठा kretprobe	rp;	/* Use rp.kp क्रम kprobe use */
	अचिन्हित दीर्घ __percpu *nhit;
	स्थिर अक्षर		*symbol;	/* symbol name */
	काष्ठा trace_probe	tp;
पूर्ण;

अटल bool is_trace_kprobe(काष्ठा dyn_event *ev)
अणु
	वापस ev->ops == &trace_kprobe_ops;
पूर्ण

अटल काष्ठा trace_kprobe *to_trace_kprobe(काष्ठा dyn_event *ev)
अणु
	वापस container_of(ev, काष्ठा trace_kprobe, devent);
पूर्ण

/**
 * क्रम_each_trace_kprobe - iterate over the trace_kprobe list
 * @pos:	the काष्ठा trace_kprobe * क्रम each entry
 * @dpos:	the काष्ठा dyn_event * to use as a loop cursor
 */
#घोषणा क्रम_each_trace_kprobe(pos, dpos)	\
	क्रम_each_dyn_event(dpos)		\
		अगर (is_trace_kprobe(dpos) && (pos = to_trace_kprobe(dpos)))

#घोषणा SIZखातापूर्ण_TRACE_KPROBE(n)				\
	(दुरत्व(काष्ठा trace_kprobe, tp.args) +	\
	(माप(काष्ठा probe_arg) * (n)))

अटल nokprobe_अंतरभूत bool trace_kprobe_is_वापस(काष्ठा trace_kprobe *tk)
अणु
	वापस tk->rp.handler != शून्य;
पूर्ण

अटल nokprobe_अंतरभूत स्थिर अक्षर *trace_kprobe_symbol(काष्ठा trace_kprobe *tk)
अणु
	वापस tk->symbol ? tk->symbol : "unknown";
पूर्ण

अटल nokprobe_अंतरभूत अचिन्हित दीर्घ trace_kprobe_offset(काष्ठा trace_kprobe *tk)
अणु
	वापस tk->rp.kp.offset;
पूर्ण

अटल nokprobe_अंतरभूत bool trace_kprobe_has_gone(काष्ठा trace_kprobe *tk)
अणु
	वापस !!(kprobe_gone(&tk->rp.kp));
पूर्ण

अटल nokprobe_अंतरभूत bool trace_kprobe_within_module(काष्ठा trace_kprobe *tk,
						 काष्ठा module *mod)
अणु
	पूर्णांक len = म_माप(module_name(mod));
	स्थिर अक्षर *name = trace_kprobe_symbol(tk);

	वापस म_भेदन(module_name(mod), name, len) == 0 && name[len] == ':';
पूर्ण

अटल nokprobe_अंतरभूत bool trace_kprobe_module_exist(काष्ठा trace_kprobe *tk)
अणु
	अक्षर *p;
	bool ret;

	अगर (!tk->symbol)
		वापस false;
	p = म_अक्षर(tk->symbol, ':');
	अगर (!p)
		वापस true;
	*p = '\0';
	rcu_पढ़ो_lock_sched();
	ret = !!find_module(tk->symbol);
	rcu_पढ़ो_unlock_sched();
	*p = ':';

	वापस ret;
पूर्ण

अटल bool trace_kprobe_is_busy(काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_kprobe *tk = to_trace_kprobe(ev);

	वापस trace_probe_is_enabled(&tk->tp);
पूर्ण

अटल bool trace_kprobe_match_command_head(काष्ठा trace_kprobe *tk,
					    पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर buf[MAX_ARGSTR_LEN + 1];

	अगर (!argc)
		वापस true;

	अगर (!tk->symbol)
		snम_लिखो(buf, माप(buf), "0x%p", tk->rp.kp.addr);
	अन्यथा अगर (tk->rp.kp.offset)
		snम_लिखो(buf, माप(buf), "%s+%u",
			 trace_kprobe_symbol(tk), tk->rp.kp.offset);
	अन्यथा
		snम_लिखो(buf, माप(buf), "%s", trace_kprobe_symbol(tk));
	अगर (म_भेद(buf, argv[0]))
		वापस false;
	argc--; argv++;

	वापस trace_probe_match_command_args(&tk->tp, argc, argv);
पूर्ण

अटल bool trace_kprobe_match(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
			पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_kprobe *tk = to_trace_kprobe(ev);

	वापस म_भेद(trace_probe_name(&tk->tp), event) == 0 &&
	    (!प्रणाली || म_भेद(trace_probe_group_name(&tk->tp), प्रणाली) == 0) &&
	    trace_kprobe_match_command_head(tk, argc, argv);
पूर्ण

अटल nokprobe_अंतरभूत अचिन्हित दीर्घ trace_kprobe_nhit(काष्ठा trace_kprobe *tk)
अणु
	अचिन्हित दीर्घ nhit = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		nhit += *per_cpu_ptr(tk->nhit, cpu);

	वापस nhit;
पूर्ण

अटल nokprobe_अंतरभूत bool trace_kprobe_is_रेजिस्टरed(काष्ठा trace_kprobe *tk)
अणु
	वापस !(list_empty(&tk->rp.kp.list) &&
		 hlist_unhashed(&tk->rp.kp.hlist));
पूर्ण

/* Return 0 अगर it fails to find the symbol address */
अटल nokprobe_अंतरभूत
अचिन्हित दीर्घ trace_kprobe_address(काष्ठा trace_kprobe *tk)
अणु
	अचिन्हित दीर्घ addr;

	अगर (tk->symbol) अणु
		addr = (अचिन्हित दीर्घ)
			kallsyms_lookup_name(trace_kprobe_symbol(tk));
		अगर (addr)
			addr += tk->rp.kp.offset;
	पूर्ण अन्यथा अणु
		addr = (अचिन्हित दीर्घ)tk->rp.kp.addr;
	पूर्ण
	वापस addr;
पूर्ण

अटल nokprobe_अंतरभूत काष्ठा trace_kprobe *
trace_kprobe_primary_from_call(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_probe *tp;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस शून्य;

	वापस container_of(tp, काष्ठा trace_kprobe, tp);
पूर्ण

bool trace_kprobe_on_func_entry(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_kprobe *tk = trace_kprobe_primary_from_call(call);

	वापस tk ? (kprobe_on_func_entry(tk->rp.kp.addr,
			tk->rp.kp.addr ? शून्य : tk->rp.kp.symbol_name,
			tk->rp.kp.addr ? 0 : tk->rp.kp.offset) == 0) : false;
पूर्ण

bool trace_kprobe_error_injectable(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_kprobe *tk = trace_kprobe_primary_from_call(call);

	वापस tk ? within_error_injection_list(trace_kprobe_address(tk)) :
	       false;
पूर्ण

अटल पूर्णांक रेजिस्टर_kprobe_event(काष्ठा trace_kprobe *tk);
अटल पूर्णांक unरेजिस्टर_kprobe_event(काष्ठा trace_kprobe *tk);

अटल पूर्णांक kprobe_dispatcher(काष्ठा kprobe *kp, काष्ठा pt_regs *regs);
अटल पूर्णांक kretprobe_dispatcher(काष्ठा kretprobe_instance *ri,
				काष्ठा pt_regs *regs);

अटल व्योम मुक्त_trace_kprobe(काष्ठा trace_kprobe *tk)
अणु
	अगर (tk) अणु
		trace_probe_cleanup(&tk->tp);
		kमुक्त(tk->symbol);
		मुक्त_percpu(tk->nhit);
		kमुक्त(tk);
	पूर्ण
पूर्ण

/*
 * Allocate new trace_probe and initialize it (including kprobes).
 */
अटल काष्ठा trace_kprobe *alloc_trace_kprobe(स्थिर अक्षर *group,
					     स्थिर अक्षर *event,
					     व्योम *addr,
					     स्थिर अक्षर *symbol,
					     अचिन्हित दीर्घ offs,
					     पूर्णांक maxactive,
					     पूर्णांक nargs, bool is_वापस)
अणु
	काष्ठा trace_kprobe *tk;
	पूर्णांक ret = -ENOMEM;

	tk = kzalloc(SIZखातापूर्ण_TRACE_KPROBE(nargs), GFP_KERNEL);
	अगर (!tk)
		वापस ERR_PTR(ret);

	tk->nhit = alloc_percpu(अचिन्हित दीर्घ);
	अगर (!tk->nhit)
		जाओ error;

	अगर (symbol) अणु
		tk->symbol = kstrdup(symbol, GFP_KERNEL);
		अगर (!tk->symbol)
			जाओ error;
		tk->rp.kp.symbol_name = tk->symbol;
		tk->rp.kp.offset = offs;
	पूर्ण अन्यथा
		tk->rp.kp.addr = addr;

	अगर (is_वापस)
		tk->rp.handler = kretprobe_dispatcher;
	अन्यथा
		tk->rp.kp.pre_handler = kprobe_dispatcher;

	tk->rp.maxactive = maxactive;
	INIT_HLIST_NODE(&tk->rp.kp.hlist);
	INIT_LIST_HEAD(&tk->rp.kp.list);

	ret = trace_probe_init(&tk->tp, event, group, false);
	अगर (ret < 0)
		जाओ error;

	dyn_event_init(&tk->devent, &trace_kprobe_ops);
	वापस tk;
error:
	मुक्त_trace_kprobe(tk);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा trace_kprobe *find_trace_kprobe(स्थिर अक्षर *event,
					      स्थिर अक्षर *group)
अणु
	काष्ठा dyn_event *pos;
	काष्ठा trace_kprobe *tk;

	क्रम_each_trace_kprobe(tk, pos)
		अगर (म_भेद(trace_probe_name(&tk->tp), event) == 0 &&
		    म_भेद(trace_probe_group_name(&tk->tp), group) == 0)
			वापस tk;
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक __enable_trace_kprobe(काष्ठा trace_kprobe *tk)
अणु
	पूर्णांक ret = 0;

	अगर (trace_kprobe_is_रेजिस्टरed(tk) && !trace_kprobe_has_gone(tk)) अणु
		अगर (trace_kprobe_is_वापस(tk))
			ret = enable_kretprobe(&tk->rp);
		अन्यथा
			ret = enable_kprobe(&tk->rp.kp);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __disable_trace_kprobe(काष्ठा trace_probe *tp)
अणु
	काष्ठा trace_probe *pos;
	काष्ठा trace_kprobe *tk;

	list_क्रम_each_entry(pos, trace_probe_probe_list(tp), list) अणु
		tk = container_of(pos, काष्ठा trace_kprobe, tp);
		अगर (!trace_kprobe_is_रेजिस्टरed(tk))
			जारी;
		अगर (trace_kprobe_is_वापस(tk))
			disable_kretprobe(&tk->rp);
		अन्यथा
			disable_kprobe(&tk->rp.kp);
	पूर्ण
पूर्ण

/*
 * Enable trace_probe
 * अगर the file is शून्य, enable "perf" handler, or enable "trace" handler.
 */
अटल पूर्णांक enable_trace_kprobe(काष्ठा trace_event_call *call,
				काष्ठा trace_event_file *file)
अणु
	काष्ठा trace_probe *pos, *tp;
	काष्ठा trace_kprobe *tk;
	bool enabled;
	पूर्णांक ret = 0;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENODEV;
	enabled = trace_probe_is_enabled(tp);

	/* This also changes "enabled" state */
	अगर (file) अणु
		ret = trace_probe_add_file(tp, file);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		trace_probe_set_flag(tp, TP_FLAG_PROखाता);

	अगर (enabled)
		वापस 0;

	list_क्रम_each_entry(pos, trace_probe_probe_list(tp), list) अणु
		tk = container_of(pos, काष्ठा trace_kprobe, tp);
		अगर (trace_kprobe_has_gone(tk))
			जारी;
		ret = __enable_trace_kprobe(tk);
		अगर (ret)
			अवरोध;
		enabled = true;
	पूर्ण

	अगर (ret) अणु
		/* Failed to enable one of them. Roll back all */
		अगर (enabled)
			__disable_trace_kprobe(tp);
		अगर (file)
			trace_probe_हटाओ_file(tp, file);
		अन्यथा
			trace_probe_clear_flag(tp, TP_FLAG_PROखाता);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Disable trace_probe
 * अगर the file is शून्य, disable "perf" handler, or disable "trace" handler.
 */
अटल पूर्णांक disable_trace_kprobe(काष्ठा trace_event_call *call,
				काष्ठा trace_event_file *file)
अणु
	काष्ठा trace_probe *tp;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENODEV;

	अगर (file) अणु
		अगर (!trace_probe_get_file_link(tp, file))
			वापस -ENOENT;
		अगर (!trace_probe_has_single_file(tp))
			जाओ out;
		trace_probe_clear_flag(tp, TP_FLAG_TRACE);
	पूर्ण अन्यथा
		trace_probe_clear_flag(tp, TP_FLAG_PROखाता);

	अगर (!trace_probe_is_enabled(tp))
		__disable_trace_kprobe(tp);

 out:
	अगर (file)
		/*
		 * Synchronization is करोne in below function. For perf event,
		 * file == शून्य and perf_trace_event_unreg() calls
		 * tracepoपूर्णांक_synchronize_unरेजिस्टर() to ensure synchronize
		 * event. We करोn't need to care about it.
		 */
		trace_probe_हटाओ_file(tp, file);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_DYNAMIC_FTRACE) && \
	!defined(CONFIG_KPROBE_EVENTS_ON_NOTRACE)
अटल bool __within_notrace_func(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ offset, size;

	अगर (!addr || !kallsyms_lookup_size_offset(addr, &size, &offset))
		वापस false;

	/* Get the entry address of the target function */
	addr -= offset;

	/*
	 * Since ftrace_location_range() करोes inclusive range check, we need
	 * to subtract 1 byte from the end address.
	 */
	वापस !ftrace_location_range(addr, addr + size - 1);
पूर्ण

अटल bool within_notrace_func(काष्ठा trace_kprobe *tk)
अणु
	अचिन्हित दीर्घ addr = trace_kprobe_address(tk);
	अक्षर symname[KSYM_NAME_LEN], *p;

	अगर (!__within_notrace_func(addr))
		वापस false;

	/* Check अगर the address is on a suffixed-symbol */
	अगर (!lookup_symbol_name(addr, symname)) अणु
		p = म_अक्षर(symname, '.');
		अगर (!p)
			वापस true;
		*p = '\0';
		addr = (अचिन्हित दीर्घ)kprobe_lookup_name(symname, 0);
		अगर (addr)
			वापस __within_notrace_func(addr);
	पूर्ण

	वापस true;
पूर्ण
#अन्यथा
#घोषणा within_notrace_func(tk)	(false)
#पूर्ण_अगर

/* Internal रेजिस्टर function - just handle k*probes and flags */
अटल पूर्णांक __रेजिस्टर_trace_kprobe(काष्ठा trace_kprobe *tk)
अणु
	पूर्णांक i, ret;

	ret = security_locked_करोwn(LOCKDOWN_KPROBES);
	अगर (ret)
		वापस ret;

	अगर (trace_kprobe_is_रेजिस्टरed(tk))
		वापस -EINVAL;

	अगर (within_notrace_func(tk)) अणु
		pr_warn("Could not probe notrace function %s\n",
			trace_kprobe_symbol(tk));
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < tk->tp.nr_args; i++) अणु
		ret = traceprobe_update_arg(&tk->tp.args[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set/clear disabled flag according to tp->flag */
	अगर (trace_probe_is_enabled(&tk->tp))
		tk->rp.kp.flags &= ~KPROBE_FLAG_DISABLED;
	अन्यथा
		tk->rp.kp.flags |= KPROBE_FLAG_DISABLED;

	अगर (trace_kprobe_is_वापस(tk))
		ret = रेजिस्टर_kretprobe(&tk->rp);
	अन्यथा
		ret = रेजिस्टर_kprobe(&tk->rp.kp);

	वापस ret;
पूर्ण

/* Internal unरेजिस्टर function - just handle k*probes and flags */
अटल व्योम __unरेजिस्टर_trace_kprobe(काष्ठा trace_kprobe *tk)
अणु
	अगर (trace_kprobe_is_रेजिस्टरed(tk)) अणु
		अगर (trace_kprobe_is_वापस(tk))
			unरेजिस्टर_kretprobe(&tk->rp);
		अन्यथा
			unरेजिस्टर_kprobe(&tk->rp.kp);
		/* Cleanup kprobe क्रम reuse and mark it unरेजिस्टरed */
		INIT_HLIST_NODE(&tk->rp.kp.hlist);
		INIT_LIST_HEAD(&tk->rp.kp.list);
		अगर (tk->rp.kp.symbol_name)
			tk->rp.kp.addr = शून्य;
	पूर्ण
पूर्ण

/* Unरेजिस्टर a trace_probe and probe_event */
अटल पूर्णांक unरेजिस्टर_trace_kprobe(काष्ठा trace_kprobe *tk)
अणु
	/* If other probes are on the event, just unरेजिस्टर kprobe */
	अगर (trace_probe_has_sibling(&tk->tp))
		जाओ unreg;

	/* Enabled event can not be unरेजिस्टरed */
	अगर (trace_probe_is_enabled(&tk->tp))
		वापस -EBUSY;

	/* Will fail अगर probe is being used by ftrace or perf */
	अगर (unरेजिस्टर_kprobe_event(tk))
		वापस -EBUSY;

unreg:
	__unरेजिस्टर_trace_kprobe(tk);
	dyn_event_हटाओ(&tk->devent);
	trace_probe_unlink(&tk->tp);

	वापस 0;
पूर्ण

अटल bool trace_kprobe_has_same_kprobe(काष्ठा trace_kprobe *orig,
					 काष्ठा trace_kprobe *comp)
अणु
	काष्ठा trace_probe_event *tpe = orig->tp.event;
	काष्ठा trace_probe *pos;
	पूर्णांक i;

	list_क्रम_each_entry(pos, &tpe->probes, list) अणु
		orig = container_of(pos, काष्ठा trace_kprobe, tp);
		अगर (म_भेद(trace_kprobe_symbol(orig),
			   trace_kprobe_symbol(comp)) ||
		    trace_kprobe_offset(orig) != trace_kprobe_offset(comp))
			जारी;

		/*
		 * trace_probe_compare_arg_type() ensured that nr_args and
		 * each argument name and type are same. Let's compare comm.
		 */
		क्रम (i = 0; i < orig->tp.nr_args; i++) अणु
			अगर (म_भेद(orig->tp.args[i].comm,
				   comp->tp.args[i].comm))
				अवरोध;
		पूर्ण

		अगर (i == orig->tp.nr_args)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक append_trace_kprobe(काष्ठा trace_kprobe *tk, काष्ठा trace_kprobe *to)
अणु
	पूर्णांक ret;

	ret = trace_probe_compare_arg_type(&tk->tp, &to->tp);
	अगर (ret) अणु
		/* Note that argument starts index = 2 */
		trace_probe_log_set_index(ret + 1);
		trace_probe_log_err(0, DIFF_ARG_TYPE);
		वापस -EEXIST;
	पूर्ण
	अगर (trace_kprobe_has_same_kprobe(to, tk)) अणु
		trace_probe_log_set_index(0);
		trace_probe_log_err(0, SAME_PROBE);
		वापस -EEXIST;
	पूर्ण

	/* Append to existing event */
	ret = trace_probe_append(&tk->tp, &to->tp);
	अगर (ret)
		वापस ret;

	/* Register k*probe */
	ret = __रेजिस्टर_trace_kprobe(tk);
	अगर (ret == -ENOENT && !trace_kprobe_module_exist(tk)) अणु
		pr_warn("This probe might be able to register after target module is loaded. Continue.\n");
		ret = 0;
	पूर्ण

	अगर (ret)
		trace_probe_unlink(&tk->tp);
	अन्यथा
		dyn_event_add(&tk->devent);

	वापस ret;
पूर्ण

/* Register a trace_probe and probe_event */
अटल पूर्णांक रेजिस्टर_trace_kprobe(काष्ठा trace_kprobe *tk)
अणु
	काष्ठा trace_kprobe *old_tk;
	पूर्णांक ret;

	mutex_lock(&event_mutex);

	old_tk = find_trace_kprobe(trace_probe_name(&tk->tp),
				   trace_probe_group_name(&tk->tp));
	अगर (old_tk) अणु
		अगर (trace_kprobe_is_वापस(tk) != trace_kprobe_is_वापस(old_tk)) अणु
			trace_probe_log_set_index(0);
			trace_probe_log_err(0, DIFF_PROBE_TYPE);
			ret = -EEXIST;
		पूर्ण अन्यथा अणु
			ret = append_trace_kprobe(tk, old_tk);
		पूर्ण
		जाओ end;
	पूर्ण

	/* Register new event */
	ret = रेजिस्टर_kprobe_event(tk);
	अगर (ret) अणु
		pr_warn("Failed to register probe event(%d)\n", ret);
		जाओ end;
	पूर्ण

	/* Register k*probe */
	ret = __रेजिस्टर_trace_kprobe(tk);
	अगर (ret == -ENOENT && !trace_kprobe_module_exist(tk)) अणु
		pr_warn("This probe might be able to register after target module is loaded. Continue.\n");
		ret = 0;
	पूर्ण

	अगर (ret < 0)
		unरेजिस्टर_kprobe_event(tk);
	अन्यथा
		dyn_event_add(&tk->devent);

end:
	mutex_unlock(&event_mutex);
	वापस ret;
पूर्ण

/* Module notअगरier call back, checking event on the module */
अटल पूर्णांक trace_kprobe_module_callback(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;
	काष्ठा dyn_event *pos;
	काष्ठा trace_kprobe *tk;
	पूर्णांक ret;

	अगर (val != MODULE_STATE_COMING)
		वापस NOTIFY_DONE;

	/* Update probes on coming module */
	mutex_lock(&event_mutex);
	क्रम_each_trace_kprobe(tk, pos) अणु
		अगर (trace_kprobe_within_module(tk, mod)) अणु
			/* Don't need to check busy - this should have gone. */
			__unरेजिस्टर_trace_kprobe(tk);
			ret = __रेजिस्टर_trace_kprobe(tk);
			अगर (ret)
				pr_warn("Failed to re-register probe %s on %s: %d\n",
					trace_probe_name(&tk->tp),
					module_name(mod), ret);
		पूर्ण
	पूर्ण
	mutex_unlock(&event_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block trace_kprobe_module_nb = अणु
	.notअगरier_call = trace_kprobe_module_callback,
	.priority = 1	/* Invoked after kprobe module callback */
पूर्ण;

/* Convert certain expected symbols पूर्णांकo '_' when generating event names */
अटल अंतरभूत व्योम sanitize_event_name(अक्षर *name)
अणु
	जबतक (*name++ != '\0')
		अगर (*name == ':' || *name == '.')
			*name = '_';
पूर्ण

अटल पूर्णांक __trace_kprobe_create(पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	/*
	 * Argument syntax:
	 *  - Add kprobe:
	 *      p[:[GRP/]EVENT] [MOD:]KSYM[+OFFS]|KADDR [FETCHARGS]
	 *  - Add kretprobe:
	 *      r[MAXACTIVE][:[GRP/]EVENT] [MOD:]KSYM[+0] [FETCHARGS]
	 *    Or
	 *      p:[GRP/]EVENT] [MOD:]KSYM[+0]%वापस [FETCHARGS]
	 *
	 * Fetch args:
	 *  $retval	: fetch वापस value
	 *  $stack	: fetch stack address
	 *  $stackN	: fetch Nth of stack (N:0-)
	 *  $comm       : fetch current task comm
	 *  @ADDR	: fetch memory at ADDR (ADDR should be in kernel)
	 *  @SYM[+|-offs] : fetch memory at SYM +|- offs (SYM is a data symbol)
	 *  %REG	: fetch रेजिस्टर REG
	 * Dereferencing memory fetch:
	 *  +|-offs(ARG) : fetch memory at ARG +|- offs address.
	 * Alias name of args:
	 *  NAME=FETCHARG : set NAME as alias of FETCHARG.
	 * Type of args:
	 *  FETCHARG:TYPE : use TYPE instead of अचिन्हित दीर्घ.
	 */
	काष्ठा trace_kprobe *tk = शून्य;
	पूर्णांक i, len, ret = 0;
	bool is_वापस = false;
	अक्षर *symbol = शून्य, *पंचांगp = शून्य;
	स्थिर अक्षर *event = शून्य, *group = KPROBE_EVENT_SYSTEM;
	पूर्णांक maxactive = 0;
	दीर्घ offset = 0;
	व्योम *addr = शून्य;
	अक्षर buf[MAX_EVENT_NAME_LEN];
	अचिन्हित पूर्णांक flags = TPARG_FL_KERNEL;

	चयन (argv[0][0]) अणु
	हाल 'r':
		is_वापस = true;
		अवरोध;
	हाल 'p':
		अवरोध;
	शेष:
		वापस -ECANCELED;
	पूर्ण
	अगर (argc < 2)
		वापस -ECANCELED;

	trace_probe_log_init("trace_kprobe", argc, argv);

	event = म_अक्षर(&argv[0][1], ':');
	अगर (event)
		event++;

	अगर (है_अंक(argv[0][1])) अणु
		अगर (!is_वापस) अणु
			trace_probe_log_err(1, MAXACT_NO_KPROBE);
			जाओ parse_error;
		पूर्ण
		अगर (event)
			len = event - &argv[0][1] - 1;
		अन्यथा
			len = म_माप(&argv[0][1]);
		अगर (len > MAX_EVENT_NAME_LEN - 1) अणु
			trace_probe_log_err(1, BAD_MAXACT);
			जाओ parse_error;
		पूर्ण
		स_नकल(buf, &argv[0][1], len);
		buf[len] = '\0';
		ret = kstrtouपूर्णांक(buf, 0, &maxactive);
		अगर (ret || !maxactive) अणु
			trace_probe_log_err(1, BAD_MAXACT);
			जाओ parse_error;
		पूर्ण
		/* kretprobes instances are iterated over via a list. The
		 * maximum should stay reasonable.
		 */
		अगर (maxactive > KRETPROBE_MAXACTIVE_MAX) अणु
			trace_probe_log_err(1, MAXACT_TOO_BIG);
			जाओ parse_error;
		पूर्ण
	पूर्ण

	/* try to parse an address. अगर that fails, try to पढ़ो the
	 * input as a symbol. */
	अगर (kम_से_अदीर्घ(argv[1], 0, (अचिन्हित दीर्घ *)&addr)) अणु
		trace_probe_log_set_index(1);
		/* Check whether uprobe event specअगरied */
		अगर (म_अक्षर(argv[1], '/') && strchr(argv[1], ':')) अणु
			ret = -ECANCELED;
			जाओ error;
		पूर्ण
		/* a symbol specअगरied */
		symbol = kstrdup(argv[1], GFP_KERNEL);
		अगर (!symbol)
			वापस -ENOMEM;

		पंचांगp = म_अक्षर(symbol, '%');
		अगर (पंचांगp) अणु
			अगर (!म_भेद(पंचांगp, "%return")) अणु
				*पंचांगp = '\0';
				is_वापस = true;
			पूर्ण अन्यथा अणु
				trace_probe_log_err(पंचांगp - symbol, BAD_ADDR_SUFFIX);
				जाओ parse_error;
			पूर्ण
		पूर्ण

		/* TODO: support .init module functions */
		ret = traceprobe_split_symbol_offset(symbol, &offset);
		अगर (ret || offset < 0 || offset > अच_पूर्णांक_उच्च) अणु
			trace_probe_log_err(0, BAD_PROBE_ADDR);
			जाओ parse_error;
		पूर्ण
		अगर (is_वापस)
			flags |= TPARG_FL_RETURN;
		ret = kprobe_on_func_entry(शून्य, symbol, offset);
		अगर (ret == 0)
			flags |= TPARG_FL_FENTRY;
		/* Defer the ENOENT हाल until रेजिस्टर kprobe */
		अगर (ret == -EINVAL && is_वापस) अणु
			trace_probe_log_err(0, BAD_RETPROBE);
			जाओ parse_error;
		पूर्ण
	पूर्ण

	trace_probe_log_set_index(0);
	अगर (event) अणु
		ret = traceprobe_parse_event_name(&event, &group, buf,
						  event - argv[0]);
		अगर (ret)
			जाओ parse_error;
	पूर्ण अन्यथा अणु
		/* Make a new event name */
		अगर (symbol)
			snम_लिखो(buf, MAX_EVENT_NAME_LEN, "%c_%s_%ld",
				 is_वापस ? 'r' : 'p', symbol, offset);
		अन्यथा
			snम_लिखो(buf, MAX_EVENT_NAME_LEN, "%c_0x%p",
				 is_वापस ? 'r' : 'p', addr);
		sanitize_event_name(buf);
		event = buf;
	पूर्ण

	/* setup a probe */
	tk = alloc_trace_kprobe(group, event, addr, symbol, offset, maxactive,
			       argc - 2, is_वापस);
	अगर (IS_ERR(tk)) अणु
		ret = PTR_ERR(tk);
		/* This must वापस -ENOMEM, अन्यथा there is a bug */
		WARN_ON_ONCE(ret != -ENOMEM);
		जाओ out;	/* We know tk is not allocated */
	पूर्ण
	argc -= 2; argv += 2;

	/* parse arguments */
	क्रम (i = 0; i < argc && i < MAX_TRACE_ARGS; i++) अणु
		पंचांगp = kstrdup(argv[i], GFP_KERNEL);
		अगर (!पंचांगp) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		trace_probe_log_set_index(i + 2);
		ret = traceprobe_parse_probe_arg(&tk->tp, i, पंचांगp, flags);
		kमुक्त(पंचांगp);
		अगर (ret)
			जाओ error;	/* This can be -ENOMEM */
	पूर्ण

	ret = traceprobe_set_prपूर्णांक_fmt(&tk->tp, is_वापस);
	अगर (ret < 0)
		जाओ error;

	ret = रेजिस्टर_trace_kprobe(tk);
	अगर (ret) अणु
		trace_probe_log_set_index(1);
		अगर (ret == -EILSEQ)
			trace_probe_log_err(0, BAD_INSN_BNDRY);
		अन्यथा अगर (ret == -ENOENT)
			trace_probe_log_err(0, BAD_PROBE_ADDR);
		अन्यथा अगर (ret != -ENOMEM && ret != -EEXIST)
			trace_probe_log_err(0, FAIL_REG_PROBE);
		जाओ error;
	पूर्ण

out:
	trace_probe_log_clear();
	kमुक्त(symbol);
	वापस ret;

parse_error:
	ret = -EINVAL;
error:
	मुक्त_trace_kprobe(tk);
	जाओ out;
पूर्ण

अटल पूर्णांक trace_kprobe_create(स्थिर अक्षर *raw_command)
अणु
	वापस trace_probe_create(raw_command, __trace_kprobe_create);
पूर्ण

अटल पूर्णांक create_or_delete_trace_kprobe(स्थिर अक्षर *raw_command)
अणु
	पूर्णांक ret;

	अगर (raw_command[0] == '-')
		वापस dyn_event_release(raw_command, &trace_kprobe_ops);

	ret = trace_kprobe_create(raw_command);
	वापस ret == -ECANCELED ? -EINVAL : ret;
पूर्ण

अटल पूर्णांक trace_kprobe_run_command(काष्ठा dynevent_cmd *cmd)
अणु
	वापस create_or_delete_trace_kprobe(cmd->seq.buffer);
पूर्ण

/**
 * kprobe_event_cmd_init - Initialize a kprobe event command object
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @buf: A poपूर्णांकer to the buffer used to build the command
 * @maxlen: The length of the buffer passed in @buf
 *
 * Initialize a synthetic event command object.  Use this beक्रमe
 * calling any of the other kprobe_event functions.
 */
व्योम kprobe_event_cmd_init(काष्ठा dynevent_cmd *cmd, अक्षर *buf, पूर्णांक maxlen)
अणु
	dynevent_cmd_init(cmd, buf, maxlen, DYNEVENT_TYPE_KPROBE,
			  trace_kprobe_run_command);
पूर्ण
EXPORT_SYMBOL_GPL(kprobe_event_cmd_init);

/**
 * __kprobe_event_gen_cmd_start - Generate a kprobe event command from arg list
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @name: The name of the kprobe event
 * @loc: The location of the kprobe event
 * @kretprobe: Is this a वापस probe?
 * @args: Variable number of arg (pairs), one pair क्रम each field
 *
 * NOTE: Users normally won't want to call this function directly, but
 * rather use the kprobe_event_gen_cmd_start() wrapper, which स्वतःmatically
 * adds a शून्य to the end of the arg list.  If this function is used
 * directly, make sure the last arg in the variable arg list is शून्य.
 *
 * Generate a kprobe event command to be executed by
 * kprobe_event_gen_cmd_end().  This function can be used to generate the
 * complete command or only the first part of it; in the latter हाल,
 * kprobe_event_add_fields() can be used to add more fields following this.
 *
 * Unlikely the synth_event_gen_cmd_start(), @loc must be specअगरied. This
 * वापसs -EINVAL अगर @loc == शून्य.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक __kprobe_event_gen_cmd_start(काष्ठा dynevent_cmd *cmd, bool kretprobe,
				 स्थिर अक्षर *name, स्थिर अक्षर *loc, ...)
अणु
	अक्षर buf[MAX_EVENT_NAME_LEN];
	काष्ठा dynevent_arg arg;
	बहु_सूची args;
	पूर्णांक ret;

	अगर (cmd->type != DYNEVENT_TYPE_KPROBE)
		वापस -EINVAL;

	अगर (!loc)
		वापस -EINVAL;

	अगर (kretprobe)
		snम_लिखो(buf, MAX_EVENT_NAME_LEN, "r:kprobes/%s", name);
	अन्यथा
		snम_लिखो(buf, MAX_EVENT_NAME_LEN, "p:kprobes/%s", name);

	ret = dynevent_str_add(cmd, buf);
	अगर (ret)
		वापस ret;

	dynevent_arg_init(&arg, 0);
	arg.str = loc;
	ret = dynevent_arg_add(cmd, &arg, शून्य);
	अगर (ret)
		वापस ret;

	बहु_शुरू(args, loc);
	क्रम (;;) अणु
		स्थिर अक्षर *field;

		field = बहु_तर्क(args, स्थिर अक्षर *);
		अगर (!field)
			अवरोध;

		अगर (++cmd->n_fields > MAX_TRACE_ARGS) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		arg.str = field;
		ret = dynevent_arg_add(cmd, &arg, शून्य);
		अगर (ret)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__kprobe_event_gen_cmd_start);

/**
 * __kprobe_event_add_fields - Add probe fields to a kprobe command from arg list
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event
 * @args: Variable number of arg (pairs), one pair क्रम each field
 *
 * NOTE: Users normally won't want to call this function directly, but
 * rather use the kprobe_event_add_fields() wrapper, which
 * स्वतःmatically adds a शून्य to the end of the arg list.  If this
 * function is used directly, make sure the last arg in the variable
 * arg list is शून्य.
 *
 * Add probe fields to an existing kprobe command using a variable
 * list of args.  Fields are added in the same order they're listed.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक __kprobe_event_add_fields(काष्ठा dynevent_cmd *cmd, ...)
अणु
	काष्ठा dynevent_arg arg;
	बहु_सूची args;
	पूर्णांक ret = 0;

	अगर (cmd->type != DYNEVENT_TYPE_KPROBE)
		वापस -EINVAL;

	dynevent_arg_init(&arg, 0);

	बहु_शुरू(args, cmd);
	क्रम (;;) अणु
		स्थिर अक्षर *field;

		field = बहु_तर्क(args, स्थिर अक्षर *);
		अगर (!field)
			अवरोध;

		अगर (++cmd->n_fields > MAX_TRACE_ARGS) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		arg.str = field;
		ret = dynevent_arg_add(cmd, &arg, शून्य);
		अगर (ret)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__kprobe_event_add_fields);

/**
 * kprobe_event_delete - Delete a kprobe event
 * @name: The name of the kprobe event to delete
 *
 * Delete a kprobe event with the give @name from kernel code rather
 * than directly from the command line.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक kprobe_event_delete(स्थिर अक्षर *name)
अणु
	अक्षर buf[MAX_EVENT_NAME_LEN];

	snम_लिखो(buf, MAX_EVENT_NAME_LEN, "-:%s", name);

	वापस create_or_delete_trace_kprobe(buf);
पूर्ण
EXPORT_SYMBOL_GPL(kprobe_event_delete);

अटल पूर्णांक trace_kprobe_release(काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_kprobe *tk = to_trace_kprobe(ev);
	पूर्णांक ret = unरेजिस्टर_trace_kprobe(tk);

	अगर (!ret)
		मुक्त_trace_kprobe(tk);
	वापस ret;
पूर्ण

अटल पूर्णांक trace_kprobe_show(काष्ठा seq_file *m, काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_kprobe *tk = to_trace_kprobe(ev);
	पूर्णांक i;

	seq_अ_दो(m, trace_kprobe_is_वापस(tk) ? 'r' : 'p');
	अगर (trace_kprobe_is_वापस(tk) && tk->rp.maxactive)
		seq_म_लिखो(m, "%d", tk->rp.maxactive);
	seq_म_लिखो(m, ":%s/%s", trace_probe_group_name(&tk->tp),
				trace_probe_name(&tk->tp));

	अगर (!tk->symbol)
		seq_म_लिखो(m, " 0x%p", tk->rp.kp.addr);
	अन्यथा अगर (tk->rp.kp.offset)
		seq_म_लिखो(m, " %s+%u", trace_kprobe_symbol(tk),
			   tk->rp.kp.offset);
	अन्यथा
		seq_म_लिखो(m, " %s", trace_kprobe_symbol(tk));

	क्रम (i = 0; i < tk->tp.nr_args; i++)
		seq_म_लिखो(m, " %s=%s", tk->tp.args[i].name, tk->tp.args[i].comm);
	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

अटल पूर्णांक probes_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dyn_event *ev = v;

	अगर (!is_trace_kprobe(ev))
		वापस 0;

	वापस trace_kprobe_show(m, ev);
पूर्ण

अटल स्थिर काष्ठा seq_operations probes_seq_op = अणु
	.start  = dyn_event_seq_start,
	.next   = dyn_event_seq_next,
	.stop   = dyn_event_seq_stop,
	.show   = probes_seq_show
पूर्ण;

अटल पूर्णांक probes_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) अणु
		ret = dyn_events_release_all(&trace_kprobe_ops);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस seq_खोलो(file, &probes_seq_op);
पूर्ण

अटल sमाप_प्रकार probes_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *ppos)
अणु
	वापस trace_parse_run_command(file, buffer, count, ppos,
				       create_or_delete_trace_kprobe);
पूर्ण

अटल स्थिर काष्ठा file_operations kprobe_events_ops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = probes_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = seq_release,
	.ग_लिखो		= probes_ग_लिखो,
पूर्ण;

/* Probes profiling पूर्णांकerfaces */
अटल पूर्णांक probes_profile_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dyn_event *ev = v;
	काष्ठा trace_kprobe *tk;

	अगर (!is_trace_kprobe(ev))
		वापस 0;

	tk = to_trace_kprobe(ev);
	seq_म_लिखो(m, "  %-44s %15lu %15lu\n",
		   trace_probe_name(&tk->tp),
		   trace_kprobe_nhit(tk),
		   tk->rp.kp.nmissed);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations profile_seq_op = अणु
	.start  = dyn_event_seq_start,
	.next   = dyn_event_seq_next,
	.stop   = dyn_event_seq_stop,
	.show   = probes_profile_seq_show
पूर्ण;

अटल पूर्णांक profile_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(file, &profile_seq_op);
पूर्ण

अटल स्थिर काष्ठा file_operations kprobe_profile_ops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = profile_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = seq_release,
पूर्ण;

/* Kprobe specअगरic fetch functions */

/* Return the length of string -- including null terminal byte */
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_म_माप_user(अचिन्हित दीर्घ addr)
अणु
	स्थिर व्योम __user *uaddr =  (__क्रमce स्थिर व्योम __user *)addr;

	वापस strnlen_user_nofault(uaddr, MAX_STRING_SIZE);
पूर्ण

/* Return the length of string -- including null terminal byte */
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_म_माप(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret, len = 0;
	u8 c;

#अगर_घोषित CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE
	अगर (addr < TASK_SIZE)
		वापस fetch_store_म_माप_user(addr);
#पूर्ण_अगर

	करो अणु
		ret = copy_from_kernel_nofault(&c, (u8 *)addr + len, 1);
		len++;
	पूर्ण जबतक (c && ret == 0 && len < MAX_STRING_SIZE);

	वापस (ret < 0) ? ret : len;
पूर्ण

/*
 * Fetch a null-terminated string from user. Caller MUST set *(u32 *)buf
 * with max length and relative data location.
 */
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_string_user(अचिन्हित दीर्घ addr, व्योम *dest, व्योम *base)
अणु
	स्थिर व्योम __user *uaddr =  (__क्रमce स्थिर व्योम __user *)addr;
	पूर्णांक maxlen = get_loc_len(*(u32 *)dest);
	व्योम *__dest;
	दीर्घ ret;

	अगर (unlikely(!maxlen))
		वापस -ENOMEM;

	__dest = get_loc_data(dest, base);

	ret = म_नकलन_from_user_nofault(__dest, uaddr, maxlen);
	अगर (ret >= 0)
		*(u32 *)dest = make_data_loc(ret, __dest - base);

	वापस ret;
पूर्ण

/*
 * Fetch a null-terminated string. Caller MUST set *(u32 *)buf with max
 * length and relative data location.
 */
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_string(अचिन्हित दीर्घ addr, व्योम *dest, व्योम *base)
अणु
	पूर्णांक maxlen = get_loc_len(*(u32 *)dest);
	व्योम *__dest;
	दीर्घ ret;

#अगर_घोषित CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE
	अगर ((अचिन्हित दीर्घ)addr < TASK_SIZE)
		वापस fetch_store_string_user(addr, dest, base);
#पूर्ण_अगर

	अगर (unlikely(!maxlen))
		वापस -ENOMEM;

	__dest = get_loc_data(dest, base);

	/*
	 * Try to get string again, since the string can be changed जबतक
	 * probing.
	 */
	ret = म_नकलन_from_kernel_nofault(__dest, (व्योम *)addr, maxlen);
	अगर (ret >= 0)
		*(u32 *)dest = make_data_loc(ret, __dest - base);

	वापस ret;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक
probe_mem_पढ़ो_user(व्योम *dest, व्योम *src, माप_प्रकार size)
अणु
	स्थिर व्योम __user *uaddr =  (__क्रमce स्थिर व्योम __user *)src;

	वापस copy_from_user_nofault(dest, uaddr, size);
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक
probe_mem_पढ़ो(व्योम *dest, व्योम *src, माप_प्रकार size)
अणु
#अगर_घोषित CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE
	अगर ((अचिन्हित दीर्घ)src < TASK_SIZE)
		वापस probe_mem_पढ़ो_user(dest, src, size);
#पूर्ण_अगर
	वापस copy_from_kernel_nofault(dest, src, size);
पूर्ण

/* Note that we करोn't verअगरy it, since the code करोes not come from user space */
अटल पूर्णांक
process_fetch_insn(काष्ठा fetch_insn *code, काष्ठा pt_regs *regs, व्योम *dest,
		   व्योम *base)
अणु
	अचिन्हित दीर्घ val;

retry:
	/* 1st stage: get value from context */
	चयन (code->op) अणु
	हाल FETCH_OP_REG:
		val = regs_get_रेजिस्टर(regs, code->param);
		अवरोध;
	हाल FETCH_OP_STACK:
		val = regs_get_kernel_stack_nth(regs, code->param);
		अवरोध;
	हाल FETCH_OP_STACKP:
		val = kernel_stack_poपूर्णांकer(regs);
		अवरोध;
	हाल FETCH_OP_RETVAL:
		val = regs_वापस_value(regs);
		अवरोध;
	हाल FETCH_OP_IMM:
		val = code->immediate;
		अवरोध;
	हाल FETCH_OP_COMM:
		val = (अचिन्हित दीर्घ)current->comm;
		अवरोध;
	हाल FETCH_OP_DATA:
		val = (अचिन्हित दीर्घ)code->data;
		अवरोध;
#अगर_घोषित CONFIG_HAVE_FUNCTION_ARG_ACCESS_API
	हाल FETCH_OP_ARG:
		val = regs_get_kernel_argument(regs, code->param);
		अवरोध;
#पूर्ण_अगर
	हाल FETCH_NOP_SYMBOL:	/* Ignore a place holder */
		code++;
		जाओ retry;
	शेष:
		वापस -EILSEQ;
	पूर्ण
	code++;

	वापस process_fetch_insn_bottom(code, val, dest, base);
पूर्ण
NOKPROBE_SYMBOL(process_fetch_insn)

/* Kprobe handler */
अटल nokprobe_अंतरभूत व्योम
__kprobe_trace_func(काष्ठा trace_kprobe *tk, काष्ठा pt_regs *regs,
		    काष्ठा trace_event_file *trace_file)
अणु
	काष्ठा kprobe_trace_entry_head *entry;
	काष्ठा trace_event_call *call = trace_probe_event_call(&tk->tp);
	काष्ठा trace_event_buffer fbuffer;
	पूर्णांक dsize;

	WARN_ON(call != trace_file->event_call);

	अगर (trace_trigger_soft_disabled(trace_file))
		वापस;

	fbuffer.trace_ctx = tracing_gen_ctx();
	fbuffer.trace_file = trace_file;

	dsize = __get_data_size(&tk->tp, regs);

	fbuffer.event =
		trace_event_buffer_lock_reserve(&fbuffer.buffer, trace_file,
					call->event.type,
					माप(*entry) + tk->tp.size + dsize,
					fbuffer.trace_ctx);
	अगर (!fbuffer.event)
		वापस;

	fbuffer.regs = regs;
	entry = fbuffer.entry = ring_buffer_event_data(fbuffer.event);
	entry->ip = (अचिन्हित दीर्घ)tk->rp.kp.addr;
	store_trace_args(&entry[1], &tk->tp, regs, माप(*entry), dsize);

	trace_event_buffer_commit(&fbuffer);
पूर्ण

अटल व्योम
kprobe_trace_func(काष्ठा trace_kprobe *tk, काष्ठा pt_regs *regs)
अणु
	काष्ठा event_file_link *link;

	trace_probe_क्रम_each_link_rcu(link, &tk->tp)
		__kprobe_trace_func(tk, regs, link->file);
पूर्ण
NOKPROBE_SYMBOL(kprobe_trace_func);

/* Kretprobe handler */
अटल nokprobe_अंतरभूत व्योम
__kretprobe_trace_func(काष्ठा trace_kprobe *tk, काष्ठा kretprobe_instance *ri,
		       काष्ठा pt_regs *regs,
		       काष्ठा trace_event_file *trace_file)
अणु
	काष्ठा kretprobe_trace_entry_head *entry;
	काष्ठा trace_event_buffer fbuffer;
	काष्ठा trace_event_call *call = trace_probe_event_call(&tk->tp);
	पूर्णांक dsize;

	WARN_ON(call != trace_file->event_call);

	अगर (trace_trigger_soft_disabled(trace_file))
		वापस;

	fbuffer.trace_ctx = tracing_gen_ctx();
	fbuffer.trace_file = trace_file;

	dsize = __get_data_size(&tk->tp, regs);
	fbuffer.event =
		trace_event_buffer_lock_reserve(&fbuffer.buffer, trace_file,
					call->event.type,
					माप(*entry) + tk->tp.size + dsize,
					fbuffer.trace_ctx);
	अगर (!fbuffer.event)
		वापस;

	fbuffer.regs = regs;
	entry = fbuffer.entry = ring_buffer_event_data(fbuffer.event);
	entry->func = (अचिन्हित दीर्घ)tk->rp.kp.addr;
	entry->ret_ip = (अचिन्हित दीर्घ)ri->ret_addr;
	store_trace_args(&entry[1], &tk->tp, regs, माप(*entry), dsize);

	trace_event_buffer_commit(&fbuffer);
पूर्ण

अटल व्योम
kretprobe_trace_func(काष्ठा trace_kprobe *tk, काष्ठा kretprobe_instance *ri,
		     काष्ठा pt_regs *regs)
अणु
	काष्ठा event_file_link *link;

	trace_probe_क्रम_each_link_rcu(link, &tk->tp)
		__kretprobe_trace_func(tk, ri, regs, link->file);
पूर्ण
NOKPROBE_SYMBOL(kretprobe_trace_func);

/* Event entry prपूर्णांकers */
अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_kprobe_event(काष्ठा trace_iterator *iter, पूर्णांक flags,
		   काष्ठा trace_event *event)
अणु
	काष्ठा kprobe_trace_entry_head *field;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_probe *tp;

	field = (काष्ठा kprobe_trace_entry_head *)iter->ent;
	tp = trace_probe_primary_from_call(
		container_of(event, काष्ठा trace_event_call, event));
	अगर (WARN_ON_ONCE(!tp))
		जाओ out;

	trace_seq_म_लिखो(s, "%s: (", trace_probe_name(tp));

	अगर (!seq_prपूर्णांक_ip_sym(s, field->ip, flags | TRACE_ITER_SYM_OFFSET))
		जाओ out;

	trace_seq_अ_दो(s, ')');

	अगर (prपूर्णांक_probe_args(s, tp->args, tp->nr_args,
			     (u8 *)&field[1], field) < 0)
		जाओ out;

	trace_seq_अ_दो(s, '\n');
 out:
	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_kretprobe_event(काष्ठा trace_iterator *iter, पूर्णांक flags,
		      काष्ठा trace_event *event)
अणु
	काष्ठा kretprobe_trace_entry_head *field;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_probe *tp;

	field = (काष्ठा kretprobe_trace_entry_head *)iter->ent;
	tp = trace_probe_primary_from_call(
		container_of(event, काष्ठा trace_event_call, event));
	अगर (WARN_ON_ONCE(!tp))
		जाओ out;

	trace_seq_म_लिखो(s, "%s: (", trace_probe_name(tp));

	अगर (!seq_prपूर्णांक_ip_sym(s, field->ret_ip, flags | TRACE_ITER_SYM_OFFSET))
		जाओ out;

	trace_seq_माला_दो(s, " <- ");

	अगर (!seq_prपूर्णांक_ip_sym(s, field->func, flags & ~TRACE_ITER_SYM_OFFSET))
		जाओ out;

	trace_seq_अ_दो(s, ')');

	अगर (prपूर्णांक_probe_args(s, tp->args, tp->nr_args,
			     (u8 *)&field[1], field) < 0)
		जाओ out;

	trace_seq_अ_दो(s, '\n');

 out:
	वापस trace_handle_वापस(s);
पूर्ण


अटल पूर्णांक kprobe_event_define_fields(काष्ठा trace_event_call *event_call)
अणु
	पूर्णांक ret;
	काष्ठा kprobe_trace_entry_head field;
	काष्ठा trace_probe *tp;

	tp = trace_probe_primary_from_call(event_call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENOENT;

	DEFINE_FIELD(अचिन्हित दीर्घ, ip, FIELD_STRING_IP, 0);

	वापस traceprobe_define_arg_fields(event_call, माप(field), tp);
पूर्ण

अटल पूर्णांक kretprobe_event_define_fields(काष्ठा trace_event_call *event_call)
अणु
	पूर्णांक ret;
	काष्ठा kretprobe_trace_entry_head field;
	काष्ठा trace_probe *tp;

	tp = trace_probe_primary_from_call(event_call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENOENT;

	DEFINE_FIELD(अचिन्हित दीर्घ, func, FIELD_STRING_FUNC, 0);
	DEFINE_FIELD(अचिन्हित दीर्घ, ret_ip, FIELD_STRING_RETIP, 0);

	वापस traceprobe_define_arg_fields(event_call, माप(field), tp);
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS

/* Kprobe profile handler */
अटल पूर्णांक
kprobe_perf_func(काष्ठा trace_kprobe *tk, काष्ठा pt_regs *regs)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(&tk->tp);
	काष्ठा kprobe_trace_entry_head *entry;
	काष्ठा hlist_head *head;
	पूर्णांक size, __size, dsize;
	पूर्णांक rctx;

	अगर (bpf_prog_array_valid(call)) अणु
		अचिन्हित दीर्घ orig_ip = inकाष्ठाion_poपूर्णांकer(regs);
		पूर्णांक ret;

		ret = trace_call_bpf(call, regs);

		/*
		 * We need to check and see अगर we modअगरied the pc of the
		 * pt_regs, and अगर so वापस 1 so that we करोn't करो the
		 * single stepping.
		 */
		अगर (orig_ip != inकाष्ठाion_poपूर्णांकer(regs))
			वापस 1;
		अगर (!ret)
			वापस 0;
	पूर्ण

	head = this_cpu_ptr(call->perf_events);
	अगर (hlist_empty(head))
		वापस 0;

	dsize = __get_data_size(&tk->tp, regs);
	__size = माप(*entry) + tk->tp.size + dsize;
	size = ALIGN(__size + माप(u32), माप(u64));
	size -= माप(u32);

	entry = perf_trace_buf_alloc(size, शून्य, &rctx);
	अगर (!entry)
		वापस 0;

	entry->ip = (अचिन्हित दीर्घ)tk->rp.kp.addr;
	स_रखो(&entry[1], 0, dsize);
	store_trace_args(&entry[1], &tk->tp, regs, माप(*entry), dsize);
	perf_trace_buf_submit(entry, size, rctx, call->event.type, 1, regs,
			      head, शून्य);
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(kprobe_perf_func);

/* Kretprobe profile handler */
अटल व्योम
kretprobe_perf_func(काष्ठा trace_kprobe *tk, काष्ठा kretprobe_instance *ri,
		    काष्ठा pt_regs *regs)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(&tk->tp);
	काष्ठा kretprobe_trace_entry_head *entry;
	काष्ठा hlist_head *head;
	पूर्णांक size, __size, dsize;
	पूर्णांक rctx;

	अगर (bpf_prog_array_valid(call) && !trace_call_bpf(call, regs))
		वापस;

	head = this_cpu_ptr(call->perf_events);
	अगर (hlist_empty(head))
		वापस;

	dsize = __get_data_size(&tk->tp, regs);
	__size = माप(*entry) + tk->tp.size + dsize;
	size = ALIGN(__size + माप(u32), माप(u64));
	size -= माप(u32);

	entry = perf_trace_buf_alloc(size, शून्य, &rctx);
	अगर (!entry)
		वापस;

	entry->func = (अचिन्हित दीर्घ)tk->rp.kp.addr;
	entry->ret_ip = (अचिन्हित दीर्घ)ri->ret_addr;
	store_trace_args(&entry[1], &tk->tp, regs, माप(*entry), dsize);
	perf_trace_buf_submit(entry, size, rctx, call->event.type, 1, regs,
			      head, शून्य);
पूर्ण
NOKPROBE_SYMBOL(kretprobe_perf_func);

पूर्णांक bpf_get_kprobe_info(स्थिर काष्ठा perf_event *event, u32 *fd_type,
			स्थिर अक्षर **symbol, u64 *probe_offset,
			u64 *probe_addr, bool perf_type_tracepoपूर्णांक)
अणु
	स्थिर अक्षर *pevent = trace_event_name(event->tp_event);
	स्थिर अक्षर *group = event->tp_event->class->प्रणाली;
	काष्ठा trace_kprobe *tk;

	अगर (perf_type_tracepoपूर्णांक)
		tk = find_trace_kprobe(pevent, group);
	अन्यथा
		tk = trace_kprobe_primary_from_call(event->tp_event);
	अगर (!tk)
		वापस -EINVAL;

	*fd_type = trace_kprobe_is_वापस(tk) ? BPF_FD_TYPE_KRETPROBE
					      : BPF_FD_TYPE_KPROBE;
	अगर (tk->symbol) अणु
		*symbol = tk->symbol;
		*probe_offset = tk->rp.kp.offset;
		*probe_addr = 0;
	पूर्ण अन्यथा अणु
		*symbol = शून्य;
		*probe_offset = 0;
		*probe_addr = (अचिन्हित दीर्घ)tk->rp.kp.addr;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PERF_EVENTS */

/*
 * called by perf_trace_init() or __ftrace_set_clr_event() under event_mutex.
 *
 * kprobe_trace_self_tests_init() करोes enable_trace_probe/disable_trace_probe
 * lockless, but we can't race with this __init function.
 */
अटल पूर्णांक kprobe_रेजिस्टर(काष्ठा trace_event_call *event,
			   क्रमागत trace_reg type, व्योम *data)
अणु
	काष्ठा trace_event_file *file = data;

	चयन (type) अणु
	हाल TRACE_REG_REGISTER:
		वापस enable_trace_kprobe(event, file);
	हाल TRACE_REG_UNREGISTER:
		वापस disable_trace_kprobe(event, file);

#अगर_घोषित CONFIG_PERF_EVENTS
	हाल TRACE_REG_PERF_REGISTER:
		वापस enable_trace_kprobe(event, शून्य);
	हाल TRACE_REG_PERF_UNREGISTER:
		वापस disable_trace_kprobe(event, शून्य);
	हाल TRACE_REG_PERF_OPEN:
	हाल TRACE_REG_PERF_CLOSE:
	हाल TRACE_REG_PERF_ADD:
	हाल TRACE_REG_PERF_DEL:
		वापस 0;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kprobe_dispatcher(काष्ठा kprobe *kp, काष्ठा pt_regs *regs)
अणु
	काष्ठा trace_kprobe *tk = container_of(kp, काष्ठा trace_kprobe, rp.kp);
	पूर्णांक ret = 0;

	raw_cpu_inc(*tk->nhit);

	अगर (trace_probe_test_flag(&tk->tp, TP_FLAG_TRACE))
		kprobe_trace_func(tk, regs);
#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (trace_probe_test_flag(&tk->tp, TP_FLAG_PROखाता))
		ret = kprobe_perf_func(tk, regs);
#पूर्ण_अगर
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(kprobe_dispatcher);

अटल पूर्णांक
kretprobe_dispatcher(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	काष्ठा kretprobe *rp = get_kretprobe(ri);
	काष्ठा trace_kprobe *tk = container_of(rp, काष्ठा trace_kprobe, rp);

	raw_cpu_inc(*tk->nhit);

	अगर (trace_probe_test_flag(&tk->tp, TP_FLAG_TRACE))
		kretprobe_trace_func(tk, ri, regs);
#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (trace_probe_test_flag(&tk->tp, TP_FLAG_PROखाता))
		kretprobe_perf_func(tk, ri, regs);
#पूर्ण_अगर
	वापस 0;	/* We करोn't tweak kernel, so just वापस 0 */
पूर्ण
NOKPROBE_SYMBOL(kretprobe_dispatcher);

अटल काष्ठा trace_event_functions kretprobe_funcs = अणु
	.trace		= prपूर्णांक_kretprobe_event
पूर्ण;

अटल काष्ठा trace_event_functions kprobe_funcs = अणु
	.trace		= prपूर्णांक_kprobe_event
पूर्ण;

अटल काष्ठा trace_event_fields kretprobe_fields_array[] = अणु
	अणु .type = TRACE_FUNCTION_TYPE,
	  .define_fields = kretprobe_event_define_fields पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा trace_event_fields kprobe_fields_array[] = अणु
	अणु .type = TRACE_FUNCTION_TYPE,
	  .define_fields = kprobe_event_define_fields पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत व्योम init_trace_event_call(काष्ठा trace_kprobe *tk)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(&tk->tp);

	अगर (trace_kprobe_is_वापस(tk)) अणु
		call->event.funcs = &kretprobe_funcs;
		call->class->fields_array = kretprobe_fields_array;
	पूर्ण अन्यथा अणु
		call->event.funcs = &kprobe_funcs;
		call->class->fields_array = kprobe_fields_array;
	पूर्ण

	call->flags = TRACE_EVENT_FL_KPROBE;
	call->class->reg = kprobe_रेजिस्टर;
पूर्ण

अटल पूर्णांक रेजिस्टर_kprobe_event(काष्ठा trace_kprobe *tk)
अणु
	init_trace_event_call(tk);

	वापस trace_probe_रेजिस्टर_event_call(&tk->tp);
पूर्ण

अटल पूर्णांक unरेजिस्टर_kprobe_event(काष्ठा trace_kprobe *tk)
अणु
	वापस trace_probe_unरेजिस्टर_event_call(&tk->tp);
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS
/* create a trace_kprobe, but करोn't add it to global lists */
काष्ठा trace_event_call *
create_local_trace_kprobe(अक्षर *func, व्योम *addr, अचिन्हित दीर्घ offs,
			  bool is_वापस)
अणु
	काष्ठा trace_kprobe *tk;
	पूर्णांक ret;
	अक्षर *event;

	/*
	 * local trace_kprobes are not added to dyn_event, so they are never
	 * searched in find_trace_kprobe(). Thereक्रमe, there is no concern of
	 * duplicated name here.
	 */
	event = func ? func : "DUMMY_EVENT";

	tk = alloc_trace_kprobe(KPROBE_EVENT_SYSTEM, event, (व्योम *)addr, func,
				offs, 0 /* maxactive */, 0 /* nargs */,
				is_वापस);

	अगर (IS_ERR(tk)) अणु
		pr_info("Failed to allocate trace_probe.(%d)\n",
			(पूर्णांक)PTR_ERR(tk));
		वापस ERR_CAST(tk);
	पूर्ण

	init_trace_event_call(tk);

	अगर (traceprobe_set_prपूर्णांक_fmt(&tk->tp, trace_kprobe_is_वापस(tk)) < 0) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ret = __रेजिस्टर_trace_kprobe(tk);
	अगर (ret < 0)
		जाओ error;

	वापस trace_probe_event_call(&tk->tp);
error:
	मुक्त_trace_kprobe(tk);
	वापस ERR_PTR(ret);
पूर्ण

व्योम destroy_local_trace_kprobe(काष्ठा trace_event_call *event_call)
अणु
	काष्ठा trace_kprobe *tk;

	tk = trace_kprobe_primary_from_call(event_call);
	अगर (unlikely(!tk))
		वापस;

	अगर (trace_probe_is_enabled(&tk->tp)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	__unरेजिस्टर_trace_kprobe(tk);

	मुक्त_trace_kprobe(tk);
पूर्ण
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */

अटल __init व्योम enable_boot_kprobe_events(व्योम)
अणु
	काष्ठा trace_array *tr = top_trace_array();
	काष्ठा trace_event_file *file;
	काष्ठा trace_kprobe *tk;
	काष्ठा dyn_event *pos;

	mutex_lock(&event_mutex);
	क्रम_each_trace_kprobe(tk, pos) अणु
		list_क्रम_each_entry(file, &tr->events, list)
			अगर (file->event_call == trace_probe_event_call(&tk->tp))
				trace_event_enable_disable(file, 1, 0);
	पूर्ण
	mutex_unlock(&event_mutex);
पूर्ण

अटल __init व्योम setup_boot_kprobe_events(व्योम)
अणु
	अक्षर *p, *cmd = kprobe_boot_events_buf;
	पूर्णांक ret;

	strreplace(kprobe_boot_events_buf, ',', ' ');

	जबतक (cmd && *cmd != '\0') अणु
		p = म_अक्षर(cmd, ';');
		अगर (p)
			*p++ = '\0';

		ret = create_or_delete_trace_kprobe(cmd);
		अगर (ret)
			pr_warn("Failed to add event(%d): %s\n", ret, cmd);

		cmd = p;
	पूर्ण

	enable_boot_kprobe_events();
पूर्ण

/*
 * Register dynevent at core_initcall. This allows kernel to setup kprobe
 * events in postcore_initcall without tracefs.
 */
अटल __init पूर्णांक init_kprobe_trace_early(व्योम)
अणु
	पूर्णांक ret;

	ret = dyn_event_रेजिस्टर(&trace_kprobe_ops);
	अगर (ret)
		वापस ret;

	अगर (रेजिस्टर_module_notअगरier(&trace_kprobe_module_nb))
		वापस -EINVAL;

	वापस 0;
पूर्ण
core_initcall(init_kprobe_trace_early);

/* Make a tracefs पूर्णांकerface क्रम controlling probe poपूर्णांकs */
अटल __init पूर्णांक init_kprobe_trace(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा dentry *entry;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	entry = tracefs_create_file("kprobe_events", 0644, शून्य,
				    शून्य, &kprobe_events_ops);

	/* Event list पूर्णांकerface */
	अगर (!entry)
		pr_warn("Could not create tracefs 'kprobe_events' entry\n");

	/* Profile पूर्णांकerface */
	entry = tracefs_create_file("kprobe_profile", 0444, शून्य,
				    शून्य, &kprobe_profile_ops);

	अगर (!entry)
		pr_warn("Could not create tracefs 'kprobe_profile' entry\n");

	setup_boot_kprobe_events();

	वापस 0;
पूर्ण
fs_initcall(init_kprobe_trace);


#अगर_घोषित CONFIG_FTRACE_STARTUP_TEST
अटल __init काष्ठा trace_event_file *
find_trace_probe_file(काष्ठा trace_kprobe *tk, काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	list_क्रम_each_entry(file, &tr->events, list)
		अगर (file->event_call == trace_probe_event_call(&tk->tp))
			वापस file;

	वापस शून्य;
पूर्ण

/*
 * Nobody but us can call enable_trace_kprobe/disable_trace_kprobe at this
 * stage, we can करो this lockless.
 */
अटल __init पूर्णांक kprobe_trace_self_tests_init(व्योम)
अणु
	पूर्णांक ret, warn = 0;
	पूर्णांक (*target)(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
	काष्ठा trace_kprobe *tk;
	काष्ठा trace_event_file *file;

	अगर (tracing_is_disabled())
		वापस -ENODEV;

	अगर (tracing_selftest_disabled)
		वापस 0;

	target = kprobe_trace_selftest_target;

	pr_info("Testing kprobe tracing: ");

	ret = create_or_delete_trace_kprobe("p:testprobe kprobe_trace_selftest_target $stack $stack0 +0($stack)");
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error on probing function entry.\n");
		warn++;
	पूर्ण अन्यथा अणु
		/* Enable trace poपूर्णांक */
		tk = find_trace_kprobe("testprobe", KPROBE_EVENT_SYSTEM);
		अगर (WARN_ON_ONCE(tk == शून्य)) अणु
			pr_warn("error on getting new probe.\n");
			warn++;
		पूर्ण अन्यथा अणु
			file = find_trace_probe_file(tk, top_trace_array());
			अगर (WARN_ON_ONCE(file == शून्य)) अणु
				pr_warn("error on getting probe file.\n");
				warn++;
			पूर्ण अन्यथा
				enable_trace_kprobe(
					trace_probe_event_call(&tk->tp), file);
		पूर्ण
	पूर्ण

	ret = create_or_delete_trace_kprobe("r:testprobe2 kprobe_trace_selftest_target $retval");
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error on probing function return.\n");
		warn++;
	पूर्ण अन्यथा अणु
		/* Enable trace poपूर्णांक */
		tk = find_trace_kprobe("testprobe2", KPROBE_EVENT_SYSTEM);
		अगर (WARN_ON_ONCE(tk == शून्य)) अणु
			pr_warn("error on getting 2nd new probe.\n");
			warn++;
		पूर्ण अन्यथा अणु
			file = find_trace_probe_file(tk, top_trace_array());
			अगर (WARN_ON_ONCE(file == शून्य)) अणु
				pr_warn("error on getting probe file.\n");
				warn++;
			पूर्ण अन्यथा
				enable_trace_kprobe(
					trace_probe_event_call(&tk->tp), file);
		पूर्ण
	पूर्ण

	अगर (warn)
		जाओ end;

	ret = target(1, 2, 3, 4, 5, 6);

	/*
	 * Not expecting an error here, the check is only to prevent the
	 * optimizer from removing the call to target() as otherwise there
	 * are no side-effects and the call is never perक्रमmed.
	 */
	अगर (ret != 21)
		warn++;

	/* Disable trace poपूर्णांकs beक्रमe removing it */
	tk = find_trace_kprobe("testprobe", KPROBE_EVENT_SYSTEM);
	अगर (WARN_ON_ONCE(tk == शून्य)) अणु
		pr_warn("error on getting test probe.\n");
		warn++;
	पूर्ण अन्यथा अणु
		अगर (trace_kprobe_nhit(tk) != 1) अणु
			pr_warn("incorrect number of testprobe hits\n");
			warn++;
		पूर्ण

		file = find_trace_probe_file(tk, top_trace_array());
		अगर (WARN_ON_ONCE(file == शून्य)) अणु
			pr_warn("error on getting probe file.\n");
			warn++;
		पूर्ण अन्यथा
			disable_trace_kprobe(
				trace_probe_event_call(&tk->tp), file);
	पूर्ण

	tk = find_trace_kprobe("testprobe2", KPROBE_EVENT_SYSTEM);
	अगर (WARN_ON_ONCE(tk == शून्य)) अणु
		pr_warn("error on getting 2nd test probe.\n");
		warn++;
	पूर्ण अन्यथा अणु
		अगर (trace_kprobe_nhit(tk) != 1) अणु
			pr_warn("incorrect number of testprobe2 hits\n");
			warn++;
		पूर्ण

		file = find_trace_probe_file(tk, top_trace_array());
		अगर (WARN_ON_ONCE(file == शून्य)) अणु
			pr_warn("error on getting probe file.\n");
			warn++;
		पूर्ण अन्यथा
			disable_trace_kprobe(
				trace_probe_event_call(&tk->tp), file);
	पूर्ण

	ret = create_or_delete_trace_kprobe("-:testprobe");
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error on deleting a probe.\n");
		warn++;
	पूर्ण

	ret = create_or_delete_trace_kprobe("-:testprobe2");
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error on deleting a probe.\n");
		warn++;
	पूर्ण

end:
	ret = dyn_events_release_all(&trace_kprobe_ops);
	अगर (WARN_ON_ONCE(ret)) अणु
		pr_warn("error on cleaning up probes.\n");
		warn++;
	पूर्ण
	/*
	 * Wait क्रम the optimizer work to finish. Otherwise it might fiddle
	 * with probes in alपढ़ोy मुक्तd __init text.
	 */
	रुको_क्रम_kprobe_optimizer();
	अगर (warn)
		pr_cont("NG: Some tests are failed. Please check them.\n");
	अन्यथा
		pr_cont("OK\n");
	वापस 0;
पूर्ण

late_initcall(kprobe_trace_self_tests_init);

#पूर्ण_अगर
