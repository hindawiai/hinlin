<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * unlikely profiler
 *
 * Copyright (C) 2008 Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <linux/kallsyms.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/hash.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/local.h>

#समावेश "trace.h"
#समावेश "trace_stat.h"
#समावेश "trace_output.h"

#अगर_घोषित CONFIG_BRANCH_TRACER

अटल काष्ठा tracer branch_trace;
अटल पूर्णांक branch_tracing_enabled __पढ़ो_mostly;
अटल DEFINE_MUTEX(branch_tracing_mutex);

अटल काष्ठा trace_array *branch_tracer;

अटल व्योम
probe_likely_condition(काष्ठा ftrace_likely_data *f, पूर्णांक val, पूर्णांक expect)
अणु
	काष्ठा trace_event_call *call = &event_branch;
	काष्ठा trace_array *tr = branch_tracer;
	काष्ठा trace_buffer *buffer;
	काष्ठा trace_array_cpu *data;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_branch *entry;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक trace_ctx;
	स्थिर अक्षर *p;

	अगर (current->trace_recursion & TRACE_BRANCH_BIT)
		वापस;

	/*
	 * I would love to save just the ftrace_likely_data poपूर्णांकer, but
	 * this code can also be used by modules. Ugly things can happen
	 * अगर the module is unloaded, and then we go and पढ़ो the
	 * poपूर्णांकer.  This is slower, but much safer.
	 */

	अगर (unlikely(!tr))
		वापस;

	raw_local_irq_save(flags);
	current->trace_recursion |= TRACE_BRANCH_BIT;
	data = this_cpu_ptr(tr->array_buffer.data);
	अगर (atomic_पढ़ो(&data->disabled))
		जाओ out;

	trace_ctx = tracing_gen_ctx_flags(flags);
	buffer = tr->array_buffer.buffer;
	event = trace_buffer_lock_reserve(buffer, TRACE_BRANCH,
					  माप(*entry), trace_ctx);
	अगर (!event)
		जाओ out;

	entry	= ring_buffer_event_data(event);

	/* Strip off the path, only save the file */
	p = f->data.file + म_माप(f->data.file);
	जबतक (p >= f->data.file && *p != '/')
		p--;
	p++;

	म_नकलन(entry->func, f->data.func, TRACE_FUNC_SIZE);
	म_नकलन(entry->file, p, TRACE_खाता_SIZE);
	entry->func[TRACE_FUNC_SIZE] = 0;
	entry->file[TRACE_खाता_SIZE] = 0;
	entry->स्थिरant = f->स्थिरant;
	entry->line = f->data.line;
	entry->correct = val == expect;

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit_nostack(buffer, event);

 out:
	current->trace_recursion &= ~TRACE_BRANCH_BIT;
	raw_local_irq_restore(flags);
पूर्ण

अटल अंतरभूत
व्योम trace_likely_condition(काष्ठा ftrace_likely_data *f, पूर्णांक val, पूर्णांक expect)
अणु
	अगर (!branch_tracing_enabled)
		वापस;

	probe_likely_condition(f, val, expect);
पूर्ण

पूर्णांक enable_branch_tracing(काष्ठा trace_array *tr)
अणु
	mutex_lock(&branch_tracing_mutex);
	branch_tracer = tr;
	/*
	 * Must be seen beक्रमe enabling. The पढ़ोer is a condition
	 * where we करो not need a matching rmb()
	 */
	smp_wmb();
	branch_tracing_enabled++;
	mutex_unlock(&branch_tracing_mutex);

	वापस 0;
पूर्ण

व्योम disable_branch_tracing(व्योम)
अणु
	mutex_lock(&branch_tracing_mutex);

	अगर (!branch_tracing_enabled)
		जाओ out_unlock;

	branch_tracing_enabled--;

 out_unlock:
	mutex_unlock(&branch_tracing_mutex);
पूर्ण

अटल पूर्णांक branch_trace_init(काष्ठा trace_array *tr)
अणु
	वापस enable_branch_tracing(tr);
पूर्ण

अटल व्योम branch_trace_reset(काष्ठा trace_array *tr)
अणु
	disable_branch_tracing();
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_branch_prपूर्णांक(काष्ठा trace_iterator *iter,
					    पूर्णांक flags, काष्ठा trace_event *event)
अणु
	काष्ठा trace_branch *field;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(&iter->seq, "[%s] %s:%s:%d\n",
			 field->correct ? "  ok  " : " MISS ",
			 field->func,
			 field->file,
			 field->line);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल व्योम branch_prपूर्णांक_header(काष्ठा seq_file *s)
अणु
	seq_माला_दो(s, "#           TASK-PID    CPU#    TIMESTAMP  CORRECT"
		    "  FUNC:FILE:LINE\n"
		    "#              | |       |          |         |   "
		    "    |\n");
पूर्ण

अटल काष्ठा trace_event_functions trace_branch_funcs = अणु
	.trace		= trace_branch_prपूर्णांक,
पूर्ण;

अटल काष्ठा trace_event trace_branch_event = अणु
	.type		= TRACE_BRANCH,
	.funcs		= &trace_branch_funcs,
पूर्ण;

अटल काष्ठा tracer branch_trace __पढ़ो_mostly =
अणु
	.name		= "branch",
	.init		= branch_trace_init,
	.reset		= branch_trace_reset,
#अगर_घोषित CONFIG_FTRACE_SELFTEST
	.selftest	= trace_selftest_startup_branch,
#पूर्ण_अगर /* CONFIG_FTRACE_SELFTEST */
	.prपूर्णांक_header	= branch_prपूर्णांक_header,
पूर्ण;

__init अटल पूर्णांक init_branch_tracer(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_trace_event(&trace_branch_event);
	अगर (!ret) अणु
		prपूर्णांकk(KERN_WARNING "Warning: could not register "
				    "branch events\n");
		वापस 1;
	पूर्ण
	वापस रेजिस्टर_tracer(&branch_trace);
पूर्ण
core_initcall(init_branch_tracer);

#अन्यथा
अटल अंतरभूत
व्योम trace_likely_condition(काष्ठा ftrace_likely_data *f, पूर्णांक val, पूर्णांक expect)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BRANCH_TRACER */

व्योम ftrace_likely_update(काष्ठा ftrace_likely_data *f, पूर्णांक val,
			  पूर्णांक expect, पूर्णांक is_स्थिरant)
अणु
	अचिन्हित दीर्घ flags = user_access_save();

	/* A स्थिरant is always correct */
	अगर (is_स्थिरant) अणु
		f->स्थिरant++;
		val = expect;
	पूर्ण
	/*
	 * I would love to have a trace poपूर्णांक here instead, but the
	 * trace poपूर्णांक code is so inundated with unlikely and likely
	 * conditions that the recursive nighपंचांगare that exists is too
	 * much to try to get working. At least क्रम now.
	 */
	trace_likely_condition(f, val, expect);

	/* FIXME: Make this atomic! */
	अगर (val == expect)
		f->data.correct++;
	अन्यथा
		f->data.incorrect++;

	user_access_restore(flags);
पूर्ण
EXPORT_SYMBOL(ftrace_likely_update);

बाह्य अचिन्हित दीर्घ __start_annotated_branch_profile[];
बाह्य अचिन्हित दीर्घ __stop_annotated_branch_profile[];

अटल पूर्णांक annotated_branch_stat_headers(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, " correct incorrect  % "
		    "       Function                "
		    "  File              Line\n"
		    " ------- ---------  - "
		    "       --------                "
		    "  ----              ----\n");
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ get_incorrect_percent(स्थिर काष्ठा ftrace_branch_data *p)
अणु
	दीर्घ percent;

	अगर (p->correct) अणु
		percent = p->incorrect * 100;
		percent /= p->correct + p->incorrect;
	पूर्ण अन्यथा
		percent = p->incorrect ? 100 : -1;

	वापस percent;
पूर्ण

अटल स्थिर अक्षर *branch_stat_process_file(काष्ठा ftrace_branch_data *p)
अणु
	स्थिर अक्षर *f;

	/* Only prपूर्णांक the file, not the path */
	f = p->file + म_माप(p->file);
	जबतक (f >= p->file && *f != '/')
		f--;
	वापस ++f;
पूर्ण

अटल व्योम branch_stat_show(काष्ठा seq_file *m,
			     काष्ठा ftrace_branch_data *p, स्थिर अक्षर *f)
अणु
	दीर्घ percent;

	/*
	 * The miss is overlayed on correct, and hit on incorrect.
	 */
	percent = get_incorrect_percent(p);

	अगर (percent < 0)
		seq_माला_दो(m, "  X ");
	अन्यथा
		seq_म_लिखो(m, "%3ld ", percent);

	seq_म_लिखो(m, "%-30.30s %-20.20s %d\n", p->func, f, p->line);
पूर्ण

अटल पूर्णांक branch_stat_show_normal(काष्ठा seq_file *m,
				   काष्ठा ftrace_branch_data *p, स्थिर अक्षर *f)
अणु
	seq_म_लिखो(m, "%8lu %8lu ",  p->correct, p->incorrect);
	branch_stat_show(m, p, f);
	वापस 0;
पूर्ण

अटल पूर्णांक annotate_branch_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ftrace_likely_data *p = v;
	स्थिर अक्षर *f;
	पूर्णांक l;

	f = branch_stat_process_file(&p->data);

	अगर (!p->स्थिरant)
		वापस branch_stat_show_normal(m, &p->data, f);

	l = snम_लिखो(शून्य, 0, "/%lu", p->स्थिरant);
	l = l > 8 ? 0 : 8 - l;

	seq_म_लिखो(m, "%8lu/%lu %*lu ",
		   p->data.correct, p->स्थिरant, l, p->data.incorrect);
	branch_stat_show(m, &p->data, f);
	वापस 0;
पूर्ण

अटल व्योम *annotated_branch_stat_start(काष्ठा tracer_stat *trace)
अणु
	वापस __start_annotated_branch_profile;
पूर्ण

अटल व्योम *
annotated_branch_stat_next(व्योम *v, पूर्णांक idx)
अणु
	काष्ठा ftrace_likely_data *p = v;

	++p;

	अगर ((व्योम *)p >= (व्योम *)__stop_annotated_branch_profile)
		वापस शून्य;

	वापस p;
पूर्ण

अटल पूर्णांक annotated_branch_stat_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा ftrace_branch_data *a = p1;
	स्थिर काष्ठा ftrace_branch_data *b = p2;

	दीर्घ percent_a, percent_b;

	percent_a = get_incorrect_percent(a);
	percent_b = get_incorrect_percent(b);

	अगर (percent_a < percent_b)
		वापस -1;
	अगर (percent_a > percent_b)
		वापस 1;

	अगर (a->incorrect < b->incorrect)
		वापस -1;
	अगर (a->incorrect > b->incorrect)
		वापस 1;

	/*
	 * Since the above shows worse (incorrect) हालs
	 * first, we जारी that by showing best (correct)
	 * हालs last.
	 */
	अगर (a->correct > b->correct)
		वापस -1;
	अगर (a->correct < b->correct)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा tracer_stat annotated_branch_stats = अणु
	.name = "branch_annotated",
	.stat_start = annotated_branch_stat_start,
	.stat_next = annotated_branch_stat_next,
	.stat_cmp = annotated_branch_stat_cmp,
	.stat_headers = annotated_branch_stat_headers,
	.stat_show = annotate_branch_stat_show
पूर्ण;

__init अटल पूर्णांक init_annotated_branch_stats(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_stat_tracer(&annotated_branch_stats);
	अगर (!ret) अणु
		prपूर्णांकk(KERN_WARNING "Warning: could not register "
				    "annotated branches stats\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
fs_initcall(init_annotated_branch_stats);

#अगर_घोषित CONFIG_PROखाता_ALL_BRANCHES

बाह्य अचिन्हित दीर्घ __start_branch_profile[];
बाह्य अचिन्हित दीर्घ __stop_branch_profile[];

अटल पूर्णांक all_branch_stat_headers(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "   miss      hit    % "
		    "       Function                "
		    "  File              Line\n"
		    " ------- ---------  - "
		    "       --------                "
		    "  ----              ----\n");
	वापस 0;
पूर्ण

अटल व्योम *all_branch_stat_start(काष्ठा tracer_stat *trace)
अणु
	वापस __start_branch_profile;
पूर्ण

अटल व्योम *
all_branch_stat_next(व्योम *v, पूर्णांक idx)
अणु
	काष्ठा ftrace_branch_data *p = v;

	++p;

	अगर ((व्योम *)p >= (व्योम *)__stop_branch_profile)
		वापस शून्य;

	वापस p;
पूर्ण

अटल पूर्णांक all_branch_stat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ftrace_branch_data *p = v;
	स्थिर अक्षर *f;

	f = branch_stat_process_file(p);
	वापस branch_stat_show_normal(m, p, f);
पूर्ण

अटल काष्ठा tracer_stat all_branch_stats = अणु
	.name = "branch_all",
	.stat_start = all_branch_stat_start,
	.stat_next = all_branch_stat_next,
	.stat_headers = all_branch_stat_headers,
	.stat_show = all_branch_stat_show
पूर्ण;

__init अटल पूर्णांक all_annotated_branch_stats(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_stat_tracer(&all_branch_stats);
	अगर (!ret) अणु
		prपूर्णांकk(KERN_WARNING "Warning: could not register "
				    "all branches stats\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
fs_initcall(all_annotated_branch_stats);
#पूर्ण_अगर /* CONFIG_PROखाता_ALL_BRANCHES */
